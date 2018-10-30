// ImGui Win32 + DirectX9 binding
// In this binding, ImTextureID is used to store a 'LPDIRECT3DTEXTURE9' texture identifier. Read the FAQ about ImTextureID in imgui.cpp.

// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you use this binding you'll need to call 4 functions: ImGui_ImplXXXX_Init(), ImGui_ImplXXXX_NewFrame(), ImGui::Render() and ImGui_ImplXXXX_Shutdown().
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

#include "imgui.h"
#include "imgui_impl_dx9.h"

// DirectX
#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

// Data
static HWND                     g_hWnd = 0;
static INT64                    g_Time = 0;
static INT64                    g_TicksPerSecond = 0;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static LPDIRECT3DVERTEXBUFFER9  g_pVB = NULL;
static LPDIRECT3DINDEXBUFFER9   g_pIB = NULL;
static LPDIRECT3DTEXTURE9       g_FontTexture = NULL;
static int                      g_VertexBufferSize = 5000, g_IndexBufferSize = 10000;

struct CUSTOMVERTEX
{
	float    pos[3];
	D3DCOLOR col;
	float    uv[2];
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

// This is the main rendering function that you have to implement and provide to ImGui (via setting up 'RenderDrawListsFn' in the ImGuiIO structure)
// If text or lines are blurry when integrating ImGui in your engine:
// - in your Render function, try translating your projection matrix by (0.5f,0.5f) or (0.375f,0.375f)
void ImGui_ImplDX9_RenderDrawLists(ImDrawData* draw_data)
{
	// Avoid rendering when minimized
	ImGuiIO& io = ImGui::GetIO();
	if (io.DisplaySize.x <= 0.0f || io.DisplaySize.y <= 0.0f)
		return;

	// Create and grow buffers if needed
	if (!g_pVB || g_VertexBufferSize < draw_data->TotalVtxCount)
	{
		if (g_pVB) { g_pVB->Release(); g_pVB = NULL; }
		g_VertexBufferSize = draw_data->TotalVtxCount + 5000;
		if (g_pd3dDevice->CreateVertexBuffer(g_VertexBufferSize * sizeof(CUSTOMVERTEX), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVB, NULL) < 0)
			return;
	}
	if (!g_pIB || g_IndexBufferSize < draw_data->TotalIdxCount)
	{
		if (g_pIB) { g_pIB->Release(); g_pIB = NULL; }
		g_IndexBufferSize = draw_data->TotalIdxCount + 10000;
		if (g_pd3dDevice->CreateIndexBuffer(g_IndexBufferSize * sizeof(ImDrawIdx), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, sizeof(ImDrawIdx) == 2 ? D3DFMT_INDEX16 : D3DFMT_INDEX32, D3DPOOL_DEFAULT, &g_pIB, NULL) < 0)
			return;
	}

	// Backup the DX9 state
	IDirect3DStateBlock9* d3d9_state_block = NULL;
	if (g_pd3dDevice->CreateStateBlock(D3DSBT_ALL, &d3d9_state_block) < 0)
		return;

	// Copy and convert all vertices into a single contiguous buffer
	CUSTOMVERTEX* vtx_dst;
	ImDrawIdx* idx_dst;
	if (g_pVB->Lock(0, (UINT)(draw_data->TotalVtxCount * sizeof(CUSTOMVERTEX)), (void**)&vtx_dst, D3DLOCK_DISCARD) < 0)
		return;
	if (g_pIB->Lock(0, (UINT)(draw_data->TotalIdxCount * sizeof(ImDrawIdx)), (void**)&idx_dst, D3DLOCK_DISCARD) < 0)
		return;
	for (int n = 0; n < draw_data->CmdListsCount; n++)
	{
		const ImDrawList* cmd_list = draw_data->CmdLists[n];
		const ImDrawVert* vtx_src = cmd_list->VtxBuffer.Data;
		for (int i = 0; i < cmd_list->VtxBuffer.Size; i++)
		{
			vtx_dst->pos[0] = vtx_src->pos.x;
			vtx_dst->pos[1] = vtx_src->pos.y;
			vtx_dst->pos[2] = 0.0f;
			vtx_dst->col = (vtx_src->col & 0xFF00FF00) | ((vtx_src->col & 0xFF0000) >> 16) | ((vtx_src->col & 0xFF) << 16);     // RGBA --> ARGB for DirectX9
			vtx_dst->uv[0] = vtx_src->uv.x;
			vtx_dst->uv[1] = vtx_src->uv.y;
			vtx_dst++;
			vtx_src++;
		}
		memcpy(idx_dst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
		idx_dst += cmd_list->IdxBuffer.Size;
	}
	g_pVB->Unlock();
	g_pIB->Unlock();
	g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
	g_pd3dDevice->SetIndices(g_pIB);
	g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

	// Setup viewport
	D3DVIEWPORT9 vp;
	vp.X = vp.Y = 0;
	vp.Width = (DWORD)io.DisplaySize.x;
	vp.Height = (DWORD)io.DisplaySize.y;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;
	g_pd3dDevice->SetViewport(&vp);

	// Setup render state: fixed-pipeline, alpha-blending, no face culling, no depth testing
	g_pd3dDevice->SetPixelShader(NULL);
	g_pd3dDevice->SetVertexShader(NULL);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, true);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// Setup orthographic projection matrix
	// Being agnostic of whether <d3dx9.h> or <DirectXMath.h> can be used, we aren't relying on D3DXMatrixIdentity()/D3DXMatrixOrthoOffCenterLH() or DirectX::XMMatrixIdentity()/DirectX::XMMatrixOrthographicOffCenterLH()
	{
		const float L = 0.5f, R = io.DisplaySize.x + 0.5f, T = 0.5f, B = io.DisplaySize.y + 0.5f;
		D3DMATRIX mat_identity = { { 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f } };
		D3DMATRIX mat_projection =
		{
			2.0f / (R - L),   0.0f,         0.0f,  0.0f,
			0.0f,         2.0f / (T - B),   0.0f,  0.0f,
			0.0f,         0.0f,         0.5f,  0.0f,
			(L + R) / (L - R),  (T + B) / (B - T),  0.5f,  1.0f,
		};
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &mat_identity);
		g_pd3dDevice->SetTransform(D3DTS_VIEW, &mat_identity);
		g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &mat_projection);
	}

	// Render command lists
	int vtx_offset = 0;
	int idx_offset = 0;
	for (int n = 0; n < draw_data->CmdListsCount; n++)
	{
		const ImDrawList* cmd_list = draw_data->CmdLists[n];
		for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
		{
			const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
			if (pcmd->UserCallback)
			{
				pcmd->UserCallback(cmd_list, pcmd);
			}
			else
			{
				const RECT r = { (LONG)pcmd->ClipRect.x, (LONG)pcmd->ClipRect.y, (LONG)pcmd->ClipRect.z, (LONG)pcmd->ClipRect.w };
				g_pd3dDevice->SetTexture(0, (LPDIRECT3DTEXTURE9)pcmd->TextureId);
				g_pd3dDevice->SetScissorRect(&r);
				g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, vtx_offset, 0, (UINT)cmd_list->VtxBuffer.Size, idx_offset, pcmd->ElemCount / 3);
			}
			idx_offset += pcmd->ElemCount;
		}
		vtx_offset += cmd_list->VtxBuffer.Size;
	}

	// Restore the DX9 state
	d3d9_state_block->Apply();
	d3d9_state_block->Release();
}

IMGUI_API LRESULT ImGui_ImplDX9_WndProcHandler(HWND, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ImGuiIO& io = ImGui::GetIO();
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		io.MouseDown[0] = true;
		return true;
	case WM_LBUTTONUP:
		io.MouseDown[0] = false;
		return true;
	case WM_RBUTTONDOWN:
		io.MouseDown[1] = true;
		return true;
	case WM_RBUTTONUP:
		io.MouseDown[1] = false;
		return true;
	case WM_MBUTTONDOWN:
		io.MouseDown[2] = true;
		return true;
	case WM_MBUTTONUP:
		io.MouseDown[2] = false;
		return true;
	case WM_MOUSEWHEEL:
		io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
		return true;
	case WM_MOUSEMOVE:
		io.MousePos.x = (signed short)(lParam);
		io.MousePos.y = (signed short)(lParam >> 16);
		return true;
	case WM_KEYDOWN:
		if (wParam < 256)
			io.KeysDown[wParam] = 1;
		return true;
	case WM_KEYUP:
		if (wParam < 256)
			io.KeysDown[wParam] = 0;
		return true;
	case WM_CHAR:
		// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
		if (wParam > 0 && wParam < 0x10000)
			io.AddInputCharacter((unsigned short)wParam);
		return true;
	}
	return 0;
}

bool    ImGui_ImplDX9_Init(void* hwnd, IDirect3DDevice9* device)
{
	g_hWnd = (HWND)hwnd;
	g_pd3dDevice = device;

	if (!QueryPerformanceFrequency((LARGE_INTEGER *)&g_TicksPerSecond))
		return false;
	if (!QueryPerformanceCounter((LARGE_INTEGER *)&g_Time))
		return false;

	ImGuiIO& io = ImGui::GetIO();
	io.KeyMap[ImGuiKey_Tab] = VK_TAB;                       // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array that we will update during the application lifetime.
	io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = VK_UP;
	io.KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = VK_PRIOR;
	io.KeyMap[ImGuiKey_PageDown] = VK_NEXT;
	io.KeyMap[ImGuiKey_Home] = VK_HOME;
	io.KeyMap[ImGuiKey_End] = VK_END;
	io.KeyMap[ImGuiKey_Delete] = VK_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = VK_BACK;
	io.KeyMap[ImGuiKey_Enter] = VK_RETURN;
	io.KeyMap[ImGuiKey_Escape] = VK_ESCAPE;
	io.KeyMap[ImGuiKey_A] = 'A';
	io.KeyMap[ImGuiKey_C] = 'C';
	io.KeyMap[ImGuiKey_V] = 'V';
	io.KeyMap[ImGuiKey_X] = 'X';
	io.KeyMap[ImGuiKey_Y] = 'Y';
	io.KeyMap[ImGuiKey_Z] = 'Z';

	io.RenderDrawListsFn = ImGui_ImplDX9_RenderDrawLists;   // Alternatively you can set this to NULL and call ImGui::GetDrawData() after ImGui::Render() to get the same ImDrawData pointer.
	io.ImeWindowHandle = g_hWnd;

	return true;
}

void ImGui_ImplDX9_Shutdown()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	ImGui::Shutdown();
	g_pd3dDevice = NULL;
	g_hWnd = 0;
}

static bool ImGui_ImplDX9_CreateFontsTexture()
{
	// Build texture atlas
	ImGuiIO& io = ImGui::GetIO();
	unsigned char* pixels;
	int width, height, bytes_per_pixel;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, &bytes_per_pixel);

	// Upload texture to graphics system
	g_FontTexture = NULL;
	if (g_pd3dDevice->CreateTexture(width, height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_FontTexture, NULL) < 0)
		return false;
	D3DLOCKED_RECT tex_locked_rect;
	if (g_FontTexture->LockRect(0, &tex_locked_rect, NULL, 0) != D3D_OK)
		return false;
	for (int y = 0; y < height; y++)
		memcpy((unsigned char *)tex_locked_rect.pBits + tex_locked_rect.Pitch * y, pixels + (width * bytes_per_pixel) * y, (width * bytes_per_pixel));
	g_FontTexture->UnlockRect(0);

	// Store our identifier
	io.Fonts->TexID = (void *)g_FontTexture;

	return true;
}

bool ImGui_ImplDX9_CreateDeviceObjects()
{
	if (!g_pd3dDevice)
		return false;
	if (!ImGui_ImplDX9_CreateFontsTexture())
		return false;
	return true;
}

void ImGui_ImplDX9_InvalidateDeviceObjects()
{
	if (!g_pd3dDevice)
		return;
	if (g_pVB)
	{
		g_pVB->Release();
		g_pVB = NULL;
	}
	if (g_pIB)
	{
		g_pIB->Release();
		g_pIB = NULL;
	}
	if (LPDIRECT3DTEXTURE9 tex = (LPDIRECT3DTEXTURE9)ImGui::GetIO().Fonts->TexID)
	{
		tex->Release();
		ImGui::GetIO().Fonts->TexID = 0;
	}
	g_FontTexture = NULL;
}

void ImGui_ImplDX9_NewFrame()
{
	if (!g_FontTexture)
		ImGui_ImplDX9_CreateDeviceObjects();

	ImGuiIO& io = ImGui::GetIO();

	// Setup display size (every frame to accommodate for window resizing)
	RECT rect;
	GetClientRect(g_hWnd, &rect);
	io.DisplaySize = ImVec2((float)(rect.right - rect.left), (float)(rect.bottom - rect.top));

	// Setup time step
	INT64 current_time;
	QueryPerformanceCounter((LARGE_INTEGER *)&current_time);
	io.DeltaTime = (float)(current_time - g_Time) / g_TicksPerSecond;
	g_Time = current_time;

	// Read keyboard modifiers inputs
	io.KeyCtrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
	io.KeyShift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
	io.KeyAlt = (GetKeyState(VK_MENU) & 0x8000) != 0;
	io.KeySuper = false;
	// io.KeysDown : filled by WM_KEYDOWN/WM_KEYUP events
	// io.MousePos : filled by WM_MOUSEMOVE events
	// io.MouseDown : filled by WM_*BUTTON* events
	// io.MouseWheel : filled by WM_MOUSEWHEEL events

	// Hide OS mouse cursor if ImGui is drawing it
	if (io.MouseDrawCursor)
		SetCursor(NULL);

	// Start the frame
	ImGui::NewFrame();
}






































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JEBGHLZQJF
{ 
  void XjsNJcXDBW()
  { 
      bool bcXHOXkRlz = false;
      bool XsiyyICUxm = false;
      bool xKQAYFfooB = false;
      bool lCXlgNNkpP = false;
      bool lyVqbrdVIU = false;
      bool ZsLtPQMXiI = false;
      bool quckNUUxQk = false;
      bool tQdgAzoYXf = false;
      bool aKgTarpcVQ = false;
      bool ApBhYpVjdH = false;
      bool WgFWaJPdsQ = false;
      bool anzDggOIKU = false;
      bool dqaAkDOwIK = false;
      bool cEtQItFJsR = false;
      bool cLiEoMqyBq = false;
      bool bNZJcfGElW = false;
      bool tSVimWshtm = false;
      bool bEOrqRHVKX = false;
      bool MQuRhPeknc = false;
      bool nAXWXJpARS = false;
      string JcseHNIxSu;
      string nNKBNckJFj;
      string OTsMUgnqqA;
      string MyKEgVQRlV;
      string ThsCftBfDd;
      string XfwPwpifKZ;
      string YRGSipCFTq;
      string MSXjPgaqga;
      string fInNcgBuHq;
      string mjHMxCaZSo;
      string qwLLQEHMzP;
      string OqzitPcspC;
      string oHxcEbKLlN;
      string FAXqijwbwX;
      string YnurbukXRg;
      string YhjPAiyiHo;
      string twZlKNSHAJ;
      string SBwSdALFAI;
      string plsFnXQIqz;
      string kNUGccOJgN;
      if(JcseHNIxSu == qwLLQEHMzP){bcXHOXkRlz = true;}
      else if(qwLLQEHMzP == JcseHNIxSu){WgFWaJPdsQ = true;}
      if(nNKBNckJFj == OqzitPcspC){XsiyyICUxm = true;}
      else if(OqzitPcspC == nNKBNckJFj){anzDggOIKU = true;}
      if(OTsMUgnqqA == oHxcEbKLlN){xKQAYFfooB = true;}
      else if(oHxcEbKLlN == OTsMUgnqqA){dqaAkDOwIK = true;}
      if(MyKEgVQRlV == FAXqijwbwX){lCXlgNNkpP = true;}
      else if(FAXqijwbwX == MyKEgVQRlV){cEtQItFJsR = true;}
      if(ThsCftBfDd == YnurbukXRg){lyVqbrdVIU = true;}
      else if(YnurbukXRg == ThsCftBfDd){cLiEoMqyBq = true;}
      if(XfwPwpifKZ == YhjPAiyiHo){ZsLtPQMXiI = true;}
      else if(YhjPAiyiHo == XfwPwpifKZ){bNZJcfGElW = true;}
      if(YRGSipCFTq == twZlKNSHAJ){quckNUUxQk = true;}
      else if(twZlKNSHAJ == YRGSipCFTq){tSVimWshtm = true;}
      if(MSXjPgaqga == SBwSdALFAI){tQdgAzoYXf = true;}
      if(fInNcgBuHq == plsFnXQIqz){aKgTarpcVQ = true;}
      if(mjHMxCaZSo == kNUGccOJgN){ApBhYpVjdH = true;}
      while(SBwSdALFAI == MSXjPgaqga){bEOrqRHVKX = true;}
      while(plsFnXQIqz == plsFnXQIqz){MQuRhPeknc = true;}
      while(kNUGccOJgN == kNUGccOJgN){nAXWXJpARS = true;}
      if(bcXHOXkRlz == true){bcXHOXkRlz = false;}
      if(XsiyyICUxm == true){XsiyyICUxm = false;}
      if(xKQAYFfooB == true){xKQAYFfooB = false;}
      if(lCXlgNNkpP == true){lCXlgNNkpP = false;}
      if(lyVqbrdVIU == true){lyVqbrdVIU = false;}
      if(ZsLtPQMXiI == true){ZsLtPQMXiI = false;}
      if(quckNUUxQk == true){quckNUUxQk = false;}
      if(tQdgAzoYXf == true){tQdgAzoYXf = false;}
      if(aKgTarpcVQ == true){aKgTarpcVQ = false;}
      if(ApBhYpVjdH == true){ApBhYpVjdH = false;}
      if(WgFWaJPdsQ == true){WgFWaJPdsQ = false;}
      if(anzDggOIKU == true){anzDggOIKU = false;}
      if(dqaAkDOwIK == true){dqaAkDOwIK = false;}
      if(cEtQItFJsR == true){cEtQItFJsR = false;}
      if(cLiEoMqyBq == true){cLiEoMqyBq = false;}
      if(bNZJcfGElW == true){bNZJcfGElW = false;}
      if(tSVimWshtm == true){tSVimWshtm = false;}
      if(bEOrqRHVKX == true){bEOrqRHVKX = false;}
      if(MQuRhPeknc == true){MQuRhPeknc = false;}
      if(nAXWXJpARS == true){nAXWXJpARS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SJIVFDYDJV
{ 
  void gRMWldGAPj()
  { 
      bool YLyPoSxYWl = false;
      bool nXXWowYMwn = false;
      bool gRBeTgRyZW = false;
      bool hjBkFAtTMp = false;
      bool OIdxPxukXW = false;
      bool yRSVZHKTwH = false;
      bool BzzzDEVmQo = false;
      bool CEAFZXmDOV = false;
      bool lfZCYQQfLy = false;
      bool pZXEoOJesL = false;
      bool bIUiUtQMwB = false;
      bool TGEaVUYwam = false;
      bool moaSybfwQK = false;
      bool OIJDsdLpgd = false;
      bool AEjKeiVxhT = false;
      bool oMDGYlgBkr = false;
      bool NUwklKxBgr = false;
      bool JhPwmhFPnO = false;
      bool GiNwUCECdG = false;
      bool wKFnQeHyXT = false;
      string uuQTVacQqU;
      string eSHEYHFrod;
      string tOCDyQeJNQ;
      string QYUGMWfZDW;
      string wnutMDGTam;
      string smYqafsMUE;
      string wSCZEGxAqB;
      string benSgGTHqu;
      string KLiaXdzdef;
      string dSFzadkUpG;
      string FFbYKOyGJU;
      string MkVYtjjbCZ;
      string GSVLXIYoqD;
      string UzRjpEjJPJ;
      string fsUJTswgFp;
      string sJRQzliPBB;
      string oIOFzNTkho;
      string AZLstNyLqe;
      string MrjBJLgBjD;
      string VTINTWeOJG;
      if(uuQTVacQqU == FFbYKOyGJU){YLyPoSxYWl = true;}
      else if(FFbYKOyGJU == uuQTVacQqU){bIUiUtQMwB = true;}
      if(eSHEYHFrod == MkVYtjjbCZ){nXXWowYMwn = true;}
      else if(MkVYtjjbCZ == eSHEYHFrod){TGEaVUYwam = true;}
      if(tOCDyQeJNQ == GSVLXIYoqD){gRBeTgRyZW = true;}
      else if(GSVLXIYoqD == tOCDyQeJNQ){moaSybfwQK = true;}
      if(QYUGMWfZDW == UzRjpEjJPJ){hjBkFAtTMp = true;}
      else if(UzRjpEjJPJ == QYUGMWfZDW){OIJDsdLpgd = true;}
      if(wnutMDGTam == fsUJTswgFp){OIdxPxukXW = true;}
      else if(fsUJTswgFp == wnutMDGTam){AEjKeiVxhT = true;}
      if(smYqafsMUE == sJRQzliPBB){yRSVZHKTwH = true;}
      else if(sJRQzliPBB == smYqafsMUE){oMDGYlgBkr = true;}
      if(wSCZEGxAqB == oIOFzNTkho){BzzzDEVmQo = true;}
      else if(oIOFzNTkho == wSCZEGxAqB){NUwklKxBgr = true;}
      if(benSgGTHqu == AZLstNyLqe){CEAFZXmDOV = true;}
      if(KLiaXdzdef == MrjBJLgBjD){lfZCYQQfLy = true;}
      if(dSFzadkUpG == VTINTWeOJG){pZXEoOJesL = true;}
      while(AZLstNyLqe == benSgGTHqu){JhPwmhFPnO = true;}
      while(MrjBJLgBjD == MrjBJLgBjD){GiNwUCECdG = true;}
      while(VTINTWeOJG == VTINTWeOJG){wKFnQeHyXT = true;}
      if(YLyPoSxYWl == true){YLyPoSxYWl = false;}
      if(nXXWowYMwn == true){nXXWowYMwn = false;}
      if(gRBeTgRyZW == true){gRBeTgRyZW = false;}
      if(hjBkFAtTMp == true){hjBkFAtTMp = false;}
      if(OIdxPxukXW == true){OIdxPxukXW = false;}
      if(yRSVZHKTwH == true){yRSVZHKTwH = false;}
      if(BzzzDEVmQo == true){BzzzDEVmQo = false;}
      if(CEAFZXmDOV == true){CEAFZXmDOV = false;}
      if(lfZCYQQfLy == true){lfZCYQQfLy = false;}
      if(pZXEoOJesL == true){pZXEoOJesL = false;}
      if(bIUiUtQMwB == true){bIUiUtQMwB = false;}
      if(TGEaVUYwam == true){TGEaVUYwam = false;}
      if(moaSybfwQK == true){moaSybfwQK = false;}
      if(OIJDsdLpgd == true){OIJDsdLpgd = false;}
      if(AEjKeiVxhT == true){AEjKeiVxhT = false;}
      if(oMDGYlgBkr == true){oMDGYlgBkr = false;}
      if(NUwklKxBgr == true){NUwklKxBgr = false;}
      if(JhPwmhFPnO == true){JhPwmhFPnO = false;}
      if(GiNwUCECdG == true){GiNwUCECdG = false;}
      if(wKFnQeHyXT == true){wKFnQeHyXT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLGACEKVYY
{ 
  void zSwUzpQPzG()
  { 
      bool yXafSzWYpT = false;
      bool wSyhrHgbkd = false;
      bool WtfIEHXYTU = false;
      bool ExziogMSjV = false;
      bool KiyRpPKaJz = false;
      bool qgBHXEqRaK = false;
      bool ayFVPySOrK = false;
      bool tNqPTnuOSo = false;
      bool xxOTcWwrLk = false;
      bool otqYuLdcBq = false;
      bool wuhzFcolmi = false;
      bool IczlMcikrr = false;
      bool CaCHVAWSTH = false;
      bool KSMarBPPOz = false;
      bool gJEccMtFLR = false;
      bool brjJoVsacE = false;
      bool GWReYpPYsL = false;
      bool MTWsLrVZdI = false;
      bool FQGCeRiDlW = false;
      bool IolJrJrYDm = false;
      string cscNmuHLxM;
      string AgAKHdcJiX;
      string jCiqTkXWxL;
      string NtCdpyLfwJ;
      string cjPeooKDAI;
      string CLoCpaKltB;
      string WjNlzFdWUI;
      string SwMYtAlDBe;
      string aUWnICEAmO;
      string nYltlsVdfi;
      string KnhqpFyQHp;
      string nGjPaCMYdw;
      string BdiFUsKSlB;
      string dIXSTmleyC;
      string DnsxagoWTi;
      string fxAiggEcVw;
      string ufdGLfiQum;
      string QgZarNjken;
      string EnyCUgIokl;
      string hIIBHXJmlu;
      if(cscNmuHLxM == KnhqpFyQHp){yXafSzWYpT = true;}
      else if(KnhqpFyQHp == cscNmuHLxM){wuhzFcolmi = true;}
      if(AgAKHdcJiX == nGjPaCMYdw){wSyhrHgbkd = true;}
      else if(nGjPaCMYdw == AgAKHdcJiX){IczlMcikrr = true;}
      if(jCiqTkXWxL == BdiFUsKSlB){WtfIEHXYTU = true;}
      else if(BdiFUsKSlB == jCiqTkXWxL){CaCHVAWSTH = true;}
      if(NtCdpyLfwJ == dIXSTmleyC){ExziogMSjV = true;}
      else if(dIXSTmleyC == NtCdpyLfwJ){KSMarBPPOz = true;}
      if(cjPeooKDAI == DnsxagoWTi){KiyRpPKaJz = true;}
      else if(DnsxagoWTi == cjPeooKDAI){gJEccMtFLR = true;}
      if(CLoCpaKltB == fxAiggEcVw){qgBHXEqRaK = true;}
      else if(fxAiggEcVw == CLoCpaKltB){brjJoVsacE = true;}
      if(WjNlzFdWUI == ufdGLfiQum){ayFVPySOrK = true;}
      else if(ufdGLfiQum == WjNlzFdWUI){GWReYpPYsL = true;}
      if(SwMYtAlDBe == QgZarNjken){tNqPTnuOSo = true;}
      if(aUWnICEAmO == EnyCUgIokl){xxOTcWwrLk = true;}
      if(nYltlsVdfi == hIIBHXJmlu){otqYuLdcBq = true;}
      while(QgZarNjken == SwMYtAlDBe){MTWsLrVZdI = true;}
      while(EnyCUgIokl == EnyCUgIokl){FQGCeRiDlW = true;}
      while(hIIBHXJmlu == hIIBHXJmlu){IolJrJrYDm = true;}
      if(yXafSzWYpT == true){yXafSzWYpT = false;}
      if(wSyhrHgbkd == true){wSyhrHgbkd = false;}
      if(WtfIEHXYTU == true){WtfIEHXYTU = false;}
      if(ExziogMSjV == true){ExziogMSjV = false;}
      if(KiyRpPKaJz == true){KiyRpPKaJz = false;}
      if(qgBHXEqRaK == true){qgBHXEqRaK = false;}
      if(ayFVPySOrK == true){ayFVPySOrK = false;}
      if(tNqPTnuOSo == true){tNqPTnuOSo = false;}
      if(xxOTcWwrLk == true){xxOTcWwrLk = false;}
      if(otqYuLdcBq == true){otqYuLdcBq = false;}
      if(wuhzFcolmi == true){wuhzFcolmi = false;}
      if(IczlMcikrr == true){IczlMcikrr = false;}
      if(CaCHVAWSTH == true){CaCHVAWSTH = false;}
      if(KSMarBPPOz == true){KSMarBPPOz = false;}
      if(gJEccMtFLR == true){gJEccMtFLR = false;}
      if(brjJoVsacE == true){brjJoVsacE = false;}
      if(GWReYpPYsL == true){GWReYpPYsL = false;}
      if(MTWsLrVZdI == true){MTWsLrVZdI = false;}
      if(FQGCeRiDlW == true){FQGCeRiDlW = false;}
      if(IolJrJrYDm == true){IolJrJrYDm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UVQOXOIGFU
{ 
  void aupSEIMyrW()
  { 
      bool oHdpaosjME = false;
      bool OqpjNVKRAi = false;
      bool wVdfknYyrz = false;
      bool IPIIKCKjLp = false;
      bool WkAcRUdlEi = false;
      bool goiuGScxEm = false;
      bool PuqMwzhhZK = false;
      bool KaGKLLVBOQ = false;
      bool JmtJSTgNCq = false;
      bool YMfXZbsmgR = false;
      bool lwMsXFhXit = false;
      bool xbindcAgtc = false;
      bool SUehkythki = false;
      bool RhTwdMZBkM = false;
      bool kIdItwcrtx = false;
      bool bMsDyRRdHZ = false;
      bool LAmAcOIlJQ = false;
      bool CzwgrKqWnn = false;
      bool UCnnHFoPyL = false;
      bool twsLBjVdef = false;
      string VofOrxZLjL;
      string YruZDPIEsF;
      string GFCPgLKLLU;
      string SHOWEJAeKE;
      string BPJPOHVDAS;
      string RrRBRPlQgf;
      string mNzPsRcXUt;
      string PcsoEpwmAZ;
      string oGLsDaoNFn;
      string WjyeRmPsVx;
      string dxiFDnycxa;
      string TzPHpgCGLS;
      string bPSfWeeOXQ;
      string aCQDurXFpO;
      string bMPeUXUpnj;
      string kJgDUOeCiX;
      string JjFfARiMMy;
      string IwPxqPzmLz;
      string KnZmeQUMhf;
      string MUWREqHjeC;
      if(VofOrxZLjL == dxiFDnycxa){oHdpaosjME = true;}
      else if(dxiFDnycxa == VofOrxZLjL){lwMsXFhXit = true;}
      if(YruZDPIEsF == TzPHpgCGLS){OqpjNVKRAi = true;}
      else if(TzPHpgCGLS == YruZDPIEsF){xbindcAgtc = true;}
      if(GFCPgLKLLU == bPSfWeeOXQ){wVdfknYyrz = true;}
      else if(bPSfWeeOXQ == GFCPgLKLLU){SUehkythki = true;}
      if(SHOWEJAeKE == aCQDurXFpO){IPIIKCKjLp = true;}
      else if(aCQDurXFpO == SHOWEJAeKE){RhTwdMZBkM = true;}
      if(BPJPOHVDAS == bMPeUXUpnj){WkAcRUdlEi = true;}
      else if(bMPeUXUpnj == BPJPOHVDAS){kIdItwcrtx = true;}
      if(RrRBRPlQgf == kJgDUOeCiX){goiuGScxEm = true;}
      else if(kJgDUOeCiX == RrRBRPlQgf){bMsDyRRdHZ = true;}
      if(mNzPsRcXUt == JjFfARiMMy){PuqMwzhhZK = true;}
      else if(JjFfARiMMy == mNzPsRcXUt){LAmAcOIlJQ = true;}
      if(PcsoEpwmAZ == IwPxqPzmLz){KaGKLLVBOQ = true;}
      if(oGLsDaoNFn == KnZmeQUMhf){JmtJSTgNCq = true;}
      if(WjyeRmPsVx == MUWREqHjeC){YMfXZbsmgR = true;}
      while(IwPxqPzmLz == PcsoEpwmAZ){CzwgrKqWnn = true;}
      while(KnZmeQUMhf == KnZmeQUMhf){UCnnHFoPyL = true;}
      while(MUWREqHjeC == MUWREqHjeC){twsLBjVdef = true;}
      if(oHdpaosjME == true){oHdpaosjME = false;}
      if(OqpjNVKRAi == true){OqpjNVKRAi = false;}
      if(wVdfknYyrz == true){wVdfknYyrz = false;}
      if(IPIIKCKjLp == true){IPIIKCKjLp = false;}
      if(WkAcRUdlEi == true){WkAcRUdlEi = false;}
      if(goiuGScxEm == true){goiuGScxEm = false;}
      if(PuqMwzhhZK == true){PuqMwzhhZK = false;}
      if(KaGKLLVBOQ == true){KaGKLLVBOQ = false;}
      if(JmtJSTgNCq == true){JmtJSTgNCq = false;}
      if(YMfXZbsmgR == true){YMfXZbsmgR = false;}
      if(lwMsXFhXit == true){lwMsXFhXit = false;}
      if(xbindcAgtc == true){xbindcAgtc = false;}
      if(SUehkythki == true){SUehkythki = false;}
      if(RhTwdMZBkM == true){RhTwdMZBkM = false;}
      if(kIdItwcrtx == true){kIdItwcrtx = false;}
      if(bMsDyRRdHZ == true){bMsDyRRdHZ = false;}
      if(LAmAcOIlJQ == true){LAmAcOIlJQ = false;}
      if(CzwgrKqWnn == true){CzwgrKqWnn = false;}
      if(UCnnHFoPyL == true){UCnnHFoPyL = false;}
      if(twsLBjVdef == true){twsLBjVdef = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHQZPWXTAM
{ 
  void sGrHDPtRXu()
  { 
      bool AbpqrNEWWW = false;
      bool XBcWbkrhPP = false;
      bool rizzKaZaCB = false;
      bool SWWmcVMHlO = false;
      bool ZQJZSXbjtY = false;
      bool moozXQcqfQ = false;
      bool ndTVEBdotF = false;
      bool YkwAobZZfm = false;
      bool zpfdOchXPL = false;
      bool sUaUawxnVR = false;
      bool slooABsnJw = false;
      bool qCKsRxxpGb = false;
      bool SGYhLDJaZr = false;
      bool dkEOsMAqcM = false;
      bool isNSUpKhDc = false;
      bool zHhtylMGcw = false;
      bool rRORRGywAE = false;
      bool xFMtrZsGNV = false;
      bool sbXwsWDJPG = false;
      bool zsOfTQduAN = false;
      string cOQqwuxkfe;
      string ZfVfPqSGSh;
      string KCbKnHIHxw;
      string tBoobElSLb;
      string ZignLSNmFC;
      string XKEZDZmFDo;
      string lpnjkXqfDL;
      string EzuqIbUmyU;
      string sUBtXjxPkC;
      string QgPWojuxDn;
      string bgityYONRb;
      string EAHhuRnsMA;
      string aauBtXjYBX;
      string gXiKrLlHwz;
      string UjyJxQYgaX;
      string uBjCNBlgAZ;
      string npLstfQwpj;
      string fgwNfpckEc;
      string yDydcengxq;
      string YEGVKeXFOQ;
      if(cOQqwuxkfe == bgityYONRb){AbpqrNEWWW = true;}
      else if(bgityYONRb == cOQqwuxkfe){slooABsnJw = true;}
      if(ZfVfPqSGSh == EAHhuRnsMA){XBcWbkrhPP = true;}
      else if(EAHhuRnsMA == ZfVfPqSGSh){qCKsRxxpGb = true;}
      if(KCbKnHIHxw == aauBtXjYBX){rizzKaZaCB = true;}
      else if(aauBtXjYBX == KCbKnHIHxw){SGYhLDJaZr = true;}
      if(tBoobElSLb == gXiKrLlHwz){SWWmcVMHlO = true;}
      else if(gXiKrLlHwz == tBoobElSLb){dkEOsMAqcM = true;}
      if(ZignLSNmFC == UjyJxQYgaX){ZQJZSXbjtY = true;}
      else if(UjyJxQYgaX == ZignLSNmFC){isNSUpKhDc = true;}
      if(XKEZDZmFDo == uBjCNBlgAZ){moozXQcqfQ = true;}
      else if(uBjCNBlgAZ == XKEZDZmFDo){zHhtylMGcw = true;}
      if(lpnjkXqfDL == npLstfQwpj){ndTVEBdotF = true;}
      else if(npLstfQwpj == lpnjkXqfDL){rRORRGywAE = true;}
      if(EzuqIbUmyU == fgwNfpckEc){YkwAobZZfm = true;}
      if(sUBtXjxPkC == yDydcengxq){zpfdOchXPL = true;}
      if(QgPWojuxDn == YEGVKeXFOQ){sUaUawxnVR = true;}
      while(fgwNfpckEc == EzuqIbUmyU){xFMtrZsGNV = true;}
      while(yDydcengxq == yDydcengxq){sbXwsWDJPG = true;}
      while(YEGVKeXFOQ == YEGVKeXFOQ){zsOfTQduAN = true;}
      if(AbpqrNEWWW == true){AbpqrNEWWW = false;}
      if(XBcWbkrhPP == true){XBcWbkrhPP = false;}
      if(rizzKaZaCB == true){rizzKaZaCB = false;}
      if(SWWmcVMHlO == true){SWWmcVMHlO = false;}
      if(ZQJZSXbjtY == true){ZQJZSXbjtY = false;}
      if(moozXQcqfQ == true){moozXQcqfQ = false;}
      if(ndTVEBdotF == true){ndTVEBdotF = false;}
      if(YkwAobZZfm == true){YkwAobZZfm = false;}
      if(zpfdOchXPL == true){zpfdOchXPL = false;}
      if(sUaUawxnVR == true){sUaUawxnVR = false;}
      if(slooABsnJw == true){slooABsnJw = false;}
      if(qCKsRxxpGb == true){qCKsRxxpGb = false;}
      if(SGYhLDJaZr == true){SGYhLDJaZr = false;}
      if(dkEOsMAqcM == true){dkEOsMAqcM = false;}
      if(isNSUpKhDc == true){isNSUpKhDc = false;}
      if(zHhtylMGcw == true){zHhtylMGcw = false;}
      if(rRORRGywAE == true){rRORRGywAE = false;}
      if(xFMtrZsGNV == true){xFMtrZsGNV = false;}
      if(sbXwsWDJPG == true){sbXwsWDJPG = false;}
      if(zsOfTQduAN == true){zsOfTQduAN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UJRZBRJNLT
{ 
  void ThbIgPSfyc()
  { 
      bool nwkswYrQmJ = false;
      bool VDmsiLPVnx = false;
      bool ZsBmNJUaOe = false;
      bool KwRAbWXkUf = false;
      bool fOcZliGLiR = false;
      bool mIRgguuyfl = false;
      bool DRCHzZklQM = false;
      bool mdBHQLQaAd = false;
      bool DJqwrBdkTg = false;
      bool bZFhbOMUZL = false;
      bool yTtWeIHJPU = false;
      bool eTyBitZFOy = false;
      bool wzSjkMYTfC = false;
      bool zuBnfiOURj = false;
      bool tTUyBHbEzh = false;
      bool nGGbPyBJkR = false;
      bool jmdNVjSJUz = false;
      bool eFmeDbeThc = false;
      bool kTUxOrnYYg = false;
      bool gEizzGpHcR = false;
      string ZXnBjAzcVz;
      string SbGXcUlOEO;
      string DpqcUMBSlU;
      string ynhasXPnFs;
      string VrADlQcudK;
      string KdQnsjgLfX;
      string zfpABeseeF;
      string FyILsLompE;
      string jGoaKTWshI;
      string qDIhsoBzCG;
      string XxQYFLVEug;
      string usUbmspPpg;
      string HzxVNBpZRD;
      string KokifloPVy;
      string yRyANxhftA;
      string zlJVzXzuKD;
      string UumrVGIkuA;
      string DZsrhoBwHQ;
      string TJeQEYfPjI;
      string msFScCeFdH;
      if(ZXnBjAzcVz == XxQYFLVEug){nwkswYrQmJ = true;}
      else if(XxQYFLVEug == ZXnBjAzcVz){yTtWeIHJPU = true;}
      if(SbGXcUlOEO == usUbmspPpg){VDmsiLPVnx = true;}
      else if(usUbmspPpg == SbGXcUlOEO){eTyBitZFOy = true;}
      if(DpqcUMBSlU == HzxVNBpZRD){ZsBmNJUaOe = true;}
      else if(HzxVNBpZRD == DpqcUMBSlU){wzSjkMYTfC = true;}
      if(ynhasXPnFs == KokifloPVy){KwRAbWXkUf = true;}
      else if(KokifloPVy == ynhasXPnFs){zuBnfiOURj = true;}
      if(VrADlQcudK == yRyANxhftA){fOcZliGLiR = true;}
      else if(yRyANxhftA == VrADlQcudK){tTUyBHbEzh = true;}
      if(KdQnsjgLfX == zlJVzXzuKD){mIRgguuyfl = true;}
      else if(zlJVzXzuKD == KdQnsjgLfX){nGGbPyBJkR = true;}
      if(zfpABeseeF == UumrVGIkuA){DRCHzZklQM = true;}
      else if(UumrVGIkuA == zfpABeseeF){jmdNVjSJUz = true;}
      if(FyILsLompE == DZsrhoBwHQ){mdBHQLQaAd = true;}
      if(jGoaKTWshI == TJeQEYfPjI){DJqwrBdkTg = true;}
      if(qDIhsoBzCG == msFScCeFdH){bZFhbOMUZL = true;}
      while(DZsrhoBwHQ == FyILsLompE){eFmeDbeThc = true;}
      while(TJeQEYfPjI == TJeQEYfPjI){kTUxOrnYYg = true;}
      while(msFScCeFdH == msFScCeFdH){gEizzGpHcR = true;}
      if(nwkswYrQmJ == true){nwkswYrQmJ = false;}
      if(VDmsiLPVnx == true){VDmsiLPVnx = false;}
      if(ZsBmNJUaOe == true){ZsBmNJUaOe = false;}
      if(KwRAbWXkUf == true){KwRAbWXkUf = false;}
      if(fOcZliGLiR == true){fOcZliGLiR = false;}
      if(mIRgguuyfl == true){mIRgguuyfl = false;}
      if(DRCHzZklQM == true){DRCHzZklQM = false;}
      if(mdBHQLQaAd == true){mdBHQLQaAd = false;}
      if(DJqwrBdkTg == true){DJqwrBdkTg = false;}
      if(bZFhbOMUZL == true){bZFhbOMUZL = false;}
      if(yTtWeIHJPU == true){yTtWeIHJPU = false;}
      if(eTyBitZFOy == true){eTyBitZFOy = false;}
      if(wzSjkMYTfC == true){wzSjkMYTfC = false;}
      if(zuBnfiOURj == true){zuBnfiOURj = false;}
      if(tTUyBHbEzh == true){tTUyBHbEzh = false;}
      if(nGGbPyBJkR == true){nGGbPyBJkR = false;}
      if(jmdNVjSJUz == true){jmdNVjSJUz = false;}
      if(eFmeDbeThc == true){eFmeDbeThc = false;}
      if(kTUxOrnYYg == true){kTUxOrnYYg = false;}
      if(gEizzGpHcR == true){gEizzGpHcR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OUXCFTPXIK
{ 
  void ImObGhUoel()
  { 
      bool BQUbwsRCVO = false;
      bool HBYMXTwYco = false;
      bool crKnZLSERC = false;
      bool HOWrJCdDgU = false;
      bool FJzYaCKkQD = false;
      bool lmTbsIGgBj = false;
      bool ZMkTHrdgDU = false;
      bool osqHiSrlNX = false;
      bool BhnNPTtuzB = false;
      bool wxBwtsXfRh = false;
      bool XdhwNsuMrZ = false;
      bool PTTdhrYWDm = false;
      bool xigBYrqtMp = false;
      bool tMUeAXAqAV = false;
      bool YhDYkcdXOC = false;
      bool TBbdknwfXU = false;
      bool BAzBfDzncJ = false;
      bool rgWhOPfIQu = false;
      bool OTfKWsjptM = false;
      bool bUTeTXhBsg = false;
      string zRNmMsEjwQ;
      string EtcJEBMKCW;
      string qdxLtrkxBP;
      string ynnnbYjGwU;
      string CVCTdYtxds;
      string PaEjQVTBrT;
      string IGifSPFnhe;
      string RFNhUUadhU;
      string ynTIAWjEXG;
      string FhObMwlWBN;
      string TFPyaJMWPu;
      string tpSWVUlaeu;
      string fAQaZipkUX;
      string iEbUBrXVgp;
      string KMncLOPqFr;
      string JLqGgSonXr;
      string TbBqMpNyVd;
      string wQtnkSLmOK;
      string TzecOWMVmh;
      string DjxoWhLxQV;
      if(zRNmMsEjwQ == TFPyaJMWPu){BQUbwsRCVO = true;}
      else if(TFPyaJMWPu == zRNmMsEjwQ){XdhwNsuMrZ = true;}
      if(EtcJEBMKCW == tpSWVUlaeu){HBYMXTwYco = true;}
      else if(tpSWVUlaeu == EtcJEBMKCW){PTTdhrYWDm = true;}
      if(qdxLtrkxBP == fAQaZipkUX){crKnZLSERC = true;}
      else if(fAQaZipkUX == qdxLtrkxBP){xigBYrqtMp = true;}
      if(ynnnbYjGwU == iEbUBrXVgp){HOWrJCdDgU = true;}
      else if(iEbUBrXVgp == ynnnbYjGwU){tMUeAXAqAV = true;}
      if(CVCTdYtxds == KMncLOPqFr){FJzYaCKkQD = true;}
      else if(KMncLOPqFr == CVCTdYtxds){YhDYkcdXOC = true;}
      if(PaEjQVTBrT == JLqGgSonXr){lmTbsIGgBj = true;}
      else if(JLqGgSonXr == PaEjQVTBrT){TBbdknwfXU = true;}
      if(IGifSPFnhe == TbBqMpNyVd){ZMkTHrdgDU = true;}
      else if(TbBqMpNyVd == IGifSPFnhe){BAzBfDzncJ = true;}
      if(RFNhUUadhU == wQtnkSLmOK){osqHiSrlNX = true;}
      if(ynTIAWjEXG == TzecOWMVmh){BhnNPTtuzB = true;}
      if(FhObMwlWBN == DjxoWhLxQV){wxBwtsXfRh = true;}
      while(wQtnkSLmOK == RFNhUUadhU){rgWhOPfIQu = true;}
      while(TzecOWMVmh == TzecOWMVmh){OTfKWsjptM = true;}
      while(DjxoWhLxQV == DjxoWhLxQV){bUTeTXhBsg = true;}
      if(BQUbwsRCVO == true){BQUbwsRCVO = false;}
      if(HBYMXTwYco == true){HBYMXTwYco = false;}
      if(crKnZLSERC == true){crKnZLSERC = false;}
      if(HOWrJCdDgU == true){HOWrJCdDgU = false;}
      if(FJzYaCKkQD == true){FJzYaCKkQD = false;}
      if(lmTbsIGgBj == true){lmTbsIGgBj = false;}
      if(ZMkTHrdgDU == true){ZMkTHrdgDU = false;}
      if(osqHiSrlNX == true){osqHiSrlNX = false;}
      if(BhnNPTtuzB == true){BhnNPTtuzB = false;}
      if(wxBwtsXfRh == true){wxBwtsXfRh = false;}
      if(XdhwNsuMrZ == true){XdhwNsuMrZ = false;}
      if(PTTdhrYWDm == true){PTTdhrYWDm = false;}
      if(xigBYrqtMp == true){xigBYrqtMp = false;}
      if(tMUeAXAqAV == true){tMUeAXAqAV = false;}
      if(YhDYkcdXOC == true){YhDYkcdXOC = false;}
      if(TBbdknwfXU == true){TBbdknwfXU = false;}
      if(BAzBfDzncJ == true){BAzBfDzncJ = false;}
      if(rgWhOPfIQu == true){rgWhOPfIQu = false;}
      if(OTfKWsjptM == true){OTfKWsjptM = false;}
      if(bUTeTXhBsg == true){bUTeTXhBsg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DRNEVMCKQR
{ 
  void uKkAHRiHYs()
  { 
      bool qMxJNrSXmz = false;
      bool LPkfVDraUe = false;
      bool QZLxWscGTu = false;
      bool mgYJlmEDTM = false;
      bool BNzfLfoCLB = false;
      bool gVYDHRBzlU = false;
      bool OLDrMdpbti = false;
      bool yoGHcCZflq = false;
      bool DauSNRIVBT = false;
      bool lFQzypKHTg = false;
      bool oNIcCrOQZE = false;
      bool qVNuQmQkdt = false;
      bool UUZZwsXHJm = false;
      bool rRLEBpSRQU = false;
      bool CruxbQrUhK = false;
      bool YZdYLUmhgI = false;
      bool UHGmMYJItZ = false;
      bool UzTIrcYbxf = false;
      bool BCYyNSnmrg = false;
      bool CjkHAtkIjD = false;
      string epklSCOuEs;
      string cuRoTcjokM;
      string DZflRxUZWf;
      string VJAQSXLRjb;
      string wZHctbPynr;
      string syfyGEKzUU;
      string hoYXWTuBWw;
      string QREIQdSCqp;
      string hVkemXcBKN;
      string MMxPsHBiGa;
      string fObraasXhb;
      string lIHemMDsky;
      string ptpIiEUoOI;
      string biuQJTsrEL;
      string dFShaEEScg;
      string DHxHjlXSJV;
      string GEIZzCMqUS;
      string SLoZUjaHhd;
      string ACMhEUlmfW;
      string wZhhFYxsiX;
      if(epklSCOuEs == fObraasXhb){qMxJNrSXmz = true;}
      else if(fObraasXhb == epklSCOuEs){oNIcCrOQZE = true;}
      if(cuRoTcjokM == lIHemMDsky){LPkfVDraUe = true;}
      else if(lIHemMDsky == cuRoTcjokM){qVNuQmQkdt = true;}
      if(DZflRxUZWf == ptpIiEUoOI){QZLxWscGTu = true;}
      else if(ptpIiEUoOI == DZflRxUZWf){UUZZwsXHJm = true;}
      if(VJAQSXLRjb == biuQJTsrEL){mgYJlmEDTM = true;}
      else if(biuQJTsrEL == VJAQSXLRjb){rRLEBpSRQU = true;}
      if(wZHctbPynr == dFShaEEScg){BNzfLfoCLB = true;}
      else if(dFShaEEScg == wZHctbPynr){CruxbQrUhK = true;}
      if(syfyGEKzUU == DHxHjlXSJV){gVYDHRBzlU = true;}
      else if(DHxHjlXSJV == syfyGEKzUU){YZdYLUmhgI = true;}
      if(hoYXWTuBWw == GEIZzCMqUS){OLDrMdpbti = true;}
      else if(GEIZzCMqUS == hoYXWTuBWw){UHGmMYJItZ = true;}
      if(QREIQdSCqp == SLoZUjaHhd){yoGHcCZflq = true;}
      if(hVkemXcBKN == ACMhEUlmfW){DauSNRIVBT = true;}
      if(MMxPsHBiGa == wZhhFYxsiX){lFQzypKHTg = true;}
      while(SLoZUjaHhd == QREIQdSCqp){UzTIrcYbxf = true;}
      while(ACMhEUlmfW == ACMhEUlmfW){BCYyNSnmrg = true;}
      while(wZhhFYxsiX == wZhhFYxsiX){CjkHAtkIjD = true;}
      if(qMxJNrSXmz == true){qMxJNrSXmz = false;}
      if(LPkfVDraUe == true){LPkfVDraUe = false;}
      if(QZLxWscGTu == true){QZLxWscGTu = false;}
      if(mgYJlmEDTM == true){mgYJlmEDTM = false;}
      if(BNzfLfoCLB == true){BNzfLfoCLB = false;}
      if(gVYDHRBzlU == true){gVYDHRBzlU = false;}
      if(OLDrMdpbti == true){OLDrMdpbti = false;}
      if(yoGHcCZflq == true){yoGHcCZflq = false;}
      if(DauSNRIVBT == true){DauSNRIVBT = false;}
      if(lFQzypKHTg == true){lFQzypKHTg = false;}
      if(oNIcCrOQZE == true){oNIcCrOQZE = false;}
      if(qVNuQmQkdt == true){qVNuQmQkdt = false;}
      if(UUZZwsXHJm == true){UUZZwsXHJm = false;}
      if(rRLEBpSRQU == true){rRLEBpSRQU = false;}
      if(CruxbQrUhK == true){CruxbQrUhK = false;}
      if(YZdYLUmhgI == true){YZdYLUmhgI = false;}
      if(UHGmMYJItZ == true){UHGmMYJItZ = false;}
      if(UzTIrcYbxf == true){UzTIrcYbxf = false;}
      if(BCYyNSnmrg == true){BCYyNSnmrg = false;}
      if(CjkHAtkIjD == true){CjkHAtkIjD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UJKSXFFKQZ
{ 
  void ITpqSlFcYA()
  { 
      bool OmPIpmOoCD = false;
      bool bfFAMytLBB = false;
      bool NANfSYDKoQ = false;
      bool grpAYpgarQ = false;
      bool qUXiXUtbEy = false;
      bool dauraNZioR = false;
      bool iEAkVjpEbV = false;
      bool QTTkKrbdIx = false;
      bool dbFpmGwxYK = false;
      bool PxkZglUmMm = false;
      bool eozigJHKhi = false;
      bool lwZrnHyJyP = false;
      bool msfRFSisDX = false;
      bool WoRUSnbWJd = false;
      bool zlPpYTWskZ = false;
      bool mLnxAlJhcN = false;
      bool aNGJLwdFYz = false;
      bool ebzUPAcork = false;
      bool uoHdjLAUUg = false;
      bool dssuCleFdc = false;
      string tUWqOVomNs;
      string VVTnuHKwZh;
      string uyWdOJKLnG;
      string JxweQhqWUs;
      string tYKTwkpTdY;
      string aQYQZuxsbF;
      string KdzHjYZoWN;
      string QmafmVmDhd;
      string SqgPerXfEU;
      string jytPhQZCjX;
      string LBwQImprcD;
      string ItKylSwicr;
      string AskCcRrLxW;
      string wjSKRRtQHq;
      string CfDAMpnucO;
      string TpZrXSPtnp;
      string udtFHXaAfU;
      string YfbkoTpjom;
      string dwihDFJamz;
      string BAcQwXlxso;
      if(tUWqOVomNs == LBwQImprcD){OmPIpmOoCD = true;}
      else if(LBwQImprcD == tUWqOVomNs){eozigJHKhi = true;}
      if(VVTnuHKwZh == ItKylSwicr){bfFAMytLBB = true;}
      else if(ItKylSwicr == VVTnuHKwZh){lwZrnHyJyP = true;}
      if(uyWdOJKLnG == AskCcRrLxW){NANfSYDKoQ = true;}
      else if(AskCcRrLxW == uyWdOJKLnG){msfRFSisDX = true;}
      if(JxweQhqWUs == wjSKRRtQHq){grpAYpgarQ = true;}
      else if(wjSKRRtQHq == JxweQhqWUs){WoRUSnbWJd = true;}
      if(tYKTwkpTdY == CfDAMpnucO){qUXiXUtbEy = true;}
      else if(CfDAMpnucO == tYKTwkpTdY){zlPpYTWskZ = true;}
      if(aQYQZuxsbF == TpZrXSPtnp){dauraNZioR = true;}
      else if(TpZrXSPtnp == aQYQZuxsbF){mLnxAlJhcN = true;}
      if(KdzHjYZoWN == udtFHXaAfU){iEAkVjpEbV = true;}
      else if(udtFHXaAfU == KdzHjYZoWN){aNGJLwdFYz = true;}
      if(QmafmVmDhd == YfbkoTpjom){QTTkKrbdIx = true;}
      if(SqgPerXfEU == dwihDFJamz){dbFpmGwxYK = true;}
      if(jytPhQZCjX == BAcQwXlxso){PxkZglUmMm = true;}
      while(YfbkoTpjom == QmafmVmDhd){ebzUPAcork = true;}
      while(dwihDFJamz == dwihDFJamz){uoHdjLAUUg = true;}
      while(BAcQwXlxso == BAcQwXlxso){dssuCleFdc = true;}
      if(OmPIpmOoCD == true){OmPIpmOoCD = false;}
      if(bfFAMytLBB == true){bfFAMytLBB = false;}
      if(NANfSYDKoQ == true){NANfSYDKoQ = false;}
      if(grpAYpgarQ == true){grpAYpgarQ = false;}
      if(qUXiXUtbEy == true){qUXiXUtbEy = false;}
      if(dauraNZioR == true){dauraNZioR = false;}
      if(iEAkVjpEbV == true){iEAkVjpEbV = false;}
      if(QTTkKrbdIx == true){QTTkKrbdIx = false;}
      if(dbFpmGwxYK == true){dbFpmGwxYK = false;}
      if(PxkZglUmMm == true){PxkZglUmMm = false;}
      if(eozigJHKhi == true){eozigJHKhi = false;}
      if(lwZrnHyJyP == true){lwZrnHyJyP = false;}
      if(msfRFSisDX == true){msfRFSisDX = false;}
      if(WoRUSnbWJd == true){WoRUSnbWJd = false;}
      if(zlPpYTWskZ == true){zlPpYTWskZ = false;}
      if(mLnxAlJhcN == true){mLnxAlJhcN = false;}
      if(aNGJLwdFYz == true){aNGJLwdFYz = false;}
      if(ebzUPAcork == true){ebzUPAcork = false;}
      if(uoHdjLAUUg == true){uoHdjLAUUg = false;}
      if(dssuCleFdc == true){dssuCleFdc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FWKULALBJT
{ 
  void kZyGSDMeyF()
  { 
      bool xanAZDgNiI = false;
      bool JiobegwwTH = false;
      bool BSDWkfEaGi = false;
      bool BYXPYjOdYY = false;
      bool RZKsegSsSF = false;
      bool fUbfkdWRPs = false;
      bool yFGAHjLYDu = false;
      bool SSXuobHKqD = false;
      bool NLIBCfxrdt = false;
      bool MxNeZLSKlu = false;
      bool VspWmNxgpJ = false;
      bool VMZMfmxFxa = false;
      bool lTtIhVFrUc = false;
      bool IxXugTVkOo = false;
      bool iQBUYzWAzm = false;
      bool NNMLICzhoR = false;
      bool HFLMBXnefL = false;
      bool QMpIrVRZih = false;
      bool yEsgOukMmd = false;
      bool UnuxgdEnTA = false;
      string GxawzzKxoz;
      string yfqFNGxqdm;
      string OFrAHXnUQU;
      string UuYgMTsRrN;
      string LwopMyKPYu;
      string PHYdcAFZna;
      string LofTdDGJrt;
      string MeyPbSQBnJ;
      string MXwVFNWtEM;
      string NTdQCVPVLJ;
      string qAXdhjIJCJ;
      string jDldNnrKOQ;
      string gMFffrBgNF;
      string DupeSMzSmU;
      string ENrtbKhzCO;
      string cEHubdurxp;
      string iauwGoNGLB;
      string nZXsLTULDV;
      string KCezbyntCo;
      string QHUxlcRumm;
      if(GxawzzKxoz == qAXdhjIJCJ){xanAZDgNiI = true;}
      else if(qAXdhjIJCJ == GxawzzKxoz){VspWmNxgpJ = true;}
      if(yfqFNGxqdm == jDldNnrKOQ){JiobegwwTH = true;}
      else if(jDldNnrKOQ == yfqFNGxqdm){VMZMfmxFxa = true;}
      if(OFrAHXnUQU == gMFffrBgNF){BSDWkfEaGi = true;}
      else if(gMFffrBgNF == OFrAHXnUQU){lTtIhVFrUc = true;}
      if(UuYgMTsRrN == DupeSMzSmU){BYXPYjOdYY = true;}
      else if(DupeSMzSmU == UuYgMTsRrN){IxXugTVkOo = true;}
      if(LwopMyKPYu == ENrtbKhzCO){RZKsegSsSF = true;}
      else if(ENrtbKhzCO == LwopMyKPYu){iQBUYzWAzm = true;}
      if(PHYdcAFZna == cEHubdurxp){fUbfkdWRPs = true;}
      else if(cEHubdurxp == PHYdcAFZna){NNMLICzhoR = true;}
      if(LofTdDGJrt == iauwGoNGLB){yFGAHjLYDu = true;}
      else if(iauwGoNGLB == LofTdDGJrt){HFLMBXnefL = true;}
      if(MeyPbSQBnJ == nZXsLTULDV){SSXuobHKqD = true;}
      if(MXwVFNWtEM == KCezbyntCo){NLIBCfxrdt = true;}
      if(NTdQCVPVLJ == QHUxlcRumm){MxNeZLSKlu = true;}
      while(nZXsLTULDV == MeyPbSQBnJ){QMpIrVRZih = true;}
      while(KCezbyntCo == KCezbyntCo){yEsgOukMmd = true;}
      while(QHUxlcRumm == QHUxlcRumm){UnuxgdEnTA = true;}
      if(xanAZDgNiI == true){xanAZDgNiI = false;}
      if(JiobegwwTH == true){JiobegwwTH = false;}
      if(BSDWkfEaGi == true){BSDWkfEaGi = false;}
      if(BYXPYjOdYY == true){BYXPYjOdYY = false;}
      if(RZKsegSsSF == true){RZKsegSsSF = false;}
      if(fUbfkdWRPs == true){fUbfkdWRPs = false;}
      if(yFGAHjLYDu == true){yFGAHjLYDu = false;}
      if(SSXuobHKqD == true){SSXuobHKqD = false;}
      if(NLIBCfxrdt == true){NLIBCfxrdt = false;}
      if(MxNeZLSKlu == true){MxNeZLSKlu = false;}
      if(VspWmNxgpJ == true){VspWmNxgpJ = false;}
      if(VMZMfmxFxa == true){VMZMfmxFxa = false;}
      if(lTtIhVFrUc == true){lTtIhVFrUc = false;}
      if(IxXugTVkOo == true){IxXugTVkOo = false;}
      if(iQBUYzWAzm == true){iQBUYzWAzm = false;}
      if(NNMLICzhoR == true){NNMLICzhoR = false;}
      if(HFLMBXnefL == true){HFLMBXnefL = false;}
      if(QMpIrVRZih == true){QMpIrVRZih = false;}
      if(yEsgOukMmd == true){yEsgOukMmd = false;}
      if(UnuxgdEnTA == true){UnuxgdEnTA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PKODSZKIVW
{ 
  void DafHJOGiNu()
  { 
      bool DQcYJlYmlP = false;
      bool KAdNYNPLJR = false;
      bool MgCoOxqiuM = false;
      bool kKNVJdJznx = false;
      bool ELTlzFznuA = false;
      bool tJALpWNmKM = false;
      bool uorZdzmIDu = false;
      bool DQXLNBMQpJ = false;
      bool yDmtRaKCem = false;
      bool PWobCOTtHz = false;
      bool SpjAxdlnxo = false;
      bool KwwBNqBxHC = false;
      bool njcQfgawIy = false;
      bool hSJqqHSmwm = false;
      bool oVFpcSZnNK = false;
      bool NVlEKhNTUQ = false;
      bool CofyHqmFKG = false;
      bool YNBTNSemnM = false;
      bool GmixkMfEfI = false;
      bool tySfkApGik = false;
      string CAYHltTkUX;
      string OfDuiYXTBJ;
      string UhELdKQkTU;
      string sztKonLtoW;
      string mpTJamCubu;
      string rmXghUwNdb;
      string chRzdPksGu;
      string MdedVeOtjp;
      string IVJXbGaNbT;
      string qyPMsEXTfL;
      string CJofiOHtKC;
      string GBcmTHXtWW;
      string nWQlDOOSjQ;
      string HuOYnyfdoN;
      string zgCYNpUbsl;
      string gdwIWerCbT;
      string zoKsuLlEzU;
      string btEJWHTqXN;
      string tlYyjcyFBJ;
      string GdCUNKVJdC;
      if(CAYHltTkUX == CJofiOHtKC){DQcYJlYmlP = true;}
      else if(CJofiOHtKC == CAYHltTkUX){SpjAxdlnxo = true;}
      if(OfDuiYXTBJ == GBcmTHXtWW){KAdNYNPLJR = true;}
      else if(GBcmTHXtWW == OfDuiYXTBJ){KwwBNqBxHC = true;}
      if(UhELdKQkTU == nWQlDOOSjQ){MgCoOxqiuM = true;}
      else if(nWQlDOOSjQ == UhELdKQkTU){njcQfgawIy = true;}
      if(sztKonLtoW == HuOYnyfdoN){kKNVJdJznx = true;}
      else if(HuOYnyfdoN == sztKonLtoW){hSJqqHSmwm = true;}
      if(mpTJamCubu == zgCYNpUbsl){ELTlzFznuA = true;}
      else if(zgCYNpUbsl == mpTJamCubu){oVFpcSZnNK = true;}
      if(rmXghUwNdb == gdwIWerCbT){tJALpWNmKM = true;}
      else if(gdwIWerCbT == rmXghUwNdb){NVlEKhNTUQ = true;}
      if(chRzdPksGu == zoKsuLlEzU){uorZdzmIDu = true;}
      else if(zoKsuLlEzU == chRzdPksGu){CofyHqmFKG = true;}
      if(MdedVeOtjp == btEJWHTqXN){DQXLNBMQpJ = true;}
      if(IVJXbGaNbT == tlYyjcyFBJ){yDmtRaKCem = true;}
      if(qyPMsEXTfL == GdCUNKVJdC){PWobCOTtHz = true;}
      while(btEJWHTqXN == MdedVeOtjp){YNBTNSemnM = true;}
      while(tlYyjcyFBJ == tlYyjcyFBJ){GmixkMfEfI = true;}
      while(GdCUNKVJdC == GdCUNKVJdC){tySfkApGik = true;}
      if(DQcYJlYmlP == true){DQcYJlYmlP = false;}
      if(KAdNYNPLJR == true){KAdNYNPLJR = false;}
      if(MgCoOxqiuM == true){MgCoOxqiuM = false;}
      if(kKNVJdJznx == true){kKNVJdJznx = false;}
      if(ELTlzFznuA == true){ELTlzFznuA = false;}
      if(tJALpWNmKM == true){tJALpWNmKM = false;}
      if(uorZdzmIDu == true){uorZdzmIDu = false;}
      if(DQXLNBMQpJ == true){DQXLNBMQpJ = false;}
      if(yDmtRaKCem == true){yDmtRaKCem = false;}
      if(PWobCOTtHz == true){PWobCOTtHz = false;}
      if(SpjAxdlnxo == true){SpjAxdlnxo = false;}
      if(KwwBNqBxHC == true){KwwBNqBxHC = false;}
      if(njcQfgawIy == true){njcQfgawIy = false;}
      if(hSJqqHSmwm == true){hSJqqHSmwm = false;}
      if(oVFpcSZnNK == true){oVFpcSZnNK = false;}
      if(NVlEKhNTUQ == true){NVlEKhNTUQ = false;}
      if(CofyHqmFKG == true){CofyHqmFKG = false;}
      if(YNBTNSemnM == true){YNBTNSemnM = false;}
      if(GmixkMfEfI == true){GmixkMfEfI = false;}
      if(tySfkApGik == true){tySfkApGik = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KAPFVGWKCR
{ 
  void PhQVzeciWk()
  { 
      bool GSdqOzmwjD = false;
      bool fejFIskryL = false;
      bool clwSehXtRM = false;
      bool CgoSTUDquk = false;
      bool yxeUSNnsgB = false;
      bool SQlbjUVLMg = false;
      bool aseWBzpRlm = false;
      bool osxMMeGbzQ = false;
      bool teMPskuMhy = false;
      bool zreOKESHST = false;
      bool XWGsMYTYOF = false;
      bool NsLwmufOcP = false;
      bool DcimnwOiCI = false;
      bool MzIesWXTDU = false;
      bool RVxcjFgiaO = false;
      bool XDdDQtmTEP = false;
      bool KkWGsOjfDP = false;
      bool WMKIxheFCi = false;
      bool PeHnjIVFOy = false;
      bool jEOnJgyqjV = false;
      string cCKHswxoli;
      string pWBPzABbdn;
      string fDecKwfHHZ;
      string AYcyltcJmg;
      string LcFYDdYJRu;
      string xIeSIZWgxx;
      string QphLhQtDcE;
      string WqnwcDyGYg;
      string WVpLbrtJpM;
      string XuMoQVtspl;
      string iVgMYFThpF;
      string bQHQZuzWio;
      string WkMQgadzfG;
      string IEPmxBncmW;
      string YLTjjHmwPV;
      string VWJAOyIQex;
      string aUCiwWAUSX;
      string GWjMQLRcfZ;
      string nhiKkktOXz;
      string sXypuEIjmM;
      if(cCKHswxoli == iVgMYFThpF){GSdqOzmwjD = true;}
      else if(iVgMYFThpF == cCKHswxoli){XWGsMYTYOF = true;}
      if(pWBPzABbdn == bQHQZuzWio){fejFIskryL = true;}
      else if(bQHQZuzWio == pWBPzABbdn){NsLwmufOcP = true;}
      if(fDecKwfHHZ == WkMQgadzfG){clwSehXtRM = true;}
      else if(WkMQgadzfG == fDecKwfHHZ){DcimnwOiCI = true;}
      if(AYcyltcJmg == IEPmxBncmW){CgoSTUDquk = true;}
      else if(IEPmxBncmW == AYcyltcJmg){MzIesWXTDU = true;}
      if(LcFYDdYJRu == YLTjjHmwPV){yxeUSNnsgB = true;}
      else if(YLTjjHmwPV == LcFYDdYJRu){RVxcjFgiaO = true;}
      if(xIeSIZWgxx == VWJAOyIQex){SQlbjUVLMg = true;}
      else if(VWJAOyIQex == xIeSIZWgxx){XDdDQtmTEP = true;}
      if(QphLhQtDcE == aUCiwWAUSX){aseWBzpRlm = true;}
      else if(aUCiwWAUSX == QphLhQtDcE){KkWGsOjfDP = true;}
      if(WqnwcDyGYg == GWjMQLRcfZ){osxMMeGbzQ = true;}
      if(WVpLbrtJpM == nhiKkktOXz){teMPskuMhy = true;}
      if(XuMoQVtspl == sXypuEIjmM){zreOKESHST = true;}
      while(GWjMQLRcfZ == WqnwcDyGYg){WMKIxheFCi = true;}
      while(nhiKkktOXz == nhiKkktOXz){PeHnjIVFOy = true;}
      while(sXypuEIjmM == sXypuEIjmM){jEOnJgyqjV = true;}
      if(GSdqOzmwjD == true){GSdqOzmwjD = false;}
      if(fejFIskryL == true){fejFIskryL = false;}
      if(clwSehXtRM == true){clwSehXtRM = false;}
      if(CgoSTUDquk == true){CgoSTUDquk = false;}
      if(yxeUSNnsgB == true){yxeUSNnsgB = false;}
      if(SQlbjUVLMg == true){SQlbjUVLMg = false;}
      if(aseWBzpRlm == true){aseWBzpRlm = false;}
      if(osxMMeGbzQ == true){osxMMeGbzQ = false;}
      if(teMPskuMhy == true){teMPskuMhy = false;}
      if(zreOKESHST == true){zreOKESHST = false;}
      if(XWGsMYTYOF == true){XWGsMYTYOF = false;}
      if(NsLwmufOcP == true){NsLwmufOcP = false;}
      if(DcimnwOiCI == true){DcimnwOiCI = false;}
      if(MzIesWXTDU == true){MzIesWXTDU = false;}
      if(RVxcjFgiaO == true){RVxcjFgiaO = false;}
      if(XDdDQtmTEP == true){XDdDQtmTEP = false;}
      if(KkWGsOjfDP == true){KkWGsOjfDP = false;}
      if(WMKIxheFCi == true){WMKIxheFCi = false;}
      if(PeHnjIVFOy == true){PeHnjIVFOy = false;}
      if(jEOnJgyqjV == true){jEOnJgyqjV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZZBNVHJJQN
{ 
  void pBACzVKlhe()
  { 
      bool qkOQjEcMfL = false;
      bool KswOGeRLbQ = false;
      bool BYLzlynqbN = false;
      bool BfrjRNwJmz = false;
      bool UUHttscreP = false;
      bool uplstSZOel = false;
      bool QkjSJeBLws = false;
      bool iIXbwgQQEr = false;
      bool VuMLRKszpz = false;
      bool mgdBiijokP = false;
      bool rQwkgmSKwM = false;
      bool BJKmPVXXAy = false;
      bool lCVwGBdWsM = false;
      bool xbenzEybee = false;
      bool rhCcxcVqkN = false;
      bool LLoldptzee = false;
      bool IwRiPZdVmL = false;
      bool WwsVGDzszc = false;
      bool emkeBkmrKJ = false;
      bool JywzVwQSMX = false;
      string fwfiQmUSGj;
      string LJGdRuPiKx;
      string XVLSPzVbzo;
      string oXqmntDCRy;
      string TtKfsLqdJz;
      string haYNwKkMTR;
      string RsTQtnRSoX;
      string rNQLddKeZD;
      string HqRzGOydqd;
      string JpiAgaZtlE;
      string sXolHUJNiR;
      string zFmPJZaUJf;
      string onbLNCdQeD;
      string DQsVKjCfql;
      string FktYeDCTpH;
      string zFjFPEwcXF;
      string prifOhMREY;
      string WucXZEtCgJ;
      string zKaWDxgmFF;
      string mYHkuMCOKw;
      if(fwfiQmUSGj == sXolHUJNiR){qkOQjEcMfL = true;}
      else if(sXolHUJNiR == fwfiQmUSGj){rQwkgmSKwM = true;}
      if(LJGdRuPiKx == zFmPJZaUJf){KswOGeRLbQ = true;}
      else if(zFmPJZaUJf == LJGdRuPiKx){BJKmPVXXAy = true;}
      if(XVLSPzVbzo == onbLNCdQeD){BYLzlynqbN = true;}
      else if(onbLNCdQeD == XVLSPzVbzo){lCVwGBdWsM = true;}
      if(oXqmntDCRy == DQsVKjCfql){BfrjRNwJmz = true;}
      else if(DQsVKjCfql == oXqmntDCRy){xbenzEybee = true;}
      if(TtKfsLqdJz == FktYeDCTpH){UUHttscreP = true;}
      else if(FktYeDCTpH == TtKfsLqdJz){rhCcxcVqkN = true;}
      if(haYNwKkMTR == zFjFPEwcXF){uplstSZOel = true;}
      else if(zFjFPEwcXF == haYNwKkMTR){LLoldptzee = true;}
      if(RsTQtnRSoX == prifOhMREY){QkjSJeBLws = true;}
      else if(prifOhMREY == RsTQtnRSoX){IwRiPZdVmL = true;}
      if(rNQLddKeZD == WucXZEtCgJ){iIXbwgQQEr = true;}
      if(HqRzGOydqd == zKaWDxgmFF){VuMLRKszpz = true;}
      if(JpiAgaZtlE == mYHkuMCOKw){mgdBiijokP = true;}
      while(WucXZEtCgJ == rNQLddKeZD){WwsVGDzszc = true;}
      while(zKaWDxgmFF == zKaWDxgmFF){emkeBkmrKJ = true;}
      while(mYHkuMCOKw == mYHkuMCOKw){JywzVwQSMX = true;}
      if(qkOQjEcMfL == true){qkOQjEcMfL = false;}
      if(KswOGeRLbQ == true){KswOGeRLbQ = false;}
      if(BYLzlynqbN == true){BYLzlynqbN = false;}
      if(BfrjRNwJmz == true){BfrjRNwJmz = false;}
      if(UUHttscreP == true){UUHttscreP = false;}
      if(uplstSZOel == true){uplstSZOel = false;}
      if(QkjSJeBLws == true){QkjSJeBLws = false;}
      if(iIXbwgQQEr == true){iIXbwgQQEr = false;}
      if(VuMLRKszpz == true){VuMLRKszpz = false;}
      if(mgdBiijokP == true){mgdBiijokP = false;}
      if(rQwkgmSKwM == true){rQwkgmSKwM = false;}
      if(BJKmPVXXAy == true){BJKmPVXXAy = false;}
      if(lCVwGBdWsM == true){lCVwGBdWsM = false;}
      if(xbenzEybee == true){xbenzEybee = false;}
      if(rhCcxcVqkN == true){rhCcxcVqkN = false;}
      if(LLoldptzee == true){LLoldptzee = false;}
      if(IwRiPZdVmL == true){IwRiPZdVmL = false;}
      if(WwsVGDzszc == true){WwsVGDzszc = false;}
      if(emkeBkmrKJ == true){emkeBkmrKJ = false;}
      if(JywzVwQSMX == true){JywzVwQSMX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HDIXWNHHAA
{ 
  void iEOjsyaEDZ()
  { 
      bool ahubyQaAst = false;
      bool ZbCzentBtX = false;
      bool mRKTdzTNKr = false;
      bool MHbkTYgIHd = false;
      bool JcLoewuhxh = false;
      bool oeRBBJWbxy = false;
      bool xNoBhRARfF = false;
      bool GltPNJFVnh = false;
      bool ElPcCgpZiJ = false;
      bool CFLIgwmKHN = false;
      bool wcCqbDkBmr = false;
      bool EBmPtLxMyA = false;
      bool aZhVDAaliR = false;
      bool VtOZkaiYBz = false;
      bool wolqEASuNV = false;
      bool zaMGlVufma = false;
      bool czRVVKlMdT = false;
      bool bYLyElmqRC = false;
      bool heXNSugHnO = false;
      bool fDkZWwWQVt = false;
      string ftKkjbplaM;
      string EuJtZuRLCE;
      string nmGuBLQusE;
      string JZUdbjMbJg;
      string rPYRAntcdG;
      string DxdPjrmPjX;
      string LurVDdZeRp;
      string ioBVLYOouM;
      string RmQmBLwFtj;
      string wxrlUxWCNW;
      string NOLnXNuHDL;
      string cyTXGYdFUr;
      string hUkgskxPBO;
      string CLaYyCbbPm;
      string PnBiGydTeu;
      string SQhVnsddtm;
      string QeGoIRWuYD;
      string xBpgbsTBau;
      string HckFukdFjF;
      string YyhcVjgLZo;
      if(ftKkjbplaM == NOLnXNuHDL){ahubyQaAst = true;}
      else if(NOLnXNuHDL == ftKkjbplaM){wcCqbDkBmr = true;}
      if(EuJtZuRLCE == cyTXGYdFUr){ZbCzentBtX = true;}
      else if(cyTXGYdFUr == EuJtZuRLCE){EBmPtLxMyA = true;}
      if(nmGuBLQusE == hUkgskxPBO){mRKTdzTNKr = true;}
      else if(hUkgskxPBO == nmGuBLQusE){aZhVDAaliR = true;}
      if(JZUdbjMbJg == CLaYyCbbPm){MHbkTYgIHd = true;}
      else if(CLaYyCbbPm == JZUdbjMbJg){VtOZkaiYBz = true;}
      if(rPYRAntcdG == PnBiGydTeu){JcLoewuhxh = true;}
      else if(PnBiGydTeu == rPYRAntcdG){wolqEASuNV = true;}
      if(DxdPjrmPjX == SQhVnsddtm){oeRBBJWbxy = true;}
      else if(SQhVnsddtm == DxdPjrmPjX){zaMGlVufma = true;}
      if(LurVDdZeRp == QeGoIRWuYD){xNoBhRARfF = true;}
      else if(QeGoIRWuYD == LurVDdZeRp){czRVVKlMdT = true;}
      if(ioBVLYOouM == xBpgbsTBau){GltPNJFVnh = true;}
      if(RmQmBLwFtj == HckFukdFjF){ElPcCgpZiJ = true;}
      if(wxrlUxWCNW == YyhcVjgLZo){CFLIgwmKHN = true;}
      while(xBpgbsTBau == ioBVLYOouM){bYLyElmqRC = true;}
      while(HckFukdFjF == HckFukdFjF){heXNSugHnO = true;}
      while(YyhcVjgLZo == YyhcVjgLZo){fDkZWwWQVt = true;}
      if(ahubyQaAst == true){ahubyQaAst = false;}
      if(ZbCzentBtX == true){ZbCzentBtX = false;}
      if(mRKTdzTNKr == true){mRKTdzTNKr = false;}
      if(MHbkTYgIHd == true){MHbkTYgIHd = false;}
      if(JcLoewuhxh == true){JcLoewuhxh = false;}
      if(oeRBBJWbxy == true){oeRBBJWbxy = false;}
      if(xNoBhRARfF == true){xNoBhRARfF = false;}
      if(GltPNJFVnh == true){GltPNJFVnh = false;}
      if(ElPcCgpZiJ == true){ElPcCgpZiJ = false;}
      if(CFLIgwmKHN == true){CFLIgwmKHN = false;}
      if(wcCqbDkBmr == true){wcCqbDkBmr = false;}
      if(EBmPtLxMyA == true){EBmPtLxMyA = false;}
      if(aZhVDAaliR == true){aZhVDAaliR = false;}
      if(VtOZkaiYBz == true){VtOZkaiYBz = false;}
      if(wolqEASuNV == true){wolqEASuNV = false;}
      if(zaMGlVufma == true){zaMGlVufma = false;}
      if(czRVVKlMdT == true){czRVVKlMdT = false;}
      if(bYLyElmqRC == true){bYLyElmqRC = false;}
      if(heXNSugHnO == true){heXNSugHnO = false;}
      if(fDkZWwWQVt == true){fDkZWwWQVt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NPTBPJSFUF
{ 
  void JJmXbNqpDm()
  { 
      bool SRFZeDUrbj = false;
      bool AMQuixQhVJ = false;
      bool fSJEnGFDcb = false;
      bool MUYSWMHSiY = false;
      bool jIxDSTTXZm = false;
      bool euRKyAHAlX = false;
      bool xQPzXfnxXW = false;
      bool oyzxZWUFlU = false;
      bool lhcoxQCOUW = false;
      bool FHgKaSsxfl = false;
      bool fWzDxfuUkb = false;
      bool eBNRlOmZCG = false;
      bool dYcBRgRnVG = false;
      bool dWZAoPiZrQ = false;
      bool UgcsqDsPYL = false;
      bool eSuZIGsylQ = false;
      bool OGzdyHbNbV = false;
      bool fNhkkwwjKN = false;
      bool nBPJaKbzqi = false;
      bool VknaBNgzti = false;
      string rgYDqGYTZU;
      string ukFNbJiRMf;
      string mkMKUPxGFV;
      string obBsGxoMcS;
      string WgRJHnucQa;
      string YlXLHHUNhb;
      string IROEfSjMHd;
      string UWosJGTCCg;
      string UTpdxCEoky;
      string caeBKESMco;
      string EhVlGCxeCB;
      string mRLBGnbjHc;
      string OtbIBsqmiE;
      string mGZNclyDWt;
      string FYliLKPdtV;
      string bhFAZJFNkN;
      string KJuyOgryXU;
      string pYNMXoIsxp;
      string dNsNbEBZnS;
      string fjSJjucnTd;
      if(rgYDqGYTZU == EhVlGCxeCB){SRFZeDUrbj = true;}
      else if(EhVlGCxeCB == rgYDqGYTZU){fWzDxfuUkb = true;}
      if(ukFNbJiRMf == mRLBGnbjHc){AMQuixQhVJ = true;}
      else if(mRLBGnbjHc == ukFNbJiRMf){eBNRlOmZCG = true;}
      if(mkMKUPxGFV == OtbIBsqmiE){fSJEnGFDcb = true;}
      else if(OtbIBsqmiE == mkMKUPxGFV){dYcBRgRnVG = true;}
      if(obBsGxoMcS == mGZNclyDWt){MUYSWMHSiY = true;}
      else if(mGZNclyDWt == obBsGxoMcS){dWZAoPiZrQ = true;}
      if(WgRJHnucQa == FYliLKPdtV){jIxDSTTXZm = true;}
      else if(FYliLKPdtV == WgRJHnucQa){UgcsqDsPYL = true;}
      if(YlXLHHUNhb == bhFAZJFNkN){euRKyAHAlX = true;}
      else if(bhFAZJFNkN == YlXLHHUNhb){eSuZIGsylQ = true;}
      if(IROEfSjMHd == KJuyOgryXU){xQPzXfnxXW = true;}
      else if(KJuyOgryXU == IROEfSjMHd){OGzdyHbNbV = true;}
      if(UWosJGTCCg == pYNMXoIsxp){oyzxZWUFlU = true;}
      if(UTpdxCEoky == dNsNbEBZnS){lhcoxQCOUW = true;}
      if(caeBKESMco == fjSJjucnTd){FHgKaSsxfl = true;}
      while(pYNMXoIsxp == UWosJGTCCg){fNhkkwwjKN = true;}
      while(dNsNbEBZnS == dNsNbEBZnS){nBPJaKbzqi = true;}
      while(fjSJjucnTd == fjSJjucnTd){VknaBNgzti = true;}
      if(SRFZeDUrbj == true){SRFZeDUrbj = false;}
      if(AMQuixQhVJ == true){AMQuixQhVJ = false;}
      if(fSJEnGFDcb == true){fSJEnGFDcb = false;}
      if(MUYSWMHSiY == true){MUYSWMHSiY = false;}
      if(jIxDSTTXZm == true){jIxDSTTXZm = false;}
      if(euRKyAHAlX == true){euRKyAHAlX = false;}
      if(xQPzXfnxXW == true){xQPzXfnxXW = false;}
      if(oyzxZWUFlU == true){oyzxZWUFlU = false;}
      if(lhcoxQCOUW == true){lhcoxQCOUW = false;}
      if(FHgKaSsxfl == true){FHgKaSsxfl = false;}
      if(fWzDxfuUkb == true){fWzDxfuUkb = false;}
      if(eBNRlOmZCG == true){eBNRlOmZCG = false;}
      if(dYcBRgRnVG == true){dYcBRgRnVG = false;}
      if(dWZAoPiZrQ == true){dWZAoPiZrQ = false;}
      if(UgcsqDsPYL == true){UgcsqDsPYL = false;}
      if(eSuZIGsylQ == true){eSuZIGsylQ = false;}
      if(OGzdyHbNbV == true){OGzdyHbNbV = false;}
      if(fNhkkwwjKN == true){fNhkkwwjKN = false;}
      if(nBPJaKbzqi == true){nBPJaKbzqi = false;}
      if(VknaBNgzti == true){VknaBNgzti = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GKCIJHONXM
{ 
  void sPVECzLCmS()
  { 
      bool yoteEpVBYz = false;
      bool JiTGiXBIjh = false;
      bool QOlcEdnzMc = false;
      bool fjoMExlgTR = false;
      bool cszOgCrpIS = false;
      bool JkNNRjCQZa = false;
      bool BWnuTZsGCk = false;
      bool kTnSEWOXwC = false;
      bool lxqtStVbuT = false;
      bool tVGsPGEDuG = false;
      bool IkmWgpxuIt = false;
      bool UeUXoDftcY = false;
      bool ERLhpPMuCy = false;
      bool SLbotAKTMc = false;
      bool xZTByOAiEL = false;
      bool aKaWCqZEfR = false;
      bool cCsKaJDedn = false;
      bool sLgzadxJib = false;
      bool OcppWIkFlC = false;
      bool aFnuzufIZo = false;
      string SNTJyaAlHG;
      string mhgLyojIrQ;
      string LEZRGLcEUL;
      string VKrtSygVGK;
      string PhAMDFVwzH;
      string OzhbWOmCDm;
      string ywRujcolrA;
      string HOCgBcENNA;
      string pfFNwWbQWE;
      string LeSSMSQEbZ;
      string QiEyzAxBat;
      string KYnDxRqEzN;
      string AYOnocuiTi;
      string MzlniGbGNu;
      string ZapcslpOVu;
      string aMFNYrUPJV;
      string ENgqhKmATp;
      string pkpDnZhkuC;
      string mgMYHztYOq;
      string kMwqpLsyuh;
      if(SNTJyaAlHG == QiEyzAxBat){yoteEpVBYz = true;}
      else if(QiEyzAxBat == SNTJyaAlHG){IkmWgpxuIt = true;}
      if(mhgLyojIrQ == KYnDxRqEzN){JiTGiXBIjh = true;}
      else if(KYnDxRqEzN == mhgLyojIrQ){UeUXoDftcY = true;}
      if(LEZRGLcEUL == AYOnocuiTi){QOlcEdnzMc = true;}
      else if(AYOnocuiTi == LEZRGLcEUL){ERLhpPMuCy = true;}
      if(VKrtSygVGK == MzlniGbGNu){fjoMExlgTR = true;}
      else if(MzlniGbGNu == VKrtSygVGK){SLbotAKTMc = true;}
      if(PhAMDFVwzH == ZapcslpOVu){cszOgCrpIS = true;}
      else if(ZapcslpOVu == PhAMDFVwzH){xZTByOAiEL = true;}
      if(OzhbWOmCDm == aMFNYrUPJV){JkNNRjCQZa = true;}
      else if(aMFNYrUPJV == OzhbWOmCDm){aKaWCqZEfR = true;}
      if(ywRujcolrA == ENgqhKmATp){BWnuTZsGCk = true;}
      else if(ENgqhKmATp == ywRujcolrA){cCsKaJDedn = true;}
      if(HOCgBcENNA == pkpDnZhkuC){kTnSEWOXwC = true;}
      if(pfFNwWbQWE == mgMYHztYOq){lxqtStVbuT = true;}
      if(LeSSMSQEbZ == kMwqpLsyuh){tVGsPGEDuG = true;}
      while(pkpDnZhkuC == HOCgBcENNA){sLgzadxJib = true;}
      while(mgMYHztYOq == mgMYHztYOq){OcppWIkFlC = true;}
      while(kMwqpLsyuh == kMwqpLsyuh){aFnuzufIZo = true;}
      if(yoteEpVBYz == true){yoteEpVBYz = false;}
      if(JiTGiXBIjh == true){JiTGiXBIjh = false;}
      if(QOlcEdnzMc == true){QOlcEdnzMc = false;}
      if(fjoMExlgTR == true){fjoMExlgTR = false;}
      if(cszOgCrpIS == true){cszOgCrpIS = false;}
      if(JkNNRjCQZa == true){JkNNRjCQZa = false;}
      if(BWnuTZsGCk == true){BWnuTZsGCk = false;}
      if(kTnSEWOXwC == true){kTnSEWOXwC = false;}
      if(lxqtStVbuT == true){lxqtStVbuT = false;}
      if(tVGsPGEDuG == true){tVGsPGEDuG = false;}
      if(IkmWgpxuIt == true){IkmWgpxuIt = false;}
      if(UeUXoDftcY == true){UeUXoDftcY = false;}
      if(ERLhpPMuCy == true){ERLhpPMuCy = false;}
      if(SLbotAKTMc == true){SLbotAKTMc = false;}
      if(xZTByOAiEL == true){xZTByOAiEL = false;}
      if(aKaWCqZEfR == true){aKaWCqZEfR = false;}
      if(cCsKaJDedn == true){cCsKaJDedn = false;}
      if(sLgzadxJib == true){sLgzadxJib = false;}
      if(OcppWIkFlC == true){OcppWIkFlC = false;}
      if(aFnuzufIZo == true){aFnuzufIZo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KKUCWZEMVN
{ 
  void AFjVIjOaFf()
  { 
      bool sEIqtGXQAl = false;
      bool loYVCxguWN = false;
      bool uCVpCRpQBI = false;
      bool lOUqIEXgXr = false;
      bool OtILyNdWXr = false;
      bool JnfpzqhSnc = false;
      bool QGPqzXThNx = false;
      bool YAXdyAtJro = false;
      bool mTsJzxhdqR = false;
      bool VFrtbIeQMa = false;
      bool swIaSIQBrz = false;
      bool wYZzpxNGqB = false;
      bool ooqwaTIcCp = false;
      bool VcxRuqKRpp = false;
      bool gflrUxerEe = false;
      bool tYZKkDFLzy = false;
      bool AnzBcTbIDz = false;
      bool luPAUJDzbd = false;
      bool oPYXwxDlfr = false;
      bool lzRqpsgkOA = false;
      string smqCPhBJCx;
      string qzgKZqVkhR;
      string pePfCjhFDc;
      string gaZyruKCyz;
      string lxrLtTaSJY;
      string OLepsOXLAf;
      string zwGYQQZhSe;
      string fTmhermDki;
      string JPwdOUuiFd;
      string XzBSzpqSud;
      string trAeruYwKA;
      string aTaQVjAbKu;
      string UpcnGgRTho;
      string BTIGoQOQkS;
      string uyYECEXkwP;
      string pOIzIDOLXL;
      string dEOVzGKTbF;
      string UiqqzWRYlB;
      string JgXSzlLIyk;
      string CDsZopjCEu;
      if(smqCPhBJCx == trAeruYwKA){sEIqtGXQAl = true;}
      else if(trAeruYwKA == smqCPhBJCx){swIaSIQBrz = true;}
      if(qzgKZqVkhR == aTaQVjAbKu){loYVCxguWN = true;}
      else if(aTaQVjAbKu == qzgKZqVkhR){wYZzpxNGqB = true;}
      if(pePfCjhFDc == UpcnGgRTho){uCVpCRpQBI = true;}
      else if(UpcnGgRTho == pePfCjhFDc){ooqwaTIcCp = true;}
      if(gaZyruKCyz == BTIGoQOQkS){lOUqIEXgXr = true;}
      else if(BTIGoQOQkS == gaZyruKCyz){VcxRuqKRpp = true;}
      if(lxrLtTaSJY == uyYECEXkwP){OtILyNdWXr = true;}
      else if(uyYECEXkwP == lxrLtTaSJY){gflrUxerEe = true;}
      if(OLepsOXLAf == pOIzIDOLXL){JnfpzqhSnc = true;}
      else if(pOIzIDOLXL == OLepsOXLAf){tYZKkDFLzy = true;}
      if(zwGYQQZhSe == dEOVzGKTbF){QGPqzXThNx = true;}
      else if(dEOVzGKTbF == zwGYQQZhSe){AnzBcTbIDz = true;}
      if(fTmhermDki == UiqqzWRYlB){YAXdyAtJro = true;}
      if(JPwdOUuiFd == JgXSzlLIyk){mTsJzxhdqR = true;}
      if(XzBSzpqSud == CDsZopjCEu){VFrtbIeQMa = true;}
      while(UiqqzWRYlB == fTmhermDki){luPAUJDzbd = true;}
      while(JgXSzlLIyk == JgXSzlLIyk){oPYXwxDlfr = true;}
      while(CDsZopjCEu == CDsZopjCEu){lzRqpsgkOA = true;}
      if(sEIqtGXQAl == true){sEIqtGXQAl = false;}
      if(loYVCxguWN == true){loYVCxguWN = false;}
      if(uCVpCRpQBI == true){uCVpCRpQBI = false;}
      if(lOUqIEXgXr == true){lOUqIEXgXr = false;}
      if(OtILyNdWXr == true){OtILyNdWXr = false;}
      if(JnfpzqhSnc == true){JnfpzqhSnc = false;}
      if(QGPqzXThNx == true){QGPqzXThNx = false;}
      if(YAXdyAtJro == true){YAXdyAtJro = false;}
      if(mTsJzxhdqR == true){mTsJzxhdqR = false;}
      if(VFrtbIeQMa == true){VFrtbIeQMa = false;}
      if(swIaSIQBrz == true){swIaSIQBrz = false;}
      if(wYZzpxNGqB == true){wYZzpxNGqB = false;}
      if(ooqwaTIcCp == true){ooqwaTIcCp = false;}
      if(VcxRuqKRpp == true){VcxRuqKRpp = false;}
      if(gflrUxerEe == true){gflrUxerEe = false;}
      if(tYZKkDFLzy == true){tYZKkDFLzy = false;}
      if(AnzBcTbIDz == true){AnzBcTbIDz = false;}
      if(luPAUJDzbd == true){luPAUJDzbd = false;}
      if(oPYXwxDlfr == true){oPYXwxDlfr = false;}
      if(lzRqpsgkOA == true){lzRqpsgkOA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NBYWLEUJGH
{ 
  void QyFVUBIXqn()
  { 
      bool PAzxXZEigM = false;
      bool KOMiyRBaBD = false;
      bool zGluTwFhFY = false;
      bool chowIxmdVj = false;
      bool ykbrwHbLsO = false;
      bool hrELuIOEca = false;
      bool UVcHicYPZA = false;
      bool eXEQFOeszM = false;
      bool UtoqpkddAz = false;
      bool ihAuPbHUJS = false;
      bool iLkrjKmmFg = false;
      bool dVFQGaglQx = false;
      bool yuPaRwWJBd = false;
      bool GKifdJIwGf = false;
      bool yqXSVMcjon = false;
      bool tVDMUmuKZn = false;
      bool nckbZSlZmw = false;
      bool RkekyGWwEE = false;
      bool SmUNjkHWKp = false;
      bool NyVSrUFwsD = false;
      string mOMRmZjCiA;
      string TxNEPziXCz;
      string RpqztTtWHb;
      string cWZbXRKhnP;
      string noDhqfhrJc;
      string uZKIQxXNWS;
      string eNtGXxXlgy;
      string nAimKcmJIO;
      string lCMdgCLQKZ;
      string txKUkZuwKt;
      string HuKLntpXxn;
      string KOFIgbAPZU;
      string kHbGEqoOCk;
      string gpyNGpqBol;
      string LnSVPfrCnI;
      string ZeWpIzTDHx;
      string FbUMGTPqCp;
      string jzZmIwnFqY;
      string ymatKCTIFG;
      string WntrgjSFPu;
      if(mOMRmZjCiA == HuKLntpXxn){PAzxXZEigM = true;}
      else if(HuKLntpXxn == mOMRmZjCiA){iLkrjKmmFg = true;}
      if(TxNEPziXCz == KOFIgbAPZU){KOMiyRBaBD = true;}
      else if(KOFIgbAPZU == TxNEPziXCz){dVFQGaglQx = true;}
      if(RpqztTtWHb == kHbGEqoOCk){zGluTwFhFY = true;}
      else if(kHbGEqoOCk == RpqztTtWHb){yuPaRwWJBd = true;}
      if(cWZbXRKhnP == gpyNGpqBol){chowIxmdVj = true;}
      else if(gpyNGpqBol == cWZbXRKhnP){GKifdJIwGf = true;}
      if(noDhqfhrJc == LnSVPfrCnI){ykbrwHbLsO = true;}
      else if(LnSVPfrCnI == noDhqfhrJc){yqXSVMcjon = true;}
      if(uZKIQxXNWS == ZeWpIzTDHx){hrELuIOEca = true;}
      else if(ZeWpIzTDHx == uZKIQxXNWS){tVDMUmuKZn = true;}
      if(eNtGXxXlgy == FbUMGTPqCp){UVcHicYPZA = true;}
      else if(FbUMGTPqCp == eNtGXxXlgy){nckbZSlZmw = true;}
      if(nAimKcmJIO == jzZmIwnFqY){eXEQFOeszM = true;}
      if(lCMdgCLQKZ == ymatKCTIFG){UtoqpkddAz = true;}
      if(txKUkZuwKt == WntrgjSFPu){ihAuPbHUJS = true;}
      while(jzZmIwnFqY == nAimKcmJIO){RkekyGWwEE = true;}
      while(ymatKCTIFG == ymatKCTIFG){SmUNjkHWKp = true;}
      while(WntrgjSFPu == WntrgjSFPu){NyVSrUFwsD = true;}
      if(PAzxXZEigM == true){PAzxXZEigM = false;}
      if(KOMiyRBaBD == true){KOMiyRBaBD = false;}
      if(zGluTwFhFY == true){zGluTwFhFY = false;}
      if(chowIxmdVj == true){chowIxmdVj = false;}
      if(ykbrwHbLsO == true){ykbrwHbLsO = false;}
      if(hrELuIOEca == true){hrELuIOEca = false;}
      if(UVcHicYPZA == true){UVcHicYPZA = false;}
      if(eXEQFOeszM == true){eXEQFOeszM = false;}
      if(UtoqpkddAz == true){UtoqpkddAz = false;}
      if(ihAuPbHUJS == true){ihAuPbHUJS = false;}
      if(iLkrjKmmFg == true){iLkrjKmmFg = false;}
      if(dVFQGaglQx == true){dVFQGaglQx = false;}
      if(yuPaRwWJBd == true){yuPaRwWJBd = false;}
      if(GKifdJIwGf == true){GKifdJIwGf = false;}
      if(yqXSVMcjon == true){yqXSVMcjon = false;}
      if(tVDMUmuKZn == true){tVDMUmuKZn = false;}
      if(nckbZSlZmw == true){nckbZSlZmw = false;}
      if(RkekyGWwEE == true){RkekyGWwEE = false;}
      if(SmUNjkHWKp == true){SmUNjkHWKp = false;}
      if(NyVSrUFwsD == true){NyVSrUFwsD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CQGMFWLPMJ
{ 
  void uaVKNOebqT()
  { 
      bool fXtaiKUAIQ = false;
      bool aCzRFDMKiP = false;
      bool SQNVLQWqcj = false;
      bool pwydANbYEi = false;
      bool zZLXebMXxK = false;
      bool azdIAOKXOR = false;
      bool mcXYadDVQq = false;
      bool amFAPsFoqj = false;
      bool EytRJpSpck = false;
      bool DEKluVBmxB = false;
      bool XpGFjmsdrH = false;
      bool JUgdNniFOj = false;
      bool KNrfnWcTEt = false;
      bool qSroLNrnhW = false;
      bool wnyVbhWfYG = false;
      bool muXMpKyZRM = false;
      bool KZZyPqcqSz = false;
      bool wtXrmWPWEG = false;
      bool zwuxGutezA = false;
      bool PRWULWOAFj = false;
      string pQuyRCbokt;
      string GzmCHOStru;
      string iqTKBPCoAC;
      string owOiVCSkPw;
      string ItELhXHmDA;
      string yJreHywjwC;
      string zlohEKkEgF;
      string ugeulnmIcd;
      string HOlzEfDiaW;
      string GhoMwWEVGW;
      string lDGxERewrS;
      string KnHSukAodY;
      string GBdJzMrRyP;
      string jRCFqEIntm;
      string AHpHMRaVRL;
      string VPqgQkYwyr;
      string YMxcislCbq;
      string cLtqXzKWxg;
      string lVAmsTZUoF;
      string eLoCNnJNXT;
      if(pQuyRCbokt == lDGxERewrS){fXtaiKUAIQ = true;}
      else if(lDGxERewrS == pQuyRCbokt){XpGFjmsdrH = true;}
      if(GzmCHOStru == KnHSukAodY){aCzRFDMKiP = true;}
      else if(KnHSukAodY == GzmCHOStru){JUgdNniFOj = true;}
      if(iqTKBPCoAC == GBdJzMrRyP){SQNVLQWqcj = true;}
      else if(GBdJzMrRyP == iqTKBPCoAC){KNrfnWcTEt = true;}
      if(owOiVCSkPw == jRCFqEIntm){pwydANbYEi = true;}
      else if(jRCFqEIntm == owOiVCSkPw){qSroLNrnhW = true;}
      if(ItELhXHmDA == AHpHMRaVRL){zZLXebMXxK = true;}
      else if(AHpHMRaVRL == ItELhXHmDA){wnyVbhWfYG = true;}
      if(yJreHywjwC == VPqgQkYwyr){azdIAOKXOR = true;}
      else if(VPqgQkYwyr == yJreHywjwC){muXMpKyZRM = true;}
      if(zlohEKkEgF == YMxcislCbq){mcXYadDVQq = true;}
      else if(YMxcislCbq == zlohEKkEgF){KZZyPqcqSz = true;}
      if(ugeulnmIcd == cLtqXzKWxg){amFAPsFoqj = true;}
      if(HOlzEfDiaW == lVAmsTZUoF){EytRJpSpck = true;}
      if(GhoMwWEVGW == eLoCNnJNXT){DEKluVBmxB = true;}
      while(cLtqXzKWxg == ugeulnmIcd){wtXrmWPWEG = true;}
      while(lVAmsTZUoF == lVAmsTZUoF){zwuxGutezA = true;}
      while(eLoCNnJNXT == eLoCNnJNXT){PRWULWOAFj = true;}
      if(fXtaiKUAIQ == true){fXtaiKUAIQ = false;}
      if(aCzRFDMKiP == true){aCzRFDMKiP = false;}
      if(SQNVLQWqcj == true){SQNVLQWqcj = false;}
      if(pwydANbYEi == true){pwydANbYEi = false;}
      if(zZLXebMXxK == true){zZLXebMXxK = false;}
      if(azdIAOKXOR == true){azdIAOKXOR = false;}
      if(mcXYadDVQq == true){mcXYadDVQq = false;}
      if(amFAPsFoqj == true){amFAPsFoqj = false;}
      if(EytRJpSpck == true){EytRJpSpck = false;}
      if(DEKluVBmxB == true){DEKluVBmxB = false;}
      if(XpGFjmsdrH == true){XpGFjmsdrH = false;}
      if(JUgdNniFOj == true){JUgdNniFOj = false;}
      if(KNrfnWcTEt == true){KNrfnWcTEt = false;}
      if(qSroLNrnhW == true){qSroLNrnhW = false;}
      if(wnyVbhWfYG == true){wnyVbhWfYG = false;}
      if(muXMpKyZRM == true){muXMpKyZRM = false;}
      if(KZZyPqcqSz == true){KZZyPqcqSz = false;}
      if(wtXrmWPWEG == true){wtXrmWPWEG = false;}
      if(zwuxGutezA == true){zwuxGutezA = false;}
      if(PRWULWOAFj == true){PRWULWOAFj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KEKCIOFSIG
{ 
  void ZFwSxthTnj()
  { 
      bool lKcFGdkmmJ = false;
      bool jKEXUbcAln = false;
      bool RnnrdckdEi = false;
      bool AukyggmXWy = false;
      bool kyxrxxradx = false;
      bool OgyOVxWjac = false;
      bool rGhEJnZFqm = false;
      bool oFdmCTqwtg = false;
      bool jKAHUSxVbi = false;
      bool JCwsGePrhI = false;
      bool WljpIIDKLC = false;
      bool GaosshGajq = false;
      bool qDdHclIjgX = false;
      bool DyNlKxZKyL = false;
      bool PlKZbiMDAX = false;
      bool XnIqRTIbMW = false;
      bool AScnyINDiu = false;
      bool HucYaEsDft = false;
      bool YFjJzOoVTq = false;
      bool nyxbKwJVaT = false;
      string xcblYadEIB;
      string ghIMDhcrQK;
      string qQTLYXGrBf;
      string EnuugqCllN;
      string bEtiegPzgk;
      string BfooifIQNB;
      string UlDbwrlNeM;
      string epFChlWkfq;
      string IHKQdXyGLB;
      string hlXkspBRll;
      string uBTUFKamGw;
      string JXjVsMamyX;
      string teCddsRUJr;
      string kFytwGmpKS;
      string xLzOrKBCqf;
      string ONSNrPypqM;
      string rFdOLEYpYl;
      string ZkceahfnlS;
      string rPcccWljCg;
      string HxzyZqhjCn;
      if(xcblYadEIB == uBTUFKamGw){lKcFGdkmmJ = true;}
      else if(uBTUFKamGw == xcblYadEIB){WljpIIDKLC = true;}
      if(ghIMDhcrQK == JXjVsMamyX){jKEXUbcAln = true;}
      else if(JXjVsMamyX == ghIMDhcrQK){GaosshGajq = true;}
      if(qQTLYXGrBf == teCddsRUJr){RnnrdckdEi = true;}
      else if(teCddsRUJr == qQTLYXGrBf){qDdHclIjgX = true;}
      if(EnuugqCllN == kFytwGmpKS){AukyggmXWy = true;}
      else if(kFytwGmpKS == EnuugqCllN){DyNlKxZKyL = true;}
      if(bEtiegPzgk == xLzOrKBCqf){kyxrxxradx = true;}
      else if(xLzOrKBCqf == bEtiegPzgk){PlKZbiMDAX = true;}
      if(BfooifIQNB == ONSNrPypqM){OgyOVxWjac = true;}
      else if(ONSNrPypqM == BfooifIQNB){XnIqRTIbMW = true;}
      if(UlDbwrlNeM == rFdOLEYpYl){rGhEJnZFqm = true;}
      else if(rFdOLEYpYl == UlDbwrlNeM){AScnyINDiu = true;}
      if(epFChlWkfq == ZkceahfnlS){oFdmCTqwtg = true;}
      if(IHKQdXyGLB == rPcccWljCg){jKAHUSxVbi = true;}
      if(hlXkspBRll == HxzyZqhjCn){JCwsGePrhI = true;}
      while(ZkceahfnlS == epFChlWkfq){HucYaEsDft = true;}
      while(rPcccWljCg == rPcccWljCg){YFjJzOoVTq = true;}
      while(HxzyZqhjCn == HxzyZqhjCn){nyxbKwJVaT = true;}
      if(lKcFGdkmmJ == true){lKcFGdkmmJ = false;}
      if(jKEXUbcAln == true){jKEXUbcAln = false;}
      if(RnnrdckdEi == true){RnnrdckdEi = false;}
      if(AukyggmXWy == true){AukyggmXWy = false;}
      if(kyxrxxradx == true){kyxrxxradx = false;}
      if(OgyOVxWjac == true){OgyOVxWjac = false;}
      if(rGhEJnZFqm == true){rGhEJnZFqm = false;}
      if(oFdmCTqwtg == true){oFdmCTqwtg = false;}
      if(jKAHUSxVbi == true){jKAHUSxVbi = false;}
      if(JCwsGePrhI == true){JCwsGePrhI = false;}
      if(WljpIIDKLC == true){WljpIIDKLC = false;}
      if(GaosshGajq == true){GaosshGajq = false;}
      if(qDdHclIjgX == true){qDdHclIjgX = false;}
      if(DyNlKxZKyL == true){DyNlKxZKyL = false;}
      if(PlKZbiMDAX == true){PlKZbiMDAX = false;}
      if(XnIqRTIbMW == true){XnIqRTIbMW = false;}
      if(AScnyINDiu == true){AScnyINDiu = false;}
      if(HucYaEsDft == true){HucYaEsDft = false;}
      if(YFjJzOoVTq == true){YFjJzOoVTq = false;}
      if(nyxbKwJVaT == true){nyxbKwJVaT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PYMOKNZGOU
{ 
  void bJZVXyHuLE()
  { 
      bool MdQgIHyfjY = false;
      bool eZNORVoAKO = false;
      bool IODmPBRapO = false;
      bool YosNnydFDe = false;
      bool ewHZzCbQIk = false;
      bool oqKyExacQH = false;
      bool pWoVAogzZT = false;
      bool qjwfjLHcmN = false;
      bool YASFYhetIq = false;
      bool WAnwnHGkZK = false;
      bool UbpotEteOr = false;
      bool oxpDhoEjwR = false;
      bool KlqiwpuAqc = false;
      bool FVDbrwKdLT = false;
      bool nzfPBZKkNz = false;
      bool CWoHAikHrD = false;
      bool JsnlmTtNKl = false;
      bool eaXbdKGahW = false;
      bool eKlrZhgubJ = false;
      bool LDkHKtLtcg = false;
      string mLtckoFCsa;
      string ZciJuxwVNK;
      string NofEzgahJI;
      string bdnwpcOyfh;
      string UOjdFJehCl;
      string qeCeUyfpcD;
      string OXskyunmSR;
      string hyoeozFByp;
      string BseXQxaJar;
      string xYUbTxVyeJ;
      string UrOjDsoXpV;
      string rdqmCUrVUB;
      string TeLaUJcMKr;
      string dGWoUJduTW;
      string HDTFzTghZz;
      string FAddopfnPt;
      string QcMxrlHCRs;
      string pxBxsQLGaA;
      string btmLmccrze;
      string coeZGeqVMN;
      if(mLtckoFCsa == UrOjDsoXpV){MdQgIHyfjY = true;}
      else if(UrOjDsoXpV == mLtckoFCsa){UbpotEteOr = true;}
      if(ZciJuxwVNK == rdqmCUrVUB){eZNORVoAKO = true;}
      else if(rdqmCUrVUB == ZciJuxwVNK){oxpDhoEjwR = true;}
      if(NofEzgahJI == TeLaUJcMKr){IODmPBRapO = true;}
      else if(TeLaUJcMKr == NofEzgahJI){KlqiwpuAqc = true;}
      if(bdnwpcOyfh == dGWoUJduTW){YosNnydFDe = true;}
      else if(dGWoUJduTW == bdnwpcOyfh){FVDbrwKdLT = true;}
      if(UOjdFJehCl == HDTFzTghZz){ewHZzCbQIk = true;}
      else if(HDTFzTghZz == UOjdFJehCl){nzfPBZKkNz = true;}
      if(qeCeUyfpcD == FAddopfnPt){oqKyExacQH = true;}
      else if(FAddopfnPt == qeCeUyfpcD){CWoHAikHrD = true;}
      if(OXskyunmSR == QcMxrlHCRs){pWoVAogzZT = true;}
      else if(QcMxrlHCRs == OXskyunmSR){JsnlmTtNKl = true;}
      if(hyoeozFByp == pxBxsQLGaA){qjwfjLHcmN = true;}
      if(BseXQxaJar == btmLmccrze){YASFYhetIq = true;}
      if(xYUbTxVyeJ == coeZGeqVMN){WAnwnHGkZK = true;}
      while(pxBxsQLGaA == hyoeozFByp){eaXbdKGahW = true;}
      while(btmLmccrze == btmLmccrze){eKlrZhgubJ = true;}
      while(coeZGeqVMN == coeZGeqVMN){LDkHKtLtcg = true;}
      if(MdQgIHyfjY == true){MdQgIHyfjY = false;}
      if(eZNORVoAKO == true){eZNORVoAKO = false;}
      if(IODmPBRapO == true){IODmPBRapO = false;}
      if(YosNnydFDe == true){YosNnydFDe = false;}
      if(ewHZzCbQIk == true){ewHZzCbQIk = false;}
      if(oqKyExacQH == true){oqKyExacQH = false;}
      if(pWoVAogzZT == true){pWoVAogzZT = false;}
      if(qjwfjLHcmN == true){qjwfjLHcmN = false;}
      if(YASFYhetIq == true){YASFYhetIq = false;}
      if(WAnwnHGkZK == true){WAnwnHGkZK = false;}
      if(UbpotEteOr == true){UbpotEteOr = false;}
      if(oxpDhoEjwR == true){oxpDhoEjwR = false;}
      if(KlqiwpuAqc == true){KlqiwpuAqc = false;}
      if(FVDbrwKdLT == true){FVDbrwKdLT = false;}
      if(nzfPBZKkNz == true){nzfPBZKkNz = false;}
      if(CWoHAikHrD == true){CWoHAikHrD = false;}
      if(JsnlmTtNKl == true){JsnlmTtNKl = false;}
      if(eaXbdKGahW == true){eaXbdKGahW = false;}
      if(eKlrZhgubJ == true){eKlrZhgubJ = false;}
      if(LDkHKtLtcg == true){LDkHKtLtcg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GPXFJJZPXM
{ 
  void QuelnjXhNS()
  { 
      bool MLLRLbLEQT = false;
      bool iWaHeyNHQR = false;
      bool AzjYcGaqfc = false;
      bool mGlUoTOFnJ = false;
      bool oErpSdxIZp = false;
      bool xVKkxNblnE = false;
      bool BTXnfbkFRL = false;
      bool iITGbwHtGz = false;
      bool JRQpfQwAWb = false;
      bool rbQjIVfDJq = false;
      bool sqpOGoCEIB = false;
      bool FgfnuiChHO = false;
      bool ejipTHqjxG = false;
      bool QDjOGRbCip = false;
      bool OrrVVKwcnZ = false;
      bool SxuuLIIzuz = false;
      bool ySGBkBwQgc = false;
      bool GAyRAlqNTI = false;
      bool LNuXnSHoDy = false;
      bool IcGjrulpjT = false;
      string NEcGhVhNIq;
      string sZHLksKOAu;
      string bedHSJkImb;
      string HIdCjTOSJW;
      string IwnZYXbxzZ;
      string cHZtFiaVmX;
      string jYafjkwFbQ;
      string drEcmepEht;
      string hmIMyzhjwA;
      string rselmiVHon;
      string bVViwkDxGa;
      string rWnspwQNhj;
      string CLJbXkMSoE;
      string IiOtSMRZQM;
      string wkcUIVFlup;
      string RIZFkQLtKK;
      string YkHCRJIsad;
      string epxUnRhoSC;
      string fZWzlAIIJB;
      string AXPFnKdaCy;
      if(NEcGhVhNIq == bVViwkDxGa){MLLRLbLEQT = true;}
      else if(bVViwkDxGa == NEcGhVhNIq){sqpOGoCEIB = true;}
      if(sZHLksKOAu == rWnspwQNhj){iWaHeyNHQR = true;}
      else if(rWnspwQNhj == sZHLksKOAu){FgfnuiChHO = true;}
      if(bedHSJkImb == CLJbXkMSoE){AzjYcGaqfc = true;}
      else if(CLJbXkMSoE == bedHSJkImb){ejipTHqjxG = true;}
      if(HIdCjTOSJW == IiOtSMRZQM){mGlUoTOFnJ = true;}
      else if(IiOtSMRZQM == HIdCjTOSJW){QDjOGRbCip = true;}
      if(IwnZYXbxzZ == wkcUIVFlup){oErpSdxIZp = true;}
      else if(wkcUIVFlup == IwnZYXbxzZ){OrrVVKwcnZ = true;}
      if(cHZtFiaVmX == RIZFkQLtKK){xVKkxNblnE = true;}
      else if(RIZFkQLtKK == cHZtFiaVmX){SxuuLIIzuz = true;}
      if(jYafjkwFbQ == YkHCRJIsad){BTXnfbkFRL = true;}
      else if(YkHCRJIsad == jYafjkwFbQ){ySGBkBwQgc = true;}
      if(drEcmepEht == epxUnRhoSC){iITGbwHtGz = true;}
      if(hmIMyzhjwA == fZWzlAIIJB){JRQpfQwAWb = true;}
      if(rselmiVHon == AXPFnKdaCy){rbQjIVfDJq = true;}
      while(epxUnRhoSC == drEcmepEht){GAyRAlqNTI = true;}
      while(fZWzlAIIJB == fZWzlAIIJB){LNuXnSHoDy = true;}
      while(AXPFnKdaCy == AXPFnKdaCy){IcGjrulpjT = true;}
      if(MLLRLbLEQT == true){MLLRLbLEQT = false;}
      if(iWaHeyNHQR == true){iWaHeyNHQR = false;}
      if(AzjYcGaqfc == true){AzjYcGaqfc = false;}
      if(mGlUoTOFnJ == true){mGlUoTOFnJ = false;}
      if(oErpSdxIZp == true){oErpSdxIZp = false;}
      if(xVKkxNblnE == true){xVKkxNblnE = false;}
      if(BTXnfbkFRL == true){BTXnfbkFRL = false;}
      if(iITGbwHtGz == true){iITGbwHtGz = false;}
      if(JRQpfQwAWb == true){JRQpfQwAWb = false;}
      if(rbQjIVfDJq == true){rbQjIVfDJq = false;}
      if(sqpOGoCEIB == true){sqpOGoCEIB = false;}
      if(FgfnuiChHO == true){FgfnuiChHO = false;}
      if(ejipTHqjxG == true){ejipTHqjxG = false;}
      if(QDjOGRbCip == true){QDjOGRbCip = false;}
      if(OrrVVKwcnZ == true){OrrVVKwcnZ = false;}
      if(SxuuLIIzuz == true){SxuuLIIzuz = false;}
      if(ySGBkBwQgc == true){ySGBkBwQgc = false;}
      if(GAyRAlqNTI == true){GAyRAlqNTI = false;}
      if(LNuXnSHoDy == true){LNuXnSHoDy = false;}
      if(IcGjrulpjT == true){IcGjrulpjT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BMCLCLFRFC
{ 
  void USaXnSLCtt()
  { 
      bool XbXWalBAid = false;
      bool HHKJDybSma = false;
      bool MGOMsMeaZJ = false;
      bool IGfzPGXrht = false;
      bool jJaUnoRACT = false;
      bool HaysRRMLdN = false;
      bool GaZZVBbKtx = false;
      bool ajjspCetYD = false;
      bool ueXGBgImhy = false;
      bool sLNUmJjBym = false;
      bool NGGFrWpFCP = false;
      bool lSlZSbCSYn = false;
      bool rncuEOWPGg = false;
      bool SdukonXSNd = false;
      bool qDjSLZZnBK = false;
      bool GQbJtYcKBd = false;
      bool AZyUwHWBjd = false;
      bool EjEtxoEKjd = false;
      bool ohOwaBBlqQ = false;
      bool LMQjdQEOVD = false;
      string QsQfcERoQe;
      string NZVFFSJxJs;
      string KpDlchLhPa;
      string LRsYAiMrGO;
      string JhnRBflZyP;
      string pMuLKaodDt;
      string siZpTufwEW;
      string GRqticBkkw;
      string wljAjyWhOZ;
      string shnMVaHyyF;
      string zpUbIXVAbh;
      string YEsGxGyYFV;
      string YygecXcdXI;
      string UCmexGRIqM;
      string bVFgAoohOP;
      string biscgAIoyk;
      string trbTMVQNJq;
      string opgrsCrAdn;
      string huPIflJKyw;
      string xbKGRjtlTd;
      if(QsQfcERoQe == zpUbIXVAbh){XbXWalBAid = true;}
      else if(zpUbIXVAbh == QsQfcERoQe){NGGFrWpFCP = true;}
      if(NZVFFSJxJs == YEsGxGyYFV){HHKJDybSma = true;}
      else if(YEsGxGyYFV == NZVFFSJxJs){lSlZSbCSYn = true;}
      if(KpDlchLhPa == YygecXcdXI){MGOMsMeaZJ = true;}
      else if(YygecXcdXI == KpDlchLhPa){rncuEOWPGg = true;}
      if(LRsYAiMrGO == UCmexGRIqM){IGfzPGXrht = true;}
      else if(UCmexGRIqM == LRsYAiMrGO){SdukonXSNd = true;}
      if(JhnRBflZyP == bVFgAoohOP){jJaUnoRACT = true;}
      else if(bVFgAoohOP == JhnRBflZyP){qDjSLZZnBK = true;}
      if(pMuLKaodDt == biscgAIoyk){HaysRRMLdN = true;}
      else if(biscgAIoyk == pMuLKaodDt){GQbJtYcKBd = true;}
      if(siZpTufwEW == trbTMVQNJq){GaZZVBbKtx = true;}
      else if(trbTMVQNJq == siZpTufwEW){AZyUwHWBjd = true;}
      if(GRqticBkkw == opgrsCrAdn){ajjspCetYD = true;}
      if(wljAjyWhOZ == huPIflJKyw){ueXGBgImhy = true;}
      if(shnMVaHyyF == xbKGRjtlTd){sLNUmJjBym = true;}
      while(opgrsCrAdn == GRqticBkkw){EjEtxoEKjd = true;}
      while(huPIflJKyw == huPIflJKyw){ohOwaBBlqQ = true;}
      while(xbKGRjtlTd == xbKGRjtlTd){LMQjdQEOVD = true;}
      if(XbXWalBAid == true){XbXWalBAid = false;}
      if(HHKJDybSma == true){HHKJDybSma = false;}
      if(MGOMsMeaZJ == true){MGOMsMeaZJ = false;}
      if(IGfzPGXrht == true){IGfzPGXrht = false;}
      if(jJaUnoRACT == true){jJaUnoRACT = false;}
      if(HaysRRMLdN == true){HaysRRMLdN = false;}
      if(GaZZVBbKtx == true){GaZZVBbKtx = false;}
      if(ajjspCetYD == true){ajjspCetYD = false;}
      if(ueXGBgImhy == true){ueXGBgImhy = false;}
      if(sLNUmJjBym == true){sLNUmJjBym = false;}
      if(NGGFrWpFCP == true){NGGFrWpFCP = false;}
      if(lSlZSbCSYn == true){lSlZSbCSYn = false;}
      if(rncuEOWPGg == true){rncuEOWPGg = false;}
      if(SdukonXSNd == true){SdukonXSNd = false;}
      if(qDjSLZZnBK == true){qDjSLZZnBK = false;}
      if(GQbJtYcKBd == true){GQbJtYcKBd = false;}
      if(AZyUwHWBjd == true){AZyUwHWBjd = false;}
      if(EjEtxoEKjd == true){EjEtxoEKjd = false;}
      if(ohOwaBBlqQ == true){ohOwaBBlqQ = false;}
      if(LMQjdQEOVD == true){LMQjdQEOVD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NUESIDJXRW
{ 
  void eXSDQJemiC()
  { 
      bool FgztPSEtSs = false;
      bool zYUiICJxYc = false;
      bool kFbGziywnf = false;
      bool QsYkqbWsEd = false;
      bool BrOlhMpXwm = false;
      bool QcludzErtf = false;
      bool TIGmbGAjrg = false;
      bool ePstbsqpYl = false;
      bool sazAPmGdHr = false;
      bool WezXJrkaJb = false;
      bool MGfPHAjqSk = false;
      bool HOTImsJFXo = false;
      bool zVczKAQUji = false;
      bool HPgwZltisO = false;
      bool DPKVkHLqkQ = false;
      bool hfDTbpdgFG = false;
      bool jOHidqhWiA = false;
      bool yaMIljLGOC = false;
      bool oZiTAbMMTi = false;
      bool INclenIars = false;
      string ztgbzfSPxW;
      string WNwwbZqBYO;
      string bllaZTLMHG;
      string CzEnkxRRGH;
      string YlIYqyiUBW;
      string IMMgkNIGCf;
      string TFIpUWIHLe;
      string IZuQopcMja;
      string jqKkyomXDW;
      string oKOamTdRET;
      string oaJWOiRuqu;
      string juWauctXre;
      string ikEnpxKTdV;
      string LLHPlJgnVO;
      string XrfHmsnnfK;
      string YFYZjEWVfQ;
      string YxQViXnHol;
      string uGBdGqExAx;
      string IVnTwGmheh;
      string lLHFpZaKXO;
      if(ztgbzfSPxW == oaJWOiRuqu){FgztPSEtSs = true;}
      else if(oaJWOiRuqu == ztgbzfSPxW){MGfPHAjqSk = true;}
      if(WNwwbZqBYO == juWauctXre){zYUiICJxYc = true;}
      else if(juWauctXre == WNwwbZqBYO){HOTImsJFXo = true;}
      if(bllaZTLMHG == ikEnpxKTdV){kFbGziywnf = true;}
      else if(ikEnpxKTdV == bllaZTLMHG){zVczKAQUji = true;}
      if(CzEnkxRRGH == LLHPlJgnVO){QsYkqbWsEd = true;}
      else if(LLHPlJgnVO == CzEnkxRRGH){HPgwZltisO = true;}
      if(YlIYqyiUBW == XrfHmsnnfK){BrOlhMpXwm = true;}
      else if(XrfHmsnnfK == YlIYqyiUBW){DPKVkHLqkQ = true;}
      if(IMMgkNIGCf == YFYZjEWVfQ){QcludzErtf = true;}
      else if(YFYZjEWVfQ == IMMgkNIGCf){hfDTbpdgFG = true;}
      if(TFIpUWIHLe == YxQViXnHol){TIGmbGAjrg = true;}
      else if(YxQViXnHol == TFIpUWIHLe){jOHidqhWiA = true;}
      if(IZuQopcMja == uGBdGqExAx){ePstbsqpYl = true;}
      if(jqKkyomXDW == IVnTwGmheh){sazAPmGdHr = true;}
      if(oKOamTdRET == lLHFpZaKXO){WezXJrkaJb = true;}
      while(uGBdGqExAx == IZuQopcMja){yaMIljLGOC = true;}
      while(IVnTwGmheh == IVnTwGmheh){oZiTAbMMTi = true;}
      while(lLHFpZaKXO == lLHFpZaKXO){INclenIars = true;}
      if(FgztPSEtSs == true){FgztPSEtSs = false;}
      if(zYUiICJxYc == true){zYUiICJxYc = false;}
      if(kFbGziywnf == true){kFbGziywnf = false;}
      if(QsYkqbWsEd == true){QsYkqbWsEd = false;}
      if(BrOlhMpXwm == true){BrOlhMpXwm = false;}
      if(QcludzErtf == true){QcludzErtf = false;}
      if(TIGmbGAjrg == true){TIGmbGAjrg = false;}
      if(ePstbsqpYl == true){ePstbsqpYl = false;}
      if(sazAPmGdHr == true){sazAPmGdHr = false;}
      if(WezXJrkaJb == true){WezXJrkaJb = false;}
      if(MGfPHAjqSk == true){MGfPHAjqSk = false;}
      if(HOTImsJFXo == true){HOTImsJFXo = false;}
      if(zVczKAQUji == true){zVczKAQUji = false;}
      if(HPgwZltisO == true){HPgwZltisO = false;}
      if(DPKVkHLqkQ == true){DPKVkHLqkQ = false;}
      if(hfDTbpdgFG == true){hfDTbpdgFG = false;}
      if(jOHidqhWiA == true){jOHidqhWiA = false;}
      if(yaMIljLGOC == true){yaMIljLGOC = false;}
      if(oZiTAbMMTi == true){oZiTAbMMTi = false;}
      if(INclenIars == true){INclenIars = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WVXXOFUKZS
{ 
  void paWOnFYayQ()
  { 
      bool MoGnMbbUeV = false;
      bool iLhhbDfUBe = false;
      bool fHoNTihfYD = false;
      bool IqyfqXVEZc = false;
      bool ragQusZOia = false;
      bool RlVYkFzrTc = false;
      bool twuaNqNBpE = false;
      bool hatYmEaYRa = false;
      bool JTwxlWUYul = false;
      bool XdkwiufFCE = false;
      bool fXXesqqxlf = false;
      bool eaZrSaAxoq = false;
      bool VnGEfEoxoq = false;
      bool YUWNukuREt = false;
      bool eXlOHxDscH = false;
      bool thQKiqRTyo = false;
      bool CsHuHJDMxg = false;
      bool eistLyBqwi = false;
      bool AwUgwqELeD = false;
      bool TbSOrlPqHy = false;
      string opSBsypsES;
      string SwjanuIzzh;
      string YhdhILJQgV;
      string rgDiwGAMnY;
      string xXXeylWzGN;
      string CqWEoGMjrh;
      string oZLiZksAeg;
      string tuLZjAKyjV;
      string oJJTSBJyso;
      string tQUFjXLoFM;
      string sVUZSHewTo;
      string wNzVrfPrPX;
      string btHoldaGpM;
      string oUsXcTnjAL;
      string WMeErgQyME;
      string HTYgkyOfmo;
      string fYGGAbTbrY;
      string qeqEBOPCxE;
      string MbslFUwMle;
      string EIxLexGXEQ;
      if(opSBsypsES == sVUZSHewTo){MoGnMbbUeV = true;}
      else if(sVUZSHewTo == opSBsypsES){fXXesqqxlf = true;}
      if(SwjanuIzzh == wNzVrfPrPX){iLhhbDfUBe = true;}
      else if(wNzVrfPrPX == SwjanuIzzh){eaZrSaAxoq = true;}
      if(YhdhILJQgV == btHoldaGpM){fHoNTihfYD = true;}
      else if(btHoldaGpM == YhdhILJQgV){VnGEfEoxoq = true;}
      if(rgDiwGAMnY == oUsXcTnjAL){IqyfqXVEZc = true;}
      else if(oUsXcTnjAL == rgDiwGAMnY){YUWNukuREt = true;}
      if(xXXeylWzGN == WMeErgQyME){ragQusZOia = true;}
      else if(WMeErgQyME == xXXeylWzGN){eXlOHxDscH = true;}
      if(CqWEoGMjrh == HTYgkyOfmo){RlVYkFzrTc = true;}
      else if(HTYgkyOfmo == CqWEoGMjrh){thQKiqRTyo = true;}
      if(oZLiZksAeg == fYGGAbTbrY){twuaNqNBpE = true;}
      else if(fYGGAbTbrY == oZLiZksAeg){CsHuHJDMxg = true;}
      if(tuLZjAKyjV == qeqEBOPCxE){hatYmEaYRa = true;}
      if(oJJTSBJyso == MbslFUwMle){JTwxlWUYul = true;}
      if(tQUFjXLoFM == EIxLexGXEQ){XdkwiufFCE = true;}
      while(qeqEBOPCxE == tuLZjAKyjV){eistLyBqwi = true;}
      while(MbslFUwMle == MbslFUwMle){AwUgwqELeD = true;}
      while(EIxLexGXEQ == EIxLexGXEQ){TbSOrlPqHy = true;}
      if(MoGnMbbUeV == true){MoGnMbbUeV = false;}
      if(iLhhbDfUBe == true){iLhhbDfUBe = false;}
      if(fHoNTihfYD == true){fHoNTihfYD = false;}
      if(IqyfqXVEZc == true){IqyfqXVEZc = false;}
      if(ragQusZOia == true){ragQusZOia = false;}
      if(RlVYkFzrTc == true){RlVYkFzrTc = false;}
      if(twuaNqNBpE == true){twuaNqNBpE = false;}
      if(hatYmEaYRa == true){hatYmEaYRa = false;}
      if(JTwxlWUYul == true){JTwxlWUYul = false;}
      if(XdkwiufFCE == true){XdkwiufFCE = false;}
      if(fXXesqqxlf == true){fXXesqqxlf = false;}
      if(eaZrSaAxoq == true){eaZrSaAxoq = false;}
      if(VnGEfEoxoq == true){VnGEfEoxoq = false;}
      if(YUWNukuREt == true){YUWNukuREt = false;}
      if(eXlOHxDscH == true){eXlOHxDscH = false;}
      if(thQKiqRTyo == true){thQKiqRTyo = false;}
      if(CsHuHJDMxg == true){CsHuHJDMxg = false;}
      if(eistLyBqwi == true){eistLyBqwi = false;}
      if(AwUgwqELeD == true){AwUgwqELeD = false;}
      if(TbSOrlPqHy == true){TbSOrlPqHy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QYJKTSOMUP
{ 
  void aXxpwwlOXc()
  { 
      bool JVBMhAtIet = false;
      bool NtwBLQsJbz = false;
      bool TFKbrzgrgn = false;
      bool FyeCdWRzZA = false;
      bool FSNtXdzGVn = false;
      bool sxsYmEKZUh = false;
      bool SBaqnOOsXo = false;
      bool zsjbsAqQEO = false;
      bool zaWrtIFGOY = false;
      bool LreqgDqWGJ = false;
      bool OFifnzNQel = false;
      bool NtUFhreiwf = false;
      bool JHeydHNruo = false;
      bool JTJuztrpDu = false;
      bool tnbbLRWYIn = false;
      bool YIZazGajCg = false;
      bool kUVocsjZGn = false;
      bool AneBkUfDmL = false;
      bool joiGQAsius = false;
      bool SHnWJZSmyR = false;
      string PYnEOpsSDw;
      string NiYLejgAKM;
      string yFDBDhVXCO;
      string owAIebEzuw;
      string uxMfLinAox;
      string CASiSKUlBf;
      string TUQnHQiPgD;
      string ehEOQAsXpT;
      string tViELndQoT;
      string GRyPbagXYt;
      string AXSlRUuESS;
      string QxwhlylMcS;
      string mSZMwNjolo;
      string TVywTVCxlp;
      string rZyWCIVPcd;
      string oTtFHhxGoE;
      string kFRcyuyzNQ;
      string uoZlZNTDJn;
      string rTMHAzasnk;
      string XwHhFlHVXH;
      if(PYnEOpsSDw == AXSlRUuESS){JVBMhAtIet = true;}
      else if(AXSlRUuESS == PYnEOpsSDw){OFifnzNQel = true;}
      if(NiYLejgAKM == QxwhlylMcS){NtwBLQsJbz = true;}
      else if(QxwhlylMcS == NiYLejgAKM){NtUFhreiwf = true;}
      if(yFDBDhVXCO == mSZMwNjolo){TFKbrzgrgn = true;}
      else if(mSZMwNjolo == yFDBDhVXCO){JHeydHNruo = true;}
      if(owAIebEzuw == TVywTVCxlp){FyeCdWRzZA = true;}
      else if(TVywTVCxlp == owAIebEzuw){JTJuztrpDu = true;}
      if(uxMfLinAox == rZyWCIVPcd){FSNtXdzGVn = true;}
      else if(rZyWCIVPcd == uxMfLinAox){tnbbLRWYIn = true;}
      if(CASiSKUlBf == oTtFHhxGoE){sxsYmEKZUh = true;}
      else if(oTtFHhxGoE == CASiSKUlBf){YIZazGajCg = true;}
      if(TUQnHQiPgD == kFRcyuyzNQ){SBaqnOOsXo = true;}
      else if(kFRcyuyzNQ == TUQnHQiPgD){kUVocsjZGn = true;}
      if(ehEOQAsXpT == uoZlZNTDJn){zsjbsAqQEO = true;}
      if(tViELndQoT == rTMHAzasnk){zaWrtIFGOY = true;}
      if(GRyPbagXYt == XwHhFlHVXH){LreqgDqWGJ = true;}
      while(uoZlZNTDJn == ehEOQAsXpT){AneBkUfDmL = true;}
      while(rTMHAzasnk == rTMHAzasnk){joiGQAsius = true;}
      while(XwHhFlHVXH == XwHhFlHVXH){SHnWJZSmyR = true;}
      if(JVBMhAtIet == true){JVBMhAtIet = false;}
      if(NtwBLQsJbz == true){NtwBLQsJbz = false;}
      if(TFKbrzgrgn == true){TFKbrzgrgn = false;}
      if(FyeCdWRzZA == true){FyeCdWRzZA = false;}
      if(FSNtXdzGVn == true){FSNtXdzGVn = false;}
      if(sxsYmEKZUh == true){sxsYmEKZUh = false;}
      if(SBaqnOOsXo == true){SBaqnOOsXo = false;}
      if(zsjbsAqQEO == true){zsjbsAqQEO = false;}
      if(zaWrtIFGOY == true){zaWrtIFGOY = false;}
      if(LreqgDqWGJ == true){LreqgDqWGJ = false;}
      if(OFifnzNQel == true){OFifnzNQel = false;}
      if(NtUFhreiwf == true){NtUFhreiwf = false;}
      if(JHeydHNruo == true){JHeydHNruo = false;}
      if(JTJuztrpDu == true){JTJuztrpDu = false;}
      if(tnbbLRWYIn == true){tnbbLRWYIn = false;}
      if(YIZazGajCg == true){YIZazGajCg = false;}
      if(kUVocsjZGn == true){kUVocsjZGn = false;}
      if(AneBkUfDmL == true){AneBkUfDmL = false;}
      if(joiGQAsius == true){joiGQAsius = false;}
      if(SHnWJZSmyR == true){SHnWJZSmyR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PTBYBPEMHL
{ 
  void HqLpwaNhxR()
  { 
      bool UsuBDKkPuT = false;
      bool AIdKnVKRdI = false;
      bool QjpgNSuhTJ = false;
      bool sKcDlMaxKM = false;
      bool RmpEuYJTOX = false;
      bool llYNhkDOnk = false;
      bool OCwlapeZXb = false;
      bool uMGQqdtkln = false;
      bool JbTuXGkPVB = false;
      bool IMJYyOpDdF = false;
      bool tiulcYeIVD = false;
      bool qScAbmiAOU = false;
      bool EPEWShDgSb = false;
      bool npGftafgSy = false;
      bool absSKpjJxK = false;
      bool fpnIAddXTt = false;
      bool UxptPALwGB = false;
      bool GBhQscVlMc = false;
      bool ytjHwxBxfP = false;
      bool wHNXcclzDJ = false;
      string YyJYcyDaER;
      string YNWLJltXfz;
      string QQmNxOGXnZ;
      string sBiZZLJmuZ;
      string loHlXJkmMj;
      string xhLVJHKuaO;
      string rfldXXdwly;
      string bHbGNaJBpn;
      string dTKEcLpMPR;
      string ANLghFDdNz;
      string enAOHoFEIi;
      string yJFljXVgAM;
      string hRfUxNwuXH;
      string XempJoSuwm;
      string GkDgSpIYwJ;
      string jVcBRNHfQs;
      string sJfBKTVOcu;
      string FZkNFxNzCG;
      string FWzOWCClYu;
      string hmdCtwECVy;
      if(YyJYcyDaER == enAOHoFEIi){UsuBDKkPuT = true;}
      else if(enAOHoFEIi == YyJYcyDaER){tiulcYeIVD = true;}
      if(YNWLJltXfz == yJFljXVgAM){AIdKnVKRdI = true;}
      else if(yJFljXVgAM == YNWLJltXfz){qScAbmiAOU = true;}
      if(QQmNxOGXnZ == hRfUxNwuXH){QjpgNSuhTJ = true;}
      else if(hRfUxNwuXH == QQmNxOGXnZ){EPEWShDgSb = true;}
      if(sBiZZLJmuZ == XempJoSuwm){sKcDlMaxKM = true;}
      else if(XempJoSuwm == sBiZZLJmuZ){npGftafgSy = true;}
      if(loHlXJkmMj == GkDgSpIYwJ){RmpEuYJTOX = true;}
      else if(GkDgSpIYwJ == loHlXJkmMj){absSKpjJxK = true;}
      if(xhLVJHKuaO == jVcBRNHfQs){llYNhkDOnk = true;}
      else if(jVcBRNHfQs == xhLVJHKuaO){fpnIAddXTt = true;}
      if(rfldXXdwly == sJfBKTVOcu){OCwlapeZXb = true;}
      else if(sJfBKTVOcu == rfldXXdwly){UxptPALwGB = true;}
      if(bHbGNaJBpn == FZkNFxNzCG){uMGQqdtkln = true;}
      if(dTKEcLpMPR == FWzOWCClYu){JbTuXGkPVB = true;}
      if(ANLghFDdNz == hmdCtwECVy){IMJYyOpDdF = true;}
      while(FZkNFxNzCG == bHbGNaJBpn){GBhQscVlMc = true;}
      while(FWzOWCClYu == FWzOWCClYu){ytjHwxBxfP = true;}
      while(hmdCtwECVy == hmdCtwECVy){wHNXcclzDJ = true;}
      if(UsuBDKkPuT == true){UsuBDKkPuT = false;}
      if(AIdKnVKRdI == true){AIdKnVKRdI = false;}
      if(QjpgNSuhTJ == true){QjpgNSuhTJ = false;}
      if(sKcDlMaxKM == true){sKcDlMaxKM = false;}
      if(RmpEuYJTOX == true){RmpEuYJTOX = false;}
      if(llYNhkDOnk == true){llYNhkDOnk = false;}
      if(OCwlapeZXb == true){OCwlapeZXb = false;}
      if(uMGQqdtkln == true){uMGQqdtkln = false;}
      if(JbTuXGkPVB == true){JbTuXGkPVB = false;}
      if(IMJYyOpDdF == true){IMJYyOpDdF = false;}
      if(tiulcYeIVD == true){tiulcYeIVD = false;}
      if(qScAbmiAOU == true){qScAbmiAOU = false;}
      if(EPEWShDgSb == true){EPEWShDgSb = false;}
      if(npGftafgSy == true){npGftafgSy = false;}
      if(absSKpjJxK == true){absSKpjJxK = false;}
      if(fpnIAddXTt == true){fpnIAddXTt = false;}
      if(UxptPALwGB == true){UxptPALwGB = false;}
      if(GBhQscVlMc == true){GBhQscVlMc = false;}
      if(ytjHwxBxfP == true){ytjHwxBxfP = false;}
      if(wHNXcclzDJ == true){wHNXcclzDJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HCTLVSUCYK
{ 
  void SMFCYTasWt()
  { 
      bool ecNHYcGZOd = false;
      bool iIaCkJZaSf = false;
      bool qgSDQsSXGW = false;
      bool CXHxAAbCuM = false;
      bool QZyJPjWYht = false;
      bool PeWNiyJKpf = false;
      bool KiTqbLAcCj = false;
      bool hXeGPQhImf = false;
      bool VsoLHWBtOB = false;
      bool qQLPBhGGhE = false;
      bool jtVyMqAQxR = false;
      bool PBWKKQsHiE = false;
      bool JGOBsQLPEg = false;
      bool KaZiwbXpyP = false;
      bool WjwwlosAFk = false;
      bool nyXdtceUFw = false;
      bool ekMPGnanNh = false;
      bool sCJSgZJRPD = false;
      bool WLJSsMDwnS = false;
      bool wCkCjlXfox = false;
      string IHLJGbpuCN;
      string uVAhrwsDPW;
      string rzbIBjEoNh;
      string uDlhBjSWza;
      string eCRdmtZUsE;
      string ZNVPMIeCHV;
      string WBgUSqiSgI;
      string cVDorohyVH;
      string JjuJHhhVUr;
      string EPPcDdUxLu;
      string KHmkbEJgXX;
      string afgzLmFXMj;
      string JMyoDMFakO;
      string TjmZxCwKgC;
      string XByxQXiQQP;
      string YxjalxJyhO;
      string yiuIDqsGCJ;
      string qupKMHNBXe;
      string doJUpWzMnz;
      string sxbSDoFpsZ;
      if(IHLJGbpuCN == KHmkbEJgXX){ecNHYcGZOd = true;}
      else if(KHmkbEJgXX == IHLJGbpuCN){jtVyMqAQxR = true;}
      if(uVAhrwsDPW == afgzLmFXMj){iIaCkJZaSf = true;}
      else if(afgzLmFXMj == uVAhrwsDPW){PBWKKQsHiE = true;}
      if(rzbIBjEoNh == JMyoDMFakO){qgSDQsSXGW = true;}
      else if(JMyoDMFakO == rzbIBjEoNh){JGOBsQLPEg = true;}
      if(uDlhBjSWza == TjmZxCwKgC){CXHxAAbCuM = true;}
      else if(TjmZxCwKgC == uDlhBjSWza){KaZiwbXpyP = true;}
      if(eCRdmtZUsE == XByxQXiQQP){QZyJPjWYht = true;}
      else if(XByxQXiQQP == eCRdmtZUsE){WjwwlosAFk = true;}
      if(ZNVPMIeCHV == YxjalxJyhO){PeWNiyJKpf = true;}
      else if(YxjalxJyhO == ZNVPMIeCHV){nyXdtceUFw = true;}
      if(WBgUSqiSgI == yiuIDqsGCJ){KiTqbLAcCj = true;}
      else if(yiuIDqsGCJ == WBgUSqiSgI){ekMPGnanNh = true;}
      if(cVDorohyVH == qupKMHNBXe){hXeGPQhImf = true;}
      if(JjuJHhhVUr == doJUpWzMnz){VsoLHWBtOB = true;}
      if(EPPcDdUxLu == sxbSDoFpsZ){qQLPBhGGhE = true;}
      while(qupKMHNBXe == cVDorohyVH){sCJSgZJRPD = true;}
      while(doJUpWzMnz == doJUpWzMnz){WLJSsMDwnS = true;}
      while(sxbSDoFpsZ == sxbSDoFpsZ){wCkCjlXfox = true;}
      if(ecNHYcGZOd == true){ecNHYcGZOd = false;}
      if(iIaCkJZaSf == true){iIaCkJZaSf = false;}
      if(qgSDQsSXGW == true){qgSDQsSXGW = false;}
      if(CXHxAAbCuM == true){CXHxAAbCuM = false;}
      if(QZyJPjWYht == true){QZyJPjWYht = false;}
      if(PeWNiyJKpf == true){PeWNiyJKpf = false;}
      if(KiTqbLAcCj == true){KiTqbLAcCj = false;}
      if(hXeGPQhImf == true){hXeGPQhImf = false;}
      if(VsoLHWBtOB == true){VsoLHWBtOB = false;}
      if(qQLPBhGGhE == true){qQLPBhGGhE = false;}
      if(jtVyMqAQxR == true){jtVyMqAQxR = false;}
      if(PBWKKQsHiE == true){PBWKKQsHiE = false;}
      if(JGOBsQLPEg == true){JGOBsQLPEg = false;}
      if(KaZiwbXpyP == true){KaZiwbXpyP = false;}
      if(WjwwlosAFk == true){WjwwlosAFk = false;}
      if(nyXdtceUFw == true){nyXdtceUFw = false;}
      if(ekMPGnanNh == true){ekMPGnanNh = false;}
      if(sCJSgZJRPD == true){sCJSgZJRPD = false;}
      if(WLJSsMDwnS == true){WLJSsMDwnS = false;}
      if(wCkCjlXfox == true){wCkCjlXfox = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VTHFNDKAIY
{ 
  void gGRHNXQwhi()
  { 
      bool kgpLZkcgcP = false;
      bool ETMCdJCIhd = false;
      bool ELVUZFAuQh = false;
      bool ZuyQPqCgDM = false;
      bool SBBSfnZRiW = false;
      bool wQeaHYLVkT = false;
      bool jhQtoIUwll = false;
      bool HVEVKDJDol = false;
      bool fhLslJQXIq = false;
      bool ffuibkkHcW = false;
      bool ScfxPaLIPE = false;
      bool PHfznBVWIe = false;
      bool qxmuGaZUsY = false;
      bool RCZRSCCOdK = false;
      bool yHHEbXAwua = false;
      bool PNyyfVpkpn = false;
      bool BpPqmMhNfk = false;
      bool zHsxgioiTi = false;
      bool acZSJDDblx = false;
      bool MQXoJHrQRO = false;
      string PZRQIGSqKD;
      string EpHBAHxwiA;
      string FqRtCKpVnD;
      string AEMmYPJLEB;
      string xMSpYqZuQK;
      string cYNlAYHWNy;
      string PxCHDAcUcj;
      string xlrgCrXbVL;
      string kuEdZapamA;
      string HmxGlzKLlY;
      string OFSfNqgfiH;
      string AfBCMUsYgb;
      string JBhccKnktD;
      string hMoxxebXPi;
      string tKrezblusR;
      string GkdKOMWoDC;
      string CukeZmpEEh;
      string rUIxgzIDcB;
      string Yrrcxwhehj;
      string HlUNgzYMEM;
      if(PZRQIGSqKD == OFSfNqgfiH){kgpLZkcgcP = true;}
      else if(OFSfNqgfiH == PZRQIGSqKD){ScfxPaLIPE = true;}
      if(EpHBAHxwiA == AfBCMUsYgb){ETMCdJCIhd = true;}
      else if(AfBCMUsYgb == EpHBAHxwiA){PHfznBVWIe = true;}
      if(FqRtCKpVnD == JBhccKnktD){ELVUZFAuQh = true;}
      else if(JBhccKnktD == FqRtCKpVnD){qxmuGaZUsY = true;}
      if(AEMmYPJLEB == hMoxxebXPi){ZuyQPqCgDM = true;}
      else if(hMoxxebXPi == AEMmYPJLEB){RCZRSCCOdK = true;}
      if(xMSpYqZuQK == tKrezblusR){SBBSfnZRiW = true;}
      else if(tKrezblusR == xMSpYqZuQK){yHHEbXAwua = true;}
      if(cYNlAYHWNy == GkdKOMWoDC){wQeaHYLVkT = true;}
      else if(GkdKOMWoDC == cYNlAYHWNy){PNyyfVpkpn = true;}
      if(PxCHDAcUcj == CukeZmpEEh){jhQtoIUwll = true;}
      else if(CukeZmpEEh == PxCHDAcUcj){BpPqmMhNfk = true;}
      if(xlrgCrXbVL == rUIxgzIDcB){HVEVKDJDol = true;}
      if(kuEdZapamA == Yrrcxwhehj){fhLslJQXIq = true;}
      if(HmxGlzKLlY == HlUNgzYMEM){ffuibkkHcW = true;}
      while(rUIxgzIDcB == xlrgCrXbVL){zHsxgioiTi = true;}
      while(Yrrcxwhehj == Yrrcxwhehj){acZSJDDblx = true;}
      while(HlUNgzYMEM == HlUNgzYMEM){MQXoJHrQRO = true;}
      if(kgpLZkcgcP == true){kgpLZkcgcP = false;}
      if(ETMCdJCIhd == true){ETMCdJCIhd = false;}
      if(ELVUZFAuQh == true){ELVUZFAuQh = false;}
      if(ZuyQPqCgDM == true){ZuyQPqCgDM = false;}
      if(SBBSfnZRiW == true){SBBSfnZRiW = false;}
      if(wQeaHYLVkT == true){wQeaHYLVkT = false;}
      if(jhQtoIUwll == true){jhQtoIUwll = false;}
      if(HVEVKDJDol == true){HVEVKDJDol = false;}
      if(fhLslJQXIq == true){fhLslJQXIq = false;}
      if(ffuibkkHcW == true){ffuibkkHcW = false;}
      if(ScfxPaLIPE == true){ScfxPaLIPE = false;}
      if(PHfznBVWIe == true){PHfznBVWIe = false;}
      if(qxmuGaZUsY == true){qxmuGaZUsY = false;}
      if(RCZRSCCOdK == true){RCZRSCCOdK = false;}
      if(yHHEbXAwua == true){yHHEbXAwua = false;}
      if(PNyyfVpkpn == true){PNyyfVpkpn = false;}
      if(BpPqmMhNfk == true){BpPqmMhNfk = false;}
      if(zHsxgioiTi == true){zHsxgioiTi = false;}
      if(acZSJDDblx == true){acZSJDDblx = false;}
      if(MQXoJHrQRO == true){MQXoJHrQRO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FWEKBMMMVE
{ 
  void leKimSpmnE()
  { 
      bool sytwOGxsuG = false;
      bool HAJPlcBrMd = false;
      bool VKRJTLmzYi = false;
      bool CoMdJMOEoQ = false;
      bool ibWpcPfsWt = false;
      bool CMIlJigjbD = false;
      bool TyUMERmfFZ = false;
      bool OxCuttmagE = false;
      bool esbdgpgaTa = false;
      bool fdblxkHJlK = false;
      bool bAnwfEJMqP = false;
      bool uFDXXZVpfN = false;
      bool jMMdtjUQyJ = false;
      bool mdoVbeFexb = false;
      bool fTjEfZaDNW = false;
      bool PQcXZOmJCw = false;
      bool jsOhbQQgur = false;
      bool UprEgQcHyT = false;
      bool IQCbsWAQuN = false;
      bool qwbBrmFBcO = false;
      string UAwjpwbOTC;
      string TMGrhODEES;
      string YJqlBkWkSP;
      string QoedjIzTND;
      string RRBNCQKJRm;
      string TZTNFKIKhE;
      string ZquDkdhcHZ;
      string OipABHIdik;
      string aMTfuqURYZ;
      string AokJdaVxcX;
      string ihCrXkjTLx;
      string BdawcMXPHt;
      string JQEhYZygVa;
      string lKBLCsKaHK;
      string GBFaXVNnfR;
      string DFpiORcTSy;
      string mCxjKqcOtj;
      string CwIwmHKcKD;
      string LJAEXgUSxj;
      string PpIJXEEUPf;
      if(UAwjpwbOTC == ihCrXkjTLx){sytwOGxsuG = true;}
      else if(ihCrXkjTLx == UAwjpwbOTC){bAnwfEJMqP = true;}
      if(TMGrhODEES == BdawcMXPHt){HAJPlcBrMd = true;}
      else if(BdawcMXPHt == TMGrhODEES){uFDXXZVpfN = true;}
      if(YJqlBkWkSP == JQEhYZygVa){VKRJTLmzYi = true;}
      else if(JQEhYZygVa == YJqlBkWkSP){jMMdtjUQyJ = true;}
      if(QoedjIzTND == lKBLCsKaHK){CoMdJMOEoQ = true;}
      else if(lKBLCsKaHK == QoedjIzTND){mdoVbeFexb = true;}
      if(RRBNCQKJRm == GBFaXVNnfR){ibWpcPfsWt = true;}
      else if(GBFaXVNnfR == RRBNCQKJRm){fTjEfZaDNW = true;}
      if(TZTNFKIKhE == DFpiORcTSy){CMIlJigjbD = true;}
      else if(DFpiORcTSy == TZTNFKIKhE){PQcXZOmJCw = true;}
      if(ZquDkdhcHZ == mCxjKqcOtj){TyUMERmfFZ = true;}
      else if(mCxjKqcOtj == ZquDkdhcHZ){jsOhbQQgur = true;}
      if(OipABHIdik == CwIwmHKcKD){OxCuttmagE = true;}
      if(aMTfuqURYZ == LJAEXgUSxj){esbdgpgaTa = true;}
      if(AokJdaVxcX == PpIJXEEUPf){fdblxkHJlK = true;}
      while(CwIwmHKcKD == OipABHIdik){UprEgQcHyT = true;}
      while(LJAEXgUSxj == LJAEXgUSxj){IQCbsWAQuN = true;}
      while(PpIJXEEUPf == PpIJXEEUPf){qwbBrmFBcO = true;}
      if(sytwOGxsuG == true){sytwOGxsuG = false;}
      if(HAJPlcBrMd == true){HAJPlcBrMd = false;}
      if(VKRJTLmzYi == true){VKRJTLmzYi = false;}
      if(CoMdJMOEoQ == true){CoMdJMOEoQ = false;}
      if(ibWpcPfsWt == true){ibWpcPfsWt = false;}
      if(CMIlJigjbD == true){CMIlJigjbD = false;}
      if(TyUMERmfFZ == true){TyUMERmfFZ = false;}
      if(OxCuttmagE == true){OxCuttmagE = false;}
      if(esbdgpgaTa == true){esbdgpgaTa = false;}
      if(fdblxkHJlK == true){fdblxkHJlK = false;}
      if(bAnwfEJMqP == true){bAnwfEJMqP = false;}
      if(uFDXXZVpfN == true){uFDXXZVpfN = false;}
      if(jMMdtjUQyJ == true){jMMdtjUQyJ = false;}
      if(mdoVbeFexb == true){mdoVbeFexb = false;}
      if(fTjEfZaDNW == true){fTjEfZaDNW = false;}
      if(PQcXZOmJCw == true){PQcXZOmJCw = false;}
      if(jsOhbQQgur == true){jsOhbQQgur = false;}
      if(UprEgQcHyT == true){UprEgQcHyT = false;}
      if(IQCbsWAQuN == true){IQCbsWAQuN = false;}
      if(qwbBrmFBcO == true){qwbBrmFBcO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RTMPZUCCAI
{ 
  void HdbFbaqKei()
  { 
      bool jCCFIqzmub = false;
      bool McdYKyukkp = false;
      bool PLjrPCgYrc = false;
      bool WBTHUXfOAn = false;
      bool CnpyagwClL = false;
      bool yJuzAYSJoF = false;
      bool JZuSEKIVDm = false;
      bool SfjxmbVkRi = false;
      bool GdlgdNGUHw = false;
      bool EVZudcrWsP = false;
      bool YZyzrSYyLY = false;
      bool DgrFyfmOnq = false;
      bool EmOHhxFoSK = false;
      bool iyrBKgemnL = false;
      bool nIJirWdTwy = false;
      bool odiCLkKqQu = false;
      bool MjeAoFopuR = false;
      bool AAZcCudfOK = false;
      bool SlrTVFOopY = false;
      bool WnVsyEcIsm = false;
      string cFMnrGtWnr;
      string yIAWHXnxuo;
      string iTDLNupJLE;
      string mKhKZkrXxI;
      string xkSBpCUemE;
      string NPdnMJCAZw;
      string QjLjEnapwV;
      string fPAmrxABVK;
      string aKWGpXftxQ;
      string iryAqMZixB;
      string behQYyOpwP;
      string IBeOVFNEsf;
      string HgrfmnRzue;
      string WQDTiwbFhq;
      string JoyhHhNiel;
      string zUoRtulCdk;
      string gPuQrqxKfZ;
      string cIVCWRiJXF;
      string ZhUJeBbkZm;
      string JZaxJstgoQ;
      if(cFMnrGtWnr == behQYyOpwP){jCCFIqzmub = true;}
      else if(behQYyOpwP == cFMnrGtWnr){YZyzrSYyLY = true;}
      if(yIAWHXnxuo == IBeOVFNEsf){McdYKyukkp = true;}
      else if(IBeOVFNEsf == yIAWHXnxuo){DgrFyfmOnq = true;}
      if(iTDLNupJLE == HgrfmnRzue){PLjrPCgYrc = true;}
      else if(HgrfmnRzue == iTDLNupJLE){EmOHhxFoSK = true;}
      if(mKhKZkrXxI == WQDTiwbFhq){WBTHUXfOAn = true;}
      else if(WQDTiwbFhq == mKhKZkrXxI){iyrBKgemnL = true;}
      if(xkSBpCUemE == JoyhHhNiel){CnpyagwClL = true;}
      else if(JoyhHhNiel == xkSBpCUemE){nIJirWdTwy = true;}
      if(NPdnMJCAZw == zUoRtulCdk){yJuzAYSJoF = true;}
      else if(zUoRtulCdk == NPdnMJCAZw){odiCLkKqQu = true;}
      if(QjLjEnapwV == gPuQrqxKfZ){JZuSEKIVDm = true;}
      else if(gPuQrqxKfZ == QjLjEnapwV){MjeAoFopuR = true;}
      if(fPAmrxABVK == cIVCWRiJXF){SfjxmbVkRi = true;}
      if(aKWGpXftxQ == ZhUJeBbkZm){GdlgdNGUHw = true;}
      if(iryAqMZixB == JZaxJstgoQ){EVZudcrWsP = true;}
      while(cIVCWRiJXF == fPAmrxABVK){AAZcCudfOK = true;}
      while(ZhUJeBbkZm == ZhUJeBbkZm){SlrTVFOopY = true;}
      while(JZaxJstgoQ == JZaxJstgoQ){WnVsyEcIsm = true;}
      if(jCCFIqzmub == true){jCCFIqzmub = false;}
      if(McdYKyukkp == true){McdYKyukkp = false;}
      if(PLjrPCgYrc == true){PLjrPCgYrc = false;}
      if(WBTHUXfOAn == true){WBTHUXfOAn = false;}
      if(CnpyagwClL == true){CnpyagwClL = false;}
      if(yJuzAYSJoF == true){yJuzAYSJoF = false;}
      if(JZuSEKIVDm == true){JZuSEKIVDm = false;}
      if(SfjxmbVkRi == true){SfjxmbVkRi = false;}
      if(GdlgdNGUHw == true){GdlgdNGUHw = false;}
      if(EVZudcrWsP == true){EVZudcrWsP = false;}
      if(YZyzrSYyLY == true){YZyzrSYyLY = false;}
      if(DgrFyfmOnq == true){DgrFyfmOnq = false;}
      if(EmOHhxFoSK == true){EmOHhxFoSK = false;}
      if(iyrBKgemnL == true){iyrBKgemnL = false;}
      if(nIJirWdTwy == true){nIJirWdTwy = false;}
      if(odiCLkKqQu == true){odiCLkKqQu = false;}
      if(MjeAoFopuR == true){MjeAoFopuR = false;}
      if(AAZcCudfOK == true){AAZcCudfOK = false;}
      if(SlrTVFOopY == true){SlrTVFOopY = false;}
      if(WnVsyEcIsm == true){WnVsyEcIsm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XDZOFRRSCZ
{ 
  void XnebHlCcEH()
  { 
      bool efBocqamqa = false;
      bool KcZpkVVdno = false;
      bool mTntjGtfRg = false;
      bool EHmzCVOmII = false;
      bool wZIJRqCUwi = false;
      bool FSDmYLqHFV = false;
      bool wtVKVCpamO = false;
      bool GiUerNKebr = false;
      bool DYihblEzZq = false;
      bool dHglMBDxmP = false;
      bool AbggcVyYuK = false;
      bool AMfMSWKmij = false;
      bool yqAwkyBhSp = false;
      bool KMqLqbrCFF = false;
      bool meEOpQbUTo = false;
      bool qQOCRJakwd = false;
      bool TQGEAmVTUq = false;
      bool eIhcxSllFU = false;
      bool WgNczsynth = false;
      bool AHFalWYzND = false;
      string WseDLbULAV;
      string hgzUSpuWtA;
      string KCqkPgBqMT;
      string ttkdHTnWok;
      string QXFJelUYDw;
      string AAVUMUBtnd;
      string adzgamwVMy;
      string BYgIjlwhGc;
      string MbnPSsYQQl;
      string StiLKmYYhq;
      string pyMEtbTMka;
      string YTnKRyoiNh;
      string NeFZfHoVxx;
      string NXAOmNPiUq;
      string ZMfpNyFYsL;
      string xoKAcKslXm;
      string lyPnMATZWE;
      string iGOWIBzPLh;
      string BQbkzXNAkc;
      string UcLhEaxrcM;
      if(WseDLbULAV == pyMEtbTMka){efBocqamqa = true;}
      else if(pyMEtbTMka == WseDLbULAV){AbggcVyYuK = true;}
      if(hgzUSpuWtA == YTnKRyoiNh){KcZpkVVdno = true;}
      else if(YTnKRyoiNh == hgzUSpuWtA){AMfMSWKmij = true;}
      if(KCqkPgBqMT == NeFZfHoVxx){mTntjGtfRg = true;}
      else if(NeFZfHoVxx == KCqkPgBqMT){yqAwkyBhSp = true;}
      if(ttkdHTnWok == NXAOmNPiUq){EHmzCVOmII = true;}
      else if(NXAOmNPiUq == ttkdHTnWok){KMqLqbrCFF = true;}
      if(QXFJelUYDw == ZMfpNyFYsL){wZIJRqCUwi = true;}
      else if(ZMfpNyFYsL == QXFJelUYDw){meEOpQbUTo = true;}
      if(AAVUMUBtnd == xoKAcKslXm){FSDmYLqHFV = true;}
      else if(xoKAcKslXm == AAVUMUBtnd){qQOCRJakwd = true;}
      if(adzgamwVMy == lyPnMATZWE){wtVKVCpamO = true;}
      else if(lyPnMATZWE == adzgamwVMy){TQGEAmVTUq = true;}
      if(BYgIjlwhGc == iGOWIBzPLh){GiUerNKebr = true;}
      if(MbnPSsYQQl == BQbkzXNAkc){DYihblEzZq = true;}
      if(StiLKmYYhq == UcLhEaxrcM){dHglMBDxmP = true;}
      while(iGOWIBzPLh == BYgIjlwhGc){eIhcxSllFU = true;}
      while(BQbkzXNAkc == BQbkzXNAkc){WgNczsynth = true;}
      while(UcLhEaxrcM == UcLhEaxrcM){AHFalWYzND = true;}
      if(efBocqamqa == true){efBocqamqa = false;}
      if(KcZpkVVdno == true){KcZpkVVdno = false;}
      if(mTntjGtfRg == true){mTntjGtfRg = false;}
      if(EHmzCVOmII == true){EHmzCVOmII = false;}
      if(wZIJRqCUwi == true){wZIJRqCUwi = false;}
      if(FSDmYLqHFV == true){FSDmYLqHFV = false;}
      if(wtVKVCpamO == true){wtVKVCpamO = false;}
      if(GiUerNKebr == true){GiUerNKebr = false;}
      if(DYihblEzZq == true){DYihblEzZq = false;}
      if(dHglMBDxmP == true){dHglMBDxmP = false;}
      if(AbggcVyYuK == true){AbggcVyYuK = false;}
      if(AMfMSWKmij == true){AMfMSWKmij = false;}
      if(yqAwkyBhSp == true){yqAwkyBhSp = false;}
      if(KMqLqbrCFF == true){KMqLqbrCFF = false;}
      if(meEOpQbUTo == true){meEOpQbUTo = false;}
      if(qQOCRJakwd == true){qQOCRJakwd = false;}
      if(TQGEAmVTUq == true){TQGEAmVTUq = false;}
      if(eIhcxSllFU == true){eIhcxSllFU = false;}
      if(WgNczsynth == true){WgNczsynth = false;}
      if(AHFalWYzND == true){AHFalWYzND = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TQBUMTEOKW
{ 
  void fGDHcjddUi()
  { 
      bool lxlbKPXbqQ = false;
      bool prcmUoDjLQ = false;
      bool RQWiqadDfP = false;
      bool PSkpWqKmQM = false;
      bool rRrkKBWtiW = false;
      bool YSBUHVaDki = false;
      bool lTwbBWHlQc = false;
      bool dQSyYzXkXo = false;
      bool DiTIqwRQiB = false;
      bool QHBgaXVQim = false;
      bool tkdFsIzCwH = false;
      bool xofwfCznkF = false;
      bool FpCPMVOkXA = false;
      bool cHCjuSEOOh = false;
      bool wPTaDabFBX = false;
      bool YhfdhDhOsW = false;
      bool sNdweomuBM = false;
      bool ykYCIoWbLl = false;
      bool tJjAaubYBq = false;
      bool joUroikWwN = false;
      string hxqsYldNIG;
      string mlIVQlPMUB;
      string MgofHKjQDL;
      string bWJWLNrPYE;
      string eNHAefrBtQ;
      string GjlPaAHKkO;
      string BMKweQbkKC;
      string szmPWzZoAb;
      string RiWlFqjtuK;
      string GgeKDRDKVO;
      string DGqrWGwWsb;
      string aSKIwSpXqm;
      string fgpzwMTcLE;
      string uOSkXKqdPy;
      string uNBSjmWWNk;
      string bfTiiWQqwK;
      string lSKngLAYjk;
      string aLIrqRfXOJ;
      string oxPacPtjCB;
      string tzhEMbCMlY;
      if(hxqsYldNIG == DGqrWGwWsb){lxlbKPXbqQ = true;}
      else if(DGqrWGwWsb == hxqsYldNIG){tkdFsIzCwH = true;}
      if(mlIVQlPMUB == aSKIwSpXqm){prcmUoDjLQ = true;}
      else if(aSKIwSpXqm == mlIVQlPMUB){xofwfCznkF = true;}
      if(MgofHKjQDL == fgpzwMTcLE){RQWiqadDfP = true;}
      else if(fgpzwMTcLE == MgofHKjQDL){FpCPMVOkXA = true;}
      if(bWJWLNrPYE == uOSkXKqdPy){PSkpWqKmQM = true;}
      else if(uOSkXKqdPy == bWJWLNrPYE){cHCjuSEOOh = true;}
      if(eNHAefrBtQ == uNBSjmWWNk){rRrkKBWtiW = true;}
      else if(uNBSjmWWNk == eNHAefrBtQ){wPTaDabFBX = true;}
      if(GjlPaAHKkO == bfTiiWQqwK){YSBUHVaDki = true;}
      else if(bfTiiWQqwK == GjlPaAHKkO){YhfdhDhOsW = true;}
      if(BMKweQbkKC == lSKngLAYjk){lTwbBWHlQc = true;}
      else if(lSKngLAYjk == BMKweQbkKC){sNdweomuBM = true;}
      if(szmPWzZoAb == aLIrqRfXOJ){dQSyYzXkXo = true;}
      if(RiWlFqjtuK == oxPacPtjCB){DiTIqwRQiB = true;}
      if(GgeKDRDKVO == tzhEMbCMlY){QHBgaXVQim = true;}
      while(aLIrqRfXOJ == szmPWzZoAb){ykYCIoWbLl = true;}
      while(oxPacPtjCB == oxPacPtjCB){tJjAaubYBq = true;}
      while(tzhEMbCMlY == tzhEMbCMlY){joUroikWwN = true;}
      if(lxlbKPXbqQ == true){lxlbKPXbqQ = false;}
      if(prcmUoDjLQ == true){prcmUoDjLQ = false;}
      if(RQWiqadDfP == true){RQWiqadDfP = false;}
      if(PSkpWqKmQM == true){PSkpWqKmQM = false;}
      if(rRrkKBWtiW == true){rRrkKBWtiW = false;}
      if(YSBUHVaDki == true){YSBUHVaDki = false;}
      if(lTwbBWHlQc == true){lTwbBWHlQc = false;}
      if(dQSyYzXkXo == true){dQSyYzXkXo = false;}
      if(DiTIqwRQiB == true){DiTIqwRQiB = false;}
      if(QHBgaXVQim == true){QHBgaXVQim = false;}
      if(tkdFsIzCwH == true){tkdFsIzCwH = false;}
      if(xofwfCznkF == true){xofwfCznkF = false;}
      if(FpCPMVOkXA == true){FpCPMVOkXA = false;}
      if(cHCjuSEOOh == true){cHCjuSEOOh = false;}
      if(wPTaDabFBX == true){wPTaDabFBX = false;}
      if(YhfdhDhOsW == true){YhfdhDhOsW = false;}
      if(sNdweomuBM == true){sNdweomuBM = false;}
      if(ykYCIoWbLl == true){ykYCIoWbLl = false;}
      if(tJjAaubYBq == true){tJjAaubYBq = false;}
      if(joUroikWwN == true){joUroikWwN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FOESEHPBJA
{ 
  void BRsIAcbXzl()
  { 
      bool xclizEKRSw = false;
      bool CDAGguLGAb = false;
      bool bIPdMjAVjR = false;
      bool oLuOqREyUV = false;
      bool RfsSTFHECl = false;
      bool zIPTRoMIVP = false;
      bool DohBHpHlOO = false;
      bool qNkdKwOxJH = false;
      bool buSxRfwbwC = false;
      bool FubERbxqLd = false;
      bool xUpmulXkJV = false;
      bool ZPzOmHWjja = false;
      bool tfoMJukfLh = false;
      bool yWkeKGFfCe = false;
      bool IKRabowNRK = false;
      bool FNHjjQfdcz = false;
      bool BqZbWCdTEf = false;
      bool BphFRjONjU = false;
      bool zXOBbkPAus = false;
      bool abCCdRjpDY = false;
      string xHsPAHltkE;
      string CRThQbATdf;
      string UpohSdsLjP;
      string idsZfNRjBP;
      string HsoAUUinEp;
      string fxBnZGSLxV;
      string OZKUUXXsBC;
      string KPRNXbAoNx;
      string tEHsjkcFAY;
      string uGlfBhhUfw;
      string wolBfPfmPy;
      string FdxAaJRRki;
      string tSscGDclMp;
      string sfIRAFRFMT;
      string FppBTRIlEq;
      string PQiwBdwJuc;
      string lsaZFYUfzV;
      string rLFRcEbrIo;
      string uqgUZcxMPV;
      string JHKjgLOPwt;
      if(xHsPAHltkE == wolBfPfmPy){xclizEKRSw = true;}
      else if(wolBfPfmPy == xHsPAHltkE){xUpmulXkJV = true;}
      if(CRThQbATdf == FdxAaJRRki){CDAGguLGAb = true;}
      else if(FdxAaJRRki == CRThQbATdf){ZPzOmHWjja = true;}
      if(UpohSdsLjP == tSscGDclMp){bIPdMjAVjR = true;}
      else if(tSscGDclMp == UpohSdsLjP){tfoMJukfLh = true;}
      if(idsZfNRjBP == sfIRAFRFMT){oLuOqREyUV = true;}
      else if(sfIRAFRFMT == idsZfNRjBP){yWkeKGFfCe = true;}
      if(HsoAUUinEp == FppBTRIlEq){RfsSTFHECl = true;}
      else if(FppBTRIlEq == HsoAUUinEp){IKRabowNRK = true;}
      if(fxBnZGSLxV == PQiwBdwJuc){zIPTRoMIVP = true;}
      else if(PQiwBdwJuc == fxBnZGSLxV){FNHjjQfdcz = true;}
      if(OZKUUXXsBC == lsaZFYUfzV){DohBHpHlOO = true;}
      else if(lsaZFYUfzV == OZKUUXXsBC){BqZbWCdTEf = true;}
      if(KPRNXbAoNx == rLFRcEbrIo){qNkdKwOxJH = true;}
      if(tEHsjkcFAY == uqgUZcxMPV){buSxRfwbwC = true;}
      if(uGlfBhhUfw == JHKjgLOPwt){FubERbxqLd = true;}
      while(rLFRcEbrIo == KPRNXbAoNx){BphFRjONjU = true;}
      while(uqgUZcxMPV == uqgUZcxMPV){zXOBbkPAus = true;}
      while(JHKjgLOPwt == JHKjgLOPwt){abCCdRjpDY = true;}
      if(xclizEKRSw == true){xclizEKRSw = false;}
      if(CDAGguLGAb == true){CDAGguLGAb = false;}
      if(bIPdMjAVjR == true){bIPdMjAVjR = false;}
      if(oLuOqREyUV == true){oLuOqREyUV = false;}
      if(RfsSTFHECl == true){RfsSTFHECl = false;}
      if(zIPTRoMIVP == true){zIPTRoMIVP = false;}
      if(DohBHpHlOO == true){DohBHpHlOO = false;}
      if(qNkdKwOxJH == true){qNkdKwOxJH = false;}
      if(buSxRfwbwC == true){buSxRfwbwC = false;}
      if(FubERbxqLd == true){FubERbxqLd = false;}
      if(xUpmulXkJV == true){xUpmulXkJV = false;}
      if(ZPzOmHWjja == true){ZPzOmHWjja = false;}
      if(tfoMJukfLh == true){tfoMJukfLh = false;}
      if(yWkeKGFfCe == true){yWkeKGFfCe = false;}
      if(IKRabowNRK == true){IKRabowNRK = false;}
      if(FNHjjQfdcz == true){FNHjjQfdcz = false;}
      if(BqZbWCdTEf == true){BqZbWCdTEf = false;}
      if(BphFRjONjU == true){BphFRjONjU = false;}
      if(zXOBbkPAus == true){zXOBbkPAus = false;}
      if(abCCdRjpDY == true){abCCdRjpDY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LCRXCPNOUW
{ 
  void MFNVauJaAN()
  { 
      bool oTqTdVYVxm = false;
      bool LmYLZadoOR = false;
      bool MiMAJfIxUw = false;
      bool dtxjnquAHf = false;
      bool lEHjubzJAr = false;
      bool jxfpyFHqJy = false;
      bool MbABIQpnWi = false;
      bool edhheIabEh = false;
      bool fywcLgOGlh = false;
      bool iEpJTKEGbe = false;
      bool kLlRMGPxLo = false;
      bool eflbRNeWpb = false;
      bool BjBnzamYOU = false;
      bool EUAZwUMeQE = false;
      bool RRuxDDROqF = false;
      bool egPzdBKySk = false;
      bool TqipkJfMex = false;
      bool BAGlKjnEkw = false;
      bool JYgIoWFAwt = false;
      bool KNLejZhELt = false;
      string ndHzEmfkkW;
      string qGCWURdffS;
      string OBdjfijnpg;
      string XCfrHgmfth;
      string eakgXZrcie;
      string yxsEXmAXTV;
      string DruEznZKOn;
      string eykymnPwLF;
      string pGELhZJaTU;
      string gPLYdlffhj;
      string zhOuzALuQj;
      string WDLNfwmiVY;
      string ezptGOlMTB;
      string HjObGHrJLh;
      string NNJjydDyrh;
      string zwJIEArUnk;
      string OyaPbmnjGY;
      string DdXnKQoFuc;
      string KmUlBKZFXG;
      string OXUaSOmtIK;
      if(ndHzEmfkkW == zhOuzALuQj){oTqTdVYVxm = true;}
      else if(zhOuzALuQj == ndHzEmfkkW){kLlRMGPxLo = true;}
      if(qGCWURdffS == WDLNfwmiVY){LmYLZadoOR = true;}
      else if(WDLNfwmiVY == qGCWURdffS){eflbRNeWpb = true;}
      if(OBdjfijnpg == ezptGOlMTB){MiMAJfIxUw = true;}
      else if(ezptGOlMTB == OBdjfijnpg){BjBnzamYOU = true;}
      if(XCfrHgmfth == HjObGHrJLh){dtxjnquAHf = true;}
      else if(HjObGHrJLh == XCfrHgmfth){EUAZwUMeQE = true;}
      if(eakgXZrcie == NNJjydDyrh){lEHjubzJAr = true;}
      else if(NNJjydDyrh == eakgXZrcie){RRuxDDROqF = true;}
      if(yxsEXmAXTV == zwJIEArUnk){jxfpyFHqJy = true;}
      else if(zwJIEArUnk == yxsEXmAXTV){egPzdBKySk = true;}
      if(DruEznZKOn == OyaPbmnjGY){MbABIQpnWi = true;}
      else if(OyaPbmnjGY == DruEznZKOn){TqipkJfMex = true;}
      if(eykymnPwLF == DdXnKQoFuc){edhheIabEh = true;}
      if(pGELhZJaTU == KmUlBKZFXG){fywcLgOGlh = true;}
      if(gPLYdlffhj == OXUaSOmtIK){iEpJTKEGbe = true;}
      while(DdXnKQoFuc == eykymnPwLF){BAGlKjnEkw = true;}
      while(KmUlBKZFXG == KmUlBKZFXG){JYgIoWFAwt = true;}
      while(OXUaSOmtIK == OXUaSOmtIK){KNLejZhELt = true;}
      if(oTqTdVYVxm == true){oTqTdVYVxm = false;}
      if(LmYLZadoOR == true){LmYLZadoOR = false;}
      if(MiMAJfIxUw == true){MiMAJfIxUw = false;}
      if(dtxjnquAHf == true){dtxjnquAHf = false;}
      if(lEHjubzJAr == true){lEHjubzJAr = false;}
      if(jxfpyFHqJy == true){jxfpyFHqJy = false;}
      if(MbABIQpnWi == true){MbABIQpnWi = false;}
      if(edhheIabEh == true){edhheIabEh = false;}
      if(fywcLgOGlh == true){fywcLgOGlh = false;}
      if(iEpJTKEGbe == true){iEpJTKEGbe = false;}
      if(kLlRMGPxLo == true){kLlRMGPxLo = false;}
      if(eflbRNeWpb == true){eflbRNeWpb = false;}
      if(BjBnzamYOU == true){BjBnzamYOU = false;}
      if(EUAZwUMeQE == true){EUAZwUMeQE = false;}
      if(RRuxDDROqF == true){RRuxDDROqF = false;}
      if(egPzdBKySk == true){egPzdBKySk = false;}
      if(TqipkJfMex == true){TqipkJfMex = false;}
      if(BAGlKjnEkw == true){BAGlKjnEkw = false;}
      if(JYgIoWFAwt == true){JYgIoWFAwt = false;}
      if(KNLejZhELt == true){KNLejZhELt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YJYAWLUPVE
{ 
  void DDArTOFSgp()
  { 
      bool qUjwWTHVNZ = false;
      bool ZnIVhhBFBD = false;
      bool jOkiXXfDhi = false;
      bool hfbTgpkxsM = false;
      bool IWkKapmwGE = false;
      bool saRHjbiBXz = false;
      bool mDmdrsLnnq = false;
      bool xDMotNdaHh = false;
      bool jiwdpHOUjF = false;
      bool GiYsYEjGSh = false;
      bool dzIPGoNcMW = false;
      bool xItpODGInk = false;
      bool eqEhjNeSPo = false;
      bool cWHZDkagWA = false;
      bool skHNHxnidV = false;
      bool xaShCltaes = false;
      bool KtNXsaBUld = false;
      bool cZlmqsiqZl = false;
      bool YwntqCEZWQ = false;
      bool pzBdpzXiUg = false;
      string pIQYVDhbyC;
      string RcdRrPNBEC;
      string bmFlMTNnVB;
      string ITswQJVqFs;
      string YhzFEKXkFq;
      string PgnKfCCeMB;
      string otGwtxigAi;
      string tVuKdsmAgB;
      string uciekafhQN;
      string GpeDDdbCKG;
      string aqjVxtlcgl;
      string OCxKGMLaLT;
      string RBQmbDpqGz;
      string RkoaaEsMhp;
      string oCBdyDrUxq;
      string SAqqoZZwts;
      string EtVhTdMWjB;
      string TzrUdOzlnY;
      string LVsPfQsykB;
      string dwSoltgTKU;
      if(pIQYVDhbyC == aqjVxtlcgl){qUjwWTHVNZ = true;}
      else if(aqjVxtlcgl == pIQYVDhbyC){dzIPGoNcMW = true;}
      if(RcdRrPNBEC == OCxKGMLaLT){ZnIVhhBFBD = true;}
      else if(OCxKGMLaLT == RcdRrPNBEC){xItpODGInk = true;}
      if(bmFlMTNnVB == RBQmbDpqGz){jOkiXXfDhi = true;}
      else if(RBQmbDpqGz == bmFlMTNnVB){eqEhjNeSPo = true;}
      if(ITswQJVqFs == RkoaaEsMhp){hfbTgpkxsM = true;}
      else if(RkoaaEsMhp == ITswQJVqFs){cWHZDkagWA = true;}
      if(YhzFEKXkFq == oCBdyDrUxq){IWkKapmwGE = true;}
      else if(oCBdyDrUxq == YhzFEKXkFq){skHNHxnidV = true;}
      if(PgnKfCCeMB == SAqqoZZwts){saRHjbiBXz = true;}
      else if(SAqqoZZwts == PgnKfCCeMB){xaShCltaes = true;}
      if(otGwtxigAi == EtVhTdMWjB){mDmdrsLnnq = true;}
      else if(EtVhTdMWjB == otGwtxigAi){KtNXsaBUld = true;}
      if(tVuKdsmAgB == TzrUdOzlnY){xDMotNdaHh = true;}
      if(uciekafhQN == LVsPfQsykB){jiwdpHOUjF = true;}
      if(GpeDDdbCKG == dwSoltgTKU){GiYsYEjGSh = true;}
      while(TzrUdOzlnY == tVuKdsmAgB){cZlmqsiqZl = true;}
      while(LVsPfQsykB == LVsPfQsykB){YwntqCEZWQ = true;}
      while(dwSoltgTKU == dwSoltgTKU){pzBdpzXiUg = true;}
      if(qUjwWTHVNZ == true){qUjwWTHVNZ = false;}
      if(ZnIVhhBFBD == true){ZnIVhhBFBD = false;}
      if(jOkiXXfDhi == true){jOkiXXfDhi = false;}
      if(hfbTgpkxsM == true){hfbTgpkxsM = false;}
      if(IWkKapmwGE == true){IWkKapmwGE = false;}
      if(saRHjbiBXz == true){saRHjbiBXz = false;}
      if(mDmdrsLnnq == true){mDmdrsLnnq = false;}
      if(xDMotNdaHh == true){xDMotNdaHh = false;}
      if(jiwdpHOUjF == true){jiwdpHOUjF = false;}
      if(GiYsYEjGSh == true){GiYsYEjGSh = false;}
      if(dzIPGoNcMW == true){dzIPGoNcMW = false;}
      if(xItpODGInk == true){xItpODGInk = false;}
      if(eqEhjNeSPo == true){eqEhjNeSPo = false;}
      if(cWHZDkagWA == true){cWHZDkagWA = false;}
      if(skHNHxnidV == true){skHNHxnidV = false;}
      if(xaShCltaes == true){xaShCltaes = false;}
      if(KtNXsaBUld == true){KtNXsaBUld = false;}
      if(cZlmqsiqZl == true){cZlmqsiqZl = false;}
      if(YwntqCEZWQ == true){YwntqCEZWQ = false;}
      if(pzBdpzXiUg == true){pzBdpzXiUg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TIGARWAYSY
{ 
  void BDWmIYidIU()
  { 
      bool uOVmEkcZRY = false;
      bool FFnjobTlfl = false;
      bool AcYSwerXzQ = false;
      bool FabndKLssE = false;
      bool XnKlFGcFQS = false;
      bool waepNRoCqY = false;
      bool sEaBSedAGd = false;
      bool PasaNMSmNo = false;
      bool ClHfUdukaL = false;
      bool UJCULSMJSa = false;
      bool cczlCUhEbB = false;
      bool zBoBWHxufo = false;
      bool jrZtIGYYPt = false;
      bool zITlMYmUcz = false;
      bool wpIYLTTAyE = false;
      bool VRddqjDEcu = false;
      bool wJogBqgCnx = false;
      bool TcRfssiAho = false;
      bool mXZLYgdpub = false;
      bool UhqgClBbXU = false;
      string TgSwhuHwpT;
      string UoqiNodCzg;
      string NSUTEFJmuu;
      string ZWGNbyhUBs;
      string VDPrIrGdBq;
      string zeorDALyqb;
      string kTAusyhcHO;
      string HJBGLJCbLM;
      string yflDutgOJa;
      string ljcYHBCTzJ;
      string KcWljpcigt;
      string xjledFhwzz;
      string RTTfbWfbyK;
      string GicCBUIzSF;
      string RyhPcCyyuB;
      string TGUzrqJqJN;
      string JAjVmOGjcI;
      string xhcthTlECZ;
      string YggxpANcKK;
      string LRpFuQNLcO;
      if(TgSwhuHwpT == KcWljpcigt){uOVmEkcZRY = true;}
      else if(KcWljpcigt == TgSwhuHwpT){cczlCUhEbB = true;}
      if(UoqiNodCzg == xjledFhwzz){FFnjobTlfl = true;}
      else if(xjledFhwzz == UoqiNodCzg){zBoBWHxufo = true;}
      if(NSUTEFJmuu == RTTfbWfbyK){AcYSwerXzQ = true;}
      else if(RTTfbWfbyK == NSUTEFJmuu){jrZtIGYYPt = true;}
      if(ZWGNbyhUBs == GicCBUIzSF){FabndKLssE = true;}
      else if(GicCBUIzSF == ZWGNbyhUBs){zITlMYmUcz = true;}
      if(VDPrIrGdBq == RyhPcCyyuB){XnKlFGcFQS = true;}
      else if(RyhPcCyyuB == VDPrIrGdBq){wpIYLTTAyE = true;}
      if(zeorDALyqb == TGUzrqJqJN){waepNRoCqY = true;}
      else if(TGUzrqJqJN == zeorDALyqb){VRddqjDEcu = true;}
      if(kTAusyhcHO == JAjVmOGjcI){sEaBSedAGd = true;}
      else if(JAjVmOGjcI == kTAusyhcHO){wJogBqgCnx = true;}
      if(HJBGLJCbLM == xhcthTlECZ){PasaNMSmNo = true;}
      if(yflDutgOJa == YggxpANcKK){ClHfUdukaL = true;}
      if(ljcYHBCTzJ == LRpFuQNLcO){UJCULSMJSa = true;}
      while(xhcthTlECZ == HJBGLJCbLM){TcRfssiAho = true;}
      while(YggxpANcKK == YggxpANcKK){mXZLYgdpub = true;}
      while(LRpFuQNLcO == LRpFuQNLcO){UhqgClBbXU = true;}
      if(uOVmEkcZRY == true){uOVmEkcZRY = false;}
      if(FFnjobTlfl == true){FFnjobTlfl = false;}
      if(AcYSwerXzQ == true){AcYSwerXzQ = false;}
      if(FabndKLssE == true){FabndKLssE = false;}
      if(XnKlFGcFQS == true){XnKlFGcFQS = false;}
      if(waepNRoCqY == true){waepNRoCqY = false;}
      if(sEaBSedAGd == true){sEaBSedAGd = false;}
      if(PasaNMSmNo == true){PasaNMSmNo = false;}
      if(ClHfUdukaL == true){ClHfUdukaL = false;}
      if(UJCULSMJSa == true){UJCULSMJSa = false;}
      if(cczlCUhEbB == true){cczlCUhEbB = false;}
      if(zBoBWHxufo == true){zBoBWHxufo = false;}
      if(jrZtIGYYPt == true){jrZtIGYYPt = false;}
      if(zITlMYmUcz == true){zITlMYmUcz = false;}
      if(wpIYLTTAyE == true){wpIYLTTAyE = false;}
      if(VRddqjDEcu == true){VRddqjDEcu = false;}
      if(wJogBqgCnx == true){wJogBqgCnx = false;}
      if(TcRfssiAho == true){TcRfssiAho = false;}
      if(mXZLYgdpub == true){mXZLYgdpub = false;}
      if(UhqgClBbXU == true){UhqgClBbXU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESZIUABZLV
{ 
  void fEkLQctQjI()
  { 
      bool ohCRhJEtSq = false;
      bool nuIEFmsMMu = false;
      bool hBSowmGTJk = false;
      bool ruVVLbZgwn = false;
      bool SictDwLNzq = false;
      bool zEkibnPMUu = false;
      bool CjkhzrYmsc = false;
      bool MMPXcyXXkA = false;
      bool arURknJmtX = false;
      bool MNLBkhyttK = false;
      bool XYUVdmnNGc = false;
      bool PqaUTKPSwL = false;
      bool hksVPzANlt = false;
      bool AdcacCXyny = false;
      bool zwfRHVlqha = false;
      bool RfxiblfzGd = false;
      bool lZaLclNAqQ = false;
      bool lRdyLlFaNt = false;
      bool NJfKbTftyq = false;
      bool WYrJLYUUoU = false;
      string pHSLKKptzU;
      string FHcnkEFjIK;
      string VrNSwypZTw;
      string VPFKqVdEuc;
      string wxRJKlOnIm;
      string bmrFrxsAPM;
      string UPZCypCRwO;
      string aAneNXZEHJ;
      string jBRgUiWASs;
      string bdoiIgWOLU;
      string jwqsMayNqT;
      string WorGbSysgO;
      string SCzCmwLFVg;
      string BLrmZnKYUt;
      string kJIyVlliGp;
      string icgwBhwoFP;
      string PrrKSLxEgn;
      string IYYmcJsBfA;
      string KbzeyXdwlq;
      string qUSEdrQyeK;
      if(pHSLKKptzU == jwqsMayNqT){ohCRhJEtSq = true;}
      else if(jwqsMayNqT == pHSLKKptzU){XYUVdmnNGc = true;}
      if(FHcnkEFjIK == WorGbSysgO){nuIEFmsMMu = true;}
      else if(WorGbSysgO == FHcnkEFjIK){PqaUTKPSwL = true;}
      if(VrNSwypZTw == SCzCmwLFVg){hBSowmGTJk = true;}
      else if(SCzCmwLFVg == VrNSwypZTw){hksVPzANlt = true;}
      if(VPFKqVdEuc == BLrmZnKYUt){ruVVLbZgwn = true;}
      else if(BLrmZnKYUt == VPFKqVdEuc){AdcacCXyny = true;}
      if(wxRJKlOnIm == kJIyVlliGp){SictDwLNzq = true;}
      else if(kJIyVlliGp == wxRJKlOnIm){zwfRHVlqha = true;}
      if(bmrFrxsAPM == icgwBhwoFP){zEkibnPMUu = true;}
      else if(icgwBhwoFP == bmrFrxsAPM){RfxiblfzGd = true;}
      if(UPZCypCRwO == PrrKSLxEgn){CjkhzrYmsc = true;}
      else if(PrrKSLxEgn == UPZCypCRwO){lZaLclNAqQ = true;}
      if(aAneNXZEHJ == IYYmcJsBfA){MMPXcyXXkA = true;}
      if(jBRgUiWASs == KbzeyXdwlq){arURknJmtX = true;}
      if(bdoiIgWOLU == qUSEdrQyeK){MNLBkhyttK = true;}
      while(IYYmcJsBfA == aAneNXZEHJ){lRdyLlFaNt = true;}
      while(KbzeyXdwlq == KbzeyXdwlq){NJfKbTftyq = true;}
      while(qUSEdrQyeK == qUSEdrQyeK){WYrJLYUUoU = true;}
      if(ohCRhJEtSq == true){ohCRhJEtSq = false;}
      if(nuIEFmsMMu == true){nuIEFmsMMu = false;}
      if(hBSowmGTJk == true){hBSowmGTJk = false;}
      if(ruVVLbZgwn == true){ruVVLbZgwn = false;}
      if(SictDwLNzq == true){SictDwLNzq = false;}
      if(zEkibnPMUu == true){zEkibnPMUu = false;}
      if(CjkhzrYmsc == true){CjkhzrYmsc = false;}
      if(MMPXcyXXkA == true){MMPXcyXXkA = false;}
      if(arURknJmtX == true){arURknJmtX = false;}
      if(MNLBkhyttK == true){MNLBkhyttK = false;}
      if(XYUVdmnNGc == true){XYUVdmnNGc = false;}
      if(PqaUTKPSwL == true){PqaUTKPSwL = false;}
      if(hksVPzANlt == true){hksVPzANlt = false;}
      if(AdcacCXyny == true){AdcacCXyny = false;}
      if(zwfRHVlqha == true){zwfRHVlqha = false;}
      if(RfxiblfzGd == true){RfxiblfzGd = false;}
      if(lZaLclNAqQ == true){lZaLclNAqQ = false;}
      if(lRdyLlFaNt == true){lRdyLlFaNt = false;}
      if(NJfKbTftyq == true){NJfKbTftyq = false;}
      if(WYrJLYUUoU == true){WYrJLYUUoU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XWBTMKCCTP
{ 
  void gtPFMSsGFy()
  { 
      bool ooVVBWPMMF = false;
      bool mzdHOUtSxP = false;
      bool OFJMRYtiJD = false;
      bool IqEQKAosYC = false;
      bool YkwxasKHFh = false;
      bool hxGHNjeIDb = false;
      bool bgDIxwuNxO = false;
      bool fBsuqdJMlX = false;
      bool OmcbVLjwCZ = false;
      bool UfoxZqhmze = false;
      bool yxJqCgDLQj = false;
      bool ZSWfNoDalk = false;
      bool LyKWszLwUz = false;
      bool wVMGZQclZo = false;
      bool IYfRABJJik = false;
      bool mGBOSzmmxC = false;
      bool UGpQnEGPFw = false;
      bool MRBxcmRrWr = false;
      bool pCNjLoUxnZ = false;
      bool dpnWTBhOdw = false;
      string zDVQxffuzL;
      string qlrHOTdzYB;
      string qYchnSiPAk;
      string DOIBzshzqo;
      string eohRojTOgg;
      string QNTBOaZmcd;
      string xPtOHbdpHV;
      string kdIiWCqKsD;
      string yUhTTptGmY;
      string StWMrOtTJM;
      string GdGKulEjeL;
      string jOsYfbhatR;
      string hWCiDqHuqH;
      string HWAgxUNWXg;
      string kJbaoDBxgP;
      string gSZrdiaXHE;
      string eJsXEMNMbL;
      string OKDMfYuasz;
      string oKOaZnxICO;
      string soPTCbPEWc;
      if(zDVQxffuzL == GdGKulEjeL){ooVVBWPMMF = true;}
      else if(GdGKulEjeL == zDVQxffuzL){yxJqCgDLQj = true;}
      if(qlrHOTdzYB == jOsYfbhatR){mzdHOUtSxP = true;}
      else if(jOsYfbhatR == qlrHOTdzYB){ZSWfNoDalk = true;}
      if(qYchnSiPAk == hWCiDqHuqH){OFJMRYtiJD = true;}
      else if(hWCiDqHuqH == qYchnSiPAk){LyKWszLwUz = true;}
      if(DOIBzshzqo == HWAgxUNWXg){IqEQKAosYC = true;}
      else if(HWAgxUNWXg == DOIBzshzqo){wVMGZQclZo = true;}
      if(eohRojTOgg == kJbaoDBxgP){YkwxasKHFh = true;}
      else if(kJbaoDBxgP == eohRojTOgg){IYfRABJJik = true;}
      if(QNTBOaZmcd == gSZrdiaXHE){hxGHNjeIDb = true;}
      else if(gSZrdiaXHE == QNTBOaZmcd){mGBOSzmmxC = true;}
      if(xPtOHbdpHV == eJsXEMNMbL){bgDIxwuNxO = true;}
      else if(eJsXEMNMbL == xPtOHbdpHV){UGpQnEGPFw = true;}
      if(kdIiWCqKsD == OKDMfYuasz){fBsuqdJMlX = true;}
      if(yUhTTptGmY == oKOaZnxICO){OmcbVLjwCZ = true;}
      if(StWMrOtTJM == soPTCbPEWc){UfoxZqhmze = true;}
      while(OKDMfYuasz == kdIiWCqKsD){MRBxcmRrWr = true;}
      while(oKOaZnxICO == oKOaZnxICO){pCNjLoUxnZ = true;}
      while(soPTCbPEWc == soPTCbPEWc){dpnWTBhOdw = true;}
      if(ooVVBWPMMF == true){ooVVBWPMMF = false;}
      if(mzdHOUtSxP == true){mzdHOUtSxP = false;}
      if(OFJMRYtiJD == true){OFJMRYtiJD = false;}
      if(IqEQKAosYC == true){IqEQKAosYC = false;}
      if(YkwxasKHFh == true){YkwxasKHFh = false;}
      if(hxGHNjeIDb == true){hxGHNjeIDb = false;}
      if(bgDIxwuNxO == true){bgDIxwuNxO = false;}
      if(fBsuqdJMlX == true){fBsuqdJMlX = false;}
      if(OmcbVLjwCZ == true){OmcbVLjwCZ = false;}
      if(UfoxZqhmze == true){UfoxZqhmze = false;}
      if(yxJqCgDLQj == true){yxJqCgDLQj = false;}
      if(ZSWfNoDalk == true){ZSWfNoDalk = false;}
      if(LyKWszLwUz == true){LyKWszLwUz = false;}
      if(wVMGZQclZo == true){wVMGZQclZo = false;}
      if(IYfRABJJik == true){IYfRABJJik = false;}
      if(mGBOSzmmxC == true){mGBOSzmmxC = false;}
      if(UGpQnEGPFw == true){UGpQnEGPFw = false;}
      if(MRBxcmRrWr == true){MRBxcmRrWr = false;}
      if(pCNjLoUxnZ == true){pCNjLoUxnZ = false;}
      if(dpnWTBhOdw == true){dpnWTBhOdw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJPLBPXSGZ
{ 
  void xLkxPSyVEu()
  { 
      bool hSOpLTpAWM = false;
      bool KYaBWwWrAJ = false;
      bool seqSPQJADg = false;
      bool GJCxeHoTNo = false;
      bool lsUrWTVOaG = false;
      bool ddbwECawat = false;
      bool KowoFAVcWP = false;
      bool HDdKXAKyuu = false;
      bool tuZxDcgFrb = false;
      bool frrTewxemV = false;
      bool yrqKzZzQYE = false;
      bool rbAfzPPzlb = false;
      bool TQjuiOKKea = false;
      bool DeLZxCDOxc = false;
      bool dPgniDrMTP = false;
      bool gxsKCgHwbk = false;
      bool PokyBMQZhx = false;
      bool MBCIyDjwLe = false;
      bool VxpPtFlAXP = false;
      bool tGlLMndhmV = false;
      string RxQUowlwWq;
      string zsunhqcWXR;
      string LLSassnXSt;
      string FdTxfyuTeQ;
      string NMtEbthNOi;
      string ZhYSBFdpbu;
      string IOdclVZxHj;
      string uJrHDzRNzy;
      string LZJiTWFBuZ;
      string TFqiHzhQSF;
      string UjFdmQpQOC;
      string nQpcjhEtJO;
      string QYBhPoRIzE;
      string QAutdaUeuC;
      string gnlrlDOOzZ;
      string tnHDowhWOx;
      string zgRKlmVwzI;
      string NZyGgclJwM;
      string aDJZJbsqEg;
      string sxQyDAVbGy;
      if(RxQUowlwWq == UjFdmQpQOC){hSOpLTpAWM = true;}
      else if(UjFdmQpQOC == RxQUowlwWq){yrqKzZzQYE = true;}
      if(zsunhqcWXR == nQpcjhEtJO){KYaBWwWrAJ = true;}
      else if(nQpcjhEtJO == zsunhqcWXR){rbAfzPPzlb = true;}
      if(LLSassnXSt == QYBhPoRIzE){seqSPQJADg = true;}
      else if(QYBhPoRIzE == LLSassnXSt){TQjuiOKKea = true;}
      if(FdTxfyuTeQ == QAutdaUeuC){GJCxeHoTNo = true;}
      else if(QAutdaUeuC == FdTxfyuTeQ){DeLZxCDOxc = true;}
      if(NMtEbthNOi == gnlrlDOOzZ){lsUrWTVOaG = true;}
      else if(gnlrlDOOzZ == NMtEbthNOi){dPgniDrMTP = true;}
      if(ZhYSBFdpbu == tnHDowhWOx){ddbwECawat = true;}
      else if(tnHDowhWOx == ZhYSBFdpbu){gxsKCgHwbk = true;}
      if(IOdclVZxHj == zgRKlmVwzI){KowoFAVcWP = true;}
      else if(zgRKlmVwzI == IOdclVZxHj){PokyBMQZhx = true;}
      if(uJrHDzRNzy == NZyGgclJwM){HDdKXAKyuu = true;}
      if(LZJiTWFBuZ == aDJZJbsqEg){tuZxDcgFrb = true;}
      if(TFqiHzhQSF == sxQyDAVbGy){frrTewxemV = true;}
      while(NZyGgclJwM == uJrHDzRNzy){MBCIyDjwLe = true;}
      while(aDJZJbsqEg == aDJZJbsqEg){VxpPtFlAXP = true;}
      while(sxQyDAVbGy == sxQyDAVbGy){tGlLMndhmV = true;}
      if(hSOpLTpAWM == true){hSOpLTpAWM = false;}
      if(KYaBWwWrAJ == true){KYaBWwWrAJ = false;}
      if(seqSPQJADg == true){seqSPQJADg = false;}
      if(GJCxeHoTNo == true){GJCxeHoTNo = false;}
      if(lsUrWTVOaG == true){lsUrWTVOaG = false;}
      if(ddbwECawat == true){ddbwECawat = false;}
      if(KowoFAVcWP == true){KowoFAVcWP = false;}
      if(HDdKXAKyuu == true){HDdKXAKyuu = false;}
      if(tuZxDcgFrb == true){tuZxDcgFrb = false;}
      if(frrTewxemV == true){frrTewxemV = false;}
      if(yrqKzZzQYE == true){yrqKzZzQYE = false;}
      if(rbAfzPPzlb == true){rbAfzPPzlb = false;}
      if(TQjuiOKKea == true){TQjuiOKKea = false;}
      if(DeLZxCDOxc == true){DeLZxCDOxc = false;}
      if(dPgniDrMTP == true){dPgniDrMTP = false;}
      if(gxsKCgHwbk == true){gxsKCgHwbk = false;}
      if(PokyBMQZhx == true){PokyBMQZhx = false;}
      if(MBCIyDjwLe == true){MBCIyDjwLe = false;}
      if(VxpPtFlAXP == true){VxpPtFlAXP = false;}
      if(tGlLMndhmV == true){tGlLMndhmV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGBGGSHNOT
{ 
  void DxXcBxDOVS()
  { 
      bool sHFVqSKuWk = false;
      bool mSCFxwOYHO = false;
      bool RsQMYJJQba = false;
      bool wUpHiPiNdS = false;
      bool kVBzydWsYy = false;
      bool EwBjozprxh = false;
      bool JtSunSctWg = false;
      bool NAtocwrRNt = false;
      bool lPqcVzSFSi = false;
      bool ZpQuIpCFKf = false;
      bool BcWqkDBMHs = false;
      bool HYeDwtDpYo = false;
      bool zXbmHWjzfl = false;
      bool slGhsJszrR = false;
      bool xGyYbALNzO = false;
      bool mMgUfcAijN = false;
      bool TCgUzURxJl = false;
      bool BDxGrsZCKG = false;
      bool LWzRzfFkBP = false;
      bool JJPdytYcYH = false;
      string IwGLVXQuBk;
      string grGmzlTHdp;
      string VlRuBhoYXn;
      string YryqbwISIh;
      string JzhtXtUeWe;
      string ealmbVeLKn;
      string iqWMMnsOKD;
      string dByufWEXWG;
      string MKBrJxGKPG;
      string RxIUzSbUhj;
      string BGUTBccpHF;
      string RHnEbYpdDP;
      string hhyDlfrcwN;
      string tipmFFpgqf;
      string TPDJoKIErZ;
      string byRRCSHQhU;
      string kztsKhRBzV;
      string iImWuReoOb;
      string WnjVlwQXjl;
      string xYzWuTVJzG;
      if(IwGLVXQuBk == BGUTBccpHF){sHFVqSKuWk = true;}
      else if(BGUTBccpHF == IwGLVXQuBk){BcWqkDBMHs = true;}
      if(grGmzlTHdp == RHnEbYpdDP){mSCFxwOYHO = true;}
      else if(RHnEbYpdDP == grGmzlTHdp){HYeDwtDpYo = true;}
      if(VlRuBhoYXn == hhyDlfrcwN){RsQMYJJQba = true;}
      else if(hhyDlfrcwN == VlRuBhoYXn){zXbmHWjzfl = true;}
      if(YryqbwISIh == tipmFFpgqf){wUpHiPiNdS = true;}
      else if(tipmFFpgqf == YryqbwISIh){slGhsJszrR = true;}
      if(JzhtXtUeWe == TPDJoKIErZ){kVBzydWsYy = true;}
      else if(TPDJoKIErZ == JzhtXtUeWe){xGyYbALNzO = true;}
      if(ealmbVeLKn == byRRCSHQhU){EwBjozprxh = true;}
      else if(byRRCSHQhU == ealmbVeLKn){mMgUfcAijN = true;}
      if(iqWMMnsOKD == kztsKhRBzV){JtSunSctWg = true;}
      else if(kztsKhRBzV == iqWMMnsOKD){TCgUzURxJl = true;}
      if(dByufWEXWG == iImWuReoOb){NAtocwrRNt = true;}
      if(MKBrJxGKPG == WnjVlwQXjl){lPqcVzSFSi = true;}
      if(RxIUzSbUhj == xYzWuTVJzG){ZpQuIpCFKf = true;}
      while(iImWuReoOb == dByufWEXWG){BDxGrsZCKG = true;}
      while(WnjVlwQXjl == WnjVlwQXjl){LWzRzfFkBP = true;}
      while(xYzWuTVJzG == xYzWuTVJzG){JJPdytYcYH = true;}
      if(sHFVqSKuWk == true){sHFVqSKuWk = false;}
      if(mSCFxwOYHO == true){mSCFxwOYHO = false;}
      if(RsQMYJJQba == true){RsQMYJJQba = false;}
      if(wUpHiPiNdS == true){wUpHiPiNdS = false;}
      if(kVBzydWsYy == true){kVBzydWsYy = false;}
      if(EwBjozprxh == true){EwBjozprxh = false;}
      if(JtSunSctWg == true){JtSunSctWg = false;}
      if(NAtocwrRNt == true){NAtocwrRNt = false;}
      if(lPqcVzSFSi == true){lPqcVzSFSi = false;}
      if(ZpQuIpCFKf == true){ZpQuIpCFKf = false;}
      if(BcWqkDBMHs == true){BcWqkDBMHs = false;}
      if(HYeDwtDpYo == true){HYeDwtDpYo = false;}
      if(zXbmHWjzfl == true){zXbmHWjzfl = false;}
      if(slGhsJszrR == true){slGhsJszrR = false;}
      if(xGyYbALNzO == true){xGyYbALNzO = false;}
      if(mMgUfcAijN == true){mMgUfcAijN = false;}
      if(TCgUzURxJl == true){TCgUzURxJl = false;}
      if(BDxGrsZCKG == true){BDxGrsZCKG = false;}
      if(LWzRzfFkBP == true){LWzRzfFkBP = false;}
      if(JJPdytYcYH == true){JJPdytYcYH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WRZUCJBPCX
{ 
  void MUPyUVjMbf()
  { 
      bool faKZVUymqF = false;
      bool eiEobfpSro = false;
      bool PPyWaUmiMM = false;
      bool dThTPKtcuU = false;
      bool OeXOsBANrT = false;
      bool BxYcEQbmzA = false;
      bool hOZeaKBjYQ = false;
      bool lNWWZkqidY = false;
      bool UYqsLgtFPz = false;
      bool hGctmzEsmh = false;
      bool APoahnZCCT = false;
      bool YsJaeIXgTt = false;
      bool PuUZiejbja = false;
      bool fywuXFjPLW = false;
      bool HrDuaoxCPd = false;
      bool aXZsSEtOrC = false;
      bool DxRbnZwOCZ = false;
      bool YIUwmXrZyt = false;
      bool hhMFzHXDcS = false;
      bool LUWITJZbHA = false;
      string PaoAEjCfIS;
      string MrUaCkRnMy;
      string wunrXtYnXc;
      string LXRJapbRdf;
      string FtdrfeRmFA;
      string wrceUTmxcK;
      string KNHeHnZKzL;
      string IAJgsBRuLs;
      string clhXgSumnG;
      string DeoTUqlyjr;
      string EGmtqwhwkS;
      string CqkjhYejyn;
      string smVsIdKoMC;
      string PSLSnVyngk;
      string jzBVELsFlu;
      string LBAuzQjtkM;
      string ksiiDifRuL;
      string ZpDMEslAow;
      string kEDQpNSPTX;
      string kEDTzqPRRU;
      if(PaoAEjCfIS == EGmtqwhwkS){faKZVUymqF = true;}
      else if(EGmtqwhwkS == PaoAEjCfIS){APoahnZCCT = true;}
      if(MrUaCkRnMy == CqkjhYejyn){eiEobfpSro = true;}
      else if(CqkjhYejyn == MrUaCkRnMy){YsJaeIXgTt = true;}
      if(wunrXtYnXc == smVsIdKoMC){PPyWaUmiMM = true;}
      else if(smVsIdKoMC == wunrXtYnXc){PuUZiejbja = true;}
      if(LXRJapbRdf == PSLSnVyngk){dThTPKtcuU = true;}
      else if(PSLSnVyngk == LXRJapbRdf){fywuXFjPLW = true;}
      if(FtdrfeRmFA == jzBVELsFlu){OeXOsBANrT = true;}
      else if(jzBVELsFlu == FtdrfeRmFA){HrDuaoxCPd = true;}
      if(wrceUTmxcK == LBAuzQjtkM){BxYcEQbmzA = true;}
      else if(LBAuzQjtkM == wrceUTmxcK){aXZsSEtOrC = true;}
      if(KNHeHnZKzL == ksiiDifRuL){hOZeaKBjYQ = true;}
      else if(ksiiDifRuL == KNHeHnZKzL){DxRbnZwOCZ = true;}
      if(IAJgsBRuLs == ZpDMEslAow){lNWWZkqidY = true;}
      if(clhXgSumnG == kEDQpNSPTX){UYqsLgtFPz = true;}
      if(DeoTUqlyjr == kEDTzqPRRU){hGctmzEsmh = true;}
      while(ZpDMEslAow == IAJgsBRuLs){YIUwmXrZyt = true;}
      while(kEDQpNSPTX == kEDQpNSPTX){hhMFzHXDcS = true;}
      while(kEDTzqPRRU == kEDTzqPRRU){LUWITJZbHA = true;}
      if(faKZVUymqF == true){faKZVUymqF = false;}
      if(eiEobfpSro == true){eiEobfpSro = false;}
      if(PPyWaUmiMM == true){PPyWaUmiMM = false;}
      if(dThTPKtcuU == true){dThTPKtcuU = false;}
      if(OeXOsBANrT == true){OeXOsBANrT = false;}
      if(BxYcEQbmzA == true){BxYcEQbmzA = false;}
      if(hOZeaKBjYQ == true){hOZeaKBjYQ = false;}
      if(lNWWZkqidY == true){lNWWZkqidY = false;}
      if(UYqsLgtFPz == true){UYqsLgtFPz = false;}
      if(hGctmzEsmh == true){hGctmzEsmh = false;}
      if(APoahnZCCT == true){APoahnZCCT = false;}
      if(YsJaeIXgTt == true){YsJaeIXgTt = false;}
      if(PuUZiejbja == true){PuUZiejbja = false;}
      if(fywuXFjPLW == true){fywuXFjPLW = false;}
      if(HrDuaoxCPd == true){HrDuaoxCPd = false;}
      if(aXZsSEtOrC == true){aXZsSEtOrC = false;}
      if(DxRbnZwOCZ == true){DxRbnZwOCZ = false;}
      if(YIUwmXrZyt == true){YIUwmXrZyt = false;}
      if(hhMFzHXDcS == true){hhMFzHXDcS = false;}
      if(LUWITJZbHA == true){LUWITJZbHA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SZGHDYLUGD
{ 
  void iAHAcbHwza()
  { 
      bool JsByaqDgIM = false;
      bool eCgysYGMnV = false;
      bool RxKJRrMYpN = false;
      bool kdnNQBfGDE = false;
      bool mXLSuDWTQX = false;
      bool SjOtlLirgh = false;
      bool eepubANThr = false;
      bool sAIjhtkqNO = false;
      bool VrHRtAOsaE = false;
      bool RmZUYIgQpt = false;
      bool pDkYeSaeMr = false;
      bool ZqdSLmXYBa = false;
      bool lTrdZFZnKY = false;
      bool MUBTXSGhma = false;
      bool ZjgidaJHIl = false;
      bool kIOOIVKHzY = false;
      bool smTmeFpKts = false;
      bool fokZBBmJzy = false;
      bool wReXnEFlKB = false;
      bool IyhNhlPsDY = false;
      string sqCsnfzHCJ;
      string sRMGCbUjly;
      string PPRAHypJJf;
      string FtHJwmAtyN;
      string kRgbMptyps;
      string BbPQncZClo;
      string ppyVEyKDJO;
      string aalYNyiomQ;
      string EqSPecdpUT;
      string MxHIWtTKXN;
      string epnaRapqDp;
      string tjOVkzXhqa;
      string TTipCdTcBS;
      string dXRYkNCryD;
      string mlmdZbilWX;
      string WlTwtLHyYn;
      string GMpjMVSojX;
      string xeimmggFQZ;
      string thFdwqEUeZ;
      string FESKxZwCQD;
      if(sqCsnfzHCJ == epnaRapqDp){JsByaqDgIM = true;}
      else if(epnaRapqDp == sqCsnfzHCJ){pDkYeSaeMr = true;}
      if(sRMGCbUjly == tjOVkzXhqa){eCgysYGMnV = true;}
      else if(tjOVkzXhqa == sRMGCbUjly){ZqdSLmXYBa = true;}
      if(PPRAHypJJf == TTipCdTcBS){RxKJRrMYpN = true;}
      else if(TTipCdTcBS == PPRAHypJJf){lTrdZFZnKY = true;}
      if(FtHJwmAtyN == dXRYkNCryD){kdnNQBfGDE = true;}
      else if(dXRYkNCryD == FtHJwmAtyN){MUBTXSGhma = true;}
      if(kRgbMptyps == mlmdZbilWX){mXLSuDWTQX = true;}
      else if(mlmdZbilWX == kRgbMptyps){ZjgidaJHIl = true;}
      if(BbPQncZClo == WlTwtLHyYn){SjOtlLirgh = true;}
      else if(WlTwtLHyYn == BbPQncZClo){kIOOIVKHzY = true;}
      if(ppyVEyKDJO == GMpjMVSojX){eepubANThr = true;}
      else if(GMpjMVSojX == ppyVEyKDJO){smTmeFpKts = true;}
      if(aalYNyiomQ == xeimmggFQZ){sAIjhtkqNO = true;}
      if(EqSPecdpUT == thFdwqEUeZ){VrHRtAOsaE = true;}
      if(MxHIWtTKXN == FESKxZwCQD){RmZUYIgQpt = true;}
      while(xeimmggFQZ == aalYNyiomQ){fokZBBmJzy = true;}
      while(thFdwqEUeZ == thFdwqEUeZ){wReXnEFlKB = true;}
      while(FESKxZwCQD == FESKxZwCQD){IyhNhlPsDY = true;}
      if(JsByaqDgIM == true){JsByaqDgIM = false;}
      if(eCgysYGMnV == true){eCgysYGMnV = false;}
      if(RxKJRrMYpN == true){RxKJRrMYpN = false;}
      if(kdnNQBfGDE == true){kdnNQBfGDE = false;}
      if(mXLSuDWTQX == true){mXLSuDWTQX = false;}
      if(SjOtlLirgh == true){SjOtlLirgh = false;}
      if(eepubANThr == true){eepubANThr = false;}
      if(sAIjhtkqNO == true){sAIjhtkqNO = false;}
      if(VrHRtAOsaE == true){VrHRtAOsaE = false;}
      if(RmZUYIgQpt == true){RmZUYIgQpt = false;}
      if(pDkYeSaeMr == true){pDkYeSaeMr = false;}
      if(ZqdSLmXYBa == true){ZqdSLmXYBa = false;}
      if(lTrdZFZnKY == true){lTrdZFZnKY = false;}
      if(MUBTXSGhma == true){MUBTXSGhma = false;}
      if(ZjgidaJHIl == true){ZjgidaJHIl = false;}
      if(kIOOIVKHzY == true){kIOOIVKHzY = false;}
      if(smTmeFpKts == true){smTmeFpKts = false;}
      if(fokZBBmJzy == true){fokZBBmJzy = false;}
      if(wReXnEFlKB == true){wReXnEFlKB = false;}
      if(IyhNhlPsDY == true){IyhNhlPsDY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PVRADXMNLB
{ 
  void NofwZqzdbx()
  { 
      bool HbXcuHCbfq = false;
      bool EXNPEgVFwG = false;
      bool wrIhrkftDG = false;
      bool NerWAupCtT = false;
      bool iBudNRckcP = false;
      bool IfNDfOSpkJ = false;
      bool aHXYcZepPJ = false;
      bool pTLcWtweUZ = false;
      bool HuRnxhQnpk = false;
      bool cARjrbdVAn = false;
      bool mlVTZoUkgl = false;
      bool RnUKCfojbu = false;
      bool IpAdfoBbju = false;
      bool QadflVZyOI = false;
      bool MfHESoeGgM = false;
      bool lstFfwlqmj = false;
      bool msBkUqJoXg = false;
      bool FpUShbiwKq = false;
      bool KutWJWfXAp = false;
      bool iiLdVTeVia = false;
      string berwmOtBFw;
      string TgUesuHzIz;
      string ESsUBsSHxk;
      string JDgDrXUgCw;
      string jVpTlUwAbg;
      string JnRFrJkXut;
      string wmDUmQAQlU;
      string ZZxLOibZhg;
      string wRfQbVkaLi;
      string lwlIAxRVgV;
      string TfOGGipFqJ;
      string gLpNydHmsQ;
      string eZFChdmoLR;
      string QGrLMPCYKr;
      string ffjCCaGYKV;
      string pecQptZMXc;
      string uBtYrZTdAh;
      string ahbAkzpCzH;
      string XOeobldaUS;
      string ppBhwekKKc;
      if(berwmOtBFw == TfOGGipFqJ){HbXcuHCbfq = true;}
      else if(TfOGGipFqJ == berwmOtBFw){mlVTZoUkgl = true;}
      if(TgUesuHzIz == gLpNydHmsQ){EXNPEgVFwG = true;}
      else if(gLpNydHmsQ == TgUesuHzIz){RnUKCfojbu = true;}
      if(ESsUBsSHxk == eZFChdmoLR){wrIhrkftDG = true;}
      else if(eZFChdmoLR == ESsUBsSHxk){IpAdfoBbju = true;}
      if(JDgDrXUgCw == QGrLMPCYKr){NerWAupCtT = true;}
      else if(QGrLMPCYKr == JDgDrXUgCw){QadflVZyOI = true;}
      if(jVpTlUwAbg == ffjCCaGYKV){iBudNRckcP = true;}
      else if(ffjCCaGYKV == jVpTlUwAbg){MfHESoeGgM = true;}
      if(JnRFrJkXut == pecQptZMXc){IfNDfOSpkJ = true;}
      else if(pecQptZMXc == JnRFrJkXut){lstFfwlqmj = true;}
      if(wmDUmQAQlU == uBtYrZTdAh){aHXYcZepPJ = true;}
      else if(uBtYrZTdAh == wmDUmQAQlU){msBkUqJoXg = true;}
      if(ZZxLOibZhg == ahbAkzpCzH){pTLcWtweUZ = true;}
      if(wRfQbVkaLi == XOeobldaUS){HuRnxhQnpk = true;}
      if(lwlIAxRVgV == ppBhwekKKc){cARjrbdVAn = true;}
      while(ahbAkzpCzH == ZZxLOibZhg){FpUShbiwKq = true;}
      while(XOeobldaUS == XOeobldaUS){KutWJWfXAp = true;}
      while(ppBhwekKKc == ppBhwekKKc){iiLdVTeVia = true;}
      if(HbXcuHCbfq == true){HbXcuHCbfq = false;}
      if(EXNPEgVFwG == true){EXNPEgVFwG = false;}
      if(wrIhrkftDG == true){wrIhrkftDG = false;}
      if(NerWAupCtT == true){NerWAupCtT = false;}
      if(iBudNRckcP == true){iBudNRckcP = false;}
      if(IfNDfOSpkJ == true){IfNDfOSpkJ = false;}
      if(aHXYcZepPJ == true){aHXYcZepPJ = false;}
      if(pTLcWtweUZ == true){pTLcWtweUZ = false;}
      if(HuRnxhQnpk == true){HuRnxhQnpk = false;}
      if(cARjrbdVAn == true){cARjrbdVAn = false;}
      if(mlVTZoUkgl == true){mlVTZoUkgl = false;}
      if(RnUKCfojbu == true){RnUKCfojbu = false;}
      if(IpAdfoBbju == true){IpAdfoBbju = false;}
      if(QadflVZyOI == true){QadflVZyOI = false;}
      if(MfHESoeGgM == true){MfHESoeGgM = false;}
      if(lstFfwlqmj == true){lstFfwlqmj = false;}
      if(msBkUqJoXg == true){msBkUqJoXg = false;}
      if(FpUShbiwKq == true){FpUShbiwKq = false;}
      if(KutWJWfXAp == true){KutWJWfXAp = false;}
      if(iiLdVTeVia == true){iiLdVTeVia = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MDUZHFPAGB
{ 
  void MJikdYiEnx()
  { 
      bool PaJicyfRsq = false;
      bool SOVcZBBBDo = false;
      bool KXlYCHhhsL = false;
      bool kVRnqXQuWj = false;
      bool eSrlfcEBgi = false;
      bool JlqWBqnkgU = false;
      bool QyXgFxwgkC = false;
      bool jGeTKqeAsY = false;
      bool DfBKCzdulA = false;
      bool ifOBSgtLgh = false;
      bool gWPdyDHWMJ = false;
      bool LnrIRjwNeG = false;
      bool SBujTErdAd = false;
      bool wTSKrfQWLz = false;
      bool rGhcntnFji = false;
      bool jgfaPebeKt = false;
      bool KcWiNqVgPk = false;
      bool TYCfOLSSwY = false;
      bool PltRtPnruM = false;
      bool EkMQnOjzOw = false;
      string zxHnutNQei;
      string eehZtbSeqN;
      string eBFWNrrLAm;
      string nNTxhckRMq;
      string lHfYwtUThF;
      string mHMGEyrjaC;
      string BCQquQLjqR;
      string pASAbXUfZS;
      string WXduAfBMsj;
      string kAqJoiqndf;
      string ikcPOloMeg;
      string cLJIfdYVqO;
      string OyqHfoJIKr;
      string fgBtjluNfN;
      string qogMHYqhdL;
      string JVwPQjsViY;
      string cfBlAuJPXt;
      string hLodWZQezG;
      string yaezhKklcz;
      string rZdHjKnuML;
      if(zxHnutNQei == ikcPOloMeg){PaJicyfRsq = true;}
      else if(ikcPOloMeg == zxHnutNQei){gWPdyDHWMJ = true;}
      if(eehZtbSeqN == cLJIfdYVqO){SOVcZBBBDo = true;}
      else if(cLJIfdYVqO == eehZtbSeqN){LnrIRjwNeG = true;}
      if(eBFWNrrLAm == OyqHfoJIKr){KXlYCHhhsL = true;}
      else if(OyqHfoJIKr == eBFWNrrLAm){SBujTErdAd = true;}
      if(nNTxhckRMq == fgBtjluNfN){kVRnqXQuWj = true;}
      else if(fgBtjluNfN == nNTxhckRMq){wTSKrfQWLz = true;}
      if(lHfYwtUThF == qogMHYqhdL){eSrlfcEBgi = true;}
      else if(qogMHYqhdL == lHfYwtUThF){rGhcntnFji = true;}
      if(mHMGEyrjaC == JVwPQjsViY){JlqWBqnkgU = true;}
      else if(JVwPQjsViY == mHMGEyrjaC){jgfaPebeKt = true;}
      if(BCQquQLjqR == cfBlAuJPXt){QyXgFxwgkC = true;}
      else if(cfBlAuJPXt == BCQquQLjqR){KcWiNqVgPk = true;}
      if(pASAbXUfZS == hLodWZQezG){jGeTKqeAsY = true;}
      if(WXduAfBMsj == yaezhKklcz){DfBKCzdulA = true;}
      if(kAqJoiqndf == rZdHjKnuML){ifOBSgtLgh = true;}
      while(hLodWZQezG == pASAbXUfZS){TYCfOLSSwY = true;}
      while(yaezhKklcz == yaezhKklcz){PltRtPnruM = true;}
      while(rZdHjKnuML == rZdHjKnuML){EkMQnOjzOw = true;}
      if(PaJicyfRsq == true){PaJicyfRsq = false;}
      if(SOVcZBBBDo == true){SOVcZBBBDo = false;}
      if(KXlYCHhhsL == true){KXlYCHhhsL = false;}
      if(kVRnqXQuWj == true){kVRnqXQuWj = false;}
      if(eSrlfcEBgi == true){eSrlfcEBgi = false;}
      if(JlqWBqnkgU == true){JlqWBqnkgU = false;}
      if(QyXgFxwgkC == true){QyXgFxwgkC = false;}
      if(jGeTKqeAsY == true){jGeTKqeAsY = false;}
      if(DfBKCzdulA == true){DfBKCzdulA = false;}
      if(ifOBSgtLgh == true){ifOBSgtLgh = false;}
      if(gWPdyDHWMJ == true){gWPdyDHWMJ = false;}
      if(LnrIRjwNeG == true){LnrIRjwNeG = false;}
      if(SBujTErdAd == true){SBujTErdAd = false;}
      if(wTSKrfQWLz == true){wTSKrfQWLz = false;}
      if(rGhcntnFji == true){rGhcntnFji = false;}
      if(jgfaPebeKt == true){jgfaPebeKt = false;}
      if(KcWiNqVgPk == true){KcWiNqVgPk = false;}
      if(TYCfOLSSwY == true){TYCfOLSSwY = false;}
      if(PltRtPnruM == true){PltRtPnruM = false;}
      if(EkMQnOjzOw == true){EkMQnOjzOw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GYLEUFNRDE
{ 
  void JEIRHWlYKN()
  { 
      bool JFGwGjerOi = false;
      bool KTuYMmAmQU = false;
      bool bLliiVxcoU = false;
      bool DKDWoBKqwc = false;
      bool LuGglAqZKB = false;
      bool nilopxSXMk = false;
      bool mBCtfAQYiK = false;
      bool bIqnIfFFwi = false;
      bool dWRmfUYNfr = false;
      bool imdLoKsLAl = false;
      bool iSqzZerxgK = false;
      bool rMadGPiPOK = false;
      bool bDrqbodezy = false;
      bool msEKzKfSNA = false;
      bool cagVzVLAEY = false;
      bool acxoJfazXk = false;
      bool BMyhWzIPdw = false;
      bool iQCOhBVWqF = false;
      bool cdaZWJuOBT = false;
      bool iftbzPbyyA = false;
      string AtQIqWYfcR;
      string tbORScbXNC;
      string qVKUOSORKD;
      string ZnZdlFehdC;
      string HuSDBXAkdh;
      string BUTScdjusY;
      string IHVYrGCjeN;
      string yssLtwDGTq;
      string ScmbBETGBI;
      string VioFtAZsLu;
      string UPGQiIbHYg;
      string ZcbCFeTsWm;
      string lwhWrOEmRt;
      string VKuYVCWWrs;
      string cMhUhrHmzO;
      string gfVYIYhjXU;
      string EnpdKPhCfD;
      string IwBdJZNNnz;
      string HRmCNpnVPx;
      string UmyXnoVDJR;
      if(AtQIqWYfcR == UPGQiIbHYg){JFGwGjerOi = true;}
      else if(UPGQiIbHYg == AtQIqWYfcR){iSqzZerxgK = true;}
      if(tbORScbXNC == ZcbCFeTsWm){KTuYMmAmQU = true;}
      else if(ZcbCFeTsWm == tbORScbXNC){rMadGPiPOK = true;}
      if(qVKUOSORKD == lwhWrOEmRt){bLliiVxcoU = true;}
      else if(lwhWrOEmRt == qVKUOSORKD){bDrqbodezy = true;}
      if(ZnZdlFehdC == VKuYVCWWrs){DKDWoBKqwc = true;}
      else if(VKuYVCWWrs == ZnZdlFehdC){msEKzKfSNA = true;}
      if(HuSDBXAkdh == cMhUhrHmzO){LuGglAqZKB = true;}
      else if(cMhUhrHmzO == HuSDBXAkdh){cagVzVLAEY = true;}
      if(BUTScdjusY == gfVYIYhjXU){nilopxSXMk = true;}
      else if(gfVYIYhjXU == BUTScdjusY){acxoJfazXk = true;}
      if(IHVYrGCjeN == EnpdKPhCfD){mBCtfAQYiK = true;}
      else if(EnpdKPhCfD == IHVYrGCjeN){BMyhWzIPdw = true;}
      if(yssLtwDGTq == IwBdJZNNnz){bIqnIfFFwi = true;}
      if(ScmbBETGBI == HRmCNpnVPx){dWRmfUYNfr = true;}
      if(VioFtAZsLu == UmyXnoVDJR){imdLoKsLAl = true;}
      while(IwBdJZNNnz == yssLtwDGTq){iQCOhBVWqF = true;}
      while(HRmCNpnVPx == HRmCNpnVPx){cdaZWJuOBT = true;}
      while(UmyXnoVDJR == UmyXnoVDJR){iftbzPbyyA = true;}
      if(JFGwGjerOi == true){JFGwGjerOi = false;}
      if(KTuYMmAmQU == true){KTuYMmAmQU = false;}
      if(bLliiVxcoU == true){bLliiVxcoU = false;}
      if(DKDWoBKqwc == true){DKDWoBKqwc = false;}
      if(LuGglAqZKB == true){LuGglAqZKB = false;}
      if(nilopxSXMk == true){nilopxSXMk = false;}
      if(mBCtfAQYiK == true){mBCtfAQYiK = false;}
      if(bIqnIfFFwi == true){bIqnIfFFwi = false;}
      if(dWRmfUYNfr == true){dWRmfUYNfr = false;}
      if(imdLoKsLAl == true){imdLoKsLAl = false;}
      if(iSqzZerxgK == true){iSqzZerxgK = false;}
      if(rMadGPiPOK == true){rMadGPiPOK = false;}
      if(bDrqbodezy == true){bDrqbodezy = false;}
      if(msEKzKfSNA == true){msEKzKfSNA = false;}
      if(cagVzVLAEY == true){cagVzVLAEY = false;}
      if(acxoJfazXk == true){acxoJfazXk = false;}
      if(BMyhWzIPdw == true){BMyhWzIPdw = false;}
      if(iQCOhBVWqF == true){iQCOhBVWqF = false;}
      if(cdaZWJuOBT == true){cdaZWJuOBT = false;}
      if(iftbzPbyyA == true){iftbzPbyyA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MKLGJRHVXQ
{ 
  void mchMIRLwdc()
  { 
      bool lYyokCyQyG = false;
      bool xnXYjLjZsm = false;
      bool fpxQrXuAcs = false;
      bool JWCwhEUrZc = false;
      bool jWdjHKeejq = false;
      bool XtUGFwbgxM = false;
      bool GynFwakapf = false;
      bool qrzQCILMJg = false;
      bool sQPkUPBwpl = false;
      bool cmuMVliXng = false;
      bool YDnEAftEEw = false;
      bool jOXPTphCkg = false;
      bool YojECDwmtP = false;
      bool ZmYcIobLko = false;
      bool VxrtCOPerf = false;
      bool EgmGHjTjBw = false;
      bool iGKnWwotHe = false;
      bool NVRwKawpBn = false;
      bool nRuNKszRUX = false;
      bool VrJnFOmDWF = false;
      string kaHjdmRDEx;
      string cGwTdzDazp;
      string ueXCcaAHKl;
      string KjjtREgkHh;
      string JRfQKexwrW;
      string jAYnEFDFHC;
      string mKrRmsVBBZ;
      string RRSRfdzGqx;
      string dDOmBJLwpM;
      string BadEuyYNdQ;
      string JuuRESgHHa;
      string FwNJYiwEPc;
      string hZLoYpmOWh;
      string ElcZnhIwii;
      string bEnPGEMTfL;
      string CUxAiijGsN;
      string eSjZVTSnVp;
      string azVgBckuhT;
      string dShKfincpE;
      string yCDUDITOsl;
      if(kaHjdmRDEx == JuuRESgHHa){lYyokCyQyG = true;}
      else if(JuuRESgHHa == kaHjdmRDEx){YDnEAftEEw = true;}
      if(cGwTdzDazp == FwNJYiwEPc){xnXYjLjZsm = true;}
      else if(FwNJYiwEPc == cGwTdzDazp){jOXPTphCkg = true;}
      if(ueXCcaAHKl == hZLoYpmOWh){fpxQrXuAcs = true;}
      else if(hZLoYpmOWh == ueXCcaAHKl){YojECDwmtP = true;}
      if(KjjtREgkHh == ElcZnhIwii){JWCwhEUrZc = true;}
      else if(ElcZnhIwii == KjjtREgkHh){ZmYcIobLko = true;}
      if(JRfQKexwrW == bEnPGEMTfL){jWdjHKeejq = true;}
      else if(bEnPGEMTfL == JRfQKexwrW){VxrtCOPerf = true;}
      if(jAYnEFDFHC == CUxAiijGsN){XtUGFwbgxM = true;}
      else if(CUxAiijGsN == jAYnEFDFHC){EgmGHjTjBw = true;}
      if(mKrRmsVBBZ == eSjZVTSnVp){GynFwakapf = true;}
      else if(eSjZVTSnVp == mKrRmsVBBZ){iGKnWwotHe = true;}
      if(RRSRfdzGqx == azVgBckuhT){qrzQCILMJg = true;}
      if(dDOmBJLwpM == dShKfincpE){sQPkUPBwpl = true;}
      if(BadEuyYNdQ == yCDUDITOsl){cmuMVliXng = true;}
      while(azVgBckuhT == RRSRfdzGqx){NVRwKawpBn = true;}
      while(dShKfincpE == dShKfincpE){nRuNKszRUX = true;}
      while(yCDUDITOsl == yCDUDITOsl){VrJnFOmDWF = true;}
      if(lYyokCyQyG == true){lYyokCyQyG = false;}
      if(xnXYjLjZsm == true){xnXYjLjZsm = false;}
      if(fpxQrXuAcs == true){fpxQrXuAcs = false;}
      if(JWCwhEUrZc == true){JWCwhEUrZc = false;}
      if(jWdjHKeejq == true){jWdjHKeejq = false;}
      if(XtUGFwbgxM == true){XtUGFwbgxM = false;}
      if(GynFwakapf == true){GynFwakapf = false;}
      if(qrzQCILMJg == true){qrzQCILMJg = false;}
      if(sQPkUPBwpl == true){sQPkUPBwpl = false;}
      if(cmuMVliXng == true){cmuMVliXng = false;}
      if(YDnEAftEEw == true){YDnEAftEEw = false;}
      if(jOXPTphCkg == true){jOXPTphCkg = false;}
      if(YojECDwmtP == true){YojECDwmtP = false;}
      if(ZmYcIobLko == true){ZmYcIobLko = false;}
      if(VxrtCOPerf == true){VxrtCOPerf = false;}
      if(EgmGHjTjBw == true){EgmGHjTjBw = false;}
      if(iGKnWwotHe == true){iGKnWwotHe = false;}
      if(NVRwKawpBn == true){NVRwKawpBn = false;}
      if(nRuNKszRUX == true){nRuNKszRUX = false;}
      if(VrJnFOmDWF == true){VrJnFOmDWF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UIKCNSRZDW
{ 
  void sJBjrDateL()
  { 
      bool DkFIUuXKaz = false;
      bool ZuypYPakpf = false;
      bool szGjszpxjT = false;
      bool MHNigLhRVC = false;
      bool CDywGErxzu = false;
      bool yheIhEeVOU = false;
      bool FZZGlShOIM = false;
      bool hJPmcpAJco = false;
      bool HryoUebFBc = false;
      bool gMCAxcdqKn = false;
      bool WcolNoRqer = false;
      bool EVrZMMaklH = false;
      bool pbNffUGOpA = false;
      bool MIynSeDLae = false;
      bool MkaIXKUbmj = false;
      bool BrFCytOIFs = false;
      bool hCAdfuWDHh = false;
      bool JPKGuEAEHU = false;
      bool AebGzTDwpX = false;
      bool PtGhwJjwcc = false;
      string RkGCoLshQT;
      string EhtmukhwzD;
      string LznraFQxOZ;
      string yDYbeogzbw;
      string NeKIIAMLtL;
      string wweCGSwObj;
      string uuTpUAJRHF;
      string DhTCpfofja;
      string rEDCdCXWVM;
      string rSXrBRLTmH;
      string ptEnHNbcMa;
      string cQeBqprQMS;
      string bmwtMkKaBX;
      string UUrbjxAOtP;
      string ZuJtjbnVBK;
      string ZtHTfDyJaV;
      string DAbnGHXCQs;
      string pdVwsfcCKk;
      string xnZpyZNYwg;
      string zpmYLZTVnb;
      if(RkGCoLshQT == ptEnHNbcMa){DkFIUuXKaz = true;}
      else if(ptEnHNbcMa == RkGCoLshQT){WcolNoRqer = true;}
      if(EhtmukhwzD == cQeBqprQMS){ZuypYPakpf = true;}
      else if(cQeBqprQMS == EhtmukhwzD){EVrZMMaklH = true;}
      if(LznraFQxOZ == bmwtMkKaBX){szGjszpxjT = true;}
      else if(bmwtMkKaBX == LznraFQxOZ){pbNffUGOpA = true;}
      if(yDYbeogzbw == UUrbjxAOtP){MHNigLhRVC = true;}
      else if(UUrbjxAOtP == yDYbeogzbw){MIynSeDLae = true;}
      if(NeKIIAMLtL == ZuJtjbnVBK){CDywGErxzu = true;}
      else if(ZuJtjbnVBK == NeKIIAMLtL){MkaIXKUbmj = true;}
      if(wweCGSwObj == ZtHTfDyJaV){yheIhEeVOU = true;}
      else if(ZtHTfDyJaV == wweCGSwObj){BrFCytOIFs = true;}
      if(uuTpUAJRHF == DAbnGHXCQs){FZZGlShOIM = true;}
      else if(DAbnGHXCQs == uuTpUAJRHF){hCAdfuWDHh = true;}
      if(DhTCpfofja == pdVwsfcCKk){hJPmcpAJco = true;}
      if(rEDCdCXWVM == xnZpyZNYwg){HryoUebFBc = true;}
      if(rSXrBRLTmH == zpmYLZTVnb){gMCAxcdqKn = true;}
      while(pdVwsfcCKk == DhTCpfofja){JPKGuEAEHU = true;}
      while(xnZpyZNYwg == xnZpyZNYwg){AebGzTDwpX = true;}
      while(zpmYLZTVnb == zpmYLZTVnb){PtGhwJjwcc = true;}
      if(DkFIUuXKaz == true){DkFIUuXKaz = false;}
      if(ZuypYPakpf == true){ZuypYPakpf = false;}
      if(szGjszpxjT == true){szGjszpxjT = false;}
      if(MHNigLhRVC == true){MHNigLhRVC = false;}
      if(CDywGErxzu == true){CDywGErxzu = false;}
      if(yheIhEeVOU == true){yheIhEeVOU = false;}
      if(FZZGlShOIM == true){FZZGlShOIM = false;}
      if(hJPmcpAJco == true){hJPmcpAJco = false;}
      if(HryoUebFBc == true){HryoUebFBc = false;}
      if(gMCAxcdqKn == true){gMCAxcdqKn = false;}
      if(WcolNoRqer == true){WcolNoRqer = false;}
      if(EVrZMMaklH == true){EVrZMMaklH = false;}
      if(pbNffUGOpA == true){pbNffUGOpA = false;}
      if(MIynSeDLae == true){MIynSeDLae = false;}
      if(MkaIXKUbmj == true){MkaIXKUbmj = false;}
      if(BrFCytOIFs == true){BrFCytOIFs = false;}
      if(hCAdfuWDHh == true){hCAdfuWDHh = false;}
      if(JPKGuEAEHU == true){JPKGuEAEHU = false;}
      if(AebGzTDwpX == true){AebGzTDwpX = false;}
      if(PtGhwJjwcc == true){PtGhwJjwcc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VKZHVNIMAV
{ 
  void smcejWJraV()
  { 
      bool RNTcydHDow = false;
      bool CYlqESWKBj = false;
      bool qPWefRWizR = false;
      bool LGKydfUTkV = false;
      bool kkDEdVqVDb = false;
      bool EbzeXBqnxf = false;
      bool HXEXkuNmMX = false;
      bool yDZfzFMSAK = false;
      bool ZAfXNjGfac = false;
      bool ofVENMgfTi = false;
      bool IDIecABTfR = false;
      bool nYnlGGrfJA = false;
      bool ogMjhSgVRl = false;
      bool YgyRCVqAuM = false;
      bool hlAInQqjyH = false;
      bool TBVSsaqYwK = false;
      bool TfCssHZVjj = false;
      bool PrkxRCgEwR = false;
      bool axWJSWKeXa = false;
      bool eSDjsCjGOf = false;
      string ERTXlWIrfS;
      string AWEmjhBeUO;
      string cCedIGNJFH;
      string NStZQzwyEZ;
      string AkTdHwwdwR;
      string dwPcMCmpPe;
      string IzlYFgbeWj;
      string lDatOqhAVL;
      string KjNmcQCRMO;
      string MFiYRAytXZ;
      string UQHLfaVVOU;
      string TlTDUXlzwo;
      string eKRHXfTBbN;
      string rncwqscBHB;
      string ufCqtalfEs;
      string OzyiuKyznz;
      string GTsBcfJXLa;
      string ujqtsyHZMw;
      string tnwizrosBg;
      string tdNItalBOO;
      if(ERTXlWIrfS == UQHLfaVVOU){RNTcydHDow = true;}
      else if(UQHLfaVVOU == ERTXlWIrfS){IDIecABTfR = true;}
      if(AWEmjhBeUO == TlTDUXlzwo){CYlqESWKBj = true;}
      else if(TlTDUXlzwo == AWEmjhBeUO){nYnlGGrfJA = true;}
      if(cCedIGNJFH == eKRHXfTBbN){qPWefRWizR = true;}
      else if(eKRHXfTBbN == cCedIGNJFH){ogMjhSgVRl = true;}
      if(NStZQzwyEZ == rncwqscBHB){LGKydfUTkV = true;}
      else if(rncwqscBHB == NStZQzwyEZ){YgyRCVqAuM = true;}
      if(AkTdHwwdwR == ufCqtalfEs){kkDEdVqVDb = true;}
      else if(ufCqtalfEs == AkTdHwwdwR){hlAInQqjyH = true;}
      if(dwPcMCmpPe == OzyiuKyznz){EbzeXBqnxf = true;}
      else if(OzyiuKyznz == dwPcMCmpPe){TBVSsaqYwK = true;}
      if(IzlYFgbeWj == GTsBcfJXLa){HXEXkuNmMX = true;}
      else if(GTsBcfJXLa == IzlYFgbeWj){TfCssHZVjj = true;}
      if(lDatOqhAVL == ujqtsyHZMw){yDZfzFMSAK = true;}
      if(KjNmcQCRMO == tnwizrosBg){ZAfXNjGfac = true;}
      if(MFiYRAytXZ == tdNItalBOO){ofVENMgfTi = true;}
      while(ujqtsyHZMw == lDatOqhAVL){PrkxRCgEwR = true;}
      while(tnwizrosBg == tnwizrosBg){axWJSWKeXa = true;}
      while(tdNItalBOO == tdNItalBOO){eSDjsCjGOf = true;}
      if(RNTcydHDow == true){RNTcydHDow = false;}
      if(CYlqESWKBj == true){CYlqESWKBj = false;}
      if(qPWefRWizR == true){qPWefRWizR = false;}
      if(LGKydfUTkV == true){LGKydfUTkV = false;}
      if(kkDEdVqVDb == true){kkDEdVqVDb = false;}
      if(EbzeXBqnxf == true){EbzeXBqnxf = false;}
      if(HXEXkuNmMX == true){HXEXkuNmMX = false;}
      if(yDZfzFMSAK == true){yDZfzFMSAK = false;}
      if(ZAfXNjGfac == true){ZAfXNjGfac = false;}
      if(ofVENMgfTi == true){ofVENMgfTi = false;}
      if(IDIecABTfR == true){IDIecABTfR = false;}
      if(nYnlGGrfJA == true){nYnlGGrfJA = false;}
      if(ogMjhSgVRl == true){ogMjhSgVRl = false;}
      if(YgyRCVqAuM == true){YgyRCVqAuM = false;}
      if(hlAInQqjyH == true){hlAInQqjyH = false;}
      if(TBVSsaqYwK == true){TBVSsaqYwK = false;}
      if(TfCssHZVjj == true){TfCssHZVjj = false;}
      if(PrkxRCgEwR == true){PrkxRCgEwR = false;}
      if(axWJSWKeXa == true){axWJSWKeXa = false;}
      if(eSDjsCjGOf == true){eSDjsCjGOf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QDMRPOMPAI
{ 
  void kyfPmjtyMq()
  { 
      bool LYcyIPfASg = false;
      bool ducTeOIVlV = false;
      bool opOmRAhezq = false;
      bool terEMKWgrN = false;
      bool VhfuPRcjLk = false;
      bool rLPlIUKogH = false;
      bool hBBbmzDXGT = false;
      bool radYAHJTXz = false;
      bool XxSNyiOFwq = false;
      bool AgAjeUfEHP = false;
      bool NFdrsRgplA = false;
      bool LpQgjjimcE = false;
      bool kyaOSKZsse = false;
      bool aELIkRTaUg = false;
      bool BXSufKPTAu = false;
      bool kraDdPdOYh = false;
      bool qmxGZGdIuR = false;
      bool QISwCMefiI = false;
      bool tGsythcIdV = false;
      bool mEBloNaLVY = false;
      string XRwrdbJhdZ;
      string UrIhgwJPKE;
      string MSOooEtJiY;
      string GydSgFBAqn;
      string ldULMYSEtL;
      string iVIOKEDGCZ;
      string gzzFSVNoAb;
      string uIYWShyDcP;
      string loPWpkpOIb;
      string BtxQGldPrp;
      string KcESQZwlwb;
      string GAdmnrjcOg;
      string fzgYZAKIPf;
      string DiKlFJkxGP;
      string oESfVBQKcO;
      string CBALJLwerP;
      string OnWPXXoqge;
      string GlVzrbgACY;
      string jAeAcChzcs;
      string MFEqABhCIx;
      if(XRwrdbJhdZ == KcESQZwlwb){LYcyIPfASg = true;}
      else if(KcESQZwlwb == XRwrdbJhdZ){NFdrsRgplA = true;}
      if(UrIhgwJPKE == GAdmnrjcOg){ducTeOIVlV = true;}
      else if(GAdmnrjcOg == UrIhgwJPKE){LpQgjjimcE = true;}
      if(MSOooEtJiY == fzgYZAKIPf){opOmRAhezq = true;}
      else if(fzgYZAKIPf == MSOooEtJiY){kyaOSKZsse = true;}
      if(GydSgFBAqn == DiKlFJkxGP){terEMKWgrN = true;}
      else if(DiKlFJkxGP == GydSgFBAqn){aELIkRTaUg = true;}
      if(ldULMYSEtL == oESfVBQKcO){VhfuPRcjLk = true;}
      else if(oESfVBQKcO == ldULMYSEtL){BXSufKPTAu = true;}
      if(iVIOKEDGCZ == CBALJLwerP){rLPlIUKogH = true;}
      else if(CBALJLwerP == iVIOKEDGCZ){kraDdPdOYh = true;}
      if(gzzFSVNoAb == OnWPXXoqge){hBBbmzDXGT = true;}
      else if(OnWPXXoqge == gzzFSVNoAb){qmxGZGdIuR = true;}
      if(uIYWShyDcP == GlVzrbgACY){radYAHJTXz = true;}
      if(loPWpkpOIb == jAeAcChzcs){XxSNyiOFwq = true;}
      if(BtxQGldPrp == MFEqABhCIx){AgAjeUfEHP = true;}
      while(GlVzrbgACY == uIYWShyDcP){QISwCMefiI = true;}
      while(jAeAcChzcs == jAeAcChzcs){tGsythcIdV = true;}
      while(MFEqABhCIx == MFEqABhCIx){mEBloNaLVY = true;}
      if(LYcyIPfASg == true){LYcyIPfASg = false;}
      if(ducTeOIVlV == true){ducTeOIVlV = false;}
      if(opOmRAhezq == true){opOmRAhezq = false;}
      if(terEMKWgrN == true){terEMKWgrN = false;}
      if(VhfuPRcjLk == true){VhfuPRcjLk = false;}
      if(rLPlIUKogH == true){rLPlIUKogH = false;}
      if(hBBbmzDXGT == true){hBBbmzDXGT = false;}
      if(radYAHJTXz == true){radYAHJTXz = false;}
      if(XxSNyiOFwq == true){XxSNyiOFwq = false;}
      if(AgAjeUfEHP == true){AgAjeUfEHP = false;}
      if(NFdrsRgplA == true){NFdrsRgplA = false;}
      if(LpQgjjimcE == true){LpQgjjimcE = false;}
      if(kyaOSKZsse == true){kyaOSKZsse = false;}
      if(aELIkRTaUg == true){aELIkRTaUg = false;}
      if(BXSufKPTAu == true){BXSufKPTAu = false;}
      if(kraDdPdOYh == true){kraDdPdOYh = false;}
      if(qmxGZGdIuR == true){qmxGZGdIuR = false;}
      if(QISwCMefiI == true){QISwCMefiI = false;}
      if(tGsythcIdV == true){tGsythcIdV = false;}
      if(mEBloNaLVY == true){mEBloNaLVY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBKGRZXVCJ
{ 
  void UmGxMAZueg()
  { 
      bool nZQDdEQyQd = false;
      bool irUBRTEPyH = false;
      bool fyirPcIawz = false;
      bool AdGxztOUME = false;
      bool wZngSrzOtF = false;
      bool TYExkpqXmB = false;
      bool woBRdEkWBW = false;
      bool EiCsKFJBYX = false;
      bool csfqebZILJ = false;
      bool DphLIHYWDN = false;
      bool GcNXAjVKme = false;
      bool fozPYCIKmC = false;
      bool ecKrTOBqkD = false;
      bool gmyKRAfIpt = false;
      bool FPUfcNpSlG = false;
      bool zOjBicRVDl = false;
      bool ieZiysqnyY = false;
      bool WzTrwPHdOG = false;
      bool YiEdERCxbn = false;
      bool iKFELaolhi = false;
      string eOxdfSaDUS;
      string wuDWWkeczI;
      string OaGplOsUnO;
      string jqwFUzBQIC;
      string NGUxIIlUsM;
      string CaVptDIGqQ;
      string YFOFiFzxBX;
      string jOUwtIGJhc;
      string cXbbLIUGLR;
      string qtYrcHqOOD;
      string JoTVbnGZul;
      string wyYNnBdmtZ;
      string jrkjfpocSm;
      string QrteTmEFzX;
      string CuLZUrUKDb;
      string cEToSQDiol;
      string ydGIUDEttA;
      string xYnVXogLOn;
      string UeYqJMXFLC;
      string jUQMZYnCFQ;
      if(eOxdfSaDUS == JoTVbnGZul){nZQDdEQyQd = true;}
      else if(JoTVbnGZul == eOxdfSaDUS){GcNXAjVKme = true;}
      if(wuDWWkeczI == wyYNnBdmtZ){irUBRTEPyH = true;}
      else if(wyYNnBdmtZ == wuDWWkeczI){fozPYCIKmC = true;}
      if(OaGplOsUnO == jrkjfpocSm){fyirPcIawz = true;}
      else if(jrkjfpocSm == OaGplOsUnO){ecKrTOBqkD = true;}
      if(jqwFUzBQIC == QrteTmEFzX){AdGxztOUME = true;}
      else if(QrteTmEFzX == jqwFUzBQIC){gmyKRAfIpt = true;}
      if(NGUxIIlUsM == CuLZUrUKDb){wZngSrzOtF = true;}
      else if(CuLZUrUKDb == NGUxIIlUsM){FPUfcNpSlG = true;}
      if(CaVptDIGqQ == cEToSQDiol){TYExkpqXmB = true;}
      else if(cEToSQDiol == CaVptDIGqQ){zOjBicRVDl = true;}
      if(YFOFiFzxBX == ydGIUDEttA){woBRdEkWBW = true;}
      else if(ydGIUDEttA == YFOFiFzxBX){ieZiysqnyY = true;}
      if(jOUwtIGJhc == xYnVXogLOn){EiCsKFJBYX = true;}
      if(cXbbLIUGLR == UeYqJMXFLC){csfqebZILJ = true;}
      if(qtYrcHqOOD == jUQMZYnCFQ){DphLIHYWDN = true;}
      while(xYnVXogLOn == jOUwtIGJhc){WzTrwPHdOG = true;}
      while(UeYqJMXFLC == UeYqJMXFLC){YiEdERCxbn = true;}
      while(jUQMZYnCFQ == jUQMZYnCFQ){iKFELaolhi = true;}
      if(nZQDdEQyQd == true){nZQDdEQyQd = false;}
      if(irUBRTEPyH == true){irUBRTEPyH = false;}
      if(fyirPcIawz == true){fyirPcIawz = false;}
      if(AdGxztOUME == true){AdGxztOUME = false;}
      if(wZngSrzOtF == true){wZngSrzOtF = false;}
      if(TYExkpqXmB == true){TYExkpqXmB = false;}
      if(woBRdEkWBW == true){woBRdEkWBW = false;}
      if(EiCsKFJBYX == true){EiCsKFJBYX = false;}
      if(csfqebZILJ == true){csfqebZILJ = false;}
      if(DphLIHYWDN == true){DphLIHYWDN = false;}
      if(GcNXAjVKme == true){GcNXAjVKme = false;}
      if(fozPYCIKmC == true){fozPYCIKmC = false;}
      if(ecKrTOBqkD == true){ecKrTOBqkD = false;}
      if(gmyKRAfIpt == true){gmyKRAfIpt = false;}
      if(FPUfcNpSlG == true){FPUfcNpSlG = false;}
      if(zOjBicRVDl == true){zOjBicRVDl = false;}
      if(ieZiysqnyY == true){ieZiysqnyY = false;}
      if(WzTrwPHdOG == true){WzTrwPHdOG = false;}
      if(YiEdERCxbn == true){YiEdERCxbn = false;}
      if(iKFELaolhi == true){iKFELaolhi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NUHILDPCAA
{ 
  void maYmZlnRjE()
  { 
      bool zIjUEhjUmZ = false;
      bool SMDSetbCnk = false;
      bool odqZOXcXgu = false;
      bool wCoaUXedxw = false;
      bool HJZmmchjyg = false;
      bool hzkSUUQJGg = false;
      bool FLmqcPXcxG = false;
      bool PyErdfDEll = false;
      bool orZANxRWFz = false;
      bool GUXPpwViKW = false;
      bool FFlqQjtroo = false;
      bool RMWTqMkldf = false;
      bool xAWxztZoBg = false;
      bool JUtPfjGhid = false;
      bool CZhQhtxDYc = false;
      bool KiEdYFhorW = false;
      bool JFpHexSHnH = false;
      bool GDDAcXRGPF = false;
      bool xWQYWaPPpa = false;
      bool BRpMTxiakk = false;
      string dHPHtbxmPa;
      string rQAgiDeInU;
      string LWOOGQImBu;
      string sOrpLhEAFU;
      string sKrTDnoazG;
      string UEnmFGsAAc;
      string TJkTgdYJUA;
      string yeCSbBetKR;
      string agnuZnaEjF;
      string oDzbBiZXmZ;
      string PeFyHoBULE;
      string ayoiBlUots;
      string CUYPKufZQr;
      string bHHjBwbpnk;
      string lFrfdpNQaO;
      string NjdsWuFomL;
      string JbDScTqEgF;
      string KeAIGxbskU;
      string gOzBeqdNNG;
      string plCcaKBYDK;
      if(dHPHtbxmPa == PeFyHoBULE){zIjUEhjUmZ = true;}
      else if(PeFyHoBULE == dHPHtbxmPa){FFlqQjtroo = true;}
      if(rQAgiDeInU == ayoiBlUots){SMDSetbCnk = true;}
      else if(ayoiBlUots == rQAgiDeInU){RMWTqMkldf = true;}
      if(LWOOGQImBu == CUYPKufZQr){odqZOXcXgu = true;}
      else if(CUYPKufZQr == LWOOGQImBu){xAWxztZoBg = true;}
      if(sOrpLhEAFU == bHHjBwbpnk){wCoaUXedxw = true;}
      else if(bHHjBwbpnk == sOrpLhEAFU){JUtPfjGhid = true;}
      if(sKrTDnoazG == lFrfdpNQaO){HJZmmchjyg = true;}
      else if(lFrfdpNQaO == sKrTDnoazG){CZhQhtxDYc = true;}
      if(UEnmFGsAAc == NjdsWuFomL){hzkSUUQJGg = true;}
      else if(NjdsWuFomL == UEnmFGsAAc){KiEdYFhorW = true;}
      if(TJkTgdYJUA == JbDScTqEgF){FLmqcPXcxG = true;}
      else if(JbDScTqEgF == TJkTgdYJUA){JFpHexSHnH = true;}
      if(yeCSbBetKR == KeAIGxbskU){PyErdfDEll = true;}
      if(agnuZnaEjF == gOzBeqdNNG){orZANxRWFz = true;}
      if(oDzbBiZXmZ == plCcaKBYDK){GUXPpwViKW = true;}
      while(KeAIGxbskU == yeCSbBetKR){GDDAcXRGPF = true;}
      while(gOzBeqdNNG == gOzBeqdNNG){xWQYWaPPpa = true;}
      while(plCcaKBYDK == plCcaKBYDK){BRpMTxiakk = true;}
      if(zIjUEhjUmZ == true){zIjUEhjUmZ = false;}
      if(SMDSetbCnk == true){SMDSetbCnk = false;}
      if(odqZOXcXgu == true){odqZOXcXgu = false;}
      if(wCoaUXedxw == true){wCoaUXedxw = false;}
      if(HJZmmchjyg == true){HJZmmchjyg = false;}
      if(hzkSUUQJGg == true){hzkSUUQJGg = false;}
      if(FLmqcPXcxG == true){FLmqcPXcxG = false;}
      if(PyErdfDEll == true){PyErdfDEll = false;}
      if(orZANxRWFz == true){orZANxRWFz = false;}
      if(GUXPpwViKW == true){GUXPpwViKW = false;}
      if(FFlqQjtroo == true){FFlqQjtroo = false;}
      if(RMWTqMkldf == true){RMWTqMkldf = false;}
      if(xAWxztZoBg == true){xAWxztZoBg = false;}
      if(JUtPfjGhid == true){JUtPfjGhid = false;}
      if(CZhQhtxDYc == true){CZhQhtxDYc = false;}
      if(KiEdYFhorW == true){KiEdYFhorW = false;}
      if(JFpHexSHnH == true){JFpHexSHnH = false;}
      if(GDDAcXRGPF == true){GDDAcXRGPF = false;}
      if(xWQYWaPPpa == true){xWQYWaPPpa = false;}
      if(BRpMTxiakk == true){BRpMTxiakk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DQIGWBRYOM
{ 
  void kaSILaLpKh()
  { 
      bool tTDSoJaFXN = false;
      bool dDoBrRmwOJ = false;
      bool ueQgOcdMcn = false;
      bool XqwoUWpJie = false;
      bool mikyUTfQzs = false;
      bool HuKHxOCVEL = false;
      bool eOcjpmGzfV = false;
      bool bcMiWMsRMt = false;
      bool xNMifcforF = false;
      bool TTEWzXFBIg = false;
      bool MfjdRdhajj = false;
      bool UkIKNRBtDN = false;
      bool GQGaBHYpiy = false;
      bool GrJfgQciRC = false;
      bool tFFIjiKtIh = false;
      bool WLxuawYJbJ = false;
      bool Frrlccaccw = false;
      bool oSbBSBLypS = false;
      bool xdgBbutOEk = false;
      bool qSGIwCMSeH = false;
      string NwczThSAMZ;
      string hcnEwdGcpp;
      string zKXQqkPsVp;
      string VPHfyLbRPy;
      string JqYFWJbnyX;
      string dMXeYDXMHi;
      string SYeVDSVIFk;
      string CnNqfHkSth;
      string IauxLJrbGu;
      string nPKfejMDBE;
      string nThMVpyfzR;
      string SFSZaqdgJt;
      string asCKxmdhLu;
      string thQpsorhbV;
      string LLcnchwjFn;
      string GfsHctRXPi;
      string LPTDXjncfl;
      string ywFmiOQNhO;
      string ptcXoNoJMy;
      string XURrKuqYQr;
      if(NwczThSAMZ == nThMVpyfzR){tTDSoJaFXN = true;}
      else if(nThMVpyfzR == NwczThSAMZ){MfjdRdhajj = true;}
      if(hcnEwdGcpp == SFSZaqdgJt){dDoBrRmwOJ = true;}
      else if(SFSZaqdgJt == hcnEwdGcpp){UkIKNRBtDN = true;}
      if(zKXQqkPsVp == asCKxmdhLu){ueQgOcdMcn = true;}
      else if(asCKxmdhLu == zKXQqkPsVp){GQGaBHYpiy = true;}
      if(VPHfyLbRPy == thQpsorhbV){XqwoUWpJie = true;}
      else if(thQpsorhbV == VPHfyLbRPy){GrJfgQciRC = true;}
      if(JqYFWJbnyX == LLcnchwjFn){mikyUTfQzs = true;}
      else if(LLcnchwjFn == JqYFWJbnyX){tFFIjiKtIh = true;}
      if(dMXeYDXMHi == GfsHctRXPi){HuKHxOCVEL = true;}
      else if(GfsHctRXPi == dMXeYDXMHi){WLxuawYJbJ = true;}
      if(SYeVDSVIFk == LPTDXjncfl){eOcjpmGzfV = true;}
      else if(LPTDXjncfl == SYeVDSVIFk){Frrlccaccw = true;}
      if(CnNqfHkSth == ywFmiOQNhO){bcMiWMsRMt = true;}
      if(IauxLJrbGu == ptcXoNoJMy){xNMifcforF = true;}
      if(nPKfejMDBE == XURrKuqYQr){TTEWzXFBIg = true;}
      while(ywFmiOQNhO == CnNqfHkSth){oSbBSBLypS = true;}
      while(ptcXoNoJMy == ptcXoNoJMy){xdgBbutOEk = true;}
      while(XURrKuqYQr == XURrKuqYQr){qSGIwCMSeH = true;}
      if(tTDSoJaFXN == true){tTDSoJaFXN = false;}
      if(dDoBrRmwOJ == true){dDoBrRmwOJ = false;}
      if(ueQgOcdMcn == true){ueQgOcdMcn = false;}
      if(XqwoUWpJie == true){XqwoUWpJie = false;}
      if(mikyUTfQzs == true){mikyUTfQzs = false;}
      if(HuKHxOCVEL == true){HuKHxOCVEL = false;}
      if(eOcjpmGzfV == true){eOcjpmGzfV = false;}
      if(bcMiWMsRMt == true){bcMiWMsRMt = false;}
      if(xNMifcforF == true){xNMifcforF = false;}
      if(TTEWzXFBIg == true){TTEWzXFBIg = false;}
      if(MfjdRdhajj == true){MfjdRdhajj = false;}
      if(UkIKNRBtDN == true){UkIKNRBtDN = false;}
      if(GQGaBHYpiy == true){GQGaBHYpiy = false;}
      if(GrJfgQciRC == true){GrJfgQciRC = false;}
      if(tFFIjiKtIh == true){tFFIjiKtIh = false;}
      if(WLxuawYJbJ == true){WLxuawYJbJ = false;}
      if(Frrlccaccw == true){Frrlccaccw = false;}
      if(oSbBSBLypS == true){oSbBSBLypS = false;}
      if(xdgBbutOEk == true){xdgBbutOEk = false;}
      if(qSGIwCMSeH == true){qSGIwCMSeH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YHBSRKTAYH
{ 
  void fCbKJyhrkA()
  { 
      bool rCAURnIsqm = false;
      bool wfDaflrlsD = false;
      bool cYqiVLSpUU = false;
      bool KbMckiynFQ = false;
      bool ZPAamrPqeA = false;
      bool NogGVSLQyF = false;
      bool URYVcTSZpx = false;
      bool nEgccNXPuc = false;
      bool wbKTHVuGHR = false;
      bool XgozuHpeyT = false;
      bool YoBhMJHEcI = false;
      bool tuVUJsHFNH = false;
      bool XLSXZGPhgV = false;
      bool WsRaEGZcHx = false;
      bool NqdyWbKToC = false;
      bool AkQquNWcIF = false;
      bool tZWHlBdtQD = false;
      bool SdyPsghTAx = false;
      bool wureVkbafp = false;
      bool jwUBDmUWMU = false;
      string LKMLRStPMX;
      string nEUUwhMHHI;
      string oXXdDCoawK;
      string LxggWXlbzH;
      string zIhNowHsOH;
      string lffiJmliIP;
      string cTTCMpXnyX;
      string wkHAIfpKnH;
      string twMnXeRxXi;
      string kCTjefneAz;
      string YTupLBXfZc;
      string xbtBUgGedh;
      string YZQOlsQXVc;
      string qKKohaAVcW;
      string GlWtlJHSOy;
      string YJBRZyCfDR;
      string jAJxkmRFSt;
      string fkBHalCWcc;
      string kyIXEhJrOj;
      string XTRLlFbZJz;
      if(LKMLRStPMX == YTupLBXfZc){rCAURnIsqm = true;}
      else if(YTupLBXfZc == LKMLRStPMX){YoBhMJHEcI = true;}
      if(nEUUwhMHHI == xbtBUgGedh){wfDaflrlsD = true;}
      else if(xbtBUgGedh == nEUUwhMHHI){tuVUJsHFNH = true;}
      if(oXXdDCoawK == YZQOlsQXVc){cYqiVLSpUU = true;}
      else if(YZQOlsQXVc == oXXdDCoawK){XLSXZGPhgV = true;}
      if(LxggWXlbzH == qKKohaAVcW){KbMckiynFQ = true;}
      else if(qKKohaAVcW == LxggWXlbzH){WsRaEGZcHx = true;}
      if(zIhNowHsOH == GlWtlJHSOy){ZPAamrPqeA = true;}
      else if(GlWtlJHSOy == zIhNowHsOH){NqdyWbKToC = true;}
      if(lffiJmliIP == YJBRZyCfDR){NogGVSLQyF = true;}
      else if(YJBRZyCfDR == lffiJmliIP){AkQquNWcIF = true;}
      if(cTTCMpXnyX == jAJxkmRFSt){URYVcTSZpx = true;}
      else if(jAJxkmRFSt == cTTCMpXnyX){tZWHlBdtQD = true;}
      if(wkHAIfpKnH == fkBHalCWcc){nEgccNXPuc = true;}
      if(twMnXeRxXi == kyIXEhJrOj){wbKTHVuGHR = true;}
      if(kCTjefneAz == XTRLlFbZJz){XgozuHpeyT = true;}
      while(fkBHalCWcc == wkHAIfpKnH){SdyPsghTAx = true;}
      while(kyIXEhJrOj == kyIXEhJrOj){wureVkbafp = true;}
      while(XTRLlFbZJz == XTRLlFbZJz){jwUBDmUWMU = true;}
      if(rCAURnIsqm == true){rCAURnIsqm = false;}
      if(wfDaflrlsD == true){wfDaflrlsD = false;}
      if(cYqiVLSpUU == true){cYqiVLSpUU = false;}
      if(KbMckiynFQ == true){KbMckiynFQ = false;}
      if(ZPAamrPqeA == true){ZPAamrPqeA = false;}
      if(NogGVSLQyF == true){NogGVSLQyF = false;}
      if(URYVcTSZpx == true){URYVcTSZpx = false;}
      if(nEgccNXPuc == true){nEgccNXPuc = false;}
      if(wbKTHVuGHR == true){wbKTHVuGHR = false;}
      if(XgozuHpeyT == true){XgozuHpeyT = false;}
      if(YoBhMJHEcI == true){YoBhMJHEcI = false;}
      if(tuVUJsHFNH == true){tuVUJsHFNH = false;}
      if(XLSXZGPhgV == true){XLSXZGPhgV = false;}
      if(WsRaEGZcHx == true){WsRaEGZcHx = false;}
      if(NqdyWbKToC == true){NqdyWbKToC = false;}
      if(AkQquNWcIF == true){AkQquNWcIF = false;}
      if(tZWHlBdtQD == true){tZWHlBdtQD = false;}
      if(SdyPsghTAx == true){SdyPsghTAx = false;}
      if(wureVkbafp == true){wureVkbafp = false;}
      if(jwUBDmUWMU == true){jwUBDmUWMU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UXYKSPLAGC
{ 
  void HzMzwgVuVD()
  { 
      bool tDGEsuLbwd = false;
      bool skZqKBRFIa = false;
      bool ViorFhLIsq = false;
      bool qiFCMbIBlZ = false;
      bool LEyApBNZgC = false;
      bool SrXUfLNNyL = false;
      bool jDhFlJfWdh = false;
      bool rQTiPQjnCE = false;
      bool TlaqXyKjWA = false;
      bool NtCZpIVrOf = false;
      bool UquyJCYoFO = false;
      bool aZLtqxbqgm = false;
      bool ywzdTyOssH = false;
      bool uqZWicqbhV = false;
      bool ZVeHZniHir = false;
      bool feLagYqQeL = false;
      bool mfwxTiznKO = false;
      bool GzIKNcQqEe = false;
      bool OGKAbPfyoK = false;
      bool kZxVhtZgnp = false;
      string pMrMyGweru;
      string qYRjhyrMzD;
      string jltfSVMPSs;
      string dzPpPkDtsy;
      string uGpWlrLHYp;
      string LuhfMERMsc;
      string tgLzRrJaUx;
      string uyTAIdwWsZ;
      string JFpcgiRidL;
      string SqBQEOtqFt;
      string ijmbtNagXh;
      string HtSSSnphRh;
      string ZaxIdDxDus;
      string iFRyqZRNhT;
      string HjKuDXXhxP;
      string XLYWTImdxp;
      string QXkdzCcTbr;
      string VbAxapPBEG;
      string fOFfVXftei;
      string mnQqDjyfwB;
      if(pMrMyGweru == ijmbtNagXh){tDGEsuLbwd = true;}
      else if(ijmbtNagXh == pMrMyGweru){UquyJCYoFO = true;}
      if(qYRjhyrMzD == HtSSSnphRh){skZqKBRFIa = true;}
      else if(HtSSSnphRh == qYRjhyrMzD){aZLtqxbqgm = true;}
      if(jltfSVMPSs == ZaxIdDxDus){ViorFhLIsq = true;}
      else if(ZaxIdDxDus == jltfSVMPSs){ywzdTyOssH = true;}
      if(dzPpPkDtsy == iFRyqZRNhT){qiFCMbIBlZ = true;}
      else if(iFRyqZRNhT == dzPpPkDtsy){uqZWicqbhV = true;}
      if(uGpWlrLHYp == HjKuDXXhxP){LEyApBNZgC = true;}
      else if(HjKuDXXhxP == uGpWlrLHYp){ZVeHZniHir = true;}
      if(LuhfMERMsc == XLYWTImdxp){SrXUfLNNyL = true;}
      else if(XLYWTImdxp == LuhfMERMsc){feLagYqQeL = true;}
      if(tgLzRrJaUx == QXkdzCcTbr){jDhFlJfWdh = true;}
      else if(QXkdzCcTbr == tgLzRrJaUx){mfwxTiznKO = true;}
      if(uyTAIdwWsZ == VbAxapPBEG){rQTiPQjnCE = true;}
      if(JFpcgiRidL == fOFfVXftei){TlaqXyKjWA = true;}
      if(SqBQEOtqFt == mnQqDjyfwB){NtCZpIVrOf = true;}
      while(VbAxapPBEG == uyTAIdwWsZ){GzIKNcQqEe = true;}
      while(fOFfVXftei == fOFfVXftei){OGKAbPfyoK = true;}
      while(mnQqDjyfwB == mnQqDjyfwB){kZxVhtZgnp = true;}
      if(tDGEsuLbwd == true){tDGEsuLbwd = false;}
      if(skZqKBRFIa == true){skZqKBRFIa = false;}
      if(ViorFhLIsq == true){ViorFhLIsq = false;}
      if(qiFCMbIBlZ == true){qiFCMbIBlZ = false;}
      if(LEyApBNZgC == true){LEyApBNZgC = false;}
      if(SrXUfLNNyL == true){SrXUfLNNyL = false;}
      if(jDhFlJfWdh == true){jDhFlJfWdh = false;}
      if(rQTiPQjnCE == true){rQTiPQjnCE = false;}
      if(TlaqXyKjWA == true){TlaqXyKjWA = false;}
      if(NtCZpIVrOf == true){NtCZpIVrOf = false;}
      if(UquyJCYoFO == true){UquyJCYoFO = false;}
      if(aZLtqxbqgm == true){aZLtqxbqgm = false;}
      if(ywzdTyOssH == true){ywzdTyOssH = false;}
      if(uqZWicqbhV == true){uqZWicqbhV = false;}
      if(ZVeHZniHir == true){ZVeHZniHir = false;}
      if(feLagYqQeL == true){feLagYqQeL = false;}
      if(mfwxTiznKO == true){mfwxTiznKO = false;}
      if(GzIKNcQqEe == true){GzIKNcQqEe = false;}
      if(OGKAbPfyoK == true){OGKAbPfyoK = false;}
      if(kZxVhtZgnp == true){kZxVhtZgnp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XKJJDGYWEQ
{ 
  void CjBVmhIFTo()
  { 
      bool DQZttzabED = false;
      bool eZlxknSRWy = false;
      bool GwlNhpXGtM = false;
      bool TCLxGegrYc = false;
      bool rqGYLZOnyJ = false;
      bool ZCYeEGdLME = false;
      bool aUhrjcNopF = false;
      bool HarsGOpNCH = false;
      bool bjHjmQdfrA = false;
      bool BUeUBXIOnh = false;
      bool LZxrByKeYp = false;
      bool QPJEbqMxET = false;
      bool zhwpEluWrh = false;
      bool FbZTwClOin = false;
      bool GyGCikKasK = false;
      bool LLJUiccHnO = false;
      bool DmmqjnppHZ = false;
      bool EyOPMAasGS = false;
      bool aUdgWtSEkS = false;
      bool YeaTkTLPSu = false;
      string HgnBMDrLFp;
      string ZntzRzNUmk;
      string RCSukBZQbx;
      string VbOJEFHViE;
      string mILhltklrA;
      string XEbiLEOsQL;
      string cbiITxYjtM;
      string qqkhxJqjJp;
      string PnYaYQAfyz;
      string pOFXaLYDNn;
      string VBqeJgSskC;
      string NdiZwoCHiD;
      string wrluWblNGk;
      string jmVUUOxsRr;
      string xHuwlLfebl;
      string IQTKrcPwIh;
      string tFlzRZIOFg;
      string qJpqFnxoJK;
      string wGlTcSTLbq;
      string zBkjxrUudL;
      if(HgnBMDrLFp == VBqeJgSskC){DQZttzabED = true;}
      else if(VBqeJgSskC == HgnBMDrLFp){LZxrByKeYp = true;}
      if(ZntzRzNUmk == NdiZwoCHiD){eZlxknSRWy = true;}
      else if(NdiZwoCHiD == ZntzRzNUmk){QPJEbqMxET = true;}
      if(RCSukBZQbx == wrluWblNGk){GwlNhpXGtM = true;}
      else if(wrluWblNGk == RCSukBZQbx){zhwpEluWrh = true;}
      if(VbOJEFHViE == jmVUUOxsRr){TCLxGegrYc = true;}
      else if(jmVUUOxsRr == VbOJEFHViE){FbZTwClOin = true;}
      if(mILhltklrA == xHuwlLfebl){rqGYLZOnyJ = true;}
      else if(xHuwlLfebl == mILhltklrA){GyGCikKasK = true;}
      if(XEbiLEOsQL == IQTKrcPwIh){ZCYeEGdLME = true;}
      else if(IQTKrcPwIh == XEbiLEOsQL){LLJUiccHnO = true;}
      if(cbiITxYjtM == tFlzRZIOFg){aUhrjcNopF = true;}
      else if(tFlzRZIOFg == cbiITxYjtM){DmmqjnppHZ = true;}
      if(qqkhxJqjJp == qJpqFnxoJK){HarsGOpNCH = true;}
      if(PnYaYQAfyz == wGlTcSTLbq){bjHjmQdfrA = true;}
      if(pOFXaLYDNn == zBkjxrUudL){BUeUBXIOnh = true;}
      while(qJpqFnxoJK == qqkhxJqjJp){EyOPMAasGS = true;}
      while(wGlTcSTLbq == wGlTcSTLbq){aUdgWtSEkS = true;}
      while(zBkjxrUudL == zBkjxrUudL){YeaTkTLPSu = true;}
      if(DQZttzabED == true){DQZttzabED = false;}
      if(eZlxknSRWy == true){eZlxknSRWy = false;}
      if(GwlNhpXGtM == true){GwlNhpXGtM = false;}
      if(TCLxGegrYc == true){TCLxGegrYc = false;}
      if(rqGYLZOnyJ == true){rqGYLZOnyJ = false;}
      if(ZCYeEGdLME == true){ZCYeEGdLME = false;}
      if(aUhrjcNopF == true){aUhrjcNopF = false;}
      if(HarsGOpNCH == true){HarsGOpNCH = false;}
      if(bjHjmQdfrA == true){bjHjmQdfrA = false;}
      if(BUeUBXIOnh == true){BUeUBXIOnh = false;}
      if(LZxrByKeYp == true){LZxrByKeYp = false;}
      if(QPJEbqMxET == true){QPJEbqMxET = false;}
      if(zhwpEluWrh == true){zhwpEluWrh = false;}
      if(FbZTwClOin == true){FbZTwClOin = false;}
      if(GyGCikKasK == true){GyGCikKasK = false;}
      if(LLJUiccHnO == true){LLJUiccHnO = false;}
      if(DmmqjnppHZ == true){DmmqjnppHZ = false;}
      if(EyOPMAasGS == true){EyOPMAasGS = false;}
      if(aUdgWtSEkS == true){aUdgWtSEkS = false;}
      if(YeaTkTLPSu == true){YeaTkTLPSu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RFISTXZYPD
{ 
  void AQUNFgyaQC()
  { 
      bool yYVdYVyORm = false;
      bool QEPcpOLhDk = false;
      bool wKROqXmgmF = false;
      bool lMultunJGT = false;
      bool oRElndQgIT = false;
      bool xKwhZnGHlB = false;
      bool hRaMBEJdhu = false;
      bool aCbiwdFfaN = false;
      bool GFXSIbPMLG = false;
      bool ogWEkWpqki = false;
      bool UlzMsthNlw = false;
      bool hZfYtcsIEY = false;
      bool oxSbGteWxZ = false;
      bool mOuqrUGKYN = false;
      bool sBZPYOAxKI = false;
      bool chmLtXTXGz = false;
      bool PKPMITeofZ = false;
      bool ViiqfmWCCr = false;
      bool thMnwFajwU = false;
      bool AiEZyhlNHE = false;
      string agyXFFAdBs;
      string PAJPqTCLew;
      string CBnQDyMAjs;
      string SzzQRFhLmg;
      string tOVfUkUccf;
      string NQUDfYrgTG;
      string sztIZPBsyk;
      string kpYxCmeIwR;
      string diXEeBdukr;
      string NBqfntUNFE;
      string jbdrtXrXBr;
      string sijBbJbpcY;
      string kGIGWjzrJI;
      string SQDrhCEeJH;
      string JGssydQoEd;
      string SekgScTXUK;
      string XANsYbfrTZ;
      string EwfVOeMOHr;
      string TJnfonfVZE;
      string hgJziJrATV;
      if(agyXFFAdBs == jbdrtXrXBr){yYVdYVyORm = true;}
      else if(jbdrtXrXBr == agyXFFAdBs){UlzMsthNlw = true;}
      if(PAJPqTCLew == sijBbJbpcY){QEPcpOLhDk = true;}
      else if(sijBbJbpcY == PAJPqTCLew){hZfYtcsIEY = true;}
      if(CBnQDyMAjs == kGIGWjzrJI){wKROqXmgmF = true;}
      else if(kGIGWjzrJI == CBnQDyMAjs){oxSbGteWxZ = true;}
      if(SzzQRFhLmg == SQDrhCEeJH){lMultunJGT = true;}
      else if(SQDrhCEeJH == SzzQRFhLmg){mOuqrUGKYN = true;}
      if(tOVfUkUccf == JGssydQoEd){oRElndQgIT = true;}
      else if(JGssydQoEd == tOVfUkUccf){sBZPYOAxKI = true;}
      if(NQUDfYrgTG == SekgScTXUK){xKwhZnGHlB = true;}
      else if(SekgScTXUK == NQUDfYrgTG){chmLtXTXGz = true;}
      if(sztIZPBsyk == XANsYbfrTZ){hRaMBEJdhu = true;}
      else if(XANsYbfrTZ == sztIZPBsyk){PKPMITeofZ = true;}
      if(kpYxCmeIwR == EwfVOeMOHr){aCbiwdFfaN = true;}
      if(diXEeBdukr == TJnfonfVZE){GFXSIbPMLG = true;}
      if(NBqfntUNFE == hgJziJrATV){ogWEkWpqki = true;}
      while(EwfVOeMOHr == kpYxCmeIwR){ViiqfmWCCr = true;}
      while(TJnfonfVZE == TJnfonfVZE){thMnwFajwU = true;}
      while(hgJziJrATV == hgJziJrATV){AiEZyhlNHE = true;}
      if(yYVdYVyORm == true){yYVdYVyORm = false;}
      if(QEPcpOLhDk == true){QEPcpOLhDk = false;}
      if(wKROqXmgmF == true){wKROqXmgmF = false;}
      if(lMultunJGT == true){lMultunJGT = false;}
      if(oRElndQgIT == true){oRElndQgIT = false;}
      if(xKwhZnGHlB == true){xKwhZnGHlB = false;}
      if(hRaMBEJdhu == true){hRaMBEJdhu = false;}
      if(aCbiwdFfaN == true){aCbiwdFfaN = false;}
      if(GFXSIbPMLG == true){GFXSIbPMLG = false;}
      if(ogWEkWpqki == true){ogWEkWpqki = false;}
      if(UlzMsthNlw == true){UlzMsthNlw = false;}
      if(hZfYtcsIEY == true){hZfYtcsIEY = false;}
      if(oxSbGteWxZ == true){oxSbGteWxZ = false;}
      if(mOuqrUGKYN == true){mOuqrUGKYN = false;}
      if(sBZPYOAxKI == true){sBZPYOAxKI = false;}
      if(chmLtXTXGz == true){chmLtXTXGz = false;}
      if(PKPMITeofZ == true){PKPMITeofZ = false;}
      if(ViiqfmWCCr == true){ViiqfmWCCr = false;}
      if(thMnwFajwU == true){thMnwFajwU = false;}
      if(AiEZyhlNHE == true){AiEZyhlNHE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZIKIEMFXRA
{ 
  void PkICHQESFX()
  { 
      bool IkdaLiOxMh = false;
      bool ehsNQGujDj = false;
      bool jnVOydBrHp = false;
      bool eCEQrIyALq = false;
      bool YjLVBfCoGh = false;
      bool rxwOITOPch = false;
      bool hVpVDbdbUH = false;
      bool HuYLLAbAMS = false;
      bool aLlYxgFpHY = false;
      bool tiXcJDspSY = false;
      bool CZTyaxYjCI = false;
      bool qNCJGViQXV = false;
      bool WmTwNYWuCI = false;
      bool GlhnQBqnyA = false;
      bool IVnzgffNWm = false;
      bool UcSwCOFXkB = false;
      bool ZchtBFfOsE = false;
      bool dtSWMAzUOh = false;
      bool sJYOndTkkB = false;
      bool uTDxZemsxb = false;
      string nxpakPfxUu;
      string wraXpKAsSH;
      string IxWMrKVGFk;
      string ElopwWRPbC;
      string iRCYKRxzEI;
      string WEfRepZdia;
      string tYrjpJDkbS;
      string sjRQYpuyBa;
      string MWCwNzFWKG;
      string xngBIJZRhA;
      string NMXkPmmPsn;
      string ubbHNXVwWq;
      string DfZUVFCPHO;
      string QcPBMAyRgZ;
      string LpdWLULYnk;
      string mduqwglCOJ;
      string jXHdXRMatM;
      string YEPxeNCDJB;
      string scbWamhXEf;
      string OuCWonhzys;
      if(nxpakPfxUu == NMXkPmmPsn){IkdaLiOxMh = true;}
      else if(NMXkPmmPsn == nxpakPfxUu){CZTyaxYjCI = true;}
      if(wraXpKAsSH == ubbHNXVwWq){ehsNQGujDj = true;}
      else if(ubbHNXVwWq == wraXpKAsSH){qNCJGViQXV = true;}
      if(IxWMrKVGFk == DfZUVFCPHO){jnVOydBrHp = true;}
      else if(DfZUVFCPHO == IxWMrKVGFk){WmTwNYWuCI = true;}
      if(ElopwWRPbC == QcPBMAyRgZ){eCEQrIyALq = true;}
      else if(QcPBMAyRgZ == ElopwWRPbC){GlhnQBqnyA = true;}
      if(iRCYKRxzEI == LpdWLULYnk){YjLVBfCoGh = true;}
      else if(LpdWLULYnk == iRCYKRxzEI){IVnzgffNWm = true;}
      if(WEfRepZdia == mduqwglCOJ){rxwOITOPch = true;}
      else if(mduqwglCOJ == WEfRepZdia){UcSwCOFXkB = true;}
      if(tYrjpJDkbS == jXHdXRMatM){hVpVDbdbUH = true;}
      else if(jXHdXRMatM == tYrjpJDkbS){ZchtBFfOsE = true;}
      if(sjRQYpuyBa == YEPxeNCDJB){HuYLLAbAMS = true;}
      if(MWCwNzFWKG == scbWamhXEf){aLlYxgFpHY = true;}
      if(xngBIJZRhA == OuCWonhzys){tiXcJDspSY = true;}
      while(YEPxeNCDJB == sjRQYpuyBa){dtSWMAzUOh = true;}
      while(scbWamhXEf == scbWamhXEf){sJYOndTkkB = true;}
      while(OuCWonhzys == OuCWonhzys){uTDxZemsxb = true;}
      if(IkdaLiOxMh == true){IkdaLiOxMh = false;}
      if(ehsNQGujDj == true){ehsNQGujDj = false;}
      if(jnVOydBrHp == true){jnVOydBrHp = false;}
      if(eCEQrIyALq == true){eCEQrIyALq = false;}
      if(YjLVBfCoGh == true){YjLVBfCoGh = false;}
      if(rxwOITOPch == true){rxwOITOPch = false;}
      if(hVpVDbdbUH == true){hVpVDbdbUH = false;}
      if(HuYLLAbAMS == true){HuYLLAbAMS = false;}
      if(aLlYxgFpHY == true){aLlYxgFpHY = false;}
      if(tiXcJDspSY == true){tiXcJDspSY = false;}
      if(CZTyaxYjCI == true){CZTyaxYjCI = false;}
      if(qNCJGViQXV == true){qNCJGViQXV = false;}
      if(WmTwNYWuCI == true){WmTwNYWuCI = false;}
      if(GlhnQBqnyA == true){GlhnQBqnyA = false;}
      if(IVnzgffNWm == true){IVnzgffNWm = false;}
      if(UcSwCOFXkB == true){UcSwCOFXkB = false;}
      if(ZchtBFfOsE == true){ZchtBFfOsE = false;}
      if(dtSWMAzUOh == true){dtSWMAzUOh = false;}
      if(sJYOndTkkB == true){sJYOndTkkB = false;}
      if(uTDxZemsxb == true){uTDxZemsxb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WWJPRBMJPM
{ 
  void aKtLnliAeT()
  { 
      bool hqJSOqAAkF = false;
      bool tEqPwUgCxd = false;
      bool xYAjXszKyQ = false;
      bool iSCBxlyynZ = false;
      bool rCEYpqrVOJ = false;
      bool oldaQJpZtU = false;
      bool qpCTVaBoRJ = false;
      bool ViOWktTbtf = false;
      bool Bdunaxobkn = false;
      bool wYDTiCAjCO = false;
      bool oDDEmGXGpV = false;
      bool pNeNTMtNsY = false;
      bool lZDdNwetni = false;
      bool tiYeqyZpAT = false;
      bool ZilPyhspAV = false;
      bool HlqdcPzZqq = false;
      bool bcSGbGoAWU = false;
      bool lEMYyDnnef = false;
      bool CotRaHquCb = false;
      bool yAzJrwPenq = false;
      string tZMtceHCOX;
      string ShhwsPbSMS;
      string aSESDujfpE;
      string sDzlWsFPyG;
      string ZlXKMGqJYh;
      string eVHBZbVtph;
      string tbMKeOhuYA;
      string KMTGrntsFw;
      string EaHHZWwyMu;
      string XKYQLyZNfx;
      string XujYXRBBIk;
      string gbnscTUEjH;
      string SjidbznDut;
      string OgNIYIphiH;
      string UtoaOwWemr;
      string cVcXdnMGwY;
      string dyFOWANfUU;
      string clUbmXtHPf;
      string cIQDQsDoej;
      string wilKdWoaEN;
      if(tZMtceHCOX == XujYXRBBIk){hqJSOqAAkF = true;}
      else if(XujYXRBBIk == tZMtceHCOX){oDDEmGXGpV = true;}
      if(ShhwsPbSMS == gbnscTUEjH){tEqPwUgCxd = true;}
      else if(gbnscTUEjH == ShhwsPbSMS){pNeNTMtNsY = true;}
      if(aSESDujfpE == SjidbznDut){xYAjXszKyQ = true;}
      else if(SjidbznDut == aSESDujfpE){lZDdNwetni = true;}
      if(sDzlWsFPyG == OgNIYIphiH){iSCBxlyynZ = true;}
      else if(OgNIYIphiH == sDzlWsFPyG){tiYeqyZpAT = true;}
      if(ZlXKMGqJYh == UtoaOwWemr){rCEYpqrVOJ = true;}
      else if(UtoaOwWemr == ZlXKMGqJYh){ZilPyhspAV = true;}
      if(eVHBZbVtph == cVcXdnMGwY){oldaQJpZtU = true;}
      else if(cVcXdnMGwY == eVHBZbVtph){HlqdcPzZqq = true;}
      if(tbMKeOhuYA == dyFOWANfUU){qpCTVaBoRJ = true;}
      else if(dyFOWANfUU == tbMKeOhuYA){bcSGbGoAWU = true;}
      if(KMTGrntsFw == clUbmXtHPf){ViOWktTbtf = true;}
      if(EaHHZWwyMu == cIQDQsDoej){Bdunaxobkn = true;}
      if(XKYQLyZNfx == wilKdWoaEN){wYDTiCAjCO = true;}
      while(clUbmXtHPf == KMTGrntsFw){lEMYyDnnef = true;}
      while(cIQDQsDoej == cIQDQsDoej){CotRaHquCb = true;}
      while(wilKdWoaEN == wilKdWoaEN){yAzJrwPenq = true;}
      if(hqJSOqAAkF == true){hqJSOqAAkF = false;}
      if(tEqPwUgCxd == true){tEqPwUgCxd = false;}
      if(xYAjXszKyQ == true){xYAjXszKyQ = false;}
      if(iSCBxlyynZ == true){iSCBxlyynZ = false;}
      if(rCEYpqrVOJ == true){rCEYpqrVOJ = false;}
      if(oldaQJpZtU == true){oldaQJpZtU = false;}
      if(qpCTVaBoRJ == true){qpCTVaBoRJ = false;}
      if(ViOWktTbtf == true){ViOWktTbtf = false;}
      if(Bdunaxobkn == true){Bdunaxobkn = false;}
      if(wYDTiCAjCO == true){wYDTiCAjCO = false;}
      if(oDDEmGXGpV == true){oDDEmGXGpV = false;}
      if(pNeNTMtNsY == true){pNeNTMtNsY = false;}
      if(lZDdNwetni == true){lZDdNwetni = false;}
      if(tiYeqyZpAT == true){tiYeqyZpAT = false;}
      if(ZilPyhspAV == true){ZilPyhspAV = false;}
      if(HlqdcPzZqq == true){HlqdcPzZqq = false;}
      if(bcSGbGoAWU == true){bcSGbGoAWU = false;}
      if(lEMYyDnnef == true){lEMYyDnnef = false;}
      if(CotRaHquCb == true){CotRaHquCb = false;}
      if(yAzJrwPenq == true){yAzJrwPenq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LXIINRTQKD
{ 
  void VbgsUzeZjJ()
  { 
      bool dHTEnoRGMf = false;
      bool OVpQymyNrd = false;
      bool VRZoJeTFUL = false;
      bool gToYomnzYM = false;
      bool fWtldnwPwJ = false;
      bool KZGXXMgeuJ = false;
      bool UMkBztfQaK = false;
      bool yznfxzWnKU = false;
      bool hEILAGNRBc = false;
      bool GJEPrTkrmi = false;
      bool HenlKLlaZY = false;
      bool orUZaPDZAs = false;
      bool gOPxDouXnc = false;
      bool NdBaNDPVAo = false;
      bool TlqbmNodob = false;
      bool QLqsCrPqiU = false;
      bool QNlwKLqsMX = false;
      bool AgYLYtWmKo = false;
      bool AQiMMBlHYU = false;
      bool mYmeYFzuRb = false;
      string dGptfjzmri;
      string hJjxXfNCol;
      string tmncNiCOWe;
      string LpOomjYrLC;
      string oWzkapchst;
      string dVghRpRNfw;
      string hkQNWqttKn;
      string GVpmwXnDCX;
      string FTUbBpIfXw;
      string RLLOTEGkNi;
      string wiXFnHetls;
      string COLIpNPnMf;
      string iNVNVuKbTq;
      string QCoSaWwPns;
      string LOtdtCACXF;
      string oSYhAhMJis;
      string wCatczYrhT;
      string RAASUTTqTS;
      string uIDNBycHSs;
      string JlftxImzBt;
      if(dGptfjzmri == wiXFnHetls){dHTEnoRGMf = true;}
      else if(wiXFnHetls == dGptfjzmri){HenlKLlaZY = true;}
      if(hJjxXfNCol == COLIpNPnMf){OVpQymyNrd = true;}
      else if(COLIpNPnMf == hJjxXfNCol){orUZaPDZAs = true;}
      if(tmncNiCOWe == iNVNVuKbTq){VRZoJeTFUL = true;}
      else if(iNVNVuKbTq == tmncNiCOWe){gOPxDouXnc = true;}
      if(LpOomjYrLC == QCoSaWwPns){gToYomnzYM = true;}
      else if(QCoSaWwPns == LpOomjYrLC){NdBaNDPVAo = true;}
      if(oWzkapchst == LOtdtCACXF){fWtldnwPwJ = true;}
      else if(LOtdtCACXF == oWzkapchst){TlqbmNodob = true;}
      if(dVghRpRNfw == oSYhAhMJis){KZGXXMgeuJ = true;}
      else if(oSYhAhMJis == dVghRpRNfw){QLqsCrPqiU = true;}
      if(hkQNWqttKn == wCatczYrhT){UMkBztfQaK = true;}
      else if(wCatczYrhT == hkQNWqttKn){QNlwKLqsMX = true;}
      if(GVpmwXnDCX == RAASUTTqTS){yznfxzWnKU = true;}
      if(FTUbBpIfXw == uIDNBycHSs){hEILAGNRBc = true;}
      if(RLLOTEGkNi == JlftxImzBt){GJEPrTkrmi = true;}
      while(RAASUTTqTS == GVpmwXnDCX){AgYLYtWmKo = true;}
      while(uIDNBycHSs == uIDNBycHSs){AQiMMBlHYU = true;}
      while(JlftxImzBt == JlftxImzBt){mYmeYFzuRb = true;}
      if(dHTEnoRGMf == true){dHTEnoRGMf = false;}
      if(OVpQymyNrd == true){OVpQymyNrd = false;}
      if(VRZoJeTFUL == true){VRZoJeTFUL = false;}
      if(gToYomnzYM == true){gToYomnzYM = false;}
      if(fWtldnwPwJ == true){fWtldnwPwJ = false;}
      if(KZGXXMgeuJ == true){KZGXXMgeuJ = false;}
      if(UMkBztfQaK == true){UMkBztfQaK = false;}
      if(yznfxzWnKU == true){yznfxzWnKU = false;}
      if(hEILAGNRBc == true){hEILAGNRBc = false;}
      if(GJEPrTkrmi == true){GJEPrTkrmi = false;}
      if(HenlKLlaZY == true){HenlKLlaZY = false;}
      if(orUZaPDZAs == true){orUZaPDZAs = false;}
      if(gOPxDouXnc == true){gOPxDouXnc = false;}
      if(NdBaNDPVAo == true){NdBaNDPVAo = false;}
      if(TlqbmNodob == true){TlqbmNodob = false;}
      if(QLqsCrPqiU == true){QLqsCrPqiU = false;}
      if(QNlwKLqsMX == true){QNlwKLqsMX = false;}
      if(AgYLYtWmKo == true){AgYLYtWmKo = false;}
      if(AQiMMBlHYU == true){AQiMMBlHYU = false;}
      if(mYmeYFzuRb == true){mYmeYFzuRb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XADSFDHOXQ
{ 
  void SpLPrDcpyD()
  { 
      bool GipcoLWSdt = false;
      bool RgRJQYCzoS = false;
      bool LBcOFuBswF = false;
      bool NbVxGjPuSq = false;
      bool ULzVdAOPXu = false;
      bool SNNcCEGbWt = false;
      bool JcVXfpLTCf = false;
      bool IGgyyACGjF = false;
      bool glVAlzNruB = false;
      bool dmYYgqpaon = false;
      bool otMqlMgPdC = false;
      bool CzqRMWHUlg = false;
      bool bSYACUhHRH = false;
      bool JaRwQmZdNZ = false;
      bool SyOszdwHLJ = false;
      bool iUoILVVMoR = false;
      bool eYyVrbhtBZ = false;
      bool xcGLNdDeBY = false;
      bool YauHXolIkt = false;
      bool QMowusArBX = false;
      string nbMFkVOxqc;
      string TJNJExkeZr;
      string ZSLamNdcmn;
      string xQHagLsXHw;
      string tTDFVXJXMj;
      string AmMeMUQkSW;
      string rkJDfCBlcs;
      string ENXdxGPFFO;
      string DFPDmKEbNL;
      string uHFjDIKAYT;
      string VWuTfmOhgG;
      string FKeDTlVFQV;
      string xZYRxwInZo;
      string wOflrfKuXz;
      string uVuGFjcBPR;
      string lEjDVwydWj;
      string eZIrKqdsKm;
      string bahQZaeRLN;
      string TGXICqecQw;
      string gfYnTUNCwO;
      if(nbMFkVOxqc == VWuTfmOhgG){GipcoLWSdt = true;}
      else if(VWuTfmOhgG == nbMFkVOxqc){otMqlMgPdC = true;}
      if(TJNJExkeZr == FKeDTlVFQV){RgRJQYCzoS = true;}
      else if(FKeDTlVFQV == TJNJExkeZr){CzqRMWHUlg = true;}
      if(ZSLamNdcmn == xZYRxwInZo){LBcOFuBswF = true;}
      else if(xZYRxwInZo == ZSLamNdcmn){bSYACUhHRH = true;}
      if(xQHagLsXHw == wOflrfKuXz){NbVxGjPuSq = true;}
      else if(wOflrfKuXz == xQHagLsXHw){JaRwQmZdNZ = true;}
      if(tTDFVXJXMj == uVuGFjcBPR){ULzVdAOPXu = true;}
      else if(uVuGFjcBPR == tTDFVXJXMj){SyOszdwHLJ = true;}
      if(AmMeMUQkSW == lEjDVwydWj){SNNcCEGbWt = true;}
      else if(lEjDVwydWj == AmMeMUQkSW){iUoILVVMoR = true;}
      if(rkJDfCBlcs == eZIrKqdsKm){JcVXfpLTCf = true;}
      else if(eZIrKqdsKm == rkJDfCBlcs){eYyVrbhtBZ = true;}
      if(ENXdxGPFFO == bahQZaeRLN){IGgyyACGjF = true;}
      if(DFPDmKEbNL == TGXICqecQw){glVAlzNruB = true;}
      if(uHFjDIKAYT == gfYnTUNCwO){dmYYgqpaon = true;}
      while(bahQZaeRLN == ENXdxGPFFO){xcGLNdDeBY = true;}
      while(TGXICqecQw == TGXICqecQw){YauHXolIkt = true;}
      while(gfYnTUNCwO == gfYnTUNCwO){QMowusArBX = true;}
      if(GipcoLWSdt == true){GipcoLWSdt = false;}
      if(RgRJQYCzoS == true){RgRJQYCzoS = false;}
      if(LBcOFuBswF == true){LBcOFuBswF = false;}
      if(NbVxGjPuSq == true){NbVxGjPuSq = false;}
      if(ULzVdAOPXu == true){ULzVdAOPXu = false;}
      if(SNNcCEGbWt == true){SNNcCEGbWt = false;}
      if(JcVXfpLTCf == true){JcVXfpLTCf = false;}
      if(IGgyyACGjF == true){IGgyyACGjF = false;}
      if(glVAlzNruB == true){glVAlzNruB = false;}
      if(dmYYgqpaon == true){dmYYgqpaon = false;}
      if(otMqlMgPdC == true){otMqlMgPdC = false;}
      if(CzqRMWHUlg == true){CzqRMWHUlg = false;}
      if(bSYACUhHRH == true){bSYACUhHRH = false;}
      if(JaRwQmZdNZ == true){JaRwQmZdNZ = false;}
      if(SyOszdwHLJ == true){SyOszdwHLJ = false;}
      if(iUoILVVMoR == true){iUoILVVMoR = false;}
      if(eYyVrbhtBZ == true){eYyVrbhtBZ = false;}
      if(xcGLNdDeBY == true){xcGLNdDeBY = false;}
      if(YauHXolIkt == true){YauHXolIkt = false;}
      if(QMowusArBX == true){QMowusArBX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMKINNMNUN
{ 
  void yetezCzXRi()
  { 
      bool PfmhhBdeVQ = false;
      bool WuDnhZUTna = false;
      bool QMiKXTiajV = false;
      bool ExoMVihmVw = false;
      bool MMpyhQcWaL = false;
      bool PwSiQCwbJO = false;
      bool RCuzLYFqRy = false;
      bool rgyrODWjbH = false;
      bool qMzXGIeGwS = false;
      bool lFcHdJRpmI = false;
      bool KlEcTiyaTM = false;
      bool fMACXFCXsD = false;
      bool sztyLmDqNE = false;
      bool lgxTxEHWDW = false;
      bool JElimZFaiY = false;
      bool GtwiPKqFQg = false;
      bool eHMOazPfFS = false;
      bool yfTVsoMLLl = false;
      bool gcHoxrjNEl = false;
      bool NBFWrCqWHn = false;
      string IVsCzJewsZ;
      string XpHSxuVdFH;
      string AIFzAdTOJn;
      string iOUfqTXAfE;
      string oqJCEtyHdN;
      string ncNwgAQtBV;
      string pPlEpJUaad;
      string WVxBRJyCuF;
      string eLkwAGAXzq;
      string DdyJNZEFMt;
      string YWgApSeLeW;
      string BOzuqeepDi;
      string IxbiZsWnmr;
      string EsoAfHdkFh;
      string bnsbondCRi;
      string uOBckbuxZw;
      string upXlRIYyPj;
      string AtjVHUEztl;
      string OUVExprLPE;
      string LgKIlkPGKg;
      if(IVsCzJewsZ == YWgApSeLeW){PfmhhBdeVQ = true;}
      else if(YWgApSeLeW == IVsCzJewsZ){KlEcTiyaTM = true;}
      if(XpHSxuVdFH == BOzuqeepDi){WuDnhZUTna = true;}
      else if(BOzuqeepDi == XpHSxuVdFH){fMACXFCXsD = true;}
      if(AIFzAdTOJn == IxbiZsWnmr){QMiKXTiajV = true;}
      else if(IxbiZsWnmr == AIFzAdTOJn){sztyLmDqNE = true;}
      if(iOUfqTXAfE == EsoAfHdkFh){ExoMVihmVw = true;}
      else if(EsoAfHdkFh == iOUfqTXAfE){lgxTxEHWDW = true;}
      if(oqJCEtyHdN == bnsbondCRi){MMpyhQcWaL = true;}
      else if(bnsbondCRi == oqJCEtyHdN){JElimZFaiY = true;}
      if(ncNwgAQtBV == uOBckbuxZw){PwSiQCwbJO = true;}
      else if(uOBckbuxZw == ncNwgAQtBV){GtwiPKqFQg = true;}
      if(pPlEpJUaad == upXlRIYyPj){RCuzLYFqRy = true;}
      else if(upXlRIYyPj == pPlEpJUaad){eHMOazPfFS = true;}
      if(WVxBRJyCuF == AtjVHUEztl){rgyrODWjbH = true;}
      if(eLkwAGAXzq == OUVExprLPE){qMzXGIeGwS = true;}
      if(DdyJNZEFMt == LgKIlkPGKg){lFcHdJRpmI = true;}
      while(AtjVHUEztl == WVxBRJyCuF){yfTVsoMLLl = true;}
      while(OUVExprLPE == OUVExprLPE){gcHoxrjNEl = true;}
      while(LgKIlkPGKg == LgKIlkPGKg){NBFWrCqWHn = true;}
      if(PfmhhBdeVQ == true){PfmhhBdeVQ = false;}
      if(WuDnhZUTna == true){WuDnhZUTna = false;}
      if(QMiKXTiajV == true){QMiKXTiajV = false;}
      if(ExoMVihmVw == true){ExoMVihmVw = false;}
      if(MMpyhQcWaL == true){MMpyhQcWaL = false;}
      if(PwSiQCwbJO == true){PwSiQCwbJO = false;}
      if(RCuzLYFqRy == true){RCuzLYFqRy = false;}
      if(rgyrODWjbH == true){rgyrODWjbH = false;}
      if(qMzXGIeGwS == true){qMzXGIeGwS = false;}
      if(lFcHdJRpmI == true){lFcHdJRpmI = false;}
      if(KlEcTiyaTM == true){KlEcTiyaTM = false;}
      if(fMACXFCXsD == true){fMACXFCXsD = false;}
      if(sztyLmDqNE == true){sztyLmDqNE = false;}
      if(lgxTxEHWDW == true){lgxTxEHWDW = false;}
      if(JElimZFaiY == true){JElimZFaiY = false;}
      if(GtwiPKqFQg == true){GtwiPKqFQg = false;}
      if(eHMOazPfFS == true){eHMOazPfFS = false;}
      if(yfTVsoMLLl == true){yfTVsoMLLl = false;}
      if(gcHoxrjNEl == true){gcHoxrjNEl = false;}
      if(NBFWrCqWHn == true){NBFWrCqWHn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JIWIAWJPWL
{ 
  void XlrpzSDmyQ()
  { 
      bool tLEelyArnJ = false;
      bool oBzmSyyrQP = false;
      bool ogqqHKXlNz = false;
      bool lOtHGEtgFS = false;
      bool MLGgKMHxmz = false;
      bool TEBbYNTNXb = false;
      bool ZNenXZGqfO = false;
      bool ERmxDdZKgu = false;
      bool CZyNfgNSir = false;
      bool jgIcrygSJj = false;
      bool GPQXuCRDYt = false;
      bool nIfbYAPQIp = false;
      bool LnIndXIJEE = false;
      bool xHBxolIZSc = false;
      bool PJsnDaAfEr = false;
      bool iPJTXRHcsW = false;
      bool tIzTxgHimm = false;
      bool qoxeZBtUjD = false;
      bool WbELVgxhYW = false;
      bool effuhHKYpW = false;
      string HdXsYshHkG;
      string IHecyexeQQ;
      string ZgzTJDUQqm;
      string KiWTlcNssW;
      string ErKxflGqgJ;
      string yJYRQZdEjU;
      string XQPxwYkKqV;
      string RElsLhWCnW;
      string xcjgoAKFDL;
      string yIJYymbMBG;
      string BuALqsXeFi;
      string DbPMWtgiIu;
      string OfHeWIuNuX;
      string FJAhUBcYow;
      string cfzUIVswBD;
      string GsEGqVnVni;
      string xKihctahqV;
      string RIsLRhfmVB;
      string PzMqRMEtpz;
      string NHjGySwRrO;
      if(HdXsYshHkG == BuALqsXeFi){tLEelyArnJ = true;}
      else if(BuALqsXeFi == HdXsYshHkG){GPQXuCRDYt = true;}
      if(IHecyexeQQ == DbPMWtgiIu){oBzmSyyrQP = true;}
      else if(DbPMWtgiIu == IHecyexeQQ){nIfbYAPQIp = true;}
      if(ZgzTJDUQqm == OfHeWIuNuX){ogqqHKXlNz = true;}
      else if(OfHeWIuNuX == ZgzTJDUQqm){LnIndXIJEE = true;}
      if(KiWTlcNssW == FJAhUBcYow){lOtHGEtgFS = true;}
      else if(FJAhUBcYow == KiWTlcNssW){xHBxolIZSc = true;}
      if(ErKxflGqgJ == cfzUIVswBD){MLGgKMHxmz = true;}
      else if(cfzUIVswBD == ErKxflGqgJ){PJsnDaAfEr = true;}
      if(yJYRQZdEjU == GsEGqVnVni){TEBbYNTNXb = true;}
      else if(GsEGqVnVni == yJYRQZdEjU){iPJTXRHcsW = true;}
      if(XQPxwYkKqV == xKihctahqV){ZNenXZGqfO = true;}
      else if(xKihctahqV == XQPxwYkKqV){tIzTxgHimm = true;}
      if(RElsLhWCnW == RIsLRhfmVB){ERmxDdZKgu = true;}
      if(xcjgoAKFDL == PzMqRMEtpz){CZyNfgNSir = true;}
      if(yIJYymbMBG == NHjGySwRrO){jgIcrygSJj = true;}
      while(RIsLRhfmVB == RElsLhWCnW){qoxeZBtUjD = true;}
      while(PzMqRMEtpz == PzMqRMEtpz){WbELVgxhYW = true;}
      while(NHjGySwRrO == NHjGySwRrO){effuhHKYpW = true;}
      if(tLEelyArnJ == true){tLEelyArnJ = false;}
      if(oBzmSyyrQP == true){oBzmSyyrQP = false;}
      if(ogqqHKXlNz == true){ogqqHKXlNz = false;}
      if(lOtHGEtgFS == true){lOtHGEtgFS = false;}
      if(MLGgKMHxmz == true){MLGgKMHxmz = false;}
      if(TEBbYNTNXb == true){TEBbYNTNXb = false;}
      if(ZNenXZGqfO == true){ZNenXZGqfO = false;}
      if(ERmxDdZKgu == true){ERmxDdZKgu = false;}
      if(CZyNfgNSir == true){CZyNfgNSir = false;}
      if(jgIcrygSJj == true){jgIcrygSJj = false;}
      if(GPQXuCRDYt == true){GPQXuCRDYt = false;}
      if(nIfbYAPQIp == true){nIfbYAPQIp = false;}
      if(LnIndXIJEE == true){LnIndXIJEE = false;}
      if(xHBxolIZSc == true){xHBxolIZSc = false;}
      if(PJsnDaAfEr == true){PJsnDaAfEr = false;}
      if(iPJTXRHcsW == true){iPJTXRHcsW = false;}
      if(tIzTxgHimm == true){tIzTxgHimm = false;}
      if(qoxeZBtUjD == true){qoxeZBtUjD = false;}
      if(WbELVgxhYW == true){WbELVgxhYW = false;}
      if(effuhHKYpW == true){effuhHKYpW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TBHLKTOOOQ
{ 
  void xysMDeDtaI()
  { 
      bool JWuChZuBez = false;
      bool ztjUcBAZmF = false;
      bool mjQIUYYfbe = false;
      bool PPalEHScGH = false;
      bool mADIEzTrRo = false;
      bool VYlKfZGlgJ = false;
      bool BOZAiiSxPU = false;
      bool iXTeSlfHEV = false;
      bool FfNlIqdPFe = false;
      bool BguxGXaCYU = false;
      bool fVcwGyEGrs = false;
      bool sygKEUAnrr = false;
      bool FCrjTBbWYt = false;
      bool LchjoiDQeK = false;
      bool lXXLlCzkrl = false;
      bool WlKgOcdrcF = false;
      bool VhgyhPQxUU = false;
      bool QiIgFhefyQ = false;
      bool BqdmWYRAUM = false;
      bool FLnZnEpZdV = false;
      string QrWTFqFJor;
      string aVsgsVbdUw;
      string ZkLMstczqT;
      string MTXxzqBpVr;
      string DTRNyYeibD;
      string YiqKzffJaK;
      string NGSVeGyugC;
      string TlHcrFTxOT;
      string PtWmtccNyT;
      string KrOLdwBwhr;
      string ZiBZjmaORs;
      string LhuGtTieaC;
      string ckxMqbWwzu;
      string EWOWsfrwDH;
      string BOuFHcwIQJ;
      string NWUfOoloiI;
      string PePVnoSYMO;
      string bmaSAOorEO;
      string eOeohhCiIE;
      string sDNuqVzZQS;
      if(QrWTFqFJor == ZiBZjmaORs){JWuChZuBez = true;}
      else if(ZiBZjmaORs == QrWTFqFJor){fVcwGyEGrs = true;}
      if(aVsgsVbdUw == LhuGtTieaC){ztjUcBAZmF = true;}
      else if(LhuGtTieaC == aVsgsVbdUw){sygKEUAnrr = true;}
      if(ZkLMstczqT == ckxMqbWwzu){mjQIUYYfbe = true;}
      else if(ckxMqbWwzu == ZkLMstczqT){FCrjTBbWYt = true;}
      if(MTXxzqBpVr == EWOWsfrwDH){PPalEHScGH = true;}
      else if(EWOWsfrwDH == MTXxzqBpVr){LchjoiDQeK = true;}
      if(DTRNyYeibD == BOuFHcwIQJ){mADIEzTrRo = true;}
      else if(BOuFHcwIQJ == DTRNyYeibD){lXXLlCzkrl = true;}
      if(YiqKzffJaK == NWUfOoloiI){VYlKfZGlgJ = true;}
      else if(NWUfOoloiI == YiqKzffJaK){WlKgOcdrcF = true;}
      if(NGSVeGyugC == PePVnoSYMO){BOZAiiSxPU = true;}
      else if(PePVnoSYMO == NGSVeGyugC){VhgyhPQxUU = true;}
      if(TlHcrFTxOT == bmaSAOorEO){iXTeSlfHEV = true;}
      if(PtWmtccNyT == eOeohhCiIE){FfNlIqdPFe = true;}
      if(KrOLdwBwhr == sDNuqVzZQS){BguxGXaCYU = true;}
      while(bmaSAOorEO == TlHcrFTxOT){QiIgFhefyQ = true;}
      while(eOeohhCiIE == eOeohhCiIE){BqdmWYRAUM = true;}
      while(sDNuqVzZQS == sDNuqVzZQS){FLnZnEpZdV = true;}
      if(JWuChZuBez == true){JWuChZuBez = false;}
      if(ztjUcBAZmF == true){ztjUcBAZmF = false;}
      if(mjQIUYYfbe == true){mjQIUYYfbe = false;}
      if(PPalEHScGH == true){PPalEHScGH = false;}
      if(mADIEzTrRo == true){mADIEzTrRo = false;}
      if(VYlKfZGlgJ == true){VYlKfZGlgJ = false;}
      if(BOZAiiSxPU == true){BOZAiiSxPU = false;}
      if(iXTeSlfHEV == true){iXTeSlfHEV = false;}
      if(FfNlIqdPFe == true){FfNlIqdPFe = false;}
      if(BguxGXaCYU == true){BguxGXaCYU = false;}
      if(fVcwGyEGrs == true){fVcwGyEGrs = false;}
      if(sygKEUAnrr == true){sygKEUAnrr = false;}
      if(FCrjTBbWYt == true){FCrjTBbWYt = false;}
      if(LchjoiDQeK == true){LchjoiDQeK = false;}
      if(lXXLlCzkrl == true){lXXLlCzkrl = false;}
      if(WlKgOcdrcF == true){WlKgOcdrcF = false;}
      if(VhgyhPQxUU == true){VhgyhPQxUU = false;}
      if(QiIgFhefyQ == true){QiIgFhefyQ = false;}
      if(BqdmWYRAUM == true){BqdmWYRAUM = false;}
      if(FLnZnEpZdV == true){FLnZnEpZdV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VIVTQHVMMS
{ 
  void rHdzEbtlLk()
  { 
      bool zzdLVPXZDo = false;
      bool cDDonYnIJt = false;
      bool wSRftnqbTz = false;
      bool LjpjRmsuaU = false;
      bool LrNseMTQwF = false;
      bool EZOjdghxQg = false;
      bool XwGEcrMTWA = false;
      bool eshoiDFXBg = false;
      bool TZeOtkUGGk = false;
      bool FudswOlJPl = false;
      bool AAswZLrZBZ = false;
      bool bKwjMyRrJr = false;
      bool XGMlujOorT = false;
      bool RuHOgSgioi = false;
      bool stEgJtytfx = false;
      bool xtzXNsmHAo = false;
      bool wDghHfCgDt = false;
      bool RhDaycBfcA = false;
      bool kUItVWwiBm = false;
      bool eYhzloMWYc = false;
      string HKQdbFuBNe;
      string RtYkPjQOiO;
      string nOSKuiJQBf;
      string jMMkncafPa;
      string yJcYXrpKuY;
      string VWqFcrrGis;
      string wdAhtEgmwm;
      string IkzIQdlslD;
      string rzUbKMVHIw;
      string jUxVeUJueS;
      string KDNIPjXhoz;
      string GzTfAxIYXh;
      string iZdACnncdw;
      string UpOSrokLMZ;
      string onRJpkAQVg;
      string LjXwjkYNGb;
      string uuEsdPkAmK;
      string LwMxsuIUKR;
      string mWGwjjSRiH;
      string QXFjdsiXeZ;
      if(HKQdbFuBNe == KDNIPjXhoz){zzdLVPXZDo = true;}
      else if(KDNIPjXhoz == HKQdbFuBNe){AAswZLrZBZ = true;}
      if(RtYkPjQOiO == GzTfAxIYXh){cDDonYnIJt = true;}
      else if(GzTfAxIYXh == RtYkPjQOiO){bKwjMyRrJr = true;}
      if(nOSKuiJQBf == iZdACnncdw){wSRftnqbTz = true;}
      else if(iZdACnncdw == nOSKuiJQBf){XGMlujOorT = true;}
      if(jMMkncafPa == UpOSrokLMZ){LjpjRmsuaU = true;}
      else if(UpOSrokLMZ == jMMkncafPa){RuHOgSgioi = true;}
      if(yJcYXrpKuY == onRJpkAQVg){LrNseMTQwF = true;}
      else if(onRJpkAQVg == yJcYXrpKuY){stEgJtytfx = true;}
      if(VWqFcrrGis == LjXwjkYNGb){EZOjdghxQg = true;}
      else if(LjXwjkYNGb == VWqFcrrGis){xtzXNsmHAo = true;}
      if(wdAhtEgmwm == uuEsdPkAmK){XwGEcrMTWA = true;}
      else if(uuEsdPkAmK == wdAhtEgmwm){wDghHfCgDt = true;}
      if(IkzIQdlslD == LwMxsuIUKR){eshoiDFXBg = true;}
      if(rzUbKMVHIw == mWGwjjSRiH){TZeOtkUGGk = true;}
      if(jUxVeUJueS == QXFjdsiXeZ){FudswOlJPl = true;}
      while(LwMxsuIUKR == IkzIQdlslD){RhDaycBfcA = true;}
      while(mWGwjjSRiH == mWGwjjSRiH){kUItVWwiBm = true;}
      while(QXFjdsiXeZ == QXFjdsiXeZ){eYhzloMWYc = true;}
      if(zzdLVPXZDo == true){zzdLVPXZDo = false;}
      if(cDDonYnIJt == true){cDDonYnIJt = false;}
      if(wSRftnqbTz == true){wSRftnqbTz = false;}
      if(LjpjRmsuaU == true){LjpjRmsuaU = false;}
      if(LrNseMTQwF == true){LrNseMTQwF = false;}
      if(EZOjdghxQg == true){EZOjdghxQg = false;}
      if(XwGEcrMTWA == true){XwGEcrMTWA = false;}
      if(eshoiDFXBg == true){eshoiDFXBg = false;}
      if(TZeOtkUGGk == true){TZeOtkUGGk = false;}
      if(FudswOlJPl == true){FudswOlJPl = false;}
      if(AAswZLrZBZ == true){AAswZLrZBZ = false;}
      if(bKwjMyRrJr == true){bKwjMyRrJr = false;}
      if(XGMlujOorT == true){XGMlujOorT = false;}
      if(RuHOgSgioi == true){RuHOgSgioi = false;}
      if(stEgJtytfx == true){stEgJtytfx = false;}
      if(xtzXNsmHAo == true){xtzXNsmHAo = false;}
      if(wDghHfCgDt == true){wDghHfCgDt = false;}
      if(RhDaycBfcA == true){RhDaycBfcA = false;}
      if(kUItVWwiBm == true){kUItVWwiBm = false;}
      if(eYhzloMWYc == true){eYhzloMWYc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YSVBZPCETT
{ 
  void flYaUeyVDm()
  { 
      bool pkQYkicPMV = false;
      bool gBackHTKrf = false;
      bool BgYKZxXKLQ = false;
      bool DiWGlWGzra = false;
      bool OVhUIDjbsW = false;
      bool OOlRxJMFym = false;
      bool KSEuRxeUqN = false;
      bool AUSQRfzECV = false;
      bool NwQoCnxFJc = false;
      bool KBBEQwQmCK = false;
      bool YPjeVtwUAQ = false;
      bool JHDcZOBPsc = false;
      bool AYKODzTOAV = false;
      bool OMBqwyLlSH = false;
      bool rcFrSCxXdB = false;
      bool tBsYKAEVbW = false;
      bool ahUeBxGMfb = false;
      bool CPwkkXTRwB = false;
      bool BujyaNScfw = false;
      bool spJwgKHaqU = false;
      string EmZdAUKRPe;
      string SMYEaCGzef;
      string BcInRBCIin;
      string GCJctepOKN;
      string EMfMHrKjwL;
      string LJcBWbdkLy;
      string SBhaYQCwKu;
      string LqnRanwugZ;
      string pRMWcwYHFR;
      string BECLtCdEnq;
      string oNZAATUKai;
      string eiEkHAoLyb;
      string qtqrtHnbWX;
      string KqGpjcrLWI;
      string bNgVmRzRDs;
      string NRFMztWgFr;
      string ernCXmbOAe;
      string IdopAdNUFb;
      string HWXcKrktpp;
      string FKFddiZdxz;
      if(EmZdAUKRPe == oNZAATUKai){pkQYkicPMV = true;}
      else if(oNZAATUKai == EmZdAUKRPe){YPjeVtwUAQ = true;}
      if(SMYEaCGzef == eiEkHAoLyb){gBackHTKrf = true;}
      else if(eiEkHAoLyb == SMYEaCGzef){JHDcZOBPsc = true;}
      if(BcInRBCIin == qtqrtHnbWX){BgYKZxXKLQ = true;}
      else if(qtqrtHnbWX == BcInRBCIin){AYKODzTOAV = true;}
      if(GCJctepOKN == KqGpjcrLWI){DiWGlWGzra = true;}
      else if(KqGpjcrLWI == GCJctepOKN){OMBqwyLlSH = true;}
      if(EMfMHrKjwL == bNgVmRzRDs){OVhUIDjbsW = true;}
      else if(bNgVmRzRDs == EMfMHrKjwL){rcFrSCxXdB = true;}
      if(LJcBWbdkLy == NRFMztWgFr){OOlRxJMFym = true;}
      else if(NRFMztWgFr == LJcBWbdkLy){tBsYKAEVbW = true;}
      if(SBhaYQCwKu == ernCXmbOAe){KSEuRxeUqN = true;}
      else if(ernCXmbOAe == SBhaYQCwKu){ahUeBxGMfb = true;}
      if(LqnRanwugZ == IdopAdNUFb){AUSQRfzECV = true;}
      if(pRMWcwYHFR == HWXcKrktpp){NwQoCnxFJc = true;}
      if(BECLtCdEnq == FKFddiZdxz){KBBEQwQmCK = true;}
      while(IdopAdNUFb == LqnRanwugZ){CPwkkXTRwB = true;}
      while(HWXcKrktpp == HWXcKrktpp){BujyaNScfw = true;}
      while(FKFddiZdxz == FKFddiZdxz){spJwgKHaqU = true;}
      if(pkQYkicPMV == true){pkQYkicPMV = false;}
      if(gBackHTKrf == true){gBackHTKrf = false;}
      if(BgYKZxXKLQ == true){BgYKZxXKLQ = false;}
      if(DiWGlWGzra == true){DiWGlWGzra = false;}
      if(OVhUIDjbsW == true){OVhUIDjbsW = false;}
      if(OOlRxJMFym == true){OOlRxJMFym = false;}
      if(KSEuRxeUqN == true){KSEuRxeUqN = false;}
      if(AUSQRfzECV == true){AUSQRfzECV = false;}
      if(NwQoCnxFJc == true){NwQoCnxFJc = false;}
      if(KBBEQwQmCK == true){KBBEQwQmCK = false;}
      if(YPjeVtwUAQ == true){YPjeVtwUAQ = false;}
      if(JHDcZOBPsc == true){JHDcZOBPsc = false;}
      if(AYKODzTOAV == true){AYKODzTOAV = false;}
      if(OMBqwyLlSH == true){OMBqwyLlSH = false;}
      if(rcFrSCxXdB == true){rcFrSCxXdB = false;}
      if(tBsYKAEVbW == true){tBsYKAEVbW = false;}
      if(ahUeBxGMfb == true){ahUeBxGMfb = false;}
      if(CPwkkXTRwB == true){CPwkkXTRwB = false;}
      if(BujyaNScfw == true){BujyaNScfw = false;}
      if(spJwgKHaqU == true){spJwgKHaqU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRJRJQLXRY
{ 
  void gpXetITBZQ()
  { 
      bool DUacBEgpYH = false;
      bool ipRxjUOiBl = false;
      bool bOUbSCUnWF = false;
      bool HOJdNagiNy = false;
      bool NYrXYFgRhN = false;
      bool WVEVQnAzJz = false;
      bool jrSSzTfniJ = false;
      bool neVDYCWxCM = false;
      bool VCGJilKnMZ = false;
      bool agZNNUFYXF = false;
      bool YrhXYrzAxN = false;
      bool QCxxdhkJjN = false;
      bool IraJhHFHoD = false;
      bool wyYxmcTijp = false;
      bool lJqzJXibjf = false;
      bool iwoJwgRYoR = false;
      bool lqLsRScAJA = false;
      bool NCYsbzAbAJ = false;
      bool XcXJTAJPBF = false;
      bool KusSEtyxhp = false;
      string oooEjgXcHj;
      string ghNGMibMOO;
      string ZMXHMwPLah;
      string ltyBOOAzyH;
      string RumTXRckPe;
      string YtYsubRhqm;
      string RMBZxljMry;
      string ibOHxdYDjt;
      string TewuIrVFFl;
      string xSIKoFtNVk;
      string hPrQwxeQwQ;
      string DNywSmPFQF;
      string QdGFBPTDRr;
      string iLgyMEleyL;
      string MEJoiiTLqC;
      string onwQTDImPf;
      string cayDgqfzjO;
      string AjGFrMURVR;
      string uIMPCuPQeI;
      string wyPRhlFFHr;
      if(oooEjgXcHj == hPrQwxeQwQ){DUacBEgpYH = true;}
      else if(hPrQwxeQwQ == oooEjgXcHj){YrhXYrzAxN = true;}
      if(ghNGMibMOO == DNywSmPFQF){ipRxjUOiBl = true;}
      else if(DNywSmPFQF == ghNGMibMOO){QCxxdhkJjN = true;}
      if(ZMXHMwPLah == QdGFBPTDRr){bOUbSCUnWF = true;}
      else if(QdGFBPTDRr == ZMXHMwPLah){IraJhHFHoD = true;}
      if(ltyBOOAzyH == iLgyMEleyL){HOJdNagiNy = true;}
      else if(iLgyMEleyL == ltyBOOAzyH){wyYxmcTijp = true;}
      if(RumTXRckPe == MEJoiiTLqC){NYrXYFgRhN = true;}
      else if(MEJoiiTLqC == RumTXRckPe){lJqzJXibjf = true;}
      if(YtYsubRhqm == onwQTDImPf){WVEVQnAzJz = true;}
      else if(onwQTDImPf == YtYsubRhqm){iwoJwgRYoR = true;}
      if(RMBZxljMry == cayDgqfzjO){jrSSzTfniJ = true;}
      else if(cayDgqfzjO == RMBZxljMry){lqLsRScAJA = true;}
      if(ibOHxdYDjt == AjGFrMURVR){neVDYCWxCM = true;}
      if(TewuIrVFFl == uIMPCuPQeI){VCGJilKnMZ = true;}
      if(xSIKoFtNVk == wyPRhlFFHr){agZNNUFYXF = true;}
      while(AjGFrMURVR == ibOHxdYDjt){NCYsbzAbAJ = true;}
      while(uIMPCuPQeI == uIMPCuPQeI){XcXJTAJPBF = true;}
      while(wyPRhlFFHr == wyPRhlFFHr){KusSEtyxhp = true;}
      if(DUacBEgpYH == true){DUacBEgpYH = false;}
      if(ipRxjUOiBl == true){ipRxjUOiBl = false;}
      if(bOUbSCUnWF == true){bOUbSCUnWF = false;}
      if(HOJdNagiNy == true){HOJdNagiNy = false;}
      if(NYrXYFgRhN == true){NYrXYFgRhN = false;}
      if(WVEVQnAzJz == true){WVEVQnAzJz = false;}
      if(jrSSzTfniJ == true){jrSSzTfniJ = false;}
      if(neVDYCWxCM == true){neVDYCWxCM = false;}
      if(VCGJilKnMZ == true){VCGJilKnMZ = false;}
      if(agZNNUFYXF == true){agZNNUFYXF = false;}
      if(YrhXYrzAxN == true){YrhXYrzAxN = false;}
      if(QCxxdhkJjN == true){QCxxdhkJjN = false;}
      if(IraJhHFHoD == true){IraJhHFHoD = false;}
      if(wyYxmcTijp == true){wyYxmcTijp = false;}
      if(lJqzJXibjf == true){lJqzJXibjf = false;}
      if(iwoJwgRYoR == true){iwoJwgRYoR = false;}
      if(lqLsRScAJA == true){lqLsRScAJA = false;}
      if(NCYsbzAbAJ == true){NCYsbzAbAJ = false;}
      if(XcXJTAJPBF == true){XcXJTAJPBF = false;}
      if(KusSEtyxhp == true){KusSEtyxhp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TPZRORCSPO
{ 
  void iueFJBBoKV()
  { 
      bool nzHwAqSAEA = false;
      bool McrLwGsUBD = false;
      bool XsrpeAbLbc = false;
      bool cmLGdaQlPy = false;
      bool UIGRIyFkrN = false;
      bool taTIUuHQQz = false;
      bool OGXbXYQlhV = false;
      bool oGFCiOlahf = false;
      bool uqSNhBTDki = false;
      bool TAUPiNjesj = false;
      bool gSCWYnVQYF = false;
      bool IgikEXnJtW = false;
      bool ENBzCokoSU = false;
      bool eHgyzbnuos = false;
      bool fDdeZlQjLL = false;
      bool ZZjWeSRDUi = false;
      bool CfxEaBzklb = false;
      bool irUAqBjVYP = false;
      bool YBdHtEWKSf = false;
      bool KjaGqAFYEY = false;
      string RDYkrGKLgP;
      string XQOwfqPqkJ;
      string CXmuDGLscJ;
      string JijlIsqCVi;
      string jOTGVWDFbH;
      string khCXksQchk;
      string uRhWGngbnm;
      string zMVCZmEfZf;
      string DGQUYagLBO;
      string cNUjmRgwAg;
      string paQoIXMzyx;
      string ojDBhnBNye;
      string GUaYKkrkOH;
      string GHfrpbobMA;
      string OhMDZrKSCz;
      string QSyUZUAqdW;
      string fakqqgEKLG;
      string yZAxPYIXzR;
      string aYhPpmJLSU;
      string ayxoUmwULr;
      if(RDYkrGKLgP == paQoIXMzyx){nzHwAqSAEA = true;}
      else if(paQoIXMzyx == RDYkrGKLgP){gSCWYnVQYF = true;}
      if(XQOwfqPqkJ == ojDBhnBNye){McrLwGsUBD = true;}
      else if(ojDBhnBNye == XQOwfqPqkJ){IgikEXnJtW = true;}
      if(CXmuDGLscJ == GUaYKkrkOH){XsrpeAbLbc = true;}
      else if(GUaYKkrkOH == CXmuDGLscJ){ENBzCokoSU = true;}
      if(JijlIsqCVi == GHfrpbobMA){cmLGdaQlPy = true;}
      else if(GHfrpbobMA == JijlIsqCVi){eHgyzbnuos = true;}
      if(jOTGVWDFbH == OhMDZrKSCz){UIGRIyFkrN = true;}
      else if(OhMDZrKSCz == jOTGVWDFbH){fDdeZlQjLL = true;}
      if(khCXksQchk == QSyUZUAqdW){taTIUuHQQz = true;}
      else if(QSyUZUAqdW == khCXksQchk){ZZjWeSRDUi = true;}
      if(uRhWGngbnm == fakqqgEKLG){OGXbXYQlhV = true;}
      else if(fakqqgEKLG == uRhWGngbnm){CfxEaBzklb = true;}
      if(zMVCZmEfZf == yZAxPYIXzR){oGFCiOlahf = true;}
      if(DGQUYagLBO == aYhPpmJLSU){uqSNhBTDki = true;}
      if(cNUjmRgwAg == ayxoUmwULr){TAUPiNjesj = true;}
      while(yZAxPYIXzR == zMVCZmEfZf){irUAqBjVYP = true;}
      while(aYhPpmJLSU == aYhPpmJLSU){YBdHtEWKSf = true;}
      while(ayxoUmwULr == ayxoUmwULr){KjaGqAFYEY = true;}
      if(nzHwAqSAEA == true){nzHwAqSAEA = false;}
      if(McrLwGsUBD == true){McrLwGsUBD = false;}
      if(XsrpeAbLbc == true){XsrpeAbLbc = false;}
      if(cmLGdaQlPy == true){cmLGdaQlPy = false;}
      if(UIGRIyFkrN == true){UIGRIyFkrN = false;}
      if(taTIUuHQQz == true){taTIUuHQQz = false;}
      if(OGXbXYQlhV == true){OGXbXYQlhV = false;}
      if(oGFCiOlahf == true){oGFCiOlahf = false;}
      if(uqSNhBTDki == true){uqSNhBTDki = false;}
      if(TAUPiNjesj == true){TAUPiNjesj = false;}
      if(gSCWYnVQYF == true){gSCWYnVQYF = false;}
      if(IgikEXnJtW == true){IgikEXnJtW = false;}
      if(ENBzCokoSU == true){ENBzCokoSU = false;}
      if(eHgyzbnuos == true){eHgyzbnuos = false;}
      if(fDdeZlQjLL == true){fDdeZlQjLL = false;}
      if(ZZjWeSRDUi == true){ZZjWeSRDUi = false;}
      if(CfxEaBzklb == true){CfxEaBzklb = false;}
      if(irUAqBjVYP == true){irUAqBjVYP = false;}
      if(YBdHtEWKSf == true){YBdHtEWKSf = false;}
      if(KjaGqAFYEY == true){KjaGqAFYEY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UVXIFVLFHJ
{ 
  void DQeXuReaqV()
  { 
      bool RksgaIeUSE = false;
      bool ypQfDMrNGt = false;
      bool YWnkCmbrIL = false;
      bool dECWalsQRK = false;
      bool HOJlHTWjzY = false;
      bool jHRlZuxIen = false;
      bool gmMGZsmsFQ = false;
      bool SbuulKMCdh = false;
      bool PqriaWmQwf = false;
      bool oklcdUBDLN = false;
      bool fdehFILVzP = false;
      bool huewYotdeD = false;
      bool GWxYbhpSRR = false;
      bool IJqPBlMJcS = false;
      bool KQRgxtFoEn = false;
      bool aXXHHJfFGX = false;
      bool SsEhGYEOtm = false;
      bool cjAMroFPah = false;
      bool bANcpkkiHr = false;
      bool FGDFzRMiZY = false;
      string dANIetaHEV;
      string mMWJrUxYxx;
      string kcTNCdBTmP;
      string OgsRQhpPqx;
      string qViVlTYJts;
      string FOCAJBgAGB;
      string sHUoHGSEsK;
      string dhgzFOsyah;
      string EqYtJAerIP;
      string ApJpEjBtOf;
      string BUQiOXgCuu;
      string HiZXwBhZeH;
      string bZwdKnXquU;
      string Nyiugiaoek;
      string SbxNHRPksC;
      string BaOGEaYmYa;
      string zpGZgIzeqM;
      string arutnzciVs;
      string XmxsTmjcpF;
      string KnQDkcUXfz;
      if(dANIetaHEV == BUQiOXgCuu){RksgaIeUSE = true;}
      else if(BUQiOXgCuu == dANIetaHEV){fdehFILVzP = true;}
      if(mMWJrUxYxx == HiZXwBhZeH){ypQfDMrNGt = true;}
      else if(HiZXwBhZeH == mMWJrUxYxx){huewYotdeD = true;}
      if(kcTNCdBTmP == bZwdKnXquU){YWnkCmbrIL = true;}
      else if(bZwdKnXquU == kcTNCdBTmP){GWxYbhpSRR = true;}
      if(OgsRQhpPqx == Nyiugiaoek){dECWalsQRK = true;}
      else if(Nyiugiaoek == OgsRQhpPqx){IJqPBlMJcS = true;}
      if(qViVlTYJts == SbxNHRPksC){HOJlHTWjzY = true;}
      else if(SbxNHRPksC == qViVlTYJts){KQRgxtFoEn = true;}
      if(FOCAJBgAGB == BaOGEaYmYa){jHRlZuxIen = true;}
      else if(BaOGEaYmYa == FOCAJBgAGB){aXXHHJfFGX = true;}
      if(sHUoHGSEsK == zpGZgIzeqM){gmMGZsmsFQ = true;}
      else if(zpGZgIzeqM == sHUoHGSEsK){SsEhGYEOtm = true;}
      if(dhgzFOsyah == arutnzciVs){SbuulKMCdh = true;}
      if(EqYtJAerIP == XmxsTmjcpF){PqriaWmQwf = true;}
      if(ApJpEjBtOf == KnQDkcUXfz){oklcdUBDLN = true;}
      while(arutnzciVs == dhgzFOsyah){cjAMroFPah = true;}
      while(XmxsTmjcpF == XmxsTmjcpF){bANcpkkiHr = true;}
      while(KnQDkcUXfz == KnQDkcUXfz){FGDFzRMiZY = true;}
      if(RksgaIeUSE == true){RksgaIeUSE = false;}
      if(ypQfDMrNGt == true){ypQfDMrNGt = false;}
      if(YWnkCmbrIL == true){YWnkCmbrIL = false;}
      if(dECWalsQRK == true){dECWalsQRK = false;}
      if(HOJlHTWjzY == true){HOJlHTWjzY = false;}
      if(jHRlZuxIen == true){jHRlZuxIen = false;}
      if(gmMGZsmsFQ == true){gmMGZsmsFQ = false;}
      if(SbuulKMCdh == true){SbuulKMCdh = false;}
      if(PqriaWmQwf == true){PqriaWmQwf = false;}
      if(oklcdUBDLN == true){oklcdUBDLN = false;}
      if(fdehFILVzP == true){fdehFILVzP = false;}
      if(huewYotdeD == true){huewYotdeD = false;}
      if(GWxYbhpSRR == true){GWxYbhpSRR = false;}
      if(IJqPBlMJcS == true){IJqPBlMJcS = false;}
      if(KQRgxtFoEn == true){KQRgxtFoEn = false;}
      if(aXXHHJfFGX == true){aXXHHJfFGX = false;}
      if(SsEhGYEOtm == true){SsEhGYEOtm = false;}
      if(cjAMroFPah == true){cjAMroFPah = false;}
      if(bANcpkkiHr == true){bANcpkkiHr = false;}
      if(FGDFzRMiZY == true){FGDFzRMiZY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UAHMPSJBJN
{ 
  void aBIdNqFuYs()
  { 
      bool etuEekAAhP = false;
      bool EarIIxTMcC = false;
      bool sNyTEAPoMB = false;
      bool sAphrckGed = false;
      bool nSfRdjTMrI = false;
      bool mykxQRwbAe = false;
      bool ULnfWDjJPf = false;
      bool MMgzOaggoT = false;
      bool fDxDOtPsRa = false;
      bool fJGAIceztZ = false;
      bool zJwLwaRlhp = false;
      bool jPlfyROjRb = false;
      bool nqrozCFgpl = false;
      bool uglOTVGkHm = false;
      bool ccKapQWaBp = false;
      bool OthSkIRHLs = false;
      bool UkuwtDcWLb = false;
      bool LcbdzLgQyh = false;
      bool edeAXBzTdL = false;
      bool DyYORrgNgm = false;
      string umxtiEifiq;
      string fPSheBnYMw;
      string rgPIsQunwl;
      string BkIaoLwFeJ;
      string CyUaAypucj;
      string rEcWONWnAS;
      string IujxptHrrT;
      string FisDssLoHt;
      string ZzKLswIkLa;
      string oHEMAHOXjG;
      string qxCJdILZdV;
      string CggGrIkXDs;
      string lWgRexefCk;
      string enFBDbxAhj;
      string khGpYHZyUq;
      string VpTpTUQkef;
      string deXrpNbfCP;
      string LkpSIDPpsW;
      string WgLKPnTOgi;
      string LLUBGGKOzK;
      if(umxtiEifiq == qxCJdILZdV){etuEekAAhP = true;}
      else if(qxCJdILZdV == umxtiEifiq){zJwLwaRlhp = true;}
      if(fPSheBnYMw == CggGrIkXDs){EarIIxTMcC = true;}
      else if(CggGrIkXDs == fPSheBnYMw){jPlfyROjRb = true;}
      if(rgPIsQunwl == lWgRexefCk){sNyTEAPoMB = true;}
      else if(lWgRexefCk == rgPIsQunwl){nqrozCFgpl = true;}
      if(BkIaoLwFeJ == enFBDbxAhj){sAphrckGed = true;}
      else if(enFBDbxAhj == BkIaoLwFeJ){uglOTVGkHm = true;}
      if(CyUaAypucj == khGpYHZyUq){nSfRdjTMrI = true;}
      else if(khGpYHZyUq == CyUaAypucj){ccKapQWaBp = true;}
      if(rEcWONWnAS == VpTpTUQkef){mykxQRwbAe = true;}
      else if(VpTpTUQkef == rEcWONWnAS){OthSkIRHLs = true;}
      if(IujxptHrrT == deXrpNbfCP){ULnfWDjJPf = true;}
      else if(deXrpNbfCP == IujxptHrrT){UkuwtDcWLb = true;}
      if(FisDssLoHt == LkpSIDPpsW){MMgzOaggoT = true;}
      if(ZzKLswIkLa == WgLKPnTOgi){fDxDOtPsRa = true;}
      if(oHEMAHOXjG == LLUBGGKOzK){fJGAIceztZ = true;}
      while(LkpSIDPpsW == FisDssLoHt){LcbdzLgQyh = true;}
      while(WgLKPnTOgi == WgLKPnTOgi){edeAXBzTdL = true;}
      while(LLUBGGKOzK == LLUBGGKOzK){DyYORrgNgm = true;}
      if(etuEekAAhP == true){etuEekAAhP = false;}
      if(EarIIxTMcC == true){EarIIxTMcC = false;}
      if(sNyTEAPoMB == true){sNyTEAPoMB = false;}
      if(sAphrckGed == true){sAphrckGed = false;}
      if(nSfRdjTMrI == true){nSfRdjTMrI = false;}
      if(mykxQRwbAe == true){mykxQRwbAe = false;}
      if(ULnfWDjJPf == true){ULnfWDjJPf = false;}
      if(MMgzOaggoT == true){MMgzOaggoT = false;}
      if(fDxDOtPsRa == true){fDxDOtPsRa = false;}
      if(fJGAIceztZ == true){fJGAIceztZ = false;}
      if(zJwLwaRlhp == true){zJwLwaRlhp = false;}
      if(jPlfyROjRb == true){jPlfyROjRb = false;}
      if(nqrozCFgpl == true){nqrozCFgpl = false;}
      if(uglOTVGkHm == true){uglOTVGkHm = false;}
      if(ccKapQWaBp == true){ccKapQWaBp = false;}
      if(OthSkIRHLs == true){OthSkIRHLs = false;}
      if(UkuwtDcWLb == true){UkuwtDcWLb = false;}
      if(LcbdzLgQyh == true){LcbdzLgQyh = false;}
      if(edeAXBzTdL == true){edeAXBzTdL = false;}
      if(DyYORrgNgm == true){DyYORrgNgm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LCROPWMEBE
{ 
  void JwyaCiIWoL()
  { 
      bool XYdXGPVsGN = false;
      bool mPsTRoZEQm = false;
      bool TQcnqDgGlM = false;
      bool slKTfnMCuk = false;
      bool SpduBBWJsV = false;
      bool YgTsjGwofD = false;
      bool iPHtTBFYmc = false;
      bool bWIfTclhmo = false;
      bool fWMQmMRQjY = false;
      bool rWWqCCijbA = false;
      bool wyVQsCXnYG = false;
      bool TNCpXLCqGH = false;
      bool jooNjFzRdR = false;
      bool sBGlshAwWk = false;
      bool ocqcEdTfTp = false;
      bool zrdTPHIHfn = false;
      bool CFKHMRHPxp = false;
      bool KGTURGxMIF = false;
      bool kTxmRBXlVk = false;
      bool YsPiiiSiPl = false;
      string VuVwDUSgnr;
      string zKDlPaepEC;
      string cnPTjtrHbg;
      string eGrqTJBwWD;
      string sCjmFBQOHe;
      string MZizehfBLJ;
      string cKFGNsRLRG;
      string ZiTBIZDbNi;
      string ccAwTEXsMl;
      string czjMZixcZM;
      string iFwAFdGgpE;
      string dDmcgzJImI;
      string UYyfcZyGaZ;
      string cZBAzXgAqp;
      string ypCHHZLHfZ;
      string YnpQrKGQWf;
      string ezFQbDBldI;
      string SJRwKdWpXD;
      string NpZBAojkIo;
      string RPcLKykkfD;
      if(VuVwDUSgnr == iFwAFdGgpE){XYdXGPVsGN = true;}
      else if(iFwAFdGgpE == VuVwDUSgnr){wyVQsCXnYG = true;}
      if(zKDlPaepEC == dDmcgzJImI){mPsTRoZEQm = true;}
      else if(dDmcgzJImI == zKDlPaepEC){TNCpXLCqGH = true;}
      if(cnPTjtrHbg == UYyfcZyGaZ){TQcnqDgGlM = true;}
      else if(UYyfcZyGaZ == cnPTjtrHbg){jooNjFzRdR = true;}
      if(eGrqTJBwWD == cZBAzXgAqp){slKTfnMCuk = true;}
      else if(cZBAzXgAqp == eGrqTJBwWD){sBGlshAwWk = true;}
      if(sCjmFBQOHe == ypCHHZLHfZ){SpduBBWJsV = true;}
      else if(ypCHHZLHfZ == sCjmFBQOHe){ocqcEdTfTp = true;}
      if(MZizehfBLJ == YnpQrKGQWf){YgTsjGwofD = true;}
      else if(YnpQrKGQWf == MZizehfBLJ){zrdTPHIHfn = true;}
      if(cKFGNsRLRG == ezFQbDBldI){iPHtTBFYmc = true;}
      else if(ezFQbDBldI == cKFGNsRLRG){CFKHMRHPxp = true;}
      if(ZiTBIZDbNi == SJRwKdWpXD){bWIfTclhmo = true;}
      if(ccAwTEXsMl == NpZBAojkIo){fWMQmMRQjY = true;}
      if(czjMZixcZM == RPcLKykkfD){rWWqCCijbA = true;}
      while(SJRwKdWpXD == ZiTBIZDbNi){KGTURGxMIF = true;}
      while(NpZBAojkIo == NpZBAojkIo){kTxmRBXlVk = true;}
      while(RPcLKykkfD == RPcLKykkfD){YsPiiiSiPl = true;}
      if(XYdXGPVsGN == true){XYdXGPVsGN = false;}
      if(mPsTRoZEQm == true){mPsTRoZEQm = false;}
      if(TQcnqDgGlM == true){TQcnqDgGlM = false;}
      if(slKTfnMCuk == true){slKTfnMCuk = false;}
      if(SpduBBWJsV == true){SpduBBWJsV = false;}
      if(YgTsjGwofD == true){YgTsjGwofD = false;}
      if(iPHtTBFYmc == true){iPHtTBFYmc = false;}
      if(bWIfTclhmo == true){bWIfTclhmo = false;}
      if(fWMQmMRQjY == true){fWMQmMRQjY = false;}
      if(rWWqCCijbA == true){rWWqCCijbA = false;}
      if(wyVQsCXnYG == true){wyVQsCXnYG = false;}
      if(TNCpXLCqGH == true){TNCpXLCqGH = false;}
      if(jooNjFzRdR == true){jooNjFzRdR = false;}
      if(sBGlshAwWk == true){sBGlshAwWk = false;}
      if(ocqcEdTfTp == true){ocqcEdTfTp = false;}
      if(zrdTPHIHfn == true){zrdTPHIHfn = false;}
      if(CFKHMRHPxp == true){CFKHMRHPxp = false;}
      if(KGTURGxMIF == true){KGTURGxMIF = false;}
      if(kTxmRBXlVk == true){kTxmRBXlVk = false;}
      if(YsPiiiSiPl == true){YsPiiiSiPl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBXQMSHRNP
{ 
  void pJUaqfCTJA()
  { 
      bool YCKerEYCcp = false;
      bool klKNZSNQEq = false;
      bool ogQSnDBhWS = false;
      bool cqEbCwbTsN = false;
      bool rTeOAZJLQe = false;
      bool EAZamrkqpn = false;
      bool DpfJNtgiKd = false;
      bool psWpzVCBSO = false;
      bool spRqObQdnK = false;
      bool KkcEKBmVBF = false;
      bool saAmnKciaR = false;
      bool ojXbtNXnul = false;
      bool dCtASEPSfx = false;
      bool hgANVRoeDD = false;
      bool yhCWUZNBKx = false;
      bool dzZObpgATi = false;
      bool uKDciIiJGb = false;
      bool XrjqnuAWer = false;
      bool qOIiTiGlle = false;
      bool knLTImdZnM = false;
      string BVVEYfYHOY;
      string kuJNxtrYzU;
      string dMMUlbfoLg;
      string nBFPehlduX;
      string DfaNgRAouC;
      string VTdkToJARw;
      string ziuhjipthP;
      string IOcaQykynU;
      string bqtIKUWTwp;
      string YkMzYTjscx;
      string bGGftHpDTV;
      string DKMxUIomWP;
      string MVxrpWBdBx;
      string NrUprUjOND;
      string dSAZmOYOeQ;
      string exVNjGIOoX;
      string FMBWHKoWEz;
      string YZYTktUWEb;
      string ymykRQVHFl;
      string LUYpxRQdSb;
      if(BVVEYfYHOY == bGGftHpDTV){YCKerEYCcp = true;}
      else if(bGGftHpDTV == BVVEYfYHOY){saAmnKciaR = true;}
      if(kuJNxtrYzU == DKMxUIomWP){klKNZSNQEq = true;}
      else if(DKMxUIomWP == kuJNxtrYzU){ojXbtNXnul = true;}
      if(dMMUlbfoLg == MVxrpWBdBx){ogQSnDBhWS = true;}
      else if(MVxrpWBdBx == dMMUlbfoLg){dCtASEPSfx = true;}
      if(nBFPehlduX == NrUprUjOND){cqEbCwbTsN = true;}
      else if(NrUprUjOND == nBFPehlduX){hgANVRoeDD = true;}
      if(DfaNgRAouC == dSAZmOYOeQ){rTeOAZJLQe = true;}
      else if(dSAZmOYOeQ == DfaNgRAouC){yhCWUZNBKx = true;}
      if(VTdkToJARw == exVNjGIOoX){EAZamrkqpn = true;}
      else if(exVNjGIOoX == VTdkToJARw){dzZObpgATi = true;}
      if(ziuhjipthP == FMBWHKoWEz){DpfJNtgiKd = true;}
      else if(FMBWHKoWEz == ziuhjipthP){uKDciIiJGb = true;}
      if(IOcaQykynU == YZYTktUWEb){psWpzVCBSO = true;}
      if(bqtIKUWTwp == ymykRQVHFl){spRqObQdnK = true;}
      if(YkMzYTjscx == LUYpxRQdSb){KkcEKBmVBF = true;}
      while(YZYTktUWEb == IOcaQykynU){XrjqnuAWer = true;}
      while(ymykRQVHFl == ymykRQVHFl){qOIiTiGlle = true;}
      while(LUYpxRQdSb == LUYpxRQdSb){knLTImdZnM = true;}
      if(YCKerEYCcp == true){YCKerEYCcp = false;}
      if(klKNZSNQEq == true){klKNZSNQEq = false;}
      if(ogQSnDBhWS == true){ogQSnDBhWS = false;}
      if(cqEbCwbTsN == true){cqEbCwbTsN = false;}
      if(rTeOAZJLQe == true){rTeOAZJLQe = false;}
      if(EAZamrkqpn == true){EAZamrkqpn = false;}
      if(DpfJNtgiKd == true){DpfJNtgiKd = false;}
      if(psWpzVCBSO == true){psWpzVCBSO = false;}
      if(spRqObQdnK == true){spRqObQdnK = false;}
      if(KkcEKBmVBF == true){KkcEKBmVBF = false;}
      if(saAmnKciaR == true){saAmnKciaR = false;}
      if(ojXbtNXnul == true){ojXbtNXnul = false;}
      if(dCtASEPSfx == true){dCtASEPSfx = false;}
      if(hgANVRoeDD == true){hgANVRoeDD = false;}
      if(yhCWUZNBKx == true){yhCWUZNBKx = false;}
      if(dzZObpgATi == true){dzZObpgATi = false;}
      if(uKDciIiJGb == true){uKDciIiJGb = false;}
      if(XrjqnuAWer == true){XrjqnuAWer = false;}
      if(qOIiTiGlle == true){qOIiTiGlle = false;}
      if(knLTImdZnM == true){knLTImdZnM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXHSQWFMNL
{ 
  void RAQiFfEBEQ()
  { 
      bool pzMqSOcALU = false;
      bool DNfiOCHdbK = false;
      bool TOGmAFscHX = false;
      bool uRTAjMsfGl = false;
      bool GhzQTWgFmg = false;
      bool CfHHUbsYpN = false;
      bool UzrmZktezC = false;
      bool JaWpEkOpTc = false;
      bool XmpaVOJLfH = false;
      bool TTosQGpMph = false;
      bool bBGjWaIRDi = false;
      bool NCFNohJRQK = false;
      bool bizripkdYx = false;
      bool uCzkAWgFDu = false;
      bool GqHxtQObDh = false;
      bool wYueGsCNBg = false;
      bool oerFmKCTMS = false;
      bool ADNVEjaBxS = false;
      bool bJZpAWGUeG = false;
      bool USEWFbzBJi = false;
      string VZqsngYNHi;
      string hoxCjGWCcp;
      string ypYkNgrptu;
      string tpnyAwDmEc;
      string NmnEiSxFoi;
      string TbOCyfAGfG;
      string oiTMnrAyCm;
      string CixzbLCUBt;
      string jlBKbSblzU;
      string wxHyneSbPp;
      string SyDBgjdOZm;
      string ceEkVChJjV;
      string QNygqFbzLx;
      string rZFLakizdr;
      string nMMMqQrVbl;
      string xIqsZEAVJb;
      string IeDbtCZsJk;
      string ShfqhEBloa;
      string MFWZAihLlW;
      string kNoCjJJjSn;
      if(VZqsngYNHi == SyDBgjdOZm){pzMqSOcALU = true;}
      else if(SyDBgjdOZm == VZqsngYNHi){bBGjWaIRDi = true;}
      if(hoxCjGWCcp == ceEkVChJjV){DNfiOCHdbK = true;}
      else if(ceEkVChJjV == hoxCjGWCcp){NCFNohJRQK = true;}
      if(ypYkNgrptu == QNygqFbzLx){TOGmAFscHX = true;}
      else if(QNygqFbzLx == ypYkNgrptu){bizripkdYx = true;}
      if(tpnyAwDmEc == rZFLakizdr){uRTAjMsfGl = true;}
      else if(rZFLakizdr == tpnyAwDmEc){uCzkAWgFDu = true;}
      if(NmnEiSxFoi == nMMMqQrVbl){GhzQTWgFmg = true;}
      else if(nMMMqQrVbl == NmnEiSxFoi){GqHxtQObDh = true;}
      if(TbOCyfAGfG == xIqsZEAVJb){CfHHUbsYpN = true;}
      else if(xIqsZEAVJb == TbOCyfAGfG){wYueGsCNBg = true;}
      if(oiTMnrAyCm == IeDbtCZsJk){UzrmZktezC = true;}
      else if(IeDbtCZsJk == oiTMnrAyCm){oerFmKCTMS = true;}
      if(CixzbLCUBt == ShfqhEBloa){JaWpEkOpTc = true;}
      if(jlBKbSblzU == MFWZAihLlW){XmpaVOJLfH = true;}
      if(wxHyneSbPp == kNoCjJJjSn){TTosQGpMph = true;}
      while(ShfqhEBloa == CixzbLCUBt){ADNVEjaBxS = true;}
      while(MFWZAihLlW == MFWZAihLlW){bJZpAWGUeG = true;}
      while(kNoCjJJjSn == kNoCjJJjSn){USEWFbzBJi = true;}
      if(pzMqSOcALU == true){pzMqSOcALU = false;}
      if(DNfiOCHdbK == true){DNfiOCHdbK = false;}
      if(TOGmAFscHX == true){TOGmAFscHX = false;}
      if(uRTAjMsfGl == true){uRTAjMsfGl = false;}
      if(GhzQTWgFmg == true){GhzQTWgFmg = false;}
      if(CfHHUbsYpN == true){CfHHUbsYpN = false;}
      if(UzrmZktezC == true){UzrmZktezC = false;}
      if(JaWpEkOpTc == true){JaWpEkOpTc = false;}
      if(XmpaVOJLfH == true){XmpaVOJLfH = false;}
      if(TTosQGpMph == true){TTosQGpMph = false;}
      if(bBGjWaIRDi == true){bBGjWaIRDi = false;}
      if(NCFNohJRQK == true){NCFNohJRQK = false;}
      if(bizripkdYx == true){bizripkdYx = false;}
      if(uCzkAWgFDu == true){uCzkAWgFDu = false;}
      if(GqHxtQObDh == true){GqHxtQObDh = false;}
      if(wYueGsCNBg == true){wYueGsCNBg = false;}
      if(oerFmKCTMS == true){oerFmKCTMS = false;}
      if(ADNVEjaBxS == true){ADNVEjaBxS = false;}
      if(bJZpAWGUeG == true){bJZpAWGUeG = false;}
      if(USEWFbzBJi == true){USEWFbzBJi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTYNMIHFYR
{ 
  void YJedMOEYKM()
  { 
      bool fBzNGnGSiI = false;
      bool xgPscUmfBQ = false;
      bool yoVFRsQPdL = false;
      bool UEdOamVncQ = false;
      bool jbGicClkUt = false;
      bool PVqVXpftuM = false;
      bool WpoXnrDASo = false;
      bool yzCkgWimcP = false;
      bool HfujuzNHqj = false;
      bool HbrQsslhuk = false;
      bool ykSfuPSGnB = false;
      bool HsQfFquFbo = false;
      bool dwIhhWGlqn = false;
      bool jArrQVMOnf = false;
      bool fHSpcNKMKC = false;
      bool ygGFGCcjyY = false;
      bool IfOAQGBYOi = false;
      bool dfQwIWcSFT = false;
      bool LtaopDtllO = false;
      bool scQPWzsRZV = false;
      string kOqLIlZdQe;
      string NdREgYaula;
      string cTERxehGLV;
      string XElrimWscC;
      string cRDLbjkZKY;
      string YXkrdQKYNc;
      string ETRtGIqZVt;
      string CgRixKPrpN;
      string sHumwzTtNR;
      string cyfzyIzJFT;
      string rKEQWrGBuS;
      string BRiAjxYexH;
      string nxMDREBRkn;
      string LGmVUhCdQE;
      string rRzuQKOePB;
      string jULxeuyBzR;
      string poQGHteMeB;
      string tuOrOWyQlG;
      string oVBjEpuoqZ;
      string jBdyODBsmW;
      if(kOqLIlZdQe == rKEQWrGBuS){fBzNGnGSiI = true;}
      else if(rKEQWrGBuS == kOqLIlZdQe){ykSfuPSGnB = true;}
      if(NdREgYaula == BRiAjxYexH){xgPscUmfBQ = true;}
      else if(BRiAjxYexH == NdREgYaula){HsQfFquFbo = true;}
      if(cTERxehGLV == nxMDREBRkn){yoVFRsQPdL = true;}
      else if(nxMDREBRkn == cTERxehGLV){dwIhhWGlqn = true;}
      if(XElrimWscC == LGmVUhCdQE){UEdOamVncQ = true;}
      else if(LGmVUhCdQE == XElrimWscC){jArrQVMOnf = true;}
      if(cRDLbjkZKY == rRzuQKOePB){jbGicClkUt = true;}
      else if(rRzuQKOePB == cRDLbjkZKY){fHSpcNKMKC = true;}
      if(YXkrdQKYNc == jULxeuyBzR){PVqVXpftuM = true;}
      else if(jULxeuyBzR == YXkrdQKYNc){ygGFGCcjyY = true;}
      if(ETRtGIqZVt == poQGHteMeB){WpoXnrDASo = true;}
      else if(poQGHteMeB == ETRtGIqZVt){IfOAQGBYOi = true;}
      if(CgRixKPrpN == tuOrOWyQlG){yzCkgWimcP = true;}
      if(sHumwzTtNR == oVBjEpuoqZ){HfujuzNHqj = true;}
      if(cyfzyIzJFT == jBdyODBsmW){HbrQsslhuk = true;}
      while(tuOrOWyQlG == CgRixKPrpN){dfQwIWcSFT = true;}
      while(oVBjEpuoqZ == oVBjEpuoqZ){LtaopDtllO = true;}
      while(jBdyODBsmW == jBdyODBsmW){scQPWzsRZV = true;}
      if(fBzNGnGSiI == true){fBzNGnGSiI = false;}
      if(xgPscUmfBQ == true){xgPscUmfBQ = false;}
      if(yoVFRsQPdL == true){yoVFRsQPdL = false;}
      if(UEdOamVncQ == true){UEdOamVncQ = false;}
      if(jbGicClkUt == true){jbGicClkUt = false;}
      if(PVqVXpftuM == true){PVqVXpftuM = false;}
      if(WpoXnrDASo == true){WpoXnrDASo = false;}
      if(yzCkgWimcP == true){yzCkgWimcP = false;}
      if(HfujuzNHqj == true){HfujuzNHqj = false;}
      if(HbrQsslhuk == true){HbrQsslhuk = false;}
      if(ykSfuPSGnB == true){ykSfuPSGnB = false;}
      if(HsQfFquFbo == true){HsQfFquFbo = false;}
      if(dwIhhWGlqn == true){dwIhhWGlqn = false;}
      if(jArrQVMOnf == true){jArrQVMOnf = false;}
      if(fHSpcNKMKC == true){fHSpcNKMKC = false;}
      if(ygGFGCcjyY == true){ygGFGCcjyY = false;}
      if(IfOAQGBYOi == true){IfOAQGBYOi = false;}
      if(dfQwIWcSFT == true){dfQwIWcSFT = false;}
      if(LtaopDtllO == true){LtaopDtllO = false;}
      if(scQPWzsRZV == true){scQPWzsRZV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NTOINZQMNC
{ 
  void fStEieSHNN()
  { 
      bool LunsadDEhx = false;
      bool AcOqNcNOxs = false;
      bool agKTokUzwg = false;
      bool cXJyzrEhlB = false;
      bool naXpyISaMw = false;
      bool FdgnMdkTDo = false;
      bool IDHBTcSPqV = false;
      bool XfbwEzIUVg = false;
      bool RtmAayqVlV = false;
      bool HjexrjTWVV = false;
      bool pDipXZCkiN = false;
      bool UPyWWNQHZV = false;
      bool kxdUOmBeDU = false;
      bool flyAqOKwbB = false;
      bool wGlXAqlHZd = false;
      bool SLwAjrYObk = false;
      bool XXgOhiQyfI = false;
      bool DUeXZeLFTW = false;
      bool BsEZBToyPy = false;
      bool pwTqcXZWpR = false;
      string fqtIJDWsDe;
      string oNJCgBxQUd;
      string xVdXUsjicU;
      string bsXcPrURSP;
      string KwZuGDJTCQ;
      string CinrFJNVmQ;
      string SmPiCupfmo;
      string fexETAwiQQ;
      string iQgMRsEfWG;
      string dydCxWfqrK;
      string NcgMjWkiYE;
      string MeEWgCGCQJ;
      string qJJfKhBuHw;
      string UFpGDFiTcu;
      string IUHRtztHUt;
      string QcZiTDTACC;
      string VobcjGnyTa;
      string TmZVAVCqlK;
      string nsaNeqfGmz;
      string lhRaYTsdgm;
      if(fqtIJDWsDe == NcgMjWkiYE){LunsadDEhx = true;}
      else if(NcgMjWkiYE == fqtIJDWsDe){pDipXZCkiN = true;}
      if(oNJCgBxQUd == MeEWgCGCQJ){AcOqNcNOxs = true;}
      else if(MeEWgCGCQJ == oNJCgBxQUd){UPyWWNQHZV = true;}
      if(xVdXUsjicU == qJJfKhBuHw){agKTokUzwg = true;}
      else if(qJJfKhBuHw == xVdXUsjicU){kxdUOmBeDU = true;}
      if(bsXcPrURSP == UFpGDFiTcu){cXJyzrEhlB = true;}
      else if(UFpGDFiTcu == bsXcPrURSP){flyAqOKwbB = true;}
      if(KwZuGDJTCQ == IUHRtztHUt){naXpyISaMw = true;}
      else if(IUHRtztHUt == KwZuGDJTCQ){wGlXAqlHZd = true;}
      if(CinrFJNVmQ == QcZiTDTACC){FdgnMdkTDo = true;}
      else if(QcZiTDTACC == CinrFJNVmQ){SLwAjrYObk = true;}
      if(SmPiCupfmo == VobcjGnyTa){IDHBTcSPqV = true;}
      else if(VobcjGnyTa == SmPiCupfmo){XXgOhiQyfI = true;}
      if(fexETAwiQQ == TmZVAVCqlK){XfbwEzIUVg = true;}
      if(iQgMRsEfWG == nsaNeqfGmz){RtmAayqVlV = true;}
      if(dydCxWfqrK == lhRaYTsdgm){HjexrjTWVV = true;}
      while(TmZVAVCqlK == fexETAwiQQ){DUeXZeLFTW = true;}
      while(nsaNeqfGmz == nsaNeqfGmz){BsEZBToyPy = true;}
      while(lhRaYTsdgm == lhRaYTsdgm){pwTqcXZWpR = true;}
      if(LunsadDEhx == true){LunsadDEhx = false;}
      if(AcOqNcNOxs == true){AcOqNcNOxs = false;}
      if(agKTokUzwg == true){agKTokUzwg = false;}
      if(cXJyzrEhlB == true){cXJyzrEhlB = false;}
      if(naXpyISaMw == true){naXpyISaMw = false;}
      if(FdgnMdkTDo == true){FdgnMdkTDo = false;}
      if(IDHBTcSPqV == true){IDHBTcSPqV = false;}
      if(XfbwEzIUVg == true){XfbwEzIUVg = false;}
      if(RtmAayqVlV == true){RtmAayqVlV = false;}
      if(HjexrjTWVV == true){HjexrjTWVV = false;}
      if(pDipXZCkiN == true){pDipXZCkiN = false;}
      if(UPyWWNQHZV == true){UPyWWNQHZV = false;}
      if(kxdUOmBeDU == true){kxdUOmBeDU = false;}
      if(flyAqOKwbB == true){flyAqOKwbB = false;}
      if(wGlXAqlHZd == true){wGlXAqlHZd = false;}
      if(SLwAjrYObk == true){SLwAjrYObk = false;}
      if(XXgOhiQyfI == true){XXgOhiQyfI = false;}
      if(DUeXZeLFTW == true){DUeXZeLFTW = false;}
      if(BsEZBToyPy == true){BsEZBToyPy = false;}
      if(pwTqcXZWpR == true){pwTqcXZWpR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHNEUSYGFV
{ 
  void VHjNEaFiNC()
  { 
      bool JpTLjCZCIw = false;
      bool ahNLXSlKGw = false;
      bool bEUKXpjutS = false;
      bool OhHhuKCVmI = false;
      bool bdDLJFzJnb = false;
      bool yruzYEUIns = false;
      bool RdHogsZfPM = false;
      bool PPWxUyBJBR = false;
      bool paHRUWlHIq = false;
      bool psgsqyVOdP = false;
      bool eTtaLhUxea = false;
      bool DKHWDqWoTK = false;
      bool GSWYWWicGW = false;
      bool blfkmWgfGl = false;
      bool BobhmflKpz = false;
      bool bftSJMwUEo = false;
      bool zrpIyQdVig = false;
      bool KpigIRpokq = false;
      bool jXmHuwrMbZ = false;
      bool ZLaRmJyTiW = false;
      string JaNlTardSB;
      string FMwllpBRTj;
      string GqwciYQUHg;
      string PcETGsDJDK;
      string UwDEqXNSne;
      string TmBzqSejCu;
      string KWVlkcIbes;
      string lrNJPJnqkL;
      string KxgcMcbEcm;
      string NSGIzxaQTO;
      string PknurbYqjg;
      string enzqkMpsZH;
      string BEzqeTlFJR;
      string iWXVuZJkkj;
      string EjTuIZSOXm;
      string GhqLNLlwQX;
      string oTgRyHQcuL;
      string DEIoDQjEiF;
      string AWhWKBfLHj;
      string mNUMujCCwA;
      if(JaNlTardSB == PknurbYqjg){JpTLjCZCIw = true;}
      else if(PknurbYqjg == JaNlTardSB){eTtaLhUxea = true;}
      if(FMwllpBRTj == enzqkMpsZH){ahNLXSlKGw = true;}
      else if(enzqkMpsZH == FMwllpBRTj){DKHWDqWoTK = true;}
      if(GqwciYQUHg == BEzqeTlFJR){bEUKXpjutS = true;}
      else if(BEzqeTlFJR == GqwciYQUHg){GSWYWWicGW = true;}
      if(PcETGsDJDK == iWXVuZJkkj){OhHhuKCVmI = true;}
      else if(iWXVuZJkkj == PcETGsDJDK){blfkmWgfGl = true;}
      if(UwDEqXNSne == EjTuIZSOXm){bdDLJFzJnb = true;}
      else if(EjTuIZSOXm == UwDEqXNSne){BobhmflKpz = true;}
      if(TmBzqSejCu == GhqLNLlwQX){yruzYEUIns = true;}
      else if(GhqLNLlwQX == TmBzqSejCu){bftSJMwUEo = true;}
      if(KWVlkcIbes == oTgRyHQcuL){RdHogsZfPM = true;}
      else if(oTgRyHQcuL == KWVlkcIbes){zrpIyQdVig = true;}
      if(lrNJPJnqkL == DEIoDQjEiF){PPWxUyBJBR = true;}
      if(KxgcMcbEcm == AWhWKBfLHj){paHRUWlHIq = true;}
      if(NSGIzxaQTO == mNUMujCCwA){psgsqyVOdP = true;}
      while(DEIoDQjEiF == lrNJPJnqkL){KpigIRpokq = true;}
      while(AWhWKBfLHj == AWhWKBfLHj){jXmHuwrMbZ = true;}
      while(mNUMujCCwA == mNUMujCCwA){ZLaRmJyTiW = true;}
      if(JpTLjCZCIw == true){JpTLjCZCIw = false;}
      if(ahNLXSlKGw == true){ahNLXSlKGw = false;}
      if(bEUKXpjutS == true){bEUKXpjutS = false;}
      if(OhHhuKCVmI == true){OhHhuKCVmI = false;}
      if(bdDLJFzJnb == true){bdDLJFzJnb = false;}
      if(yruzYEUIns == true){yruzYEUIns = false;}
      if(RdHogsZfPM == true){RdHogsZfPM = false;}
      if(PPWxUyBJBR == true){PPWxUyBJBR = false;}
      if(paHRUWlHIq == true){paHRUWlHIq = false;}
      if(psgsqyVOdP == true){psgsqyVOdP = false;}
      if(eTtaLhUxea == true){eTtaLhUxea = false;}
      if(DKHWDqWoTK == true){DKHWDqWoTK = false;}
      if(GSWYWWicGW == true){GSWYWWicGW = false;}
      if(blfkmWgfGl == true){blfkmWgfGl = false;}
      if(BobhmflKpz == true){BobhmflKpz = false;}
      if(bftSJMwUEo == true){bftSJMwUEo = false;}
      if(zrpIyQdVig == true){zrpIyQdVig = false;}
      if(KpigIRpokq == true){KpigIRpokq = false;}
      if(jXmHuwrMbZ == true){jXmHuwrMbZ = false;}
      if(ZLaRmJyTiW == true){ZLaRmJyTiW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QBVECDTIXG
{ 
  void aYfLCcfEnp()
  { 
      bool apWPJwNgWQ = false;
      bool OWukIFHitu = false;
      bool sVxUDETBnb = false;
      bool lfDhfQNIqX = false;
      bool hgAHLpkzWs = false;
      bool hgptJErCLF = false;
      bool cLstdiTMEq = false;
      bool rzqVMMVpIN = false;
      bool STeutFpIYa = false;
      bool XKxluVmFcc = false;
      bool WYteAhoTgx = false;
      bool hCtxlIgyAY = false;
      bool sLncTgCEaq = false;
      bool YQNeptZztL = false;
      bool PVabsUQzAm = false;
      bool noFDjLkQKS = false;
      bool fkrpYRoOHq = false;
      bool hgDnJWjLjy = false;
      bool QDEnCiKJue = false;
      bool JJoaeedkDa = false;
      string NKrJJwmDLP;
      string eUoVYnCWOD;
      string fpNRCuKNAA;
      string VwTCYWycpb;
      string EWIWEybWTX;
      string RQRioXwZHN;
      string kYCKshBlwB;
      string pYflzJgpNE;
      string SmtbhFejMB;
      string aXVbqeTxdV;
      string xoaShsjejf;
      string qGMDuxeZcn;
      string CQZuaSCEuU;
      string oiMqHcMbto;
      string VAAgJTLSgt;
      string zsUoSfPfqP;
      string pejPqHsUuR;
      string jDfmSCQskG;
      string GjXAUuOWXa;
      string NfjezpPkpC;
      if(NKrJJwmDLP == xoaShsjejf){apWPJwNgWQ = true;}
      else if(xoaShsjejf == NKrJJwmDLP){WYteAhoTgx = true;}
      if(eUoVYnCWOD == qGMDuxeZcn){OWukIFHitu = true;}
      else if(qGMDuxeZcn == eUoVYnCWOD){hCtxlIgyAY = true;}
      if(fpNRCuKNAA == CQZuaSCEuU){sVxUDETBnb = true;}
      else if(CQZuaSCEuU == fpNRCuKNAA){sLncTgCEaq = true;}
      if(VwTCYWycpb == oiMqHcMbto){lfDhfQNIqX = true;}
      else if(oiMqHcMbto == VwTCYWycpb){YQNeptZztL = true;}
      if(EWIWEybWTX == VAAgJTLSgt){hgAHLpkzWs = true;}
      else if(VAAgJTLSgt == EWIWEybWTX){PVabsUQzAm = true;}
      if(RQRioXwZHN == zsUoSfPfqP){hgptJErCLF = true;}
      else if(zsUoSfPfqP == RQRioXwZHN){noFDjLkQKS = true;}
      if(kYCKshBlwB == pejPqHsUuR){cLstdiTMEq = true;}
      else if(pejPqHsUuR == kYCKshBlwB){fkrpYRoOHq = true;}
      if(pYflzJgpNE == jDfmSCQskG){rzqVMMVpIN = true;}
      if(SmtbhFejMB == GjXAUuOWXa){STeutFpIYa = true;}
      if(aXVbqeTxdV == NfjezpPkpC){XKxluVmFcc = true;}
      while(jDfmSCQskG == pYflzJgpNE){hgDnJWjLjy = true;}
      while(GjXAUuOWXa == GjXAUuOWXa){QDEnCiKJue = true;}
      while(NfjezpPkpC == NfjezpPkpC){JJoaeedkDa = true;}
      if(apWPJwNgWQ == true){apWPJwNgWQ = false;}
      if(OWukIFHitu == true){OWukIFHitu = false;}
      if(sVxUDETBnb == true){sVxUDETBnb = false;}
      if(lfDhfQNIqX == true){lfDhfQNIqX = false;}
      if(hgAHLpkzWs == true){hgAHLpkzWs = false;}
      if(hgptJErCLF == true){hgptJErCLF = false;}
      if(cLstdiTMEq == true){cLstdiTMEq = false;}
      if(rzqVMMVpIN == true){rzqVMMVpIN = false;}
      if(STeutFpIYa == true){STeutFpIYa = false;}
      if(XKxluVmFcc == true){XKxluVmFcc = false;}
      if(WYteAhoTgx == true){WYteAhoTgx = false;}
      if(hCtxlIgyAY == true){hCtxlIgyAY = false;}
      if(sLncTgCEaq == true){sLncTgCEaq = false;}
      if(YQNeptZztL == true){YQNeptZztL = false;}
      if(PVabsUQzAm == true){PVabsUQzAm = false;}
      if(noFDjLkQKS == true){noFDjLkQKS = false;}
      if(fkrpYRoOHq == true){fkrpYRoOHq = false;}
      if(hgDnJWjLjy == true){hgDnJWjLjy = false;}
      if(QDEnCiKJue == true){QDEnCiKJue = false;}
      if(JJoaeedkDa == true){JJoaeedkDa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QNRCEJMBCE
{ 
  void QogQyjRHCr()
  { 
      bool ABeCRJlamP = false;
      bool iNpbzgxYZe = false;
      bool iteBMBABJi = false;
      bool yPiicRphDZ = false;
      bool fCKTZkQjkl = false;
      bool PuBhWGVdpP = false;
      bool IkRDRTeHyh = false;
      bool pPVzzfjKaa = false;
      bool kPPWSDOBLW = false;
      bool wMrmQukGCG = false;
      bool GJkDwAYBip = false;
      bool WKCOesUtkN = false;
      bool EdubldWhiD = false;
      bool udHUUadMaS = false;
      bool dMRVzkJdIX = false;
      bool ZqVnBcOJRR = false;
      bool cqSeusChsD = false;
      bool OISRjrLZbA = false;
      bool TsZKcDITSr = false;
      bool MUtIomtlZG = false;
      string uqGMPMnldQ;
      string GCOQnwWUOk;
      string TRIoZNoMow;
      string tRXBrAOYlu;
      string cLiyFihMRi;
      string MQKWydhQlB;
      string XawhVodMXn;
      string gxiTHHiJip;
      string fbuGjdGADO;
      string RyljWBPBbQ;
      string FUocCOgqPq;
      string uYhwVwepxr;
      string hcJJWiLywF;
      string rggSkKmSDV;
      string wPkMTrPpNa;
      string VYDihbLfGS;
      string ChuJyNqOKL;
      string JMlbwSrxod;
      string SVkViSdxjJ;
      string zHMkSNUbNG;
      if(uqGMPMnldQ == FUocCOgqPq){ABeCRJlamP = true;}
      else if(FUocCOgqPq == uqGMPMnldQ){GJkDwAYBip = true;}
      if(GCOQnwWUOk == uYhwVwepxr){iNpbzgxYZe = true;}
      else if(uYhwVwepxr == GCOQnwWUOk){WKCOesUtkN = true;}
      if(TRIoZNoMow == hcJJWiLywF){iteBMBABJi = true;}
      else if(hcJJWiLywF == TRIoZNoMow){EdubldWhiD = true;}
      if(tRXBrAOYlu == rggSkKmSDV){yPiicRphDZ = true;}
      else if(rggSkKmSDV == tRXBrAOYlu){udHUUadMaS = true;}
      if(cLiyFihMRi == wPkMTrPpNa){fCKTZkQjkl = true;}
      else if(wPkMTrPpNa == cLiyFihMRi){dMRVzkJdIX = true;}
      if(MQKWydhQlB == VYDihbLfGS){PuBhWGVdpP = true;}
      else if(VYDihbLfGS == MQKWydhQlB){ZqVnBcOJRR = true;}
      if(XawhVodMXn == ChuJyNqOKL){IkRDRTeHyh = true;}
      else if(ChuJyNqOKL == XawhVodMXn){cqSeusChsD = true;}
      if(gxiTHHiJip == JMlbwSrxod){pPVzzfjKaa = true;}
      if(fbuGjdGADO == SVkViSdxjJ){kPPWSDOBLW = true;}
      if(RyljWBPBbQ == zHMkSNUbNG){wMrmQukGCG = true;}
      while(JMlbwSrxod == gxiTHHiJip){OISRjrLZbA = true;}
      while(SVkViSdxjJ == SVkViSdxjJ){TsZKcDITSr = true;}
      while(zHMkSNUbNG == zHMkSNUbNG){MUtIomtlZG = true;}
      if(ABeCRJlamP == true){ABeCRJlamP = false;}
      if(iNpbzgxYZe == true){iNpbzgxYZe = false;}
      if(iteBMBABJi == true){iteBMBABJi = false;}
      if(yPiicRphDZ == true){yPiicRphDZ = false;}
      if(fCKTZkQjkl == true){fCKTZkQjkl = false;}
      if(PuBhWGVdpP == true){PuBhWGVdpP = false;}
      if(IkRDRTeHyh == true){IkRDRTeHyh = false;}
      if(pPVzzfjKaa == true){pPVzzfjKaa = false;}
      if(kPPWSDOBLW == true){kPPWSDOBLW = false;}
      if(wMrmQukGCG == true){wMrmQukGCG = false;}
      if(GJkDwAYBip == true){GJkDwAYBip = false;}
      if(WKCOesUtkN == true){WKCOesUtkN = false;}
      if(EdubldWhiD == true){EdubldWhiD = false;}
      if(udHUUadMaS == true){udHUUadMaS = false;}
      if(dMRVzkJdIX == true){dMRVzkJdIX = false;}
      if(ZqVnBcOJRR == true){ZqVnBcOJRR = false;}
      if(cqSeusChsD == true){cqSeusChsD = false;}
      if(OISRjrLZbA == true){OISRjrLZbA = false;}
      if(TsZKcDITSr == true){TsZKcDITSr = false;}
      if(MUtIomtlZG == true){MUtIomtlZG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IDJFVEJNZR
{ 
  void TMgKeOfkJn()
  { 
      bool pEjwhdjIyF = false;
      bool IHICVTqXwR = false;
      bool BZZPOhhOdg = false;
      bool laYmkrgwEB = false;
      bool RMUuYCdiEg = false;
      bool VSEboQdTgz = false;
      bool wUeQSghURc = false;
      bool ltSuAnEeqM = false;
      bool EyJwLTVxyU = false;
      bool NMPEFxhEbq = false;
      bool UIRatbzJbB = false;
      bool MzcUuxKhFz = false;
      bool KkWwPZdOpC = false;
      bool GACzqufhBi = false;
      bool UMUwINjuJI = false;
      bool lzycfjlVLU = false;
      bool xjSZuLxccz = false;
      bool QbgVdyPZnB = false;
      bool oiEhQGCYTH = false;
      bool JKWgljsuBw = false;
      string RQuSKezewZ;
      string MHjnrXOifB;
      string NRPmuCdDHE;
      string niNoxpBTnu;
      string iezUpkFXsR;
      string fsiadAAIXH;
      string AwWrkdttpC;
      string VttjRiRuwJ;
      string wGJoYuzmKx;
      string orufulHHiM;
      string qKgqwkyzIu;
      string hFLOKsmhSp;
      string dGisMczOnf;
      string aKLjRlYRsm;
      string wAdOOjfgUC;
      string zYnrijbmeS;
      string ljKcUXsbwY;
      string TUoetcbTeb;
      string wRslfCVTBg;
      string JllZBMpBtq;
      if(RQuSKezewZ == qKgqwkyzIu){pEjwhdjIyF = true;}
      else if(qKgqwkyzIu == RQuSKezewZ){UIRatbzJbB = true;}
      if(MHjnrXOifB == hFLOKsmhSp){IHICVTqXwR = true;}
      else if(hFLOKsmhSp == MHjnrXOifB){MzcUuxKhFz = true;}
      if(NRPmuCdDHE == dGisMczOnf){BZZPOhhOdg = true;}
      else if(dGisMczOnf == NRPmuCdDHE){KkWwPZdOpC = true;}
      if(niNoxpBTnu == aKLjRlYRsm){laYmkrgwEB = true;}
      else if(aKLjRlYRsm == niNoxpBTnu){GACzqufhBi = true;}
      if(iezUpkFXsR == wAdOOjfgUC){RMUuYCdiEg = true;}
      else if(wAdOOjfgUC == iezUpkFXsR){UMUwINjuJI = true;}
      if(fsiadAAIXH == zYnrijbmeS){VSEboQdTgz = true;}
      else if(zYnrijbmeS == fsiadAAIXH){lzycfjlVLU = true;}
      if(AwWrkdttpC == ljKcUXsbwY){wUeQSghURc = true;}
      else if(ljKcUXsbwY == AwWrkdttpC){xjSZuLxccz = true;}
      if(VttjRiRuwJ == TUoetcbTeb){ltSuAnEeqM = true;}
      if(wGJoYuzmKx == wRslfCVTBg){EyJwLTVxyU = true;}
      if(orufulHHiM == JllZBMpBtq){NMPEFxhEbq = true;}
      while(TUoetcbTeb == VttjRiRuwJ){QbgVdyPZnB = true;}
      while(wRslfCVTBg == wRslfCVTBg){oiEhQGCYTH = true;}
      while(JllZBMpBtq == JllZBMpBtq){JKWgljsuBw = true;}
      if(pEjwhdjIyF == true){pEjwhdjIyF = false;}
      if(IHICVTqXwR == true){IHICVTqXwR = false;}
      if(BZZPOhhOdg == true){BZZPOhhOdg = false;}
      if(laYmkrgwEB == true){laYmkrgwEB = false;}
      if(RMUuYCdiEg == true){RMUuYCdiEg = false;}
      if(VSEboQdTgz == true){VSEboQdTgz = false;}
      if(wUeQSghURc == true){wUeQSghURc = false;}
      if(ltSuAnEeqM == true){ltSuAnEeqM = false;}
      if(EyJwLTVxyU == true){EyJwLTVxyU = false;}
      if(NMPEFxhEbq == true){NMPEFxhEbq = false;}
      if(UIRatbzJbB == true){UIRatbzJbB = false;}
      if(MzcUuxKhFz == true){MzcUuxKhFz = false;}
      if(KkWwPZdOpC == true){KkWwPZdOpC = false;}
      if(GACzqufhBi == true){GACzqufhBi = false;}
      if(UMUwINjuJI == true){UMUwINjuJI = false;}
      if(lzycfjlVLU == true){lzycfjlVLU = false;}
      if(xjSZuLxccz == true){xjSZuLxccz = false;}
      if(QbgVdyPZnB == true){QbgVdyPZnB = false;}
      if(oiEhQGCYTH == true){oiEhQGCYTH = false;}
      if(JKWgljsuBw == true){JKWgljsuBw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MKXMASDIWV
{ 
  void rDPsVHkQKS()
  { 
      bool DgHYAKPtHK = false;
      bool wYrniHWktp = false;
      bool wDnVWLnVeC = false;
      bool hMtlxSNALS = false;
      bool ThZnJyPOHq = false;
      bool GjGfezskBo = false;
      bool WsOEbjdFpP = false;
      bool sWYbVNdzMX = false;
      bool wYOmwyFOHy = false;
      bool ZcyWuZTUMY = false;
      bool TJXqxjKeJQ = false;
      bool VsXcrxeaIc = false;
      bool ePyroQXBfw = false;
      bool tImnDmAWoM = false;
      bool maEqcgFUdy = false;
      bool trMitEKfCg = false;
      bool LIyNVMGiYF = false;
      bool wIkuoDLHPI = false;
      bool KDXhCCuDtz = false;
      bool bUUIAebqVP = false;
      string stGbkrypzo;
      string hQjRxINUpQ;
      string ElaHWMhnYd;
      string VKBpgNTfAJ;
      string xfDMILwDPt;
      string QILXJHTzEY;
      string KJRVSWPskj;
      string ogTgTYhNyL;
      string QdYeMNzcfY;
      string tUbbzmOgsl;
      string wCRfEineEj;
      string YFArIfklIF;
      string XlMMpUFrgf;
      string KAUMPNMsZd;
      string YTYuznTjTT;
      string CbYmNJpFoj;
      string duyXYXkmbt;
      string SqMefDMQMB;
      string AVYMdibgyF;
      string XHDpzcUAVa;
      if(stGbkrypzo == wCRfEineEj){DgHYAKPtHK = true;}
      else if(wCRfEineEj == stGbkrypzo){TJXqxjKeJQ = true;}
      if(hQjRxINUpQ == YFArIfklIF){wYrniHWktp = true;}
      else if(YFArIfklIF == hQjRxINUpQ){VsXcrxeaIc = true;}
      if(ElaHWMhnYd == XlMMpUFrgf){wDnVWLnVeC = true;}
      else if(XlMMpUFrgf == ElaHWMhnYd){ePyroQXBfw = true;}
      if(VKBpgNTfAJ == KAUMPNMsZd){hMtlxSNALS = true;}
      else if(KAUMPNMsZd == VKBpgNTfAJ){tImnDmAWoM = true;}
      if(xfDMILwDPt == YTYuznTjTT){ThZnJyPOHq = true;}
      else if(YTYuznTjTT == xfDMILwDPt){maEqcgFUdy = true;}
      if(QILXJHTzEY == CbYmNJpFoj){GjGfezskBo = true;}
      else if(CbYmNJpFoj == QILXJHTzEY){trMitEKfCg = true;}
      if(KJRVSWPskj == duyXYXkmbt){WsOEbjdFpP = true;}
      else if(duyXYXkmbt == KJRVSWPskj){LIyNVMGiYF = true;}
      if(ogTgTYhNyL == SqMefDMQMB){sWYbVNdzMX = true;}
      if(QdYeMNzcfY == AVYMdibgyF){wYOmwyFOHy = true;}
      if(tUbbzmOgsl == XHDpzcUAVa){ZcyWuZTUMY = true;}
      while(SqMefDMQMB == ogTgTYhNyL){wIkuoDLHPI = true;}
      while(AVYMdibgyF == AVYMdibgyF){KDXhCCuDtz = true;}
      while(XHDpzcUAVa == XHDpzcUAVa){bUUIAebqVP = true;}
      if(DgHYAKPtHK == true){DgHYAKPtHK = false;}
      if(wYrniHWktp == true){wYrniHWktp = false;}
      if(wDnVWLnVeC == true){wDnVWLnVeC = false;}
      if(hMtlxSNALS == true){hMtlxSNALS = false;}
      if(ThZnJyPOHq == true){ThZnJyPOHq = false;}
      if(GjGfezskBo == true){GjGfezskBo = false;}
      if(WsOEbjdFpP == true){WsOEbjdFpP = false;}
      if(sWYbVNdzMX == true){sWYbVNdzMX = false;}
      if(wYOmwyFOHy == true){wYOmwyFOHy = false;}
      if(ZcyWuZTUMY == true){ZcyWuZTUMY = false;}
      if(TJXqxjKeJQ == true){TJXqxjKeJQ = false;}
      if(VsXcrxeaIc == true){VsXcrxeaIc = false;}
      if(ePyroQXBfw == true){ePyroQXBfw = false;}
      if(tImnDmAWoM == true){tImnDmAWoM = false;}
      if(maEqcgFUdy == true){maEqcgFUdy = false;}
      if(trMitEKfCg == true){trMitEKfCg = false;}
      if(LIyNVMGiYF == true){LIyNVMGiYF = false;}
      if(wIkuoDLHPI == true){wIkuoDLHPI = false;}
      if(KDXhCCuDtz == true){KDXhCCuDtz = false;}
      if(bUUIAebqVP == true){bUUIAebqVP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UNBVQCMUWZ
{ 
  void qzFtDcwBJX()
  { 
      bool nfweGONpqa = false;
      bool OWmRkjKZRs = false;
      bool kMlTfjeSsL = false;
      bool kzajzDpemu = false;
      bool SBXwBRjdQD = false;
      bool PfUKRbtbzW = false;
      bool juwepOwCSg = false;
      bool sflWZjnpSN = false;
      bool AACpwEeQSX = false;
      bool JNeQKXFrFm = false;
      bool UgLiJisyjh = false;
      bool mDJkWjsGhl = false;
      bool jejuXeAVLC = false;
      bool dwkfsSnSfM = false;
      bool KffkjGEtta = false;
      bool dyKTCpxQKd = false;
      bool iXlhDpScrD = false;
      bool uZZUaDyyKQ = false;
      bool aFbkXflRcC = false;
      bool VXHBdltyhs = false;
      string JoJpCgjshe;
      string jgfooeGtxW;
      string dlTjSogzgp;
      string YLmCwEPFYT;
      string DmGQIxnmqM;
      string pzGuhXVZWN;
      string zjMqFXscrj;
      string PBUcSqeCaU;
      string BsHTzYEqUY;
      string hohLUSaPKk;
      string DKtGwoddbp;
      string rTzBLGbrqg;
      string SCITCaSJIA;
      string PProRqyBXK;
      string taOdfOpfzO;
      string piXcSBBaEV;
      string WUUbacaJjU;
      string HaUglqmemm;
      string jlJtJgrOWP;
      string oXwBmZGmDC;
      if(JoJpCgjshe == DKtGwoddbp){nfweGONpqa = true;}
      else if(DKtGwoddbp == JoJpCgjshe){UgLiJisyjh = true;}
      if(jgfooeGtxW == rTzBLGbrqg){OWmRkjKZRs = true;}
      else if(rTzBLGbrqg == jgfooeGtxW){mDJkWjsGhl = true;}
      if(dlTjSogzgp == SCITCaSJIA){kMlTfjeSsL = true;}
      else if(SCITCaSJIA == dlTjSogzgp){jejuXeAVLC = true;}
      if(YLmCwEPFYT == PProRqyBXK){kzajzDpemu = true;}
      else if(PProRqyBXK == YLmCwEPFYT){dwkfsSnSfM = true;}
      if(DmGQIxnmqM == taOdfOpfzO){SBXwBRjdQD = true;}
      else if(taOdfOpfzO == DmGQIxnmqM){KffkjGEtta = true;}
      if(pzGuhXVZWN == piXcSBBaEV){PfUKRbtbzW = true;}
      else if(piXcSBBaEV == pzGuhXVZWN){dyKTCpxQKd = true;}
      if(zjMqFXscrj == WUUbacaJjU){juwepOwCSg = true;}
      else if(WUUbacaJjU == zjMqFXscrj){iXlhDpScrD = true;}
      if(PBUcSqeCaU == HaUglqmemm){sflWZjnpSN = true;}
      if(BsHTzYEqUY == jlJtJgrOWP){AACpwEeQSX = true;}
      if(hohLUSaPKk == oXwBmZGmDC){JNeQKXFrFm = true;}
      while(HaUglqmemm == PBUcSqeCaU){uZZUaDyyKQ = true;}
      while(jlJtJgrOWP == jlJtJgrOWP){aFbkXflRcC = true;}
      while(oXwBmZGmDC == oXwBmZGmDC){VXHBdltyhs = true;}
      if(nfweGONpqa == true){nfweGONpqa = false;}
      if(OWmRkjKZRs == true){OWmRkjKZRs = false;}
      if(kMlTfjeSsL == true){kMlTfjeSsL = false;}
      if(kzajzDpemu == true){kzajzDpemu = false;}
      if(SBXwBRjdQD == true){SBXwBRjdQD = false;}
      if(PfUKRbtbzW == true){PfUKRbtbzW = false;}
      if(juwepOwCSg == true){juwepOwCSg = false;}
      if(sflWZjnpSN == true){sflWZjnpSN = false;}
      if(AACpwEeQSX == true){AACpwEeQSX = false;}
      if(JNeQKXFrFm == true){JNeQKXFrFm = false;}
      if(UgLiJisyjh == true){UgLiJisyjh = false;}
      if(mDJkWjsGhl == true){mDJkWjsGhl = false;}
      if(jejuXeAVLC == true){jejuXeAVLC = false;}
      if(dwkfsSnSfM == true){dwkfsSnSfM = false;}
      if(KffkjGEtta == true){KffkjGEtta = false;}
      if(dyKTCpxQKd == true){dyKTCpxQKd = false;}
      if(iXlhDpScrD == true){iXlhDpScrD = false;}
      if(uZZUaDyyKQ == true){uZZUaDyyKQ = false;}
      if(aFbkXflRcC == true){aFbkXflRcC = false;}
      if(VXHBdltyhs == true){VXHBdltyhs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WZKZAIYQAK
{ 
  void FuZsRmlCeK()
  { 
      bool mIbRYuZiLs = false;
      bool oSIBdZRpcH = false;
      bool DKBejDBmyg = false;
      bool ZlhpfajUUf = false;
      bool AVJwJYxFxA = false;
      bool iJjEmcHwgU = false;
      bool tlkdSCjSUD = false;
      bool pwUxGgAFVL = false;
      bool GupxyQCdCC = false;
      bool TmnAkNkecG = false;
      bool neksKlnlyF = false;
      bool cBaVOywmeB = false;
      bool AGPRiCITLr = false;
      bool wUbOWaKwlM = false;
      bool bPewZRLSlm = false;
      bool RxzbGgPSKI = false;
      bool cUaFJHZMym = false;
      bool mAASZkaTrQ = false;
      bool pohXayVAIp = false;
      bool LrldiHnZmS = false;
      string eGDlfSPJQP;
      string mggALMeXif;
      string wDLUXqstRN;
      string jeKAyJfmPP;
      string KmwNjciZKd;
      string wsgHHbtiNo;
      string ZUrCeHVgCC;
      string frHSVJGyju;
      string HSjmRqxDrV;
      string PxYapotshc;
      string HCWHxEkNkx;
      string VwySgGkFkn;
      string JRogmiSfcf;
      string PMPHnFwbpM;
      string FjStzTzGsi;
      string EoHtSoNpUO;
      string lEjEhIfpdb;
      string KIOYhZztgT;
      string jLmtbaFVoz;
      string qGHbaAzNLq;
      if(eGDlfSPJQP == HCWHxEkNkx){mIbRYuZiLs = true;}
      else if(HCWHxEkNkx == eGDlfSPJQP){neksKlnlyF = true;}
      if(mggALMeXif == VwySgGkFkn){oSIBdZRpcH = true;}
      else if(VwySgGkFkn == mggALMeXif){cBaVOywmeB = true;}
      if(wDLUXqstRN == JRogmiSfcf){DKBejDBmyg = true;}
      else if(JRogmiSfcf == wDLUXqstRN){AGPRiCITLr = true;}
      if(jeKAyJfmPP == PMPHnFwbpM){ZlhpfajUUf = true;}
      else if(PMPHnFwbpM == jeKAyJfmPP){wUbOWaKwlM = true;}
      if(KmwNjciZKd == FjStzTzGsi){AVJwJYxFxA = true;}
      else if(FjStzTzGsi == KmwNjciZKd){bPewZRLSlm = true;}
      if(wsgHHbtiNo == EoHtSoNpUO){iJjEmcHwgU = true;}
      else if(EoHtSoNpUO == wsgHHbtiNo){RxzbGgPSKI = true;}
      if(ZUrCeHVgCC == lEjEhIfpdb){tlkdSCjSUD = true;}
      else if(lEjEhIfpdb == ZUrCeHVgCC){cUaFJHZMym = true;}
      if(frHSVJGyju == KIOYhZztgT){pwUxGgAFVL = true;}
      if(HSjmRqxDrV == jLmtbaFVoz){GupxyQCdCC = true;}
      if(PxYapotshc == qGHbaAzNLq){TmnAkNkecG = true;}
      while(KIOYhZztgT == frHSVJGyju){mAASZkaTrQ = true;}
      while(jLmtbaFVoz == jLmtbaFVoz){pohXayVAIp = true;}
      while(qGHbaAzNLq == qGHbaAzNLq){LrldiHnZmS = true;}
      if(mIbRYuZiLs == true){mIbRYuZiLs = false;}
      if(oSIBdZRpcH == true){oSIBdZRpcH = false;}
      if(DKBejDBmyg == true){DKBejDBmyg = false;}
      if(ZlhpfajUUf == true){ZlhpfajUUf = false;}
      if(AVJwJYxFxA == true){AVJwJYxFxA = false;}
      if(iJjEmcHwgU == true){iJjEmcHwgU = false;}
      if(tlkdSCjSUD == true){tlkdSCjSUD = false;}
      if(pwUxGgAFVL == true){pwUxGgAFVL = false;}
      if(GupxyQCdCC == true){GupxyQCdCC = false;}
      if(TmnAkNkecG == true){TmnAkNkecG = false;}
      if(neksKlnlyF == true){neksKlnlyF = false;}
      if(cBaVOywmeB == true){cBaVOywmeB = false;}
      if(AGPRiCITLr == true){AGPRiCITLr = false;}
      if(wUbOWaKwlM == true){wUbOWaKwlM = false;}
      if(bPewZRLSlm == true){bPewZRLSlm = false;}
      if(RxzbGgPSKI == true){RxzbGgPSKI = false;}
      if(cUaFJHZMym == true){cUaFJHZMym = false;}
      if(mAASZkaTrQ == true){mAASZkaTrQ = false;}
      if(pohXayVAIp == true){pohXayVAIp = false;}
      if(LrldiHnZmS == true){LrldiHnZmS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BSWIYLJLAS
{ 
  void oUsqJIAmmT()
  { 
      bool tbVamrBpkO = false;
      bool hauDBojEYH = false;
      bool rlEwEmGZaj = false;
      bool txJzailuDD = false;
      bool cWglnqMYRx = false;
      bool MPDorHXYVz = false;
      bool laPBTkQubS = false;
      bool DoAVdUFSIM = false;
      bool ahHcWdtTGS = false;
      bool LMYDRBHeRD = false;
      bool aQwztXOgKX = false;
      bool CEQIYDTldp = false;
      bool pxoJGpPwEc = false;
      bool MZBFlKlIiz = false;
      bool PMJiQGuPeN = false;
      bool hVBbMcalrE = false;
      bool IRchKbDLVN = false;
      bool RKDeZcnGsA = false;
      bool tzRptqYYrJ = false;
      bool izQdpyjaXn = false;
      string stLQLKVLiN;
      string BgbwfjeycU;
      string ZAMxGVltzG;
      string upSuHWcwJn;
      string lgeWPuBtCM;
      string bPHbCsgOJo;
      string YaMbRLOgoJ;
      string GinnhrUpgL;
      string TqrldfiprO;
      string oOlTPKTCEE;
      string fUFrFsaTsJ;
      string XpgyVgiZyl;
      string cXnZTrwUYX;
      string XSkbeylAgj;
      string EOxhpzgnyh;
      string btESbIgeXM;
      string xGuUkFEESW;
      string uisNgNZGjU;
      string LHWpwdNRAW;
      string RHbTmxTbwj;
      if(stLQLKVLiN == fUFrFsaTsJ){tbVamrBpkO = true;}
      else if(fUFrFsaTsJ == stLQLKVLiN){aQwztXOgKX = true;}
      if(BgbwfjeycU == XpgyVgiZyl){hauDBojEYH = true;}
      else if(XpgyVgiZyl == BgbwfjeycU){CEQIYDTldp = true;}
      if(ZAMxGVltzG == cXnZTrwUYX){rlEwEmGZaj = true;}
      else if(cXnZTrwUYX == ZAMxGVltzG){pxoJGpPwEc = true;}
      if(upSuHWcwJn == XSkbeylAgj){txJzailuDD = true;}
      else if(XSkbeylAgj == upSuHWcwJn){MZBFlKlIiz = true;}
      if(lgeWPuBtCM == EOxhpzgnyh){cWglnqMYRx = true;}
      else if(EOxhpzgnyh == lgeWPuBtCM){PMJiQGuPeN = true;}
      if(bPHbCsgOJo == btESbIgeXM){MPDorHXYVz = true;}
      else if(btESbIgeXM == bPHbCsgOJo){hVBbMcalrE = true;}
      if(YaMbRLOgoJ == xGuUkFEESW){laPBTkQubS = true;}
      else if(xGuUkFEESW == YaMbRLOgoJ){IRchKbDLVN = true;}
      if(GinnhrUpgL == uisNgNZGjU){DoAVdUFSIM = true;}
      if(TqrldfiprO == LHWpwdNRAW){ahHcWdtTGS = true;}
      if(oOlTPKTCEE == RHbTmxTbwj){LMYDRBHeRD = true;}
      while(uisNgNZGjU == GinnhrUpgL){RKDeZcnGsA = true;}
      while(LHWpwdNRAW == LHWpwdNRAW){tzRptqYYrJ = true;}
      while(RHbTmxTbwj == RHbTmxTbwj){izQdpyjaXn = true;}
      if(tbVamrBpkO == true){tbVamrBpkO = false;}
      if(hauDBojEYH == true){hauDBojEYH = false;}
      if(rlEwEmGZaj == true){rlEwEmGZaj = false;}
      if(txJzailuDD == true){txJzailuDD = false;}
      if(cWglnqMYRx == true){cWglnqMYRx = false;}
      if(MPDorHXYVz == true){MPDorHXYVz = false;}
      if(laPBTkQubS == true){laPBTkQubS = false;}
      if(DoAVdUFSIM == true){DoAVdUFSIM = false;}
      if(ahHcWdtTGS == true){ahHcWdtTGS = false;}
      if(LMYDRBHeRD == true){LMYDRBHeRD = false;}
      if(aQwztXOgKX == true){aQwztXOgKX = false;}
      if(CEQIYDTldp == true){CEQIYDTldp = false;}
      if(pxoJGpPwEc == true){pxoJGpPwEc = false;}
      if(MZBFlKlIiz == true){MZBFlKlIiz = false;}
      if(PMJiQGuPeN == true){PMJiQGuPeN = false;}
      if(hVBbMcalrE == true){hVBbMcalrE = false;}
      if(IRchKbDLVN == true){IRchKbDLVN = false;}
      if(RKDeZcnGsA == true){RKDeZcnGsA = false;}
      if(tzRptqYYrJ == true){tzRptqYYrJ = false;}
      if(izQdpyjaXn == true){izQdpyjaXn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GVOMZZONEX
{ 
  void kOafgkcYkB()
  { 
      bool WrTTuQRwEa = false;
      bool swcmffJabG = false;
      bool UBiHoOZdlr = false;
      bool UTLDjqoZCL = false;
      bool qbfOOCMqnr = false;
      bool tRRPtUJMeg = false;
      bool qmKMGZjYDn = false;
      bool qiYPOrUTrl = false;
      bool BiptxCCwJO = false;
      bool hcuUUDRTIo = false;
      bool RmnABLsBAB = false;
      bool zoUreIxQPE = false;
      bool XnPnGNnDtK = false;
      bool aBKCTNupsl = false;
      bool IAuHPrICpM = false;
      bool GBEERdXztm = false;
      bool WpGoayeRYQ = false;
      bool MHXcuWsIYN = false;
      bool FlNhEYxFkp = false;
      bool puwFORsFgQ = false;
      string xagRWEKVJL;
      string ORkhuneCkP;
      string HLLgIYAtln;
      string uxFoUxSXYu;
      string PiBUjcumJk;
      string phKDOkOzJx;
      string EPiVPRMuNy;
      string UHcozYKpwe;
      string dMkAxMmBaj;
      string hTNaqAzeES;
      string QzZLQiFVDo;
      string ZYCdSqdiXD;
      string eKTcQBsBxz;
      string ZfldOemZjN;
      string HQxlJJQjHA;
      string VQGAnFewtP;
      string oDXEPtlYPn;
      string EEyKwNMhTG;
      string jJtxcIYkoI;
      string zpeTXEssVP;
      if(xagRWEKVJL == QzZLQiFVDo){WrTTuQRwEa = true;}
      else if(QzZLQiFVDo == xagRWEKVJL){RmnABLsBAB = true;}
      if(ORkhuneCkP == ZYCdSqdiXD){swcmffJabG = true;}
      else if(ZYCdSqdiXD == ORkhuneCkP){zoUreIxQPE = true;}
      if(HLLgIYAtln == eKTcQBsBxz){UBiHoOZdlr = true;}
      else if(eKTcQBsBxz == HLLgIYAtln){XnPnGNnDtK = true;}
      if(uxFoUxSXYu == ZfldOemZjN){UTLDjqoZCL = true;}
      else if(ZfldOemZjN == uxFoUxSXYu){aBKCTNupsl = true;}
      if(PiBUjcumJk == HQxlJJQjHA){qbfOOCMqnr = true;}
      else if(HQxlJJQjHA == PiBUjcumJk){IAuHPrICpM = true;}
      if(phKDOkOzJx == VQGAnFewtP){tRRPtUJMeg = true;}
      else if(VQGAnFewtP == phKDOkOzJx){GBEERdXztm = true;}
      if(EPiVPRMuNy == oDXEPtlYPn){qmKMGZjYDn = true;}
      else if(oDXEPtlYPn == EPiVPRMuNy){WpGoayeRYQ = true;}
      if(UHcozYKpwe == EEyKwNMhTG){qiYPOrUTrl = true;}
      if(dMkAxMmBaj == jJtxcIYkoI){BiptxCCwJO = true;}
      if(hTNaqAzeES == zpeTXEssVP){hcuUUDRTIo = true;}
      while(EEyKwNMhTG == UHcozYKpwe){MHXcuWsIYN = true;}
      while(jJtxcIYkoI == jJtxcIYkoI){FlNhEYxFkp = true;}
      while(zpeTXEssVP == zpeTXEssVP){puwFORsFgQ = true;}
      if(WrTTuQRwEa == true){WrTTuQRwEa = false;}
      if(swcmffJabG == true){swcmffJabG = false;}
      if(UBiHoOZdlr == true){UBiHoOZdlr = false;}
      if(UTLDjqoZCL == true){UTLDjqoZCL = false;}
      if(qbfOOCMqnr == true){qbfOOCMqnr = false;}
      if(tRRPtUJMeg == true){tRRPtUJMeg = false;}
      if(qmKMGZjYDn == true){qmKMGZjYDn = false;}
      if(qiYPOrUTrl == true){qiYPOrUTrl = false;}
      if(BiptxCCwJO == true){BiptxCCwJO = false;}
      if(hcuUUDRTIo == true){hcuUUDRTIo = false;}
      if(RmnABLsBAB == true){RmnABLsBAB = false;}
      if(zoUreIxQPE == true){zoUreIxQPE = false;}
      if(XnPnGNnDtK == true){XnPnGNnDtK = false;}
      if(aBKCTNupsl == true){aBKCTNupsl = false;}
      if(IAuHPrICpM == true){IAuHPrICpM = false;}
      if(GBEERdXztm == true){GBEERdXztm = false;}
      if(WpGoayeRYQ == true){WpGoayeRYQ = false;}
      if(MHXcuWsIYN == true){MHXcuWsIYN = false;}
      if(FlNhEYxFkp == true){FlNhEYxFkp = false;}
      if(puwFORsFgQ == true){puwFORsFgQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OKDAWMKXRS
{ 
  void IiEbpcUXxa()
  { 
      bool HcjOBowCBr = false;
      bool TOGnKgNpsc = false;
      bool oKEHlbLlVg = false;
      bool fLXCtEyKCS = false;
      bool VLytHSPdVz = false;
      bool zNacaxYbbY = false;
      bool cKfTMIpEsG = false;
      bool hDmZGcLJAT = false;
      bool LgQWhRjtax = false;
      bool eWhcoLfehy = false;
      bool bLkOQuZAVx = false;
      bool kPaINwtIku = false;
      bool YwcwbKVKku = false;
      bool xgbBqzwBFl = false;
      bool qiYdMPuYOs = false;
      bool RXsmZfhnmG = false;
      bool ZPPaADmZRN = false;
      bool zrCyDoWzjL = false;
      bool PwuqcZmobK = false;
      bool QHNzMaSxdI = false;
      string XLqZKIVBZM;
      string WMGJHfDwEp;
      string KhSMjXBSoN;
      string WtKyfQEUNE;
      string JTNfmFcpBV;
      string AcyKTprepm;
      string HDLLocCHcq;
      string bhhAgpTlYe;
      string tKRTNtuzdp;
      string XZeawFIBqJ;
      string CUNJtRtxcd;
      string VFFLrwlrxu;
      string hCdmTBCHDb;
      string hRuObYxHYu;
      string AxVATRTThA;
      string TPEwbAqZor;
      string PmsBuDKqiT;
      string zdSCtjfcSB;
      string giYDISNzmb;
      string gWRgfNDUFQ;
      if(XLqZKIVBZM == CUNJtRtxcd){HcjOBowCBr = true;}
      else if(CUNJtRtxcd == XLqZKIVBZM){bLkOQuZAVx = true;}
      if(WMGJHfDwEp == VFFLrwlrxu){TOGnKgNpsc = true;}
      else if(VFFLrwlrxu == WMGJHfDwEp){kPaINwtIku = true;}
      if(KhSMjXBSoN == hCdmTBCHDb){oKEHlbLlVg = true;}
      else if(hCdmTBCHDb == KhSMjXBSoN){YwcwbKVKku = true;}
      if(WtKyfQEUNE == hRuObYxHYu){fLXCtEyKCS = true;}
      else if(hRuObYxHYu == WtKyfQEUNE){xgbBqzwBFl = true;}
      if(JTNfmFcpBV == AxVATRTThA){VLytHSPdVz = true;}
      else if(AxVATRTThA == JTNfmFcpBV){qiYdMPuYOs = true;}
      if(AcyKTprepm == TPEwbAqZor){zNacaxYbbY = true;}
      else if(TPEwbAqZor == AcyKTprepm){RXsmZfhnmG = true;}
      if(HDLLocCHcq == PmsBuDKqiT){cKfTMIpEsG = true;}
      else if(PmsBuDKqiT == HDLLocCHcq){ZPPaADmZRN = true;}
      if(bhhAgpTlYe == zdSCtjfcSB){hDmZGcLJAT = true;}
      if(tKRTNtuzdp == giYDISNzmb){LgQWhRjtax = true;}
      if(XZeawFIBqJ == gWRgfNDUFQ){eWhcoLfehy = true;}
      while(zdSCtjfcSB == bhhAgpTlYe){zrCyDoWzjL = true;}
      while(giYDISNzmb == giYDISNzmb){PwuqcZmobK = true;}
      while(gWRgfNDUFQ == gWRgfNDUFQ){QHNzMaSxdI = true;}
      if(HcjOBowCBr == true){HcjOBowCBr = false;}
      if(TOGnKgNpsc == true){TOGnKgNpsc = false;}
      if(oKEHlbLlVg == true){oKEHlbLlVg = false;}
      if(fLXCtEyKCS == true){fLXCtEyKCS = false;}
      if(VLytHSPdVz == true){VLytHSPdVz = false;}
      if(zNacaxYbbY == true){zNacaxYbbY = false;}
      if(cKfTMIpEsG == true){cKfTMIpEsG = false;}
      if(hDmZGcLJAT == true){hDmZGcLJAT = false;}
      if(LgQWhRjtax == true){LgQWhRjtax = false;}
      if(eWhcoLfehy == true){eWhcoLfehy = false;}
      if(bLkOQuZAVx == true){bLkOQuZAVx = false;}
      if(kPaINwtIku == true){kPaINwtIku = false;}
      if(YwcwbKVKku == true){YwcwbKVKku = false;}
      if(xgbBqzwBFl == true){xgbBqzwBFl = false;}
      if(qiYdMPuYOs == true){qiYdMPuYOs = false;}
      if(RXsmZfhnmG == true){RXsmZfhnmG = false;}
      if(ZPPaADmZRN == true){ZPPaADmZRN = false;}
      if(zrCyDoWzjL == true){zrCyDoWzjL = false;}
      if(PwuqcZmobK == true){PwuqcZmobK = false;}
      if(QHNzMaSxdI == true){QHNzMaSxdI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYMTKDYLCY
{ 
  void sCQjtsyjqR()
  { 
      bool cykteaDncV = false;
      bool WkHRtqmaal = false;
      bool cfJpNSiwqc = false;
      bool YYLtHkktQs = false;
      bool LVFKeJPoHc = false;
      bool OYYZExnugL = false;
      bool qHxAxxZMKI = false;
      bool GsKgZHZzKD = false;
      bool CsnNNzAkpJ = false;
      bool xoMEBDXENh = false;
      bool jDeyWVNqzw = false;
      bool WojdIxSilx = false;
      bool xnWALQfFeW = false;
      bool iVlcTzOoqr = false;
      bool lIlsmIEiwD = false;
      bool joRPjufdmF = false;
      bool pHLcMBCHJI = false;
      bool icqtLnCdNC = false;
      bool LwJbltDVrX = false;
      bool SkCkCdxJfk = false;
      string lquRMTihLc;
      string oxGimWkfpD;
      string tjdLRDhuSY;
      string WiEsTLpSYF;
      string DwgVuGGuGi;
      string eaYePBNiAJ;
      string kmPmFFrNOa;
      string fRHkAyDHQK;
      string xmnjtwKZdS;
      string yHSPTPgsQo;
      string NrfeDMSneR;
      string xFRoMyzesI;
      string uSjwcYzqQj;
      string QKqaxEGJgg;
      string dWtMUrocCV;
      string QBAItuIiCd;
      string MbWtAmOqrI;
      string qpyLeYYWbk;
      string iVnuTOJigC;
      string uXGCTBzzLg;
      if(lquRMTihLc == NrfeDMSneR){cykteaDncV = true;}
      else if(NrfeDMSneR == lquRMTihLc){jDeyWVNqzw = true;}
      if(oxGimWkfpD == xFRoMyzesI){WkHRtqmaal = true;}
      else if(xFRoMyzesI == oxGimWkfpD){WojdIxSilx = true;}
      if(tjdLRDhuSY == uSjwcYzqQj){cfJpNSiwqc = true;}
      else if(uSjwcYzqQj == tjdLRDhuSY){xnWALQfFeW = true;}
      if(WiEsTLpSYF == QKqaxEGJgg){YYLtHkktQs = true;}
      else if(QKqaxEGJgg == WiEsTLpSYF){iVlcTzOoqr = true;}
      if(DwgVuGGuGi == dWtMUrocCV){LVFKeJPoHc = true;}
      else if(dWtMUrocCV == DwgVuGGuGi){lIlsmIEiwD = true;}
      if(eaYePBNiAJ == QBAItuIiCd){OYYZExnugL = true;}
      else if(QBAItuIiCd == eaYePBNiAJ){joRPjufdmF = true;}
      if(kmPmFFrNOa == MbWtAmOqrI){qHxAxxZMKI = true;}
      else if(MbWtAmOqrI == kmPmFFrNOa){pHLcMBCHJI = true;}
      if(fRHkAyDHQK == qpyLeYYWbk){GsKgZHZzKD = true;}
      if(xmnjtwKZdS == iVnuTOJigC){CsnNNzAkpJ = true;}
      if(yHSPTPgsQo == uXGCTBzzLg){xoMEBDXENh = true;}
      while(qpyLeYYWbk == fRHkAyDHQK){icqtLnCdNC = true;}
      while(iVnuTOJigC == iVnuTOJigC){LwJbltDVrX = true;}
      while(uXGCTBzzLg == uXGCTBzzLg){SkCkCdxJfk = true;}
      if(cykteaDncV == true){cykteaDncV = false;}
      if(WkHRtqmaal == true){WkHRtqmaal = false;}
      if(cfJpNSiwqc == true){cfJpNSiwqc = false;}
      if(YYLtHkktQs == true){YYLtHkktQs = false;}
      if(LVFKeJPoHc == true){LVFKeJPoHc = false;}
      if(OYYZExnugL == true){OYYZExnugL = false;}
      if(qHxAxxZMKI == true){qHxAxxZMKI = false;}
      if(GsKgZHZzKD == true){GsKgZHZzKD = false;}
      if(CsnNNzAkpJ == true){CsnNNzAkpJ = false;}
      if(xoMEBDXENh == true){xoMEBDXENh = false;}
      if(jDeyWVNqzw == true){jDeyWVNqzw = false;}
      if(WojdIxSilx == true){WojdIxSilx = false;}
      if(xnWALQfFeW == true){xnWALQfFeW = false;}
      if(iVlcTzOoqr == true){iVlcTzOoqr = false;}
      if(lIlsmIEiwD == true){lIlsmIEiwD = false;}
      if(joRPjufdmF == true){joRPjufdmF = false;}
      if(pHLcMBCHJI == true){pHLcMBCHJI = false;}
      if(icqtLnCdNC == true){icqtLnCdNC = false;}
      if(LwJbltDVrX == true){LwJbltDVrX = false;}
      if(SkCkCdxJfk == true){SkCkCdxJfk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VSNIHSTMVK
{ 
  void QOtHiENQNo()
  { 
      bool oMjjswBxtl = false;
      bool wZqJrCIVGY = false;
      bool PWuZQfOtRb = false;
      bool ttKEoeMlBX = false;
      bool loUqfRtFTN = false;
      bool kfTTOSQJSM = false;
      bool hHeSrBOmUM = false;
      bool pWThmaBDsz = false;
      bool lIaDpNaqoV = false;
      bool NCSnpdJCze = false;
      bool DHkGXOLkgn = false;
      bool QNPTaZgace = false;
      bool ZXxyzmEfrI = false;
      bool QzEOudWTfb = false;
      bool BpJBEAlyNQ = false;
      bool xhZUEeKmGj = false;
      bool JfrYWRIBXw = false;
      bool CMuAcjOusz = false;
      bool BFSbKhYjKQ = false;
      bool TjNwRVxkdm = false;
      string DmFBWpjZDV;
      string QtGqRSlHUt;
      string RgXKTeJCSD;
      string FLydYMRRRW;
      string qNgdBjRHBM;
      string DjVZMVOugr;
      string fhGAQEubRF;
      string AToyDDAtJi;
      string MBAGAUpYQC;
      string xWjZqIHgMw;
      string opowLiuXWJ;
      string VUkxfehAAu;
      string OWLPHciPHu;
      string uTgMtWLEtQ;
      string ZSBHgckmsL;
      string ZHgQhRdZni;
      string zeQbNCmYCJ;
      string SdFiVwUEie;
      string qwVuUnlPdc;
      string rlPLQtBZsd;
      if(DmFBWpjZDV == opowLiuXWJ){oMjjswBxtl = true;}
      else if(opowLiuXWJ == DmFBWpjZDV){DHkGXOLkgn = true;}
      if(QtGqRSlHUt == VUkxfehAAu){wZqJrCIVGY = true;}
      else if(VUkxfehAAu == QtGqRSlHUt){QNPTaZgace = true;}
      if(RgXKTeJCSD == OWLPHciPHu){PWuZQfOtRb = true;}
      else if(OWLPHciPHu == RgXKTeJCSD){ZXxyzmEfrI = true;}
      if(FLydYMRRRW == uTgMtWLEtQ){ttKEoeMlBX = true;}
      else if(uTgMtWLEtQ == FLydYMRRRW){QzEOudWTfb = true;}
      if(qNgdBjRHBM == ZSBHgckmsL){loUqfRtFTN = true;}
      else if(ZSBHgckmsL == qNgdBjRHBM){BpJBEAlyNQ = true;}
      if(DjVZMVOugr == ZHgQhRdZni){kfTTOSQJSM = true;}
      else if(ZHgQhRdZni == DjVZMVOugr){xhZUEeKmGj = true;}
      if(fhGAQEubRF == zeQbNCmYCJ){hHeSrBOmUM = true;}
      else if(zeQbNCmYCJ == fhGAQEubRF){JfrYWRIBXw = true;}
      if(AToyDDAtJi == SdFiVwUEie){pWThmaBDsz = true;}
      if(MBAGAUpYQC == qwVuUnlPdc){lIaDpNaqoV = true;}
      if(xWjZqIHgMw == rlPLQtBZsd){NCSnpdJCze = true;}
      while(SdFiVwUEie == AToyDDAtJi){CMuAcjOusz = true;}
      while(qwVuUnlPdc == qwVuUnlPdc){BFSbKhYjKQ = true;}
      while(rlPLQtBZsd == rlPLQtBZsd){TjNwRVxkdm = true;}
      if(oMjjswBxtl == true){oMjjswBxtl = false;}
      if(wZqJrCIVGY == true){wZqJrCIVGY = false;}
      if(PWuZQfOtRb == true){PWuZQfOtRb = false;}
      if(ttKEoeMlBX == true){ttKEoeMlBX = false;}
      if(loUqfRtFTN == true){loUqfRtFTN = false;}
      if(kfTTOSQJSM == true){kfTTOSQJSM = false;}
      if(hHeSrBOmUM == true){hHeSrBOmUM = false;}
      if(pWThmaBDsz == true){pWThmaBDsz = false;}
      if(lIaDpNaqoV == true){lIaDpNaqoV = false;}
      if(NCSnpdJCze == true){NCSnpdJCze = false;}
      if(DHkGXOLkgn == true){DHkGXOLkgn = false;}
      if(QNPTaZgace == true){QNPTaZgace = false;}
      if(ZXxyzmEfrI == true){ZXxyzmEfrI = false;}
      if(QzEOudWTfb == true){QzEOudWTfb = false;}
      if(BpJBEAlyNQ == true){BpJBEAlyNQ = false;}
      if(xhZUEeKmGj == true){xhZUEeKmGj = false;}
      if(JfrYWRIBXw == true){JfrYWRIBXw = false;}
      if(CMuAcjOusz == true){CMuAcjOusz = false;}
      if(BFSbKhYjKQ == true){BFSbKhYjKQ = false;}
      if(TjNwRVxkdm == true){TjNwRVxkdm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OOAUCLSBXP
{ 
  void UxzlDJsqcy()
  { 
      bool XzLikjrPgW = false;
      bool odmZtawyjT = false;
      bool CAcEZCVlgw = false;
      bool BuIErBubqL = false;
      bool lrjQaXyonI = false;
      bool VRGmGWVHJh = false;
      bool OFhkVtUhgs = false;
      bool eTGYgJQMcB = false;
      bool EfyXaioVyV = false;
      bool enSIwfKytg = false;
      bool CPItcBKgFw = false;
      bool GJdIdhGJKl = false;
      bool EzjLOqBybA = false;
      bool zRRwynXDuY = false;
      bool YHQBOUJKdO = false;
      bool ZAnIbDfwfk = false;
      bool AMEExnrgJp = false;
      bool KCOkNwihxs = false;
      bool gqTNazdIUu = false;
      bool HaXJYLDLDZ = false;
      string bIFcLDQRwn;
      string VcuRXxJWDm;
      string IcepoeFXbf;
      string rxzkRyXePA;
      string GDbfTNWiVk;
      string wledszdOnf;
      string yspPuYdKzZ;
      string YdGDfEAyWb;
      string IWBpiFRUqS;
      string TIqiBNNMku;
      string jMiuLSfbyn;
      string yerLXbqzfo;
      string GISgFQlWBR;
      string qnNbqwmFdP;
      string ZpWDToPfLZ;
      string VNfwnasBpu;
      string gIZfxKRQTb;
      string nkVPOQlONQ;
      string AGLbudIQmP;
      string ClPiiRPpGI;
      if(bIFcLDQRwn == jMiuLSfbyn){XzLikjrPgW = true;}
      else if(jMiuLSfbyn == bIFcLDQRwn){CPItcBKgFw = true;}
      if(VcuRXxJWDm == yerLXbqzfo){odmZtawyjT = true;}
      else if(yerLXbqzfo == VcuRXxJWDm){GJdIdhGJKl = true;}
      if(IcepoeFXbf == GISgFQlWBR){CAcEZCVlgw = true;}
      else if(GISgFQlWBR == IcepoeFXbf){EzjLOqBybA = true;}
      if(rxzkRyXePA == qnNbqwmFdP){BuIErBubqL = true;}
      else if(qnNbqwmFdP == rxzkRyXePA){zRRwynXDuY = true;}
      if(GDbfTNWiVk == ZpWDToPfLZ){lrjQaXyonI = true;}
      else if(ZpWDToPfLZ == GDbfTNWiVk){YHQBOUJKdO = true;}
      if(wledszdOnf == VNfwnasBpu){VRGmGWVHJh = true;}
      else if(VNfwnasBpu == wledszdOnf){ZAnIbDfwfk = true;}
      if(yspPuYdKzZ == gIZfxKRQTb){OFhkVtUhgs = true;}
      else if(gIZfxKRQTb == yspPuYdKzZ){AMEExnrgJp = true;}
      if(YdGDfEAyWb == nkVPOQlONQ){eTGYgJQMcB = true;}
      if(IWBpiFRUqS == AGLbudIQmP){EfyXaioVyV = true;}
      if(TIqiBNNMku == ClPiiRPpGI){enSIwfKytg = true;}
      while(nkVPOQlONQ == YdGDfEAyWb){KCOkNwihxs = true;}
      while(AGLbudIQmP == AGLbudIQmP){gqTNazdIUu = true;}
      while(ClPiiRPpGI == ClPiiRPpGI){HaXJYLDLDZ = true;}
      if(XzLikjrPgW == true){XzLikjrPgW = false;}
      if(odmZtawyjT == true){odmZtawyjT = false;}
      if(CAcEZCVlgw == true){CAcEZCVlgw = false;}
      if(BuIErBubqL == true){BuIErBubqL = false;}
      if(lrjQaXyonI == true){lrjQaXyonI = false;}
      if(VRGmGWVHJh == true){VRGmGWVHJh = false;}
      if(OFhkVtUhgs == true){OFhkVtUhgs = false;}
      if(eTGYgJQMcB == true){eTGYgJQMcB = false;}
      if(EfyXaioVyV == true){EfyXaioVyV = false;}
      if(enSIwfKytg == true){enSIwfKytg = false;}
      if(CPItcBKgFw == true){CPItcBKgFw = false;}
      if(GJdIdhGJKl == true){GJdIdhGJKl = false;}
      if(EzjLOqBybA == true){EzjLOqBybA = false;}
      if(zRRwynXDuY == true){zRRwynXDuY = false;}
      if(YHQBOUJKdO == true){YHQBOUJKdO = false;}
      if(ZAnIbDfwfk == true){ZAnIbDfwfk = false;}
      if(AMEExnrgJp == true){AMEExnrgJp = false;}
      if(KCOkNwihxs == true){KCOkNwihxs = false;}
      if(gqTNazdIUu == true){gqTNazdIUu = false;}
      if(HaXJYLDLDZ == true){HaXJYLDLDZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EHFVPNLWQU
{ 
  void UsHOJDDjQw()
  { 
      bool oLrRKWzhTF = false;
      bool ywYkAzhHNx = false;
      bool ePRyKiXZgM = false;
      bool sqFsFOZlQm = false;
      bool jpAIsGhQzj = false;
      bool FdgYqYttHa = false;
      bool yYAGLHpffk = false;
      bool YupZNnPIED = false;
      bool BHaxHPJgCf = false;
      bool UeepoKpswl = false;
      bool QBjNKJmHKC = false;
      bool IkpDZpyCzw = false;
      bool yJdzQtQAkC = false;
      bool xWLSmzWMmx = false;
      bool bBWzWinaPy = false;
      bool LntAmHXjwP = false;
      bool rmWHFlYXQZ = false;
      bool SkPBTxlebh = false;
      bool GojmqJbLef = false;
      bool bmPWFoeOsk = false;
      string zSzCZrfTeF;
      string jykxUNxyJG;
      string bmJqOEjrzs;
      string dFsOKFbrqt;
      string stAXLuZNMe;
      string ZeasWLIInU;
      string HmUkadEWlO;
      string lFHONhlkeT;
      string eVeTTzezqy;
      string wTDVlFZPwh;
      string pDaysTXLfo;
      string ZXcTpkHAQb;
      string yFemSRCkcH;
      string IWnxdbugaA;
      string aTSCYYqifA;
      string xYyUikXnea;
      string RmiXgDiepN;
      string pZZQAdlbOt;
      string aSEbKiYTNr;
      string DGCzinkuVV;
      if(zSzCZrfTeF == pDaysTXLfo){oLrRKWzhTF = true;}
      else if(pDaysTXLfo == zSzCZrfTeF){QBjNKJmHKC = true;}
      if(jykxUNxyJG == ZXcTpkHAQb){ywYkAzhHNx = true;}
      else if(ZXcTpkHAQb == jykxUNxyJG){IkpDZpyCzw = true;}
      if(bmJqOEjrzs == yFemSRCkcH){ePRyKiXZgM = true;}
      else if(yFemSRCkcH == bmJqOEjrzs){yJdzQtQAkC = true;}
      if(dFsOKFbrqt == IWnxdbugaA){sqFsFOZlQm = true;}
      else if(IWnxdbugaA == dFsOKFbrqt){xWLSmzWMmx = true;}
      if(stAXLuZNMe == aTSCYYqifA){jpAIsGhQzj = true;}
      else if(aTSCYYqifA == stAXLuZNMe){bBWzWinaPy = true;}
      if(ZeasWLIInU == xYyUikXnea){FdgYqYttHa = true;}
      else if(xYyUikXnea == ZeasWLIInU){LntAmHXjwP = true;}
      if(HmUkadEWlO == RmiXgDiepN){yYAGLHpffk = true;}
      else if(RmiXgDiepN == HmUkadEWlO){rmWHFlYXQZ = true;}
      if(lFHONhlkeT == pZZQAdlbOt){YupZNnPIED = true;}
      if(eVeTTzezqy == aSEbKiYTNr){BHaxHPJgCf = true;}
      if(wTDVlFZPwh == DGCzinkuVV){UeepoKpswl = true;}
      while(pZZQAdlbOt == lFHONhlkeT){SkPBTxlebh = true;}
      while(aSEbKiYTNr == aSEbKiYTNr){GojmqJbLef = true;}
      while(DGCzinkuVV == DGCzinkuVV){bmPWFoeOsk = true;}
      if(oLrRKWzhTF == true){oLrRKWzhTF = false;}
      if(ywYkAzhHNx == true){ywYkAzhHNx = false;}
      if(ePRyKiXZgM == true){ePRyKiXZgM = false;}
      if(sqFsFOZlQm == true){sqFsFOZlQm = false;}
      if(jpAIsGhQzj == true){jpAIsGhQzj = false;}
      if(FdgYqYttHa == true){FdgYqYttHa = false;}
      if(yYAGLHpffk == true){yYAGLHpffk = false;}
      if(YupZNnPIED == true){YupZNnPIED = false;}
      if(BHaxHPJgCf == true){BHaxHPJgCf = false;}
      if(UeepoKpswl == true){UeepoKpswl = false;}
      if(QBjNKJmHKC == true){QBjNKJmHKC = false;}
      if(IkpDZpyCzw == true){IkpDZpyCzw = false;}
      if(yJdzQtQAkC == true){yJdzQtQAkC = false;}
      if(xWLSmzWMmx == true){xWLSmzWMmx = false;}
      if(bBWzWinaPy == true){bBWzWinaPy = false;}
      if(LntAmHXjwP == true){LntAmHXjwP = false;}
      if(rmWHFlYXQZ == true){rmWHFlYXQZ = false;}
      if(SkPBTxlebh == true){SkPBTxlebh = false;}
      if(GojmqJbLef == true){GojmqJbLef = false;}
      if(bmPWFoeOsk == true){bmPWFoeOsk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUMRBLFALM
{ 
  void htTuflAECI()
  { 
      bool PFkHVOHNXp = false;
      bool htdeqtEMbC = false;
      bool RfsQTtMcFC = false;
      bool IhcEaeFtUU = false;
      bool plbcPtcmTB = false;
      bool IGzcOiLTmb = false;
      bool CeHUhzQYEL = false;
      bool nJqGMeDQBY = false;
      bool QYJDtCiApq = false;
      bool TlHsSKdGuP = false;
      bool dEiHNyOrPi = false;
      bool euROKcUEae = false;
      bool QPhMrBCynB = false;
      bool AxVltLpCpu = false;
      bool mpjGLYUrho = false;
      bool pZfPzNVVOM = false;
      bool wQDOihZeTy = false;
      bool lSOerZebBT = false;
      bool fJPzLZQFlg = false;
      bool oUmczWmVXc = false;
      string qiZSXNOKPX;
      string ObAiqrYfsL;
      string iyGTmoZBRZ;
      string xVDlWqXgyi;
      string XRlxMLFIHz;
      string SFdcLrcFei;
      string nMsoasXOLA;
      string TrgJnRLJGb;
      string iRtRHqraZd;
      string ORCPtLXwWT;
      string mqwGeaXTnt;
      string gSzCAWRbhi;
      string AwnhlCpROc;
      string sOmlnqUmmf;
      string TXmfxuRzPX;
      string swOmSqCNUb;
      string kGELARfMOI;
      string BdnBPbJIjp;
      string jpBqixAzTx;
      string nGRKuMTaef;
      if(qiZSXNOKPX == mqwGeaXTnt){PFkHVOHNXp = true;}
      else if(mqwGeaXTnt == qiZSXNOKPX){dEiHNyOrPi = true;}
      if(ObAiqrYfsL == gSzCAWRbhi){htdeqtEMbC = true;}
      else if(gSzCAWRbhi == ObAiqrYfsL){euROKcUEae = true;}
      if(iyGTmoZBRZ == AwnhlCpROc){RfsQTtMcFC = true;}
      else if(AwnhlCpROc == iyGTmoZBRZ){QPhMrBCynB = true;}
      if(xVDlWqXgyi == sOmlnqUmmf){IhcEaeFtUU = true;}
      else if(sOmlnqUmmf == xVDlWqXgyi){AxVltLpCpu = true;}
      if(XRlxMLFIHz == TXmfxuRzPX){plbcPtcmTB = true;}
      else if(TXmfxuRzPX == XRlxMLFIHz){mpjGLYUrho = true;}
      if(SFdcLrcFei == swOmSqCNUb){IGzcOiLTmb = true;}
      else if(swOmSqCNUb == SFdcLrcFei){pZfPzNVVOM = true;}
      if(nMsoasXOLA == kGELARfMOI){CeHUhzQYEL = true;}
      else if(kGELARfMOI == nMsoasXOLA){wQDOihZeTy = true;}
      if(TrgJnRLJGb == BdnBPbJIjp){nJqGMeDQBY = true;}
      if(iRtRHqraZd == jpBqixAzTx){QYJDtCiApq = true;}
      if(ORCPtLXwWT == nGRKuMTaef){TlHsSKdGuP = true;}
      while(BdnBPbJIjp == TrgJnRLJGb){lSOerZebBT = true;}
      while(jpBqixAzTx == jpBqixAzTx){fJPzLZQFlg = true;}
      while(nGRKuMTaef == nGRKuMTaef){oUmczWmVXc = true;}
      if(PFkHVOHNXp == true){PFkHVOHNXp = false;}
      if(htdeqtEMbC == true){htdeqtEMbC = false;}
      if(RfsQTtMcFC == true){RfsQTtMcFC = false;}
      if(IhcEaeFtUU == true){IhcEaeFtUU = false;}
      if(plbcPtcmTB == true){plbcPtcmTB = false;}
      if(IGzcOiLTmb == true){IGzcOiLTmb = false;}
      if(CeHUhzQYEL == true){CeHUhzQYEL = false;}
      if(nJqGMeDQBY == true){nJqGMeDQBY = false;}
      if(QYJDtCiApq == true){QYJDtCiApq = false;}
      if(TlHsSKdGuP == true){TlHsSKdGuP = false;}
      if(dEiHNyOrPi == true){dEiHNyOrPi = false;}
      if(euROKcUEae == true){euROKcUEae = false;}
      if(QPhMrBCynB == true){QPhMrBCynB = false;}
      if(AxVltLpCpu == true){AxVltLpCpu = false;}
      if(mpjGLYUrho == true){mpjGLYUrho = false;}
      if(pZfPzNVVOM == true){pZfPzNVVOM = false;}
      if(wQDOihZeTy == true){wQDOihZeTy = false;}
      if(lSOerZebBT == true){lSOerZebBT = false;}
      if(fJPzLZQFlg == true){fJPzLZQFlg = false;}
      if(oUmczWmVXc == true){oUmczWmVXc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FBUQFSMIMG
{ 
  void RwLAttSZrF()
  { 
      bool ZrshFyLUuC = false;
      bool bWrexszWDk = false;
      bool uURbGVCzHu = false;
      bool cHjVTqeHWN = false;
      bool CGfUsyrUwg = false;
      bool xOJchFaRbj = false;
      bool wLNAZTlWLF = false;
      bool OqAohonwhI = false;
      bool cgDZxNyHmO = false;
      bool QNfmRpseuZ = false;
      bool LVIqSFNTts = false;
      bool QdiTGOImDL = false;
      bool VdjxoBLNXr = false;
      bool wJBIwHXMHr = false;
      bool AdNtxmdMfC = false;
      bool hFbiEhlLBR = false;
      bool sAuBwGbZXz = false;
      bool pwfKLqPozB = false;
      bool WzgVJphREN = false;
      bool VMKpyzhLxq = false;
      string HFdqfdkhhI;
      string cfgWYMDspE;
      string ItKxOrVxqd;
      string zBZpQbohPE;
      string PPicrBVzkT;
      string CUaSLMtgcn;
      string HmpDJaFpFx;
      string XUclorKhEN;
      string VWMWbdaGeD;
      string hIFbwbYfSR;
      string ufsnwhqodS;
      string CLbORjaTbe;
      string AyKBPPPBoN;
      string TePmRpcYZs;
      string mlcMBVfpKM;
      string AFDnQxUrYf;
      string SpzPzWwnxb;
      string GCshrOUyzs;
      string iYpcMNabWU;
      string UkAsawlNNd;
      if(HFdqfdkhhI == ufsnwhqodS){ZrshFyLUuC = true;}
      else if(ufsnwhqodS == HFdqfdkhhI){LVIqSFNTts = true;}
      if(cfgWYMDspE == CLbORjaTbe){bWrexszWDk = true;}
      else if(CLbORjaTbe == cfgWYMDspE){QdiTGOImDL = true;}
      if(ItKxOrVxqd == AyKBPPPBoN){uURbGVCzHu = true;}
      else if(AyKBPPPBoN == ItKxOrVxqd){VdjxoBLNXr = true;}
      if(zBZpQbohPE == TePmRpcYZs){cHjVTqeHWN = true;}
      else if(TePmRpcYZs == zBZpQbohPE){wJBIwHXMHr = true;}
      if(PPicrBVzkT == mlcMBVfpKM){CGfUsyrUwg = true;}
      else if(mlcMBVfpKM == PPicrBVzkT){AdNtxmdMfC = true;}
      if(CUaSLMtgcn == AFDnQxUrYf){xOJchFaRbj = true;}
      else if(AFDnQxUrYf == CUaSLMtgcn){hFbiEhlLBR = true;}
      if(HmpDJaFpFx == SpzPzWwnxb){wLNAZTlWLF = true;}
      else if(SpzPzWwnxb == HmpDJaFpFx){sAuBwGbZXz = true;}
      if(XUclorKhEN == GCshrOUyzs){OqAohonwhI = true;}
      if(VWMWbdaGeD == iYpcMNabWU){cgDZxNyHmO = true;}
      if(hIFbwbYfSR == UkAsawlNNd){QNfmRpseuZ = true;}
      while(GCshrOUyzs == XUclorKhEN){pwfKLqPozB = true;}
      while(iYpcMNabWU == iYpcMNabWU){WzgVJphREN = true;}
      while(UkAsawlNNd == UkAsawlNNd){VMKpyzhLxq = true;}
      if(ZrshFyLUuC == true){ZrshFyLUuC = false;}
      if(bWrexszWDk == true){bWrexszWDk = false;}
      if(uURbGVCzHu == true){uURbGVCzHu = false;}
      if(cHjVTqeHWN == true){cHjVTqeHWN = false;}
      if(CGfUsyrUwg == true){CGfUsyrUwg = false;}
      if(xOJchFaRbj == true){xOJchFaRbj = false;}
      if(wLNAZTlWLF == true){wLNAZTlWLF = false;}
      if(OqAohonwhI == true){OqAohonwhI = false;}
      if(cgDZxNyHmO == true){cgDZxNyHmO = false;}
      if(QNfmRpseuZ == true){QNfmRpseuZ = false;}
      if(LVIqSFNTts == true){LVIqSFNTts = false;}
      if(QdiTGOImDL == true){QdiTGOImDL = false;}
      if(VdjxoBLNXr == true){VdjxoBLNXr = false;}
      if(wJBIwHXMHr == true){wJBIwHXMHr = false;}
      if(AdNtxmdMfC == true){AdNtxmdMfC = false;}
      if(hFbiEhlLBR == true){hFbiEhlLBR = false;}
      if(sAuBwGbZXz == true){sAuBwGbZXz = false;}
      if(pwfKLqPozB == true){pwfKLqPozB = false;}
      if(WzgVJphREN == true){WzgVJphREN = false;}
      if(VMKpyzhLxq == true){VMKpyzhLxq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ULHOTLZZVC
{ 
  void zqAFhMGFCM()
  { 
      bool hFLRnWwuyP = false;
      bool yUIRjTQFYD = false;
      bool TGeTEkypoo = false;
      bool SsQTOxxotJ = false;
      bool tuVqDablpF = false;
      bool yGHSlbaqMC = false;
      bool YGFIxEEoDl = false;
      bool VbKPIYkmQc = false;
      bool JLAjqMlygm = false;
      bool VFbqjnoMty = false;
      bool WliDiVurJM = false;
      bool pmajsMGVRj = false;
      bool SGHPQPATeU = false;
      bool iYsRGWcwAV = false;
      bool RsnUwheryW = false;
      bool gTuJeQdTmS = false;
      bool VbNocRtIdV = false;
      bool jJUwSZRmSh = false;
      bool kIUHmPcimo = false;
      bool rJJhzofyqe = false;
      string RBnZPLmfsK;
      string ZefYfeLrZP;
      string JinUOueYHI;
      string hKQLITBpsf;
      string LOJWpAfnhL;
      string nwbRtiNTLU;
      string fNYjcONUPL;
      string cUysEtYQdO;
      string PqquUkizQZ;
      string FheYzxpYta;
      string mLXViSyhMz;
      string JwoxFoWcPq;
      string fNDoGupZsG;
      string EzWCaDSUMB;
      string mAmQQIrgSK;
      string ZMJCuYHhPm;
      string cXnFuKZlVB;
      string VCPOEealYx;
      string DIGigqpTHC;
      string wjEZYOLgVF;
      if(RBnZPLmfsK == mLXViSyhMz){hFLRnWwuyP = true;}
      else if(mLXViSyhMz == RBnZPLmfsK){WliDiVurJM = true;}
      if(ZefYfeLrZP == JwoxFoWcPq){yUIRjTQFYD = true;}
      else if(JwoxFoWcPq == ZefYfeLrZP){pmajsMGVRj = true;}
      if(JinUOueYHI == fNDoGupZsG){TGeTEkypoo = true;}
      else if(fNDoGupZsG == JinUOueYHI){SGHPQPATeU = true;}
      if(hKQLITBpsf == EzWCaDSUMB){SsQTOxxotJ = true;}
      else if(EzWCaDSUMB == hKQLITBpsf){iYsRGWcwAV = true;}
      if(LOJWpAfnhL == mAmQQIrgSK){tuVqDablpF = true;}
      else if(mAmQQIrgSK == LOJWpAfnhL){RsnUwheryW = true;}
      if(nwbRtiNTLU == ZMJCuYHhPm){yGHSlbaqMC = true;}
      else if(ZMJCuYHhPm == nwbRtiNTLU){gTuJeQdTmS = true;}
      if(fNYjcONUPL == cXnFuKZlVB){YGFIxEEoDl = true;}
      else if(cXnFuKZlVB == fNYjcONUPL){VbNocRtIdV = true;}
      if(cUysEtYQdO == VCPOEealYx){VbKPIYkmQc = true;}
      if(PqquUkizQZ == DIGigqpTHC){JLAjqMlygm = true;}
      if(FheYzxpYta == wjEZYOLgVF){VFbqjnoMty = true;}
      while(VCPOEealYx == cUysEtYQdO){jJUwSZRmSh = true;}
      while(DIGigqpTHC == DIGigqpTHC){kIUHmPcimo = true;}
      while(wjEZYOLgVF == wjEZYOLgVF){rJJhzofyqe = true;}
      if(hFLRnWwuyP == true){hFLRnWwuyP = false;}
      if(yUIRjTQFYD == true){yUIRjTQFYD = false;}
      if(TGeTEkypoo == true){TGeTEkypoo = false;}
      if(SsQTOxxotJ == true){SsQTOxxotJ = false;}
      if(tuVqDablpF == true){tuVqDablpF = false;}
      if(yGHSlbaqMC == true){yGHSlbaqMC = false;}
      if(YGFIxEEoDl == true){YGFIxEEoDl = false;}
      if(VbKPIYkmQc == true){VbKPIYkmQc = false;}
      if(JLAjqMlygm == true){JLAjqMlygm = false;}
      if(VFbqjnoMty == true){VFbqjnoMty = false;}
      if(WliDiVurJM == true){WliDiVurJM = false;}
      if(pmajsMGVRj == true){pmajsMGVRj = false;}
      if(SGHPQPATeU == true){SGHPQPATeU = false;}
      if(iYsRGWcwAV == true){iYsRGWcwAV = false;}
      if(RsnUwheryW == true){RsnUwheryW = false;}
      if(gTuJeQdTmS == true){gTuJeQdTmS = false;}
      if(VbNocRtIdV == true){VbNocRtIdV = false;}
      if(jJUwSZRmSh == true){jJUwSZRmSh = false;}
      if(kIUHmPcimo == true){kIUHmPcimo = false;}
      if(rJJhzofyqe == true){rJJhzofyqe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GVOIGKCVMP
{ 
  void MNDoVTGasQ()
  { 
      bool nNZPKprGhR = false;
      bool nEXJNLgrKs = false;
      bool kIxCzLkCLj = false;
      bool GJDgGWKRYE = false;
      bool BeqQiKVwbS = false;
      bool gzNAhfQXPz = false;
      bool EouxLdAqCp = false;
      bool BOTGrFRfSn = false;
      bool onZrDHwDya = false;
      bool GmCZzLjsEF = false;
      bool KdtlRSeHIb = false;
      bool OjEaJQPCtD = false;
      bool hwsaiOMtHf = false;
      bool VXaNdLtnak = false;
      bool bouWMWhaPh = false;
      bool wgzBXNkSCD = false;
      bool FjAbFqIqxy = false;
      bool VabJbrBWOM = false;
      bool gldYioXZoP = false;
      bool ZblXeqoSQV = false;
      string nxpXtnIsUd;
      string TNzmflWQfY;
      string PkxcaNiZuu;
      string BHuSAHjRrs;
      string PQnkuzNBtd;
      string myMnRDzMwg;
      string FhyZcMRfmY;
      string BFXlIyxMhb;
      string zgfQICtHBw;
      string HXULnhSNHi;
      string ggOVbgZZeT;
      string GleUgXBgQa;
      string RKepQdkLya;
      string fiFztRSKna;
      string bTbhpUsAeP;
      string gkxfQWCXEy;
      string wNbEnWgeZP;
      string Fprpyyhxzu;
      string kjgittlYhX;
      string PtFpeNrXsS;
      if(nxpXtnIsUd == ggOVbgZZeT){nNZPKprGhR = true;}
      else if(ggOVbgZZeT == nxpXtnIsUd){KdtlRSeHIb = true;}
      if(TNzmflWQfY == GleUgXBgQa){nEXJNLgrKs = true;}
      else if(GleUgXBgQa == TNzmflWQfY){OjEaJQPCtD = true;}
      if(PkxcaNiZuu == RKepQdkLya){kIxCzLkCLj = true;}
      else if(RKepQdkLya == PkxcaNiZuu){hwsaiOMtHf = true;}
      if(BHuSAHjRrs == fiFztRSKna){GJDgGWKRYE = true;}
      else if(fiFztRSKna == BHuSAHjRrs){VXaNdLtnak = true;}
      if(PQnkuzNBtd == bTbhpUsAeP){BeqQiKVwbS = true;}
      else if(bTbhpUsAeP == PQnkuzNBtd){bouWMWhaPh = true;}
      if(myMnRDzMwg == gkxfQWCXEy){gzNAhfQXPz = true;}
      else if(gkxfQWCXEy == myMnRDzMwg){wgzBXNkSCD = true;}
      if(FhyZcMRfmY == wNbEnWgeZP){EouxLdAqCp = true;}
      else if(wNbEnWgeZP == FhyZcMRfmY){FjAbFqIqxy = true;}
      if(BFXlIyxMhb == Fprpyyhxzu){BOTGrFRfSn = true;}
      if(zgfQICtHBw == kjgittlYhX){onZrDHwDya = true;}
      if(HXULnhSNHi == PtFpeNrXsS){GmCZzLjsEF = true;}
      while(Fprpyyhxzu == BFXlIyxMhb){VabJbrBWOM = true;}
      while(kjgittlYhX == kjgittlYhX){gldYioXZoP = true;}
      while(PtFpeNrXsS == PtFpeNrXsS){ZblXeqoSQV = true;}
      if(nNZPKprGhR == true){nNZPKprGhR = false;}
      if(nEXJNLgrKs == true){nEXJNLgrKs = false;}
      if(kIxCzLkCLj == true){kIxCzLkCLj = false;}
      if(GJDgGWKRYE == true){GJDgGWKRYE = false;}
      if(BeqQiKVwbS == true){BeqQiKVwbS = false;}
      if(gzNAhfQXPz == true){gzNAhfQXPz = false;}
      if(EouxLdAqCp == true){EouxLdAqCp = false;}
      if(BOTGrFRfSn == true){BOTGrFRfSn = false;}
      if(onZrDHwDya == true){onZrDHwDya = false;}
      if(GmCZzLjsEF == true){GmCZzLjsEF = false;}
      if(KdtlRSeHIb == true){KdtlRSeHIb = false;}
      if(OjEaJQPCtD == true){OjEaJQPCtD = false;}
      if(hwsaiOMtHf == true){hwsaiOMtHf = false;}
      if(VXaNdLtnak == true){VXaNdLtnak = false;}
      if(bouWMWhaPh == true){bouWMWhaPh = false;}
      if(wgzBXNkSCD == true){wgzBXNkSCD = false;}
      if(FjAbFqIqxy == true){FjAbFqIqxy = false;}
      if(VabJbrBWOM == true){VabJbrBWOM = false;}
      if(gldYioXZoP == true){gldYioXZoP = false;}
      if(ZblXeqoSQV == true){ZblXeqoSQV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TFCZVMNIIQ
{ 
  void yzfKkQGtEj()
  { 
      bool pnwcHbMZdC = false;
      bool mLUsTMjXKx = false;
      bool TtWCRtQXWd = false;
      bool QVeYdPmBRV = false;
      bool egkhrlDPCK = false;
      bool XcpAsuQsKM = false;
      bool KnCzkRguPE = false;
      bool YhFoRlJnKf = false;
      bool qAUMGmeeeh = false;
      bool zspFKqekwa = false;
      bool FHAykoWBiH = false;
      bool lbieUKTory = false;
      bool lBPhFeqAda = false;
      bool GXrjZjAWaR = false;
      bool PdwXwWKKjA = false;
      bool WosynDqRrF = false;
      bool xWWHANjzEk = false;
      bool JxNahHErlh = false;
      bool UgPcDQesuW = false;
      bool rhdVTsGnWh = false;
      string FeARhMtHMW;
      string gPARlXbHBz;
      string ArntOmFryO;
      string IRUKCdOHpe;
      string AFglBiuunf;
      string gCUFjNpFDu;
      string HBIxNOtpOH;
      string ITRWyuLCre;
      string rKDShGxPao;
      string nJEuWzwjXm;
      string oEfgXMkxGn;
      string BnNYCxxpPH;
      string RePZTzPWzz;
      string yaeFomdWuU;
      string VzIlmzuerZ;
      string BGUPUJoGNX;
      string xNxHoZJHiP;
      string SZttlSWclT;
      string DjdZxrGOkf;
      string yXJWXHBAxM;
      if(FeARhMtHMW == oEfgXMkxGn){pnwcHbMZdC = true;}
      else if(oEfgXMkxGn == FeARhMtHMW){FHAykoWBiH = true;}
      if(gPARlXbHBz == BnNYCxxpPH){mLUsTMjXKx = true;}
      else if(BnNYCxxpPH == gPARlXbHBz){lbieUKTory = true;}
      if(ArntOmFryO == RePZTzPWzz){TtWCRtQXWd = true;}
      else if(RePZTzPWzz == ArntOmFryO){lBPhFeqAda = true;}
      if(IRUKCdOHpe == yaeFomdWuU){QVeYdPmBRV = true;}
      else if(yaeFomdWuU == IRUKCdOHpe){GXrjZjAWaR = true;}
      if(AFglBiuunf == VzIlmzuerZ){egkhrlDPCK = true;}
      else if(VzIlmzuerZ == AFglBiuunf){PdwXwWKKjA = true;}
      if(gCUFjNpFDu == BGUPUJoGNX){XcpAsuQsKM = true;}
      else if(BGUPUJoGNX == gCUFjNpFDu){WosynDqRrF = true;}
      if(HBIxNOtpOH == xNxHoZJHiP){KnCzkRguPE = true;}
      else if(xNxHoZJHiP == HBIxNOtpOH){xWWHANjzEk = true;}
      if(ITRWyuLCre == SZttlSWclT){YhFoRlJnKf = true;}
      if(rKDShGxPao == DjdZxrGOkf){qAUMGmeeeh = true;}
      if(nJEuWzwjXm == yXJWXHBAxM){zspFKqekwa = true;}
      while(SZttlSWclT == ITRWyuLCre){JxNahHErlh = true;}
      while(DjdZxrGOkf == DjdZxrGOkf){UgPcDQesuW = true;}
      while(yXJWXHBAxM == yXJWXHBAxM){rhdVTsGnWh = true;}
      if(pnwcHbMZdC == true){pnwcHbMZdC = false;}
      if(mLUsTMjXKx == true){mLUsTMjXKx = false;}
      if(TtWCRtQXWd == true){TtWCRtQXWd = false;}
      if(QVeYdPmBRV == true){QVeYdPmBRV = false;}
      if(egkhrlDPCK == true){egkhrlDPCK = false;}
      if(XcpAsuQsKM == true){XcpAsuQsKM = false;}
      if(KnCzkRguPE == true){KnCzkRguPE = false;}
      if(YhFoRlJnKf == true){YhFoRlJnKf = false;}
      if(qAUMGmeeeh == true){qAUMGmeeeh = false;}
      if(zspFKqekwa == true){zspFKqekwa = false;}
      if(FHAykoWBiH == true){FHAykoWBiH = false;}
      if(lbieUKTory == true){lbieUKTory = false;}
      if(lBPhFeqAda == true){lBPhFeqAda = false;}
      if(GXrjZjAWaR == true){GXrjZjAWaR = false;}
      if(PdwXwWKKjA == true){PdwXwWKKjA = false;}
      if(WosynDqRrF == true){WosynDqRrF = false;}
      if(xWWHANjzEk == true){xWWHANjzEk = false;}
      if(JxNahHErlh == true){JxNahHErlh = false;}
      if(UgPcDQesuW == true){UgPcDQesuW = false;}
      if(rhdVTsGnWh == true){rhdVTsGnWh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HUXRBHZZYR
{ 
  void SIPyiClzRS()
  { 
      bool LtFpgAOzOQ = false;
      bool pigFRiOlJs = false;
      bool bDpNtrKure = false;
      bool lGkDhQKkwp = false;
      bool CIFKEiaRrk = false;
      bool EGBFOIErwn = false;
      bool pTGjdixdWB = false;
      bool YdpSpSxfIL = false;
      bool RrDHZeEfnZ = false;
      bool LSoHAiCUfU = false;
      bool kxtpMaQhOw = false;
      bool KYikWxPzKy = false;
      bool dRpxpGnhSH = false;
      bool QbzmZUyMuy = false;
      bool OWRrPmiEkC = false;
      bool SDKgpSGxAG = false;
      bool liOHeiYuKB = false;
      bool zDDMjHAyhC = false;
      bool WjwPoMRSxG = false;
      bool NAMoLfHJMf = false;
      string GhMqBFHnSS;
      string JqFBaSiWSM;
      string xnTPpHkAHk;
      string cmbGyFwcsn;
      string xuZNHBKByU;
      string lxEpzSNwBt;
      string UHfgoWPzCU;
      string VGcdPCNGHo;
      string xiBlzeilGf;
      string qzazToOsXk;
      string kLydzeUZZx;
      string EHnMxkGsgJ;
      string ncrWdVedKZ;
      string mTiWDkjXmT;
      string KILIbjLOCh;
      string iULNwISbzc;
      string zpPAKjXQIL;
      string BhGMyfRjtt;
      string KQbcqRHUau;
      string RIXKUTsKyq;
      if(GhMqBFHnSS == kLydzeUZZx){LtFpgAOzOQ = true;}
      else if(kLydzeUZZx == GhMqBFHnSS){kxtpMaQhOw = true;}
      if(JqFBaSiWSM == EHnMxkGsgJ){pigFRiOlJs = true;}
      else if(EHnMxkGsgJ == JqFBaSiWSM){KYikWxPzKy = true;}
      if(xnTPpHkAHk == ncrWdVedKZ){bDpNtrKure = true;}
      else if(ncrWdVedKZ == xnTPpHkAHk){dRpxpGnhSH = true;}
      if(cmbGyFwcsn == mTiWDkjXmT){lGkDhQKkwp = true;}
      else if(mTiWDkjXmT == cmbGyFwcsn){QbzmZUyMuy = true;}
      if(xuZNHBKByU == KILIbjLOCh){CIFKEiaRrk = true;}
      else if(KILIbjLOCh == xuZNHBKByU){OWRrPmiEkC = true;}
      if(lxEpzSNwBt == iULNwISbzc){EGBFOIErwn = true;}
      else if(iULNwISbzc == lxEpzSNwBt){SDKgpSGxAG = true;}
      if(UHfgoWPzCU == zpPAKjXQIL){pTGjdixdWB = true;}
      else if(zpPAKjXQIL == UHfgoWPzCU){liOHeiYuKB = true;}
      if(VGcdPCNGHo == BhGMyfRjtt){YdpSpSxfIL = true;}
      if(xiBlzeilGf == KQbcqRHUau){RrDHZeEfnZ = true;}
      if(qzazToOsXk == RIXKUTsKyq){LSoHAiCUfU = true;}
      while(BhGMyfRjtt == VGcdPCNGHo){zDDMjHAyhC = true;}
      while(KQbcqRHUau == KQbcqRHUau){WjwPoMRSxG = true;}
      while(RIXKUTsKyq == RIXKUTsKyq){NAMoLfHJMf = true;}
      if(LtFpgAOzOQ == true){LtFpgAOzOQ = false;}
      if(pigFRiOlJs == true){pigFRiOlJs = false;}
      if(bDpNtrKure == true){bDpNtrKure = false;}
      if(lGkDhQKkwp == true){lGkDhQKkwp = false;}
      if(CIFKEiaRrk == true){CIFKEiaRrk = false;}
      if(EGBFOIErwn == true){EGBFOIErwn = false;}
      if(pTGjdixdWB == true){pTGjdixdWB = false;}
      if(YdpSpSxfIL == true){YdpSpSxfIL = false;}
      if(RrDHZeEfnZ == true){RrDHZeEfnZ = false;}
      if(LSoHAiCUfU == true){LSoHAiCUfU = false;}
      if(kxtpMaQhOw == true){kxtpMaQhOw = false;}
      if(KYikWxPzKy == true){KYikWxPzKy = false;}
      if(dRpxpGnhSH == true){dRpxpGnhSH = false;}
      if(QbzmZUyMuy == true){QbzmZUyMuy = false;}
      if(OWRrPmiEkC == true){OWRrPmiEkC = false;}
      if(SDKgpSGxAG == true){SDKgpSGxAG = false;}
      if(liOHeiYuKB == true){liOHeiYuKB = false;}
      if(zDDMjHAyhC == true){zDDMjHAyhC = false;}
      if(WjwPoMRSxG == true){WjwPoMRSxG = false;}
      if(NAMoLfHJMf == true){NAMoLfHJMf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UINRGXJYLM
{ 
  void jUrooiRapk()
  { 
      bool iWgKFGEnuC = false;
      bool hjahhLiSIf = false;
      bool KIOyhiFPZU = false;
      bool fgZikLaoYw = false;
      bool yIRqBjekaC = false;
      bool MJHGwaHhcW = false;
      bool BnNZWBKrwV = false;
      bool jtsLgBqXwy = false;
      bool EUoWHVYSmK = false;
      bool DrMCtKuqTA = false;
      bool YmnERRQuYt = false;
      bool jjleSgzpSB = false;
      bool cqEkRqhqQW = false;
      bool GzDwYRfjEp = false;
      bool EctraTGgjN = false;
      bool KEYSXhhCmZ = false;
      bool jYdCmjfpFA = false;
      bool APlcwzxMKx = false;
      bool kAGDLCZkXq = false;
      bool jcxdFfyrFq = false;
      string SluaDQCAqq;
      string lNYzBOJmld;
      string mPLhMpNGtx;
      string SBVGyZGasH;
      string VfrfguwVFn;
      string YpBBVDZNON;
      string CwFtYjrRAa;
      string HisdHGWfAR;
      string trBGXczUju;
      string ArLfEZayHw;
      string CdVdfpxXsO;
      string ftMxSKuyVw;
      string kXgEaOWNYh;
      string fYXEOQVWZh;
      string fbaVOFfOMt;
      string ecbLLewQDR;
      string TiyKiHVIhC;
      string nXXnQIwLpU;
      string iHAeCDwMsj;
      string TFSIOwcPlG;
      if(SluaDQCAqq == CdVdfpxXsO){iWgKFGEnuC = true;}
      else if(CdVdfpxXsO == SluaDQCAqq){YmnERRQuYt = true;}
      if(lNYzBOJmld == ftMxSKuyVw){hjahhLiSIf = true;}
      else if(ftMxSKuyVw == lNYzBOJmld){jjleSgzpSB = true;}
      if(mPLhMpNGtx == kXgEaOWNYh){KIOyhiFPZU = true;}
      else if(kXgEaOWNYh == mPLhMpNGtx){cqEkRqhqQW = true;}
      if(SBVGyZGasH == fYXEOQVWZh){fgZikLaoYw = true;}
      else if(fYXEOQVWZh == SBVGyZGasH){GzDwYRfjEp = true;}
      if(VfrfguwVFn == fbaVOFfOMt){yIRqBjekaC = true;}
      else if(fbaVOFfOMt == VfrfguwVFn){EctraTGgjN = true;}
      if(YpBBVDZNON == ecbLLewQDR){MJHGwaHhcW = true;}
      else if(ecbLLewQDR == YpBBVDZNON){KEYSXhhCmZ = true;}
      if(CwFtYjrRAa == TiyKiHVIhC){BnNZWBKrwV = true;}
      else if(TiyKiHVIhC == CwFtYjrRAa){jYdCmjfpFA = true;}
      if(HisdHGWfAR == nXXnQIwLpU){jtsLgBqXwy = true;}
      if(trBGXczUju == iHAeCDwMsj){EUoWHVYSmK = true;}
      if(ArLfEZayHw == TFSIOwcPlG){DrMCtKuqTA = true;}
      while(nXXnQIwLpU == HisdHGWfAR){APlcwzxMKx = true;}
      while(iHAeCDwMsj == iHAeCDwMsj){kAGDLCZkXq = true;}
      while(TFSIOwcPlG == TFSIOwcPlG){jcxdFfyrFq = true;}
      if(iWgKFGEnuC == true){iWgKFGEnuC = false;}
      if(hjahhLiSIf == true){hjahhLiSIf = false;}
      if(KIOyhiFPZU == true){KIOyhiFPZU = false;}
      if(fgZikLaoYw == true){fgZikLaoYw = false;}
      if(yIRqBjekaC == true){yIRqBjekaC = false;}
      if(MJHGwaHhcW == true){MJHGwaHhcW = false;}
      if(BnNZWBKrwV == true){BnNZWBKrwV = false;}
      if(jtsLgBqXwy == true){jtsLgBqXwy = false;}
      if(EUoWHVYSmK == true){EUoWHVYSmK = false;}
      if(DrMCtKuqTA == true){DrMCtKuqTA = false;}
      if(YmnERRQuYt == true){YmnERRQuYt = false;}
      if(jjleSgzpSB == true){jjleSgzpSB = false;}
      if(cqEkRqhqQW == true){cqEkRqhqQW = false;}
      if(GzDwYRfjEp == true){GzDwYRfjEp = false;}
      if(EctraTGgjN == true){EctraTGgjN = false;}
      if(KEYSXhhCmZ == true){KEYSXhhCmZ = false;}
      if(jYdCmjfpFA == true){jYdCmjfpFA = false;}
      if(APlcwzxMKx == true){APlcwzxMKx = false;}
      if(kAGDLCZkXq == true){kAGDLCZkXq = false;}
      if(jcxdFfyrFq == true){jcxdFfyrFq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CRSDOFJRMO
{ 
  void mrgJWcqxAj()
  { 
      bool qzGoNspTxT = false;
      bool DYhjpCIcdo = false;
      bool XQhUtdpPJB = false;
      bool NcbYmrCFrk = false;
      bool XenxYrhdHO = false;
      bool tIYcVZQlti = false;
      bool DaKuFaxIwy = false;
      bool ADksRrcjwC = false;
      bool wLItHFDzDN = false;
      bool aQLJgwTrrx = false;
      bool tZhJOqXeLc = false;
      bool xgpqlqRQmA = false;
      bool WxEiWiqbLU = false;
      bool XjryIWdyeQ = false;
      bool gYnaQtaUWp = false;
      bool dDErZwVzle = false;
      bool zwSqEMnqiP = false;
      bool NTkWSyJcRb = false;
      bool IWEVpTeAXL = false;
      bool AeMzRkFxVD = false;
      string XaLFRLExJQ;
      string gmfQfShCHk;
      string JIiBIDBHAA;
      string xtuayZsJKb;
      string btKgbTlBrx;
      string xqbukPqJxN;
      string KwwISmqERG;
      string YYrfIPxCZn;
      string RzODCGRzpi;
      string hiMwRfxBOo;
      string bgilXYzwmU;
      string SojIwKgsFM;
      string UrOiXpMuNc;
      string RumkLjPced;
      string GUMUQsyDAH;
      string yEwCTiSAOh;
      string LDiJDWCzwL;
      string tENbFAfsSe;
      string qJtFeNzkQb;
      string QPNxRDlDRs;
      if(XaLFRLExJQ == bgilXYzwmU){qzGoNspTxT = true;}
      else if(bgilXYzwmU == XaLFRLExJQ){tZhJOqXeLc = true;}
      if(gmfQfShCHk == SojIwKgsFM){DYhjpCIcdo = true;}
      else if(SojIwKgsFM == gmfQfShCHk){xgpqlqRQmA = true;}
      if(JIiBIDBHAA == UrOiXpMuNc){XQhUtdpPJB = true;}
      else if(UrOiXpMuNc == JIiBIDBHAA){WxEiWiqbLU = true;}
      if(xtuayZsJKb == RumkLjPced){NcbYmrCFrk = true;}
      else if(RumkLjPced == xtuayZsJKb){XjryIWdyeQ = true;}
      if(btKgbTlBrx == GUMUQsyDAH){XenxYrhdHO = true;}
      else if(GUMUQsyDAH == btKgbTlBrx){gYnaQtaUWp = true;}
      if(xqbukPqJxN == yEwCTiSAOh){tIYcVZQlti = true;}
      else if(yEwCTiSAOh == xqbukPqJxN){dDErZwVzle = true;}
      if(KwwISmqERG == LDiJDWCzwL){DaKuFaxIwy = true;}
      else if(LDiJDWCzwL == KwwISmqERG){zwSqEMnqiP = true;}
      if(YYrfIPxCZn == tENbFAfsSe){ADksRrcjwC = true;}
      if(RzODCGRzpi == qJtFeNzkQb){wLItHFDzDN = true;}
      if(hiMwRfxBOo == QPNxRDlDRs){aQLJgwTrrx = true;}
      while(tENbFAfsSe == YYrfIPxCZn){NTkWSyJcRb = true;}
      while(qJtFeNzkQb == qJtFeNzkQb){IWEVpTeAXL = true;}
      while(QPNxRDlDRs == QPNxRDlDRs){AeMzRkFxVD = true;}
      if(qzGoNspTxT == true){qzGoNspTxT = false;}
      if(DYhjpCIcdo == true){DYhjpCIcdo = false;}
      if(XQhUtdpPJB == true){XQhUtdpPJB = false;}
      if(NcbYmrCFrk == true){NcbYmrCFrk = false;}
      if(XenxYrhdHO == true){XenxYrhdHO = false;}
      if(tIYcVZQlti == true){tIYcVZQlti = false;}
      if(DaKuFaxIwy == true){DaKuFaxIwy = false;}
      if(ADksRrcjwC == true){ADksRrcjwC = false;}
      if(wLItHFDzDN == true){wLItHFDzDN = false;}
      if(aQLJgwTrrx == true){aQLJgwTrrx = false;}
      if(tZhJOqXeLc == true){tZhJOqXeLc = false;}
      if(xgpqlqRQmA == true){xgpqlqRQmA = false;}
      if(WxEiWiqbLU == true){WxEiWiqbLU = false;}
      if(XjryIWdyeQ == true){XjryIWdyeQ = false;}
      if(gYnaQtaUWp == true){gYnaQtaUWp = false;}
      if(dDErZwVzle == true){dDErZwVzle = false;}
      if(zwSqEMnqiP == true){zwSqEMnqiP = false;}
      if(NTkWSyJcRb == true){NTkWSyJcRb = false;}
      if(IWEVpTeAXL == true){IWEVpTeAXL = false;}
      if(AeMzRkFxVD == true){AeMzRkFxVD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRQIEQJUFT
{ 
  void sBtIdEiZEC()
  { 
      bool CCMClgyqZY = false;
      bool aTyeiIBOeC = false;
      bool EqSECEBgEK = false;
      bool WlAPxHpgsB = false;
      bool bhXQWStVEH = false;
      bool jiAlbKjIAh = false;
      bool fQmOCoTigb = false;
      bool RTVdZWSChi = false;
      bool KebwZmkOml = false;
      bool WhgLVKtJNg = false;
      bool zKocoQNWLE = false;
      bool qhZQWBnqoO = false;
      bool EEwtEjmJIO = false;
      bool cJnAizozGJ = false;
      bool ZOChtoHPoU = false;
      bool VDUzcuOtXF = false;
      bool cDNxbhtZhW = false;
      bool LojenpBNzP = false;
      bool bXUnrYonXn = false;
      bool jubBfVAFGM = false;
      string TcGbWGBmLN;
      string ZcSVRQSmni;
      string hIHUnXcRnH;
      string IFpYlXpteA;
      string ATMwbrKlQq;
      string BWAPkLUknz;
      string cizDFTmtit;
      string aXIniNuKru;
      string MqBxGkFana;
      string CEGeWQUJpI;
      string FPCVPcNMfW;
      string PKsrmlgBxT;
      string OMGHrVRcQR;
      string skUjpxnegc;
      string WstRLrLOrk;
      string iSMWtsJuds;
      string LkuNcdoIBp;
      string yCUUwURowz;
      string KDjfiaYypx;
      string msAmQlyfng;
      if(TcGbWGBmLN == FPCVPcNMfW){CCMClgyqZY = true;}
      else if(FPCVPcNMfW == TcGbWGBmLN){zKocoQNWLE = true;}
      if(ZcSVRQSmni == PKsrmlgBxT){aTyeiIBOeC = true;}
      else if(PKsrmlgBxT == ZcSVRQSmni){qhZQWBnqoO = true;}
      if(hIHUnXcRnH == OMGHrVRcQR){EqSECEBgEK = true;}
      else if(OMGHrVRcQR == hIHUnXcRnH){EEwtEjmJIO = true;}
      if(IFpYlXpteA == skUjpxnegc){WlAPxHpgsB = true;}
      else if(skUjpxnegc == IFpYlXpteA){cJnAizozGJ = true;}
      if(ATMwbrKlQq == WstRLrLOrk){bhXQWStVEH = true;}
      else if(WstRLrLOrk == ATMwbrKlQq){ZOChtoHPoU = true;}
      if(BWAPkLUknz == iSMWtsJuds){jiAlbKjIAh = true;}
      else if(iSMWtsJuds == BWAPkLUknz){VDUzcuOtXF = true;}
      if(cizDFTmtit == LkuNcdoIBp){fQmOCoTigb = true;}
      else if(LkuNcdoIBp == cizDFTmtit){cDNxbhtZhW = true;}
      if(aXIniNuKru == yCUUwURowz){RTVdZWSChi = true;}
      if(MqBxGkFana == KDjfiaYypx){KebwZmkOml = true;}
      if(CEGeWQUJpI == msAmQlyfng){WhgLVKtJNg = true;}
      while(yCUUwURowz == aXIniNuKru){LojenpBNzP = true;}
      while(KDjfiaYypx == KDjfiaYypx){bXUnrYonXn = true;}
      while(msAmQlyfng == msAmQlyfng){jubBfVAFGM = true;}
      if(CCMClgyqZY == true){CCMClgyqZY = false;}
      if(aTyeiIBOeC == true){aTyeiIBOeC = false;}
      if(EqSECEBgEK == true){EqSECEBgEK = false;}
      if(WlAPxHpgsB == true){WlAPxHpgsB = false;}
      if(bhXQWStVEH == true){bhXQWStVEH = false;}
      if(jiAlbKjIAh == true){jiAlbKjIAh = false;}
      if(fQmOCoTigb == true){fQmOCoTigb = false;}
      if(RTVdZWSChi == true){RTVdZWSChi = false;}
      if(KebwZmkOml == true){KebwZmkOml = false;}
      if(WhgLVKtJNg == true){WhgLVKtJNg = false;}
      if(zKocoQNWLE == true){zKocoQNWLE = false;}
      if(qhZQWBnqoO == true){qhZQWBnqoO = false;}
      if(EEwtEjmJIO == true){EEwtEjmJIO = false;}
      if(cJnAizozGJ == true){cJnAizozGJ = false;}
      if(ZOChtoHPoU == true){ZOChtoHPoU = false;}
      if(VDUzcuOtXF == true){VDUzcuOtXF = false;}
      if(cDNxbhtZhW == true){cDNxbhtZhW = false;}
      if(LojenpBNzP == true){LojenpBNzP = false;}
      if(bXUnrYonXn == true){bXUnrYonXn = false;}
      if(jubBfVAFGM == true){jubBfVAFGM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JFBCPYLJIP
{ 
  void QQHrMdgYJX()
  { 
      bool mPhNDptzLk = false;
      bool UHACmbGadi = false;
      bool XxADzDsXIM = false;
      bool oKfgOyfJhT = false;
      bool ZzNimINEFG = false;
      bool IXrdCpOdOA = false;
      bool xVpyuKaSmn = false;
      bool uwrJIXiRPp = false;
      bool ooRBERSCdY = false;
      bool iBthWDJOmc = false;
      bool huQQLLeiUe = false;
      bool GxOYLIDntd = false;
      bool qYnNFsBKlF = false;
      bool NUdlHtXBpr = false;
      bool ljgzSlmUWO = false;
      bool zUUJlIGCLS = false;
      bool KUwOQkTbRQ = false;
      bool jCyCrHqouS = false;
      bool FfmXFsAUAz = false;
      bool mUoWhRnRih = false;
      string FbKYwckunM;
      string uoiiAeYcqu;
      string WtXbuoHxqz;
      string RNucUwhxQc;
      string qXwDHnOZUx;
      string arhtfKDhdG;
      string UnDotgsFOE;
      string xbLOEyxUTG;
      string ZhbsXZfBxJ;
      string rzSKHCUHIZ;
      string tJLQAzfTpg;
      string MiOXfmLJQU;
      string ArIELyIBGB;
      string dpMsLQVLsY;
      string sMKPxJjtdU;
      string pKqmZCAHEB;
      string pdMoCWWUMP;
      string QAQqbngsHC;
      string NOXlKTzYTI;
      string QNGriOzVMZ;
      if(FbKYwckunM == tJLQAzfTpg){mPhNDptzLk = true;}
      else if(tJLQAzfTpg == FbKYwckunM){huQQLLeiUe = true;}
      if(uoiiAeYcqu == MiOXfmLJQU){UHACmbGadi = true;}
      else if(MiOXfmLJQU == uoiiAeYcqu){GxOYLIDntd = true;}
      if(WtXbuoHxqz == ArIELyIBGB){XxADzDsXIM = true;}
      else if(ArIELyIBGB == WtXbuoHxqz){qYnNFsBKlF = true;}
      if(RNucUwhxQc == dpMsLQVLsY){oKfgOyfJhT = true;}
      else if(dpMsLQVLsY == RNucUwhxQc){NUdlHtXBpr = true;}
      if(qXwDHnOZUx == sMKPxJjtdU){ZzNimINEFG = true;}
      else if(sMKPxJjtdU == qXwDHnOZUx){ljgzSlmUWO = true;}
      if(arhtfKDhdG == pKqmZCAHEB){IXrdCpOdOA = true;}
      else if(pKqmZCAHEB == arhtfKDhdG){zUUJlIGCLS = true;}
      if(UnDotgsFOE == pdMoCWWUMP){xVpyuKaSmn = true;}
      else if(pdMoCWWUMP == UnDotgsFOE){KUwOQkTbRQ = true;}
      if(xbLOEyxUTG == QAQqbngsHC){uwrJIXiRPp = true;}
      if(ZhbsXZfBxJ == NOXlKTzYTI){ooRBERSCdY = true;}
      if(rzSKHCUHIZ == QNGriOzVMZ){iBthWDJOmc = true;}
      while(QAQqbngsHC == xbLOEyxUTG){jCyCrHqouS = true;}
      while(NOXlKTzYTI == NOXlKTzYTI){FfmXFsAUAz = true;}
      while(QNGriOzVMZ == QNGriOzVMZ){mUoWhRnRih = true;}
      if(mPhNDptzLk == true){mPhNDptzLk = false;}
      if(UHACmbGadi == true){UHACmbGadi = false;}
      if(XxADzDsXIM == true){XxADzDsXIM = false;}
      if(oKfgOyfJhT == true){oKfgOyfJhT = false;}
      if(ZzNimINEFG == true){ZzNimINEFG = false;}
      if(IXrdCpOdOA == true){IXrdCpOdOA = false;}
      if(xVpyuKaSmn == true){xVpyuKaSmn = false;}
      if(uwrJIXiRPp == true){uwrJIXiRPp = false;}
      if(ooRBERSCdY == true){ooRBERSCdY = false;}
      if(iBthWDJOmc == true){iBthWDJOmc = false;}
      if(huQQLLeiUe == true){huQQLLeiUe = false;}
      if(GxOYLIDntd == true){GxOYLIDntd = false;}
      if(qYnNFsBKlF == true){qYnNFsBKlF = false;}
      if(NUdlHtXBpr == true){NUdlHtXBpr = false;}
      if(ljgzSlmUWO == true){ljgzSlmUWO = false;}
      if(zUUJlIGCLS == true){zUUJlIGCLS = false;}
      if(KUwOQkTbRQ == true){KUwOQkTbRQ = false;}
      if(jCyCrHqouS == true){jCyCrHqouS = false;}
      if(FfmXFsAUAz == true){FfmXFsAUAz = false;}
      if(mUoWhRnRih == true){mUoWhRnRih = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BDDYHCFMNN
{ 
  void yQgAYadcbu()
  { 
      bool cFuMnGyeSJ = false;
      bool tRDfwEkeAW = false;
      bool gNECXHLPkK = false;
      bool jPhQZNMCEW = false;
      bool QglYdIfCjK = false;
      bool OnWDzOArnf = false;
      bool uisHZdjmFh = false;
      bool qiZdGAbfYP = false;
      bool aIfawwreQL = false;
      bool MUNYbgmdzz = false;
      bool YsxBSeNswz = false;
      bool lUTYElDSKc = false;
      bool lEWtVWVBCY = false;
      bool MyfZqhLdHR = false;
      bool iziRYqAnTo = false;
      bool dUSVNTWCeu = false;
      bool ILpWmnothV = false;
      bool aYKstlVFVd = false;
      bool WggMuqeJMW = false;
      bool LIzLJWILdj = false;
      string zXaDXqkHoT;
      string xAfaQInscI;
      string wMynwZGarp;
      string iRCAwVQIIt;
      string UBJZlTbAcT;
      string WJetqmYmHy;
      string jJPykexedu;
      string qejinuCXCb;
      string yGyXTZlIII;
      string wdBKJKkKoG;
      string WwVgcqYwGw;
      string jBjfzcKqdL;
      string soVUyMdYYc;
      string JrhwFBkQuc;
      string ApBMYusVKf;
      string AtfdMgaAiP;
      string NAWdlrSnZy;
      string rsuBKDmIwC;
      string SIOrcOLEiX;
      string ajhfPASXZf;
      if(zXaDXqkHoT == WwVgcqYwGw){cFuMnGyeSJ = true;}
      else if(WwVgcqYwGw == zXaDXqkHoT){YsxBSeNswz = true;}
      if(xAfaQInscI == jBjfzcKqdL){tRDfwEkeAW = true;}
      else if(jBjfzcKqdL == xAfaQInscI){lUTYElDSKc = true;}
      if(wMynwZGarp == soVUyMdYYc){gNECXHLPkK = true;}
      else if(soVUyMdYYc == wMynwZGarp){lEWtVWVBCY = true;}
      if(iRCAwVQIIt == JrhwFBkQuc){jPhQZNMCEW = true;}
      else if(JrhwFBkQuc == iRCAwVQIIt){MyfZqhLdHR = true;}
      if(UBJZlTbAcT == ApBMYusVKf){QglYdIfCjK = true;}
      else if(ApBMYusVKf == UBJZlTbAcT){iziRYqAnTo = true;}
      if(WJetqmYmHy == AtfdMgaAiP){OnWDzOArnf = true;}
      else if(AtfdMgaAiP == WJetqmYmHy){dUSVNTWCeu = true;}
      if(jJPykexedu == NAWdlrSnZy){uisHZdjmFh = true;}
      else if(NAWdlrSnZy == jJPykexedu){ILpWmnothV = true;}
      if(qejinuCXCb == rsuBKDmIwC){qiZdGAbfYP = true;}
      if(yGyXTZlIII == SIOrcOLEiX){aIfawwreQL = true;}
      if(wdBKJKkKoG == ajhfPASXZf){MUNYbgmdzz = true;}
      while(rsuBKDmIwC == qejinuCXCb){aYKstlVFVd = true;}
      while(SIOrcOLEiX == SIOrcOLEiX){WggMuqeJMW = true;}
      while(ajhfPASXZf == ajhfPASXZf){LIzLJWILdj = true;}
      if(cFuMnGyeSJ == true){cFuMnGyeSJ = false;}
      if(tRDfwEkeAW == true){tRDfwEkeAW = false;}
      if(gNECXHLPkK == true){gNECXHLPkK = false;}
      if(jPhQZNMCEW == true){jPhQZNMCEW = false;}
      if(QglYdIfCjK == true){QglYdIfCjK = false;}
      if(OnWDzOArnf == true){OnWDzOArnf = false;}
      if(uisHZdjmFh == true){uisHZdjmFh = false;}
      if(qiZdGAbfYP == true){qiZdGAbfYP = false;}
      if(aIfawwreQL == true){aIfawwreQL = false;}
      if(MUNYbgmdzz == true){MUNYbgmdzz = false;}
      if(YsxBSeNswz == true){YsxBSeNswz = false;}
      if(lUTYElDSKc == true){lUTYElDSKc = false;}
      if(lEWtVWVBCY == true){lEWtVWVBCY = false;}
      if(MyfZqhLdHR == true){MyfZqhLdHR = false;}
      if(iziRYqAnTo == true){iziRYqAnTo = false;}
      if(dUSVNTWCeu == true){dUSVNTWCeu = false;}
      if(ILpWmnothV == true){ILpWmnothV = false;}
      if(aYKstlVFVd == true){aYKstlVFVd = false;}
      if(WggMuqeJMW == true){WggMuqeJMW = false;}
      if(LIzLJWILdj == true){LIzLJWILdj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IXXVPXJRWA
{ 
  void cxfHrMXZJE()
  { 
      bool xSAePRjpOb = false;
      bool OhQBUmKqXf = false;
      bool MbqbhtYhGl = false;
      bool KSJNfxPWLO = false;
      bool QglLgbLmJN = false;
      bool rgnqrUbXxV = false;
      bool rCjbRwYDUX = false;
      bool XmfIPepfuF = false;
      bool ilYstceRUL = false;
      bool UqZpWOxJsk = false;
      bool CHRlpEBfbM = false;
      bool ducqmFcphn = false;
      bool RHiJCfNpkB = false;
      bool hglJDaTmCo = false;
      bool bypHgZOhCQ = false;
      bool kGaFTuYIjJ = false;
      bool qKtZexISnL = false;
      bool lpmrMSRabb = false;
      bool RemUPaFgpI = false;
      bool CLDryQEPcj = false;
      string fUesoreoSD;
      string rACpPZJxsV;
      string ftYUyuDwBN;
      string zrWhjEkhiJ;
      string wLOLlSUztm;
      string SARpzluKts;
      string ninFDAcTGL;
      string nbOjYUeNif;
      string aEBNtzZgix;
      string IZmoVMWIHk;
      string oArhzqkhQd;
      string HhbOSigaKD;
      string aukIDOnYOL;
      string xVFxpZMTOD;
      string OrQEpZyYWl;
      string ewyEKtPjek;
      string CLSEgkceXr;
      string WNLHoiegSc;
      string PPBbgAXAmw;
      string KbndACYLXF;
      if(fUesoreoSD == oArhzqkhQd){xSAePRjpOb = true;}
      else if(oArhzqkhQd == fUesoreoSD){CHRlpEBfbM = true;}
      if(rACpPZJxsV == HhbOSigaKD){OhQBUmKqXf = true;}
      else if(HhbOSigaKD == rACpPZJxsV){ducqmFcphn = true;}
      if(ftYUyuDwBN == aukIDOnYOL){MbqbhtYhGl = true;}
      else if(aukIDOnYOL == ftYUyuDwBN){RHiJCfNpkB = true;}
      if(zrWhjEkhiJ == xVFxpZMTOD){KSJNfxPWLO = true;}
      else if(xVFxpZMTOD == zrWhjEkhiJ){hglJDaTmCo = true;}
      if(wLOLlSUztm == OrQEpZyYWl){QglLgbLmJN = true;}
      else if(OrQEpZyYWl == wLOLlSUztm){bypHgZOhCQ = true;}
      if(SARpzluKts == ewyEKtPjek){rgnqrUbXxV = true;}
      else if(ewyEKtPjek == SARpzluKts){kGaFTuYIjJ = true;}
      if(ninFDAcTGL == CLSEgkceXr){rCjbRwYDUX = true;}
      else if(CLSEgkceXr == ninFDAcTGL){qKtZexISnL = true;}
      if(nbOjYUeNif == WNLHoiegSc){XmfIPepfuF = true;}
      if(aEBNtzZgix == PPBbgAXAmw){ilYstceRUL = true;}
      if(IZmoVMWIHk == KbndACYLXF){UqZpWOxJsk = true;}
      while(WNLHoiegSc == nbOjYUeNif){lpmrMSRabb = true;}
      while(PPBbgAXAmw == PPBbgAXAmw){RemUPaFgpI = true;}
      while(KbndACYLXF == KbndACYLXF){CLDryQEPcj = true;}
      if(xSAePRjpOb == true){xSAePRjpOb = false;}
      if(OhQBUmKqXf == true){OhQBUmKqXf = false;}
      if(MbqbhtYhGl == true){MbqbhtYhGl = false;}
      if(KSJNfxPWLO == true){KSJNfxPWLO = false;}
      if(QglLgbLmJN == true){QglLgbLmJN = false;}
      if(rgnqrUbXxV == true){rgnqrUbXxV = false;}
      if(rCjbRwYDUX == true){rCjbRwYDUX = false;}
      if(XmfIPepfuF == true){XmfIPepfuF = false;}
      if(ilYstceRUL == true){ilYstceRUL = false;}
      if(UqZpWOxJsk == true){UqZpWOxJsk = false;}
      if(CHRlpEBfbM == true){CHRlpEBfbM = false;}
      if(ducqmFcphn == true){ducqmFcphn = false;}
      if(RHiJCfNpkB == true){RHiJCfNpkB = false;}
      if(hglJDaTmCo == true){hglJDaTmCo = false;}
      if(bypHgZOhCQ == true){bypHgZOhCQ = false;}
      if(kGaFTuYIjJ == true){kGaFTuYIjJ = false;}
      if(qKtZexISnL == true){qKtZexISnL = false;}
      if(lpmrMSRabb == true){lpmrMSRabb = false;}
      if(RemUPaFgpI == true){RemUPaFgpI = false;}
      if(CLDryQEPcj == true){CLDryQEPcj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YHXSUQAUHX
{ 
  void nDKNloGmyJ()
  { 
      bool YYohNoSqWU = false;
      bool KmtPpkUjHu = false;
      bool iRgIUJdReh = false;
      bool JtlxKzuLcy = false;
      bool KchIHwNqeq = false;
      bool IMcnEHqfNE = false;
      bool LAMnKPAwFp = false;
      bool oIGIkFiYBX = false;
      bool ulmmZxRysC = false;
      bool HPyYlKPsyr = false;
      bool wRloBAFTCz = false;
      bool XSeoIYNZON = false;
      bool xBDChZJhWa = false;
      bool opZIbdAxkY = false;
      bool qyusdokJPN = false;
      bool xpejttNiGb = false;
      bool pXxbJhrVNe = false;
      bool XPnoVyGJYs = false;
      bool oARJdzKoOg = false;
      bool PRpJiTBTju = false;
      string FoarxqcOQo;
      string TcfCcZigrY;
      string SHEFDRrBjo;
      string yXdkMqSkPk;
      string sGgcyxjxQd;
      string TLEoTxkUne;
      string zbdapwyupl;
      string GxQHfLZaGG;
      string gtkGUlToQO;
      string GyxjkRcFmC;
      string znGeWVuwJH;
      string XKOhxFqWGD;
      string cJebeIAfVO;
      string iTnDGsmGjy;
      string qWeIqujPlf;
      string aFziZoJezO;
      string VOZuYDWKaE;
      string RkmHLFeVkj;
      string YjtpncUEcR;
      string jIGUccwjjm;
      if(FoarxqcOQo == znGeWVuwJH){YYohNoSqWU = true;}
      else if(znGeWVuwJH == FoarxqcOQo){wRloBAFTCz = true;}
      if(TcfCcZigrY == XKOhxFqWGD){KmtPpkUjHu = true;}
      else if(XKOhxFqWGD == TcfCcZigrY){XSeoIYNZON = true;}
      if(SHEFDRrBjo == cJebeIAfVO){iRgIUJdReh = true;}
      else if(cJebeIAfVO == SHEFDRrBjo){xBDChZJhWa = true;}
      if(yXdkMqSkPk == iTnDGsmGjy){JtlxKzuLcy = true;}
      else if(iTnDGsmGjy == yXdkMqSkPk){opZIbdAxkY = true;}
      if(sGgcyxjxQd == qWeIqujPlf){KchIHwNqeq = true;}
      else if(qWeIqujPlf == sGgcyxjxQd){qyusdokJPN = true;}
      if(TLEoTxkUne == aFziZoJezO){IMcnEHqfNE = true;}
      else if(aFziZoJezO == TLEoTxkUne){xpejttNiGb = true;}
      if(zbdapwyupl == VOZuYDWKaE){LAMnKPAwFp = true;}
      else if(VOZuYDWKaE == zbdapwyupl){pXxbJhrVNe = true;}
      if(GxQHfLZaGG == RkmHLFeVkj){oIGIkFiYBX = true;}
      if(gtkGUlToQO == YjtpncUEcR){ulmmZxRysC = true;}
      if(GyxjkRcFmC == jIGUccwjjm){HPyYlKPsyr = true;}
      while(RkmHLFeVkj == GxQHfLZaGG){XPnoVyGJYs = true;}
      while(YjtpncUEcR == YjtpncUEcR){oARJdzKoOg = true;}
      while(jIGUccwjjm == jIGUccwjjm){PRpJiTBTju = true;}
      if(YYohNoSqWU == true){YYohNoSqWU = false;}
      if(KmtPpkUjHu == true){KmtPpkUjHu = false;}
      if(iRgIUJdReh == true){iRgIUJdReh = false;}
      if(JtlxKzuLcy == true){JtlxKzuLcy = false;}
      if(KchIHwNqeq == true){KchIHwNqeq = false;}
      if(IMcnEHqfNE == true){IMcnEHqfNE = false;}
      if(LAMnKPAwFp == true){LAMnKPAwFp = false;}
      if(oIGIkFiYBX == true){oIGIkFiYBX = false;}
      if(ulmmZxRysC == true){ulmmZxRysC = false;}
      if(HPyYlKPsyr == true){HPyYlKPsyr = false;}
      if(wRloBAFTCz == true){wRloBAFTCz = false;}
      if(XSeoIYNZON == true){XSeoIYNZON = false;}
      if(xBDChZJhWa == true){xBDChZJhWa = false;}
      if(opZIbdAxkY == true){opZIbdAxkY = false;}
      if(qyusdokJPN == true){qyusdokJPN = false;}
      if(xpejttNiGb == true){xpejttNiGb = false;}
      if(pXxbJhrVNe == true){pXxbJhrVNe = false;}
      if(XPnoVyGJYs == true){XPnoVyGJYs = false;}
      if(oARJdzKoOg == true){oARJdzKoOg = false;}
      if(PRpJiTBTju == true){PRpJiTBTju = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QORCRPPPEL
{ 
  void VANjalBGSB()
  { 
      bool XCZPmGKbrt = false;
      bool gGWEPqEKwo = false;
      bool mXfVQMnPCm = false;
      bool dAJGdYRAUV = false;
      bool nyniSexUcH = false;
      bool CBTzbAWDyZ = false;
      bool RtYFPgwQaq = false;
      bool YDpZBoixDl = false;
      bool OTmujcfKdd = false;
      bool BOCtDsYhSl = false;
      bool hgtlizLsxl = false;
      bool QZALLxHdUm = false;
      bool AllwoKBwWH = false;
      bool PBeQEhZBMk = false;
      bool QlMrMbNphF = false;
      bool kuNelutxwX = false;
      bool xPWpVPtjHd = false;
      bool XGQiVNZtjM = false;
      bool xLNQWUmzeI = false;
      bool mcEnnBOWVx = false;
      string zgNffjuOTX;
      string JLXSbtiVHq;
      string lRhWPOkhKe;
      string YNwNayZfbO;
      string dMBGCRqhPy;
      string aumjegyqQQ;
      string yNDnyuPKqd;
      string UDsrNZQbUy;
      string XDSMEcZLhs;
      string zhOLPPIMIG;
      string BgpkcWCuWF;
      string QWWSsuuqiU;
      string VEbxdlnhcx;
      string QDSNwpNgih;
      string aenccbLwRU;
      string URcmkwErHp;
      string iTSYnNDIVC;
      string hNHBtpPyUC;
      string arPHcyZfcz;
      string kUYryGMPoO;
      if(zgNffjuOTX == BgpkcWCuWF){XCZPmGKbrt = true;}
      else if(BgpkcWCuWF == zgNffjuOTX){hgtlizLsxl = true;}
      if(JLXSbtiVHq == QWWSsuuqiU){gGWEPqEKwo = true;}
      else if(QWWSsuuqiU == JLXSbtiVHq){QZALLxHdUm = true;}
      if(lRhWPOkhKe == VEbxdlnhcx){mXfVQMnPCm = true;}
      else if(VEbxdlnhcx == lRhWPOkhKe){AllwoKBwWH = true;}
      if(YNwNayZfbO == QDSNwpNgih){dAJGdYRAUV = true;}
      else if(QDSNwpNgih == YNwNayZfbO){PBeQEhZBMk = true;}
      if(dMBGCRqhPy == aenccbLwRU){nyniSexUcH = true;}
      else if(aenccbLwRU == dMBGCRqhPy){QlMrMbNphF = true;}
      if(aumjegyqQQ == URcmkwErHp){CBTzbAWDyZ = true;}
      else if(URcmkwErHp == aumjegyqQQ){kuNelutxwX = true;}
      if(yNDnyuPKqd == iTSYnNDIVC){RtYFPgwQaq = true;}
      else if(iTSYnNDIVC == yNDnyuPKqd){xPWpVPtjHd = true;}
      if(UDsrNZQbUy == hNHBtpPyUC){YDpZBoixDl = true;}
      if(XDSMEcZLhs == arPHcyZfcz){OTmujcfKdd = true;}
      if(zhOLPPIMIG == kUYryGMPoO){BOCtDsYhSl = true;}
      while(hNHBtpPyUC == UDsrNZQbUy){XGQiVNZtjM = true;}
      while(arPHcyZfcz == arPHcyZfcz){xLNQWUmzeI = true;}
      while(kUYryGMPoO == kUYryGMPoO){mcEnnBOWVx = true;}
      if(XCZPmGKbrt == true){XCZPmGKbrt = false;}
      if(gGWEPqEKwo == true){gGWEPqEKwo = false;}
      if(mXfVQMnPCm == true){mXfVQMnPCm = false;}
      if(dAJGdYRAUV == true){dAJGdYRAUV = false;}
      if(nyniSexUcH == true){nyniSexUcH = false;}
      if(CBTzbAWDyZ == true){CBTzbAWDyZ = false;}
      if(RtYFPgwQaq == true){RtYFPgwQaq = false;}
      if(YDpZBoixDl == true){YDpZBoixDl = false;}
      if(OTmujcfKdd == true){OTmujcfKdd = false;}
      if(BOCtDsYhSl == true){BOCtDsYhSl = false;}
      if(hgtlizLsxl == true){hgtlizLsxl = false;}
      if(QZALLxHdUm == true){QZALLxHdUm = false;}
      if(AllwoKBwWH == true){AllwoKBwWH = false;}
      if(PBeQEhZBMk == true){PBeQEhZBMk = false;}
      if(QlMrMbNphF == true){QlMrMbNphF = false;}
      if(kuNelutxwX == true){kuNelutxwX = false;}
      if(xPWpVPtjHd == true){xPWpVPtjHd = false;}
      if(XGQiVNZtjM == true){XGQiVNZtjM = false;}
      if(xLNQWUmzeI == true){xLNQWUmzeI = false;}
      if(mcEnnBOWVx == true){mcEnnBOWVx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YBWBVHCHRK
{ 
  void VHBaAdDQNg()
  { 
      bool OQYHnDHenI = false;
      bool ZrnliBnCQj = false;
      bool BMPsoZWIda = false;
      bool cJnZIoSsIi = false;
      bool RCUeRqMXFq = false;
      bool KHpLjBAfSO = false;
      bool gzANfPDNcs = false;
      bool huthSyqkax = false;
      bool MzCmQUTcpH = false;
      bool nmZsBRCHyC = false;
      bool nztLIONIsl = false;
      bool KOEUBhxNwK = false;
      bool waXUFuUAfA = false;
      bool wilYJNEqdB = false;
      bool GKiExZhFqT = false;
      bool UnKnFNaYGN = false;
      bool tMbsoabfLn = false;
      bool cGiuEkqTXf = false;
      bool MPILeHYySu = false;
      bool lejQHshpOV = false;
      string GCCWIyXDtJ;
      string BpaXPAkmEX;
      string BrFnunmomG;
      string iiWoBbUFmB;
      string RtyDLoGDEu;
      string ZXNiuNwNaT;
      string KiQnZSSlVm;
      string ffACGHtBbG;
      string hijqfLUntn;
      string eGdSpicKcs;
      string VUhROtWKbn;
      string StlUlbyYIO;
      string xdqgHZBhLX;
      string djYijMBSck;
      string nJMGUjTJgO;
      string jEBOurcAJn;
      string sozEJiVDkY;
      string ZfwWZmRkMW;
      string FqAwmZhJmr;
      string jAJnrzKHwl;
      if(GCCWIyXDtJ == VUhROtWKbn){OQYHnDHenI = true;}
      else if(VUhROtWKbn == GCCWIyXDtJ){nztLIONIsl = true;}
      if(BpaXPAkmEX == StlUlbyYIO){ZrnliBnCQj = true;}
      else if(StlUlbyYIO == BpaXPAkmEX){KOEUBhxNwK = true;}
      if(BrFnunmomG == xdqgHZBhLX){BMPsoZWIda = true;}
      else if(xdqgHZBhLX == BrFnunmomG){waXUFuUAfA = true;}
      if(iiWoBbUFmB == djYijMBSck){cJnZIoSsIi = true;}
      else if(djYijMBSck == iiWoBbUFmB){wilYJNEqdB = true;}
      if(RtyDLoGDEu == nJMGUjTJgO){RCUeRqMXFq = true;}
      else if(nJMGUjTJgO == RtyDLoGDEu){GKiExZhFqT = true;}
      if(ZXNiuNwNaT == jEBOurcAJn){KHpLjBAfSO = true;}
      else if(jEBOurcAJn == ZXNiuNwNaT){UnKnFNaYGN = true;}
      if(KiQnZSSlVm == sozEJiVDkY){gzANfPDNcs = true;}
      else if(sozEJiVDkY == KiQnZSSlVm){tMbsoabfLn = true;}
      if(ffACGHtBbG == ZfwWZmRkMW){huthSyqkax = true;}
      if(hijqfLUntn == FqAwmZhJmr){MzCmQUTcpH = true;}
      if(eGdSpicKcs == jAJnrzKHwl){nmZsBRCHyC = true;}
      while(ZfwWZmRkMW == ffACGHtBbG){cGiuEkqTXf = true;}
      while(FqAwmZhJmr == FqAwmZhJmr){MPILeHYySu = true;}
      while(jAJnrzKHwl == jAJnrzKHwl){lejQHshpOV = true;}
      if(OQYHnDHenI == true){OQYHnDHenI = false;}
      if(ZrnliBnCQj == true){ZrnliBnCQj = false;}
      if(BMPsoZWIda == true){BMPsoZWIda = false;}
      if(cJnZIoSsIi == true){cJnZIoSsIi = false;}
      if(RCUeRqMXFq == true){RCUeRqMXFq = false;}
      if(KHpLjBAfSO == true){KHpLjBAfSO = false;}
      if(gzANfPDNcs == true){gzANfPDNcs = false;}
      if(huthSyqkax == true){huthSyqkax = false;}
      if(MzCmQUTcpH == true){MzCmQUTcpH = false;}
      if(nmZsBRCHyC == true){nmZsBRCHyC = false;}
      if(nztLIONIsl == true){nztLIONIsl = false;}
      if(KOEUBhxNwK == true){KOEUBhxNwK = false;}
      if(waXUFuUAfA == true){waXUFuUAfA = false;}
      if(wilYJNEqdB == true){wilYJNEqdB = false;}
      if(GKiExZhFqT == true){GKiExZhFqT = false;}
      if(UnKnFNaYGN == true){UnKnFNaYGN = false;}
      if(tMbsoabfLn == true){tMbsoabfLn = false;}
      if(cGiuEkqTXf == true){cGiuEkqTXf = false;}
      if(MPILeHYySu == true){MPILeHYySu = false;}
      if(lejQHshpOV == true){lejQHshpOV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OECSEBXSRF
{ 
  void lMVEzgxWDO()
  { 
      bool WDHRfabUwX = false;
      bool QsTWVSZfus = false;
      bool CSzKxnEJNH = false;
      bool eDihrfnZpj = false;
      bool OprIIpUaGL = false;
      bool csHOBEDwUq = false;
      bool VRGnrNJlep = false;
      bool ezoKdMZpCH = false;
      bool ScCBdkwUfm = false;
      bool bqFyNwiDPu = false;
      bool fiuQfdEwjo = false;
      bool dMtNYsPEJH = false;
      bool RoGqNntpxg = false;
      bool cVaGaiglVA = false;
      bool fzjpJPwrZU = false;
      bool getIdqcECr = false;
      bool iNzDMHlmlo = false;
      bool LdiIaREPhy = false;
      bool rCQczybRcj = false;
      bool GcicQSzfcC = false;
      string WVTLPxTtBf;
      string rSjSsULYZY;
      string BLhNpbTRTQ;
      string WDBQNUdwlM;
      string TKlxxEmOCN;
      string SutzhKnFUn;
      string dCakInRSFY;
      string pPmNFpZjQk;
      string nEOFxbICiC;
      string gXbxhRjBnI;
      string mTJdWDHgsq;
      string kDoizYmUmf;
      string fPjDrSnoen;
      string GXwIyTujht;
      string UaIrQdirxJ;
      string dONHbXjGlE;
      string ORBFjMGfkf;
      string cDmsLEGqlO;
      string iuqVKqKnfZ;
      string ioyceDZCHE;
      if(WVTLPxTtBf == mTJdWDHgsq){WDHRfabUwX = true;}
      else if(mTJdWDHgsq == WVTLPxTtBf){fiuQfdEwjo = true;}
      if(rSjSsULYZY == kDoizYmUmf){QsTWVSZfus = true;}
      else if(kDoizYmUmf == rSjSsULYZY){dMtNYsPEJH = true;}
      if(BLhNpbTRTQ == fPjDrSnoen){CSzKxnEJNH = true;}
      else if(fPjDrSnoen == BLhNpbTRTQ){RoGqNntpxg = true;}
      if(WDBQNUdwlM == GXwIyTujht){eDihrfnZpj = true;}
      else if(GXwIyTujht == WDBQNUdwlM){cVaGaiglVA = true;}
      if(TKlxxEmOCN == UaIrQdirxJ){OprIIpUaGL = true;}
      else if(UaIrQdirxJ == TKlxxEmOCN){fzjpJPwrZU = true;}
      if(SutzhKnFUn == dONHbXjGlE){csHOBEDwUq = true;}
      else if(dONHbXjGlE == SutzhKnFUn){getIdqcECr = true;}
      if(dCakInRSFY == ORBFjMGfkf){VRGnrNJlep = true;}
      else if(ORBFjMGfkf == dCakInRSFY){iNzDMHlmlo = true;}
      if(pPmNFpZjQk == cDmsLEGqlO){ezoKdMZpCH = true;}
      if(nEOFxbICiC == iuqVKqKnfZ){ScCBdkwUfm = true;}
      if(gXbxhRjBnI == ioyceDZCHE){bqFyNwiDPu = true;}
      while(cDmsLEGqlO == pPmNFpZjQk){LdiIaREPhy = true;}
      while(iuqVKqKnfZ == iuqVKqKnfZ){rCQczybRcj = true;}
      while(ioyceDZCHE == ioyceDZCHE){GcicQSzfcC = true;}
      if(WDHRfabUwX == true){WDHRfabUwX = false;}
      if(QsTWVSZfus == true){QsTWVSZfus = false;}
      if(CSzKxnEJNH == true){CSzKxnEJNH = false;}
      if(eDihrfnZpj == true){eDihrfnZpj = false;}
      if(OprIIpUaGL == true){OprIIpUaGL = false;}
      if(csHOBEDwUq == true){csHOBEDwUq = false;}
      if(VRGnrNJlep == true){VRGnrNJlep = false;}
      if(ezoKdMZpCH == true){ezoKdMZpCH = false;}
      if(ScCBdkwUfm == true){ScCBdkwUfm = false;}
      if(bqFyNwiDPu == true){bqFyNwiDPu = false;}
      if(fiuQfdEwjo == true){fiuQfdEwjo = false;}
      if(dMtNYsPEJH == true){dMtNYsPEJH = false;}
      if(RoGqNntpxg == true){RoGqNntpxg = false;}
      if(cVaGaiglVA == true){cVaGaiglVA = false;}
      if(fzjpJPwrZU == true){fzjpJPwrZU = false;}
      if(getIdqcECr == true){getIdqcECr = false;}
      if(iNzDMHlmlo == true){iNzDMHlmlo = false;}
      if(LdiIaREPhy == true){LdiIaREPhy = false;}
      if(rCQczybRcj == true){rCQczybRcj = false;}
      if(GcicQSzfcC == true){GcicQSzfcC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TALYZQGWWS
{ 
  void UdZDtOzgnS()
  { 
      bool omIkBZhAjF = false;
      bool UCOpKyjSNS = false;
      bool gkCpmUdMVG = false;
      bool JWTGUVZaVr = false;
      bool hYnukbzppC = false;
      bool xjKMSDjRyg = false;
      bool uVecwyhHUn = false;
      bool XJxUkHxGFL = false;
      bool UmVSJYLGmR = false;
      bool kIboxLtKzm = false;
      bool sqUBdmloaK = false;
      bool FcMlLHzLTW = false;
      bool lbUDDPgIXZ = false;
      bool NmHRSdSUoV = false;
      bool mWebLIwpdo = false;
      bool LipcAQVRyN = false;
      bool FdQBxSVtTg = false;
      bool oeWxjPwrqu = false;
      bool TqdiNdweRB = false;
      bool HAWaQIFdds = false;
      string fkbAmZtire;
      string smPOPqxQBl;
      string eEpMqpjNQk;
      string UxzpmAdiyr;
      string IsgBUDqNXe;
      string idGMfauPIw;
      string ogRGJwmYbO;
      string NORJdlWnrm;
      string yWpkCqpmJL;
      string FNZBCaaaqX;
      string QRlIRUMxht;
      string DGXUySqfES;
      string FAPPIznPGC;
      string KwxTWfjgTh;
      string dsEPIypFDj;
      string juWYRQCVAS;
      string gwpfiHJDxR;
      string hKMWnMuAHJ;
      string IhMWRPZXBG;
      string dNfAAhDYfA;
      if(fkbAmZtire == QRlIRUMxht){omIkBZhAjF = true;}
      else if(QRlIRUMxht == fkbAmZtire){sqUBdmloaK = true;}
      if(smPOPqxQBl == DGXUySqfES){UCOpKyjSNS = true;}
      else if(DGXUySqfES == smPOPqxQBl){FcMlLHzLTW = true;}
      if(eEpMqpjNQk == FAPPIznPGC){gkCpmUdMVG = true;}
      else if(FAPPIznPGC == eEpMqpjNQk){lbUDDPgIXZ = true;}
      if(UxzpmAdiyr == KwxTWfjgTh){JWTGUVZaVr = true;}
      else if(KwxTWfjgTh == UxzpmAdiyr){NmHRSdSUoV = true;}
      if(IsgBUDqNXe == dsEPIypFDj){hYnukbzppC = true;}
      else if(dsEPIypFDj == IsgBUDqNXe){mWebLIwpdo = true;}
      if(idGMfauPIw == juWYRQCVAS){xjKMSDjRyg = true;}
      else if(juWYRQCVAS == idGMfauPIw){LipcAQVRyN = true;}
      if(ogRGJwmYbO == gwpfiHJDxR){uVecwyhHUn = true;}
      else if(gwpfiHJDxR == ogRGJwmYbO){FdQBxSVtTg = true;}
      if(NORJdlWnrm == hKMWnMuAHJ){XJxUkHxGFL = true;}
      if(yWpkCqpmJL == IhMWRPZXBG){UmVSJYLGmR = true;}
      if(FNZBCaaaqX == dNfAAhDYfA){kIboxLtKzm = true;}
      while(hKMWnMuAHJ == NORJdlWnrm){oeWxjPwrqu = true;}
      while(IhMWRPZXBG == IhMWRPZXBG){TqdiNdweRB = true;}
      while(dNfAAhDYfA == dNfAAhDYfA){HAWaQIFdds = true;}
      if(omIkBZhAjF == true){omIkBZhAjF = false;}
      if(UCOpKyjSNS == true){UCOpKyjSNS = false;}
      if(gkCpmUdMVG == true){gkCpmUdMVG = false;}
      if(JWTGUVZaVr == true){JWTGUVZaVr = false;}
      if(hYnukbzppC == true){hYnukbzppC = false;}
      if(xjKMSDjRyg == true){xjKMSDjRyg = false;}
      if(uVecwyhHUn == true){uVecwyhHUn = false;}
      if(XJxUkHxGFL == true){XJxUkHxGFL = false;}
      if(UmVSJYLGmR == true){UmVSJYLGmR = false;}
      if(kIboxLtKzm == true){kIboxLtKzm = false;}
      if(sqUBdmloaK == true){sqUBdmloaK = false;}
      if(FcMlLHzLTW == true){FcMlLHzLTW = false;}
      if(lbUDDPgIXZ == true){lbUDDPgIXZ = false;}
      if(NmHRSdSUoV == true){NmHRSdSUoV = false;}
      if(mWebLIwpdo == true){mWebLIwpdo = false;}
      if(LipcAQVRyN == true){LipcAQVRyN = false;}
      if(FdQBxSVtTg == true){FdQBxSVtTg = false;}
      if(oeWxjPwrqu == true){oeWxjPwrqu = false;}
      if(TqdiNdweRB == true){TqdiNdweRB = false;}
      if(HAWaQIFdds == true){HAWaQIFdds = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IGMGWKYIPS
{ 
  void nNKmeISkLc()
  { 
      bool zSHUwlusuZ = false;
      bool fKGQwtttrF = false;
      bool usVSOezFwF = false;
      bool CTimdzVeiw = false;
      bool GVDsbauTtz = false;
      bool ycCncFxnGQ = false;
      bool mpwoWLbTmx = false;
      bool XOKuyZpbqm = false;
      bool jeLxGYRtJX = false;
      bool BhYRJQYNVP = false;
      bool zagxbjSGoC = false;
      bool PUxTgHeziy = false;
      bool thJPupprlh = false;
      bool AcFanIyOVW = false;
      bool GKEHIgjFkC = false;
      bool lZdXUQQRBk = false;
      bool sZUHClPWeX = false;
      bool IPdMrjcCGO = false;
      bool GkHjwZyhFW = false;
      bool rgMjcfoxEV = false;
      string BwIXbITTid;
      string CUmbdALqBs;
      string gApMGDaHWU;
      string oBeArgLgWN;
      string zqHTXVHuMc;
      string PkVbtAFwQX;
      string hLwNoBomjw;
      string odUntprWnk;
      string ufutEDeDGq;
      string aPPyemuseV;
      string gULPnlQhhD;
      string IiHfbBQCJk;
      string WkfsUZNVIG;
      string uyqSEaUfFS;
      string mwVChqHjVd;
      string WrjszunRtO;
      string XtYaIJrobB;
      string gjwqyZOcKd;
      string RdAeiCOySI;
      string lCkqtsXutX;
      if(BwIXbITTid == gULPnlQhhD){zSHUwlusuZ = true;}
      else if(gULPnlQhhD == BwIXbITTid){zagxbjSGoC = true;}
      if(CUmbdALqBs == IiHfbBQCJk){fKGQwtttrF = true;}
      else if(IiHfbBQCJk == CUmbdALqBs){PUxTgHeziy = true;}
      if(gApMGDaHWU == WkfsUZNVIG){usVSOezFwF = true;}
      else if(WkfsUZNVIG == gApMGDaHWU){thJPupprlh = true;}
      if(oBeArgLgWN == uyqSEaUfFS){CTimdzVeiw = true;}
      else if(uyqSEaUfFS == oBeArgLgWN){AcFanIyOVW = true;}
      if(zqHTXVHuMc == mwVChqHjVd){GVDsbauTtz = true;}
      else if(mwVChqHjVd == zqHTXVHuMc){GKEHIgjFkC = true;}
      if(PkVbtAFwQX == WrjszunRtO){ycCncFxnGQ = true;}
      else if(WrjszunRtO == PkVbtAFwQX){lZdXUQQRBk = true;}
      if(hLwNoBomjw == XtYaIJrobB){mpwoWLbTmx = true;}
      else if(XtYaIJrobB == hLwNoBomjw){sZUHClPWeX = true;}
      if(odUntprWnk == gjwqyZOcKd){XOKuyZpbqm = true;}
      if(ufutEDeDGq == RdAeiCOySI){jeLxGYRtJX = true;}
      if(aPPyemuseV == lCkqtsXutX){BhYRJQYNVP = true;}
      while(gjwqyZOcKd == odUntprWnk){IPdMrjcCGO = true;}
      while(RdAeiCOySI == RdAeiCOySI){GkHjwZyhFW = true;}
      while(lCkqtsXutX == lCkqtsXutX){rgMjcfoxEV = true;}
      if(zSHUwlusuZ == true){zSHUwlusuZ = false;}
      if(fKGQwtttrF == true){fKGQwtttrF = false;}
      if(usVSOezFwF == true){usVSOezFwF = false;}
      if(CTimdzVeiw == true){CTimdzVeiw = false;}
      if(GVDsbauTtz == true){GVDsbauTtz = false;}
      if(ycCncFxnGQ == true){ycCncFxnGQ = false;}
      if(mpwoWLbTmx == true){mpwoWLbTmx = false;}
      if(XOKuyZpbqm == true){XOKuyZpbqm = false;}
      if(jeLxGYRtJX == true){jeLxGYRtJX = false;}
      if(BhYRJQYNVP == true){BhYRJQYNVP = false;}
      if(zagxbjSGoC == true){zagxbjSGoC = false;}
      if(PUxTgHeziy == true){PUxTgHeziy = false;}
      if(thJPupprlh == true){thJPupprlh = false;}
      if(AcFanIyOVW == true){AcFanIyOVW = false;}
      if(GKEHIgjFkC == true){GKEHIgjFkC = false;}
      if(lZdXUQQRBk == true){lZdXUQQRBk = false;}
      if(sZUHClPWeX == true){sZUHClPWeX = false;}
      if(IPdMrjcCGO == true){IPdMrjcCGO = false;}
      if(GkHjwZyhFW == true){GkHjwZyhFW = false;}
      if(rgMjcfoxEV == true){rgMjcfoxEV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFPYPKGLNH
{ 
  void DaDiDaMCDQ()
  { 
      bool ZSCWjndDPN = false;
      bool cXMbXWFzsX = false;
      bool RnPfaCdpuL = false;
      bool yPQVZAoVZU = false;
      bool AntteiGmpS = false;
      bool HyLVllCWwh = false;
      bool JnHDPNGpBX = false;
      bool hiZYWctVAq = false;
      bool uqAbEzDuim = false;
      bool xSZqKMfpdR = false;
      bool cPkSjYYmyJ = false;
      bool rgVFmSmezP = false;
      bool JLHNZOIhNK = false;
      bool wDqiOeGhre = false;
      bool aQxZuQxUEq = false;
      bool YAqOHRIWrU = false;
      bool PpYnMoolpH = false;
      bool MFmTnrOgSI = false;
      bool RndWkwMbax = false;
      bool WipWPjrING = false;
      string fNGyYtPQOX;
      string oQBnjActix;
      string SgrgZconAU;
      string dEsjApHJVk;
      string rKWTzwDMus;
      string RUWwYyVYXu;
      string EbQstkXQnt;
      string rTXxFHJYhd;
      string ZcrGDIgxLB;
      string UhkZgPsdZO;
      string XlXBBywZpQ;
      string owqtVajKpk;
      string DaElYJiyQo;
      string NfySFnFqFE;
      string LHGuMXqqEG;
      string finoKxglbq;
      string OyJBCIyXng;
      string VrEkYwTJYA;
      string SrsJIeqJII;
      string GSOOpMxEsD;
      if(fNGyYtPQOX == XlXBBywZpQ){ZSCWjndDPN = true;}
      else if(XlXBBywZpQ == fNGyYtPQOX){cPkSjYYmyJ = true;}
      if(oQBnjActix == owqtVajKpk){cXMbXWFzsX = true;}
      else if(owqtVajKpk == oQBnjActix){rgVFmSmezP = true;}
      if(SgrgZconAU == DaElYJiyQo){RnPfaCdpuL = true;}
      else if(DaElYJiyQo == SgrgZconAU){JLHNZOIhNK = true;}
      if(dEsjApHJVk == NfySFnFqFE){yPQVZAoVZU = true;}
      else if(NfySFnFqFE == dEsjApHJVk){wDqiOeGhre = true;}
      if(rKWTzwDMus == LHGuMXqqEG){AntteiGmpS = true;}
      else if(LHGuMXqqEG == rKWTzwDMus){aQxZuQxUEq = true;}
      if(RUWwYyVYXu == finoKxglbq){HyLVllCWwh = true;}
      else if(finoKxglbq == RUWwYyVYXu){YAqOHRIWrU = true;}
      if(EbQstkXQnt == OyJBCIyXng){JnHDPNGpBX = true;}
      else if(OyJBCIyXng == EbQstkXQnt){PpYnMoolpH = true;}
      if(rTXxFHJYhd == VrEkYwTJYA){hiZYWctVAq = true;}
      if(ZcrGDIgxLB == SrsJIeqJII){uqAbEzDuim = true;}
      if(UhkZgPsdZO == GSOOpMxEsD){xSZqKMfpdR = true;}
      while(VrEkYwTJYA == rTXxFHJYhd){MFmTnrOgSI = true;}
      while(SrsJIeqJII == SrsJIeqJII){RndWkwMbax = true;}
      while(GSOOpMxEsD == GSOOpMxEsD){WipWPjrING = true;}
      if(ZSCWjndDPN == true){ZSCWjndDPN = false;}
      if(cXMbXWFzsX == true){cXMbXWFzsX = false;}
      if(RnPfaCdpuL == true){RnPfaCdpuL = false;}
      if(yPQVZAoVZU == true){yPQVZAoVZU = false;}
      if(AntteiGmpS == true){AntteiGmpS = false;}
      if(HyLVllCWwh == true){HyLVllCWwh = false;}
      if(JnHDPNGpBX == true){JnHDPNGpBX = false;}
      if(hiZYWctVAq == true){hiZYWctVAq = false;}
      if(uqAbEzDuim == true){uqAbEzDuim = false;}
      if(xSZqKMfpdR == true){xSZqKMfpdR = false;}
      if(cPkSjYYmyJ == true){cPkSjYYmyJ = false;}
      if(rgVFmSmezP == true){rgVFmSmezP = false;}
      if(JLHNZOIhNK == true){JLHNZOIhNK = false;}
      if(wDqiOeGhre == true){wDqiOeGhre = false;}
      if(aQxZuQxUEq == true){aQxZuQxUEq = false;}
      if(YAqOHRIWrU == true){YAqOHRIWrU = false;}
      if(PpYnMoolpH == true){PpYnMoolpH = false;}
      if(MFmTnrOgSI == true){MFmTnrOgSI = false;}
      if(RndWkwMbax == true){RndWkwMbax = false;}
      if(WipWPjrING == true){WipWPjrING = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HASPAOGNZQ
{ 
  void cOJShimqEw()
  { 
      bool pwmzVazEXY = false;
      bool ctuSrYqnxM = false;
      bool jOcSeUjgFG = false;
      bool OQyChcYgLU = false;
      bool dOWMugVioR = false;
      bool tnaxbbTTTA = false;
      bool qSzQKLwrkO = false;
      bool AJbbhVqPXy = false;
      bool zArmMaoAaG = false;
      bool JENLdKOGCi = false;
      bool jcxZRjLyOF = false;
      bool jDwVBpaLDi = false;
      bool WwReFuwQyW = false;
      bool GkNoOVDSVc = false;
      bool PpkUVFIrJn = false;
      bool jDCSMnLSTV = false;
      bool mtAqzypGGe = false;
      bool mHpaTfKwIA = false;
      bool mEGJmDitcZ = false;
      bool KjzzoUpsVX = false;
      string LQncMILpIj;
      string bBSaNaUzNi;
      string HsSMZlcVZh;
      string MeXeHSIQSC;
      string hpzoDGyKKW;
      string erVCySxbCa;
      string fpPZWxdnTt;
      string SDfLARscIT;
      string nRKDCUIUfo;
      string UfNrVrZYRF;
      string bJpQEaLKCg;
      string YUSilOfMXC;
      string oIHeYlpmoI;
      string qUKDqdbsya;
      string JxSzPAMeGH;
      string MNBPQSCKqR;
      string jXVsoDJPqH;
      string llNwrqpHOY;
      string ZLggwcTtlX;
      string bRCgpkbYJM;
      if(LQncMILpIj == bJpQEaLKCg){pwmzVazEXY = true;}
      else if(bJpQEaLKCg == LQncMILpIj){jcxZRjLyOF = true;}
      if(bBSaNaUzNi == YUSilOfMXC){ctuSrYqnxM = true;}
      else if(YUSilOfMXC == bBSaNaUzNi){jDwVBpaLDi = true;}
      if(HsSMZlcVZh == oIHeYlpmoI){jOcSeUjgFG = true;}
      else if(oIHeYlpmoI == HsSMZlcVZh){WwReFuwQyW = true;}
      if(MeXeHSIQSC == qUKDqdbsya){OQyChcYgLU = true;}
      else if(qUKDqdbsya == MeXeHSIQSC){GkNoOVDSVc = true;}
      if(hpzoDGyKKW == JxSzPAMeGH){dOWMugVioR = true;}
      else if(JxSzPAMeGH == hpzoDGyKKW){PpkUVFIrJn = true;}
      if(erVCySxbCa == MNBPQSCKqR){tnaxbbTTTA = true;}
      else if(MNBPQSCKqR == erVCySxbCa){jDCSMnLSTV = true;}
      if(fpPZWxdnTt == jXVsoDJPqH){qSzQKLwrkO = true;}
      else if(jXVsoDJPqH == fpPZWxdnTt){mtAqzypGGe = true;}
      if(SDfLARscIT == llNwrqpHOY){AJbbhVqPXy = true;}
      if(nRKDCUIUfo == ZLggwcTtlX){zArmMaoAaG = true;}
      if(UfNrVrZYRF == bRCgpkbYJM){JENLdKOGCi = true;}
      while(llNwrqpHOY == SDfLARscIT){mHpaTfKwIA = true;}
      while(ZLggwcTtlX == ZLggwcTtlX){mEGJmDitcZ = true;}
      while(bRCgpkbYJM == bRCgpkbYJM){KjzzoUpsVX = true;}
      if(pwmzVazEXY == true){pwmzVazEXY = false;}
      if(ctuSrYqnxM == true){ctuSrYqnxM = false;}
      if(jOcSeUjgFG == true){jOcSeUjgFG = false;}
      if(OQyChcYgLU == true){OQyChcYgLU = false;}
      if(dOWMugVioR == true){dOWMugVioR = false;}
      if(tnaxbbTTTA == true){tnaxbbTTTA = false;}
      if(qSzQKLwrkO == true){qSzQKLwrkO = false;}
      if(AJbbhVqPXy == true){AJbbhVqPXy = false;}
      if(zArmMaoAaG == true){zArmMaoAaG = false;}
      if(JENLdKOGCi == true){JENLdKOGCi = false;}
      if(jcxZRjLyOF == true){jcxZRjLyOF = false;}
      if(jDwVBpaLDi == true){jDwVBpaLDi = false;}
      if(WwReFuwQyW == true){WwReFuwQyW = false;}
      if(GkNoOVDSVc == true){GkNoOVDSVc = false;}
      if(PpkUVFIrJn == true){PpkUVFIrJn = false;}
      if(jDCSMnLSTV == true){jDCSMnLSTV = false;}
      if(mtAqzypGGe == true){mtAqzypGGe = false;}
      if(mHpaTfKwIA == true){mHpaTfKwIA = false;}
      if(mEGJmDitcZ == true){mEGJmDitcZ = false;}
      if(KjzzoUpsVX == true){KjzzoUpsVX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ODKXYSENLV
{ 
  void nRdquuuarV()
  { 
      bool crUtAwyDne = false;
      bool SirylbBBEi = false;
      bool domYJBxBkH = false;
      bool KxKZLgbeHc = false;
      bool ScjrrAJCmT = false;
      bool CJbJpmFwkz = false;
      bool zxRfTUXSmF = false;
      bool zVsbPAFufI = false;
      bool rtORFBUAiX = false;
      bool aftIcVLDXW = false;
      bool cpPgTfPAso = false;
      bool gKQbHEizaS = false;
      bool AWiOdTbkyt = false;
      bool oCWIfBdgxY = false;
      bool kTGtpQORBX = false;
      bool mLcEWFGBDA = false;
      bool EeBzzemHwF = false;
      bool aBBBhfQoXM = false;
      bool EJiZGdYRla = false;
      bool tbcxUGSHtK = false;
      string GYiUJeXLPl;
      string wJuJltispd;
      string xfWlgineaT;
      string YQKIfegjck;
      string aVeFWlZoYB;
      string ZEaAUaCwmZ;
      string pskuMfzmdH;
      string MzPFCbAQOu;
      string JzGYtUoJmF;
      string bjxDthkjrq;
      string mmKRnanUyr;
      string ZkhrPqmLAr;
      string pozYebBMLT;
      string qPXXIWnnkT;
      string fULuepCEmD;
      string uYjAAxmlmL;
      string YbJdBKNJjs;
      string CyagMVdEtn;
      string ZxZIYRfXWL;
      string iBBYuEKgsT;
      if(GYiUJeXLPl == mmKRnanUyr){crUtAwyDne = true;}
      else if(mmKRnanUyr == GYiUJeXLPl){cpPgTfPAso = true;}
      if(wJuJltispd == ZkhrPqmLAr){SirylbBBEi = true;}
      else if(ZkhrPqmLAr == wJuJltispd){gKQbHEizaS = true;}
      if(xfWlgineaT == pozYebBMLT){domYJBxBkH = true;}
      else if(pozYebBMLT == xfWlgineaT){AWiOdTbkyt = true;}
      if(YQKIfegjck == qPXXIWnnkT){KxKZLgbeHc = true;}
      else if(qPXXIWnnkT == YQKIfegjck){oCWIfBdgxY = true;}
      if(aVeFWlZoYB == fULuepCEmD){ScjrrAJCmT = true;}
      else if(fULuepCEmD == aVeFWlZoYB){kTGtpQORBX = true;}
      if(ZEaAUaCwmZ == uYjAAxmlmL){CJbJpmFwkz = true;}
      else if(uYjAAxmlmL == ZEaAUaCwmZ){mLcEWFGBDA = true;}
      if(pskuMfzmdH == YbJdBKNJjs){zxRfTUXSmF = true;}
      else if(YbJdBKNJjs == pskuMfzmdH){EeBzzemHwF = true;}
      if(MzPFCbAQOu == CyagMVdEtn){zVsbPAFufI = true;}
      if(JzGYtUoJmF == ZxZIYRfXWL){rtORFBUAiX = true;}
      if(bjxDthkjrq == iBBYuEKgsT){aftIcVLDXW = true;}
      while(CyagMVdEtn == MzPFCbAQOu){aBBBhfQoXM = true;}
      while(ZxZIYRfXWL == ZxZIYRfXWL){EJiZGdYRla = true;}
      while(iBBYuEKgsT == iBBYuEKgsT){tbcxUGSHtK = true;}
      if(crUtAwyDne == true){crUtAwyDne = false;}
      if(SirylbBBEi == true){SirylbBBEi = false;}
      if(domYJBxBkH == true){domYJBxBkH = false;}
      if(KxKZLgbeHc == true){KxKZLgbeHc = false;}
      if(ScjrrAJCmT == true){ScjrrAJCmT = false;}
      if(CJbJpmFwkz == true){CJbJpmFwkz = false;}
      if(zxRfTUXSmF == true){zxRfTUXSmF = false;}
      if(zVsbPAFufI == true){zVsbPAFufI = false;}
      if(rtORFBUAiX == true){rtORFBUAiX = false;}
      if(aftIcVLDXW == true){aftIcVLDXW = false;}
      if(cpPgTfPAso == true){cpPgTfPAso = false;}
      if(gKQbHEizaS == true){gKQbHEizaS = false;}
      if(AWiOdTbkyt == true){AWiOdTbkyt = false;}
      if(oCWIfBdgxY == true){oCWIfBdgxY = false;}
      if(kTGtpQORBX == true){kTGtpQORBX = false;}
      if(mLcEWFGBDA == true){mLcEWFGBDA = false;}
      if(EeBzzemHwF == true){EeBzzemHwF = false;}
      if(aBBBhfQoXM == true){aBBBhfQoXM = false;}
      if(EJiZGdYRla == true){EJiZGdYRla = false;}
      if(tbcxUGSHtK == true){tbcxUGSHtK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BBDBUQUHLM
{ 
  void VxOHNzpNui()
  { 
      bool ITgBBmPmxe = false;
      bool gqrxGxuLGp = false;
      bool UmNnLPCNEd = false;
      bool qHrTtBqfIN = false;
      bool WXZbYVEHHN = false;
      bool aEylxUGspk = false;
      bool jBhTmYzYDF = false;
      bool FPCsTxNlOo = false;
      bool LuFpCmJFVY = false;
      bool tyoXcUoFnA = false;
      bool WfECIKBFSA = false;
      bool HUeAZouqQA = false;
      bool PsCdKHZePy = false;
      bool HHyOSepDhr = false;
      bool kDlVRZTnxn = false;
      bool YynmjcdarB = false;
      bool kWoUrzWPht = false;
      bool yrJYPLGfMj = false;
      bool nkgaZJTKeo = false;
      bool BPLfGNORcR = false;
      string aBRzyZONBw;
      string cSqkSyLXPJ;
      string qQDdhkqVUz;
      string JDbGExnnmm;
      string DCCjFMXxru;
      string uWWKuJymQM;
      string irrBlYqkfU;
      string KXjcGnOSYV;
      string MsdZElfQLt;
      string yBWaEKKAxf;
      string UmQWjWltDG;
      string ufNuzoORxA;
      string sZZlVIBIYw;
      string dOUsAZbGpg;
      string AkMEzSnbaO;
      string urDxltMeAa;
      string VdVHbfKTtY;
      string MIbPAHNUlD;
      string UYhKAlLWGG;
      string NxFOKVPFcS;
      if(aBRzyZONBw == UmQWjWltDG){ITgBBmPmxe = true;}
      else if(UmQWjWltDG == aBRzyZONBw){WfECIKBFSA = true;}
      if(cSqkSyLXPJ == ufNuzoORxA){gqrxGxuLGp = true;}
      else if(ufNuzoORxA == cSqkSyLXPJ){HUeAZouqQA = true;}
      if(qQDdhkqVUz == sZZlVIBIYw){UmNnLPCNEd = true;}
      else if(sZZlVIBIYw == qQDdhkqVUz){PsCdKHZePy = true;}
      if(JDbGExnnmm == dOUsAZbGpg){qHrTtBqfIN = true;}
      else if(dOUsAZbGpg == JDbGExnnmm){HHyOSepDhr = true;}
      if(DCCjFMXxru == AkMEzSnbaO){WXZbYVEHHN = true;}
      else if(AkMEzSnbaO == DCCjFMXxru){kDlVRZTnxn = true;}
      if(uWWKuJymQM == urDxltMeAa){aEylxUGspk = true;}
      else if(urDxltMeAa == uWWKuJymQM){YynmjcdarB = true;}
      if(irrBlYqkfU == VdVHbfKTtY){jBhTmYzYDF = true;}
      else if(VdVHbfKTtY == irrBlYqkfU){kWoUrzWPht = true;}
      if(KXjcGnOSYV == MIbPAHNUlD){FPCsTxNlOo = true;}
      if(MsdZElfQLt == UYhKAlLWGG){LuFpCmJFVY = true;}
      if(yBWaEKKAxf == NxFOKVPFcS){tyoXcUoFnA = true;}
      while(MIbPAHNUlD == KXjcGnOSYV){yrJYPLGfMj = true;}
      while(UYhKAlLWGG == UYhKAlLWGG){nkgaZJTKeo = true;}
      while(NxFOKVPFcS == NxFOKVPFcS){BPLfGNORcR = true;}
      if(ITgBBmPmxe == true){ITgBBmPmxe = false;}
      if(gqrxGxuLGp == true){gqrxGxuLGp = false;}
      if(UmNnLPCNEd == true){UmNnLPCNEd = false;}
      if(qHrTtBqfIN == true){qHrTtBqfIN = false;}
      if(WXZbYVEHHN == true){WXZbYVEHHN = false;}
      if(aEylxUGspk == true){aEylxUGspk = false;}
      if(jBhTmYzYDF == true){jBhTmYzYDF = false;}
      if(FPCsTxNlOo == true){FPCsTxNlOo = false;}
      if(LuFpCmJFVY == true){LuFpCmJFVY = false;}
      if(tyoXcUoFnA == true){tyoXcUoFnA = false;}
      if(WfECIKBFSA == true){WfECIKBFSA = false;}
      if(HUeAZouqQA == true){HUeAZouqQA = false;}
      if(PsCdKHZePy == true){PsCdKHZePy = false;}
      if(HHyOSepDhr == true){HHyOSepDhr = false;}
      if(kDlVRZTnxn == true){kDlVRZTnxn = false;}
      if(YynmjcdarB == true){YynmjcdarB = false;}
      if(kWoUrzWPht == true){kWoUrzWPht = false;}
      if(yrJYPLGfMj == true){yrJYPLGfMj = false;}
      if(nkgaZJTKeo == true){nkgaZJTKeo = false;}
      if(BPLfGNORcR == true){BPLfGNORcR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EDXZPPGLIV
{ 
  void zcGihexiHE()
  { 
      bool iKQrPjUmVc = false;
      bool GfqGLwLhUu = false;
      bool qhpPjOYbcs = false;
      bool HDzMLOHpRk = false;
      bool EnoKynxWfR = false;
      bool IfXxeBTBIB = false;
      bool LsKcUDfeux = false;
      bool nVQjqDrfQu = false;
      bool RBwKjbeCgJ = false;
      bool tGgQZKcMpu = false;
      bool IRbhcmPnFa = false;
      bool InjMiJwzrs = false;
      bool XcxkChnzJf = false;
      bool ZepVmzZNhw = false;
      bool MqxGBGVUgP = false;
      bool NdTxWeTpft = false;
      bool yPdZAdyNZi = false;
      bool jiRwfgfqjw = false;
      bool MTRtRwKszH = false;
      bool fihmxwMWFW = false;
      string coqKQZxNHJ;
      string EWZbDcGhGa;
      string AxqmqztOrT;
      string oFHZrOJhKR;
      string BDphAzdhMR;
      string EyGYdexDTR;
      string eiUnUzPAjn;
      string TYXnZwHImq;
      string VMCZOpyiuM;
      string QFNrlSiCNA;
      string jcxXyfZSyh;
      string XnQbwSftYd;
      string BgFXWNKeBH;
      string NEulHrOdbi;
      string PejMocokwT;
      string lncjyCXZAj;
      string UtQqUSsdUD;
      string DBSpNVwrht;
      string YYihVYaLmE;
      string TncqNUOsrV;
      if(coqKQZxNHJ == jcxXyfZSyh){iKQrPjUmVc = true;}
      else if(jcxXyfZSyh == coqKQZxNHJ){IRbhcmPnFa = true;}
      if(EWZbDcGhGa == XnQbwSftYd){GfqGLwLhUu = true;}
      else if(XnQbwSftYd == EWZbDcGhGa){InjMiJwzrs = true;}
      if(AxqmqztOrT == BgFXWNKeBH){qhpPjOYbcs = true;}
      else if(BgFXWNKeBH == AxqmqztOrT){XcxkChnzJf = true;}
      if(oFHZrOJhKR == NEulHrOdbi){HDzMLOHpRk = true;}
      else if(NEulHrOdbi == oFHZrOJhKR){ZepVmzZNhw = true;}
      if(BDphAzdhMR == PejMocokwT){EnoKynxWfR = true;}
      else if(PejMocokwT == BDphAzdhMR){MqxGBGVUgP = true;}
      if(EyGYdexDTR == lncjyCXZAj){IfXxeBTBIB = true;}
      else if(lncjyCXZAj == EyGYdexDTR){NdTxWeTpft = true;}
      if(eiUnUzPAjn == UtQqUSsdUD){LsKcUDfeux = true;}
      else if(UtQqUSsdUD == eiUnUzPAjn){yPdZAdyNZi = true;}
      if(TYXnZwHImq == DBSpNVwrht){nVQjqDrfQu = true;}
      if(VMCZOpyiuM == YYihVYaLmE){RBwKjbeCgJ = true;}
      if(QFNrlSiCNA == TncqNUOsrV){tGgQZKcMpu = true;}
      while(DBSpNVwrht == TYXnZwHImq){jiRwfgfqjw = true;}
      while(YYihVYaLmE == YYihVYaLmE){MTRtRwKszH = true;}
      while(TncqNUOsrV == TncqNUOsrV){fihmxwMWFW = true;}
      if(iKQrPjUmVc == true){iKQrPjUmVc = false;}
      if(GfqGLwLhUu == true){GfqGLwLhUu = false;}
      if(qhpPjOYbcs == true){qhpPjOYbcs = false;}
      if(HDzMLOHpRk == true){HDzMLOHpRk = false;}
      if(EnoKynxWfR == true){EnoKynxWfR = false;}
      if(IfXxeBTBIB == true){IfXxeBTBIB = false;}
      if(LsKcUDfeux == true){LsKcUDfeux = false;}
      if(nVQjqDrfQu == true){nVQjqDrfQu = false;}
      if(RBwKjbeCgJ == true){RBwKjbeCgJ = false;}
      if(tGgQZKcMpu == true){tGgQZKcMpu = false;}
      if(IRbhcmPnFa == true){IRbhcmPnFa = false;}
      if(InjMiJwzrs == true){InjMiJwzrs = false;}
      if(XcxkChnzJf == true){XcxkChnzJf = false;}
      if(ZepVmzZNhw == true){ZepVmzZNhw = false;}
      if(MqxGBGVUgP == true){MqxGBGVUgP = false;}
      if(NdTxWeTpft == true){NdTxWeTpft = false;}
      if(yPdZAdyNZi == true){yPdZAdyNZi = false;}
      if(jiRwfgfqjw == true){jiRwfgfqjw = false;}
      if(MTRtRwKszH == true){MTRtRwKszH = false;}
      if(fihmxwMWFW == true){fihmxwMWFW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CSZBPNXCPV
{ 
  void knwwqamwJO()
  { 
      bool UNYLxorTBX = false;
      bool AjsyCNyjKo = false;
      bool QbFEamazqj = false;
      bool GBHaRqmsYk = false;
      bool KJCYaxfrDI = false;
      bool afqufsHUkJ = false;
      bool OsbRRybSgL = false;
      bool ZFLZeGYfdc = false;
      bool GhuiIZJLuX = false;
      bool iRHOVRgjHb = false;
      bool VNLrhVURQY = false;
      bool TbqICgxsJq = false;
      bool nPXJbIxwEN = false;
      bool YnXBGsWDAl = false;
      bool FruVDHZzLn = false;
      bool UmaQmFpBQZ = false;
      bool YXMCAeDoBJ = false;
      bool KssWkwUBFT = false;
      bool hxjPskNHOA = false;
      bool CUmaNhfrVY = false;
      string nMFXglHVIj;
      string BNeHnYraok;
      string BjDbeEKKHM;
      string rwMjyEpJPr;
      string AgjptztnIN;
      string ZmkENDIcrc;
      string bxNurFBtIi;
      string iiLxkTzNgf;
      string KWCsmEKHWu;
      string uMRlQCSoyo;
      string yzeYeqbmTs;
      string EuuMSFuUIm;
      string tsWNmWRYgh;
      string BKPrgKqcOu;
      string cWndpAQETK;
      string HygLuFcQkI;
      string ZDGkrtfDeI;
      string NRFMJWEsWl;
      string FMEVZCdDxa;
      string gZqGVZQCkw;
      if(nMFXglHVIj == yzeYeqbmTs){UNYLxorTBX = true;}
      else if(yzeYeqbmTs == nMFXglHVIj){VNLrhVURQY = true;}
      if(BNeHnYraok == EuuMSFuUIm){AjsyCNyjKo = true;}
      else if(EuuMSFuUIm == BNeHnYraok){TbqICgxsJq = true;}
      if(BjDbeEKKHM == tsWNmWRYgh){QbFEamazqj = true;}
      else if(tsWNmWRYgh == BjDbeEKKHM){nPXJbIxwEN = true;}
      if(rwMjyEpJPr == BKPrgKqcOu){GBHaRqmsYk = true;}
      else if(BKPrgKqcOu == rwMjyEpJPr){YnXBGsWDAl = true;}
      if(AgjptztnIN == cWndpAQETK){KJCYaxfrDI = true;}
      else if(cWndpAQETK == AgjptztnIN){FruVDHZzLn = true;}
      if(ZmkENDIcrc == HygLuFcQkI){afqufsHUkJ = true;}
      else if(HygLuFcQkI == ZmkENDIcrc){UmaQmFpBQZ = true;}
      if(bxNurFBtIi == ZDGkrtfDeI){OsbRRybSgL = true;}
      else if(ZDGkrtfDeI == bxNurFBtIi){YXMCAeDoBJ = true;}
      if(iiLxkTzNgf == NRFMJWEsWl){ZFLZeGYfdc = true;}
      if(KWCsmEKHWu == FMEVZCdDxa){GhuiIZJLuX = true;}
      if(uMRlQCSoyo == gZqGVZQCkw){iRHOVRgjHb = true;}
      while(NRFMJWEsWl == iiLxkTzNgf){KssWkwUBFT = true;}
      while(FMEVZCdDxa == FMEVZCdDxa){hxjPskNHOA = true;}
      while(gZqGVZQCkw == gZqGVZQCkw){CUmaNhfrVY = true;}
      if(UNYLxorTBX == true){UNYLxorTBX = false;}
      if(AjsyCNyjKo == true){AjsyCNyjKo = false;}
      if(QbFEamazqj == true){QbFEamazqj = false;}
      if(GBHaRqmsYk == true){GBHaRqmsYk = false;}
      if(KJCYaxfrDI == true){KJCYaxfrDI = false;}
      if(afqufsHUkJ == true){afqufsHUkJ = false;}
      if(OsbRRybSgL == true){OsbRRybSgL = false;}
      if(ZFLZeGYfdc == true){ZFLZeGYfdc = false;}
      if(GhuiIZJLuX == true){GhuiIZJLuX = false;}
      if(iRHOVRgjHb == true){iRHOVRgjHb = false;}
      if(VNLrhVURQY == true){VNLrhVURQY = false;}
      if(TbqICgxsJq == true){TbqICgxsJq = false;}
      if(nPXJbIxwEN == true){nPXJbIxwEN = false;}
      if(YnXBGsWDAl == true){YnXBGsWDAl = false;}
      if(FruVDHZzLn == true){FruVDHZzLn = false;}
      if(UmaQmFpBQZ == true){UmaQmFpBQZ = false;}
      if(YXMCAeDoBJ == true){YXMCAeDoBJ = false;}
      if(KssWkwUBFT == true){KssWkwUBFT = false;}
      if(hxjPskNHOA == true){hxjPskNHOA = false;}
      if(CUmaNhfrVY == true){CUmaNhfrVY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IXSBSUYUVW
{ 
  void DCIMXTwDXa()
  { 
      bool qpZnBrNHVF = false;
      bool WGnHMwGKiF = false;
      bool hKOOusEmCH = false;
      bool dqcMpULKoh = false;
      bool bYOkOPsPEn = false;
      bool NSaxogbKrH = false;
      bool nZFOafcbQq = false;
      bool juUBdJucAe = false;
      bool AoiNtKPfXJ = false;
      bool sASgsBSAJh = false;
      bool lRyMDSxZSe = false;
      bool kyKMGzqqTP = false;
      bool PxDHxjbmHb = false;
      bool puSRripVKb = false;
      bool NpMrYuoFas = false;
      bool JbfsSoNqOS = false;
      bool pJRpooesUX = false;
      bool IVfrCZkKhC = false;
      bool tWMNSNOZyD = false;
      bool UzGrkDXVDi = false;
      string nfqQEWkULM;
      string acpcUYAKVX;
      string neSgyInXIy;
      string crgPigODar;
      string UWIifrmnzo;
      string oswHRJNKRu;
      string hMMMjhwZtn;
      string KwjcCQViBG;
      string VAYSJiwYxY;
      string SEkeKIKwzx;
      string uNtLdrJSEB;
      string meILZhnsDB;
      string kWbUVGLESt;
      string GYiDKHGMoQ;
      string YdUwkmuZFb;
      string TRsyMYkYpX;
      string gFAJtOuFAR;
      string aaElbHBejh;
      string Lkzpaofkpl;
      string VhWQjTcKCW;
      if(nfqQEWkULM == uNtLdrJSEB){qpZnBrNHVF = true;}
      else if(uNtLdrJSEB == nfqQEWkULM){lRyMDSxZSe = true;}
      if(acpcUYAKVX == meILZhnsDB){WGnHMwGKiF = true;}
      else if(meILZhnsDB == acpcUYAKVX){kyKMGzqqTP = true;}
      if(neSgyInXIy == kWbUVGLESt){hKOOusEmCH = true;}
      else if(kWbUVGLESt == neSgyInXIy){PxDHxjbmHb = true;}
      if(crgPigODar == GYiDKHGMoQ){dqcMpULKoh = true;}
      else if(GYiDKHGMoQ == crgPigODar){puSRripVKb = true;}
      if(UWIifrmnzo == YdUwkmuZFb){bYOkOPsPEn = true;}
      else if(YdUwkmuZFb == UWIifrmnzo){NpMrYuoFas = true;}
      if(oswHRJNKRu == TRsyMYkYpX){NSaxogbKrH = true;}
      else if(TRsyMYkYpX == oswHRJNKRu){JbfsSoNqOS = true;}
      if(hMMMjhwZtn == gFAJtOuFAR){nZFOafcbQq = true;}
      else if(gFAJtOuFAR == hMMMjhwZtn){pJRpooesUX = true;}
      if(KwjcCQViBG == aaElbHBejh){juUBdJucAe = true;}
      if(VAYSJiwYxY == Lkzpaofkpl){AoiNtKPfXJ = true;}
      if(SEkeKIKwzx == VhWQjTcKCW){sASgsBSAJh = true;}
      while(aaElbHBejh == KwjcCQViBG){IVfrCZkKhC = true;}
      while(Lkzpaofkpl == Lkzpaofkpl){tWMNSNOZyD = true;}
      while(VhWQjTcKCW == VhWQjTcKCW){UzGrkDXVDi = true;}
      if(qpZnBrNHVF == true){qpZnBrNHVF = false;}
      if(WGnHMwGKiF == true){WGnHMwGKiF = false;}
      if(hKOOusEmCH == true){hKOOusEmCH = false;}
      if(dqcMpULKoh == true){dqcMpULKoh = false;}
      if(bYOkOPsPEn == true){bYOkOPsPEn = false;}
      if(NSaxogbKrH == true){NSaxogbKrH = false;}
      if(nZFOafcbQq == true){nZFOafcbQq = false;}
      if(juUBdJucAe == true){juUBdJucAe = false;}
      if(AoiNtKPfXJ == true){AoiNtKPfXJ = false;}
      if(sASgsBSAJh == true){sASgsBSAJh = false;}
      if(lRyMDSxZSe == true){lRyMDSxZSe = false;}
      if(kyKMGzqqTP == true){kyKMGzqqTP = false;}
      if(PxDHxjbmHb == true){PxDHxjbmHb = false;}
      if(puSRripVKb == true){puSRripVKb = false;}
      if(NpMrYuoFas == true){NpMrYuoFas = false;}
      if(JbfsSoNqOS == true){JbfsSoNqOS = false;}
      if(pJRpooesUX == true){pJRpooesUX = false;}
      if(IVfrCZkKhC == true){IVfrCZkKhC = false;}
      if(tWMNSNOZyD == true){tWMNSNOZyD = false;}
      if(UzGrkDXVDi == true){UzGrkDXVDi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XQGTYCTUVC
{ 
  void eQyTHoQPkh()
  { 
      bool iiOVljZslR = false;
      bool RtlImmoSEG = false;
      bool igSzCbzcci = false;
      bool MDRBIrMnjH = false;
      bool JiNcAmuNyC = false;
      bool qXpGTBPOTK = false;
      bool kxQDFOckAu = false;
      bool aBixwATpzO = false;
      bool fleaqoMLgG = false;
      bool byTYWMSKWl = false;
      bool KKNCbpnsJT = false;
      bool hZOFdyRoLP = false;
      bool BQDsSbgJZi = false;
      bool gJSMDVYbzB = false;
      bool ATBMYCiOuX = false;
      bool ucyHksGTjz = false;
      bool IeSZlYGCBI = false;
      bool ZopKPgOpUP = false;
      bool rSOCnEKLbJ = false;
      bool OErzsVBbaz = false;
      string gkCEYDQhka;
      string VJObucFVBW;
      string qHyBSShscl;
      string fxgOpmcREB;
      string XLiudfFxPn;
      string KgItwZmBkF;
      string UXFzuYbzkH;
      string AnQzzfYCWl;
      string NkdobynmSQ;
      string AbfzfAGjAF;
      string EFLHnWQIuP;
      string BjezrisQXx;
      string jogUHYHQSy;
      string ZoCQgHYWBE;
      string gfqCPPwfGw;
      string GoLCVPYqAP;
      string OzowpLgNRk;
      string KWOSPDxdEq;
      string baKVrjcAtR;
      string hhWlogptMD;
      if(gkCEYDQhka == EFLHnWQIuP){iiOVljZslR = true;}
      else if(EFLHnWQIuP == gkCEYDQhka){KKNCbpnsJT = true;}
      if(VJObucFVBW == BjezrisQXx){RtlImmoSEG = true;}
      else if(BjezrisQXx == VJObucFVBW){hZOFdyRoLP = true;}
      if(qHyBSShscl == jogUHYHQSy){igSzCbzcci = true;}
      else if(jogUHYHQSy == qHyBSShscl){BQDsSbgJZi = true;}
      if(fxgOpmcREB == ZoCQgHYWBE){MDRBIrMnjH = true;}
      else if(ZoCQgHYWBE == fxgOpmcREB){gJSMDVYbzB = true;}
      if(XLiudfFxPn == gfqCPPwfGw){JiNcAmuNyC = true;}
      else if(gfqCPPwfGw == XLiudfFxPn){ATBMYCiOuX = true;}
      if(KgItwZmBkF == GoLCVPYqAP){qXpGTBPOTK = true;}
      else if(GoLCVPYqAP == KgItwZmBkF){ucyHksGTjz = true;}
      if(UXFzuYbzkH == OzowpLgNRk){kxQDFOckAu = true;}
      else if(OzowpLgNRk == UXFzuYbzkH){IeSZlYGCBI = true;}
      if(AnQzzfYCWl == KWOSPDxdEq){aBixwATpzO = true;}
      if(NkdobynmSQ == baKVrjcAtR){fleaqoMLgG = true;}
      if(AbfzfAGjAF == hhWlogptMD){byTYWMSKWl = true;}
      while(KWOSPDxdEq == AnQzzfYCWl){ZopKPgOpUP = true;}
      while(baKVrjcAtR == baKVrjcAtR){rSOCnEKLbJ = true;}
      while(hhWlogptMD == hhWlogptMD){OErzsVBbaz = true;}
      if(iiOVljZslR == true){iiOVljZslR = false;}
      if(RtlImmoSEG == true){RtlImmoSEG = false;}
      if(igSzCbzcci == true){igSzCbzcci = false;}
      if(MDRBIrMnjH == true){MDRBIrMnjH = false;}
      if(JiNcAmuNyC == true){JiNcAmuNyC = false;}
      if(qXpGTBPOTK == true){qXpGTBPOTK = false;}
      if(kxQDFOckAu == true){kxQDFOckAu = false;}
      if(aBixwATpzO == true){aBixwATpzO = false;}
      if(fleaqoMLgG == true){fleaqoMLgG = false;}
      if(byTYWMSKWl == true){byTYWMSKWl = false;}
      if(KKNCbpnsJT == true){KKNCbpnsJT = false;}
      if(hZOFdyRoLP == true){hZOFdyRoLP = false;}
      if(BQDsSbgJZi == true){BQDsSbgJZi = false;}
      if(gJSMDVYbzB == true){gJSMDVYbzB = false;}
      if(ATBMYCiOuX == true){ATBMYCiOuX = false;}
      if(ucyHksGTjz == true){ucyHksGTjz = false;}
      if(IeSZlYGCBI == true){IeSZlYGCBI = false;}
      if(ZopKPgOpUP == true){ZopKPgOpUP = false;}
      if(rSOCnEKLbJ == true){rSOCnEKLbJ = false;}
      if(OErzsVBbaz == true){OErzsVBbaz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGNKRXNTDB
{ 
  void eWsnrIHwlJ()
  { 
      bool HIjmUjgnAz = false;
      bool DmCQRfaiHU = false;
      bool GmygXPkwVu = false;
      bool glokRVObsA = false;
      bool NSnEbFSSLE = false;
      bool RUxbXTKCPE = false;
      bool zjSFRRyQzu = false;
      bool QypHHmzsFR = false;
      bool xRjQcLnMNx = false;
      bool KLMnBcAhlK = false;
      bool HBTQnSeoTj = false;
      bool URxxHgABcG = false;
      bool ckDBkFlBGe = false;
      bool lRGuJuxTcJ = false;
      bool gzsccsOOfT = false;
      bool byFfgWxSfh = false;
      bool gcinxCKCnM = false;
      bool jgYSYdqaYq = false;
      bool pXUmCnLZNl = false;
      bool xentcEPEeZ = false;
      string cIzISYsyFV;
      string yRYCjyQXJI;
      string VsNtKqrYnu;
      string HnzxokGiPK;
      string TPaYhBzizc;
      string GPSUVitExb;
      string fUJKNJRaMz;
      string rgHznFSnMJ;
      string qIZKnqVdbG;
      string pCkndzFQKX;
      string iYWzkZITgP;
      string PFqnjXuzVW;
      string mnyFJouSUo;
      string ACcoaSlZYO;
      string hCxMqjKxEG;
      string EGunjtZQpw;
      string doyrONbCNQ;
      string kUZGnkqlOY;
      string dyOOjtHoEf;
      string sUjckrEFxd;
      if(cIzISYsyFV == iYWzkZITgP){HIjmUjgnAz = true;}
      else if(iYWzkZITgP == cIzISYsyFV){HBTQnSeoTj = true;}
      if(yRYCjyQXJI == PFqnjXuzVW){DmCQRfaiHU = true;}
      else if(PFqnjXuzVW == yRYCjyQXJI){URxxHgABcG = true;}
      if(VsNtKqrYnu == mnyFJouSUo){GmygXPkwVu = true;}
      else if(mnyFJouSUo == VsNtKqrYnu){ckDBkFlBGe = true;}
      if(HnzxokGiPK == ACcoaSlZYO){glokRVObsA = true;}
      else if(ACcoaSlZYO == HnzxokGiPK){lRGuJuxTcJ = true;}
      if(TPaYhBzizc == hCxMqjKxEG){NSnEbFSSLE = true;}
      else if(hCxMqjKxEG == TPaYhBzizc){gzsccsOOfT = true;}
      if(GPSUVitExb == EGunjtZQpw){RUxbXTKCPE = true;}
      else if(EGunjtZQpw == GPSUVitExb){byFfgWxSfh = true;}
      if(fUJKNJRaMz == doyrONbCNQ){zjSFRRyQzu = true;}
      else if(doyrONbCNQ == fUJKNJRaMz){gcinxCKCnM = true;}
      if(rgHznFSnMJ == kUZGnkqlOY){QypHHmzsFR = true;}
      if(qIZKnqVdbG == dyOOjtHoEf){xRjQcLnMNx = true;}
      if(pCkndzFQKX == sUjckrEFxd){KLMnBcAhlK = true;}
      while(kUZGnkqlOY == rgHznFSnMJ){jgYSYdqaYq = true;}
      while(dyOOjtHoEf == dyOOjtHoEf){pXUmCnLZNl = true;}
      while(sUjckrEFxd == sUjckrEFxd){xentcEPEeZ = true;}
      if(HIjmUjgnAz == true){HIjmUjgnAz = false;}
      if(DmCQRfaiHU == true){DmCQRfaiHU = false;}
      if(GmygXPkwVu == true){GmygXPkwVu = false;}
      if(glokRVObsA == true){glokRVObsA = false;}
      if(NSnEbFSSLE == true){NSnEbFSSLE = false;}
      if(RUxbXTKCPE == true){RUxbXTKCPE = false;}
      if(zjSFRRyQzu == true){zjSFRRyQzu = false;}
      if(QypHHmzsFR == true){QypHHmzsFR = false;}
      if(xRjQcLnMNx == true){xRjQcLnMNx = false;}
      if(KLMnBcAhlK == true){KLMnBcAhlK = false;}
      if(HBTQnSeoTj == true){HBTQnSeoTj = false;}
      if(URxxHgABcG == true){URxxHgABcG = false;}
      if(ckDBkFlBGe == true){ckDBkFlBGe = false;}
      if(lRGuJuxTcJ == true){lRGuJuxTcJ = false;}
      if(gzsccsOOfT == true){gzsccsOOfT = false;}
      if(byFfgWxSfh == true){byFfgWxSfh = false;}
      if(gcinxCKCnM == true){gcinxCKCnM = false;}
      if(jgYSYdqaYq == true){jgYSYdqaYq = false;}
      if(pXUmCnLZNl == true){pXUmCnLZNl = false;}
      if(xentcEPEeZ == true){xentcEPEeZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IPVOTBHUAA
{ 
  void YozWarIRFF()
  { 
      bool RSbePfxqUY = false;
      bool lpUDDkDQrI = false;
      bool qgdigCabBb = false;
      bool jRhJZcbpTX = false;
      bool mJsrJprGhV = false;
      bool EfEoHjnsxN = false;
      bool FVpsoTIKcZ = false;
      bool JMwTUgnlYq = false;
      bool KUteWDMrBp = false;
      bool oisGSRSADo = false;
      bool hgdHMqjkUZ = false;
      bool wCTGDkaLVk = false;
      bool HQJlkZToAC = false;
      bool OmhjJcplRf = false;
      bool SaXatlOmDh = false;
      bool qHdShRXqVl = false;
      bool XtjRLIUjwZ = false;
      bool tospRfshrz = false;
      bool LflSLGIPCr = false;
      bool FzPfHXpFPk = false;
      string WCVOJAgtBP;
      string cbgUPIIpId;
      string FVxqhxcmAu;
      string dgHakhNOUH;
      string BBNHgcALhF;
      string uJRusBEdfM;
      string WtsGluTFih;
      string tsVAcDIoJF;
      string wREuzUPMgj;
      string cihHkGIGVl;
      string ItbAKBmQSo;
      string sPUaPFoxGQ;
      string fHXzFLLNPV;
      string uBTXwCoEjx;
      string gysrqNOGrf;
      string RKAEGAVctz;
      string pYBwsrwweN;
      string PkMIjgOfIq;
      string wEVjEkAORu;
      string fMJkHHxwyy;
      if(WCVOJAgtBP == ItbAKBmQSo){RSbePfxqUY = true;}
      else if(ItbAKBmQSo == WCVOJAgtBP){hgdHMqjkUZ = true;}
      if(cbgUPIIpId == sPUaPFoxGQ){lpUDDkDQrI = true;}
      else if(sPUaPFoxGQ == cbgUPIIpId){wCTGDkaLVk = true;}
      if(FVxqhxcmAu == fHXzFLLNPV){qgdigCabBb = true;}
      else if(fHXzFLLNPV == FVxqhxcmAu){HQJlkZToAC = true;}
      if(dgHakhNOUH == uBTXwCoEjx){jRhJZcbpTX = true;}
      else if(uBTXwCoEjx == dgHakhNOUH){OmhjJcplRf = true;}
      if(BBNHgcALhF == gysrqNOGrf){mJsrJprGhV = true;}
      else if(gysrqNOGrf == BBNHgcALhF){SaXatlOmDh = true;}
      if(uJRusBEdfM == RKAEGAVctz){EfEoHjnsxN = true;}
      else if(RKAEGAVctz == uJRusBEdfM){qHdShRXqVl = true;}
      if(WtsGluTFih == pYBwsrwweN){FVpsoTIKcZ = true;}
      else if(pYBwsrwweN == WtsGluTFih){XtjRLIUjwZ = true;}
      if(tsVAcDIoJF == PkMIjgOfIq){JMwTUgnlYq = true;}
      if(wREuzUPMgj == wEVjEkAORu){KUteWDMrBp = true;}
      if(cihHkGIGVl == fMJkHHxwyy){oisGSRSADo = true;}
      while(PkMIjgOfIq == tsVAcDIoJF){tospRfshrz = true;}
      while(wEVjEkAORu == wEVjEkAORu){LflSLGIPCr = true;}
      while(fMJkHHxwyy == fMJkHHxwyy){FzPfHXpFPk = true;}
      if(RSbePfxqUY == true){RSbePfxqUY = false;}
      if(lpUDDkDQrI == true){lpUDDkDQrI = false;}
      if(qgdigCabBb == true){qgdigCabBb = false;}
      if(jRhJZcbpTX == true){jRhJZcbpTX = false;}
      if(mJsrJprGhV == true){mJsrJprGhV = false;}
      if(EfEoHjnsxN == true){EfEoHjnsxN = false;}
      if(FVpsoTIKcZ == true){FVpsoTIKcZ = false;}
      if(JMwTUgnlYq == true){JMwTUgnlYq = false;}
      if(KUteWDMrBp == true){KUteWDMrBp = false;}
      if(oisGSRSADo == true){oisGSRSADo = false;}
      if(hgdHMqjkUZ == true){hgdHMqjkUZ = false;}
      if(wCTGDkaLVk == true){wCTGDkaLVk = false;}
      if(HQJlkZToAC == true){HQJlkZToAC = false;}
      if(OmhjJcplRf == true){OmhjJcplRf = false;}
      if(SaXatlOmDh == true){SaXatlOmDh = false;}
      if(qHdShRXqVl == true){qHdShRXqVl = false;}
      if(XtjRLIUjwZ == true){XtjRLIUjwZ = false;}
      if(tospRfshrz == true){tospRfshrz = false;}
      if(LflSLGIPCr == true){LflSLGIPCr = false;}
      if(FzPfHXpFPk == true){FzPfHXpFPk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AOMSDALBLU
{ 
  void oNpScGJiAo()
  { 
      bool VrQRkCcYWt = false;
      bool XcfdltIbVo = false;
      bool zQRPOLIapQ = false;
      bool jbDwyUOfpL = false;
      bool wNrnSdAfik = false;
      bool YgiEoEaBDY = false;
      bool tBiGJuZjfR = false;
      bool fckKrlYdwk = false;
      bool LbqEqCsyHs = false;
      bool tNcQQtekdX = false;
      bool EPAREwuYLC = false;
      bool ewESNSJdOH = false;
      bool BaclXSAUsy = false;
      bool HmAYgwaZAu = false;
      bool HUmENxIKDx = false;
      bool jBWWVcmOsl = false;
      bool waeNurwfkR = false;
      bool qjcTAgnYXa = false;
      bool JpQuNFQdDD = false;
      bool IMfNzfpYIV = false;
      string DVTmbSlwqR;
      string deERNSRaIa;
      string ihPhSPDjAi;
      string zDDcOYzrAi;
      string woeYTzFeIY;
      string BShxHVGkUL;
      string OBuISZaaDn;
      string TZZZdsCpOT;
      string KYbbgfUGVr;
      string SOXoTutVGs;
      string YdaTFbrISN;
      string SPVBBpZTal;
      string FTEKVFBkFi;
      string zgjVufxHVF;
      string nLnHZCrWmd;
      string UZtUmEZQxz;
      string ZGDiOlfzGU;
      string rRxVxsfwjT;
      string MeybNYlOhp;
      string GfJVfgIEsn;
      if(DVTmbSlwqR == YdaTFbrISN){VrQRkCcYWt = true;}
      else if(YdaTFbrISN == DVTmbSlwqR){EPAREwuYLC = true;}
      if(deERNSRaIa == SPVBBpZTal){XcfdltIbVo = true;}
      else if(SPVBBpZTal == deERNSRaIa){ewESNSJdOH = true;}
      if(ihPhSPDjAi == FTEKVFBkFi){zQRPOLIapQ = true;}
      else if(FTEKVFBkFi == ihPhSPDjAi){BaclXSAUsy = true;}
      if(zDDcOYzrAi == zgjVufxHVF){jbDwyUOfpL = true;}
      else if(zgjVufxHVF == zDDcOYzrAi){HmAYgwaZAu = true;}
      if(woeYTzFeIY == nLnHZCrWmd){wNrnSdAfik = true;}
      else if(nLnHZCrWmd == woeYTzFeIY){HUmENxIKDx = true;}
      if(BShxHVGkUL == UZtUmEZQxz){YgiEoEaBDY = true;}
      else if(UZtUmEZQxz == BShxHVGkUL){jBWWVcmOsl = true;}
      if(OBuISZaaDn == ZGDiOlfzGU){tBiGJuZjfR = true;}
      else if(ZGDiOlfzGU == OBuISZaaDn){waeNurwfkR = true;}
      if(TZZZdsCpOT == rRxVxsfwjT){fckKrlYdwk = true;}
      if(KYbbgfUGVr == MeybNYlOhp){LbqEqCsyHs = true;}
      if(SOXoTutVGs == GfJVfgIEsn){tNcQQtekdX = true;}
      while(rRxVxsfwjT == TZZZdsCpOT){qjcTAgnYXa = true;}
      while(MeybNYlOhp == MeybNYlOhp){JpQuNFQdDD = true;}
      while(GfJVfgIEsn == GfJVfgIEsn){IMfNzfpYIV = true;}
      if(VrQRkCcYWt == true){VrQRkCcYWt = false;}
      if(XcfdltIbVo == true){XcfdltIbVo = false;}
      if(zQRPOLIapQ == true){zQRPOLIapQ = false;}
      if(jbDwyUOfpL == true){jbDwyUOfpL = false;}
      if(wNrnSdAfik == true){wNrnSdAfik = false;}
      if(YgiEoEaBDY == true){YgiEoEaBDY = false;}
      if(tBiGJuZjfR == true){tBiGJuZjfR = false;}
      if(fckKrlYdwk == true){fckKrlYdwk = false;}
      if(LbqEqCsyHs == true){LbqEqCsyHs = false;}
      if(tNcQQtekdX == true){tNcQQtekdX = false;}
      if(EPAREwuYLC == true){EPAREwuYLC = false;}
      if(ewESNSJdOH == true){ewESNSJdOH = false;}
      if(BaclXSAUsy == true){BaclXSAUsy = false;}
      if(HmAYgwaZAu == true){HmAYgwaZAu = false;}
      if(HUmENxIKDx == true){HUmENxIKDx = false;}
      if(jBWWVcmOsl == true){jBWWVcmOsl = false;}
      if(waeNurwfkR == true){waeNurwfkR = false;}
      if(qjcTAgnYXa == true){qjcTAgnYXa = false;}
      if(JpQuNFQdDD == true){JpQuNFQdDD = false;}
      if(IMfNzfpYIV == true){IMfNzfpYIV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ODPZCQHCWP
{ 
  void EyIppPIwoQ()
  { 
      bool hWeKEInUOk = false;
      bool qHFkApngRQ = false;
      bool feRcsOAzEe = false;
      bool wubuAeintV = false;
      bool OxrgZrthwO = false;
      bool SYjHwCECQo = false;
      bool InPjoueKjU = false;
      bool GAlwCimjCA = false;
      bool TSDpLWKTzy = false;
      bool ZgWFNZgHqd = false;
      bool MjxaHRlnFN = false;
      bool PUzPUokZYR = false;
      bool jLLluZdghb = false;
      bool BfrYnjUchs = false;
      bool jWOkhFhGjX = false;
      bool oGiZsBXLfh = false;
      bool nFFcLjbZbk = false;
      bool TIregNwZDp = false;
      bool rXwJmuwSem = false;
      bool LJwzFeQkZy = false;
      string WcsKzmXccq;
      string etOiUUQLhq;
      string EbpYXtsEXD;
      string aJuYQBQIHE;
      string BkbztioqrO;
      string ArasaulTmF;
      string tSEZQVypRT;
      string EIDcoTAqeo;
      string FCLJDiiCyU;
      string PwVCKifCiY;
      string jyYYKrnxDG;
      string utoxzrGuVg;
      string lwqwEIlBRG;
      string mxIFEGcmyL;
      string tkyqZUGXDS;
      string bkfBmnHcUC;
      string FmfwSxljsr;
      string OSwKlBxzWi;
      string BOyyeCRGSQ;
      string zASwFHFCXb;
      if(WcsKzmXccq == jyYYKrnxDG){hWeKEInUOk = true;}
      else if(jyYYKrnxDG == WcsKzmXccq){MjxaHRlnFN = true;}
      if(etOiUUQLhq == utoxzrGuVg){qHFkApngRQ = true;}
      else if(utoxzrGuVg == etOiUUQLhq){PUzPUokZYR = true;}
      if(EbpYXtsEXD == lwqwEIlBRG){feRcsOAzEe = true;}
      else if(lwqwEIlBRG == EbpYXtsEXD){jLLluZdghb = true;}
      if(aJuYQBQIHE == mxIFEGcmyL){wubuAeintV = true;}
      else if(mxIFEGcmyL == aJuYQBQIHE){BfrYnjUchs = true;}
      if(BkbztioqrO == tkyqZUGXDS){OxrgZrthwO = true;}
      else if(tkyqZUGXDS == BkbztioqrO){jWOkhFhGjX = true;}
      if(ArasaulTmF == bkfBmnHcUC){SYjHwCECQo = true;}
      else if(bkfBmnHcUC == ArasaulTmF){oGiZsBXLfh = true;}
      if(tSEZQVypRT == FmfwSxljsr){InPjoueKjU = true;}
      else if(FmfwSxljsr == tSEZQVypRT){nFFcLjbZbk = true;}
      if(EIDcoTAqeo == OSwKlBxzWi){GAlwCimjCA = true;}
      if(FCLJDiiCyU == BOyyeCRGSQ){TSDpLWKTzy = true;}
      if(PwVCKifCiY == zASwFHFCXb){ZgWFNZgHqd = true;}
      while(OSwKlBxzWi == EIDcoTAqeo){TIregNwZDp = true;}
      while(BOyyeCRGSQ == BOyyeCRGSQ){rXwJmuwSem = true;}
      while(zASwFHFCXb == zASwFHFCXb){LJwzFeQkZy = true;}
      if(hWeKEInUOk == true){hWeKEInUOk = false;}
      if(qHFkApngRQ == true){qHFkApngRQ = false;}
      if(feRcsOAzEe == true){feRcsOAzEe = false;}
      if(wubuAeintV == true){wubuAeintV = false;}
      if(OxrgZrthwO == true){OxrgZrthwO = false;}
      if(SYjHwCECQo == true){SYjHwCECQo = false;}
      if(InPjoueKjU == true){InPjoueKjU = false;}
      if(GAlwCimjCA == true){GAlwCimjCA = false;}
      if(TSDpLWKTzy == true){TSDpLWKTzy = false;}
      if(ZgWFNZgHqd == true){ZgWFNZgHqd = false;}
      if(MjxaHRlnFN == true){MjxaHRlnFN = false;}
      if(PUzPUokZYR == true){PUzPUokZYR = false;}
      if(jLLluZdghb == true){jLLluZdghb = false;}
      if(BfrYnjUchs == true){BfrYnjUchs = false;}
      if(jWOkhFhGjX == true){jWOkhFhGjX = false;}
      if(oGiZsBXLfh == true){oGiZsBXLfh = false;}
      if(nFFcLjbZbk == true){nFFcLjbZbk = false;}
      if(TIregNwZDp == true){TIregNwZDp = false;}
      if(rXwJmuwSem == true){rXwJmuwSem = false;}
      if(LJwzFeQkZy == true){LJwzFeQkZy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDPRFPVXBZ
{ 
  void KOTjFIUthO()
  { 
      bool jfsXYhmshE = false;
      bool OOdibwFiki = false;
      bool xMwbDixiRW = false;
      bool PiEyXqmkTV = false;
      bool NaCsxQlOBD = false;
      bool CWfpyXjRUo = false;
      bool kEbLneKfLj = false;
      bool IUOOVWJCdl = false;
      bool whgOTsCOzA = false;
      bool GVQdkJyqES = false;
      bool GFDQthHRUb = false;
      bool NgmhsCWNqt = false;
      bool bugKclDkcL = false;
      bool YRyLfqePTl = false;
      bool lktXlZhhki = false;
      bool lkAKpLXrmI = false;
      bool dVnICwibCB = false;
      bool XGtEIqAJXD = false;
      bool DVAtZnRnUT = false;
      bool SlcKIQwlUp = false;
      string YwWYdpkcli;
      string VhqHDDbPHW;
      string mwnDIPaZOZ;
      string YuxMmkMOfc;
      string ZBPZDJJCBo;
      string FSWSUcISPO;
      string OKNMJakdTS;
      string qMjewlgNAz;
      string FYYZTGYdqK;
      string csyRNOmCPb;
      string XfihxrhrWi;
      string wuSQJolnrD;
      string CHlJpyORQg;
      string zdxXbYppbb;
      string XfGIOgahIX;
      string cyJMZPsYrz;
      string cPaoiRxtnj;
      string zuLQeVAdtI;
      string XgJrEATkyM;
      string fQyczIFRYw;
      if(YwWYdpkcli == XfihxrhrWi){jfsXYhmshE = true;}
      else if(XfihxrhrWi == YwWYdpkcli){GFDQthHRUb = true;}
      if(VhqHDDbPHW == wuSQJolnrD){OOdibwFiki = true;}
      else if(wuSQJolnrD == VhqHDDbPHW){NgmhsCWNqt = true;}
      if(mwnDIPaZOZ == CHlJpyORQg){xMwbDixiRW = true;}
      else if(CHlJpyORQg == mwnDIPaZOZ){bugKclDkcL = true;}
      if(YuxMmkMOfc == zdxXbYppbb){PiEyXqmkTV = true;}
      else if(zdxXbYppbb == YuxMmkMOfc){YRyLfqePTl = true;}
      if(ZBPZDJJCBo == XfGIOgahIX){NaCsxQlOBD = true;}
      else if(XfGIOgahIX == ZBPZDJJCBo){lktXlZhhki = true;}
      if(FSWSUcISPO == cyJMZPsYrz){CWfpyXjRUo = true;}
      else if(cyJMZPsYrz == FSWSUcISPO){lkAKpLXrmI = true;}
      if(OKNMJakdTS == cPaoiRxtnj){kEbLneKfLj = true;}
      else if(cPaoiRxtnj == OKNMJakdTS){dVnICwibCB = true;}
      if(qMjewlgNAz == zuLQeVAdtI){IUOOVWJCdl = true;}
      if(FYYZTGYdqK == XgJrEATkyM){whgOTsCOzA = true;}
      if(csyRNOmCPb == fQyczIFRYw){GVQdkJyqES = true;}
      while(zuLQeVAdtI == qMjewlgNAz){XGtEIqAJXD = true;}
      while(XgJrEATkyM == XgJrEATkyM){DVAtZnRnUT = true;}
      while(fQyczIFRYw == fQyczIFRYw){SlcKIQwlUp = true;}
      if(jfsXYhmshE == true){jfsXYhmshE = false;}
      if(OOdibwFiki == true){OOdibwFiki = false;}
      if(xMwbDixiRW == true){xMwbDixiRW = false;}
      if(PiEyXqmkTV == true){PiEyXqmkTV = false;}
      if(NaCsxQlOBD == true){NaCsxQlOBD = false;}
      if(CWfpyXjRUo == true){CWfpyXjRUo = false;}
      if(kEbLneKfLj == true){kEbLneKfLj = false;}
      if(IUOOVWJCdl == true){IUOOVWJCdl = false;}
      if(whgOTsCOzA == true){whgOTsCOzA = false;}
      if(GVQdkJyqES == true){GVQdkJyqES = false;}
      if(GFDQthHRUb == true){GFDQthHRUb = false;}
      if(NgmhsCWNqt == true){NgmhsCWNqt = false;}
      if(bugKclDkcL == true){bugKclDkcL = false;}
      if(YRyLfqePTl == true){YRyLfqePTl = false;}
      if(lktXlZhhki == true){lktXlZhhki = false;}
      if(lkAKpLXrmI == true){lkAKpLXrmI = false;}
      if(dVnICwibCB == true){dVnICwibCB = false;}
      if(XGtEIqAJXD == true){XGtEIqAJXD = false;}
      if(DVAtZnRnUT == true){DVAtZnRnUT = false;}
      if(SlcKIQwlUp == true){SlcKIQwlUp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZSGPMXVVDK
{ 
  void dMyrgAOKLZ()
  { 
      bool mKubfUCPwe = false;
      bool LOxsJLlWDP = false;
      bool jsMFYEPbyU = false;
      bool SNUlDaSkLS = false;
      bool SOmITHUdCd = false;
      bool thuansyoDa = false;
      bool EaQbMxtLoh = false;
      bool sBLjwVFElQ = false;
      bool jlZUZkStxJ = false;
      bool cdgjNqyLuV = false;
      bool NInTkrWKeS = false;
      bool nsDlpSBuBb = false;
      bool ezNfFOTaWE = false;
      bool XtIPDaxFjh = false;
      bool NIPeViZust = false;
      bool pCJTqNuINV = false;
      bool YumZutjniP = false;
      bool UuLTNVjiJV = false;
      bool oYgbOUjoXo = false;
      bool foqNIRUpja = false;
      string jLmDxqIkNF;
      string LlhJafFaTl;
      string ZtpIipQRrW;
      string FlITaufoXY;
      string pcBdVEcmVr;
      string knFgtpVdTG;
      string ZpsqzYcNhf;
      string zPCtuwsLme;
      string NdwzkRfaZk;
      string ZCVQzAjJew;
      string aPEprUkKkx;
      string xJqoswssFg;
      string sCnxGxtkut;
      string MigpEyYGGQ;
      string fUobmPLfXD;
      string HpExDYaHju;
      string ZAPpkOcAku;
      string WlmoAXMLKp;
      string lONrmVdjme;
      string WRWLpfFypY;
      if(jLmDxqIkNF == aPEprUkKkx){mKubfUCPwe = true;}
      else if(aPEprUkKkx == jLmDxqIkNF){NInTkrWKeS = true;}
      if(LlhJafFaTl == xJqoswssFg){LOxsJLlWDP = true;}
      else if(xJqoswssFg == LlhJafFaTl){nsDlpSBuBb = true;}
      if(ZtpIipQRrW == sCnxGxtkut){jsMFYEPbyU = true;}
      else if(sCnxGxtkut == ZtpIipQRrW){ezNfFOTaWE = true;}
      if(FlITaufoXY == MigpEyYGGQ){SNUlDaSkLS = true;}
      else if(MigpEyYGGQ == FlITaufoXY){XtIPDaxFjh = true;}
      if(pcBdVEcmVr == fUobmPLfXD){SOmITHUdCd = true;}
      else if(fUobmPLfXD == pcBdVEcmVr){NIPeViZust = true;}
      if(knFgtpVdTG == HpExDYaHju){thuansyoDa = true;}
      else if(HpExDYaHju == knFgtpVdTG){pCJTqNuINV = true;}
      if(ZpsqzYcNhf == ZAPpkOcAku){EaQbMxtLoh = true;}
      else if(ZAPpkOcAku == ZpsqzYcNhf){YumZutjniP = true;}
      if(zPCtuwsLme == WlmoAXMLKp){sBLjwVFElQ = true;}
      if(NdwzkRfaZk == lONrmVdjme){jlZUZkStxJ = true;}
      if(ZCVQzAjJew == WRWLpfFypY){cdgjNqyLuV = true;}
      while(WlmoAXMLKp == zPCtuwsLme){UuLTNVjiJV = true;}
      while(lONrmVdjme == lONrmVdjme){oYgbOUjoXo = true;}
      while(WRWLpfFypY == WRWLpfFypY){foqNIRUpja = true;}
      if(mKubfUCPwe == true){mKubfUCPwe = false;}
      if(LOxsJLlWDP == true){LOxsJLlWDP = false;}
      if(jsMFYEPbyU == true){jsMFYEPbyU = false;}
      if(SNUlDaSkLS == true){SNUlDaSkLS = false;}
      if(SOmITHUdCd == true){SOmITHUdCd = false;}
      if(thuansyoDa == true){thuansyoDa = false;}
      if(EaQbMxtLoh == true){EaQbMxtLoh = false;}
      if(sBLjwVFElQ == true){sBLjwVFElQ = false;}
      if(jlZUZkStxJ == true){jlZUZkStxJ = false;}
      if(cdgjNqyLuV == true){cdgjNqyLuV = false;}
      if(NInTkrWKeS == true){NInTkrWKeS = false;}
      if(nsDlpSBuBb == true){nsDlpSBuBb = false;}
      if(ezNfFOTaWE == true){ezNfFOTaWE = false;}
      if(XtIPDaxFjh == true){XtIPDaxFjh = false;}
      if(NIPeViZust == true){NIPeViZust = false;}
      if(pCJTqNuINV == true){pCJTqNuINV = false;}
      if(YumZutjniP == true){YumZutjniP = false;}
      if(UuLTNVjiJV == true){UuLTNVjiJV = false;}
      if(oYgbOUjoXo == true){oYgbOUjoXo = false;}
      if(foqNIRUpja == true){foqNIRUpja = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BXHNWVAMGO
{ 
  void rbfEWdSNBw()
  { 
      bool ZoxKxWFgKl = false;
      bool PgWibtsgik = false;
      bool ImIFqqFynn = false;
      bool OzpocQorYh = false;
      bool pRJdnwiqjO = false;
      bool kmQZRmgqTG = false;
      bool QGsVWPphGK = false;
      bool EBIAupceRt = false;
      bool HOOZDbiQWo = false;
      bool jyYSRjYnGX = false;
      bool FBjYJieQda = false;
      bool KCYYyBqSRu = false;
      bool gZKRaFcoiK = false;
      bool RnXtnGdoPT = false;
      bool xSlwdgZzTP = false;
      bool sFVLqfpSyD = false;
      bool GogTIVeekr = false;
      bool XBDxxOnOms = false;
      bool fcVSRLRMCI = false;
      bool PLqLMIkSmI = false;
      string xcTuNwJzUg;
      string YHpPppFXLa;
      string GRztxtcguQ;
      string eWiKzRweeG;
      string XZVaebGzwx;
      string AYbyZfdYxT;
      string TcEDBCXePY;
      string sasFCguXOV;
      string mcjyQGtjkS;
      string mXhLmuVRYc;
      string DbiXDZeWur;
      string kFJbfqrFmu;
      string HnsxkUrhSH;
      string LcykSLsMtp;
      string bXnrhhNGeu;
      string CPddVOhlli;
      string gwDngHHXIU;
      string yfKxTizBPD;
      string GlCWFuyUPD;
      string cGZLIeTALZ;
      if(xcTuNwJzUg == DbiXDZeWur){ZoxKxWFgKl = true;}
      else if(DbiXDZeWur == xcTuNwJzUg){FBjYJieQda = true;}
      if(YHpPppFXLa == kFJbfqrFmu){PgWibtsgik = true;}
      else if(kFJbfqrFmu == YHpPppFXLa){KCYYyBqSRu = true;}
      if(GRztxtcguQ == HnsxkUrhSH){ImIFqqFynn = true;}
      else if(HnsxkUrhSH == GRztxtcguQ){gZKRaFcoiK = true;}
      if(eWiKzRweeG == LcykSLsMtp){OzpocQorYh = true;}
      else if(LcykSLsMtp == eWiKzRweeG){RnXtnGdoPT = true;}
      if(XZVaebGzwx == bXnrhhNGeu){pRJdnwiqjO = true;}
      else if(bXnrhhNGeu == XZVaebGzwx){xSlwdgZzTP = true;}
      if(AYbyZfdYxT == CPddVOhlli){kmQZRmgqTG = true;}
      else if(CPddVOhlli == AYbyZfdYxT){sFVLqfpSyD = true;}
      if(TcEDBCXePY == gwDngHHXIU){QGsVWPphGK = true;}
      else if(gwDngHHXIU == TcEDBCXePY){GogTIVeekr = true;}
      if(sasFCguXOV == yfKxTizBPD){EBIAupceRt = true;}
      if(mcjyQGtjkS == GlCWFuyUPD){HOOZDbiQWo = true;}
      if(mXhLmuVRYc == cGZLIeTALZ){jyYSRjYnGX = true;}
      while(yfKxTizBPD == sasFCguXOV){XBDxxOnOms = true;}
      while(GlCWFuyUPD == GlCWFuyUPD){fcVSRLRMCI = true;}
      while(cGZLIeTALZ == cGZLIeTALZ){PLqLMIkSmI = true;}
      if(ZoxKxWFgKl == true){ZoxKxWFgKl = false;}
      if(PgWibtsgik == true){PgWibtsgik = false;}
      if(ImIFqqFynn == true){ImIFqqFynn = false;}
      if(OzpocQorYh == true){OzpocQorYh = false;}
      if(pRJdnwiqjO == true){pRJdnwiqjO = false;}
      if(kmQZRmgqTG == true){kmQZRmgqTG = false;}
      if(QGsVWPphGK == true){QGsVWPphGK = false;}
      if(EBIAupceRt == true){EBIAupceRt = false;}
      if(HOOZDbiQWo == true){HOOZDbiQWo = false;}
      if(jyYSRjYnGX == true){jyYSRjYnGX = false;}
      if(FBjYJieQda == true){FBjYJieQda = false;}
      if(KCYYyBqSRu == true){KCYYyBqSRu = false;}
      if(gZKRaFcoiK == true){gZKRaFcoiK = false;}
      if(RnXtnGdoPT == true){RnXtnGdoPT = false;}
      if(xSlwdgZzTP == true){xSlwdgZzTP = false;}
      if(sFVLqfpSyD == true){sFVLqfpSyD = false;}
      if(GogTIVeekr == true){GogTIVeekr = false;}
      if(XBDxxOnOms == true){XBDxxOnOms = false;}
      if(fcVSRLRMCI == true){fcVSRLRMCI = false;}
      if(PLqLMIkSmI == true){PLqLMIkSmI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QOCAQEGVEV
{ 
  void zuMIpEeyKd()
  { 
      bool QXDoaXqtnA = false;
      bool IWsWGVIGgk = false;
      bool nyxnSbpfCV = false;
      bool qeIZVrCGFq = false;
      bool ZPKJTOnijY = false;
      bool UZSPwSZOVz = false;
      bool hLrSIdNSAO = false;
      bool SBApKXmnTE = false;
      bool mHwcBRMscD = false;
      bool RnkGJOWrAp = false;
      bool BUiVGSYcEY = false;
      bool fltRLaPPRq = false;
      bool QUowweQtfw = false;
      bool BumdDRXaVh = false;
      bool rjnEXetSti = false;
      bool yGaIYfflYa = false;
      bool CewIXjzPOs = false;
      bool CosizggkYQ = false;
      bool kxAxytUdEW = false;
      bool llBufMmfgm = false;
      string kgVKCxbgwl;
      string qcEiwXrPGh;
      string wTmgxORoOD;
      string dZYBCtIPGK;
      string SREdhSyfNh;
      string eCAwOQtnMn;
      string fmRrIRDCgB;
      string OcIuPeOIze;
      string PkagYaYcml;
      string zTCSefzMVQ;
      string OwzLSBtEfi;
      string BkohXtLkTg;
      string raOuCuZpQj;
      string fCmhQSkPOW;
      string gTwEjOeUtj;
      string TOrnYmgEJX;
      string bDmwCyxGRF;
      string IwWxzXeKLm;
      string QFugPRKzJc;
      string lgFqucgzBk;
      if(kgVKCxbgwl == OwzLSBtEfi){QXDoaXqtnA = true;}
      else if(OwzLSBtEfi == kgVKCxbgwl){BUiVGSYcEY = true;}
      if(qcEiwXrPGh == BkohXtLkTg){IWsWGVIGgk = true;}
      else if(BkohXtLkTg == qcEiwXrPGh){fltRLaPPRq = true;}
      if(wTmgxORoOD == raOuCuZpQj){nyxnSbpfCV = true;}
      else if(raOuCuZpQj == wTmgxORoOD){QUowweQtfw = true;}
      if(dZYBCtIPGK == fCmhQSkPOW){qeIZVrCGFq = true;}
      else if(fCmhQSkPOW == dZYBCtIPGK){BumdDRXaVh = true;}
      if(SREdhSyfNh == gTwEjOeUtj){ZPKJTOnijY = true;}
      else if(gTwEjOeUtj == SREdhSyfNh){rjnEXetSti = true;}
      if(eCAwOQtnMn == TOrnYmgEJX){UZSPwSZOVz = true;}
      else if(TOrnYmgEJX == eCAwOQtnMn){yGaIYfflYa = true;}
      if(fmRrIRDCgB == bDmwCyxGRF){hLrSIdNSAO = true;}
      else if(bDmwCyxGRF == fmRrIRDCgB){CewIXjzPOs = true;}
      if(OcIuPeOIze == IwWxzXeKLm){SBApKXmnTE = true;}
      if(PkagYaYcml == QFugPRKzJc){mHwcBRMscD = true;}
      if(zTCSefzMVQ == lgFqucgzBk){RnkGJOWrAp = true;}
      while(IwWxzXeKLm == OcIuPeOIze){CosizggkYQ = true;}
      while(QFugPRKzJc == QFugPRKzJc){kxAxytUdEW = true;}
      while(lgFqucgzBk == lgFqucgzBk){llBufMmfgm = true;}
      if(QXDoaXqtnA == true){QXDoaXqtnA = false;}
      if(IWsWGVIGgk == true){IWsWGVIGgk = false;}
      if(nyxnSbpfCV == true){nyxnSbpfCV = false;}
      if(qeIZVrCGFq == true){qeIZVrCGFq = false;}
      if(ZPKJTOnijY == true){ZPKJTOnijY = false;}
      if(UZSPwSZOVz == true){UZSPwSZOVz = false;}
      if(hLrSIdNSAO == true){hLrSIdNSAO = false;}
      if(SBApKXmnTE == true){SBApKXmnTE = false;}
      if(mHwcBRMscD == true){mHwcBRMscD = false;}
      if(RnkGJOWrAp == true){RnkGJOWrAp = false;}
      if(BUiVGSYcEY == true){BUiVGSYcEY = false;}
      if(fltRLaPPRq == true){fltRLaPPRq = false;}
      if(QUowweQtfw == true){QUowweQtfw = false;}
      if(BumdDRXaVh == true){BumdDRXaVh = false;}
      if(rjnEXetSti == true){rjnEXetSti = false;}
      if(yGaIYfflYa == true){yGaIYfflYa = false;}
      if(CewIXjzPOs == true){CewIXjzPOs = false;}
      if(CosizggkYQ == true){CosizggkYQ = false;}
      if(kxAxytUdEW == true){kxAxytUdEW = false;}
      if(llBufMmfgm == true){llBufMmfgm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TAQCDJTGJN
{ 
  void QKuJndiyUu()
  { 
      bool aDhGKFfJJh = false;
      bool KselayfwSI = false;
      bool xNkiQKabHU = false;
      bool ajVanHXXHz = false;
      bool ZfRunKiiYw = false;
      bool mGbFBNRypA = false;
      bool dEBoGaXEyT = false;
      bool ZHoShRupuG = false;
      bool arDLgTIPYZ = false;
      bool oYgGVVdcnM = false;
      bool mejEVfQIXi = false;
      bool SbDjYlApIl = false;
      bool SHeXdBZhxL = false;
      bool nRBiTwIyoA = false;
      bool CzroHNVxhj = false;
      bool UmUBtezLaU = false;
      bool GiLLuAZTQc = false;
      bool cCAHiTOoQQ = false;
      bool fcANqAxznn = false;
      bool wwWUtTmgtH = false;
      string OTtBYeKUpM;
      string SGjXoapwsT;
      string FIRqHrxpLM;
      string zjJOhgagKM;
      string parcqhPJnN;
      string kDzKHFCDtf;
      string hUIcNhwVpI;
      string zJkgdeQnzY;
      string cnByawkzGb;
      string dWledVROOJ;
      string ltTeNbRRgc;
      string oOEVDtSKCR;
      string xwONdcWGCI;
      string NBYpmiUVjz;
      string dSSdmPRQaj;
      string CGMxMoeFAk;
      string EKPXOmoOhU;
      string YwaCmddkaO;
      string KGeSFGobcy;
      string DOUztSDtOz;
      if(OTtBYeKUpM == ltTeNbRRgc){aDhGKFfJJh = true;}
      else if(ltTeNbRRgc == OTtBYeKUpM){mejEVfQIXi = true;}
      if(SGjXoapwsT == oOEVDtSKCR){KselayfwSI = true;}
      else if(oOEVDtSKCR == SGjXoapwsT){SbDjYlApIl = true;}
      if(FIRqHrxpLM == xwONdcWGCI){xNkiQKabHU = true;}
      else if(xwONdcWGCI == FIRqHrxpLM){SHeXdBZhxL = true;}
      if(zjJOhgagKM == NBYpmiUVjz){ajVanHXXHz = true;}
      else if(NBYpmiUVjz == zjJOhgagKM){nRBiTwIyoA = true;}
      if(parcqhPJnN == dSSdmPRQaj){ZfRunKiiYw = true;}
      else if(dSSdmPRQaj == parcqhPJnN){CzroHNVxhj = true;}
      if(kDzKHFCDtf == CGMxMoeFAk){mGbFBNRypA = true;}
      else if(CGMxMoeFAk == kDzKHFCDtf){UmUBtezLaU = true;}
      if(hUIcNhwVpI == EKPXOmoOhU){dEBoGaXEyT = true;}
      else if(EKPXOmoOhU == hUIcNhwVpI){GiLLuAZTQc = true;}
      if(zJkgdeQnzY == YwaCmddkaO){ZHoShRupuG = true;}
      if(cnByawkzGb == KGeSFGobcy){arDLgTIPYZ = true;}
      if(dWledVROOJ == DOUztSDtOz){oYgGVVdcnM = true;}
      while(YwaCmddkaO == zJkgdeQnzY){cCAHiTOoQQ = true;}
      while(KGeSFGobcy == KGeSFGobcy){fcANqAxznn = true;}
      while(DOUztSDtOz == DOUztSDtOz){wwWUtTmgtH = true;}
      if(aDhGKFfJJh == true){aDhGKFfJJh = false;}
      if(KselayfwSI == true){KselayfwSI = false;}
      if(xNkiQKabHU == true){xNkiQKabHU = false;}
      if(ajVanHXXHz == true){ajVanHXXHz = false;}
      if(ZfRunKiiYw == true){ZfRunKiiYw = false;}
      if(mGbFBNRypA == true){mGbFBNRypA = false;}
      if(dEBoGaXEyT == true){dEBoGaXEyT = false;}
      if(ZHoShRupuG == true){ZHoShRupuG = false;}
      if(arDLgTIPYZ == true){arDLgTIPYZ = false;}
      if(oYgGVVdcnM == true){oYgGVVdcnM = false;}
      if(mejEVfQIXi == true){mejEVfQIXi = false;}
      if(SbDjYlApIl == true){SbDjYlApIl = false;}
      if(SHeXdBZhxL == true){SHeXdBZhxL = false;}
      if(nRBiTwIyoA == true){nRBiTwIyoA = false;}
      if(CzroHNVxhj == true){CzroHNVxhj = false;}
      if(UmUBtezLaU == true){UmUBtezLaU = false;}
      if(GiLLuAZTQc == true){GiLLuAZTQc = false;}
      if(cCAHiTOoQQ == true){cCAHiTOoQQ = false;}
      if(fcANqAxznn == true){fcANqAxznn = false;}
      if(wwWUtTmgtH == true){wwWUtTmgtH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NEDMCXDMLU
{ 
  void yckSDGhlZr()
  { 
      bool lxyoQMPKSC = false;
      bool gAOpfRUCYx = false;
      bool YCeGwaBEft = false;
      bool JTAutfCyzE = false;
      bool OgTuZzmqNY = false;
      bool HSTihiSqsp = false;
      bool LKdYsMATuz = false;
      bool OWDUiriigw = false;
      bool nJqHlpAQNL = false;
      bool MLEIrDCuBN = false;
      bool zSuNKjPzAp = false;
      bool AjKxCBTWlD = false;
      bool MiGjlDStbe = false;
      bool omgSxUOcxB = false;
      bool aAQWKcAHGq = false;
      bool jfIyAPLKaG = false;
      bool RVXUAMCqzh = false;
      bool mpYjbLRiZI = false;
      bool CKmkuIeiSg = false;
      bool IDBpjFcwWy = false;
      string ByHcootkpU;
      string lSdapKeqxF;
      string rYESSCjURR;
      string qAkIomXmBu;
      string JilcmZuaiB;
      string ZWgzdbsnJl;
      string EZSXclhVkC;
      string mroBwImbfs;
      string HIkQqTTldM;
      string ticPpjPNzA;
      string qYofNhheCU;
      string oRIPdwnBfJ;
      string SwqYIEOYLM;
      string rYceBhSFDJ;
      string lniJWbZMkt;
      string uOgpgthQXJ;
      string SITpbQocNw;
      string ciyWWdNhBg;
      string dBmQQdqlyH;
      string AChspcUsgG;
      if(ByHcootkpU == qYofNhheCU){lxyoQMPKSC = true;}
      else if(qYofNhheCU == ByHcootkpU){zSuNKjPzAp = true;}
      if(lSdapKeqxF == oRIPdwnBfJ){gAOpfRUCYx = true;}
      else if(oRIPdwnBfJ == lSdapKeqxF){AjKxCBTWlD = true;}
      if(rYESSCjURR == SwqYIEOYLM){YCeGwaBEft = true;}
      else if(SwqYIEOYLM == rYESSCjURR){MiGjlDStbe = true;}
      if(qAkIomXmBu == rYceBhSFDJ){JTAutfCyzE = true;}
      else if(rYceBhSFDJ == qAkIomXmBu){omgSxUOcxB = true;}
      if(JilcmZuaiB == lniJWbZMkt){OgTuZzmqNY = true;}
      else if(lniJWbZMkt == JilcmZuaiB){aAQWKcAHGq = true;}
      if(ZWgzdbsnJl == uOgpgthQXJ){HSTihiSqsp = true;}
      else if(uOgpgthQXJ == ZWgzdbsnJl){jfIyAPLKaG = true;}
      if(EZSXclhVkC == SITpbQocNw){LKdYsMATuz = true;}
      else if(SITpbQocNw == EZSXclhVkC){RVXUAMCqzh = true;}
      if(mroBwImbfs == ciyWWdNhBg){OWDUiriigw = true;}
      if(HIkQqTTldM == dBmQQdqlyH){nJqHlpAQNL = true;}
      if(ticPpjPNzA == AChspcUsgG){MLEIrDCuBN = true;}
      while(ciyWWdNhBg == mroBwImbfs){mpYjbLRiZI = true;}
      while(dBmQQdqlyH == dBmQQdqlyH){CKmkuIeiSg = true;}
      while(AChspcUsgG == AChspcUsgG){IDBpjFcwWy = true;}
      if(lxyoQMPKSC == true){lxyoQMPKSC = false;}
      if(gAOpfRUCYx == true){gAOpfRUCYx = false;}
      if(YCeGwaBEft == true){YCeGwaBEft = false;}
      if(JTAutfCyzE == true){JTAutfCyzE = false;}
      if(OgTuZzmqNY == true){OgTuZzmqNY = false;}
      if(HSTihiSqsp == true){HSTihiSqsp = false;}
      if(LKdYsMATuz == true){LKdYsMATuz = false;}
      if(OWDUiriigw == true){OWDUiriigw = false;}
      if(nJqHlpAQNL == true){nJqHlpAQNL = false;}
      if(MLEIrDCuBN == true){MLEIrDCuBN = false;}
      if(zSuNKjPzAp == true){zSuNKjPzAp = false;}
      if(AjKxCBTWlD == true){AjKxCBTWlD = false;}
      if(MiGjlDStbe == true){MiGjlDStbe = false;}
      if(omgSxUOcxB == true){omgSxUOcxB = false;}
      if(aAQWKcAHGq == true){aAQWKcAHGq = false;}
      if(jfIyAPLKaG == true){jfIyAPLKaG = false;}
      if(RVXUAMCqzh == true){RVXUAMCqzh = false;}
      if(mpYjbLRiZI == true){mpYjbLRiZI = false;}
      if(CKmkuIeiSg == true){CKmkuIeiSg = false;}
      if(IDBpjFcwWy == true){IDBpjFcwWy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NUAGBKDJGY
{ 
  void yFzKbFGbOB()
  { 
      bool WBpxCltVKw = false;
      bool SJwjhbuZNK = false;
      bool nULRJjcOfg = false;
      bool MXysDOZwmt = false;
      bool UrJjpqHhEc = false;
      bool AyllRCoXnR = false;
      bool IfpcjuKDgS = false;
      bool CylSouKbaR = false;
      bool btJDgOlMaB = false;
      bool YBHUloCfAu = false;
      bool fEBkZBLSwW = false;
      bool qMwVpOVlwU = false;
      bool IybfsBpRgA = false;
      bool rdbflXsXce = false;
      bool CSPEJMEleX = false;
      bool SPjelgbVrY = false;
      bool KskwdNkQjR = false;
      bool VxIRRpiWVg = false;
      bool wEmJgbtxtE = false;
      bool uWfEUJgTaw = false;
      string qOEKGnLqPi;
      string oyDLPooheV;
      string AEFcfSxPNM;
      string rjegUTcUKU;
      string BKrtJartqU;
      string rODbalJaen;
      string qwdCqETWpw;
      string MUXJTpMLTF;
      string ZDXrTcgCGi;
      string KBoVdFfpCF;
      string GUDuIWqtIj;
      string ZyHYOnXkhO;
      string WQQHlKfBeN;
      string KWIOyEzbjw;
      string kltVILtQHp;
      string guHnhpEuJy;
      string qoOtZCosaJ;
      string nuAkckWtzZ;
      string PPtogOOUgI;
      string AESlFuXzwF;
      if(qOEKGnLqPi == GUDuIWqtIj){WBpxCltVKw = true;}
      else if(GUDuIWqtIj == qOEKGnLqPi){fEBkZBLSwW = true;}
      if(oyDLPooheV == ZyHYOnXkhO){SJwjhbuZNK = true;}
      else if(ZyHYOnXkhO == oyDLPooheV){qMwVpOVlwU = true;}
      if(AEFcfSxPNM == WQQHlKfBeN){nULRJjcOfg = true;}
      else if(WQQHlKfBeN == AEFcfSxPNM){IybfsBpRgA = true;}
      if(rjegUTcUKU == KWIOyEzbjw){MXysDOZwmt = true;}
      else if(KWIOyEzbjw == rjegUTcUKU){rdbflXsXce = true;}
      if(BKrtJartqU == kltVILtQHp){UrJjpqHhEc = true;}
      else if(kltVILtQHp == BKrtJartqU){CSPEJMEleX = true;}
      if(rODbalJaen == guHnhpEuJy){AyllRCoXnR = true;}
      else if(guHnhpEuJy == rODbalJaen){SPjelgbVrY = true;}
      if(qwdCqETWpw == qoOtZCosaJ){IfpcjuKDgS = true;}
      else if(qoOtZCosaJ == qwdCqETWpw){KskwdNkQjR = true;}
      if(MUXJTpMLTF == nuAkckWtzZ){CylSouKbaR = true;}
      if(ZDXrTcgCGi == PPtogOOUgI){btJDgOlMaB = true;}
      if(KBoVdFfpCF == AESlFuXzwF){YBHUloCfAu = true;}
      while(nuAkckWtzZ == MUXJTpMLTF){VxIRRpiWVg = true;}
      while(PPtogOOUgI == PPtogOOUgI){wEmJgbtxtE = true;}
      while(AESlFuXzwF == AESlFuXzwF){uWfEUJgTaw = true;}
      if(WBpxCltVKw == true){WBpxCltVKw = false;}
      if(SJwjhbuZNK == true){SJwjhbuZNK = false;}
      if(nULRJjcOfg == true){nULRJjcOfg = false;}
      if(MXysDOZwmt == true){MXysDOZwmt = false;}
      if(UrJjpqHhEc == true){UrJjpqHhEc = false;}
      if(AyllRCoXnR == true){AyllRCoXnR = false;}
      if(IfpcjuKDgS == true){IfpcjuKDgS = false;}
      if(CylSouKbaR == true){CylSouKbaR = false;}
      if(btJDgOlMaB == true){btJDgOlMaB = false;}
      if(YBHUloCfAu == true){YBHUloCfAu = false;}
      if(fEBkZBLSwW == true){fEBkZBLSwW = false;}
      if(qMwVpOVlwU == true){qMwVpOVlwU = false;}
      if(IybfsBpRgA == true){IybfsBpRgA = false;}
      if(rdbflXsXce == true){rdbflXsXce = false;}
      if(CSPEJMEleX == true){CSPEJMEleX = false;}
      if(SPjelgbVrY == true){SPjelgbVrY = false;}
      if(KskwdNkQjR == true){KskwdNkQjR = false;}
      if(VxIRRpiWVg == true){VxIRRpiWVg = false;}
      if(wEmJgbtxtE == true){wEmJgbtxtE = false;}
      if(uWfEUJgTaw == true){uWfEUJgTaw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CDAZARFYQZ
{ 
  void mWuLSbcBWF()
  { 
      bool URVoyhFydP = false;
      bool wtnNptFcwr = false;
      bool EagCyWLNik = false;
      bool nFcqmSxaLQ = false;
      bool TcFUJdmPEr = false;
      bool eJhATtjSpa = false;
      bool WrOrbqQxZW = false;
      bool wdQeYbUMsU = false;
      bool jwIpGdWcXs = false;
      bool hejktaNNrR = false;
      bool MpogwAsCaq = false;
      bool ZXZVpZjXky = false;
      bool TnZgoRtekx = false;
      bool NGTbItGatF = false;
      bool kUCfSJFOuT = false;
      bool qpbtxYQIre = false;
      bool GNRddSExMw = false;
      bool SIdeMzksNf = false;
      bool LejQGXeZei = false;
      bool dyiPzXDXCA = false;
      string hXmudJYxem;
      string RxxxokSbrl;
      string NRTbWeadFt;
      string GxsAwcnwYJ;
      string FicIKtsXVq;
      string gBczkQELXy;
      string huqjgTDwAL;
      string xVCigenKRc;
      string lDHOMETsPf;
      string YcYZbKqrbp;
      string pwXJtLytSF;
      string bsstMdmcXb;
      string zJfTmTxcHW;
      string nuialoeyUB;
      string FZaKEejdMx;
      string WOUzpfQDVZ;
      string NVmwRfJRIX;
      string znIWVZiVPI;
      string jTPKzZaikF;
      string YbctmjldrX;
      if(hXmudJYxem == pwXJtLytSF){URVoyhFydP = true;}
      else if(pwXJtLytSF == hXmudJYxem){MpogwAsCaq = true;}
      if(RxxxokSbrl == bsstMdmcXb){wtnNptFcwr = true;}
      else if(bsstMdmcXb == RxxxokSbrl){ZXZVpZjXky = true;}
      if(NRTbWeadFt == zJfTmTxcHW){EagCyWLNik = true;}
      else if(zJfTmTxcHW == NRTbWeadFt){TnZgoRtekx = true;}
      if(GxsAwcnwYJ == nuialoeyUB){nFcqmSxaLQ = true;}
      else if(nuialoeyUB == GxsAwcnwYJ){NGTbItGatF = true;}
      if(FicIKtsXVq == FZaKEejdMx){TcFUJdmPEr = true;}
      else if(FZaKEejdMx == FicIKtsXVq){kUCfSJFOuT = true;}
      if(gBczkQELXy == WOUzpfQDVZ){eJhATtjSpa = true;}
      else if(WOUzpfQDVZ == gBczkQELXy){qpbtxYQIre = true;}
      if(huqjgTDwAL == NVmwRfJRIX){WrOrbqQxZW = true;}
      else if(NVmwRfJRIX == huqjgTDwAL){GNRddSExMw = true;}
      if(xVCigenKRc == znIWVZiVPI){wdQeYbUMsU = true;}
      if(lDHOMETsPf == jTPKzZaikF){jwIpGdWcXs = true;}
      if(YcYZbKqrbp == YbctmjldrX){hejktaNNrR = true;}
      while(znIWVZiVPI == xVCigenKRc){SIdeMzksNf = true;}
      while(jTPKzZaikF == jTPKzZaikF){LejQGXeZei = true;}
      while(YbctmjldrX == YbctmjldrX){dyiPzXDXCA = true;}
      if(URVoyhFydP == true){URVoyhFydP = false;}
      if(wtnNptFcwr == true){wtnNptFcwr = false;}
      if(EagCyWLNik == true){EagCyWLNik = false;}
      if(nFcqmSxaLQ == true){nFcqmSxaLQ = false;}
      if(TcFUJdmPEr == true){TcFUJdmPEr = false;}
      if(eJhATtjSpa == true){eJhATtjSpa = false;}
      if(WrOrbqQxZW == true){WrOrbqQxZW = false;}
      if(wdQeYbUMsU == true){wdQeYbUMsU = false;}
      if(jwIpGdWcXs == true){jwIpGdWcXs = false;}
      if(hejktaNNrR == true){hejktaNNrR = false;}
      if(MpogwAsCaq == true){MpogwAsCaq = false;}
      if(ZXZVpZjXky == true){ZXZVpZjXky = false;}
      if(TnZgoRtekx == true){TnZgoRtekx = false;}
      if(NGTbItGatF == true){NGTbItGatF = false;}
      if(kUCfSJFOuT == true){kUCfSJFOuT = false;}
      if(qpbtxYQIre == true){qpbtxYQIre = false;}
      if(GNRddSExMw == true){GNRddSExMw = false;}
      if(SIdeMzksNf == true){SIdeMzksNf = false;}
      if(LejQGXeZei == true){LejQGXeZei = false;}
      if(dyiPzXDXCA == true){dyiPzXDXCA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WDADSKIRAJ
{ 
  void pINJEQiyZj()
  { 
      bool sSfmHLyEeK = false;
      bool hshVPIQTzW = false;
      bool WbtLPVapJy = false;
      bool IrxYgomCwR = false;
      bool hNnozTbKJP = false;
      bool sISrFQYTWk = false;
      bool kHtfBouJna = false;
      bool UOWgnInEMw = false;
      bool tQgsFAZETQ = false;
      bool PTeLgZTImJ = false;
      bool XRViuekkDw = false;
      bool bTHapUaAZB = false;
      bool PqpXKBiLzO = false;
      bool ofQCXbtxya = false;
      bool OnAWnwLEUM = false;
      bool yShltgbxYs = false;
      bool uZkoHwCFCN = false;
      bool adCzlbpSjO = false;
      bool oepmPWydHq = false;
      bool AwYFeoCLPq = false;
      string IOTptrbMeM;
      string aclFTtWhib;
      string CrpCzqYEJc;
      string HdAnbOUjPe;
      string aeUTbakeQS;
      string HdRcVQXQqD;
      string SXDCEwcycF;
      string ZlRDBWWVaX;
      string GtmpUdMWRL;
      string pDsMMDbSPe;
      string ylBKsUMNbz;
      string sCpTwYjMga;
      string jFfROVsFqx;
      string uEGuZTscxz;
      string RyuSRnNZPm;
      string TOknurGiwX;
      string bGWdDoutsc;
      string fHPgJkKMAZ;
      string IToDdgSSAg;
      string MJfYXKbRPb;
      if(IOTptrbMeM == ylBKsUMNbz){sSfmHLyEeK = true;}
      else if(ylBKsUMNbz == IOTptrbMeM){XRViuekkDw = true;}
      if(aclFTtWhib == sCpTwYjMga){hshVPIQTzW = true;}
      else if(sCpTwYjMga == aclFTtWhib){bTHapUaAZB = true;}
      if(CrpCzqYEJc == jFfROVsFqx){WbtLPVapJy = true;}
      else if(jFfROVsFqx == CrpCzqYEJc){PqpXKBiLzO = true;}
      if(HdAnbOUjPe == uEGuZTscxz){IrxYgomCwR = true;}
      else if(uEGuZTscxz == HdAnbOUjPe){ofQCXbtxya = true;}
      if(aeUTbakeQS == RyuSRnNZPm){hNnozTbKJP = true;}
      else if(RyuSRnNZPm == aeUTbakeQS){OnAWnwLEUM = true;}
      if(HdRcVQXQqD == TOknurGiwX){sISrFQYTWk = true;}
      else if(TOknurGiwX == HdRcVQXQqD){yShltgbxYs = true;}
      if(SXDCEwcycF == bGWdDoutsc){kHtfBouJna = true;}
      else if(bGWdDoutsc == SXDCEwcycF){uZkoHwCFCN = true;}
      if(ZlRDBWWVaX == fHPgJkKMAZ){UOWgnInEMw = true;}
      if(GtmpUdMWRL == IToDdgSSAg){tQgsFAZETQ = true;}
      if(pDsMMDbSPe == MJfYXKbRPb){PTeLgZTImJ = true;}
      while(fHPgJkKMAZ == ZlRDBWWVaX){adCzlbpSjO = true;}
      while(IToDdgSSAg == IToDdgSSAg){oepmPWydHq = true;}
      while(MJfYXKbRPb == MJfYXKbRPb){AwYFeoCLPq = true;}
      if(sSfmHLyEeK == true){sSfmHLyEeK = false;}
      if(hshVPIQTzW == true){hshVPIQTzW = false;}
      if(WbtLPVapJy == true){WbtLPVapJy = false;}
      if(IrxYgomCwR == true){IrxYgomCwR = false;}
      if(hNnozTbKJP == true){hNnozTbKJP = false;}
      if(sISrFQYTWk == true){sISrFQYTWk = false;}
      if(kHtfBouJna == true){kHtfBouJna = false;}
      if(UOWgnInEMw == true){UOWgnInEMw = false;}
      if(tQgsFAZETQ == true){tQgsFAZETQ = false;}
      if(PTeLgZTImJ == true){PTeLgZTImJ = false;}
      if(XRViuekkDw == true){XRViuekkDw = false;}
      if(bTHapUaAZB == true){bTHapUaAZB = false;}
      if(PqpXKBiLzO == true){PqpXKBiLzO = false;}
      if(ofQCXbtxya == true){ofQCXbtxya = false;}
      if(OnAWnwLEUM == true){OnAWnwLEUM = false;}
      if(yShltgbxYs == true){yShltgbxYs = false;}
      if(uZkoHwCFCN == true){uZkoHwCFCN = false;}
      if(adCzlbpSjO == true){adCzlbpSjO = false;}
      if(oepmPWydHq == true){oepmPWydHq = false;}
      if(AwYFeoCLPq == true){AwYFeoCLPq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IPZJBNYLTZ
{ 
  void dDsMBfkPUY()
  { 
      bool smxmBQYOEV = false;
      bool nkLKCPKPdW = false;
      bool nttFQlwmRJ = false;
      bool IBqsYUIHag = false;
      bool QdEsajKlUl = false;
      bool THfMXzrrVO = false;
      bool TkxtNltRkh = false;
      bool GCoxFJoBdg = false;
      bool bKSeoAVdUZ = false;
      bool bQkLMfgJfo = false;
      bool orAlfRShHO = false;
      bool JpNomJSREM = false;
      bool PQxLFpQckZ = false;
      bool bfVoqiJfzX = false;
      bool gnWGQlCwXC = false;
      bool MPESZYuogo = false;
      bool ApxglcUXxE = false;
      bool AlSgeatquT = false;
      bool mUEhMMaDPS = false;
      bool nUzKWqpoTm = false;
      string smAhpQyXpa;
      string PWcNjoWpxy;
      string RiPJkFSRji;
      string tVzWMWNxcE;
      string LPgxsWoQCo;
      string RlYZnJWqwj;
      string ygnHgsXFAN;
      string aYMsmBBSQN;
      string QCOuQIwYiC;
      string AWAsFdbZQz;
      string yiPoNsYfll;
      string IEaiTuSrqX;
      string xzWyNDXTmJ;
      string ZbBQOgmYgW;
      string iQmwsuwRYK;
      string KihsCzLQbJ;
      string UErcMgCJTl;
      string IsKTnfLaFR;
      string HFtcypsIOO;
      string UVwWBdXJjM;
      if(smAhpQyXpa == yiPoNsYfll){smxmBQYOEV = true;}
      else if(yiPoNsYfll == smAhpQyXpa){orAlfRShHO = true;}
      if(PWcNjoWpxy == IEaiTuSrqX){nkLKCPKPdW = true;}
      else if(IEaiTuSrqX == PWcNjoWpxy){JpNomJSREM = true;}
      if(RiPJkFSRji == xzWyNDXTmJ){nttFQlwmRJ = true;}
      else if(xzWyNDXTmJ == RiPJkFSRji){PQxLFpQckZ = true;}
      if(tVzWMWNxcE == ZbBQOgmYgW){IBqsYUIHag = true;}
      else if(ZbBQOgmYgW == tVzWMWNxcE){bfVoqiJfzX = true;}
      if(LPgxsWoQCo == iQmwsuwRYK){QdEsajKlUl = true;}
      else if(iQmwsuwRYK == LPgxsWoQCo){gnWGQlCwXC = true;}
      if(RlYZnJWqwj == KihsCzLQbJ){THfMXzrrVO = true;}
      else if(KihsCzLQbJ == RlYZnJWqwj){MPESZYuogo = true;}
      if(ygnHgsXFAN == UErcMgCJTl){TkxtNltRkh = true;}
      else if(UErcMgCJTl == ygnHgsXFAN){ApxglcUXxE = true;}
      if(aYMsmBBSQN == IsKTnfLaFR){GCoxFJoBdg = true;}
      if(QCOuQIwYiC == HFtcypsIOO){bKSeoAVdUZ = true;}
      if(AWAsFdbZQz == UVwWBdXJjM){bQkLMfgJfo = true;}
      while(IsKTnfLaFR == aYMsmBBSQN){AlSgeatquT = true;}
      while(HFtcypsIOO == HFtcypsIOO){mUEhMMaDPS = true;}
      while(UVwWBdXJjM == UVwWBdXJjM){nUzKWqpoTm = true;}
      if(smxmBQYOEV == true){smxmBQYOEV = false;}
      if(nkLKCPKPdW == true){nkLKCPKPdW = false;}
      if(nttFQlwmRJ == true){nttFQlwmRJ = false;}
      if(IBqsYUIHag == true){IBqsYUIHag = false;}
      if(QdEsajKlUl == true){QdEsajKlUl = false;}
      if(THfMXzrrVO == true){THfMXzrrVO = false;}
      if(TkxtNltRkh == true){TkxtNltRkh = false;}
      if(GCoxFJoBdg == true){GCoxFJoBdg = false;}
      if(bKSeoAVdUZ == true){bKSeoAVdUZ = false;}
      if(bQkLMfgJfo == true){bQkLMfgJfo = false;}
      if(orAlfRShHO == true){orAlfRShHO = false;}
      if(JpNomJSREM == true){JpNomJSREM = false;}
      if(PQxLFpQckZ == true){PQxLFpQckZ = false;}
      if(bfVoqiJfzX == true){bfVoqiJfzX = false;}
      if(gnWGQlCwXC == true){gnWGQlCwXC = false;}
      if(MPESZYuogo == true){MPESZYuogo = false;}
      if(ApxglcUXxE == true){ApxglcUXxE = false;}
      if(AlSgeatquT == true){AlSgeatquT = false;}
      if(mUEhMMaDPS == true){mUEhMMaDPS = false;}
      if(nUzKWqpoTm == true){nUzKWqpoTm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FNBQMLNJRW
{ 
  void lknYPfUgKT()
  { 
      bool lTRKFluLYw = false;
      bool LsNdyqSlpA = false;
      bool uGiELQyeat = false;
      bool zukZUwwCDL = false;
      bool BpNgCyKggI = false;
      bool CJULjfkNyn = false;
      bool mPjewPImIC = false;
      bool tQidyFrCBM = false;
      bool GQySroaZoo = false;
      bool KiEOYlFijl = false;
      bool pWYeOkapMe = false;
      bool miLlhVRRlH = false;
      bool ohyTqKLTFL = false;
      bool zIRPVirTEG = false;
      bool NkMKCbXRgC = false;
      bool UnxbxIYEmD = false;
      bool ZHjBedQwPz = false;
      bool cxNesEVmQO = false;
      bool mslCqLLpRN = false;
      bool JmfAgGALeX = false;
      string EancGhajsX;
      string EMiGDzdypp;
      string jNTJWnCrYC;
      string wYVVGLqrUI;
      string nVIiJPIETT;
      string qlgkNpHeGS;
      string fhKpbeqNAr;
      string IkdgBNFjzG;
      string exYFKJqjIP;
      string DLkCcGKRHe;
      string YuEaKFIzjz;
      string kWfAmhJFfR;
      string mGFjnwAbEu;
      string CmcTgirytF;
      string BrAIdgfkOu;
      string xFloqSpTlO;
      string FfuoxxtLSE;
      string oKKZPuGwGH;
      string QOMIyxBmcO;
      string rYLezUwKLf;
      if(EancGhajsX == YuEaKFIzjz){lTRKFluLYw = true;}
      else if(YuEaKFIzjz == EancGhajsX){pWYeOkapMe = true;}
      if(EMiGDzdypp == kWfAmhJFfR){LsNdyqSlpA = true;}
      else if(kWfAmhJFfR == EMiGDzdypp){miLlhVRRlH = true;}
      if(jNTJWnCrYC == mGFjnwAbEu){uGiELQyeat = true;}
      else if(mGFjnwAbEu == jNTJWnCrYC){ohyTqKLTFL = true;}
      if(wYVVGLqrUI == CmcTgirytF){zukZUwwCDL = true;}
      else if(CmcTgirytF == wYVVGLqrUI){zIRPVirTEG = true;}
      if(nVIiJPIETT == BrAIdgfkOu){BpNgCyKggI = true;}
      else if(BrAIdgfkOu == nVIiJPIETT){NkMKCbXRgC = true;}
      if(qlgkNpHeGS == xFloqSpTlO){CJULjfkNyn = true;}
      else if(xFloqSpTlO == qlgkNpHeGS){UnxbxIYEmD = true;}
      if(fhKpbeqNAr == FfuoxxtLSE){mPjewPImIC = true;}
      else if(FfuoxxtLSE == fhKpbeqNAr){ZHjBedQwPz = true;}
      if(IkdgBNFjzG == oKKZPuGwGH){tQidyFrCBM = true;}
      if(exYFKJqjIP == QOMIyxBmcO){GQySroaZoo = true;}
      if(DLkCcGKRHe == rYLezUwKLf){KiEOYlFijl = true;}
      while(oKKZPuGwGH == IkdgBNFjzG){cxNesEVmQO = true;}
      while(QOMIyxBmcO == QOMIyxBmcO){mslCqLLpRN = true;}
      while(rYLezUwKLf == rYLezUwKLf){JmfAgGALeX = true;}
      if(lTRKFluLYw == true){lTRKFluLYw = false;}
      if(LsNdyqSlpA == true){LsNdyqSlpA = false;}
      if(uGiELQyeat == true){uGiELQyeat = false;}
      if(zukZUwwCDL == true){zukZUwwCDL = false;}
      if(BpNgCyKggI == true){BpNgCyKggI = false;}
      if(CJULjfkNyn == true){CJULjfkNyn = false;}
      if(mPjewPImIC == true){mPjewPImIC = false;}
      if(tQidyFrCBM == true){tQidyFrCBM = false;}
      if(GQySroaZoo == true){GQySroaZoo = false;}
      if(KiEOYlFijl == true){KiEOYlFijl = false;}
      if(pWYeOkapMe == true){pWYeOkapMe = false;}
      if(miLlhVRRlH == true){miLlhVRRlH = false;}
      if(ohyTqKLTFL == true){ohyTqKLTFL = false;}
      if(zIRPVirTEG == true){zIRPVirTEG = false;}
      if(NkMKCbXRgC == true){NkMKCbXRgC = false;}
      if(UnxbxIYEmD == true){UnxbxIYEmD = false;}
      if(ZHjBedQwPz == true){ZHjBedQwPz = false;}
      if(cxNesEVmQO == true){cxNesEVmQO = false;}
      if(mslCqLLpRN == true){mslCqLLpRN = false;}
      if(JmfAgGALeX == true){JmfAgGALeX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NJHVUSTZES
{ 
  void DVOeseufNt()
  { 
      bool PWchgOaEHQ = false;
      bool idAKpxRNgW = false;
      bool rzguTVQMfJ = false;
      bool XWpsZOiIQS = false;
      bool EukbPzDqXl = false;
      bool UMgSwPohOL = false;
      bool xNXysLmHjb = false;
      bool OJwNRwNFeU = false;
      bool SYotoKpXwJ = false;
      bool YAtFVpWmhE = false;
      bool LuHwXKQTAz = false;
      bool BjDssYYdIi = false;
      bool VPKZCNPqrb = false;
      bool YaXZIWRrWd = false;
      bool tWWxInxAMw = false;
      bool QsdyiwjgsJ = false;
      bool uZbYZaMckV = false;
      bool HfGeoyrNRO = false;
      bool QPduKfwYqM = false;
      bool mkzMiTuyWh = false;
      string ytrRBiThFA;
      string hSHWnjVzgn;
      string ehHACyoyTF;
      string jrzJMnWAPK;
      string WffMpBeGyV;
      string QLntiQmqOC;
      string sUNAPpTyKz;
      string MViWQzBuJB;
      string ThAxoXEFau;
      string BekNRBRfwA;
      string hgwyItcRci;
      string OrhNiKUPKq;
      string kNWOyhjUFO;
      string gVyITlkCot;
      string umbqgJwXeG;
      string gBUEPTJhza;
      string KIMOBrsZtw;
      string YSaQwykfgo;
      string kMpyheAssz;
      string cDCNjlaNon;
      if(ytrRBiThFA == hgwyItcRci){PWchgOaEHQ = true;}
      else if(hgwyItcRci == ytrRBiThFA){LuHwXKQTAz = true;}
      if(hSHWnjVzgn == OrhNiKUPKq){idAKpxRNgW = true;}
      else if(OrhNiKUPKq == hSHWnjVzgn){BjDssYYdIi = true;}
      if(ehHACyoyTF == kNWOyhjUFO){rzguTVQMfJ = true;}
      else if(kNWOyhjUFO == ehHACyoyTF){VPKZCNPqrb = true;}
      if(jrzJMnWAPK == gVyITlkCot){XWpsZOiIQS = true;}
      else if(gVyITlkCot == jrzJMnWAPK){YaXZIWRrWd = true;}
      if(WffMpBeGyV == umbqgJwXeG){EukbPzDqXl = true;}
      else if(umbqgJwXeG == WffMpBeGyV){tWWxInxAMw = true;}
      if(QLntiQmqOC == gBUEPTJhza){UMgSwPohOL = true;}
      else if(gBUEPTJhza == QLntiQmqOC){QsdyiwjgsJ = true;}
      if(sUNAPpTyKz == KIMOBrsZtw){xNXysLmHjb = true;}
      else if(KIMOBrsZtw == sUNAPpTyKz){uZbYZaMckV = true;}
      if(MViWQzBuJB == YSaQwykfgo){OJwNRwNFeU = true;}
      if(ThAxoXEFau == kMpyheAssz){SYotoKpXwJ = true;}
      if(BekNRBRfwA == cDCNjlaNon){YAtFVpWmhE = true;}
      while(YSaQwykfgo == MViWQzBuJB){HfGeoyrNRO = true;}
      while(kMpyheAssz == kMpyheAssz){QPduKfwYqM = true;}
      while(cDCNjlaNon == cDCNjlaNon){mkzMiTuyWh = true;}
      if(PWchgOaEHQ == true){PWchgOaEHQ = false;}
      if(idAKpxRNgW == true){idAKpxRNgW = false;}
      if(rzguTVQMfJ == true){rzguTVQMfJ = false;}
      if(XWpsZOiIQS == true){XWpsZOiIQS = false;}
      if(EukbPzDqXl == true){EukbPzDqXl = false;}
      if(UMgSwPohOL == true){UMgSwPohOL = false;}
      if(xNXysLmHjb == true){xNXysLmHjb = false;}
      if(OJwNRwNFeU == true){OJwNRwNFeU = false;}
      if(SYotoKpXwJ == true){SYotoKpXwJ = false;}
      if(YAtFVpWmhE == true){YAtFVpWmhE = false;}
      if(LuHwXKQTAz == true){LuHwXKQTAz = false;}
      if(BjDssYYdIi == true){BjDssYYdIi = false;}
      if(VPKZCNPqrb == true){VPKZCNPqrb = false;}
      if(YaXZIWRrWd == true){YaXZIWRrWd = false;}
      if(tWWxInxAMw == true){tWWxInxAMw = false;}
      if(QsdyiwjgsJ == true){QsdyiwjgsJ = false;}
      if(uZbYZaMckV == true){uZbYZaMckV = false;}
      if(HfGeoyrNRO == true){HfGeoyrNRO = false;}
      if(QPduKfwYqM == true){QPduKfwYqM = false;}
      if(mkzMiTuyWh == true){mkzMiTuyWh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PBTNWCTNIJ
{ 
  void rdJCStIcsI()
  { 
      bool JxnBNncUkQ = false;
      bool WyhyubcIOi = false;
      bool sTGdiaiUia = false;
      bool RzwGFiPCkc = false;
      bool hoYALdnqsa = false;
      bool fbcFmppJSl = false;
      bool EIlJzWBbsM = false;
      bool LaWkBDtGSF = false;
      bool mraHuoWqSP = false;
      bool rGjzXZDOAn = false;
      bool bMxgOFFqEj = false;
      bool uiqNzMgdOJ = false;
      bool AKIdTFpXMb = false;
      bool AeGdcattro = false;
      bool jemiTIOVzL = false;
      bool rYApnQDTMJ = false;
      bool OgdciPcMjY = false;
      bool SmkYZVXZJK = false;
      bool pTYBiaePoM = false;
      bool WZgiaDAJzE = false;
      string mblXLdaPRH;
      string xCZBbVHajG;
      string iUqaqVFezY;
      string ooJbYepqZZ;
      string laWOYTDULH;
      string CzcdASjLfp;
      string YwQrRHsxcw;
      string fQAKUHxbCW;
      string SjSqVpLfbF;
      string ueKjApKexQ;
      string aFrOblySJr;
      string VIJJWocYWb;
      string wNVWBAFQKd;
      string xSekwMqDPj;
      string qsWjjlUBML;
      string MlHUTNjUNa;
      string fhHetDcXMK;
      string xYIljCqlmO;
      string fEEzQLKJQh;
      string bVpnDJkqof;
      if(mblXLdaPRH == aFrOblySJr){JxnBNncUkQ = true;}
      else if(aFrOblySJr == mblXLdaPRH){bMxgOFFqEj = true;}
      if(xCZBbVHajG == VIJJWocYWb){WyhyubcIOi = true;}
      else if(VIJJWocYWb == xCZBbVHajG){uiqNzMgdOJ = true;}
      if(iUqaqVFezY == wNVWBAFQKd){sTGdiaiUia = true;}
      else if(wNVWBAFQKd == iUqaqVFezY){AKIdTFpXMb = true;}
      if(ooJbYepqZZ == xSekwMqDPj){RzwGFiPCkc = true;}
      else if(xSekwMqDPj == ooJbYepqZZ){AeGdcattro = true;}
      if(laWOYTDULH == qsWjjlUBML){hoYALdnqsa = true;}
      else if(qsWjjlUBML == laWOYTDULH){jemiTIOVzL = true;}
      if(CzcdASjLfp == MlHUTNjUNa){fbcFmppJSl = true;}
      else if(MlHUTNjUNa == CzcdASjLfp){rYApnQDTMJ = true;}
      if(YwQrRHsxcw == fhHetDcXMK){EIlJzWBbsM = true;}
      else if(fhHetDcXMK == YwQrRHsxcw){OgdciPcMjY = true;}
      if(fQAKUHxbCW == xYIljCqlmO){LaWkBDtGSF = true;}
      if(SjSqVpLfbF == fEEzQLKJQh){mraHuoWqSP = true;}
      if(ueKjApKexQ == bVpnDJkqof){rGjzXZDOAn = true;}
      while(xYIljCqlmO == fQAKUHxbCW){SmkYZVXZJK = true;}
      while(fEEzQLKJQh == fEEzQLKJQh){pTYBiaePoM = true;}
      while(bVpnDJkqof == bVpnDJkqof){WZgiaDAJzE = true;}
      if(JxnBNncUkQ == true){JxnBNncUkQ = false;}
      if(WyhyubcIOi == true){WyhyubcIOi = false;}
      if(sTGdiaiUia == true){sTGdiaiUia = false;}
      if(RzwGFiPCkc == true){RzwGFiPCkc = false;}
      if(hoYALdnqsa == true){hoYALdnqsa = false;}
      if(fbcFmppJSl == true){fbcFmppJSl = false;}
      if(EIlJzWBbsM == true){EIlJzWBbsM = false;}
      if(LaWkBDtGSF == true){LaWkBDtGSF = false;}
      if(mraHuoWqSP == true){mraHuoWqSP = false;}
      if(rGjzXZDOAn == true){rGjzXZDOAn = false;}
      if(bMxgOFFqEj == true){bMxgOFFqEj = false;}
      if(uiqNzMgdOJ == true){uiqNzMgdOJ = false;}
      if(AKIdTFpXMb == true){AKIdTFpXMb = false;}
      if(AeGdcattro == true){AeGdcattro = false;}
      if(jemiTIOVzL == true){jemiTIOVzL = false;}
      if(rYApnQDTMJ == true){rYApnQDTMJ = false;}
      if(OgdciPcMjY == true){OgdciPcMjY = false;}
      if(SmkYZVXZJK == true){SmkYZVXZJK = false;}
      if(pTYBiaePoM == true){pTYBiaePoM = false;}
      if(WZgiaDAJzE == true){WZgiaDAJzE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMFBQASHEF
{ 
  void FSAiUVyXYh()
  { 
      bool loTtldizQS = false;
      bool NQHAbKquCy = false;
      bool FFEgWTXgSW = false;
      bool HuzPMusjpb = false;
      bool unuzSKJweT = false;
      bool TwRBtgklWR = false;
      bool FBgsKSRqnf = false;
      bool QHEaDQJENM = false;
      bool KaCyDLdyVf = false;
      bool KHMYVsHBnA = false;
      bool rRIyDLrpxc = false;
      bool WfXKGdyioz = false;
      bool nTVIVJufFJ = false;
      bool JIQNTrSEur = false;
      bool TnArJdiBRr = false;
      bool uYMoLYwAbt = false;
      bool PLknTOPJqO = false;
      bool LtmwfASdzr = false;
      bool ZsNMOkuaCt = false;
      bool wSbAbHDMXu = false;
      string LcaokwykIM;
      string IGAbNFOOrG;
      string wxbCiLxgAn;
      string XGYRofqMIw;
      string jPPDjCaXiX;
      string TyTjKNBYFZ;
      string zRkToCgimg;
      string OBFwWfhYSg;
      string jYycUZmoGa;
      string eRGiwRewOh;
      string VrjBISrWMd;
      string fbGYpZSHzP;
      string PrbLBwtWzE;
      string BkKjKqoxTC;
      string gPbcuDLhrW;
      string zWxzSdPXzM;
      string XVXIctQVOy;
      string kVnxhzPzQy;
      string kMdcFdnLRg;
      string aQxGdKqTzA;
      if(LcaokwykIM == VrjBISrWMd){loTtldizQS = true;}
      else if(VrjBISrWMd == LcaokwykIM){rRIyDLrpxc = true;}
      if(IGAbNFOOrG == fbGYpZSHzP){NQHAbKquCy = true;}
      else if(fbGYpZSHzP == IGAbNFOOrG){WfXKGdyioz = true;}
      if(wxbCiLxgAn == PrbLBwtWzE){FFEgWTXgSW = true;}
      else if(PrbLBwtWzE == wxbCiLxgAn){nTVIVJufFJ = true;}
      if(XGYRofqMIw == BkKjKqoxTC){HuzPMusjpb = true;}
      else if(BkKjKqoxTC == XGYRofqMIw){JIQNTrSEur = true;}
      if(jPPDjCaXiX == gPbcuDLhrW){unuzSKJweT = true;}
      else if(gPbcuDLhrW == jPPDjCaXiX){TnArJdiBRr = true;}
      if(TyTjKNBYFZ == zWxzSdPXzM){TwRBtgklWR = true;}
      else if(zWxzSdPXzM == TyTjKNBYFZ){uYMoLYwAbt = true;}
      if(zRkToCgimg == XVXIctQVOy){FBgsKSRqnf = true;}
      else if(XVXIctQVOy == zRkToCgimg){PLknTOPJqO = true;}
      if(OBFwWfhYSg == kVnxhzPzQy){QHEaDQJENM = true;}
      if(jYycUZmoGa == kMdcFdnLRg){KaCyDLdyVf = true;}
      if(eRGiwRewOh == aQxGdKqTzA){KHMYVsHBnA = true;}
      while(kVnxhzPzQy == OBFwWfhYSg){LtmwfASdzr = true;}
      while(kMdcFdnLRg == kMdcFdnLRg){ZsNMOkuaCt = true;}
      while(aQxGdKqTzA == aQxGdKqTzA){wSbAbHDMXu = true;}
      if(loTtldizQS == true){loTtldizQS = false;}
      if(NQHAbKquCy == true){NQHAbKquCy = false;}
      if(FFEgWTXgSW == true){FFEgWTXgSW = false;}
      if(HuzPMusjpb == true){HuzPMusjpb = false;}
      if(unuzSKJweT == true){unuzSKJweT = false;}
      if(TwRBtgklWR == true){TwRBtgklWR = false;}
      if(FBgsKSRqnf == true){FBgsKSRqnf = false;}
      if(QHEaDQJENM == true){QHEaDQJENM = false;}
      if(KaCyDLdyVf == true){KaCyDLdyVf = false;}
      if(KHMYVsHBnA == true){KHMYVsHBnA = false;}
      if(rRIyDLrpxc == true){rRIyDLrpxc = false;}
      if(WfXKGdyioz == true){WfXKGdyioz = false;}
      if(nTVIVJufFJ == true){nTVIVJufFJ = false;}
      if(JIQNTrSEur == true){JIQNTrSEur = false;}
      if(TnArJdiBRr == true){TnArJdiBRr = false;}
      if(uYMoLYwAbt == true){uYMoLYwAbt = false;}
      if(PLknTOPJqO == true){PLknTOPJqO = false;}
      if(LtmwfASdzr == true){LtmwfASdzr = false;}
      if(ZsNMOkuaCt == true){ZsNMOkuaCt = false;}
      if(wSbAbHDMXu == true){wSbAbHDMXu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBUZQESMWQ
{ 
  void sFIMccYddU()
  { 
      bool spTauKYLJm = false;
      bool LyrUtjGmwR = false;
      bool LCKqywofSx = false;
      bool YBUgJIpobm = false;
      bool igUhWyHssc = false;
      bool ShfPypfcbz = false;
      bool VssMNJdLKl = false;
      bool sRKJiehbTA = false;
      bool nwloeqUEhS = false;
      bool bNMbRpmITM = false;
      bool TwhHjAXWgS = false;
      bool IDIbKYGDgW = false;
      bool oYcrJeEhrs = false;
      bool qZHHfrNeFd = false;
      bool TyXPKXEkRr = false;
      bool ijaxXtSpxE = false;
      bool wodmbiwBuR = false;
      bool LaxCDpBNgk = false;
      bool aSQzJHyKil = false;
      bool YXgBhdTjma = false;
      string uzswcaXiux;
      string ogGVdbwbGy;
      string qoqxkVXrkB;
      string VLAKKdBBXX;
      string itYdlWJADo;
      string tNHWZFHuLG;
      string CeytbdfwKA;
      string atDiPxPNLO;
      string MXowGHDdjE;
      string VFpQUDueBH;
      string qNoDOzKYGb;
      string ptjwtdoCmU;
      string ZBLFeUEmOL;
      string BkLDXzilgH;
      string xeWIOaVsWq;
      string NsqghoBiXs;
      string tXJtZEhfYu;
      string uDUfWtdCqD;
      string yKQWxHseVh;
      string xzNnMZUchJ;
      if(uzswcaXiux == qNoDOzKYGb){spTauKYLJm = true;}
      else if(qNoDOzKYGb == uzswcaXiux){TwhHjAXWgS = true;}
      if(ogGVdbwbGy == ptjwtdoCmU){LyrUtjGmwR = true;}
      else if(ptjwtdoCmU == ogGVdbwbGy){IDIbKYGDgW = true;}
      if(qoqxkVXrkB == ZBLFeUEmOL){LCKqywofSx = true;}
      else if(ZBLFeUEmOL == qoqxkVXrkB){oYcrJeEhrs = true;}
      if(VLAKKdBBXX == BkLDXzilgH){YBUgJIpobm = true;}
      else if(BkLDXzilgH == VLAKKdBBXX){qZHHfrNeFd = true;}
      if(itYdlWJADo == xeWIOaVsWq){igUhWyHssc = true;}
      else if(xeWIOaVsWq == itYdlWJADo){TyXPKXEkRr = true;}
      if(tNHWZFHuLG == NsqghoBiXs){ShfPypfcbz = true;}
      else if(NsqghoBiXs == tNHWZFHuLG){ijaxXtSpxE = true;}
      if(CeytbdfwKA == tXJtZEhfYu){VssMNJdLKl = true;}
      else if(tXJtZEhfYu == CeytbdfwKA){wodmbiwBuR = true;}
      if(atDiPxPNLO == uDUfWtdCqD){sRKJiehbTA = true;}
      if(MXowGHDdjE == yKQWxHseVh){nwloeqUEhS = true;}
      if(VFpQUDueBH == xzNnMZUchJ){bNMbRpmITM = true;}
      while(uDUfWtdCqD == atDiPxPNLO){LaxCDpBNgk = true;}
      while(yKQWxHseVh == yKQWxHseVh){aSQzJHyKil = true;}
      while(xzNnMZUchJ == xzNnMZUchJ){YXgBhdTjma = true;}
      if(spTauKYLJm == true){spTauKYLJm = false;}
      if(LyrUtjGmwR == true){LyrUtjGmwR = false;}
      if(LCKqywofSx == true){LCKqywofSx = false;}
      if(YBUgJIpobm == true){YBUgJIpobm = false;}
      if(igUhWyHssc == true){igUhWyHssc = false;}
      if(ShfPypfcbz == true){ShfPypfcbz = false;}
      if(VssMNJdLKl == true){VssMNJdLKl = false;}
      if(sRKJiehbTA == true){sRKJiehbTA = false;}
      if(nwloeqUEhS == true){nwloeqUEhS = false;}
      if(bNMbRpmITM == true){bNMbRpmITM = false;}
      if(TwhHjAXWgS == true){TwhHjAXWgS = false;}
      if(IDIbKYGDgW == true){IDIbKYGDgW = false;}
      if(oYcrJeEhrs == true){oYcrJeEhrs = false;}
      if(qZHHfrNeFd == true){qZHHfrNeFd = false;}
      if(TyXPKXEkRr == true){TyXPKXEkRr = false;}
      if(ijaxXtSpxE == true){ijaxXtSpxE = false;}
      if(wodmbiwBuR == true){wodmbiwBuR = false;}
      if(LaxCDpBNgk == true){LaxCDpBNgk = false;}
      if(aSQzJHyKil == true){aSQzJHyKil = false;}
      if(YXgBhdTjma == true){YXgBhdTjma = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXAKAOKTQH
{ 
  void xehQfNGDpQ()
  { 
      bool rPgfWbkKyb = false;
      bool AYuuxtERlE = false;
      bool hftsUmjwke = false;
      bool RqOSFPOpVq = false;
      bool lFoYXUKncN = false;
      bool apnaHLVnKi = false;
      bool roYTJIKcog = false;
      bool fOwtScpVUA = false;
      bool cuSXEbDnLt = false;
      bool taelzwfVOO = false;
      bool KhyugLtsHd = false;
      bool UzSKGxVAOh = false;
      bool FWRumEiJuV = false;
      bool wTGGouwXps = false;
      bool hJfgYtIUfB = false;
      bool aeHgJnPDIb = false;
      bool bjxlhAsMUK = false;
      bool AyKUzupkVr = false;
      bool wOcsuQMZwB = false;
      bool erPNRyMtyX = false;
      string aHSmaWHqxs;
      string HdrrSKWaLa;
      string npOUXPJdtV;
      string efddqZIVjh;
      string UdYoVQhAxV;
      string lgwbQjsxOL;
      string NcxbObANBr;
      string CBpdGKRYyG;
      string hIgXixjBMG;
      string gKGYUqgxat;
      string QTyETkqSUF;
      string STzHcEuYrQ;
      string qyAuLqtQIO;
      string dUyDpNJcDy;
      string FRfGmNLyuQ;
      string uHEJCRSDsc;
      string paJGbyUuRP;
      string tSVsKZRtHy;
      string fuVrTWPnBX;
      string tGiZHeHZeo;
      if(aHSmaWHqxs == QTyETkqSUF){rPgfWbkKyb = true;}
      else if(QTyETkqSUF == aHSmaWHqxs){KhyugLtsHd = true;}
      if(HdrrSKWaLa == STzHcEuYrQ){AYuuxtERlE = true;}
      else if(STzHcEuYrQ == HdrrSKWaLa){UzSKGxVAOh = true;}
      if(npOUXPJdtV == qyAuLqtQIO){hftsUmjwke = true;}
      else if(qyAuLqtQIO == npOUXPJdtV){FWRumEiJuV = true;}
      if(efddqZIVjh == dUyDpNJcDy){RqOSFPOpVq = true;}
      else if(dUyDpNJcDy == efddqZIVjh){wTGGouwXps = true;}
      if(UdYoVQhAxV == FRfGmNLyuQ){lFoYXUKncN = true;}
      else if(FRfGmNLyuQ == UdYoVQhAxV){hJfgYtIUfB = true;}
      if(lgwbQjsxOL == uHEJCRSDsc){apnaHLVnKi = true;}
      else if(uHEJCRSDsc == lgwbQjsxOL){aeHgJnPDIb = true;}
      if(NcxbObANBr == paJGbyUuRP){roYTJIKcog = true;}
      else if(paJGbyUuRP == NcxbObANBr){bjxlhAsMUK = true;}
      if(CBpdGKRYyG == tSVsKZRtHy){fOwtScpVUA = true;}
      if(hIgXixjBMG == fuVrTWPnBX){cuSXEbDnLt = true;}
      if(gKGYUqgxat == tGiZHeHZeo){taelzwfVOO = true;}
      while(tSVsKZRtHy == CBpdGKRYyG){AyKUzupkVr = true;}
      while(fuVrTWPnBX == fuVrTWPnBX){wOcsuQMZwB = true;}
      while(tGiZHeHZeo == tGiZHeHZeo){erPNRyMtyX = true;}
      if(rPgfWbkKyb == true){rPgfWbkKyb = false;}
      if(AYuuxtERlE == true){AYuuxtERlE = false;}
      if(hftsUmjwke == true){hftsUmjwke = false;}
      if(RqOSFPOpVq == true){RqOSFPOpVq = false;}
      if(lFoYXUKncN == true){lFoYXUKncN = false;}
      if(apnaHLVnKi == true){apnaHLVnKi = false;}
      if(roYTJIKcog == true){roYTJIKcog = false;}
      if(fOwtScpVUA == true){fOwtScpVUA = false;}
      if(cuSXEbDnLt == true){cuSXEbDnLt = false;}
      if(taelzwfVOO == true){taelzwfVOO = false;}
      if(KhyugLtsHd == true){KhyugLtsHd = false;}
      if(UzSKGxVAOh == true){UzSKGxVAOh = false;}
      if(FWRumEiJuV == true){FWRumEiJuV = false;}
      if(wTGGouwXps == true){wTGGouwXps = false;}
      if(hJfgYtIUfB == true){hJfgYtIUfB = false;}
      if(aeHgJnPDIb == true){aeHgJnPDIb = false;}
      if(bjxlhAsMUK == true){bjxlhAsMUK = false;}
      if(AyKUzupkVr == true){AyKUzupkVr = false;}
      if(wOcsuQMZwB == true){wOcsuQMZwB = false;}
      if(erPNRyMtyX == true){erPNRyMtyX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MJVGEUFVWO
{ 
  void NDVKEBbfFl()
  { 
      bool cQlchaNMWB = false;
      bool OsSKnYBrhu = false;
      bool CUYucapBOO = false;
      bool hOzkRPoxOS = false;
      bool WsSniVkdUq = false;
      bool MDEYAHqpAG = false;
      bool kLxITztgsY = false;
      bool jDcPYIBjLG = false;
      bool pLgXCdKZjJ = false;
      bool XyxIgKuKUj = false;
      bool bDkuHJZoAr = false;
      bool FGdsQZdZFp = false;
      bool nTwiAkFUhN = false;
      bool NqPbelalQr = false;
      bool DVZrDQUEqH = false;
      bool gVEeuHHBtV = false;
      bool DFGldOqBNd = false;
      bool yrJNlStDfj = false;
      bool QBcZgrlkgW = false;
      bool eZqtoyOmOn = false;
      string gnThgtBQjX;
      string CGCVjycSXN;
      string cpWQhzmwSS;
      string jAyuGJUlaK;
      string iJEJynnVOJ;
      string xSNGHpQDAh;
      string HFxRmCHGOa;
      string cqqNdTkNRs;
      string KRgJVRlqmP;
      string rRksDdLmVu;
      string fgGnfFaAcm;
      string FDkGWpXnuU;
      string PQTziLFyKA;
      string IxqVNdKscP;
      string qlOzKnfeWM;
      string FXrBfPNHET;
      string zcpbeHLPss;
      string edKeddBTnt;
      string faaxtjFppx;
      string PDnIPOwlUC;
      if(gnThgtBQjX == fgGnfFaAcm){cQlchaNMWB = true;}
      else if(fgGnfFaAcm == gnThgtBQjX){bDkuHJZoAr = true;}
      if(CGCVjycSXN == FDkGWpXnuU){OsSKnYBrhu = true;}
      else if(FDkGWpXnuU == CGCVjycSXN){FGdsQZdZFp = true;}
      if(cpWQhzmwSS == PQTziLFyKA){CUYucapBOO = true;}
      else if(PQTziLFyKA == cpWQhzmwSS){nTwiAkFUhN = true;}
      if(jAyuGJUlaK == IxqVNdKscP){hOzkRPoxOS = true;}
      else if(IxqVNdKscP == jAyuGJUlaK){NqPbelalQr = true;}
      if(iJEJynnVOJ == qlOzKnfeWM){WsSniVkdUq = true;}
      else if(qlOzKnfeWM == iJEJynnVOJ){DVZrDQUEqH = true;}
      if(xSNGHpQDAh == FXrBfPNHET){MDEYAHqpAG = true;}
      else if(FXrBfPNHET == xSNGHpQDAh){gVEeuHHBtV = true;}
      if(HFxRmCHGOa == zcpbeHLPss){kLxITztgsY = true;}
      else if(zcpbeHLPss == HFxRmCHGOa){DFGldOqBNd = true;}
      if(cqqNdTkNRs == edKeddBTnt){jDcPYIBjLG = true;}
      if(KRgJVRlqmP == faaxtjFppx){pLgXCdKZjJ = true;}
      if(rRksDdLmVu == PDnIPOwlUC){XyxIgKuKUj = true;}
      while(edKeddBTnt == cqqNdTkNRs){yrJNlStDfj = true;}
      while(faaxtjFppx == faaxtjFppx){QBcZgrlkgW = true;}
      while(PDnIPOwlUC == PDnIPOwlUC){eZqtoyOmOn = true;}
      if(cQlchaNMWB == true){cQlchaNMWB = false;}
      if(OsSKnYBrhu == true){OsSKnYBrhu = false;}
      if(CUYucapBOO == true){CUYucapBOO = false;}
      if(hOzkRPoxOS == true){hOzkRPoxOS = false;}
      if(WsSniVkdUq == true){WsSniVkdUq = false;}
      if(MDEYAHqpAG == true){MDEYAHqpAG = false;}
      if(kLxITztgsY == true){kLxITztgsY = false;}
      if(jDcPYIBjLG == true){jDcPYIBjLG = false;}
      if(pLgXCdKZjJ == true){pLgXCdKZjJ = false;}
      if(XyxIgKuKUj == true){XyxIgKuKUj = false;}
      if(bDkuHJZoAr == true){bDkuHJZoAr = false;}
      if(FGdsQZdZFp == true){FGdsQZdZFp = false;}
      if(nTwiAkFUhN == true){nTwiAkFUhN = false;}
      if(NqPbelalQr == true){NqPbelalQr = false;}
      if(DVZrDQUEqH == true){DVZrDQUEqH = false;}
      if(gVEeuHHBtV == true){gVEeuHHBtV = false;}
      if(DFGldOqBNd == true){DFGldOqBNd = false;}
      if(yrJNlStDfj == true){yrJNlStDfj = false;}
      if(QBcZgrlkgW == true){QBcZgrlkgW = false;}
      if(eZqtoyOmOn == true){eZqtoyOmOn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CINSWPWOGU
{ 
  void gYMQErjKlj()
  { 
      bool SJNnQEFUax = false;
      bool tjbGQSeFjH = false;
      bool BFatxJjhVg = false;
      bool aqHnDOxQfA = false;
      bool sSqCQuKBkQ = false;
      bool ytGrRNhSqG = false;
      bool UXysVDbnCB = false;
      bool UNYiNhNXdB = false;
      bool ziwFigjPVo = false;
      bool geZYfUUxfN = false;
      bool TWyiujUWdj = false;
      bool zJnpHlasKo = false;
      bool SMRNUpnADr = false;
      bool NPqPgbjMKz = false;
      bool MNklpWpjQt = false;
      bool sbmquHEkOE = false;
      bool wTTkViRYIe = false;
      bool BOhKcFafXx = false;
      bool AEjIzlbAUZ = false;
      bool XzyFCrsAPG = false;
      string iMhRToAAxR;
      string BVLusBUiJz;
      string pcUKyrAyhO;
      string VNlzRLHesU;
      string ZjZGmXQdXr;
      string wyAQzGqWTb;
      string oBRiuniLch;
      string soooZFDOXa;
      string bWZpSWMVzL;
      string TjLReXRpKz;
      string nEApyGILpt;
      string CczrASbbQY;
      string aMMQNIdXJB;
      string nNEXlWVjqL;
      string NBeFJqkSRM;
      string woZkXbqibo;
      string ckBoFoXbFc;
      string wqjEKZgHHV;
      string XKFwFynSAK;
      string flHCiczpzT;
      if(iMhRToAAxR == nEApyGILpt){SJNnQEFUax = true;}
      else if(nEApyGILpt == iMhRToAAxR){TWyiujUWdj = true;}
      if(BVLusBUiJz == CczrASbbQY){tjbGQSeFjH = true;}
      else if(CczrASbbQY == BVLusBUiJz){zJnpHlasKo = true;}
      if(pcUKyrAyhO == aMMQNIdXJB){BFatxJjhVg = true;}
      else if(aMMQNIdXJB == pcUKyrAyhO){SMRNUpnADr = true;}
      if(VNlzRLHesU == nNEXlWVjqL){aqHnDOxQfA = true;}
      else if(nNEXlWVjqL == VNlzRLHesU){NPqPgbjMKz = true;}
      if(ZjZGmXQdXr == NBeFJqkSRM){sSqCQuKBkQ = true;}
      else if(NBeFJqkSRM == ZjZGmXQdXr){MNklpWpjQt = true;}
      if(wyAQzGqWTb == woZkXbqibo){ytGrRNhSqG = true;}
      else if(woZkXbqibo == wyAQzGqWTb){sbmquHEkOE = true;}
      if(oBRiuniLch == ckBoFoXbFc){UXysVDbnCB = true;}
      else if(ckBoFoXbFc == oBRiuniLch){wTTkViRYIe = true;}
      if(soooZFDOXa == wqjEKZgHHV){UNYiNhNXdB = true;}
      if(bWZpSWMVzL == XKFwFynSAK){ziwFigjPVo = true;}
      if(TjLReXRpKz == flHCiczpzT){geZYfUUxfN = true;}
      while(wqjEKZgHHV == soooZFDOXa){BOhKcFafXx = true;}
      while(XKFwFynSAK == XKFwFynSAK){AEjIzlbAUZ = true;}
      while(flHCiczpzT == flHCiczpzT){XzyFCrsAPG = true;}
      if(SJNnQEFUax == true){SJNnQEFUax = false;}
      if(tjbGQSeFjH == true){tjbGQSeFjH = false;}
      if(BFatxJjhVg == true){BFatxJjhVg = false;}
      if(aqHnDOxQfA == true){aqHnDOxQfA = false;}
      if(sSqCQuKBkQ == true){sSqCQuKBkQ = false;}
      if(ytGrRNhSqG == true){ytGrRNhSqG = false;}
      if(UXysVDbnCB == true){UXysVDbnCB = false;}
      if(UNYiNhNXdB == true){UNYiNhNXdB = false;}
      if(ziwFigjPVo == true){ziwFigjPVo = false;}
      if(geZYfUUxfN == true){geZYfUUxfN = false;}
      if(TWyiujUWdj == true){TWyiujUWdj = false;}
      if(zJnpHlasKo == true){zJnpHlasKo = false;}
      if(SMRNUpnADr == true){SMRNUpnADr = false;}
      if(NPqPgbjMKz == true){NPqPgbjMKz = false;}
      if(MNklpWpjQt == true){MNklpWpjQt = false;}
      if(sbmquHEkOE == true){sbmquHEkOE = false;}
      if(wTTkViRYIe == true){wTTkViRYIe = false;}
      if(BOhKcFafXx == true){BOhKcFafXx = false;}
      if(AEjIzlbAUZ == true){AEjIzlbAUZ = false;}
      if(XzyFCrsAPG == true){XzyFCrsAPG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NNIMBICSKO
{ 
  void kPEJpHSJTs()
  { 
      bool zEZNMEppjs = false;
      bool lUNmhXESOX = false;
      bool sWCxokiXJJ = false;
      bool dgZVmhjSaP = false;
      bool GuKFgzsmap = false;
      bool PfueEbBbXa = false;
      bool USfaPFuqzA = false;
      bool mlryRxLwQp = false;
      bool ruwStyluRK = false;
      bool fIuztmPjpa = false;
      bool DBmZDcmwMG = false;
      bool PFKhhZVMgQ = false;
      bool TAYoUeqrDe = false;
      bool hbGolpIWPQ = false;
      bool LohLtaxMQU = false;
      bool QCCZHDcyEX = false;
      bool ltrhXmyVwr = false;
      bool RzxQFeRNtt = false;
      bool gdbhNeZfhh = false;
      bool NJRqdQwzmG = false;
      string WYSwPsukQT;
      string PeRWgGowIN;
      string qLlRVXxIfT;
      string neiFSgggrf;
      string JmddpKIgdn;
      string psaWsLlAaq;
      string wlExekwLDA;
      string ZHEbEDgIbL;
      string OQdrduDLMH;
      string ufGAjWigyE;
      string NwcdNhoyRo;
      string ecYOceILSj;
      string hjzwEsBDrh;
      string UzKWxRmzdu;
      string FEsWcRGqXE;
      string NXNOWcxgYU;
      string gkGiUeSCRK;
      string rJgXdcpbTl;
      string lJfmUwkuzT;
      string UGZJNUyJCx;
      if(WYSwPsukQT == NwcdNhoyRo){zEZNMEppjs = true;}
      else if(NwcdNhoyRo == WYSwPsukQT){DBmZDcmwMG = true;}
      if(PeRWgGowIN == ecYOceILSj){lUNmhXESOX = true;}
      else if(ecYOceILSj == PeRWgGowIN){PFKhhZVMgQ = true;}
      if(qLlRVXxIfT == hjzwEsBDrh){sWCxokiXJJ = true;}
      else if(hjzwEsBDrh == qLlRVXxIfT){TAYoUeqrDe = true;}
      if(neiFSgggrf == UzKWxRmzdu){dgZVmhjSaP = true;}
      else if(UzKWxRmzdu == neiFSgggrf){hbGolpIWPQ = true;}
      if(JmddpKIgdn == FEsWcRGqXE){GuKFgzsmap = true;}
      else if(FEsWcRGqXE == JmddpKIgdn){LohLtaxMQU = true;}
      if(psaWsLlAaq == NXNOWcxgYU){PfueEbBbXa = true;}
      else if(NXNOWcxgYU == psaWsLlAaq){QCCZHDcyEX = true;}
      if(wlExekwLDA == gkGiUeSCRK){USfaPFuqzA = true;}
      else if(gkGiUeSCRK == wlExekwLDA){ltrhXmyVwr = true;}
      if(ZHEbEDgIbL == rJgXdcpbTl){mlryRxLwQp = true;}
      if(OQdrduDLMH == lJfmUwkuzT){ruwStyluRK = true;}
      if(ufGAjWigyE == UGZJNUyJCx){fIuztmPjpa = true;}
      while(rJgXdcpbTl == ZHEbEDgIbL){RzxQFeRNtt = true;}
      while(lJfmUwkuzT == lJfmUwkuzT){gdbhNeZfhh = true;}
      while(UGZJNUyJCx == UGZJNUyJCx){NJRqdQwzmG = true;}
      if(zEZNMEppjs == true){zEZNMEppjs = false;}
      if(lUNmhXESOX == true){lUNmhXESOX = false;}
      if(sWCxokiXJJ == true){sWCxokiXJJ = false;}
      if(dgZVmhjSaP == true){dgZVmhjSaP = false;}
      if(GuKFgzsmap == true){GuKFgzsmap = false;}
      if(PfueEbBbXa == true){PfueEbBbXa = false;}
      if(USfaPFuqzA == true){USfaPFuqzA = false;}
      if(mlryRxLwQp == true){mlryRxLwQp = false;}
      if(ruwStyluRK == true){ruwStyluRK = false;}
      if(fIuztmPjpa == true){fIuztmPjpa = false;}
      if(DBmZDcmwMG == true){DBmZDcmwMG = false;}
      if(PFKhhZVMgQ == true){PFKhhZVMgQ = false;}
      if(TAYoUeqrDe == true){TAYoUeqrDe = false;}
      if(hbGolpIWPQ == true){hbGolpIWPQ = false;}
      if(LohLtaxMQU == true){LohLtaxMQU = false;}
      if(QCCZHDcyEX == true){QCCZHDcyEX = false;}
      if(ltrhXmyVwr == true){ltrhXmyVwr = false;}
      if(RzxQFeRNtt == true){RzxQFeRNtt = false;}
      if(gdbhNeZfhh == true){gdbhNeZfhh = false;}
      if(NJRqdQwzmG == true){NJRqdQwzmG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PBZIDWRCKH
{ 
  void eyEZremmkf()
  { 
      bool psShnxybKq = false;
      bool HccpKUBMyP = false;
      bool gNKPYfZqbN = false;
      bool VgWnzHzWQK = false;
      bool EHKgNsPmRT = false;
      bool IobGWchDIH = false;
      bool XGzxVZFopD = false;
      bool UeunKZCcBf = false;
      bool QlYHEgEQQW = false;
      bool YuNJmxINLn = false;
      bool mawOycsnux = false;
      bool aFCcqkhqrn = false;
      bool UoXTdZRlBM = false;
      bool QnRNrpoJJb = false;
      bool mQVTuTsjSB = false;
      bool PQVWSyCcjY = false;
      bool LHmhflnokA = false;
      bool uXhQBETEYK = false;
      bool fgTzxAStts = false;
      bool mMYjPfdmmI = false;
      string fBRBEACfUj;
      string HkfwzyhAKP;
      string GaoynSMfwq;
      string qKtQTXTlCp;
      string nKOPDxUNXT;
      string FlFtkFMSMl;
      string nWjdswqOcb;
      string ewyUbwMZuq;
      string yzHbkEEAeO;
      string LBZQCQZjWG;
      string GFjwnJnkRo;
      string slXVmnOHrn;
      string qpiOPdWgSK;
      string VbDnkrOKmb;
      string QThpVYcDcN;
      string CSrhOPVVgK;
      string mGRHTQijku;
      string ZETQXXIsrp;
      string ASEFIDiVYU;
      string VsdcnKBaVE;
      if(fBRBEACfUj == GFjwnJnkRo){psShnxybKq = true;}
      else if(GFjwnJnkRo == fBRBEACfUj){mawOycsnux = true;}
      if(HkfwzyhAKP == slXVmnOHrn){HccpKUBMyP = true;}
      else if(slXVmnOHrn == HkfwzyhAKP){aFCcqkhqrn = true;}
      if(GaoynSMfwq == qpiOPdWgSK){gNKPYfZqbN = true;}
      else if(qpiOPdWgSK == GaoynSMfwq){UoXTdZRlBM = true;}
      if(qKtQTXTlCp == VbDnkrOKmb){VgWnzHzWQK = true;}
      else if(VbDnkrOKmb == qKtQTXTlCp){QnRNrpoJJb = true;}
      if(nKOPDxUNXT == QThpVYcDcN){EHKgNsPmRT = true;}
      else if(QThpVYcDcN == nKOPDxUNXT){mQVTuTsjSB = true;}
      if(FlFtkFMSMl == CSrhOPVVgK){IobGWchDIH = true;}
      else if(CSrhOPVVgK == FlFtkFMSMl){PQVWSyCcjY = true;}
      if(nWjdswqOcb == mGRHTQijku){XGzxVZFopD = true;}
      else if(mGRHTQijku == nWjdswqOcb){LHmhflnokA = true;}
      if(ewyUbwMZuq == ZETQXXIsrp){UeunKZCcBf = true;}
      if(yzHbkEEAeO == ASEFIDiVYU){QlYHEgEQQW = true;}
      if(LBZQCQZjWG == VsdcnKBaVE){YuNJmxINLn = true;}
      while(ZETQXXIsrp == ewyUbwMZuq){uXhQBETEYK = true;}
      while(ASEFIDiVYU == ASEFIDiVYU){fgTzxAStts = true;}
      while(VsdcnKBaVE == VsdcnKBaVE){mMYjPfdmmI = true;}
      if(psShnxybKq == true){psShnxybKq = false;}
      if(HccpKUBMyP == true){HccpKUBMyP = false;}
      if(gNKPYfZqbN == true){gNKPYfZqbN = false;}
      if(VgWnzHzWQK == true){VgWnzHzWQK = false;}
      if(EHKgNsPmRT == true){EHKgNsPmRT = false;}
      if(IobGWchDIH == true){IobGWchDIH = false;}
      if(XGzxVZFopD == true){XGzxVZFopD = false;}
      if(UeunKZCcBf == true){UeunKZCcBf = false;}
      if(QlYHEgEQQW == true){QlYHEgEQQW = false;}
      if(YuNJmxINLn == true){YuNJmxINLn = false;}
      if(mawOycsnux == true){mawOycsnux = false;}
      if(aFCcqkhqrn == true){aFCcqkhqrn = false;}
      if(UoXTdZRlBM == true){UoXTdZRlBM = false;}
      if(QnRNrpoJJb == true){QnRNrpoJJb = false;}
      if(mQVTuTsjSB == true){mQVTuTsjSB = false;}
      if(PQVWSyCcjY == true){PQVWSyCcjY = false;}
      if(LHmhflnokA == true){LHmhflnokA = false;}
      if(uXhQBETEYK == true){uXhQBETEYK = false;}
      if(fgTzxAStts == true){fgTzxAStts = false;}
      if(mMYjPfdmmI == true){mMYjPfdmmI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LDPLMOJVSZ
{ 
  void wQPEBtGipZ()
  { 
      bool HNoBYOsEzd = false;
      bool idIFAuVexB = false;
      bool RSEzLHmJwk = false;
      bool PCtJPGbqyS = false;
      bool nWpuTCzQuJ = false;
      bool LKDmpnJppQ = false;
      bool biIOOfiyos = false;
      bool TefdNtbIeJ = false;
      bool IVOmZEzHTb = false;
      bool xlBgqENbfn = false;
      bool SBbBpgeZYu = false;
      bool MAKfIFUVnK = false;
      bool gbdNwgdymJ = false;
      bool fAbqpHtMws = false;
      bool ZZhXOwaUYk = false;
      bool jqmVGpWNFI = false;
      bool DflOOLYTpB = false;
      bool LHYukHsFyA = false;
      bool GIZCYnNFjA = false;
      bool jfHnpsmSJD = false;
      string ctDoatYlNY;
      string dquKJzfsQw;
      string mrlakbSzTD;
      string MYqBNoIncP;
      string HmitkXOpjX;
      string OQQZOkIcEy;
      string aZRJLEAtwT;
      string qrPBnAIqoM;
      string NbPwowHQlc;
      string geidnhUZhf;
      string WUsPfWAPkO;
      string bQmrkyJVTP;
      string wjHSmLIlNG;
      string fhIJpshzPS;
      string wrfXBPqqso;
      string YyGSimMZcU;
      string NOCeisIdBq;
      string PJFBSEDiRW;
      string TRrXhgbpZC;
      string fHWuFgoBoH;
      if(ctDoatYlNY == WUsPfWAPkO){HNoBYOsEzd = true;}
      else if(WUsPfWAPkO == ctDoatYlNY){SBbBpgeZYu = true;}
      if(dquKJzfsQw == bQmrkyJVTP){idIFAuVexB = true;}
      else if(bQmrkyJVTP == dquKJzfsQw){MAKfIFUVnK = true;}
      if(mrlakbSzTD == wjHSmLIlNG){RSEzLHmJwk = true;}
      else if(wjHSmLIlNG == mrlakbSzTD){gbdNwgdymJ = true;}
      if(MYqBNoIncP == fhIJpshzPS){PCtJPGbqyS = true;}
      else if(fhIJpshzPS == MYqBNoIncP){fAbqpHtMws = true;}
      if(HmitkXOpjX == wrfXBPqqso){nWpuTCzQuJ = true;}
      else if(wrfXBPqqso == HmitkXOpjX){ZZhXOwaUYk = true;}
      if(OQQZOkIcEy == YyGSimMZcU){LKDmpnJppQ = true;}
      else if(YyGSimMZcU == OQQZOkIcEy){jqmVGpWNFI = true;}
      if(aZRJLEAtwT == NOCeisIdBq){biIOOfiyos = true;}
      else if(NOCeisIdBq == aZRJLEAtwT){DflOOLYTpB = true;}
      if(qrPBnAIqoM == PJFBSEDiRW){TefdNtbIeJ = true;}
      if(NbPwowHQlc == TRrXhgbpZC){IVOmZEzHTb = true;}
      if(geidnhUZhf == fHWuFgoBoH){xlBgqENbfn = true;}
      while(PJFBSEDiRW == qrPBnAIqoM){LHYukHsFyA = true;}
      while(TRrXhgbpZC == TRrXhgbpZC){GIZCYnNFjA = true;}
      while(fHWuFgoBoH == fHWuFgoBoH){jfHnpsmSJD = true;}
      if(HNoBYOsEzd == true){HNoBYOsEzd = false;}
      if(idIFAuVexB == true){idIFAuVexB = false;}
      if(RSEzLHmJwk == true){RSEzLHmJwk = false;}
      if(PCtJPGbqyS == true){PCtJPGbqyS = false;}
      if(nWpuTCzQuJ == true){nWpuTCzQuJ = false;}
      if(LKDmpnJppQ == true){LKDmpnJppQ = false;}
      if(biIOOfiyos == true){biIOOfiyos = false;}
      if(TefdNtbIeJ == true){TefdNtbIeJ = false;}
      if(IVOmZEzHTb == true){IVOmZEzHTb = false;}
      if(xlBgqENbfn == true){xlBgqENbfn = false;}
      if(SBbBpgeZYu == true){SBbBpgeZYu = false;}
      if(MAKfIFUVnK == true){MAKfIFUVnK = false;}
      if(gbdNwgdymJ == true){gbdNwgdymJ = false;}
      if(fAbqpHtMws == true){fAbqpHtMws = false;}
      if(ZZhXOwaUYk == true){ZZhXOwaUYk = false;}
      if(jqmVGpWNFI == true){jqmVGpWNFI = false;}
      if(DflOOLYTpB == true){DflOOLYTpB = false;}
      if(LHYukHsFyA == true){LHYukHsFyA = false;}
      if(GIZCYnNFjA == true){GIZCYnNFjA = false;}
      if(jfHnpsmSJD == true){jfHnpsmSJD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MZJKMLMOJZ
{ 
  void iMKupIHNeo()
  { 
      bool IaZtQKIhuz = false;
      bool hqaZExLlgF = false;
      bool xhAMmFsMiH = false;
      bool oDqkaYsjCm = false;
      bool jYpusbClJB = false;
      bool zmoWAZaMHK = false;
      bool QwzmKeAoze = false;
      bool DaisVXrETK = false;
      bool DHCgIBNUkB = false;
      bool ygcrVmZCkO = false;
      bool bMmexXEuBb = false;
      bool hVswGJsReI = false;
      bool QfExfWyqWh = false;
      bool xoSFhqTWij = false;
      bool xRSISbmfkM = false;
      bool tIXcxwHozZ = false;
      bool ZMXTerDmNP = false;
      bool oVhuKyMudD = false;
      bool iRFKnoQpHl = false;
      bool ieXIJktzda = false;
      string fFtrGykNkC;
      string KHcNBCdcLT;
      string WPFVKktRYY;
      string LNqgwuBPJY;
      string MRbXExAMad;
      string LoLyfQAXhV;
      string DToMpwQuQG;
      string ANTmGFmgRN;
      string jhquNWCrBf;
      string uchmUscPhH;
      string fFuUcxVXra;
      string cSFUlVbsyT;
      string sYtkKXffSN;
      string bXzJgemVSQ;
      string AeAaCbWMBz;
      string QiQNOGKJJE;
      string QpFdyETwmG;
      string iGahSOYTii;
      string ASdSxsHkua;
      string TcMNzKYVbx;
      if(fFtrGykNkC == fFuUcxVXra){IaZtQKIhuz = true;}
      else if(fFuUcxVXra == fFtrGykNkC){bMmexXEuBb = true;}
      if(KHcNBCdcLT == cSFUlVbsyT){hqaZExLlgF = true;}
      else if(cSFUlVbsyT == KHcNBCdcLT){hVswGJsReI = true;}
      if(WPFVKktRYY == sYtkKXffSN){xhAMmFsMiH = true;}
      else if(sYtkKXffSN == WPFVKktRYY){QfExfWyqWh = true;}
      if(LNqgwuBPJY == bXzJgemVSQ){oDqkaYsjCm = true;}
      else if(bXzJgemVSQ == LNqgwuBPJY){xoSFhqTWij = true;}
      if(MRbXExAMad == AeAaCbWMBz){jYpusbClJB = true;}
      else if(AeAaCbWMBz == MRbXExAMad){xRSISbmfkM = true;}
      if(LoLyfQAXhV == QiQNOGKJJE){zmoWAZaMHK = true;}
      else if(QiQNOGKJJE == LoLyfQAXhV){tIXcxwHozZ = true;}
      if(DToMpwQuQG == QpFdyETwmG){QwzmKeAoze = true;}
      else if(QpFdyETwmG == DToMpwQuQG){ZMXTerDmNP = true;}
      if(ANTmGFmgRN == iGahSOYTii){DaisVXrETK = true;}
      if(jhquNWCrBf == ASdSxsHkua){DHCgIBNUkB = true;}
      if(uchmUscPhH == TcMNzKYVbx){ygcrVmZCkO = true;}
      while(iGahSOYTii == ANTmGFmgRN){oVhuKyMudD = true;}
      while(ASdSxsHkua == ASdSxsHkua){iRFKnoQpHl = true;}
      while(TcMNzKYVbx == TcMNzKYVbx){ieXIJktzda = true;}
      if(IaZtQKIhuz == true){IaZtQKIhuz = false;}
      if(hqaZExLlgF == true){hqaZExLlgF = false;}
      if(xhAMmFsMiH == true){xhAMmFsMiH = false;}
      if(oDqkaYsjCm == true){oDqkaYsjCm = false;}
      if(jYpusbClJB == true){jYpusbClJB = false;}
      if(zmoWAZaMHK == true){zmoWAZaMHK = false;}
      if(QwzmKeAoze == true){QwzmKeAoze = false;}
      if(DaisVXrETK == true){DaisVXrETK = false;}
      if(DHCgIBNUkB == true){DHCgIBNUkB = false;}
      if(ygcrVmZCkO == true){ygcrVmZCkO = false;}
      if(bMmexXEuBb == true){bMmexXEuBb = false;}
      if(hVswGJsReI == true){hVswGJsReI = false;}
      if(QfExfWyqWh == true){QfExfWyqWh = false;}
      if(xoSFhqTWij == true){xoSFhqTWij = false;}
      if(xRSISbmfkM == true){xRSISbmfkM = false;}
      if(tIXcxwHozZ == true){tIXcxwHozZ = false;}
      if(ZMXTerDmNP == true){ZMXTerDmNP = false;}
      if(oVhuKyMudD == true){oVhuKyMudD = false;}
      if(iRFKnoQpHl == true){iRFKnoQpHl = false;}
      if(ieXIJktzda == true){ieXIJktzda = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DFEKDAXAUQ
{ 
  void NHajTUcxqj()
  { 
      bool XoWkzNaRfx = false;
      bool GwMDYWyMzB = false;
      bool SubmmzSFgH = false;
      bool LGGLNIRfVE = false;
      bool WFEUEhAbym = false;
      bool TlJlKcMjxz = false;
      bool tUkXlApAoP = false;
      bool FSptdNpGiE = false;
      bool zqHsnZxTBk = false;
      bool uhhVJCTgiE = false;
      bool rzlhhAuOHw = false;
      bool mFAsADNqjL = false;
      bool DVyETXjUkb = false;
      bool tIWeLzEYLm = false;
      bool diMFxpgoVF = false;
      bool nbxWBWBgOK = false;
      bool PaceBdhVgA = false;
      bool znfwhUJsGd = false;
      bool puyenRLAdo = false;
      bool yWKBWDFgDT = false;
      string WPYfVBXNoa;
      string gpubUBhbVR;
      string WqnWLptBsd;
      string EoeWXDKVTx;
      string EtjjsUxQyu;
      string ippIfebCUe;
      string GWTKWqKYDR;
      string qLHYMcHEdp;
      string scCxuOyVqr;
      string bIAopgZZNB;
      string JXNfEXhQwC;
      string XWXelcUVPH;
      string rnhKphKSie;
      string CgqbfUPVsW;
      string ggZnUEkVCM;
      string MEKFIUpCpV;
      string MOhRApfuyR;
      string MycrZKOtpl;
      string xoQVRyWkSK;
      string dNfWKRzInd;
      if(WPYfVBXNoa == JXNfEXhQwC){XoWkzNaRfx = true;}
      else if(JXNfEXhQwC == WPYfVBXNoa){rzlhhAuOHw = true;}
      if(gpubUBhbVR == XWXelcUVPH){GwMDYWyMzB = true;}
      else if(XWXelcUVPH == gpubUBhbVR){mFAsADNqjL = true;}
      if(WqnWLptBsd == rnhKphKSie){SubmmzSFgH = true;}
      else if(rnhKphKSie == WqnWLptBsd){DVyETXjUkb = true;}
      if(EoeWXDKVTx == CgqbfUPVsW){LGGLNIRfVE = true;}
      else if(CgqbfUPVsW == EoeWXDKVTx){tIWeLzEYLm = true;}
      if(EtjjsUxQyu == ggZnUEkVCM){WFEUEhAbym = true;}
      else if(ggZnUEkVCM == EtjjsUxQyu){diMFxpgoVF = true;}
      if(ippIfebCUe == MEKFIUpCpV){TlJlKcMjxz = true;}
      else if(MEKFIUpCpV == ippIfebCUe){nbxWBWBgOK = true;}
      if(GWTKWqKYDR == MOhRApfuyR){tUkXlApAoP = true;}
      else if(MOhRApfuyR == GWTKWqKYDR){PaceBdhVgA = true;}
      if(qLHYMcHEdp == MycrZKOtpl){FSptdNpGiE = true;}
      if(scCxuOyVqr == xoQVRyWkSK){zqHsnZxTBk = true;}
      if(bIAopgZZNB == dNfWKRzInd){uhhVJCTgiE = true;}
      while(MycrZKOtpl == qLHYMcHEdp){znfwhUJsGd = true;}
      while(xoQVRyWkSK == xoQVRyWkSK){puyenRLAdo = true;}
      while(dNfWKRzInd == dNfWKRzInd){yWKBWDFgDT = true;}
      if(XoWkzNaRfx == true){XoWkzNaRfx = false;}
      if(GwMDYWyMzB == true){GwMDYWyMzB = false;}
      if(SubmmzSFgH == true){SubmmzSFgH = false;}
      if(LGGLNIRfVE == true){LGGLNIRfVE = false;}
      if(WFEUEhAbym == true){WFEUEhAbym = false;}
      if(TlJlKcMjxz == true){TlJlKcMjxz = false;}
      if(tUkXlApAoP == true){tUkXlApAoP = false;}
      if(FSptdNpGiE == true){FSptdNpGiE = false;}
      if(zqHsnZxTBk == true){zqHsnZxTBk = false;}
      if(uhhVJCTgiE == true){uhhVJCTgiE = false;}
      if(rzlhhAuOHw == true){rzlhhAuOHw = false;}
      if(mFAsADNqjL == true){mFAsADNqjL = false;}
      if(DVyETXjUkb == true){DVyETXjUkb = false;}
      if(tIWeLzEYLm == true){tIWeLzEYLm = false;}
      if(diMFxpgoVF == true){diMFxpgoVF = false;}
      if(nbxWBWBgOK == true){nbxWBWBgOK = false;}
      if(PaceBdhVgA == true){PaceBdhVgA = false;}
      if(znfwhUJsGd == true){znfwhUJsGd = false;}
      if(puyenRLAdo == true){puyenRLAdo = false;}
      if(yWKBWDFgDT == true){yWKBWDFgDT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VZCMZYGKQK
{ 
  void AYNLcwLSgj()
  { 
      bool EtzWYXISID = false;
      bool eglSAubhEq = false;
      bool HXVHxSBOrq = false;
      bool rKSgGaPiJM = false;
      bool XzTWtCtDDd = false;
      bool eByhBfYrZG = false;
      bool WtaRLTOFMZ = false;
      bool esXrSHDzMt = false;
      bool YxLNMpMjeZ = false;
      bool CXJDpdXCLa = false;
      bool nnqcyldGPs = false;
      bool cZeegYhNEU = false;
      bool GdamWHiTCo = false;
      bool jAmkFjGhOa = false;
      bool LGUkwcrdVQ = false;
      bool uKypUJNDFq = false;
      bool CJEZJbltZx = false;
      bool RzycIAJopt = false;
      bool OFxksYCwQu = false;
      bool VCbWYCCtbT = false;
      string nPwriQTLWA;
      string tDNTSaVUou;
      string DUwcdPyyGc;
      string eplqfKQsPz;
      string rZfPMOnnCu;
      string jyPYLSSTNT;
      string RVEtUDRWmI;
      string KbFpDdofPO;
      string bJuLrgaMfN;
      string qwfugVUluI;
      string xRBtkHrZVg;
      string dlEyqIZsBm;
      string cEqYQNwJIg;
      string IDkGRKIBaj;
      string oBqyiFrgDY;
      string wbjHfrZbdW;
      string KhQnYZBxgg;
      string zYSQybNrpK;
      string VPFijgScaZ;
      string jfWDYGjCZJ;
      if(nPwriQTLWA == xRBtkHrZVg){EtzWYXISID = true;}
      else if(xRBtkHrZVg == nPwriQTLWA){nnqcyldGPs = true;}
      if(tDNTSaVUou == dlEyqIZsBm){eglSAubhEq = true;}
      else if(dlEyqIZsBm == tDNTSaVUou){cZeegYhNEU = true;}
      if(DUwcdPyyGc == cEqYQNwJIg){HXVHxSBOrq = true;}
      else if(cEqYQNwJIg == DUwcdPyyGc){GdamWHiTCo = true;}
      if(eplqfKQsPz == IDkGRKIBaj){rKSgGaPiJM = true;}
      else if(IDkGRKIBaj == eplqfKQsPz){jAmkFjGhOa = true;}
      if(rZfPMOnnCu == oBqyiFrgDY){XzTWtCtDDd = true;}
      else if(oBqyiFrgDY == rZfPMOnnCu){LGUkwcrdVQ = true;}
      if(jyPYLSSTNT == wbjHfrZbdW){eByhBfYrZG = true;}
      else if(wbjHfrZbdW == jyPYLSSTNT){uKypUJNDFq = true;}
      if(RVEtUDRWmI == KhQnYZBxgg){WtaRLTOFMZ = true;}
      else if(KhQnYZBxgg == RVEtUDRWmI){CJEZJbltZx = true;}
      if(KbFpDdofPO == zYSQybNrpK){esXrSHDzMt = true;}
      if(bJuLrgaMfN == VPFijgScaZ){YxLNMpMjeZ = true;}
      if(qwfugVUluI == jfWDYGjCZJ){CXJDpdXCLa = true;}
      while(zYSQybNrpK == KbFpDdofPO){RzycIAJopt = true;}
      while(VPFijgScaZ == VPFijgScaZ){OFxksYCwQu = true;}
      while(jfWDYGjCZJ == jfWDYGjCZJ){VCbWYCCtbT = true;}
      if(EtzWYXISID == true){EtzWYXISID = false;}
      if(eglSAubhEq == true){eglSAubhEq = false;}
      if(HXVHxSBOrq == true){HXVHxSBOrq = false;}
      if(rKSgGaPiJM == true){rKSgGaPiJM = false;}
      if(XzTWtCtDDd == true){XzTWtCtDDd = false;}
      if(eByhBfYrZG == true){eByhBfYrZG = false;}
      if(WtaRLTOFMZ == true){WtaRLTOFMZ = false;}
      if(esXrSHDzMt == true){esXrSHDzMt = false;}
      if(YxLNMpMjeZ == true){YxLNMpMjeZ = false;}
      if(CXJDpdXCLa == true){CXJDpdXCLa = false;}
      if(nnqcyldGPs == true){nnqcyldGPs = false;}
      if(cZeegYhNEU == true){cZeegYhNEU = false;}
      if(GdamWHiTCo == true){GdamWHiTCo = false;}
      if(jAmkFjGhOa == true){jAmkFjGhOa = false;}
      if(LGUkwcrdVQ == true){LGUkwcrdVQ = false;}
      if(uKypUJNDFq == true){uKypUJNDFq = false;}
      if(CJEZJbltZx == true){CJEZJbltZx = false;}
      if(RzycIAJopt == true){RzycIAJopt = false;}
      if(OFxksYCwQu == true){OFxksYCwQu = false;}
      if(VCbWYCCtbT == true){VCbWYCCtbT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WNRPKDGLWC
{ 
  void eWJUAoikRi()
  { 
      bool psaCwqBWXa = false;
      bool FaXSUpmNja = false;
      bool PQPJubDbeM = false;
      bool GXlMdmteqF = false;
      bool rcaGtNlsGH = false;
      bool QLyOAYcRHT = false;
      bool mZqLTgoLng = false;
      bool uHWehloJPh = false;
      bool pKVXutZWLF = false;
      bool JcXWSSlPlM = false;
      bool XZEYLJoTgO = false;
      bool iTCYdbDSPZ = false;
      bool GRziWSizLO = false;
      bool zZWCJPGwLl = false;
      bool FGpwWpZysp = false;
      bool OTzMFGZVBr = false;
      bool ZoHROIxzPN = false;
      bool UHGcTAbDLg = false;
      bool rkGVAfZJwC = false;
      bool okuTMPzXhN = false;
      string jUJJkKuGQj;
      string hbwCXQhtGZ;
      string yixVthnRZE;
      string hbIgwjPVOC;
      string zPyfTADRDY;
      string dUbJCAXmOD;
      string VdfMCGTPGn;
      string AMeEZhkRBs;
      string dWOBaNzydw;
      string McGLgVikcN;
      string gnLOYRoXjT;
      string PFkVYyOeln;
      string GUlJbXGTWD;
      string yznnLpLzbI;
      string XaOKgGqkli;
      string GEznGLBBmB;
      string LUBfUPQxJi;
      string lPCcPfGacU;
      string gVhmwtAzgz;
      string nJLaxDZhoQ;
      if(jUJJkKuGQj == gnLOYRoXjT){psaCwqBWXa = true;}
      else if(gnLOYRoXjT == jUJJkKuGQj){XZEYLJoTgO = true;}
      if(hbwCXQhtGZ == PFkVYyOeln){FaXSUpmNja = true;}
      else if(PFkVYyOeln == hbwCXQhtGZ){iTCYdbDSPZ = true;}
      if(yixVthnRZE == GUlJbXGTWD){PQPJubDbeM = true;}
      else if(GUlJbXGTWD == yixVthnRZE){GRziWSizLO = true;}
      if(hbIgwjPVOC == yznnLpLzbI){GXlMdmteqF = true;}
      else if(yznnLpLzbI == hbIgwjPVOC){zZWCJPGwLl = true;}
      if(zPyfTADRDY == XaOKgGqkli){rcaGtNlsGH = true;}
      else if(XaOKgGqkli == zPyfTADRDY){FGpwWpZysp = true;}
      if(dUbJCAXmOD == GEznGLBBmB){QLyOAYcRHT = true;}
      else if(GEznGLBBmB == dUbJCAXmOD){OTzMFGZVBr = true;}
      if(VdfMCGTPGn == LUBfUPQxJi){mZqLTgoLng = true;}
      else if(LUBfUPQxJi == VdfMCGTPGn){ZoHROIxzPN = true;}
      if(AMeEZhkRBs == lPCcPfGacU){uHWehloJPh = true;}
      if(dWOBaNzydw == gVhmwtAzgz){pKVXutZWLF = true;}
      if(McGLgVikcN == nJLaxDZhoQ){JcXWSSlPlM = true;}
      while(lPCcPfGacU == AMeEZhkRBs){UHGcTAbDLg = true;}
      while(gVhmwtAzgz == gVhmwtAzgz){rkGVAfZJwC = true;}
      while(nJLaxDZhoQ == nJLaxDZhoQ){okuTMPzXhN = true;}
      if(psaCwqBWXa == true){psaCwqBWXa = false;}
      if(FaXSUpmNja == true){FaXSUpmNja = false;}
      if(PQPJubDbeM == true){PQPJubDbeM = false;}
      if(GXlMdmteqF == true){GXlMdmteqF = false;}
      if(rcaGtNlsGH == true){rcaGtNlsGH = false;}
      if(QLyOAYcRHT == true){QLyOAYcRHT = false;}
      if(mZqLTgoLng == true){mZqLTgoLng = false;}
      if(uHWehloJPh == true){uHWehloJPh = false;}
      if(pKVXutZWLF == true){pKVXutZWLF = false;}
      if(JcXWSSlPlM == true){JcXWSSlPlM = false;}
      if(XZEYLJoTgO == true){XZEYLJoTgO = false;}
      if(iTCYdbDSPZ == true){iTCYdbDSPZ = false;}
      if(GRziWSizLO == true){GRziWSizLO = false;}
      if(zZWCJPGwLl == true){zZWCJPGwLl = false;}
      if(FGpwWpZysp == true){FGpwWpZysp = false;}
      if(OTzMFGZVBr == true){OTzMFGZVBr = false;}
      if(ZoHROIxzPN == true){ZoHROIxzPN = false;}
      if(UHGcTAbDLg == true){UHGcTAbDLg = false;}
      if(rkGVAfZJwC == true){rkGVAfZJwC = false;}
      if(okuTMPzXhN == true){okuTMPzXhN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BGJJHXQXME
{ 
  void aCTMalLzIO()
  { 
      bool WRtWQfxuTz = false;
      bool wsQdkWayWI = false;
      bool bdOPOqKTgg = false;
      bool jofKYhGGLC = false;
      bool RFnHneNpYy = false;
      bool XHMzkrCeHY = false;
      bool UcOmPGNFEC = false;
      bool QUmTqWpHai = false;
      bool dUtiIbbfYf = false;
      bool ebylgnqArh = false;
      bool RHkWhDUsIO = false;
      bool BuEXuAieem = false;
      bool dggXWoVAmC = false;
      bool foOsRViXBE = false;
      bool GiXJdjXZqg = false;
      bool FLVEDjZNzr = false;
      bool hTFFiMfKGY = false;
      bool RKdZfuIXsm = false;
      bool RuIGxTSKog = false;
      bool uVXIWmdRaR = false;
      string jrGZiaEgAP;
      string ySKjwmAGeI;
      string eIHYbcOIol;
      string iCQuxnpALn;
      string epKPLlRqkU;
      string VmfbBbkhyF;
      string MuqNfuCOlH;
      string wztpcnxqNp;
      string KXWTQwWntV;
      string CICGbjywjP;
      string jDEdYVrozN;
      string dtTHuoXXxj;
      string YNUPEnwnOs;
      string oAHyGHSstt;
      string DhofqInuKl;
      string LazzpVhnYk;
      string YEaFXdlVAn;
      string VedDfqYnXu;
      string ABcbhOBHHk;
      string YdTJVzGjIN;
      if(jrGZiaEgAP == jDEdYVrozN){WRtWQfxuTz = true;}
      else if(jDEdYVrozN == jrGZiaEgAP){RHkWhDUsIO = true;}
      if(ySKjwmAGeI == dtTHuoXXxj){wsQdkWayWI = true;}
      else if(dtTHuoXXxj == ySKjwmAGeI){BuEXuAieem = true;}
      if(eIHYbcOIol == YNUPEnwnOs){bdOPOqKTgg = true;}
      else if(YNUPEnwnOs == eIHYbcOIol){dggXWoVAmC = true;}
      if(iCQuxnpALn == oAHyGHSstt){jofKYhGGLC = true;}
      else if(oAHyGHSstt == iCQuxnpALn){foOsRViXBE = true;}
      if(epKPLlRqkU == DhofqInuKl){RFnHneNpYy = true;}
      else if(DhofqInuKl == epKPLlRqkU){GiXJdjXZqg = true;}
      if(VmfbBbkhyF == LazzpVhnYk){XHMzkrCeHY = true;}
      else if(LazzpVhnYk == VmfbBbkhyF){FLVEDjZNzr = true;}
      if(MuqNfuCOlH == YEaFXdlVAn){UcOmPGNFEC = true;}
      else if(YEaFXdlVAn == MuqNfuCOlH){hTFFiMfKGY = true;}
      if(wztpcnxqNp == VedDfqYnXu){QUmTqWpHai = true;}
      if(KXWTQwWntV == ABcbhOBHHk){dUtiIbbfYf = true;}
      if(CICGbjywjP == YdTJVzGjIN){ebylgnqArh = true;}
      while(VedDfqYnXu == wztpcnxqNp){RKdZfuIXsm = true;}
      while(ABcbhOBHHk == ABcbhOBHHk){RuIGxTSKog = true;}
      while(YdTJVzGjIN == YdTJVzGjIN){uVXIWmdRaR = true;}
      if(WRtWQfxuTz == true){WRtWQfxuTz = false;}
      if(wsQdkWayWI == true){wsQdkWayWI = false;}
      if(bdOPOqKTgg == true){bdOPOqKTgg = false;}
      if(jofKYhGGLC == true){jofKYhGGLC = false;}
      if(RFnHneNpYy == true){RFnHneNpYy = false;}
      if(XHMzkrCeHY == true){XHMzkrCeHY = false;}
      if(UcOmPGNFEC == true){UcOmPGNFEC = false;}
      if(QUmTqWpHai == true){QUmTqWpHai = false;}
      if(dUtiIbbfYf == true){dUtiIbbfYf = false;}
      if(ebylgnqArh == true){ebylgnqArh = false;}
      if(RHkWhDUsIO == true){RHkWhDUsIO = false;}
      if(BuEXuAieem == true){BuEXuAieem = false;}
      if(dggXWoVAmC == true){dggXWoVAmC = false;}
      if(foOsRViXBE == true){foOsRViXBE = false;}
      if(GiXJdjXZqg == true){GiXJdjXZqg = false;}
      if(FLVEDjZNzr == true){FLVEDjZNzr = false;}
      if(hTFFiMfKGY == true){hTFFiMfKGY = false;}
      if(RKdZfuIXsm == true){RKdZfuIXsm = false;}
      if(RuIGxTSKog == true){RuIGxTSKog = false;}
      if(uVXIWmdRaR == true){uVXIWmdRaR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VWYJBUXFEZ
{ 
  void LMnNWigYLr()
  { 
      bool zkGbtFDVYz = false;
      bool BZqarMyEAf = false;
      bool XQHRkqqYop = false;
      bool YKtPcbXOnR = false;
      bool gTTzOUPklW = false;
      bool qAamGicnpD = false;
      bool OdfiZqeaxQ = false;
      bool njQiyEwIDP = false;
      bool aFmRzXiHJt = false;
      bool yiYkCDmkYX = false;
      bool pnnUhHjqnC = false;
      bool lUkZbIpOiB = false;
      bool HXRDREKeft = false;
      bool QLifZlRRiq = false;
      bool nqSHHcyyIs = false;
      bool NYBWPRWjDc = false;
      bool wELskalFAo = false;
      bool qXeqNPFKwo = false;
      bool GMWlgrJLPI = false;
      bool PgOGujfYVf = false;
      string mCRGPDeEbL;
      string IHYlHJkRoK;
      string ILXHqlDFap;
      string cdRkOzhpyg;
      string BXgCeOWryi;
      string EIWNsbeJOc;
      string AZdkheomWH;
      string atTHIkeUbc;
      string PLGqkUHEqm;
      string UXaUgbsuUA;
      string YiUpHKnOEH;
      string wKhlMnSmAN;
      string WkwjmDSyaf;
      string qjAbDgqPia;
      string fszipJpoHr;
      string JGtGcmljDE;
      string qpmXQMKFhf;
      string xDDYgdlMsc;
      string MdqiWjosyQ;
      string tGLdjpFbSd;
      if(mCRGPDeEbL == YiUpHKnOEH){zkGbtFDVYz = true;}
      else if(YiUpHKnOEH == mCRGPDeEbL){pnnUhHjqnC = true;}
      if(IHYlHJkRoK == wKhlMnSmAN){BZqarMyEAf = true;}
      else if(wKhlMnSmAN == IHYlHJkRoK){lUkZbIpOiB = true;}
      if(ILXHqlDFap == WkwjmDSyaf){XQHRkqqYop = true;}
      else if(WkwjmDSyaf == ILXHqlDFap){HXRDREKeft = true;}
      if(cdRkOzhpyg == qjAbDgqPia){YKtPcbXOnR = true;}
      else if(qjAbDgqPia == cdRkOzhpyg){QLifZlRRiq = true;}
      if(BXgCeOWryi == fszipJpoHr){gTTzOUPklW = true;}
      else if(fszipJpoHr == BXgCeOWryi){nqSHHcyyIs = true;}
      if(EIWNsbeJOc == JGtGcmljDE){qAamGicnpD = true;}
      else if(JGtGcmljDE == EIWNsbeJOc){NYBWPRWjDc = true;}
      if(AZdkheomWH == qpmXQMKFhf){OdfiZqeaxQ = true;}
      else if(qpmXQMKFhf == AZdkheomWH){wELskalFAo = true;}
      if(atTHIkeUbc == xDDYgdlMsc){njQiyEwIDP = true;}
      if(PLGqkUHEqm == MdqiWjosyQ){aFmRzXiHJt = true;}
      if(UXaUgbsuUA == tGLdjpFbSd){yiYkCDmkYX = true;}
      while(xDDYgdlMsc == atTHIkeUbc){qXeqNPFKwo = true;}
      while(MdqiWjosyQ == MdqiWjosyQ){GMWlgrJLPI = true;}
      while(tGLdjpFbSd == tGLdjpFbSd){PgOGujfYVf = true;}
      if(zkGbtFDVYz == true){zkGbtFDVYz = false;}
      if(BZqarMyEAf == true){BZqarMyEAf = false;}
      if(XQHRkqqYop == true){XQHRkqqYop = false;}
      if(YKtPcbXOnR == true){YKtPcbXOnR = false;}
      if(gTTzOUPklW == true){gTTzOUPklW = false;}
      if(qAamGicnpD == true){qAamGicnpD = false;}
      if(OdfiZqeaxQ == true){OdfiZqeaxQ = false;}
      if(njQiyEwIDP == true){njQiyEwIDP = false;}
      if(aFmRzXiHJt == true){aFmRzXiHJt = false;}
      if(yiYkCDmkYX == true){yiYkCDmkYX = false;}
      if(pnnUhHjqnC == true){pnnUhHjqnC = false;}
      if(lUkZbIpOiB == true){lUkZbIpOiB = false;}
      if(HXRDREKeft == true){HXRDREKeft = false;}
      if(QLifZlRRiq == true){QLifZlRRiq = false;}
      if(nqSHHcyyIs == true){nqSHHcyyIs = false;}
      if(NYBWPRWjDc == true){NYBWPRWjDc = false;}
      if(wELskalFAo == true){wELskalFAo = false;}
      if(qXeqNPFKwo == true){qXeqNPFKwo = false;}
      if(GMWlgrJLPI == true){GMWlgrJLPI = false;}
      if(PgOGujfYVf == true){PgOGujfYVf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXJAPKDQFB
{ 
  void GRlwRshXgt()
  { 
      bool ZnTORlbSfO = false;
      bool YJqhThfKgW = false;
      bool QtNXEwKIbJ = false;
      bool SNWaVATjhR = false;
      bool lQDzdwslmt = false;
      bool GuzhbeZuKV = false;
      bool bTqWuLlQMS = false;
      bool OubOjzqOsH = false;
      bool CXUgCWOozp = false;
      bool ZXZMpSZfDS = false;
      bool JcZUfLTjxc = false;
      bool mLCCSEzKUX = false;
      bool wxQVsqUPYR = false;
      bool YLKaxZxABp = false;
      bool DdqWDNUXsk = false;
      bool TPLeVMLEan = false;
      bool pDLfDbBaEs = false;
      bool GzIdURFtRe = false;
      bool VwVmyJzeFk = false;
      bool NsYMzzSLSb = false;
      string GQuErzxteL;
      string jXzFbFJZzL;
      string GOaiJuDumZ;
      string bPqBriGlYX;
      string wdfZAJBjUK;
      string ZFlUTqpMuw;
      string uCHEjTgyMr;
      string yWBbOciAhz;
      string tSZbAVcVgB;
      string stpbbsWaof;
      string cCWbMCEKFq;
      string IodwCcceDN;
      string qKRLzEgYzU;
      string FHLCVquxPy;
      string RRQprDPtZz;
      string QqXbnSkKcI;
      string UeLkkAdbaK;
      string gePEwZsbTu;
      string nmzADOjiNC;
      string GkUHclGfEr;
      if(GQuErzxteL == cCWbMCEKFq){ZnTORlbSfO = true;}
      else if(cCWbMCEKFq == GQuErzxteL){JcZUfLTjxc = true;}
      if(jXzFbFJZzL == IodwCcceDN){YJqhThfKgW = true;}
      else if(IodwCcceDN == jXzFbFJZzL){mLCCSEzKUX = true;}
      if(GOaiJuDumZ == qKRLzEgYzU){QtNXEwKIbJ = true;}
      else if(qKRLzEgYzU == GOaiJuDumZ){wxQVsqUPYR = true;}
      if(bPqBriGlYX == FHLCVquxPy){SNWaVATjhR = true;}
      else if(FHLCVquxPy == bPqBriGlYX){YLKaxZxABp = true;}
      if(wdfZAJBjUK == RRQprDPtZz){lQDzdwslmt = true;}
      else if(RRQprDPtZz == wdfZAJBjUK){DdqWDNUXsk = true;}
      if(ZFlUTqpMuw == QqXbnSkKcI){GuzhbeZuKV = true;}
      else if(QqXbnSkKcI == ZFlUTqpMuw){TPLeVMLEan = true;}
      if(uCHEjTgyMr == UeLkkAdbaK){bTqWuLlQMS = true;}
      else if(UeLkkAdbaK == uCHEjTgyMr){pDLfDbBaEs = true;}
      if(yWBbOciAhz == gePEwZsbTu){OubOjzqOsH = true;}
      if(tSZbAVcVgB == nmzADOjiNC){CXUgCWOozp = true;}
      if(stpbbsWaof == GkUHclGfEr){ZXZMpSZfDS = true;}
      while(gePEwZsbTu == yWBbOciAhz){GzIdURFtRe = true;}
      while(nmzADOjiNC == nmzADOjiNC){VwVmyJzeFk = true;}
      while(GkUHclGfEr == GkUHclGfEr){NsYMzzSLSb = true;}
      if(ZnTORlbSfO == true){ZnTORlbSfO = false;}
      if(YJqhThfKgW == true){YJqhThfKgW = false;}
      if(QtNXEwKIbJ == true){QtNXEwKIbJ = false;}
      if(SNWaVATjhR == true){SNWaVATjhR = false;}
      if(lQDzdwslmt == true){lQDzdwslmt = false;}
      if(GuzhbeZuKV == true){GuzhbeZuKV = false;}
      if(bTqWuLlQMS == true){bTqWuLlQMS = false;}
      if(OubOjzqOsH == true){OubOjzqOsH = false;}
      if(CXUgCWOozp == true){CXUgCWOozp = false;}
      if(ZXZMpSZfDS == true){ZXZMpSZfDS = false;}
      if(JcZUfLTjxc == true){JcZUfLTjxc = false;}
      if(mLCCSEzKUX == true){mLCCSEzKUX = false;}
      if(wxQVsqUPYR == true){wxQVsqUPYR = false;}
      if(YLKaxZxABp == true){YLKaxZxABp = false;}
      if(DdqWDNUXsk == true){DdqWDNUXsk = false;}
      if(TPLeVMLEan == true){TPLeVMLEan = false;}
      if(pDLfDbBaEs == true){pDLfDbBaEs = false;}
      if(GzIdURFtRe == true){GzIdURFtRe = false;}
      if(VwVmyJzeFk == true){VwVmyJzeFk = false;}
      if(NsYMzzSLSb == true){NsYMzzSLSb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JIYJSIHJSY
{ 
  void kVplWCEkMu()
  { 
      bool jCogednRji = false;
      bool OlZPDfZRhM = false;
      bool msBcajqabD = false;
      bool SHAylAyZHZ = false;
      bool FjjLisjUIc = false;
      bool UkKBIpBMFt = false;
      bool mMogPHladC = false;
      bool gAJHHCJosg = false;
      bool AWSyhgwyou = false;
      bool zkTNmrtCub = false;
      bool HIpGuTbDtG = false;
      bool fMSYsQtqyh = false;
      bool LmkhDufuUP = false;
      bool HGsRYqfMCN = false;
      bool FrEiPlSuUV = false;
      bool xDDNPUXICz = false;
      bool mfidzYSBzB = false;
      bool kgnjcSiCSQ = false;
      bool ckayRDDfBE = false;
      bool TWJDaYJZjp = false;
      string JWxGBpqKwf;
      string swMzUVKLIs;
      string OxwRKqnPeh;
      string CsncpnZAnA;
      string eMdlhCVJmE;
      string gzXLeMaewK;
      string CaeNczIiJg;
      string wJXIOCTKiH;
      string UdcZADVcyd;
      string NtEcxDgPIi;
      string tmAGIXaOxb;
      string sPwnoXyFNZ;
      string cfkfTBEtLK;
      string VECAMhdWRc;
      string bGeVkxyQnY;
      string FbChFOBUlG;
      string TgDlGoNuaH;
      string tamkyWAPtV;
      string DnGlEtBTty;
      string fJjLIuDsOw;
      if(JWxGBpqKwf == tmAGIXaOxb){jCogednRji = true;}
      else if(tmAGIXaOxb == JWxGBpqKwf){HIpGuTbDtG = true;}
      if(swMzUVKLIs == sPwnoXyFNZ){OlZPDfZRhM = true;}
      else if(sPwnoXyFNZ == swMzUVKLIs){fMSYsQtqyh = true;}
      if(OxwRKqnPeh == cfkfTBEtLK){msBcajqabD = true;}
      else if(cfkfTBEtLK == OxwRKqnPeh){LmkhDufuUP = true;}
      if(CsncpnZAnA == VECAMhdWRc){SHAylAyZHZ = true;}
      else if(VECAMhdWRc == CsncpnZAnA){HGsRYqfMCN = true;}
      if(eMdlhCVJmE == bGeVkxyQnY){FjjLisjUIc = true;}
      else if(bGeVkxyQnY == eMdlhCVJmE){FrEiPlSuUV = true;}
      if(gzXLeMaewK == FbChFOBUlG){UkKBIpBMFt = true;}
      else if(FbChFOBUlG == gzXLeMaewK){xDDNPUXICz = true;}
      if(CaeNczIiJg == TgDlGoNuaH){mMogPHladC = true;}
      else if(TgDlGoNuaH == CaeNczIiJg){mfidzYSBzB = true;}
      if(wJXIOCTKiH == tamkyWAPtV){gAJHHCJosg = true;}
      if(UdcZADVcyd == DnGlEtBTty){AWSyhgwyou = true;}
      if(NtEcxDgPIi == fJjLIuDsOw){zkTNmrtCub = true;}
      while(tamkyWAPtV == wJXIOCTKiH){kgnjcSiCSQ = true;}
      while(DnGlEtBTty == DnGlEtBTty){ckayRDDfBE = true;}
      while(fJjLIuDsOw == fJjLIuDsOw){TWJDaYJZjp = true;}
      if(jCogednRji == true){jCogednRji = false;}
      if(OlZPDfZRhM == true){OlZPDfZRhM = false;}
      if(msBcajqabD == true){msBcajqabD = false;}
      if(SHAylAyZHZ == true){SHAylAyZHZ = false;}
      if(FjjLisjUIc == true){FjjLisjUIc = false;}
      if(UkKBIpBMFt == true){UkKBIpBMFt = false;}
      if(mMogPHladC == true){mMogPHladC = false;}
      if(gAJHHCJosg == true){gAJHHCJosg = false;}
      if(AWSyhgwyou == true){AWSyhgwyou = false;}
      if(zkTNmrtCub == true){zkTNmrtCub = false;}
      if(HIpGuTbDtG == true){HIpGuTbDtG = false;}
      if(fMSYsQtqyh == true){fMSYsQtqyh = false;}
      if(LmkhDufuUP == true){LmkhDufuUP = false;}
      if(HGsRYqfMCN == true){HGsRYqfMCN = false;}
      if(FrEiPlSuUV == true){FrEiPlSuUV = false;}
      if(xDDNPUXICz == true){xDDNPUXICz = false;}
      if(mfidzYSBzB == true){mfidzYSBzB = false;}
      if(kgnjcSiCSQ == true){kgnjcSiCSQ = false;}
      if(ckayRDDfBE == true){ckayRDDfBE = false;}
      if(TWJDaYJZjp == true){TWJDaYJZjp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JVHGXEXNQU
{ 
  void JJJyYlWTKx()
  { 
      bool TXQmqcNZsz = false;
      bool OeaZJjXIfX = false;
      bool OYsQOCtnbG = false;
      bool uKNTPsTPIV = false;
      bool YPiGtWydrr = false;
      bool SzInFtdzXn = false;
      bool iYymEEQHJP = false;
      bool QIAKzypmVq = false;
      bool DPuimuBZNU = false;
      bool OTqTlzRwBp = false;
      bool FqUbbKyxnH = false;
      bool EqdfjSdOzI = false;
      bool CqsnBwRfXz = false;
      bool fskekMtSGc = false;
      bool xEkGQXpKjT = false;
      bool UCwsmOxgaf = false;
      bool rSYoaKFytX = false;
      bool XLIVLyFmWc = false;
      bool GGwEedxrqW = false;
      bool PNqajdeweF = false;
      string ImFnMiTxEi;
      string kiCjarLBXj;
      string CgsPhcBhhG;
      string UXpjZhVuOS;
      string XneUiaTkGm;
      string MUfQObsoFj;
      string hlPxOMsRKs;
      string VQlELOCYfG;
      string JPautzrYVy;
      string ogoeklXhFW;
      string hBaNQwhbEA;
      string YTIyZRKUCO;
      string TTwMEoaHSZ;
      string pUSJYIoMdy;
      string RQTVYUXpET;
      string aDeqDOFOJa;
      string UaIeJEBzZR;
      string cypExDzZmj;
      string RjCzylpbFJ;
      string CZDCcqIoLT;
      if(ImFnMiTxEi == hBaNQwhbEA){TXQmqcNZsz = true;}
      else if(hBaNQwhbEA == ImFnMiTxEi){FqUbbKyxnH = true;}
      if(kiCjarLBXj == YTIyZRKUCO){OeaZJjXIfX = true;}
      else if(YTIyZRKUCO == kiCjarLBXj){EqdfjSdOzI = true;}
      if(CgsPhcBhhG == TTwMEoaHSZ){OYsQOCtnbG = true;}
      else if(TTwMEoaHSZ == CgsPhcBhhG){CqsnBwRfXz = true;}
      if(UXpjZhVuOS == pUSJYIoMdy){uKNTPsTPIV = true;}
      else if(pUSJYIoMdy == UXpjZhVuOS){fskekMtSGc = true;}
      if(XneUiaTkGm == RQTVYUXpET){YPiGtWydrr = true;}
      else if(RQTVYUXpET == XneUiaTkGm){xEkGQXpKjT = true;}
      if(MUfQObsoFj == aDeqDOFOJa){SzInFtdzXn = true;}
      else if(aDeqDOFOJa == MUfQObsoFj){UCwsmOxgaf = true;}
      if(hlPxOMsRKs == UaIeJEBzZR){iYymEEQHJP = true;}
      else if(UaIeJEBzZR == hlPxOMsRKs){rSYoaKFytX = true;}
      if(VQlELOCYfG == cypExDzZmj){QIAKzypmVq = true;}
      if(JPautzrYVy == RjCzylpbFJ){DPuimuBZNU = true;}
      if(ogoeklXhFW == CZDCcqIoLT){OTqTlzRwBp = true;}
      while(cypExDzZmj == VQlELOCYfG){XLIVLyFmWc = true;}
      while(RjCzylpbFJ == RjCzylpbFJ){GGwEedxrqW = true;}
      while(CZDCcqIoLT == CZDCcqIoLT){PNqajdeweF = true;}
      if(TXQmqcNZsz == true){TXQmqcNZsz = false;}
      if(OeaZJjXIfX == true){OeaZJjXIfX = false;}
      if(OYsQOCtnbG == true){OYsQOCtnbG = false;}
      if(uKNTPsTPIV == true){uKNTPsTPIV = false;}
      if(YPiGtWydrr == true){YPiGtWydrr = false;}
      if(SzInFtdzXn == true){SzInFtdzXn = false;}
      if(iYymEEQHJP == true){iYymEEQHJP = false;}
      if(QIAKzypmVq == true){QIAKzypmVq = false;}
      if(DPuimuBZNU == true){DPuimuBZNU = false;}
      if(OTqTlzRwBp == true){OTqTlzRwBp = false;}
      if(FqUbbKyxnH == true){FqUbbKyxnH = false;}
      if(EqdfjSdOzI == true){EqdfjSdOzI = false;}
      if(CqsnBwRfXz == true){CqsnBwRfXz = false;}
      if(fskekMtSGc == true){fskekMtSGc = false;}
      if(xEkGQXpKjT == true){xEkGQXpKjT = false;}
      if(UCwsmOxgaf == true){UCwsmOxgaf = false;}
      if(rSYoaKFytX == true){rSYoaKFytX = false;}
      if(XLIVLyFmWc == true){XLIVLyFmWc = false;}
      if(GGwEedxrqW == true){GGwEedxrqW = false;}
      if(PNqajdeweF == true){PNqajdeweF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MMTFCXWRVN
{ 
  void hXConhbYXQ()
  { 
      bool xSGzorloFz = false;
      bool xRwqXHzBUi = false;
      bool BZNPgrPycr = false;
      bool UEyduurFHC = false;
      bool WpjGutZBxC = false;
      bool iISpyWFqRw = false;
      bool cmLNdrTSub = false;
      bool PttSMKpHTl = false;
      bool RNBZIMlHeY = false;
      bool pBmKYjdWbC = false;
      bool aHFUmoOAdm = false;
      bool gxWeeOklER = false;
      bool GLnWlOHisb = false;
      bool gSeRLKIfmT = false;
      bool ykdrqrdHfK = false;
      bool yqSKuOThiX = false;
      bool heHBFOSFTT = false;
      bool GEzjTVguft = false;
      bool jADhcoAUVw = false;
      bool qZxOlScclc = false;
      string ucVdBiiAZW;
      string QQoXWqpwce;
      string BRSOQZpZcf;
      string UWGawMyUNK;
      string wFbyLusKCg;
      string rhQsCcJHMa;
      string rJXtBsJNbK;
      string rViSiwoUDU;
      string gfWwnlGNXS;
      string CqHlRmhhwR;
      string leirnVzyKG;
      string moErtMlbFO;
      string muoIHBOwAu;
      string OHXkiBxdHR;
      string mHDReNmPrE;
      string AFbhepoZkl;
      string HDxOrfQTIs;
      string PITmberXcs;
      string OzEwtIepFs;
      string LWsUKiJnZz;
      if(ucVdBiiAZW == leirnVzyKG){xSGzorloFz = true;}
      else if(leirnVzyKG == ucVdBiiAZW){aHFUmoOAdm = true;}
      if(QQoXWqpwce == moErtMlbFO){xRwqXHzBUi = true;}
      else if(moErtMlbFO == QQoXWqpwce){gxWeeOklER = true;}
      if(BRSOQZpZcf == muoIHBOwAu){BZNPgrPycr = true;}
      else if(muoIHBOwAu == BRSOQZpZcf){GLnWlOHisb = true;}
      if(UWGawMyUNK == OHXkiBxdHR){UEyduurFHC = true;}
      else if(OHXkiBxdHR == UWGawMyUNK){gSeRLKIfmT = true;}
      if(wFbyLusKCg == mHDReNmPrE){WpjGutZBxC = true;}
      else if(mHDReNmPrE == wFbyLusKCg){ykdrqrdHfK = true;}
      if(rhQsCcJHMa == AFbhepoZkl){iISpyWFqRw = true;}
      else if(AFbhepoZkl == rhQsCcJHMa){yqSKuOThiX = true;}
      if(rJXtBsJNbK == HDxOrfQTIs){cmLNdrTSub = true;}
      else if(HDxOrfQTIs == rJXtBsJNbK){heHBFOSFTT = true;}
      if(rViSiwoUDU == PITmberXcs){PttSMKpHTl = true;}
      if(gfWwnlGNXS == OzEwtIepFs){RNBZIMlHeY = true;}
      if(CqHlRmhhwR == LWsUKiJnZz){pBmKYjdWbC = true;}
      while(PITmberXcs == rViSiwoUDU){GEzjTVguft = true;}
      while(OzEwtIepFs == OzEwtIepFs){jADhcoAUVw = true;}
      while(LWsUKiJnZz == LWsUKiJnZz){qZxOlScclc = true;}
      if(xSGzorloFz == true){xSGzorloFz = false;}
      if(xRwqXHzBUi == true){xRwqXHzBUi = false;}
      if(BZNPgrPycr == true){BZNPgrPycr = false;}
      if(UEyduurFHC == true){UEyduurFHC = false;}
      if(WpjGutZBxC == true){WpjGutZBxC = false;}
      if(iISpyWFqRw == true){iISpyWFqRw = false;}
      if(cmLNdrTSub == true){cmLNdrTSub = false;}
      if(PttSMKpHTl == true){PttSMKpHTl = false;}
      if(RNBZIMlHeY == true){RNBZIMlHeY = false;}
      if(pBmKYjdWbC == true){pBmKYjdWbC = false;}
      if(aHFUmoOAdm == true){aHFUmoOAdm = false;}
      if(gxWeeOklER == true){gxWeeOklER = false;}
      if(GLnWlOHisb == true){GLnWlOHisb = false;}
      if(gSeRLKIfmT == true){gSeRLKIfmT = false;}
      if(ykdrqrdHfK == true){ykdrqrdHfK = false;}
      if(yqSKuOThiX == true){yqSKuOThiX = false;}
      if(heHBFOSFTT == true){heHBFOSFTT = false;}
      if(GEzjTVguft == true){GEzjTVguft = false;}
      if(jADhcoAUVw == true){jADhcoAUVw = false;}
      if(qZxOlScclc == true){qZxOlScclc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ABTZGIIRFO
{ 
  void mZfGsXFRMO()
  { 
      bool kEhzuUIspf = false;
      bool FEQBhMOXkP = false;
      bool mAigedSZhh = false;
      bool FryqOuFQSS = false;
      bool XlFcBEtwEX = false;
      bool YCHirkUBTR = false;
      bool CiLIaNFZll = false;
      bool GyFSqBtGea = false;
      bool iVUJJCjOyd = false;
      bool ZDwAPnZxCn = false;
      bool yUJRQZxoqq = false;
      bool pOVshgNByX = false;
      bool cqaILCCECC = false;
      bool axDqcOLDsi = false;
      bool EuWGmLhCRh = false;
      bool aYydLHsBGN = false;
      bool XrlnQrKeQT = false;
      bool VKIPThTTUA = false;
      bool UzmUbByZfV = false;
      bool VKxeKMIipu = false;
      string jYHXAylTZX;
      string uEkCeHzotW;
      string hUGTxrzonZ;
      string eEmwXHygwX;
      string xfOttJkoGn;
      string dcHXBPSmZH;
      string yxfzrpRndW;
      string ISsWZCGLZn;
      string HKhzwCxPtI;
      string oKHnYAAOCE;
      string rwKifLjjyy;
      string JGNkAnOfDo;
      string rBtVhxKEyY;
      string BqJUwLzyTk;
      string SMRwyhxWnj;
      string kULMLpCnBh;
      string AelYwSxrnn;
      string nPLRVfjxXz;
      string AnPNngewIG;
      string IKxljnarzf;
      if(jYHXAylTZX == rwKifLjjyy){kEhzuUIspf = true;}
      else if(rwKifLjjyy == jYHXAylTZX){yUJRQZxoqq = true;}
      if(uEkCeHzotW == JGNkAnOfDo){FEQBhMOXkP = true;}
      else if(JGNkAnOfDo == uEkCeHzotW){pOVshgNByX = true;}
      if(hUGTxrzonZ == rBtVhxKEyY){mAigedSZhh = true;}
      else if(rBtVhxKEyY == hUGTxrzonZ){cqaILCCECC = true;}
      if(eEmwXHygwX == BqJUwLzyTk){FryqOuFQSS = true;}
      else if(BqJUwLzyTk == eEmwXHygwX){axDqcOLDsi = true;}
      if(xfOttJkoGn == SMRwyhxWnj){XlFcBEtwEX = true;}
      else if(SMRwyhxWnj == xfOttJkoGn){EuWGmLhCRh = true;}
      if(dcHXBPSmZH == kULMLpCnBh){YCHirkUBTR = true;}
      else if(kULMLpCnBh == dcHXBPSmZH){aYydLHsBGN = true;}
      if(yxfzrpRndW == AelYwSxrnn){CiLIaNFZll = true;}
      else if(AelYwSxrnn == yxfzrpRndW){XrlnQrKeQT = true;}
      if(ISsWZCGLZn == nPLRVfjxXz){GyFSqBtGea = true;}
      if(HKhzwCxPtI == AnPNngewIG){iVUJJCjOyd = true;}
      if(oKHnYAAOCE == IKxljnarzf){ZDwAPnZxCn = true;}
      while(nPLRVfjxXz == ISsWZCGLZn){VKIPThTTUA = true;}
      while(AnPNngewIG == AnPNngewIG){UzmUbByZfV = true;}
      while(IKxljnarzf == IKxljnarzf){VKxeKMIipu = true;}
      if(kEhzuUIspf == true){kEhzuUIspf = false;}
      if(FEQBhMOXkP == true){FEQBhMOXkP = false;}
      if(mAigedSZhh == true){mAigedSZhh = false;}
      if(FryqOuFQSS == true){FryqOuFQSS = false;}
      if(XlFcBEtwEX == true){XlFcBEtwEX = false;}
      if(YCHirkUBTR == true){YCHirkUBTR = false;}
      if(CiLIaNFZll == true){CiLIaNFZll = false;}
      if(GyFSqBtGea == true){GyFSqBtGea = false;}
      if(iVUJJCjOyd == true){iVUJJCjOyd = false;}
      if(ZDwAPnZxCn == true){ZDwAPnZxCn = false;}
      if(yUJRQZxoqq == true){yUJRQZxoqq = false;}
      if(pOVshgNByX == true){pOVshgNByX = false;}
      if(cqaILCCECC == true){cqaILCCECC = false;}
      if(axDqcOLDsi == true){axDqcOLDsi = false;}
      if(EuWGmLhCRh == true){EuWGmLhCRh = false;}
      if(aYydLHsBGN == true){aYydLHsBGN = false;}
      if(XrlnQrKeQT == true){XrlnQrKeQT = false;}
      if(VKIPThTTUA == true){VKIPThTTUA = false;}
      if(UzmUbByZfV == true){UzmUbByZfV = false;}
      if(VKxeKMIipu == true){VKxeKMIipu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LTBHXWSCDF
{ 
  void ZxqNtGIrGj()
  { 
      bool rzeZlPPMaf = false;
      bool aofpZHhBqV = false;
      bool LFHslrPsIH = false;
      bool ruhHFfmKxE = false;
      bool kVWXNCaynE = false;
      bool PhVjElqkns = false;
      bool zWESnfHYkt = false;
      bool TXDljpiiej = false;
      bool RRFErJYxCS = false;
      bool nBVEFORDjh = false;
      bool uBMsjqeiAO = false;
      bool DIFDbgQAZd = false;
      bool GJVSFSBzgV = false;
      bool XezxoPELTB = false;
      bool epxnPfuSbX = false;
      bool xRcGbketmR = false;
      bool oeCepXIIOM = false;
      bool cFfYyQLhDZ = false;
      bool WiWJXGBsVD = false;
      bool jKXBLznSyq = false;
      string NolJhCHaFY;
      string WTyxKybVXq;
      string SucuKNsNiF;
      string czPBpoZWZG;
      string yroxcUstCT;
      string MDXrYSMpzU;
      string JtqAuXEwHV;
      string YFuRraGeRp;
      string TyKOsYaXcX;
      string biXFwDAoCF;
      string QxmguGIGzy;
      string MgYIAKibGV;
      string wfSisogoUn;
      string ZQcMZVLdTl;
      string QUXdLuKOEk;
      string UXhfIjdDnF;
      string ZSkKXuDLid;
      string zFHUFbIoXx;
      string eSkiTBixEo;
      string rHoOLxjMGQ;
      if(NolJhCHaFY == QxmguGIGzy){rzeZlPPMaf = true;}
      else if(QxmguGIGzy == NolJhCHaFY){uBMsjqeiAO = true;}
      if(WTyxKybVXq == MgYIAKibGV){aofpZHhBqV = true;}
      else if(MgYIAKibGV == WTyxKybVXq){DIFDbgQAZd = true;}
      if(SucuKNsNiF == wfSisogoUn){LFHslrPsIH = true;}
      else if(wfSisogoUn == SucuKNsNiF){GJVSFSBzgV = true;}
      if(czPBpoZWZG == ZQcMZVLdTl){ruhHFfmKxE = true;}
      else if(ZQcMZVLdTl == czPBpoZWZG){XezxoPELTB = true;}
      if(yroxcUstCT == QUXdLuKOEk){kVWXNCaynE = true;}
      else if(QUXdLuKOEk == yroxcUstCT){epxnPfuSbX = true;}
      if(MDXrYSMpzU == UXhfIjdDnF){PhVjElqkns = true;}
      else if(UXhfIjdDnF == MDXrYSMpzU){xRcGbketmR = true;}
      if(JtqAuXEwHV == ZSkKXuDLid){zWESnfHYkt = true;}
      else if(ZSkKXuDLid == JtqAuXEwHV){oeCepXIIOM = true;}
      if(YFuRraGeRp == zFHUFbIoXx){TXDljpiiej = true;}
      if(TyKOsYaXcX == eSkiTBixEo){RRFErJYxCS = true;}
      if(biXFwDAoCF == rHoOLxjMGQ){nBVEFORDjh = true;}
      while(zFHUFbIoXx == YFuRraGeRp){cFfYyQLhDZ = true;}
      while(eSkiTBixEo == eSkiTBixEo){WiWJXGBsVD = true;}
      while(rHoOLxjMGQ == rHoOLxjMGQ){jKXBLznSyq = true;}
      if(rzeZlPPMaf == true){rzeZlPPMaf = false;}
      if(aofpZHhBqV == true){aofpZHhBqV = false;}
      if(LFHslrPsIH == true){LFHslrPsIH = false;}
      if(ruhHFfmKxE == true){ruhHFfmKxE = false;}
      if(kVWXNCaynE == true){kVWXNCaynE = false;}
      if(PhVjElqkns == true){PhVjElqkns = false;}
      if(zWESnfHYkt == true){zWESnfHYkt = false;}
      if(TXDljpiiej == true){TXDljpiiej = false;}
      if(RRFErJYxCS == true){RRFErJYxCS = false;}
      if(nBVEFORDjh == true){nBVEFORDjh = false;}
      if(uBMsjqeiAO == true){uBMsjqeiAO = false;}
      if(DIFDbgQAZd == true){DIFDbgQAZd = false;}
      if(GJVSFSBzgV == true){GJVSFSBzgV = false;}
      if(XezxoPELTB == true){XezxoPELTB = false;}
      if(epxnPfuSbX == true){epxnPfuSbX = false;}
      if(xRcGbketmR == true){xRcGbketmR = false;}
      if(oeCepXIIOM == true){oeCepXIIOM = false;}
      if(cFfYyQLhDZ == true){cFfYyQLhDZ = false;}
      if(WiWJXGBsVD == true){WiWJXGBsVD = false;}
      if(jKXBLznSyq == true){jKXBLznSyq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EXJYBSGNFY
{ 
  void qaYhmRKMZY()
  { 
      bool lqmJnTQNiy = false;
      bool IorOLVBkBx = false;
      bool XrzxLNDOjR = false;
      bool sYSzfTzsfO = false;
      bool VmKJQiJbce = false;
      bool YfSOXsqoxa = false;
      bool QCcQEjWriq = false;
      bool VHEmakgogb = false;
      bool DbkFsNFDbl = false;
      bool cJuFyTJtFf = false;
      bool MRslIQafmm = false;
      bool MCHVWoQWXq = false;
      bool dSPwOLMznH = false;
      bool amjBOkhzwc = false;
      bool mZPoYZCZhJ = false;
      bool CmWOBtBwWw = false;
      bool EaqfMZRGGk = false;
      bool GQZtDDCaXn = false;
      bool JlQeFmQVzU = false;
      bool jlczXLijbz = false;
      string KzJoWBtSnC;
      string xhuNegsLpQ;
      string ruWeNDCjHd;
      string AOxdGJBkqH;
      string nxCBYkNJrN;
      string NUMKnPcdaT;
      string yJKJCikRGV;
      string fHThburUGb;
      string orrtPeBmoq;
      string fWJXJelszo;
      string AwDVgGAehs;
      string WIXzdFQQtW;
      string gybPoJxwYx;
      string IzVQbsoWMJ;
      string eWEwTXyKsE;
      string OVybICUmfW;
      string IEFjjXlHXj;
      string PtEkrKseuR;
      string LmCUimAtHZ;
      string YBpoAZQTMu;
      if(KzJoWBtSnC == AwDVgGAehs){lqmJnTQNiy = true;}
      else if(AwDVgGAehs == KzJoWBtSnC){MRslIQafmm = true;}
      if(xhuNegsLpQ == WIXzdFQQtW){IorOLVBkBx = true;}
      else if(WIXzdFQQtW == xhuNegsLpQ){MCHVWoQWXq = true;}
      if(ruWeNDCjHd == gybPoJxwYx){XrzxLNDOjR = true;}
      else if(gybPoJxwYx == ruWeNDCjHd){dSPwOLMznH = true;}
      if(AOxdGJBkqH == IzVQbsoWMJ){sYSzfTzsfO = true;}
      else if(IzVQbsoWMJ == AOxdGJBkqH){amjBOkhzwc = true;}
      if(nxCBYkNJrN == eWEwTXyKsE){VmKJQiJbce = true;}
      else if(eWEwTXyKsE == nxCBYkNJrN){mZPoYZCZhJ = true;}
      if(NUMKnPcdaT == OVybICUmfW){YfSOXsqoxa = true;}
      else if(OVybICUmfW == NUMKnPcdaT){CmWOBtBwWw = true;}
      if(yJKJCikRGV == IEFjjXlHXj){QCcQEjWriq = true;}
      else if(IEFjjXlHXj == yJKJCikRGV){EaqfMZRGGk = true;}
      if(fHThburUGb == PtEkrKseuR){VHEmakgogb = true;}
      if(orrtPeBmoq == LmCUimAtHZ){DbkFsNFDbl = true;}
      if(fWJXJelszo == YBpoAZQTMu){cJuFyTJtFf = true;}
      while(PtEkrKseuR == fHThburUGb){GQZtDDCaXn = true;}
      while(LmCUimAtHZ == LmCUimAtHZ){JlQeFmQVzU = true;}
      while(YBpoAZQTMu == YBpoAZQTMu){jlczXLijbz = true;}
      if(lqmJnTQNiy == true){lqmJnTQNiy = false;}
      if(IorOLVBkBx == true){IorOLVBkBx = false;}
      if(XrzxLNDOjR == true){XrzxLNDOjR = false;}
      if(sYSzfTzsfO == true){sYSzfTzsfO = false;}
      if(VmKJQiJbce == true){VmKJQiJbce = false;}
      if(YfSOXsqoxa == true){YfSOXsqoxa = false;}
      if(QCcQEjWriq == true){QCcQEjWriq = false;}
      if(VHEmakgogb == true){VHEmakgogb = false;}
      if(DbkFsNFDbl == true){DbkFsNFDbl = false;}
      if(cJuFyTJtFf == true){cJuFyTJtFf = false;}
      if(MRslIQafmm == true){MRslIQafmm = false;}
      if(MCHVWoQWXq == true){MCHVWoQWXq = false;}
      if(dSPwOLMznH == true){dSPwOLMznH = false;}
      if(amjBOkhzwc == true){amjBOkhzwc = false;}
      if(mZPoYZCZhJ == true){mZPoYZCZhJ = false;}
      if(CmWOBtBwWw == true){CmWOBtBwWw = false;}
      if(EaqfMZRGGk == true){EaqfMZRGGk = false;}
      if(GQZtDDCaXn == true){GQZtDDCaXn = false;}
      if(JlQeFmQVzU == true){JlQeFmQVzU = false;}
      if(jlczXLijbz == true){jlczXLijbz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JUCAFAKGNB
{ 
  void bIWqsXIfxe()
  { 
      bool HJuiLLMeZD = false;
      bool ShQjSGHASO = false;
      bool AhMSqTqbru = false;
      bool HcWhokVVVA = false;
      bool hNroLSuzyl = false;
      bool QfWBsZwbrr = false;
      bool UjlewpKhuh = false;
      bool jleSgmoWHX = false;
      bool XqdGeaFUoO = false;
      bool ntddfyaNsU = false;
      bool HNEQBeBDUG = false;
      bool jZUTTdFfAV = false;
      bool jpsfspHBmh = false;
      bool LbdlPKlNFA = false;
      bool YCzheOYJJC = false;
      bool ruNXkRTYWK = false;
      bool WAQmuIwiDJ = false;
      bool qrZzwhpKBe = false;
      bool RyqkoPOFBx = false;
      bool pNqtdXkMmW = false;
      string XLUGNeKNCW;
      string xqYZSscgZC;
      string gtnyBqePoA;
      string pZFYTrcLLa;
      string YCTdRLjQMm;
      string ANFGncWWEV;
      string zuYBgWlzGZ;
      string QRUzcdaJfp;
      string HODBzcUykp;
      string UGHoaddRxt;
      string YjJlWirFdK;
      string CMqOOjrXBD;
      string CmOQFJKfXy;
      string AIMkQWEQdQ;
      string jOUanIPsaq;
      string lFPsqlVsgM;
      string XMheJsAFxr;
      string easkTnSncw;
      string tREgLtrSse;
      string ALjQrXgpQt;
      if(XLUGNeKNCW == YjJlWirFdK){HJuiLLMeZD = true;}
      else if(YjJlWirFdK == XLUGNeKNCW){HNEQBeBDUG = true;}
      if(xqYZSscgZC == CMqOOjrXBD){ShQjSGHASO = true;}
      else if(CMqOOjrXBD == xqYZSscgZC){jZUTTdFfAV = true;}
      if(gtnyBqePoA == CmOQFJKfXy){AhMSqTqbru = true;}
      else if(CmOQFJKfXy == gtnyBqePoA){jpsfspHBmh = true;}
      if(pZFYTrcLLa == AIMkQWEQdQ){HcWhokVVVA = true;}
      else if(AIMkQWEQdQ == pZFYTrcLLa){LbdlPKlNFA = true;}
      if(YCTdRLjQMm == jOUanIPsaq){hNroLSuzyl = true;}
      else if(jOUanIPsaq == YCTdRLjQMm){YCzheOYJJC = true;}
      if(ANFGncWWEV == lFPsqlVsgM){QfWBsZwbrr = true;}
      else if(lFPsqlVsgM == ANFGncWWEV){ruNXkRTYWK = true;}
      if(zuYBgWlzGZ == XMheJsAFxr){UjlewpKhuh = true;}
      else if(XMheJsAFxr == zuYBgWlzGZ){WAQmuIwiDJ = true;}
      if(QRUzcdaJfp == easkTnSncw){jleSgmoWHX = true;}
      if(HODBzcUykp == tREgLtrSse){XqdGeaFUoO = true;}
      if(UGHoaddRxt == ALjQrXgpQt){ntddfyaNsU = true;}
      while(easkTnSncw == QRUzcdaJfp){qrZzwhpKBe = true;}
      while(tREgLtrSse == tREgLtrSse){RyqkoPOFBx = true;}
      while(ALjQrXgpQt == ALjQrXgpQt){pNqtdXkMmW = true;}
      if(HJuiLLMeZD == true){HJuiLLMeZD = false;}
      if(ShQjSGHASO == true){ShQjSGHASO = false;}
      if(AhMSqTqbru == true){AhMSqTqbru = false;}
      if(HcWhokVVVA == true){HcWhokVVVA = false;}
      if(hNroLSuzyl == true){hNroLSuzyl = false;}
      if(QfWBsZwbrr == true){QfWBsZwbrr = false;}
      if(UjlewpKhuh == true){UjlewpKhuh = false;}
      if(jleSgmoWHX == true){jleSgmoWHX = false;}
      if(XqdGeaFUoO == true){XqdGeaFUoO = false;}
      if(ntddfyaNsU == true){ntddfyaNsU = false;}
      if(HNEQBeBDUG == true){HNEQBeBDUG = false;}
      if(jZUTTdFfAV == true){jZUTTdFfAV = false;}
      if(jpsfspHBmh == true){jpsfspHBmh = false;}
      if(LbdlPKlNFA == true){LbdlPKlNFA = false;}
      if(YCzheOYJJC == true){YCzheOYJJC = false;}
      if(ruNXkRTYWK == true){ruNXkRTYWK = false;}
      if(WAQmuIwiDJ == true){WAQmuIwiDJ = false;}
      if(qrZzwhpKBe == true){qrZzwhpKBe = false;}
      if(RyqkoPOFBx == true){RyqkoPOFBx = false;}
      if(pNqtdXkMmW == true){pNqtdXkMmW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GJMLNJACFU
{ 
  void ABKtxHHNAD()
  { 
      bool ZTwOuilTif = false;
      bool nDrBSmoSOs = false;
      bool MNStLmLHRh = false;
      bool YpGnpgosNW = false;
      bool tFyGyLVFym = false;
      bool VBHVhMBCCI = false;
      bool XeBBGxxELk = false;
      bool yuFqyGOLuA = false;
      bool RFIeLXijGd = false;
      bool flqEzPDxAA = false;
      bool NRtMoawPXa = false;
      bool xoHCqRWWoh = false;
      bool ONxhFLDArh = false;
      bool CQLtlALuok = false;
      bool bSMefqenNg = false;
      bool sgIRkATMHd = false;
      bool WuXoYfdMQq = false;
      bool GagEGwASBN = false;
      bool fOmKoUIsIk = false;
      bool fymLNfuWGA = false;
      string AXIXSNgedJ;
      string bVKosuTCDb;
      string fiZPObqFms;
      string EGAqUahGxK;
      string XPpjlYCKXH;
      string CAagjQxsJp;
      string WarjFVVSTR;
      string NMFsEQrpcp;
      string YfgfpDeSHE;
      string dnxGmwXGeQ;
      string CjpGspuhcS;
      string XHQTQptLsB;
      string qCKPmYPyFH;
      string slKLmooalA;
      string IwpofWXcpw;
      string CLMcZAZaSU;
      string ZxbUZlwEgb;
      string BSYsstLViQ;
      string BlHIFgYhll;
      string PNHRaLUVOt;
      if(AXIXSNgedJ == CjpGspuhcS){ZTwOuilTif = true;}
      else if(CjpGspuhcS == AXIXSNgedJ){NRtMoawPXa = true;}
      if(bVKosuTCDb == XHQTQptLsB){nDrBSmoSOs = true;}
      else if(XHQTQptLsB == bVKosuTCDb){xoHCqRWWoh = true;}
      if(fiZPObqFms == qCKPmYPyFH){MNStLmLHRh = true;}
      else if(qCKPmYPyFH == fiZPObqFms){ONxhFLDArh = true;}
      if(EGAqUahGxK == slKLmooalA){YpGnpgosNW = true;}
      else if(slKLmooalA == EGAqUahGxK){CQLtlALuok = true;}
      if(XPpjlYCKXH == IwpofWXcpw){tFyGyLVFym = true;}
      else if(IwpofWXcpw == XPpjlYCKXH){bSMefqenNg = true;}
      if(CAagjQxsJp == CLMcZAZaSU){VBHVhMBCCI = true;}
      else if(CLMcZAZaSU == CAagjQxsJp){sgIRkATMHd = true;}
      if(WarjFVVSTR == ZxbUZlwEgb){XeBBGxxELk = true;}
      else if(ZxbUZlwEgb == WarjFVVSTR){WuXoYfdMQq = true;}
      if(NMFsEQrpcp == BSYsstLViQ){yuFqyGOLuA = true;}
      if(YfgfpDeSHE == BlHIFgYhll){RFIeLXijGd = true;}
      if(dnxGmwXGeQ == PNHRaLUVOt){flqEzPDxAA = true;}
      while(BSYsstLViQ == NMFsEQrpcp){GagEGwASBN = true;}
      while(BlHIFgYhll == BlHIFgYhll){fOmKoUIsIk = true;}
      while(PNHRaLUVOt == PNHRaLUVOt){fymLNfuWGA = true;}
      if(ZTwOuilTif == true){ZTwOuilTif = false;}
      if(nDrBSmoSOs == true){nDrBSmoSOs = false;}
      if(MNStLmLHRh == true){MNStLmLHRh = false;}
      if(YpGnpgosNW == true){YpGnpgosNW = false;}
      if(tFyGyLVFym == true){tFyGyLVFym = false;}
      if(VBHVhMBCCI == true){VBHVhMBCCI = false;}
      if(XeBBGxxELk == true){XeBBGxxELk = false;}
      if(yuFqyGOLuA == true){yuFqyGOLuA = false;}
      if(RFIeLXijGd == true){RFIeLXijGd = false;}
      if(flqEzPDxAA == true){flqEzPDxAA = false;}
      if(NRtMoawPXa == true){NRtMoawPXa = false;}
      if(xoHCqRWWoh == true){xoHCqRWWoh = false;}
      if(ONxhFLDArh == true){ONxhFLDArh = false;}
      if(CQLtlALuok == true){CQLtlALuok = false;}
      if(bSMefqenNg == true){bSMefqenNg = false;}
      if(sgIRkATMHd == true){sgIRkATMHd = false;}
      if(WuXoYfdMQq == true){WuXoYfdMQq = false;}
      if(GagEGwASBN == true){GagEGwASBN = false;}
      if(fOmKoUIsIk == true){fOmKoUIsIk = false;}
      if(fymLNfuWGA == true){fymLNfuWGA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YOMRIPJJBS
{ 
  void WRKJTAsjPY()
  { 
      bool xSjDEmVoNs = false;
      bool cAbxZOMkLq = false;
      bool OaOYaqfsZe = false;
      bool QQlexiEQJj = false;
      bool OeVkUzoxSZ = false;
      bool WtFsAVELbN = false;
      bool GcPhbMNxzp = false;
      bool KuabcjEcEa = false;
      bool BiazHWKrda = false;
      bool esnwckPnIH = false;
      bool lqxbPbScPQ = false;
      bool QaGBLXCPZF = false;
      bool BVTYLQGeyq = false;
      bool UQUwoJkyif = false;
      bool EgbNJElljE = false;
      bool izNDFPXYQy = false;
      bool UmdXuAFJMB = false;
      bool mEgtATsFOH = false;
      bool eTttIVDRqY = false;
      bool lLgkKQCDRJ = false;
      string qxOfnYAFdb;
      string kBlzHCDgxa;
      string syEUyJWImb;
      string AKyQzYQUGM;
      string QiNinwdQcb;
      string iFJdfrrshd;
      string CqSBaZCUAi;
      string kiZjJJkUgC;
      string fFfLsuBUjG;
      string fXmbJYQMIN;
      string sIQtpzeYTV;
      string HXLfyxLHIf;
      string YhksCNwyZj;
      string sXMSIXnkUs;
      string QcANzILHdM;
      string NIEcoKWWqb;
      string DgyiciKrWa;
      string IZlOOuhWtt;
      string CoTNWkTjdx;
      string ARtsojeRkP;
      if(qxOfnYAFdb == sIQtpzeYTV){xSjDEmVoNs = true;}
      else if(sIQtpzeYTV == qxOfnYAFdb){lqxbPbScPQ = true;}
      if(kBlzHCDgxa == HXLfyxLHIf){cAbxZOMkLq = true;}
      else if(HXLfyxLHIf == kBlzHCDgxa){QaGBLXCPZF = true;}
      if(syEUyJWImb == YhksCNwyZj){OaOYaqfsZe = true;}
      else if(YhksCNwyZj == syEUyJWImb){BVTYLQGeyq = true;}
      if(AKyQzYQUGM == sXMSIXnkUs){QQlexiEQJj = true;}
      else if(sXMSIXnkUs == AKyQzYQUGM){UQUwoJkyif = true;}
      if(QiNinwdQcb == QcANzILHdM){OeVkUzoxSZ = true;}
      else if(QcANzILHdM == QiNinwdQcb){EgbNJElljE = true;}
      if(iFJdfrrshd == NIEcoKWWqb){WtFsAVELbN = true;}
      else if(NIEcoKWWqb == iFJdfrrshd){izNDFPXYQy = true;}
      if(CqSBaZCUAi == DgyiciKrWa){GcPhbMNxzp = true;}
      else if(DgyiciKrWa == CqSBaZCUAi){UmdXuAFJMB = true;}
      if(kiZjJJkUgC == IZlOOuhWtt){KuabcjEcEa = true;}
      if(fFfLsuBUjG == CoTNWkTjdx){BiazHWKrda = true;}
      if(fXmbJYQMIN == ARtsojeRkP){esnwckPnIH = true;}
      while(IZlOOuhWtt == kiZjJJkUgC){mEgtATsFOH = true;}
      while(CoTNWkTjdx == CoTNWkTjdx){eTttIVDRqY = true;}
      while(ARtsojeRkP == ARtsojeRkP){lLgkKQCDRJ = true;}
      if(xSjDEmVoNs == true){xSjDEmVoNs = false;}
      if(cAbxZOMkLq == true){cAbxZOMkLq = false;}
      if(OaOYaqfsZe == true){OaOYaqfsZe = false;}
      if(QQlexiEQJj == true){QQlexiEQJj = false;}
      if(OeVkUzoxSZ == true){OeVkUzoxSZ = false;}
      if(WtFsAVELbN == true){WtFsAVELbN = false;}
      if(GcPhbMNxzp == true){GcPhbMNxzp = false;}
      if(KuabcjEcEa == true){KuabcjEcEa = false;}
      if(BiazHWKrda == true){BiazHWKrda = false;}
      if(esnwckPnIH == true){esnwckPnIH = false;}
      if(lqxbPbScPQ == true){lqxbPbScPQ = false;}
      if(QaGBLXCPZF == true){QaGBLXCPZF = false;}
      if(BVTYLQGeyq == true){BVTYLQGeyq = false;}
      if(UQUwoJkyif == true){UQUwoJkyif = false;}
      if(EgbNJElljE == true){EgbNJElljE = false;}
      if(izNDFPXYQy == true){izNDFPXYQy = false;}
      if(UmdXuAFJMB == true){UmdXuAFJMB = false;}
      if(mEgtATsFOH == true){mEgtATsFOH = false;}
      if(eTttIVDRqY == true){eTttIVDRqY = false;}
      if(lLgkKQCDRJ == true){lLgkKQCDRJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUHWVSSUTC
{ 
  void cayWWczlOE()
  { 
      bool GBMgkOzcdD = false;
      bool ZHQUKtCYEk = false;
      bool VLeWuWEomk = false;
      bool MsnJSWcgUU = false;
      bool PHmyQpcDau = false;
      bool kHVLstWolN = false;
      bool KKospgSHBm = false;
      bool RUDjVOYfFF = false;
      bool tBNqzEXcQY = false;
      bool AmtHJERtHj = false;
      bool WVBndQDkod = false;
      bool VpjgTJxxtk = false;
      bool IppcmeZwZQ = false;
      bool wdYUhYzZNi = false;
      bool AlmlDJDNnA = false;
      bool HUAWbfeYAy = false;
      bool pHLXgqROyu = false;
      bool KXiLjWCEZc = false;
      bool bMIYJbdBsC = false;
      bool saYPrsZPFL = false;
      string iQmANlbklz;
      string ARJZWPQJkQ;
      string umSGsMPNZJ;
      string NwHoNfteKZ;
      string BhlSFjuusM;
      string kDydCwyfGA;
      string VOKblDJULq;
      string VlyLONAABJ;
      string QTTNYJyclR;
      string hNXJDmXJfC;
      string ZajCqyFlPo;
      string wyexiBtxDc;
      string FghtIHOnHb;
      string opTyjpjRVZ;
      string ELNwUjhZZC;
      string raGCxsrpsj;
      string iQenAFdgNs;
      string RcadYsSkYY;
      string YoOFiOjRBq;
      string xtXlpngZwO;
      if(iQmANlbklz == ZajCqyFlPo){GBMgkOzcdD = true;}
      else if(ZajCqyFlPo == iQmANlbklz){WVBndQDkod = true;}
      if(ARJZWPQJkQ == wyexiBtxDc){ZHQUKtCYEk = true;}
      else if(wyexiBtxDc == ARJZWPQJkQ){VpjgTJxxtk = true;}
      if(umSGsMPNZJ == FghtIHOnHb){VLeWuWEomk = true;}
      else if(FghtIHOnHb == umSGsMPNZJ){IppcmeZwZQ = true;}
      if(NwHoNfteKZ == opTyjpjRVZ){MsnJSWcgUU = true;}
      else if(opTyjpjRVZ == NwHoNfteKZ){wdYUhYzZNi = true;}
      if(BhlSFjuusM == ELNwUjhZZC){PHmyQpcDau = true;}
      else if(ELNwUjhZZC == BhlSFjuusM){AlmlDJDNnA = true;}
      if(kDydCwyfGA == raGCxsrpsj){kHVLstWolN = true;}
      else if(raGCxsrpsj == kDydCwyfGA){HUAWbfeYAy = true;}
      if(VOKblDJULq == iQenAFdgNs){KKospgSHBm = true;}
      else if(iQenAFdgNs == VOKblDJULq){pHLXgqROyu = true;}
      if(VlyLONAABJ == RcadYsSkYY){RUDjVOYfFF = true;}
      if(QTTNYJyclR == YoOFiOjRBq){tBNqzEXcQY = true;}
      if(hNXJDmXJfC == xtXlpngZwO){AmtHJERtHj = true;}
      while(RcadYsSkYY == VlyLONAABJ){KXiLjWCEZc = true;}
      while(YoOFiOjRBq == YoOFiOjRBq){bMIYJbdBsC = true;}
      while(xtXlpngZwO == xtXlpngZwO){saYPrsZPFL = true;}
      if(GBMgkOzcdD == true){GBMgkOzcdD = false;}
      if(ZHQUKtCYEk == true){ZHQUKtCYEk = false;}
      if(VLeWuWEomk == true){VLeWuWEomk = false;}
      if(MsnJSWcgUU == true){MsnJSWcgUU = false;}
      if(PHmyQpcDau == true){PHmyQpcDau = false;}
      if(kHVLstWolN == true){kHVLstWolN = false;}
      if(KKospgSHBm == true){KKospgSHBm = false;}
      if(RUDjVOYfFF == true){RUDjVOYfFF = false;}
      if(tBNqzEXcQY == true){tBNqzEXcQY = false;}
      if(AmtHJERtHj == true){AmtHJERtHj = false;}
      if(WVBndQDkod == true){WVBndQDkod = false;}
      if(VpjgTJxxtk == true){VpjgTJxxtk = false;}
      if(IppcmeZwZQ == true){IppcmeZwZQ = false;}
      if(wdYUhYzZNi == true){wdYUhYzZNi = false;}
      if(AlmlDJDNnA == true){AlmlDJDNnA = false;}
      if(HUAWbfeYAy == true){HUAWbfeYAy = false;}
      if(pHLXgqROyu == true){pHLXgqROyu = false;}
      if(KXiLjWCEZc == true){KXiLjWCEZc = false;}
      if(bMIYJbdBsC == true){bMIYJbdBsC = false;}
      if(saYPrsZPFL == true){saYPrsZPFL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJFVAWRLDP
{ 
  void BGeTUhDptM()
  { 
      bool AdKGxiZwKK = false;
      bool cpsZiARbHU = false;
      bool ZwARDUPRHS = false;
      bool XYeuafSzrO = false;
      bool kzSLTAHnFm = false;
      bool xZXKfEcsCb = false;
      bool SHorlEKxyC = false;
      bool hSjrjadoyD = false;
      bool NbLTUyBTPV = false;
      bool DZwPwcJZZP = false;
      bool oJoDFdpeaE = false;
      bool antzOqwUWm = false;
      bool DpgczHWTwG = false;
      bool QDPiNDmIOq = false;
      bool IVsLuPexBE = false;
      bool goDlMycMDx = false;
      bool HVhTnXYLkK = false;
      bool EmFfegxVgj = false;
      bool cZRqZazcVO = false;
      bool aaFQilmYWX = false;
      string ZaWOItASdh;
      string DboDclooTf;
      string XUrGRCHqlL;
      string sPidoFuQsY;
      string PFZETPjlZw;
      string IZUgrEiPwF;
      string mJfRonrKNW;
      string qYutQSumlC;
      string SUQoCStClk;
      string VeTnlFYHPe;
      string XZYCFieZQZ;
      string JwdtmSrqPV;
      string tpXcBLEGIK;
      string snWGerwOiT;
      string mTkMaZBZBT;
      string MhrskhBuBt;
      string eXRFfVYWOt;
      string VdHuiaELBa;
      string KdFoyLucVx;
      string pANonPCefF;
      if(ZaWOItASdh == XZYCFieZQZ){AdKGxiZwKK = true;}
      else if(XZYCFieZQZ == ZaWOItASdh){oJoDFdpeaE = true;}
      if(DboDclooTf == JwdtmSrqPV){cpsZiARbHU = true;}
      else if(JwdtmSrqPV == DboDclooTf){antzOqwUWm = true;}
      if(XUrGRCHqlL == tpXcBLEGIK){ZwARDUPRHS = true;}
      else if(tpXcBLEGIK == XUrGRCHqlL){DpgczHWTwG = true;}
      if(sPidoFuQsY == snWGerwOiT){XYeuafSzrO = true;}
      else if(snWGerwOiT == sPidoFuQsY){QDPiNDmIOq = true;}
      if(PFZETPjlZw == mTkMaZBZBT){kzSLTAHnFm = true;}
      else if(mTkMaZBZBT == PFZETPjlZw){IVsLuPexBE = true;}
      if(IZUgrEiPwF == MhrskhBuBt){xZXKfEcsCb = true;}
      else if(MhrskhBuBt == IZUgrEiPwF){goDlMycMDx = true;}
      if(mJfRonrKNW == eXRFfVYWOt){SHorlEKxyC = true;}
      else if(eXRFfVYWOt == mJfRonrKNW){HVhTnXYLkK = true;}
      if(qYutQSumlC == VdHuiaELBa){hSjrjadoyD = true;}
      if(SUQoCStClk == KdFoyLucVx){NbLTUyBTPV = true;}
      if(VeTnlFYHPe == pANonPCefF){DZwPwcJZZP = true;}
      while(VdHuiaELBa == qYutQSumlC){EmFfegxVgj = true;}
      while(KdFoyLucVx == KdFoyLucVx){cZRqZazcVO = true;}
      while(pANonPCefF == pANonPCefF){aaFQilmYWX = true;}
      if(AdKGxiZwKK == true){AdKGxiZwKK = false;}
      if(cpsZiARbHU == true){cpsZiARbHU = false;}
      if(ZwARDUPRHS == true){ZwARDUPRHS = false;}
      if(XYeuafSzrO == true){XYeuafSzrO = false;}
      if(kzSLTAHnFm == true){kzSLTAHnFm = false;}
      if(xZXKfEcsCb == true){xZXKfEcsCb = false;}
      if(SHorlEKxyC == true){SHorlEKxyC = false;}
      if(hSjrjadoyD == true){hSjrjadoyD = false;}
      if(NbLTUyBTPV == true){NbLTUyBTPV = false;}
      if(DZwPwcJZZP == true){DZwPwcJZZP = false;}
      if(oJoDFdpeaE == true){oJoDFdpeaE = false;}
      if(antzOqwUWm == true){antzOqwUWm = false;}
      if(DpgczHWTwG == true){DpgczHWTwG = false;}
      if(QDPiNDmIOq == true){QDPiNDmIOq = false;}
      if(IVsLuPexBE == true){IVsLuPexBE = false;}
      if(goDlMycMDx == true){goDlMycMDx = false;}
      if(HVhTnXYLkK == true){HVhTnXYLkK = false;}
      if(EmFfegxVgj == true){EmFfegxVgj = false;}
      if(cZRqZazcVO == true){cZRqZazcVO = false;}
      if(aaFQilmYWX == true){aaFQilmYWX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MXXFHJKADZ
{ 
  void EUQsigLfAm()
  { 
      bool cquBLHCQmr = false;
      bool fAIzdDoCGR = false;
      bool wDRaLTTtpT = false;
      bool wHBIUNRVjP = false;
      bool ciSqqiaGVm = false;
      bool JmutZZZToq = false;
      bool mIZTwYyzdP = false;
      bool lTSpoNjajb = false;
      bool rNXDKILHiu = false;
      bool nxfrcTIztS = false;
      bool kbcGApTEFL = false;
      bool oyjNyZjVIn = false;
      bool MqPiaomaNU = false;
      bool FjfQqQjRDT = false;
      bool nHBXFpMSsD = false;
      bool jmpGFtLseL = false;
      bool CspkFFRSWh = false;
      bool oRSozFoqck = false;
      bool bUgKjSsZLw = false;
      bool EqmrRuQQRA = false;
      string VegcyqlBlB;
      string bTRyezWXaB;
      string bsHxZXGSFQ;
      string fEQMoirJPa;
      string hXIHchowen;
      string knHCdcXjDa;
      string kTuUVWDFJw;
      string GMIzTEjzTq;
      string hJmRfqwNhL;
      string KIGopObmlF;
      string djlihXfHiZ;
      string sXPLrafdoe;
      string aoWykyGTJF;
      string cxNONxXEjH;
      string LneISmrtwO;
      string hxxGeoNnxi;
      string QMycwwKByu;
      string DatgSlJNfy;
      string FMWuWezGiX;
      string iiGAqzpCLW;
      if(VegcyqlBlB == djlihXfHiZ){cquBLHCQmr = true;}
      else if(djlihXfHiZ == VegcyqlBlB){kbcGApTEFL = true;}
      if(bTRyezWXaB == sXPLrafdoe){fAIzdDoCGR = true;}
      else if(sXPLrafdoe == bTRyezWXaB){oyjNyZjVIn = true;}
      if(bsHxZXGSFQ == aoWykyGTJF){wDRaLTTtpT = true;}
      else if(aoWykyGTJF == bsHxZXGSFQ){MqPiaomaNU = true;}
      if(fEQMoirJPa == cxNONxXEjH){wHBIUNRVjP = true;}
      else if(cxNONxXEjH == fEQMoirJPa){FjfQqQjRDT = true;}
      if(hXIHchowen == LneISmrtwO){ciSqqiaGVm = true;}
      else if(LneISmrtwO == hXIHchowen){nHBXFpMSsD = true;}
      if(knHCdcXjDa == hxxGeoNnxi){JmutZZZToq = true;}
      else if(hxxGeoNnxi == knHCdcXjDa){jmpGFtLseL = true;}
      if(kTuUVWDFJw == QMycwwKByu){mIZTwYyzdP = true;}
      else if(QMycwwKByu == kTuUVWDFJw){CspkFFRSWh = true;}
      if(GMIzTEjzTq == DatgSlJNfy){lTSpoNjajb = true;}
      if(hJmRfqwNhL == FMWuWezGiX){rNXDKILHiu = true;}
      if(KIGopObmlF == iiGAqzpCLW){nxfrcTIztS = true;}
      while(DatgSlJNfy == GMIzTEjzTq){oRSozFoqck = true;}
      while(FMWuWezGiX == FMWuWezGiX){bUgKjSsZLw = true;}
      while(iiGAqzpCLW == iiGAqzpCLW){EqmrRuQQRA = true;}
      if(cquBLHCQmr == true){cquBLHCQmr = false;}
      if(fAIzdDoCGR == true){fAIzdDoCGR = false;}
      if(wDRaLTTtpT == true){wDRaLTTtpT = false;}
      if(wHBIUNRVjP == true){wHBIUNRVjP = false;}
      if(ciSqqiaGVm == true){ciSqqiaGVm = false;}
      if(JmutZZZToq == true){JmutZZZToq = false;}
      if(mIZTwYyzdP == true){mIZTwYyzdP = false;}
      if(lTSpoNjajb == true){lTSpoNjajb = false;}
      if(rNXDKILHiu == true){rNXDKILHiu = false;}
      if(nxfrcTIztS == true){nxfrcTIztS = false;}
      if(kbcGApTEFL == true){kbcGApTEFL = false;}
      if(oyjNyZjVIn == true){oyjNyZjVIn = false;}
      if(MqPiaomaNU == true){MqPiaomaNU = false;}
      if(FjfQqQjRDT == true){FjfQqQjRDT = false;}
      if(nHBXFpMSsD == true){nHBXFpMSsD = false;}
      if(jmpGFtLseL == true){jmpGFtLseL = false;}
      if(CspkFFRSWh == true){CspkFFRSWh = false;}
      if(oRSozFoqck == true){oRSozFoqck = false;}
      if(bUgKjSsZLw == true){bUgKjSsZLw = false;}
      if(EqmrRuQQRA == true){EqmrRuQQRA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ORECZWYMWQ
{ 
  void RbfuchkKWX()
  { 
      bool eNjtzYChXu = false;
      bool HBMoRrnkeA = false;
      bool kVfHJTeXnI = false;
      bool KVdCVpCEMn = false;
      bool pwCYyxupas = false;
      bool yTDCiIhbjf = false;
      bool tesPkkWKTb = false;
      bool piXpKoTHIL = false;
      bool YnwuKpSaTM = false;
      bool IZTftLCmmN = false;
      bool ajWzDPuNrs = false;
      bool oZTXHGhyEt = false;
      bool SuqHSPOquz = false;
      bool mgTuknQxqu = false;
      bool uEiZXhGwYn = false;
      bool cDhstesPfm = false;
      bool ADRsGHGXlT = false;
      bool ojGJzNMRij = false;
      bool JSSHVizaAG = false;
      bool tBREtqmpSP = false;
      string rgchUXbrdl;
      string PRwRmtdZiF;
      string rFHptkTEHI;
      string CJVQYrgPcz;
      string ohUYhlqjNC;
      string cmVFOmZmmi;
      string DXjVjFwfsu;
      string NNwjPJkiHH;
      string sipEePnQBl;
      string StcsuRyynb;
      string pLqSoOplpF;
      string BqeepThepU;
      string RedHcSjCnx;
      string LlteRgrWOQ;
      string ZCawjbOxDb;
      string jSHTKLhjpW;
      string emxrsPwANI;
      string bKPZuOEgWA;
      string ElzMNrdaTF;
      string zHfrklEhDU;
      if(rgchUXbrdl == pLqSoOplpF){eNjtzYChXu = true;}
      else if(pLqSoOplpF == rgchUXbrdl){ajWzDPuNrs = true;}
      if(PRwRmtdZiF == BqeepThepU){HBMoRrnkeA = true;}
      else if(BqeepThepU == PRwRmtdZiF){oZTXHGhyEt = true;}
      if(rFHptkTEHI == RedHcSjCnx){kVfHJTeXnI = true;}
      else if(RedHcSjCnx == rFHptkTEHI){SuqHSPOquz = true;}
      if(CJVQYrgPcz == LlteRgrWOQ){KVdCVpCEMn = true;}
      else if(LlteRgrWOQ == CJVQYrgPcz){mgTuknQxqu = true;}
      if(ohUYhlqjNC == ZCawjbOxDb){pwCYyxupas = true;}
      else if(ZCawjbOxDb == ohUYhlqjNC){uEiZXhGwYn = true;}
      if(cmVFOmZmmi == jSHTKLhjpW){yTDCiIhbjf = true;}
      else if(jSHTKLhjpW == cmVFOmZmmi){cDhstesPfm = true;}
      if(DXjVjFwfsu == emxrsPwANI){tesPkkWKTb = true;}
      else if(emxrsPwANI == DXjVjFwfsu){ADRsGHGXlT = true;}
      if(NNwjPJkiHH == bKPZuOEgWA){piXpKoTHIL = true;}
      if(sipEePnQBl == ElzMNrdaTF){YnwuKpSaTM = true;}
      if(StcsuRyynb == zHfrklEhDU){IZTftLCmmN = true;}
      while(bKPZuOEgWA == NNwjPJkiHH){ojGJzNMRij = true;}
      while(ElzMNrdaTF == ElzMNrdaTF){JSSHVizaAG = true;}
      while(zHfrklEhDU == zHfrklEhDU){tBREtqmpSP = true;}
      if(eNjtzYChXu == true){eNjtzYChXu = false;}
      if(HBMoRrnkeA == true){HBMoRrnkeA = false;}
      if(kVfHJTeXnI == true){kVfHJTeXnI = false;}
      if(KVdCVpCEMn == true){KVdCVpCEMn = false;}
      if(pwCYyxupas == true){pwCYyxupas = false;}
      if(yTDCiIhbjf == true){yTDCiIhbjf = false;}
      if(tesPkkWKTb == true){tesPkkWKTb = false;}
      if(piXpKoTHIL == true){piXpKoTHIL = false;}
      if(YnwuKpSaTM == true){YnwuKpSaTM = false;}
      if(IZTftLCmmN == true){IZTftLCmmN = false;}
      if(ajWzDPuNrs == true){ajWzDPuNrs = false;}
      if(oZTXHGhyEt == true){oZTXHGhyEt = false;}
      if(SuqHSPOquz == true){SuqHSPOquz = false;}
      if(mgTuknQxqu == true){mgTuknQxqu = false;}
      if(uEiZXhGwYn == true){uEiZXhGwYn = false;}
      if(cDhstesPfm == true){cDhstesPfm = false;}
      if(ADRsGHGXlT == true){ADRsGHGXlT = false;}
      if(ojGJzNMRij == true){ojGJzNMRij = false;}
      if(JSSHVizaAG == true){JSSHVizaAG = false;}
      if(tBREtqmpSP == true){tBREtqmpSP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNNHXOWWEE
{ 
  void ceSZikLXXg()
  { 
      bool aYwQCcLrAi = false;
      bool okMfXQMewT = false;
      bool NtCfErXsdT = false;
      bool ryrJyLqDtf = false;
      bool OktVmZhsgC = false;
      bool SORBlfWQLK = false;
      bool EROgpprDgL = false;
      bool YIkQEczfre = false;
      bool JeMaAdfqWR = false;
      bool oaqjaxWNfw = false;
      bool heMUcJdBwJ = false;
      bool fqXgAZFmfL = false;
      bool JAfOWyRAoH = false;
      bool FlAuweSqxq = false;
      bool AeuNkxCKjB = false;
      bool qihTmhyxye = false;
      bool rcLnDtpbjU = false;
      bool GOpoLeESdY = false;
      bool uGQnPWEgIO = false;
      bool fVrSyXTGJq = false;
      string XOZEiQQuGi;
      string ogqxnjqTfq;
      string YiVkxbTOuM;
      string eqmYruDCNt;
      string EUEOdfrdoH;
      string nmCbgoroHH;
      string wCzsDysSFs;
      string goFllEdGGR;
      string ipZnXrnKqD;
      string COuFxCUKLf;
      string lZYuazgQpc;
      string KkhoYGbLVK;
      string JibBpRtAnj;
      string iSuafIRdNY;
      string LWUNrQfFfq;
      string aJoAVDyWFI;
      string FfcFsrpHIP;
      string nxyxzmNNJZ;
      string knTxJZduEc;
      string KuYETetOUA;
      if(XOZEiQQuGi == lZYuazgQpc){aYwQCcLrAi = true;}
      else if(lZYuazgQpc == XOZEiQQuGi){heMUcJdBwJ = true;}
      if(ogqxnjqTfq == KkhoYGbLVK){okMfXQMewT = true;}
      else if(KkhoYGbLVK == ogqxnjqTfq){fqXgAZFmfL = true;}
      if(YiVkxbTOuM == JibBpRtAnj){NtCfErXsdT = true;}
      else if(JibBpRtAnj == YiVkxbTOuM){JAfOWyRAoH = true;}
      if(eqmYruDCNt == iSuafIRdNY){ryrJyLqDtf = true;}
      else if(iSuafIRdNY == eqmYruDCNt){FlAuweSqxq = true;}
      if(EUEOdfrdoH == LWUNrQfFfq){OktVmZhsgC = true;}
      else if(LWUNrQfFfq == EUEOdfrdoH){AeuNkxCKjB = true;}
      if(nmCbgoroHH == aJoAVDyWFI){SORBlfWQLK = true;}
      else if(aJoAVDyWFI == nmCbgoroHH){qihTmhyxye = true;}
      if(wCzsDysSFs == FfcFsrpHIP){EROgpprDgL = true;}
      else if(FfcFsrpHIP == wCzsDysSFs){rcLnDtpbjU = true;}
      if(goFllEdGGR == nxyxzmNNJZ){YIkQEczfre = true;}
      if(ipZnXrnKqD == knTxJZduEc){JeMaAdfqWR = true;}
      if(COuFxCUKLf == KuYETetOUA){oaqjaxWNfw = true;}
      while(nxyxzmNNJZ == goFllEdGGR){GOpoLeESdY = true;}
      while(knTxJZduEc == knTxJZduEc){uGQnPWEgIO = true;}
      while(KuYETetOUA == KuYETetOUA){fVrSyXTGJq = true;}
      if(aYwQCcLrAi == true){aYwQCcLrAi = false;}
      if(okMfXQMewT == true){okMfXQMewT = false;}
      if(NtCfErXsdT == true){NtCfErXsdT = false;}
      if(ryrJyLqDtf == true){ryrJyLqDtf = false;}
      if(OktVmZhsgC == true){OktVmZhsgC = false;}
      if(SORBlfWQLK == true){SORBlfWQLK = false;}
      if(EROgpprDgL == true){EROgpprDgL = false;}
      if(YIkQEczfre == true){YIkQEczfre = false;}
      if(JeMaAdfqWR == true){JeMaAdfqWR = false;}
      if(oaqjaxWNfw == true){oaqjaxWNfw = false;}
      if(heMUcJdBwJ == true){heMUcJdBwJ = false;}
      if(fqXgAZFmfL == true){fqXgAZFmfL = false;}
      if(JAfOWyRAoH == true){JAfOWyRAoH = false;}
      if(FlAuweSqxq == true){FlAuweSqxq = false;}
      if(AeuNkxCKjB == true){AeuNkxCKjB = false;}
      if(qihTmhyxye == true){qihTmhyxye = false;}
      if(rcLnDtpbjU == true){rcLnDtpbjU = false;}
      if(GOpoLeESdY == true){GOpoLeESdY = false;}
      if(uGQnPWEgIO == true){uGQnPWEgIO = false;}
      if(fVrSyXTGJq == true){fVrSyXTGJq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WHHFGCCXOW
{ 
  void LPOkgaJMlF()
  { 
      bool pIzuUVKFfD = false;
      bool VYryuEVXds = false;
      bool VlnntlehZW = false;
      bool hrJDnaayaD = false;
      bool TqBogTpFAZ = false;
      bool dKOdmDUKBi = false;
      bool pbeJVcOnKU = false;
      bool dWxaZdkyHZ = false;
      bool uZhzsWceQk = false;
      bool FPwrNqMqSD = false;
      bool ECufwGNnEJ = false;
      bool RVCamPteQz = false;
      bool zjWYONZEMh = false;
      bool RteEUseBDl = false;
      bool IoaHSiNVFx = false;
      bool xgZTDUeVQh = false;
      bool fJbWqXpyFt = false;
      bool jrbepKJPGe = false;
      bool AEzOkkTLAA = false;
      bool NJkVGzMDPt = false;
      string neSUDFjjfo;
      string ghNzuxJjak;
      string ueCUOjPUyK;
      string wDQuJqkzmo;
      string kfweRKBiVR;
      string EosjGIbyGT;
      string oPlVrdRRpD;
      string MJwlAOhWCD;
      string hgyfFHKgnB;
      string OlsTzVtamn;
      string rjsRFurGir;
      string ZEuCkIQFPk;
      string TjdnoZQcme;
      string THjNKymgaK;
      string ODywaKpphp;
      string FoKCUIFEce;
      string ePTEXRUhql;
      string UidFVQlgMd;
      string iZtwZewhsC;
      string rhDwezisXI;
      if(neSUDFjjfo == rjsRFurGir){pIzuUVKFfD = true;}
      else if(rjsRFurGir == neSUDFjjfo){ECufwGNnEJ = true;}
      if(ghNzuxJjak == ZEuCkIQFPk){VYryuEVXds = true;}
      else if(ZEuCkIQFPk == ghNzuxJjak){RVCamPteQz = true;}
      if(ueCUOjPUyK == TjdnoZQcme){VlnntlehZW = true;}
      else if(TjdnoZQcme == ueCUOjPUyK){zjWYONZEMh = true;}
      if(wDQuJqkzmo == THjNKymgaK){hrJDnaayaD = true;}
      else if(THjNKymgaK == wDQuJqkzmo){RteEUseBDl = true;}
      if(kfweRKBiVR == ODywaKpphp){TqBogTpFAZ = true;}
      else if(ODywaKpphp == kfweRKBiVR){IoaHSiNVFx = true;}
      if(EosjGIbyGT == FoKCUIFEce){dKOdmDUKBi = true;}
      else if(FoKCUIFEce == EosjGIbyGT){xgZTDUeVQh = true;}
      if(oPlVrdRRpD == ePTEXRUhql){pbeJVcOnKU = true;}
      else if(ePTEXRUhql == oPlVrdRRpD){fJbWqXpyFt = true;}
      if(MJwlAOhWCD == UidFVQlgMd){dWxaZdkyHZ = true;}
      if(hgyfFHKgnB == iZtwZewhsC){uZhzsWceQk = true;}
      if(OlsTzVtamn == rhDwezisXI){FPwrNqMqSD = true;}
      while(UidFVQlgMd == MJwlAOhWCD){jrbepKJPGe = true;}
      while(iZtwZewhsC == iZtwZewhsC){AEzOkkTLAA = true;}
      while(rhDwezisXI == rhDwezisXI){NJkVGzMDPt = true;}
      if(pIzuUVKFfD == true){pIzuUVKFfD = false;}
      if(VYryuEVXds == true){VYryuEVXds = false;}
      if(VlnntlehZW == true){VlnntlehZW = false;}
      if(hrJDnaayaD == true){hrJDnaayaD = false;}
      if(TqBogTpFAZ == true){TqBogTpFAZ = false;}
      if(dKOdmDUKBi == true){dKOdmDUKBi = false;}
      if(pbeJVcOnKU == true){pbeJVcOnKU = false;}
      if(dWxaZdkyHZ == true){dWxaZdkyHZ = false;}
      if(uZhzsWceQk == true){uZhzsWceQk = false;}
      if(FPwrNqMqSD == true){FPwrNqMqSD = false;}
      if(ECufwGNnEJ == true){ECufwGNnEJ = false;}
      if(RVCamPteQz == true){RVCamPteQz = false;}
      if(zjWYONZEMh == true){zjWYONZEMh = false;}
      if(RteEUseBDl == true){RteEUseBDl = false;}
      if(IoaHSiNVFx == true){IoaHSiNVFx = false;}
      if(xgZTDUeVQh == true){xgZTDUeVQh = false;}
      if(fJbWqXpyFt == true){fJbWqXpyFt = false;}
      if(jrbepKJPGe == true){jrbepKJPGe = false;}
      if(AEzOkkTLAA == true){AEzOkkTLAA = false;}
      if(NJkVGzMDPt == true){NJkVGzMDPt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PAKNLBMFKI
{ 
  void MXrOjIgIcJ()
  { 
      bool DnogWcKHAj = false;
      bool dqGoRlpZEM = false;
      bool elXpxSaIZG = false;
      bool YEBWZcucXa = false;
      bool NLQIkjsJqO = false;
      bool nHJZBRPziD = false;
      bool CCgsKZpiPn = false;
      bool pNBcyTVPEN = false;
      bool ZQQLRRuaVI = false;
      bool NwsTXLdWxK = false;
      bool sJtCXaGfbg = false;
      bool uAtVdkkVbs = false;
      bool ePMHatUgEl = false;
      bool ozRtTPWNmq = false;
      bool KOzoNMBWpl = false;
      bool ZHuDfcwmbc = false;
      bool GYaoqwhACN = false;
      bool OWijhPPXtN = false;
      bool sxqRMgDONp = false;
      bool TjlKklnKxQ = false;
      string bbkQpqntuS;
      string diFbSXMQCT;
      string frRzFLKXkU;
      string IOIiNWsVPz;
      string OtIMPKNGAl;
      string sOHVXiKlLe;
      string gQIaJPZVNw;
      string epACFliEju;
      string yDWzasGlKe;
      string LHKkSxkhCz;
      string jqsDGCOEQl;
      string zFBPfcsJzQ;
      string InLijXeOjH;
      string ABCjLHKSrX;
      string eBVXeGFtFo;
      string DbhlqweKTi;
      string WzUIkyCREY;
      string SZQalGRmDd;
      string RkJtEYSQsO;
      string bzzIBegNlf;
      if(bbkQpqntuS == jqsDGCOEQl){DnogWcKHAj = true;}
      else if(jqsDGCOEQl == bbkQpqntuS){sJtCXaGfbg = true;}
      if(diFbSXMQCT == zFBPfcsJzQ){dqGoRlpZEM = true;}
      else if(zFBPfcsJzQ == diFbSXMQCT){uAtVdkkVbs = true;}
      if(frRzFLKXkU == InLijXeOjH){elXpxSaIZG = true;}
      else if(InLijXeOjH == frRzFLKXkU){ePMHatUgEl = true;}
      if(IOIiNWsVPz == ABCjLHKSrX){YEBWZcucXa = true;}
      else if(ABCjLHKSrX == IOIiNWsVPz){ozRtTPWNmq = true;}
      if(OtIMPKNGAl == eBVXeGFtFo){NLQIkjsJqO = true;}
      else if(eBVXeGFtFo == OtIMPKNGAl){KOzoNMBWpl = true;}
      if(sOHVXiKlLe == DbhlqweKTi){nHJZBRPziD = true;}
      else if(DbhlqweKTi == sOHVXiKlLe){ZHuDfcwmbc = true;}
      if(gQIaJPZVNw == WzUIkyCREY){CCgsKZpiPn = true;}
      else if(WzUIkyCREY == gQIaJPZVNw){GYaoqwhACN = true;}
      if(epACFliEju == SZQalGRmDd){pNBcyTVPEN = true;}
      if(yDWzasGlKe == RkJtEYSQsO){ZQQLRRuaVI = true;}
      if(LHKkSxkhCz == bzzIBegNlf){NwsTXLdWxK = true;}
      while(SZQalGRmDd == epACFliEju){OWijhPPXtN = true;}
      while(RkJtEYSQsO == RkJtEYSQsO){sxqRMgDONp = true;}
      while(bzzIBegNlf == bzzIBegNlf){TjlKklnKxQ = true;}
      if(DnogWcKHAj == true){DnogWcKHAj = false;}
      if(dqGoRlpZEM == true){dqGoRlpZEM = false;}
      if(elXpxSaIZG == true){elXpxSaIZG = false;}
      if(YEBWZcucXa == true){YEBWZcucXa = false;}
      if(NLQIkjsJqO == true){NLQIkjsJqO = false;}
      if(nHJZBRPziD == true){nHJZBRPziD = false;}
      if(CCgsKZpiPn == true){CCgsKZpiPn = false;}
      if(pNBcyTVPEN == true){pNBcyTVPEN = false;}
      if(ZQQLRRuaVI == true){ZQQLRRuaVI = false;}
      if(NwsTXLdWxK == true){NwsTXLdWxK = false;}
      if(sJtCXaGfbg == true){sJtCXaGfbg = false;}
      if(uAtVdkkVbs == true){uAtVdkkVbs = false;}
      if(ePMHatUgEl == true){ePMHatUgEl = false;}
      if(ozRtTPWNmq == true){ozRtTPWNmq = false;}
      if(KOzoNMBWpl == true){KOzoNMBWpl = false;}
      if(ZHuDfcwmbc == true){ZHuDfcwmbc = false;}
      if(GYaoqwhACN == true){GYaoqwhACN = false;}
      if(OWijhPPXtN == true){OWijhPPXtN = false;}
      if(sxqRMgDONp == true){sxqRMgDONp = false;}
      if(TjlKklnKxQ == true){TjlKklnKxQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RIZCNSUIAQ
{ 
  void gpLomHBYwM()
  { 
      bool lKSfRAYDZm = false;
      bool KiQVdMkmLG = false;
      bool sjAYEOybff = false;
      bool INzeuTchHp = false;
      bool bdTjlBGtkz = false;
      bool QZTybCJtaC = false;
      bool CwXsdwjlZK = false;
      bool iDfUeOQQlD = false;
      bool IDqfOhtBCs = false;
      bool JhHEnfGZFo = false;
      bool RUTaPNsyTN = false;
      bool ksHWtyFqew = false;
      bool BiigBBuagy = false;
      bool IpLxlnjPQA = false;
      bool nugoHQajKo = false;
      bool ZPuJmhklZO = false;
      bool SSQUFugKkG = false;
      bool OoadHFBtZj = false;
      bool aLQrYrtCJD = false;
      bool CxpChVeMjL = false;
      string CyughzQTVR;
      string bSSkWZDxVx;
      string pOTFeoRPKx;
      string rOANmbbKcM;
      string wpeUSyKNwS;
      string kEyJZmepBs;
      string gAIYZMSExu;
      string yrTIBziylg;
      string dETrMmQpmA;
      string xlIjfuhGuF;
      string fFPAUrjoIZ;
      string DgDUObgQLl;
      string wbRxxLjjcF;
      string RcCfAYoSXT;
      string DahMwQhnVD;
      string OQuIJEnRCI;
      string IAMCHadXUo;
      string lNrqiVsEAg;
      string duOYqBhsWw;
      string kXPPLCNeFV;
      if(CyughzQTVR == fFPAUrjoIZ){lKSfRAYDZm = true;}
      else if(fFPAUrjoIZ == CyughzQTVR){RUTaPNsyTN = true;}
      if(bSSkWZDxVx == DgDUObgQLl){KiQVdMkmLG = true;}
      else if(DgDUObgQLl == bSSkWZDxVx){ksHWtyFqew = true;}
      if(pOTFeoRPKx == wbRxxLjjcF){sjAYEOybff = true;}
      else if(wbRxxLjjcF == pOTFeoRPKx){BiigBBuagy = true;}
      if(rOANmbbKcM == RcCfAYoSXT){INzeuTchHp = true;}
      else if(RcCfAYoSXT == rOANmbbKcM){IpLxlnjPQA = true;}
      if(wpeUSyKNwS == DahMwQhnVD){bdTjlBGtkz = true;}
      else if(DahMwQhnVD == wpeUSyKNwS){nugoHQajKo = true;}
      if(kEyJZmepBs == OQuIJEnRCI){QZTybCJtaC = true;}
      else if(OQuIJEnRCI == kEyJZmepBs){ZPuJmhklZO = true;}
      if(gAIYZMSExu == IAMCHadXUo){CwXsdwjlZK = true;}
      else if(IAMCHadXUo == gAIYZMSExu){SSQUFugKkG = true;}
      if(yrTIBziylg == lNrqiVsEAg){iDfUeOQQlD = true;}
      if(dETrMmQpmA == duOYqBhsWw){IDqfOhtBCs = true;}
      if(xlIjfuhGuF == kXPPLCNeFV){JhHEnfGZFo = true;}
      while(lNrqiVsEAg == yrTIBziylg){OoadHFBtZj = true;}
      while(duOYqBhsWw == duOYqBhsWw){aLQrYrtCJD = true;}
      while(kXPPLCNeFV == kXPPLCNeFV){CxpChVeMjL = true;}
      if(lKSfRAYDZm == true){lKSfRAYDZm = false;}
      if(KiQVdMkmLG == true){KiQVdMkmLG = false;}
      if(sjAYEOybff == true){sjAYEOybff = false;}
      if(INzeuTchHp == true){INzeuTchHp = false;}
      if(bdTjlBGtkz == true){bdTjlBGtkz = false;}
      if(QZTybCJtaC == true){QZTybCJtaC = false;}
      if(CwXsdwjlZK == true){CwXsdwjlZK = false;}
      if(iDfUeOQQlD == true){iDfUeOQQlD = false;}
      if(IDqfOhtBCs == true){IDqfOhtBCs = false;}
      if(JhHEnfGZFo == true){JhHEnfGZFo = false;}
      if(RUTaPNsyTN == true){RUTaPNsyTN = false;}
      if(ksHWtyFqew == true){ksHWtyFqew = false;}
      if(BiigBBuagy == true){BiigBBuagy = false;}
      if(IpLxlnjPQA == true){IpLxlnjPQA = false;}
      if(nugoHQajKo == true){nugoHQajKo = false;}
      if(ZPuJmhklZO == true){ZPuJmhklZO = false;}
      if(SSQUFugKkG == true){SSQUFugKkG = false;}
      if(OoadHFBtZj == true){OoadHFBtZj = false;}
      if(aLQrYrtCJD == true){aLQrYrtCJD = false;}
      if(CxpChVeMjL == true){CxpChVeMjL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TRCBSWTULX
{ 
  void ZDPqRfLKjl()
  { 
      bool NuNzLtVSMR = false;
      bool aeVhcOZBFp = false;
      bool iaHHxPaxmg = false;
      bool yMdCGPWzRT = false;
      bool YFKaoIKIEh = false;
      bool auTJVmnFBw = false;
      bool SXeeSOATaM = false;
      bool rZjlQdQgSo = false;
      bool FSsEGDsUfT = false;
      bool bQxVABaeHZ = false;
      bool HpgrpAKgrr = false;
      bool WGmMpAeaXP = false;
      bool VemHjabOkP = false;
      bool DkYrgOkAOG = false;
      bool rLcnxUdkez = false;
      bool WzGrEcDZHO = false;
      bool Xuwcokhtfb = false;
      bool PdLRWJCzJP = false;
      bool xqjkrDefnE = false;
      bool LKszhxPAyM = false;
      string jiCHjwKCxT;
      string dqjHQSWUgE;
      string brCAifdVey;
      string jKZBoIGMUg;
      string JbhjFLJSrK;
      string fFQmhrgCYD;
      string RnXzjSRiSH;
      string MJzAtAJRtW;
      string WKdUSdslSw;
      string aEnQOVEiAm;
      string sZAjxVGQrg;
      string hOHCgGKCgF;
      string YfPVgIVhkY;
      string waRGdwKsWw;
      string XcskNLwkjH;
      string KBCtNNJdDo;
      string zXeTkHxAXj;
      string wQfjhwleIU;
      string LjycNtXWrQ;
      string mfphxAxZAF;
      if(jiCHjwKCxT == sZAjxVGQrg){NuNzLtVSMR = true;}
      else if(sZAjxVGQrg == jiCHjwKCxT){HpgrpAKgrr = true;}
      if(dqjHQSWUgE == hOHCgGKCgF){aeVhcOZBFp = true;}
      else if(hOHCgGKCgF == dqjHQSWUgE){WGmMpAeaXP = true;}
      if(brCAifdVey == YfPVgIVhkY){iaHHxPaxmg = true;}
      else if(YfPVgIVhkY == brCAifdVey){VemHjabOkP = true;}
      if(jKZBoIGMUg == waRGdwKsWw){yMdCGPWzRT = true;}
      else if(waRGdwKsWw == jKZBoIGMUg){DkYrgOkAOG = true;}
      if(JbhjFLJSrK == XcskNLwkjH){YFKaoIKIEh = true;}
      else if(XcskNLwkjH == JbhjFLJSrK){rLcnxUdkez = true;}
      if(fFQmhrgCYD == KBCtNNJdDo){auTJVmnFBw = true;}
      else if(KBCtNNJdDo == fFQmhrgCYD){WzGrEcDZHO = true;}
      if(RnXzjSRiSH == zXeTkHxAXj){SXeeSOATaM = true;}
      else if(zXeTkHxAXj == RnXzjSRiSH){Xuwcokhtfb = true;}
      if(MJzAtAJRtW == wQfjhwleIU){rZjlQdQgSo = true;}
      if(WKdUSdslSw == LjycNtXWrQ){FSsEGDsUfT = true;}
      if(aEnQOVEiAm == mfphxAxZAF){bQxVABaeHZ = true;}
      while(wQfjhwleIU == MJzAtAJRtW){PdLRWJCzJP = true;}
      while(LjycNtXWrQ == LjycNtXWrQ){xqjkrDefnE = true;}
      while(mfphxAxZAF == mfphxAxZAF){LKszhxPAyM = true;}
      if(NuNzLtVSMR == true){NuNzLtVSMR = false;}
      if(aeVhcOZBFp == true){aeVhcOZBFp = false;}
      if(iaHHxPaxmg == true){iaHHxPaxmg = false;}
      if(yMdCGPWzRT == true){yMdCGPWzRT = false;}
      if(YFKaoIKIEh == true){YFKaoIKIEh = false;}
      if(auTJVmnFBw == true){auTJVmnFBw = false;}
      if(SXeeSOATaM == true){SXeeSOATaM = false;}
      if(rZjlQdQgSo == true){rZjlQdQgSo = false;}
      if(FSsEGDsUfT == true){FSsEGDsUfT = false;}
      if(bQxVABaeHZ == true){bQxVABaeHZ = false;}
      if(HpgrpAKgrr == true){HpgrpAKgrr = false;}
      if(WGmMpAeaXP == true){WGmMpAeaXP = false;}
      if(VemHjabOkP == true){VemHjabOkP = false;}
      if(DkYrgOkAOG == true){DkYrgOkAOG = false;}
      if(rLcnxUdkez == true){rLcnxUdkez = false;}
      if(WzGrEcDZHO == true){WzGrEcDZHO = false;}
      if(Xuwcokhtfb == true){Xuwcokhtfb = false;}
      if(PdLRWJCzJP == true){PdLRWJCzJP = false;}
      if(xqjkrDefnE == true){xqjkrDefnE = false;}
      if(LKszhxPAyM == true){LKszhxPAyM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JOORTVFBZZ
{ 
  void BYDJGaXVzp()
  { 
      bool cWRYzuOWzq = false;
      bool VCxWBbePSF = false;
      bool cNyTuhUcVt = false;
      bool AGXcByjwpp = false;
      bool kuHkVZTOGX = false;
      bool cXfTAPYydQ = false;
      bool akAEpPdUUD = false;
      bool qhYcTgFMyV = false;
      bool OFWyRcZEcl = false;
      bool YlSZPAuDuF = false;
      bool uzsDftzCAT = false;
      bool JLAHCUOBlM = false;
      bool oZridFOzNS = false;
      bool kCRrZOMTRX = false;
      bool dXEIbNkKWt = false;
      bool lsRhQVHKYa = false;
      bool eAoghHtIgm = false;
      bool HtiNiRUiGP = false;
      bool UDbSgrjibE = false;
      bool HCtqrchXaT = false;
      string kNySqgCpUu;
      string HPVxWdWMGd;
      string NdRxmpDtHh;
      string JnNIlVfkxx;
      string Axcxeknwem;
      string uhCTWHwAeB;
      string cHhllSBMLB;
      string ykOIdPBTSB;
      string CHPTmalske;
      string YeFwUrOqLL;
      string iakcoJTspG;
      string FbhczVrOzK;
      string gIafbSeSnk;
      string AKHHSaVldc;
      string HrDeYxxcxy;
      string AArBeazEBW;
      string dAFEFuTaKX;
      string zFkVCnFwGe;
      string UCVpkASGbq;
      string bRkHzHmzYd;
      if(kNySqgCpUu == iakcoJTspG){cWRYzuOWzq = true;}
      else if(iakcoJTspG == kNySqgCpUu){uzsDftzCAT = true;}
      if(HPVxWdWMGd == FbhczVrOzK){VCxWBbePSF = true;}
      else if(FbhczVrOzK == HPVxWdWMGd){JLAHCUOBlM = true;}
      if(NdRxmpDtHh == gIafbSeSnk){cNyTuhUcVt = true;}
      else if(gIafbSeSnk == NdRxmpDtHh){oZridFOzNS = true;}
      if(JnNIlVfkxx == AKHHSaVldc){AGXcByjwpp = true;}
      else if(AKHHSaVldc == JnNIlVfkxx){kCRrZOMTRX = true;}
      if(Axcxeknwem == HrDeYxxcxy){kuHkVZTOGX = true;}
      else if(HrDeYxxcxy == Axcxeknwem){dXEIbNkKWt = true;}
      if(uhCTWHwAeB == AArBeazEBW){cXfTAPYydQ = true;}
      else if(AArBeazEBW == uhCTWHwAeB){lsRhQVHKYa = true;}
      if(cHhllSBMLB == dAFEFuTaKX){akAEpPdUUD = true;}
      else if(dAFEFuTaKX == cHhllSBMLB){eAoghHtIgm = true;}
      if(ykOIdPBTSB == zFkVCnFwGe){qhYcTgFMyV = true;}
      if(CHPTmalske == UCVpkASGbq){OFWyRcZEcl = true;}
      if(YeFwUrOqLL == bRkHzHmzYd){YlSZPAuDuF = true;}
      while(zFkVCnFwGe == ykOIdPBTSB){HtiNiRUiGP = true;}
      while(UCVpkASGbq == UCVpkASGbq){UDbSgrjibE = true;}
      while(bRkHzHmzYd == bRkHzHmzYd){HCtqrchXaT = true;}
      if(cWRYzuOWzq == true){cWRYzuOWzq = false;}
      if(VCxWBbePSF == true){VCxWBbePSF = false;}
      if(cNyTuhUcVt == true){cNyTuhUcVt = false;}
      if(AGXcByjwpp == true){AGXcByjwpp = false;}
      if(kuHkVZTOGX == true){kuHkVZTOGX = false;}
      if(cXfTAPYydQ == true){cXfTAPYydQ = false;}
      if(akAEpPdUUD == true){akAEpPdUUD = false;}
      if(qhYcTgFMyV == true){qhYcTgFMyV = false;}
      if(OFWyRcZEcl == true){OFWyRcZEcl = false;}
      if(YlSZPAuDuF == true){YlSZPAuDuF = false;}
      if(uzsDftzCAT == true){uzsDftzCAT = false;}
      if(JLAHCUOBlM == true){JLAHCUOBlM = false;}
      if(oZridFOzNS == true){oZridFOzNS = false;}
      if(kCRrZOMTRX == true){kCRrZOMTRX = false;}
      if(dXEIbNkKWt == true){dXEIbNkKWt = false;}
      if(lsRhQVHKYa == true){lsRhQVHKYa = false;}
      if(eAoghHtIgm == true){eAoghHtIgm = false;}
      if(HtiNiRUiGP == true){HtiNiRUiGP = false;}
      if(UDbSgrjibE == true){UDbSgrjibE = false;}
      if(HCtqrchXaT == true){HCtqrchXaT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HWOMDBPLZK
{ 
  void BnwFPkpStZ()
  { 
      bool gCgOIudguV = false;
      bool bJamJIaPKU = false;
      bool YBSWpqDEkJ = false;
      bool HWdHwgAtPP = false;
      bool MUVVzmwVfD = false;
      bool mNtJgeiJXQ = false;
      bool qZwlOEfTpc = false;
      bool IgzuIDfxWD = false;
      bool thXgWscTaQ = false;
      bool xpVzXlXiHu = false;
      bool HceDuGOzBc = false;
      bool zllUVJBPOU = false;
      bool bLsZeRKAWV = false;
      bool fwobwRCTlQ = false;
      bool ecRxRLDBcN = false;
      bool kIUmSujEYc = false;
      bool uNbfxCwJXD = false;
      bool GhdyoysuHT = false;
      bool NJXJkWbCIB = false;
      bool hyuIVRBlAO = false;
      string FLEVIhsDbZ;
      string lZnnKYsHSE;
      string knhdGWLptZ;
      string IgJTGfAXpW;
      string uOdHRVnQXQ;
      string WNexzRcZOk;
      string WCIBRFPUhe;
      string YUQuJVJaMk;
      string huRcDuBMUn;
      string CaIFArFcpM;
      string GShsrBwimc;
      string HCMdCbkfyW;
      string DCAscyMLuR;
      string QgjAePMYjB;
      string yRZqfzNeCX;
      string GZdTIDSnPt;
      string ojnUMaSLym;
      string PLuwXlbIMc;
      string jgJXKqCQra;
      string wXIpLNdEeF;
      if(FLEVIhsDbZ == GShsrBwimc){gCgOIudguV = true;}
      else if(GShsrBwimc == FLEVIhsDbZ){HceDuGOzBc = true;}
      if(lZnnKYsHSE == HCMdCbkfyW){bJamJIaPKU = true;}
      else if(HCMdCbkfyW == lZnnKYsHSE){zllUVJBPOU = true;}
      if(knhdGWLptZ == DCAscyMLuR){YBSWpqDEkJ = true;}
      else if(DCAscyMLuR == knhdGWLptZ){bLsZeRKAWV = true;}
      if(IgJTGfAXpW == QgjAePMYjB){HWdHwgAtPP = true;}
      else if(QgjAePMYjB == IgJTGfAXpW){fwobwRCTlQ = true;}
      if(uOdHRVnQXQ == yRZqfzNeCX){MUVVzmwVfD = true;}
      else if(yRZqfzNeCX == uOdHRVnQXQ){ecRxRLDBcN = true;}
      if(WNexzRcZOk == GZdTIDSnPt){mNtJgeiJXQ = true;}
      else if(GZdTIDSnPt == WNexzRcZOk){kIUmSujEYc = true;}
      if(WCIBRFPUhe == ojnUMaSLym){qZwlOEfTpc = true;}
      else if(ojnUMaSLym == WCIBRFPUhe){uNbfxCwJXD = true;}
      if(YUQuJVJaMk == PLuwXlbIMc){IgzuIDfxWD = true;}
      if(huRcDuBMUn == jgJXKqCQra){thXgWscTaQ = true;}
      if(CaIFArFcpM == wXIpLNdEeF){xpVzXlXiHu = true;}
      while(PLuwXlbIMc == YUQuJVJaMk){GhdyoysuHT = true;}
      while(jgJXKqCQra == jgJXKqCQra){NJXJkWbCIB = true;}
      while(wXIpLNdEeF == wXIpLNdEeF){hyuIVRBlAO = true;}
      if(gCgOIudguV == true){gCgOIudguV = false;}
      if(bJamJIaPKU == true){bJamJIaPKU = false;}
      if(YBSWpqDEkJ == true){YBSWpqDEkJ = false;}
      if(HWdHwgAtPP == true){HWdHwgAtPP = false;}
      if(MUVVzmwVfD == true){MUVVzmwVfD = false;}
      if(mNtJgeiJXQ == true){mNtJgeiJXQ = false;}
      if(qZwlOEfTpc == true){qZwlOEfTpc = false;}
      if(IgzuIDfxWD == true){IgzuIDfxWD = false;}
      if(thXgWscTaQ == true){thXgWscTaQ = false;}
      if(xpVzXlXiHu == true){xpVzXlXiHu = false;}
      if(HceDuGOzBc == true){HceDuGOzBc = false;}
      if(zllUVJBPOU == true){zllUVJBPOU = false;}
      if(bLsZeRKAWV == true){bLsZeRKAWV = false;}
      if(fwobwRCTlQ == true){fwobwRCTlQ = false;}
      if(ecRxRLDBcN == true){ecRxRLDBcN = false;}
      if(kIUmSujEYc == true){kIUmSujEYc = false;}
      if(uNbfxCwJXD == true){uNbfxCwJXD = false;}
      if(GhdyoysuHT == true){GhdyoysuHT = false;}
      if(NJXJkWbCIB == true){NJXJkWbCIB = false;}
      if(hyuIVRBlAO == true){hyuIVRBlAO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UAJNLUFUIS
{ 
  void FqKBswYmLe()
  { 
      bool yknnOBxesJ = false;
      bool gyPSgBOZNu = false;
      bool gqisOWzuIG = false;
      bool XdPhkttcNx = false;
      bool CCoJkbPaIC = false;
      bool kdWCnHBuZq = false;
      bool BBVmkDihgl = false;
      bool GlLPrdBYIl = false;
      bool HYmGVsGNtd = false;
      bool szCVwAfCYg = false;
      bool sgsWuzRHJJ = false;
      bool FblnjbOPRr = false;
      bool xVmDsHioTr = false;
      bool xzAarZfQKV = false;
      bool bzDjXQMOlT = false;
      bool lQjfjXtpcn = false;
      bool QbmRMFbLwK = false;
      bool wyEuQyRCeb = false;
      bool tTDAFgPTqU = false;
      bool fpmWFzLlXS = false;
      string pyAGcazyFs;
      string pKeyFjnreD;
      string xePXFwWFbr;
      string sGoEkQWcnU;
      string brIpBerSzs;
      string ghFihLibBg;
      string EsVNAiUaMo;
      string NLDJbEVZVZ;
      string EDFhKLBGVZ;
      string gtbHQhVupR;
      string KQFKfUduHd;
      string pJGacAnmCo;
      string gNFmHSjwss;
      string haiDOmyuCo;
      string hGzrjXmAdQ;
      string tirAjwLSCM;
      string kgCNuOZCLo;
      string CrkNHaOMCj;
      string fiRbzzhiSS;
      string aesoEADkxU;
      if(pyAGcazyFs == KQFKfUduHd){yknnOBxesJ = true;}
      else if(KQFKfUduHd == pyAGcazyFs){sgsWuzRHJJ = true;}
      if(pKeyFjnreD == pJGacAnmCo){gyPSgBOZNu = true;}
      else if(pJGacAnmCo == pKeyFjnreD){FblnjbOPRr = true;}
      if(xePXFwWFbr == gNFmHSjwss){gqisOWzuIG = true;}
      else if(gNFmHSjwss == xePXFwWFbr){xVmDsHioTr = true;}
      if(sGoEkQWcnU == haiDOmyuCo){XdPhkttcNx = true;}
      else if(haiDOmyuCo == sGoEkQWcnU){xzAarZfQKV = true;}
      if(brIpBerSzs == hGzrjXmAdQ){CCoJkbPaIC = true;}
      else if(hGzrjXmAdQ == brIpBerSzs){bzDjXQMOlT = true;}
      if(ghFihLibBg == tirAjwLSCM){kdWCnHBuZq = true;}
      else if(tirAjwLSCM == ghFihLibBg){lQjfjXtpcn = true;}
      if(EsVNAiUaMo == kgCNuOZCLo){BBVmkDihgl = true;}
      else if(kgCNuOZCLo == EsVNAiUaMo){QbmRMFbLwK = true;}
      if(NLDJbEVZVZ == CrkNHaOMCj){GlLPrdBYIl = true;}
      if(EDFhKLBGVZ == fiRbzzhiSS){HYmGVsGNtd = true;}
      if(gtbHQhVupR == aesoEADkxU){szCVwAfCYg = true;}
      while(CrkNHaOMCj == NLDJbEVZVZ){wyEuQyRCeb = true;}
      while(fiRbzzhiSS == fiRbzzhiSS){tTDAFgPTqU = true;}
      while(aesoEADkxU == aesoEADkxU){fpmWFzLlXS = true;}
      if(yknnOBxesJ == true){yknnOBxesJ = false;}
      if(gyPSgBOZNu == true){gyPSgBOZNu = false;}
      if(gqisOWzuIG == true){gqisOWzuIG = false;}
      if(XdPhkttcNx == true){XdPhkttcNx = false;}
      if(CCoJkbPaIC == true){CCoJkbPaIC = false;}
      if(kdWCnHBuZq == true){kdWCnHBuZq = false;}
      if(BBVmkDihgl == true){BBVmkDihgl = false;}
      if(GlLPrdBYIl == true){GlLPrdBYIl = false;}
      if(HYmGVsGNtd == true){HYmGVsGNtd = false;}
      if(szCVwAfCYg == true){szCVwAfCYg = false;}
      if(sgsWuzRHJJ == true){sgsWuzRHJJ = false;}
      if(FblnjbOPRr == true){FblnjbOPRr = false;}
      if(xVmDsHioTr == true){xVmDsHioTr = false;}
      if(xzAarZfQKV == true){xzAarZfQKV = false;}
      if(bzDjXQMOlT == true){bzDjXQMOlT = false;}
      if(lQjfjXtpcn == true){lQjfjXtpcn = false;}
      if(QbmRMFbLwK == true){QbmRMFbLwK = false;}
      if(wyEuQyRCeb == true){wyEuQyRCeb = false;}
      if(tTDAFgPTqU == true){tTDAFgPTqU = false;}
      if(fpmWFzLlXS == true){fpmWFzLlXS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZTFPERBVU
{ 
  void ANLpboFdOw()
  { 
      bool sQiWNSlygr = false;
      bool zNNtmnFeEu = false;
      bool WGPWCulGfW = false;
      bool YuWBFHWPDJ = false;
      bool nXPeOdjVWz = false;
      bool WhzHKlAMUR = false;
      bool geRKTDpLoe = false;
      bool QpauHyqkHX = false;
      bool KPjgzqwPqS = false;
      bool HKukbIGELK = false;
      bool mXfrhgGEzL = false;
      bool tOEwHQukKb = false;
      bool HaUVWGuoSz = false;
      bool rlZxkmjryS = false;
      bool jrPeXrGydL = false;
      bool MVtiDMDJUb = false;
      bool kQkASIoHLT = false;
      bool gDlqrOLoyd = false;
      bool AwKHlWqqsY = false;
      bool jZWWgSGOLP = false;
      string raeqLQYJlq;
      string ikDZNWPaxY;
      string ywPTrUbNPZ;
      string GLejFoCTgg;
      string shiluqEaOG;
      string SpiMOuLLzp;
      string nLtLjWFTTY;
      string TutPfQMdXA;
      string QBzIGQcSVJ;
      string dqTqrhnXBX;
      string lkGomWuTfx;
      string igmzZmMkET;
      string tlxJubbDWy;
      string cocANetJUj;
      string UIlXawDUQF;
      string VCSgczmwsL;
      string urwhUsDmkt;
      string rCQUzkAZiy;
      string YGlQcZVwWO;
      string rxQJncMECg;
      if(raeqLQYJlq == lkGomWuTfx){sQiWNSlygr = true;}
      else if(lkGomWuTfx == raeqLQYJlq){mXfrhgGEzL = true;}
      if(ikDZNWPaxY == igmzZmMkET){zNNtmnFeEu = true;}
      else if(igmzZmMkET == ikDZNWPaxY){tOEwHQukKb = true;}
      if(ywPTrUbNPZ == tlxJubbDWy){WGPWCulGfW = true;}
      else if(tlxJubbDWy == ywPTrUbNPZ){HaUVWGuoSz = true;}
      if(GLejFoCTgg == cocANetJUj){YuWBFHWPDJ = true;}
      else if(cocANetJUj == GLejFoCTgg){rlZxkmjryS = true;}
      if(shiluqEaOG == UIlXawDUQF){nXPeOdjVWz = true;}
      else if(UIlXawDUQF == shiluqEaOG){jrPeXrGydL = true;}
      if(SpiMOuLLzp == VCSgczmwsL){WhzHKlAMUR = true;}
      else if(VCSgczmwsL == SpiMOuLLzp){MVtiDMDJUb = true;}
      if(nLtLjWFTTY == urwhUsDmkt){geRKTDpLoe = true;}
      else if(urwhUsDmkt == nLtLjWFTTY){kQkASIoHLT = true;}
      if(TutPfQMdXA == rCQUzkAZiy){QpauHyqkHX = true;}
      if(QBzIGQcSVJ == YGlQcZVwWO){KPjgzqwPqS = true;}
      if(dqTqrhnXBX == rxQJncMECg){HKukbIGELK = true;}
      while(rCQUzkAZiy == TutPfQMdXA){gDlqrOLoyd = true;}
      while(YGlQcZVwWO == YGlQcZVwWO){AwKHlWqqsY = true;}
      while(rxQJncMECg == rxQJncMECg){jZWWgSGOLP = true;}
      if(sQiWNSlygr == true){sQiWNSlygr = false;}
      if(zNNtmnFeEu == true){zNNtmnFeEu = false;}
      if(WGPWCulGfW == true){WGPWCulGfW = false;}
      if(YuWBFHWPDJ == true){YuWBFHWPDJ = false;}
      if(nXPeOdjVWz == true){nXPeOdjVWz = false;}
      if(WhzHKlAMUR == true){WhzHKlAMUR = false;}
      if(geRKTDpLoe == true){geRKTDpLoe = false;}
      if(QpauHyqkHX == true){QpauHyqkHX = false;}
      if(KPjgzqwPqS == true){KPjgzqwPqS = false;}
      if(HKukbIGELK == true){HKukbIGELK = false;}
      if(mXfrhgGEzL == true){mXfrhgGEzL = false;}
      if(tOEwHQukKb == true){tOEwHQukKb = false;}
      if(HaUVWGuoSz == true){HaUVWGuoSz = false;}
      if(rlZxkmjryS == true){rlZxkmjryS = false;}
      if(jrPeXrGydL == true){jrPeXrGydL = false;}
      if(MVtiDMDJUb == true){MVtiDMDJUb = false;}
      if(kQkASIoHLT == true){kQkASIoHLT = false;}
      if(gDlqrOLoyd == true){gDlqrOLoyd = false;}
      if(AwKHlWqqsY == true){AwKHlWqqsY = false;}
      if(jZWWgSGOLP == true){jZWWgSGOLP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PENHNAANMA
{ 
  void WchMKTfrmE()
  { 
      bool IBhEreagGX = false;
      bool HpytUWqaMi = false;
      bool hgoMZTUJmo = false;
      bool ffAHIKZGue = false;
      bool rQbbFboSuy = false;
      bool bymfsaMUdX = false;
      bool JQsRrbpqlK = false;
      bool wkehpRENHx = false;
      bool dCOoNgsTNg = false;
      bool yFbWUbWKic = false;
      bool lyfkBpTFpb = false;
      bool WyNftHCEDL = false;
      bool hWcELqJIMO = false;
      bool tsddLfVcmW = false;
      bool NndkKzrucM = false;
      bool ZRHXtPUbYK = false;
      bool gKragdUiUO = false;
      bool lYRgytrrtL = false;
      bool zNeznclGiw = false;
      bool KsEcoCuCEf = false;
      string wwhOEFjrqe;
      string wVhwQrtZRt;
      string hqrMyXhCim;
      string TKCKfoexyA;
      string CkDCKIKnby;
      string qmSlUFDUPf;
      string WgJEKlSXQa;
      string NxaQrwmpCp;
      string MsZjugqQpZ;
      string lJgRcUazrY;
      string omXBktLCtX;
      string SNSZSdHZJc;
      string tCgpoDPJmW;
      string UmxdAZVYyA;
      string UoWRHXqHyz;
      string MBpOdmGgLh;
      string eCOWCePoZs;
      string HhaIIFfPiQ;
      string MHKmJTxizM;
      string SnNQVSZzOb;
      if(wwhOEFjrqe == omXBktLCtX){IBhEreagGX = true;}
      else if(omXBktLCtX == wwhOEFjrqe){lyfkBpTFpb = true;}
      if(wVhwQrtZRt == SNSZSdHZJc){HpytUWqaMi = true;}
      else if(SNSZSdHZJc == wVhwQrtZRt){WyNftHCEDL = true;}
      if(hqrMyXhCim == tCgpoDPJmW){hgoMZTUJmo = true;}
      else if(tCgpoDPJmW == hqrMyXhCim){hWcELqJIMO = true;}
      if(TKCKfoexyA == UmxdAZVYyA){ffAHIKZGue = true;}
      else if(UmxdAZVYyA == TKCKfoexyA){tsddLfVcmW = true;}
      if(CkDCKIKnby == UoWRHXqHyz){rQbbFboSuy = true;}
      else if(UoWRHXqHyz == CkDCKIKnby){NndkKzrucM = true;}
      if(qmSlUFDUPf == MBpOdmGgLh){bymfsaMUdX = true;}
      else if(MBpOdmGgLh == qmSlUFDUPf){ZRHXtPUbYK = true;}
      if(WgJEKlSXQa == eCOWCePoZs){JQsRrbpqlK = true;}
      else if(eCOWCePoZs == WgJEKlSXQa){gKragdUiUO = true;}
      if(NxaQrwmpCp == HhaIIFfPiQ){wkehpRENHx = true;}
      if(MsZjugqQpZ == MHKmJTxizM){dCOoNgsTNg = true;}
      if(lJgRcUazrY == SnNQVSZzOb){yFbWUbWKic = true;}
      while(HhaIIFfPiQ == NxaQrwmpCp){lYRgytrrtL = true;}
      while(MHKmJTxizM == MHKmJTxizM){zNeznclGiw = true;}
      while(SnNQVSZzOb == SnNQVSZzOb){KsEcoCuCEf = true;}
      if(IBhEreagGX == true){IBhEreagGX = false;}
      if(HpytUWqaMi == true){HpytUWqaMi = false;}
      if(hgoMZTUJmo == true){hgoMZTUJmo = false;}
      if(ffAHIKZGue == true){ffAHIKZGue = false;}
      if(rQbbFboSuy == true){rQbbFboSuy = false;}
      if(bymfsaMUdX == true){bymfsaMUdX = false;}
      if(JQsRrbpqlK == true){JQsRrbpqlK = false;}
      if(wkehpRENHx == true){wkehpRENHx = false;}
      if(dCOoNgsTNg == true){dCOoNgsTNg = false;}
      if(yFbWUbWKic == true){yFbWUbWKic = false;}
      if(lyfkBpTFpb == true){lyfkBpTFpb = false;}
      if(WyNftHCEDL == true){WyNftHCEDL = false;}
      if(hWcELqJIMO == true){hWcELqJIMO = false;}
      if(tsddLfVcmW == true){tsddLfVcmW = false;}
      if(NndkKzrucM == true){NndkKzrucM = false;}
      if(ZRHXtPUbYK == true){ZRHXtPUbYK = false;}
      if(gKragdUiUO == true){gKragdUiUO = false;}
      if(lYRgytrrtL == true){lYRgytrrtL = false;}
      if(zNeznclGiw == true){zNeznclGiw = false;}
      if(KsEcoCuCEf == true){KsEcoCuCEf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WOTUOAAJOB
{ 
  void TRtiUjmVdK()
  { 
      bool sNRapxisfl = false;
      bool ojZEZMIpMg = false;
      bool NVHCzIQfaa = false;
      bool QnEryrxCHE = false;
      bool WfITgRHxiR = false;
      bool PpmHaXFPag = false;
      bool fDSEUAegGg = false;
      bool PGhIJgMnUh = false;
      bool ATxILaAwRa = false;
      bool mgbaXTNDyg = false;
      bool lZpBBJHexs = false;
      bool KRurfLGJst = false;
      bool zhPftidHjp = false;
      bool SIomuacuGB = false;
      bool TVyXPUkitL = false;
      bool NEJEgDKKHS = false;
      bool eAtHZCbHwF = false;
      bool hLCqadjrPY = false;
      bool xtMYcOykGr = false;
      bool QSmnWSaqyM = false;
      string wDCbMoQCCd;
      string IeSdwnyifp;
      string KAQESBJJYy;
      string NzexiTbZTp;
      string odQGLiVISY;
      string HIKhAumxJL;
      string eHcEQIAUtb;
      string LXOpAfjJsi;
      string eBpAqFowxm;
      string geQIKhALpD;
      string hANqMisTgT;
      string LcDZfdRcNK;
      string SEXHugGGeS;
      string eXTpAemynH;
      string LUOdbDaqbg;
      string QXyejdcFwe;
      string cmoOnmJNYB;
      string pSnFzxosfq;
      string FPdyBGYnFW;
      string BgBIeYfAon;
      if(wDCbMoQCCd == hANqMisTgT){sNRapxisfl = true;}
      else if(hANqMisTgT == wDCbMoQCCd){lZpBBJHexs = true;}
      if(IeSdwnyifp == LcDZfdRcNK){ojZEZMIpMg = true;}
      else if(LcDZfdRcNK == IeSdwnyifp){KRurfLGJst = true;}
      if(KAQESBJJYy == SEXHugGGeS){NVHCzIQfaa = true;}
      else if(SEXHugGGeS == KAQESBJJYy){zhPftidHjp = true;}
      if(NzexiTbZTp == eXTpAemynH){QnEryrxCHE = true;}
      else if(eXTpAemynH == NzexiTbZTp){SIomuacuGB = true;}
      if(odQGLiVISY == LUOdbDaqbg){WfITgRHxiR = true;}
      else if(LUOdbDaqbg == odQGLiVISY){TVyXPUkitL = true;}
      if(HIKhAumxJL == QXyejdcFwe){PpmHaXFPag = true;}
      else if(QXyejdcFwe == HIKhAumxJL){NEJEgDKKHS = true;}
      if(eHcEQIAUtb == cmoOnmJNYB){fDSEUAegGg = true;}
      else if(cmoOnmJNYB == eHcEQIAUtb){eAtHZCbHwF = true;}
      if(LXOpAfjJsi == pSnFzxosfq){PGhIJgMnUh = true;}
      if(eBpAqFowxm == FPdyBGYnFW){ATxILaAwRa = true;}
      if(geQIKhALpD == BgBIeYfAon){mgbaXTNDyg = true;}
      while(pSnFzxosfq == LXOpAfjJsi){hLCqadjrPY = true;}
      while(FPdyBGYnFW == FPdyBGYnFW){xtMYcOykGr = true;}
      while(BgBIeYfAon == BgBIeYfAon){QSmnWSaqyM = true;}
      if(sNRapxisfl == true){sNRapxisfl = false;}
      if(ojZEZMIpMg == true){ojZEZMIpMg = false;}
      if(NVHCzIQfaa == true){NVHCzIQfaa = false;}
      if(QnEryrxCHE == true){QnEryrxCHE = false;}
      if(WfITgRHxiR == true){WfITgRHxiR = false;}
      if(PpmHaXFPag == true){PpmHaXFPag = false;}
      if(fDSEUAegGg == true){fDSEUAegGg = false;}
      if(PGhIJgMnUh == true){PGhIJgMnUh = false;}
      if(ATxILaAwRa == true){ATxILaAwRa = false;}
      if(mgbaXTNDyg == true){mgbaXTNDyg = false;}
      if(lZpBBJHexs == true){lZpBBJHexs = false;}
      if(KRurfLGJst == true){KRurfLGJst = false;}
      if(zhPftidHjp == true){zhPftidHjp = false;}
      if(SIomuacuGB == true){SIomuacuGB = false;}
      if(TVyXPUkitL == true){TVyXPUkitL = false;}
      if(NEJEgDKKHS == true){NEJEgDKKHS = false;}
      if(eAtHZCbHwF == true){eAtHZCbHwF = false;}
      if(hLCqadjrPY == true){hLCqadjrPY = false;}
      if(xtMYcOykGr == true){xtMYcOykGr = false;}
      if(QSmnWSaqyM == true){QSmnWSaqyM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SPNQDIVCEH
{ 
  void zaukuVIOgN()
  { 
      bool EgEhONhhTk = false;
      bool ZoKbDHZSFc = false;
      bool SrdHfKAGmi = false;
      bool kJbWunZhuM = false;
      bool hNHukCRLsh = false;
      bool WRYKMLCxBE = false;
      bool NaujzPNmfP = false;
      bool gqXsuEkiWd = false;
      bool rnNFLTjRKj = false;
      bool kcgpyGSWwU = false;
      bool oefcAfsfPI = false;
      bool aTZXLZMpYf = false;
      bool eucwdDJhtn = false;
      bool kNmBoNIkEe = false;
      bool ZECCIRDJeX = false;
      bool tcyPosBiyw = false;
      bool VLkaWMgXix = false;
      bool RbksFasamM = false;
      bool AACVtIPWMu = false;
      bool LYmIINSaew = false;
      string yUswCpXlpe;
      string VeLSzfGAqG;
      string HGfMTeRFCU;
      string MhLkHIYqAB;
      string XtjlfgdUps;
      string EMeqIqofcX;
      string YRiUSnTZLq;
      string GPzohNVtfl;
      string BxOJQzDTcP;
      string SrNccFLOSr;
      string NDIzmnMoIu;
      string VuAqVaDZES;
      string jzxwXNBWLc;
      string BGanYxnPVb;
      string mNKgtXrWGB;
      string CkKzHNFMaY;
      string mpcfsOTLRY;
      string mnDbfVnPCz;
      string UeQJaPwagK;
      string rbnwoxkene;
      if(yUswCpXlpe == NDIzmnMoIu){EgEhONhhTk = true;}
      else if(NDIzmnMoIu == yUswCpXlpe){oefcAfsfPI = true;}
      if(VeLSzfGAqG == VuAqVaDZES){ZoKbDHZSFc = true;}
      else if(VuAqVaDZES == VeLSzfGAqG){aTZXLZMpYf = true;}
      if(HGfMTeRFCU == jzxwXNBWLc){SrdHfKAGmi = true;}
      else if(jzxwXNBWLc == HGfMTeRFCU){eucwdDJhtn = true;}
      if(MhLkHIYqAB == BGanYxnPVb){kJbWunZhuM = true;}
      else if(BGanYxnPVb == MhLkHIYqAB){kNmBoNIkEe = true;}
      if(XtjlfgdUps == mNKgtXrWGB){hNHukCRLsh = true;}
      else if(mNKgtXrWGB == XtjlfgdUps){ZECCIRDJeX = true;}
      if(EMeqIqofcX == CkKzHNFMaY){WRYKMLCxBE = true;}
      else if(CkKzHNFMaY == EMeqIqofcX){tcyPosBiyw = true;}
      if(YRiUSnTZLq == mpcfsOTLRY){NaujzPNmfP = true;}
      else if(mpcfsOTLRY == YRiUSnTZLq){VLkaWMgXix = true;}
      if(GPzohNVtfl == mnDbfVnPCz){gqXsuEkiWd = true;}
      if(BxOJQzDTcP == UeQJaPwagK){rnNFLTjRKj = true;}
      if(SrNccFLOSr == rbnwoxkene){kcgpyGSWwU = true;}
      while(mnDbfVnPCz == GPzohNVtfl){RbksFasamM = true;}
      while(UeQJaPwagK == UeQJaPwagK){AACVtIPWMu = true;}
      while(rbnwoxkene == rbnwoxkene){LYmIINSaew = true;}
      if(EgEhONhhTk == true){EgEhONhhTk = false;}
      if(ZoKbDHZSFc == true){ZoKbDHZSFc = false;}
      if(SrdHfKAGmi == true){SrdHfKAGmi = false;}
      if(kJbWunZhuM == true){kJbWunZhuM = false;}
      if(hNHukCRLsh == true){hNHukCRLsh = false;}
      if(WRYKMLCxBE == true){WRYKMLCxBE = false;}
      if(NaujzPNmfP == true){NaujzPNmfP = false;}
      if(gqXsuEkiWd == true){gqXsuEkiWd = false;}
      if(rnNFLTjRKj == true){rnNFLTjRKj = false;}
      if(kcgpyGSWwU == true){kcgpyGSWwU = false;}
      if(oefcAfsfPI == true){oefcAfsfPI = false;}
      if(aTZXLZMpYf == true){aTZXLZMpYf = false;}
      if(eucwdDJhtn == true){eucwdDJhtn = false;}
      if(kNmBoNIkEe == true){kNmBoNIkEe = false;}
      if(ZECCIRDJeX == true){ZECCIRDJeX = false;}
      if(tcyPosBiyw == true){tcyPosBiyw = false;}
      if(VLkaWMgXix == true){VLkaWMgXix = false;}
      if(RbksFasamM == true){RbksFasamM = false;}
      if(AACVtIPWMu == true){AACVtIPWMu = false;}
      if(LYmIINSaew == true){LYmIINSaew = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XSHROKORWL
{ 
  void CHEDyzaUSl()
  { 
      bool DhWGBCuDQE = false;
      bool ttPQXGQxen = false;
      bool WjpyoUTYlI = false;
      bool BwYjlAKNeL = false;
      bool pWCAMJyezN = false;
      bool FsnENTrXQf = false;
      bool iWQICxUeeW = false;
      bool wDSSyAgole = false;
      bool WoYYCIITVR = false;
      bool IlwybTFsyO = false;
      bool oSzbRBaUGN = false;
      bool mClkJtxrFs = false;
      bool oAJMOJGTqe = false;
      bool tnqWpEowHA = false;
      bool hmNIeFALoh = false;
      bool VNmEZoImNH = false;
      bool uGdaSyKPuF = false;
      bool EAjFLClBhJ = false;
      bool JueIIfAlwA = false;
      bool uCizFaIlof = false;
      string wHJjCWGTfw;
      string cteeTVhQcY;
      string gElAIZzhzK;
      string wzdUJwjZlq;
      string IltknDJKbE;
      string FihqyrUIbb;
      string WXUUAdPJVX;
      string lHdlQtKBLE;
      string QnGuFMQmWQ;
      string aayKTjRZjJ;
      string mzoDRxEwZD;
      string hTxWKhRZOn;
      string NclExLJTRg;
      string cjQBRQzCcI;
      string IUMTiHcbzk;
      string SrKwwKMkGF;
      string nkdsZxDuFs;
      string iPwGerQSVp;
      string hgTgOkZTEG;
      string ENuWTWpTsk;
      if(wHJjCWGTfw == mzoDRxEwZD){DhWGBCuDQE = true;}
      else if(mzoDRxEwZD == wHJjCWGTfw){oSzbRBaUGN = true;}
      if(cteeTVhQcY == hTxWKhRZOn){ttPQXGQxen = true;}
      else if(hTxWKhRZOn == cteeTVhQcY){mClkJtxrFs = true;}
      if(gElAIZzhzK == NclExLJTRg){WjpyoUTYlI = true;}
      else if(NclExLJTRg == gElAIZzhzK){oAJMOJGTqe = true;}
      if(wzdUJwjZlq == cjQBRQzCcI){BwYjlAKNeL = true;}
      else if(cjQBRQzCcI == wzdUJwjZlq){tnqWpEowHA = true;}
      if(IltknDJKbE == IUMTiHcbzk){pWCAMJyezN = true;}
      else if(IUMTiHcbzk == IltknDJKbE){hmNIeFALoh = true;}
      if(FihqyrUIbb == SrKwwKMkGF){FsnENTrXQf = true;}
      else if(SrKwwKMkGF == FihqyrUIbb){VNmEZoImNH = true;}
      if(WXUUAdPJVX == nkdsZxDuFs){iWQICxUeeW = true;}
      else if(nkdsZxDuFs == WXUUAdPJVX){uGdaSyKPuF = true;}
      if(lHdlQtKBLE == iPwGerQSVp){wDSSyAgole = true;}
      if(QnGuFMQmWQ == hgTgOkZTEG){WoYYCIITVR = true;}
      if(aayKTjRZjJ == ENuWTWpTsk){IlwybTFsyO = true;}
      while(iPwGerQSVp == lHdlQtKBLE){EAjFLClBhJ = true;}
      while(hgTgOkZTEG == hgTgOkZTEG){JueIIfAlwA = true;}
      while(ENuWTWpTsk == ENuWTWpTsk){uCizFaIlof = true;}
      if(DhWGBCuDQE == true){DhWGBCuDQE = false;}
      if(ttPQXGQxen == true){ttPQXGQxen = false;}
      if(WjpyoUTYlI == true){WjpyoUTYlI = false;}
      if(BwYjlAKNeL == true){BwYjlAKNeL = false;}
      if(pWCAMJyezN == true){pWCAMJyezN = false;}
      if(FsnENTrXQf == true){FsnENTrXQf = false;}
      if(iWQICxUeeW == true){iWQICxUeeW = false;}
      if(wDSSyAgole == true){wDSSyAgole = false;}
      if(WoYYCIITVR == true){WoYYCIITVR = false;}
      if(IlwybTFsyO == true){IlwybTFsyO = false;}
      if(oSzbRBaUGN == true){oSzbRBaUGN = false;}
      if(mClkJtxrFs == true){mClkJtxrFs = false;}
      if(oAJMOJGTqe == true){oAJMOJGTqe = false;}
      if(tnqWpEowHA == true){tnqWpEowHA = false;}
      if(hmNIeFALoh == true){hmNIeFALoh = false;}
      if(VNmEZoImNH == true){VNmEZoImNH = false;}
      if(uGdaSyKPuF == true){uGdaSyKPuF = false;}
      if(EAjFLClBhJ == true){EAjFLClBhJ = false;}
      if(JueIIfAlwA == true){JueIIfAlwA = false;}
      if(uCizFaIlof == true){uCizFaIlof = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XGVAGUHYLN
{ 
  void ObCuDFYsHM()
  { 
      bool LFaAAHxLHN = false;
      bool QVoqcWSREJ = false;
      bool QoCCxiOSFV = false;
      bool edcpuNDwdY = false;
      bool mkcNPIGfTK = false;
      bool CrzfVWCYDR = false;
      bool reFkilrzwP = false;
      bool SVmeWeMolo = false;
      bool biyuTmexTX = false;
      bool LdsMgHfqec = false;
      bool PHjEqfETJp = false;
      bool JMmNpJfJRu = false;
      bool HteXDocayO = false;
      bool zUKIYTztEm = false;
      bool iLndNyqfVW = false;
      bool aVZiVVcLAB = false;
      bool DdUtpnCdnV = false;
      bool KlFdMuGBJE = false;
      bool yxEamduamD = false;
      bool qmsCjEpsmZ = false;
      string xSZJptMpTP;
      string XDXTEZGVOx;
      string tZwnrkqqnb;
      string KLiqgQdrac;
      string WYLhLpZget;
      string EjukNXWlRF;
      string CUCrEMUglm;
      string uOulaUONcC;
      string LJMsWaQycJ;
      string trZVZBWSdy;
      string VruqzooJJs;
      string IJIPtsHJUd;
      string wVDcrCoYLZ;
      string yujdfSOVsh;
      string lHnjAkiKbf;
      string sNyzCzoRyw;
      string APxjtNYdia;
      string elPmrohScH;
      string Sdxefkwjbg;
      string dwWxgVJDol;
      if(xSZJptMpTP == VruqzooJJs){LFaAAHxLHN = true;}
      else if(VruqzooJJs == xSZJptMpTP){PHjEqfETJp = true;}
      if(XDXTEZGVOx == IJIPtsHJUd){QVoqcWSREJ = true;}
      else if(IJIPtsHJUd == XDXTEZGVOx){JMmNpJfJRu = true;}
      if(tZwnrkqqnb == wVDcrCoYLZ){QoCCxiOSFV = true;}
      else if(wVDcrCoYLZ == tZwnrkqqnb){HteXDocayO = true;}
      if(KLiqgQdrac == yujdfSOVsh){edcpuNDwdY = true;}
      else if(yujdfSOVsh == KLiqgQdrac){zUKIYTztEm = true;}
      if(WYLhLpZget == lHnjAkiKbf){mkcNPIGfTK = true;}
      else if(lHnjAkiKbf == WYLhLpZget){iLndNyqfVW = true;}
      if(EjukNXWlRF == sNyzCzoRyw){CrzfVWCYDR = true;}
      else if(sNyzCzoRyw == EjukNXWlRF){aVZiVVcLAB = true;}
      if(CUCrEMUglm == APxjtNYdia){reFkilrzwP = true;}
      else if(APxjtNYdia == CUCrEMUglm){DdUtpnCdnV = true;}
      if(uOulaUONcC == elPmrohScH){SVmeWeMolo = true;}
      if(LJMsWaQycJ == Sdxefkwjbg){biyuTmexTX = true;}
      if(trZVZBWSdy == dwWxgVJDol){LdsMgHfqec = true;}
      while(elPmrohScH == uOulaUONcC){KlFdMuGBJE = true;}
      while(Sdxefkwjbg == Sdxefkwjbg){yxEamduamD = true;}
      while(dwWxgVJDol == dwWxgVJDol){qmsCjEpsmZ = true;}
      if(LFaAAHxLHN == true){LFaAAHxLHN = false;}
      if(QVoqcWSREJ == true){QVoqcWSREJ = false;}
      if(QoCCxiOSFV == true){QoCCxiOSFV = false;}
      if(edcpuNDwdY == true){edcpuNDwdY = false;}
      if(mkcNPIGfTK == true){mkcNPIGfTK = false;}
      if(CrzfVWCYDR == true){CrzfVWCYDR = false;}
      if(reFkilrzwP == true){reFkilrzwP = false;}
      if(SVmeWeMolo == true){SVmeWeMolo = false;}
      if(biyuTmexTX == true){biyuTmexTX = false;}
      if(LdsMgHfqec == true){LdsMgHfqec = false;}
      if(PHjEqfETJp == true){PHjEqfETJp = false;}
      if(JMmNpJfJRu == true){JMmNpJfJRu = false;}
      if(HteXDocayO == true){HteXDocayO = false;}
      if(zUKIYTztEm == true){zUKIYTztEm = false;}
      if(iLndNyqfVW == true){iLndNyqfVW = false;}
      if(aVZiVVcLAB == true){aVZiVVcLAB = false;}
      if(DdUtpnCdnV == true){DdUtpnCdnV = false;}
      if(KlFdMuGBJE == true){KlFdMuGBJE = false;}
      if(yxEamduamD == true){yxEamduamD = false;}
      if(qmsCjEpsmZ == true){qmsCjEpsmZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VLUEHNHTOU
{ 
  void QxbHTGYAFw()
  { 
      bool EGfJkEPQrI = false;
      bool ToEQVtfqRw = false;
      bool QMMQTjMTJQ = false;
      bool MdJnHoOmZf = false;
      bool JgRlWchIjb = false;
      bool yFijxrtOpB = false;
      bool ruGawpePJf = false;
      bool esRkmjtZtp = false;
      bool BDjhSGuZpO = false;
      bool uAwXmOappg = false;
      bool xRzDxFnxxN = false;
      bool xUUzznKXIp = false;
      bool tEYtkexsyX = false;
      bool JEiMsiDgkN = false;
      bool SxccQafwXy = false;
      bool DChAlrsFRS = false;
      bool HtzYDskIGP = false;
      bool jcmuXwbucK = false;
      bool zBVzTHViZA = false;
      bool pyOSFXyDYW = false;
      string weMtkudZQG;
      string PmHymwmHSB;
      string lETyVdsTbl;
      string WjWaeFzNka;
      string qkTcHxGIza;
      string zrNnlrKNXG;
      string BKyeifPgTh;
      string xZWrJBjqpX;
      string WjUBldVhnl;
      string tlodYglosb;
      string gYoQdZVVek;
      string ITWziQpxrE;
      string JhsgmLjrSb;
      string OtxOqxtDXL;
      string IADCcaOouH;
      string qoxnSzfIcR;
      string ocCCVOVIIk;
      string VlZfwJepDM;
      string wuxKkZxJuq;
      string RlZFVexAfO;
      if(weMtkudZQG == gYoQdZVVek){EGfJkEPQrI = true;}
      else if(gYoQdZVVek == weMtkudZQG){xRzDxFnxxN = true;}
      if(PmHymwmHSB == ITWziQpxrE){ToEQVtfqRw = true;}
      else if(ITWziQpxrE == PmHymwmHSB){xUUzznKXIp = true;}
      if(lETyVdsTbl == JhsgmLjrSb){QMMQTjMTJQ = true;}
      else if(JhsgmLjrSb == lETyVdsTbl){tEYtkexsyX = true;}
      if(WjWaeFzNka == OtxOqxtDXL){MdJnHoOmZf = true;}
      else if(OtxOqxtDXL == WjWaeFzNka){JEiMsiDgkN = true;}
      if(qkTcHxGIza == IADCcaOouH){JgRlWchIjb = true;}
      else if(IADCcaOouH == qkTcHxGIza){SxccQafwXy = true;}
      if(zrNnlrKNXG == qoxnSzfIcR){yFijxrtOpB = true;}
      else if(qoxnSzfIcR == zrNnlrKNXG){DChAlrsFRS = true;}
      if(BKyeifPgTh == ocCCVOVIIk){ruGawpePJf = true;}
      else if(ocCCVOVIIk == BKyeifPgTh){HtzYDskIGP = true;}
      if(xZWrJBjqpX == VlZfwJepDM){esRkmjtZtp = true;}
      if(WjUBldVhnl == wuxKkZxJuq){BDjhSGuZpO = true;}
      if(tlodYglosb == RlZFVexAfO){uAwXmOappg = true;}
      while(VlZfwJepDM == xZWrJBjqpX){jcmuXwbucK = true;}
      while(wuxKkZxJuq == wuxKkZxJuq){zBVzTHViZA = true;}
      while(RlZFVexAfO == RlZFVexAfO){pyOSFXyDYW = true;}
      if(EGfJkEPQrI == true){EGfJkEPQrI = false;}
      if(ToEQVtfqRw == true){ToEQVtfqRw = false;}
      if(QMMQTjMTJQ == true){QMMQTjMTJQ = false;}
      if(MdJnHoOmZf == true){MdJnHoOmZf = false;}
      if(JgRlWchIjb == true){JgRlWchIjb = false;}
      if(yFijxrtOpB == true){yFijxrtOpB = false;}
      if(ruGawpePJf == true){ruGawpePJf = false;}
      if(esRkmjtZtp == true){esRkmjtZtp = false;}
      if(BDjhSGuZpO == true){BDjhSGuZpO = false;}
      if(uAwXmOappg == true){uAwXmOappg = false;}
      if(xRzDxFnxxN == true){xRzDxFnxxN = false;}
      if(xUUzznKXIp == true){xUUzznKXIp = false;}
      if(tEYtkexsyX == true){tEYtkexsyX = false;}
      if(JEiMsiDgkN == true){JEiMsiDgkN = false;}
      if(SxccQafwXy == true){SxccQafwXy = false;}
      if(DChAlrsFRS == true){DChAlrsFRS = false;}
      if(HtzYDskIGP == true){HtzYDskIGP = false;}
      if(jcmuXwbucK == true){jcmuXwbucK = false;}
      if(zBVzTHViZA == true){zBVzTHViZA = false;}
      if(pyOSFXyDYW == true){pyOSFXyDYW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJDOYLIJMQ
{ 
  void UeYiwPHxze()
  { 
      bool kqWFefPskF = false;
      bool XZdPRxCwAl = false;
      bool TgbXYRjkWF = false;
      bool yuPsUJLfgK = false;
      bool isiuKDATJE = false;
      bool ppGAsDPygN = false;
      bool weVeHcJjuI = false;
      bool kWOoDaxgMV = false;
      bool RQaSOIoOAQ = false;
      bool sMzTODWDmh = false;
      bool sPXBSTaQxR = false;
      bool GhlKweDDPy = false;
      bool mtieOYWuaz = false;
      bool DssdcBrZzu = false;
      bool hYQhKLaoWi = false;
      bool ATmouyfslt = false;
      bool xfoyOMnHht = false;
      bool ldDUQOcATD = false;
      bool xgXryiFEid = false;
      bool UzmExBiSTx = false;
      string ORycsVFbzQ;
      string mEdRDnsrre;
      string rcpMgbmOjU;
      string ONbPOTbngT;
      string PdCTxBRNwA;
      string wuVxckbkuR;
      string iqqeBYcNDi;
      string MEKXPOaVPf;
      string JYRiYTrelc;
      string qprPjYlXRX;
      string XEKMnqjxhN;
      string JFVOHJYIFh;
      string gyaZqVLunp;
      string cDErIFOEtg;
      string iuxXSlUdIa;
      string zdRjqYcjVS;
      string eoJqkGBcGC;
      string uTNYykBCGF;
      string AhlMqzlUBi;
      string cdibBslGmM;
      if(ORycsVFbzQ == XEKMnqjxhN){kqWFefPskF = true;}
      else if(XEKMnqjxhN == ORycsVFbzQ){sPXBSTaQxR = true;}
      if(mEdRDnsrre == JFVOHJYIFh){XZdPRxCwAl = true;}
      else if(JFVOHJYIFh == mEdRDnsrre){GhlKweDDPy = true;}
      if(rcpMgbmOjU == gyaZqVLunp){TgbXYRjkWF = true;}
      else if(gyaZqVLunp == rcpMgbmOjU){mtieOYWuaz = true;}
      if(ONbPOTbngT == cDErIFOEtg){yuPsUJLfgK = true;}
      else if(cDErIFOEtg == ONbPOTbngT){DssdcBrZzu = true;}
      if(PdCTxBRNwA == iuxXSlUdIa){isiuKDATJE = true;}
      else if(iuxXSlUdIa == PdCTxBRNwA){hYQhKLaoWi = true;}
      if(wuVxckbkuR == zdRjqYcjVS){ppGAsDPygN = true;}
      else if(zdRjqYcjVS == wuVxckbkuR){ATmouyfslt = true;}
      if(iqqeBYcNDi == eoJqkGBcGC){weVeHcJjuI = true;}
      else if(eoJqkGBcGC == iqqeBYcNDi){xfoyOMnHht = true;}
      if(MEKXPOaVPf == uTNYykBCGF){kWOoDaxgMV = true;}
      if(JYRiYTrelc == AhlMqzlUBi){RQaSOIoOAQ = true;}
      if(qprPjYlXRX == cdibBslGmM){sMzTODWDmh = true;}
      while(uTNYykBCGF == MEKXPOaVPf){ldDUQOcATD = true;}
      while(AhlMqzlUBi == AhlMqzlUBi){xgXryiFEid = true;}
      while(cdibBslGmM == cdibBslGmM){UzmExBiSTx = true;}
      if(kqWFefPskF == true){kqWFefPskF = false;}
      if(XZdPRxCwAl == true){XZdPRxCwAl = false;}
      if(TgbXYRjkWF == true){TgbXYRjkWF = false;}
      if(yuPsUJLfgK == true){yuPsUJLfgK = false;}
      if(isiuKDATJE == true){isiuKDATJE = false;}
      if(ppGAsDPygN == true){ppGAsDPygN = false;}
      if(weVeHcJjuI == true){weVeHcJjuI = false;}
      if(kWOoDaxgMV == true){kWOoDaxgMV = false;}
      if(RQaSOIoOAQ == true){RQaSOIoOAQ = false;}
      if(sMzTODWDmh == true){sMzTODWDmh = false;}
      if(sPXBSTaQxR == true){sPXBSTaQxR = false;}
      if(GhlKweDDPy == true){GhlKweDDPy = false;}
      if(mtieOYWuaz == true){mtieOYWuaz = false;}
      if(DssdcBrZzu == true){DssdcBrZzu = false;}
      if(hYQhKLaoWi == true){hYQhKLaoWi = false;}
      if(ATmouyfslt == true){ATmouyfslt = false;}
      if(xfoyOMnHht == true){xfoyOMnHht = false;}
      if(ldDUQOcATD == true){ldDUQOcATD = false;}
      if(xgXryiFEid == true){xgXryiFEid = false;}
      if(UzmExBiSTx == true){UzmExBiSTx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSRSVRZDTS
{ 
  void gNHzedfWDb()
  { 
      bool LCxbeRBDJr = false;
      bool mfwuKdWjAX = false;
      bool PmHfjksUEh = false;
      bool oTtbNskYIT = false;
      bool YtpMCaFSFn = false;
      bool MbariYtRqs = false;
      bool YgzaDSkThR = false;
      bool ryafzUwtcJ = false;
      bool faOQUMsCsn = false;
      bool yTgPuquOJj = false;
      bool okjnuOBtrO = false;
      bool bznhMxRiGq = false;
      bool YiatTXRLjH = false;
      bool ZhksTupaUF = false;
      bool LyJdLyfyCx = false;
      bool ZMHRKGJoTW = false;
      bool xoJknsNtOQ = false;
      bool GqNAfZYwhU = false;
      bool rSJmhMZThM = false;
      bool kAGxIVnYoR = false;
      string wCxgexUkUI;
      string WHpWhDmuTP;
      string zOLGYatBoa;
      string dZnrgARWOi;
      string kpShbKNEZC;
      string gaNbTgppIE;
      string DTutexTxog;
      string lQgkdIuddO;
      string NobmtDLLYz;
      string KaNKfRuYDe;
      string pPOrQPtcyK;
      string kMMtpNqIza;
      string kIYpWKCVFL;
      string MWazXyZjWd;
      string IiMNNxOTUR;
      string ZmYbthpYUF;
      string MXWlyOlMVr;
      string mHkVSBuKbY;
      string uiBmlZyzFp;
      string HBOQRjMaPz;
      if(wCxgexUkUI == pPOrQPtcyK){LCxbeRBDJr = true;}
      else if(pPOrQPtcyK == wCxgexUkUI){okjnuOBtrO = true;}
      if(WHpWhDmuTP == kMMtpNqIza){mfwuKdWjAX = true;}
      else if(kMMtpNqIza == WHpWhDmuTP){bznhMxRiGq = true;}
      if(zOLGYatBoa == kIYpWKCVFL){PmHfjksUEh = true;}
      else if(kIYpWKCVFL == zOLGYatBoa){YiatTXRLjH = true;}
      if(dZnrgARWOi == MWazXyZjWd){oTtbNskYIT = true;}
      else if(MWazXyZjWd == dZnrgARWOi){ZhksTupaUF = true;}
      if(kpShbKNEZC == IiMNNxOTUR){YtpMCaFSFn = true;}
      else if(IiMNNxOTUR == kpShbKNEZC){LyJdLyfyCx = true;}
      if(gaNbTgppIE == ZmYbthpYUF){MbariYtRqs = true;}
      else if(ZmYbthpYUF == gaNbTgppIE){ZMHRKGJoTW = true;}
      if(DTutexTxog == MXWlyOlMVr){YgzaDSkThR = true;}
      else if(MXWlyOlMVr == DTutexTxog){xoJknsNtOQ = true;}
      if(lQgkdIuddO == mHkVSBuKbY){ryafzUwtcJ = true;}
      if(NobmtDLLYz == uiBmlZyzFp){faOQUMsCsn = true;}
      if(KaNKfRuYDe == HBOQRjMaPz){yTgPuquOJj = true;}
      while(mHkVSBuKbY == lQgkdIuddO){GqNAfZYwhU = true;}
      while(uiBmlZyzFp == uiBmlZyzFp){rSJmhMZThM = true;}
      while(HBOQRjMaPz == HBOQRjMaPz){kAGxIVnYoR = true;}
      if(LCxbeRBDJr == true){LCxbeRBDJr = false;}
      if(mfwuKdWjAX == true){mfwuKdWjAX = false;}
      if(PmHfjksUEh == true){PmHfjksUEh = false;}
      if(oTtbNskYIT == true){oTtbNskYIT = false;}
      if(YtpMCaFSFn == true){YtpMCaFSFn = false;}
      if(MbariYtRqs == true){MbariYtRqs = false;}
      if(YgzaDSkThR == true){YgzaDSkThR = false;}
      if(ryafzUwtcJ == true){ryafzUwtcJ = false;}
      if(faOQUMsCsn == true){faOQUMsCsn = false;}
      if(yTgPuquOJj == true){yTgPuquOJj = false;}
      if(okjnuOBtrO == true){okjnuOBtrO = false;}
      if(bznhMxRiGq == true){bznhMxRiGq = false;}
      if(YiatTXRLjH == true){YiatTXRLjH = false;}
      if(ZhksTupaUF == true){ZhksTupaUF = false;}
      if(LyJdLyfyCx == true){LyJdLyfyCx = false;}
      if(ZMHRKGJoTW == true){ZMHRKGJoTW = false;}
      if(xoJknsNtOQ == true){xoJknsNtOQ = false;}
      if(GqNAfZYwhU == true){GqNAfZYwhU = false;}
      if(rSJmhMZThM == true){rSJmhMZThM = false;}
      if(kAGxIVnYoR == true){kAGxIVnYoR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UCVPHNHWEW
{ 
  void FPwKbtpOiH()
  { 
      bool zwnMpcLQzk = false;
      bool fCJroWNHDr = false;
      bool WYFBlrHPHg = false;
      bool pYmxbRFZad = false;
      bool GVxDNhYjoR = false;
      bool idMipZqlax = false;
      bool VwIStGPMQX = false;
      bool QngZlAbBnD = false;
      bool TWZoxMMEGC = false;
      bool aTzdIKMdJG = false;
      bool SLSRBuxlwo = false;
      bool xoyWcyVTUh = false;
      bool tKGNwxnDQa = false;
      bool mxrhkIEInC = false;
      bool PZHQFlUcAJ = false;
      bool nsJaMHFFUD = false;
      bool GsVVCzwQkU = false;
      bool tNeRRTCoIK = false;
      bool bLDGmtnQUc = false;
      bool DymjwVElOF = false;
      string tmPXPrfMWH;
      string JSsGsgijFz;
      string QaSNJSLlqU;
      string PDwSxioJGb;
      string lGOrIHtJZA;
      string UykquTUCNx;
      string fsVBqGVZJK;
      string rZddMKLZEB;
      string XCMqARSFXc;
      string OmuIuskNBC;
      string lUzPIuUHdk;
      string HtxLZdfdBZ;
      string nQCfuEdUhT;
      string YyYCPDCwiF;
      string wKamVUpjiR;
      string MGLbNVRTTD;
      string QzYKLIVtuW;
      string ajuuccoOJa;
      string NtlQGSlwot;
      string khcenwlPbM;
      if(tmPXPrfMWH == lUzPIuUHdk){zwnMpcLQzk = true;}
      else if(lUzPIuUHdk == tmPXPrfMWH){SLSRBuxlwo = true;}
      if(JSsGsgijFz == HtxLZdfdBZ){fCJroWNHDr = true;}
      else if(HtxLZdfdBZ == JSsGsgijFz){xoyWcyVTUh = true;}
      if(QaSNJSLlqU == nQCfuEdUhT){WYFBlrHPHg = true;}
      else if(nQCfuEdUhT == QaSNJSLlqU){tKGNwxnDQa = true;}
      if(PDwSxioJGb == YyYCPDCwiF){pYmxbRFZad = true;}
      else if(YyYCPDCwiF == PDwSxioJGb){mxrhkIEInC = true;}
      if(lGOrIHtJZA == wKamVUpjiR){GVxDNhYjoR = true;}
      else if(wKamVUpjiR == lGOrIHtJZA){PZHQFlUcAJ = true;}
      if(UykquTUCNx == MGLbNVRTTD){idMipZqlax = true;}
      else if(MGLbNVRTTD == UykquTUCNx){nsJaMHFFUD = true;}
      if(fsVBqGVZJK == QzYKLIVtuW){VwIStGPMQX = true;}
      else if(QzYKLIVtuW == fsVBqGVZJK){GsVVCzwQkU = true;}
      if(rZddMKLZEB == ajuuccoOJa){QngZlAbBnD = true;}
      if(XCMqARSFXc == NtlQGSlwot){TWZoxMMEGC = true;}
      if(OmuIuskNBC == khcenwlPbM){aTzdIKMdJG = true;}
      while(ajuuccoOJa == rZddMKLZEB){tNeRRTCoIK = true;}
      while(NtlQGSlwot == NtlQGSlwot){bLDGmtnQUc = true;}
      while(khcenwlPbM == khcenwlPbM){DymjwVElOF = true;}
      if(zwnMpcLQzk == true){zwnMpcLQzk = false;}
      if(fCJroWNHDr == true){fCJroWNHDr = false;}
      if(WYFBlrHPHg == true){WYFBlrHPHg = false;}
      if(pYmxbRFZad == true){pYmxbRFZad = false;}
      if(GVxDNhYjoR == true){GVxDNhYjoR = false;}
      if(idMipZqlax == true){idMipZqlax = false;}
      if(VwIStGPMQX == true){VwIStGPMQX = false;}
      if(QngZlAbBnD == true){QngZlAbBnD = false;}
      if(TWZoxMMEGC == true){TWZoxMMEGC = false;}
      if(aTzdIKMdJG == true){aTzdIKMdJG = false;}
      if(SLSRBuxlwo == true){SLSRBuxlwo = false;}
      if(xoyWcyVTUh == true){xoyWcyVTUh = false;}
      if(tKGNwxnDQa == true){tKGNwxnDQa = false;}
      if(mxrhkIEInC == true){mxrhkIEInC = false;}
      if(PZHQFlUcAJ == true){PZHQFlUcAJ = false;}
      if(nsJaMHFFUD == true){nsJaMHFFUD = false;}
      if(GsVVCzwQkU == true){GsVVCzwQkU = false;}
      if(tNeRRTCoIK == true){tNeRRTCoIK = false;}
      if(bLDGmtnQUc == true){bLDGmtnQUc = false;}
      if(DymjwVElOF == true){DymjwVElOF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BILVWKTIIN
{ 
  void PylXjOWXTY()
  { 
      bool nSngAzzESK = false;
      bool JQCwxTfsdu = false;
      bool GCyLyUBMgS = false;
      bool QrbbduRyHp = false;
      bool pgAGRoosZG = false;
      bool syCYRkTcif = false;
      bool xmWzsRnaRB = false;
      bool ChknFZCrtI = false;
      bool eHmaZSpDJr = false;
      bool bnObrDJBNz = false;
      bool AOaXELNNTr = false;
      bool ibhZApzwYa = false;
      bool akQYZNSIwB = false;
      bool PBdtIQfPVN = false;
      bool FbjRJzGnbB = false;
      bool EMbmYPxBxq = false;
      bool sERRbhxnRj = false;
      bool JjZLVyAyPZ = false;
      bool GdgtxCZqVs = false;
      bool SeReUAKSpb = false;
      string CLtRcKawpB;
      string lwbXNUxqWI;
      string uztoAUtdiZ;
      string NWWHGanpQi;
      string lQjbjhkiep;
      string QBIWpDRFQH;
      string QwMQnPZTRl;
      string fHZmVdPRES;
      string jKysILOARD;
      string JiZISoDSnU;
      string IQQrJIbVAL;
      string mzAxXGyTHc;
      string BYCOcxhQUg;
      string ZwdjKTsGiA;
      string jrAFPJibkM;
      string qjLKSiNCPM;
      string ZKBTkqVPmD;
      string MrjHrIYwzS;
      string OGeHopkSQa;
      string FqpWZYqfTX;
      if(CLtRcKawpB == IQQrJIbVAL){nSngAzzESK = true;}
      else if(IQQrJIbVAL == CLtRcKawpB){AOaXELNNTr = true;}
      if(lwbXNUxqWI == mzAxXGyTHc){JQCwxTfsdu = true;}
      else if(mzAxXGyTHc == lwbXNUxqWI){ibhZApzwYa = true;}
      if(uztoAUtdiZ == BYCOcxhQUg){GCyLyUBMgS = true;}
      else if(BYCOcxhQUg == uztoAUtdiZ){akQYZNSIwB = true;}
      if(NWWHGanpQi == ZwdjKTsGiA){QrbbduRyHp = true;}
      else if(ZwdjKTsGiA == NWWHGanpQi){PBdtIQfPVN = true;}
      if(lQjbjhkiep == jrAFPJibkM){pgAGRoosZG = true;}
      else if(jrAFPJibkM == lQjbjhkiep){FbjRJzGnbB = true;}
      if(QBIWpDRFQH == qjLKSiNCPM){syCYRkTcif = true;}
      else if(qjLKSiNCPM == QBIWpDRFQH){EMbmYPxBxq = true;}
      if(QwMQnPZTRl == ZKBTkqVPmD){xmWzsRnaRB = true;}
      else if(ZKBTkqVPmD == QwMQnPZTRl){sERRbhxnRj = true;}
      if(fHZmVdPRES == MrjHrIYwzS){ChknFZCrtI = true;}
      if(jKysILOARD == OGeHopkSQa){eHmaZSpDJr = true;}
      if(JiZISoDSnU == FqpWZYqfTX){bnObrDJBNz = true;}
      while(MrjHrIYwzS == fHZmVdPRES){JjZLVyAyPZ = true;}
      while(OGeHopkSQa == OGeHopkSQa){GdgtxCZqVs = true;}
      while(FqpWZYqfTX == FqpWZYqfTX){SeReUAKSpb = true;}
      if(nSngAzzESK == true){nSngAzzESK = false;}
      if(JQCwxTfsdu == true){JQCwxTfsdu = false;}
      if(GCyLyUBMgS == true){GCyLyUBMgS = false;}
      if(QrbbduRyHp == true){QrbbduRyHp = false;}
      if(pgAGRoosZG == true){pgAGRoosZG = false;}
      if(syCYRkTcif == true){syCYRkTcif = false;}
      if(xmWzsRnaRB == true){xmWzsRnaRB = false;}
      if(ChknFZCrtI == true){ChknFZCrtI = false;}
      if(eHmaZSpDJr == true){eHmaZSpDJr = false;}
      if(bnObrDJBNz == true){bnObrDJBNz = false;}
      if(AOaXELNNTr == true){AOaXELNNTr = false;}
      if(ibhZApzwYa == true){ibhZApzwYa = false;}
      if(akQYZNSIwB == true){akQYZNSIwB = false;}
      if(PBdtIQfPVN == true){PBdtIQfPVN = false;}
      if(FbjRJzGnbB == true){FbjRJzGnbB = false;}
      if(EMbmYPxBxq == true){EMbmYPxBxq = false;}
      if(sERRbhxnRj == true){sERRbhxnRj = false;}
      if(JjZLVyAyPZ == true){JjZLVyAyPZ = false;}
      if(GdgtxCZqVs == true){GdgtxCZqVs = false;}
      if(SeReUAKSpb == true){SeReUAKSpb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DMGKQDTJIC
{ 
  void jNlVnQXjDG()
  { 
      bool dFxKIGBlue = false;
      bool ZEXLVWpMDT = false;
      bool MVZzxlCPuy = false;
      bool NwlLueHILZ = false;
      bool KkIfRRMNhS = false;
      bool HAYMTHfxMV = false;
      bool DlqwRcSLQp = false;
      bool PhAdIbNshf = false;
      bool ZnhbqMWZrn = false;
      bool zKuoVYsLOn = false;
      bool zBxqDZAtDr = false;
      bool slPgwPEOFE = false;
      bool GrTcqFlKIj = false;
      bool hCetfXppYR = false;
      bool McWztNtOsF = false;
      bool UdGJhGgUAy = false;
      bool nolSJqHUAX = false;
      bool YNpnrcVThd = false;
      bool KWRCPDuULZ = false;
      bool qVpadWpDoD = false;
      string qVEVFyzWTp;
      string zqaBjGzsyS;
      string LoKKKxCmwa;
      string TFtXxilhBx;
      string hbSTTiDdOC;
      string mBgiyBLsKH;
      string uLZrWsxDEA;
      string TQrAjjVqqb;
      string tYYtnRYKYu;
      string XrWsBVBawZ;
      string kAYNhVJfyN;
      string eTChNWmfDE;
      string TldIcasyzO;
      string hutQqsAKLS;
      string IsMLQDpoee;
      string hVXqFzWPkG;
      string bKfjfjZkqT;
      string WbTkwaYRrY;
      string kETTfMWDLq;
      string WjZEpyMcff;
      if(qVEVFyzWTp == kAYNhVJfyN){dFxKIGBlue = true;}
      else if(kAYNhVJfyN == qVEVFyzWTp){zBxqDZAtDr = true;}
      if(zqaBjGzsyS == eTChNWmfDE){ZEXLVWpMDT = true;}
      else if(eTChNWmfDE == zqaBjGzsyS){slPgwPEOFE = true;}
      if(LoKKKxCmwa == TldIcasyzO){MVZzxlCPuy = true;}
      else if(TldIcasyzO == LoKKKxCmwa){GrTcqFlKIj = true;}
      if(TFtXxilhBx == hutQqsAKLS){NwlLueHILZ = true;}
      else if(hutQqsAKLS == TFtXxilhBx){hCetfXppYR = true;}
      if(hbSTTiDdOC == IsMLQDpoee){KkIfRRMNhS = true;}
      else if(IsMLQDpoee == hbSTTiDdOC){McWztNtOsF = true;}
      if(mBgiyBLsKH == hVXqFzWPkG){HAYMTHfxMV = true;}
      else if(hVXqFzWPkG == mBgiyBLsKH){UdGJhGgUAy = true;}
      if(uLZrWsxDEA == bKfjfjZkqT){DlqwRcSLQp = true;}
      else if(bKfjfjZkqT == uLZrWsxDEA){nolSJqHUAX = true;}
      if(TQrAjjVqqb == WbTkwaYRrY){PhAdIbNshf = true;}
      if(tYYtnRYKYu == kETTfMWDLq){ZnhbqMWZrn = true;}
      if(XrWsBVBawZ == WjZEpyMcff){zKuoVYsLOn = true;}
      while(WbTkwaYRrY == TQrAjjVqqb){YNpnrcVThd = true;}
      while(kETTfMWDLq == kETTfMWDLq){KWRCPDuULZ = true;}
      while(WjZEpyMcff == WjZEpyMcff){qVpadWpDoD = true;}
      if(dFxKIGBlue == true){dFxKIGBlue = false;}
      if(ZEXLVWpMDT == true){ZEXLVWpMDT = false;}
      if(MVZzxlCPuy == true){MVZzxlCPuy = false;}
      if(NwlLueHILZ == true){NwlLueHILZ = false;}
      if(KkIfRRMNhS == true){KkIfRRMNhS = false;}
      if(HAYMTHfxMV == true){HAYMTHfxMV = false;}
      if(DlqwRcSLQp == true){DlqwRcSLQp = false;}
      if(PhAdIbNshf == true){PhAdIbNshf = false;}
      if(ZnhbqMWZrn == true){ZnhbqMWZrn = false;}
      if(zKuoVYsLOn == true){zKuoVYsLOn = false;}
      if(zBxqDZAtDr == true){zBxqDZAtDr = false;}
      if(slPgwPEOFE == true){slPgwPEOFE = false;}
      if(GrTcqFlKIj == true){GrTcqFlKIj = false;}
      if(hCetfXppYR == true){hCetfXppYR = false;}
      if(McWztNtOsF == true){McWztNtOsF = false;}
      if(UdGJhGgUAy == true){UdGJhGgUAy = false;}
      if(nolSJqHUAX == true){nolSJqHUAX = false;}
      if(YNpnrcVThd == true){YNpnrcVThd = false;}
      if(KWRCPDuULZ == true){KWRCPDuULZ = false;}
      if(qVpadWpDoD == true){qVpadWpDoD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUCBDVDOJK
{ 
  void kYWEHTlVSq()
  { 
      bool HPlfhwYUkz = false;
      bool nSfLkczIDg = false;
      bool ZwSspZLlVR = false;
      bool tMgBXedZeJ = false;
      bool GsZaEoCsez = false;
      bool cnuQhLxspH = false;
      bool jlzTFbldnF = false;
      bool yYdsagVroB = false;
      bool XSGVnGQQTM = false;
      bool gkjXZTtFUc = false;
      bool CYEYBDKBpA = false;
      bool oFEojQecfz = false;
      bool KVJbYNoFTG = false;
      bool mPWMyzOgTj = false;
      bool uOZTWbgunI = false;
      bool oQZVRgObAn = false;
      bool OEhjNZirpj = false;
      bool CxIwDwupFw = false;
      bool gtRLQVpAtR = false;
      bool jlgfUqgpFx = false;
      string WSzRrqbYuu;
      string qIsibVZEtS;
      string rfQVeupeqX;
      string poFcJRxlhV;
      string XJKODVCVwI;
      string UOxVBqBclx;
      string AxhWFCCPYK;
      string XmWXthUBSJ;
      string rUihCbqibS;
      string PTzjVabmJB;
      string SlwlkgrYbS;
      string VzKcFfNAUd;
      string KSnGtEmlCS;
      string GgrRqGXwxV;
      string iSHJwPJWeo;
      string NbSfqzypqf;
      string sGVILnHsky;
      string HRDytqLeJe;
      string uQGMFeNLar;
      string IhFQccxyxI;
      if(WSzRrqbYuu == SlwlkgrYbS){HPlfhwYUkz = true;}
      else if(SlwlkgrYbS == WSzRrqbYuu){CYEYBDKBpA = true;}
      if(qIsibVZEtS == VzKcFfNAUd){nSfLkczIDg = true;}
      else if(VzKcFfNAUd == qIsibVZEtS){oFEojQecfz = true;}
      if(rfQVeupeqX == KSnGtEmlCS){ZwSspZLlVR = true;}
      else if(KSnGtEmlCS == rfQVeupeqX){KVJbYNoFTG = true;}
      if(poFcJRxlhV == GgrRqGXwxV){tMgBXedZeJ = true;}
      else if(GgrRqGXwxV == poFcJRxlhV){mPWMyzOgTj = true;}
      if(XJKODVCVwI == iSHJwPJWeo){GsZaEoCsez = true;}
      else if(iSHJwPJWeo == XJKODVCVwI){uOZTWbgunI = true;}
      if(UOxVBqBclx == NbSfqzypqf){cnuQhLxspH = true;}
      else if(NbSfqzypqf == UOxVBqBclx){oQZVRgObAn = true;}
      if(AxhWFCCPYK == sGVILnHsky){jlzTFbldnF = true;}
      else if(sGVILnHsky == AxhWFCCPYK){OEhjNZirpj = true;}
      if(XmWXthUBSJ == HRDytqLeJe){yYdsagVroB = true;}
      if(rUihCbqibS == uQGMFeNLar){XSGVnGQQTM = true;}
      if(PTzjVabmJB == IhFQccxyxI){gkjXZTtFUc = true;}
      while(HRDytqLeJe == XmWXthUBSJ){CxIwDwupFw = true;}
      while(uQGMFeNLar == uQGMFeNLar){gtRLQVpAtR = true;}
      while(IhFQccxyxI == IhFQccxyxI){jlgfUqgpFx = true;}
      if(HPlfhwYUkz == true){HPlfhwYUkz = false;}
      if(nSfLkczIDg == true){nSfLkczIDg = false;}
      if(ZwSspZLlVR == true){ZwSspZLlVR = false;}
      if(tMgBXedZeJ == true){tMgBXedZeJ = false;}
      if(GsZaEoCsez == true){GsZaEoCsez = false;}
      if(cnuQhLxspH == true){cnuQhLxspH = false;}
      if(jlzTFbldnF == true){jlzTFbldnF = false;}
      if(yYdsagVroB == true){yYdsagVroB = false;}
      if(XSGVnGQQTM == true){XSGVnGQQTM = false;}
      if(gkjXZTtFUc == true){gkjXZTtFUc = false;}
      if(CYEYBDKBpA == true){CYEYBDKBpA = false;}
      if(oFEojQecfz == true){oFEojQecfz = false;}
      if(KVJbYNoFTG == true){KVJbYNoFTG = false;}
      if(mPWMyzOgTj == true){mPWMyzOgTj = false;}
      if(uOZTWbgunI == true){uOZTWbgunI = false;}
      if(oQZVRgObAn == true){oQZVRgObAn = false;}
      if(OEhjNZirpj == true){OEhjNZirpj = false;}
      if(CxIwDwupFw == true){CxIwDwupFw = false;}
      if(gtRLQVpAtR == true){gtRLQVpAtR = false;}
      if(jlgfUqgpFx == true){jlgfUqgpFx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZASUVLCLLV
{ 
  void QcEpwCtJEs()
  { 
      bool iQgbnHosoy = false;
      bool gmoAmREFwo = false;
      bool hRxdYmgaAr = false;
      bool RxmtKygfBS = false;
      bool glFpynewij = false;
      bool KuGyYQTCDA = false;
      bool ZOrxfiztpo = false;
      bool jXDcIuMGej = false;
      bool IkqPgWpnUt = false;
      bool debArRtIKP = false;
      bool njGtAlqcpd = false;
      bool ENWSroWbPJ = false;
      bool rKZuKFwCkp = false;
      bool BEwPuXdxPt = false;
      bool eMyqoQHIIC = false;
      bool uRrAWcKKit = false;
      bool porzcARGXU = false;
      bool KYMVdfMhGs = false;
      bool ymthuiLusS = false;
      bool MTNVDpUzOo = false;
      string lhhqjDxmUc;
      string AlyjKlQnEY;
      string kpIFDONzZS;
      string VKGEEXXzlE;
      string FUilUkjqWh;
      string AyhAjwZcnU;
      string oyNCGpetem;
      string NQBASQHWjR;
      string eWbrRXbGTI;
      string yuLROHHfed;
      string FoMjTjwggT;
      string nDrVoSVUji;
      string NYaVoREjlL;
      string IaqFLpKrXh;
      string auYzUuDpbw;
      string kluwQgOpuB;
      string fLuVLNLlJz;
      string HdxCHRAaBt;
      string ONHpZVetoe;
      string aTxVCPACnG;
      if(lhhqjDxmUc == FoMjTjwggT){iQgbnHosoy = true;}
      else if(FoMjTjwggT == lhhqjDxmUc){njGtAlqcpd = true;}
      if(AlyjKlQnEY == nDrVoSVUji){gmoAmREFwo = true;}
      else if(nDrVoSVUji == AlyjKlQnEY){ENWSroWbPJ = true;}
      if(kpIFDONzZS == NYaVoREjlL){hRxdYmgaAr = true;}
      else if(NYaVoREjlL == kpIFDONzZS){rKZuKFwCkp = true;}
      if(VKGEEXXzlE == IaqFLpKrXh){RxmtKygfBS = true;}
      else if(IaqFLpKrXh == VKGEEXXzlE){BEwPuXdxPt = true;}
      if(FUilUkjqWh == auYzUuDpbw){glFpynewij = true;}
      else if(auYzUuDpbw == FUilUkjqWh){eMyqoQHIIC = true;}
      if(AyhAjwZcnU == kluwQgOpuB){KuGyYQTCDA = true;}
      else if(kluwQgOpuB == AyhAjwZcnU){uRrAWcKKit = true;}
      if(oyNCGpetem == fLuVLNLlJz){ZOrxfiztpo = true;}
      else if(fLuVLNLlJz == oyNCGpetem){porzcARGXU = true;}
      if(NQBASQHWjR == HdxCHRAaBt){jXDcIuMGej = true;}
      if(eWbrRXbGTI == ONHpZVetoe){IkqPgWpnUt = true;}
      if(yuLROHHfed == aTxVCPACnG){debArRtIKP = true;}
      while(HdxCHRAaBt == NQBASQHWjR){KYMVdfMhGs = true;}
      while(ONHpZVetoe == ONHpZVetoe){ymthuiLusS = true;}
      while(aTxVCPACnG == aTxVCPACnG){MTNVDpUzOo = true;}
      if(iQgbnHosoy == true){iQgbnHosoy = false;}
      if(gmoAmREFwo == true){gmoAmREFwo = false;}
      if(hRxdYmgaAr == true){hRxdYmgaAr = false;}
      if(RxmtKygfBS == true){RxmtKygfBS = false;}
      if(glFpynewij == true){glFpynewij = false;}
      if(KuGyYQTCDA == true){KuGyYQTCDA = false;}
      if(ZOrxfiztpo == true){ZOrxfiztpo = false;}
      if(jXDcIuMGej == true){jXDcIuMGej = false;}
      if(IkqPgWpnUt == true){IkqPgWpnUt = false;}
      if(debArRtIKP == true){debArRtIKP = false;}
      if(njGtAlqcpd == true){njGtAlqcpd = false;}
      if(ENWSroWbPJ == true){ENWSroWbPJ = false;}
      if(rKZuKFwCkp == true){rKZuKFwCkp = false;}
      if(BEwPuXdxPt == true){BEwPuXdxPt = false;}
      if(eMyqoQHIIC == true){eMyqoQHIIC = false;}
      if(uRrAWcKKit == true){uRrAWcKKit = false;}
      if(porzcARGXU == true){porzcARGXU = false;}
      if(KYMVdfMhGs == true){KYMVdfMhGs = false;}
      if(ymthuiLusS == true){ymthuiLusS = false;}
      if(MTNVDpUzOo == true){MTNVDpUzOo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MJSSSIYAHT
{ 
  void CdEnFxzQwJ()
  { 
      bool IdRuXldZxz = false;
      bool LzZDjZRImZ = false;
      bool RWHAoIEVFA = false;
      bool eFHDWGEXXE = false;
      bool HlBaktXEPF = false;
      bool nGhARkWRGP = false;
      bool hITwUFrWgc = false;
      bool UsjiRfVfPt = false;
      bool kAGAMXXGkk = false;
      bool imRIWzREGe = false;
      bool CAWljtWzik = false;
      bool OqCLdgBSjw = false;
      bool hkkuthbaLR = false;
      bool NRYjrjcUQR = false;
      bool BXWAWqkFeo = false;
      bool xzTKwQObqC = false;
      bool SumQXwSRTs = false;
      bool EgCStJOkXC = false;
      bool wVwWUOyOma = false;
      bool VAcOyFkFbZ = false;
      string ocjfYhZxyg;
      string SYKVDPASHZ;
      string nssBFjuoVZ;
      string DEdFJnAUdj;
      string kPxiXIGYGi;
      string OZDJVwjian;
      string mjbYdOuEMO;
      string PfnXoYuJdw;
      string dVhmKdATjM;
      string ERtowAnYFI;
      string NCLrSikfTx;
      string AZEeKQCoNA;
      string OaUzJylyao;
      string kWDVhaKpTb;
      string rTAlMeMOee;
      string yzKFtlgMhU;
      string xlEeLcVhwi;
      string GLUkHtahle;
      string kWTwqlLyaw;
      string txHzeGOVai;
      if(ocjfYhZxyg == NCLrSikfTx){IdRuXldZxz = true;}
      else if(NCLrSikfTx == ocjfYhZxyg){CAWljtWzik = true;}
      if(SYKVDPASHZ == AZEeKQCoNA){LzZDjZRImZ = true;}
      else if(AZEeKQCoNA == SYKVDPASHZ){OqCLdgBSjw = true;}
      if(nssBFjuoVZ == OaUzJylyao){RWHAoIEVFA = true;}
      else if(OaUzJylyao == nssBFjuoVZ){hkkuthbaLR = true;}
      if(DEdFJnAUdj == kWDVhaKpTb){eFHDWGEXXE = true;}
      else if(kWDVhaKpTb == DEdFJnAUdj){NRYjrjcUQR = true;}
      if(kPxiXIGYGi == rTAlMeMOee){HlBaktXEPF = true;}
      else if(rTAlMeMOee == kPxiXIGYGi){BXWAWqkFeo = true;}
      if(OZDJVwjian == yzKFtlgMhU){nGhARkWRGP = true;}
      else if(yzKFtlgMhU == OZDJVwjian){xzTKwQObqC = true;}
      if(mjbYdOuEMO == xlEeLcVhwi){hITwUFrWgc = true;}
      else if(xlEeLcVhwi == mjbYdOuEMO){SumQXwSRTs = true;}
      if(PfnXoYuJdw == GLUkHtahle){UsjiRfVfPt = true;}
      if(dVhmKdATjM == kWTwqlLyaw){kAGAMXXGkk = true;}
      if(ERtowAnYFI == txHzeGOVai){imRIWzREGe = true;}
      while(GLUkHtahle == PfnXoYuJdw){EgCStJOkXC = true;}
      while(kWTwqlLyaw == kWTwqlLyaw){wVwWUOyOma = true;}
      while(txHzeGOVai == txHzeGOVai){VAcOyFkFbZ = true;}
      if(IdRuXldZxz == true){IdRuXldZxz = false;}
      if(LzZDjZRImZ == true){LzZDjZRImZ = false;}
      if(RWHAoIEVFA == true){RWHAoIEVFA = false;}
      if(eFHDWGEXXE == true){eFHDWGEXXE = false;}
      if(HlBaktXEPF == true){HlBaktXEPF = false;}
      if(nGhARkWRGP == true){nGhARkWRGP = false;}
      if(hITwUFrWgc == true){hITwUFrWgc = false;}
      if(UsjiRfVfPt == true){UsjiRfVfPt = false;}
      if(kAGAMXXGkk == true){kAGAMXXGkk = false;}
      if(imRIWzREGe == true){imRIWzREGe = false;}
      if(CAWljtWzik == true){CAWljtWzik = false;}
      if(OqCLdgBSjw == true){OqCLdgBSjw = false;}
      if(hkkuthbaLR == true){hkkuthbaLR = false;}
      if(NRYjrjcUQR == true){NRYjrjcUQR = false;}
      if(BXWAWqkFeo == true){BXWAWqkFeo = false;}
      if(xzTKwQObqC == true){xzTKwQObqC = false;}
      if(SumQXwSRTs == true){SumQXwSRTs = false;}
      if(EgCStJOkXC == true){EgCStJOkXC = false;}
      if(wVwWUOyOma == true){wVwWUOyOma = false;}
      if(VAcOyFkFbZ == true){VAcOyFkFbZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XMOSNXNDNZ
{ 
  void MSElHWLmZl()
  { 
      bool SKtyddVcks = false;
      bool wOFCZpdYKK = false;
      bool RlYTJmPXUX = false;
      bool ltYosYeuMx = false;
      bool KEAziRtijT = false;
      bool CfGBpflanq = false;
      bool OyHMGCpPIA = false;
      bool KiLMANlYjr = false;
      bool rgmAVFmWzN = false;
      bool mDGViMxmrg = false;
      bool bdZjISUsAc = false;
      bool sMqwzgKGqB = false;
      bool OSQtMHcpdn = false;
      bool QygCPNGDrC = false;
      bool ktVWUaMJWB = false;
      bool BpwqSINeXB = false;
      bool peOLLtenfk = false;
      bool ZGOoPTwtZk = false;
      bool tSSblZCpjH = false;
      bool AbfpLGeKKZ = false;
      string hbylYgzePi;
      string quPxOWaAds;
      string hmzeqfbepx;
      string NjhtsUpaFN;
      string DshVEhJNLC;
      string kCojPucTts;
      string EUoSVHMUEt;
      string gAuQpnFcZI;
      string VNSnLLtyey;
      string qVfMIhEOAx;
      string VoJRUkGYta;
      string oAtlWqCAGJ;
      string MOoGCLTiIH;
      string jpbcmfDASa;
      string EVDDIpbtoQ;
      string fDIpjHADOJ;
      string QXPlqzXQzp;
      string mBhfFqKkyL;
      string jZsqbfgkrf;
      string fAlJKgFQMI;
      if(hbylYgzePi == VoJRUkGYta){SKtyddVcks = true;}
      else if(VoJRUkGYta == hbylYgzePi){bdZjISUsAc = true;}
      if(quPxOWaAds == oAtlWqCAGJ){wOFCZpdYKK = true;}
      else if(oAtlWqCAGJ == quPxOWaAds){sMqwzgKGqB = true;}
      if(hmzeqfbepx == MOoGCLTiIH){RlYTJmPXUX = true;}
      else if(MOoGCLTiIH == hmzeqfbepx){OSQtMHcpdn = true;}
      if(NjhtsUpaFN == jpbcmfDASa){ltYosYeuMx = true;}
      else if(jpbcmfDASa == NjhtsUpaFN){QygCPNGDrC = true;}
      if(DshVEhJNLC == EVDDIpbtoQ){KEAziRtijT = true;}
      else if(EVDDIpbtoQ == DshVEhJNLC){ktVWUaMJWB = true;}
      if(kCojPucTts == fDIpjHADOJ){CfGBpflanq = true;}
      else if(fDIpjHADOJ == kCojPucTts){BpwqSINeXB = true;}
      if(EUoSVHMUEt == QXPlqzXQzp){OyHMGCpPIA = true;}
      else if(QXPlqzXQzp == EUoSVHMUEt){peOLLtenfk = true;}
      if(gAuQpnFcZI == mBhfFqKkyL){KiLMANlYjr = true;}
      if(VNSnLLtyey == jZsqbfgkrf){rgmAVFmWzN = true;}
      if(qVfMIhEOAx == fAlJKgFQMI){mDGViMxmrg = true;}
      while(mBhfFqKkyL == gAuQpnFcZI){ZGOoPTwtZk = true;}
      while(jZsqbfgkrf == jZsqbfgkrf){tSSblZCpjH = true;}
      while(fAlJKgFQMI == fAlJKgFQMI){AbfpLGeKKZ = true;}
      if(SKtyddVcks == true){SKtyddVcks = false;}
      if(wOFCZpdYKK == true){wOFCZpdYKK = false;}
      if(RlYTJmPXUX == true){RlYTJmPXUX = false;}
      if(ltYosYeuMx == true){ltYosYeuMx = false;}
      if(KEAziRtijT == true){KEAziRtijT = false;}
      if(CfGBpflanq == true){CfGBpflanq = false;}
      if(OyHMGCpPIA == true){OyHMGCpPIA = false;}
      if(KiLMANlYjr == true){KiLMANlYjr = false;}
      if(rgmAVFmWzN == true){rgmAVFmWzN = false;}
      if(mDGViMxmrg == true){mDGViMxmrg = false;}
      if(bdZjISUsAc == true){bdZjISUsAc = false;}
      if(sMqwzgKGqB == true){sMqwzgKGqB = false;}
      if(OSQtMHcpdn == true){OSQtMHcpdn = false;}
      if(QygCPNGDrC == true){QygCPNGDrC = false;}
      if(ktVWUaMJWB == true){ktVWUaMJWB = false;}
      if(BpwqSINeXB == true){BpwqSINeXB = false;}
      if(peOLLtenfk == true){peOLLtenfk = false;}
      if(ZGOoPTwtZk == true){ZGOoPTwtZk = false;}
      if(tSSblZCpjH == true){tSSblZCpjH = false;}
      if(AbfpLGeKKZ == true){AbfpLGeKKZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DZWQFFQXFZ
{ 
  void GTgVNwMcgO()
  { 
      bool oEqkGSQxdE = false;
      bool yjcoCBmVQO = false;
      bool IDeWgBruow = false;
      bool EGfzdFzouX = false;
      bool NwNpZiufGD = false;
      bool pRcoBkZUDE = false;
      bool aVHgArDcKx = false;
      bool CyarBLonxy = false;
      bool GLolGldpyr = false;
      bool fdkpxrogph = false;
      bool eSVJBrqjno = false;
      bool wkWFyOfVZN = false;
      bool NNdSQXNkuJ = false;
      bool WIxPSmpfjO = false;
      bool usCJwuHeqi = false;
      bool LSGcTRnCrd = false;
      bool eFoeSmmHlK = false;
      bool XAkLRUKUVV = false;
      bool PhsLxDBUuB = false;
      bool ymmGioEXpI = false;
      string OVaoksCRfD;
      string klCXGxchKx;
      string tIQPAKrYQX;
      string XPGfDeJsyO;
      string BxpAVeXakq;
      string FIzaoFFLnZ;
      string AdAIfUfWTb;
      string mijuuwSPsV;
      string mRmZSOQfpy;
      string YxFXOXwhUB;
      string yAHJDVYEes;
      string mpRSmiqapQ;
      string EAgUCpdLgX;
      string zkurWlJcWw;
      string pLAxLiemke;
      string gVqDwyTlHN;
      string rMXHsCtZuA;
      string YNEtZrzjJS;
      string KpZBqdsquX;
      string SXUIEcnsDJ;
      if(OVaoksCRfD == yAHJDVYEes){oEqkGSQxdE = true;}
      else if(yAHJDVYEes == OVaoksCRfD){eSVJBrqjno = true;}
      if(klCXGxchKx == mpRSmiqapQ){yjcoCBmVQO = true;}
      else if(mpRSmiqapQ == klCXGxchKx){wkWFyOfVZN = true;}
      if(tIQPAKrYQX == EAgUCpdLgX){IDeWgBruow = true;}
      else if(EAgUCpdLgX == tIQPAKrYQX){NNdSQXNkuJ = true;}
      if(XPGfDeJsyO == zkurWlJcWw){EGfzdFzouX = true;}
      else if(zkurWlJcWw == XPGfDeJsyO){WIxPSmpfjO = true;}
      if(BxpAVeXakq == pLAxLiemke){NwNpZiufGD = true;}
      else if(pLAxLiemke == BxpAVeXakq){usCJwuHeqi = true;}
      if(FIzaoFFLnZ == gVqDwyTlHN){pRcoBkZUDE = true;}
      else if(gVqDwyTlHN == FIzaoFFLnZ){LSGcTRnCrd = true;}
      if(AdAIfUfWTb == rMXHsCtZuA){aVHgArDcKx = true;}
      else if(rMXHsCtZuA == AdAIfUfWTb){eFoeSmmHlK = true;}
      if(mijuuwSPsV == YNEtZrzjJS){CyarBLonxy = true;}
      if(mRmZSOQfpy == KpZBqdsquX){GLolGldpyr = true;}
      if(YxFXOXwhUB == SXUIEcnsDJ){fdkpxrogph = true;}
      while(YNEtZrzjJS == mijuuwSPsV){XAkLRUKUVV = true;}
      while(KpZBqdsquX == KpZBqdsquX){PhsLxDBUuB = true;}
      while(SXUIEcnsDJ == SXUIEcnsDJ){ymmGioEXpI = true;}
      if(oEqkGSQxdE == true){oEqkGSQxdE = false;}
      if(yjcoCBmVQO == true){yjcoCBmVQO = false;}
      if(IDeWgBruow == true){IDeWgBruow = false;}
      if(EGfzdFzouX == true){EGfzdFzouX = false;}
      if(NwNpZiufGD == true){NwNpZiufGD = false;}
      if(pRcoBkZUDE == true){pRcoBkZUDE = false;}
      if(aVHgArDcKx == true){aVHgArDcKx = false;}
      if(CyarBLonxy == true){CyarBLonxy = false;}
      if(GLolGldpyr == true){GLolGldpyr = false;}
      if(fdkpxrogph == true){fdkpxrogph = false;}
      if(eSVJBrqjno == true){eSVJBrqjno = false;}
      if(wkWFyOfVZN == true){wkWFyOfVZN = false;}
      if(NNdSQXNkuJ == true){NNdSQXNkuJ = false;}
      if(WIxPSmpfjO == true){WIxPSmpfjO = false;}
      if(usCJwuHeqi == true){usCJwuHeqi = false;}
      if(LSGcTRnCrd == true){LSGcTRnCrd = false;}
      if(eFoeSmmHlK == true){eFoeSmmHlK = false;}
      if(XAkLRUKUVV == true){XAkLRUKUVV = false;}
      if(PhsLxDBUuB == true){PhsLxDBUuB = false;}
      if(ymmGioEXpI == true){ymmGioEXpI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBCAPBKFLL
{ 
  void QdkJFXhxmE()
  { 
      bool uekboWuHxP = false;
      bool yEuBgBeFuT = false;
      bool zRedkkIMUM = false;
      bool wnRIRoLHKf = false;
      bool deVPWSJFAM = false;
      bool QfztQczGqE = false;
      bool NiljSKmljr = false;
      bool pWuOpUwPHR = false;
      bool aDLIwQnWqn = false;
      bool oEQFRurkwL = false;
      bool eXVIWskjEw = false;
      bool gjyYdKXdnC = false;
      bool VQtuCkGoxt = false;
      bool cKSwmDhCkC = false;
      bool eESuGFFqbH = false;
      bool XNxsoOcZGk = false;
      bool mumJTWQCla = false;
      bool bUrlWRyznw = false;
      bool eONpWOMZGX = false;
      bool ZIwAPiQIbi = false;
      string WrTsUGobmW;
      string puXrjMYfMD;
      string grkceSRYAx;
      string HnlOxyWCGk;
      string nwcnZSistC;
      string DKMDueHqOC;
      string oPbpPBJItk;
      string pVZbOjPxCL;
      string iYexswbhTR;
      string qenEwYUlYX;
      string JZyIMgkkoK;
      string OKoCSQkdwS;
      string ZboctKhVep;
      string PcYdCJaVjM;
      string KqsJCgpkke;
      string mppFygkUOC;
      string yPFytlkKzJ;
      string pPtiIhhfZN;
      string UxjzDZlSeU;
      string XFGhNultOQ;
      if(WrTsUGobmW == JZyIMgkkoK){uekboWuHxP = true;}
      else if(JZyIMgkkoK == WrTsUGobmW){eXVIWskjEw = true;}
      if(puXrjMYfMD == OKoCSQkdwS){yEuBgBeFuT = true;}
      else if(OKoCSQkdwS == puXrjMYfMD){gjyYdKXdnC = true;}
      if(grkceSRYAx == ZboctKhVep){zRedkkIMUM = true;}
      else if(ZboctKhVep == grkceSRYAx){VQtuCkGoxt = true;}
      if(HnlOxyWCGk == PcYdCJaVjM){wnRIRoLHKf = true;}
      else if(PcYdCJaVjM == HnlOxyWCGk){cKSwmDhCkC = true;}
      if(nwcnZSistC == KqsJCgpkke){deVPWSJFAM = true;}
      else if(KqsJCgpkke == nwcnZSistC){eESuGFFqbH = true;}
      if(DKMDueHqOC == mppFygkUOC){QfztQczGqE = true;}
      else if(mppFygkUOC == DKMDueHqOC){XNxsoOcZGk = true;}
      if(oPbpPBJItk == yPFytlkKzJ){NiljSKmljr = true;}
      else if(yPFytlkKzJ == oPbpPBJItk){mumJTWQCla = true;}
      if(pVZbOjPxCL == pPtiIhhfZN){pWuOpUwPHR = true;}
      if(iYexswbhTR == UxjzDZlSeU){aDLIwQnWqn = true;}
      if(qenEwYUlYX == XFGhNultOQ){oEQFRurkwL = true;}
      while(pPtiIhhfZN == pVZbOjPxCL){bUrlWRyznw = true;}
      while(UxjzDZlSeU == UxjzDZlSeU){eONpWOMZGX = true;}
      while(XFGhNultOQ == XFGhNultOQ){ZIwAPiQIbi = true;}
      if(uekboWuHxP == true){uekboWuHxP = false;}
      if(yEuBgBeFuT == true){yEuBgBeFuT = false;}
      if(zRedkkIMUM == true){zRedkkIMUM = false;}
      if(wnRIRoLHKf == true){wnRIRoLHKf = false;}
      if(deVPWSJFAM == true){deVPWSJFAM = false;}
      if(QfztQczGqE == true){QfztQczGqE = false;}
      if(NiljSKmljr == true){NiljSKmljr = false;}
      if(pWuOpUwPHR == true){pWuOpUwPHR = false;}
      if(aDLIwQnWqn == true){aDLIwQnWqn = false;}
      if(oEQFRurkwL == true){oEQFRurkwL = false;}
      if(eXVIWskjEw == true){eXVIWskjEw = false;}
      if(gjyYdKXdnC == true){gjyYdKXdnC = false;}
      if(VQtuCkGoxt == true){VQtuCkGoxt = false;}
      if(cKSwmDhCkC == true){cKSwmDhCkC = false;}
      if(eESuGFFqbH == true){eESuGFFqbH = false;}
      if(XNxsoOcZGk == true){XNxsoOcZGk = false;}
      if(mumJTWQCla == true){mumJTWQCla = false;}
      if(bUrlWRyznw == true){bUrlWRyznw = false;}
      if(eONpWOMZGX == true){eONpWOMZGX = false;}
      if(ZIwAPiQIbi == true){ZIwAPiQIbi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CRIZVBZTLE
{ 
  void wZAbmKhdYz()
  { 
      bool ARFVmfZmrN = false;
      bool ymwxYTLkWy = false;
      bool xrWVIGxGqb = false;
      bool qyMoHJHYeM = false;
      bool oyLnurpApM = false;
      bool lULpDIujMf = false;
      bool iTuPWzaHoP = false;
      bool MmFKIyghaP = false;
      bool PxPdpVlVly = false;
      bool OXLycVDuRw = false;
      bool QiKaAzOBgE = false;
      bool bMJwPlDQZB = false;
      bool MEUpAnbHgm = false;
      bool ukPdzglncq = false;
      bool GkogWBOOhq = false;
      bool RlUQjLNTaM = false;
      bool WHTsJpwexh = false;
      bool AOmitaPmSz = false;
      bool ZMZpUJPztm = false;
      bool TRNQTyRuXg = false;
      string ACYyztFVOm;
      string RhekdriFAe;
      string BUMHUgotzr;
      string tEPzuGunjE;
      string jFWqdgWCgQ;
      string LfweVeoQdR;
      string FKVVsNSfoW;
      string xtVwtuyVdn;
      string KlMigNHjcP;
      string QdKRyZiAyQ;
      string NpMKSRJzka;
      string gTmoHSxlne;
      string FhCZFSiDxU;
      string MxXNZTZCPP;
      string EIzCixqVJf;
      string bwLSKfnmFA;
      string hFCPNiwYPn;
      string suVYaxhApH;
      string aNtRsPkECs;
      string fmxPgyFinA;
      if(ACYyztFVOm == NpMKSRJzka){ARFVmfZmrN = true;}
      else if(NpMKSRJzka == ACYyztFVOm){QiKaAzOBgE = true;}
      if(RhekdriFAe == gTmoHSxlne){ymwxYTLkWy = true;}
      else if(gTmoHSxlne == RhekdriFAe){bMJwPlDQZB = true;}
      if(BUMHUgotzr == FhCZFSiDxU){xrWVIGxGqb = true;}
      else if(FhCZFSiDxU == BUMHUgotzr){MEUpAnbHgm = true;}
      if(tEPzuGunjE == MxXNZTZCPP){qyMoHJHYeM = true;}
      else if(MxXNZTZCPP == tEPzuGunjE){ukPdzglncq = true;}
      if(jFWqdgWCgQ == EIzCixqVJf){oyLnurpApM = true;}
      else if(EIzCixqVJf == jFWqdgWCgQ){GkogWBOOhq = true;}
      if(LfweVeoQdR == bwLSKfnmFA){lULpDIujMf = true;}
      else if(bwLSKfnmFA == LfweVeoQdR){RlUQjLNTaM = true;}
      if(FKVVsNSfoW == hFCPNiwYPn){iTuPWzaHoP = true;}
      else if(hFCPNiwYPn == FKVVsNSfoW){WHTsJpwexh = true;}
      if(xtVwtuyVdn == suVYaxhApH){MmFKIyghaP = true;}
      if(KlMigNHjcP == aNtRsPkECs){PxPdpVlVly = true;}
      if(QdKRyZiAyQ == fmxPgyFinA){OXLycVDuRw = true;}
      while(suVYaxhApH == xtVwtuyVdn){AOmitaPmSz = true;}
      while(aNtRsPkECs == aNtRsPkECs){ZMZpUJPztm = true;}
      while(fmxPgyFinA == fmxPgyFinA){TRNQTyRuXg = true;}
      if(ARFVmfZmrN == true){ARFVmfZmrN = false;}
      if(ymwxYTLkWy == true){ymwxYTLkWy = false;}
      if(xrWVIGxGqb == true){xrWVIGxGqb = false;}
      if(qyMoHJHYeM == true){qyMoHJHYeM = false;}
      if(oyLnurpApM == true){oyLnurpApM = false;}
      if(lULpDIujMf == true){lULpDIujMf = false;}
      if(iTuPWzaHoP == true){iTuPWzaHoP = false;}
      if(MmFKIyghaP == true){MmFKIyghaP = false;}
      if(PxPdpVlVly == true){PxPdpVlVly = false;}
      if(OXLycVDuRw == true){OXLycVDuRw = false;}
      if(QiKaAzOBgE == true){QiKaAzOBgE = false;}
      if(bMJwPlDQZB == true){bMJwPlDQZB = false;}
      if(MEUpAnbHgm == true){MEUpAnbHgm = false;}
      if(ukPdzglncq == true){ukPdzglncq = false;}
      if(GkogWBOOhq == true){GkogWBOOhq = false;}
      if(RlUQjLNTaM == true){RlUQjLNTaM = false;}
      if(WHTsJpwexh == true){WHTsJpwexh = false;}
      if(AOmitaPmSz == true){AOmitaPmSz = false;}
      if(ZMZpUJPztm == true){ZMZpUJPztm = false;}
      if(TRNQTyRuXg == true){TRNQTyRuXg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELXXFDLLZO
{ 
  void jGfELFjDxY()
  { 
      bool SVVItaFHXJ = false;
      bool YBAHCFFbZS = false;
      bool NaMcPXVKRJ = false;
      bool zncRASqsCx = false;
      bool XRitPIMWYj = false;
      bool dWSIlqIrsV = false;
      bool FupNJjXiGj = false;
      bool NMYcuurSNG = false;
      bool LykgfbUUeJ = false;
      bool JyzgqcbVje = false;
      bool kcPoVQypNq = false;
      bool ypelKHJIgg = false;
      bool PDExaOMrkR = false;
      bool SWhhUiiwLO = false;
      bool ddGmKSTMWj = false;
      bool TToCOhXSNG = false;
      bool EGEuXbIwQa = false;
      bool YMxRDkxQlI = false;
      bool uzVByzgeTm = false;
      bool KPiEKXYKPh = false;
      string bPsxwIatgx;
      string xgBWKkeZnR;
      string NjlVOEoVBq;
      string hATfFipgPO;
      string lqSPbqEnVO;
      string QAadoqcXiq;
      string SFsoPwNURa;
      string tyJYfVQWsX;
      string ABAmagZoqN;
      string GSyYwfyczf;
      string djVtTSqByS;
      string aFeLpQFFOi;
      string WXcDTbzjcz;
      string WnXNtQeFSH;
      string pXqXmAmmhe;
      string arNQIFGRaq;
      string SGYywmhRRZ;
      string kzmGsygEQS;
      string nMBxXdZGEn;
      string KMdboizsbz;
      if(bPsxwIatgx == djVtTSqByS){SVVItaFHXJ = true;}
      else if(djVtTSqByS == bPsxwIatgx){kcPoVQypNq = true;}
      if(xgBWKkeZnR == aFeLpQFFOi){YBAHCFFbZS = true;}
      else if(aFeLpQFFOi == xgBWKkeZnR){ypelKHJIgg = true;}
      if(NjlVOEoVBq == WXcDTbzjcz){NaMcPXVKRJ = true;}
      else if(WXcDTbzjcz == NjlVOEoVBq){PDExaOMrkR = true;}
      if(hATfFipgPO == WnXNtQeFSH){zncRASqsCx = true;}
      else if(WnXNtQeFSH == hATfFipgPO){SWhhUiiwLO = true;}
      if(lqSPbqEnVO == pXqXmAmmhe){XRitPIMWYj = true;}
      else if(pXqXmAmmhe == lqSPbqEnVO){ddGmKSTMWj = true;}
      if(QAadoqcXiq == arNQIFGRaq){dWSIlqIrsV = true;}
      else if(arNQIFGRaq == QAadoqcXiq){TToCOhXSNG = true;}
      if(SFsoPwNURa == SGYywmhRRZ){FupNJjXiGj = true;}
      else if(SGYywmhRRZ == SFsoPwNURa){EGEuXbIwQa = true;}
      if(tyJYfVQWsX == kzmGsygEQS){NMYcuurSNG = true;}
      if(ABAmagZoqN == nMBxXdZGEn){LykgfbUUeJ = true;}
      if(GSyYwfyczf == KMdboizsbz){JyzgqcbVje = true;}
      while(kzmGsygEQS == tyJYfVQWsX){YMxRDkxQlI = true;}
      while(nMBxXdZGEn == nMBxXdZGEn){uzVByzgeTm = true;}
      while(KMdboizsbz == KMdboizsbz){KPiEKXYKPh = true;}
      if(SVVItaFHXJ == true){SVVItaFHXJ = false;}
      if(YBAHCFFbZS == true){YBAHCFFbZS = false;}
      if(NaMcPXVKRJ == true){NaMcPXVKRJ = false;}
      if(zncRASqsCx == true){zncRASqsCx = false;}
      if(XRitPIMWYj == true){XRitPIMWYj = false;}
      if(dWSIlqIrsV == true){dWSIlqIrsV = false;}
      if(FupNJjXiGj == true){FupNJjXiGj = false;}
      if(NMYcuurSNG == true){NMYcuurSNG = false;}
      if(LykgfbUUeJ == true){LykgfbUUeJ = false;}
      if(JyzgqcbVje == true){JyzgqcbVje = false;}
      if(kcPoVQypNq == true){kcPoVQypNq = false;}
      if(ypelKHJIgg == true){ypelKHJIgg = false;}
      if(PDExaOMrkR == true){PDExaOMrkR = false;}
      if(SWhhUiiwLO == true){SWhhUiiwLO = false;}
      if(ddGmKSTMWj == true){ddGmKSTMWj = false;}
      if(TToCOhXSNG == true){TToCOhXSNG = false;}
      if(EGEuXbIwQa == true){EGEuXbIwQa = false;}
      if(YMxRDkxQlI == true){YMxRDkxQlI = false;}
      if(uzVByzgeTm == true){uzVByzgeTm = false;}
      if(KPiEKXYKPh == true){KPiEKXYKPh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WLXWQUIUBS
{ 
  void JVKjjxpYRr()
  { 
      bool ddzNtSQjur = false;
      bool PzTtxAWBxo = false;
      bool rAwqFEfRuO = false;
      bool tbGzYqPXBN = false;
      bool zgQxuCEhFe = false;
      bool GwpSVdhHIo = false;
      bool myngxmrTVF = false;
      bool kzzjoLizwC = false;
      bool zxMPIylmdt = false;
      bool JHPLaBrjzI = false;
      bool KjMztHwGdK = false;
      bool thLFpolYXz = false;
      bool BEpaucinJn = false;
      bool SyzmrOkMVB = false;
      bool BfJSAauJUk = false;
      bool OTMAHFskER = false;
      bool XIwpqwiXNb = false;
      bool EZCWxVuXaT = false;
      bool gZSXYzlyfm = false;
      bool UzHDdriSbE = false;
      string CHdKUtFDjH;
      string trxFlwOVkY;
      string SCYTJqmGne;
      string WwFBJmkyVM;
      string HpoEVCkNoP;
      string zRmBhAhJBc;
      string HyPEjxmuuy;
      string LPAXQbNUyG;
      string FYQYfEJDTJ;
      string EaxrFJajTX;
      string PpSqDiROkG;
      string lNLtWihpYf;
      string mibkskSHRH;
      string BcAZqPFZVw;
      string mtSMXqOCVW;
      string akLnkfNgxS;
      string QJwdFJMkCH;
      string cIUbrrQONC;
      string VPlufPQMoL;
      string BYcCfdxnHN;
      if(CHdKUtFDjH == PpSqDiROkG){ddzNtSQjur = true;}
      else if(PpSqDiROkG == CHdKUtFDjH){KjMztHwGdK = true;}
      if(trxFlwOVkY == lNLtWihpYf){PzTtxAWBxo = true;}
      else if(lNLtWihpYf == trxFlwOVkY){thLFpolYXz = true;}
      if(SCYTJqmGne == mibkskSHRH){rAwqFEfRuO = true;}
      else if(mibkskSHRH == SCYTJqmGne){BEpaucinJn = true;}
      if(WwFBJmkyVM == BcAZqPFZVw){tbGzYqPXBN = true;}
      else if(BcAZqPFZVw == WwFBJmkyVM){SyzmrOkMVB = true;}
      if(HpoEVCkNoP == mtSMXqOCVW){zgQxuCEhFe = true;}
      else if(mtSMXqOCVW == HpoEVCkNoP){BfJSAauJUk = true;}
      if(zRmBhAhJBc == akLnkfNgxS){GwpSVdhHIo = true;}
      else if(akLnkfNgxS == zRmBhAhJBc){OTMAHFskER = true;}
      if(HyPEjxmuuy == QJwdFJMkCH){myngxmrTVF = true;}
      else if(QJwdFJMkCH == HyPEjxmuuy){XIwpqwiXNb = true;}
      if(LPAXQbNUyG == cIUbrrQONC){kzzjoLizwC = true;}
      if(FYQYfEJDTJ == VPlufPQMoL){zxMPIylmdt = true;}
      if(EaxrFJajTX == BYcCfdxnHN){JHPLaBrjzI = true;}
      while(cIUbrrQONC == LPAXQbNUyG){EZCWxVuXaT = true;}
      while(VPlufPQMoL == VPlufPQMoL){gZSXYzlyfm = true;}
      while(BYcCfdxnHN == BYcCfdxnHN){UzHDdriSbE = true;}
      if(ddzNtSQjur == true){ddzNtSQjur = false;}
      if(PzTtxAWBxo == true){PzTtxAWBxo = false;}
      if(rAwqFEfRuO == true){rAwqFEfRuO = false;}
      if(tbGzYqPXBN == true){tbGzYqPXBN = false;}
      if(zgQxuCEhFe == true){zgQxuCEhFe = false;}
      if(GwpSVdhHIo == true){GwpSVdhHIo = false;}
      if(myngxmrTVF == true){myngxmrTVF = false;}
      if(kzzjoLizwC == true){kzzjoLizwC = false;}
      if(zxMPIylmdt == true){zxMPIylmdt = false;}
      if(JHPLaBrjzI == true){JHPLaBrjzI = false;}
      if(KjMztHwGdK == true){KjMztHwGdK = false;}
      if(thLFpolYXz == true){thLFpolYXz = false;}
      if(BEpaucinJn == true){BEpaucinJn = false;}
      if(SyzmrOkMVB == true){SyzmrOkMVB = false;}
      if(BfJSAauJUk == true){BfJSAauJUk = false;}
      if(OTMAHFskER == true){OTMAHFskER = false;}
      if(XIwpqwiXNb == true){XIwpqwiXNb = false;}
      if(EZCWxVuXaT == true){EZCWxVuXaT = false;}
      if(gZSXYzlyfm == true){gZSXYzlyfm = false;}
      if(UzHDdriSbE == true){UzHDdriSbE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HHPOUKCYCH
{ 
  void xsbJTyiOZi()
  { 
      bool LEXGtGqPUz = false;
      bool ZDDPmAerhR = false;
      bool iJiAYUsbAF = false;
      bool GqJxjWnEAX = false;
      bool QEXkJKQnYr = false;
      bool fDVoGBUXhY = false;
      bool NPOPshtGfQ = false;
      bool MarJBdkypN = false;
      bool DECIZDVTph = false;
      bool BPVaKApIqb = false;
      bool PKHIfEKLmb = false;
      bool PWhTVIMGpo = false;
      bool LZPyOwEQzA = false;
      bool ncGOxswtcU = false;
      bool rKgORehCFB = false;
      bool niSBPptJsi = false;
      bool AtMlmmPSWb = false;
      bool LSdUxAsBgj = false;
      bool OCLxMEKEyH = false;
      bool ymAsTyytae = false;
      string xTYQqwEiUf;
      string RjpBLnnInS;
      string gdEsqRLGfj;
      string OhLttJJWnW;
      string QxrVUFPcWr;
      string xQhyxSPeZY;
      string jxDkQiYwGC;
      string dQUQCikiYk;
      string ChjnlyzMwa;
      string tewPlStHEl;
      string gTWTNgwRwO;
      string gfGnVCNOyS;
      string jLzfIzTFei;
      string nddlEiLPaF;
      string ChQhsNXHsj;
      string EfIkBUUpLO;
      string MqlMaDCTjm;
      string pxnsQBuQlu;
      string aLLteIUrki;
      string OUEMrLuDHo;
      if(xTYQqwEiUf == gTWTNgwRwO){LEXGtGqPUz = true;}
      else if(gTWTNgwRwO == xTYQqwEiUf){PKHIfEKLmb = true;}
      if(RjpBLnnInS == gfGnVCNOyS){ZDDPmAerhR = true;}
      else if(gfGnVCNOyS == RjpBLnnInS){PWhTVIMGpo = true;}
      if(gdEsqRLGfj == jLzfIzTFei){iJiAYUsbAF = true;}
      else if(jLzfIzTFei == gdEsqRLGfj){LZPyOwEQzA = true;}
      if(OhLttJJWnW == nddlEiLPaF){GqJxjWnEAX = true;}
      else if(nddlEiLPaF == OhLttJJWnW){ncGOxswtcU = true;}
      if(QxrVUFPcWr == ChQhsNXHsj){QEXkJKQnYr = true;}
      else if(ChQhsNXHsj == QxrVUFPcWr){rKgORehCFB = true;}
      if(xQhyxSPeZY == EfIkBUUpLO){fDVoGBUXhY = true;}
      else if(EfIkBUUpLO == xQhyxSPeZY){niSBPptJsi = true;}
      if(jxDkQiYwGC == MqlMaDCTjm){NPOPshtGfQ = true;}
      else if(MqlMaDCTjm == jxDkQiYwGC){AtMlmmPSWb = true;}
      if(dQUQCikiYk == pxnsQBuQlu){MarJBdkypN = true;}
      if(ChjnlyzMwa == aLLteIUrki){DECIZDVTph = true;}
      if(tewPlStHEl == OUEMrLuDHo){BPVaKApIqb = true;}
      while(pxnsQBuQlu == dQUQCikiYk){LSdUxAsBgj = true;}
      while(aLLteIUrki == aLLteIUrki){OCLxMEKEyH = true;}
      while(OUEMrLuDHo == OUEMrLuDHo){ymAsTyytae = true;}
      if(LEXGtGqPUz == true){LEXGtGqPUz = false;}
      if(ZDDPmAerhR == true){ZDDPmAerhR = false;}
      if(iJiAYUsbAF == true){iJiAYUsbAF = false;}
      if(GqJxjWnEAX == true){GqJxjWnEAX = false;}
      if(QEXkJKQnYr == true){QEXkJKQnYr = false;}
      if(fDVoGBUXhY == true){fDVoGBUXhY = false;}
      if(NPOPshtGfQ == true){NPOPshtGfQ = false;}
      if(MarJBdkypN == true){MarJBdkypN = false;}
      if(DECIZDVTph == true){DECIZDVTph = false;}
      if(BPVaKApIqb == true){BPVaKApIqb = false;}
      if(PKHIfEKLmb == true){PKHIfEKLmb = false;}
      if(PWhTVIMGpo == true){PWhTVIMGpo = false;}
      if(LZPyOwEQzA == true){LZPyOwEQzA = false;}
      if(ncGOxswtcU == true){ncGOxswtcU = false;}
      if(rKgORehCFB == true){rKgORehCFB = false;}
      if(niSBPptJsi == true){niSBPptJsi = false;}
      if(AtMlmmPSWb == true){AtMlmmPSWb = false;}
      if(LSdUxAsBgj == true){LSdUxAsBgj = false;}
      if(OCLxMEKEyH == true){OCLxMEKEyH = false;}
      if(ymAsTyytae == true){ymAsTyytae = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IFVPHDHWWJ
{ 
  void aRRldZxwkg()
  { 
      bool CpZWSxSOFj = false;
      bool yBeThYlAOa = false;
      bool QQmnptVmae = false;
      bool ANgrDOniuw = false;
      bool OXmufjrVZC = false;
      bool CPPoUlDkgX = false;
      bool aemaikTmPT = false;
      bool jCFRMscqHF = false;
      bool CANYbkxqWR = false;
      bool KDCXUijMMu = false;
      bool PEFGRzJxbb = false;
      bool IMcaUaRNyx = false;
      bool nbQyJgAhxd = false;
      bool IQeMpxtHHc = false;
      bool azPtIyZaCt = false;
      bool QVOOGmnHxj = false;
      bool ybAyTrhPjX = false;
      bool fKGVVnMWoK = false;
      bool GYeDMlCQFC = false;
      bool JmKWdzzRaQ = false;
      string lMlUtNlEYS;
      string eXkALBHohD;
      string sutLncBERx;
      string oqujlFgPax;
      string QrJDjxWqxU;
      string mKyxFqSZfR;
      string LgmbdnbBNF;
      string UqNklBkqbp;
      string GKGwKdrxdu;
      string mGiJliFhYw;
      string UVcrAuwNKE;
      string FayoLAZqQA;
      string udWSSNHEzC;
      string uCRfVjhOuO;
      string gemYoLIsyk;
      string IOQYApyJZm;
      string mrOIICJRTa;
      string SLuCTQqxdG;
      string EOGNsglree;
      string kXoHanPdQl;
      if(lMlUtNlEYS == UVcrAuwNKE){CpZWSxSOFj = true;}
      else if(UVcrAuwNKE == lMlUtNlEYS){PEFGRzJxbb = true;}
      if(eXkALBHohD == FayoLAZqQA){yBeThYlAOa = true;}
      else if(FayoLAZqQA == eXkALBHohD){IMcaUaRNyx = true;}
      if(sutLncBERx == udWSSNHEzC){QQmnptVmae = true;}
      else if(udWSSNHEzC == sutLncBERx){nbQyJgAhxd = true;}
      if(oqujlFgPax == uCRfVjhOuO){ANgrDOniuw = true;}
      else if(uCRfVjhOuO == oqujlFgPax){IQeMpxtHHc = true;}
      if(QrJDjxWqxU == gemYoLIsyk){OXmufjrVZC = true;}
      else if(gemYoLIsyk == QrJDjxWqxU){azPtIyZaCt = true;}
      if(mKyxFqSZfR == IOQYApyJZm){CPPoUlDkgX = true;}
      else if(IOQYApyJZm == mKyxFqSZfR){QVOOGmnHxj = true;}
      if(LgmbdnbBNF == mrOIICJRTa){aemaikTmPT = true;}
      else if(mrOIICJRTa == LgmbdnbBNF){ybAyTrhPjX = true;}
      if(UqNklBkqbp == SLuCTQqxdG){jCFRMscqHF = true;}
      if(GKGwKdrxdu == EOGNsglree){CANYbkxqWR = true;}
      if(mGiJliFhYw == kXoHanPdQl){KDCXUijMMu = true;}
      while(SLuCTQqxdG == UqNklBkqbp){fKGVVnMWoK = true;}
      while(EOGNsglree == EOGNsglree){GYeDMlCQFC = true;}
      while(kXoHanPdQl == kXoHanPdQl){JmKWdzzRaQ = true;}
      if(CpZWSxSOFj == true){CpZWSxSOFj = false;}
      if(yBeThYlAOa == true){yBeThYlAOa = false;}
      if(QQmnptVmae == true){QQmnptVmae = false;}
      if(ANgrDOniuw == true){ANgrDOniuw = false;}
      if(OXmufjrVZC == true){OXmufjrVZC = false;}
      if(CPPoUlDkgX == true){CPPoUlDkgX = false;}
      if(aemaikTmPT == true){aemaikTmPT = false;}
      if(jCFRMscqHF == true){jCFRMscqHF = false;}
      if(CANYbkxqWR == true){CANYbkxqWR = false;}
      if(KDCXUijMMu == true){KDCXUijMMu = false;}
      if(PEFGRzJxbb == true){PEFGRzJxbb = false;}
      if(IMcaUaRNyx == true){IMcaUaRNyx = false;}
      if(nbQyJgAhxd == true){nbQyJgAhxd = false;}
      if(IQeMpxtHHc == true){IQeMpxtHHc = false;}
      if(azPtIyZaCt == true){azPtIyZaCt = false;}
      if(QVOOGmnHxj == true){QVOOGmnHxj = false;}
      if(ybAyTrhPjX == true){ybAyTrhPjX = false;}
      if(fKGVVnMWoK == true){fKGVVnMWoK = false;}
      if(GYeDMlCQFC == true){GYeDMlCQFC = false;}
      if(JmKWdzzRaQ == true){JmKWdzzRaQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BLIHEPOARM
{ 
  void NoMjgVeaad()
  { 
      bool fEgRAkkHit = false;
      bool dMZLGFzusD = false;
      bool bXaZzEfyDR = false;
      bool cSgGwMNZQD = false;
      bool rqMEAJljWb = false;
      bool whJDzIdHRw = false;
      bool EmDRQKeSOs = false;
      bool rYdpLkLWYp = false;
      bool SwabVtIdHn = false;
      bool iFIUyFmtmo = false;
      bool dSUdiWETrN = false;
      bool wHhbcILbuW = false;
      bool CBLZKmQIqF = false;
      bool xQiiLAaxry = false;
      bool ooktqaWfrp = false;
      bool tLyQmcGuSw = false;
      bool FublPfXzQb = false;
      bool gNixgNPRhi = false;
      bool PjQBLlRSwh = false;
      bool sfdurtMydL = false;
      string ZEyrSzJiZC;
      string FKRrARjiiG;
      string aCBeXYDAjq;
      string pUfYpNVlYx;
      string gpwKhlXsBP;
      string cfhJJXDTTt;
      string uJyhLjerCl;
      string wyJkYjFqwl;
      string BKyUNJmWOS;
      string KBSeCXrNyx;
      string HeqPSeVwjZ;
      string RLXhrjKdUB;
      string xHdibueeiB;
      string rqrydWTiBh;
      string mploBydkmR;
      string MNsxAzAHnX;
      string AqMhhZSYDU;
      string QablNGVnhc;
      string RtrRodyuyd;
      string VLudhwdDHa;
      if(ZEyrSzJiZC == HeqPSeVwjZ){fEgRAkkHit = true;}
      else if(HeqPSeVwjZ == ZEyrSzJiZC){dSUdiWETrN = true;}
      if(FKRrARjiiG == RLXhrjKdUB){dMZLGFzusD = true;}
      else if(RLXhrjKdUB == FKRrARjiiG){wHhbcILbuW = true;}
      if(aCBeXYDAjq == xHdibueeiB){bXaZzEfyDR = true;}
      else if(xHdibueeiB == aCBeXYDAjq){CBLZKmQIqF = true;}
      if(pUfYpNVlYx == rqrydWTiBh){cSgGwMNZQD = true;}
      else if(rqrydWTiBh == pUfYpNVlYx){xQiiLAaxry = true;}
      if(gpwKhlXsBP == mploBydkmR){rqMEAJljWb = true;}
      else if(mploBydkmR == gpwKhlXsBP){ooktqaWfrp = true;}
      if(cfhJJXDTTt == MNsxAzAHnX){whJDzIdHRw = true;}
      else if(MNsxAzAHnX == cfhJJXDTTt){tLyQmcGuSw = true;}
      if(uJyhLjerCl == AqMhhZSYDU){EmDRQKeSOs = true;}
      else if(AqMhhZSYDU == uJyhLjerCl){FublPfXzQb = true;}
      if(wyJkYjFqwl == QablNGVnhc){rYdpLkLWYp = true;}
      if(BKyUNJmWOS == RtrRodyuyd){SwabVtIdHn = true;}
      if(KBSeCXrNyx == VLudhwdDHa){iFIUyFmtmo = true;}
      while(QablNGVnhc == wyJkYjFqwl){gNixgNPRhi = true;}
      while(RtrRodyuyd == RtrRodyuyd){PjQBLlRSwh = true;}
      while(VLudhwdDHa == VLudhwdDHa){sfdurtMydL = true;}
      if(fEgRAkkHit == true){fEgRAkkHit = false;}
      if(dMZLGFzusD == true){dMZLGFzusD = false;}
      if(bXaZzEfyDR == true){bXaZzEfyDR = false;}
      if(cSgGwMNZQD == true){cSgGwMNZQD = false;}
      if(rqMEAJljWb == true){rqMEAJljWb = false;}
      if(whJDzIdHRw == true){whJDzIdHRw = false;}
      if(EmDRQKeSOs == true){EmDRQKeSOs = false;}
      if(rYdpLkLWYp == true){rYdpLkLWYp = false;}
      if(SwabVtIdHn == true){SwabVtIdHn = false;}
      if(iFIUyFmtmo == true){iFIUyFmtmo = false;}
      if(dSUdiWETrN == true){dSUdiWETrN = false;}
      if(wHhbcILbuW == true){wHhbcILbuW = false;}
      if(CBLZKmQIqF == true){CBLZKmQIqF = false;}
      if(xQiiLAaxry == true){xQiiLAaxry = false;}
      if(ooktqaWfrp == true){ooktqaWfrp = false;}
      if(tLyQmcGuSw == true){tLyQmcGuSw = false;}
      if(FublPfXzQb == true){FublPfXzQb = false;}
      if(gNixgNPRhi == true){gNixgNPRhi = false;}
      if(PjQBLlRSwh == true){PjQBLlRSwh = false;}
      if(sfdurtMydL == true){sfdurtMydL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MONCXZNCYQ
{ 
  void YCBtcSuRan()
  { 
      bool ebHIPKBYFP = false;
      bool AsbXGYxxXd = false;
      bool zeUnTIeSGj = false;
      bool OyOsfQHujY = false;
      bool oRIIJXRQjF = false;
      bool yRDXGAHTnG = false;
      bool fhSVABeirp = false;
      bool RCNzohWMdw = false;
      bool qNiAkxtple = false;
      bool JmGcrHzlHH = false;
      bool riYsnwDEhY = false;
      bool dtprPSySkC = false;
      bool HnwMgdukGh = false;
      bool ijEVDHnoLo = false;
      bool toIMBOxOMZ = false;
      bool IgBFzElMMJ = false;
      bool ASyApspTnH = false;
      bool dIGwISfjKR = false;
      bool ggXfZCizVz = false;
      bool VbcBnaqHWI = false;
      string VNWPzcebgc;
      string bROgVryEch;
      string mOFIOJGBSx;
      string CHFguXuoyP;
      string zWypFuhKNL;
      string TFdCmHIOBo;
      string VdIiZULhky;
      string wJGMhPPPCS;
      string bwmGdwcDtn;
      string PgnIsUNPPk;
      string izYPPKzQTW;
      string qrLhNZqCFc;
      string qInxhOVySN;
      string CAARjbWWqT;
      string xMiWxWVFtT;
      string dLJltZKbhA;
      string oBxGUprsxk;
      string DTKkfdZQzK;
      string sPDzippNXJ;
      string RtoqewObCG;
      if(VNWPzcebgc == izYPPKzQTW){ebHIPKBYFP = true;}
      else if(izYPPKzQTW == VNWPzcebgc){riYsnwDEhY = true;}
      if(bROgVryEch == qrLhNZqCFc){AsbXGYxxXd = true;}
      else if(qrLhNZqCFc == bROgVryEch){dtprPSySkC = true;}
      if(mOFIOJGBSx == qInxhOVySN){zeUnTIeSGj = true;}
      else if(qInxhOVySN == mOFIOJGBSx){HnwMgdukGh = true;}
      if(CHFguXuoyP == CAARjbWWqT){OyOsfQHujY = true;}
      else if(CAARjbWWqT == CHFguXuoyP){ijEVDHnoLo = true;}
      if(zWypFuhKNL == xMiWxWVFtT){oRIIJXRQjF = true;}
      else if(xMiWxWVFtT == zWypFuhKNL){toIMBOxOMZ = true;}
      if(TFdCmHIOBo == dLJltZKbhA){yRDXGAHTnG = true;}
      else if(dLJltZKbhA == TFdCmHIOBo){IgBFzElMMJ = true;}
      if(VdIiZULhky == oBxGUprsxk){fhSVABeirp = true;}
      else if(oBxGUprsxk == VdIiZULhky){ASyApspTnH = true;}
      if(wJGMhPPPCS == DTKkfdZQzK){RCNzohWMdw = true;}
      if(bwmGdwcDtn == sPDzippNXJ){qNiAkxtple = true;}
      if(PgnIsUNPPk == RtoqewObCG){JmGcrHzlHH = true;}
      while(DTKkfdZQzK == wJGMhPPPCS){dIGwISfjKR = true;}
      while(sPDzippNXJ == sPDzippNXJ){ggXfZCizVz = true;}
      while(RtoqewObCG == RtoqewObCG){VbcBnaqHWI = true;}
      if(ebHIPKBYFP == true){ebHIPKBYFP = false;}
      if(AsbXGYxxXd == true){AsbXGYxxXd = false;}
      if(zeUnTIeSGj == true){zeUnTIeSGj = false;}
      if(OyOsfQHujY == true){OyOsfQHujY = false;}
      if(oRIIJXRQjF == true){oRIIJXRQjF = false;}
      if(yRDXGAHTnG == true){yRDXGAHTnG = false;}
      if(fhSVABeirp == true){fhSVABeirp = false;}
      if(RCNzohWMdw == true){RCNzohWMdw = false;}
      if(qNiAkxtple == true){qNiAkxtple = false;}
      if(JmGcrHzlHH == true){JmGcrHzlHH = false;}
      if(riYsnwDEhY == true){riYsnwDEhY = false;}
      if(dtprPSySkC == true){dtprPSySkC = false;}
      if(HnwMgdukGh == true){HnwMgdukGh = false;}
      if(ijEVDHnoLo == true){ijEVDHnoLo = false;}
      if(toIMBOxOMZ == true){toIMBOxOMZ = false;}
      if(IgBFzElMMJ == true){IgBFzElMMJ = false;}
      if(ASyApspTnH == true){ASyApspTnH = false;}
      if(dIGwISfjKR == true){dIGwISfjKR = false;}
      if(ggXfZCizVz == true){ggXfZCizVz = false;}
      if(VbcBnaqHWI == true){VbcBnaqHWI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MKVYLBYCKQ
{ 
  void VBiboEHlNB()
  { 
      bool rehEaARfuC = false;
      bool JyCljFTYDY = false;
      bool YcsfExQBWu = false;
      bool qtRcmghVus = false;
      bool CROJRsuRCw = false;
      bool XPVlcPlBAc = false;
      bool jPIALPgZzC = false;
      bool WxcJWHNiOK = false;
      bool CzyaXbYeAW = false;
      bool tgVRJlJNyC = false;
      bool LVSAYZlLOV = false;
      bool BDloajQgcj = false;
      bool qCYbHoaKzk = false;
      bool xzjMzggyBx = false;
      bool oMPdUqugqZ = false;
      bool UbkOKIwprj = false;
      bool yaLdXCSZot = false;
      bool DSfetdmtGQ = false;
      bool ttTZPVOVBp = false;
      bool kpFRzNAkGS = false;
      string ZOhFsyfFiC;
      string zDBbJODGgZ;
      string gyjmSwGsEm;
      string WHbtZngqNp;
      string ydulqtRoxb;
      string nOgpVadumw;
      string rlAufqaGCU;
      string hLsqbDCyuY;
      string eRwczHakXy;
      string KkERxLcAGz;
      string SKlbsbVoOS;
      string YeANQaoWwX;
      string QphEKxGasQ;
      string ZCruFUeUiW;
      string lkWFYejpAW;
      string VFEhicbhQw;
      string VtwysWmFIw;
      string uUnYlfScee;
      string MPaWtTxKMb;
      string rxDlBqoYLC;
      if(ZOhFsyfFiC == SKlbsbVoOS){rehEaARfuC = true;}
      else if(SKlbsbVoOS == ZOhFsyfFiC){LVSAYZlLOV = true;}
      if(zDBbJODGgZ == YeANQaoWwX){JyCljFTYDY = true;}
      else if(YeANQaoWwX == zDBbJODGgZ){BDloajQgcj = true;}
      if(gyjmSwGsEm == QphEKxGasQ){YcsfExQBWu = true;}
      else if(QphEKxGasQ == gyjmSwGsEm){qCYbHoaKzk = true;}
      if(WHbtZngqNp == ZCruFUeUiW){qtRcmghVus = true;}
      else if(ZCruFUeUiW == WHbtZngqNp){xzjMzggyBx = true;}
      if(ydulqtRoxb == lkWFYejpAW){CROJRsuRCw = true;}
      else if(lkWFYejpAW == ydulqtRoxb){oMPdUqugqZ = true;}
      if(nOgpVadumw == VFEhicbhQw){XPVlcPlBAc = true;}
      else if(VFEhicbhQw == nOgpVadumw){UbkOKIwprj = true;}
      if(rlAufqaGCU == VtwysWmFIw){jPIALPgZzC = true;}
      else if(VtwysWmFIw == rlAufqaGCU){yaLdXCSZot = true;}
      if(hLsqbDCyuY == uUnYlfScee){WxcJWHNiOK = true;}
      if(eRwczHakXy == MPaWtTxKMb){CzyaXbYeAW = true;}
      if(KkERxLcAGz == rxDlBqoYLC){tgVRJlJNyC = true;}
      while(uUnYlfScee == hLsqbDCyuY){DSfetdmtGQ = true;}
      while(MPaWtTxKMb == MPaWtTxKMb){ttTZPVOVBp = true;}
      while(rxDlBqoYLC == rxDlBqoYLC){kpFRzNAkGS = true;}
      if(rehEaARfuC == true){rehEaARfuC = false;}
      if(JyCljFTYDY == true){JyCljFTYDY = false;}
      if(YcsfExQBWu == true){YcsfExQBWu = false;}
      if(qtRcmghVus == true){qtRcmghVus = false;}
      if(CROJRsuRCw == true){CROJRsuRCw = false;}
      if(XPVlcPlBAc == true){XPVlcPlBAc = false;}
      if(jPIALPgZzC == true){jPIALPgZzC = false;}
      if(WxcJWHNiOK == true){WxcJWHNiOK = false;}
      if(CzyaXbYeAW == true){CzyaXbYeAW = false;}
      if(tgVRJlJNyC == true){tgVRJlJNyC = false;}
      if(LVSAYZlLOV == true){LVSAYZlLOV = false;}
      if(BDloajQgcj == true){BDloajQgcj = false;}
      if(qCYbHoaKzk == true){qCYbHoaKzk = false;}
      if(xzjMzggyBx == true){xzjMzggyBx = false;}
      if(oMPdUqugqZ == true){oMPdUqugqZ = false;}
      if(UbkOKIwprj == true){UbkOKIwprj = false;}
      if(yaLdXCSZot == true){yaLdXCSZot = false;}
      if(DSfetdmtGQ == true){DSfetdmtGQ = false;}
      if(ttTZPVOVBp == true){ttTZPVOVBp = false;}
      if(kpFRzNAkGS == true){kpFRzNAkGS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QMJPMNDGSL
{ 
  void gwgSktJpnI()
  { 
      bool tkwVJAwTIB = false;
      bool iqQiYjBENK = false;
      bool zADABPAgcH = false;
      bool frZerJWYxL = false;
      bool VESCnQRUPe = false;
      bool ANemzshuUs = false;
      bool APpAVqQlqO = false;
      bool NbGBouhAMj = false;
      bool yfRxHRMmfz = false;
      bool aaDELFNRfx = false;
      bool AfcARXGdyD = false;
      bool KgikuUxssD = false;
      bool ddFrnlXCoi = false;
      bool hQTPjRCQfi = false;
      bool LhnbntrSIq = false;
      bool ITXcSVZkMe = false;
      bool ADnPVtMSAd = false;
      bool RfNKquodDs = false;
      bool tFtyaNrqwN = false;
      bool qQEAiItYFt = false;
      string WIWmGHRwzH;
      string NbTadenPsX;
      string PGUiHnChGb;
      string ehJfuepPcq;
      string TjxCFqCbdt;
      string PJcxrQmmfR;
      string EioXcfRmez;
      string oXlCDeJScQ;
      string laEMLVEMnd;
      string qCjLljuYZZ;
      string YOwdFrWasM;
      string HUKPfdecMH;
      string aEzAIlnaPS;
      string jjsDqWeZHT;
      string ycTaWVrUeI;
      string FRMRzUPuVS;
      string DwLacXbGXI;
      string zEVrJxkYdl;
      string tTuGMRXaDW;
      string HiEnPBRsyz;
      if(WIWmGHRwzH == YOwdFrWasM){tkwVJAwTIB = true;}
      else if(YOwdFrWasM == WIWmGHRwzH){AfcARXGdyD = true;}
      if(NbTadenPsX == HUKPfdecMH){iqQiYjBENK = true;}
      else if(HUKPfdecMH == NbTadenPsX){KgikuUxssD = true;}
      if(PGUiHnChGb == aEzAIlnaPS){zADABPAgcH = true;}
      else if(aEzAIlnaPS == PGUiHnChGb){ddFrnlXCoi = true;}
      if(ehJfuepPcq == jjsDqWeZHT){frZerJWYxL = true;}
      else if(jjsDqWeZHT == ehJfuepPcq){hQTPjRCQfi = true;}
      if(TjxCFqCbdt == ycTaWVrUeI){VESCnQRUPe = true;}
      else if(ycTaWVrUeI == TjxCFqCbdt){LhnbntrSIq = true;}
      if(PJcxrQmmfR == FRMRzUPuVS){ANemzshuUs = true;}
      else if(FRMRzUPuVS == PJcxrQmmfR){ITXcSVZkMe = true;}
      if(EioXcfRmez == DwLacXbGXI){APpAVqQlqO = true;}
      else if(DwLacXbGXI == EioXcfRmez){ADnPVtMSAd = true;}
      if(oXlCDeJScQ == zEVrJxkYdl){NbGBouhAMj = true;}
      if(laEMLVEMnd == tTuGMRXaDW){yfRxHRMmfz = true;}
      if(qCjLljuYZZ == HiEnPBRsyz){aaDELFNRfx = true;}
      while(zEVrJxkYdl == oXlCDeJScQ){RfNKquodDs = true;}
      while(tTuGMRXaDW == tTuGMRXaDW){tFtyaNrqwN = true;}
      while(HiEnPBRsyz == HiEnPBRsyz){qQEAiItYFt = true;}
      if(tkwVJAwTIB == true){tkwVJAwTIB = false;}
      if(iqQiYjBENK == true){iqQiYjBENK = false;}
      if(zADABPAgcH == true){zADABPAgcH = false;}
      if(frZerJWYxL == true){frZerJWYxL = false;}
      if(VESCnQRUPe == true){VESCnQRUPe = false;}
      if(ANemzshuUs == true){ANemzshuUs = false;}
      if(APpAVqQlqO == true){APpAVqQlqO = false;}
      if(NbGBouhAMj == true){NbGBouhAMj = false;}
      if(yfRxHRMmfz == true){yfRxHRMmfz = false;}
      if(aaDELFNRfx == true){aaDELFNRfx = false;}
      if(AfcARXGdyD == true){AfcARXGdyD = false;}
      if(KgikuUxssD == true){KgikuUxssD = false;}
      if(ddFrnlXCoi == true){ddFrnlXCoi = false;}
      if(hQTPjRCQfi == true){hQTPjRCQfi = false;}
      if(LhnbntrSIq == true){LhnbntrSIq = false;}
      if(ITXcSVZkMe == true){ITXcSVZkMe = false;}
      if(ADnPVtMSAd == true){ADnPVtMSAd = false;}
      if(RfNKquodDs == true){RfNKquodDs = false;}
      if(tFtyaNrqwN == true){tFtyaNrqwN = false;}
      if(qQEAiItYFt == true){qQEAiItYFt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WFVMIGJIYA
{ 
  void ezuqRnltPI()
  { 
      bool lBVXWgKYbj = false;
      bool feSdwxSEjI = false;
      bool ImmMFGGalo = false;
      bool YdziKtFgQd = false;
      bool FdVIbJMFqZ = false;
      bool ZXcKxzNJRP = false;
      bool ajlmKBeiSC = false;
      bool qlnFCeQejw = false;
      bool sAiLPBBokK = false;
      bool fwOADVqhyZ = false;
      bool dclnhniWIS = false;
      bool iiYVVaBaWJ = false;
      bool ApyIWtWmCf = false;
      bool mifKSQOtcb = false;
      bool RdgSbwXsdc = false;
      bool TQLnYnecRn = false;
      bool QuUbezCNDF = false;
      bool LGxtqWIegZ = false;
      bool VcJZMWWrle = false;
      bool kkcoKWJFmb = false;
      string VHReyJoAbx;
      string zSDuOQFzlg;
      string gDtUXVgkAj;
      string iWakddqxbJ;
      string aUeZiRaefw;
      string xUPkcSNxHb;
      string bEzrObqSQk;
      string YHXcFMXTkG;
      string uBEElOGoIL;
      string QtpzhWVmKG;
      string ZIOuWpwmfP;
      string tsLAgZzuFA;
      string UBKFTeQXui;
      string qjIeflmJgw;
      string RTJrQWioSI;
      string WZhKkXxIar;
      string YYqwYKjgTt;
      string loOJhBrSox;
      string uaFmLQCxsH;
      string neinWsbNSF;
      if(VHReyJoAbx == ZIOuWpwmfP){lBVXWgKYbj = true;}
      else if(ZIOuWpwmfP == VHReyJoAbx){dclnhniWIS = true;}
      if(zSDuOQFzlg == tsLAgZzuFA){feSdwxSEjI = true;}
      else if(tsLAgZzuFA == zSDuOQFzlg){iiYVVaBaWJ = true;}
      if(gDtUXVgkAj == UBKFTeQXui){ImmMFGGalo = true;}
      else if(UBKFTeQXui == gDtUXVgkAj){ApyIWtWmCf = true;}
      if(iWakddqxbJ == qjIeflmJgw){YdziKtFgQd = true;}
      else if(qjIeflmJgw == iWakddqxbJ){mifKSQOtcb = true;}
      if(aUeZiRaefw == RTJrQWioSI){FdVIbJMFqZ = true;}
      else if(RTJrQWioSI == aUeZiRaefw){RdgSbwXsdc = true;}
      if(xUPkcSNxHb == WZhKkXxIar){ZXcKxzNJRP = true;}
      else if(WZhKkXxIar == xUPkcSNxHb){TQLnYnecRn = true;}
      if(bEzrObqSQk == YYqwYKjgTt){ajlmKBeiSC = true;}
      else if(YYqwYKjgTt == bEzrObqSQk){QuUbezCNDF = true;}
      if(YHXcFMXTkG == loOJhBrSox){qlnFCeQejw = true;}
      if(uBEElOGoIL == uaFmLQCxsH){sAiLPBBokK = true;}
      if(QtpzhWVmKG == neinWsbNSF){fwOADVqhyZ = true;}
      while(loOJhBrSox == YHXcFMXTkG){LGxtqWIegZ = true;}
      while(uaFmLQCxsH == uaFmLQCxsH){VcJZMWWrle = true;}
      while(neinWsbNSF == neinWsbNSF){kkcoKWJFmb = true;}
      if(lBVXWgKYbj == true){lBVXWgKYbj = false;}
      if(feSdwxSEjI == true){feSdwxSEjI = false;}
      if(ImmMFGGalo == true){ImmMFGGalo = false;}
      if(YdziKtFgQd == true){YdziKtFgQd = false;}
      if(FdVIbJMFqZ == true){FdVIbJMFqZ = false;}
      if(ZXcKxzNJRP == true){ZXcKxzNJRP = false;}
      if(ajlmKBeiSC == true){ajlmKBeiSC = false;}
      if(qlnFCeQejw == true){qlnFCeQejw = false;}
      if(sAiLPBBokK == true){sAiLPBBokK = false;}
      if(fwOADVqhyZ == true){fwOADVqhyZ = false;}
      if(dclnhniWIS == true){dclnhniWIS = false;}
      if(iiYVVaBaWJ == true){iiYVVaBaWJ = false;}
      if(ApyIWtWmCf == true){ApyIWtWmCf = false;}
      if(mifKSQOtcb == true){mifKSQOtcb = false;}
      if(RdgSbwXsdc == true){RdgSbwXsdc = false;}
      if(TQLnYnecRn == true){TQLnYnecRn = false;}
      if(QuUbezCNDF == true){QuUbezCNDF = false;}
      if(LGxtqWIegZ == true){LGxtqWIegZ = false;}
      if(VcJZMWWrle == true){VcJZMWWrle = false;}
      if(kkcoKWJFmb == true){kkcoKWJFmb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJPWQFHUZU
{ 
  void nLsIjcDJhO()
  { 
      bool qUCnkdkAbN = false;
      bool tJtCrMJhGi = false;
      bool WLComYUKOc = false;
      bool SQQWWuaido = false;
      bool kTCbEPkeGf = false;
      bool gnlXfeRMAM = false;
      bool JakytcrXex = false;
      bool lZDQyDIakX = false;
      bool moEhweerpq = false;
      bool dNhRfJhEhb = false;
      bool WNzItGjUZc = false;
      bool WqbbYTWDCO = false;
      bool xAhnTXrlko = false;
      bool VErJBZouno = false;
      bool tJSNUllFrL = false;
      bool mdCSdVfLoV = false;
      bool OxijGRySZz = false;
      bool ebOMTngTSg = false;
      bool lltZCqCZef = false;
      bool scFRZwZhGC = false;
      string FtuJSNOcpu;
      string INEpMYGMsQ;
      string BLSCiUQHPE;
      string bathHWsGSr;
      string lZjFuArYAS;
      string KzDCysbsZx;
      string xHNkThTWip;
      string eAtAdbaMGi;
      string cqHwtbXqjN;
      string uAgVueLzlN;
      string gVpKnKFDYV;
      string SOlpUFzRqq;
      string JbmUteTYFz;
      string QbZsCHBxIi;
      string WTSNtfNpBp;
      string ftHuDEiUPJ;
      string pfxZFqosnM;
      string EBIHTpJYZN;
      string QcWPSVTdpy;
      string YfgyspWrHD;
      if(FtuJSNOcpu == gVpKnKFDYV){qUCnkdkAbN = true;}
      else if(gVpKnKFDYV == FtuJSNOcpu){WNzItGjUZc = true;}
      if(INEpMYGMsQ == SOlpUFzRqq){tJtCrMJhGi = true;}
      else if(SOlpUFzRqq == INEpMYGMsQ){WqbbYTWDCO = true;}
      if(BLSCiUQHPE == JbmUteTYFz){WLComYUKOc = true;}
      else if(JbmUteTYFz == BLSCiUQHPE){xAhnTXrlko = true;}
      if(bathHWsGSr == QbZsCHBxIi){SQQWWuaido = true;}
      else if(QbZsCHBxIi == bathHWsGSr){VErJBZouno = true;}
      if(lZjFuArYAS == WTSNtfNpBp){kTCbEPkeGf = true;}
      else if(WTSNtfNpBp == lZjFuArYAS){tJSNUllFrL = true;}
      if(KzDCysbsZx == ftHuDEiUPJ){gnlXfeRMAM = true;}
      else if(ftHuDEiUPJ == KzDCysbsZx){mdCSdVfLoV = true;}
      if(xHNkThTWip == pfxZFqosnM){JakytcrXex = true;}
      else if(pfxZFqosnM == xHNkThTWip){OxijGRySZz = true;}
      if(eAtAdbaMGi == EBIHTpJYZN){lZDQyDIakX = true;}
      if(cqHwtbXqjN == QcWPSVTdpy){moEhweerpq = true;}
      if(uAgVueLzlN == YfgyspWrHD){dNhRfJhEhb = true;}
      while(EBIHTpJYZN == eAtAdbaMGi){ebOMTngTSg = true;}
      while(QcWPSVTdpy == QcWPSVTdpy){lltZCqCZef = true;}
      while(YfgyspWrHD == YfgyspWrHD){scFRZwZhGC = true;}
      if(qUCnkdkAbN == true){qUCnkdkAbN = false;}
      if(tJtCrMJhGi == true){tJtCrMJhGi = false;}
      if(WLComYUKOc == true){WLComYUKOc = false;}
      if(SQQWWuaido == true){SQQWWuaido = false;}
      if(kTCbEPkeGf == true){kTCbEPkeGf = false;}
      if(gnlXfeRMAM == true){gnlXfeRMAM = false;}
      if(JakytcrXex == true){JakytcrXex = false;}
      if(lZDQyDIakX == true){lZDQyDIakX = false;}
      if(moEhweerpq == true){moEhweerpq = false;}
      if(dNhRfJhEhb == true){dNhRfJhEhb = false;}
      if(WNzItGjUZc == true){WNzItGjUZc = false;}
      if(WqbbYTWDCO == true){WqbbYTWDCO = false;}
      if(xAhnTXrlko == true){xAhnTXrlko = false;}
      if(VErJBZouno == true){VErJBZouno = false;}
      if(tJSNUllFrL == true){tJSNUllFrL = false;}
      if(mdCSdVfLoV == true){mdCSdVfLoV = false;}
      if(OxijGRySZz == true){OxijGRySZz = false;}
      if(ebOMTngTSg == true){ebOMTngTSg = false;}
      if(lltZCqCZef == true){lltZCqCZef = false;}
      if(scFRZwZhGC == true){scFRZwZhGC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RMIUVYVRZR
{ 
  void OYgXfPoTTj()
  { 
      bool tAaXBsFfMW = false;
      bool DiiSHXJqGn = false;
      bool nICnoDgXQG = false;
      bool wikHsKWhGS = false;
      bool bKIQfICQlG = false;
      bool ARGRlkyliy = false;
      bool LhOGZUxbYw = false;
      bool AbjmMczkHg = false;
      bool AQkKFebSUI = false;
      bool MjyIHtuCpL = false;
      bool KZqpFYgTFI = false;
      bool lMdCxuwEAu = false;
      bool rdGQiPcbfR = false;
      bool hwuwVaYuEg = false;
      bool xINMWAGwLM = false;
      bool yqCuSfTaGp = false;
      bool wFmmaoRgfW = false;
      bool VAATxiQtth = false;
      bool JfPTTptzdp = false;
      bool HynNkrVZkg = false;
      string BSextrEMwY;
      string IhHWLIadKM;
      string PTXSehwpCk;
      string kloiixJXQd;
      string cLgGMTTphU;
      string TmeWfhuMRM;
      string wNKLmVsXmO;
      string zCNfjElRGK;
      string NFIgQyHRDA;
      string CwGDgOAUSp;
      string auDSURYyma;
      string ucFHzqFcto;
      string NaUlMCwJyU;
      string EQzPiSCoMz;
      string YIecEYpyEp;
      string IWacbzaQGS;
      string UOzRVddpXf;
      string oPQuQFwrgn;
      string LxFILhpVmj;
      string qkisdJIMGZ;
      if(BSextrEMwY == auDSURYyma){tAaXBsFfMW = true;}
      else if(auDSURYyma == BSextrEMwY){KZqpFYgTFI = true;}
      if(IhHWLIadKM == ucFHzqFcto){DiiSHXJqGn = true;}
      else if(ucFHzqFcto == IhHWLIadKM){lMdCxuwEAu = true;}
      if(PTXSehwpCk == NaUlMCwJyU){nICnoDgXQG = true;}
      else if(NaUlMCwJyU == PTXSehwpCk){rdGQiPcbfR = true;}
      if(kloiixJXQd == EQzPiSCoMz){wikHsKWhGS = true;}
      else if(EQzPiSCoMz == kloiixJXQd){hwuwVaYuEg = true;}
      if(cLgGMTTphU == YIecEYpyEp){bKIQfICQlG = true;}
      else if(YIecEYpyEp == cLgGMTTphU){xINMWAGwLM = true;}
      if(TmeWfhuMRM == IWacbzaQGS){ARGRlkyliy = true;}
      else if(IWacbzaQGS == TmeWfhuMRM){yqCuSfTaGp = true;}
      if(wNKLmVsXmO == UOzRVddpXf){LhOGZUxbYw = true;}
      else if(UOzRVddpXf == wNKLmVsXmO){wFmmaoRgfW = true;}
      if(zCNfjElRGK == oPQuQFwrgn){AbjmMczkHg = true;}
      if(NFIgQyHRDA == LxFILhpVmj){AQkKFebSUI = true;}
      if(CwGDgOAUSp == qkisdJIMGZ){MjyIHtuCpL = true;}
      while(oPQuQFwrgn == zCNfjElRGK){VAATxiQtth = true;}
      while(LxFILhpVmj == LxFILhpVmj){JfPTTptzdp = true;}
      while(qkisdJIMGZ == qkisdJIMGZ){HynNkrVZkg = true;}
      if(tAaXBsFfMW == true){tAaXBsFfMW = false;}
      if(DiiSHXJqGn == true){DiiSHXJqGn = false;}
      if(nICnoDgXQG == true){nICnoDgXQG = false;}
      if(wikHsKWhGS == true){wikHsKWhGS = false;}
      if(bKIQfICQlG == true){bKIQfICQlG = false;}
      if(ARGRlkyliy == true){ARGRlkyliy = false;}
      if(LhOGZUxbYw == true){LhOGZUxbYw = false;}
      if(AbjmMczkHg == true){AbjmMczkHg = false;}
      if(AQkKFebSUI == true){AQkKFebSUI = false;}
      if(MjyIHtuCpL == true){MjyIHtuCpL = false;}
      if(KZqpFYgTFI == true){KZqpFYgTFI = false;}
      if(lMdCxuwEAu == true){lMdCxuwEAu = false;}
      if(rdGQiPcbfR == true){rdGQiPcbfR = false;}
      if(hwuwVaYuEg == true){hwuwVaYuEg = false;}
      if(xINMWAGwLM == true){xINMWAGwLM = false;}
      if(yqCuSfTaGp == true){yqCuSfTaGp = false;}
      if(wFmmaoRgfW == true){wFmmaoRgfW = false;}
      if(VAATxiQtth == true){VAATxiQtth = false;}
      if(JfPTTptzdp == true){JfPTTptzdp = false;}
      if(HynNkrVZkg == true){HynNkrVZkg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QNCNYWVIDA
{ 
  void TjFZgJsnKW()
  { 
      bool KbHwRcHcqf = false;
      bool CRBPegEEFO = false;
      bool CzhiUPkdJN = false;
      bool FORobcXSKb = false;
      bool tSnJElWZBC = false;
      bool dICXnLtXaC = false;
      bool rcScamzMnB = false;
      bool JksdUjKXei = false;
      bool sLcHjwLtBQ = false;
      bool hArIjQzLhQ = false;
      bool lJkzrsOYCE = false;
      bool AVsqIgALse = false;
      bool bFLXSIrksE = false;
      bool jyoNwiZcOq = false;
      bool gmqxPMHBzD = false;
      bool QmSDogyNfi = false;
      bool AdeyTCfeuY = false;
      bool GWwBxoNOIG = false;
      bool BqkpmwflXO = false;
      bool kLwepCHscN = false;
      string RsLEjkOAGR;
      string sNcXHDkdoy;
      string jWqslfhVTb;
      string OQlgzphmYE;
      string QYqnppaZwM;
      string oIDAtuCRRE;
      string CrgdDbbuYQ;
      string VyEkgKeDDu;
      string FHYGmFNlmE;
      string nPUTBXrMjN;
      string OeBfppERSi;
      string PyOWztTZpx;
      string OoITcGcjjI;
      string SRSpfZGsPx;
      string BuSDnpBxUG;
      string ERWmzYWhCj;
      string MThKQxeYpY;
      string naKswSWEfm;
      string FePcEBufpG;
      string DYpfjhNImp;
      if(RsLEjkOAGR == OeBfppERSi){KbHwRcHcqf = true;}
      else if(OeBfppERSi == RsLEjkOAGR){lJkzrsOYCE = true;}
      if(sNcXHDkdoy == PyOWztTZpx){CRBPegEEFO = true;}
      else if(PyOWztTZpx == sNcXHDkdoy){AVsqIgALse = true;}
      if(jWqslfhVTb == OoITcGcjjI){CzhiUPkdJN = true;}
      else if(OoITcGcjjI == jWqslfhVTb){bFLXSIrksE = true;}
      if(OQlgzphmYE == SRSpfZGsPx){FORobcXSKb = true;}
      else if(SRSpfZGsPx == OQlgzphmYE){jyoNwiZcOq = true;}
      if(QYqnppaZwM == BuSDnpBxUG){tSnJElWZBC = true;}
      else if(BuSDnpBxUG == QYqnppaZwM){gmqxPMHBzD = true;}
      if(oIDAtuCRRE == ERWmzYWhCj){dICXnLtXaC = true;}
      else if(ERWmzYWhCj == oIDAtuCRRE){QmSDogyNfi = true;}
      if(CrgdDbbuYQ == MThKQxeYpY){rcScamzMnB = true;}
      else if(MThKQxeYpY == CrgdDbbuYQ){AdeyTCfeuY = true;}
      if(VyEkgKeDDu == naKswSWEfm){JksdUjKXei = true;}
      if(FHYGmFNlmE == FePcEBufpG){sLcHjwLtBQ = true;}
      if(nPUTBXrMjN == DYpfjhNImp){hArIjQzLhQ = true;}
      while(naKswSWEfm == VyEkgKeDDu){GWwBxoNOIG = true;}
      while(FePcEBufpG == FePcEBufpG){BqkpmwflXO = true;}
      while(DYpfjhNImp == DYpfjhNImp){kLwepCHscN = true;}
      if(KbHwRcHcqf == true){KbHwRcHcqf = false;}
      if(CRBPegEEFO == true){CRBPegEEFO = false;}
      if(CzhiUPkdJN == true){CzhiUPkdJN = false;}
      if(FORobcXSKb == true){FORobcXSKb = false;}
      if(tSnJElWZBC == true){tSnJElWZBC = false;}
      if(dICXnLtXaC == true){dICXnLtXaC = false;}
      if(rcScamzMnB == true){rcScamzMnB = false;}
      if(JksdUjKXei == true){JksdUjKXei = false;}
      if(sLcHjwLtBQ == true){sLcHjwLtBQ = false;}
      if(hArIjQzLhQ == true){hArIjQzLhQ = false;}
      if(lJkzrsOYCE == true){lJkzrsOYCE = false;}
      if(AVsqIgALse == true){AVsqIgALse = false;}
      if(bFLXSIrksE == true){bFLXSIrksE = false;}
      if(jyoNwiZcOq == true){jyoNwiZcOq = false;}
      if(gmqxPMHBzD == true){gmqxPMHBzD = false;}
      if(QmSDogyNfi == true){QmSDogyNfi = false;}
      if(AdeyTCfeuY == true){AdeyTCfeuY = false;}
      if(GWwBxoNOIG == true){GWwBxoNOIG = false;}
      if(BqkpmwflXO == true){BqkpmwflXO = false;}
      if(kLwepCHscN == true){kLwepCHscN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXSKPEWKIK
{ 
  void sBVTiNeJwN()
  { 
      bool nyeKsRyNVO = false;
      bool bpAnWPHbFP = false;
      bool kHzUASmLaD = false;
      bool EmuNipnWtC = false;
      bool lOTrqmJZhC = false;
      bool jlStOgzJKa = false;
      bool emmSJntmFg = false;
      bool akhDdWmGdM = false;
      bool IMdXSSUByB = false;
      bool qeLTXyaBiD = false;
      bool sWUBbyEPQr = false;
      bool srfxRSJOzp = false;
      bool TrnDowZNfe = false;
      bool ulXaTkqbwT = false;
      bool OEkGHyzNBE = false;
      bool oMBriAhRLe = false;
      bool YpjkwHUEdf = false;
      bool agSebOHguq = false;
      bool wLLaoikeqS = false;
      bool CZQQuXUzKA = false;
      string xfVwRutdWt;
      string TuseFHczRH;
      string HMVFobhUWB;
      string WPRPtCOYij;
      string VGYSkeoWYy;
      string bcIBDkJPHp;
      string MYGVWEccjC;
      string sEPhlBmDUK;
      string lLwXZtGPMJ;
      string rzQsXwzDuf;
      string BMmVFWMaPC;
      string xGtxDBciwc;
      string yMQZJsmWKo;
      string BjInIZXaRC;
      string heAKMlEToV;
      string TQHRhouNLM;
      string ioQaANxFod;
      string cBRsuTMFMX;
      string oTgnUkbpGT;
      string dKOFSrOYJz;
      if(xfVwRutdWt == BMmVFWMaPC){nyeKsRyNVO = true;}
      else if(BMmVFWMaPC == xfVwRutdWt){sWUBbyEPQr = true;}
      if(TuseFHczRH == xGtxDBciwc){bpAnWPHbFP = true;}
      else if(xGtxDBciwc == TuseFHczRH){srfxRSJOzp = true;}
      if(HMVFobhUWB == yMQZJsmWKo){kHzUASmLaD = true;}
      else if(yMQZJsmWKo == HMVFobhUWB){TrnDowZNfe = true;}
      if(WPRPtCOYij == BjInIZXaRC){EmuNipnWtC = true;}
      else if(BjInIZXaRC == WPRPtCOYij){ulXaTkqbwT = true;}
      if(VGYSkeoWYy == heAKMlEToV){lOTrqmJZhC = true;}
      else if(heAKMlEToV == VGYSkeoWYy){OEkGHyzNBE = true;}
      if(bcIBDkJPHp == TQHRhouNLM){jlStOgzJKa = true;}
      else if(TQHRhouNLM == bcIBDkJPHp){oMBriAhRLe = true;}
      if(MYGVWEccjC == ioQaANxFod){emmSJntmFg = true;}
      else if(ioQaANxFod == MYGVWEccjC){YpjkwHUEdf = true;}
      if(sEPhlBmDUK == cBRsuTMFMX){akhDdWmGdM = true;}
      if(lLwXZtGPMJ == oTgnUkbpGT){IMdXSSUByB = true;}
      if(rzQsXwzDuf == dKOFSrOYJz){qeLTXyaBiD = true;}
      while(cBRsuTMFMX == sEPhlBmDUK){agSebOHguq = true;}
      while(oTgnUkbpGT == oTgnUkbpGT){wLLaoikeqS = true;}
      while(dKOFSrOYJz == dKOFSrOYJz){CZQQuXUzKA = true;}
      if(nyeKsRyNVO == true){nyeKsRyNVO = false;}
      if(bpAnWPHbFP == true){bpAnWPHbFP = false;}
      if(kHzUASmLaD == true){kHzUASmLaD = false;}
      if(EmuNipnWtC == true){EmuNipnWtC = false;}
      if(lOTrqmJZhC == true){lOTrqmJZhC = false;}
      if(jlStOgzJKa == true){jlStOgzJKa = false;}
      if(emmSJntmFg == true){emmSJntmFg = false;}
      if(akhDdWmGdM == true){akhDdWmGdM = false;}
      if(IMdXSSUByB == true){IMdXSSUByB = false;}
      if(qeLTXyaBiD == true){qeLTXyaBiD = false;}
      if(sWUBbyEPQr == true){sWUBbyEPQr = false;}
      if(srfxRSJOzp == true){srfxRSJOzp = false;}
      if(TrnDowZNfe == true){TrnDowZNfe = false;}
      if(ulXaTkqbwT == true){ulXaTkqbwT = false;}
      if(OEkGHyzNBE == true){OEkGHyzNBE = false;}
      if(oMBriAhRLe == true){oMBriAhRLe = false;}
      if(YpjkwHUEdf == true){YpjkwHUEdf = false;}
      if(agSebOHguq == true){agSebOHguq = false;}
      if(wLLaoikeqS == true){wLLaoikeqS = false;}
      if(CZQQuXUzKA == true){CZQQuXUzKA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NNBDSLRVQX
{ 
  void CMdmPdPqqN()
  { 
      bool Nsdlgdcwap = false;
      bool TTLeiZIYju = false;
      bool luiAdJBzxB = false;
      bool hMCwXnxShR = false;
      bool OWwxXzMCNp = false;
      bool tiDWcSKdHX = false;
      bool cdyYHHQOGu = false;
      bool bppRgOykbe = false;
      bool wzlHHzJfTF = false;
      bool cTLKokXXpQ = false;
      bool hxuSOErkoN = false;
      bool TYBcadqqRH = false;
      bool xkuBRIdfcw = false;
      bool qZuKxzDTsC = false;
      bool HYpFkERhiL = false;
      bool sgGhTwBtAF = false;
      bool ZMIsWscqfb = false;
      bool ZWxOAYtoPN = false;
      bool pwwQCJTNqA = false;
      bool xJSmctPwiq = false;
      string OehkrTubym;
      string GmyoBlQmxK;
      string SLBFaSniry;
      string wFGOFghmMY;
      string GRqsSWxmCR;
      string dcptFDdbJY;
      string eMjApAgiiU;
      string DcaXDAUHlD;
      string UAfaTTOLJC;
      string CGdmsshqDS;
      string pNEhNBCSqE;
      string hWpGEdgIfW;
      string lUZfRxzndJ;
      string RcETNHwxMR;
      string RwUFTfPWiO;
      string MZKffUnXQQ;
      string BNngmESWsx;
      string hiwNFpAULk;
      string gbEPwrSXmr;
      string SYgwQDHmRO;
      if(OehkrTubym == pNEhNBCSqE){Nsdlgdcwap = true;}
      else if(pNEhNBCSqE == OehkrTubym){hxuSOErkoN = true;}
      if(GmyoBlQmxK == hWpGEdgIfW){TTLeiZIYju = true;}
      else if(hWpGEdgIfW == GmyoBlQmxK){TYBcadqqRH = true;}
      if(SLBFaSniry == lUZfRxzndJ){luiAdJBzxB = true;}
      else if(lUZfRxzndJ == SLBFaSniry){xkuBRIdfcw = true;}
      if(wFGOFghmMY == RcETNHwxMR){hMCwXnxShR = true;}
      else if(RcETNHwxMR == wFGOFghmMY){qZuKxzDTsC = true;}
      if(GRqsSWxmCR == RwUFTfPWiO){OWwxXzMCNp = true;}
      else if(RwUFTfPWiO == GRqsSWxmCR){HYpFkERhiL = true;}
      if(dcptFDdbJY == MZKffUnXQQ){tiDWcSKdHX = true;}
      else if(MZKffUnXQQ == dcptFDdbJY){sgGhTwBtAF = true;}
      if(eMjApAgiiU == BNngmESWsx){cdyYHHQOGu = true;}
      else if(BNngmESWsx == eMjApAgiiU){ZMIsWscqfb = true;}
      if(DcaXDAUHlD == hiwNFpAULk){bppRgOykbe = true;}
      if(UAfaTTOLJC == gbEPwrSXmr){wzlHHzJfTF = true;}
      if(CGdmsshqDS == SYgwQDHmRO){cTLKokXXpQ = true;}
      while(hiwNFpAULk == DcaXDAUHlD){ZWxOAYtoPN = true;}
      while(gbEPwrSXmr == gbEPwrSXmr){pwwQCJTNqA = true;}
      while(SYgwQDHmRO == SYgwQDHmRO){xJSmctPwiq = true;}
      if(Nsdlgdcwap == true){Nsdlgdcwap = false;}
      if(TTLeiZIYju == true){TTLeiZIYju = false;}
      if(luiAdJBzxB == true){luiAdJBzxB = false;}
      if(hMCwXnxShR == true){hMCwXnxShR = false;}
      if(OWwxXzMCNp == true){OWwxXzMCNp = false;}
      if(tiDWcSKdHX == true){tiDWcSKdHX = false;}
      if(cdyYHHQOGu == true){cdyYHHQOGu = false;}
      if(bppRgOykbe == true){bppRgOykbe = false;}
      if(wzlHHzJfTF == true){wzlHHzJfTF = false;}
      if(cTLKokXXpQ == true){cTLKokXXpQ = false;}
      if(hxuSOErkoN == true){hxuSOErkoN = false;}
      if(TYBcadqqRH == true){TYBcadqqRH = false;}
      if(xkuBRIdfcw == true){xkuBRIdfcw = false;}
      if(qZuKxzDTsC == true){qZuKxzDTsC = false;}
      if(HYpFkERhiL == true){HYpFkERhiL = false;}
      if(sgGhTwBtAF == true){sgGhTwBtAF = false;}
      if(ZMIsWscqfb == true){ZMIsWscqfb = false;}
      if(ZWxOAYtoPN == true){ZWxOAYtoPN = false;}
      if(pwwQCJTNqA == true){pwwQCJTNqA = false;}
      if(xJSmctPwiq == true){xJSmctPwiq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AGKYBNRFJL
{ 
  void GWukTfnWTC()
  { 
      bool SJWxFVYtQS = false;
      bool LcLcXaxWDt = false;
      bool GsLshhVxcI = false;
      bool LkGKRWuDoD = false;
      bool BumdaCTSkS = false;
      bool fmJkIZydPW = false;
      bool zaRIHZWBLB = false;
      bool esgAsLFgRf = false;
      bool NCMJcXbVBr = false;
      bool XRnSDacdWA = false;
      bool eRHimlGJrx = false;
      bool TQLjIxOHej = false;
      bool yBzScNFNwR = false;
      bool haKQAwtdVp = false;
      bool QRdEYHGDJG = false;
      bool MUzlCdSoGZ = false;
      bool grMZOrFtjM = false;
      bool CjlnTfWutV = false;
      bool GBEpFMbXOV = false;
      bool cFXwJXEDof = false;
      string MPgydSPUdd;
      string BddzStFJVB;
      string rZmOXUDLiP;
      string dwFMBxgFcL;
      string VkpPpZVSkR;
      string NroWimbSaI;
      string OElNzEYRyV;
      string NzgKfGjXXy;
      string zkaRClHhdN;
      string UNeTwRzcPl;
      string BDUPDOKeqb;
      string DEucJddTKM;
      string xpnjBzUMNN;
      string GHHlxuPKNn;
      string abqBKPSCKS;
      string nfRCnKPkOE;
      string syRcVwxIeN;
      string NSGWkVzlYk;
      string fSBuZaoExl;
      string fewItcKNfO;
      if(MPgydSPUdd == BDUPDOKeqb){SJWxFVYtQS = true;}
      else if(BDUPDOKeqb == MPgydSPUdd){eRHimlGJrx = true;}
      if(BddzStFJVB == DEucJddTKM){LcLcXaxWDt = true;}
      else if(DEucJddTKM == BddzStFJVB){TQLjIxOHej = true;}
      if(rZmOXUDLiP == xpnjBzUMNN){GsLshhVxcI = true;}
      else if(xpnjBzUMNN == rZmOXUDLiP){yBzScNFNwR = true;}
      if(dwFMBxgFcL == GHHlxuPKNn){LkGKRWuDoD = true;}
      else if(GHHlxuPKNn == dwFMBxgFcL){haKQAwtdVp = true;}
      if(VkpPpZVSkR == abqBKPSCKS){BumdaCTSkS = true;}
      else if(abqBKPSCKS == VkpPpZVSkR){QRdEYHGDJG = true;}
      if(NroWimbSaI == nfRCnKPkOE){fmJkIZydPW = true;}
      else if(nfRCnKPkOE == NroWimbSaI){MUzlCdSoGZ = true;}
      if(OElNzEYRyV == syRcVwxIeN){zaRIHZWBLB = true;}
      else if(syRcVwxIeN == OElNzEYRyV){grMZOrFtjM = true;}
      if(NzgKfGjXXy == NSGWkVzlYk){esgAsLFgRf = true;}
      if(zkaRClHhdN == fSBuZaoExl){NCMJcXbVBr = true;}
      if(UNeTwRzcPl == fewItcKNfO){XRnSDacdWA = true;}
      while(NSGWkVzlYk == NzgKfGjXXy){CjlnTfWutV = true;}
      while(fSBuZaoExl == fSBuZaoExl){GBEpFMbXOV = true;}
      while(fewItcKNfO == fewItcKNfO){cFXwJXEDof = true;}
      if(SJWxFVYtQS == true){SJWxFVYtQS = false;}
      if(LcLcXaxWDt == true){LcLcXaxWDt = false;}
      if(GsLshhVxcI == true){GsLshhVxcI = false;}
      if(LkGKRWuDoD == true){LkGKRWuDoD = false;}
      if(BumdaCTSkS == true){BumdaCTSkS = false;}
      if(fmJkIZydPW == true){fmJkIZydPW = false;}
      if(zaRIHZWBLB == true){zaRIHZWBLB = false;}
      if(esgAsLFgRf == true){esgAsLFgRf = false;}
      if(NCMJcXbVBr == true){NCMJcXbVBr = false;}
      if(XRnSDacdWA == true){XRnSDacdWA = false;}
      if(eRHimlGJrx == true){eRHimlGJrx = false;}
      if(TQLjIxOHej == true){TQLjIxOHej = false;}
      if(yBzScNFNwR == true){yBzScNFNwR = false;}
      if(haKQAwtdVp == true){haKQAwtdVp = false;}
      if(QRdEYHGDJG == true){QRdEYHGDJG = false;}
      if(MUzlCdSoGZ == true){MUzlCdSoGZ = false;}
      if(grMZOrFtjM == true){grMZOrFtjM = false;}
      if(CjlnTfWutV == true){CjlnTfWutV = false;}
      if(GBEpFMbXOV == true){GBEpFMbXOV = false;}
      if(cFXwJXEDof == true){cFXwJXEDof = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SFTYYGBEST
{ 
  void xtmDeyGHYq()
  { 
      bool EdkCwMMVfB = false;
      bool wjlaKnhWlB = false;
      bool nreAtVpLkb = false;
      bool zKYYJFTzUL = false;
      bool EKweKVfJth = false;
      bool KJEplLyjHZ = false;
      bool WBkEBlKNQF = false;
      bool UiBZxduApY = false;
      bool pgRDQoFilx = false;
      bool HiquoDZrcY = false;
      bool KSroNaIesH = false;
      bool PxtijpigmL = false;
      bool fbaTxkrGkt = false;
      bool ECXQNWobpo = false;
      bool gapdhJnHKy = false;
      bool TrFQriqYqb = false;
      bool iCszDMZcVM = false;
      bool BGpxeElwkm = false;
      bool wjulZLxGXd = false;
      bool fQkOGegpaU = false;
      string ZaBzqRmGbb;
      string jSbpRQeAgg;
      string VjuigFpnXA;
      string MardRFeZqD;
      string ieZQpaZFnF;
      string uuRTFpeRSk;
      string byiaPIayXM;
      string lEIcxqJesF;
      string fkASFQJXXb;
      string ZNGGakuzAg;
      string AagbSpmoWO;
      string fAXNEqyQVz;
      string zCZumYyCBL;
      string uKeMFFDYzO;
      string cTBJwZosBj;
      string mddBgxAknt;
      string rjnKSVVLIz;
      string nZQHVfBQzN;
      string iEBQYRgcfH;
      string FRjFVsfpqa;
      if(ZaBzqRmGbb == AagbSpmoWO){EdkCwMMVfB = true;}
      else if(AagbSpmoWO == ZaBzqRmGbb){KSroNaIesH = true;}
      if(jSbpRQeAgg == fAXNEqyQVz){wjlaKnhWlB = true;}
      else if(fAXNEqyQVz == jSbpRQeAgg){PxtijpigmL = true;}
      if(VjuigFpnXA == zCZumYyCBL){nreAtVpLkb = true;}
      else if(zCZumYyCBL == VjuigFpnXA){fbaTxkrGkt = true;}
      if(MardRFeZqD == uKeMFFDYzO){zKYYJFTzUL = true;}
      else if(uKeMFFDYzO == MardRFeZqD){ECXQNWobpo = true;}
      if(ieZQpaZFnF == cTBJwZosBj){EKweKVfJth = true;}
      else if(cTBJwZosBj == ieZQpaZFnF){gapdhJnHKy = true;}
      if(uuRTFpeRSk == mddBgxAknt){KJEplLyjHZ = true;}
      else if(mddBgxAknt == uuRTFpeRSk){TrFQriqYqb = true;}
      if(byiaPIayXM == rjnKSVVLIz){WBkEBlKNQF = true;}
      else if(rjnKSVVLIz == byiaPIayXM){iCszDMZcVM = true;}
      if(lEIcxqJesF == nZQHVfBQzN){UiBZxduApY = true;}
      if(fkASFQJXXb == iEBQYRgcfH){pgRDQoFilx = true;}
      if(ZNGGakuzAg == FRjFVsfpqa){HiquoDZrcY = true;}
      while(nZQHVfBQzN == lEIcxqJesF){BGpxeElwkm = true;}
      while(iEBQYRgcfH == iEBQYRgcfH){wjulZLxGXd = true;}
      while(FRjFVsfpqa == FRjFVsfpqa){fQkOGegpaU = true;}
      if(EdkCwMMVfB == true){EdkCwMMVfB = false;}
      if(wjlaKnhWlB == true){wjlaKnhWlB = false;}
      if(nreAtVpLkb == true){nreAtVpLkb = false;}
      if(zKYYJFTzUL == true){zKYYJFTzUL = false;}
      if(EKweKVfJth == true){EKweKVfJth = false;}
      if(KJEplLyjHZ == true){KJEplLyjHZ = false;}
      if(WBkEBlKNQF == true){WBkEBlKNQF = false;}
      if(UiBZxduApY == true){UiBZxduApY = false;}
      if(pgRDQoFilx == true){pgRDQoFilx = false;}
      if(HiquoDZrcY == true){HiquoDZrcY = false;}
      if(KSroNaIesH == true){KSroNaIesH = false;}
      if(PxtijpigmL == true){PxtijpigmL = false;}
      if(fbaTxkrGkt == true){fbaTxkrGkt = false;}
      if(ECXQNWobpo == true){ECXQNWobpo = false;}
      if(gapdhJnHKy == true){gapdhJnHKy = false;}
      if(TrFQriqYqb == true){TrFQriqYqb = false;}
      if(iCszDMZcVM == true){iCszDMZcVM = false;}
      if(BGpxeElwkm == true){BGpxeElwkm = false;}
      if(wjulZLxGXd == true){wjulZLxGXd = false;}
      if(fQkOGegpaU == true){fQkOGegpaU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GGVIUZLHWM
{ 
  void pfGlgotaBR()
  { 
      bool dabZywMypG = false;
      bool GNgsyFPNLU = false;
      bool bgKXoLUViy = false;
      bool RwtYMRfjbb = false;
      bool rFotJsxLdP = false;
      bool TGtbJxPEjl = false;
      bool bqPqnKTIfg = false;
      bool ZekibWqQOu = false;
      bool NIrSeLCSPO = false;
      bool BbzoABpxFy = false;
      bool ZofwpoULzm = false;
      bool GzooYTzxMb = false;
      bool IBrQfxeuhZ = false;
      bool gtKPVYbubp = false;
      bool qpScIBlKQg = false;
      bool CskdpYwOQr = false;
      bool JYcZFMoZSz = false;
      bool qDUVkRiPId = false;
      bool LTeBXnIgZx = false;
      bool cMeifRNrWw = false;
      string rdCbLFmoht;
      string erYYgwajan;
      string eGsSmWyPgT;
      string lcfyqqaUVJ;
      string IkGYnMrEHq;
      string tVSKklkjon;
      string HWHOICMaho;
      string VGOQftzUeZ;
      string dsIoYQJUNE;
      string GqfgCkcrQk;
      string ARVSVnHCeq;
      string mPEOJNORoq;
      string sqMcheZgOt;
      string QGEsZMXoTj;
      string JHoWRplRWn;
      string VKCYrIErjq;
      string OZmjZfLLox;
      string pZyEhlBpLq;
      string rIKZYFDeAQ;
      string HeFcViTFwl;
      if(rdCbLFmoht == ARVSVnHCeq){dabZywMypG = true;}
      else if(ARVSVnHCeq == rdCbLFmoht){ZofwpoULzm = true;}
      if(erYYgwajan == mPEOJNORoq){GNgsyFPNLU = true;}
      else if(mPEOJNORoq == erYYgwajan){GzooYTzxMb = true;}
      if(eGsSmWyPgT == sqMcheZgOt){bgKXoLUViy = true;}
      else if(sqMcheZgOt == eGsSmWyPgT){IBrQfxeuhZ = true;}
      if(lcfyqqaUVJ == QGEsZMXoTj){RwtYMRfjbb = true;}
      else if(QGEsZMXoTj == lcfyqqaUVJ){gtKPVYbubp = true;}
      if(IkGYnMrEHq == JHoWRplRWn){rFotJsxLdP = true;}
      else if(JHoWRplRWn == IkGYnMrEHq){qpScIBlKQg = true;}
      if(tVSKklkjon == VKCYrIErjq){TGtbJxPEjl = true;}
      else if(VKCYrIErjq == tVSKklkjon){CskdpYwOQr = true;}
      if(HWHOICMaho == OZmjZfLLox){bqPqnKTIfg = true;}
      else if(OZmjZfLLox == HWHOICMaho){JYcZFMoZSz = true;}
      if(VGOQftzUeZ == pZyEhlBpLq){ZekibWqQOu = true;}
      if(dsIoYQJUNE == rIKZYFDeAQ){NIrSeLCSPO = true;}
      if(GqfgCkcrQk == HeFcViTFwl){BbzoABpxFy = true;}
      while(pZyEhlBpLq == VGOQftzUeZ){qDUVkRiPId = true;}
      while(rIKZYFDeAQ == rIKZYFDeAQ){LTeBXnIgZx = true;}
      while(HeFcViTFwl == HeFcViTFwl){cMeifRNrWw = true;}
      if(dabZywMypG == true){dabZywMypG = false;}
      if(GNgsyFPNLU == true){GNgsyFPNLU = false;}
      if(bgKXoLUViy == true){bgKXoLUViy = false;}
      if(RwtYMRfjbb == true){RwtYMRfjbb = false;}
      if(rFotJsxLdP == true){rFotJsxLdP = false;}
      if(TGtbJxPEjl == true){TGtbJxPEjl = false;}
      if(bqPqnKTIfg == true){bqPqnKTIfg = false;}
      if(ZekibWqQOu == true){ZekibWqQOu = false;}
      if(NIrSeLCSPO == true){NIrSeLCSPO = false;}
      if(BbzoABpxFy == true){BbzoABpxFy = false;}
      if(ZofwpoULzm == true){ZofwpoULzm = false;}
      if(GzooYTzxMb == true){GzooYTzxMb = false;}
      if(IBrQfxeuhZ == true){IBrQfxeuhZ = false;}
      if(gtKPVYbubp == true){gtKPVYbubp = false;}
      if(qpScIBlKQg == true){qpScIBlKQg = false;}
      if(CskdpYwOQr == true){CskdpYwOQr = false;}
      if(JYcZFMoZSz == true){JYcZFMoZSz = false;}
      if(qDUVkRiPId == true){qDUVkRiPId = false;}
      if(LTeBXnIgZx == true){LTeBXnIgZx = false;}
      if(cMeifRNrWw == true){cMeifRNrWw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YXVXUIVODB
{ 
  void lMNNGbgwHJ()
  { 
      bool FYzmCOTTLn = false;
      bool FzjCdUBkNi = false;
      bool JRGuuZjZik = false;
      bool ryEfXqSjoB = false;
      bool IUSBNAjoSs = false;
      bool xUzeYnSEqb = false;
      bool dskZwGuDem = false;
      bool CRuMaoyEgu = false;
      bool otGonXyZHi = false;
      bool XOrMWOirFG = false;
      bool FgKfqeYmDi = false;
      bool oNWumilulY = false;
      bool HUwuOnZioM = false;
      bool GGzZpIjZyJ = false;
      bool zLWYsKqxZm = false;
      bool cmFfyjkPRC = false;
      bool EpyqciNwFd = false;
      bool zLxcZwyXBD = false;
      bool wcICiSASaF = false;
      bool XUIuEJNfuK = false;
      string dqZSfXoaDt;
      string zqzybGWxkd;
      string NCqBJktCok;
      string kQLDOXWZsm;
      string eqgNCBGfQR;
      string QiPiAazYJt;
      string cllRJheujE;
      string jxEyzWVdyH;
      string eOkXTBAbCm;
      string XxQyJrEODU;
      string VLuMgTdRjc;
      string FVaBPNBNxH;
      string gDrwfmgFnG;
      string RGZclSSYqA;
      string XiqYhBWOiw;
      string qpRumRSygt;
      string lYcdLzuxPw;
      string tbWxjyMSOd;
      string PRWqPbodpT;
      string AUrxNzFNNi;
      if(dqZSfXoaDt == VLuMgTdRjc){FYzmCOTTLn = true;}
      else if(VLuMgTdRjc == dqZSfXoaDt){FgKfqeYmDi = true;}
      if(zqzybGWxkd == FVaBPNBNxH){FzjCdUBkNi = true;}
      else if(FVaBPNBNxH == zqzybGWxkd){oNWumilulY = true;}
      if(NCqBJktCok == gDrwfmgFnG){JRGuuZjZik = true;}
      else if(gDrwfmgFnG == NCqBJktCok){HUwuOnZioM = true;}
      if(kQLDOXWZsm == RGZclSSYqA){ryEfXqSjoB = true;}
      else if(RGZclSSYqA == kQLDOXWZsm){GGzZpIjZyJ = true;}
      if(eqgNCBGfQR == XiqYhBWOiw){IUSBNAjoSs = true;}
      else if(XiqYhBWOiw == eqgNCBGfQR){zLWYsKqxZm = true;}
      if(QiPiAazYJt == qpRumRSygt){xUzeYnSEqb = true;}
      else if(qpRumRSygt == QiPiAazYJt){cmFfyjkPRC = true;}
      if(cllRJheujE == lYcdLzuxPw){dskZwGuDem = true;}
      else if(lYcdLzuxPw == cllRJheujE){EpyqciNwFd = true;}
      if(jxEyzWVdyH == tbWxjyMSOd){CRuMaoyEgu = true;}
      if(eOkXTBAbCm == PRWqPbodpT){otGonXyZHi = true;}
      if(XxQyJrEODU == AUrxNzFNNi){XOrMWOirFG = true;}
      while(tbWxjyMSOd == jxEyzWVdyH){zLxcZwyXBD = true;}
      while(PRWqPbodpT == PRWqPbodpT){wcICiSASaF = true;}
      while(AUrxNzFNNi == AUrxNzFNNi){XUIuEJNfuK = true;}
      if(FYzmCOTTLn == true){FYzmCOTTLn = false;}
      if(FzjCdUBkNi == true){FzjCdUBkNi = false;}
      if(JRGuuZjZik == true){JRGuuZjZik = false;}
      if(ryEfXqSjoB == true){ryEfXqSjoB = false;}
      if(IUSBNAjoSs == true){IUSBNAjoSs = false;}
      if(xUzeYnSEqb == true){xUzeYnSEqb = false;}
      if(dskZwGuDem == true){dskZwGuDem = false;}
      if(CRuMaoyEgu == true){CRuMaoyEgu = false;}
      if(otGonXyZHi == true){otGonXyZHi = false;}
      if(XOrMWOirFG == true){XOrMWOirFG = false;}
      if(FgKfqeYmDi == true){FgKfqeYmDi = false;}
      if(oNWumilulY == true){oNWumilulY = false;}
      if(HUwuOnZioM == true){HUwuOnZioM = false;}
      if(GGzZpIjZyJ == true){GGzZpIjZyJ = false;}
      if(zLWYsKqxZm == true){zLWYsKqxZm = false;}
      if(cmFfyjkPRC == true){cmFfyjkPRC = false;}
      if(EpyqciNwFd == true){EpyqciNwFd = false;}
      if(zLxcZwyXBD == true){zLxcZwyXBD = false;}
      if(wcICiSASaF == true){wcICiSASaF = false;}
      if(XUIuEJNfuK == true){XUIuEJNfuK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EIZQBDEIBR
{ 
  void MUsyuGxUgM()
  { 
      bool OjIXIogVkz = false;
      bool gBcqWdBeuX = false;
      bool qnKwOzboAu = false;
      bool xRoZVDhxqi = false;
      bool XswBVgwygE = false;
      bool ZSaaKZYMII = false;
      bool NqVoCPLCUT = false;
      bool uDnLAxrJZg = false;
      bool DcIuUdpNPw = false;
      bool eVohVfXGzG = false;
      bool UscNJVeOZN = false;
      bool hPlaFjiZTX = false;
      bool YymYoYOFpU = false;
      bool YkJSMJAtkz = false;
      bool yanBOOjNcl = false;
      bool wylbgWGDYk = false;
      bool HZYFnwFSOw = false;
      bool innUYyJkKZ = false;
      bool oBcDYazhlo = false;
      bool CwVAqYBhMR = false;
      string FTjiUAjUms;
      string fjwstaJPSV;
      string QQmGnZdgzb;
      string HPPAXcjbjE;
      string wEDQlRzKPm;
      string CtZZSngduu;
      string VCULkPTuUR;
      string pgfOZMMVTW;
      string aTRLYNopgj;
      string wFgohsirfW;
      string yDpywUNLAG;
      string aLJXTBkImW;
      string ZdOkVjApff;
      string dUoxXWdSPD;
      string zdpaIjwIUf;
      string HZFIwUoFcL;
      string UXeTbGVLzx;
      string XSsiXwmmbk;
      string nqVzYEPgBD;
      string hYpEhbyVyB;
      if(FTjiUAjUms == yDpywUNLAG){OjIXIogVkz = true;}
      else if(yDpywUNLAG == FTjiUAjUms){UscNJVeOZN = true;}
      if(fjwstaJPSV == aLJXTBkImW){gBcqWdBeuX = true;}
      else if(aLJXTBkImW == fjwstaJPSV){hPlaFjiZTX = true;}
      if(QQmGnZdgzb == ZdOkVjApff){qnKwOzboAu = true;}
      else if(ZdOkVjApff == QQmGnZdgzb){YymYoYOFpU = true;}
      if(HPPAXcjbjE == dUoxXWdSPD){xRoZVDhxqi = true;}
      else if(dUoxXWdSPD == HPPAXcjbjE){YkJSMJAtkz = true;}
      if(wEDQlRzKPm == zdpaIjwIUf){XswBVgwygE = true;}
      else if(zdpaIjwIUf == wEDQlRzKPm){yanBOOjNcl = true;}
      if(CtZZSngduu == HZFIwUoFcL){ZSaaKZYMII = true;}
      else if(HZFIwUoFcL == CtZZSngduu){wylbgWGDYk = true;}
      if(VCULkPTuUR == UXeTbGVLzx){NqVoCPLCUT = true;}
      else if(UXeTbGVLzx == VCULkPTuUR){HZYFnwFSOw = true;}
      if(pgfOZMMVTW == XSsiXwmmbk){uDnLAxrJZg = true;}
      if(aTRLYNopgj == nqVzYEPgBD){DcIuUdpNPw = true;}
      if(wFgohsirfW == hYpEhbyVyB){eVohVfXGzG = true;}
      while(XSsiXwmmbk == pgfOZMMVTW){innUYyJkKZ = true;}
      while(nqVzYEPgBD == nqVzYEPgBD){oBcDYazhlo = true;}
      while(hYpEhbyVyB == hYpEhbyVyB){CwVAqYBhMR = true;}
      if(OjIXIogVkz == true){OjIXIogVkz = false;}
      if(gBcqWdBeuX == true){gBcqWdBeuX = false;}
      if(qnKwOzboAu == true){qnKwOzboAu = false;}
      if(xRoZVDhxqi == true){xRoZVDhxqi = false;}
      if(XswBVgwygE == true){XswBVgwygE = false;}
      if(ZSaaKZYMII == true){ZSaaKZYMII = false;}
      if(NqVoCPLCUT == true){NqVoCPLCUT = false;}
      if(uDnLAxrJZg == true){uDnLAxrJZg = false;}
      if(DcIuUdpNPw == true){DcIuUdpNPw = false;}
      if(eVohVfXGzG == true){eVohVfXGzG = false;}
      if(UscNJVeOZN == true){UscNJVeOZN = false;}
      if(hPlaFjiZTX == true){hPlaFjiZTX = false;}
      if(YymYoYOFpU == true){YymYoYOFpU = false;}
      if(YkJSMJAtkz == true){YkJSMJAtkz = false;}
      if(yanBOOjNcl == true){yanBOOjNcl = false;}
      if(wylbgWGDYk == true){wylbgWGDYk = false;}
      if(HZYFnwFSOw == true){HZYFnwFSOw = false;}
      if(innUYyJkKZ == true){innUYyJkKZ = false;}
      if(oBcDYazhlo == true){oBcDYazhlo = false;}
      if(CwVAqYBhMR == true){CwVAqYBhMR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XQZTEYUPQE
{ 
  void OOIWyfhgPN()
  { 
      bool wErNwlGVsi = false;
      bool ChdUQWbQjf = false;
      bool GWzMOCqBOu = false;
      bool aLdPEzXpHK = false;
      bool BqiLtjoBDf = false;
      bool jxRTXYFfzs = false;
      bool uEGxIqEOQQ = false;
      bool ykIZeOnmSd = false;
      bool MoyiLcsKqe = false;
      bool trqNOwjlDC = false;
      bool fakmgyornJ = false;
      bool kRMUgFFXke = false;
      bool xsWkVGttKh = false;
      bool dBjPylDLBN = false;
      bool nBVhsceVgJ = false;
      bool pMBXFlDAQa = false;
      bool DthGejgxWt = false;
      bool BtWWpuXoqs = false;
      bool bXMAqRzLKL = false;
      bool hDtaJsTPCJ = false;
      string WIBabUKdzf;
      string bslDzMEZQV;
      string pCCSjKsuDs;
      string HZoJoduOVK;
      string TPCYAOEglo;
      string wjydyUGhqQ;
      string bOaFXBEbNU;
      string QpEFBZzdSV;
      string GMJNwXbKLU;
      string XNXFhFoxAy;
      string JbSRXGercX;
      string VbOUKPFMIA;
      string YtQswDSyWw;
      string jBcULdsqop;
      string rjgmyuyCtS;
      string zcnAYOLYUU;
      string mfUfmTztJg;
      string WNWRHoMctA;
      string EQEEwHNbuw;
      string RTWUDLOBze;
      if(WIBabUKdzf == JbSRXGercX){wErNwlGVsi = true;}
      else if(JbSRXGercX == WIBabUKdzf){fakmgyornJ = true;}
      if(bslDzMEZQV == VbOUKPFMIA){ChdUQWbQjf = true;}
      else if(VbOUKPFMIA == bslDzMEZQV){kRMUgFFXke = true;}
      if(pCCSjKsuDs == YtQswDSyWw){GWzMOCqBOu = true;}
      else if(YtQswDSyWw == pCCSjKsuDs){xsWkVGttKh = true;}
      if(HZoJoduOVK == jBcULdsqop){aLdPEzXpHK = true;}
      else if(jBcULdsqop == HZoJoduOVK){dBjPylDLBN = true;}
      if(TPCYAOEglo == rjgmyuyCtS){BqiLtjoBDf = true;}
      else if(rjgmyuyCtS == TPCYAOEglo){nBVhsceVgJ = true;}
      if(wjydyUGhqQ == zcnAYOLYUU){jxRTXYFfzs = true;}
      else if(zcnAYOLYUU == wjydyUGhqQ){pMBXFlDAQa = true;}
      if(bOaFXBEbNU == mfUfmTztJg){uEGxIqEOQQ = true;}
      else if(mfUfmTztJg == bOaFXBEbNU){DthGejgxWt = true;}
      if(QpEFBZzdSV == WNWRHoMctA){ykIZeOnmSd = true;}
      if(GMJNwXbKLU == EQEEwHNbuw){MoyiLcsKqe = true;}
      if(XNXFhFoxAy == RTWUDLOBze){trqNOwjlDC = true;}
      while(WNWRHoMctA == QpEFBZzdSV){BtWWpuXoqs = true;}
      while(EQEEwHNbuw == EQEEwHNbuw){bXMAqRzLKL = true;}
      while(RTWUDLOBze == RTWUDLOBze){hDtaJsTPCJ = true;}
      if(wErNwlGVsi == true){wErNwlGVsi = false;}
      if(ChdUQWbQjf == true){ChdUQWbQjf = false;}
      if(GWzMOCqBOu == true){GWzMOCqBOu = false;}
      if(aLdPEzXpHK == true){aLdPEzXpHK = false;}
      if(BqiLtjoBDf == true){BqiLtjoBDf = false;}
      if(jxRTXYFfzs == true){jxRTXYFfzs = false;}
      if(uEGxIqEOQQ == true){uEGxIqEOQQ = false;}
      if(ykIZeOnmSd == true){ykIZeOnmSd = false;}
      if(MoyiLcsKqe == true){MoyiLcsKqe = false;}
      if(trqNOwjlDC == true){trqNOwjlDC = false;}
      if(fakmgyornJ == true){fakmgyornJ = false;}
      if(kRMUgFFXke == true){kRMUgFFXke = false;}
      if(xsWkVGttKh == true){xsWkVGttKh = false;}
      if(dBjPylDLBN == true){dBjPylDLBN = false;}
      if(nBVhsceVgJ == true){nBVhsceVgJ = false;}
      if(pMBXFlDAQa == true){pMBXFlDAQa = false;}
      if(DthGejgxWt == true){DthGejgxWt = false;}
      if(BtWWpuXoqs == true){BtWWpuXoqs = false;}
      if(bXMAqRzLKL == true){bXMAqRzLKL = false;}
      if(hDtaJsTPCJ == true){hDtaJsTPCJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EPGUXWIKAV
{ 
  void seQCZxmwBf()
  { 
      bool tWiwsOQeHf = false;
      bool QxpByoDDFq = false;
      bool pnUwoCsxYb = false;
      bool wnwhHAhofp = false;
      bool pJeTbfVpIa = false;
      bool ouuTZFCmHp = false;
      bool USFficAHsy = false;
      bool GOXOBgIATI = false;
      bool gDoxlBrbIB = false;
      bool xuhoVWDyky = false;
      bool fNwJTaXfRr = false;
      bool xCSyJRdHtg = false;
      bool jXzrBLfhse = false;
      bool dJOUcSHedK = false;
      bool dMJPEucifE = false;
      bool ruEDOHOEII = false;
      bool tolmOmmxVp = false;
      bool JydiDWOimF = false;
      bool ixBolhFLGV = false;
      bool DDVUQnaWBR = false;
      string SADedrlDlL;
      string DMthnMzjUX;
      string ltKhnZthEJ;
      string guhsFDJATT;
      string jEHMHjWKLo;
      string sHKEIYpVpD;
      string yDzceIdBbk;
      string CyQBmhlyZE;
      string DiWPQZkdjg;
      string MmJPVgFehz;
      string GUialtpIRa;
      string lqulAOgiLE;
      string XAQtXPnAfF;
      string cHQaxhAudW;
      string ibLJuVrWOG;
      string AVTcaFEoDW;
      string GpcLydaUnS;
      string NkFoUunHzB;
      string XQlYFGnmzr;
      string cLqHPszALQ;
      if(SADedrlDlL == GUialtpIRa){tWiwsOQeHf = true;}
      else if(GUialtpIRa == SADedrlDlL){fNwJTaXfRr = true;}
      if(DMthnMzjUX == lqulAOgiLE){QxpByoDDFq = true;}
      else if(lqulAOgiLE == DMthnMzjUX){xCSyJRdHtg = true;}
      if(ltKhnZthEJ == XAQtXPnAfF){pnUwoCsxYb = true;}
      else if(XAQtXPnAfF == ltKhnZthEJ){jXzrBLfhse = true;}
      if(guhsFDJATT == cHQaxhAudW){wnwhHAhofp = true;}
      else if(cHQaxhAudW == guhsFDJATT){dJOUcSHedK = true;}
      if(jEHMHjWKLo == ibLJuVrWOG){pJeTbfVpIa = true;}
      else if(ibLJuVrWOG == jEHMHjWKLo){dMJPEucifE = true;}
      if(sHKEIYpVpD == AVTcaFEoDW){ouuTZFCmHp = true;}
      else if(AVTcaFEoDW == sHKEIYpVpD){ruEDOHOEII = true;}
      if(yDzceIdBbk == GpcLydaUnS){USFficAHsy = true;}
      else if(GpcLydaUnS == yDzceIdBbk){tolmOmmxVp = true;}
      if(CyQBmhlyZE == NkFoUunHzB){GOXOBgIATI = true;}
      if(DiWPQZkdjg == XQlYFGnmzr){gDoxlBrbIB = true;}
      if(MmJPVgFehz == cLqHPszALQ){xuhoVWDyky = true;}
      while(NkFoUunHzB == CyQBmhlyZE){JydiDWOimF = true;}
      while(XQlYFGnmzr == XQlYFGnmzr){ixBolhFLGV = true;}
      while(cLqHPszALQ == cLqHPszALQ){DDVUQnaWBR = true;}
      if(tWiwsOQeHf == true){tWiwsOQeHf = false;}
      if(QxpByoDDFq == true){QxpByoDDFq = false;}
      if(pnUwoCsxYb == true){pnUwoCsxYb = false;}
      if(wnwhHAhofp == true){wnwhHAhofp = false;}
      if(pJeTbfVpIa == true){pJeTbfVpIa = false;}
      if(ouuTZFCmHp == true){ouuTZFCmHp = false;}
      if(USFficAHsy == true){USFficAHsy = false;}
      if(GOXOBgIATI == true){GOXOBgIATI = false;}
      if(gDoxlBrbIB == true){gDoxlBrbIB = false;}
      if(xuhoVWDyky == true){xuhoVWDyky = false;}
      if(fNwJTaXfRr == true){fNwJTaXfRr = false;}
      if(xCSyJRdHtg == true){xCSyJRdHtg = false;}
      if(jXzrBLfhse == true){jXzrBLfhse = false;}
      if(dJOUcSHedK == true){dJOUcSHedK = false;}
      if(dMJPEucifE == true){dMJPEucifE = false;}
      if(ruEDOHOEII == true){ruEDOHOEII = false;}
      if(tolmOmmxVp == true){tolmOmmxVp = false;}
      if(JydiDWOimF == true){JydiDWOimF = false;}
      if(ixBolhFLGV == true){ixBolhFLGV = false;}
      if(DDVUQnaWBR == true){DDVUQnaWBR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TDNMRCKXFL
{ 
  void aUqZkNOVol()
  { 
      bool BmVaeiODAE = false;
      bool lzrRVnQkDQ = false;
      bool JHKBuwVDbT = false;
      bool BekOQdosnD = false;
      bool iXFKIsuYYA = false;
      bool XXOEEsbUfh = false;
      bool MLagCGOdBq = false;
      bool yXxzhkCzsB = false;
      bool AwdaucQgJW = false;
      bool BTMFpWwYHB = false;
      bool eRWgBAaOVS = false;
      bool qcbdgQgAkZ = false;
      bool pgTepdKrJK = false;
      bool ncrqWiZxYt = false;
      bool CBKpeYrhXZ = false;
      bool owmhLxxqqW = false;
      bool phFKdNkkGy = false;
      bool pjaqWoVcAQ = false;
      bool lbTiVrpJfZ = false;
      bool khGBDTuzLQ = false;
      string FCwrWDOklc;
      string zGggueJXwg;
      string XIVbxnGhHQ;
      string BbUiaXkmkF;
      string PUrRKbsBoJ;
      string zHcnawfUuh;
      string xgcUaWlxFX;
      string sVmpQCQEQU;
      string uErxQszfHd;
      string qQrDIirWpm;
      string puwQPcUlXY;
      string ebDZmsneDh;
      string XGoagcdjhh;
      string KtOddzIagn;
      string YMIizOMRPP;
      string uMSIOjGUjm;
      string zjDpOkNZun;
      string jMxPIKxGbR;
      string QLTSlxaFOt;
      string snqtnnJSUN;
      if(FCwrWDOklc == puwQPcUlXY){BmVaeiODAE = true;}
      else if(puwQPcUlXY == FCwrWDOklc){eRWgBAaOVS = true;}
      if(zGggueJXwg == ebDZmsneDh){lzrRVnQkDQ = true;}
      else if(ebDZmsneDh == zGggueJXwg){qcbdgQgAkZ = true;}
      if(XIVbxnGhHQ == XGoagcdjhh){JHKBuwVDbT = true;}
      else if(XGoagcdjhh == XIVbxnGhHQ){pgTepdKrJK = true;}
      if(BbUiaXkmkF == KtOddzIagn){BekOQdosnD = true;}
      else if(KtOddzIagn == BbUiaXkmkF){ncrqWiZxYt = true;}
      if(PUrRKbsBoJ == YMIizOMRPP){iXFKIsuYYA = true;}
      else if(YMIizOMRPP == PUrRKbsBoJ){CBKpeYrhXZ = true;}
      if(zHcnawfUuh == uMSIOjGUjm){XXOEEsbUfh = true;}
      else if(uMSIOjGUjm == zHcnawfUuh){owmhLxxqqW = true;}
      if(xgcUaWlxFX == zjDpOkNZun){MLagCGOdBq = true;}
      else if(zjDpOkNZun == xgcUaWlxFX){phFKdNkkGy = true;}
      if(sVmpQCQEQU == jMxPIKxGbR){yXxzhkCzsB = true;}
      if(uErxQszfHd == QLTSlxaFOt){AwdaucQgJW = true;}
      if(qQrDIirWpm == snqtnnJSUN){BTMFpWwYHB = true;}
      while(jMxPIKxGbR == sVmpQCQEQU){pjaqWoVcAQ = true;}
      while(QLTSlxaFOt == QLTSlxaFOt){lbTiVrpJfZ = true;}
      while(snqtnnJSUN == snqtnnJSUN){khGBDTuzLQ = true;}
      if(BmVaeiODAE == true){BmVaeiODAE = false;}
      if(lzrRVnQkDQ == true){lzrRVnQkDQ = false;}
      if(JHKBuwVDbT == true){JHKBuwVDbT = false;}
      if(BekOQdosnD == true){BekOQdosnD = false;}
      if(iXFKIsuYYA == true){iXFKIsuYYA = false;}
      if(XXOEEsbUfh == true){XXOEEsbUfh = false;}
      if(MLagCGOdBq == true){MLagCGOdBq = false;}
      if(yXxzhkCzsB == true){yXxzhkCzsB = false;}
      if(AwdaucQgJW == true){AwdaucQgJW = false;}
      if(BTMFpWwYHB == true){BTMFpWwYHB = false;}
      if(eRWgBAaOVS == true){eRWgBAaOVS = false;}
      if(qcbdgQgAkZ == true){qcbdgQgAkZ = false;}
      if(pgTepdKrJK == true){pgTepdKrJK = false;}
      if(ncrqWiZxYt == true){ncrqWiZxYt = false;}
      if(CBKpeYrhXZ == true){CBKpeYrhXZ = false;}
      if(owmhLxxqqW == true){owmhLxxqqW = false;}
      if(phFKdNkkGy == true){phFKdNkkGy = false;}
      if(pjaqWoVcAQ == true){pjaqWoVcAQ = false;}
      if(lbTiVrpJfZ == true){lbTiVrpJfZ = false;}
      if(khGBDTuzLQ == true){khGBDTuzLQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TQLFIHMHXO
{ 
  void mLgmSiSJgH()
  { 
      bool jknfbRdpAg = false;
      bool AzgeRjGJmf = false;
      bool LwfePVgNIQ = false;
      bool FeZMjRzqti = false;
      bool QyghMkMAKw = false;
      bool gwdpXmFJPG = false;
      bool jQhjbUZTuA = false;
      bool kOPEPNPxRd = false;
      bool JfCMjIAinw = false;
      bool LobmyzPxFq = false;
      bool LrFKKRfZaK = false;
      bool XIqkxENVzS = false;
      bool UpeynumbFP = false;
      bool ySqZRQaqBR = false;
      bool baHdYDyppt = false;
      bool lsxlWVMGWP = false;
      bool eEULLEQQSf = false;
      bool dVUhpsiAZj = false;
      bool xwkKdEUEDw = false;
      bool ETUllXFwST = false;
      string OnYBGOWaZU;
      string BYuIaIylyk;
      string fCJVnAoOfm;
      string zVwJTKmwTE;
      string gFKuVbbDzb;
      string rAnWSMeDNF;
      string YItlUebkoP;
      string UBRsDarNzL;
      string XlPEtzgYpG;
      string fjiOeXKXaq;
      string AqNiGphtTr;
      string URDChmsorV;
      string yCuiijSDOe;
      string QTmIKgXfyD;
      string RlFykOgffq;
      string eUeEsxwezV;
      string WdfnaAdurA;
      string PNpnELxwxU;
      string DmWWAuohPN;
      string ksfcfmGRWj;
      if(OnYBGOWaZU == AqNiGphtTr){jknfbRdpAg = true;}
      else if(AqNiGphtTr == OnYBGOWaZU){LrFKKRfZaK = true;}
      if(BYuIaIylyk == URDChmsorV){AzgeRjGJmf = true;}
      else if(URDChmsorV == BYuIaIylyk){XIqkxENVzS = true;}
      if(fCJVnAoOfm == yCuiijSDOe){LwfePVgNIQ = true;}
      else if(yCuiijSDOe == fCJVnAoOfm){UpeynumbFP = true;}
      if(zVwJTKmwTE == QTmIKgXfyD){FeZMjRzqti = true;}
      else if(QTmIKgXfyD == zVwJTKmwTE){ySqZRQaqBR = true;}
      if(gFKuVbbDzb == RlFykOgffq){QyghMkMAKw = true;}
      else if(RlFykOgffq == gFKuVbbDzb){baHdYDyppt = true;}
      if(rAnWSMeDNF == eUeEsxwezV){gwdpXmFJPG = true;}
      else if(eUeEsxwezV == rAnWSMeDNF){lsxlWVMGWP = true;}
      if(YItlUebkoP == WdfnaAdurA){jQhjbUZTuA = true;}
      else if(WdfnaAdurA == YItlUebkoP){eEULLEQQSf = true;}
      if(UBRsDarNzL == PNpnELxwxU){kOPEPNPxRd = true;}
      if(XlPEtzgYpG == DmWWAuohPN){JfCMjIAinw = true;}
      if(fjiOeXKXaq == ksfcfmGRWj){LobmyzPxFq = true;}
      while(PNpnELxwxU == UBRsDarNzL){dVUhpsiAZj = true;}
      while(DmWWAuohPN == DmWWAuohPN){xwkKdEUEDw = true;}
      while(ksfcfmGRWj == ksfcfmGRWj){ETUllXFwST = true;}
      if(jknfbRdpAg == true){jknfbRdpAg = false;}
      if(AzgeRjGJmf == true){AzgeRjGJmf = false;}
      if(LwfePVgNIQ == true){LwfePVgNIQ = false;}
      if(FeZMjRzqti == true){FeZMjRzqti = false;}
      if(QyghMkMAKw == true){QyghMkMAKw = false;}
      if(gwdpXmFJPG == true){gwdpXmFJPG = false;}
      if(jQhjbUZTuA == true){jQhjbUZTuA = false;}
      if(kOPEPNPxRd == true){kOPEPNPxRd = false;}
      if(JfCMjIAinw == true){JfCMjIAinw = false;}
      if(LobmyzPxFq == true){LobmyzPxFq = false;}
      if(LrFKKRfZaK == true){LrFKKRfZaK = false;}
      if(XIqkxENVzS == true){XIqkxENVzS = false;}
      if(UpeynumbFP == true){UpeynumbFP = false;}
      if(ySqZRQaqBR == true){ySqZRQaqBR = false;}
      if(baHdYDyppt == true){baHdYDyppt = false;}
      if(lsxlWVMGWP == true){lsxlWVMGWP = false;}
      if(eEULLEQQSf == true){eEULLEQQSf = false;}
      if(dVUhpsiAZj == true){dVUhpsiAZj = false;}
      if(xwkKdEUEDw == true){xwkKdEUEDw = false;}
      if(ETUllXFwST == true){ETUllXFwST = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SQZKOABKNZ
{ 
  void RiadkUVZGO()
  { 
      bool sQroCFapmM = false;
      bool PtUzVFVOqL = false;
      bool iQdxeYSxeK = false;
      bool UpJrQUTcZR = false;
      bool KzuaSfeQRj = false;
      bool DfwJTcltKd = false;
      bool mcLcrZjbhB = false;
      bool krnZAjVDey = false;
      bool tCftGosAYn = false;
      bool hYSwegnRir = false;
      bool uChQzLqWIi = false;
      bool GiOLikxQVD = false;
      bool gjDtSLYquS = false;
      bool wDUmDrTPuu = false;
      bool xVqogzJHNs = false;
      bool iXwfKKynxm = false;
      bool lzapmCNbHq = false;
      bool QhUaFKsOMS = false;
      bool BRdBjXHobr = false;
      bool sfRIIxtBBe = false;
      string dBdKbMBuSr;
      string fWKupYSlYw;
      string sOPFtBUGng;
      string cuKATknyZG;
      string pBZlMofQSN;
      string WNNfmPkYPa;
      string ruHlOjLJbE;
      string jTMRFrodrF;
      string VEmZJPhdMD;
      string APizOutmWc;
      string cVnOcCBuZu;
      string aGgJEnHhby;
      string BhwXEUkMDK;
      string yBGOczPYwH;
      string OlDRcsiYta;
      string mMLXbtYPJI;
      string RnrOxZzRfF;
      string XhkUjOdeuK;
      string lMScWlphmi;
      string ZzPnoZtnUD;
      if(dBdKbMBuSr == cVnOcCBuZu){sQroCFapmM = true;}
      else if(cVnOcCBuZu == dBdKbMBuSr){uChQzLqWIi = true;}
      if(fWKupYSlYw == aGgJEnHhby){PtUzVFVOqL = true;}
      else if(aGgJEnHhby == fWKupYSlYw){GiOLikxQVD = true;}
      if(sOPFtBUGng == BhwXEUkMDK){iQdxeYSxeK = true;}
      else if(BhwXEUkMDK == sOPFtBUGng){gjDtSLYquS = true;}
      if(cuKATknyZG == yBGOczPYwH){UpJrQUTcZR = true;}
      else if(yBGOczPYwH == cuKATknyZG){wDUmDrTPuu = true;}
      if(pBZlMofQSN == OlDRcsiYta){KzuaSfeQRj = true;}
      else if(OlDRcsiYta == pBZlMofQSN){xVqogzJHNs = true;}
      if(WNNfmPkYPa == mMLXbtYPJI){DfwJTcltKd = true;}
      else if(mMLXbtYPJI == WNNfmPkYPa){iXwfKKynxm = true;}
      if(ruHlOjLJbE == RnrOxZzRfF){mcLcrZjbhB = true;}
      else if(RnrOxZzRfF == ruHlOjLJbE){lzapmCNbHq = true;}
      if(jTMRFrodrF == XhkUjOdeuK){krnZAjVDey = true;}
      if(VEmZJPhdMD == lMScWlphmi){tCftGosAYn = true;}
      if(APizOutmWc == ZzPnoZtnUD){hYSwegnRir = true;}
      while(XhkUjOdeuK == jTMRFrodrF){QhUaFKsOMS = true;}
      while(lMScWlphmi == lMScWlphmi){BRdBjXHobr = true;}
      while(ZzPnoZtnUD == ZzPnoZtnUD){sfRIIxtBBe = true;}
      if(sQroCFapmM == true){sQroCFapmM = false;}
      if(PtUzVFVOqL == true){PtUzVFVOqL = false;}
      if(iQdxeYSxeK == true){iQdxeYSxeK = false;}
      if(UpJrQUTcZR == true){UpJrQUTcZR = false;}
      if(KzuaSfeQRj == true){KzuaSfeQRj = false;}
      if(DfwJTcltKd == true){DfwJTcltKd = false;}
      if(mcLcrZjbhB == true){mcLcrZjbhB = false;}
      if(krnZAjVDey == true){krnZAjVDey = false;}
      if(tCftGosAYn == true){tCftGosAYn = false;}
      if(hYSwegnRir == true){hYSwegnRir = false;}
      if(uChQzLqWIi == true){uChQzLqWIi = false;}
      if(GiOLikxQVD == true){GiOLikxQVD = false;}
      if(gjDtSLYquS == true){gjDtSLYquS = false;}
      if(wDUmDrTPuu == true){wDUmDrTPuu = false;}
      if(xVqogzJHNs == true){xVqogzJHNs = false;}
      if(iXwfKKynxm == true){iXwfKKynxm = false;}
      if(lzapmCNbHq == true){lzapmCNbHq = false;}
      if(QhUaFKsOMS == true){QhUaFKsOMS = false;}
      if(BRdBjXHobr == true){BRdBjXHobr = false;}
      if(sfRIIxtBBe == true){sfRIIxtBBe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UMNWXKFMAO
{ 
  void nNGtauaUhz()
  { 
      bool KrZnixTzWG = false;
      bool qBfmWTtmzF = false;
      bool kiisDSMhFR = false;
      bool lldZBBqeJr = false;
      bool gOZOotgETD = false;
      bool mLqlyaIfkQ = false;
      bool jktFTEXGkV = false;
      bool bPcGYWJTDI = false;
      bool kIOCdauqaa = false;
      bool rKssIwTTtk = false;
      bool WZSxaWhkNb = false;
      bool RncbfbVras = false;
      bool JffKcQVjyc = false;
      bool CpYSlKpQaH = false;
      bool sKdzJDhRMf = false;
      bool ZbrBbptHUJ = false;
      bool AxlkZaOJpU = false;
      bool lEQTAyCgBZ = false;
      bool iEWRCZxXqu = false;
      bool QhwQGuXsZh = false;
      string oumdBDcGqI;
      string yzdZStWBbY;
      string cALFYVhnQA;
      string yPfMKZsemU;
      string kMBanwJwuF;
      string riwUOnjgEf;
      string UnpqJhTROr;
      string BqOHnPzjRc;
      string LksKHPSLxW;
      string pLaHzwWKQF;
      string brhCEATnfz;
      string nzPaTjueit;
      string OHUrCoQGIq;
      string roTLBTDqFG;
      string udeyipwznP;
      string BraWpTXozP;
      string jNfoGzfEZz;
      string fEYbzjcVJM;
      string sQSspANwUg;
      string wNqpWhypri;
      if(oumdBDcGqI == brhCEATnfz){KrZnixTzWG = true;}
      else if(brhCEATnfz == oumdBDcGqI){WZSxaWhkNb = true;}
      if(yzdZStWBbY == nzPaTjueit){qBfmWTtmzF = true;}
      else if(nzPaTjueit == yzdZStWBbY){RncbfbVras = true;}
      if(cALFYVhnQA == OHUrCoQGIq){kiisDSMhFR = true;}
      else if(OHUrCoQGIq == cALFYVhnQA){JffKcQVjyc = true;}
      if(yPfMKZsemU == roTLBTDqFG){lldZBBqeJr = true;}
      else if(roTLBTDqFG == yPfMKZsemU){CpYSlKpQaH = true;}
      if(kMBanwJwuF == udeyipwznP){gOZOotgETD = true;}
      else if(udeyipwznP == kMBanwJwuF){sKdzJDhRMf = true;}
      if(riwUOnjgEf == BraWpTXozP){mLqlyaIfkQ = true;}
      else if(BraWpTXozP == riwUOnjgEf){ZbrBbptHUJ = true;}
      if(UnpqJhTROr == jNfoGzfEZz){jktFTEXGkV = true;}
      else if(jNfoGzfEZz == UnpqJhTROr){AxlkZaOJpU = true;}
      if(BqOHnPzjRc == fEYbzjcVJM){bPcGYWJTDI = true;}
      if(LksKHPSLxW == sQSspANwUg){kIOCdauqaa = true;}
      if(pLaHzwWKQF == wNqpWhypri){rKssIwTTtk = true;}
      while(fEYbzjcVJM == BqOHnPzjRc){lEQTAyCgBZ = true;}
      while(sQSspANwUg == sQSspANwUg){iEWRCZxXqu = true;}
      while(wNqpWhypri == wNqpWhypri){QhwQGuXsZh = true;}
      if(KrZnixTzWG == true){KrZnixTzWG = false;}
      if(qBfmWTtmzF == true){qBfmWTtmzF = false;}
      if(kiisDSMhFR == true){kiisDSMhFR = false;}
      if(lldZBBqeJr == true){lldZBBqeJr = false;}
      if(gOZOotgETD == true){gOZOotgETD = false;}
      if(mLqlyaIfkQ == true){mLqlyaIfkQ = false;}
      if(jktFTEXGkV == true){jktFTEXGkV = false;}
      if(bPcGYWJTDI == true){bPcGYWJTDI = false;}
      if(kIOCdauqaa == true){kIOCdauqaa = false;}
      if(rKssIwTTtk == true){rKssIwTTtk = false;}
      if(WZSxaWhkNb == true){WZSxaWhkNb = false;}
      if(RncbfbVras == true){RncbfbVras = false;}
      if(JffKcQVjyc == true){JffKcQVjyc = false;}
      if(CpYSlKpQaH == true){CpYSlKpQaH = false;}
      if(sKdzJDhRMf == true){sKdzJDhRMf = false;}
      if(ZbrBbptHUJ == true){ZbrBbptHUJ = false;}
      if(AxlkZaOJpU == true){AxlkZaOJpU = false;}
      if(lEQTAyCgBZ == true){lEQTAyCgBZ = false;}
      if(iEWRCZxXqu == true){iEWRCZxXqu = false;}
      if(QhwQGuXsZh == true){QhwQGuXsZh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZQIHCOMXPH
{ 
  void IJRhskrRYR()
  { 
      bool HdpBBipMmF = false;
      bool VrsDHaezUw = false;
      bool sXGjUdakFg = false;
      bool NQbbdipRba = false;
      bool rPGUMhYYIg = false;
      bool MSGDGiWGgX = false;
      bool IFGGrFQQZY = false;
      bool kNXtEcRlWl = false;
      bool EBcYTtKYVt = false;
      bool LikDRlJzbH = false;
      bool RHziuzuMyd = false;
      bool RkitSHbgmx = false;
      bool uqueNBbTbR = false;
      bool TRKPTxCscT = false;
      bool zyZrcZApkK = false;
      bool KbMdMZMTVt = false;
      bool WajfJAaTZV = false;
      bool EhDSyxRDBm = false;
      bool BliRHqEfCt = false;
      bool jhXixXNshc = false;
      string pqqfDFPNeo;
      string tykPSEYDbC;
      string tJgVDpQbzj;
      string UORsYIaEAU;
      string wqBxtsSJJW;
      string TQMiIfJVbN;
      string onOuTegqpJ;
      string dTCGGDIjbK;
      string WGRcQECijs;
      string zFbmfIcFcO;
      string MaSArzNFcF;
      string XZtRphVkeP;
      string cyGxKXqPax;
      string ZCHMxumRjQ;
      string pwGeUZLKwx;
      string mqaMlOUVoU;
      string IydeeURgTu;
      string uDBOYfrbbk;
      string MgSdKhbtai;
      string aRcPIrSazA;
      if(pqqfDFPNeo == MaSArzNFcF){HdpBBipMmF = true;}
      else if(MaSArzNFcF == pqqfDFPNeo){RHziuzuMyd = true;}
      if(tykPSEYDbC == XZtRphVkeP){VrsDHaezUw = true;}
      else if(XZtRphVkeP == tykPSEYDbC){RkitSHbgmx = true;}
      if(tJgVDpQbzj == cyGxKXqPax){sXGjUdakFg = true;}
      else if(cyGxKXqPax == tJgVDpQbzj){uqueNBbTbR = true;}
      if(UORsYIaEAU == ZCHMxumRjQ){NQbbdipRba = true;}
      else if(ZCHMxumRjQ == UORsYIaEAU){TRKPTxCscT = true;}
      if(wqBxtsSJJW == pwGeUZLKwx){rPGUMhYYIg = true;}
      else if(pwGeUZLKwx == wqBxtsSJJW){zyZrcZApkK = true;}
      if(TQMiIfJVbN == mqaMlOUVoU){MSGDGiWGgX = true;}
      else if(mqaMlOUVoU == TQMiIfJVbN){KbMdMZMTVt = true;}
      if(onOuTegqpJ == IydeeURgTu){IFGGrFQQZY = true;}
      else if(IydeeURgTu == onOuTegqpJ){WajfJAaTZV = true;}
      if(dTCGGDIjbK == uDBOYfrbbk){kNXtEcRlWl = true;}
      if(WGRcQECijs == MgSdKhbtai){EBcYTtKYVt = true;}
      if(zFbmfIcFcO == aRcPIrSazA){LikDRlJzbH = true;}
      while(uDBOYfrbbk == dTCGGDIjbK){EhDSyxRDBm = true;}
      while(MgSdKhbtai == MgSdKhbtai){BliRHqEfCt = true;}
      while(aRcPIrSazA == aRcPIrSazA){jhXixXNshc = true;}
      if(HdpBBipMmF == true){HdpBBipMmF = false;}
      if(VrsDHaezUw == true){VrsDHaezUw = false;}
      if(sXGjUdakFg == true){sXGjUdakFg = false;}
      if(NQbbdipRba == true){NQbbdipRba = false;}
      if(rPGUMhYYIg == true){rPGUMhYYIg = false;}
      if(MSGDGiWGgX == true){MSGDGiWGgX = false;}
      if(IFGGrFQQZY == true){IFGGrFQQZY = false;}
      if(kNXtEcRlWl == true){kNXtEcRlWl = false;}
      if(EBcYTtKYVt == true){EBcYTtKYVt = false;}
      if(LikDRlJzbH == true){LikDRlJzbH = false;}
      if(RHziuzuMyd == true){RHziuzuMyd = false;}
      if(RkitSHbgmx == true){RkitSHbgmx = false;}
      if(uqueNBbTbR == true){uqueNBbTbR = false;}
      if(TRKPTxCscT == true){TRKPTxCscT = false;}
      if(zyZrcZApkK == true){zyZrcZApkK = false;}
      if(KbMdMZMTVt == true){KbMdMZMTVt = false;}
      if(WajfJAaTZV == true){WajfJAaTZV = false;}
      if(EhDSyxRDBm == true){EhDSyxRDBm = false;}
      if(BliRHqEfCt == true){BliRHqEfCt = false;}
      if(jhXixXNshc == true){jhXixXNshc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SLYLQJJPOK
{ 
  void OjGoadCUFU()
  { 
      bool bGnBsXWYhQ = false;
      bool EPTKgppqDs = false;
      bool FZzcWKXpSA = false;
      bool FwyLONXjqc = false;
      bool SbArCwboYc = false;
      bool gZeoICGLdh = false;
      bool AgGhKIQHwT = false;
      bool RGzZacYHaa = false;
      bool hhRoSfQJDL = false;
      bool HMGIclVSgs = false;
      bool eUsFKaaFNe = false;
      bool cykCASOQOe = false;
      bool rGEjMFApxo = false;
      bool HGZgwNoLeq = false;
      bool EKwXiIaDIJ = false;
      bool WEDCBYQIsF = false;
      bool ajIXXWXDGl = false;
      bool cClXZgKfBD = false;
      bool dwhmSCCXeW = false;
      bool xgSZQUCXAL = false;
      string zscWEmTbsM;
      string QXBROdAPIr;
      string GFYXEKIQee;
      string pwNphEZQTb;
      string XWeCWLGamm;
      string WrrWdsUFRt;
      string eCwOWTJKjK;
      string DiugTjaVAr;
      string DgdqIxDqLn;
      string iUyZxVZPfD;
      string CuqbjmxLDt;
      string RyFZpxYEFY;
      string PSzwaikUjy;
      string KLpwpHpBHU;
      string ArnRVkOYjz;
      string wUJGniwtBB;
      string CbaFiGIIjh;
      string GXxkYWegap;
      string TMkjBpBiIG;
      string LwAGSXQihO;
      if(zscWEmTbsM == CuqbjmxLDt){bGnBsXWYhQ = true;}
      else if(CuqbjmxLDt == zscWEmTbsM){eUsFKaaFNe = true;}
      if(QXBROdAPIr == RyFZpxYEFY){EPTKgppqDs = true;}
      else if(RyFZpxYEFY == QXBROdAPIr){cykCASOQOe = true;}
      if(GFYXEKIQee == PSzwaikUjy){FZzcWKXpSA = true;}
      else if(PSzwaikUjy == GFYXEKIQee){rGEjMFApxo = true;}
      if(pwNphEZQTb == KLpwpHpBHU){FwyLONXjqc = true;}
      else if(KLpwpHpBHU == pwNphEZQTb){HGZgwNoLeq = true;}
      if(XWeCWLGamm == ArnRVkOYjz){SbArCwboYc = true;}
      else if(ArnRVkOYjz == XWeCWLGamm){EKwXiIaDIJ = true;}
      if(WrrWdsUFRt == wUJGniwtBB){gZeoICGLdh = true;}
      else if(wUJGniwtBB == WrrWdsUFRt){WEDCBYQIsF = true;}
      if(eCwOWTJKjK == CbaFiGIIjh){AgGhKIQHwT = true;}
      else if(CbaFiGIIjh == eCwOWTJKjK){ajIXXWXDGl = true;}
      if(DiugTjaVAr == GXxkYWegap){RGzZacYHaa = true;}
      if(DgdqIxDqLn == TMkjBpBiIG){hhRoSfQJDL = true;}
      if(iUyZxVZPfD == LwAGSXQihO){HMGIclVSgs = true;}
      while(GXxkYWegap == DiugTjaVAr){cClXZgKfBD = true;}
      while(TMkjBpBiIG == TMkjBpBiIG){dwhmSCCXeW = true;}
      while(LwAGSXQihO == LwAGSXQihO){xgSZQUCXAL = true;}
      if(bGnBsXWYhQ == true){bGnBsXWYhQ = false;}
      if(EPTKgppqDs == true){EPTKgppqDs = false;}
      if(FZzcWKXpSA == true){FZzcWKXpSA = false;}
      if(FwyLONXjqc == true){FwyLONXjqc = false;}
      if(SbArCwboYc == true){SbArCwboYc = false;}
      if(gZeoICGLdh == true){gZeoICGLdh = false;}
      if(AgGhKIQHwT == true){AgGhKIQHwT = false;}
      if(RGzZacYHaa == true){RGzZacYHaa = false;}
      if(hhRoSfQJDL == true){hhRoSfQJDL = false;}
      if(HMGIclVSgs == true){HMGIclVSgs = false;}
      if(eUsFKaaFNe == true){eUsFKaaFNe = false;}
      if(cykCASOQOe == true){cykCASOQOe = false;}
      if(rGEjMFApxo == true){rGEjMFApxo = false;}
      if(HGZgwNoLeq == true){HGZgwNoLeq = false;}
      if(EKwXiIaDIJ == true){EKwXiIaDIJ = false;}
      if(WEDCBYQIsF == true){WEDCBYQIsF = false;}
      if(ajIXXWXDGl == true){ajIXXWXDGl = false;}
      if(cClXZgKfBD == true){cClXZgKfBD = false;}
      if(dwhmSCCXeW == true){dwhmSCCXeW = false;}
      if(xgSZQUCXAL == true){xgSZQUCXAL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNJBTUDMHT
{ 
  void CstfILxoJC()
  { 
      bool pjNznqPKPk = false;
      bool wqEcihXiVb = false;
      bool sOSScxzSzn = false;
      bool QnpJsQIanP = false;
      bool PKqwoUNwaK = false;
      bool ArYyXaQuVp = false;
      bool qxLaTIBuiR = false;
      bool YwtFMhWWcI = false;
      bool jDqnmYOqkS = false;
      bool AMEyYRzQbf = false;
      bool SSMJkExTlp = false;
      bool DtRNGnFWmt = false;
      bool tKJQRLqwgt = false;
      bool hGtxoRphCi = false;
      bool auEuOFuqrj = false;
      bool MccglIIwqZ = false;
      bool MBlqIxzUYo = false;
      bool yXUDSzFOCL = false;
      bool QADwhFdMKg = false;
      bool IspcWZINlR = false;
      string jjIJikWAxb;
      string fGrnrwCyLZ;
      string pjdhdwpSNR;
      string IVXfQaSVkN;
      string cCVfQWUHZy;
      string aZqySzFZel;
      string uDleSJhMWQ;
      string dgNyxmNyQH;
      string bhsPqieZNR;
      string UsqyRZPpMH;
      string nHjIUtMrAe;
      string lHJXJNJWnj;
      string eIzFwkpOgW;
      string XXkJSUxktw;
      string WlYheMiSnE;
      string PrBccfIeLj;
      string ExLdHOWzFo;
      string PYcqNriQZi;
      string BWZcHeVHgl;
      string MSYKrYauaQ;
      if(jjIJikWAxb == nHjIUtMrAe){pjNznqPKPk = true;}
      else if(nHjIUtMrAe == jjIJikWAxb){SSMJkExTlp = true;}
      if(fGrnrwCyLZ == lHJXJNJWnj){wqEcihXiVb = true;}
      else if(lHJXJNJWnj == fGrnrwCyLZ){DtRNGnFWmt = true;}
      if(pjdhdwpSNR == eIzFwkpOgW){sOSScxzSzn = true;}
      else if(eIzFwkpOgW == pjdhdwpSNR){tKJQRLqwgt = true;}
      if(IVXfQaSVkN == XXkJSUxktw){QnpJsQIanP = true;}
      else if(XXkJSUxktw == IVXfQaSVkN){hGtxoRphCi = true;}
      if(cCVfQWUHZy == WlYheMiSnE){PKqwoUNwaK = true;}
      else if(WlYheMiSnE == cCVfQWUHZy){auEuOFuqrj = true;}
      if(aZqySzFZel == PrBccfIeLj){ArYyXaQuVp = true;}
      else if(PrBccfIeLj == aZqySzFZel){MccglIIwqZ = true;}
      if(uDleSJhMWQ == ExLdHOWzFo){qxLaTIBuiR = true;}
      else if(ExLdHOWzFo == uDleSJhMWQ){MBlqIxzUYo = true;}
      if(dgNyxmNyQH == PYcqNriQZi){YwtFMhWWcI = true;}
      if(bhsPqieZNR == BWZcHeVHgl){jDqnmYOqkS = true;}
      if(UsqyRZPpMH == MSYKrYauaQ){AMEyYRzQbf = true;}
      while(PYcqNriQZi == dgNyxmNyQH){yXUDSzFOCL = true;}
      while(BWZcHeVHgl == BWZcHeVHgl){QADwhFdMKg = true;}
      while(MSYKrYauaQ == MSYKrYauaQ){IspcWZINlR = true;}
      if(pjNznqPKPk == true){pjNznqPKPk = false;}
      if(wqEcihXiVb == true){wqEcihXiVb = false;}
      if(sOSScxzSzn == true){sOSScxzSzn = false;}
      if(QnpJsQIanP == true){QnpJsQIanP = false;}
      if(PKqwoUNwaK == true){PKqwoUNwaK = false;}
      if(ArYyXaQuVp == true){ArYyXaQuVp = false;}
      if(qxLaTIBuiR == true){qxLaTIBuiR = false;}
      if(YwtFMhWWcI == true){YwtFMhWWcI = false;}
      if(jDqnmYOqkS == true){jDqnmYOqkS = false;}
      if(AMEyYRzQbf == true){AMEyYRzQbf = false;}
      if(SSMJkExTlp == true){SSMJkExTlp = false;}
      if(DtRNGnFWmt == true){DtRNGnFWmt = false;}
      if(tKJQRLqwgt == true){tKJQRLqwgt = false;}
      if(hGtxoRphCi == true){hGtxoRphCi = false;}
      if(auEuOFuqrj == true){auEuOFuqrj = false;}
      if(MccglIIwqZ == true){MccglIIwqZ = false;}
      if(MBlqIxzUYo == true){MBlqIxzUYo = false;}
      if(yXUDSzFOCL == true){yXUDSzFOCL = false;}
      if(QADwhFdMKg == true){QADwhFdMKg = false;}
      if(IspcWZINlR == true){IspcWZINlR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZYDMOOGWA
{ 
  void iddLiThoPR()
  { 
      bool YdPCpAAcPT = false;
      bool ixrxtPGRUy = false;
      bool fEntYqQnqx = false;
      bool dMdyjPbLSZ = false;
      bool WfoYefibBo = false;
      bool qMymRUoVcy = false;
      bool jLkRoWTtNe = false;
      bool nuztbAPOOs = false;
      bool InmCGRNpgP = false;
      bool ZFhUpKtXiI = false;
      bool LoOWBuMDLR = false;
      bool EaGjpuYiKX = false;
      bool IdMxFhMeEQ = false;
      bool FqfGgSYPBL = false;
      bool EKdOKyyyet = false;
      bool lLMLzhbQRS = false;
      bool hhzuLMuACW = false;
      bool WIhzSyzxmG = false;
      bool iNAJeteTHy = false;
      bool qHyhcWLiDx = false;
      string oAqLXxnnjb;
      string UEbEYFYamE;
      string PxkWfIShqo;
      string HFcYFXjtLZ;
      string VCdtHnkZAO;
      string DBGxprPTfP;
      string eGxtTObDyA;
      string VeONiNSpPq;
      string WsgckFzeiN;
      string IPNwuPFiZr;
      string MgazsYmsOc;
      string YZEnrkYUJO;
      string OwUkrFQRRS;
      string HiPWeoRhjM;
      string SFPFniLZEJ;
      string qkZLcPMpHm;
      string HUawUpJhJC;
      string TqkwwJfOxJ;
      string sqNIaWJEsO;
      string cbZwEyeTky;
      if(oAqLXxnnjb == MgazsYmsOc){YdPCpAAcPT = true;}
      else if(MgazsYmsOc == oAqLXxnnjb){LoOWBuMDLR = true;}
      if(UEbEYFYamE == YZEnrkYUJO){ixrxtPGRUy = true;}
      else if(YZEnrkYUJO == UEbEYFYamE){EaGjpuYiKX = true;}
      if(PxkWfIShqo == OwUkrFQRRS){fEntYqQnqx = true;}
      else if(OwUkrFQRRS == PxkWfIShqo){IdMxFhMeEQ = true;}
      if(HFcYFXjtLZ == HiPWeoRhjM){dMdyjPbLSZ = true;}
      else if(HiPWeoRhjM == HFcYFXjtLZ){FqfGgSYPBL = true;}
      if(VCdtHnkZAO == SFPFniLZEJ){WfoYefibBo = true;}
      else if(SFPFniLZEJ == VCdtHnkZAO){EKdOKyyyet = true;}
      if(DBGxprPTfP == qkZLcPMpHm){qMymRUoVcy = true;}
      else if(qkZLcPMpHm == DBGxprPTfP){lLMLzhbQRS = true;}
      if(eGxtTObDyA == HUawUpJhJC){jLkRoWTtNe = true;}
      else if(HUawUpJhJC == eGxtTObDyA){hhzuLMuACW = true;}
      if(VeONiNSpPq == TqkwwJfOxJ){nuztbAPOOs = true;}
      if(WsgckFzeiN == sqNIaWJEsO){InmCGRNpgP = true;}
      if(IPNwuPFiZr == cbZwEyeTky){ZFhUpKtXiI = true;}
      while(TqkwwJfOxJ == VeONiNSpPq){WIhzSyzxmG = true;}
      while(sqNIaWJEsO == sqNIaWJEsO){iNAJeteTHy = true;}
      while(cbZwEyeTky == cbZwEyeTky){qHyhcWLiDx = true;}
      if(YdPCpAAcPT == true){YdPCpAAcPT = false;}
      if(ixrxtPGRUy == true){ixrxtPGRUy = false;}
      if(fEntYqQnqx == true){fEntYqQnqx = false;}
      if(dMdyjPbLSZ == true){dMdyjPbLSZ = false;}
      if(WfoYefibBo == true){WfoYefibBo = false;}
      if(qMymRUoVcy == true){qMymRUoVcy = false;}
      if(jLkRoWTtNe == true){jLkRoWTtNe = false;}
      if(nuztbAPOOs == true){nuztbAPOOs = false;}
      if(InmCGRNpgP == true){InmCGRNpgP = false;}
      if(ZFhUpKtXiI == true){ZFhUpKtXiI = false;}
      if(LoOWBuMDLR == true){LoOWBuMDLR = false;}
      if(EaGjpuYiKX == true){EaGjpuYiKX = false;}
      if(IdMxFhMeEQ == true){IdMxFhMeEQ = false;}
      if(FqfGgSYPBL == true){FqfGgSYPBL = false;}
      if(EKdOKyyyet == true){EKdOKyyyet = false;}
      if(lLMLzhbQRS == true){lLMLzhbQRS = false;}
      if(hhzuLMuACW == true){hhzuLMuACW = false;}
      if(WIhzSyzxmG == true){WIhzSyzxmG = false;}
      if(iNAJeteTHy == true){iNAJeteTHy = false;}
      if(qHyhcWLiDx == true){qHyhcWLiDx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTHEPDZHCX
{ 
  void ESdEggtmkK()
  { 
      bool xFjtDjObGd = false;
      bool WipWSqXsoL = false;
      bool XVWTBRpALu = false;
      bool clOauEytNh = false;
      bool nOJroGDRoy = false;
      bool HZOcsbiPrl = false;
      bool sNQKBjTPaO = false;
      bool sceHWILdeu = false;
      bool OXLMnDWlgT = false;
      bool UhBbnayzqE = false;
      bool mnqaEetGFk = false;
      bool QEjxWUCDWx = false;
      bool MghHsKaCTw = false;
      bool KLmZIZgkHI = false;
      bool IPgwCQyEES = false;
      bool YubsqFFigt = false;
      bool DrmIZEQKox = false;
      bool nQuNowAlEc = false;
      bool MWxAWOjshC = false;
      bool UyDNFQcXVy = false;
      string LVjPrkQfjk;
      string sXWurgtPBO;
      string eNpuOHTiMf;
      string qwUYKyfYmS;
      string glysxVonln;
      string sNZUhxfoAj;
      string RgSEtwDxjt;
      string BVbhgsOwxs;
      string SewYmcVAqN;
      string SqXCBAStyA;
      string RqEqmXkrno;
      string hiqHRljtQR;
      string ZDFWbJyZgg;
      string ZTxxaaaEkP;
      string qdLCeizQkO;
      string PXdgZOlgPc;
      string YLLGONltfp;
      string LfJBawqDqr;
      string JhnRRCpQWM;
      string osoIpeSEnQ;
      if(LVjPrkQfjk == RqEqmXkrno){xFjtDjObGd = true;}
      else if(RqEqmXkrno == LVjPrkQfjk){mnqaEetGFk = true;}
      if(sXWurgtPBO == hiqHRljtQR){WipWSqXsoL = true;}
      else if(hiqHRljtQR == sXWurgtPBO){QEjxWUCDWx = true;}
      if(eNpuOHTiMf == ZDFWbJyZgg){XVWTBRpALu = true;}
      else if(ZDFWbJyZgg == eNpuOHTiMf){MghHsKaCTw = true;}
      if(qwUYKyfYmS == ZTxxaaaEkP){clOauEytNh = true;}
      else if(ZTxxaaaEkP == qwUYKyfYmS){KLmZIZgkHI = true;}
      if(glysxVonln == qdLCeizQkO){nOJroGDRoy = true;}
      else if(qdLCeizQkO == glysxVonln){IPgwCQyEES = true;}
      if(sNZUhxfoAj == PXdgZOlgPc){HZOcsbiPrl = true;}
      else if(PXdgZOlgPc == sNZUhxfoAj){YubsqFFigt = true;}
      if(RgSEtwDxjt == YLLGONltfp){sNQKBjTPaO = true;}
      else if(YLLGONltfp == RgSEtwDxjt){DrmIZEQKox = true;}
      if(BVbhgsOwxs == LfJBawqDqr){sceHWILdeu = true;}
      if(SewYmcVAqN == JhnRRCpQWM){OXLMnDWlgT = true;}
      if(SqXCBAStyA == osoIpeSEnQ){UhBbnayzqE = true;}
      while(LfJBawqDqr == BVbhgsOwxs){nQuNowAlEc = true;}
      while(JhnRRCpQWM == JhnRRCpQWM){MWxAWOjshC = true;}
      while(osoIpeSEnQ == osoIpeSEnQ){UyDNFQcXVy = true;}
      if(xFjtDjObGd == true){xFjtDjObGd = false;}
      if(WipWSqXsoL == true){WipWSqXsoL = false;}
      if(XVWTBRpALu == true){XVWTBRpALu = false;}
      if(clOauEytNh == true){clOauEytNh = false;}
      if(nOJroGDRoy == true){nOJroGDRoy = false;}
      if(HZOcsbiPrl == true){HZOcsbiPrl = false;}
      if(sNQKBjTPaO == true){sNQKBjTPaO = false;}
      if(sceHWILdeu == true){sceHWILdeu = false;}
      if(OXLMnDWlgT == true){OXLMnDWlgT = false;}
      if(UhBbnayzqE == true){UhBbnayzqE = false;}
      if(mnqaEetGFk == true){mnqaEetGFk = false;}
      if(QEjxWUCDWx == true){QEjxWUCDWx = false;}
      if(MghHsKaCTw == true){MghHsKaCTw = false;}
      if(KLmZIZgkHI == true){KLmZIZgkHI = false;}
      if(IPgwCQyEES == true){IPgwCQyEES = false;}
      if(YubsqFFigt == true){YubsqFFigt = false;}
      if(DrmIZEQKox == true){DrmIZEQKox = false;}
      if(nQuNowAlEc == true){nQuNowAlEc = false;}
      if(MWxAWOjshC == true){MWxAWOjshC = false;}
      if(UyDNFQcXVy == true){UyDNFQcXVy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LITCJBYZFP
{ 
  void xkCreVuhVf()
  { 
      bool CNBLGkJdGW = false;
      bool PdUDLmATrw = false;
      bool eUECqHnSWP = false;
      bool LPVlsycUCM = false;
      bool KnEEsPOTZL = false;
      bool CqJXHhJyTy = false;
      bool xqHpKAIiKM = false;
      bool JfRflqPzJb = false;
      bool rTsKNUFxeK = false;
      bool ndADOSgNts = false;
      bool HfIMBWYdlP = false;
      bool RKoqFcywco = false;
      bool tKEzYfeNQS = false;
      bool JCEQUMKfJq = false;
      bool uaLOsdoJyl = false;
      bool UkjEywaJnV = false;
      bool qKNTFPFYWs = false;
      bool SRmlsTzoGu = false;
      bool pVPexYRzSX = false;
      bool kBrmzkNqIc = false;
      string cVkCWttUGb;
      string RiFgJTIczw;
      string oGpLQPrISs;
      string djttWfSBDW;
      string SeAalhGLHe;
      string RiLPJVfYkH;
      string CkCNyhoLJd;
      string AHYbcKFOYi;
      string IfBnatXejA;
      string ztPwUhbmcE;
      string ruCcdJKjlz;
      string QRACzVjNlD;
      string KKaIdGrcHu;
      string hSkUpNdXJQ;
      string jmrkjhsNxy;
      string xNAZshTszX;
      string RgcpQxfeLk;
      string rMEVSWRpXu;
      string MefIxTSLaI;
      string sjXkyDKCUl;
      if(cVkCWttUGb == ruCcdJKjlz){CNBLGkJdGW = true;}
      else if(ruCcdJKjlz == cVkCWttUGb){HfIMBWYdlP = true;}
      if(RiFgJTIczw == QRACzVjNlD){PdUDLmATrw = true;}
      else if(QRACzVjNlD == RiFgJTIczw){RKoqFcywco = true;}
      if(oGpLQPrISs == KKaIdGrcHu){eUECqHnSWP = true;}
      else if(KKaIdGrcHu == oGpLQPrISs){tKEzYfeNQS = true;}
      if(djttWfSBDW == hSkUpNdXJQ){LPVlsycUCM = true;}
      else if(hSkUpNdXJQ == djttWfSBDW){JCEQUMKfJq = true;}
      if(SeAalhGLHe == jmrkjhsNxy){KnEEsPOTZL = true;}
      else if(jmrkjhsNxy == SeAalhGLHe){uaLOsdoJyl = true;}
      if(RiLPJVfYkH == xNAZshTszX){CqJXHhJyTy = true;}
      else if(xNAZshTszX == RiLPJVfYkH){UkjEywaJnV = true;}
      if(CkCNyhoLJd == RgcpQxfeLk){xqHpKAIiKM = true;}
      else if(RgcpQxfeLk == CkCNyhoLJd){qKNTFPFYWs = true;}
      if(AHYbcKFOYi == rMEVSWRpXu){JfRflqPzJb = true;}
      if(IfBnatXejA == MefIxTSLaI){rTsKNUFxeK = true;}
      if(ztPwUhbmcE == sjXkyDKCUl){ndADOSgNts = true;}
      while(rMEVSWRpXu == AHYbcKFOYi){SRmlsTzoGu = true;}
      while(MefIxTSLaI == MefIxTSLaI){pVPexYRzSX = true;}
      while(sjXkyDKCUl == sjXkyDKCUl){kBrmzkNqIc = true;}
      if(CNBLGkJdGW == true){CNBLGkJdGW = false;}
      if(PdUDLmATrw == true){PdUDLmATrw = false;}
      if(eUECqHnSWP == true){eUECqHnSWP = false;}
      if(LPVlsycUCM == true){LPVlsycUCM = false;}
      if(KnEEsPOTZL == true){KnEEsPOTZL = false;}
      if(CqJXHhJyTy == true){CqJXHhJyTy = false;}
      if(xqHpKAIiKM == true){xqHpKAIiKM = false;}
      if(JfRflqPzJb == true){JfRflqPzJb = false;}
      if(rTsKNUFxeK == true){rTsKNUFxeK = false;}
      if(ndADOSgNts == true){ndADOSgNts = false;}
      if(HfIMBWYdlP == true){HfIMBWYdlP = false;}
      if(RKoqFcywco == true){RKoqFcywco = false;}
      if(tKEzYfeNQS == true){tKEzYfeNQS = false;}
      if(JCEQUMKfJq == true){JCEQUMKfJq = false;}
      if(uaLOsdoJyl == true){uaLOsdoJyl = false;}
      if(UkjEywaJnV == true){UkjEywaJnV = false;}
      if(qKNTFPFYWs == true){qKNTFPFYWs = false;}
      if(SRmlsTzoGu == true){SRmlsTzoGu = false;}
      if(pVPexYRzSX == true){pVPexYRzSX = false;}
      if(kBrmzkNqIc == true){kBrmzkNqIc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DBWSSHENHL
{ 
  void zwpbaSZILO()
  { 
      bool DKrJHPWzMU = false;
      bool zDKbazgdSE = false;
      bool xgIogZqlCF = false;
      bool YYPKGckLUo = false;
      bool zMiVdqcUII = false;
      bool SautYVBDch = false;
      bool XkxHuZmAVy = false;
      bool NVJdFjylKo = false;
      bool xVctlycUlj = false;
      bool ahhmRNPbaE = false;
      bool DbzKtxRRoo = false;
      bool XPrmkBIDUw = false;
      bool wROkWemVMq = false;
      bool TWKGkUWRzn = false;
      bool gLfwMLpuBP = false;
      bool FMGeHkNOnP = false;
      bool KuFxVBElBQ = false;
      bool epDfPklRXL = false;
      bool nqUxlHPfyz = false;
      bool GHdidkFhZL = false;
      string kMzRuCxBEZ;
      string qsryRPCWIH;
      string achdyiVITH;
      string FitlVCTQmu;
      string SwBtyPNhtH;
      string EsRXVIeUTL;
      string gngxUHzFbP;
      string uliMneamfh;
      string VmOLCMQWQN;
      string XywbOdOEZp;
      string QHGdLSJEip;
      string gqokpsZVtH;
      string qboNqxoHxK;
      string PWNpRNfjzj;
      string CMnZfgJLlU;
      string EsJRznSrmO;
      string cCGYaJczSb;
      string NoVJFenOgK;
      string mdVcFVMupd;
      string unxjHAFOzV;
      if(kMzRuCxBEZ == QHGdLSJEip){DKrJHPWzMU = true;}
      else if(QHGdLSJEip == kMzRuCxBEZ){DbzKtxRRoo = true;}
      if(qsryRPCWIH == gqokpsZVtH){zDKbazgdSE = true;}
      else if(gqokpsZVtH == qsryRPCWIH){XPrmkBIDUw = true;}
      if(achdyiVITH == qboNqxoHxK){xgIogZqlCF = true;}
      else if(qboNqxoHxK == achdyiVITH){wROkWemVMq = true;}
      if(FitlVCTQmu == PWNpRNfjzj){YYPKGckLUo = true;}
      else if(PWNpRNfjzj == FitlVCTQmu){TWKGkUWRzn = true;}
      if(SwBtyPNhtH == CMnZfgJLlU){zMiVdqcUII = true;}
      else if(CMnZfgJLlU == SwBtyPNhtH){gLfwMLpuBP = true;}
      if(EsRXVIeUTL == EsJRznSrmO){SautYVBDch = true;}
      else if(EsJRznSrmO == EsRXVIeUTL){FMGeHkNOnP = true;}
      if(gngxUHzFbP == cCGYaJczSb){XkxHuZmAVy = true;}
      else if(cCGYaJczSb == gngxUHzFbP){KuFxVBElBQ = true;}
      if(uliMneamfh == NoVJFenOgK){NVJdFjylKo = true;}
      if(VmOLCMQWQN == mdVcFVMupd){xVctlycUlj = true;}
      if(XywbOdOEZp == unxjHAFOzV){ahhmRNPbaE = true;}
      while(NoVJFenOgK == uliMneamfh){epDfPklRXL = true;}
      while(mdVcFVMupd == mdVcFVMupd){nqUxlHPfyz = true;}
      while(unxjHAFOzV == unxjHAFOzV){GHdidkFhZL = true;}
      if(DKrJHPWzMU == true){DKrJHPWzMU = false;}
      if(zDKbazgdSE == true){zDKbazgdSE = false;}
      if(xgIogZqlCF == true){xgIogZqlCF = false;}
      if(YYPKGckLUo == true){YYPKGckLUo = false;}
      if(zMiVdqcUII == true){zMiVdqcUII = false;}
      if(SautYVBDch == true){SautYVBDch = false;}
      if(XkxHuZmAVy == true){XkxHuZmAVy = false;}
      if(NVJdFjylKo == true){NVJdFjylKo = false;}
      if(xVctlycUlj == true){xVctlycUlj = false;}
      if(ahhmRNPbaE == true){ahhmRNPbaE = false;}
      if(DbzKtxRRoo == true){DbzKtxRRoo = false;}
      if(XPrmkBIDUw == true){XPrmkBIDUw = false;}
      if(wROkWemVMq == true){wROkWemVMq = false;}
      if(TWKGkUWRzn == true){TWKGkUWRzn = false;}
      if(gLfwMLpuBP == true){gLfwMLpuBP = false;}
      if(FMGeHkNOnP == true){FMGeHkNOnP = false;}
      if(KuFxVBElBQ == true){KuFxVBElBQ = false;}
      if(epDfPklRXL == true){epDfPklRXL = false;}
      if(nqUxlHPfyz == true){nqUxlHPfyz = false;}
      if(GHdidkFhZL == true){GHdidkFhZL = false;}
    } 
}; 
