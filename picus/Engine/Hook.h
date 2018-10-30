#pragma once

#include "Engine.h"
using FrameStageNotify = void(__thiscall*)(IBaseClientDLL*, ClientFrameStage_t);
using CreateMove = void(__thiscall *)(IClientMode*, float flInputSampleTime, CUserCmd* pCmd);
using GameEvent = bool(__thiscall*)(void*, IGameEvent*);
using ResetHook = void(__thiscall *)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
using GetFov = void(__thiscall *)(CViewSetup*);
using PlaySound = void(__thiscall *)(ISurface*, const char*);
typedef float(__thiscall* xdxdxd)();
typedef void(__thiscall* LockCursor)(void*);
using ModelRender = void(__thiscall *)(IVModelRender* fix, IMatRenderContext* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
using EmitsoundXD = void(__stdcall*)(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample,
	float flVolume, soundlevel_t iSoundlevel, int nSeed, int iFlags, int iPitch,
	const Vector *pOrigin, const Vector *pDirection, CUtlVector< Vector >* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, int test);namespace Engine
{
	namespace Hook
	{
		bool Initialize();
		void Shutdown();
	}
}