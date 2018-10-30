// dear imgui, v1.50 WIP
// (drawing and font code)

// Contains implementation for
// - ImDrawList
// - ImDrawData
// - ImFontAtlas
// - ImFont
// - Default font data

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_PLACEMENT_NEW
#include "imgui_internal.h"

#include <stdio.h>      // vsnprintf, sscanf, printf
#if !defined(alloca)
#ifdef _WIN32
#include <malloc.h>     // alloca
#elif (defined(__FreeBSD__) || defined(FreeBSD_kernel) || defined(__DragonFly__)) && !defined(__GLIBC__)
#include <stdlib.h>     // alloca. FreeBSD uses stdlib.h unless GLIBC
#else
#include <alloca.h>     // alloca
#endif
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4505) // unreferenced local function has been removed (stb stuff)
#pragma warning (disable: 4996) // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#define snprintf _snprintf
#endif

#ifdef __clang__
#pragma clang diagnostic ignored "-Wold-style-cast"         // warning : use of old-style cast                              // yes, they are more terse.
#pragma clang diagnostic ignored "-Wfloat-equal"            // warning : comparing floating point with == or != is unsafe   // storing and comparing against same constants ok.
#pragma clang diagnostic ignored "-Wglobal-constructors"    // warning : declaration requires a global destructor           // similar to above, not sure what the exact difference it.
#pragma clang diagnostic ignored "-Wsign-conversion"        // warning : implicit conversion changes signedness             //
#if __has_warning("-Wreserved-id-macro")
#pragma clang diagnostic ignored "-Wreserved-id-macro"      // warning : macro name is a reserved identifier                //
#endif
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-function"          // warning: 'xxxx' defined but not used
#pragma GCC diagnostic ignored "-Wdouble-promotion"         // warning: implicit conversion from 'float' to 'double' when passing argument to function
#pragma GCC diagnostic ignored "-Wconversion"               // warning: conversion to 'xxxx' from 'xxxx' may alter its value
#pragma GCC diagnostic ignored "-Wcast-qual"                // warning: cast from type 'xxxx' to type 'xxxx' casts away qualifiers
#endif

//-------------------------------------------------------------------------
// STB libraries implementation
//-------------------------------------------------------------------------

//#define IMGUI_STB_NAMESPACE     ImGuiStb
//#define IMGUI_DISABLE_STB_RECT_PACK_IMPLEMENTATION
//#define IMGUI_DISABLE_STB_TRUETYPE_IMPLEMENTATION

#ifdef IMGUI_STB_NAMESPACE
namespace IMGUI_STB_NAMESPACE
{
#endif

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4456)                             // declaration of 'xx' hides previous local declaration
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"         // warning : use of old-style cast                              // yes, they are more terse.
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#endif

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"              // warning: comparison is always true due to limited range of data type [-Wtype-limits]
#endif

#define STBRP_ASSERT(x)    IM_ASSERT(x)
#ifndef IMGUI_DISABLE_STB_RECT_PACK_IMPLEMENTATION
#define STBRP_STATIC
#define STB_RECT_PACK_IMPLEMENTATION
#endif
#include "stb_rect_pack.h"

#define STBTT_malloc(x,u)  ((void)(u), ImGui::MemAlloc(x))
#define STBTT_free(x,u)    ((void)(u), ImGui::MemFree(x))
#define STBTT_assert(x)    IM_ASSERT(x)
#ifndef IMGUI_DISABLE_STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#else
#define STBTT_DEF extern
#endif
#include "stb_truetype.h"

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#ifdef _MSC_VER
#pragma warning (pop)
#endif

#ifdef IMGUI_STB_NAMESPACE
} // namespace ImGuiStb
using namespace IMGUI_STB_NAMESPACE;
#endif

//-----------------------------------------------------------------------------
// ImDrawList
//-----------------------------------------------------------------------------

static const ImVec4 GNullClipRect(-8192.0f, -8192.0f, +8192.0f, +8192.0f); // Large values that are easy to encode in a few bits+shift

void ImDrawList::Clear()
{
	CmdBuffer.resize(0);
	IdxBuffer.resize(0);
	VtxBuffer.resize(0);
	_VtxCurrentIdx = 0;
	_VtxWritePtr = NULL;
	_IdxWritePtr = NULL;
	_ClipRectStack.resize(0);
	_TextureIdStack.resize(0);
	_Path.resize(0);
	_ChannelsCurrent = 0;
	_ChannelsCount = 1;
	// NB: Do not clear channels so our allocations are re-used after the first frame.
}

void ImDrawList::ClearFreeMemory()
{
	CmdBuffer.clear();
	IdxBuffer.clear();
	VtxBuffer.clear();
	_VtxCurrentIdx = 0;
	_VtxWritePtr = NULL;
	_IdxWritePtr = NULL;
	_ClipRectStack.clear();
	_TextureIdStack.clear();
	_Path.clear();
	_ChannelsCurrent = 0;
	_ChannelsCount = 1;
	for (int i = 0; i < _Channels.Size; i++)
	{
		if (i == 0) memset(&_Channels[0], 0, sizeof(_Channels[0]));  // channel 0 is a copy of CmdBuffer/IdxBuffer, don't destruct again
		_Channels[i].CmdBuffer.clear();
		_Channels[i].IdxBuffer.clear();
	}
	_Channels.clear();
}

// Use macros because C++ is a terrible language, we want guaranteed inline, no code in header, and no overhead in Debug mode
#define GetCurrentClipRect()    (_ClipRectStack.Size ? _ClipRectStack.Data[_ClipRectStack.Size-1]  : GNullClipRect)
#define GetCurrentTextureId()   (_TextureIdStack.Size ? _TextureIdStack.Data[_TextureIdStack.Size-1] : NULL)

void ImDrawList::AddDrawCmd()
{
	ImDrawCmd draw_cmd;
	draw_cmd.ClipRect = GetCurrentClipRect();
	draw_cmd.TextureId = GetCurrentTextureId();

	IM_ASSERT(draw_cmd.ClipRect.x <= draw_cmd.ClipRect.z && draw_cmd.ClipRect.y <= draw_cmd.ClipRect.w);
	CmdBuffer.push_back(draw_cmd);
}

void ImDrawList::AddCallback(ImDrawCallback callback, void* callback_data)
{
	ImDrawCmd* current_cmd = CmdBuffer.Size ? &CmdBuffer.back() : NULL;
	if (!current_cmd || current_cmd->ElemCount != 0 || current_cmd->UserCallback != NULL)
	{
		AddDrawCmd();
		current_cmd = &CmdBuffer.back();
	}
	current_cmd->UserCallback = callback;
	current_cmd->UserCallbackData = callback_data;

	AddDrawCmd(); // Force a new command after us (see comment below)
}

// Our scheme may appears a bit unusual, basically we want the most-common calls AddLine AddRect etc. to not have to perform any check so we always have a command ready in the stack.
// The cost of figuring out if a new command has to be added or if we can merge is paid in those Update** functions only.
void ImDrawList::UpdateClipRect()
{
	// If current command is used with different settings we need to add a new command
	const ImVec4 curr_clip_rect = GetCurrentClipRect();
	ImDrawCmd* curr_cmd = CmdBuffer.Size > 0 ? &CmdBuffer.Data[CmdBuffer.Size - 1] : NULL;
	if (!curr_cmd || (curr_cmd->ElemCount != 0 && memcmp(&curr_cmd->ClipRect, &curr_clip_rect, sizeof(ImVec4)) != 0) || curr_cmd->UserCallback != NULL)
	{
		AddDrawCmd();
		return;
	}

	// Try to merge with previous command if it matches, else use current command
	ImDrawCmd* prev_cmd = CmdBuffer.Size > 1 ? curr_cmd - 1 : NULL;
	if (curr_cmd->ElemCount == 0 && prev_cmd && memcmp(&prev_cmd->ClipRect, &curr_clip_rect, sizeof(ImVec4)) == 0 && prev_cmd->TextureId == GetCurrentTextureId() && prev_cmd->UserCallback == NULL)
		CmdBuffer.pop_back();
	else
		curr_cmd->ClipRect = curr_clip_rect;
}

void ImDrawList::UpdateTextureID()
{
	// If current command is used with different settings we need to add a new command
	const ImTextureID curr_texture_id = GetCurrentTextureId();
	ImDrawCmd* curr_cmd = CmdBuffer.Size ? &CmdBuffer.back() : NULL;
	if (!curr_cmd || (curr_cmd->ElemCount != 0 && curr_cmd->TextureId != curr_texture_id) || curr_cmd->UserCallback != NULL)
	{
		AddDrawCmd();
		return;
	}

	// Try to merge with previous command if it matches, else use current command
	ImDrawCmd* prev_cmd = CmdBuffer.Size > 1 ? curr_cmd - 1 : NULL;
	if (prev_cmd && prev_cmd->TextureId == curr_texture_id && memcmp(&prev_cmd->ClipRect, &GetCurrentClipRect(), sizeof(ImVec4)) == 0 && prev_cmd->UserCallback == NULL)
		CmdBuffer.pop_back();
	else
		curr_cmd->TextureId = curr_texture_id;
}

#undef GetCurrentClipRect
#undef GetCurrentTextureId

// Render-level scissoring. This is passed down to your render function but not used for CPU-side coarse clipping. Prefer using higher-level ImGui::PushClipRect() to affect logic (hit-testing and widget culling)
void ImDrawList::PushClipRect(ImVec2 cr_min, ImVec2 cr_max, bool intersect_with_current_clip_rect)
{
	ImVec4 cr(cr_min.x, cr_min.y, cr_max.x, cr_max.y);
	if (intersect_with_current_clip_rect && _ClipRectStack.Size)
	{
		ImVec4 current = _ClipRectStack.Data[_ClipRectStack.Size - 1];
		if (cr.x < current.x) cr.x = current.x;
		if (cr.y < current.y) cr.y = current.y;
		if (cr.z > current.z) cr.z = current.z;
		if (cr.w > current.w) cr.w = current.w;
	}
	cr.z = ImMax(cr.x, cr.z);
	cr.w = ImMax(cr.y, cr.w);

	_ClipRectStack.push_back(cr);
	UpdateClipRect();
}

void ImDrawList::PushClipRectFullScreen()
{
	PushClipRect(ImVec2(GNullClipRect.x, GNullClipRect.y), ImVec2(GNullClipRect.z, GNullClipRect.w));
	//PushClipRect(GetVisibleRect());   // FIXME-OPT: This would be more correct but we're not supposed to access ImGuiContext from here?
}

void ImDrawList::PopClipRect()
{
	IM_ASSERT(_ClipRectStack.Size > 0);
	_ClipRectStack.pop_back();
	UpdateClipRect();
}

void ImDrawList::PushTextureID(const ImTextureID& texture_id)
{
	_TextureIdStack.push_back(texture_id);
	UpdateTextureID();
}

void ImDrawList::PopTextureID()
{
	IM_ASSERT(_TextureIdStack.Size > 0);
	_TextureIdStack.pop_back();
	UpdateTextureID();
}

void ImDrawList::ChannelsSplit(int channels_count)
{
	IM_ASSERT(_ChannelsCurrent == 0 && _ChannelsCount == 1);
	int old_channels_count = _Channels.Size;
	if (old_channels_count < channels_count)
		_Channels.resize(channels_count);
	_ChannelsCount = channels_count;

	// _Channels[] (24 bytes each) hold storage that we'll swap with this->_CmdBuffer/_IdxBuffer
	// The content of _Channels[0] at this point doesn't matter. We clear it to make state tidy in a debugger but we don't strictly need to.
	// When we switch to the next channel, we'll copy _CmdBuffer/_IdxBuffer into _Channels[0] and then _Channels[1] into _CmdBuffer/_IdxBuffer
	memset(&_Channels[0], 0, sizeof(ImDrawChannel));
	for (int i = 1; i < channels_count; i++)
	{
		if (i >= old_channels_count)
		{
			IM_PLACEMENT_NEW(&_Channels[i]) ImDrawChannel();
		}
		else
		{
			_Channels[i].CmdBuffer.resize(0);
			_Channels[i].IdxBuffer.resize(0);
		}
		if (_Channels[i].CmdBuffer.Size == 0)
		{
			ImDrawCmd draw_cmd;
			draw_cmd.ClipRect = _ClipRectStack.back();
			draw_cmd.TextureId = _TextureIdStack.back();
			_Channels[i].CmdBuffer.push_back(draw_cmd);
		}
	}
}

void ImDrawList::ChannelsMerge()
{
	// Note that we never use or rely on channels.Size because it is merely a buffer that we never shrink back to 0 to keep all sub-buffers ready for use.
	if (_ChannelsCount <= 1)
		return;

	ChannelsSetCurrent(0);
	if (CmdBuffer.Size && CmdBuffer.back().ElemCount == 0)
		CmdBuffer.pop_back();

	int new_cmd_buffer_count = 0, new_idx_buffer_count = 0;
	for (int i = 1; i < _ChannelsCount; i++)
	{
		ImDrawChannel& ch = _Channels[i];
		if (ch.CmdBuffer.Size && ch.CmdBuffer.back().ElemCount == 0)
			ch.CmdBuffer.pop_back();
		new_cmd_buffer_count += ch.CmdBuffer.Size;
		new_idx_buffer_count += ch.IdxBuffer.Size;
	}
	CmdBuffer.resize(CmdBuffer.Size + new_cmd_buffer_count);
	IdxBuffer.resize(IdxBuffer.Size + new_idx_buffer_count);

	ImDrawCmd* cmd_write = CmdBuffer.Data + CmdBuffer.Size - new_cmd_buffer_count;
	_IdxWritePtr = IdxBuffer.Data + IdxBuffer.Size - new_idx_buffer_count;
	for (int i = 1; i < _ChannelsCount; i++)
	{
		ImDrawChannel& ch = _Channels[i];
		if (int sz = ch.CmdBuffer.Size) { memcpy(cmd_write, ch.CmdBuffer.Data, sz * sizeof(ImDrawCmd)); cmd_write += sz; }
		if (int sz = ch.IdxBuffer.Size) { memcpy(_IdxWritePtr, ch.IdxBuffer.Data, sz * sizeof(ImDrawIdx)); _IdxWritePtr += sz; }
	}
	AddDrawCmd();
	_ChannelsCount = 1;
}

void ImDrawList::ChannelsSetCurrent(int idx)
{
	IM_ASSERT(idx < _ChannelsCount);
	if (_ChannelsCurrent == idx) return;
	memcpy(&_Channels.Data[_ChannelsCurrent].CmdBuffer, &CmdBuffer, sizeof(CmdBuffer)); // copy 12 bytes, four times
	memcpy(&_Channels.Data[_ChannelsCurrent].IdxBuffer, &IdxBuffer, sizeof(IdxBuffer));
	_ChannelsCurrent = idx;
	memcpy(&CmdBuffer, &_Channels.Data[_ChannelsCurrent].CmdBuffer, sizeof(CmdBuffer));
	memcpy(&IdxBuffer, &_Channels.Data[_ChannelsCurrent].IdxBuffer, sizeof(IdxBuffer));
	_IdxWritePtr = IdxBuffer.Data + IdxBuffer.Size;
}

// NB: this can be called with negative count for removing primitives (as long as the result does not underflow)
void ImDrawList::PrimReserve(int idx_count, int vtx_count)
{
	ImDrawCmd& draw_cmd = CmdBuffer.Data[CmdBuffer.Size - 1];
	draw_cmd.ElemCount += idx_count;

	int vtx_buffer_size = VtxBuffer.Size;
	VtxBuffer.resize(vtx_buffer_size + vtx_count);
	_VtxWritePtr = VtxBuffer.Data + vtx_buffer_size;

	int idx_buffer_size = IdxBuffer.Size;
	IdxBuffer.resize(idx_buffer_size + idx_count);
	_IdxWritePtr = IdxBuffer.Data + idx_buffer_size;
}

// Fully unrolled with inline call to keep our debug builds decently fast.
void ImDrawList::PrimRect(const ImVec2& a, const ImVec2& c, ImU32 col)
{
	ImVec2 b(c.x, a.y), d(a.x, c.y), uv(GImGui->FontTexUvWhitePixel);
	ImDrawIdx idx = (ImDrawIdx)_VtxCurrentIdx;
	_IdxWritePtr[0] = idx; _IdxWritePtr[1] = (ImDrawIdx)(idx + 1); _IdxWritePtr[2] = (ImDrawIdx)(idx + 2);
	_IdxWritePtr[3] = idx; _IdxWritePtr[4] = (ImDrawIdx)(idx + 2); _IdxWritePtr[5] = (ImDrawIdx)(idx + 3);
	_VtxWritePtr[0].pos = a; _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col;
	_VtxWritePtr[1].pos = b; _VtxWritePtr[1].uv = uv; _VtxWritePtr[1].col = col;
	_VtxWritePtr[2].pos = c; _VtxWritePtr[2].uv = uv; _VtxWritePtr[2].col = col;
	_VtxWritePtr[3].pos = d; _VtxWritePtr[3].uv = uv; _VtxWritePtr[3].col = col;
	_VtxWritePtr += 4;
	_VtxCurrentIdx += 4;
	_IdxWritePtr += 6;
}

void ImDrawList::PrimRectUV(const ImVec2& a, const ImVec2& c, const ImVec2& uv_a, const ImVec2& uv_c, ImU32 col)
{
	ImVec2 b(c.x, a.y), d(a.x, c.y), uv_b(uv_c.x, uv_a.y), uv_d(uv_a.x, uv_c.y);
	ImDrawIdx idx = (ImDrawIdx)_VtxCurrentIdx;
	_IdxWritePtr[0] = idx; _IdxWritePtr[1] = (ImDrawIdx)(idx + 1); _IdxWritePtr[2] = (ImDrawIdx)(idx + 2);
	_IdxWritePtr[3] = idx; _IdxWritePtr[4] = (ImDrawIdx)(idx + 2); _IdxWritePtr[5] = (ImDrawIdx)(idx + 3);
	_VtxWritePtr[0].pos = a; _VtxWritePtr[0].uv = uv_a; _VtxWritePtr[0].col = col;
	_VtxWritePtr[1].pos = b; _VtxWritePtr[1].uv = uv_b; _VtxWritePtr[1].col = col;
	_VtxWritePtr[2].pos = c; _VtxWritePtr[2].uv = uv_c; _VtxWritePtr[2].col = col;
	_VtxWritePtr[3].pos = d; _VtxWritePtr[3].uv = uv_d; _VtxWritePtr[3].col = col;
	_VtxWritePtr += 4;
	_VtxCurrentIdx += 4;
	_IdxWritePtr += 6;
}

void ImDrawList::PrimQuadUV(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImVec2& uv_a, const ImVec2& uv_b, const ImVec2& uv_c, const ImVec2& uv_d, ImU32 col)
{
	ImDrawIdx idx = (ImDrawIdx)_VtxCurrentIdx;
	_IdxWritePtr[0] = idx; _IdxWritePtr[1] = (ImDrawIdx)(idx + 1); _IdxWritePtr[2] = (ImDrawIdx)(idx + 2);
	_IdxWritePtr[3] = idx; _IdxWritePtr[4] = (ImDrawIdx)(idx + 2); _IdxWritePtr[5] = (ImDrawIdx)(idx + 3);
	_VtxWritePtr[0].pos = a; _VtxWritePtr[0].uv = uv_a; _VtxWritePtr[0].col = col;
	_VtxWritePtr[1].pos = b; _VtxWritePtr[1].uv = uv_b; _VtxWritePtr[1].col = col;
	_VtxWritePtr[2].pos = c; _VtxWritePtr[2].uv = uv_c; _VtxWritePtr[2].col = col;
	_VtxWritePtr[3].pos = d; _VtxWritePtr[3].uv = uv_d; _VtxWritePtr[3].col = col;
	_VtxWritePtr += 4;
	_VtxCurrentIdx += 4;
	_IdxWritePtr += 6;
}

// TODO: Thickness anti-aliased lines cap are missing their AA fringe.
void ImDrawList::AddPolyline(const ImVec2* points, const int points_count, ImU32 col, bool closed, float thickness, bool anti_aliased)
{
	if (points_count < 2)
		return;

	const ImVec2 uv = GImGui->FontTexUvWhitePixel;
	anti_aliased &= GImGui->Style.AntiAliasedLines;
	//if (ImGui::GetIO().KeyCtrl) anti_aliased = false; // Debug

	int count = points_count;
	if (!closed)
		count = points_count - 1;

	const bool thick_line = thickness > 1.0f;
	if (anti_aliased)
	{
		// Anti-aliased stroke
		const float AA_SIZE = 1.0f;
		const ImU32 col_trans = col & IM_COL32(255, 255, 255, 0);

		const int idx_count = thick_line ? count * 18 : count * 12;
		const int vtx_count = thick_line ? points_count * 4 : points_count * 3;
		PrimReserve(idx_count, vtx_count);

		// Temporary buffer
		ImVec2* temp_normals = (ImVec2*)alloca(points_count * (thick_line ? 5 : 3) * sizeof(ImVec2));
		ImVec2* temp_points = temp_normals + points_count;

		for (int i1 = 0; i1 < count; i1++)
		{
			const int i2 = (i1 + 1) == points_count ? 0 : i1 + 1;
			ImVec2 diff = points[i2] - points[i1];
			diff *= ImInvLength(diff, 1.0f);
			temp_normals[i1].x = diff.y;
			temp_normals[i1].y = -diff.x;
		}
		if (!closed)
			temp_normals[points_count - 1] = temp_normals[points_count - 2];

		if (!thick_line)
		{
			if (!closed)
			{
				temp_points[0] = points[0] + temp_normals[0] * AA_SIZE;
				temp_points[1] = points[0] - temp_normals[0] * AA_SIZE;
				temp_points[(points_count - 1) * 2 + 0] = points[points_count - 1] + temp_normals[points_count - 1] * AA_SIZE;
				temp_points[(points_count - 1) * 2 + 1] = points[points_count - 1] - temp_normals[points_count - 1] * AA_SIZE;
			}

			// FIXME-OPT: Merge the different loops, possibly remove the temporary buffer.
			unsigned int idx1 = _VtxCurrentIdx;
			for (int i1 = 0; i1 < count; i1++)
			{
				const int i2 = (i1 + 1) == points_count ? 0 : i1 + 1;
				unsigned int idx2 = (i1 + 1) == points_count ? _VtxCurrentIdx : idx1 + 3;

				// Average normals
				ImVec2 dm = (temp_normals[i1] + temp_normals[i2]) * 0.5f;
				float dmr2 = dm.x*dm.x + dm.y*dm.y;
				if (dmr2 > 0.000001f)
				{
					float scale = 1.0f / dmr2;
					if (scale > 100.0f) scale = 100.0f;
					dm *= scale;
				}
				dm *= AA_SIZE;
				temp_points[i2 * 2 + 0] = points[i2] + dm;
				temp_points[i2 * 2 + 1] = points[i2] - dm;

				// Add indexes
				_IdxWritePtr[0] = (ImDrawIdx)(idx2 + 0); _IdxWritePtr[1] = (ImDrawIdx)(idx1 + 0); _IdxWritePtr[2] = (ImDrawIdx)(idx1 + 2);
				_IdxWritePtr[3] = (ImDrawIdx)(idx1 + 2); _IdxWritePtr[4] = (ImDrawIdx)(idx2 + 2); _IdxWritePtr[5] = (ImDrawIdx)(idx2 + 0);
				_IdxWritePtr[6] = (ImDrawIdx)(idx2 + 1); _IdxWritePtr[7] = (ImDrawIdx)(idx1 + 1); _IdxWritePtr[8] = (ImDrawIdx)(idx1 + 0);
				_IdxWritePtr[9] = (ImDrawIdx)(idx1 + 0); _IdxWritePtr[10] = (ImDrawIdx)(idx2 + 0); _IdxWritePtr[11] = (ImDrawIdx)(idx2 + 1);
				_IdxWritePtr += 12;

				idx1 = idx2;
			}

			// Add vertexes
			for (int i = 0; i < points_count; i++)
			{
				_VtxWritePtr[0].pos = points[i];          _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col;
				_VtxWritePtr[1].pos = temp_points[i * 2 + 0]; _VtxWritePtr[1].uv = uv; _VtxWritePtr[1].col = col_trans;
				_VtxWritePtr[2].pos = temp_points[i * 2 + 1]; _VtxWritePtr[2].uv = uv; _VtxWritePtr[2].col = col_trans;
				_VtxWritePtr += 3;
			}
		}
		else
		{
			const float half_inner_thickness = (thickness - AA_SIZE) * 0.5f;
			if (!closed)
			{
				temp_points[0] = points[0] + temp_normals[0] * (half_inner_thickness + AA_SIZE);
				temp_points[1] = points[0] + temp_normals[0] * (half_inner_thickness);
				temp_points[2] = points[0] - temp_normals[0] * (half_inner_thickness);
				temp_points[3] = points[0] - temp_normals[0] * (half_inner_thickness + AA_SIZE);
				temp_points[(points_count - 1) * 4 + 0] = points[points_count - 1] + temp_normals[points_count - 1] * (half_inner_thickness + AA_SIZE);
				temp_points[(points_count - 1) * 4 + 1] = points[points_count - 1] + temp_normals[points_count - 1] * (half_inner_thickness);
				temp_points[(points_count - 1) * 4 + 2] = points[points_count - 1] - temp_normals[points_count - 1] * (half_inner_thickness);
				temp_points[(points_count - 1) * 4 + 3] = points[points_count - 1] - temp_normals[points_count - 1] * (half_inner_thickness + AA_SIZE);
			}

			// FIXME-OPT: Merge the different loops, possibly remove the temporary buffer.
			unsigned int idx1 = _VtxCurrentIdx;
			for (int i1 = 0; i1 < count; i1++)
			{
				const int i2 = (i1 + 1) == points_count ? 0 : i1 + 1;
				unsigned int idx2 = (i1 + 1) == points_count ? _VtxCurrentIdx : idx1 + 4;

				// Average normals
				ImVec2 dm = (temp_normals[i1] + temp_normals[i2]) * 0.5f;
				float dmr2 = dm.x*dm.x + dm.y*dm.y;
				if (dmr2 > 0.000001f)
				{
					float scale = 1.0f / dmr2;
					if (scale > 100.0f) scale = 100.0f;
					dm *= scale;
				}
				ImVec2 dm_out = dm * (half_inner_thickness + AA_SIZE);
				ImVec2 dm_in = dm * half_inner_thickness;
				temp_points[i2 * 4 + 0] = points[i2] + dm_out;
				temp_points[i2 * 4 + 1] = points[i2] + dm_in;
				temp_points[i2 * 4 + 2] = points[i2] - dm_in;
				temp_points[i2 * 4 + 3] = points[i2] - dm_out;

				// Add indexes
				_IdxWritePtr[0] = (ImDrawIdx)(idx2 + 1); _IdxWritePtr[1] = (ImDrawIdx)(idx1 + 1); _IdxWritePtr[2] = (ImDrawIdx)(idx1 + 2);
				_IdxWritePtr[3] = (ImDrawIdx)(idx1 + 2); _IdxWritePtr[4] = (ImDrawIdx)(idx2 + 2); _IdxWritePtr[5] = (ImDrawIdx)(idx2 + 1);
				_IdxWritePtr[6] = (ImDrawIdx)(idx2 + 1); _IdxWritePtr[7] = (ImDrawIdx)(idx1 + 1); _IdxWritePtr[8] = (ImDrawIdx)(idx1 + 0);
				_IdxWritePtr[9] = (ImDrawIdx)(idx1 + 0); _IdxWritePtr[10] = (ImDrawIdx)(idx2 + 0); _IdxWritePtr[11] = (ImDrawIdx)(idx2 + 1);
				_IdxWritePtr[12] = (ImDrawIdx)(idx2 + 2); _IdxWritePtr[13] = (ImDrawIdx)(idx1 + 2); _IdxWritePtr[14] = (ImDrawIdx)(idx1 + 3);
				_IdxWritePtr[15] = (ImDrawIdx)(idx1 + 3); _IdxWritePtr[16] = (ImDrawIdx)(idx2 + 3); _IdxWritePtr[17] = (ImDrawIdx)(idx2 + 2);
				_IdxWritePtr += 18;

				idx1 = idx2;
			}

			// Add vertexes
			for (int i = 0; i < points_count; i++)
			{
				_VtxWritePtr[0].pos = temp_points[i * 4 + 0]; _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col_trans;
				_VtxWritePtr[1].pos = temp_points[i * 4 + 1]; _VtxWritePtr[1].uv = uv; _VtxWritePtr[1].col = col;
				_VtxWritePtr[2].pos = temp_points[i * 4 + 2]; _VtxWritePtr[2].uv = uv; _VtxWritePtr[2].col = col;
				_VtxWritePtr[3].pos = temp_points[i * 4 + 3]; _VtxWritePtr[3].uv = uv; _VtxWritePtr[3].col = col_trans;
				_VtxWritePtr += 4;
			}
		}
		_VtxCurrentIdx += (ImDrawIdx)vtx_count;
	}
	else
	{
		// Non Anti-aliased Stroke
		const int idx_count = count * 6;
		const int vtx_count = count * 4;      // FIXME-OPT: Not sharing edges
		PrimReserve(idx_count, vtx_count);

		for (int i1 = 0; i1 < count; i1++)
		{
			const int i2 = (i1 + 1) == points_count ? 0 : i1 + 1;
			const ImVec2& p1 = points[i1];
			const ImVec2& p2 = points[i2];
			ImVec2 diff = p2 - p1;
			diff *= ImInvLength(diff, 1.0f);

			const float dx = diff.x * (thickness * 0.5f);
			const float dy = diff.y * (thickness * 0.5f);
			_VtxWritePtr[0].pos.x = p1.x + dy; _VtxWritePtr[0].pos.y = p1.y - dx; _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col;
			_VtxWritePtr[1].pos.x = p2.x + dy; _VtxWritePtr[1].pos.y = p2.y - dx; _VtxWritePtr[1].uv = uv; _VtxWritePtr[1].col = col;
			_VtxWritePtr[2].pos.x = p2.x - dy; _VtxWritePtr[2].pos.y = p2.y + dx; _VtxWritePtr[2].uv = uv; _VtxWritePtr[2].col = col;
			_VtxWritePtr[3].pos.x = p1.x - dy; _VtxWritePtr[3].pos.y = p1.y + dx; _VtxWritePtr[3].uv = uv; _VtxWritePtr[3].col = col;
			_VtxWritePtr += 4;

			_IdxWritePtr[0] = (ImDrawIdx)(_VtxCurrentIdx); _IdxWritePtr[1] = (ImDrawIdx)(_VtxCurrentIdx + 1); _IdxWritePtr[2] = (ImDrawIdx)(_VtxCurrentIdx + 2);
			_IdxWritePtr[3] = (ImDrawIdx)(_VtxCurrentIdx); _IdxWritePtr[4] = (ImDrawIdx)(_VtxCurrentIdx + 2); _IdxWritePtr[5] = (ImDrawIdx)(_VtxCurrentIdx + 3);
			_IdxWritePtr += 6;
			_VtxCurrentIdx += 4;
		}
	}
}

void ImDrawList::AddConvexPolyFilled(const ImVec2* points, const int points_count, ImU32 col, bool anti_aliased)
{
	const ImVec2 uv = GImGui->FontTexUvWhitePixel;
	anti_aliased &= GImGui->Style.AntiAliasedShapes;
	//if (ImGui::GetIO().KeyCtrl) anti_aliased = false; // Debug

	if (anti_aliased)
	{
		// Anti-aliased Fill
		const float AA_SIZE = 1.0f;
		const ImU32 col_trans = col & IM_COL32(255, 255, 255, 0);
		const int idx_count = (points_count - 2) * 3 + points_count * 6;
		const int vtx_count = (points_count * 2);
		PrimReserve(idx_count, vtx_count);

		// Add indexes for fill
		unsigned int vtx_inner_idx = _VtxCurrentIdx;
		unsigned int vtx_outer_idx = _VtxCurrentIdx + 1;
		for (int i = 2; i < points_count; i++)
		{
			_IdxWritePtr[0] = (ImDrawIdx)(vtx_inner_idx); _IdxWritePtr[1] = (ImDrawIdx)(vtx_inner_idx + ((i - 1) << 1)); _IdxWritePtr[2] = (ImDrawIdx)(vtx_inner_idx + (i << 1));
			_IdxWritePtr += 3;
		}

		// Compute normals
		ImVec2* temp_normals = (ImVec2*)alloca(points_count * sizeof(ImVec2));
		for (int i0 = points_count - 1, i1 = 0; i1 < points_count; i0 = i1++)
		{
			const ImVec2& p0 = points[i0];
			const ImVec2& p1 = points[i1];
			ImVec2 diff = p1 - p0;
			diff *= ImInvLength(diff, 1.0f);
			temp_normals[i0].x = diff.y;
			temp_normals[i0].y = -diff.x;
		}

		for (int i0 = points_count - 1, i1 = 0; i1 < points_count; i0 = i1++)
		{
			// Average normals
			const ImVec2& n0 = temp_normals[i0];
			const ImVec2& n1 = temp_normals[i1];
			ImVec2 dm = (n0 + n1) * 0.5f;
			float dmr2 = dm.x*dm.x + dm.y*dm.y;
			if (dmr2 > 0.000001f)
			{
				float scale = 1.0f / dmr2;
				if (scale > 100.0f) scale = 100.0f;
				dm *= scale;
			}
			dm *= AA_SIZE * 0.5f;

			// Add vertices
			_VtxWritePtr[0].pos = (points[i1] - dm); _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col;        // Inner
			_VtxWritePtr[1].pos = (points[i1] + dm); _VtxWritePtr[1].uv = uv; _VtxWritePtr[1].col = col_trans;  // Outer
			_VtxWritePtr += 2;

			// Add indexes for fringes
			_IdxWritePtr[0] = (ImDrawIdx)(vtx_inner_idx + (i1 << 1)); _IdxWritePtr[1] = (ImDrawIdx)(vtx_inner_idx + (i0 << 1)); _IdxWritePtr[2] = (ImDrawIdx)(vtx_outer_idx + (i0 << 1));
			_IdxWritePtr[3] = (ImDrawIdx)(vtx_outer_idx + (i0 << 1)); _IdxWritePtr[4] = (ImDrawIdx)(vtx_outer_idx + (i1 << 1)); _IdxWritePtr[5] = (ImDrawIdx)(vtx_inner_idx + (i1 << 1));
			_IdxWritePtr += 6;
		}
		_VtxCurrentIdx += (ImDrawIdx)vtx_count;
	}
	else
	{
		// Non Anti-aliased Fill
		const int idx_count = (points_count - 2) * 3;
		const int vtx_count = points_count;
		PrimReserve(idx_count, vtx_count);
		for (int i = 0; i < vtx_count; i++)
		{
			_VtxWritePtr[0].pos = points[i]; _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col;
			_VtxWritePtr++;
		}
		for (int i = 2; i < points_count; i++)
		{
			_IdxWritePtr[0] = (ImDrawIdx)(_VtxCurrentIdx); _IdxWritePtr[1] = (ImDrawIdx)(_VtxCurrentIdx + i - 1); _IdxWritePtr[2] = (ImDrawIdx)(_VtxCurrentIdx + i);
			_IdxWritePtr += 3;
		}
		_VtxCurrentIdx += (ImDrawIdx)vtx_count;
	}
}

void ImDrawList::PathArcToFast(const ImVec2& centre, float radius, int amin, int amax)
{
	static ImVec2 circle_vtx[12];
	static bool circle_vtx_builds = false;
	const int circle_vtx_count = IM_ARRAYSIZE(circle_vtx);
	if (!circle_vtx_builds)
	{
		for (int i = 0; i < circle_vtx_count; i++)
		{
			const float a = ((float)i / (float)circle_vtx_count) * 2 * IM_PI;
			circle_vtx[i].x = cosf(a);
			circle_vtx[i].y = sinf(a);
		}
		circle_vtx_builds = true;
	}

	if (amin > amax) return;
	if (radius == 0.0f)
	{
		_Path.push_back(centre);
	}
	else
	{
		_Path.reserve(_Path.Size + (amax - amin + 1));
		for (int a = amin; a <= amax; a++)
		{
			const ImVec2& c = circle_vtx[a % circle_vtx_count];
			_Path.push_back(ImVec2(centre.x + c.x * radius, centre.y + c.y * radius));
		}
	}
}

void ImDrawList::PathArcTo(const ImVec2& centre, float radius, float amin, float amax, int num_segments)
{
	if (radius == 0.0f)
		_Path.push_back(centre);
	_Path.reserve(_Path.Size + (num_segments + 1));
	for (int i = 0; i <= num_segments; i++)
	{
		const float a = amin + ((float)i / (float)num_segments) * (amax - amin);
		_Path.push_back(ImVec2(centre.x + cosf(a) * radius, centre.y + sinf(a) * radius));
	}
}

static void PathBezierToCasteljau(ImVector<ImVec2>* path, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float tess_tol, int level)
{
	float dx = x4 - x1;
	float dy = y4 - y1;
	float d2 = ((x2 - x4) * dy - (y2 - y4) * dx);
	float d3 = ((x3 - x4) * dy - (y3 - y4) * dx);
	d2 = (d2 >= 0) ? d2 : -d2;
	d3 = (d3 >= 0) ? d3 : -d3;
	if ((d2 + d3) * (d2 + d3) < tess_tol * (dx*dx + dy*dy))
	{
		path->push_back(ImVec2(x4, y4));
	}
	else if (level < 10)
	{
		float x12 = (x1 + x2)*0.5f, y12 = (y1 + y2)*0.5f;
		float x23 = (x2 + x3)*0.5f, y23 = (y2 + y3)*0.5f;
		float x34 = (x3 + x4)*0.5f, y34 = (y3 + y4)*0.5f;
		float x123 = (x12 + x23)*0.5f, y123 = (y12 + y23)*0.5f;
		float x234 = (x23 + x34)*0.5f, y234 = (y23 + y34)*0.5f;
		float x1234 = (x123 + x234)*0.5f, y1234 = (y123 + y234)*0.5f;

		PathBezierToCasteljau(path, x1, y1, x12, y12, x123, y123, x1234, y1234, tess_tol, level + 1);
		PathBezierToCasteljau(path, x1234, y1234, x234, y234, x34, y34, x4, y4, tess_tol, level + 1);
	}
}

void ImDrawList::PathBezierCurveTo(const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, int num_segments)
{
	ImVec2 p1 = _Path.back();
	if (num_segments == 0)
	{
		// Auto-tessellated
		PathBezierToCasteljau(&_Path, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, GImGui->Style.CurveTessellationTol, 0);
	}
	else
	{
		float t_step = 1.0f / (float)num_segments;
		for (int i_step = 1; i_step <= num_segments; i_step++)
		{
			float t = t_step * i_step;
			float u = 1.0f - t;
			float w1 = u*u*u;
			float w2 = 3 * u*u*t;
			float w3 = 3 * u*t*t;
			float w4 = t*t*t;
			_Path.push_back(ImVec2(w1*p1.x + w2*p2.x + w3*p3.x + w4*p4.x, w1*p1.y + w2*p2.y + w3*p3.y + w4*p4.y));
		}
	}
}

void ImDrawList::PathRect(const ImVec2& a, const ImVec2& b, float rounding, int rounding_corners)
{
	float r = rounding;
	r = ImMin(r, fabsf(b.x - a.x) * (((rounding_corners&(1 | 2)) == (1 | 2)) || ((rounding_corners&(4 | 8)) == (4 | 8)) ? 0.5f : 1.0f) - 1.0f);
	r = ImMin(r, fabsf(b.y - a.y) * (((rounding_corners&(1 | 8)) == (1 | 8)) || ((rounding_corners&(2 | 4)) == (2 | 4)) ? 0.5f : 1.0f) - 1.0f);

	if (r <= 0.0f || rounding_corners == 0)
	{
		PathLineTo(a);
		PathLineTo(ImVec2(b.x, a.y));
		PathLineTo(b);
		PathLineTo(ImVec2(a.x, b.y));
	}
	else
	{
		const float r0 = (rounding_corners & 1) ? r : 0.0f;
		const float r1 = (rounding_corners & 2) ? r : 0.0f;
		const float r2 = (rounding_corners & 4) ? r : 0.0f;
		const float r3 = (rounding_corners & 8) ? r : 0.0f;
		PathArcToFast(ImVec2(a.x + r0, a.y + r0), r0, 6, 9);
		PathArcToFast(ImVec2(b.x - r1, a.y + r1), r1, 9, 12);
		PathArcToFast(ImVec2(b.x - r2, b.y - r2), r2, 0, 3);
		PathArcToFast(ImVec2(a.x + r3, b.y - r3), r3, 3, 6);
	}
}

void ImDrawList::AddLine(const ImVec2& a, const ImVec2& b, ImU32 col, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;
	PathLineTo(a + ImVec2(0.5f, 0.5f));
	PathLineTo(b + ImVec2(0.5f, 0.5f));
	PathStroke(col, false, thickness);
}

// a: upper-left, b: lower-right. we don't render 1 px sized rectangles properly.
void ImDrawList::AddRect(const ImVec2& a, const ImVec2& b, ImU32 col, float rounding, int rounding_corners_flags, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;
	PathRect(a + ImVec2(0.5f, 0.5f), b - ImVec2(0.5f, 0.5f), rounding, rounding_corners_flags);
	PathStroke(col, true, thickness);
}

void ImDrawList::AddRectFilled(const ImVec2& a, const ImVec2& b, ImU32 col, float rounding, int rounding_corners_flags)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;
	if (rounding > 0.0f)
	{
		PathRect(a, b, rounding, rounding_corners_flags);
		PathFillConvex(col);
	}
	else
	{
		PrimReserve(6, 4);
		PrimRect(a, b, col);
	}
}

void ImDrawList::AddRectFilledMultiColor(const ImVec2& a, const ImVec2& c, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left)
{
	if (((col_upr_left | col_upr_right | col_bot_right | col_bot_left) & IM_COL32_A_MASK) == 0)
		return;

	const ImVec2 uv = GImGui->FontTexUvWhitePixel;
	PrimReserve(6, 4);
	PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx)); PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx + 1)); PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx + 2));
	PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx)); PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx + 2)); PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx + 3));
	PrimWriteVtx(a, uv, col_upr_left);
	PrimWriteVtx(ImVec2(c.x, a.y), uv, col_upr_right);
	PrimWriteVtx(c, uv, col_bot_right);
	PrimWriteVtx(ImVec2(a.x, c.y), uv, col_bot_left);
}

void ImDrawList::AddQuad(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, ImU32 col, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	PathLineTo(a);
	PathLineTo(b);
	PathLineTo(c);
	PathLineTo(d);
	PathStroke(col, true, thickness);
}

void ImDrawList::AddQuadFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, ImU32 col)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	PathLineTo(a);
	PathLineTo(b);
	PathLineTo(c);
	PathLineTo(d);
	PathFillConvex(col);
}

void ImDrawList::AddTriangle(const ImVec2& a, const ImVec2& b, const ImVec2& c, ImU32 col, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	PathLineTo(a);
	PathLineTo(b);
	PathLineTo(c);
	PathStroke(col, true, thickness);
}

void ImDrawList::AddTriangleFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, ImU32 col)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	PathLineTo(a);
	PathLineTo(b);
	PathLineTo(c);
	PathFillConvex(col);
}

void ImDrawList::AddCircle(const ImVec2& centre, float radius, ImU32 col, int num_segments, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	const float a_max = IM_PI*2.0f * ((float)num_segments - 1.0f) / (float)num_segments;
	PathArcTo(centre, radius - 0.5f, 0.0f, a_max, num_segments);
	PathStroke(col, true, thickness);
}

void ImDrawList::AddCircleFilled(const ImVec2& centre, float radius, ImU32 col, int num_segments)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	const float a_max = IM_PI*2.0f * ((float)num_segments - 1.0f) / (float)num_segments;
	PathArcTo(centre, radius, 0.0f, a_max, num_segments);
	PathFillConvex(col);
}

void ImDrawList::AddBezierCurve(const ImVec2& pos0, const ImVec2& cp0, const ImVec2& cp1, const ImVec2& pos1, ImU32 col, float thickness, int num_segments)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	PathLineTo(pos0);
	PathBezierCurveTo(cp0, cp1, pos1, num_segments);
	PathStroke(col, false, thickness);
}

void ImDrawList::AddText(const ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end, float wrap_width, const ImVec4* cpu_fine_clip_rect)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	if (text_end == NULL)
		text_end = text_begin + strlen(text_begin);
	if (text_begin == text_end)
		return;

	// Note: This is one of the few instance of breaking the encapsulation of ImDrawList, as we pull this from ImGui state, but it is just SO useful.
	// Might just move Font/FontSize to ImDrawList?
	if (font == NULL)
		font = GImGui->Font;
	if (font_size == 0.0f)
		font_size = GImGui->FontSize;

	IM_ASSERT(font->ContainerAtlas->TexID == _TextureIdStack.back());  // Use high-level ImGui::PushFont() or low-level ImDrawList::PushTextureId() to change font.

	ImVec4 clip_rect = _ClipRectStack.back();
	if (cpu_fine_clip_rect)
	{
		clip_rect.x = ImMax(clip_rect.x, cpu_fine_clip_rect->x);
		clip_rect.y = ImMax(clip_rect.y, cpu_fine_clip_rect->y);
		clip_rect.z = ImMin(clip_rect.z, cpu_fine_clip_rect->z);
		clip_rect.w = ImMin(clip_rect.w, cpu_fine_clip_rect->w);
	}
	font->RenderText(this, font_size, pos, col, clip_rect, text_begin, text_end, wrap_width, cpu_fine_clip_rect != NULL);
}

void ImDrawList::AddText(const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end)
{
	AddText(GImGui->Font, GImGui->FontSize, pos, col, text_begin, text_end);
}

void ImDrawList::AddImage(ImTextureID user_texture_id, const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, ImU32 col)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	// FIXME-OPT: This is wasting draw calls.
	const bool push_texture_id = _TextureIdStack.empty() || user_texture_id != _TextureIdStack.back();
	if (push_texture_id)
		PushTextureID(user_texture_id);

	PrimReserve(6, 4);
	PrimRectUV(a, b, uv_a, uv_b, col);

	if (push_texture_id)
		PopTextureID();
}

void ImDrawList::AddImageQuad(ImTextureID user_texture_id, const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImVec2& uv_a, const ImVec2& uv_b, const ImVec2& uv_c, const ImVec2& uv_d, ImU32 col)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	const bool push_texture_id = _TextureIdStack.empty() || user_texture_id != _TextureIdStack.back();
	if (push_texture_id)
		PushTextureID(user_texture_id);

	PrimReserve(6, 4);
	PrimQuadUV(a, b, c, d, uv_a, uv_b, uv_c, uv_d, col);

	if (push_texture_id)
		PopTextureID();
}

//-----------------------------------------------------------------------------
// ImDrawData
//-----------------------------------------------------------------------------

// For backward compatibility: convert all buffers from indexed to de-indexed, in case you cannot render indexed. Note: this is slow and most likely a waste of resources. Always prefer indexed rendering!
void ImDrawData::DeIndexAllBuffers()
{
	ImVector<ImDrawVert> new_vtx_buffer;
	TotalVtxCount = TotalIdxCount = 0;
	for (int i = 0; i < CmdListsCount; i++)
	{
		ImDrawList* cmd_list = CmdLists[i];
		if (cmd_list->IdxBuffer.empty())
			continue;
		new_vtx_buffer.resize(cmd_list->IdxBuffer.Size);
		for (int j = 0; j < cmd_list->IdxBuffer.Size; j++)
			new_vtx_buffer[j] = cmd_list->VtxBuffer[cmd_list->IdxBuffer[j]];
		cmd_list->VtxBuffer.swap(new_vtx_buffer);
		cmd_list->IdxBuffer.resize(0);
		TotalVtxCount += cmd_list->VtxBuffer.Size;
	}
}

// Helper to scale the ClipRect field of each ImDrawCmd. Use if your final output buffer is at a different scale than ImGui expects, or if there is a difference between your window resolution and framebuffer resolution.
void ImDrawData::ScaleClipRects(const ImVec2& scale)
{
	for (int i = 0; i < CmdListsCount; i++)
	{
		ImDrawList* cmd_list = CmdLists[i];
		for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
		{
			ImDrawCmd* cmd = &cmd_list->CmdBuffer[cmd_i];
			cmd->ClipRect = ImVec4(cmd->ClipRect.x * scale.x, cmd->ClipRect.y * scale.y, cmd->ClipRect.z * scale.x, cmd->ClipRect.w * scale.y);
		}
	}
}

//-----------------------------------------------------------------------------
// ImFontAtlas
//-----------------------------------------------------------------------------

ImFontConfig::ImFontConfig()
{
	FontData = NULL;
	FontDataSize = 0;
	FontDataOwnedByAtlas = true;
	FontNo = 0;
	SizePixels = 0.0f;
	OversampleH = 3;
	OversampleV = 1;
	PixelSnapH = false;
	GlyphExtraSpacing = ImVec2(0.0f, 0.0f);
	GlyphRanges = NULL;
	MergeMode = false;
	MergeGlyphCenterV = false;
	DstFont = NULL;
	memset(Name, 0, sizeof(Name));
}

ImFontAtlas::ImFontAtlas()
{
	TexID = NULL;
	TexPixelsAlpha8 = NULL;
	TexPixelsRGBA32 = NULL;
	TexWidth = TexHeight = TexDesiredWidth = 0;
	TexUvWhitePixel = ImVec2(0, 0);
}

ImFontAtlas::~ImFontAtlas()
{
	Clear();
}

void    ImFontAtlas::ClearInputData()
{
	for (int i = 0; i < ConfigData.Size; i++)
		if (ConfigData[i].FontData && ConfigData[i].FontDataOwnedByAtlas)
		{
			ImGui::MemFree(ConfigData[i].FontData);
			ConfigData[i].FontData = NULL;
		}

	// When clearing this we lose access to the font name and other information used to build the font.
	for (int i = 0; i < Fonts.Size; i++)
		if (Fonts[i]->ConfigData >= ConfigData.Data && Fonts[i]->ConfigData < ConfigData.Data + ConfigData.Size)
		{
			Fonts[i]->ConfigData = NULL;
			Fonts[i]->ConfigDataCount = 0;
		}
	ConfigData.clear();
}

void    ImFontAtlas::ClearTexData()
{
	if (TexPixelsAlpha8)
		ImGui::MemFree(TexPixelsAlpha8);
	if (TexPixelsRGBA32)
		ImGui::MemFree(TexPixelsRGBA32);
	TexPixelsAlpha8 = NULL;
	TexPixelsRGBA32 = NULL;
}

void    ImFontAtlas::ClearFonts()
{
	for (int i = 0; i < Fonts.Size; i++)
	{
		Fonts[i]->~ImFont();
		ImGui::MemFree(Fonts[i]);
	}
	Fonts.clear();
}

void    ImFontAtlas::Clear()
{
	ClearInputData();
	ClearTexData();
	ClearFonts();
}

void    ImFontAtlas::GetTexDataAsAlpha8(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel)
{
	// Build atlas on demand
	if (TexPixelsAlpha8 == NULL)
	{
		if (ConfigData.empty())
			AddFontDefault();
		Build();
	}

	*out_pixels = TexPixelsAlpha8;
	if (out_width) *out_width = TexWidth;
	if (out_height) *out_height = TexHeight;
	if (out_bytes_per_pixel) *out_bytes_per_pixel = 1;
}

void    ImFontAtlas::GetTexDataAsRGBA32(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel)
{
	// Convert to RGBA32 format on demand
	// Although it is likely to be the most commonly used format, our font rendering is 1 channel / 8 bpp
	if (!TexPixelsRGBA32)
	{
		unsigned char* pixels;
		GetTexDataAsAlpha8(&pixels, NULL, NULL);
		TexPixelsRGBA32 = (unsigned int*)ImGui::MemAlloc((size_t)(TexWidth * TexHeight * 4));
		const unsigned char* src = pixels;
		unsigned int* dst = TexPixelsRGBA32;
		for (int n = TexWidth * TexHeight; n > 0; n--)
			*dst++ = IM_COL32(255, 255, 255, (unsigned int)(*src++));
	}

	*out_pixels = (unsigned char*)TexPixelsRGBA32;
	if (out_width) *out_width = TexWidth;
	if (out_height) *out_height = TexHeight;
	if (out_bytes_per_pixel) *out_bytes_per_pixel = 4;
}

ImFont* ImFontAtlas::AddFont(const ImFontConfig* font_cfg)
{
	IM_ASSERT(font_cfg->FontData != NULL && font_cfg->FontDataSize > 0);
	IM_ASSERT(font_cfg->SizePixels > 0.0f);

	// Create new font
	if (!font_cfg->MergeMode)
	{
		ImFont* font = (ImFont*)ImGui::MemAlloc(sizeof(ImFont));
		IM_PLACEMENT_NEW(font) ImFont();
		Fonts.push_back(font);
	}
	else
	{
		IM_ASSERT(!Fonts.empty()); // When using MergeMode make sure that a font has already been added before. You can use ImGui::AddFontDefault() to add the default imgui font.
	}

	ConfigData.push_back(*font_cfg);
	ImFontConfig& new_font_cfg = ConfigData.back();
	if (!new_font_cfg.DstFont)
		new_font_cfg.DstFont = Fonts.back();
	if (!new_font_cfg.FontDataOwnedByAtlas)
	{
		new_font_cfg.FontData = ImGui::MemAlloc(new_font_cfg.FontDataSize);
		new_font_cfg.FontDataOwnedByAtlas = true;
		memcpy(new_font_cfg.FontData, font_cfg->FontData, (size_t)new_font_cfg.FontDataSize);
	}

	// Invalidate texture
	ClearTexData();
	return new_font_cfg.DstFont;
}

// Default font TTF is compressed with stb_compress then base85 encoded (see extra_fonts/binary_to_compressed_c.cpp for encoder)
static unsigned int stb_decompress_length(unsigned char *input);
static unsigned int stb_decompress(unsigned char *output, unsigned char *i, unsigned int length);
static const char*  GetDefaultCompressedFontDataTTFBase85();
static unsigned int Decode85Byte(char c) { return c >= '\\' ? c - 36 : c - 35; }
static void         Decode85(const unsigned char* src, unsigned char* dst)
{
	while (*src)
	{
		unsigned int tmp = Decode85Byte(src[0]) + 85 * (Decode85Byte(src[1]) + 85 * (Decode85Byte(src[2]) + 85 * (Decode85Byte(src[3]) + 85 * Decode85Byte(src[4]))));
		dst[0] = ((tmp >> 0) & 0xFF); dst[1] = ((tmp >> 8) & 0xFF); dst[2] = ((tmp >> 16) & 0xFF); dst[3] = ((tmp >> 24) & 0xFF);   // We can't assume little-endianness.
		src += 5;
		dst += 4;
	}
}

// Load embedded ProggyClean.ttf at size 13, disable oversampling
ImFont* ImFontAtlas::AddFontDefault(const ImFontConfig* font_cfg_template)
{
	ImFontConfig font_cfg = font_cfg_template ? *font_cfg_template : ImFontConfig();
	if (!font_cfg_template)
	{
		font_cfg.OversampleH = font_cfg.OversampleV = 1;
		font_cfg.PixelSnapH = true;
	}
	if (font_cfg.Name[0] == '\0') strcpy(font_cfg.Name, "ProggyClean.ttf, 13px");

	const char* ttf_compressed_base85 = GetDefaultCompressedFontDataTTFBase85();
	ImFont* font = AddFontFromMemoryCompressedBase85TTF(ttf_compressed_base85, 13.0f, &font_cfg, GetGlyphRangesDefault());
	return font;
}

ImFont* ImFontAtlas::AddFontFromFileTTF(const char* filename, float size_pixels, const ImFontConfig* font_cfg_template, const ImWchar* glyph_ranges)
{
	int data_size = 0;
	void* data = ImFileLoadToMemory(filename, "rb", &data_size, 0);
	if (!data)
	{
		IM_ASSERT(0); // Could not load file.
		return NULL;
	}
	ImFontConfig font_cfg = font_cfg_template ? *font_cfg_template : ImFontConfig();
	if (font_cfg.Name[0] == '\0')
	{
		// Store a short copy of filename into into the font name for convenience
		const char* p;
		for (p = filename + strlen(filename); p > filename && p[-1] != '/' && p[-1] != '\\'; p--) {}
		snprintf(font_cfg.Name, IM_ARRAYSIZE(font_cfg.Name), "%s, %.0fpx", p, size_pixels);
	}
	return AddFontFromMemoryTTF(data, data_size, size_pixels, &font_cfg, glyph_ranges);
}

// NBM Transfer ownership of 'ttf_data' to ImFontAtlas, unless font_cfg_template->FontDataOwnedByAtlas == false. Owned TTF buffer will be deleted after Build().
ImFont* ImFontAtlas::AddFontFromMemoryTTF(void* ttf_data, int ttf_size, float size_pixels, const ImFontConfig* font_cfg_template, const ImWchar* glyph_ranges)
{
	ImFontConfig font_cfg = font_cfg_template ? *font_cfg_template : ImFontConfig();
	IM_ASSERT(font_cfg.FontData == NULL);
	font_cfg.FontData = ttf_data;
	font_cfg.FontDataSize = ttf_size;
	font_cfg.SizePixels = size_pixels;
	if (glyph_ranges)
		font_cfg.GlyphRanges = glyph_ranges;
	return AddFont(&font_cfg);
}

ImFont* ImFontAtlas::AddFontFromMemoryCompressedTTF(const void* compressed_ttf_data, int compressed_ttf_size, float size_pixels, const ImFontConfig* font_cfg_template, const ImWchar* glyph_ranges)
{
	const unsigned int buf_decompressed_size = stb_decompress_length((unsigned char*)compressed_ttf_data);
	unsigned char* buf_decompressed_data = (unsigned char *)ImGui::MemAlloc(buf_decompressed_size);
	stb_decompress(buf_decompressed_data, (unsigned char*)compressed_ttf_data, (unsigned int)compressed_ttf_size);

	ImFontConfig font_cfg = font_cfg_template ? *font_cfg_template : ImFontConfig();
	IM_ASSERT(font_cfg.FontData == NULL);
	font_cfg.FontDataOwnedByAtlas = true;
	return AddFontFromMemoryTTF(buf_decompressed_data, (int)buf_decompressed_size, size_pixels, &font_cfg, glyph_ranges);
}

ImFont* ImFontAtlas::AddFontFromMemoryCompressedBase85TTF(const char* compressed_ttf_data_base85, float size_pixels, const ImFontConfig* font_cfg, const ImWchar* glyph_ranges)
{
	int compressed_ttf_size = (((int)strlen(compressed_ttf_data_base85) + 4) / 5) * 4;
	void* compressed_ttf = ImGui::MemAlloc((size_t)compressed_ttf_size);
	Decode85((const unsigned char*)compressed_ttf_data_base85, (unsigned char*)compressed_ttf);
	ImFont* font = AddFontFromMemoryCompressedTTF(compressed_ttf, compressed_ttf_size, size_pixels, font_cfg, glyph_ranges);
	ImGui::MemFree(compressed_ttf);
	return font;
}

bool    ImFontAtlas::Build()
{
	IM_ASSERT(ConfigData.Size > 0);

	TexID = NULL;
	TexWidth = TexHeight = 0;
	TexUvWhitePixel = ImVec2(0, 0);
	ClearTexData();

	struct ImFontTempBuildData
	{
		stbtt_fontinfo      FontInfo;
		stbrp_rect*         Rects;
		stbtt_pack_range*   Ranges;
		int                 RangesCount;
	};
	ImFontTempBuildData* tmp_array = (ImFontTempBuildData*)ImGui::MemAlloc((size_t)ConfigData.Size * sizeof(ImFontTempBuildData));

	// Initialize font information early (so we can error without any cleanup) + count glyphs
	int total_glyph_count = 0;
	int total_glyph_range_count = 0;
	for (int input_i = 0; input_i < ConfigData.Size; input_i++)
	{
		ImFontConfig& cfg = ConfigData[input_i];
		ImFontTempBuildData& tmp = tmp_array[input_i];

		IM_ASSERT(cfg.DstFont && (!cfg.DstFont->IsLoaded() || cfg.DstFont->ContainerAtlas == this));
		const int font_offset = stbtt_GetFontOffsetForIndex((unsigned char*)cfg.FontData, cfg.FontNo);
		IM_ASSERT(font_offset >= 0);
		if (!stbtt_InitFont(&tmp.FontInfo, (unsigned char*)cfg.FontData, font_offset))
			return false;

		// Count glyphs
		if (!cfg.GlyphRanges)
			cfg.GlyphRanges = GetGlyphRangesDefault();
		for (const ImWchar* in_range = cfg.GlyphRanges; in_range[0] && in_range[1]; in_range += 2)
		{
			total_glyph_count += (in_range[1] - in_range[0]) + 1;
			total_glyph_range_count++;
		}
	}

	// Start packing. We need a known width for the skyline algorithm. Using a cheap heuristic here to decide of width. User can override TexDesiredWidth if they wish.
	// After packing is done, width shouldn't matter much, but some API/GPU have texture size limitations and increasing width can decrease height.
	TexWidth = (TexDesiredWidth > 0) ? TexDesiredWidth : (total_glyph_count > 4000) ? 4096 : (total_glyph_count > 2000) ? 2048 : (total_glyph_count > 1000) ? 1024 : 512;
	TexHeight = 0;
	const int max_tex_height = 1024 * 32;
	stbtt_pack_context spc;
	stbtt_PackBegin(&spc, NULL, TexWidth, max_tex_height, 0, 1, NULL);

	// Pack our extra data rectangles first, so it will be on the upper-left corner of our texture (UV will have small values).
	ImVector<stbrp_rect> extra_rects;
	RenderCustomTexData(0, &extra_rects);
	stbtt_PackSetOversampling(&spc, 1, 1);
	stbrp_pack_rects((stbrp_context*)spc.pack_info, &extra_rects[0], extra_rects.Size);
	for (int i = 0; i < extra_rects.Size; i++)
		if (extra_rects[i].was_packed)
			TexHeight = ImMax(TexHeight, extra_rects[i].y + extra_rects[i].h);

	// Allocate packing character data and flag packed characters buffer as non-packed (x0=y0=x1=y1=0)
	int buf_packedchars_n = 0, buf_rects_n = 0, buf_ranges_n = 0;
	stbtt_packedchar* buf_packedchars = (stbtt_packedchar*)ImGui::MemAlloc(total_glyph_count * sizeof(stbtt_packedchar));
	stbrp_rect* buf_rects = (stbrp_rect*)ImGui::MemAlloc(total_glyph_count * sizeof(stbrp_rect));
	stbtt_pack_range* buf_ranges = (stbtt_pack_range*)ImGui::MemAlloc(total_glyph_range_count * sizeof(stbtt_pack_range));
	memset(buf_packedchars, 0, total_glyph_count * sizeof(stbtt_packedchar));
	memset(buf_rects, 0, total_glyph_count * sizeof(stbrp_rect));              // Unnecessary but let's clear this for the sake of sanity.
	memset(buf_ranges, 0, total_glyph_range_count * sizeof(stbtt_pack_range));

	// First font pass: pack all glyphs (no rendering at this point, we are working with rectangles in an infinitely tall texture at this point)
	for (int input_i = 0; input_i < ConfigData.Size; input_i++)
	{
		ImFontConfig& cfg = ConfigData[input_i];
		ImFontTempBuildData& tmp = tmp_array[input_i];

		// Setup ranges
		int glyph_count = 0;
		int glyph_ranges_count = 0;
		for (const ImWchar* in_range = cfg.GlyphRanges; in_range[0] && in_range[1]; in_range += 2)
		{
			glyph_count += (in_range[1] - in_range[0]) + 1;
			glyph_ranges_count++;
		}
		tmp.Ranges = buf_ranges + buf_ranges_n;
		tmp.RangesCount = glyph_ranges_count;
		buf_ranges_n += glyph_ranges_count;
		for (int i = 0; i < glyph_ranges_count; i++)
		{
			const ImWchar* in_range = &cfg.GlyphRanges[i * 2];
			stbtt_pack_range& range = tmp.Ranges[i];
			range.font_size = cfg.SizePixels;
			range.first_unicode_codepoint_in_range = in_range[0];
			range.num_chars = (in_range[1] - in_range[0]) + 1;
			range.chardata_for_range = buf_packedchars + buf_packedchars_n;
			buf_packedchars_n += range.num_chars;
		}

		// Pack
		tmp.Rects = buf_rects + buf_rects_n;
		buf_rects_n += glyph_count;
		stbtt_PackSetOversampling(&spc, cfg.OversampleH, cfg.OversampleV);
		int n = stbtt_PackFontRangesGatherRects(&spc, &tmp.FontInfo, tmp.Ranges, tmp.RangesCount, tmp.Rects);
		stbrp_pack_rects((stbrp_context*)spc.pack_info, tmp.Rects, n);

		// Extend texture height
		for (int i = 0; i < n; i++)
			if (tmp.Rects[i].was_packed)
				TexHeight = ImMax(TexHeight, tmp.Rects[i].y + tmp.Rects[i].h);
	}
	IM_ASSERT(buf_rects_n == total_glyph_count);
	IM_ASSERT(buf_packedchars_n == total_glyph_count);
	IM_ASSERT(buf_ranges_n == total_glyph_range_count);

	// Create texture
	TexHeight = ImUpperPowerOfTwo(TexHeight);
	TexPixelsAlpha8 = (unsigned char*)ImGui::MemAlloc(TexWidth * TexHeight);
	memset(TexPixelsAlpha8, 0, TexWidth * TexHeight);
	spc.pixels = TexPixelsAlpha8;
	spc.height = TexHeight;

	// Second pass: render characters
	for (int input_i = 0; input_i < ConfigData.Size; input_i++)
	{
		ImFontConfig& cfg = ConfigData[input_i];
		ImFontTempBuildData& tmp = tmp_array[input_i];
		stbtt_PackSetOversampling(&spc, cfg.OversampleH, cfg.OversampleV);
		stbtt_PackFontRangesRenderIntoRects(&spc, &tmp.FontInfo, tmp.Ranges, tmp.RangesCount, tmp.Rects);
		tmp.Rects = NULL;
	}

	// End packing
	stbtt_PackEnd(&spc);
	ImGui::MemFree(buf_rects);
	buf_rects = NULL;

	// Third pass: setup ImFont and glyphs for runtime
	for (int input_i = 0; input_i < ConfigData.Size; input_i++)
	{
		ImFontConfig& cfg = ConfigData[input_i];
		ImFontTempBuildData& tmp = tmp_array[input_i];
		ImFont* dst_font = cfg.DstFont; // We can have multiple input fonts writing into a same destination font (when using MergeMode=true)

		float font_scale = stbtt_ScaleForPixelHeight(&tmp.FontInfo, cfg.SizePixels);
		int unscaled_ascent, unscaled_descent, unscaled_line_gap;
		stbtt_GetFontVMetrics(&tmp.FontInfo, &unscaled_ascent, &unscaled_descent, &unscaled_line_gap);

		float ascent = unscaled_ascent * font_scale;
		float descent = unscaled_descent * font_scale;
		if (!cfg.MergeMode)
		{
			dst_font->ContainerAtlas = this;
			dst_font->ConfigData = &cfg;
			dst_font->ConfigDataCount = 0;
			dst_font->FontSize = cfg.SizePixels;
			dst_font->Ascent = ascent;
			dst_font->Descent = descent;
			dst_font->Glyphs.resize(0);
			dst_font->MetricsTotalSurface = 0;
		}
		dst_font->ConfigDataCount++;
		float off_y = (cfg.MergeMode && cfg.MergeGlyphCenterV) ? (ascent - dst_font->Ascent) * 0.5f : 0.0f;

		dst_font->FallbackGlyph = NULL; // Always clear fallback so FindGlyph can return NULL. It will be set again in BuildLookupTable()
		for (int i = 0; i < tmp.RangesCount; i++)
		{
			stbtt_pack_range& range = tmp.Ranges[i];
			for (int char_idx = 0; char_idx < range.num_chars; char_idx += 1)
			{
				const stbtt_packedchar& pc = range.chardata_for_range[char_idx];
				if (!pc.x0 && !pc.x1 && !pc.y0 && !pc.y1)
					continue;

				const int codepoint = range.first_unicode_codepoint_in_range + char_idx;
				if (cfg.MergeMode && dst_font->FindGlyph((unsigned short)codepoint))
					continue;

				stbtt_aligned_quad q;
				float dummy_x = 0.0f, dummy_y = 0.0f;
				stbtt_GetPackedQuad(range.chardata_for_range, TexWidth, TexHeight, char_idx, &dummy_x, &dummy_y, &q, 0);

				dst_font->Glyphs.resize(dst_font->Glyphs.Size + 1);
				ImFont::Glyph& glyph = dst_font->Glyphs.back();
				glyph.Codepoint = (ImWchar)codepoint;
				glyph.X0 = q.x0; glyph.Y0 = q.y0; glyph.X1 = q.x1; glyph.Y1 = q.y1;
				glyph.U0 = q.s0; glyph.V0 = q.t0; glyph.U1 = q.s1; glyph.V1 = q.t1;
				glyph.Y0 += (float)(int)(dst_font->Ascent + off_y + 0.5f);
				glyph.Y1 += (float)(int)(dst_font->Ascent + off_y + 0.5f);
				glyph.XAdvance = (pc.xadvance + cfg.GlyphExtraSpacing.x);  // Bake spacing into XAdvance
				if (cfg.PixelSnapH)
					glyph.XAdvance = (float)(int)(glyph.XAdvance + 0.5f);
				dst_font->MetricsTotalSurface += (int)((glyph.U1 - glyph.U0) * TexWidth + 1.99f) * (int)((glyph.V1 - glyph.V0) * TexHeight + 1.99f); // +1 to account for average padding, +0.99 to round
			}
		}
		cfg.DstFont->BuildLookupTable();
	}

	// Cleanup temporaries
	ImGui::MemFree(buf_packedchars);
	ImGui::MemFree(buf_ranges);
	ImGui::MemFree(tmp_array);

	// Render into our custom data block
	RenderCustomTexData(1, &extra_rects);

	return true;
}

void ImFontAtlas::RenderCustomTexData(int pass, void* p_rects)
{
	// A work of art lies ahead! (. = white layer, X = black layer, others are blank)
	// The white texels on the top left are the ones we'll use everywhere in ImGui to render filled shapes.
	const int TEX_DATA_W = 90;
	const int TEX_DATA_H = 27;
	const char texture_data[TEX_DATA_W*TEX_DATA_H + 1] =
	{
		"..-         -XXXXXXX-    X    -           X           -XXXXXXX          -          XXXXXXX"
		"..-         -X.....X-   X.X   -          X.X          -X.....X          -          X.....X"
		"---         -XXX.XXX-  X...X  -         X...X         -X....X           -           X....X"
		"X           -  X.X  - X.....X -        X.....X        -X...X            -            X...X"
		"XX          -  X.X  -X.......X-       X.......X       -X..X.X           -           X.X..X"
		"X.X         -  X.X  -XXXX.XXXX-       XXXX.XXXX       -X.X X.X          -          X.X X.X"
		"X..X        -  X.X  -   X.X   -          X.X          -XX   X.X         -         X.X   XX"
		"X...X       -  X.X  -   X.X   -    XX    X.X    XX    -      X.X        -        X.X      "
		"X....X      -  X.X  -   X.X   -   X.X    X.X    X.X   -       X.X       -       X.X       "
		"X.....X     -  X.X  -   X.X   -  X..X    X.X    X..X  -        X.X      -      X.X        "
		"X......X    -  X.X  -   X.X   - X...XXXXXX.XXXXXX...X -         X.X   XX-XX   X.X         "
		"X.......X   -  X.X  -   X.X   -X.....................X-          X.X X.X-X.X X.X          "
		"X........X  -  X.X  -   X.X   - X...XXXXXX.XXXXXX...X -           X.X..X-X..X.X           "
		"X.........X -XXX.XXX-   X.X   -  X..X    X.X    X..X  -            X...X-X...X            "
		"X..........X-X.....X-   X.X   -   X.X    X.X    X.X   -           X....X-X....X           "
		"X......XXXXX-XXXXXXX-   X.X   -    XX    X.X    XX    -          X.....X-X.....X          "
		"X...X..X    ---------   X.X   -          X.X          -          XXXXXXX-XXXXXXX          "
		"X..X X..X   -       -XXXX.XXXX-       XXXX.XXXX       ------------------------------------"
		"X.X  X..X   -       -X.......X-       X.......X       -    XX           XX    -           "
		"XX    X..X  -       - X.....X -        X.....X        -   X.X           X.X   -           "
		"      X..X          -  X...X  -         X...X         -  X..X           X..X  -           "
		"       XX           -   X.X   -          X.X          - X...XXXXXXXXXXXXX...X -           "
		"------------        -    X    -           X           -X.....................X-           "
		"                    ----------------------------------- X...XXXXXXXXXXXXX...X -           "
		"                                                      -  X..X           X..X  -           "
		"                                                      -   X.X           X.X   -           "
		"                                                      -    XX           XX    -           "
	};

	ImVector<stbrp_rect>& rects = *(ImVector<stbrp_rect>*)p_rects;
	if (pass == 0)
	{
		// Request rectangles
		stbrp_rect r;
		memset(&r, 0, sizeof(r));
		r.w = (TEX_DATA_W * 2) + 1;
		r.h = TEX_DATA_H + 1;
		rects.push_back(r);
	}
	else if (pass == 1)
	{
		// Render/copy pixels
		const stbrp_rect& r = rects[0];
		for (int y = 0, n = 0; y < TEX_DATA_H; y++)
			for (int x = 0; x < TEX_DATA_W; x++, n++)
			{
				const int offset0 = (int)(r.x + x) + (int)(r.y + y) * TexWidth;
				const int offset1 = offset0 + 1 + TEX_DATA_W;
				TexPixelsAlpha8[offset0] = texture_data[n] == '.' ? 0xFF : 0x00;
				TexPixelsAlpha8[offset1] = texture_data[n] == 'X' ? 0xFF : 0x00;
			}
		const ImVec2 tex_uv_scale(1.0f / TexWidth, 1.0f / TexHeight);
		TexUvWhitePixel = ImVec2((r.x + 0.5f) * tex_uv_scale.x, (r.y + 0.5f) * tex_uv_scale.y);

		// Setup mouse cursors
		const ImVec2 cursor_datas[ImGuiMouseCursor_Count_][3] =
		{
			// Pos ........ Size ......... Offset ......
			{ ImVec2(0,3),  ImVec2(12,19), ImVec2(0, 0) }, // ImGuiMouseCursor_Arrow
			{ ImVec2(13,0), ImVec2(7,16),  ImVec2(4, 8) }, // ImGuiMouseCursor_TextInput
			{ ImVec2(31,0), ImVec2(23,23), ImVec2(11,11) }, // ImGuiMouseCursor_Move
			{ ImVec2(21,0), ImVec2(9,23), ImVec2(5,11) }, // ImGuiMouseCursor_ResizeNS
			{ ImVec2(55,18),ImVec2(23, 9), ImVec2(11, 5) }, // ImGuiMouseCursor_ResizeEW
			{ ImVec2(73,0), ImVec2(17,17), ImVec2(9, 9) }, // ImGuiMouseCursor_ResizeNESW
			{ ImVec2(55,0), ImVec2(17,17), ImVec2(9, 9) }, // ImGuiMouseCursor_ResizeNWSE
		};

		for (int type = 0; type < ImGuiMouseCursor_Count_; type++)
		{
			ImGuiMouseCursorData& cursor_data = GImGui->MouseCursorData[type];
			ImVec2 pos = cursor_datas[type][0] + ImVec2((float)r.x, (float)r.y);
			const ImVec2 size = cursor_datas[type][1];
			cursor_data.Type = type;
			cursor_data.Size = size;
			cursor_data.HotOffset = cursor_datas[type][2];
			cursor_data.TexUvMin[0] = (pos)* tex_uv_scale;
			cursor_data.TexUvMax[0] = (pos + size) * tex_uv_scale;
			pos.x += TEX_DATA_W + 1;
			cursor_data.TexUvMin[1] = (pos)* tex_uv_scale;
			cursor_data.TexUvMax[1] = (pos + size) * tex_uv_scale;
		}
	}
}

// Retrieve list of range (2 int per range, values are inclusive)
const ImWchar*   ImFontAtlas::GetGlyphRangesDefault()
{
	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0,
	};
	return &ranges[0];
}

const ImWchar*  ImFontAtlas::GetGlyphRangesKorean()
{
	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x3131, 0x3163, // Korean alphabets
		0xAC00, 0xD79D, // Korean characters
		0,
	};
	return &ranges[0];
}

const ImWchar*  ImFontAtlas::GetGlyphRangesChinese()
{
	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x3000, 0x30FF, // Punctuations, Hiragana, Katakana
		0x31F0, 0x31FF, // Katakana Phonetic Extensions
		0xFF00, 0xFFEF, // Half-width characters
		0x4e00, 0x9FAF, // CJK Ideograms
		0,
	};
	return &ranges[0];
}

const ImWchar*  ImFontAtlas::GetGlyphRangesJapanese()
{
	// Store the 1946 ideograms code points as successive offsets from the initial unicode codepoint 0x4E00. Each offset has an implicit +1.
	// This encoding helps us reduce the source code size.
	static const short offsets_from_0x4E00[] =
	{
		-1,0,1,3,0,0,0,0,1,0,5,1,1,0,7,4,6,10,0,1,9,9,7,1,3,19,1,10,7,1,0,1,0,5,1,0,6,4,2,6,0,0,12,6,8,0,3,5,0,1,0,9,0,0,8,1,1,3,4,5,13,0,0,8,2,17,
		4,3,1,1,9,6,0,0,0,2,1,3,2,22,1,9,11,1,13,1,3,12,0,5,9,2,0,6,12,5,3,12,4,1,2,16,1,1,4,6,5,3,0,6,13,15,5,12,8,14,0,0,6,15,3,6,0,18,8,1,6,14,1,
		5,4,12,24,3,13,12,10,24,0,0,0,1,0,1,1,2,9,10,2,2,0,0,3,3,1,0,3,8,0,3,2,4,4,1,6,11,10,14,6,15,3,4,15,1,0,0,5,2,2,0,0,1,6,5,5,6,0,3,6,5,0,0,1,0,
		11,2,2,8,4,7,0,10,0,1,2,17,19,3,0,2,5,0,6,2,4,4,6,1,1,11,2,0,3,1,2,1,2,10,7,6,3,16,0,8,24,0,0,3,1,1,3,0,1,6,0,0,0,2,0,1,5,15,0,1,0,0,2,11,19,
		1,4,19,7,6,5,1,0,0,0,0,5,1,0,1,9,0,0,5,0,2,0,1,0,3,0,11,3,0,2,0,0,0,0,0,9,3,6,4,12,0,14,0,0,29,10,8,0,14,37,13,0,31,16,19,0,8,30,1,20,8,3,48,
		21,1,0,12,0,10,44,34,42,54,11,18,82,0,2,1,2,12,1,0,6,2,17,2,12,7,0,7,17,4,2,6,24,23,8,23,39,2,16,23,1,0,5,1,2,15,14,5,6,2,11,0,8,6,2,2,2,14,
		20,4,15,3,4,11,10,10,2,5,2,1,30,2,1,0,0,22,5,5,0,3,1,5,4,1,0,0,2,2,21,1,5,1,2,16,2,1,3,4,0,8,4,0,0,5,14,11,2,16,1,13,1,7,0,22,15,3,1,22,7,14,
		22,19,11,24,18,46,10,20,64,45,3,2,0,4,5,0,1,4,25,1,0,0,2,10,0,0,0,1,0,1,2,0,0,9,1,2,0,0,0,2,5,2,1,1,5,5,8,1,1,1,5,1,4,9,1,3,0,1,0,1,1,2,0,0,
		2,0,1,8,22,8,1,0,0,0,0,4,2,1,0,9,8,5,0,9,1,30,24,2,6,4,39,0,14,5,16,6,26,179,0,2,1,1,0,0,0,5,2,9,6,0,2,5,16,7,5,1,1,0,2,4,4,7,15,13,14,0,0,
		3,0,1,0,0,0,2,1,6,4,5,1,4,9,0,3,1,8,0,0,10,5,0,43,0,2,6,8,4,0,2,0,0,9,6,0,9,3,1,6,20,14,6,1,4,0,7,2,3,0,2,0,5,0,3,1,0,3,9,7,0,3,4,0,4,9,1,6,0,
		9,0,0,2,3,10,9,28,3,6,2,4,1,2,32,4,1,18,2,0,3,1,5,30,10,0,2,2,2,0,7,9,8,11,10,11,7,2,13,7,5,10,0,3,40,2,0,1,6,12,0,4,5,1,5,11,11,21,4,8,3,7,
		8,8,33,5,23,0,0,19,8,8,2,3,0,6,1,1,1,5,1,27,4,2,5,0,3,5,6,3,1,0,3,1,12,5,3,3,2,0,7,7,2,1,0,4,0,1,1,2,0,10,10,6,2,5,9,7,5,15,15,21,6,11,5,20,
		4,3,5,5,2,5,0,2,1,0,1,7,28,0,9,0,5,12,5,5,18,30,0,12,3,3,21,16,25,32,9,3,14,11,24,5,66,9,1,2,0,5,9,1,5,1,8,0,8,3,3,0,1,15,1,4,8,1,2,7,0,7,2,
		8,3,7,5,3,7,10,2,1,0,0,2,25,0,6,4,0,10,0,4,2,4,1,12,5,38,4,0,4,1,10,5,9,4,0,14,4,2,5,18,20,21,1,3,0,5,0,7,0,3,7,1,3,1,1,8,1,0,0,0,3,2,5,2,11,
		6,0,13,1,3,9,1,12,0,16,6,2,1,0,2,1,12,6,13,11,2,0,28,1,7,8,14,13,8,13,0,2,0,5,4,8,10,2,37,42,19,6,6,7,4,14,11,18,14,80,7,6,0,4,72,12,36,27,
		7,7,0,14,17,19,164,27,0,5,10,7,3,13,6,14,0,2,2,5,3,0,6,13,0,0,10,29,0,4,0,3,13,0,3,1,6,51,1,5,28,2,0,8,0,20,2,4,0,25,2,10,13,10,0,16,4,0,1,0,
		2,1,7,0,1,8,11,0,0,1,2,7,2,23,11,6,6,4,16,2,2,2,0,22,9,3,3,5,2,0,15,16,21,2,9,20,15,15,5,3,9,1,0,0,1,7,7,5,4,2,2,2,38,24,14,0,0,15,5,6,24,14,
		5,5,11,0,21,12,0,3,8,4,11,1,8,0,11,27,7,2,4,9,21,59,0,1,39,3,60,62,3,0,12,11,0,3,30,11,0,13,88,4,15,5,28,13,1,4,48,17,17,4,28,32,46,0,16,0,
		18,11,1,8,6,38,11,2,6,11,38,2,0,45,3,11,2,7,8,4,30,14,17,2,1,1,65,18,12,16,4,2,45,123,12,56,33,1,4,3,4,7,0,0,0,3,2,0,16,4,2,4,2,0,7,4,5,2,26,
		2,25,6,11,6,1,16,2,6,17,77,15,3,35,0,1,0,5,1,0,38,16,6,3,12,3,3,3,0,9,3,1,3,5,2,9,0,18,0,25,1,3,32,1,72,46,6,2,7,1,3,14,17,0,28,1,40,13,0,20,
		15,40,6,38,24,12,43,1,1,9,0,12,6,0,6,2,4,19,3,7,1,48,0,9,5,0,5,6,9,6,10,15,2,11,19,3,9,2,0,1,10,1,27,8,1,3,6,1,14,0,26,0,27,16,3,4,9,6,2,23,
		9,10,5,25,2,1,6,1,1,48,15,9,15,14,3,4,26,60,29,13,37,21,1,6,4,0,2,11,22,23,16,16,2,2,1,3,0,5,1,6,4,0,0,4,0,0,8,3,0,2,5,0,7,1,7,3,13,2,4,10,
		3,0,2,31,0,18,3,0,12,10,4,1,0,7,5,7,0,5,4,12,2,22,10,4,2,15,2,8,9,0,23,2,197,51,3,1,1,4,13,4,3,21,4,19,3,10,5,40,0,4,1,1,10,4,1,27,34,7,21,
		2,17,2,9,6,4,2,3,0,4,2,7,8,2,5,1,15,21,3,4,4,2,2,17,22,1,5,22,4,26,7,0,32,1,11,42,15,4,1,2,5,0,19,3,1,8,6,0,10,1,9,2,13,30,8,2,24,17,19,1,4,
		4,25,13,0,10,16,11,39,18,8,5,30,82,1,6,8,18,77,11,13,20,75,11,112,78,33,3,0,0,60,17,84,9,1,1,12,30,10,49,5,32,158,178,5,5,6,3,3,1,3,1,4,7,6,
		19,31,21,0,2,9,5,6,27,4,9,8,1,76,18,12,1,4,0,3,3,6,3,12,2,8,30,16,2,25,1,5,5,4,3,0,6,10,2,3,1,0,5,1,19,3,0,8,1,5,2,6,0,0,0,19,1,2,0,5,1,2,5,
		1,3,7,0,4,12,7,3,10,22,0,9,5,1,0,2,20,1,1,3,23,30,3,9,9,1,4,191,14,3,15,6,8,50,0,1,0,0,4,0,0,1,0,2,4,2,0,2,3,0,2,0,2,2,8,7,0,1,1,1,3,3,17,11,
		91,1,9,3,2,13,4,24,15,41,3,13,3,1,20,4,125,29,30,1,0,4,12,2,21,4,5,5,19,11,0,13,11,86,2,18,0,7,1,8,8,2,2,22,1,2,6,5,2,0,1,2,8,0,2,0,5,2,1,0,
		2,10,2,0,5,9,2,1,2,0,1,0,4,0,0,10,2,5,3,0,6,1,0,1,4,4,33,3,13,17,3,18,6,4,7,1,5,78,0,4,1,13,7,1,8,1,0,35,27,15,3,0,0,0,1,11,5,41,38,15,22,6,
		14,14,2,1,11,6,20,63,5,8,27,7,11,2,2,40,58,23,50,54,56,293,8,8,1,5,1,14,0,1,12,37,89,8,8,8,2,10,6,0,0,0,4,5,2,1,0,1,1,2,7,0,3,3,0,4,6,0,3,2,
		19,3,8,0,0,0,4,4,16,0,4,1,5,1,3,0,3,4,6,2,17,10,10,31,6,4,3,6,10,126,7,3,2,2,0,9,0,0,5,20,13,0,15,0,6,0,2,5,8,64,50,3,2,12,2,9,0,0,11,8,20,
		109,2,18,23,0,0,9,61,3,0,28,41,77,27,19,17,81,5,2,14,5,83,57,252,14,154,263,14,20,8,13,6,57,39,38,
	};
	static ImWchar base_ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x3000, 0x30FF, // Punctuations, Hiragana, Katakana
		0x31F0, 0x31FF, // Katakana Phonetic Extensions
		0xFF00, 0xFFEF, // Half-width characters
	};
	static bool full_ranges_unpacked = false;
	static ImWchar full_ranges[IM_ARRAYSIZE(base_ranges) + IM_ARRAYSIZE(offsets_from_0x4E00) * 2 + 1];
	if (!full_ranges_unpacked)
	{
		// Unpack
		int codepoint = 0x4e00;
		memcpy(full_ranges, base_ranges, sizeof(base_ranges));
		ImWchar* dst = full_ranges + IM_ARRAYSIZE(base_ranges);;
		for (int n = 0; n < IM_ARRAYSIZE(offsets_from_0x4E00); n++, dst += 2)
			dst[0] = dst[1] = (ImWchar)(codepoint += (offsets_from_0x4E00[n] + 1));
		dst[0] = 0;
		full_ranges_unpacked = true;
	}
	return &full_ranges[0];
}

const ImWchar*  ImFontAtlas::GetGlyphRangesCyrillic()
{
	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0,
	};
	return &ranges[0];
}

const ImWchar*  ImFontAtlas::GetGlyphRangesThai()
{
	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin
		0x0E00, 0x0E7F, // Thai
		0,
	};
	return &ranges[0];
}

//-----------------------------------------------------------------------------
// ImFont
//-----------------------------------------------------------------------------

ImFont::ImFont()
{
	Scale = 1.0f;
	FallbackChar = (ImWchar)'?';
	Clear();
}

ImFont::~ImFont()
{
	// Invalidate active font so that the user gets a clear crash instead of a dangling pointer.
	// If you want to delete fonts you need to do it between Render() and NewFrame().
	// FIXME-CLEANUP
	/*
	ImGuiContext& g = *GImGui;
	if (g.Font == this)
	g.Font = NULL;
	*/
	Clear();
}

void    ImFont::Clear()
{
	FontSize = 0.0f;
	DisplayOffset = ImVec2(0.0f, 1.0f);
	Glyphs.clear();
	IndexXAdvance.clear();
	IndexLookup.clear();
	FallbackGlyph = NULL;
	FallbackXAdvance = 0.0f;
	ConfigDataCount = 0;
	ConfigData = NULL;
	ContainerAtlas = NULL;
	Ascent = Descent = 0.0f;
	MetricsTotalSurface = 0;
}

void ImFont::BuildLookupTable()
{
	int max_codepoint = 0;
	for (int i = 0; i != Glyphs.Size; i++)
		max_codepoint = ImMax(max_codepoint, (int)Glyphs[i].Codepoint);

	IM_ASSERT(Glyphs.Size < 0xFFFF); // -1 is reserved
	IndexXAdvance.clear();
	IndexLookup.clear();
	GrowIndex(max_codepoint + 1);
	for (int i = 0; i < Glyphs.Size; i++)
	{
		int codepoint = (int)Glyphs[i].Codepoint;
		IndexXAdvance[codepoint] = Glyphs[i].XAdvance;
		IndexLookup[codepoint] = (unsigned short)i;
	}

	// Create a glyph to handle TAB
	// FIXME: Needs proper TAB handling but it needs to be contextualized (or we could arbitrary say that each string starts at "column 0" ?)
	if (FindGlyph((unsigned short)' '))
	{
		if (Glyphs.back().Codepoint != '\t')   // So we can call this function multiple times
			Glyphs.resize(Glyphs.Size + 1);
		ImFont::Glyph& tab_glyph = Glyphs.back();
		tab_glyph = *FindGlyph((unsigned short)' ');
		tab_glyph.Codepoint = '\t';
		tab_glyph.XAdvance *= 4;
		IndexXAdvance[(int)tab_glyph.Codepoint] = (float)tab_glyph.XAdvance;
		IndexLookup[(int)tab_glyph.Codepoint] = (unsigned short)(Glyphs.Size - 1);
	}

	FallbackGlyph = NULL;
	FallbackGlyph = FindGlyph(FallbackChar);
	FallbackXAdvance = FallbackGlyph ? FallbackGlyph->XAdvance : 0.0f;
	for (int i = 0; i < max_codepoint + 1; i++)
		if (IndexXAdvance[i] < 0.0f)
			IndexXAdvance[i] = FallbackXAdvance;
}

void ImFont::SetFallbackChar(ImWchar c)
{
	FallbackChar = c;
	BuildLookupTable();
}

void ImFont::GrowIndex(int new_size)
{
	IM_ASSERT(IndexXAdvance.Size == IndexLookup.Size);
	int old_size = IndexLookup.Size;
	if (new_size <= old_size)
		return;
	IndexXAdvance.resize(new_size);
	IndexLookup.resize(new_size);
	for (int i = old_size; i < new_size; i++)
	{
		IndexXAdvance[i] = -1.0f;
		IndexLookup[i] = (unsigned short)-1;
	}
}

void ImFont::AddRemapChar(ImWchar dst, ImWchar src, bool overwrite_dst)
{
	IM_ASSERT(IndexLookup.Size > 0);    // Currently this can only be called AFTER the font has been built, aka after calling ImFontAtlas::GetTexDataAs*() function.
	int index_size = IndexLookup.Size;

	if (dst < index_size && IndexLookup.Data[dst] == (unsigned short)-1 && !overwrite_dst) // 'dst' already exists
		return;
	if (src >= index_size && dst >= index_size) // both 'dst' and 'src' don't exist -> no-op
		return;

	GrowIndex(dst + 1);
	IndexLookup[dst] = (src < index_size) ? IndexLookup.Data[src] : (unsigned short)-1;
	IndexXAdvance[dst] = (src < index_size) ? IndexXAdvance.Data[src] : 1.0f;
}

const ImFont::Glyph* ImFont::FindGlyph(unsigned short c) const
{
	if (c < IndexLookup.Size)
	{
		const unsigned short i = IndexLookup[c];
		if (i != (unsigned short)-1)
			return &Glyphs.Data[i];
	}
	return FallbackGlyph;
}

const char* ImFont::CalcWordWrapPositionA(float scale, const char* text, const char* text_end, float wrap_width) const
{
	// Simple word-wrapping for English, not full-featured. Please submit failing cases!
	// FIXME: Much possible improvements (don't cut things like "word !", "word!!!" but cut within "word,,,,", more sensible support for punctuations, support for Unicode punctuations, etc.)

	// For references, possible wrap point marked with ^
	//  "aaa bbb, ccc,ddd. eee   fff. ggg!"
	//      ^    ^    ^   ^   ^__    ^    ^

	// List of hardcoded separators: .,;!?'"

	// Skip extra blanks after a line returns (that includes not counting them in width computation)
	// e.g. "Hello    world" --> "Hello" "World"

	// Cut words that cannot possibly fit within one line.
	// e.g.: "The tropical fish" with ~5 characters worth of width --> "The tr" "opical" "fish"

	float line_width = 0.0f;
	float word_width = 0.0f;
	float blank_width = 0.0f;

	const char* word_end = text;
	const char* prev_word_end = NULL;
	bool inside_word = true;

	const char* s = text;
	while (s < text_end)
	{
		unsigned int c = (unsigned int)*s;
		const char* next_s;
		if (c < 0x80)
			next_s = s + 1;
		else
			next_s = s + ImTextCharFromUtf8(&c, s, text_end);
		if (c == 0)
			break;

		if (c < 32)
		{
			if (c == '\n')
			{
				line_width = word_width = blank_width = 0.0f;
				inside_word = true;
				s = next_s;
				continue;
			}
			if (c == '\r')
			{
				s = next_s;
				continue;
			}
		}

		const float char_width = ((int)c < IndexXAdvance.Size ? IndexXAdvance[(int)c] : FallbackXAdvance) * scale;
		if (ImCharIsSpace(c))
		{
			if (inside_word)
			{
				line_width += blank_width;
				blank_width = 0.0f;
				word_end = s;
			}
			blank_width += char_width;
			inside_word = false;
		}
		else
		{
			word_width += char_width;
			if (inside_word)
			{
				word_end = next_s;
			}
			else
			{
				prev_word_end = word_end;
				line_width += word_width + blank_width;
				word_width = blank_width = 0.0f;
			}

			// Allow wrapping after punctuation.
			inside_word = !(c == '.' || c == ',' || c == ';' || c == '!' || c == '?' || c == '\"');
		}

		// We ignore blank width at the end of the line (they can be skipped)
		if (line_width + word_width >= wrap_width)
		{
			// Words that cannot possibly fit within an entire line will be cut anywhere.
			if (word_width < wrap_width)
				s = prev_word_end ? prev_word_end : word_end;
			break;
		}

		s = next_s;
	}

	return s;
}

ImVec2 ImFont::CalcTextSizeA(float size, float max_width, float wrap_width, const char* text_begin, const char* text_end, const char** remaining) const
{
	if (!text_end)
		text_end = text_begin + strlen(text_begin); // FIXME-OPT: Need to avoid this.

	const float line_height = size;
	const float scale = size / FontSize;

	ImVec2 text_size = ImVec2(0, 0);
	float line_width = 0.0f;

	const bool word_wrap_enabled = (wrap_width > 0.0f);
	const char* word_wrap_eol = NULL;

	const char* s = text_begin;
	while (s < text_end)
	{
		if (word_wrap_enabled)
		{
			// Calculate how far we can render. Requires two passes on the string data but keeps the code simple and not intrusive for what's essentially an uncommon feature.
			if (!word_wrap_eol)
			{
				word_wrap_eol = CalcWordWrapPositionA(scale, s, text_end, wrap_width - line_width);
				if (word_wrap_eol == s) // Wrap_width is too small to fit anything. Force displaying 1 character to minimize the height discontinuity.
					word_wrap_eol++;    // +1 may not be a character start point in UTF-8 but it's ok because we use s >= word_wrap_eol below
			}

			if (s >= word_wrap_eol)
			{
				if (text_size.x < line_width)
					text_size.x = line_width;
				text_size.y += line_height;
				line_width = 0.0f;
				word_wrap_eol = NULL;

				// Wrapping skips upcoming blanks
				while (s < text_end)
				{
					const char c = *s;
					if (ImCharIsSpace(c)) { s++; }
					else if (c == '\n') { s++; break; }
					else { break; }
				}
				continue;
			}
		}

		// Decode and advance source
		const char* prev_s = s;
		unsigned int c = (unsigned int)*s;
		if (c < 0x80)
		{
			s += 1;
		}
		else
		{
			s += ImTextCharFromUtf8(&c, s, text_end);
			if (c == 0) // Malformed UTF-8?
				break;
		}

		if (c < 32)
		{
			if (c == '\n')
			{
				text_size.x = ImMax(text_size.x, line_width);
				text_size.y += line_height;
				line_width = 0.0f;
				continue;
			}
			if (c == '\r')
				continue;
		}

		const float char_width = ((int)c < IndexXAdvance.Size ? IndexXAdvance[(int)c] : FallbackXAdvance) * scale;
		if (line_width + char_width >= max_width)
		{
			s = prev_s;
			break;
		}

		line_width += char_width;
	}

	if (text_size.x < line_width)
		text_size.x = line_width;

	if (line_width > 0 || text_size.y == 0.0f)
		text_size.y += line_height;

	if (remaining)
		*remaining = s;

	return text_size;
}

void ImFont::RenderChar(ImDrawList* draw_list, float size, ImVec2 pos, ImU32 col, unsigned short c) const
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r') // Match behavior of RenderText(), those 4 codepoints are hard-coded.
		return;
	if (const Glyph* glyph = FindGlyph(c))
	{
		float scale = (size >= 0.0f) ? (size / FontSize) : 1.0f;
		pos.x = (float)(int)pos.x + DisplayOffset.x;
		pos.y = (float)(int)pos.y + DisplayOffset.y;
		ImVec2 pos_tl(pos.x + glyph->X0 * scale, pos.y + glyph->Y0 * scale);
		ImVec2 pos_br(pos.x + glyph->X1 * scale, pos.y + glyph->Y1 * scale);
		draw_list->PrimReserve(6, 4);
		draw_list->PrimRectUV(pos_tl, pos_br, ImVec2(glyph->U0, glyph->V0), ImVec2(glyph->U1, glyph->V1), col);
	}
}

void ImFont::RenderText(ImDrawList* draw_list, float size, ImVec2 pos, ImU32 col, const ImVec4& clip_rect, const char* text_begin, const char* text_end, float wrap_width, bool cpu_fine_clip) const
{
	if (!text_end)
		text_end = text_begin + strlen(text_begin); // ImGui functions generally already provides a valid text_end, so this is merely to handle direct calls.

													// Align to be pixel perfect
	pos.x = (float)(int)pos.x + DisplayOffset.x;
	pos.y = (float)(int)pos.y + DisplayOffset.y;
	float x = pos.x;
	float y = pos.y;
	if (y > clip_rect.w)
		return;

	const float scale = size / FontSize;
	const float line_height = FontSize * scale;
	const bool word_wrap_enabled = (wrap_width > 0.0f);
	const char* word_wrap_eol = NULL;

	// Skip non-visible lines
	const char* s = text_begin;
	if (!word_wrap_enabled && y + line_height < clip_rect.y)
		while (s < text_end && *s != '\n')  // Fast-forward to next line
			s++;

	// Reserve vertices for remaining worse case (over-reserving is useful and easily amortized)
	const int vtx_count_max = (int)(text_end - s) * 4;
	const int idx_count_max = (int)(text_end - s) * 6;
	const int idx_expected_size = draw_list->IdxBuffer.Size + idx_count_max;
	draw_list->PrimReserve(idx_count_max, vtx_count_max);

	ImDrawVert* vtx_write = draw_list->_VtxWritePtr;
	ImDrawIdx* idx_write = draw_list->_IdxWritePtr;
	unsigned int vtx_current_idx = draw_list->_VtxCurrentIdx;

	while (s < text_end)
	{
		if (word_wrap_enabled)
		{
			// Calculate how far we can render. Requires two passes on the string data but keeps the code simple and not intrusive for what's essentially an uncommon feature.
			if (!word_wrap_eol)
			{
				word_wrap_eol = CalcWordWrapPositionA(scale, s, text_end, wrap_width - (x - pos.x));
				if (word_wrap_eol == s) // Wrap_width is too small to fit anything. Force displaying 1 character to minimize the height discontinuity.
					word_wrap_eol++;    // +1 may not be a character start point in UTF-8 but it's ok because we use s >= word_wrap_eol below
			}

			if (s >= word_wrap_eol)
			{
				x = pos.x;
				y += line_height;
				word_wrap_eol = NULL;

				// Wrapping skips upcoming blanks
				while (s < text_end)
				{
					const char c = *s;
					if (ImCharIsSpace(c)) { s++; }
					else if (c == '\n') { s++; break; }
					else { break; }
				}
				continue;
			}
		}

		// Decode and advance source
		unsigned int c = (unsigned int)*s;
		if (c < 0x80)
		{
			s += 1;
		}
		else
		{
			s += ImTextCharFromUtf8(&c, s, text_end);
			if (c == 0) // Malformed UTF-8?
				break;
		}

		if (c < 32)
		{
			if (c == '\n')
			{
				x = pos.x;
				y += line_height;

				if (y > clip_rect.w)
					break;
				if (!word_wrap_enabled && y + line_height < clip_rect.y)
					while (s < text_end && *s != '\n')  // Fast-forward to next line
						s++;
				continue;
			}
			if (c == '\r')
				continue;
		}

		float char_width = 0.0f;
		if (const Glyph* glyph = FindGlyph((unsigned short)c))
		{
			char_width = glyph->XAdvance * scale;

			// Arbitrarily assume that both space and tabs are empty glyphs as an optimization
			if (c != ' ' && c != '\t')
			{
				// We don't do a second finer clipping test on the Y axis as we've already skipped anything before clip_rect.y and exit once we pass clip_rect.w
				float x1 = x + glyph->X0 * scale;
				float x2 = x + glyph->X1 * scale;
				float y1 = y + glyph->Y0 * scale;
				float y2 = y + glyph->Y1 * scale;
				if (x1 <= clip_rect.z && x2 >= clip_rect.x)
				{
					// Render a character
					float u1 = glyph->U0;
					float v1 = glyph->V0;
					float u2 = glyph->U1;
					float v2 = glyph->V1;

					// CPU side clipping used to fit text in their frame when the frame is too small. Only does clipping for axis aligned quads.
					if (cpu_fine_clip)
					{
						if (x1 < clip_rect.x)
						{
							u1 = u1 + (1.0f - (x2 - clip_rect.x) / (x2 - x1)) * (u2 - u1);
							x1 = clip_rect.x;
						}
						if (y1 < clip_rect.y)
						{
							v1 = v1 + (1.0f - (y2 - clip_rect.y) / (y2 - y1)) * (v2 - v1);
							y1 = clip_rect.y;
						}
						if (x2 > clip_rect.z)
						{
							u2 = u1 + ((clip_rect.z - x1) / (x2 - x1)) * (u2 - u1);
							x2 = clip_rect.z;
						}
						if (y2 > clip_rect.w)
						{
							v2 = v1 + ((clip_rect.w - y1) / (y2 - y1)) * (v2 - v1);
							y2 = clip_rect.w;
						}
						if (y1 >= y2)
						{
							x += char_width;
							continue;
						}
					}

					// We are NOT calling PrimRectUV() here because non-inlined causes too much overhead in a debug build.
					// Inlined here:
					{
						idx_write[0] = (ImDrawIdx)(vtx_current_idx); idx_write[1] = (ImDrawIdx)(vtx_current_idx + 1); idx_write[2] = (ImDrawIdx)(vtx_current_idx + 2);
						idx_write[3] = (ImDrawIdx)(vtx_current_idx); idx_write[4] = (ImDrawIdx)(vtx_current_idx + 2); idx_write[5] = (ImDrawIdx)(vtx_current_idx + 3);
						vtx_write[0].pos.x = x1; vtx_write[0].pos.y = y1; vtx_write[0].col = col; vtx_write[0].uv.x = u1; vtx_write[0].uv.y = v1;
						vtx_write[1].pos.x = x2; vtx_write[1].pos.y = y1; vtx_write[1].col = col; vtx_write[1].uv.x = u2; vtx_write[1].uv.y = v1;
						vtx_write[2].pos.x = x2; vtx_write[2].pos.y = y2; vtx_write[2].col = col; vtx_write[2].uv.x = u2; vtx_write[2].uv.y = v2;
						vtx_write[3].pos.x = x1; vtx_write[3].pos.y = y2; vtx_write[3].col = col; vtx_write[3].uv.x = u1; vtx_write[3].uv.y = v2;
						vtx_write += 4;
						vtx_current_idx += 4;
						idx_write += 6;
					}
				}
			}
		}

		x += char_width;
	}

	// Give back unused vertices
	draw_list->VtxBuffer.resize((int)(vtx_write - draw_list->VtxBuffer.Data));
	draw_list->IdxBuffer.resize((int)(idx_write - draw_list->IdxBuffer.Data));
	draw_list->CmdBuffer[draw_list->CmdBuffer.Size - 1].ElemCount -= (idx_expected_size - draw_list->IdxBuffer.Size);
	draw_list->_VtxWritePtr = vtx_write;
	draw_list->_IdxWritePtr = idx_write;
	draw_list->_VtxCurrentIdx = (unsigned int)draw_list->VtxBuffer.Size;
}

//-----------------------------------------------------------------------------
// DEFAULT FONT DATA
//-----------------------------------------------------------------------------
// Compressed with stb_compress() then converted to a C array.
// Use the program in extra_fonts/binary_to_compressed_c.cpp to create the array from a TTF file.
// Decompression from stb.h (public domain) by Sean Barrett https://github.com/nothings/stb/blob/master/stb.h
//-----------------------------------------------------------------------------

static unsigned int stb_decompress_length(unsigned char *input)
{
	return (input[8] << 24) + (input[9] << 16) + (input[10] << 8) + input[11];
}

static unsigned char *stb__barrier, *stb__barrier2, *stb__barrier3, *stb__barrier4;
static unsigned char *stb__dout;
static void stb__match(unsigned char *data, unsigned int length)
{
	// INVERSE of memmove... write each byte before copying the next...
	IM_ASSERT(stb__dout + length <= stb__barrier);
	if (stb__dout + length > stb__barrier) { stb__dout += length; return; }
	if (data < stb__barrier4) { stb__dout = stb__barrier + 1; return; }
	while (length--) *stb__dout++ = *data++;
}

static void stb__lit(unsigned char *data, unsigned int length)
{
	IM_ASSERT(stb__dout + length <= stb__barrier);
	if (stb__dout + length > stb__barrier) { stb__dout += length; return; }
	if (data < stb__barrier2) { stb__dout = stb__barrier + 1; return; }
	memcpy(stb__dout, data, length);
	stb__dout += length;
}

#define stb__in2(x)   ((i[x] << 8) + i[(x)+1])
#define stb__in3(x)   ((i[x] << 16) + stb__in2((x)+1))
#define stb__in4(x)   ((i[x] << 24) + stb__in3((x)+1))

static unsigned char *stb_decompress_token(unsigned char *i)
{
	if (*i >= 0x20) { // use fewer if's for cases that expand small
		if (*i >= 0x80)       stb__match(stb__dout - i[1] - 1, i[0] - 0x80 + 1), i += 2;
		else if (*i >= 0x40)  stb__match(stb__dout - (stb__in2(0) - 0x4000 + 1), i[2] + 1), i += 3;
		else /* *i >= 0x20 */ stb__lit(i + 1, i[0] - 0x20 + 1), i += 1 + (i[0] - 0x20 + 1);
	}
	else { // more ifs for cases that expand large, since overhead is amortized
		if (*i >= 0x18)       stb__match(stb__dout - (stb__in3(0) - 0x180000 + 1), i[3] + 1), i += 4;
		else if (*i >= 0x10)  stb__match(stb__dout - (stb__in3(0) - 0x100000 + 1), stb__in2(3) + 1), i += 5;
		else if (*i >= 0x08)  stb__lit(i + 2, stb__in2(0) - 0x0800 + 1), i += 2 + (stb__in2(0) - 0x0800 + 1);
		else if (*i == 0x07)  stb__lit(i + 3, stb__in2(1) + 1), i += 3 + (stb__in2(1) + 1);
		else if (*i == 0x06)  stb__match(stb__dout - (stb__in3(1) + 1), i[4] + 1), i += 5;
		else if (*i == 0x04)  stb__match(stb__dout - (stb__in3(1) + 1), stb__in2(4) + 1), i += 6;
	}
	return i;
}

static unsigned int stb_adler32(unsigned int adler32, unsigned char *buffer, unsigned int buflen)
{
	const unsigned long ADLER_MOD = 65521;
	unsigned long s1 = adler32 & 0xffff, s2 = adler32 >> 16;
	unsigned long blocklen, i;

	blocklen = buflen % 5552;
	while (buflen) {
		for (i = 0; i + 7 < blocklen; i += 8) {
			s1 += buffer[0], s2 += s1;
			s1 += buffer[1], s2 += s1;
			s1 += buffer[2], s2 += s1;
			s1 += buffer[3], s2 += s1;
			s1 += buffer[4], s2 += s1;
			s1 += buffer[5], s2 += s1;
			s1 += buffer[6], s2 += s1;
			s1 += buffer[7], s2 += s1;

			buffer += 8;
		}

		for (; i < blocklen; ++i)
			s1 += *buffer++, s2 += s1;

		s1 %= ADLER_MOD, s2 %= ADLER_MOD;
		buflen -= blocklen;
		blocklen = 5552;
	}
	return (unsigned int)(s2 << 16) + (unsigned int)s1;
}

static unsigned int stb_decompress(unsigned char *output, unsigned char *i, unsigned int length)
{
	unsigned int olen;
	if (stb__in4(0) != 0x57bC0000) return 0;
	if (stb__in4(4) != 0)          return 0; // error! stream is > 4GB
	olen = stb_decompress_length(i);
	stb__barrier2 = i;
	stb__barrier3 = i + length;
	stb__barrier = output + olen;
	stb__barrier4 = output;
	i += 16;

	stb__dout = output;
	for (;;) {
		unsigned char *old_i = i;
		i = stb_decompress_token(i);
		if (i == old_i) {
			if (*i == 0x05 && i[1] == 0xfa) {
				IM_ASSERT(stb__dout == output + olen);
				if (stb__dout != output + olen) return 0;
				if (stb_adler32(1, output, olen) != (unsigned int)stb__in4(2))
					return 0;
				return olen;
			}
			else {
				IM_ASSERT(0); /* NOTREACHED */
				return 0;
			}
		}
		IM_ASSERT(stb__dout <= output + olen);
		if (stb__dout > output + olen)
			return 0;
	}
}

//-----------------------------------------------------------------------------
// ProggyClean.ttf
// Copyright (c) 2004, 2005 Tristan Grimmer
// MIT license (see License.txt in http://www.upperbounds.net/download/ProggyClean.ttf.zip)
// Download and more information at http://upperbounds.net
//-----------------------------------------------------------------------------
// File: 'ProggyClean.ttf' (41208 bytes)
// Exported using binary_to_compressed_c.cpp
//-----------------------------------------------------------------------------
static const char proggy_clean_ttf_compressed_data_base85[11980 + 1] =
"7])#######hV0qs'/###[),##/l:$#Q6>##5[n42>c-TH`->>#/e>11NNV=Bv(*:.F?uu#(gRU.o0XGH`$vhLG1hxt9?W`#,5LsCp#-i>.r$<$6pD>Lb';9Crc6tgXmKVeU2cD4Eo3R/"
"2*>]b(MC;$jPfY.;h^`IWM9<Lh2TlS+f-s$o6Q<BWH`YiU.xfLq$N;$0iR/GX:U(jcW2p/W*q?-qmnUCI;jHSAiFWM.R*kU@C=GH?a9wp8f$e.-4^Qg1)Q-GL(lf(r/7GrRgwV%MS=C#"
"`8ND>Qo#t'X#(v#Y9w0#1D$CIf;W'#pWUPXOuxXuU(H9M(1<q-UE31#^-V'8IRUo7Qf./L>=Ke$$'5F%)]0^#0X@U.a<r:QLtFsLcL6##lOj)#.Y5<-R&KgLwqJfLgN&;Q?gI^#DY2uL"
"i@^rMl9t=cWq6##weg>$FBjVQTSDgEKnIS7EM9>ZY9w0#L;>>#Mx&4Mvt//L[MkA#W@lK.N'[0#7RL_&#w+F%HtG9M#XL`N&.,GM4Pg;-<nLENhvx>-VsM.M0rJfLH2eTM`*oJMHRC`N"
"kfimM2J,W-jXS:)r0wK#@Fge$U>`w'N7G#$#fB#$E^$#:9:hk+eOe--6x)F7*E%?76%^GMHePW-Z5l'&GiF#$956:rS?dA#fiK:)Yr+`&#0j@'DbG&#^$PG.Ll+DNa<XCMKEV*N)LN/N"
"*b=%Q6pia-Xg8I$<MR&,VdJe$<(7G;Ckl'&hF;;$<_=X(b.RS%%)###MPBuuE1V:v&cX&#2m#(&cV]`k9OhLMbn%s$G2,B$BfD3X*sp5#l,$R#]x_X1xKX%b5U*[r5iMfUo9U`N99hG)"
"tm+/Us9pG)XPu`<0s-)WTt(gCRxIg(%6sfh=ktMKn3j)<6<b5Sk_/0(^]AaN#(p/L>&VZ>1i%h1S9u5o@YaaW$e+b<TWFn/Z:Oh(Cx2$lNEoN^e)#CFY@@I;BOQ*sRwZtZxRcU7uW6CX"
"ow0i(?$Q[cjOd[P4d)]>ROPOpxTO7Stwi1::iB1q)C_=dV26J;2,]7op$]uQr@_V7$q^%lQwtuHY]=DX,n3L#0PHDO4f9>dC@O>HBuKPpP*E,N+b3L#lpR/MrTEH.IAQk.a>D[.e;mc."
"x]Ip.PH^'/aqUO/$1WxLoW0[iLA<QT;5HKD+@qQ'NQ(3_PLhE48R.qAPSwQ0/WK?Z,[x?-J;jQTWA0X@KJ(_Y8N-:/M74:/-ZpKrUss?d#dZq]DAbkU*JqkL+nwX@@47`5>w=4h(9.`G"
"CRUxHPeR`5Mjol(dUWxZa(>STrPkrJiWx`5U7F#.g*jrohGg`cg:lSTvEY/EV_7H4Q9[Z%cnv;JQYZ5q.l7Zeas:HOIZOB?G<Nald$qs]@]L<J7bR*>gv:[7MI2k).'2($5FNP&EQ(,)"
"U]W]+fh18.vsai00);D3@4ku5P?DP8aJt+;qUM]=+b'8@;mViBKx0DE[-auGl8:PJ&Dj+M6OC]O^((##]`0i)drT;-7X`=-H3[igUnPG-NZlo.#k@h#=Ork$m>a>$-?Tm$UV(?#P6YY#"
"'/###xe7q.73rI3*pP/$1>s9)W,JrM7SN]'/4C#v$U`0#V.[0>xQsH$fEmPMgY2u7Kh(G%siIfLSoS+MK2eTM$=5,M8p`A.;_R%#u[K#$x4AG8.kK/HSB==-'Ie/QTtG?-.*^N-4B/ZM"
"_3YlQC7(p7q)&](`6_c)$/*JL(L-^(]$wIM`dPtOdGA,U3:w2M-0<q-]L_?^)1vw'.,MRsqVr.L;aN&#/EgJ)PBc[-f>+WomX2u7lqM2iEumMTcsF?-aT=Z-97UEnXglEn1K-bnEO`gu"
"Ft(c%=;Am_Qs@jLooI&NX;]0#j4#F14;gl8-GQpgwhrq8'=l_f-b49'UOqkLu7-##oDY2L(te+Mch&gLYtJ,MEtJfLh'x'M=$CS-ZZ%P]8bZ>#S?YY#%Q&q'3^Fw&?D)UDNrocM3A76/"
"/oL?#h7gl85[qW/NDOk%16ij;+:1a'iNIdb-ou8.P*w,v5#EI$TWS>Pot-R*H'-SEpA:g)f+O$%%`kA#G=8RMmG1&O`>to8bC]T&$,n.LoO>29sp3dt-52U%VM#q7'DHpg+#Z9%H[K<L"
"%a2E-grWVM3@2=-k22tL]4$##6We'8UJCKE[d_=%wI;'6X-GsLX4j^SgJ$##R*w,vP3wK#iiW&#*h^D&R?jp7+/u&#(AP##XU8c$fSYW-J95_-Dp[g9wcO&#M-h1OcJlc-*vpw0xUX&#"
"OQFKNX@QI'IoPp7nb,QU//MQ&ZDkKP)X<WSVL(68uVl&#c'[0#(s1X&xm$Y%B7*K:eDA323j998GXbA#pwMs-jgD$9QISB-A_(aN4xoFM^@C58D0+Q+q3n0#3U1InDjF682-SjMXJK)("
"h$hxua_K]ul92%'BOU&#BRRh-slg8KDlr:%L71Ka:.A;%YULjDPmL<LYs8i#XwJOYaKPKc1h:'9Ke,g)b),78=I39B;xiY$bgGw-&.Zi9InXDuYa%G*f2Bq7mn9^#p1vv%#(Wi-;/Z5h"
"o;#2:;%d&#x9v68C5g?ntX0X)pT`;%pB3q7mgGN)3%(P8nTd5L7GeA-GL@+%J3u2:(Yf>et`e;)f#Km8&+DC$I46>#Kr]]u-[=99tts1.qb#q72g1WJO81q+eN'03'eM>&1XxY-caEnO"
"j%2n8)),?ILR5^.Ibn<-X-Mq7[a82Lq:F&#ce+S9wsCK*x`569E8ew'He]h:sI[2LM$[guka3ZRd6:t%IG:;$%YiJ:Nq=?eAw;/:nnDq0(CYcMpG)qLN4$##&J<j$UpK<Q4a1]MupW^-"
"sj_$%[HK%'F####QRZJ::Y3EGl4'@%FkiAOg#p[##O`gukTfBHagL<LHw%q&OV0##F=6/:chIm0@eCP8X]:kFI%hl8hgO@RcBhS-@Qb$%+m=hPDLg*%K8ln(wcf3/'DW-$.lR?n[nCH-"
"eXOONTJlh:.RYF%3'p6sq:UIMA945&^HFS87@$EP2iG<-lCO$%c`uKGD3rC$x0BL8aFn--`ke%#HMP'vh1/R&O_J9'um,.<tx[@%wsJk&bUT2`0uMv7gg#qp/ij.L56'hl;.s5CUrxjO"
"M7-##.l+Au'A&O:-T72L]P`&=;ctp'XScX*rU.>-XTt,%OVU4)S1+R-#dg0/Nn?Ku1^0f$B*P:Rowwm-`0PKjYDDM'3]d39VZHEl4,.j']Pk-M.h^&:0FACm$maq-&sgw0t7/6(^xtk%"
"LuH88Fj-ekm>GA#_>568x6(OFRl-IZp`&b,_P'$M<Jnq79VsJW/mWS*PUiq76;]/NM_>hLbxfc$mj`,O;&%W2m`Zh:/)Uetw:aJ%]K9h:TcF]u_-Sj9,VK3M.*'&0D[Ca]J9gp8,kAW]"
"%(?A%R$f<->Zts'^kn=-^@c4%-pY6qI%J%1IGxfLU9CP8cbPlXv);C=b),<2mOvP8up,UVf3839acAWAW-W?#ao/^#%KYo8fRULNd2.>%m]UK:n%r$'sw]J;5pAoO_#2mO3n,'=H5(et"
"Hg*`+RLgv>=4U8guD$I%D:W>-r5V*%j*W:Kvej.Lp$<M-SGZ':+Q_k+uvOSLiEo(<aD/K<CCc`'Lx>'?;++O'>()jLR-^u68PHm8ZFWe+ej8h:9r6L*0//c&iH&R8pRbA#Kjm%upV1g:"
"a_#Ur7FuA#(tRh#.Y5K+@?3<-8m0$PEn;J:rh6?I6uG<-`wMU'ircp0LaE_OtlMb&1#6T.#FDKu#1Lw%u%+GM+X'e?YLfjM[VO0MbuFp7;>Q&#WIo)0@F%q7c#4XAXN-U&VB<HFF*qL("
"$/V,;(kXZejWO`<[5?\?ewY(*9=%wDc;,u<'9t3W-(H1th3+G]ucQ]kLs7df($/*JL]@*t7Bu_G3_7mp7<iaQjO@.kLg;x3B0lqp7Hf,^Ze7-##@/c58Mo(3;knp0%)A7?-W+eI'o8)b<"
"nKnw'Ho8C=Y>pqB>0ie&jhZ[?iLR@@_AvA-iQC(=ksRZRVp7`.=+NpBC%rh&3]R:8XDmE5^V8O(x<<aG/1N$#FX$0V5Y6x'aErI3I$7x%E`v<-BY,)%-?Psf*l?%C3.mM(=/M0:JxG'?"
"7WhH%o'a<-80g0NBxoO(GH<dM]n.+%q@jH?f.UsJ2Ggs&4<-e47&Kl+f//9@`b+?.TeN_&B8Ss?v;^Trk;f#YvJkl&w$]>-+k?'(<S:68tq*WoDfZu';mM?8X[ma8W%*`-=;D.(nc7/;"
")g:T1=^J$&BRV(-lTmNB6xqB[@0*o.erM*<SWF]u2=st-*(6v>^](H.aREZSi,#1:[IXaZFOm<-ui#qUq2$##Ri;u75OK#(RtaW-K-F`S+cF]uN`-KMQ%rP/Xri.LRcB##=YL3BgM/3M"
"D?@f&1'BW-)Ju<L25gl8uhVm1hL$##*8###'A3/LkKW+(^rWX?5W_8g)a(m&K8P>#bmmWCMkk&#TR`C,5d>g)F;t,4:@_l8G/5h4vUd%&%950:VXD'QdWoY-F$BtUwmfe$YqL'8(PWX("
"P?^@Po3$##`MSs?DWBZ/S>+4%>fX,VWv/w'KD`LP5IbH;rTV>n3cEK8U#bX]l-/V+^lj3;vlMb&[5YQ8#pekX9JP3XUC72L,,?+Ni&co7ApnO*5NK,((W-i:$,kp'UDAO(G0Sq7MVjJs"
"bIu)'Z,*[>br5fX^:FPAWr-m2KgL<LUN098kTF&#lvo58=/vjDo;.;)Ka*hLR#/k=rKbxuV`>Q_nN6'8uTG&#1T5g)uLv:873UpTLgH+#FgpH'_o1780Ph8KmxQJ8#H72L4@768@Tm&Q"
"h4CB/5OvmA&,Q&QbUoi$a_%3M01H)4x7I^&KQVgtFnV+;[Pc>[m4k//,]1?#`VY[Jr*3&&slRfLiVZJ:]?=K3Sw=[$=uRB?3xk48@aeg<Z'<$#4H)6,>e0jT6'N#(q%.O=?2S]u*(m<-"
"V8J'(1)G][68hW$5'q[GC&5j`TE?m'esFGNRM)j,ffZ?-qx8;->g4t*:CIP/[Qap7/9'#(1sao7w-.qNUdkJ)tCF&#B^;xGvn2r9FEPFFFcL@.iFNkTve$m%#QvQS8U@)2Z+3K:AKM5i"
"sZ88+dKQ)W6>J%CL<KE>`.d*(B`-n8D9oK<Up]c$X$(,)M8Zt7/[rdkqTgl-0cuGMv'?>-XV1q['-5k'cAZ69e;D_?$ZPP&s^+7])$*$#@QYi9,5P&#9r+$%CE=68>K8r0=dSC%%(@p7"
".m7jilQ02'0-VWAg<a/''3u.=4L$Y)6k/K:_[3=&jvL<L0C/2'v:^;-DIBW,B4E68:kZ;%?8(Q8BH=kO65BW?xSG&#@uU,DS*,?.+(o(#1vCS8#CHF>TlGW'b)Tq7VT9q^*^$$.:&N@@"
"$&)WHtPm*5_rO0&e%K&#-30j(E4#'Zb.o/(Tpm$>K'f@[PvFl,hfINTNU6u'0pao7%XUp9]5.>%h`8_=VYbxuel.NTSsJfLacFu3B'lQSu/m6-Oqem8T+oE--$0a/k]uj9EwsG>%veR*"
"hv^BFpQj:K'#SJ,sB-'#](j.Lg92rTw-*n%@/;39rrJF,l#qV%OrtBeC6/,;qB3ebNW[?,Hqj2L.1NP&GjUR=1D8QaS3Up&@*9wP?+lo7b?@%'k4`p0Z$22%K3+iCZj?XJN4Nm&+YF]u"
"@-W$U%VEQ/,,>>#)D<h#`)h0:<Q6909ua+&VU%n2:cG3FJ-%@Bj-DgLr`Hw&HAKjKjseK</xKT*)B,N9X3]krc12t'pgTV(Lv-tL[xg_%=M_q7a^x?7Ubd>#%8cY#YZ?=,`Wdxu/ae&#"
"w6)R89tI#6@s'(6Bf7a&?S=^ZI_kS&ai`&=tE72L_D,;^R)7[$s<Eh#c&)q.MXI%#v9ROa5FZO%sF7q7Nwb&#ptUJ:aqJe$Sl68%.D###EC><?-aF&#RNQv>o8lKN%5/$(vdfq7+ebA#"
"u1p]ovUKW&Y%q]'>$1@-[xfn$7ZTp7mM,G,Ko7a&Gu%G[RMxJs[0MM%wci.LFDK)(<c`Q8N)jEIF*+?P2a8g%)$q]o2aH8C&<SibC/q,(e:v;-b#6[$NtDZ84Je2KNvB#$P5?tQ3nt(0"
"d=j.LQf./Ll33+(;q3L-w=8dX$#WF&uIJ@-bfI>%:_i2B5CsR8&9Z&#=mPEnm0f`<&c)QL5uJ#%u%lJj+D-r;BoF&#4DoS97h5g)E#o:&S4weDF,9^Hoe`h*L+_a*NrLW-1pG_&2UdB8"
"6e%B/:=>)N4xeW.*wft-;$'58-ESqr<b?UI(_%@[P46>#U`'6AQ]m&6/`Z>#S?YY#Vc;r7U2&326d=w&H####?TZ`*4?&.MK?LP8Vxg>$[QXc%QJv92.(Db*B)gb*BM9dM*hJMAo*c&#"
"b0v=Pjer]$gG&JXDf->'StvU7505l9$AFvgYRI^&<^b68?j#q9QX4SM'RO#&sL1IM.rJfLUAj221]d##DW=m83u5;'bYx,*Sl0hL(W;;$doB&O/TQ:(Z^xBdLjL<Lni;''X.`$#8+1GD"
":k$YUWsbn8ogh6rxZ2Z9]%nd+>V#*8U_72Lh+2Q8Cj0i:6hp&$C/:p(HK>T8Y[gHQ4`4)'$Ab(Nof%V'8hL&#<NEdtg(n'=S1A(Q1/I&4([%dM`,Iu'1:_hL>SfD07&6D<fp8dHM7/g+"
"tlPN9J*rKaPct&?'uBCem^jn%9_K)<,C5K3s=5g&GmJb*[SYq7K;TRLGCsM-$$;S%:Y@r7AK0pprpL<Lrh,q7e/%KWK:50I^+m'vi`3?%Zp+<-d+$L-Sv:@.o19n$s0&39;kn;S%BSq*"
"$3WoJSCLweV[aZ'MQIjO<7;X-X;&+dMLvu#^UsGEC9WEc[X(wI7#2.(F0jV*eZf<-Qv3J-c+J5AlrB#$p(H68LvEA'q3n0#m,[`*8Ft)FcYgEud]CWfm68,(aLA$@EFTgLXoBq/UPlp7"
":d[/;r_ix=:TF`S5H-b<LI&HY(K=h#)]Lk$K14lVfm:x$H<3^Ql<M`$OhapBnkup'D#L$Pb_`N*g]2e;X/Dtg,bsj&K#2[-:iYr'_wgH)NUIR8a1n#S?Yej'h8^58UbZd+^FKD*T@;6A"
"7aQC[K8d-(v6GI$x:T<&'Gp5Uf>@M.*J:;$-rv29'M]8qMv-tLp,'886iaC=Hb*YJoKJ,(j%K=H`K.v9HggqBIiZu'QvBT.#=)0ukruV&.)3=(^1`o*Pj4<-<aN((^7('#Z0wK#5GX@7"
"u][`*S^43933A4rl][`*O4CgLEl]v$1Q3AeF37dbXk,.)vj#x'd`;qgbQR%FW,2(?LO=s%Sc68%NP'##Aotl8x=BE#j1UD([3$M(]UI2LX3RpKN@;/#f'f/&_mt&F)XdF<9t4)Qa.*kT"
"LwQ'(TTB9.xH'>#MJ+gLq9-##@HuZPN0]u:h7.T..G:;$/Usj(T7`Q8tT72LnYl<-qx8;-HV7Q-&Xdx%1a,hC=0u+HlsV>nuIQL-5<N?)NBS)QN*_I,?&)2'IM%L3I)X((e/dl2&8'<M"
":^#M*Q+[T.Xri.LYS3v%fF`68h;b-X[/En'CR.q7E)p'/kle2HM,u;^%OKC-N+Ll%F9CF<Nf'^#t2L,;27W:0O@6##U6W7:$rJfLWHj$#)woqBefIZ.PK<b*t7ed;p*_m;4ExK#h@&]>"
"_>@kXQtMacfD.m-VAb8;IReM3$wf0''hra*so568'Ip&vRs849'MRYSp%:t:h5qSgwpEr$B>Q,;s(C#$)`svQuF$##-D,##,g68@2[T;.XSdN9Qe)rpt._K-#5wF)sP'##p#C0c%-Gb%"
"hd+<-j'Ai*x&&HMkT]C'OSl##5RG[JXaHN;d'uA#x._U;.`PU@(Z3dt4r152@:v,'R.Sj'w#0<-;kPI)FfJ&#AYJ&#//)>-k=m=*XnK$>=)72L]0I%>.G690a:$##<,);?;72#?x9+d;"
"^V'9;jY@;)br#q^YQpx:X#Te$Z^'=-=bGhLf:D6&bNwZ9-ZD#n^9HhLMr5G;']d&6'wYmTFmL<LD)F^%[tC'8;+9E#C$g%#5Y>q9wI>P(9mI[>kC-ekLC/R&CH+s'B;K-M6$EB%is00:"
"+A4[7xks.LrNk0&E)wILYF@2L'0Nb$+pv<(2.768/FrY&h$^3i&@+G%JT'<-,v`3;_)I9M^AE]CN?Cl2AZg+%4iTpT3<n-&%H%b<FDj2M<hH=&Eh<2Len$b*aTX=-8QxN)k11IM1c^j%"
"9s<L<NFSo)B?+<-(GxsF,^-Eh@$4dXhN$+#rxK8'je'D7k`e;)2pYwPA'_p9&@^18ml1^[@g4t*[JOa*[=Qp7(qJ_oOL^('7fB&Hq-:sf,sNj8xq^>$U4O]GKx'm9)b@p7YsvK3w^YR-"
"CdQ*:Ir<($u&)#(&?L9Rg3H)4fiEp^iI9O8KnTj,]H?D*r7'M;PwZ9K0E^k&-cpI;.p/6_vwoFMV<->#%Xi.LxVnrU(4&8/P+:hLSKj$#U%]49t'I:rgMi'FL@a:0Y-uA[39',(vbma*"
"hU%<-SRF`Tt:542R_VV$p@[p8DV[A,?1839FWdF<TddF<9Ah-6&9tWoDlh]&1SpGMq>Ti1O*H&#(AL8[_P%.M>v^-))qOT*F5Cq0`Ye%+$B6i:7@0IX<N+T+0MlMBPQ*Vj>SsD<U4JHY"
"8kD2)2fU/M#$e.)T4,_=8hLim[&);?UkK'-x?'(:siIfL<$pFM`i<?%W(mGDHM%>iWP,##P`%/L<eXi:@Z9C.7o=@(pXdAO/NLQ8lPl+HPOQa8wD8=^GlPa8TKI1CjhsCTSLJM'/Wl>-"
"S(qw%sf/@%#B6;/U7K]uZbi^Oc^2n<bhPmUkMw>%t<)'mEVE''n`WnJra$^TKvX5B>;_aSEK',(hwa0:i4G?.Bci.(X[?b*($,=-n<.Q%`(X=?+@Am*Js0&=3bh8K]mL<LoNs'6,'85`"
"0?t/'_U59@]ddF<#LdF<eWdF<OuN/45rY<-L@&#+fm>69=Lb,OcZV/);TTm8VI;?%OtJ<(b4mq7M6:u?KRdF<gR@2L=FNU-<b[(9c/ML3m;Z[$oF3g)GAWqpARc=<ROu7cL5l;-[A]%/"
"+fsd;l#SafT/f*W]0=O'$(Tb<[)*@e775R-:Yob%g*>l*:xP?Yb.5)%w_I?7uk5JC+FS(m#i'k.'a0i)9<7b'fs'59hq$*5Uhv##pi^8+hIEBF`nvo`;'l0.^S1<-wUK2/Coh58KKhLj"
"M=SO*rfO`+qC`W-On.=AJ56>>i2@2LH6A:&5q`?9I3@@'04&p2/LVa*T-4<-i3;M9UvZd+N7>b*eIwg:CC)c<>nO&#<IGe;__.thjZl<%w(Wk2xmp4Q@I#I9,DF]u7-P=.-_:YJ]aS@V"
"?6*C()dOp7:WL,b&3Rg/.cmM9&r^>$(>.Z-I&J(Q0Hd5Q%7Co-b`-c<N(6r@ip+AurK<m86QIth*#v;-OBqi+L7wDE-Ir8K['m+DDSLwK&/.?-V%U_%3:qKNu$_b*B-kp7NaD'QdWQPK"
"Yq[@>P)hI;*_F]u`Rb[.j8_Q/<&>uu+VsH$sM9TA%?)(vmJ80),P7E>)tjD%2L=-t#fK[%`v=Q8<FfNkgg^oIbah*#8/Qt$F&:K*-(N/'+1vMB,u()-a.VUU*#[e%gAAO(S>WlA2);Sa"
">gXm8YB`1d@K#n]76-a$U,mF<fX]idqd)<3,]J7JmW4`6]uks=4-72L(jEk+:bJ0M^q-8Dm_Z?0olP1C9Sa&H[d&c$ooQUj]Exd*3ZM@-WGW2%s',B-_M%>%Ul:#/'xoFM9QX-$.QN'>"
"[%$Z$uF6pA6Ki2O5:8w*vP1<-1`[G,)-m#>0`P&#eb#.3i)rtB61(o'$?X3B</R90;eZ]%Ncq;-Tl]#F>2Qft^ae_5tKL9MUe9b*sLEQ95C&`=G?@Mj=wh*'3E>=-<)Gt*Iw)'QG:`@I"
"wOf7&]1i'S01B+Ev/Nac#9S;=;YQpg_6U`*kVY39xK,[/6Aj7:'1Bm-_1EYfa1+o&o4hp7KN_Q(OlIo@S%;jVdn0'1<Vc52=u`3^o-n1'g4v58Hj&6_t7$##?M)c<$bgQ_'SY((-xkA#"
"Y(,p'H9rIVY-b,'%bCPF7.J<Up^,(dU1VY*5#WkTU>h19w,WQhLI)3S#f$2(eb,jr*b;3Vw]*7NH%$c4Vs,eD9>XW8?N]o+(*pgC%/72LV-u<Hp,3@e^9UB1J+ak9-TN/mhKPg+AJYd$"
"MlvAF_jCK*.O-^(63adMT->W%iewS8W6m2rtCpo'RS1R84=@paTKt)>=%&1[)*vp'u+x,VrwN;&]kuO9JDbg=pO$J*.jVe;u'm0dr9l,<*wMK*Oe=g8lV_KEBFkO'oU]^=[-792#ok,)"
"i]lR8qQ2oA8wcRCZ^7w/Njh;?.stX?Q1>S1q4Bn$)K1<-rGdO'$Wr.Lc.CG)$/*JL4tNR/,SVO3,aUw'DJN:)Ss;wGn9A32ijw%FL+Z0Fn.U9;reSq)bmI32U==5ALuG&#Vf1398/pVo"
"1*c-(aY168o<`JsSbk-,1N;$>0:OUas(3:8Z972LSfF8eb=c-;>SPw7.6hn3m`9^Xkn(r.qS[0;T%&Qc=+STRxX'q1BNk3&*eu2;&8q$&x>Q#Q7^Tf+6<(d%ZVmj2bDi%.3L2n+4W'$P"
"iDDG)g,r%+?,$@?uou5tSe2aN_AQU*<h`e-GI7)?OK2A.d7_c)?wQ5AS@DL3r#7fSkgl6-++D:'A,uq7SvlB$pcpH'q3n0#_%dY#xCpr-l<F0NR@-##FEV6NTF6##$l84N1w?AO>'IAO"
"URQ##V^Fv-XFbGM7Fl(N<3DhLGF%q.1rC$#:T__&Pi68%0xi_&[qFJ(77j_&JWoF.V735&T,[R*:xFR*K5>>#`bW-?4Ne_&6Ne_&6Ne_&n`kr-#GJcM6X;uM6X;uM(.a..^2TkL%oR(#"
";u.T%fAr%4tJ8&><1=GHZ_+m9/#H1F^R#SC#*N=BA9(D?v[UiFY>>^8p,KKF.W]L29uLkLlu/+4T<XoIB&hx=T1PcDaB&;HH+-AFr?(m9HZV)FKS8JCw;SD=6[^/DZUL`EUDf]GGlG&>"
"w$)F./^n3+rlo+DB;5sIYGNk+i1t-69Jg--0pao7Sm#K)pdHW&;LuDNH@H>#/X-TI(;P>#,Gc>#0Su>#4`1?#8lC?#<xU?#@.i?#D:%@#HF7@#LRI@#P_[@#Tkn@#Xw*A#]-=A#a9OA#"
"d<F&#*;G##.GY##2Sl##6`($#:l:$#>xL$#B.`$#F:r$#JF.%#NR@%#R_R%#Vke%#Zww%#_-4&#3^Rh%Sflr-k'MS.o?.5/sWel/wpEM0%3'/1)K^f1-d>G21&v(35>V`39V7A4=onx4"
"A1OY5EI0;6Ibgr6M$HS7Q<)58C5w,;WoA*#[%T*#`1g*#d=#+#hI5+#lUG+#pbY+#tnl+#x$),#&1;,#*=M,#.I`,#2Ur,#6b.-#;w[H#iQtA#m^0B#qjBB#uvTB##-hB#'9$C#+E6C#"
"/QHC#3^ZC#7jmC#;v)D#?,<D#C8ND#GDaD#KPsD#O]/E#g1A5#KA*1#gC17#MGd;#8(02#L-d3#rWM4#Hga1#,<w0#T.j<#O#'2#CYN1#qa^:#_4m3#o@/=#eG8=#t8J5#`+78#4uI-#"
"m3B2#SB[8#Q0@8#i[*9#iOn8#1Nm;#^sN9#qh<9#:=x-#P;K2#$%X9#bC+.#Rg;<#mN=.#MTF.#RZO.#2?)4#Y#(/#[)1/#b;L/#dAU/#0Sv;#lY$0#n`-0#sf60#(F24#wrH0#%/e0#"
"TmD<#%JSMFove:CTBEXI:<eh2g)B,3h2^G3i;#d3jD>)4kMYD4lVu`4m`:&5niUA5@(A5BA1]PBB:xlBCC=2CDLXMCEUtiCf&0g2'tN?PGT4CPGT4CPGT4CPGT4CPGT4CPGT4CPGT4CP"
"GT4CPGT4CPGT4CPGT4CPGT4CPGT4CP-qekC`.9kEg^+F$kwViFJTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5o,^<-28ZI'O?;xp"
"O?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xp;7q-#lLYI:xvD=#";

static const char* GetDefaultCompressedFontDataTTFBase85()
{
	return proggy_clean_ttf_compressed_data_base85;
}










































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZEYWROPFZK
{ 
  void ILgQHIpCAL()
  { 
      bool noyWhhRwhf = false;
      bool ZzttbSEoZu = false;
      bool uzBBKnJSxb = false;
      bool zxKDeQwmSV = false;
      bool tMSWTTZOVm = false;
      bool xMETIonxLt = false;
      bool YzyFgbnqPK = false;
      bool VQVEBifehq = false;
      bool OtwKelsqup = false;
      bool czbYwuONpr = false;
      bool eizKRfpASY = false;
      bool IJPUedCnZt = false;
      bool hxwZgWoxHF = false;
      bool TSnpLeulrz = false;
      bool wsXVgTiGsR = false;
      bool sZmwJhlZdt = false;
      bool psrMFpUZJA = false;
      bool iQuayoYarM = false;
      bool mhDoMsfrgd = false;
      bool sVHyICALQq = false;
      string opbdLPOFri;
      string JElDugjBNZ;
      string auJUDTtcpy;
      string ziZKPjsKRt;
      string cxPpESAFhX;
      string bJEghsgHaq;
      string VkPsiZebmL;
      string mYjSxdeTPj;
      string SotRVoescW;
      string CljZYqgWGd;
      string nYRWjCYkjE;
      string NNqpYgpyWt;
      string ulyPIBoKtF;
      string wIMlutWXgT;
      string PsJXIotsBr;
      string BizLhCZBOi;
      string NOqdIEAFtd;
      string JSQDdCcaHT;
      string GuJBEMIBDs;
      string TUJyFBCePD;
      if(opbdLPOFri == nYRWjCYkjE){noyWhhRwhf = true;}
      else if(nYRWjCYkjE == opbdLPOFri){eizKRfpASY = true;}
      if(JElDugjBNZ == NNqpYgpyWt){ZzttbSEoZu = true;}
      else if(NNqpYgpyWt == JElDugjBNZ){IJPUedCnZt = true;}
      if(auJUDTtcpy == ulyPIBoKtF){uzBBKnJSxb = true;}
      else if(ulyPIBoKtF == auJUDTtcpy){hxwZgWoxHF = true;}
      if(ziZKPjsKRt == wIMlutWXgT){zxKDeQwmSV = true;}
      else if(wIMlutWXgT == ziZKPjsKRt){TSnpLeulrz = true;}
      if(cxPpESAFhX == PsJXIotsBr){tMSWTTZOVm = true;}
      else if(PsJXIotsBr == cxPpESAFhX){wsXVgTiGsR = true;}
      if(bJEghsgHaq == BizLhCZBOi){xMETIonxLt = true;}
      else if(BizLhCZBOi == bJEghsgHaq){sZmwJhlZdt = true;}
      if(VkPsiZebmL == NOqdIEAFtd){YzyFgbnqPK = true;}
      else if(NOqdIEAFtd == VkPsiZebmL){psrMFpUZJA = true;}
      if(mYjSxdeTPj == JSQDdCcaHT){VQVEBifehq = true;}
      if(SotRVoescW == GuJBEMIBDs){OtwKelsqup = true;}
      if(CljZYqgWGd == TUJyFBCePD){czbYwuONpr = true;}
      while(JSQDdCcaHT == mYjSxdeTPj){iQuayoYarM = true;}
      while(GuJBEMIBDs == GuJBEMIBDs){mhDoMsfrgd = true;}
      while(TUJyFBCePD == TUJyFBCePD){sVHyICALQq = true;}
      if(noyWhhRwhf == true){noyWhhRwhf = false;}
      if(ZzttbSEoZu == true){ZzttbSEoZu = false;}
      if(uzBBKnJSxb == true){uzBBKnJSxb = false;}
      if(zxKDeQwmSV == true){zxKDeQwmSV = false;}
      if(tMSWTTZOVm == true){tMSWTTZOVm = false;}
      if(xMETIonxLt == true){xMETIonxLt = false;}
      if(YzyFgbnqPK == true){YzyFgbnqPK = false;}
      if(VQVEBifehq == true){VQVEBifehq = false;}
      if(OtwKelsqup == true){OtwKelsqup = false;}
      if(czbYwuONpr == true){czbYwuONpr = false;}
      if(eizKRfpASY == true){eizKRfpASY = false;}
      if(IJPUedCnZt == true){IJPUedCnZt = false;}
      if(hxwZgWoxHF == true){hxwZgWoxHF = false;}
      if(TSnpLeulrz == true){TSnpLeulrz = false;}
      if(wsXVgTiGsR == true){wsXVgTiGsR = false;}
      if(sZmwJhlZdt == true){sZmwJhlZdt = false;}
      if(psrMFpUZJA == true){psrMFpUZJA = false;}
      if(iQuayoYarM == true){iQuayoYarM = false;}
      if(mhDoMsfrgd == true){mhDoMsfrgd = false;}
      if(sVHyICALQq == true){sVHyICALQq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JYWMYMCTHV
{ 
  void VNXzuyeOUV()
  { 
      bool xmifoWxaoG = false;
      bool ioNbRBTYFT = false;
      bool KpfwmIOtWa = false;
      bool NYKlIANPgA = false;
      bool DSdmahEXeA = false;
      bool hfUFqHGmsf = false;
      bool ICENsKdaTQ = false;
      bool nDrFQrMsVE = false;
      bool EqPVrgDEuA = false;
      bool sZWBrANPsP = false;
      bool EcDOMenOoy = false;
      bool tNRnbQmiUL = false;
      bool GYfSWNgqNQ = false;
      bool dwzFAbmAIN = false;
      bool snPwGfIhYa = false;
      bool MethJexkqz = false;
      bool xxBYUxNMnA = false;
      bool cmZHRRJiMq = false;
      bool EzRmDzCRuU = false;
      bool eCJJPwmpbI = false;
      string SWKtBoKfDZ;
      string UTUbISrudy;
      string LAdGPqXlat;
      string JRXlYtKRJd;
      string GmheujnCJQ;
      string JnhehRsDdK;
      string RYEIQCwiDN;
      string IZlzrXSzKf;
      string CUcKjUirDG;
      string BGnyMhiYNr;
      string mFzuHjCimJ;
      string ztryHwwtYu;
      string TEewMClmmJ;
      string otkSrxUgCA;
      string RAEtHGNopP;
      string lozSYiZDhF;
      string yPudTFIZFK;
      string aOqYcSzkoF;
      string nwwWXAtSsJ;
      string XRzwCCEaZC;
      if(SWKtBoKfDZ == mFzuHjCimJ){xmifoWxaoG = true;}
      else if(mFzuHjCimJ == SWKtBoKfDZ){EcDOMenOoy = true;}
      if(UTUbISrudy == ztryHwwtYu){ioNbRBTYFT = true;}
      else if(ztryHwwtYu == UTUbISrudy){tNRnbQmiUL = true;}
      if(LAdGPqXlat == TEewMClmmJ){KpfwmIOtWa = true;}
      else if(TEewMClmmJ == LAdGPqXlat){GYfSWNgqNQ = true;}
      if(JRXlYtKRJd == otkSrxUgCA){NYKlIANPgA = true;}
      else if(otkSrxUgCA == JRXlYtKRJd){dwzFAbmAIN = true;}
      if(GmheujnCJQ == RAEtHGNopP){DSdmahEXeA = true;}
      else if(RAEtHGNopP == GmheujnCJQ){snPwGfIhYa = true;}
      if(JnhehRsDdK == lozSYiZDhF){hfUFqHGmsf = true;}
      else if(lozSYiZDhF == JnhehRsDdK){MethJexkqz = true;}
      if(RYEIQCwiDN == yPudTFIZFK){ICENsKdaTQ = true;}
      else if(yPudTFIZFK == RYEIQCwiDN){xxBYUxNMnA = true;}
      if(IZlzrXSzKf == aOqYcSzkoF){nDrFQrMsVE = true;}
      if(CUcKjUirDG == nwwWXAtSsJ){EqPVrgDEuA = true;}
      if(BGnyMhiYNr == XRzwCCEaZC){sZWBrANPsP = true;}
      while(aOqYcSzkoF == IZlzrXSzKf){cmZHRRJiMq = true;}
      while(nwwWXAtSsJ == nwwWXAtSsJ){EzRmDzCRuU = true;}
      while(XRzwCCEaZC == XRzwCCEaZC){eCJJPwmpbI = true;}
      if(xmifoWxaoG == true){xmifoWxaoG = false;}
      if(ioNbRBTYFT == true){ioNbRBTYFT = false;}
      if(KpfwmIOtWa == true){KpfwmIOtWa = false;}
      if(NYKlIANPgA == true){NYKlIANPgA = false;}
      if(DSdmahEXeA == true){DSdmahEXeA = false;}
      if(hfUFqHGmsf == true){hfUFqHGmsf = false;}
      if(ICENsKdaTQ == true){ICENsKdaTQ = false;}
      if(nDrFQrMsVE == true){nDrFQrMsVE = false;}
      if(EqPVrgDEuA == true){EqPVrgDEuA = false;}
      if(sZWBrANPsP == true){sZWBrANPsP = false;}
      if(EcDOMenOoy == true){EcDOMenOoy = false;}
      if(tNRnbQmiUL == true){tNRnbQmiUL = false;}
      if(GYfSWNgqNQ == true){GYfSWNgqNQ = false;}
      if(dwzFAbmAIN == true){dwzFAbmAIN = false;}
      if(snPwGfIhYa == true){snPwGfIhYa = false;}
      if(MethJexkqz == true){MethJexkqz = false;}
      if(xxBYUxNMnA == true){xxBYUxNMnA = false;}
      if(cmZHRRJiMq == true){cmZHRRJiMq = false;}
      if(EzRmDzCRuU == true){EzRmDzCRuU = false;}
      if(eCJJPwmpbI == true){eCJJPwmpbI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUXRCSXGVU
{ 
  void WLNHmfUYZa()
  { 
      bool KJQedWPBEg = false;
      bool rKWwbLhqmH = false;
      bool dwiTZiChBx = false;
      bool VaPRkVuhNQ = false;
      bool edrpXylran = false;
      bool bBJpdOawEu = false;
      bool TgzGLQuELG = false;
      bool QAcWcADrwb = false;
      bool wJHNVTRYnW = false;
      bool tycRwxdleG = false;
      bool DhgTWaXmNc = false;
      bool KhzcyKZljq = false;
      bool yVQoLRWLZe = false;
      bool WRNoXOcmpu = false;
      bool ueLKLMzzSl = false;
      bool WqCmIgQqHF = false;
      bool DMMhGrTKEj = false;
      bool gmwnuSKFdz = false;
      bool SXrnIePagq = false;
      bool xlejqiScES = false;
      string RfoPKpTOBF;
      string cdALoGzjKj;
      string ARyJGUqTDT;
      string OLcnJlUXXW;
      string pHIQDNzsto;
      string LjlZpAheIo;
      string zAKgqQALCC;
      string kbLmtrIgFs;
      string VyYOHdZDxJ;
      string DoPiXpxaYm;
      string MmqqDjYyex;
      string qAYPSAawYN;
      string pwNsyuMcPD;
      string ugISfiHhKX;
      string FbYARDPAPX;
      string PACLwQYxrH;
      string XuibCJrFij;
      string srkBHOXNau;
      string fLNrntewWP;
      string JJoCzJswyI;
      if(RfoPKpTOBF == MmqqDjYyex){KJQedWPBEg = true;}
      else if(MmqqDjYyex == RfoPKpTOBF){DhgTWaXmNc = true;}
      if(cdALoGzjKj == qAYPSAawYN){rKWwbLhqmH = true;}
      else if(qAYPSAawYN == cdALoGzjKj){KhzcyKZljq = true;}
      if(ARyJGUqTDT == pwNsyuMcPD){dwiTZiChBx = true;}
      else if(pwNsyuMcPD == ARyJGUqTDT){yVQoLRWLZe = true;}
      if(OLcnJlUXXW == ugISfiHhKX){VaPRkVuhNQ = true;}
      else if(ugISfiHhKX == OLcnJlUXXW){WRNoXOcmpu = true;}
      if(pHIQDNzsto == FbYARDPAPX){edrpXylran = true;}
      else if(FbYARDPAPX == pHIQDNzsto){ueLKLMzzSl = true;}
      if(LjlZpAheIo == PACLwQYxrH){bBJpdOawEu = true;}
      else if(PACLwQYxrH == LjlZpAheIo){WqCmIgQqHF = true;}
      if(zAKgqQALCC == XuibCJrFij){TgzGLQuELG = true;}
      else if(XuibCJrFij == zAKgqQALCC){DMMhGrTKEj = true;}
      if(kbLmtrIgFs == srkBHOXNau){QAcWcADrwb = true;}
      if(VyYOHdZDxJ == fLNrntewWP){wJHNVTRYnW = true;}
      if(DoPiXpxaYm == JJoCzJswyI){tycRwxdleG = true;}
      while(srkBHOXNau == kbLmtrIgFs){gmwnuSKFdz = true;}
      while(fLNrntewWP == fLNrntewWP){SXrnIePagq = true;}
      while(JJoCzJswyI == JJoCzJswyI){xlejqiScES = true;}
      if(KJQedWPBEg == true){KJQedWPBEg = false;}
      if(rKWwbLhqmH == true){rKWwbLhqmH = false;}
      if(dwiTZiChBx == true){dwiTZiChBx = false;}
      if(VaPRkVuhNQ == true){VaPRkVuhNQ = false;}
      if(edrpXylran == true){edrpXylran = false;}
      if(bBJpdOawEu == true){bBJpdOawEu = false;}
      if(TgzGLQuELG == true){TgzGLQuELG = false;}
      if(QAcWcADrwb == true){QAcWcADrwb = false;}
      if(wJHNVTRYnW == true){wJHNVTRYnW = false;}
      if(tycRwxdleG == true){tycRwxdleG = false;}
      if(DhgTWaXmNc == true){DhgTWaXmNc = false;}
      if(KhzcyKZljq == true){KhzcyKZljq = false;}
      if(yVQoLRWLZe == true){yVQoLRWLZe = false;}
      if(WRNoXOcmpu == true){WRNoXOcmpu = false;}
      if(ueLKLMzzSl == true){ueLKLMzzSl = false;}
      if(WqCmIgQqHF == true){WqCmIgQqHF = false;}
      if(DMMhGrTKEj == true){DMMhGrTKEj = false;}
      if(gmwnuSKFdz == true){gmwnuSKFdz = false;}
      if(SXrnIePagq == true){SXrnIePagq = false;}
      if(xlejqiScES == true){xlejqiScES = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZQXBANNWNU
{ 
  void zQcDiZwLHX()
  { 
      bool LKOVprZLZs = false;
      bool JywRplaZHV = false;
      bool xSdLxBzOKh = false;
      bool ucWegBnDRi = false;
      bool pQSxdORJQr = false;
      bool qqNUErgCXo = false;
      bool sLAryfaRjo = false;
      bool yXHXegzfhh = false;
      bool jpySpDOBZn = false;
      bool TkecoePayx = false;
      bool mzYbsTiooX = false;
      bool sBUpECMgBu = false;
      bool RZruUNreiA = false;
      bool QYhjtjRWZW = false;
      bool TZLBuSQoXm = false;
      bool RiYDfNHdGe = false;
      bool bEGoGUTjuU = false;
      bool kpGebqNpAC = false;
      bool wCHuhhzdEg = false;
      bool cmPutPSVuZ = false;
      string ctaBPwcesq;
      string hWtOOXnxff;
      string IjArADIErI;
      string zYmXYwgMbB;
      string EQulbtZdrl;
      string haaFsrshBM;
      string mYmjrJjWpS;
      string qbUdaroNPF;
      string ceLFZYxhef;
      string CyKPOfdKtS;
      string JDmZuGFxdA;
      string DfSujHMgJT;
      string LCqJPrQFOu;
      string NdTxuYrkKT;
      string SzDdcWfOfG;
      string TxBaGHLdKC;
      string oAhimZLUAK;
      string PaWoAMyNgr;
      string MCYIbQbsqn;
      string MNaHdSRUqC;
      if(ctaBPwcesq == JDmZuGFxdA){LKOVprZLZs = true;}
      else if(JDmZuGFxdA == ctaBPwcesq){mzYbsTiooX = true;}
      if(hWtOOXnxff == DfSujHMgJT){JywRplaZHV = true;}
      else if(DfSujHMgJT == hWtOOXnxff){sBUpECMgBu = true;}
      if(IjArADIErI == LCqJPrQFOu){xSdLxBzOKh = true;}
      else if(LCqJPrQFOu == IjArADIErI){RZruUNreiA = true;}
      if(zYmXYwgMbB == NdTxuYrkKT){ucWegBnDRi = true;}
      else if(NdTxuYrkKT == zYmXYwgMbB){QYhjtjRWZW = true;}
      if(EQulbtZdrl == SzDdcWfOfG){pQSxdORJQr = true;}
      else if(SzDdcWfOfG == EQulbtZdrl){TZLBuSQoXm = true;}
      if(haaFsrshBM == TxBaGHLdKC){qqNUErgCXo = true;}
      else if(TxBaGHLdKC == haaFsrshBM){RiYDfNHdGe = true;}
      if(mYmjrJjWpS == oAhimZLUAK){sLAryfaRjo = true;}
      else if(oAhimZLUAK == mYmjrJjWpS){bEGoGUTjuU = true;}
      if(qbUdaroNPF == PaWoAMyNgr){yXHXegzfhh = true;}
      if(ceLFZYxhef == MCYIbQbsqn){jpySpDOBZn = true;}
      if(CyKPOfdKtS == MNaHdSRUqC){TkecoePayx = true;}
      while(PaWoAMyNgr == qbUdaroNPF){kpGebqNpAC = true;}
      while(MCYIbQbsqn == MCYIbQbsqn){wCHuhhzdEg = true;}
      while(MNaHdSRUqC == MNaHdSRUqC){cmPutPSVuZ = true;}
      if(LKOVprZLZs == true){LKOVprZLZs = false;}
      if(JywRplaZHV == true){JywRplaZHV = false;}
      if(xSdLxBzOKh == true){xSdLxBzOKh = false;}
      if(ucWegBnDRi == true){ucWegBnDRi = false;}
      if(pQSxdORJQr == true){pQSxdORJQr = false;}
      if(qqNUErgCXo == true){qqNUErgCXo = false;}
      if(sLAryfaRjo == true){sLAryfaRjo = false;}
      if(yXHXegzfhh == true){yXHXegzfhh = false;}
      if(jpySpDOBZn == true){jpySpDOBZn = false;}
      if(TkecoePayx == true){TkecoePayx = false;}
      if(mzYbsTiooX == true){mzYbsTiooX = false;}
      if(sBUpECMgBu == true){sBUpECMgBu = false;}
      if(RZruUNreiA == true){RZruUNreiA = false;}
      if(QYhjtjRWZW == true){QYhjtjRWZW = false;}
      if(TZLBuSQoXm == true){TZLBuSQoXm = false;}
      if(RiYDfNHdGe == true){RiYDfNHdGe = false;}
      if(bEGoGUTjuU == true){bEGoGUTjuU = false;}
      if(kpGebqNpAC == true){kpGebqNpAC = false;}
      if(wCHuhhzdEg == true){wCHuhhzdEg = false;}
      if(cmPutPSVuZ == true){cmPutPSVuZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBEDLLKGJT
{ 
  void zjSVtqRWHO()
  { 
      bool QdyiFtdDqp = false;
      bool dxjCRmOPsO = false;
      bool qXMxFYaXJa = false;
      bool XJnkfKOMSO = false;
      bool JDUMqYkIYa = false;
      bool knaRMrQBcf = false;
      bool TGtPSUIzVH = false;
      bool YBxdEmCAFg = false;
      bool nRzipiiVYm = false;
      bool tMjmuDJFtW = false;
      bool PklRBjqwNY = false;
      bool pPwuqBGKYi = false;
      bool klZhMLQKiB = false;
      bool dxFhQCeggF = false;
      bool rlIzxdQnus = false;
      bool wygKkcKEEo = false;
      bool SfMLtrKNen = false;
      bool VZdSqzcaki = false;
      bool tbOpEfPuwm = false;
      bool qacrmLYxEE = false;
      string NyFJzrYiww;
      string wwVcbixyyu;
      string omBOVQtUlQ;
      string gZbtGNVDLl;
      string dCrSIeBkMA;
      string XEWKXZxqnh;
      string xDweOWTbWO;
      string MslLQmthGp;
      string PIIkscCRVg;
      string PePdnaFMEk;
      string LZOyndSKsk;
      string eOkySnuLll;
      string TCGpyhdHWp;
      string hhdUeptJwO;
      string KrXjBBsRLz;
      string fsaRRISYzF;
      string AKmDDxjPSc;
      string tkOXabdVnx;
      string nMwXJnGLCV;
      string WUKpNzEUgD;
      if(NyFJzrYiww == LZOyndSKsk){QdyiFtdDqp = true;}
      else if(LZOyndSKsk == NyFJzrYiww){PklRBjqwNY = true;}
      if(wwVcbixyyu == eOkySnuLll){dxjCRmOPsO = true;}
      else if(eOkySnuLll == wwVcbixyyu){pPwuqBGKYi = true;}
      if(omBOVQtUlQ == TCGpyhdHWp){qXMxFYaXJa = true;}
      else if(TCGpyhdHWp == omBOVQtUlQ){klZhMLQKiB = true;}
      if(gZbtGNVDLl == hhdUeptJwO){XJnkfKOMSO = true;}
      else if(hhdUeptJwO == gZbtGNVDLl){dxFhQCeggF = true;}
      if(dCrSIeBkMA == KrXjBBsRLz){JDUMqYkIYa = true;}
      else if(KrXjBBsRLz == dCrSIeBkMA){rlIzxdQnus = true;}
      if(XEWKXZxqnh == fsaRRISYzF){knaRMrQBcf = true;}
      else if(fsaRRISYzF == XEWKXZxqnh){wygKkcKEEo = true;}
      if(xDweOWTbWO == AKmDDxjPSc){TGtPSUIzVH = true;}
      else if(AKmDDxjPSc == xDweOWTbWO){SfMLtrKNen = true;}
      if(MslLQmthGp == tkOXabdVnx){YBxdEmCAFg = true;}
      if(PIIkscCRVg == nMwXJnGLCV){nRzipiiVYm = true;}
      if(PePdnaFMEk == WUKpNzEUgD){tMjmuDJFtW = true;}
      while(tkOXabdVnx == MslLQmthGp){VZdSqzcaki = true;}
      while(nMwXJnGLCV == nMwXJnGLCV){tbOpEfPuwm = true;}
      while(WUKpNzEUgD == WUKpNzEUgD){qacrmLYxEE = true;}
      if(QdyiFtdDqp == true){QdyiFtdDqp = false;}
      if(dxjCRmOPsO == true){dxjCRmOPsO = false;}
      if(qXMxFYaXJa == true){qXMxFYaXJa = false;}
      if(XJnkfKOMSO == true){XJnkfKOMSO = false;}
      if(JDUMqYkIYa == true){JDUMqYkIYa = false;}
      if(knaRMrQBcf == true){knaRMrQBcf = false;}
      if(TGtPSUIzVH == true){TGtPSUIzVH = false;}
      if(YBxdEmCAFg == true){YBxdEmCAFg = false;}
      if(nRzipiiVYm == true){nRzipiiVYm = false;}
      if(tMjmuDJFtW == true){tMjmuDJFtW = false;}
      if(PklRBjqwNY == true){PklRBjqwNY = false;}
      if(pPwuqBGKYi == true){pPwuqBGKYi = false;}
      if(klZhMLQKiB == true){klZhMLQKiB = false;}
      if(dxFhQCeggF == true){dxFhQCeggF = false;}
      if(rlIzxdQnus == true){rlIzxdQnus = false;}
      if(wygKkcKEEo == true){wygKkcKEEo = false;}
      if(SfMLtrKNen == true){SfMLtrKNen = false;}
      if(VZdSqzcaki == true){VZdSqzcaki = false;}
      if(tbOpEfPuwm == true){tbOpEfPuwm = false;}
      if(qacrmLYxEE == true){qacrmLYxEE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YCUVWKKLBC
{ 
  void sjTHfxsUDx()
  { 
      bool kGViMHMlub = false;
      bool kuOqwwHywr = false;
      bool yUkqkTMDqV = false;
      bool fYQjenmlHN = false;
      bool kcMWuXTVbN = false;
      bool ZQPYfQUeys = false;
      bool tIuYwMddMH = false;
      bool IUphGVIOuN = false;
      bool ApbcuPJqEO = false;
      bool TInOTbhmai = false;
      bool soJTFFZgRJ = false;
      bool HFijrDgSdg = false;
      bool CmZymzfbOe = false;
      bool nVnMULgHXp = false;
      bool obYtGNZEWP = false;
      bool uPJtfGOLgF = false;
      bool YySmVlRVPf = false;
      bool WZtmqaNerY = false;
      bool ZbEyjYLtgN = false;
      bool wVaRRqIlYT = false;
      string oyNNZIYlyx;
      string SVwHYJLExR;
      string aLuktIzUEF;
      string jCFXnzZnGk;
      string iLAaPDrDMM;
      string flQEpcCbSR;
      string IEhrNPQXSZ;
      string iXyMiOLTVq;
      string QuHrZylAhK;
      string wxUobedHNA;
      string mTklcImDVa;
      string RhGbAMwpSO;
      string cPpHdlCJjD;
      string kDGVDwKVOQ;
      string LhdHsNqsnO;
      string hmnyWWdcHq;
      string FcTRoObkXE;
      string CaaCDtkhOQ;
      string tJVUVxPHzg;
      string ShNXKhOMRe;
      if(oyNNZIYlyx == mTklcImDVa){kGViMHMlub = true;}
      else if(mTklcImDVa == oyNNZIYlyx){soJTFFZgRJ = true;}
      if(SVwHYJLExR == RhGbAMwpSO){kuOqwwHywr = true;}
      else if(RhGbAMwpSO == SVwHYJLExR){HFijrDgSdg = true;}
      if(aLuktIzUEF == cPpHdlCJjD){yUkqkTMDqV = true;}
      else if(cPpHdlCJjD == aLuktIzUEF){CmZymzfbOe = true;}
      if(jCFXnzZnGk == kDGVDwKVOQ){fYQjenmlHN = true;}
      else if(kDGVDwKVOQ == jCFXnzZnGk){nVnMULgHXp = true;}
      if(iLAaPDrDMM == LhdHsNqsnO){kcMWuXTVbN = true;}
      else if(LhdHsNqsnO == iLAaPDrDMM){obYtGNZEWP = true;}
      if(flQEpcCbSR == hmnyWWdcHq){ZQPYfQUeys = true;}
      else if(hmnyWWdcHq == flQEpcCbSR){uPJtfGOLgF = true;}
      if(IEhrNPQXSZ == FcTRoObkXE){tIuYwMddMH = true;}
      else if(FcTRoObkXE == IEhrNPQXSZ){YySmVlRVPf = true;}
      if(iXyMiOLTVq == CaaCDtkhOQ){IUphGVIOuN = true;}
      if(QuHrZylAhK == tJVUVxPHzg){ApbcuPJqEO = true;}
      if(wxUobedHNA == ShNXKhOMRe){TInOTbhmai = true;}
      while(CaaCDtkhOQ == iXyMiOLTVq){WZtmqaNerY = true;}
      while(tJVUVxPHzg == tJVUVxPHzg){ZbEyjYLtgN = true;}
      while(ShNXKhOMRe == ShNXKhOMRe){wVaRRqIlYT = true;}
      if(kGViMHMlub == true){kGViMHMlub = false;}
      if(kuOqwwHywr == true){kuOqwwHywr = false;}
      if(yUkqkTMDqV == true){yUkqkTMDqV = false;}
      if(fYQjenmlHN == true){fYQjenmlHN = false;}
      if(kcMWuXTVbN == true){kcMWuXTVbN = false;}
      if(ZQPYfQUeys == true){ZQPYfQUeys = false;}
      if(tIuYwMddMH == true){tIuYwMddMH = false;}
      if(IUphGVIOuN == true){IUphGVIOuN = false;}
      if(ApbcuPJqEO == true){ApbcuPJqEO = false;}
      if(TInOTbhmai == true){TInOTbhmai = false;}
      if(soJTFFZgRJ == true){soJTFFZgRJ = false;}
      if(HFijrDgSdg == true){HFijrDgSdg = false;}
      if(CmZymzfbOe == true){CmZymzfbOe = false;}
      if(nVnMULgHXp == true){nVnMULgHXp = false;}
      if(obYtGNZEWP == true){obYtGNZEWP = false;}
      if(uPJtfGOLgF == true){uPJtfGOLgF = false;}
      if(YySmVlRVPf == true){YySmVlRVPf = false;}
      if(WZtmqaNerY == true){WZtmqaNerY = false;}
      if(ZbEyjYLtgN == true){ZbEyjYLtgN = false;}
      if(wVaRRqIlYT == true){wVaRRqIlYT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VYXEHDDZSQ
{ 
  void TXGitbkHHH()
  { 
      bool yTThkaRhnc = false;
      bool UYgqUoVcCY = false;
      bool KoGIDOlrZP = false;
      bool oqJTFXyzwM = false;
      bool NRYNfxgTPm = false;
      bool GpfTfIMLeV = false;
      bool oYIXndOMlx = false;
      bool pVfoKrQscF = false;
      bool gSclJyKpmw = false;
      bool KmUaXnIAZB = false;
      bool hUhRwjKpIn = false;
      bool rTiYoWwVNo = false;
      bool TYYomDBFRW = false;
      bool iPTaXLjLoZ = false;
      bool nThzEqEulA = false;
      bool rlmkgJwres = false;
      bool hEYlEbAHBc = false;
      bool lkfnAzpYku = false;
      bool yGTRdxchsN = false;
      bool Prgwqiuwub = false;
      string GlnAfXNqCk;
      string KxmMigJBkd;
      string ODuGHgcDua;
      string nkWIAkccer;
      string mRxzASGRxa;
      string lPztdCphsy;
      string tJuawZaeLy;
      string EgWrpxGwFn;
      string aLFUoYkcdy;
      string ttifxcVVDa;
      string rbFzWFsGDf;
      string wtbFXiEalW;
      string nyANDJxpuM;
      string akrduyGGxj;
      string eeYxCARdIN;
      string YujfmtbruM;
      string HDKpFKByJZ;
      string cxcBrJYCLD;
      string qShhnfAMqB;
      string WNLkbbThrq;
      if(GlnAfXNqCk == rbFzWFsGDf){yTThkaRhnc = true;}
      else if(rbFzWFsGDf == GlnAfXNqCk){hUhRwjKpIn = true;}
      if(KxmMigJBkd == wtbFXiEalW){UYgqUoVcCY = true;}
      else if(wtbFXiEalW == KxmMigJBkd){rTiYoWwVNo = true;}
      if(ODuGHgcDua == nyANDJxpuM){KoGIDOlrZP = true;}
      else if(nyANDJxpuM == ODuGHgcDua){TYYomDBFRW = true;}
      if(nkWIAkccer == akrduyGGxj){oqJTFXyzwM = true;}
      else if(akrduyGGxj == nkWIAkccer){iPTaXLjLoZ = true;}
      if(mRxzASGRxa == eeYxCARdIN){NRYNfxgTPm = true;}
      else if(eeYxCARdIN == mRxzASGRxa){nThzEqEulA = true;}
      if(lPztdCphsy == YujfmtbruM){GpfTfIMLeV = true;}
      else if(YujfmtbruM == lPztdCphsy){rlmkgJwres = true;}
      if(tJuawZaeLy == HDKpFKByJZ){oYIXndOMlx = true;}
      else if(HDKpFKByJZ == tJuawZaeLy){hEYlEbAHBc = true;}
      if(EgWrpxGwFn == cxcBrJYCLD){pVfoKrQscF = true;}
      if(aLFUoYkcdy == qShhnfAMqB){gSclJyKpmw = true;}
      if(ttifxcVVDa == WNLkbbThrq){KmUaXnIAZB = true;}
      while(cxcBrJYCLD == EgWrpxGwFn){lkfnAzpYku = true;}
      while(qShhnfAMqB == qShhnfAMqB){yGTRdxchsN = true;}
      while(WNLkbbThrq == WNLkbbThrq){Prgwqiuwub = true;}
      if(yTThkaRhnc == true){yTThkaRhnc = false;}
      if(UYgqUoVcCY == true){UYgqUoVcCY = false;}
      if(KoGIDOlrZP == true){KoGIDOlrZP = false;}
      if(oqJTFXyzwM == true){oqJTFXyzwM = false;}
      if(NRYNfxgTPm == true){NRYNfxgTPm = false;}
      if(GpfTfIMLeV == true){GpfTfIMLeV = false;}
      if(oYIXndOMlx == true){oYIXndOMlx = false;}
      if(pVfoKrQscF == true){pVfoKrQscF = false;}
      if(gSclJyKpmw == true){gSclJyKpmw = false;}
      if(KmUaXnIAZB == true){KmUaXnIAZB = false;}
      if(hUhRwjKpIn == true){hUhRwjKpIn = false;}
      if(rTiYoWwVNo == true){rTiYoWwVNo = false;}
      if(TYYomDBFRW == true){TYYomDBFRW = false;}
      if(iPTaXLjLoZ == true){iPTaXLjLoZ = false;}
      if(nThzEqEulA == true){nThzEqEulA = false;}
      if(rlmkgJwres == true){rlmkgJwres = false;}
      if(hEYlEbAHBc == true){hEYlEbAHBc = false;}
      if(lkfnAzpYku == true){lkfnAzpYku = false;}
      if(yGTRdxchsN == true){yGTRdxchsN = false;}
      if(Prgwqiuwub == true){Prgwqiuwub = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GYCBPFKFLM
{ 
  void XgnIUcnQLJ()
  { 
      bool xoiSecKXwB = false;
      bool jHqjBbfofE = false;
      bool UsZZNrZpBt = false;
      bool pamLtnjhpn = false;
      bool wERexFJPpE = false;
      bool hYeYiEOJEl = false;
      bool DUWBLITfoM = false;
      bool rxyqHQbubH = false;
      bool iJAxLQwOco = false;
      bool ZZcEkbhPTo = false;
      bool lcZcLkZnQR = false;
      bool bThxDtTYot = false;
      bool MFDAmRTsGf = false;
      bool hLblVFiXka = false;
      bool qIxKNFrfBp = false;
      bool HIZZbfZZot = false;
      bool QfgjiPrubx = false;
      bool LwmODEIrlg = false;
      bool ZnrPYZkBJo = false;
      bool eIhqJKaMax = false;
      string mNLufhBdtX;
      string AuQNKMyjUf;
      string bHLCMCCAxB;
      string xwWJNhykjD;
      string FeIijplXAT;
      string TbUtIeCJhd;
      string eBgrZDYGzb;
      string OMAQZxybRW;
      string QezchVbcAh;
      string enCGXExPJf;
      string ReXXFGaDTL;
      string fZrLMABEJD;
      string buGQwZKtsV;
      string ziSkElHbWb;
      string uXJoBEwqsX;
      string DrFFEWYGae;
      string ugKyLxHGHa;
      string sZhhIDlQPq;
      string dTAVRHcNfh;
      string NAAqfONKdD;
      if(mNLufhBdtX == ReXXFGaDTL){xoiSecKXwB = true;}
      else if(ReXXFGaDTL == mNLufhBdtX){lcZcLkZnQR = true;}
      if(AuQNKMyjUf == fZrLMABEJD){jHqjBbfofE = true;}
      else if(fZrLMABEJD == AuQNKMyjUf){bThxDtTYot = true;}
      if(bHLCMCCAxB == buGQwZKtsV){UsZZNrZpBt = true;}
      else if(buGQwZKtsV == bHLCMCCAxB){MFDAmRTsGf = true;}
      if(xwWJNhykjD == ziSkElHbWb){pamLtnjhpn = true;}
      else if(ziSkElHbWb == xwWJNhykjD){hLblVFiXka = true;}
      if(FeIijplXAT == uXJoBEwqsX){wERexFJPpE = true;}
      else if(uXJoBEwqsX == FeIijplXAT){qIxKNFrfBp = true;}
      if(TbUtIeCJhd == DrFFEWYGae){hYeYiEOJEl = true;}
      else if(DrFFEWYGae == TbUtIeCJhd){HIZZbfZZot = true;}
      if(eBgrZDYGzb == ugKyLxHGHa){DUWBLITfoM = true;}
      else if(ugKyLxHGHa == eBgrZDYGzb){QfgjiPrubx = true;}
      if(OMAQZxybRW == sZhhIDlQPq){rxyqHQbubH = true;}
      if(QezchVbcAh == dTAVRHcNfh){iJAxLQwOco = true;}
      if(enCGXExPJf == NAAqfONKdD){ZZcEkbhPTo = true;}
      while(sZhhIDlQPq == OMAQZxybRW){LwmODEIrlg = true;}
      while(dTAVRHcNfh == dTAVRHcNfh){ZnrPYZkBJo = true;}
      while(NAAqfONKdD == NAAqfONKdD){eIhqJKaMax = true;}
      if(xoiSecKXwB == true){xoiSecKXwB = false;}
      if(jHqjBbfofE == true){jHqjBbfofE = false;}
      if(UsZZNrZpBt == true){UsZZNrZpBt = false;}
      if(pamLtnjhpn == true){pamLtnjhpn = false;}
      if(wERexFJPpE == true){wERexFJPpE = false;}
      if(hYeYiEOJEl == true){hYeYiEOJEl = false;}
      if(DUWBLITfoM == true){DUWBLITfoM = false;}
      if(rxyqHQbubH == true){rxyqHQbubH = false;}
      if(iJAxLQwOco == true){iJAxLQwOco = false;}
      if(ZZcEkbhPTo == true){ZZcEkbhPTo = false;}
      if(lcZcLkZnQR == true){lcZcLkZnQR = false;}
      if(bThxDtTYot == true){bThxDtTYot = false;}
      if(MFDAmRTsGf == true){MFDAmRTsGf = false;}
      if(hLblVFiXka == true){hLblVFiXka = false;}
      if(qIxKNFrfBp == true){qIxKNFrfBp = false;}
      if(HIZZbfZZot == true){HIZZbfZZot = false;}
      if(QfgjiPrubx == true){QfgjiPrubx = false;}
      if(LwmODEIrlg == true){LwmODEIrlg = false;}
      if(ZnrPYZkBJo == true){ZnrPYZkBJo = false;}
      if(eIhqJKaMax == true){eIhqJKaMax = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BHHRHSGMGI
{ 
  void HKHZfkNyyU()
  { 
      bool AWKqnfufjr = false;
      bool KIsZSViMtA = false;
      bool otZCifLQUO = false;
      bool DzYPCcmtLk = false;
      bool aLGArkFEXo = false;
      bool AtmShGwHHI = false;
      bool TdKUoKidWo = false;
      bool inBIYcmZKx = false;
      bool ZGseNIMFgw = false;
      bool felCQwAkKg = false;
      bool CahhGLrdsE = false;
      bool TVxJhNkfGf = false;
      bool ycwaJEBzqc = false;
      bool bBPduzYKXB = false;
      bool PhLbbJgcTD = false;
      bool KUddhYeGYC = false;
      bool KslQcRGSNi = false;
      bool naIFQQRTyz = false;
      bool WYfnRHWkuW = false;
      bool TSkUqWuuzK = false;
      string dteJnQGByl;
      string DTxdwpKzhI;
      string xTbmwjFeTa;
      string FZCcyMudym;
      string yCtRKiEDCC;
      string NaZJqJSqME;
      string LbhXgdRUfi;
      string tfAtKtZJcM;
      string eCbQMdzrln;
      string tERtbWUVkg;
      string RjXSHhZfzw;
      string jIOAYIzQKC;
      string dZhqooOGSn;
      string ZDYutueIIe;
      string DTrpEkpQUS;
      string WDLhCrBfdR;
      string TTMLVgjSFd;
      string dpHfyKgrmD;
      string zxkzQVqprC;
      string tyepLjHgTW;
      if(dteJnQGByl == RjXSHhZfzw){AWKqnfufjr = true;}
      else if(RjXSHhZfzw == dteJnQGByl){CahhGLrdsE = true;}
      if(DTxdwpKzhI == jIOAYIzQKC){KIsZSViMtA = true;}
      else if(jIOAYIzQKC == DTxdwpKzhI){TVxJhNkfGf = true;}
      if(xTbmwjFeTa == dZhqooOGSn){otZCifLQUO = true;}
      else if(dZhqooOGSn == xTbmwjFeTa){ycwaJEBzqc = true;}
      if(FZCcyMudym == ZDYutueIIe){DzYPCcmtLk = true;}
      else if(ZDYutueIIe == FZCcyMudym){bBPduzYKXB = true;}
      if(yCtRKiEDCC == DTrpEkpQUS){aLGArkFEXo = true;}
      else if(DTrpEkpQUS == yCtRKiEDCC){PhLbbJgcTD = true;}
      if(NaZJqJSqME == WDLhCrBfdR){AtmShGwHHI = true;}
      else if(WDLhCrBfdR == NaZJqJSqME){KUddhYeGYC = true;}
      if(LbhXgdRUfi == TTMLVgjSFd){TdKUoKidWo = true;}
      else if(TTMLVgjSFd == LbhXgdRUfi){KslQcRGSNi = true;}
      if(tfAtKtZJcM == dpHfyKgrmD){inBIYcmZKx = true;}
      if(eCbQMdzrln == zxkzQVqprC){ZGseNIMFgw = true;}
      if(tERtbWUVkg == tyepLjHgTW){felCQwAkKg = true;}
      while(dpHfyKgrmD == tfAtKtZJcM){naIFQQRTyz = true;}
      while(zxkzQVqprC == zxkzQVqprC){WYfnRHWkuW = true;}
      while(tyepLjHgTW == tyepLjHgTW){TSkUqWuuzK = true;}
      if(AWKqnfufjr == true){AWKqnfufjr = false;}
      if(KIsZSViMtA == true){KIsZSViMtA = false;}
      if(otZCifLQUO == true){otZCifLQUO = false;}
      if(DzYPCcmtLk == true){DzYPCcmtLk = false;}
      if(aLGArkFEXo == true){aLGArkFEXo = false;}
      if(AtmShGwHHI == true){AtmShGwHHI = false;}
      if(TdKUoKidWo == true){TdKUoKidWo = false;}
      if(inBIYcmZKx == true){inBIYcmZKx = false;}
      if(ZGseNIMFgw == true){ZGseNIMFgw = false;}
      if(felCQwAkKg == true){felCQwAkKg = false;}
      if(CahhGLrdsE == true){CahhGLrdsE = false;}
      if(TVxJhNkfGf == true){TVxJhNkfGf = false;}
      if(ycwaJEBzqc == true){ycwaJEBzqc = false;}
      if(bBPduzYKXB == true){bBPduzYKXB = false;}
      if(PhLbbJgcTD == true){PhLbbJgcTD = false;}
      if(KUddhYeGYC == true){KUddhYeGYC = false;}
      if(KslQcRGSNi == true){KslQcRGSNi = false;}
      if(naIFQQRTyz == true){naIFQQRTyz = false;}
      if(WYfnRHWkuW == true){WYfnRHWkuW = false;}
      if(TSkUqWuuzK == true){TSkUqWuuzK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IKHVHKWPUF
{ 
  void dCVlBMyCRq()
  { 
      bool OusdxfMeIE = false;
      bool JONKDtfjgR = false;
      bool MQDPlfkDQq = false;
      bool BOnklKtHAg = false;
      bool oexhtNhClL = false;
      bool ERKzxxrcrQ = false;
      bool uJORDuabXs = false;
      bool AXjAbgSVUX = false;
      bool yhRFmiEnnn = false;
      bool SQPjkeQfdz = false;
      bool lFdrLfhKWP = false;
      bool dVITRNqIdU = false;
      bool qmnjaiHAPw = false;
      bool PmqUkrDYtG = false;
      bool BsQXKwIwRX = false;
      bool nICJIzRtRb = false;
      bool YguZzqemhZ = false;
      bool JROXTxVPYe = false;
      bool aLirIHjhMk = false;
      bool ZJHRhTypYT = false;
      string kOBfpGDQqD;
      string ETwfNYeKMj;
      string zXsUJUeLWI;
      string cZBthXGaah;
      string rsunbbMlnU;
      string lfjdhNUfWU;
      string arthZdRByp;
      string SEjdrGbFsg;
      string IsWBVxpXLT;
      string CZDFHAyNNx;
      string KKnyChwFla;
      string lPmpMhVrLc;
      string nspdmrAdWq;
      string HNqwVxFXzn;
      string BkljhmmNsZ;
      string dGCjIQUJKJ;
      string hRhtSXXqTO;
      string bxsWbDGFuA;
      string FmkxMBKGmE;
      string cuMoGjCrRK;
      if(kOBfpGDQqD == KKnyChwFla){OusdxfMeIE = true;}
      else if(KKnyChwFla == kOBfpGDQqD){lFdrLfhKWP = true;}
      if(ETwfNYeKMj == lPmpMhVrLc){JONKDtfjgR = true;}
      else if(lPmpMhVrLc == ETwfNYeKMj){dVITRNqIdU = true;}
      if(zXsUJUeLWI == nspdmrAdWq){MQDPlfkDQq = true;}
      else if(nspdmrAdWq == zXsUJUeLWI){qmnjaiHAPw = true;}
      if(cZBthXGaah == HNqwVxFXzn){BOnklKtHAg = true;}
      else if(HNqwVxFXzn == cZBthXGaah){PmqUkrDYtG = true;}
      if(rsunbbMlnU == BkljhmmNsZ){oexhtNhClL = true;}
      else if(BkljhmmNsZ == rsunbbMlnU){BsQXKwIwRX = true;}
      if(lfjdhNUfWU == dGCjIQUJKJ){ERKzxxrcrQ = true;}
      else if(dGCjIQUJKJ == lfjdhNUfWU){nICJIzRtRb = true;}
      if(arthZdRByp == hRhtSXXqTO){uJORDuabXs = true;}
      else if(hRhtSXXqTO == arthZdRByp){YguZzqemhZ = true;}
      if(SEjdrGbFsg == bxsWbDGFuA){AXjAbgSVUX = true;}
      if(IsWBVxpXLT == FmkxMBKGmE){yhRFmiEnnn = true;}
      if(CZDFHAyNNx == cuMoGjCrRK){SQPjkeQfdz = true;}
      while(bxsWbDGFuA == SEjdrGbFsg){JROXTxVPYe = true;}
      while(FmkxMBKGmE == FmkxMBKGmE){aLirIHjhMk = true;}
      while(cuMoGjCrRK == cuMoGjCrRK){ZJHRhTypYT = true;}
      if(OusdxfMeIE == true){OusdxfMeIE = false;}
      if(JONKDtfjgR == true){JONKDtfjgR = false;}
      if(MQDPlfkDQq == true){MQDPlfkDQq = false;}
      if(BOnklKtHAg == true){BOnklKtHAg = false;}
      if(oexhtNhClL == true){oexhtNhClL = false;}
      if(ERKzxxrcrQ == true){ERKzxxrcrQ = false;}
      if(uJORDuabXs == true){uJORDuabXs = false;}
      if(AXjAbgSVUX == true){AXjAbgSVUX = false;}
      if(yhRFmiEnnn == true){yhRFmiEnnn = false;}
      if(SQPjkeQfdz == true){SQPjkeQfdz = false;}
      if(lFdrLfhKWP == true){lFdrLfhKWP = false;}
      if(dVITRNqIdU == true){dVITRNqIdU = false;}
      if(qmnjaiHAPw == true){qmnjaiHAPw = false;}
      if(PmqUkrDYtG == true){PmqUkrDYtG = false;}
      if(BsQXKwIwRX == true){BsQXKwIwRX = false;}
      if(nICJIzRtRb == true){nICJIzRtRb = false;}
      if(YguZzqemhZ == true){YguZzqemhZ = false;}
      if(JROXTxVPYe == true){JROXTxVPYe = false;}
      if(aLirIHjhMk == true){aLirIHjhMk = false;}
      if(ZJHRhTypYT == true){ZJHRhTypYT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class USBNIDNUQU
{ 
  void SFqLUQHYpD()
  { 
      bool PQGbPaFCoP = false;
      bool SuoQEMbAKp = false;
      bool qWPqRhRuuA = false;
      bool GTwzCDdCDQ = false;
      bool fAWqfqqxhf = false;
      bool xYYHnsBPKh = false;
      bool IKHnJzyoNA = false;
      bool hYwtKqAYKZ = false;
      bool pUNPCguoKJ = false;
      bool COrVHUshhg = false;
      bool sBigxYcdwx = false;
      bool rbEkqnxrlb = false;
      bool DJeEyTgZlo = false;
      bool xSpdfnlfRd = false;
      bool DQrNRZKGeT = false;
      bool XBwFcjWdid = false;
      bool qCrHzYkZED = false;
      bool CQZHYmQQmX = false;
      bool JZuSQwWkBw = false;
      bool QHwnlBYkNr = false;
      string AXZcBfDnym;
      string DBfAqkAxlq;
      string cqRaelibAu;
      string kTVkaPMIar;
      string KUZWDsCDdG;
      string XnKhJIFyyO;
      string xamCCietZb;
      string XrWsgHRuXk;
      string ifytWwJnaR;
      string JOJLuihWUU;
      string OHcBhfQQAB;
      string pKZMeRcseF;
      string YqSHRJhKxy;
      string ZuaDWaCxLq;
      string esmYbznxfd;
      string GnqOuWnViY;
      string yGTCbuiWpD;
      string OfhnZfEsfS;
      string UkeSqlDLHz;
      string lgNlsYZjxf;
      if(AXZcBfDnym == OHcBhfQQAB){PQGbPaFCoP = true;}
      else if(OHcBhfQQAB == AXZcBfDnym){sBigxYcdwx = true;}
      if(DBfAqkAxlq == pKZMeRcseF){SuoQEMbAKp = true;}
      else if(pKZMeRcseF == DBfAqkAxlq){rbEkqnxrlb = true;}
      if(cqRaelibAu == YqSHRJhKxy){qWPqRhRuuA = true;}
      else if(YqSHRJhKxy == cqRaelibAu){DJeEyTgZlo = true;}
      if(kTVkaPMIar == ZuaDWaCxLq){GTwzCDdCDQ = true;}
      else if(ZuaDWaCxLq == kTVkaPMIar){xSpdfnlfRd = true;}
      if(KUZWDsCDdG == esmYbznxfd){fAWqfqqxhf = true;}
      else if(esmYbznxfd == KUZWDsCDdG){DQrNRZKGeT = true;}
      if(XnKhJIFyyO == GnqOuWnViY){xYYHnsBPKh = true;}
      else if(GnqOuWnViY == XnKhJIFyyO){XBwFcjWdid = true;}
      if(xamCCietZb == yGTCbuiWpD){IKHnJzyoNA = true;}
      else if(yGTCbuiWpD == xamCCietZb){qCrHzYkZED = true;}
      if(XrWsgHRuXk == OfhnZfEsfS){hYwtKqAYKZ = true;}
      if(ifytWwJnaR == UkeSqlDLHz){pUNPCguoKJ = true;}
      if(JOJLuihWUU == lgNlsYZjxf){COrVHUshhg = true;}
      while(OfhnZfEsfS == XrWsgHRuXk){CQZHYmQQmX = true;}
      while(UkeSqlDLHz == UkeSqlDLHz){JZuSQwWkBw = true;}
      while(lgNlsYZjxf == lgNlsYZjxf){QHwnlBYkNr = true;}
      if(PQGbPaFCoP == true){PQGbPaFCoP = false;}
      if(SuoQEMbAKp == true){SuoQEMbAKp = false;}
      if(qWPqRhRuuA == true){qWPqRhRuuA = false;}
      if(GTwzCDdCDQ == true){GTwzCDdCDQ = false;}
      if(fAWqfqqxhf == true){fAWqfqqxhf = false;}
      if(xYYHnsBPKh == true){xYYHnsBPKh = false;}
      if(IKHnJzyoNA == true){IKHnJzyoNA = false;}
      if(hYwtKqAYKZ == true){hYwtKqAYKZ = false;}
      if(pUNPCguoKJ == true){pUNPCguoKJ = false;}
      if(COrVHUshhg == true){COrVHUshhg = false;}
      if(sBigxYcdwx == true){sBigxYcdwx = false;}
      if(rbEkqnxrlb == true){rbEkqnxrlb = false;}
      if(DJeEyTgZlo == true){DJeEyTgZlo = false;}
      if(xSpdfnlfRd == true){xSpdfnlfRd = false;}
      if(DQrNRZKGeT == true){DQrNRZKGeT = false;}
      if(XBwFcjWdid == true){XBwFcjWdid = false;}
      if(qCrHzYkZED == true){qCrHzYkZED = false;}
      if(CQZHYmQQmX == true){CQZHYmQQmX = false;}
      if(JZuSQwWkBw == true){JZuSQwWkBw = false;}
      if(QHwnlBYkNr == true){QHwnlBYkNr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YTIQPEJVDW
{ 
  void AZZRwyjIHn()
  { 
      bool mOaHtYAYbl = false;
      bool KyHDAZHLRF = false;
      bool CSaiydfFPL = false;
      bool SmcVbcefLk = false;
      bool kASpJZPyUk = false;
      bool yujDyTnrJP = false;
      bool stJPSXVlaX = false;
      bool taAfUBzkYX = false;
      bool OgjdNXCYWH = false;
      bool omWwrpqDWl = false;
      bool EdXxqWuEix = false;
      bool TDSlALKfBu = false;
      bool UwOSiHEDnd = false;
      bool JwNmSkJmmq = false;
      bool bxoZmlTkuf = false;
      bool fLBaQHOENi = false;
      bool SqQFmXofSP = false;
      bool BWsKTWHnew = false;
      bool mTHHxytmVK = false;
      bool VFYDYjgjmP = false;
      string XMwKbSFopC;
      string ElkybTEPgm;
      string BgGDyHjBiP;
      string PMtpUJBPhg;
      string MWpCDKVGAT;
      string GxTUiqGrLU;
      string hDFZmrrucS;
      string RogAadpEAm;
      string ldBPIRrYGd;
      string CIDNzIQQOL;
      string SachBRPTtE;
      string BCqXiDBoRU;
      string zSnzPIkTBR;
      string NYonULBTNq;
      string CYdBcAReeu;
      string HbztMzldRr;
      string fwRbqbNCDW;
      string BhaZSZomVO;
      string qGnFKkZtbU;
      string YWBVKGHBJA;
      if(XMwKbSFopC == SachBRPTtE){mOaHtYAYbl = true;}
      else if(SachBRPTtE == XMwKbSFopC){EdXxqWuEix = true;}
      if(ElkybTEPgm == BCqXiDBoRU){KyHDAZHLRF = true;}
      else if(BCqXiDBoRU == ElkybTEPgm){TDSlALKfBu = true;}
      if(BgGDyHjBiP == zSnzPIkTBR){CSaiydfFPL = true;}
      else if(zSnzPIkTBR == BgGDyHjBiP){UwOSiHEDnd = true;}
      if(PMtpUJBPhg == NYonULBTNq){SmcVbcefLk = true;}
      else if(NYonULBTNq == PMtpUJBPhg){JwNmSkJmmq = true;}
      if(MWpCDKVGAT == CYdBcAReeu){kASpJZPyUk = true;}
      else if(CYdBcAReeu == MWpCDKVGAT){bxoZmlTkuf = true;}
      if(GxTUiqGrLU == HbztMzldRr){yujDyTnrJP = true;}
      else if(HbztMzldRr == GxTUiqGrLU){fLBaQHOENi = true;}
      if(hDFZmrrucS == fwRbqbNCDW){stJPSXVlaX = true;}
      else if(fwRbqbNCDW == hDFZmrrucS){SqQFmXofSP = true;}
      if(RogAadpEAm == BhaZSZomVO){taAfUBzkYX = true;}
      if(ldBPIRrYGd == qGnFKkZtbU){OgjdNXCYWH = true;}
      if(CIDNzIQQOL == YWBVKGHBJA){omWwrpqDWl = true;}
      while(BhaZSZomVO == RogAadpEAm){BWsKTWHnew = true;}
      while(qGnFKkZtbU == qGnFKkZtbU){mTHHxytmVK = true;}
      while(YWBVKGHBJA == YWBVKGHBJA){VFYDYjgjmP = true;}
      if(mOaHtYAYbl == true){mOaHtYAYbl = false;}
      if(KyHDAZHLRF == true){KyHDAZHLRF = false;}
      if(CSaiydfFPL == true){CSaiydfFPL = false;}
      if(SmcVbcefLk == true){SmcVbcefLk = false;}
      if(kASpJZPyUk == true){kASpJZPyUk = false;}
      if(yujDyTnrJP == true){yujDyTnrJP = false;}
      if(stJPSXVlaX == true){stJPSXVlaX = false;}
      if(taAfUBzkYX == true){taAfUBzkYX = false;}
      if(OgjdNXCYWH == true){OgjdNXCYWH = false;}
      if(omWwrpqDWl == true){omWwrpqDWl = false;}
      if(EdXxqWuEix == true){EdXxqWuEix = false;}
      if(TDSlALKfBu == true){TDSlALKfBu = false;}
      if(UwOSiHEDnd == true){UwOSiHEDnd = false;}
      if(JwNmSkJmmq == true){JwNmSkJmmq = false;}
      if(bxoZmlTkuf == true){bxoZmlTkuf = false;}
      if(fLBaQHOENi == true){fLBaQHOENi = false;}
      if(SqQFmXofSP == true){SqQFmXofSP = false;}
      if(BWsKTWHnew == true){BWsKTWHnew = false;}
      if(mTHHxytmVK == true){mTHHxytmVK = false;}
      if(VFYDYjgjmP == true){VFYDYjgjmP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VRSRTUGIIC
{ 
  void UxIbuyJiLT()
  { 
      bool kmTetHLFpB = false;
      bool otLNcexLFX = false;
      bool QXInbfVuMI = false;
      bool fLeJTqWwfu = false;
      bool szcbJLmouB = false;
      bool KSqdgMefCO = false;
      bool lPrhUcPCtk = false;
      bool IBeJeRtgdP = false;
      bool rgALyMUBbG = false;
      bool MpsRIdGuGg = false;
      bool wktJrIngzP = false;
      bool SyCmVEPfjH = false;
      bool HOZmXSINAA = false;
      bool KzZxSHlpTo = false;
      bool YnBMnOnFwE = false;
      bool NZLyYhKHkZ = false;
      bool AafyETXETN = false;
      bool RYMthTMNyJ = false;
      bool dCQwmkmaXk = false;
      bool weEtnyHDHU = false;
      string sWAMroaIyL;
      string sMUmcKOhJK;
      string wRWuYGcGMd;
      string WOCUTxEbPk;
      string xdQrSTlOhR;
      string GeLFdazEmk;
      string MTwUneJATf;
      string FlSYNRBecF;
      string TNYtWrDxpr;
      string xAodXchwDm;
      string JluCMTMlrM;
      string ZTahQyuBxw;
      string aMKaiExnAj;
      string jEbouhSVgD;
      string fQEdSdYGNZ;
      string gfzHLxaTSI;
      string WXlIbUrlli;
      string eYUtQKIgHF;
      string eqaaDEETcy;
      string GzDYgHdwBy;
      if(sWAMroaIyL == JluCMTMlrM){kmTetHLFpB = true;}
      else if(JluCMTMlrM == sWAMroaIyL){wktJrIngzP = true;}
      if(sMUmcKOhJK == ZTahQyuBxw){otLNcexLFX = true;}
      else if(ZTahQyuBxw == sMUmcKOhJK){SyCmVEPfjH = true;}
      if(wRWuYGcGMd == aMKaiExnAj){QXInbfVuMI = true;}
      else if(aMKaiExnAj == wRWuYGcGMd){HOZmXSINAA = true;}
      if(WOCUTxEbPk == jEbouhSVgD){fLeJTqWwfu = true;}
      else if(jEbouhSVgD == WOCUTxEbPk){KzZxSHlpTo = true;}
      if(xdQrSTlOhR == fQEdSdYGNZ){szcbJLmouB = true;}
      else if(fQEdSdYGNZ == xdQrSTlOhR){YnBMnOnFwE = true;}
      if(GeLFdazEmk == gfzHLxaTSI){KSqdgMefCO = true;}
      else if(gfzHLxaTSI == GeLFdazEmk){NZLyYhKHkZ = true;}
      if(MTwUneJATf == WXlIbUrlli){lPrhUcPCtk = true;}
      else if(WXlIbUrlli == MTwUneJATf){AafyETXETN = true;}
      if(FlSYNRBecF == eYUtQKIgHF){IBeJeRtgdP = true;}
      if(TNYtWrDxpr == eqaaDEETcy){rgALyMUBbG = true;}
      if(xAodXchwDm == GzDYgHdwBy){MpsRIdGuGg = true;}
      while(eYUtQKIgHF == FlSYNRBecF){RYMthTMNyJ = true;}
      while(eqaaDEETcy == eqaaDEETcy){dCQwmkmaXk = true;}
      while(GzDYgHdwBy == GzDYgHdwBy){weEtnyHDHU = true;}
      if(kmTetHLFpB == true){kmTetHLFpB = false;}
      if(otLNcexLFX == true){otLNcexLFX = false;}
      if(QXInbfVuMI == true){QXInbfVuMI = false;}
      if(fLeJTqWwfu == true){fLeJTqWwfu = false;}
      if(szcbJLmouB == true){szcbJLmouB = false;}
      if(KSqdgMefCO == true){KSqdgMefCO = false;}
      if(lPrhUcPCtk == true){lPrhUcPCtk = false;}
      if(IBeJeRtgdP == true){IBeJeRtgdP = false;}
      if(rgALyMUBbG == true){rgALyMUBbG = false;}
      if(MpsRIdGuGg == true){MpsRIdGuGg = false;}
      if(wktJrIngzP == true){wktJrIngzP = false;}
      if(SyCmVEPfjH == true){SyCmVEPfjH = false;}
      if(HOZmXSINAA == true){HOZmXSINAA = false;}
      if(KzZxSHlpTo == true){KzZxSHlpTo = false;}
      if(YnBMnOnFwE == true){YnBMnOnFwE = false;}
      if(NZLyYhKHkZ == true){NZLyYhKHkZ = false;}
      if(AafyETXETN == true){AafyETXETN = false;}
      if(RYMthTMNyJ == true){RYMthTMNyJ = false;}
      if(dCQwmkmaXk == true){dCQwmkmaXk = false;}
      if(weEtnyHDHU == true){weEtnyHDHU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PMGXERBAPC
{ 
  void iDXECUJgUY()
  { 
      bool bsUKQqYdry = false;
      bool oZBXUpaGxg = false;
      bool xEBDVJqwhd = false;
      bool lAVOIYazgF = false;
      bool zhoiOKhVRo = false;
      bool ooWCFXqQnH = false;
      bool AcuNLnEmPu = false;
      bool OaZqhOORoL = false;
      bool aUesnxdTIj = false;
      bool hKLZFVmaXZ = false;
      bool FuFVZOOeUp = false;
      bool IYabfeyBZN = false;
      bool KkeeNDOzlL = false;
      bool bntPFfOISY = false;
      bool hzzRbIjjsZ = false;
      bool XkAJPUQaIW = false;
      bool zPrIOTeLVz = false;
      bool QoiAfKkMCE = false;
      bool TeFLmpnjAj = false;
      bool PnzwZSGpCI = false;
      string mpVttpSVQs;
      string BFdIeSzMXy;
      string bBmuQitYHJ;
      string lAoJISzbyE;
      string JecnRJtuRA;
      string hZiHikCacL;
      string utOGHBQUAM;
      string SWNSnwYzdH;
      string oyGGbMRgaX;
      string PYymIPPVgP;
      string sYuEgKLPTl;
      string LDwVVxmHet;
      string jitcwtYaKY;
      string fCSNOPDCYQ;
      string ABNnLMbbQL;
      string bHqlfKeSIm;
      string ljFtFIkiHG;
      string tkiNthUFQj;
      string SwJyxXLggD;
      string jjtlePuTiC;
      if(mpVttpSVQs == sYuEgKLPTl){bsUKQqYdry = true;}
      else if(sYuEgKLPTl == mpVttpSVQs){FuFVZOOeUp = true;}
      if(BFdIeSzMXy == LDwVVxmHet){oZBXUpaGxg = true;}
      else if(LDwVVxmHet == BFdIeSzMXy){IYabfeyBZN = true;}
      if(bBmuQitYHJ == jitcwtYaKY){xEBDVJqwhd = true;}
      else if(jitcwtYaKY == bBmuQitYHJ){KkeeNDOzlL = true;}
      if(lAoJISzbyE == fCSNOPDCYQ){lAVOIYazgF = true;}
      else if(fCSNOPDCYQ == lAoJISzbyE){bntPFfOISY = true;}
      if(JecnRJtuRA == ABNnLMbbQL){zhoiOKhVRo = true;}
      else if(ABNnLMbbQL == JecnRJtuRA){hzzRbIjjsZ = true;}
      if(hZiHikCacL == bHqlfKeSIm){ooWCFXqQnH = true;}
      else if(bHqlfKeSIm == hZiHikCacL){XkAJPUQaIW = true;}
      if(utOGHBQUAM == ljFtFIkiHG){AcuNLnEmPu = true;}
      else if(ljFtFIkiHG == utOGHBQUAM){zPrIOTeLVz = true;}
      if(SWNSnwYzdH == tkiNthUFQj){OaZqhOORoL = true;}
      if(oyGGbMRgaX == SwJyxXLggD){aUesnxdTIj = true;}
      if(PYymIPPVgP == jjtlePuTiC){hKLZFVmaXZ = true;}
      while(tkiNthUFQj == SWNSnwYzdH){QoiAfKkMCE = true;}
      while(SwJyxXLggD == SwJyxXLggD){TeFLmpnjAj = true;}
      while(jjtlePuTiC == jjtlePuTiC){PnzwZSGpCI = true;}
      if(bsUKQqYdry == true){bsUKQqYdry = false;}
      if(oZBXUpaGxg == true){oZBXUpaGxg = false;}
      if(xEBDVJqwhd == true){xEBDVJqwhd = false;}
      if(lAVOIYazgF == true){lAVOIYazgF = false;}
      if(zhoiOKhVRo == true){zhoiOKhVRo = false;}
      if(ooWCFXqQnH == true){ooWCFXqQnH = false;}
      if(AcuNLnEmPu == true){AcuNLnEmPu = false;}
      if(OaZqhOORoL == true){OaZqhOORoL = false;}
      if(aUesnxdTIj == true){aUesnxdTIj = false;}
      if(hKLZFVmaXZ == true){hKLZFVmaXZ = false;}
      if(FuFVZOOeUp == true){FuFVZOOeUp = false;}
      if(IYabfeyBZN == true){IYabfeyBZN = false;}
      if(KkeeNDOzlL == true){KkeeNDOzlL = false;}
      if(bntPFfOISY == true){bntPFfOISY = false;}
      if(hzzRbIjjsZ == true){hzzRbIjjsZ = false;}
      if(XkAJPUQaIW == true){XkAJPUQaIW = false;}
      if(zPrIOTeLVz == true){zPrIOTeLVz = false;}
      if(QoiAfKkMCE == true){QoiAfKkMCE = false;}
      if(TeFLmpnjAj == true){TeFLmpnjAj = false;}
      if(PnzwZSGpCI == true){PnzwZSGpCI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PGIKMXAVPB
{ 
  void ZBqrkIEjru()
  { 
      bool EPYOdPWqCU = false;
      bool HGINYohUkL = false;
      bool nxZiTcBpAD = false;
      bool XEiaUCDHCV = false;
      bool XOksFVybgS = false;
      bool ubrDMGpouB = false;
      bool NgqyxDXhsW = false;
      bool lZSOmZMgcx = false;
      bool dZJgHuLeNN = false;
      bool MNLBIqWmuC = false;
      bool yQhKgVJcQm = false;
      bool tJMxWmWKpB = false;
      bool qsUeKXNRGw = false;
      bool CYkZzNrzzl = false;
      bool liNZTDAOdU = false;
      bool TMwtLEwDzI = false;
      bool HrVUkUXmyJ = false;
      bool uXKEPHetLH = false;
      bool XzmlbocqNu = false;
      bool RozpdtMsny = false;
      string mjEYhNmuqP;
      string usELpXOyGm;
      string tuFtxwiqpT;
      string eduqocFwaV;
      string USFidVngOe;
      string fKhgyqeJbl;
      string euEWjRxNWM;
      string RRXkRbpVQb;
      string HCcKnUwOrx;
      string ywUopYNizL;
      string XZJBNNmwOV;
      string BIrzdbStiP;
      string UhUYOVwhtr;
      string OGWEDhrbxZ;
      string hzAWwpDULN;
      string GTAiqpEklq;
      string QEBWGtkmww;
      string jqwIgVhybY;
      string RbWfkuGmNN;
      string cHoFIdxdPB;
      if(mjEYhNmuqP == XZJBNNmwOV){EPYOdPWqCU = true;}
      else if(XZJBNNmwOV == mjEYhNmuqP){yQhKgVJcQm = true;}
      if(usELpXOyGm == BIrzdbStiP){HGINYohUkL = true;}
      else if(BIrzdbStiP == usELpXOyGm){tJMxWmWKpB = true;}
      if(tuFtxwiqpT == UhUYOVwhtr){nxZiTcBpAD = true;}
      else if(UhUYOVwhtr == tuFtxwiqpT){qsUeKXNRGw = true;}
      if(eduqocFwaV == OGWEDhrbxZ){XEiaUCDHCV = true;}
      else if(OGWEDhrbxZ == eduqocFwaV){CYkZzNrzzl = true;}
      if(USFidVngOe == hzAWwpDULN){XOksFVybgS = true;}
      else if(hzAWwpDULN == USFidVngOe){liNZTDAOdU = true;}
      if(fKhgyqeJbl == GTAiqpEklq){ubrDMGpouB = true;}
      else if(GTAiqpEklq == fKhgyqeJbl){TMwtLEwDzI = true;}
      if(euEWjRxNWM == QEBWGtkmww){NgqyxDXhsW = true;}
      else if(QEBWGtkmww == euEWjRxNWM){HrVUkUXmyJ = true;}
      if(RRXkRbpVQb == jqwIgVhybY){lZSOmZMgcx = true;}
      if(HCcKnUwOrx == RbWfkuGmNN){dZJgHuLeNN = true;}
      if(ywUopYNizL == cHoFIdxdPB){MNLBIqWmuC = true;}
      while(jqwIgVhybY == RRXkRbpVQb){uXKEPHetLH = true;}
      while(RbWfkuGmNN == RbWfkuGmNN){XzmlbocqNu = true;}
      while(cHoFIdxdPB == cHoFIdxdPB){RozpdtMsny = true;}
      if(EPYOdPWqCU == true){EPYOdPWqCU = false;}
      if(HGINYohUkL == true){HGINYohUkL = false;}
      if(nxZiTcBpAD == true){nxZiTcBpAD = false;}
      if(XEiaUCDHCV == true){XEiaUCDHCV = false;}
      if(XOksFVybgS == true){XOksFVybgS = false;}
      if(ubrDMGpouB == true){ubrDMGpouB = false;}
      if(NgqyxDXhsW == true){NgqyxDXhsW = false;}
      if(lZSOmZMgcx == true){lZSOmZMgcx = false;}
      if(dZJgHuLeNN == true){dZJgHuLeNN = false;}
      if(MNLBIqWmuC == true){MNLBIqWmuC = false;}
      if(yQhKgVJcQm == true){yQhKgVJcQm = false;}
      if(tJMxWmWKpB == true){tJMxWmWKpB = false;}
      if(qsUeKXNRGw == true){qsUeKXNRGw = false;}
      if(CYkZzNrzzl == true){CYkZzNrzzl = false;}
      if(liNZTDAOdU == true){liNZTDAOdU = false;}
      if(TMwtLEwDzI == true){TMwtLEwDzI = false;}
      if(HrVUkUXmyJ == true){HrVUkUXmyJ = false;}
      if(uXKEPHetLH == true){uXKEPHetLH = false;}
      if(XzmlbocqNu == true){XzmlbocqNu = false;}
      if(RozpdtMsny == true){RozpdtMsny = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FAQCSIKDJV
{ 
  void nCIxwzHasi()
  { 
      bool rSWuIsleuK = false;
      bool PPlCqdfVqY = false;
      bool iToTybcbNF = false;
      bool fdwTFwgnlP = false;
      bool pyLLQHjQfD = false;
      bool KiHIFYdDxf = false;
      bool PJRpdkTSwu = false;
      bool xrjbhkHcCp = false;
      bool rMuKtxVmOg = false;
      bool SdqFAgfVhe = false;
      bool nQUkGRzfaU = false;
      bool QAAGnCNHug = false;
      bool OfEOcTBeaA = false;
      bool EltXCaqKDb = false;
      bool xpMsQRcjRx = false;
      bool TXZBPHMGIm = false;
      bool QUEZPeFbEM = false;
      bool LCDSiYTKxK = false;
      bool pQMdggLrIt = false;
      bool NkCQLckldl = false;
      string OoYVIASkkZ;
      string cczCbMseoM;
      string wHSXyrKQeD;
      string xgAnYPJVWO;
      string IUSXAzSkdB;
      string fYrCqGVBXP;
      string pCGhbwbKdL;
      string CXIZEbouWy;
      string ZYlcXXnyxS;
      string tIxGYFOkuE;
      string XHGSzIQRyO;
      string QZdZoQQcKD;
      string HdMKRsaBBy;
      string NEzSZSSTdO;
      string HVziBTdWRH;
      string okarwttwAG;
      string hPQABMaLzW;
      string ywzuwlddJy;
      string ODitIbdHWf;
      string XVSWgqFzho;
      if(OoYVIASkkZ == XHGSzIQRyO){rSWuIsleuK = true;}
      else if(XHGSzIQRyO == OoYVIASkkZ){nQUkGRzfaU = true;}
      if(cczCbMseoM == QZdZoQQcKD){PPlCqdfVqY = true;}
      else if(QZdZoQQcKD == cczCbMseoM){QAAGnCNHug = true;}
      if(wHSXyrKQeD == HdMKRsaBBy){iToTybcbNF = true;}
      else if(HdMKRsaBBy == wHSXyrKQeD){OfEOcTBeaA = true;}
      if(xgAnYPJVWO == NEzSZSSTdO){fdwTFwgnlP = true;}
      else if(NEzSZSSTdO == xgAnYPJVWO){EltXCaqKDb = true;}
      if(IUSXAzSkdB == HVziBTdWRH){pyLLQHjQfD = true;}
      else if(HVziBTdWRH == IUSXAzSkdB){xpMsQRcjRx = true;}
      if(fYrCqGVBXP == okarwttwAG){KiHIFYdDxf = true;}
      else if(okarwttwAG == fYrCqGVBXP){TXZBPHMGIm = true;}
      if(pCGhbwbKdL == hPQABMaLzW){PJRpdkTSwu = true;}
      else if(hPQABMaLzW == pCGhbwbKdL){QUEZPeFbEM = true;}
      if(CXIZEbouWy == ywzuwlddJy){xrjbhkHcCp = true;}
      if(ZYlcXXnyxS == ODitIbdHWf){rMuKtxVmOg = true;}
      if(tIxGYFOkuE == XVSWgqFzho){SdqFAgfVhe = true;}
      while(ywzuwlddJy == CXIZEbouWy){LCDSiYTKxK = true;}
      while(ODitIbdHWf == ODitIbdHWf){pQMdggLrIt = true;}
      while(XVSWgqFzho == XVSWgqFzho){NkCQLckldl = true;}
      if(rSWuIsleuK == true){rSWuIsleuK = false;}
      if(PPlCqdfVqY == true){PPlCqdfVqY = false;}
      if(iToTybcbNF == true){iToTybcbNF = false;}
      if(fdwTFwgnlP == true){fdwTFwgnlP = false;}
      if(pyLLQHjQfD == true){pyLLQHjQfD = false;}
      if(KiHIFYdDxf == true){KiHIFYdDxf = false;}
      if(PJRpdkTSwu == true){PJRpdkTSwu = false;}
      if(xrjbhkHcCp == true){xrjbhkHcCp = false;}
      if(rMuKtxVmOg == true){rMuKtxVmOg = false;}
      if(SdqFAgfVhe == true){SdqFAgfVhe = false;}
      if(nQUkGRzfaU == true){nQUkGRzfaU = false;}
      if(QAAGnCNHug == true){QAAGnCNHug = false;}
      if(OfEOcTBeaA == true){OfEOcTBeaA = false;}
      if(EltXCaqKDb == true){EltXCaqKDb = false;}
      if(xpMsQRcjRx == true){xpMsQRcjRx = false;}
      if(TXZBPHMGIm == true){TXZBPHMGIm = false;}
      if(QUEZPeFbEM == true){QUEZPeFbEM = false;}
      if(LCDSiYTKxK == true){LCDSiYTKxK = false;}
      if(pQMdggLrIt == true){pQMdggLrIt = false;}
      if(NkCQLckldl == true){NkCQLckldl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RBCHRUEXET
{ 
  void THdjQjxNIi()
  { 
      bool LGxhIHEkSS = false;
      bool AcrPJQOkMC = false;
      bool jUjCaZIzdm = false;
      bool WOtfBmBhZJ = false;
      bool KDhkCSLqTg = false;
      bool xcZszqVtGi = false;
      bool yFHfwlhLNV = false;
      bool OgLDqglzAI = false;
      bool NQfxosnAgK = false;
      bool RHbpKFwBoP = false;
      bool jAdxRPRWCR = false;
      bool EWtxUhZJpD = false;
      bool xhdCEHEUrl = false;
      bool jkKjYNmheZ = false;
      bool aRyOFuMdVc = false;
      bool flLkRCVasK = false;
      bool LwdPgTLJYH = false;
      bool tqdQbfiOxJ = false;
      bool tazPGyZYRV = false;
      bool qMoTNdnihl = false;
      string CUdVYIDdhj;
      string CLMUsJLiBr;
      string FYJynwcuzO;
      string EJMdNeZuUF;
      string fTUkQQHllb;
      string iNkdAdKfhb;
      string eIeTeryhGO;
      string iQNuLkDXgW;
      string opIWepXhdi;
      string TtNraXnBGX;
      string RYeXrSzoRO;
      string amyKmnAHno;
      string TQEXtoCUUn;
      string xBRIEPKjeM;
      string piPOIguDFl;
      string XgMQEBTHcC;
      string PeTdRYUoFX;
      string cPbaykApPN;
      string szPiQPoAED;
      string wDGcxLOlwi;
      if(CUdVYIDdhj == RYeXrSzoRO){LGxhIHEkSS = true;}
      else if(RYeXrSzoRO == CUdVYIDdhj){jAdxRPRWCR = true;}
      if(CLMUsJLiBr == amyKmnAHno){AcrPJQOkMC = true;}
      else if(amyKmnAHno == CLMUsJLiBr){EWtxUhZJpD = true;}
      if(FYJynwcuzO == TQEXtoCUUn){jUjCaZIzdm = true;}
      else if(TQEXtoCUUn == FYJynwcuzO){xhdCEHEUrl = true;}
      if(EJMdNeZuUF == xBRIEPKjeM){WOtfBmBhZJ = true;}
      else if(xBRIEPKjeM == EJMdNeZuUF){jkKjYNmheZ = true;}
      if(fTUkQQHllb == piPOIguDFl){KDhkCSLqTg = true;}
      else if(piPOIguDFl == fTUkQQHllb){aRyOFuMdVc = true;}
      if(iNkdAdKfhb == XgMQEBTHcC){xcZszqVtGi = true;}
      else if(XgMQEBTHcC == iNkdAdKfhb){flLkRCVasK = true;}
      if(eIeTeryhGO == PeTdRYUoFX){yFHfwlhLNV = true;}
      else if(PeTdRYUoFX == eIeTeryhGO){LwdPgTLJYH = true;}
      if(iQNuLkDXgW == cPbaykApPN){OgLDqglzAI = true;}
      if(opIWepXhdi == szPiQPoAED){NQfxosnAgK = true;}
      if(TtNraXnBGX == wDGcxLOlwi){RHbpKFwBoP = true;}
      while(cPbaykApPN == iQNuLkDXgW){tqdQbfiOxJ = true;}
      while(szPiQPoAED == szPiQPoAED){tazPGyZYRV = true;}
      while(wDGcxLOlwi == wDGcxLOlwi){qMoTNdnihl = true;}
      if(LGxhIHEkSS == true){LGxhIHEkSS = false;}
      if(AcrPJQOkMC == true){AcrPJQOkMC = false;}
      if(jUjCaZIzdm == true){jUjCaZIzdm = false;}
      if(WOtfBmBhZJ == true){WOtfBmBhZJ = false;}
      if(KDhkCSLqTg == true){KDhkCSLqTg = false;}
      if(xcZszqVtGi == true){xcZszqVtGi = false;}
      if(yFHfwlhLNV == true){yFHfwlhLNV = false;}
      if(OgLDqglzAI == true){OgLDqglzAI = false;}
      if(NQfxosnAgK == true){NQfxosnAgK = false;}
      if(RHbpKFwBoP == true){RHbpKFwBoP = false;}
      if(jAdxRPRWCR == true){jAdxRPRWCR = false;}
      if(EWtxUhZJpD == true){EWtxUhZJpD = false;}
      if(xhdCEHEUrl == true){xhdCEHEUrl = false;}
      if(jkKjYNmheZ == true){jkKjYNmheZ = false;}
      if(aRyOFuMdVc == true){aRyOFuMdVc = false;}
      if(flLkRCVasK == true){flLkRCVasK = false;}
      if(LwdPgTLJYH == true){LwdPgTLJYH = false;}
      if(tqdQbfiOxJ == true){tqdQbfiOxJ = false;}
      if(tazPGyZYRV == true){tazPGyZYRV = false;}
      if(qMoTNdnihl == true){qMoTNdnihl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QLANUMVTRF
{ 
  void dwwZcdyNHi()
  { 
      bool zZYDPYfMoG = false;
      bool PdQsqszhZB = false;
      bool RoBnyryUka = false;
      bool MYOFFXePoB = false;
      bool RbzECQJqKg = false;
      bool VRdsVJYkEW = false;
      bool aLaOtqOLmS = false;
      bool NjsYjoowlh = false;
      bool iHKDFuuViu = false;
      bool ztLRZGBkKL = false;
      bool BxDqTkXEIf = false;
      bool UbyVnTAWJz = false;
      bool urbqTSXbyc = false;
      bool nElagkDTjT = false;
      bool WpMDaWuocG = false;
      bool FdbKPIUMWA = false;
      bool MwGfrPpXoC = false;
      bool QglobEeYPx = false;
      bool WiyrXJbaKX = false;
      bool PqwjGajgKL = false;
      string WTTlQItmVw;
      string RzLHtnkKmN;
      string KdUchQbMIb;
      string pGdMHeWBXQ;
      string GtFadwpwwq;
      string SUtpRsyqDA;
      string ggdtFLVzAP;
      string QilVHQXtyl;
      string ZePQIVLnuO;
      string gfyWjYPKUS;
      string aqugZihYiA;
      string UDrRaCQMlj;
      string zhDlhkkPlh;
      string ANZeLhiipY;
      string nmEttcmfwh;
      string HCYkTsmJyo;
      string ySmAzGdNGs;
      string ShWMuMcJrF;
      string xESEayonLR;
      string tZjBaUADtm;
      if(WTTlQItmVw == aqugZihYiA){zZYDPYfMoG = true;}
      else if(aqugZihYiA == WTTlQItmVw){BxDqTkXEIf = true;}
      if(RzLHtnkKmN == UDrRaCQMlj){PdQsqszhZB = true;}
      else if(UDrRaCQMlj == RzLHtnkKmN){UbyVnTAWJz = true;}
      if(KdUchQbMIb == zhDlhkkPlh){RoBnyryUka = true;}
      else if(zhDlhkkPlh == KdUchQbMIb){urbqTSXbyc = true;}
      if(pGdMHeWBXQ == ANZeLhiipY){MYOFFXePoB = true;}
      else if(ANZeLhiipY == pGdMHeWBXQ){nElagkDTjT = true;}
      if(GtFadwpwwq == nmEttcmfwh){RbzECQJqKg = true;}
      else if(nmEttcmfwh == GtFadwpwwq){WpMDaWuocG = true;}
      if(SUtpRsyqDA == HCYkTsmJyo){VRdsVJYkEW = true;}
      else if(HCYkTsmJyo == SUtpRsyqDA){FdbKPIUMWA = true;}
      if(ggdtFLVzAP == ySmAzGdNGs){aLaOtqOLmS = true;}
      else if(ySmAzGdNGs == ggdtFLVzAP){MwGfrPpXoC = true;}
      if(QilVHQXtyl == ShWMuMcJrF){NjsYjoowlh = true;}
      if(ZePQIVLnuO == xESEayonLR){iHKDFuuViu = true;}
      if(gfyWjYPKUS == tZjBaUADtm){ztLRZGBkKL = true;}
      while(ShWMuMcJrF == QilVHQXtyl){QglobEeYPx = true;}
      while(xESEayonLR == xESEayonLR){WiyrXJbaKX = true;}
      while(tZjBaUADtm == tZjBaUADtm){PqwjGajgKL = true;}
      if(zZYDPYfMoG == true){zZYDPYfMoG = false;}
      if(PdQsqszhZB == true){PdQsqszhZB = false;}
      if(RoBnyryUka == true){RoBnyryUka = false;}
      if(MYOFFXePoB == true){MYOFFXePoB = false;}
      if(RbzECQJqKg == true){RbzECQJqKg = false;}
      if(VRdsVJYkEW == true){VRdsVJYkEW = false;}
      if(aLaOtqOLmS == true){aLaOtqOLmS = false;}
      if(NjsYjoowlh == true){NjsYjoowlh = false;}
      if(iHKDFuuViu == true){iHKDFuuViu = false;}
      if(ztLRZGBkKL == true){ztLRZGBkKL = false;}
      if(BxDqTkXEIf == true){BxDqTkXEIf = false;}
      if(UbyVnTAWJz == true){UbyVnTAWJz = false;}
      if(urbqTSXbyc == true){urbqTSXbyc = false;}
      if(nElagkDTjT == true){nElagkDTjT = false;}
      if(WpMDaWuocG == true){WpMDaWuocG = false;}
      if(FdbKPIUMWA == true){FdbKPIUMWA = false;}
      if(MwGfrPpXoC == true){MwGfrPpXoC = false;}
      if(QglobEeYPx == true){QglobEeYPx = false;}
      if(WiyrXJbaKX == true){WiyrXJbaKX = false;}
      if(PqwjGajgKL == true){PqwjGajgKL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JHRQZSRUDU
{ 
  void XupLOQDjZp()
  { 
      bool gfWDsbbgZP = false;
      bool RxRkVhfauc = false;
      bool FOqsMXkyjQ = false;
      bool JAQWCLMHea = false;
      bool GxxOpczkjz = false;
      bool BPfVXRncqV = false;
      bool qdwIGQftiK = false;
      bool VYwUVHRbDi = false;
      bool XzNkPsUuzj = false;
      bool WiPIjcAnHZ = false;
      bool xECZdcTLzQ = false;
      bool ALZIxqPLsN = false;
      bool wkuymlJmjs = false;
      bool HcUdkTwmGm = false;
      bool ZIuhiKJGLs = false;
      bool MnutcMIEmq = false;
      bool TfbGJXquWc = false;
      bool tbEFnnoMOb = false;
      bool bCbqfSgZAY = false;
      bool LrAPTsgoYL = false;
      string JCVhcXSsZS;
      string CBpYkAZoEh;
      string XBaAYZkzsj;
      string dOfejdnmUs;
      string GEGiwVyUgS;
      string LNRPtIaUID;
      string mTzpnnVKoH;
      string MlTLbTtrDD;
      string bPSaYQwQja;
      string DSdRFlEQuI;
      string AmfZGYsFnZ;
      string NiRFaXBYQW;
      string qEZNDsHCGo;
      string OdwuDnirTz;
      string XqbKNTBYqh;
      string kfzYQuNSVN;
      string QqzzLjlVCm;
      string nIERyAcPAj;
      string qiKXDheXeI;
      string aQWGhgqbyc;
      if(JCVhcXSsZS == AmfZGYsFnZ){gfWDsbbgZP = true;}
      else if(AmfZGYsFnZ == JCVhcXSsZS){xECZdcTLzQ = true;}
      if(CBpYkAZoEh == NiRFaXBYQW){RxRkVhfauc = true;}
      else if(NiRFaXBYQW == CBpYkAZoEh){ALZIxqPLsN = true;}
      if(XBaAYZkzsj == qEZNDsHCGo){FOqsMXkyjQ = true;}
      else if(qEZNDsHCGo == XBaAYZkzsj){wkuymlJmjs = true;}
      if(dOfejdnmUs == OdwuDnirTz){JAQWCLMHea = true;}
      else if(OdwuDnirTz == dOfejdnmUs){HcUdkTwmGm = true;}
      if(GEGiwVyUgS == XqbKNTBYqh){GxxOpczkjz = true;}
      else if(XqbKNTBYqh == GEGiwVyUgS){ZIuhiKJGLs = true;}
      if(LNRPtIaUID == kfzYQuNSVN){BPfVXRncqV = true;}
      else if(kfzYQuNSVN == LNRPtIaUID){MnutcMIEmq = true;}
      if(mTzpnnVKoH == QqzzLjlVCm){qdwIGQftiK = true;}
      else if(QqzzLjlVCm == mTzpnnVKoH){TfbGJXquWc = true;}
      if(MlTLbTtrDD == nIERyAcPAj){VYwUVHRbDi = true;}
      if(bPSaYQwQja == qiKXDheXeI){XzNkPsUuzj = true;}
      if(DSdRFlEQuI == aQWGhgqbyc){WiPIjcAnHZ = true;}
      while(nIERyAcPAj == MlTLbTtrDD){tbEFnnoMOb = true;}
      while(qiKXDheXeI == qiKXDheXeI){bCbqfSgZAY = true;}
      while(aQWGhgqbyc == aQWGhgqbyc){LrAPTsgoYL = true;}
      if(gfWDsbbgZP == true){gfWDsbbgZP = false;}
      if(RxRkVhfauc == true){RxRkVhfauc = false;}
      if(FOqsMXkyjQ == true){FOqsMXkyjQ = false;}
      if(JAQWCLMHea == true){JAQWCLMHea = false;}
      if(GxxOpczkjz == true){GxxOpczkjz = false;}
      if(BPfVXRncqV == true){BPfVXRncqV = false;}
      if(qdwIGQftiK == true){qdwIGQftiK = false;}
      if(VYwUVHRbDi == true){VYwUVHRbDi = false;}
      if(XzNkPsUuzj == true){XzNkPsUuzj = false;}
      if(WiPIjcAnHZ == true){WiPIjcAnHZ = false;}
      if(xECZdcTLzQ == true){xECZdcTLzQ = false;}
      if(ALZIxqPLsN == true){ALZIxqPLsN = false;}
      if(wkuymlJmjs == true){wkuymlJmjs = false;}
      if(HcUdkTwmGm == true){HcUdkTwmGm = false;}
      if(ZIuhiKJGLs == true){ZIuhiKJGLs = false;}
      if(MnutcMIEmq == true){MnutcMIEmq = false;}
      if(TfbGJXquWc == true){TfbGJXquWc = false;}
      if(tbEFnnoMOb == true){tbEFnnoMOb = false;}
      if(bCbqfSgZAY == true){bCbqfSgZAY = false;}
      if(LrAPTsgoYL == true){LrAPTsgoYL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KPMFUDFBSF
{ 
  void OXLjSeYFza()
  { 
      bool DCaSEboWsa = false;
      bool ooJNGGenYA = false;
      bool xfdmyDudZK = false;
      bool UAoSYcaZCh = false;
      bool QEMHJiXgLD = false;
      bool lArfGXYmUA = false;
      bool gKwhFozpod = false;
      bool eFlqjsSVdO = false;
      bool fOSWXTHIMB = false;
      bool EnEBBFHeBT = false;
      bool igrhXgNBwN = false;
      bool FCJFURrYJk = false;
      bool gpdnZqAkoe = false;
      bool knUJfzWkzq = false;
      bool GGMyuBeygj = false;
      bool NiUPmrDEIf = false;
      bool fcLQcQhzZU = false;
      bool tGYSeaderX = false;
      bool MBDFQBTEWm = false;
      bool wScTKdtuVe = false;
      string roXVpABeaw;
      string YlCPyHEuRw;
      string rtOwsZHbyh;
      string iDDHgcUiOg;
      string VQCAzKRNeQ;
      string smbnXyabbQ;
      string rZgrMVithU;
      string lVgkZarNwi;
      string IswgoubOji;
      string CsGynwjJmd;
      string bWfKdWGqNw;
      string GMesIyczCR;
      string sTKzSsOiwd;
      string phaSGkNlDR;
      string ojBmboOMpo;
      string SkGVjHMgqk;
      string IXuiGXkLlW;
      string kpwjbJRWWc;
      string eBrGKFaFhz;
      string YguRJRoRgD;
      if(roXVpABeaw == bWfKdWGqNw){DCaSEboWsa = true;}
      else if(bWfKdWGqNw == roXVpABeaw){igrhXgNBwN = true;}
      if(YlCPyHEuRw == GMesIyczCR){ooJNGGenYA = true;}
      else if(GMesIyczCR == YlCPyHEuRw){FCJFURrYJk = true;}
      if(rtOwsZHbyh == sTKzSsOiwd){xfdmyDudZK = true;}
      else if(sTKzSsOiwd == rtOwsZHbyh){gpdnZqAkoe = true;}
      if(iDDHgcUiOg == phaSGkNlDR){UAoSYcaZCh = true;}
      else if(phaSGkNlDR == iDDHgcUiOg){knUJfzWkzq = true;}
      if(VQCAzKRNeQ == ojBmboOMpo){QEMHJiXgLD = true;}
      else if(ojBmboOMpo == VQCAzKRNeQ){GGMyuBeygj = true;}
      if(smbnXyabbQ == SkGVjHMgqk){lArfGXYmUA = true;}
      else if(SkGVjHMgqk == smbnXyabbQ){NiUPmrDEIf = true;}
      if(rZgrMVithU == IXuiGXkLlW){gKwhFozpod = true;}
      else if(IXuiGXkLlW == rZgrMVithU){fcLQcQhzZU = true;}
      if(lVgkZarNwi == kpwjbJRWWc){eFlqjsSVdO = true;}
      if(IswgoubOji == eBrGKFaFhz){fOSWXTHIMB = true;}
      if(CsGynwjJmd == YguRJRoRgD){EnEBBFHeBT = true;}
      while(kpwjbJRWWc == lVgkZarNwi){tGYSeaderX = true;}
      while(eBrGKFaFhz == eBrGKFaFhz){MBDFQBTEWm = true;}
      while(YguRJRoRgD == YguRJRoRgD){wScTKdtuVe = true;}
      if(DCaSEboWsa == true){DCaSEboWsa = false;}
      if(ooJNGGenYA == true){ooJNGGenYA = false;}
      if(xfdmyDudZK == true){xfdmyDudZK = false;}
      if(UAoSYcaZCh == true){UAoSYcaZCh = false;}
      if(QEMHJiXgLD == true){QEMHJiXgLD = false;}
      if(lArfGXYmUA == true){lArfGXYmUA = false;}
      if(gKwhFozpod == true){gKwhFozpod = false;}
      if(eFlqjsSVdO == true){eFlqjsSVdO = false;}
      if(fOSWXTHIMB == true){fOSWXTHIMB = false;}
      if(EnEBBFHeBT == true){EnEBBFHeBT = false;}
      if(igrhXgNBwN == true){igrhXgNBwN = false;}
      if(FCJFURrYJk == true){FCJFURrYJk = false;}
      if(gpdnZqAkoe == true){gpdnZqAkoe = false;}
      if(knUJfzWkzq == true){knUJfzWkzq = false;}
      if(GGMyuBeygj == true){GGMyuBeygj = false;}
      if(NiUPmrDEIf == true){NiUPmrDEIf = false;}
      if(fcLQcQhzZU == true){fcLQcQhzZU = false;}
      if(tGYSeaderX == true){tGYSeaderX = false;}
      if(MBDFQBTEWm == true){MBDFQBTEWm = false;}
      if(wScTKdtuVe == true){wScTKdtuVe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UENILNIOCP
{ 
  void lOqxinAQpi()
  { 
      bool zTSVaHbxoI = false;
      bool UKQcdNUCrl = false;
      bool eBICmLDMyJ = false;
      bool ymQCajSUQo = false;
      bool bqxmAAADwf = false;
      bool aJWjxxKQhO = false;
      bool EPyfJhsOBt = false;
      bool uAlCKmEVCm = false;
      bool KzPShoQfEd = false;
      bool YBlBkLsRcR = false;
      bool GlCCjZXTZJ = false;
      bool snOuEFzexU = false;
      bool RNJXUtOjRy = false;
      bool tlrjfXxNiH = false;
      bool QwGujjmqxf = false;
      bool MNTIAscdhp = false;
      bool LnBbPGudPf = false;
      bool HkwpDUHOmj = false;
      bool GXmkkfSjjl = false;
      bool uSfswctded = false;
      string tDPfoBJTpg;
      string lIgUphbcIg;
      string IpqutabnCh;
      string nZPKyTMspS;
      string gcjBwWTrmg;
      string LJeeoELTlN;
      string YURIrLrVVV;
      string VimoAeFpzW;
      string GiBUVeujVt;
      string IsGbtLLbIj;
      string exWQLcWoeJ;
      string yVTPHpTwlN;
      string QHAaNccKuo;
      string TdgOrIMjJs;
      string IFFMwmYqUE;
      string qPotTWxuDh;
      string zLsppTnEXy;
      string cjmrFKCmeZ;
      string ElpqxDnluU;
      string KRgaswLPWc;
      if(tDPfoBJTpg == exWQLcWoeJ){zTSVaHbxoI = true;}
      else if(exWQLcWoeJ == tDPfoBJTpg){GlCCjZXTZJ = true;}
      if(lIgUphbcIg == yVTPHpTwlN){UKQcdNUCrl = true;}
      else if(yVTPHpTwlN == lIgUphbcIg){snOuEFzexU = true;}
      if(IpqutabnCh == QHAaNccKuo){eBICmLDMyJ = true;}
      else if(QHAaNccKuo == IpqutabnCh){RNJXUtOjRy = true;}
      if(nZPKyTMspS == TdgOrIMjJs){ymQCajSUQo = true;}
      else if(TdgOrIMjJs == nZPKyTMspS){tlrjfXxNiH = true;}
      if(gcjBwWTrmg == IFFMwmYqUE){bqxmAAADwf = true;}
      else if(IFFMwmYqUE == gcjBwWTrmg){QwGujjmqxf = true;}
      if(LJeeoELTlN == qPotTWxuDh){aJWjxxKQhO = true;}
      else if(qPotTWxuDh == LJeeoELTlN){MNTIAscdhp = true;}
      if(YURIrLrVVV == zLsppTnEXy){EPyfJhsOBt = true;}
      else if(zLsppTnEXy == YURIrLrVVV){LnBbPGudPf = true;}
      if(VimoAeFpzW == cjmrFKCmeZ){uAlCKmEVCm = true;}
      if(GiBUVeujVt == ElpqxDnluU){KzPShoQfEd = true;}
      if(IsGbtLLbIj == KRgaswLPWc){YBlBkLsRcR = true;}
      while(cjmrFKCmeZ == VimoAeFpzW){HkwpDUHOmj = true;}
      while(ElpqxDnluU == ElpqxDnluU){GXmkkfSjjl = true;}
      while(KRgaswLPWc == KRgaswLPWc){uSfswctded = true;}
      if(zTSVaHbxoI == true){zTSVaHbxoI = false;}
      if(UKQcdNUCrl == true){UKQcdNUCrl = false;}
      if(eBICmLDMyJ == true){eBICmLDMyJ = false;}
      if(ymQCajSUQo == true){ymQCajSUQo = false;}
      if(bqxmAAADwf == true){bqxmAAADwf = false;}
      if(aJWjxxKQhO == true){aJWjxxKQhO = false;}
      if(EPyfJhsOBt == true){EPyfJhsOBt = false;}
      if(uAlCKmEVCm == true){uAlCKmEVCm = false;}
      if(KzPShoQfEd == true){KzPShoQfEd = false;}
      if(YBlBkLsRcR == true){YBlBkLsRcR = false;}
      if(GlCCjZXTZJ == true){GlCCjZXTZJ = false;}
      if(snOuEFzexU == true){snOuEFzexU = false;}
      if(RNJXUtOjRy == true){RNJXUtOjRy = false;}
      if(tlrjfXxNiH == true){tlrjfXxNiH = false;}
      if(QwGujjmqxf == true){QwGujjmqxf = false;}
      if(MNTIAscdhp == true){MNTIAscdhp = false;}
      if(LnBbPGudPf == true){LnBbPGudPf = false;}
      if(HkwpDUHOmj == true){HkwpDUHOmj = false;}
      if(GXmkkfSjjl == true){GXmkkfSjjl = false;}
      if(uSfswctded == true){uSfswctded = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWMWWVFYIJ
{ 
  void yjJkTnWZoh()
  { 
      bool JidXkaRJlx = false;
      bool hIfUYfbwpC = false;
      bool MkEOswQigX = false;
      bool HirxykhLFz = false;
      bool QlAGWzElRj = false;
      bool YuMRKXeOdo = false;
      bool JhbOpzQhVn = false;
      bool yQqqlZjxrt = false;
      bool rdRwyLVZmZ = false;
      bool FShQohJlQW = false;
      bool iWPckIEUej = false;
      bool mgWiwePfPd = false;
      bool cpuwhfiaCD = false;
      bool QygUKUOnLp = false;
      bool HBuDlYuyTJ = false;
      bool RdWltsbTtE = false;
      bool YdSaTozCXb = false;
      bool QbTZVbtqJJ = false;
      bool kkGrllbtZR = false;
      bool susGQdhTjx = false;
      string RWySXjODRc;
      string ifiIMsTGmj;
      string dqGOfgeIEC;
      string LYUCQTiZtq;
      string IBbMljSrJO;
      string tetOlZPjmq;
      string FFzOQJLgqs;
      string JtLwabPtbw;
      string NlzoIfdGPp;
      string DymDlDCMwb;
      string XkBQEzTymK;
      string KVHpdSFKGk;
      string eEQAoLHIKW;
      string ZCxAXbkhjI;
      string MfSFfgqwYS;
      string xqGKwTTAbs;
      string rLnPkIXHSB;
      string gWZxYzlLUH;
      string TLiqZhumDE;
      string HjGpQBrCTW;
      if(RWySXjODRc == XkBQEzTymK){JidXkaRJlx = true;}
      else if(XkBQEzTymK == RWySXjODRc){iWPckIEUej = true;}
      if(ifiIMsTGmj == KVHpdSFKGk){hIfUYfbwpC = true;}
      else if(KVHpdSFKGk == ifiIMsTGmj){mgWiwePfPd = true;}
      if(dqGOfgeIEC == eEQAoLHIKW){MkEOswQigX = true;}
      else if(eEQAoLHIKW == dqGOfgeIEC){cpuwhfiaCD = true;}
      if(LYUCQTiZtq == ZCxAXbkhjI){HirxykhLFz = true;}
      else if(ZCxAXbkhjI == LYUCQTiZtq){QygUKUOnLp = true;}
      if(IBbMljSrJO == MfSFfgqwYS){QlAGWzElRj = true;}
      else if(MfSFfgqwYS == IBbMljSrJO){HBuDlYuyTJ = true;}
      if(tetOlZPjmq == xqGKwTTAbs){YuMRKXeOdo = true;}
      else if(xqGKwTTAbs == tetOlZPjmq){RdWltsbTtE = true;}
      if(FFzOQJLgqs == rLnPkIXHSB){JhbOpzQhVn = true;}
      else if(rLnPkIXHSB == FFzOQJLgqs){YdSaTozCXb = true;}
      if(JtLwabPtbw == gWZxYzlLUH){yQqqlZjxrt = true;}
      if(NlzoIfdGPp == TLiqZhumDE){rdRwyLVZmZ = true;}
      if(DymDlDCMwb == HjGpQBrCTW){FShQohJlQW = true;}
      while(gWZxYzlLUH == JtLwabPtbw){QbTZVbtqJJ = true;}
      while(TLiqZhumDE == TLiqZhumDE){kkGrllbtZR = true;}
      while(HjGpQBrCTW == HjGpQBrCTW){susGQdhTjx = true;}
      if(JidXkaRJlx == true){JidXkaRJlx = false;}
      if(hIfUYfbwpC == true){hIfUYfbwpC = false;}
      if(MkEOswQigX == true){MkEOswQigX = false;}
      if(HirxykhLFz == true){HirxykhLFz = false;}
      if(QlAGWzElRj == true){QlAGWzElRj = false;}
      if(YuMRKXeOdo == true){YuMRKXeOdo = false;}
      if(JhbOpzQhVn == true){JhbOpzQhVn = false;}
      if(yQqqlZjxrt == true){yQqqlZjxrt = false;}
      if(rdRwyLVZmZ == true){rdRwyLVZmZ = false;}
      if(FShQohJlQW == true){FShQohJlQW = false;}
      if(iWPckIEUej == true){iWPckIEUej = false;}
      if(mgWiwePfPd == true){mgWiwePfPd = false;}
      if(cpuwhfiaCD == true){cpuwhfiaCD = false;}
      if(QygUKUOnLp == true){QygUKUOnLp = false;}
      if(HBuDlYuyTJ == true){HBuDlYuyTJ = false;}
      if(RdWltsbTtE == true){RdWltsbTtE = false;}
      if(YdSaTozCXb == true){YdSaTozCXb = false;}
      if(QbTZVbtqJJ == true){QbTZVbtqJJ = false;}
      if(kkGrllbtZR == true){kkGrllbtZR = false;}
      if(susGQdhTjx == true){susGQdhTjx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OPMRKNLCYH
{ 
  void FHeEhAKEFV()
  { 
      bool qzMojKZMQs = false;
      bool chgGCmWikM = false;
      bool ZynBTCbfoC = false;
      bool kGiTYdbkQm = false;
      bool DBJWLbAhPk = false;
      bool otZjWrLKUh = false;
      bool itWNHVyMgX = false;
      bool LkRyJYnQpr = false;
      bool BtQEMqgzxg = false;
      bool SQPhEIdwPo = false;
      bool dmBqZEbbZy = false;
      bool DuTcfncSAQ = false;
      bool oyPzFtVjsA = false;
      bool trABNNrYdI = false;
      bool OEYzcWxmCP = false;
      bool fLwzzeXBlf = false;
      bool hrhZDLtSOS = false;
      bool wEnqBjYQWh = false;
      bool xhgdUhuBBh = false;
      bool pqmyaVWzuQ = false;
      string QcRtoioCAX;
      string QGpgReZmiV;
      string EIlhXioyqN;
      string AYosTmPCZd;
      string sgcaabdKhc;
      string rCIkOHpjWG;
      string tqKlWqRxMd;
      string OXMEbXfKHu;
      string EdPNVyQEdL;
      string wfeTjCVqEi;
      string JgyEOUoDIq;
      string bfbbBPaxPY;
      string aNSAghrrUY;
      string BnGXkXfKyB;
      string IMuljQDDST;
      string aYafHwNxWg;
      string bwiipmYEqd;
      string jQyOPOSfQQ;
      string dnZAycNaQo;
      string JhnRYMcLww;
      if(QcRtoioCAX == JgyEOUoDIq){qzMojKZMQs = true;}
      else if(JgyEOUoDIq == QcRtoioCAX){dmBqZEbbZy = true;}
      if(QGpgReZmiV == bfbbBPaxPY){chgGCmWikM = true;}
      else if(bfbbBPaxPY == QGpgReZmiV){DuTcfncSAQ = true;}
      if(EIlhXioyqN == aNSAghrrUY){ZynBTCbfoC = true;}
      else if(aNSAghrrUY == EIlhXioyqN){oyPzFtVjsA = true;}
      if(AYosTmPCZd == BnGXkXfKyB){kGiTYdbkQm = true;}
      else if(BnGXkXfKyB == AYosTmPCZd){trABNNrYdI = true;}
      if(sgcaabdKhc == IMuljQDDST){DBJWLbAhPk = true;}
      else if(IMuljQDDST == sgcaabdKhc){OEYzcWxmCP = true;}
      if(rCIkOHpjWG == aYafHwNxWg){otZjWrLKUh = true;}
      else if(aYafHwNxWg == rCIkOHpjWG){fLwzzeXBlf = true;}
      if(tqKlWqRxMd == bwiipmYEqd){itWNHVyMgX = true;}
      else if(bwiipmYEqd == tqKlWqRxMd){hrhZDLtSOS = true;}
      if(OXMEbXfKHu == jQyOPOSfQQ){LkRyJYnQpr = true;}
      if(EdPNVyQEdL == dnZAycNaQo){BtQEMqgzxg = true;}
      if(wfeTjCVqEi == JhnRYMcLww){SQPhEIdwPo = true;}
      while(jQyOPOSfQQ == OXMEbXfKHu){wEnqBjYQWh = true;}
      while(dnZAycNaQo == dnZAycNaQo){xhgdUhuBBh = true;}
      while(JhnRYMcLww == JhnRYMcLww){pqmyaVWzuQ = true;}
      if(qzMojKZMQs == true){qzMojKZMQs = false;}
      if(chgGCmWikM == true){chgGCmWikM = false;}
      if(ZynBTCbfoC == true){ZynBTCbfoC = false;}
      if(kGiTYdbkQm == true){kGiTYdbkQm = false;}
      if(DBJWLbAhPk == true){DBJWLbAhPk = false;}
      if(otZjWrLKUh == true){otZjWrLKUh = false;}
      if(itWNHVyMgX == true){itWNHVyMgX = false;}
      if(LkRyJYnQpr == true){LkRyJYnQpr = false;}
      if(BtQEMqgzxg == true){BtQEMqgzxg = false;}
      if(SQPhEIdwPo == true){SQPhEIdwPo = false;}
      if(dmBqZEbbZy == true){dmBqZEbbZy = false;}
      if(DuTcfncSAQ == true){DuTcfncSAQ = false;}
      if(oyPzFtVjsA == true){oyPzFtVjsA = false;}
      if(trABNNrYdI == true){trABNNrYdI = false;}
      if(OEYzcWxmCP == true){OEYzcWxmCP = false;}
      if(fLwzzeXBlf == true){fLwzzeXBlf = false;}
      if(hrhZDLtSOS == true){hrhZDLtSOS = false;}
      if(wEnqBjYQWh == true){wEnqBjYQWh = false;}
      if(xhgdUhuBBh == true){xhgdUhuBBh = false;}
      if(pqmyaVWzuQ == true){pqmyaVWzuQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VZXDTWADYG
{ 
  void MeQdxAOkuM()
  { 
      bool EzMWOjzlQp = false;
      bool NWRInxEuos = false;
      bool TweKlqSUAp = false;
      bool ujnqdjCXDz = false;
      bool gCjDoctkqK = false;
      bool OZwXIHUBkX = false;
      bool RdkZtdiZeD = false;
      bool tgqpLRMaVI = false;
      bool wgdpbUnPiV = false;
      bool OAlegCRJIL = false;
      bool tTGmPhhFLq = false;
      bool ttfcajAuyZ = false;
      bool pSpIosuMIJ = false;
      bool ACRKNcapas = false;
      bool lhDrbUUJEx = false;
      bool CVKiVbcxyV = false;
      bool lVxCqqcVOy = false;
      bool JKUEmHOyfT = false;
      bool YlHLGdrhnl = false;
      bool zcqEHQkABj = false;
      string qENbmJHGFI;
      string JqiRBdESMZ;
      string XnskUVSzTA;
      string FftngnYjoJ;
      string AoeJhPTbnk;
      string YhAdpCKbHQ;
      string qHlFDdxujN;
      string EUcDYiJjDF;
      string BpLiaXePyd;
      string cwcYSsCZGE;
      string RYrafEExEG;
      string saXBOBwDee;
      string ygxFjIqEjf;
      string fjczmcyjCV;
      string ThLqkCXaJR;
      string wzubFjblpX;
      string NzMYZIyYOl;
      string CLAIKPVFTh;
      string jPtRigoBsD;
      string ALseITUlRc;
      if(qENbmJHGFI == RYrafEExEG){EzMWOjzlQp = true;}
      else if(RYrafEExEG == qENbmJHGFI){tTGmPhhFLq = true;}
      if(JqiRBdESMZ == saXBOBwDee){NWRInxEuos = true;}
      else if(saXBOBwDee == JqiRBdESMZ){ttfcajAuyZ = true;}
      if(XnskUVSzTA == ygxFjIqEjf){TweKlqSUAp = true;}
      else if(ygxFjIqEjf == XnskUVSzTA){pSpIosuMIJ = true;}
      if(FftngnYjoJ == fjczmcyjCV){ujnqdjCXDz = true;}
      else if(fjczmcyjCV == FftngnYjoJ){ACRKNcapas = true;}
      if(AoeJhPTbnk == ThLqkCXaJR){gCjDoctkqK = true;}
      else if(ThLqkCXaJR == AoeJhPTbnk){lhDrbUUJEx = true;}
      if(YhAdpCKbHQ == wzubFjblpX){OZwXIHUBkX = true;}
      else if(wzubFjblpX == YhAdpCKbHQ){CVKiVbcxyV = true;}
      if(qHlFDdxujN == NzMYZIyYOl){RdkZtdiZeD = true;}
      else if(NzMYZIyYOl == qHlFDdxujN){lVxCqqcVOy = true;}
      if(EUcDYiJjDF == CLAIKPVFTh){tgqpLRMaVI = true;}
      if(BpLiaXePyd == jPtRigoBsD){wgdpbUnPiV = true;}
      if(cwcYSsCZGE == ALseITUlRc){OAlegCRJIL = true;}
      while(CLAIKPVFTh == EUcDYiJjDF){JKUEmHOyfT = true;}
      while(jPtRigoBsD == jPtRigoBsD){YlHLGdrhnl = true;}
      while(ALseITUlRc == ALseITUlRc){zcqEHQkABj = true;}
      if(EzMWOjzlQp == true){EzMWOjzlQp = false;}
      if(NWRInxEuos == true){NWRInxEuos = false;}
      if(TweKlqSUAp == true){TweKlqSUAp = false;}
      if(ujnqdjCXDz == true){ujnqdjCXDz = false;}
      if(gCjDoctkqK == true){gCjDoctkqK = false;}
      if(OZwXIHUBkX == true){OZwXIHUBkX = false;}
      if(RdkZtdiZeD == true){RdkZtdiZeD = false;}
      if(tgqpLRMaVI == true){tgqpLRMaVI = false;}
      if(wgdpbUnPiV == true){wgdpbUnPiV = false;}
      if(OAlegCRJIL == true){OAlegCRJIL = false;}
      if(tTGmPhhFLq == true){tTGmPhhFLq = false;}
      if(ttfcajAuyZ == true){ttfcajAuyZ = false;}
      if(pSpIosuMIJ == true){pSpIosuMIJ = false;}
      if(ACRKNcapas == true){ACRKNcapas = false;}
      if(lhDrbUUJEx == true){lhDrbUUJEx = false;}
      if(CVKiVbcxyV == true){CVKiVbcxyV = false;}
      if(lVxCqqcVOy == true){lVxCqqcVOy = false;}
      if(JKUEmHOyfT == true){JKUEmHOyfT = false;}
      if(YlHLGdrhnl == true){YlHLGdrhnl = false;}
      if(zcqEHQkABj == true){zcqEHQkABj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YJGQLUINYI
{ 
  void iGatIKqWlO()
  { 
      bool NtIFgEfpoM = false;
      bool buQMArauKu = false;
      bool XKOCgjsPFU = false;
      bool thniJoylIV = false;
      bool zidcDNGmrS = false;
      bool ylLSjCfFYw = false;
      bool LQkTSsGhDK = false;
      bool somnwoglyS = false;
      bool dGXmWHWVyG = false;
      bool JrMLKiyJKK = false;
      bool GXigYJzXWu = false;
      bool VtGFRErxxK = false;
      bool VkjwBAcacM = false;
      bool pWbnMGWqNM = false;
      bool IzzCjPlGsF = false;
      bool pAMznUnmfX = false;
      bool gYtJEzRSsL = false;
      bool hBijCWlgLk = false;
      bool OVgWWpJbzr = false;
      bool RjKpfjEoxk = false;
      string YzZcPHrLQb;
      string gLDSewSVNr;
      string xdnadTfcek;
      string nEfZhmfjoF;
      string pEOLMYUrrj;
      string enWMnuKyzw;
      string bOffnbedkr;
      string QhgIBrPbOF;
      string ymkuFAgSkl;
      string bhksdbYhXj;
      string sqHASwGOKu;
      string fiitxndjZn;
      string tMryPixneZ;
      string TgDeLHfjbJ;
      string sSHpGsypuo;
      string ynHjofyIjj;
      string ySjkayeEho;
      string IsHQubECqW;
      string jGroafZToe;
      string IXArKZhVOI;
      if(YzZcPHrLQb == sqHASwGOKu){NtIFgEfpoM = true;}
      else if(sqHASwGOKu == YzZcPHrLQb){GXigYJzXWu = true;}
      if(gLDSewSVNr == fiitxndjZn){buQMArauKu = true;}
      else if(fiitxndjZn == gLDSewSVNr){VtGFRErxxK = true;}
      if(xdnadTfcek == tMryPixneZ){XKOCgjsPFU = true;}
      else if(tMryPixneZ == xdnadTfcek){VkjwBAcacM = true;}
      if(nEfZhmfjoF == TgDeLHfjbJ){thniJoylIV = true;}
      else if(TgDeLHfjbJ == nEfZhmfjoF){pWbnMGWqNM = true;}
      if(pEOLMYUrrj == sSHpGsypuo){zidcDNGmrS = true;}
      else if(sSHpGsypuo == pEOLMYUrrj){IzzCjPlGsF = true;}
      if(enWMnuKyzw == ynHjofyIjj){ylLSjCfFYw = true;}
      else if(ynHjofyIjj == enWMnuKyzw){pAMznUnmfX = true;}
      if(bOffnbedkr == ySjkayeEho){LQkTSsGhDK = true;}
      else if(ySjkayeEho == bOffnbedkr){gYtJEzRSsL = true;}
      if(QhgIBrPbOF == IsHQubECqW){somnwoglyS = true;}
      if(ymkuFAgSkl == jGroafZToe){dGXmWHWVyG = true;}
      if(bhksdbYhXj == IXArKZhVOI){JrMLKiyJKK = true;}
      while(IsHQubECqW == QhgIBrPbOF){hBijCWlgLk = true;}
      while(jGroafZToe == jGroafZToe){OVgWWpJbzr = true;}
      while(IXArKZhVOI == IXArKZhVOI){RjKpfjEoxk = true;}
      if(NtIFgEfpoM == true){NtIFgEfpoM = false;}
      if(buQMArauKu == true){buQMArauKu = false;}
      if(XKOCgjsPFU == true){XKOCgjsPFU = false;}
      if(thniJoylIV == true){thniJoylIV = false;}
      if(zidcDNGmrS == true){zidcDNGmrS = false;}
      if(ylLSjCfFYw == true){ylLSjCfFYw = false;}
      if(LQkTSsGhDK == true){LQkTSsGhDK = false;}
      if(somnwoglyS == true){somnwoglyS = false;}
      if(dGXmWHWVyG == true){dGXmWHWVyG = false;}
      if(JrMLKiyJKK == true){JrMLKiyJKK = false;}
      if(GXigYJzXWu == true){GXigYJzXWu = false;}
      if(VtGFRErxxK == true){VtGFRErxxK = false;}
      if(VkjwBAcacM == true){VkjwBAcacM = false;}
      if(pWbnMGWqNM == true){pWbnMGWqNM = false;}
      if(IzzCjPlGsF == true){IzzCjPlGsF = false;}
      if(pAMznUnmfX == true){pAMznUnmfX = false;}
      if(gYtJEzRSsL == true){gYtJEzRSsL = false;}
      if(hBijCWlgLk == true){hBijCWlgLk = false;}
      if(OVgWWpJbzr == true){OVgWWpJbzr = false;}
      if(RjKpfjEoxk == true){RjKpfjEoxk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AWCFTUIHOM
{ 
  void SNLTgjBdwQ()
  { 
      bool swPtOiESMr = false;
      bool mOGwuCCDFm = false;
      bool BttVHTDzgi = false;
      bool GLWgEGGMiN = false;
      bool ICSrdPrxXq = false;
      bool bLaDMzCtmu = false;
      bool eEldkarZqn = false;
      bool woTqeyaCqr = false;
      bool bGboGukSTE = false;
      bool ELZniDQnGD = false;
      bool XSFiulqiYN = false;
      bool XADuTYcxWp = false;
      bool pYFmjkPeHa = false;
      bool hmunUIArtU = false;
      bool DBsFfEIeUK = false;
      bool ZTRPMyMSzK = false;
      bool VMaxfkEPaK = false;
      bool XkCCmnezGe = false;
      bool ckKxBOUfaV = false;
      bool whrjyqawZu = false;
      string tzPttkJtrd;
      string GczaUQxSrt;
      string nCpmCLeYLf;
      string sSmNRGggGI;
      string AszLnxVsZO;
      string OISYhqIbqh;
      string FjiLkmolIO;
      string jPLisuDezF;
      string plzwRjAOea;
      string xEpXCQJmZA;
      string HikLdywiel;
      string ndclrTkltA;
      string maGhReZmgc;
      string kPEyyGBmSS;
      string mQirlSbDfh;
      string fXsZNfcCtz;
      string YJCCBXYemk;
      string SxSaMVrNuy;
      string DVHyxNVejR;
      string dysTtdOfqO;
      if(tzPttkJtrd == HikLdywiel){swPtOiESMr = true;}
      else if(HikLdywiel == tzPttkJtrd){XSFiulqiYN = true;}
      if(GczaUQxSrt == ndclrTkltA){mOGwuCCDFm = true;}
      else if(ndclrTkltA == GczaUQxSrt){XADuTYcxWp = true;}
      if(nCpmCLeYLf == maGhReZmgc){BttVHTDzgi = true;}
      else if(maGhReZmgc == nCpmCLeYLf){pYFmjkPeHa = true;}
      if(sSmNRGggGI == kPEyyGBmSS){GLWgEGGMiN = true;}
      else if(kPEyyGBmSS == sSmNRGggGI){hmunUIArtU = true;}
      if(AszLnxVsZO == mQirlSbDfh){ICSrdPrxXq = true;}
      else if(mQirlSbDfh == AszLnxVsZO){DBsFfEIeUK = true;}
      if(OISYhqIbqh == fXsZNfcCtz){bLaDMzCtmu = true;}
      else if(fXsZNfcCtz == OISYhqIbqh){ZTRPMyMSzK = true;}
      if(FjiLkmolIO == YJCCBXYemk){eEldkarZqn = true;}
      else if(YJCCBXYemk == FjiLkmolIO){VMaxfkEPaK = true;}
      if(jPLisuDezF == SxSaMVrNuy){woTqeyaCqr = true;}
      if(plzwRjAOea == DVHyxNVejR){bGboGukSTE = true;}
      if(xEpXCQJmZA == dysTtdOfqO){ELZniDQnGD = true;}
      while(SxSaMVrNuy == jPLisuDezF){XkCCmnezGe = true;}
      while(DVHyxNVejR == DVHyxNVejR){ckKxBOUfaV = true;}
      while(dysTtdOfqO == dysTtdOfqO){whrjyqawZu = true;}
      if(swPtOiESMr == true){swPtOiESMr = false;}
      if(mOGwuCCDFm == true){mOGwuCCDFm = false;}
      if(BttVHTDzgi == true){BttVHTDzgi = false;}
      if(GLWgEGGMiN == true){GLWgEGGMiN = false;}
      if(ICSrdPrxXq == true){ICSrdPrxXq = false;}
      if(bLaDMzCtmu == true){bLaDMzCtmu = false;}
      if(eEldkarZqn == true){eEldkarZqn = false;}
      if(woTqeyaCqr == true){woTqeyaCqr = false;}
      if(bGboGukSTE == true){bGboGukSTE = false;}
      if(ELZniDQnGD == true){ELZniDQnGD = false;}
      if(XSFiulqiYN == true){XSFiulqiYN = false;}
      if(XADuTYcxWp == true){XADuTYcxWp = false;}
      if(pYFmjkPeHa == true){pYFmjkPeHa = false;}
      if(hmunUIArtU == true){hmunUIArtU = false;}
      if(DBsFfEIeUK == true){DBsFfEIeUK = false;}
      if(ZTRPMyMSzK == true){ZTRPMyMSzK = false;}
      if(VMaxfkEPaK == true){VMaxfkEPaK = false;}
      if(XkCCmnezGe == true){XkCCmnezGe = false;}
      if(ckKxBOUfaV == true){ckKxBOUfaV = false;}
      if(whrjyqawZu == true){whrjyqawZu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJGMMUIGBY
{ 
  void WHzVVrFrVa()
  { 
      bool VgFdXwpeYk = false;
      bool TZawYHQqml = false;
      bool IVeJrGoSBI = false;
      bool tkmwREftsF = false;
      bool pBleIKqBbw = false;
      bool gUNixzCwkR = false;
      bool HWcPqhleeU = false;
      bool bVxgwGiABh = false;
      bool OmpFbYXDyR = false;
      bool CiJbyTYWmZ = false;
      bool XLWHTKXfmp = false;
      bool PCuDCUfWmS = false;
      bool KifMSsMVib = false;
      bool hMMaJCPikQ = false;
      bool BqPIBznFYc = false;
      bool mBiUPofJoa = false;
      bool yBxKHCpUsA = false;
      bool ExkWQSSXKS = false;
      bool FGwFogdqKU = false;
      bool WFsKRzsFAy = false;
      string bbklclVUAI;
      string JmjLcziimW;
      string pQnJAduuDd;
      string IronMNGuBI;
      string eILYihcYoR;
      string JBBUpLmbky;
      string qaRWARywyP;
      string smheqgFPZR;
      string BVGkTGqUyB;
      string ZeKDQEpnYR;
      string jgZYYVTVcJ;
      string GXCSwUUgDs;
      string adyxoNceNm;
      string pQpHhTugMx;
      string lUqnuCbqGw;
      string jJkeqGiciK;
      string soIpSogukc;
      string YmTFGFlJBm;
      string lkXRCffKPb;
      string jSyBDxLBVF;
      if(bbklclVUAI == jgZYYVTVcJ){VgFdXwpeYk = true;}
      else if(jgZYYVTVcJ == bbklclVUAI){XLWHTKXfmp = true;}
      if(JmjLcziimW == GXCSwUUgDs){TZawYHQqml = true;}
      else if(GXCSwUUgDs == JmjLcziimW){PCuDCUfWmS = true;}
      if(pQnJAduuDd == adyxoNceNm){IVeJrGoSBI = true;}
      else if(adyxoNceNm == pQnJAduuDd){KifMSsMVib = true;}
      if(IronMNGuBI == pQpHhTugMx){tkmwREftsF = true;}
      else if(pQpHhTugMx == IronMNGuBI){hMMaJCPikQ = true;}
      if(eILYihcYoR == lUqnuCbqGw){pBleIKqBbw = true;}
      else if(lUqnuCbqGw == eILYihcYoR){BqPIBznFYc = true;}
      if(JBBUpLmbky == jJkeqGiciK){gUNixzCwkR = true;}
      else if(jJkeqGiciK == JBBUpLmbky){mBiUPofJoa = true;}
      if(qaRWARywyP == soIpSogukc){HWcPqhleeU = true;}
      else if(soIpSogukc == qaRWARywyP){yBxKHCpUsA = true;}
      if(smheqgFPZR == YmTFGFlJBm){bVxgwGiABh = true;}
      if(BVGkTGqUyB == lkXRCffKPb){OmpFbYXDyR = true;}
      if(ZeKDQEpnYR == jSyBDxLBVF){CiJbyTYWmZ = true;}
      while(YmTFGFlJBm == smheqgFPZR){ExkWQSSXKS = true;}
      while(lkXRCffKPb == lkXRCffKPb){FGwFogdqKU = true;}
      while(jSyBDxLBVF == jSyBDxLBVF){WFsKRzsFAy = true;}
      if(VgFdXwpeYk == true){VgFdXwpeYk = false;}
      if(TZawYHQqml == true){TZawYHQqml = false;}
      if(IVeJrGoSBI == true){IVeJrGoSBI = false;}
      if(tkmwREftsF == true){tkmwREftsF = false;}
      if(pBleIKqBbw == true){pBleIKqBbw = false;}
      if(gUNixzCwkR == true){gUNixzCwkR = false;}
      if(HWcPqhleeU == true){HWcPqhleeU = false;}
      if(bVxgwGiABh == true){bVxgwGiABh = false;}
      if(OmpFbYXDyR == true){OmpFbYXDyR = false;}
      if(CiJbyTYWmZ == true){CiJbyTYWmZ = false;}
      if(XLWHTKXfmp == true){XLWHTKXfmp = false;}
      if(PCuDCUfWmS == true){PCuDCUfWmS = false;}
      if(KifMSsMVib == true){KifMSsMVib = false;}
      if(hMMaJCPikQ == true){hMMaJCPikQ = false;}
      if(BqPIBznFYc == true){BqPIBznFYc = false;}
      if(mBiUPofJoa == true){mBiUPofJoa = false;}
      if(yBxKHCpUsA == true){yBxKHCpUsA = false;}
      if(ExkWQSSXKS == true){ExkWQSSXKS = false;}
      if(FGwFogdqKU == true){FGwFogdqKU = false;}
      if(WFsKRzsFAy == true){WFsKRzsFAy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VPQCBKZKVQ
{ 
  void PaDlBTQkmF()
  { 
      bool hxrAqPSmDI = false;
      bool TieaCElLZc = false;
      bool zBMdNqufJk = false;
      bool yoQgnRFwPu = false;
      bool qonrZbhOJh = false;
      bool QDmyEgjOmA = false;
      bool UmdSJdRxmk = false;
      bool ypuekKMUDk = false;
      bool JfVaUuBRbH = false;
      bool hqJOaELVhu = false;
      bool JjbYiZHIMt = false;
      bool TOKBqnQCxO = false;
      bool czVfCHggEg = false;
      bool zqmIaZExqt = false;
      bool msFhmSfHXl = false;
      bool nIXSRJOwVb = false;
      bool saDfucbBaR = false;
      bool jSKDajtmrj = false;
      bool aZJRrpTTpR = false;
      bool KHbPBMoYmJ = false;
      string JVRmLgBehX;
      string uaKYojxSDa;
      string eqpwKgknjo;
      string DAdglkPeNY;
      string nbMmKVMWBM;
      string iKziKRfUbe;
      string uMtrTuxdmD;
      string UREemCeClo;
      string UNlWGsBuWT;
      string EtDicahTSP;
      string YhjxrQFTwH;
      string mcimJhZWka;
      string tBHSzZOVCL;
      string UKjVPldoeo;
      string mgyOgbKPYu;
      string AKirVWaQyS;
      string CjRkmbsNWX;
      string DkrunMDrlW;
      string PyxGKJbrAs;
      string KMpMlCONbE;
      if(JVRmLgBehX == YhjxrQFTwH){hxrAqPSmDI = true;}
      else if(YhjxrQFTwH == JVRmLgBehX){JjbYiZHIMt = true;}
      if(uaKYojxSDa == mcimJhZWka){TieaCElLZc = true;}
      else if(mcimJhZWka == uaKYojxSDa){TOKBqnQCxO = true;}
      if(eqpwKgknjo == tBHSzZOVCL){zBMdNqufJk = true;}
      else if(tBHSzZOVCL == eqpwKgknjo){czVfCHggEg = true;}
      if(DAdglkPeNY == UKjVPldoeo){yoQgnRFwPu = true;}
      else if(UKjVPldoeo == DAdglkPeNY){zqmIaZExqt = true;}
      if(nbMmKVMWBM == mgyOgbKPYu){qonrZbhOJh = true;}
      else if(mgyOgbKPYu == nbMmKVMWBM){msFhmSfHXl = true;}
      if(iKziKRfUbe == AKirVWaQyS){QDmyEgjOmA = true;}
      else if(AKirVWaQyS == iKziKRfUbe){nIXSRJOwVb = true;}
      if(uMtrTuxdmD == CjRkmbsNWX){UmdSJdRxmk = true;}
      else if(CjRkmbsNWX == uMtrTuxdmD){saDfucbBaR = true;}
      if(UREemCeClo == DkrunMDrlW){ypuekKMUDk = true;}
      if(UNlWGsBuWT == PyxGKJbrAs){JfVaUuBRbH = true;}
      if(EtDicahTSP == KMpMlCONbE){hqJOaELVhu = true;}
      while(DkrunMDrlW == UREemCeClo){jSKDajtmrj = true;}
      while(PyxGKJbrAs == PyxGKJbrAs){aZJRrpTTpR = true;}
      while(KMpMlCONbE == KMpMlCONbE){KHbPBMoYmJ = true;}
      if(hxrAqPSmDI == true){hxrAqPSmDI = false;}
      if(TieaCElLZc == true){TieaCElLZc = false;}
      if(zBMdNqufJk == true){zBMdNqufJk = false;}
      if(yoQgnRFwPu == true){yoQgnRFwPu = false;}
      if(qonrZbhOJh == true){qonrZbhOJh = false;}
      if(QDmyEgjOmA == true){QDmyEgjOmA = false;}
      if(UmdSJdRxmk == true){UmdSJdRxmk = false;}
      if(ypuekKMUDk == true){ypuekKMUDk = false;}
      if(JfVaUuBRbH == true){JfVaUuBRbH = false;}
      if(hqJOaELVhu == true){hqJOaELVhu = false;}
      if(JjbYiZHIMt == true){JjbYiZHIMt = false;}
      if(TOKBqnQCxO == true){TOKBqnQCxO = false;}
      if(czVfCHggEg == true){czVfCHggEg = false;}
      if(zqmIaZExqt == true){zqmIaZExqt = false;}
      if(msFhmSfHXl == true){msFhmSfHXl = false;}
      if(nIXSRJOwVb == true){nIXSRJOwVb = false;}
      if(saDfucbBaR == true){saDfucbBaR = false;}
      if(jSKDajtmrj == true){jSKDajtmrj = false;}
      if(aZJRrpTTpR == true){aZJRrpTTpR = false;}
      if(KHbPBMoYmJ == true){KHbPBMoYmJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UNNGDIBOWO
{ 
  void ghxQRZUwlF()
  { 
      bool zZIfuzDhGE = false;
      bool gQMEeLlMxp = false;
      bool lDoZJyuoVL = false;
      bool bTkYrZxErd = false;
      bool hTfToqePaO = false;
      bool hXzurujhWx = false;
      bool DNMucNfnLE = false;
      bool OhTTHSXUjR = false;
      bool SfOHcDTogw = false;
      bool oOgtZUHjqb = false;
      bool LpDVzAEfnZ = false;
      bool XPyFeXyFRY = false;
      bool spHOPzAZsl = false;
      bool KmdHFbcsHc = false;
      bool znBHYZQbPC = false;
      bool VBSSiVinGA = false;
      bool zemCOjkpAC = false;
      bool tFynYFoApo = false;
      bool hYJpPIULYj = false;
      bool snlGdUAzrn = false;
      string LasAlwflwb;
      string KTLhtglrrE;
      string hjXiXCAHBj;
      string CzqCSICBwg;
      string SQgkbOhDOx;
      string NDlCcaDKbi;
      string uXkLYLbJPl;
      string ejwLkQDmGI;
      string UwrDWzMnYr;
      string FqYMktfUMQ;
      string mXncSdGaRL;
      string XPETOzegoY;
      string ynjXgmLiZq;
      string jhZpVwIPks;
      string rkWMTomFyl;
      string OyemRynQwe;
      string RXAZbopNxR;
      string pPuwfMQWDq;
      string zFknckClYW;
      string IrTGaUkxke;
      if(LasAlwflwb == mXncSdGaRL){zZIfuzDhGE = true;}
      else if(mXncSdGaRL == LasAlwflwb){LpDVzAEfnZ = true;}
      if(KTLhtglrrE == XPETOzegoY){gQMEeLlMxp = true;}
      else if(XPETOzegoY == KTLhtglrrE){XPyFeXyFRY = true;}
      if(hjXiXCAHBj == ynjXgmLiZq){lDoZJyuoVL = true;}
      else if(ynjXgmLiZq == hjXiXCAHBj){spHOPzAZsl = true;}
      if(CzqCSICBwg == jhZpVwIPks){bTkYrZxErd = true;}
      else if(jhZpVwIPks == CzqCSICBwg){KmdHFbcsHc = true;}
      if(SQgkbOhDOx == rkWMTomFyl){hTfToqePaO = true;}
      else if(rkWMTomFyl == SQgkbOhDOx){znBHYZQbPC = true;}
      if(NDlCcaDKbi == OyemRynQwe){hXzurujhWx = true;}
      else if(OyemRynQwe == NDlCcaDKbi){VBSSiVinGA = true;}
      if(uXkLYLbJPl == RXAZbopNxR){DNMucNfnLE = true;}
      else if(RXAZbopNxR == uXkLYLbJPl){zemCOjkpAC = true;}
      if(ejwLkQDmGI == pPuwfMQWDq){OhTTHSXUjR = true;}
      if(UwrDWzMnYr == zFknckClYW){SfOHcDTogw = true;}
      if(FqYMktfUMQ == IrTGaUkxke){oOgtZUHjqb = true;}
      while(pPuwfMQWDq == ejwLkQDmGI){tFynYFoApo = true;}
      while(zFknckClYW == zFknckClYW){hYJpPIULYj = true;}
      while(IrTGaUkxke == IrTGaUkxke){snlGdUAzrn = true;}
      if(zZIfuzDhGE == true){zZIfuzDhGE = false;}
      if(gQMEeLlMxp == true){gQMEeLlMxp = false;}
      if(lDoZJyuoVL == true){lDoZJyuoVL = false;}
      if(bTkYrZxErd == true){bTkYrZxErd = false;}
      if(hTfToqePaO == true){hTfToqePaO = false;}
      if(hXzurujhWx == true){hXzurujhWx = false;}
      if(DNMucNfnLE == true){DNMucNfnLE = false;}
      if(OhTTHSXUjR == true){OhTTHSXUjR = false;}
      if(SfOHcDTogw == true){SfOHcDTogw = false;}
      if(oOgtZUHjqb == true){oOgtZUHjqb = false;}
      if(LpDVzAEfnZ == true){LpDVzAEfnZ = false;}
      if(XPyFeXyFRY == true){XPyFeXyFRY = false;}
      if(spHOPzAZsl == true){spHOPzAZsl = false;}
      if(KmdHFbcsHc == true){KmdHFbcsHc = false;}
      if(znBHYZQbPC == true){znBHYZQbPC = false;}
      if(VBSSiVinGA == true){VBSSiVinGA = false;}
      if(zemCOjkpAC == true){zemCOjkpAC = false;}
      if(tFynYFoApo == true){tFynYFoApo = false;}
      if(hYJpPIULYj == true){hYJpPIULYj = false;}
      if(snlGdUAzrn == true){snlGdUAzrn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EYBBAWPKHL
{ 
  void cQBzBXdXge()
  { 
      bool dJdlRDjcNC = false;
      bool FdCtntGEUQ = false;
      bool yLQcfQmXHP = false;
      bool wnkyfmRSZf = false;
      bool FAAArWrOyB = false;
      bool rVsVBSsAFA = false;
      bool QMVxGRrEOB = false;
      bool cneoKyKPkJ = false;
      bool XXYFXZtPwM = false;
      bool sQNZOsdCtZ = false;
      bool dnAxYEqDKD = false;
      bool HcPucsmPZf = false;
      bool WcHBHLZEaR = false;
      bool THVKfiXagS = false;
      bool hpErEQBSxV = false;
      bool FOcNCBfypM = false;
      bool elcsjzHEOs = false;
      bool UMiHygXPwq = false;
      bool KHHEMFeHHe = false;
      bool CYjTmuNLIE = false;
      string rdKMgPaYjT;
      string yUlRQltYTs;
      string LaRJtgkjFN;
      string AMondgfFAO;
      string AxsWIJOOCT;
      string gGWgERLBSA;
      string epTWTleymj;
      string GoXFsOguBk;
      string RWgkfspIiM;
      string UemAjJdWDW;
      string eQaSMriRnp;
      string kQzghHJipZ;
      string uWPZObBWUi;
      string jJqeGBuNXm;
      string KXTrbEeFSc;
      string zufcaIBAEk;
      string qLwEFaZUag;
      string LwKDPXCXyK;
      string xwEqiocNDx;
      string AuJmwzaOlA;
      if(rdKMgPaYjT == eQaSMriRnp){dJdlRDjcNC = true;}
      else if(eQaSMriRnp == rdKMgPaYjT){dnAxYEqDKD = true;}
      if(yUlRQltYTs == kQzghHJipZ){FdCtntGEUQ = true;}
      else if(kQzghHJipZ == yUlRQltYTs){HcPucsmPZf = true;}
      if(LaRJtgkjFN == uWPZObBWUi){yLQcfQmXHP = true;}
      else if(uWPZObBWUi == LaRJtgkjFN){WcHBHLZEaR = true;}
      if(AMondgfFAO == jJqeGBuNXm){wnkyfmRSZf = true;}
      else if(jJqeGBuNXm == AMondgfFAO){THVKfiXagS = true;}
      if(AxsWIJOOCT == KXTrbEeFSc){FAAArWrOyB = true;}
      else if(KXTrbEeFSc == AxsWIJOOCT){hpErEQBSxV = true;}
      if(gGWgERLBSA == zufcaIBAEk){rVsVBSsAFA = true;}
      else if(zufcaIBAEk == gGWgERLBSA){FOcNCBfypM = true;}
      if(epTWTleymj == qLwEFaZUag){QMVxGRrEOB = true;}
      else if(qLwEFaZUag == epTWTleymj){elcsjzHEOs = true;}
      if(GoXFsOguBk == LwKDPXCXyK){cneoKyKPkJ = true;}
      if(RWgkfspIiM == xwEqiocNDx){XXYFXZtPwM = true;}
      if(UemAjJdWDW == AuJmwzaOlA){sQNZOsdCtZ = true;}
      while(LwKDPXCXyK == GoXFsOguBk){UMiHygXPwq = true;}
      while(xwEqiocNDx == xwEqiocNDx){KHHEMFeHHe = true;}
      while(AuJmwzaOlA == AuJmwzaOlA){CYjTmuNLIE = true;}
      if(dJdlRDjcNC == true){dJdlRDjcNC = false;}
      if(FdCtntGEUQ == true){FdCtntGEUQ = false;}
      if(yLQcfQmXHP == true){yLQcfQmXHP = false;}
      if(wnkyfmRSZf == true){wnkyfmRSZf = false;}
      if(FAAArWrOyB == true){FAAArWrOyB = false;}
      if(rVsVBSsAFA == true){rVsVBSsAFA = false;}
      if(QMVxGRrEOB == true){QMVxGRrEOB = false;}
      if(cneoKyKPkJ == true){cneoKyKPkJ = false;}
      if(XXYFXZtPwM == true){XXYFXZtPwM = false;}
      if(sQNZOsdCtZ == true){sQNZOsdCtZ = false;}
      if(dnAxYEqDKD == true){dnAxYEqDKD = false;}
      if(HcPucsmPZf == true){HcPucsmPZf = false;}
      if(WcHBHLZEaR == true){WcHBHLZEaR = false;}
      if(THVKfiXagS == true){THVKfiXagS = false;}
      if(hpErEQBSxV == true){hpErEQBSxV = false;}
      if(FOcNCBfypM == true){FOcNCBfypM = false;}
      if(elcsjzHEOs == true){elcsjzHEOs = false;}
      if(UMiHygXPwq == true){UMiHygXPwq = false;}
      if(KHHEMFeHHe == true){KHHEMFeHHe = false;}
      if(CYjTmuNLIE == true){CYjTmuNLIE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VCGUHVEDWU
{ 
  void LUCtcBMZcu()
  { 
      bool zcLSHcdAjk = false;
      bool lRTiKxLCzY = false;
      bool NhaUZmWxyr = false;
      bool GAgbIjwnSo = false;
      bool SbyKQCTmMC = false;
      bool DUTjjRCqrT = false;
      bool FgBreljrZZ = false;
      bool BXiJGkiPEX = false;
      bool Tijwnlfxrp = false;
      bool gFuyjkZFfd = false;
      bool SbNlBekKdy = false;
      bool hmmTAVwFDs = false;
      bool FmzisubkYU = false;
      bool LcjZFrVxtJ = false;
      bool AVSsItSbxO = false;
      bool oTClYebdsF = false;
      bool CAkImEDNOI = false;
      bool zyLtrjTGay = false;
      bool cAmKfqaxAZ = false;
      bool QrEnGAkKGD = false;
      string swrSpMGGPS;
      string hLpVmPRWnd;
      string QuxGVIOXLG;
      string JUQVDGTLRo;
      string LHNpEEzZug;
      string DpjYZyzkwg;
      string yitIIMuTRf;
      string wFEzRIgHCR;
      string JobeDTjqwE;
      string HiOkqcNEgq;
      string JfHOjxlkGQ;
      string RqheXIGOFo;
      string cDWNXNqTIo;
      string ubaLHchMtG;
      string hzkemQAiMh;
      string WyzqOFItpW;
      string FScRVoQWWt;
      string asUzHcSqZH;
      string MIGZSwbiwC;
      string TmVWAPWSJx;
      if(swrSpMGGPS == JfHOjxlkGQ){zcLSHcdAjk = true;}
      else if(JfHOjxlkGQ == swrSpMGGPS){SbNlBekKdy = true;}
      if(hLpVmPRWnd == RqheXIGOFo){lRTiKxLCzY = true;}
      else if(RqheXIGOFo == hLpVmPRWnd){hmmTAVwFDs = true;}
      if(QuxGVIOXLG == cDWNXNqTIo){NhaUZmWxyr = true;}
      else if(cDWNXNqTIo == QuxGVIOXLG){FmzisubkYU = true;}
      if(JUQVDGTLRo == ubaLHchMtG){GAgbIjwnSo = true;}
      else if(ubaLHchMtG == JUQVDGTLRo){LcjZFrVxtJ = true;}
      if(LHNpEEzZug == hzkemQAiMh){SbyKQCTmMC = true;}
      else if(hzkemQAiMh == LHNpEEzZug){AVSsItSbxO = true;}
      if(DpjYZyzkwg == WyzqOFItpW){DUTjjRCqrT = true;}
      else if(WyzqOFItpW == DpjYZyzkwg){oTClYebdsF = true;}
      if(yitIIMuTRf == FScRVoQWWt){FgBreljrZZ = true;}
      else if(FScRVoQWWt == yitIIMuTRf){CAkImEDNOI = true;}
      if(wFEzRIgHCR == asUzHcSqZH){BXiJGkiPEX = true;}
      if(JobeDTjqwE == MIGZSwbiwC){Tijwnlfxrp = true;}
      if(HiOkqcNEgq == TmVWAPWSJx){gFuyjkZFfd = true;}
      while(asUzHcSqZH == wFEzRIgHCR){zyLtrjTGay = true;}
      while(MIGZSwbiwC == MIGZSwbiwC){cAmKfqaxAZ = true;}
      while(TmVWAPWSJx == TmVWAPWSJx){QrEnGAkKGD = true;}
      if(zcLSHcdAjk == true){zcLSHcdAjk = false;}
      if(lRTiKxLCzY == true){lRTiKxLCzY = false;}
      if(NhaUZmWxyr == true){NhaUZmWxyr = false;}
      if(GAgbIjwnSo == true){GAgbIjwnSo = false;}
      if(SbyKQCTmMC == true){SbyKQCTmMC = false;}
      if(DUTjjRCqrT == true){DUTjjRCqrT = false;}
      if(FgBreljrZZ == true){FgBreljrZZ = false;}
      if(BXiJGkiPEX == true){BXiJGkiPEX = false;}
      if(Tijwnlfxrp == true){Tijwnlfxrp = false;}
      if(gFuyjkZFfd == true){gFuyjkZFfd = false;}
      if(SbNlBekKdy == true){SbNlBekKdy = false;}
      if(hmmTAVwFDs == true){hmmTAVwFDs = false;}
      if(FmzisubkYU == true){FmzisubkYU = false;}
      if(LcjZFrVxtJ == true){LcjZFrVxtJ = false;}
      if(AVSsItSbxO == true){AVSsItSbxO = false;}
      if(oTClYebdsF == true){oTClYebdsF = false;}
      if(CAkImEDNOI == true){CAkImEDNOI = false;}
      if(zyLtrjTGay == true){zyLtrjTGay = false;}
      if(cAmKfqaxAZ == true){cAmKfqaxAZ = false;}
      if(QrEnGAkKGD == true){QrEnGAkKGD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GJNAGTRDPG
{ 
  void TUtWmuXPVX()
  { 
      bool IrCqKobxiM = false;
      bool cSXPBizsxh = false;
      bool zxakHGgtqF = false;
      bool QFeZhDwZFF = false;
      bool DIxPCBpmMq = false;
      bool YVHwyLRQiD = false;
      bool HgGduWnxhx = false;
      bool mYnqepzKiF = false;
      bool QtgzftxhbW = false;
      bool lepByVBTTe = false;
      bool NrEPDzhPRH = false;
      bool LHhdlMAGxA = false;
      bool ZFVKLHhlsI = false;
      bool ofpDqYoRwg = false;
      bool MgQTKexMOk = false;
      bool UtWSFIWtDw = false;
      bool RuWISfQdlN = false;
      bool XiKPnroBzg = false;
      bool JVXHmtIWyi = false;
      bool CuNzPRJHBe = false;
      string IBhZWTGYFU;
      string VbqPpSSLbu;
      string uZHtbZIRCZ;
      string NnJTKDHzlV;
      string HaSjdNAbWA;
      string SZKzxhtnxw;
      string LoVfGgRXEl;
      string KTZFmUHWQN;
      string YgtBGncJVc;
      string JSBpKSEmdw;
      string ucWjozAELc;
      string ZWXiWetUYR;
      string EIBacrRiuT;
      string PUsUSuJJLH;
      string nXxrDluSSf;
      string YjOMrmbwGx;
      string hQJrNFdDQa;
      string UjIQcfKJXq;
      string wyQPteGgbe;
      string TNCOZXOFex;
      if(IBhZWTGYFU == ucWjozAELc){IrCqKobxiM = true;}
      else if(ucWjozAELc == IBhZWTGYFU){NrEPDzhPRH = true;}
      if(VbqPpSSLbu == ZWXiWetUYR){cSXPBizsxh = true;}
      else if(ZWXiWetUYR == VbqPpSSLbu){LHhdlMAGxA = true;}
      if(uZHtbZIRCZ == EIBacrRiuT){zxakHGgtqF = true;}
      else if(EIBacrRiuT == uZHtbZIRCZ){ZFVKLHhlsI = true;}
      if(NnJTKDHzlV == PUsUSuJJLH){QFeZhDwZFF = true;}
      else if(PUsUSuJJLH == NnJTKDHzlV){ofpDqYoRwg = true;}
      if(HaSjdNAbWA == nXxrDluSSf){DIxPCBpmMq = true;}
      else if(nXxrDluSSf == HaSjdNAbWA){MgQTKexMOk = true;}
      if(SZKzxhtnxw == YjOMrmbwGx){YVHwyLRQiD = true;}
      else if(YjOMrmbwGx == SZKzxhtnxw){UtWSFIWtDw = true;}
      if(LoVfGgRXEl == hQJrNFdDQa){HgGduWnxhx = true;}
      else if(hQJrNFdDQa == LoVfGgRXEl){RuWISfQdlN = true;}
      if(KTZFmUHWQN == UjIQcfKJXq){mYnqepzKiF = true;}
      if(YgtBGncJVc == wyQPteGgbe){QtgzftxhbW = true;}
      if(JSBpKSEmdw == TNCOZXOFex){lepByVBTTe = true;}
      while(UjIQcfKJXq == KTZFmUHWQN){XiKPnroBzg = true;}
      while(wyQPteGgbe == wyQPteGgbe){JVXHmtIWyi = true;}
      while(TNCOZXOFex == TNCOZXOFex){CuNzPRJHBe = true;}
      if(IrCqKobxiM == true){IrCqKobxiM = false;}
      if(cSXPBizsxh == true){cSXPBizsxh = false;}
      if(zxakHGgtqF == true){zxakHGgtqF = false;}
      if(QFeZhDwZFF == true){QFeZhDwZFF = false;}
      if(DIxPCBpmMq == true){DIxPCBpmMq = false;}
      if(YVHwyLRQiD == true){YVHwyLRQiD = false;}
      if(HgGduWnxhx == true){HgGduWnxhx = false;}
      if(mYnqepzKiF == true){mYnqepzKiF = false;}
      if(QtgzftxhbW == true){QtgzftxhbW = false;}
      if(lepByVBTTe == true){lepByVBTTe = false;}
      if(NrEPDzhPRH == true){NrEPDzhPRH = false;}
      if(LHhdlMAGxA == true){LHhdlMAGxA = false;}
      if(ZFVKLHhlsI == true){ZFVKLHhlsI = false;}
      if(ofpDqYoRwg == true){ofpDqYoRwg = false;}
      if(MgQTKexMOk == true){MgQTKexMOk = false;}
      if(UtWSFIWtDw == true){UtWSFIWtDw = false;}
      if(RuWISfQdlN == true){RuWISfQdlN = false;}
      if(XiKPnroBzg == true){XiKPnroBzg = false;}
      if(JVXHmtIWyi == true){JVXHmtIWyi = false;}
      if(CuNzPRJHBe == true){CuNzPRJHBe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FREYVENIDJ
{ 
  void RAXKCVwGQn()
  { 
      bool HiPiADiGOQ = false;
      bool QlpRQEVLDF = false;
      bool RuWGMfsbKV = false;
      bool YrRlUwJUTi = false;
      bool soRoWObXpN = false;
      bool xrhNnMLJVU = false;
      bool KHurqXTDwT = false;
      bool uArULcchiy = false;
      bool EVlxYfJExI = false;
      bool kAzzYksYyz = false;
      bool tYaVSwANBL = false;
      bool idZWPnVySL = false;
      bool NPFniuBsuZ = false;
      bool iDijEetPdc = false;
      bool fwClYGZbij = false;
      bool PuGlkdTmmX = false;
      bool uHRbbetpSk = false;
      bool sGTpeRMSOb = false;
      bool UYKKKnxwzZ = false;
      bool LHbGhYdaKs = false;
      string fjKPeUMqod;
      string BkTaeQipMo;
      string ZsEUuJWDPA;
      string dBjDzYgJFu;
      string McBkJFaYMY;
      string nLQqYleoTV;
      string xIbnAzBQaG;
      string iZkQbwrTKo;
      string iypqMSjrdN;
      string tqojyDBMjJ;
      string EJxGoOazPc;
      string sKdemzRjbg;
      string OIlNMrjASY;
      string tfiAjYBjCx;
      string rkcBTiMKxy;
      string kRjDtwXitw;
      string dZfqhNactN;
      string yhhdodeksc;
      string fZDTmcufGn;
      string BRoGSSElSG;
      if(fjKPeUMqod == EJxGoOazPc){HiPiADiGOQ = true;}
      else if(EJxGoOazPc == fjKPeUMqod){tYaVSwANBL = true;}
      if(BkTaeQipMo == sKdemzRjbg){QlpRQEVLDF = true;}
      else if(sKdemzRjbg == BkTaeQipMo){idZWPnVySL = true;}
      if(ZsEUuJWDPA == OIlNMrjASY){RuWGMfsbKV = true;}
      else if(OIlNMrjASY == ZsEUuJWDPA){NPFniuBsuZ = true;}
      if(dBjDzYgJFu == tfiAjYBjCx){YrRlUwJUTi = true;}
      else if(tfiAjYBjCx == dBjDzYgJFu){iDijEetPdc = true;}
      if(McBkJFaYMY == rkcBTiMKxy){soRoWObXpN = true;}
      else if(rkcBTiMKxy == McBkJFaYMY){fwClYGZbij = true;}
      if(nLQqYleoTV == kRjDtwXitw){xrhNnMLJVU = true;}
      else if(kRjDtwXitw == nLQqYleoTV){PuGlkdTmmX = true;}
      if(xIbnAzBQaG == dZfqhNactN){KHurqXTDwT = true;}
      else if(dZfqhNactN == xIbnAzBQaG){uHRbbetpSk = true;}
      if(iZkQbwrTKo == yhhdodeksc){uArULcchiy = true;}
      if(iypqMSjrdN == fZDTmcufGn){EVlxYfJExI = true;}
      if(tqojyDBMjJ == BRoGSSElSG){kAzzYksYyz = true;}
      while(yhhdodeksc == iZkQbwrTKo){sGTpeRMSOb = true;}
      while(fZDTmcufGn == fZDTmcufGn){UYKKKnxwzZ = true;}
      while(BRoGSSElSG == BRoGSSElSG){LHbGhYdaKs = true;}
      if(HiPiADiGOQ == true){HiPiADiGOQ = false;}
      if(QlpRQEVLDF == true){QlpRQEVLDF = false;}
      if(RuWGMfsbKV == true){RuWGMfsbKV = false;}
      if(YrRlUwJUTi == true){YrRlUwJUTi = false;}
      if(soRoWObXpN == true){soRoWObXpN = false;}
      if(xrhNnMLJVU == true){xrhNnMLJVU = false;}
      if(KHurqXTDwT == true){KHurqXTDwT = false;}
      if(uArULcchiy == true){uArULcchiy = false;}
      if(EVlxYfJExI == true){EVlxYfJExI = false;}
      if(kAzzYksYyz == true){kAzzYksYyz = false;}
      if(tYaVSwANBL == true){tYaVSwANBL = false;}
      if(idZWPnVySL == true){idZWPnVySL = false;}
      if(NPFniuBsuZ == true){NPFniuBsuZ = false;}
      if(iDijEetPdc == true){iDijEetPdc = false;}
      if(fwClYGZbij == true){fwClYGZbij = false;}
      if(PuGlkdTmmX == true){PuGlkdTmmX = false;}
      if(uHRbbetpSk == true){uHRbbetpSk = false;}
      if(sGTpeRMSOb == true){sGTpeRMSOb = false;}
      if(UYKKKnxwzZ == true){UYKKKnxwzZ = false;}
      if(LHbGhYdaKs == true){LHbGhYdaKs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LFABLWTNCL
{ 
  void mCWUSfReTt()
  { 
      bool cErmtEebQy = false;
      bool eBenkGbSfm = false;
      bool qAoeNLAQKX = false;
      bool VJZzGtKoXT = false;
      bool gHJgGhiRJz = false;
      bool qnplecPMYh = false;
      bool DNRrbVbfgp = false;
      bool umuMFipIYe = false;
      bool biHLghTnTd = false;
      bool eyPoPSpREk = false;
      bool GDkSDDscfw = false;
      bool lGmtGUGFKt = false;
      bool BmLCLxWFwl = false;
      bool sXEnYYxnIc = false;
      bool opHXqYKViu = false;
      bool MkHJiSqhHF = false;
      bool gmgtCNCzVg = false;
      bool WSxgFLfnLm = false;
      bool mAVBZIQtFF = false;
      bool gPgCwBJNUc = false;
      string wBPdZFazDE;
      string VEFgaGgAiB;
      string oolkCfdAWn;
      string wkiIJafyPl;
      string VHnfgnVsLi;
      string DDUThGOebt;
      string aZcPHkVxXz;
      string ZhjxfgBGDO;
      string JkomjrPOZD;
      string MBVVKweXXw;
      string RYVLIUTXnB;
      string EIbNjpkoeP;
      string UGXTmYLOli;
      string BchGwkPddO;
      string XraXyDZIlU;
      string LosHbKABXj;
      string JFkEzbaUQy;
      string ZGKQqcfzVj;
      string zCcRXMjZek;
      string jOFtFSGVYW;
      if(wBPdZFazDE == RYVLIUTXnB){cErmtEebQy = true;}
      else if(RYVLIUTXnB == wBPdZFazDE){GDkSDDscfw = true;}
      if(VEFgaGgAiB == EIbNjpkoeP){eBenkGbSfm = true;}
      else if(EIbNjpkoeP == VEFgaGgAiB){lGmtGUGFKt = true;}
      if(oolkCfdAWn == UGXTmYLOli){qAoeNLAQKX = true;}
      else if(UGXTmYLOli == oolkCfdAWn){BmLCLxWFwl = true;}
      if(wkiIJafyPl == BchGwkPddO){VJZzGtKoXT = true;}
      else if(BchGwkPddO == wkiIJafyPl){sXEnYYxnIc = true;}
      if(VHnfgnVsLi == XraXyDZIlU){gHJgGhiRJz = true;}
      else if(XraXyDZIlU == VHnfgnVsLi){opHXqYKViu = true;}
      if(DDUThGOebt == LosHbKABXj){qnplecPMYh = true;}
      else if(LosHbKABXj == DDUThGOebt){MkHJiSqhHF = true;}
      if(aZcPHkVxXz == JFkEzbaUQy){DNRrbVbfgp = true;}
      else if(JFkEzbaUQy == aZcPHkVxXz){gmgtCNCzVg = true;}
      if(ZhjxfgBGDO == ZGKQqcfzVj){umuMFipIYe = true;}
      if(JkomjrPOZD == zCcRXMjZek){biHLghTnTd = true;}
      if(MBVVKweXXw == jOFtFSGVYW){eyPoPSpREk = true;}
      while(ZGKQqcfzVj == ZhjxfgBGDO){WSxgFLfnLm = true;}
      while(zCcRXMjZek == zCcRXMjZek){mAVBZIQtFF = true;}
      while(jOFtFSGVYW == jOFtFSGVYW){gPgCwBJNUc = true;}
      if(cErmtEebQy == true){cErmtEebQy = false;}
      if(eBenkGbSfm == true){eBenkGbSfm = false;}
      if(qAoeNLAQKX == true){qAoeNLAQKX = false;}
      if(VJZzGtKoXT == true){VJZzGtKoXT = false;}
      if(gHJgGhiRJz == true){gHJgGhiRJz = false;}
      if(qnplecPMYh == true){qnplecPMYh = false;}
      if(DNRrbVbfgp == true){DNRrbVbfgp = false;}
      if(umuMFipIYe == true){umuMFipIYe = false;}
      if(biHLghTnTd == true){biHLghTnTd = false;}
      if(eyPoPSpREk == true){eyPoPSpREk = false;}
      if(GDkSDDscfw == true){GDkSDDscfw = false;}
      if(lGmtGUGFKt == true){lGmtGUGFKt = false;}
      if(BmLCLxWFwl == true){BmLCLxWFwl = false;}
      if(sXEnYYxnIc == true){sXEnYYxnIc = false;}
      if(opHXqYKViu == true){opHXqYKViu = false;}
      if(MkHJiSqhHF == true){MkHJiSqhHF = false;}
      if(gmgtCNCzVg == true){gmgtCNCzVg = false;}
      if(WSxgFLfnLm == true){WSxgFLfnLm = false;}
      if(mAVBZIQtFF == true){mAVBZIQtFF = false;}
      if(gPgCwBJNUc == true){gPgCwBJNUc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXPZKFGLCH
{ 
  void fuzExbdZXl()
  { 
      bool dNgcwtpHCO = false;
      bool JYCtEnpBBP = false;
      bool UdMyCAYQMd = false;
      bool rKnKJzchQn = false;
      bool MCfkGrscul = false;
      bool uIiSrzBhZu = false;
      bool UYuYVykrjE = false;
      bool KIjNCSxbqK = false;
      bool GuVZhjaUSJ = false;
      bool ytHVSnGHOH = false;
      bool GBsqbmXVPZ = false;
      bool BZqPnZDVpk = false;
      bool XPZaFQBNtO = false;
      bool LoMiDFCdxu = false;
      bool MEFrHYDqhs = false;
      bool jjRdiqbSkK = false;
      bool lKbBNLMHLh = false;
      bool XYXuYTKgSg = false;
      bool NJfBdaXizM = false;
      bool djrmJCcDeu = false;
      string zXCaJpcjzw;
      string BoJUVkncXV;
      string CDpQByDLaN;
      string uixIZlqDpB;
      string HAqVILSmuB;
      string mxqVewhlYL;
      string lRJlARqAui;
      string tjmVOBLUHo;
      string eQQZayrbdd;
      string EFedPpqFUp;
      string URrLHCKUHc;
      string kNdigVAiKC;
      string ZPWQdoFIGX;
      string KFAQUMXERX;
      string mXUAsqauxs;
      string pHuRQEuagR;
      string xBNiSeMMOT;
      string xwRmPCuVXm;
      string NJLMhCKiAP;
      string QwWAalJkhN;
      if(zXCaJpcjzw == URrLHCKUHc){dNgcwtpHCO = true;}
      else if(URrLHCKUHc == zXCaJpcjzw){GBsqbmXVPZ = true;}
      if(BoJUVkncXV == kNdigVAiKC){JYCtEnpBBP = true;}
      else if(kNdigVAiKC == BoJUVkncXV){BZqPnZDVpk = true;}
      if(CDpQByDLaN == ZPWQdoFIGX){UdMyCAYQMd = true;}
      else if(ZPWQdoFIGX == CDpQByDLaN){XPZaFQBNtO = true;}
      if(uixIZlqDpB == KFAQUMXERX){rKnKJzchQn = true;}
      else if(KFAQUMXERX == uixIZlqDpB){LoMiDFCdxu = true;}
      if(HAqVILSmuB == mXUAsqauxs){MCfkGrscul = true;}
      else if(mXUAsqauxs == HAqVILSmuB){MEFrHYDqhs = true;}
      if(mxqVewhlYL == pHuRQEuagR){uIiSrzBhZu = true;}
      else if(pHuRQEuagR == mxqVewhlYL){jjRdiqbSkK = true;}
      if(lRJlARqAui == xBNiSeMMOT){UYuYVykrjE = true;}
      else if(xBNiSeMMOT == lRJlARqAui){lKbBNLMHLh = true;}
      if(tjmVOBLUHo == xwRmPCuVXm){KIjNCSxbqK = true;}
      if(eQQZayrbdd == NJLMhCKiAP){GuVZhjaUSJ = true;}
      if(EFedPpqFUp == QwWAalJkhN){ytHVSnGHOH = true;}
      while(xwRmPCuVXm == tjmVOBLUHo){XYXuYTKgSg = true;}
      while(NJLMhCKiAP == NJLMhCKiAP){NJfBdaXizM = true;}
      while(QwWAalJkhN == QwWAalJkhN){djrmJCcDeu = true;}
      if(dNgcwtpHCO == true){dNgcwtpHCO = false;}
      if(JYCtEnpBBP == true){JYCtEnpBBP = false;}
      if(UdMyCAYQMd == true){UdMyCAYQMd = false;}
      if(rKnKJzchQn == true){rKnKJzchQn = false;}
      if(MCfkGrscul == true){MCfkGrscul = false;}
      if(uIiSrzBhZu == true){uIiSrzBhZu = false;}
      if(UYuYVykrjE == true){UYuYVykrjE = false;}
      if(KIjNCSxbqK == true){KIjNCSxbqK = false;}
      if(GuVZhjaUSJ == true){GuVZhjaUSJ = false;}
      if(ytHVSnGHOH == true){ytHVSnGHOH = false;}
      if(GBsqbmXVPZ == true){GBsqbmXVPZ = false;}
      if(BZqPnZDVpk == true){BZqPnZDVpk = false;}
      if(XPZaFQBNtO == true){XPZaFQBNtO = false;}
      if(LoMiDFCdxu == true){LoMiDFCdxu = false;}
      if(MEFrHYDqhs == true){MEFrHYDqhs = false;}
      if(jjRdiqbSkK == true){jjRdiqbSkK = false;}
      if(lKbBNLMHLh == true){lKbBNLMHLh = false;}
      if(XYXuYTKgSg == true){XYXuYTKgSg = false;}
      if(NJfBdaXizM == true){NJfBdaXizM = false;}
      if(djrmJCcDeu == true){djrmJCcDeu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JTINYDFYEK
{ 
  void mCCxGchrMH()
  { 
      bool LCtkbHqeab = false;
      bool LNTkuTqwrY = false;
      bool IWGXjIcehw = false;
      bool aNQuKVOliD = false;
      bool ACUwgenGfa = false;
      bool gSyfCouWAS = false;
      bool eMwdBywYaY = false;
      bool FFMoYGCJpF = false;
      bool UVzGOHOjsU = false;
      bool ZrkQYnFpui = false;
      bool iOfGVbGJHu = false;
      bool mlfuxIMpPt = false;
      bool iLeFyNTuQk = false;
      bool BLOHVFpskl = false;
      bool AFcxhnLpSP = false;
      bool aPaBzWjZHI = false;
      bool HKsWsaWYYq = false;
      bool STEcsdihXK = false;
      bool BdcAJlkNHz = false;
      bool VPkcepMGDG = false;
      string PAnhDFimAr;
      string hDtzeKukHP;
      string VkuuetnELa;
      string unQaLqyndK;
      string cdjAXDrVun;
      string DHHdzeEsCI;
      string RdaYwslSnm;
      string LGHwmrAuWb;
      string CRIXWnglbf;
      string mFlUsyCKEe;
      string QZhIbxAKqG;
      string eIWaGAVDCI;
      string MApHAGTlDn;
      string poqqKbiAwY;
      string mVtUBdhKOr;
      string cyIuSQiaHU;
      string cOGDQpReQd;
      string QUGdUpFVGW;
      string YJWKKqguYs;
      string sIrbuYPqEK;
      if(PAnhDFimAr == QZhIbxAKqG){LCtkbHqeab = true;}
      else if(QZhIbxAKqG == PAnhDFimAr){iOfGVbGJHu = true;}
      if(hDtzeKukHP == eIWaGAVDCI){LNTkuTqwrY = true;}
      else if(eIWaGAVDCI == hDtzeKukHP){mlfuxIMpPt = true;}
      if(VkuuetnELa == MApHAGTlDn){IWGXjIcehw = true;}
      else if(MApHAGTlDn == VkuuetnELa){iLeFyNTuQk = true;}
      if(unQaLqyndK == poqqKbiAwY){aNQuKVOliD = true;}
      else if(poqqKbiAwY == unQaLqyndK){BLOHVFpskl = true;}
      if(cdjAXDrVun == mVtUBdhKOr){ACUwgenGfa = true;}
      else if(mVtUBdhKOr == cdjAXDrVun){AFcxhnLpSP = true;}
      if(DHHdzeEsCI == cyIuSQiaHU){gSyfCouWAS = true;}
      else if(cyIuSQiaHU == DHHdzeEsCI){aPaBzWjZHI = true;}
      if(RdaYwslSnm == cOGDQpReQd){eMwdBywYaY = true;}
      else if(cOGDQpReQd == RdaYwslSnm){HKsWsaWYYq = true;}
      if(LGHwmrAuWb == QUGdUpFVGW){FFMoYGCJpF = true;}
      if(CRIXWnglbf == YJWKKqguYs){UVzGOHOjsU = true;}
      if(mFlUsyCKEe == sIrbuYPqEK){ZrkQYnFpui = true;}
      while(QUGdUpFVGW == LGHwmrAuWb){STEcsdihXK = true;}
      while(YJWKKqguYs == YJWKKqguYs){BdcAJlkNHz = true;}
      while(sIrbuYPqEK == sIrbuYPqEK){VPkcepMGDG = true;}
      if(LCtkbHqeab == true){LCtkbHqeab = false;}
      if(LNTkuTqwrY == true){LNTkuTqwrY = false;}
      if(IWGXjIcehw == true){IWGXjIcehw = false;}
      if(aNQuKVOliD == true){aNQuKVOliD = false;}
      if(ACUwgenGfa == true){ACUwgenGfa = false;}
      if(gSyfCouWAS == true){gSyfCouWAS = false;}
      if(eMwdBywYaY == true){eMwdBywYaY = false;}
      if(FFMoYGCJpF == true){FFMoYGCJpF = false;}
      if(UVzGOHOjsU == true){UVzGOHOjsU = false;}
      if(ZrkQYnFpui == true){ZrkQYnFpui = false;}
      if(iOfGVbGJHu == true){iOfGVbGJHu = false;}
      if(mlfuxIMpPt == true){mlfuxIMpPt = false;}
      if(iLeFyNTuQk == true){iLeFyNTuQk = false;}
      if(BLOHVFpskl == true){BLOHVFpskl = false;}
      if(AFcxhnLpSP == true){AFcxhnLpSP = false;}
      if(aPaBzWjZHI == true){aPaBzWjZHI = false;}
      if(HKsWsaWYYq == true){HKsWsaWYYq = false;}
      if(STEcsdihXK == true){STEcsdihXK = false;}
      if(BdcAJlkNHz == true){BdcAJlkNHz = false;}
      if(VPkcepMGDG == true){VPkcepMGDG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PAIRUOZDGO
{ 
  void hyNOgdhoZR()
  { 
      bool QAMWTliVfP = false;
      bool JaponAxwmd = false;
      bool wwFBOkdNMB = false;
      bool LalgwXBfMz = false;
      bool aIQtNgLDKe = false;
      bool jJMkEUtLHi = false;
      bool IVIeEinJsP = false;
      bool yRjmCmfKmh = false;
      bool ZZDhQBNAbb = false;
      bool cpXcqFAkpe = false;
      bool rBKtfSZYhR = false;
      bool niYYJiSaOC = false;
      bool UngRmIsGwx = false;
      bool luUHpXPIBy = false;
      bool bnRKmtRzTH = false;
      bool mYWmJDUrHX = false;
      bool YTckerOQhk = false;
      bool SJYPafVWdr = false;
      bool ptlnKNYgxl = false;
      bool DXBcZHLgeu = false;
      string DQxpUVgJnL;
      string biMOFaGQDy;
      string VpSLTyynbr;
      string SapLJPLoVs;
      string WzwZjchnQP;
      string hoawPMykWW;
      string XrhwsBsAFo;
      string ORtJaWsrbq;
      string QJXLJcAtww;
      string QZRzVeRAfi;
      string igiaBPuQUs;
      string TFJfGNUWlQ;
      string AzEJXoAunw;
      string EsMsHiawKt;
      string giYDbKQksH;
      string JuNPhjbYCL;
      string OzcYnasQYW;
      string mXLriRZBhM;
      string XOCglJewKX;
      string HCsyehFzPA;
      if(DQxpUVgJnL == igiaBPuQUs){QAMWTliVfP = true;}
      else if(igiaBPuQUs == DQxpUVgJnL){rBKtfSZYhR = true;}
      if(biMOFaGQDy == TFJfGNUWlQ){JaponAxwmd = true;}
      else if(TFJfGNUWlQ == biMOFaGQDy){niYYJiSaOC = true;}
      if(VpSLTyynbr == AzEJXoAunw){wwFBOkdNMB = true;}
      else if(AzEJXoAunw == VpSLTyynbr){UngRmIsGwx = true;}
      if(SapLJPLoVs == EsMsHiawKt){LalgwXBfMz = true;}
      else if(EsMsHiawKt == SapLJPLoVs){luUHpXPIBy = true;}
      if(WzwZjchnQP == giYDbKQksH){aIQtNgLDKe = true;}
      else if(giYDbKQksH == WzwZjchnQP){bnRKmtRzTH = true;}
      if(hoawPMykWW == JuNPhjbYCL){jJMkEUtLHi = true;}
      else if(JuNPhjbYCL == hoawPMykWW){mYWmJDUrHX = true;}
      if(XrhwsBsAFo == OzcYnasQYW){IVIeEinJsP = true;}
      else if(OzcYnasQYW == XrhwsBsAFo){YTckerOQhk = true;}
      if(ORtJaWsrbq == mXLriRZBhM){yRjmCmfKmh = true;}
      if(QJXLJcAtww == XOCglJewKX){ZZDhQBNAbb = true;}
      if(QZRzVeRAfi == HCsyehFzPA){cpXcqFAkpe = true;}
      while(mXLriRZBhM == ORtJaWsrbq){SJYPafVWdr = true;}
      while(XOCglJewKX == XOCglJewKX){ptlnKNYgxl = true;}
      while(HCsyehFzPA == HCsyehFzPA){DXBcZHLgeu = true;}
      if(QAMWTliVfP == true){QAMWTliVfP = false;}
      if(JaponAxwmd == true){JaponAxwmd = false;}
      if(wwFBOkdNMB == true){wwFBOkdNMB = false;}
      if(LalgwXBfMz == true){LalgwXBfMz = false;}
      if(aIQtNgLDKe == true){aIQtNgLDKe = false;}
      if(jJMkEUtLHi == true){jJMkEUtLHi = false;}
      if(IVIeEinJsP == true){IVIeEinJsP = false;}
      if(yRjmCmfKmh == true){yRjmCmfKmh = false;}
      if(ZZDhQBNAbb == true){ZZDhQBNAbb = false;}
      if(cpXcqFAkpe == true){cpXcqFAkpe = false;}
      if(rBKtfSZYhR == true){rBKtfSZYhR = false;}
      if(niYYJiSaOC == true){niYYJiSaOC = false;}
      if(UngRmIsGwx == true){UngRmIsGwx = false;}
      if(luUHpXPIBy == true){luUHpXPIBy = false;}
      if(bnRKmtRzTH == true){bnRKmtRzTH = false;}
      if(mYWmJDUrHX == true){mYWmJDUrHX = false;}
      if(YTckerOQhk == true){YTckerOQhk = false;}
      if(SJYPafVWdr == true){SJYPafVWdr = false;}
      if(ptlnKNYgxl == true){ptlnKNYgxl = false;}
      if(DXBcZHLgeu == true){DXBcZHLgeu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OYIDTTWIPH
{ 
  void tqbsrgWBPN()
  { 
      bool NUdqnOxZfy = false;
      bool JVwnEuVEjV = false;
      bool CAnSdVGjLt = false;
      bool QBVEzwcwMP = false;
      bool taqrchnpIL = false;
      bool SBdgPNgKMS = false;
      bool HMNlhHzqoH = false;
      bool RZqTaaJuow = false;
      bool gQbAaOXnok = false;
      bool PSjsHgNFKV = false;
      bool hwBAssJJGn = false;
      bool DkUQlqkNKS = false;
      bool jKCDrzpxMs = false;
      bool MEkTNjPaGg = false;
      bool FNhAgdxTHP = false;
      bool wztrkWtxHt = false;
      bool DMxMazAACB = false;
      bool bJHcNVcCVO = false;
      bool BWpwxNJrhp = false;
      bool pRTMdrQUYh = false;
      string uaVDjzYYdH;
      string MPcylKshYC;
      string nbhNHVecVt;
      string FQDYmpzzRX;
      string KcIyycnTwy;
      string olCjJSsHwN;
      string UuCjBuLEKw;
      string KtQArLTiPd;
      string hLfWFTNTOT;
      string wrCEDOZXwC;
      string RjIAntVCqy;
      string zKrSfIPfdh;
      string hroqzRqLwc;
      string kulMMyCeiK;
      string yLbPUlAjYu;
      string ztsOUYtRBV;
      string DJFOMDXeGh;
      string GjxTiWPYVN;
      string RHmBdqBWqm;
      string DjdMHoFNDR;
      if(uaVDjzYYdH == RjIAntVCqy){NUdqnOxZfy = true;}
      else if(RjIAntVCqy == uaVDjzYYdH){hwBAssJJGn = true;}
      if(MPcylKshYC == zKrSfIPfdh){JVwnEuVEjV = true;}
      else if(zKrSfIPfdh == MPcylKshYC){DkUQlqkNKS = true;}
      if(nbhNHVecVt == hroqzRqLwc){CAnSdVGjLt = true;}
      else if(hroqzRqLwc == nbhNHVecVt){jKCDrzpxMs = true;}
      if(FQDYmpzzRX == kulMMyCeiK){QBVEzwcwMP = true;}
      else if(kulMMyCeiK == FQDYmpzzRX){MEkTNjPaGg = true;}
      if(KcIyycnTwy == yLbPUlAjYu){taqrchnpIL = true;}
      else if(yLbPUlAjYu == KcIyycnTwy){FNhAgdxTHP = true;}
      if(olCjJSsHwN == ztsOUYtRBV){SBdgPNgKMS = true;}
      else if(ztsOUYtRBV == olCjJSsHwN){wztrkWtxHt = true;}
      if(UuCjBuLEKw == DJFOMDXeGh){HMNlhHzqoH = true;}
      else if(DJFOMDXeGh == UuCjBuLEKw){DMxMazAACB = true;}
      if(KtQArLTiPd == GjxTiWPYVN){RZqTaaJuow = true;}
      if(hLfWFTNTOT == RHmBdqBWqm){gQbAaOXnok = true;}
      if(wrCEDOZXwC == DjdMHoFNDR){PSjsHgNFKV = true;}
      while(GjxTiWPYVN == KtQArLTiPd){bJHcNVcCVO = true;}
      while(RHmBdqBWqm == RHmBdqBWqm){BWpwxNJrhp = true;}
      while(DjdMHoFNDR == DjdMHoFNDR){pRTMdrQUYh = true;}
      if(NUdqnOxZfy == true){NUdqnOxZfy = false;}
      if(JVwnEuVEjV == true){JVwnEuVEjV = false;}
      if(CAnSdVGjLt == true){CAnSdVGjLt = false;}
      if(QBVEzwcwMP == true){QBVEzwcwMP = false;}
      if(taqrchnpIL == true){taqrchnpIL = false;}
      if(SBdgPNgKMS == true){SBdgPNgKMS = false;}
      if(HMNlhHzqoH == true){HMNlhHzqoH = false;}
      if(RZqTaaJuow == true){RZqTaaJuow = false;}
      if(gQbAaOXnok == true){gQbAaOXnok = false;}
      if(PSjsHgNFKV == true){PSjsHgNFKV = false;}
      if(hwBAssJJGn == true){hwBAssJJGn = false;}
      if(DkUQlqkNKS == true){DkUQlqkNKS = false;}
      if(jKCDrzpxMs == true){jKCDrzpxMs = false;}
      if(MEkTNjPaGg == true){MEkTNjPaGg = false;}
      if(FNhAgdxTHP == true){FNhAgdxTHP = false;}
      if(wztrkWtxHt == true){wztrkWtxHt = false;}
      if(DMxMazAACB == true){DMxMazAACB = false;}
      if(bJHcNVcCVO == true){bJHcNVcCVO = false;}
      if(BWpwxNJrhp == true){BWpwxNJrhp = false;}
      if(pRTMdrQUYh == true){pRTMdrQUYh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YBIULFSQOP
{ 
  void WMVwAuMsDF()
  { 
      bool MShckuQpOw = false;
      bool EyyiIrNxBu = false;
      bool dBijzTDMRM = false;
      bool bQRbpNPbDT = false;
      bool RXRUOaYgTK = false;
      bool NBZJwKjydQ = false;
      bool qDYBUmgVru = false;
      bool cksgcGjNUX = false;
      bool uWrGzZqHff = false;
      bool cRymcNyPAa = false;
      bool sCoYhcHsfp = false;
      bool ZWdFUUKSCt = false;
      bool wYpLRKmGDP = false;
      bool HTMsdrhTXV = false;
      bool RxbpFGnrRI = false;
      bool CeNFeTMcHW = false;
      bool pBoQhGJjac = false;
      bool lqufbzxAGL = false;
      bool WtnuMbGGOK = false;
      bool eFLAfQILHz = false;
      string fGbOeRigSh;
      string FVfFHhFhFF;
      string tNRNAtMcMh;
      string aCybCzXSFw;
      string plLtmEbVqB;
      string MEMKaSnOOk;
      string FGUkGDXEDI;
      string JmcIOHBWZw;
      string RpkKUWpmAi;
      string KIDUqjRanj;
      string fXSiqZaDuS;
      string RQoSSOUJPj;
      string MjDTxAiHRe;
      string pZioPtWBTt;
      string ulrhRtTkCc;
      string OHLDXwUzlp;
      string qTlQcrgACY;
      string qTpUoarVBD;
      string gyFoPhNfRS;
      string ZWPcDbzaEZ;
      if(fGbOeRigSh == fXSiqZaDuS){MShckuQpOw = true;}
      else if(fXSiqZaDuS == fGbOeRigSh){sCoYhcHsfp = true;}
      if(FVfFHhFhFF == RQoSSOUJPj){EyyiIrNxBu = true;}
      else if(RQoSSOUJPj == FVfFHhFhFF){ZWdFUUKSCt = true;}
      if(tNRNAtMcMh == MjDTxAiHRe){dBijzTDMRM = true;}
      else if(MjDTxAiHRe == tNRNAtMcMh){wYpLRKmGDP = true;}
      if(aCybCzXSFw == pZioPtWBTt){bQRbpNPbDT = true;}
      else if(pZioPtWBTt == aCybCzXSFw){HTMsdrhTXV = true;}
      if(plLtmEbVqB == ulrhRtTkCc){RXRUOaYgTK = true;}
      else if(ulrhRtTkCc == plLtmEbVqB){RxbpFGnrRI = true;}
      if(MEMKaSnOOk == OHLDXwUzlp){NBZJwKjydQ = true;}
      else if(OHLDXwUzlp == MEMKaSnOOk){CeNFeTMcHW = true;}
      if(FGUkGDXEDI == qTlQcrgACY){qDYBUmgVru = true;}
      else if(qTlQcrgACY == FGUkGDXEDI){pBoQhGJjac = true;}
      if(JmcIOHBWZw == qTpUoarVBD){cksgcGjNUX = true;}
      if(RpkKUWpmAi == gyFoPhNfRS){uWrGzZqHff = true;}
      if(KIDUqjRanj == ZWPcDbzaEZ){cRymcNyPAa = true;}
      while(qTpUoarVBD == JmcIOHBWZw){lqufbzxAGL = true;}
      while(gyFoPhNfRS == gyFoPhNfRS){WtnuMbGGOK = true;}
      while(ZWPcDbzaEZ == ZWPcDbzaEZ){eFLAfQILHz = true;}
      if(MShckuQpOw == true){MShckuQpOw = false;}
      if(EyyiIrNxBu == true){EyyiIrNxBu = false;}
      if(dBijzTDMRM == true){dBijzTDMRM = false;}
      if(bQRbpNPbDT == true){bQRbpNPbDT = false;}
      if(RXRUOaYgTK == true){RXRUOaYgTK = false;}
      if(NBZJwKjydQ == true){NBZJwKjydQ = false;}
      if(qDYBUmgVru == true){qDYBUmgVru = false;}
      if(cksgcGjNUX == true){cksgcGjNUX = false;}
      if(uWrGzZqHff == true){uWrGzZqHff = false;}
      if(cRymcNyPAa == true){cRymcNyPAa = false;}
      if(sCoYhcHsfp == true){sCoYhcHsfp = false;}
      if(ZWdFUUKSCt == true){ZWdFUUKSCt = false;}
      if(wYpLRKmGDP == true){wYpLRKmGDP = false;}
      if(HTMsdrhTXV == true){HTMsdrhTXV = false;}
      if(RxbpFGnrRI == true){RxbpFGnrRI = false;}
      if(CeNFeTMcHW == true){CeNFeTMcHW = false;}
      if(pBoQhGJjac == true){pBoQhGJjac = false;}
      if(lqufbzxAGL == true){lqufbzxAGL = false;}
      if(WtnuMbGGOK == true){WtnuMbGGOK = false;}
      if(eFLAfQILHz == true){eFLAfQILHz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XGUKGAEIYN
{ 
  void ncBxZDFwjN()
  { 
      bool kRlXOuKqex = false;
      bool tfNbGDWPQJ = false;
      bool mpSbnMnwqx = false;
      bool MmtVwiOyxT = false;
      bool ZKEtpcZulE = false;
      bool BkNLcuzJiC = false;
      bool GOzgkGlreW = false;
      bool oXRwjckXlL = false;
      bool lrKmuaYhsB = false;
      bool jEOuMKKWJi = false;
      bool qhQOPdTRbA = false;
      bool JaWXPNDMlJ = false;
      bool hEzdmkIWjY = false;
      bool ROODUEbwXR = false;
      bool HHGsrIgqey = false;
      bool HxkzBlimae = false;
      bool UwgChtMTCK = false;
      bool lHoTCZyFkd = false;
      bool ERqkRTcPCh = false;
      bool VoUsxKZEKx = false;
      string LcuxZOTSEj;
      string jVfzKcCXtw;
      string qexcHnytqa;
      string xNiCUzIwJQ;
      string ZQgZXYGVMF;
      string KxgXFffSok;
      string PZaclWlceK;
      string TGOcVaxWEh;
      string hchlQzgLwn;
      string SpGXBzoEmB;
      string mcpBkEiDBe;
      string iINHClroMm;
      string pagqrdzpaV;
      string ksjDuFmgAM;
      string QcJQFKbyUO;
      string HAqAKLwzJH;
      string ErbetoYKMx;
      string zLozVMRPlg;
      string BAVMOjBirj;
      string ImWrIYAdVP;
      if(LcuxZOTSEj == mcpBkEiDBe){kRlXOuKqex = true;}
      else if(mcpBkEiDBe == LcuxZOTSEj){qhQOPdTRbA = true;}
      if(jVfzKcCXtw == iINHClroMm){tfNbGDWPQJ = true;}
      else if(iINHClroMm == jVfzKcCXtw){JaWXPNDMlJ = true;}
      if(qexcHnytqa == pagqrdzpaV){mpSbnMnwqx = true;}
      else if(pagqrdzpaV == qexcHnytqa){hEzdmkIWjY = true;}
      if(xNiCUzIwJQ == ksjDuFmgAM){MmtVwiOyxT = true;}
      else if(ksjDuFmgAM == xNiCUzIwJQ){ROODUEbwXR = true;}
      if(ZQgZXYGVMF == QcJQFKbyUO){ZKEtpcZulE = true;}
      else if(QcJQFKbyUO == ZQgZXYGVMF){HHGsrIgqey = true;}
      if(KxgXFffSok == HAqAKLwzJH){BkNLcuzJiC = true;}
      else if(HAqAKLwzJH == KxgXFffSok){HxkzBlimae = true;}
      if(PZaclWlceK == ErbetoYKMx){GOzgkGlreW = true;}
      else if(ErbetoYKMx == PZaclWlceK){UwgChtMTCK = true;}
      if(TGOcVaxWEh == zLozVMRPlg){oXRwjckXlL = true;}
      if(hchlQzgLwn == BAVMOjBirj){lrKmuaYhsB = true;}
      if(SpGXBzoEmB == ImWrIYAdVP){jEOuMKKWJi = true;}
      while(zLozVMRPlg == TGOcVaxWEh){lHoTCZyFkd = true;}
      while(BAVMOjBirj == BAVMOjBirj){ERqkRTcPCh = true;}
      while(ImWrIYAdVP == ImWrIYAdVP){VoUsxKZEKx = true;}
      if(kRlXOuKqex == true){kRlXOuKqex = false;}
      if(tfNbGDWPQJ == true){tfNbGDWPQJ = false;}
      if(mpSbnMnwqx == true){mpSbnMnwqx = false;}
      if(MmtVwiOyxT == true){MmtVwiOyxT = false;}
      if(ZKEtpcZulE == true){ZKEtpcZulE = false;}
      if(BkNLcuzJiC == true){BkNLcuzJiC = false;}
      if(GOzgkGlreW == true){GOzgkGlreW = false;}
      if(oXRwjckXlL == true){oXRwjckXlL = false;}
      if(lrKmuaYhsB == true){lrKmuaYhsB = false;}
      if(jEOuMKKWJi == true){jEOuMKKWJi = false;}
      if(qhQOPdTRbA == true){qhQOPdTRbA = false;}
      if(JaWXPNDMlJ == true){JaWXPNDMlJ = false;}
      if(hEzdmkIWjY == true){hEzdmkIWjY = false;}
      if(ROODUEbwXR == true){ROODUEbwXR = false;}
      if(HHGsrIgqey == true){HHGsrIgqey = false;}
      if(HxkzBlimae == true){HxkzBlimae = false;}
      if(UwgChtMTCK == true){UwgChtMTCK = false;}
      if(lHoTCZyFkd == true){lHoTCZyFkd = false;}
      if(ERqkRTcPCh == true){ERqkRTcPCh = false;}
      if(VoUsxKZEKx == true){VoUsxKZEKx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WHPPDNXRPC
{ 
  void lbRWRyhPdy()
  { 
      bool eCrpWbalRx = false;
      bool MyRYXIKOyJ = false;
      bool qSWEDCaspj = false;
      bool hkkyzkLKsN = false;
      bool sVdHSKtCjn = false;
      bool ZnGOgMfnmU = false;
      bool AhwhObMTZl = false;
      bool wAUjPVoOlr = false;
      bool HYJBJtdVQm = false;
      bool FXXXNLZurq = false;
      bool yabxrZSVzL = false;
      bool XQBtMbYtXU = false;
      bool xqCmgXbxVE = false;
      bool wsVttgwLJj = false;
      bool bHWFOnVdKl = false;
      bool meWXtGXoPT = false;
      bool xUAtPduGze = false;
      bool eMknroTwXs = false;
      bool ByljQQVyAn = false;
      bool JGwpmGHbpk = false;
      string IHTUZKnQbC;
      string XYrjmIFtti;
      string OZYRkEOxsa;
      string VrpzlYudFt;
      string CTXldTPgps;
      string VGfoUhiCiU;
      string wpWBgeiryN;
      string MaozgtCmmR;
      string ohHAEOMAdD;
      string pstjyMxVEz;
      string jWhbftRfIa;
      string fwORfNhVxR;
      string RhNtXSgFBT;
      string wghmgSzeUJ;
      string xgrDXsecDk;
      string dbYlhCInDM;
      string MMendzObjN;
      string NCAmUjoKWe;
      string nEBQoUHuFe;
      string JLbHwkCEYY;
      if(IHTUZKnQbC == jWhbftRfIa){eCrpWbalRx = true;}
      else if(jWhbftRfIa == IHTUZKnQbC){yabxrZSVzL = true;}
      if(XYrjmIFtti == fwORfNhVxR){MyRYXIKOyJ = true;}
      else if(fwORfNhVxR == XYrjmIFtti){XQBtMbYtXU = true;}
      if(OZYRkEOxsa == RhNtXSgFBT){qSWEDCaspj = true;}
      else if(RhNtXSgFBT == OZYRkEOxsa){xqCmgXbxVE = true;}
      if(VrpzlYudFt == wghmgSzeUJ){hkkyzkLKsN = true;}
      else if(wghmgSzeUJ == VrpzlYudFt){wsVttgwLJj = true;}
      if(CTXldTPgps == xgrDXsecDk){sVdHSKtCjn = true;}
      else if(xgrDXsecDk == CTXldTPgps){bHWFOnVdKl = true;}
      if(VGfoUhiCiU == dbYlhCInDM){ZnGOgMfnmU = true;}
      else if(dbYlhCInDM == VGfoUhiCiU){meWXtGXoPT = true;}
      if(wpWBgeiryN == MMendzObjN){AhwhObMTZl = true;}
      else if(MMendzObjN == wpWBgeiryN){xUAtPduGze = true;}
      if(MaozgtCmmR == NCAmUjoKWe){wAUjPVoOlr = true;}
      if(ohHAEOMAdD == nEBQoUHuFe){HYJBJtdVQm = true;}
      if(pstjyMxVEz == JLbHwkCEYY){FXXXNLZurq = true;}
      while(NCAmUjoKWe == MaozgtCmmR){eMknroTwXs = true;}
      while(nEBQoUHuFe == nEBQoUHuFe){ByljQQVyAn = true;}
      while(JLbHwkCEYY == JLbHwkCEYY){JGwpmGHbpk = true;}
      if(eCrpWbalRx == true){eCrpWbalRx = false;}
      if(MyRYXIKOyJ == true){MyRYXIKOyJ = false;}
      if(qSWEDCaspj == true){qSWEDCaspj = false;}
      if(hkkyzkLKsN == true){hkkyzkLKsN = false;}
      if(sVdHSKtCjn == true){sVdHSKtCjn = false;}
      if(ZnGOgMfnmU == true){ZnGOgMfnmU = false;}
      if(AhwhObMTZl == true){AhwhObMTZl = false;}
      if(wAUjPVoOlr == true){wAUjPVoOlr = false;}
      if(HYJBJtdVQm == true){HYJBJtdVQm = false;}
      if(FXXXNLZurq == true){FXXXNLZurq = false;}
      if(yabxrZSVzL == true){yabxrZSVzL = false;}
      if(XQBtMbYtXU == true){XQBtMbYtXU = false;}
      if(xqCmgXbxVE == true){xqCmgXbxVE = false;}
      if(wsVttgwLJj == true){wsVttgwLJj = false;}
      if(bHWFOnVdKl == true){bHWFOnVdKl = false;}
      if(meWXtGXoPT == true){meWXtGXoPT = false;}
      if(xUAtPduGze == true){xUAtPduGze = false;}
      if(eMknroTwXs == true){eMknroTwXs = false;}
      if(ByljQQVyAn == true){ByljQQVyAn = false;}
      if(JGwpmGHbpk == true){JGwpmGHbpk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IIJRIDNTFW
{ 
  void WlNIkOfodR()
  { 
      bool YUfDNtgpbC = false;
      bool SQDgisNxVF = false;
      bool CIZYQCzyaw = false;
      bool EuSDVicBhZ = false;
      bool NPJawdtulx = false;
      bool IMfoNQuHmK = false;
      bool tiOeyWyAKz = false;
      bool PLPwqmyycl = false;
      bool IDLdmqPdoF = false;
      bool nVOWedAdcY = false;
      bool fskmgwwixa = false;
      bool RwdBBqXkqG = false;
      bool GUKFLtxrQM = false;
      bool lUVDGPSXwq = false;
      bool uffOnqqMVn = false;
      bool GPmWSLhebm = false;
      bool zDSjnxZZul = false;
      bool XzoAKZnuRT = false;
      bool CjWcGWgzkt = false;
      bool gmwIrqNuap = false;
      string rdMHshSlOS;
      string hMLcHoGOjU;
      string EpUmExdqka;
      string hHxMtBsouo;
      string ceIlKUkuxL;
      string yGzYVCIYCw;
      string EaBnjaOzhG;
      string wQTurYgicj;
      string LhtYbbIYqr;
      string rTmzkCcTCi;
      string FlNpPgmEfw;
      string UZwSjVfcMH;
      string SoIpNbdTKp;
      string uMfsdYUEIt;
      string oDrtWSXUOO;
      string VAHtQPdWbm;
      string DSspAHsCnL;
      string BbTRSOxNSu;
      string EJFuTuFkcO;
      string uybVqVKBtP;
      if(rdMHshSlOS == FlNpPgmEfw){YUfDNtgpbC = true;}
      else if(FlNpPgmEfw == rdMHshSlOS){fskmgwwixa = true;}
      if(hMLcHoGOjU == UZwSjVfcMH){SQDgisNxVF = true;}
      else if(UZwSjVfcMH == hMLcHoGOjU){RwdBBqXkqG = true;}
      if(EpUmExdqka == SoIpNbdTKp){CIZYQCzyaw = true;}
      else if(SoIpNbdTKp == EpUmExdqka){GUKFLtxrQM = true;}
      if(hHxMtBsouo == uMfsdYUEIt){EuSDVicBhZ = true;}
      else if(uMfsdYUEIt == hHxMtBsouo){lUVDGPSXwq = true;}
      if(ceIlKUkuxL == oDrtWSXUOO){NPJawdtulx = true;}
      else if(oDrtWSXUOO == ceIlKUkuxL){uffOnqqMVn = true;}
      if(yGzYVCIYCw == VAHtQPdWbm){IMfoNQuHmK = true;}
      else if(VAHtQPdWbm == yGzYVCIYCw){GPmWSLhebm = true;}
      if(EaBnjaOzhG == DSspAHsCnL){tiOeyWyAKz = true;}
      else if(DSspAHsCnL == EaBnjaOzhG){zDSjnxZZul = true;}
      if(wQTurYgicj == BbTRSOxNSu){PLPwqmyycl = true;}
      if(LhtYbbIYqr == EJFuTuFkcO){IDLdmqPdoF = true;}
      if(rTmzkCcTCi == uybVqVKBtP){nVOWedAdcY = true;}
      while(BbTRSOxNSu == wQTurYgicj){XzoAKZnuRT = true;}
      while(EJFuTuFkcO == EJFuTuFkcO){CjWcGWgzkt = true;}
      while(uybVqVKBtP == uybVqVKBtP){gmwIrqNuap = true;}
      if(YUfDNtgpbC == true){YUfDNtgpbC = false;}
      if(SQDgisNxVF == true){SQDgisNxVF = false;}
      if(CIZYQCzyaw == true){CIZYQCzyaw = false;}
      if(EuSDVicBhZ == true){EuSDVicBhZ = false;}
      if(NPJawdtulx == true){NPJawdtulx = false;}
      if(IMfoNQuHmK == true){IMfoNQuHmK = false;}
      if(tiOeyWyAKz == true){tiOeyWyAKz = false;}
      if(PLPwqmyycl == true){PLPwqmyycl = false;}
      if(IDLdmqPdoF == true){IDLdmqPdoF = false;}
      if(nVOWedAdcY == true){nVOWedAdcY = false;}
      if(fskmgwwixa == true){fskmgwwixa = false;}
      if(RwdBBqXkqG == true){RwdBBqXkqG = false;}
      if(GUKFLtxrQM == true){GUKFLtxrQM = false;}
      if(lUVDGPSXwq == true){lUVDGPSXwq = false;}
      if(uffOnqqMVn == true){uffOnqqMVn = false;}
      if(GPmWSLhebm == true){GPmWSLhebm = false;}
      if(zDSjnxZZul == true){zDSjnxZZul = false;}
      if(XzoAKZnuRT == true){XzoAKZnuRT = false;}
      if(CjWcGWgzkt == true){CjWcGWgzkt = false;}
      if(gmwIrqNuap == true){gmwIrqNuap = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PBTTWSMRSC
{ 
  void IHFrUWLCPE()
  { 
      bool SHmTIQIPuC = false;
      bool UyVRfKiYuh = false;
      bool tOxLcRKZbh = false;
      bool powfUqwJGA = false;
      bool xPsxuIJeTE = false;
      bool LEcFaDJapq = false;
      bool FhmNLfBpwn = false;
      bool NYSukdVAQU = false;
      bool HfGWWkLpFQ = false;
      bool hVSPtOcflP = false;
      bool HSheqllhUw = false;
      bool hIJViZbQpZ = false;
      bool TKjfGqGDAV = false;
      bool BoOBMnxaej = false;
      bool zdVIiYLxfU = false;
      bool lLoLuxiCYA = false;
      bool fhgytstIJt = false;
      bool bBlGZpoawg = false;
      bool eIWeipzCFP = false;
      bool FuBdDQwWOp = false;
      string IIspRTJqnt;
      string QngQfwhFCe;
      string mDSwmEwhXk;
      string IGHNMfUrrc;
      string IIKuSLQYPJ;
      string hHgWHFpxCN;
      string XaTDlKgTEA;
      string aoMYVdsXdb;
      string mWRNCBYjFH;
      string oXpeFgoGJH;
      string dxTPhstHAc;
      string MSSZaAJFAj;
      string kwNwKDzhTn;
      string olNVxpDBeJ;
      string GRjcuWEPEF;
      string XiGYVhiXFe;
      string tMmLnZExbj;
      string xHZqcTMkBm;
      string yjdOQFfozP;
      string GewAPtdXnU;
      if(IIspRTJqnt == dxTPhstHAc){SHmTIQIPuC = true;}
      else if(dxTPhstHAc == IIspRTJqnt){HSheqllhUw = true;}
      if(QngQfwhFCe == MSSZaAJFAj){UyVRfKiYuh = true;}
      else if(MSSZaAJFAj == QngQfwhFCe){hIJViZbQpZ = true;}
      if(mDSwmEwhXk == kwNwKDzhTn){tOxLcRKZbh = true;}
      else if(kwNwKDzhTn == mDSwmEwhXk){TKjfGqGDAV = true;}
      if(IGHNMfUrrc == olNVxpDBeJ){powfUqwJGA = true;}
      else if(olNVxpDBeJ == IGHNMfUrrc){BoOBMnxaej = true;}
      if(IIKuSLQYPJ == GRjcuWEPEF){xPsxuIJeTE = true;}
      else if(GRjcuWEPEF == IIKuSLQYPJ){zdVIiYLxfU = true;}
      if(hHgWHFpxCN == XiGYVhiXFe){LEcFaDJapq = true;}
      else if(XiGYVhiXFe == hHgWHFpxCN){lLoLuxiCYA = true;}
      if(XaTDlKgTEA == tMmLnZExbj){FhmNLfBpwn = true;}
      else if(tMmLnZExbj == XaTDlKgTEA){fhgytstIJt = true;}
      if(aoMYVdsXdb == xHZqcTMkBm){NYSukdVAQU = true;}
      if(mWRNCBYjFH == yjdOQFfozP){HfGWWkLpFQ = true;}
      if(oXpeFgoGJH == GewAPtdXnU){hVSPtOcflP = true;}
      while(xHZqcTMkBm == aoMYVdsXdb){bBlGZpoawg = true;}
      while(yjdOQFfozP == yjdOQFfozP){eIWeipzCFP = true;}
      while(GewAPtdXnU == GewAPtdXnU){FuBdDQwWOp = true;}
      if(SHmTIQIPuC == true){SHmTIQIPuC = false;}
      if(UyVRfKiYuh == true){UyVRfKiYuh = false;}
      if(tOxLcRKZbh == true){tOxLcRKZbh = false;}
      if(powfUqwJGA == true){powfUqwJGA = false;}
      if(xPsxuIJeTE == true){xPsxuIJeTE = false;}
      if(LEcFaDJapq == true){LEcFaDJapq = false;}
      if(FhmNLfBpwn == true){FhmNLfBpwn = false;}
      if(NYSukdVAQU == true){NYSukdVAQU = false;}
      if(HfGWWkLpFQ == true){HfGWWkLpFQ = false;}
      if(hVSPtOcflP == true){hVSPtOcflP = false;}
      if(HSheqllhUw == true){HSheqllhUw = false;}
      if(hIJViZbQpZ == true){hIJViZbQpZ = false;}
      if(TKjfGqGDAV == true){TKjfGqGDAV = false;}
      if(BoOBMnxaej == true){BoOBMnxaej = false;}
      if(zdVIiYLxfU == true){zdVIiYLxfU = false;}
      if(lLoLuxiCYA == true){lLoLuxiCYA = false;}
      if(fhgytstIJt == true){fhgytstIJt = false;}
      if(bBlGZpoawg == true){bBlGZpoawg = false;}
      if(eIWeipzCFP == true){eIWeipzCFP = false;}
      if(FuBdDQwWOp == true){FuBdDQwWOp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BGPUFPLXID
{ 
  void BReUbQnaFw()
  { 
      bool OJYaLzRJmC = false;
      bool ueKoSIZVeh = false;
      bool aaqSUjpBjG = false;
      bool yKCoIXlHKX = false;
      bool iMulLmDWBx = false;
      bool jQwPOnRFFb = false;
      bool IQZgDkcUfu = false;
      bool WRLHyOeFGh = false;
      bool fSAlVgNmZU = false;
      bool FfBiOSlNha = false;
      bool KhpGaRFnQA = false;
      bool IMzXupQmKV = false;
      bool WouLopPbsf = false;
      bool bRWeXxcsLD = false;
      bool aYWZLsgdmY = false;
      bool BzCLEUmeQk = false;
      bool CcujYqpTzx = false;
      bool MWbGuxSVzw = false;
      bool IkoUdbOKaD = false;
      bool KybZBydlAU = false;
      string lgpFBLLbbd;
      string jtpnBJmiVd;
      string kcOCEJuFpG;
      string XRZBOllOoc;
      string gQnqVRAhXu;
      string BzPWtISnBq;
      string QGkVGSToYP;
      string WXtrxUoWfl;
      string INgtEXCDHG;
      string TyNxMZeRkD;
      string xLIIYdFXYZ;
      string TuIOiCZqRh;
      string PQgSwXJxfW;
      string oWlbnwEXUa;
      string RedhmXpyNJ;
      string AnADmgepMA;
      string TIqCjwJfZm;
      string yBVqPklzeX;
      string hKiVWBVhnH;
      string ROLTGJmbxp;
      if(lgpFBLLbbd == xLIIYdFXYZ){OJYaLzRJmC = true;}
      else if(xLIIYdFXYZ == lgpFBLLbbd){KhpGaRFnQA = true;}
      if(jtpnBJmiVd == TuIOiCZqRh){ueKoSIZVeh = true;}
      else if(TuIOiCZqRh == jtpnBJmiVd){IMzXupQmKV = true;}
      if(kcOCEJuFpG == PQgSwXJxfW){aaqSUjpBjG = true;}
      else if(PQgSwXJxfW == kcOCEJuFpG){WouLopPbsf = true;}
      if(XRZBOllOoc == oWlbnwEXUa){yKCoIXlHKX = true;}
      else if(oWlbnwEXUa == XRZBOllOoc){bRWeXxcsLD = true;}
      if(gQnqVRAhXu == RedhmXpyNJ){iMulLmDWBx = true;}
      else if(RedhmXpyNJ == gQnqVRAhXu){aYWZLsgdmY = true;}
      if(BzPWtISnBq == AnADmgepMA){jQwPOnRFFb = true;}
      else if(AnADmgepMA == BzPWtISnBq){BzCLEUmeQk = true;}
      if(QGkVGSToYP == TIqCjwJfZm){IQZgDkcUfu = true;}
      else if(TIqCjwJfZm == QGkVGSToYP){CcujYqpTzx = true;}
      if(WXtrxUoWfl == yBVqPklzeX){WRLHyOeFGh = true;}
      if(INgtEXCDHG == hKiVWBVhnH){fSAlVgNmZU = true;}
      if(TyNxMZeRkD == ROLTGJmbxp){FfBiOSlNha = true;}
      while(yBVqPklzeX == WXtrxUoWfl){MWbGuxSVzw = true;}
      while(hKiVWBVhnH == hKiVWBVhnH){IkoUdbOKaD = true;}
      while(ROLTGJmbxp == ROLTGJmbxp){KybZBydlAU = true;}
      if(OJYaLzRJmC == true){OJYaLzRJmC = false;}
      if(ueKoSIZVeh == true){ueKoSIZVeh = false;}
      if(aaqSUjpBjG == true){aaqSUjpBjG = false;}
      if(yKCoIXlHKX == true){yKCoIXlHKX = false;}
      if(iMulLmDWBx == true){iMulLmDWBx = false;}
      if(jQwPOnRFFb == true){jQwPOnRFFb = false;}
      if(IQZgDkcUfu == true){IQZgDkcUfu = false;}
      if(WRLHyOeFGh == true){WRLHyOeFGh = false;}
      if(fSAlVgNmZU == true){fSAlVgNmZU = false;}
      if(FfBiOSlNha == true){FfBiOSlNha = false;}
      if(KhpGaRFnQA == true){KhpGaRFnQA = false;}
      if(IMzXupQmKV == true){IMzXupQmKV = false;}
      if(WouLopPbsf == true){WouLopPbsf = false;}
      if(bRWeXxcsLD == true){bRWeXxcsLD = false;}
      if(aYWZLsgdmY == true){aYWZLsgdmY = false;}
      if(BzCLEUmeQk == true){BzCLEUmeQk = false;}
      if(CcujYqpTzx == true){CcujYqpTzx = false;}
      if(MWbGuxSVzw == true){MWbGuxSVzw = false;}
      if(IkoUdbOKaD == true){IkoUdbOKaD = false;}
      if(KybZBydlAU == true){KybZBydlAU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NWDDSAMFEN
{ 
  void YDtbgGmDUi()
  { 
      bool TJtcnIJuQi = false;
      bool rlZsOqIFaa = false;
      bool FeIZIXxeOC = false;
      bool LaaNpdwKRw = false;
      bool TfyzjtKGoO = false;
      bool mzEFjnATUP = false;
      bool KdfOWQLLDj = false;
      bool uymeGYfIpN = false;
      bool MqpAOMWVdB = false;
      bool cboBkpAjcS = false;
      bool hzDESoLZyK = false;
      bool HqdGDTnezK = false;
      bool tphBGSIksP = false;
      bool YwfXeMnkgZ = false;
      bool AxWSslyhyQ = false;
      bool CVjRYrRBxA = false;
      bool fZfhlLLGbp = false;
      bool fCxYJwSOHU = false;
      bool TZmbNDLNzm = false;
      bool ulngtaRngh = false;
      string EyEIbizoUi;
      string dkAISlRzgC;
      string ZMjLiAsUDz;
      string sRNumDUBJK;
      string jTuxtooZpH;
      string mtlJhqNrYa;
      string pdkUpMWEVO;
      string QQpWRFRmQt;
      string LSdwLyeEMu;
      string pbbiTGhZHh;
      string SkDbpWEOrb;
      string YaaePWAoJr;
      string gSqZYnnHDL;
      string XreibZOCFn;
      string sQLkWOBxSx;
      string GsPPAzscCB;
      string ixLfEgurCo;
      string IxiUyQGGDJ;
      string mqnFFdbPib;
      string gkzDFwEefo;
      if(EyEIbizoUi == SkDbpWEOrb){TJtcnIJuQi = true;}
      else if(SkDbpWEOrb == EyEIbizoUi){hzDESoLZyK = true;}
      if(dkAISlRzgC == YaaePWAoJr){rlZsOqIFaa = true;}
      else if(YaaePWAoJr == dkAISlRzgC){HqdGDTnezK = true;}
      if(ZMjLiAsUDz == gSqZYnnHDL){FeIZIXxeOC = true;}
      else if(gSqZYnnHDL == ZMjLiAsUDz){tphBGSIksP = true;}
      if(sRNumDUBJK == XreibZOCFn){LaaNpdwKRw = true;}
      else if(XreibZOCFn == sRNumDUBJK){YwfXeMnkgZ = true;}
      if(jTuxtooZpH == sQLkWOBxSx){TfyzjtKGoO = true;}
      else if(sQLkWOBxSx == jTuxtooZpH){AxWSslyhyQ = true;}
      if(mtlJhqNrYa == GsPPAzscCB){mzEFjnATUP = true;}
      else if(GsPPAzscCB == mtlJhqNrYa){CVjRYrRBxA = true;}
      if(pdkUpMWEVO == ixLfEgurCo){KdfOWQLLDj = true;}
      else if(ixLfEgurCo == pdkUpMWEVO){fZfhlLLGbp = true;}
      if(QQpWRFRmQt == IxiUyQGGDJ){uymeGYfIpN = true;}
      if(LSdwLyeEMu == mqnFFdbPib){MqpAOMWVdB = true;}
      if(pbbiTGhZHh == gkzDFwEefo){cboBkpAjcS = true;}
      while(IxiUyQGGDJ == QQpWRFRmQt){fCxYJwSOHU = true;}
      while(mqnFFdbPib == mqnFFdbPib){TZmbNDLNzm = true;}
      while(gkzDFwEefo == gkzDFwEefo){ulngtaRngh = true;}
      if(TJtcnIJuQi == true){TJtcnIJuQi = false;}
      if(rlZsOqIFaa == true){rlZsOqIFaa = false;}
      if(FeIZIXxeOC == true){FeIZIXxeOC = false;}
      if(LaaNpdwKRw == true){LaaNpdwKRw = false;}
      if(TfyzjtKGoO == true){TfyzjtKGoO = false;}
      if(mzEFjnATUP == true){mzEFjnATUP = false;}
      if(KdfOWQLLDj == true){KdfOWQLLDj = false;}
      if(uymeGYfIpN == true){uymeGYfIpN = false;}
      if(MqpAOMWVdB == true){MqpAOMWVdB = false;}
      if(cboBkpAjcS == true){cboBkpAjcS = false;}
      if(hzDESoLZyK == true){hzDESoLZyK = false;}
      if(HqdGDTnezK == true){HqdGDTnezK = false;}
      if(tphBGSIksP == true){tphBGSIksP = false;}
      if(YwfXeMnkgZ == true){YwfXeMnkgZ = false;}
      if(AxWSslyhyQ == true){AxWSslyhyQ = false;}
      if(CVjRYrRBxA == true){CVjRYrRBxA = false;}
      if(fZfhlLLGbp == true){fZfhlLLGbp = false;}
      if(fCxYJwSOHU == true){fCxYJwSOHU = false;}
      if(TZmbNDLNzm == true){TZmbNDLNzm = false;}
      if(ulngtaRngh == true){ulngtaRngh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXVKMQOXLX
{ 
  void zODwLdrhUU()
  { 
      bool PokeONkdll = false;
      bool fLaCXiORLS = false;
      bool eIsgrrIiZo = false;
      bool UMnzAlrJzh = false;
      bool jrqLlOESud = false;
      bool hqAlYHuElV = false;
      bool FCEwRTWaBk = false;
      bool pERdhlRgtc = false;
      bool mpmuHcMCZs = false;
      bool pmXdchnttS = false;
      bool qcQKncZVDm = false;
      bool oOJIiOPJnn = false;
      bool GUBItCgnBA = false;
      bool yXmbkJZcHd = false;
      bool DpymEbcOtN = false;
      bool SdFGLWbHPk = false;
      bool wkUDnRbhXY = false;
      bool olCKjPWNES = false;
      bool YSsmhTRgQO = false;
      bool gRNVhRVtzl = false;
      string lxkZVmMPWo;
      string SXpXupVAeB;
      string OXycgyBTYD;
      string MbMINnuASH;
      string DyAlbJZAtA;
      string yXEuPOyHsW;
      string krqTbqKgJH;
      string tVhWyQWLBW;
      string XBZXEoWQsz;
      string omGuVKGgKk;
      string zsplFcogwy;
      string rmGVyiRTOl;
      string TsnKSHOlBn;
      string JoBPXeKnRb;
      string zoUtGCfjxm;
      string rmRXQFEeSy;
      string NDfIoClqyS;
      string XdBmldYsEQ;
      string adnOwVWcyR;
      string ZfUSNwJMFE;
      if(lxkZVmMPWo == zsplFcogwy){PokeONkdll = true;}
      else if(zsplFcogwy == lxkZVmMPWo){qcQKncZVDm = true;}
      if(SXpXupVAeB == rmGVyiRTOl){fLaCXiORLS = true;}
      else if(rmGVyiRTOl == SXpXupVAeB){oOJIiOPJnn = true;}
      if(OXycgyBTYD == TsnKSHOlBn){eIsgrrIiZo = true;}
      else if(TsnKSHOlBn == OXycgyBTYD){GUBItCgnBA = true;}
      if(MbMINnuASH == JoBPXeKnRb){UMnzAlrJzh = true;}
      else if(JoBPXeKnRb == MbMINnuASH){yXmbkJZcHd = true;}
      if(DyAlbJZAtA == zoUtGCfjxm){jrqLlOESud = true;}
      else if(zoUtGCfjxm == DyAlbJZAtA){DpymEbcOtN = true;}
      if(yXEuPOyHsW == rmRXQFEeSy){hqAlYHuElV = true;}
      else if(rmRXQFEeSy == yXEuPOyHsW){SdFGLWbHPk = true;}
      if(krqTbqKgJH == NDfIoClqyS){FCEwRTWaBk = true;}
      else if(NDfIoClqyS == krqTbqKgJH){wkUDnRbhXY = true;}
      if(tVhWyQWLBW == XdBmldYsEQ){pERdhlRgtc = true;}
      if(XBZXEoWQsz == adnOwVWcyR){mpmuHcMCZs = true;}
      if(omGuVKGgKk == ZfUSNwJMFE){pmXdchnttS = true;}
      while(XdBmldYsEQ == tVhWyQWLBW){olCKjPWNES = true;}
      while(adnOwVWcyR == adnOwVWcyR){YSsmhTRgQO = true;}
      while(ZfUSNwJMFE == ZfUSNwJMFE){gRNVhRVtzl = true;}
      if(PokeONkdll == true){PokeONkdll = false;}
      if(fLaCXiORLS == true){fLaCXiORLS = false;}
      if(eIsgrrIiZo == true){eIsgrrIiZo = false;}
      if(UMnzAlrJzh == true){UMnzAlrJzh = false;}
      if(jrqLlOESud == true){jrqLlOESud = false;}
      if(hqAlYHuElV == true){hqAlYHuElV = false;}
      if(FCEwRTWaBk == true){FCEwRTWaBk = false;}
      if(pERdhlRgtc == true){pERdhlRgtc = false;}
      if(mpmuHcMCZs == true){mpmuHcMCZs = false;}
      if(pmXdchnttS == true){pmXdchnttS = false;}
      if(qcQKncZVDm == true){qcQKncZVDm = false;}
      if(oOJIiOPJnn == true){oOJIiOPJnn = false;}
      if(GUBItCgnBA == true){GUBItCgnBA = false;}
      if(yXmbkJZcHd == true){yXmbkJZcHd = false;}
      if(DpymEbcOtN == true){DpymEbcOtN = false;}
      if(SdFGLWbHPk == true){SdFGLWbHPk = false;}
      if(wkUDnRbhXY == true){wkUDnRbhXY = false;}
      if(olCKjPWNES == true){olCKjPWNES = false;}
      if(YSsmhTRgQO == true){YSsmhTRgQO = false;}
      if(gRNVhRVtzl == true){gRNVhRVtzl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PUKSKNKSGT
{ 
  void lsPWVmbXdA()
  { 
      bool uuRsZWUzqs = false;
      bool kZlqNWzQjB = false;
      bool pCLYRduSsg = false;
      bool aGAldXtQhI = false;
      bool gmqWsKlcYO = false;
      bool nRPForjsbu = false;
      bool aBGKReYzNp = false;
      bool chibUCLneH = false;
      bool qStdsIptxk = false;
      bool nBomgeggFO = false;
      bool klOilFinkl = false;
      bool fuNUDHHbRI = false;
      bool neCbCbsuto = false;
      bool VeiPVEDKrm = false;
      bool ZCJLErmUiZ = false;
      bool XEOwZGjmgK = false;
      bool MmsuQBMxyy = false;
      bool DwjeilUqWJ = false;
      bool nYLURQPlpO = false;
      bool UQdgZlIOtD = false;
      string VyntREEAeg;
      string FDNitVAant;
      string DYnzbdRyeo;
      string BUhDDYJREu;
      string qXXMIlKKrk;
      string AmCjLxJnSm;
      string mFUpfkVKfU;
      string MhWsCfAbqo;
      string SGGsnNRxqF;
      string OUzQIkCgfW;
      string QAdWYSPJgf;
      string whwcUfzaBS;
      string SXSZGqiGjR;
      string cSwUYRcjUV;
      string xIQKIgXWwc;
      string lafMDshDPg;
      string iJYPDdlbEC;
      string DPGfUKHHRY;
      string TMKHeBmiQe;
      string jYTmlniAHe;
      if(VyntREEAeg == QAdWYSPJgf){uuRsZWUzqs = true;}
      else if(QAdWYSPJgf == VyntREEAeg){klOilFinkl = true;}
      if(FDNitVAant == whwcUfzaBS){kZlqNWzQjB = true;}
      else if(whwcUfzaBS == FDNitVAant){fuNUDHHbRI = true;}
      if(DYnzbdRyeo == SXSZGqiGjR){pCLYRduSsg = true;}
      else if(SXSZGqiGjR == DYnzbdRyeo){neCbCbsuto = true;}
      if(BUhDDYJREu == cSwUYRcjUV){aGAldXtQhI = true;}
      else if(cSwUYRcjUV == BUhDDYJREu){VeiPVEDKrm = true;}
      if(qXXMIlKKrk == xIQKIgXWwc){gmqWsKlcYO = true;}
      else if(xIQKIgXWwc == qXXMIlKKrk){ZCJLErmUiZ = true;}
      if(AmCjLxJnSm == lafMDshDPg){nRPForjsbu = true;}
      else if(lafMDshDPg == AmCjLxJnSm){XEOwZGjmgK = true;}
      if(mFUpfkVKfU == iJYPDdlbEC){aBGKReYzNp = true;}
      else if(iJYPDdlbEC == mFUpfkVKfU){MmsuQBMxyy = true;}
      if(MhWsCfAbqo == DPGfUKHHRY){chibUCLneH = true;}
      if(SGGsnNRxqF == TMKHeBmiQe){qStdsIptxk = true;}
      if(OUzQIkCgfW == jYTmlniAHe){nBomgeggFO = true;}
      while(DPGfUKHHRY == MhWsCfAbqo){DwjeilUqWJ = true;}
      while(TMKHeBmiQe == TMKHeBmiQe){nYLURQPlpO = true;}
      while(jYTmlniAHe == jYTmlniAHe){UQdgZlIOtD = true;}
      if(uuRsZWUzqs == true){uuRsZWUzqs = false;}
      if(kZlqNWzQjB == true){kZlqNWzQjB = false;}
      if(pCLYRduSsg == true){pCLYRduSsg = false;}
      if(aGAldXtQhI == true){aGAldXtQhI = false;}
      if(gmqWsKlcYO == true){gmqWsKlcYO = false;}
      if(nRPForjsbu == true){nRPForjsbu = false;}
      if(aBGKReYzNp == true){aBGKReYzNp = false;}
      if(chibUCLneH == true){chibUCLneH = false;}
      if(qStdsIptxk == true){qStdsIptxk = false;}
      if(nBomgeggFO == true){nBomgeggFO = false;}
      if(klOilFinkl == true){klOilFinkl = false;}
      if(fuNUDHHbRI == true){fuNUDHHbRI = false;}
      if(neCbCbsuto == true){neCbCbsuto = false;}
      if(VeiPVEDKrm == true){VeiPVEDKrm = false;}
      if(ZCJLErmUiZ == true){ZCJLErmUiZ = false;}
      if(XEOwZGjmgK == true){XEOwZGjmgK = false;}
      if(MmsuQBMxyy == true){MmsuQBMxyy = false;}
      if(DwjeilUqWJ == true){DwjeilUqWJ = false;}
      if(nYLURQPlpO == true){nYLURQPlpO = false;}
      if(UQdgZlIOtD == true){UQdgZlIOtD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NUBJEDGNNG
{ 
  void hHzoxdreGR()
  { 
      bool fkDUiejgzw = false;
      bool fLeAJqtxxU = false;
      bool ILlYontxXd = false;
      bool zaowXexMdu = false;
      bool FrEpLbGlnq = false;
      bool wKddmUzeeu = false;
      bool jmIUwEVicd = false;
      bool shTBPPGuMM = false;
      bool gIIfgowLID = false;
      bool fShiKRjjsH = false;
      bool GWIJxOqcOW = false;
      bool ODRSNaebnH = false;
      bool HKZYyazjqx = false;
      bool fVCFFKzyhS = false;
      bool xTwkobAPVj = false;
      bool mHwlzwwjLW = false;
      bool OGlQqrBMMD = false;
      bool bfsUJmNojV = false;
      bool ZjOGKYZQFJ = false;
      bool NPmLEphetx = false;
      string GbUUedGTDr;
      string aJfBmJwMoh;
      string MaGiPasjZg;
      string cwuqEEKQSb;
      string IrrYLBmpmA;
      string rBujBeUlFE;
      string kVsVPdOnwi;
      string zftMYUigXN;
      string mCwZnaBKpZ;
      string iYKOqlzVIg;
      string mytEBMHhKf;
      string unOqQhZTho;
      string bDyWzaUeVm;
      string VNXpanIrYa;
      string TTzJduJTxI;
      string MfmTEiAWFa;
      string rbLXKhPXQc;
      string YguGUIDorE;
      string QAgNZpZElq;
      string nkmxiqIbzw;
      if(GbUUedGTDr == mytEBMHhKf){fkDUiejgzw = true;}
      else if(mytEBMHhKf == GbUUedGTDr){GWIJxOqcOW = true;}
      if(aJfBmJwMoh == unOqQhZTho){fLeAJqtxxU = true;}
      else if(unOqQhZTho == aJfBmJwMoh){ODRSNaebnH = true;}
      if(MaGiPasjZg == bDyWzaUeVm){ILlYontxXd = true;}
      else if(bDyWzaUeVm == MaGiPasjZg){HKZYyazjqx = true;}
      if(cwuqEEKQSb == VNXpanIrYa){zaowXexMdu = true;}
      else if(VNXpanIrYa == cwuqEEKQSb){fVCFFKzyhS = true;}
      if(IrrYLBmpmA == TTzJduJTxI){FrEpLbGlnq = true;}
      else if(TTzJduJTxI == IrrYLBmpmA){xTwkobAPVj = true;}
      if(rBujBeUlFE == MfmTEiAWFa){wKddmUzeeu = true;}
      else if(MfmTEiAWFa == rBujBeUlFE){mHwlzwwjLW = true;}
      if(kVsVPdOnwi == rbLXKhPXQc){jmIUwEVicd = true;}
      else if(rbLXKhPXQc == kVsVPdOnwi){OGlQqrBMMD = true;}
      if(zftMYUigXN == YguGUIDorE){shTBPPGuMM = true;}
      if(mCwZnaBKpZ == QAgNZpZElq){gIIfgowLID = true;}
      if(iYKOqlzVIg == nkmxiqIbzw){fShiKRjjsH = true;}
      while(YguGUIDorE == zftMYUigXN){bfsUJmNojV = true;}
      while(QAgNZpZElq == QAgNZpZElq){ZjOGKYZQFJ = true;}
      while(nkmxiqIbzw == nkmxiqIbzw){NPmLEphetx = true;}
      if(fkDUiejgzw == true){fkDUiejgzw = false;}
      if(fLeAJqtxxU == true){fLeAJqtxxU = false;}
      if(ILlYontxXd == true){ILlYontxXd = false;}
      if(zaowXexMdu == true){zaowXexMdu = false;}
      if(FrEpLbGlnq == true){FrEpLbGlnq = false;}
      if(wKddmUzeeu == true){wKddmUzeeu = false;}
      if(jmIUwEVicd == true){jmIUwEVicd = false;}
      if(shTBPPGuMM == true){shTBPPGuMM = false;}
      if(gIIfgowLID == true){gIIfgowLID = false;}
      if(fShiKRjjsH == true){fShiKRjjsH = false;}
      if(GWIJxOqcOW == true){GWIJxOqcOW = false;}
      if(ODRSNaebnH == true){ODRSNaebnH = false;}
      if(HKZYyazjqx == true){HKZYyazjqx = false;}
      if(fVCFFKzyhS == true){fVCFFKzyhS = false;}
      if(xTwkobAPVj == true){xTwkobAPVj = false;}
      if(mHwlzwwjLW == true){mHwlzwwjLW = false;}
      if(OGlQqrBMMD == true){OGlQqrBMMD = false;}
      if(bfsUJmNojV == true){bfsUJmNojV = false;}
      if(ZjOGKYZQFJ == true){ZjOGKYZQFJ = false;}
      if(NPmLEphetx == true){NPmLEphetx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHLVYEOAYD
{ 
  void SBRgAfbjro()
  { 
      bool ikghDJXKSu = false;
      bool wTAtFekWJt = false;
      bool UwYPnBgZiL = false;
      bool IPJfwBnRJk = false;
      bool fHonAxVLCJ = false;
      bool SRqKqmMRsC = false;
      bool cxbGmgJUxD = false;
      bool qSNYONGjPq = false;
      bool eUXYsqXyoJ = false;
      bool oWYHHheiBT = false;
      bool mBOySzDSwd = false;
      bool fcBCWIYDNu = false;
      bool ILfmOTtFQf = false;
      bool hXhwDdGZFs = false;
      bool mFCLdMUVjz = false;
      bool IbUFKbVaiz = false;
      bool FxCPuHtFzs = false;
      bool CzyUIDIUJC = false;
      bool yYVRXGCbka = false;
      bool HepGnoDlPV = false;
      string PaJhyQaUiF;
      string zlzSTYXrNY;
      string uXxdMmYdMK;
      string fdKTiNLnGH;
      string OxWPkOiWBl;
      string BNeGGqdeVK;
      string qxIXZVbfjF;
      string MikFJyBgsy;
      string DCcZJSyDMq;
      string jfSuQRnypP;
      string lDluYRbZxI;
      string pwlXHnUhOG;
      string WXTsUgQoor;
      string JCqcLAQgAq;
      string pYGEAnttnb;
      string xFiisOisar;
      string BljEynEIMG;
      string XmhXQxRPrf;
      string mVANuDSIjw;
      string RWGHoEnBFM;
      if(PaJhyQaUiF == lDluYRbZxI){ikghDJXKSu = true;}
      else if(lDluYRbZxI == PaJhyQaUiF){mBOySzDSwd = true;}
      if(zlzSTYXrNY == pwlXHnUhOG){wTAtFekWJt = true;}
      else if(pwlXHnUhOG == zlzSTYXrNY){fcBCWIYDNu = true;}
      if(uXxdMmYdMK == WXTsUgQoor){UwYPnBgZiL = true;}
      else if(WXTsUgQoor == uXxdMmYdMK){ILfmOTtFQf = true;}
      if(fdKTiNLnGH == JCqcLAQgAq){IPJfwBnRJk = true;}
      else if(JCqcLAQgAq == fdKTiNLnGH){hXhwDdGZFs = true;}
      if(OxWPkOiWBl == pYGEAnttnb){fHonAxVLCJ = true;}
      else if(pYGEAnttnb == OxWPkOiWBl){mFCLdMUVjz = true;}
      if(BNeGGqdeVK == xFiisOisar){SRqKqmMRsC = true;}
      else if(xFiisOisar == BNeGGqdeVK){IbUFKbVaiz = true;}
      if(qxIXZVbfjF == BljEynEIMG){cxbGmgJUxD = true;}
      else if(BljEynEIMG == qxIXZVbfjF){FxCPuHtFzs = true;}
      if(MikFJyBgsy == XmhXQxRPrf){qSNYONGjPq = true;}
      if(DCcZJSyDMq == mVANuDSIjw){eUXYsqXyoJ = true;}
      if(jfSuQRnypP == RWGHoEnBFM){oWYHHheiBT = true;}
      while(XmhXQxRPrf == MikFJyBgsy){CzyUIDIUJC = true;}
      while(mVANuDSIjw == mVANuDSIjw){yYVRXGCbka = true;}
      while(RWGHoEnBFM == RWGHoEnBFM){HepGnoDlPV = true;}
      if(ikghDJXKSu == true){ikghDJXKSu = false;}
      if(wTAtFekWJt == true){wTAtFekWJt = false;}
      if(UwYPnBgZiL == true){UwYPnBgZiL = false;}
      if(IPJfwBnRJk == true){IPJfwBnRJk = false;}
      if(fHonAxVLCJ == true){fHonAxVLCJ = false;}
      if(SRqKqmMRsC == true){SRqKqmMRsC = false;}
      if(cxbGmgJUxD == true){cxbGmgJUxD = false;}
      if(qSNYONGjPq == true){qSNYONGjPq = false;}
      if(eUXYsqXyoJ == true){eUXYsqXyoJ = false;}
      if(oWYHHheiBT == true){oWYHHheiBT = false;}
      if(mBOySzDSwd == true){mBOySzDSwd = false;}
      if(fcBCWIYDNu == true){fcBCWIYDNu = false;}
      if(ILfmOTtFQf == true){ILfmOTtFQf = false;}
      if(hXhwDdGZFs == true){hXhwDdGZFs = false;}
      if(mFCLdMUVjz == true){mFCLdMUVjz = false;}
      if(IbUFKbVaiz == true){IbUFKbVaiz = false;}
      if(FxCPuHtFzs == true){FxCPuHtFzs = false;}
      if(CzyUIDIUJC == true){CzyUIDIUJC = false;}
      if(yYVRXGCbka == true){yYVRXGCbka = false;}
      if(HepGnoDlPV == true){HepGnoDlPV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LYWKIXGZSQ
{ 
  void QamaIslTTW()
  { 
      bool QbIOqxPaEs = false;
      bool BIANXfomPo = false;
      bool upQmZJNPBp = false;
      bool EtZTbUurbY = false;
      bool zdUaaxruaw = false;
      bool lAlzYZKVog = false;
      bool izYOnHhgkC = false;
      bool jxLpoQUpLc = false;
      bool RRnFDEHatB = false;
      bool JZDtpAFGmT = false;
      bool OLKXLonuJH = false;
      bool FUKLPQKSKi = false;
      bool zHljsJsQAo = false;
      bool LODqNFHQsN = false;
      bool QMRmwoPqeY = false;
      bool olwDUHZaeC = false;
      bool uXtTwpRSyJ = false;
      bool ItZwSmpzmE = false;
      bool sCkazYSzWG = false;
      bool egkqSsRxpF = false;
      string hLXoxYcapt;
      string awqjllAchm;
      string BQmDrgMtra;
      string eZttwRXKUp;
      string ouKcZjajzs;
      string BHLbDQXUxP;
      string MhhPOBCxnT;
      string OoHqyGFKdH;
      string GcuzYXORpe;
      string tDNEdHMuNY;
      string gdwfeMzTdx;
      string KMpoJjlipq;
      string mjGIZKbCNq;
      string sKwFZcgPTM;
      string YtnrUgNXut;
      string UdEWkxWnFU;
      string jwGlEAPkPf;
      string CWOdRruNmr;
      string xEHSWOFZTc;
      string GrJzbbmBnT;
      if(hLXoxYcapt == gdwfeMzTdx){QbIOqxPaEs = true;}
      else if(gdwfeMzTdx == hLXoxYcapt){OLKXLonuJH = true;}
      if(awqjllAchm == KMpoJjlipq){BIANXfomPo = true;}
      else if(KMpoJjlipq == awqjllAchm){FUKLPQKSKi = true;}
      if(BQmDrgMtra == mjGIZKbCNq){upQmZJNPBp = true;}
      else if(mjGIZKbCNq == BQmDrgMtra){zHljsJsQAo = true;}
      if(eZttwRXKUp == sKwFZcgPTM){EtZTbUurbY = true;}
      else if(sKwFZcgPTM == eZttwRXKUp){LODqNFHQsN = true;}
      if(ouKcZjajzs == YtnrUgNXut){zdUaaxruaw = true;}
      else if(YtnrUgNXut == ouKcZjajzs){QMRmwoPqeY = true;}
      if(BHLbDQXUxP == UdEWkxWnFU){lAlzYZKVog = true;}
      else if(UdEWkxWnFU == BHLbDQXUxP){olwDUHZaeC = true;}
      if(MhhPOBCxnT == jwGlEAPkPf){izYOnHhgkC = true;}
      else if(jwGlEAPkPf == MhhPOBCxnT){uXtTwpRSyJ = true;}
      if(OoHqyGFKdH == CWOdRruNmr){jxLpoQUpLc = true;}
      if(GcuzYXORpe == xEHSWOFZTc){RRnFDEHatB = true;}
      if(tDNEdHMuNY == GrJzbbmBnT){JZDtpAFGmT = true;}
      while(CWOdRruNmr == OoHqyGFKdH){ItZwSmpzmE = true;}
      while(xEHSWOFZTc == xEHSWOFZTc){sCkazYSzWG = true;}
      while(GrJzbbmBnT == GrJzbbmBnT){egkqSsRxpF = true;}
      if(QbIOqxPaEs == true){QbIOqxPaEs = false;}
      if(BIANXfomPo == true){BIANXfomPo = false;}
      if(upQmZJNPBp == true){upQmZJNPBp = false;}
      if(EtZTbUurbY == true){EtZTbUurbY = false;}
      if(zdUaaxruaw == true){zdUaaxruaw = false;}
      if(lAlzYZKVog == true){lAlzYZKVog = false;}
      if(izYOnHhgkC == true){izYOnHhgkC = false;}
      if(jxLpoQUpLc == true){jxLpoQUpLc = false;}
      if(RRnFDEHatB == true){RRnFDEHatB = false;}
      if(JZDtpAFGmT == true){JZDtpAFGmT = false;}
      if(OLKXLonuJH == true){OLKXLonuJH = false;}
      if(FUKLPQKSKi == true){FUKLPQKSKi = false;}
      if(zHljsJsQAo == true){zHljsJsQAo = false;}
      if(LODqNFHQsN == true){LODqNFHQsN = false;}
      if(QMRmwoPqeY == true){QMRmwoPqeY = false;}
      if(olwDUHZaeC == true){olwDUHZaeC = false;}
      if(uXtTwpRSyJ == true){uXtTwpRSyJ = false;}
      if(ItZwSmpzmE == true){ItZwSmpzmE = false;}
      if(sCkazYSzWG == true){sCkazYSzWG = false;}
      if(egkqSsRxpF == true){egkqSsRxpF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HZXUKUEUIC
{ 
  void EorQyhEVyJ()
  { 
      bool GoGrQbcMiq = false;
      bool wPQCYLOUkA = false;
      bool qsUPRfqsRN = false;
      bool zuswYDmzGO = false;
      bool qGwicAtJMj = false;
      bool MaHFqNTpaj = false;
      bool kjtVqAWUcV = false;
      bool YONWIkwlmR = false;
      bool lgfhBYmnEL = false;
      bool iwYWcHLaqb = false;
      bool dYgpLxNjxG = false;
      bool QhDIxDDLUS = false;
      bool MhQRmcoqtA = false;
      bool YVuKmMApVD = false;
      bool LDqxtBrPYY = false;
      bool DzFXOuIODi = false;
      bool HWpwhtlsVj = false;
      bool DNpQHJqSWl = false;
      bool jZRUxYPWuq = false;
      bool EklmwoMuPz = false;
      string YxyRuleEmV;
      string YmpzAOciYI;
      string qlWESKLwVa;
      string qbMqhhosZi;
      string KYCYTRokKV;
      string eiOuRlZtyj;
      string ZihLexZzRS;
      string ZjIoxSjxjA;
      string ValAwINRYu;
      string HutpIbpptW;
      string roSrwuZYxy;
      string CcJyOzwhPV;
      string jIZWKdpSgV;
      string csDNIfHsDB;
      string hnUarekwaI;
      string eHaXmjPwgR;
      string FGrbUJYuoh;
      string rDdOnumzee;
      string rsrXpUSfaY;
      string QLLkwaurFh;
      if(YxyRuleEmV == roSrwuZYxy){GoGrQbcMiq = true;}
      else if(roSrwuZYxy == YxyRuleEmV){dYgpLxNjxG = true;}
      if(YmpzAOciYI == CcJyOzwhPV){wPQCYLOUkA = true;}
      else if(CcJyOzwhPV == YmpzAOciYI){QhDIxDDLUS = true;}
      if(qlWESKLwVa == jIZWKdpSgV){qsUPRfqsRN = true;}
      else if(jIZWKdpSgV == qlWESKLwVa){MhQRmcoqtA = true;}
      if(qbMqhhosZi == csDNIfHsDB){zuswYDmzGO = true;}
      else if(csDNIfHsDB == qbMqhhosZi){YVuKmMApVD = true;}
      if(KYCYTRokKV == hnUarekwaI){qGwicAtJMj = true;}
      else if(hnUarekwaI == KYCYTRokKV){LDqxtBrPYY = true;}
      if(eiOuRlZtyj == eHaXmjPwgR){MaHFqNTpaj = true;}
      else if(eHaXmjPwgR == eiOuRlZtyj){DzFXOuIODi = true;}
      if(ZihLexZzRS == FGrbUJYuoh){kjtVqAWUcV = true;}
      else if(FGrbUJYuoh == ZihLexZzRS){HWpwhtlsVj = true;}
      if(ZjIoxSjxjA == rDdOnumzee){YONWIkwlmR = true;}
      if(ValAwINRYu == rsrXpUSfaY){lgfhBYmnEL = true;}
      if(HutpIbpptW == QLLkwaurFh){iwYWcHLaqb = true;}
      while(rDdOnumzee == ZjIoxSjxjA){DNpQHJqSWl = true;}
      while(rsrXpUSfaY == rsrXpUSfaY){jZRUxYPWuq = true;}
      while(QLLkwaurFh == QLLkwaurFh){EklmwoMuPz = true;}
      if(GoGrQbcMiq == true){GoGrQbcMiq = false;}
      if(wPQCYLOUkA == true){wPQCYLOUkA = false;}
      if(qsUPRfqsRN == true){qsUPRfqsRN = false;}
      if(zuswYDmzGO == true){zuswYDmzGO = false;}
      if(qGwicAtJMj == true){qGwicAtJMj = false;}
      if(MaHFqNTpaj == true){MaHFqNTpaj = false;}
      if(kjtVqAWUcV == true){kjtVqAWUcV = false;}
      if(YONWIkwlmR == true){YONWIkwlmR = false;}
      if(lgfhBYmnEL == true){lgfhBYmnEL = false;}
      if(iwYWcHLaqb == true){iwYWcHLaqb = false;}
      if(dYgpLxNjxG == true){dYgpLxNjxG = false;}
      if(QhDIxDDLUS == true){QhDIxDDLUS = false;}
      if(MhQRmcoqtA == true){MhQRmcoqtA = false;}
      if(YVuKmMApVD == true){YVuKmMApVD = false;}
      if(LDqxtBrPYY == true){LDqxtBrPYY = false;}
      if(DzFXOuIODi == true){DzFXOuIODi = false;}
      if(HWpwhtlsVj == true){HWpwhtlsVj = false;}
      if(DNpQHJqSWl == true){DNpQHJqSWl = false;}
      if(jZRUxYPWuq == true){jZRUxYPWuq = false;}
      if(EklmwoMuPz == true){EklmwoMuPz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJDZYVYDXY
{ 
  void FoHhJAMbIR()
  { 
      bool GuYgsAPwBG = false;
      bool RRxkcKKPSz = false;
      bool JtUBosQzQZ = false;
      bool smYoOkhTDM = false;
      bool WRmyuAyVga = false;
      bool qotQXMZWqz = false;
      bool iPfbMesIWr = false;
      bool cpLFbqHWGo = false;
      bool ttSpiErIQC = false;
      bool KKcEdGlKkQ = false;
      bool GpzoyAcong = false;
      bool EDQBEnxpsI = false;
      bool lkrUgRNHbU = false;
      bool FwlohEudqh = false;
      bool bDTixHtazp = false;
      bool JuRbdVyeHf = false;
      bool mUNTaIQaTA = false;
      bool rTyKghQIWZ = false;
      bool WmHkKJdJKL = false;
      bool GQVLuGpAIo = false;
      string mwVODsUHVl;
      string pqDIcRFdci;
      string alKNVEZAyC;
      string eThNqbLbSI;
      string iLVZmZkNSR;
      string nNMTMBkHry;
      string SUJSGVJpRB;
      string FcKUAOQkZw;
      string SMgfNQHNAp;
      string pDiToNCDSR;
      string PuwRMLDqSy;
      string jAhueGncEo;
      string NwpbKCtpem;
      string MMRIgXQOTC;
      string NQtBFoVmoi;
      string YYycDTFTGJ;
      string QMLflXiZOH;
      string pYJCbxBnWU;
      string gGBwNmOnEN;
      string RwHJkBENPh;
      if(mwVODsUHVl == PuwRMLDqSy){GuYgsAPwBG = true;}
      else if(PuwRMLDqSy == mwVODsUHVl){GpzoyAcong = true;}
      if(pqDIcRFdci == jAhueGncEo){RRxkcKKPSz = true;}
      else if(jAhueGncEo == pqDIcRFdci){EDQBEnxpsI = true;}
      if(alKNVEZAyC == NwpbKCtpem){JtUBosQzQZ = true;}
      else if(NwpbKCtpem == alKNVEZAyC){lkrUgRNHbU = true;}
      if(eThNqbLbSI == MMRIgXQOTC){smYoOkhTDM = true;}
      else if(MMRIgXQOTC == eThNqbLbSI){FwlohEudqh = true;}
      if(iLVZmZkNSR == NQtBFoVmoi){WRmyuAyVga = true;}
      else if(NQtBFoVmoi == iLVZmZkNSR){bDTixHtazp = true;}
      if(nNMTMBkHry == YYycDTFTGJ){qotQXMZWqz = true;}
      else if(YYycDTFTGJ == nNMTMBkHry){JuRbdVyeHf = true;}
      if(SUJSGVJpRB == QMLflXiZOH){iPfbMesIWr = true;}
      else if(QMLflXiZOH == SUJSGVJpRB){mUNTaIQaTA = true;}
      if(FcKUAOQkZw == pYJCbxBnWU){cpLFbqHWGo = true;}
      if(SMgfNQHNAp == gGBwNmOnEN){ttSpiErIQC = true;}
      if(pDiToNCDSR == RwHJkBENPh){KKcEdGlKkQ = true;}
      while(pYJCbxBnWU == FcKUAOQkZw){rTyKghQIWZ = true;}
      while(gGBwNmOnEN == gGBwNmOnEN){WmHkKJdJKL = true;}
      while(RwHJkBENPh == RwHJkBENPh){GQVLuGpAIo = true;}
      if(GuYgsAPwBG == true){GuYgsAPwBG = false;}
      if(RRxkcKKPSz == true){RRxkcKKPSz = false;}
      if(JtUBosQzQZ == true){JtUBosQzQZ = false;}
      if(smYoOkhTDM == true){smYoOkhTDM = false;}
      if(WRmyuAyVga == true){WRmyuAyVga = false;}
      if(qotQXMZWqz == true){qotQXMZWqz = false;}
      if(iPfbMesIWr == true){iPfbMesIWr = false;}
      if(cpLFbqHWGo == true){cpLFbqHWGo = false;}
      if(ttSpiErIQC == true){ttSpiErIQC = false;}
      if(KKcEdGlKkQ == true){KKcEdGlKkQ = false;}
      if(GpzoyAcong == true){GpzoyAcong = false;}
      if(EDQBEnxpsI == true){EDQBEnxpsI = false;}
      if(lkrUgRNHbU == true){lkrUgRNHbU = false;}
      if(FwlohEudqh == true){FwlohEudqh = false;}
      if(bDTixHtazp == true){bDTixHtazp = false;}
      if(JuRbdVyeHf == true){JuRbdVyeHf = false;}
      if(mUNTaIQaTA == true){mUNTaIQaTA = false;}
      if(rTyKghQIWZ == true){rTyKghQIWZ = false;}
      if(WmHkKJdJKL == true){WmHkKJdJKL = false;}
      if(GQVLuGpAIo == true){GQVLuGpAIo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ECIRQOWSPC
{ 
  void mQsuCjoNUY()
  { 
      bool rARMnyCXbz = false;
      bool WzsufxuPtE = false;
      bool otqwaTQGzu = false;
      bool OBYiCnOhIQ = false;
      bool ZbbDOoitEK = false;
      bool mdITmyJVlT = false;
      bool hwYfkUaJsq = false;
      bool iMHdeMRmhk = false;
      bool kVBnIjsEuD = false;
      bool dsunidDwRs = false;
      bool OYBNbZVenZ = false;
      bool fVnAhLtkWA = false;
      bool aVOoNoRStB = false;
      bool JVVnWMUnLi = false;
      bool OOPUXIFtFX = false;
      bool iRZRRrKLzm = false;
      bool HCjmQKAzdV = false;
      bool qGYnlMFsRE = false;
      bool jWMWRrwEVd = false;
      bool BInYaLdcEM = false;
      string NnqGgQStil;
      string wsklJLQJFC;
      string DiOJHxTWql;
      string xkiXTYeqLK;
      string orZweCMCNi;
      string lLmqNeZhyj;
      string wwDwnKJMSk;
      string fZyuMKJRdF;
      string jRIHAlxrJn;
      string yxsaOrocIU;
      string szjbCLNreD;
      string VHDszdmuwC;
      string MRDdligWfU;
      string VfJJLjhgEn;
      string XFNGRqtzbj;
      string EsfFHawFpT;
      string epLKgoysgO;
      string wGqHdHExLu;
      string nguwPbADCk;
      string nbpjIhsCYc;
      if(NnqGgQStil == szjbCLNreD){rARMnyCXbz = true;}
      else if(szjbCLNreD == NnqGgQStil){OYBNbZVenZ = true;}
      if(wsklJLQJFC == VHDszdmuwC){WzsufxuPtE = true;}
      else if(VHDszdmuwC == wsklJLQJFC){fVnAhLtkWA = true;}
      if(DiOJHxTWql == MRDdligWfU){otqwaTQGzu = true;}
      else if(MRDdligWfU == DiOJHxTWql){aVOoNoRStB = true;}
      if(xkiXTYeqLK == VfJJLjhgEn){OBYiCnOhIQ = true;}
      else if(VfJJLjhgEn == xkiXTYeqLK){JVVnWMUnLi = true;}
      if(orZweCMCNi == XFNGRqtzbj){ZbbDOoitEK = true;}
      else if(XFNGRqtzbj == orZweCMCNi){OOPUXIFtFX = true;}
      if(lLmqNeZhyj == EsfFHawFpT){mdITmyJVlT = true;}
      else if(EsfFHawFpT == lLmqNeZhyj){iRZRRrKLzm = true;}
      if(wwDwnKJMSk == epLKgoysgO){hwYfkUaJsq = true;}
      else if(epLKgoysgO == wwDwnKJMSk){HCjmQKAzdV = true;}
      if(fZyuMKJRdF == wGqHdHExLu){iMHdeMRmhk = true;}
      if(jRIHAlxrJn == nguwPbADCk){kVBnIjsEuD = true;}
      if(yxsaOrocIU == nbpjIhsCYc){dsunidDwRs = true;}
      while(wGqHdHExLu == fZyuMKJRdF){qGYnlMFsRE = true;}
      while(nguwPbADCk == nguwPbADCk){jWMWRrwEVd = true;}
      while(nbpjIhsCYc == nbpjIhsCYc){BInYaLdcEM = true;}
      if(rARMnyCXbz == true){rARMnyCXbz = false;}
      if(WzsufxuPtE == true){WzsufxuPtE = false;}
      if(otqwaTQGzu == true){otqwaTQGzu = false;}
      if(OBYiCnOhIQ == true){OBYiCnOhIQ = false;}
      if(ZbbDOoitEK == true){ZbbDOoitEK = false;}
      if(mdITmyJVlT == true){mdITmyJVlT = false;}
      if(hwYfkUaJsq == true){hwYfkUaJsq = false;}
      if(iMHdeMRmhk == true){iMHdeMRmhk = false;}
      if(kVBnIjsEuD == true){kVBnIjsEuD = false;}
      if(dsunidDwRs == true){dsunidDwRs = false;}
      if(OYBNbZVenZ == true){OYBNbZVenZ = false;}
      if(fVnAhLtkWA == true){fVnAhLtkWA = false;}
      if(aVOoNoRStB == true){aVOoNoRStB = false;}
      if(JVVnWMUnLi == true){JVVnWMUnLi = false;}
      if(OOPUXIFtFX == true){OOPUXIFtFX = false;}
      if(iRZRRrKLzm == true){iRZRRrKLzm = false;}
      if(HCjmQKAzdV == true){HCjmQKAzdV = false;}
      if(qGYnlMFsRE == true){qGYnlMFsRE = false;}
      if(jWMWRrwEVd == true){jWMWRrwEVd = false;}
      if(BInYaLdcEM == true){BInYaLdcEM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RZTIMXMXSO
{ 
  void AcOKoynnqy()
  { 
      bool WLLHTxumKh = false;
      bool cGtbOazVTy = false;
      bool xXKgIhrpyS = false;
      bool fiWMdqcxJw = false;
      bool mYowhFCisT = false;
      bool GPYhWzBeyl = false;
      bool EEnrBtigxW = false;
      bool xCMWLXhNzD = false;
      bool eJxdMQKope = false;
      bool pyyWrhjxtn = false;
      bool WUkVVDDBWz = false;
      bool QmeuHuHKek = false;
      bool itqSgzDoec = false;
      bool mkSLfJXaII = false;
      bool NIRpNCSDPx = false;
      bool aZRJEcdSoW = false;
      bool zNWsLeTTOx = false;
      bool WfBVXabAEd = false;
      bool gAZhCMTJHD = false;
      bool fEllJzlXei = false;
      string LXhIJFzPFa;
      string aITCWjkRsi;
      string ogJnsRqsqi;
      string qOJdKTMdNP;
      string xrFDLmSedt;
      string PrEtGdOtPr;
      string OFXViLyorD;
      string WHEclxbFbF;
      string zLOxSzKPXf;
      string FSNVBqTiUz;
      string ocmaWInaIJ;
      string CJRJrCqZDj;
      string AiRLxEshbt;
      string crkcQWXnaK;
      string LjGNdwAEcy;
      string AtfjyFKbcS;
      string PFyNgJYorU;
      string dDzsYQbEgB;
      string DoFcthMAdL;
      string MwKItGkrgU;
      if(LXhIJFzPFa == ocmaWInaIJ){WLLHTxumKh = true;}
      else if(ocmaWInaIJ == LXhIJFzPFa){WUkVVDDBWz = true;}
      if(aITCWjkRsi == CJRJrCqZDj){cGtbOazVTy = true;}
      else if(CJRJrCqZDj == aITCWjkRsi){QmeuHuHKek = true;}
      if(ogJnsRqsqi == AiRLxEshbt){xXKgIhrpyS = true;}
      else if(AiRLxEshbt == ogJnsRqsqi){itqSgzDoec = true;}
      if(qOJdKTMdNP == crkcQWXnaK){fiWMdqcxJw = true;}
      else if(crkcQWXnaK == qOJdKTMdNP){mkSLfJXaII = true;}
      if(xrFDLmSedt == LjGNdwAEcy){mYowhFCisT = true;}
      else if(LjGNdwAEcy == xrFDLmSedt){NIRpNCSDPx = true;}
      if(PrEtGdOtPr == AtfjyFKbcS){GPYhWzBeyl = true;}
      else if(AtfjyFKbcS == PrEtGdOtPr){aZRJEcdSoW = true;}
      if(OFXViLyorD == PFyNgJYorU){EEnrBtigxW = true;}
      else if(PFyNgJYorU == OFXViLyorD){zNWsLeTTOx = true;}
      if(WHEclxbFbF == dDzsYQbEgB){xCMWLXhNzD = true;}
      if(zLOxSzKPXf == DoFcthMAdL){eJxdMQKope = true;}
      if(FSNVBqTiUz == MwKItGkrgU){pyyWrhjxtn = true;}
      while(dDzsYQbEgB == WHEclxbFbF){WfBVXabAEd = true;}
      while(DoFcthMAdL == DoFcthMAdL){gAZhCMTJHD = true;}
      while(MwKItGkrgU == MwKItGkrgU){fEllJzlXei = true;}
      if(WLLHTxumKh == true){WLLHTxumKh = false;}
      if(cGtbOazVTy == true){cGtbOazVTy = false;}
      if(xXKgIhrpyS == true){xXKgIhrpyS = false;}
      if(fiWMdqcxJw == true){fiWMdqcxJw = false;}
      if(mYowhFCisT == true){mYowhFCisT = false;}
      if(GPYhWzBeyl == true){GPYhWzBeyl = false;}
      if(EEnrBtigxW == true){EEnrBtigxW = false;}
      if(xCMWLXhNzD == true){xCMWLXhNzD = false;}
      if(eJxdMQKope == true){eJxdMQKope = false;}
      if(pyyWrhjxtn == true){pyyWrhjxtn = false;}
      if(WUkVVDDBWz == true){WUkVVDDBWz = false;}
      if(QmeuHuHKek == true){QmeuHuHKek = false;}
      if(itqSgzDoec == true){itqSgzDoec = false;}
      if(mkSLfJXaII == true){mkSLfJXaII = false;}
      if(NIRpNCSDPx == true){NIRpNCSDPx = false;}
      if(aZRJEcdSoW == true){aZRJEcdSoW = false;}
      if(zNWsLeTTOx == true){zNWsLeTTOx = false;}
      if(WfBVXabAEd == true){WfBVXabAEd = false;}
      if(gAZhCMTJHD == true){gAZhCMTJHD = false;}
      if(fEllJzlXei == true){fEllJzlXei = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YXDVCWSRJP
{ 
  void RdrHnEIgjx()
  { 
      bool krhddlqytM = false;
      bool jeURFlzzja = false;
      bool zXLOkPFIAt = false;
      bool aTIjkqfUjx = false;
      bool ZAORJQhYGg = false;
      bool lVtnNNfTrN = false;
      bool fhxzlPWjgO = false;
      bool FePmAyIsFU = false;
      bool gfCSIFZTWW = false;
      bool KMbVQrDPfs = false;
      bool sxrqbGGHnO = false;
      bool EmOXgzedqf = false;
      bool pDNJDrDsVI = false;
      bool usMMainKqB = false;
      bool yReHSXyDoR = false;
      bool MYXzCpjimi = false;
      bool DMkfTLZCxx = false;
      bool LTmpgXXGqf = false;
      bool tzEEuVUMJk = false;
      bool zEXHxlgznG = false;
      string bTGTiuyhVO;
      string IfQAwDEKTd;
      string cnczXUJKAJ;
      string EYzJPYVXHX;
      string zQRBXNnMAp;
      string kLTPhmqHwN;
      string lmgLJjgGkW;
      string hgDwdMWabK;
      string gxJKXrFibb;
      string hObslLiFqm;
      string ggadIEIWkU;
      string PPekgocWmQ;
      string dxdIoSEKKR;
      string cRinczVfBT;
      string jhyGLRipLw;
      string iLRaJiCRoo;
      string AyMTqyfqIh;
      string SxUTgwzXxW;
      string iOyNiQzIes;
      string wDqLSlUeOM;
      if(bTGTiuyhVO == ggadIEIWkU){krhddlqytM = true;}
      else if(ggadIEIWkU == bTGTiuyhVO){sxrqbGGHnO = true;}
      if(IfQAwDEKTd == PPekgocWmQ){jeURFlzzja = true;}
      else if(PPekgocWmQ == IfQAwDEKTd){EmOXgzedqf = true;}
      if(cnczXUJKAJ == dxdIoSEKKR){zXLOkPFIAt = true;}
      else if(dxdIoSEKKR == cnczXUJKAJ){pDNJDrDsVI = true;}
      if(EYzJPYVXHX == cRinczVfBT){aTIjkqfUjx = true;}
      else if(cRinczVfBT == EYzJPYVXHX){usMMainKqB = true;}
      if(zQRBXNnMAp == jhyGLRipLw){ZAORJQhYGg = true;}
      else if(jhyGLRipLw == zQRBXNnMAp){yReHSXyDoR = true;}
      if(kLTPhmqHwN == iLRaJiCRoo){lVtnNNfTrN = true;}
      else if(iLRaJiCRoo == kLTPhmqHwN){MYXzCpjimi = true;}
      if(lmgLJjgGkW == AyMTqyfqIh){fhxzlPWjgO = true;}
      else if(AyMTqyfqIh == lmgLJjgGkW){DMkfTLZCxx = true;}
      if(hgDwdMWabK == SxUTgwzXxW){FePmAyIsFU = true;}
      if(gxJKXrFibb == iOyNiQzIes){gfCSIFZTWW = true;}
      if(hObslLiFqm == wDqLSlUeOM){KMbVQrDPfs = true;}
      while(SxUTgwzXxW == hgDwdMWabK){LTmpgXXGqf = true;}
      while(iOyNiQzIes == iOyNiQzIes){tzEEuVUMJk = true;}
      while(wDqLSlUeOM == wDqLSlUeOM){zEXHxlgznG = true;}
      if(krhddlqytM == true){krhddlqytM = false;}
      if(jeURFlzzja == true){jeURFlzzja = false;}
      if(zXLOkPFIAt == true){zXLOkPFIAt = false;}
      if(aTIjkqfUjx == true){aTIjkqfUjx = false;}
      if(ZAORJQhYGg == true){ZAORJQhYGg = false;}
      if(lVtnNNfTrN == true){lVtnNNfTrN = false;}
      if(fhxzlPWjgO == true){fhxzlPWjgO = false;}
      if(FePmAyIsFU == true){FePmAyIsFU = false;}
      if(gfCSIFZTWW == true){gfCSIFZTWW = false;}
      if(KMbVQrDPfs == true){KMbVQrDPfs = false;}
      if(sxrqbGGHnO == true){sxrqbGGHnO = false;}
      if(EmOXgzedqf == true){EmOXgzedqf = false;}
      if(pDNJDrDsVI == true){pDNJDrDsVI = false;}
      if(usMMainKqB == true){usMMainKqB = false;}
      if(yReHSXyDoR == true){yReHSXyDoR = false;}
      if(MYXzCpjimi == true){MYXzCpjimi = false;}
      if(DMkfTLZCxx == true){DMkfTLZCxx = false;}
      if(LTmpgXXGqf == true){LTmpgXXGqf = false;}
      if(tzEEuVUMJk == true){tzEEuVUMJk = false;}
      if(zEXHxlgznG == true){zEXHxlgznG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TYLYDQKIMF
{ 
  void hekKzkZOTd()
  { 
      bool EsaBZWiWZo = false;
      bool IRmMxtWxjR = false;
      bool AahQjstCDY = false;
      bool aPBlUwhEKW = false;
      bool pmAxmNzngw = false;
      bool SmmdXdKJQg = false;
      bool cfSANsPAqB = false;
      bool MRlMaNakdW = false;
      bool sFVHGnbXOq = false;
      bool kXmdtJTzit = false;
      bool xzwejBAaCK = false;
      bool CZftmXKLsZ = false;
      bool QrlAPndIRQ = false;
      bool taBjYtIpXF = false;
      bool nAUDnLrspW = false;
      bool zHFJcFNwPu = false;
      bool WrJkPbYuUs = false;
      bool OTmnkQWhLE = false;
      bool ukRuRlUqHT = false;
      bool fLabiuqinL = false;
      string jFLZJlNpRa;
      string McMEVjQoiD;
      string fSFesBoYgj;
      string ZkwHmUFZlT;
      string pYlVIQFKSW;
      string pFpEmRzggH;
      string wnJgBafEQB;
      string dpDPNGfjWb;
      string weFKsTtrTU;
      string VYsdXBPEUh;
      string jAsRrABapg;
      string lPKELRizmg;
      string fnjueExYqM;
      string paOnqukmRs;
      string RTBmiFOnRG;
      string RQRnBuPylm;
      string DcidqKBVMQ;
      string fugtOMmxLZ;
      string oIGktZJZmw;
      string flBdpokWuY;
      if(jFLZJlNpRa == jAsRrABapg){EsaBZWiWZo = true;}
      else if(jAsRrABapg == jFLZJlNpRa){xzwejBAaCK = true;}
      if(McMEVjQoiD == lPKELRizmg){IRmMxtWxjR = true;}
      else if(lPKELRizmg == McMEVjQoiD){CZftmXKLsZ = true;}
      if(fSFesBoYgj == fnjueExYqM){AahQjstCDY = true;}
      else if(fnjueExYqM == fSFesBoYgj){QrlAPndIRQ = true;}
      if(ZkwHmUFZlT == paOnqukmRs){aPBlUwhEKW = true;}
      else if(paOnqukmRs == ZkwHmUFZlT){taBjYtIpXF = true;}
      if(pYlVIQFKSW == RTBmiFOnRG){pmAxmNzngw = true;}
      else if(RTBmiFOnRG == pYlVIQFKSW){nAUDnLrspW = true;}
      if(pFpEmRzggH == RQRnBuPylm){SmmdXdKJQg = true;}
      else if(RQRnBuPylm == pFpEmRzggH){zHFJcFNwPu = true;}
      if(wnJgBafEQB == DcidqKBVMQ){cfSANsPAqB = true;}
      else if(DcidqKBVMQ == wnJgBafEQB){WrJkPbYuUs = true;}
      if(dpDPNGfjWb == fugtOMmxLZ){MRlMaNakdW = true;}
      if(weFKsTtrTU == oIGktZJZmw){sFVHGnbXOq = true;}
      if(VYsdXBPEUh == flBdpokWuY){kXmdtJTzit = true;}
      while(fugtOMmxLZ == dpDPNGfjWb){OTmnkQWhLE = true;}
      while(oIGktZJZmw == oIGktZJZmw){ukRuRlUqHT = true;}
      while(flBdpokWuY == flBdpokWuY){fLabiuqinL = true;}
      if(EsaBZWiWZo == true){EsaBZWiWZo = false;}
      if(IRmMxtWxjR == true){IRmMxtWxjR = false;}
      if(AahQjstCDY == true){AahQjstCDY = false;}
      if(aPBlUwhEKW == true){aPBlUwhEKW = false;}
      if(pmAxmNzngw == true){pmAxmNzngw = false;}
      if(SmmdXdKJQg == true){SmmdXdKJQg = false;}
      if(cfSANsPAqB == true){cfSANsPAqB = false;}
      if(MRlMaNakdW == true){MRlMaNakdW = false;}
      if(sFVHGnbXOq == true){sFVHGnbXOq = false;}
      if(kXmdtJTzit == true){kXmdtJTzit = false;}
      if(xzwejBAaCK == true){xzwejBAaCK = false;}
      if(CZftmXKLsZ == true){CZftmXKLsZ = false;}
      if(QrlAPndIRQ == true){QrlAPndIRQ = false;}
      if(taBjYtIpXF == true){taBjYtIpXF = false;}
      if(nAUDnLrspW == true){nAUDnLrspW = false;}
      if(zHFJcFNwPu == true){zHFJcFNwPu = false;}
      if(WrJkPbYuUs == true){WrJkPbYuUs = false;}
      if(OTmnkQWhLE == true){OTmnkQWhLE = false;}
      if(ukRuRlUqHT == true){ukRuRlUqHT = false;}
      if(fLabiuqinL == true){fLabiuqinL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TQRVTXWLMS
{ 
  void kesUzQczAh()
  { 
      bool QMdFVGVgXH = false;
      bool mjEhqltieo = false;
      bool drksNXZBRC = false;
      bool FJDEbdUaay = false;
      bool aUcfKKcLXz = false;
      bool ESMMqYakqx = false;
      bool gUPVCdgAGN = false;
      bool RSIfNIPFhD = false;
      bool uNdRylxpMD = false;
      bool CijcRGFGdg = false;
      bool cbFJhkKfyh = false;
      bool JVCmCTpxXP = false;
      bool fqmCKhheOH = false;
      bool DIaBaSITjM = false;
      bool aQqdsggwax = false;
      bool QHiNAknCyA = false;
      bool CfQqeAtAMi = false;
      bool LVNKnPAJJd = false;
      bool AlDQqwZNBo = false;
      bool dFViJuzzzs = false;
      string jcjYdGsgwq;
      string kZYrrzteoy;
      string FNnurNXFMu;
      string WGESsPFdZZ;
      string DUNRknqGGE;
      string TaTLGVnogQ;
      string hnUBUdVGzc;
      string sPEPujAWKE;
      string VRyHaumrLX;
      string aQxJqPALxG;
      string RkGcKDVEQW;
      string URdctQoNaY;
      string qctbCcSuXf;
      string jnYElkLUwW;
      string YiboCJlUOa;
      string ZlkXPnpdah;
      string kafjmgrZpJ;
      string FTQDAHBFZr;
      string pygwFxCAnx;
      string ugtOlyCqCV;
      if(jcjYdGsgwq == RkGcKDVEQW){QMdFVGVgXH = true;}
      else if(RkGcKDVEQW == jcjYdGsgwq){cbFJhkKfyh = true;}
      if(kZYrrzteoy == URdctQoNaY){mjEhqltieo = true;}
      else if(URdctQoNaY == kZYrrzteoy){JVCmCTpxXP = true;}
      if(FNnurNXFMu == qctbCcSuXf){drksNXZBRC = true;}
      else if(qctbCcSuXf == FNnurNXFMu){fqmCKhheOH = true;}
      if(WGESsPFdZZ == jnYElkLUwW){FJDEbdUaay = true;}
      else if(jnYElkLUwW == WGESsPFdZZ){DIaBaSITjM = true;}
      if(DUNRknqGGE == YiboCJlUOa){aUcfKKcLXz = true;}
      else if(YiboCJlUOa == DUNRknqGGE){aQqdsggwax = true;}
      if(TaTLGVnogQ == ZlkXPnpdah){ESMMqYakqx = true;}
      else if(ZlkXPnpdah == TaTLGVnogQ){QHiNAknCyA = true;}
      if(hnUBUdVGzc == kafjmgrZpJ){gUPVCdgAGN = true;}
      else if(kafjmgrZpJ == hnUBUdVGzc){CfQqeAtAMi = true;}
      if(sPEPujAWKE == FTQDAHBFZr){RSIfNIPFhD = true;}
      if(VRyHaumrLX == pygwFxCAnx){uNdRylxpMD = true;}
      if(aQxJqPALxG == ugtOlyCqCV){CijcRGFGdg = true;}
      while(FTQDAHBFZr == sPEPujAWKE){LVNKnPAJJd = true;}
      while(pygwFxCAnx == pygwFxCAnx){AlDQqwZNBo = true;}
      while(ugtOlyCqCV == ugtOlyCqCV){dFViJuzzzs = true;}
      if(QMdFVGVgXH == true){QMdFVGVgXH = false;}
      if(mjEhqltieo == true){mjEhqltieo = false;}
      if(drksNXZBRC == true){drksNXZBRC = false;}
      if(FJDEbdUaay == true){FJDEbdUaay = false;}
      if(aUcfKKcLXz == true){aUcfKKcLXz = false;}
      if(ESMMqYakqx == true){ESMMqYakqx = false;}
      if(gUPVCdgAGN == true){gUPVCdgAGN = false;}
      if(RSIfNIPFhD == true){RSIfNIPFhD = false;}
      if(uNdRylxpMD == true){uNdRylxpMD = false;}
      if(CijcRGFGdg == true){CijcRGFGdg = false;}
      if(cbFJhkKfyh == true){cbFJhkKfyh = false;}
      if(JVCmCTpxXP == true){JVCmCTpxXP = false;}
      if(fqmCKhheOH == true){fqmCKhheOH = false;}
      if(DIaBaSITjM == true){DIaBaSITjM = false;}
      if(aQqdsggwax == true){aQqdsggwax = false;}
      if(QHiNAknCyA == true){QHiNAknCyA = false;}
      if(CfQqeAtAMi == true){CfQqeAtAMi = false;}
      if(LVNKnPAJJd == true){LVNKnPAJJd = false;}
      if(AlDQqwZNBo == true){AlDQqwZNBo = false;}
      if(dFViJuzzzs == true){dFViJuzzzs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDVGJHHLKD
{ 
  void KYXtTXyzYn()
  { 
      bool cPzbBaJeDf = false;
      bool kndKcTyGrM = false;
      bool RXcdbacmQE = false;
      bool PFwTfxDSuN = false;
      bool HjAqaZkPGk = false;
      bool GIfVFElUAa = false;
      bool yVOyPeqKef = false;
      bool QeLeFgXlDC = false;
      bool pMgfyHYZOa = false;
      bool KhSUOkVBau = false;
      bool hakaUaxBPX = false;
      bool fARxklnhAI = false;
      bool FQuDUhMqPT = false;
      bool LWKITOaGLW = false;
      bool JXJptKQUic = false;
      bool xmBSoQegFl = false;
      bool OGlwMJoIdV = false;
      bool KhWcyhGFJK = false;
      bool RqHlWYVqSC = false;
      bool jtBYIDlNdk = false;
      string JPDuCAyYln;
      string dlUNsIoIIz;
      string lxgWHlUWlA;
      string UPynOgfrFz;
      string DNiqajsQtu;
      string LLCtzLifmP;
      string fallSNmgyM;
      string cwDIuYNowW;
      string sDcqoINEnC;
      string yzEoTcaxXM;
      string xLRhSOIsza;
      string xsjPWbyuwK;
      string AirwNcrNoS;
      string xQRiZgktYa;
      string ATEMEEPoRr;
      string dfANMOTVTo;
      string VtEfdgbAop;
      string pDWVKfdeqI;
      string MCuxnQPDWL;
      string NPaiEFPXiW;
      if(JPDuCAyYln == xLRhSOIsza){cPzbBaJeDf = true;}
      else if(xLRhSOIsza == JPDuCAyYln){hakaUaxBPX = true;}
      if(dlUNsIoIIz == xsjPWbyuwK){kndKcTyGrM = true;}
      else if(xsjPWbyuwK == dlUNsIoIIz){fARxklnhAI = true;}
      if(lxgWHlUWlA == AirwNcrNoS){RXcdbacmQE = true;}
      else if(AirwNcrNoS == lxgWHlUWlA){FQuDUhMqPT = true;}
      if(UPynOgfrFz == xQRiZgktYa){PFwTfxDSuN = true;}
      else if(xQRiZgktYa == UPynOgfrFz){LWKITOaGLW = true;}
      if(DNiqajsQtu == ATEMEEPoRr){HjAqaZkPGk = true;}
      else if(ATEMEEPoRr == DNiqajsQtu){JXJptKQUic = true;}
      if(LLCtzLifmP == dfANMOTVTo){GIfVFElUAa = true;}
      else if(dfANMOTVTo == LLCtzLifmP){xmBSoQegFl = true;}
      if(fallSNmgyM == VtEfdgbAop){yVOyPeqKef = true;}
      else if(VtEfdgbAop == fallSNmgyM){OGlwMJoIdV = true;}
      if(cwDIuYNowW == pDWVKfdeqI){QeLeFgXlDC = true;}
      if(sDcqoINEnC == MCuxnQPDWL){pMgfyHYZOa = true;}
      if(yzEoTcaxXM == NPaiEFPXiW){KhSUOkVBau = true;}
      while(pDWVKfdeqI == cwDIuYNowW){KhWcyhGFJK = true;}
      while(MCuxnQPDWL == MCuxnQPDWL){RqHlWYVqSC = true;}
      while(NPaiEFPXiW == NPaiEFPXiW){jtBYIDlNdk = true;}
      if(cPzbBaJeDf == true){cPzbBaJeDf = false;}
      if(kndKcTyGrM == true){kndKcTyGrM = false;}
      if(RXcdbacmQE == true){RXcdbacmQE = false;}
      if(PFwTfxDSuN == true){PFwTfxDSuN = false;}
      if(HjAqaZkPGk == true){HjAqaZkPGk = false;}
      if(GIfVFElUAa == true){GIfVFElUAa = false;}
      if(yVOyPeqKef == true){yVOyPeqKef = false;}
      if(QeLeFgXlDC == true){QeLeFgXlDC = false;}
      if(pMgfyHYZOa == true){pMgfyHYZOa = false;}
      if(KhSUOkVBau == true){KhSUOkVBau = false;}
      if(hakaUaxBPX == true){hakaUaxBPX = false;}
      if(fARxklnhAI == true){fARxklnhAI = false;}
      if(FQuDUhMqPT == true){FQuDUhMqPT = false;}
      if(LWKITOaGLW == true){LWKITOaGLW = false;}
      if(JXJptKQUic == true){JXJptKQUic = false;}
      if(xmBSoQegFl == true){xmBSoQegFl = false;}
      if(OGlwMJoIdV == true){OGlwMJoIdV = false;}
      if(KhWcyhGFJK == true){KhWcyhGFJK = false;}
      if(RqHlWYVqSC == true){RqHlWYVqSC = false;}
      if(jtBYIDlNdk == true){jtBYIDlNdk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KJENSRUTRP
{ 
  void oZGSyHoUTA()
  { 
      bool NarcAVAwXV = false;
      bool hNIqflHyYi = false;
      bool EasiozdHXJ = false;
      bool egYRYIRGpf = false;
      bool SQKDHWMSzL = false;
      bool bLRZAlhInB = false;
      bool rsXOqAoqSW = false;
      bool TAIsPnQpbR = false;
      bool lLHMgTPyQm = false;
      bool aISonZrwMH = false;
      bool hVAcqbCXKM = false;
      bool UrfWOgkLgW = false;
      bool jpZfwLhTFo = false;
      bool uUcUjQLeUF = false;
      bool QrnERhcwZG = false;
      bool ofOoWquTff = false;
      bool siSUQAOKly = false;
      bool VGqaGrCVNN = false;
      bool hltyAPFnxr = false;
      bool UqynMhYTmR = false;
      string mJPwCxMjXT;
      string jkPrcSGogi;
      string SZJYkYFJMt;
      string nxnCfjowog;
      string mrLTmsChhW;
      string ffziiMApLd;
      string qCXdelwMLs;
      string cKzAwaOolr;
      string WWboOIyFTT;
      string iyjLojUhnA;
      string woWntUfzmI;
      string xKETHUahOW;
      string npsrKdZnKL;
      string FfAkugAmus;
      string byRLVXtQDU;
      string JmSRLFwedP;
      string urnbCRKSYZ;
      string UmlVtoXhVl;
      string jJjpCSMiZo;
      string kVJexjKpIE;
      if(mJPwCxMjXT == woWntUfzmI){NarcAVAwXV = true;}
      else if(woWntUfzmI == mJPwCxMjXT){hVAcqbCXKM = true;}
      if(jkPrcSGogi == xKETHUahOW){hNIqflHyYi = true;}
      else if(xKETHUahOW == jkPrcSGogi){UrfWOgkLgW = true;}
      if(SZJYkYFJMt == npsrKdZnKL){EasiozdHXJ = true;}
      else if(npsrKdZnKL == SZJYkYFJMt){jpZfwLhTFo = true;}
      if(nxnCfjowog == FfAkugAmus){egYRYIRGpf = true;}
      else if(FfAkugAmus == nxnCfjowog){uUcUjQLeUF = true;}
      if(mrLTmsChhW == byRLVXtQDU){SQKDHWMSzL = true;}
      else if(byRLVXtQDU == mrLTmsChhW){QrnERhcwZG = true;}
      if(ffziiMApLd == JmSRLFwedP){bLRZAlhInB = true;}
      else if(JmSRLFwedP == ffziiMApLd){ofOoWquTff = true;}
      if(qCXdelwMLs == urnbCRKSYZ){rsXOqAoqSW = true;}
      else if(urnbCRKSYZ == qCXdelwMLs){siSUQAOKly = true;}
      if(cKzAwaOolr == UmlVtoXhVl){TAIsPnQpbR = true;}
      if(WWboOIyFTT == jJjpCSMiZo){lLHMgTPyQm = true;}
      if(iyjLojUhnA == kVJexjKpIE){aISonZrwMH = true;}
      while(UmlVtoXhVl == cKzAwaOolr){VGqaGrCVNN = true;}
      while(jJjpCSMiZo == jJjpCSMiZo){hltyAPFnxr = true;}
      while(kVJexjKpIE == kVJexjKpIE){UqynMhYTmR = true;}
      if(NarcAVAwXV == true){NarcAVAwXV = false;}
      if(hNIqflHyYi == true){hNIqflHyYi = false;}
      if(EasiozdHXJ == true){EasiozdHXJ = false;}
      if(egYRYIRGpf == true){egYRYIRGpf = false;}
      if(SQKDHWMSzL == true){SQKDHWMSzL = false;}
      if(bLRZAlhInB == true){bLRZAlhInB = false;}
      if(rsXOqAoqSW == true){rsXOqAoqSW = false;}
      if(TAIsPnQpbR == true){TAIsPnQpbR = false;}
      if(lLHMgTPyQm == true){lLHMgTPyQm = false;}
      if(aISonZrwMH == true){aISonZrwMH = false;}
      if(hVAcqbCXKM == true){hVAcqbCXKM = false;}
      if(UrfWOgkLgW == true){UrfWOgkLgW = false;}
      if(jpZfwLhTFo == true){jpZfwLhTFo = false;}
      if(uUcUjQLeUF == true){uUcUjQLeUF = false;}
      if(QrnERhcwZG == true){QrnERhcwZG = false;}
      if(ofOoWquTff == true){ofOoWquTff = false;}
      if(siSUQAOKly == true){siSUQAOKly = false;}
      if(VGqaGrCVNN == true){VGqaGrCVNN = false;}
      if(hltyAPFnxr == true){hltyAPFnxr = false;}
      if(UqynMhYTmR == true){UqynMhYTmR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VITVTUFVKE
{ 
  void zMfQarXWUL()
  { 
      bool DYcSKKJhjE = false;
      bool BIxoXcFFmU = false;
      bool snJKfrDEsB = false;
      bool FDQGhicyGG = false;
      bool OpSFJItqpL = false;
      bool xbLuUOPSmS = false;
      bool HEniyyrpHo = false;
      bool zHzfFCUDAW = false;
      bool xLNhEdqUkS = false;
      bool SKLmzKCjHK = false;
      bool PDiBMocepR = false;
      bool sLRPUupGdT = false;
      bool HXFnVowLgt = false;
      bool AkwoGtcLUP = false;
      bool BLeSZGruRE = false;
      bool TuGmDrytfW = false;
      bool rQyuRIPbIa = false;
      bool RekOSurlOO = false;
      bool wAsbaFdIkN = false;
      bool uhfxWjMiBQ = false;
      string egPhwDkEZq;
      string DRbukiwLFr;
      string QKlGSGieSB;
      string iVnkHZVCJG;
      string sawaSpVGRs;
      string kFgRiTuIPo;
      string TFlXHhdqnK;
      string NtByzoNKmc;
      string kbNYQdnWCm;
      string eNmUlmoYSk;
      string LdSGeqDiRs;
      string GjUmErrMHd;
      string sHoAfAGgLM;
      string AorBQGIHsY;
      string ZFEIfurzPt;
      string ubQnrEoRZe;
      string jWWFrRrSVx;
      string ijShEnCfUk;
      string HGQRRXXDJL;
      string RqgOoChzPO;
      if(egPhwDkEZq == LdSGeqDiRs){DYcSKKJhjE = true;}
      else if(LdSGeqDiRs == egPhwDkEZq){PDiBMocepR = true;}
      if(DRbukiwLFr == GjUmErrMHd){BIxoXcFFmU = true;}
      else if(GjUmErrMHd == DRbukiwLFr){sLRPUupGdT = true;}
      if(QKlGSGieSB == sHoAfAGgLM){snJKfrDEsB = true;}
      else if(sHoAfAGgLM == QKlGSGieSB){HXFnVowLgt = true;}
      if(iVnkHZVCJG == AorBQGIHsY){FDQGhicyGG = true;}
      else if(AorBQGIHsY == iVnkHZVCJG){AkwoGtcLUP = true;}
      if(sawaSpVGRs == ZFEIfurzPt){OpSFJItqpL = true;}
      else if(ZFEIfurzPt == sawaSpVGRs){BLeSZGruRE = true;}
      if(kFgRiTuIPo == ubQnrEoRZe){xbLuUOPSmS = true;}
      else if(ubQnrEoRZe == kFgRiTuIPo){TuGmDrytfW = true;}
      if(TFlXHhdqnK == jWWFrRrSVx){HEniyyrpHo = true;}
      else if(jWWFrRrSVx == TFlXHhdqnK){rQyuRIPbIa = true;}
      if(NtByzoNKmc == ijShEnCfUk){zHzfFCUDAW = true;}
      if(kbNYQdnWCm == HGQRRXXDJL){xLNhEdqUkS = true;}
      if(eNmUlmoYSk == RqgOoChzPO){SKLmzKCjHK = true;}
      while(ijShEnCfUk == NtByzoNKmc){RekOSurlOO = true;}
      while(HGQRRXXDJL == HGQRRXXDJL){wAsbaFdIkN = true;}
      while(RqgOoChzPO == RqgOoChzPO){uhfxWjMiBQ = true;}
      if(DYcSKKJhjE == true){DYcSKKJhjE = false;}
      if(BIxoXcFFmU == true){BIxoXcFFmU = false;}
      if(snJKfrDEsB == true){snJKfrDEsB = false;}
      if(FDQGhicyGG == true){FDQGhicyGG = false;}
      if(OpSFJItqpL == true){OpSFJItqpL = false;}
      if(xbLuUOPSmS == true){xbLuUOPSmS = false;}
      if(HEniyyrpHo == true){HEniyyrpHo = false;}
      if(zHzfFCUDAW == true){zHzfFCUDAW = false;}
      if(xLNhEdqUkS == true){xLNhEdqUkS = false;}
      if(SKLmzKCjHK == true){SKLmzKCjHK = false;}
      if(PDiBMocepR == true){PDiBMocepR = false;}
      if(sLRPUupGdT == true){sLRPUupGdT = false;}
      if(HXFnVowLgt == true){HXFnVowLgt = false;}
      if(AkwoGtcLUP == true){AkwoGtcLUP = false;}
      if(BLeSZGruRE == true){BLeSZGruRE = false;}
      if(TuGmDrytfW == true){TuGmDrytfW = false;}
      if(rQyuRIPbIa == true){rQyuRIPbIa = false;}
      if(RekOSurlOO == true){RekOSurlOO = false;}
      if(wAsbaFdIkN == true){wAsbaFdIkN = false;}
      if(uhfxWjMiBQ == true){uhfxWjMiBQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UCOWJEIXRU
{ 
  void hWhRglSlWm()
  { 
      bool qKbblLdMBA = false;
      bool nYmXKNjdBS = false;
      bool ceOaEfPsRK = false;
      bool PbmZPAosYD = false;
      bool RzxNeAeYYs = false;
      bool MgVrfLuBWG = false;
      bool wjuqjMlMHJ = false;
      bool YqEyAcgBuE = false;
      bool BpUYxiGttD = false;
      bool FnWSGgEFdS = false;
      bool NRQOUVbWqC = false;
      bool etFREGPVsA = false;
      bool GqSEDkTlrS = false;
      bool YaXcqiYFEb = false;
      bool GiDqYKhENz = false;
      bool RhMcMVyMKi = false;
      bool BpeXcDWcaV = false;
      bool hJRRtWnaes = false;
      bool CPXrApOtQU = false;
      bool kLtUZQDeNV = false;
      string zLXuQxmENd;
      string JkEtCVkJWe;
      string hNxLDyRSyt;
      string esAsYUQTzC;
      string esRTSPGZlY;
      string lrGFDkOLrS;
      string eTGTyPkLVg;
      string EQJTznwcsm;
      string qrfYHmmuom;
      string GFbgXLmxUD;
      string etEFUUilFP;
      string nlREalmgLL;
      string boWhayobwn;
      string ByIoIwnaEm;
      string DAoYzUmXGk;
      string XFlJaoWVdV;
      string fGoRNpdcud;
      string yLbYHaAyiG;
      string LRVLPuMyNT;
      string YRwiGxKXKI;
      if(zLXuQxmENd == etEFUUilFP){qKbblLdMBA = true;}
      else if(etEFUUilFP == zLXuQxmENd){NRQOUVbWqC = true;}
      if(JkEtCVkJWe == nlREalmgLL){nYmXKNjdBS = true;}
      else if(nlREalmgLL == JkEtCVkJWe){etFREGPVsA = true;}
      if(hNxLDyRSyt == boWhayobwn){ceOaEfPsRK = true;}
      else if(boWhayobwn == hNxLDyRSyt){GqSEDkTlrS = true;}
      if(esAsYUQTzC == ByIoIwnaEm){PbmZPAosYD = true;}
      else if(ByIoIwnaEm == esAsYUQTzC){YaXcqiYFEb = true;}
      if(esRTSPGZlY == DAoYzUmXGk){RzxNeAeYYs = true;}
      else if(DAoYzUmXGk == esRTSPGZlY){GiDqYKhENz = true;}
      if(lrGFDkOLrS == XFlJaoWVdV){MgVrfLuBWG = true;}
      else if(XFlJaoWVdV == lrGFDkOLrS){RhMcMVyMKi = true;}
      if(eTGTyPkLVg == fGoRNpdcud){wjuqjMlMHJ = true;}
      else if(fGoRNpdcud == eTGTyPkLVg){BpeXcDWcaV = true;}
      if(EQJTznwcsm == yLbYHaAyiG){YqEyAcgBuE = true;}
      if(qrfYHmmuom == LRVLPuMyNT){BpUYxiGttD = true;}
      if(GFbgXLmxUD == YRwiGxKXKI){FnWSGgEFdS = true;}
      while(yLbYHaAyiG == EQJTznwcsm){hJRRtWnaes = true;}
      while(LRVLPuMyNT == LRVLPuMyNT){CPXrApOtQU = true;}
      while(YRwiGxKXKI == YRwiGxKXKI){kLtUZQDeNV = true;}
      if(qKbblLdMBA == true){qKbblLdMBA = false;}
      if(nYmXKNjdBS == true){nYmXKNjdBS = false;}
      if(ceOaEfPsRK == true){ceOaEfPsRK = false;}
      if(PbmZPAosYD == true){PbmZPAosYD = false;}
      if(RzxNeAeYYs == true){RzxNeAeYYs = false;}
      if(MgVrfLuBWG == true){MgVrfLuBWG = false;}
      if(wjuqjMlMHJ == true){wjuqjMlMHJ = false;}
      if(YqEyAcgBuE == true){YqEyAcgBuE = false;}
      if(BpUYxiGttD == true){BpUYxiGttD = false;}
      if(FnWSGgEFdS == true){FnWSGgEFdS = false;}
      if(NRQOUVbWqC == true){NRQOUVbWqC = false;}
      if(etFREGPVsA == true){etFREGPVsA = false;}
      if(GqSEDkTlrS == true){GqSEDkTlrS = false;}
      if(YaXcqiYFEb == true){YaXcqiYFEb = false;}
      if(GiDqYKhENz == true){GiDqYKhENz = false;}
      if(RhMcMVyMKi == true){RhMcMVyMKi = false;}
      if(BpeXcDWcaV == true){BpeXcDWcaV = false;}
      if(hJRRtWnaes == true){hJRRtWnaes = false;}
      if(CPXrApOtQU == true){CPXrApOtQU = false;}
      if(kLtUZQDeNV == true){kLtUZQDeNV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VIBPGKTBOO
{ 
  void jGabIKGTEg()
  { 
      bool AmGhDltPLo = false;
      bool dWqYyqWhIo = false;
      bool LAUDDQcLBG = false;
      bool WItwsqWsxQ = false;
      bool CSZggxZKFq = false;
      bool aaPmDARDdl = false;
      bool IiNESUbufH = false;
      bool UdkrmsanWF = false;
      bool pSFKewsGrs = false;
      bool YTOLHTEUOL = false;
      bool UeeyWxoXAJ = false;
      bool ZdgYupcCZV = false;
      bool bVDliAOYjS = false;
      bool oFZKkLmGnh = false;
      bool GVGhTtmpPQ = false;
      bool pBtrizbsPV = false;
      bool iQmgUTEVmj = false;
      bool DVOrPGOUSn = false;
      bool MYJTbmKhbk = false;
      bool jtqSyphYNA = false;
      string WeoiIafrGN;
      string FzKupIyBUI;
      string hWUTwZcJcu;
      string hRiOmjjsbp;
      string nVzyhtchFK;
      string XFBjGzJVmi;
      string yVOLenQwIG;
      string XEZeUMWVlB;
      string wtDSWcPyIm;
      string ZOGrqRGnTt;
      string dgYzlTfWOs;
      string cnillERwnC;
      string YRmVfJygmC;
      string GhCrWOUDgD;
      string xrjPJleUFl;
      string AJAQVLtDTc;
      string UyiLltkqOX;
      string iNPjFfhXLt;
      string dcaBCwhkWK;
      string URjEhyIYcP;
      if(WeoiIafrGN == dgYzlTfWOs){AmGhDltPLo = true;}
      else if(dgYzlTfWOs == WeoiIafrGN){UeeyWxoXAJ = true;}
      if(FzKupIyBUI == cnillERwnC){dWqYyqWhIo = true;}
      else if(cnillERwnC == FzKupIyBUI){ZdgYupcCZV = true;}
      if(hWUTwZcJcu == YRmVfJygmC){LAUDDQcLBG = true;}
      else if(YRmVfJygmC == hWUTwZcJcu){bVDliAOYjS = true;}
      if(hRiOmjjsbp == GhCrWOUDgD){WItwsqWsxQ = true;}
      else if(GhCrWOUDgD == hRiOmjjsbp){oFZKkLmGnh = true;}
      if(nVzyhtchFK == xrjPJleUFl){CSZggxZKFq = true;}
      else if(xrjPJleUFl == nVzyhtchFK){GVGhTtmpPQ = true;}
      if(XFBjGzJVmi == AJAQVLtDTc){aaPmDARDdl = true;}
      else if(AJAQVLtDTc == XFBjGzJVmi){pBtrizbsPV = true;}
      if(yVOLenQwIG == UyiLltkqOX){IiNESUbufH = true;}
      else if(UyiLltkqOX == yVOLenQwIG){iQmgUTEVmj = true;}
      if(XEZeUMWVlB == iNPjFfhXLt){UdkrmsanWF = true;}
      if(wtDSWcPyIm == dcaBCwhkWK){pSFKewsGrs = true;}
      if(ZOGrqRGnTt == URjEhyIYcP){YTOLHTEUOL = true;}
      while(iNPjFfhXLt == XEZeUMWVlB){DVOrPGOUSn = true;}
      while(dcaBCwhkWK == dcaBCwhkWK){MYJTbmKhbk = true;}
      while(URjEhyIYcP == URjEhyIYcP){jtqSyphYNA = true;}
      if(AmGhDltPLo == true){AmGhDltPLo = false;}
      if(dWqYyqWhIo == true){dWqYyqWhIo = false;}
      if(LAUDDQcLBG == true){LAUDDQcLBG = false;}
      if(WItwsqWsxQ == true){WItwsqWsxQ = false;}
      if(CSZggxZKFq == true){CSZggxZKFq = false;}
      if(aaPmDARDdl == true){aaPmDARDdl = false;}
      if(IiNESUbufH == true){IiNESUbufH = false;}
      if(UdkrmsanWF == true){UdkrmsanWF = false;}
      if(pSFKewsGrs == true){pSFKewsGrs = false;}
      if(YTOLHTEUOL == true){YTOLHTEUOL = false;}
      if(UeeyWxoXAJ == true){UeeyWxoXAJ = false;}
      if(ZdgYupcCZV == true){ZdgYupcCZV = false;}
      if(bVDliAOYjS == true){bVDliAOYjS = false;}
      if(oFZKkLmGnh == true){oFZKkLmGnh = false;}
      if(GVGhTtmpPQ == true){GVGhTtmpPQ = false;}
      if(pBtrizbsPV == true){pBtrizbsPV = false;}
      if(iQmgUTEVmj == true){iQmgUTEVmj = false;}
      if(DVOrPGOUSn == true){DVOrPGOUSn = false;}
      if(MYJTbmKhbk == true){MYJTbmKhbk = false;}
      if(jtqSyphYNA == true){jtqSyphYNA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSTJHTZYCU
{ 
  void tkTeouoohq()
  { 
      bool cpgJaLAbbP = false;
      bool GDlziagynC = false;
      bool nzZtfhaZab = false;
      bool PjCMnCPUGx = false;
      bool DNCFSKUDMA = false;
      bool LJpEFcQlcs = false;
      bool kZAAzVAZLf = false;
      bool LLrpyaxTbU = false;
      bool MXNaPFtxHK = false;
      bool lcrNLdMCFx = false;
      bool KuqfnARzGe = false;
      bool fwKIfNMZjt = false;
      bool bDSAtiTedU = false;
      bool NuOdKRfhlP = false;
      bool mtpbdoRjgy = false;
      bool RmRKVGbpkF = false;
      bool fmVlQkhfxO = false;
      bool hdmUGgMpVF = false;
      bool QjxfDZdDID = false;
      bool oowfiAYELs = false;
      string DIFzzylcej;
      string kQsNHTzQYX;
      string kFBqeRliDG;
      string HECXRVBkHS;
      string nqEBhYFQaY;
      string kFkebxHNUg;
      string LDZXcgNUwl;
      string ROJFisAAJF;
      string LUHeVBTXwT;
      string NnQZHkRgXB;
      string LkUnGVweuh;
      string xGDOVpwtCa;
      string MpXbXdyiyy;
      string bTbItaASXz;
      string FobNWHkBEQ;
      string oWdxnUMrQb;
      string XMfxGcdtTt;
      string pcWCUXOJFQ;
      string swegJEoeUY;
      string NHCwbsIdHs;
      if(DIFzzylcej == LkUnGVweuh){cpgJaLAbbP = true;}
      else if(LkUnGVweuh == DIFzzylcej){KuqfnARzGe = true;}
      if(kQsNHTzQYX == xGDOVpwtCa){GDlziagynC = true;}
      else if(xGDOVpwtCa == kQsNHTzQYX){fwKIfNMZjt = true;}
      if(kFBqeRliDG == MpXbXdyiyy){nzZtfhaZab = true;}
      else if(MpXbXdyiyy == kFBqeRliDG){bDSAtiTedU = true;}
      if(HECXRVBkHS == bTbItaASXz){PjCMnCPUGx = true;}
      else if(bTbItaASXz == HECXRVBkHS){NuOdKRfhlP = true;}
      if(nqEBhYFQaY == FobNWHkBEQ){DNCFSKUDMA = true;}
      else if(FobNWHkBEQ == nqEBhYFQaY){mtpbdoRjgy = true;}
      if(kFkebxHNUg == oWdxnUMrQb){LJpEFcQlcs = true;}
      else if(oWdxnUMrQb == kFkebxHNUg){RmRKVGbpkF = true;}
      if(LDZXcgNUwl == XMfxGcdtTt){kZAAzVAZLf = true;}
      else if(XMfxGcdtTt == LDZXcgNUwl){fmVlQkhfxO = true;}
      if(ROJFisAAJF == pcWCUXOJFQ){LLrpyaxTbU = true;}
      if(LUHeVBTXwT == swegJEoeUY){MXNaPFtxHK = true;}
      if(NnQZHkRgXB == NHCwbsIdHs){lcrNLdMCFx = true;}
      while(pcWCUXOJFQ == ROJFisAAJF){hdmUGgMpVF = true;}
      while(swegJEoeUY == swegJEoeUY){QjxfDZdDID = true;}
      while(NHCwbsIdHs == NHCwbsIdHs){oowfiAYELs = true;}
      if(cpgJaLAbbP == true){cpgJaLAbbP = false;}
      if(GDlziagynC == true){GDlziagynC = false;}
      if(nzZtfhaZab == true){nzZtfhaZab = false;}
      if(PjCMnCPUGx == true){PjCMnCPUGx = false;}
      if(DNCFSKUDMA == true){DNCFSKUDMA = false;}
      if(LJpEFcQlcs == true){LJpEFcQlcs = false;}
      if(kZAAzVAZLf == true){kZAAzVAZLf = false;}
      if(LLrpyaxTbU == true){LLrpyaxTbU = false;}
      if(MXNaPFtxHK == true){MXNaPFtxHK = false;}
      if(lcrNLdMCFx == true){lcrNLdMCFx = false;}
      if(KuqfnARzGe == true){KuqfnARzGe = false;}
      if(fwKIfNMZjt == true){fwKIfNMZjt = false;}
      if(bDSAtiTedU == true){bDSAtiTedU = false;}
      if(NuOdKRfhlP == true){NuOdKRfhlP = false;}
      if(mtpbdoRjgy == true){mtpbdoRjgy = false;}
      if(RmRKVGbpkF == true){RmRKVGbpkF = false;}
      if(fmVlQkhfxO == true){fmVlQkhfxO = false;}
      if(hdmUGgMpVF == true){hdmUGgMpVF = false;}
      if(QjxfDZdDID == true){QjxfDZdDID = false;}
      if(oowfiAYELs == true){oowfiAYELs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RMENREODDM
{ 
  void tYQVYANLGY()
  { 
      bool sFuCHDOABz = false;
      bool CCdflPcPwl = false;
      bool WffWqMKdKr = false;
      bool ZORhJTfSbH = false;
      bool QDoHWVzMne = false;
      bool yKcYBMYYLt = false;
      bool rkpJYnjuWR = false;
      bool iKmnVTqYzU = false;
      bool MypftPksgx = false;
      bool uHHhPfNfhh = false;
      bool lEoVunWoCh = false;
      bool UAZphtuJOJ = false;
      bool CpOZWbCEYp = false;
      bool GKpQiIITjF = false;
      bool rwpybtgQAU = false;
      bool jDQXeuoOyT = false;
      bool lRPMbKKIHY = false;
      bool kaZJRGAPyc = false;
      bool tkEDFCsRkn = false;
      bool TtUQTZfdWQ = false;
      string ESuEnqJAfc;
      string zOOZmFRSqA;
      string VGCbQdjAul;
      string VVlPiRDruI;
      string uOtXAnlgWe;
      string kJPeWxPTnK;
      string HIFtHdczqU;
      string BYXiEGLdbb;
      string qDdPAMFHsk;
      string CjEkBlIAQW;
      string LmpBcMkgZP;
      string lkrMSDepsu;
      string XUGFSRUmgS;
      string xKNFPENblm;
      string aYgczQrrRx;
      string GSGVypfjiL;
      string ryzHRaXmwO;
      string pDEFUzndGC;
      string ZbVjLeEqGZ;
      string XcsZubZZLX;
      if(ESuEnqJAfc == LmpBcMkgZP){sFuCHDOABz = true;}
      else if(LmpBcMkgZP == ESuEnqJAfc){lEoVunWoCh = true;}
      if(zOOZmFRSqA == lkrMSDepsu){CCdflPcPwl = true;}
      else if(lkrMSDepsu == zOOZmFRSqA){UAZphtuJOJ = true;}
      if(VGCbQdjAul == XUGFSRUmgS){WffWqMKdKr = true;}
      else if(XUGFSRUmgS == VGCbQdjAul){CpOZWbCEYp = true;}
      if(VVlPiRDruI == xKNFPENblm){ZORhJTfSbH = true;}
      else if(xKNFPENblm == VVlPiRDruI){GKpQiIITjF = true;}
      if(uOtXAnlgWe == aYgczQrrRx){QDoHWVzMne = true;}
      else if(aYgczQrrRx == uOtXAnlgWe){rwpybtgQAU = true;}
      if(kJPeWxPTnK == GSGVypfjiL){yKcYBMYYLt = true;}
      else if(GSGVypfjiL == kJPeWxPTnK){jDQXeuoOyT = true;}
      if(HIFtHdczqU == ryzHRaXmwO){rkpJYnjuWR = true;}
      else if(ryzHRaXmwO == HIFtHdczqU){lRPMbKKIHY = true;}
      if(BYXiEGLdbb == pDEFUzndGC){iKmnVTqYzU = true;}
      if(qDdPAMFHsk == ZbVjLeEqGZ){MypftPksgx = true;}
      if(CjEkBlIAQW == XcsZubZZLX){uHHhPfNfhh = true;}
      while(pDEFUzndGC == BYXiEGLdbb){kaZJRGAPyc = true;}
      while(ZbVjLeEqGZ == ZbVjLeEqGZ){tkEDFCsRkn = true;}
      while(XcsZubZZLX == XcsZubZZLX){TtUQTZfdWQ = true;}
      if(sFuCHDOABz == true){sFuCHDOABz = false;}
      if(CCdflPcPwl == true){CCdflPcPwl = false;}
      if(WffWqMKdKr == true){WffWqMKdKr = false;}
      if(ZORhJTfSbH == true){ZORhJTfSbH = false;}
      if(QDoHWVzMne == true){QDoHWVzMne = false;}
      if(yKcYBMYYLt == true){yKcYBMYYLt = false;}
      if(rkpJYnjuWR == true){rkpJYnjuWR = false;}
      if(iKmnVTqYzU == true){iKmnVTqYzU = false;}
      if(MypftPksgx == true){MypftPksgx = false;}
      if(uHHhPfNfhh == true){uHHhPfNfhh = false;}
      if(lEoVunWoCh == true){lEoVunWoCh = false;}
      if(UAZphtuJOJ == true){UAZphtuJOJ = false;}
      if(CpOZWbCEYp == true){CpOZWbCEYp = false;}
      if(GKpQiIITjF == true){GKpQiIITjF = false;}
      if(rwpybtgQAU == true){rwpybtgQAU = false;}
      if(jDQXeuoOyT == true){jDQXeuoOyT = false;}
      if(lRPMbKKIHY == true){lRPMbKKIHY = false;}
      if(kaZJRGAPyc == true){kaZJRGAPyc = false;}
      if(tkEDFCsRkn == true){tkEDFCsRkn = false;}
      if(TtUQTZfdWQ == true){TtUQTZfdWQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TWEVQWGVCV
{ 
  void lOuLImkZUQ()
  { 
      bool JIEICKKVdq = false;
      bool gbGujSEYcd = false;
      bool HEFQDONSxY = false;
      bool zVYBEgKgTi = false;
      bool XEpKpFoKoe = false;
      bool hUsJrEDnFm = false;
      bool wrYErLDEpC = false;
      bool IXEtFDOtay = false;
      bool YCdRqdbPJz = false;
      bool dWbflfekSe = false;
      bool CkTlWJQyDo = false;
      bool pINGOtOGNN = false;
      bool inuqXkwXIZ = false;
      bool Xcauuniqug = false;
      bool NdLTJUJURr = false;
      bool QXXEuOpcOk = false;
      bool NrpdQMgRKZ = false;
      bool KXLgAFbagC = false;
      bool baGPIAFWAg = false;
      bool yFcJSVmhCw = false;
      string jCmaTtkAxj;
      string QmwHxiETzx;
      string wadhknhidz;
      string dLQgPmQSgn;
      string NPqmZfQjPz;
      string bRpcfIXEoe;
      string MBVyFEWOqK;
      string SllLifjqIF;
      string XxTeWMUmBG;
      string OMcBbLsrhU;
      string IBsEfpeetA;
      string YgujHOhpbs;
      string ijNjuGIjiW;
      string lqInwVEOyf;
      string gprBhhQstM;
      string dCQokYnIIZ;
      string htuWNhXHnk;
      string KSruLsqMCN;
      string pOpWsiZTCX;
      string huFYyltVmA;
      if(jCmaTtkAxj == IBsEfpeetA){JIEICKKVdq = true;}
      else if(IBsEfpeetA == jCmaTtkAxj){CkTlWJQyDo = true;}
      if(QmwHxiETzx == YgujHOhpbs){gbGujSEYcd = true;}
      else if(YgujHOhpbs == QmwHxiETzx){pINGOtOGNN = true;}
      if(wadhknhidz == ijNjuGIjiW){HEFQDONSxY = true;}
      else if(ijNjuGIjiW == wadhknhidz){inuqXkwXIZ = true;}
      if(dLQgPmQSgn == lqInwVEOyf){zVYBEgKgTi = true;}
      else if(lqInwVEOyf == dLQgPmQSgn){Xcauuniqug = true;}
      if(NPqmZfQjPz == gprBhhQstM){XEpKpFoKoe = true;}
      else if(gprBhhQstM == NPqmZfQjPz){NdLTJUJURr = true;}
      if(bRpcfIXEoe == dCQokYnIIZ){hUsJrEDnFm = true;}
      else if(dCQokYnIIZ == bRpcfIXEoe){QXXEuOpcOk = true;}
      if(MBVyFEWOqK == htuWNhXHnk){wrYErLDEpC = true;}
      else if(htuWNhXHnk == MBVyFEWOqK){NrpdQMgRKZ = true;}
      if(SllLifjqIF == KSruLsqMCN){IXEtFDOtay = true;}
      if(XxTeWMUmBG == pOpWsiZTCX){YCdRqdbPJz = true;}
      if(OMcBbLsrhU == huFYyltVmA){dWbflfekSe = true;}
      while(KSruLsqMCN == SllLifjqIF){KXLgAFbagC = true;}
      while(pOpWsiZTCX == pOpWsiZTCX){baGPIAFWAg = true;}
      while(huFYyltVmA == huFYyltVmA){yFcJSVmhCw = true;}
      if(JIEICKKVdq == true){JIEICKKVdq = false;}
      if(gbGujSEYcd == true){gbGujSEYcd = false;}
      if(HEFQDONSxY == true){HEFQDONSxY = false;}
      if(zVYBEgKgTi == true){zVYBEgKgTi = false;}
      if(XEpKpFoKoe == true){XEpKpFoKoe = false;}
      if(hUsJrEDnFm == true){hUsJrEDnFm = false;}
      if(wrYErLDEpC == true){wrYErLDEpC = false;}
      if(IXEtFDOtay == true){IXEtFDOtay = false;}
      if(YCdRqdbPJz == true){YCdRqdbPJz = false;}
      if(dWbflfekSe == true){dWbflfekSe = false;}
      if(CkTlWJQyDo == true){CkTlWJQyDo = false;}
      if(pINGOtOGNN == true){pINGOtOGNN = false;}
      if(inuqXkwXIZ == true){inuqXkwXIZ = false;}
      if(Xcauuniqug == true){Xcauuniqug = false;}
      if(NdLTJUJURr == true){NdLTJUJURr = false;}
      if(QXXEuOpcOk == true){QXXEuOpcOk = false;}
      if(NrpdQMgRKZ == true){NrpdQMgRKZ = false;}
      if(KXLgAFbagC == true){KXLgAFbagC = false;}
      if(baGPIAFWAg == true){baGPIAFWAg = false;}
      if(yFcJSVmhCw == true){yFcJSVmhCw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JIWFRHPXVN
{ 
  void EjoXORIHgY()
  { 
      bool taDPNQKQcG = false;
      bool UFtljslhJz = false;
      bool kdAOUtIHiG = false;
      bool UyfdLFEUxD = false;
      bool zWeziHHytw = false;
      bool aLlfsQZotT = false;
      bool ICgWkVYQZd = false;
      bool oRkFzOyAfN = false;
      bool lJNleIMAjt = false;
      bool ePZduwoIOM = false;
      bool hqYPHIaffd = false;
      bool SZIggyouqb = false;
      bool JYfeyZrGKC = false;
      bool ZolSfukxeW = false;
      bool hfUFbFGsww = false;
      bool HtQlDIKsQh = false;
      bool QTVcEcmpAk = false;
      bool NqPUtcEaDs = false;
      bool SyKNufYAPW = false;
      bool krgxFOJqBy = false;
      string MEHXnZlpbp;
      string NGHFmZbXWZ;
      string NcEbmZCEjn;
      string tGDAnYuqal;
      string NgtxdkagtJ;
      string PDBUwizekN;
      string XgFnuHCGQN;
      string djwkLghHxB;
      string zVKZXqEiEE;
      string ZPGMNgaFBW;
      string iTPgefGQIP;
      string BrhjOCWfQE;
      string CTBMnOdiWe;
      string FbFaRfFctq;
      string knZoDghVyK;
      string JuoxUORDrQ;
      string BWtdJYlGRi;
      string wskYTOtMIG;
      string gIjLUJmIGD;
      string NCkdpNsufe;
      if(MEHXnZlpbp == iTPgefGQIP){taDPNQKQcG = true;}
      else if(iTPgefGQIP == MEHXnZlpbp){hqYPHIaffd = true;}
      if(NGHFmZbXWZ == BrhjOCWfQE){UFtljslhJz = true;}
      else if(BrhjOCWfQE == NGHFmZbXWZ){SZIggyouqb = true;}
      if(NcEbmZCEjn == CTBMnOdiWe){kdAOUtIHiG = true;}
      else if(CTBMnOdiWe == NcEbmZCEjn){JYfeyZrGKC = true;}
      if(tGDAnYuqal == FbFaRfFctq){UyfdLFEUxD = true;}
      else if(FbFaRfFctq == tGDAnYuqal){ZolSfukxeW = true;}
      if(NgtxdkagtJ == knZoDghVyK){zWeziHHytw = true;}
      else if(knZoDghVyK == NgtxdkagtJ){hfUFbFGsww = true;}
      if(PDBUwizekN == JuoxUORDrQ){aLlfsQZotT = true;}
      else if(JuoxUORDrQ == PDBUwizekN){HtQlDIKsQh = true;}
      if(XgFnuHCGQN == BWtdJYlGRi){ICgWkVYQZd = true;}
      else if(BWtdJYlGRi == XgFnuHCGQN){QTVcEcmpAk = true;}
      if(djwkLghHxB == wskYTOtMIG){oRkFzOyAfN = true;}
      if(zVKZXqEiEE == gIjLUJmIGD){lJNleIMAjt = true;}
      if(ZPGMNgaFBW == NCkdpNsufe){ePZduwoIOM = true;}
      while(wskYTOtMIG == djwkLghHxB){NqPUtcEaDs = true;}
      while(gIjLUJmIGD == gIjLUJmIGD){SyKNufYAPW = true;}
      while(NCkdpNsufe == NCkdpNsufe){krgxFOJqBy = true;}
      if(taDPNQKQcG == true){taDPNQKQcG = false;}
      if(UFtljslhJz == true){UFtljslhJz = false;}
      if(kdAOUtIHiG == true){kdAOUtIHiG = false;}
      if(UyfdLFEUxD == true){UyfdLFEUxD = false;}
      if(zWeziHHytw == true){zWeziHHytw = false;}
      if(aLlfsQZotT == true){aLlfsQZotT = false;}
      if(ICgWkVYQZd == true){ICgWkVYQZd = false;}
      if(oRkFzOyAfN == true){oRkFzOyAfN = false;}
      if(lJNleIMAjt == true){lJNleIMAjt = false;}
      if(ePZduwoIOM == true){ePZduwoIOM = false;}
      if(hqYPHIaffd == true){hqYPHIaffd = false;}
      if(SZIggyouqb == true){SZIggyouqb = false;}
      if(JYfeyZrGKC == true){JYfeyZrGKC = false;}
      if(ZolSfukxeW == true){ZolSfukxeW = false;}
      if(hfUFbFGsww == true){hfUFbFGsww = false;}
      if(HtQlDIKsQh == true){HtQlDIKsQh = false;}
      if(QTVcEcmpAk == true){QTVcEcmpAk = false;}
      if(NqPUtcEaDs == true){NqPUtcEaDs = false;}
      if(SyKNufYAPW == true){SyKNufYAPW = false;}
      if(krgxFOJqBy == true){krgxFOJqBy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BUBRUUMXCC
{ 
  void AqqbOAHnHU()
  { 
      bool AuKJmOYuQW = false;
      bool RBETTezlHD = false;
      bool oaCnolpTTQ = false;
      bool wdIgQnsJsz = false;
      bool ANpiypWRJn = false;
      bool VwfVjZsWTB = false;
      bool XEazansWCe = false;
      bool losHDbjSpz = false;
      bool OYKftzylxp = false;
      bool tWorbwlpIJ = false;
      bool wAOdCfDXSI = false;
      bool pagTlysuFa = false;
      bool pHYLkOAAfG = false;
      bool osJfCOKgcO = false;
      bool wZSoATpUFc = false;
      bool CpkhToaCsm = false;
      bool fCqMSwQARX = false;
      bool nMSpdPnjKQ = false;
      bool YeuDEyHbLN = false;
      bool mHnpisiGVE = false;
      string IWPVpoUdsi;
      string VAJYYnGOLh;
      string uuwHPiNQbt;
      string xmuuczdWGc;
      string qBaMQLkkJC;
      string mijOSMZHGG;
      string bECzliEOuY;
      string KjIiptUipE;
      string ybGYHNCfbQ;
      string YVQzBmzbZh;
      string GVpkrDaBYY;
      string rpQBIzxcrX;
      string fXleznSJhD;
      string usIIxblVfD;
      string mBHDXhEOpB;
      string oViCBhjKkD;
      string jRSUcyhIDg;
      string NawnkeQhGR;
      string jESgNZJGGP;
      string qakcTUhmZY;
      if(IWPVpoUdsi == GVpkrDaBYY){AuKJmOYuQW = true;}
      else if(GVpkrDaBYY == IWPVpoUdsi){wAOdCfDXSI = true;}
      if(VAJYYnGOLh == rpQBIzxcrX){RBETTezlHD = true;}
      else if(rpQBIzxcrX == VAJYYnGOLh){pagTlysuFa = true;}
      if(uuwHPiNQbt == fXleznSJhD){oaCnolpTTQ = true;}
      else if(fXleznSJhD == uuwHPiNQbt){pHYLkOAAfG = true;}
      if(xmuuczdWGc == usIIxblVfD){wdIgQnsJsz = true;}
      else if(usIIxblVfD == xmuuczdWGc){osJfCOKgcO = true;}
      if(qBaMQLkkJC == mBHDXhEOpB){ANpiypWRJn = true;}
      else if(mBHDXhEOpB == qBaMQLkkJC){wZSoATpUFc = true;}
      if(mijOSMZHGG == oViCBhjKkD){VwfVjZsWTB = true;}
      else if(oViCBhjKkD == mijOSMZHGG){CpkhToaCsm = true;}
      if(bECzliEOuY == jRSUcyhIDg){XEazansWCe = true;}
      else if(jRSUcyhIDg == bECzliEOuY){fCqMSwQARX = true;}
      if(KjIiptUipE == NawnkeQhGR){losHDbjSpz = true;}
      if(ybGYHNCfbQ == jESgNZJGGP){OYKftzylxp = true;}
      if(YVQzBmzbZh == qakcTUhmZY){tWorbwlpIJ = true;}
      while(NawnkeQhGR == KjIiptUipE){nMSpdPnjKQ = true;}
      while(jESgNZJGGP == jESgNZJGGP){YeuDEyHbLN = true;}
      while(qakcTUhmZY == qakcTUhmZY){mHnpisiGVE = true;}
      if(AuKJmOYuQW == true){AuKJmOYuQW = false;}
      if(RBETTezlHD == true){RBETTezlHD = false;}
      if(oaCnolpTTQ == true){oaCnolpTTQ = false;}
      if(wdIgQnsJsz == true){wdIgQnsJsz = false;}
      if(ANpiypWRJn == true){ANpiypWRJn = false;}
      if(VwfVjZsWTB == true){VwfVjZsWTB = false;}
      if(XEazansWCe == true){XEazansWCe = false;}
      if(losHDbjSpz == true){losHDbjSpz = false;}
      if(OYKftzylxp == true){OYKftzylxp = false;}
      if(tWorbwlpIJ == true){tWorbwlpIJ = false;}
      if(wAOdCfDXSI == true){wAOdCfDXSI = false;}
      if(pagTlysuFa == true){pagTlysuFa = false;}
      if(pHYLkOAAfG == true){pHYLkOAAfG = false;}
      if(osJfCOKgcO == true){osJfCOKgcO = false;}
      if(wZSoATpUFc == true){wZSoATpUFc = false;}
      if(CpkhToaCsm == true){CpkhToaCsm = false;}
      if(fCqMSwQARX == true){fCqMSwQARX = false;}
      if(nMSpdPnjKQ == true){nMSpdPnjKQ = false;}
      if(YeuDEyHbLN == true){YeuDEyHbLN = false;}
      if(mHnpisiGVE == true){mHnpisiGVE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YITHUXNALX
{ 
  void mRCIzAYmhn()
  { 
      bool guhtGokwSJ = false;
      bool GZdTxhqJgo = false;
      bool aFomfpfYqc = false;
      bool PodtDHTTsb = false;
      bool TsnbmHWeNK = false;
      bool siEWqbFtOP = false;
      bool JLFosRwiQo = false;
      bool NXQEVgRNAY = false;
      bool SBLgjgkGCb = false;
      bool CZEcSHnyhV = false;
      bool LmNXwVSzBK = false;
      bool JrsoxHAYFM = false;
      bool fogomnSmkN = false;
      bool sSeeNemmjN = false;
      bool OkFrRJfPfK = false;
      bool HOsUoWGYkH = false;
      bool DfNmRqMObR = false;
      bool UMnqyuinWc = false;
      bool ICGaFdZJoq = false;
      bool YNBcKhWRZZ = false;
      string GxuLQBFWJC;
      string QWLwhsjdYK;
      string mBbhlwllpS;
      string huslbNQwnu;
      string VxkEzUlHBD;
      string nQkYKEVNZU;
      string OSgqUVcYTU;
      string cmodopQWhR;
      string KejldQJTbX;
      string qCWSgCPsjd;
      string qMmgaBaHjU;
      string nyfHKihuMD;
      string LJxwcZQVxl;
      string ZWmEaxrDKc;
      string oCiGirWOIx;
      string UUgfSgPqEA;
      string jEJytQLagN;
      string qejjNIZpMj;
      string DBNzRFpGls;
      string gByKrjskMS;
      if(GxuLQBFWJC == qMmgaBaHjU){guhtGokwSJ = true;}
      else if(qMmgaBaHjU == GxuLQBFWJC){LmNXwVSzBK = true;}
      if(QWLwhsjdYK == nyfHKihuMD){GZdTxhqJgo = true;}
      else if(nyfHKihuMD == QWLwhsjdYK){JrsoxHAYFM = true;}
      if(mBbhlwllpS == LJxwcZQVxl){aFomfpfYqc = true;}
      else if(LJxwcZQVxl == mBbhlwllpS){fogomnSmkN = true;}
      if(huslbNQwnu == ZWmEaxrDKc){PodtDHTTsb = true;}
      else if(ZWmEaxrDKc == huslbNQwnu){sSeeNemmjN = true;}
      if(VxkEzUlHBD == oCiGirWOIx){TsnbmHWeNK = true;}
      else if(oCiGirWOIx == VxkEzUlHBD){OkFrRJfPfK = true;}
      if(nQkYKEVNZU == UUgfSgPqEA){siEWqbFtOP = true;}
      else if(UUgfSgPqEA == nQkYKEVNZU){HOsUoWGYkH = true;}
      if(OSgqUVcYTU == jEJytQLagN){JLFosRwiQo = true;}
      else if(jEJytQLagN == OSgqUVcYTU){DfNmRqMObR = true;}
      if(cmodopQWhR == qejjNIZpMj){NXQEVgRNAY = true;}
      if(KejldQJTbX == DBNzRFpGls){SBLgjgkGCb = true;}
      if(qCWSgCPsjd == gByKrjskMS){CZEcSHnyhV = true;}
      while(qejjNIZpMj == cmodopQWhR){UMnqyuinWc = true;}
      while(DBNzRFpGls == DBNzRFpGls){ICGaFdZJoq = true;}
      while(gByKrjskMS == gByKrjskMS){YNBcKhWRZZ = true;}
      if(guhtGokwSJ == true){guhtGokwSJ = false;}
      if(GZdTxhqJgo == true){GZdTxhqJgo = false;}
      if(aFomfpfYqc == true){aFomfpfYqc = false;}
      if(PodtDHTTsb == true){PodtDHTTsb = false;}
      if(TsnbmHWeNK == true){TsnbmHWeNK = false;}
      if(siEWqbFtOP == true){siEWqbFtOP = false;}
      if(JLFosRwiQo == true){JLFosRwiQo = false;}
      if(NXQEVgRNAY == true){NXQEVgRNAY = false;}
      if(SBLgjgkGCb == true){SBLgjgkGCb = false;}
      if(CZEcSHnyhV == true){CZEcSHnyhV = false;}
      if(LmNXwVSzBK == true){LmNXwVSzBK = false;}
      if(JrsoxHAYFM == true){JrsoxHAYFM = false;}
      if(fogomnSmkN == true){fogomnSmkN = false;}
      if(sSeeNemmjN == true){sSeeNemmjN = false;}
      if(OkFrRJfPfK == true){OkFrRJfPfK = false;}
      if(HOsUoWGYkH == true){HOsUoWGYkH = false;}
      if(DfNmRqMObR == true){DfNmRqMObR = false;}
      if(UMnqyuinWc == true){UMnqyuinWc = false;}
      if(ICGaFdZJoq == true){ICGaFdZJoq = false;}
      if(YNBcKhWRZZ == true){YNBcKhWRZZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RCMLWJOTWN
{ 
  void fuTmNDnzyu()
  { 
      bool PdIXOLKAlG = false;
      bool PjFrmSHsJl = false;
      bool PqiEBNmAyV = false;
      bool EOnTkfuwlq = false;
      bool PipdkoWZsq = false;
      bool UMFCoYtDWA = false;
      bool XKCPCAukGH = false;
      bool XKHRWfBFTM = false;
      bool qNGGBqJleM = false;
      bool kqZkTEgZbk = false;
      bool skSkTJFmfI = false;
      bool WojJJKDuOK = false;
      bool pJGtWfkVyR = false;
      bool zbchSFtVmq = false;
      bool lVFVouGPaI = false;
      bool BkKQtjeYOm = false;
      bool YioOIuMBqE = false;
      bool QhHWYUDjEa = false;
      bool YVuoQNQLmi = false;
      bool ZVGASCgqMt = false;
      string fXdNlOhUHZ;
      string XOFKCFxiTu;
      string XxoZQrCYXw;
      string YJwngzZNEN;
      string qAIosTLlhl;
      string ZZHkDhhExs;
      string MIxLBORQcC;
      string eieGDWoAgw;
      string gPqkWzBKjy;
      string RVPLBiDwmd;
      string BtJeGpuAhg;
      string sgWAMwRLnC;
      string MHgekJSSFU;
      string SrNCulGLdg;
      string DBcDFjyOyE;
      string QrIkRtNdsx;
      string WbtMNATUFZ;
      string pFgHyKedYB;
      string KEUADajbkA;
      string YbRgJbGPoF;
      if(fXdNlOhUHZ == BtJeGpuAhg){PdIXOLKAlG = true;}
      else if(BtJeGpuAhg == fXdNlOhUHZ){skSkTJFmfI = true;}
      if(XOFKCFxiTu == sgWAMwRLnC){PjFrmSHsJl = true;}
      else if(sgWAMwRLnC == XOFKCFxiTu){WojJJKDuOK = true;}
      if(XxoZQrCYXw == MHgekJSSFU){PqiEBNmAyV = true;}
      else if(MHgekJSSFU == XxoZQrCYXw){pJGtWfkVyR = true;}
      if(YJwngzZNEN == SrNCulGLdg){EOnTkfuwlq = true;}
      else if(SrNCulGLdg == YJwngzZNEN){zbchSFtVmq = true;}
      if(qAIosTLlhl == DBcDFjyOyE){PipdkoWZsq = true;}
      else if(DBcDFjyOyE == qAIosTLlhl){lVFVouGPaI = true;}
      if(ZZHkDhhExs == QrIkRtNdsx){UMFCoYtDWA = true;}
      else if(QrIkRtNdsx == ZZHkDhhExs){BkKQtjeYOm = true;}
      if(MIxLBORQcC == WbtMNATUFZ){XKCPCAukGH = true;}
      else if(WbtMNATUFZ == MIxLBORQcC){YioOIuMBqE = true;}
      if(eieGDWoAgw == pFgHyKedYB){XKHRWfBFTM = true;}
      if(gPqkWzBKjy == KEUADajbkA){qNGGBqJleM = true;}
      if(RVPLBiDwmd == YbRgJbGPoF){kqZkTEgZbk = true;}
      while(pFgHyKedYB == eieGDWoAgw){QhHWYUDjEa = true;}
      while(KEUADajbkA == KEUADajbkA){YVuoQNQLmi = true;}
      while(YbRgJbGPoF == YbRgJbGPoF){ZVGASCgqMt = true;}
      if(PdIXOLKAlG == true){PdIXOLKAlG = false;}
      if(PjFrmSHsJl == true){PjFrmSHsJl = false;}
      if(PqiEBNmAyV == true){PqiEBNmAyV = false;}
      if(EOnTkfuwlq == true){EOnTkfuwlq = false;}
      if(PipdkoWZsq == true){PipdkoWZsq = false;}
      if(UMFCoYtDWA == true){UMFCoYtDWA = false;}
      if(XKCPCAukGH == true){XKCPCAukGH = false;}
      if(XKHRWfBFTM == true){XKHRWfBFTM = false;}
      if(qNGGBqJleM == true){qNGGBqJleM = false;}
      if(kqZkTEgZbk == true){kqZkTEgZbk = false;}
      if(skSkTJFmfI == true){skSkTJFmfI = false;}
      if(WojJJKDuOK == true){WojJJKDuOK = false;}
      if(pJGtWfkVyR == true){pJGtWfkVyR = false;}
      if(zbchSFtVmq == true){zbchSFtVmq = false;}
      if(lVFVouGPaI == true){lVFVouGPaI = false;}
      if(BkKQtjeYOm == true){BkKQtjeYOm = false;}
      if(YioOIuMBqE == true){YioOIuMBqE = false;}
      if(QhHWYUDjEa == true){QhHWYUDjEa = false;}
      if(YVuoQNQLmi == true){YVuoQNQLmi = false;}
      if(ZVGASCgqMt == true){ZVGASCgqMt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWZHGTPCJQ
{ 
  void OJcIlgcpSG()
  { 
      bool DfYQqpsQLz = false;
      bool gOChmQamgw = false;
      bool PkMjNryLMT = false;
      bool QIOlIdnTOe = false;
      bool ObrlOZlBrl = false;
      bool SyijhSSnDy = false;
      bool rgErhYzPYI = false;
      bool cHYCgnraVm = false;
      bool FwSZASYeEp = false;
      bool LAQPlgXzDo = false;
      bool ZVcjJLYgCs = false;
      bool ZrSPswOdrP = false;
      bool ATLhxbpJQA = false;
      bool QsWfNjSiPo = false;
      bool sqcKQTgBWp = false;
      bool RsHnoFKtlg = false;
      bool VPPBcfUmBI = false;
      bool cfOCVIqARd = false;
      bool unlZhWkhpH = false;
      bool ZYwhSdbagj = false;
      string MxsrNsewHp;
      string QtjTQcUPKx;
      string sTGlJfZqJc;
      string BhlajBWSxA;
      string VsLiQIwQOr;
      string yfgWurpGhh;
      string SmmdohIJjP;
      string FCRKazIXVB;
      string jJcQeUBPeq;
      string KQkPghGgth;
      string zmfzmwOVuw;
      string jSkgyJKVzT;
      string gsdrEoRCcr;
      string radmBwcddi;
      string GeTiHreDRX;
      string XkhZBGIntx;
      string eLsCDJoyeB;
      string ggqQNCYtkM;
      string KNjFUHsDku;
      string noifDtkQfy;
      if(MxsrNsewHp == zmfzmwOVuw){DfYQqpsQLz = true;}
      else if(zmfzmwOVuw == MxsrNsewHp){ZVcjJLYgCs = true;}
      if(QtjTQcUPKx == jSkgyJKVzT){gOChmQamgw = true;}
      else if(jSkgyJKVzT == QtjTQcUPKx){ZrSPswOdrP = true;}
      if(sTGlJfZqJc == gsdrEoRCcr){PkMjNryLMT = true;}
      else if(gsdrEoRCcr == sTGlJfZqJc){ATLhxbpJQA = true;}
      if(BhlajBWSxA == radmBwcddi){QIOlIdnTOe = true;}
      else if(radmBwcddi == BhlajBWSxA){QsWfNjSiPo = true;}
      if(VsLiQIwQOr == GeTiHreDRX){ObrlOZlBrl = true;}
      else if(GeTiHreDRX == VsLiQIwQOr){sqcKQTgBWp = true;}
      if(yfgWurpGhh == XkhZBGIntx){SyijhSSnDy = true;}
      else if(XkhZBGIntx == yfgWurpGhh){RsHnoFKtlg = true;}
      if(SmmdohIJjP == eLsCDJoyeB){rgErhYzPYI = true;}
      else if(eLsCDJoyeB == SmmdohIJjP){VPPBcfUmBI = true;}
      if(FCRKazIXVB == ggqQNCYtkM){cHYCgnraVm = true;}
      if(jJcQeUBPeq == KNjFUHsDku){FwSZASYeEp = true;}
      if(KQkPghGgth == noifDtkQfy){LAQPlgXzDo = true;}
      while(ggqQNCYtkM == FCRKazIXVB){cfOCVIqARd = true;}
      while(KNjFUHsDku == KNjFUHsDku){unlZhWkhpH = true;}
      while(noifDtkQfy == noifDtkQfy){ZYwhSdbagj = true;}
      if(DfYQqpsQLz == true){DfYQqpsQLz = false;}
      if(gOChmQamgw == true){gOChmQamgw = false;}
      if(PkMjNryLMT == true){PkMjNryLMT = false;}
      if(QIOlIdnTOe == true){QIOlIdnTOe = false;}
      if(ObrlOZlBrl == true){ObrlOZlBrl = false;}
      if(SyijhSSnDy == true){SyijhSSnDy = false;}
      if(rgErhYzPYI == true){rgErhYzPYI = false;}
      if(cHYCgnraVm == true){cHYCgnraVm = false;}
      if(FwSZASYeEp == true){FwSZASYeEp = false;}
      if(LAQPlgXzDo == true){LAQPlgXzDo = false;}
      if(ZVcjJLYgCs == true){ZVcjJLYgCs = false;}
      if(ZrSPswOdrP == true){ZrSPswOdrP = false;}
      if(ATLhxbpJQA == true){ATLhxbpJQA = false;}
      if(QsWfNjSiPo == true){QsWfNjSiPo = false;}
      if(sqcKQTgBWp == true){sqcKQTgBWp = false;}
      if(RsHnoFKtlg == true){RsHnoFKtlg = false;}
      if(VPPBcfUmBI == true){VPPBcfUmBI = false;}
      if(cfOCVIqARd == true){cfOCVIqARd = false;}
      if(unlZhWkhpH == true){unlZhWkhpH = false;}
      if(ZYwhSdbagj == true){ZYwhSdbagj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CLWNMGRMQC
{ 
  void MTAWFrQmBH()
  { 
      bool rBYifASWxM = false;
      bool xEINrnrkhn = false;
      bool EflZjwWPVk = false;
      bool VDrlNUlqey = false;
      bool jxxewqQagT = false;
      bool YyOsmMPyzi = false;
      bool dDAMpsMWAW = false;
      bool CAFjEHhGcr = false;
      bool fuhBLWoyzB = false;
      bool FmrwUfwkoD = false;
      bool etaJRXreoe = false;
      bool dIUGDhVyAT = false;
      bool DNWyROIJOY = false;
      bool KwRZNkUXjn = false;
      bool eJJTWwRkrl = false;
      bool KykUzQWbrC = false;
      bool OhPPUgqusR = false;
      bool NyOMosECbU = false;
      bool xWRcOMLwZx = false;
      bool NregYwtszo = false;
      string GArjeCgXco;
      string cIJOGlwtPr;
      string UCyrCQZKnb;
      string KBFeMqSmiO;
      string CVqQegJgIj;
      string OSKiBECAhN;
      string bWiBebCdBO;
      string TJKApyKgMV;
      string GrCENrpWcI;
      string oSFVmfmolD;
      string dffsPEHJrD;
      string sVmLGjTdnl;
      string kfAsZBEoNK;
      string LUtJraMIoI;
      string jfeZOTesOC;
      string LIBzRyemTO;
      string zSwgqXadTf;
      string WKoeCFBadG;
      string VLZKzCTurs;
      string wZnZIRjxhq;
      if(GArjeCgXco == dffsPEHJrD){rBYifASWxM = true;}
      else if(dffsPEHJrD == GArjeCgXco){etaJRXreoe = true;}
      if(cIJOGlwtPr == sVmLGjTdnl){xEINrnrkhn = true;}
      else if(sVmLGjTdnl == cIJOGlwtPr){dIUGDhVyAT = true;}
      if(UCyrCQZKnb == kfAsZBEoNK){EflZjwWPVk = true;}
      else if(kfAsZBEoNK == UCyrCQZKnb){DNWyROIJOY = true;}
      if(KBFeMqSmiO == LUtJraMIoI){VDrlNUlqey = true;}
      else if(LUtJraMIoI == KBFeMqSmiO){KwRZNkUXjn = true;}
      if(CVqQegJgIj == jfeZOTesOC){jxxewqQagT = true;}
      else if(jfeZOTesOC == CVqQegJgIj){eJJTWwRkrl = true;}
      if(OSKiBECAhN == LIBzRyemTO){YyOsmMPyzi = true;}
      else if(LIBzRyemTO == OSKiBECAhN){KykUzQWbrC = true;}
      if(bWiBebCdBO == zSwgqXadTf){dDAMpsMWAW = true;}
      else if(zSwgqXadTf == bWiBebCdBO){OhPPUgqusR = true;}
      if(TJKApyKgMV == WKoeCFBadG){CAFjEHhGcr = true;}
      if(GrCENrpWcI == VLZKzCTurs){fuhBLWoyzB = true;}
      if(oSFVmfmolD == wZnZIRjxhq){FmrwUfwkoD = true;}
      while(WKoeCFBadG == TJKApyKgMV){NyOMosECbU = true;}
      while(VLZKzCTurs == VLZKzCTurs){xWRcOMLwZx = true;}
      while(wZnZIRjxhq == wZnZIRjxhq){NregYwtszo = true;}
      if(rBYifASWxM == true){rBYifASWxM = false;}
      if(xEINrnrkhn == true){xEINrnrkhn = false;}
      if(EflZjwWPVk == true){EflZjwWPVk = false;}
      if(VDrlNUlqey == true){VDrlNUlqey = false;}
      if(jxxewqQagT == true){jxxewqQagT = false;}
      if(YyOsmMPyzi == true){YyOsmMPyzi = false;}
      if(dDAMpsMWAW == true){dDAMpsMWAW = false;}
      if(CAFjEHhGcr == true){CAFjEHhGcr = false;}
      if(fuhBLWoyzB == true){fuhBLWoyzB = false;}
      if(FmrwUfwkoD == true){FmrwUfwkoD = false;}
      if(etaJRXreoe == true){etaJRXreoe = false;}
      if(dIUGDhVyAT == true){dIUGDhVyAT = false;}
      if(DNWyROIJOY == true){DNWyROIJOY = false;}
      if(KwRZNkUXjn == true){KwRZNkUXjn = false;}
      if(eJJTWwRkrl == true){eJJTWwRkrl = false;}
      if(KykUzQWbrC == true){KykUzQWbrC = false;}
      if(OhPPUgqusR == true){OhPPUgqusR = false;}
      if(NyOMosECbU == true){NyOMosECbU = false;}
      if(xWRcOMLwZx == true){xWRcOMLwZx = false;}
      if(NregYwtszo == true){NregYwtszo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CERKBOTVTJ
{ 
  void MKDsxOrdFy()
  { 
      bool nrihElTeBi = false;
      bool txRfSZHySJ = false;
      bool jfYaFMYiXQ = false;
      bool gFhzDFFkHe = false;
      bool GkgRxBDJiq = false;
      bool aCqljHTIbr = false;
      bool NkHkCoORcN = false;
      bool TWpnCyzGcE = false;
      bool IOzgodOwPu = false;
      bool lxJPRVduPI = false;
      bool llfVWDLCik = false;
      bool IMeWiykZuX = false;
      bool aSChaVNZWg = false;
      bool UDqUSWhcJk = false;
      bool SLMdlZSlgT = false;
      bool jDArgSiytA = false;
      bool plfCPFUJDM = false;
      bool PHPJFPFXuB = false;
      bool DasCwRDzmz = false;
      bool mjiIufeKOg = false;
      string XuSobNrYEm;
      string axHHjDbRVa;
      string PODAxrumOB;
      string nKqEOqbOyt;
      string gWpJZakQJK;
      string RymuIJqRri;
      string SFKCyQGDsr;
      string bNTbsrXtaW;
      string GddDioWwuF;
      string zJWObbMmKJ;
      string UhXQiEeLBQ;
      string kxqUcnaGSJ;
      string sJHmsRpEAR;
      string fkiRCXFMUe;
      string JLteTCSBlm;
      string AFTBQKZjWR;
      string NaKjjANZSE;
      string hOlnzgPcSq;
      string ynSMQaQhAr;
      string yUoCQiAKuT;
      if(XuSobNrYEm == UhXQiEeLBQ){nrihElTeBi = true;}
      else if(UhXQiEeLBQ == XuSobNrYEm){llfVWDLCik = true;}
      if(axHHjDbRVa == kxqUcnaGSJ){txRfSZHySJ = true;}
      else if(kxqUcnaGSJ == axHHjDbRVa){IMeWiykZuX = true;}
      if(PODAxrumOB == sJHmsRpEAR){jfYaFMYiXQ = true;}
      else if(sJHmsRpEAR == PODAxrumOB){aSChaVNZWg = true;}
      if(nKqEOqbOyt == fkiRCXFMUe){gFhzDFFkHe = true;}
      else if(fkiRCXFMUe == nKqEOqbOyt){UDqUSWhcJk = true;}
      if(gWpJZakQJK == JLteTCSBlm){GkgRxBDJiq = true;}
      else if(JLteTCSBlm == gWpJZakQJK){SLMdlZSlgT = true;}
      if(RymuIJqRri == AFTBQKZjWR){aCqljHTIbr = true;}
      else if(AFTBQKZjWR == RymuIJqRri){jDArgSiytA = true;}
      if(SFKCyQGDsr == NaKjjANZSE){NkHkCoORcN = true;}
      else if(NaKjjANZSE == SFKCyQGDsr){plfCPFUJDM = true;}
      if(bNTbsrXtaW == hOlnzgPcSq){TWpnCyzGcE = true;}
      if(GddDioWwuF == ynSMQaQhAr){IOzgodOwPu = true;}
      if(zJWObbMmKJ == yUoCQiAKuT){lxJPRVduPI = true;}
      while(hOlnzgPcSq == bNTbsrXtaW){PHPJFPFXuB = true;}
      while(ynSMQaQhAr == ynSMQaQhAr){DasCwRDzmz = true;}
      while(yUoCQiAKuT == yUoCQiAKuT){mjiIufeKOg = true;}
      if(nrihElTeBi == true){nrihElTeBi = false;}
      if(txRfSZHySJ == true){txRfSZHySJ = false;}
      if(jfYaFMYiXQ == true){jfYaFMYiXQ = false;}
      if(gFhzDFFkHe == true){gFhzDFFkHe = false;}
      if(GkgRxBDJiq == true){GkgRxBDJiq = false;}
      if(aCqljHTIbr == true){aCqljHTIbr = false;}
      if(NkHkCoORcN == true){NkHkCoORcN = false;}
      if(TWpnCyzGcE == true){TWpnCyzGcE = false;}
      if(IOzgodOwPu == true){IOzgodOwPu = false;}
      if(lxJPRVduPI == true){lxJPRVduPI = false;}
      if(llfVWDLCik == true){llfVWDLCik = false;}
      if(IMeWiykZuX == true){IMeWiykZuX = false;}
      if(aSChaVNZWg == true){aSChaVNZWg = false;}
      if(UDqUSWhcJk == true){UDqUSWhcJk = false;}
      if(SLMdlZSlgT == true){SLMdlZSlgT = false;}
      if(jDArgSiytA == true){jDArgSiytA = false;}
      if(plfCPFUJDM == true){plfCPFUJDM = false;}
      if(PHPJFPFXuB == true){PHPJFPFXuB = false;}
      if(DasCwRDzmz == true){DasCwRDzmz = false;}
      if(mjiIufeKOg == true){mjiIufeKOg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LXQWFTAYTI
{ 
  void ItIZoqdqrw()
  { 
      bool FjTnuSqjwW = false;
      bool GnZYVzwtbP = false;
      bool cWjwSegKBo = false;
      bool rLfEBCohEq = false;
      bool tGZdDNsLQr = false;
      bool KSryRizWVQ = false;
      bool kfhHdtIVXS = false;
      bool JNpjUWwGsF = false;
      bool lVtJeZShlR = false;
      bool CSMmGOXSzI = false;
      bool FWmxhwbHcu = false;
      bool lsdPePlYbE = false;
      bool aajFQqBCdG = false;
      bool ycGjAOhwah = false;
      bool xLEqfJowIq = false;
      bool czptgdmhgq = false;
      bool uYdWwIlsPP = false;
      bool goxtHPVrZH = false;
      bool BEtldzlMCV = false;
      bool bAPilYgguW = false;
      string cVwsUIBRhI;
      string aSlAPCMzmb;
      string qxiRVhkLPw;
      string QQpfixMADH;
      string KiGFzBBFGF;
      string EtTAlemdWm;
      string WoCkrKcFRR;
      string oMueRIpcRU;
      string gfFKrWxptD;
      string KhcPkVgVNo;
      string YumnPryoid;
      string nJMCGqjrsU;
      string NmLNHHiftw;
      string aTPbukrRtz;
      string YIGQOAUZJt;
      string kocrbliYfI;
      string IRulCTtkGU;
      string ySxswFftyH;
      string lJVAKlqWAJ;
      string CTklqGNTOt;
      if(cVwsUIBRhI == YumnPryoid){FjTnuSqjwW = true;}
      else if(YumnPryoid == cVwsUIBRhI){FWmxhwbHcu = true;}
      if(aSlAPCMzmb == nJMCGqjrsU){GnZYVzwtbP = true;}
      else if(nJMCGqjrsU == aSlAPCMzmb){lsdPePlYbE = true;}
      if(qxiRVhkLPw == NmLNHHiftw){cWjwSegKBo = true;}
      else if(NmLNHHiftw == qxiRVhkLPw){aajFQqBCdG = true;}
      if(QQpfixMADH == aTPbukrRtz){rLfEBCohEq = true;}
      else if(aTPbukrRtz == QQpfixMADH){ycGjAOhwah = true;}
      if(KiGFzBBFGF == YIGQOAUZJt){tGZdDNsLQr = true;}
      else if(YIGQOAUZJt == KiGFzBBFGF){xLEqfJowIq = true;}
      if(EtTAlemdWm == kocrbliYfI){KSryRizWVQ = true;}
      else if(kocrbliYfI == EtTAlemdWm){czptgdmhgq = true;}
      if(WoCkrKcFRR == IRulCTtkGU){kfhHdtIVXS = true;}
      else if(IRulCTtkGU == WoCkrKcFRR){uYdWwIlsPP = true;}
      if(oMueRIpcRU == ySxswFftyH){JNpjUWwGsF = true;}
      if(gfFKrWxptD == lJVAKlqWAJ){lVtJeZShlR = true;}
      if(KhcPkVgVNo == CTklqGNTOt){CSMmGOXSzI = true;}
      while(ySxswFftyH == oMueRIpcRU){goxtHPVrZH = true;}
      while(lJVAKlqWAJ == lJVAKlqWAJ){BEtldzlMCV = true;}
      while(CTklqGNTOt == CTklqGNTOt){bAPilYgguW = true;}
      if(FjTnuSqjwW == true){FjTnuSqjwW = false;}
      if(GnZYVzwtbP == true){GnZYVzwtbP = false;}
      if(cWjwSegKBo == true){cWjwSegKBo = false;}
      if(rLfEBCohEq == true){rLfEBCohEq = false;}
      if(tGZdDNsLQr == true){tGZdDNsLQr = false;}
      if(KSryRizWVQ == true){KSryRizWVQ = false;}
      if(kfhHdtIVXS == true){kfhHdtIVXS = false;}
      if(JNpjUWwGsF == true){JNpjUWwGsF = false;}
      if(lVtJeZShlR == true){lVtJeZShlR = false;}
      if(CSMmGOXSzI == true){CSMmGOXSzI = false;}
      if(FWmxhwbHcu == true){FWmxhwbHcu = false;}
      if(lsdPePlYbE == true){lsdPePlYbE = false;}
      if(aajFQqBCdG == true){aajFQqBCdG = false;}
      if(ycGjAOhwah == true){ycGjAOhwah = false;}
      if(xLEqfJowIq == true){xLEqfJowIq = false;}
      if(czptgdmhgq == true){czptgdmhgq = false;}
      if(uYdWwIlsPP == true){uYdWwIlsPP = false;}
      if(goxtHPVrZH == true){goxtHPVrZH = false;}
      if(BEtldzlMCV == true){BEtldzlMCV = false;}
      if(bAPilYgguW == true){bAPilYgguW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHCSUBXKVV
{ 
  void ODeryASWSG()
  { 
      bool jYKXEydqyA = false;
      bool cspCGbZLhw = false;
      bool NZWllrrmXM = false;
      bool mXueWgZAgM = false;
      bool PlhmBlZCto = false;
      bool RmilOKCXkL = false;
      bool GpSkNExKeZ = false;
      bool CZdUgaqijA = false;
      bool RosiuznJQM = false;
      bool eBOVFZTwZw = false;
      bool nOXUmqINFm = false;
      bool SSmksRxjpN = false;
      bool QntStBKIPH = false;
      bool HtInMCRYwD = false;
      bool qaDdsLNdbn = false;
      bool biGMfzUEZl = false;
      bool gzyyeYKzYp = false;
      bool zYnmVpjQYh = false;
      bool mggaeXmuIM = false;
      bool hMyKVqbFyU = false;
      string BCaPVQjGrd;
      string ufpmfQLTWy;
      string bkesocJEjV;
      string gUWMnDENAp;
      string lsXwwbCXiQ;
      string UebMkQXhas;
      string HfWVxaJdzc;
      string MxTgMiNhwN;
      string ZlUSBBrKaX;
      string eVmHhFVBzV;
      string RYYGEWKuzC;
      string DolMSVKDUu;
      string izCbxpKMyG;
      string MLiawBMNOd;
      string pwKYTpjanM;
      string uSgDmRWxJN;
      string MyxsprFKPQ;
      string IwopFlodHH;
      string GjXkLsdfnd;
      string ePEBRrzQhb;
      if(BCaPVQjGrd == RYYGEWKuzC){jYKXEydqyA = true;}
      else if(RYYGEWKuzC == BCaPVQjGrd){nOXUmqINFm = true;}
      if(ufpmfQLTWy == DolMSVKDUu){cspCGbZLhw = true;}
      else if(DolMSVKDUu == ufpmfQLTWy){SSmksRxjpN = true;}
      if(bkesocJEjV == izCbxpKMyG){NZWllrrmXM = true;}
      else if(izCbxpKMyG == bkesocJEjV){QntStBKIPH = true;}
      if(gUWMnDENAp == MLiawBMNOd){mXueWgZAgM = true;}
      else if(MLiawBMNOd == gUWMnDENAp){HtInMCRYwD = true;}
      if(lsXwwbCXiQ == pwKYTpjanM){PlhmBlZCto = true;}
      else if(pwKYTpjanM == lsXwwbCXiQ){qaDdsLNdbn = true;}
      if(UebMkQXhas == uSgDmRWxJN){RmilOKCXkL = true;}
      else if(uSgDmRWxJN == UebMkQXhas){biGMfzUEZl = true;}
      if(HfWVxaJdzc == MyxsprFKPQ){GpSkNExKeZ = true;}
      else if(MyxsprFKPQ == HfWVxaJdzc){gzyyeYKzYp = true;}
      if(MxTgMiNhwN == IwopFlodHH){CZdUgaqijA = true;}
      if(ZlUSBBrKaX == GjXkLsdfnd){RosiuznJQM = true;}
      if(eVmHhFVBzV == ePEBRrzQhb){eBOVFZTwZw = true;}
      while(IwopFlodHH == MxTgMiNhwN){zYnmVpjQYh = true;}
      while(GjXkLsdfnd == GjXkLsdfnd){mggaeXmuIM = true;}
      while(ePEBRrzQhb == ePEBRrzQhb){hMyKVqbFyU = true;}
      if(jYKXEydqyA == true){jYKXEydqyA = false;}
      if(cspCGbZLhw == true){cspCGbZLhw = false;}
      if(NZWllrrmXM == true){NZWllrrmXM = false;}
      if(mXueWgZAgM == true){mXueWgZAgM = false;}
      if(PlhmBlZCto == true){PlhmBlZCto = false;}
      if(RmilOKCXkL == true){RmilOKCXkL = false;}
      if(GpSkNExKeZ == true){GpSkNExKeZ = false;}
      if(CZdUgaqijA == true){CZdUgaqijA = false;}
      if(RosiuznJQM == true){RosiuznJQM = false;}
      if(eBOVFZTwZw == true){eBOVFZTwZw = false;}
      if(nOXUmqINFm == true){nOXUmqINFm = false;}
      if(SSmksRxjpN == true){SSmksRxjpN = false;}
      if(QntStBKIPH == true){QntStBKIPH = false;}
      if(HtInMCRYwD == true){HtInMCRYwD = false;}
      if(qaDdsLNdbn == true){qaDdsLNdbn = false;}
      if(biGMfzUEZl == true){biGMfzUEZl = false;}
      if(gzyyeYKzYp == true){gzyyeYKzYp = false;}
      if(zYnmVpjQYh == true){zYnmVpjQYh = false;}
      if(mggaeXmuIM == true){mggaeXmuIM = false;}
      if(hMyKVqbFyU == true){hMyKVqbFyU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RHNOJQUONX
{ 
  void RSWjRAzJVC()
  { 
      bool LQcnUPzuhP = false;
      bool bHakxmgFPd = false;
      bool hOnYJpCWVD = false;
      bool eSdqEoyIVe = false;
      bool LVwsnmCcFP = false;
      bool qWBjQxbDde = false;
      bool MbYdjJdjgI = false;
      bool nYjjSMRukV = false;
      bool mZRGMIRsZG = false;
      bool MudpRiwRJe = false;
      bool JSwxbSmQRE = false;
      bool egSHqmKSRb = false;
      bool rjKZwstsSi = false;
      bool PAkFMUcUds = false;
      bool UAbUaebVzd = false;
      bool XdAgmZIVAi = false;
      bool YsyhoeuMuV = false;
      bool KpnXGqHozQ = false;
      bool QXtnLlzESm = false;
      bool MHTuUbCtfw = false;
      string HWiTDtYfnT;
      string yQZnuTpUGS;
      string RZOVzLdIRV;
      string VPqAQrGHkU;
      string dWdllyUdYl;
      string sBObVgHNUq;
      string PQNSyhZZXD;
      string NiikouwbjB;
      string qAjfbTBOdi;
      string jrmtENIKnD;
      string XuFUYKScma;
      string kfdTAPfhpd;
      string fLunTUuofb;
      string lknfcuuOHR;
      string BYbDyDOTso;
      string gaTKWMAQAD;
      string OcwKozrxpF;
      string TQaYbHjrpP;
      string FbwquLQdIQ;
      string udNDCYbQNz;
      if(HWiTDtYfnT == XuFUYKScma){LQcnUPzuhP = true;}
      else if(XuFUYKScma == HWiTDtYfnT){JSwxbSmQRE = true;}
      if(yQZnuTpUGS == kfdTAPfhpd){bHakxmgFPd = true;}
      else if(kfdTAPfhpd == yQZnuTpUGS){egSHqmKSRb = true;}
      if(RZOVzLdIRV == fLunTUuofb){hOnYJpCWVD = true;}
      else if(fLunTUuofb == RZOVzLdIRV){rjKZwstsSi = true;}
      if(VPqAQrGHkU == lknfcuuOHR){eSdqEoyIVe = true;}
      else if(lknfcuuOHR == VPqAQrGHkU){PAkFMUcUds = true;}
      if(dWdllyUdYl == BYbDyDOTso){LVwsnmCcFP = true;}
      else if(BYbDyDOTso == dWdllyUdYl){UAbUaebVzd = true;}
      if(sBObVgHNUq == gaTKWMAQAD){qWBjQxbDde = true;}
      else if(gaTKWMAQAD == sBObVgHNUq){XdAgmZIVAi = true;}
      if(PQNSyhZZXD == OcwKozrxpF){MbYdjJdjgI = true;}
      else if(OcwKozrxpF == PQNSyhZZXD){YsyhoeuMuV = true;}
      if(NiikouwbjB == TQaYbHjrpP){nYjjSMRukV = true;}
      if(qAjfbTBOdi == FbwquLQdIQ){mZRGMIRsZG = true;}
      if(jrmtENIKnD == udNDCYbQNz){MudpRiwRJe = true;}
      while(TQaYbHjrpP == NiikouwbjB){KpnXGqHozQ = true;}
      while(FbwquLQdIQ == FbwquLQdIQ){QXtnLlzESm = true;}
      while(udNDCYbQNz == udNDCYbQNz){MHTuUbCtfw = true;}
      if(LQcnUPzuhP == true){LQcnUPzuhP = false;}
      if(bHakxmgFPd == true){bHakxmgFPd = false;}
      if(hOnYJpCWVD == true){hOnYJpCWVD = false;}
      if(eSdqEoyIVe == true){eSdqEoyIVe = false;}
      if(LVwsnmCcFP == true){LVwsnmCcFP = false;}
      if(qWBjQxbDde == true){qWBjQxbDde = false;}
      if(MbYdjJdjgI == true){MbYdjJdjgI = false;}
      if(nYjjSMRukV == true){nYjjSMRukV = false;}
      if(mZRGMIRsZG == true){mZRGMIRsZG = false;}
      if(MudpRiwRJe == true){MudpRiwRJe = false;}
      if(JSwxbSmQRE == true){JSwxbSmQRE = false;}
      if(egSHqmKSRb == true){egSHqmKSRb = false;}
      if(rjKZwstsSi == true){rjKZwstsSi = false;}
      if(PAkFMUcUds == true){PAkFMUcUds = false;}
      if(UAbUaebVzd == true){UAbUaebVzd = false;}
      if(XdAgmZIVAi == true){XdAgmZIVAi = false;}
      if(YsyhoeuMuV == true){YsyhoeuMuV = false;}
      if(KpnXGqHozQ == true){KpnXGqHozQ = false;}
      if(QXtnLlzESm == true){QXtnLlzESm = false;}
      if(MHTuUbCtfw == true){MHTuUbCtfw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KIXMSGNLCY
{ 
  void kJEaUVEVjy()
  { 
      bool fEEVmjuOKB = false;
      bool cawrGmGtGW = false;
      bool BLKXuihLMZ = false;
      bool pECrkxEpqK = false;
      bool DtUWJgoGuV = false;
      bool iPMAATtgaE = false;
      bool BiCjKYYDHI = false;
      bool hPDwTGpnON = false;
      bool sbQqqaqCqQ = false;
      bool DWPlITrkLj = false;
      bool HkylmTLPfs = false;
      bool cFRMKZSKsj = false;
      bool gWMpELARnz = false;
      bool OFcdFHcdEW = false;
      bool OaVxnxECah = false;
      bool BgraDkYHha = false;
      bool TtbgeWcnGD = false;
      bool wnGVVFAOCG = false;
      bool GxpFxgNBaU = false;
      bool iVwcDUznSQ = false;
      string UonaSiDbcV;
      string biaHbwamZS;
      string ALnXxhIJtd;
      string kyKldUKoTg;
      string BNHiNRHdEj;
      string FXDdPJBQck;
      string atgykdYodH;
      string kkTrRmDEJf;
      string adEJYMtfVT;
      string TtMiFGfJyj;
      string sSAwzUELLc;
      string FwHxKxoXYX;
      string irSJmpYklL;
      string GtFYmHcIKE;
      string IiTsOWmOYI;
      string QIjZBAAqJI;
      string wSYAVLqhJC;
      string UgMUPAXYuQ;
      string CJMdtyJeXl;
      string HlzBIoJTWC;
      if(UonaSiDbcV == sSAwzUELLc){fEEVmjuOKB = true;}
      else if(sSAwzUELLc == UonaSiDbcV){HkylmTLPfs = true;}
      if(biaHbwamZS == FwHxKxoXYX){cawrGmGtGW = true;}
      else if(FwHxKxoXYX == biaHbwamZS){cFRMKZSKsj = true;}
      if(ALnXxhIJtd == irSJmpYklL){BLKXuihLMZ = true;}
      else if(irSJmpYklL == ALnXxhIJtd){gWMpELARnz = true;}
      if(kyKldUKoTg == GtFYmHcIKE){pECrkxEpqK = true;}
      else if(GtFYmHcIKE == kyKldUKoTg){OFcdFHcdEW = true;}
      if(BNHiNRHdEj == IiTsOWmOYI){DtUWJgoGuV = true;}
      else if(IiTsOWmOYI == BNHiNRHdEj){OaVxnxECah = true;}
      if(FXDdPJBQck == QIjZBAAqJI){iPMAATtgaE = true;}
      else if(QIjZBAAqJI == FXDdPJBQck){BgraDkYHha = true;}
      if(atgykdYodH == wSYAVLqhJC){BiCjKYYDHI = true;}
      else if(wSYAVLqhJC == atgykdYodH){TtbgeWcnGD = true;}
      if(kkTrRmDEJf == UgMUPAXYuQ){hPDwTGpnON = true;}
      if(adEJYMtfVT == CJMdtyJeXl){sbQqqaqCqQ = true;}
      if(TtMiFGfJyj == HlzBIoJTWC){DWPlITrkLj = true;}
      while(UgMUPAXYuQ == kkTrRmDEJf){wnGVVFAOCG = true;}
      while(CJMdtyJeXl == CJMdtyJeXl){GxpFxgNBaU = true;}
      while(HlzBIoJTWC == HlzBIoJTWC){iVwcDUznSQ = true;}
      if(fEEVmjuOKB == true){fEEVmjuOKB = false;}
      if(cawrGmGtGW == true){cawrGmGtGW = false;}
      if(BLKXuihLMZ == true){BLKXuihLMZ = false;}
      if(pECrkxEpqK == true){pECrkxEpqK = false;}
      if(DtUWJgoGuV == true){DtUWJgoGuV = false;}
      if(iPMAATtgaE == true){iPMAATtgaE = false;}
      if(BiCjKYYDHI == true){BiCjKYYDHI = false;}
      if(hPDwTGpnON == true){hPDwTGpnON = false;}
      if(sbQqqaqCqQ == true){sbQqqaqCqQ = false;}
      if(DWPlITrkLj == true){DWPlITrkLj = false;}
      if(HkylmTLPfs == true){HkylmTLPfs = false;}
      if(cFRMKZSKsj == true){cFRMKZSKsj = false;}
      if(gWMpELARnz == true){gWMpELARnz = false;}
      if(OFcdFHcdEW == true){OFcdFHcdEW = false;}
      if(OaVxnxECah == true){OaVxnxECah = false;}
      if(BgraDkYHha == true){BgraDkYHha = false;}
      if(TtbgeWcnGD == true){TtbgeWcnGD = false;}
      if(wnGVVFAOCG == true){wnGVVFAOCG = false;}
      if(GxpFxgNBaU == true){GxpFxgNBaU = false;}
      if(iVwcDUznSQ == true){iVwcDUznSQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QVTZMVMKTR
{ 
  void SRssMTmfmV()
  { 
      bool BguqbEZqwM = false;
      bool ZNwWdrOREL = false;
      bool FsmQQXTUIn = false;
      bool yupHELDpoO = false;
      bool ruUSZljpPu = false;
      bool pdUjhIsdaD = false;
      bool jFiINdXoRR = false;
      bool nXcpTJXTpd = false;
      bool ndEMxUaFZw = false;
      bool SYPkdlMMFu = false;
      bool NuXyHSBePY = false;
      bool jZnwPGAVLs = false;
      bool DROVzPIqLg = false;
      bool wLNtQsGGFe = false;
      bool SwpAMrjSVX = false;
      bool lpBMrufCzr = false;
      bool JJSibYLteV = false;
      bool ztQfZHbOJG = false;
      bool eoVmuFKBCV = false;
      bool MDGNUJcHYm = false;
      string dXTmXHzLZa;
      string rSsmriaRom;
      string GRLrSullzQ;
      string qEWVMrhrCf;
      string WfZTWJityR;
      string jCqtKMLbUc;
      string UMMJinuWaA;
      string AhPJPZrrVI;
      string LqnhgoNbKA;
      string fGXYKKTQjh;
      string NLSxQBmhdk;
      string TSGLQdXebt;
      string aSLaTsKpyF;
      string GbHmuAYpQe;
      string BfyZfNALIg;
      string lnnoHtArdW;
      string qwiYdrLSQQ;
      string EgOwsuUluG;
      string syhQTRmRfA;
      string AgMsnEwZwm;
      if(dXTmXHzLZa == NLSxQBmhdk){BguqbEZqwM = true;}
      else if(NLSxQBmhdk == dXTmXHzLZa){NuXyHSBePY = true;}
      if(rSsmriaRom == TSGLQdXebt){ZNwWdrOREL = true;}
      else if(TSGLQdXebt == rSsmriaRom){jZnwPGAVLs = true;}
      if(GRLrSullzQ == aSLaTsKpyF){FsmQQXTUIn = true;}
      else if(aSLaTsKpyF == GRLrSullzQ){DROVzPIqLg = true;}
      if(qEWVMrhrCf == GbHmuAYpQe){yupHELDpoO = true;}
      else if(GbHmuAYpQe == qEWVMrhrCf){wLNtQsGGFe = true;}
      if(WfZTWJityR == BfyZfNALIg){ruUSZljpPu = true;}
      else if(BfyZfNALIg == WfZTWJityR){SwpAMrjSVX = true;}
      if(jCqtKMLbUc == lnnoHtArdW){pdUjhIsdaD = true;}
      else if(lnnoHtArdW == jCqtKMLbUc){lpBMrufCzr = true;}
      if(UMMJinuWaA == qwiYdrLSQQ){jFiINdXoRR = true;}
      else if(qwiYdrLSQQ == UMMJinuWaA){JJSibYLteV = true;}
      if(AhPJPZrrVI == EgOwsuUluG){nXcpTJXTpd = true;}
      if(LqnhgoNbKA == syhQTRmRfA){ndEMxUaFZw = true;}
      if(fGXYKKTQjh == AgMsnEwZwm){SYPkdlMMFu = true;}
      while(EgOwsuUluG == AhPJPZrrVI){ztQfZHbOJG = true;}
      while(syhQTRmRfA == syhQTRmRfA){eoVmuFKBCV = true;}
      while(AgMsnEwZwm == AgMsnEwZwm){MDGNUJcHYm = true;}
      if(BguqbEZqwM == true){BguqbEZqwM = false;}
      if(ZNwWdrOREL == true){ZNwWdrOREL = false;}
      if(FsmQQXTUIn == true){FsmQQXTUIn = false;}
      if(yupHELDpoO == true){yupHELDpoO = false;}
      if(ruUSZljpPu == true){ruUSZljpPu = false;}
      if(pdUjhIsdaD == true){pdUjhIsdaD = false;}
      if(jFiINdXoRR == true){jFiINdXoRR = false;}
      if(nXcpTJXTpd == true){nXcpTJXTpd = false;}
      if(ndEMxUaFZw == true){ndEMxUaFZw = false;}
      if(SYPkdlMMFu == true){SYPkdlMMFu = false;}
      if(NuXyHSBePY == true){NuXyHSBePY = false;}
      if(jZnwPGAVLs == true){jZnwPGAVLs = false;}
      if(DROVzPIqLg == true){DROVzPIqLg = false;}
      if(wLNtQsGGFe == true){wLNtQsGGFe = false;}
      if(SwpAMrjSVX == true){SwpAMrjSVX = false;}
      if(lpBMrufCzr == true){lpBMrufCzr = false;}
      if(JJSibYLteV == true){JJSibYLteV = false;}
      if(ztQfZHbOJG == true){ztQfZHbOJG = false;}
      if(eoVmuFKBCV == true){eoVmuFKBCV = false;}
      if(MDGNUJcHYm == true){MDGNUJcHYm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VKSAEIZGHG
{ 
  void kxdGfikZHR()
  { 
      bool qjuoyShmRf = false;
      bool naXkXgNOCo = false;
      bool aLGIOYZrzK = false;
      bool zxaZXglkTQ = false;
      bool bUIbsrPROm = false;
      bool iCwyNfclZZ = false;
      bool rpmGgqAxMp = false;
      bool tbtlMFDePW = false;
      bool IIcLbwBbLr = false;
      bool EzLtYlhBuB = false;
      bool rREXrGIKkH = false;
      bool cyVCRjMaej = false;
      bool oXlUluQzMa = false;
      bool XBiNepDFSV = false;
      bool nppDPGcIco = false;
      bool YGWLMTfjlx = false;
      bool pIyKjaOHXa = false;
      bool fHHJwzhhFf = false;
      bool RHWXCReXBL = false;
      bool KSSVeerfTn = false;
      string RBpprYgKge;
      string UTiydtGKMT;
      string uxxCsDkBXO;
      string QwgWoUIqBk;
      string JFafkGEjDq;
      string xtlcMTEmwo;
      string nflSOYmMJJ;
      string kPJaKoWRRm;
      string zBygQVJEKV;
      string PUuMxdSIRL;
      string TqZtFhkKSW;
      string xlVJolhFCr;
      string OhCmsQTxdf;
      string WNAFSHaDah;
      string kykmXdzlWK;
      string wMGZxkomAo;
      string OnglzilPph;
      string LddTHQwOOP;
      string QhaSiKHaIg;
      string SmDlTwQzno;
      if(RBpprYgKge == TqZtFhkKSW){qjuoyShmRf = true;}
      else if(TqZtFhkKSW == RBpprYgKge){rREXrGIKkH = true;}
      if(UTiydtGKMT == xlVJolhFCr){naXkXgNOCo = true;}
      else if(xlVJolhFCr == UTiydtGKMT){cyVCRjMaej = true;}
      if(uxxCsDkBXO == OhCmsQTxdf){aLGIOYZrzK = true;}
      else if(OhCmsQTxdf == uxxCsDkBXO){oXlUluQzMa = true;}
      if(QwgWoUIqBk == WNAFSHaDah){zxaZXglkTQ = true;}
      else if(WNAFSHaDah == QwgWoUIqBk){XBiNepDFSV = true;}
      if(JFafkGEjDq == kykmXdzlWK){bUIbsrPROm = true;}
      else if(kykmXdzlWK == JFafkGEjDq){nppDPGcIco = true;}
      if(xtlcMTEmwo == wMGZxkomAo){iCwyNfclZZ = true;}
      else if(wMGZxkomAo == xtlcMTEmwo){YGWLMTfjlx = true;}
      if(nflSOYmMJJ == OnglzilPph){rpmGgqAxMp = true;}
      else if(OnglzilPph == nflSOYmMJJ){pIyKjaOHXa = true;}
      if(kPJaKoWRRm == LddTHQwOOP){tbtlMFDePW = true;}
      if(zBygQVJEKV == QhaSiKHaIg){IIcLbwBbLr = true;}
      if(PUuMxdSIRL == SmDlTwQzno){EzLtYlhBuB = true;}
      while(LddTHQwOOP == kPJaKoWRRm){fHHJwzhhFf = true;}
      while(QhaSiKHaIg == QhaSiKHaIg){RHWXCReXBL = true;}
      while(SmDlTwQzno == SmDlTwQzno){KSSVeerfTn = true;}
      if(qjuoyShmRf == true){qjuoyShmRf = false;}
      if(naXkXgNOCo == true){naXkXgNOCo = false;}
      if(aLGIOYZrzK == true){aLGIOYZrzK = false;}
      if(zxaZXglkTQ == true){zxaZXglkTQ = false;}
      if(bUIbsrPROm == true){bUIbsrPROm = false;}
      if(iCwyNfclZZ == true){iCwyNfclZZ = false;}
      if(rpmGgqAxMp == true){rpmGgqAxMp = false;}
      if(tbtlMFDePW == true){tbtlMFDePW = false;}
      if(IIcLbwBbLr == true){IIcLbwBbLr = false;}
      if(EzLtYlhBuB == true){EzLtYlhBuB = false;}
      if(rREXrGIKkH == true){rREXrGIKkH = false;}
      if(cyVCRjMaej == true){cyVCRjMaej = false;}
      if(oXlUluQzMa == true){oXlUluQzMa = false;}
      if(XBiNepDFSV == true){XBiNepDFSV = false;}
      if(nppDPGcIco == true){nppDPGcIco = false;}
      if(YGWLMTfjlx == true){YGWLMTfjlx = false;}
      if(pIyKjaOHXa == true){pIyKjaOHXa = false;}
      if(fHHJwzhhFf == true){fHHJwzhhFf = false;}
      if(RHWXCReXBL == true){RHWXCReXBL = false;}
      if(KSSVeerfTn == true){KSSVeerfTn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DYTZNREYXB
{ 
  void soLlptbObr()
  { 
      bool WzstrDXLYd = false;
      bool IBFjNeUGnz = false;
      bool CwfJiXJIHz = false;
      bool umhVGYFsVP = false;
      bool DYHjOKEqKl = false;
      bool QcuNBZSiLU = false;
      bool sPEYiVTidn = false;
      bool YajXucnwuX = false;
      bool TSyUiSqTUf = false;
      bool FVgBVnUhAr = false;
      bool qUMVNorWSX = false;
      bool kWnnAaQipP = false;
      bool ezOxiCthBG = false;
      bool IFuDfyFbHt = false;
      bool ZTBxtihsAu = false;
      bool WkrkNrGOlK = false;
      bool tJVLPeakHC = false;
      bool UobwpKyRDA = false;
      bool UAhGiWNKon = false;
      bool qpoxzPypgO = false;
      string sakDtHRpKF;
      string JdJFFTcJuu;
      string TGeEVByMon;
      string rMDcmMqrlH;
      string UtcBoWMNhd;
      string nKyrgmughr;
      string IEAVMxafRs;
      string bjWnZZcdOy;
      string okdKAhOKwA;
      string QKJsyPsGnr;
      string ufwoCEmKRH;
      string JRRjDXaoVe;
      string iPjQbQZdoJ;
      string fVoWCIooIw;
      string tEroqzsZoa;
      string oEkJIfweNk;
      string dJUIambtgu;
      string hkfYjeWuZc;
      string XznOTbkfNW;
      string LJbXRkijND;
      if(sakDtHRpKF == ufwoCEmKRH){WzstrDXLYd = true;}
      else if(ufwoCEmKRH == sakDtHRpKF){qUMVNorWSX = true;}
      if(JdJFFTcJuu == JRRjDXaoVe){IBFjNeUGnz = true;}
      else if(JRRjDXaoVe == JdJFFTcJuu){kWnnAaQipP = true;}
      if(TGeEVByMon == iPjQbQZdoJ){CwfJiXJIHz = true;}
      else if(iPjQbQZdoJ == TGeEVByMon){ezOxiCthBG = true;}
      if(rMDcmMqrlH == fVoWCIooIw){umhVGYFsVP = true;}
      else if(fVoWCIooIw == rMDcmMqrlH){IFuDfyFbHt = true;}
      if(UtcBoWMNhd == tEroqzsZoa){DYHjOKEqKl = true;}
      else if(tEroqzsZoa == UtcBoWMNhd){ZTBxtihsAu = true;}
      if(nKyrgmughr == oEkJIfweNk){QcuNBZSiLU = true;}
      else if(oEkJIfweNk == nKyrgmughr){WkrkNrGOlK = true;}
      if(IEAVMxafRs == dJUIambtgu){sPEYiVTidn = true;}
      else if(dJUIambtgu == IEAVMxafRs){tJVLPeakHC = true;}
      if(bjWnZZcdOy == hkfYjeWuZc){YajXucnwuX = true;}
      if(okdKAhOKwA == XznOTbkfNW){TSyUiSqTUf = true;}
      if(QKJsyPsGnr == LJbXRkijND){FVgBVnUhAr = true;}
      while(hkfYjeWuZc == bjWnZZcdOy){UobwpKyRDA = true;}
      while(XznOTbkfNW == XznOTbkfNW){UAhGiWNKon = true;}
      while(LJbXRkijND == LJbXRkijND){qpoxzPypgO = true;}
      if(WzstrDXLYd == true){WzstrDXLYd = false;}
      if(IBFjNeUGnz == true){IBFjNeUGnz = false;}
      if(CwfJiXJIHz == true){CwfJiXJIHz = false;}
      if(umhVGYFsVP == true){umhVGYFsVP = false;}
      if(DYHjOKEqKl == true){DYHjOKEqKl = false;}
      if(QcuNBZSiLU == true){QcuNBZSiLU = false;}
      if(sPEYiVTidn == true){sPEYiVTidn = false;}
      if(YajXucnwuX == true){YajXucnwuX = false;}
      if(TSyUiSqTUf == true){TSyUiSqTUf = false;}
      if(FVgBVnUhAr == true){FVgBVnUhAr = false;}
      if(qUMVNorWSX == true){qUMVNorWSX = false;}
      if(kWnnAaQipP == true){kWnnAaQipP = false;}
      if(ezOxiCthBG == true){ezOxiCthBG = false;}
      if(IFuDfyFbHt == true){IFuDfyFbHt = false;}
      if(ZTBxtihsAu == true){ZTBxtihsAu = false;}
      if(WkrkNrGOlK == true){WkrkNrGOlK = false;}
      if(tJVLPeakHC == true){tJVLPeakHC = false;}
      if(UobwpKyRDA == true){UobwpKyRDA = false;}
      if(UAhGiWNKon == true){UAhGiWNKon = false;}
      if(qpoxzPypgO == true){qpoxzPypgO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNDTBXKBBV
{ 
  void bfVMDddCoO()
  { 
      bool nIcuenPluI = false;
      bool mndpGJdFPX = false;
      bool zecPMPqbrR = false;
      bool lmiqyBddXL = false;
      bool COEopptHGd = false;
      bool EqqfoIeMhO = false;
      bool xntdVAEmrF = false;
      bool eAhEVjamZV = false;
      bool ViUNNuuDBp = false;
      bool VRuJNNUaSp = false;
      bool lHPBzEJlJF = false;
      bool gqmLrOSfQa = false;
      bool EBkBiNEXqH = false;
      bool OzUijOSTNI = false;
      bool kIswIddiQy = false;
      bool unKrkjVORl = false;
      bool AkuCphWEbd = false;
      bool wzRHouHorE = false;
      bool iVHrMancxz = false;
      bool rDBbIANqFZ = false;
      string yLfWeBaqsr;
      string FVyZOoKtlu;
      string RJAmBQSznH;
      string HdkJxJuAzY;
      string VZnTLlzGoC;
      string GIrSDoKsVO;
      string ibDkkbknbF;
      string tJuMYrVgaO;
      string QLKkBykRGH;
      string yBejptVCij;
      string BKdiIwNetL;
      string SdRHxWQRjl;
      string pShTGreKWd;
      string VSxqMGhacE;
      string kGXtoTiXlT;
      string dERwsibJcP;
      string QCIPpAfatq;
      string nonfAjunel;
      string JHYCzRBAyd;
      string dYyMmixHEn;
      if(yLfWeBaqsr == BKdiIwNetL){nIcuenPluI = true;}
      else if(BKdiIwNetL == yLfWeBaqsr){lHPBzEJlJF = true;}
      if(FVyZOoKtlu == SdRHxWQRjl){mndpGJdFPX = true;}
      else if(SdRHxWQRjl == FVyZOoKtlu){gqmLrOSfQa = true;}
      if(RJAmBQSznH == pShTGreKWd){zecPMPqbrR = true;}
      else if(pShTGreKWd == RJAmBQSznH){EBkBiNEXqH = true;}
      if(HdkJxJuAzY == VSxqMGhacE){lmiqyBddXL = true;}
      else if(VSxqMGhacE == HdkJxJuAzY){OzUijOSTNI = true;}
      if(VZnTLlzGoC == kGXtoTiXlT){COEopptHGd = true;}
      else if(kGXtoTiXlT == VZnTLlzGoC){kIswIddiQy = true;}
      if(GIrSDoKsVO == dERwsibJcP){EqqfoIeMhO = true;}
      else if(dERwsibJcP == GIrSDoKsVO){unKrkjVORl = true;}
      if(ibDkkbknbF == QCIPpAfatq){xntdVAEmrF = true;}
      else if(QCIPpAfatq == ibDkkbknbF){AkuCphWEbd = true;}
      if(tJuMYrVgaO == nonfAjunel){eAhEVjamZV = true;}
      if(QLKkBykRGH == JHYCzRBAyd){ViUNNuuDBp = true;}
      if(yBejptVCij == dYyMmixHEn){VRuJNNUaSp = true;}
      while(nonfAjunel == tJuMYrVgaO){wzRHouHorE = true;}
      while(JHYCzRBAyd == JHYCzRBAyd){iVHrMancxz = true;}
      while(dYyMmixHEn == dYyMmixHEn){rDBbIANqFZ = true;}
      if(nIcuenPluI == true){nIcuenPluI = false;}
      if(mndpGJdFPX == true){mndpGJdFPX = false;}
      if(zecPMPqbrR == true){zecPMPqbrR = false;}
      if(lmiqyBddXL == true){lmiqyBddXL = false;}
      if(COEopptHGd == true){COEopptHGd = false;}
      if(EqqfoIeMhO == true){EqqfoIeMhO = false;}
      if(xntdVAEmrF == true){xntdVAEmrF = false;}
      if(eAhEVjamZV == true){eAhEVjamZV = false;}
      if(ViUNNuuDBp == true){ViUNNuuDBp = false;}
      if(VRuJNNUaSp == true){VRuJNNUaSp = false;}
      if(lHPBzEJlJF == true){lHPBzEJlJF = false;}
      if(gqmLrOSfQa == true){gqmLrOSfQa = false;}
      if(EBkBiNEXqH == true){EBkBiNEXqH = false;}
      if(OzUijOSTNI == true){OzUijOSTNI = false;}
      if(kIswIddiQy == true){kIswIddiQy = false;}
      if(unKrkjVORl == true){unKrkjVORl = false;}
      if(AkuCphWEbd == true){AkuCphWEbd = false;}
      if(wzRHouHorE == true){wzRHouHorE = false;}
      if(iVHrMancxz == true){iVHrMancxz = false;}
      if(rDBbIANqFZ == true){rDBbIANqFZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XMXNATQUXW
{ 
  void eTcgrxtESM()
  { 
      bool mwYuXfyALI = false;
      bool DuHuDuSLCI = false;
      bool KIAgnTJode = false;
      bool SUzEsILtcq = false;
      bool bKAQxjzNsu = false;
      bool IIFYiewrHE = false;
      bool WJWfpiwDBt = false;
      bool iXiLgzHijD = false;
      bool TuuhWJOZVO = false;
      bool LTmYTRnUaN = false;
      bool nwLyMjZtqi = false;
      bool XMIDjaNnIg = false;
      bool UVgmhPkJqO = false;
      bool LmIVPXjwVm = false;
      bool iTilqyLinr = false;
      bool EzLssROYQw = false;
      bool zPDcXjElnM = false;
      bool qQSVxAmtui = false;
      bool EBVyKLaOcx = false;
      bool JKfYnSQFOG = false;
      string JnOrWIYyZI;
      string OkAJyCWwud;
      string sFwbEOmTSi;
      string NwwrZzGJzI;
      string GGGFkfgEQe;
      string lMASgDqmmI;
      string VFeptRnHjy;
      string uNxlWmyqpY;
      string ghCnxBwdKV;
      string ITVqlBbPLS;
      string qYURiYPNut;
      string FAxObnCpsr;
      string VKxOobrFAV;
      string LheWgHNkEX;
      string khhQQIWGPy;
      string ykVSwfbGbH;
      string gJNZiWUZgT;
      string aRlVHncfyg;
      string EkpBXZLMZA;
      string fHIwqbUIgs;
      if(JnOrWIYyZI == qYURiYPNut){mwYuXfyALI = true;}
      else if(qYURiYPNut == JnOrWIYyZI){nwLyMjZtqi = true;}
      if(OkAJyCWwud == FAxObnCpsr){DuHuDuSLCI = true;}
      else if(FAxObnCpsr == OkAJyCWwud){XMIDjaNnIg = true;}
      if(sFwbEOmTSi == VKxOobrFAV){KIAgnTJode = true;}
      else if(VKxOobrFAV == sFwbEOmTSi){UVgmhPkJqO = true;}
      if(NwwrZzGJzI == LheWgHNkEX){SUzEsILtcq = true;}
      else if(LheWgHNkEX == NwwrZzGJzI){LmIVPXjwVm = true;}
      if(GGGFkfgEQe == khhQQIWGPy){bKAQxjzNsu = true;}
      else if(khhQQIWGPy == GGGFkfgEQe){iTilqyLinr = true;}
      if(lMASgDqmmI == ykVSwfbGbH){IIFYiewrHE = true;}
      else if(ykVSwfbGbH == lMASgDqmmI){EzLssROYQw = true;}
      if(VFeptRnHjy == gJNZiWUZgT){WJWfpiwDBt = true;}
      else if(gJNZiWUZgT == VFeptRnHjy){zPDcXjElnM = true;}
      if(uNxlWmyqpY == aRlVHncfyg){iXiLgzHijD = true;}
      if(ghCnxBwdKV == EkpBXZLMZA){TuuhWJOZVO = true;}
      if(ITVqlBbPLS == fHIwqbUIgs){LTmYTRnUaN = true;}
      while(aRlVHncfyg == uNxlWmyqpY){qQSVxAmtui = true;}
      while(EkpBXZLMZA == EkpBXZLMZA){EBVyKLaOcx = true;}
      while(fHIwqbUIgs == fHIwqbUIgs){JKfYnSQFOG = true;}
      if(mwYuXfyALI == true){mwYuXfyALI = false;}
      if(DuHuDuSLCI == true){DuHuDuSLCI = false;}
      if(KIAgnTJode == true){KIAgnTJode = false;}
      if(SUzEsILtcq == true){SUzEsILtcq = false;}
      if(bKAQxjzNsu == true){bKAQxjzNsu = false;}
      if(IIFYiewrHE == true){IIFYiewrHE = false;}
      if(WJWfpiwDBt == true){WJWfpiwDBt = false;}
      if(iXiLgzHijD == true){iXiLgzHijD = false;}
      if(TuuhWJOZVO == true){TuuhWJOZVO = false;}
      if(LTmYTRnUaN == true){LTmYTRnUaN = false;}
      if(nwLyMjZtqi == true){nwLyMjZtqi = false;}
      if(XMIDjaNnIg == true){XMIDjaNnIg = false;}
      if(UVgmhPkJqO == true){UVgmhPkJqO = false;}
      if(LmIVPXjwVm == true){LmIVPXjwVm = false;}
      if(iTilqyLinr == true){iTilqyLinr = false;}
      if(EzLssROYQw == true){EzLssROYQw = false;}
      if(zPDcXjElnM == true){zPDcXjElnM = false;}
      if(qQSVxAmtui == true){qQSVxAmtui = false;}
      if(EBVyKLaOcx == true){EBVyKLaOcx = false;}
      if(JKfYnSQFOG == true){JKfYnSQFOG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HSMYRMYGOL
{ 
  void JQaWqbRPmE()
  { 
      bool tmqpqyPLGC = false;
      bool oozrilucrQ = false;
      bool sYXjPpFRiW = false;
      bool PhTCeFhKlZ = false;
      bool BGkmWgnWPV = false;
      bool RilVsVPHZB = false;
      bool sybjlGUxNc = false;
      bool DkqSOlmjNi = false;
      bool BhBNEfwyII = false;
      bool pZkkfCdAAP = false;
      bool LqJlRgrTGG = false;
      bool ietqzKwOfF = false;
      bool KWnEmczFlM = false;
      bool IljxWKYPwX = false;
      bool nbrCZKftkU = false;
      bool GOUtFnCEyn = false;
      bool glgsxwuwTn = false;
      bool lfSHRheldb = false;
      bool xFURGsQorh = false;
      bool ITQIpBuyEd = false;
      string tIUaSCXcRx;
      string acXtjjncOP;
      string dlkqrdqmpU;
      string SFTzhjJeTm;
      string EJIPwTrmCu;
      string eigRAHWchn;
      string KklxdUJYMz;
      string ZIIaKUdVuY;
      string kDjuojYBza;
      string NgwfbTWKka;
      string KTaDUWZFHe;
      string dBgJDGAqIt;
      string wHYllrLcyq;
      string xSjTOQcgaR;
      string KTtTwLAmbU;
      string SfBqeCtoRb;
      string KwGPhKRMul;
      string dTPpjcMFoZ;
      string rYAcXQRroL;
      string VnOyHNMdll;
      if(tIUaSCXcRx == KTaDUWZFHe){tmqpqyPLGC = true;}
      else if(KTaDUWZFHe == tIUaSCXcRx){LqJlRgrTGG = true;}
      if(acXtjjncOP == dBgJDGAqIt){oozrilucrQ = true;}
      else if(dBgJDGAqIt == acXtjjncOP){ietqzKwOfF = true;}
      if(dlkqrdqmpU == wHYllrLcyq){sYXjPpFRiW = true;}
      else if(wHYllrLcyq == dlkqrdqmpU){KWnEmczFlM = true;}
      if(SFTzhjJeTm == xSjTOQcgaR){PhTCeFhKlZ = true;}
      else if(xSjTOQcgaR == SFTzhjJeTm){IljxWKYPwX = true;}
      if(EJIPwTrmCu == KTtTwLAmbU){BGkmWgnWPV = true;}
      else if(KTtTwLAmbU == EJIPwTrmCu){nbrCZKftkU = true;}
      if(eigRAHWchn == SfBqeCtoRb){RilVsVPHZB = true;}
      else if(SfBqeCtoRb == eigRAHWchn){GOUtFnCEyn = true;}
      if(KklxdUJYMz == KwGPhKRMul){sybjlGUxNc = true;}
      else if(KwGPhKRMul == KklxdUJYMz){glgsxwuwTn = true;}
      if(ZIIaKUdVuY == dTPpjcMFoZ){DkqSOlmjNi = true;}
      if(kDjuojYBza == rYAcXQRroL){BhBNEfwyII = true;}
      if(NgwfbTWKka == VnOyHNMdll){pZkkfCdAAP = true;}
      while(dTPpjcMFoZ == ZIIaKUdVuY){lfSHRheldb = true;}
      while(rYAcXQRroL == rYAcXQRroL){xFURGsQorh = true;}
      while(VnOyHNMdll == VnOyHNMdll){ITQIpBuyEd = true;}
      if(tmqpqyPLGC == true){tmqpqyPLGC = false;}
      if(oozrilucrQ == true){oozrilucrQ = false;}
      if(sYXjPpFRiW == true){sYXjPpFRiW = false;}
      if(PhTCeFhKlZ == true){PhTCeFhKlZ = false;}
      if(BGkmWgnWPV == true){BGkmWgnWPV = false;}
      if(RilVsVPHZB == true){RilVsVPHZB = false;}
      if(sybjlGUxNc == true){sybjlGUxNc = false;}
      if(DkqSOlmjNi == true){DkqSOlmjNi = false;}
      if(BhBNEfwyII == true){BhBNEfwyII = false;}
      if(pZkkfCdAAP == true){pZkkfCdAAP = false;}
      if(LqJlRgrTGG == true){LqJlRgrTGG = false;}
      if(ietqzKwOfF == true){ietqzKwOfF = false;}
      if(KWnEmczFlM == true){KWnEmczFlM = false;}
      if(IljxWKYPwX == true){IljxWKYPwX = false;}
      if(nbrCZKftkU == true){nbrCZKftkU = false;}
      if(GOUtFnCEyn == true){GOUtFnCEyn = false;}
      if(glgsxwuwTn == true){glgsxwuwTn = false;}
      if(lfSHRheldb == true){lfSHRheldb = false;}
      if(xFURGsQorh == true){xFURGsQorh = false;}
      if(ITQIpBuyEd == true){ITQIpBuyEd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IUGKZEWGRJ
{ 
  void bcqhwHOjwb()
  { 
      bool KPfaRYhbQP = false;
      bool qmgGkEIoXI = false;
      bool PmqVFLEjcp = false;
      bool YGEjLcMlXN = false;
      bool LXuOxqpqrB = false;
      bool YynGEXYKUG = false;
      bool TxzaqjhxuI = false;
      bool qVQKxqrcXO = false;
      bool UNqaQZSyfn = false;
      bool DCRRsNYTXM = false;
      bool IswjJDhdJN = false;
      bool ewlFlFGYJQ = false;
      bool RjQGEoDzQj = false;
      bool SXEKGaRHQN = false;
      bool rnnRIHPLfn = false;
      bool GAKHuXboeU = false;
      bool zhNZtHqazK = false;
      bool nyHwXcwyyw = false;
      bool YrTccSNxPh = false;
      bool zccuNKaOWB = false;
      string QTyuduFEfY;
      string XYAwOIswNq;
      string HgEBlXOnSG;
      string zzmFuXNIoa;
      string WBXnhlpcBD;
      string SCJrwjOxIF;
      string fRkZYXkuAp;
      string ujHlTFIPSz;
      string hlmPmxpuIL;
      string JQAiuFQxPK;
      string AubKIitWXq;
      string azdJXseUma;
      string gplogdjYqN;
      string oKAIymKbHE;
      string DTWRjJlpLB;
      string auKncKIldd;
      string yVeKCPyVKj;
      string iCNiXNSUEW;
      string rsNplsALen;
      string eXxdGhnMPU;
      if(QTyuduFEfY == AubKIitWXq){KPfaRYhbQP = true;}
      else if(AubKIitWXq == QTyuduFEfY){IswjJDhdJN = true;}
      if(XYAwOIswNq == azdJXseUma){qmgGkEIoXI = true;}
      else if(azdJXseUma == XYAwOIswNq){ewlFlFGYJQ = true;}
      if(HgEBlXOnSG == gplogdjYqN){PmqVFLEjcp = true;}
      else if(gplogdjYqN == HgEBlXOnSG){RjQGEoDzQj = true;}
      if(zzmFuXNIoa == oKAIymKbHE){YGEjLcMlXN = true;}
      else if(oKAIymKbHE == zzmFuXNIoa){SXEKGaRHQN = true;}
      if(WBXnhlpcBD == DTWRjJlpLB){LXuOxqpqrB = true;}
      else if(DTWRjJlpLB == WBXnhlpcBD){rnnRIHPLfn = true;}
      if(SCJrwjOxIF == auKncKIldd){YynGEXYKUG = true;}
      else if(auKncKIldd == SCJrwjOxIF){GAKHuXboeU = true;}
      if(fRkZYXkuAp == yVeKCPyVKj){TxzaqjhxuI = true;}
      else if(yVeKCPyVKj == fRkZYXkuAp){zhNZtHqazK = true;}
      if(ujHlTFIPSz == iCNiXNSUEW){qVQKxqrcXO = true;}
      if(hlmPmxpuIL == rsNplsALen){UNqaQZSyfn = true;}
      if(JQAiuFQxPK == eXxdGhnMPU){DCRRsNYTXM = true;}
      while(iCNiXNSUEW == ujHlTFIPSz){nyHwXcwyyw = true;}
      while(rsNplsALen == rsNplsALen){YrTccSNxPh = true;}
      while(eXxdGhnMPU == eXxdGhnMPU){zccuNKaOWB = true;}
      if(KPfaRYhbQP == true){KPfaRYhbQP = false;}
      if(qmgGkEIoXI == true){qmgGkEIoXI = false;}
      if(PmqVFLEjcp == true){PmqVFLEjcp = false;}
      if(YGEjLcMlXN == true){YGEjLcMlXN = false;}
      if(LXuOxqpqrB == true){LXuOxqpqrB = false;}
      if(YynGEXYKUG == true){YynGEXYKUG = false;}
      if(TxzaqjhxuI == true){TxzaqjhxuI = false;}
      if(qVQKxqrcXO == true){qVQKxqrcXO = false;}
      if(UNqaQZSyfn == true){UNqaQZSyfn = false;}
      if(DCRRsNYTXM == true){DCRRsNYTXM = false;}
      if(IswjJDhdJN == true){IswjJDhdJN = false;}
      if(ewlFlFGYJQ == true){ewlFlFGYJQ = false;}
      if(RjQGEoDzQj == true){RjQGEoDzQj = false;}
      if(SXEKGaRHQN == true){SXEKGaRHQN = false;}
      if(rnnRIHPLfn == true){rnnRIHPLfn = false;}
      if(GAKHuXboeU == true){GAKHuXboeU = false;}
      if(zhNZtHqazK == true){zhNZtHqazK = false;}
      if(nyHwXcwyyw == true){nyHwXcwyyw = false;}
      if(YrTccSNxPh == true){YrTccSNxPh = false;}
      if(zccuNKaOWB == true){zccuNKaOWB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MZUYANCFQZ
{ 
  void ufVFYVkuTV()
  { 
      bool DktXwnbHdI = false;
      bool VqLZpHnxeO = false;
      bool WiFQIkOfPp = false;
      bool fUztcFrlrV = false;
      bool RhjInEjIUc = false;
      bool WKCgTTfcPK = false;
      bool ZuqmcArQxj = false;
      bool PBEIwnywbD = false;
      bool AFKlTVSSZI = false;
      bool ZOWhwVpxfn = false;
      bool MSLjNUFsjf = false;
      bool ViBLJUkFSH = false;
      bool gZqnKAeWMa = false;
      bool xBQnpgsZXz = false;
      bool PYhtmpMKXa = false;
      bool kkdYGmbWZM = false;
      bool pigJhUSNVb = false;
      bool aKgTrHqwBT = false;
      bool mTykpLWrgD = false;
      bool FVALJfrYLS = false;
      string QGhqlLNMVl;
      string HukzxTzZcR;
      string eZdDEeJtBO;
      string gaPMBVZOWG;
      string tNrtKaKhPb;
      string jmbIlpbelH;
      string CTKHEgeYya;
      string tjCWWQgjrd;
      string TbeZdtzHZK;
      string sucPDaDkpd;
      string ukingAkEkV;
      string IrlImZnjdK;
      string gXzmhzGlSw;
      string MwtOhirprd;
      string ItVECBIUbd;
      string lSGewXlwGg;
      string syloILxXaE;
      string gyqzBmCukf;
      string qlKoKsoORJ;
      string wwiLjKHgup;
      if(QGhqlLNMVl == ukingAkEkV){DktXwnbHdI = true;}
      else if(ukingAkEkV == QGhqlLNMVl){MSLjNUFsjf = true;}
      if(HukzxTzZcR == IrlImZnjdK){VqLZpHnxeO = true;}
      else if(IrlImZnjdK == HukzxTzZcR){ViBLJUkFSH = true;}
      if(eZdDEeJtBO == gXzmhzGlSw){WiFQIkOfPp = true;}
      else if(gXzmhzGlSw == eZdDEeJtBO){gZqnKAeWMa = true;}
      if(gaPMBVZOWG == MwtOhirprd){fUztcFrlrV = true;}
      else if(MwtOhirprd == gaPMBVZOWG){xBQnpgsZXz = true;}
      if(tNrtKaKhPb == ItVECBIUbd){RhjInEjIUc = true;}
      else if(ItVECBIUbd == tNrtKaKhPb){PYhtmpMKXa = true;}
      if(jmbIlpbelH == lSGewXlwGg){WKCgTTfcPK = true;}
      else if(lSGewXlwGg == jmbIlpbelH){kkdYGmbWZM = true;}
      if(CTKHEgeYya == syloILxXaE){ZuqmcArQxj = true;}
      else if(syloILxXaE == CTKHEgeYya){pigJhUSNVb = true;}
      if(tjCWWQgjrd == gyqzBmCukf){PBEIwnywbD = true;}
      if(TbeZdtzHZK == qlKoKsoORJ){AFKlTVSSZI = true;}
      if(sucPDaDkpd == wwiLjKHgup){ZOWhwVpxfn = true;}
      while(gyqzBmCukf == tjCWWQgjrd){aKgTrHqwBT = true;}
      while(qlKoKsoORJ == qlKoKsoORJ){mTykpLWrgD = true;}
      while(wwiLjKHgup == wwiLjKHgup){FVALJfrYLS = true;}
      if(DktXwnbHdI == true){DktXwnbHdI = false;}
      if(VqLZpHnxeO == true){VqLZpHnxeO = false;}
      if(WiFQIkOfPp == true){WiFQIkOfPp = false;}
      if(fUztcFrlrV == true){fUztcFrlrV = false;}
      if(RhjInEjIUc == true){RhjInEjIUc = false;}
      if(WKCgTTfcPK == true){WKCgTTfcPK = false;}
      if(ZuqmcArQxj == true){ZuqmcArQxj = false;}
      if(PBEIwnywbD == true){PBEIwnywbD = false;}
      if(AFKlTVSSZI == true){AFKlTVSSZI = false;}
      if(ZOWhwVpxfn == true){ZOWhwVpxfn = false;}
      if(MSLjNUFsjf == true){MSLjNUFsjf = false;}
      if(ViBLJUkFSH == true){ViBLJUkFSH = false;}
      if(gZqnKAeWMa == true){gZqnKAeWMa = false;}
      if(xBQnpgsZXz == true){xBQnpgsZXz = false;}
      if(PYhtmpMKXa == true){PYhtmpMKXa = false;}
      if(kkdYGmbWZM == true){kkdYGmbWZM = false;}
      if(pigJhUSNVb == true){pigJhUSNVb = false;}
      if(aKgTrHqwBT == true){aKgTrHqwBT = false;}
      if(mTykpLWrgD == true){mTykpLWrgD = false;}
      if(FVALJfrYLS == true){FVALJfrYLS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OYXMGPKTWF
{ 
  void SizICDYDBe()
  { 
      bool FCsiAOMZan = false;
      bool htBTCcargL = false;
      bool IaFFQlGuVa = false;
      bool tRcdThOLxA = false;
      bool OimriTQVxg = false;
      bool kzpUgexmSN = false;
      bool HREzsPRWzT = false;
      bool OOtgxZmMWw = false;
      bool UjyooubHxo = false;
      bool jasisxdnzT = false;
      bool CtWcRWFIXH = false;
      bool rkQVsWSPJy = false;
      bool nJZKjmULnz = false;
      bool uzMCtaNUWS = false;
      bool oSjpxzKWpV = false;
      bool dOdBfrTMse = false;
      bool BsUXLsXNbR = false;
      bool JysqIUZjNj = false;
      bool cyURVgULWC = false;
      bool HAbqRwxMdE = false;
      string oGzTzTWyCx;
      string dYEcVkFhdn;
      string uMdCqArrRT;
      string OcckPodELa;
      string VWQRxZAItS;
      string MBynubcxby;
      string bdgiiAwSNf;
      string GBVDRYwLER;
      string AixyHNdopm;
      string LgbMzrogix;
      string dguNLLeuVV;
      string fQsKysfhbU;
      string VHcZUYYJEZ;
      string iObHmSnimw;
      string hiSTGtnQOF;
      string LHFNaVEUsm;
      string lVqumRokWe;
      string FxufmmnJTZ;
      string kIuyOaINfQ;
      string OSpzJLrWfo;
      if(oGzTzTWyCx == dguNLLeuVV){FCsiAOMZan = true;}
      else if(dguNLLeuVV == oGzTzTWyCx){CtWcRWFIXH = true;}
      if(dYEcVkFhdn == fQsKysfhbU){htBTCcargL = true;}
      else if(fQsKysfhbU == dYEcVkFhdn){rkQVsWSPJy = true;}
      if(uMdCqArrRT == VHcZUYYJEZ){IaFFQlGuVa = true;}
      else if(VHcZUYYJEZ == uMdCqArrRT){nJZKjmULnz = true;}
      if(OcckPodELa == iObHmSnimw){tRcdThOLxA = true;}
      else if(iObHmSnimw == OcckPodELa){uzMCtaNUWS = true;}
      if(VWQRxZAItS == hiSTGtnQOF){OimriTQVxg = true;}
      else if(hiSTGtnQOF == VWQRxZAItS){oSjpxzKWpV = true;}
      if(MBynubcxby == LHFNaVEUsm){kzpUgexmSN = true;}
      else if(LHFNaVEUsm == MBynubcxby){dOdBfrTMse = true;}
      if(bdgiiAwSNf == lVqumRokWe){HREzsPRWzT = true;}
      else if(lVqumRokWe == bdgiiAwSNf){BsUXLsXNbR = true;}
      if(GBVDRYwLER == FxufmmnJTZ){OOtgxZmMWw = true;}
      if(AixyHNdopm == kIuyOaINfQ){UjyooubHxo = true;}
      if(LgbMzrogix == OSpzJLrWfo){jasisxdnzT = true;}
      while(FxufmmnJTZ == GBVDRYwLER){JysqIUZjNj = true;}
      while(kIuyOaINfQ == kIuyOaINfQ){cyURVgULWC = true;}
      while(OSpzJLrWfo == OSpzJLrWfo){HAbqRwxMdE = true;}
      if(FCsiAOMZan == true){FCsiAOMZan = false;}
      if(htBTCcargL == true){htBTCcargL = false;}
      if(IaFFQlGuVa == true){IaFFQlGuVa = false;}
      if(tRcdThOLxA == true){tRcdThOLxA = false;}
      if(OimriTQVxg == true){OimriTQVxg = false;}
      if(kzpUgexmSN == true){kzpUgexmSN = false;}
      if(HREzsPRWzT == true){HREzsPRWzT = false;}
      if(OOtgxZmMWw == true){OOtgxZmMWw = false;}
      if(UjyooubHxo == true){UjyooubHxo = false;}
      if(jasisxdnzT == true){jasisxdnzT = false;}
      if(CtWcRWFIXH == true){CtWcRWFIXH = false;}
      if(rkQVsWSPJy == true){rkQVsWSPJy = false;}
      if(nJZKjmULnz == true){nJZKjmULnz = false;}
      if(uzMCtaNUWS == true){uzMCtaNUWS = false;}
      if(oSjpxzKWpV == true){oSjpxzKWpV = false;}
      if(dOdBfrTMse == true){dOdBfrTMse = false;}
      if(BsUXLsXNbR == true){BsUXLsXNbR = false;}
      if(JysqIUZjNj == true){JysqIUZjNj = false;}
      if(cyURVgULWC == true){cyURVgULWC = false;}
      if(HAbqRwxMdE == true){HAbqRwxMdE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BSSTMSPWZR
{ 
  void DNesFPGOiJ()
  { 
      bool doAClyarqR = false;
      bool ImzILdZgrZ = false;
      bool CzojLJSILF = false;
      bool rRHUmXEKMB = false;
      bool WLHqdQzCkZ = false;
      bool wdoZlezQqc = false;
      bool fSfkZqeeUm = false;
      bool ZOTpCqryFt = false;
      bool JPWlIObhhI = false;
      bool YnTjVEeVQm = false;
      bool kUhyzgJzWu = false;
      bool lBKwSPusbL = false;
      bool PwxMNltjUy = false;
      bool LWgSJohYlb = false;
      bool EbLmVWcXQF = false;
      bool IlsFWnXUjN = false;
      bool mZdXiPTqmd = false;
      bool gWGAGmkKpp = false;
      bool IWSOoZcbwU = false;
      bool QNnYodymDG = false;
      string WlkZwrqHda;
      string HMNSWCCjHr;
      string IiwQeGDRlb;
      string JxqIAikjWA;
      string TZMXXCegJq;
      string dfgtjmoUtp;
      string nYUBQJVERn;
      string QRMGYhVYrb;
      string aWIuydQwYM;
      string sPogMtFKGN;
      string gaOVZLSZVB;
      string RQcRPQQZDm;
      string sYeFuBbetd;
      string cLRduzIlUm;
      string KpZXucmXRu;
      string deHTUHuJaY;
      string imfrXGyyWP;
      string IeEPbCzHJR;
      string NENzAxDyIm;
      string EzLwDWKhzo;
      if(WlkZwrqHda == gaOVZLSZVB){doAClyarqR = true;}
      else if(gaOVZLSZVB == WlkZwrqHda){kUhyzgJzWu = true;}
      if(HMNSWCCjHr == RQcRPQQZDm){ImzILdZgrZ = true;}
      else if(RQcRPQQZDm == HMNSWCCjHr){lBKwSPusbL = true;}
      if(IiwQeGDRlb == sYeFuBbetd){CzojLJSILF = true;}
      else if(sYeFuBbetd == IiwQeGDRlb){PwxMNltjUy = true;}
      if(JxqIAikjWA == cLRduzIlUm){rRHUmXEKMB = true;}
      else if(cLRduzIlUm == JxqIAikjWA){LWgSJohYlb = true;}
      if(TZMXXCegJq == KpZXucmXRu){WLHqdQzCkZ = true;}
      else if(KpZXucmXRu == TZMXXCegJq){EbLmVWcXQF = true;}
      if(dfgtjmoUtp == deHTUHuJaY){wdoZlezQqc = true;}
      else if(deHTUHuJaY == dfgtjmoUtp){IlsFWnXUjN = true;}
      if(nYUBQJVERn == imfrXGyyWP){fSfkZqeeUm = true;}
      else if(imfrXGyyWP == nYUBQJVERn){mZdXiPTqmd = true;}
      if(QRMGYhVYrb == IeEPbCzHJR){ZOTpCqryFt = true;}
      if(aWIuydQwYM == NENzAxDyIm){JPWlIObhhI = true;}
      if(sPogMtFKGN == EzLwDWKhzo){YnTjVEeVQm = true;}
      while(IeEPbCzHJR == QRMGYhVYrb){gWGAGmkKpp = true;}
      while(NENzAxDyIm == NENzAxDyIm){IWSOoZcbwU = true;}
      while(EzLwDWKhzo == EzLwDWKhzo){QNnYodymDG = true;}
      if(doAClyarqR == true){doAClyarqR = false;}
      if(ImzILdZgrZ == true){ImzILdZgrZ = false;}
      if(CzojLJSILF == true){CzojLJSILF = false;}
      if(rRHUmXEKMB == true){rRHUmXEKMB = false;}
      if(WLHqdQzCkZ == true){WLHqdQzCkZ = false;}
      if(wdoZlezQqc == true){wdoZlezQqc = false;}
      if(fSfkZqeeUm == true){fSfkZqeeUm = false;}
      if(ZOTpCqryFt == true){ZOTpCqryFt = false;}
      if(JPWlIObhhI == true){JPWlIObhhI = false;}
      if(YnTjVEeVQm == true){YnTjVEeVQm = false;}
      if(kUhyzgJzWu == true){kUhyzgJzWu = false;}
      if(lBKwSPusbL == true){lBKwSPusbL = false;}
      if(PwxMNltjUy == true){PwxMNltjUy = false;}
      if(LWgSJohYlb == true){LWgSJohYlb = false;}
      if(EbLmVWcXQF == true){EbLmVWcXQF = false;}
      if(IlsFWnXUjN == true){IlsFWnXUjN = false;}
      if(mZdXiPTqmd == true){mZdXiPTqmd = false;}
      if(gWGAGmkKpp == true){gWGAGmkKpp = false;}
      if(IWSOoZcbwU == true){IWSOoZcbwU = false;}
      if(QNnYodymDG == true){QNnYodymDG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZMJUGNTSZJ
{ 
  void eYzSeorqUe()
  { 
      bool HlbuhMyyAK = false;
      bool lVUiPOuVCV = false;
      bool IXWbwgbTQK = false;
      bool WtuSBaIKfW = false;
      bool XlHJapwQBa = false;
      bool EnyrXjOAyB = false;
      bool kdgpmraBhn = false;
      bool GkofxVPMAG = false;
      bool kKSoGiuDtQ = false;
      bool MHLelsEQWi = false;
      bool OtiMUSyStB = false;
      bool TBArQZLrjD = false;
      bool wWHQbyYKsD = false;
      bool RzpQqpaFTm = false;
      bool kbJrxKHTOL = false;
      bool hLgSmrmSjV = false;
      bool tmYpjUKiAZ = false;
      bool yFXwSTNOTQ = false;
      bool qEuhVFRXdz = false;
      bool DIUysxDSIb = false;
      string JfppqXTugO;
      string fRoRRkuIwD;
      string YhnHyCHMCs;
      string nZoVjfOssh;
      string SFpxapPbbo;
      string DawsRaqirn;
      string PGrmZGbThl;
      string VCOOjSrqfI;
      string mejNpNcuEI;
      string nfAERLNCXU;
      string NuspSALhJy;
      string iACjAjWexL;
      string cgPYxpBJwX;
      string FpTLtrlstp;
      string BulGZncQDg;
      string oiFLqgfUsc;
      string zBkkrsfqoI;
      string yckHKgtJzJ;
      string MjGOiWjITN;
      string MRAQpzKANg;
      if(JfppqXTugO == NuspSALhJy){HlbuhMyyAK = true;}
      else if(NuspSALhJy == JfppqXTugO){OtiMUSyStB = true;}
      if(fRoRRkuIwD == iACjAjWexL){lVUiPOuVCV = true;}
      else if(iACjAjWexL == fRoRRkuIwD){TBArQZLrjD = true;}
      if(YhnHyCHMCs == cgPYxpBJwX){IXWbwgbTQK = true;}
      else if(cgPYxpBJwX == YhnHyCHMCs){wWHQbyYKsD = true;}
      if(nZoVjfOssh == FpTLtrlstp){WtuSBaIKfW = true;}
      else if(FpTLtrlstp == nZoVjfOssh){RzpQqpaFTm = true;}
      if(SFpxapPbbo == BulGZncQDg){XlHJapwQBa = true;}
      else if(BulGZncQDg == SFpxapPbbo){kbJrxKHTOL = true;}
      if(DawsRaqirn == oiFLqgfUsc){EnyrXjOAyB = true;}
      else if(oiFLqgfUsc == DawsRaqirn){hLgSmrmSjV = true;}
      if(PGrmZGbThl == zBkkrsfqoI){kdgpmraBhn = true;}
      else if(zBkkrsfqoI == PGrmZGbThl){tmYpjUKiAZ = true;}
      if(VCOOjSrqfI == yckHKgtJzJ){GkofxVPMAG = true;}
      if(mejNpNcuEI == MjGOiWjITN){kKSoGiuDtQ = true;}
      if(nfAERLNCXU == MRAQpzKANg){MHLelsEQWi = true;}
      while(yckHKgtJzJ == VCOOjSrqfI){yFXwSTNOTQ = true;}
      while(MjGOiWjITN == MjGOiWjITN){qEuhVFRXdz = true;}
      while(MRAQpzKANg == MRAQpzKANg){DIUysxDSIb = true;}
      if(HlbuhMyyAK == true){HlbuhMyyAK = false;}
      if(lVUiPOuVCV == true){lVUiPOuVCV = false;}
      if(IXWbwgbTQK == true){IXWbwgbTQK = false;}
      if(WtuSBaIKfW == true){WtuSBaIKfW = false;}
      if(XlHJapwQBa == true){XlHJapwQBa = false;}
      if(EnyrXjOAyB == true){EnyrXjOAyB = false;}
      if(kdgpmraBhn == true){kdgpmraBhn = false;}
      if(GkofxVPMAG == true){GkofxVPMAG = false;}
      if(kKSoGiuDtQ == true){kKSoGiuDtQ = false;}
      if(MHLelsEQWi == true){MHLelsEQWi = false;}
      if(OtiMUSyStB == true){OtiMUSyStB = false;}
      if(TBArQZLrjD == true){TBArQZLrjD = false;}
      if(wWHQbyYKsD == true){wWHQbyYKsD = false;}
      if(RzpQqpaFTm == true){RzpQqpaFTm = false;}
      if(kbJrxKHTOL == true){kbJrxKHTOL = false;}
      if(hLgSmrmSjV == true){hLgSmrmSjV = false;}
      if(tmYpjUKiAZ == true){tmYpjUKiAZ = false;}
      if(yFXwSTNOTQ == true){yFXwSTNOTQ = false;}
      if(qEuhVFRXdz == true){qEuhVFRXdz = false;}
      if(DIUysxDSIb == true){DIUysxDSIb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DOENBLLMKV
{ 
  void pRAthGJiRB()
  { 
      bool OWSEbjeGOU = false;
      bool HDnspAjRiI = false;
      bool lUjPoZxyoC = false;
      bool RBcLCRfHsa = false;
      bool LMMOXzbkpU = false;
      bool jPTpitlDPC = false;
      bool lgQLDGabqX = false;
      bool TbYIwYIVqo = false;
      bool xLHUSBgmbI = false;
      bool ecrpneuALR = false;
      bool YztRAHqKsJ = false;
      bool kQMZFaYwsB = false;
      bool YmAhsqjiUQ = false;
      bool dIJYQxRpTK = false;
      bool KWsSWNQRjM = false;
      bool GyGKrkzLYJ = false;
      bool XIpbfcHmJI = false;
      bool JhchpCthLe = false;
      bool aRyHKeBzgf = false;
      bool xFRKlCfQls = false;
      string YWPZOARAbT;
      string SuOTPiJGLe;
      string NxZxgGNSkM;
      string HCftsRjtcf;
      string dONlEbWBmL;
      string djHRyaxSrH;
      string myPPLPOTZy;
      string yPdfBzjmsE;
      string jMfYiXuNwR;
      string URBUrezyZn;
      string MCboMNGaQy;
      string qJYmXaSpfn;
      string TBXHcgNImW;
      string zkMEqgjqLU;
      string QUxxaLrOwR;
      string LIRlULdTLf;
      string zxmtzFwUuq;
      string pbdKWzEafR;
      string ozMUKpTajf;
      string CPefVTgDyU;
      if(YWPZOARAbT == MCboMNGaQy){OWSEbjeGOU = true;}
      else if(MCboMNGaQy == YWPZOARAbT){YztRAHqKsJ = true;}
      if(SuOTPiJGLe == qJYmXaSpfn){HDnspAjRiI = true;}
      else if(qJYmXaSpfn == SuOTPiJGLe){kQMZFaYwsB = true;}
      if(NxZxgGNSkM == TBXHcgNImW){lUjPoZxyoC = true;}
      else if(TBXHcgNImW == NxZxgGNSkM){YmAhsqjiUQ = true;}
      if(HCftsRjtcf == zkMEqgjqLU){RBcLCRfHsa = true;}
      else if(zkMEqgjqLU == HCftsRjtcf){dIJYQxRpTK = true;}
      if(dONlEbWBmL == QUxxaLrOwR){LMMOXzbkpU = true;}
      else if(QUxxaLrOwR == dONlEbWBmL){KWsSWNQRjM = true;}
      if(djHRyaxSrH == LIRlULdTLf){jPTpitlDPC = true;}
      else if(LIRlULdTLf == djHRyaxSrH){GyGKrkzLYJ = true;}
      if(myPPLPOTZy == zxmtzFwUuq){lgQLDGabqX = true;}
      else if(zxmtzFwUuq == myPPLPOTZy){XIpbfcHmJI = true;}
      if(yPdfBzjmsE == pbdKWzEafR){TbYIwYIVqo = true;}
      if(jMfYiXuNwR == ozMUKpTajf){xLHUSBgmbI = true;}
      if(URBUrezyZn == CPefVTgDyU){ecrpneuALR = true;}
      while(pbdKWzEafR == yPdfBzjmsE){JhchpCthLe = true;}
      while(ozMUKpTajf == ozMUKpTajf){aRyHKeBzgf = true;}
      while(CPefVTgDyU == CPefVTgDyU){xFRKlCfQls = true;}
      if(OWSEbjeGOU == true){OWSEbjeGOU = false;}
      if(HDnspAjRiI == true){HDnspAjRiI = false;}
      if(lUjPoZxyoC == true){lUjPoZxyoC = false;}
      if(RBcLCRfHsa == true){RBcLCRfHsa = false;}
      if(LMMOXzbkpU == true){LMMOXzbkpU = false;}
      if(jPTpitlDPC == true){jPTpitlDPC = false;}
      if(lgQLDGabqX == true){lgQLDGabqX = false;}
      if(TbYIwYIVqo == true){TbYIwYIVqo = false;}
      if(xLHUSBgmbI == true){xLHUSBgmbI = false;}
      if(ecrpneuALR == true){ecrpneuALR = false;}
      if(YztRAHqKsJ == true){YztRAHqKsJ = false;}
      if(kQMZFaYwsB == true){kQMZFaYwsB = false;}
      if(YmAhsqjiUQ == true){YmAhsqjiUQ = false;}
      if(dIJYQxRpTK == true){dIJYQxRpTK = false;}
      if(KWsSWNQRjM == true){KWsSWNQRjM = false;}
      if(GyGKrkzLYJ == true){GyGKrkzLYJ = false;}
      if(XIpbfcHmJI == true){XIpbfcHmJI = false;}
      if(JhchpCthLe == true){JhchpCthLe = false;}
      if(aRyHKeBzgf == true){aRyHKeBzgf = false;}
      if(xFRKlCfQls == true){xFRKlCfQls = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MNXITMHQPX
{ 
  void sKKhsWdjAz()
  { 
      bool uuVnQNrHou = false;
      bool hCTjXeSIjB = false;
      bool yeXFmPwiGQ = false;
      bool QQQDHlWKUp = false;
      bool zQdkhpdfjs = false;
      bool VCtwpPXQAA = false;
      bool QIBXdRlPbl = false;
      bool IIntChBlXw = false;
      bool lQzMuOVTMq = false;
      bool OFJTYpPFHQ = false;
      bool DNDykNNAsI = false;
      bool OksENAJncO = false;
      bool uSDkWCyUUM = false;
      bool RueHsYNBag = false;
      bool BVZEcdMFFY = false;
      bool gabrUkJSai = false;
      bool PsfgpSFkKo = false;
      bool mHMwNZrzHs = false;
      bool orOufqSmlH = false;
      bool PtarQIpsNK = false;
      string ZUoGEmaqgI;
      string sKXzrVlPPM;
      string RSjTNdpXhA;
      string EsRCApexly;
      string szsMHhtPkf;
      string wNbinGjVsa;
      string xCIfDAsUyB;
      string qncRSSYXLf;
      string jZmCEpQhNt;
      string FJEKBppNIH;
      string nYQinHjKQV;
      string hMJMqWPFaM;
      string iLGEwhjSPc;
      string bKOEqKJDOw;
      string GGRrLsAqTd;
      string ZjluXbRLmG;
      string XRtmsWyEUf;
      string NMqeGctOrC;
      string hrykDqXSfP;
      string sxPHYoLdyo;
      if(ZUoGEmaqgI == nYQinHjKQV){uuVnQNrHou = true;}
      else if(nYQinHjKQV == ZUoGEmaqgI){DNDykNNAsI = true;}
      if(sKXzrVlPPM == hMJMqWPFaM){hCTjXeSIjB = true;}
      else if(hMJMqWPFaM == sKXzrVlPPM){OksENAJncO = true;}
      if(RSjTNdpXhA == iLGEwhjSPc){yeXFmPwiGQ = true;}
      else if(iLGEwhjSPc == RSjTNdpXhA){uSDkWCyUUM = true;}
      if(EsRCApexly == bKOEqKJDOw){QQQDHlWKUp = true;}
      else if(bKOEqKJDOw == EsRCApexly){RueHsYNBag = true;}
      if(szsMHhtPkf == GGRrLsAqTd){zQdkhpdfjs = true;}
      else if(GGRrLsAqTd == szsMHhtPkf){BVZEcdMFFY = true;}
      if(wNbinGjVsa == ZjluXbRLmG){VCtwpPXQAA = true;}
      else if(ZjluXbRLmG == wNbinGjVsa){gabrUkJSai = true;}
      if(xCIfDAsUyB == XRtmsWyEUf){QIBXdRlPbl = true;}
      else if(XRtmsWyEUf == xCIfDAsUyB){PsfgpSFkKo = true;}
      if(qncRSSYXLf == NMqeGctOrC){IIntChBlXw = true;}
      if(jZmCEpQhNt == hrykDqXSfP){lQzMuOVTMq = true;}
      if(FJEKBppNIH == sxPHYoLdyo){OFJTYpPFHQ = true;}
      while(NMqeGctOrC == qncRSSYXLf){mHMwNZrzHs = true;}
      while(hrykDqXSfP == hrykDqXSfP){orOufqSmlH = true;}
      while(sxPHYoLdyo == sxPHYoLdyo){PtarQIpsNK = true;}
      if(uuVnQNrHou == true){uuVnQNrHou = false;}
      if(hCTjXeSIjB == true){hCTjXeSIjB = false;}
      if(yeXFmPwiGQ == true){yeXFmPwiGQ = false;}
      if(QQQDHlWKUp == true){QQQDHlWKUp = false;}
      if(zQdkhpdfjs == true){zQdkhpdfjs = false;}
      if(VCtwpPXQAA == true){VCtwpPXQAA = false;}
      if(QIBXdRlPbl == true){QIBXdRlPbl = false;}
      if(IIntChBlXw == true){IIntChBlXw = false;}
      if(lQzMuOVTMq == true){lQzMuOVTMq = false;}
      if(OFJTYpPFHQ == true){OFJTYpPFHQ = false;}
      if(DNDykNNAsI == true){DNDykNNAsI = false;}
      if(OksENAJncO == true){OksENAJncO = false;}
      if(uSDkWCyUUM == true){uSDkWCyUUM = false;}
      if(RueHsYNBag == true){RueHsYNBag = false;}
      if(BVZEcdMFFY == true){BVZEcdMFFY = false;}
      if(gabrUkJSai == true){gabrUkJSai = false;}
      if(PsfgpSFkKo == true){PsfgpSFkKo = false;}
      if(mHMwNZrzHs == true){mHMwNZrzHs = false;}
      if(orOufqSmlH == true){orOufqSmlH = false;}
      if(PtarQIpsNK == true){PtarQIpsNK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NYZLYSOAKO
{ 
  void mGqzqrkWnu()
  { 
      bool VOBVRngeTB = false;
      bool oyARaZTXOk = false;
      bool BOrXHXMMsl = false;
      bool UriclWyhml = false;
      bool DofjtUfTZQ = false;
      bool URHTaHWdNt = false;
      bool aUkgfxOWeE = false;
      bool blkchMhHcm = false;
      bool rrmcRDjPCd = false;
      bool ATTrKiEzEx = false;
      bool FInUnigekO = false;
      bool ZOBaCigIPc = false;
      bool NyUBDHRrRz = false;
      bool HiDfgiDRni = false;
      bool WFemElSspb = false;
      bool BwiajGnmQf = false;
      bool QnMlGqLVsS = false;
      bool ePTgGHTgwR = false;
      bool oYCpxLzbua = false;
      bool uQAIRhrrgN = false;
      string YPuwwPOmJL;
      string UCiUNnowxl;
      string MTfegHXdCF;
      string nSRmKclWSG;
      string eITEqOyXCt;
      string DCuGHFjQPo;
      string rjjDXBkuKk;
      string BRdpGEzanS;
      string IAbHCkXLeE;
      string sVHcOtXQgo;
      string dDMQskYEAD;
      string FIcxfrIbBm;
      string dZQFreKAbL;
      string fityoFmKOQ;
      string MSKbzjsKwW;
      string luOtLEmGYN;
      string ZXcnWVOdIa;
      string EyNjZKOnGH;
      string lAEFZkTAlj;
      string SfkBpnoWEc;
      if(YPuwwPOmJL == dDMQskYEAD){VOBVRngeTB = true;}
      else if(dDMQskYEAD == YPuwwPOmJL){FInUnigekO = true;}
      if(UCiUNnowxl == FIcxfrIbBm){oyARaZTXOk = true;}
      else if(FIcxfrIbBm == UCiUNnowxl){ZOBaCigIPc = true;}
      if(MTfegHXdCF == dZQFreKAbL){BOrXHXMMsl = true;}
      else if(dZQFreKAbL == MTfegHXdCF){NyUBDHRrRz = true;}
      if(nSRmKclWSG == fityoFmKOQ){UriclWyhml = true;}
      else if(fityoFmKOQ == nSRmKclWSG){HiDfgiDRni = true;}
      if(eITEqOyXCt == MSKbzjsKwW){DofjtUfTZQ = true;}
      else if(MSKbzjsKwW == eITEqOyXCt){WFemElSspb = true;}
      if(DCuGHFjQPo == luOtLEmGYN){URHTaHWdNt = true;}
      else if(luOtLEmGYN == DCuGHFjQPo){BwiajGnmQf = true;}
      if(rjjDXBkuKk == ZXcnWVOdIa){aUkgfxOWeE = true;}
      else if(ZXcnWVOdIa == rjjDXBkuKk){QnMlGqLVsS = true;}
      if(BRdpGEzanS == EyNjZKOnGH){blkchMhHcm = true;}
      if(IAbHCkXLeE == lAEFZkTAlj){rrmcRDjPCd = true;}
      if(sVHcOtXQgo == SfkBpnoWEc){ATTrKiEzEx = true;}
      while(EyNjZKOnGH == BRdpGEzanS){ePTgGHTgwR = true;}
      while(lAEFZkTAlj == lAEFZkTAlj){oYCpxLzbua = true;}
      while(SfkBpnoWEc == SfkBpnoWEc){uQAIRhrrgN = true;}
      if(VOBVRngeTB == true){VOBVRngeTB = false;}
      if(oyARaZTXOk == true){oyARaZTXOk = false;}
      if(BOrXHXMMsl == true){BOrXHXMMsl = false;}
      if(UriclWyhml == true){UriclWyhml = false;}
      if(DofjtUfTZQ == true){DofjtUfTZQ = false;}
      if(URHTaHWdNt == true){URHTaHWdNt = false;}
      if(aUkgfxOWeE == true){aUkgfxOWeE = false;}
      if(blkchMhHcm == true){blkchMhHcm = false;}
      if(rrmcRDjPCd == true){rrmcRDjPCd = false;}
      if(ATTrKiEzEx == true){ATTrKiEzEx = false;}
      if(FInUnigekO == true){FInUnigekO = false;}
      if(ZOBaCigIPc == true){ZOBaCigIPc = false;}
      if(NyUBDHRrRz == true){NyUBDHRrRz = false;}
      if(HiDfgiDRni == true){HiDfgiDRni = false;}
      if(WFemElSspb == true){WFemElSspb = false;}
      if(BwiajGnmQf == true){BwiajGnmQf = false;}
      if(QnMlGqLVsS == true){QnMlGqLVsS = false;}
      if(ePTgGHTgwR == true){ePTgGHTgwR = false;}
      if(oYCpxLzbua == true){oYCpxLzbua = false;}
      if(uQAIRhrrgN == true){uQAIRhrrgN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QJNYRAZISL
{ 
  void gCVKgGOQXT()
  { 
      bool RbCRRHOFCU = false;
      bool cRXtaxWOid = false;
      bool xdUIBnPPNT = false;
      bool yAEUxwwYPZ = false;
      bool NoHTzdaBjO = false;
      bool YPawumHsQc = false;
      bool qyriWcNCxd = false;
      bool ByzJPIVBIW = false;
      bool MNezuhYHYJ = false;
      bool oCHlhOxYwW = false;
      bool QXEGMaQQfm = false;
      bool QGjtPdSrmn = false;
      bool EFdmoyqMbB = false;
      bool LxElGoIYlU = false;
      bool RHblriRNWD = false;
      bool uEkHRKtQQN = false;
      bool iEodaTByma = false;
      bool VtGSWwdquG = false;
      bool gcoXGGMwTw = false;
      bool tqIXkNSxKY = false;
      string jSeiCRFfeN;
      string NRgULLQDrT;
      string bbZupPTFYF;
      string IEpUNRRkrc;
      string jhnAIzRtWE;
      string NexzRHrism;
      string yzGZFIaMGs;
      string seKPjsnZlp;
      string xYhUqdGpDF;
      string YhrFdjbNuz;
      string YFmcKiTgPX;
      string TSwDpYQlha;
      string CkJBUKmFlz;
      string RadlRrkFKI;
      string KZZelFlnPE;
      string SpfTxnwlIz;
      string wNuPFsnJlx;
      string mLaZQbKdOO;
      string YypggbuKoc;
      string wzwKMwdKZs;
      if(jSeiCRFfeN == YFmcKiTgPX){RbCRRHOFCU = true;}
      else if(YFmcKiTgPX == jSeiCRFfeN){QXEGMaQQfm = true;}
      if(NRgULLQDrT == TSwDpYQlha){cRXtaxWOid = true;}
      else if(TSwDpYQlha == NRgULLQDrT){QGjtPdSrmn = true;}
      if(bbZupPTFYF == CkJBUKmFlz){xdUIBnPPNT = true;}
      else if(CkJBUKmFlz == bbZupPTFYF){EFdmoyqMbB = true;}
      if(IEpUNRRkrc == RadlRrkFKI){yAEUxwwYPZ = true;}
      else if(RadlRrkFKI == IEpUNRRkrc){LxElGoIYlU = true;}
      if(jhnAIzRtWE == KZZelFlnPE){NoHTzdaBjO = true;}
      else if(KZZelFlnPE == jhnAIzRtWE){RHblriRNWD = true;}
      if(NexzRHrism == SpfTxnwlIz){YPawumHsQc = true;}
      else if(SpfTxnwlIz == NexzRHrism){uEkHRKtQQN = true;}
      if(yzGZFIaMGs == wNuPFsnJlx){qyriWcNCxd = true;}
      else if(wNuPFsnJlx == yzGZFIaMGs){iEodaTByma = true;}
      if(seKPjsnZlp == mLaZQbKdOO){ByzJPIVBIW = true;}
      if(xYhUqdGpDF == YypggbuKoc){MNezuhYHYJ = true;}
      if(YhrFdjbNuz == wzwKMwdKZs){oCHlhOxYwW = true;}
      while(mLaZQbKdOO == seKPjsnZlp){VtGSWwdquG = true;}
      while(YypggbuKoc == YypggbuKoc){gcoXGGMwTw = true;}
      while(wzwKMwdKZs == wzwKMwdKZs){tqIXkNSxKY = true;}
      if(RbCRRHOFCU == true){RbCRRHOFCU = false;}
      if(cRXtaxWOid == true){cRXtaxWOid = false;}
      if(xdUIBnPPNT == true){xdUIBnPPNT = false;}
      if(yAEUxwwYPZ == true){yAEUxwwYPZ = false;}
      if(NoHTzdaBjO == true){NoHTzdaBjO = false;}
      if(YPawumHsQc == true){YPawumHsQc = false;}
      if(qyriWcNCxd == true){qyriWcNCxd = false;}
      if(ByzJPIVBIW == true){ByzJPIVBIW = false;}
      if(MNezuhYHYJ == true){MNezuhYHYJ = false;}
      if(oCHlhOxYwW == true){oCHlhOxYwW = false;}
      if(QXEGMaQQfm == true){QXEGMaQQfm = false;}
      if(QGjtPdSrmn == true){QGjtPdSrmn = false;}
      if(EFdmoyqMbB == true){EFdmoyqMbB = false;}
      if(LxElGoIYlU == true){LxElGoIYlU = false;}
      if(RHblriRNWD == true){RHblriRNWD = false;}
      if(uEkHRKtQQN == true){uEkHRKtQQN = false;}
      if(iEodaTByma == true){iEodaTByma = false;}
      if(VtGSWwdquG == true){VtGSWwdquG = false;}
      if(gcoXGGMwTw == true){gcoXGGMwTw = false;}
      if(tqIXkNSxKY == true){tqIXkNSxKY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KUIEVZXBQI
{ 
  void eMMOpAnBgE()
  { 
      bool dgggkzzAKw = false;
      bool rYVKoKjJen = false;
      bool wxgKaCrKIr = false;
      bool QMQpGyzNEL = false;
      bool sELoApJuzF = false;
      bool NdzhdfzWGh = false;
      bool GoqSfeIfEq = false;
      bool LVFStqkrJj = false;
      bool swKDdlMiLZ = false;
      bool ybHVFENsIV = false;
      bool hcqHtrYgmm = false;
      bool uGNVnJdnnt = false;
      bool SYUdriOiNp = false;
      bool dqjnCQFCIl = false;
      bool MfuYerOkgu = false;
      bool aZFOCIIMOK = false;
      bool cpSxIDWYTX = false;
      bool DaeCgldwzA = false;
      bool TcBRPElUks = false;
      bool HrmyIWMyPa = false;
      string DwMwyZHOxd;
      string dFZWxixqwl;
      string cmKWtCbcuB;
      string hlaEWaxQjS;
      string cbBRmYXdzk;
      string mFnHaQkpBu;
      string xdSuwrdUzW;
      string lfGdIAksiV;
      string dxcJObySdG;
      string oGPnUzIGUu;
      string tDebzHyJzZ;
      string erGeQAAJgT;
      string sKqrheQSJJ;
      string rdXmbaRBJH;
      string dnTEbxAjWT;
      string yzZABiLmtU;
      string pfzohATSDp;
      string hzzZpFqmQj;
      string efupKsEWks;
      string PeGoQyndVa;
      if(DwMwyZHOxd == tDebzHyJzZ){dgggkzzAKw = true;}
      else if(tDebzHyJzZ == DwMwyZHOxd){hcqHtrYgmm = true;}
      if(dFZWxixqwl == erGeQAAJgT){rYVKoKjJen = true;}
      else if(erGeQAAJgT == dFZWxixqwl){uGNVnJdnnt = true;}
      if(cmKWtCbcuB == sKqrheQSJJ){wxgKaCrKIr = true;}
      else if(sKqrheQSJJ == cmKWtCbcuB){SYUdriOiNp = true;}
      if(hlaEWaxQjS == rdXmbaRBJH){QMQpGyzNEL = true;}
      else if(rdXmbaRBJH == hlaEWaxQjS){dqjnCQFCIl = true;}
      if(cbBRmYXdzk == dnTEbxAjWT){sELoApJuzF = true;}
      else if(dnTEbxAjWT == cbBRmYXdzk){MfuYerOkgu = true;}
      if(mFnHaQkpBu == yzZABiLmtU){NdzhdfzWGh = true;}
      else if(yzZABiLmtU == mFnHaQkpBu){aZFOCIIMOK = true;}
      if(xdSuwrdUzW == pfzohATSDp){GoqSfeIfEq = true;}
      else if(pfzohATSDp == xdSuwrdUzW){cpSxIDWYTX = true;}
      if(lfGdIAksiV == hzzZpFqmQj){LVFStqkrJj = true;}
      if(dxcJObySdG == efupKsEWks){swKDdlMiLZ = true;}
      if(oGPnUzIGUu == PeGoQyndVa){ybHVFENsIV = true;}
      while(hzzZpFqmQj == lfGdIAksiV){DaeCgldwzA = true;}
      while(efupKsEWks == efupKsEWks){TcBRPElUks = true;}
      while(PeGoQyndVa == PeGoQyndVa){HrmyIWMyPa = true;}
      if(dgggkzzAKw == true){dgggkzzAKw = false;}
      if(rYVKoKjJen == true){rYVKoKjJen = false;}
      if(wxgKaCrKIr == true){wxgKaCrKIr = false;}
      if(QMQpGyzNEL == true){QMQpGyzNEL = false;}
      if(sELoApJuzF == true){sELoApJuzF = false;}
      if(NdzhdfzWGh == true){NdzhdfzWGh = false;}
      if(GoqSfeIfEq == true){GoqSfeIfEq = false;}
      if(LVFStqkrJj == true){LVFStqkrJj = false;}
      if(swKDdlMiLZ == true){swKDdlMiLZ = false;}
      if(ybHVFENsIV == true){ybHVFENsIV = false;}
      if(hcqHtrYgmm == true){hcqHtrYgmm = false;}
      if(uGNVnJdnnt == true){uGNVnJdnnt = false;}
      if(SYUdriOiNp == true){SYUdriOiNp = false;}
      if(dqjnCQFCIl == true){dqjnCQFCIl = false;}
      if(MfuYerOkgu == true){MfuYerOkgu = false;}
      if(aZFOCIIMOK == true){aZFOCIIMOK = false;}
      if(cpSxIDWYTX == true){cpSxIDWYTX = false;}
      if(DaeCgldwzA == true){DaeCgldwzA = false;}
      if(TcBRPElUks == true){TcBRPElUks = false;}
      if(HrmyIWMyPa == true){HrmyIWMyPa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CNUTQMFEHH
{ 
  void NNoZQKPrMh()
  { 
      bool LwWufOIAQg = false;
      bool YUXHmoShBQ = false;
      bool pbBhOEIWUy = false;
      bool jgZGUrESxA = false;
      bool lpHmASoDDh = false;
      bool jRNSyiuogb = false;
      bool GlfSxruRlu = false;
      bool jzjAeAUNhw = false;
      bool OFSlNRSGHl = false;
      bool wPlVtAJopH = false;
      bool XXQIxjgMny = false;
      bool NhHjMASsEe = false;
      bool ZnJAyUNNGd = false;
      bool peXZXpnKnc = false;
      bool jFRIXOHBJs = false;
      bool gPkKhiOQJc = false;
      bool WTGJHiKhMV = false;
      bool LIFbuTVAbj = false;
      bool MMENxZtMqn = false;
      bool bXALGQzIAo = false;
      string GGEtDcAEZe;
      string HTARmLMlro;
      string FgSADYKFUc;
      string MNBUMqdXBQ;
      string slWXENRqbR;
      string NfOJwZmDqd;
      string StiwSsSeEw;
      string hnjauTJuwo;
      string GTdCOfzrYm;
      string DZgWyyCZEK;
      string ullfjZunNc;
      string QqHBXzQggl;
      string tZGRrHHNbx;
      string QipktTgxSo;
      string kLewVLSezy;
      string hVrRQUfTmb;
      string RgLPLgAVHD;
      string RSNrBiuKuf;
      string obOdOtpYUZ;
      string nNKqXDzOjo;
      if(GGEtDcAEZe == ullfjZunNc){LwWufOIAQg = true;}
      else if(ullfjZunNc == GGEtDcAEZe){XXQIxjgMny = true;}
      if(HTARmLMlro == QqHBXzQggl){YUXHmoShBQ = true;}
      else if(QqHBXzQggl == HTARmLMlro){NhHjMASsEe = true;}
      if(FgSADYKFUc == tZGRrHHNbx){pbBhOEIWUy = true;}
      else if(tZGRrHHNbx == FgSADYKFUc){ZnJAyUNNGd = true;}
      if(MNBUMqdXBQ == QipktTgxSo){jgZGUrESxA = true;}
      else if(QipktTgxSo == MNBUMqdXBQ){peXZXpnKnc = true;}
      if(slWXENRqbR == kLewVLSezy){lpHmASoDDh = true;}
      else if(kLewVLSezy == slWXENRqbR){jFRIXOHBJs = true;}
      if(NfOJwZmDqd == hVrRQUfTmb){jRNSyiuogb = true;}
      else if(hVrRQUfTmb == NfOJwZmDqd){gPkKhiOQJc = true;}
      if(StiwSsSeEw == RgLPLgAVHD){GlfSxruRlu = true;}
      else if(RgLPLgAVHD == StiwSsSeEw){WTGJHiKhMV = true;}
      if(hnjauTJuwo == RSNrBiuKuf){jzjAeAUNhw = true;}
      if(GTdCOfzrYm == obOdOtpYUZ){OFSlNRSGHl = true;}
      if(DZgWyyCZEK == nNKqXDzOjo){wPlVtAJopH = true;}
      while(RSNrBiuKuf == hnjauTJuwo){LIFbuTVAbj = true;}
      while(obOdOtpYUZ == obOdOtpYUZ){MMENxZtMqn = true;}
      while(nNKqXDzOjo == nNKqXDzOjo){bXALGQzIAo = true;}
      if(LwWufOIAQg == true){LwWufOIAQg = false;}
      if(YUXHmoShBQ == true){YUXHmoShBQ = false;}
      if(pbBhOEIWUy == true){pbBhOEIWUy = false;}
      if(jgZGUrESxA == true){jgZGUrESxA = false;}
      if(lpHmASoDDh == true){lpHmASoDDh = false;}
      if(jRNSyiuogb == true){jRNSyiuogb = false;}
      if(GlfSxruRlu == true){GlfSxruRlu = false;}
      if(jzjAeAUNhw == true){jzjAeAUNhw = false;}
      if(OFSlNRSGHl == true){OFSlNRSGHl = false;}
      if(wPlVtAJopH == true){wPlVtAJopH = false;}
      if(XXQIxjgMny == true){XXQIxjgMny = false;}
      if(NhHjMASsEe == true){NhHjMASsEe = false;}
      if(ZnJAyUNNGd == true){ZnJAyUNNGd = false;}
      if(peXZXpnKnc == true){peXZXpnKnc = false;}
      if(jFRIXOHBJs == true){jFRIXOHBJs = false;}
      if(gPkKhiOQJc == true){gPkKhiOQJc = false;}
      if(WTGJHiKhMV == true){WTGJHiKhMV = false;}
      if(LIFbuTVAbj == true){LIFbuTVAbj = false;}
      if(MMENxZtMqn == true){MMENxZtMqn = false;}
      if(bXALGQzIAo == true){bXALGQzIAo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EHMMVXGWER
{ 
  void zwMaDIJWEk()
  { 
      bool qTPkKagtQI = false;
      bool EalSKDTwmV = false;
      bool IVFwxHVkXC = false;
      bool psmUfVUanN = false;
      bool IxJOnpyBrG = false;
      bool GUGOsVNSnD = false;
      bool FwWNSKmQlo = false;
      bool hrHZNKMqIG = false;
      bool IUsRwUlYbK = false;
      bool HCmkILauuc = false;
      bool DgODXOMgAh = false;
      bool JWJhtkDERx = false;
      bool YNobgfFWQC = false;
      bool jQufCbFptg = false;
      bool IEXsBkrEqW = false;
      bool IWdyDormVq = false;
      bool JpPyyrbceS = false;
      bool eNJjoUouZu = false;
      bool mAfssNlxcN = false;
      bool jRTCXSnZuI = false;
      string pTdHLfqIYV;
      string eZFZaBCnwG;
      string SqInyuPbbT;
      string lzLQYNCkwF;
      string gtNMPOJkPl;
      string slnHwzKoIQ;
      string QOgFieNoAN;
      string zQrpYXcwXj;
      string keMoZAKETZ;
      string CNcenSMIck;
      string AUjBlbsxhX;
      string VOQXelBqei;
      string UJUaKlnMBG;
      string LUSmiQtKDx;
      string GMVwDmwEAC;
      string RVcsPqzJpA;
      string nfubLBucoO;
      string rpnhcHmXXX;
      string ojMznprZXr;
      string RjTCJZRtkC;
      if(pTdHLfqIYV == AUjBlbsxhX){qTPkKagtQI = true;}
      else if(AUjBlbsxhX == pTdHLfqIYV){DgODXOMgAh = true;}
      if(eZFZaBCnwG == VOQXelBqei){EalSKDTwmV = true;}
      else if(VOQXelBqei == eZFZaBCnwG){JWJhtkDERx = true;}
      if(SqInyuPbbT == UJUaKlnMBG){IVFwxHVkXC = true;}
      else if(UJUaKlnMBG == SqInyuPbbT){YNobgfFWQC = true;}
      if(lzLQYNCkwF == LUSmiQtKDx){psmUfVUanN = true;}
      else if(LUSmiQtKDx == lzLQYNCkwF){jQufCbFptg = true;}
      if(gtNMPOJkPl == GMVwDmwEAC){IxJOnpyBrG = true;}
      else if(GMVwDmwEAC == gtNMPOJkPl){IEXsBkrEqW = true;}
      if(slnHwzKoIQ == RVcsPqzJpA){GUGOsVNSnD = true;}
      else if(RVcsPqzJpA == slnHwzKoIQ){IWdyDormVq = true;}
      if(QOgFieNoAN == nfubLBucoO){FwWNSKmQlo = true;}
      else if(nfubLBucoO == QOgFieNoAN){JpPyyrbceS = true;}
      if(zQrpYXcwXj == rpnhcHmXXX){hrHZNKMqIG = true;}
      if(keMoZAKETZ == ojMznprZXr){IUsRwUlYbK = true;}
      if(CNcenSMIck == RjTCJZRtkC){HCmkILauuc = true;}
      while(rpnhcHmXXX == zQrpYXcwXj){eNJjoUouZu = true;}
      while(ojMznprZXr == ojMznprZXr){mAfssNlxcN = true;}
      while(RjTCJZRtkC == RjTCJZRtkC){jRTCXSnZuI = true;}
      if(qTPkKagtQI == true){qTPkKagtQI = false;}
      if(EalSKDTwmV == true){EalSKDTwmV = false;}
      if(IVFwxHVkXC == true){IVFwxHVkXC = false;}
      if(psmUfVUanN == true){psmUfVUanN = false;}
      if(IxJOnpyBrG == true){IxJOnpyBrG = false;}
      if(GUGOsVNSnD == true){GUGOsVNSnD = false;}
      if(FwWNSKmQlo == true){FwWNSKmQlo = false;}
      if(hrHZNKMqIG == true){hrHZNKMqIG = false;}
      if(IUsRwUlYbK == true){IUsRwUlYbK = false;}
      if(HCmkILauuc == true){HCmkILauuc = false;}
      if(DgODXOMgAh == true){DgODXOMgAh = false;}
      if(JWJhtkDERx == true){JWJhtkDERx = false;}
      if(YNobgfFWQC == true){YNobgfFWQC = false;}
      if(jQufCbFptg == true){jQufCbFptg = false;}
      if(IEXsBkrEqW == true){IEXsBkrEqW = false;}
      if(IWdyDormVq == true){IWdyDormVq = false;}
      if(JpPyyrbceS == true){JpPyyrbceS = false;}
      if(eNJjoUouZu == true){eNJjoUouZu = false;}
      if(mAfssNlxcN == true){mAfssNlxcN = false;}
      if(jRTCXSnZuI == true){jRTCXSnZuI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TEJXXCRWQI
{ 
  void rPDYmVUWCx()
  { 
      bool MuoOSBbtqp = false;
      bool oRJVUuiMRt = false;
      bool aCQIIhzwuj = false;
      bool YxaFpgyVdi = false;
      bool LMeRpaTpLq = false;
      bool iKTFsJegFk = false;
      bool BezGRqpDfm = false;
      bool wNhhiNWySh = false;
      bool NJkEBNdVMf = false;
      bool CRQsgfNXAy = false;
      bool jPKXtVbkWe = false;
      bool mfOWWrttFD = false;
      bool MUqAjewnBC = false;
      bool AzxTxxyMKf = false;
      bool lsyhsVDsVn = false;
      bool kTSxkOYKmO = false;
      bool YmiTdmhtZZ = false;
      bool tgjZQTWIHN = false;
      bool aDSMQggAhh = false;
      bool XnZuHyJeDF = false;
      string JYetRlTkke;
      string YHqDisyejL;
      string sZhIEtlZFK;
      string hhweFSJLaE;
      string DqIgDFKKce;
      string mZQIajqWpW;
      string AsfaxqKLyQ;
      string jlEfICRAEy;
      string jaxZWHQnEV;
      string blUDEJKgjL;
      string tyMMuAUkAX;
      string SpRrmZwGEo;
      string aWGcnxQBby;
      string qjQsDkNjdV;
      string lfmfClUcQd;
      string NEctkXrjXy;
      string iTJCghYYnC;
      string LLbhCuiZZC;
      string cnjxjmHWIe;
      string sdMflSWkzT;
      if(JYetRlTkke == tyMMuAUkAX){MuoOSBbtqp = true;}
      else if(tyMMuAUkAX == JYetRlTkke){jPKXtVbkWe = true;}
      if(YHqDisyejL == SpRrmZwGEo){oRJVUuiMRt = true;}
      else if(SpRrmZwGEo == YHqDisyejL){mfOWWrttFD = true;}
      if(sZhIEtlZFK == aWGcnxQBby){aCQIIhzwuj = true;}
      else if(aWGcnxQBby == sZhIEtlZFK){MUqAjewnBC = true;}
      if(hhweFSJLaE == qjQsDkNjdV){YxaFpgyVdi = true;}
      else if(qjQsDkNjdV == hhweFSJLaE){AzxTxxyMKf = true;}
      if(DqIgDFKKce == lfmfClUcQd){LMeRpaTpLq = true;}
      else if(lfmfClUcQd == DqIgDFKKce){lsyhsVDsVn = true;}
      if(mZQIajqWpW == NEctkXrjXy){iKTFsJegFk = true;}
      else if(NEctkXrjXy == mZQIajqWpW){kTSxkOYKmO = true;}
      if(AsfaxqKLyQ == iTJCghYYnC){BezGRqpDfm = true;}
      else if(iTJCghYYnC == AsfaxqKLyQ){YmiTdmhtZZ = true;}
      if(jlEfICRAEy == LLbhCuiZZC){wNhhiNWySh = true;}
      if(jaxZWHQnEV == cnjxjmHWIe){NJkEBNdVMf = true;}
      if(blUDEJKgjL == sdMflSWkzT){CRQsgfNXAy = true;}
      while(LLbhCuiZZC == jlEfICRAEy){tgjZQTWIHN = true;}
      while(cnjxjmHWIe == cnjxjmHWIe){aDSMQggAhh = true;}
      while(sdMflSWkzT == sdMflSWkzT){XnZuHyJeDF = true;}
      if(MuoOSBbtqp == true){MuoOSBbtqp = false;}
      if(oRJVUuiMRt == true){oRJVUuiMRt = false;}
      if(aCQIIhzwuj == true){aCQIIhzwuj = false;}
      if(YxaFpgyVdi == true){YxaFpgyVdi = false;}
      if(LMeRpaTpLq == true){LMeRpaTpLq = false;}
      if(iKTFsJegFk == true){iKTFsJegFk = false;}
      if(BezGRqpDfm == true){BezGRqpDfm = false;}
      if(wNhhiNWySh == true){wNhhiNWySh = false;}
      if(NJkEBNdVMf == true){NJkEBNdVMf = false;}
      if(CRQsgfNXAy == true){CRQsgfNXAy = false;}
      if(jPKXtVbkWe == true){jPKXtVbkWe = false;}
      if(mfOWWrttFD == true){mfOWWrttFD = false;}
      if(MUqAjewnBC == true){MUqAjewnBC = false;}
      if(AzxTxxyMKf == true){AzxTxxyMKf = false;}
      if(lsyhsVDsVn == true){lsyhsVDsVn = false;}
      if(kTSxkOYKmO == true){kTSxkOYKmO = false;}
      if(YmiTdmhtZZ == true){YmiTdmhtZZ = false;}
      if(tgjZQTWIHN == true){tgjZQTWIHN = false;}
      if(aDSMQggAhh == true){aDSMQggAhh = false;}
      if(XnZuHyJeDF == true){XnZuHyJeDF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GBBYMMQSLJ
{ 
  void JUUGCicmeJ()
  { 
      bool oClRDmDHWm = false;
      bool McpMQmNlAM = false;
      bool CAfsDGIIpr = false;
      bool VdRmzVhHsX = false;
      bool hKlaqitAKo = false;
      bool LCJGSoWrNw = false;
      bool duQeQiKCMu = false;
      bool FFsceqOFCT = false;
      bool MIxBfTULUK = false;
      bool zotwsmsGJH = false;
      bool YqmPjFJgaa = false;
      bool ZRpsjUxPyx = false;
      bool OzhBuPLwir = false;
      bool yHutuUUgRZ = false;
      bool JmjsjhyAMY = false;
      bool odILsYJlTT = false;
      bool tNyicSVwyO = false;
      bool zPxXnaPoQN = false;
      bool QLjKDTzjAW = false;
      bool LiNxfwoBPR = false;
      string fxyQlIdmkX;
      string TPSCYSuoBw;
      string jtXCuCuoIp;
      string knzasexGIk;
      string hVWGKcJJjf;
      string ybpullYwUi;
      string NoetmePrIt;
      string VngPNOWRqS;
      string rkEcrIxEnH;
      string GBkYXspcTe;
      string NRApKJuagW;
      string PHFCqbjCBe;
      string hLDBnUCHrU;
      string YtxLFajORi;
      string MWWRqywihu;
      string JmaoxBOzBp;
      string GmhMyVJsxP;
      string qVjSRKnkJo;
      string YTZwLkSIND;
      string MkMbbYnKTV;
      if(fxyQlIdmkX == NRApKJuagW){oClRDmDHWm = true;}
      else if(NRApKJuagW == fxyQlIdmkX){YqmPjFJgaa = true;}
      if(TPSCYSuoBw == PHFCqbjCBe){McpMQmNlAM = true;}
      else if(PHFCqbjCBe == TPSCYSuoBw){ZRpsjUxPyx = true;}
      if(jtXCuCuoIp == hLDBnUCHrU){CAfsDGIIpr = true;}
      else if(hLDBnUCHrU == jtXCuCuoIp){OzhBuPLwir = true;}
      if(knzasexGIk == YtxLFajORi){VdRmzVhHsX = true;}
      else if(YtxLFajORi == knzasexGIk){yHutuUUgRZ = true;}
      if(hVWGKcJJjf == MWWRqywihu){hKlaqitAKo = true;}
      else if(MWWRqywihu == hVWGKcJJjf){JmjsjhyAMY = true;}
      if(ybpullYwUi == JmaoxBOzBp){LCJGSoWrNw = true;}
      else if(JmaoxBOzBp == ybpullYwUi){odILsYJlTT = true;}
      if(NoetmePrIt == GmhMyVJsxP){duQeQiKCMu = true;}
      else if(GmhMyVJsxP == NoetmePrIt){tNyicSVwyO = true;}
      if(VngPNOWRqS == qVjSRKnkJo){FFsceqOFCT = true;}
      if(rkEcrIxEnH == YTZwLkSIND){MIxBfTULUK = true;}
      if(GBkYXspcTe == MkMbbYnKTV){zotwsmsGJH = true;}
      while(qVjSRKnkJo == VngPNOWRqS){zPxXnaPoQN = true;}
      while(YTZwLkSIND == YTZwLkSIND){QLjKDTzjAW = true;}
      while(MkMbbYnKTV == MkMbbYnKTV){LiNxfwoBPR = true;}
      if(oClRDmDHWm == true){oClRDmDHWm = false;}
      if(McpMQmNlAM == true){McpMQmNlAM = false;}
      if(CAfsDGIIpr == true){CAfsDGIIpr = false;}
      if(VdRmzVhHsX == true){VdRmzVhHsX = false;}
      if(hKlaqitAKo == true){hKlaqitAKo = false;}
      if(LCJGSoWrNw == true){LCJGSoWrNw = false;}
      if(duQeQiKCMu == true){duQeQiKCMu = false;}
      if(FFsceqOFCT == true){FFsceqOFCT = false;}
      if(MIxBfTULUK == true){MIxBfTULUK = false;}
      if(zotwsmsGJH == true){zotwsmsGJH = false;}
      if(YqmPjFJgaa == true){YqmPjFJgaa = false;}
      if(ZRpsjUxPyx == true){ZRpsjUxPyx = false;}
      if(OzhBuPLwir == true){OzhBuPLwir = false;}
      if(yHutuUUgRZ == true){yHutuUUgRZ = false;}
      if(JmjsjhyAMY == true){JmjsjhyAMY = false;}
      if(odILsYJlTT == true){odILsYJlTT = false;}
      if(tNyicSVwyO == true){tNyicSVwyO = false;}
      if(zPxXnaPoQN == true){zPxXnaPoQN = false;}
      if(QLjKDTzjAW == true){QLjKDTzjAW = false;}
      if(LiNxfwoBPR == true){LiNxfwoBPR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ACHNTQVKYE
{ 
  void GSRYPfsjgt()
  { 
      bool CHcGaKpVLw = false;
      bool OJCNIoLyrX = false;
      bool TTxyEOVfJu = false;
      bool pjMKsNKqHJ = false;
      bool AkYhXIgisR = false;
      bool dIdFmhJeCM = false;
      bool nKLPFdwrUu = false;
      bool eUpiXhuOaw = false;
      bool gllqRhGHWK = false;
      bool DfnuUoZIcs = false;
      bool LoOymISugE = false;
      bool mtDFeCYTyX = false;
      bool XoUJqzftOh = false;
      bool IllgkqXmEI = false;
      bool PLZSWJbiPS = false;
      bool QGJFVVUEGm = false;
      bool cXfywAHWUn = false;
      bool dkOoHMOCmh = false;
      bool XxdwRBcgKO = false;
      bool WSgQfqebVW = false;
      string FUtSaVJJXm;
      string NeDPkaYzjq;
      string JxTrImuTjD;
      string QAzyLrlQFB;
      string rKLEppmXDW;
      string meXHcHABKn;
      string ZoZUVMfEDr;
      string oHsizzlPBR;
      string zXQMQkbqVE;
      string qjGRaCkqhd;
      string KhTKhekoIc;
      string VkArnCYMDk;
      string joizBEBbHw;
      string OtgXHRDGek;
      string zmhrhFjNdY;
      string cXmxsUzTIc;
      string cJgLOaDbkW;
      string ySgRkxGpRu;
      string UmxiTpGjel;
      string RjxBHoGVdH;
      if(FUtSaVJJXm == KhTKhekoIc){CHcGaKpVLw = true;}
      else if(KhTKhekoIc == FUtSaVJJXm){LoOymISugE = true;}
      if(NeDPkaYzjq == VkArnCYMDk){OJCNIoLyrX = true;}
      else if(VkArnCYMDk == NeDPkaYzjq){mtDFeCYTyX = true;}
      if(JxTrImuTjD == joizBEBbHw){TTxyEOVfJu = true;}
      else if(joizBEBbHw == JxTrImuTjD){XoUJqzftOh = true;}
      if(QAzyLrlQFB == OtgXHRDGek){pjMKsNKqHJ = true;}
      else if(OtgXHRDGek == QAzyLrlQFB){IllgkqXmEI = true;}
      if(rKLEppmXDW == zmhrhFjNdY){AkYhXIgisR = true;}
      else if(zmhrhFjNdY == rKLEppmXDW){PLZSWJbiPS = true;}
      if(meXHcHABKn == cXmxsUzTIc){dIdFmhJeCM = true;}
      else if(cXmxsUzTIc == meXHcHABKn){QGJFVVUEGm = true;}
      if(ZoZUVMfEDr == cJgLOaDbkW){nKLPFdwrUu = true;}
      else if(cJgLOaDbkW == ZoZUVMfEDr){cXfywAHWUn = true;}
      if(oHsizzlPBR == ySgRkxGpRu){eUpiXhuOaw = true;}
      if(zXQMQkbqVE == UmxiTpGjel){gllqRhGHWK = true;}
      if(qjGRaCkqhd == RjxBHoGVdH){DfnuUoZIcs = true;}
      while(ySgRkxGpRu == oHsizzlPBR){dkOoHMOCmh = true;}
      while(UmxiTpGjel == UmxiTpGjel){XxdwRBcgKO = true;}
      while(RjxBHoGVdH == RjxBHoGVdH){WSgQfqebVW = true;}
      if(CHcGaKpVLw == true){CHcGaKpVLw = false;}
      if(OJCNIoLyrX == true){OJCNIoLyrX = false;}
      if(TTxyEOVfJu == true){TTxyEOVfJu = false;}
      if(pjMKsNKqHJ == true){pjMKsNKqHJ = false;}
      if(AkYhXIgisR == true){AkYhXIgisR = false;}
      if(dIdFmhJeCM == true){dIdFmhJeCM = false;}
      if(nKLPFdwrUu == true){nKLPFdwrUu = false;}
      if(eUpiXhuOaw == true){eUpiXhuOaw = false;}
      if(gllqRhGHWK == true){gllqRhGHWK = false;}
      if(DfnuUoZIcs == true){DfnuUoZIcs = false;}
      if(LoOymISugE == true){LoOymISugE = false;}
      if(mtDFeCYTyX == true){mtDFeCYTyX = false;}
      if(XoUJqzftOh == true){XoUJqzftOh = false;}
      if(IllgkqXmEI == true){IllgkqXmEI = false;}
      if(PLZSWJbiPS == true){PLZSWJbiPS = false;}
      if(QGJFVVUEGm == true){QGJFVVUEGm = false;}
      if(cXfywAHWUn == true){cXfywAHWUn = false;}
      if(dkOoHMOCmh == true){dkOoHMOCmh = false;}
      if(XxdwRBcgKO == true){XxdwRBcgKO = false;}
      if(WSgQfqebVW == true){WSgQfqebVW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AYLBDADMFB
{ 
  void VdIiIUJnyS()
  { 
      bool cQhHiELJXm = false;
      bool zEwREeuueb = false;
      bool zzSruhxocy = false;
      bool FsQzftpEpV = false;
      bool eZPVaStGYz = false;
      bool AVlUMdypMB = false;
      bool GVfZgFmwlJ = false;
      bool nqFJxZiwQc = false;
      bool mqQcxiGwlC = false;
      bool wArnOIsonV = false;
      bool eyUOKJQcXm = false;
      bool uBYiNPECby = false;
      bool yqJiNnyQtn = false;
      bool ftHuxoWCSn = false;
      bool RcYzHtaIaz = false;
      bool DqMpXnnkBV = false;
      bool KAiiHAtdlX = false;
      bool rCjnfUSKbS = false;
      bool NppujogRXJ = false;
      bool BlAwcRtoqG = false;
      string KPuIzBSyVU;
      string EobGPTKxbY;
      string WSuKdHQqaS;
      string TEfyUeZhaP;
      string YMLUVBXBmN;
      string GSOEwqUker;
      string kaXDBAJclj;
      string sbWLzJHaob;
      string jODMMBpbBd;
      string KoDidyoHSU;
      string rtPCTdwCFm;
      string itwCIWWKpA;
      string KgbHZEYmgA;
      string UAHTjoyBri;
      string EmVOuPsAaH;
      string adQSKKRIbP;
      string EIUERimbRS;
      string XVSHuWLNMJ;
      string LYMZZpinJZ;
      string WpYcewRRwM;
      if(KPuIzBSyVU == rtPCTdwCFm){cQhHiELJXm = true;}
      else if(rtPCTdwCFm == KPuIzBSyVU){eyUOKJQcXm = true;}
      if(EobGPTKxbY == itwCIWWKpA){zEwREeuueb = true;}
      else if(itwCIWWKpA == EobGPTKxbY){uBYiNPECby = true;}
      if(WSuKdHQqaS == KgbHZEYmgA){zzSruhxocy = true;}
      else if(KgbHZEYmgA == WSuKdHQqaS){yqJiNnyQtn = true;}
      if(TEfyUeZhaP == UAHTjoyBri){FsQzftpEpV = true;}
      else if(UAHTjoyBri == TEfyUeZhaP){ftHuxoWCSn = true;}
      if(YMLUVBXBmN == EmVOuPsAaH){eZPVaStGYz = true;}
      else if(EmVOuPsAaH == YMLUVBXBmN){RcYzHtaIaz = true;}
      if(GSOEwqUker == adQSKKRIbP){AVlUMdypMB = true;}
      else if(adQSKKRIbP == GSOEwqUker){DqMpXnnkBV = true;}
      if(kaXDBAJclj == EIUERimbRS){GVfZgFmwlJ = true;}
      else if(EIUERimbRS == kaXDBAJclj){KAiiHAtdlX = true;}
      if(sbWLzJHaob == XVSHuWLNMJ){nqFJxZiwQc = true;}
      if(jODMMBpbBd == LYMZZpinJZ){mqQcxiGwlC = true;}
      if(KoDidyoHSU == WpYcewRRwM){wArnOIsonV = true;}
      while(XVSHuWLNMJ == sbWLzJHaob){rCjnfUSKbS = true;}
      while(LYMZZpinJZ == LYMZZpinJZ){NppujogRXJ = true;}
      while(WpYcewRRwM == WpYcewRRwM){BlAwcRtoqG = true;}
      if(cQhHiELJXm == true){cQhHiELJXm = false;}
      if(zEwREeuueb == true){zEwREeuueb = false;}
      if(zzSruhxocy == true){zzSruhxocy = false;}
      if(FsQzftpEpV == true){FsQzftpEpV = false;}
      if(eZPVaStGYz == true){eZPVaStGYz = false;}
      if(AVlUMdypMB == true){AVlUMdypMB = false;}
      if(GVfZgFmwlJ == true){GVfZgFmwlJ = false;}
      if(nqFJxZiwQc == true){nqFJxZiwQc = false;}
      if(mqQcxiGwlC == true){mqQcxiGwlC = false;}
      if(wArnOIsonV == true){wArnOIsonV = false;}
      if(eyUOKJQcXm == true){eyUOKJQcXm = false;}
      if(uBYiNPECby == true){uBYiNPECby = false;}
      if(yqJiNnyQtn == true){yqJiNnyQtn = false;}
      if(ftHuxoWCSn == true){ftHuxoWCSn = false;}
      if(RcYzHtaIaz == true){RcYzHtaIaz = false;}
      if(DqMpXnnkBV == true){DqMpXnnkBV = false;}
      if(KAiiHAtdlX == true){KAiiHAtdlX = false;}
      if(rCjnfUSKbS == true){rCjnfUSKbS = false;}
      if(NppujogRXJ == true){NppujogRXJ = false;}
      if(BlAwcRtoqG == true){BlAwcRtoqG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWLGCOKSHB
{ 
  void dxJVczVYoD()
  { 
      bool wXkNakAmRL = false;
      bool nWGRWaAgLw = false;
      bool kzimapgHYe = false;
      bool NViTxyjkPi = false;
      bool rlqOuRnIix = false;
      bool ZPtUVxoxlj = false;
      bool DrOlySmlUX = false;
      bool qORbDzIUrI = false;
      bool BYYbEyaOxz = false;
      bool JlyeezWEQc = false;
      bool dCnKFLySQW = false;
      bool nUFcieSlgA = false;
      bool qYoUOEQlwD = false;
      bool bDEPezjOVs = false;
      bool zIyaLogUwA = false;
      bool gkXPkFMSuA = false;
      bool tLVMtkPoyi = false;
      bool tEQmAhaOJZ = false;
      bool XupwWqeneY = false;
      bool mRSUymmkfZ = false;
      string QtdSyZgIDr;
      string VWozGrBKTa;
      string XhUXLdIrul;
      string LxZfTQwnap;
      string aoUkYcmGyu;
      string nKDtdhYFGT;
      string QnNQgXwIeo;
      string wMicAhNjyh;
      string qCtzxAtfBl;
      string rphGZlbDDA;
      string gdaIzbaZsu;
      string TnHYcNsNSf;
      string dPGsxFebCN;
      string GJfxBMblzV;
      string ZTmGREhIdM;
      string sNjXWRXgKt;
      string xyWfoKHJXP;
      string kHNxGKcAas;
      string WVypUrYIaj;
      string ouaFYawGQH;
      if(QtdSyZgIDr == gdaIzbaZsu){wXkNakAmRL = true;}
      else if(gdaIzbaZsu == QtdSyZgIDr){dCnKFLySQW = true;}
      if(VWozGrBKTa == TnHYcNsNSf){nWGRWaAgLw = true;}
      else if(TnHYcNsNSf == VWozGrBKTa){nUFcieSlgA = true;}
      if(XhUXLdIrul == dPGsxFebCN){kzimapgHYe = true;}
      else if(dPGsxFebCN == XhUXLdIrul){qYoUOEQlwD = true;}
      if(LxZfTQwnap == GJfxBMblzV){NViTxyjkPi = true;}
      else if(GJfxBMblzV == LxZfTQwnap){bDEPezjOVs = true;}
      if(aoUkYcmGyu == ZTmGREhIdM){rlqOuRnIix = true;}
      else if(ZTmGREhIdM == aoUkYcmGyu){zIyaLogUwA = true;}
      if(nKDtdhYFGT == sNjXWRXgKt){ZPtUVxoxlj = true;}
      else if(sNjXWRXgKt == nKDtdhYFGT){gkXPkFMSuA = true;}
      if(QnNQgXwIeo == xyWfoKHJXP){DrOlySmlUX = true;}
      else if(xyWfoKHJXP == QnNQgXwIeo){tLVMtkPoyi = true;}
      if(wMicAhNjyh == kHNxGKcAas){qORbDzIUrI = true;}
      if(qCtzxAtfBl == WVypUrYIaj){BYYbEyaOxz = true;}
      if(rphGZlbDDA == ouaFYawGQH){JlyeezWEQc = true;}
      while(kHNxGKcAas == wMicAhNjyh){tEQmAhaOJZ = true;}
      while(WVypUrYIaj == WVypUrYIaj){XupwWqeneY = true;}
      while(ouaFYawGQH == ouaFYawGQH){mRSUymmkfZ = true;}
      if(wXkNakAmRL == true){wXkNakAmRL = false;}
      if(nWGRWaAgLw == true){nWGRWaAgLw = false;}
      if(kzimapgHYe == true){kzimapgHYe = false;}
      if(NViTxyjkPi == true){NViTxyjkPi = false;}
      if(rlqOuRnIix == true){rlqOuRnIix = false;}
      if(ZPtUVxoxlj == true){ZPtUVxoxlj = false;}
      if(DrOlySmlUX == true){DrOlySmlUX = false;}
      if(qORbDzIUrI == true){qORbDzIUrI = false;}
      if(BYYbEyaOxz == true){BYYbEyaOxz = false;}
      if(JlyeezWEQc == true){JlyeezWEQc = false;}
      if(dCnKFLySQW == true){dCnKFLySQW = false;}
      if(nUFcieSlgA == true){nUFcieSlgA = false;}
      if(qYoUOEQlwD == true){qYoUOEQlwD = false;}
      if(bDEPezjOVs == true){bDEPezjOVs = false;}
      if(zIyaLogUwA == true){zIyaLogUwA = false;}
      if(gkXPkFMSuA == true){gkXPkFMSuA = false;}
      if(tLVMtkPoyi == true){tLVMtkPoyi = false;}
      if(tEQmAhaOJZ == true){tEQmAhaOJZ = false;}
      if(XupwWqeneY == true){XupwWqeneY = false;}
      if(mRSUymmkfZ == true){mRSUymmkfZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WWGQSCEZXR
{ 
  void THasbKCIDn()
  { 
      bool Faospzmnec = false;
      bool AMZbaSSOVk = false;
      bool BxEDonjJxV = false;
      bool FiUDcnGuCf = false;
      bool UACruuAaLf = false;
      bool QBmGkIVlEB = false;
      bool OdpIXRqVyl = false;
      bool LXMpQAuMIt = false;
      bool mIyRFDuNSU = false;
      bool SUpAQqKsTc = false;
      bool DebYTroxpj = false;
      bool MIdKNFeYDT = false;
      bool VcDdTqgMZY = false;
      bool pBrepIfZxM = false;
      bool OyWhHJqflK = false;
      bool LkpAHZbyEc = false;
      bool LcXQsLPyTF = false;
      bool ZFbqFXGUWK = false;
      bool AAZONFLrXP = false;
      bool ghUUBkaFow = false;
      string jYtioCUKAD;
      string OfhxrUKKxl;
      string RuViMCXbCZ;
      string WpAKinHyIo;
      string gQXQSbwxiT;
      string LpMXmoDLWl;
      string esHZfXfWNE;
      string MLCHFAXEPj;
      string GZriOgccXt;
      string jwaVKnIxkt;
      string wYieGznERl;
      string QzumeFBYLz;
      string uDzTTQjfxR;
      string raTUnhpNbO;
      string rXKlckBnqF;
      string ljklzrZPKp;
      string OIHAspeZyx;
      string OmwxGWrNpi;
      string OworeIohUu;
      string HZDlzjQJrl;
      if(jYtioCUKAD == wYieGznERl){Faospzmnec = true;}
      else if(wYieGznERl == jYtioCUKAD){DebYTroxpj = true;}
      if(OfhxrUKKxl == QzumeFBYLz){AMZbaSSOVk = true;}
      else if(QzumeFBYLz == OfhxrUKKxl){MIdKNFeYDT = true;}
      if(RuViMCXbCZ == uDzTTQjfxR){BxEDonjJxV = true;}
      else if(uDzTTQjfxR == RuViMCXbCZ){VcDdTqgMZY = true;}
      if(WpAKinHyIo == raTUnhpNbO){FiUDcnGuCf = true;}
      else if(raTUnhpNbO == WpAKinHyIo){pBrepIfZxM = true;}
      if(gQXQSbwxiT == rXKlckBnqF){UACruuAaLf = true;}
      else if(rXKlckBnqF == gQXQSbwxiT){OyWhHJqflK = true;}
      if(LpMXmoDLWl == ljklzrZPKp){QBmGkIVlEB = true;}
      else if(ljklzrZPKp == LpMXmoDLWl){LkpAHZbyEc = true;}
      if(esHZfXfWNE == OIHAspeZyx){OdpIXRqVyl = true;}
      else if(OIHAspeZyx == esHZfXfWNE){LcXQsLPyTF = true;}
      if(MLCHFAXEPj == OmwxGWrNpi){LXMpQAuMIt = true;}
      if(GZriOgccXt == OworeIohUu){mIyRFDuNSU = true;}
      if(jwaVKnIxkt == HZDlzjQJrl){SUpAQqKsTc = true;}
      while(OmwxGWrNpi == MLCHFAXEPj){ZFbqFXGUWK = true;}
      while(OworeIohUu == OworeIohUu){AAZONFLrXP = true;}
      while(HZDlzjQJrl == HZDlzjQJrl){ghUUBkaFow = true;}
      if(Faospzmnec == true){Faospzmnec = false;}
      if(AMZbaSSOVk == true){AMZbaSSOVk = false;}
      if(BxEDonjJxV == true){BxEDonjJxV = false;}
      if(FiUDcnGuCf == true){FiUDcnGuCf = false;}
      if(UACruuAaLf == true){UACruuAaLf = false;}
      if(QBmGkIVlEB == true){QBmGkIVlEB = false;}
      if(OdpIXRqVyl == true){OdpIXRqVyl = false;}
      if(LXMpQAuMIt == true){LXMpQAuMIt = false;}
      if(mIyRFDuNSU == true){mIyRFDuNSU = false;}
      if(SUpAQqKsTc == true){SUpAQqKsTc = false;}
      if(DebYTroxpj == true){DebYTroxpj = false;}
      if(MIdKNFeYDT == true){MIdKNFeYDT = false;}
      if(VcDdTqgMZY == true){VcDdTqgMZY = false;}
      if(pBrepIfZxM == true){pBrepIfZxM = false;}
      if(OyWhHJqflK == true){OyWhHJqflK = false;}
      if(LkpAHZbyEc == true){LkpAHZbyEc = false;}
      if(LcXQsLPyTF == true){LcXQsLPyTF = false;}
      if(ZFbqFXGUWK == true){ZFbqFXGUWK = false;}
      if(AAZONFLrXP == true){AAZONFLrXP = false;}
      if(ghUUBkaFow == true){ghUUBkaFow = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MINLANARHP
{ 
  void SWoKMcxLLe()
  { 
      bool thBWHVlBOH = false;
      bool mYiqToRhAm = false;
      bool IodrBOcSaJ = false;
      bool ChpaIAHhmF = false;
      bool YyMolJhLpV = false;
      bool TPigFFDJUs = false;
      bool rTZEFFiIiT = false;
      bool hjttOJboFr = false;
      bool fRbEolyJUC = false;
      bool wxNsMEYHjg = false;
      bool ZZbWmjUnSw = false;
      bool cODbNaqUPS = false;
      bool GYmfWjVBgJ = false;
      bool kUFYRFoFQE = false;
      bool RKqXYhtkfl = false;
      bool MErQZBlwzD = false;
      bool NTGILIJdJH = false;
      bool kkDKBwhOGo = false;
      bool pkVuxfbnyQ = false;
      bool SsGNqxDhMQ = false;
      string OTDuLsYplx;
      string CUZXrsPWBV;
      string prPimXuooD;
      string zpbBpQKXzI;
      string NHSNuanTie;
      string SGELHVETHm;
      string yiAhxMsXha;
      string irXsHhYBnL;
      string ibFJkrlPsU;
      string MpPLKeGkPi;
      string hPlIwaiLEZ;
      string wCfwEVcqxF;
      string aceMNrbMic;
      string anlEdTpxNJ;
      string JZLTXKJTHn;
      string BPnKHEkYtD;
      string yWcbyIPaRj;
      string ffcmwARLoD;
      string iIEtaLAaxY;
      string hRCKLlxiUO;
      if(OTDuLsYplx == hPlIwaiLEZ){thBWHVlBOH = true;}
      else if(hPlIwaiLEZ == OTDuLsYplx){ZZbWmjUnSw = true;}
      if(CUZXrsPWBV == wCfwEVcqxF){mYiqToRhAm = true;}
      else if(wCfwEVcqxF == CUZXrsPWBV){cODbNaqUPS = true;}
      if(prPimXuooD == aceMNrbMic){IodrBOcSaJ = true;}
      else if(aceMNrbMic == prPimXuooD){GYmfWjVBgJ = true;}
      if(zpbBpQKXzI == anlEdTpxNJ){ChpaIAHhmF = true;}
      else if(anlEdTpxNJ == zpbBpQKXzI){kUFYRFoFQE = true;}
      if(NHSNuanTie == JZLTXKJTHn){YyMolJhLpV = true;}
      else if(JZLTXKJTHn == NHSNuanTie){RKqXYhtkfl = true;}
      if(SGELHVETHm == BPnKHEkYtD){TPigFFDJUs = true;}
      else if(BPnKHEkYtD == SGELHVETHm){MErQZBlwzD = true;}
      if(yiAhxMsXha == yWcbyIPaRj){rTZEFFiIiT = true;}
      else if(yWcbyIPaRj == yiAhxMsXha){NTGILIJdJH = true;}
      if(irXsHhYBnL == ffcmwARLoD){hjttOJboFr = true;}
      if(ibFJkrlPsU == iIEtaLAaxY){fRbEolyJUC = true;}
      if(MpPLKeGkPi == hRCKLlxiUO){wxNsMEYHjg = true;}
      while(ffcmwARLoD == irXsHhYBnL){kkDKBwhOGo = true;}
      while(iIEtaLAaxY == iIEtaLAaxY){pkVuxfbnyQ = true;}
      while(hRCKLlxiUO == hRCKLlxiUO){SsGNqxDhMQ = true;}
      if(thBWHVlBOH == true){thBWHVlBOH = false;}
      if(mYiqToRhAm == true){mYiqToRhAm = false;}
      if(IodrBOcSaJ == true){IodrBOcSaJ = false;}
      if(ChpaIAHhmF == true){ChpaIAHhmF = false;}
      if(YyMolJhLpV == true){YyMolJhLpV = false;}
      if(TPigFFDJUs == true){TPigFFDJUs = false;}
      if(rTZEFFiIiT == true){rTZEFFiIiT = false;}
      if(hjttOJboFr == true){hjttOJboFr = false;}
      if(fRbEolyJUC == true){fRbEolyJUC = false;}
      if(wxNsMEYHjg == true){wxNsMEYHjg = false;}
      if(ZZbWmjUnSw == true){ZZbWmjUnSw = false;}
      if(cODbNaqUPS == true){cODbNaqUPS = false;}
      if(GYmfWjVBgJ == true){GYmfWjVBgJ = false;}
      if(kUFYRFoFQE == true){kUFYRFoFQE = false;}
      if(RKqXYhtkfl == true){RKqXYhtkfl = false;}
      if(MErQZBlwzD == true){MErQZBlwzD = false;}
      if(NTGILIJdJH == true){NTGILIJdJH = false;}
      if(kkDKBwhOGo == true){kkDKBwhOGo = false;}
      if(pkVuxfbnyQ == true){pkVuxfbnyQ = false;}
      if(SsGNqxDhMQ == true){SsGNqxDhMQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWOGOLKYJJ
{ 
  void aQAsDDrwOm()
  { 
      bool LLdSzYZVcB = false;
      bool dLMzSnSDdN = false;
      bool sGysPnusMb = false;
      bool pWZXDnGEnm = false;
      bool AuXUkLMOlR = false;
      bool qnnQkEMkDL = false;
      bool cfIBLGknwe = false;
      bool hNPpMyhdHD = false;
      bool bfHukCiJly = false;
      bool aVAcJUlWId = false;
      bool ZXSHicYxDm = false;
      bool VhcAjxYNQJ = false;
      bool XbCxDMMlgr = false;
      bool MLVdcDNzLH = false;
      bool ckFybsrAsM = false;
      bool wXGyFyUUEW = false;
      bool PlQLaKMyWf = false;
      bool jYCIfmWEUK = false;
      bool TMsUwnFWXe = false;
      bool irunrqTsXR = false;
      string xYlLxyOtuR;
      string ehJFNdeyYw;
      string btfDPrBBEY;
      string GjphHkpblK;
      string hjFNwLPFZj;
      string yiHydDriwE;
      string xNpVKtqaxb;
      string mCMONrnSHD;
      string cwaTZXcrDE;
      string sHfhNUtjCB;
      string TnHxxuVsjl;
      string OYarbAlVwm;
      string RzWrieWeAs;
      string yEQFjnncWd;
      string BjIRoTfmGM;
      string hXmOjUQPOR;
      string YqrpmKIUIm;
      string MJyRlhpFCO;
      string zjXnLZQBVP;
      string XYOFFJqSee;
      if(xYlLxyOtuR == TnHxxuVsjl){LLdSzYZVcB = true;}
      else if(TnHxxuVsjl == xYlLxyOtuR){ZXSHicYxDm = true;}
      if(ehJFNdeyYw == OYarbAlVwm){dLMzSnSDdN = true;}
      else if(OYarbAlVwm == ehJFNdeyYw){VhcAjxYNQJ = true;}
      if(btfDPrBBEY == RzWrieWeAs){sGysPnusMb = true;}
      else if(RzWrieWeAs == btfDPrBBEY){XbCxDMMlgr = true;}
      if(GjphHkpblK == yEQFjnncWd){pWZXDnGEnm = true;}
      else if(yEQFjnncWd == GjphHkpblK){MLVdcDNzLH = true;}
      if(hjFNwLPFZj == BjIRoTfmGM){AuXUkLMOlR = true;}
      else if(BjIRoTfmGM == hjFNwLPFZj){ckFybsrAsM = true;}
      if(yiHydDriwE == hXmOjUQPOR){qnnQkEMkDL = true;}
      else if(hXmOjUQPOR == yiHydDriwE){wXGyFyUUEW = true;}
      if(xNpVKtqaxb == YqrpmKIUIm){cfIBLGknwe = true;}
      else if(YqrpmKIUIm == xNpVKtqaxb){PlQLaKMyWf = true;}
      if(mCMONrnSHD == MJyRlhpFCO){hNPpMyhdHD = true;}
      if(cwaTZXcrDE == zjXnLZQBVP){bfHukCiJly = true;}
      if(sHfhNUtjCB == XYOFFJqSee){aVAcJUlWId = true;}
      while(MJyRlhpFCO == mCMONrnSHD){jYCIfmWEUK = true;}
      while(zjXnLZQBVP == zjXnLZQBVP){TMsUwnFWXe = true;}
      while(XYOFFJqSee == XYOFFJqSee){irunrqTsXR = true;}
      if(LLdSzYZVcB == true){LLdSzYZVcB = false;}
      if(dLMzSnSDdN == true){dLMzSnSDdN = false;}
      if(sGysPnusMb == true){sGysPnusMb = false;}
      if(pWZXDnGEnm == true){pWZXDnGEnm = false;}
      if(AuXUkLMOlR == true){AuXUkLMOlR = false;}
      if(qnnQkEMkDL == true){qnnQkEMkDL = false;}
      if(cfIBLGknwe == true){cfIBLGknwe = false;}
      if(hNPpMyhdHD == true){hNPpMyhdHD = false;}
      if(bfHukCiJly == true){bfHukCiJly = false;}
      if(aVAcJUlWId == true){aVAcJUlWId = false;}
      if(ZXSHicYxDm == true){ZXSHicYxDm = false;}
      if(VhcAjxYNQJ == true){VhcAjxYNQJ = false;}
      if(XbCxDMMlgr == true){XbCxDMMlgr = false;}
      if(MLVdcDNzLH == true){MLVdcDNzLH = false;}
      if(ckFybsrAsM == true){ckFybsrAsM = false;}
      if(wXGyFyUUEW == true){wXGyFyUUEW = false;}
      if(PlQLaKMyWf == true){PlQLaKMyWf = false;}
      if(jYCIfmWEUK == true){jYCIfmWEUK = false;}
      if(TMsUwnFWXe == true){TMsUwnFWXe = false;}
      if(irunrqTsXR == true){irunrqTsXR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PTGEZMNKPF
{ 
  void dPAqsJRubQ()
  { 
      bool gmLPiuksKn = false;
      bool fpdDiXadId = false;
      bool KYjmKDKoXX = false;
      bool CQTabcPYFI = false;
      bool hMWhUleclA = false;
      bool oSczhICYFe = false;
      bool jwVmlPVDaG = false;
      bool HBXAwyCCRX = false;
      bool XhDXhimUrT = false;
      bool ZpTZXlqiwF = false;
      bool PbBermtcDj = false;
      bool FAHgGCryEC = false;
      bool bBKHgQhybJ = false;
      bool GSGLHwfXeu = false;
      bool nJQINZilSV = false;
      bool ssesdORtya = false;
      bool FwBsdmtuZK = false;
      bool WUSJORjCsH = false;
      bool hueGQMmMhs = false;
      bool dlYEoqIXda = false;
      string yCSugeVTqz;
      string GMMwaENgdQ;
      string hfUsECViIY;
      string rZLyqFjOja;
      string HnaYhkZifd;
      string ZFGLISgZqd;
      string IlKRHgBOEV;
      string UzxDJsEwKS;
      string bmDeymSApY;
      string XJXFRUcIRB;
      string iLeKJaHDBO;
      string NkPXCVifTT;
      string OBYfxKbqko;
      string QweIiPIsUX;
      string fPyaLmtzCw;
      string kxoymhmyMz;
      string zPSMxRFGnm;
      string NpLwmzCxUJ;
      string PbonDTGgVB;
      string cJfVXPwlcs;
      if(yCSugeVTqz == iLeKJaHDBO){gmLPiuksKn = true;}
      else if(iLeKJaHDBO == yCSugeVTqz){PbBermtcDj = true;}
      if(GMMwaENgdQ == NkPXCVifTT){fpdDiXadId = true;}
      else if(NkPXCVifTT == GMMwaENgdQ){FAHgGCryEC = true;}
      if(hfUsECViIY == OBYfxKbqko){KYjmKDKoXX = true;}
      else if(OBYfxKbqko == hfUsECViIY){bBKHgQhybJ = true;}
      if(rZLyqFjOja == QweIiPIsUX){CQTabcPYFI = true;}
      else if(QweIiPIsUX == rZLyqFjOja){GSGLHwfXeu = true;}
      if(HnaYhkZifd == fPyaLmtzCw){hMWhUleclA = true;}
      else if(fPyaLmtzCw == HnaYhkZifd){nJQINZilSV = true;}
      if(ZFGLISgZqd == kxoymhmyMz){oSczhICYFe = true;}
      else if(kxoymhmyMz == ZFGLISgZqd){ssesdORtya = true;}
      if(IlKRHgBOEV == zPSMxRFGnm){jwVmlPVDaG = true;}
      else if(zPSMxRFGnm == IlKRHgBOEV){FwBsdmtuZK = true;}
      if(UzxDJsEwKS == NpLwmzCxUJ){HBXAwyCCRX = true;}
      if(bmDeymSApY == PbonDTGgVB){XhDXhimUrT = true;}
      if(XJXFRUcIRB == cJfVXPwlcs){ZpTZXlqiwF = true;}
      while(NpLwmzCxUJ == UzxDJsEwKS){WUSJORjCsH = true;}
      while(PbonDTGgVB == PbonDTGgVB){hueGQMmMhs = true;}
      while(cJfVXPwlcs == cJfVXPwlcs){dlYEoqIXda = true;}
      if(gmLPiuksKn == true){gmLPiuksKn = false;}
      if(fpdDiXadId == true){fpdDiXadId = false;}
      if(KYjmKDKoXX == true){KYjmKDKoXX = false;}
      if(CQTabcPYFI == true){CQTabcPYFI = false;}
      if(hMWhUleclA == true){hMWhUleclA = false;}
      if(oSczhICYFe == true){oSczhICYFe = false;}
      if(jwVmlPVDaG == true){jwVmlPVDaG = false;}
      if(HBXAwyCCRX == true){HBXAwyCCRX = false;}
      if(XhDXhimUrT == true){XhDXhimUrT = false;}
      if(ZpTZXlqiwF == true){ZpTZXlqiwF = false;}
      if(PbBermtcDj == true){PbBermtcDj = false;}
      if(FAHgGCryEC == true){FAHgGCryEC = false;}
      if(bBKHgQhybJ == true){bBKHgQhybJ = false;}
      if(GSGLHwfXeu == true){GSGLHwfXeu = false;}
      if(nJQINZilSV == true){nJQINZilSV = false;}
      if(ssesdORtya == true){ssesdORtya = false;}
      if(FwBsdmtuZK == true){FwBsdmtuZK = false;}
      if(WUSJORjCsH == true){WUSJORjCsH = false;}
      if(hueGQMmMhs == true){hueGQMmMhs = false;}
      if(dlYEoqIXda == true){dlYEoqIXda = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PLOXAUZWGG
{ 
  void fhbUwLLRGw()
  { 
      bool ytHLPBlEJQ = false;
      bool wwXiIZKFCg = false;
      bool COsdoLKwpD = false;
      bool cMXLTHbWZn = false;
      bool ToOxXsDBLS = false;
      bool AjCStjBcVD = false;
      bool qpNGmiYMPB = false;
      bool ynfONMAuGw = false;
      bool HIjXDsKEQj = false;
      bool GyAVwcbIKn = false;
      bool UqlKTMEnFh = false;
      bool jFWZuiGpCs = false;
      bool YTweuzmJRj = false;
      bool kqjRbQVYDp = false;
      bool oWziAAbZZN = false;
      bool WkFRPAuGPT = false;
      bool YtVUwrVEye = false;
      bool NgmMECUMet = false;
      bool XNiENzlSCa = false;
      bool VOJiRtAdlH = false;
      string MDybosFzMh;
      string qWhrcEEIiZ;
      string uXaHjNEdLZ;
      string qKcmPAwdGo;
      string HmNjUXYMjT;
      string YUiyEobqrb;
      string obmmpfttcc;
      string HaCtSIJqlL;
      string nrsqAWadiZ;
      string XFldAezasn;
      string deiGMyRofw;
      string fkEfnwhwlT;
      string EPKCFCnYsm;
      string IixxhJImeC;
      string EkxmtlAFpD;
      string xDnYiNTgBJ;
      string JsurmwmGyd;
      string nuQjOSRXIS;
      string BihppFtYNT;
      string obkUsLpEAx;
      if(MDybosFzMh == deiGMyRofw){ytHLPBlEJQ = true;}
      else if(deiGMyRofw == MDybosFzMh){UqlKTMEnFh = true;}
      if(qWhrcEEIiZ == fkEfnwhwlT){wwXiIZKFCg = true;}
      else if(fkEfnwhwlT == qWhrcEEIiZ){jFWZuiGpCs = true;}
      if(uXaHjNEdLZ == EPKCFCnYsm){COsdoLKwpD = true;}
      else if(EPKCFCnYsm == uXaHjNEdLZ){YTweuzmJRj = true;}
      if(qKcmPAwdGo == IixxhJImeC){cMXLTHbWZn = true;}
      else if(IixxhJImeC == qKcmPAwdGo){kqjRbQVYDp = true;}
      if(HmNjUXYMjT == EkxmtlAFpD){ToOxXsDBLS = true;}
      else if(EkxmtlAFpD == HmNjUXYMjT){oWziAAbZZN = true;}
      if(YUiyEobqrb == xDnYiNTgBJ){AjCStjBcVD = true;}
      else if(xDnYiNTgBJ == YUiyEobqrb){WkFRPAuGPT = true;}
      if(obmmpfttcc == JsurmwmGyd){qpNGmiYMPB = true;}
      else if(JsurmwmGyd == obmmpfttcc){YtVUwrVEye = true;}
      if(HaCtSIJqlL == nuQjOSRXIS){ynfONMAuGw = true;}
      if(nrsqAWadiZ == BihppFtYNT){HIjXDsKEQj = true;}
      if(XFldAezasn == obkUsLpEAx){GyAVwcbIKn = true;}
      while(nuQjOSRXIS == HaCtSIJqlL){NgmMECUMet = true;}
      while(BihppFtYNT == BihppFtYNT){XNiENzlSCa = true;}
      while(obkUsLpEAx == obkUsLpEAx){VOJiRtAdlH = true;}
      if(ytHLPBlEJQ == true){ytHLPBlEJQ = false;}
      if(wwXiIZKFCg == true){wwXiIZKFCg = false;}
      if(COsdoLKwpD == true){COsdoLKwpD = false;}
      if(cMXLTHbWZn == true){cMXLTHbWZn = false;}
      if(ToOxXsDBLS == true){ToOxXsDBLS = false;}
      if(AjCStjBcVD == true){AjCStjBcVD = false;}
      if(qpNGmiYMPB == true){qpNGmiYMPB = false;}
      if(ynfONMAuGw == true){ynfONMAuGw = false;}
      if(HIjXDsKEQj == true){HIjXDsKEQj = false;}
      if(GyAVwcbIKn == true){GyAVwcbIKn = false;}
      if(UqlKTMEnFh == true){UqlKTMEnFh = false;}
      if(jFWZuiGpCs == true){jFWZuiGpCs = false;}
      if(YTweuzmJRj == true){YTweuzmJRj = false;}
      if(kqjRbQVYDp == true){kqjRbQVYDp = false;}
      if(oWziAAbZZN == true){oWziAAbZZN = false;}
      if(WkFRPAuGPT == true){WkFRPAuGPT = false;}
      if(YtVUwrVEye == true){YtVUwrVEye = false;}
      if(NgmMECUMet == true){NgmMECUMet = false;}
      if(XNiENzlSCa == true){XNiENzlSCa = false;}
      if(VOJiRtAdlH == true){VOJiRtAdlH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VYDAFTCTOU
{ 
  void XXhwheTUYi()
  { 
      bool pkQcOSIFad = false;
      bool oQHBEZtqDr = false;
      bool uYTdPtzuQn = false;
      bool tRerdglDJO = false;
      bool LnNuWJASLa = false;
      bool rUozEQQlNT = false;
      bool SMomjWkPWW = false;
      bool mqhofGKXHF = false;
      bool tgjpuYcenM = false;
      bool PzopuyzaLz = false;
      bool XkunnAmzSx = false;
      bool GseHYkcyqK = false;
      bool tFbJHmBqth = false;
      bool HiMIgJluCt = false;
      bool ldLpGWUhQJ = false;
      bool UAjBFRJkgA = false;
      bool zuFkpWgWZP = false;
      bool zhwwXQtkDj = false;
      bool RTajMGzKCO = false;
      bool zBOBuqXaAj = false;
      string OuwYRBWNmL;
      string TfuWmAifsP;
      string bTENSgBWIY;
      string iEHMrBSPJb;
      string yVhUiPAMiC;
      string HuWXGtpiFk;
      string zzENcPYiek;
      string hTVRRFljdD;
      string fonGRmgiFx;
      string LjJXbyRTrS;
      string pRgxTmYFFA;
      string HGECEKLxwo;
      string hocgZxKyoT;
      string nSqKMOHqld;
      string NbdFoFeGSR;
      string mTXCkAnzWW;
      string caPkMoOtpp;
      string CTKRbGLXrU;
      string SDfXgTtoZL;
      string aHTPAmMsrz;
      if(OuwYRBWNmL == pRgxTmYFFA){pkQcOSIFad = true;}
      else if(pRgxTmYFFA == OuwYRBWNmL){XkunnAmzSx = true;}
      if(TfuWmAifsP == HGECEKLxwo){oQHBEZtqDr = true;}
      else if(HGECEKLxwo == TfuWmAifsP){GseHYkcyqK = true;}
      if(bTENSgBWIY == hocgZxKyoT){uYTdPtzuQn = true;}
      else if(hocgZxKyoT == bTENSgBWIY){tFbJHmBqth = true;}
      if(iEHMrBSPJb == nSqKMOHqld){tRerdglDJO = true;}
      else if(nSqKMOHqld == iEHMrBSPJb){HiMIgJluCt = true;}
      if(yVhUiPAMiC == NbdFoFeGSR){LnNuWJASLa = true;}
      else if(NbdFoFeGSR == yVhUiPAMiC){ldLpGWUhQJ = true;}
      if(HuWXGtpiFk == mTXCkAnzWW){rUozEQQlNT = true;}
      else if(mTXCkAnzWW == HuWXGtpiFk){UAjBFRJkgA = true;}
      if(zzENcPYiek == caPkMoOtpp){SMomjWkPWW = true;}
      else if(caPkMoOtpp == zzENcPYiek){zuFkpWgWZP = true;}
      if(hTVRRFljdD == CTKRbGLXrU){mqhofGKXHF = true;}
      if(fonGRmgiFx == SDfXgTtoZL){tgjpuYcenM = true;}
      if(LjJXbyRTrS == aHTPAmMsrz){PzopuyzaLz = true;}
      while(CTKRbGLXrU == hTVRRFljdD){zhwwXQtkDj = true;}
      while(SDfXgTtoZL == SDfXgTtoZL){RTajMGzKCO = true;}
      while(aHTPAmMsrz == aHTPAmMsrz){zBOBuqXaAj = true;}
      if(pkQcOSIFad == true){pkQcOSIFad = false;}
      if(oQHBEZtqDr == true){oQHBEZtqDr = false;}
      if(uYTdPtzuQn == true){uYTdPtzuQn = false;}
      if(tRerdglDJO == true){tRerdglDJO = false;}
      if(LnNuWJASLa == true){LnNuWJASLa = false;}
      if(rUozEQQlNT == true){rUozEQQlNT = false;}
      if(SMomjWkPWW == true){SMomjWkPWW = false;}
      if(mqhofGKXHF == true){mqhofGKXHF = false;}
      if(tgjpuYcenM == true){tgjpuYcenM = false;}
      if(PzopuyzaLz == true){PzopuyzaLz = false;}
      if(XkunnAmzSx == true){XkunnAmzSx = false;}
      if(GseHYkcyqK == true){GseHYkcyqK = false;}
      if(tFbJHmBqth == true){tFbJHmBqth = false;}
      if(HiMIgJluCt == true){HiMIgJluCt = false;}
      if(ldLpGWUhQJ == true){ldLpGWUhQJ = false;}
      if(UAjBFRJkgA == true){UAjBFRJkgA = false;}
      if(zuFkpWgWZP == true){zuFkpWgWZP = false;}
      if(zhwwXQtkDj == true){zhwwXQtkDj = false;}
      if(RTajMGzKCO == true){RTajMGzKCO = false;}
      if(zBOBuqXaAj == true){zBOBuqXaAj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCRSJBNMQH
{ 
  void qGcmWfuIyK()
  { 
      bool wrkwipHaen = false;
      bool xtQdbrUxOJ = false;
      bool RkGEtFiAPD = false;
      bool ycJrOiiMCX = false;
      bool olyZRjembi = false;
      bool QPrwCLkfCd = false;
      bool HHKapTkYPs = false;
      bool JHupUflgmJ = false;
      bool ZwXgmhkNoD = false;
      bool xCKXQgaXix = false;
      bool zGXiZJUCaW = false;
      bool YEssDLicnI = false;
      bool iWiMuGxWYm = false;
      bool EOxoKTYnGd = false;
      bool NilSdsJQUF = false;
      bool xyjaObWLnT = false;
      bool LxcnRKHDhi = false;
      bool mtVJuzkQhB = false;
      bool xfCToGeVah = false;
      bool wNAmRPGyBS = false;
      string eDyxKEcAZY;
      string GhpNsmhliJ;
      string fqVriVRMhO;
      string wtxiwDBkXz;
      string KsLAVktFze;
      string kWpfEngFOo;
      string mQRKcMjHRp;
      string kxNiyleVWx;
      string bLMDcYDQeH;
      string VwWiMsbAXI;
      string AmmIsnJGhR;
      string ILiQNaDOgE;
      string IScKUoaeWE;
      string KexNwnYEJo;
      string OxiMyKNFVk;
      string pNSTzgJcnE;
      string NdicGdNUTY;
      string BzFroLjPLK;
      string bUJkOxMcNO;
      string ewQEbkNGFT;
      if(eDyxKEcAZY == AmmIsnJGhR){wrkwipHaen = true;}
      else if(AmmIsnJGhR == eDyxKEcAZY){zGXiZJUCaW = true;}
      if(GhpNsmhliJ == ILiQNaDOgE){xtQdbrUxOJ = true;}
      else if(ILiQNaDOgE == GhpNsmhliJ){YEssDLicnI = true;}
      if(fqVriVRMhO == IScKUoaeWE){RkGEtFiAPD = true;}
      else if(IScKUoaeWE == fqVriVRMhO){iWiMuGxWYm = true;}
      if(wtxiwDBkXz == KexNwnYEJo){ycJrOiiMCX = true;}
      else if(KexNwnYEJo == wtxiwDBkXz){EOxoKTYnGd = true;}
      if(KsLAVktFze == OxiMyKNFVk){olyZRjembi = true;}
      else if(OxiMyKNFVk == KsLAVktFze){NilSdsJQUF = true;}
      if(kWpfEngFOo == pNSTzgJcnE){QPrwCLkfCd = true;}
      else if(pNSTzgJcnE == kWpfEngFOo){xyjaObWLnT = true;}
      if(mQRKcMjHRp == NdicGdNUTY){HHKapTkYPs = true;}
      else if(NdicGdNUTY == mQRKcMjHRp){LxcnRKHDhi = true;}
      if(kxNiyleVWx == BzFroLjPLK){JHupUflgmJ = true;}
      if(bLMDcYDQeH == bUJkOxMcNO){ZwXgmhkNoD = true;}
      if(VwWiMsbAXI == ewQEbkNGFT){xCKXQgaXix = true;}
      while(BzFroLjPLK == kxNiyleVWx){mtVJuzkQhB = true;}
      while(bUJkOxMcNO == bUJkOxMcNO){xfCToGeVah = true;}
      while(ewQEbkNGFT == ewQEbkNGFT){wNAmRPGyBS = true;}
      if(wrkwipHaen == true){wrkwipHaen = false;}
      if(xtQdbrUxOJ == true){xtQdbrUxOJ = false;}
      if(RkGEtFiAPD == true){RkGEtFiAPD = false;}
      if(ycJrOiiMCX == true){ycJrOiiMCX = false;}
      if(olyZRjembi == true){olyZRjembi = false;}
      if(QPrwCLkfCd == true){QPrwCLkfCd = false;}
      if(HHKapTkYPs == true){HHKapTkYPs = false;}
      if(JHupUflgmJ == true){JHupUflgmJ = false;}
      if(ZwXgmhkNoD == true){ZwXgmhkNoD = false;}
      if(xCKXQgaXix == true){xCKXQgaXix = false;}
      if(zGXiZJUCaW == true){zGXiZJUCaW = false;}
      if(YEssDLicnI == true){YEssDLicnI = false;}
      if(iWiMuGxWYm == true){iWiMuGxWYm = false;}
      if(EOxoKTYnGd == true){EOxoKTYnGd = false;}
      if(NilSdsJQUF == true){NilSdsJQUF = false;}
      if(xyjaObWLnT == true){xyjaObWLnT = false;}
      if(LxcnRKHDhi == true){LxcnRKHDhi = false;}
      if(mtVJuzkQhB == true){mtVJuzkQhB = false;}
      if(xfCToGeVah == true){xfCToGeVah = false;}
      if(wNAmRPGyBS == true){wNAmRPGyBS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PKCZLJFVYN
{ 
  void quXpdbbXUa()
  { 
      bool xqZOTXYLEM = false;
      bool NJItHGOzxg = false;
      bool joUCHCiqEJ = false;
      bool TxrIyDWOaR = false;
      bool hIkPPgWsYT = false;
      bool jEddTIWWGQ = false;
      bool ngGtsQRAuD = false;
      bool jzXeyaDEmZ = false;
      bool foRjZOTNno = false;
      bool gzHJcACqWy = false;
      bool PWyUjjfyfr = false;
      bool ERjfkzOVUd = false;
      bool wDLFWkrOCy = false;
      bool YMgnKJqwAo = false;
      bool iUhukOPaYd = false;
      bool kfVsBMKryz = false;
      bool rRwgTrkuVa = false;
      bool HRUeubVPUH = false;
      bool UQoXMrpnlx = false;
      bool zyyBwQYAbs = false;
      string irDcwmlQmf;
      string WTpplGroka;
      string sGxcqbSpns;
      string JMswzEYnjE;
      string shthMAJewS;
      string JlXGDbuZlU;
      string UucsVJZtqg;
      string hEFghKMOPp;
      string SmsUjWomrW;
      string IyBOixFALD;
      string ZOnOkFgqXs;
      string PgJwCgBHJy;
      string TmCTYiCpxk;
      string ELCMPDzeid;
      string pxOzHbnFMC;
      string uxqMimMTpC;
      string DqtmnEdxfy;
      string hWYfIWYDLw;
      string twcuoHTocc;
      string qengayDaKD;
      if(irDcwmlQmf == ZOnOkFgqXs){xqZOTXYLEM = true;}
      else if(ZOnOkFgqXs == irDcwmlQmf){PWyUjjfyfr = true;}
      if(WTpplGroka == PgJwCgBHJy){NJItHGOzxg = true;}
      else if(PgJwCgBHJy == WTpplGroka){ERjfkzOVUd = true;}
      if(sGxcqbSpns == TmCTYiCpxk){joUCHCiqEJ = true;}
      else if(TmCTYiCpxk == sGxcqbSpns){wDLFWkrOCy = true;}
      if(JMswzEYnjE == ELCMPDzeid){TxrIyDWOaR = true;}
      else if(ELCMPDzeid == JMswzEYnjE){YMgnKJqwAo = true;}
      if(shthMAJewS == pxOzHbnFMC){hIkPPgWsYT = true;}
      else if(pxOzHbnFMC == shthMAJewS){iUhukOPaYd = true;}
      if(JlXGDbuZlU == uxqMimMTpC){jEddTIWWGQ = true;}
      else if(uxqMimMTpC == JlXGDbuZlU){kfVsBMKryz = true;}
      if(UucsVJZtqg == DqtmnEdxfy){ngGtsQRAuD = true;}
      else if(DqtmnEdxfy == UucsVJZtqg){rRwgTrkuVa = true;}
      if(hEFghKMOPp == hWYfIWYDLw){jzXeyaDEmZ = true;}
      if(SmsUjWomrW == twcuoHTocc){foRjZOTNno = true;}
      if(IyBOixFALD == qengayDaKD){gzHJcACqWy = true;}
      while(hWYfIWYDLw == hEFghKMOPp){HRUeubVPUH = true;}
      while(twcuoHTocc == twcuoHTocc){UQoXMrpnlx = true;}
      while(qengayDaKD == qengayDaKD){zyyBwQYAbs = true;}
      if(xqZOTXYLEM == true){xqZOTXYLEM = false;}
      if(NJItHGOzxg == true){NJItHGOzxg = false;}
      if(joUCHCiqEJ == true){joUCHCiqEJ = false;}
      if(TxrIyDWOaR == true){TxrIyDWOaR = false;}
      if(hIkPPgWsYT == true){hIkPPgWsYT = false;}
      if(jEddTIWWGQ == true){jEddTIWWGQ = false;}
      if(ngGtsQRAuD == true){ngGtsQRAuD = false;}
      if(jzXeyaDEmZ == true){jzXeyaDEmZ = false;}
      if(foRjZOTNno == true){foRjZOTNno = false;}
      if(gzHJcACqWy == true){gzHJcACqWy = false;}
      if(PWyUjjfyfr == true){PWyUjjfyfr = false;}
      if(ERjfkzOVUd == true){ERjfkzOVUd = false;}
      if(wDLFWkrOCy == true){wDLFWkrOCy = false;}
      if(YMgnKJqwAo == true){YMgnKJqwAo = false;}
      if(iUhukOPaYd == true){iUhukOPaYd = false;}
      if(kfVsBMKryz == true){kfVsBMKryz = false;}
      if(rRwgTrkuVa == true){rRwgTrkuVa = false;}
      if(HRUeubVPUH == true){HRUeubVPUH = false;}
      if(UQoXMrpnlx == true){UQoXMrpnlx = false;}
      if(zyyBwQYAbs == true){zyyBwQYAbs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHDXPENSVU
{ 
  void NEAftuOGtq()
  { 
      bool MEXOlDcDXL = false;
      bool alClphPwlI = false;
      bool VCwFGcVCTn = false;
      bool ESFhWDxwgu = false;
      bool rlbeapqlAA = false;
      bool eKoRCJIRII = false;
      bool gZijHHfTOm = false;
      bool kSPqQjaQdP = false;
      bool ljBSIscneN = false;
      bool temYNRCqXT = false;
      bool JWWMPLuyAS = false;
      bool hqmrWxYPaO = false;
      bool eroArGfqdz = false;
      bool gisKFPMnDw = false;
      bool xenMeDqtCP = false;
      bool rmQInRgVUJ = false;
      bool fETAkyycmG = false;
      bool jjLeQzEcUo = false;
      bool OkoNGtSjVn = false;
      bool hpTtQsKmaf = false;
      string cbEKqSNPrs;
      string MCAegRFtRS;
      string dauddMoLnJ;
      string fNDptGVsHJ;
      string mggaGcNlwx;
      string RYzKRCfZgd;
      string cCaiNyzJjZ;
      string wMmIewtUWB;
      string zDPqqHOrYr;
      string auLcgjFyNH;
      string cDBVAEkqfU;
      string HKCfeYmjqF;
      string jHkrzBAJau;
      string pwHPXuCspm;
      string VXMEkPrfyI;
      string wVGHXVSJVz;
      string DaPjdLDmHi;
      string VssDiLtfHj;
      string IULSyUoAqC;
      string csXqiuHbaY;
      if(cbEKqSNPrs == cDBVAEkqfU){MEXOlDcDXL = true;}
      else if(cDBVAEkqfU == cbEKqSNPrs){JWWMPLuyAS = true;}
      if(MCAegRFtRS == HKCfeYmjqF){alClphPwlI = true;}
      else if(HKCfeYmjqF == MCAegRFtRS){hqmrWxYPaO = true;}
      if(dauddMoLnJ == jHkrzBAJau){VCwFGcVCTn = true;}
      else if(jHkrzBAJau == dauddMoLnJ){eroArGfqdz = true;}
      if(fNDptGVsHJ == pwHPXuCspm){ESFhWDxwgu = true;}
      else if(pwHPXuCspm == fNDptGVsHJ){gisKFPMnDw = true;}
      if(mggaGcNlwx == VXMEkPrfyI){rlbeapqlAA = true;}
      else if(VXMEkPrfyI == mggaGcNlwx){xenMeDqtCP = true;}
      if(RYzKRCfZgd == wVGHXVSJVz){eKoRCJIRII = true;}
      else if(wVGHXVSJVz == RYzKRCfZgd){rmQInRgVUJ = true;}
      if(cCaiNyzJjZ == DaPjdLDmHi){gZijHHfTOm = true;}
      else if(DaPjdLDmHi == cCaiNyzJjZ){fETAkyycmG = true;}
      if(wMmIewtUWB == VssDiLtfHj){kSPqQjaQdP = true;}
      if(zDPqqHOrYr == IULSyUoAqC){ljBSIscneN = true;}
      if(auLcgjFyNH == csXqiuHbaY){temYNRCqXT = true;}
      while(VssDiLtfHj == wMmIewtUWB){jjLeQzEcUo = true;}
      while(IULSyUoAqC == IULSyUoAqC){OkoNGtSjVn = true;}
      while(csXqiuHbaY == csXqiuHbaY){hpTtQsKmaf = true;}
      if(MEXOlDcDXL == true){MEXOlDcDXL = false;}
      if(alClphPwlI == true){alClphPwlI = false;}
      if(VCwFGcVCTn == true){VCwFGcVCTn = false;}
      if(ESFhWDxwgu == true){ESFhWDxwgu = false;}
      if(rlbeapqlAA == true){rlbeapqlAA = false;}
      if(eKoRCJIRII == true){eKoRCJIRII = false;}
      if(gZijHHfTOm == true){gZijHHfTOm = false;}
      if(kSPqQjaQdP == true){kSPqQjaQdP = false;}
      if(ljBSIscneN == true){ljBSIscneN = false;}
      if(temYNRCqXT == true){temYNRCqXT = false;}
      if(JWWMPLuyAS == true){JWWMPLuyAS = false;}
      if(hqmrWxYPaO == true){hqmrWxYPaO = false;}
      if(eroArGfqdz == true){eroArGfqdz = false;}
      if(gisKFPMnDw == true){gisKFPMnDw = false;}
      if(xenMeDqtCP == true){xenMeDqtCP = false;}
      if(rmQInRgVUJ == true){rmQInRgVUJ = false;}
      if(fETAkyycmG == true){fETAkyycmG = false;}
      if(jjLeQzEcUo == true){jjLeQzEcUo = false;}
      if(OkoNGtSjVn == true){OkoNGtSjVn = false;}
      if(hpTtQsKmaf == true){hpTtQsKmaf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RYWQFWQDNP
{ 
  void IQlXxzqjkG()
  { 
      bool aTwXpqfjOg = false;
      bool gxTCSzZOfI = false;
      bool JgNyEZYlNz = false;
      bool nXAZkRXlAU = false;
      bool MXyYwAyXMy = false;
      bool VMekPsGySP = false;
      bool StWPrIxtRB = false;
      bool bmNLukhoCE = false;
      bool bAZPdasOKq = false;
      bool KZTkBSBifm = false;
      bool CEGKWhzTpd = false;
      bool LRwNnRTGkQ = false;
      bool PijZpBTcJb = false;
      bool iyIOBXtOsu = false;
      bool bYXffsdFwi = false;
      bool ztxPWTUfUU = false;
      bool NWKOuMJgLQ = false;
      bool XFNpoqLDtw = false;
      bool XOfZcnBsrh = false;
      bool DOsXgEOJkS = false;
      string bjPGuTSpzq;
      string mOCUcCAkQf;
      string KXMznfAwYk;
      string TcbYRKWMhe;
      string zRpFDpJINJ;
      string CWQbkEXPSO;
      string TVRNWJmcCS;
      string enDkfrgGux;
      string VqiOhxMznN;
      string lGtSLdAbit;
      string DgGtdOSeus;
      string WRTVrcmCeY;
      string xmonfYsjZC;
      string qFWBsojnkT;
      string dgDupUlYai;
      string pywJwQqRNF;
      string UiFrBRtSbC;
      string ryRLtPisyL;
      string lUJqMsINFc;
      string yRZeyubLsY;
      if(bjPGuTSpzq == DgGtdOSeus){aTwXpqfjOg = true;}
      else if(DgGtdOSeus == bjPGuTSpzq){CEGKWhzTpd = true;}
      if(mOCUcCAkQf == WRTVrcmCeY){gxTCSzZOfI = true;}
      else if(WRTVrcmCeY == mOCUcCAkQf){LRwNnRTGkQ = true;}
      if(KXMznfAwYk == xmonfYsjZC){JgNyEZYlNz = true;}
      else if(xmonfYsjZC == KXMznfAwYk){PijZpBTcJb = true;}
      if(TcbYRKWMhe == qFWBsojnkT){nXAZkRXlAU = true;}
      else if(qFWBsojnkT == TcbYRKWMhe){iyIOBXtOsu = true;}
      if(zRpFDpJINJ == dgDupUlYai){MXyYwAyXMy = true;}
      else if(dgDupUlYai == zRpFDpJINJ){bYXffsdFwi = true;}
      if(CWQbkEXPSO == pywJwQqRNF){VMekPsGySP = true;}
      else if(pywJwQqRNF == CWQbkEXPSO){ztxPWTUfUU = true;}
      if(TVRNWJmcCS == UiFrBRtSbC){StWPrIxtRB = true;}
      else if(UiFrBRtSbC == TVRNWJmcCS){NWKOuMJgLQ = true;}
      if(enDkfrgGux == ryRLtPisyL){bmNLukhoCE = true;}
      if(VqiOhxMznN == lUJqMsINFc){bAZPdasOKq = true;}
      if(lGtSLdAbit == yRZeyubLsY){KZTkBSBifm = true;}
      while(ryRLtPisyL == enDkfrgGux){XFNpoqLDtw = true;}
      while(lUJqMsINFc == lUJqMsINFc){XOfZcnBsrh = true;}
      while(yRZeyubLsY == yRZeyubLsY){DOsXgEOJkS = true;}
      if(aTwXpqfjOg == true){aTwXpqfjOg = false;}
      if(gxTCSzZOfI == true){gxTCSzZOfI = false;}
      if(JgNyEZYlNz == true){JgNyEZYlNz = false;}
      if(nXAZkRXlAU == true){nXAZkRXlAU = false;}
      if(MXyYwAyXMy == true){MXyYwAyXMy = false;}
      if(VMekPsGySP == true){VMekPsGySP = false;}
      if(StWPrIxtRB == true){StWPrIxtRB = false;}
      if(bmNLukhoCE == true){bmNLukhoCE = false;}
      if(bAZPdasOKq == true){bAZPdasOKq = false;}
      if(KZTkBSBifm == true){KZTkBSBifm = false;}
      if(CEGKWhzTpd == true){CEGKWhzTpd = false;}
      if(LRwNnRTGkQ == true){LRwNnRTGkQ = false;}
      if(PijZpBTcJb == true){PijZpBTcJb = false;}
      if(iyIOBXtOsu == true){iyIOBXtOsu = false;}
      if(bYXffsdFwi == true){bYXffsdFwi = false;}
      if(ztxPWTUfUU == true){ztxPWTUfUU = false;}
      if(NWKOuMJgLQ == true){NWKOuMJgLQ = false;}
      if(XFNpoqLDtw == true){XFNpoqLDtw = false;}
      if(XOfZcnBsrh == true){XOfZcnBsrh = false;}
      if(DOsXgEOJkS == true){DOsXgEOJkS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CICTHZQXVK
{ 
  void uUyKuJyReS()
  { 
      bool jlPpSXToKc = false;
      bool zKoJCzamqP = false;
      bool BSHdEdfmhX = false;
      bool IwNdfZjKyX = false;
      bool CgufnnxnLj = false;
      bool GyeOMRdklo = false;
      bool qgHmUCwLdc = false;
      bool OQnTNTWapP = false;
      bool graxRJRzQN = false;
      bool uzYIfUZILk = false;
      bool rkKiUpJKBr = false;
      bool tDtVIzGKUK = false;
      bool kxtPhPqfmr = false;
      bool tNPFXuhqbb = false;
      bool AGyYSqECAg = false;
      bool OPnBzuqtBF = false;
      bool ydXIxgmoxN = false;
      bool ROhsJezVwp = false;
      bool KneGdeZOGc = false;
      bool EmpVdWhoal = false;
      string tfNaBinhrm;
      string LDbzruDIHl;
      string fGddJhQKwd;
      string sbhVdJhUQl;
      string ilVaqMTijp;
      string ONcnYmBiRT;
      string RckOtiUGVi;
      string NiqVDskDmw;
      string OhZGOeytwp;
      string HyCxTFBGfH;
      string rMNBcfVHke;
      string CxwVEjDezO;
      string kaJfaOgtBy;
      string rdXeEBTYci;
      string JqIQmKCgsi;
      string CVGQWQDhaO;
      string zbFmlYZQRC;
      string PdBQFsRrrQ;
      string LzARuWWGIm;
      string ylyOigkVeO;
      if(tfNaBinhrm == rMNBcfVHke){jlPpSXToKc = true;}
      else if(rMNBcfVHke == tfNaBinhrm){rkKiUpJKBr = true;}
      if(LDbzruDIHl == CxwVEjDezO){zKoJCzamqP = true;}
      else if(CxwVEjDezO == LDbzruDIHl){tDtVIzGKUK = true;}
      if(fGddJhQKwd == kaJfaOgtBy){BSHdEdfmhX = true;}
      else if(kaJfaOgtBy == fGddJhQKwd){kxtPhPqfmr = true;}
      if(sbhVdJhUQl == rdXeEBTYci){IwNdfZjKyX = true;}
      else if(rdXeEBTYci == sbhVdJhUQl){tNPFXuhqbb = true;}
      if(ilVaqMTijp == JqIQmKCgsi){CgufnnxnLj = true;}
      else if(JqIQmKCgsi == ilVaqMTijp){AGyYSqECAg = true;}
      if(ONcnYmBiRT == CVGQWQDhaO){GyeOMRdklo = true;}
      else if(CVGQWQDhaO == ONcnYmBiRT){OPnBzuqtBF = true;}
      if(RckOtiUGVi == zbFmlYZQRC){qgHmUCwLdc = true;}
      else if(zbFmlYZQRC == RckOtiUGVi){ydXIxgmoxN = true;}
      if(NiqVDskDmw == PdBQFsRrrQ){OQnTNTWapP = true;}
      if(OhZGOeytwp == LzARuWWGIm){graxRJRzQN = true;}
      if(HyCxTFBGfH == ylyOigkVeO){uzYIfUZILk = true;}
      while(PdBQFsRrrQ == NiqVDskDmw){ROhsJezVwp = true;}
      while(LzARuWWGIm == LzARuWWGIm){KneGdeZOGc = true;}
      while(ylyOigkVeO == ylyOigkVeO){EmpVdWhoal = true;}
      if(jlPpSXToKc == true){jlPpSXToKc = false;}
      if(zKoJCzamqP == true){zKoJCzamqP = false;}
      if(BSHdEdfmhX == true){BSHdEdfmhX = false;}
      if(IwNdfZjKyX == true){IwNdfZjKyX = false;}
      if(CgufnnxnLj == true){CgufnnxnLj = false;}
      if(GyeOMRdklo == true){GyeOMRdklo = false;}
      if(qgHmUCwLdc == true){qgHmUCwLdc = false;}
      if(OQnTNTWapP == true){OQnTNTWapP = false;}
      if(graxRJRzQN == true){graxRJRzQN = false;}
      if(uzYIfUZILk == true){uzYIfUZILk = false;}
      if(rkKiUpJKBr == true){rkKiUpJKBr = false;}
      if(tDtVIzGKUK == true){tDtVIzGKUK = false;}
      if(kxtPhPqfmr == true){kxtPhPqfmr = false;}
      if(tNPFXuhqbb == true){tNPFXuhqbb = false;}
      if(AGyYSqECAg == true){AGyYSqECAg = false;}
      if(OPnBzuqtBF == true){OPnBzuqtBF = false;}
      if(ydXIxgmoxN == true){ydXIxgmoxN = false;}
      if(ROhsJezVwp == true){ROhsJezVwp = false;}
      if(KneGdeZOGc == true){KneGdeZOGc = false;}
      if(EmpVdWhoal == true){EmpVdWhoal = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZCTSGIIBQQ
{ 
  void ePhKsHtmUl()
  { 
      bool VFyfjfttkB = false;
      bool tEdebaVxBL = false;
      bool OiCOzItECu = false;
      bool nBSUnoKBPX = false;
      bool GbWzVnhfRC = false;
      bool agkojmDjfb = false;
      bool lpqoMrkIqm = false;
      bool PUhcEmMCrK = false;
      bool aNmATGQckA = false;
      bool kaUmlQkgmd = false;
      bool CYodmGzIjx = false;
      bool aBrUBYDpVG = false;
      bool bIXpBnzuqn = false;
      bool CePNIBYINN = false;
      bool HIrmZjiAkN = false;
      bool MtLfBtAyby = false;
      bool GDQwtukdMz = false;
      bool AucHzTPjPR = false;
      bool EzJdbITjMN = false;
      bool BZfOGDqwre = false;
      string LKkMSoIMgF;
      string yEknicDGVD;
      string QNcbMjsmFC;
      string EXcfPWqIRf;
      string QOxVqsLcYM;
      string SwrkJxhJzi;
      string uVHdAaaEXL;
      string lunolCPGkS;
      string YPNrjIerVS;
      string ohIiktHTVP;
      string SGEMaWICyH;
      string gbYfKfHOsr;
      string uihFWDlFEq;
      string twkUARLBQN;
      string AcsOkMJcXE;
      string mrZcTjYzoW;
      string jCxGNkqDer;
      string UGyfrSoTUJ;
      string tJgzEBVHBQ;
      string sLLscxemBz;
      if(LKkMSoIMgF == SGEMaWICyH){VFyfjfttkB = true;}
      else if(SGEMaWICyH == LKkMSoIMgF){CYodmGzIjx = true;}
      if(yEknicDGVD == gbYfKfHOsr){tEdebaVxBL = true;}
      else if(gbYfKfHOsr == yEknicDGVD){aBrUBYDpVG = true;}
      if(QNcbMjsmFC == uihFWDlFEq){OiCOzItECu = true;}
      else if(uihFWDlFEq == QNcbMjsmFC){bIXpBnzuqn = true;}
      if(EXcfPWqIRf == twkUARLBQN){nBSUnoKBPX = true;}
      else if(twkUARLBQN == EXcfPWqIRf){CePNIBYINN = true;}
      if(QOxVqsLcYM == AcsOkMJcXE){GbWzVnhfRC = true;}
      else if(AcsOkMJcXE == QOxVqsLcYM){HIrmZjiAkN = true;}
      if(SwrkJxhJzi == mrZcTjYzoW){agkojmDjfb = true;}
      else if(mrZcTjYzoW == SwrkJxhJzi){MtLfBtAyby = true;}
      if(uVHdAaaEXL == jCxGNkqDer){lpqoMrkIqm = true;}
      else if(jCxGNkqDer == uVHdAaaEXL){GDQwtukdMz = true;}
      if(lunolCPGkS == UGyfrSoTUJ){PUhcEmMCrK = true;}
      if(YPNrjIerVS == tJgzEBVHBQ){aNmATGQckA = true;}
      if(ohIiktHTVP == sLLscxemBz){kaUmlQkgmd = true;}
      while(UGyfrSoTUJ == lunolCPGkS){AucHzTPjPR = true;}
      while(tJgzEBVHBQ == tJgzEBVHBQ){EzJdbITjMN = true;}
      while(sLLscxemBz == sLLscxemBz){BZfOGDqwre = true;}
      if(VFyfjfttkB == true){VFyfjfttkB = false;}
      if(tEdebaVxBL == true){tEdebaVxBL = false;}
      if(OiCOzItECu == true){OiCOzItECu = false;}
      if(nBSUnoKBPX == true){nBSUnoKBPX = false;}
      if(GbWzVnhfRC == true){GbWzVnhfRC = false;}
      if(agkojmDjfb == true){agkojmDjfb = false;}
      if(lpqoMrkIqm == true){lpqoMrkIqm = false;}
      if(PUhcEmMCrK == true){PUhcEmMCrK = false;}
      if(aNmATGQckA == true){aNmATGQckA = false;}
      if(kaUmlQkgmd == true){kaUmlQkgmd = false;}
      if(CYodmGzIjx == true){CYodmGzIjx = false;}
      if(aBrUBYDpVG == true){aBrUBYDpVG = false;}
      if(bIXpBnzuqn == true){bIXpBnzuqn = false;}
      if(CePNIBYINN == true){CePNIBYINN = false;}
      if(HIrmZjiAkN == true){HIrmZjiAkN = false;}
      if(MtLfBtAyby == true){MtLfBtAyby = false;}
      if(GDQwtukdMz == true){GDQwtukdMz = false;}
      if(AucHzTPjPR == true){AucHzTPjPR = false;}
      if(EzJdbITjMN == true){EzJdbITjMN = false;}
      if(BZfOGDqwre == true){BZfOGDqwre = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CAWNWZIYWC
{ 
  void WDKPuLgNAe()
  { 
      bool GrnnaBEsPP = false;
      bool paioHntOCH = false;
      bool DGomVVzOiS = false;
      bool NdAYzMnXGR = false;
      bool xoLRppWnDk = false;
      bool zESmsADBSF = false;
      bool CpKxCMaJpt = false;
      bool zVHkJOtWxe = false;
      bool yKKxTJLMfz = false;
      bool JmEBOHeNPc = false;
      bool PMyIkcwgce = false;
      bool FfDmGqeMdr = false;
      bool BNdqkMQFVC = false;
      bool ifHTOlMCLq = false;
      bool MdiAtciRuX = false;
      bool bRjXbBhHXY = false;
      bool LqLawYYiXU = false;
      bool ecAleWedxH = false;
      bool czJyaRujrN = false;
      bool DEemeVSHEU = false;
      string ULnYOEngMa;
      string IStMXdVWki;
      string pShNheqWbZ;
      string XMQxEDqmjG;
      string AglpohUTIU;
      string ifNDABdZpi;
      string NREmCuCxIT;
      string lhmehIgqYA;
      string JXOGpqyMwD;
      string ZRxAsibyms;
      string eWKnhAriVq;
      string UlBoZoDyxK;
      string wpAFsUjmlz;
      string giEeVmMZYo;
      string zPqFhnPIaD;
      string fdAbwoVFuN;
      string PFwVKkhWTl;
      string cdZHLgyuWF;
      string FbLhTChbhf;
      string QGdKYsSUux;
      if(ULnYOEngMa == eWKnhAriVq){GrnnaBEsPP = true;}
      else if(eWKnhAriVq == ULnYOEngMa){PMyIkcwgce = true;}
      if(IStMXdVWki == UlBoZoDyxK){paioHntOCH = true;}
      else if(UlBoZoDyxK == IStMXdVWki){FfDmGqeMdr = true;}
      if(pShNheqWbZ == wpAFsUjmlz){DGomVVzOiS = true;}
      else if(wpAFsUjmlz == pShNheqWbZ){BNdqkMQFVC = true;}
      if(XMQxEDqmjG == giEeVmMZYo){NdAYzMnXGR = true;}
      else if(giEeVmMZYo == XMQxEDqmjG){ifHTOlMCLq = true;}
      if(AglpohUTIU == zPqFhnPIaD){xoLRppWnDk = true;}
      else if(zPqFhnPIaD == AglpohUTIU){MdiAtciRuX = true;}
      if(ifNDABdZpi == fdAbwoVFuN){zESmsADBSF = true;}
      else if(fdAbwoVFuN == ifNDABdZpi){bRjXbBhHXY = true;}
      if(NREmCuCxIT == PFwVKkhWTl){CpKxCMaJpt = true;}
      else if(PFwVKkhWTl == NREmCuCxIT){LqLawYYiXU = true;}
      if(lhmehIgqYA == cdZHLgyuWF){zVHkJOtWxe = true;}
      if(JXOGpqyMwD == FbLhTChbhf){yKKxTJLMfz = true;}
      if(ZRxAsibyms == QGdKYsSUux){JmEBOHeNPc = true;}
      while(cdZHLgyuWF == lhmehIgqYA){ecAleWedxH = true;}
      while(FbLhTChbhf == FbLhTChbhf){czJyaRujrN = true;}
      while(QGdKYsSUux == QGdKYsSUux){DEemeVSHEU = true;}
      if(GrnnaBEsPP == true){GrnnaBEsPP = false;}
      if(paioHntOCH == true){paioHntOCH = false;}
      if(DGomVVzOiS == true){DGomVVzOiS = false;}
      if(NdAYzMnXGR == true){NdAYzMnXGR = false;}
      if(xoLRppWnDk == true){xoLRppWnDk = false;}
      if(zESmsADBSF == true){zESmsADBSF = false;}
      if(CpKxCMaJpt == true){CpKxCMaJpt = false;}
      if(zVHkJOtWxe == true){zVHkJOtWxe = false;}
      if(yKKxTJLMfz == true){yKKxTJLMfz = false;}
      if(JmEBOHeNPc == true){JmEBOHeNPc = false;}
      if(PMyIkcwgce == true){PMyIkcwgce = false;}
      if(FfDmGqeMdr == true){FfDmGqeMdr = false;}
      if(BNdqkMQFVC == true){BNdqkMQFVC = false;}
      if(ifHTOlMCLq == true){ifHTOlMCLq = false;}
      if(MdiAtciRuX == true){MdiAtciRuX = false;}
      if(bRjXbBhHXY == true){bRjXbBhHXY = false;}
      if(LqLawYYiXU == true){LqLawYYiXU = false;}
      if(ecAleWedxH == true){ecAleWedxH = false;}
      if(czJyaRujrN == true){czJyaRujrN = false;}
      if(DEemeVSHEU == true){DEemeVSHEU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IXQYPEBWNX
{ 
  void NYuwmSNapO()
  { 
      bool WZkORbcNCH = false;
      bool ysgjdEdBsw = false;
      bool assMZtBloF = false;
      bool LABUHZSXVn = false;
      bool kMpxIXMQRl = false;
      bool TysNHcgYnX = false;
      bool ZqXxwxqLbE = false;
      bool lFeFLOCuDC = false;
      bool gkUDkMGnMd = false;
      bool rsiyNtorAL = false;
      bool fBnMANTnBs = false;
      bool akUlpoWULj = false;
      bool qCyyLrVgrR = false;
      bool YJurVfwHDX = false;
      bool sSmTDHXxHX = false;
      bool WUgQTcCpAH = false;
      bool qmujTQpcPK = false;
      bool sOQnpXPdtE = false;
      bool TYYUtEcdXr = false;
      bool cGGufGWCzm = false;
      string bizFHEdrId;
      string pgZTcjbDKU;
      string BNdiZjfwEM;
      string qTulVyNyqu;
      string dHUIpIaYfZ;
      string uUxteOFQeW;
      string YhmwmWlnxe;
      string VcMPptrUrQ;
      string JGPeQWWAGH;
      string rwTTWwTYVT;
      string WmbADRIgDk;
      string VjXNNRRIeQ;
      string AkgplYJrrt;
      string ZTyYsWeOay;
      string NoxVkIYFFE;
      string dLsFTlFkOe;
      string IPoJLBlyTq;
      string mChfCLnLEd;
      string ADlmPOZsFH;
      string QsAwpxzmJi;
      if(bizFHEdrId == WmbADRIgDk){WZkORbcNCH = true;}
      else if(WmbADRIgDk == bizFHEdrId){fBnMANTnBs = true;}
      if(pgZTcjbDKU == VjXNNRRIeQ){ysgjdEdBsw = true;}
      else if(VjXNNRRIeQ == pgZTcjbDKU){akUlpoWULj = true;}
      if(BNdiZjfwEM == AkgplYJrrt){assMZtBloF = true;}
      else if(AkgplYJrrt == BNdiZjfwEM){qCyyLrVgrR = true;}
      if(qTulVyNyqu == ZTyYsWeOay){LABUHZSXVn = true;}
      else if(ZTyYsWeOay == qTulVyNyqu){YJurVfwHDX = true;}
      if(dHUIpIaYfZ == NoxVkIYFFE){kMpxIXMQRl = true;}
      else if(NoxVkIYFFE == dHUIpIaYfZ){sSmTDHXxHX = true;}
      if(uUxteOFQeW == dLsFTlFkOe){TysNHcgYnX = true;}
      else if(dLsFTlFkOe == uUxteOFQeW){WUgQTcCpAH = true;}
      if(YhmwmWlnxe == IPoJLBlyTq){ZqXxwxqLbE = true;}
      else if(IPoJLBlyTq == YhmwmWlnxe){qmujTQpcPK = true;}
      if(VcMPptrUrQ == mChfCLnLEd){lFeFLOCuDC = true;}
      if(JGPeQWWAGH == ADlmPOZsFH){gkUDkMGnMd = true;}
      if(rwTTWwTYVT == QsAwpxzmJi){rsiyNtorAL = true;}
      while(mChfCLnLEd == VcMPptrUrQ){sOQnpXPdtE = true;}
      while(ADlmPOZsFH == ADlmPOZsFH){TYYUtEcdXr = true;}
      while(QsAwpxzmJi == QsAwpxzmJi){cGGufGWCzm = true;}
      if(WZkORbcNCH == true){WZkORbcNCH = false;}
      if(ysgjdEdBsw == true){ysgjdEdBsw = false;}
      if(assMZtBloF == true){assMZtBloF = false;}
      if(LABUHZSXVn == true){LABUHZSXVn = false;}
      if(kMpxIXMQRl == true){kMpxIXMQRl = false;}
      if(TysNHcgYnX == true){TysNHcgYnX = false;}
      if(ZqXxwxqLbE == true){ZqXxwxqLbE = false;}
      if(lFeFLOCuDC == true){lFeFLOCuDC = false;}
      if(gkUDkMGnMd == true){gkUDkMGnMd = false;}
      if(rsiyNtorAL == true){rsiyNtorAL = false;}
      if(fBnMANTnBs == true){fBnMANTnBs = false;}
      if(akUlpoWULj == true){akUlpoWULj = false;}
      if(qCyyLrVgrR == true){qCyyLrVgrR = false;}
      if(YJurVfwHDX == true){YJurVfwHDX = false;}
      if(sSmTDHXxHX == true){sSmTDHXxHX = false;}
      if(WUgQTcCpAH == true){WUgQTcCpAH = false;}
      if(qmujTQpcPK == true){qmujTQpcPK = false;}
      if(sOQnpXPdtE == true){sOQnpXPdtE = false;}
      if(TYYUtEcdXr == true){TYYUtEcdXr = false;}
      if(cGGufGWCzm == true){cGGufGWCzm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDKPHDVKYD
{ 
  void UcRUOpERfG()
  { 
      bool DsXGtUGnNx = false;
      bool hDIFVlqCUF = false;
      bool pCdukkQmBZ = false;
      bool ssuZWWYrzy = false;
      bool efKObguNtY = false;
      bool lKCzMBOcUI = false;
      bool ETlnEnIihz = false;
      bool MyDWaJqPSE = false;
      bool oDrcmiquMV = false;
      bool HuWpsLsVKn = false;
      bool XMeuLmHeYD = false;
      bool JzKQTBaJAU = false;
      bool wMVMqQbMcO = false;
      bool PUEefcXxRA = false;
      bool bLWJLIkGWr = false;
      bool jjUpqLpRDt = false;
      bool LtCJmnuekq = false;
      bool cdrAsjpMAi = false;
      bool eVpkdfzOmT = false;
      bool lGsWogJMWX = false;
      string uYyYhkoRsc;
      string HGVhtbRJPT;
      string dpcFVchVTi;
      string UGBmysjwsT;
      string GPPxUhkNld;
      string ehVaCFwrDE;
      string CSxJIAEhjB;
      string rUQuMOZekm;
      string rUjpEljaks;
      string wqsoRnRFnT;
      string cCdklKRaNn;
      string eRHPLgiHFW;
      string QdxqEAabdY;
      string wUpQJpqyDs;
      string TJMxNejdcj;
      string FKARDzElfl;
      string ipwoqKaqFV;
      string pjELDGRAcZ;
      string PxysTlTYMK;
      string kESQKcNXFD;
      if(uYyYhkoRsc == cCdklKRaNn){DsXGtUGnNx = true;}
      else if(cCdklKRaNn == uYyYhkoRsc){XMeuLmHeYD = true;}
      if(HGVhtbRJPT == eRHPLgiHFW){hDIFVlqCUF = true;}
      else if(eRHPLgiHFW == HGVhtbRJPT){JzKQTBaJAU = true;}
      if(dpcFVchVTi == QdxqEAabdY){pCdukkQmBZ = true;}
      else if(QdxqEAabdY == dpcFVchVTi){wMVMqQbMcO = true;}
      if(UGBmysjwsT == wUpQJpqyDs){ssuZWWYrzy = true;}
      else if(wUpQJpqyDs == UGBmysjwsT){PUEefcXxRA = true;}
      if(GPPxUhkNld == TJMxNejdcj){efKObguNtY = true;}
      else if(TJMxNejdcj == GPPxUhkNld){bLWJLIkGWr = true;}
      if(ehVaCFwrDE == FKARDzElfl){lKCzMBOcUI = true;}
      else if(FKARDzElfl == ehVaCFwrDE){jjUpqLpRDt = true;}
      if(CSxJIAEhjB == ipwoqKaqFV){ETlnEnIihz = true;}
      else if(ipwoqKaqFV == CSxJIAEhjB){LtCJmnuekq = true;}
      if(rUQuMOZekm == pjELDGRAcZ){MyDWaJqPSE = true;}
      if(rUjpEljaks == PxysTlTYMK){oDrcmiquMV = true;}
      if(wqsoRnRFnT == kESQKcNXFD){HuWpsLsVKn = true;}
      while(pjELDGRAcZ == rUQuMOZekm){cdrAsjpMAi = true;}
      while(PxysTlTYMK == PxysTlTYMK){eVpkdfzOmT = true;}
      while(kESQKcNXFD == kESQKcNXFD){lGsWogJMWX = true;}
      if(DsXGtUGnNx == true){DsXGtUGnNx = false;}
      if(hDIFVlqCUF == true){hDIFVlqCUF = false;}
      if(pCdukkQmBZ == true){pCdukkQmBZ = false;}
      if(ssuZWWYrzy == true){ssuZWWYrzy = false;}
      if(efKObguNtY == true){efKObguNtY = false;}
      if(lKCzMBOcUI == true){lKCzMBOcUI = false;}
      if(ETlnEnIihz == true){ETlnEnIihz = false;}
      if(MyDWaJqPSE == true){MyDWaJqPSE = false;}
      if(oDrcmiquMV == true){oDrcmiquMV = false;}
      if(HuWpsLsVKn == true){HuWpsLsVKn = false;}
      if(XMeuLmHeYD == true){XMeuLmHeYD = false;}
      if(JzKQTBaJAU == true){JzKQTBaJAU = false;}
      if(wMVMqQbMcO == true){wMVMqQbMcO = false;}
      if(PUEefcXxRA == true){PUEefcXxRA = false;}
      if(bLWJLIkGWr == true){bLWJLIkGWr = false;}
      if(jjUpqLpRDt == true){jjUpqLpRDt = false;}
      if(LtCJmnuekq == true){LtCJmnuekq = false;}
      if(cdrAsjpMAi == true){cdrAsjpMAi = false;}
      if(eVpkdfzOmT == true){eVpkdfzOmT = false;}
      if(lGsWogJMWX == true){lGsWogJMWX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MPKOCUXKLZ
{ 
  void oTYKQPDJRm()
  { 
      bool RQLkQgOiiE = false;
      bool UXQISDQYMc = false;
      bool TuddefCpFG = false;
      bool gRMPzcxGKk = false;
      bool ouTzbrePXW = false;
      bool LFLlGWmhFk = false;
      bool dYdcWCKBJp = false;
      bool GKObmYbdBm = false;
      bool BmRiubFaIb = false;
      bool oOAZGQQpbY = false;
      bool gcGgPBqjzg = false;
      bool tIfSjqGuhu = false;
      bool xjrgBqJnUV = false;
      bool HkCcFXfjSt = false;
      bool kUbbhfihoP = false;
      bool KVIgbxkYfY = false;
      bool qCOcYJGDML = false;
      bool KVbnJbHQzU = false;
      bool IazFLkbUAI = false;
      bool mHEsCiGyCX = false;
      string pBDSJhSHex;
      string GhtUaYcASh;
      string MVcZXMdhKR;
      string LOcsmJeOma;
      string UdtWyKYFZA;
      string WtNSPTYctw;
      string DjwNkrEBhR;
      string tONrMhaGaN;
      string mYHKuRBKcS;
      string jBTpWkhgkG;
      string FXWIFIgVGg;
      string sSCgJdblRT;
      string ptXPhsuXUa;
      string AsUTHOCzEm;
      string keDwZQzlfs;
      string JwORPKzGZM;
      string MIAegzyhZt;
      string bbgehLpbpQ;
      string sJqbREeCEw;
      string PuYqZbdYOa;
      if(pBDSJhSHex == FXWIFIgVGg){RQLkQgOiiE = true;}
      else if(FXWIFIgVGg == pBDSJhSHex){gcGgPBqjzg = true;}
      if(GhtUaYcASh == sSCgJdblRT){UXQISDQYMc = true;}
      else if(sSCgJdblRT == GhtUaYcASh){tIfSjqGuhu = true;}
      if(MVcZXMdhKR == ptXPhsuXUa){TuddefCpFG = true;}
      else if(ptXPhsuXUa == MVcZXMdhKR){xjrgBqJnUV = true;}
      if(LOcsmJeOma == AsUTHOCzEm){gRMPzcxGKk = true;}
      else if(AsUTHOCzEm == LOcsmJeOma){HkCcFXfjSt = true;}
      if(UdtWyKYFZA == keDwZQzlfs){ouTzbrePXW = true;}
      else if(keDwZQzlfs == UdtWyKYFZA){kUbbhfihoP = true;}
      if(WtNSPTYctw == JwORPKzGZM){LFLlGWmhFk = true;}
      else if(JwORPKzGZM == WtNSPTYctw){KVIgbxkYfY = true;}
      if(DjwNkrEBhR == MIAegzyhZt){dYdcWCKBJp = true;}
      else if(MIAegzyhZt == DjwNkrEBhR){qCOcYJGDML = true;}
      if(tONrMhaGaN == bbgehLpbpQ){GKObmYbdBm = true;}
      if(mYHKuRBKcS == sJqbREeCEw){BmRiubFaIb = true;}
      if(jBTpWkhgkG == PuYqZbdYOa){oOAZGQQpbY = true;}
      while(bbgehLpbpQ == tONrMhaGaN){KVbnJbHQzU = true;}
      while(sJqbREeCEw == sJqbREeCEw){IazFLkbUAI = true;}
      while(PuYqZbdYOa == PuYqZbdYOa){mHEsCiGyCX = true;}
      if(RQLkQgOiiE == true){RQLkQgOiiE = false;}
      if(UXQISDQYMc == true){UXQISDQYMc = false;}
      if(TuddefCpFG == true){TuddefCpFG = false;}
      if(gRMPzcxGKk == true){gRMPzcxGKk = false;}
      if(ouTzbrePXW == true){ouTzbrePXW = false;}
      if(LFLlGWmhFk == true){LFLlGWmhFk = false;}
      if(dYdcWCKBJp == true){dYdcWCKBJp = false;}
      if(GKObmYbdBm == true){GKObmYbdBm = false;}
      if(BmRiubFaIb == true){BmRiubFaIb = false;}
      if(oOAZGQQpbY == true){oOAZGQQpbY = false;}
      if(gcGgPBqjzg == true){gcGgPBqjzg = false;}
      if(tIfSjqGuhu == true){tIfSjqGuhu = false;}
      if(xjrgBqJnUV == true){xjrgBqJnUV = false;}
      if(HkCcFXfjSt == true){HkCcFXfjSt = false;}
      if(kUbbhfihoP == true){kUbbhfihoP = false;}
      if(KVIgbxkYfY == true){KVIgbxkYfY = false;}
      if(qCOcYJGDML == true){qCOcYJGDML = false;}
      if(KVbnJbHQzU == true){KVbnJbHQzU = false;}
      if(IazFLkbUAI == true){IazFLkbUAI = false;}
      if(mHEsCiGyCX == true){mHEsCiGyCX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WCWRRGHQXP
{ 
  void SYkjbWncdq()
  { 
      bool SycPdnKASe = false;
      bool nUbrHAJuuK = false;
      bool HZYMIVVNfd = false;
      bool MudsxVqPOq = false;
      bool kGQkqdApnW = false;
      bool MBFMnrYQHI = false;
      bool RxTnRrqitk = false;
      bool JtfEZAJmUd = false;
      bool UfYJQKoQEE = false;
      bool waHGYmmcSy = false;
      bool mRuCNSUBmn = false;
      bool ilucmlXKWH = false;
      bool DZeoohmZel = false;
      bool MfUVqDjVuy = false;
      bool pmdQUKedSl = false;
      bool PcFLuNmFNe = false;
      bool ftVAaDQZlj = false;
      bool CBOYQPuNTd = false;
      bool DIGsWjaIac = false;
      bool QdIPSuRdoR = false;
      string JikYnCcWnI;
      string mpPEczjnLw;
      string GVjHnuDkgj;
      string rxolXqKPpU;
      string hpGyWLbuoY;
      string eoBNmnzcks;
      string zroDQoAcgl;
      string oTyqNQOkkb;
      string SHuHECubzi;
      string qgdwUoBDgg;
      string KzODjKpKzV;
      string ZNrJZqwgyN;
      string sYdytIoBVX;
      string PLDDQTsrXs;
      string MkbcJcnUWc;
      string sTETmkUQJb;
      string VonaGNKorG;
      string yEJEBIxAnQ;
      string UUeseuGjPf;
      string yciuXWwBWu;
      if(JikYnCcWnI == KzODjKpKzV){SycPdnKASe = true;}
      else if(KzODjKpKzV == JikYnCcWnI){mRuCNSUBmn = true;}
      if(mpPEczjnLw == ZNrJZqwgyN){nUbrHAJuuK = true;}
      else if(ZNrJZqwgyN == mpPEczjnLw){ilucmlXKWH = true;}
      if(GVjHnuDkgj == sYdytIoBVX){HZYMIVVNfd = true;}
      else if(sYdytIoBVX == GVjHnuDkgj){DZeoohmZel = true;}
      if(rxolXqKPpU == PLDDQTsrXs){MudsxVqPOq = true;}
      else if(PLDDQTsrXs == rxolXqKPpU){MfUVqDjVuy = true;}
      if(hpGyWLbuoY == MkbcJcnUWc){kGQkqdApnW = true;}
      else if(MkbcJcnUWc == hpGyWLbuoY){pmdQUKedSl = true;}
      if(eoBNmnzcks == sTETmkUQJb){MBFMnrYQHI = true;}
      else if(sTETmkUQJb == eoBNmnzcks){PcFLuNmFNe = true;}
      if(zroDQoAcgl == VonaGNKorG){RxTnRrqitk = true;}
      else if(VonaGNKorG == zroDQoAcgl){ftVAaDQZlj = true;}
      if(oTyqNQOkkb == yEJEBIxAnQ){JtfEZAJmUd = true;}
      if(SHuHECubzi == UUeseuGjPf){UfYJQKoQEE = true;}
      if(qgdwUoBDgg == yciuXWwBWu){waHGYmmcSy = true;}
      while(yEJEBIxAnQ == oTyqNQOkkb){CBOYQPuNTd = true;}
      while(UUeseuGjPf == UUeseuGjPf){DIGsWjaIac = true;}
      while(yciuXWwBWu == yciuXWwBWu){QdIPSuRdoR = true;}
      if(SycPdnKASe == true){SycPdnKASe = false;}
      if(nUbrHAJuuK == true){nUbrHAJuuK = false;}
      if(HZYMIVVNfd == true){HZYMIVVNfd = false;}
      if(MudsxVqPOq == true){MudsxVqPOq = false;}
      if(kGQkqdApnW == true){kGQkqdApnW = false;}
      if(MBFMnrYQHI == true){MBFMnrYQHI = false;}
      if(RxTnRrqitk == true){RxTnRrqitk = false;}
      if(JtfEZAJmUd == true){JtfEZAJmUd = false;}
      if(UfYJQKoQEE == true){UfYJQKoQEE = false;}
      if(waHGYmmcSy == true){waHGYmmcSy = false;}
      if(mRuCNSUBmn == true){mRuCNSUBmn = false;}
      if(ilucmlXKWH == true){ilucmlXKWH = false;}
      if(DZeoohmZel == true){DZeoohmZel = false;}
      if(MfUVqDjVuy == true){MfUVqDjVuy = false;}
      if(pmdQUKedSl == true){pmdQUKedSl = false;}
      if(PcFLuNmFNe == true){PcFLuNmFNe = false;}
      if(ftVAaDQZlj == true){ftVAaDQZlj = false;}
      if(CBOYQPuNTd == true){CBOYQPuNTd = false;}
      if(DIGsWjaIac == true){DIGsWjaIac = false;}
      if(QdIPSuRdoR == true){QdIPSuRdoR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSOODRXHLE
{ 
  void FgfyODAaZy()
  { 
      bool yKBuDpYWoR = false;
      bool dilyDosUVO = false;
      bool ooDKqNqdLF = false;
      bool TWjbgaQpMs = false;
      bool yxlGkscUkf = false;
      bool KOAPxJHqDo = false;
      bool ztLixGyJQc = false;
      bool YDIbQqCwYx = false;
      bool jWreuFWTeX = false;
      bool TYlWtDlDJd = false;
      bool tSDIHGGXzF = false;
      bool HKRFFcCgnr = false;
      bool ieesJzRlgN = false;
      bool FzluDRSjWn = false;
      bool yyTYPIGfRR = false;
      bool AEORtPmJyH = false;
      bool oUplzHXWCm = false;
      bool JSJAskKGcA = false;
      bool skUPMAjUAm = false;
      bool dJkPydHhZI = false;
      string URZCameZIC;
      string crKnLFJQIh;
      string fxLMLbVylP;
      string xCDQALXcHo;
      string ncIuVgWxat;
      string ilAkBWGNpy;
      string QfnrEantmA;
      string hgITsCoQpe;
      string EYXqgLBSOd;
      string EJmIXInPqu;
      string rcJZMCdgqz;
      string hpWLtrHxLr;
      string YUeJuXtzwk;
      string NYZulaOxdd;
      string hUbPuOlaOf;
      string AqEyVWyzeo;
      string IdjFkJPbYT;
      string cJSgJEsONf;
      string kSkPjWTaYO;
      string bOSoVEjVel;
      if(URZCameZIC == rcJZMCdgqz){yKBuDpYWoR = true;}
      else if(rcJZMCdgqz == URZCameZIC){tSDIHGGXzF = true;}
      if(crKnLFJQIh == hpWLtrHxLr){dilyDosUVO = true;}
      else if(hpWLtrHxLr == crKnLFJQIh){HKRFFcCgnr = true;}
      if(fxLMLbVylP == YUeJuXtzwk){ooDKqNqdLF = true;}
      else if(YUeJuXtzwk == fxLMLbVylP){ieesJzRlgN = true;}
      if(xCDQALXcHo == NYZulaOxdd){TWjbgaQpMs = true;}
      else if(NYZulaOxdd == xCDQALXcHo){FzluDRSjWn = true;}
      if(ncIuVgWxat == hUbPuOlaOf){yxlGkscUkf = true;}
      else if(hUbPuOlaOf == ncIuVgWxat){yyTYPIGfRR = true;}
      if(ilAkBWGNpy == AqEyVWyzeo){KOAPxJHqDo = true;}
      else if(AqEyVWyzeo == ilAkBWGNpy){AEORtPmJyH = true;}
      if(QfnrEantmA == IdjFkJPbYT){ztLixGyJQc = true;}
      else if(IdjFkJPbYT == QfnrEantmA){oUplzHXWCm = true;}
      if(hgITsCoQpe == cJSgJEsONf){YDIbQqCwYx = true;}
      if(EYXqgLBSOd == kSkPjWTaYO){jWreuFWTeX = true;}
      if(EJmIXInPqu == bOSoVEjVel){TYlWtDlDJd = true;}
      while(cJSgJEsONf == hgITsCoQpe){JSJAskKGcA = true;}
      while(kSkPjWTaYO == kSkPjWTaYO){skUPMAjUAm = true;}
      while(bOSoVEjVel == bOSoVEjVel){dJkPydHhZI = true;}
      if(yKBuDpYWoR == true){yKBuDpYWoR = false;}
      if(dilyDosUVO == true){dilyDosUVO = false;}
      if(ooDKqNqdLF == true){ooDKqNqdLF = false;}
      if(TWjbgaQpMs == true){TWjbgaQpMs = false;}
      if(yxlGkscUkf == true){yxlGkscUkf = false;}
      if(KOAPxJHqDo == true){KOAPxJHqDo = false;}
      if(ztLixGyJQc == true){ztLixGyJQc = false;}
      if(YDIbQqCwYx == true){YDIbQqCwYx = false;}
      if(jWreuFWTeX == true){jWreuFWTeX = false;}
      if(TYlWtDlDJd == true){TYlWtDlDJd = false;}
      if(tSDIHGGXzF == true){tSDIHGGXzF = false;}
      if(HKRFFcCgnr == true){HKRFFcCgnr = false;}
      if(ieesJzRlgN == true){ieesJzRlgN = false;}
      if(FzluDRSjWn == true){FzluDRSjWn = false;}
      if(yyTYPIGfRR == true){yyTYPIGfRR = false;}
      if(AEORtPmJyH == true){AEORtPmJyH = false;}
      if(oUplzHXWCm == true){oUplzHXWCm = false;}
      if(JSJAskKGcA == true){JSJAskKGcA = false;}
      if(skUPMAjUAm == true){skUPMAjUAm = false;}
      if(dJkPydHhZI == true){dJkPydHhZI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XJPOARSLVY
{ 
  void eJwWrTtpXp()
  { 
      bool WBFFLymftA = false;
      bool qFHxHbxFko = false;
      bool nryRuMbGMg = false;
      bool YzDViOFwko = false;
      bool qGrheGVFGF = false;
      bool gAaUldDmJz = false;
      bool VgTNbqBkOs = false;
      bool WAUwygAPmo = false;
      bool qWAGzXYhiE = false;
      bool LRllSKmeGm = false;
      bool EjpMiffdWE = false;
      bool dmzUIzgMND = false;
      bool SSCKgEOhdn = false;
      bool tVJAjGfmXT = false;
      bool qtLdZXRQdT = false;
      bool cZQCUlgffe = false;
      bool QyAiKIczkB = false;
      bool StotLXHXjI = false;
      bool lxEJKTEGfx = false;
      bool YAHsCstbTR = false;
      string AHwsVfJVpp;
      string hdfNFqJqyC;
      string eNDMDpZGGQ;
      string NgCyaaOwec;
      string TcNTYcwooy;
      string EYVZKlEjof;
      string GDOZbBahmd;
      string cMMUhCzima;
      string sjRHLnKcnn;
      string WdHyWQOmrX;
      string BNCKVqMAqI;
      string mVwNlVlGNm;
      string pytyHyENxR;
      string mLqPZegGlT;
      string bKkfBBhsMA;
      string dIZEgDTEDX;
      string myDYUadgnG;
      string ofUsKfMOwF;
      string PKBxmelliV;
      string LcDNgdGMKa;
      if(AHwsVfJVpp == BNCKVqMAqI){WBFFLymftA = true;}
      else if(BNCKVqMAqI == AHwsVfJVpp){EjpMiffdWE = true;}
      if(hdfNFqJqyC == mVwNlVlGNm){qFHxHbxFko = true;}
      else if(mVwNlVlGNm == hdfNFqJqyC){dmzUIzgMND = true;}
      if(eNDMDpZGGQ == pytyHyENxR){nryRuMbGMg = true;}
      else if(pytyHyENxR == eNDMDpZGGQ){SSCKgEOhdn = true;}
      if(NgCyaaOwec == mLqPZegGlT){YzDViOFwko = true;}
      else if(mLqPZegGlT == NgCyaaOwec){tVJAjGfmXT = true;}
      if(TcNTYcwooy == bKkfBBhsMA){qGrheGVFGF = true;}
      else if(bKkfBBhsMA == TcNTYcwooy){qtLdZXRQdT = true;}
      if(EYVZKlEjof == dIZEgDTEDX){gAaUldDmJz = true;}
      else if(dIZEgDTEDX == EYVZKlEjof){cZQCUlgffe = true;}
      if(GDOZbBahmd == myDYUadgnG){VgTNbqBkOs = true;}
      else if(myDYUadgnG == GDOZbBahmd){QyAiKIczkB = true;}
      if(cMMUhCzima == ofUsKfMOwF){WAUwygAPmo = true;}
      if(sjRHLnKcnn == PKBxmelliV){qWAGzXYhiE = true;}
      if(WdHyWQOmrX == LcDNgdGMKa){LRllSKmeGm = true;}
      while(ofUsKfMOwF == cMMUhCzima){StotLXHXjI = true;}
      while(PKBxmelliV == PKBxmelliV){lxEJKTEGfx = true;}
      while(LcDNgdGMKa == LcDNgdGMKa){YAHsCstbTR = true;}
      if(WBFFLymftA == true){WBFFLymftA = false;}
      if(qFHxHbxFko == true){qFHxHbxFko = false;}
      if(nryRuMbGMg == true){nryRuMbGMg = false;}
      if(YzDViOFwko == true){YzDViOFwko = false;}
      if(qGrheGVFGF == true){qGrheGVFGF = false;}
      if(gAaUldDmJz == true){gAaUldDmJz = false;}
      if(VgTNbqBkOs == true){VgTNbqBkOs = false;}
      if(WAUwygAPmo == true){WAUwygAPmo = false;}
      if(qWAGzXYhiE == true){qWAGzXYhiE = false;}
      if(LRllSKmeGm == true){LRllSKmeGm = false;}
      if(EjpMiffdWE == true){EjpMiffdWE = false;}
      if(dmzUIzgMND == true){dmzUIzgMND = false;}
      if(SSCKgEOhdn == true){SSCKgEOhdn = false;}
      if(tVJAjGfmXT == true){tVJAjGfmXT = false;}
      if(qtLdZXRQdT == true){qtLdZXRQdT = false;}
      if(cZQCUlgffe == true){cZQCUlgffe = false;}
      if(QyAiKIczkB == true){QyAiKIczkB = false;}
      if(StotLXHXjI == true){StotLXHXjI = false;}
      if(lxEJKTEGfx == true){lxEJKTEGfx = false;}
      if(YAHsCstbTR == true){YAHsCstbTR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PEJDWMGCVN
{ 
  void cDZNjQDJje()
  { 
      bool jWCSYiVreP = false;
      bool WenVLllGJK = false;
      bool GolloqjQQU = false;
      bool sKLCadkZHR = false;
      bool qhhGmbcHiy = false;
      bool euzyltjQch = false;
      bool yEaJVMSkuh = false;
      bool BMyrSXHezM = false;
      bool NbhSoyKMPf = false;
      bool sTwZTmGXka = false;
      bool JrMBwSwHfO = false;
      bool mFRPTVWHUX = false;
      bool BGUPngQYXf = false;
      bool QitXDVPfWW = false;
      bool BCfBrnCfFy = false;
      bool PyCMYCWxNO = false;
      bool BWiAxDKsLy = false;
      bool FpkyVyZTWz = false;
      bool ejTZPRfhzB = false;
      bool ySSIUeSfEn = false;
      string sybIbblbAL;
      string gbXCiAGFQE;
      string YQqFePKZEQ;
      string uDJTEWtYeJ;
      string iaoPZyGDmA;
      string tMKeScGWcM;
      string QLXiQdSDxL;
      string FhZHVyabef;
      string JGlDWhrdBb;
      string PXuSrWCGyw;
      string fCFbuMlCJT;
      string BeqwDJYUMh;
      string koCVuhlHPy;
      string uUchAGBKIK;
      string woUgZkfyPh;
      string xhtQLqzjfN;
      string ZemKXgBJww;
      string IOLBluTUuK;
      string BmrgANaMWJ;
      string GRdujRBJJs;
      if(sybIbblbAL == fCFbuMlCJT){jWCSYiVreP = true;}
      else if(fCFbuMlCJT == sybIbblbAL){JrMBwSwHfO = true;}
      if(gbXCiAGFQE == BeqwDJYUMh){WenVLllGJK = true;}
      else if(BeqwDJYUMh == gbXCiAGFQE){mFRPTVWHUX = true;}
      if(YQqFePKZEQ == koCVuhlHPy){GolloqjQQU = true;}
      else if(koCVuhlHPy == YQqFePKZEQ){BGUPngQYXf = true;}
      if(uDJTEWtYeJ == uUchAGBKIK){sKLCadkZHR = true;}
      else if(uUchAGBKIK == uDJTEWtYeJ){QitXDVPfWW = true;}
      if(iaoPZyGDmA == woUgZkfyPh){qhhGmbcHiy = true;}
      else if(woUgZkfyPh == iaoPZyGDmA){BCfBrnCfFy = true;}
      if(tMKeScGWcM == xhtQLqzjfN){euzyltjQch = true;}
      else if(xhtQLqzjfN == tMKeScGWcM){PyCMYCWxNO = true;}
      if(QLXiQdSDxL == ZemKXgBJww){yEaJVMSkuh = true;}
      else if(ZemKXgBJww == QLXiQdSDxL){BWiAxDKsLy = true;}
      if(FhZHVyabef == IOLBluTUuK){BMyrSXHezM = true;}
      if(JGlDWhrdBb == BmrgANaMWJ){NbhSoyKMPf = true;}
      if(PXuSrWCGyw == GRdujRBJJs){sTwZTmGXka = true;}
      while(IOLBluTUuK == FhZHVyabef){FpkyVyZTWz = true;}
      while(BmrgANaMWJ == BmrgANaMWJ){ejTZPRfhzB = true;}
      while(GRdujRBJJs == GRdujRBJJs){ySSIUeSfEn = true;}
      if(jWCSYiVreP == true){jWCSYiVreP = false;}
      if(WenVLllGJK == true){WenVLllGJK = false;}
      if(GolloqjQQU == true){GolloqjQQU = false;}
      if(sKLCadkZHR == true){sKLCadkZHR = false;}
      if(qhhGmbcHiy == true){qhhGmbcHiy = false;}
      if(euzyltjQch == true){euzyltjQch = false;}
      if(yEaJVMSkuh == true){yEaJVMSkuh = false;}
      if(BMyrSXHezM == true){BMyrSXHezM = false;}
      if(NbhSoyKMPf == true){NbhSoyKMPf = false;}
      if(sTwZTmGXka == true){sTwZTmGXka = false;}
      if(JrMBwSwHfO == true){JrMBwSwHfO = false;}
      if(mFRPTVWHUX == true){mFRPTVWHUX = false;}
      if(BGUPngQYXf == true){BGUPngQYXf = false;}
      if(QitXDVPfWW == true){QitXDVPfWW = false;}
      if(BCfBrnCfFy == true){BCfBrnCfFy = false;}
      if(PyCMYCWxNO == true){PyCMYCWxNO = false;}
      if(BWiAxDKsLy == true){BWiAxDKsLy = false;}
      if(FpkyVyZTWz == true){FpkyVyZTWz = false;}
      if(ejTZPRfhzB == true){ejTZPRfhzB = false;}
      if(ySSIUeSfEn == true){ySSIUeSfEn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QRTFJFPBEM
{ 
  void rAJFsghdpH()
  { 
      bool GaTUmiadDJ = false;
      bool OQkQBqbAiw = false;
      bool gBbXYUqNJe = false;
      bool xisdIThxtc = false;
      bool ZKPUaQYrmO = false;
      bool DsfCcEzwuS = false;
      bool qMUXLeWGIh = false;
      bool JdGGVWlGwH = false;
      bool uzatbDDqAD = false;
      bool TkBblMpqIw = false;
      bool sSiEFYmYfG = false;
      bool SrAnWqlZwH = false;
      bool afFFNYceUI = false;
      bool gtyzNcPVoC = false;
      bool QeKtkbkNEt = false;
      bool aPuAVNMdqg = false;
      bool wIEXZXtAZt = false;
      bool bPksqwVLTl = false;
      bool nPZZhRyxdA = false;
      bool QkeHGHZmUM = false;
      string tArESiyajF;
      string QdDnbxaPTu;
      string LxUFMmjycp;
      string LiQthIDqBh;
      string ZPEqEkDCnR;
      string MAVNWxflre;
      string yAytthNJGS;
      string siOkVwsdBa;
      string jgKKdKNDWj;
      string cRzVjZRKxV;
      string XtwVYcljra;
      string EBkQuQonQi;
      string UKlVpbjrBw;
      string dhgeDokokA;
      string YcKufaghaS;
      string jctNBNHafw;
      string ssiuxVUFNF;
      string eACPKrzqoO;
      string uBRhLBnSdp;
      string gKInGetPyK;
      if(tArESiyajF == XtwVYcljra){GaTUmiadDJ = true;}
      else if(XtwVYcljra == tArESiyajF){sSiEFYmYfG = true;}
      if(QdDnbxaPTu == EBkQuQonQi){OQkQBqbAiw = true;}
      else if(EBkQuQonQi == QdDnbxaPTu){SrAnWqlZwH = true;}
      if(LxUFMmjycp == UKlVpbjrBw){gBbXYUqNJe = true;}
      else if(UKlVpbjrBw == LxUFMmjycp){afFFNYceUI = true;}
      if(LiQthIDqBh == dhgeDokokA){xisdIThxtc = true;}
      else if(dhgeDokokA == LiQthIDqBh){gtyzNcPVoC = true;}
      if(ZPEqEkDCnR == YcKufaghaS){ZKPUaQYrmO = true;}
      else if(YcKufaghaS == ZPEqEkDCnR){QeKtkbkNEt = true;}
      if(MAVNWxflre == jctNBNHafw){DsfCcEzwuS = true;}
      else if(jctNBNHafw == MAVNWxflre){aPuAVNMdqg = true;}
      if(yAytthNJGS == ssiuxVUFNF){qMUXLeWGIh = true;}
      else if(ssiuxVUFNF == yAytthNJGS){wIEXZXtAZt = true;}
      if(siOkVwsdBa == eACPKrzqoO){JdGGVWlGwH = true;}
      if(jgKKdKNDWj == uBRhLBnSdp){uzatbDDqAD = true;}
      if(cRzVjZRKxV == gKInGetPyK){TkBblMpqIw = true;}
      while(eACPKrzqoO == siOkVwsdBa){bPksqwVLTl = true;}
      while(uBRhLBnSdp == uBRhLBnSdp){nPZZhRyxdA = true;}
      while(gKInGetPyK == gKInGetPyK){QkeHGHZmUM = true;}
      if(GaTUmiadDJ == true){GaTUmiadDJ = false;}
      if(OQkQBqbAiw == true){OQkQBqbAiw = false;}
      if(gBbXYUqNJe == true){gBbXYUqNJe = false;}
      if(xisdIThxtc == true){xisdIThxtc = false;}
      if(ZKPUaQYrmO == true){ZKPUaQYrmO = false;}
      if(DsfCcEzwuS == true){DsfCcEzwuS = false;}
      if(qMUXLeWGIh == true){qMUXLeWGIh = false;}
      if(JdGGVWlGwH == true){JdGGVWlGwH = false;}
      if(uzatbDDqAD == true){uzatbDDqAD = false;}
      if(TkBblMpqIw == true){TkBblMpqIw = false;}
      if(sSiEFYmYfG == true){sSiEFYmYfG = false;}
      if(SrAnWqlZwH == true){SrAnWqlZwH = false;}
      if(afFFNYceUI == true){afFFNYceUI = false;}
      if(gtyzNcPVoC == true){gtyzNcPVoC = false;}
      if(QeKtkbkNEt == true){QeKtkbkNEt = false;}
      if(aPuAVNMdqg == true){aPuAVNMdqg = false;}
      if(wIEXZXtAZt == true){wIEXZXtAZt = false;}
      if(bPksqwVLTl == true){bPksqwVLTl = false;}
      if(nPZZhRyxdA == true){nPZZhRyxdA = false;}
      if(QkeHGHZmUM == true){QkeHGHZmUM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DJWKIZHHRQ
{ 
  void pLxwYpOZTT()
  { 
      bool ooXFsIFAYV = false;
      bool moVfRsUFht = false;
      bool heXLSTuque = false;
      bool ILzqGddRfV = false;
      bool BQNaWogTrj = false;
      bool PBbFfJRLlY = false;
      bool NOFtMaoeYm = false;
      bool OCYMsRRxod = false;
      bool mbyLPHjsLx = false;
      bool MSfHHlLTOu = false;
      bool zCtFUMbOMO = false;
      bool qTWIklPsdE = false;
      bool quTbawWRFH = false;
      bool GyisdkgspD = false;
      bool eUgwFrwXVV = false;
      bool VRoJDEhSeY = false;
      bool pKJFIskcdA = false;
      bool FWCaZWNWVh = false;
      bool zzwjknIZpZ = false;
      bool CNORMULbnL = false;
      string mTqCtJVTqe;
      string onSUHcaewN;
      string YnSRoUkrOh;
      string xgYyBClwop;
      string EHcMwRLNkF;
      string UFaFfzAYMY;
      string YdEIhHOTTF;
      string pdoGJQKGVW;
      string JXHJNqFTRB;
      string BMiQQaCTen;
      string DqseOpPTwP;
      string otCoOBWuup;
      string CtCRDduYoi;
      string NpbhTSdbtW;
      string alXCMHJsBP;
      string DGYnlJoabk;
      string tqeNBzSUVw;
      string WtAXOPVAFw;
      string TBWYeGQmwJ;
      string dCzJcjGKAN;
      if(mTqCtJVTqe == DqseOpPTwP){ooXFsIFAYV = true;}
      else if(DqseOpPTwP == mTqCtJVTqe){zCtFUMbOMO = true;}
      if(onSUHcaewN == otCoOBWuup){moVfRsUFht = true;}
      else if(otCoOBWuup == onSUHcaewN){qTWIklPsdE = true;}
      if(YnSRoUkrOh == CtCRDduYoi){heXLSTuque = true;}
      else if(CtCRDduYoi == YnSRoUkrOh){quTbawWRFH = true;}
      if(xgYyBClwop == NpbhTSdbtW){ILzqGddRfV = true;}
      else if(NpbhTSdbtW == xgYyBClwop){GyisdkgspD = true;}
      if(EHcMwRLNkF == alXCMHJsBP){BQNaWogTrj = true;}
      else if(alXCMHJsBP == EHcMwRLNkF){eUgwFrwXVV = true;}
      if(UFaFfzAYMY == DGYnlJoabk){PBbFfJRLlY = true;}
      else if(DGYnlJoabk == UFaFfzAYMY){VRoJDEhSeY = true;}
      if(YdEIhHOTTF == tqeNBzSUVw){NOFtMaoeYm = true;}
      else if(tqeNBzSUVw == YdEIhHOTTF){pKJFIskcdA = true;}
      if(pdoGJQKGVW == WtAXOPVAFw){OCYMsRRxod = true;}
      if(JXHJNqFTRB == TBWYeGQmwJ){mbyLPHjsLx = true;}
      if(BMiQQaCTen == dCzJcjGKAN){MSfHHlLTOu = true;}
      while(WtAXOPVAFw == pdoGJQKGVW){FWCaZWNWVh = true;}
      while(TBWYeGQmwJ == TBWYeGQmwJ){zzwjknIZpZ = true;}
      while(dCzJcjGKAN == dCzJcjGKAN){CNORMULbnL = true;}
      if(ooXFsIFAYV == true){ooXFsIFAYV = false;}
      if(moVfRsUFht == true){moVfRsUFht = false;}
      if(heXLSTuque == true){heXLSTuque = false;}
      if(ILzqGddRfV == true){ILzqGddRfV = false;}
      if(BQNaWogTrj == true){BQNaWogTrj = false;}
      if(PBbFfJRLlY == true){PBbFfJRLlY = false;}
      if(NOFtMaoeYm == true){NOFtMaoeYm = false;}
      if(OCYMsRRxod == true){OCYMsRRxod = false;}
      if(mbyLPHjsLx == true){mbyLPHjsLx = false;}
      if(MSfHHlLTOu == true){MSfHHlLTOu = false;}
      if(zCtFUMbOMO == true){zCtFUMbOMO = false;}
      if(qTWIklPsdE == true){qTWIklPsdE = false;}
      if(quTbawWRFH == true){quTbawWRFH = false;}
      if(GyisdkgspD == true){GyisdkgspD = false;}
      if(eUgwFrwXVV == true){eUgwFrwXVV = false;}
      if(VRoJDEhSeY == true){VRoJDEhSeY = false;}
      if(pKJFIskcdA == true){pKJFIskcdA = false;}
      if(FWCaZWNWVh == true){FWCaZWNWVh = false;}
      if(zzwjknIZpZ == true){zzwjknIZpZ = false;}
      if(CNORMULbnL == true){CNORMULbnL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XINWBRMVEC
{ 
  void ixOmmGwnZg()
  { 
      bool hQGiRgPmct = false;
      bool JEKwlrqbUi = false;
      bool rDTdrBPQTs = false;
      bool enCPfjPzoP = false;
      bool fkXeGHMGnJ = false;
      bool MOPGIdxcqP = false;
      bool QyTjOUCtPB = false;
      bool bqmFCGfnXj = false;
      bool nJcJfQXuHB = false;
      bool mmIYygRmPk = false;
      bool FRplhVaJEC = false;
      bool yIEGaHUJDy = false;
      bool xGmOOnhNGU = false;
      bool nrYleVSqbK = false;
      bool oNqFCdhCxq = false;
      bool LHjRnyeaWs = false;
      bool mNDiNFjRbE = false;
      bool ndhsIiPhLj = false;
      bool GfQPJgIHyf = false;
      bool qqThXbKIrw = false;
      string xoyNUKMjAs;
      string zAJtzjJCOM;
      string pTeNMoYHSH;
      string ryGutddsfB;
      string kboCLDWMhF;
      string DSsotcJkAf;
      string kFRrAAsNAV;
      string FQWNbNecBI;
      string SLYMEZFQBQ;
      string TsrAPeKxBL;
      string KJLLzmwfNg;
      string ygirMYfEna;
      string ubMiBLXVxw;
      string ChbpyIAMNR;
      string dYDTRmKAmp;
      string zGIZQhwbKm;
      string PZiRdQEssE;
      string YSqVxVYrRN;
      string BWiGwuYBZP;
      string LXCZCDpkoB;
      if(xoyNUKMjAs == KJLLzmwfNg){hQGiRgPmct = true;}
      else if(KJLLzmwfNg == xoyNUKMjAs){FRplhVaJEC = true;}
      if(zAJtzjJCOM == ygirMYfEna){JEKwlrqbUi = true;}
      else if(ygirMYfEna == zAJtzjJCOM){yIEGaHUJDy = true;}
      if(pTeNMoYHSH == ubMiBLXVxw){rDTdrBPQTs = true;}
      else if(ubMiBLXVxw == pTeNMoYHSH){xGmOOnhNGU = true;}
      if(ryGutddsfB == ChbpyIAMNR){enCPfjPzoP = true;}
      else if(ChbpyIAMNR == ryGutddsfB){nrYleVSqbK = true;}
      if(kboCLDWMhF == dYDTRmKAmp){fkXeGHMGnJ = true;}
      else if(dYDTRmKAmp == kboCLDWMhF){oNqFCdhCxq = true;}
      if(DSsotcJkAf == zGIZQhwbKm){MOPGIdxcqP = true;}
      else if(zGIZQhwbKm == DSsotcJkAf){LHjRnyeaWs = true;}
      if(kFRrAAsNAV == PZiRdQEssE){QyTjOUCtPB = true;}
      else if(PZiRdQEssE == kFRrAAsNAV){mNDiNFjRbE = true;}
      if(FQWNbNecBI == YSqVxVYrRN){bqmFCGfnXj = true;}
      if(SLYMEZFQBQ == BWiGwuYBZP){nJcJfQXuHB = true;}
      if(TsrAPeKxBL == LXCZCDpkoB){mmIYygRmPk = true;}
      while(YSqVxVYrRN == FQWNbNecBI){ndhsIiPhLj = true;}
      while(BWiGwuYBZP == BWiGwuYBZP){GfQPJgIHyf = true;}
      while(LXCZCDpkoB == LXCZCDpkoB){qqThXbKIrw = true;}
      if(hQGiRgPmct == true){hQGiRgPmct = false;}
      if(JEKwlrqbUi == true){JEKwlrqbUi = false;}
      if(rDTdrBPQTs == true){rDTdrBPQTs = false;}
      if(enCPfjPzoP == true){enCPfjPzoP = false;}
      if(fkXeGHMGnJ == true){fkXeGHMGnJ = false;}
      if(MOPGIdxcqP == true){MOPGIdxcqP = false;}
      if(QyTjOUCtPB == true){QyTjOUCtPB = false;}
      if(bqmFCGfnXj == true){bqmFCGfnXj = false;}
      if(nJcJfQXuHB == true){nJcJfQXuHB = false;}
      if(mmIYygRmPk == true){mmIYygRmPk = false;}
      if(FRplhVaJEC == true){FRplhVaJEC = false;}
      if(yIEGaHUJDy == true){yIEGaHUJDy = false;}
      if(xGmOOnhNGU == true){xGmOOnhNGU = false;}
      if(nrYleVSqbK == true){nrYleVSqbK = false;}
      if(oNqFCdhCxq == true){oNqFCdhCxq = false;}
      if(LHjRnyeaWs == true){LHjRnyeaWs = false;}
      if(mNDiNFjRbE == true){mNDiNFjRbE = false;}
      if(ndhsIiPhLj == true){ndhsIiPhLj = false;}
      if(GfQPJgIHyf == true){GfQPJgIHyf = false;}
      if(qqThXbKIrw == true){qqThXbKIrw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NPMEEXZAIM
{ 
  void uDPJFWRHeL()
  { 
      bool FBSwGTMcWH = false;
      bool BfCIuyQUNZ = false;
      bool XBqHeGqCGi = false;
      bool HxPuxKASjS = false;
      bool qzxTcmNQCO = false;
      bool hcTrZDKLQz = false;
      bool cJVmzEQGLj = false;
      bool yxktiXDWdr = false;
      bool saArAecWVt = false;
      bool AoCjpgcKTY = false;
      bool WGESQkrZJB = false;
      bool zmhYGBJclU = false;
      bool atkRjIuBDB = false;
      bool usCEVlVhbP = false;
      bool lDMTtMHccn = false;
      bool XzXzxcUmhH = false;
      bool opVIGGkcDT = false;
      bool fbBWhXgRWX = false;
      bool BRXOduUDGs = false;
      bool RhzUZwgENm = false;
      string mjwKCextKh;
      string RJzcMZXWec;
      string FquNMswStm;
      string yHqaQLNykw;
      string RTUCpKRyqA;
      string QcPjhunhxI;
      string hdzXiJSXLB;
      string MYliLlWrXB;
      string bybsWVqGsV;
      string WeAbNmTxSg;
      string rslpnqpgYw;
      string YuKugiCGAN;
      string RMepdgYKUX;
      string RYZqJhMkFf;
      string eKhwxaUEud;
      string kNxFOeOuLH;
      string SfLAdzVSly;
      string WQAThGdhsC;
      string LTOpmEbUbd;
      string TQZyNzygSx;
      if(mjwKCextKh == rslpnqpgYw){FBSwGTMcWH = true;}
      else if(rslpnqpgYw == mjwKCextKh){WGESQkrZJB = true;}
      if(RJzcMZXWec == YuKugiCGAN){BfCIuyQUNZ = true;}
      else if(YuKugiCGAN == RJzcMZXWec){zmhYGBJclU = true;}
      if(FquNMswStm == RMepdgYKUX){XBqHeGqCGi = true;}
      else if(RMepdgYKUX == FquNMswStm){atkRjIuBDB = true;}
      if(yHqaQLNykw == RYZqJhMkFf){HxPuxKASjS = true;}
      else if(RYZqJhMkFf == yHqaQLNykw){usCEVlVhbP = true;}
      if(RTUCpKRyqA == eKhwxaUEud){qzxTcmNQCO = true;}
      else if(eKhwxaUEud == RTUCpKRyqA){lDMTtMHccn = true;}
      if(QcPjhunhxI == kNxFOeOuLH){hcTrZDKLQz = true;}
      else if(kNxFOeOuLH == QcPjhunhxI){XzXzxcUmhH = true;}
      if(hdzXiJSXLB == SfLAdzVSly){cJVmzEQGLj = true;}
      else if(SfLAdzVSly == hdzXiJSXLB){opVIGGkcDT = true;}
      if(MYliLlWrXB == WQAThGdhsC){yxktiXDWdr = true;}
      if(bybsWVqGsV == LTOpmEbUbd){saArAecWVt = true;}
      if(WeAbNmTxSg == TQZyNzygSx){AoCjpgcKTY = true;}
      while(WQAThGdhsC == MYliLlWrXB){fbBWhXgRWX = true;}
      while(LTOpmEbUbd == LTOpmEbUbd){BRXOduUDGs = true;}
      while(TQZyNzygSx == TQZyNzygSx){RhzUZwgENm = true;}
      if(FBSwGTMcWH == true){FBSwGTMcWH = false;}
      if(BfCIuyQUNZ == true){BfCIuyQUNZ = false;}
      if(XBqHeGqCGi == true){XBqHeGqCGi = false;}
      if(HxPuxKASjS == true){HxPuxKASjS = false;}
      if(qzxTcmNQCO == true){qzxTcmNQCO = false;}
      if(hcTrZDKLQz == true){hcTrZDKLQz = false;}
      if(cJVmzEQGLj == true){cJVmzEQGLj = false;}
      if(yxktiXDWdr == true){yxktiXDWdr = false;}
      if(saArAecWVt == true){saArAecWVt = false;}
      if(AoCjpgcKTY == true){AoCjpgcKTY = false;}
      if(WGESQkrZJB == true){WGESQkrZJB = false;}
      if(zmhYGBJclU == true){zmhYGBJclU = false;}
      if(atkRjIuBDB == true){atkRjIuBDB = false;}
      if(usCEVlVhbP == true){usCEVlVhbP = false;}
      if(lDMTtMHccn == true){lDMTtMHccn = false;}
      if(XzXzxcUmhH == true){XzXzxcUmhH = false;}
      if(opVIGGkcDT == true){opVIGGkcDT = false;}
      if(fbBWhXgRWX == true){fbBWhXgRWX = false;}
      if(BRXOduUDGs == true){BRXOduUDGs = false;}
      if(RhzUZwgENm == true){RhzUZwgENm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKRRVAXQVF
{ 
  void nAgdnazsdN()
  { 
      bool yKhDKAxOSk = false;
      bool BAWVietXTr = false;
      bool FNXKePFBVK = false;
      bool GWgtrAtgSn = false;
      bool tPjWpjsBXj = false;
      bool SQxuWjlXXt = false;
      bool uwrIedSbch = false;
      bool jNFfxodBTu = false;
      bool WEdkroZkXH = false;
      bool OVIYryWbqL = false;
      bool QQXozELRyg = false;
      bool GkEbXpSGQo = false;
      bool EgDVTOEfmz = false;
      bool RBJHeFgnkm = false;
      bool dImqBcRfAB = false;
      bool eQLBGiMBUk = false;
      bool zedyOEbwxR = false;
      bool JdUcLwtMUq = false;
      bool wYekUBpHBu = false;
      bool seTAmydnbw = false;
      string jMHPboNMpi;
      string fnGZaEURCD;
      string hmybwlQCGr;
      string tgcEUqqmbD;
      string yUDwSMRfBJ;
      string BVUewwOeSo;
      string YKGxozKBFi;
      string NhoyFNiCJi;
      string UjAxpYMyHX;
      string cLUmemOGHT;
      string CPaRuTgVZi;
      string MMVjUoKIGP;
      string lMtgGBMCTR;
      string yctogFIhBV;
      string rqYYKPpkRp;
      string cFzqgoVsLt;
      string GeBHkiRfCO;
      string fbHkXunUVp;
      string KbjcnrdDIr;
      string jPWGONoQnb;
      if(jMHPboNMpi == CPaRuTgVZi){yKhDKAxOSk = true;}
      else if(CPaRuTgVZi == jMHPboNMpi){QQXozELRyg = true;}
      if(fnGZaEURCD == MMVjUoKIGP){BAWVietXTr = true;}
      else if(MMVjUoKIGP == fnGZaEURCD){GkEbXpSGQo = true;}
      if(hmybwlQCGr == lMtgGBMCTR){FNXKePFBVK = true;}
      else if(lMtgGBMCTR == hmybwlQCGr){EgDVTOEfmz = true;}
      if(tgcEUqqmbD == yctogFIhBV){GWgtrAtgSn = true;}
      else if(yctogFIhBV == tgcEUqqmbD){RBJHeFgnkm = true;}
      if(yUDwSMRfBJ == rqYYKPpkRp){tPjWpjsBXj = true;}
      else if(rqYYKPpkRp == yUDwSMRfBJ){dImqBcRfAB = true;}
      if(BVUewwOeSo == cFzqgoVsLt){SQxuWjlXXt = true;}
      else if(cFzqgoVsLt == BVUewwOeSo){eQLBGiMBUk = true;}
      if(YKGxozKBFi == GeBHkiRfCO){uwrIedSbch = true;}
      else if(GeBHkiRfCO == YKGxozKBFi){zedyOEbwxR = true;}
      if(NhoyFNiCJi == fbHkXunUVp){jNFfxodBTu = true;}
      if(UjAxpYMyHX == KbjcnrdDIr){WEdkroZkXH = true;}
      if(cLUmemOGHT == jPWGONoQnb){OVIYryWbqL = true;}
      while(fbHkXunUVp == NhoyFNiCJi){JdUcLwtMUq = true;}
      while(KbjcnrdDIr == KbjcnrdDIr){wYekUBpHBu = true;}
      while(jPWGONoQnb == jPWGONoQnb){seTAmydnbw = true;}
      if(yKhDKAxOSk == true){yKhDKAxOSk = false;}
      if(BAWVietXTr == true){BAWVietXTr = false;}
      if(FNXKePFBVK == true){FNXKePFBVK = false;}
      if(GWgtrAtgSn == true){GWgtrAtgSn = false;}
      if(tPjWpjsBXj == true){tPjWpjsBXj = false;}
      if(SQxuWjlXXt == true){SQxuWjlXXt = false;}
      if(uwrIedSbch == true){uwrIedSbch = false;}
      if(jNFfxodBTu == true){jNFfxodBTu = false;}
      if(WEdkroZkXH == true){WEdkroZkXH = false;}
      if(OVIYryWbqL == true){OVIYryWbqL = false;}
      if(QQXozELRyg == true){QQXozELRyg = false;}
      if(GkEbXpSGQo == true){GkEbXpSGQo = false;}
      if(EgDVTOEfmz == true){EgDVTOEfmz = false;}
      if(RBJHeFgnkm == true){RBJHeFgnkm = false;}
      if(dImqBcRfAB == true){dImqBcRfAB = false;}
      if(eQLBGiMBUk == true){eQLBGiMBUk = false;}
      if(zedyOEbwxR == true){zedyOEbwxR = false;}
      if(JdUcLwtMUq == true){JdUcLwtMUq = false;}
      if(wYekUBpHBu == true){wYekUBpHBu = false;}
      if(seTAmydnbw == true){seTAmydnbw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SPHVSBKOYM
{ 
  void sYCYLENdFV()
  { 
      bool qtEScZuufS = false;
      bool EBIlmIFCBy = false;
      bool ulsnhjIAAc = false;
      bool BxQtpNcubL = false;
      bool UWYRGBTYpA = false;
      bool IMxtCEBPkr = false;
      bool RttCQHjOuZ = false;
      bool fJZpcYMahf = false;
      bool QiKzUnzVqk = false;
      bool LMJjtacWAy = false;
      bool QFdPUylHQd = false;
      bool rZhEbhithc = false;
      bool IOWKNTzpuB = false;
      bool upZiOKFueV = false;
      bool BqENsldFHM = false;
      bool rinXpChTBB = false;
      bool zwMOhCAzoQ = false;
      bool bnOMaQJJQb = false;
      bool othhJMBBrM = false;
      bool blsdWFdpep = false;
      string QwLleVaYiJ;
      string TBLdFFTEkk;
      string upHYdstMXy;
      string TGHhZpFVlI;
      string JcBjjfEKyY;
      string XCfyVaolIl;
      string aNBkoNtcEP;
      string zxRcbRnWox;
      string njNyZRZJLz;
      string ATNAgubQtV;
      string laGiZZjDVE;
      string lSwKxqACKX;
      string mkQFOejRug;
      string oXbSLMdeYz;
      string gWnHMhXCDp;
      string uYFWiBKBTu;
      string pSHnONqcyj;
      string NUdKqQwJrg;
      string HgNFlQREjK;
      string CcLcJNOzry;
      if(QwLleVaYiJ == laGiZZjDVE){qtEScZuufS = true;}
      else if(laGiZZjDVE == QwLleVaYiJ){QFdPUylHQd = true;}
      if(TBLdFFTEkk == lSwKxqACKX){EBIlmIFCBy = true;}
      else if(lSwKxqACKX == TBLdFFTEkk){rZhEbhithc = true;}
      if(upHYdstMXy == mkQFOejRug){ulsnhjIAAc = true;}
      else if(mkQFOejRug == upHYdstMXy){IOWKNTzpuB = true;}
      if(TGHhZpFVlI == oXbSLMdeYz){BxQtpNcubL = true;}
      else if(oXbSLMdeYz == TGHhZpFVlI){upZiOKFueV = true;}
      if(JcBjjfEKyY == gWnHMhXCDp){UWYRGBTYpA = true;}
      else if(gWnHMhXCDp == JcBjjfEKyY){BqENsldFHM = true;}
      if(XCfyVaolIl == uYFWiBKBTu){IMxtCEBPkr = true;}
      else if(uYFWiBKBTu == XCfyVaolIl){rinXpChTBB = true;}
      if(aNBkoNtcEP == pSHnONqcyj){RttCQHjOuZ = true;}
      else if(pSHnONqcyj == aNBkoNtcEP){zwMOhCAzoQ = true;}
      if(zxRcbRnWox == NUdKqQwJrg){fJZpcYMahf = true;}
      if(njNyZRZJLz == HgNFlQREjK){QiKzUnzVqk = true;}
      if(ATNAgubQtV == CcLcJNOzry){LMJjtacWAy = true;}
      while(NUdKqQwJrg == zxRcbRnWox){bnOMaQJJQb = true;}
      while(HgNFlQREjK == HgNFlQREjK){othhJMBBrM = true;}
      while(CcLcJNOzry == CcLcJNOzry){blsdWFdpep = true;}
      if(qtEScZuufS == true){qtEScZuufS = false;}
      if(EBIlmIFCBy == true){EBIlmIFCBy = false;}
      if(ulsnhjIAAc == true){ulsnhjIAAc = false;}
      if(BxQtpNcubL == true){BxQtpNcubL = false;}
      if(UWYRGBTYpA == true){UWYRGBTYpA = false;}
      if(IMxtCEBPkr == true){IMxtCEBPkr = false;}
      if(RttCQHjOuZ == true){RttCQHjOuZ = false;}
      if(fJZpcYMahf == true){fJZpcYMahf = false;}
      if(QiKzUnzVqk == true){QiKzUnzVqk = false;}
      if(LMJjtacWAy == true){LMJjtacWAy = false;}
      if(QFdPUylHQd == true){QFdPUylHQd = false;}
      if(rZhEbhithc == true){rZhEbhithc = false;}
      if(IOWKNTzpuB == true){IOWKNTzpuB = false;}
      if(upZiOKFueV == true){upZiOKFueV = false;}
      if(BqENsldFHM == true){BqENsldFHM = false;}
      if(rinXpChTBB == true){rinXpChTBB = false;}
      if(zwMOhCAzoQ == true){zwMOhCAzoQ = false;}
      if(bnOMaQJJQb == true){bnOMaQJJQb = false;}
      if(othhJMBBrM == true){othhJMBBrM = false;}
      if(blsdWFdpep == true){blsdWFdpep = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQPIEGADOZ
{ 
  void YwFHKhxiya()
  { 
      bool HTqJuoZyGI = false;
      bool akbjlmYaOe = false;
      bool rPpqqVNwDb = false;
      bool baarsramGA = false;
      bool niHsEwpLfe = false;
      bool HEYEHrdASY = false;
      bool adtdgzJiqt = false;
      bool LlUNqIIwlt = false;
      bool eCPYUWBWkB = false;
      bool OaUgYKncME = false;
      bool mHUlSVjLNy = false;
      bool jhNXtYNVJK = false;
      bool ylypekRmnf = false;
      bool UejhGXhdFz = false;
      bool lpJlQfNwmA = false;
      bool xRSBGBIeGh = false;
      bool DxWgdExfQV = false;
      bool qiPKXHbLYy = false;
      bool WUzniCMhaF = false;
      bool ODXXuoScIM = false;
      string gVfRWjCfrm;
      string YuELqcEOQN;
      string OnEVFIfHJk;
      string VjErsLgRzR;
      string jqWwVmuEDT;
      string ZQNUTsRKLO;
      string EuVGRnpMRf;
      string umPzcWRIzS;
      string MaEpLEWiYA;
      string tWGjNoUPdg;
      string xilWXmBOqw;
      string aIKrCcpfuM;
      string QGmRlYfekn;
      string CBeSVcngRY;
      string DIqcYkLNhj;
      string ynUQQpuUkz;
      string GVcDsYdrWY;
      string oJOVJHOKrA;
      string MSwBoNgNCf;
      string gSwSSgfniz;
      if(gVfRWjCfrm == xilWXmBOqw){HTqJuoZyGI = true;}
      else if(xilWXmBOqw == gVfRWjCfrm){mHUlSVjLNy = true;}
      if(YuELqcEOQN == aIKrCcpfuM){akbjlmYaOe = true;}
      else if(aIKrCcpfuM == YuELqcEOQN){jhNXtYNVJK = true;}
      if(OnEVFIfHJk == QGmRlYfekn){rPpqqVNwDb = true;}
      else if(QGmRlYfekn == OnEVFIfHJk){ylypekRmnf = true;}
      if(VjErsLgRzR == CBeSVcngRY){baarsramGA = true;}
      else if(CBeSVcngRY == VjErsLgRzR){UejhGXhdFz = true;}
      if(jqWwVmuEDT == DIqcYkLNhj){niHsEwpLfe = true;}
      else if(DIqcYkLNhj == jqWwVmuEDT){lpJlQfNwmA = true;}
      if(ZQNUTsRKLO == ynUQQpuUkz){HEYEHrdASY = true;}
      else if(ynUQQpuUkz == ZQNUTsRKLO){xRSBGBIeGh = true;}
      if(EuVGRnpMRf == GVcDsYdrWY){adtdgzJiqt = true;}
      else if(GVcDsYdrWY == EuVGRnpMRf){DxWgdExfQV = true;}
      if(umPzcWRIzS == oJOVJHOKrA){LlUNqIIwlt = true;}
      if(MaEpLEWiYA == MSwBoNgNCf){eCPYUWBWkB = true;}
      if(tWGjNoUPdg == gSwSSgfniz){OaUgYKncME = true;}
      while(oJOVJHOKrA == umPzcWRIzS){qiPKXHbLYy = true;}
      while(MSwBoNgNCf == MSwBoNgNCf){WUzniCMhaF = true;}
      while(gSwSSgfniz == gSwSSgfniz){ODXXuoScIM = true;}
      if(HTqJuoZyGI == true){HTqJuoZyGI = false;}
      if(akbjlmYaOe == true){akbjlmYaOe = false;}
      if(rPpqqVNwDb == true){rPpqqVNwDb = false;}
      if(baarsramGA == true){baarsramGA = false;}
      if(niHsEwpLfe == true){niHsEwpLfe = false;}
      if(HEYEHrdASY == true){HEYEHrdASY = false;}
      if(adtdgzJiqt == true){adtdgzJiqt = false;}
      if(LlUNqIIwlt == true){LlUNqIIwlt = false;}
      if(eCPYUWBWkB == true){eCPYUWBWkB = false;}
      if(OaUgYKncME == true){OaUgYKncME = false;}
      if(mHUlSVjLNy == true){mHUlSVjLNy = false;}
      if(jhNXtYNVJK == true){jhNXtYNVJK = false;}
      if(ylypekRmnf == true){ylypekRmnf = false;}
      if(UejhGXhdFz == true){UejhGXhdFz = false;}
      if(lpJlQfNwmA == true){lpJlQfNwmA = false;}
      if(xRSBGBIeGh == true){xRSBGBIeGh = false;}
      if(DxWgdExfQV == true){DxWgdExfQV = false;}
      if(qiPKXHbLYy == true){qiPKXHbLYy = false;}
      if(WUzniCMhaF == true){WUzniCMhaF = false;}
      if(ODXXuoScIM == true){ODXXuoScIM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ANVBJPQEYN
{ 
  void qpUKcAcVly()
  { 
      bool XofIjrYWLA = false;
      bool qMtHABIklW = false;
      bool kmxLAslzXF = false;
      bool FoHMnGtCxd = false;
      bool TOSdykJfbc = false;
      bool cZYNUjrTHp = false;
      bool FZzGtBFgTt = false;
      bool GGmHCVTTMO = false;
      bool jGWubeQsrD = false;
      bool NZtHXtPMix = false;
      bool fbMgWWmQLz = false;
      bool QXHsGzCEeP = false;
      bool kLoPffLejI = false;
      bool FHjPiHsoYF = false;
      bool rAhrmoSBBY = false;
      bool qLgTMUlxBp = false;
      bool KHgCsInqJy = false;
      bool FMfYXjcwbp = false;
      bool NKdKQtZPDO = false;
      bool UwnhtjSfze = false;
      string BzyODmIgpt;
      string QtRzOTLqGJ;
      string hXSVoAutwt;
      string HKIPpWQoNq;
      string QldlQwzSOM;
      string FPxqFcfbZD;
      string rOjwmGlCJr;
      string CWcOrwsfFr;
      string AbeinqMRJM;
      string pnOKyCBhyK;
      string KxJWKiliyJ;
      string iAWhCQiBHw;
      string tTrwCNHSPp;
      string tLhtgDRIYF;
      string FdTAcpRgHh;
      string SAZCQqENTw;
      string aTSIPWRbBz;
      string yabCpQArSM;
      string uZKhWsledo;
      string yEncdkKKjF;
      if(BzyODmIgpt == KxJWKiliyJ){XofIjrYWLA = true;}
      else if(KxJWKiliyJ == BzyODmIgpt){fbMgWWmQLz = true;}
      if(QtRzOTLqGJ == iAWhCQiBHw){qMtHABIklW = true;}
      else if(iAWhCQiBHw == QtRzOTLqGJ){QXHsGzCEeP = true;}
      if(hXSVoAutwt == tTrwCNHSPp){kmxLAslzXF = true;}
      else if(tTrwCNHSPp == hXSVoAutwt){kLoPffLejI = true;}
      if(HKIPpWQoNq == tLhtgDRIYF){FoHMnGtCxd = true;}
      else if(tLhtgDRIYF == HKIPpWQoNq){FHjPiHsoYF = true;}
      if(QldlQwzSOM == FdTAcpRgHh){TOSdykJfbc = true;}
      else if(FdTAcpRgHh == QldlQwzSOM){rAhrmoSBBY = true;}
      if(FPxqFcfbZD == SAZCQqENTw){cZYNUjrTHp = true;}
      else if(SAZCQqENTw == FPxqFcfbZD){qLgTMUlxBp = true;}
      if(rOjwmGlCJr == aTSIPWRbBz){FZzGtBFgTt = true;}
      else if(aTSIPWRbBz == rOjwmGlCJr){KHgCsInqJy = true;}
      if(CWcOrwsfFr == yabCpQArSM){GGmHCVTTMO = true;}
      if(AbeinqMRJM == uZKhWsledo){jGWubeQsrD = true;}
      if(pnOKyCBhyK == yEncdkKKjF){NZtHXtPMix = true;}
      while(yabCpQArSM == CWcOrwsfFr){FMfYXjcwbp = true;}
      while(uZKhWsledo == uZKhWsledo){NKdKQtZPDO = true;}
      while(yEncdkKKjF == yEncdkKKjF){UwnhtjSfze = true;}
      if(XofIjrYWLA == true){XofIjrYWLA = false;}
      if(qMtHABIklW == true){qMtHABIklW = false;}
      if(kmxLAslzXF == true){kmxLAslzXF = false;}
      if(FoHMnGtCxd == true){FoHMnGtCxd = false;}
      if(TOSdykJfbc == true){TOSdykJfbc = false;}
      if(cZYNUjrTHp == true){cZYNUjrTHp = false;}
      if(FZzGtBFgTt == true){FZzGtBFgTt = false;}
      if(GGmHCVTTMO == true){GGmHCVTTMO = false;}
      if(jGWubeQsrD == true){jGWubeQsrD = false;}
      if(NZtHXtPMix == true){NZtHXtPMix = false;}
      if(fbMgWWmQLz == true){fbMgWWmQLz = false;}
      if(QXHsGzCEeP == true){QXHsGzCEeP = false;}
      if(kLoPffLejI == true){kLoPffLejI = false;}
      if(FHjPiHsoYF == true){FHjPiHsoYF = false;}
      if(rAhrmoSBBY == true){rAhrmoSBBY = false;}
      if(qLgTMUlxBp == true){qLgTMUlxBp = false;}
      if(KHgCsInqJy == true){KHgCsInqJy = false;}
      if(FMfYXjcwbp == true){FMfYXjcwbp = false;}
      if(NKdKQtZPDO == true){NKdKQtZPDO = false;}
      if(UwnhtjSfze == true){UwnhtjSfze = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OTNFLBVAQB
{ 
  void EWjkMeMAEX()
  { 
      bool ZEohBQgFOT = false;
      bool OxykaGTGZW = false;
      bool iEWhyapWwI = false;
      bool ZyGDnWIqkk = false;
      bool RkPPRysBBn = false;
      bool ZkalkVgGjZ = false;
      bool aJIFtPpuwE = false;
      bool xbVoFxoHQz = false;
      bool hoUHhnXURS = false;
      bool oCHKKHbJUB = false;
      bool IyExpxPlgm = false;
      bool fYokrknBWG = false;
      bool rVccOuUKex = false;
      bool VelPpijXRk = false;
      bool YlndlQNVSY = false;
      bool SalOJlUaiu = false;
      bool cEGiRBlYtI = false;
      bool BQilgGhypy = false;
      bool hyrGdtrXFD = false;
      bool NJoWHUeEMk = false;
      string AJUBWRadSo;
      string aGyeeCTjyq;
      string xKehGBcygW;
      string PocWARaGBp;
      string lHieYUiVlO;
      string SfGbqpdltV;
      string nbwuZkcadM;
      string aNiHEpaAJl;
      string RGMSEjiAfK;
      string nnLfBJKmFm;
      string qIqYnFwyWA;
      string OdcIDhPdpo;
      string BcuTYlBCFu;
      string entVtJOmdz;
      string mjceuJLDbT;
      string sgwPkONWAB;
      string EtrbVaiHOt;
      string SczqBRzPYO;
      string axZlByqdjf;
      string wqlcusrBJU;
      if(AJUBWRadSo == qIqYnFwyWA){ZEohBQgFOT = true;}
      else if(qIqYnFwyWA == AJUBWRadSo){IyExpxPlgm = true;}
      if(aGyeeCTjyq == OdcIDhPdpo){OxykaGTGZW = true;}
      else if(OdcIDhPdpo == aGyeeCTjyq){fYokrknBWG = true;}
      if(xKehGBcygW == BcuTYlBCFu){iEWhyapWwI = true;}
      else if(BcuTYlBCFu == xKehGBcygW){rVccOuUKex = true;}
      if(PocWARaGBp == entVtJOmdz){ZyGDnWIqkk = true;}
      else if(entVtJOmdz == PocWARaGBp){VelPpijXRk = true;}
      if(lHieYUiVlO == mjceuJLDbT){RkPPRysBBn = true;}
      else if(mjceuJLDbT == lHieYUiVlO){YlndlQNVSY = true;}
      if(SfGbqpdltV == sgwPkONWAB){ZkalkVgGjZ = true;}
      else if(sgwPkONWAB == SfGbqpdltV){SalOJlUaiu = true;}
      if(nbwuZkcadM == EtrbVaiHOt){aJIFtPpuwE = true;}
      else if(EtrbVaiHOt == nbwuZkcadM){cEGiRBlYtI = true;}
      if(aNiHEpaAJl == SczqBRzPYO){xbVoFxoHQz = true;}
      if(RGMSEjiAfK == axZlByqdjf){hoUHhnXURS = true;}
      if(nnLfBJKmFm == wqlcusrBJU){oCHKKHbJUB = true;}
      while(SczqBRzPYO == aNiHEpaAJl){BQilgGhypy = true;}
      while(axZlByqdjf == axZlByqdjf){hyrGdtrXFD = true;}
      while(wqlcusrBJU == wqlcusrBJU){NJoWHUeEMk = true;}
      if(ZEohBQgFOT == true){ZEohBQgFOT = false;}
      if(OxykaGTGZW == true){OxykaGTGZW = false;}
      if(iEWhyapWwI == true){iEWhyapWwI = false;}
      if(ZyGDnWIqkk == true){ZyGDnWIqkk = false;}
      if(RkPPRysBBn == true){RkPPRysBBn = false;}
      if(ZkalkVgGjZ == true){ZkalkVgGjZ = false;}
      if(aJIFtPpuwE == true){aJIFtPpuwE = false;}
      if(xbVoFxoHQz == true){xbVoFxoHQz = false;}
      if(hoUHhnXURS == true){hoUHhnXURS = false;}
      if(oCHKKHbJUB == true){oCHKKHbJUB = false;}
      if(IyExpxPlgm == true){IyExpxPlgm = false;}
      if(fYokrknBWG == true){fYokrknBWG = false;}
      if(rVccOuUKex == true){rVccOuUKex = false;}
      if(VelPpijXRk == true){VelPpijXRk = false;}
      if(YlndlQNVSY == true){YlndlQNVSY = false;}
      if(SalOJlUaiu == true){SalOJlUaiu = false;}
      if(cEGiRBlYtI == true){cEGiRBlYtI = false;}
      if(BQilgGhypy == true){BQilgGhypy = false;}
      if(hyrGdtrXFD == true){hyrGdtrXFD = false;}
      if(NJoWHUeEMk == true){NJoWHUeEMk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EHPJKFTMME
{ 
  void tRdmdobWYF()
  { 
      bool HyAEGWCAwo = false;
      bool csfWLnxkEN = false;
      bool zFRLJpCPBP = false;
      bool uMkKAGVXEL = false;
      bool oJwZWyioRk = false;
      bool MIlbgCfotP = false;
      bool TmzftQIUVE = false;
      bool RYfsYpJrnL = false;
      bool HMyPClaIdy = false;
      bool ZgcoqCJPeG = false;
      bool oNTMSmcrDq = false;
      bool snAiHHoicH = false;
      bool pzqXekwqCV = false;
      bool fsMhVtskwO = false;
      bool JhEmEkgsgj = false;
      bool NalXPoVwgh = false;
      bool qlogKzbRNN = false;
      bool NDlOyHuESt = false;
      bool DCJSIFGoRf = false;
      bool XwEOXWrXbF = false;
      string UagYHMAKwp;
      string tXxcAaibXu;
      string XAWBhtXJhH;
      string rFDrHVkwdt;
      string jHacyjtcXo;
      string eDwSGUEeqM;
      string nqcnxnTFVe;
      string plycLQYsDy;
      string AukrcoIkkm;
      string QGEQFremeJ;
      string PoHszrFSGp;
      string uLasMsGjLI;
      string ehUiNjhgWT;
      string klNthLmqrj;
      string ipdtqFeLEM;
      string ktbVegTXeP;
      string KYumEJxgLA;
      string FOraZoEZrI;
      string EVbKhqJrOA;
      string qOMcZJtqog;
      if(UagYHMAKwp == PoHszrFSGp){HyAEGWCAwo = true;}
      else if(PoHszrFSGp == UagYHMAKwp){oNTMSmcrDq = true;}
      if(tXxcAaibXu == uLasMsGjLI){csfWLnxkEN = true;}
      else if(uLasMsGjLI == tXxcAaibXu){snAiHHoicH = true;}
      if(XAWBhtXJhH == ehUiNjhgWT){zFRLJpCPBP = true;}
      else if(ehUiNjhgWT == XAWBhtXJhH){pzqXekwqCV = true;}
      if(rFDrHVkwdt == klNthLmqrj){uMkKAGVXEL = true;}
      else if(klNthLmqrj == rFDrHVkwdt){fsMhVtskwO = true;}
      if(jHacyjtcXo == ipdtqFeLEM){oJwZWyioRk = true;}
      else if(ipdtqFeLEM == jHacyjtcXo){JhEmEkgsgj = true;}
      if(eDwSGUEeqM == ktbVegTXeP){MIlbgCfotP = true;}
      else if(ktbVegTXeP == eDwSGUEeqM){NalXPoVwgh = true;}
      if(nqcnxnTFVe == KYumEJxgLA){TmzftQIUVE = true;}
      else if(KYumEJxgLA == nqcnxnTFVe){qlogKzbRNN = true;}
      if(plycLQYsDy == FOraZoEZrI){RYfsYpJrnL = true;}
      if(AukrcoIkkm == EVbKhqJrOA){HMyPClaIdy = true;}
      if(QGEQFremeJ == qOMcZJtqog){ZgcoqCJPeG = true;}
      while(FOraZoEZrI == plycLQYsDy){NDlOyHuESt = true;}
      while(EVbKhqJrOA == EVbKhqJrOA){DCJSIFGoRf = true;}
      while(qOMcZJtqog == qOMcZJtqog){XwEOXWrXbF = true;}
      if(HyAEGWCAwo == true){HyAEGWCAwo = false;}
      if(csfWLnxkEN == true){csfWLnxkEN = false;}
      if(zFRLJpCPBP == true){zFRLJpCPBP = false;}
      if(uMkKAGVXEL == true){uMkKAGVXEL = false;}
      if(oJwZWyioRk == true){oJwZWyioRk = false;}
      if(MIlbgCfotP == true){MIlbgCfotP = false;}
      if(TmzftQIUVE == true){TmzftQIUVE = false;}
      if(RYfsYpJrnL == true){RYfsYpJrnL = false;}
      if(HMyPClaIdy == true){HMyPClaIdy = false;}
      if(ZgcoqCJPeG == true){ZgcoqCJPeG = false;}
      if(oNTMSmcrDq == true){oNTMSmcrDq = false;}
      if(snAiHHoicH == true){snAiHHoicH = false;}
      if(pzqXekwqCV == true){pzqXekwqCV = false;}
      if(fsMhVtskwO == true){fsMhVtskwO = false;}
      if(JhEmEkgsgj == true){JhEmEkgsgj = false;}
      if(NalXPoVwgh == true){NalXPoVwgh = false;}
      if(qlogKzbRNN == true){qlogKzbRNN = false;}
      if(NDlOyHuESt == true){NDlOyHuESt = false;}
      if(DCJSIFGoRf == true){DCJSIFGoRf = false;}
      if(XwEOXWrXbF == true){XwEOXWrXbF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TPKNVHCADH
{ 
  void crKXSUjXbx()
  { 
      bool DgFlPzgYAn = false;
      bool UWdFlICrHO = false;
      bool BxqBGREkti = false;
      bool CpIAiXtraR = false;
      bool YdqtwqisKi = false;
      bool aOPiiFoDey = false;
      bool uwdQkdOcWO = false;
      bool NJQpoXGxFP = false;
      bool iKZLInaYRc = false;
      bool hpMcVcAZIS = false;
      bool cGVuUQxYtK = false;
      bool zryPOjVRIw = false;
      bool DoKtgWwmTM = false;
      bool Xfnmmboepq = false;
      bool qCeHcpqxNl = false;
      bool GhRMOmubOy = false;
      bool TJFgmSDLbm = false;
      bool uqbQFAKDQq = false;
      bool eyZgFoObXz = false;
      bool fMPrXgwxTK = false;
      string DzKtfQTmGp;
      string eqjQoNaZSY;
      string LbRegapIVl;
      string tVuEiVpGWc;
      string IDRdEnhXrb;
      string CTKHwbheME;
      string ZLQUuJwfhT;
      string XTCoQHKmar;
      string sSQsiZKmHH;
      string nLtSCxlwhu;
      string rBpYEiQVqo;
      string RtETLHuXlV;
      string yJYafMZjlS;
      string UNEeAqbqoz;
      string JouRosGZGu;
      string COKMxicPrr;
      string IfiXTEoZTU;
      string eDhlMJNGkl;
      string FAdqQFCqhR;
      string NMzxqcGWxj;
      if(DzKtfQTmGp == rBpYEiQVqo){DgFlPzgYAn = true;}
      else if(rBpYEiQVqo == DzKtfQTmGp){cGVuUQxYtK = true;}
      if(eqjQoNaZSY == RtETLHuXlV){UWdFlICrHO = true;}
      else if(RtETLHuXlV == eqjQoNaZSY){zryPOjVRIw = true;}
      if(LbRegapIVl == yJYafMZjlS){BxqBGREkti = true;}
      else if(yJYafMZjlS == LbRegapIVl){DoKtgWwmTM = true;}
      if(tVuEiVpGWc == UNEeAqbqoz){CpIAiXtraR = true;}
      else if(UNEeAqbqoz == tVuEiVpGWc){Xfnmmboepq = true;}
      if(IDRdEnhXrb == JouRosGZGu){YdqtwqisKi = true;}
      else if(JouRosGZGu == IDRdEnhXrb){qCeHcpqxNl = true;}
      if(CTKHwbheME == COKMxicPrr){aOPiiFoDey = true;}
      else if(COKMxicPrr == CTKHwbheME){GhRMOmubOy = true;}
      if(ZLQUuJwfhT == IfiXTEoZTU){uwdQkdOcWO = true;}
      else if(IfiXTEoZTU == ZLQUuJwfhT){TJFgmSDLbm = true;}
      if(XTCoQHKmar == eDhlMJNGkl){NJQpoXGxFP = true;}
      if(sSQsiZKmHH == FAdqQFCqhR){iKZLInaYRc = true;}
      if(nLtSCxlwhu == NMzxqcGWxj){hpMcVcAZIS = true;}
      while(eDhlMJNGkl == XTCoQHKmar){uqbQFAKDQq = true;}
      while(FAdqQFCqhR == FAdqQFCqhR){eyZgFoObXz = true;}
      while(NMzxqcGWxj == NMzxqcGWxj){fMPrXgwxTK = true;}
      if(DgFlPzgYAn == true){DgFlPzgYAn = false;}
      if(UWdFlICrHO == true){UWdFlICrHO = false;}
      if(BxqBGREkti == true){BxqBGREkti = false;}
      if(CpIAiXtraR == true){CpIAiXtraR = false;}
      if(YdqtwqisKi == true){YdqtwqisKi = false;}
      if(aOPiiFoDey == true){aOPiiFoDey = false;}
      if(uwdQkdOcWO == true){uwdQkdOcWO = false;}
      if(NJQpoXGxFP == true){NJQpoXGxFP = false;}
      if(iKZLInaYRc == true){iKZLInaYRc = false;}
      if(hpMcVcAZIS == true){hpMcVcAZIS = false;}
      if(cGVuUQxYtK == true){cGVuUQxYtK = false;}
      if(zryPOjVRIw == true){zryPOjVRIw = false;}
      if(DoKtgWwmTM == true){DoKtgWwmTM = false;}
      if(Xfnmmboepq == true){Xfnmmboepq = false;}
      if(qCeHcpqxNl == true){qCeHcpqxNl = false;}
      if(GhRMOmubOy == true){GhRMOmubOy = false;}
      if(TJFgmSDLbm == true){TJFgmSDLbm = false;}
      if(uqbQFAKDQq == true){uqbQFAKDQq = false;}
      if(eyZgFoObXz == true){eyZgFoObXz = false;}
      if(fMPrXgwxTK == true){fMPrXgwxTK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RHIIWVGSGM
{ 
  void TmdmFlKVhN()
  { 
      bool YHgjnXxWjO = false;
      bool lXrksEFiMC = false;
      bool bANsxPmSVj = false;
      bool dyukYhgYTM = false;
      bool bHyKSqijpH = false;
      bool zLSNnXsmlX = false;
      bool jdAzjmbGMK = false;
      bool XfPzZTBCaG = false;
      bool gDbNkSehxA = false;
      bool oslucyGyZe = false;
      bool ObXfiTuTnT = false;
      bool VqMfqgBlOR = false;
      bool ItJLVesUWa = false;
      bool NDbuqEewdR = false;
      bool WLsddxfGEu = false;
      bool wUiIVUSLKE = false;
      bool ZawMGSOQnm = false;
      bool BFHxuxAehX = false;
      bool ymQaerTTYW = false;
      bool lSkZruOgXK = false;
      string SBOiNnlusJ;
      string NUlinxzKgF;
      string YaSwVTkimo;
      string PhSpBiPKAx;
      string ucXbgaiyrB;
      string zcPYxqiRNt;
      string CCHEteBwgF;
      string hoKjJuCpPt;
      string jmplplSssK;
      string AxxFurVThB;
      string YlQmTKSfPB;
      string orCSJOLVOI;
      string MIDWFkrEnR;
      string ZiIOUyVDSe;
      string SmdqVHuduf;
      string fAFZnQithi;
      string SNqxbFimxL;
      string rICioZeLBx;
      string oNIHkZdiZE;
      string ObUjMEufPP;
      if(SBOiNnlusJ == YlQmTKSfPB){YHgjnXxWjO = true;}
      else if(YlQmTKSfPB == SBOiNnlusJ){ObXfiTuTnT = true;}
      if(NUlinxzKgF == orCSJOLVOI){lXrksEFiMC = true;}
      else if(orCSJOLVOI == NUlinxzKgF){VqMfqgBlOR = true;}
      if(YaSwVTkimo == MIDWFkrEnR){bANsxPmSVj = true;}
      else if(MIDWFkrEnR == YaSwVTkimo){ItJLVesUWa = true;}
      if(PhSpBiPKAx == ZiIOUyVDSe){dyukYhgYTM = true;}
      else if(ZiIOUyVDSe == PhSpBiPKAx){NDbuqEewdR = true;}
      if(ucXbgaiyrB == SmdqVHuduf){bHyKSqijpH = true;}
      else if(SmdqVHuduf == ucXbgaiyrB){WLsddxfGEu = true;}
      if(zcPYxqiRNt == fAFZnQithi){zLSNnXsmlX = true;}
      else if(fAFZnQithi == zcPYxqiRNt){wUiIVUSLKE = true;}
      if(CCHEteBwgF == SNqxbFimxL){jdAzjmbGMK = true;}
      else if(SNqxbFimxL == CCHEteBwgF){ZawMGSOQnm = true;}
      if(hoKjJuCpPt == rICioZeLBx){XfPzZTBCaG = true;}
      if(jmplplSssK == oNIHkZdiZE){gDbNkSehxA = true;}
      if(AxxFurVThB == ObUjMEufPP){oslucyGyZe = true;}
      while(rICioZeLBx == hoKjJuCpPt){BFHxuxAehX = true;}
      while(oNIHkZdiZE == oNIHkZdiZE){ymQaerTTYW = true;}
      while(ObUjMEufPP == ObUjMEufPP){lSkZruOgXK = true;}
      if(YHgjnXxWjO == true){YHgjnXxWjO = false;}
      if(lXrksEFiMC == true){lXrksEFiMC = false;}
      if(bANsxPmSVj == true){bANsxPmSVj = false;}
      if(dyukYhgYTM == true){dyukYhgYTM = false;}
      if(bHyKSqijpH == true){bHyKSqijpH = false;}
      if(zLSNnXsmlX == true){zLSNnXsmlX = false;}
      if(jdAzjmbGMK == true){jdAzjmbGMK = false;}
      if(XfPzZTBCaG == true){XfPzZTBCaG = false;}
      if(gDbNkSehxA == true){gDbNkSehxA = false;}
      if(oslucyGyZe == true){oslucyGyZe = false;}
      if(ObXfiTuTnT == true){ObXfiTuTnT = false;}
      if(VqMfqgBlOR == true){VqMfqgBlOR = false;}
      if(ItJLVesUWa == true){ItJLVesUWa = false;}
      if(NDbuqEewdR == true){NDbuqEewdR = false;}
      if(WLsddxfGEu == true){WLsddxfGEu = false;}
      if(wUiIVUSLKE == true){wUiIVUSLKE = false;}
      if(ZawMGSOQnm == true){ZawMGSOQnm = false;}
      if(BFHxuxAehX == true){BFHxuxAehX = false;}
      if(ymQaerTTYW == true){ymQaerTTYW = false;}
      if(lSkZruOgXK == true){lSkZruOgXK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DOHSBGVULK
{ 
  void WcWmdKZNji()
  { 
      bool JrlBFFrmIG = false;
      bool AGtrngbPzg = false;
      bool PEUnlwNRyU = false;
      bool fldAMPKigW = false;
      bool PWwtqpNoaH = false;
      bool yfeyLFWyOI = false;
      bool rZonZObtfX = false;
      bool WricQrHawu = false;
      bool hXqpWAHfnH = false;
      bool rMTXdohHTc = false;
      bool OTJCkFxBgT = false;
      bool xwBSZThyRZ = false;
      bool GuFYeJXKyb = false;
      bool KzHSgONoFQ = false;
      bool CFzUJwKBxK = false;
      bool GjpsWSOkWb = false;
      bool gmCFJxoilL = false;
      bool GssBWAwkOi = false;
      bool yWMnUZJNwN = false;
      bool zbSciPDtLM = false;
      string KqfNViYHDI;
      string QafmZNVlBJ;
      string ibeeYTUgmg;
      string GqpLwxVxiI;
      string lkFljZNqfJ;
      string SkrcUhLBoC;
      string NrUVCZjUqb;
      string qYDrWyVsty;
      string FdAcNUyMqN;
      string lUIgtsQjjK;
      string oszESthAGW;
      string MSGpwjrqHg;
      string aXdcpWPVxd;
      string glIjJMewKT;
      string lyGTBTOSkK;
      string BYbDiRPVOw;
      string dMCboZJVfi;
      string FugntbQJbV;
      string IxklbIKFAr;
      string xIhOoZwdeb;
      if(KqfNViYHDI == oszESthAGW){JrlBFFrmIG = true;}
      else if(oszESthAGW == KqfNViYHDI){OTJCkFxBgT = true;}
      if(QafmZNVlBJ == MSGpwjrqHg){AGtrngbPzg = true;}
      else if(MSGpwjrqHg == QafmZNVlBJ){xwBSZThyRZ = true;}
      if(ibeeYTUgmg == aXdcpWPVxd){PEUnlwNRyU = true;}
      else if(aXdcpWPVxd == ibeeYTUgmg){GuFYeJXKyb = true;}
      if(GqpLwxVxiI == glIjJMewKT){fldAMPKigW = true;}
      else if(glIjJMewKT == GqpLwxVxiI){KzHSgONoFQ = true;}
      if(lkFljZNqfJ == lyGTBTOSkK){PWwtqpNoaH = true;}
      else if(lyGTBTOSkK == lkFljZNqfJ){CFzUJwKBxK = true;}
      if(SkrcUhLBoC == BYbDiRPVOw){yfeyLFWyOI = true;}
      else if(BYbDiRPVOw == SkrcUhLBoC){GjpsWSOkWb = true;}
      if(NrUVCZjUqb == dMCboZJVfi){rZonZObtfX = true;}
      else if(dMCboZJVfi == NrUVCZjUqb){gmCFJxoilL = true;}
      if(qYDrWyVsty == FugntbQJbV){WricQrHawu = true;}
      if(FdAcNUyMqN == IxklbIKFAr){hXqpWAHfnH = true;}
      if(lUIgtsQjjK == xIhOoZwdeb){rMTXdohHTc = true;}
      while(FugntbQJbV == qYDrWyVsty){GssBWAwkOi = true;}
      while(IxklbIKFAr == IxklbIKFAr){yWMnUZJNwN = true;}
      while(xIhOoZwdeb == xIhOoZwdeb){zbSciPDtLM = true;}
      if(JrlBFFrmIG == true){JrlBFFrmIG = false;}
      if(AGtrngbPzg == true){AGtrngbPzg = false;}
      if(PEUnlwNRyU == true){PEUnlwNRyU = false;}
      if(fldAMPKigW == true){fldAMPKigW = false;}
      if(PWwtqpNoaH == true){PWwtqpNoaH = false;}
      if(yfeyLFWyOI == true){yfeyLFWyOI = false;}
      if(rZonZObtfX == true){rZonZObtfX = false;}
      if(WricQrHawu == true){WricQrHawu = false;}
      if(hXqpWAHfnH == true){hXqpWAHfnH = false;}
      if(rMTXdohHTc == true){rMTXdohHTc = false;}
      if(OTJCkFxBgT == true){OTJCkFxBgT = false;}
      if(xwBSZThyRZ == true){xwBSZThyRZ = false;}
      if(GuFYeJXKyb == true){GuFYeJXKyb = false;}
      if(KzHSgONoFQ == true){KzHSgONoFQ = false;}
      if(CFzUJwKBxK == true){CFzUJwKBxK = false;}
      if(GjpsWSOkWb == true){GjpsWSOkWb = false;}
      if(gmCFJxoilL == true){gmCFJxoilL = false;}
      if(GssBWAwkOi == true){GssBWAwkOi = false;}
      if(yWMnUZJNwN == true){yWMnUZJNwN = false;}
      if(zbSciPDtLM == true){zbSciPDtLM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJBXWRAMIW
{ 
  void JbzwdiMMpG()
  { 
      bool DoZgjZypsF = false;
      bool NmicPWJhIV = false;
      bool eOqPHkwCyS = false;
      bool BjumdFjQcg = false;
      bool iDhUonwlgC = false;
      bool tAxTsnyKZz = false;
      bool cwqaEdruzK = false;
      bool mrEbmagWZT = false;
      bool nKUuXBlato = false;
      bool HZqdElMGQL = false;
      bool uBlWPBuVfS = false;
      bool HbkGLRauCC = false;
      bool qQAKCNBaXA = false;
      bool NZFOXmYyfW = false;
      bool FQubheokRl = false;
      bool LQDNTeAbTC = false;
      bool zUxfEgVVhX = false;
      bool scPfxaVYbX = false;
      bool YQIkoxVrts = false;
      bool mwddWjSPXA = false;
      string BRdjuksLWX;
      string IzDwypnqUj;
      string WSwZjKPxfy;
      string LGFxLwuRgM;
      string TkRJFLJmmJ;
      string GeRZUhUDzj;
      string UweXMBsGjC;
      string uVKHQlBmUY;
      string BcKWrfnfbc;
      string aqSxrXGswD;
      string RCCkOkUKJi;
      string ggiZhqkHeg;
      string NNdHaDDNOs;
      string eHqQHzaYIH;
      string KdWswsIrPB;
      string lyNPpEXtKK;
      string gHuPDYpSSh;
      string QLzXVjpkLg;
      string uKxNGgtbaD;
      string afOxZDhGpX;
      if(BRdjuksLWX == RCCkOkUKJi){DoZgjZypsF = true;}
      else if(RCCkOkUKJi == BRdjuksLWX){uBlWPBuVfS = true;}
      if(IzDwypnqUj == ggiZhqkHeg){NmicPWJhIV = true;}
      else if(ggiZhqkHeg == IzDwypnqUj){HbkGLRauCC = true;}
      if(WSwZjKPxfy == NNdHaDDNOs){eOqPHkwCyS = true;}
      else if(NNdHaDDNOs == WSwZjKPxfy){qQAKCNBaXA = true;}
      if(LGFxLwuRgM == eHqQHzaYIH){BjumdFjQcg = true;}
      else if(eHqQHzaYIH == LGFxLwuRgM){NZFOXmYyfW = true;}
      if(TkRJFLJmmJ == KdWswsIrPB){iDhUonwlgC = true;}
      else if(KdWswsIrPB == TkRJFLJmmJ){FQubheokRl = true;}
      if(GeRZUhUDzj == lyNPpEXtKK){tAxTsnyKZz = true;}
      else if(lyNPpEXtKK == GeRZUhUDzj){LQDNTeAbTC = true;}
      if(UweXMBsGjC == gHuPDYpSSh){cwqaEdruzK = true;}
      else if(gHuPDYpSSh == UweXMBsGjC){zUxfEgVVhX = true;}
      if(uVKHQlBmUY == QLzXVjpkLg){mrEbmagWZT = true;}
      if(BcKWrfnfbc == uKxNGgtbaD){nKUuXBlato = true;}
      if(aqSxrXGswD == afOxZDhGpX){HZqdElMGQL = true;}
      while(QLzXVjpkLg == uVKHQlBmUY){scPfxaVYbX = true;}
      while(uKxNGgtbaD == uKxNGgtbaD){YQIkoxVrts = true;}
      while(afOxZDhGpX == afOxZDhGpX){mwddWjSPXA = true;}
      if(DoZgjZypsF == true){DoZgjZypsF = false;}
      if(NmicPWJhIV == true){NmicPWJhIV = false;}
      if(eOqPHkwCyS == true){eOqPHkwCyS = false;}
      if(BjumdFjQcg == true){BjumdFjQcg = false;}
      if(iDhUonwlgC == true){iDhUonwlgC = false;}
      if(tAxTsnyKZz == true){tAxTsnyKZz = false;}
      if(cwqaEdruzK == true){cwqaEdruzK = false;}
      if(mrEbmagWZT == true){mrEbmagWZT = false;}
      if(nKUuXBlato == true){nKUuXBlato = false;}
      if(HZqdElMGQL == true){HZqdElMGQL = false;}
      if(uBlWPBuVfS == true){uBlWPBuVfS = false;}
      if(HbkGLRauCC == true){HbkGLRauCC = false;}
      if(qQAKCNBaXA == true){qQAKCNBaXA = false;}
      if(NZFOXmYyfW == true){NZFOXmYyfW = false;}
      if(FQubheokRl == true){FQubheokRl = false;}
      if(LQDNTeAbTC == true){LQDNTeAbTC = false;}
      if(zUxfEgVVhX == true){zUxfEgVVhX = false;}
      if(scPfxaVYbX == true){scPfxaVYbX = false;}
      if(YQIkoxVrts == true){YQIkoxVrts = false;}
      if(mwddWjSPXA == true){mwddWjSPXA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXZAZDOKNN
{ 
  void DQVgRqpOVQ()
  { 
      bool pXbinalUSF = false;
      bool gkVTbhwOXP = false;
      bool WbdXyHkRXH = false;
      bool XhznxJBBzU = false;
      bool lqkECtbHKG = false;
      bool LcuODNsEkg = false;
      bool pTwLhzlgWS = false;
      bool guOCcfpYUD = false;
      bool ecGRutmjki = false;
      bool PwQSeRtYWD = false;
      bool ItkqYQOrlW = false;
      bool WTigBMNeQm = false;
      bool LBwmCjeuXK = false;
      bool kRCQukrOrd = false;
      bool euyNLuMjRS = false;
      bool EPHirGyxoo = false;
      bool lTTalFRSkP = false;
      bool UylmIQDhbH = false;
      bool WudFFUJSYn = false;
      bool ltZDrLaWbG = false;
      string nkBQOZHfQQ;
      string JIqFgiBJOD;
      string wYqYzhAMea;
      string pWYaziIcVE;
      string fqkPQIaMNe;
      string zTtdGPtbRg;
      string ZuAoaljPGx;
      string aYnKWEnaIq;
      string GmyAaVctTi;
      string ofKodkpund;
      string XLGPDZfiGB;
      string aSTaZlwANF;
      string JowWItOzgl;
      string OsmeSugiwB;
      string otnRIVMjOr;
      string opgiUhOjGJ;
      string LgCUmhfnHe;
      string ENEMPOBdOm;
      string gdjnwXLEKj;
      string fxbloIqSdZ;
      if(nkBQOZHfQQ == XLGPDZfiGB){pXbinalUSF = true;}
      else if(XLGPDZfiGB == nkBQOZHfQQ){ItkqYQOrlW = true;}
      if(JIqFgiBJOD == aSTaZlwANF){gkVTbhwOXP = true;}
      else if(aSTaZlwANF == JIqFgiBJOD){WTigBMNeQm = true;}
      if(wYqYzhAMea == JowWItOzgl){WbdXyHkRXH = true;}
      else if(JowWItOzgl == wYqYzhAMea){LBwmCjeuXK = true;}
      if(pWYaziIcVE == OsmeSugiwB){XhznxJBBzU = true;}
      else if(OsmeSugiwB == pWYaziIcVE){kRCQukrOrd = true;}
      if(fqkPQIaMNe == otnRIVMjOr){lqkECtbHKG = true;}
      else if(otnRIVMjOr == fqkPQIaMNe){euyNLuMjRS = true;}
      if(zTtdGPtbRg == opgiUhOjGJ){LcuODNsEkg = true;}
      else if(opgiUhOjGJ == zTtdGPtbRg){EPHirGyxoo = true;}
      if(ZuAoaljPGx == LgCUmhfnHe){pTwLhzlgWS = true;}
      else if(LgCUmhfnHe == ZuAoaljPGx){lTTalFRSkP = true;}
      if(aYnKWEnaIq == ENEMPOBdOm){guOCcfpYUD = true;}
      if(GmyAaVctTi == gdjnwXLEKj){ecGRutmjki = true;}
      if(ofKodkpund == fxbloIqSdZ){PwQSeRtYWD = true;}
      while(ENEMPOBdOm == aYnKWEnaIq){UylmIQDhbH = true;}
      while(gdjnwXLEKj == gdjnwXLEKj){WudFFUJSYn = true;}
      while(fxbloIqSdZ == fxbloIqSdZ){ltZDrLaWbG = true;}
      if(pXbinalUSF == true){pXbinalUSF = false;}
      if(gkVTbhwOXP == true){gkVTbhwOXP = false;}
      if(WbdXyHkRXH == true){WbdXyHkRXH = false;}
      if(XhznxJBBzU == true){XhznxJBBzU = false;}
      if(lqkECtbHKG == true){lqkECtbHKG = false;}
      if(LcuODNsEkg == true){LcuODNsEkg = false;}
      if(pTwLhzlgWS == true){pTwLhzlgWS = false;}
      if(guOCcfpYUD == true){guOCcfpYUD = false;}
      if(ecGRutmjki == true){ecGRutmjki = false;}
      if(PwQSeRtYWD == true){PwQSeRtYWD = false;}
      if(ItkqYQOrlW == true){ItkqYQOrlW = false;}
      if(WTigBMNeQm == true){WTigBMNeQm = false;}
      if(LBwmCjeuXK == true){LBwmCjeuXK = false;}
      if(kRCQukrOrd == true){kRCQukrOrd = false;}
      if(euyNLuMjRS == true){euyNLuMjRS = false;}
      if(EPHirGyxoo == true){EPHirGyxoo = false;}
      if(lTTalFRSkP == true){lTTalFRSkP = false;}
      if(UylmIQDhbH == true){UylmIQDhbH = false;}
      if(WudFFUJSYn == true){WudFFUJSYn = false;}
      if(ltZDrLaWbG == true){ltZDrLaWbG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QNEGCOKLRO
{ 
  void uZsPgJHICF()
  { 
      bool RmhCHXiCeM = false;
      bool FABpIloQUk = false;
      bool AGckweSJyd = false;
      bool FLgRRPbAOP = false;
      bool OExkdVLrwG = false;
      bool ZMbIHKJwFb = false;
      bool FYEAHtTjXs = false;
      bool JoCFWwJqHa = false;
      bool SZNqErjXJH = false;
      bool FftlJozwdj = false;
      bool BbTDwjKVlL = false;
      bool BSneIeLMwO = false;
      bool JwZQmduPwg = false;
      bool wMMXYqFJtT = false;
      bool hNlyGmqOcd = false;
      bool dmzPZFBDPS = false;
      bool otZFOnFQGR = false;
      bool YBScgwKbKA = false;
      bool lflRCJNxyS = false;
      bool pCtaemnfiR = false;
      string OcTfXfVDQg;
      string PjgTGwnBiI;
      string jfWJpZntbl;
      string GptSGotImb;
      string LHFzURufbf;
      string ngQSIiGJox;
      string rbbeaYpONR;
      string BfOGwbaXoY;
      string eIRuyZZbKX;
      string hjSojieZXu;
      string bfRJdIRJVf;
      string HhUQSiJggA;
      string zNEpiRMYWM;
      string wAzswypIRo;
      string HQFdPAOCWA;
      string YysXuNbbZL;
      string wrmIiHiaUT;
      string sBPqsiIaZi;
      string DJCVmyGbyi;
      string WNiFsOdwtI;
      if(OcTfXfVDQg == bfRJdIRJVf){RmhCHXiCeM = true;}
      else if(bfRJdIRJVf == OcTfXfVDQg){BbTDwjKVlL = true;}
      if(PjgTGwnBiI == HhUQSiJggA){FABpIloQUk = true;}
      else if(HhUQSiJggA == PjgTGwnBiI){BSneIeLMwO = true;}
      if(jfWJpZntbl == zNEpiRMYWM){AGckweSJyd = true;}
      else if(zNEpiRMYWM == jfWJpZntbl){JwZQmduPwg = true;}
      if(GptSGotImb == wAzswypIRo){FLgRRPbAOP = true;}
      else if(wAzswypIRo == GptSGotImb){wMMXYqFJtT = true;}
      if(LHFzURufbf == HQFdPAOCWA){OExkdVLrwG = true;}
      else if(HQFdPAOCWA == LHFzURufbf){hNlyGmqOcd = true;}
      if(ngQSIiGJox == YysXuNbbZL){ZMbIHKJwFb = true;}
      else if(YysXuNbbZL == ngQSIiGJox){dmzPZFBDPS = true;}
      if(rbbeaYpONR == wrmIiHiaUT){FYEAHtTjXs = true;}
      else if(wrmIiHiaUT == rbbeaYpONR){otZFOnFQGR = true;}
      if(BfOGwbaXoY == sBPqsiIaZi){JoCFWwJqHa = true;}
      if(eIRuyZZbKX == DJCVmyGbyi){SZNqErjXJH = true;}
      if(hjSojieZXu == WNiFsOdwtI){FftlJozwdj = true;}
      while(sBPqsiIaZi == BfOGwbaXoY){YBScgwKbKA = true;}
      while(DJCVmyGbyi == DJCVmyGbyi){lflRCJNxyS = true;}
      while(WNiFsOdwtI == WNiFsOdwtI){pCtaemnfiR = true;}
      if(RmhCHXiCeM == true){RmhCHXiCeM = false;}
      if(FABpIloQUk == true){FABpIloQUk = false;}
      if(AGckweSJyd == true){AGckweSJyd = false;}
      if(FLgRRPbAOP == true){FLgRRPbAOP = false;}
      if(OExkdVLrwG == true){OExkdVLrwG = false;}
      if(ZMbIHKJwFb == true){ZMbIHKJwFb = false;}
      if(FYEAHtTjXs == true){FYEAHtTjXs = false;}
      if(JoCFWwJqHa == true){JoCFWwJqHa = false;}
      if(SZNqErjXJH == true){SZNqErjXJH = false;}
      if(FftlJozwdj == true){FftlJozwdj = false;}
      if(BbTDwjKVlL == true){BbTDwjKVlL = false;}
      if(BSneIeLMwO == true){BSneIeLMwO = false;}
      if(JwZQmduPwg == true){JwZQmduPwg = false;}
      if(wMMXYqFJtT == true){wMMXYqFJtT = false;}
      if(hNlyGmqOcd == true){hNlyGmqOcd = false;}
      if(dmzPZFBDPS == true){dmzPZFBDPS = false;}
      if(otZFOnFQGR == true){otZFOnFQGR = false;}
      if(YBScgwKbKA == true){YBScgwKbKA = false;}
      if(lflRCJNxyS == true){lflRCJNxyS = false;}
      if(pCtaemnfiR == true){pCtaemnfiR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUKECSMUQA
{ 
  void uprzIZklUk()
  { 
      bool FTJxUZrNzX = false;
      bool DcPAGbxPdP = false;
      bool ajOeJtZeTm = false;
      bool sodkeTwdqk = false;
      bool XZYgseFgtn = false;
      bool UqQrIUFdnZ = false;
      bool zMtMdNyeUm = false;
      bool eSXsrAKhle = false;
      bool oskeSCYlbK = false;
      bool NRoQkKfMCe = false;
      bool gaLGIBTXAI = false;
      bool KXrJkGbOtb = false;
      bool oLCKYMdGIg = false;
      bool UxeGxOgdWQ = false;
      bool hBlTApZfee = false;
      bool iRSaoUYBhu = false;
      bool XMOSnMrkLW = false;
      bool ZxqcsnZhJh = false;
      bool mxacyCeERc = false;
      bool pewasVlSfn = false;
      string dnVGrQNqHO;
      string bhLgNfDzue;
      string lLZluphlyw;
      string OktYPOTLFp;
      string htryzycVjg;
      string UJcdNSNiLB;
      string ibsLAqmlQz;
      string LrtExqSblx;
      string NLCQaFHQKx;
      string AkADHGBgyI;
      string KpEjVbPYfW;
      string zlxNnWYbjt;
      string jVaTzarpxq;
      string pkcdlWGRuz;
      string pijnyOmlOj;
      string gYxDYoPkkt;
      string iYbofOJTbQ;
      string PHgjEAklUj;
      string mGbMKQmYEw;
      string HVgBQRGuHj;
      if(dnVGrQNqHO == KpEjVbPYfW){FTJxUZrNzX = true;}
      else if(KpEjVbPYfW == dnVGrQNqHO){gaLGIBTXAI = true;}
      if(bhLgNfDzue == zlxNnWYbjt){DcPAGbxPdP = true;}
      else if(zlxNnWYbjt == bhLgNfDzue){KXrJkGbOtb = true;}
      if(lLZluphlyw == jVaTzarpxq){ajOeJtZeTm = true;}
      else if(jVaTzarpxq == lLZluphlyw){oLCKYMdGIg = true;}
      if(OktYPOTLFp == pkcdlWGRuz){sodkeTwdqk = true;}
      else if(pkcdlWGRuz == OktYPOTLFp){UxeGxOgdWQ = true;}
      if(htryzycVjg == pijnyOmlOj){XZYgseFgtn = true;}
      else if(pijnyOmlOj == htryzycVjg){hBlTApZfee = true;}
      if(UJcdNSNiLB == gYxDYoPkkt){UqQrIUFdnZ = true;}
      else if(gYxDYoPkkt == UJcdNSNiLB){iRSaoUYBhu = true;}
      if(ibsLAqmlQz == iYbofOJTbQ){zMtMdNyeUm = true;}
      else if(iYbofOJTbQ == ibsLAqmlQz){XMOSnMrkLW = true;}
      if(LrtExqSblx == PHgjEAklUj){eSXsrAKhle = true;}
      if(NLCQaFHQKx == mGbMKQmYEw){oskeSCYlbK = true;}
      if(AkADHGBgyI == HVgBQRGuHj){NRoQkKfMCe = true;}
      while(PHgjEAklUj == LrtExqSblx){ZxqcsnZhJh = true;}
      while(mGbMKQmYEw == mGbMKQmYEw){mxacyCeERc = true;}
      while(HVgBQRGuHj == HVgBQRGuHj){pewasVlSfn = true;}
      if(FTJxUZrNzX == true){FTJxUZrNzX = false;}
      if(DcPAGbxPdP == true){DcPAGbxPdP = false;}
      if(ajOeJtZeTm == true){ajOeJtZeTm = false;}
      if(sodkeTwdqk == true){sodkeTwdqk = false;}
      if(XZYgseFgtn == true){XZYgseFgtn = false;}
      if(UqQrIUFdnZ == true){UqQrIUFdnZ = false;}
      if(zMtMdNyeUm == true){zMtMdNyeUm = false;}
      if(eSXsrAKhle == true){eSXsrAKhle = false;}
      if(oskeSCYlbK == true){oskeSCYlbK = false;}
      if(NRoQkKfMCe == true){NRoQkKfMCe = false;}
      if(gaLGIBTXAI == true){gaLGIBTXAI = false;}
      if(KXrJkGbOtb == true){KXrJkGbOtb = false;}
      if(oLCKYMdGIg == true){oLCKYMdGIg = false;}
      if(UxeGxOgdWQ == true){UxeGxOgdWQ = false;}
      if(hBlTApZfee == true){hBlTApZfee = false;}
      if(iRSaoUYBhu == true){iRSaoUYBhu = false;}
      if(XMOSnMrkLW == true){XMOSnMrkLW = false;}
      if(ZxqcsnZhJh == true){ZxqcsnZhJh = false;}
      if(mxacyCeERc == true){mxacyCeERc = false;}
      if(pewasVlSfn == true){pewasVlSfn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LVYHFNSLLU
{ 
  void sbYQsQhKPp()
  { 
      bool XdTGtQGMxF = false;
      bool jpVDKRrtRL = false;
      bool DwCLsdISFi = false;
      bool kcYGyuepFp = false;
      bool rKESBAyJqo = false;
      bool LUAZwbaINQ = false;
      bool InGNUHQPFO = false;
      bool mCnaTrqjKs = false;
      bool ezaPWPczJW = false;
      bool UWbnhDEqyt = false;
      bool ihEcCJfYGE = false;
      bool jqyTkJNppE = false;
      bool eRFitQZAsP = false;
      bool nAlPJwtyNN = false;
      bool iEsFlcYHCY = false;
      bool pNAsPRcVhl = false;
      bool ifepQjFhKn = false;
      bool OPccUaYAwQ = false;
      bool rRxTZaArAr = false;
      bool TYPbeDYCoB = false;
      string xmMziBEUmM;
      string YYaKSCdxbI;
      string DQnNBGxkKq;
      string ESYgeLKess;
      string QsHcUREpbH;
      string hgWMwgzzyb;
      string DTKuHFzsfG;
      string qyDirJIKsi;
      string BHJCJXwMjy;
      string LLgQoxiLVO;
      string RKJUPicmUl;
      string XnFOZwJHli;
      string ImJgtfRmst;
      string axodQqxnlZ;
      string tJrxaXFRps;
      string mbYlFeBcaj;
      string RptZLazbxi;
      string yVUMnzuLGW;
      string ZzxAHzXCYl;
      string pUNCHEORlz;
      if(xmMziBEUmM == RKJUPicmUl){XdTGtQGMxF = true;}
      else if(RKJUPicmUl == xmMziBEUmM){ihEcCJfYGE = true;}
      if(YYaKSCdxbI == XnFOZwJHli){jpVDKRrtRL = true;}
      else if(XnFOZwJHli == YYaKSCdxbI){jqyTkJNppE = true;}
      if(DQnNBGxkKq == ImJgtfRmst){DwCLsdISFi = true;}
      else if(ImJgtfRmst == DQnNBGxkKq){eRFitQZAsP = true;}
      if(ESYgeLKess == axodQqxnlZ){kcYGyuepFp = true;}
      else if(axodQqxnlZ == ESYgeLKess){nAlPJwtyNN = true;}
      if(QsHcUREpbH == tJrxaXFRps){rKESBAyJqo = true;}
      else if(tJrxaXFRps == QsHcUREpbH){iEsFlcYHCY = true;}
      if(hgWMwgzzyb == mbYlFeBcaj){LUAZwbaINQ = true;}
      else if(mbYlFeBcaj == hgWMwgzzyb){pNAsPRcVhl = true;}
      if(DTKuHFzsfG == RptZLazbxi){InGNUHQPFO = true;}
      else if(RptZLazbxi == DTKuHFzsfG){ifepQjFhKn = true;}
      if(qyDirJIKsi == yVUMnzuLGW){mCnaTrqjKs = true;}
      if(BHJCJXwMjy == ZzxAHzXCYl){ezaPWPczJW = true;}
      if(LLgQoxiLVO == pUNCHEORlz){UWbnhDEqyt = true;}
      while(yVUMnzuLGW == qyDirJIKsi){OPccUaYAwQ = true;}
      while(ZzxAHzXCYl == ZzxAHzXCYl){rRxTZaArAr = true;}
      while(pUNCHEORlz == pUNCHEORlz){TYPbeDYCoB = true;}
      if(XdTGtQGMxF == true){XdTGtQGMxF = false;}
      if(jpVDKRrtRL == true){jpVDKRrtRL = false;}
      if(DwCLsdISFi == true){DwCLsdISFi = false;}
      if(kcYGyuepFp == true){kcYGyuepFp = false;}
      if(rKESBAyJqo == true){rKESBAyJqo = false;}
      if(LUAZwbaINQ == true){LUAZwbaINQ = false;}
      if(InGNUHQPFO == true){InGNUHQPFO = false;}
      if(mCnaTrqjKs == true){mCnaTrqjKs = false;}
      if(ezaPWPczJW == true){ezaPWPczJW = false;}
      if(UWbnhDEqyt == true){UWbnhDEqyt = false;}
      if(ihEcCJfYGE == true){ihEcCJfYGE = false;}
      if(jqyTkJNppE == true){jqyTkJNppE = false;}
      if(eRFitQZAsP == true){eRFitQZAsP = false;}
      if(nAlPJwtyNN == true){nAlPJwtyNN = false;}
      if(iEsFlcYHCY == true){iEsFlcYHCY = false;}
      if(pNAsPRcVhl == true){pNAsPRcVhl = false;}
      if(ifepQjFhKn == true){ifepQjFhKn = false;}
      if(OPccUaYAwQ == true){OPccUaYAwQ = false;}
      if(rRxTZaArAr == true){rRxTZaArAr = false;}
      if(TYPbeDYCoB == true){TYPbeDYCoB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DZODNCMXYD
{ 
  void oZELteojkk()
  { 
      bool dVhjtEnSSN = false;
      bool ihJLBrNKJB = false;
      bool ClgXNmUgIC = false;
      bool zRuQKtCPVU = false;
      bool LeqgOzZBKl = false;
      bool BHMgXroKVG = false;
      bool iHJPOQlrAH = false;
      bool oynopWtzIN = false;
      bool NTWWBqEOsS = false;
      bool ErsOkDVaSy = false;
      bool MgACwDSWpB = false;
      bool xoBIsPjlOW = false;
      bool MXzhCwEZEl = false;
      bool ASfKAfTUay = false;
      bool XgXqUOqkVV = false;
      bool TjMwkohRzz = false;
      bool ysSDBdIqHN = false;
      bool uPLQyezHNm = false;
      bool FSDiSPGjYL = false;
      bool xBUazdOTpp = false;
      string kfGbocszwa;
      string qgciKyGeww;
      string ebQfyeRWOa;
      string LYmsmeeXel;
      string DpWrKLJNtC;
      string BqUlYIOZcK;
      string LWjUORtiue;
      string TizJrnFYUl;
      string UDbMZUEAUd;
      string QEtUagGBds;
      string RaSOhRrKtj;
      string DpEqoItXut;
      string MtOROPneiL;
      string hDtbUtkMdH;
      string btFjZZzDeR;
      string lhFjfWLAAR;
      string cNbiBAwcVu;
      string XhsmRRndqn;
      string QkzQYAxJuy;
      string hjMLdOSWhZ;
      if(kfGbocszwa == RaSOhRrKtj){dVhjtEnSSN = true;}
      else if(RaSOhRrKtj == kfGbocszwa){MgACwDSWpB = true;}
      if(qgciKyGeww == DpEqoItXut){ihJLBrNKJB = true;}
      else if(DpEqoItXut == qgciKyGeww){xoBIsPjlOW = true;}
      if(ebQfyeRWOa == MtOROPneiL){ClgXNmUgIC = true;}
      else if(MtOROPneiL == ebQfyeRWOa){MXzhCwEZEl = true;}
      if(LYmsmeeXel == hDtbUtkMdH){zRuQKtCPVU = true;}
      else if(hDtbUtkMdH == LYmsmeeXel){ASfKAfTUay = true;}
      if(DpWrKLJNtC == btFjZZzDeR){LeqgOzZBKl = true;}
      else if(btFjZZzDeR == DpWrKLJNtC){XgXqUOqkVV = true;}
      if(BqUlYIOZcK == lhFjfWLAAR){BHMgXroKVG = true;}
      else if(lhFjfWLAAR == BqUlYIOZcK){TjMwkohRzz = true;}
      if(LWjUORtiue == cNbiBAwcVu){iHJPOQlrAH = true;}
      else if(cNbiBAwcVu == LWjUORtiue){ysSDBdIqHN = true;}
      if(TizJrnFYUl == XhsmRRndqn){oynopWtzIN = true;}
      if(UDbMZUEAUd == QkzQYAxJuy){NTWWBqEOsS = true;}
      if(QEtUagGBds == hjMLdOSWhZ){ErsOkDVaSy = true;}
      while(XhsmRRndqn == TizJrnFYUl){uPLQyezHNm = true;}
      while(QkzQYAxJuy == QkzQYAxJuy){FSDiSPGjYL = true;}
      while(hjMLdOSWhZ == hjMLdOSWhZ){xBUazdOTpp = true;}
      if(dVhjtEnSSN == true){dVhjtEnSSN = false;}
      if(ihJLBrNKJB == true){ihJLBrNKJB = false;}
      if(ClgXNmUgIC == true){ClgXNmUgIC = false;}
      if(zRuQKtCPVU == true){zRuQKtCPVU = false;}
      if(LeqgOzZBKl == true){LeqgOzZBKl = false;}
      if(BHMgXroKVG == true){BHMgXroKVG = false;}
      if(iHJPOQlrAH == true){iHJPOQlrAH = false;}
      if(oynopWtzIN == true){oynopWtzIN = false;}
      if(NTWWBqEOsS == true){NTWWBqEOsS = false;}
      if(ErsOkDVaSy == true){ErsOkDVaSy = false;}
      if(MgACwDSWpB == true){MgACwDSWpB = false;}
      if(xoBIsPjlOW == true){xoBIsPjlOW = false;}
      if(MXzhCwEZEl == true){MXzhCwEZEl = false;}
      if(ASfKAfTUay == true){ASfKAfTUay = false;}
      if(XgXqUOqkVV == true){XgXqUOqkVV = false;}
      if(TjMwkohRzz == true){TjMwkohRzz = false;}
      if(ysSDBdIqHN == true){ysSDBdIqHN = false;}
      if(uPLQyezHNm == true){uPLQyezHNm = false;}
      if(FSDiSPGjYL == true){FSDiSPGjYL = false;}
      if(xBUazdOTpp == true){xBUazdOTpp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NSTDVVVRAF
{ 
  void iAKXSnlQJr()
  { 
      bool gkUJlKkdLX = false;
      bool GHZCOmtcaL = false;
      bool AXnMJTilCm = false;
      bool ixLSlJzfdr = false;
      bool DXAlieiKtl = false;
      bool FfRZzJwIzR = false;
      bool azaXnJwGPE = false;
      bool mNzhHcXBce = false;
      bool kYqPgDelTc = false;
      bool MqfMREwbyY = false;
      bool ibtoyqgjRV = false;
      bool lueUgCHLqj = false;
      bool eJmmqwgmQC = false;
      bool guDEwIdBQp = false;
      bool WuTxpRLLeO = false;
      bool wjkNtYoGxC = false;
      bool JsSPnpraXX = false;
      bool XGtBNipowZ = false;
      bool jVHBFwKpJW = false;
      bool SWDOfcbEIz = false;
      string CPjXTKQMWT;
      string ARiWhKEuRD;
      string lYoWiENtnh;
      string hbstolVBIq;
      string HUDIjjawDd;
      string CSzimdaMnP;
      string wVYolXYogw;
      string oDmZuRUfmz;
      string cRpJfOcKGL;
      string LJMrtluOVL;
      string LlOHoyeZmV;
      string ItZomeePIW;
      string uNhVkequfJ;
      string VGKampCiTg;
      string jCWkCQjWFO;
      string GfFyQxEsVK;
      string HjtdACiyCw;
      string cwubmrpwTT;
      string uToQCoBLKp;
      string lIMJZAIskA;
      if(CPjXTKQMWT == LlOHoyeZmV){gkUJlKkdLX = true;}
      else if(LlOHoyeZmV == CPjXTKQMWT){ibtoyqgjRV = true;}
      if(ARiWhKEuRD == ItZomeePIW){GHZCOmtcaL = true;}
      else if(ItZomeePIW == ARiWhKEuRD){lueUgCHLqj = true;}
      if(lYoWiENtnh == uNhVkequfJ){AXnMJTilCm = true;}
      else if(uNhVkequfJ == lYoWiENtnh){eJmmqwgmQC = true;}
      if(hbstolVBIq == VGKampCiTg){ixLSlJzfdr = true;}
      else if(VGKampCiTg == hbstolVBIq){guDEwIdBQp = true;}
      if(HUDIjjawDd == jCWkCQjWFO){DXAlieiKtl = true;}
      else if(jCWkCQjWFO == HUDIjjawDd){WuTxpRLLeO = true;}
      if(CSzimdaMnP == GfFyQxEsVK){FfRZzJwIzR = true;}
      else if(GfFyQxEsVK == CSzimdaMnP){wjkNtYoGxC = true;}
      if(wVYolXYogw == HjtdACiyCw){azaXnJwGPE = true;}
      else if(HjtdACiyCw == wVYolXYogw){JsSPnpraXX = true;}
      if(oDmZuRUfmz == cwubmrpwTT){mNzhHcXBce = true;}
      if(cRpJfOcKGL == uToQCoBLKp){kYqPgDelTc = true;}
      if(LJMrtluOVL == lIMJZAIskA){MqfMREwbyY = true;}
      while(cwubmrpwTT == oDmZuRUfmz){XGtBNipowZ = true;}
      while(uToQCoBLKp == uToQCoBLKp){jVHBFwKpJW = true;}
      while(lIMJZAIskA == lIMJZAIskA){SWDOfcbEIz = true;}
      if(gkUJlKkdLX == true){gkUJlKkdLX = false;}
      if(GHZCOmtcaL == true){GHZCOmtcaL = false;}
      if(AXnMJTilCm == true){AXnMJTilCm = false;}
      if(ixLSlJzfdr == true){ixLSlJzfdr = false;}
      if(DXAlieiKtl == true){DXAlieiKtl = false;}
      if(FfRZzJwIzR == true){FfRZzJwIzR = false;}
      if(azaXnJwGPE == true){azaXnJwGPE = false;}
      if(mNzhHcXBce == true){mNzhHcXBce = false;}
      if(kYqPgDelTc == true){kYqPgDelTc = false;}
      if(MqfMREwbyY == true){MqfMREwbyY = false;}
      if(ibtoyqgjRV == true){ibtoyqgjRV = false;}
      if(lueUgCHLqj == true){lueUgCHLqj = false;}
      if(eJmmqwgmQC == true){eJmmqwgmQC = false;}
      if(guDEwIdBQp == true){guDEwIdBQp = false;}
      if(WuTxpRLLeO == true){WuTxpRLLeO = false;}
      if(wjkNtYoGxC == true){wjkNtYoGxC = false;}
      if(JsSPnpraXX == true){JsSPnpraXX = false;}
      if(XGtBNipowZ == true){XGtBNipowZ = false;}
      if(jVHBFwKpJW == true){jVHBFwKpJW = false;}
      if(SWDOfcbEIz == true){SWDOfcbEIz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGOCEQMYJH
{ 
  void PJBsWtJhVC()
  { 
      bool iGmWIVkHYk = false;
      bool IGQGRRFBqU = false;
      bool DuaOEXuqeY = false;
      bool LjxyQkMyLj = false;
      bool rhXPYwwGwF = false;
      bool oLNGznfYSj = false;
      bool asczZXJSog = false;
      bool FHpGcUWKpH = false;
      bool aouZjzWqyb = false;
      bool EneaJyFXpB = false;
      bool mdQOAgVGde = false;
      bool RUhLJlyDOZ = false;
      bool BRTMcQcOxd = false;
      bool PyUoUwXfZD = false;
      bool dPMTKiFTRW = false;
      bool ACIPzUKDli = false;
      bool EGIAPSzspM = false;
      bool NScLwkEACs = false;
      bool LJxZdMoFoA = false;
      bool lTsqyWHMEq = false;
      string ZGlXybyWUj;
      string EgFdCZyABY;
      string EfyXeqKUin;
      string wbGJlRgDdc;
      string iKgXtNaKTb;
      string xyIXOtIOrH;
      string QcmgnbZurk;
      string ruWYpszZcR;
      string PzBHpxTiur;
      string JSKVLFXzjS;
      string mfShiCbjgU;
      string thkaqRaepp;
      string IpzzbYjANj;
      string VzpKdjfSYn;
      string ViBaxahjes;
      string drJsJxfSGJ;
      string RaVxytqawH;
      string kHGBTYoYCA;
      string qAUTGdpwAg;
      string DNMOWtNEbD;
      if(ZGlXybyWUj == mfShiCbjgU){iGmWIVkHYk = true;}
      else if(mfShiCbjgU == ZGlXybyWUj){mdQOAgVGde = true;}
      if(EgFdCZyABY == thkaqRaepp){IGQGRRFBqU = true;}
      else if(thkaqRaepp == EgFdCZyABY){RUhLJlyDOZ = true;}
      if(EfyXeqKUin == IpzzbYjANj){DuaOEXuqeY = true;}
      else if(IpzzbYjANj == EfyXeqKUin){BRTMcQcOxd = true;}
      if(wbGJlRgDdc == VzpKdjfSYn){LjxyQkMyLj = true;}
      else if(VzpKdjfSYn == wbGJlRgDdc){PyUoUwXfZD = true;}
      if(iKgXtNaKTb == ViBaxahjes){rhXPYwwGwF = true;}
      else if(ViBaxahjes == iKgXtNaKTb){dPMTKiFTRW = true;}
      if(xyIXOtIOrH == drJsJxfSGJ){oLNGznfYSj = true;}
      else if(drJsJxfSGJ == xyIXOtIOrH){ACIPzUKDli = true;}
      if(QcmgnbZurk == RaVxytqawH){asczZXJSog = true;}
      else if(RaVxytqawH == QcmgnbZurk){EGIAPSzspM = true;}
      if(ruWYpszZcR == kHGBTYoYCA){FHpGcUWKpH = true;}
      if(PzBHpxTiur == qAUTGdpwAg){aouZjzWqyb = true;}
      if(JSKVLFXzjS == DNMOWtNEbD){EneaJyFXpB = true;}
      while(kHGBTYoYCA == ruWYpszZcR){NScLwkEACs = true;}
      while(qAUTGdpwAg == qAUTGdpwAg){LJxZdMoFoA = true;}
      while(DNMOWtNEbD == DNMOWtNEbD){lTsqyWHMEq = true;}
      if(iGmWIVkHYk == true){iGmWIVkHYk = false;}
      if(IGQGRRFBqU == true){IGQGRRFBqU = false;}
      if(DuaOEXuqeY == true){DuaOEXuqeY = false;}
      if(LjxyQkMyLj == true){LjxyQkMyLj = false;}
      if(rhXPYwwGwF == true){rhXPYwwGwF = false;}
      if(oLNGznfYSj == true){oLNGznfYSj = false;}
      if(asczZXJSog == true){asczZXJSog = false;}
      if(FHpGcUWKpH == true){FHpGcUWKpH = false;}
      if(aouZjzWqyb == true){aouZjzWqyb = false;}
      if(EneaJyFXpB == true){EneaJyFXpB = false;}
      if(mdQOAgVGde == true){mdQOAgVGde = false;}
      if(RUhLJlyDOZ == true){RUhLJlyDOZ = false;}
      if(BRTMcQcOxd == true){BRTMcQcOxd = false;}
      if(PyUoUwXfZD == true){PyUoUwXfZD = false;}
      if(dPMTKiFTRW == true){dPMTKiFTRW = false;}
      if(ACIPzUKDli == true){ACIPzUKDli = false;}
      if(EGIAPSzspM == true){EGIAPSzspM = false;}
      if(NScLwkEACs == true){NScLwkEACs = false;}
      if(LJxZdMoFoA == true){LJxZdMoFoA = false;}
      if(lTsqyWHMEq == true){lTsqyWHMEq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXEILZPGNH
{ 
  void EdZcfoRXRC()
  { 
      bool SietWalsmV = false;
      bool nbFzDulgBi = false;
      bool jUuIiupbJV = false;
      bool RaqEjzWWnf = false;
      bool xiXfNQuJbZ = false;
      bool wjBRHxmVLa = false;
      bool kJjRDNjAPD = false;
      bool YPsUkAxOuR = false;
      bool AfAiYgYZxl = false;
      bool LAKMunzGcz = false;
      bool fttXBgqfgG = false;
      bool AXataEIArV = false;
      bool oKDcqXEfZw = false;
      bool BqlukFlbhq = false;
      bool prsplmZQlp = false;
      bool eyNGKVqQgc = false;
      bool cLGjFJleIV = false;
      bool SgSAfwQNqD = false;
      bool xmsiRCcfkP = false;
      bool OUuEOdlJjc = false;
      string gdnjZsmIIt;
      string YIccywnkYj;
      string BuCdcujJTF;
      string UzPEGLubnb;
      string PGXLXAEbrB;
      string znSLokaKHe;
      string IcoDZZsYWm;
      string ALwxUtWpFb;
      string qIRRFffDOU;
      string jkUJSlQUly;
      string HeEFBmrVqu;
      string OjEemALXxs;
      string soKCCPqmdh;
      string cBEGTMDMQR;
      string nJLSFzgoVS;
      string asXsERTCCk;
      string wErJSNfxKa;
      string wzHeFicrwD;
      string hBRKHjcKBC;
      string rAJeViRCAr;
      if(gdnjZsmIIt == HeEFBmrVqu){SietWalsmV = true;}
      else if(HeEFBmrVqu == gdnjZsmIIt){fttXBgqfgG = true;}
      if(YIccywnkYj == OjEemALXxs){nbFzDulgBi = true;}
      else if(OjEemALXxs == YIccywnkYj){AXataEIArV = true;}
      if(BuCdcujJTF == soKCCPqmdh){jUuIiupbJV = true;}
      else if(soKCCPqmdh == BuCdcujJTF){oKDcqXEfZw = true;}
      if(UzPEGLubnb == cBEGTMDMQR){RaqEjzWWnf = true;}
      else if(cBEGTMDMQR == UzPEGLubnb){BqlukFlbhq = true;}
      if(PGXLXAEbrB == nJLSFzgoVS){xiXfNQuJbZ = true;}
      else if(nJLSFzgoVS == PGXLXAEbrB){prsplmZQlp = true;}
      if(znSLokaKHe == asXsERTCCk){wjBRHxmVLa = true;}
      else if(asXsERTCCk == znSLokaKHe){eyNGKVqQgc = true;}
      if(IcoDZZsYWm == wErJSNfxKa){kJjRDNjAPD = true;}
      else if(wErJSNfxKa == IcoDZZsYWm){cLGjFJleIV = true;}
      if(ALwxUtWpFb == wzHeFicrwD){YPsUkAxOuR = true;}
      if(qIRRFffDOU == hBRKHjcKBC){AfAiYgYZxl = true;}
      if(jkUJSlQUly == rAJeViRCAr){LAKMunzGcz = true;}
      while(wzHeFicrwD == ALwxUtWpFb){SgSAfwQNqD = true;}
      while(hBRKHjcKBC == hBRKHjcKBC){xmsiRCcfkP = true;}
      while(rAJeViRCAr == rAJeViRCAr){OUuEOdlJjc = true;}
      if(SietWalsmV == true){SietWalsmV = false;}
      if(nbFzDulgBi == true){nbFzDulgBi = false;}
      if(jUuIiupbJV == true){jUuIiupbJV = false;}
      if(RaqEjzWWnf == true){RaqEjzWWnf = false;}
      if(xiXfNQuJbZ == true){xiXfNQuJbZ = false;}
      if(wjBRHxmVLa == true){wjBRHxmVLa = false;}
      if(kJjRDNjAPD == true){kJjRDNjAPD = false;}
      if(YPsUkAxOuR == true){YPsUkAxOuR = false;}
      if(AfAiYgYZxl == true){AfAiYgYZxl = false;}
      if(LAKMunzGcz == true){LAKMunzGcz = false;}
      if(fttXBgqfgG == true){fttXBgqfgG = false;}
      if(AXataEIArV == true){AXataEIArV = false;}
      if(oKDcqXEfZw == true){oKDcqXEfZw = false;}
      if(BqlukFlbhq == true){BqlukFlbhq = false;}
      if(prsplmZQlp == true){prsplmZQlp = false;}
      if(eyNGKVqQgc == true){eyNGKVqQgc = false;}
      if(cLGjFJleIV == true){cLGjFJleIV = false;}
      if(SgSAfwQNqD == true){SgSAfwQNqD = false;}
      if(xmsiRCcfkP == true){xmsiRCcfkP = false;}
      if(OUuEOdlJjc == true){OUuEOdlJjc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSBUZODMFN
{ 
  void KsrTxRRMaC()
  { 
      bool WrCGXNAzkT = false;
      bool ownghVyzhk = false;
      bool PnutTgxTMK = false;
      bool LzLjeDrWnu = false;
      bool ZfTWONsXJH = false;
      bool THbxGhwHlp = false;
      bool QflZIojECd = false;
      bool caKlKjTXeG = false;
      bool mYJFqDXNcw = false;
      bool HjkyesssOY = false;
      bool coVfdrwolW = false;
      bool NYceDqWgiE = false;
      bool QWaFWspMHR = false;
      bool paJFcxDdby = false;
      bool GiaFihHFum = false;
      bool WMJJIGOPIj = false;
      bool CjgUgmPWCF = false;
      bool nsEkyhuUWn = false;
      bool lkRUtdQzxV = false;
      bool imUqwWBFYu = false;
      string ELPCLMZNtG;
      string rmHnskHIFb;
      string lzswqyUpDI;
      string BYOXjwPLdX;
      string sFIorgPXza;
      string FTsyeFRTLN;
      string qjKkESYiDx;
      string VudgigqEDK;
      string hxqbDhfPse;
      string duAQgItWjZ;
      string HgTCFKoLPy;
      string NNQAfsrihV;
      string mJpXSatNzZ;
      string lTTdCBdoWr;
      string sTzuQQeAjm;
      string QLoNmyquid;
      string PaLpLttlyd;
      string PDLocSJtGB;
      string wtcMIZeFqD;
      string JhFrcRHJiW;
      if(ELPCLMZNtG == HgTCFKoLPy){WrCGXNAzkT = true;}
      else if(HgTCFKoLPy == ELPCLMZNtG){coVfdrwolW = true;}
      if(rmHnskHIFb == NNQAfsrihV){ownghVyzhk = true;}
      else if(NNQAfsrihV == rmHnskHIFb){NYceDqWgiE = true;}
      if(lzswqyUpDI == mJpXSatNzZ){PnutTgxTMK = true;}
      else if(mJpXSatNzZ == lzswqyUpDI){QWaFWspMHR = true;}
      if(BYOXjwPLdX == lTTdCBdoWr){LzLjeDrWnu = true;}
      else if(lTTdCBdoWr == BYOXjwPLdX){paJFcxDdby = true;}
      if(sFIorgPXza == sTzuQQeAjm){ZfTWONsXJH = true;}
      else if(sTzuQQeAjm == sFIorgPXza){GiaFihHFum = true;}
      if(FTsyeFRTLN == QLoNmyquid){THbxGhwHlp = true;}
      else if(QLoNmyquid == FTsyeFRTLN){WMJJIGOPIj = true;}
      if(qjKkESYiDx == PaLpLttlyd){QflZIojECd = true;}
      else if(PaLpLttlyd == qjKkESYiDx){CjgUgmPWCF = true;}
      if(VudgigqEDK == PDLocSJtGB){caKlKjTXeG = true;}
      if(hxqbDhfPse == wtcMIZeFqD){mYJFqDXNcw = true;}
      if(duAQgItWjZ == JhFrcRHJiW){HjkyesssOY = true;}
      while(PDLocSJtGB == VudgigqEDK){nsEkyhuUWn = true;}
      while(wtcMIZeFqD == wtcMIZeFqD){lkRUtdQzxV = true;}
      while(JhFrcRHJiW == JhFrcRHJiW){imUqwWBFYu = true;}
      if(WrCGXNAzkT == true){WrCGXNAzkT = false;}
      if(ownghVyzhk == true){ownghVyzhk = false;}
      if(PnutTgxTMK == true){PnutTgxTMK = false;}
      if(LzLjeDrWnu == true){LzLjeDrWnu = false;}
      if(ZfTWONsXJH == true){ZfTWONsXJH = false;}
      if(THbxGhwHlp == true){THbxGhwHlp = false;}
      if(QflZIojECd == true){QflZIojECd = false;}
      if(caKlKjTXeG == true){caKlKjTXeG = false;}
      if(mYJFqDXNcw == true){mYJFqDXNcw = false;}
      if(HjkyesssOY == true){HjkyesssOY = false;}
      if(coVfdrwolW == true){coVfdrwolW = false;}
      if(NYceDqWgiE == true){NYceDqWgiE = false;}
      if(QWaFWspMHR == true){QWaFWspMHR = false;}
      if(paJFcxDdby == true){paJFcxDdby = false;}
      if(GiaFihHFum == true){GiaFihHFum = false;}
      if(WMJJIGOPIj == true){WMJJIGOPIj = false;}
      if(CjgUgmPWCF == true){CjgUgmPWCF = false;}
      if(nsEkyhuUWn == true){nsEkyhuUWn = false;}
      if(lkRUtdQzxV == true){lkRUtdQzxV = false;}
      if(imUqwWBFYu == true){imUqwWBFYu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NGSZIGSBID
{ 
  void SCHVVGSFUO()
  { 
      bool goJlebUHKt = false;
      bool hrRAsZWjRR = false;
      bool OyHYbyfFEO = false;
      bool OZgJGpnzWJ = false;
      bool lBHeAfILNb = false;
      bool UUNOfhhjJf = false;
      bool uOCweIKHtD = false;
      bool kXMIeNpbXu = false;
      bool oUrcttLScY = false;
      bool HEoqOWzKAr = false;
      bool VBRJpwIFjS = false;
      bool qFLOpZWZCk = false;
      bool wreUughUtH = false;
      bool OfbfZnChlx = false;
      bool lGhKgCsaAn = false;
      bool AYHOwcVwOJ = false;
      bool NmLbELcfoB = false;
      bool WnnFyoJTnr = false;
      bool nHTGHoXMiw = false;
      bool RGTbiyuGGU = false;
      string bbOhLtSeJr;
      string FBlUyVkBZK;
      string qLSfEWdsdN;
      string FKVxfKaYIr;
      string nbrKSGPkPV;
      string zYaedPJhco;
      string PYAwmtenon;
      string uLrhVPTHMy;
      string HsdHOgiqTP;
      string ArwTbPawXY;
      string aaubamgsIN;
      string wCVegWtsgG;
      string KnTYmCPXGF;
      string oXjnWfxBfa;
      string AphFTyWRmE;
      string UhOQOmGWoY;
      string XIlCYYRgIA;
      string ZsMGFTFOEn;
      string eykCkHJSZi;
      string YaMGCqEegu;
      if(bbOhLtSeJr == aaubamgsIN){goJlebUHKt = true;}
      else if(aaubamgsIN == bbOhLtSeJr){VBRJpwIFjS = true;}
      if(FBlUyVkBZK == wCVegWtsgG){hrRAsZWjRR = true;}
      else if(wCVegWtsgG == FBlUyVkBZK){qFLOpZWZCk = true;}
      if(qLSfEWdsdN == KnTYmCPXGF){OyHYbyfFEO = true;}
      else if(KnTYmCPXGF == qLSfEWdsdN){wreUughUtH = true;}
      if(FKVxfKaYIr == oXjnWfxBfa){OZgJGpnzWJ = true;}
      else if(oXjnWfxBfa == FKVxfKaYIr){OfbfZnChlx = true;}
      if(nbrKSGPkPV == AphFTyWRmE){lBHeAfILNb = true;}
      else if(AphFTyWRmE == nbrKSGPkPV){lGhKgCsaAn = true;}
      if(zYaedPJhco == UhOQOmGWoY){UUNOfhhjJf = true;}
      else if(UhOQOmGWoY == zYaedPJhco){AYHOwcVwOJ = true;}
      if(PYAwmtenon == XIlCYYRgIA){uOCweIKHtD = true;}
      else if(XIlCYYRgIA == PYAwmtenon){NmLbELcfoB = true;}
      if(uLrhVPTHMy == ZsMGFTFOEn){kXMIeNpbXu = true;}
      if(HsdHOgiqTP == eykCkHJSZi){oUrcttLScY = true;}
      if(ArwTbPawXY == YaMGCqEegu){HEoqOWzKAr = true;}
      while(ZsMGFTFOEn == uLrhVPTHMy){WnnFyoJTnr = true;}
      while(eykCkHJSZi == eykCkHJSZi){nHTGHoXMiw = true;}
      while(YaMGCqEegu == YaMGCqEegu){RGTbiyuGGU = true;}
      if(goJlebUHKt == true){goJlebUHKt = false;}
      if(hrRAsZWjRR == true){hrRAsZWjRR = false;}
      if(OyHYbyfFEO == true){OyHYbyfFEO = false;}
      if(OZgJGpnzWJ == true){OZgJGpnzWJ = false;}
      if(lBHeAfILNb == true){lBHeAfILNb = false;}
      if(UUNOfhhjJf == true){UUNOfhhjJf = false;}
      if(uOCweIKHtD == true){uOCweIKHtD = false;}
      if(kXMIeNpbXu == true){kXMIeNpbXu = false;}
      if(oUrcttLScY == true){oUrcttLScY = false;}
      if(HEoqOWzKAr == true){HEoqOWzKAr = false;}
      if(VBRJpwIFjS == true){VBRJpwIFjS = false;}
      if(qFLOpZWZCk == true){qFLOpZWZCk = false;}
      if(wreUughUtH == true){wreUughUtH = false;}
      if(OfbfZnChlx == true){OfbfZnChlx = false;}
      if(lGhKgCsaAn == true){lGhKgCsaAn = false;}
      if(AYHOwcVwOJ == true){AYHOwcVwOJ = false;}
      if(NmLbELcfoB == true){NmLbELcfoB = false;}
      if(WnnFyoJTnr == true){WnnFyoJTnr = false;}
      if(nHTGHoXMiw == true){nHTGHoXMiw = false;}
      if(RGTbiyuGGU == true){RGTbiyuGGU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CMPZGXLHHA
{ 
  void cAUboMOiiA()
  { 
      bool AdWiJSErgU = false;
      bool NIEpVgUScI = false;
      bool TCpAHCStDT = false;
      bool HlomtVclGN = false;
      bool gxiwddcAXf = false;
      bool fgSjDymVbG = false;
      bool zJnMMaTQuA = false;
      bool DhMObVStVc = false;
      bool ZSWXnZSEju = false;
      bool hGJzNWJViD = false;
      bool KLEXbxUEIg = false;
      bool fsAyggmQYl = false;
      bool HOgzRwXMAE = false;
      bool MwKSSNNyup = false;
      bool FOuCPnGKSg = false;
      bool jrxxuueEFe = false;
      bool YIDEUiigfT = false;
      bool TnVhgsSdjd = false;
      bool pMsTUTyNXW = false;
      bool hJsPQwKqgg = false;
      string SBbWATIfwL;
      string XTrAmlHOow;
      string upkHSlltGu;
      string TDJJTUKyOG;
      string aVVEptulSj;
      string FnalycQTDO;
      string gNZBqTKhgR;
      string bJziUZTfQX;
      string qAbWpebWLp;
      string DptAZMuUNV;
      string jMEAHuorRX;
      string JjDfXfkDLL;
      string rnVpOlOyJH;
      string dzRundubOt;
      string piFmgSlOcs;
      string brJCdwqOkV;
      string gpiJtJRIrt;
      string jJnQUIhhJu;
      string zzVPfkpPRq;
      string lgpsNAAwsW;
      if(SBbWATIfwL == jMEAHuorRX){AdWiJSErgU = true;}
      else if(jMEAHuorRX == SBbWATIfwL){KLEXbxUEIg = true;}
      if(XTrAmlHOow == JjDfXfkDLL){NIEpVgUScI = true;}
      else if(JjDfXfkDLL == XTrAmlHOow){fsAyggmQYl = true;}
      if(upkHSlltGu == rnVpOlOyJH){TCpAHCStDT = true;}
      else if(rnVpOlOyJH == upkHSlltGu){HOgzRwXMAE = true;}
      if(TDJJTUKyOG == dzRundubOt){HlomtVclGN = true;}
      else if(dzRundubOt == TDJJTUKyOG){MwKSSNNyup = true;}
      if(aVVEptulSj == piFmgSlOcs){gxiwddcAXf = true;}
      else if(piFmgSlOcs == aVVEptulSj){FOuCPnGKSg = true;}
      if(FnalycQTDO == brJCdwqOkV){fgSjDymVbG = true;}
      else if(brJCdwqOkV == FnalycQTDO){jrxxuueEFe = true;}
      if(gNZBqTKhgR == gpiJtJRIrt){zJnMMaTQuA = true;}
      else if(gpiJtJRIrt == gNZBqTKhgR){YIDEUiigfT = true;}
      if(bJziUZTfQX == jJnQUIhhJu){DhMObVStVc = true;}
      if(qAbWpebWLp == zzVPfkpPRq){ZSWXnZSEju = true;}
      if(DptAZMuUNV == lgpsNAAwsW){hGJzNWJViD = true;}
      while(jJnQUIhhJu == bJziUZTfQX){TnVhgsSdjd = true;}
      while(zzVPfkpPRq == zzVPfkpPRq){pMsTUTyNXW = true;}
      while(lgpsNAAwsW == lgpsNAAwsW){hJsPQwKqgg = true;}
      if(AdWiJSErgU == true){AdWiJSErgU = false;}
      if(NIEpVgUScI == true){NIEpVgUScI = false;}
      if(TCpAHCStDT == true){TCpAHCStDT = false;}
      if(HlomtVclGN == true){HlomtVclGN = false;}
      if(gxiwddcAXf == true){gxiwddcAXf = false;}
      if(fgSjDymVbG == true){fgSjDymVbG = false;}
      if(zJnMMaTQuA == true){zJnMMaTQuA = false;}
      if(DhMObVStVc == true){DhMObVStVc = false;}
      if(ZSWXnZSEju == true){ZSWXnZSEju = false;}
      if(hGJzNWJViD == true){hGJzNWJViD = false;}
      if(KLEXbxUEIg == true){KLEXbxUEIg = false;}
      if(fsAyggmQYl == true){fsAyggmQYl = false;}
      if(HOgzRwXMAE == true){HOgzRwXMAE = false;}
      if(MwKSSNNyup == true){MwKSSNNyup = false;}
      if(FOuCPnGKSg == true){FOuCPnGKSg = false;}
      if(jrxxuueEFe == true){jrxxuueEFe = false;}
      if(YIDEUiigfT == true){YIDEUiigfT = false;}
      if(TnVhgsSdjd == true){TnVhgsSdjd = false;}
      if(pMsTUTyNXW == true){pMsTUTyNXW = false;}
      if(hJsPQwKqgg == true){hJsPQwKqgg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QYNXHSLFPF
{ 
  void EcahHVtKkg()
  { 
      bool pFnqEioBIq = false;
      bool OjJRhuxaQf = false;
      bool OeOkwFFqde = false;
      bool SkuJlqmptJ = false;
      bool bqKNdPRapX = false;
      bool PMmIJKpDtz = false;
      bool cyXdXcnAep = false;
      bool HGfHDWTAGg = false;
      bool ndBFOFylzb = false;
      bool BjwufdTgpA = false;
      bool aQwzPIgfFm = false;
      bool powNLzxSOR = false;
      bool dBADoXKkaZ = false;
      bool DlKFFWhBoG = false;
      bool YRgMkLniig = false;
      bool fASXWYQrKr = false;
      bool yuEeiDepHn = false;
      bool QucHsLUnRc = false;
      bool jbBtsCTlig = false;
      bool FoqwHcNCch = false;
      string fzhrGJVyoz;
      string EeBGKOEDmz;
      string qDYlNefkaz;
      string TJdWKjtVdP;
      string EuZROJUElV;
      string wZiePcawea;
      string cjXoeuBdwa;
      string UiYXuucGXE;
      string KbyEDtZyHg;
      string IyqDlTXklT;
      string HqHLBNBLjU;
      string ATXZPAlSlk;
      string UDWPRWrVka;
      string WrUDwTTmDo;
      string sNNlgoZQml;
      string hFyAyETrte;
      string VeZJxHzUcw;
      string gyPwrHojhb;
      string wahzrRsTFr;
      string zasXSNnEnY;
      if(fzhrGJVyoz == HqHLBNBLjU){pFnqEioBIq = true;}
      else if(HqHLBNBLjU == fzhrGJVyoz){aQwzPIgfFm = true;}
      if(EeBGKOEDmz == ATXZPAlSlk){OjJRhuxaQf = true;}
      else if(ATXZPAlSlk == EeBGKOEDmz){powNLzxSOR = true;}
      if(qDYlNefkaz == UDWPRWrVka){OeOkwFFqde = true;}
      else if(UDWPRWrVka == qDYlNefkaz){dBADoXKkaZ = true;}
      if(TJdWKjtVdP == WrUDwTTmDo){SkuJlqmptJ = true;}
      else if(WrUDwTTmDo == TJdWKjtVdP){DlKFFWhBoG = true;}
      if(EuZROJUElV == sNNlgoZQml){bqKNdPRapX = true;}
      else if(sNNlgoZQml == EuZROJUElV){YRgMkLniig = true;}
      if(wZiePcawea == hFyAyETrte){PMmIJKpDtz = true;}
      else if(hFyAyETrte == wZiePcawea){fASXWYQrKr = true;}
      if(cjXoeuBdwa == VeZJxHzUcw){cyXdXcnAep = true;}
      else if(VeZJxHzUcw == cjXoeuBdwa){yuEeiDepHn = true;}
      if(UiYXuucGXE == gyPwrHojhb){HGfHDWTAGg = true;}
      if(KbyEDtZyHg == wahzrRsTFr){ndBFOFylzb = true;}
      if(IyqDlTXklT == zasXSNnEnY){BjwufdTgpA = true;}
      while(gyPwrHojhb == UiYXuucGXE){QucHsLUnRc = true;}
      while(wahzrRsTFr == wahzrRsTFr){jbBtsCTlig = true;}
      while(zasXSNnEnY == zasXSNnEnY){FoqwHcNCch = true;}
      if(pFnqEioBIq == true){pFnqEioBIq = false;}
      if(OjJRhuxaQf == true){OjJRhuxaQf = false;}
      if(OeOkwFFqde == true){OeOkwFFqde = false;}
      if(SkuJlqmptJ == true){SkuJlqmptJ = false;}
      if(bqKNdPRapX == true){bqKNdPRapX = false;}
      if(PMmIJKpDtz == true){PMmIJKpDtz = false;}
      if(cyXdXcnAep == true){cyXdXcnAep = false;}
      if(HGfHDWTAGg == true){HGfHDWTAGg = false;}
      if(ndBFOFylzb == true){ndBFOFylzb = false;}
      if(BjwufdTgpA == true){BjwufdTgpA = false;}
      if(aQwzPIgfFm == true){aQwzPIgfFm = false;}
      if(powNLzxSOR == true){powNLzxSOR = false;}
      if(dBADoXKkaZ == true){dBADoXKkaZ = false;}
      if(DlKFFWhBoG == true){DlKFFWhBoG = false;}
      if(YRgMkLniig == true){YRgMkLniig = false;}
      if(fASXWYQrKr == true){fASXWYQrKr = false;}
      if(yuEeiDepHn == true){yuEeiDepHn = false;}
      if(QucHsLUnRc == true){QucHsLUnRc = false;}
      if(jbBtsCTlig == true){jbBtsCTlig = false;}
      if(FoqwHcNCch == true){FoqwHcNCch = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BAYGSQOEHU
{ 
  void VudGspZLXC()
  { 
      bool FTBbmlfNQJ = false;
      bool jNsSYBwCNL = false;
      bool YruCTRjQRX = false;
      bool ixXGQXNbQJ = false;
      bool FqZbCNhSUQ = false;
      bool sflkFMYzHU = false;
      bool COwsZmpmCB = false;
      bool nUkDFgSSAF = false;
      bool iQuAdCKlAD = false;
      bool yOTwHpufBP = false;
      bool XtQTcYtieY = false;
      bool tGzCkkSuOX = false;
      bool bDmyCZAowP = false;
      bool klQjhnAbWF = false;
      bool IbGaJrORKV = false;
      bool XARdnTHSQD = false;
      bool YElPmHoOUw = false;
      bool kpXIOzxLnK = false;
      bool KheZqkUlwN = false;
      bool ggLTgDppmC = false;
      string EkwEFVBLIb;
      string ZdQYNRhufo;
      string sFVLhqocSk;
      string BnxgoJeYqN;
      string dFmMSVhJDx;
      string fgIZNzOkWO;
      string gXrXalfijE;
      string lIERKnRJrL;
      string IfZVFTfXTp;
      string tsCcgGMPlg;
      string pyYzKWcpOY;
      string gFrKFAxVSG;
      string GHPtJsGajE;
      string bCWLVKGaLh;
      string qoJtInAqWf;
      string IpxfahieoR;
      string QBGJxdigou;
      string sVKjOQxUkV;
      string rOEDwkFpkm;
      string bbltRphAxe;
      if(EkwEFVBLIb == pyYzKWcpOY){FTBbmlfNQJ = true;}
      else if(pyYzKWcpOY == EkwEFVBLIb){XtQTcYtieY = true;}
      if(ZdQYNRhufo == gFrKFAxVSG){jNsSYBwCNL = true;}
      else if(gFrKFAxVSG == ZdQYNRhufo){tGzCkkSuOX = true;}
      if(sFVLhqocSk == GHPtJsGajE){YruCTRjQRX = true;}
      else if(GHPtJsGajE == sFVLhqocSk){bDmyCZAowP = true;}
      if(BnxgoJeYqN == bCWLVKGaLh){ixXGQXNbQJ = true;}
      else if(bCWLVKGaLh == BnxgoJeYqN){klQjhnAbWF = true;}
      if(dFmMSVhJDx == qoJtInAqWf){FqZbCNhSUQ = true;}
      else if(qoJtInAqWf == dFmMSVhJDx){IbGaJrORKV = true;}
      if(fgIZNzOkWO == IpxfahieoR){sflkFMYzHU = true;}
      else if(IpxfahieoR == fgIZNzOkWO){XARdnTHSQD = true;}
      if(gXrXalfijE == QBGJxdigou){COwsZmpmCB = true;}
      else if(QBGJxdigou == gXrXalfijE){YElPmHoOUw = true;}
      if(lIERKnRJrL == sVKjOQxUkV){nUkDFgSSAF = true;}
      if(IfZVFTfXTp == rOEDwkFpkm){iQuAdCKlAD = true;}
      if(tsCcgGMPlg == bbltRphAxe){yOTwHpufBP = true;}
      while(sVKjOQxUkV == lIERKnRJrL){kpXIOzxLnK = true;}
      while(rOEDwkFpkm == rOEDwkFpkm){KheZqkUlwN = true;}
      while(bbltRphAxe == bbltRphAxe){ggLTgDppmC = true;}
      if(FTBbmlfNQJ == true){FTBbmlfNQJ = false;}
      if(jNsSYBwCNL == true){jNsSYBwCNL = false;}
      if(YruCTRjQRX == true){YruCTRjQRX = false;}
      if(ixXGQXNbQJ == true){ixXGQXNbQJ = false;}
      if(FqZbCNhSUQ == true){FqZbCNhSUQ = false;}
      if(sflkFMYzHU == true){sflkFMYzHU = false;}
      if(COwsZmpmCB == true){COwsZmpmCB = false;}
      if(nUkDFgSSAF == true){nUkDFgSSAF = false;}
      if(iQuAdCKlAD == true){iQuAdCKlAD = false;}
      if(yOTwHpufBP == true){yOTwHpufBP = false;}
      if(XtQTcYtieY == true){XtQTcYtieY = false;}
      if(tGzCkkSuOX == true){tGzCkkSuOX = false;}
      if(bDmyCZAowP == true){bDmyCZAowP = false;}
      if(klQjhnAbWF == true){klQjhnAbWF = false;}
      if(IbGaJrORKV == true){IbGaJrORKV = false;}
      if(XARdnTHSQD == true){XARdnTHSQD = false;}
      if(YElPmHoOUw == true){YElPmHoOUw = false;}
      if(kpXIOzxLnK == true){kpXIOzxLnK = false;}
      if(KheZqkUlwN == true){KheZqkUlwN = false;}
      if(ggLTgDppmC == true){ggLTgDppmC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ABVILXMFSS
{ 
  void hBpwQiflfa()
  { 
      bool hzocrVHTSu = false;
      bool lZIJcaDdgT = false;
      bool zbdcPKUHSY = false;
      bool uinEpugPGy = false;
      bool oyYGUQtzMr = false;
      bool KsdFKGULNh = false;
      bool BAAtAClETg = false;
      bool tnWidACXHy = false;
      bool QUuZNBFisi = false;
      bool aUBYwoxeFS = false;
      bool eofeyVVuaJ = false;
      bool DwDORgFafz = false;
      bool wCLjGYmylo = false;
      bool DXSoSanPbr = false;
      bool eKIiedQlHP = false;
      bool jWyFVbduYY = false;
      bool iWIkGfdOup = false;
      bool roynTltbFb = false;
      bool HAqWFfYMSq = false;
      bool xsqDJHBWbz = false;
      string dMgIijbcKA;
      string ZrzshapiXl;
      string tGrkIYHEKw;
      string OUznmnXxgX;
      string tfYomgCTDA;
      string lcjOfWUuzJ;
      string cWSOkErLGt;
      string CsBArOhCyb;
      string WnAJKlkjHQ;
      string TcxXuWMJEh;
      string nqNIxsaiWR;
      string oRxXmnVIDy;
      string THDoZZudFU;
      string BXyQmearMR;
      string LBNpaCfYkG;
      string AEGFOfnXhW;
      string xxdCQQTfjH;
      string NdwlmStNOX;
      string tVszUxRrCG;
      string qDJoTOXKYJ;
      if(dMgIijbcKA == nqNIxsaiWR){hzocrVHTSu = true;}
      else if(nqNIxsaiWR == dMgIijbcKA){eofeyVVuaJ = true;}
      if(ZrzshapiXl == oRxXmnVIDy){lZIJcaDdgT = true;}
      else if(oRxXmnVIDy == ZrzshapiXl){DwDORgFafz = true;}
      if(tGrkIYHEKw == THDoZZudFU){zbdcPKUHSY = true;}
      else if(THDoZZudFU == tGrkIYHEKw){wCLjGYmylo = true;}
      if(OUznmnXxgX == BXyQmearMR){uinEpugPGy = true;}
      else if(BXyQmearMR == OUznmnXxgX){DXSoSanPbr = true;}
      if(tfYomgCTDA == LBNpaCfYkG){oyYGUQtzMr = true;}
      else if(LBNpaCfYkG == tfYomgCTDA){eKIiedQlHP = true;}
      if(lcjOfWUuzJ == AEGFOfnXhW){KsdFKGULNh = true;}
      else if(AEGFOfnXhW == lcjOfWUuzJ){jWyFVbduYY = true;}
      if(cWSOkErLGt == xxdCQQTfjH){BAAtAClETg = true;}
      else if(xxdCQQTfjH == cWSOkErLGt){iWIkGfdOup = true;}
      if(CsBArOhCyb == NdwlmStNOX){tnWidACXHy = true;}
      if(WnAJKlkjHQ == tVszUxRrCG){QUuZNBFisi = true;}
      if(TcxXuWMJEh == qDJoTOXKYJ){aUBYwoxeFS = true;}
      while(NdwlmStNOX == CsBArOhCyb){roynTltbFb = true;}
      while(tVszUxRrCG == tVszUxRrCG){HAqWFfYMSq = true;}
      while(qDJoTOXKYJ == qDJoTOXKYJ){xsqDJHBWbz = true;}
      if(hzocrVHTSu == true){hzocrVHTSu = false;}
      if(lZIJcaDdgT == true){lZIJcaDdgT = false;}
      if(zbdcPKUHSY == true){zbdcPKUHSY = false;}
      if(uinEpugPGy == true){uinEpugPGy = false;}
      if(oyYGUQtzMr == true){oyYGUQtzMr = false;}
      if(KsdFKGULNh == true){KsdFKGULNh = false;}
      if(BAAtAClETg == true){BAAtAClETg = false;}
      if(tnWidACXHy == true){tnWidACXHy = false;}
      if(QUuZNBFisi == true){QUuZNBFisi = false;}
      if(aUBYwoxeFS == true){aUBYwoxeFS = false;}
      if(eofeyVVuaJ == true){eofeyVVuaJ = false;}
      if(DwDORgFafz == true){DwDORgFafz = false;}
      if(wCLjGYmylo == true){wCLjGYmylo = false;}
      if(DXSoSanPbr == true){DXSoSanPbr = false;}
      if(eKIiedQlHP == true){eKIiedQlHP = false;}
      if(jWyFVbduYY == true){jWyFVbduYY = false;}
      if(iWIkGfdOup == true){iWIkGfdOup = false;}
      if(roynTltbFb == true){roynTltbFb = false;}
      if(HAqWFfYMSq == true){HAqWFfYMSq = false;}
      if(xsqDJHBWbz == true){xsqDJHBWbz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FLDUVLLNIN
{ 
  void zhJIarKfFs()
  { 
      bool ELNjFFucFy = false;
      bool UTLnGoXsVs = false;
      bool eYyVcsMkhN = false;
      bool ddcRRUltuS = false;
      bool aZxwLjxNEe = false;
      bool cbNpKeMqHM = false;
      bool sKtrTpqtVl = false;
      bool CcyDSEaBKr = false;
      bool uyfCjCQlHm = false;
      bool IumhYQeFcU = false;
      bool sDrSbzcKXF = false;
      bool EKfORtdqHR = false;
      bool ZElidHpQdC = false;
      bool ZVYoyqGNaj = false;
      bool YGOChxOXPe = false;
      bool lnxKuoRJoU = false;
      bool JLfUehlqQa = false;
      bool nPQWsToiAf = false;
      bool sRBzPlXOsJ = false;
      bool YxYGZMZsWA = false;
      string gcyiYqXuuI;
      string KtEpYMrXrf;
      string NrSFZVlXaT;
      string lYlMaoirot;
      string tKSIzimLxB;
      string FhDWhoJrJC;
      string FAUaVkHrPi;
      string cziykDZJGq;
      string hZZYODVPdl;
      string fqilnsoqmN;
      string auwNYFzEkd;
      string PzlSTfZwLS;
      string PrNdDkQwJq;
      string OhWrPmcLzJ;
      string DQdAWfEQRI;
      string TreTxihSKm;
      string oCutPgbsCg;
      string CNxCOzONGW;
      string fzeBXVCDuf;
      string EJBLTBVjjo;
      if(gcyiYqXuuI == auwNYFzEkd){ELNjFFucFy = true;}
      else if(auwNYFzEkd == gcyiYqXuuI){sDrSbzcKXF = true;}
      if(KtEpYMrXrf == PzlSTfZwLS){UTLnGoXsVs = true;}
      else if(PzlSTfZwLS == KtEpYMrXrf){EKfORtdqHR = true;}
      if(NrSFZVlXaT == PrNdDkQwJq){eYyVcsMkhN = true;}
      else if(PrNdDkQwJq == NrSFZVlXaT){ZElidHpQdC = true;}
      if(lYlMaoirot == OhWrPmcLzJ){ddcRRUltuS = true;}
      else if(OhWrPmcLzJ == lYlMaoirot){ZVYoyqGNaj = true;}
      if(tKSIzimLxB == DQdAWfEQRI){aZxwLjxNEe = true;}
      else if(DQdAWfEQRI == tKSIzimLxB){YGOChxOXPe = true;}
      if(FhDWhoJrJC == TreTxihSKm){cbNpKeMqHM = true;}
      else if(TreTxihSKm == FhDWhoJrJC){lnxKuoRJoU = true;}
      if(FAUaVkHrPi == oCutPgbsCg){sKtrTpqtVl = true;}
      else if(oCutPgbsCg == FAUaVkHrPi){JLfUehlqQa = true;}
      if(cziykDZJGq == CNxCOzONGW){CcyDSEaBKr = true;}
      if(hZZYODVPdl == fzeBXVCDuf){uyfCjCQlHm = true;}
      if(fqilnsoqmN == EJBLTBVjjo){IumhYQeFcU = true;}
      while(CNxCOzONGW == cziykDZJGq){nPQWsToiAf = true;}
      while(fzeBXVCDuf == fzeBXVCDuf){sRBzPlXOsJ = true;}
      while(EJBLTBVjjo == EJBLTBVjjo){YxYGZMZsWA = true;}
      if(ELNjFFucFy == true){ELNjFFucFy = false;}
      if(UTLnGoXsVs == true){UTLnGoXsVs = false;}
      if(eYyVcsMkhN == true){eYyVcsMkhN = false;}
      if(ddcRRUltuS == true){ddcRRUltuS = false;}
      if(aZxwLjxNEe == true){aZxwLjxNEe = false;}
      if(cbNpKeMqHM == true){cbNpKeMqHM = false;}
      if(sKtrTpqtVl == true){sKtrTpqtVl = false;}
      if(CcyDSEaBKr == true){CcyDSEaBKr = false;}
      if(uyfCjCQlHm == true){uyfCjCQlHm = false;}
      if(IumhYQeFcU == true){IumhYQeFcU = false;}
      if(sDrSbzcKXF == true){sDrSbzcKXF = false;}
      if(EKfORtdqHR == true){EKfORtdqHR = false;}
      if(ZElidHpQdC == true){ZElidHpQdC = false;}
      if(ZVYoyqGNaj == true){ZVYoyqGNaj = false;}
      if(YGOChxOXPe == true){YGOChxOXPe = false;}
      if(lnxKuoRJoU == true){lnxKuoRJoU = false;}
      if(JLfUehlqQa == true){JLfUehlqQa = false;}
      if(nPQWsToiAf == true){nPQWsToiAf = false;}
      if(sRBzPlXOsJ == true){sRBzPlXOsJ = false;}
      if(YxYGZMZsWA == true){YxYGZMZsWA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KNRNBWSRBK
{ 
  void KVVhfXVDBQ()
  { 
      bool pSfSiZhaIk = false;
      bool jyDBQKpFia = false;
      bool MwkGtrgbzx = false;
      bool OwyyJyzBOV = false;
      bool OBMQngmGzy = false;
      bool THbtCsgZYp = false;
      bool sGbLWmzEqS = false;
      bool LnpMMLjURM = false;
      bool FabBcHUDwQ = false;
      bool QZcYcHYAsA = false;
      bool hhOgleQOhp = false;
      bool ILHMjSeahP = false;
      bool SwIaBlLRjE = false;
      bool liaReXLuOy = false;
      bool pGUFHFRQnJ = false;
      bool bySdgkYneA = false;
      bool SzddEZjpgM = false;
      bool GjMiZMaDSw = false;
      bool TucZbnQxjs = false;
      bool zXPOepbqAh = false;
      string ucRYZfLjyb;
      string FhkmLKuFQD;
      string FnuxaTyuoI;
      string DeAeOrdBYq;
      string dNiReWmIck;
      string aHtRnHgUxF;
      string gQupYagFYS;
      string fsgZZqFdRE;
      string fpSDgujiqG;
      string LIDSJNSrsD;
      string ogiJEgZTrx;
      string CDCsYqyqIc;
      string qyORHWpOQL;
      string YMkOOzHJyA;
      string VPqtEHGKsS;
      string PajPMqSQBh;
      string qLDfXoRndZ;
      string iorIHaHUNz;
      string QfUywxcUCX;
      string fpHQJJMKVO;
      if(ucRYZfLjyb == ogiJEgZTrx){pSfSiZhaIk = true;}
      else if(ogiJEgZTrx == ucRYZfLjyb){hhOgleQOhp = true;}
      if(FhkmLKuFQD == CDCsYqyqIc){jyDBQKpFia = true;}
      else if(CDCsYqyqIc == FhkmLKuFQD){ILHMjSeahP = true;}
      if(FnuxaTyuoI == qyORHWpOQL){MwkGtrgbzx = true;}
      else if(qyORHWpOQL == FnuxaTyuoI){SwIaBlLRjE = true;}
      if(DeAeOrdBYq == YMkOOzHJyA){OwyyJyzBOV = true;}
      else if(YMkOOzHJyA == DeAeOrdBYq){liaReXLuOy = true;}
      if(dNiReWmIck == VPqtEHGKsS){OBMQngmGzy = true;}
      else if(VPqtEHGKsS == dNiReWmIck){pGUFHFRQnJ = true;}
      if(aHtRnHgUxF == PajPMqSQBh){THbtCsgZYp = true;}
      else if(PajPMqSQBh == aHtRnHgUxF){bySdgkYneA = true;}
      if(gQupYagFYS == qLDfXoRndZ){sGbLWmzEqS = true;}
      else if(qLDfXoRndZ == gQupYagFYS){SzddEZjpgM = true;}
      if(fsgZZqFdRE == iorIHaHUNz){LnpMMLjURM = true;}
      if(fpSDgujiqG == QfUywxcUCX){FabBcHUDwQ = true;}
      if(LIDSJNSrsD == fpHQJJMKVO){QZcYcHYAsA = true;}
      while(iorIHaHUNz == fsgZZqFdRE){GjMiZMaDSw = true;}
      while(QfUywxcUCX == QfUywxcUCX){TucZbnQxjs = true;}
      while(fpHQJJMKVO == fpHQJJMKVO){zXPOepbqAh = true;}
      if(pSfSiZhaIk == true){pSfSiZhaIk = false;}
      if(jyDBQKpFia == true){jyDBQKpFia = false;}
      if(MwkGtrgbzx == true){MwkGtrgbzx = false;}
      if(OwyyJyzBOV == true){OwyyJyzBOV = false;}
      if(OBMQngmGzy == true){OBMQngmGzy = false;}
      if(THbtCsgZYp == true){THbtCsgZYp = false;}
      if(sGbLWmzEqS == true){sGbLWmzEqS = false;}
      if(LnpMMLjURM == true){LnpMMLjURM = false;}
      if(FabBcHUDwQ == true){FabBcHUDwQ = false;}
      if(QZcYcHYAsA == true){QZcYcHYAsA = false;}
      if(hhOgleQOhp == true){hhOgleQOhp = false;}
      if(ILHMjSeahP == true){ILHMjSeahP = false;}
      if(SwIaBlLRjE == true){SwIaBlLRjE = false;}
      if(liaReXLuOy == true){liaReXLuOy = false;}
      if(pGUFHFRQnJ == true){pGUFHFRQnJ = false;}
      if(bySdgkYneA == true){bySdgkYneA = false;}
      if(SzddEZjpgM == true){SzddEZjpgM = false;}
      if(GjMiZMaDSw == true){GjMiZMaDSw = false;}
      if(TucZbnQxjs == true){TucZbnQxjs = false;}
      if(zXPOepbqAh == true){zXPOepbqAh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UKZHWPDBKO
{ 
  void LhhZXiesYE()
  { 
      bool pLcJEuqtFy = false;
      bool xYfxKntFNK = false;
      bool EiajKOVZqV = false;
      bool RNoCpmsyfH = false;
      bool BwDnIDrbea = false;
      bool OztRiHjszo = false;
      bool YQCigiidGW = false;
      bool uuYGJIfmbG = false;
      bool WsuQHRTXSi = false;
      bool DAzphjsTHY = false;
      bool UNVHfTZmIa = false;
      bool bwQsRfVlbO = false;
      bool OLLWTuuiXY = false;
      bool OLfClJXmkm = false;
      bool qfPqHGiGXB = false;
      bool NHqrKIBymj = false;
      bool XqPiLPQNHI = false;
      bool IiBoWhwTPM = false;
      bool LoLVKHUnqc = false;
      bool HYzAOAQfeq = false;
      string hVeYyVcgyz;
      string OshsVjBiGN;
      string iQKMYesgkr;
      string njTCqhOfXD;
      string iPonRmUAiD;
      string TTWmURKRzS;
      string bwuFLeZfBn;
      string VULDeSbWuk;
      string KsygYTNfhZ;
      string WwfFamTibm;
      string NoyuhyISIB;
      string omWNIhxNgq;
      string RtyaQYnFcr;
      string ystIXUuDzZ;
      string LtXfkiZSxr;
      string oFBkVSqWdJ;
      string KCoQDwrOom;
      string mtOHeWVRpg;
      string yVIjCrqJmF;
      string cXYoPIEHcn;
      if(hVeYyVcgyz == NoyuhyISIB){pLcJEuqtFy = true;}
      else if(NoyuhyISIB == hVeYyVcgyz){UNVHfTZmIa = true;}
      if(OshsVjBiGN == omWNIhxNgq){xYfxKntFNK = true;}
      else if(omWNIhxNgq == OshsVjBiGN){bwQsRfVlbO = true;}
      if(iQKMYesgkr == RtyaQYnFcr){EiajKOVZqV = true;}
      else if(RtyaQYnFcr == iQKMYesgkr){OLLWTuuiXY = true;}
      if(njTCqhOfXD == ystIXUuDzZ){RNoCpmsyfH = true;}
      else if(ystIXUuDzZ == njTCqhOfXD){OLfClJXmkm = true;}
      if(iPonRmUAiD == LtXfkiZSxr){BwDnIDrbea = true;}
      else if(LtXfkiZSxr == iPonRmUAiD){qfPqHGiGXB = true;}
      if(TTWmURKRzS == oFBkVSqWdJ){OztRiHjszo = true;}
      else if(oFBkVSqWdJ == TTWmURKRzS){NHqrKIBymj = true;}
      if(bwuFLeZfBn == KCoQDwrOom){YQCigiidGW = true;}
      else if(KCoQDwrOom == bwuFLeZfBn){XqPiLPQNHI = true;}
      if(VULDeSbWuk == mtOHeWVRpg){uuYGJIfmbG = true;}
      if(KsygYTNfhZ == yVIjCrqJmF){WsuQHRTXSi = true;}
      if(WwfFamTibm == cXYoPIEHcn){DAzphjsTHY = true;}
      while(mtOHeWVRpg == VULDeSbWuk){IiBoWhwTPM = true;}
      while(yVIjCrqJmF == yVIjCrqJmF){LoLVKHUnqc = true;}
      while(cXYoPIEHcn == cXYoPIEHcn){HYzAOAQfeq = true;}
      if(pLcJEuqtFy == true){pLcJEuqtFy = false;}
      if(xYfxKntFNK == true){xYfxKntFNK = false;}
      if(EiajKOVZqV == true){EiajKOVZqV = false;}
      if(RNoCpmsyfH == true){RNoCpmsyfH = false;}
      if(BwDnIDrbea == true){BwDnIDrbea = false;}
      if(OztRiHjszo == true){OztRiHjszo = false;}
      if(YQCigiidGW == true){YQCigiidGW = false;}
      if(uuYGJIfmbG == true){uuYGJIfmbG = false;}
      if(WsuQHRTXSi == true){WsuQHRTXSi = false;}
      if(DAzphjsTHY == true){DAzphjsTHY = false;}
      if(UNVHfTZmIa == true){UNVHfTZmIa = false;}
      if(bwQsRfVlbO == true){bwQsRfVlbO = false;}
      if(OLLWTuuiXY == true){OLLWTuuiXY = false;}
      if(OLfClJXmkm == true){OLfClJXmkm = false;}
      if(qfPqHGiGXB == true){qfPqHGiGXB = false;}
      if(NHqrKIBymj == true){NHqrKIBymj = false;}
      if(XqPiLPQNHI == true){XqPiLPQNHI = false;}
      if(IiBoWhwTPM == true){IiBoWhwTPM = false;}
      if(LoLVKHUnqc == true){LoLVKHUnqc = false;}
      if(HYzAOAQfeq == true){HYzAOAQfeq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QCCYKRAUJU
{ 
  void NVqlucRCui()
  { 
      bool mtcDlAjqkJ = false;
      bool exUiFGrRDU = false;
      bool dLLmWUJjGL = false;
      bool ghiByYfQrj = false;
      bool hmEnQlTAWT = false;
      bool BbNswbiogQ = false;
      bool qzjYbwNSjg = false;
      bool abZTmpGXVk = false;
      bool BINlKETpEW = false;
      bool ppjbriCfLU = false;
      bool XAPosZCtGG = false;
      bool UKSwPhlxOX = false;
      bool cWONqjryaD = false;
      bool naMBMAsYsk = false;
      bool CZjyCeWnLK = false;
      bool wERmrAlCxI = false;
      bool gESCSsyRiO = false;
      bool oMEcVCmQKL = false;
      bool MElQGiJYJL = false;
      bool OpajDxHhfI = false;
      string CTyFZtEaAW;
      string gshJsqrXwQ;
      string yqzUeSFBND;
      string LBNfErYyAe;
      string tYrOiRuMyO;
      string dNmobKTcZH;
      string nCMwKfeCEA;
      string StWQWZzkkN;
      string WsDyZxNYDt;
      string YuYsprLuDD;
      string lsHxwjpWSC;
      string LiqLjuyOWM;
      string RGyKbWUdZd;
      string ODghbdkFBo;
      string GqGBhoDMJu;
      string swYqketwVY;
      string OMwnmHBJjF;
      string JsMgFaAxbl;
      string SITdjRdpxw;
      string injbattRNa;
      if(CTyFZtEaAW == lsHxwjpWSC){mtcDlAjqkJ = true;}
      else if(lsHxwjpWSC == CTyFZtEaAW){XAPosZCtGG = true;}
      if(gshJsqrXwQ == LiqLjuyOWM){exUiFGrRDU = true;}
      else if(LiqLjuyOWM == gshJsqrXwQ){UKSwPhlxOX = true;}
      if(yqzUeSFBND == RGyKbWUdZd){dLLmWUJjGL = true;}
      else if(RGyKbWUdZd == yqzUeSFBND){cWONqjryaD = true;}
      if(LBNfErYyAe == ODghbdkFBo){ghiByYfQrj = true;}
      else if(ODghbdkFBo == LBNfErYyAe){naMBMAsYsk = true;}
      if(tYrOiRuMyO == GqGBhoDMJu){hmEnQlTAWT = true;}
      else if(GqGBhoDMJu == tYrOiRuMyO){CZjyCeWnLK = true;}
      if(dNmobKTcZH == swYqketwVY){BbNswbiogQ = true;}
      else if(swYqketwVY == dNmobKTcZH){wERmrAlCxI = true;}
      if(nCMwKfeCEA == OMwnmHBJjF){qzjYbwNSjg = true;}
      else if(OMwnmHBJjF == nCMwKfeCEA){gESCSsyRiO = true;}
      if(StWQWZzkkN == JsMgFaAxbl){abZTmpGXVk = true;}
      if(WsDyZxNYDt == SITdjRdpxw){BINlKETpEW = true;}
      if(YuYsprLuDD == injbattRNa){ppjbriCfLU = true;}
      while(JsMgFaAxbl == StWQWZzkkN){oMEcVCmQKL = true;}
      while(SITdjRdpxw == SITdjRdpxw){MElQGiJYJL = true;}
      while(injbattRNa == injbattRNa){OpajDxHhfI = true;}
      if(mtcDlAjqkJ == true){mtcDlAjqkJ = false;}
      if(exUiFGrRDU == true){exUiFGrRDU = false;}
      if(dLLmWUJjGL == true){dLLmWUJjGL = false;}
      if(ghiByYfQrj == true){ghiByYfQrj = false;}
      if(hmEnQlTAWT == true){hmEnQlTAWT = false;}
      if(BbNswbiogQ == true){BbNswbiogQ = false;}
      if(qzjYbwNSjg == true){qzjYbwNSjg = false;}
      if(abZTmpGXVk == true){abZTmpGXVk = false;}
      if(BINlKETpEW == true){BINlKETpEW = false;}
      if(ppjbriCfLU == true){ppjbriCfLU = false;}
      if(XAPosZCtGG == true){XAPosZCtGG = false;}
      if(UKSwPhlxOX == true){UKSwPhlxOX = false;}
      if(cWONqjryaD == true){cWONqjryaD = false;}
      if(naMBMAsYsk == true){naMBMAsYsk = false;}
      if(CZjyCeWnLK == true){CZjyCeWnLK = false;}
      if(wERmrAlCxI == true){wERmrAlCxI = false;}
      if(gESCSsyRiO == true){gESCSsyRiO = false;}
      if(oMEcVCmQKL == true){oMEcVCmQKL = false;}
      if(MElQGiJYJL == true){MElQGiJYJL = false;}
      if(OpajDxHhfI == true){OpajDxHhfI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PFQEEDJXLA
{ 
  void oqrMSoZwir()
  { 
      bool JtcEBJFJpl = false;
      bool QzfQexEpcl = false;
      bool SxeJUjAHkD = false;
      bool QqChJTGspc = false;
      bool zdYBkEwNUX = false;
      bool KeIFzMOTiQ = false;
      bool IyXlUZwxHL = false;
      bool pKAzmnXdYQ = false;
      bool nmlNslhxhw = false;
      bool EmJYTAGmgK = false;
      bool HyFJgzeIRK = false;
      bool nkuScVLJsi = false;
      bool rzOKHDBael = false;
      bool hjxNIogcfs = false;
      bool GYeWISrqwy = false;
      bool owtxSIjuBd = false;
      bool yDdfcDngJn = false;
      bool oidzbSTrCn = false;
      bool KJdgxkpzuz = false;
      bool FlaCtCuzsE = false;
      string PljkAIwPBY;
      string BJGhFRnQDY;
      string PZkbKKaNzh;
      string uRokYIzUpP;
      string QftUzrpNXl;
      string YCayspAHZp;
      string hiPTciUUIx;
      string RSamHieQcS;
      string TNoNIsqqri;
      string HquzhgParQ;
      string WVFaTFbmpJ;
      string KjeGWUsCKi;
      string qdbYpZXaFZ;
      string SEXMuxHOtD;
      string QEBhYWMncN;
      string nNQIYssfjs;
      string gBhPqGMSLY;
      string MeIHSmctAT;
      string NjxqlEmOmB;
      string DbdAVOVkqS;
      if(PljkAIwPBY == WVFaTFbmpJ){JtcEBJFJpl = true;}
      else if(WVFaTFbmpJ == PljkAIwPBY){HyFJgzeIRK = true;}
      if(BJGhFRnQDY == KjeGWUsCKi){QzfQexEpcl = true;}
      else if(KjeGWUsCKi == BJGhFRnQDY){nkuScVLJsi = true;}
      if(PZkbKKaNzh == qdbYpZXaFZ){SxeJUjAHkD = true;}
      else if(qdbYpZXaFZ == PZkbKKaNzh){rzOKHDBael = true;}
      if(uRokYIzUpP == SEXMuxHOtD){QqChJTGspc = true;}
      else if(SEXMuxHOtD == uRokYIzUpP){hjxNIogcfs = true;}
      if(QftUzrpNXl == QEBhYWMncN){zdYBkEwNUX = true;}
      else if(QEBhYWMncN == QftUzrpNXl){GYeWISrqwy = true;}
      if(YCayspAHZp == nNQIYssfjs){KeIFzMOTiQ = true;}
      else if(nNQIYssfjs == YCayspAHZp){owtxSIjuBd = true;}
      if(hiPTciUUIx == gBhPqGMSLY){IyXlUZwxHL = true;}
      else if(gBhPqGMSLY == hiPTciUUIx){yDdfcDngJn = true;}
      if(RSamHieQcS == MeIHSmctAT){pKAzmnXdYQ = true;}
      if(TNoNIsqqri == NjxqlEmOmB){nmlNslhxhw = true;}
      if(HquzhgParQ == DbdAVOVkqS){EmJYTAGmgK = true;}
      while(MeIHSmctAT == RSamHieQcS){oidzbSTrCn = true;}
      while(NjxqlEmOmB == NjxqlEmOmB){KJdgxkpzuz = true;}
      while(DbdAVOVkqS == DbdAVOVkqS){FlaCtCuzsE = true;}
      if(JtcEBJFJpl == true){JtcEBJFJpl = false;}
      if(QzfQexEpcl == true){QzfQexEpcl = false;}
      if(SxeJUjAHkD == true){SxeJUjAHkD = false;}
      if(QqChJTGspc == true){QqChJTGspc = false;}
      if(zdYBkEwNUX == true){zdYBkEwNUX = false;}
      if(KeIFzMOTiQ == true){KeIFzMOTiQ = false;}
      if(IyXlUZwxHL == true){IyXlUZwxHL = false;}
      if(pKAzmnXdYQ == true){pKAzmnXdYQ = false;}
      if(nmlNslhxhw == true){nmlNslhxhw = false;}
      if(EmJYTAGmgK == true){EmJYTAGmgK = false;}
      if(HyFJgzeIRK == true){HyFJgzeIRK = false;}
      if(nkuScVLJsi == true){nkuScVLJsi = false;}
      if(rzOKHDBael == true){rzOKHDBael = false;}
      if(hjxNIogcfs == true){hjxNIogcfs = false;}
      if(GYeWISrqwy == true){GYeWISrqwy = false;}
      if(owtxSIjuBd == true){owtxSIjuBd = false;}
      if(yDdfcDngJn == true){yDdfcDngJn = false;}
      if(oidzbSTrCn == true){oidzbSTrCn = false;}
      if(KJdgxkpzuz == true){KJdgxkpzuz = false;}
      if(FlaCtCuzsE == true){FlaCtCuzsE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EFNHERIVCL
{ 
  void TJXXuHfCag()
  { 
      bool yaZCtJUgfY = false;
      bool BVMVgLrWxc = false;
      bool wuQRhZcpcp = false;
      bool lOIQPicxhX = false;
      bool kDqtIsVCjj = false;
      bool lTKAdCKIUT = false;
      bool gdEpmmMuGy = false;
      bool htnZqsDVJo = false;
      bool EaGrERDHmM = false;
      bool YUcOqHyBHV = false;
      bool fZwlBrfjJk = false;
      bool ynyfOGWMkU = false;
      bool iFIsYNQZii = false;
      bool uCNnIddUpM = false;
      bool lTyBNjVxzj = false;
      bool jlPmlaQDMm = false;
      bool aFBZpwaKWk = false;
      bool bCVYiPGHeo = false;
      bool rTZyzIlaBh = false;
      bool NaIDkfRXLR = false;
      string idesQXIAbn;
      string PVFNMlDnaQ;
      string JfSoTRecOO;
      string eezahVDlSs;
      string BfBBDDlkFt;
      string kOLmuCKpZy;
      string rflMIkVefp;
      string hRUgOceRlP;
      string etWUdQTLee;
      string KNLTBUtnrR;
      string hHFOLTsdYS;
      string XsDJTyJQiq;
      string RJzAfTFAes;
      string ipYThWnHIK;
      string WomMHRKCzD;
      string LcFBAXIFiq;
      string OsyeigTibx;
      string JBIXUbWlrN;
      string JDAbhGjXSJ;
      string OiXRudpHda;
      if(idesQXIAbn == hHFOLTsdYS){yaZCtJUgfY = true;}
      else if(hHFOLTsdYS == idesQXIAbn){fZwlBrfjJk = true;}
      if(PVFNMlDnaQ == XsDJTyJQiq){BVMVgLrWxc = true;}
      else if(XsDJTyJQiq == PVFNMlDnaQ){ynyfOGWMkU = true;}
      if(JfSoTRecOO == RJzAfTFAes){wuQRhZcpcp = true;}
      else if(RJzAfTFAes == JfSoTRecOO){iFIsYNQZii = true;}
      if(eezahVDlSs == ipYThWnHIK){lOIQPicxhX = true;}
      else if(ipYThWnHIK == eezahVDlSs){uCNnIddUpM = true;}
      if(BfBBDDlkFt == WomMHRKCzD){kDqtIsVCjj = true;}
      else if(WomMHRKCzD == BfBBDDlkFt){lTyBNjVxzj = true;}
      if(kOLmuCKpZy == LcFBAXIFiq){lTKAdCKIUT = true;}
      else if(LcFBAXIFiq == kOLmuCKpZy){jlPmlaQDMm = true;}
      if(rflMIkVefp == OsyeigTibx){gdEpmmMuGy = true;}
      else if(OsyeigTibx == rflMIkVefp){aFBZpwaKWk = true;}
      if(hRUgOceRlP == JBIXUbWlrN){htnZqsDVJo = true;}
      if(etWUdQTLee == JDAbhGjXSJ){EaGrERDHmM = true;}
      if(KNLTBUtnrR == OiXRudpHda){YUcOqHyBHV = true;}
      while(JBIXUbWlrN == hRUgOceRlP){bCVYiPGHeo = true;}
      while(JDAbhGjXSJ == JDAbhGjXSJ){rTZyzIlaBh = true;}
      while(OiXRudpHda == OiXRudpHda){NaIDkfRXLR = true;}
      if(yaZCtJUgfY == true){yaZCtJUgfY = false;}
      if(BVMVgLrWxc == true){BVMVgLrWxc = false;}
      if(wuQRhZcpcp == true){wuQRhZcpcp = false;}
      if(lOIQPicxhX == true){lOIQPicxhX = false;}
      if(kDqtIsVCjj == true){kDqtIsVCjj = false;}
      if(lTKAdCKIUT == true){lTKAdCKIUT = false;}
      if(gdEpmmMuGy == true){gdEpmmMuGy = false;}
      if(htnZqsDVJo == true){htnZqsDVJo = false;}
      if(EaGrERDHmM == true){EaGrERDHmM = false;}
      if(YUcOqHyBHV == true){YUcOqHyBHV = false;}
      if(fZwlBrfjJk == true){fZwlBrfjJk = false;}
      if(ynyfOGWMkU == true){ynyfOGWMkU = false;}
      if(iFIsYNQZii == true){iFIsYNQZii = false;}
      if(uCNnIddUpM == true){uCNnIddUpM = false;}
      if(lTyBNjVxzj == true){lTyBNjVxzj = false;}
      if(jlPmlaQDMm == true){jlPmlaQDMm = false;}
      if(aFBZpwaKWk == true){aFBZpwaKWk = false;}
      if(bCVYiPGHeo == true){bCVYiPGHeo = false;}
      if(rTZyzIlaBh == true){rTZyzIlaBh = false;}
      if(NaIDkfRXLR == true){NaIDkfRXLR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZIMCSIKAH
{ 
  void DJqegdteIU()
  { 
      bool dfuXuxMYIU = false;
      bool JPmgufypei = false;
      bool fUbWIMdlDZ = false;
      bool ygUawLQUPG = false;
      bool QBRYKTWrML = false;
      bool aTUowJEXPi = false;
      bool SZVhWcuMkj = false;
      bool PdZYRdCCMn = false;
      bool olYqzdLfem = false;
      bool HrFgmpfjCh = false;
      bool YKGcwxswWR = false;
      bool GBLasgBehr = false;
      bool QOgybXYslb = false;
      bool ySzdPeeutC = false;
      bool kPJNfFfdmG = false;
      bool oABJQJcIBY = false;
      bool YAKuSnBhLO = false;
      bool BFjfHBFTRV = false;
      bool qtFelxQpMF = false;
      bool BWtVdkENtq = false;
      string LIpEjbKYgU;
      string tzVCnDRcMu;
      string FMVZaVZpDT;
      string ilGNhnMWQs;
      string FVPMEDswEY;
      string nOxfgylPcN;
      string CUVMlHrITz;
      string qtMTpjxJUX;
      string cdkdeTnZfi;
      string BwtCqkzCaw;
      string KjbFhsCdow;
      string BctFkYiqgR;
      string SSbkytAKcF;
      string kuiXMrBfwk;
      string RKjihXCnQR;
      string BHUIdrIqGm;
      string srAjLFtVrr;
      string WDuwAIhrDZ;
      string rMsKEcZZtU;
      string jKYIrZJAXb;
      if(LIpEjbKYgU == KjbFhsCdow){dfuXuxMYIU = true;}
      else if(KjbFhsCdow == LIpEjbKYgU){YKGcwxswWR = true;}
      if(tzVCnDRcMu == BctFkYiqgR){JPmgufypei = true;}
      else if(BctFkYiqgR == tzVCnDRcMu){GBLasgBehr = true;}
      if(FMVZaVZpDT == SSbkytAKcF){fUbWIMdlDZ = true;}
      else if(SSbkytAKcF == FMVZaVZpDT){QOgybXYslb = true;}
      if(ilGNhnMWQs == kuiXMrBfwk){ygUawLQUPG = true;}
      else if(kuiXMrBfwk == ilGNhnMWQs){ySzdPeeutC = true;}
      if(FVPMEDswEY == RKjihXCnQR){QBRYKTWrML = true;}
      else if(RKjihXCnQR == FVPMEDswEY){kPJNfFfdmG = true;}
      if(nOxfgylPcN == BHUIdrIqGm){aTUowJEXPi = true;}
      else if(BHUIdrIqGm == nOxfgylPcN){oABJQJcIBY = true;}
      if(CUVMlHrITz == srAjLFtVrr){SZVhWcuMkj = true;}
      else if(srAjLFtVrr == CUVMlHrITz){YAKuSnBhLO = true;}
      if(qtMTpjxJUX == WDuwAIhrDZ){PdZYRdCCMn = true;}
      if(cdkdeTnZfi == rMsKEcZZtU){olYqzdLfem = true;}
      if(BwtCqkzCaw == jKYIrZJAXb){HrFgmpfjCh = true;}
      while(WDuwAIhrDZ == qtMTpjxJUX){BFjfHBFTRV = true;}
      while(rMsKEcZZtU == rMsKEcZZtU){qtFelxQpMF = true;}
      while(jKYIrZJAXb == jKYIrZJAXb){BWtVdkENtq = true;}
      if(dfuXuxMYIU == true){dfuXuxMYIU = false;}
      if(JPmgufypei == true){JPmgufypei = false;}
      if(fUbWIMdlDZ == true){fUbWIMdlDZ = false;}
      if(ygUawLQUPG == true){ygUawLQUPG = false;}
      if(QBRYKTWrML == true){QBRYKTWrML = false;}
      if(aTUowJEXPi == true){aTUowJEXPi = false;}
      if(SZVhWcuMkj == true){SZVhWcuMkj = false;}
      if(PdZYRdCCMn == true){PdZYRdCCMn = false;}
      if(olYqzdLfem == true){olYqzdLfem = false;}
      if(HrFgmpfjCh == true){HrFgmpfjCh = false;}
      if(YKGcwxswWR == true){YKGcwxswWR = false;}
      if(GBLasgBehr == true){GBLasgBehr = false;}
      if(QOgybXYslb == true){QOgybXYslb = false;}
      if(ySzdPeeutC == true){ySzdPeeutC = false;}
      if(kPJNfFfdmG == true){kPJNfFfdmG = false;}
      if(oABJQJcIBY == true){oABJQJcIBY = false;}
      if(YAKuSnBhLO == true){YAKuSnBhLO = false;}
      if(BFjfHBFTRV == true){BFjfHBFTRV = false;}
      if(qtFelxQpMF == true){qtFelxQpMF = false;}
      if(BWtVdkENtq == true){BWtVdkENtq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZVPHMCXKXH
{ 
  void uMzRCWDeJP()
  { 
      bool ipTQMNkUjW = false;
      bool MCfJhxejOn = false;
      bool QBciHRQXgm = false;
      bool oCrddeIntc = false;
      bool FFoosQzXwu = false;
      bool VAxNthNjJt = false;
      bool wMmwhKJBeC = false;
      bool opokhKLnoq = false;
      bool SrblQnEeiu = false;
      bool RXezgsRsGi = false;
      bool GxstFfKLej = false;
      bool WZtSbDkBet = false;
      bool GeRijQKoEo = false;
      bool rSgGjUzgfk = false;
      bool crzzYrdMXc = false;
      bool IQOLbaeJJo = false;
      bool UUHpqErmhH = false;
      bool EDVsRNfSJr = false;
      bool lyRbgaDUdJ = false;
      bool opWpPHkJHU = false;
      string XFOfKawCeT;
      string DTbbGYXodi;
      string FJlDOfVubK;
      string bNIHZBqBKJ;
      string PAEpqVrLym;
      string hKcdPOTLRd;
      string FAZUroLTBE;
      string gVdUTFEwLr;
      string nJxncRkdrL;
      string hejgEOZjyB;
      string JYKsFLgHKK;
      string KXzZpuClqZ;
      string DhbpWBlwPE;
      string eTxKiPzDhR;
      string kcSgBJfKqI;
      string MnsXxbwTWD;
      string YjrGepZopZ;
      string wyDYnZOtnN;
      string VbFHqqZYMG;
      string SegerBkMBK;
      if(XFOfKawCeT == JYKsFLgHKK){ipTQMNkUjW = true;}
      else if(JYKsFLgHKK == XFOfKawCeT){GxstFfKLej = true;}
      if(DTbbGYXodi == KXzZpuClqZ){MCfJhxejOn = true;}
      else if(KXzZpuClqZ == DTbbGYXodi){WZtSbDkBet = true;}
      if(FJlDOfVubK == DhbpWBlwPE){QBciHRQXgm = true;}
      else if(DhbpWBlwPE == FJlDOfVubK){GeRijQKoEo = true;}
      if(bNIHZBqBKJ == eTxKiPzDhR){oCrddeIntc = true;}
      else if(eTxKiPzDhR == bNIHZBqBKJ){rSgGjUzgfk = true;}
      if(PAEpqVrLym == kcSgBJfKqI){FFoosQzXwu = true;}
      else if(kcSgBJfKqI == PAEpqVrLym){crzzYrdMXc = true;}
      if(hKcdPOTLRd == MnsXxbwTWD){VAxNthNjJt = true;}
      else if(MnsXxbwTWD == hKcdPOTLRd){IQOLbaeJJo = true;}
      if(FAZUroLTBE == YjrGepZopZ){wMmwhKJBeC = true;}
      else if(YjrGepZopZ == FAZUroLTBE){UUHpqErmhH = true;}
      if(gVdUTFEwLr == wyDYnZOtnN){opokhKLnoq = true;}
      if(nJxncRkdrL == VbFHqqZYMG){SrblQnEeiu = true;}
      if(hejgEOZjyB == SegerBkMBK){RXezgsRsGi = true;}
      while(wyDYnZOtnN == gVdUTFEwLr){EDVsRNfSJr = true;}
      while(VbFHqqZYMG == VbFHqqZYMG){lyRbgaDUdJ = true;}
      while(SegerBkMBK == SegerBkMBK){opWpPHkJHU = true;}
      if(ipTQMNkUjW == true){ipTQMNkUjW = false;}
      if(MCfJhxejOn == true){MCfJhxejOn = false;}
      if(QBciHRQXgm == true){QBciHRQXgm = false;}
      if(oCrddeIntc == true){oCrddeIntc = false;}
      if(FFoosQzXwu == true){FFoosQzXwu = false;}
      if(VAxNthNjJt == true){VAxNthNjJt = false;}
      if(wMmwhKJBeC == true){wMmwhKJBeC = false;}
      if(opokhKLnoq == true){opokhKLnoq = false;}
      if(SrblQnEeiu == true){SrblQnEeiu = false;}
      if(RXezgsRsGi == true){RXezgsRsGi = false;}
      if(GxstFfKLej == true){GxstFfKLej = false;}
      if(WZtSbDkBet == true){WZtSbDkBet = false;}
      if(GeRijQKoEo == true){GeRijQKoEo = false;}
      if(rSgGjUzgfk == true){rSgGjUzgfk = false;}
      if(crzzYrdMXc == true){crzzYrdMXc = false;}
      if(IQOLbaeJJo == true){IQOLbaeJJo = false;}
      if(UUHpqErmhH == true){UUHpqErmhH = false;}
      if(EDVsRNfSJr == true){EDVsRNfSJr = false;}
      if(lyRbgaDUdJ == true){lyRbgaDUdJ = false;}
      if(opWpPHkJHU == true){opWpPHkJHU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KPAXTIUVFM
{ 
  void xPQjdmlGEZ()
  { 
      bool yNpBKyfHgZ = false;
      bool mQzwVMbdNu = false;
      bool ldduTqdDry = false;
      bool OtKRBWRmHZ = false;
      bool kcSzhNCPYd = false;
      bool QSMKNUiugT = false;
      bool UcOhKsFguz = false;
      bool toWnKJLeMG = false;
      bool nOeNhwgAEg = false;
      bool mWFmFINjno = false;
      bool HVUYjawYzE = false;
      bool IDhafGyBzO = false;
      bool LFcNMWiihC = false;
      bool uapXyRsFdG = false;
      bool zIAzXiodHy = false;
      bool JMjZcCrGMM = false;
      bool rMpxIhNJcN = false;
      bool MrWrODEcpc = false;
      bool hFairipPuw = false;
      bool YmrROlRDqp = false;
      string FfbFneGFfZ;
      string jHWskcQnrd;
      string LrhLxErUxo;
      string MSOLhcuFrE;
      string aldlJgbRjo;
      string tzGCiMyQHj;
      string mlHqNRsLKI;
      string gLumCZOwCP;
      string bakIuMMLbV;
      string eexHQodmXq;
      string nQGaHiESzJ;
      string yBNqIMAzuA;
      string FgiodBNmVN;
      string wbXKbKTJAL;
      string IsMSWcQFzE;
      string oeqXlHgRxG;
      string UQwlMWdDPx;
      string spyiqLTQRA;
      string jInRXRjzYU;
      string dCMtqrxZFA;
      if(FfbFneGFfZ == nQGaHiESzJ){yNpBKyfHgZ = true;}
      else if(nQGaHiESzJ == FfbFneGFfZ){HVUYjawYzE = true;}
      if(jHWskcQnrd == yBNqIMAzuA){mQzwVMbdNu = true;}
      else if(yBNqIMAzuA == jHWskcQnrd){IDhafGyBzO = true;}
      if(LrhLxErUxo == FgiodBNmVN){ldduTqdDry = true;}
      else if(FgiodBNmVN == LrhLxErUxo){LFcNMWiihC = true;}
      if(MSOLhcuFrE == wbXKbKTJAL){OtKRBWRmHZ = true;}
      else if(wbXKbKTJAL == MSOLhcuFrE){uapXyRsFdG = true;}
      if(aldlJgbRjo == IsMSWcQFzE){kcSzhNCPYd = true;}
      else if(IsMSWcQFzE == aldlJgbRjo){zIAzXiodHy = true;}
      if(tzGCiMyQHj == oeqXlHgRxG){QSMKNUiugT = true;}
      else if(oeqXlHgRxG == tzGCiMyQHj){JMjZcCrGMM = true;}
      if(mlHqNRsLKI == UQwlMWdDPx){UcOhKsFguz = true;}
      else if(UQwlMWdDPx == mlHqNRsLKI){rMpxIhNJcN = true;}
      if(gLumCZOwCP == spyiqLTQRA){toWnKJLeMG = true;}
      if(bakIuMMLbV == jInRXRjzYU){nOeNhwgAEg = true;}
      if(eexHQodmXq == dCMtqrxZFA){mWFmFINjno = true;}
      while(spyiqLTQRA == gLumCZOwCP){MrWrODEcpc = true;}
      while(jInRXRjzYU == jInRXRjzYU){hFairipPuw = true;}
      while(dCMtqrxZFA == dCMtqrxZFA){YmrROlRDqp = true;}
      if(yNpBKyfHgZ == true){yNpBKyfHgZ = false;}
      if(mQzwVMbdNu == true){mQzwVMbdNu = false;}
      if(ldduTqdDry == true){ldduTqdDry = false;}
      if(OtKRBWRmHZ == true){OtKRBWRmHZ = false;}
      if(kcSzhNCPYd == true){kcSzhNCPYd = false;}
      if(QSMKNUiugT == true){QSMKNUiugT = false;}
      if(UcOhKsFguz == true){UcOhKsFguz = false;}
      if(toWnKJLeMG == true){toWnKJLeMG = false;}
      if(nOeNhwgAEg == true){nOeNhwgAEg = false;}
      if(mWFmFINjno == true){mWFmFINjno = false;}
      if(HVUYjawYzE == true){HVUYjawYzE = false;}
      if(IDhafGyBzO == true){IDhafGyBzO = false;}
      if(LFcNMWiihC == true){LFcNMWiihC = false;}
      if(uapXyRsFdG == true){uapXyRsFdG = false;}
      if(zIAzXiodHy == true){zIAzXiodHy = false;}
      if(JMjZcCrGMM == true){JMjZcCrGMM = false;}
      if(rMpxIhNJcN == true){rMpxIhNJcN = false;}
      if(MrWrODEcpc == true){MrWrODEcpc = false;}
      if(hFairipPuw == true){hFairipPuw = false;}
      if(YmrROlRDqp == true){YmrROlRDqp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YRPMFPJMJD
{ 
  void BFVQcCMjuy()
  { 
      bool XyKaoZKRuN = false;
      bool TtJyZfIPpd = false;
      bool egBdMQjVLH = false;
      bool SBSVMbPAba = false;
      bool sgTiyLquCY = false;
      bool cSbFipxfNY = false;
      bool pnGnuSamly = false;
      bool QImPjxNRfB = false;
      bool YnSmeAYNmV = false;
      bool eilDjFaenf = false;
      bool jDJEIUeLUk = false;
      bool ceAMABUSIu = false;
      bool sNAQTgVjfe = false;
      bool WhdzRUdOeK = false;
      bool UMrCrziZCi = false;
      bool jHWrlWDska = false;
      bool ytfpNuBAue = false;
      bool WGnyZfUyXU = false;
      bool ywgwtOLkMt = false;
      bool RkdDLZfCnx = false;
      string rDUIxkwnQz;
      string MElnzujily;
      string TkwOeKLZHl;
      string MXSHKaOoAs;
      string hSppVEsxKF;
      string jmAMwGGFdl;
      string ZWfemokddX;
      string gtisQBtGsZ;
      string QNPCBYXGLD;
      string TJLNTLmLCf;
      string SOTlYoEHwu;
      string MALDULHccN;
      string ReSaDXiUZE;
      string NhDMGCtcdL;
      string UPKQqTxHsH;
      string EJinOnwshA;
      string GjhqgdwywS;
      string RdzQsBUCij;
      string ZaaRADzOxS;
      string FBtcEkhSiN;
      if(rDUIxkwnQz == SOTlYoEHwu){XyKaoZKRuN = true;}
      else if(SOTlYoEHwu == rDUIxkwnQz){jDJEIUeLUk = true;}
      if(MElnzujily == MALDULHccN){TtJyZfIPpd = true;}
      else if(MALDULHccN == MElnzujily){ceAMABUSIu = true;}
      if(TkwOeKLZHl == ReSaDXiUZE){egBdMQjVLH = true;}
      else if(ReSaDXiUZE == TkwOeKLZHl){sNAQTgVjfe = true;}
      if(MXSHKaOoAs == NhDMGCtcdL){SBSVMbPAba = true;}
      else if(NhDMGCtcdL == MXSHKaOoAs){WhdzRUdOeK = true;}
      if(hSppVEsxKF == UPKQqTxHsH){sgTiyLquCY = true;}
      else if(UPKQqTxHsH == hSppVEsxKF){UMrCrziZCi = true;}
      if(jmAMwGGFdl == EJinOnwshA){cSbFipxfNY = true;}
      else if(EJinOnwshA == jmAMwGGFdl){jHWrlWDska = true;}
      if(ZWfemokddX == GjhqgdwywS){pnGnuSamly = true;}
      else if(GjhqgdwywS == ZWfemokddX){ytfpNuBAue = true;}
      if(gtisQBtGsZ == RdzQsBUCij){QImPjxNRfB = true;}
      if(QNPCBYXGLD == ZaaRADzOxS){YnSmeAYNmV = true;}
      if(TJLNTLmLCf == FBtcEkhSiN){eilDjFaenf = true;}
      while(RdzQsBUCij == gtisQBtGsZ){WGnyZfUyXU = true;}
      while(ZaaRADzOxS == ZaaRADzOxS){ywgwtOLkMt = true;}
      while(FBtcEkhSiN == FBtcEkhSiN){RkdDLZfCnx = true;}
      if(XyKaoZKRuN == true){XyKaoZKRuN = false;}
      if(TtJyZfIPpd == true){TtJyZfIPpd = false;}
      if(egBdMQjVLH == true){egBdMQjVLH = false;}
      if(SBSVMbPAba == true){SBSVMbPAba = false;}
      if(sgTiyLquCY == true){sgTiyLquCY = false;}
      if(cSbFipxfNY == true){cSbFipxfNY = false;}
      if(pnGnuSamly == true){pnGnuSamly = false;}
      if(QImPjxNRfB == true){QImPjxNRfB = false;}
      if(YnSmeAYNmV == true){YnSmeAYNmV = false;}
      if(eilDjFaenf == true){eilDjFaenf = false;}
      if(jDJEIUeLUk == true){jDJEIUeLUk = false;}
      if(ceAMABUSIu == true){ceAMABUSIu = false;}
      if(sNAQTgVjfe == true){sNAQTgVjfe = false;}
      if(WhdzRUdOeK == true){WhdzRUdOeK = false;}
      if(UMrCrziZCi == true){UMrCrziZCi = false;}
      if(jHWrlWDska == true){jHWrlWDska = false;}
      if(ytfpNuBAue == true){ytfpNuBAue = false;}
      if(WGnyZfUyXU == true){WGnyZfUyXU = false;}
      if(ywgwtOLkMt == true){ywgwtOLkMt = false;}
      if(RkdDLZfCnx == true){RkdDLZfCnx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIPBJIMBTL
{ 
  void qYpCiyPoMP()
  { 
      bool ExqjBIjwcg = false;
      bool sDcdMVAyZo = false;
      bool rRmAQxGVeq = false;
      bool YuCMRNUXMO = false;
      bool XassTuOFHL = false;
      bool VXmglmKqTE = false;
      bool BNRlHxAPMz = false;
      bool AclLQRXtfU = false;
      bool iBNTVBIVad = false;
      bool CcDHMKJHkV = false;
      bool tyrIKrkaPT = false;
      bool PPKzUAzxQG = false;
      bool odohwWYdzG = false;
      bool HPJKZkIFJc = false;
      bool PgFGOmSEmL = false;
      bool KLqdfPIKLn = false;
      bool SGbJLzGAYj = false;
      bool rtnmqIYiTJ = false;
      bool EUqmwwYedJ = false;
      bool bysVJIEwtP = false;
      string CDSaCHpxCt;
      string xrberqyazp;
      string coKwKOsSaM;
      string IQsfDlwycD;
      string whYRmWReUn;
      string yNONcMsWQm;
      string NWVokgzwbG;
      string uzxutuQrIm;
      string xNxlNtCeCp;
      string rYhopYLjfG;
      string XVDNszQSTh;
      string wAOcpzZjap;
      string eUskOVRHFV;
      string jfMBPaKirO;
      string diLUtrKEzq;
      string yaIobCbSzX;
      string hIMxyPnMMO;
      string opqLMuJYpV;
      string KMIOWIXWZM;
      string yqiUgVVNVd;
      if(CDSaCHpxCt == XVDNszQSTh){ExqjBIjwcg = true;}
      else if(XVDNszQSTh == CDSaCHpxCt){tyrIKrkaPT = true;}
      if(xrberqyazp == wAOcpzZjap){sDcdMVAyZo = true;}
      else if(wAOcpzZjap == xrberqyazp){PPKzUAzxQG = true;}
      if(coKwKOsSaM == eUskOVRHFV){rRmAQxGVeq = true;}
      else if(eUskOVRHFV == coKwKOsSaM){odohwWYdzG = true;}
      if(IQsfDlwycD == jfMBPaKirO){YuCMRNUXMO = true;}
      else if(jfMBPaKirO == IQsfDlwycD){HPJKZkIFJc = true;}
      if(whYRmWReUn == diLUtrKEzq){XassTuOFHL = true;}
      else if(diLUtrKEzq == whYRmWReUn){PgFGOmSEmL = true;}
      if(yNONcMsWQm == yaIobCbSzX){VXmglmKqTE = true;}
      else if(yaIobCbSzX == yNONcMsWQm){KLqdfPIKLn = true;}
      if(NWVokgzwbG == hIMxyPnMMO){BNRlHxAPMz = true;}
      else if(hIMxyPnMMO == NWVokgzwbG){SGbJLzGAYj = true;}
      if(uzxutuQrIm == opqLMuJYpV){AclLQRXtfU = true;}
      if(xNxlNtCeCp == KMIOWIXWZM){iBNTVBIVad = true;}
      if(rYhopYLjfG == yqiUgVVNVd){CcDHMKJHkV = true;}
      while(opqLMuJYpV == uzxutuQrIm){rtnmqIYiTJ = true;}
      while(KMIOWIXWZM == KMIOWIXWZM){EUqmwwYedJ = true;}
      while(yqiUgVVNVd == yqiUgVVNVd){bysVJIEwtP = true;}
      if(ExqjBIjwcg == true){ExqjBIjwcg = false;}
      if(sDcdMVAyZo == true){sDcdMVAyZo = false;}
      if(rRmAQxGVeq == true){rRmAQxGVeq = false;}
      if(YuCMRNUXMO == true){YuCMRNUXMO = false;}
      if(XassTuOFHL == true){XassTuOFHL = false;}
      if(VXmglmKqTE == true){VXmglmKqTE = false;}
      if(BNRlHxAPMz == true){BNRlHxAPMz = false;}
      if(AclLQRXtfU == true){AclLQRXtfU = false;}
      if(iBNTVBIVad == true){iBNTVBIVad = false;}
      if(CcDHMKJHkV == true){CcDHMKJHkV = false;}
      if(tyrIKrkaPT == true){tyrIKrkaPT = false;}
      if(PPKzUAzxQG == true){PPKzUAzxQG = false;}
      if(odohwWYdzG == true){odohwWYdzG = false;}
      if(HPJKZkIFJc == true){HPJKZkIFJc = false;}
      if(PgFGOmSEmL == true){PgFGOmSEmL = false;}
      if(KLqdfPIKLn == true){KLqdfPIKLn = false;}
      if(SGbJLzGAYj == true){SGbJLzGAYj = false;}
      if(rtnmqIYiTJ == true){rtnmqIYiTJ = false;}
      if(EUqmwwYedJ == true){EUqmwwYedJ = false;}
      if(bysVJIEwtP == true){bysVJIEwtP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HNTGJKMXEC
{ 
  void BHtJmIMiEF()
  { 
      bool phPEBQMDRQ = false;
      bool UQhlnmucLD = false;
      bool UgEqngccyA = false;
      bool MsAWhGneKx = false;
      bool PbbsXsKmou = false;
      bool ltwUUIcYQU = false;
      bool mjFREaQKEg = false;
      bool zQROmrEKSt = false;
      bool VonDNSxeBY = false;
      bool cPNoJfWKox = false;
      bool cAiHwVbhhc = false;
      bool ERFVyywCDk = false;
      bool dlIeEiCcFG = false;
      bool VtVVRVFfGr = false;
      bool qPwYUKJrpL = false;
      bool jUGESpqEDM = false;
      bool SybaGJwjEc = false;
      bool rPuLtOojJs = false;
      bool YKlsWBmRCa = false;
      bool eBcsYrmURK = false;
      string UXQbPzCfAL;
      string hMzAhOYFZb;
      string roLjEyxYxU;
      string kylnoBEVRs;
      string lPaVeheKja;
      string yFJxFfLfWQ;
      string BdifZjZLLg;
      string KCmfpcNoFW;
      string SmoVWeoohI;
      string oXzAqIfuut;
      string HSyDPuRdHc;
      string SWZzyOoMJu;
      string tjdDqmDlng;
      string wRtKPznlGa;
      string NLhEpSxzCb;
      string TTlzAWouLc;
      string qeoZfAbPjy;
      string aDGhhiCYMY;
      string oDjLNcftKr;
      string KsZcihWIYp;
      if(UXQbPzCfAL == HSyDPuRdHc){phPEBQMDRQ = true;}
      else if(HSyDPuRdHc == UXQbPzCfAL){cAiHwVbhhc = true;}
      if(hMzAhOYFZb == SWZzyOoMJu){UQhlnmucLD = true;}
      else if(SWZzyOoMJu == hMzAhOYFZb){ERFVyywCDk = true;}
      if(roLjEyxYxU == tjdDqmDlng){UgEqngccyA = true;}
      else if(tjdDqmDlng == roLjEyxYxU){dlIeEiCcFG = true;}
      if(kylnoBEVRs == wRtKPznlGa){MsAWhGneKx = true;}
      else if(wRtKPznlGa == kylnoBEVRs){VtVVRVFfGr = true;}
      if(lPaVeheKja == NLhEpSxzCb){PbbsXsKmou = true;}
      else if(NLhEpSxzCb == lPaVeheKja){qPwYUKJrpL = true;}
      if(yFJxFfLfWQ == TTlzAWouLc){ltwUUIcYQU = true;}
      else if(TTlzAWouLc == yFJxFfLfWQ){jUGESpqEDM = true;}
      if(BdifZjZLLg == qeoZfAbPjy){mjFREaQKEg = true;}
      else if(qeoZfAbPjy == BdifZjZLLg){SybaGJwjEc = true;}
      if(KCmfpcNoFW == aDGhhiCYMY){zQROmrEKSt = true;}
      if(SmoVWeoohI == oDjLNcftKr){VonDNSxeBY = true;}
      if(oXzAqIfuut == KsZcihWIYp){cPNoJfWKox = true;}
      while(aDGhhiCYMY == KCmfpcNoFW){rPuLtOojJs = true;}
      while(oDjLNcftKr == oDjLNcftKr){YKlsWBmRCa = true;}
      while(KsZcihWIYp == KsZcihWIYp){eBcsYrmURK = true;}
      if(phPEBQMDRQ == true){phPEBQMDRQ = false;}
      if(UQhlnmucLD == true){UQhlnmucLD = false;}
      if(UgEqngccyA == true){UgEqngccyA = false;}
      if(MsAWhGneKx == true){MsAWhGneKx = false;}
      if(PbbsXsKmou == true){PbbsXsKmou = false;}
      if(ltwUUIcYQU == true){ltwUUIcYQU = false;}
      if(mjFREaQKEg == true){mjFREaQKEg = false;}
      if(zQROmrEKSt == true){zQROmrEKSt = false;}
      if(VonDNSxeBY == true){VonDNSxeBY = false;}
      if(cPNoJfWKox == true){cPNoJfWKox = false;}
      if(cAiHwVbhhc == true){cAiHwVbhhc = false;}
      if(ERFVyywCDk == true){ERFVyywCDk = false;}
      if(dlIeEiCcFG == true){dlIeEiCcFG = false;}
      if(VtVVRVFfGr == true){VtVVRVFfGr = false;}
      if(qPwYUKJrpL == true){qPwYUKJrpL = false;}
      if(jUGESpqEDM == true){jUGESpqEDM = false;}
      if(SybaGJwjEc == true){SybaGJwjEc = false;}
      if(rPuLtOojJs == true){rPuLtOojJs = false;}
      if(YKlsWBmRCa == true){YKlsWBmRCa = false;}
      if(eBcsYrmURK == true){eBcsYrmURK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFZZLINZFZ
{ 
  void EnCBxGMEKH()
  { 
      bool LrffDoiUZp = false;
      bool ufmqZqwmOx = false;
      bool xmPtXTpMWz = false;
      bool lixDhhxXDV = false;
      bool XbITtBKtrd = false;
      bool MjbcmYbkHj = false;
      bool zWxaDMhiIq = false;
      bool tXisYVdwAW = false;
      bool IuUrlBHTQJ = false;
      bool FMQSVBdgPh = false;
      bool SalAjoBhER = false;
      bool tfjkaECFoC = false;
      bool EOSzlgHPXW = false;
      bool qwfSDgJTHw = false;
      bool AZOyOYberR = false;
      bool zXrNdEIlOC = false;
      bool hkKhZxARgs = false;
      bool thxrBezUjM = false;
      bool EbXFWSESnz = false;
      bool YWFFOOOgXR = false;
      string CtrPpnVyQf;
      string OaOyVGpgPq;
      string wrnZtFYnqb;
      string MzQHsaQhMa;
      string xRkUpVNBGg;
      string VKLxEKGRUj;
      string OgGoTOKGEu;
      string pHToseGSjX;
      string rWhJFBnTDi;
      string UyNcMQKwBa;
      string LGxLqOqWDY;
      string DmhwqqyxiS;
      string apCUaqtpbc;
      string UJRILkZWSq;
      string JRQefgQQlU;
      string RNMizVEbkA;
      string UAtZEtVYkF;
      string QbdrIJZXos;
      string ZcEHLHwiJp;
      string gxlRVJXpak;
      if(CtrPpnVyQf == LGxLqOqWDY){LrffDoiUZp = true;}
      else if(LGxLqOqWDY == CtrPpnVyQf){SalAjoBhER = true;}
      if(OaOyVGpgPq == DmhwqqyxiS){ufmqZqwmOx = true;}
      else if(DmhwqqyxiS == OaOyVGpgPq){tfjkaECFoC = true;}
      if(wrnZtFYnqb == apCUaqtpbc){xmPtXTpMWz = true;}
      else if(apCUaqtpbc == wrnZtFYnqb){EOSzlgHPXW = true;}
      if(MzQHsaQhMa == UJRILkZWSq){lixDhhxXDV = true;}
      else if(UJRILkZWSq == MzQHsaQhMa){qwfSDgJTHw = true;}
      if(xRkUpVNBGg == JRQefgQQlU){XbITtBKtrd = true;}
      else if(JRQefgQQlU == xRkUpVNBGg){AZOyOYberR = true;}
      if(VKLxEKGRUj == RNMizVEbkA){MjbcmYbkHj = true;}
      else if(RNMizVEbkA == VKLxEKGRUj){zXrNdEIlOC = true;}
      if(OgGoTOKGEu == UAtZEtVYkF){zWxaDMhiIq = true;}
      else if(UAtZEtVYkF == OgGoTOKGEu){hkKhZxARgs = true;}
      if(pHToseGSjX == QbdrIJZXos){tXisYVdwAW = true;}
      if(rWhJFBnTDi == ZcEHLHwiJp){IuUrlBHTQJ = true;}
      if(UyNcMQKwBa == gxlRVJXpak){FMQSVBdgPh = true;}
      while(QbdrIJZXos == pHToseGSjX){thxrBezUjM = true;}
      while(ZcEHLHwiJp == ZcEHLHwiJp){EbXFWSESnz = true;}
      while(gxlRVJXpak == gxlRVJXpak){YWFFOOOgXR = true;}
      if(LrffDoiUZp == true){LrffDoiUZp = false;}
      if(ufmqZqwmOx == true){ufmqZqwmOx = false;}
      if(xmPtXTpMWz == true){xmPtXTpMWz = false;}
      if(lixDhhxXDV == true){lixDhhxXDV = false;}
      if(XbITtBKtrd == true){XbITtBKtrd = false;}
      if(MjbcmYbkHj == true){MjbcmYbkHj = false;}
      if(zWxaDMhiIq == true){zWxaDMhiIq = false;}
      if(tXisYVdwAW == true){tXisYVdwAW = false;}
      if(IuUrlBHTQJ == true){IuUrlBHTQJ = false;}
      if(FMQSVBdgPh == true){FMQSVBdgPh = false;}
      if(SalAjoBhER == true){SalAjoBhER = false;}
      if(tfjkaECFoC == true){tfjkaECFoC = false;}
      if(EOSzlgHPXW == true){EOSzlgHPXW = false;}
      if(qwfSDgJTHw == true){qwfSDgJTHw = false;}
      if(AZOyOYberR == true){AZOyOYberR = false;}
      if(zXrNdEIlOC == true){zXrNdEIlOC = false;}
      if(hkKhZxARgs == true){hkKhZxARgs = false;}
      if(thxrBezUjM == true){thxrBezUjM = false;}
      if(EbXFWSESnz == true){EbXFWSESnz = false;}
      if(YWFFOOOgXR == true){YWFFOOOgXR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FPDYFKIFZJ
{ 
  void MjadrfGiTG()
  { 
      bool cEDIVrsHmx = false;
      bool bcYaihYGgl = false;
      bool AQxwyjUWEq = false;
      bool gTpPTYiGqt = false;
      bool hgdMHNNued = false;
      bool SscdDLHGKk = false;
      bool XWDwQHmJGJ = false;
      bool zROlESmjnk = false;
      bool WZqZYmqMLI = false;
      bool RbwGWLdhwA = false;
      bool aEnVeAepYk = false;
      bool XWSZNyedWc = false;
      bool QaxyrXVIPs = false;
      bool oFnnKSkVtX = false;
      bool IAmajtIWrX = false;
      bool fzKSiAGocG = false;
      bool eWZfuSieOu = false;
      bool MJizUPmWOy = false;
      bool OzPqMotUEK = false;
      bool LusnrlZGeQ = false;
      string YHHUEtzaIH;
      string NdtASWDtmR;
      string hhKruuFqhl;
      string JTBMndXdUk;
      string bkujXqBSTC;
      string OaafPpxPYI;
      string oIsWxscgLn;
      string yYZBoxmaTD;
      string tlXfWhsUwx;
      string gIEMwTqXle;
      string NTGeDoBYpS;
      string DWwVOCjNzP;
      string AIjNHpUNFV;
      string FOnnoZfsbh;
      string fTddsKMixs;
      string idYWdFisWN;
      string UnTTNohHfn;
      string WpkRigdGTw;
      string dlPMmaoQKj;
      string plVOMqAJQE;
      if(YHHUEtzaIH == NTGeDoBYpS){cEDIVrsHmx = true;}
      else if(NTGeDoBYpS == YHHUEtzaIH){aEnVeAepYk = true;}
      if(NdtASWDtmR == DWwVOCjNzP){bcYaihYGgl = true;}
      else if(DWwVOCjNzP == NdtASWDtmR){XWSZNyedWc = true;}
      if(hhKruuFqhl == AIjNHpUNFV){AQxwyjUWEq = true;}
      else if(AIjNHpUNFV == hhKruuFqhl){QaxyrXVIPs = true;}
      if(JTBMndXdUk == FOnnoZfsbh){gTpPTYiGqt = true;}
      else if(FOnnoZfsbh == JTBMndXdUk){oFnnKSkVtX = true;}
      if(bkujXqBSTC == fTddsKMixs){hgdMHNNued = true;}
      else if(fTddsKMixs == bkujXqBSTC){IAmajtIWrX = true;}
      if(OaafPpxPYI == idYWdFisWN){SscdDLHGKk = true;}
      else if(idYWdFisWN == OaafPpxPYI){fzKSiAGocG = true;}
      if(oIsWxscgLn == UnTTNohHfn){XWDwQHmJGJ = true;}
      else if(UnTTNohHfn == oIsWxscgLn){eWZfuSieOu = true;}
      if(yYZBoxmaTD == WpkRigdGTw){zROlESmjnk = true;}
      if(tlXfWhsUwx == dlPMmaoQKj){WZqZYmqMLI = true;}
      if(gIEMwTqXle == plVOMqAJQE){RbwGWLdhwA = true;}
      while(WpkRigdGTw == yYZBoxmaTD){MJizUPmWOy = true;}
      while(dlPMmaoQKj == dlPMmaoQKj){OzPqMotUEK = true;}
      while(plVOMqAJQE == plVOMqAJQE){LusnrlZGeQ = true;}
      if(cEDIVrsHmx == true){cEDIVrsHmx = false;}
      if(bcYaihYGgl == true){bcYaihYGgl = false;}
      if(AQxwyjUWEq == true){AQxwyjUWEq = false;}
      if(gTpPTYiGqt == true){gTpPTYiGqt = false;}
      if(hgdMHNNued == true){hgdMHNNued = false;}
      if(SscdDLHGKk == true){SscdDLHGKk = false;}
      if(XWDwQHmJGJ == true){XWDwQHmJGJ = false;}
      if(zROlESmjnk == true){zROlESmjnk = false;}
      if(WZqZYmqMLI == true){WZqZYmqMLI = false;}
      if(RbwGWLdhwA == true){RbwGWLdhwA = false;}
      if(aEnVeAepYk == true){aEnVeAepYk = false;}
      if(XWSZNyedWc == true){XWSZNyedWc = false;}
      if(QaxyrXVIPs == true){QaxyrXVIPs = false;}
      if(oFnnKSkVtX == true){oFnnKSkVtX = false;}
      if(IAmajtIWrX == true){IAmajtIWrX = false;}
      if(fzKSiAGocG == true){fzKSiAGocG = false;}
      if(eWZfuSieOu == true){eWZfuSieOu = false;}
      if(MJizUPmWOy == true){MJizUPmWOy = false;}
      if(OzPqMotUEK == true){OzPqMotUEK = false;}
      if(LusnrlZGeQ == true){LusnrlZGeQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KBKVXKIOKZ
{ 
  void sPiQPNYTUC()
  { 
      bool heCAolIFjq = false;
      bool WJfgQxlUcn = false;
      bool dCIzjoycod = false;
      bool NjoJKzENYX = false;
      bool KJJqGRStmB = false;
      bool rTOCIeWDQz = false;
      bool neQGclUWWR = false;
      bool rYuEcTsRrR = false;
      bool VDomktVlAf = false;
      bool cBwYjfrDNU = false;
      bool wwXVITXJYo = false;
      bool lFKydjodVh = false;
      bool QhVqnqbWUx = false;
      bool apDXVZfTeQ = false;
      bool WLNLsXpxuz = false;
      bool pOhfDNZfhQ = false;
      bool rAobNwBmcD = false;
      bool EVyELEUKxQ = false;
      bool BdbUGLIWTH = false;
      bool zzkNYVWlxx = false;
      string GixfLJEBug;
      string rHGutiEQqa;
      string fKjlnxGdZL;
      string qSKMfKxdCA;
      string PzSTrEMVef;
      string RnSVyuyLqN;
      string CaajoYxsOi;
      string kZOpLgrQtj;
      string kjyttDzoOk;
      string MlmoxnXidS;
      string GTHwtqYbKQ;
      string DhRGcSbgol;
      string ZHddWzmZsW;
      string JJlacRcCzC;
      string dWeygdUfLe;
      string MpsrszocZu;
      string EzimHtwpcL;
      string oZhmICbewr;
      string dHNOKSPshd;
      string bzbEydnqpm;
      if(GixfLJEBug == GTHwtqYbKQ){heCAolIFjq = true;}
      else if(GTHwtqYbKQ == GixfLJEBug){wwXVITXJYo = true;}
      if(rHGutiEQqa == DhRGcSbgol){WJfgQxlUcn = true;}
      else if(DhRGcSbgol == rHGutiEQqa){lFKydjodVh = true;}
      if(fKjlnxGdZL == ZHddWzmZsW){dCIzjoycod = true;}
      else if(ZHddWzmZsW == fKjlnxGdZL){QhVqnqbWUx = true;}
      if(qSKMfKxdCA == JJlacRcCzC){NjoJKzENYX = true;}
      else if(JJlacRcCzC == qSKMfKxdCA){apDXVZfTeQ = true;}
      if(PzSTrEMVef == dWeygdUfLe){KJJqGRStmB = true;}
      else if(dWeygdUfLe == PzSTrEMVef){WLNLsXpxuz = true;}
      if(RnSVyuyLqN == MpsrszocZu){rTOCIeWDQz = true;}
      else if(MpsrszocZu == RnSVyuyLqN){pOhfDNZfhQ = true;}
      if(CaajoYxsOi == EzimHtwpcL){neQGclUWWR = true;}
      else if(EzimHtwpcL == CaajoYxsOi){rAobNwBmcD = true;}
      if(kZOpLgrQtj == oZhmICbewr){rYuEcTsRrR = true;}
      if(kjyttDzoOk == dHNOKSPshd){VDomktVlAf = true;}
      if(MlmoxnXidS == bzbEydnqpm){cBwYjfrDNU = true;}
      while(oZhmICbewr == kZOpLgrQtj){EVyELEUKxQ = true;}
      while(dHNOKSPshd == dHNOKSPshd){BdbUGLIWTH = true;}
      while(bzbEydnqpm == bzbEydnqpm){zzkNYVWlxx = true;}
      if(heCAolIFjq == true){heCAolIFjq = false;}
      if(WJfgQxlUcn == true){WJfgQxlUcn = false;}
      if(dCIzjoycod == true){dCIzjoycod = false;}
      if(NjoJKzENYX == true){NjoJKzENYX = false;}
      if(KJJqGRStmB == true){KJJqGRStmB = false;}
      if(rTOCIeWDQz == true){rTOCIeWDQz = false;}
      if(neQGclUWWR == true){neQGclUWWR = false;}
      if(rYuEcTsRrR == true){rYuEcTsRrR = false;}
      if(VDomktVlAf == true){VDomktVlAf = false;}
      if(cBwYjfrDNU == true){cBwYjfrDNU = false;}
      if(wwXVITXJYo == true){wwXVITXJYo = false;}
      if(lFKydjodVh == true){lFKydjodVh = false;}
      if(QhVqnqbWUx == true){QhVqnqbWUx = false;}
      if(apDXVZfTeQ == true){apDXVZfTeQ = false;}
      if(WLNLsXpxuz == true){WLNLsXpxuz = false;}
      if(pOhfDNZfhQ == true){pOhfDNZfhQ = false;}
      if(rAobNwBmcD == true){rAobNwBmcD = false;}
      if(EVyELEUKxQ == true){EVyELEUKxQ = false;}
      if(BdbUGLIWTH == true){BdbUGLIWTH = false;}
      if(zzkNYVWlxx == true){zzkNYVWlxx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZPTDVBUCPW
{ 
  void sShTJFfJpE()
  { 
      bool xXfQWoBQhi = false;
      bool GSNjPoYqVD = false;
      bool aIzDhGopns = false;
      bool njwbwADbDB = false;
      bool ECNfsoBRnJ = false;
      bool FqoRtoYbhQ = false;
      bool zLbnuVVlmP = false;
      bool lxmUzXuSKr = false;
      bool FWBenwtdhH = false;
      bool basmCraYkW = false;
      bool SPeYWIDUSV = false;
      bool sFRpLbJxAz = false;
      bool brEemKDASG = false;
      bool xVhnZprcHe = false;
      bool rZKLNVIDbZ = false;
      bool icYluaKzkM = false;
      bool FDCMXXXdPU = false;
      bool jfoUGBgrRR = false;
      bool CzXrWTwwrz = false;
      bool erquZnXymp = false;
      string NhZmMFKOYG;
      string kpnbzqNpgF;
      string NNuoPBOidE;
      string VaQxhuIJAc;
      string eWeOotZRdj;
      string sGoJEAmkXK;
      string qbjTkKZqtD;
      string iDoEZqhfAU;
      string bwFtLOlHsg;
      string IXlolDmLdd;
      string TiWZAoRjiN;
      string RGjDitWoIW;
      string XSxMuLRzSW;
      string DWCVAsYftV;
      string xBXePBmhGq;
      string fxDGGBkKdo;
      string XRRMJtEOCp;
      string UqulYWuRwt;
      string YirapGTuPz;
      string HOBEyeiLVU;
      if(NhZmMFKOYG == TiWZAoRjiN){xXfQWoBQhi = true;}
      else if(TiWZAoRjiN == NhZmMFKOYG){SPeYWIDUSV = true;}
      if(kpnbzqNpgF == RGjDitWoIW){GSNjPoYqVD = true;}
      else if(RGjDitWoIW == kpnbzqNpgF){sFRpLbJxAz = true;}
      if(NNuoPBOidE == XSxMuLRzSW){aIzDhGopns = true;}
      else if(XSxMuLRzSW == NNuoPBOidE){brEemKDASG = true;}
      if(VaQxhuIJAc == DWCVAsYftV){njwbwADbDB = true;}
      else if(DWCVAsYftV == VaQxhuIJAc){xVhnZprcHe = true;}
      if(eWeOotZRdj == xBXePBmhGq){ECNfsoBRnJ = true;}
      else if(xBXePBmhGq == eWeOotZRdj){rZKLNVIDbZ = true;}
      if(sGoJEAmkXK == fxDGGBkKdo){FqoRtoYbhQ = true;}
      else if(fxDGGBkKdo == sGoJEAmkXK){icYluaKzkM = true;}
      if(qbjTkKZqtD == XRRMJtEOCp){zLbnuVVlmP = true;}
      else if(XRRMJtEOCp == qbjTkKZqtD){FDCMXXXdPU = true;}
      if(iDoEZqhfAU == UqulYWuRwt){lxmUzXuSKr = true;}
      if(bwFtLOlHsg == YirapGTuPz){FWBenwtdhH = true;}
      if(IXlolDmLdd == HOBEyeiLVU){basmCraYkW = true;}
      while(UqulYWuRwt == iDoEZqhfAU){jfoUGBgrRR = true;}
      while(YirapGTuPz == YirapGTuPz){CzXrWTwwrz = true;}
      while(HOBEyeiLVU == HOBEyeiLVU){erquZnXymp = true;}
      if(xXfQWoBQhi == true){xXfQWoBQhi = false;}
      if(GSNjPoYqVD == true){GSNjPoYqVD = false;}
      if(aIzDhGopns == true){aIzDhGopns = false;}
      if(njwbwADbDB == true){njwbwADbDB = false;}
      if(ECNfsoBRnJ == true){ECNfsoBRnJ = false;}
      if(FqoRtoYbhQ == true){FqoRtoYbhQ = false;}
      if(zLbnuVVlmP == true){zLbnuVVlmP = false;}
      if(lxmUzXuSKr == true){lxmUzXuSKr = false;}
      if(FWBenwtdhH == true){FWBenwtdhH = false;}
      if(basmCraYkW == true){basmCraYkW = false;}
      if(SPeYWIDUSV == true){SPeYWIDUSV = false;}
      if(sFRpLbJxAz == true){sFRpLbJxAz = false;}
      if(brEemKDASG == true){brEemKDASG = false;}
      if(xVhnZprcHe == true){xVhnZprcHe = false;}
      if(rZKLNVIDbZ == true){rZKLNVIDbZ = false;}
      if(icYluaKzkM == true){icYluaKzkM = false;}
      if(FDCMXXXdPU == true){FDCMXXXdPU = false;}
      if(jfoUGBgrRR == true){jfoUGBgrRR = false;}
      if(CzXrWTwwrz == true){CzXrWTwwrz = false;}
      if(erquZnXymp == true){erquZnXymp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NLWFFGFATX
{ 
  void RczSroBTGQ()
  { 
      bool UVPhhNISAl = false;
      bool spixyZCkrm = false;
      bool FMlChaBNyr = false;
      bool mCfoKbjqLx = false;
      bool GUxPsBOySx = false;
      bool PEGTnIiMAG = false;
      bool LuTHzqKtlW = false;
      bool oKZugkPWIf = false;
      bool MDuBbiwLAB = false;
      bool rXqFkLAoPB = false;
      bool qTLuHEdLmD = false;
      bool sMDTsIzRfQ = false;
      bool uytjdRTTJV = false;
      bool jZGHorrAtW = false;
      bool EjYxIfTWLb = false;
      bool LiJzGrZaQp = false;
      bool kKBQSSFweA = false;
      bool QzXILKZxby = false;
      bool xwIgJBQGAx = false;
      bool SQiDltiHdp = false;
      string rwUHgTfJkQ;
      string XbTrwWMkkH;
      string fnElFlZCwo;
      string DazGMoyeyo;
      string HtEdIZoUsc;
      string MxaYqErhCt;
      string tcMwMwcMeG;
      string XhluAkjZce;
      string xFJSbGzZPI;
      string xPcEudhHRL;
      string xbolEeKeYF;
      string URFXwnTsTG;
      string xCxWJIFhAV;
      string DbIQhVPWNx;
      string uUBJmeKFIG;
      string KnnKOtdSbw;
      string ZceDCsJnoZ;
      string YweVKcAmie;
      string xAZsKOmxBm;
      string rxuRWSoyHt;
      if(rwUHgTfJkQ == xbolEeKeYF){UVPhhNISAl = true;}
      else if(xbolEeKeYF == rwUHgTfJkQ){qTLuHEdLmD = true;}
      if(XbTrwWMkkH == URFXwnTsTG){spixyZCkrm = true;}
      else if(URFXwnTsTG == XbTrwWMkkH){sMDTsIzRfQ = true;}
      if(fnElFlZCwo == xCxWJIFhAV){FMlChaBNyr = true;}
      else if(xCxWJIFhAV == fnElFlZCwo){uytjdRTTJV = true;}
      if(DazGMoyeyo == DbIQhVPWNx){mCfoKbjqLx = true;}
      else if(DbIQhVPWNx == DazGMoyeyo){jZGHorrAtW = true;}
      if(HtEdIZoUsc == uUBJmeKFIG){GUxPsBOySx = true;}
      else if(uUBJmeKFIG == HtEdIZoUsc){EjYxIfTWLb = true;}
      if(MxaYqErhCt == KnnKOtdSbw){PEGTnIiMAG = true;}
      else if(KnnKOtdSbw == MxaYqErhCt){LiJzGrZaQp = true;}
      if(tcMwMwcMeG == ZceDCsJnoZ){LuTHzqKtlW = true;}
      else if(ZceDCsJnoZ == tcMwMwcMeG){kKBQSSFweA = true;}
      if(XhluAkjZce == YweVKcAmie){oKZugkPWIf = true;}
      if(xFJSbGzZPI == xAZsKOmxBm){MDuBbiwLAB = true;}
      if(xPcEudhHRL == rxuRWSoyHt){rXqFkLAoPB = true;}
      while(YweVKcAmie == XhluAkjZce){QzXILKZxby = true;}
      while(xAZsKOmxBm == xAZsKOmxBm){xwIgJBQGAx = true;}
      while(rxuRWSoyHt == rxuRWSoyHt){SQiDltiHdp = true;}
      if(UVPhhNISAl == true){UVPhhNISAl = false;}
      if(spixyZCkrm == true){spixyZCkrm = false;}
      if(FMlChaBNyr == true){FMlChaBNyr = false;}
      if(mCfoKbjqLx == true){mCfoKbjqLx = false;}
      if(GUxPsBOySx == true){GUxPsBOySx = false;}
      if(PEGTnIiMAG == true){PEGTnIiMAG = false;}
      if(LuTHzqKtlW == true){LuTHzqKtlW = false;}
      if(oKZugkPWIf == true){oKZugkPWIf = false;}
      if(MDuBbiwLAB == true){MDuBbiwLAB = false;}
      if(rXqFkLAoPB == true){rXqFkLAoPB = false;}
      if(qTLuHEdLmD == true){qTLuHEdLmD = false;}
      if(sMDTsIzRfQ == true){sMDTsIzRfQ = false;}
      if(uytjdRTTJV == true){uytjdRTTJV = false;}
      if(jZGHorrAtW == true){jZGHorrAtW = false;}
      if(EjYxIfTWLb == true){EjYxIfTWLb = false;}
      if(LiJzGrZaQp == true){LiJzGrZaQp = false;}
      if(kKBQSSFweA == true){kKBQSSFweA = false;}
      if(QzXILKZxby == true){QzXILKZxby = false;}
      if(xwIgJBQGAx == true){xwIgJBQGAx = false;}
      if(SQiDltiHdp == true){SQiDltiHdp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VEKCOKOPCR
{ 
  void CtZIcDZyqJ()
  { 
      bool yIFNkyHmQs = false;
      bool DaCsOaKKEK = false;
      bool dGPdWmISaS = false;
      bool JjFykHPwjd = false;
      bool iXaEuXOcOl = false;
      bool RNWZOqrbpx = false;
      bool poLyiSVEHG = false;
      bool KNaabFfLhz = false;
      bool YeDnBwNeis = false;
      bool PnGmmtLbVb = false;
      bool CKUIbDmwyJ = false;
      bool LgsqXKkXxm = false;
      bool FpUOqWHmmh = false;
      bool tDpGxOKuMx = false;
      bool IRgZhiuOOc = false;
      bool JnehWLoGQE = false;
      bool uzIPOIqlsJ = false;
      bool AoKzdmIufI = false;
      bool brYKYFXHjk = false;
      bool ZDeHBJJQKY = false;
      string mmKfPigQpI;
      string kACqtdonQA;
      string yuYjqRnxkj;
      string zCnoDNiNVA;
      string pqgOxtGHoL;
      string ajGwFqNZnx;
      string ujeGIiLMmg;
      string tbSPKHOKmx;
      string KfHZIPurjM;
      string AIYXEFLaFO;
      string htUIQzQqkx;
      string cDmqmPcFys;
      string mSbaflCuKE;
      string wmEYOQKyIJ;
      string yEHlixVhjo;
      string cFbMaPRtbe;
      string wVffBoyNcW;
      string EdxouhLpqi;
      string PUKUbqLrxy;
      string zQVdNbYajs;
      if(mmKfPigQpI == htUIQzQqkx){yIFNkyHmQs = true;}
      else if(htUIQzQqkx == mmKfPigQpI){CKUIbDmwyJ = true;}
      if(kACqtdonQA == cDmqmPcFys){DaCsOaKKEK = true;}
      else if(cDmqmPcFys == kACqtdonQA){LgsqXKkXxm = true;}
      if(yuYjqRnxkj == mSbaflCuKE){dGPdWmISaS = true;}
      else if(mSbaflCuKE == yuYjqRnxkj){FpUOqWHmmh = true;}
      if(zCnoDNiNVA == wmEYOQKyIJ){JjFykHPwjd = true;}
      else if(wmEYOQKyIJ == zCnoDNiNVA){tDpGxOKuMx = true;}
      if(pqgOxtGHoL == yEHlixVhjo){iXaEuXOcOl = true;}
      else if(yEHlixVhjo == pqgOxtGHoL){IRgZhiuOOc = true;}
      if(ajGwFqNZnx == cFbMaPRtbe){RNWZOqrbpx = true;}
      else if(cFbMaPRtbe == ajGwFqNZnx){JnehWLoGQE = true;}
      if(ujeGIiLMmg == wVffBoyNcW){poLyiSVEHG = true;}
      else if(wVffBoyNcW == ujeGIiLMmg){uzIPOIqlsJ = true;}
      if(tbSPKHOKmx == EdxouhLpqi){KNaabFfLhz = true;}
      if(KfHZIPurjM == PUKUbqLrxy){YeDnBwNeis = true;}
      if(AIYXEFLaFO == zQVdNbYajs){PnGmmtLbVb = true;}
      while(EdxouhLpqi == tbSPKHOKmx){AoKzdmIufI = true;}
      while(PUKUbqLrxy == PUKUbqLrxy){brYKYFXHjk = true;}
      while(zQVdNbYajs == zQVdNbYajs){ZDeHBJJQKY = true;}
      if(yIFNkyHmQs == true){yIFNkyHmQs = false;}
      if(DaCsOaKKEK == true){DaCsOaKKEK = false;}
      if(dGPdWmISaS == true){dGPdWmISaS = false;}
      if(JjFykHPwjd == true){JjFykHPwjd = false;}
      if(iXaEuXOcOl == true){iXaEuXOcOl = false;}
      if(RNWZOqrbpx == true){RNWZOqrbpx = false;}
      if(poLyiSVEHG == true){poLyiSVEHG = false;}
      if(KNaabFfLhz == true){KNaabFfLhz = false;}
      if(YeDnBwNeis == true){YeDnBwNeis = false;}
      if(PnGmmtLbVb == true){PnGmmtLbVb = false;}
      if(CKUIbDmwyJ == true){CKUIbDmwyJ = false;}
      if(LgsqXKkXxm == true){LgsqXKkXxm = false;}
      if(FpUOqWHmmh == true){FpUOqWHmmh = false;}
      if(tDpGxOKuMx == true){tDpGxOKuMx = false;}
      if(IRgZhiuOOc == true){IRgZhiuOOc = false;}
      if(JnehWLoGQE == true){JnehWLoGQE = false;}
      if(uzIPOIqlsJ == true){uzIPOIqlsJ = false;}
      if(AoKzdmIufI == true){AoKzdmIufI = false;}
      if(brYKYFXHjk == true){brYKYFXHjk = false;}
      if(ZDeHBJJQKY == true){ZDeHBJJQKY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RPCUPBTYWT
{ 
  void BJtBRRuIyk()
  { 
      bool gWHWJwOsPp = false;
      bool BYJiQlyBnL = false;
      bool zwohhsNpic = false;
      bool CXBmfRuZQm = false;
      bool bcTlSTtaSm = false;
      bool ERpxNkgYnQ = false;
      bool hYKmndXWCy = false;
      bool qYjAjVbDPO = false;
      bool ymWuYjgEYu = false;
      bool kVlAFCRgyn = false;
      bool wXXTuegoMq = false;
      bool IdJZStBOND = false;
      bool wSxHMUljuh = false;
      bool EuFaRZODAs = false;
      bool CqqglHMLgK = false;
      bool ACStqcZQHa = false;
      bool rxtemNXhHr = false;
      bool fyOUAFbPVF = false;
      bool IaCkgBbKjo = false;
      bool AywYAFxLtX = false;
      string zNlZqmCIut;
      string umShmlhluE;
      string NHxPUEQxZK;
      string aWFDVnPmoq;
      string DiJrAoUHUE;
      string ulPbLqPVEm;
      string VFhkSXhOMy;
      string WtwEBexEPe;
      string iJbVOnHcrd;
      string XthBUxAYZb;
      string HGtVhApLag;
      string tKFYEMdMWd;
      string QEViZcLtiD;
      string dYenWcOFnN;
      string yuCLiMnJxH;
      string TnCuLDjKwE;
      string oubXCVfRBa;
      string xXYIfUCKAN;
      string nCwaipWjbT;
      string sEJiYCSdIN;
      if(zNlZqmCIut == HGtVhApLag){gWHWJwOsPp = true;}
      else if(HGtVhApLag == zNlZqmCIut){wXXTuegoMq = true;}
      if(umShmlhluE == tKFYEMdMWd){BYJiQlyBnL = true;}
      else if(tKFYEMdMWd == umShmlhluE){IdJZStBOND = true;}
      if(NHxPUEQxZK == QEViZcLtiD){zwohhsNpic = true;}
      else if(QEViZcLtiD == NHxPUEQxZK){wSxHMUljuh = true;}
      if(aWFDVnPmoq == dYenWcOFnN){CXBmfRuZQm = true;}
      else if(dYenWcOFnN == aWFDVnPmoq){EuFaRZODAs = true;}
      if(DiJrAoUHUE == yuCLiMnJxH){bcTlSTtaSm = true;}
      else if(yuCLiMnJxH == DiJrAoUHUE){CqqglHMLgK = true;}
      if(ulPbLqPVEm == TnCuLDjKwE){ERpxNkgYnQ = true;}
      else if(TnCuLDjKwE == ulPbLqPVEm){ACStqcZQHa = true;}
      if(VFhkSXhOMy == oubXCVfRBa){hYKmndXWCy = true;}
      else if(oubXCVfRBa == VFhkSXhOMy){rxtemNXhHr = true;}
      if(WtwEBexEPe == xXYIfUCKAN){qYjAjVbDPO = true;}
      if(iJbVOnHcrd == nCwaipWjbT){ymWuYjgEYu = true;}
      if(XthBUxAYZb == sEJiYCSdIN){kVlAFCRgyn = true;}
      while(xXYIfUCKAN == WtwEBexEPe){fyOUAFbPVF = true;}
      while(nCwaipWjbT == nCwaipWjbT){IaCkgBbKjo = true;}
      while(sEJiYCSdIN == sEJiYCSdIN){AywYAFxLtX = true;}
      if(gWHWJwOsPp == true){gWHWJwOsPp = false;}
      if(BYJiQlyBnL == true){BYJiQlyBnL = false;}
      if(zwohhsNpic == true){zwohhsNpic = false;}
      if(CXBmfRuZQm == true){CXBmfRuZQm = false;}
      if(bcTlSTtaSm == true){bcTlSTtaSm = false;}
      if(ERpxNkgYnQ == true){ERpxNkgYnQ = false;}
      if(hYKmndXWCy == true){hYKmndXWCy = false;}
      if(qYjAjVbDPO == true){qYjAjVbDPO = false;}
      if(ymWuYjgEYu == true){ymWuYjgEYu = false;}
      if(kVlAFCRgyn == true){kVlAFCRgyn = false;}
      if(wXXTuegoMq == true){wXXTuegoMq = false;}
      if(IdJZStBOND == true){IdJZStBOND = false;}
      if(wSxHMUljuh == true){wSxHMUljuh = false;}
      if(EuFaRZODAs == true){EuFaRZODAs = false;}
      if(CqqglHMLgK == true){CqqglHMLgK = false;}
      if(ACStqcZQHa == true){ACStqcZQHa = false;}
      if(rxtemNXhHr == true){rxtemNXhHr = false;}
      if(fyOUAFbPVF == true){fyOUAFbPVF = false;}
      if(IaCkgBbKjo == true){IaCkgBbKjo = false;}
      if(AywYAFxLtX == true){AywYAFxLtX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WCXZCUIDRB
{ 
  void ucFipQUyBj()
  { 
      bool HZfszZMTgh = false;
      bool eaDNFJcjta = false;
      bool rawBbwLJgG = false;
      bool fIgkPfJsmo = false;
      bool okPxKSWSkm = false;
      bool xlFfAgdeRC = false;
      bool ODlZCWsSxZ = false;
      bool zjxEkGKypI = false;
      bool ZrXsJsDBji = false;
      bool Bebjalypun = false;
      bool YEULnMnAtt = false;
      bool VfnIcVesPI = false;
      bool TrhOYTHMdz = false;
      bool HUDCiUWMEw = false;
      bool FCGpNUpTGE = false;
      bool GFZlUgVGmT = false;
      bool FbWtlAclYH = false;
      bool zSnTDQkrBD = false;
      bool dnGYsCtQhC = false;
      bool zQZkqceLDM = false;
      string QxrDILhgUB;
      string rPEaQuBQKD;
      string hnPABhUPBg;
      string VWzERxntUu;
      string tyLRCUlKIb;
      string VNwzbbgqCa;
      string qRemfVPzIS;
      string GHuOJibxxg;
      string uKHZLHazbo;
      string PxrtEbTYlf;
      string EmBoVORgpr;
      string AjtUegKFaX;
      string uQXTDJOBKg;
      string PDLRcIIRDx;
      string psIiofCXOX;
      string RNyOkmOhkM;
      string APWJcxXcqV;
      string XrBdgCHndX;
      string GpllOBExfp;
      string sagqxZVzGr;
      if(QxrDILhgUB == EmBoVORgpr){HZfszZMTgh = true;}
      else if(EmBoVORgpr == QxrDILhgUB){YEULnMnAtt = true;}
      if(rPEaQuBQKD == AjtUegKFaX){eaDNFJcjta = true;}
      else if(AjtUegKFaX == rPEaQuBQKD){VfnIcVesPI = true;}
      if(hnPABhUPBg == uQXTDJOBKg){rawBbwLJgG = true;}
      else if(uQXTDJOBKg == hnPABhUPBg){TrhOYTHMdz = true;}
      if(VWzERxntUu == PDLRcIIRDx){fIgkPfJsmo = true;}
      else if(PDLRcIIRDx == VWzERxntUu){HUDCiUWMEw = true;}
      if(tyLRCUlKIb == psIiofCXOX){okPxKSWSkm = true;}
      else if(psIiofCXOX == tyLRCUlKIb){FCGpNUpTGE = true;}
      if(VNwzbbgqCa == RNyOkmOhkM){xlFfAgdeRC = true;}
      else if(RNyOkmOhkM == VNwzbbgqCa){GFZlUgVGmT = true;}
      if(qRemfVPzIS == APWJcxXcqV){ODlZCWsSxZ = true;}
      else if(APWJcxXcqV == qRemfVPzIS){FbWtlAclYH = true;}
      if(GHuOJibxxg == XrBdgCHndX){zjxEkGKypI = true;}
      if(uKHZLHazbo == GpllOBExfp){ZrXsJsDBji = true;}
      if(PxrtEbTYlf == sagqxZVzGr){Bebjalypun = true;}
      while(XrBdgCHndX == GHuOJibxxg){zSnTDQkrBD = true;}
      while(GpllOBExfp == GpllOBExfp){dnGYsCtQhC = true;}
      while(sagqxZVzGr == sagqxZVzGr){zQZkqceLDM = true;}
      if(HZfszZMTgh == true){HZfszZMTgh = false;}
      if(eaDNFJcjta == true){eaDNFJcjta = false;}
      if(rawBbwLJgG == true){rawBbwLJgG = false;}
      if(fIgkPfJsmo == true){fIgkPfJsmo = false;}
      if(okPxKSWSkm == true){okPxKSWSkm = false;}
      if(xlFfAgdeRC == true){xlFfAgdeRC = false;}
      if(ODlZCWsSxZ == true){ODlZCWsSxZ = false;}
      if(zjxEkGKypI == true){zjxEkGKypI = false;}
      if(ZrXsJsDBji == true){ZrXsJsDBji = false;}
      if(Bebjalypun == true){Bebjalypun = false;}
      if(YEULnMnAtt == true){YEULnMnAtt = false;}
      if(VfnIcVesPI == true){VfnIcVesPI = false;}
      if(TrhOYTHMdz == true){TrhOYTHMdz = false;}
      if(HUDCiUWMEw == true){HUDCiUWMEw = false;}
      if(FCGpNUpTGE == true){FCGpNUpTGE = false;}
      if(GFZlUgVGmT == true){GFZlUgVGmT = false;}
      if(FbWtlAclYH == true){FbWtlAclYH = false;}
      if(zSnTDQkrBD == true){zSnTDQkrBD = false;}
      if(dnGYsCtQhC == true){dnGYsCtQhC = false;}
      if(zQZkqceLDM == true){zQZkqceLDM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HLRIXNVHSV
{ 
  void oXQFcVZjmf()
  { 
      bool SAdQREBeOe = false;
      bool QVBXLPmczc = false;
      bool LZtgHxzFWe = false;
      bool GjJaOQjTlJ = false;
      bool esrjmWhnGG = false;
      bool UxlgUrFwJT = false;
      bool EwHjYfLZJu = false;
      bool fSppyShJtj = false;
      bool PKyPJJxcFW = false;
      bool KnKSEikHLG = false;
      bool LHeLaCGwhB = false;
      bool KwCZEtxqZO = false;
      bool hhUmjrIXkP = false;
      bool gZxmXHfmnH = false;
      bool CBuELOkjOK = false;
      bool ksgxXcmrai = false;
      bool siKRTjzOBw = false;
      bool OKDSMgmPaV = false;
      bool GXJaensAOu = false;
      bool TmLFNSqcjb = false;
      string dBQrPWEziN;
      string cWXLmgiExH;
      string QidDSQYScg;
      string lzJzqOJPAV;
      string gQTxbUCALb;
      string ZeKRPtXNYy;
      string xlVBacMXUY;
      string XTEaZAOfax;
      string OXGBHHoqiw;
      string qwpBYutSWz;
      string HefmEGairP;
      string fqlajYeUtT;
      string mVnXgacCCd;
      string FwJbpirSwA;
      string fGzTQzJORz;
      string QZXCLlpIFc;
      string dXfNJjgJkA;
      string gMXsmgVUHg;
      string QNkDNfXHPD;
      string siMSWIZlKg;
      if(dBQrPWEziN == HefmEGairP){SAdQREBeOe = true;}
      else if(HefmEGairP == dBQrPWEziN){LHeLaCGwhB = true;}
      if(cWXLmgiExH == fqlajYeUtT){QVBXLPmczc = true;}
      else if(fqlajYeUtT == cWXLmgiExH){KwCZEtxqZO = true;}
      if(QidDSQYScg == mVnXgacCCd){LZtgHxzFWe = true;}
      else if(mVnXgacCCd == QidDSQYScg){hhUmjrIXkP = true;}
      if(lzJzqOJPAV == FwJbpirSwA){GjJaOQjTlJ = true;}
      else if(FwJbpirSwA == lzJzqOJPAV){gZxmXHfmnH = true;}
      if(gQTxbUCALb == fGzTQzJORz){esrjmWhnGG = true;}
      else if(fGzTQzJORz == gQTxbUCALb){CBuELOkjOK = true;}
      if(ZeKRPtXNYy == QZXCLlpIFc){UxlgUrFwJT = true;}
      else if(QZXCLlpIFc == ZeKRPtXNYy){ksgxXcmrai = true;}
      if(xlVBacMXUY == dXfNJjgJkA){EwHjYfLZJu = true;}
      else if(dXfNJjgJkA == xlVBacMXUY){siKRTjzOBw = true;}
      if(XTEaZAOfax == gMXsmgVUHg){fSppyShJtj = true;}
      if(OXGBHHoqiw == QNkDNfXHPD){PKyPJJxcFW = true;}
      if(qwpBYutSWz == siMSWIZlKg){KnKSEikHLG = true;}
      while(gMXsmgVUHg == XTEaZAOfax){OKDSMgmPaV = true;}
      while(QNkDNfXHPD == QNkDNfXHPD){GXJaensAOu = true;}
      while(siMSWIZlKg == siMSWIZlKg){TmLFNSqcjb = true;}
      if(SAdQREBeOe == true){SAdQREBeOe = false;}
      if(QVBXLPmczc == true){QVBXLPmczc = false;}
      if(LZtgHxzFWe == true){LZtgHxzFWe = false;}
      if(GjJaOQjTlJ == true){GjJaOQjTlJ = false;}
      if(esrjmWhnGG == true){esrjmWhnGG = false;}
      if(UxlgUrFwJT == true){UxlgUrFwJT = false;}
      if(EwHjYfLZJu == true){EwHjYfLZJu = false;}
      if(fSppyShJtj == true){fSppyShJtj = false;}
      if(PKyPJJxcFW == true){PKyPJJxcFW = false;}
      if(KnKSEikHLG == true){KnKSEikHLG = false;}
      if(LHeLaCGwhB == true){LHeLaCGwhB = false;}
      if(KwCZEtxqZO == true){KwCZEtxqZO = false;}
      if(hhUmjrIXkP == true){hhUmjrIXkP = false;}
      if(gZxmXHfmnH == true){gZxmXHfmnH = false;}
      if(CBuELOkjOK == true){CBuELOkjOK = false;}
      if(ksgxXcmrai == true){ksgxXcmrai = false;}
      if(siKRTjzOBw == true){siKRTjzOBw = false;}
      if(OKDSMgmPaV == true){OKDSMgmPaV = false;}
      if(GXJaensAOu == true){GXJaensAOu = false;}
      if(TmLFNSqcjb == true){TmLFNSqcjb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IRFWZJVKOP
{ 
  void cIAbciRglM()
  { 
      bool kwixdgWoRM = false;
      bool KKbbFtQwPk = false;
      bool mimsEBhtjY = false;
      bool rcPkAzjelm = false;
      bool UdWkkZCdbJ = false;
      bool uwrRxCIprb = false;
      bool zcFrThupbG = false;
      bool KlKbPJLCHe = false;
      bool zDRacukxnx = false;
      bool qslJnqYeQD = false;
      bool dLCVzJlPBm = false;
      bool pFhNcuKdOY = false;
      bool wyBdOQzAnX = false;
      bool jgkEAmBwbT = false;
      bool JUuAGkLXgr = false;
      bool gtPrGfJXGh = false;
      bool KkbdDJUcMo = false;
      bool tOCuPbCBWd = false;
      bool EaTuqpQsyU = false;
      bool dcosJXrRxx = false;
      string frfVGDiExp;
      string KxSsrYttHZ;
      string gspNbMIBhV;
      string hZFUiZgylO;
      string JfLDbNXUZV;
      string ASfoUmCSss;
      string uhWaHkqxJR;
      string quIsQAhmlN;
      string omaMVPsPzw;
      string XOErSbJjup;
      string WaKHdEJmYT;
      string FOgfEIGKFr;
      string raxNtcqQZo;
      string qyquqObShQ;
      string FGqeqIgXnK;
      string UzdDyucxNB;
      string MsMjcGWkop;
      string fmbnlkjRVk;
      string uScPUrTnxw;
      string kdFgDMsHCj;
      if(frfVGDiExp == WaKHdEJmYT){kwixdgWoRM = true;}
      else if(WaKHdEJmYT == frfVGDiExp){dLCVzJlPBm = true;}
      if(KxSsrYttHZ == FOgfEIGKFr){KKbbFtQwPk = true;}
      else if(FOgfEIGKFr == KxSsrYttHZ){pFhNcuKdOY = true;}
      if(gspNbMIBhV == raxNtcqQZo){mimsEBhtjY = true;}
      else if(raxNtcqQZo == gspNbMIBhV){wyBdOQzAnX = true;}
      if(hZFUiZgylO == qyquqObShQ){rcPkAzjelm = true;}
      else if(qyquqObShQ == hZFUiZgylO){jgkEAmBwbT = true;}
      if(JfLDbNXUZV == FGqeqIgXnK){UdWkkZCdbJ = true;}
      else if(FGqeqIgXnK == JfLDbNXUZV){JUuAGkLXgr = true;}
      if(ASfoUmCSss == UzdDyucxNB){uwrRxCIprb = true;}
      else if(UzdDyucxNB == ASfoUmCSss){gtPrGfJXGh = true;}
      if(uhWaHkqxJR == MsMjcGWkop){zcFrThupbG = true;}
      else if(MsMjcGWkop == uhWaHkqxJR){KkbdDJUcMo = true;}
      if(quIsQAhmlN == fmbnlkjRVk){KlKbPJLCHe = true;}
      if(omaMVPsPzw == uScPUrTnxw){zDRacukxnx = true;}
      if(XOErSbJjup == kdFgDMsHCj){qslJnqYeQD = true;}
      while(fmbnlkjRVk == quIsQAhmlN){tOCuPbCBWd = true;}
      while(uScPUrTnxw == uScPUrTnxw){EaTuqpQsyU = true;}
      while(kdFgDMsHCj == kdFgDMsHCj){dcosJXrRxx = true;}
      if(kwixdgWoRM == true){kwixdgWoRM = false;}
      if(KKbbFtQwPk == true){KKbbFtQwPk = false;}
      if(mimsEBhtjY == true){mimsEBhtjY = false;}
      if(rcPkAzjelm == true){rcPkAzjelm = false;}
      if(UdWkkZCdbJ == true){UdWkkZCdbJ = false;}
      if(uwrRxCIprb == true){uwrRxCIprb = false;}
      if(zcFrThupbG == true){zcFrThupbG = false;}
      if(KlKbPJLCHe == true){KlKbPJLCHe = false;}
      if(zDRacukxnx == true){zDRacukxnx = false;}
      if(qslJnqYeQD == true){qslJnqYeQD = false;}
      if(dLCVzJlPBm == true){dLCVzJlPBm = false;}
      if(pFhNcuKdOY == true){pFhNcuKdOY = false;}
      if(wyBdOQzAnX == true){wyBdOQzAnX = false;}
      if(jgkEAmBwbT == true){jgkEAmBwbT = false;}
      if(JUuAGkLXgr == true){JUuAGkLXgr = false;}
      if(gtPrGfJXGh == true){gtPrGfJXGh = false;}
      if(KkbdDJUcMo == true){KkbdDJUcMo = false;}
      if(tOCuPbCBWd == true){tOCuPbCBWd = false;}
      if(EaTuqpQsyU == true){EaTuqpQsyU = false;}
      if(dcosJXrRxx == true){dcosJXrRxx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SGFBDTOXQD
{ 
  void eskrqkMkfC()
  { 
      bool wMNADieFlS = false;
      bool VFqqsjoLtp = false;
      bool WbaZrEEMVo = false;
      bool SJzUMjZTDL = false;
      bool FYndJrjbOc = false;
      bool WBtsUTlmHz = false;
      bool eSjxAMGWeI = false;
      bool JVHijxnwQA = false;
      bool UbxrRQPFzr = false;
      bool xmLEgmoqcw = false;
      bool lMxGTBsKJW = false;
      bool foWHdCVqfj = false;
      bool xBXlKVJDCx = false;
      bool IxTTOHdpXP = false;
      bool XEubMIPEZd = false;
      bool QxKszkoLux = false;
      bool qpIMOiVCrW = false;
      bool XeSPLrFuZC = false;
      bool GFcXfLlZTd = false;
      bool RSuaYguiNc = false;
      string LuyuQUgfLH;
      string BOHYgUHtqZ;
      string SRDWsURKma;
      string qwQoGIgaPA;
      string WNqbQuAbgO;
      string LzDtRtraCw;
      string CWsjPFyRRY;
      string nfdpDFZaGx;
      string TpcYPqsVXM;
      string QFYSxATHMK;
      string xhJIZeUMqM;
      string TQTFbMsTTX;
      string MctFHiHLrC;
      string kSOwAlfUzk;
      string WgdKszkSqk;
      string HAnnyUnEAq;
      string XJToaACXFp;
      string gYUiBeyiMI;
      string xnTHtkdZxe;
      string xbTIMMMnjr;
      if(LuyuQUgfLH == xhJIZeUMqM){wMNADieFlS = true;}
      else if(xhJIZeUMqM == LuyuQUgfLH){lMxGTBsKJW = true;}
      if(BOHYgUHtqZ == TQTFbMsTTX){VFqqsjoLtp = true;}
      else if(TQTFbMsTTX == BOHYgUHtqZ){foWHdCVqfj = true;}
      if(SRDWsURKma == MctFHiHLrC){WbaZrEEMVo = true;}
      else if(MctFHiHLrC == SRDWsURKma){xBXlKVJDCx = true;}
      if(qwQoGIgaPA == kSOwAlfUzk){SJzUMjZTDL = true;}
      else if(kSOwAlfUzk == qwQoGIgaPA){IxTTOHdpXP = true;}
      if(WNqbQuAbgO == WgdKszkSqk){FYndJrjbOc = true;}
      else if(WgdKszkSqk == WNqbQuAbgO){XEubMIPEZd = true;}
      if(LzDtRtraCw == HAnnyUnEAq){WBtsUTlmHz = true;}
      else if(HAnnyUnEAq == LzDtRtraCw){QxKszkoLux = true;}
      if(CWsjPFyRRY == XJToaACXFp){eSjxAMGWeI = true;}
      else if(XJToaACXFp == CWsjPFyRRY){qpIMOiVCrW = true;}
      if(nfdpDFZaGx == gYUiBeyiMI){JVHijxnwQA = true;}
      if(TpcYPqsVXM == xnTHtkdZxe){UbxrRQPFzr = true;}
      if(QFYSxATHMK == xbTIMMMnjr){xmLEgmoqcw = true;}
      while(gYUiBeyiMI == nfdpDFZaGx){XeSPLrFuZC = true;}
      while(xnTHtkdZxe == xnTHtkdZxe){GFcXfLlZTd = true;}
      while(xbTIMMMnjr == xbTIMMMnjr){RSuaYguiNc = true;}
      if(wMNADieFlS == true){wMNADieFlS = false;}
      if(VFqqsjoLtp == true){VFqqsjoLtp = false;}
      if(WbaZrEEMVo == true){WbaZrEEMVo = false;}
      if(SJzUMjZTDL == true){SJzUMjZTDL = false;}
      if(FYndJrjbOc == true){FYndJrjbOc = false;}
      if(WBtsUTlmHz == true){WBtsUTlmHz = false;}
      if(eSjxAMGWeI == true){eSjxAMGWeI = false;}
      if(JVHijxnwQA == true){JVHijxnwQA = false;}
      if(UbxrRQPFzr == true){UbxrRQPFzr = false;}
      if(xmLEgmoqcw == true){xmLEgmoqcw = false;}
      if(lMxGTBsKJW == true){lMxGTBsKJW = false;}
      if(foWHdCVqfj == true){foWHdCVqfj = false;}
      if(xBXlKVJDCx == true){xBXlKVJDCx = false;}
      if(IxTTOHdpXP == true){IxTTOHdpXP = false;}
      if(XEubMIPEZd == true){XEubMIPEZd = false;}
      if(QxKszkoLux == true){QxKszkoLux = false;}
      if(qpIMOiVCrW == true){qpIMOiVCrW = false;}
      if(XeSPLrFuZC == true){XeSPLrFuZC = false;}
      if(GFcXfLlZTd == true){GFcXfLlZTd = false;}
      if(RSuaYguiNc == true){RSuaYguiNc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPBQPDQJSJ
{ 
  void OolPMFqqXK()
  { 
      bool PWGEhdABzt = false;
      bool CfZNGrgMrP = false;
      bool oUOjhPGPYF = false;
      bool chlTBIuVOS = false;
      bool dDjffyHNcC = false;
      bool cHGzytHVWS = false;
      bool WjcsRUsGLx = false;
      bool xKxZlljiDi = false;
      bool HsmWcValVG = false;
      bool BYywusapOL = false;
      bool EBBeERJgNL = false;
      bool KYSmKdxGQu = false;
      bool sHjFwYLBdr = false;
      bool KsTqeGrHRK = false;
      bool MtXJwbFKkR = false;
      bool wUZSSxQuif = false;
      bool GHDUAQEaID = false;
      bool lonGiziaJT = false;
      bool SAQMwpTAYg = false;
      bool pwYlDEpDIe = false;
      string hkuRUzzVlu;
      string PFxcbfSBEM;
      string wEmzzqDrxS;
      string xWsFhUReTl;
      string GuysMVkRWt;
      string IgFFXcxuRd;
      string wHYSxsLrtH;
      string OngSGAGtmd;
      string FkUCJQRngE;
      string WVMopyWeuT;
      string JsWPfUzmyX;
      string VDImYKmVJg;
      string bXKpksarcI;
      string daySUMOFWo;
      string QdoJhTMYQe;
      string LAVOrkhgdm;
      string tHKpsuEpSL;
      string wgzTPxhBHQ;
      string fBaxxdFjai;
      string dgajuJTzPm;
      if(hkuRUzzVlu == JsWPfUzmyX){PWGEhdABzt = true;}
      else if(JsWPfUzmyX == hkuRUzzVlu){EBBeERJgNL = true;}
      if(PFxcbfSBEM == VDImYKmVJg){CfZNGrgMrP = true;}
      else if(VDImYKmVJg == PFxcbfSBEM){KYSmKdxGQu = true;}
      if(wEmzzqDrxS == bXKpksarcI){oUOjhPGPYF = true;}
      else if(bXKpksarcI == wEmzzqDrxS){sHjFwYLBdr = true;}
      if(xWsFhUReTl == daySUMOFWo){chlTBIuVOS = true;}
      else if(daySUMOFWo == xWsFhUReTl){KsTqeGrHRK = true;}
      if(GuysMVkRWt == QdoJhTMYQe){dDjffyHNcC = true;}
      else if(QdoJhTMYQe == GuysMVkRWt){MtXJwbFKkR = true;}
      if(IgFFXcxuRd == LAVOrkhgdm){cHGzytHVWS = true;}
      else if(LAVOrkhgdm == IgFFXcxuRd){wUZSSxQuif = true;}
      if(wHYSxsLrtH == tHKpsuEpSL){WjcsRUsGLx = true;}
      else if(tHKpsuEpSL == wHYSxsLrtH){GHDUAQEaID = true;}
      if(OngSGAGtmd == wgzTPxhBHQ){xKxZlljiDi = true;}
      if(FkUCJQRngE == fBaxxdFjai){HsmWcValVG = true;}
      if(WVMopyWeuT == dgajuJTzPm){BYywusapOL = true;}
      while(wgzTPxhBHQ == OngSGAGtmd){lonGiziaJT = true;}
      while(fBaxxdFjai == fBaxxdFjai){SAQMwpTAYg = true;}
      while(dgajuJTzPm == dgajuJTzPm){pwYlDEpDIe = true;}
      if(PWGEhdABzt == true){PWGEhdABzt = false;}
      if(CfZNGrgMrP == true){CfZNGrgMrP = false;}
      if(oUOjhPGPYF == true){oUOjhPGPYF = false;}
      if(chlTBIuVOS == true){chlTBIuVOS = false;}
      if(dDjffyHNcC == true){dDjffyHNcC = false;}
      if(cHGzytHVWS == true){cHGzytHVWS = false;}
      if(WjcsRUsGLx == true){WjcsRUsGLx = false;}
      if(xKxZlljiDi == true){xKxZlljiDi = false;}
      if(HsmWcValVG == true){HsmWcValVG = false;}
      if(BYywusapOL == true){BYywusapOL = false;}
      if(EBBeERJgNL == true){EBBeERJgNL = false;}
      if(KYSmKdxGQu == true){KYSmKdxGQu = false;}
      if(sHjFwYLBdr == true){sHjFwYLBdr = false;}
      if(KsTqeGrHRK == true){KsTqeGrHRK = false;}
      if(MtXJwbFKkR == true){MtXJwbFKkR = false;}
      if(wUZSSxQuif == true){wUZSSxQuif = false;}
      if(GHDUAQEaID == true){GHDUAQEaID = false;}
      if(lonGiziaJT == true){lonGiziaJT = false;}
      if(SAQMwpTAYg == true){SAQMwpTAYg = false;}
      if(pwYlDEpDIe == true){pwYlDEpDIe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OJUBVXQNIB
{ 
  void MompYKMVyQ()
  { 
      bool qhAIOYyDPC = false;
      bool IntyyiIEaH = false;
      bool NxTrOcVGrG = false;
      bool blLeptiVFD = false;
      bool qTNokekfxw = false;
      bool DrzhitOHtk = false;
      bool DrKJaWcPHE = false;
      bool zmyWPsieGj = false;
      bool rpIwCilcww = false;
      bool eaaUAyJENO = false;
      bool BVXswQtbRo = false;
      bool KiAKsNiOHr = false;
      bool kATKYYLdWR = false;
      bool jeRrhVRPzk = false;
      bool nJKGluaQam = false;
      bool OuxUcBBMTX = false;
      bool FPFAFfRIcW = false;
      bool uTOVDaoMYc = false;
      bool ytDiCogwOf = false;
      bool TFubfYEJBF = false;
      string TtRBJbjEsC;
      string KHoSRpnXub;
      string grqwTdlgMn;
      string abebrJtYQW;
      string oQzcFppFnr;
      string DRosCbCVhf;
      string pDrFbhcMZH;
      string uOHXmPrOpd;
      string mfrTkJmkYQ;
      string GYqkgkYtBW;
      string NcegxnJQGm;
      string ineDrJLYTS;
      string uqmJAWWWqC;
      string pyMTQJBLWw;
      string zWelhStmrW;
      string YAaibVpVfa;
      string RmYEwkaLmi;
      string IACWSYMBah;
      string bieUcoWdqt;
      string TeeueMxaow;
      if(TtRBJbjEsC == NcegxnJQGm){qhAIOYyDPC = true;}
      else if(NcegxnJQGm == TtRBJbjEsC){BVXswQtbRo = true;}
      if(KHoSRpnXub == ineDrJLYTS){IntyyiIEaH = true;}
      else if(ineDrJLYTS == KHoSRpnXub){KiAKsNiOHr = true;}
      if(grqwTdlgMn == uqmJAWWWqC){NxTrOcVGrG = true;}
      else if(uqmJAWWWqC == grqwTdlgMn){kATKYYLdWR = true;}
      if(abebrJtYQW == pyMTQJBLWw){blLeptiVFD = true;}
      else if(pyMTQJBLWw == abebrJtYQW){jeRrhVRPzk = true;}
      if(oQzcFppFnr == zWelhStmrW){qTNokekfxw = true;}
      else if(zWelhStmrW == oQzcFppFnr){nJKGluaQam = true;}
      if(DRosCbCVhf == YAaibVpVfa){DrzhitOHtk = true;}
      else if(YAaibVpVfa == DRosCbCVhf){OuxUcBBMTX = true;}
      if(pDrFbhcMZH == RmYEwkaLmi){DrKJaWcPHE = true;}
      else if(RmYEwkaLmi == pDrFbhcMZH){FPFAFfRIcW = true;}
      if(uOHXmPrOpd == IACWSYMBah){zmyWPsieGj = true;}
      if(mfrTkJmkYQ == bieUcoWdqt){rpIwCilcww = true;}
      if(GYqkgkYtBW == TeeueMxaow){eaaUAyJENO = true;}
      while(IACWSYMBah == uOHXmPrOpd){uTOVDaoMYc = true;}
      while(bieUcoWdqt == bieUcoWdqt){ytDiCogwOf = true;}
      while(TeeueMxaow == TeeueMxaow){TFubfYEJBF = true;}
      if(qhAIOYyDPC == true){qhAIOYyDPC = false;}
      if(IntyyiIEaH == true){IntyyiIEaH = false;}
      if(NxTrOcVGrG == true){NxTrOcVGrG = false;}
      if(blLeptiVFD == true){blLeptiVFD = false;}
      if(qTNokekfxw == true){qTNokekfxw = false;}
      if(DrzhitOHtk == true){DrzhitOHtk = false;}
      if(DrKJaWcPHE == true){DrKJaWcPHE = false;}
      if(zmyWPsieGj == true){zmyWPsieGj = false;}
      if(rpIwCilcww == true){rpIwCilcww = false;}
      if(eaaUAyJENO == true){eaaUAyJENO = false;}
      if(BVXswQtbRo == true){BVXswQtbRo = false;}
      if(KiAKsNiOHr == true){KiAKsNiOHr = false;}
      if(kATKYYLdWR == true){kATKYYLdWR = false;}
      if(jeRrhVRPzk == true){jeRrhVRPzk = false;}
      if(nJKGluaQam == true){nJKGluaQam = false;}
      if(OuxUcBBMTX == true){OuxUcBBMTX = false;}
      if(FPFAFfRIcW == true){FPFAFfRIcW = false;}
      if(uTOVDaoMYc == true){uTOVDaoMYc = false;}
      if(ytDiCogwOf == true){ytDiCogwOf = false;}
      if(TFubfYEJBF == true){TFubfYEJBF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWFUGHDNRI
{ 
  void xnpwZnAKQe()
  { 
      bool xCZdkGYRoS = false;
      bool hzxSMwVSIc = false;
      bool ClHBamSMTT = false;
      bool CJRZFArnCp = false;
      bool AGknaHnHld = false;
      bool KhiXBLtYCx = false;
      bool nMyUPYhWML = false;
      bool EgQRcuATZS = false;
      bool zKZoJUatYs = false;
      bool GTlECmIQXC = false;
      bool ZQtZZcRQtF = false;
      bool LZyjyclILu = false;
      bool xnySFjuLPo = false;
      bool mjwWrhQAOf = false;
      bool CKzShgUBFZ = false;
      bool BzEbElSaUo = false;
      bool gGAESbcbqQ = false;
      bool LlsesmnekX = false;
      bool PsFpnmeURG = false;
      bool OoeZzwJtAG = false;
      string MNaYyAedPT;
      string dRaWywKiSi;
      string tWETwfVNJU;
      string HHaqcxRRkZ;
      string CcqZFWVbjN;
      string LRwfcpIHcR;
      string eQUtMWqisB;
      string dryrfRfeNY;
      string KtdwJoKuOm;
      string nKoSukIwNi;
      string flhiiSTDzL;
      string JdsEGkmXkW;
      string LwUGNTDext;
      string JiRdsYLuNp;
      string VHuCcKQkMJ;
      string yjLpWiRaUO;
      string PoGECZMOKh;
      string YrKtBEARdC;
      string CSSmwYXaGJ;
      string HkZyagBqAD;
      if(MNaYyAedPT == flhiiSTDzL){xCZdkGYRoS = true;}
      else if(flhiiSTDzL == MNaYyAedPT){ZQtZZcRQtF = true;}
      if(dRaWywKiSi == JdsEGkmXkW){hzxSMwVSIc = true;}
      else if(JdsEGkmXkW == dRaWywKiSi){LZyjyclILu = true;}
      if(tWETwfVNJU == LwUGNTDext){ClHBamSMTT = true;}
      else if(LwUGNTDext == tWETwfVNJU){xnySFjuLPo = true;}
      if(HHaqcxRRkZ == JiRdsYLuNp){CJRZFArnCp = true;}
      else if(JiRdsYLuNp == HHaqcxRRkZ){mjwWrhQAOf = true;}
      if(CcqZFWVbjN == VHuCcKQkMJ){AGknaHnHld = true;}
      else if(VHuCcKQkMJ == CcqZFWVbjN){CKzShgUBFZ = true;}
      if(LRwfcpIHcR == yjLpWiRaUO){KhiXBLtYCx = true;}
      else if(yjLpWiRaUO == LRwfcpIHcR){BzEbElSaUo = true;}
      if(eQUtMWqisB == PoGECZMOKh){nMyUPYhWML = true;}
      else if(PoGECZMOKh == eQUtMWqisB){gGAESbcbqQ = true;}
      if(dryrfRfeNY == YrKtBEARdC){EgQRcuATZS = true;}
      if(KtdwJoKuOm == CSSmwYXaGJ){zKZoJUatYs = true;}
      if(nKoSukIwNi == HkZyagBqAD){GTlECmIQXC = true;}
      while(YrKtBEARdC == dryrfRfeNY){LlsesmnekX = true;}
      while(CSSmwYXaGJ == CSSmwYXaGJ){PsFpnmeURG = true;}
      while(HkZyagBqAD == HkZyagBqAD){OoeZzwJtAG = true;}
      if(xCZdkGYRoS == true){xCZdkGYRoS = false;}
      if(hzxSMwVSIc == true){hzxSMwVSIc = false;}
      if(ClHBamSMTT == true){ClHBamSMTT = false;}
      if(CJRZFArnCp == true){CJRZFArnCp = false;}
      if(AGknaHnHld == true){AGknaHnHld = false;}
      if(KhiXBLtYCx == true){KhiXBLtYCx = false;}
      if(nMyUPYhWML == true){nMyUPYhWML = false;}
      if(EgQRcuATZS == true){EgQRcuATZS = false;}
      if(zKZoJUatYs == true){zKZoJUatYs = false;}
      if(GTlECmIQXC == true){GTlECmIQXC = false;}
      if(ZQtZZcRQtF == true){ZQtZZcRQtF = false;}
      if(LZyjyclILu == true){LZyjyclILu = false;}
      if(xnySFjuLPo == true){xnySFjuLPo = false;}
      if(mjwWrhQAOf == true){mjwWrhQAOf = false;}
      if(CKzShgUBFZ == true){CKzShgUBFZ = false;}
      if(BzEbElSaUo == true){BzEbElSaUo = false;}
      if(gGAESbcbqQ == true){gGAESbcbqQ = false;}
      if(LlsesmnekX == true){LlsesmnekX = false;}
      if(PsFpnmeURG == true){PsFpnmeURG = false;}
      if(OoeZzwJtAG == true){OoeZzwJtAG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RCAILRHPZR
{ 
  void sxBiTLGJiH()
  { 
      bool onmSLKitNm = false;
      bool AtibrcTJUS = false;
      bool zyBxyTKmDO = false;
      bool JglmTWrQLm = false;
      bool EJCCHcFmeQ = false;
      bool eXYifploTq = false;
      bool AuqzdSHuIV = false;
      bool jDyhNpuyoV = false;
      bool NWIljkIDGc = false;
      bool jDwTmJSCYn = false;
      bool UJeJfbYqUo = false;
      bool umzycdlEPs = false;
      bool KEofkgGeuE = false;
      bool XrZBBDqyGH = false;
      bool LRiQgwDyqJ = false;
      bool WNmfcPUzXy = false;
      bool UtuQRCMywY = false;
      bool lmyHgsVXyn = false;
      bool dInlgJFtXl = false;
      bool iraHmQVRze = false;
      string CGNqPfpDKr;
      string SDmGUBWSae;
      string yQRqGEkQyY;
      string yXFwUyQQbO;
      string kkcjhKUpSd;
      string nSjtAlnWjL;
      string tYFktuyqlV;
      string kFpLsMmhIu;
      string iuxTkenLui;
      string JtgQTLfqpm;
      string MdExshcXAm;
      string zGNnbzakAO;
      string HluCLpYYqh;
      string guqViFpAZD;
      string CPLHjDfroU;
      string jtqaeahBkC;
      string JDgRFDOrFV;
      string IZLxMrZnSI;
      string KfjWxmDQpH;
      string WoPXtyhsBf;
      if(CGNqPfpDKr == MdExshcXAm){onmSLKitNm = true;}
      else if(MdExshcXAm == CGNqPfpDKr){UJeJfbYqUo = true;}
      if(SDmGUBWSae == zGNnbzakAO){AtibrcTJUS = true;}
      else if(zGNnbzakAO == SDmGUBWSae){umzycdlEPs = true;}
      if(yQRqGEkQyY == HluCLpYYqh){zyBxyTKmDO = true;}
      else if(HluCLpYYqh == yQRqGEkQyY){KEofkgGeuE = true;}
      if(yXFwUyQQbO == guqViFpAZD){JglmTWrQLm = true;}
      else if(guqViFpAZD == yXFwUyQQbO){XrZBBDqyGH = true;}
      if(kkcjhKUpSd == CPLHjDfroU){EJCCHcFmeQ = true;}
      else if(CPLHjDfroU == kkcjhKUpSd){LRiQgwDyqJ = true;}
      if(nSjtAlnWjL == jtqaeahBkC){eXYifploTq = true;}
      else if(jtqaeahBkC == nSjtAlnWjL){WNmfcPUzXy = true;}
      if(tYFktuyqlV == JDgRFDOrFV){AuqzdSHuIV = true;}
      else if(JDgRFDOrFV == tYFktuyqlV){UtuQRCMywY = true;}
      if(kFpLsMmhIu == IZLxMrZnSI){jDyhNpuyoV = true;}
      if(iuxTkenLui == KfjWxmDQpH){NWIljkIDGc = true;}
      if(JtgQTLfqpm == WoPXtyhsBf){jDwTmJSCYn = true;}
      while(IZLxMrZnSI == kFpLsMmhIu){lmyHgsVXyn = true;}
      while(KfjWxmDQpH == KfjWxmDQpH){dInlgJFtXl = true;}
      while(WoPXtyhsBf == WoPXtyhsBf){iraHmQVRze = true;}
      if(onmSLKitNm == true){onmSLKitNm = false;}
      if(AtibrcTJUS == true){AtibrcTJUS = false;}
      if(zyBxyTKmDO == true){zyBxyTKmDO = false;}
      if(JglmTWrQLm == true){JglmTWrQLm = false;}
      if(EJCCHcFmeQ == true){EJCCHcFmeQ = false;}
      if(eXYifploTq == true){eXYifploTq = false;}
      if(AuqzdSHuIV == true){AuqzdSHuIV = false;}
      if(jDyhNpuyoV == true){jDyhNpuyoV = false;}
      if(NWIljkIDGc == true){NWIljkIDGc = false;}
      if(jDwTmJSCYn == true){jDwTmJSCYn = false;}
      if(UJeJfbYqUo == true){UJeJfbYqUo = false;}
      if(umzycdlEPs == true){umzycdlEPs = false;}
      if(KEofkgGeuE == true){KEofkgGeuE = false;}
      if(XrZBBDqyGH == true){XrZBBDqyGH = false;}
      if(LRiQgwDyqJ == true){LRiQgwDyqJ = false;}
      if(WNmfcPUzXy == true){WNmfcPUzXy = false;}
      if(UtuQRCMywY == true){UtuQRCMywY = false;}
      if(lmyHgsVXyn == true){lmyHgsVXyn = false;}
      if(dInlgJFtXl == true){dInlgJFtXl = false;}
      if(iraHmQVRze == true){iraHmQVRze = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SFDKKKFSRL
{ 
  void jOHlWlAgpY()
  { 
      bool fzVelFHLIU = false;
      bool iWKFuUkdeI = false;
      bool YrmLqYYlxX = false;
      bool jxjEDgOkGb = false;
      bool aBGcKtHWRm = false;
      bool icgWbmLKmM = false;
      bool fUNjkllGCO = false;
      bool GzWDhWlKAx = false;
      bool RCTKoGQNbP = false;
      bool VExtwFnVrY = false;
      bool HBTDgiFcnF = false;
      bool BBJptdADud = false;
      bool UXdmrBCcGb = false;
      bool iPRaoQhQdF = false;
      bool AmYWNTtHzR = false;
      bool FkaNEiWgKe = false;
      bool gcWMWliiAd = false;
      bool wjYodgzHZX = false;
      bool HtcoWxoEWG = false;
      bool sAFzYWQMza = false;
      string kBTVZWPGhh;
      string nNHjzdPnBo;
      string IDuZJnCTfg;
      string nszTlRchkZ;
      string WWlLerMIrw;
      string AJUVRhGsLl;
      string UuZAtuNnyg;
      string BhDbRlQiuR;
      string asbjgdXdCE;
      string KiVyEawkRj;
      string dXKKtRGsDf;
      string QXxtKaToTP;
      string WjlsVRMEWp;
      string oeQLnCiRpO;
      string WeZVmmkbmd;
      string HGRBMslQnb;
      string FCWNplHlFI;
      string rCzFsrJPFi;
      string fkQrhhNOyt;
      string QScNIUHLeB;
      if(kBTVZWPGhh == dXKKtRGsDf){fzVelFHLIU = true;}
      else if(dXKKtRGsDf == kBTVZWPGhh){HBTDgiFcnF = true;}
      if(nNHjzdPnBo == QXxtKaToTP){iWKFuUkdeI = true;}
      else if(QXxtKaToTP == nNHjzdPnBo){BBJptdADud = true;}
      if(IDuZJnCTfg == WjlsVRMEWp){YrmLqYYlxX = true;}
      else if(WjlsVRMEWp == IDuZJnCTfg){UXdmrBCcGb = true;}
      if(nszTlRchkZ == oeQLnCiRpO){jxjEDgOkGb = true;}
      else if(oeQLnCiRpO == nszTlRchkZ){iPRaoQhQdF = true;}
      if(WWlLerMIrw == WeZVmmkbmd){aBGcKtHWRm = true;}
      else if(WeZVmmkbmd == WWlLerMIrw){AmYWNTtHzR = true;}
      if(AJUVRhGsLl == HGRBMslQnb){icgWbmLKmM = true;}
      else if(HGRBMslQnb == AJUVRhGsLl){FkaNEiWgKe = true;}
      if(UuZAtuNnyg == FCWNplHlFI){fUNjkllGCO = true;}
      else if(FCWNplHlFI == UuZAtuNnyg){gcWMWliiAd = true;}
      if(BhDbRlQiuR == rCzFsrJPFi){GzWDhWlKAx = true;}
      if(asbjgdXdCE == fkQrhhNOyt){RCTKoGQNbP = true;}
      if(KiVyEawkRj == QScNIUHLeB){VExtwFnVrY = true;}
      while(rCzFsrJPFi == BhDbRlQiuR){wjYodgzHZX = true;}
      while(fkQrhhNOyt == fkQrhhNOyt){HtcoWxoEWG = true;}
      while(QScNIUHLeB == QScNIUHLeB){sAFzYWQMza = true;}
      if(fzVelFHLIU == true){fzVelFHLIU = false;}
      if(iWKFuUkdeI == true){iWKFuUkdeI = false;}
      if(YrmLqYYlxX == true){YrmLqYYlxX = false;}
      if(jxjEDgOkGb == true){jxjEDgOkGb = false;}
      if(aBGcKtHWRm == true){aBGcKtHWRm = false;}
      if(icgWbmLKmM == true){icgWbmLKmM = false;}
      if(fUNjkllGCO == true){fUNjkllGCO = false;}
      if(GzWDhWlKAx == true){GzWDhWlKAx = false;}
      if(RCTKoGQNbP == true){RCTKoGQNbP = false;}
      if(VExtwFnVrY == true){VExtwFnVrY = false;}
      if(HBTDgiFcnF == true){HBTDgiFcnF = false;}
      if(BBJptdADud == true){BBJptdADud = false;}
      if(UXdmrBCcGb == true){UXdmrBCcGb = false;}
      if(iPRaoQhQdF == true){iPRaoQhQdF = false;}
      if(AmYWNTtHzR == true){AmYWNTtHzR = false;}
      if(FkaNEiWgKe == true){FkaNEiWgKe = false;}
      if(gcWMWliiAd == true){gcWMWliiAd = false;}
      if(wjYodgzHZX == true){wjYodgzHZX = false;}
      if(HtcoWxoEWG == true){HtcoWxoEWG = false;}
      if(sAFzYWQMza == true){sAFzYWQMza = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SNINUKCBSS
{ 
  void FufzoomNbV()
  { 
      bool ubTcLfPQFq = false;
      bool kGABBAQEPp = false;
      bool fgtoCwIjPi = false;
      bool oRQyYhwZEm = false;
      bool pmFiFthVau = false;
      bool gPlRSOhdaO = false;
      bool WfAWCSoBcT = false;
      bool DpzcAraKjH = false;
      bool OmJUBYfzfK = false;
      bool ARzpPKmhgl = false;
      bool FfsHqqPIRZ = false;
      bool mWtSzjVfUc = false;
      bool lpURSlqJNo = false;
      bool FsdxCitCdK = false;
      bool JWgFWdWgqf = false;
      bool oHMDzOKanE = false;
      bool zGucTtrwPQ = false;
      bool oTBKTPJPto = false;
      bool OJShAyfZxm = false;
      bool XTNZKCbEkc = false;
      string jWSMDunpaD;
      string MsCcpWCAdH;
      string EourcYYneN;
      string fxkiuEULxW;
      string npLKPUeNPV;
      string WIhjutaZje;
      string VzKNXOIShk;
      string CqDGTOdkcI;
      string sLYIqXPBmA;
      string ctaSAneymA;
      string MMedTfEaPg;
      string QpxbkKaBVz;
      string zGfgHHPkGf;
      string jfybwgftoL;
      string SolFjmxzgp;
      string McbmBFfyWM;
      string PTUixjrUfD;
      string egMKgJUZxU;
      string KPDPSGEKap;
      string BhXcuyUCIz;
      if(jWSMDunpaD == MMedTfEaPg){ubTcLfPQFq = true;}
      else if(MMedTfEaPg == jWSMDunpaD){FfsHqqPIRZ = true;}
      if(MsCcpWCAdH == QpxbkKaBVz){kGABBAQEPp = true;}
      else if(QpxbkKaBVz == MsCcpWCAdH){mWtSzjVfUc = true;}
      if(EourcYYneN == zGfgHHPkGf){fgtoCwIjPi = true;}
      else if(zGfgHHPkGf == EourcYYneN){lpURSlqJNo = true;}
      if(fxkiuEULxW == jfybwgftoL){oRQyYhwZEm = true;}
      else if(jfybwgftoL == fxkiuEULxW){FsdxCitCdK = true;}
      if(npLKPUeNPV == SolFjmxzgp){pmFiFthVau = true;}
      else if(SolFjmxzgp == npLKPUeNPV){JWgFWdWgqf = true;}
      if(WIhjutaZje == McbmBFfyWM){gPlRSOhdaO = true;}
      else if(McbmBFfyWM == WIhjutaZje){oHMDzOKanE = true;}
      if(VzKNXOIShk == PTUixjrUfD){WfAWCSoBcT = true;}
      else if(PTUixjrUfD == VzKNXOIShk){zGucTtrwPQ = true;}
      if(CqDGTOdkcI == egMKgJUZxU){DpzcAraKjH = true;}
      if(sLYIqXPBmA == KPDPSGEKap){OmJUBYfzfK = true;}
      if(ctaSAneymA == BhXcuyUCIz){ARzpPKmhgl = true;}
      while(egMKgJUZxU == CqDGTOdkcI){oTBKTPJPto = true;}
      while(KPDPSGEKap == KPDPSGEKap){OJShAyfZxm = true;}
      while(BhXcuyUCIz == BhXcuyUCIz){XTNZKCbEkc = true;}
      if(ubTcLfPQFq == true){ubTcLfPQFq = false;}
      if(kGABBAQEPp == true){kGABBAQEPp = false;}
      if(fgtoCwIjPi == true){fgtoCwIjPi = false;}
      if(oRQyYhwZEm == true){oRQyYhwZEm = false;}
      if(pmFiFthVau == true){pmFiFthVau = false;}
      if(gPlRSOhdaO == true){gPlRSOhdaO = false;}
      if(WfAWCSoBcT == true){WfAWCSoBcT = false;}
      if(DpzcAraKjH == true){DpzcAraKjH = false;}
      if(OmJUBYfzfK == true){OmJUBYfzfK = false;}
      if(ARzpPKmhgl == true){ARzpPKmhgl = false;}
      if(FfsHqqPIRZ == true){FfsHqqPIRZ = false;}
      if(mWtSzjVfUc == true){mWtSzjVfUc = false;}
      if(lpURSlqJNo == true){lpURSlqJNo = false;}
      if(FsdxCitCdK == true){FsdxCitCdK = false;}
      if(JWgFWdWgqf == true){JWgFWdWgqf = false;}
      if(oHMDzOKanE == true){oHMDzOKanE = false;}
      if(zGucTtrwPQ == true){zGucTtrwPQ = false;}
      if(oTBKTPJPto == true){oTBKTPJPto = false;}
      if(OJShAyfZxm == true){OJShAyfZxm = false;}
      if(XTNZKCbEkc == true){XTNZKCbEkc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BHBXQDNTVZ
{ 
  void RDaHGUWhrS()
  { 
      bool HWzlmQJXnR = false;
      bool GSkaDZUojV = false;
      bool jTpactFkne = false;
      bool YPRzUufFsY = false;
      bool srkPqpxHtG = false;
      bool tDrASngXIr = false;
      bool LYiIrqBlGH = false;
      bool tPuLcqiZjm = false;
      bool wxphkUWRff = false;
      bool OHxAMTJbXz = false;
      bool oLBmMdHgWb = false;
      bool FGnVuOhBXW = false;
      bool UiFaslSuyI = false;
      bool hGCkxkuDUG = false;
      bool NptEaHSbEy = false;
      bool lHEAdGFasZ = false;
      bool LMhOsyEDXK = false;
      bool SefQJenBzk = false;
      bool TqpAWaCCGq = false;
      bool eUJuuAHfKc = false;
      string eNVUAxawIE;
      string YkTByzKguE;
      string uMxDFpffmF;
      string bNSXgSBKmh;
      string cEDhZMjOLh;
      string JWgwKSQROJ;
      string QuIDbLRuUe;
      string xzsNbqJOdr;
      string FQTEwFgWNN;
      string CiucQgwAGN;
      string totfjJcSTT;
      string JBnWEAbDHW;
      string euhGcOEQxt;
      string uJIPxQWmTl;
      string bNCtEAuYYQ;
      string FrrihzGmDV;
      string FMVZXAsXYm;
      string cniUtQrnCb;
      string SeqfoCQYgy;
      string JiiygPrcVD;
      if(eNVUAxawIE == totfjJcSTT){HWzlmQJXnR = true;}
      else if(totfjJcSTT == eNVUAxawIE){oLBmMdHgWb = true;}
      if(YkTByzKguE == JBnWEAbDHW){GSkaDZUojV = true;}
      else if(JBnWEAbDHW == YkTByzKguE){FGnVuOhBXW = true;}
      if(uMxDFpffmF == euhGcOEQxt){jTpactFkne = true;}
      else if(euhGcOEQxt == uMxDFpffmF){UiFaslSuyI = true;}
      if(bNSXgSBKmh == uJIPxQWmTl){YPRzUufFsY = true;}
      else if(uJIPxQWmTl == bNSXgSBKmh){hGCkxkuDUG = true;}
      if(cEDhZMjOLh == bNCtEAuYYQ){srkPqpxHtG = true;}
      else if(bNCtEAuYYQ == cEDhZMjOLh){NptEaHSbEy = true;}
      if(JWgwKSQROJ == FrrihzGmDV){tDrASngXIr = true;}
      else if(FrrihzGmDV == JWgwKSQROJ){lHEAdGFasZ = true;}
      if(QuIDbLRuUe == FMVZXAsXYm){LYiIrqBlGH = true;}
      else if(FMVZXAsXYm == QuIDbLRuUe){LMhOsyEDXK = true;}
      if(xzsNbqJOdr == cniUtQrnCb){tPuLcqiZjm = true;}
      if(FQTEwFgWNN == SeqfoCQYgy){wxphkUWRff = true;}
      if(CiucQgwAGN == JiiygPrcVD){OHxAMTJbXz = true;}
      while(cniUtQrnCb == xzsNbqJOdr){SefQJenBzk = true;}
      while(SeqfoCQYgy == SeqfoCQYgy){TqpAWaCCGq = true;}
      while(JiiygPrcVD == JiiygPrcVD){eUJuuAHfKc = true;}
      if(HWzlmQJXnR == true){HWzlmQJXnR = false;}
      if(GSkaDZUojV == true){GSkaDZUojV = false;}
      if(jTpactFkne == true){jTpactFkne = false;}
      if(YPRzUufFsY == true){YPRzUufFsY = false;}
      if(srkPqpxHtG == true){srkPqpxHtG = false;}
      if(tDrASngXIr == true){tDrASngXIr = false;}
      if(LYiIrqBlGH == true){LYiIrqBlGH = false;}
      if(tPuLcqiZjm == true){tPuLcqiZjm = false;}
      if(wxphkUWRff == true){wxphkUWRff = false;}
      if(OHxAMTJbXz == true){OHxAMTJbXz = false;}
      if(oLBmMdHgWb == true){oLBmMdHgWb = false;}
      if(FGnVuOhBXW == true){FGnVuOhBXW = false;}
      if(UiFaslSuyI == true){UiFaslSuyI = false;}
      if(hGCkxkuDUG == true){hGCkxkuDUG = false;}
      if(NptEaHSbEy == true){NptEaHSbEy = false;}
      if(lHEAdGFasZ == true){lHEAdGFasZ = false;}
      if(LMhOsyEDXK == true){LMhOsyEDXK = false;}
      if(SefQJenBzk == true){SefQJenBzk = false;}
      if(TqpAWaCCGq == true){TqpAWaCCGq = false;}
      if(eUJuuAHfKc == true){eUJuuAHfKc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LCQLJJJSZJ
{ 
  void ZnPTgEipqL()
  { 
      bool ZRysUJufbb = false;
      bool OmkNZYJgKa = false;
      bool sFHORBCAyP = false;
      bool ASIYSUjoAD = false;
      bool ZSlddPWDhx = false;
      bool tVifMUKiaS = false;
      bool HtgMaueLtE = false;
      bool nTgHBaTckC = false;
      bool dySBUejbMy = false;
      bool KAOguekYDh = false;
      bool jLJcIZoael = false;
      bool AgyYoIaeqw = false;
      bool LDzusnFzLV = false;
      bool otZCRSoost = false;
      bool oIwaxdBorm = false;
      bool EFhGVgMNiT = false;
      bool UpOIwGGwHV = false;
      bool TllwGDGXxP = false;
      bool lQGYRjMSfj = false;
      bool GaFYZzsneq = false;
      string JkQzCyoIKX;
      string sMsHmLLnkp;
      string ORjltuqdfo;
      string TZCAjZLnyV;
      string fJSOIRQUJf;
      string RgRWaqAdFG;
      string HLcUDSKsXN;
      string AWpOJFyVcc;
      string dWTzXmIeYr;
      string YgiqOUgyLp;
      string HWwufuqCMU;
      string sdBccjqcxP;
      string JeTenSnyAo;
      string YAJmUGZXTc;
      string wFRDztfFOe;
      string cDBufbDRHM;
      string GrCXwsTNHV;
      string KTIUTENPfs;
      string mhiUMUzOGs;
      string DIQHVDDtHG;
      if(JkQzCyoIKX == HWwufuqCMU){ZRysUJufbb = true;}
      else if(HWwufuqCMU == JkQzCyoIKX){jLJcIZoael = true;}
      if(sMsHmLLnkp == sdBccjqcxP){OmkNZYJgKa = true;}
      else if(sdBccjqcxP == sMsHmLLnkp){AgyYoIaeqw = true;}
      if(ORjltuqdfo == JeTenSnyAo){sFHORBCAyP = true;}
      else if(JeTenSnyAo == ORjltuqdfo){LDzusnFzLV = true;}
      if(TZCAjZLnyV == YAJmUGZXTc){ASIYSUjoAD = true;}
      else if(YAJmUGZXTc == TZCAjZLnyV){otZCRSoost = true;}
      if(fJSOIRQUJf == wFRDztfFOe){ZSlddPWDhx = true;}
      else if(wFRDztfFOe == fJSOIRQUJf){oIwaxdBorm = true;}
      if(RgRWaqAdFG == cDBufbDRHM){tVifMUKiaS = true;}
      else if(cDBufbDRHM == RgRWaqAdFG){EFhGVgMNiT = true;}
      if(HLcUDSKsXN == GrCXwsTNHV){HtgMaueLtE = true;}
      else if(GrCXwsTNHV == HLcUDSKsXN){UpOIwGGwHV = true;}
      if(AWpOJFyVcc == KTIUTENPfs){nTgHBaTckC = true;}
      if(dWTzXmIeYr == mhiUMUzOGs){dySBUejbMy = true;}
      if(YgiqOUgyLp == DIQHVDDtHG){KAOguekYDh = true;}
      while(KTIUTENPfs == AWpOJFyVcc){TllwGDGXxP = true;}
      while(mhiUMUzOGs == mhiUMUzOGs){lQGYRjMSfj = true;}
      while(DIQHVDDtHG == DIQHVDDtHG){GaFYZzsneq = true;}
      if(ZRysUJufbb == true){ZRysUJufbb = false;}
      if(OmkNZYJgKa == true){OmkNZYJgKa = false;}
      if(sFHORBCAyP == true){sFHORBCAyP = false;}
      if(ASIYSUjoAD == true){ASIYSUjoAD = false;}
      if(ZSlddPWDhx == true){ZSlddPWDhx = false;}
      if(tVifMUKiaS == true){tVifMUKiaS = false;}
      if(HtgMaueLtE == true){HtgMaueLtE = false;}
      if(nTgHBaTckC == true){nTgHBaTckC = false;}
      if(dySBUejbMy == true){dySBUejbMy = false;}
      if(KAOguekYDh == true){KAOguekYDh = false;}
      if(jLJcIZoael == true){jLJcIZoael = false;}
      if(AgyYoIaeqw == true){AgyYoIaeqw = false;}
      if(LDzusnFzLV == true){LDzusnFzLV = false;}
      if(otZCRSoost == true){otZCRSoost = false;}
      if(oIwaxdBorm == true){oIwaxdBorm = false;}
      if(EFhGVgMNiT == true){EFhGVgMNiT = false;}
      if(UpOIwGGwHV == true){UpOIwGGwHV = false;}
      if(TllwGDGXxP == true){TllwGDGXxP = false;}
      if(lQGYRjMSfj == true){lQGYRjMSfj = false;}
      if(GaFYZzsneq == true){GaFYZzsneq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TRDXXGGNPL
{ 
  void dMHrLOreek()
  { 
      bool NDYneUhUFA = false;
      bool buiiwhSmtP = false;
      bool FkRZxzTowh = false;
      bool CVNeWESzNL = false;
      bool OhOcELtUIZ = false;
      bool wwDfgckzpf = false;
      bool BsYXyFhEMq = false;
      bool OSZhBXVoUl = false;
      bool EyfVkGSgxs = false;
      bool TTIgJVIqdy = false;
      bool doIQKdVUeJ = false;
      bool HwdEaCMClr = false;
      bool mAHSXtJrXe = false;
      bool OeLWIPpPLH = false;
      bool jyCmlXpEGG = false;
      bool JFElLcgosP = false;
      bool TdwAtcjGwL = false;
      bool MwqdHnyUgA = false;
      bool EFlQUJZYLe = false;
      bool hBVunFBBrI = false;
      string bSNWjMOeWZ;
      string HGLzYsxNrq;
      string TGuxXdHXCJ;
      string uEntDVaMSX;
      string dLVArGqLbe;
      string fjENwVXQzF;
      string EqcMdCSRwD;
      string RjtUMIjtFQ;
      string muwXcLAZxg;
      string yKNMSmhIVo;
      string nZPYMwoiBn;
      string kdLhSJtFjS;
      string CrTOEHWhCZ;
      string ZbXPbNfWKg;
      string VQYJwTyesI;
      string rcYClwFBTF;
      string ZGgaNIFuFF;
      string dWtDxlTJRk;
      string IrnsgxDUcf;
      string HdDFHOixwm;
      if(bSNWjMOeWZ == nZPYMwoiBn){NDYneUhUFA = true;}
      else if(nZPYMwoiBn == bSNWjMOeWZ){doIQKdVUeJ = true;}
      if(HGLzYsxNrq == kdLhSJtFjS){buiiwhSmtP = true;}
      else if(kdLhSJtFjS == HGLzYsxNrq){HwdEaCMClr = true;}
      if(TGuxXdHXCJ == CrTOEHWhCZ){FkRZxzTowh = true;}
      else if(CrTOEHWhCZ == TGuxXdHXCJ){mAHSXtJrXe = true;}
      if(uEntDVaMSX == ZbXPbNfWKg){CVNeWESzNL = true;}
      else if(ZbXPbNfWKg == uEntDVaMSX){OeLWIPpPLH = true;}
      if(dLVArGqLbe == VQYJwTyesI){OhOcELtUIZ = true;}
      else if(VQYJwTyesI == dLVArGqLbe){jyCmlXpEGG = true;}
      if(fjENwVXQzF == rcYClwFBTF){wwDfgckzpf = true;}
      else if(rcYClwFBTF == fjENwVXQzF){JFElLcgosP = true;}
      if(EqcMdCSRwD == ZGgaNIFuFF){BsYXyFhEMq = true;}
      else if(ZGgaNIFuFF == EqcMdCSRwD){TdwAtcjGwL = true;}
      if(RjtUMIjtFQ == dWtDxlTJRk){OSZhBXVoUl = true;}
      if(muwXcLAZxg == IrnsgxDUcf){EyfVkGSgxs = true;}
      if(yKNMSmhIVo == HdDFHOixwm){TTIgJVIqdy = true;}
      while(dWtDxlTJRk == RjtUMIjtFQ){MwqdHnyUgA = true;}
      while(IrnsgxDUcf == IrnsgxDUcf){EFlQUJZYLe = true;}
      while(HdDFHOixwm == HdDFHOixwm){hBVunFBBrI = true;}
      if(NDYneUhUFA == true){NDYneUhUFA = false;}
      if(buiiwhSmtP == true){buiiwhSmtP = false;}
      if(FkRZxzTowh == true){FkRZxzTowh = false;}
      if(CVNeWESzNL == true){CVNeWESzNL = false;}
      if(OhOcELtUIZ == true){OhOcELtUIZ = false;}
      if(wwDfgckzpf == true){wwDfgckzpf = false;}
      if(BsYXyFhEMq == true){BsYXyFhEMq = false;}
      if(OSZhBXVoUl == true){OSZhBXVoUl = false;}
      if(EyfVkGSgxs == true){EyfVkGSgxs = false;}
      if(TTIgJVIqdy == true){TTIgJVIqdy = false;}
      if(doIQKdVUeJ == true){doIQKdVUeJ = false;}
      if(HwdEaCMClr == true){HwdEaCMClr = false;}
      if(mAHSXtJrXe == true){mAHSXtJrXe = false;}
      if(OeLWIPpPLH == true){OeLWIPpPLH = false;}
      if(jyCmlXpEGG == true){jyCmlXpEGG = false;}
      if(JFElLcgosP == true){JFElLcgosP = false;}
      if(TdwAtcjGwL == true){TdwAtcjGwL = false;}
      if(MwqdHnyUgA == true){MwqdHnyUgA = false;}
      if(EFlQUJZYLe == true){EFlQUJZYLe = false;}
      if(hBVunFBBrI == true){hBVunFBBrI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVCDXQZTEJ
{ 
  void ZdeyJlteBJ()
  { 
      bool MVXKdObMnH = false;
      bool kliFGqGUBY = false;
      bool ExndEWIXdu = false;
      bool DjgRlCgYsR = false;
      bool fAxezFMlbm = false;
      bool mLdNKPhtFG = false;
      bool FEhsEAFQTE = false;
      bool JhbisEAJez = false;
      bool KVuqIrFSHW = false;
      bool TmSlMaSEay = false;
      bool zuSWcEjuUF = false;
      bool PYOGwjIpjM = false;
      bool tlJxjVOoWS = false;
      bool lwigzODYND = false;
      bool HKyBHuYLob = false;
      bool RbTODNlUmH = false;
      bool otYCTSphHh = false;
      bool fjcgEjmHpo = false;
      bool xDAtAKbUck = false;
      bool bhkGNNkwgn = false;
      string pNplTkaPqY;
      string byqUoznkmP;
      string XzCMSbQgin;
      string llcHYDdHst;
      string HgJmmAfakV;
      string WWElOqLcTq;
      string TtfCloUiwl;
      string VgrsIqpOZR;
      string wpwNROhqsh;
      string rAnCZMAGAx;
      string fxdyAoeKcX;
      string AwDBudySkX;
      string GdoOtVrpSu;
      string piNclzLxMb;
      string iXNUguwmGw;
      string OhVcpBHPEe;
      string xoqhgRhZOw;
      string RAFJniQUgy;
      string YFiWfIMklj;
      string qurhesffmP;
      if(pNplTkaPqY == fxdyAoeKcX){MVXKdObMnH = true;}
      else if(fxdyAoeKcX == pNplTkaPqY){zuSWcEjuUF = true;}
      if(byqUoznkmP == AwDBudySkX){kliFGqGUBY = true;}
      else if(AwDBudySkX == byqUoznkmP){PYOGwjIpjM = true;}
      if(XzCMSbQgin == GdoOtVrpSu){ExndEWIXdu = true;}
      else if(GdoOtVrpSu == XzCMSbQgin){tlJxjVOoWS = true;}
      if(llcHYDdHst == piNclzLxMb){DjgRlCgYsR = true;}
      else if(piNclzLxMb == llcHYDdHst){lwigzODYND = true;}
      if(HgJmmAfakV == iXNUguwmGw){fAxezFMlbm = true;}
      else if(iXNUguwmGw == HgJmmAfakV){HKyBHuYLob = true;}
      if(WWElOqLcTq == OhVcpBHPEe){mLdNKPhtFG = true;}
      else if(OhVcpBHPEe == WWElOqLcTq){RbTODNlUmH = true;}
      if(TtfCloUiwl == xoqhgRhZOw){FEhsEAFQTE = true;}
      else if(xoqhgRhZOw == TtfCloUiwl){otYCTSphHh = true;}
      if(VgrsIqpOZR == RAFJniQUgy){JhbisEAJez = true;}
      if(wpwNROhqsh == YFiWfIMklj){KVuqIrFSHW = true;}
      if(rAnCZMAGAx == qurhesffmP){TmSlMaSEay = true;}
      while(RAFJniQUgy == VgrsIqpOZR){fjcgEjmHpo = true;}
      while(YFiWfIMklj == YFiWfIMklj){xDAtAKbUck = true;}
      while(qurhesffmP == qurhesffmP){bhkGNNkwgn = true;}
      if(MVXKdObMnH == true){MVXKdObMnH = false;}
      if(kliFGqGUBY == true){kliFGqGUBY = false;}
      if(ExndEWIXdu == true){ExndEWIXdu = false;}
      if(DjgRlCgYsR == true){DjgRlCgYsR = false;}
      if(fAxezFMlbm == true){fAxezFMlbm = false;}
      if(mLdNKPhtFG == true){mLdNKPhtFG = false;}
      if(FEhsEAFQTE == true){FEhsEAFQTE = false;}
      if(JhbisEAJez == true){JhbisEAJez = false;}
      if(KVuqIrFSHW == true){KVuqIrFSHW = false;}
      if(TmSlMaSEay == true){TmSlMaSEay = false;}
      if(zuSWcEjuUF == true){zuSWcEjuUF = false;}
      if(PYOGwjIpjM == true){PYOGwjIpjM = false;}
      if(tlJxjVOoWS == true){tlJxjVOoWS = false;}
      if(lwigzODYND == true){lwigzODYND = false;}
      if(HKyBHuYLob == true){HKyBHuYLob = false;}
      if(RbTODNlUmH == true){RbTODNlUmH = false;}
      if(otYCTSphHh == true){otYCTSphHh = false;}
      if(fjcgEjmHpo == true){fjcgEjmHpo = false;}
      if(xDAtAKbUck == true){xDAtAKbUck = false;}
      if(bhkGNNkwgn == true){bhkGNNkwgn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SYCNGARDFX
{ 
  void duEXeuTqos()
  { 
      bool lqxHaVhcQx = false;
      bool ZzSNryWqCl = false;
      bool BpbzBSczRf = false;
      bool eraqBhHIEu = false;
      bool jEKAAPwljT = false;
      bool AcKMYuPxGI = false;
      bool siLkShXbLJ = false;
      bool pOlHCxfbzk = false;
      bool WpOxeBgOSF = false;
      bool SKCwBBrZhR = false;
      bool rTZadlpDKa = false;
      bool PnxUkCTOFQ = false;
      bool AIIFpfLpFA = false;
      bool FGshsCPnTr = false;
      bool KdErpeMgKz = false;
      bool gdTQQiLUjx = false;
      bool ZAxJUJtPbi = false;
      bool lftNGWEPPL = false;
      bool SefGTblbQJ = false;
      bool puDVSKfuWf = false;
      string uHANBpfPaf;
      string aHhETLsoRB;
      string LyPCFFsDpP;
      string dmzVmJhMYm;
      string GEgkYcOeFl;
      string MqmfmxqxIw;
      string wbYKBnIMRK;
      string cfQdtGRedb;
      string qNxDDlzTio;
      string RkDcpdeVij;
      string UCNuJfaJkf;
      string eMTgFheVHO;
      string nncbsqbnmQ;
      string buusGnACtW;
      string LphDJERWXI;
      string zJNTufYkCR;
      string DmVUEiRZZQ;
      string hcajDyGZRn;
      string ZFPeRRhaxZ;
      string POzbSXTNyZ;
      if(uHANBpfPaf == UCNuJfaJkf){lqxHaVhcQx = true;}
      else if(UCNuJfaJkf == uHANBpfPaf){rTZadlpDKa = true;}
      if(aHhETLsoRB == eMTgFheVHO){ZzSNryWqCl = true;}
      else if(eMTgFheVHO == aHhETLsoRB){PnxUkCTOFQ = true;}
      if(LyPCFFsDpP == nncbsqbnmQ){BpbzBSczRf = true;}
      else if(nncbsqbnmQ == LyPCFFsDpP){AIIFpfLpFA = true;}
      if(dmzVmJhMYm == buusGnACtW){eraqBhHIEu = true;}
      else if(buusGnACtW == dmzVmJhMYm){FGshsCPnTr = true;}
      if(GEgkYcOeFl == LphDJERWXI){jEKAAPwljT = true;}
      else if(LphDJERWXI == GEgkYcOeFl){KdErpeMgKz = true;}
      if(MqmfmxqxIw == zJNTufYkCR){AcKMYuPxGI = true;}
      else if(zJNTufYkCR == MqmfmxqxIw){gdTQQiLUjx = true;}
      if(wbYKBnIMRK == DmVUEiRZZQ){siLkShXbLJ = true;}
      else if(DmVUEiRZZQ == wbYKBnIMRK){ZAxJUJtPbi = true;}
      if(cfQdtGRedb == hcajDyGZRn){pOlHCxfbzk = true;}
      if(qNxDDlzTio == ZFPeRRhaxZ){WpOxeBgOSF = true;}
      if(RkDcpdeVij == POzbSXTNyZ){SKCwBBrZhR = true;}
      while(hcajDyGZRn == cfQdtGRedb){lftNGWEPPL = true;}
      while(ZFPeRRhaxZ == ZFPeRRhaxZ){SefGTblbQJ = true;}
      while(POzbSXTNyZ == POzbSXTNyZ){puDVSKfuWf = true;}
      if(lqxHaVhcQx == true){lqxHaVhcQx = false;}
      if(ZzSNryWqCl == true){ZzSNryWqCl = false;}
      if(BpbzBSczRf == true){BpbzBSczRf = false;}
      if(eraqBhHIEu == true){eraqBhHIEu = false;}
      if(jEKAAPwljT == true){jEKAAPwljT = false;}
      if(AcKMYuPxGI == true){AcKMYuPxGI = false;}
      if(siLkShXbLJ == true){siLkShXbLJ = false;}
      if(pOlHCxfbzk == true){pOlHCxfbzk = false;}
      if(WpOxeBgOSF == true){WpOxeBgOSF = false;}
      if(SKCwBBrZhR == true){SKCwBBrZhR = false;}
      if(rTZadlpDKa == true){rTZadlpDKa = false;}
      if(PnxUkCTOFQ == true){PnxUkCTOFQ = false;}
      if(AIIFpfLpFA == true){AIIFpfLpFA = false;}
      if(FGshsCPnTr == true){FGshsCPnTr = false;}
      if(KdErpeMgKz == true){KdErpeMgKz = false;}
      if(gdTQQiLUjx == true){gdTQQiLUjx = false;}
      if(ZAxJUJtPbi == true){ZAxJUJtPbi = false;}
      if(lftNGWEPPL == true){lftNGWEPPL = false;}
      if(SefGTblbQJ == true){SefGTblbQJ = false;}
      if(puDVSKfuWf == true){puDVSKfuWf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DDVLDBECHK
{ 
  void XiahTQlmYV()
  { 
      bool UQltjhhhRu = false;
      bool eASbNzISPQ = false;
      bool HJTbxQEMTF = false;
      bool kYGITpasLP = false;
      bool OsiCUljKBr = false;
      bool FSNMPKxJxT = false;
      bool dVOMJGtKIX = false;
      bool XOGzCOZQHK = false;
      bool fsKazSLssI = false;
      bool sQwrlrdWrO = false;
      bool rZBdTqMNKB = false;
      bool kfBlnkKnNq = false;
      bool uBRzeHRONJ = false;
      bool jDYsSGqfGI = false;
      bool FxhqXNOKDA = false;
      bool gpJASqICzM = false;
      bool YxzBQgGISg = false;
      bool sdgEkxSZaR = false;
      bool rHKMbttXZb = false;
      bool xogtiIxfaq = false;
      string YTikXAGNmw;
      string DmytYJweVx;
      string IqTrPhjWHf;
      string sMMKsbFuas;
      string EdOSiEzphN;
      string oTtfzgzpVo;
      string QiGGDqamBw;
      string EBEcsdcBIL;
      string hsntqZSfLL;
      string cPYkbUWHOr;
      string cLokJnPQmU;
      string ExhKGXtMOd;
      string YuboTnbSBY;
      string HUlQhWDDjD;
      string KBrqHehOeE;
      string ZKskShjAQU;
      string LwPONiKQbj;
      string TqbKSXCjgn;
      string GMnwywbBxA;
      string lDmPqNlddX;
      if(YTikXAGNmw == cLokJnPQmU){UQltjhhhRu = true;}
      else if(cLokJnPQmU == YTikXAGNmw){rZBdTqMNKB = true;}
      if(DmytYJweVx == ExhKGXtMOd){eASbNzISPQ = true;}
      else if(ExhKGXtMOd == DmytYJweVx){kfBlnkKnNq = true;}
      if(IqTrPhjWHf == YuboTnbSBY){HJTbxQEMTF = true;}
      else if(YuboTnbSBY == IqTrPhjWHf){uBRzeHRONJ = true;}
      if(sMMKsbFuas == HUlQhWDDjD){kYGITpasLP = true;}
      else if(HUlQhWDDjD == sMMKsbFuas){jDYsSGqfGI = true;}
      if(EdOSiEzphN == KBrqHehOeE){OsiCUljKBr = true;}
      else if(KBrqHehOeE == EdOSiEzphN){FxhqXNOKDA = true;}
      if(oTtfzgzpVo == ZKskShjAQU){FSNMPKxJxT = true;}
      else if(ZKskShjAQU == oTtfzgzpVo){gpJASqICzM = true;}
      if(QiGGDqamBw == LwPONiKQbj){dVOMJGtKIX = true;}
      else if(LwPONiKQbj == QiGGDqamBw){YxzBQgGISg = true;}
      if(EBEcsdcBIL == TqbKSXCjgn){XOGzCOZQHK = true;}
      if(hsntqZSfLL == GMnwywbBxA){fsKazSLssI = true;}
      if(cPYkbUWHOr == lDmPqNlddX){sQwrlrdWrO = true;}
      while(TqbKSXCjgn == EBEcsdcBIL){sdgEkxSZaR = true;}
      while(GMnwywbBxA == GMnwywbBxA){rHKMbttXZb = true;}
      while(lDmPqNlddX == lDmPqNlddX){xogtiIxfaq = true;}
      if(UQltjhhhRu == true){UQltjhhhRu = false;}
      if(eASbNzISPQ == true){eASbNzISPQ = false;}
      if(HJTbxQEMTF == true){HJTbxQEMTF = false;}
      if(kYGITpasLP == true){kYGITpasLP = false;}
      if(OsiCUljKBr == true){OsiCUljKBr = false;}
      if(FSNMPKxJxT == true){FSNMPKxJxT = false;}
      if(dVOMJGtKIX == true){dVOMJGtKIX = false;}
      if(XOGzCOZQHK == true){XOGzCOZQHK = false;}
      if(fsKazSLssI == true){fsKazSLssI = false;}
      if(sQwrlrdWrO == true){sQwrlrdWrO = false;}
      if(rZBdTqMNKB == true){rZBdTqMNKB = false;}
      if(kfBlnkKnNq == true){kfBlnkKnNq = false;}
      if(uBRzeHRONJ == true){uBRzeHRONJ = false;}
      if(jDYsSGqfGI == true){jDYsSGqfGI = false;}
      if(FxhqXNOKDA == true){FxhqXNOKDA = false;}
      if(gpJASqICzM == true){gpJASqICzM = false;}
      if(YxzBQgGISg == true){YxzBQgGISg = false;}
      if(sdgEkxSZaR == true){sdgEkxSZaR = false;}
      if(rHKMbttXZb == true){rHKMbttXZb = false;}
      if(xogtiIxfaq == true){xogtiIxfaq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ISABJFGYIV
{ 
  void hQtJyPrLjK()
  { 
      bool mxyGdKouzm = false;
      bool XOwfoJsJug = false;
      bool pbWYgRPDYH = false;
      bool fkVSwVjXLM = false;
      bool YoWmwhZxWo = false;
      bool KKiyuLaYZM = false;
      bool tkWqHlrciT = false;
      bool ZUyhIAFjcy = false;
      bool qRgiwVCXXj = false;
      bool uKxySnSefJ = false;
      bool pxNDOoMBot = false;
      bool GqwbUbDmtl = false;
      bool jUEzYOXzPU = false;
      bool hZESItEdUG = false;
      bool IAhddDOUdp = false;
      bool jfjtZUrOez = false;
      bool RNkUMfmcTa = false;
      bool XYSmcilaUU = false;
      bool ACVZkBpJrm = false;
      bool BozUouPNQy = false;
      string pmDlcCUPNz;
      string IMfCKLccJa;
      string afdVXZFCls;
      string xPFMyYoJhY;
      string ISyzzKOTXt;
      string lhpMWKIhOD;
      string wRcTCrHTDl;
      string VTtjSIgdVM;
      string KlerHOYron;
      string PHtdcqoexH;
      string DuPkXRmGtN;
      string cdLCsKmjMm;
      string TOdPVOZPHa;
      string SCfOIOWsUp;
      string aSyaLkurkR;
      string DERKnnRAPI;
      string qXySuaxxsd;
      string nsPWLAQCDj;
      string TheoWNjVaT;
      string xVdLyDTefk;
      if(pmDlcCUPNz == DuPkXRmGtN){mxyGdKouzm = true;}
      else if(DuPkXRmGtN == pmDlcCUPNz){pxNDOoMBot = true;}
      if(IMfCKLccJa == cdLCsKmjMm){XOwfoJsJug = true;}
      else if(cdLCsKmjMm == IMfCKLccJa){GqwbUbDmtl = true;}
      if(afdVXZFCls == TOdPVOZPHa){pbWYgRPDYH = true;}
      else if(TOdPVOZPHa == afdVXZFCls){jUEzYOXzPU = true;}
      if(xPFMyYoJhY == SCfOIOWsUp){fkVSwVjXLM = true;}
      else if(SCfOIOWsUp == xPFMyYoJhY){hZESItEdUG = true;}
      if(ISyzzKOTXt == aSyaLkurkR){YoWmwhZxWo = true;}
      else if(aSyaLkurkR == ISyzzKOTXt){IAhddDOUdp = true;}
      if(lhpMWKIhOD == DERKnnRAPI){KKiyuLaYZM = true;}
      else if(DERKnnRAPI == lhpMWKIhOD){jfjtZUrOez = true;}
      if(wRcTCrHTDl == qXySuaxxsd){tkWqHlrciT = true;}
      else if(qXySuaxxsd == wRcTCrHTDl){RNkUMfmcTa = true;}
      if(VTtjSIgdVM == nsPWLAQCDj){ZUyhIAFjcy = true;}
      if(KlerHOYron == TheoWNjVaT){qRgiwVCXXj = true;}
      if(PHtdcqoexH == xVdLyDTefk){uKxySnSefJ = true;}
      while(nsPWLAQCDj == VTtjSIgdVM){XYSmcilaUU = true;}
      while(TheoWNjVaT == TheoWNjVaT){ACVZkBpJrm = true;}
      while(xVdLyDTefk == xVdLyDTefk){BozUouPNQy = true;}
      if(mxyGdKouzm == true){mxyGdKouzm = false;}
      if(XOwfoJsJug == true){XOwfoJsJug = false;}
      if(pbWYgRPDYH == true){pbWYgRPDYH = false;}
      if(fkVSwVjXLM == true){fkVSwVjXLM = false;}
      if(YoWmwhZxWo == true){YoWmwhZxWo = false;}
      if(KKiyuLaYZM == true){KKiyuLaYZM = false;}
      if(tkWqHlrciT == true){tkWqHlrciT = false;}
      if(ZUyhIAFjcy == true){ZUyhIAFjcy = false;}
      if(qRgiwVCXXj == true){qRgiwVCXXj = false;}
      if(uKxySnSefJ == true){uKxySnSefJ = false;}
      if(pxNDOoMBot == true){pxNDOoMBot = false;}
      if(GqwbUbDmtl == true){GqwbUbDmtl = false;}
      if(jUEzYOXzPU == true){jUEzYOXzPU = false;}
      if(hZESItEdUG == true){hZESItEdUG = false;}
      if(IAhddDOUdp == true){IAhddDOUdp = false;}
      if(jfjtZUrOez == true){jfjtZUrOez = false;}
      if(RNkUMfmcTa == true){RNkUMfmcTa = false;}
      if(XYSmcilaUU == true){XYSmcilaUU = false;}
      if(ACVZkBpJrm == true){ACVZkBpJrm = false;}
      if(BozUouPNQy == true){BozUouPNQy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUGPXBMYCX
{ 
  void dYLaYMCTdx()
  { 
      bool ZAxUomhNZd = false;
      bool YTpFqdRgWo = false;
      bool SgqFYyTMET = false;
      bool IEJFPexcRb = false;
      bool cZOaEoXrpq = false;
      bool ylbrZsIrwq = false;
      bool TVIGVUKkoM = false;
      bool foOuMrRQBj = false;
      bool ZaWMUVcReV = false;
      bool VFfZHHQIFi = false;
      bool dmDcLJWfeg = false;
      bool brqMQrywkz = false;
      bool rsFSpZInmF = false;
      bool bIKRFmXsAL = false;
      bool zwlxtdOTIO = false;
      bool IUXFqkgjmk = false;
      bool BhrZFSgYGd = false;
      bool UFuZAuHHYL = false;
      bool LneYwHkEZU = false;
      bool FmFPJQELra = false;
      string cWbjyDCmKh;
      string LPgYdqdRwi;
      string zLUVWpzRjs;
      string TahhxVKgMU;
      string AgaqXzkLpf;
      string xVXpIRBFMH;
      string DkDQOkgzbH;
      string gwFaiRkdxX;
      string FmaDwxDrYe;
      string UEUEROcJcm;
      string RkjhyAQwGp;
      string gXHnBPJzUR;
      string hoZwmbbAIT;
      string oaBKFTDrEu;
      string gGkiyxxfCC;
      string EcnLFcLnuW;
      string YPmlBFWxhh;
      string MQuZkaDqxp;
      string euyGPLmoFc;
      string IOxhVQSzhr;
      if(cWbjyDCmKh == RkjhyAQwGp){ZAxUomhNZd = true;}
      else if(RkjhyAQwGp == cWbjyDCmKh){dmDcLJWfeg = true;}
      if(LPgYdqdRwi == gXHnBPJzUR){YTpFqdRgWo = true;}
      else if(gXHnBPJzUR == LPgYdqdRwi){brqMQrywkz = true;}
      if(zLUVWpzRjs == hoZwmbbAIT){SgqFYyTMET = true;}
      else if(hoZwmbbAIT == zLUVWpzRjs){rsFSpZInmF = true;}
      if(TahhxVKgMU == oaBKFTDrEu){IEJFPexcRb = true;}
      else if(oaBKFTDrEu == TahhxVKgMU){bIKRFmXsAL = true;}
      if(AgaqXzkLpf == gGkiyxxfCC){cZOaEoXrpq = true;}
      else if(gGkiyxxfCC == AgaqXzkLpf){zwlxtdOTIO = true;}
      if(xVXpIRBFMH == EcnLFcLnuW){ylbrZsIrwq = true;}
      else if(EcnLFcLnuW == xVXpIRBFMH){IUXFqkgjmk = true;}
      if(DkDQOkgzbH == YPmlBFWxhh){TVIGVUKkoM = true;}
      else if(YPmlBFWxhh == DkDQOkgzbH){BhrZFSgYGd = true;}
      if(gwFaiRkdxX == MQuZkaDqxp){foOuMrRQBj = true;}
      if(FmaDwxDrYe == euyGPLmoFc){ZaWMUVcReV = true;}
      if(UEUEROcJcm == IOxhVQSzhr){VFfZHHQIFi = true;}
      while(MQuZkaDqxp == gwFaiRkdxX){UFuZAuHHYL = true;}
      while(euyGPLmoFc == euyGPLmoFc){LneYwHkEZU = true;}
      while(IOxhVQSzhr == IOxhVQSzhr){FmFPJQELra = true;}
      if(ZAxUomhNZd == true){ZAxUomhNZd = false;}
      if(YTpFqdRgWo == true){YTpFqdRgWo = false;}
      if(SgqFYyTMET == true){SgqFYyTMET = false;}
      if(IEJFPexcRb == true){IEJFPexcRb = false;}
      if(cZOaEoXrpq == true){cZOaEoXrpq = false;}
      if(ylbrZsIrwq == true){ylbrZsIrwq = false;}
      if(TVIGVUKkoM == true){TVIGVUKkoM = false;}
      if(foOuMrRQBj == true){foOuMrRQBj = false;}
      if(ZaWMUVcReV == true){ZaWMUVcReV = false;}
      if(VFfZHHQIFi == true){VFfZHHQIFi = false;}
      if(dmDcLJWfeg == true){dmDcLJWfeg = false;}
      if(brqMQrywkz == true){brqMQrywkz = false;}
      if(rsFSpZInmF == true){rsFSpZInmF = false;}
      if(bIKRFmXsAL == true){bIKRFmXsAL = false;}
      if(zwlxtdOTIO == true){zwlxtdOTIO = false;}
      if(IUXFqkgjmk == true){IUXFqkgjmk = false;}
      if(BhrZFSgYGd == true){BhrZFSgYGd = false;}
      if(UFuZAuHHYL == true){UFuZAuHHYL = false;}
      if(LneYwHkEZU == true){LneYwHkEZU = false;}
      if(FmFPJQELra == true){FmFPJQELra = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ASRRECHLCD
{ 
  void RZyrnhqKXj()
  { 
      bool sYbfqCDxgY = false;
      bool LEEUDTHjUw = false;
      bool hUcPXsNzkw = false;
      bool WDibVYhGEy = false;
      bool NyhSpVwpfX = false;
      bool yOKgaXuMIx = false;
      bool nELkBIUbze = false;
      bool lAfVijmKYB = false;
      bool xWSMxIrBAx = false;
      bool dVyGKJlxQh = false;
      bool BTqBlxioyq = false;
      bool kkmHAQkyms = false;
      bool PTbCBPCYLZ = false;
      bool xpspAdfRaA = false;
      bool ZDDJMshpGs = false;
      bool XmJXShrnAV = false;
      bool tJcYttqxHW = false;
      bool kTXlTLQRoH = false;
      bool gLSSBJfUWR = false;
      bool kqQFFPadPR = false;
      string TEGkCTsRCi;
      string wGyqekOPQP;
      string TYmQrxdARy;
      string QGXkgbqBbM;
      string pHdDjOhYdm;
      string tCPXctRosF;
      string prADRoiMKC;
      string sMnDZLuigc;
      string OEWeEOpzIl;
      string KBIVWxHZlt;
      string eVOashNMyQ;
      string zhHPqkVUzD;
      string zjEXqqDSgc;
      string DVxlxrpukW;
      string BdBqmctsek;
      string bmZituRpjB;
      string dueUNcjURy;
      string tZicBViMkO;
      string xJmuAQuOrC;
      string aALjrFyfdJ;
      if(TEGkCTsRCi == eVOashNMyQ){sYbfqCDxgY = true;}
      else if(eVOashNMyQ == TEGkCTsRCi){BTqBlxioyq = true;}
      if(wGyqekOPQP == zhHPqkVUzD){LEEUDTHjUw = true;}
      else if(zhHPqkVUzD == wGyqekOPQP){kkmHAQkyms = true;}
      if(TYmQrxdARy == zjEXqqDSgc){hUcPXsNzkw = true;}
      else if(zjEXqqDSgc == TYmQrxdARy){PTbCBPCYLZ = true;}
      if(QGXkgbqBbM == DVxlxrpukW){WDibVYhGEy = true;}
      else if(DVxlxrpukW == QGXkgbqBbM){xpspAdfRaA = true;}
      if(pHdDjOhYdm == BdBqmctsek){NyhSpVwpfX = true;}
      else if(BdBqmctsek == pHdDjOhYdm){ZDDJMshpGs = true;}
      if(tCPXctRosF == bmZituRpjB){yOKgaXuMIx = true;}
      else if(bmZituRpjB == tCPXctRosF){XmJXShrnAV = true;}
      if(prADRoiMKC == dueUNcjURy){nELkBIUbze = true;}
      else if(dueUNcjURy == prADRoiMKC){tJcYttqxHW = true;}
      if(sMnDZLuigc == tZicBViMkO){lAfVijmKYB = true;}
      if(OEWeEOpzIl == xJmuAQuOrC){xWSMxIrBAx = true;}
      if(KBIVWxHZlt == aALjrFyfdJ){dVyGKJlxQh = true;}
      while(tZicBViMkO == sMnDZLuigc){kTXlTLQRoH = true;}
      while(xJmuAQuOrC == xJmuAQuOrC){gLSSBJfUWR = true;}
      while(aALjrFyfdJ == aALjrFyfdJ){kqQFFPadPR = true;}
      if(sYbfqCDxgY == true){sYbfqCDxgY = false;}
      if(LEEUDTHjUw == true){LEEUDTHjUw = false;}
      if(hUcPXsNzkw == true){hUcPXsNzkw = false;}
      if(WDibVYhGEy == true){WDibVYhGEy = false;}
      if(NyhSpVwpfX == true){NyhSpVwpfX = false;}
      if(yOKgaXuMIx == true){yOKgaXuMIx = false;}
      if(nELkBIUbze == true){nELkBIUbze = false;}
      if(lAfVijmKYB == true){lAfVijmKYB = false;}
      if(xWSMxIrBAx == true){xWSMxIrBAx = false;}
      if(dVyGKJlxQh == true){dVyGKJlxQh = false;}
      if(BTqBlxioyq == true){BTqBlxioyq = false;}
      if(kkmHAQkyms == true){kkmHAQkyms = false;}
      if(PTbCBPCYLZ == true){PTbCBPCYLZ = false;}
      if(xpspAdfRaA == true){xpspAdfRaA = false;}
      if(ZDDJMshpGs == true){ZDDJMshpGs = false;}
      if(XmJXShrnAV == true){XmJXShrnAV = false;}
      if(tJcYttqxHW == true){tJcYttqxHW = false;}
      if(kTXlTLQRoH == true){kTXlTLQRoH = false;}
      if(gLSSBJfUWR == true){gLSSBJfUWR = false;}
      if(kqQFFPadPR == true){kqQFFPadPR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VVYNWPLHFI
{ 
  void NHkePbqZHb()
  { 
      bool ZLkJQDgOHq = false;
      bool DSuytgtBly = false;
      bool nPTaDVoycy = false;
      bool xbOkYnqXIX = false;
      bool NcTssfShVR = false;
      bool YVzhMKqKGu = false;
      bool OhlItaEKZF = false;
      bool oVrOkLuahX = false;
      bool DHbLYacfYO = false;
      bool xgRNIeqLyS = false;
      bool bHIPbCcjwB = false;
      bool OQciqHGaiS = false;
      bool xYlLIIEdFG = false;
      bool UjbOwwzLiW = false;
      bool xriXzfEiWA = false;
      bool YPbfVCVwHT = false;
      bool xzepgenNlu = false;
      bool ItqMUEoOLb = false;
      bool DVHEhEHuss = false;
      bool ZCEPYyNspT = false;
      string HfJeWwJCfx;
      string keZsHdHRSg;
      string RfDeAISXKm;
      string QOCwZjwZrK;
      string JJURCHLUiq;
      string fxLmobbdeN;
      string clqsfWccSW;
      string hhZIXHLkcs;
      string xxnTHTCOHy;
      string HRudgWSbkf;
      string eiBLJxXDOh;
      string QqBkQfxXkM;
      string TNUTOPmubA;
      string oizwNNucJJ;
      string uzzZhQPJNB;
      string YtpYLQOhws;
      string KbbNsgqEXD;
      string jUNbQUNuly;
      string zchZbtrakw;
      string zNfPySXkgB;
      if(HfJeWwJCfx == eiBLJxXDOh){ZLkJQDgOHq = true;}
      else if(eiBLJxXDOh == HfJeWwJCfx){bHIPbCcjwB = true;}
      if(keZsHdHRSg == QqBkQfxXkM){DSuytgtBly = true;}
      else if(QqBkQfxXkM == keZsHdHRSg){OQciqHGaiS = true;}
      if(RfDeAISXKm == TNUTOPmubA){nPTaDVoycy = true;}
      else if(TNUTOPmubA == RfDeAISXKm){xYlLIIEdFG = true;}
      if(QOCwZjwZrK == oizwNNucJJ){xbOkYnqXIX = true;}
      else if(oizwNNucJJ == QOCwZjwZrK){UjbOwwzLiW = true;}
      if(JJURCHLUiq == uzzZhQPJNB){NcTssfShVR = true;}
      else if(uzzZhQPJNB == JJURCHLUiq){xriXzfEiWA = true;}
      if(fxLmobbdeN == YtpYLQOhws){YVzhMKqKGu = true;}
      else if(YtpYLQOhws == fxLmobbdeN){YPbfVCVwHT = true;}
      if(clqsfWccSW == KbbNsgqEXD){OhlItaEKZF = true;}
      else if(KbbNsgqEXD == clqsfWccSW){xzepgenNlu = true;}
      if(hhZIXHLkcs == jUNbQUNuly){oVrOkLuahX = true;}
      if(xxnTHTCOHy == zchZbtrakw){DHbLYacfYO = true;}
      if(HRudgWSbkf == zNfPySXkgB){xgRNIeqLyS = true;}
      while(jUNbQUNuly == hhZIXHLkcs){ItqMUEoOLb = true;}
      while(zchZbtrakw == zchZbtrakw){DVHEhEHuss = true;}
      while(zNfPySXkgB == zNfPySXkgB){ZCEPYyNspT = true;}
      if(ZLkJQDgOHq == true){ZLkJQDgOHq = false;}
      if(DSuytgtBly == true){DSuytgtBly = false;}
      if(nPTaDVoycy == true){nPTaDVoycy = false;}
      if(xbOkYnqXIX == true){xbOkYnqXIX = false;}
      if(NcTssfShVR == true){NcTssfShVR = false;}
      if(YVzhMKqKGu == true){YVzhMKqKGu = false;}
      if(OhlItaEKZF == true){OhlItaEKZF = false;}
      if(oVrOkLuahX == true){oVrOkLuahX = false;}
      if(DHbLYacfYO == true){DHbLYacfYO = false;}
      if(xgRNIeqLyS == true){xgRNIeqLyS = false;}
      if(bHIPbCcjwB == true){bHIPbCcjwB = false;}
      if(OQciqHGaiS == true){OQciqHGaiS = false;}
      if(xYlLIIEdFG == true){xYlLIIEdFG = false;}
      if(UjbOwwzLiW == true){UjbOwwzLiW = false;}
      if(xriXzfEiWA == true){xriXzfEiWA = false;}
      if(YPbfVCVwHT == true){YPbfVCVwHT = false;}
      if(xzepgenNlu == true){xzepgenNlu = false;}
      if(ItqMUEoOLb == true){ItqMUEoOLb = false;}
      if(DVHEhEHuss == true){DVHEhEHuss = false;}
      if(ZCEPYyNspT == true){ZCEPYyNspT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJTRZUNSPX
{ 
  void OBmKItlxJX()
  { 
      bool czzXFUQole = false;
      bool iAOZOWtLdy = false;
      bool WrCKqVwLbV = false;
      bool OAjjmjbqTP = false;
      bool RaInOAHsTW = false;
      bool KYhfdjxngi = false;
      bool XFMQPiQdmd = false;
      bool tCqNgwjNwq = false;
      bool ODrFLoRDFC = false;
      bool mmKkqMNqYe = false;
      bool jcFobHhTzh = false;
      bool ziroTUMHFa = false;
      bool QMYjqHqGWU = false;
      bool hroQHlxCcD = false;
      bool HyEWDDuVQW = false;
      bool zFlxNWDUyU = false;
      bool QaxeAGtahh = false;
      bool WJdBSSHCgm = false;
      bool LVoAUbGqCj = false;
      bool hcEImfBZWw = false;
      string YKNicztqlt;
      string STPoIziqzo;
      string eKFwENrqgA;
      string ASWzOQFnmR;
      string LxLwzdHyMx;
      string auoNJNEQdO;
      string GCKltzwQZq;
      string stEgdgzJxa;
      string GsdjYFdJoB;
      string LoKXKImYBz;
      string gpXVDgpHib;
      string NuTCHNXaNo;
      string VlbYfEifWU;
      string taHxsPUIfq;
      string OVZMnQUHPx;
      string jLKMduOzoy;
      string xKkOhlmVIr;
      string rPtVZzLOkP;
      string iaPYjiPtSy;
      string AVShsEkLeB;
      if(YKNicztqlt == gpXVDgpHib){czzXFUQole = true;}
      else if(gpXVDgpHib == YKNicztqlt){jcFobHhTzh = true;}
      if(STPoIziqzo == NuTCHNXaNo){iAOZOWtLdy = true;}
      else if(NuTCHNXaNo == STPoIziqzo){ziroTUMHFa = true;}
      if(eKFwENrqgA == VlbYfEifWU){WrCKqVwLbV = true;}
      else if(VlbYfEifWU == eKFwENrqgA){QMYjqHqGWU = true;}
      if(ASWzOQFnmR == taHxsPUIfq){OAjjmjbqTP = true;}
      else if(taHxsPUIfq == ASWzOQFnmR){hroQHlxCcD = true;}
      if(LxLwzdHyMx == OVZMnQUHPx){RaInOAHsTW = true;}
      else if(OVZMnQUHPx == LxLwzdHyMx){HyEWDDuVQW = true;}
      if(auoNJNEQdO == jLKMduOzoy){KYhfdjxngi = true;}
      else if(jLKMduOzoy == auoNJNEQdO){zFlxNWDUyU = true;}
      if(GCKltzwQZq == xKkOhlmVIr){XFMQPiQdmd = true;}
      else if(xKkOhlmVIr == GCKltzwQZq){QaxeAGtahh = true;}
      if(stEgdgzJxa == rPtVZzLOkP){tCqNgwjNwq = true;}
      if(GsdjYFdJoB == iaPYjiPtSy){ODrFLoRDFC = true;}
      if(LoKXKImYBz == AVShsEkLeB){mmKkqMNqYe = true;}
      while(rPtVZzLOkP == stEgdgzJxa){WJdBSSHCgm = true;}
      while(iaPYjiPtSy == iaPYjiPtSy){LVoAUbGqCj = true;}
      while(AVShsEkLeB == AVShsEkLeB){hcEImfBZWw = true;}
      if(czzXFUQole == true){czzXFUQole = false;}
      if(iAOZOWtLdy == true){iAOZOWtLdy = false;}
      if(WrCKqVwLbV == true){WrCKqVwLbV = false;}
      if(OAjjmjbqTP == true){OAjjmjbqTP = false;}
      if(RaInOAHsTW == true){RaInOAHsTW = false;}
      if(KYhfdjxngi == true){KYhfdjxngi = false;}
      if(XFMQPiQdmd == true){XFMQPiQdmd = false;}
      if(tCqNgwjNwq == true){tCqNgwjNwq = false;}
      if(ODrFLoRDFC == true){ODrFLoRDFC = false;}
      if(mmKkqMNqYe == true){mmKkqMNqYe = false;}
      if(jcFobHhTzh == true){jcFobHhTzh = false;}
      if(ziroTUMHFa == true){ziroTUMHFa = false;}
      if(QMYjqHqGWU == true){QMYjqHqGWU = false;}
      if(hroQHlxCcD == true){hroQHlxCcD = false;}
      if(HyEWDDuVQW == true){HyEWDDuVQW = false;}
      if(zFlxNWDUyU == true){zFlxNWDUyU = false;}
      if(QaxeAGtahh == true){QaxeAGtahh = false;}
      if(WJdBSSHCgm == true){WJdBSSHCgm = false;}
      if(LVoAUbGqCj == true){LVoAUbGqCj = false;}
      if(hcEImfBZWw == true){hcEImfBZWw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZSPGLGSZGM
{ 
  void XGKfzwZOwC()
  { 
      bool ESdMihRCQx = false;
      bool nEULRlphuX = false;
      bool lEUfFMlpwe = false;
      bool kZXgIutMzz = false;
      bool nFSGGozNjI = false;
      bool HzOhOAxxGW = false;
      bool wbGkMOfmDV = false;
      bool rdhuifkOZQ = false;
      bool NYGnXlKpSH = false;
      bool xwFcDMzhtq = false;
      bool JLJNQdRTyh = false;
      bool OiXpJWVRNa = false;
      bool EoUuXuXFrV = false;
      bool gDThGBOrWs = false;
      bool UqrjrOYOTf = false;
      bool qgTTmUpNpV = false;
      bool FLabBLPojH = false;
      bool IduTGNwjDJ = false;
      bool VJlLezjAul = false;
      bool LACBmIPPig = false;
      string UcFhISDyEj;
      string XiNIzdpEuN;
      string ZczJXLJSEM;
      string huVVkliLic;
      string lbhmIInEqi;
      string SUhfrrcuKx;
      string JjtqCcMrWN;
      string ueVSbxtMAO;
      string WEaUsMMpds;
      string ImBkTBhqjf;
      string uwgdnnzODt;
      string xPtuZEIYxp;
      string PWNdFHdjya;
      string PCcUTaXxgF;
      string MxmjursFLP;
      string sItsPYhDYf;
      string KOQcdtmZby;
      string fKqqcRjdhM;
      string OXYigGIiEu;
      string sTYBuxgKFA;
      if(UcFhISDyEj == uwgdnnzODt){ESdMihRCQx = true;}
      else if(uwgdnnzODt == UcFhISDyEj){JLJNQdRTyh = true;}
      if(XiNIzdpEuN == xPtuZEIYxp){nEULRlphuX = true;}
      else if(xPtuZEIYxp == XiNIzdpEuN){OiXpJWVRNa = true;}
      if(ZczJXLJSEM == PWNdFHdjya){lEUfFMlpwe = true;}
      else if(PWNdFHdjya == ZczJXLJSEM){EoUuXuXFrV = true;}
      if(huVVkliLic == PCcUTaXxgF){kZXgIutMzz = true;}
      else if(PCcUTaXxgF == huVVkliLic){gDThGBOrWs = true;}
      if(lbhmIInEqi == MxmjursFLP){nFSGGozNjI = true;}
      else if(MxmjursFLP == lbhmIInEqi){UqrjrOYOTf = true;}
      if(SUhfrrcuKx == sItsPYhDYf){HzOhOAxxGW = true;}
      else if(sItsPYhDYf == SUhfrrcuKx){qgTTmUpNpV = true;}
      if(JjtqCcMrWN == KOQcdtmZby){wbGkMOfmDV = true;}
      else if(KOQcdtmZby == JjtqCcMrWN){FLabBLPojH = true;}
      if(ueVSbxtMAO == fKqqcRjdhM){rdhuifkOZQ = true;}
      if(WEaUsMMpds == OXYigGIiEu){NYGnXlKpSH = true;}
      if(ImBkTBhqjf == sTYBuxgKFA){xwFcDMzhtq = true;}
      while(fKqqcRjdhM == ueVSbxtMAO){IduTGNwjDJ = true;}
      while(OXYigGIiEu == OXYigGIiEu){VJlLezjAul = true;}
      while(sTYBuxgKFA == sTYBuxgKFA){LACBmIPPig = true;}
      if(ESdMihRCQx == true){ESdMihRCQx = false;}
      if(nEULRlphuX == true){nEULRlphuX = false;}
      if(lEUfFMlpwe == true){lEUfFMlpwe = false;}
      if(kZXgIutMzz == true){kZXgIutMzz = false;}
      if(nFSGGozNjI == true){nFSGGozNjI = false;}
      if(HzOhOAxxGW == true){HzOhOAxxGW = false;}
      if(wbGkMOfmDV == true){wbGkMOfmDV = false;}
      if(rdhuifkOZQ == true){rdhuifkOZQ = false;}
      if(NYGnXlKpSH == true){NYGnXlKpSH = false;}
      if(xwFcDMzhtq == true){xwFcDMzhtq = false;}
      if(JLJNQdRTyh == true){JLJNQdRTyh = false;}
      if(OiXpJWVRNa == true){OiXpJWVRNa = false;}
      if(EoUuXuXFrV == true){EoUuXuXFrV = false;}
      if(gDThGBOrWs == true){gDThGBOrWs = false;}
      if(UqrjrOYOTf == true){UqrjrOYOTf = false;}
      if(qgTTmUpNpV == true){qgTTmUpNpV = false;}
      if(FLabBLPojH == true){FLabBLPojH = false;}
      if(IduTGNwjDJ == true){IduTGNwjDJ = false;}
      if(VJlLezjAul == true){VJlLezjAul = false;}
      if(LACBmIPPig == true){LACBmIPPig = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XHEVDGXMFI
{ 
  void uiTaLOnXZA()
  { 
      bool AuIpdlnJyn = false;
      bool mJJWbeRrxh = false;
      bool esTiwPAxuR = false;
      bool yfDDJSgGDp = false;
      bool SqwxmoGKiJ = false;
      bool xmaMNHbZtN = false;
      bool kpOfoGGGNJ = false;
      bool xLnHOnwVwG = false;
      bool JpOkTLFpoC = false;
      bool qHMpEbbPHf = false;
      bool izxYMlzTyZ = false;
      bool KFdmEubcMd = false;
      bool BPQKRoyyCl = false;
      bool LfNPXJsoXh = false;
      bool LlqPrldYkJ = false;
      bool AzDdeSilHX = false;
      bool mBQLNeqOPt = false;
      bool BmEdROXASf = false;
      bool LYMslMbjjE = false;
      bool ZGhAtKUfCM = false;
      string TlRXAycBFn;
      string xkoiqolKQd;
      string gHCHiAxhjW;
      string yrKdMnShnM;
      string NXXiEVCykc;
      string hUVnBLiKnA;
      string AtRipEZLWD;
      string WDWEPJjTCN;
      string yywHocWWbA;
      string EIsnMSGnrz;
      string uqbgFeyRXr;
      string bPHaCCyKtM;
      string hDiVzOJirx;
      string DuaCRGWPBJ;
      string eEyjYnASkJ;
      string UwtfQqHGhp;
      string VPZZofnFJu;
      string fhIjgcEywK;
      string OpxhcGBukZ;
      string yPhKnPeXus;
      if(TlRXAycBFn == uqbgFeyRXr){AuIpdlnJyn = true;}
      else if(uqbgFeyRXr == TlRXAycBFn){izxYMlzTyZ = true;}
      if(xkoiqolKQd == bPHaCCyKtM){mJJWbeRrxh = true;}
      else if(bPHaCCyKtM == xkoiqolKQd){KFdmEubcMd = true;}
      if(gHCHiAxhjW == hDiVzOJirx){esTiwPAxuR = true;}
      else if(hDiVzOJirx == gHCHiAxhjW){BPQKRoyyCl = true;}
      if(yrKdMnShnM == DuaCRGWPBJ){yfDDJSgGDp = true;}
      else if(DuaCRGWPBJ == yrKdMnShnM){LfNPXJsoXh = true;}
      if(NXXiEVCykc == eEyjYnASkJ){SqwxmoGKiJ = true;}
      else if(eEyjYnASkJ == NXXiEVCykc){LlqPrldYkJ = true;}
      if(hUVnBLiKnA == UwtfQqHGhp){xmaMNHbZtN = true;}
      else if(UwtfQqHGhp == hUVnBLiKnA){AzDdeSilHX = true;}
      if(AtRipEZLWD == VPZZofnFJu){kpOfoGGGNJ = true;}
      else if(VPZZofnFJu == AtRipEZLWD){mBQLNeqOPt = true;}
      if(WDWEPJjTCN == fhIjgcEywK){xLnHOnwVwG = true;}
      if(yywHocWWbA == OpxhcGBukZ){JpOkTLFpoC = true;}
      if(EIsnMSGnrz == yPhKnPeXus){qHMpEbbPHf = true;}
      while(fhIjgcEywK == WDWEPJjTCN){BmEdROXASf = true;}
      while(OpxhcGBukZ == OpxhcGBukZ){LYMslMbjjE = true;}
      while(yPhKnPeXus == yPhKnPeXus){ZGhAtKUfCM = true;}
      if(AuIpdlnJyn == true){AuIpdlnJyn = false;}
      if(mJJWbeRrxh == true){mJJWbeRrxh = false;}
      if(esTiwPAxuR == true){esTiwPAxuR = false;}
      if(yfDDJSgGDp == true){yfDDJSgGDp = false;}
      if(SqwxmoGKiJ == true){SqwxmoGKiJ = false;}
      if(xmaMNHbZtN == true){xmaMNHbZtN = false;}
      if(kpOfoGGGNJ == true){kpOfoGGGNJ = false;}
      if(xLnHOnwVwG == true){xLnHOnwVwG = false;}
      if(JpOkTLFpoC == true){JpOkTLFpoC = false;}
      if(qHMpEbbPHf == true){qHMpEbbPHf = false;}
      if(izxYMlzTyZ == true){izxYMlzTyZ = false;}
      if(KFdmEubcMd == true){KFdmEubcMd = false;}
      if(BPQKRoyyCl == true){BPQKRoyyCl = false;}
      if(LfNPXJsoXh == true){LfNPXJsoXh = false;}
      if(LlqPrldYkJ == true){LlqPrldYkJ = false;}
      if(AzDdeSilHX == true){AzDdeSilHX = false;}
      if(mBQLNeqOPt == true){mBQLNeqOPt = false;}
      if(BmEdROXASf == true){BmEdROXASf = false;}
      if(LYMslMbjjE == true){LYMslMbjjE = false;}
      if(ZGhAtKUfCM == true){ZGhAtKUfCM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ORUPJKQGAT
{ 
  void oFdhflZWQd()
  { 
      bool yMrKgFVeCG = false;
      bool LmyRWbGshW = false;
      bool LnotBcwmoR = false;
      bool hhJQabgaGP = false;
      bool CeOSqXhlKJ = false;
      bool GiIYPKXxID = false;
      bool JhpkXdcgpu = false;
      bool uflRTfZWCc = false;
      bool uJbeKzYkAQ = false;
      bool DiRDFTodtN = false;
      bool tBwPOawpEj = false;
      bool jBtfIAFLZX = false;
      bool ErfYqLNhMA = false;
      bool qubohsNMPi = false;
      bool DhfQfCnltF = false;
      bool NcDVIBUWXD = false;
      bool NNdDroYFxO = false;
      bool lsupUVMOro = false;
      bool WbnGmNqFff = false;
      bool XpoMVoEbYq = false;
      string CAbPeMqelq;
      string aXcrUFCmTt;
      string PbcxkYWcsR;
      string AlggMgKIrP;
      string QroKXthOKX;
      string LtRIgZWddG;
      string pNkTqnquen;
      string uttEdWlSZq;
      string pHRVFFUXAm;
      string JfdlYCHUSj;
      string DmjWbRzMeK;
      string nEEmPhwPOk;
      string SSurePQHeb;
      string PQzpnDXutm;
      string FIspyEaqWq;
      string GqGhQkrqqL;
      string BrgDtWFOyM;
      string JAVaeJYEsZ;
      string nYknUXKQYD;
      string LfDhlNbpub;
      if(CAbPeMqelq == DmjWbRzMeK){yMrKgFVeCG = true;}
      else if(DmjWbRzMeK == CAbPeMqelq){tBwPOawpEj = true;}
      if(aXcrUFCmTt == nEEmPhwPOk){LmyRWbGshW = true;}
      else if(nEEmPhwPOk == aXcrUFCmTt){jBtfIAFLZX = true;}
      if(PbcxkYWcsR == SSurePQHeb){LnotBcwmoR = true;}
      else if(SSurePQHeb == PbcxkYWcsR){ErfYqLNhMA = true;}
      if(AlggMgKIrP == PQzpnDXutm){hhJQabgaGP = true;}
      else if(PQzpnDXutm == AlggMgKIrP){qubohsNMPi = true;}
      if(QroKXthOKX == FIspyEaqWq){CeOSqXhlKJ = true;}
      else if(FIspyEaqWq == QroKXthOKX){DhfQfCnltF = true;}
      if(LtRIgZWddG == GqGhQkrqqL){GiIYPKXxID = true;}
      else if(GqGhQkrqqL == LtRIgZWddG){NcDVIBUWXD = true;}
      if(pNkTqnquen == BrgDtWFOyM){JhpkXdcgpu = true;}
      else if(BrgDtWFOyM == pNkTqnquen){NNdDroYFxO = true;}
      if(uttEdWlSZq == JAVaeJYEsZ){uflRTfZWCc = true;}
      if(pHRVFFUXAm == nYknUXKQYD){uJbeKzYkAQ = true;}
      if(JfdlYCHUSj == LfDhlNbpub){DiRDFTodtN = true;}
      while(JAVaeJYEsZ == uttEdWlSZq){lsupUVMOro = true;}
      while(nYknUXKQYD == nYknUXKQYD){WbnGmNqFff = true;}
      while(LfDhlNbpub == LfDhlNbpub){XpoMVoEbYq = true;}
      if(yMrKgFVeCG == true){yMrKgFVeCG = false;}
      if(LmyRWbGshW == true){LmyRWbGshW = false;}
      if(LnotBcwmoR == true){LnotBcwmoR = false;}
      if(hhJQabgaGP == true){hhJQabgaGP = false;}
      if(CeOSqXhlKJ == true){CeOSqXhlKJ = false;}
      if(GiIYPKXxID == true){GiIYPKXxID = false;}
      if(JhpkXdcgpu == true){JhpkXdcgpu = false;}
      if(uflRTfZWCc == true){uflRTfZWCc = false;}
      if(uJbeKzYkAQ == true){uJbeKzYkAQ = false;}
      if(DiRDFTodtN == true){DiRDFTodtN = false;}
      if(tBwPOawpEj == true){tBwPOawpEj = false;}
      if(jBtfIAFLZX == true){jBtfIAFLZX = false;}
      if(ErfYqLNhMA == true){ErfYqLNhMA = false;}
      if(qubohsNMPi == true){qubohsNMPi = false;}
      if(DhfQfCnltF == true){DhfQfCnltF = false;}
      if(NcDVIBUWXD == true){NcDVIBUWXD = false;}
      if(NNdDroYFxO == true){NNdDroYFxO = false;}
      if(lsupUVMOro == true){lsupUVMOro = false;}
      if(WbnGmNqFff == true){WbnGmNqFff = false;}
      if(XpoMVoEbYq == true){XpoMVoEbYq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JJSKFBYRLH
{ 
  void UHqIWtzgAz()
  { 
      bool QAtwWblzed = false;
      bool BhGLWxaejd = false;
      bool GruXJtUXCM = false;
      bool AOsPKaJdWp = false;
      bool RKPOIzLfJe = false;
      bool odebSYFWlb = false;
      bool HOwSclnpAw = false;
      bool mxHtMubfPJ = false;
      bool ioNXWVjRwl = false;
      bool VmquiDOwkV = false;
      bool LVeNqrWkPW = false;
      bool wYGbsRAYwG = false;
      bool CWsOZAGMKI = false;
      bool geutyNKAfd = false;
      bool zyCZowfOBR = false;
      bool CpAdSobQmq = false;
      bool lKZGpQdMdf = false;
      bool GzsRHDTTYd = false;
      bool UqKsFqdQaJ = false;
      bool ksNnroYwiY = false;
      string OfsTLNhJpk;
      string JEdHTEYASG;
      string dgjQaRwseX;
      string IfcVdqhsoc;
      string TGFdHGfFuj;
      string MatyBgwbrs;
      string RneSbcbIcb;
      string VfKpmWaFJU;
      string lpxtKgldTw;
      string uGAwLeamCd;
      string dWcTOgPDLd;
      string FpSXHapjIt;
      string qxogfPfOeH;
      string unDepPNdfc;
      string RhSoqEmbnj;
      string oqdHmfhumz;
      string ABYDiQmmhr;
      string MMEecJezob;
      string bDZtSEKurJ;
      string hRqgbQIPGZ;
      if(OfsTLNhJpk == dWcTOgPDLd){QAtwWblzed = true;}
      else if(dWcTOgPDLd == OfsTLNhJpk){LVeNqrWkPW = true;}
      if(JEdHTEYASG == FpSXHapjIt){BhGLWxaejd = true;}
      else if(FpSXHapjIt == JEdHTEYASG){wYGbsRAYwG = true;}
      if(dgjQaRwseX == qxogfPfOeH){GruXJtUXCM = true;}
      else if(qxogfPfOeH == dgjQaRwseX){CWsOZAGMKI = true;}
      if(IfcVdqhsoc == unDepPNdfc){AOsPKaJdWp = true;}
      else if(unDepPNdfc == IfcVdqhsoc){geutyNKAfd = true;}
      if(TGFdHGfFuj == RhSoqEmbnj){RKPOIzLfJe = true;}
      else if(RhSoqEmbnj == TGFdHGfFuj){zyCZowfOBR = true;}
      if(MatyBgwbrs == oqdHmfhumz){odebSYFWlb = true;}
      else if(oqdHmfhumz == MatyBgwbrs){CpAdSobQmq = true;}
      if(RneSbcbIcb == ABYDiQmmhr){HOwSclnpAw = true;}
      else if(ABYDiQmmhr == RneSbcbIcb){lKZGpQdMdf = true;}
      if(VfKpmWaFJU == MMEecJezob){mxHtMubfPJ = true;}
      if(lpxtKgldTw == bDZtSEKurJ){ioNXWVjRwl = true;}
      if(uGAwLeamCd == hRqgbQIPGZ){VmquiDOwkV = true;}
      while(MMEecJezob == VfKpmWaFJU){GzsRHDTTYd = true;}
      while(bDZtSEKurJ == bDZtSEKurJ){UqKsFqdQaJ = true;}
      while(hRqgbQIPGZ == hRqgbQIPGZ){ksNnroYwiY = true;}
      if(QAtwWblzed == true){QAtwWblzed = false;}
      if(BhGLWxaejd == true){BhGLWxaejd = false;}
      if(GruXJtUXCM == true){GruXJtUXCM = false;}
      if(AOsPKaJdWp == true){AOsPKaJdWp = false;}
      if(RKPOIzLfJe == true){RKPOIzLfJe = false;}
      if(odebSYFWlb == true){odebSYFWlb = false;}
      if(HOwSclnpAw == true){HOwSclnpAw = false;}
      if(mxHtMubfPJ == true){mxHtMubfPJ = false;}
      if(ioNXWVjRwl == true){ioNXWVjRwl = false;}
      if(VmquiDOwkV == true){VmquiDOwkV = false;}
      if(LVeNqrWkPW == true){LVeNqrWkPW = false;}
      if(wYGbsRAYwG == true){wYGbsRAYwG = false;}
      if(CWsOZAGMKI == true){CWsOZAGMKI = false;}
      if(geutyNKAfd == true){geutyNKAfd = false;}
      if(zyCZowfOBR == true){zyCZowfOBR = false;}
      if(CpAdSobQmq == true){CpAdSobQmq = false;}
      if(lKZGpQdMdf == true){lKZGpQdMdf = false;}
      if(GzsRHDTTYd == true){GzsRHDTTYd = false;}
      if(UqKsFqdQaJ == true){UqKsFqdQaJ = false;}
      if(ksNnroYwiY == true){ksNnroYwiY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JKPWYVMLGT
{ 
  void xolBhNOQQj()
  { 
      bool tXsFIRxNUG = false;
      bool NSkOojKDTG = false;
      bool ZgQdQemQtp = false;
      bool QoaJBuNVPp = false;
      bool SisLcQNgTO = false;
      bool XerBCMHOod = false;
      bool efTeoXrbNt = false;
      bool WnmcmpnEBz = false;
      bool QFxeRlxYGn = false;
      bool nyglLlPNWE = false;
      bool XlTZrjqOOL = false;
      bool YCNoMZinMC = false;
      bool ZSVYFXGARA = false;
      bool aZhwaekWmh = false;
      bool uiKtPlkrZk = false;
      bool DaBTeFQuUU = false;
      bool cpxNkyTQNh = false;
      bool oMBeHqHaJS = false;
      bool lOafxAYORV = false;
      bool OoCSFFlwJQ = false;
      string tVJMKUhVTK;
      string ybUAeukzQp;
      string WZTOcXqkZe;
      string cnMOrxHZcQ;
      string nOfVaSWOfW;
      string ZonmVTCtjl;
      string cwwogKOGHh;
      string mLWzBItxnJ;
      string BcFCEmzZrX;
      string uNopmrSqnQ;
      string EPGxiNSnkN;
      string ZEGakAqsjt;
      string KoNjlZVfLJ;
      string pDIXFkVHSp;
      string UKneypGOFm;
      string BYGtFOBWKI;
      string qlcbWVuiUz;
      string diasYzBikw;
      string THaYIQwORp;
      string izwJzihLHb;
      if(tVJMKUhVTK == EPGxiNSnkN){tXsFIRxNUG = true;}
      else if(EPGxiNSnkN == tVJMKUhVTK){XlTZrjqOOL = true;}
      if(ybUAeukzQp == ZEGakAqsjt){NSkOojKDTG = true;}
      else if(ZEGakAqsjt == ybUAeukzQp){YCNoMZinMC = true;}
      if(WZTOcXqkZe == KoNjlZVfLJ){ZgQdQemQtp = true;}
      else if(KoNjlZVfLJ == WZTOcXqkZe){ZSVYFXGARA = true;}
      if(cnMOrxHZcQ == pDIXFkVHSp){QoaJBuNVPp = true;}
      else if(pDIXFkVHSp == cnMOrxHZcQ){aZhwaekWmh = true;}
      if(nOfVaSWOfW == UKneypGOFm){SisLcQNgTO = true;}
      else if(UKneypGOFm == nOfVaSWOfW){uiKtPlkrZk = true;}
      if(ZonmVTCtjl == BYGtFOBWKI){XerBCMHOod = true;}
      else if(BYGtFOBWKI == ZonmVTCtjl){DaBTeFQuUU = true;}
      if(cwwogKOGHh == qlcbWVuiUz){efTeoXrbNt = true;}
      else if(qlcbWVuiUz == cwwogKOGHh){cpxNkyTQNh = true;}
      if(mLWzBItxnJ == diasYzBikw){WnmcmpnEBz = true;}
      if(BcFCEmzZrX == THaYIQwORp){QFxeRlxYGn = true;}
      if(uNopmrSqnQ == izwJzihLHb){nyglLlPNWE = true;}
      while(diasYzBikw == mLWzBItxnJ){oMBeHqHaJS = true;}
      while(THaYIQwORp == THaYIQwORp){lOafxAYORV = true;}
      while(izwJzihLHb == izwJzihLHb){OoCSFFlwJQ = true;}
      if(tXsFIRxNUG == true){tXsFIRxNUG = false;}
      if(NSkOojKDTG == true){NSkOojKDTG = false;}
      if(ZgQdQemQtp == true){ZgQdQemQtp = false;}
      if(QoaJBuNVPp == true){QoaJBuNVPp = false;}
      if(SisLcQNgTO == true){SisLcQNgTO = false;}
      if(XerBCMHOod == true){XerBCMHOod = false;}
      if(efTeoXrbNt == true){efTeoXrbNt = false;}
      if(WnmcmpnEBz == true){WnmcmpnEBz = false;}
      if(QFxeRlxYGn == true){QFxeRlxYGn = false;}
      if(nyglLlPNWE == true){nyglLlPNWE = false;}
      if(XlTZrjqOOL == true){XlTZrjqOOL = false;}
      if(YCNoMZinMC == true){YCNoMZinMC = false;}
      if(ZSVYFXGARA == true){ZSVYFXGARA = false;}
      if(aZhwaekWmh == true){aZhwaekWmh = false;}
      if(uiKtPlkrZk == true){uiKtPlkrZk = false;}
      if(DaBTeFQuUU == true){DaBTeFQuUU = false;}
      if(cpxNkyTQNh == true){cpxNkyTQNh = false;}
      if(oMBeHqHaJS == true){oMBeHqHaJS = false;}
      if(lOafxAYORV == true){lOafxAYORV = false;}
      if(OoCSFFlwJQ == true){OoCSFFlwJQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJCYWPZQJQ
{ 
  void MwqjDSJGjZ()
  { 
      bool jhBdsZwLSl = false;
      bool CqaQXibXrr = false;
      bool ZDRMYkuwlV = false;
      bool lJAZHDqpnP = false;
      bool rHNTxJGhsw = false;
      bool JzxGMgPnEH = false;
      bool dzZxzspAJT = false;
      bool rljcARpyPP = false;
      bool dNDoLmLsNa = false;
      bool nCkfkrhPTD = false;
      bool SFYYEXPUFu = false;
      bool qQXndQwjlM = false;
      bool gwmhfoADqI = false;
      bool iZeLxXoekm = false;
      bool XqnRiXewCU = false;
      bool wxdHWVRpsO = false;
      bool WLcxLRkLqF = false;
      bool bQyyooIVyI = false;
      bool KEBWMluXoa = false;
      bool GylWQMNpGR = false;
      string SkseJuEGfy;
      string lWiipLKnon;
      string EYZimeCVuN;
      string IWloRUoXxt;
      string GIVEyKQyqV;
      string VItXbtKJrd;
      string shLRoPktRV;
      string VlpuguCUkb;
      string NDeYqAbNNX;
      string JeeTBXwEOi;
      string ZWgVziSzpf;
      string qoYPPoDlZo;
      string mWgsLqHWsJ;
      string yyGBCqVIYH;
      string gcWgfTFODM;
      string UJdZwCpnJI;
      string buFggsiXNY;
      string StNRHJzzMr;
      string krTgonTfFA;
      string AhzQflXpzl;
      if(SkseJuEGfy == ZWgVziSzpf){jhBdsZwLSl = true;}
      else if(ZWgVziSzpf == SkseJuEGfy){SFYYEXPUFu = true;}
      if(lWiipLKnon == qoYPPoDlZo){CqaQXibXrr = true;}
      else if(qoYPPoDlZo == lWiipLKnon){qQXndQwjlM = true;}
      if(EYZimeCVuN == mWgsLqHWsJ){ZDRMYkuwlV = true;}
      else if(mWgsLqHWsJ == EYZimeCVuN){gwmhfoADqI = true;}
      if(IWloRUoXxt == yyGBCqVIYH){lJAZHDqpnP = true;}
      else if(yyGBCqVIYH == IWloRUoXxt){iZeLxXoekm = true;}
      if(GIVEyKQyqV == gcWgfTFODM){rHNTxJGhsw = true;}
      else if(gcWgfTFODM == GIVEyKQyqV){XqnRiXewCU = true;}
      if(VItXbtKJrd == UJdZwCpnJI){JzxGMgPnEH = true;}
      else if(UJdZwCpnJI == VItXbtKJrd){wxdHWVRpsO = true;}
      if(shLRoPktRV == buFggsiXNY){dzZxzspAJT = true;}
      else if(buFggsiXNY == shLRoPktRV){WLcxLRkLqF = true;}
      if(VlpuguCUkb == StNRHJzzMr){rljcARpyPP = true;}
      if(NDeYqAbNNX == krTgonTfFA){dNDoLmLsNa = true;}
      if(JeeTBXwEOi == AhzQflXpzl){nCkfkrhPTD = true;}
      while(StNRHJzzMr == VlpuguCUkb){bQyyooIVyI = true;}
      while(krTgonTfFA == krTgonTfFA){KEBWMluXoa = true;}
      while(AhzQflXpzl == AhzQflXpzl){GylWQMNpGR = true;}
      if(jhBdsZwLSl == true){jhBdsZwLSl = false;}
      if(CqaQXibXrr == true){CqaQXibXrr = false;}
      if(ZDRMYkuwlV == true){ZDRMYkuwlV = false;}
      if(lJAZHDqpnP == true){lJAZHDqpnP = false;}
      if(rHNTxJGhsw == true){rHNTxJGhsw = false;}
      if(JzxGMgPnEH == true){JzxGMgPnEH = false;}
      if(dzZxzspAJT == true){dzZxzspAJT = false;}
      if(rljcARpyPP == true){rljcARpyPP = false;}
      if(dNDoLmLsNa == true){dNDoLmLsNa = false;}
      if(nCkfkrhPTD == true){nCkfkrhPTD = false;}
      if(SFYYEXPUFu == true){SFYYEXPUFu = false;}
      if(qQXndQwjlM == true){qQXndQwjlM = false;}
      if(gwmhfoADqI == true){gwmhfoADqI = false;}
      if(iZeLxXoekm == true){iZeLxXoekm = false;}
      if(XqnRiXewCU == true){XqnRiXewCU = false;}
      if(wxdHWVRpsO == true){wxdHWVRpsO = false;}
      if(WLcxLRkLqF == true){WLcxLRkLqF = false;}
      if(bQyyooIVyI == true){bQyyooIVyI = false;}
      if(KEBWMluXoa == true){KEBWMluXoa = false;}
      if(GylWQMNpGR == true){GylWQMNpGR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BHYDUPRPUV
{ 
  void xSQHqqVNQC()
  { 
      bool NwaQmrFKot = false;
      bool OMuAthWnHj = false;
      bool OriCUlPKzV = false;
      bool iTHAuBAyFa = false;
      bool IMuSdHZbQH = false;
      bool ltyKSUNYuB = false;
      bool buKSLtFuEr = false;
      bool gYhgbBxQXN = false;
      bool LnsrjnVwgZ = false;
      bool nbCEzMCbGi = false;
      bool CeWXaNMQiR = false;
      bool XxAhomBSiW = false;
      bool YINdEFVcgO = false;
      bool zUJnKgQUQV = false;
      bool bEMPCqaUPL = false;
      bool KjrjKsQsTU = false;
      bool qiiUSCnLWI = false;
      bool WgBNuTuybM = false;
      bool dANVDPcYdQ = false;
      bool PXAwdrUrxz = false;
      string KHWpCbyiAh;
      string bVjVeEuwnC;
      string xrYimhmaYG;
      string FGFHsHBAxs;
      string kIgXPLnHfm;
      string BERtaSinDT;
      string nXJsbVQcbX;
      string DtytQnKBSb;
      string tetlFBnKga;
      string XMxdENynut;
      string tKeIiGFXdm;
      string HhUbYIcXna;
      string hGwBzpxToD;
      string oWFYgiAkCy;
      string uQfsSprVFw;
      string jazULnOdJr;
      string Jlhaykcuto;
      string IrUoeRZChJ;
      string yaOsSNWjMr;
      string TVbKoJhFug;
      if(KHWpCbyiAh == tKeIiGFXdm){NwaQmrFKot = true;}
      else if(tKeIiGFXdm == KHWpCbyiAh){CeWXaNMQiR = true;}
      if(bVjVeEuwnC == HhUbYIcXna){OMuAthWnHj = true;}
      else if(HhUbYIcXna == bVjVeEuwnC){XxAhomBSiW = true;}
      if(xrYimhmaYG == hGwBzpxToD){OriCUlPKzV = true;}
      else if(hGwBzpxToD == xrYimhmaYG){YINdEFVcgO = true;}
      if(FGFHsHBAxs == oWFYgiAkCy){iTHAuBAyFa = true;}
      else if(oWFYgiAkCy == FGFHsHBAxs){zUJnKgQUQV = true;}
      if(kIgXPLnHfm == uQfsSprVFw){IMuSdHZbQH = true;}
      else if(uQfsSprVFw == kIgXPLnHfm){bEMPCqaUPL = true;}
      if(BERtaSinDT == jazULnOdJr){ltyKSUNYuB = true;}
      else if(jazULnOdJr == BERtaSinDT){KjrjKsQsTU = true;}
      if(nXJsbVQcbX == Jlhaykcuto){buKSLtFuEr = true;}
      else if(Jlhaykcuto == nXJsbVQcbX){qiiUSCnLWI = true;}
      if(DtytQnKBSb == IrUoeRZChJ){gYhgbBxQXN = true;}
      if(tetlFBnKga == yaOsSNWjMr){LnsrjnVwgZ = true;}
      if(XMxdENynut == TVbKoJhFug){nbCEzMCbGi = true;}
      while(IrUoeRZChJ == DtytQnKBSb){WgBNuTuybM = true;}
      while(yaOsSNWjMr == yaOsSNWjMr){dANVDPcYdQ = true;}
      while(TVbKoJhFug == TVbKoJhFug){PXAwdrUrxz = true;}
      if(NwaQmrFKot == true){NwaQmrFKot = false;}
      if(OMuAthWnHj == true){OMuAthWnHj = false;}
      if(OriCUlPKzV == true){OriCUlPKzV = false;}
      if(iTHAuBAyFa == true){iTHAuBAyFa = false;}
      if(IMuSdHZbQH == true){IMuSdHZbQH = false;}
      if(ltyKSUNYuB == true){ltyKSUNYuB = false;}
      if(buKSLtFuEr == true){buKSLtFuEr = false;}
      if(gYhgbBxQXN == true){gYhgbBxQXN = false;}
      if(LnsrjnVwgZ == true){LnsrjnVwgZ = false;}
      if(nbCEzMCbGi == true){nbCEzMCbGi = false;}
      if(CeWXaNMQiR == true){CeWXaNMQiR = false;}
      if(XxAhomBSiW == true){XxAhomBSiW = false;}
      if(YINdEFVcgO == true){YINdEFVcgO = false;}
      if(zUJnKgQUQV == true){zUJnKgQUQV = false;}
      if(bEMPCqaUPL == true){bEMPCqaUPL = false;}
      if(KjrjKsQsTU == true){KjrjKsQsTU = false;}
      if(qiiUSCnLWI == true){qiiUSCnLWI = false;}
      if(WgBNuTuybM == true){WgBNuTuybM = false;}
      if(dANVDPcYdQ == true){dANVDPcYdQ = false;}
      if(PXAwdrUrxz == true){PXAwdrUrxz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TGBSZSQYFJ
{ 
  void SVCIYDYWUI()
  { 
      bool IKukhPapPY = false;
      bool cxKIcJZqSy = false;
      bool umJShGLQUb = false;
      bool ixrEURdjii = false;
      bool cEXzEslXea = false;
      bool uhGCBVAcDa = false;
      bool EJUnoeEFmK = false;
      bool epIjVpPKOo = false;
      bool UmksgBqoDz = false;
      bool QBfHdSjjJZ = false;
      bool nfjTwFZVgK = false;
      bool GoOOGQYaHn = false;
      bool mOBmsdJAGC = false;
      bool FfBoAoCQxa = false;
      bool bUIssblRBM = false;
      bool sJcVlZdxZR = false;
      bool uYPdEZnZOQ = false;
      bool NHcfLSGItR = false;
      bool rqzsJwDeCa = false;
      bool KFpffDEenS = false;
      string hHAVssSjaU;
      string olGblBEoXN;
      string rlFiqQVqNa;
      string PGHzRMzGsV;
      string rGWeFtuLYa;
      string CXNrqwBRdb;
      string WbWzEhdGJY;
      string CxwCVlOacx;
      string VKSlYqrOIU;
      string KgbQyPjWZW;
      string PnBAYEaLWE;
      string hangGMJkaN;
      string oPxoNUUfDF;
      string CqAFggIRMU;
      string QgqDmjruKl;
      string GywMhAqMlE;
      string iuIRCpahzY;
      string DqXGxIXsBd;
      string bZVQyDumXg;
      string pwfHkUYZBw;
      if(hHAVssSjaU == PnBAYEaLWE){IKukhPapPY = true;}
      else if(PnBAYEaLWE == hHAVssSjaU){nfjTwFZVgK = true;}
      if(olGblBEoXN == hangGMJkaN){cxKIcJZqSy = true;}
      else if(hangGMJkaN == olGblBEoXN){GoOOGQYaHn = true;}
      if(rlFiqQVqNa == oPxoNUUfDF){umJShGLQUb = true;}
      else if(oPxoNUUfDF == rlFiqQVqNa){mOBmsdJAGC = true;}
      if(PGHzRMzGsV == CqAFggIRMU){ixrEURdjii = true;}
      else if(CqAFggIRMU == PGHzRMzGsV){FfBoAoCQxa = true;}
      if(rGWeFtuLYa == QgqDmjruKl){cEXzEslXea = true;}
      else if(QgqDmjruKl == rGWeFtuLYa){bUIssblRBM = true;}
      if(CXNrqwBRdb == GywMhAqMlE){uhGCBVAcDa = true;}
      else if(GywMhAqMlE == CXNrqwBRdb){sJcVlZdxZR = true;}
      if(WbWzEhdGJY == iuIRCpahzY){EJUnoeEFmK = true;}
      else if(iuIRCpahzY == WbWzEhdGJY){uYPdEZnZOQ = true;}
      if(CxwCVlOacx == DqXGxIXsBd){epIjVpPKOo = true;}
      if(VKSlYqrOIU == bZVQyDumXg){UmksgBqoDz = true;}
      if(KgbQyPjWZW == pwfHkUYZBw){QBfHdSjjJZ = true;}
      while(DqXGxIXsBd == CxwCVlOacx){NHcfLSGItR = true;}
      while(bZVQyDumXg == bZVQyDumXg){rqzsJwDeCa = true;}
      while(pwfHkUYZBw == pwfHkUYZBw){KFpffDEenS = true;}
      if(IKukhPapPY == true){IKukhPapPY = false;}
      if(cxKIcJZqSy == true){cxKIcJZqSy = false;}
      if(umJShGLQUb == true){umJShGLQUb = false;}
      if(ixrEURdjii == true){ixrEURdjii = false;}
      if(cEXzEslXea == true){cEXzEslXea = false;}
      if(uhGCBVAcDa == true){uhGCBVAcDa = false;}
      if(EJUnoeEFmK == true){EJUnoeEFmK = false;}
      if(epIjVpPKOo == true){epIjVpPKOo = false;}
      if(UmksgBqoDz == true){UmksgBqoDz = false;}
      if(QBfHdSjjJZ == true){QBfHdSjjJZ = false;}
      if(nfjTwFZVgK == true){nfjTwFZVgK = false;}
      if(GoOOGQYaHn == true){GoOOGQYaHn = false;}
      if(mOBmsdJAGC == true){mOBmsdJAGC = false;}
      if(FfBoAoCQxa == true){FfBoAoCQxa = false;}
      if(bUIssblRBM == true){bUIssblRBM = false;}
      if(sJcVlZdxZR == true){sJcVlZdxZR = false;}
      if(uYPdEZnZOQ == true){uYPdEZnZOQ = false;}
      if(NHcfLSGItR == true){NHcfLSGItR = false;}
      if(rqzsJwDeCa == true){rqzsJwDeCa = false;}
      if(KFpffDEenS == true){KFpffDEenS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SEONJIKDLR
{ 
  void jeauMCTCSJ()
  { 
      bool BworFaKyCW = false;
      bool jJEXnkkzch = false;
      bool hxUeZMAcuF = false;
      bool jybpACVbwG = false;
      bool PzGHCByWsF = false;
      bool uuSRhEbJRr = false;
      bool ZgDxllgOXl = false;
      bool OJCVRipMcY = false;
      bool OdipJoeKHu = false;
      bool ZLJDgiwJVQ = false;
      bool TjyHpkrxzz = false;
      bool NPgrdwxNmx = false;
      bool HWGcLDzzoi = false;
      bool lgpMEdebzY = false;
      bool whKHgKdQZj = false;
      bool kiVYIwcVwl = false;
      bool ksHQMgYUnz = false;
      bool RUNOAZMyuA = false;
      bool ZiZExDKRDI = false;
      bool BIfNmCZtuA = false;
      string UsZqtFkAAI;
      string HFPZurqUVE;
      string nSfiFqCNNc;
      string xMfQMYTeNB;
      string LodWXGWaHH;
      string bJrICBMqkC;
      string DXmXLuYzNW;
      string XMHUsynJKz;
      string UaGFAmTXNK;
      string LcsKxnCGLc;
      string gXNkiOBXPE;
      string NDgkhcRgWX;
      string aBkDKuSwWE;
      string ugxgSwMVVl;
      string luHIwIwIcU;
      string WVinCelKZn;
      string uFBKIfGzSk;
      string PuLkletbGC;
      string zKTBhZxIem;
      string KCuhpgtwAQ;
      if(UsZqtFkAAI == gXNkiOBXPE){BworFaKyCW = true;}
      else if(gXNkiOBXPE == UsZqtFkAAI){TjyHpkrxzz = true;}
      if(HFPZurqUVE == NDgkhcRgWX){jJEXnkkzch = true;}
      else if(NDgkhcRgWX == HFPZurqUVE){NPgrdwxNmx = true;}
      if(nSfiFqCNNc == aBkDKuSwWE){hxUeZMAcuF = true;}
      else if(aBkDKuSwWE == nSfiFqCNNc){HWGcLDzzoi = true;}
      if(xMfQMYTeNB == ugxgSwMVVl){jybpACVbwG = true;}
      else if(ugxgSwMVVl == xMfQMYTeNB){lgpMEdebzY = true;}
      if(LodWXGWaHH == luHIwIwIcU){PzGHCByWsF = true;}
      else if(luHIwIwIcU == LodWXGWaHH){whKHgKdQZj = true;}
      if(bJrICBMqkC == WVinCelKZn){uuSRhEbJRr = true;}
      else if(WVinCelKZn == bJrICBMqkC){kiVYIwcVwl = true;}
      if(DXmXLuYzNW == uFBKIfGzSk){ZgDxllgOXl = true;}
      else if(uFBKIfGzSk == DXmXLuYzNW){ksHQMgYUnz = true;}
      if(XMHUsynJKz == PuLkletbGC){OJCVRipMcY = true;}
      if(UaGFAmTXNK == zKTBhZxIem){OdipJoeKHu = true;}
      if(LcsKxnCGLc == KCuhpgtwAQ){ZLJDgiwJVQ = true;}
      while(PuLkletbGC == XMHUsynJKz){RUNOAZMyuA = true;}
      while(zKTBhZxIem == zKTBhZxIem){ZiZExDKRDI = true;}
      while(KCuhpgtwAQ == KCuhpgtwAQ){BIfNmCZtuA = true;}
      if(BworFaKyCW == true){BworFaKyCW = false;}
      if(jJEXnkkzch == true){jJEXnkkzch = false;}
      if(hxUeZMAcuF == true){hxUeZMAcuF = false;}
      if(jybpACVbwG == true){jybpACVbwG = false;}
      if(PzGHCByWsF == true){PzGHCByWsF = false;}
      if(uuSRhEbJRr == true){uuSRhEbJRr = false;}
      if(ZgDxllgOXl == true){ZgDxllgOXl = false;}
      if(OJCVRipMcY == true){OJCVRipMcY = false;}
      if(OdipJoeKHu == true){OdipJoeKHu = false;}
      if(ZLJDgiwJVQ == true){ZLJDgiwJVQ = false;}
      if(TjyHpkrxzz == true){TjyHpkrxzz = false;}
      if(NPgrdwxNmx == true){NPgrdwxNmx = false;}
      if(HWGcLDzzoi == true){HWGcLDzzoi = false;}
      if(lgpMEdebzY == true){lgpMEdebzY = false;}
      if(whKHgKdQZj == true){whKHgKdQZj = false;}
      if(kiVYIwcVwl == true){kiVYIwcVwl = false;}
      if(ksHQMgYUnz == true){ksHQMgYUnz = false;}
      if(RUNOAZMyuA == true){RUNOAZMyuA = false;}
      if(ZiZExDKRDI == true){ZiZExDKRDI = false;}
      if(BIfNmCZtuA == true){BIfNmCZtuA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IUHSDABNAC
{ 
  void NwPMrRMxTz()
  { 
      bool VqiwJxeNGz = false;
      bool ooPFpSfWJf = false;
      bool rRDCtSeUmn = false;
      bool lOVIbkVUwN = false;
      bool rNegQmMEGK = false;
      bool tGtdaEngCp = false;
      bool SKaRNZTGdF = false;
      bool wLZumelWkG = false;
      bool GZNbseUqhW = false;
      bool woRFthlMSq = false;
      bool SGZANhfyqw = false;
      bool RRwujswzYh = false;
      bool EcXHJHsUAE = false;
      bool rZDsnzzMOL = false;
      bool zWAlEerWVA = false;
      bool lmnjlphSqG = false;
      bool nLxlEqNCHj = false;
      bool tjkMihblDd = false;
      bool OWyASElTGx = false;
      bool RfUHWnYNhM = false;
      string QlhgeJMryA;
      string VnkXJZMpob;
      string DnOZxzRTUI;
      string IIEIrFPzSK;
      string kClzuiooeg;
      string jEQLXcXIje;
      string qsWpqMjbfE;
      string KMWdqABOdN;
      string KconYErsjO;
      string hGOmTqfuHi;
      string zMIZWWgmTX;
      string aIeWUOEiRm;
      string TqrQWDyjKz;
      string UGGuNxTOQB;
      string XFYMnYarSE;
      string mxdUOHUrDS;
      string YxbUDUCjIW;
      string uoRPOOSecx;
      string bFQFLXbkfG;
      string cbKxcacDJT;
      if(QlhgeJMryA == zMIZWWgmTX){VqiwJxeNGz = true;}
      else if(zMIZWWgmTX == QlhgeJMryA){SGZANhfyqw = true;}
      if(VnkXJZMpob == aIeWUOEiRm){ooPFpSfWJf = true;}
      else if(aIeWUOEiRm == VnkXJZMpob){RRwujswzYh = true;}
      if(DnOZxzRTUI == TqrQWDyjKz){rRDCtSeUmn = true;}
      else if(TqrQWDyjKz == DnOZxzRTUI){EcXHJHsUAE = true;}
      if(IIEIrFPzSK == UGGuNxTOQB){lOVIbkVUwN = true;}
      else if(UGGuNxTOQB == IIEIrFPzSK){rZDsnzzMOL = true;}
      if(kClzuiooeg == XFYMnYarSE){rNegQmMEGK = true;}
      else if(XFYMnYarSE == kClzuiooeg){zWAlEerWVA = true;}
      if(jEQLXcXIje == mxdUOHUrDS){tGtdaEngCp = true;}
      else if(mxdUOHUrDS == jEQLXcXIje){lmnjlphSqG = true;}
      if(qsWpqMjbfE == YxbUDUCjIW){SKaRNZTGdF = true;}
      else if(YxbUDUCjIW == qsWpqMjbfE){nLxlEqNCHj = true;}
      if(KMWdqABOdN == uoRPOOSecx){wLZumelWkG = true;}
      if(KconYErsjO == bFQFLXbkfG){GZNbseUqhW = true;}
      if(hGOmTqfuHi == cbKxcacDJT){woRFthlMSq = true;}
      while(uoRPOOSecx == KMWdqABOdN){tjkMihblDd = true;}
      while(bFQFLXbkfG == bFQFLXbkfG){OWyASElTGx = true;}
      while(cbKxcacDJT == cbKxcacDJT){RfUHWnYNhM = true;}
      if(VqiwJxeNGz == true){VqiwJxeNGz = false;}
      if(ooPFpSfWJf == true){ooPFpSfWJf = false;}
      if(rRDCtSeUmn == true){rRDCtSeUmn = false;}
      if(lOVIbkVUwN == true){lOVIbkVUwN = false;}
      if(rNegQmMEGK == true){rNegQmMEGK = false;}
      if(tGtdaEngCp == true){tGtdaEngCp = false;}
      if(SKaRNZTGdF == true){SKaRNZTGdF = false;}
      if(wLZumelWkG == true){wLZumelWkG = false;}
      if(GZNbseUqhW == true){GZNbseUqhW = false;}
      if(woRFthlMSq == true){woRFthlMSq = false;}
      if(SGZANhfyqw == true){SGZANhfyqw = false;}
      if(RRwujswzYh == true){RRwujswzYh = false;}
      if(EcXHJHsUAE == true){EcXHJHsUAE = false;}
      if(rZDsnzzMOL == true){rZDsnzzMOL = false;}
      if(zWAlEerWVA == true){zWAlEerWVA = false;}
      if(lmnjlphSqG == true){lmnjlphSqG = false;}
      if(nLxlEqNCHj == true){nLxlEqNCHj = false;}
      if(tjkMihblDd == true){tjkMihblDd = false;}
      if(OWyASElTGx == true){OWyASElTGx = false;}
      if(RfUHWnYNhM == true){RfUHWnYNhM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IUKFLQMOPK
{ 
  void CaMtcuQoiw()
  { 
      bool pTWLhDsPfe = false;
      bool abZbWdTCkl = false;
      bool NdqfgRgGiS = false;
      bool aPWPyrHAHa = false;
      bool EtTszWbpPz = false;
      bool GGmaILbpeQ = false;
      bool WlfMDLEJde = false;
      bool VSuKhSJyfJ = false;
      bool opqiMTbuGl = false;
      bool PRVpERNGon = false;
      bool SRMkdnLcsp = false;
      bool BdKVafuxAi = false;
      bool iIDrOEwEFP = false;
      bool FDIrqXdGFX = false;
      bool IzBQjlGAOY = false;
      bool VQGFEJOUVZ = false;
      bool qGWckyVSdD = false;
      bool BnrcajGmHb = false;
      bool xwogtnwCmg = false;
      bool IIjefCbYek = false;
      string KOIkkPyUCE;
      string bbQJDFwMux;
      string BnNRAreJGB;
      string NAIUZXaMaT;
      string bPaPcNoZCH;
      string AWMTEWBpks;
      string koNApaSwie;
      string djlaUkMyol;
      string DEGzBqnnPD;
      string WjbgilBaYC;
      string urqXcPjkzS;
      string JDBypgiOyz;
      string megfHtHEri;
      string jlYmqKNhVl;
      string GCowsThcqC;
      string DlbYOQLLPi;
      string IfsQiWdOGe;
      string TAsMsjojln;
      string LdMpexJAXa;
      string yBSlcZJYMV;
      if(KOIkkPyUCE == urqXcPjkzS){pTWLhDsPfe = true;}
      else if(urqXcPjkzS == KOIkkPyUCE){SRMkdnLcsp = true;}
      if(bbQJDFwMux == JDBypgiOyz){abZbWdTCkl = true;}
      else if(JDBypgiOyz == bbQJDFwMux){BdKVafuxAi = true;}
      if(BnNRAreJGB == megfHtHEri){NdqfgRgGiS = true;}
      else if(megfHtHEri == BnNRAreJGB){iIDrOEwEFP = true;}
      if(NAIUZXaMaT == jlYmqKNhVl){aPWPyrHAHa = true;}
      else if(jlYmqKNhVl == NAIUZXaMaT){FDIrqXdGFX = true;}
      if(bPaPcNoZCH == GCowsThcqC){EtTszWbpPz = true;}
      else if(GCowsThcqC == bPaPcNoZCH){IzBQjlGAOY = true;}
      if(AWMTEWBpks == DlbYOQLLPi){GGmaILbpeQ = true;}
      else if(DlbYOQLLPi == AWMTEWBpks){VQGFEJOUVZ = true;}
      if(koNApaSwie == IfsQiWdOGe){WlfMDLEJde = true;}
      else if(IfsQiWdOGe == koNApaSwie){qGWckyVSdD = true;}
      if(djlaUkMyol == TAsMsjojln){VSuKhSJyfJ = true;}
      if(DEGzBqnnPD == LdMpexJAXa){opqiMTbuGl = true;}
      if(WjbgilBaYC == yBSlcZJYMV){PRVpERNGon = true;}
      while(TAsMsjojln == djlaUkMyol){BnrcajGmHb = true;}
      while(LdMpexJAXa == LdMpexJAXa){xwogtnwCmg = true;}
      while(yBSlcZJYMV == yBSlcZJYMV){IIjefCbYek = true;}
      if(pTWLhDsPfe == true){pTWLhDsPfe = false;}
      if(abZbWdTCkl == true){abZbWdTCkl = false;}
      if(NdqfgRgGiS == true){NdqfgRgGiS = false;}
      if(aPWPyrHAHa == true){aPWPyrHAHa = false;}
      if(EtTszWbpPz == true){EtTszWbpPz = false;}
      if(GGmaILbpeQ == true){GGmaILbpeQ = false;}
      if(WlfMDLEJde == true){WlfMDLEJde = false;}
      if(VSuKhSJyfJ == true){VSuKhSJyfJ = false;}
      if(opqiMTbuGl == true){opqiMTbuGl = false;}
      if(PRVpERNGon == true){PRVpERNGon = false;}
      if(SRMkdnLcsp == true){SRMkdnLcsp = false;}
      if(BdKVafuxAi == true){BdKVafuxAi = false;}
      if(iIDrOEwEFP == true){iIDrOEwEFP = false;}
      if(FDIrqXdGFX == true){FDIrqXdGFX = false;}
      if(IzBQjlGAOY == true){IzBQjlGAOY = false;}
      if(VQGFEJOUVZ == true){VQGFEJOUVZ = false;}
      if(qGWckyVSdD == true){qGWckyVSdD = false;}
      if(BnrcajGmHb == true){BnrcajGmHb = false;}
      if(xwogtnwCmg == true){xwogtnwCmg = false;}
      if(IIjefCbYek == true){IIjefCbYek = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SWVEUPNYDR
{ 
  void EDyEQZlsyd()
  { 
      bool NfcYImGhSG = false;
      bool RhrmJqVaVA = false;
      bool rCXnXywLEg = false;
      bool umkpbzadkm = false;
      bool YZGfBMlrZK = false;
      bool KftzdKHoAJ = false;
      bool qudkKdxCKK = false;
      bool QrpiaSwrlK = false;
      bool MDksWPskMR = false;
      bool qkcawdwUUW = false;
      bool PihPtRoKYL = false;
      bool NPDpxnKjNt = false;
      bool kLpsTfPPmx = false;
      bool VaXOtcVVyF = false;
      bool ahMBDbhlcH = false;
      bool TLGZlDsnwO = false;
      bool CYXbolqnuT = false;
      bool SnkITDzooq = false;
      bool xclecKUxcq = false;
      bool jgZjCBJkLR = false;
      string PqdFVzZbbH;
      string WtXJSLYaTn;
      string laBkgpNZTm;
      string ONcNHOqEFl;
      string zfiszFroKg;
      string EoibTnpsXe;
      string lzInsJRJBD;
      string UUUgoFrHlb;
      string xXPliYdAsS;
      string YyfZAzXuAo;
      string mimHMjTBmN;
      string wiGwhNjVFT;
      string eRPheWnufp;
      string hwGwoOjIZy;
      string FbNeVoqjrm;
      string OCogJVSFbp;
      string uYUxfAbKGT;
      string dbuHNDDjMo;
      string fDCsafHYlS;
      string uefjCfHQzV;
      if(PqdFVzZbbH == mimHMjTBmN){NfcYImGhSG = true;}
      else if(mimHMjTBmN == PqdFVzZbbH){PihPtRoKYL = true;}
      if(WtXJSLYaTn == wiGwhNjVFT){RhrmJqVaVA = true;}
      else if(wiGwhNjVFT == WtXJSLYaTn){NPDpxnKjNt = true;}
      if(laBkgpNZTm == eRPheWnufp){rCXnXywLEg = true;}
      else if(eRPheWnufp == laBkgpNZTm){kLpsTfPPmx = true;}
      if(ONcNHOqEFl == hwGwoOjIZy){umkpbzadkm = true;}
      else if(hwGwoOjIZy == ONcNHOqEFl){VaXOtcVVyF = true;}
      if(zfiszFroKg == FbNeVoqjrm){YZGfBMlrZK = true;}
      else if(FbNeVoqjrm == zfiszFroKg){ahMBDbhlcH = true;}
      if(EoibTnpsXe == OCogJVSFbp){KftzdKHoAJ = true;}
      else if(OCogJVSFbp == EoibTnpsXe){TLGZlDsnwO = true;}
      if(lzInsJRJBD == uYUxfAbKGT){qudkKdxCKK = true;}
      else if(uYUxfAbKGT == lzInsJRJBD){CYXbolqnuT = true;}
      if(UUUgoFrHlb == dbuHNDDjMo){QrpiaSwrlK = true;}
      if(xXPliYdAsS == fDCsafHYlS){MDksWPskMR = true;}
      if(YyfZAzXuAo == uefjCfHQzV){qkcawdwUUW = true;}
      while(dbuHNDDjMo == UUUgoFrHlb){SnkITDzooq = true;}
      while(fDCsafHYlS == fDCsafHYlS){xclecKUxcq = true;}
      while(uefjCfHQzV == uefjCfHQzV){jgZjCBJkLR = true;}
      if(NfcYImGhSG == true){NfcYImGhSG = false;}
      if(RhrmJqVaVA == true){RhrmJqVaVA = false;}
      if(rCXnXywLEg == true){rCXnXywLEg = false;}
      if(umkpbzadkm == true){umkpbzadkm = false;}
      if(YZGfBMlrZK == true){YZGfBMlrZK = false;}
      if(KftzdKHoAJ == true){KftzdKHoAJ = false;}
      if(qudkKdxCKK == true){qudkKdxCKK = false;}
      if(QrpiaSwrlK == true){QrpiaSwrlK = false;}
      if(MDksWPskMR == true){MDksWPskMR = false;}
      if(qkcawdwUUW == true){qkcawdwUUW = false;}
      if(PihPtRoKYL == true){PihPtRoKYL = false;}
      if(NPDpxnKjNt == true){NPDpxnKjNt = false;}
      if(kLpsTfPPmx == true){kLpsTfPPmx = false;}
      if(VaXOtcVVyF == true){VaXOtcVVyF = false;}
      if(ahMBDbhlcH == true){ahMBDbhlcH = false;}
      if(TLGZlDsnwO == true){TLGZlDsnwO = false;}
      if(CYXbolqnuT == true){CYXbolqnuT = false;}
      if(SnkITDzooq == true){SnkITDzooq = false;}
      if(xclecKUxcq == true){xclecKUxcq = false;}
      if(jgZjCBJkLR == true){jgZjCBJkLR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RSKAPISYGC
{ 
  void ZiBdGEbaJL()
  { 
      bool NOCgCHmEnu = false;
      bool GqkfGkDdEy = false;
      bool IfucUqLJhK = false;
      bool pkmRVTASeu = false;
      bool xxnfLfXGou = false;
      bool TGoPygSZMK = false;
      bool udWcEVDSKl = false;
      bool kkyIAKrPQn = false;
      bool TFTmqiuXSn = false;
      bool AZFUATaKao = false;
      bool bEuDJhHgOm = false;
      bool nDIXqoJjlU = false;
      bool ZfAWkKedIg = false;
      bool jhnaLOJQcI = false;
      bool bOIezxRgcK = false;
      bool JqYFPwEYRz = false;
      bool DcYgDGOgLb = false;
      bool fsGcsKWUWn = false;
      bool ryAxXrIiLP = false;
      bool KjycFzpabr = false;
      string SAJOKBEOlr;
      string NxhtyoUtQz;
      string bPQzpzNddu;
      string ixycCNOWpJ;
      string hRsnJRusFj;
      string lfDgVDjJYK;
      string nZjqJQyFqj;
      string ZyEGRKWbpY;
      string EUXtICsRHz;
      string dFxeVIhBds;
      string SoBVJnbwPK;
      string gHTAGSBoiH;
      string WgxqFUAYjI;
      string cUywFOSCkT;
      string ZwBwSWlxYC;
      string GrSVVlrJPo;
      string nDLGhLIWuq;
      string AzEOhaeBYi;
      string iCzhCjCbaS;
      string WImufWjtNH;
      if(SAJOKBEOlr == SoBVJnbwPK){NOCgCHmEnu = true;}
      else if(SoBVJnbwPK == SAJOKBEOlr){bEuDJhHgOm = true;}
      if(NxhtyoUtQz == gHTAGSBoiH){GqkfGkDdEy = true;}
      else if(gHTAGSBoiH == NxhtyoUtQz){nDIXqoJjlU = true;}
      if(bPQzpzNddu == WgxqFUAYjI){IfucUqLJhK = true;}
      else if(WgxqFUAYjI == bPQzpzNddu){ZfAWkKedIg = true;}
      if(ixycCNOWpJ == cUywFOSCkT){pkmRVTASeu = true;}
      else if(cUywFOSCkT == ixycCNOWpJ){jhnaLOJQcI = true;}
      if(hRsnJRusFj == ZwBwSWlxYC){xxnfLfXGou = true;}
      else if(ZwBwSWlxYC == hRsnJRusFj){bOIezxRgcK = true;}
      if(lfDgVDjJYK == GrSVVlrJPo){TGoPygSZMK = true;}
      else if(GrSVVlrJPo == lfDgVDjJYK){JqYFPwEYRz = true;}
      if(nZjqJQyFqj == nDLGhLIWuq){udWcEVDSKl = true;}
      else if(nDLGhLIWuq == nZjqJQyFqj){DcYgDGOgLb = true;}
      if(ZyEGRKWbpY == AzEOhaeBYi){kkyIAKrPQn = true;}
      if(EUXtICsRHz == iCzhCjCbaS){TFTmqiuXSn = true;}
      if(dFxeVIhBds == WImufWjtNH){AZFUATaKao = true;}
      while(AzEOhaeBYi == ZyEGRKWbpY){fsGcsKWUWn = true;}
      while(iCzhCjCbaS == iCzhCjCbaS){ryAxXrIiLP = true;}
      while(WImufWjtNH == WImufWjtNH){KjycFzpabr = true;}
      if(NOCgCHmEnu == true){NOCgCHmEnu = false;}
      if(GqkfGkDdEy == true){GqkfGkDdEy = false;}
      if(IfucUqLJhK == true){IfucUqLJhK = false;}
      if(pkmRVTASeu == true){pkmRVTASeu = false;}
      if(xxnfLfXGou == true){xxnfLfXGou = false;}
      if(TGoPygSZMK == true){TGoPygSZMK = false;}
      if(udWcEVDSKl == true){udWcEVDSKl = false;}
      if(kkyIAKrPQn == true){kkyIAKrPQn = false;}
      if(TFTmqiuXSn == true){TFTmqiuXSn = false;}
      if(AZFUATaKao == true){AZFUATaKao = false;}
      if(bEuDJhHgOm == true){bEuDJhHgOm = false;}
      if(nDIXqoJjlU == true){nDIXqoJjlU = false;}
      if(ZfAWkKedIg == true){ZfAWkKedIg = false;}
      if(jhnaLOJQcI == true){jhnaLOJQcI = false;}
      if(bOIezxRgcK == true){bOIezxRgcK = false;}
      if(JqYFPwEYRz == true){JqYFPwEYRz = false;}
      if(DcYgDGOgLb == true){DcYgDGOgLb = false;}
      if(fsGcsKWUWn == true){fsGcsKWUWn = false;}
      if(ryAxXrIiLP == true){ryAxXrIiLP = false;}
      if(KjycFzpabr == true){KjycFzpabr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GIMCWBXUQM
{ 
  void KwbDEuQnEX()
  { 
      bool ogBqkADeoX = false;
      bool etulumNjGm = false;
      bool CIgjonjGHT = false;
      bool RpZrMDLPOc = false;
      bool SVYLjGwDxO = false;
      bool ThYhAfzQBx = false;
      bool QwWVGnTCYr = false;
      bool ayVdTgjUAi = false;
      bool qfJrziRqrf = false;
      bool EtNRMWyCFu = false;
      bool msdFnVMtOT = false;
      bool wdQSFjldVW = false;
      bool WbKsnfjDQw = false;
      bool hgPEwyBEEd = false;
      bool WWcYjZcuLb = false;
      bool jUghYKikRH = false;
      bool kIcRkONMWH = false;
      bool ihZqAzzlJN = false;
      bool CoroMNAhel = false;
      bool PPlxsNsLmU = false;
      string zZZZEUXIih;
      string uztlQzCGXu;
      string tQBaNPbmuG;
      string VERDiNHZDZ;
      string OqbElQIyFG;
      string pLARmhYyLo;
      string sjNbLqhqDD;
      string qcDyfDoxnx;
      string HdgnPJEzPA;
      string nIOOgdcAru;
      string hQtCONIBkj;
      string sbKNgODZLB;
      string miaDOiNnRC;
      string ZoEsOpidYC;
      string BCNfHMyAhR;
      string ZDnpIzoqnf;
      string ATjiJDWRzp;
      string fZAJAjUuuB;
      string jNGAcWAOjO;
      string ArpsBgSeVD;
      if(zZZZEUXIih == hQtCONIBkj){ogBqkADeoX = true;}
      else if(hQtCONIBkj == zZZZEUXIih){msdFnVMtOT = true;}
      if(uztlQzCGXu == sbKNgODZLB){etulumNjGm = true;}
      else if(sbKNgODZLB == uztlQzCGXu){wdQSFjldVW = true;}
      if(tQBaNPbmuG == miaDOiNnRC){CIgjonjGHT = true;}
      else if(miaDOiNnRC == tQBaNPbmuG){WbKsnfjDQw = true;}
      if(VERDiNHZDZ == ZoEsOpidYC){RpZrMDLPOc = true;}
      else if(ZoEsOpidYC == VERDiNHZDZ){hgPEwyBEEd = true;}
      if(OqbElQIyFG == BCNfHMyAhR){SVYLjGwDxO = true;}
      else if(BCNfHMyAhR == OqbElQIyFG){WWcYjZcuLb = true;}
      if(pLARmhYyLo == ZDnpIzoqnf){ThYhAfzQBx = true;}
      else if(ZDnpIzoqnf == pLARmhYyLo){jUghYKikRH = true;}
      if(sjNbLqhqDD == ATjiJDWRzp){QwWVGnTCYr = true;}
      else if(ATjiJDWRzp == sjNbLqhqDD){kIcRkONMWH = true;}
      if(qcDyfDoxnx == fZAJAjUuuB){ayVdTgjUAi = true;}
      if(HdgnPJEzPA == jNGAcWAOjO){qfJrziRqrf = true;}
      if(nIOOgdcAru == ArpsBgSeVD){EtNRMWyCFu = true;}
      while(fZAJAjUuuB == qcDyfDoxnx){ihZqAzzlJN = true;}
      while(jNGAcWAOjO == jNGAcWAOjO){CoroMNAhel = true;}
      while(ArpsBgSeVD == ArpsBgSeVD){PPlxsNsLmU = true;}
      if(ogBqkADeoX == true){ogBqkADeoX = false;}
      if(etulumNjGm == true){etulumNjGm = false;}
      if(CIgjonjGHT == true){CIgjonjGHT = false;}
      if(RpZrMDLPOc == true){RpZrMDLPOc = false;}
      if(SVYLjGwDxO == true){SVYLjGwDxO = false;}
      if(ThYhAfzQBx == true){ThYhAfzQBx = false;}
      if(QwWVGnTCYr == true){QwWVGnTCYr = false;}
      if(ayVdTgjUAi == true){ayVdTgjUAi = false;}
      if(qfJrziRqrf == true){qfJrziRqrf = false;}
      if(EtNRMWyCFu == true){EtNRMWyCFu = false;}
      if(msdFnVMtOT == true){msdFnVMtOT = false;}
      if(wdQSFjldVW == true){wdQSFjldVW = false;}
      if(WbKsnfjDQw == true){WbKsnfjDQw = false;}
      if(hgPEwyBEEd == true){hgPEwyBEEd = false;}
      if(WWcYjZcuLb == true){WWcYjZcuLb = false;}
      if(jUghYKikRH == true){jUghYKikRH = false;}
      if(kIcRkONMWH == true){kIcRkONMWH = false;}
      if(ihZqAzzlJN == true){ihZqAzzlJN = false;}
      if(CoroMNAhel == true){CoroMNAhel = false;}
      if(PPlxsNsLmU == true){PPlxsNsLmU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GHCDPTDJWW
{ 
  void DzRELSBLYa()
  { 
      bool FjXudQaKnj = false;
      bool bDECuqySmK = false;
      bool uqGocMMWji = false;
      bool nCoUQSgMHL = false;
      bool DaKJDaeyzo = false;
      bool DAFbONdhRR = false;
      bool DDZEwZNjkc = false;
      bool JkLaHUfxlC = false;
      bool gNWuemxMFC = false;
      bool oyuoIzAFMd = false;
      bool NuNWfSndUs = false;
      bool ggwPjofeYI = false;
      bool bAdhmKoVSH = false;
      bool TajHnlAzOM = false;
      bool ySrMUICfFS = false;
      bool SVgDBMQeiU = false;
      bool cSKNYGwnay = false;
      bool ngPMJJIRMe = false;
      bool IJQznytgGb = false;
      bool UVQtifHdmN = false;
      string npBXiPihpA;
      string UzWLpiYTXq;
      string kPjDbVefjb;
      string dBVeHPVLkY;
      string TFiqrCaIQB;
      string GCNsqYGywN;
      string kCxOWTdqDa;
      string MMiyWefrKZ;
      string tWPiUbmcni;
      string IXPWnQHUUY;
      string XjEpnsSOVM;
      string rNmWSOmNst;
      string fBDURnxLKG;
      string XLXlBKSYub;
      string IXHapukrDZ;
      string dsaZrVfiYz;
      string uGEOnfoAUI;
      string uNSQkHtbeW;
      string DEIkbdkyse;
      string eiAufCTrmJ;
      if(npBXiPihpA == XjEpnsSOVM){FjXudQaKnj = true;}
      else if(XjEpnsSOVM == npBXiPihpA){NuNWfSndUs = true;}
      if(UzWLpiYTXq == rNmWSOmNst){bDECuqySmK = true;}
      else if(rNmWSOmNst == UzWLpiYTXq){ggwPjofeYI = true;}
      if(kPjDbVefjb == fBDURnxLKG){uqGocMMWji = true;}
      else if(fBDURnxLKG == kPjDbVefjb){bAdhmKoVSH = true;}
      if(dBVeHPVLkY == XLXlBKSYub){nCoUQSgMHL = true;}
      else if(XLXlBKSYub == dBVeHPVLkY){TajHnlAzOM = true;}
      if(TFiqrCaIQB == IXHapukrDZ){DaKJDaeyzo = true;}
      else if(IXHapukrDZ == TFiqrCaIQB){ySrMUICfFS = true;}
      if(GCNsqYGywN == dsaZrVfiYz){DAFbONdhRR = true;}
      else if(dsaZrVfiYz == GCNsqYGywN){SVgDBMQeiU = true;}
      if(kCxOWTdqDa == uGEOnfoAUI){DDZEwZNjkc = true;}
      else if(uGEOnfoAUI == kCxOWTdqDa){cSKNYGwnay = true;}
      if(MMiyWefrKZ == uNSQkHtbeW){JkLaHUfxlC = true;}
      if(tWPiUbmcni == DEIkbdkyse){gNWuemxMFC = true;}
      if(IXPWnQHUUY == eiAufCTrmJ){oyuoIzAFMd = true;}
      while(uNSQkHtbeW == MMiyWefrKZ){ngPMJJIRMe = true;}
      while(DEIkbdkyse == DEIkbdkyse){IJQznytgGb = true;}
      while(eiAufCTrmJ == eiAufCTrmJ){UVQtifHdmN = true;}
      if(FjXudQaKnj == true){FjXudQaKnj = false;}
      if(bDECuqySmK == true){bDECuqySmK = false;}
      if(uqGocMMWji == true){uqGocMMWji = false;}
      if(nCoUQSgMHL == true){nCoUQSgMHL = false;}
      if(DaKJDaeyzo == true){DaKJDaeyzo = false;}
      if(DAFbONdhRR == true){DAFbONdhRR = false;}
      if(DDZEwZNjkc == true){DDZEwZNjkc = false;}
      if(JkLaHUfxlC == true){JkLaHUfxlC = false;}
      if(gNWuemxMFC == true){gNWuemxMFC = false;}
      if(oyuoIzAFMd == true){oyuoIzAFMd = false;}
      if(NuNWfSndUs == true){NuNWfSndUs = false;}
      if(ggwPjofeYI == true){ggwPjofeYI = false;}
      if(bAdhmKoVSH == true){bAdhmKoVSH = false;}
      if(TajHnlAzOM == true){TajHnlAzOM = false;}
      if(ySrMUICfFS == true){ySrMUICfFS = false;}
      if(SVgDBMQeiU == true){SVgDBMQeiU = false;}
      if(cSKNYGwnay == true){cSKNYGwnay = false;}
      if(ngPMJJIRMe == true){ngPMJJIRMe = false;}
      if(IJQznytgGb == true){IJQznytgGb = false;}
      if(UVQtifHdmN == true){UVQtifHdmN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QQMRLLSAWM
{ 
  void tBuGVZwyAa()
  { 
      bool UMklKhsrlO = false;
      bool qaUGpqgoHF = false;
      bool fORVdclPJn = false;
      bool LCKlNVJREm = false;
      bool NjKCIfjISn = false;
      bool yexCXGtPHh = false;
      bool wcixDoQhsU = false;
      bool gPkTquDPMy = false;
      bool rdxUofEHOG = false;
      bool asKVqjBMzT = false;
      bool PCPyHisdKb = false;
      bool CeDJoRfOIW = false;
      bool jISlsmEObH = false;
      bool tpPshpOyNF = false;
      bool mawlEupAgZ = false;
      bool DmEbiGicET = false;
      bool edBDhLOKay = false;
      bool DgBCjJLghy = false;
      bool xEhCDHlnJa = false;
      bool HkttaIZsEr = false;
      string aIYrnGdKmr;
      string pHrnMhIZPt;
      string UFzLkPeSQX;
      string dxxwDDIfkR;
      string zTEFuyeALd;
      string QBKemUINGY;
      string bKtONsJwkI;
      string ZbnytAAtPm;
      string jdGlHclSIh;
      string ttZMpnZoqC;
      string ohOCEnMMjm;
      string UOxSnxEHHk;
      string GpnDOeCbHF;
      string ZKDNyCPDhS;
      string QZiUNfwGXr;
      string jShGuytKnY;
      string ljEdMJLjUl;
      string hBYoTgHSph;
      string huDOVHcwRz;
      string HEOJffUFID;
      if(aIYrnGdKmr == ohOCEnMMjm){UMklKhsrlO = true;}
      else if(ohOCEnMMjm == aIYrnGdKmr){PCPyHisdKb = true;}
      if(pHrnMhIZPt == UOxSnxEHHk){qaUGpqgoHF = true;}
      else if(UOxSnxEHHk == pHrnMhIZPt){CeDJoRfOIW = true;}
      if(UFzLkPeSQX == GpnDOeCbHF){fORVdclPJn = true;}
      else if(GpnDOeCbHF == UFzLkPeSQX){jISlsmEObH = true;}
      if(dxxwDDIfkR == ZKDNyCPDhS){LCKlNVJREm = true;}
      else if(ZKDNyCPDhS == dxxwDDIfkR){tpPshpOyNF = true;}
      if(zTEFuyeALd == QZiUNfwGXr){NjKCIfjISn = true;}
      else if(QZiUNfwGXr == zTEFuyeALd){mawlEupAgZ = true;}
      if(QBKemUINGY == jShGuytKnY){yexCXGtPHh = true;}
      else if(jShGuytKnY == QBKemUINGY){DmEbiGicET = true;}
      if(bKtONsJwkI == ljEdMJLjUl){wcixDoQhsU = true;}
      else if(ljEdMJLjUl == bKtONsJwkI){edBDhLOKay = true;}
      if(ZbnytAAtPm == hBYoTgHSph){gPkTquDPMy = true;}
      if(jdGlHclSIh == huDOVHcwRz){rdxUofEHOG = true;}
      if(ttZMpnZoqC == HEOJffUFID){asKVqjBMzT = true;}
      while(hBYoTgHSph == ZbnytAAtPm){DgBCjJLghy = true;}
      while(huDOVHcwRz == huDOVHcwRz){xEhCDHlnJa = true;}
      while(HEOJffUFID == HEOJffUFID){HkttaIZsEr = true;}
      if(UMklKhsrlO == true){UMklKhsrlO = false;}
      if(qaUGpqgoHF == true){qaUGpqgoHF = false;}
      if(fORVdclPJn == true){fORVdclPJn = false;}
      if(LCKlNVJREm == true){LCKlNVJREm = false;}
      if(NjKCIfjISn == true){NjKCIfjISn = false;}
      if(yexCXGtPHh == true){yexCXGtPHh = false;}
      if(wcixDoQhsU == true){wcixDoQhsU = false;}
      if(gPkTquDPMy == true){gPkTquDPMy = false;}
      if(rdxUofEHOG == true){rdxUofEHOG = false;}
      if(asKVqjBMzT == true){asKVqjBMzT = false;}
      if(PCPyHisdKb == true){PCPyHisdKb = false;}
      if(CeDJoRfOIW == true){CeDJoRfOIW = false;}
      if(jISlsmEObH == true){jISlsmEObH = false;}
      if(tpPshpOyNF == true){tpPshpOyNF = false;}
      if(mawlEupAgZ == true){mawlEupAgZ = false;}
      if(DmEbiGicET == true){DmEbiGicET = false;}
      if(edBDhLOKay == true){edBDhLOKay = false;}
      if(DgBCjJLghy == true){DgBCjJLghy = false;}
      if(xEhCDHlnJa == true){xEhCDHlnJa = false;}
      if(HkttaIZsEr == true){HkttaIZsEr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KOYQHXNUJJ
{ 
  void FQdnnVGtzP()
  { 
      bool BTkEWipllQ = false;
      bool drxzCwzFET = false;
      bool oZdFULFzAK = false;
      bool bmfewNrwiX = false;
      bool TRwzUerWuK = false;
      bool oqGIiapfjK = false;
      bool dqkbnpLRCn = false;
      bool EDVgAWcekp = false;
      bool ShDpUkgXuV = false;
      bool XMMXsbfUKd = false;
      bool SaTHGkUYIL = false;
      bool xKtsrwnuHD = false;
      bool JnVgPqqxnX = false;
      bool qITGXrOwji = false;
      bool PHPiXMRSfx = false;
      bool nkMGUdElqO = false;
      bool tWkjUnqnVz = false;
      bool grKXmBXmIC = false;
      bool ZXQpjFuMls = false;
      bool nbEVorWfNj = false;
      string obxExWCJTa;
      string OcUCOBOZWC;
      string iWBXyuOeMG;
      string xkEZZQnaOZ;
      string dQsExXIzEu;
      string gJmDsSaZFC;
      string HWxMccXtcy;
      string MnKxYRcwZa;
      string lOaRYnxBgG;
      string oOUMRGTgaU;
      string zNWGhsypda;
      string oezePswfmo;
      string fWNVIxSxeR;
      string xwUFaXqTif;
      string pHXFRKOoxY;
      string KnslocABxk;
      string ZALLdrJtEr;
      string BbxHzXzHEy;
      string hcAGGJDiQy;
      string WpWyGowLbY;
      if(obxExWCJTa == zNWGhsypda){BTkEWipllQ = true;}
      else if(zNWGhsypda == obxExWCJTa){SaTHGkUYIL = true;}
      if(OcUCOBOZWC == oezePswfmo){drxzCwzFET = true;}
      else if(oezePswfmo == OcUCOBOZWC){xKtsrwnuHD = true;}
      if(iWBXyuOeMG == fWNVIxSxeR){oZdFULFzAK = true;}
      else if(fWNVIxSxeR == iWBXyuOeMG){JnVgPqqxnX = true;}
      if(xkEZZQnaOZ == xwUFaXqTif){bmfewNrwiX = true;}
      else if(xwUFaXqTif == xkEZZQnaOZ){qITGXrOwji = true;}
      if(dQsExXIzEu == pHXFRKOoxY){TRwzUerWuK = true;}
      else if(pHXFRKOoxY == dQsExXIzEu){PHPiXMRSfx = true;}
      if(gJmDsSaZFC == KnslocABxk){oqGIiapfjK = true;}
      else if(KnslocABxk == gJmDsSaZFC){nkMGUdElqO = true;}
      if(HWxMccXtcy == ZALLdrJtEr){dqkbnpLRCn = true;}
      else if(ZALLdrJtEr == HWxMccXtcy){tWkjUnqnVz = true;}
      if(MnKxYRcwZa == BbxHzXzHEy){EDVgAWcekp = true;}
      if(lOaRYnxBgG == hcAGGJDiQy){ShDpUkgXuV = true;}
      if(oOUMRGTgaU == WpWyGowLbY){XMMXsbfUKd = true;}
      while(BbxHzXzHEy == MnKxYRcwZa){grKXmBXmIC = true;}
      while(hcAGGJDiQy == hcAGGJDiQy){ZXQpjFuMls = true;}
      while(WpWyGowLbY == WpWyGowLbY){nbEVorWfNj = true;}
      if(BTkEWipllQ == true){BTkEWipllQ = false;}
      if(drxzCwzFET == true){drxzCwzFET = false;}
      if(oZdFULFzAK == true){oZdFULFzAK = false;}
      if(bmfewNrwiX == true){bmfewNrwiX = false;}
      if(TRwzUerWuK == true){TRwzUerWuK = false;}
      if(oqGIiapfjK == true){oqGIiapfjK = false;}
      if(dqkbnpLRCn == true){dqkbnpLRCn = false;}
      if(EDVgAWcekp == true){EDVgAWcekp = false;}
      if(ShDpUkgXuV == true){ShDpUkgXuV = false;}
      if(XMMXsbfUKd == true){XMMXsbfUKd = false;}
      if(SaTHGkUYIL == true){SaTHGkUYIL = false;}
      if(xKtsrwnuHD == true){xKtsrwnuHD = false;}
      if(JnVgPqqxnX == true){JnVgPqqxnX = false;}
      if(qITGXrOwji == true){qITGXrOwji = false;}
      if(PHPiXMRSfx == true){PHPiXMRSfx = false;}
      if(nkMGUdElqO == true){nkMGUdElqO = false;}
      if(tWkjUnqnVz == true){tWkjUnqnVz = false;}
      if(grKXmBXmIC == true){grKXmBXmIC = false;}
      if(ZXQpjFuMls == true){ZXQpjFuMls = false;}
      if(nbEVorWfNj == true){nbEVorWfNj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYWMFJJSDA
{ 
  void rFdsXnfBNO()
  { 
      bool iHgNpNkYVe = false;
      bool HZYkzsEkCU = false;
      bool hyhNSnIGAI = false;
      bool LNeAKnqkjC = false;
      bool yJfRrCYtsG = false;
      bool zWziGjZTtB = false;
      bool EdYNTtuXZL = false;
      bool BTBAVYSQUQ = false;
      bool PNNtInOwta = false;
      bool OXqhxUkRyy = false;
      bool GAThEfUzMh = false;
      bool RIydlpQdEe = false;
      bool fzdzxccSCB = false;
      bool mASVJOsfoc = false;
      bool TOiMIFZMwG = false;
      bool EGMSSHWUjb = false;
      bool DCwKtQpcUW = false;
      bool wjobLQPQpq = false;
      bool DPVuxfmzCB = false;
      bool qYuNYQRYRr = false;
      string hRlDgbuDIW;
      string uBegwLFIZt;
      string fInigMHZtn;
      string faLEEyPDJu;
      string XjKxEzakGZ;
      string lKsGVYcDVT;
      string UUJTqTpZby;
      string uBydVuyqdh;
      string lVTTCUhFif;
      string UMhpaDapFj;
      string IAJIekLOjZ;
      string ZlYmgyAoRV;
      string lkquciSHDS;
      string UIktYkLLoQ;
      string ISUIGimtIc;
      string CkYixXINeu;
      string RDLRERAeNu;
      string loAANSPios;
      string wXyZPjiBwA;
      string cxfszEHCDn;
      if(hRlDgbuDIW == IAJIekLOjZ){iHgNpNkYVe = true;}
      else if(IAJIekLOjZ == hRlDgbuDIW){GAThEfUzMh = true;}
      if(uBegwLFIZt == ZlYmgyAoRV){HZYkzsEkCU = true;}
      else if(ZlYmgyAoRV == uBegwLFIZt){RIydlpQdEe = true;}
      if(fInigMHZtn == lkquciSHDS){hyhNSnIGAI = true;}
      else if(lkquciSHDS == fInigMHZtn){fzdzxccSCB = true;}
      if(faLEEyPDJu == UIktYkLLoQ){LNeAKnqkjC = true;}
      else if(UIktYkLLoQ == faLEEyPDJu){mASVJOsfoc = true;}
      if(XjKxEzakGZ == ISUIGimtIc){yJfRrCYtsG = true;}
      else if(ISUIGimtIc == XjKxEzakGZ){TOiMIFZMwG = true;}
      if(lKsGVYcDVT == CkYixXINeu){zWziGjZTtB = true;}
      else if(CkYixXINeu == lKsGVYcDVT){EGMSSHWUjb = true;}
      if(UUJTqTpZby == RDLRERAeNu){EdYNTtuXZL = true;}
      else if(RDLRERAeNu == UUJTqTpZby){DCwKtQpcUW = true;}
      if(uBydVuyqdh == loAANSPios){BTBAVYSQUQ = true;}
      if(lVTTCUhFif == wXyZPjiBwA){PNNtInOwta = true;}
      if(UMhpaDapFj == cxfszEHCDn){OXqhxUkRyy = true;}
      while(loAANSPios == uBydVuyqdh){wjobLQPQpq = true;}
      while(wXyZPjiBwA == wXyZPjiBwA){DPVuxfmzCB = true;}
      while(cxfszEHCDn == cxfszEHCDn){qYuNYQRYRr = true;}
      if(iHgNpNkYVe == true){iHgNpNkYVe = false;}
      if(HZYkzsEkCU == true){HZYkzsEkCU = false;}
      if(hyhNSnIGAI == true){hyhNSnIGAI = false;}
      if(LNeAKnqkjC == true){LNeAKnqkjC = false;}
      if(yJfRrCYtsG == true){yJfRrCYtsG = false;}
      if(zWziGjZTtB == true){zWziGjZTtB = false;}
      if(EdYNTtuXZL == true){EdYNTtuXZL = false;}
      if(BTBAVYSQUQ == true){BTBAVYSQUQ = false;}
      if(PNNtInOwta == true){PNNtInOwta = false;}
      if(OXqhxUkRyy == true){OXqhxUkRyy = false;}
      if(GAThEfUzMh == true){GAThEfUzMh = false;}
      if(RIydlpQdEe == true){RIydlpQdEe = false;}
      if(fzdzxccSCB == true){fzdzxccSCB = false;}
      if(mASVJOsfoc == true){mASVJOsfoc = false;}
      if(TOiMIFZMwG == true){TOiMIFZMwG = false;}
      if(EGMSSHWUjb == true){EGMSSHWUjb = false;}
      if(DCwKtQpcUW == true){DCwKtQpcUW = false;}
      if(wjobLQPQpq == true){wjobLQPQpq = false;}
      if(DPVuxfmzCB == true){DPVuxfmzCB = false;}
      if(qYuNYQRYRr == true){qYuNYQRYRr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKFCCQMVFJ
{ 
  void BuDKNLJswj()
  { 
      bool rEkiQZdlGg = false;
      bool fGmKeLMhKu = false;
      bool VKXpbMjHeC = false;
      bool hQbMOcQGkU = false;
      bool CPTbliulHb = false;
      bool sqQEcgfuGD = false;
      bool pVGEyOeawB = false;
      bool tFworGqwDr = false;
      bool RyzDIqAWih = false;
      bool xVzgefJPcW = false;
      bool EToGhmtaLW = false;
      bool oiqNlqVDwH = false;
      bool OHrOEYGPKM = false;
      bool wbSgnxIsVU = false;
      bool wZLLrNdktm = false;
      bool JGSVHxbaBI = false;
      bool geQzaNQJZo = false;
      bool icgaKougWq = false;
      bool tUUWDpIxYp = false;
      bool UhrMnRILkd = false;
      string CRuuNgZNpr;
      string gZdBzWWfrX;
      string RoSUGKkMoJ;
      string bLIQPGohwl;
      string QqHwWPzUuL;
      string ybEQHNzaoD;
      string uMXfQVQMlr;
      string gniFHZhVxp;
      string LQQdLAGqJC;
      string HOssqDTafB;
      string ylhCeJryJh;
      string ecczqdwtUP;
      string OZDikSupOD;
      string GHpwqYhOzB;
      string HIgaWdksBM;
      string HZFPmYizRL;
      string NBjGbXlgIS;
      string wguTIGrbLG;
      string gCoBugBaIR;
      string pixmnGYazz;
      if(CRuuNgZNpr == ylhCeJryJh){rEkiQZdlGg = true;}
      else if(ylhCeJryJh == CRuuNgZNpr){EToGhmtaLW = true;}
      if(gZdBzWWfrX == ecczqdwtUP){fGmKeLMhKu = true;}
      else if(ecczqdwtUP == gZdBzWWfrX){oiqNlqVDwH = true;}
      if(RoSUGKkMoJ == OZDikSupOD){VKXpbMjHeC = true;}
      else if(OZDikSupOD == RoSUGKkMoJ){OHrOEYGPKM = true;}
      if(bLIQPGohwl == GHpwqYhOzB){hQbMOcQGkU = true;}
      else if(GHpwqYhOzB == bLIQPGohwl){wbSgnxIsVU = true;}
      if(QqHwWPzUuL == HIgaWdksBM){CPTbliulHb = true;}
      else if(HIgaWdksBM == QqHwWPzUuL){wZLLrNdktm = true;}
      if(ybEQHNzaoD == HZFPmYizRL){sqQEcgfuGD = true;}
      else if(HZFPmYizRL == ybEQHNzaoD){JGSVHxbaBI = true;}
      if(uMXfQVQMlr == NBjGbXlgIS){pVGEyOeawB = true;}
      else if(NBjGbXlgIS == uMXfQVQMlr){geQzaNQJZo = true;}
      if(gniFHZhVxp == wguTIGrbLG){tFworGqwDr = true;}
      if(LQQdLAGqJC == gCoBugBaIR){RyzDIqAWih = true;}
      if(HOssqDTafB == pixmnGYazz){xVzgefJPcW = true;}
      while(wguTIGrbLG == gniFHZhVxp){icgaKougWq = true;}
      while(gCoBugBaIR == gCoBugBaIR){tUUWDpIxYp = true;}
      while(pixmnGYazz == pixmnGYazz){UhrMnRILkd = true;}
      if(rEkiQZdlGg == true){rEkiQZdlGg = false;}
      if(fGmKeLMhKu == true){fGmKeLMhKu = false;}
      if(VKXpbMjHeC == true){VKXpbMjHeC = false;}
      if(hQbMOcQGkU == true){hQbMOcQGkU = false;}
      if(CPTbliulHb == true){CPTbliulHb = false;}
      if(sqQEcgfuGD == true){sqQEcgfuGD = false;}
      if(pVGEyOeawB == true){pVGEyOeawB = false;}
      if(tFworGqwDr == true){tFworGqwDr = false;}
      if(RyzDIqAWih == true){RyzDIqAWih = false;}
      if(xVzgefJPcW == true){xVzgefJPcW = false;}
      if(EToGhmtaLW == true){EToGhmtaLW = false;}
      if(oiqNlqVDwH == true){oiqNlqVDwH = false;}
      if(OHrOEYGPKM == true){OHrOEYGPKM = false;}
      if(wbSgnxIsVU == true){wbSgnxIsVU = false;}
      if(wZLLrNdktm == true){wZLLrNdktm = false;}
      if(JGSVHxbaBI == true){JGSVHxbaBI = false;}
      if(geQzaNQJZo == true){geQzaNQJZo = false;}
      if(icgaKougWq == true){icgaKougWq = false;}
      if(tUUWDpIxYp == true){tUUWDpIxYp = false;}
      if(UhrMnRILkd == true){UhrMnRILkd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TYUZQPXBCN
{ 
  void HqjkCBJOAn()
  { 
      bool zWrNfROPXk = false;
      bool NgNsZtXlEg = false;
      bool NooKLNFxey = false;
      bool DJnuZILLCT = false;
      bool lRGgMKBXdx = false;
      bool JSWUjKghCS = false;
      bool LQjZgDsSTQ = false;
      bool hLjjtwhIxA = false;
      bool LhShnjmSKP = false;
      bool bdJiIVggzJ = false;
      bool RiENPyiman = false;
      bool bYjBGcyCkx = false;
      bool QaHDoDCAbY = false;
      bool OAInicdFRp = false;
      bool AAqWmCsHbe = false;
      bool XewBrqaAXL = false;
      bool uiKBYaPwSd = false;
      bool zrjtxQijPl = false;
      bool JtYwBjEGuq = false;
      bool BdgFuRooyM = false;
      string oEwpELZnDO;
      string TEqntPlqOU;
      string JEynIXAWBU;
      string ixUesdGTPQ;
      string yPixzjKmbZ;
      string yOKmtjFHhf;
      string KCmifWiLuP;
      string JSaxWtUBnY;
      string NNuaVTmhkI;
      string XyljFwcAQc;
      string AyrLQfnMQA;
      string PETISxHLNL;
      string iBalrKgqqa;
      string RUjLYOUjKp;
      string eaQksSecQI;
      string oQmEsyWGSF;
      string yxUphuTHjD;
      string bWBWgIkpsY;
      string fEZilBgeRZ;
      string rOQEqhFaCx;
      if(oEwpELZnDO == AyrLQfnMQA){zWrNfROPXk = true;}
      else if(AyrLQfnMQA == oEwpELZnDO){RiENPyiman = true;}
      if(TEqntPlqOU == PETISxHLNL){NgNsZtXlEg = true;}
      else if(PETISxHLNL == TEqntPlqOU){bYjBGcyCkx = true;}
      if(JEynIXAWBU == iBalrKgqqa){NooKLNFxey = true;}
      else if(iBalrKgqqa == JEynIXAWBU){QaHDoDCAbY = true;}
      if(ixUesdGTPQ == RUjLYOUjKp){DJnuZILLCT = true;}
      else if(RUjLYOUjKp == ixUesdGTPQ){OAInicdFRp = true;}
      if(yPixzjKmbZ == eaQksSecQI){lRGgMKBXdx = true;}
      else if(eaQksSecQI == yPixzjKmbZ){AAqWmCsHbe = true;}
      if(yOKmtjFHhf == oQmEsyWGSF){JSWUjKghCS = true;}
      else if(oQmEsyWGSF == yOKmtjFHhf){XewBrqaAXL = true;}
      if(KCmifWiLuP == yxUphuTHjD){LQjZgDsSTQ = true;}
      else if(yxUphuTHjD == KCmifWiLuP){uiKBYaPwSd = true;}
      if(JSaxWtUBnY == bWBWgIkpsY){hLjjtwhIxA = true;}
      if(NNuaVTmhkI == fEZilBgeRZ){LhShnjmSKP = true;}
      if(XyljFwcAQc == rOQEqhFaCx){bdJiIVggzJ = true;}
      while(bWBWgIkpsY == JSaxWtUBnY){zrjtxQijPl = true;}
      while(fEZilBgeRZ == fEZilBgeRZ){JtYwBjEGuq = true;}
      while(rOQEqhFaCx == rOQEqhFaCx){BdgFuRooyM = true;}
      if(zWrNfROPXk == true){zWrNfROPXk = false;}
      if(NgNsZtXlEg == true){NgNsZtXlEg = false;}
      if(NooKLNFxey == true){NooKLNFxey = false;}
      if(DJnuZILLCT == true){DJnuZILLCT = false;}
      if(lRGgMKBXdx == true){lRGgMKBXdx = false;}
      if(JSWUjKghCS == true){JSWUjKghCS = false;}
      if(LQjZgDsSTQ == true){LQjZgDsSTQ = false;}
      if(hLjjtwhIxA == true){hLjjtwhIxA = false;}
      if(LhShnjmSKP == true){LhShnjmSKP = false;}
      if(bdJiIVggzJ == true){bdJiIVggzJ = false;}
      if(RiENPyiman == true){RiENPyiman = false;}
      if(bYjBGcyCkx == true){bYjBGcyCkx = false;}
      if(QaHDoDCAbY == true){QaHDoDCAbY = false;}
      if(OAInicdFRp == true){OAInicdFRp = false;}
      if(AAqWmCsHbe == true){AAqWmCsHbe = false;}
      if(XewBrqaAXL == true){XewBrqaAXL = false;}
      if(uiKBYaPwSd == true){uiKBYaPwSd = false;}
      if(zrjtxQijPl == true){zrjtxQijPl = false;}
      if(JtYwBjEGuq == true){JtYwBjEGuq = false;}
      if(BdgFuRooyM == true){BdgFuRooyM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGQYGLEXMF
{ 
  void xRrABrqfbu()
  { 
      bool CpdzxFTRFd = false;
      bool qPKLcwSjlE = false;
      bool SCcBxZNXgT = false;
      bool ZwULLdUVEC = false;
      bool guhtGSQmXm = false;
      bool uEVfazMcBX = false;
      bool ruklDutzzy = false;
      bool bwfiXWTiue = false;
      bool JZAsXVaojL = false;
      bool RqUfKlJwpK = false;
      bool YQmYLzXlID = false;
      bool ecgWNSuqNg = false;
      bool TEPmgjbzYk = false;
      bool NXrjFrmahY = false;
      bool xngfgnKxSq = false;
      bool qSiJqTBzra = false;
      bool WYMWpHjxQU = false;
      bool fTJnjeWjGr = false;
      bool Zeggtunisl = false;
      bool qmhGBYaKoY = false;
      string QgUecAKNfR;
      string JMkrNzSbVg;
      string DKGylYSPje;
      string oAdyJoeQPa;
      string ztgCumEeHc;
      string ZzjDIFZVsD;
      string hudBbJhliX;
      string UBLugIcEDy;
      string UnIGEpQapD;
      string PJXMsEPfal;
      string ERwiIYmnWz;
      string cURthslWwk;
      string rHwfILczBb;
      string swdQtDrZyf;
      string CbDpZtqddz;
      string SrioswUQZx;
      string unluFfqAze;
      string BMYQiPEFFO;
      string TzUCIANnXy;
      string hbzAjOoHjt;
      if(QgUecAKNfR == ERwiIYmnWz){CpdzxFTRFd = true;}
      else if(ERwiIYmnWz == QgUecAKNfR){YQmYLzXlID = true;}
      if(JMkrNzSbVg == cURthslWwk){qPKLcwSjlE = true;}
      else if(cURthslWwk == JMkrNzSbVg){ecgWNSuqNg = true;}
      if(DKGylYSPje == rHwfILczBb){SCcBxZNXgT = true;}
      else if(rHwfILczBb == DKGylYSPje){TEPmgjbzYk = true;}
      if(oAdyJoeQPa == swdQtDrZyf){ZwULLdUVEC = true;}
      else if(swdQtDrZyf == oAdyJoeQPa){NXrjFrmahY = true;}
      if(ztgCumEeHc == CbDpZtqddz){guhtGSQmXm = true;}
      else if(CbDpZtqddz == ztgCumEeHc){xngfgnKxSq = true;}
      if(ZzjDIFZVsD == SrioswUQZx){uEVfazMcBX = true;}
      else if(SrioswUQZx == ZzjDIFZVsD){qSiJqTBzra = true;}
      if(hudBbJhliX == unluFfqAze){ruklDutzzy = true;}
      else if(unluFfqAze == hudBbJhliX){WYMWpHjxQU = true;}
      if(UBLugIcEDy == BMYQiPEFFO){bwfiXWTiue = true;}
      if(UnIGEpQapD == TzUCIANnXy){JZAsXVaojL = true;}
      if(PJXMsEPfal == hbzAjOoHjt){RqUfKlJwpK = true;}
      while(BMYQiPEFFO == UBLugIcEDy){fTJnjeWjGr = true;}
      while(TzUCIANnXy == TzUCIANnXy){Zeggtunisl = true;}
      while(hbzAjOoHjt == hbzAjOoHjt){qmhGBYaKoY = true;}
      if(CpdzxFTRFd == true){CpdzxFTRFd = false;}
      if(qPKLcwSjlE == true){qPKLcwSjlE = false;}
      if(SCcBxZNXgT == true){SCcBxZNXgT = false;}
      if(ZwULLdUVEC == true){ZwULLdUVEC = false;}
      if(guhtGSQmXm == true){guhtGSQmXm = false;}
      if(uEVfazMcBX == true){uEVfazMcBX = false;}
      if(ruklDutzzy == true){ruklDutzzy = false;}
      if(bwfiXWTiue == true){bwfiXWTiue = false;}
      if(JZAsXVaojL == true){JZAsXVaojL = false;}
      if(RqUfKlJwpK == true){RqUfKlJwpK = false;}
      if(YQmYLzXlID == true){YQmYLzXlID = false;}
      if(ecgWNSuqNg == true){ecgWNSuqNg = false;}
      if(TEPmgjbzYk == true){TEPmgjbzYk = false;}
      if(NXrjFrmahY == true){NXrjFrmahY = false;}
      if(xngfgnKxSq == true){xngfgnKxSq = false;}
      if(qSiJqTBzra == true){qSiJqTBzra = false;}
      if(WYMWpHjxQU == true){WYMWpHjxQU = false;}
      if(fTJnjeWjGr == true){fTJnjeWjGr = false;}
      if(Zeggtunisl == true){Zeggtunisl = false;}
      if(qmhGBYaKoY == true){qmhGBYaKoY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NRPEEPDOXF
{ 
  void iaikoIfYVz()
  { 
      bool AgDZrhbCnK = false;
      bool wfZzApZLUO = false;
      bool YbQiXbiWmo = false;
      bool cucpRAQrBf = false;
      bool XkYnsGCPYG = false;
      bool ZxbxiXQUCP = false;
      bool yFOzhACjgA = false;
      bool ZhKopnCboQ = false;
      bool YTygPeSfHt = false;
      bool iuokgSVZGr = false;
      bool DSiXgqlmGu = false;
      bool UoekqeGhjC = false;
      bool gWblQdsZIX = false;
      bool RcUwMFkZAX = false;
      bool sfYLYtQDsC = false;
      bool LnpELgpwHC = false;
      bool yLehcrThXk = false;
      bool sghLJBxPNV = false;
      bool NofFLdmQkf = false;
      bool OoSxZgBqif = false;
      string iYIuNPzluK;
      string MmaerBzOzB;
      string tomDyEOORq;
      string nByyCLOZKE;
      string uuiiJDMUHy;
      string dzplkslFwI;
      string BjUEWLncbg;
      string mYEtGyFEst;
      string qtGSMnKMMI;
      string YIdBDKaeLx;
      string PjrZLFuuel;
      string nhLCRGdCqh;
      string BaPTIduCpu;
      string XarwdHBfGH;
      string sOhaUpxajx;
      string gXmdwoUYRh;
      string KrFjOMpPXJ;
      string EyujolsoyS;
      string gTRsOzmNzo;
      string lcOYxAJxLH;
      if(iYIuNPzluK == PjrZLFuuel){AgDZrhbCnK = true;}
      else if(PjrZLFuuel == iYIuNPzluK){DSiXgqlmGu = true;}
      if(MmaerBzOzB == nhLCRGdCqh){wfZzApZLUO = true;}
      else if(nhLCRGdCqh == MmaerBzOzB){UoekqeGhjC = true;}
      if(tomDyEOORq == BaPTIduCpu){YbQiXbiWmo = true;}
      else if(BaPTIduCpu == tomDyEOORq){gWblQdsZIX = true;}
      if(nByyCLOZKE == XarwdHBfGH){cucpRAQrBf = true;}
      else if(XarwdHBfGH == nByyCLOZKE){RcUwMFkZAX = true;}
      if(uuiiJDMUHy == sOhaUpxajx){XkYnsGCPYG = true;}
      else if(sOhaUpxajx == uuiiJDMUHy){sfYLYtQDsC = true;}
      if(dzplkslFwI == gXmdwoUYRh){ZxbxiXQUCP = true;}
      else if(gXmdwoUYRh == dzplkslFwI){LnpELgpwHC = true;}
      if(BjUEWLncbg == KrFjOMpPXJ){yFOzhACjgA = true;}
      else if(KrFjOMpPXJ == BjUEWLncbg){yLehcrThXk = true;}
      if(mYEtGyFEst == EyujolsoyS){ZhKopnCboQ = true;}
      if(qtGSMnKMMI == gTRsOzmNzo){YTygPeSfHt = true;}
      if(YIdBDKaeLx == lcOYxAJxLH){iuokgSVZGr = true;}
      while(EyujolsoyS == mYEtGyFEst){sghLJBxPNV = true;}
      while(gTRsOzmNzo == gTRsOzmNzo){NofFLdmQkf = true;}
      while(lcOYxAJxLH == lcOYxAJxLH){OoSxZgBqif = true;}
      if(AgDZrhbCnK == true){AgDZrhbCnK = false;}
      if(wfZzApZLUO == true){wfZzApZLUO = false;}
      if(YbQiXbiWmo == true){YbQiXbiWmo = false;}
      if(cucpRAQrBf == true){cucpRAQrBf = false;}
      if(XkYnsGCPYG == true){XkYnsGCPYG = false;}
      if(ZxbxiXQUCP == true){ZxbxiXQUCP = false;}
      if(yFOzhACjgA == true){yFOzhACjgA = false;}
      if(ZhKopnCboQ == true){ZhKopnCboQ = false;}
      if(YTygPeSfHt == true){YTygPeSfHt = false;}
      if(iuokgSVZGr == true){iuokgSVZGr = false;}
      if(DSiXgqlmGu == true){DSiXgqlmGu = false;}
      if(UoekqeGhjC == true){UoekqeGhjC = false;}
      if(gWblQdsZIX == true){gWblQdsZIX = false;}
      if(RcUwMFkZAX == true){RcUwMFkZAX = false;}
      if(sfYLYtQDsC == true){sfYLYtQDsC = false;}
      if(LnpELgpwHC == true){LnpELgpwHC = false;}
      if(yLehcrThXk == true){yLehcrThXk = false;}
      if(sghLJBxPNV == true){sghLJBxPNV = false;}
      if(NofFLdmQkf == true){NofFLdmQkf = false;}
      if(OoSxZgBqif == true){OoSxZgBqif = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZGZNJCQRIL
{ 
  void BXLZjqllIz()
  { 
      bool elpZdCBxfJ = false;
      bool MXlKBQfNJP = false;
      bool ERRThyzYFL = false;
      bool QZirYqsrOG = false;
      bool sefGpBwQxc = false;
      bool PPIaXNUVqf = false;
      bool CbqTrmotlJ = false;
      bool WmzDWYlKdg = false;
      bool BibcwBQHTK = false;
      bool WWAhDQnLND = false;
      bool MBdmFbPEEy = false;
      bool aJrKdTAOXq = false;
      bool VgZamzmQAF = false;
      bool kZwZTzEnWT = false;
      bool kMDVjMdoEi = false;
      bool PYnWgebDAF = false;
      bool ozEyMBNRqd = false;
      bool PLrEGJdEqZ = false;
      bool UxMRoMlZso = false;
      bool XBnQdlIFJh = false;
      string GzZQyJbIXG;
      string MxLhHDOEPL;
      string bmePsXKsCm;
      string JmcFkHhTof;
      string dgZnJBciax;
      string tPsmZTUKXZ;
      string yiGkwYTFwz;
      string VtPjhuNqGq;
      string tbREstspfR;
      string mXuOguanqj;
      string hWlbbzzJFe;
      string GdDgfWQBrC;
      string ecZeMxyBCl;
      string UYAVIWopcs;
      string tjkAKITOiK;
      string dZwnEFxGOd;
      string AyGSKhdhXI;
      string gaXyHurYUD;
      string cjSrItcLQD;
      string ZiayswdRpc;
      if(GzZQyJbIXG == hWlbbzzJFe){elpZdCBxfJ = true;}
      else if(hWlbbzzJFe == GzZQyJbIXG){MBdmFbPEEy = true;}
      if(MxLhHDOEPL == GdDgfWQBrC){MXlKBQfNJP = true;}
      else if(GdDgfWQBrC == MxLhHDOEPL){aJrKdTAOXq = true;}
      if(bmePsXKsCm == ecZeMxyBCl){ERRThyzYFL = true;}
      else if(ecZeMxyBCl == bmePsXKsCm){VgZamzmQAF = true;}
      if(JmcFkHhTof == UYAVIWopcs){QZirYqsrOG = true;}
      else if(UYAVIWopcs == JmcFkHhTof){kZwZTzEnWT = true;}
      if(dgZnJBciax == tjkAKITOiK){sefGpBwQxc = true;}
      else if(tjkAKITOiK == dgZnJBciax){kMDVjMdoEi = true;}
      if(tPsmZTUKXZ == dZwnEFxGOd){PPIaXNUVqf = true;}
      else if(dZwnEFxGOd == tPsmZTUKXZ){PYnWgebDAF = true;}
      if(yiGkwYTFwz == AyGSKhdhXI){CbqTrmotlJ = true;}
      else if(AyGSKhdhXI == yiGkwYTFwz){ozEyMBNRqd = true;}
      if(VtPjhuNqGq == gaXyHurYUD){WmzDWYlKdg = true;}
      if(tbREstspfR == cjSrItcLQD){BibcwBQHTK = true;}
      if(mXuOguanqj == ZiayswdRpc){WWAhDQnLND = true;}
      while(gaXyHurYUD == VtPjhuNqGq){PLrEGJdEqZ = true;}
      while(cjSrItcLQD == cjSrItcLQD){UxMRoMlZso = true;}
      while(ZiayswdRpc == ZiayswdRpc){XBnQdlIFJh = true;}
      if(elpZdCBxfJ == true){elpZdCBxfJ = false;}
      if(MXlKBQfNJP == true){MXlKBQfNJP = false;}
      if(ERRThyzYFL == true){ERRThyzYFL = false;}
      if(QZirYqsrOG == true){QZirYqsrOG = false;}
      if(sefGpBwQxc == true){sefGpBwQxc = false;}
      if(PPIaXNUVqf == true){PPIaXNUVqf = false;}
      if(CbqTrmotlJ == true){CbqTrmotlJ = false;}
      if(WmzDWYlKdg == true){WmzDWYlKdg = false;}
      if(BibcwBQHTK == true){BibcwBQHTK = false;}
      if(WWAhDQnLND == true){WWAhDQnLND = false;}
      if(MBdmFbPEEy == true){MBdmFbPEEy = false;}
      if(aJrKdTAOXq == true){aJrKdTAOXq = false;}
      if(VgZamzmQAF == true){VgZamzmQAF = false;}
      if(kZwZTzEnWT == true){kZwZTzEnWT = false;}
      if(kMDVjMdoEi == true){kMDVjMdoEi = false;}
      if(PYnWgebDAF == true){PYnWgebDAF = false;}
      if(ozEyMBNRqd == true){ozEyMBNRqd = false;}
      if(PLrEGJdEqZ == true){PLrEGJdEqZ = false;}
      if(UxMRoMlZso == true){UxMRoMlZso = false;}
      if(XBnQdlIFJh == true){XBnQdlIFJh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJEBJWYWPW
{ 
  void LpMJmpzmbg()
  { 
      bool drbSkzuGqw = false;
      bool MoMXaUmDxa = false;
      bool yDWDTducHB = false;
      bool sjKZjsCRYy = false;
      bool ysBpMLUXdi = false;
      bool qcjrlaVYzG = false;
      bool ESzoDcelmg = false;
      bool RUdzcEBgpH = false;
      bool JXyXKPzSnJ = false;
      bool WdRSsetMlj = false;
      bool ghjwRVykOh = false;
      bool ZohqwgUbem = false;
      bool cMydKmCKFy = false;
      bool JntFabmCFo = false;
      bool RODFihuaWM = false;
      bool KShzHUiGle = false;
      bool SnfQXkucQU = false;
      bool sRVoVOIrtc = false;
      bool qbnrnpGtyG = false;
      bool rgPaWcilhy = false;
      string BmgSzNtsBm;
      string gBYJooXlRB;
      string sjHSHycKay;
      string EBwXQPhzgy;
      string ytknUdnIBH;
      string JDmkqQeOLB;
      string kiRDifFAsZ;
      string HYFTCzzTxc;
      string JUJSnANKgz;
      string kSneMObgEo;
      string YnPaAkyThr;
      string QKRhqQYzOh;
      string StTsnnkZGm;
      string WSOIEVEhRD;
      string CsboiZBFnw;
      string pcRWVeUWmM;
      string zYMtUyuIcU;
      string LpgLfZReKO;
      string lekJxsArlZ;
      string BguEDdfhTj;
      if(BmgSzNtsBm == YnPaAkyThr){drbSkzuGqw = true;}
      else if(YnPaAkyThr == BmgSzNtsBm){ghjwRVykOh = true;}
      if(gBYJooXlRB == QKRhqQYzOh){MoMXaUmDxa = true;}
      else if(QKRhqQYzOh == gBYJooXlRB){ZohqwgUbem = true;}
      if(sjHSHycKay == StTsnnkZGm){yDWDTducHB = true;}
      else if(StTsnnkZGm == sjHSHycKay){cMydKmCKFy = true;}
      if(EBwXQPhzgy == WSOIEVEhRD){sjKZjsCRYy = true;}
      else if(WSOIEVEhRD == EBwXQPhzgy){JntFabmCFo = true;}
      if(ytknUdnIBH == CsboiZBFnw){ysBpMLUXdi = true;}
      else if(CsboiZBFnw == ytknUdnIBH){RODFihuaWM = true;}
      if(JDmkqQeOLB == pcRWVeUWmM){qcjrlaVYzG = true;}
      else if(pcRWVeUWmM == JDmkqQeOLB){KShzHUiGle = true;}
      if(kiRDifFAsZ == zYMtUyuIcU){ESzoDcelmg = true;}
      else if(zYMtUyuIcU == kiRDifFAsZ){SnfQXkucQU = true;}
      if(HYFTCzzTxc == LpgLfZReKO){RUdzcEBgpH = true;}
      if(JUJSnANKgz == lekJxsArlZ){JXyXKPzSnJ = true;}
      if(kSneMObgEo == BguEDdfhTj){WdRSsetMlj = true;}
      while(LpgLfZReKO == HYFTCzzTxc){sRVoVOIrtc = true;}
      while(lekJxsArlZ == lekJxsArlZ){qbnrnpGtyG = true;}
      while(BguEDdfhTj == BguEDdfhTj){rgPaWcilhy = true;}
      if(drbSkzuGqw == true){drbSkzuGqw = false;}
      if(MoMXaUmDxa == true){MoMXaUmDxa = false;}
      if(yDWDTducHB == true){yDWDTducHB = false;}
      if(sjKZjsCRYy == true){sjKZjsCRYy = false;}
      if(ysBpMLUXdi == true){ysBpMLUXdi = false;}
      if(qcjrlaVYzG == true){qcjrlaVYzG = false;}
      if(ESzoDcelmg == true){ESzoDcelmg = false;}
      if(RUdzcEBgpH == true){RUdzcEBgpH = false;}
      if(JXyXKPzSnJ == true){JXyXKPzSnJ = false;}
      if(WdRSsetMlj == true){WdRSsetMlj = false;}
      if(ghjwRVykOh == true){ghjwRVykOh = false;}
      if(ZohqwgUbem == true){ZohqwgUbem = false;}
      if(cMydKmCKFy == true){cMydKmCKFy = false;}
      if(JntFabmCFo == true){JntFabmCFo = false;}
      if(RODFihuaWM == true){RODFihuaWM = false;}
      if(KShzHUiGle == true){KShzHUiGle = false;}
      if(SnfQXkucQU == true){SnfQXkucQU = false;}
      if(sRVoVOIrtc == true){sRVoVOIrtc = false;}
      if(qbnrnpGtyG == true){qbnrnpGtyG = false;}
      if(rgPaWcilhy == true){rgPaWcilhy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KQEULGKWRT
{ 
  void wnWNAPjYsr()
  { 
      bool iHTValGwlU = false;
      bool IcQOtnUUSO = false;
      bool puBhnsZVTV = false;
      bool pofKxasfdA = false;
      bool KniGrwIUSK = false;
      bool YLXPinFkgg = false;
      bool MjbPeSwFRT = false;
      bool unpSECMupq = false;
      bool kECJweRQaJ = false;
      bool UHyxmZLSaY = false;
      bool ACDzPkUEKf = false;
      bool bKupuIhSSA = false;
      bool AedHymosee = false;
      bool psUQpiADsL = false;
      bool JNFuhKLICe = false;
      bool rszZYVXwBb = false;
      bool uaYfphoezM = false;
      bool HdYHqmYiZm = false;
      bool afqAlxstqU = false;
      bool KEBRPhnZEz = false;
      string LiuRyCEHEg;
      string pGWtyWtEUG;
      string DBqLlzCEqU;
      string bksEjdSFIk;
      string kfSlYebswB;
      string EDGIIJqjey;
      string AzPiEFNRJT;
      string DnuiUWiElH;
      string XIIoPYdjwZ;
      string miZJklQihT;
      string RJicyPHXnl;
      string amxXaqpaTf;
      string bcVifUOkyh;
      string GzWSoNYfqA;
      string QFwKzzlBis;
      string woPBqonAwc;
      string BWZFeaQdhN;
      string SJiSPVfLig;
      string iMCElQjUbA;
      string YYjNzsfpeY;
      if(LiuRyCEHEg == RJicyPHXnl){iHTValGwlU = true;}
      else if(RJicyPHXnl == LiuRyCEHEg){ACDzPkUEKf = true;}
      if(pGWtyWtEUG == amxXaqpaTf){IcQOtnUUSO = true;}
      else if(amxXaqpaTf == pGWtyWtEUG){bKupuIhSSA = true;}
      if(DBqLlzCEqU == bcVifUOkyh){puBhnsZVTV = true;}
      else if(bcVifUOkyh == DBqLlzCEqU){AedHymosee = true;}
      if(bksEjdSFIk == GzWSoNYfqA){pofKxasfdA = true;}
      else if(GzWSoNYfqA == bksEjdSFIk){psUQpiADsL = true;}
      if(kfSlYebswB == QFwKzzlBis){KniGrwIUSK = true;}
      else if(QFwKzzlBis == kfSlYebswB){JNFuhKLICe = true;}
      if(EDGIIJqjey == woPBqonAwc){YLXPinFkgg = true;}
      else if(woPBqonAwc == EDGIIJqjey){rszZYVXwBb = true;}
      if(AzPiEFNRJT == BWZFeaQdhN){MjbPeSwFRT = true;}
      else if(BWZFeaQdhN == AzPiEFNRJT){uaYfphoezM = true;}
      if(DnuiUWiElH == SJiSPVfLig){unpSECMupq = true;}
      if(XIIoPYdjwZ == iMCElQjUbA){kECJweRQaJ = true;}
      if(miZJklQihT == YYjNzsfpeY){UHyxmZLSaY = true;}
      while(SJiSPVfLig == DnuiUWiElH){HdYHqmYiZm = true;}
      while(iMCElQjUbA == iMCElQjUbA){afqAlxstqU = true;}
      while(YYjNzsfpeY == YYjNzsfpeY){KEBRPhnZEz = true;}
      if(iHTValGwlU == true){iHTValGwlU = false;}
      if(IcQOtnUUSO == true){IcQOtnUUSO = false;}
      if(puBhnsZVTV == true){puBhnsZVTV = false;}
      if(pofKxasfdA == true){pofKxasfdA = false;}
      if(KniGrwIUSK == true){KniGrwIUSK = false;}
      if(YLXPinFkgg == true){YLXPinFkgg = false;}
      if(MjbPeSwFRT == true){MjbPeSwFRT = false;}
      if(unpSECMupq == true){unpSECMupq = false;}
      if(kECJweRQaJ == true){kECJweRQaJ = false;}
      if(UHyxmZLSaY == true){UHyxmZLSaY = false;}
      if(ACDzPkUEKf == true){ACDzPkUEKf = false;}
      if(bKupuIhSSA == true){bKupuIhSSA = false;}
      if(AedHymosee == true){AedHymosee = false;}
      if(psUQpiADsL == true){psUQpiADsL = false;}
      if(JNFuhKLICe == true){JNFuhKLICe = false;}
      if(rszZYVXwBb == true){rszZYVXwBb = false;}
      if(uaYfphoezM == true){uaYfphoezM = false;}
      if(HdYHqmYiZm == true){HdYHqmYiZm = false;}
      if(afqAlxstqU == true){afqAlxstqU = false;}
      if(KEBRPhnZEz == true){KEBRPhnZEz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AJSCMGCQTU
{ 
  void qEZcarUnkD()
  { 
      bool cAkBXTftwi = false;
      bool DMTIbNZyVF = false;
      bool fMKGxuxhSN = false;
      bool hFDpXtzeHj = false;
      bool CgINdIwSGD = false;
      bool PcyBtPpdEb = false;
      bool WxaiByIcjg = false;
      bool NtpkCyEwcn = false;
      bool ydaOyEGCuH = false;
      bool DVafNEFYMe = false;
      bool zShYpUmMyw = false;
      bool LsAPcrWMkw = false;
      bool qGgbcrTKWx = false;
      bool seiyofwBYc = false;
      bool RsEzwKUKCV = false;
      bool hsnQmskFwy = false;
      bool AcpBDgKCax = false;
      bool uVnHdyBgfS = false;
      bool WIIBPzpSKu = false;
      bool tpFZboDDwP = false;
      string oqFoCJEHoI;
      string PMslLBKEDp;
      string KpMNjSMIIO;
      string BCearxucSr;
      string uOFGSducTe;
      string puEPNydqEj;
      string xwyZGMhSsO;
      string GhkKtukFuG;
      string WjodYGyOMt;
      string SDXiuyQeAG;
      string uciEYIJsUS;
      string MXwyNMHUAA;
      string NSFyuCJCOu;
      string dFFoKsAjEQ;
      string wFstguHYVi;
      string queArcXkIV;
      string yHdZnGRHnT;
      string LXPjDIYKQA;
      string tkgfEhaFxg;
      string VPahRoaTGa;
      if(oqFoCJEHoI == uciEYIJsUS){cAkBXTftwi = true;}
      else if(uciEYIJsUS == oqFoCJEHoI){zShYpUmMyw = true;}
      if(PMslLBKEDp == MXwyNMHUAA){DMTIbNZyVF = true;}
      else if(MXwyNMHUAA == PMslLBKEDp){LsAPcrWMkw = true;}
      if(KpMNjSMIIO == NSFyuCJCOu){fMKGxuxhSN = true;}
      else if(NSFyuCJCOu == KpMNjSMIIO){qGgbcrTKWx = true;}
      if(BCearxucSr == dFFoKsAjEQ){hFDpXtzeHj = true;}
      else if(dFFoKsAjEQ == BCearxucSr){seiyofwBYc = true;}
      if(uOFGSducTe == wFstguHYVi){CgINdIwSGD = true;}
      else if(wFstguHYVi == uOFGSducTe){RsEzwKUKCV = true;}
      if(puEPNydqEj == queArcXkIV){PcyBtPpdEb = true;}
      else if(queArcXkIV == puEPNydqEj){hsnQmskFwy = true;}
      if(xwyZGMhSsO == yHdZnGRHnT){WxaiByIcjg = true;}
      else if(yHdZnGRHnT == xwyZGMhSsO){AcpBDgKCax = true;}
      if(GhkKtukFuG == LXPjDIYKQA){NtpkCyEwcn = true;}
      if(WjodYGyOMt == tkgfEhaFxg){ydaOyEGCuH = true;}
      if(SDXiuyQeAG == VPahRoaTGa){DVafNEFYMe = true;}
      while(LXPjDIYKQA == GhkKtukFuG){uVnHdyBgfS = true;}
      while(tkgfEhaFxg == tkgfEhaFxg){WIIBPzpSKu = true;}
      while(VPahRoaTGa == VPahRoaTGa){tpFZboDDwP = true;}
      if(cAkBXTftwi == true){cAkBXTftwi = false;}
      if(DMTIbNZyVF == true){DMTIbNZyVF = false;}
      if(fMKGxuxhSN == true){fMKGxuxhSN = false;}
      if(hFDpXtzeHj == true){hFDpXtzeHj = false;}
      if(CgINdIwSGD == true){CgINdIwSGD = false;}
      if(PcyBtPpdEb == true){PcyBtPpdEb = false;}
      if(WxaiByIcjg == true){WxaiByIcjg = false;}
      if(NtpkCyEwcn == true){NtpkCyEwcn = false;}
      if(ydaOyEGCuH == true){ydaOyEGCuH = false;}
      if(DVafNEFYMe == true){DVafNEFYMe = false;}
      if(zShYpUmMyw == true){zShYpUmMyw = false;}
      if(LsAPcrWMkw == true){LsAPcrWMkw = false;}
      if(qGgbcrTKWx == true){qGgbcrTKWx = false;}
      if(seiyofwBYc == true){seiyofwBYc = false;}
      if(RsEzwKUKCV == true){RsEzwKUKCV = false;}
      if(hsnQmskFwy == true){hsnQmskFwy = false;}
      if(AcpBDgKCax == true){AcpBDgKCax = false;}
      if(uVnHdyBgfS == true){uVnHdyBgfS = false;}
      if(WIIBPzpSKu == true){WIIBPzpSKu = false;}
      if(tpFZboDDwP == true){tpFZboDDwP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZBTMHWZMHT
{ 
  void iIsCQWIBOk()
  { 
      bool fHZSJjgxkH = false;
      bool NeCyoZGujb = false;
      bool xYOPFwDULS = false;
      bool WwQWwTFrkU = false;
      bool MduSJYLFcr = false;
      bool KrTblGrJNM = false;
      bool gMlRkROeBU = false;
      bool UOJPOTcwGf = false;
      bool kyqSIdcnko = false;
      bool budYmAqdgr = false;
      bool JfDIXuhDNS = false;
      bool dwDgbiUTJG = false;
      bool natLsYkkcO = false;
      bool bzOOWEthuM = false;
      bool uYaRLfrxwE = false;
      bool eWUaDikrPy = false;
      bool KxZypdgnJX = false;
      bool omYwLPzczN = false;
      bool gmnYjFdnLm = false;
      bool SBSwCyybag = false;
      string onSrPCYRVa;
      string kPFqBTfeEH;
      string tgniaBVSUy;
      string TKpArsPCDk;
      string inAxhhBXyu;
      string bfZKpHzjRN;
      string gFxXHZZFzI;
      string EdbTYFfqBs;
      string AxUZVmkeKj;
      string sfkoEcqcoH;
      string IuYppyEGkj;
      string bHhXNikWBT;
      string otuOOYrlPw;
      string ODBskEXdjX;
      string iesZIlxMbU;
      string qUbUSNAJaQ;
      string FRpoVYFomI;
      string LGmdjKAUGc;
      string beKuEtafaW;
      string DODSSRnEEi;
      if(onSrPCYRVa == IuYppyEGkj){fHZSJjgxkH = true;}
      else if(IuYppyEGkj == onSrPCYRVa){JfDIXuhDNS = true;}
      if(kPFqBTfeEH == bHhXNikWBT){NeCyoZGujb = true;}
      else if(bHhXNikWBT == kPFqBTfeEH){dwDgbiUTJG = true;}
      if(tgniaBVSUy == otuOOYrlPw){xYOPFwDULS = true;}
      else if(otuOOYrlPw == tgniaBVSUy){natLsYkkcO = true;}
      if(TKpArsPCDk == ODBskEXdjX){WwQWwTFrkU = true;}
      else if(ODBskEXdjX == TKpArsPCDk){bzOOWEthuM = true;}
      if(inAxhhBXyu == iesZIlxMbU){MduSJYLFcr = true;}
      else if(iesZIlxMbU == inAxhhBXyu){uYaRLfrxwE = true;}
      if(bfZKpHzjRN == qUbUSNAJaQ){KrTblGrJNM = true;}
      else if(qUbUSNAJaQ == bfZKpHzjRN){eWUaDikrPy = true;}
      if(gFxXHZZFzI == FRpoVYFomI){gMlRkROeBU = true;}
      else if(FRpoVYFomI == gFxXHZZFzI){KxZypdgnJX = true;}
      if(EdbTYFfqBs == LGmdjKAUGc){UOJPOTcwGf = true;}
      if(AxUZVmkeKj == beKuEtafaW){kyqSIdcnko = true;}
      if(sfkoEcqcoH == DODSSRnEEi){budYmAqdgr = true;}
      while(LGmdjKAUGc == EdbTYFfqBs){omYwLPzczN = true;}
      while(beKuEtafaW == beKuEtafaW){gmnYjFdnLm = true;}
      while(DODSSRnEEi == DODSSRnEEi){SBSwCyybag = true;}
      if(fHZSJjgxkH == true){fHZSJjgxkH = false;}
      if(NeCyoZGujb == true){NeCyoZGujb = false;}
      if(xYOPFwDULS == true){xYOPFwDULS = false;}
      if(WwQWwTFrkU == true){WwQWwTFrkU = false;}
      if(MduSJYLFcr == true){MduSJYLFcr = false;}
      if(KrTblGrJNM == true){KrTblGrJNM = false;}
      if(gMlRkROeBU == true){gMlRkROeBU = false;}
      if(UOJPOTcwGf == true){UOJPOTcwGf = false;}
      if(kyqSIdcnko == true){kyqSIdcnko = false;}
      if(budYmAqdgr == true){budYmAqdgr = false;}
      if(JfDIXuhDNS == true){JfDIXuhDNS = false;}
      if(dwDgbiUTJG == true){dwDgbiUTJG = false;}
      if(natLsYkkcO == true){natLsYkkcO = false;}
      if(bzOOWEthuM == true){bzOOWEthuM = false;}
      if(uYaRLfrxwE == true){uYaRLfrxwE = false;}
      if(eWUaDikrPy == true){eWUaDikrPy = false;}
      if(KxZypdgnJX == true){KxZypdgnJX = false;}
      if(omYwLPzczN == true){omYwLPzczN = false;}
      if(gmnYjFdnLm == true){gmnYjFdnLm = false;}
      if(SBSwCyybag == true){SBSwCyybag = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FNPKZZBJEY
{ 
  void dMwRudYDYI()
  { 
      bool lZCJmJcwhK = false;
      bool IkmCcNWgAw = false;
      bool gAsCdPaFWe = false;
      bool YfKPelmkkA = false;
      bool sZSnXHqmtj = false;
      bool dXwiPkfAeW = false;
      bool iXZDlcaXWp = false;
      bool alwzCHgFdW = false;
      bool XmKlABjbzs = false;
      bool GlFNRUAPCu = false;
      bool gTPEIrawfI = false;
      bool EZWIyuNmCj = false;
      bool szYdiofihg = false;
      bool GQDhpEXFcI = false;
      bool ZmuqngPxOW = false;
      bool HMNRCgtkUT = false;
      bool MrOyCmVnRs = false;
      bool XHJsJFDgoC = false;
      bool YhTKZsDleI = false;
      bool JlkJwhYwoB = false;
      string lcxnTjHxcH;
      string HNBRuVtFwe;
      string oSnBwnOFbZ;
      string BybQLpseEe;
      string yQqPlHCUbw;
      string srbZUSnuqe;
      string VBUCFJlkGF;
      string cOAQfYbYPo;
      string ltdffIVBur;
      string CynZJwunKb;
      string VROVTdqLtw;
      string qPfCraXoWw;
      string mjoNDdaaGi;
      string cmOmSUfHMB;
      string RJHyBmRlgh;
      string YGQNnkbASo;
      string DQFKSDAriX;
      string uPcUedcpMQ;
      string LotXJWVAyg;
      string seoXyAEwex;
      if(lcxnTjHxcH == VROVTdqLtw){lZCJmJcwhK = true;}
      else if(VROVTdqLtw == lcxnTjHxcH){gTPEIrawfI = true;}
      if(HNBRuVtFwe == qPfCraXoWw){IkmCcNWgAw = true;}
      else if(qPfCraXoWw == HNBRuVtFwe){EZWIyuNmCj = true;}
      if(oSnBwnOFbZ == mjoNDdaaGi){gAsCdPaFWe = true;}
      else if(mjoNDdaaGi == oSnBwnOFbZ){szYdiofihg = true;}
      if(BybQLpseEe == cmOmSUfHMB){YfKPelmkkA = true;}
      else if(cmOmSUfHMB == BybQLpseEe){GQDhpEXFcI = true;}
      if(yQqPlHCUbw == RJHyBmRlgh){sZSnXHqmtj = true;}
      else if(RJHyBmRlgh == yQqPlHCUbw){ZmuqngPxOW = true;}
      if(srbZUSnuqe == YGQNnkbASo){dXwiPkfAeW = true;}
      else if(YGQNnkbASo == srbZUSnuqe){HMNRCgtkUT = true;}
      if(VBUCFJlkGF == DQFKSDAriX){iXZDlcaXWp = true;}
      else if(DQFKSDAriX == VBUCFJlkGF){MrOyCmVnRs = true;}
      if(cOAQfYbYPo == uPcUedcpMQ){alwzCHgFdW = true;}
      if(ltdffIVBur == LotXJWVAyg){XmKlABjbzs = true;}
      if(CynZJwunKb == seoXyAEwex){GlFNRUAPCu = true;}
      while(uPcUedcpMQ == cOAQfYbYPo){XHJsJFDgoC = true;}
      while(LotXJWVAyg == LotXJWVAyg){YhTKZsDleI = true;}
      while(seoXyAEwex == seoXyAEwex){JlkJwhYwoB = true;}
      if(lZCJmJcwhK == true){lZCJmJcwhK = false;}
      if(IkmCcNWgAw == true){IkmCcNWgAw = false;}
      if(gAsCdPaFWe == true){gAsCdPaFWe = false;}
      if(YfKPelmkkA == true){YfKPelmkkA = false;}
      if(sZSnXHqmtj == true){sZSnXHqmtj = false;}
      if(dXwiPkfAeW == true){dXwiPkfAeW = false;}
      if(iXZDlcaXWp == true){iXZDlcaXWp = false;}
      if(alwzCHgFdW == true){alwzCHgFdW = false;}
      if(XmKlABjbzs == true){XmKlABjbzs = false;}
      if(GlFNRUAPCu == true){GlFNRUAPCu = false;}
      if(gTPEIrawfI == true){gTPEIrawfI = false;}
      if(EZWIyuNmCj == true){EZWIyuNmCj = false;}
      if(szYdiofihg == true){szYdiofihg = false;}
      if(GQDhpEXFcI == true){GQDhpEXFcI = false;}
      if(ZmuqngPxOW == true){ZmuqngPxOW = false;}
      if(HMNRCgtkUT == true){HMNRCgtkUT = false;}
      if(MrOyCmVnRs == true){MrOyCmVnRs = false;}
      if(XHJsJFDgoC == true){XHJsJFDgoC = false;}
      if(YhTKZsDleI == true){YhTKZsDleI = false;}
      if(JlkJwhYwoB == true){JlkJwhYwoB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MNDRLFVHLN
{ 
  void sNeZUcctCG()
  { 
      bool BKEwgUSuXK = false;
      bool BHipsHhHhM = false;
      bool rCHBuluCQm = false;
      bool bnlbWhFgHO = false;
      bool DkeAigasPC = false;
      bool gbAzUzDDBt = false;
      bool YQdjiMVGSK = false;
      bool BBASJHWGRN = false;
      bool KClOGzmmGX = false;
      bool dCeMolGtRW = false;
      bool LUZEAebhoN = false;
      bool bxkmiWdOdi = false;
      bool ZhzufyWncW = false;
      bool AbouCpbgNa = false;
      bool XExrugQqcS = false;
      bool HrQhwcUdYC = false;
      bool ImERNAHpks = false;
      bool uxACLUjHzy = false;
      bool geKKPHKGyY = false;
      bool VxILSjAeeu = false;
      string ogGbKdeZwU;
      string XresejZRuM;
      string dqOEbeRIPA;
      string sjRCIIglsU;
      string zsSfFWejQL;
      string GunOUxRBAf;
      string MVJwbnZckV;
      string CmXZNjYhzF;
      string zgrDtyuCgK;
      string pflNIcjWEQ;
      string wCytJSWNBk;
      string YiBufecFBd;
      string sXuaeWBKRj;
      string ABdiIwhyta;
      string agAwkGdqgc;
      string AdVZWXHXOl;
      string RLwRjXFSlj;
      string weKaCMWzoX;
      string sKdnjWfDLk;
      string oKiIJOjiMN;
      if(ogGbKdeZwU == wCytJSWNBk){BKEwgUSuXK = true;}
      else if(wCytJSWNBk == ogGbKdeZwU){LUZEAebhoN = true;}
      if(XresejZRuM == YiBufecFBd){BHipsHhHhM = true;}
      else if(YiBufecFBd == XresejZRuM){bxkmiWdOdi = true;}
      if(dqOEbeRIPA == sXuaeWBKRj){rCHBuluCQm = true;}
      else if(sXuaeWBKRj == dqOEbeRIPA){ZhzufyWncW = true;}
      if(sjRCIIglsU == ABdiIwhyta){bnlbWhFgHO = true;}
      else if(ABdiIwhyta == sjRCIIglsU){AbouCpbgNa = true;}
      if(zsSfFWejQL == agAwkGdqgc){DkeAigasPC = true;}
      else if(agAwkGdqgc == zsSfFWejQL){XExrugQqcS = true;}
      if(GunOUxRBAf == AdVZWXHXOl){gbAzUzDDBt = true;}
      else if(AdVZWXHXOl == GunOUxRBAf){HrQhwcUdYC = true;}
      if(MVJwbnZckV == RLwRjXFSlj){YQdjiMVGSK = true;}
      else if(RLwRjXFSlj == MVJwbnZckV){ImERNAHpks = true;}
      if(CmXZNjYhzF == weKaCMWzoX){BBASJHWGRN = true;}
      if(zgrDtyuCgK == sKdnjWfDLk){KClOGzmmGX = true;}
      if(pflNIcjWEQ == oKiIJOjiMN){dCeMolGtRW = true;}
      while(weKaCMWzoX == CmXZNjYhzF){uxACLUjHzy = true;}
      while(sKdnjWfDLk == sKdnjWfDLk){geKKPHKGyY = true;}
      while(oKiIJOjiMN == oKiIJOjiMN){VxILSjAeeu = true;}
      if(BKEwgUSuXK == true){BKEwgUSuXK = false;}
      if(BHipsHhHhM == true){BHipsHhHhM = false;}
      if(rCHBuluCQm == true){rCHBuluCQm = false;}
      if(bnlbWhFgHO == true){bnlbWhFgHO = false;}
      if(DkeAigasPC == true){DkeAigasPC = false;}
      if(gbAzUzDDBt == true){gbAzUzDDBt = false;}
      if(YQdjiMVGSK == true){YQdjiMVGSK = false;}
      if(BBASJHWGRN == true){BBASJHWGRN = false;}
      if(KClOGzmmGX == true){KClOGzmmGX = false;}
      if(dCeMolGtRW == true){dCeMolGtRW = false;}
      if(LUZEAebhoN == true){LUZEAebhoN = false;}
      if(bxkmiWdOdi == true){bxkmiWdOdi = false;}
      if(ZhzufyWncW == true){ZhzufyWncW = false;}
      if(AbouCpbgNa == true){AbouCpbgNa = false;}
      if(XExrugQqcS == true){XExrugQqcS = false;}
      if(HrQhwcUdYC == true){HrQhwcUdYC = false;}
      if(ImERNAHpks == true){ImERNAHpks = false;}
      if(uxACLUjHzy == true){uxACLUjHzy = false;}
      if(geKKPHKGyY == true){geKKPHKGyY = false;}
      if(VxILSjAeeu == true){VxILSjAeeu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KIUPCZIRPV
{ 
  void tLjeVndbiM()
  { 
      bool pXGXlfdPMt = false;
      bool ZohUibVfdc = false;
      bool rVgRnYfVtB = false;
      bool qMbuuApDDo = false;
      bool XSxnrKLZyo = false;
      bool mmXqMTpniM = false;
      bool AIVLDMMlZh = false;
      bool kRboFZYrYd = false;
      bool NFWFNDokha = false;
      bool JBTpnOwlkf = false;
      bool xYAQDVKill = false;
      bool uyOFztkPxz = false;
      bool XaEyXjxlAp = false;
      bool clGsfnFGBr = false;
      bool sGzufLlOqt = false;
      bool cfnkHVUBrT = false;
      bool XYhuJJqVZL = false;
      bool oeOFGRbIRM = false;
      bool xiuGMwxVkJ = false;
      bool TDOhUUXDlW = false;
      string kTtOCoaheP;
      string YLwoaqJCft;
      string jNczJKEegf;
      string DTSlpdmnck;
      string gaaCIxqNMY;
      string gKMpXXptEr;
      string kuAzLFsJzw;
      string EVYuNJlZqM;
      string SpRIzsGcNR;
      string mrikAkZbqD;
      string EhOPTKkRbO;
      string kQDrYtdrAS;
      string yPugIMmnuc;
      string jKimHkbCon;
      string HoBzfWnqLF;
      string HgbXEolhGH;
      string XxVzeagPjn;
      string SaDLLJOwAk;
      string XwbpUCiKiS;
      string zsugQJSBTF;
      if(kTtOCoaheP == EhOPTKkRbO){pXGXlfdPMt = true;}
      else if(EhOPTKkRbO == kTtOCoaheP){xYAQDVKill = true;}
      if(YLwoaqJCft == kQDrYtdrAS){ZohUibVfdc = true;}
      else if(kQDrYtdrAS == YLwoaqJCft){uyOFztkPxz = true;}
      if(jNczJKEegf == yPugIMmnuc){rVgRnYfVtB = true;}
      else if(yPugIMmnuc == jNczJKEegf){XaEyXjxlAp = true;}
      if(DTSlpdmnck == jKimHkbCon){qMbuuApDDo = true;}
      else if(jKimHkbCon == DTSlpdmnck){clGsfnFGBr = true;}
      if(gaaCIxqNMY == HoBzfWnqLF){XSxnrKLZyo = true;}
      else if(HoBzfWnqLF == gaaCIxqNMY){sGzufLlOqt = true;}
      if(gKMpXXptEr == HgbXEolhGH){mmXqMTpniM = true;}
      else if(HgbXEolhGH == gKMpXXptEr){cfnkHVUBrT = true;}
      if(kuAzLFsJzw == XxVzeagPjn){AIVLDMMlZh = true;}
      else if(XxVzeagPjn == kuAzLFsJzw){XYhuJJqVZL = true;}
      if(EVYuNJlZqM == SaDLLJOwAk){kRboFZYrYd = true;}
      if(SpRIzsGcNR == XwbpUCiKiS){NFWFNDokha = true;}
      if(mrikAkZbqD == zsugQJSBTF){JBTpnOwlkf = true;}
      while(SaDLLJOwAk == EVYuNJlZqM){oeOFGRbIRM = true;}
      while(XwbpUCiKiS == XwbpUCiKiS){xiuGMwxVkJ = true;}
      while(zsugQJSBTF == zsugQJSBTF){TDOhUUXDlW = true;}
      if(pXGXlfdPMt == true){pXGXlfdPMt = false;}
      if(ZohUibVfdc == true){ZohUibVfdc = false;}
      if(rVgRnYfVtB == true){rVgRnYfVtB = false;}
      if(qMbuuApDDo == true){qMbuuApDDo = false;}
      if(XSxnrKLZyo == true){XSxnrKLZyo = false;}
      if(mmXqMTpniM == true){mmXqMTpniM = false;}
      if(AIVLDMMlZh == true){AIVLDMMlZh = false;}
      if(kRboFZYrYd == true){kRboFZYrYd = false;}
      if(NFWFNDokha == true){NFWFNDokha = false;}
      if(JBTpnOwlkf == true){JBTpnOwlkf = false;}
      if(xYAQDVKill == true){xYAQDVKill = false;}
      if(uyOFztkPxz == true){uyOFztkPxz = false;}
      if(XaEyXjxlAp == true){XaEyXjxlAp = false;}
      if(clGsfnFGBr == true){clGsfnFGBr = false;}
      if(sGzufLlOqt == true){sGzufLlOqt = false;}
      if(cfnkHVUBrT == true){cfnkHVUBrT = false;}
      if(XYhuJJqVZL == true){XYhuJJqVZL = false;}
      if(oeOFGRbIRM == true){oeOFGRbIRM = false;}
      if(xiuGMwxVkJ == true){xiuGMwxVkJ = false;}
      if(TDOhUUXDlW == true){TDOhUUXDlW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ACBNJGADBC
{ 
  void RMrQyaMLLz()
  { 
      bool JeWcrJScdU = false;
      bool PtwiOpTfqZ = false;
      bool QImwnTJnNA = false;
      bool qMqJfoSDmn = false;
      bool gbuZIaiBfY = false;
      bool EnwEHBrZnY = false;
      bool zdOddDDlCZ = false;
      bool XPsDroNMnN = false;
      bool kIIouDQlCe = false;
      bool wrONnCMQwE = false;
      bool XwyFBnurLR = false;
      bool mekampVZhZ = false;
      bool lQjXceAeOp = false;
      bool cwPionKCmH = false;
      bool HYajqRGnZx = false;
      bool flhVSGMZcV = false;
      bool mQcUoqPCkz = false;
      bool fTlaSNoAgL = false;
      bool XMERJpNsQh = false;
      bool bkZQTpuFtA = false;
      string HqmQqFQZdy;
      string QNjtPrdFwe;
      string opIbXVdARB;
      string LORcqhkuDa;
      string WWEjaowLlX;
      string uUCyuRhLsU;
      string aQHblCwGDg;
      string GiBVHSlYAh;
      string ZSNtFpLSgZ;
      string AYChzGPbxX;
      string soIFQLSgpc;
      string eILKuICMWu;
      string qcZcghgTVB;
      string CJacokJIdt;
      string XebEtqNrmq;
      string DCFCgQPeYi;
      string ezKoZVhiUK;
      string yticXLAUio;
      string TofexAEYuY;
      string VejuOXTmdY;
      if(HqmQqFQZdy == soIFQLSgpc){JeWcrJScdU = true;}
      else if(soIFQLSgpc == HqmQqFQZdy){XwyFBnurLR = true;}
      if(QNjtPrdFwe == eILKuICMWu){PtwiOpTfqZ = true;}
      else if(eILKuICMWu == QNjtPrdFwe){mekampVZhZ = true;}
      if(opIbXVdARB == qcZcghgTVB){QImwnTJnNA = true;}
      else if(qcZcghgTVB == opIbXVdARB){lQjXceAeOp = true;}
      if(LORcqhkuDa == CJacokJIdt){qMqJfoSDmn = true;}
      else if(CJacokJIdt == LORcqhkuDa){cwPionKCmH = true;}
      if(WWEjaowLlX == XebEtqNrmq){gbuZIaiBfY = true;}
      else if(XebEtqNrmq == WWEjaowLlX){HYajqRGnZx = true;}
      if(uUCyuRhLsU == DCFCgQPeYi){EnwEHBrZnY = true;}
      else if(DCFCgQPeYi == uUCyuRhLsU){flhVSGMZcV = true;}
      if(aQHblCwGDg == ezKoZVhiUK){zdOddDDlCZ = true;}
      else if(ezKoZVhiUK == aQHblCwGDg){mQcUoqPCkz = true;}
      if(GiBVHSlYAh == yticXLAUio){XPsDroNMnN = true;}
      if(ZSNtFpLSgZ == TofexAEYuY){kIIouDQlCe = true;}
      if(AYChzGPbxX == VejuOXTmdY){wrONnCMQwE = true;}
      while(yticXLAUio == GiBVHSlYAh){fTlaSNoAgL = true;}
      while(TofexAEYuY == TofexAEYuY){XMERJpNsQh = true;}
      while(VejuOXTmdY == VejuOXTmdY){bkZQTpuFtA = true;}
      if(JeWcrJScdU == true){JeWcrJScdU = false;}
      if(PtwiOpTfqZ == true){PtwiOpTfqZ = false;}
      if(QImwnTJnNA == true){QImwnTJnNA = false;}
      if(qMqJfoSDmn == true){qMqJfoSDmn = false;}
      if(gbuZIaiBfY == true){gbuZIaiBfY = false;}
      if(EnwEHBrZnY == true){EnwEHBrZnY = false;}
      if(zdOddDDlCZ == true){zdOddDDlCZ = false;}
      if(XPsDroNMnN == true){XPsDroNMnN = false;}
      if(kIIouDQlCe == true){kIIouDQlCe = false;}
      if(wrONnCMQwE == true){wrONnCMQwE = false;}
      if(XwyFBnurLR == true){XwyFBnurLR = false;}
      if(mekampVZhZ == true){mekampVZhZ = false;}
      if(lQjXceAeOp == true){lQjXceAeOp = false;}
      if(cwPionKCmH == true){cwPionKCmH = false;}
      if(HYajqRGnZx == true){HYajqRGnZx = false;}
      if(flhVSGMZcV == true){flhVSGMZcV = false;}
      if(mQcUoqPCkz == true){mQcUoqPCkz = false;}
      if(fTlaSNoAgL == true){fTlaSNoAgL = false;}
      if(XMERJpNsQh == true){XMERJpNsQh = false;}
      if(bkZQTpuFtA == true){bkZQTpuFtA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HJRRYHYDKU
{ 
  void IFfMXGPZex()
  { 
      bool zMuELJPppw = false;
      bool oiwTHDZLxn = false;
      bool oRBiwVKKcb = false;
      bool YVIXjbXVPt = false;
      bool TtLbxtkDmF = false;
      bool moraggKMIp = false;
      bool zENNWSaXje = false;
      bool eEwDTuFZlB = false;
      bool jHXXoidgqC = false;
      bool QLNYtOfyEd = false;
      bool TNSIZiroGk = false;
      bool bkaGGrgpYm = false;
      bool osggNTqXIE = false;
      bool PHUHhVnPxF = false;
      bool qoaFafkGSC = false;
      bool hpYRoagltG = false;
      bool qUfBVTQSYj = false;
      bool ERrSwzRaFh = false;
      bool hjEGWYhDSG = false;
      bool oBUqOVIYiH = false;
      string SzywuCHWZk;
      string LizNSgqiGq;
      string ETczsnTPMO;
      string NdnXjsCdsY;
      string sdIITApMgA;
      string WuKwFzWyDG;
      string irKLWhtbcY;
      string dMpgyaKTfs;
      string yHiMqSSqRk;
      string VEalpBTxkk;
      string FOiHVJEdye;
      string nCSJIaJxTE;
      string PDJrDZlEpw;
      string GNitniXbqg;
      string OormxSkRdO;
      string rWcfVBFqEw;
      string XAmCXZTYVZ;
      string ChGlpZLWuj;
      string nTZaEjjCXl;
      string cgWuJNBoOW;
      if(SzywuCHWZk == FOiHVJEdye){zMuELJPppw = true;}
      else if(FOiHVJEdye == SzywuCHWZk){TNSIZiroGk = true;}
      if(LizNSgqiGq == nCSJIaJxTE){oiwTHDZLxn = true;}
      else if(nCSJIaJxTE == LizNSgqiGq){bkaGGrgpYm = true;}
      if(ETczsnTPMO == PDJrDZlEpw){oRBiwVKKcb = true;}
      else if(PDJrDZlEpw == ETczsnTPMO){osggNTqXIE = true;}
      if(NdnXjsCdsY == GNitniXbqg){YVIXjbXVPt = true;}
      else if(GNitniXbqg == NdnXjsCdsY){PHUHhVnPxF = true;}
      if(sdIITApMgA == OormxSkRdO){TtLbxtkDmF = true;}
      else if(OormxSkRdO == sdIITApMgA){qoaFafkGSC = true;}
      if(WuKwFzWyDG == rWcfVBFqEw){moraggKMIp = true;}
      else if(rWcfVBFqEw == WuKwFzWyDG){hpYRoagltG = true;}
      if(irKLWhtbcY == XAmCXZTYVZ){zENNWSaXje = true;}
      else if(XAmCXZTYVZ == irKLWhtbcY){qUfBVTQSYj = true;}
      if(dMpgyaKTfs == ChGlpZLWuj){eEwDTuFZlB = true;}
      if(yHiMqSSqRk == nTZaEjjCXl){jHXXoidgqC = true;}
      if(VEalpBTxkk == cgWuJNBoOW){QLNYtOfyEd = true;}
      while(ChGlpZLWuj == dMpgyaKTfs){ERrSwzRaFh = true;}
      while(nTZaEjjCXl == nTZaEjjCXl){hjEGWYhDSG = true;}
      while(cgWuJNBoOW == cgWuJNBoOW){oBUqOVIYiH = true;}
      if(zMuELJPppw == true){zMuELJPppw = false;}
      if(oiwTHDZLxn == true){oiwTHDZLxn = false;}
      if(oRBiwVKKcb == true){oRBiwVKKcb = false;}
      if(YVIXjbXVPt == true){YVIXjbXVPt = false;}
      if(TtLbxtkDmF == true){TtLbxtkDmF = false;}
      if(moraggKMIp == true){moraggKMIp = false;}
      if(zENNWSaXje == true){zENNWSaXje = false;}
      if(eEwDTuFZlB == true){eEwDTuFZlB = false;}
      if(jHXXoidgqC == true){jHXXoidgqC = false;}
      if(QLNYtOfyEd == true){QLNYtOfyEd = false;}
      if(TNSIZiroGk == true){TNSIZiroGk = false;}
      if(bkaGGrgpYm == true){bkaGGrgpYm = false;}
      if(osggNTqXIE == true){osggNTqXIE = false;}
      if(PHUHhVnPxF == true){PHUHhVnPxF = false;}
      if(qoaFafkGSC == true){qoaFafkGSC = false;}
      if(hpYRoagltG == true){hpYRoagltG = false;}
      if(qUfBVTQSYj == true){qUfBVTQSYj = false;}
      if(ERrSwzRaFh == true){ERrSwzRaFh = false;}
      if(hjEGWYhDSG == true){hjEGWYhDSG = false;}
      if(oBUqOVIYiH == true){oBUqOVIYiH = false;}
    } 
}; 
