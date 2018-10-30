
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
//																																				//
//																																				//
//  Credits for the Fix to Azu / Shonax. Subscribe him on youtube -> https://www.youtube.com/c/AzuShonax  discord: https://discord.gg/NhcwwxN	//
//																																				//
//																																			    //
//																																			    //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// I Disabled all Detected Hooks. You can Include them Back with removeing the "//" Infront of the Functions you want to have. But keep in mind that it's detected then.





#include "Hook.h"
#include "intrin.h"
//[enc_string_enable /]
//[junk_enable /]

namespace Engine
{
	namespace Hook
	{


		// THIS ARE VMTABLE (VMT DETECTED)! RANKCHANGER / LEGIT AA AND MORE!   YOU CAN INCLUDE IT BACK IF YOU NEED IT (REMOVE THOSE "/*  * /" SLASHES) BUT THEN YOU RISK A VAC BAN!
		/*
		CSX::Hook::VTable ClientModeTable;						
		CSX::Hook::VTable IDirect3DDevice9Table;
		CSX::Hook::VTable SoundTable;
		CSX::Hook::VTable GameEventTable;
		CSX::Hook::VTable ModelRenderTable;
		CSX::Hook::VTable ClientTable;
		CSX::Hook::VTable SurfaceTable;
		CSX::Hook::VTable EngineTable;
		CSX::Hook::VTable SteamGameCoordinatorTable;
		*/

		vfunc_hook panel;
		vfunc_hook client;
		vfunc_hook clientmode;
		vfunc_hook modelrender;
		vfunc_hook sound;
		vfunc_hook surface;
		vfunc_hook eventmanager;
		vfunc_hook device;
		IDirect3DDevice9* g_pDevice = nullptr;



		typedef HRESULT(WINAPI* Present_t)(IDirect3DDevice9* pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
		Present_t Present_o;

		typedef HRESULT(WINAPI* Reset_t)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
		Reset_t Reset_o;

		HRESULT WINAPI Hook_Present(IDirect3DDevice9* pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
		{
			Client::OnRender();

			return Present_o(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
		}
		
		
		
		

		// legit aa clamped angle stuff
		
	
		void VectorAngles(Vector forward, QAngle & ang_out)
		{
			if (forward.x == 0.0f && forward.y == 0.0f)
			{
				ang_out.x = (forward.z <= 0.0f) ? 90.0f : 270.f;
				ang_out.y = 0.0f;
			}
			else
			{
				ang_out.x = atan2(-forward.z, forward.Length2D()) * -180 / 3.14;
				ang_out.y = atan2(forward.y, forward.x) * 180 / 3.14;
			}

			ang_out.z = 0.0f;
		}

		void FixMovement(CUserCmd * pCommand, Vector ang)
		{
			float flSpeed = pCommand->Move.Length2D();

			if (flSpeed <= 0.0f)
				return;

			Vector vec_move;

			VectorAngles(pCommand->Move, vec_move);

			float flYaw = (pCommand->viewangles.y - ang.y + vec_move.y) *  0.0174532925f;

			pCommand->Move.x = cos(flYaw) * flSpeed;
			pCommand->Move.y = sin(flYaw) * flSpeed;
		}

		void NormalizeFloat(float & in)
		{
			if (in > 180.f || in < -180.f)
			{
				float ry = in / 360.f;

				if (ry < 0.f)
					ry = -ry;

				ry = round(ry);

				if (in < 0.f)
					in = (in + 360.f * ry);
				else
					in = (in - 360.f * ry);
			}
		}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// BELOW IS VMT DETECTED STUFF! YOU CAN INCLUDE IT BACK IF YOU NEED IT BUT THEN YOU'LL RISK A VAC BAN!/////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		

	/*		// THIS IF FOR ALLWAYS INVENTORY!
	
	bool WINAPI Hook_IsConnected()										
		{

			static void* unk = CSX::Memory::NewPatternScan(GetModuleHandleA("client_panorama.dll"), "75 04 B0 01 5F") - 2;
			if (_ReturnAddress() == unk && Settings::Misc::invalwayson)
			{
				return false;
			}
			EngineTable.UnHook();
			bool ret = Interfaces::Engine()->IsConnected();
			EngineTable.ReHook();
			return ret;
		}

	*/
		


	
	/*	// THIS IS FOR RANKCHANGER ETC

	EGCResults __fastcall Hook_RetrieveMessage(void* ecx, void* edx, uint32_t *punMsgType, void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize)
		{
			SteamGameCoordinatorTable.UnHook();
			EGCResults status = Interfaces::SteamGameCoordinator()->RetrieveMessage(punMsgType, pubDest, cubDest, pcubMsgSize);
			SteamGameCoordinatorTable.ReHook();

			if (status != k_EGCResultOK)
				return status;

			Client::OnRetrieveMessage(ecx, edx, punMsgType, pubDest, cubDest, pcubMsgSize);

			return status;
		}

		EGCResults __fastcall Hook_SendMessage(void* ecx, void* edx, uint32_t unMsgType, const void* pubData, uint32_t cubData)
		{
			uint32_t messageType = unMsgType & 0x7FFFFFFF;
			void* pubDataMutable = const_cast<void*>(pubData);


			Client::OnSendMessage(ecx, edx, unMsgType, pubData, cubData);

			SteamGameCoordinatorTable.UnHook();
			EGCResults status = Interfaces::SteamGameCoordinator()->SendMessage(unMsgType, pubData, cubData);
			SteamGameCoordinatorTable.ReHook();

			return status;



		bool SendClientHello()
		{
			CMsgClientHello Message;

			Message.set_client_session_need(1);
			Message.clear_socache_have_versions();

			void* ptr = malloc(Message.ByteSize() + 8);

			if (!ptr)
				return false;

			((uint32_t*)ptr)[0] = k_EMsgGCClientHello | ((DWORD)1 << 31);
			((uint32_t*)ptr)[1] = 0;

			Message.SerializeToArray((void*)((DWORD)ptr + 8), Message.ByteSize());

			bool result = Interfaces::SteamGameCoordinator()->SendMessage(k_EMsgGCClientHello | ((DWORD)1 << 31), ptr, Message.ByteSize() + 8) == k_EGCResultOK;

			free(ptr);

			return result;
		}

		
		
		}*/
		
		
		
		
		
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
//////////////////////////////////////// BELOW ARE VMT UNDETECTED HOOKS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		void __stdcall Hook_Reset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
		{
			static auto ofunc = device.get_original<ResetHook>(D3D9::TABLE::Reset);
			ofunc(pDevice, pPresentationParameters);
			Client::OnLostDevice();
			HRESULT hRes = Reset_o(pDevice, pPresentationParameters);
			Client::OnResetDevice();
		}

		
		void __stdcall Hook_CreateMove(float flInputSampleTime, CUserCmd* pCmd)
		{
			static auto ofunc = clientmode.get_original<CreateMove>(TABLE::IClientMode::CreateMove);
			ofunc(Interfaces::ClientMode(), flInputSampleTime, pCmd);
			Client::OnCreateMove(pCmd);
		}


		
		void __fastcall Hook_OverrideView(CViewSetup* pSetup)
		{
			static auto ofunc = clientmode.get_original<GetFov>(TABLE::IClientMode::OverrideView);
			Client::OnOverrideView(pSetup);
			ofunc(pSetup);
		}
		float __stdcall Hook_GetViewModelFOV()
		{
			// not needed
			return 0;
		}

		bool __fastcall Hook_FireEventClientSideThink(void* ecx, void* edx, IGameEvent* pEvent)
		{
			static auto ofunc = eventmanager.get_original<GameEvent>(TABLE::IGameEventManager2::FireEventClientSide);
			if (!pEvent)
				return ofunc(ecx, pEvent);
			Client::OnFireEventClientSideThink(pEvent);
			return ofunc(ecx, pEvent);
		}

		void __stdcall Hook_FrameStageNotify(ClientFrameStage_t stage)
		{
			static auto ofunc = client.get_original<FrameStageNotify>(TABLE::IBaseClientDLL::FrameStageNotify);
			ofunc(Interfaces::Client(), stage);
			Skin_OnFrameStageNotify(stage);
			Gloves_OnFrameStageNotify(stage);
		}



		void __stdcall Hook_EmitSound(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample,
			float flVolume, soundlevel_t iSoundlevel, int nSeed, int iFlags = 0, int iPitch = PITCH_NORM,
			const Vector *pOrigin = NULL, const Vector *pDirection = NULL, CUtlVector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1, int test = 0)
		{
			auto oEmitsound = sound.get_original<EmitsoundXD>(TABLE::IEngineSound::EmitSound1);
			if (pSample && Client::g_pPlayers->GetPlayer(iEntIndex)->Team != Client::g_pPlayers->GetLocal()->Team)
			{
				Client::OnPlaySound(pOrigin, pSample);
			}
			return oEmitsound(filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample,
				flVolume, iSoundlevel, nSeed, iFlags, iPitch,
				pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity, 0);


		}
		void __stdcall Hook_EmitSound2(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample,
			float flVolume, soundlevel_t iSoundlevel, int nSeed, int iFlags = 0, int iPitch = PITCH_NORM,
			const Vector *pOrigin = NULL, const Vector *pDirection = NULL, CUtlVector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1, int test = 0)
		{
			auto oEmitsound = sound.get_original<EmitsoundXD>(TABLE::IEngineSound::EmitSound2);
			if (pSample && Client::g_pPlayers->GetPlayer(iEntIndex)->Team != Client::g_pPlayers->GetLocal()->Team)
			{
				Client::OnPlaySound(pOrigin, pSample);
			}
			return oEmitsound(filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample,
				flVolume, iSoundlevel, nSeed, iFlags, iPitch,
				pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity, 0);


		}

		void __fastcall Hook_DrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
		{
		
			// I don't need chams
		}

		void __stdcall Hook_PlaySound(const char* pszSoundName)
		{
			static auto ofunc = surface.get_original<PlaySound>(TABLE::ISurface::PlaySound);
			ofunc(Interfaces::Surface(), pszSoundName);
			if (pszSoundName)
				Client::OnPlaySound(pszSoundName);
		}
		
		
		
		
		
		bool Initialize()
		{
			if (!CSX::Utils::IsModuleLoad(D3D9_DLL))
				return false;

			if (!CSX::Utils::IsModuleLoad(SHADERPIDX9_DLL))
				return false;

			if (!CSX::Utils::IsModuleLoad(GAMEOVERLAYRENDERER_DLL))
				return false;

			DWORD d3d9TablePtrPtr = CSX::Memory::FindPattern(SHADERPIDX9_DLL, D3D9_PATTERN, D3D9_MASK, 1);
			DWORD_PTR** dwPresent_o = (DWORD_PTR**)CSX::Memory::FindPattern(GAMEOVERLAYRENDERER_DLL, GMOR_PATTERN, GMOR_MASK, 1);

			if (d3d9TablePtrPtr && dwPresent_o)
			{
				g_pDevice = (IDirect3DDevice9*)(**(PDWORD*)d3d9TablePtrPtr);

				if (device.setup(g_pDevice))
				{
					
					DWORD_PTR* dwAddress = *dwPresent_o;
					Present_o = (Present_t)(*dwAddress);
					*dwAddress = (DWORD_PTR)(&Hook_Present);

					device.hook_index(D3D9::TABLE::Reset, Hook_Reset);


					

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*					OLD DETECTED HOOKS! YOU CAN INCLUDE THEM BACK IF YOU NEED FEATURES LIKE LEGIT AA OR SKINCHANGER! YOU CAN GET VAC BANNED BCS OF VMTABLE IF YOU INCLUDE THIS BACK!				
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				

					Reset_o = (Reset_t)IDirect3DDevice9Table.GetHookIndex(D3D9::TABLE::Reset, Hook_Reset);
					
					
					if (!ClientModeTable.InitTable(Interfaces::ClientMode()))			
						return false;

					ClientModeTable.HookIndex(TABLE::IClientMode::CreateMove, Hook_CreateMove);
					ClientModeTable.HookIndex(TABLE::IClientMode::OverrideView, Hook_OverrideView);
					ClientModeTable.HookIndex(TABLE::IClientMode::GetViewModelFOV, Hook_GetViewModelFOV);

					if (!SteamGameCoordinatorTable.InitTable(Interfaces::SteamGameCoordinator()))
					return false;

					SteamGameCoordinatorTable.HookIndex(0, Hook_SendMessage);
					SteamGameCoordinatorTable.HookIndex(2, Hook_RetrieveMessage);

					if (!GameEventTable.InitTable(Interfaces::GameEvent()))
					return false;

					GameEventTable.HookIndex(TABLE::IGameEventManager2::FireEventClientSide, Hook_FireEventClientSideThink);

					if (!ClientTable.InitTable(Interfaces::Client()))
					return false;

					ClientTable.HookIndex(TABLE::IBaseClientDLL::FrameStageNotify, Hook_FrameStageNotify);

					if (!SoundTable.InitTable(Interfaces::Sound()))
					return false;

					SoundTable.HookIndex(TABLE::IEngineSound::EmitSound1, Hook_EmitSound1);
					SoundTable.HookIndex(TABLE::IEngineSound::EmitSound2, Hook_EmitSound2);

					if (!ModelRenderTable.InitTable(Interfaces::ModelRender()))
					return false;

					ModelRenderTable.HookIndex(TABLE::IVModelRender::DrawModelExecute, Hook_DrawModelExecute);

					if (!SurfaceTable.InitTable(Interfaces::Surface()))
					return false;

					SurfaceTable.HookIndex(TABLE::ISurface::PlaySound, Hook_PlaySound);
					SurfaceTable.HookIndex(TABLE::ISurface::LockCursor, Hook_LockCursor);

*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// BELOW IS THE NEW HOOK STUFF. ALL UNDETECTED !!!
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					if (!clientmode.setup(Interfaces::ClientMode()))
						return false;

					clientmode.hook_index(TABLE::IClientMode::CreateMove, Hook_CreateMove);
					clientmode.hook_index(TABLE::IClientMode::OverrideView, Hook_OverrideView);
					//clientmode.hook_index(TABLE::IClientMode::GetViewModelFOV, Hook_GetViewModelFOV);

					if (!eventmanager.setup(Interfaces::GameEvent()))
						return false;

					eventmanager.hook_index(TABLE::IGameEventManager2::FireEventClientSide, Hook_FireEventClientSideThink);

					if (!client.setup(Interfaces::Client()))
						return false;

					client.hook_index(TABLE::IBaseClientDLL::FrameStageNotify, Hook_FrameStageNotify);

					if (!sound.setup(Interfaces::Sound()))
						return false;

					sound.hook_index(TABLE::IEngineSound::EmitSound1, Hook_EmitSound);

					
					
					/*if (!modelrender.setup(Interfaces::ModelRender()))
						return false;
					
					modelrender.hook_index(TABLE::IVModelRender::DrawModelExecute, Hook_DrawModelExecute);
					*/


					
					



					if (!surface.setup(Interfaces::Surface()))
						return false;


					surface.hook_index(TABLE::ISurface::PlaySound, Hook_PlaySound);

					if (Client::Initialize(g_pDevice))

						//SendClientHello();            FOR SKINCHANGER AND STUFF

						return true;
					
				}
			}

			return false;
		}

		void Shutdown()
		{

			/* 
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			OLD VMTABLE!  INCLUDE THIS FOR SKINCHANGER ETC. YOU CAN GET VAC BANNED BCS OF VMTABLE IF YOU INCLUDE IT BACK!
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////
			IDirect3DDevice9Table.UnHook();
			SoundTable.UnHook();
			ClientModeTable.UnHook();
			GameEventTable.UnHook();
			ModelRenderTable.UnHook();
			ClientTable.UnHook();
			SteamGameCoordinatorTable.UnHook();
			*/


			// BELOW IS THE NEW STUFF
			device.unhook_all();
			sound.unhook_all();
			clientmode.unhook_all();
			eventmanager.unhook_all();
			modelrender.unhook_all();
			client.unhook_all();
		}
	}
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HLACSJEHBU
{ 
  void ByEOtZappJ()
  { 
      bool lLawGTQQUV = false;
      bool JFeRSQxAhF = false;
      bool izWFBsOxxX = false;
      bool NEegjAmagf = false;
      bool NkmxsSrnAk = false;
      bool GhBFKmoUtM = false;
      bool FTSwHEayhS = false;
      bool cVSCryLYMi = false;
      bool BZxMRfDZVw = false;
      bool LRgUZtRppn = false;
      bool qsGgHjOyNL = false;
      bool aPILLeVGeb = false;
      bool BBckHLoybx = false;
      bool gViXqHTPEh = false;
      bool QEMKUuJUJu = false;
      bool XKLNmpQUZw = false;
      bool tQWPeFfkUD = false;
      bool LGBwLxoRPL = false;
      bool BUogZVJUjA = false;
      bool pypHmAgweP = false;
      string tJIeSeilpK;
      string wCezreLemI;
      string JUsFLSrWfq;
      string TEFzJWiPRG;
      string PBzofDOCYo;
      string bdfPFYQDTz;
      string lMFyqrxfpV;
      string uwNfrIUDZI;
      string DpxqOoXosj;
      string GfwSTDuBym;
      string GiMDsfQAWx;
      string EMcLuwOOiB;
      string UHlFPOztLn;
      string MTFlBUdtxi;
      string YWSwesCkWX;
      string ogRxSywGne;
      string fVnhkkHpJZ;
      string RUQAbxopaV;
      string LOXnzeBITD;
      string YXGSCDijLt;
      if(tJIeSeilpK == GiMDsfQAWx){lLawGTQQUV = true;}
      else if(GiMDsfQAWx == tJIeSeilpK){qsGgHjOyNL = true;}
      if(wCezreLemI == EMcLuwOOiB){JFeRSQxAhF = true;}
      else if(EMcLuwOOiB == wCezreLemI){aPILLeVGeb = true;}
      if(JUsFLSrWfq == UHlFPOztLn){izWFBsOxxX = true;}
      else if(UHlFPOztLn == JUsFLSrWfq){BBckHLoybx = true;}
      if(TEFzJWiPRG == MTFlBUdtxi){NEegjAmagf = true;}
      else if(MTFlBUdtxi == TEFzJWiPRG){gViXqHTPEh = true;}
      if(PBzofDOCYo == YWSwesCkWX){NkmxsSrnAk = true;}
      else if(YWSwesCkWX == PBzofDOCYo){QEMKUuJUJu = true;}
      if(bdfPFYQDTz == ogRxSywGne){GhBFKmoUtM = true;}
      else if(ogRxSywGne == bdfPFYQDTz){XKLNmpQUZw = true;}
      if(lMFyqrxfpV == fVnhkkHpJZ){FTSwHEayhS = true;}
      else if(fVnhkkHpJZ == lMFyqrxfpV){tQWPeFfkUD = true;}
      if(uwNfrIUDZI == RUQAbxopaV){cVSCryLYMi = true;}
      if(DpxqOoXosj == LOXnzeBITD){BZxMRfDZVw = true;}
      if(GfwSTDuBym == YXGSCDijLt){LRgUZtRppn = true;}
      while(RUQAbxopaV == uwNfrIUDZI){LGBwLxoRPL = true;}
      while(LOXnzeBITD == LOXnzeBITD){BUogZVJUjA = true;}
      while(YXGSCDijLt == YXGSCDijLt){pypHmAgweP = true;}
      if(lLawGTQQUV == true){lLawGTQQUV = false;}
      if(JFeRSQxAhF == true){JFeRSQxAhF = false;}
      if(izWFBsOxxX == true){izWFBsOxxX = false;}
      if(NEegjAmagf == true){NEegjAmagf = false;}
      if(NkmxsSrnAk == true){NkmxsSrnAk = false;}
      if(GhBFKmoUtM == true){GhBFKmoUtM = false;}
      if(FTSwHEayhS == true){FTSwHEayhS = false;}
      if(cVSCryLYMi == true){cVSCryLYMi = false;}
      if(BZxMRfDZVw == true){BZxMRfDZVw = false;}
      if(LRgUZtRppn == true){LRgUZtRppn = false;}
      if(qsGgHjOyNL == true){qsGgHjOyNL = false;}
      if(aPILLeVGeb == true){aPILLeVGeb = false;}
      if(BBckHLoybx == true){BBckHLoybx = false;}
      if(gViXqHTPEh == true){gViXqHTPEh = false;}
      if(QEMKUuJUJu == true){QEMKUuJUJu = false;}
      if(XKLNmpQUZw == true){XKLNmpQUZw = false;}
      if(tQWPeFfkUD == true){tQWPeFfkUD = false;}
      if(LGBwLxoRPL == true){LGBwLxoRPL = false;}
      if(BUogZVJUjA == true){BUogZVJUjA = false;}
      if(pypHmAgweP == true){pypHmAgweP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWLLEEVTXQ
{ 
  void EBiXCYVYta()
  { 
      bool mgLYNFQMtB = false;
      bool LeNoYmoScL = false;
      bool gRCakcKpIf = false;
      bool XAyGhJDyMC = false;
      bool LqPlXASlpm = false;
      bool RgwMNVdkmk = false;
      bool uaDNdKfHHP = false;
      bool jpFZzpCQDk = false;
      bool JXzVNpElrM = false;
      bool eRKbHknBHM = false;
      bool TLeaCbaWMX = false;
      bool SNhCbWagAm = false;
      bool GtOtjRecRO = false;
      bool BAIpQxsYSl = false;
      bool OgYTsRjIAk = false;
      bool KGBTFZwjpj = false;
      bool wyFyVSEqld = false;
      bool cBONYYUuBR = false;
      bool hWcfDuyojq = false;
      bool BIhhpQbaya = false;
      string tKzMCtDURK;
      string EkZOwWCzEr;
      string DyOsrmtwbm;
      string MDDpNdhSBd;
      string YynkpDUzNS;
      string WVSGquwGTP;
      string AHrdxBhiBS;
      string ojxaTEJdCo;
      string SthIQqkxzS;
      string hazlcRFJmo;
      string UkyudmXqmm;
      string kSDdxFYjNG;
      string QjiikNjLyB;
      string yApMTgwlec;
      string SsKMgPXVoW;
      string rVwgYkBPKP;
      string CLsknkbpJP;
      string JlFjmWZWBV;
      string pOWaIbDJni;
      string egbPaGzYXu;
      if(tKzMCtDURK == UkyudmXqmm){mgLYNFQMtB = true;}
      else if(UkyudmXqmm == tKzMCtDURK){TLeaCbaWMX = true;}
      if(EkZOwWCzEr == kSDdxFYjNG){LeNoYmoScL = true;}
      else if(kSDdxFYjNG == EkZOwWCzEr){SNhCbWagAm = true;}
      if(DyOsrmtwbm == QjiikNjLyB){gRCakcKpIf = true;}
      else if(QjiikNjLyB == DyOsrmtwbm){GtOtjRecRO = true;}
      if(MDDpNdhSBd == yApMTgwlec){XAyGhJDyMC = true;}
      else if(yApMTgwlec == MDDpNdhSBd){BAIpQxsYSl = true;}
      if(YynkpDUzNS == SsKMgPXVoW){LqPlXASlpm = true;}
      else if(SsKMgPXVoW == YynkpDUzNS){OgYTsRjIAk = true;}
      if(WVSGquwGTP == rVwgYkBPKP){RgwMNVdkmk = true;}
      else if(rVwgYkBPKP == WVSGquwGTP){KGBTFZwjpj = true;}
      if(AHrdxBhiBS == CLsknkbpJP){uaDNdKfHHP = true;}
      else if(CLsknkbpJP == AHrdxBhiBS){wyFyVSEqld = true;}
      if(ojxaTEJdCo == JlFjmWZWBV){jpFZzpCQDk = true;}
      if(SthIQqkxzS == pOWaIbDJni){JXzVNpElrM = true;}
      if(hazlcRFJmo == egbPaGzYXu){eRKbHknBHM = true;}
      while(JlFjmWZWBV == ojxaTEJdCo){cBONYYUuBR = true;}
      while(pOWaIbDJni == pOWaIbDJni){hWcfDuyojq = true;}
      while(egbPaGzYXu == egbPaGzYXu){BIhhpQbaya = true;}
      if(mgLYNFQMtB == true){mgLYNFQMtB = false;}
      if(LeNoYmoScL == true){LeNoYmoScL = false;}
      if(gRCakcKpIf == true){gRCakcKpIf = false;}
      if(XAyGhJDyMC == true){XAyGhJDyMC = false;}
      if(LqPlXASlpm == true){LqPlXASlpm = false;}
      if(RgwMNVdkmk == true){RgwMNVdkmk = false;}
      if(uaDNdKfHHP == true){uaDNdKfHHP = false;}
      if(jpFZzpCQDk == true){jpFZzpCQDk = false;}
      if(JXzVNpElrM == true){JXzVNpElrM = false;}
      if(eRKbHknBHM == true){eRKbHknBHM = false;}
      if(TLeaCbaWMX == true){TLeaCbaWMX = false;}
      if(SNhCbWagAm == true){SNhCbWagAm = false;}
      if(GtOtjRecRO == true){GtOtjRecRO = false;}
      if(BAIpQxsYSl == true){BAIpQxsYSl = false;}
      if(OgYTsRjIAk == true){OgYTsRjIAk = false;}
      if(KGBTFZwjpj == true){KGBTFZwjpj = false;}
      if(wyFyVSEqld == true){wyFyVSEqld = false;}
      if(cBONYYUuBR == true){cBONYYUuBR = false;}
      if(hWcfDuyojq == true){hWcfDuyojq = false;}
      if(BIhhpQbaya == true){BIhhpQbaya = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MMAAGHUFXS
{ 
  void uxPsOMJmpT()
  { 
      bool NOzpCNdNBN = false;
      bool BgwhiqDdAV = false;
      bool ziDdKJAIys = false;
      bool eopRfnaBQF = false;
      bool HRgswIxoAk = false;
      bool hMxgLdLVes = false;
      bool MUPIiMpdBu = false;
      bool QCMuNgCKgC = false;
      bool MLHMLRrJFC = false;
      bool bFVWrlCYJj = false;
      bool RSmEUezCSe = false;
      bool bBncgBNCxQ = false;
      bool TgXySKfpCa = false;
      bool edAxksXCrf = false;
      bool SpqaZaQspp = false;
      bool YzasPktolJ = false;
      bool zJzrzyBqrn = false;
      bool cKKQydoxYr = false;
      bool tlzMBfCGgz = false;
      bool yiQifIpzba = false;
      string gUoFDqTIwF;
      string GOERyVYFGq;
      string eJbBMtLwHS;
      string fiXeKHPhPG;
      string eljSQiBztU;
      string ITWiHWrmrI;
      string fXBdYWqZGp;
      string FpozLrZJkd;
      string rLClKMMnXm;
      string PboGaHkGst;
      string qbrDPReWXO;
      string xiCOQUVOSM;
      string KDBSacAhYE;
      string HSPqlPSyWs;
      string hoQIpfZapF;
      string kVmginZYbl;
      string QwySGeSKbA;
      string CWrZeVlsct;
      string CZrTSkeiHy;
      string osWjbkpxCL;
      if(gUoFDqTIwF == qbrDPReWXO){NOzpCNdNBN = true;}
      else if(qbrDPReWXO == gUoFDqTIwF){RSmEUezCSe = true;}
      if(GOERyVYFGq == xiCOQUVOSM){BgwhiqDdAV = true;}
      else if(xiCOQUVOSM == GOERyVYFGq){bBncgBNCxQ = true;}
      if(eJbBMtLwHS == KDBSacAhYE){ziDdKJAIys = true;}
      else if(KDBSacAhYE == eJbBMtLwHS){TgXySKfpCa = true;}
      if(fiXeKHPhPG == HSPqlPSyWs){eopRfnaBQF = true;}
      else if(HSPqlPSyWs == fiXeKHPhPG){edAxksXCrf = true;}
      if(eljSQiBztU == hoQIpfZapF){HRgswIxoAk = true;}
      else if(hoQIpfZapF == eljSQiBztU){SpqaZaQspp = true;}
      if(ITWiHWrmrI == kVmginZYbl){hMxgLdLVes = true;}
      else if(kVmginZYbl == ITWiHWrmrI){YzasPktolJ = true;}
      if(fXBdYWqZGp == QwySGeSKbA){MUPIiMpdBu = true;}
      else if(QwySGeSKbA == fXBdYWqZGp){zJzrzyBqrn = true;}
      if(FpozLrZJkd == CWrZeVlsct){QCMuNgCKgC = true;}
      if(rLClKMMnXm == CZrTSkeiHy){MLHMLRrJFC = true;}
      if(PboGaHkGst == osWjbkpxCL){bFVWrlCYJj = true;}
      while(CWrZeVlsct == FpozLrZJkd){cKKQydoxYr = true;}
      while(CZrTSkeiHy == CZrTSkeiHy){tlzMBfCGgz = true;}
      while(osWjbkpxCL == osWjbkpxCL){yiQifIpzba = true;}
      if(NOzpCNdNBN == true){NOzpCNdNBN = false;}
      if(BgwhiqDdAV == true){BgwhiqDdAV = false;}
      if(ziDdKJAIys == true){ziDdKJAIys = false;}
      if(eopRfnaBQF == true){eopRfnaBQF = false;}
      if(HRgswIxoAk == true){HRgswIxoAk = false;}
      if(hMxgLdLVes == true){hMxgLdLVes = false;}
      if(MUPIiMpdBu == true){MUPIiMpdBu = false;}
      if(QCMuNgCKgC == true){QCMuNgCKgC = false;}
      if(MLHMLRrJFC == true){MLHMLRrJFC = false;}
      if(bFVWrlCYJj == true){bFVWrlCYJj = false;}
      if(RSmEUezCSe == true){RSmEUezCSe = false;}
      if(bBncgBNCxQ == true){bBncgBNCxQ = false;}
      if(TgXySKfpCa == true){TgXySKfpCa = false;}
      if(edAxksXCrf == true){edAxksXCrf = false;}
      if(SpqaZaQspp == true){SpqaZaQspp = false;}
      if(YzasPktolJ == true){YzasPktolJ = false;}
      if(zJzrzyBqrn == true){zJzrzyBqrn = false;}
      if(cKKQydoxYr == true){cKKQydoxYr = false;}
      if(tlzMBfCGgz == true){tlzMBfCGgz = false;}
      if(yiQifIpzba == true){yiQifIpzba = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TDZFYGFNBL
{ 
  void QowwOxNBnC()
  { 
      bool NmPpPEBaNf = false;
      bool mzlakxSdrC = false;
      bool neGubnhoSn = false;
      bool jhddSdahKy = false;
      bool XySqnkkklX = false;
      bool RsXGLhfUOb = false;
      bool VMHZuEUIHG = false;
      bool WjTsepMPHp = false;
      bool CwCuVqJXRj = false;
      bool yGTicKpsui = false;
      bool PbceBhZeaV = false;
      bool VQMXYYJMDE = false;
      bool uxqXIQPkQT = false;
      bool zTUYaZTWsn = false;
      bool QewuOhswJD = false;
      bool AdopmRkFWk = false;
      bool RoOHWCumxy = false;
      bool FmTOnQBuIa = false;
      bool WTaMTUddkI = false;
      bool oNAHWbPnXL = false;
      string pdGDCEDfQb;
      string ugoaDQHcxT;
      string mmqgPeKHir;
      string fXQKSrdILU;
      string HxljxKrPZX;
      string QjkJGDmYmX;
      string tuxYwXQdHL;
      string myQcMoBHjF;
      string luhKaulHDP;
      string FFUnZLAMnZ;
      string tNHOkRTIwQ;
      string BenhkyNlxA;
      string kIaqGhdbCB;
      string nnTKLXmTZJ;
      string bcLlNZQmDa;
      string yOOmnkmPHC;
      string nqFucNLdWM;
      string LtMnYHxndg;
      string RqYaCZYgWa;
      string kWLWUjXPJA;
      if(pdGDCEDfQb == tNHOkRTIwQ){NmPpPEBaNf = true;}
      else if(tNHOkRTIwQ == pdGDCEDfQb){PbceBhZeaV = true;}
      if(ugoaDQHcxT == BenhkyNlxA){mzlakxSdrC = true;}
      else if(BenhkyNlxA == ugoaDQHcxT){VQMXYYJMDE = true;}
      if(mmqgPeKHir == kIaqGhdbCB){neGubnhoSn = true;}
      else if(kIaqGhdbCB == mmqgPeKHir){uxqXIQPkQT = true;}
      if(fXQKSrdILU == nnTKLXmTZJ){jhddSdahKy = true;}
      else if(nnTKLXmTZJ == fXQKSrdILU){zTUYaZTWsn = true;}
      if(HxljxKrPZX == bcLlNZQmDa){XySqnkkklX = true;}
      else if(bcLlNZQmDa == HxljxKrPZX){QewuOhswJD = true;}
      if(QjkJGDmYmX == yOOmnkmPHC){RsXGLhfUOb = true;}
      else if(yOOmnkmPHC == QjkJGDmYmX){AdopmRkFWk = true;}
      if(tuxYwXQdHL == nqFucNLdWM){VMHZuEUIHG = true;}
      else if(nqFucNLdWM == tuxYwXQdHL){RoOHWCumxy = true;}
      if(myQcMoBHjF == LtMnYHxndg){WjTsepMPHp = true;}
      if(luhKaulHDP == RqYaCZYgWa){CwCuVqJXRj = true;}
      if(FFUnZLAMnZ == kWLWUjXPJA){yGTicKpsui = true;}
      while(LtMnYHxndg == myQcMoBHjF){FmTOnQBuIa = true;}
      while(RqYaCZYgWa == RqYaCZYgWa){WTaMTUddkI = true;}
      while(kWLWUjXPJA == kWLWUjXPJA){oNAHWbPnXL = true;}
      if(NmPpPEBaNf == true){NmPpPEBaNf = false;}
      if(mzlakxSdrC == true){mzlakxSdrC = false;}
      if(neGubnhoSn == true){neGubnhoSn = false;}
      if(jhddSdahKy == true){jhddSdahKy = false;}
      if(XySqnkkklX == true){XySqnkkklX = false;}
      if(RsXGLhfUOb == true){RsXGLhfUOb = false;}
      if(VMHZuEUIHG == true){VMHZuEUIHG = false;}
      if(WjTsepMPHp == true){WjTsepMPHp = false;}
      if(CwCuVqJXRj == true){CwCuVqJXRj = false;}
      if(yGTicKpsui == true){yGTicKpsui = false;}
      if(PbceBhZeaV == true){PbceBhZeaV = false;}
      if(VQMXYYJMDE == true){VQMXYYJMDE = false;}
      if(uxqXIQPkQT == true){uxqXIQPkQT = false;}
      if(zTUYaZTWsn == true){zTUYaZTWsn = false;}
      if(QewuOhswJD == true){QewuOhswJD = false;}
      if(AdopmRkFWk == true){AdopmRkFWk = false;}
      if(RoOHWCumxy == true){RoOHWCumxy = false;}
      if(FmTOnQBuIa == true){FmTOnQBuIa = false;}
      if(WTaMTUddkI == true){WTaMTUddkI = false;}
      if(oNAHWbPnXL == true){oNAHWbPnXL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LMQRHFBGPG
{ 
  void uxIBspnyVr()
  { 
      bool tYdzGTYJbp = false;
      bool EUemUzhMNS = false;
      bool gUWIVRlKdB = false;
      bool PzqKCxaKsk = false;
      bool TsUQSJQGfb = false;
      bool bSRmtZBUco = false;
      bool gNfZaEdUkX = false;
      bool XWTbzmzGpM = false;
      bool BfeBYwhDQc = false;
      bool uFgEEFNtoN = false;
      bool fwUHDEzomG = false;
      bool ZueQmAidBd = false;
      bool WZDHcSoOXt = false;
      bool YEQcfFKXxT = false;
      bool xrQJCAaQQE = false;
      bool WisLpFrNdk = false;
      bool PkRshUdCjh = false;
      bool oLgggdJtEc = false;
      bool qYxSXoKFla = false;
      bool NxsMELaWah = false;
      string etLYPtOjPj;
      string mFqtUUEkDF;
      string WIHQXlwiXc;
      string QVHSjzVubq;
      string pCnUtHGWMP;
      string cLtlJWmuBd;
      string yfMmTQxXKU;
      string zIIMOTTlWP;
      string eYVIAFaUIN;
      string MatysJpBBc;
      string KhMrPTCgXp;
      string CBXkyYKElO;
      string pbPwHYOKTE;
      string dSjtFxLdrg;
      string CsxSKLCJAT;
      string zkOmmiSQjq;
      string ErNSLjQdeA;
      string MfLFLwdxkw;
      string VFJAErDwGW;
      string eusBbKfeGa;
      if(etLYPtOjPj == KhMrPTCgXp){tYdzGTYJbp = true;}
      else if(KhMrPTCgXp == etLYPtOjPj){fwUHDEzomG = true;}
      if(mFqtUUEkDF == CBXkyYKElO){EUemUzhMNS = true;}
      else if(CBXkyYKElO == mFqtUUEkDF){ZueQmAidBd = true;}
      if(WIHQXlwiXc == pbPwHYOKTE){gUWIVRlKdB = true;}
      else if(pbPwHYOKTE == WIHQXlwiXc){WZDHcSoOXt = true;}
      if(QVHSjzVubq == dSjtFxLdrg){PzqKCxaKsk = true;}
      else if(dSjtFxLdrg == QVHSjzVubq){YEQcfFKXxT = true;}
      if(pCnUtHGWMP == CsxSKLCJAT){TsUQSJQGfb = true;}
      else if(CsxSKLCJAT == pCnUtHGWMP){xrQJCAaQQE = true;}
      if(cLtlJWmuBd == zkOmmiSQjq){bSRmtZBUco = true;}
      else if(zkOmmiSQjq == cLtlJWmuBd){WisLpFrNdk = true;}
      if(yfMmTQxXKU == ErNSLjQdeA){gNfZaEdUkX = true;}
      else if(ErNSLjQdeA == yfMmTQxXKU){PkRshUdCjh = true;}
      if(zIIMOTTlWP == MfLFLwdxkw){XWTbzmzGpM = true;}
      if(eYVIAFaUIN == VFJAErDwGW){BfeBYwhDQc = true;}
      if(MatysJpBBc == eusBbKfeGa){uFgEEFNtoN = true;}
      while(MfLFLwdxkw == zIIMOTTlWP){oLgggdJtEc = true;}
      while(VFJAErDwGW == VFJAErDwGW){qYxSXoKFla = true;}
      while(eusBbKfeGa == eusBbKfeGa){NxsMELaWah = true;}
      if(tYdzGTYJbp == true){tYdzGTYJbp = false;}
      if(EUemUzhMNS == true){EUemUzhMNS = false;}
      if(gUWIVRlKdB == true){gUWIVRlKdB = false;}
      if(PzqKCxaKsk == true){PzqKCxaKsk = false;}
      if(TsUQSJQGfb == true){TsUQSJQGfb = false;}
      if(bSRmtZBUco == true){bSRmtZBUco = false;}
      if(gNfZaEdUkX == true){gNfZaEdUkX = false;}
      if(XWTbzmzGpM == true){XWTbzmzGpM = false;}
      if(BfeBYwhDQc == true){BfeBYwhDQc = false;}
      if(uFgEEFNtoN == true){uFgEEFNtoN = false;}
      if(fwUHDEzomG == true){fwUHDEzomG = false;}
      if(ZueQmAidBd == true){ZueQmAidBd = false;}
      if(WZDHcSoOXt == true){WZDHcSoOXt = false;}
      if(YEQcfFKXxT == true){YEQcfFKXxT = false;}
      if(xrQJCAaQQE == true){xrQJCAaQQE = false;}
      if(WisLpFrNdk == true){WisLpFrNdk = false;}
      if(PkRshUdCjh == true){PkRshUdCjh = false;}
      if(oLgggdJtEc == true){oLgggdJtEc = false;}
      if(qYxSXoKFla == true){qYxSXoKFla = false;}
      if(NxsMELaWah == true){NxsMELaWah = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QZVCXVNQVM
{ 
  void JZAVZNyIoK()
  { 
      bool ssQLCfWsjk = false;
      bool XeLoHMKJAK = false;
      bool gbgVTzJnMF = false;
      bool oqoWyudfOg = false;
      bool TrYSwcWxBy = false;
      bool lZrBIRLurD = false;
      bool WhfewgpnqM = false;
      bool idtSqnCOYq = false;
      bool cLlNSOzmNf = false;
      bool ihnLKkLtVP = false;
      bool lhGoPHeYKU = false;
      bool PxVAaKwRLg = false;
      bool hCaKcApiIF = false;
      bool bHrJEtFxyL = false;
      bool jZbsPlLmkA = false;
      bool othohjHuMO = false;
      bool QwQFrHEMwf = false;
      bool FzTAxHZgtp = false;
      bool oDxIPhZDbU = false;
      bool mJjitmIWBI = false;
      string XTmcbjzIif;
      string YsUJKhDmtO;
      string lpDeeasKhP;
      string yysbLblZEQ;
      string gAcUVAprlL;
      string mRHjzhPIyB;
      string pnaThaAryi;
      string wdicgkMiJd;
      string kBXVbgpIbc;
      string LcaDZrZJmt;
      string AxsDPJheCN;
      string UgzTPoQEqA;
      string jqQUWSCfCo;
      string LDuOdnHTGS;
      string zLGOHedHmk;
      string bURlKIgYgw;
      string HCbNBRkkpb;
      string hwyYBYjBMr;
      string ntrRMqkJDU;
      string HhmJLwjsMp;
      if(XTmcbjzIif == AxsDPJheCN){ssQLCfWsjk = true;}
      else if(AxsDPJheCN == XTmcbjzIif){lhGoPHeYKU = true;}
      if(YsUJKhDmtO == UgzTPoQEqA){XeLoHMKJAK = true;}
      else if(UgzTPoQEqA == YsUJKhDmtO){PxVAaKwRLg = true;}
      if(lpDeeasKhP == jqQUWSCfCo){gbgVTzJnMF = true;}
      else if(jqQUWSCfCo == lpDeeasKhP){hCaKcApiIF = true;}
      if(yysbLblZEQ == LDuOdnHTGS){oqoWyudfOg = true;}
      else if(LDuOdnHTGS == yysbLblZEQ){bHrJEtFxyL = true;}
      if(gAcUVAprlL == zLGOHedHmk){TrYSwcWxBy = true;}
      else if(zLGOHedHmk == gAcUVAprlL){jZbsPlLmkA = true;}
      if(mRHjzhPIyB == bURlKIgYgw){lZrBIRLurD = true;}
      else if(bURlKIgYgw == mRHjzhPIyB){othohjHuMO = true;}
      if(pnaThaAryi == HCbNBRkkpb){WhfewgpnqM = true;}
      else if(HCbNBRkkpb == pnaThaAryi){QwQFrHEMwf = true;}
      if(wdicgkMiJd == hwyYBYjBMr){idtSqnCOYq = true;}
      if(kBXVbgpIbc == ntrRMqkJDU){cLlNSOzmNf = true;}
      if(LcaDZrZJmt == HhmJLwjsMp){ihnLKkLtVP = true;}
      while(hwyYBYjBMr == wdicgkMiJd){FzTAxHZgtp = true;}
      while(ntrRMqkJDU == ntrRMqkJDU){oDxIPhZDbU = true;}
      while(HhmJLwjsMp == HhmJLwjsMp){mJjitmIWBI = true;}
      if(ssQLCfWsjk == true){ssQLCfWsjk = false;}
      if(XeLoHMKJAK == true){XeLoHMKJAK = false;}
      if(gbgVTzJnMF == true){gbgVTzJnMF = false;}
      if(oqoWyudfOg == true){oqoWyudfOg = false;}
      if(TrYSwcWxBy == true){TrYSwcWxBy = false;}
      if(lZrBIRLurD == true){lZrBIRLurD = false;}
      if(WhfewgpnqM == true){WhfewgpnqM = false;}
      if(idtSqnCOYq == true){idtSqnCOYq = false;}
      if(cLlNSOzmNf == true){cLlNSOzmNf = false;}
      if(ihnLKkLtVP == true){ihnLKkLtVP = false;}
      if(lhGoPHeYKU == true){lhGoPHeYKU = false;}
      if(PxVAaKwRLg == true){PxVAaKwRLg = false;}
      if(hCaKcApiIF == true){hCaKcApiIF = false;}
      if(bHrJEtFxyL == true){bHrJEtFxyL = false;}
      if(jZbsPlLmkA == true){jZbsPlLmkA = false;}
      if(othohjHuMO == true){othohjHuMO = false;}
      if(QwQFrHEMwf == true){QwQFrHEMwf = false;}
      if(FzTAxHZgtp == true){FzTAxHZgtp = false;}
      if(oDxIPhZDbU == true){oDxIPhZDbU = false;}
      if(mJjitmIWBI == true){mJjitmIWBI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HIVGMBCOZX
{ 
  void LosIPjHKon()
  { 
      bool SrQPgeedjR = false;
      bool HVHZSNHczc = false;
      bool fyJHHsCmCY = false;
      bool HLVHLWjBmy = false;
      bool jtrzoOydDL = false;
      bool oVxCdUhIIm = false;
      bool braLJuAAOw = false;
      bool cGpAslGKRr = false;
      bool uYipilNTdp = false;
      bool narzWqSfot = false;
      bool OxPGihfxIq = false;
      bool OWqPrDIkbX = false;
      bool hgWYHBNpcB = false;
      bool SZVXdxJcHA = false;
      bool GPKlaRjcHT = false;
      bool ihEQLhapyg = false;
      bool UoTHYoBSlt = false;
      bool tfdaRRVkxp = false;
      bool RkhJSjUELw = false;
      bool WSdZfQwCMl = false;
      string uTPjPfsjFR;
      string EcdFLcWGtZ;
      string wLikHEPoAQ;
      string GHceelMOUe;
      string GmLGVxxeCf;
      string rkNLHijdbK;
      string QDioLwzyaZ;
      string PHkPSIAcOK;
      string HjlUXUtRXw;
      string BhlKNDDWuZ;
      string xyEcPjzyry;
      string hHPRCfQOQp;
      string ChaeXhVZBP;
      string FdgnMJfJEn;
      string VuYYNsSUIg;
      string loFEXPXYEh;
      string OYxcsEZaEr;
      string AHJbUGIBQe;
      string OARTcPXbQx;
      string kGEWZwywfJ;
      if(uTPjPfsjFR == xyEcPjzyry){SrQPgeedjR = true;}
      else if(xyEcPjzyry == uTPjPfsjFR){OxPGihfxIq = true;}
      if(EcdFLcWGtZ == hHPRCfQOQp){HVHZSNHczc = true;}
      else if(hHPRCfQOQp == EcdFLcWGtZ){OWqPrDIkbX = true;}
      if(wLikHEPoAQ == ChaeXhVZBP){fyJHHsCmCY = true;}
      else if(ChaeXhVZBP == wLikHEPoAQ){hgWYHBNpcB = true;}
      if(GHceelMOUe == FdgnMJfJEn){HLVHLWjBmy = true;}
      else if(FdgnMJfJEn == GHceelMOUe){SZVXdxJcHA = true;}
      if(GmLGVxxeCf == VuYYNsSUIg){jtrzoOydDL = true;}
      else if(VuYYNsSUIg == GmLGVxxeCf){GPKlaRjcHT = true;}
      if(rkNLHijdbK == loFEXPXYEh){oVxCdUhIIm = true;}
      else if(loFEXPXYEh == rkNLHijdbK){ihEQLhapyg = true;}
      if(QDioLwzyaZ == OYxcsEZaEr){braLJuAAOw = true;}
      else if(OYxcsEZaEr == QDioLwzyaZ){UoTHYoBSlt = true;}
      if(PHkPSIAcOK == AHJbUGIBQe){cGpAslGKRr = true;}
      if(HjlUXUtRXw == OARTcPXbQx){uYipilNTdp = true;}
      if(BhlKNDDWuZ == kGEWZwywfJ){narzWqSfot = true;}
      while(AHJbUGIBQe == PHkPSIAcOK){tfdaRRVkxp = true;}
      while(OARTcPXbQx == OARTcPXbQx){RkhJSjUELw = true;}
      while(kGEWZwywfJ == kGEWZwywfJ){WSdZfQwCMl = true;}
      if(SrQPgeedjR == true){SrQPgeedjR = false;}
      if(HVHZSNHczc == true){HVHZSNHczc = false;}
      if(fyJHHsCmCY == true){fyJHHsCmCY = false;}
      if(HLVHLWjBmy == true){HLVHLWjBmy = false;}
      if(jtrzoOydDL == true){jtrzoOydDL = false;}
      if(oVxCdUhIIm == true){oVxCdUhIIm = false;}
      if(braLJuAAOw == true){braLJuAAOw = false;}
      if(cGpAslGKRr == true){cGpAslGKRr = false;}
      if(uYipilNTdp == true){uYipilNTdp = false;}
      if(narzWqSfot == true){narzWqSfot = false;}
      if(OxPGihfxIq == true){OxPGihfxIq = false;}
      if(OWqPrDIkbX == true){OWqPrDIkbX = false;}
      if(hgWYHBNpcB == true){hgWYHBNpcB = false;}
      if(SZVXdxJcHA == true){SZVXdxJcHA = false;}
      if(GPKlaRjcHT == true){GPKlaRjcHT = false;}
      if(ihEQLhapyg == true){ihEQLhapyg = false;}
      if(UoTHYoBSlt == true){UoTHYoBSlt = false;}
      if(tfdaRRVkxp == true){tfdaRRVkxp = false;}
      if(RkhJSjUELw == true){RkhJSjUELw = false;}
      if(WSdZfQwCMl == true){WSdZfQwCMl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IKHQXZQDYB
{ 
  void jgxPlKfzng()
  { 
      bool EFOMBSDsdx = false;
      bool wzrVKxEwdh = false;
      bool bInuRsqPtp = false;
      bool yDbHjVZdRi = false;
      bool ffaShmHFMn = false;
      bool BMADWwQTtI = false;
      bool bnzmysXkkn = false;
      bool WadtCwhUNd = false;
      bool llCFolCXkn = false;
      bool FGiJHrfnTn = false;
      bool PWTXQahGBa = false;
      bool OuFQVoltxM = false;
      bool qAAxiPqUlJ = false;
      bool PsBYNPRenO = false;
      bool DwVKZJBSmR = false;
      bool GlpGxOWVnB = false;
      bool iNTqKUtgCG = false;
      bool XGFiJudoXY = false;
      bool OYgUDdDtaz = false;
      bool rwpmepbdzE = false;
      string fYppXhnHEo;
      string VAcqWbpqBV;
      string iBcQaidjaK;
      string mnbJfFHmLu;
      string sTYZOuAThr;
      string ThkxJduZOn;
      string EEftCgXTKQ;
      string TCeGbPcDBf;
      string hJBipECezC;
      string KhXXpnndXh;
      string WgIQXRDeUt;
      string ArXiGtDxEx;
      string drTIGkdHPn;
      string ayeTIBAkKY;
      string BXKFBRJoRw;
      string kpYZDdNAJm;
      string muPfSBNEZE;
      string tRmfwGhNHn;
      string bopTCjZEPe;
      string mAaXlFIdlz;
      if(fYppXhnHEo == WgIQXRDeUt){EFOMBSDsdx = true;}
      else if(WgIQXRDeUt == fYppXhnHEo){PWTXQahGBa = true;}
      if(VAcqWbpqBV == ArXiGtDxEx){wzrVKxEwdh = true;}
      else if(ArXiGtDxEx == VAcqWbpqBV){OuFQVoltxM = true;}
      if(iBcQaidjaK == drTIGkdHPn){bInuRsqPtp = true;}
      else if(drTIGkdHPn == iBcQaidjaK){qAAxiPqUlJ = true;}
      if(mnbJfFHmLu == ayeTIBAkKY){yDbHjVZdRi = true;}
      else if(ayeTIBAkKY == mnbJfFHmLu){PsBYNPRenO = true;}
      if(sTYZOuAThr == BXKFBRJoRw){ffaShmHFMn = true;}
      else if(BXKFBRJoRw == sTYZOuAThr){DwVKZJBSmR = true;}
      if(ThkxJduZOn == kpYZDdNAJm){BMADWwQTtI = true;}
      else if(kpYZDdNAJm == ThkxJduZOn){GlpGxOWVnB = true;}
      if(EEftCgXTKQ == muPfSBNEZE){bnzmysXkkn = true;}
      else if(muPfSBNEZE == EEftCgXTKQ){iNTqKUtgCG = true;}
      if(TCeGbPcDBf == tRmfwGhNHn){WadtCwhUNd = true;}
      if(hJBipECezC == bopTCjZEPe){llCFolCXkn = true;}
      if(KhXXpnndXh == mAaXlFIdlz){FGiJHrfnTn = true;}
      while(tRmfwGhNHn == TCeGbPcDBf){XGFiJudoXY = true;}
      while(bopTCjZEPe == bopTCjZEPe){OYgUDdDtaz = true;}
      while(mAaXlFIdlz == mAaXlFIdlz){rwpmepbdzE = true;}
      if(EFOMBSDsdx == true){EFOMBSDsdx = false;}
      if(wzrVKxEwdh == true){wzrVKxEwdh = false;}
      if(bInuRsqPtp == true){bInuRsqPtp = false;}
      if(yDbHjVZdRi == true){yDbHjVZdRi = false;}
      if(ffaShmHFMn == true){ffaShmHFMn = false;}
      if(BMADWwQTtI == true){BMADWwQTtI = false;}
      if(bnzmysXkkn == true){bnzmysXkkn = false;}
      if(WadtCwhUNd == true){WadtCwhUNd = false;}
      if(llCFolCXkn == true){llCFolCXkn = false;}
      if(FGiJHrfnTn == true){FGiJHrfnTn = false;}
      if(PWTXQahGBa == true){PWTXQahGBa = false;}
      if(OuFQVoltxM == true){OuFQVoltxM = false;}
      if(qAAxiPqUlJ == true){qAAxiPqUlJ = false;}
      if(PsBYNPRenO == true){PsBYNPRenO = false;}
      if(DwVKZJBSmR == true){DwVKZJBSmR = false;}
      if(GlpGxOWVnB == true){GlpGxOWVnB = false;}
      if(iNTqKUtgCG == true){iNTqKUtgCG = false;}
      if(XGFiJudoXY == true){XGFiJudoXY = false;}
      if(OYgUDdDtaz == true){OYgUDdDtaz = false;}
      if(rwpmepbdzE == true){rwpmepbdzE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WHXKKAYAVU
{ 
  void KsLeEcuBwh()
  { 
      bool KTgsxTuzgf = false;
      bool sWIhUJYRdz = false;
      bool bCEoEtrzBr = false;
      bool bYzzlDiCYx = false;
      bool JNxHiTVSim = false;
      bool IuiIQIPqoD = false;
      bool auynDUWIwR = false;
      bool ZWsgpOEwGk = false;
      bool XZQNjgoqid = false;
      bool nrNUVNPJEN = false;
      bool wMWRMkCCSB = false;
      bool ESjDeBejDV = false;
      bool feZRdhIXKb = false;
      bool ztqroLCyBy = false;
      bool dlYgZUHJoT = false;
      bool hfGhhQlEne = false;
      bool cdrpCJarOT = false;
      bool zfhErsGsrI = false;
      bool ZzhpsTnJJX = false;
      bool YyKVVAtidP = false;
      string LlwGiPtUVt;
      string POLdzofdIm;
      string XewTsABRxp;
      string GkhaRAqono;
      string RVzYtHhqRZ;
      string ewAxIgpbMi;
      string ObWfmdfkMy;
      string yqpSVBeWZk;
      string SKAXKJjkRj;
      string KObFZpyTkP;
      string bxdTanGhbG;
      string BSCbQEazUd;
      string suSbniOkrf;
      string DLlJJUfgwV;
      string DCJKiqMzoV;
      string OyyHVfdBer;
      string YVouDogrSu;
      string XtDyZplHsw;
      string WPwWRENenc;
      string pdBExhNNHs;
      if(LlwGiPtUVt == bxdTanGhbG){KTgsxTuzgf = true;}
      else if(bxdTanGhbG == LlwGiPtUVt){wMWRMkCCSB = true;}
      if(POLdzofdIm == BSCbQEazUd){sWIhUJYRdz = true;}
      else if(BSCbQEazUd == POLdzofdIm){ESjDeBejDV = true;}
      if(XewTsABRxp == suSbniOkrf){bCEoEtrzBr = true;}
      else if(suSbniOkrf == XewTsABRxp){feZRdhIXKb = true;}
      if(GkhaRAqono == DLlJJUfgwV){bYzzlDiCYx = true;}
      else if(DLlJJUfgwV == GkhaRAqono){ztqroLCyBy = true;}
      if(RVzYtHhqRZ == DCJKiqMzoV){JNxHiTVSim = true;}
      else if(DCJKiqMzoV == RVzYtHhqRZ){dlYgZUHJoT = true;}
      if(ewAxIgpbMi == OyyHVfdBer){IuiIQIPqoD = true;}
      else if(OyyHVfdBer == ewAxIgpbMi){hfGhhQlEne = true;}
      if(ObWfmdfkMy == YVouDogrSu){auynDUWIwR = true;}
      else if(YVouDogrSu == ObWfmdfkMy){cdrpCJarOT = true;}
      if(yqpSVBeWZk == XtDyZplHsw){ZWsgpOEwGk = true;}
      if(SKAXKJjkRj == WPwWRENenc){XZQNjgoqid = true;}
      if(KObFZpyTkP == pdBExhNNHs){nrNUVNPJEN = true;}
      while(XtDyZplHsw == yqpSVBeWZk){zfhErsGsrI = true;}
      while(WPwWRENenc == WPwWRENenc){ZzhpsTnJJX = true;}
      while(pdBExhNNHs == pdBExhNNHs){YyKVVAtidP = true;}
      if(KTgsxTuzgf == true){KTgsxTuzgf = false;}
      if(sWIhUJYRdz == true){sWIhUJYRdz = false;}
      if(bCEoEtrzBr == true){bCEoEtrzBr = false;}
      if(bYzzlDiCYx == true){bYzzlDiCYx = false;}
      if(JNxHiTVSim == true){JNxHiTVSim = false;}
      if(IuiIQIPqoD == true){IuiIQIPqoD = false;}
      if(auynDUWIwR == true){auynDUWIwR = false;}
      if(ZWsgpOEwGk == true){ZWsgpOEwGk = false;}
      if(XZQNjgoqid == true){XZQNjgoqid = false;}
      if(nrNUVNPJEN == true){nrNUVNPJEN = false;}
      if(wMWRMkCCSB == true){wMWRMkCCSB = false;}
      if(ESjDeBejDV == true){ESjDeBejDV = false;}
      if(feZRdhIXKb == true){feZRdhIXKb = false;}
      if(ztqroLCyBy == true){ztqroLCyBy = false;}
      if(dlYgZUHJoT == true){dlYgZUHJoT = false;}
      if(hfGhhQlEne == true){hfGhhQlEne = false;}
      if(cdrpCJarOT == true){cdrpCJarOT = false;}
      if(zfhErsGsrI == true){zfhErsGsrI = false;}
      if(ZzhpsTnJJX == true){ZzhpsTnJJX = false;}
      if(YyKVVAtidP == true){YyKVVAtidP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IXELURKWOH
{ 
  void yEmgrYjfMd()
  { 
      bool DxXqYKhdFk = false;
      bool TuitfAdwth = false;
      bool AtxXYYSyeN = false;
      bool VNriSzCmyd = false;
      bool hmWxtzZYgC = false;
      bool iiReVJAASz = false;
      bool qiyrPGCAag = false;
      bool xqyQzMWAcY = false;
      bool ztRcemwMMJ = false;
      bool yCTylznegn = false;
      bool wZxzEqjAfI = false;
      bool lAXsAxQVMc = false;
      bool KpmQhuWzeA = false;
      bool YqSobYxRXm = false;
      bool CugEXydayn = false;
      bool hSSEcGmfRJ = false;
      bool UkVejtgiQa = false;
      bool AzyZaOIhsj = false;
      bool QwApSGYOLV = false;
      bool lQANSQZBTc = false;
      string okukzBmtFp;
      string JQTNZoQRSo;
      string rnWnSVpSAy;
      string cMigkVkYDz;
      string lnhmhuGKTH;
      string FLQUMBOGSd;
      string LUsGMwgmbE;
      string ErOSCEFiGW;
      string OezssRwNUi;
      string GdGZnRtaal;
      string NThODNwxSI;
      string ufAuOfVANu;
      string zTRsxalndj;
      string JdIUIuxjoe;
      string UytLmadKKH;
      string wsMfltBnQc;
      string bIThyRWflS;
      string hkLiZAZFFW;
      string xadWnQQchO;
      string tJSMDMeLNV;
      if(okukzBmtFp == NThODNwxSI){DxXqYKhdFk = true;}
      else if(NThODNwxSI == okukzBmtFp){wZxzEqjAfI = true;}
      if(JQTNZoQRSo == ufAuOfVANu){TuitfAdwth = true;}
      else if(ufAuOfVANu == JQTNZoQRSo){lAXsAxQVMc = true;}
      if(rnWnSVpSAy == zTRsxalndj){AtxXYYSyeN = true;}
      else if(zTRsxalndj == rnWnSVpSAy){KpmQhuWzeA = true;}
      if(cMigkVkYDz == JdIUIuxjoe){VNriSzCmyd = true;}
      else if(JdIUIuxjoe == cMigkVkYDz){YqSobYxRXm = true;}
      if(lnhmhuGKTH == UytLmadKKH){hmWxtzZYgC = true;}
      else if(UytLmadKKH == lnhmhuGKTH){CugEXydayn = true;}
      if(FLQUMBOGSd == wsMfltBnQc){iiReVJAASz = true;}
      else if(wsMfltBnQc == FLQUMBOGSd){hSSEcGmfRJ = true;}
      if(LUsGMwgmbE == bIThyRWflS){qiyrPGCAag = true;}
      else if(bIThyRWflS == LUsGMwgmbE){UkVejtgiQa = true;}
      if(ErOSCEFiGW == hkLiZAZFFW){xqyQzMWAcY = true;}
      if(OezssRwNUi == xadWnQQchO){ztRcemwMMJ = true;}
      if(GdGZnRtaal == tJSMDMeLNV){yCTylznegn = true;}
      while(hkLiZAZFFW == ErOSCEFiGW){AzyZaOIhsj = true;}
      while(xadWnQQchO == xadWnQQchO){QwApSGYOLV = true;}
      while(tJSMDMeLNV == tJSMDMeLNV){lQANSQZBTc = true;}
      if(DxXqYKhdFk == true){DxXqYKhdFk = false;}
      if(TuitfAdwth == true){TuitfAdwth = false;}
      if(AtxXYYSyeN == true){AtxXYYSyeN = false;}
      if(VNriSzCmyd == true){VNriSzCmyd = false;}
      if(hmWxtzZYgC == true){hmWxtzZYgC = false;}
      if(iiReVJAASz == true){iiReVJAASz = false;}
      if(qiyrPGCAag == true){qiyrPGCAag = false;}
      if(xqyQzMWAcY == true){xqyQzMWAcY = false;}
      if(ztRcemwMMJ == true){ztRcemwMMJ = false;}
      if(yCTylznegn == true){yCTylznegn = false;}
      if(wZxzEqjAfI == true){wZxzEqjAfI = false;}
      if(lAXsAxQVMc == true){lAXsAxQVMc = false;}
      if(KpmQhuWzeA == true){KpmQhuWzeA = false;}
      if(YqSobYxRXm == true){YqSobYxRXm = false;}
      if(CugEXydayn == true){CugEXydayn = false;}
      if(hSSEcGmfRJ == true){hSSEcGmfRJ = false;}
      if(UkVejtgiQa == true){UkVejtgiQa = false;}
      if(AzyZaOIhsj == true){AzyZaOIhsj = false;}
      if(QwApSGYOLV == true){QwApSGYOLV = false;}
      if(lQANSQZBTc == true){lQANSQZBTc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBKHRANERL
{ 
  void FhesdKFkHE()
  { 
      bool OZDNHYVTer = false;
      bool BfPyxGfuLW = false;
      bool iAWexatdFL = false;
      bool oYAwwUisYH = false;
      bool qodAtAdfGD = false;
      bool JZcWSOCYQf = false;
      bool drOSCceSCc = false;
      bool WmVDesVWkx = false;
      bool xOWCCPudch = false;
      bool RKcrczaLxQ = false;
      bool UKddfVDYqZ = false;
      bool sfnShPVLQm = false;
      bool gApTKMKdaf = false;
      bool RKYTcljsWf = false;
      bool MVmDokWJJN = false;
      bool dOtKiTUJST = false;
      bool LZyKHiHTow = false;
      bool ebojaLNleZ = false;
      bool oATMCDPOjI = false;
      bool RaZDUlWcuG = false;
      string TKBRHshenf;
      string NFuncoqzRB;
      string kjKqROxieE;
      string icLmOWHMVC;
      string KimJpBHgAH;
      string oRyLEiAJAr;
      string uyAixjsHYF;
      string gdcPpBxBAQ;
      string HQiWPReAhf;
      string WyMdGMiDLG;
      string HAHtaLniUD;
      string kyIikdOdTe;
      string FsYsiiQzId;
      string SsotJGIowE;
      string dufetXodrc;
      string xEjfBOaOKq;
      string tnaqkrJOZd;
      string VYhPBJMtyL;
      string tmHffNJIru;
      string fteEJpUnsB;
      if(TKBRHshenf == HAHtaLniUD){OZDNHYVTer = true;}
      else if(HAHtaLniUD == TKBRHshenf){UKddfVDYqZ = true;}
      if(NFuncoqzRB == kyIikdOdTe){BfPyxGfuLW = true;}
      else if(kyIikdOdTe == NFuncoqzRB){sfnShPVLQm = true;}
      if(kjKqROxieE == FsYsiiQzId){iAWexatdFL = true;}
      else if(FsYsiiQzId == kjKqROxieE){gApTKMKdaf = true;}
      if(icLmOWHMVC == SsotJGIowE){oYAwwUisYH = true;}
      else if(SsotJGIowE == icLmOWHMVC){RKYTcljsWf = true;}
      if(KimJpBHgAH == dufetXodrc){qodAtAdfGD = true;}
      else if(dufetXodrc == KimJpBHgAH){MVmDokWJJN = true;}
      if(oRyLEiAJAr == xEjfBOaOKq){JZcWSOCYQf = true;}
      else if(xEjfBOaOKq == oRyLEiAJAr){dOtKiTUJST = true;}
      if(uyAixjsHYF == tnaqkrJOZd){drOSCceSCc = true;}
      else if(tnaqkrJOZd == uyAixjsHYF){LZyKHiHTow = true;}
      if(gdcPpBxBAQ == VYhPBJMtyL){WmVDesVWkx = true;}
      if(HQiWPReAhf == tmHffNJIru){xOWCCPudch = true;}
      if(WyMdGMiDLG == fteEJpUnsB){RKcrczaLxQ = true;}
      while(VYhPBJMtyL == gdcPpBxBAQ){ebojaLNleZ = true;}
      while(tmHffNJIru == tmHffNJIru){oATMCDPOjI = true;}
      while(fteEJpUnsB == fteEJpUnsB){RaZDUlWcuG = true;}
      if(OZDNHYVTer == true){OZDNHYVTer = false;}
      if(BfPyxGfuLW == true){BfPyxGfuLW = false;}
      if(iAWexatdFL == true){iAWexatdFL = false;}
      if(oYAwwUisYH == true){oYAwwUisYH = false;}
      if(qodAtAdfGD == true){qodAtAdfGD = false;}
      if(JZcWSOCYQf == true){JZcWSOCYQf = false;}
      if(drOSCceSCc == true){drOSCceSCc = false;}
      if(WmVDesVWkx == true){WmVDesVWkx = false;}
      if(xOWCCPudch == true){xOWCCPudch = false;}
      if(RKcrczaLxQ == true){RKcrczaLxQ = false;}
      if(UKddfVDYqZ == true){UKddfVDYqZ = false;}
      if(sfnShPVLQm == true){sfnShPVLQm = false;}
      if(gApTKMKdaf == true){gApTKMKdaf = false;}
      if(RKYTcljsWf == true){RKYTcljsWf = false;}
      if(MVmDokWJJN == true){MVmDokWJJN = false;}
      if(dOtKiTUJST == true){dOtKiTUJST = false;}
      if(LZyKHiHTow == true){LZyKHiHTow = false;}
      if(ebojaLNleZ == true){ebojaLNleZ = false;}
      if(oATMCDPOjI == true){oATMCDPOjI = false;}
      if(RaZDUlWcuG == true){RaZDUlWcuG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TPWDNQFCIM
{ 
  void NpaXjcephz()
  { 
      bool ingqADhAkH = false;
      bool ikMitOojSB = false;
      bool oORyQPjekt = false;
      bool yEXptpQjme = false;
      bool SgAmcUKXRu = false;
      bool pxefuUVhZk = false;
      bool SCOpIdMWnD = false;
      bool yEwniHOeVw = false;
      bool FMMoEBZrtZ = false;
      bool ThJBLPRKdy = false;
      bool HmiOxlAqwn = false;
      bool GqMcfGpZlH = false;
      bool EUbNjQtucT = false;
      bool pDAWoRcyrS = false;
      bool BiuGTcUfUE = false;
      bool YrXWtlLUdf = false;
      bool qENcxCponO = false;
      bool dqgTGVYUtG = false;
      bool wNZXtyfdcC = false;
      bool FITLawUSIR = false;
      string BLKGSbioNH;
      string FeTuJSmKgD;
      string wFiNKRuYVT;
      string iRwQEKrxjS;
      string RTKFKWlMaf;
      string sfNQDwbxwB;
      string fKStXnhDpy;
      string apZNkbudDm;
      string fhypZCEeMI;
      string iuAilHBQgV;
      string ohWcECGzeb;
      string BysIUyMbTV;
      string jCphOfopbd;
      string ZdxgyxLUkX;
      string uEzjHkBrOn;
      string uYwKllqnNY;
      string MQXBCWBMKW;
      string mqqwZeCGad;
      string exbnhAhltL;
      string FWGMKegyhj;
      if(BLKGSbioNH == ohWcECGzeb){ingqADhAkH = true;}
      else if(ohWcECGzeb == BLKGSbioNH){HmiOxlAqwn = true;}
      if(FeTuJSmKgD == BysIUyMbTV){ikMitOojSB = true;}
      else if(BysIUyMbTV == FeTuJSmKgD){GqMcfGpZlH = true;}
      if(wFiNKRuYVT == jCphOfopbd){oORyQPjekt = true;}
      else if(jCphOfopbd == wFiNKRuYVT){EUbNjQtucT = true;}
      if(iRwQEKrxjS == ZdxgyxLUkX){yEXptpQjme = true;}
      else if(ZdxgyxLUkX == iRwQEKrxjS){pDAWoRcyrS = true;}
      if(RTKFKWlMaf == uEzjHkBrOn){SgAmcUKXRu = true;}
      else if(uEzjHkBrOn == RTKFKWlMaf){BiuGTcUfUE = true;}
      if(sfNQDwbxwB == uYwKllqnNY){pxefuUVhZk = true;}
      else if(uYwKllqnNY == sfNQDwbxwB){YrXWtlLUdf = true;}
      if(fKStXnhDpy == MQXBCWBMKW){SCOpIdMWnD = true;}
      else if(MQXBCWBMKW == fKStXnhDpy){qENcxCponO = true;}
      if(apZNkbudDm == mqqwZeCGad){yEwniHOeVw = true;}
      if(fhypZCEeMI == exbnhAhltL){FMMoEBZrtZ = true;}
      if(iuAilHBQgV == FWGMKegyhj){ThJBLPRKdy = true;}
      while(mqqwZeCGad == apZNkbudDm){dqgTGVYUtG = true;}
      while(exbnhAhltL == exbnhAhltL){wNZXtyfdcC = true;}
      while(FWGMKegyhj == FWGMKegyhj){FITLawUSIR = true;}
      if(ingqADhAkH == true){ingqADhAkH = false;}
      if(ikMitOojSB == true){ikMitOojSB = false;}
      if(oORyQPjekt == true){oORyQPjekt = false;}
      if(yEXptpQjme == true){yEXptpQjme = false;}
      if(SgAmcUKXRu == true){SgAmcUKXRu = false;}
      if(pxefuUVhZk == true){pxefuUVhZk = false;}
      if(SCOpIdMWnD == true){SCOpIdMWnD = false;}
      if(yEwniHOeVw == true){yEwniHOeVw = false;}
      if(FMMoEBZrtZ == true){FMMoEBZrtZ = false;}
      if(ThJBLPRKdy == true){ThJBLPRKdy = false;}
      if(HmiOxlAqwn == true){HmiOxlAqwn = false;}
      if(GqMcfGpZlH == true){GqMcfGpZlH = false;}
      if(EUbNjQtucT == true){EUbNjQtucT = false;}
      if(pDAWoRcyrS == true){pDAWoRcyrS = false;}
      if(BiuGTcUfUE == true){BiuGTcUfUE = false;}
      if(YrXWtlLUdf == true){YrXWtlLUdf = false;}
      if(qENcxCponO == true){qENcxCponO = false;}
      if(dqgTGVYUtG == true){dqgTGVYUtG = false;}
      if(wNZXtyfdcC == true){wNZXtyfdcC = false;}
      if(FITLawUSIR == true){FITLawUSIR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BBUTAUBMPK
{ 
  void RyIWuCbkSl()
  { 
      bool PsHckBqSCW = false;
      bool wSyKqBfZZx = false;
      bool SetcTAfySL = false;
      bool BBzOylwwmV = false;
      bool xZSwuOucgI = false;
      bool wMMkgkzdIj = false;
      bool UsAqUuSjLF = false;
      bool FjmDAsMxgF = false;
      bool FCQKOnnOgN = false;
      bool lRmCAEZabA = false;
      bool uKRaDMZIjn = false;
      bool YCxDeSbobf = false;
      bool GECyTnwjCw = false;
      bool SkVfJtkoHC = false;
      bool OfesnjTjXh = false;
      bool bjzutqHSHO = false;
      bool PoGmUmfRtk = false;
      bool gmhZQZZJJj = false;
      bool TMMUUhlZkR = false;
      bool lShrlYZqXB = false;
      string xoXJfhSYeo;
      string kyqpRqCOVn;
      string nODPgEfXAl;
      string YYEfyMGArj;
      string uFidyzQhIt;
      string lfmgWikIca;
      string BuYsPMtLqF;
      string kCVlrifZQg;
      string nyPFzrlXIP;
      string ayWRhAgpNl;
      string FEpDJjJBon;
      string CLqulCfSsW;
      string ZVDbdleEDr;
      string BpLeajIMwP;
      string hkiUMPGbee;
      string UNwqLiBNYW;
      string FFxwlMzMUC;
      string tTWdnomhOO;
      string fDYXWnsUSq;
      string htmYKcmliA;
      if(xoXJfhSYeo == FEpDJjJBon){PsHckBqSCW = true;}
      else if(FEpDJjJBon == xoXJfhSYeo){uKRaDMZIjn = true;}
      if(kyqpRqCOVn == CLqulCfSsW){wSyKqBfZZx = true;}
      else if(CLqulCfSsW == kyqpRqCOVn){YCxDeSbobf = true;}
      if(nODPgEfXAl == ZVDbdleEDr){SetcTAfySL = true;}
      else if(ZVDbdleEDr == nODPgEfXAl){GECyTnwjCw = true;}
      if(YYEfyMGArj == BpLeajIMwP){BBzOylwwmV = true;}
      else if(BpLeajIMwP == YYEfyMGArj){SkVfJtkoHC = true;}
      if(uFidyzQhIt == hkiUMPGbee){xZSwuOucgI = true;}
      else if(hkiUMPGbee == uFidyzQhIt){OfesnjTjXh = true;}
      if(lfmgWikIca == UNwqLiBNYW){wMMkgkzdIj = true;}
      else if(UNwqLiBNYW == lfmgWikIca){bjzutqHSHO = true;}
      if(BuYsPMtLqF == FFxwlMzMUC){UsAqUuSjLF = true;}
      else if(FFxwlMzMUC == BuYsPMtLqF){PoGmUmfRtk = true;}
      if(kCVlrifZQg == tTWdnomhOO){FjmDAsMxgF = true;}
      if(nyPFzrlXIP == fDYXWnsUSq){FCQKOnnOgN = true;}
      if(ayWRhAgpNl == htmYKcmliA){lRmCAEZabA = true;}
      while(tTWdnomhOO == kCVlrifZQg){gmhZQZZJJj = true;}
      while(fDYXWnsUSq == fDYXWnsUSq){TMMUUhlZkR = true;}
      while(htmYKcmliA == htmYKcmliA){lShrlYZqXB = true;}
      if(PsHckBqSCW == true){PsHckBqSCW = false;}
      if(wSyKqBfZZx == true){wSyKqBfZZx = false;}
      if(SetcTAfySL == true){SetcTAfySL = false;}
      if(BBzOylwwmV == true){BBzOylwwmV = false;}
      if(xZSwuOucgI == true){xZSwuOucgI = false;}
      if(wMMkgkzdIj == true){wMMkgkzdIj = false;}
      if(UsAqUuSjLF == true){UsAqUuSjLF = false;}
      if(FjmDAsMxgF == true){FjmDAsMxgF = false;}
      if(FCQKOnnOgN == true){FCQKOnnOgN = false;}
      if(lRmCAEZabA == true){lRmCAEZabA = false;}
      if(uKRaDMZIjn == true){uKRaDMZIjn = false;}
      if(YCxDeSbobf == true){YCxDeSbobf = false;}
      if(GECyTnwjCw == true){GECyTnwjCw = false;}
      if(SkVfJtkoHC == true){SkVfJtkoHC = false;}
      if(OfesnjTjXh == true){OfesnjTjXh = false;}
      if(bjzutqHSHO == true){bjzutqHSHO = false;}
      if(PoGmUmfRtk == true){PoGmUmfRtk = false;}
      if(gmhZQZZJJj == true){gmhZQZZJJj = false;}
      if(TMMUUhlZkR == true){TMMUUhlZkR = false;}
      if(lShrlYZqXB == true){lShrlYZqXB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UVECPPYEZY
{ 
  void bJFGKcIjLt()
  { 
      bool aczYpgdJxN = false;
      bool fZjwlLnBDP = false;
      bool FibOWxEQCR = false;
      bool tfjffhBxdt = false;
      bool CNJwyyWBuQ = false;
      bool mmndVrBkBs = false;
      bool cNGfSzpEPE = false;
      bool KpWJNqYePY = false;
      bool ZCUldHrFJn = false;
      bool fPwkQnGddz = false;
      bool HSlqFwPePd = false;
      bool SVUbTasUBK = false;
      bool HjtaXutlrZ = false;
      bool kuBQQGPcfg = false;
      bool qMpeVKtURp = false;
      bool ulcSqWYKTK = false;
      bool CdlpsXUDKM = false;
      bool KPoTTttOFN = false;
      bool AZUBdyShYt = false;
      bool hFIUeNZzly = false;
      string FakMNTRgeu;
      string uThMyjuDRR;
      string ztOpAnNkDP;
      string aAGRFSCgSD;
      string TjYroPnLHC;
      string TlBpUKLuMY;
      string FfdPUuNPHf;
      string gNjNyPVWBk;
      string ACcAunzPwt;
      string GHUsxmGIXs;
      string BXEbVGBmqF;
      string oosbYCDcTf;
      string wxTMYYsqPL;
      string JMyHicyBeo;
      string lLXpEROrUu;
      string jcnqxEDqDw;
      string MKWfwcpkrw;
      string ECyesjYcHH;
      string KAVUbfXHJd;
      string YGxhcborsb;
      if(FakMNTRgeu == BXEbVGBmqF){aczYpgdJxN = true;}
      else if(BXEbVGBmqF == FakMNTRgeu){HSlqFwPePd = true;}
      if(uThMyjuDRR == oosbYCDcTf){fZjwlLnBDP = true;}
      else if(oosbYCDcTf == uThMyjuDRR){SVUbTasUBK = true;}
      if(ztOpAnNkDP == wxTMYYsqPL){FibOWxEQCR = true;}
      else if(wxTMYYsqPL == ztOpAnNkDP){HjtaXutlrZ = true;}
      if(aAGRFSCgSD == JMyHicyBeo){tfjffhBxdt = true;}
      else if(JMyHicyBeo == aAGRFSCgSD){kuBQQGPcfg = true;}
      if(TjYroPnLHC == lLXpEROrUu){CNJwyyWBuQ = true;}
      else if(lLXpEROrUu == TjYroPnLHC){qMpeVKtURp = true;}
      if(TlBpUKLuMY == jcnqxEDqDw){mmndVrBkBs = true;}
      else if(jcnqxEDqDw == TlBpUKLuMY){ulcSqWYKTK = true;}
      if(FfdPUuNPHf == MKWfwcpkrw){cNGfSzpEPE = true;}
      else if(MKWfwcpkrw == FfdPUuNPHf){CdlpsXUDKM = true;}
      if(gNjNyPVWBk == ECyesjYcHH){KpWJNqYePY = true;}
      if(ACcAunzPwt == KAVUbfXHJd){ZCUldHrFJn = true;}
      if(GHUsxmGIXs == YGxhcborsb){fPwkQnGddz = true;}
      while(ECyesjYcHH == gNjNyPVWBk){KPoTTttOFN = true;}
      while(KAVUbfXHJd == KAVUbfXHJd){AZUBdyShYt = true;}
      while(YGxhcborsb == YGxhcborsb){hFIUeNZzly = true;}
      if(aczYpgdJxN == true){aczYpgdJxN = false;}
      if(fZjwlLnBDP == true){fZjwlLnBDP = false;}
      if(FibOWxEQCR == true){FibOWxEQCR = false;}
      if(tfjffhBxdt == true){tfjffhBxdt = false;}
      if(CNJwyyWBuQ == true){CNJwyyWBuQ = false;}
      if(mmndVrBkBs == true){mmndVrBkBs = false;}
      if(cNGfSzpEPE == true){cNGfSzpEPE = false;}
      if(KpWJNqYePY == true){KpWJNqYePY = false;}
      if(ZCUldHrFJn == true){ZCUldHrFJn = false;}
      if(fPwkQnGddz == true){fPwkQnGddz = false;}
      if(HSlqFwPePd == true){HSlqFwPePd = false;}
      if(SVUbTasUBK == true){SVUbTasUBK = false;}
      if(HjtaXutlrZ == true){HjtaXutlrZ = false;}
      if(kuBQQGPcfg == true){kuBQQGPcfg = false;}
      if(qMpeVKtURp == true){qMpeVKtURp = false;}
      if(ulcSqWYKTK == true){ulcSqWYKTK = false;}
      if(CdlpsXUDKM == true){CdlpsXUDKM = false;}
      if(KPoTTttOFN == true){KPoTTttOFN = false;}
      if(AZUBdyShYt == true){AZUBdyShYt = false;}
      if(hFIUeNZzly == true){hFIUeNZzly = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZZECIPMAPJ
{ 
  void hZBhTTKnVe()
  { 
      bool CFKYzxAdYo = false;
      bool rXFBfmyIrA = false;
      bool gumKKCMdUf = false;
      bool LjjQaMLUIA = false;
      bool hCImzJbkXI = false;
      bool zBaIpGSAOx = false;
      bool jWJrdInoZS = false;
      bool bcAqSemzKA = false;
      bool ZbFLfJJbaU = false;
      bool tKGKQLrPJq = false;
      bool VmKEgVBipL = false;
      bool SSpNWIQyLT = false;
      bool yMNFYQWoaH = false;
      bool mWpSemRBdK = false;
      bool IZkOBaUrnI = false;
      bool tsDorIYFfP = false;
      bool yLHiXwcWhi = false;
      bool pPTBKXazDx = false;
      bool weASMsTAaV = false;
      bool OMUOLxSCqF = false;
      string LPgHnYMLwf;
      string xBNJOpealp;
      string cdtfSqQrmc;
      string RVqgINbrGC;
      string hqkliUlUnz;
      string eXptlhVBox;
      string HUXTNbKgAA;
      string NmUjIkrHwy;
      string EwEnxsfwta;
      string rZDJtNSQXH;
      string JETmkrDFlB;
      string oNEprLQjVU;
      string uNmZImiKpu;
      string RbjonAbQCF;
      string pZKskeUMQi;
      string wiuDLwRtey;
      string JrPqiNcPCr;
      string izhQdVDsnc;
      string RVtHyifgcr;
      string hglEwyKTJX;
      if(LPgHnYMLwf == JETmkrDFlB){CFKYzxAdYo = true;}
      else if(JETmkrDFlB == LPgHnYMLwf){VmKEgVBipL = true;}
      if(xBNJOpealp == oNEprLQjVU){rXFBfmyIrA = true;}
      else if(oNEprLQjVU == xBNJOpealp){SSpNWIQyLT = true;}
      if(cdtfSqQrmc == uNmZImiKpu){gumKKCMdUf = true;}
      else if(uNmZImiKpu == cdtfSqQrmc){yMNFYQWoaH = true;}
      if(RVqgINbrGC == RbjonAbQCF){LjjQaMLUIA = true;}
      else if(RbjonAbQCF == RVqgINbrGC){mWpSemRBdK = true;}
      if(hqkliUlUnz == pZKskeUMQi){hCImzJbkXI = true;}
      else if(pZKskeUMQi == hqkliUlUnz){IZkOBaUrnI = true;}
      if(eXptlhVBox == wiuDLwRtey){zBaIpGSAOx = true;}
      else if(wiuDLwRtey == eXptlhVBox){tsDorIYFfP = true;}
      if(HUXTNbKgAA == JrPqiNcPCr){jWJrdInoZS = true;}
      else if(JrPqiNcPCr == HUXTNbKgAA){yLHiXwcWhi = true;}
      if(NmUjIkrHwy == izhQdVDsnc){bcAqSemzKA = true;}
      if(EwEnxsfwta == RVtHyifgcr){ZbFLfJJbaU = true;}
      if(rZDJtNSQXH == hglEwyKTJX){tKGKQLrPJq = true;}
      while(izhQdVDsnc == NmUjIkrHwy){pPTBKXazDx = true;}
      while(RVtHyifgcr == RVtHyifgcr){weASMsTAaV = true;}
      while(hglEwyKTJX == hglEwyKTJX){OMUOLxSCqF = true;}
      if(CFKYzxAdYo == true){CFKYzxAdYo = false;}
      if(rXFBfmyIrA == true){rXFBfmyIrA = false;}
      if(gumKKCMdUf == true){gumKKCMdUf = false;}
      if(LjjQaMLUIA == true){LjjQaMLUIA = false;}
      if(hCImzJbkXI == true){hCImzJbkXI = false;}
      if(zBaIpGSAOx == true){zBaIpGSAOx = false;}
      if(jWJrdInoZS == true){jWJrdInoZS = false;}
      if(bcAqSemzKA == true){bcAqSemzKA = false;}
      if(ZbFLfJJbaU == true){ZbFLfJJbaU = false;}
      if(tKGKQLrPJq == true){tKGKQLrPJq = false;}
      if(VmKEgVBipL == true){VmKEgVBipL = false;}
      if(SSpNWIQyLT == true){SSpNWIQyLT = false;}
      if(yMNFYQWoaH == true){yMNFYQWoaH = false;}
      if(mWpSemRBdK == true){mWpSemRBdK = false;}
      if(IZkOBaUrnI == true){IZkOBaUrnI = false;}
      if(tsDorIYFfP == true){tsDorIYFfP = false;}
      if(yLHiXwcWhi == true){yLHiXwcWhi = false;}
      if(pPTBKXazDx == true){pPTBKXazDx = false;}
      if(weASMsTAaV == true){weASMsTAaV = false;}
      if(OMUOLxSCqF == true){OMUOLxSCqF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MBPMQGBIMK
{ 
  void SglbMkggtC()
  { 
      bool DGlShdoWHu = false;
      bool ARYlQdWEkF = false;
      bool WnfqRyuwsm = false;
      bool nHShqkTofw = false;
      bool cepJmawKnI = false;
      bool cCMLVPZtBj = false;
      bool isdUGsypte = false;
      bool JhYocrxWDp = false;
      bool BjIkJluHMa = false;
      bool KZnuMiAVCt = false;
      bool cGPIyucXhc = false;
      bool RCpLizkrKT = false;
      bool yqdTTjsdbs = false;
      bool qaUJNuTzlO = false;
      bool JWYiJHicMN = false;
      bool yILhwkbwnN = false;
      bool Byuokqhgym = false;
      bool fkFuKaRtKL = false;
      bool BQROtiPlNb = false;
      bool SWKXMKbjyR = false;
      string khmqSquWcz;
      string fqKXWSkbwE;
      string hwqAHrqZEw;
      string hANPjNKYIp;
      string NVlgruVebz;
      string Sjpxsopmja;
      string zURfRfcunJ;
      string HLTGpMKJHL;
      string VLxEcxJPVu;
      string WXohpsDFPM;
      string SaqSrGQiHg;
      string dgfXEnWNCT;
      string VMYrljWkQw;
      string IEtustUdMW;
      string fZIoRpqQcC;
      string WpDupFBzgI;
      string jfSKXYlkeK;
      string TrAfnuEjau;
      string rFINZRByEn;
      string sUxElAGxQr;
      if(khmqSquWcz == SaqSrGQiHg){DGlShdoWHu = true;}
      else if(SaqSrGQiHg == khmqSquWcz){cGPIyucXhc = true;}
      if(fqKXWSkbwE == dgfXEnWNCT){ARYlQdWEkF = true;}
      else if(dgfXEnWNCT == fqKXWSkbwE){RCpLizkrKT = true;}
      if(hwqAHrqZEw == VMYrljWkQw){WnfqRyuwsm = true;}
      else if(VMYrljWkQw == hwqAHrqZEw){yqdTTjsdbs = true;}
      if(hANPjNKYIp == IEtustUdMW){nHShqkTofw = true;}
      else if(IEtustUdMW == hANPjNKYIp){qaUJNuTzlO = true;}
      if(NVlgruVebz == fZIoRpqQcC){cepJmawKnI = true;}
      else if(fZIoRpqQcC == NVlgruVebz){JWYiJHicMN = true;}
      if(Sjpxsopmja == WpDupFBzgI){cCMLVPZtBj = true;}
      else if(WpDupFBzgI == Sjpxsopmja){yILhwkbwnN = true;}
      if(zURfRfcunJ == jfSKXYlkeK){isdUGsypte = true;}
      else if(jfSKXYlkeK == zURfRfcunJ){Byuokqhgym = true;}
      if(HLTGpMKJHL == TrAfnuEjau){JhYocrxWDp = true;}
      if(VLxEcxJPVu == rFINZRByEn){BjIkJluHMa = true;}
      if(WXohpsDFPM == sUxElAGxQr){KZnuMiAVCt = true;}
      while(TrAfnuEjau == HLTGpMKJHL){fkFuKaRtKL = true;}
      while(rFINZRByEn == rFINZRByEn){BQROtiPlNb = true;}
      while(sUxElAGxQr == sUxElAGxQr){SWKXMKbjyR = true;}
      if(DGlShdoWHu == true){DGlShdoWHu = false;}
      if(ARYlQdWEkF == true){ARYlQdWEkF = false;}
      if(WnfqRyuwsm == true){WnfqRyuwsm = false;}
      if(nHShqkTofw == true){nHShqkTofw = false;}
      if(cepJmawKnI == true){cepJmawKnI = false;}
      if(cCMLVPZtBj == true){cCMLVPZtBj = false;}
      if(isdUGsypte == true){isdUGsypte = false;}
      if(JhYocrxWDp == true){JhYocrxWDp = false;}
      if(BjIkJluHMa == true){BjIkJluHMa = false;}
      if(KZnuMiAVCt == true){KZnuMiAVCt = false;}
      if(cGPIyucXhc == true){cGPIyucXhc = false;}
      if(RCpLizkrKT == true){RCpLizkrKT = false;}
      if(yqdTTjsdbs == true){yqdTTjsdbs = false;}
      if(qaUJNuTzlO == true){qaUJNuTzlO = false;}
      if(JWYiJHicMN == true){JWYiJHicMN = false;}
      if(yILhwkbwnN == true){yILhwkbwnN = false;}
      if(Byuokqhgym == true){Byuokqhgym = false;}
      if(fkFuKaRtKL == true){fkFuKaRtKL = false;}
      if(BQROtiPlNb == true){BQROtiPlNb = false;}
      if(SWKXMKbjyR == true){SWKXMKbjyR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DMGHEZEMNS
{ 
  void Refzptgadl()
  { 
      bool RdlXmfaAmq = false;
      bool YgkAJoNPot = false;
      bool wyIsWSxjCB = false;
      bool fjrfaSIqFj = false;
      bool mnwighxxbT = false;
      bool wGWtATVrBU = false;
      bool iqylLnoFYp = false;
      bool gVKFGHBZMn = false;
      bool UzHiEYNxeH = false;
      bool xQpjBupKWr = false;
      bool srYklawRms = false;
      bool RwfMziiOgl = false;
      bool arZQsQeZEL = false;
      bool QqCTucaVwc = false;
      bool buJloAjdkR = false;
      bool MackQASHrV = false;
      bool uVNbbatLRW = false;
      bool IMSDJfimar = false;
      bool fBolyoNQDt = false;
      bool KTdZgGhgKO = false;
      string BTZcynqPdd;
      string iJAEalxKZn;
      string uwTbkMVZwR;
      string pfZEZQNELF;
      string fbdleVpBwn;
      string IAKHmFzyql;
      string RQTMnDiwdK;
      string YsyUHSRhwP;
      string WTdHIoUSRU;
      string RONYmOIQyb;
      string msXlPPCpzT;
      string mRCbPymMEy;
      string hQeJrJfYgs;
      string KBiTbcwqqs;
      string meSygzMkJo;
      string bwMztVNNsG;
      string jcIGIkhhzl;
      string BuULLCxgbs;
      string xtPrQOojZF;
      string PiykIKWMow;
      if(BTZcynqPdd == msXlPPCpzT){RdlXmfaAmq = true;}
      else if(msXlPPCpzT == BTZcynqPdd){srYklawRms = true;}
      if(iJAEalxKZn == mRCbPymMEy){YgkAJoNPot = true;}
      else if(mRCbPymMEy == iJAEalxKZn){RwfMziiOgl = true;}
      if(uwTbkMVZwR == hQeJrJfYgs){wyIsWSxjCB = true;}
      else if(hQeJrJfYgs == uwTbkMVZwR){arZQsQeZEL = true;}
      if(pfZEZQNELF == KBiTbcwqqs){fjrfaSIqFj = true;}
      else if(KBiTbcwqqs == pfZEZQNELF){QqCTucaVwc = true;}
      if(fbdleVpBwn == meSygzMkJo){mnwighxxbT = true;}
      else if(meSygzMkJo == fbdleVpBwn){buJloAjdkR = true;}
      if(IAKHmFzyql == bwMztVNNsG){wGWtATVrBU = true;}
      else if(bwMztVNNsG == IAKHmFzyql){MackQASHrV = true;}
      if(RQTMnDiwdK == jcIGIkhhzl){iqylLnoFYp = true;}
      else if(jcIGIkhhzl == RQTMnDiwdK){uVNbbatLRW = true;}
      if(YsyUHSRhwP == BuULLCxgbs){gVKFGHBZMn = true;}
      if(WTdHIoUSRU == xtPrQOojZF){UzHiEYNxeH = true;}
      if(RONYmOIQyb == PiykIKWMow){xQpjBupKWr = true;}
      while(BuULLCxgbs == YsyUHSRhwP){IMSDJfimar = true;}
      while(xtPrQOojZF == xtPrQOojZF){fBolyoNQDt = true;}
      while(PiykIKWMow == PiykIKWMow){KTdZgGhgKO = true;}
      if(RdlXmfaAmq == true){RdlXmfaAmq = false;}
      if(YgkAJoNPot == true){YgkAJoNPot = false;}
      if(wyIsWSxjCB == true){wyIsWSxjCB = false;}
      if(fjrfaSIqFj == true){fjrfaSIqFj = false;}
      if(mnwighxxbT == true){mnwighxxbT = false;}
      if(wGWtATVrBU == true){wGWtATVrBU = false;}
      if(iqylLnoFYp == true){iqylLnoFYp = false;}
      if(gVKFGHBZMn == true){gVKFGHBZMn = false;}
      if(UzHiEYNxeH == true){UzHiEYNxeH = false;}
      if(xQpjBupKWr == true){xQpjBupKWr = false;}
      if(srYklawRms == true){srYklawRms = false;}
      if(RwfMziiOgl == true){RwfMziiOgl = false;}
      if(arZQsQeZEL == true){arZQsQeZEL = false;}
      if(QqCTucaVwc == true){QqCTucaVwc = false;}
      if(buJloAjdkR == true){buJloAjdkR = false;}
      if(MackQASHrV == true){MackQASHrV = false;}
      if(uVNbbatLRW == true){uVNbbatLRW = false;}
      if(IMSDJfimar == true){IMSDJfimar = false;}
      if(fBolyoNQDt == true){fBolyoNQDt = false;}
      if(KTdZgGhgKO == true){KTdZgGhgKO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DDUHPCMSJX
{ 
  void mKQRqXFTdC()
  { 
      bool wOAgAEPwjg = false;
      bool lZEeSGgTEE = false;
      bool JhqMKkUJrd = false;
      bool MWZtcPKhOn = false;
      bool wGGwXcTSbL = false;
      bool WPeGdOXmVO = false;
      bool iFDFUOzKBD = false;
      bool uyEPIDbuoh = false;
      bool RChgGxrSPO = false;
      bool rWMAFpCAbI = false;
      bool dJQYPXKOyZ = false;
      bool mcynxfXWzX = false;
      bool VftmKYlEJS = false;
      bool BaTfDHkJQh = false;
      bool ldUoaPYYDY = false;
      bool SeBDmyOcNq = false;
      bool lGEeYLJRjo = false;
      bool uNGQkrKELu = false;
      bool zNAkAVYPsF = false;
      bool rIwYwfYpQP = false;
      string WgVwVMUzuc;
      string koKJoVlUqT;
      string UospoEIzuQ;
      string prLVDqsEnj;
      string NVelmIPbxo;
      string gkPSugnfGR;
      string DVDdlsdnFy;
      string bgfGGyKHCg;
      string ogBGjEcrZW;
      string CNxWgqSBzt;
      string daVzMAEJMx;
      string VgcZbVUxtg;
      string PlOiuOiJZP;
      string fJHICOLBsi;
      string zTfcAVjXtK;
      string WUGRdrLmEy;
      string RuiwQMYUWN;
      string KSEKhwGlhZ;
      string eKOOrLCpdK;
      string CYxtRDjiLn;
      if(WgVwVMUzuc == daVzMAEJMx){wOAgAEPwjg = true;}
      else if(daVzMAEJMx == WgVwVMUzuc){dJQYPXKOyZ = true;}
      if(koKJoVlUqT == VgcZbVUxtg){lZEeSGgTEE = true;}
      else if(VgcZbVUxtg == koKJoVlUqT){mcynxfXWzX = true;}
      if(UospoEIzuQ == PlOiuOiJZP){JhqMKkUJrd = true;}
      else if(PlOiuOiJZP == UospoEIzuQ){VftmKYlEJS = true;}
      if(prLVDqsEnj == fJHICOLBsi){MWZtcPKhOn = true;}
      else if(fJHICOLBsi == prLVDqsEnj){BaTfDHkJQh = true;}
      if(NVelmIPbxo == zTfcAVjXtK){wGGwXcTSbL = true;}
      else if(zTfcAVjXtK == NVelmIPbxo){ldUoaPYYDY = true;}
      if(gkPSugnfGR == WUGRdrLmEy){WPeGdOXmVO = true;}
      else if(WUGRdrLmEy == gkPSugnfGR){SeBDmyOcNq = true;}
      if(DVDdlsdnFy == RuiwQMYUWN){iFDFUOzKBD = true;}
      else if(RuiwQMYUWN == DVDdlsdnFy){lGEeYLJRjo = true;}
      if(bgfGGyKHCg == KSEKhwGlhZ){uyEPIDbuoh = true;}
      if(ogBGjEcrZW == eKOOrLCpdK){RChgGxrSPO = true;}
      if(CNxWgqSBzt == CYxtRDjiLn){rWMAFpCAbI = true;}
      while(KSEKhwGlhZ == bgfGGyKHCg){uNGQkrKELu = true;}
      while(eKOOrLCpdK == eKOOrLCpdK){zNAkAVYPsF = true;}
      while(CYxtRDjiLn == CYxtRDjiLn){rIwYwfYpQP = true;}
      if(wOAgAEPwjg == true){wOAgAEPwjg = false;}
      if(lZEeSGgTEE == true){lZEeSGgTEE = false;}
      if(JhqMKkUJrd == true){JhqMKkUJrd = false;}
      if(MWZtcPKhOn == true){MWZtcPKhOn = false;}
      if(wGGwXcTSbL == true){wGGwXcTSbL = false;}
      if(WPeGdOXmVO == true){WPeGdOXmVO = false;}
      if(iFDFUOzKBD == true){iFDFUOzKBD = false;}
      if(uyEPIDbuoh == true){uyEPIDbuoh = false;}
      if(RChgGxrSPO == true){RChgGxrSPO = false;}
      if(rWMAFpCAbI == true){rWMAFpCAbI = false;}
      if(dJQYPXKOyZ == true){dJQYPXKOyZ = false;}
      if(mcynxfXWzX == true){mcynxfXWzX = false;}
      if(VftmKYlEJS == true){VftmKYlEJS = false;}
      if(BaTfDHkJQh == true){BaTfDHkJQh = false;}
      if(ldUoaPYYDY == true){ldUoaPYYDY = false;}
      if(SeBDmyOcNq == true){SeBDmyOcNq = false;}
      if(lGEeYLJRjo == true){lGEeYLJRjo = false;}
      if(uNGQkrKELu == true){uNGQkrKELu = false;}
      if(zNAkAVYPsF == true){zNAkAVYPsF = false;}
      if(rIwYwfYpQP == true){rIwYwfYpQP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BDLVQWODOK
{ 
  void QwenmUdFTN()
  { 
      bool UBWfxfkCpV = false;
      bool nTgpyiEpmg = false;
      bool gRjkoFVmkU = false;
      bool clkfsUcUup = false;
      bool fNJprgkxiY = false;
      bool WdsTkCRlqr = false;
      bool KxRUrChBxc = false;
      bool GjuxBSHsrI = false;
      bool TXDLyzsRtp = false;
      bool DqdDfhwoxp = false;
      bool yizGSlhuRR = false;
      bool uXsiXlsFWr = false;
      bool JQHHYOGqRS = false;
      bool WSuCJjYxrL = false;
      bool Qxzbtfyues = false;
      bool npREghbrgE = false;
      bool fqdyucbpYn = false;
      bool MwNKbLQeMs = false;
      bool QLMXegAqVb = false;
      bool HgQneZTBgR = false;
      string gOkBsrnkOQ;
      string yFoYqniJMp;
      string jaGMqwcqXQ;
      string dAijhzwCRG;
      string nmfCPlwjuh;
      string CUBXQGIXJx;
      string OxMylxVEpq;
      string rfqFCxuDxE;
      string zrupNJyLTb;
      string qXsUrqagPR;
      string QrtDoVcwUT;
      string LEaFxWBVkc;
      string zJkOzTmWNL;
      string VNmenHyrBq;
      string gCpzQlxnWU;
      string oEwmSHGeEU;
      string iFhJyyRwQp;
      string XJTswxSlyN;
      string WzArVQQALf;
      string BSngIaTgAS;
      if(gOkBsrnkOQ == QrtDoVcwUT){UBWfxfkCpV = true;}
      else if(QrtDoVcwUT == gOkBsrnkOQ){yizGSlhuRR = true;}
      if(yFoYqniJMp == LEaFxWBVkc){nTgpyiEpmg = true;}
      else if(LEaFxWBVkc == yFoYqniJMp){uXsiXlsFWr = true;}
      if(jaGMqwcqXQ == zJkOzTmWNL){gRjkoFVmkU = true;}
      else if(zJkOzTmWNL == jaGMqwcqXQ){JQHHYOGqRS = true;}
      if(dAijhzwCRG == VNmenHyrBq){clkfsUcUup = true;}
      else if(VNmenHyrBq == dAijhzwCRG){WSuCJjYxrL = true;}
      if(nmfCPlwjuh == gCpzQlxnWU){fNJprgkxiY = true;}
      else if(gCpzQlxnWU == nmfCPlwjuh){Qxzbtfyues = true;}
      if(CUBXQGIXJx == oEwmSHGeEU){WdsTkCRlqr = true;}
      else if(oEwmSHGeEU == CUBXQGIXJx){npREghbrgE = true;}
      if(OxMylxVEpq == iFhJyyRwQp){KxRUrChBxc = true;}
      else if(iFhJyyRwQp == OxMylxVEpq){fqdyucbpYn = true;}
      if(rfqFCxuDxE == XJTswxSlyN){GjuxBSHsrI = true;}
      if(zrupNJyLTb == WzArVQQALf){TXDLyzsRtp = true;}
      if(qXsUrqagPR == BSngIaTgAS){DqdDfhwoxp = true;}
      while(XJTswxSlyN == rfqFCxuDxE){MwNKbLQeMs = true;}
      while(WzArVQQALf == WzArVQQALf){QLMXegAqVb = true;}
      while(BSngIaTgAS == BSngIaTgAS){HgQneZTBgR = true;}
      if(UBWfxfkCpV == true){UBWfxfkCpV = false;}
      if(nTgpyiEpmg == true){nTgpyiEpmg = false;}
      if(gRjkoFVmkU == true){gRjkoFVmkU = false;}
      if(clkfsUcUup == true){clkfsUcUup = false;}
      if(fNJprgkxiY == true){fNJprgkxiY = false;}
      if(WdsTkCRlqr == true){WdsTkCRlqr = false;}
      if(KxRUrChBxc == true){KxRUrChBxc = false;}
      if(GjuxBSHsrI == true){GjuxBSHsrI = false;}
      if(TXDLyzsRtp == true){TXDLyzsRtp = false;}
      if(DqdDfhwoxp == true){DqdDfhwoxp = false;}
      if(yizGSlhuRR == true){yizGSlhuRR = false;}
      if(uXsiXlsFWr == true){uXsiXlsFWr = false;}
      if(JQHHYOGqRS == true){JQHHYOGqRS = false;}
      if(WSuCJjYxrL == true){WSuCJjYxrL = false;}
      if(Qxzbtfyues == true){Qxzbtfyues = false;}
      if(npREghbrgE == true){npREghbrgE = false;}
      if(fqdyucbpYn == true){fqdyucbpYn = false;}
      if(MwNKbLQeMs == true){MwNKbLQeMs = false;}
      if(QLMXegAqVb == true){QLMXegAqVb = false;}
      if(HgQneZTBgR == true){HgQneZTBgR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZHCQEONWPH
{ 
  void wqlhlzeNVA()
  { 
      bool TZuwiAxIwu = false;
      bool SXSadGqIXH = false;
      bool BROQNmCUEE = false;
      bool YJCJMJDpZr = false;
      bool jjwXPLGcOD = false;
      bool JHuhHBLdiw = false;
      bool ybErWIVJOT = false;
      bool DAhfWQVpBB = false;
      bool fZGAtQNTBK = false;
      bool yYHdtIfDBG = false;
      bool pxNuAJZPLq = false;
      bool eUcgPYVDxG = false;
      bool uBIDUerElO = false;
      bool jRouLiLLAj = false;
      bool pyIJedwaNV = false;
      bool lcGtLooKZU = false;
      bool QUdxHNehVg = false;
      bool NKCMPwryYq = false;
      bool iRpQbGLtjV = false;
      bool sBlfTUTKBR = false;
      string BcrzGFiwZy;
      string fPOjNjSEou;
      string sSrtZSMnLf;
      string YEwaxUtzfN;
      string URxLigcsKx;
      string RizrLhkyYn;
      string rujsZbTnls;
      string oSYbZbVfLs;
      string oScOOoFDPP;
      string iwZrVZgDlG;
      string NoHRHyKXRj;
      string MEmeyYRUej;
      string WPXVKssgFA;
      string tRtEfALLHP;
      string ehkfDdItsw;
      string HLXBjxQkHN;
      string FdRRotKizx;
      string NGNPFodrSf;
      string jymJshsrTh;
      string jZEsKBQTpI;
      if(BcrzGFiwZy == NoHRHyKXRj){TZuwiAxIwu = true;}
      else if(NoHRHyKXRj == BcrzGFiwZy){pxNuAJZPLq = true;}
      if(fPOjNjSEou == MEmeyYRUej){SXSadGqIXH = true;}
      else if(MEmeyYRUej == fPOjNjSEou){eUcgPYVDxG = true;}
      if(sSrtZSMnLf == WPXVKssgFA){BROQNmCUEE = true;}
      else if(WPXVKssgFA == sSrtZSMnLf){uBIDUerElO = true;}
      if(YEwaxUtzfN == tRtEfALLHP){YJCJMJDpZr = true;}
      else if(tRtEfALLHP == YEwaxUtzfN){jRouLiLLAj = true;}
      if(URxLigcsKx == ehkfDdItsw){jjwXPLGcOD = true;}
      else if(ehkfDdItsw == URxLigcsKx){pyIJedwaNV = true;}
      if(RizrLhkyYn == HLXBjxQkHN){JHuhHBLdiw = true;}
      else if(HLXBjxQkHN == RizrLhkyYn){lcGtLooKZU = true;}
      if(rujsZbTnls == FdRRotKizx){ybErWIVJOT = true;}
      else if(FdRRotKizx == rujsZbTnls){QUdxHNehVg = true;}
      if(oSYbZbVfLs == NGNPFodrSf){DAhfWQVpBB = true;}
      if(oScOOoFDPP == jymJshsrTh){fZGAtQNTBK = true;}
      if(iwZrVZgDlG == jZEsKBQTpI){yYHdtIfDBG = true;}
      while(NGNPFodrSf == oSYbZbVfLs){NKCMPwryYq = true;}
      while(jymJshsrTh == jymJshsrTh){iRpQbGLtjV = true;}
      while(jZEsKBQTpI == jZEsKBQTpI){sBlfTUTKBR = true;}
      if(TZuwiAxIwu == true){TZuwiAxIwu = false;}
      if(SXSadGqIXH == true){SXSadGqIXH = false;}
      if(BROQNmCUEE == true){BROQNmCUEE = false;}
      if(YJCJMJDpZr == true){YJCJMJDpZr = false;}
      if(jjwXPLGcOD == true){jjwXPLGcOD = false;}
      if(JHuhHBLdiw == true){JHuhHBLdiw = false;}
      if(ybErWIVJOT == true){ybErWIVJOT = false;}
      if(DAhfWQVpBB == true){DAhfWQVpBB = false;}
      if(fZGAtQNTBK == true){fZGAtQNTBK = false;}
      if(yYHdtIfDBG == true){yYHdtIfDBG = false;}
      if(pxNuAJZPLq == true){pxNuAJZPLq = false;}
      if(eUcgPYVDxG == true){eUcgPYVDxG = false;}
      if(uBIDUerElO == true){uBIDUerElO = false;}
      if(jRouLiLLAj == true){jRouLiLLAj = false;}
      if(pyIJedwaNV == true){pyIJedwaNV = false;}
      if(lcGtLooKZU == true){lcGtLooKZU = false;}
      if(QUdxHNehVg == true){QUdxHNehVg = false;}
      if(NKCMPwryYq == true){NKCMPwryYq = false;}
      if(iRpQbGLtjV == true){iRpQbGLtjV = false;}
      if(sBlfTUTKBR == true){sBlfTUTKBR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CTSZWTPBIZ
{ 
  void SdEGZodZVn()
  { 
      bool PVQWDtXuca = false;
      bool UkcpicBHwf = false;
      bool posqsolGWQ = false;
      bool nuwExMZQxn = false;
      bool szBXDDzHYQ = false;
      bool YfflBZcYdN = false;
      bool IRYMlZnXsW = false;
      bool CjKHlpnUmp = false;
      bool oegFqIOKDW = false;
      bool jAlifbaokd = false;
      bool ObNCOnVYzK = false;
      bool lHknYcjTUd = false;
      bool KcUWlByaaK = false;
      bool PziJaNReqD = false;
      bool mpLrkcOxKD = false;
      bool qHTHTkGpPM = false;
      bool ptxnulXbMK = false;
      bool KEbRqTRblJ = false;
      bool lAQXSHebop = false;
      bool GaPdMrrWwy = false;
      string MxWjcWjxQE;
      string FRpIqshhYl;
      string mWFxGozxQh;
      string zLfwLsjtON;
      string EHYfTMWwwY;
      string dBnbfprYdn;
      string XmfiEtkswx;
      string ImTKgexZct;
      string RCAqExWDPV;
      string BKQapRbpaZ;
      string acAzQphcuB;
      string rRwiVUlodG;
      string WgdZwyWsUO;
      string DGyDSnCBaN;
      string PtIOciOgEU;
      string flLTDtzZDS;
      string ToHfxkTsQg;
      string RkOQqbYOwM;
      string ipnAiRudzY;
      string ncyItZmcRr;
      if(MxWjcWjxQE == acAzQphcuB){PVQWDtXuca = true;}
      else if(acAzQphcuB == MxWjcWjxQE){ObNCOnVYzK = true;}
      if(FRpIqshhYl == rRwiVUlodG){UkcpicBHwf = true;}
      else if(rRwiVUlodG == FRpIqshhYl){lHknYcjTUd = true;}
      if(mWFxGozxQh == WgdZwyWsUO){posqsolGWQ = true;}
      else if(WgdZwyWsUO == mWFxGozxQh){KcUWlByaaK = true;}
      if(zLfwLsjtON == DGyDSnCBaN){nuwExMZQxn = true;}
      else if(DGyDSnCBaN == zLfwLsjtON){PziJaNReqD = true;}
      if(EHYfTMWwwY == PtIOciOgEU){szBXDDzHYQ = true;}
      else if(PtIOciOgEU == EHYfTMWwwY){mpLrkcOxKD = true;}
      if(dBnbfprYdn == flLTDtzZDS){YfflBZcYdN = true;}
      else if(flLTDtzZDS == dBnbfprYdn){qHTHTkGpPM = true;}
      if(XmfiEtkswx == ToHfxkTsQg){IRYMlZnXsW = true;}
      else if(ToHfxkTsQg == XmfiEtkswx){ptxnulXbMK = true;}
      if(ImTKgexZct == RkOQqbYOwM){CjKHlpnUmp = true;}
      if(RCAqExWDPV == ipnAiRudzY){oegFqIOKDW = true;}
      if(BKQapRbpaZ == ncyItZmcRr){jAlifbaokd = true;}
      while(RkOQqbYOwM == ImTKgexZct){KEbRqTRblJ = true;}
      while(ipnAiRudzY == ipnAiRudzY){lAQXSHebop = true;}
      while(ncyItZmcRr == ncyItZmcRr){GaPdMrrWwy = true;}
      if(PVQWDtXuca == true){PVQWDtXuca = false;}
      if(UkcpicBHwf == true){UkcpicBHwf = false;}
      if(posqsolGWQ == true){posqsolGWQ = false;}
      if(nuwExMZQxn == true){nuwExMZQxn = false;}
      if(szBXDDzHYQ == true){szBXDDzHYQ = false;}
      if(YfflBZcYdN == true){YfflBZcYdN = false;}
      if(IRYMlZnXsW == true){IRYMlZnXsW = false;}
      if(CjKHlpnUmp == true){CjKHlpnUmp = false;}
      if(oegFqIOKDW == true){oegFqIOKDW = false;}
      if(jAlifbaokd == true){jAlifbaokd = false;}
      if(ObNCOnVYzK == true){ObNCOnVYzK = false;}
      if(lHknYcjTUd == true){lHknYcjTUd = false;}
      if(KcUWlByaaK == true){KcUWlByaaK = false;}
      if(PziJaNReqD == true){PziJaNReqD = false;}
      if(mpLrkcOxKD == true){mpLrkcOxKD = false;}
      if(qHTHTkGpPM == true){qHTHTkGpPM = false;}
      if(ptxnulXbMK == true){ptxnulXbMK = false;}
      if(KEbRqTRblJ == true){KEbRqTRblJ = false;}
      if(lAQXSHebop == true){lAQXSHebop = false;}
      if(GaPdMrrWwy == true){GaPdMrrWwy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MOXZUUAPXA
{ 
  void lzPMpstXEe()
  { 
      bool gEIkpagGyF = false;
      bool qjcuWFupZm = false;
      bool PIorZJGnxm = false;
      bool JdKqRDXoXi = false;
      bool urFAiPKtbX = false;
      bool dDSGZYPQLg = false;
      bool UsIKuMZkdS = false;
      bool gGRqqWCoIK = false;
      bool yLLZJGKDRr = false;
      bool nHcqNCjuEW = false;
      bool pYQIqWkaPC = false;
      bool WZIAhJhiBo = false;
      bool CVTkeZcZdo = false;
      bool lHjlTYtDim = false;
      bool UinOVNzcJE = false;
      bool UBtPTTFfdQ = false;
      bool sLxZQOoVfJ = false;
      bool OdANUShFPQ = false;
      bool aAQZUkNURA = false;
      bool TOYRsJkOyG = false;
      string AXmcrGaKHj;
      string MzKrtOjtEq;
      string HsNARkUXZA;
      string XBAWHfwshT;
      string FXieYNreBG;
      string mUsDyGJlKH;
      string kCkGLLymkO;
      string SqMkkjKhbD;
      string spWSNDHwYA;
      string VJhZhDlbSM;
      string PEsmnuIISN;
      string wbJGOtfRsI;
      string DBOjsIIlCh;
      string xhOOnoxjeR;
      string uzdKDtzaLn;
      string XUhKJNoItf;
      string mVFkPOMuSZ;
      string xwmbMEWEfy;
      string IgZOKczEFZ;
      string znozdYtsto;
      if(AXmcrGaKHj == PEsmnuIISN){gEIkpagGyF = true;}
      else if(PEsmnuIISN == AXmcrGaKHj){pYQIqWkaPC = true;}
      if(MzKrtOjtEq == wbJGOtfRsI){qjcuWFupZm = true;}
      else if(wbJGOtfRsI == MzKrtOjtEq){WZIAhJhiBo = true;}
      if(HsNARkUXZA == DBOjsIIlCh){PIorZJGnxm = true;}
      else if(DBOjsIIlCh == HsNARkUXZA){CVTkeZcZdo = true;}
      if(XBAWHfwshT == xhOOnoxjeR){JdKqRDXoXi = true;}
      else if(xhOOnoxjeR == XBAWHfwshT){lHjlTYtDim = true;}
      if(FXieYNreBG == uzdKDtzaLn){urFAiPKtbX = true;}
      else if(uzdKDtzaLn == FXieYNreBG){UinOVNzcJE = true;}
      if(mUsDyGJlKH == XUhKJNoItf){dDSGZYPQLg = true;}
      else if(XUhKJNoItf == mUsDyGJlKH){UBtPTTFfdQ = true;}
      if(kCkGLLymkO == mVFkPOMuSZ){UsIKuMZkdS = true;}
      else if(mVFkPOMuSZ == kCkGLLymkO){sLxZQOoVfJ = true;}
      if(SqMkkjKhbD == xwmbMEWEfy){gGRqqWCoIK = true;}
      if(spWSNDHwYA == IgZOKczEFZ){yLLZJGKDRr = true;}
      if(VJhZhDlbSM == znozdYtsto){nHcqNCjuEW = true;}
      while(xwmbMEWEfy == SqMkkjKhbD){OdANUShFPQ = true;}
      while(IgZOKczEFZ == IgZOKczEFZ){aAQZUkNURA = true;}
      while(znozdYtsto == znozdYtsto){TOYRsJkOyG = true;}
      if(gEIkpagGyF == true){gEIkpagGyF = false;}
      if(qjcuWFupZm == true){qjcuWFupZm = false;}
      if(PIorZJGnxm == true){PIorZJGnxm = false;}
      if(JdKqRDXoXi == true){JdKqRDXoXi = false;}
      if(urFAiPKtbX == true){urFAiPKtbX = false;}
      if(dDSGZYPQLg == true){dDSGZYPQLg = false;}
      if(UsIKuMZkdS == true){UsIKuMZkdS = false;}
      if(gGRqqWCoIK == true){gGRqqWCoIK = false;}
      if(yLLZJGKDRr == true){yLLZJGKDRr = false;}
      if(nHcqNCjuEW == true){nHcqNCjuEW = false;}
      if(pYQIqWkaPC == true){pYQIqWkaPC = false;}
      if(WZIAhJhiBo == true){WZIAhJhiBo = false;}
      if(CVTkeZcZdo == true){CVTkeZcZdo = false;}
      if(lHjlTYtDim == true){lHjlTYtDim = false;}
      if(UinOVNzcJE == true){UinOVNzcJE = false;}
      if(UBtPTTFfdQ == true){UBtPTTFfdQ = false;}
      if(sLxZQOoVfJ == true){sLxZQOoVfJ = false;}
      if(OdANUShFPQ == true){OdANUShFPQ = false;}
      if(aAQZUkNURA == true){aAQZUkNURA = false;}
      if(TOYRsJkOyG == true){TOYRsJkOyG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SPREYOUZUW
{ 
  void IEmkpGJuJF()
  { 
      bool laYcfGHAzB = false;
      bool LycEIqGrKm = false;
      bool GHoeHhcVEx = false;
      bool fljFTYhjtR = false;
      bool BEmrIfCnQZ = false;
      bool YizFAektVx = false;
      bool ckuCUYOWkj = false;
      bool JVyslBTxWa = false;
      bool eoFdYxmdFn = false;
      bool mnOwnPJkWi = false;
      bool RfDfQCkFTy = false;
      bool LnXtSnfQdX = false;
      bool kjQwxVHCFW = false;
      bool riZmIykYNW = false;
      bool LgKGczPTcz = false;
      bool irGzxhOGiu = false;
      bool tiAxFcNjlU = false;
      bool CGDHLEZKTx = false;
      bool FmYFmAbaoa = false;
      bool iepRbcgMBA = false;
      string GYCtHXCrmG;
      string qoKQztatyi;
      string zguDtLybQD;
      string hLUueUryGC;
      string dHtbpTJGaS;
      string HkgpzZdyAw;
      string ZaajXfUOkd;
      string CcnuEqlTNZ;
      string BqAyuwdewF;
      string qtxKcDfKDK;
      string ytVxQdxkkH;
      string mKkZtiZcna;
      string BpSfmIedSB;
      string LbPCbHVDhR;
      string zssoSgIXPs;
      string cCWbJIboKI;
      string zTRiuLthym;
      string NWuWbHwcMF;
      string zHNZXIEmsT;
      string efsZReaKsH;
      if(GYCtHXCrmG == ytVxQdxkkH){laYcfGHAzB = true;}
      else if(ytVxQdxkkH == GYCtHXCrmG){RfDfQCkFTy = true;}
      if(qoKQztatyi == mKkZtiZcna){LycEIqGrKm = true;}
      else if(mKkZtiZcna == qoKQztatyi){LnXtSnfQdX = true;}
      if(zguDtLybQD == BpSfmIedSB){GHoeHhcVEx = true;}
      else if(BpSfmIedSB == zguDtLybQD){kjQwxVHCFW = true;}
      if(hLUueUryGC == LbPCbHVDhR){fljFTYhjtR = true;}
      else if(LbPCbHVDhR == hLUueUryGC){riZmIykYNW = true;}
      if(dHtbpTJGaS == zssoSgIXPs){BEmrIfCnQZ = true;}
      else if(zssoSgIXPs == dHtbpTJGaS){LgKGczPTcz = true;}
      if(HkgpzZdyAw == cCWbJIboKI){YizFAektVx = true;}
      else if(cCWbJIboKI == HkgpzZdyAw){irGzxhOGiu = true;}
      if(ZaajXfUOkd == zTRiuLthym){ckuCUYOWkj = true;}
      else if(zTRiuLthym == ZaajXfUOkd){tiAxFcNjlU = true;}
      if(CcnuEqlTNZ == NWuWbHwcMF){JVyslBTxWa = true;}
      if(BqAyuwdewF == zHNZXIEmsT){eoFdYxmdFn = true;}
      if(qtxKcDfKDK == efsZReaKsH){mnOwnPJkWi = true;}
      while(NWuWbHwcMF == CcnuEqlTNZ){CGDHLEZKTx = true;}
      while(zHNZXIEmsT == zHNZXIEmsT){FmYFmAbaoa = true;}
      while(efsZReaKsH == efsZReaKsH){iepRbcgMBA = true;}
      if(laYcfGHAzB == true){laYcfGHAzB = false;}
      if(LycEIqGrKm == true){LycEIqGrKm = false;}
      if(GHoeHhcVEx == true){GHoeHhcVEx = false;}
      if(fljFTYhjtR == true){fljFTYhjtR = false;}
      if(BEmrIfCnQZ == true){BEmrIfCnQZ = false;}
      if(YizFAektVx == true){YizFAektVx = false;}
      if(ckuCUYOWkj == true){ckuCUYOWkj = false;}
      if(JVyslBTxWa == true){JVyslBTxWa = false;}
      if(eoFdYxmdFn == true){eoFdYxmdFn = false;}
      if(mnOwnPJkWi == true){mnOwnPJkWi = false;}
      if(RfDfQCkFTy == true){RfDfQCkFTy = false;}
      if(LnXtSnfQdX == true){LnXtSnfQdX = false;}
      if(kjQwxVHCFW == true){kjQwxVHCFW = false;}
      if(riZmIykYNW == true){riZmIykYNW = false;}
      if(LgKGczPTcz == true){LgKGczPTcz = false;}
      if(irGzxhOGiu == true){irGzxhOGiu = false;}
      if(tiAxFcNjlU == true){tiAxFcNjlU = false;}
      if(CGDHLEZKTx == true){CGDHLEZKTx = false;}
      if(FmYFmAbaoa == true){FmYFmAbaoa = false;}
      if(iepRbcgMBA == true){iepRbcgMBA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NQGHXQEYAW
{ 
  void VYZfHxSlMB()
  { 
      bool FpDpeVgPxU = false;
      bool GKoubfVxGq = false;
      bool ODSLWWwJRG = false;
      bool cRJTdbYbpE = false;
      bool DuigXfJXHm = false;
      bool glDGlBXqSI = false;
      bool YXypqoAVQA = false;
      bool HtHCnTTknp = false;
      bool MXBdZqNDgc = false;
      bool DgIhefwsoh = false;
      bool fnGHfmeBSS = false;
      bool glCcuBVTQA = false;
      bool axnnwakYWH = false;
      bool WauGKXRtyl = false;
      bool LMkNwRdfld = false;
      bool JcboHhzSKE = false;
      bool CFdKuFpwRX = false;
      bool jbUeoNMZre = false;
      bool wFmrytyGyb = false;
      bool XyisiFhaSp = false;
      string lrhhrlSueP;
      string CyUuiAeElg;
      string oTQsSLmzUH;
      string JqsUhrFLHf;
      string TboQJFBUuR;
      string yHwHDSaoOg;
      string ySaXFKEAMq;
      string tSwFNNeAiM;
      string KRDCICtlRP;
      string QQwahAAQKy;
      string BBHEXfKqtp;
      string naFCWfOYOC;
      string QSixZcWVXM;
      string MNojLIJyec;
      string rDqabpLtDB;
      string lbCIhhRKet;
      string InTgcZkUpN;
      string VPtlKNaHUi;
      string RcRVakLgCd;
      string qzTjTDjJyB;
      if(lrhhrlSueP == BBHEXfKqtp){FpDpeVgPxU = true;}
      else if(BBHEXfKqtp == lrhhrlSueP){fnGHfmeBSS = true;}
      if(CyUuiAeElg == naFCWfOYOC){GKoubfVxGq = true;}
      else if(naFCWfOYOC == CyUuiAeElg){glCcuBVTQA = true;}
      if(oTQsSLmzUH == QSixZcWVXM){ODSLWWwJRG = true;}
      else if(QSixZcWVXM == oTQsSLmzUH){axnnwakYWH = true;}
      if(JqsUhrFLHf == MNojLIJyec){cRJTdbYbpE = true;}
      else if(MNojLIJyec == JqsUhrFLHf){WauGKXRtyl = true;}
      if(TboQJFBUuR == rDqabpLtDB){DuigXfJXHm = true;}
      else if(rDqabpLtDB == TboQJFBUuR){LMkNwRdfld = true;}
      if(yHwHDSaoOg == lbCIhhRKet){glDGlBXqSI = true;}
      else if(lbCIhhRKet == yHwHDSaoOg){JcboHhzSKE = true;}
      if(ySaXFKEAMq == InTgcZkUpN){YXypqoAVQA = true;}
      else if(InTgcZkUpN == ySaXFKEAMq){CFdKuFpwRX = true;}
      if(tSwFNNeAiM == VPtlKNaHUi){HtHCnTTknp = true;}
      if(KRDCICtlRP == RcRVakLgCd){MXBdZqNDgc = true;}
      if(QQwahAAQKy == qzTjTDjJyB){DgIhefwsoh = true;}
      while(VPtlKNaHUi == tSwFNNeAiM){jbUeoNMZre = true;}
      while(RcRVakLgCd == RcRVakLgCd){wFmrytyGyb = true;}
      while(qzTjTDjJyB == qzTjTDjJyB){XyisiFhaSp = true;}
      if(FpDpeVgPxU == true){FpDpeVgPxU = false;}
      if(GKoubfVxGq == true){GKoubfVxGq = false;}
      if(ODSLWWwJRG == true){ODSLWWwJRG = false;}
      if(cRJTdbYbpE == true){cRJTdbYbpE = false;}
      if(DuigXfJXHm == true){DuigXfJXHm = false;}
      if(glDGlBXqSI == true){glDGlBXqSI = false;}
      if(YXypqoAVQA == true){YXypqoAVQA = false;}
      if(HtHCnTTknp == true){HtHCnTTknp = false;}
      if(MXBdZqNDgc == true){MXBdZqNDgc = false;}
      if(DgIhefwsoh == true){DgIhefwsoh = false;}
      if(fnGHfmeBSS == true){fnGHfmeBSS = false;}
      if(glCcuBVTQA == true){glCcuBVTQA = false;}
      if(axnnwakYWH == true){axnnwakYWH = false;}
      if(WauGKXRtyl == true){WauGKXRtyl = false;}
      if(LMkNwRdfld == true){LMkNwRdfld = false;}
      if(JcboHhzSKE == true){JcboHhzSKE = false;}
      if(CFdKuFpwRX == true){CFdKuFpwRX = false;}
      if(jbUeoNMZre == true){jbUeoNMZre = false;}
      if(wFmrytyGyb == true){wFmrytyGyb = false;}
      if(XyisiFhaSp == true){XyisiFhaSp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FRMKKWPIZD
{ 
  void XNyTQQiowq()
  { 
      bool aNCtDbNxHU = false;
      bool KlrIZhJxIV = false;
      bool dWCiJtygXH = false;
      bool WJNwtheEFU = false;
      bool tNJLMGjGzh = false;
      bool ETQhKDKSjJ = false;
      bool cfZAxBXuNr = false;
      bool CFqnaQMpWC = false;
      bool KrhpCCrflq = false;
      bool WMUwqOnJNK = false;
      bool hnrGezbcGs = false;
      bool pUugykyjyu = false;
      bool JrJWUpkuwM = false;
      bool cDcMTWzaKC = false;
      bool aPYrACQmxG = false;
      bool PDLSBpeVlo = false;
      bool OgfsQmriMb = false;
      bool lWZuUsSQWS = false;
      bool YxxpxYqJKd = false;
      bool qcoUntjfbM = false;
      string IPpVEKWwZy;
      string bdksmOJzYq;
      string gQMIUzeHjT;
      string bysuJCBjEj;
      string KhMsysudza;
      string gzgXFqChAF;
      string eOLGVdjpik;
      string MZuogyDSJa;
      string DBHJlbQVoS;
      string zTizEuVGXU;
      string JFtOOGErpG;
      string mjXZBdGCTt;
      string MOAQkrqwkk;
      string cxuoRyGsuf;
      string XYehePwJxa;
      string oTldItEddV;
      string PIHFdpoiHD;
      string WNGnVniRkV;
      string ugyJwILRfX;
      string sbOYPORZDo;
      if(IPpVEKWwZy == JFtOOGErpG){aNCtDbNxHU = true;}
      else if(JFtOOGErpG == IPpVEKWwZy){hnrGezbcGs = true;}
      if(bdksmOJzYq == mjXZBdGCTt){KlrIZhJxIV = true;}
      else if(mjXZBdGCTt == bdksmOJzYq){pUugykyjyu = true;}
      if(gQMIUzeHjT == MOAQkrqwkk){dWCiJtygXH = true;}
      else if(MOAQkrqwkk == gQMIUzeHjT){JrJWUpkuwM = true;}
      if(bysuJCBjEj == cxuoRyGsuf){WJNwtheEFU = true;}
      else if(cxuoRyGsuf == bysuJCBjEj){cDcMTWzaKC = true;}
      if(KhMsysudza == XYehePwJxa){tNJLMGjGzh = true;}
      else if(XYehePwJxa == KhMsysudza){aPYrACQmxG = true;}
      if(gzgXFqChAF == oTldItEddV){ETQhKDKSjJ = true;}
      else if(oTldItEddV == gzgXFqChAF){PDLSBpeVlo = true;}
      if(eOLGVdjpik == PIHFdpoiHD){cfZAxBXuNr = true;}
      else if(PIHFdpoiHD == eOLGVdjpik){OgfsQmriMb = true;}
      if(MZuogyDSJa == WNGnVniRkV){CFqnaQMpWC = true;}
      if(DBHJlbQVoS == ugyJwILRfX){KrhpCCrflq = true;}
      if(zTizEuVGXU == sbOYPORZDo){WMUwqOnJNK = true;}
      while(WNGnVniRkV == MZuogyDSJa){lWZuUsSQWS = true;}
      while(ugyJwILRfX == ugyJwILRfX){YxxpxYqJKd = true;}
      while(sbOYPORZDo == sbOYPORZDo){qcoUntjfbM = true;}
      if(aNCtDbNxHU == true){aNCtDbNxHU = false;}
      if(KlrIZhJxIV == true){KlrIZhJxIV = false;}
      if(dWCiJtygXH == true){dWCiJtygXH = false;}
      if(WJNwtheEFU == true){WJNwtheEFU = false;}
      if(tNJLMGjGzh == true){tNJLMGjGzh = false;}
      if(ETQhKDKSjJ == true){ETQhKDKSjJ = false;}
      if(cfZAxBXuNr == true){cfZAxBXuNr = false;}
      if(CFqnaQMpWC == true){CFqnaQMpWC = false;}
      if(KrhpCCrflq == true){KrhpCCrflq = false;}
      if(WMUwqOnJNK == true){WMUwqOnJNK = false;}
      if(hnrGezbcGs == true){hnrGezbcGs = false;}
      if(pUugykyjyu == true){pUugykyjyu = false;}
      if(JrJWUpkuwM == true){JrJWUpkuwM = false;}
      if(cDcMTWzaKC == true){cDcMTWzaKC = false;}
      if(aPYrACQmxG == true){aPYrACQmxG = false;}
      if(PDLSBpeVlo == true){PDLSBpeVlo = false;}
      if(OgfsQmriMb == true){OgfsQmriMb = false;}
      if(lWZuUsSQWS == true){lWZuUsSQWS = false;}
      if(YxxpxYqJKd == true){YxxpxYqJKd = false;}
      if(qcoUntjfbM == true){qcoUntjfbM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WXVBDMLHJS
{ 
  void uwoQuMdJSq()
  { 
      bool XdSzTdoQeH = false;
      bool LWNczAsrIK = false;
      bool PAEkpiPBJz = false;
      bool otNwJMpFrU = false;
      bool cOBsFSZJhD = false;
      bool UjKRRWZgIk = false;
      bool NmGfSRJRTm = false;
      bool KmzmhAzKeX = false;
      bool JFSGdEiuel = false;
      bool lIxGGoIUan = false;
      bool JHptsgjXjQ = false;
      bool WOCjbIUzBO = false;
      bool hNmhABprfs = false;
      bool qejpNBPXNx = false;
      bool TLLNOXGMey = false;
      bool UITMGwUHtq = false;
      bool prqqZreLWa = false;
      bool rwlEtVBYSc = false;
      bool udNhXhKXjR = false;
      bool fHdVGbUUnV = false;
      string IklQjnprxG;
      string gWfiHjCLSy;
      string xplHTnKqwZ;
      string htTLyKtKKW;
      string hbbrKPchuH;
      string cjEEnRzdxu;
      string dywXYmCTkx;
      string pqAwPVNsxD;
      string LbwoxxoOXf;
      string KPNPrieETW;
      string MIwxQkjInS;
      string EFfsiBBHZa;
      string ynuFlZckDg;
      string pJYZpCeyXL;
      string NgaFbEjUfp;
      string gXdsYYMqKp;
      string IyEHctgFCf;
      string WDiNNQNpcg;
      string pIFMzRefBR;
      string ommhDObScg;
      if(IklQjnprxG == MIwxQkjInS){XdSzTdoQeH = true;}
      else if(MIwxQkjInS == IklQjnprxG){JHptsgjXjQ = true;}
      if(gWfiHjCLSy == EFfsiBBHZa){LWNczAsrIK = true;}
      else if(EFfsiBBHZa == gWfiHjCLSy){WOCjbIUzBO = true;}
      if(xplHTnKqwZ == ynuFlZckDg){PAEkpiPBJz = true;}
      else if(ynuFlZckDg == xplHTnKqwZ){hNmhABprfs = true;}
      if(htTLyKtKKW == pJYZpCeyXL){otNwJMpFrU = true;}
      else if(pJYZpCeyXL == htTLyKtKKW){qejpNBPXNx = true;}
      if(hbbrKPchuH == NgaFbEjUfp){cOBsFSZJhD = true;}
      else if(NgaFbEjUfp == hbbrKPchuH){TLLNOXGMey = true;}
      if(cjEEnRzdxu == gXdsYYMqKp){UjKRRWZgIk = true;}
      else if(gXdsYYMqKp == cjEEnRzdxu){UITMGwUHtq = true;}
      if(dywXYmCTkx == IyEHctgFCf){NmGfSRJRTm = true;}
      else if(IyEHctgFCf == dywXYmCTkx){prqqZreLWa = true;}
      if(pqAwPVNsxD == WDiNNQNpcg){KmzmhAzKeX = true;}
      if(LbwoxxoOXf == pIFMzRefBR){JFSGdEiuel = true;}
      if(KPNPrieETW == ommhDObScg){lIxGGoIUan = true;}
      while(WDiNNQNpcg == pqAwPVNsxD){rwlEtVBYSc = true;}
      while(pIFMzRefBR == pIFMzRefBR){udNhXhKXjR = true;}
      while(ommhDObScg == ommhDObScg){fHdVGbUUnV = true;}
      if(XdSzTdoQeH == true){XdSzTdoQeH = false;}
      if(LWNczAsrIK == true){LWNczAsrIK = false;}
      if(PAEkpiPBJz == true){PAEkpiPBJz = false;}
      if(otNwJMpFrU == true){otNwJMpFrU = false;}
      if(cOBsFSZJhD == true){cOBsFSZJhD = false;}
      if(UjKRRWZgIk == true){UjKRRWZgIk = false;}
      if(NmGfSRJRTm == true){NmGfSRJRTm = false;}
      if(KmzmhAzKeX == true){KmzmhAzKeX = false;}
      if(JFSGdEiuel == true){JFSGdEiuel = false;}
      if(lIxGGoIUan == true){lIxGGoIUan = false;}
      if(JHptsgjXjQ == true){JHptsgjXjQ = false;}
      if(WOCjbIUzBO == true){WOCjbIUzBO = false;}
      if(hNmhABprfs == true){hNmhABprfs = false;}
      if(qejpNBPXNx == true){qejpNBPXNx = false;}
      if(TLLNOXGMey == true){TLLNOXGMey = false;}
      if(UITMGwUHtq == true){UITMGwUHtq = false;}
      if(prqqZreLWa == true){prqqZreLWa = false;}
      if(rwlEtVBYSc == true){rwlEtVBYSc = false;}
      if(udNhXhKXjR == true){udNhXhKXjR = false;}
      if(fHdVGbUUnV == true){fHdVGbUUnV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HERZJSIXMO
{ 
  void jJPFWuibSX()
  { 
      bool gfYJzqMCWU = false;
      bool idpbPgKXWQ = false;
      bool VpMqdLloda = false;
      bool EcfMCxIyrJ = false;
      bool QgCUIBKCBP = false;
      bool bxbRXpThfn = false;
      bool FWXuPGxdYS = false;
      bool YLeNzonrib = false;
      bool AjnOyGAOoM = false;
      bool caSEDtJGEB = false;
      bool EgchpQSNRi = false;
      bool BayDmVhIwJ = false;
      bool FhnMoxrZJF = false;
      bool fhmgXTGGXh = false;
      bool nmxGKCbPRh = false;
      bool MAJuwVrQrr = false;
      bool XrEMDTnRfS = false;
      bool ObjOUSkhBm = false;
      bool VcIbseXrjC = false;
      bool apNeJuikCq = false;
      string iUncEiHdMo;
      string SOHaCXiXKX;
      string yrjNbKWVxJ;
      string VBKsGDswui;
      string AQRWXOzWoh;
      string rVuEYqjaAs;
      string LlfCSRENUy;
      string dlbaWgaMoN;
      string KAfOQzFFUO;
      string TSuBWNjODG;
      string KlCpEFsThq;
      string QXkliKFRlT;
      string LzrFeKqaEJ;
      string wLIiDYyoKK;
      string FkXcyuhISL;
      string HScjtKsxLs;
      string OSPYtEOBiJ;
      string MQGaNZbOGi;
      string chIrBdiYor;
      string fBdQwmVzhs;
      if(iUncEiHdMo == KlCpEFsThq){gfYJzqMCWU = true;}
      else if(KlCpEFsThq == iUncEiHdMo){EgchpQSNRi = true;}
      if(SOHaCXiXKX == QXkliKFRlT){idpbPgKXWQ = true;}
      else if(QXkliKFRlT == SOHaCXiXKX){BayDmVhIwJ = true;}
      if(yrjNbKWVxJ == LzrFeKqaEJ){VpMqdLloda = true;}
      else if(LzrFeKqaEJ == yrjNbKWVxJ){FhnMoxrZJF = true;}
      if(VBKsGDswui == wLIiDYyoKK){EcfMCxIyrJ = true;}
      else if(wLIiDYyoKK == VBKsGDswui){fhmgXTGGXh = true;}
      if(AQRWXOzWoh == FkXcyuhISL){QgCUIBKCBP = true;}
      else if(FkXcyuhISL == AQRWXOzWoh){nmxGKCbPRh = true;}
      if(rVuEYqjaAs == HScjtKsxLs){bxbRXpThfn = true;}
      else if(HScjtKsxLs == rVuEYqjaAs){MAJuwVrQrr = true;}
      if(LlfCSRENUy == OSPYtEOBiJ){FWXuPGxdYS = true;}
      else if(OSPYtEOBiJ == LlfCSRENUy){XrEMDTnRfS = true;}
      if(dlbaWgaMoN == MQGaNZbOGi){YLeNzonrib = true;}
      if(KAfOQzFFUO == chIrBdiYor){AjnOyGAOoM = true;}
      if(TSuBWNjODG == fBdQwmVzhs){caSEDtJGEB = true;}
      while(MQGaNZbOGi == dlbaWgaMoN){ObjOUSkhBm = true;}
      while(chIrBdiYor == chIrBdiYor){VcIbseXrjC = true;}
      while(fBdQwmVzhs == fBdQwmVzhs){apNeJuikCq = true;}
      if(gfYJzqMCWU == true){gfYJzqMCWU = false;}
      if(idpbPgKXWQ == true){idpbPgKXWQ = false;}
      if(VpMqdLloda == true){VpMqdLloda = false;}
      if(EcfMCxIyrJ == true){EcfMCxIyrJ = false;}
      if(QgCUIBKCBP == true){QgCUIBKCBP = false;}
      if(bxbRXpThfn == true){bxbRXpThfn = false;}
      if(FWXuPGxdYS == true){FWXuPGxdYS = false;}
      if(YLeNzonrib == true){YLeNzonrib = false;}
      if(AjnOyGAOoM == true){AjnOyGAOoM = false;}
      if(caSEDtJGEB == true){caSEDtJGEB = false;}
      if(EgchpQSNRi == true){EgchpQSNRi = false;}
      if(BayDmVhIwJ == true){BayDmVhIwJ = false;}
      if(FhnMoxrZJF == true){FhnMoxrZJF = false;}
      if(fhmgXTGGXh == true){fhmgXTGGXh = false;}
      if(nmxGKCbPRh == true){nmxGKCbPRh = false;}
      if(MAJuwVrQrr == true){MAJuwVrQrr = false;}
      if(XrEMDTnRfS == true){XrEMDTnRfS = false;}
      if(ObjOUSkhBm == true){ObjOUSkhBm = false;}
      if(VcIbseXrjC == true){VcIbseXrjC = false;}
      if(apNeJuikCq == true){apNeJuikCq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QEUNWHFBFO
{ 
  void XIYwxqfdBh()
  { 
      bool iTLGsAmfGU = false;
      bool tBixahjEXt = false;
      bool sUMlTjyfGd = false;
      bool qQVBRuWDPZ = false;
      bool QXOpuxMMBR = false;
      bool zPTggNGYlI = false;
      bool CGYbcdehfe = false;
      bool LfnxcUGWqW = false;
      bool WkenebxoTD = false;
      bool oyQGXKzlMR = false;
      bool SdgWGTaWEM = false;
      bool HigPlRbkxB = false;
      bool goOboMOhZS = false;
      bool VTKZErDHhL = false;
      bool AZkHuFQBUG = false;
      bool hNoKjcPFgs = false;
      bool EsxlpnYHLs = false;
      bool NTClAGEHfj = false;
      bool wMMSjHezob = false;
      bool cyanGHczQH = false;
      string aAszRJxQyQ;
      string sBpTdzOzVp;
      string kkPNdizuZX;
      string PVZuEslgYY;
      string cNjMwfQcLK;
      string UGrxWpjfUh;
      string KBpZAWbuPk;
      string NhawMWACQy;
      string RVjPDJcbYO;
      string IGLpObWJLZ;
      string DUNaxmewjz;
      string ohOWPoRaWq;
      string sAWBbGWkhk;
      string AqpqtxIISQ;
      string dgqZYaqnZZ;
      string JwlUfDyLyp;
      string PtNzyyqXcS;
      string fIIGNLIxbB;
      string PhKIaEEVKp;
      string ywKbAiTraa;
      if(aAszRJxQyQ == DUNaxmewjz){iTLGsAmfGU = true;}
      else if(DUNaxmewjz == aAszRJxQyQ){SdgWGTaWEM = true;}
      if(sBpTdzOzVp == ohOWPoRaWq){tBixahjEXt = true;}
      else if(ohOWPoRaWq == sBpTdzOzVp){HigPlRbkxB = true;}
      if(kkPNdizuZX == sAWBbGWkhk){sUMlTjyfGd = true;}
      else if(sAWBbGWkhk == kkPNdizuZX){goOboMOhZS = true;}
      if(PVZuEslgYY == AqpqtxIISQ){qQVBRuWDPZ = true;}
      else if(AqpqtxIISQ == PVZuEslgYY){VTKZErDHhL = true;}
      if(cNjMwfQcLK == dgqZYaqnZZ){QXOpuxMMBR = true;}
      else if(dgqZYaqnZZ == cNjMwfQcLK){AZkHuFQBUG = true;}
      if(UGrxWpjfUh == JwlUfDyLyp){zPTggNGYlI = true;}
      else if(JwlUfDyLyp == UGrxWpjfUh){hNoKjcPFgs = true;}
      if(KBpZAWbuPk == PtNzyyqXcS){CGYbcdehfe = true;}
      else if(PtNzyyqXcS == KBpZAWbuPk){EsxlpnYHLs = true;}
      if(NhawMWACQy == fIIGNLIxbB){LfnxcUGWqW = true;}
      if(RVjPDJcbYO == PhKIaEEVKp){WkenebxoTD = true;}
      if(IGLpObWJLZ == ywKbAiTraa){oyQGXKzlMR = true;}
      while(fIIGNLIxbB == NhawMWACQy){NTClAGEHfj = true;}
      while(PhKIaEEVKp == PhKIaEEVKp){wMMSjHezob = true;}
      while(ywKbAiTraa == ywKbAiTraa){cyanGHczQH = true;}
      if(iTLGsAmfGU == true){iTLGsAmfGU = false;}
      if(tBixahjEXt == true){tBixahjEXt = false;}
      if(sUMlTjyfGd == true){sUMlTjyfGd = false;}
      if(qQVBRuWDPZ == true){qQVBRuWDPZ = false;}
      if(QXOpuxMMBR == true){QXOpuxMMBR = false;}
      if(zPTggNGYlI == true){zPTggNGYlI = false;}
      if(CGYbcdehfe == true){CGYbcdehfe = false;}
      if(LfnxcUGWqW == true){LfnxcUGWqW = false;}
      if(WkenebxoTD == true){WkenebxoTD = false;}
      if(oyQGXKzlMR == true){oyQGXKzlMR = false;}
      if(SdgWGTaWEM == true){SdgWGTaWEM = false;}
      if(HigPlRbkxB == true){HigPlRbkxB = false;}
      if(goOboMOhZS == true){goOboMOhZS = false;}
      if(VTKZErDHhL == true){VTKZErDHhL = false;}
      if(AZkHuFQBUG == true){AZkHuFQBUG = false;}
      if(hNoKjcPFgs == true){hNoKjcPFgs = false;}
      if(EsxlpnYHLs == true){EsxlpnYHLs = false;}
      if(NTClAGEHfj == true){NTClAGEHfj = false;}
      if(wMMSjHezob == true){wMMSjHezob = false;}
      if(cyanGHczQH == true){cyanGHczQH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CDUIRMHJGO
{ 
  void gNPIIqYCEW()
  { 
      bool MWPwKClLWK = false;
      bool TEihwGroYm = false;
      bool gzxLanAqCn = false;
      bool VgzzYYJgcL = false;
      bool yJjtcqlIxG = false;
      bool XKYIwMYEUW = false;
      bool CtIhnlFjJX = false;
      bool xKLNnWPDij = false;
      bool BrtwPLHqCL = false;
      bool zFLGJEBBGp = false;
      bool lByZJNyLTZ = false;
      bool xVUkUJzMRc = false;
      bool eNhyXryFEj = false;
      bool VOwsyAsTmC = false;
      bool MwWcOdjakz = false;
      bool EnicLXTzCQ = false;
      bool OsHjDhYbmU = false;
      bool PeZPQhqFjt = false;
      bool IWUEegfShZ = false;
      bool gsRVmSomYf = false;
      string qFJcPOMWBD;
      string fcEMMCGwfp;
      string XEPFSnSYzU;
      string HUgmUySjMJ;
      string kTTOpKeNny;
      string yCGAlmpDKa;
      string wnXfwLwQrN;
      string jViVFEkAPI;
      string JEkAVFNfBh;
      string IOZkMxumSd;
      string NOVZNbSkug;
      string BonCRrCXKp;
      string yPOJFVwxII;
      string IyhktuhLls;
      string lbkTgTZXTU;
      string tXbbfyzMTr;
      string fVcmYCGDHW;
      string JqkQEVeuck;
      string uYdnNkVGFw;
      string uVqtNPzyud;
      if(qFJcPOMWBD == NOVZNbSkug){MWPwKClLWK = true;}
      else if(NOVZNbSkug == qFJcPOMWBD){lByZJNyLTZ = true;}
      if(fcEMMCGwfp == BonCRrCXKp){TEihwGroYm = true;}
      else if(BonCRrCXKp == fcEMMCGwfp){xVUkUJzMRc = true;}
      if(XEPFSnSYzU == yPOJFVwxII){gzxLanAqCn = true;}
      else if(yPOJFVwxII == XEPFSnSYzU){eNhyXryFEj = true;}
      if(HUgmUySjMJ == IyhktuhLls){VgzzYYJgcL = true;}
      else if(IyhktuhLls == HUgmUySjMJ){VOwsyAsTmC = true;}
      if(kTTOpKeNny == lbkTgTZXTU){yJjtcqlIxG = true;}
      else if(lbkTgTZXTU == kTTOpKeNny){MwWcOdjakz = true;}
      if(yCGAlmpDKa == tXbbfyzMTr){XKYIwMYEUW = true;}
      else if(tXbbfyzMTr == yCGAlmpDKa){EnicLXTzCQ = true;}
      if(wnXfwLwQrN == fVcmYCGDHW){CtIhnlFjJX = true;}
      else if(fVcmYCGDHW == wnXfwLwQrN){OsHjDhYbmU = true;}
      if(jViVFEkAPI == JqkQEVeuck){xKLNnWPDij = true;}
      if(JEkAVFNfBh == uYdnNkVGFw){BrtwPLHqCL = true;}
      if(IOZkMxumSd == uVqtNPzyud){zFLGJEBBGp = true;}
      while(JqkQEVeuck == jViVFEkAPI){PeZPQhqFjt = true;}
      while(uYdnNkVGFw == uYdnNkVGFw){IWUEegfShZ = true;}
      while(uVqtNPzyud == uVqtNPzyud){gsRVmSomYf = true;}
      if(MWPwKClLWK == true){MWPwKClLWK = false;}
      if(TEihwGroYm == true){TEihwGroYm = false;}
      if(gzxLanAqCn == true){gzxLanAqCn = false;}
      if(VgzzYYJgcL == true){VgzzYYJgcL = false;}
      if(yJjtcqlIxG == true){yJjtcqlIxG = false;}
      if(XKYIwMYEUW == true){XKYIwMYEUW = false;}
      if(CtIhnlFjJX == true){CtIhnlFjJX = false;}
      if(xKLNnWPDij == true){xKLNnWPDij = false;}
      if(BrtwPLHqCL == true){BrtwPLHqCL = false;}
      if(zFLGJEBBGp == true){zFLGJEBBGp = false;}
      if(lByZJNyLTZ == true){lByZJNyLTZ = false;}
      if(xVUkUJzMRc == true){xVUkUJzMRc = false;}
      if(eNhyXryFEj == true){eNhyXryFEj = false;}
      if(VOwsyAsTmC == true){VOwsyAsTmC = false;}
      if(MwWcOdjakz == true){MwWcOdjakz = false;}
      if(EnicLXTzCQ == true){EnicLXTzCQ = false;}
      if(OsHjDhYbmU == true){OsHjDhYbmU = false;}
      if(PeZPQhqFjt == true){PeZPQhqFjt = false;}
      if(IWUEegfShZ == true){IWUEegfShZ = false;}
      if(gsRVmSomYf == true){gsRVmSomYf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CMAHEHLTWI
{ 
  void olTIILkLxR()
  { 
      bool PAoDqDGXot = false;
      bool mNnKtSahUq = false;
      bool zZeANxROlX = false;
      bool RUnerLikmp = false;
      bool PREdoUKjzH = false;
      bool tzpldpUnot = false;
      bool lrlQbRZJRh = false;
      bool jpudbgUBKs = false;
      bool lgOddReBAC = false;
      bool qtusEXfnBX = false;
      bool tBSRXDELKw = false;
      bool USdwHFcHmK = false;
      bool mXIPpouCZD = false;
      bool BgAmzkOxGZ = false;
      bool MSqDgXQykz = false;
      bool tXApkWrCah = false;
      bool IClGunSqxV = false;
      bool peBMxUgFiS = false;
      bool YwQaJcfJBc = false;
      bool sLWYRKfjHr = false;
      string xPrwSQGItS;
      string UhAGqlQdjp;
      string FnbQCAFHfO;
      string wzaxsSyjcn;
      string ozwkKgtlhJ;
      string OFZaFImasR;
      string KzcfWUHCMX;
      string mgAuAGrqGU;
      string GTYVAqZArj;
      string fXpLdpVQOo;
      string ZqYKVhFdZz;
      string QwUXLpZHee;
      string uGKbrPpoRK;
      string kacRuOuNzS;
      string luarTiDRAm;
      string POkisSfwSG;
      string qPMOOoTDcw;
      string uMHMszfSII;
      string MXndtWpsXb;
      string hytsaVhLdd;
      if(xPrwSQGItS == ZqYKVhFdZz){PAoDqDGXot = true;}
      else if(ZqYKVhFdZz == xPrwSQGItS){tBSRXDELKw = true;}
      if(UhAGqlQdjp == QwUXLpZHee){mNnKtSahUq = true;}
      else if(QwUXLpZHee == UhAGqlQdjp){USdwHFcHmK = true;}
      if(FnbQCAFHfO == uGKbrPpoRK){zZeANxROlX = true;}
      else if(uGKbrPpoRK == FnbQCAFHfO){mXIPpouCZD = true;}
      if(wzaxsSyjcn == kacRuOuNzS){RUnerLikmp = true;}
      else if(kacRuOuNzS == wzaxsSyjcn){BgAmzkOxGZ = true;}
      if(ozwkKgtlhJ == luarTiDRAm){PREdoUKjzH = true;}
      else if(luarTiDRAm == ozwkKgtlhJ){MSqDgXQykz = true;}
      if(OFZaFImasR == POkisSfwSG){tzpldpUnot = true;}
      else if(POkisSfwSG == OFZaFImasR){tXApkWrCah = true;}
      if(KzcfWUHCMX == qPMOOoTDcw){lrlQbRZJRh = true;}
      else if(qPMOOoTDcw == KzcfWUHCMX){IClGunSqxV = true;}
      if(mgAuAGrqGU == uMHMszfSII){jpudbgUBKs = true;}
      if(GTYVAqZArj == MXndtWpsXb){lgOddReBAC = true;}
      if(fXpLdpVQOo == hytsaVhLdd){qtusEXfnBX = true;}
      while(uMHMszfSII == mgAuAGrqGU){peBMxUgFiS = true;}
      while(MXndtWpsXb == MXndtWpsXb){YwQaJcfJBc = true;}
      while(hytsaVhLdd == hytsaVhLdd){sLWYRKfjHr = true;}
      if(PAoDqDGXot == true){PAoDqDGXot = false;}
      if(mNnKtSahUq == true){mNnKtSahUq = false;}
      if(zZeANxROlX == true){zZeANxROlX = false;}
      if(RUnerLikmp == true){RUnerLikmp = false;}
      if(PREdoUKjzH == true){PREdoUKjzH = false;}
      if(tzpldpUnot == true){tzpldpUnot = false;}
      if(lrlQbRZJRh == true){lrlQbRZJRh = false;}
      if(jpudbgUBKs == true){jpudbgUBKs = false;}
      if(lgOddReBAC == true){lgOddReBAC = false;}
      if(qtusEXfnBX == true){qtusEXfnBX = false;}
      if(tBSRXDELKw == true){tBSRXDELKw = false;}
      if(USdwHFcHmK == true){USdwHFcHmK = false;}
      if(mXIPpouCZD == true){mXIPpouCZD = false;}
      if(BgAmzkOxGZ == true){BgAmzkOxGZ = false;}
      if(MSqDgXQykz == true){MSqDgXQykz = false;}
      if(tXApkWrCah == true){tXApkWrCah = false;}
      if(IClGunSqxV == true){IClGunSqxV = false;}
      if(peBMxUgFiS == true){peBMxUgFiS = false;}
      if(YwQaJcfJBc == true){YwQaJcfJBc = false;}
      if(sLWYRKfjHr == true){sLWYRKfjHr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWGIJGHYEF
{ 
  void iOjdzFgaZc()
  { 
      bool hOCsYDGHWZ = false;
      bool gQdepRyWEc = false;
      bool UPwioDhesy = false;
      bool ebLHiWlmmw = false;
      bool gXJGlwXpzH = false;
      bool zWAtQSSSEU = false;
      bool UaNXtFFVwT = false;
      bool fLiIwwFpxr = false;
      bool erelzIbRqP = false;
      bool ESiRaFJkLf = false;
      bool qBtfbnmqyT = false;
      bool NcVLocubYl = false;
      bool cnefOMcQgq = false;
      bool lTdRBdxzJK = false;
      bool UkSWCbxWby = false;
      bool JhMZCDWNQO = false;
      bool KVJHgsyDKL = false;
      bool ewROQrUHdm = false;
      bool PFnigEHEOx = false;
      bool HihtzyaLoJ = false;
      string ptdVzBPcJl;
      string cZYEzXxzKz;
      string NzAmAyxfNW;
      string cYPhhXrMMM;
      string NgPEFNNWTm;
      string msWwNptpVA;
      string EiPlJEJqVa;
      string fkmykgjwgl;
      string kZLZjiBTTq;
      string dBpLIeRctB;
      string EWBsHCGYKf;
      string GyIjPdWoBZ;
      string CpWdwdtapG;
      string PGBfgNYSSh;
      string ccImkerFud;
      string HbaTzOAWwc;
      string HeiDQzxcCC;
      string FEVTxYgisR;
      string lofLzmeggS;
      string NBVpZysEWk;
      if(ptdVzBPcJl == EWBsHCGYKf){hOCsYDGHWZ = true;}
      else if(EWBsHCGYKf == ptdVzBPcJl){qBtfbnmqyT = true;}
      if(cZYEzXxzKz == GyIjPdWoBZ){gQdepRyWEc = true;}
      else if(GyIjPdWoBZ == cZYEzXxzKz){NcVLocubYl = true;}
      if(NzAmAyxfNW == CpWdwdtapG){UPwioDhesy = true;}
      else if(CpWdwdtapG == NzAmAyxfNW){cnefOMcQgq = true;}
      if(cYPhhXrMMM == PGBfgNYSSh){ebLHiWlmmw = true;}
      else if(PGBfgNYSSh == cYPhhXrMMM){lTdRBdxzJK = true;}
      if(NgPEFNNWTm == ccImkerFud){gXJGlwXpzH = true;}
      else if(ccImkerFud == NgPEFNNWTm){UkSWCbxWby = true;}
      if(msWwNptpVA == HbaTzOAWwc){zWAtQSSSEU = true;}
      else if(HbaTzOAWwc == msWwNptpVA){JhMZCDWNQO = true;}
      if(EiPlJEJqVa == HeiDQzxcCC){UaNXtFFVwT = true;}
      else if(HeiDQzxcCC == EiPlJEJqVa){KVJHgsyDKL = true;}
      if(fkmykgjwgl == FEVTxYgisR){fLiIwwFpxr = true;}
      if(kZLZjiBTTq == lofLzmeggS){erelzIbRqP = true;}
      if(dBpLIeRctB == NBVpZysEWk){ESiRaFJkLf = true;}
      while(FEVTxYgisR == fkmykgjwgl){ewROQrUHdm = true;}
      while(lofLzmeggS == lofLzmeggS){PFnigEHEOx = true;}
      while(NBVpZysEWk == NBVpZysEWk){HihtzyaLoJ = true;}
      if(hOCsYDGHWZ == true){hOCsYDGHWZ = false;}
      if(gQdepRyWEc == true){gQdepRyWEc = false;}
      if(UPwioDhesy == true){UPwioDhesy = false;}
      if(ebLHiWlmmw == true){ebLHiWlmmw = false;}
      if(gXJGlwXpzH == true){gXJGlwXpzH = false;}
      if(zWAtQSSSEU == true){zWAtQSSSEU = false;}
      if(UaNXtFFVwT == true){UaNXtFFVwT = false;}
      if(fLiIwwFpxr == true){fLiIwwFpxr = false;}
      if(erelzIbRqP == true){erelzIbRqP = false;}
      if(ESiRaFJkLf == true){ESiRaFJkLf = false;}
      if(qBtfbnmqyT == true){qBtfbnmqyT = false;}
      if(NcVLocubYl == true){NcVLocubYl = false;}
      if(cnefOMcQgq == true){cnefOMcQgq = false;}
      if(lTdRBdxzJK == true){lTdRBdxzJK = false;}
      if(UkSWCbxWby == true){UkSWCbxWby = false;}
      if(JhMZCDWNQO == true){JhMZCDWNQO = false;}
      if(KVJHgsyDKL == true){KVJHgsyDKL = false;}
      if(ewROQrUHdm == true){ewROQrUHdm = false;}
      if(PFnigEHEOx == true){PFnigEHEOx = false;}
      if(HihtzyaLoJ == true){HihtzyaLoJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNUDUAAUWI
{ 
  void cxMcPsBcnE()
  { 
      bool QwwYCWUJpx = false;
      bool wkjwoHpDUZ = false;
      bool CLywMtCGHZ = false;
      bool HPXxUtDziT = false;
      bool dTKUMFFBmi = false;
      bool KAzbfFxzMI = false;
      bool UNCPofMmbt = false;
      bool EpTAwhBdjH = false;
      bool nBTXPHPwRP = false;
      bool xDlazPRtff = false;
      bool sSYseTfzfy = false;
      bool DTPFTTteAg = false;
      bool PPUMwBDrBg = false;
      bool PHxDNUbasu = false;
      bool aQPTLcmgGf = false;
      bool VmsyPcyMwc = false;
      bool PmyzhwVMqz = false;
      bool qTkFFzABAT = false;
      bool NWkUKcOzmk = false;
      bool WOdPfnSQlP = false;
      string OuwzFIJWPx;
      string odYSbufoqk;
      string XCuPOhAymL;
      string dbEVrGkhFl;
      string QcJYaYRjTt;
      string FzSwULzfkW;
      string HLiDTNZDaV;
      string JxjEUurWno;
      string QQdrGdIIAg;
      string GFxheFsFFN;
      string zOJxkHPOaZ;
      string ScquFqgpxo;
      string ERCsOEABYP;
      string BlQapCGgHy;
      string OsgaNcNBcm;
      string XDIQIgLPhf;
      string HOoLXfMQFD;
      string kAhyZLkael;
      string qzYlqydARI;
      string ppybqADUCh;
      if(OuwzFIJWPx == zOJxkHPOaZ){QwwYCWUJpx = true;}
      else if(zOJxkHPOaZ == OuwzFIJWPx){sSYseTfzfy = true;}
      if(odYSbufoqk == ScquFqgpxo){wkjwoHpDUZ = true;}
      else if(ScquFqgpxo == odYSbufoqk){DTPFTTteAg = true;}
      if(XCuPOhAymL == ERCsOEABYP){CLywMtCGHZ = true;}
      else if(ERCsOEABYP == XCuPOhAymL){PPUMwBDrBg = true;}
      if(dbEVrGkhFl == BlQapCGgHy){HPXxUtDziT = true;}
      else if(BlQapCGgHy == dbEVrGkhFl){PHxDNUbasu = true;}
      if(QcJYaYRjTt == OsgaNcNBcm){dTKUMFFBmi = true;}
      else if(OsgaNcNBcm == QcJYaYRjTt){aQPTLcmgGf = true;}
      if(FzSwULzfkW == XDIQIgLPhf){KAzbfFxzMI = true;}
      else if(XDIQIgLPhf == FzSwULzfkW){VmsyPcyMwc = true;}
      if(HLiDTNZDaV == HOoLXfMQFD){UNCPofMmbt = true;}
      else if(HOoLXfMQFD == HLiDTNZDaV){PmyzhwVMqz = true;}
      if(JxjEUurWno == kAhyZLkael){EpTAwhBdjH = true;}
      if(QQdrGdIIAg == qzYlqydARI){nBTXPHPwRP = true;}
      if(GFxheFsFFN == ppybqADUCh){xDlazPRtff = true;}
      while(kAhyZLkael == JxjEUurWno){qTkFFzABAT = true;}
      while(qzYlqydARI == qzYlqydARI){NWkUKcOzmk = true;}
      while(ppybqADUCh == ppybqADUCh){WOdPfnSQlP = true;}
      if(QwwYCWUJpx == true){QwwYCWUJpx = false;}
      if(wkjwoHpDUZ == true){wkjwoHpDUZ = false;}
      if(CLywMtCGHZ == true){CLywMtCGHZ = false;}
      if(HPXxUtDziT == true){HPXxUtDziT = false;}
      if(dTKUMFFBmi == true){dTKUMFFBmi = false;}
      if(KAzbfFxzMI == true){KAzbfFxzMI = false;}
      if(UNCPofMmbt == true){UNCPofMmbt = false;}
      if(EpTAwhBdjH == true){EpTAwhBdjH = false;}
      if(nBTXPHPwRP == true){nBTXPHPwRP = false;}
      if(xDlazPRtff == true){xDlazPRtff = false;}
      if(sSYseTfzfy == true){sSYseTfzfy = false;}
      if(DTPFTTteAg == true){DTPFTTteAg = false;}
      if(PPUMwBDrBg == true){PPUMwBDrBg = false;}
      if(PHxDNUbasu == true){PHxDNUbasu = false;}
      if(aQPTLcmgGf == true){aQPTLcmgGf = false;}
      if(VmsyPcyMwc == true){VmsyPcyMwc = false;}
      if(PmyzhwVMqz == true){PmyzhwVMqz = false;}
      if(qTkFFzABAT == true){qTkFFzABAT = false;}
      if(NWkUKcOzmk == true){NWkUKcOzmk = false;}
      if(WOdPfnSQlP == true){WOdPfnSQlP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EAJPCRUNZQ
{ 
  void qrcoSFxuye()
  { 
      bool ONAZTdKFxC = false;
      bool iSOZwNHkls = false;
      bool ZtsqHrmzAV = false;
      bool sIsVZVBdzl = false;
      bool ipULsODGxl = false;
      bool baOWTTUJRa = false;
      bool pLFaIaYszZ = false;
      bool LclzKjYhxs = false;
      bool ogBNtRsVBF = false;
      bool BrMXwWksCR = false;
      bool oJGWZynPMj = false;
      bool ulLYlIJqgq = false;
      bool hDqtYTQNDm = false;
      bool zefeDeadmu = false;
      bool cdIRKOfmkm = false;
      bool NsMLjkSMyG = false;
      bool haLYkPGfUH = false;
      bool heDkNDtZiJ = false;
      bool mccQZFSTuR = false;
      bool MNfgMCRjfu = false;
      string sFpWpDMcaJ;
      string nryyfazpif;
      string UBBPJrnXzN;
      string iAMueKXVKB;
      string CAgcQjseyn;
      string NJisFqEaNx;
      string PndNZmeDTU;
      string CdehcUUXyY;
      string zIYKzZRTom;
      string GxHMkNWTDd;
      string EpLckjdAQk;
      string WfbnyHPSOA;
      string VLNfOFVSwO;
      string xAUUUJxuZO;
      string uQCEQZUTOd;
      string yDFCHrbeOf;
      string OLECmVLGTo;
      string KTszFFIJPn;
      string jBESPsuRNb;
      string gRgsziMAQt;
      if(sFpWpDMcaJ == EpLckjdAQk){ONAZTdKFxC = true;}
      else if(EpLckjdAQk == sFpWpDMcaJ){oJGWZynPMj = true;}
      if(nryyfazpif == WfbnyHPSOA){iSOZwNHkls = true;}
      else if(WfbnyHPSOA == nryyfazpif){ulLYlIJqgq = true;}
      if(UBBPJrnXzN == VLNfOFVSwO){ZtsqHrmzAV = true;}
      else if(VLNfOFVSwO == UBBPJrnXzN){hDqtYTQNDm = true;}
      if(iAMueKXVKB == xAUUUJxuZO){sIsVZVBdzl = true;}
      else if(xAUUUJxuZO == iAMueKXVKB){zefeDeadmu = true;}
      if(CAgcQjseyn == uQCEQZUTOd){ipULsODGxl = true;}
      else if(uQCEQZUTOd == CAgcQjseyn){cdIRKOfmkm = true;}
      if(NJisFqEaNx == yDFCHrbeOf){baOWTTUJRa = true;}
      else if(yDFCHrbeOf == NJisFqEaNx){NsMLjkSMyG = true;}
      if(PndNZmeDTU == OLECmVLGTo){pLFaIaYszZ = true;}
      else if(OLECmVLGTo == PndNZmeDTU){haLYkPGfUH = true;}
      if(CdehcUUXyY == KTszFFIJPn){LclzKjYhxs = true;}
      if(zIYKzZRTom == jBESPsuRNb){ogBNtRsVBF = true;}
      if(GxHMkNWTDd == gRgsziMAQt){BrMXwWksCR = true;}
      while(KTszFFIJPn == CdehcUUXyY){heDkNDtZiJ = true;}
      while(jBESPsuRNb == jBESPsuRNb){mccQZFSTuR = true;}
      while(gRgsziMAQt == gRgsziMAQt){MNfgMCRjfu = true;}
      if(ONAZTdKFxC == true){ONAZTdKFxC = false;}
      if(iSOZwNHkls == true){iSOZwNHkls = false;}
      if(ZtsqHrmzAV == true){ZtsqHrmzAV = false;}
      if(sIsVZVBdzl == true){sIsVZVBdzl = false;}
      if(ipULsODGxl == true){ipULsODGxl = false;}
      if(baOWTTUJRa == true){baOWTTUJRa = false;}
      if(pLFaIaYszZ == true){pLFaIaYszZ = false;}
      if(LclzKjYhxs == true){LclzKjYhxs = false;}
      if(ogBNtRsVBF == true){ogBNtRsVBF = false;}
      if(BrMXwWksCR == true){BrMXwWksCR = false;}
      if(oJGWZynPMj == true){oJGWZynPMj = false;}
      if(ulLYlIJqgq == true){ulLYlIJqgq = false;}
      if(hDqtYTQNDm == true){hDqtYTQNDm = false;}
      if(zefeDeadmu == true){zefeDeadmu = false;}
      if(cdIRKOfmkm == true){cdIRKOfmkm = false;}
      if(NsMLjkSMyG == true){NsMLjkSMyG = false;}
      if(haLYkPGfUH == true){haLYkPGfUH = false;}
      if(heDkNDtZiJ == true){heDkNDtZiJ = false;}
      if(mccQZFSTuR == true){mccQZFSTuR = false;}
      if(MNfgMCRjfu == true){MNfgMCRjfu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EMSGAMNTOV
{ 
  void XSVdFMYErq()
  { 
      bool okiwqsBtcf = false;
      bool nNzpwhNsNf = false;
      bool jqgIcypmNd = false;
      bool uSziuilyPf = false;
      bool LnPlhBijfN = false;
      bool IRROqxDaTr = false;
      bool DNgykUNPuM = false;
      bool wOchUwbuab = false;
      bool OGHzVdBkrx = false;
      bool fKeXcxHRBM = false;
      bool mSoTRsnjtu = false;
      bool VIAqcwGgcG = false;
      bool TcXxgkjFFW = false;
      bool oKsNnwRmhb = false;
      bool oRpwbXKmtf = false;
      bool qZntsKtqmf = false;
      bool JidWGLOlCg = false;
      bool eSzAQBlbVI = false;
      bool awKYeOVyTd = false;
      bool BZABSGmSpQ = false;
      string OseYfYYJGO;
      string OghKVxiWWs;
      string FJBSYBjTjJ;
      string IFYmEaBzho;
      string gAKSLMmXfS;
      string WhNibErLzd;
      string nEZwGIHuGt;
      string wjngLEziHM;
      string OLmQmZrpLz;
      string ipAEBbaNLC;
      string EqRlWmsgWW;
      string EIElObRJJg;
      string QRiGKGijfj;
      string dlXEIWtBsz;
      string fKSntZkNoY;
      string KQDdllILaQ;
      string DJAmsSkAdr;
      string hQPJBFyuLj;
      string UVuHYMhsSV;
      string OiZbwWKfub;
      if(OseYfYYJGO == EqRlWmsgWW){okiwqsBtcf = true;}
      else if(EqRlWmsgWW == OseYfYYJGO){mSoTRsnjtu = true;}
      if(OghKVxiWWs == EIElObRJJg){nNzpwhNsNf = true;}
      else if(EIElObRJJg == OghKVxiWWs){VIAqcwGgcG = true;}
      if(FJBSYBjTjJ == QRiGKGijfj){jqgIcypmNd = true;}
      else if(QRiGKGijfj == FJBSYBjTjJ){TcXxgkjFFW = true;}
      if(IFYmEaBzho == dlXEIWtBsz){uSziuilyPf = true;}
      else if(dlXEIWtBsz == IFYmEaBzho){oKsNnwRmhb = true;}
      if(gAKSLMmXfS == fKSntZkNoY){LnPlhBijfN = true;}
      else if(fKSntZkNoY == gAKSLMmXfS){oRpwbXKmtf = true;}
      if(WhNibErLzd == KQDdllILaQ){IRROqxDaTr = true;}
      else if(KQDdllILaQ == WhNibErLzd){qZntsKtqmf = true;}
      if(nEZwGIHuGt == DJAmsSkAdr){DNgykUNPuM = true;}
      else if(DJAmsSkAdr == nEZwGIHuGt){JidWGLOlCg = true;}
      if(wjngLEziHM == hQPJBFyuLj){wOchUwbuab = true;}
      if(OLmQmZrpLz == UVuHYMhsSV){OGHzVdBkrx = true;}
      if(ipAEBbaNLC == OiZbwWKfub){fKeXcxHRBM = true;}
      while(hQPJBFyuLj == wjngLEziHM){eSzAQBlbVI = true;}
      while(UVuHYMhsSV == UVuHYMhsSV){awKYeOVyTd = true;}
      while(OiZbwWKfub == OiZbwWKfub){BZABSGmSpQ = true;}
      if(okiwqsBtcf == true){okiwqsBtcf = false;}
      if(nNzpwhNsNf == true){nNzpwhNsNf = false;}
      if(jqgIcypmNd == true){jqgIcypmNd = false;}
      if(uSziuilyPf == true){uSziuilyPf = false;}
      if(LnPlhBijfN == true){LnPlhBijfN = false;}
      if(IRROqxDaTr == true){IRROqxDaTr = false;}
      if(DNgykUNPuM == true){DNgykUNPuM = false;}
      if(wOchUwbuab == true){wOchUwbuab = false;}
      if(OGHzVdBkrx == true){OGHzVdBkrx = false;}
      if(fKeXcxHRBM == true){fKeXcxHRBM = false;}
      if(mSoTRsnjtu == true){mSoTRsnjtu = false;}
      if(VIAqcwGgcG == true){VIAqcwGgcG = false;}
      if(TcXxgkjFFW == true){TcXxgkjFFW = false;}
      if(oKsNnwRmhb == true){oKsNnwRmhb = false;}
      if(oRpwbXKmtf == true){oRpwbXKmtf = false;}
      if(qZntsKtqmf == true){qZntsKtqmf = false;}
      if(JidWGLOlCg == true){JidWGLOlCg = false;}
      if(eSzAQBlbVI == true){eSzAQBlbVI = false;}
      if(awKYeOVyTd == true){awKYeOVyTd = false;}
      if(BZABSGmSpQ == true){BZABSGmSpQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HDVWOEECUZ
{ 
  void mXrghJnzjO()
  { 
      bool WlVhHOcJJK = false;
      bool dCGhwDGhEk = false;
      bool ztqXLUJZoO = false;
      bool yphEVueqaZ = false;
      bool VkfwWWIFhC = false;
      bool YScjobtyWm = false;
      bool FCTuMnTBLB = false;
      bool XOGdPOOuBn = false;
      bool MEqlpeNyPt = false;
      bool AgUnUSQkii = false;
      bool CGsgeJLyUa = false;
      bool MzwhaBKhFg = false;
      bool ZVlRApsSJw = false;
      bool xdLSlFKKHf = false;
      bool SPcogBkmNT = false;
      bool IieCIfUbfn = false;
      bool QsoXcimdwU = false;
      bool pzZZNKrxjz = false;
      bool FGEonOyJJF = false;
      bool khdTOZaFLx = false;
      string GsEJEWHqBp;
      string pSwzKYWguB;
      string AwJwcpfFUg;
      string wOuRpWHDAf;
      string aUhEDYtmPN;
      string UIFWwKjHfN;
      string qCWTtaWdJn;
      string RSgOafOEsE;
      string wspGMnJXVf;
      string mzWloYyNKb;
      string BPdbwBbqwQ;
      string weObRyLPHG;
      string RzIcARwtZC;
      string gBtQCfOOJL;
      string MSbEjHjuTp;
      string MiFDJCGAad;
      string EgQtiukyYk;
      string ixFwtzXDss;
      string hBZioyupGA;
      string ZOmeGeBgVo;
      if(GsEJEWHqBp == BPdbwBbqwQ){WlVhHOcJJK = true;}
      else if(BPdbwBbqwQ == GsEJEWHqBp){CGsgeJLyUa = true;}
      if(pSwzKYWguB == weObRyLPHG){dCGhwDGhEk = true;}
      else if(weObRyLPHG == pSwzKYWguB){MzwhaBKhFg = true;}
      if(AwJwcpfFUg == RzIcARwtZC){ztqXLUJZoO = true;}
      else if(RzIcARwtZC == AwJwcpfFUg){ZVlRApsSJw = true;}
      if(wOuRpWHDAf == gBtQCfOOJL){yphEVueqaZ = true;}
      else if(gBtQCfOOJL == wOuRpWHDAf){xdLSlFKKHf = true;}
      if(aUhEDYtmPN == MSbEjHjuTp){VkfwWWIFhC = true;}
      else if(MSbEjHjuTp == aUhEDYtmPN){SPcogBkmNT = true;}
      if(UIFWwKjHfN == MiFDJCGAad){YScjobtyWm = true;}
      else if(MiFDJCGAad == UIFWwKjHfN){IieCIfUbfn = true;}
      if(qCWTtaWdJn == EgQtiukyYk){FCTuMnTBLB = true;}
      else if(EgQtiukyYk == qCWTtaWdJn){QsoXcimdwU = true;}
      if(RSgOafOEsE == ixFwtzXDss){XOGdPOOuBn = true;}
      if(wspGMnJXVf == hBZioyupGA){MEqlpeNyPt = true;}
      if(mzWloYyNKb == ZOmeGeBgVo){AgUnUSQkii = true;}
      while(ixFwtzXDss == RSgOafOEsE){pzZZNKrxjz = true;}
      while(hBZioyupGA == hBZioyupGA){FGEonOyJJF = true;}
      while(ZOmeGeBgVo == ZOmeGeBgVo){khdTOZaFLx = true;}
      if(WlVhHOcJJK == true){WlVhHOcJJK = false;}
      if(dCGhwDGhEk == true){dCGhwDGhEk = false;}
      if(ztqXLUJZoO == true){ztqXLUJZoO = false;}
      if(yphEVueqaZ == true){yphEVueqaZ = false;}
      if(VkfwWWIFhC == true){VkfwWWIFhC = false;}
      if(YScjobtyWm == true){YScjobtyWm = false;}
      if(FCTuMnTBLB == true){FCTuMnTBLB = false;}
      if(XOGdPOOuBn == true){XOGdPOOuBn = false;}
      if(MEqlpeNyPt == true){MEqlpeNyPt = false;}
      if(AgUnUSQkii == true){AgUnUSQkii = false;}
      if(CGsgeJLyUa == true){CGsgeJLyUa = false;}
      if(MzwhaBKhFg == true){MzwhaBKhFg = false;}
      if(ZVlRApsSJw == true){ZVlRApsSJw = false;}
      if(xdLSlFKKHf == true){xdLSlFKKHf = false;}
      if(SPcogBkmNT == true){SPcogBkmNT = false;}
      if(IieCIfUbfn == true){IieCIfUbfn = false;}
      if(QsoXcimdwU == true){QsoXcimdwU = false;}
      if(pzZZNKrxjz == true){pzZZNKrxjz = false;}
      if(FGEonOyJJF == true){FGEonOyJJF = false;}
      if(khdTOZaFLx == true){khdTOZaFLx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UXESZRIOTC
{ 
  void YcBBdBzwfC()
  { 
      bool TbcGrLJLCO = false;
      bool nLOzmdriCM = false;
      bool XVVmElUgEJ = false;
      bool PyqJMsIibJ = false;
      bool rxAmlMjuqX = false;
      bool tNlfkxFoCG = false;
      bool qcHrypUFls = false;
      bool UJHrTaViAq = false;
      bool CYpfOBLLXO = false;
      bool mTfUSPoHnw = false;
      bool rdIxCkGtLK = false;
      bool bVnKERladx = false;
      bool dJgWGBclZE = false;
      bool kNuEzXPscc = false;
      bool tQzNmQeVQA = false;
      bool cOcpRixlpB = false;
      bool IUUHYNajLg = false;
      bool BsyACMJTjo = false;
      bool WHUYaWjElP = false;
      bool adCbUZwrnY = false;
      string mEqplCLVeX;
      string GMEqzoqqSR;
      string OFQWsgRiKq;
      string iqaShGTFlc;
      string xahCENYxzx;
      string eKpqYhnTxF;
      string jbKmnOkkIr;
      string UkEoTmXOSf;
      string HUiNMYBjsA;
      string SAIgrUQtNo;
      string cmoGbsFAWl;
      string KZARxPrwaP;
      string NAqIZUcXxy;
      string WcAcCUebkS;
      string TANHpszqic;
      string bUTybbuggH;
      string QgDXOgYXOc;
      string jQKHuMmjRg;
      string UloTVCJCBa;
      string YyudClxorI;
      if(mEqplCLVeX == cmoGbsFAWl){TbcGrLJLCO = true;}
      else if(cmoGbsFAWl == mEqplCLVeX){rdIxCkGtLK = true;}
      if(GMEqzoqqSR == KZARxPrwaP){nLOzmdriCM = true;}
      else if(KZARxPrwaP == GMEqzoqqSR){bVnKERladx = true;}
      if(OFQWsgRiKq == NAqIZUcXxy){XVVmElUgEJ = true;}
      else if(NAqIZUcXxy == OFQWsgRiKq){dJgWGBclZE = true;}
      if(iqaShGTFlc == WcAcCUebkS){PyqJMsIibJ = true;}
      else if(WcAcCUebkS == iqaShGTFlc){kNuEzXPscc = true;}
      if(xahCENYxzx == TANHpszqic){rxAmlMjuqX = true;}
      else if(TANHpszqic == xahCENYxzx){tQzNmQeVQA = true;}
      if(eKpqYhnTxF == bUTybbuggH){tNlfkxFoCG = true;}
      else if(bUTybbuggH == eKpqYhnTxF){cOcpRixlpB = true;}
      if(jbKmnOkkIr == QgDXOgYXOc){qcHrypUFls = true;}
      else if(QgDXOgYXOc == jbKmnOkkIr){IUUHYNajLg = true;}
      if(UkEoTmXOSf == jQKHuMmjRg){UJHrTaViAq = true;}
      if(HUiNMYBjsA == UloTVCJCBa){CYpfOBLLXO = true;}
      if(SAIgrUQtNo == YyudClxorI){mTfUSPoHnw = true;}
      while(jQKHuMmjRg == UkEoTmXOSf){BsyACMJTjo = true;}
      while(UloTVCJCBa == UloTVCJCBa){WHUYaWjElP = true;}
      while(YyudClxorI == YyudClxorI){adCbUZwrnY = true;}
      if(TbcGrLJLCO == true){TbcGrLJLCO = false;}
      if(nLOzmdriCM == true){nLOzmdriCM = false;}
      if(XVVmElUgEJ == true){XVVmElUgEJ = false;}
      if(PyqJMsIibJ == true){PyqJMsIibJ = false;}
      if(rxAmlMjuqX == true){rxAmlMjuqX = false;}
      if(tNlfkxFoCG == true){tNlfkxFoCG = false;}
      if(qcHrypUFls == true){qcHrypUFls = false;}
      if(UJHrTaViAq == true){UJHrTaViAq = false;}
      if(CYpfOBLLXO == true){CYpfOBLLXO = false;}
      if(mTfUSPoHnw == true){mTfUSPoHnw = false;}
      if(rdIxCkGtLK == true){rdIxCkGtLK = false;}
      if(bVnKERladx == true){bVnKERladx = false;}
      if(dJgWGBclZE == true){dJgWGBclZE = false;}
      if(kNuEzXPscc == true){kNuEzXPscc = false;}
      if(tQzNmQeVQA == true){tQzNmQeVQA = false;}
      if(cOcpRixlpB == true){cOcpRixlpB = false;}
      if(IUUHYNajLg == true){IUUHYNajLg = false;}
      if(BsyACMJTjo == true){BsyACMJTjo = false;}
      if(WHUYaWjElP == true){WHUYaWjElP = false;}
      if(adCbUZwrnY == true){adCbUZwrnY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ODMATQGTFE
{ 
  void IxIYgoxDXl()
  { 
      bool dOiKSmuDfk = false;
      bool gubbkOilOA = false;
      bool JWeEOyqWXm = false;
      bool ANRkTVpkMC = false;
      bool fIBdgXXapY = false;
      bool YjEApGjdwT = false;
      bool wXesjTcqHO = false;
      bool XyZMUBVAWp = false;
      bool aPgyOPIQuN = false;
      bool lLnsFHcHsN = false;
      bool tgTaBZKrfn = false;
      bool jiGFsgqfeU = false;
      bool KLutcMJgGM = false;
      bool YOHJusuGxo = false;
      bool FQkHcDEizX = false;
      bool QwcYCikZyo = false;
      bool PdkTOVbxJz = false;
      bool ljipOtanQY = false;
      bool HaghwckhGM = false;
      bool IVIIYaeRrG = false;
      string AyyYhZhTPD;
      string OVPdLOSEAr;
      string VTQjebeYFh;
      string PwKpBfqsLY;
      string OGlxofjxno;
      string pKqHNfhOtF;
      string tINgmSKYbf;
      string XZracOhTuy;
      string rhkPrFEDbU;
      string ycyFdFrFJW;
      string VKUHRPRPdy;
      string yOSwNMXxoh;
      string NGwHhtbmxX;
      string WbJYcgNcyb;
      string moZcViJCqR;
      string htQbIOONZW;
      string neRFbVFtSg;
      string ytzMuXgSky;
      string kZufpbLhPO;
      string SADbnHWTBz;
      if(AyyYhZhTPD == VKUHRPRPdy){dOiKSmuDfk = true;}
      else if(VKUHRPRPdy == AyyYhZhTPD){tgTaBZKrfn = true;}
      if(OVPdLOSEAr == yOSwNMXxoh){gubbkOilOA = true;}
      else if(yOSwNMXxoh == OVPdLOSEAr){jiGFsgqfeU = true;}
      if(VTQjebeYFh == NGwHhtbmxX){JWeEOyqWXm = true;}
      else if(NGwHhtbmxX == VTQjebeYFh){KLutcMJgGM = true;}
      if(PwKpBfqsLY == WbJYcgNcyb){ANRkTVpkMC = true;}
      else if(WbJYcgNcyb == PwKpBfqsLY){YOHJusuGxo = true;}
      if(OGlxofjxno == moZcViJCqR){fIBdgXXapY = true;}
      else if(moZcViJCqR == OGlxofjxno){FQkHcDEizX = true;}
      if(pKqHNfhOtF == htQbIOONZW){YjEApGjdwT = true;}
      else if(htQbIOONZW == pKqHNfhOtF){QwcYCikZyo = true;}
      if(tINgmSKYbf == neRFbVFtSg){wXesjTcqHO = true;}
      else if(neRFbVFtSg == tINgmSKYbf){PdkTOVbxJz = true;}
      if(XZracOhTuy == ytzMuXgSky){XyZMUBVAWp = true;}
      if(rhkPrFEDbU == kZufpbLhPO){aPgyOPIQuN = true;}
      if(ycyFdFrFJW == SADbnHWTBz){lLnsFHcHsN = true;}
      while(ytzMuXgSky == XZracOhTuy){ljipOtanQY = true;}
      while(kZufpbLhPO == kZufpbLhPO){HaghwckhGM = true;}
      while(SADbnHWTBz == SADbnHWTBz){IVIIYaeRrG = true;}
      if(dOiKSmuDfk == true){dOiKSmuDfk = false;}
      if(gubbkOilOA == true){gubbkOilOA = false;}
      if(JWeEOyqWXm == true){JWeEOyqWXm = false;}
      if(ANRkTVpkMC == true){ANRkTVpkMC = false;}
      if(fIBdgXXapY == true){fIBdgXXapY = false;}
      if(YjEApGjdwT == true){YjEApGjdwT = false;}
      if(wXesjTcqHO == true){wXesjTcqHO = false;}
      if(XyZMUBVAWp == true){XyZMUBVAWp = false;}
      if(aPgyOPIQuN == true){aPgyOPIQuN = false;}
      if(lLnsFHcHsN == true){lLnsFHcHsN = false;}
      if(tgTaBZKrfn == true){tgTaBZKrfn = false;}
      if(jiGFsgqfeU == true){jiGFsgqfeU = false;}
      if(KLutcMJgGM == true){KLutcMJgGM = false;}
      if(YOHJusuGxo == true){YOHJusuGxo = false;}
      if(FQkHcDEizX == true){FQkHcDEizX = false;}
      if(QwcYCikZyo == true){QwcYCikZyo = false;}
      if(PdkTOVbxJz == true){PdkTOVbxJz = false;}
      if(ljipOtanQY == true){ljipOtanQY = false;}
      if(HaghwckhGM == true){HaghwckhGM = false;}
      if(IVIIYaeRrG == true){IVIIYaeRrG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHWKASLZXJ
{ 
  void kJDrKhCBqJ()
  { 
      bool YSgucdZXdf = false;
      bool yBPzooTQko = false;
      bool lwwVZOMDzC = false;
      bool JwTTueyASo = false;
      bool xLfVQayTqb = false;
      bool UitwUbWKVO = false;
      bool RWXbWChwDJ = false;
      bool qTyuqZQZEz = false;
      bool PrLWhZCWyS = false;
      bool ImeDXanEzO = false;
      bool rBQgkBkyFt = false;
      bool LwGWyYKBsw = false;
      bool zLxjADntXP = false;
      bool lLaoGObdkg = false;
      bool oEQEHMfIFy = false;
      bool QmKCOfDfgh = false;
      bool MqZpIAVQPj = false;
      bool xfPMHuuscn = false;
      bool WenYyzBXZZ = false;
      bool KuxDTxdZuH = false;
      string eWNHhDUdXY;
      string hqcJbhtyNI;
      string hSiQAAUuDO;
      string JhKgiHGCRW;
      string BnBhLVGUne;
      string JrGpnLnwHg;
      string hYaIOzguaU;
      string arfqGtRAFe;
      string tzGXERbTrW;
      string TJtkncMsTM;
      string nKtTERLOit;
      string tnqbmhSDDx;
      string WMDDAQxuCd;
      string gYgrqjFmTl;
      string FMkycfRRyG;
      string JJoVpaGqTm;
      string UQMFMVHzkC;
      string cfiRqJbEaU;
      string yewwTXiKCP;
      string cOSfRoAekG;
      if(eWNHhDUdXY == nKtTERLOit){YSgucdZXdf = true;}
      else if(nKtTERLOit == eWNHhDUdXY){rBQgkBkyFt = true;}
      if(hqcJbhtyNI == tnqbmhSDDx){yBPzooTQko = true;}
      else if(tnqbmhSDDx == hqcJbhtyNI){LwGWyYKBsw = true;}
      if(hSiQAAUuDO == WMDDAQxuCd){lwwVZOMDzC = true;}
      else if(WMDDAQxuCd == hSiQAAUuDO){zLxjADntXP = true;}
      if(JhKgiHGCRW == gYgrqjFmTl){JwTTueyASo = true;}
      else if(gYgrqjFmTl == JhKgiHGCRW){lLaoGObdkg = true;}
      if(BnBhLVGUne == FMkycfRRyG){xLfVQayTqb = true;}
      else if(FMkycfRRyG == BnBhLVGUne){oEQEHMfIFy = true;}
      if(JrGpnLnwHg == JJoVpaGqTm){UitwUbWKVO = true;}
      else if(JJoVpaGqTm == JrGpnLnwHg){QmKCOfDfgh = true;}
      if(hYaIOzguaU == UQMFMVHzkC){RWXbWChwDJ = true;}
      else if(UQMFMVHzkC == hYaIOzguaU){MqZpIAVQPj = true;}
      if(arfqGtRAFe == cfiRqJbEaU){qTyuqZQZEz = true;}
      if(tzGXERbTrW == yewwTXiKCP){PrLWhZCWyS = true;}
      if(TJtkncMsTM == cOSfRoAekG){ImeDXanEzO = true;}
      while(cfiRqJbEaU == arfqGtRAFe){xfPMHuuscn = true;}
      while(yewwTXiKCP == yewwTXiKCP){WenYyzBXZZ = true;}
      while(cOSfRoAekG == cOSfRoAekG){KuxDTxdZuH = true;}
      if(YSgucdZXdf == true){YSgucdZXdf = false;}
      if(yBPzooTQko == true){yBPzooTQko = false;}
      if(lwwVZOMDzC == true){lwwVZOMDzC = false;}
      if(JwTTueyASo == true){JwTTueyASo = false;}
      if(xLfVQayTqb == true){xLfVQayTqb = false;}
      if(UitwUbWKVO == true){UitwUbWKVO = false;}
      if(RWXbWChwDJ == true){RWXbWChwDJ = false;}
      if(qTyuqZQZEz == true){qTyuqZQZEz = false;}
      if(PrLWhZCWyS == true){PrLWhZCWyS = false;}
      if(ImeDXanEzO == true){ImeDXanEzO = false;}
      if(rBQgkBkyFt == true){rBQgkBkyFt = false;}
      if(LwGWyYKBsw == true){LwGWyYKBsw = false;}
      if(zLxjADntXP == true){zLxjADntXP = false;}
      if(lLaoGObdkg == true){lLaoGObdkg = false;}
      if(oEQEHMfIFy == true){oEQEHMfIFy = false;}
      if(QmKCOfDfgh == true){QmKCOfDfgh = false;}
      if(MqZpIAVQPj == true){MqZpIAVQPj = false;}
      if(xfPMHuuscn == true){xfPMHuuscn = false;}
      if(WenYyzBXZZ == true){WenYyzBXZZ = false;}
      if(KuxDTxdZuH == true){KuxDTxdZuH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBNZCJRUHA
{ 
  void ldABCSOMAg()
  { 
      bool pnYpZcSJol = false;
      bool oJUeEhEmrg = false;
      bool NmWqNCPKSQ = false;
      bool FOLJIuHokG = false;
      bool hweecExuUS = false;
      bool wxgnICRgcW = false;
      bool MHpXfaxLWJ = false;
      bool ZPCkyRIqOI = false;
      bool FUoAUIgWBF = false;
      bool caMNsZFHyC = false;
      bool GkXLrfuupp = false;
      bool tZRTRrSoCX = false;
      bool saJRfzDnrX = false;
      bool MBsLBTwdIn = false;
      bool MkgLKDIrwB = false;
      bool HPEaJfbGes = false;
      bool cGDRdsgGRx = false;
      bool wngOKHtyGc = false;
      bool pKrpQwwSCV = false;
      bool royOKGhPhR = false;
      string cupLtLuuza;
      string trIFZEIIFA;
      string XfZMugeYgY;
      string BfZipAkFLP;
      string jQklQiBmxS;
      string gfsusxVcQM;
      string gVNZZNSZOZ;
      string TDxoQHtmwL;
      string fqbOrUmeos;
      string eInziNDLLC;
      string QaXXzciDdl;
      string ChfFgotzhE;
      string ZnjVtLPyFC;
      string EiasuETDOO;
      string liADpwbiRt;
      string TDcHccpBcn;
      string NkyahTGmKb;
      string UpkTSqmgfy;
      string iffKiAFTQS;
      string NRaZABkYVV;
      if(cupLtLuuza == QaXXzciDdl){pnYpZcSJol = true;}
      else if(QaXXzciDdl == cupLtLuuza){GkXLrfuupp = true;}
      if(trIFZEIIFA == ChfFgotzhE){oJUeEhEmrg = true;}
      else if(ChfFgotzhE == trIFZEIIFA){tZRTRrSoCX = true;}
      if(XfZMugeYgY == ZnjVtLPyFC){NmWqNCPKSQ = true;}
      else if(ZnjVtLPyFC == XfZMugeYgY){saJRfzDnrX = true;}
      if(BfZipAkFLP == EiasuETDOO){FOLJIuHokG = true;}
      else if(EiasuETDOO == BfZipAkFLP){MBsLBTwdIn = true;}
      if(jQklQiBmxS == liADpwbiRt){hweecExuUS = true;}
      else if(liADpwbiRt == jQklQiBmxS){MkgLKDIrwB = true;}
      if(gfsusxVcQM == TDcHccpBcn){wxgnICRgcW = true;}
      else if(TDcHccpBcn == gfsusxVcQM){HPEaJfbGes = true;}
      if(gVNZZNSZOZ == NkyahTGmKb){MHpXfaxLWJ = true;}
      else if(NkyahTGmKb == gVNZZNSZOZ){cGDRdsgGRx = true;}
      if(TDxoQHtmwL == UpkTSqmgfy){ZPCkyRIqOI = true;}
      if(fqbOrUmeos == iffKiAFTQS){FUoAUIgWBF = true;}
      if(eInziNDLLC == NRaZABkYVV){caMNsZFHyC = true;}
      while(UpkTSqmgfy == TDxoQHtmwL){wngOKHtyGc = true;}
      while(iffKiAFTQS == iffKiAFTQS){pKrpQwwSCV = true;}
      while(NRaZABkYVV == NRaZABkYVV){royOKGhPhR = true;}
      if(pnYpZcSJol == true){pnYpZcSJol = false;}
      if(oJUeEhEmrg == true){oJUeEhEmrg = false;}
      if(NmWqNCPKSQ == true){NmWqNCPKSQ = false;}
      if(FOLJIuHokG == true){FOLJIuHokG = false;}
      if(hweecExuUS == true){hweecExuUS = false;}
      if(wxgnICRgcW == true){wxgnICRgcW = false;}
      if(MHpXfaxLWJ == true){MHpXfaxLWJ = false;}
      if(ZPCkyRIqOI == true){ZPCkyRIqOI = false;}
      if(FUoAUIgWBF == true){FUoAUIgWBF = false;}
      if(caMNsZFHyC == true){caMNsZFHyC = false;}
      if(GkXLrfuupp == true){GkXLrfuupp = false;}
      if(tZRTRrSoCX == true){tZRTRrSoCX = false;}
      if(saJRfzDnrX == true){saJRfzDnrX = false;}
      if(MBsLBTwdIn == true){MBsLBTwdIn = false;}
      if(MkgLKDIrwB == true){MkgLKDIrwB = false;}
      if(HPEaJfbGes == true){HPEaJfbGes = false;}
      if(cGDRdsgGRx == true){cGDRdsgGRx = false;}
      if(wngOKHtyGc == true){wngOKHtyGc = false;}
      if(pKrpQwwSCV == true){pKrpQwwSCV = false;}
      if(royOKGhPhR == true){royOKGhPhR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWSCNKFYTF
{ 
  void DumsPRtFro()
  { 
      bool VGYixklDXX = false;
      bool LOsppzRIFs = false;
      bool IQgbieFcwD = false;
      bool kxHJTHiKFu = false;
      bool kMPeXVRRNu = false;
      bool syegXFYxAS = false;
      bool fJHTlOGjWi = false;
      bool QGDJIwACDN = false;
      bool MnOAJmRakN = false;
      bool ilKlPbEusJ = false;
      bool OhteeluVYb = false;
      bool EWslFquHKz = false;
      bool wfyIzdwQtg = false;
      bool rEItzdsiUW = false;
      bool rwBJJMrXgY = false;
      bool fxktMhjlfB = false;
      bool pdbrjANzmb = false;
      bool yLlmGAenzl = false;
      bool kYjVAtTOhQ = false;
      bool tGCTgNUJZI = false;
      string pFxtPGptgA;
      string OluTyyOLDV;
      string dAfyZHsChd;
      string lkpRgcwtLm;
      string nYujDwBSRM;
      string WHRAPpYzTH;
      string MmMDNcwcmU;
      string CUAQgFEutd;
      string GakUGdSpCq;
      string EwaDZBMrVZ;
      string AXfwKCHBSJ;
      string kdFoBlCrwj;
      string JFauQFswpf;
      string rMYTdhunJE;
      string VRXrFZqkCn;
      string zUwlQtxjfE;
      string ILKlRYEkLT;
      string pNhrNrhhpp;
      string OIsCgXQmDj;
      string jLHEuKGkag;
      if(pFxtPGptgA == AXfwKCHBSJ){VGYixklDXX = true;}
      else if(AXfwKCHBSJ == pFxtPGptgA){OhteeluVYb = true;}
      if(OluTyyOLDV == kdFoBlCrwj){LOsppzRIFs = true;}
      else if(kdFoBlCrwj == OluTyyOLDV){EWslFquHKz = true;}
      if(dAfyZHsChd == JFauQFswpf){IQgbieFcwD = true;}
      else if(JFauQFswpf == dAfyZHsChd){wfyIzdwQtg = true;}
      if(lkpRgcwtLm == rMYTdhunJE){kxHJTHiKFu = true;}
      else if(rMYTdhunJE == lkpRgcwtLm){rEItzdsiUW = true;}
      if(nYujDwBSRM == VRXrFZqkCn){kMPeXVRRNu = true;}
      else if(VRXrFZqkCn == nYujDwBSRM){rwBJJMrXgY = true;}
      if(WHRAPpYzTH == zUwlQtxjfE){syegXFYxAS = true;}
      else if(zUwlQtxjfE == WHRAPpYzTH){fxktMhjlfB = true;}
      if(MmMDNcwcmU == ILKlRYEkLT){fJHTlOGjWi = true;}
      else if(ILKlRYEkLT == MmMDNcwcmU){pdbrjANzmb = true;}
      if(CUAQgFEutd == pNhrNrhhpp){QGDJIwACDN = true;}
      if(GakUGdSpCq == OIsCgXQmDj){MnOAJmRakN = true;}
      if(EwaDZBMrVZ == jLHEuKGkag){ilKlPbEusJ = true;}
      while(pNhrNrhhpp == CUAQgFEutd){yLlmGAenzl = true;}
      while(OIsCgXQmDj == OIsCgXQmDj){kYjVAtTOhQ = true;}
      while(jLHEuKGkag == jLHEuKGkag){tGCTgNUJZI = true;}
      if(VGYixklDXX == true){VGYixklDXX = false;}
      if(LOsppzRIFs == true){LOsppzRIFs = false;}
      if(IQgbieFcwD == true){IQgbieFcwD = false;}
      if(kxHJTHiKFu == true){kxHJTHiKFu = false;}
      if(kMPeXVRRNu == true){kMPeXVRRNu = false;}
      if(syegXFYxAS == true){syegXFYxAS = false;}
      if(fJHTlOGjWi == true){fJHTlOGjWi = false;}
      if(QGDJIwACDN == true){QGDJIwACDN = false;}
      if(MnOAJmRakN == true){MnOAJmRakN = false;}
      if(ilKlPbEusJ == true){ilKlPbEusJ = false;}
      if(OhteeluVYb == true){OhteeluVYb = false;}
      if(EWslFquHKz == true){EWslFquHKz = false;}
      if(wfyIzdwQtg == true){wfyIzdwQtg = false;}
      if(rEItzdsiUW == true){rEItzdsiUW = false;}
      if(rwBJJMrXgY == true){rwBJJMrXgY = false;}
      if(fxktMhjlfB == true){fxktMhjlfB = false;}
      if(pdbrjANzmb == true){pdbrjANzmb = false;}
      if(yLlmGAenzl == true){yLlmGAenzl = false;}
      if(kYjVAtTOhQ == true){kYjVAtTOhQ = false;}
      if(tGCTgNUJZI == true){tGCTgNUJZI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XZACGZHEUN
{ 
  void fNcRymCHlz()
  { 
      bool PgyzGCVKXO = false;
      bool bIxRKmXddm = false;
      bool VFGFDrzGGY = false;
      bool hSidKZETPh = false;
      bool JbCnNpdDdN = false;
      bool SqOdXKarwO = false;
      bool DPEzgJZSGj = false;
      bool hEOucsCSrM = false;
      bool NubsFpDEGA = false;
      bool zLWBesXDHD = false;
      bool QKwteNcSAd = false;
      bool HIAiAHnLsp = false;
      bool GUMGjVgNQj = false;
      bool VzLnwDzgNr = false;
      bool NjEbrqLnAW = false;
      bool FMKQwwypKI = false;
      bool fOBQIIwLmw = false;
      bool IGxAcVPjNr = false;
      bool KsMtdIntrA = false;
      bool EIWELyhnTj = false;
      string xMwHfhCfCb;
      string sNKulirAdS;
      string FLWCwXcwHb;
      string kzMcDcOdTs;
      string IqoZmJYmWj;
      string ArfgdkotLI;
      string EGYZptAgrI;
      string TOfjJOVwOl;
      string ypZWbsSfyR;
      string mUSLnCSPjs;
      string IqtNQlLwWO;
      string PreYJOfBxx;
      string aUiZVywUuH;
      string wFMVdHuMGp;
      string hWIiCupsBZ;
      string VQSmSnIUrR;
      string oqAPSJeIuC;
      string STtHOELzWZ;
      string HCSVkfmZCp;
      string zaUnApVsQs;
      if(xMwHfhCfCb == IqtNQlLwWO){PgyzGCVKXO = true;}
      else if(IqtNQlLwWO == xMwHfhCfCb){QKwteNcSAd = true;}
      if(sNKulirAdS == PreYJOfBxx){bIxRKmXddm = true;}
      else if(PreYJOfBxx == sNKulirAdS){HIAiAHnLsp = true;}
      if(FLWCwXcwHb == aUiZVywUuH){VFGFDrzGGY = true;}
      else if(aUiZVywUuH == FLWCwXcwHb){GUMGjVgNQj = true;}
      if(kzMcDcOdTs == wFMVdHuMGp){hSidKZETPh = true;}
      else if(wFMVdHuMGp == kzMcDcOdTs){VzLnwDzgNr = true;}
      if(IqoZmJYmWj == hWIiCupsBZ){JbCnNpdDdN = true;}
      else if(hWIiCupsBZ == IqoZmJYmWj){NjEbrqLnAW = true;}
      if(ArfgdkotLI == VQSmSnIUrR){SqOdXKarwO = true;}
      else if(VQSmSnIUrR == ArfgdkotLI){FMKQwwypKI = true;}
      if(EGYZptAgrI == oqAPSJeIuC){DPEzgJZSGj = true;}
      else if(oqAPSJeIuC == EGYZptAgrI){fOBQIIwLmw = true;}
      if(TOfjJOVwOl == STtHOELzWZ){hEOucsCSrM = true;}
      if(ypZWbsSfyR == HCSVkfmZCp){NubsFpDEGA = true;}
      if(mUSLnCSPjs == zaUnApVsQs){zLWBesXDHD = true;}
      while(STtHOELzWZ == TOfjJOVwOl){IGxAcVPjNr = true;}
      while(HCSVkfmZCp == HCSVkfmZCp){KsMtdIntrA = true;}
      while(zaUnApVsQs == zaUnApVsQs){EIWELyhnTj = true;}
      if(PgyzGCVKXO == true){PgyzGCVKXO = false;}
      if(bIxRKmXddm == true){bIxRKmXddm = false;}
      if(VFGFDrzGGY == true){VFGFDrzGGY = false;}
      if(hSidKZETPh == true){hSidKZETPh = false;}
      if(JbCnNpdDdN == true){JbCnNpdDdN = false;}
      if(SqOdXKarwO == true){SqOdXKarwO = false;}
      if(DPEzgJZSGj == true){DPEzgJZSGj = false;}
      if(hEOucsCSrM == true){hEOucsCSrM = false;}
      if(NubsFpDEGA == true){NubsFpDEGA = false;}
      if(zLWBesXDHD == true){zLWBesXDHD = false;}
      if(QKwteNcSAd == true){QKwteNcSAd = false;}
      if(HIAiAHnLsp == true){HIAiAHnLsp = false;}
      if(GUMGjVgNQj == true){GUMGjVgNQj = false;}
      if(VzLnwDzgNr == true){VzLnwDzgNr = false;}
      if(NjEbrqLnAW == true){NjEbrqLnAW = false;}
      if(FMKQwwypKI == true){FMKQwwypKI = false;}
      if(fOBQIIwLmw == true){fOBQIIwLmw = false;}
      if(IGxAcVPjNr == true){IGxAcVPjNr = false;}
      if(KsMtdIntrA == true){KsMtdIntrA = false;}
      if(EIWELyhnTj == true){EIWELyhnTj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NTHFXDZIVR
{ 
  void MWJelzoork()
  { 
      bool GHNzhIhcWU = false;
      bool egWhkagRAs = false;
      bool bIcfWxVBlJ = false;
      bool IAsKHKLgXD = false;
      bool oHYJAxOVeo = false;
      bool mNUmoxegck = false;
      bool mfqMMdnLaa = false;
      bool OzsxDTjSfZ = false;
      bool hzVxWufFVK = false;
      bool eeElQIQMxW = false;
      bool JDtEZmTXjV = false;
      bool NMACDmKtoQ = false;
      bool xipQwiuGfu = false;
      bool DWUJQeERWj = false;
      bool bHVzwSdBid = false;
      bool yWWfYZNdIp = false;
      bool rMqoRpqqlX = false;
      bool hrXFooNpTd = false;
      bool EsWCwgznkp = false;
      bool RaJfqOQghG = false;
      string mhMaEjWgIs;
      string sBnYKnLLFK;
      string ntUctCWanb;
      string yCEfEZtxox;
      string GfeIpFlcFf;
      string MSDMusNifC;
      string NwsgtpxHTk;
      string tOVHEIOLmn;
      string PtUHOfzqjK;
      string MLQmjJlxOz;
      string HdIUlyxuIm;
      string eBurlTalSN;
      string qGXIYhyhXu;
      string WQwngkkAUP;
      string iDixfKPYAQ;
      string izeBIBGzwE;
      string AOXMQNEHLB;
      string hZRCemWZcN;
      string SYgGLWkuee;
      string dkEQPUeVgR;
      if(mhMaEjWgIs == HdIUlyxuIm){GHNzhIhcWU = true;}
      else if(HdIUlyxuIm == mhMaEjWgIs){JDtEZmTXjV = true;}
      if(sBnYKnLLFK == eBurlTalSN){egWhkagRAs = true;}
      else if(eBurlTalSN == sBnYKnLLFK){NMACDmKtoQ = true;}
      if(ntUctCWanb == qGXIYhyhXu){bIcfWxVBlJ = true;}
      else if(qGXIYhyhXu == ntUctCWanb){xipQwiuGfu = true;}
      if(yCEfEZtxox == WQwngkkAUP){IAsKHKLgXD = true;}
      else if(WQwngkkAUP == yCEfEZtxox){DWUJQeERWj = true;}
      if(GfeIpFlcFf == iDixfKPYAQ){oHYJAxOVeo = true;}
      else if(iDixfKPYAQ == GfeIpFlcFf){bHVzwSdBid = true;}
      if(MSDMusNifC == izeBIBGzwE){mNUmoxegck = true;}
      else if(izeBIBGzwE == MSDMusNifC){yWWfYZNdIp = true;}
      if(NwsgtpxHTk == AOXMQNEHLB){mfqMMdnLaa = true;}
      else if(AOXMQNEHLB == NwsgtpxHTk){rMqoRpqqlX = true;}
      if(tOVHEIOLmn == hZRCemWZcN){OzsxDTjSfZ = true;}
      if(PtUHOfzqjK == SYgGLWkuee){hzVxWufFVK = true;}
      if(MLQmjJlxOz == dkEQPUeVgR){eeElQIQMxW = true;}
      while(hZRCemWZcN == tOVHEIOLmn){hrXFooNpTd = true;}
      while(SYgGLWkuee == SYgGLWkuee){EsWCwgznkp = true;}
      while(dkEQPUeVgR == dkEQPUeVgR){RaJfqOQghG = true;}
      if(GHNzhIhcWU == true){GHNzhIhcWU = false;}
      if(egWhkagRAs == true){egWhkagRAs = false;}
      if(bIcfWxVBlJ == true){bIcfWxVBlJ = false;}
      if(IAsKHKLgXD == true){IAsKHKLgXD = false;}
      if(oHYJAxOVeo == true){oHYJAxOVeo = false;}
      if(mNUmoxegck == true){mNUmoxegck = false;}
      if(mfqMMdnLaa == true){mfqMMdnLaa = false;}
      if(OzsxDTjSfZ == true){OzsxDTjSfZ = false;}
      if(hzVxWufFVK == true){hzVxWufFVK = false;}
      if(eeElQIQMxW == true){eeElQIQMxW = false;}
      if(JDtEZmTXjV == true){JDtEZmTXjV = false;}
      if(NMACDmKtoQ == true){NMACDmKtoQ = false;}
      if(xipQwiuGfu == true){xipQwiuGfu = false;}
      if(DWUJQeERWj == true){DWUJQeERWj = false;}
      if(bHVzwSdBid == true){bHVzwSdBid = false;}
      if(yWWfYZNdIp == true){yWWfYZNdIp = false;}
      if(rMqoRpqqlX == true){rMqoRpqqlX = false;}
      if(hrXFooNpTd == true){hrXFooNpTd = false;}
      if(EsWCwgznkp == true){EsWCwgznkp = false;}
      if(RaJfqOQghG == true){RaJfqOQghG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TIJKKCRXPR
{ 
  void dxZDzBHLra()
  { 
      bool ouXUFXkqhc = false;
      bool tGsGBSFRSU = false;
      bool fgSNOPSaxL = false;
      bool ugFOajyigC = false;
      bool wejZNkqaOG = false;
      bool HGayZIcKFo = false;
      bool EJtWgMBdeQ = false;
      bool UVkPXAwrAc = false;
      bool XrLqDoGHoR = false;
      bool HmdqxmkNsA = false;
      bool jMuykkUKZY = false;
      bool MjKbQMyDSq = false;
      bool GsoNJgrsRk = false;
      bool PizzrLxNFS = false;
      bool TugPFXcBZk = false;
      bool oguBtpXhoD = false;
      bool rarnJckLiF = false;
      bool OjyzXKMZHl = false;
      bool EpTgwhnxEC = false;
      bool nPYBarDrFb = false;
      string RkOxaJEGsr;
      string gpwDfjNTrf;
      string HqjBmzRXpl;
      string kOwUYNzDhw;
      string HgGIKbBYsO;
      string QZqRlZAMKb;
      string rgPGGSsbdR;
      string jKkwYakbqL;
      string xsdbVLWehz;
      string NmsFEZQzCq;
      string hZtadGourL;
      string oYVydzCnku;
      string uNteExQeqy;
      string JkYzcXyCxO;
      string WbmVJnRtaF;
      string XbNGwUeOVg;
      string oJDsCDzVVG;
      string AzqWYTaYUP;
      string fWDlagWSDH;
      string rjgQYMXsSG;
      if(RkOxaJEGsr == hZtadGourL){ouXUFXkqhc = true;}
      else if(hZtadGourL == RkOxaJEGsr){jMuykkUKZY = true;}
      if(gpwDfjNTrf == oYVydzCnku){tGsGBSFRSU = true;}
      else if(oYVydzCnku == gpwDfjNTrf){MjKbQMyDSq = true;}
      if(HqjBmzRXpl == uNteExQeqy){fgSNOPSaxL = true;}
      else if(uNteExQeqy == HqjBmzRXpl){GsoNJgrsRk = true;}
      if(kOwUYNzDhw == JkYzcXyCxO){ugFOajyigC = true;}
      else if(JkYzcXyCxO == kOwUYNzDhw){PizzrLxNFS = true;}
      if(HgGIKbBYsO == WbmVJnRtaF){wejZNkqaOG = true;}
      else if(WbmVJnRtaF == HgGIKbBYsO){TugPFXcBZk = true;}
      if(QZqRlZAMKb == XbNGwUeOVg){HGayZIcKFo = true;}
      else if(XbNGwUeOVg == QZqRlZAMKb){oguBtpXhoD = true;}
      if(rgPGGSsbdR == oJDsCDzVVG){EJtWgMBdeQ = true;}
      else if(oJDsCDzVVG == rgPGGSsbdR){rarnJckLiF = true;}
      if(jKkwYakbqL == AzqWYTaYUP){UVkPXAwrAc = true;}
      if(xsdbVLWehz == fWDlagWSDH){XrLqDoGHoR = true;}
      if(NmsFEZQzCq == rjgQYMXsSG){HmdqxmkNsA = true;}
      while(AzqWYTaYUP == jKkwYakbqL){OjyzXKMZHl = true;}
      while(fWDlagWSDH == fWDlagWSDH){EpTgwhnxEC = true;}
      while(rjgQYMXsSG == rjgQYMXsSG){nPYBarDrFb = true;}
      if(ouXUFXkqhc == true){ouXUFXkqhc = false;}
      if(tGsGBSFRSU == true){tGsGBSFRSU = false;}
      if(fgSNOPSaxL == true){fgSNOPSaxL = false;}
      if(ugFOajyigC == true){ugFOajyigC = false;}
      if(wejZNkqaOG == true){wejZNkqaOG = false;}
      if(HGayZIcKFo == true){HGayZIcKFo = false;}
      if(EJtWgMBdeQ == true){EJtWgMBdeQ = false;}
      if(UVkPXAwrAc == true){UVkPXAwrAc = false;}
      if(XrLqDoGHoR == true){XrLqDoGHoR = false;}
      if(HmdqxmkNsA == true){HmdqxmkNsA = false;}
      if(jMuykkUKZY == true){jMuykkUKZY = false;}
      if(MjKbQMyDSq == true){MjKbQMyDSq = false;}
      if(GsoNJgrsRk == true){GsoNJgrsRk = false;}
      if(PizzrLxNFS == true){PizzrLxNFS = false;}
      if(TugPFXcBZk == true){TugPFXcBZk = false;}
      if(oguBtpXhoD == true){oguBtpXhoD = false;}
      if(rarnJckLiF == true){rarnJckLiF = false;}
      if(OjyzXKMZHl == true){OjyzXKMZHl = false;}
      if(EpTgwhnxEC == true){EpTgwhnxEC = false;}
      if(nPYBarDrFb == true){nPYBarDrFb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YRTEWENQST
{ 
  void cWpcAnsUce()
  { 
      bool YFfGoDRYVp = false;
      bool bKKMOJdmpD = false;
      bool dluIMwDLVz = false;
      bool kijQsUKlVo = false;
      bool MuDhshcfes = false;
      bool yohFalKXss = false;
      bool AFCWEratTt = false;
      bool zqRBqhiMOe = false;
      bool SWgcAwBdoG = false;
      bool KmsboGrfdB = false;
      bool HiMjtHXgOr = false;
      bool CyIOacXZVI = false;
      bool qxEMjLyoLj = false;
      bool pDiNWiJwhs = false;
      bool YTPxELddAL = false;
      bool iSJUJKezAh = false;
      bool IhUdCzPuqr = false;
      bool TaqcjWgHIX = false;
      bool gToABWsNDM = false;
      bool EKwAkpzktE = false;
      string XMczdDpEze;
      string OVeTdKmhfK;
      string qMcLGlWNnL;
      string bOWUdEmoKN;
      string xcQdqzyuGN;
      string CADnwLiQrr;
      string gbPmDzyJpY;
      string WyXSNNuyUH;
      string maGaIbLiYR;
      string VWwRfUMcar;
      string AoFhqDbjah;
      string PjwkEGUoeb;
      string nPjXDACFlr;
      string ARXcGyVYjE;
      string zaHqCkZKMZ;
      string zWyyDjEgep;
      string BWyigxLTeG;
      string jwFZbNIsVR;
      string aqrLrdTYYV;
      string snssDcbYJE;
      if(XMczdDpEze == AoFhqDbjah){YFfGoDRYVp = true;}
      else if(AoFhqDbjah == XMczdDpEze){HiMjtHXgOr = true;}
      if(OVeTdKmhfK == PjwkEGUoeb){bKKMOJdmpD = true;}
      else if(PjwkEGUoeb == OVeTdKmhfK){CyIOacXZVI = true;}
      if(qMcLGlWNnL == nPjXDACFlr){dluIMwDLVz = true;}
      else if(nPjXDACFlr == qMcLGlWNnL){qxEMjLyoLj = true;}
      if(bOWUdEmoKN == ARXcGyVYjE){kijQsUKlVo = true;}
      else if(ARXcGyVYjE == bOWUdEmoKN){pDiNWiJwhs = true;}
      if(xcQdqzyuGN == zaHqCkZKMZ){MuDhshcfes = true;}
      else if(zaHqCkZKMZ == xcQdqzyuGN){YTPxELddAL = true;}
      if(CADnwLiQrr == zWyyDjEgep){yohFalKXss = true;}
      else if(zWyyDjEgep == CADnwLiQrr){iSJUJKezAh = true;}
      if(gbPmDzyJpY == BWyigxLTeG){AFCWEratTt = true;}
      else if(BWyigxLTeG == gbPmDzyJpY){IhUdCzPuqr = true;}
      if(WyXSNNuyUH == jwFZbNIsVR){zqRBqhiMOe = true;}
      if(maGaIbLiYR == aqrLrdTYYV){SWgcAwBdoG = true;}
      if(VWwRfUMcar == snssDcbYJE){KmsboGrfdB = true;}
      while(jwFZbNIsVR == WyXSNNuyUH){TaqcjWgHIX = true;}
      while(aqrLrdTYYV == aqrLrdTYYV){gToABWsNDM = true;}
      while(snssDcbYJE == snssDcbYJE){EKwAkpzktE = true;}
      if(YFfGoDRYVp == true){YFfGoDRYVp = false;}
      if(bKKMOJdmpD == true){bKKMOJdmpD = false;}
      if(dluIMwDLVz == true){dluIMwDLVz = false;}
      if(kijQsUKlVo == true){kijQsUKlVo = false;}
      if(MuDhshcfes == true){MuDhshcfes = false;}
      if(yohFalKXss == true){yohFalKXss = false;}
      if(AFCWEratTt == true){AFCWEratTt = false;}
      if(zqRBqhiMOe == true){zqRBqhiMOe = false;}
      if(SWgcAwBdoG == true){SWgcAwBdoG = false;}
      if(KmsboGrfdB == true){KmsboGrfdB = false;}
      if(HiMjtHXgOr == true){HiMjtHXgOr = false;}
      if(CyIOacXZVI == true){CyIOacXZVI = false;}
      if(qxEMjLyoLj == true){qxEMjLyoLj = false;}
      if(pDiNWiJwhs == true){pDiNWiJwhs = false;}
      if(YTPxELddAL == true){YTPxELddAL = false;}
      if(iSJUJKezAh == true){iSJUJKezAh = false;}
      if(IhUdCzPuqr == true){IhUdCzPuqr = false;}
      if(TaqcjWgHIX == true){TaqcjWgHIX = false;}
      if(gToABWsNDM == true){gToABWsNDM = false;}
      if(EKwAkpzktE == true){EKwAkpzktE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ACLQPKXWOF
{ 
  void EKqfxilCpl()
  { 
      bool dxaJZImgXp = false;
      bool hjoliTfRwA = false;
      bool AFFzmBUpsg = false;
      bool sYjPkOJprJ = false;
      bool RkUMtRSsZF = false;
      bool xlQMlXrbVX = false;
      bool nwmpxJAYAT = false;
      bool KpYmiPksEU = false;
      bool ibQniHHWdM = false;
      bool VgTUUUydPk = false;
      bool QsrFtHNdcV = false;
      bool mzXBoMfyGo = false;
      bool BcumxcVDRN = false;
      bool RHcSEoiLsb = false;
      bool sdtHZWISfI = false;
      bool ozWZinyEHQ = false;
      bool kKLOEeVEwz = false;
      bool cTEewXimMa = false;
      bool TCXJYRjDjQ = false;
      bool qdDcpiReCt = false;
      string uBWqKUWaHE;
      string VEOCAAwAFR;
      string lowEnFGOGj;
      string rJZlzGZedI;
      string zIWQlKYEmo;
      string LCjIYFESCF;
      string NIUXLLdbDs;
      string ZQWxSdSfRd;
      string fCaRYpZRMs;
      string BGcXupnzEZ;
      string gwBsOtelpu;
      string mYAYYKgCyV;
      string lMOJrSnyCb;
      string pTaqwjAgDe;
      string KnaRGbGDyj;
      string JkAinTgrBu;
      string FfjOETyIbo;
      string KAyTLxkwCP;
      string MkzSRESrDc;
      string CIeIZdDMMm;
      if(uBWqKUWaHE == gwBsOtelpu){dxaJZImgXp = true;}
      else if(gwBsOtelpu == uBWqKUWaHE){QsrFtHNdcV = true;}
      if(VEOCAAwAFR == mYAYYKgCyV){hjoliTfRwA = true;}
      else if(mYAYYKgCyV == VEOCAAwAFR){mzXBoMfyGo = true;}
      if(lowEnFGOGj == lMOJrSnyCb){AFFzmBUpsg = true;}
      else if(lMOJrSnyCb == lowEnFGOGj){BcumxcVDRN = true;}
      if(rJZlzGZedI == pTaqwjAgDe){sYjPkOJprJ = true;}
      else if(pTaqwjAgDe == rJZlzGZedI){RHcSEoiLsb = true;}
      if(zIWQlKYEmo == KnaRGbGDyj){RkUMtRSsZF = true;}
      else if(KnaRGbGDyj == zIWQlKYEmo){sdtHZWISfI = true;}
      if(LCjIYFESCF == JkAinTgrBu){xlQMlXrbVX = true;}
      else if(JkAinTgrBu == LCjIYFESCF){ozWZinyEHQ = true;}
      if(NIUXLLdbDs == FfjOETyIbo){nwmpxJAYAT = true;}
      else if(FfjOETyIbo == NIUXLLdbDs){kKLOEeVEwz = true;}
      if(ZQWxSdSfRd == KAyTLxkwCP){KpYmiPksEU = true;}
      if(fCaRYpZRMs == MkzSRESrDc){ibQniHHWdM = true;}
      if(BGcXupnzEZ == CIeIZdDMMm){VgTUUUydPk = true;}
      while(KAyTLxkwCP == ZQWxSdSfRd){cTEewXimMa = true;}
      while(MkzSRESrDc == MkzSRESrDc){TCXJYRjDjQ = true;}
      while(CIeIZdDMMm == CIeIZdDMMm){qdDcpiReCt = true;}
      if(dxaJZImgXp == true){dxaJZImgXp = false;}
      if(hjoliTfRwA == true){hjoliTfRwA = false;}
      if(AFFzmBUpsg == true){AFFzmBUpsg = false;}
      if(sYjPkOJprJ == true){sYjPkOJprJ = false;}
      if(RkUMtRSsZF == true){RkUMtRSsZF = false;}
      if(xlQMlXrbVX == true){xlQMlXrbVX = false;}
      if(nwmpxJAYAT == true){nwmpxJAYAT = false;}
      if(KpYmiPksEU == true){KpYmiPksEU = false;}
      if(ibQniHHWdM == true){ibQniHHWdM = false;}
      if(VgTUUUydPk == true){VgTUUUydPk = false;}
      if(QsrFtHNdcV == true){QsrFtHNdcV = false;}
      if(mzXBoMfyGo == true){mzXBoMfyGo = false;}
      if(BcumxcVDRN == true){BcumxcVDRN = false;}
      if(RHcSEoiLsb == true){RHcSEoiLsb = false;}
      if(sdtHZWISfI == true){sdtHZWISfI = false;}
      if(ozWZinyEHQ == true){ozWZinyEHQ = false;}
      if(kKLOEeVEwz == true){kKLOEeVEwz = false;}
      if(cTEewXimMa == true){cTEewXimMa = false;}
      if(TCXJYRjDjQ == true){TCXJYRjDjQ = false;}
      if(qdDcpiReCt == true){qdDcpiReCt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PSEQLFTVCQ
{ 
  void TVMKwzFXVP()
  { 
      bool RBETFUXKPx = false;
      bool NLRVoRisbg = false;
      bool wXOuKMuFYu = false;
      bool dsiUahwjTe = false;
      bool ZQjMXCyEid = false;
      bool SdbPGsmIIr = false;
      bool YRkTSUbxtH = false;
      bool UyZwGfnBWI = false;
      bool OqVucAQTNh = false;
      bool umaaGHePtD = false;
      bool ZBJaITEfIa = false;
      bool FllAdhwoqS = false;
      bool DIiMMgXypz = false;
      bool AXGThNgtlI = false;
      bool wkKmbIBaxX = false;
      bool LoYbzRRxOb = false;
      bool wFoJZheRRQ = false;
      bool ABChVSxukD = false;
      bool ewARmKyeUQ = false;
      bool ujfKMpuBMt = false;
      string cdsGzYxlak;
      string qgdCrLZTjr;
      string NgbIuRpyeY;
      string YdHOzesZCE;
      string AjOMGMNrLz;
      string FAIKHuCkLg;
      string iyGBLNZOCM;
      string RARercSOCi;
      string DxmeSYUxGD;
      string cINUVBcMBr;
      string mzpyhFicRe;
      string cmhcckKbhm;
      string sbHziJlwJp;
      string zFNJwEHoxN;
      string oqebapZkrj;
      string pBeNzKqpOY;
      string SmTbeWYYgX;
      string dVdUxBwfXs;
      string iBDZzxaAKk;
      string NQZYuBXDwD;
      if(cdsGzYxlak == mzpyhFicRe){RBETFUXKPx = true;}
      else if(mzpyhFicRe == cdsGzYxlak){ZBJaITEfIa = true;}
      if(qgdCrLZTjr == cmhcckKbhm){NLRVoRisbg = true;}
      else if(cmhcckKbhm == qgdCrLZTjr){FllAdhwoqS = true;}
      if(NgbIuRpyeY == sbHziJlwJp){wXOuKMuFYu = true;}
      else if(sbHziJlwJp == NgbIuRpyeY){DIiMMgXypz = true;}
      if(YdHOzesZCE == zFNJwEHoxN){dsiUahwjTe = true;}
      else if(zFNJwEHoxN == YdHOzesZCE){AXGThNgtlI = true;}
      if(AjOMGMNrLz == oqebapZkrj){ZQjMXCyEid = true;}
      else if(oqebapZkrj == AjOMGMNrLz){wkKmbIBaxX = true;}
      if(FAIKHuCkLg == pBeNzKqpOY){SdbPGsmIIr = true;}
      else if(pBeNzKqpOY == FAIKHuCkLg){LoYbzRRxOb = true;}
      if(iyGBLNZOCM == SmTbeWYYgX){YRkTSUbxtH = true;}
      else if(SmTbeWYYgX == iyGBLNZOCM){wFoJZheRRQ = true;}
      if(RARercSOCi == dVdUxBwfXs){UyZwGfnBWI = true;}
      if(DxmeSYUxGD == iBDZzxaAKk){OqVucAQTNh = true;}
      if(cINUVBcMBr == NQZYuBXDwD){umaaGHePtD = true;}
      while(dVdUxBwfXs == RARercSOCi){ABChVSxukD = true;}
      while(iBDZzxaAKk == iBDZzxaAKk){ewARmKyeUQ = true;}
      while(NQZYuBXDwD == NQZYuBXDwD){ujfKMpuBMt = true;}
      if(RBETFUXKPx == true){RBETFUXKPx = false;}
      if(NLRVoRisbg == true){NLRVoRisbg = false;}
      if(wXOuKMuFYu == true){wXOuKMuFYu = false;}
      if(dsiUahwjTe == true){dsiUahwjTe = false;}
      if(ZQjMXCyEid == true){ZQjMXCyEid = false;}
      if(SdbPGsmIIr == true){SdbPGsmIIr = false;}
      if(YRkTSUbxtH == true){YRkTSUbxtH = false;}
      if(UyZwGfnBWI == true){UyZwGfnBWI = false;}
      if(OqVucAQTNh == true){OqVucAQTNh = false;}
      if(umaaGHePtD == true){umaaGHePtD = false;}
      if(ZBJaITEfIa == true){ZBJaITEfIa = false;}
      if(FllAdhwoqS == true){FllAdhwoqS = false;}
      if(DIiMMgXypz == true){DIiMMgXypz = false;}
      if(AXGThNgtlI == true){AXGThNgtlI = false;}
      if(wkKmbIBaxX == true){wkKmbIBaxX = false;}
      if(LoYbzRRxOb == true){LoYbzRRxOb = false;}
      if(wFoJZheRRQ == true){wFoJZheRRQ = false;}
      if(ABChVSxukD == true){ABChVSxukD = false;}
      if(ewARmKyeUQ == true){ewARmKyeUQ = false;}
      if(ujfKMpuBMt == true){ujfKMpuBMt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRDNTMABLO
{ 
  void qcwYcjYCNR()
  { 
      bool qRBpXVANib = false;
      bool oBxfnPoJSD = false;
      bool hxJrYsJgWF = false;
      bool XUAPDaRlZq = false;
      bool oyjJBOsfSJ = false;
      bool qUZuYsIIQe = false;
      bool MSqdEUBhcN = false;
      bool xDjaOiNzqK = false;
      bool zcONODtEpJ = false;
      bool SJUueVHGFg = false;
      bool MLDEMmjzfp = false;
      bool eIRGeiDdOA = false;
      bool ZxqStminwr = false;
      bool aHsJynZKBa = false;
      bool SuYAdJrOQw = false;
      bool SdqFGPTkJY = false;
      bool EwCnOXPHHp = false;
      bool JscngeXqnk = false;
      bool uTXAZxPnCi = false;
      bool ToAbWWrkkG = false;
      string EZxoXdaGCM;
      string ToqMmIzBKQ;
      string VATyYHgGzC;
      string zcrjWVZeEA;
      string QYOVLmyfsW;
      string GYZjUDFzPQ;
      string wTGzNqwGpR;
      string hTxKAwlylk;
      string IBNcuaCIPS;
      string PaPnDwSOIU;
      string qqpbnmbPiX;
      string RHNdHuGcEl;
      string omqWCGEJGD;
      string dWpRtRKknI;
      string zmYrBINkfI;
      string poKVeDATZg;
      string iSIfstRujp;
      string jUnwlCNyVt;
      string sTcyMoMTlq;
      string QqLGYgdsyG;
      if(EZxoXdaGCM == qqpbnmbPiX){qRBpXVANib = true;}
      else if(qqpbnmbPiX == EZxoXdaGCM){MLDEMmjzfp = true;}
      if(ToqMmIzBKQ == RHNdHuGcEl){oBxfnPoJSD = true;}
      else if(RHNdHuGcEl == ToqMmIzBKQ){eIRGeiDdOA = true;}
      if(VATyYHgGzC == omqWCGEJGD){hxJrYsJgWF = true;}
      else if(omqWCGEJGD == VATyYHgGzC){ZxqStminwr = true;}
      if(zcrjWVZeEA == dWpRtRKknI){XUAPDaRlZq = true;}
      else if(dWpRtRKknI == zcrjWVZeEA){aHsJynZKBa = true;}
      if(QYOVLmyfsW == zmYrBINkfI){oyjJBOsfSJ = true;}
      else if(zmYrBINkfI == QYOVLmyfsW){SuYAdJrOQw = true;}
      if(GYZjUDFzPQ == poKVeDATZg){qUZuYsIIQe = true;}
      else if(poKVeDATZg == GYZjUDFzPQ){SdqFGPTkJY = true;}
      if(wTGzNqwGpR == iSIfstRujp){MSqdEUBhcN = true;}
      else if(iSIfstRujp == wTGzNqwGpR){EwCnOXPHHp = true;}
      if(hTxKAwlylk == jUnwlCNyVt){xDjaOiNzqK = true;}
      if(IBNcuaCIPS == sTcyMoMTlq){zcONODtEpJ = true;}
      if(PaPnDwSOIU == QqLGYgdsyG){SJUueVHGFg = true;}
      while(jUnwlCNyVt == hTxKAwlylk){JscngeXqnk = true;}
      while(sTcyMoMTlq == sTcyMoMTlq){uTXAZxPnCi = true;}
      while(QqLGYgdsyG == QqLGYgdsyG){ToAbWWrkkG = true;}
      if(qRBpXVANib == true){qRBpXVANib = false;}
      if(oBxfnPoJSD == true){oBxfnPoJSD = false;}
      if(hxJrYsJgWF == true){hxJrYsJgWF = false;}
      if(XUAPDaRlZq == true){XUAPDaRlZq = false;}
      if(oyjJBOsfSJ == true){oyjJBOsfSJ = false;}
      if(qUZuYsIIQe == true){qUZuYsIIQe = false;}
      if(MSqdEUBhcN == true){MSqdEUBhcN = false;}
      if(xDjaOiNzqK == true){xDjaOiNzqK = false;}
      if(zcONODtEpJ == true){zcONODtEpJ = false;}
      if(SJUueVHGFg == true){SJUueVHGFg = false;}
      if(MLDEMmjzfp == true){MLDEMmjzfp = false;}
      if(eIRGeiDdOA == true){eIRGeiDdOA = false;}
      if(ZxqStminwr == true){ZxqStminwr = false;}
      if(aHsJynZKBa == true){aHsJynZKBa = false;}
      if(SuYAdJrOQw == true){SuYAdJrOQw = false;}
      if(SdqFGPTkJY == true){SdqFGPTkJY = false;}
      if(EwCnOXPHHp == true){EwCnOXPHHp = false;}
      if(JscngeXqnk == true){JscngeXqnk = false;}
      if(uTXAZxPnCi == true){uTXAZxPnCi = false;}
      if(ToAbWWrkkG == true){ToAbWWrkkG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HPXMQICMSD
{ 
  void OKSahapHWy()
  { 
      bool TabaFpNmME = false;
      bool YmGmWXYUtF = false;
      bool hDSFPOrlbm = false;
      bool qUYgBqYlZn = false;
      bool HLnEZEyTMN = false;
      bool LAfdIQIWKq = false;
      bool ybLZNDOZke = false;
      bool ymuGyVONfK = false;
      bool QYYNbqotYk = false;
      bool hCaiofAOqV = false;
      bool pYigOYFYfl = false;
      bool BtpAaZCxxV = false;
      bool OUAzxwLLQS = false;
      bool VzVJUqpqzD = false;
      bool lPNlinLaIP = false;
      bool cCRVGUYijS = false;
      bool MsIMQCXgei = false;
      bool jLysjzGNPI = false;
      bool kkDApSgADz = false;
      bool SGHgqrHBVg = false;
      string gGUZhyHtqN;
      string nwGFjMjLiI;
      string hdwpaeicTF;
      string OZKxGZkAiu;
      string iCIdOxZYLl;
      string oKuSICJezC;
      string PealyNkIzJ;
      string bibmYeVRad;
      string FJQhPEeroE;
      string PGBffEbVeA;
      string MQZBJGhIsd;
      string gqDVxFOsVt;
      string isTusUgwGU;
      string DzmaRojOXJ;
      string VWyKXXDfia;
      string phAkRSwdIn;
      string YlBYagEbDI;
      string UzUMXMtIXU;
      string RBMfeUzBJy;
      string rFGikjUZjp;
      if(gGUZhyHtqN == MQZBJGhIsd){TabaFpNmME = true;}
      else if(MQZBJGhIsd == gGUZhyHtqN){pYigOYFYfl = true;}
      if(nwGFjMjLiI == gqDVxFOsVt){YmGmWXYUtF = true;}
      else if(gqDVxFOsVt == nwGFjMjLiI){BtpAaZCxxV = true;}
      if(hdwpaeicTF == isTusUgwGU){hDSFPOrlbm = true;}
      else if(isTusUgwGU == hdwpaeicTF){OUAzxwLLQS = true;}
      if(OZKxGZkAiu == DzmaRojOXJ){qUYgBqYlZn = true;}
      else if(DzmaRojOXJ == OZKxGZkAiu){VzVJUqpqzD = true;}
      if(iCIdOxZYLl == VWyKXXDfia){HLnEZEyTMN = true;}
      else if(VWyKXXDfia == iCIdOxZYLl){lPNlinLaIP = true;}
      if(oKuSICJezC == phAkRSwdIn){LAfdIQIWKq = true;}
      else if(phAkRSwdIn == oKuSICJezC){cCRVGUYijS = true;}
      if(PealyNkIzJ == YlBYagEbDI){ybLZNDOZke = true;}
      else if(YlBYagEbDI == PealyNkIzJ){MsIMQCXgei = true;}
      if(bibmYeVRad == UzUMXMtIXU){ymuGyVONfK = true;}
      if(FJQhPEeroE == RBMfeUzBJy){QYYNbqotYk = true;}
      if(PGBffEbVeA == rFGikjUZjp){hCaiofAOqV = true;}
      while(UzUMXMtIXU == bibmYeVRad){jLysjzGNPI = true;}
      while(RBMfeUzBJy == RBMfeUzBJy){kkDApSgADz = true;}
      while(rFGikjUZjp == rFGikjUZjp){SGHgqrHBVg = true;}
      if(TabaFpNmME == true){TabaFpNmME = false;}
      if(YmGmWXYUtF == true){YmGmWXYUtF = false;}
      if(hDSFPOrlbm == true){hDSFPOrlbm = false;}
      if(qUYgBqYlZn == true){qUYgBqYlZn = false;}
      if(HLnEZEyTMN == true){HLnEZEyTMN = false;}
      if(LAfdIQIWKq == true){LAfdIQIWKq = false;}
      if(ybLZNDOZke == true){ybLZNDOZke = false;}
      if(ymuGyVONfK == true){ymuGyVONfK = false;}
      if(QYYNbqotYk == true){QYYNbqotYk = false;}
      if(hCaiofAOqV == true){hCaiofAOqV = false;}
      if(pYigOYFYfl == true){pYigOYFYfl = false;}
      if(BtpAaZCxxV == true){BtpAaZCxxV = false;}
      if(OUAzxwLLQS == true){OUAzxwLLQS = false;}
      if(VzVJUqpqzD == true){VzVJUqpqzD = false;}
      if(lPNlinLaIP == true){lPNlinLaIP = false;}
      if(cCRVGUYijS == true){cCRVGUYijS = false;}
      if(MsIMQCXgei == true){MsIMQCXgei = false;}
      if(jLysjzGNPI == true){jLysjzGNPI = false;}
      if(kkDApSgADz == true){kkDApSgADz = false;}
      if(SGHgqrHBVg == true){SGHgqrHBVg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFWLBXZTAJ
{ 
  void ICRDxNOdxn()
  { 
      bool sgikGjLmJA = false;
      bool LclqRldQwK = false;
      bool mztmeiRNfi = false;
      bool LoxpnaoFMw = false;
      bool oQlTfqrYUu = false;
      bool zjRoyslwFX = false;
      bool SyHanVewDq = false;
      bool wXDzVVMaGn = false;
      bool qssjjbXIqt = false;
      bool osAodqJLeK = false;
      bool LuVdzbgRTb = false;
      bool gKoRgZFXqM = false;
      bool yVEICCXNVd = false;
      bool MAuwbuXOjI = false;
      bool tFoPNdEhIE = false;
      bool llUSLoqMaw = false;
      bool DSuoOfOrpk = false;
      bool BpmhRrgntX = false;
      bool yoERraeckl = false;
      bool EKnnEaJzBg = false;
      string ZxoepUXNZp;
      string xsuLxWkHAr;
      string LRhDfPFMMb;
      string oriyhUbyDn;
      string CZFhOSiuYX;
      string kxjQLIPkzZ;
      string PLBxBFKxcb;
      string tlDMplMzoN;
      string fKmoqqIRlY;
      string EqzcYqXHfJ;
      string HkRxcytXaZ;
      string wPuksFXMGJ;
      string wsKEWDmZmy;
      string NETfGtrpLs;
      string xjpMcouNiT;
      string SLAWMOaNZY;
      string KTjbMqwOey;
      string MhANMLCyah;
      string HYpTfBDwTq;
      string TdQlhcANAk;
      if(ZxoepUXNZp == HkRxcytXaZ){sgikGjLmJA = true;}
      else if(HkRxcytXaZ == ZxoepUXNZp){LuVdzbgRTb = true;}
      if(xsuLxWkHAr == wPuksFXMGJ){LclqRldQwK = true;}
      else if(wPuksFXMGJ == xsuLxWkHAr){gKoRgZFXqM = true;}
      if(LRhDfPFMMb == wsKEWDmZmy){mztmeiRNfi = true;}
      else if(wsKEWDmZmy == LRhDfPFMMb){yVEICCXNVd = true;}
      if(oriyhUbyDn == NETfGtrpLs){LoxpnaoFMw = true;}
      else if(NETfGtrpLs == oriyhUbyDn){MAuwbuXOjI = true;}
      if(CZFhOSiuYX == xjpMcouNiT){oQlTfqrYUu = true;}
      else if(xjpMcouNiT == CZFhOSiuYX){tFoPNdEhIE = true;}
      if(kxjQLIPkzZ == SLAWMOaNZY){zjRoyslwFX = true;}
      else if(SLAWMOaNZY == kxjQLIPkzZ){llUSLoqMaw = true;}
      if(PLBxBFKxcb == KTjbMqwOey){SyHanVewDq = true;}
      else if(KTjbMqwOey == PLBxBFKxcb){DSuoOfOrpk = true;}
      if(tlDMplMzoN == MhANMLCyah){wXDzVVMaGn = true;}
      if(fKmoqqIRlY == HYpTfBDwTq){qssjjbXIqt = true;}
      if(EqzcYqXHfJ == TdQlhcANAk){osAodqJLeK = true;}
      while(MhANMLCyah == tlDMplMzoN){BpmhRrgntX = true;}
      while(HYpTfBDwTq == HYpTfBDwTq){yoERraeckl = true;}
      while(TdQlhcANAk == TdQlhcANAk){EKnnEaJzBg = true;}
      if(sgikGjLmJA == true){sgikGjLmJA = false;}
      if(LclqRldQwK == true){LclqRldQwK = false;}
      if(mztmeiRNfi == true){mztmeiRNfi = false;}
      if(LoxpnaoFMw == true){LoxpnaoFMw = false;}
      if(oQlTfqrYUu == true){oQlTfqrYUu = false;}
      if(zjRoyslwFX == true){zjRoyslwFX = false;}
      if(SyHanVewDq == true){SyHanVewDq = false;}
      if(wXDzVVMaGn == true){wXDzVVMaGn = false;}
      if(qssjjbXIqt == true){qssjjbXIqt = false;}
      if(osAodqJLeK == true){osAodqJLeK = false;}
      if(LuVdzbgRTb == true){LuVdzbgRTb = false;}
      if(gKoRgZFXqM == true){gKoRgZFXqM = false;}
      if(yVEICCXNVd == true){yVEICCXNVd = false;}
      if(MAuwbuXOjI == true){MAuwbuXOjI = false;}
      if(tFoPNdEhIE == true){tFoPNdEhIE = false;}
      if(llUSLoqMaw == true){llUSLoqMaw = false;}
      if(DSuoOfOrpk == true){DSuoOfOrpk = false;}
      if(BpmhRrgntX == true){BpmhRrgntX = false;}
      if(yoERraeckl == true){yoERraeckl = false;}
      if(EKnnEaJzBg == true){EKnnEaJzBg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UDHWAMWTGD
{ 
  void zchLHwhOGe()
  { 
      bool WNDKRRtzqe = false;
      bool XJBtDDPALQ = false;
      bool gVoTwrhNNC = false;
      bool GbNFrHWEtX = false;
      bool yYbkEInRQK = false;
      bool kGgtZAXjOY = false;
      bool jglnYwwuBw = false;
      bool gLFmSHtEPm = false;
      bool EQwCRztTfr = false;
      bool imoVnRmmMI = false;
      bool MrPUdZBsaR = false;
      bool FTTaTTjiVY = false;
      bool BcOJMtVjzA = false;
      bool UGrHaLAbYr = false;
      bool yArOlPSOBU = false;
      bool gDRnGjcFIi = false;
      bool DQtZwybMAH = false;
      bool SIKdZAjAXw = false;
      bool aHieTRoEAq = false;
      bool itSongGRSm = false;
      string RMrzqwySQp;
      string uBBKBFFMOc;
      string IOOpDzTdlw;
      string CSkGULiMgO;
      string xiRTEZWcYh;
      string xAYkFCxBur;
      string cUfTmcQupo;
      string VrezeYxtld;
      string bpEEyCtABR;
      string OhRolbDxgb;
      string IbmjLFUZFf;
      string FCPQPlPaVk;
      string hPsYamaoMD;
      string VANJUADUrs;
      string gTuULLSAZA;
      string McbusshNIX;
      string deMCKFoFwO;
      string hthbENUXMO;
      string UaPMpsXSPb;
      string SoLUOBHsKG;
      if(RMrzqwySQp == IbmjLFUZFf){WNDKRRtzqe = true;}
      else if(IbmjLFUZFf == RMrzqwySQp){MrPUdZBsaR = true;}
      if(uBBKBFFMOc == FCPQPlPaVk){XJBtDDPALQ = true;}
      else if(FCPQPlPaVk == uBBKBFFMOc){FTTaTTjiVY = true;}
      if(IOOpDzTdlw == hPsYamaoMD){gVoTwrhNNC = true;}
      else if(hPsYamaoMD == IOOpDzTdlw){BcOJMtVjzA = true;}
      if(CSkGULiMgO == VANJUADUrs){GbNFrHWEtX = true;}
      else if(VANJUADUrs == CSkGULiMgO){UGrHaLAbYr = true;}
      if(xiRTEZWcYh == gTuULLSAZA){yYbkEInRQK = true;}
      else if(gTuULLSAZA == xiRTEZWcYh){yArOlPSOBU = true;}
      if(xAYkFCxBur == McbusshNIX){kGgtZAXjOY = true;}
      else if(McbusshNIX == xAYkFCxBur){gDRnGjcFIi = true;}
      if(cUfTmcQupo == deMCKFoFwO){jglnYwwuBw = true;}
      else if(deMCKFoFwO == cUfTmcQupo){DQtZwybMAH = true;}
      if(VrezeYxtld == hthbENUXMO){gLFmSHtEPm = true;}
      if(bpEEyCtABR == UaPMpsXSPb){EQwCRztTfr = true;}
      if(OhRolbDxgb == SoLUOBHsKG){imoVnRmmMI = true;}
      while(hthbENUXMO == VrezeYxtld){SIKdZAjAXw = true;}
      while(UaPMpsXSPb == UaPMpsXSPb){aHieTRoEAq = true;}
      while(SoLUOBHsKG == SoLUOBHsKG){itSongGRSm = true;}
      if(WNDKRRtzqe == true){WNDKRRtzqe = false;}
      if(XJBtDDPALQ == true){XJBtDDPALQ = false;}
      if(gVoTwrhNNC == true){gVoTwrhNNC = false;}
      if(GbNFrHWEtX == true){GbNFrHWEtX = false;}
      if(yYbkEInRQK == true){yYbkEInRQK = false;}
      if(kGgtZAXjOY == true){kGgtZAXjOY = false;}
      if(jglnYwwuBw == true){jglnYwwuBw = false;}
      if(gLFmSHtEPm == true){gLFmSHtEPm = false;}
      if(EQwCRztTfr == true){EQwCRztTfr = false;}
      if(imoVnRmmMI == true){imoVnRmmMI = false;}
      if(MrPUdZBsaR == true){MrPUdZBsaR = false;}
      if(FTTaTTjiVY == true){FTTaTTjiVY = false;}
      if(BcOJMtVjzA == true){BcOJMtVjzA = false;}
      if(UGrHaLAbYr == true){UGrHaLAbYr = false;}
      if(yArOlPSOBU == true){yArOlPSOBU = false;}
      if(gDRnGjcFIi == true){gDRnGjcFIi = false;}
      if(DQtZwybMAH == true){DQtZwybMAH = false;}
      if(SIKdZAjAXw == true){SIKdZAjAXw = false;}
      if(aHieTRoEAq == true){aHieTRoEAq = false;}
      if(itSongGRSm == true){itSongGRSm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MAYTHZEWEQ
{ 
  void ClYCAZfaLA()
  { 
      bool gfXHaZMiTc = false;
      bool UlOXaONIdi = false;
      bool cLsDmLUfKT = false;
      bool znxqNnDUMI = false;
      bool lhqDuQJYFy = false;
      bool znnuSUmUUO = false;
      bool EgYAcfoXKl = false;
      bool LruVxtUpHV = false;
      bool CuZLULzBXr = false;
      bool BhAxDEJqZO = false;
      bool blOSmHrSyY = false;
      bool zwNyMJGMfR = false;
      bool gnzRkdqySr = false;
      bool jdQrtPfHYN = false;
      bool SfCzsEUBjs = false;
      bool xxLHhnlxhI = false;
      bool PtAFnVfUEw = false;
      bool dznSzAkAYf = false;
      bool IpNYtmSIKF = false;
      bool chYPxYfwLW = false;
      string VdzTVeGPnd;
      string cxbaOmfVAp;
      string kqsEIoSoct;
      string WByOoZdLmg;
      string qzfsnIRPGe;
      string eAOjsejtKf;
      string LQlsGayMln;
      string JUiTzkLzQA;
      string XChyPVmOVJ;
      string oiBHUZMllM;
      string KFdRVKRukH;
      string TkdJIJhndk;
      string njpczZSbyY;
      string YYMEpRYQbF;
      string DrdOpEFqyL;
      string qYHBXZOASu;
      string qpwLitXYSp;
      string jRLYguFblt;
      string UbcmhzRLfP;
      string DXxfNMwReu;
      if(VdzTVeGPnd == KFdRVKRukH){gfXHaZMiTc = true;}
      else if(KFdRVKRukH == VdzTVeGPnd){blOSmHrSyY = true;}
      if(cxbaOmfVAp == TkdJIJhndk){UlOXaONIdi = true;}
      else if(TkdJIJhndk == cxbaOmfVAp){zwNyMJGMfR = true;}
      if(kqsEIoSoct == njpczZSbyY){cLsDmLUfKT = true;}
      else if(njpczZSbyY == kqsEIoSoct){gnzRkdqySr = true;}
      if(WByOoZdLmg == YYMEpRYQbF){znxqNnDUMI = true;}
      else if(YYMEpRYQbF == WByOoZdLmg){jdQrtPfHYN = true;}
      if(qzfsnIRPGe == DrdOpEFqyL){lhqDuQJYFy = true;}
      else if(DrdOpEFqyL == qzfsnIRPGe){SfCzsEUBjs = true;}
      if(eAOjsejtKf == qYHBXZOASu){znnuSUmUUO = true;}
      else if(qYHBXZOASu == eAOjsejtKf){xxLHhnlxhI = true;}
      if(LQlsGayMln == qpwLitXYSp){EgYAcfoXKl = true;}
      else if(qpwLitXYSp == LQlsGayMln){PtAFnVfUEw = true;}
      if(JUiTzkLzQA == jRLYguFblt){LruVxtUpHV = true;}
      if(XChyPVmOVJ == UbcmhzRLfP){CuZLULzBXr = true;}
      if(oiBHUZMllM == DXxfNMwReu){BhAxDEJqZO = true;}
      while(jRLYguFblt == JUiTzkLzQA){dznSzAkAYf = true;}
      while(UbcmhzRLfP == UbcmhzRLfP){IpNYtmSIKF = true;}
      while(DXxfNMwReu == DXxfNMwReu){chYPxYfwLW = true;}
      if(gfXHaZMiTc == true){gfXHaZMiTc = false;}
      if(UlOXaONIdi == true){UlOXaONIdi = false;}
      if(cLsDmLUfKT == true){cLsDmLUfKT = false;}
      if(znxqNnDUMI == true){znxqNnDUMI = false;}
      if(lhqDuQJYFy == true){lhqDuQJYFy = false;}
      if(znnuSUmUUO == true){znnuSUmUUO = false;}
      if(EgYAcfoXKl == true){EgYAcfoXKl = false;}
      if(LruVxtUpHV == true){LruVxtUpHV = false;}
      if(CuZLULzBXr == true){CuZLULzBXr = false;}
      if(BhAxDEJqZO == true){BhAxDEJqZO = false;}
      if(blOSmHrSyY == true){blOSmHrSyY = false;}
      if(zwNyMJGMfR == true){zwNyMJGMfR = false;}
      if(gnzRkdqySr == true){gnzRkdqySr = false;}
      if(jdQrtPfHYN == true){jdQrtPfHYN = false;}
      if(SfCzsEUBjs == true){SfCzsEUBjs = false;}
      if(xxLHhnlxhI == true){xxLHhnlxhI = false;}
      if(PtAFnVfUEw == true){PtAFnVfUEw = false;}
      if(dznSzAkAYf == true){dznSzAkAYf = false;}
      if(IpNYtmSIKF == true){IpNYtmSIKF = false;}
      if(chYPxYfwLW == true){chYPxYfwLW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YZCKBMZXBI
{ 
  void ToqzqISxWX()
  { 
      bool KIfgTtEUPE = false;
      bool zsxdoZjGNR = false;
      bool HCwMHVJIcg = false;
      bool jsXcKNoRAU = false;
      bool FxNjtIRCYj = false;
      bool IUwopHMSYx = false;
      bool juriUFVTSa = false;
      bool kSFrLKoLSz = false;
      bool DHjsYOwilD = false;
      bool BVrCkJEePo = false;
      bool mxjxzpPEcf = false;
      bool SAAZtcLzJF = false;
      bool IlgOYOZCHB = false;
      bool GJwcLFXlsi = false;
      bool zrFGkAVSIH = false;
      bool yEVJfAQUXj = false;
      bool PMwaZIDWNn = false;
      bool EZFZGPfadY = false;
      bool sHtzDBnmxL = false;
      bool oCNJTlwegc = false;
      string GCujLyVaSf;
      string RIbZDDiqUa;
      string ZesYqMLHcP;
      string iDAQAzEiaQ;
      string TSDkrByyPa;
      string EmCjTbIVsz;
      string mNxDwOHLYD;
      string yzQDGGaIgp;
      string NNqBKwBQwY;
      string qhpbdGVAoc;
      string smYMcEWzcN;
      string AAnDkZVurz;
      string NqOzMQInYA;
      string kaSEwaneYF;
      string ZBmiXqsmpE;
      string kZHoPCYYzL;
      string whZcbZgjGJ;
      string kpVlZLDeaV;
      string WVyTPKSdns;
      string CPfNJrbKGy;
      if(GCujLyVaSf == smYMcEWzcN){KIfgTtEUPE = true;}
      else if(smYMcEWzcN == GCujLyVaSf){mxjxzpPEcf = true;}
      if(RIbZDDiqUa == AAnDkZVurz){zsxdoZjGNR = true;}
      else if(AAnDkZVurz == RIbZDDiqUa){SAAZtcLzJF = true;}
      if(ZesYqMLHcP == NqOzMQInYA){HCwMHVJIcg = true;}
      else if(NqOzMQInYA == ZesYqMLHcP){IlgOYOZCHB = true;}
      if(iDAQAzEiaQ == kaSEwaneYF){jsXcKNoRAU = true;}
      else if(kaSEwaneYF == iDAQAzEiaQ){GJwcLFXlsi = true;}
      if(TSDkrByyPa == ZBmiXqsmpE){FxNjtIRCYj = true;}
      else if(ZBmiXqsmpE == TSDkrByyPa){zrFGkAVSIH = true;}
      if(EmCjTbIVsz == kZHoPCYYzL){IUwopHMSYx = true;}
      else if(kZHoPCYYzL == EmCjTbIVsz){yEVJfAQUXj = true;}
      if(mNxDwOHLYD == whZcbZgjGJ){juriUFVTSa = true;}
      else if(whZcbZgjGJ == mNxDwOHLYD){PMwaZIDWNn = true;}
      if(yzQDGGaIgp == kpVlZLDeaV){kSFrLKoLSz = true;}
      if(NNqBKwBQwY == WVyTPKSdns){DHjsYOwilD = true;}
      if(qhpbdGVAoc == CPfNJrbKGy){BVrCkJEePo = true;}
      while(kpVlZLDeaV == yzQDGGaIgp){EZFZGPfadY = true;}
      while(WVyTPKSdns == WVyTPKSdns){sHtzDBnmxL = true;}
      while(CPfNJrbKGy == CPfNJrbKGy){oCNJTlwegc = true;}
      if(KIfgTtEUPE == true){KIfgTtEUPE = false;}
      if(zsxdoZjGNR == true){zsxdoZjGNR = false;}
      if(HCwMHVJIcg == true){HCwMHVJIcg = false;}
      if(jsXcKNoRAU == true){jsXcKNoRAU = false;}
      if(FxNjtIRCYj == true){FxNjtIRCYj = false;}
      if(IUwopHMSYx == true){IUwopHMSYx = false;}
      if(juriUFVTSa == true){juriUFVTSa = false;}
      if(kSFrLKoLSz == true){kSFrLKoLSz = false;}
      if(DHjsYOwilD == true){DHjsYOwilD = false;}
      if(BVrCkJEePo == true){BVrCkJEePo = false;}
      if(mxjxzpPEcf == true){mxjxzpPEcf = false;}
      if(SAAZtcLzJF == true){SAAZtcLzJF = false;}
      if(IlgOYOZCHB == true){IlgOYOZCHB = false;}
      if(GJwcLFXlsi == true){GJwcLFXlsi = false;}
      if(zrFGkAVSIH == true){zrFGkAVSIH = false;}
      if(yEVJfAQUXj == true){yEVJfAQUXj = false;}
      if(PMwaZIDWNn == true){PMwaZIDWNn = false;}
      if(EZFZGPfadY == true){EZFZGPfadY = false;}
      if(sHtzDBnmxL == true){sHtzDBnmxL = false;}
      if(oCNJTlwegc == true){oCNJTlwegc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JACKBQEKHR
{ 
  void eCRRghkHfj()
  { 
      bool dxAHRYGLtw = false;
      bool PbrORXdojq = false;
      bool TNRELIEnXl = false;
      bool DODuEPVwsB = false;
      bool HSFzzdRpjE = false;
      bool npWePQfuuJ = false;
      bool USmHrBYwKC = false;
      bool CgwiiAIRFh = false;
      bool qODSyMrXen = false;
      bool jZAifofxGx = false;
      bool EUehCGtmuO = false;
      bool INpMSGOTJe = false;
      bool JARWSbfMCt = false;
      bool UKKHdViVQq = false;
      bool SEbQfVjnQZ = false;
      bool ZLmanDDIOZ = false;
      bool ZgjAsxChiw = false;
      bool WsDRMEYAqw = false;
      bool rrucUJXjTZ = false;
      bool SZHqQkTaWh = false;
      string LnWOCDUPHS;
      string whpcCdMTbn;
      string NtXLVOngGZ;
      string CCJspVIgoy;
      string ieRToxBWFW;
      string QpZXzRQKsn;
      string OnIgQsYwlf;
      string UeedEhbDWY;
      string NQbjILcksY;
      string FynAiuVjDu;
      string XEjYCkLwTR;
      string pMnTayMYXE;
      string PmCNaWpduI;
      string LqzaAIfChX;
      string zgRbirJTZj;
      string ixMzfkCWxe;
      string thAKFzNMTR;
      string RJqAEiUZei;
      string MWEKZOeAuO;
      string FJECcRfGWj;
      if(LnWOCDUPHS == XEjYCkLwTR){dxAHRYGLtw = true;}
      else if(XEjYCkLwTR == LnWOCDUPHS){EUehCGtmuO = true;}
      if(whpcCdMTbn == pMnTayMYXE){PbrORXdojq = true;}
      else if(pMnTayMYXE == whpcCdMTbn){INpMSGOTJe = true;}
      if(NtXLVOngGZ == PmCNaWpduI){TNRELIEnXl = true;}
      else if(PmCNaWpduI == NtXLVOngGZ){JARWSbfMCt = true;}
      if(CCJspVIgoy == LqzaAIfChX){DODuEPVwsB = true;}
      else if(LqzaAIfChX == CCJspVIgoy){UKKHdViVQq = true;}
      if(ieRToxBWFW == zgRbirJTZj){HSFzzdRpjE = true;}
      else if(zgRbirJTZj == ieRToxBWFW){SEbQfVjnQZ = true;}
      if(QpZXzRQKsn == ixMzfkCWxe){npWePQfuuJ = true;}
      else if(ixMzfkCWxe == QpZXzRQKsn){ZLmanDDIOZ = true;}
      if(OnIgQsYwlf == thAKFzNMTR){USmHrBYwKC = true;}
      else if(thAKFzNMTR == OnIgQsYwlf){ZgjAsxChiw = true;}
      if(UeedEhbDWY == RJqAEiUZei){CgwiiAIRFh = true;}
      if(NQbjILcksY == MWEKZOeAuO){qODSyMrXen = true;}
      if(FynAiuVjDu == FJECcRfGWj){jZAifofxGx = true;}
      while(RJqAEiUZei == UeedEhbDWY){WsDRMEYAqw = true;}
      while(MWEKZOeAuO == MWEKZOeAuO){rrucUJXjTZ = true;}
      while(FJECcRfGWj == FJECcRfGWj){SZHqQkTaWh = true;}
      if(dxAHRYGLtw == true){dxAHRYGLtw = false;}
      if(PbrORXdojq == true){PbrORXdojq = false;}
      if(TNRELIEnXl == true){TNRELIEnXl = false;}
      if(DODuEPVwsB == true){DODuEPVwsB = false;}
      if(HSFzzdRpjE == true){HSFzzdRpjE = false;}
      if(npWePQfuuJ == true){npWePQfuuJ = false;}
      if(USmHrBYwKC == true){USmHrBYwKC = false;}
      if(CgwiiAIRFh == true){CgwiiAIRFh = false;}
      if(qODSyMrXen == true){qODSyMrXen = false;}
      if(jZAifofxGx == true){jZAifofxGx = false;}
      if(EUehCGtmuO == true){EUehCGtmuO = false;}
      if(INpMSGOTJe == true){INpMSGOTJe = false;}
      if(JARWSbfMCt == true){JARWSbfMCt = false;}
      if(UKKHdViVQq == true){UKKHdViVQq = false;}
      if(SEbQfVjnQZ == true){SEbQfVjnQZ = false;}
      if(ZLmanDDIOZ == true){ZLmanDDIOZ = false;}
      if(ZgjAsxChiw == true){ZgjAsxChiw = false;}
      if(WsDRMEYAqw == true){WsDRMEYAqw = false;}
      if(rrucUJXjTZ == true){rrucUJXjTZ = false;}
      if(SZHqQkTaWh == true){SZHqQkTaWh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BUJAJYZDGH
{ 
  void OJKGSJKDcm()
  { 
      bool cYEnMWGsFJ = false;
      bool FDhQPDjXZD = false;
      bool QXtQTPeLPM = false;
      bool mJMVCleuHf = false;
      bool jWSzEqrJDn = false;
      bool oAsCnEenTx = false;
      bool rudrVuqLOc = false;
      bool XnPsSsFtLb = false;
      bool WUIaWmPKgx = false;
      bool HqaKmosZdJ = false;
      bool AfuZQAkzit = false;
      bool zjbrZWlCUi = false;
      bool efeQVfNFGd = false;
      bool zeQCbpZhKW = false;
      bool BPbmxWOijQ = false;
      bool CqEtdTBdEj = false;
      bool mesEuTTYPj = false;
      bool wEqygOEqSy = false;
      bool QdUobIaVYH = false;
      bool nwcZiWWWqd = false;
      string XozzTFHDWQ;
      string BcVuVZcyDo;
      string eQqkigbJWB;
      string jszgthZOYF;
      string DqKEHjaWmO;
      string RhNtKGxNQm;
      string dygVgIdnAm;
      string ANZykmGldy;
      string FEVIiBfEWm;
      string jLylaFKnWy;
      string GmVzODHOIW;
      string ALiShYbYmf;
      string cYRNDnPnWf;
      string cSPeqRiVse;
      string sQuzmYcfEC;
      string clBqVhVIua;
      string mTrcthwDaP;
      string pFeHlLcRae;
      string LjjTDqQXJJ;
      string uZaSqZYSFE;
      if(XozzTFHDWQ == GmVzODHOIW){cYEnMWGsFJ = true;}
      else if(GmVzODHOIW == XozzTFHDWQ){AfuZQAkzit = true;}
      if(BcVuVZcyDo == ALiShYbYmf){FDhQPDjXZD = true;}
      else if(ALiShYbYmf == BcVuVZcyDo){zjbrZWlCUi = true;}
      if(eQqkigbJWB == cYRNDnPnWf){QXtQTPeLPM = true;}
      else if(cYRNDnPnWf == eQqkigbJWB){efeQVfNFGd = true;}
      if(jszgthZOYF == cSPeqRiVse){mJMVCleuHf = true;}
      else if(cSPeqRiVse == jszgthZOYF){zeQCbpZhKW = true;}
      if(DqKEHjaWmO == sQuzmYcfEC){jWSzEqrJDn = true;}
      else if(sQuzmYcfEC == DqKEHjaWmO){BPbmxWOijQ = true;}
      if(RhNtKGxNQm == clBqVhVIua){oAsCnEenTx = true;}
      else if(clBqVhVIua == RhNtKGxNQm){CqEtdTBdEj = true;}
      if(dygVgIdnAm == mTrcthwDaP){rudrVuqLOc = true;}
      else if(mTrcthwDaP == dygVgIdnAm){mesEuTTYPj = true;}
      if(ANZykmGldy == pFeHlLcRae){XnPsSsFtLb = true;}
      if(FEVIiBfEWm == LjjTDqQXJJ){WUIaWmPKgx = true;}
      if(jLylaFKnWy == uZaSqZYSFE){HqaKmosZdJ = true;}
      while(pFeHlLcRae == ANZykmGldy){wEqygOEqSy = true;}
      while(LjjTDqQXJJ == LjjTDqQXJJ){QdUobIaVYH = true;}
      while(uZaSqZYSFE == uZaSqZYSFE){nwcZiWWWqd = true;}
      if(cYEnMWGsFJ == true){cYEnMWGsFJ = false;}
      if(FDhQPDjXZD == true){FDhQPDjXZD = false;}
      if(QXtQTPeLPM == true){QXtQTPeLPM = false;}
      if(mJMVCleuHf == true){mJMVCleuHf = false;}
      if(jWSzEqrJDn == true){jWSzEqrJDn = false;}
      if(oAsCnEenTx == true){oAsCnEenTx = false;}
      if(rudrVuqLOc == true){rudrVuqLOc = false;}
      if(XnPsSsFtLb == true){XnPsSsFtLb = false;}
      if(WUIaWmPKgx == true){WUIaWmPKgx = false;}
      if(HqaKmosZdJ == true){HqaKmosZdJ = false;}
      if(AfuZQAkzit == true){AfuZQAkzit = false;}
      if(zjbrZWlCUi == true){zjbrZWlCUi = false;}
      if(efeQVfNFGd == true){efeQVfNFGd = false;}
      if(zeQCbpZhKW == true){zeQCbpZhKW = false;}
      if(BPbmxWOijQ == true){BPbmxWOijQ = false;}
      if(CqEtdTBdEj == true){CqEtdTBdEj = false;}
      if(mesEuTTYPj == true){mesEuTTYPj = false;}
      if(wEqygOEqSy == true){wEqygOEqSy = false;}
      if(QdUobIaVYH == true){QdUobIaVYH = false;}
      if(nwcZiWWWqd == true){nwcZiWWWqd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BJYOXZYMYM
{ 
  void sOZYtkOYAT()
  { 
      bool ZuhwLjYpRM = false;
      bool dAMBZoYFNj = false;
      bool QrYXqYAxGV = false;
      bool WEgAXRTSZQ = false;
      bool YezCqYFZLF = false;
      bool BIahXgVJFl = false;
      bool ibiuoZTMcH = false;
      bool UFewLlrVgR = false;
      bool TakBUOdzbq = false;
      bool uJNngxuDNR = false;
      bool FswDjwcdVl = false;
      bool nAcnSIphaa = false;
      bool wUjlMLrqPO = false;
      bool poIOLZegQX = false;
      bool lzcpCtgYUY = false;
      bool GNclVkIJqY = false;
      bool DkOHwzrNbr = false;
      bool cIQDowrtiR = false;
      bool dSWpHbMVsa = false;
      bool RUprTAkUtD = false;
      string PTSqfsKkVZ;
      string FDiMdSBFUE;
      string xWXRwOuyWY;
      string gbfuUVlIWN;
      string bccRQnnIoP;
      string PAnDHswBtR;
      string yLOxrdWnqH;
      string gshGbTsFAI;
      string ZlIHIgmcna;
      string ZjNEPPOfZm;
      string QARgiWRham;
      string ApBlqLDHnL;
      string ptzPhwedpM;
      string FNfMrZTaXl;
      string OFBAajibND;
      string LHrOxVABzl;
      string qnqNhlJntQ;
      string rbiBwjrzoy;
      string MCPlAxVRPV;
      string ZSaktZNnSn;
      if(PTSqfsKkVZ == QARgiWRham){ZuhwLjYpRM = true;}
      else if(QARgiWRham == PTSqfsKkVZ){FswDjwcdVl = true;}
      if(FDiMdSBFUE == ApBlqLDHnL){dAMBZoYFNj = true;}
      else if(ApBlqLDHnL == FDiMdSBFUE){nAcnSIphaa = true;}
      if(xWXRwOuyWY == ptzPhwedpM){QrYXqYAxGV = true;}
      else if(ptzPhwedpM == xWXRwOuyWY){wUjlMLrqPO = true;}
      if(gbfuUVlIWN == FNfMrZTaXl){WEgAXRTSZQ = true;}
      else if(FNfMrZTaXl == gbfuUVlIWN){poIOLZegQX = true;}
      if(bccRQnnIoP == OFBAajibND){YezCqYFZLF = true;}
      else if(OFBAajibND == bccRQnnIoP){lzcpCtgYUY = true;}
      if(PAnDHswBtR == LHrOxVABzl){BIahXgVJFl = true;}
      else if(LHrOxVABzl == PAnDHswBtR){GNclVkIJqY = true;}
      if(yLOxrdWnqH == qnqNhlJntQ){ibiuoZTMcH = true;}
      else if(qnqNhlJntQ == yLOxrdWnqH){DkOHwzrNbr = true;}
      if(gshGbTsFAI == rbiBwjrzoy){UFewLlrVgR = true;}
      if(ZlIHIgmcna == MCPlAxVRPV){TakBUOdzbq = true;}
      if(ZjNEPPOfZm == ZSaktZNnSn){uJNngxuDNR = true;}
      while(rbiBwjrzoy == gshGbTsFAI){cIQDowrtiR = true;}
      while(MCPlAxVRPV == MCPlAxVRPV){dSWpHbMVsa = true;}
      while(ZSaktZNnSn == ZSaktZNnSn){RUprTAkUtD = true;}
      if(ZuhwLjYpRM == true){ZuhwLjYpRM = false;}
      if(dAMBZoYFNj == true){dAMBZoYFNj = false;}
      if(QrYXqYAxGV == true){QrYXqYAxGV = false;}
      if(WEgAXRTSZQ == true){WEgAXRTSZQ = false;}
      if(YezCqYFZLF == true){YezCqYFZLF = false;}
      if(BIahXgVJFl == true){BIahXgVJFl = false;}
      if(ibiuoZTMcH == true){ibiuoZTMcH = false;}
      if(UFewLlrVgR == true){UFewLlrVgR = false;}
      if(TakBUOdzbq == true){TakBUOdzbq = false;}
      if(uJNngxuDNR == true){uJNngxuDNR = false;}
      if(FswDjwcdVl == true){FswDjwcdVl = false;}
      if(nAcnSIphaa == true){nAcnSIphaa = false;}
      if(wUjlMLrqPO == true){wUjlMLrqPO = false;}
      if(poIOLZegQX == true){poIOLZegQX = false;}
      if(lzcpCtgYUY == true){lzcpCtgYUY = false;}
      if(GNclVkIJqY == true){GNclVkIJqY = false;}
      if(DkOHwzrNbr == true){DkOHwzrNbr = false;}
      if(cIQDowrtiR == true){cIQDowrtiR = false;}
      if(dSWpHbMVsa == true){dSWpHbMVsa = false;}
      if(RUprTAkUtD == true){RUprTAkUtD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CCEWGHPEUI
{ 
  void kpXjoqEMZD()
  { 
      bool KtAieLQEsi = false;
      bool BJIMwiFBlb = false;
      bool oJsOmpodYl = false;
      bool hJJHGtEuEB = false;
      bool PZZRfQElha = false;
      bool qGASyAAlun = false;
      bool VleGAqzBFC = false;
      bool dJxkMPjbhW = false;
      bool lCwxubIqIG = false;
      bool tSAPectSRn = false;
      bool QCgfxhIPFi = false;
      bool PYDYCTohLX = false;
      bool hIszILIhGi = false;
      bool VQJsFiVQAN = false;
      bool TslYpUOaMK = false;
      bool mLHsGIJgXk = false;
      bool YZIVNzOKSS = false;
      bool yYgyEoWTJm = false;
      bool whUwuJIPmx = false;
      bool ZnrOnskPLq = false;
      string zubOMWjpTi;
      string yOHMozjjSQ;
      string NbjXZBcJiz;
      string cThjQXMLJx;
      string oHoxnMrDzC;
      string MkXlTXKDnL;
      string tZGTGefWwR;
      string mXZUaGlliM;
      string JYKgmquwQr;
      string MIWyDPAUqJ;
      string gUHhPnKCKN;
      string kYUaBUPZgO;
      string jiGDEdAaRL;
      string FRuZfnRbQy;
      string fslCHnnuwh;
      string zZmbZyNEcl;
      string njkyHTctuN;
      string DnJiipxEuQ;
      string oEeiMfdSAg;
      string ZMyeKwHmtn;
      if(zubOMWjpTi == gUHhPnKCKN){KtAieLQEsi = true;}
      else if(gUHhPnKCKN == zubOMWjpTi){QCgfxhIPFi = true;}
      if(yOHMozjjSQ == kYUaBUPZgO){BJIMwiFBlb = true;}
      else if(kYUaBUPZgO == yOHMozjjSQ){PYDYCTohLX = true;}
      if(NbjXZBcJiz == jiGDEdAaRL){oJsOmpodYl = true;}
      else if(jiGDEdAaRL == NbjXZBcJiz){hIszILIhGi = true;}
      if(cThjQXMLJx == FRuZfnRbQy){hJJHGtEuEB = true;}
      else if(FRuZfnRbQy == cThjQXMLJx){VQJsFiVQAN = true;}
      if(oHoxnMrDzC == fslCHnnuwh){PZZRfQElha = true;}
      else if(fslCHnnuwh == oHoxnMrDzC){TslYpUOaMK = true;}
      if(MkXlTXKDnL == zZmbZyNEcl){qGASyAAlun = true;}
      else if(zZmbZyNEcl == MkXlTXKDnL){mLHsGIJgXk = true;}
      if(tZGTGefWwR == njkyHTctuN){VleGAqzBFC = true;}
      else if(njkyHTctuN == tZGTGefWwR){YZIVNzOKSS = true;}
      if(mXZUaGlliM == DnJiipxEuQ){dJxkMPjbhW = true;}
      if(JYKgmquwQr == oEeiMfdSAg){lCwxubIqIG = true;}
      if(MIWyDPAUqJ == ZMyeKwHmtn){tSAPectSRn = true;}
      while(DnJiipxEuQ == mXZUaGlliM){yYgyEoWTJm = true;}
      while(oEeiMfdSAg == oEeiMfdSAg){whUwuJIPmx = true;}
      while(ZMyeKwHmtn == ZMyeKwHmtn){ZnrOnskPLq = true;}
      if(KtAieLQEsi == true){KtAieLQEsi = false;}
      if(BJIMwiFBlb == true){BJIMwiFBlb = false;}
      if(oJsOmpodYl == true){oJsOmpodYl = false;}
      if(hJJHGtEuEB == true){hJJHGtEuEB = false;}
      if(PZZRfQElha == true){PZZRfQElha = false;}
      if(qGASyAAlun == true){qGASyAAlun = false;}
      if(VleGAqzBFC == true){VleGAqzBFC = false;}
      if(dJxkMPjbhW == true){dJxkMPjbhW = false;}
      if(lCwxubIqIG == true){lCwxubIqIG = false;}
      if(tSAPectSRn == true){tSAPectSRn = false;}
      if(QCgfxhIPFi == true){QCgfxhIPFi = false;}
      if(PYDYCTohLX == true){PYDYCTohLX = false;}
      if(hIszILIhGi == true){hIszILIhGi = false;}
      if(VQJsFiVQAN == true){VQJsFiVQAN = false;}
      if(TslYpUOaMK == true){TslYpUOaMK = false;}
      if(mLHsGIJgXk == true){mLHsGIJgXk = false;}
      if(YZIVNzOKSS == true){YZIVNzOKSS = false;}
      if(yYgyEoWTJm == true){yYgyEoWTJm = false;}
      if(whUwuJIPmx == true){whUwuJIPmx = false;}
      if(ZnrOnskPLq == true){ZnrOnskPLq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JITRNSADCE
{ 
  void WQQjbDcKMw()
  { 
      bool pDFrpStAWa = false;
      bool MmrnfZnynk = false;
      bool zMXTRTDnKE = false;
      bool kKepBmoGqM = false;
      bool frNjrOmiji = false;
      bool ZfwCYcflZW = false;
      bool PFpRpCIBls = false;
      bool jgHbFGynaD = false;
      bool fTEadFObRY = false;
      bool HCgUwZCwsp = false;
      bool FkxqysXUxS = false;
      bool drKVpwBOmk = false;
      bool nfjNkgAmee = false;
      bool ECtkytWMck = false;
      bool gsdytPrKdA = false;
      bool YmIICYBjGQ = false;
      bool skoSNaxZXu = false;
      bool ZolCDtCkSV = false;
      bool ooIeFRtlhY = false;
      bool slGLruELkS = false;
      string ANRjQgzbiO;
      string pjwMBYVteG;
      string yPJPaJUKrN;
      string wGlrINYbuk;
      string LdkbzFcsxC;
      string oxuoGjEBIH;
      string LojUSjxEEm;
      string AsytuTdhQV;
      string faMpYzKxkX;
      string IWSmYVtQIP;
      string HYnJBuyBsl;
      string GVjmakctwT;
      string YzSgddaKVY;
      string ZNYBNHlCnc;
      string BJEzRmleLn;
      string szTopHFHeX;
      string UmfTLrxiZT;
      string yZFSSOuSPq;
      string quzgfZsjKF;
      string BeWQINdjnY;
      if(ANRjQgzbiO == HYnJBuyBsl){pDFrpStAWa = true;}
      else if(HYnJBuyBsl == ANRjQgzbiO){FkxqysXUxS = true;}
      if(pjwMBYVteG == GVjmakctwT){MmrnfZnynk = true;}
      else if(GVjmakctwT == pjwMBYVteG){drKVpwBOmk = true;}
      if(yPJPaJUKrN == YzSgddaKVY){zMXTRTDnKE = true;}
      else if(YzSgddaKVY == yPJPaJUKrN){nfjNkgAmee = true;}
      if(wGlrINYbuk == ZNYBNHlCnc){kKepBmoGqM = true;}
      else if(ZNYBNHlCnc == wGlrINYbuk){ECtkytWMck = true;}
      if(LdkbzFcsxC == BJEzRmleLn){frNjrOmiji = true;}
      else if(BJEzRmleLn == LdkbzFcsxC){gsdytPrKdA = true;}
      if(oxuoGjEBIH == szTopHFHeX){ZfwCYcflZW = true;}
      else if(szTopHFHeX == oxuoGjEBIH){YmIICYBjGQ = true;}
      if(LojUSjxEEm == UmfTLrxiZT){PFpRpCIBls = true;}
      else if(UmfTLrxiZT == LojUSjxEEm){skoSNaxZXu = true;}
      if(AsytuTdhQV == yZFSSOuSPq){jgHbFGynaD = true;}
      if(faMpYzKxkX == quzgfZsjKF){fTEadFObRY = true;}
      if(IWSmYVtQIP == BeWQINdjnY){HCgUwZCwsp = true;}
      while(yZFSSOuSPq == AsytuTdhQV){ZolCDtCkSV = true;}
      while(quzgfZsjKF == quzgfZsjKF){ooIeFRtlhY = true;}
      while(BeWQINdjnY == BeWQINdjnY){slGLruELkS = true;}
      if(pDFrpStAWa == true){pDFrpStAWa = false;}
      if(MmrnfZnynk == true){MmrnfZnynk = false;}
      if(zMXTRTDnKE == true){zMXTRTDnKE = false;}
      if(kKepBmoGqM == true){kKepBmoGqM = false;}
      if(frNjrOmiji == true){frNjrOmiji = false;}
      if(ZfwCYcflZW == true){ZfwCYcflZW = false;}
      if(PFpRpCIBls == true){PFpRpCIBls = false;}
      if(jgHbFGynaD == true){jgHbFGynaD = false;}
      if(fTEadFObRY == true){fTEadFObRY = false;}
      if(HCgUwZCwsp == true){HCgUwZCwsp = false;}
      if(FkxqysXUxS == true){FkxqysXUxS = false;}
      if(drKVpwBOmk == true){drKVpwBOmk = false;}
      if(nfjNkgAmee == true){nfjNkgAmee = false;}
      if(ECtkytWMck == true){ECtkytWMck = false;}
      if(gsdytPrKdA == true){gsdytPrKdA = false;}
      if(YmIICYBjGQ == true){YmIICYBjGQ = false;}
      if(skoSNaxZXu == true){skoSNaxZXu = false;}
      if(ZolCDtCkSV == true){ZolCDtCkSV = false;}
      if(ooIeFRtlhY == true){ooIeFRtlhY = false;}
      if(slGLruELkS == true){slGLruELkS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BXVIIXKSBX
{ 
  void YlmHwfesTS()
  { 
      bool JcTNabFxnP = false;
      bool FNDWVzsbVa = false;
      bool FbfgQLJThl = false;
      bool pHGEsSUMyA = false;
      bool BTsXoIFjoh = false;
      bool YYxCehxlxP = false;
      bool RkPBZyGycC = false;
      bool egdUYliHrH = false;
      bool GZezNRJEYL = false;
      bool VhOihPEqxp = false;
      bool BGGmCqubcs = false;
      bool yotoIrGPnI = false;
      bool nCZQfxStlJ = false;
      bool gqKBFASrwV = false;
      bool VhbfMgmZZp = false;
      bool JnDoBzfpGF = false;
      bool YAoTLHeriI = false;
      bool YOSRlGatDz = false;
      bool JsUwzsnVAG = false;
      bool TckqxVrHTF = false;
      string lPZzNQOqnu;
      string GlVxOVlVZR;
      string OIWQxoxryG;
      string TlKonsTAil;
      string KhfMUzZCQM;
      string KiLZFdrJBX;
      string SWrhbTbfJV;
      string CkmnHfbKuy;
      string PualwjZjjK;
      string AJzKSmpykA;
      string XtsuJZwXSY;
      string BhNCIWuGkr;
      string squzVrkbVT;
      string pdZtaUCfbV;
      string mCRLIRwwBu;
      string qiMrGfytZR;
      string nTByhWISbm;
      string UPdPEqZjpD;
      string woZZbGRgmt;
      string WIGKhSASck;
      if(lPZzNQOqnu == XtsuJZwXSY){JcTNabFxnP = true;}
      else if(XtsuJZwXSY == lPZzNQOqnu){BGGmCqubcs = true;}
      if(GlVxOVlVZR == BhNCIWuGkr){FNDWVzsbVa = true;}
      else if(BhNCIWuGkr == GlVxOVlVZR){yotoIrGPnI = true;}
      if(OIWQxoxryG == squzVrkbVT){FbfgQLJThl = true;}
      else if(squzVrkbVT == OIWQxoxryG){nCZQfxStlJ = true;}
      if(TlKonsTAil == pdZtaUCfbV){pHGEsSUMyA = true;}
      else if(pdZtaUCfbV == TlKonsTAil){gqKBFASrwV = true;}
      if(KhfMUzZCQM == mCRLIRwwBu){BTsXoIFjoh = true;}
      else if(mCRLIRwwBu == KhfMUzZCQM){VhbfMgmZZp = true;}
      if(KiLZFdrJBX == qiMrGfytZR){YYxCehxlxP = true;}
      else if(qiMrGfytZR == KiLZFdrJBX){JnDoBzfpGF = true;}
      if(SWrhbTbfJV == nTByhWISbm){RkPBZyGycC = true;}
      else if(nTByhWISbm == SWrhbTbfJV){YAoTLHeriI = true;}
      if(CkmnHfbKuy == UPdPEqZjpD){egdUYliHrH = true;}
      if(PualwjZjjK == woZZbGRgmt){GZezNRJEYL = true;}
      if(AJzKSmpykA == WIGKhSASck){VhOihPEqxp = true;}
      while(UPdPEqZjpD == CkmnHfbKuy){YOSRlGatDz = true;}
      while(woZZbGRgmt == woZZbGRgmt){JsUwzsnVAG = true;}
      while(WIGKhSASck == WIGKhSASck){TckqxVrHTF = true;}
      if(JcTNabFxnP == true){JcTNabFxnP = false;}
      if(FNDWVzsbVa == true){FNDWVzsbVa = false;}
      if(FbfgQLJThl == true){FbfgQLJThl = false;}
      if(pHGEsSUMyA == true){pHGEsSUMyA = false;}
      if(BTsXoIFjoh == true){BTsXoIFjoh = false;}
      if(YYxCehxlxP == true){YYxCehxlxP = false;}
      if(RkPBZyGycC == true){RkPBZyGycC = false;}
      if(egdUYliHrH == true){egdUYliHrH = false;}
      if(GZezNRJEYL == true){GZezNRJEYL = false;}
      if(VhOihPEqxp == true){VhOihPEqxp = false;}
      if(BGGmCqubcs == true){BGGmCqubcs = false;}
      if(yotoIrGPnI == true){yotoIrGPnI = false;}
      if(nCZQfxStlJ == true){nCZQfxStlJ = false;}
      if(gqKBFASrwV == true){gqKBFASrwV = false;}
      if(VhbfMgmZZp == true){VhbfMgmZZp = false;}
      if(JnDoBzfpGF == true){JnDoBzfpGF = false;}
      if(YAoTLHeriI == true){YAoTLHeriI = false;}
      if(YOSRlGatDz == true){YOSRlGatDz = false;}
      if(JsUwzsnVAG == true){JsUwzsnVAG = false;}
      if(TckqxVrHTF == true){TckqxVrHTF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MQSNMPXEAN
{ 
  void WTMIbNXqeH()
  { 
      bool JshZiVCild = false;
      bool dNHizQyyCt = false;
      bool ogutnwcrZi = false;
      bool XIRBDwJLIp = false;
      bool BOFFpseagT = false;
      bool uyXhSbxnll = false;
      bool rJICGUuGfD = false;
      bool GmoLsabpDt = false;
      bool RCLGnYkjia = false;
      bool yVYVyqGDzV = false;
      bool yYucMHILnr = false;
      bool AHkrUpxCNg = false;
      bool jLWEFkNTNB = false;
      bool TXphwsHhsf = false;
      bool PYupapkgBH = false;
      bool sDoRklBpXb = false;
      bool toxmXbQDua = false;
      bool iOIgRLPgdO = false;
      bool zfRGHQhYwJ = false;
      bool rQKRlZaISy = false;
      string tcBItkopRa;
      string EdxSbnkafV;
      string kdWxwpYxYW;
      string AFhboToDlQ;
      string wlquHfxzzB;
      string efQJZPGDLE;
      string LrRuayuVcH;
      string zgoOZylapQ;
      string rZxXqUoXBY;
      string NkrhEEUwUI;
      string jbVqCyqBjb;
      string ceMuLltsDG;
      string JWTEtNoHKV;
      string dpGhgPDGUs;
      string cnnZuhXwVR;
      string JarOyMIQwo;
      string IjqOxmYeOu;
      string inYJcUitJM;
      string orkrLDxqiT;
      string HlKfjsxZbH;
      if(tcBItkopRa == jbVqCyqBjb){JshZiVCild = true;}
      else if(jbVqCyqBjb == tcBItkopRa){yYucMHILnr = true;}
      if(EdxSbnkafV == ceMuLltsDG){dNHizQyyCt = true;}
      else if(ceMuLltsDG == EdxSbnkafV){AHkrUpxCNg = true;}
      if(kdWxwpYxYW == JWTEtNoHKV){ogutnwcrZi = true;}
      else if(JWTEtNoHKV == kdWxwpYxYW){jLWEFkNTNB = true;}
      if(AFhboToDlQ == dpGhgPDGUs){XIRBDwJLIp = true;}
      else if(dpGhgPDGUs == AFhboToDlQ){TXphwsHhsf = true;}
      if(wlquHfxzzB == cnnZuhXwVR){BOFFpseagT = true;}
      else if(cnnZuhXwVR == wlquHfxzzB){PYupapkgBH = true;}
      if(efQJZPGDLE == JarOyMIQwo){uyXhSbxnll = true;}
      else if(JarOyMIQwo == efQJZPGDLE){sDoRklBpXb = true;}
      if(LrRuayuVcH == IjqOxmYeOu){rJICGUuGfD = true;}
      else if(IjqOxmYeOu == LrRuayuVcH){toxmXbQDua = true;}
      if(zgoOZylapQ == inYJcUitJM){GmoLsabpDt = true;}
      if(rZxXqUoXBY == orkrLDxqiT){RCLGnYkjia = true;}
      if(NkrhEEUwUI == HlKfjsxZbH){yVYVyqGDzV = true;}
      while(inYJcUitJM == zgoOZylapQ){iOIgRLPgdO = true;}
      while(orkrLDxqiT == orkrLDxqiT){zfRGHQhYwJ = true;}
      while(HlKfjsxZbH == HlKfjsxZbH){rQKRlZaISy = true;}
      if(JshZiVCild == true){JshZiVCild = false;}
      if(dNHizQyyCt == true){dNHizQyyCt = false;}
      if(ogutnwcrZi == true){ogutnwcrZi = false;}
      if(XIRBDwJLIp == true){XIRBDwJLIp = false;}
      if(BOFFpseagT == true){BOFFpseagT = false;}
      if(uyXhSbxnll == true){uyXhSbxnll = false;}
      if(rJICGUuGfD == true){rJICGUuGfD = false;}
      if(GmoLsabpDt == true){GmoLsabpDt = false;}
      if(RCLGnYkjia == true){RCLGnYkjia = false;}
      if(yVYVyqGDzV == true){yVYVyqGDzV = false;}
      if(yYucMHILnr == true){yYucMHILnr = false;}
      if(AHkrUpxCNg == true){AHkrUpxCNg = false;}
      if(jLWEFkNTNB == true){jLWEFkNTNB = false;}
      if(TXphwsHhsf == true){TXphwsHhsf = false;}
      if(PYupapkgBH == true){PYupapkgBH = false;}
      if(sDoRklBpXb == true){sDoRklBpXb = false;}
      if(toxmXbQDua == true){toxmXbQDua = false;}
      if(iOIgRLPgdO == true){iOIgRLPgdO = false;}
      if(zfRGHQhYwJ == true){zfRGHQhYwJ = false;}
      if(rQKRlZaISy == true){rQKRlZaISy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QHLHUQHAXV
{ 
  void hmiphjMLrI()
  { 
      bool SlXjfitmBs = false;
      bool sAxkwquKzH = false;
      bool FCCzsetKcn = false;
      bool IyVUZWqdjc = false;
      bool XAfUmXidyj = false;
      bool srizTPiXqB = false;
      bool njJMjtdcKY = false;
      bool zRaWiFVgMU = false;
      bool wQMrtPPVAK = false;
      bool nTminnpSks = false;
      bool sFTZkbRLQO = false;
      bool tBLVEXWRST = false;
      bool dHbAkedqht = false;
      bool ODwSbpwmHS = false;
      bool yEFlQlIQdQ = false;
      bool QYAQPkdToF = false;
      bool xZdVzpFrsO = false;
      bool ajKzVZCpjy = false;
      bool WNNRcpCfDq = false;
      bool McxBUXailZ = false;
      string QzSjhxHOip;
      string oNiZLrqUaW;
      string HhgRqUiloo;
      string ljcwXQpiip;
      string TgYLBjbGSU;
      string hMUSUhRBrM;
      string NVZtDFjlCt;
      string CIlkCaJVPG;
      string rcSTHZOJbp;
      string znpVcxGeIw;
      string AoEYSYZjQt;
      string XwklUjDGmc;
      string qZKMuNSPIF;
      string TeMTGCYsAh;
      string zesgRCDDBr;
      string sAreFZdrdF;
      string GKaLZrjQfR;
      string LKFEdLgctr;
      string JOOQLSmgOf;
      string YgPtboDhHY;
      if(QzSjhxHOip == AoEYSYZjQt){SlXjfitmBs = true;}
      else if(AoEYSYZjQt == QzSjhxHOip){sFTZkbRLQO = true;}
      if(oNiZLrqUaW == XwklUjDGmc){sAxkwquKzH = true;}
      else if(XwklUjDGmc == oNiZLrqUaW){tBLVEXWRST = true;}
      if(HhgRqUiloo == qZKMuNSPIF){FCCzsetKcn = true;}
      else if(qZKMuNSPIF == HhgRqUiloo){dHbAkedqht = true;}
      if(ljcwXQpiip == TeMTGCYsAh){IyVUZWqdjc = true;}
      else if(TeMTGCYsAh == ljcwXQpiip){ODwSbpwmHS = true;}
      if(TgYLBjbGSU == zesgRCDDBr){XAfUmXidyj = true;}
      else if(zesgRCDDBr == TgYLBjbGSU){yEFlQlIQdQ = true;}
      if(hMUSUhRBrM == sAreFZdrdF){srizTPiXqB = true;}
      else if(sAreFZdrdF == hMUSUhRBrM){QYAQPkdToF = true;}
      if(NVZtDFjlCt == GKaLZrjQfR){njJMjtdcKY = true;}
      else if(GKaLZrjQfR == NVZtDFjlCt){xZdVzpFrsO = true;}
      if(CIlkCaJVPG == LKFEdLgctr){zRaWiFVgMU = true;}
      if(rcSTHZOJbp == JOOQLSmgOf){wQMrtPPVAK = true;}
      if(znpVcxGeIw == YgPtboDhHY){nTminnpSks = true;}
      while(LKFEdLgctr == CIlkCaJVPG){ajKzVZCpjy = true;}
      while(JOOQLSmgOf == JOOQLSmgOf){WNNRcpCfDq = true;}
      while(YgPtboDhHY == YgPtboDhHY){McxBUXailZ = true;}
      if(SlXjfitmBs == true){SlXjfitmBs = false;}
      if(sAxkwquKzH == true){sAxkwquKzH = false;}
      if(FCCzsetKcn == true){FCCzsetKcn = false;}
      if(IyVUZWqdjc == true){IyVUZWqdjc = false;}
      if(XAfUmXidyj == true){XAfUmXidyj = false;}
      if(srizTPiXqB == true){srizTPiXqB = false;}
      if(njJMjtdcKY == true){njJMjtdcKY = false;}
      if(zRaWiFVgMU == true){zRaWiFVgMU = false;}
      if(wQMrtPPVAK == true){wQMrtPPVAK = false;}
      if(nTminnpSks == true){nTminnpSks = false;}
      if(sFTZkbRLQO == true){sFTZkbRLQO = false;}
      if(tBLVEXWRST == true){tBLVEXWRST = false;}
      if(dHbAkedqht == true){dHbAkedqht = false;}
      if(ODwSbpwmHS == true){ODwSbpwmHS = false;}
      if(yEFlQlIQdQ == true){yEFlQlIQdQ = false;}
      if(QYAQPkdToF == true){QYAQPkdToF = false;}
      if(xZdVzpFrsO == true){xZdVzpFrsO = false;}
      if(ajKzVZCpjy == true){ajKzVZCpjy = false;}
      if(WNNRcpCfDq == true){WNNRcpCfDq = false;}
      if(McxBUXailZ == true){McxBUXailZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENNFUCSNWV
{ 
  void VEDyGOQFIW()
  { 
      bool JKtzsTHRHr = false;
      bool ojjITIFXeh = false;
      bool hsLWTAtjnK = false;
      bool jTAdxdxwgs = false;
      bool WwEdkfMTyA = false;
      bool gbHdQPyWes = false;
      bool YWdwHUjFLp = false;
      bool LIplKkohln = false;
      bool nakmcHMVNg = false;
      bool eZQnTzSIVP = false;
      bool uGHInYlVSe = false;
      bool aQkqFylpSz = false;
      bool INreLkqCRL = false;
      bool RgLVrgSczE = false;
      bool VqChFNoZiU = false;
      bool MboVHgOcwC = false;
      bool giDHMtFOyX = false;
      bool fIqNcRLJYy = false;
      bool wRSxypqoNK = false;
      bool SogwXmmuUK = false;
      string xjcVgcSOXS;
      string EsRqbfbmSI;
      string UVEfznZZQX;
      string NBfGxSXhZB;
      string znVwRureuy;
      string dsiFgafwWs;
      string CsxAFCMKtJ;
      string ItMRJfzIOE;
      string uudRsTRaZV;
      string maKgyFpVpO;
      string hhklpjfRuB;
      string aWhSxHOeGk;
      string klkXVgieSD;
      string odRzVNJrbJ;
      string mzeXuPsqiq;
      string pKOFcwxMPI;
      string AAzrLwFhxj;
      string xWDwxkGMcG;
      string nquaMdOMWZ;
      string PxbSIlAmMy;
      if(xjcVgcSOXS == hhklpjfRuB){JKtzsTHRHr = true;}
      else if(hhklpjfRuB == xjcVgcSOXS){uGHInYlVSe = true;}
      if(EsRqbfbmSI == aWhSxHOeGk){ojjITIFXeh = true;}
      else if(aWhSxHOeGk == EsRqbfbmSI){aQkqFylpSz = true;}
      if(UVEfznZZQX == klkXVgieSD){hsLWTAtjnK = true;}
      else if(klkXVgieSD == UVEfznZZQX){INreLkqCRL = true;}
      if(NBfGxSXhZB == odRzVNJrbJ){jTAdxdxwgs = true;}
      else if(odRzVNJrbJ == NBfGxSXhZB){RgLVrgSczE = true;}
      if(znVwRureuy == mzeXuPsqiq){WwEdkfMTyA = true;}
      else if(mzeXuPsqiq == znVwRureuy){VqChFNoZiU = true;}
      if(dsiFgafwWs == pKOFcwxMPI){gbHdQPyWes = true;}
      else if(pKOFcwxMPI == dsiFgafwWs){MboVHgOcwC = true;}
      if(CsxAFCMKtJ == AAzrLwFhxj){YWdwHUjFLp = true;}
      else if(AAzrLwFhxj == CsxAFCMKtJ){giDHMtFOyX = true;}
      if(ItMRJfzIOE == xWDwxkGMcG){LIplKkohln = true;}
      if(uudRsTRaZV == nquaMdOMWZ){nakmcHMVNg = true;}
      if(maKgyFpVpO == PxbSIlAmMy){eZQnTzSIVP = true;}
      while(xWDwxkGMcG == ItMRJfzIOE){fIqNcRLJYy = true;}
      while(nquaMdOMWZ == nquaMdOMWZ){wRSxypqoNK = true;}
      while(PxbSIlAmMy == PxbSIlAmMy){SogwXmmuUK = true;}
      if(JKtzsTHRHr == true){JKtzsTHRHr = false;}
      if(ojjITIFXeh == true){ojjITIFXeh = false;}
      if(hsLWTAtjnK == true){hsLWTAtjnK = false;}
      if(jTAdxdxwgs == true){jTAdxdxwgs = false;}
      if(WwEdkfMTyA == true){WwEdkfMTyA = false;}
      if(gbHdQPyWes == true){gbHdQPyWes = false;}
      if(YWdwHUjFLp == true){YWdwHUjFLp = false;}
      if(LIplKkohln == true){LIplKkohln = false;}
      if(nakmcHMVNg == true){nakmcHMVNg = false;}
      if(eZQnTzSIVP == true){eZQnTzSIVP = false;}
      if(uGHInYlVSe == true){uGHInYlVSe = false;}
      if(aQkqFylpSz == true){aQkqFylpSz = false;}
      if(INreLkqCRL == true){INreLkqCRL = false;}
      if(RgLVrgSczE == true){RgLVrgSczE = false;}
      if(VqChFNoZiU == true){VqChFNoZiU = false;}
      if(MboVHgOcwC == true){MboVHgOcwC = false;}
      if(giDHMtFOyX == true){giDHMtFOyX = false;}
      if(fIqNcRLJYy == true){fIqNcRLJYy = false;}
      if(wRSxypqoNK == true){wRSxypqoNK = false;}
      if(SogwXmmuUK == true){SogwXmmuUK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EVGJRBHWAM
{ 
  void uTOWQokFRm()
  { 
      bool VCiutXMpma = false;
      bool IqWjFcOHAH = false;
      bool dErbJUGDiz = false;
      bool zLjurtAhqa = false;
      bool OGXDRLIAOM = false;
      bool lxQxrRJGlZ = false;
      bool RIGmawHbqK = false;
      bool bgQZrXfoKx = false;
      bool LFoVNCulDZ = false;
      bool ksuRIGzjcU = false;
      bool DgIEjFgpET = false;
      bool kUwnOLTkZY = false;
      bool BUXRYhkzQl = false;
      bool XwLosdwjkI = false;
      bool VEhinQxGCx = false;
      bool lOKEThIqeB = false;
      bool TgZRwoIGtj = false;
      bool OizRCwmocI = false;
      bool kdwTzJkHUK = false;
      bool UFFinnePmy = false;
      string nbjyuNslAQ;
      string eVbTtHdmBI;
      string PBhJrGWhuo;
      string xzzTVtfGtF;
      string CWBAPBPAzz;
      string EXXUlltaFn;
      string pKqLSfWIxA;
      string bWswGrAgtp;
      string qWiujYadgi;
      string zFBGOqfohj;
      string dHCzXhebOt;
      string lNgOxTauat;
      string EraOAVVmgO;
      string LKyJMjTjWC;
      string szPmxkYlIu;
      string PkOmekfnyC;
      string MrtzhaOWCN;
      string AqXYAEcnRO;
      string widlyawKda;
      string DfkUpAFQEV;
      if(nbjyuNslAQ == dHCzXhebOt){VCiutXMpma = true;}
      else if(dHCzXhebOt == nbjyuNslAQ){DgIEjFgpET = true;}
      if(eVbTtHdmBI == lNgOxTauat){IqWjFcOHAH = true;}
      else if(lNgOxTauat == eVbTtHdmBI){kUwnOLTkZY = true;}
      if(PBhJrGWhuo == EraOAVVmgO){dErbJUGDiz = true;}
      else if(EraOAVVmgO == PBhJrGWhuo){BUXRYhkzQl = true;}
      if(xzzTVtfGtF == LKyJMjTjWC){zLjurtAhqa = true;}
      else if(LKyJMjTjWC == xzzTVtfGtF){XwLosdwjkI = true;}
      if(CWBAPBPAzz == szPmxkYlIu){OGXDRLIAOM = true;}
      else if(szPmxkYlIu == CWBAPBPAzz){VEhinQxGCx = true;}
      if(EXXUlltaFn == PkOmekfnyC){lxQxrRJGlZ = true;}
      else if(PkOmekfnyC == EXXUlltaFn){lOKEThIqeB = true;}
      if(pKqLSfWIxA == MrtzhaOWCN){RIGmawHbqK = true;}
      else if(MrtzhaOWCN == pKqLSfWIxA){TgZRwoIGtj = true;}
      if(bWswGrAgtp == AqXYAEcnRO){bgQZrXfoKx = true;}
      if(qWiujYadgi == widlyawKda){LFoVNCulDZ = true;}
      if(zFBGOqfohj == DfkUpAFQEV){ksuRIGzjcU = true;}
      while(AqXYAEcnRO == bWswGrAgtp){OizRCwmocI = true;}
      while(widlyawKda == widlyawKda){kdwTzJkHUK = true;}
      while(DfkUpAFQEV == DfkUpAFQEV){UFFinnePmy = true;}
      if(VCiutXMpma == true){VCiutXMpma = false;}
      if(IqWjFcOHAH == true){IqWjFcOHAH = false;}
      if(dErbJUGDiz == true){dErbJUGDiz = false;}
      if(zLjurtAhqa == true){zLjurtAhqa = false;}
      if(OGXDRLIAOM == true){OGXDRLIAOM = false;}
      if(lxQxrRJGlZ == true){lxQxrRJGlZ = false;}
      if(RIGmawHbqK == true){RIGmawHbqK = false;}
      if(bgQZrXfoKx == true){bgQZrXfoKx = false;}
      if(LFoVNCulDZ == true){LFoVNCulDZ = false;}
      if(ksuRIGzjcU == true){ksuRIGzjcU = false;}
      if(DgIEjFgpET == true){DgIEjFgpET = false;}
      if(kUwnOLTkZY == true){kUwnOLTkZY = false;}
      if(BUXRYhkzQl == true){BUXRYhkzQl = false;}
      if(XwLosdwjkI == true){XwLosdwjkI = false;}
      if(VEhinQxGCx == true){VEhinQxGCx = false;}
      if(lOKEThIqeB == true){lOKEThIqeB = false;}
      if(TgZRwoIGtj == true){TgZRwoIGtj = false;}
      if(OizRCwmocI == true){OizRCwmocI = false;}
      if(kdwTzJkHUK == true){kdwTzJkHUK = false;}
      if(UFFinnePmy == true){UFFinnePmy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XZVDHJXKDZ
{ 
  void DZYfxbZOQw()
  { 
      bool WkcyJbFSFW = false;
      bool FaoeiZsZHV = false;
      bool ydYWCtnSMA = false;
      bool uJcWJGgDQm = false;
      bool jXwTthRyhX = false;
      bool AhanhrLFuO = false;
      bool nmFFawyRVc = false;
      bool roJUkZhFcU = false;
      bool cojozNhonQ = false;
      bool ubHCywSqsy = false;
      bool jAcFfKYGCI = false;
      bool KFcalyDQFN = false;
      bool NJcEgQhHVo = false;
      bool GpMdkcMdIo = false;
      bool oblfFoygPA = false;
      bool rBlekaWXYP = false;
      bool cRjNBUsypJ = false;
      bool kZHPYlWxyr = false;
      bool RAqVwEEgsK = false;
      bool FoFsMWqYdk = false;
      string mGuqDFGtee;
      string iKWkbDUUYJ;
      string EkoEZemKGH;
      string DaaDgDamQc;
      string yFtHxenVVu;
      string dJgpqBQpQY;
      string RwmWaHiTEY;
      string chDuKzqhHt;
      string pQnKdttkMe;
      string mjWrKCSWfo;
      string wTRxSuGker;
      string JiiVhAIbsg;
      string NyGYkrLLjI;
      string fUBSyVzprh;
      string nIFUVEBAJK;
      string tpdzayNrMZ;
      string jtAWLogQWL;
      string BRjKsErlDg;
      string qKBZOpqCqA;
      string IGdRxsIiJf;
      if(mGuqDFGtee == wTRxSuGker){WkcyJbFSFW = true;}
      else if(wTRxSuGker == mGuqDFGtee){jAcFfKYGCI = true;}
      if(iKWkbDUUYJ == JiiVhAIbsg){FaoeiZsZHV = true;}
      else if(JiiVhAIbsg == iKWkbDUUYJ){KFcalyDQFN = true;}
      if(EkoEZemKGH == NyGYkrLLjI){ydYWCtnSMA = true;}
      else if(NyGYkrLLjI == EkoEZemKGH){NJcEgQhHVo = true;}
      if(DaaDgDamQc == fUBSyVzprh){uJcWJGgDQm = true;}
      else if(fUBSyVzprh == DaaDgDamQc){GpMdkcMdIo = true;}
      if(yFtHxenVVu == nIFUVEBAJK){jXwTthRyhX = true;}
      else if(nIFUVEBAJK == yFtHxenVVu){oblfFoygPA = true;}
      if(dJgpqBQpQY == tpdzayNrMZ){AhanhrLFuO = true;}
      else if(tpdzayNrMZ == dJgpqBQpQY){rBlekaWXYP = true;}
      if(RwmWaHiTEY == jtAWLogQWL){nmFFawyRVc = true;}
      else if(jtAWLogQWL == RwmWaHiTEY){cRjNBUsypJ = true;}
      if(chDuKzqhHt == BRjKsErlDg){roJUkZhFcU = true;}
      if(pQnKdttkMe == qKBZOpqCqA){cojozNhonQ = true;}
      if(mjWrKCSWfo == IGdRxsIiJf){ubHCywSqsy = true;}
      while(BRjKsErlDg == chDuKzqhHt){kZHPYlWxyr = true;}
      while(qKBZOpqCqA == qKBZOpqCqA){RAqVwEEgsK = true;}
      while(IGdRxsIiJf == IGdRxsIiJf){FoFsMWqYdk = true;}
      if(WkcyJbFSFW == true){WkcyJbFSFW = false;}
      if(FaoeiZsZHV == true){FaoeiZsZHV = false;}
      if(ydYWCtnSMA == true){ydYWCtnSMA = false;}
      if(uJcWJGgDQm == true){uJcWJGgDQm = false;}
      if(jXwTthRyhX == true){jXwTthRyhX = false;}
      if(AhanhrLFuO == true){AhanhrLFuO = false;}
      if(nmFFawyRVc == true){nmFFawyRVc = false;}
      if(roJUkZhFcU == true){roJUkZhFcU = false;}
      if(cojozNhonQ == true){cojozNhonQ = false;}
      if(ubHCywSqsy == true){ubHCywSqsy = false;}
      if(jAcFfKYGCI == true){jAcFfKYGCI = false;}
      if(KFcalyDQFN == true){KFcalyDQFN = false;}
      if(NJcEgQhHVo == true){NJcEgQhHVo = false;}
      if(GpMdkcMdIo == true){GpMdkcMdIo = false;}
      if(oblfFoygPA == true){oblfFoygPA = false;}
      if(rBlekaWXYP == true){rBlekaWXYP = false;}
      if(cRjNBUsypJ == true){cRjNBUsypJ = false;}
      if(kZHPYlWxyr == true){kZHPYlWxyr = false;}
      if(RAqVwEEgsK == true){RAqVwEEgsK = false;}
      if(FoFsMWqYdk == true){FoFsMWqYdk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UTZDECBTCU
{ 
  void NfXKoWgpIA()
  { 
      bool KTRYNSDQFk = false;
      bool eBQNuAmiGB = false;
      bool eoAyQxIarm = false;
      bool EayMecFzAh = false;
      bool jwVQduXAYL = false;
      bool uQtIaVTSHP = false;
      bool JbXRfDDDiS = false;
      bool umhYQiSiUV = false;
      bool YHCfrnfolI = false;
      bool IlrjXIXDjZ = false;
      bool rURFQHiVrq = false;
      bool CjxkpCZrZr = false;
      bool WNRZJIuxAI = false;
      bool LPzudEpwOj = false;
      bool EKxtFYoGsV = false;
      bool hedrCdCruI = false;
      bool MkUifmkCHl = false;
      bool LccpmMQWTk = false;
      bool ToDeZfkHsz = false;
      bool BxAGXTpNOS = false;
      string PfOUMBgsKf;
      string CTofQaPIYS;
      string lxSkqXPKNP;
      string AsaEpHsXsy;
      string znEXBkBpbq;
      string LjkSaSNdco;
      string lVetfJskoJ;
      string gqOaTxrtjG;
      string VZiWEPHHcX;
      string sPuEMcIKqq;
      string qQASJTVKyd;
      string ZStVSLmIoP;
      string BkHQPRwJOq;
      string nhCrOFYQMj;
      string twIzyaVYlA;
      string oAUbpGJjCr;
      string XLwHorPBHN;
      string mWwEVEbHSo;
      string wWXNBnMaBI;
      string woNUMhzBJF;
      if(PfOUMBgsKf == qQASJTVKyd){KTRYNSDQFk = true;}
      else if(qQASJTVKyd == PfOUMBgsKf){rURFQHiVrq = true;}
      if(CTofQaPIYS == ZStVSLmIoP){eBQNuAmiGB = true;}
      else if(ZStVSLmIoP == CTofQaPIYS){CjxkpCZrZr = true;}
      if(lxSkqXPKNP == BkHQPRwJOq){eoAyQxIarm = true;}
      else if(BkHQPRwJOq == lxSkqXPKNP){WNRZJIuxAI = true;}
      if(AsaEpHsXsy == nhCrOFYQMj){EayMecFzAh = true;}
      else if(nhCrOFYQMj == AsaEpHsXsy){LPzudEpwOj = true;}
      if(znEXBkBpbq == twIzyaVYlA){jwVQduXAYL = true;}
      else if(twIzyaVYlA == znEXBkBpbq){EKxtFYoGsV = true;}
      if(LjkSaSNdco == oAUbpGJjCr){uQtIaVTSHP = true;}
      else if(oAUbpGJjCr == LjkSaSNdco){hedrCdCruI = true;}
      if(lVetfJskoJ == XLwHorPBHN){JbXRfDDDiS = true;}
      else if(XLwHorPBHN == lVetfJskoJ){MkUifmkCHl = true;}
      if(gqOaTxrtjG == mWwEVEbHSo){umhYQiSiUV = true;}
      if(VZiWEPHHcX == wWXNBnMaBI){YHCfrnfolI = true;}
      if(sPuEMcIKqq == woNUMhzBJF){IlrjXIXDjZ = true;}
      while(mWwEVEbHSo == gqOaTxrtjG){LccpmMQWTk = true;}
      while(wWXNBnMaBI == wWXNBnMaBI){ToDeZfkHsz = true;}
      while(woNUMhzBJF == woNUMhzBJF){BxAGXTpNOS = true;}
      if(KTRYNSDQFk == true){KTRYNSDQFk = false;}
      if(eBQNuAmiGB == true){eBQNuAmiGB = false;}
      if(eoAyQxIarm == true){eoAyQxIarm = false;}
      if(EayMecFzAh == true){EayMecFzAh = false;}
      if(jwVQduXAYL == true){jwVQduXAYL = false;}
      if(uQtIaVTSHP == true){uQtIaVTSHP = false;}
      if(JbXRfDDDiS == true){JbXRfDDDiS = false;}
      if(umhYQiSiUV == true){umhYQiSiUV = false;}
      if(YHCfrnfolI == true){YHCfrnfolI = false;}
      if(IlrjXIXDjZ == true){IlrjXIXDjZ = false;}
      if(rURFQHiVrq == true){rURFQHiVrq = false;}
      if(CjxkpCZrZr == true){CjxkpCZrZr = false;}
      if(WNRZJIuxAI == true){WNRZJIuxAI = false;}
      if(LPzudEpwOj == true){LPzudEpwOj = false;}
      if(EKxtFYoGsV == true){EKxtFYoGsV = false;}
      if(hedrCdCruI == true){hedrCdCruI = false;}
      if(MkUifmkCHl == true){MkUifmkCHl = false;}
      if(LccpmMQWTk == true){LccpmMQWTk = false;}
      if(ToDeZfkHsz == true){ToDeZfkHsz = false;}
      if(BxAGXTpNOS == true){BxAGXTpNOS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FFIWVBCZJM
{ 
  void YqFZIcdFJN()
  { 
      bool UGngUIIVob = false;
      bool kWqclTVIjp = false;
      bool wVQsfEzAMP = false;
      bool XZIKiBRtpW = false;
      bool fHZTdtXljc = false;
      bool ttDQOyotBQ = false;
      bool JIJYEKOgtj = false;
      bool CbSNKouxPk = false;
      bool fNPiVdWruj = false;
      bool MWrYMWxBPS = false;
      bool fqrzaSboGY = false;
      bool CrdQjwraDZ = false;
      bool mWkJWeisAm = false;
      bool qtgwEnUQHD = false;
      bool CglVgUrboQ = false;
      bool eWypeJGhbu = false;
      bool ihoShIKgLw = false;
      bool abSzXGkOcC = false;
      bool lGEiITwqRu = false;
      bool gmnLTTrSnY = false;
      string LjItOlZrXG;
      string mazBoHqPOb;
      string XIPsqStXTt;
      string BxiOXzxVcc;
      string monRqKYxhg;
      string wnFJfDUODw;
      string rBYcFoqjcp;
      string KUlkoiTxBf;
      string swolxNqYiU;
      string dhSgkkQKMB;
      string SnUrWaBUUx;
      string iWNWCuMlfq;
      string ySBHLbCFAE;
      string SIkzNEbwPV;
      string LWEklHTwdo;
      string YdeUDzmMgt;
      string YwTPdZlNIx;
      string TPVJfaOPVE;
      string IFaLfndPwO;
      string RPPVxPCnGL;
      if(LjItOlZrXG == SnUrWaBUUx){UGngUIIVob = true;}
      else if(SnUrWaBUUx == LjItOlZrXG){fqrzaSboGY = true;}
      if(mazBoHqPOb == iWNWCuMlfq){kWqclTVIjp = true;}
      else if(iWNWCuMlfq == mazBoHqPOb){CrdQjwraDZ = true;}
      if(XIPsqStXTt == ySBHLbCFAE){wVQsfEzAMP = true;}
      else if(ySBHLbCFAE == XIPsqStXTt){mWkJWeisAm = true;}
      if(BxiOXzxVcc == SIkzNEbwPV){XZIKiBRtpW = true;}
      else if(SIkzNEbwPV == BxiOXzxVcc){qtgwEnUQHD = true;}
      if(monRqKYxhg == LWEklHTwdo){fHZTdtXljc = true;}
      else if(LWEklHTwdo == monRqKYxhg){CglVgUrboQ = true;}
      if(wnFJfDUODw == YdeUDzmMgt){ttDQOyotBQ = true;}
      else if(YdeUDzmMgt == wnFJfDUODw){eWypeJGhbu = true;}
      if(rBYcFoqjcp == YwTPdZlNIx){JIJYEKOgtj = true;}
      else if(YwTPdZlNIx == rBYcFoqjcp){ihoShIKgLw = true;}
      if(KUlkoiTxBf == TPVJfaOPVE){CbSNKouxPk = true;}
      if(swolxNqYiU == IFaLfndPwO){fNPiVdWruj = true;}
      if(dhSgkkQKMB == RPPVxPCnGL){MWrYMWxBPS = true;}
      while(TPVJfaOPVE == KUlkoiTxBf){abSzXGkOcC = true;}
      while(IFaLfndPwO == IFaLfndPwO){lGEiITwqRu = true;}
      while(RPPVxPCnGL == RPPVxPCnGL){gmnLTTrSnY = true;}
      if(UGngUIIVob == true){UGngUIIVob = false;}
      if(kWqclTVIjp == true){kWqclTVIjp = false;}
      if(wVQsfEzAMP == true){wVQsfEzAMP = false;}
      if(XZIKiBRtpW == true){XZIKiBRtpW = false;}
      if(fHZTdtXljc == true){fHZTdtXljc = false;}
      if(ttDQOyotBQ == true){ttDQOyotBQ = false;}
      if(JIJYEKOgtj == true){JIJYEKOgtj = false;}
      if(CbSNKouxPk == true){CbSNKouxPk = false;}
      if(fNPiVdWruj == true){fNPiVdWruj = false;}
      if(MWrYMWxBPS == true){MWrYMWxBPS = false;}
      if(fqrzaSboGY == true){fqrzaSboGY = false;}
      if(CrdQjwraDZ == true){CrdQjwraDZ = false;}
      if(mWkJWeisAm == true){mWkJWeisAm = false;}
      if(qtgwEnUQHD == true){qtgwEnUQHD = false;}
      if(CglVgUrboQ == true){CglVgUrboQ = false;}
      if(eWypeJGhbu == true){eWypeJGhbu = false;}
      if(ihoShIKgLw == true){ihoShIKgLw = false;}
      if(abSzXGkOcC == true){abSzXGkOcC = false;}
      if(lGEiITwqRu == true){lGEiITwqRu = false;}
      if(gmnLTTrSnY == true){gmnLTTrSnY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JAIKSRGIYI
{ 
  void sAfmoOCECk()
  { 
      bool drGmaYOjRa = false;
      bool elRdelGeJk = false;
      bool eVDljOPqSR = false;
      bool iDTGfdGFOE = false;
      bool DNhYJmPVhI = false;
      bool REtUEHnTDM = false;
      bool JWRArbSLxB = false;
      bool eBPEhQmdcw = false;
      bool ysJJzeJzCY = false;
      bool omCCufwhgh = false;
      bool UEXfdQnplm = false;
      bool TJpGNPMHAN = false;
      bool RTJYLryNIB = false;
      bool UFxubtUdfi = false;
      bool pTMOEewwnf = false;
      bool SnhSPAuzUl = false;
      bool RagkROMudT = false;
      bool tibQWxHtTg = false;
      bool wCYbhgWdea = false;
      bool zVJtROlawp = false;
      string QqxETfYGKF;
      string KxknlMinUq;
      string FweooysgIP;
      string dyFHDsCBKw;
      string iiyydbVtrc;
      string bRILKUMIPU;
      string lrxtaMqdjr;
      string KgdYHWyfKM;
      string bznfnMotwi;
      string gskoKqkDXQ;
      string jrJARtnjDn;
      string WfxDslDRGO;
      string XxgBLRunOQ;
      string ktItbjpnNs;
      string XEpILAuhwX;
      string mSwIsmKHnA;
      string zzVmCbWDbI;
      string wOEMpSHYpK;
      string VNrpcRxAAo;
      string YhzMtYiDFi;
      if(QqxETfYGKF == jrJARtnjDn){drGmaYOjRa = true;}
      else if(jrJARtnjDn == QqxETfYGKF){UEXfdQnplm = true;}
      if(KxknlMinUq == WfxDslDRGO){elRdelGeJk = true;}
      else if(WfxDslDRGO == KxknlMinUq){TJpGNPMHAN = true;}
      if(FweooysgIP == XxgBLRunOQ){eVDljOPqSR = true;}
      else if(XxgBLRunOQ == FweooysgIP){RTJYLryNIB = true;}
      if(dyFHDsCBKw == ktItbjpnNs){iDTGfdGFOE = true;}
      else if(ktItbjpnNs == dyFHDsCBKw){UFxubtUdfi = true;}
      if(iiyydbVtrc == XEpILAuhwX){DNhYJmPVhI = true;}
      else if(XEpILAuhwX == iiyydbVtrc){pTMOEewwnf = true;}
      if(bRILKUMIPU == mSwIsmKHnA){REtUEHnTDM = true;}
      else if(mSwIsmKHnA == bRILKUMIPU){SnhSPAuzUl = true;}
      if(lrxtaMqdjr == zzVmCbWDbI){JWRArbSLxB = true;}
      else if(zzVmCbWDbI == lrxtaMqdjr){RagkROMudT = true;}
      if(KgdYHWyfKM == wOEMpSHYpK){eBPEhQmdcw = true;}
      if(bznfnMotwi == VNrpcRxAAo){ysJJzeJzCY = true;}
      if(gskoKqkDXQ == YhzMtYiDFi){omCCufwhgh = true;}
      while(wOEMpSHYpK == KgdYHWyfKM){tibQWxHtTg = true;}
      while(VNrpcRxAAo == VNrpcRxAAo){wCYbhgWdea = true;}
      while(YhzMtYiDFi == YhzMtYiDFi){zVJtROlawp = true;}
      if(drGmaYOjRa == true){drGmaYOjRa = false;}
      if(elRdelGeJk == true){elRdelGeJk = false;}
      if(eVDljOPqSR == true){eVDljOPqSR = false;}
      if(iDTGfdGFOE == true){iDTGfdGFOE = false;}
      if(DNhYJmPVhI == true){DNhYJmPVhI = false;}
      if(REtUEHnTDM == true){REtUEHnTDM = false;}
      if(JWRArbSLxB == true){JWRArbSLxB = false;}
      if(eBPEhQmdcw == true){eBPEhQmdcw = false;}
      if(ysJJzeJzCY == true){ysJJzeJzCY = false;}
      if(omCCufwhgh == true){omCCufwhgh = false;}
      if(UEXfdQnplm == true){UEXfdQnplm = false;}
      if(TJpGNPMHAN == true){TJpGNPMHAN = false;}
      if(RTJYLryNIB == true){RTJYLryNIB = false;}
      if(UFxubtUdfi == true){UFxubtUdfi = false;}
      if(pTMOEewwnf == true){pTMOEewwnf = false;}
      if(SnhSPAuzUl == true){SnhSPAuzUl = false;}
      if(RagkROMudT == true){RagkROMudT = false;}
      if(tibQWxHtTg == true){tibQWxHtTg = false;}
      if(wCYbhgWdea == true){wCYbhgWdea = false;}
      if(zVJtROlawp == true){zVJtROlawp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IQZDBZVODQ
{ 
  void xBFXneRhNj()
  { 
      bool VTwHUqVjPg = false;
      bool cEhCXLgKfM = false;
      bool LcPikNtdxb = false;
      bool QPPDciUJVh = false;
      bool mDMQQkDyKh = false;
      bool GlWWhrEMWG = false;
      bool xqmmPNoeYo = false;
      bool pWnyZHPyRA = false;
      bool JuTOVdrrUk = false;
      bool dHmPkuQZAD = false;
      bool uYZVrixYxa = false;
      bool cFtVwBXXRl = false;
      bool UwJnKhjYMd = false;
      bool qpyOEjVxWl = false;
      bool fTutIXMQSi = false;
      bool XrHNizPkKJ = false;
      bool zYLTilHfRL = false;
      bool fZBeGABOfl = false;
      bool UTGdFzhjfF = false;
      bool UjmNmHIaLV = false;
      string NAlaFkMyoF;
      string DFGiLOGTFU;
      string zsygsjWeEn;
      string ZczgesqYVD;
      string TAoLgehdxi;
      string AtPUNTCEgU;
      string NgsAfZGYDS;
      string WhyCAzEmzN;
      string CshVnfMdTK;
      string qlqApmGneH;
      string YIZdLRuNTN;
      string POFSSTzXMA;
      string McFsbjpyMN;
      string rPIrosTDJV;
      string jzJFtbgYgV;
      string miaetuDgCa;
      string bxBGVAGMcZ;
      string AuNqPNSzyz;
      string DQQqZIncxt;
      string olBismxDjt;
      if(NAlaFkMyoF == YIZdLRuNTN){VTwHUqVjPg = true;}
      else if(YIZdLRuNTN == NAlaFkMyoF){uYZVrixYxa = true;}
      if(DFGiLOGTFU == POFSSTzXMA){cEhCXLgKfM = true;}
      else if(POFSSTzXMA == DFGiLOGTFU){cFtVwBXXRl = true;}
      if(zsygsjWeEn == McFsbjpyMN){LcPikNtdxb = true;}
      else if(McFsbjpyMN == zsygsjWeEn){UwJnKhjYMd = true;}
      if(ZczgesqYVD == rPIrosTDJV){QPPDciUJVh = true;}
      else if(rPIrosTDJV == ZczgesqYVD){qpyOEjVxWl = true;}
      if(TAoLgehdxi == jzJFtbgYgV){mDMQQkDyKh = true;}
      else if(jzJFtbgYgV == TAoLgehdxi){fTutIXMQSi = true;}
      if(AtPUNTCEgU == miaetuDgCa){GlWWhrEMWG = true;}
      else if(miaetuDgCa == AtPUNTCEgU){XrHNizPkKJ = true;}
      if(NgsAfZGYDS == bxBGVAGMcZ){xqmmPNoeYo = true;}
      else if(bxBGVAGMcZ == NgsAfZGYDS){zYLTilHfRL = true;}
      if(WhyCAzEmzN == AuNqPNSzyz){pWnyZHPyRA = true;}
      if(CshVnfMdTK == DQQqZIncxt){JuTOVdrrUk = true;}
      if(qlqApmGneH == olBismxDjt){dHmPkuQZAD = true;}
      while(AuNqPNSzyz == WhyCAzEmzN){fZBeGABOfl = true;}
      while(DQQqZIncxt == DQQqZIncxt){UTGdFzhjfF = true;}
      while(olBismxDjt == olBismxDjt){UjmNmHIaLV = true;}
      if(VTwHUqVjPg == true){VTwHUqVjPg = false;}
      if(cEhCXLgKfM == true){cEhCXLgKfM = false;}
      if(LcPikNtdxb == true){LcPikNtdxb = false;}
      if(QPPDciUJVh == true){QPPDciUJVh = false;}
      if(mDMQQkDyKh == true){mDMQQkDyKh = false;}
      if(GlWWhrEMWG == true){GlWWhrEMWG = false;}
      if(xqmmPNoeYo == true){xqmmPNoeYo = false;}
      if(pWnyZHPyRA == true){pWnyZHPyRA = false;}
      if(JuTOVdrrUk == true){JuTOVdrrUk = false;}
      if(dHmPkuQZAD == true){dHmPkuQZAD = false;}
      if(uYZVrixYxa == true){uYZVrixYxa = false;}
      if(cFtVwBXXRl == true){cFtVwBXXRl = false;}
      if(UwJnKhjYMd == true){UwJnKhjYMd = false;}
      if(qpyOEjVxWl == true){qpyOEjVxWl = false;}
      if(fTutIXMQSi == true){fTutIXMQSi = false;}
      if(XrHNizPkKJ == true){XrHNizPkKJ = false;}
      if(zYLTilHfRL == true){zYLTilHfRL = false;}
      if(fZBeGABOfl == true){fZBeGABOfl = false;}
      if(UTGdFzhjfF == true){UTGdFzhjfF = false;}
      if(UjmNmHIaLV == true){UjmNmHIaLV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUYEMPICES
{ 
  void VmmRWTDASM()
  { 
      bool cswpfuOOsB = false;
      bool URKwqInmVM = false;
      bool GnNcjIKpLr = false;
      bool PXurPDPTeo = false;
      bool jGaIZtyelb = false;
      bool DXkfWnfTGX = false;
      bool kXDBlxVRgm = false;
      bool rTIfbANFCo = false;
      bool JeEjoqlOVa = false;
      bool XwNGEMDYVc = false;
      bool XfyyjiOFEV = false;
      bool aZQQNGTTMt = false;
      bool LGwFOwGBbP = false;
      bool xojZQdgFzF = false;
      bool cfKzAyexry = false;
      bool rjMaQRjrin = false;
      bool cNdoYlppzj = false;
      bool YNTGRewxFQ = false;
      bool QIJdWMbIJz = false;
      bool snWLbOCUZO = false;
      string QUXXhMVTtl;
      string owgLVbWVZc;
      string WOOOOFEfOj;
      string amPpRykyaM;
      string ZWVOPZoDst;
      string boUbsCGJIc;
      string HpEJLCgpsX;
      string qXtNCzrAzn;
      string PAmTIkRmxP;
      string rboyEjSMDM;
      string syKVDDtHYs;
      string JFKTMHDjBZ;
      string jssceOhwIS;
      string gfxluRpRQF;
      string pJNEGlRVkx;
      string ghKcbAFgpn;
      string UyyGLcIXYu;
      string QlSwjaenWs;
      string xMKLkzVTJu;
      string LIbcjqLHsd;
      if(QUXXhMVTtl == syKVDDtHYs){cswpfuOOsB = true;}
      else if(syKVDDtHYs == QUXXhMVTtl){XfyyjiOFEV = true;}
      if(owgLVbWVZc == JFKTMHDjBZ){URKwqInmVM = true;}
      else if(JFKTMHDjBZ == owgLVbWVZc){aZQQNGTTMt = true;}
      if(WOOOOFEfOj == jssceOhwIS){GnNcjIKpLr = true;}
      else if(jssceOhwIS == WOOOOFEfOj){LGwFOwGBbP = true;}
      if(amPpRykyaM == gfxluRpRQF){PXurPDPTeo = true;}
      else if(gfxluRpRQF == amPpRykyaM){xojZQdgFzF = true;}
      if(ZWVOPZoDst == pJNEGlRVkx){jGaIZtyelb = true;}
      else if(pJNEGlRVkx == ZWVOPZoDst){cfKzAyexry = true;}
      if(boUbsCGJIc == ghKcbAFgpn){DXkfWnfTGX = true;}
      else if(ghKcbAFgpn == boUbsCGJIc){rjMaQRjrin = true;}
      if(HpEJLCgpsX == UyyGLcIXYu){kXDBlxVRgm = true;}
      else if(UyyGLcIXYu == HpEJLCgpsX){cNdoYlppzj = true;}
      if(qXtNCzrAzn == QlSwjaenWs){rTIfbANFCo = true;}
      if(PAmTIkRmxP == xMKLkzVTJu){JeEjoqlOVa = true;}
      if(rboyEjSMDM == LIbcjqLHsd){XwNGEMDYVc = true;}
      while(QlSwjaenWs == qXtNCzrAzn){YNTGRewxFQ = true;}
      while(xMKLkzVTJu == xMKLkzVTJu){QIJdWMbIJz = true;}
      while(LIbcjqLHsd == LIbcjqLHsd){snWLbOCUZO = true;}
      if(cswpfuOOsB == true){cswpfuOOsB = false;}
      if(URKwqInmVM == true){URKwqInmVM = false;}
      if(GnNcjIKpLr == true){GnNcjIKpLr = false;}
      if(PXurPDPTeo == true){PXurPDPTeo = false;}
      if(jGaIZtyelb == true){jGaIZtyelb = false;}
      if(DXkfWnfTGX == true){DXkfWnfTGX = false;}
      if(kXDBlxVRgm == true){kXDBlxVRgm = false;}
      if(rTIfbANFCo == true){rTIfbANFCo = false;}
      if(JeEjoqlOVa == true){JeEjoqlOVa = false;}
      if(XwNGEMDYVc == true){XwNGEMDYVc = false;}
      if(XfyyjiOFEV == true){XfyyjiOFEV = false;}
      if(aZQQNGTTMt == true){aZQQNGTTMt = false;}
      if(LGwFOwGBbP == true){LGwFOwGBbP = false;}
      if(xojZQdgFzF == true){xojZQdgFzF = false;}
      if(cfKzAyexry == true){cfKzAyexry = false;}
      if(rjMaQRjrin == true){rjMaQRjrin = false;}
      if(cNdoYlppzj == true){cNdoYlppzj = false;}
      if(YNTGRewxFQ == true){YNTGRewxFQ = false;}
      if(QIJdWMbIJz == true){QIJdWMbIJz = false;}
      if(snWLbOCUZO == true){snWLbOCUZO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WELHBEXYFV
{ 
  void sQhynsiYRG()
  { 
      bool oqMZSCeOwj = false;
      bool niWPLJLpVz = false;
      bool GOtAADKqjy = false;
      bool MemoUcMsZK = false;
      bool FEUltYbOyf = false;
      bool jotlIZxLYO = false;
      bool qmdyXIuhui = false;
      bool wSQKsBtHFa = false;
      bool ausDNWkAgt = false;
      bool eBUKTSaWNk = false;
      bool ctTPjRYisH = false;
      bool foFxnusZjA = false;
      bool XuBADuxFqZ = false;
      bool ZXsTygbdTu = false;
      bool yBHZOpuWVX = false;
      bool YAlNNhrTLn = false;
      bool TSrSgHwkzG = false;
      bool TPGoBVnbkN = false;
      bool AajTBZkfGP = false;
      bool nIRfafJnsH = false;
      string jWULatKBbh;
      string fHdIGSPJfl;
      string IINZMjXEIA;
      string CRXNwRRwzU;
      string sROsuPRetJ;
      string WrHhqbItzq;
      string VFrbfOjPMn;
      string ASKLsptUex;
      string RsKzcJJoVU;
      string IXxHymZmMg;
      string eBSFIEhwoA;
      string gnOBYcuryV;
      string EutqecUCNF;
      string QHHySPZFpY;
      string bNzUnUIuiU;
      string rgnpbiHaZf;
      string iehiiZfQiI;
      string CpCZtquYDJ;
      string UYTrNjSQWi;
      string IzeKowePlO;
      if(jWULatKBbh == eBSFIEhwoA){oqMZSCeOwj = true;}
      else if(eBSFIEhwoA == jWULatKBbh){ctTPjRYisH = true;}
      if(fHdIGSPJfl == gnOBYcuryV){niWPLJLpVz = true;}
      else if(gnOBYcuryV == fHdIGSPJfl){foFxnusZjA = true;}
      if(IINZMjXEIA == EutqecUCNF){GOtAADKqjy = true;}
      else if(EutqecUCNF == IINZMjXEIA){XuBADuxFqZ = true;}
      if(CRXNwRRwzU == QHHySPZFpY){MemoUcMsZK = true;}
      else if(QHHySPZFpY == CRXNwRRwzU){ZXsTygbdTu = true;}
      if(sROsuPRetJ == bNzUnUIuiU){FEUltYbOyf = true;}
      else if(bNzUnUIuiU == sROsuPRetJ){yBHZOpuWVX = true;}
      if(WrHhqbItzq == rgnpbiHaZf){jotlIZxLYO = true;}
      else if(rgnpbiHaZf == WrHhqbItzq){YAlNNhrTLn = true;}
      if(VFrbfOjPMn == iehiiZfQiI){qmdyXIuhui = true;}
      else if(iehiiZfQiI == VFrbfOjPMn){TSrSgHwkzG = true;}
      if(ASKLsptUex == CpCZtquYDJ){wSQKsBtHFa = true;}
      if(RsKzcJJoVU == UYTrNjSQWi){ausDNWkAgt = true;}
      if(IXxHymZmMg == IzeKowePlO){eBUKTSaWNk = true;}
      while(CpCZtquYDJ == ASKLsptUex){TPGoBVnbkN = true;}
      while(UYTrNjSQWi == UYTrNjSQWi){AajTBZkfGP = true;}
      while(IzeKowePlO == IzeKowePlO){nIRfafJnsH = true;}
      if(oqMZSCeOwj == true){oqMZSCeOwj = false;}
      if(niWPLJLpVz == true){niWPLJLpVz = false;}
      if(GOtAADKqjy == true){GOtAADKqjy = false;}
      if(MemoUcMsZK == true){MemoUcMsZK = false;}
      if(FEUltYbOyf == true){FEUltYbOyf = false;}
      if(jotlIZxLYO == true){jotlIZxLYO = false;}
      if(qmdyXIuhui == true){qmdyXIuhui = false;}
      if(wSQKsBtHFa == true){wSQKsBtHFa = false;}
      if(ausDNWkAgt == true){ausDNWkAgt = false;}
      if(eBUKTSaWNk == true){eBUKTSaWNk = false;}
      if(ctTPjRYisH == true){ctTPjRYisH = false;}
      if(foFxnusZjA == true){foFxnusZjA = false;}
      if(XuBADuxFqZ == true){XuBADuxFqZ = false;}
      if(ZXsTygbdTu == true){ZXsTygbdTu = false;}
      if(yBHZOpuWVX == true){yBHZOpuWVX = false;}
      if(YAlNNhrTLn == true){YAlNNhrTLn = false;}
      if(TSrSgHwkzG == true){TSrSgHwkzG = false;}
      if(TPGoBVnbkN == true){TPGoBVnbkN = false;}
      if(AajTBZkfGP == true){AajTBZkfGP = false;}
      if(nIRfafJnsH == true){nIRfafJnsH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYJJNIALWD
{ 
  void bIDlMCxUJy()
  { 
      bool USFEEUDkwm = false;
      bool yhQUxenpTP = false;
      bool QaJixVCQRX = false;
      bool IgLUtCPfrb = false;
      bool cdNheCWIYw = false;
      bool LsoufsIWGh = false;
      bool RmTYeRWwau = false;
      bool PHxqmlNbDu = false;
      bool ztrULPqQoB = false;
      bool srZKJpJnCM = false;
      bool fagcgDuxIs = false;
      bool egSKhXtyMP = false;
      bool ZFGZBWhmgx = false;
      bool cYYpPYMOnI = false;
      bool TsHuVLZObl = false;
      bool uKbmmZTHbJ = false;
      bool UIQLQGHbuJ = false;
      bool KeJDugxKDo = false;
      bool xSKuBRxkDo = false;
      bool EFmemLcweO = false;
      string JqCZNyezhV;
      string JwjUZAfucA;
      string AmfaaOURCs;
      string CYsfYhEuLX;
      string INqjeGnWxe;
      string ZgDGFVLayz;
      string cNxoSjCEur;
      string ujjFrmwuuU;
      string ZxTWSVUmZC;
      string WcwLttQBQt;
      string DjbFjowyNS;
      string ZPfdYftZWx;
      string OOdsVRnXKx;
      string WtdARpVNmc;
      string YWYHbGxSmN;
      string ApeTfnFhjR;
      string BYmQwfleMi;
      string JflsXroWQO;
      string UVjwwfPKUc;
      string kmcVbAiIKw;
      if(JqCZNyezhV == DjbFjowyNS){USFEEUDkwm = true;}
      else if(DjbFjowyNS == JqCZNyezhV){fagcgDuxIs = true;}
      if(JwjUZAfucA == ZPfdYftZWx){yhQUxenpTP = true;}
      else if(ZPfdYftZWx == JwjUZAfucA){egSKhXtyMP = true;}
      if(AmfaaOURCs == OOdsVRnXKx){QaJixVCQRX = true;}
      else if(OOdsVRnXKx == AmfaaOURCs){ZFGZBWhmgx = true;}
      if(CYsfYhEuLX == WtdARpVNmc){IgLUtCPfrb = true;}
      else if(WtdARpVNmc == CYsfYhEuLX){cYYpPYMOnI = true;}
      if(INqjeGnWxe == YWYHbGxSmN){cdNheCWIYw = true;}
      else if(YWYHbGxSmN == INqjeGnWxe){TsHuVLZObl = true;}
      if(ZgDGFVLayz == ApeTfnFhjR){LsoufsIWGh = true;}
      else if(ApeTfnFhjR == ZgDGFVLayz){uKbmmZTHbJ = true;}
      if(cNxoSjCEur == BYmQwfleMi){RmTYeRWwau = true;}
      else if(BYmQwfleMi == cNxoSjCEur){UIQLQGHbuJ = true;}
      if(ujjFrmwuuU == JflsXroWQO){PHxqmlNbDu = true;}
      if(ZxTWSVUmZC == UVjwwfPKUc){ztrULPqQoB = true;}
      if(WcwLttQBQt == kmcVbAiIKw){srZKJpJnCM = true;}
      while(JflsXroWQO == ujjFrmwuuU){KeJDugxKDo = true;}
      while(UVjwwfPKUc == UVjwwfPKUc){xSKuBRxkDo = true;}
      while(kmcVbAiIKw == kmcVbAiIKw){EFmemLcweO = true;}
      if(USFEEUDkwm == true){USFEEUDkwm = false;}
      if(yhQUxenpTP == true){yhQUxenpTP = false;}
      if(QaJixVCQRX == true){QaJixVCQRX = false;}
      if(IgLUtCPfrb == true){IgLUtCPfrb = false;}
      if(cdNheCWIYw == true){cdNheCWIYw = false;}
      if(LsoufsIWGh == true){LsoufsIWGh = false;}
      if(RmTYeRWwau == true){RmTYeRWwau = false;}
      if(PHxqmlNbDu == true){PHxqmlNbDu = false;}
      if(ztrULPqQoB == true){ztrULPqQoB = false;}
      if(srZKJpJnCM == true){srZKJpJnCM = false;}
      if(fagcgDuxIs == true){fagcgDuxIs = false;}
      if(egSKhXtyMP == true){egSKhXtyMP = false;}
      if(ZFGZBWhmgx == true){ZFGZBWhmgx = false;}
      if(cYYpPYMOnI == true){cYYpPYMOnI = false;}
      if(TsHuVLZObl == true){TsHuVLZObl = false;}
      if(uKbmmZTHbJ == true){uKbmmZTHbJ = false;}
      if(UIQLQGHbuJ == true){UIQLQGHbuJ = false;}
      if(KeJDugxKDo == true){KeJDugxKDo = false;}
      if(xSKuBRxkDo == true){xSKuBRxkDo = false;}
      if(EFmemLcweO == true){EFmemLcweO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GFZWBNLMQV
{ 
  void NLwMkyjFCA()
  { 
      bool SOPGbzsnUm = false;
      bool XKdzJumtie = false;
      bool JFrTyqCXRa = false;
      bool dWdPUaipbI = false;
      bool dKewXZdAYJ = false;
      bool ZjrArNWwHk = false;
      bool xUWsJAgOdh = false;
      bool MxRZByZuwY = false;
      bool NCzHBsdcXH = false;
      bool EmhqLInllW = false;
      bool rPVpxbSSzt = false;
      bool maAhXtVOrP = false;
      bool VEpWdYOaOr = false;
      bool JnJYgygIKY = false;
      bool aLcdTdmATQ = false;
      bool mZsWAnYzMX = false;
      bool MqDHjzQaBZ = false;
      bool NMDToKaMCz = false;
      bool lOHyEjumXr = false;
      bool ZhwmLiIVsU = false;
      string pSUUiuUQpG;
      string EJoBEtwxdb;
      string wbAyfcLpRr;
      string CFYpsESDiP;
      string XmgxiYLgAF;
      string SjtEiORWoF;
      string iezxDykzHz;
      string arONDJtCPG;
      string RdoLZRLTHe;
      string mwNcgsmitj;
      string nMZAdZUgBY;
      string TOGhnEpnXk;
      string mQrcMeekgK;
      string WKIfSEEngA;
      string xeShKYofob;
      string CzLIwWUwnz;
      string ujzqCIFaPi;
      string zCGWnIyJRn;
      string ozwEIWzAiu;
      string jIzhFNebfB;
      if(pSUUiuUQpG == nMZAdZUgBY){SOPGbzsnUm = true;}
      else if(nMZAdZUgBY == pSUUiuUQpG){rPVpxbSSzt = true;}
      if(EJoBEtwxdb == TOGhnEpnXk){XKdzJumtie = true;}
      else if(TOGhnEpnXk == EJoBEtwxdb){maAhXtVOrP = true;}
      if(wbAyfcLpRr == mQrcMeekgK){JFrTyqCXRa = true;}
      else if(mQrcMeekgK == wbAyfcLpRr){VEpWdYOaOr = true;}
      if(CFYpsESDiP == WKIfSEEngA){dWdPUaipbI = true;}
      else if(WKIfSEEngA == CFYpsESDiP){JnJYgygIKY = true;}
      if(XmgxiYLgAF == xeShKYofob){dKewXZdAYJ = true;}
      else if(xeShKYofob == XmgxiYLgAF){aLcdTdmATQ = true;}
      if(SjtEiORWoF == CzLIwWUwnz){ZjrArNWwHk = true;}
      else if(CzLIwWUwnz == SjtEiORWoF){mZsWAnYzMX = true;}
      if(iezxDykzHz == ujzqCIFaPi){xUWsJAgOdh = true;}
      else if(ujzqCIFaPi == iezxDykzHz){MqDHjzQaBZ = true;}
      if(arONDJtCPG == zCGWnIyJRn){MxRZByZuwY = true;}
      if(RdoLZRLTHe == ozwEIWzAiu){NCzHBsdcXH = true;}
      if(mwNcgsmitj == jIzhFNebfB){EmhqLInllW = true;}
      while(zCGWnIyJRn == arONDJtCPG){NMDToKaMCz = true;}
      while(ozwEIWzAiu == ozwEIWzAiu){lOHyEjumXr = true;}
      while(jIzhFNebfB == jIzhFNebfB){ZhwmLiIVsU = true;}
      if(SOPGbzsnUm == true){SOPGbzsnUm = false;}
      if(XKdzJumtie == true){XKdzJumtie = false;}
      if(JFrTyqCXRa == true){JFrTyqCXRa = false;}
      if(dWdPUaipbI == true){dWdPUaipbI = false;}
      if(dKewXZdAYJ == true){dKewXZdAYJ = false;}
      if(ZjrArNWwHk == true){ZjrArNWwHk = false;}
      if(xUWsJAgOdh == true){xUWsJAgOdh = false;}
      if(MxRZByZuwY == true){MxRZByZuwY = false;}
      if(NCzHBsdcXH == true){NCzHBsdcXH = false;}
      if(EmhqLInllW == true){EmhqLInllW = false;}
      if(rPVpxbSSzt == true){rPVpxbSSzt = false;}
      if(maAhXtVOrP == true){maAhXtVOrP = false;}
      if(VEpWdYOaOr == true){VEpWdYOaOr = false;}
      if(JnJYgygIKY == true){JnJYgygIKY = false;}
      if(aLcdTdmATQ == true){aLcdTdmATQ = false;}
      if(mZsWAnYzMX == true){mZsWAnYzMX = false;}
      if(MqDHjzQaBZ == true){MqDHjzQaBZ = false;}
      if(NMDToKaMCz == true){NMDToKaMCz = false;}
      if(lOHyEjumXr == true){lOHyEjumXr = false;}
      if(ZhwmLiIVsU == true){ZhwmLiIVsU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CRYBWCHVDV
{ 
  void mcNBozwhrR()
  { 
      bool NjoVziXCli = false;
      bool GzRcYhPRfG = false;
      bool EuPwDoKPEH = false;
      bool UMKVybqIqF = false;
      bool FaFecbfmFs = false;
      bool meQABRUsSK = false;
      bool XHxeOtnuew = false;
      bool qGaaBdojSb = false;
      bool JWKLTpuJTf = false;
      bool HypggxdZQi = false;
      bool mjIICfEpzX = false;
      bool cjZqBBxkLX = false;
      bool yeayosQttD = false;
      bool zOTjnYOBIm = false;
      bool lFJuDWXzef = false;
      bool ArOrjIIJTJ = false;
      bool PKwuYNQoCb = false;
      bool mwcXlsUeuR = false;
      bool UQOODGAazf = false;
      bool PEgzWbINWo = false;
      string TLDcQBlVNn;
      string ZBKAxbnRmN;
      string xFlUAZTAdh;
      string FOodyEqgNw;
      string aVmohFHOtz;
      string YeaEGNZhcp;
      string hkqfiKMgCr;
      string kHDqlaSwmt;
      string SEGeIZnjWj;
      string eJEXOoeGGW;
      string saMBNRajRf;
      string tcthWceLXJ;
      string VbJRMbCfbx;
      string wMoPBrqEQp;
      string yERqoBOVAk;
      string JSixBQQtnl;
      string OuHUjhndge;
      string laugKRKRcL;
      string MgepnccrOj;
      string axPebDwxHG;
      if(TLDcQBlVNn == saMBNRajRf){NjoVziXCli = true;}
      else if(saMBNRajRf == TLDcQBlVNn){mjIICfEpzX = true;}
      if(ZBKAxbnRmN == tcthWceLXJ){GzRcYhPRfG = true;}
      else if(tcthWceLXJ == ZBKAxbnRmN){cjZqBBxkLX = true;}
      if(xFlUAZTAdh == VbJRMbCfbx){EuPwDoKPEH = true;}
      else if(VbJRMbCfbx == xFlUAZTAdh){yeayosQttD = true;}
      if(FOodyEqgNw == wMoPBrqEQp){UMKVybqIqF = true;}
      else if(wMoPBrqEQp == FOodyEqgNw){zOTjnYOBIm = true;}
      if(aVmohFHOtz == yERqoBOVAk){FaFecbfmFs = true;}
      else if(yERqoBOVAk == aVmohFHOtz){lFJuDWXzef = true;}
      if(YeaEGNZhcp == JSixBQQtnl){meQABRUsSK = true;}
      else if(JSixBQQtnl == YeaEGNZhcp){ArOrjIIJTJ = true;}
      if(hkqfiKMgCr == OuHUjhndge){XHxeOtnuew = true;}
      else if(OuHUjhndge == hkqfiKMgCr){PKwuYNQoCb = true;}
      if(kHDqlaSwmt == laugKRKRcL){qGaaBdojSb = true;}
      if(SEGeIZnjWj == MgepnccrOj){JWKLTpuJTf = true;}
      if(eJEXOoeGGW == axPebDwxHG){HypggxdZQi = true;}
      while(laugKRKRcL == kHDqlaSwmt){mwcXlsUeuR = true;}
      while(MgepnccrOj == MgepnccrOj){UQOODGAazf = true;}
      while(axPebDwxHG == axPebDwxHG){PEgzWbINWo = true;}
      if(NjoVziXCli == true){NjoVziXCli = false;}
      if(GzRcYhPRfG == true){GzRcYhPRfG = false;}
      if(EuPwDoKPEH == true){EuPwDoKPEH = false;}
      if(UMKVybqIqF == true){UMKVybqIqF = false;}
      if(FaFecbfmFs == true){FaFecbfmFs = false;}
      if(meQABRUsSK == true){meQABRUsSK = false;}
      if(XHxeOtnuew == true){XHxeOtnuew = false;}
      if(qGaaBdojSb == true){qGaaBdojSb = false;}
      if(JWKLTpuJTf == true){JWKLTpuJTf = false;}
      if(HypggxdZQi == true){HypggxdZQi = false;}
      if(mjIICfEpzX == true){mjIICfEpzX = false;}
      if(cjZqBBxkLX == true){cjZqBBxkLX = false;}
      if(yeayosQttD == true){yeayosQttD = false;}
      if(zOTjnYOBIm == true){zOTjnYOBIm = false;}
      if(lFJuDWXzef == true){lFJuDWXzef = false;}
      if(ArOrjIIJTJ == true){ArOrjIIJTJ = false;}
      if(PKwuYNQoCb == true){PKwuYNQoCb = false;}
      if(mwcXlsUeuR == true){mwcXlsUeuR = false;}
      if(UQOODGAazf == true){UQOODGAazf = false;}
      if(PEgzWbINWo == true){PEgzWbINWo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LRABFBHCCQ
{ 
  void blRfNwNlWc()
  { 
      bool pEonYgHRFw = false;
      bool RbNydXubly = false;
      bool qkoNHOFbJk = false;
      bool gCWEwRwkPb = false;
      bool cJGwKFUagH = false;
      bool oBNZZFOafK = false;
      bool beHUOPEJBM = false;
      bool bKLJVhdsDC = false;
      bool sdtCufowdq = false;
      bool CUFEAxClgu = false;
      bool ALYTeeoDEr = false;
      bool bVXcRxjEYi = false;
      bool ZHeKKHFHJX = false;
      bool fqLIChEZWQ = false;
      bool plrlOfxbmC = false;
      bool MxNyUrfNJX = false;
      bool ZhsgLjJOaj = false;
      bool rKgHrnPswd = false;
      bool JcTHKhcNnJ = false;
      bool BqQzqHrKZd = false;
      string IUoYHSzQKb;
      string WDesykrXMp;
      string ertwcgrjAT;
      string YwyFByKLyN;
      string RIaFlTAhLh;
      string GwanjQZrua;
      string ZOPqDZFYqz;
      string ZgZyXWQoKJ;
      string fJXRNbVJVj;
      string YSQXmDrjCL;
      string OaqMHZWbPN;
      string AkgktQpxca;
      string EuDGaHQCLU;
      string dgmzuESLKn;
      string FstHjnlecW;
      string MtGaGSXjkz;
      string IUQtiSxgpo;
      string xemoVKBuVm;
      string VkYoIjaMrb;
      string giZKekczYR;
      if(IUoYHSzQKb == OaqMHZWbPN){pEonYgHRFw = true;}
      else if(OaqMHZWbPN == IUoYHSzQKb){ALYTeeoDEr = true;}
      if(WDesykrXMp == AkgktQpxca){RbNydXubly = true;}
      else if(AkgktQpxca == WDesykrXMp){bVXcRxjEYi = true;}
      if(ertwcgrjAT == EuDGaHQCLU){qkoNHOFbJk = true;}
      else if(EuDGaHQCLU == ertwcgrjAT){ZHeKKHFHJX = true;}
      if(YwyFByKLyN == dgmzuESLKn){gCWEwRwkPb = true;}
      else if(dgmzuESLKn == YwyFByKLyN){fqLIChEZWQ = true;}
      if(RIaFlTAhLh == FstHjnlecW){cJGwKFUagH = true;}
      else if(FstHjnlecW == RIaFlTAhLh){plrlOfxbmC = true;}
      if(GwanjQZrua == MtGaGSXjkz){oBNZZFOafK = true;}
      else if(MtGaGSXjkz == GwanjQZrua){MxNyUrfNJX = true;}
      if(ZOPqDZFYqz == IUQtiSxgpo){beHUOPEJBM = true;}
      else if(IUQtiSxgpo == ZOPqDZFYqz){ZhsgLjJOaj = true;}
      if(ZgZyXWQoKJ == xemoVKBuVm){bKLJVhdsDC = true;}
      if(fJXRNbVJVj == VkYoIjaMrb){sdtCufowdq = true;}
      if(YSQXmDrjCL == giZKekczYR){CUFEAxClgu = true;}
      while(xemoVKBuVm == ZgZyXWQoKJ){rKgHrnPswd = true;}
      while(VkYoIjaMrb == VkYoIjaMrb){JcTHKhcNnJ = true;}
      while(giZKekczYR == giZKekczYR){BqQzqHrKZd = true;}
      if(pEonYgHRFw == true){pEonYgHRFw = false;}
      if(RbNydXubly == true){RbNydXubly = false;}
      if(qkoNHOFbJk == true){qkoNHOFbJk = false;}
      if(gCWEwRwkPb == true){gCWEwRwkPb = false;}
      if(cJGwKFUagH == true){cJGwKFUagH = false;}
      if(oBNZZFOafK == true){oBNZZFOafK = false;}
      if(beHUOPEJBM == true){beHUOPEJBM = false;}
      if(bKLJVhdsDC == true){bKLJVhdsDC = false;}
      if(sdtCufowdq == true){sdtCufowdq = false;}
      if(CUFEAxClgu == true){CUFEAxClgu = false;}
      if(ALYTeeoDEr == true){ALYTeeoDEr = false;}
      if(bVXcRxjEYi == true){bVXcRxjEYi = false;}
      if(ZHeKKHFHJX == true){ZHeKKHFHJX = false;}
      if(fqLIChEZWQ == true){fqLIChEZWQ = false;}
      if(plrlOfxbmC == true){plrlOfxbmC = false;}
      if(MxNyUrfNJX == true){MxNyUrfNJX = false;}
      if(ZhsgLjJOaj == true){ZhsgLjJOaj = false;}
      if(rKgHrnPswd == true){rKgHrnPswd = false;}
      if(JcTHKhcNnJ == true){JcTHKhcNnJ = false;}
      if(BqQzqHrKZd == true){BqQzqHrKZd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWPFBPDRUC
{ 
  void WWSaagmSKj()
  { 
      bool WCgaTAfUEz = false;
      bool JfGtRUFfTa = false;
      bool otrBzxhSPJ = false;
      bool LKKozZHPBC = false;
      bool xCeVgfixtw = false;
      bool tusbqbJfaV = false;
      bool SMFumyURur = false;
      bool NpeQclPVUS = false;
      bool NkXSPQQixX = false;
      bool Pbnejkxjih = false;
      bool LRCCiEQcyE = false;
      bool MmKHIgnmeW = false;
      bool hlTWblBzfr = false;
      bool ofmmHwhViK = false;
      bool AmjsKbQfWC = false;
      bool wJELzYxeaw = false;
      bool CQwGOfAXAL = false;
      bool zSDUWtCaMz = false;
      bool VVcduebbmh = false;
      bool zDulHiqcde = false;
      string eBEjNRYAaF;
      string oiLFUtRmSn;
      string XEIaGTBoQT;
      string fVjkHUOQBd;
      string wiSrTqspoT;
      string VKRuhZrcdt;
      string QjjHZSzZxA;
      string fAkoqnlQHO;
      string ZKzwyUEoCh;
      string clmHMLzLSA;
      string qSronVZcDt;
      string nbUOTFjmIE;
      string OJXPXsMdbe;
      string oZxHXHSJHb;
      string ublItAQXmG;
      string bLCNlgucRu;
      string JuAXENdNqM;
      string mafgJlXOVW;
      string cnpUDcXiVp;
      string MprMRzaNDg;
      if(eBEjNRYAaF == qSronVZcDt){WCgaTAfUEz = true;}
      else if(qSronVZcDt == eBEjNRYAaF){LRCCiEQcyE = true;}
      if(oiLFUtRmSn == nbUOTFjmIE){JfGtRUFfTa = true;}
      else if(nbUOTFjmIE == oiLFUtRmSn){MmKHIgnmeW = true;}
      if(XEIaGTBoQT == OJXPXsMdbe){otrBzxhSPJ = true;}
      else if(OJXPXsMdbe == XEIaGTBoQT){hlTWblBzfr = true;}
      if(fVjkHUOQBd == oZxHXHSJHb){LKKozZHPBC = true;}
      else if(oZxHXHSJHb == fVjkHUOQBd){ofmmHwhViK = true;}
      if(wiSrTqspoT == ublItAQXmG){xCeVgfixtw = true;}
      else if(ublItAQXmG == wiSrTqspoT){AmjsKbQfWC = true;}
      if(VKRuhZrcdt == bLCNlgucRu){tusbqbJfaV = true;}
      else if(bLCNlgucRu == VKRuhZrcdt){wJELzYxeaw = true;}
      if(QjjHZSzZxA == JuAXENdNqM){SMFumyURur = true;}
      else if(JuAXENdNqM == QjjHZSzZxA){CQwGOfAXAL = true;}
      if(fAkoqnlQHO == mafgJlXOVW){NpeQclPVUS = true;}
      if(ZKzwyUEoCh == cnpUDcXiVp){NkXSPQQixX = true;}
      if(clmHMLzLSA == MprMRzaNDg){Pbnejkxjih = true;}
      while(mafgJlXOVW == fAkoqnlQHO){zSDUWtCaMz = true;}
      while(cnpUDcXiVp == cnpUDcXiVp){VVcduebbmh = true;}
      while(MprMRzaNDg == MprMRzaNDg){zDulHiqcde = true;}
      if(WCgaTAfUEz == true){WCgaTAfUEz = false;}
      if(JfGtRUFfTa == true){JfGtRUFfTa = false;}
      if(otrBzxhSPJ == true){otrBzxhSPJ = false;}
      if(LKKozZHPBC == true){LKKozZHPBC = false;}
      if(xCeVgfixtw == true){xCeVgfixtw = false;}
      if(tusbqbJfaV == true){tusbqbJfaV = false;}
      if(SMFumyURur == true){SMFumyURur = false;}
      if(NpeQclPVUS == true){NpeQclPVUS = false;}
      if(NkXSPQQixX == true){NkXSPQQixX = false;}
      if(Pbnejkxjih == true){Pbnejkxjih = false;}
      if(LRCCiEQcyE == true){LRCCiEQcyE = false;}
      if(MmKHIgnmeW == true){MmKHIgnmeW = false;}
      if(hlTWblBzfr == true){hlTWblBzfr = false;}
      if(ofmmHwhViK == true){ofmmHwhViK = false;}
      if(AmjsKbQfWC == true){AmjsKbQfWC = false;}
      if(wJELzYxeaw == true){wJELzYxeaw = false;}
      if(CQwGOfAXAL == true){CQwGOfAXAL = false;}
      if(zSDUWtCaMz == true){zSDUWtCaMz = false;}
      if(VVcduebbmh == true){VVcduebbmh = false;}
      if(zDulHiqcde == true){zDulHiqcde = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LHEVRHETGC
{ 
  void HUGYMqaqDO()
  { 
      bool ObEaxXwUyE = false;
      bool WZQSDBWLqe = false;
      bool AihZNJYugE = false;
      bool osbhSMFVow = false;
      bool qBkeopLWmR = false;
      bool HdfowetdNm = false;
      bool yBnsPdxizq = false;
      bool wAWumzyCkX = false;
      bool xCHOwLMmkn = false;
      bool RaIBxpNqPK = false;
      bool rbXwVGGjBx = false;
      bool gqsoowsYxD = false;
      bool QKxLYUqVxx = false;
      bool kGmZeUeLsp = false;
      bool EbknGagTLB = false;
      bool wotLsgeLWA = false;
      bool PkmELZESJT = false;
      bool RgeGznZJFy = false;
      bool nXJuAwMafy = false;
      bool pSorZSofbf = false;
      string fCsAgZJWIR;
      string LSIZDtjIpC;
      string DVqpZTuytj;
      string QnRssZhEjZ;
      string DeZOWmXasl;
      string ruiQOKKDZN;
      string eKbXBWAOgd;
      string MfYPyYucSm;
      string wTFIrUFBdi;
      string OddWtrCCMA;
      string mItOZMWSRp;
      string PhjmRLFTfg;
      string QzkyOhBCUG;
      string WrPSAmYphe;
      string ylinSgsqEi;
      string lhVfimWwAq;
      string LTxLSWRRld;
      string lOlBhdQxeh;
      string nJxlTnVijM;
      string PcppTdoWUw;
      if(fCsAgZJWIR == mItOZMWSRp){ObEaxXwUyE = true;}
      else if(mItOZMWSRp == fCsAgZJWIR){rbXwVGGjBx = true;}
      if(LSIZDtjIpC == PhjmRLFTfg){WZQSDBWLqe = true;}
      else if(PhjmRLFTfg == LSIZDtjIpC){gqsoowsYxD = true;}
      if(DVqpZTuytj == QzkyOhBCUG){AihZNJYugE = true;}
      else if(QzkyOhBCUG == DVqpZTuytj){QKxLYUqVxx = true;}
      if(QnRssZhEjZ == WrPSAmYphe){osbhSMFVow = true;}
      else if(WrPSAmYphe == QnRssZhEjZ){kGmZeUeLsp = true;}
      if(DeZOWmXasl == ylinSgsqEi){qBkeopLWmR = true;}
      else if(ylinSgsqEi == DeZOWmXasl){EbknGagTLB = true;}
      if(ruiQOKKDZN == lhVfimWwAq){HdfowetdNm = true;}
      else if(lhVfimWwAq == ruiQOKKDZN){wotLsgeLWA = true;}
      if(eKbXBWAOgd == LTxLSWRRld){yBnsPdxizq = true;}
      else if(LTxLSWRRld == eKbXBWAOgd){PkmELZESJT = true;}
      if(MfYPyYucSm == lOlBhdQxeh){wAWumzyCkX = true;}
      if(wTFIrUFBdi == nJxlTnVijM){xCHOwLMmkn = true;}
      if(OddWtrCCMA == PcppTdoWUw){RaIBxpNqPK = true;}
      while(lOlBhdQxeh == MfYPyYucSm){RgeGznZJFy = true;}
      while(nJxlTnVijM == nJxlTnVijM){nXJuAwMafy = true;}
      while(PcppTdoWUw == PcppTdoWUw){pSorZSofbf = true;}
      if(ObEaxXwUyE == true){ObEaxXwUyE = false;}
      if(WZQSDBWLqe == true){WZQSDBWLqe = false;}
      if(AihZNJYugE == true){AihZNJYugE = false;}
      if(osbhSMFVow == true){osbhSMFVow = false;}
      if(qBkeopLWmR == true){qBkeopLWmR = false;}
      if(HdfowetdNm == true){HdfowetdNm = false;}
      if(yBnsPdxizq == true){yBnsPdxizq = false;}
      if(wAWumzyCkX == true){wAWumzyCkX = false;}
      if(xCHOwLMmkn == true){xCHOwLMmkn = false;}
      if(RaIBxpNqPK == true){RaIBxpNqPK = false;}
      if(rbXwVGGjBx == true){rbXwVGGjBx = false;}
      if(gqsoowsYxD == true){gqsoowsYxD = false;}
      if(QKxLYUqVxx == true){QKxLYUqVxx = false;}
      if(kGmZeUeLsp == true){kGmZeUeLsp = false;}
      if(EbknGagTLB == true){EbknGagTLB = false;}
      if(wotLsgeLWA == true){wotLsgeLWA = false;}
      if(PkmELZESJT == true){PkmELZESJT = false;}
      if(RgeGznZJFy == true){RgeGznZJFy = false;}
      if(nXJuAwMafy == true){nXJuAwMafy = false;}
      if(pSorZSofbf == true){pSorZSofbf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DTTNLTEZIS
{ 
  void YIOdAkCRTa()
  { 
      bool ziTfDrsBAe = false;
      bool eASAJCOhiA = false;
      bool hkSMjuOPZz = false;
      bool HIHJInBYWT = false;
      bool eUxpayEkGo = false;
      bool hKrxcOPGwI = false;
      bool dcbBXVrIrU = false;
      bool BoKPVNmblk = false;
      bool qcJkQxQKgs = false;
      bool YucOpBrwSF = false;
      bool FuskmrzbaO = false;
      bool amUKRASpja = false;
      bool EhbywGMwZU = false;
      bool UqJgeuiYxX = false;
      bool yniRSkZRwo = false;
      bool hCLrAXStog = false;
      bool fCCGtjdmeV = false;
      bool RtsMbPyJfK = false;
      bool fuzjlSeQgH = false;
      bool cojQrulcXi = false;
      string DLxPXyZFrk;
      string RjmfntqFxR;
      string zUfYjtqmGN;
      string RHJPpolHgE;
      string ZAebqtGLuj;
      string QMzpVifXec;
      string GlzdSJZWpy;
      string IjYsqzpDhp;
      string neqWwFHTtH;
      string JNbDxmBAJg;
      string UiVxafnFyW;
      string rbponbubhN;
      string CFciotIUwD;
      string xotAVFJtwP;
      string QCVWOgXmPV;
      string rZSweOGmHf;
      string XTJtYDhoTi;
      string RAfRwAjFTH;
      string WUFaLXVxVG;
      string zWlPrxrayK;
      if(DLxPXyZFrk == UiVxafnFyW){ziTfDrsBAe = true;}
      else if(UiVxafnFyW == DLxPXyZFrk){FuskmrzbaO = true;}
      if(RjmfntqFxR == rbponbubhN){eASAJCOhiA = true;}
      else if(rbponbubhN == RjmfntqFxR){amUKRASpja = true;}
      if(zUfYjtqmGN == CFciotIUwD){hkSMjuOPZz = true;}
      else if(CFciotIUwD == zUfYjtqmGN){EhbywGMwZU = true;}
      if(RHJPpolHgE == xotAVFJtwP){HIHJInBYWT = true;}
      else if(xotAVFJtwP == RHJPpolHgE){UqJgeuiYxX = true;}
      if(ZAebqtGLuj == QCVWOgXmPV){eUxpayEkGo = true;}
      else if(QCVWOgXmPV == ZAebqtGLuj){yniRSkZRwo = true;}
      if(QMzpVifXec == rZSweOGmHf){hKrxcOPGwI = true;}
      else if(rZSweOGmHf == QMzpVifXec){hCLrAXStog = true;}
      if(GlzdSJZWpy == XTJtYDhoTi){dcbBXVrIrU = true;}
      else if(XTJtYDhoTi == GlzdSJZWpy){fCCGtjdmeV = true;}
      if(IjYsqzpDhp == RAfRwAjFTH){BoKPVNmblk = true;}
      if(neqWwFHTtH == WUFaLXVxVG){qcJkQxQKgs = true;}
      if(JNbDxmBAJg == zWlPrxrayK){YucOpBrwSF = true;}
      while(RAfRwAjFTH == IjYsqzpDhp){RtsMbPyJfK = true;}
      while(WUFaLXVxVG == WUFaLXVxVG){fuzjlSeQgH = true;}
      while(zWlPrxrayK == zWlPrxrayK){cojQrulcXi = true;}
      if(ziTfDrsBAe == true){ziTfDrsBAe = false;}
      if(eASAJCOhiA == true){eASAJCOhiA = false;}
      if(hkSMjuOPZz == true){hkSMjuOPZz = false;}
      if(HIHJInBYWT == true){HIHJInBYWT = false;}
      if(eUxpayEkGo == true){eUxpayEkGo = false;}
      if(hKrxcOPGwI == true){hKrxcOPGwI = false;}
      if(dcbBXVrIrU == true){dcbBXVrIrU = false;}
      if(BoKPVNmblk == true){BoKPVNmblk = false;}
      if(qcJkQxQKgs == true){qcJkQxQKgs = false;}
      if(YucOpBrwSF == true){YucOpBrwSF = false;}
      if(FuskmrzbaO == true){FuskmrzbaO = false;}
      if(amUKRASpja == true){amUKRASpja = false;}
      if(EhbywGMwZU == true){EhbywGMwZU = false;}
      if(UqJgeuiYxX == true){UqJgeuiYxX = false;}
      if(yniRSkZRwo == true){yniRSkZRwo = false;}
      if(hCLrAXStog == true){hCLrAXStog = false;}
      if(fCCGtjdmeV == true){fCCGtjdmeV = false;}
      if(RtsMbPyJfK == true){RtsMbPyJfK = false;}
      if(fuzjlSeQgH == true){fuzjlSeQgH = false;}
      if(cojQrulcXi == true){cojQrulcXi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VMASFRBEUF
{ 
  void iasUoRlPam()
  { 
      bool NBizpwQnAg = false;
      bool llkUFtyFgU = false;
      bool dlbOOqfuwn = false;
      bool jlJySidzMD = false;
      bool DbuLxDkKQN = false;
      bool rTfVybZUjy = false;
      bool PVrLxAbmBV = false;
      bool QyrdRCpPRK = false;
      bool GUdiwPFnzq = false;
      bool JJPNmhjjOw = false;
      bool byItxsaCDw = false;
      bool kJCYrtqJOg = false;
      bool tnmKMGiepj = false;
      bool RGBUiHLilD = false;
      bool nDjDFzGpUs = false;
      bool paUgCmKyhp = false;
      bool KwMTddHgpj = false;
      bool iHWLrqEjEM = false;
      bool ArJwsqlUSu = false;
      bool wNBwsrpPYa = false;
      string rPyojiedHg;
      string COgiZWcszQ;
      string SRfgQLoZnV;
      string ZQjeEpqcHs;
      string GCxFRMTrNd;
      string DlUzHZjRYX;
      string sFokGleCei;
      string fzlGJPUZOD;
      string rwLKSnujWd;
      string GYDiABNLyf;
      string gQNexDzOoq;
      string FJCUfwseSS;
      string pteAcGuCGI;
      string CJbhWaigMO;
      string ngueYwVhDD;
      string IhrepllMBp;
      string HxHgouhUyE;
      string NLRDeIzzbg;
      string kNyCzTQwrj;
      string oVfWHpYNpc;
      if(rPyojiedHg == gQNexDzOoq){NBizpwQnAg = true;}
      else if(gQNexDzOoq == rPyojiedHg){byItxsaCDw = true;}
      if(COgiZWcszQ == FJCUfwseSS){llkUFtyFgU = true;}
      else if(FJCUfwseSS == COgiZWcszQ){kJCYrtqJOg = true;}
      if(SRfgQLoZnV == pteAcGuCGI){dlbOOqfuwn = true;}
      else if(pteAcGuCGI == SRfgQLoZnV){tnmKMGiepj = true;}
      if(ZQjeEpqcHs == CJbhWaigMO){jlJySidzMD = true;}
      else if(CJbhWaigMO == ZQjeEpqcHs){RGBUiHLilD = true;}
      if(GCxFRMTrNd == ngueYwVhDD){DbuLxDkKQN = true;}
      else if(ngueYwVhDD == GCxFRMTrNd){nDjDFzGpUs = true;}
      if(DlUzHZjRYX == IhrepllMBp){rTfVybZUjy = true;}
      else if(IhrepllMBp == DlUzHZjRYX){paUgCmKyhp = true;}
      if(sFokGleCei == HxHgouhUyE){PVrLxAbmBV = true;}
      else if(HxHgouhUyE == sFokGleCei){KwMTddHgpj = true;}
      if(fzlGJPUZOD == NLRDeIzzbg){QyrdRCpPRK = true;}
      if(rwLKSnujWd == kNyCzTQwrj){GUdiwPFnzq = true;}
      if(GYDiABNLyf == oVfWHpYNpc){JJPNmhjjOw = true;}
      while(NLRDeIzzbg == fzlGJPUZOD){iHWLrqEjEM = true;}
      while(kNyCzTQwrj == kNyCzTQwrj){ArJwsqlUSu = true;}
      while(oVfWHpYNpc == oVfWHpYNpc){wNBwsrpPYa = true;}
      if(NBizpwQnAg == true){NBizpwQnAg = false;}
      if(llkUFtyFgU == true){llkUFtyFgU = false;}
      if(dlbOOqfuwn == true){dlbOOqfuwn = false;}
      if(jlJySidzMD == true){jlJySidzMD = false;}
      if(DbuLxDkKQN == true){DbuLxDkKQN = false;}
      if(rTfVybZUjy == true){rTfVybZUjy = false;}
      if(PVrLxAbmBV == true){PVrLxAbmBV = false;}
      if(QyrdRCpPRK == true){QyrdRCpPRK = false;}
      if(GUdiwPFnzq == true){GUdiwPFnzq = false;}
      if(JJPNmhjjOw == true){JJPNmhjjOw = false;}
      if(byItxsaCDw == true){byItxsaCDw = false;}
      if(kJCYrtqJOg == true){kJCYrtqJOg = false;}
      if(tnmKMGiepj == true){tnmKMGiepj = false;}
      if(RGBUiHLilD == true){RGBUiHLilD = false;}
      if(nDjDFzGpUs == true){nDjDFzGpUs = false;}
      if(paUgCmKyhp == true){paUgCmKyhp = false;}
      if(KwMTddHgpj == true){KwMTddHgpj = false;}
      if(iHWLrqEjEM == true){iHWLrqEjEM = false;}
      if(ArJwsqlUSu == true){ArJwsqlUSu = false;}
      if(wNBwsrpPYa == true){wNBwsrpPYa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RXIWQVSGCK
{ 
  void ugKOMKWRcJ()
  { 
      bool GRyEtjqUQg = false;
      bool XMZjZbuHSY = false;
      bool csOucKNMIm = false;
      bool VxDEupmzfF = false;
      bool YinalMjiQS = false;
      bool mTyYzMCDai = false;
      bool VdMcKaJUnj = false;
      bool nubNzsEnJQ = false;
      bool aduozBydFh = false;
      bool njXwiuVLPL = false;
      bool COugerrjZG = false;
      bool HOtKIriXcJ = false;
      bool bePFuEWeeE = false;
      bool XsXxNMiNKH = false;
      bool INEzaYpNnq = false;
      bool LyiGiWyoka = false;
      bool UNFUhOpwwu = false;
      bool JUNUANaQeW = false;
      bool NJpmrYKROp = false;
      bool NscimuIiQL = false;
      string xttDOqaahF;
      string wrIJViYrGx;
      string AXUIddiqmJ;
      string JDNctTleiL;
      string mNJlgFjPte;
      string xSTYmYYlZk;
      string HimXusdeOB;
      string xtItJlOiaX;
      string sTxILqjooV;
      string uzEyEDZkqn;
      string bEBrgDJYOB;
      string KpKBqnleME;
      string IoprGyoKpG;
      string LcqmwnSEaI;
      string hKZnKEoDGP;
      string QuYmelOIki;
      string NyhIohyWEC;
      string VgEDVyOBhB;
      string IlDaoQEEHJ;
      string ZKTquibRyc;
      if(xttDOqaahF == bEBrgDJYOB){GRyEtjqUQg = true;}
      else if(bEBrgDJYOB == xttDOqaahF){COugerrjZG = true;}
      if(wrIJViYrGx == KpKBqnleME){XMZjZbuHSY = true;}
      else if(KpKBqnleME == wrIJViYrGx){HOtKIriXcJ = true;}
      if(AXUIddiqmJ == IoprGyoKpG){csOucKNMIm = true;}
      else if(IoprGyoKpG == AXUIddiqmJ){bePFuEWeeE = true;}
      if(JDNctTleiL == LcqmwnSEaI){VxDEupmzfF = true;}
      else if(LcqmwnSEaI == JDNctTleiL){XsXxNMiNKH = true;}
      if(mNJlgFjPte == hKZnKEoDGP){YinalMjiQS = true;}
      else if(hKZnKEoDGP == mNJlgFjPte){INEzaYpNnq = true;}
      if(xSTYmYYlZk == QuYmelOIki){mTyYzMCDai = true;}
      else if(QuYmelOIki == xSTYmYYlZk){LyiGiWyoka = true;}
      if(HimXusdeOB == NyhIohyWEC){VdMcKaJUnj = true;}
      else if(NyhIohyWEC == HimXusdeOB){UNFUhOpwwu = true;}
      if(xtItJlOiaX == VgEDVyOBhB){nubNzsEnJQ = true;}
      if(sTxILqjooV == IlDaoQEEHJ){aduozBydFh = true;}
      if(uzEyEDZkqn == ZKTquibRyc){njXwiuVLPL = true;}
      while(VgEDVyOBhB == xtItJlOiaX){JUNUANaQeW = true;}
      while(IlDaoQEEHJ == IlDaoQEEHJ){NJpmrYKROp = true;}
      while(ZKTquibRyc == ZKTquibRyc){NscimuIiQL = true;}
      if(GRyEtjqUQg == true){GRyEtjqUQg = false;}
      if(XMZjZbuHSY == true){XMZjZbuHSY = false;}
      if(csOucKNMIm == true){csOucKNMIm = false;}
      if(VxDEupmzfF == true){VxDEupmzfF = false;}
      if(YinalMjiQS == true){YinalMjiQS = false;}
      if(mTyYzMCDai == true){mTyYzMCDai = false;}
      if(VdMcKaJUnj == true){VdMcKaJUnj = false;}
      if(nubNzsEnJQ == true){nubNzsEnJQ = false;}
      if(aduozBydFh == true){aduozBydFh = false;}
      if(njXwiuVLPL == true){njXwiuVLPL = false;}
      if(COugerrjZG == true){COugerrjZG = false;}
      if(HOtKIriXcJ == true){HOtKIriXcJ = false;}
      if(bePFuEWeeE == true){bePFuEWeeE = false;}
      if(XsXxNMiNKH == true){XsXxNMiNKH = false;}
      if(INEzaYpNnq == true){INEzaYpNnq = false;}
      if(LyiGiWyoka == true){LyiGiWyoka = false;}
      if(UNFUhOpwwu == true){UNFUhOpwwu = false;}
      if(JUNUANaQeW == true){JUNUANaQeW = false;}
      if(NJpmrYKROp == true){NJpmrYKROp = false;}
      if(NscimuIiQL == true){NscimuIiQL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XBGNPIAKVK
{ 
  void wEWAejJrxM()
  { 
      bool oVsRRGrwcE = false;
      bool oNQKBOgYhe = false;
      bool usorBTZZlF = false;
      bool AgqNHiCJah = false;
      bool uqWEUTRWqu = false;
      bool FMTEyugBQy = false;
      bool fSJXEHVDDR = false;
      bool MXxAjEWjWh = false;
      bool CDhpzmNlOL = false;
      bool CAscBbgyAM = false;
      bool xOSYihPSUt = false;
      bool XwdhucjTXQ = false;
      bool siorPMdTzH = false;
      bool XYjKjnjJHR = false;
      bool XuRTmGVKhX = false;
      bool qNZiSOYaJV = false;
      bool DuTNWzLTyH = false;
      bool saLFryRUEJ = false;
      bool pTlaPJyAqV = false;
      bool OIzlObaDxm = false;
      string FFUAsfLFlR;
      string kCIeTsxbzE;
      string CwKnDBEmGu;
      string wKtLBrzbwG;
      string laDeHoNmMZ;
      string XQZsrItfxq;
      string aYypUZIwda;
      string sVfsRbsfgN;
      string mQafXfjASr;
      string xTdEeNcMJg;
      string fRJkgBjgaQ;
      string POyiEJyRSn;
      string pIckdZqbOE;
      string ygVAhVHozV;
      string wDYBchUuAU;
      string PKsVqXnYGG;
      string KIRWSisyBh;
      string CIRxrliaHw;
      string FuasnmmzJJ;
      string gihrKmkBit;
      if(FFUAsfLFlR == fRJkgBjgaQ){oVsRRGrwcE = true;}
      else if(fRJkgBjgaQ == FFUAsfLFlR){xOSYihPSUt = true;}
      if(kCIeTsxbzE == POyiEJyRSn){oNQKBOgYhe = true;}
      else if(POyiEJyRSn == kCIeTsxbzE){XwdhucjTXQ = true;}
      if(CwKnDBEmGu == pIckdZqbOE){usorBTZZlF = true;}
      else if(pIckdZqbOE == CwKnDBEmGu){siorPMdTzH = true;}
      if(wKtLBrzbwG == ygVAhVHozV){AgqNHiCJah = true;}
      else if(ygVAhVHozV == wKtLBrzbwG){XYjKjnjJHR = true;}
      if(laDeHoNmMZ == wDYBchUuAU){uqWEUTRWqu = true;}
      else if(wDYBchUuAU == laDeHoNmMZ){XuRTmGVKhX = true;}
      if(XQZsrItfxq == PKsVqXnYGG){FMTEyugBQy = true;}
      else if(PKsVqXnYGG == XQZsrItfxq){qNZiSOYaJV = true;}
      if(aYypUZIwda == KIRWSisyBh){fSJXEHVDDR = true;}
      else if(KIRWSisyBh == aYypUZIwda){DuTNWzLTyH = true;}
      if(sVfsRbsfgN == CIRxrliaHw){MXxAjEWjWh = true;}
      if(mQafXfjASr == FuasnmmzJJ){CDhpzmNlOL = true;}
      if(xTdEeNcMJg == gihrKmkBit){CAscBbgyAM = true;}
      while(CIRxrliaHw == sVfsRbsfgN){saLFryRUEJ = true;}
      while(FuasnmmzJJ == FuasnmmzJJ){pTlaPJyAqV = true;}
      while(gihrKmkBit == gihrKmkBit){OIzlObaDxm = true;}
      if(oVsRRGrwcE == true){oVsRRGrwcE = false;}
      if(oNQKBOgYhe == true){oNQKBOgYhe = false;}
      if(usorBTZZlF == true){usorBTZZlF = false;}
      if(AgqNHiCJah == true){AgqNHiCJah = false;}
      if(uqWEUTRWqu == true){uqWEUTRWqu = false;}
      if(FMTEyugBQy == true){FMTEyugBQy = false;}
      if(fSJXEHVDDR == true){fSJXEHVDDR = false;}
      if(MXxAjEWjWh == true){MXxAjEWjWh = false;}
      if(CDhpzmNlOL == true){CDhpzmNlOL = false;}
      if(CAscBbgyAM == true){CAscBbgyAM = false;}
      if(xOSYihPSUt == true){xOSYihPSUt = false;}
      if(XwdhucjTXQ == true){XwdhucjTXQ = false;}
      if(siorPMdTzH == true){siorPMdTzH = false;}
      if(XYjKjnjJHR == true){XYjKjnjJHR = false;}
      if(XuRTmGVKhX == true){XuRTmGVKhX = false;}
      if(qNZiSOYaJV == true){qNZiSOYaJV = false;}
      if(DuTNWzLTyH == true){DuTNWzLTyH = false;}
      if(saLFryRUEJ == true){saLFryRUEJ = false;}
      if(pTlaPJyAqV == true){pTlaPJyAqV = false;}
      if(OIzlObaDxm == true){OIzlObaDxm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TEBAGEMBGB
{ 
  void mPLRRtWjSy()
  { 
      bool CAEHtOGNEH = false;
      bool UicJVAHrJL = false;
      bool zZbXDFJiDM = false;
      bool oiIaHggEqP = false;
      bool qjZGhSjDNP = false;
      bool VoqYobXgEo = false;
      bool FXKqSlaBCo = false;
      bool SCAtTOAVoj = false;
      bool UFUnpzrile = false;
      bool IzABJSZhmw = false;
      bool rhBXwSnwFZ = false;
      bool aCrTTADWBS = false;
      bool tqPWfSCzkB = false;
      bool oShrrmDwqX = false;
      bool LudLDGHfgJ = false;
      bool PDgUCASerc = false;
      bool QnLDkITzbg = false;
      bool wGecGyMDSZ = false;
      bool LWRaklkNpq = false;
      bool TYENHWiZat = false;
      string ZMUxGTPySy;
      string VTZpUzMGfK;
      string yNakeZCyfq;
      string PzCLaUFgfz;
      string FweShteGiT;
      string jVKIjMkiSg;
      string RRRbiWROOz;
      string sfZgECiICj;
      string uuOMGtosbO;
      string iWNzhndCjL;
      string cPqiZEucEg;
      string ccghkVCFUo;
      string hXmAPWRayQ;
      string XfYqHeDfmC;
      string yLotkGofNM;
      string kYgtdEcqSD;
      string lUdnJxEoaF;
      string RVRSpVisOJ;
      string glMleyydND;
      string CMMiPdgAjn;
      if(ZMUxGTPySy == cPqiZEucEg){CAEHtOGNEH = true;}
      else if(cPqiZEucEg == ZMUxGTPySy){rhBXwSnwFZ = true;}
      if(VTZpUzMGfK == ccghkVCFUo){UicJVAHrJL = true;}
      else if(ccghkVCFUo == VTZpUzMGfK){aCrTTADWBS = true;}
      if(yNakeZCyfq == hXmAPWRayQ){zZbXDFJiDM = true;}
      else if(hXmAPWRayQ == yNakeZCyfq){tqPWfSCzkB = true;}
      if(PzCLaUFgfz == XfYqHeDfmC){oiIaHggEqP = true;}
      else if(XfYqHeDfmC == PzCLaUFgfz){oShrrmDwqX = true;}
      if(FweShteGiT == yLotkGofNM){qjZGhSjDNP = true;}
      else if(yLotkGofNM == FweShteGiT){LudLDGHfgJ = true;}
      if(jVKIjMkiSg == kYgtdEcqSD){VoqYobXgEo = true;}
      else if(kYgtdEcqSD == jVKIjMkiSg){PDgUCASerc = true;}
      if(RRRbiWROOz == lUdnJxEoaF){FXKqSlaBCo = true;}
      else if(lUdnJxEoaF == RRRbiWROOz){QnLDkITzbg = true;}
      if(sfZgECiICj == RVRSpVisOJ){SCAtTOAVoj = true;}
      if(uuOMGtosbO == glMleyydND){UFUnpzrile = true;}
      if(iWNzhndCjL == CMMiPdgAjn){IzABJSZhmw = true;}
      while(RVRSpVisOJ == sfZgECiICj){wGecGyMDSZ = true;}
      while(glMleyydND == glMleyydND){LWRaklkNpq = true;}
      while(CMMiPdgAjn == CMMiPdgAjn){TYENHWiZat = true;}
      if(CAEHtOGNEH == true){CAEHtOGNEH = false;}
      if(UicJVAHrJL == true){UicJVAHrJL = false;}
      if(zZbXDFJiDM == true){zZbXDFJiDM = false;}
      if(oiIaHggEqP == true){oiIaHggEqP = false;}
      if(qjZGhSjDNP == true){qjZGhSjDNP = false;}
      if(VoqYobXgEo == true){VoqYobXgEo = false;}
      if(FXKqSlaBCo == true){FXKqSlaBCo = false;}
      if(SCAtTOAVoj == true){SCAtTOAVoj = false;}
      if(UFUnpzrile == true){UFUnpzrile = false;}
      if(IzABJSZhmw == true){IzABJSZhmw = false;}
      if(rhBXwSnwFZ == true){rhBXwSnwFZ = false;}
      if(aCrTTADWBS == true){aCrTTADWBS = false;}
      if(tqPWfSCzkB == true){tqPWfSCzkB = false;}
      if(oShrrmDwqX == true){oShrrmDwqX = false;}
      if(LudLDGHfgJ == true){LudLDGHfgJ = false;}
      if(PDgUCASerc == true){PDgUCASerc = false;}
      if(QnLDkITzbg == true){QnLDkITzbg = false;}
      if(wGecGyMDSZ == true){wGecGyMDSZ = false;}
      if(LWRaklkNpq == true){LWRaklkNpq = false;}
      if(TYENHWiZat == true){TYENHWiZat = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBEEKAYOUL
{ 
  void sKhHZSnfFb()
  { 
      bool FqIexiusUa = false;
      bool qHeqRdnKQI = false;
      bool ACTpOLLfeP = false;
      bool gGpLiKzahZ = false;
      bool pTbflHEtyn = false;
      bool kIEMaDXSQk = false;
      bool XPNEsjRSHG = false;
      bool eMbqRgZmDH = false;
      bool GRgqeXBcke = false;
      bool mfKwCaFWmB = false;
      bool oklqIXgNtt = false;
      bool djPJeGhWZU = false;
      bool iohcTzCeoq = false;
      bool aCzBRVepiG = false;
      bool qmhpBCPARw = false;
      bool siwRSACJXI = false;
      bool UBYDTajNqJ = false;
      bool armTduGraQ = false;
      bool iCMsxqFhiR = false;
      bool SVRZkoOeWZ = false;
      string oSFThebGHT;
      string ZtaOxsbAyk;
      string XWkfOqiVEc;
      string duLKarzyNl;
      string AYYJOZLjeg;
      string AxZAWRgZEq;
      string wFCepdiQmE;
      string sdlMjzyaRn;
      string ezqWbfVKnJ;
      string KZsVouVtTj;
      string quwZmWLMPX;
      string SGIQMxOeCJ;
      string IXbdsTjPWo;
      string cEGhxiCQiE;
      string UIuQpERcJr;
      string fqqJaTTSfT;
      string luoZtOzZTd;
      string uxuxoAbLmo;
      string CHGeIlNxGd;
      string OjkPSYSVVb;
      if(oSFThebGHT == quwZmWLMPX){FqIexiusUa = true;}
      else if(quwZmWLMPX == oSFThebGHT){oklqIXgNtt = true;}
      if(ZtaOxsbAyk == SGIQMxOeCJ){qHeqRdnKQI = true;}
      else if(SGIQMxOeCJ == ZtaOxsbAyk){djPJeGhWZU = true;}
      if(XWkfOqiVEc == IXbdsTjPWo){ACTpOLLfeP = true;}
      else if(IXbdsTjPWo == XWkfOqiVEc){iohcTzCeoq = true;}
      if(duLKarzyNl == cEGhxiCQiE){gGpLiKzahZ = true;}
      else if(cEGhxiCQiE == duLKarzyNl){aCzBRVepiG = true;}
      if(AYYJOZLjeg == UIuQpERcJr){pTbflHEtyn = true;}
      else if(UIuQpERcJr == AYYJOZLjeg){qmhpBCPARw = true;}
      if(AxZAWRgZEq == fqqJaTTSfT){kIEMaDXSQk = true;}
      else if(fqqJaTTSfT == AxZAWRgZEq){siwRSACJXI = true;}
      if(wFCepdiQmE == luoZtOzZTd){XPNEsjRSHG = true;}
      else if(luoZtOzZTd == wFCepdiQmE){UBYDTajNqJ = true;}
      if(sdlMjzyaRn == uxuxoAbLmo){eMbqRgZmDH = true;}
      if(ezqWbfVKnJ == CHGeIlNxGd){GRgqeXBcke = true;}
      if(KZsVouVtTj == OjkPSYSVVb){mfKwCaFWmB = true;}
      while(uxuxoAbLmo == sdlMjzyaRn){armTduGraQ = true;}
      while(CHGeIlNxGd == CHGeIlNxGd){iCMsxqFhiR = true;}
      while(OjkPSYSVVb == OjkPSYSVVb){SVRZkoOeWZ = true;}
      if(FqIexiusUa == true){FqIexiusUa = false;}
      if(qHeqRdnKQI == true){qHeqRdnKQI = false;}
      if(ACTpOLLfeP == true){ACTpOLLfeP = false;}
      if(gGpLiKzahZ == true){gGpLiKzahZ = false;}
      if(pTbflHEtyn == true){pTbflHEtyn = false;}
      if(kIEMaDXSQk == true){kIEMaDXSQk = false;}
      if(XPNEsjRSHG == true){XPNEsjRSHG = false;}
      if(eMbqRgZmDH == true){eMbqRgZmDH = false;}
      if(GRgqeXBcke == true){GRgqeXBcke = false;}
      if(mfKwCaFWmB == true){mfKwCaFWmB = false;}
      if(oklqIXgNtt == true){oklqIXgNtt = false;}
      if(djPJeGhWZU == true){djPJeGhWZU = false;}
      if(iohcTzCeoq == true){iohcTzCeoq = false;}
      if(aCzBRVepiG == true){aCzBRVepiG = false;}
      if(qmhpBCPARw == true){qmhpBCPARw = false;}
      if(siwRSACJXI == true){siwRSACJXI = false;}
      if(UBYDTajNqJ == true){UBYDTajNqJ = false;}
      if(armTduGraQ == true){armTduGraQ = false;}
      if(iCMsxqFhiR == true){iCMsxqFhiR = false;}
      if(SVRZkoOeWZ == true){SVRZkoOeWZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WNSORLIOGH
{ 
  void thuRUCTXYp()
  { 
      bool WcFpSOOqdB = false;
      bool eYLhftVlKi = false;
      bool OHYSJcjzGM = false;
      bool LlJZrosdRP = false;
      bool fOTyNKJKNp = false;
      bool SQGNWPEmgp = false;
      bool dPkQprPlop = false;
      bool BqTuDzmZEy = false;
      bool SZkQstewCc = false;
      bool kFxbkQdDIU = false;
      bool uXUWnaxKKX = false;
      bool cehhWDdTWw = false;
      bool MSjMFutqKl = false;
      bool ViRjDuENbS = false;
      bool xUkezFXPEg = false;
      bool mJfMHbmIRr = false;
      bool gFAXBsNxdb = false;
      bool yPrEyrhEMz = false;
      bool XdlczLCFba = false;
      bool HwwikqTNcG = false;
      string OqSBmfetUk;
      string WmkGpPcryx;
      string sIQIssFctM;
      string akKqXlBLpk;
      string OtNYoWKWtg;
      string ZymrfGaJIt;
      string aCzIKlctiD;
      string NRBNhyurTV;
      string hhhMlbyRKR;
      string LrCwKMuFND;
      string tQnqTIwYKh;
      string KiplLrUlVh;
      string mKjRrUOFCV;
      string DpdQbRsqsd;
      string fYGbGbCQjR;
      string rIifPigWyy;
      string sqWoeUFYKt;
      string zcsqCNEHKP;
      string SyUkduGxAr;
      string jVrtkoCRxk;
      if(OqSBmfetUk == tQnqTIwYKh){WcFpSOOqdB = true;}
      else if(tQnqTIwYKh == OqSBmfetUk){uXUWnaxKKX = true;}
      if(WmkGpPcryx == KiplLrUlVh){eYLhftVlKi = true;}
      else if(KiplLrUlVh == WmkGpPcryx){cehhWDdTWw = true;}
      if(sIQIssFctM == mKjRrUOFCV){OHYSJcjzGM = true;}
      else if(mKjRrUOFCV == sIQIssFctM){MSjMFutqKl = true;}
      if(akKqXlBLpk == DpdQbRsqsd){LlJZrosdRP = true;}
      else if(DpdQbRsqsd == akKqXlBLpk){ViRjDuENbS = true;}
      if(OtNYoWKWtg == fYGbGbCQjR){fOTyNKJKNp = true;}
      else if(fYGbGbCQjR == OtNYoWKWtg){xUkezFXPEg = true;}
      if(ZymrfGaJIt == rIifPigWyy){SQGNWPEmgp = true;}
      else if(rIifPigWyy == ZymrfGaJIt){mJfMHbmIRr = true;}
      if(aCzIKlctiD == sqWoeUFYKt){dPkQprPlop = true;}
      else if(sqWoeUFYKt == aCzIKlctiD){gFAXBsNxdb = true;}
      if(NRBNhyurTV == zcsqCNEHKP){BqTuDzmZEy = true;}
      if(hhhMlbyRKR == SyUkduGxAr){SZkQstewCc = true;}
      if(LrCwKMuFND == jVrtkoCRxk){kFxbkQdDIU = true;}
      while(zcsqCNEHKP == NRBNhyurTV){yPrEyrhEMz = true;}
      while(SyUkduGxAr == SyUkduGxAr){XdlczLCFba = true;}
      while(jVrtkoCRxk == jVrtkoCRxk){HwwikqTNcG = true;}
      if(WcFpSOOqdB == true){WcFpSOOqdB = false;}
      if(eYLhftVlKi == true){eYLhftVlKi = false;}
      if(OHYSJcjzGM == true){OHYSJcjzGM = false;}
      if(LlJZrosdRP == true){LlJZrosdRP = false;}
      if(fOTyNKJKNp == true){fOTyNKJKNp = false;}
      if(SQGNWPEmgp == true){SQGNWPEmgp = false;}
      if(dPkQprPlop == true){dPkQprPlop = false;}
      if(BqTuDzmZEy == true){BqTuDzmZEy = false;}
      if(SZkQstewCc == true){SZkQstewCc = false;}
      if(kFxbkQdDIU == true){kFxbkQdDIU = false;}
      if(uXUWnaxKKX == true){uXUWnaxKKX = false;}
      if(cehhWDdTWw == true){cehhWDdTWw = false;}
      if(MSjMFutqKl == true){MSjMFutqKl = false;}
      if(ViRjDuENbS == true){ViRjDuENbS = false;}
      if(xUkezFXPEg == true){xUkezFXPEg = false;}
      if(mJfMHbmIRr == true){mJfMHbmIRr = false;}
      if(gFAXBsNxdb == true){gFAXBsNxdb = false;}
      if(yPrEyrhEMz == true){yPrEyrhEMz = false;}
      if(XdlczLCFba == true){XdlczLCFba = false;}
      if(HwwikqTNcG == true){HwwikqTNcG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YWYRPJBOMD
{ 
  void UgnETYcEwT()
  { 
      bool FpTnBjhnio = false;
      bool ULCwYMYeXI = false;
      bool cXBiNyTahR = false;
      bool OwecSCaOTi = false;
      bool QRfRAQzLgI = false;
      bool PSZIwhojZD = false;
      bool QGGRaYfZcV = false;
      bool lKLnrKqjix = false;
      bool zItZBwVVfj = false;
      bool NpnQSJLNqb = false;
      bool jZhKWFGkQk = false;
      bool qEBcDHMfPd = false;
      bool CKssHuVuVh = false;
      bool ydsGMZaiDw = false;
      bool okFtsInLMK = false;
      bool xexMYZfnDa = false;
      bool iLPhmNLtPd = false;
      bool fccTnREyAz = false;
      bool GKhKkSfghm = false;
      bool slfbNdUWHf = false;
      string jeFGFIYnCM;
      string QcPqyKbjTf;
      string kfVTeNgFBQ;
      string SfgxstCqxl;
      string iEJExuxMpT;
      string MuHTBDIlaq;
      string bTlksjwSyD;
      string IjmhwfWQVj;
      string PUPhEXYMuo;
      string kPPFJPSXLN;
      string yeNmKbHYXV;
      string grQqaHDDfV;
      string LiWJRrTgXf;
      string NyFIkkGbXc;
      string PzoZHszYdC;
      string LOqoBPIEUR;
      string HaBqHimIFp;
      string AbfDFMtwBY;
      string stCVTzGPGV;
      string bCHFUnxxRY;
      if(jeFGFIYnCM == yeNmKbHYXV){FpTnBjhnio = true;}
      else if(yeNmKbHYXV == jeFGFIYnCM){jZhKWFGkQk = true;}
      if(QcPqyKbjTf == grQqaHDDfV){ULCwYMYeXI = true;}
      else if(grQqaHDDfV == QcPqyKbjTf){qEBcDHMfPd = true;}
      if(kfVTeNgFBQ == LiWJRrTgXf){cXBiNyTahR = true;}
      else if(LiWJRrTgXf == kfVTeNgFBQ){CKssHuVuVh = true;}
      if(SfgxstCqxl == NyFIkkGbXc){OwecSCaOTi = true;}
      else if(NyFIkkGbXc == SfgxstCqxl){ydsGMZaiDw = true;}
      if(iEJExuxMpT == PzoZHszYdC){QRfRAQzLgI = true;}
      else if(PzoZHszYdC == iEJExuxMpT){okFtsInLMK = true;}
      if(MuHTBDIlaq == LOqoBPIEUR){PSZIwhojZD = true;}
      else if(LOqoBPIEUR == MuHTBDIlaq){xexMYZfnDa = true;}
      if(bTlksjwSyD == HaBqHimIFp){QGGRaYfZcV = true;}
      else if(HaBqHimIFp == bTlksjwSyD){iLPhmNLtPd = true;}
      if(IjmhwfWQVj == AbfDFMtwBY){lKLnrKqjix = true;}
      if(PUPhEXYMuo == stCVTzGPGV){zItZBwVVfj = true;}
      if(kPPFJPSXLN == bCHFUnxxRY){NpnQSJLNqb = true;}
      while(AbfDFMtwBY == IjmhwfWQVj){fccTnREyAz = true;}
      while(stCVTzGPGV == stCVTzGPGV){GKhKkSfghm = true;}
      while(bCHFUnxxRY == bCHFUnxxRY){slfbNdUWHf = true;}
      if(FpTnBjhnio == true){FpTnBjhnio = false;}
      if(ULCwYMYeXI == true){ULCwYMYeXI = false;}
      if(cXBiNyTahR == true){cXBiNyTahR = false;}
      if(OwecSCaOTi == true){OwecSCaOTi = false;}
      if(QRfRAQzLgI == true){QRfRAQzLgI = false;}
      if(PSZIwhojZD == true){PSZIwhojZD = false;}
      if(QGGRaYfZcV == true){QGGRaYfZcV = false;}
      if(lKLnrKqjix == true){lKLnrKqjix = false;}
      if(zItZBwVVfj == true){zItZBwVVfj = false;}
      if(NpnQSJLNqb == true){NpnQSJLNqb = false;}
      if(jZhKWFGkQk == true){jZhKWFGkQk = false;}
      if(qEBcDHMfPd == true){qEBcDHMfPd = false;}
      if(CKssHuVuVh == true){CKssHuVuVh = false;}
      if(ydsGMZaiDw == true){ydsGMZaiDw = false;}
      if(okFtsInLMK == true){okFtsInLMK = false;}
      if(xexMYZfnDa == true){xexMYZfnDa = false;}
      if(iLPhmNLtPd == true){iLPhmNLtPd = false;}
      if(fccTnREyAz == true){fccTnREyAz = false;}
      if(GKhKkSfghm == true){GKhKkSfghm = false;}
      if(slfbNdUWHf == true){slfbNdUWHf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GKCTQFFJNE
{ 
  void kOFSnOIEbQ()
  { 
      bool AqpqSojoII = false;
      bool bKIoGAzoVw = false;
      bool pYhetrwnKN = false;
      bool auyWdOUWQo = false;
      bool aDyBifQgHR = false;
      bool CHlSlbILwa = false;
      bool swduhgMlKr = false;
      bool ebXfVlZfuO = false;
      bool aOfsKSIekB = false;
      bool FJZpwdZCTC = false;
      bool SeWPmZiFxz = false;
      bool BcQhzdQjjO = false;
      bool XgAImVBhjq = false;
      bool LXMruwrPGk = false;
      bool jCgkAcrrpR = false;
      bool MoREdkdNcQ = false;
      bool YAVGmdPYmD = false;
      bool lBdzdVAOIJ = false;
      bool cJrRdWFHNJ = false;
      bool SdmoLjfayV = false;
      string hcxBcegmht;
      string ZuPzoYhbps;
      string iCiykAeDir;
      string uQkzjkRcFj;
      string rTQBhCafiH;
      string JaAnVfsyPb;
      string zcDpzJJPOD;
      string HFVFBOkhPi;
      string ZzUahUPwdE;
      string rSNdkOPZCY;
      string rKReAEFtmG;
      string tLigBzHcHd;
      string sMkJLnrqUl;
      string yLeppPhoZd;
      string PVJXKgifck;
      string HmSXfeYHTL;
      string LNYBHifrpk;
      string RRCcOWDNye;
      string FLOjeLrHKL;
      string qZVOSBwIPb;
      if(hcxBcegmht == rKReAEFtmG){AqpqSojoII = true;}
      else if(rKReAEFtmG == hcxBcegmht){SeWPmZiFxz = true;}
      if(ZuPzoYhbps == tLigBzHcHd){bKIoGAzoVw = true;}
      else if(tLigBzHcHd == ZuPzoYhbps){BcQhzdQjjO = true;}
      if(iCiykAeDir == sMkJLnrqUl){pYhetrwnKN = true;}
      else if(sMkJLnrqUl == iCiykAeDir){XgAImVBhjq = true;}
      if(uQkzjkRcFj == yLeppPhoZd){auyWdOUWQo = true;}
      else if(yLeppPhoZd == uQkzjkRcFj){LXMruwrPGk = true;}
      if(rTQBhCafiH == PVJXKgifck){aDyBifQgHR = true;}
      else if(PVJXKgifck == rTQBhCafiH){jCgkAcrrpR = true;}
      if(JaAnVfsyPb == HmSXfeYHTL){CHlSlbILwa = true;}
      else if(HmSXfeYHTL == JaAnVfsyPb){MoREdkdNcQ = true;}
      if(zcDpzJJPOD == LNYBHifrpk){swduhgMlKr = true;}
      else if(LNYBHifrpk == zcDpzJJPOD){YAVGmdPYmD = true;}
      if(HFVFBOkhPi == RRCcOWDNye){ebXfVlZfuO = true;}
      if(ZzUahUPwdE == FLOjeLrHKL){aOfsKSIekB = true;}
      if(rSNdkOPZCY == qZVOSBwIPb){FJZpwdZCTC = true;}
      while(RRCcOWDNye == HFVFBOkhPi){lBdzdVAOIJ = true;}
      while(FLOjeLrHKL == FLOjeLrHKL){cJrRdWFHNJ = true;}
      while(qZVOSBwIPb == qZVOSBwIPb){SdmoLjfayV = true;}
      if(AqpqSojoII == true){AqpqSojoII = false;}
      if(bKIoGAzoVw == true){bKIoGAzoVw = false;}
      if(pYhetrwnKN == true){pYhetrwnKN = false;}
      if(auyWdOUWQo == true){auyWdOUWQo = false;}
      if(aDyBifQgHR == true){aDyBifQgHR = false;}
      if(CHlSlbILwa == true){CHlSlbILwa = false;}
      if(swduhgMlKr == true){swduhgMlKr = false;}
      if(ebXfVlZfuO == true){ebXfVlZfuO = false;}
      if(aOfsKSIekB == true){aOfsKSIekB = false;}
      if(FJZpwdZCTC == true){FJZpwdZCTC = false;}
      if(SeWPmZiFxz == true){SeWPmZiFxz = false;}
      if(BcQhzdQjjO == true){BcQhzdQjjO = false;}
      if(XgAImVBhjq == true){XgAImVBhjq = false;}
      if(LXMruwrPGk == true){LXMruwrPGk = false;}
      if(jCgkAcrrpR == true){jCgkAcrrpR = false;}
      if(MoREdkdNcQ == true){MoREdkdNcQ = false;}
      if(YAVGmdPYmD == true){YAVGmdPYmD = false;}
      if(lBdzdVAOIJ == true){lBdzdVAOIJ = false;}
      if(cJrRdWFHNJ == true){cJrRdWFHNJ = false;}
      if(SdmoLjfayV == true){SdmoLjfayV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EQIKACLFTB
{ 
  void WnylPHWghP()
  { 
      bool pXtdDIEKEo = false;
      bool qZwUOcrEQC = false;
      bool VOLbTsnkuG = false;
      bool xyeZwjDCol = false;
      bool WkFekcxclH = false;
      bool PsgkmaLSJK = false;
      bool UTPxqstWYe = false;
      bool YoOefkJgpq = false;
      bool uKympEQtlU = false;
      bool XkrdQDVImq = false;
      bool hZEHhadCEB = false;
      bool RdbSPKUbGm = false;
      bool bAkEHnwkNc = false;
      bool PBtyIVFqEP = false;
      bool ZOojCsJZOG = false;
      bool hsBAPhoAzt = false;
      bool dsoblQjcJs = false;
      bool EdWpMNKBCN = false;
      bool dVVHtVzsia = false;
      bool fFqJlgZMxk = false;
      string MgrtBdJzzU;
      string SChznAIOVa;
      string jkkbQGzAjV;
      string pymgIPCtNh;
      string xQNswHfiie;
      string kFUdQbuPct;
      string dJPceUOBqX;
      string xNBmcTWrfI;
      string aQQEjjcJPf;
      string TmRTDmBjNb;
      string seqKgXEhAx;
      string EDjTSMrKst;
      string qFkKDKwgjo;
      string SmdEPwZGXM;
      string fuISbQDyAp;
      string uqqTjnsfHW;
      string aXxKeRZeDW;
      string mllfOuwSim;
      string HyfstbuKTb;
      string CtyBkHxxnJ;
      if(MgrtBdJzzU == seqKgXEhAx){pXtdDIEKEo = true;}
      else if(seqKgXEhAx == MgrtBdJzzU){hZEHhadCEB = true;}
      if(SChznAIOVa == EDjTSMrKst){qZwUOcrEQC = true;}
      else if(EDjTSMrKst == SChznAIOVa){RdbSPKUbGm = true;}
      if(jkkbQGzAjV == qFkKDKwgjo){VOLbTsnkuG = true;}
      else if(qFkKDKwgjo == jkkbQGzAjV){bAkEHnwkNc = true;}
      if(pymgIPCtNh == SmdEPwZGXM){xyeZwjDCol = true;}
      else if(SmdEPwZGXM == pymgIPCtNh){PBtyIVFqEP = true;}
      if(xQNswHfiie == fuISbQDyAp){WkFekcxclH = true;}
      else if(fuISbQDyAp == xQNswHfiie){ZOojCsJZOG = true;}
      if(kFUdQbuPct == uqqTjnsfHW){PsgkmaLSJK = true;}
      else if(uqqTjnsfHW == kFUdQbuPct){hsBAPhoAzt = true;}
      if(dJPceUOBqX == aXxKeRZeDW){UTPxqstWYe = true;}
      else if(aXxKeRZeDW == dJPceUOBqX){dsoblQjcJs = true;}
      if(xNBmcTWrfI == mllfOuwSim){YoOefkJgpq = true;}
      if(aQQEjjcJPf == HyfstbuKTb){uKympEQtlU = true;}
      if(TmRTDmBjNb == CtyBkHxxnJ){XkrdQDVImq = true;}
      while(mllfOuwSim == xNBmcTWrfI){EdWpMNKBCN = true;}
      while(HyfstbuKTb == HyfstbuKTb){dVVHtVzsia = true;}
      while(CtyBkHxxnJ == CtyBkHxxnJ){fFqJlgZMxk = true;}
      if(pXtdDIEKEo == true){pXtdDIEKEo = false;}
      if(qZwUOcrEQC == true){qZwUOcrEQC = false;}
      if(VOLbTsnkuG == true){VOLbTsnkuG = false;}
      if(xyeZwjDCol == true){xyeZwjDCol = false;}
      if(WkFekcxclH == true){WkFekcxclH = false;}
      if(PsgkmaLSJK == true){PsgkmaLSJK = false;}
      if(UTPxqstWYe == true){UTPxqstWYe = false;}
      if(YoOefkJgpq == true){YoOefkJgpq = false;}
      if(uKympEQtlU == true){uKympEQtlU = false;}
      if(XkrdQDVImq == true){XkrdQDVImq = false;}
      if(hZEHhadCEB == true){hZEHhadCEB = false;}
      if(RdbSPKUbGm == true){RdbSPKUbGm = false;}
      if(bAkEHnwkNc == true){bAkEHnwkNc = false;}
      if(PBtyIVFqEP == true){PBtyIVFqEP = false;}
      if(ZOojCsJZOG == true){ZOojCsJZOG = false;}
      if(hsBAPhoAzt == true){hsBAPhoAzt = false;}
      if(dsoblQjcJs == true){dsoblQjcJs = false;}
      if(EdWpMNKBCN == true){EdWpMNKBCN = false;}
      if(dVVHtVzsia == true){dVVHtVzsia = false;}
      if(fFqJlgZMxk == true){fFqJlgZMxk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DFDITWAOZB
{ 
  void lNHkRrWMWk()
  { 
      bool WAJuEcpDyr = false;
      bool LTpnaUsuHJ = false;
      bool GLbsRBtWJy = false;
      bool QJmeKtPFod = false;
      bool rfrSXlImjg = false;
      bool ZkqiULYQcC = false;
      bool iTtAaCgKdg = false;
      bool FmGdQZSIVe = false;
      bool sGlbYeREKz = false;
      bool UzbmtYkrqU = false;
      bool ExJDaleNRt = false;
      bool rPtyIbgSaw = false;
      bool kcAdLGLTir = false;
      bool naRAauwiAm = false;
      bool zEmPGFEddS = false;
      bool qSQtjbxfqU = false;
      bool ZLdYGQytWM = false;
      bool eyRnwfpjXG = false;
      bool ChoQBUKWQy = false;
      bool yQrfMnaNJo = false;
      string dKFStVdmME;
      string ejgAiihMKj;
      string WOzEpsLmrx;
      string ByecWtbyxL;
      string JfoxquUxPJ;
      string qbnuqPLBcB;
      string KquPDfFDdn;
      string HiPzZqZBMt;
      string XOXhFYKilG;
      string iaVwBSkZtL;
      string pRTaCIMnVA;
      string pJnhduSMJd;
      string UVRWFgNSyG;
      string GzHBEFuwfx;
      string MWNlQYmmSF;
      string zXPQpUzwUU;
      string usoOspCldX;
      string AVgLRyIfFg;
      string tZAsGijqKj;
      string FybKCSgyra;
      if(dKFStVdmME == pRTaCIMnVA){WAJuEcpDyr = true;}
      else if(pRTaCIMnVA == dKFStVdmME){ExJDaleNRt = true;}
      if(ejgAiihMKj == pJnhduSMJd){LTpnaUsuHJ = true;}
      else if(pJnhduSMJd == ejgAiihMKj){rPtyIbgSaw = true;}
      if(WOzEpsLmrx == UVRWFgNSyG){GLbsRBtWJy = true;}
      else if(UVRWFgNSyG == WOzEpsLmrx){kcAdLGLTir = true;}
      if(ByecWtbyxL == GzHBEFuwfx){QJmeKtPFod = true;}
      else if(GzHBEFuwfx == ByecWtbyxL){naRAauwiAm = true;}
      if(JfoxquUxPJ == MWNlQYmmSF){rfrSXlImjg = true;}
      else if(MWNlQYmmSF == JfoxquUxPJ){zEmPGFEddS = true;}
      if(qbnuqPLBcB == zXPQpUzwUU){ZkqiULYQcC = true;}
      else if(zXPQpUzwUU == qbnuqPLBcB){qSQtjbxfqU = true;}
      if(KquPDfFDdn == usoOspCldX){iTtAaCgKdg = true;}
      else if(usoOspCldX == KquPDfFDdn){ZLdYGQytWM = true;}
      if(HiPzZqZBMt == AVgLRyIfFg){FmGdQZSIVe = true;}
      if(XOXhFYKilG == tZAsGijqKj){sGlbYeREKz = true;}
      if(iaVwBSkZtL == FybKCSgyra){UzbmtYkrqU = true;}
      while(AVgLRyIfFg == HiPzZqZBMt){eyRnwfpjXG = true;}
      while(tZAsGijqKj == tZAsGijqKj){ChoQBUKWQy = true;}
      while(FybKCSgyra == FybKCSgyra){yQrfMnaNJo = true;}
      if(WAJuEcpDyr == true){WAJuEcpDyr = false;}
      if(LTpnaUsuHJ == true){LTpnaUsuHJ = false;}
      if(GLbsRBtWJy == true){GLbsRBtWJy = false;}
      if(QJmeKtPFod == true){QJmeKtPFod = false;}
      if(rfrSXlImjg == true){rfrSXlImjg = false;}
      if(ZkqiULYQcC == true){ZkqiULYQcC = false;}
      if(iTtAaCgKdg == true){iTtAaCgKdg = false;}
      if(FmGdQZSIVe == true){FmGdQZSIVe = false;}
      if(sGlbYeREKz == true){sGlbYeREKz = false;}
      if(UzbmtYkrqU == true){UzbmtYkrqU = false;}
      if(ExJDaleNRt == true){ExJDaleNRt = false;}
      if(rPtyIbgSaw == true){rPtyIbgSaw = false;}
      if(kcAdLGLTir == true){kcAdLGLTir = false;}
      if(naRAauwiAm == true){naRAauwiAm = false;}
      if(zEmPGFEddS == true){zEmPGFEddS = false;}
      if(qSQtjbxfqU == true){qSQtjbxfqU = false;}
      if(ZLdYGQytWM == true){ZLdYGQytWM = false;}
      if(eyRnwfpjXG == true){eyRnwfpjXG = false;}
      if(ChoQBUKWQy == true){ChoQBUKWQy = false;}
      if(yQrfMnaNJo == true){yQrfMnaNJo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SVLOPAOCFQ
{ 
  void QNIxJsLMJd()
  { 
      bool zGSKipioud = false;
      bool jfgJZsZhOQ = false;
      bool wiufLnQsDb = false;
      bool gJHRgaaEhN = false;
      bool YOIXxXZihC = false;
      bool zdqNaQKmzu = false;
      bool ZpkTwaXOcy = false;
      bool RUzAqhaWim = false;
      bool OgKBbCRtqQ = false;
      bool QmFmnicoaV = false;
      bool zKGjjdepVs = false;
      bool pmELfreiqt = false;
      bool IdXLgePMMI = false;
      bool EluMnDaaRy = false;
      bool XbXyacitGw = false;
      bool EtxgNVmtCF = false;
      bool ORcNnEqrXc = false;
      bool QDRsWfFZkE = false;
      bool uVGQEKnOzR = false;
      bool QgYMiGyKJW = false;
      string ZsLCNVhnpx;
      string CmmHcPnmlQ;
      string RQolouhyPK;
      string jtGdafBngo;
      string YYBZjUQSGH;
      string OmoMJIDYNR;
      string miXeMIgJgw;
      string NAGwqsOOBT;
      string ePrIwwEsTR;
      string bbZOBoAWNb;
      string mHlJsNgsUQ;
      string soXsmXqPhQ;
      string EnoOTlZqtC;
      string rrBZgWdhOi;
      string OKYCYmEfad;
      string yjnxWzSWpH;
      string mpySYAmyMQ;
      string tIBzBsOlpf;
      string gtPQDIDECg;
      string EGrHuYMFdX;
      if(ZsLCNVhnpx == mHlJsNgsUQ){zGSKipioud = true;}
      else if(mHlJsNgsUQ == ZsLCNVhnpx){zKGjjdepVs = true;}
      if(CmmHcPnmlQ == soXsmXqPhQ){jfgJZsZhOQ = true;}
      else if(soXsmXqPhQ == CmmHcPnmlQ){pmELfreiqt = true;}
      if(RQolouhyPK == EnoOTlZqtC){wiufLnQsDb = true;}
      else if(EnoOTlZqtC == RQolouhyPK){IdXLgePMMI = true;}
      if(jtGdafBngo == rrBZgWdhOi){gJHRgaaEhN = true;}
      else if(rrBZgWdhOi == jtGdafBngo){EluMnDaaRy = true;}
      if(YYBZjUQSGH == OKYCYmEfad){YOIXxXZihC = true;}
      else if(OKYCYmEfad == YYBZjUQSGH){XbXyacitGw = true;}
      if(OmoMJIDYNR == yjnxWzSWpH){zdqNaQKmzu = true;}
      else if(yjnxWzSWpH == OmoMJIDYNR){EtxgNVmtCF = true;}
      if(miXeMIgJgw == mpySYAmyMQ){ZpkTwaXOcy = true;}
      else if(mpySYAmyMQ == miXeMIgJgw){ORcNnEqrXc = true;}
      if(NAGwqsOOBT == tIBzBsOlpf){RUzAqhaWim = true;}
      if(ePrIwwEsTR == gtPQDIDECg){OgKBbCRtqQ = true;}
      if(bbZOBoAWNb == EGrHuYMFdX){QmFmnicoaV = true;}
      while(tIBzBsOlpf == NAGwqsOOBT){QDRsWfFZkE = true;}
      while(gtPQDIDECg == gtPQDIDECg){uVGQEKnOzR = true;}
      while(EGrHuYMFdX == EGrHuYMFdX){QgYMiGyKJW = true;}
      if(zGSKipioud == true){zGSKipioud = false;}
      if(jfgJZsZhOQ == true){jfgJZsZhOQ = false;}
      if(wiufLnQsDb == true){wiufLnQsDb = false;}
      if(gJHRgaaEhN == true){gJHRgaaEhN = false;}
      if(YOIXxXZihC == true){YOIXxXZihC = false;}
      if(zdqNaQKmzu == true){zdqNaQKmzu = false;}
      if(ZpkTwaXOcy == true){ZpkTwaXOcy = false;}
      if(RUzAqhaWim == true){RUzAqhaWim = false;}
      if(OgKBbCRtqQ == true){OgKBbCRtqQ = false;}
      if(QmFmnicoaV == true){QmFmnicoaV = false;}
      if(zKGjjdepVs == true){zKGjjdepVs = false;}
      if(pmELfreiqt == true){pmELfreiqt = false;}
      if(IdXLgePMMI == true){IdXLgePMMI = false;}
      if(EluMnDaaRy == true){EluMnDaaRy = false;}
      if(XbXyacitGw == true){XbXyacitGw = false;}
      if(EtxgNVmtCF == true){EtxgNVmtCF = false;}
      if(ORcNnEqrXc == true){ORcNnEqrXc = false;}
      if(QDRsWfFZkE == true){QDRsWfFZkE = false;}
      if(uVGQEKnOzR == true){uVGQEKnOzR = false;}
      if(QgYMiGyKJW == true){QgYMiGyKJW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CFPTSSKHFS
{ 
  void JaZJSuyOrm()
  { 
      bool cPAnylJRPc = false;
      bool nnhgayIWfG = false;
      bool KWVBGDYAHa = false;
      bool deXTVnRVyO = false;
      bool ZwVpSgaSAZ = false;
      bool CXPttFtzht = false;
      bool MIJnyJPNLl = false;
      bool gmYQfNAehY = false;
      bool cFAhYFOdYP = false;
      bool tSmEBQlhqJ = false;
      bool QMHNsOzyNg = false;
      bool EOQIQHIbOs = false;
      bool tlowqOzTPO = false;
      bool bSnYHQylnJ = false;
      bool GQQrKeBemt = false;
      bool IJSyPeXLVe = false;
      bool PeizElarAA = false;
      bool IWnEmdUwkM = false;
      bool MTgUGRzoIc = false;
      bool rlPJtagRmX = false;
      string OyJDUtqmyq;
      string mdHoCSbugF;
      string eAzijztlLt;
      string JJBtahqJul;
      string YsWxUuoWmQ;
      string LpUbtNyZTU;
      string zFbDgdcNOU;
      string aRztgkdCNn;
      string KXztiSoYzM;
      string iRoamSRSPq;
      string SbIRosqauJ;
      string jwLeKbGgUO;
      string nDOBlJcYHN;
      string TLmWViPgFo;
      string bOcpclFKPK;
      string MjxBCOMGfe;
      string QRSgoXIoJb;
      string MZaflZZYYz;
      string ESJwBiNlTH;
      string VIAaXKuuAE;
      if(OyJDUtqmyq == SbIRosqauJ){cPAnylJRPc = true;}
      else if(SbIRosqauJ == OyJDUtqmyq){QMHNsOzyNg = true;}
      if(mdHoCSbugF == jwLeKbGgUO){nnhgayIWfG = true;}
      else if(jwLeKbGgUO == mdHoCSbugF){EOQIQHIbOs = true;}
      if(eAzijztlLt == nDOBlJcYHN){KWVBGDYAHa = true;}
      else if(nDOBlJcYHN == eAzijztlLt){tlowqOzTPO = true;}
      if(JJBtahqJul == TLmWViPgFo){deXTVnRVyO = true;}
      else if(TLmWViPgFo == JJBtahqJul){bSnYHQylnJ = true;}
      if(YsWxUuoWmQ == bOcpclFKPK){ZwVpSgaSAZ = true;}
      else if(bOcpclFKPK == YsWxUuoWmQ){GQQrKeBemt = true;}
      if(LpUbtNyZTU == MjxBCOMGfe){CXPttFtzht = true;}
      else if(MjxBCOMGfe == LpUbtNyZTU){IJSyPeXLVe = true;}
      if(zFbDgdcNOU == QRSgoXIoJb){MIJnyJPNLl = true;}
      else if(QRSgoXIoJb == zFbDgdcNOU){PeizElarAA = true;}
      if(aRztgkdCNn == MZaflZZYYz){gmYQfNAehY = true;}
      if(KXztiSoYzM == ESJwBiNlTH){cFAhYFOdYP = true;}
      if(iRoamSRSPq == VIAaXKuuAE){tSmEBQlhqJ = true;}
      while(MZaflZZYYz == aRztgkdCNn){IWnEmdUwkM = true;}
      while(ESJwBiNlTH == ESJwBiNlTH){MTgUGRzoIc = true;}
      while(VIAaXKuuAE == VIAaXKuuAE){rlPJtagRmX = true;}
      if(cPAnylJRPc == true){cPAnylJRPc = false;}
      if(nnhgayIWfG == true){nnhgayIWfG = false;}
      if(KWVBGDYAHa == true){KWVBGDYAHa = false;}
      if(deXTVnRVyO == true){deXTVnRVyO = false;}
      if(ZwVpSgaSAZ == true){ZwVpSgaSAZ = false;}
      if(CXPttFtzht == true){CXPttFtzht = false;}
      if(MIJnyJPNLl == true){MIJnyJPNLl = false;}
      if(gmYQfNAehY == true){gmYQfNAehY = false;}
      if(cFAhYFOdYP == true){cFAhYFOdYP = false;}
      if(tSmEBQlhqJ == true){tSmEBQlhqJ = false;}
      if(QMHNsOzyNg == true){QMHNsOzyNg = false;}
      if(EOQIQHIbOs == true){EOQIQHIbOs = false;}
      if(tlowqOzTPO == true){tlowqOzTPO = false;}
      if(bSnYHQylnJ == true){bSnYHQylnJ = false;}
      if(GQQrKeBemt == true){GQQrKeBemt = false;}
      if(IJSyPeXLVe == true){IJSyPeXLVe = false;}
      if(PeizElarAA == true){PeizElarAA = false;}
      if(IWnEmdUwkM == true){IWnEmdUwkM = false;}
      if(MTgUGRzoIc == true){MTgUGRzoIc = false;}
      if(rlPJtagRmX == true){rlPJtagRmX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YODXWQEJZV
{ 
  void xtSihiXhos()
  { 
      bool PXtwnNPemH = false;
      bool ZowfKeekbE = false;
      bool ftQRceUEby = false;
      bool AbgccjPMcE = false;
      bool eaqFnLdXaN = false;
      bool EyPodVHcSJ = false;
      bool sKDoHxHTCa = false;
      bool PSIXZECKdR = false;
      bool BwcOtBMqzH = false;
      bool cmtTKTXCyp = false;
      bool DJUAxlprPY = false;
      bool SwyAIwhouF = false;
      bool jQUuybXoMG = false;
      bool gAMmOqbcQI = false;
      bool LUbZnfnsLO = false;
      bool lhGsGmoZBV = false;
      bool NBeJrSiKlQ = false;
      bool UEYmsOotGR = false;
      bool mddxTysTgb = false;
      bool BBautKoRhV = false;
      string YyMotDTjnU;
      string zXIPGoBRLU;
      string gWzHwzOiGd;
      string UcftrMrEOt;
      string ZeNZlpyoAY;
      string VZdtBCyFru;
      string nkcKAVqNXt;
      string wwCQtCJZVG;
      string AZhhHuzkso;
      string NlLTGoBCZP;
      string zkQFcZWMzz;
      string sYjltNCuCE;
      string WFUhgJjiKF;
      string AGzFHPIcEh;
      string XlkswnCZZs;
      string mGzUrsPiYS;
      string onCtzlYded;
      string EYpUgjTalr;
      string HKIQStGeNN;
      string AZElrijqtJ;
      if(YyMotDTjnU == zkQFcZWMzz){PXtwnNPemH = true;}
      else if(zkQFcZWMzz == YyMotDTjnU){DJUAxlprPY = true;}
      if(zXIPGoBRLU == sYjltNCuCE){ZowfKeekbE = true;}
      else if(sYjltNCuCE == zXIPGoBRLU){SwyAIwhouF = true;}
      if(gWzHwzOiGd == WFUhgJjiKF){ftQRceUEby = true;}
      else if(WFUhgJjiKF == gWzHwzOiGd){jQUuybXoMG = true;}
      if(UcftrMrEOt == AGzFHPIcEh){AbgccjPMcE = true;}
      else if(AGzFHPIcEh == UcftrMrEOt){gAMmOqbcQI = true;}
      if(ZeNZlpyoAY == XlkswnCZZs){eaqFnLdXaN = true;}
      else if(XlkswnCZZs == ZeNZlpyoAY){LUbZnfnsLO = true;}
      if(VZdtBCyFru == mGzUrsPiYS){EyPodVHcSJ = true;}
      else if(mGzUrsPiYS == VZdtBCyFru){lhGsGmoZBV = true;}
      if(nkcKAVqNXt == onCtzlYded){sKDoHxHTCa = true;}
      else if(onCtzlYded == nkcKAVqNXt){NBeJrSiKlQ = true;}
      if(wwCQtCJZVG == EYpUgjTalr){PSIXZECKdR = true;}
      if(AZhhHuzkso == HKIQStGeNN){BwcOtBMqzH = true;}
      if(NlLTGoBCZP == AZElrijqtJ){cmtTKTXCyp = true;}
      while(EYpUgjTalr == wwCQtCJZVG){UEYmsOotGR = true;}
      while(HKIQStGeNN == HKIQStGeNN){mddxTysTgb = true;}
      while(AZElrijqtJ == AZElrijqtJ){BBautKoRhV = true;}
      if(PXtwnNPemH == true){PXtwnNPemH = false;}
      if(ZowfKeekbE == true){ZowfKeekbE = false;}
      if(ftQRceUEby == true){ftQRceUEby = false;}
      if(AbgccjPMcE == true){AbgccjPMcE = false;}
      if(eaqFnLdXaN == true){eaqFnLdXaN = false;}
      if(EyPodVHcSJ == true){EyPodVHcSJ = false;}
      if(sKDoHxHTCa == true){sKDoHxHTCa = false;}
      if(PSIXZECKdR == true){PSIXZECKdR = false;}
      if(BwcOtBMqzH == true){BwcOtBMqzH = false;}
      if(cmtTKTXCyp == true){cmtTKTXCyp = false;}
      if(DJUAxlprPY == true){DJUAxlprPY = false;}
      if(SwyAIwhouF == true){SwyAIwhouF = false;}
      if(jQUuybXoMG == true){jQUuybXoMG = false;}
      if(gAMmOqbcQI == true){gAMmOqbcQI = false;}
      if(LUbZnfnsLO == true){LUbZnfnsLO = false;}
      if(lhGsGmoZBV == true){lhGsGmoZBV = false;}
      if(NBeJrSiKlQ == true){NBeJrSiKlQ = false;}
      if(UEYmsOotGR == true){UEYmsOotGR = false;}
      if(mddxTysTgb == true){mddxTysTgb = false;}
      if(BBautKoRhV == true){BBautKoRhV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BPNJXDERAS
{ 
  void hccwOyQdEW()
  { 
      bool YhSuWWtDhi = false;
      bool oQnHmOMGZb = false;
      bool ioVGIRBchP = false;
      bool RetgxyPFLF = false;
      bool EjsWgCiDRo = false;
      bool BEHPIiMMmF = false;
      bool URVSRJWGJn = false;
      bool zHtUXzwyZF = false;
      bool hyKrNMXdYN = false;
      bool lDRGjmNZFX = false;
      bool fbscptJmrJ = false;
      bool lOlhWWGcFE = false;
      bool krgwCwpnjj = false;
      bool kVrBZFEgCS = false;
      bool DklPaXQjiM = false;
      bool gjUBlmtxat = false;
      bool EVCHXQVkIQ = false;
      bool SYalBAFRUe = false;
      bool eGEXDAAqOl = false;
      bool LGGIOhierK = false;
      string AJOlsFCmyV;
      string SEOXLyxudN;
      string rwxNOPsXri;
      string yCJlTFEUzy;
      string PfqpFsjFtF;
      string FhQLPELBWc;
      string MdtPWPtbDF;
      string tcufxMEHHV;
      string emclcPlyWP;
      string tDxWkkkbTp;
      string yICoLbmjOD;
      string AEsByZBIlH;
      string dwFnLqeYtL;
      string acmRXWknZA;
      string cBiTOoJwXL;
      string jboMLBCNcU;
      string xNpCbWQbcb;
      string oMhkdcMlYV;
      string giBibznaFV;
      string TWKFDOLgrq;
      if(AJOlsFCmyV == yICoLbmjOD){YhSuWWtDhi = true;}
      else if(yICoLbmjOD == AJOlsFCmyV){fbscptJmrJ = true;}
      if(SEOXLyxudN == AEsByZBIlH){oQnHmOMGZb = true;}
      else if(AEsByZBIlH == SEOXLyxudN){lOlhWWGcFE = true;}
      if(rwxNOPsXri == dwFnLqeYtL){ioVGIRBchP = true;}
      else if(dwFnLqeYtL == rwxNOPsXri){krgwCwpnjj = true;}
      if(yCJlTFEUzy == acmRXWknZA){RetgxyPFLF = true;}
      else if(acmRXWknZA == yCJlTFEUzy){kVrBZFEgCS = true;}
      if(PfqpFsjFtF == cBiTOoJwXL){EjsWgCiDRo = true;}
      else if(cBiTOoJwXL == PfqpFsjFtF){DklPaXQjiM = true;}
      if(FhQLPELBWc == jboMLBCNcU){BEHPIiMMmF = true;}
      else if(jboMLBCNcU == FhQLPELBWc){gjUBlmtxat = true;}
      if(MdtPWPtbDF == xNpCbWQbcb){URVSRJWGJn = true;}
      else if(xNpCbWQbcb == MdtPWPtbDF){EVCHXQVkIQ = true;}
      if(tcufxMEHHV == oMhkdcMlYV){zHtUXzwyZF = true;}
      if(emclcPlyWP == giBibznaFV){hyKrNMXdYN = true;}
      if(tDxWkkkbTp == TWKFDOLgrq){lDRGjmNZFX = true;}
      while(oMhkdcMlYV == tcufxMEHHV){SYalBAFRUe = true;}
      while(giBibznaFV == giBibznaFV){eGEXDAAqOl = true;}
      while(TWKFDOLgrq == TWKFDOLgrq){LGGIOhierK = true;}
      if(YhSuWWtDhi == true){YhSuWWtDhi = false;}
      if(oQnHmOMGZb == true){oQnHmOMGZb = false;}
      if(ioVGIRBchP == true){ioVGIRBchP = false;}
      if(RetgxyPFLF == true){RetgxyPFLF = false;}
      if(EjsWgCiDRo == true){EjsWgCiDRo = false;}
      if(BEHPIiMMmF == true){BEHPIiMMmF = false;}
      if(URVSRJWGJn == true){URVSRJWGJn = false;}
      if(zHtUXzwyZF == true){zHtUXzwyZF = false;}
      if(hyKrNMXdYN == true){hyKrNMXdYN = false;}
      if(lDRGjmNZFX == true){lDRGjmNZFX = false;}
      if(fbscptJmrJ == true){fbscptJmrJ = false;}
      if(lOlhWWGcFE == true){lOlhWWGcFE = false;}
      if(krgwCwpnjj == true){krgwCwpnjj = false;}
      if(kVrBZFEgCS == true){kVrBZFEgCS = false;}
      if(DklPaXQjiM == true){DklPaXQjiM = false;}
      if(gjUBlmtxat == true){gjUBlmtxat = false;}
      if(EVCHXQVkIQ == true){EVCHXQVkIQ = false;}
      if(SYalBAFRUe == true){SYalBAFRUe = false;}
      if(eGEXDAAqOl == true){eGEXDAAqOl = false;}
      if(LGGIOhierK == true){LGGIOhierK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MOZHTDDBWM
{ 
  void cHBSibxMWS()
  { 
      bool bWXwakQoJi = false;
      bool jBhKratyZQ = false;
      bool zXQfEzBHfj = false;
      bool DVkzMcBjdb = false;
      bool OeJdbjdKRP = false;
      bool AFReJDGqqb = false;
      bool iIJYfOPiyP = false;
      bool ZJUxCTOmET = false;
      bool UqoPjxDFoI = false;
      bool VJrCsFUjxM = false;
      bool TuMCppkUco = false;
      bool nTlWGrTtni = false;
      bool LJsosPRREw = false;
      bool ydorAZdmYt = false;
      bool MicATCXUuB = false;
      bool lawOBJBWJa = false;
      bool YSPgpKdtWf = false;
      bool NfUtWbgsVp = false;
      bool qwVDJXhZpp = false;
      bool YHdyVsSwJJ = false;
      string smgeAQYpia;
      string KsJGiQkqil;
      string gitmYOXFak;
      string PpNeoKeZer;
      string RQZzaWmsee;
      string BDlbaKstGk;
      string rSOyLTedQY;
      string lKLqTPIuLC;
      string beauiLDlDe;
      string RjTtzzBbnH;
      string qIbGsqquHK;
      string ByiDINqTOz;
      string PrZlHBpRqU;
      string NgHEKTCUBr;
      string UIescSBQkl;
      string HhMnqyhpyr;
      string AZDlwTqdro;
      string KWRWeHNgIn;
      string zZfFMfUSNM;
      string kLVJqtErwJ;
      if(smgeAQYpia == qIbGsqquHK){bWXwakQoJi = true;}
      else if(qIbGsqquHK == smgeAQYpia){TuMCppkUco = true;}
      if(KsJGiQkqil == ByiDINqTOz){jBhKratyZQ = true;}
      else if(ByiDINqTOz == KsJGiQkqil){nTlWGrTtni = true;}
      if(gitmYOXFak == PrZlHBpRqU){zXQfEzBHfj = true;}
      else if(PrZlHBpRqU == gitmYOXFak){LJsosPRREw = true;}
      if(PpNeoKeZer == NgHEKTCUBr){DVkzMcBjdb = true;}
      else if(NgHEKTCUBr == PpNeoKeZer){ydorAZdmYt = true;}
      if(RQZzaWmsee == UIescSBQkl){OeJdbjdKRP = true;}
      else if(UIescSBQkl == RQZzaWmsee){MicATCXUuB = true;}
      if(BDlbaKstGk == HhMnqyhpyr){AFReJDGqqb = true;}
      else if(HhMnqyhpyr == BDlbaKstGk){lawOBJBWJa = true;}
      if(rSOyLTedQY == AZDlwTqdro){iIJYfOPiyP = true;}
      else if(AZDlwTqdro == rSOyLTedQY){YSPgpKdtWf = true;}
      if(lKLqTPIuLC == KWRWeHNgIn){ZJUxCTOmET = true;}
      if(beauiLDlDe == zZfFMfUSNM){UqoPjxDFoI = true;}
      if(RjTtzzBbnH == kLVJqtErwJ){VJrCsFUjxM = true;}
      while(KWRWeHNgIn == lKLqTPIuLC){NfUtWbgsVp = true;}
      while(zZfFMfUSNM == zZfFMfUSNM){qwVDJXhZpp = true;}
      while(kLVJqtErwJ == kLVJqtErwJ){YHdyVsSwJJ = true;}
      if(bWXwakQoJi == true){bWXwakQoJi = false;}
      if(jBhKratyZQ == true){jBhKratyZQ = false;}
      if(zXQfEzBHfj == true){zXQfEzBHfj = false;}
      if(DVkzMcBjdb == true){DVkzMcBjdb = false;}
      if(OeJdbjdKRP == true){OeJdbjdKRP = false;}
      if(AFReJDGqqb == true){AFReJDGqqb = false;}
      if(iIJYfOPiyP == true){iIJYfOPiyP = false;}
      if(ZJUxCTOmET == true){ZJUxCTOmET = false;}
      if(UqoPjxDFoI == true){UqoPjxDFoI = false;}
      if(VJrCsFUjxM == true){VJrCsFUjxM = false;}
      if(TuMCppkUco == true){TuMCppkUco = false;}
      if(nTlWGrTtni == true){nTlWGrTtni = false;}
      if(LJsosPRREw == true){LJsosPRREw = false;}
      if(ydorAZdmYt == true){ydorAZdmYt = false;}
      if(MicATCXUuB == true){MicATCXUuB = false;}
      if(lawOBJBWJa == true){lawOBJBWJa = false;}
      if(YSPgpKdtWf == true){YSPgpKdtWf = false;}
      if(NfUtWbgsVp == true){NfUtWbgsVp = false;}
      if(qwVDJXhZpp == true){qwVDJXhZpp = false;}
      if(YHdyVsSwJJ == true){YHdyVsSwJJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OYNHFUMJBL
{ 
  void RESzUtWTTR()
  { 
      bool PrcyQkLNxD = false;
      bool EmIoASMGOc = false;
      bool zESoekcVEP = false;
      bool RhWeXAbHfW = false;
      bool GoIWOIOxDl = false;
      bool kJeHsLZmSf = false;
      bool IoIhlVQdQA = false;
      bool pEaqWKuuaW = false;
      bool VfSSeIDOlM = false;
      bool ZoozOQfaks = false;
      bool rkfDuginji = false;
      bool PdMwKbVoDd = false;
      bool SCqEZBPacF = false;
      bool dTKgejzPXx = false;
      bool YPdCwwbsol = false;
      bool upXGZosacs = false;
      bool QHKdEwTeQZ = false;
      bool bGRFEDXnId = false;
      bool YWkpKmuDHo = false;
      bool pYldgQEzyA = false;
      string jXcUYUCANg;
      string OAHiHPIRNB;
      string KVnZmcBRKl;
      string nXMonntZpF;
      string OykgbNBuKq;
      string wZfQKNjCgu;
      string SjpbrqnStS;
      string UhaHlLjGxZ;
      string aFGSpOqueZ;
      string EqrtldIJok;
      string ZiBrWNyYey;
      string dcFHTMdWlc;
      string zsnUOdpfVI;
      string DaRLzrEOwb;
      string PSQfwakkZY;
      string AlXLkgugcr;
      string XRCWuDKsIb;
      string IOZJNgbHXn;
      string rEFwHRDGaS;
      string wXlDExPtks;
      if(jXcUYUCANg == ZiBrWNyYey){PrcyQkLNxD = true;}
      else if(ZiBrWNyYey == jXcUYUCANg){rkfDuginji = true;}
      if(OAHiHPIRNB == dcFHTMdWlc){EmIoASMGOc = true;}
      else if(dcFHTMdWlc == OAHiHPIRNB){PdMwKbVoDd = true;}
      if(KVnZmcBRKl == zsnUOdpfVI){zESoekcVEP = true;}
      else if(zsnUOdpfVI == KVnZmcBRKl){SCqEZBPacF = true;}
      if(nXMonntZpF == DaRLzrEOwb){RhWeXAbHfW = true;}
      else if(DaRLzrEOwb == nXMonntZpF){dTKgejzPXx = true;}
      if(OykgbNBuKq == PSQfwakkZY){GoIWOIOxDl = true;}
      else if(PSQfwakkZY == OykgbNBuKq){YPdCwwbsol = true;}
      if(wZfQKNjCgu == AlXLkgugcr){kJeHsLZmSf = true;}
      else if(AlXLkgugcr == wZfQKNjCgu){upXGZosacs = true;}
      if(SjpbrqnStS == XRCWuDKsIb){IoIhlVQdQA = true;}
      else if(XRCWuDKsIb == SjpbrqnStS){QHKdEwTeQZ = true;}
      if(UhaHlLjGxZ == IOZJNgbHXn){pEaqWKuuaW = true;}
      if(aFGSpOqueZ == rEFwHRDGaS){VfSSeIDOlM = true;}
      if(EqrtldIJok == wXlDExPtks){ZoozOQfaks = true;}
      while(IOZJNgbHXn == UhaHlLjGxZ){bGRFEDXnId = true;}
      while(rEFwHRDGaS == rEFwHRDGaS){YWkpKmuDHo = true;}
      while(wXlDExPtks == wXlDExPtks){pYldgQEzyA = true;}
      if(PrcyQkLNxD == true){PrcyQkLNxD = false;}
      if(EmIoASMGOc == true){EmIoASMGOc = false;}
      if(zESoekcVEP == true){zESoekcVEP = false;}
      if(RhWeXAbHfW == true){RhWeXAbHfW = false;}
      if(GoIWOIOxDl == true){GoIWOIOxDl = false;}
      if(kJeHsLZmSf == true){kJeHsLZmSf = false;}
      if(IoIhlVQdQA == true){IoIhlVQdQA = false;}
      if(pEaqWKuuaW == true){pEaqWKuuaW = false;}
      if(VfSSeIDOlM == true){VfSSeIDOlM = false;}
      if(ZoozOQfaks == true){ZoozOQfaks = false;}
      if(rkfDuginji == true){rkfDuginji = false;}
      if(PdMwKbVoDd == true){PdMwKbVoDd = false;}
      if(SCqEZBPacF == true){SCqEZBPacF = false;}
      if(dTKgejzPXx == true){dTKgejzPXx = false;}
      if(YPdCwwbsol == true){YPdCwwbsol = false;}
      if(upXGZosacs == true){upXGZosacs = false;}
      if(QHKdEwTeQZ == true){QHKdEwTeQZ = false;}
      if(bGRFEDXnId == true){bGRFEDXnId = false;}
      if(YWkpKmuDHo == true){YWkpKmuDHo = false;}
      if(pYldgQEzyA == true){pYldgQEzyA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DCUHQXNRNA
{ 
  void TqaQcNHYCL()
  { 
      bool XRtjXjHMgN = false;
      bool KKoiNdzfGr = false;
      bool AhJnGoQfUN = false;
      bool gNUopOJKGQ = false;
      bool CAVkALcdft = false;
      bool PhiSBoIFch = false;
      bool TaqSgxpArz = false;
      bool UnZooAMYnt = false;
      bool LlAZyydBnA = false;
      bool FDhXxbJCDC = false;
      bool VclgZbIscB = false;
      bool ciRhWhZQUi = false;
      bool SnLqsRGBrN = false;
      bool pJUkYizTAV = false;
      bool ojYmXVlzBP = false;
      bool BrhUjhQtmI = false;
      bool UHBPKSOfJm = false;
      bool hGQyshOYTW = false;
      bool eHzcMybABp = false;
      bool RFfqBhiJcF = false;
      string edhqUhRjSi;
      string bnpMEptElC;
      string fVQfdgjpjf;
      string fMPnGWseqm;
      string gttDsnktGw;
      string sQSsgINCNm;
      string ybzmDOXBFh;
      string wONyVlaNlo;
      string wojmlOsWHy;
      string JpREnFtHzd;
      string PioXAeDUXt;
      string hzPXpIqMBn;
      string UBsHYGxIJP;
      string rTNHYMAMmG;
      string KYyNPJZsNf;
      string OgGKJOpgys;
      string htKICNkIzd;
      string IdZtduDfqO;
      string fDudBKMCyK;
      string WSNsYPOpKC;
      if(edhqUhRjSi == PioXAeDUXt){XRtjXjHMgN = true;}
      else if(PioXAeDUXt == edhqUhRjSi){VclgZbIscB = true;}
      if(bnpMEptElC == hzPXpIqMBn){KKoiNdzfGr = true;}
      else if(hzPXpIqMBn == bnpMEptElC){ciRhWhZQUi = true;}
      if(fVQfdgjpjf == UBsHYGxIJP){AhJnGoQfUN = true;}
      else if(UBsHYGxIJP == fVQfdgjpjf){SnLqsRGBrN = true;}
      if(fMPnGWseqm == rTNHYMAMmG){gNUopOJKGQ = true;}
      else if(rTNHYMAMmG == fMPnGWseqm){pJUkYizTAV = true;}
      if(gttDsnktGw == KYyNPJZsNf){CAVkALcdft = true;}
      else if(KYyNPJZsNf == gttDsnktGw){ojYmXVlzBP = true;}
      if(sQSsgINCNm == OgGKJOpgys){PhiSBoIFch = true;}
      else if(OgGKJOpgys == sQSsgINCNm){BrhUjhQtmI = true;}
      if(ybzmDOXBFh == htKICNkIzd){TaqSgxpArz = true;}
      else if(htKICNkIzd == ybzmDOXBFh){UHBPKSOfJm = true;}
      if(wONyVlaNlo == IdZtduDfqO){UnZooAMYnt = true;}
      if(wojmlOsWHy == fDudBKMCyK){LlAZyydBnA = true;}
      if(JpREnFtHzd == WSNsYPOpKC){FDhXxbJCDC = true;}
      while(IdZtduDfqO == wONyVlaNlo){hGQyshOYTW = true;}
      while(fDudBKMCyK == fDudBKMCyK){eHzcMybABp = true;}
      while(WSNsYPOpKC == WSNsYPOpKC){RFfqBhiJcF = true;}
      if(XRtjXjHMgN == true){XRtjXjHMgN = false;}
      if(KKoiNdzfGr == true){KKoiNdzfGr = false;}
      if(AhJnGoQfUN == true){AhJnGoQfUN = false;}
      if(gNUopOJKGQ == true){gNUopOJKGQ = false;}
      if(CAVkALcdft == true){CAVkALcdft = false;}
      if(PhiSBoIFch == true){PhiSBoIFch = false;}
      if(TaqSgxpArz == true){TaqSgxpArz = false;}
      if(UnZooAMYnt == true){UnZooAMYnt = false;}
      if(LlAZyydBnA == true){LlAZyydBnA = false;}
      if(FDhXxbJCDC == true){FDhXxbJCDC = false;}
      if(VclgZbIscB == true){VclgZbIscB = false;}
      if(ciRhWhZQUi == true){ciRhWhZQUi = false;}
      if(SnLqsRGBrN == true){SnLqsRGBrN = false;}
      if(pJUkYizTAV == true){pJUkYizTAV = false;}
      if(ojYmXVlzBP == true){ojYmXVlzBP = false;}
      if(BrhUjhQtmI == true){BrhUjhQtmI = false;}
      if(UHBPKSOfJm == true){UHBPKSOfJm = false;}
      if(hGQyshOYTW == true){hGQyshOYTW = false;}
      if(eHzcMybABp == true){eHzcMybABp = false;}
      if(RFfqBhiJcF == true){RFfqBhiJcF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CWGLIQYFVA
{ 
  void WuaMgoesrY()
  { 
      bool ZrkmeODTEx = false;
      bool kXHZRqIjHr = false;
      bool HPyPwVMJij = false;
      bool UzlLBzpABU = false;
      bool aVMwrjpboS = false;
      bool OdRUsJtUqI = false;
      bool BsjTbklwYR = false;
      bool AHimRkDCXM = false;
      bool ekTQUpgQRq = false;
      bool FVJrShksTG = false;
      bool ytDWSGueDH = false;
      bool GqwecQYTyk = false;
      bool DUdgMeypTj = false;
      bool AKiQNkgwxO = false;
      bool tCNKkNYePC = false;
      bool IRthDdPWKm = false;
      bool IFKTHuIeQr = false;
      bool jbVjpBGTwy = false;
      bool GSaRahPANi = false;
      bool VJlKFoqtCo = false;
      string YJraNMeLGO;
      string cBWktRuOlN;
      string uohFFndYWl;
      string mmmefsnfDU;
      string DrDPkPAhkR;
      string loMPYjblVZ;
      string iGnUaoOqEA;
      string dPKRKCkRUo;
      string numFzyaWGu;
      string RBKdlwDiou;
      string BIcjmWduFV;
      string yKQfkmSiVc;
      string OqkIicFgeN;
      string yCcZmfSDRb;
      string UeRkxHjdrz;
      string dUMLgKXTBK;
      string RwQqWwgqsF;
      string UORsHiZzLb;
      string ranfjdoQsc;
      string IyCHJXOZNA;
      if(YJraNMeLGO == BIcjmWduFV){ZrkmeODTEx = true;}
      else if(BIcjmWduFV == YJraNMeLGO){ytDWSGueDH = true;}
      if(cBWktRuOlN == yKQfkmSiVc){kXHZRqIjHr = true;}
      else if(yKQfkmSiVc == cBWktRuOlN){GqwecQYTyk = true;}
      if(uohFFndYWl == OqkIicFgeN){HPyPwVMJij = true;}
      else if(OqkIicFgeN == uohFFndYWl){DUdgMeypTj = true;}
      if(mmmefsnfDU == yCcZmfSDRb){UzlLBzpABU = true;}
      else if(yCcZmfSDRb == mmmefsnfDU){AKiQNkgwxO = true;}
      if(DrDPkPAhkR == UeRkxHjdrz){aVMwrjpboS = true;}
      else if(UeRkxHjdrz == DrDPkPAhkR){tCNKkNYePC = true;}
      if(loMPYjblVZ == dUMLgKXTBK){OdRUsJtUqI = true;}
      else if(dUMLgKXTBK == loMPYjblVZ){IRthDdPWKm = true;}
      if(iGnUaoOqEA == RwQqWwgqsF){BsjTbklwYR = true;}
      else if(RwQqWwgqsF == iGnUaoOqEA){IFKTHuIeQr = true;}
      if(dPKRKCkRUo == UORsHiZzLb){AHimRkDCXM = true;}
      if(numFzyaWGu == ranfjdoQsc){ekTQUpgQRq = true;}
      if(RBKdlwDiou == IyCHJXOZNA){FVJrShksTG = true;}
      while(UORsHiZzLb == dPKRKCkRUo){jbVjpBGTwy = true;}
      while(ranfjdoQsc == ranfjdoQsc){GSaRahPANi = true;}
      while(IyCHJXOZNA == IyCHJXOZNA){VJlKFoqtCo = true;}
      if(ZrkmeODTEx == true){ZrkmeODTEx = false;}
      if(kXHZRqIjHr == true){kXHZRqIjHr = false;}
      if(HPyPwVMJij == true){HPyPwVMJij = false;}
      if(UzlLBzpABU == true){UzlLBzpABU = false;}
      if(aVMwrjpboS == true){aVMwrjpboS = false;}
      if(OdRUsJtUqI == true){OdRUsJtUqI = false;}
      if(BsjTbklwYR == true){BsjTbklwYR = false;}
      if(AHimRkDCXM == true){AHimRkDCXM = false;}
      if(ekTQUpgQRq == true){ekTQUpgQRq = false;}
      if(FVJrShksTG == true){FVJrShksTG = false;}
      if(ytDWSGueDH == true){ytDWSGueDH = false;}
      if(GqwecQYTyk == true){GqwecQYTyk = false;}
      if(DUdgMeypTj == true){DUdgMeypTj = false;}
      if(AKiQNkgwxO == true){AKiQNkgwxO = false;}
      if(tCNKkNYePC == true){tCNKkNYePC = false;}
      if(IRthDdPWKm == true){IRthDdPWKm = false;}
      if(IFKTHuIeQr == true){IFKTHuIeQr = false;}
      if(jbVjpBGTwy == true){jbVjpBGTwy = false;}
      if(GSaRahPANi == true){GSaRahPANi = false;}
      if(VJlKFoqtCo == true){VJlKFoqtCo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OPQTUBCERB
{ 
  void iEOygutAby()
  { 
      bool PADAbrUHFl = false;
      bool MqcVFieFOp = false;
      bool OcHzjkNFFy = false;
      bool gyTZLLszqk = false;
      bool SLDIPlxoUB = false;
      bool AqYQbmrEPq = false;
      bool ePBGFNWDKs = false;
      bool oeOdXDZzix = false;
      bool mYkDyoZCxX = false;
      bool SojzGDJwCC = false;
      bool PsdaMUcusY = false;
      bool NsURDGdxIP = false;
      bool nUGlazuOWU = false;
      bool scwghttJqd = false;
      bool MdJXKYTRuz = false;
      bool YLmmNtmqAM = false;
      bool YNXYfjxnjJ = false;
      bool LUGeDJLhbB = false;
      bool edSWwgoJSm = false;
      bool HDJeEyGkrZ = false;
      string PosIRzfYco;
      string QtEDmnBEoG;
      string eAqAGcJQfx;
      string rMElndJmOL;
      string MRhXWJzBiJ;
      string XkJhgPyrBn;
      string pOsexEpSOI;
      string eOocsNRTdw;
      string cHhVZHCVFX;
      string fQkZVyXCaR;
      string TglZeJufoS;
      string xdNFKhgWFp;
      string BTNqcNcPHu;
      string oPsLcwVHqP;
      string LWglZBCfOn;
      string RBwjQzSuxQ;
      string ffYsdhkCbO;
      string LYfodembRa;
      string LxASdmSItc;
      string daKZjfxnHq;
      if(PosIRzfYco == TglZeJufoS){PADAbrUHFl = true;}
      else if(TglZeJufoS == PosIRzfYco){PsdaMUcusY = true;}
      if(QtEDmnBEoG == xdNFKhgWFp){MqcVFieFOp = true;}
      else if(xdNFKhgWFp == QtEDmnBEoG){NsURDGdxIP = true;}
      if(eAqAGcJQfx == BTNqcNcPHu){OcHzjkNFFy = true;}
      else if(BTNqcNcPHu == eAqAGcJQfx){nUGlazuOWU = true;}
      if(rMElndJmOL == oPsLcwVHqP){gyTZLLszqk = true;}
      else if(oPsLcwVHqP == rMElndJmOL){scwghttJqd = true;}
      if(MRhXWJzBiJ == LWglZBCfOn){SLDIPlxoUB = true;}
      else if(LWglZBCfOn == MRhXWJzBiJ){MdJXKYTRuz = true;}
      if(XkJhgPyrBn == RBwjQzSuxQ){AqYQbmrEPq = true;}
      else if(RBwjQzSuxQ == XkJhgPyrBn){YLmmNtmqAM = true;}
      if(pOsexEpSOI == ffYsdhkCbO){ePBGFNWDKs = true;}
      else if(ffYsdhkCbO == pOsexEpSOI){YNXYfjxnjJ = true;}
      if(eOocsNRTdw == LYfodembRa){oeOdXDZzix = true;}
      if(cHhVZHCVFX == LxASdmSItc){mYkDyoZCxX = true;}
      if(fQkZVyXCaR == daKZjfxnHq){SojzGDJwCC = true;}
      while(LYfodembRa == eOocsNRTdw){LUGeDJLhbB = true;}
      while(LxASdmSItc == LxASdmSItc){edSWwgoJSm = true;}
      while(daKZjfxnHq == daKZjfxnHq){HDJeEyGkrZ = true;}
      if(PADAbrUHFl == true){PADAbrUHFl = false;}
      if(MqcVFieFOp == true){MqcVFieFOp = false;}
      if(OcHzjkNFFy == true){OcHzjkNFFy = false;}
      if(gyTZLLszqk == true){gyTZLLszqk = false;}
      if(SLDIPlxoUB == true){SLDIPlxoUB = false;}
      if(AqYQbmrEPq == true){AqYQbmrEPq = false;}
      if(ePBGFNWDKs == true){ePBGFNWDKs = false;}
      if(oeOdXDZzix == true){oeOdXDZzix = false;}
      if(mYkDyoZCxX == true){mYkDyoZCxX = false;}
      if(SojzGDJwCC == true){SojzGDJwCC = false;}
      if(PsdaMUcusY == true){PsdaMUcusY = false;}
      if(NsURDGdxIP == true){NsURDGdxIP = false;}
      if(nUGlazuOWU == true){nUGlazuOWU = false;}
      if(scwghttJqd == true){scwghttJqd = false;}
      if(MdJXKYTRuz == true){MdJXKYTRuz = false;}
      if(YLmmNtmqAM == true){YLmmNtmqAM = false;}
      if(YNXYfjxnjJ == true){YNXYfjxnjJ = false;}
      if(LUGeDJLhbB == true){LUGeDJLhbB = false;}
      if(edSWwgoJSm == true){edSWwgoJSm = false;}
      if(HDJeEyGkrZ == true){HDJeEyGkrZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MOVBGDCFKD
{ 
  void CpxiayRVYn()
  { 
      bool hGLSDXxtHr = false;
      bool GCDndfrYVX = false;
      bool pYHyTXmIKk = false;
      bool bxuKNtpxif = false;
      bool wmfpGemagm = false;
      bool CWarzIyNzf = false;
      bool jojWQJGsZj = false;
      bool puopaDrQqn = false;
      bool jMaXiEVDKE = false;
      bool ubxDwHDJYx = false;
      bool XsAxxGhkRw = false;
      bool QhWLuWOMmM = false;
      bool mDiVnNxltS = false;
      bool zhrtPqMcZb = false;
      bool VklOnNFlHY = false;
      bool sqWMJUKeJi = false;
      bool JwqywhobuE = false;
      bool KklKpCRUgZ = false;
      bool IKeVZILfju = false;
      bool ghSqSZtmRG = false;
      string zlhJKNsDgQ;
      string idgsxBgLhy;
      string sIyyzMpWap;
      string mbibkXTIMz;
      string wFwADPLbzI;
      string fqAGQqmiKx;
      string XWcpdGtEIZ;
      string gXzhCmLyuj;
      string BOWRKuabLs;
      string jjyObYbFVw;
      string UGSYaHrSDc;
      string eonauJzKfh;
      string fSsOpwZjGd;
      string LGbyOtuxpC;
      string CIXhOtwXTS;
      string ZRYmPBNEie;
      string hIMZRXMpLA;
      string OBTdfXtLAu;
      string ACPmDthnhN;
      string gpOLTtwxPp;
      if(zlhJKNsDgQ == UGSYaHrSDc){hGLSDXxtHr = true;}
      else if(UGSYaHrSDc == zlhJKNsDgQ){XsAxxGhkRw = true;}
      if(idgsxBgLhy == eonauJzKfh){GCDndfrYVX = true;}
      else if(eonauJzKfh == idgsxBgLhy){QhWLuWOMmM = true;}
      if(sIyyzMpWap == fSsOpwZjGd){pYHyTXmIKk = true;}
      else if(fSsOpwZjGd == sIyyzMpWap){mDiVnNxltS = true;}
      if(mbibkXTIMz == LGbyOtuxpC){bxuKNtpxif = true;}
      else if(LGbyOtuxpC == mbibkXTIMz){zhrtPqMcZb = true;}
      if(wFwADPLbzI == CIXhOtwXTS){wmfpGemagm = true;}
      else if(CIXhOtwXTS == wFwADPLbzI){VklOnNFlHY = true;}
      if(fqAGQqmiKx == ZRYmPBNEie){CWarzIyNzf = true;}
      else if(ZRYmPBNEie == fqAGQqmiKx){sqWMJUKeJi = true;}
      if(XWcpdGtEIZ == hIMZRXMpLA){jojWQJGsZj = true;}
      else if(hIMZRXMpLA == XWcpdGtEIZ){JwqywhobuE = true;}
      if(gXzhCmLyuj == OBTdfXtLAu){puopaDrQqn = true;}
      if(BOWRKuabLs == ACPmDthnhN){jMaXiEVDKE = true;}
      if(jjyObYbFVw == gpOLTtwxPp){ubxDwHDJYx = true;}
      while(OBTdfXtLAu == gXzhCmLyuj){KklKpCRUgZ = true;}
      while(ACPmDthnhN == ACPmDthnhN){IKeVZILfju = true;}
      while(gpOLTtwxPp == gpOLTtwxPp){ghSqSZtmRG = true;}
      if(hGLSDXxtHr == true){hGLSDXxtHr = false;}
      if(GCDndfrYVX == true){GCDndfrYVX = false;}
      if(pYHyTXmIKk == true){pYHyTXmIKk = false;}
      if(bxuKNtpxif == true){bxuKNtpxif = false;}
      if(wmfpGemagm == true){wmfpGemagm = false;}
      if(CWarzIyNzf == true){CWarzIyNzf = false;}
      if(jojWQJGsZj == true){jojWQJGsZj = false;}
      if(puopaDrQqn == true){puopaDrQqn = false;}
      if(jMaXiEVDKE == true){jMaXiEVDKE = false;}
      if(ubxDwHDJYx == true){ubxDwHDJYx = false;}
      if(XsAxxGhkRw == true){XsAxxGhkRw = false;}
      if(QhWLuWOMmM == true){QhWLuWOMmM = false;}
      if(mDiVnNxltS == true){mDiVnNxltS = false;}
      if(zhrtPqMcZb == true){zhrtPqMcZb = false;}
      if(VklOnNFlHY == true){VklOnNFlHY = false;}
      if(sqWMJUKeJi == true){sqWMJUKeJi = false;}
      if(JwqywhobuE == true){JwqywhobuE = false;}
      if(KklKpCRUgZ == true){KklKpCRUgZ = false;}
      if(IKeVZILfju == true){IKeVZILfju = false;}
      if(ghSqSZtmRG == true){ghSqSZtmRG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OGMNNNWNDD
{ 
  void PSCsXnzgUk()
  { 
      bool MCMxnJXjyJ = false;
      bool WqynaofEDK = false;
      bool fRRCSWmUio = false;
      bool iXSdAVspPh = false;
      bool BWxdbnTYus = false;
      bool bjQeJtjJeR = false;
      bool VDAIZzXUmF = false;
      bool upnVIJTnae = false;
      bool DOZoNzHnUG = false;
      bool liLyLyVnDc = false;
      bool QykpykuuVz = false;
      bool ZwiANHcKuZ = false;
      bool qjAgSMdpJK = false;
      bool mejxOEdiqb = false;
      bool DLSUfozLjE = false;
      bool ULsckgyDWk = false;
      bool HFlKMtMllJ = false;
      bool ctSSWfQfBd = false;
      bool MSFEoblGLh = false;
      bool GZMGUyZHHk = false;
      string zRpyRPhFIG;
      string ePXBUwwXQY;
      string GwwooboMrR;
      string xSppdBhqNe;
      string uoofPyPnIr;
      string WOdapDVAIo;
      string aUNqJLYhXS;
      string NEJlcQGPZp;
      string MBEAuhoOzZ;
      string fhiYDabyWE;
      string ZhPoeRFqyY;
      string wFaScZPMua;
      string VJhxmeVjhC;
      string oIrUPdkPVd;
      string cxQZcZHPwd;
      string KOCwhQzSBz;
      string uUJujmNFCy;
      string oAqRxXsITN;
      string XGnErZGwmz;
      string eRNVhInUop;
      if(zRpyRPhFIG == ZhPoeRFqyY){MCMxnJXjyJ = true;}
      else if(ZhPoeRFqyY == zRpyRPhFIG){QykpykuuVz = true;}
      if(ePXBUwwXQY == wFaScZPMua){WqynaofEDK = true;}
      else if(wFaScZPMua == ePXBUwwXQY){ZwiANHcKuZ = true;}
      if(GwwooboMrR == VJhxmeVjhC){fRRCSWmUio = true;}
      else if(VJhxmeVjhC == GwwooboMrR){qjAgSMdpJK = true;}
      if(xSppdBhqNe == oIrUPdkPVd){iXSdAVspPh = true;}
      else if(oIrUPdkPVd == xSppdBhqNe){mejxOEdiqb = true;}
      if(uoofPyPnIr == cxQZcZHPwd){BWxdbnTYus = true;}
      else if(cxQZcZHPwd == uoofPyPnIr){DLSUfozLjE = true;}
      if(WOdapDVAIo == KOCwhQzSBz){bjQeJtjJeR = true;}
      else if(KOCwhQzSBz == WOdapDVAIo){ULsckgyDWk = true;}
      if(aUNqJLYhXS == uUJujmNFCy){VDAIZzXUmF = true;}
      else if(uUJujmNFCy == aUNqJLYhXS){HFlKMtMllJ = true;}
      if(NEJlcQGPZp == oAqRxXsITN){upnVIJTnae = true;}
      if(MBEAuhoOzZ == XGnErZGwmz){DOZoNzHnUG = true;}
      if(fhiYDabyWE == eRNVhInUop){liLyLyVnDc = true;}
      while(oAqRxXsITN == NEJlcQGPZp){ctSSWfQfBd = true;}
      while(XGnErZGwmz == XGnErZGwmz){MSFEoblGLh = true;}
      while(eRNVhInUop == eRNVhInUop){GZMGUyZHHk = true;}
      if(MCMxnJXjyJ == true){MCMxnJXjyJ = false;}
      if(WqynaofEDK == true){WqynaofEDK = false;}
      if(fRRCSWmUio == true){fRRCSWmUio = false;}
      if(iXSdAVspPh == true){iXSdAVspPh = false;}
      if(BWxdbnTYus == true){BWxdbnTYus = false;}
      if(bjQeJtjJeR == true){bjQeJtjJeR = false;}
      if(VDAIZzXUmF == true){VDAIZzXUmF = false;}
      if(upnVIJTnae == true){upnVIJTnae = false;}
      if(DOZoNzHnUG == true){DOZoNzHnUG = false;}
      if(liLyLyVnDc == true){liLyLyVnDc = false;}
      if(QykpykuuVz == true){QykpykuuVz = false;}
      if(ZwiANHcKuZ == true){ZwiANHcKuZ = false;}
      if(qjAgSMdpJK == true){qjAgSMdpJK = false;}
      if(mejxOEdiqb == true){mejxOEdiqb = false;}
      if(DLSUfozLjE == true){DLSUfozLjE = false;}
      if(ULsckgyDWk == true){ULsckgyDWk = false;}
      if(HFlKMtMllJ == true){HFlKMtMllJ = false;}
      if(ctSSWfQfBd == true){ctSSWfQfBd = false;}
      if(MSFEoblGLh == true){MSFEoblGLh = false;}
      if(GZMGUyZHHk == true){GZMGUyZHHk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TRHOQQEMSF
{ 
  void LFkctCkXXC()
  { 
      bool zAjtZWocYL = false;
      bool ckQXsEDfFx = false;
      bool XDbBMVScit = false;
      bool uNlQxxsTGL = false;
      bool fUyiGKVyYk = false;
      bool ZCVTewYihD = false;
      bool ELsdQPzzZu = false;
      bool KiZtQDErtB = false;
      bool ATEyTrqRlB = false;
      bool YJlDHUaTRq = false;
      bool LVYdZqcbDa = false;
      bool qfofCkHuKX = false;
      bool XgNYWAxVmw = false;
      bool bkaDoetaXb = false;
      bool PPOKJrUFAW = false;
      bool MfIsSdHAHZ = false;
      bool tGnGzGFkqW = false;
      bool pfXhIISCOd = false;
      bool eqUQiwcgjK = false;
      bool XtTyhJaHLD = false;
      string STQQwxcJxY;
      string XXeBgiYVWr;
      string PzsKEnROht;
      string bbSgNrjSGt;
      string GRBLKdZQfL;
      string nyETWSaGLI;
      string fObDxwFxmn;
      string yFPckxxhzZ;
      string NAhVGdWzJt;
      string RdGxNqpyOO;
      string YbcqMhibhZ;
      string VrGltefFxS;
      string YGmsWUzROt;
      string GzSjBkWqJX;
      string uuQjYYWUDh;
      string LkBwoSojUq;
      string iRMnSVZWjI;
      string IouYXdoDTx;
      string ydNfhVxWti;
      string wlWRodhbQC;
      if(STQQwxcJxY == YbcqMhibhZ){zAjtZWocYL = true;}
      else if(YbcqMhibhZ == STQQwxcJxY){LVYdZqcbDa = true;}
      if(XXeBgiYVWr == VrGltefFxS){ckQXsEDfFx = true;}
      else if(VrGltefFxS == XXeBgiYVWr){qfofCkHuKX = true;}
      if(PzsKEnROht == YGmsWUzROt){XDbBMVScit = true;}
      else if(YGmsWUzROt == PzsKEnROht){XgNYWAxVmw = true;}
      if(bbSgNrjSGt == GzSjBkWqJX){uNlQxxsTGL = true;}
      else if(GzSjBkWqJX == bbSgNrjSGt){bkaDoetaXb = true;}
      if(GRBLKdZQfL == uuQjYYWUDh){fUyiGKVyYk = true;}
      else if(uuQjYYWUDh == GRBLKdZQfL){PPOKJrUFAW = true;}
      if(nyETWSaGLI == LkBwoSojUq){ZCVTewYihD = true;}
      else if(LkBwoSojUq == nyETWSaGLI){MfIsSdHAHZ = true;}
      if(fObDxwFxmn == iRMnSVZWjI){ELsdQPzzZu = true;}
      else if(iRMnSVZWjI == fObDxwFxmn){tGnGzGFkqW = true;}
      if(yFPckxxhzZ == IouYXdoDTx){KiZtQDErtB = true;}
      if(NAhVGdWzJt == ydNfhVxWti){ATEyTrqRlB = true;}
      if(RdGxNqpyOO == wlWRodhbQC){YJlDHUaTRq = true;}
      while(IouYXdoDTx == yFPckxxhzZ){pfXhIISCOd = true;}
      while(ydNfhVxWti == ydNfhVxWti){eqUQiwcgjK = true;}
      while(wlWRodhbQC == wlWRodhbQC){XtTyhJaHLD = true;}
      if(zAjtZWocYL == true){zAjtZWocYL = false;}
      if(ckQXsEDfFx == true){ckQXsEDfFx = false;}
      if(XDbBMVScit == true){XDbBMVScit = false;}
      if(uNlQxxsTGL == true){uNlQxxsTGL = false;}
      if(fUyiGKVyYk == true){fUyiGKVyYk = false;}
      if(ZCVTewYihD == true){ZCVTewYihD = false;}
      if(ELsdQPzzZu == true){ELsdQPzzZu = false;}
      if(KiZtQDErtB == true){KiZtQDErtB = false;}
      if(ATEyTrqRlB == true){ATEyTrqRlB = false;}
      if(YJlDHUaTRq == true){YJlDHUaTRq = false;}
      if(LVYdZqcbDa == true){LVYdZqcbDa = false;}
      if(qfofCkHuKX == true){qfofCkHuKX = false;}
      if(XgNYWAxVmw == true){XgNYWAxVmw = false;}
      if(bkaDoetaXb == true){bkaDoetaXb = false;}
      if(PPOKJrUFAW == true){PPOKJrUFAW = false;}
      if(MfIsSdHAHZ == true){MfIsSdHAHZ = false;}
      if(tGnGzGFkqW == true){tGnGzGFkqW = false;}
      if(pfXhIISCOd == true){pfXhIISCOd = false;}
      if(eqUQiwcgjK == true){eqUQiwcgjK = false;}
      if(XtTyhJaHLD == true){XtTyhJaHLD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KAGMISTNAN
{ 
  void gYNxdFfGmm()
  { 
      bool GUqWIDTELb = false;
      bool WJctOUegNj = false;
      bool jkhFmmthrm = false;
      bool aZuhKtuseO = false;
      bool DadoZbaKga = false;
      bool IRIRRUmkiV = false;
      bool IlMXAwOujT = false;
      bool YlBygIHrfL = false;
      bool MjBReJRcPo = false;
      bool GKKJFROFod = false;
      bool NeZMBVPKkI = false;
      bool NtFXIYjusp = false;
      bool elftNObrrP = false;
      bool tCDBxgJoPI = false;
      bool tHqGbMFlAg = false;
      bool gTLyzazfym = false;
      bool tXRVOLpDZa = false;
      bool PuejwXtZRB = false;
      bool JoqLhapFCV = false;
      bool hcpcNWoVqQ = false;
      string ZEOAsGFGMa;
      string JmbUwmKRAr;
      string FbahySNQSc;
      string ZlmgHORPpC;
      string GlTzSQJdqg;
      string jiIluydfBa;
      string romiBXztMh;
      string UuaylSIaOh;
      string IiZkrqdBlI;
      string jkNOJRyjyu;
      string RPRJMoHJzb;
      string oDRTSJPBqK;
      string tyHDxigLnU;
      string TYcSQsRQYD;
      string iTBKTgTtwA;
      string CxrmBSHNLd;
      string HuUeHQayDZ;
      string qzcnaZwxjQ;
      string OmPnRWfoQx;
      string lDEuunyVCC;
      if(ZEOAsGFGMa == RPRJMoHJzb){GUqWIDTELb = true;}
      else if(RPRJMoHJzb == ZEOAsGFGMa){NeZMBVPKkI = true;}
      if(JmbUwmKRAr == oDRTSJPBqK){WJctOUegNj = true;}
      else if(oDRTSJPBqK == JmbUwmKRAr){NtFXIYjusp = true;}
      if(FbahySNQSc == tyHDxigLnU){jkhFmmthrm = true;}
      else if(tyHDxigLnU == FbahySNQSc){elftNObrrP = true;}
      if(ZlmgHORPpC == TYcSQsRQYD){aZuhKtuseO = true;}
      else if(TYcSQsRQYD == ZlmgHORPpC){tCDBxgJoPI = true;}
      if(GlTzSQJdqg == iTBKTgTtwA){DadoZbaKga = true;}
      else if(iTBKTgTtwA == GlTzSQJdqg){tHqGbMFlAg = true;}
      if(jiIluydfBa == CxrmBSHNLd){IRIRRUmkiV = true;}
      else if(CxrmBSHNLd == jiIluydfBa){gTLyzazfym = true;}
      if(romiBXztMh == HuUeHQayDZ){IlMXAwOujT = true;}
      else if(HuUeHQayDZ == romiBXztMh){tXRVOLpDZa = true;}
      if(UuaylSIaOh == qzcnaZwxjQ){YlBygIHrfL = true;}
      if(IiZkrqdBlI == OmPnRWfoQx){MjBReJRcPo = true;}
      if(jkNOJRyjyu == lDEuunyVCC){GKKJFROFod = true;}
      while(qzcnaZwxjQ == UuaylSIaOh){PuejwXtZRB = true;}
      while(OmPnRWfoQx == OmPnRWfoQx){JoqLhapFCV = true;}
      while(lDEuunyVCC == lDEuunyVCC){hcpcNWoVqQ = true;}
      if(GUqWIDTELb == true){GUqWIDTELb = false;}
      if(WJctOUegNj == true){WJctOUegNj = false;}
      if(jkhFmmthrm == true){jkhFmmthrm = false;}
      if(aZuhKtuseO == true){aZuhKtuseO = false;}
      if(DadoZbaKga == true){DadoZbaKga = false;}
      if(IRIRRUmkiV == true){IRIRRUmkiV = false;}
      if(IlMXAwOujT == true){IlMXAwOujT = false;}
      if(YlBygIHrfL == true){YlBygIHrfL = false;}
      if(MjBReJRcPo == true){MjBReJRcPo = false;}
      if(GKKJFROFod == true){GKKJFROFod = false;}
      if(NeZMBVPKkI == true){NeZMBVPKkI = false;}
      if(NtFXIYjusp == true){NtFXIYjusp = false;}
      if(elftNObrrP == true){elftNObrrP = false;}
      if(tCDBxgJoPI == true){tCDBxgJoPI = false;}
      if(tHqGbMFlAg == true){tHqGbMFlAg = false;}
      if(gTLyzazfym == true){gTLyzazfym = false;}
      if(tXRVOLpDZa == true){tXRVOLpDZa = false;}
      if(PuejwXtZRB == true){PuejwXtZRB = false;}
      if(JoqLhapFCV == true){JoqLhapFCV = false;}
      if(hcpcNWoVqQ == true){hcpcNWoVqQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class INXLOTKAZL
{ 
  void XXqBkQNqrP()
  { 
      bool wRQnPXuZhD = false;
      bool JLXpnkZmpq = false;
      bool zwYkYQUAks = false;
      bool lusmGrmxzC = false;
      bool ubSJKlcCQL = false;
      bool coswiArfOy = false;
      bool DunnRNSjju = false;
      bool xcnnwWcPZl = false;
      bool mRiZQxCwDF = false;
      bool AHhAzzmerx = false;
      bool TrRVOAAFAL = false;
      bool WcFcLkMOWT = false;
      bool LVfeuotnnx = false;
      bool jyXcStANKQ = false;
      bool wxwriWCFnO = false;
      bool mXHXlxLmZY = false;
      bool FMQCaXFbKQ = false;
      bool kzDGXNZnuY = false;
      bool mozZJLpAqU = false;
      bool hMmlKjfsQK = false;
      string FtjxiCOwJf;
      string iLXLnRnrhL;
      string rzuZFiykSi;
      string xMCXFVfbYu;
      string OoHYhcuFIz;
      string dajZcGzJqA;
      string EcdahVIzFS;
      string kMTmxDrWrc;
      string mscSEVccuz;
      string VVkXqkLfqL;
      string TwzpORHxbZ;
      string OcRNNKAKWL;
      string sfDGwOauuL;
      string qLefIqslEm;
      string OeAVksEWKf;
      string kBJeSnsssz;
      string pLCQhCxlFW;
      string QNFixOegVC;
      string KEkOZpCAMT;
      string yAsFxDcinh;
      if(FtjxiCOwJf == TwzpORHxbZ){wRQnPXuZhD = true;}
      else if(TwzpORHxbZ == FtjxiCOwJf){TrRVOAAFAL = true;}
      if(iLXLnRnrhL == OcRNNKAKWL){JLXpnkZmpq = true;}
      else if(OcRNNKAKWL == iLXLnRnrhL){WcFcLkMOWT = true;}
      if(rzuZFiykSi == sfDGwOauuL){zwYkYQUAks = true;}
      else if(sfDGwOauuL == rzuZFiykSi){LVfeuotnnx = true;}
      if(xMCXFVfbYu == qLefIqslEm){lusmGrmxzC = true;}
      else if(qLefIqslEm == xMCXFVfbYu){jyXcStANKQ = true;}
      if(OoHYhcuFIz == OeAVksEWKf){ubSJKlcCQL = true;}
      else if(OeAVksEWKf == OoHYhcuFIz){wxwriWCFnO = true;}
      if(dajZcGzJqA == kBJeSnsssz){coswiArfOy = true;}
      else if(kBJeSnsssz == dajZcGzJqA){mXHXlxLmZY = true;}
      if(EcdahVIzFS == pLCQhCxlFW){DunnRNSjju = true;}
      else if(pLCQhCxlFW == EcdahVIzFS){FMQCaXFbKQ = true;}
      if(kMTmxDrWrc == QNFixOegVC){xcnnwWcPZl = true;}
      if(mscSEVccuz == KEkOZpCAMT){mRiZQxCwDF = true;}
      if(VVkXqkLfqL == yAsFxDcinh){AHhAzzmerx = true;}
      while(QNFixOegVC == kMTmxDrWrc){kzDGXNZnuY = true;}
      while(KEkOZpCAMT == KEkOZpCAMT){mozZJLpAqU = true;}
      while(yAsFxDcinh == yAsFxDcinh){hMmlKjfsQK = true;}
      if(wRQnPXuZhD == true){wRQnPXuZhD = false;}
      if(JLXpnkZmpq == true){JLXpnkZmpq = false;}
      if(zwYkYQUAks == true){zwYkYQUAks = false;}
      if(lusmGrmxzC == true){lusmGrmxzC = false;}
      if(ubSJKlcCQL == true){ubSJKlcCQL = false;}
      if(coswiArfOy == true){coswiArfOy = false;}
      if(DunnRNSjju == true){DunnRNSjju = false;}
      if(xcnnwWcPZl == true){xcnnwWcPZl = false;}
      if(mRiZQxCwDF == true){mRiZQxCwDF = false;}
      if(AHhAzzmerx == true){AHhAzzmerx = false;}
      if(TrRVOAAFAL == true){TrRVOAAFAL = false;}
      if(WcFcLkMOWT == true){WcFcLkMOWT = false;}
      if(LVfeuotnnx == true){LVfeuotnnx = false;}
      if(jyXcStANKQ == true){jyXcStANKQ = false;}
      if(wxwriWCFnO == true){wxwriWCFnO = false;}
      if(mXHXlxLmZY == true){mXHXlxLmZY = false;}
      if(FMQCaXFbKQ == true){FMQCaXFbKQ = false;}
      if(kzDGXNZnuY == true){kzDGXNZnuY = false;}
      if(mozZJLpAqU == true){mozZJLpAqU = false;}
      if(hMmlKjfsQK == true){hMmlKjfsQK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LXTFAFSVPV
{ 
  void KkqLotcmaC()
  { 
      bool NDHPcMVkSl = false;
      bool IqrXGxuoAE = false;
      bool XGUAuXgdRk = false;
      bool XUOkdGJLrF = false;
      bool fxdBitkmHl = false;
      bool tYhEcHiGUE = false;
      bool frShNmcGsA = false;
      bool njxtYZbSRA = false;
      bool lsWepylKHW = false;
      bool XCpmZmdunu = false;
      bool QesHyKbneD = false;
      bool ePoTSlVmrO = false;
      bool BSyWbksJTk = false;
      bool ufeWjHzOgf = false;
      bool VyeEqHNVUn = false;
      bool RpDYtxfWeM = false;
      bool QRTtHyjRjK = false;
      bool lGGLrDmteT = false;
      bool XWofSEcGcl = false;
      bool bciUODdkwr = false;
      string HYiGPXFAqE;
      string QfsuAuTROg;
      string lXEUpfhoHO;
      string HZeSSfsKOc;
      string lfPeZTcBqn;
      string myskdjTOQj;
      string pPrbxqAacT;
      string BICktFIZtV;
      string CgxSbIfsni;
      string LesdmWnmhi;
      string SBYXmduHqY;
      string atTtgJRYAn;
      string KGmtIVPYyX;
      string RUqLDAHZfy;
      string NXCPHQLywd;
      string EPmtXLOeOQ;
      string OWJTGGDHqg;
      string BrsBalDWlq;
      string KQbUSChxmq;
      string lcKOjpOiIB;
      if(HYiGPXFAqE == SBYXmduHqY){NDHPcMVkSl = true;}
      else if(SBYXmduHqY == HYiGPXFAqE){QesHyKbneD = true;}
      if(QfsuAuTROg == atTtgJRYAn){IqrXGxuoAE = true;}
      else if(atTtgJRYAn == QfsuAuTROg){ePoTSlVmrO = true;}
      if(lXEUpfhoHO == KGmtIVPYyX){XGUAuXgdRk = true;}
      else if(KGmtIVPYyX == lXEUpfhoHO){BSyWbksJTk = true;}
      if(HZeSSfsKOc == RUqLDAHZfy){XUOkdGJLrF = true;}
      else if(RUqLDAHZfy == HZeSSfsKOc){ufeWjHzOgf = true;}
      if(lfPeZTcBqn == NXCPHQLywd){fxdBitkmHl = true;}
      else if(NXCPHQLywd == lfPeZTcBqn){VyeEqHNVUn = true;}
      if(myskdjTOQj == EPmtXLOeOQ){tYhEcHiGUE = true;}
      else if(EPmtXLOeOQ == myskdjTOQj){RpDYtxfWeM = true;}
      if(pPrbxqAacT == OWJTGGDHqg){frShNmcGsA = true;}
      else if(OWJTGGDHqg == pPrbxqAacT){QRTtHyjRjK = true;}
      if(BICktFIZtV == BrsBalDWlq){njxtYZbSRA = true;}
      if(CgxSbIfsni == KQbUSChxmq){lsWepylKHW = true;}
      if(LesdmWnmhi == lcKOjpOiIB){XCpmZmdunu = true;}
      while(BrsBalDWlq == BICktFIZtV){lGGLrDmteT = true;}
      while(KQbUSChxmq == KQbUSChxmq){XWofSEcGcl = true;}
      while(lcKOjpOiIB == lcKOjpOiIB){bciUODdkwr = true;}
      if(NDHPcMVkSl == true){NDHPcMVkSl = false;}
      if(IqrXGxuoAE == true){IqrXGxuoAE = false;}
      if(XGUAuXgdRk == true){XGUAuXgdRk = false;}
      if(XUOkdGJLrF == true){XUOkdGJLrF = false;}
      if(fxdBitkmHl == true){fxdBitkmHl = false;}
      if(tYhEcHiGUE == true){tYhEcHiGUE = false;}
      if(frShNmcGsA == true){frShNmcGsA = false;}
      if(njxtYZbSRA == true){njxtYZbSRA = false;}
      if(lsWepylKHW == true){lsWepylKHW = false;}
      if(XCpmZmdunu == true){XCpmZmdunu = false;}
      if(QesHyKbneD == true){QesHyKbneD = false;}
      if(ePoTSlVmrO == true){ePoTSlVmrO = false;}
      if(BSyWbksJTk == true){BSyWbksJTk = false;}
      if(ufeWjHzOgf == true){ufeWjHzOgf = false;}
      if(VyeEqHNVUn == true){VyeEqHNVUn = false;}
      if(RpDYtxfWeM == true){RpDYtxfWeM = false;}
      if(QRTtHyjRjK == true){QRTtHyjRjK = false;}
      if(lGGLrDmteT == true){lGGLrDmteT = false;}
      if(XWofSEcGcl == true){XWofSEcGcl = false;}
      if(bciUODdkwr == true){bciUODdkwr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TBEJBWEWWX
{ 
  void FdKrKuAZOK()
  { 
      bool mckJgJISLP = false;
      bool JfWYUokTzO = false;
      bool IFEfHDoDDp = false;
      bool nNRGqurTsr = false;
      bool TBEgqLdIAC = false;
      bool xlOChhXEBc = false;
      bool TEOUbuOPgZ = false;
      bool xQaHtHBWow = false;
      bool YgDBsByPYJ = false;
      bool WmSPXPliEu = false;
      bool wNbaEfLHHa = false;
      bool fBPEEmAMbZ = false;
      bool wzqWCJyKid = false;
      bool URSszKEcwN = false;
      bool pqHycVXNLk = false;
      bool PZHdzxWEXu = false;
      bool gAXdFOhVFs = false;
      bool hXPNjErssf = false;
      bool kkzxOuKnsC = false;
      bool nAEBfoSdrO = false;
      string GJBhfUNxuY;
      string ozpfWFGkTp;
      string BwgbtOlfyS;
      string EkFpmFOYgu;
      string UVuaLaDdGm;
      string tFdFgJbZmR;
      string igzcUDtzsQ;
      string qgDXVfAGPT;
      string KHZKXzHAIc;
      string dnlPMmVSFH;
      string fEkowNCFiB;
      string JVJTGaHnFV;
      string wtpQlCumLh;
      string JgAImGVjOJ;
      string wBQHSIdRJk;
      string fhNjLlOUDs;
      string SOtBqbUBgA;
      string EWYuYuchxd;
      string XcdZBbTPxA;
      string rBgUqhGOQp;
      if(GJBhfUNxuY == fEkowNCFiB){mckJgJISLP = true;}
      else if(fEkowNCFiB == GJBhfUNxuY){wNbaEfLHHa = true;}
      if(ozpfWFGkTp == JVJTGaHnFV){JfWYUokTzO = true;}
      else if(JVJTGaHnFV == ozpfWFGkTp){fBPEEmAMbZ = true;}
      if(BwgbtOlfyS == wtpQlCumLh){IFEfHDoDDp = true;}
      else if(wtpQlCumLh == BwgbtOlfyS){wzqWCJyKid = true;}
      if(EkFpmFOYgu == JgAImGVjOJ){nNRGqurTsr = true;}
      else if(JgAImGVjOJ == EkFpmFOYgu){URSszKEcwN = true;}
      if(UVuaLaDdGm == wBQHSIdRJk){TBEgqLdIAC = true;}
      else if(wBQHSIdRJk == UVuaLaDdGm){pqHycVXNLk = true;}
      if(tFdFgJbZmR == fhNjLlOUDs){xlOChhXEBc = true;}
      else if(fhNjLlOUDs == tFdFgJbZmR){PZHdzxWEXu = true;}
      if(igzcUDtzsQ == SOtBqbUBgA){TEOUbuOPgZ = true;}
      else if(SOtBqbUBgA == igzcUDtzsQ){gAXdFOhVFs = true;}
      if(qgDXVfAGPT == EWYuYuchxd){xQaHtHBWow = true;}
      if(KHZKXzHAIc == XcdZBbTPxA){YgDBsByPYJ = true;}
      if(dnlPMmVSFH == rBgUqhGOQp){WmSPXPliEu = true;}
      while(EWYuYuchxd == qgDXVfAGPT){hXPNjErssf = true;}
      while(XcdZBbTPxA == XcdZBbTPxA){kkzxOuKnsC = true;}
      while(rBgUqhGOQp == rBgUqhGOQp){nAEBfoSdrO = true;}
      if(mckJgJISLP == true){mckJgJISLP = false;}
      if(JfWYUokTzO == true){JfWYUokTzO = false;}
      if(IFEfHDoDDp == true){IFEfHDoDDp = false;}
      if(nNRGqurTsr == true){nNRGqurTsr = false;}
      if(TBEgqLdIAC == true){TBEgqLdIAC = false;}
      if(xlOChhXEBc == true){xlOChhXEBc = false;}
      if(TEOUbuOPgZ == true){TEOUbuOPgZ = false;}
      if(xQaHtHBWow == true){xQaHtHBWow = false;}
      if(YgDBsByPYJ == true){YgDBsByPYJ = false;}
      if(WmSPXPliEu == true){WmSPXPliEu = false;}
      if(wNbaEfLHHa == true){wNbaEfLHHa = false;}
      if(fBPEEmAMbZ == true){fBPEEmAMbZ = false;}
      if(wzqWCJyKid == true){wzqWCJyKid = false;}
      if(URSszKEcwN == true){URSszKEcwN = false;}
      if(pqHycVXNLk == true){pqHycVXNLk = false;}
      if(PZHdzxWEXu == true){PZHdzxWEXu = false;}
      if(gAXdFOhVFs == true){gAXdFOhVFs = false;}
      if(hXPNjErssf == true){hXPNjErssf = false;}
      if(kkzxOuKnsC == true){kkzxOuKnsC = false;}
      if(nAEBfoSdrO == true){nAEBfoSdrO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WKZAYMQHZJ
{ 
  void pNlWiPDeuf()
  { 
      bool zaZUUcYKRW = false;
      bool pdhTXlDzAM = false;
      bool VyJuZRghyY = false;
      bool doVnxCtwEg = false;
      bool xPagEkJqRJ = false;
      bool qhfzIBReuD = false;
      bool uqLrsAIsVV = false;
      bool rHuSPGWbpn = false;
      bool HpQohuJVew = false;
      bool kOAAlFDhmE = false;
      bool bPUwRimMiC = false;
      bool dooGuEZWJy = false;
      bool qlOZjdGtgJ = false;
      bool ConlLrVUWz = false;
      bool IwmbRuYtFg = false;
      bool egYoMoAtLn = false;
      bool crfZAoBDtD = false;
      bool iFzKptzmIo = false;
      bool EMoAdUPyYV = false;
      bool qbIiWPQMab = false;
      string meZpPGgSgC;
      string mwGDXkyNsM;
      string VdMlIgWfpn;
      string InyfJbcxKN;
      string powOzYPlAc;
      string syGOhIRnhi;
      string jAcrsyyasw;
      string HBCfWfhymi;
      string QjfMuKgjxA;
      string JoPbcpMDUA;
      string aorEUruarC;
      string aTAyRzTPxi;
      string RNcrmSkaCf;
      string SedmIbqbrC;
      string OGruZonQKc;
      string VxFkhMLAQC;
      string GUYLiupNpo;
      string IrXuTLVhSx;
      string dUQYKVZrEu;
      string PqKowthfLe;
      if(meZpPGgSgC == aorEUruarC){zaZUUcYKRW = true;}
      else if(aorEUruarC == meZpPGgSgC){bPUwRimMiC = true;}
      if(mwGDXkyNsM == aTAyRzTPxi){pdhTXlDzAM = true;}
      else if(aTAyRzTPxi == mwGDXkyNsM){dooGuEZWJy = true;}
      if(VdMlIgWfpn == RNcrmSkaCf){VyJuZRghyY = true;}
      else if(RNcrmSkaCf == VdMlIgWfpn){qlOZjdGtgJ = true;}
      if(InyfJbcxKN == SedmIbqbrC){doVnxCtwEg = true;}
      else if(SedmIbqbrC == InyfJbcxKN){ConlLrVUWz = true;}
      if(powOzYPlAc == OGruZonQKc){xPagEkJqRJ = true;}
      else if(OGruZonQKc == powOzYPlAc){IwmbRuYtFg = true;}
      if(syGOhIRnhi == VxFkhMLAQC){qhfzIBReuD = true;}
      else if(VxFkhMLAQC == syGOhIRnhi){egYoMoAtLn = true;}
      if(jAcrsyyasw == GUYLiupNpo){uqLrsAIsVV = true;}
      else if(GUYLiupNpo == jAcrsyyasw){crfZAoBDtD = true;}
      if(HBCfWfhymi == IrXuTLVhSx){rHuSPGWbpn = true;}
      if(QjfMuKgjxA == dUQYKVZrEu){HpQohuJVew = true;}
      if(JoPbcpMDUA == PqKowthfLe){kOAAlFDhmE = true;}
      while(IrXuTLVhSx == HBCfWfhymi){iFzKptzmIo = true;}
      while(dUQYKVZrEu == dUQYKVZrEu){EMoAdUPyYV = true;}
      while(PqKowthfLe == PqKowthfLe){qbIiWPQMab = true;}
      if(zaZUUcYKRW == true){zaZUUcYKRW = false;}
      if(pdhTXlDzAM == true){pdhTXlDzAM = false;}
      if(VyJuZRghyY == true){VyJuZRghyY = false;}
      if(doVnxCtwEg == true){doVnxCtwEg = false;}
      if(xPagEkJqRJ == true){xPagEkJqRJ = false;}
      if(qhfzIBReuD == true){qhfzIBReuD = false;}
      if(uqLrsAIsVV == true){uqLrsAIsVV = false;}
      if(rHuSPGWbpn == true){rHuSPGWbpn = false;}
      if(HpQohuJVew == true){HpQohuJVew = false;}
      if(kOAAlFDhmE == true){kOAAlFDhmE = false;}
      if(bPUwRimMiC == true){bPUwRimMiC = false;}
      if(dooGuEZWJy == true){dooGuEZWJy = false;}
      if(qlOZjdGtgJ == true){qlOZjdGtgJ = false;}
      if(ConlLrVUWz == true){ConlLrVUWz = false;}
      if(IwmbRuYtFg == true){IwmbRuYtFg = false;}
      if(egYoMoAtLn == true){egYoMoAtLn = false;}
      if(crfZAoBDtD == true){crfZAoBDtD = false;}
      if(iFzKptzmIo == true){iFzKptzmIo = false;}
      if(EMoAdUPyYV == true){EMoAdUPyYV = false;}
      if(qbIiWPQMab == true){qbIiWPQMab = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJQGUMUJVS
{ 
  void zkjqMzoerV()
  { 
      bool yChFsfoDhy = false;
      bool NaShRoCZyP = false;
      bool KhxFsABMjC = false;
      bool oNLRiSiPCI = false;
      bool qZZUAzRiei = false;
      bool PlXPcQFbLr = false;
      bool dcTeIAPByz = false;
      bool GmXpXjHbEt = false;
      bool iSgAlDounS = false;
      bool MGEKeOFtLA = false;
      bool jQkfccNhrs = false;
      bool IcWQILuTrF = false;
      bool KTMelAhNLJ = false;
      bool dNPEKSgBXJ = false;
      bool oHDuJjjmCT = false;
      bool SlBGoPDFtb = false;
      bool tAWhOuNRGo = false;
      bool dtwiPDQRVC = false;
      bool PuLqprLJPu = false;
      bool PaHuOokUfN = false;
      string JtnSmNnfZi;
      string ffjTegcPWG;
      string VlQBesITbg;
      string LTzJeSpYgb;
      string TxtnxYNuzR;
      string cBpODWcmns;
      string FUEsXMfaoM;
      string pDhumYrbDF;
      string fMTKEKckGH;
      string oCkmVzrBQj;
      string rmFmaYSuad;
      string eBjhNrAsnM;
      string jtThWnSuYm;
      string gpLTMsHgje;
      string qhKcbnSCZd;
      string zzMDAySXPm;
      string FXVmxnoQUU;
      string kSJIVBjqFh;
      string UQUungdHSO;
      string ajQxYSMWfn;
      if(JtnSmNnfZi == rmFmaYSuad){yChFsfoDhy = true;}
      else if(rmFmaYSuad == JtnSmNnfZi){jQkfccNhrs = true;}
      if(ffjTegcPWG == eBjhNrAsnM){NaShRoCZyP = true;}
      else if(eBjhNrAsnM == ffjTegcPWG){IcWQILuTrF = true;}
      if(VlQBesITbg == jtThWnSuYm){KhxFsABMjC = true;}
      else if(jtThWnSuYm == VlQBesITbg){KTMelAhNLJ = true;}
      if(LTzJeSpYgb == gpLTMsHgje){oNLRiSiPCI = true;}
      else if(gpLTMsHgje == LTzJeSpYgb){dNPEKSgBXJ = true;}
      if(TxtnxYNuzR == qhKcbnSCZd){qZZUAzRiei = true;}
      else if(qhKcbnSCZd == TxtnxYNuzR){oHDuJjjmCT = true;}
      if(cBpODWcmns == zzMDAySXPm){PlXPcQFbLr = true;}
      else if(zzMDAySXPm == cBpODWcmns){SlBGoPDFtb = true;}
      if(FUEsXMfaoM == FXVmxnoQUU){dcTeIAPByz = true;}
      else if(FXVmxnoQUU == FUEsXMfaoM){tAWhOuNRGo = true;}
      if(pDhumYrbDF == kSJIVBjqFh){GmXpXjHbEt = true;}
      if(fMTKEKckGH == UQUungdHSO){iSgAlDounS = true;}
      if(oCkmVzrBQj == ajQxYSMWfn){MGEKeOFtLA = true;}
      while(kSJIVBjqFh == pDhumYrbDF){dtwiPDQRVC = true;}
      while(UQUungdHSO == UQUungdHSO){PuLqprLJPu = true;}
      while(ajQxYSMWfn == ajQxYSMWfn){PaHuOokUfN = true;}
      if(yChFsfoDhy == true){yChFsfoDhy = false;}
      if(NaShRoCZyP == true){NaShRoCZyP = false;}
      if(KhxFsABMjC == true){KhxFsABMjC = false;}
      if(oNLRiSiPCI == true){oNLRiSiPCI = false;}
      if(qZZUAzRiei == true){qZZUAzRiei = false;}
      if(PlXPcQFbLr == true){PlXPcQFbLr = false;}
      if(dcTeIAPByz == true){dcTeIAPByz = false;}
      if(GmXpXjHbEt == true){GmXpXjHbEt = false;}
      if(iSgAlDounS == true){iSgAlDounS = false;}
      if(MGEKeOFtLA == true){MGEKeOFtLA = false;}
      if(jQkfccNhrs == true){jQkfccNhrs = false;}
      if(IcWQILuTrF == true){IcWQILuTrF = false;}
      if(KTMelAhNLJ == true){KTMelAhNLJ = false;}
      if(dNPEKSgBXJ == true){dNPEKSgBXJ = false;}
      if(oHDuJjjmCT == true){oHDuJjjmCT = false;}
      if(SlBGoPDFtb == true){SlBGoPDFtb = false;}
      if(tAWhOuNRGo == true){tAWhOuNRGo = false;}
      if(dtwiPDQRVC == true){dtwiPDQRVC = false;}
      if(PuLqprLJPu == true){PuLqprLJPu = false;}
      if(PaHuOokUfN == true){PaHuOokUfN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XFGGOSANMP
{ 
  void ZRTEfWEenX()
  { 
      bool GckmrAbuZE = false;
      bool aTJCEtwqet = false;
      bool ofDOtJASCQ = false;
      bool RAkAtGYNIN = false;
      bool ZjxJrjtXch = false;
      bool sDNWoZYVri = false;
      bool AJsIlahIHx = false;
      bool ViiQUFitWJ = false;
      bool OboTWOlOLU = false;
      bool hDVYNPpnXQ = false;
      bool BkPfMKTwBj = false;
      bool peyhTXUYlW = false;
      bool nTxmPRNJDE = false;
      bool OuVFIcLJHL = false;
      bool upMadDEmEo = false;
      bool uRBAchncPt = false;
      bool xJrxVuIsZq = false;
      bool LKRZbxHVJL = false;
      bool NZFNIxsVcZ = false;
      bool oisNOkxPFh = false;
      string dMxtryrrBa;
      string thztgNQywM;
      string nLaClFgofV;
      string HGgsqDowyc;
      string lKSuFArVsq;
      string DiTKESluHm;
      string QDLeSnBFCc;
      string XTzSZcsexl;
      string NLuoRXmWoY;
      string QsoLLizmbR;
      string ymSPSjjAja;
      string ZHyVZFHWMu;
      string AeQdLedmHp;
      string dFDfmarfVh;
      string nmlNyJuTlF;
      string bbZgQTVnEn;
      string FxrswUDShz;
      string NbAeGMrCeB;
      string iKABOBeWOS;
      string EDahcptrRd;
      if(dMxtryrrBa == ymSPSjjAja){GckmrAbuZE = true;}
      else if(ymSPSjjAja == dMxtryrrBa){BkPfMKTwBj = true;}
      if(thztgNQywM == ZHyVZFHWMu){aTJCEtwqet = true;}
      else if(ZHyVZFHWMu == thztgNQywM){peyhTXUYlW = true;}
      if(nLaClFgofV == AeQdLedmHp){ofDOtJASCQ = true;}
      else if(AeQdLedmHp == nLaClFgofV){nTxmPRNJDE = true;}
      if(HGgsqDowyc == dFDfmarfVh){RAkAtGYNIN = true;}
      else if(dFDfmarfVh == HGgsqDowyc){OuVFIcLJHL = true;}
      if(lKSuFArVsq == nmlNyJuTlF){ZjxJrjtXch = true;}
      else if(nmlNyJuTlF == lKSuFArVsq){upMadDEmEo = true;}
      if(DiTKESluHm == bbZgQTVnEn){sDNWoZYVri = true;}
      else if(bbZgQTVnEn == DiTKESluHm){uRBAchncPt = true;}
      if(QDLeSnBFCc == FxrswUDShz){AJsIlahIHx = true;}
      else if(FxrswUDShz == QDLeSnBFCc){xJrxVuIsZq = true;}
      if(XTzSZcsexl == NbAeGMrCeB){ViiQUFitWJ = true;}
      if(NLuoRXmWoY == iKABOBeWOS){OboTWOlOLU = true;}
      if(QsoLLizmbR == EDahcptrRd){hDVYNPpnXQ = true;}
      while(NbAeGMrCeB == XTzSZcsexl){LKRZbxHVJL = true;}
      while(iKABOBeWOS == iKABOBeWOS){NZFNIxsVcZ = true;}
      while(EDahcptrRd == EDahcptrRd){oisNOkxPFh = true;}
      if(GckmrAbuZE == true){GckmrAbuZE = false;}
      if(aTJCEtwqet == true){aTJCEtwqet = false;}
      if(ofDOtJASCQ == true){ofDOtJASCQ = false;}
      if(RAkAtGYNIN == true){RAkAtGYNIN = false;}
      if(ZjxJrjtXch == true){ZjxJrjtXch = false;}
      if(sDNWoZYVri == true){sDNWoZYVri = false;}
      if(AJsIlahIHx == true){AJsIlahIHx = false;}
      if(ViiQUFitWJ == true){ViiQUFitWJ = false;}
      if(OboTWOlOLU == true){OboTWOlOLU = false;}
      if(hDVYNPpnXQ == true){hDVYNPpnXQ = false;}
      if(BkPfMKTwBj == true){BkPfMKTwBj = false;}
      if(peyhTXUYlW == true){peyhTXUYlW = false;}
      if(nTxmPRNJDE == true){nTxmPRNJDE = false;}
      if(OuVFIcLJHL == true){OuVFIcLJHL = false;}
      if(upMadDEmEo == true){upMadDEmEo = false;}
      if(uRBAchncPt == true){uRBAchncPt = false;}
      if(xJrxVuIsZq == true){xJrxVuIsZq = false;}
      if(LKRZbxHVJL == true){LKRZbxHVJL = false;}
      if(NZFNIxsVcZ == true){NZFNIxsVcZ = false;}
      if(oisNOkxPFh == true){oisNOkxPFh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XPRHORRMSV
{ 
  void YZZZDPjZKu()
  { 
      bool ZGSRdlVmCk = false;
      bool HamZCScXiU = false;
      bool VKULJwUhyp = false;
      bool aXYgQtYnsq = false;
      bool LlTpKPTUds = false;
      bool EutDnOkHHh = false;
      bool RnoMKiBGJH = false;
      bool tnerIiqeBs = false;
      bool bzDEkecUrB = false;
      bool IQfLZWxGfa = false;
      bool NNLVzPPCuF = false;
      bool WGGOFSkjbe = false;
      bool FgNHzcISRk = false;
      bool kjyZeOmgFU = false;
      bool PaYmdCKQGH = false;
      bool lNeAVgzDWV = false;
      bool GxjJTmHfip = false;
      bool eDdGPeHZcw = false;
      bool SqMKzXFxEy = false;
      bool OjKjNRpPTq = false;
      string YRKDENhuar;
      string VSmYGTnODx;
      string SweKOdKbIT;
      string iunQCXHsIa;
      string lToVPhRxzS;
      string uMdEUblzna;
      string CFlHJadVWi;
      string LtFcLzHIug;
      string LMcoXWQjwZ;
      string kHEhXfghMo;
      string EwaPGAGBsU;
      string UdDHPpcwim;
      string JtYwyEoXFf;
      string RYwGcOlMiX;
      string PPqbFHDxSh;
      string CjzZeJXdQC;
      string KhwMCugxdA;
      string DPNLWtCxqp;
      string AqFXchZVbS;
      string qHufMgTdYJ;
      if(YRKDENhuar == EwaPGAGBsU){ZGSRdlVmCk = true;}
      else if(EwaPGAGBsU == YRKDENhuar){NNLVzPPCuF = true;}
      if(VSmYGTnODx == UdDHPpcwim){HamZCScXiU = true;}
      else if(UdDHPpcwim == VSmYGTnODx){WGGOFSkjbe = true;}
      if(SweKOdKbIT == JtYwyEoXFf){VKULJwUhyp = true;}
      else if(JtYwyEoXFf == SweKOdKbIT){FgNHzcISRk = true;}
      if(iunQCXHsIa == RYwGcOlMiX){aXYgQtYnsq = true;}
      else if(RYwGcOlMiX == iunQCXHsIa){kjyZeOmgFU = true;}
      if(lToVPhRxzS == PPqbFHDxSh){LlTpKPTUds = true;}
      else if(PPqbFHDxSh == lToVPhRxzS){PaYmdCKQGH = true;}
      if(uMdEUblzna == CjzZeJXdQC){EutDnOkHHh = true;}
      else if(CjzZeJXdQC == uMdEUblzna){lNeAVgzDWV = true;}
      if(CFlHJadVWi == KhwMCugxdA){RnoMKiBGJH = true;}
      else if(KhwMCugxdA == CFlHJadVWi){GxjJTmHfip = true;}
      if(LtFcLzHIug == DPNLWtCxqp){tnerIiqeBs = true;}
      if(LMcoXWQjwZ == AqFXchZVbS){bzDEkecUrB = true;}
      if(kHEhXfghMo == qHufMgTdYJ){IQfLZWxGfa = true;}
      while(DPNLWtCxqp == LtFcLzHIug){eDdGPeHZcw = true;}
      while(AqFXchZVbS == AqFXchZVbS){SqMKzXFxEy = true;}
      while(qHufMgTdYJ == qHufMgTdYJ){OjKjNRpPTq = true;}
      if(ZGSRdlVmCk == true){ZGSRdlVmCk = false;}
      if(HamZCScXiU == true){HamZCScXiU = false;}
      if(VKULJwUhyp == true){VKULJwUhyp = false;}
      if(aXYgQtYnsq == true){aXYgQtYnsq = false;}
      if(LlTpKPTUds == true){LlTpKPTUds = false;}
      if(EutDnOkHHh == true){EutDnOkHHh = false;}
      if(RnoMKiBGJH == true){RnoMKiBGJH = false;}
      if(tnerIiqeBs == true){tnerIiqeBs = false;}
      if(bzDEkecUrB == true){bzDEkecUrB = false;}
      if(IQfLZWxGfa == true){IQfLZWxGfa = false;}
      if(NNLVzPPCuF == true){NNLVzPPCuF = false;}
      if(WGGOFSkjbe == true){WGGOFSkjbe = false;}
      if(FgNHzcISRk == true){FgNHzcISRk = false;}
      if(kjyZeOmgFU == true){kjyZeOmgFU = false;}
      if(PaYmdCKQGH == true){PaYmdCKQGH = false;}
      if(lNeAVgzDWV == true){lNeAVgzDWV = false;}
      if(GxjJTmHfip == true){GxjJTmHfip = false;}
      if(eDdGPeHZcw == true){eDdGPeHZcw = false;}
      if(SqMKzXFxEy == true){SqMKzXFxEy = false;}
      if(OjKjNRpPTq == true){OjKjNRpPTq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LSOQUAKCZU
{ 
  void CuIaJpCcxG()
  { 
      bool OHgeQmkLNO = false;
      bool CFAAxTDLqD = false;
      bool WwOlPJoMRo = false;
      bool tQopqSffcn = false;
      bool HRiIbSPVZA = false;
      bool YFuUdRruOH = false;
      bool yXsYTlQKJe = false;
      bool mWiDuEMGKx = false;
      bool sTlQPoVTLY = false;
      bool ZkRVpiXKnp = false;
      bool CFLuNBWrZZ = false;
      bool FkjROelcJd = false;
      bool PwykECFNMM = false;
      bool gCSUtmHqDN = false;
      bool SdtlSoBzHL = false;
      bool xuBKZFHZpK = false;
      bool wIeMrCSPWa = false;
      bool WuYuLkCLRP = false;
      bool BFGBPlBHtn = false;
      bool fgArRJzgsQ = false;
      string irBfbfGqtE;
      string GMLqTOTBOo;
      string gqCLaDCSYG;
      string JLEAUWSFWE;
      string bSbjEYLHSm;
      string IXzFWqppEX;
      string dnRmuuIKVw;
      string wNdKMNPRGC;
      string rtzlxkLycc;
      string gbBzZmAnoJ;
      string QAkVqttorI;
      string bXiCfioepJ;
      string iJhsPTMejZ;
      string NbcxkqJcuD;
      string qWFTBJsyTp;
      string yUyfaGSrGX;
      string hOFSuAtlQn;
      string ZLjlRMDNqF;
      string ZNLsarcxWe;
      string XQWXUcRmYB;
      if(irBfbfGqtE == QAkVqttorI){OHgeQmkLNO = true;}
      else if(QAkVqttorI == irBfbfGqtE){CFLuNBWrZZ = true;}
      if(GMLqTOTBOo == bXiCfioepJ){CFAAxTDLqD = true;}
      else if(bXiCfioepJ == GMLqTOTBOo){FkjROelcJd = true;}
      if(gqCLaDCSYG == iJhsPTMejZ){WwOlPJoMRo = true;}
      else if(iJhsPTMejZ == gqCLaDCSYG){PwykECFNMM = true;}
      if(JLEAUWSFWE == NbcxkqJcuD){tQopqSffcn = true;}
      else if(NbcxkqJcuD == JLEAUWSFWE){gCSUtmHqDN = true;}
      if(bSbjEYLHSm == qWFTBJsyTp){HRiIbSPVZA = true;}
      else if(qWFTBJsyTp == bSbjEYLHSm){SdtlSoBzHL = true;}
      if(IXzFWqppEX == yUyfaGSrGX){YFuUdRruOH = true;}
      else if(yUyfaGSrGX == IXzFWqppEX){xuBKZFHZpK = true;}
      if(dnRmuuIKVw == hOFSuAtlQn){yXsYTlQKJe = true;}
      else if(hOFSuAtlQn == dnRmuuIKVw){wIeMrCSPWa = true;}
      if(wNdKMNPRGC == ZLjlRMDNqF){mWiDuEMGKx = true;}
      if(rtzlxkLycc == ZNLsarcxWe){sTlQPoVTLY = true;}
      if(gbBzZmAnoJ == XQWXUcRmYB){ZkRVpiXKnp = true;}
      while(ZLjlRMDNqF == wNdKMNPRGC){WuYuLkCLRP = true;}
      while(ZNLsarcxWe == ZNLsarcxWe){BFGBPlBHtn = true;}
      while(XQWXUcRmYB == XQWXUcRmYB){fgArRJzgsQ = true;}
      if(OHgeQmkLNO == true){OHgeQmkLNO = false;}
      if(CFAAxTDLqD == true){CFAAxTDLqD = false;}
      if(WwOlPJoMRo == true){WwOlPJoMRo = false;}
      if(tQopqSffcn == true){tQopqSffcn = false;}
      if(HRiIbSPVZA == true){HRiIbSPVZA = false;}
      if(YFuUdRruOH == true){YFuUdRruOH = false;}
      if(yXsYTlQKJe == true){yXsYTlQKJe = false;}
      if(mWiDuEMGKx == true){mWiDuEMGKx = false;}
      if(sTlQPoVTLY == true){sTlQPoVTLY = false;}
      if(ZkRVpiXKnp == true){ZkRVpiXKnp = false;}
      if(CFLuNBWrZZ == true){CFLuNBWrZZ = false;}
      if(FkjROelcJd == true){FkjROelcJd = false;}
      if(PwykECFNMM == true){PwykECFNMM = false;}
      if(gCSUtmHqDN == true){gCSUtmHqDN = false;}
      if(SdtlSoBzHL == true){SdtlSoBzHL = false;}
      if(xuBKZFHZpK == true){xuBKZFHZpK = false;}
      if(wIeMrCSPWa == true){wIeMrCSPWa = false;}
      if(WuYuLkCLRP == true){WuYuLkCLRP = false;}
      if(BFGBPlBHtn == true){BFGBPlBHtn = false;}
      if(fgArRJzgsQ == true){fgArRJzgsQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MURGDDNVNH
{ 
  void hYpCnpZmru()
  { 
      bool oFRTRtkhCo = false;
      bool WtwlmeeSTc = false;
      bool WMGqEAFRJH = false;
      bool fuMBuoPXjK = false;
      bool feZzaLFxQT = false;
      bool HrgPjbyZOQ = false;
      bool oTXuJahuqy = false;
      bool OHiIwrmHQs = false;
      bool uHApAmOwQT = false;
      bool ppISVMGepz = false;
      bool cJGSEzJYTr = false;
      bool oqJUUgThtV = false;
      bool MldXHYyQlj = false;
      bool kIRQQlAgkB = false;
      bool cocXdzgmxn = false;
      bool sYkTmqeiKf = false;
      bool BsliHgZrEi = false;
      bool glxssXIGsI = false;
      bool qKSyqMWxdY = false;
      bool GQWEzjDsPx = false;
      string aYTcIaglHQ;
      string NnSYtbnYEx;
      string eRhaKtDpLW;
      string KRbQpkLhIC;
      string YoyGACuout;
      string IIsmIIprRO;
      string XqZkFwLBhJ;
      string PGPBXoTaZI;
      string yNtQOCXoIg;
      string tTQtehPNBE;
      string psGleCrqOT;
      string oPRIPJxIVD;
      string XWsAOwoVWp;
      string YFZVSFHHlM;
      string JfZnreBHdU;
      string jHrxgTzFWh;
      string MWUYujowpK;
      string CpVJtqwFIj;
      string tgqBFRNcoy;
      string FBjEzlLAsH;
      if(aYTcIaglHQ == psGleCrqOT){oFRTRtkhCo = true;}
      else if(psGleCrqOT == aYTcIaglHQ){cJGSEzJYTr = true;}
      if(NnSYtbnYEx == oPRIPJxIVD){WtwlmeeSTc = true;}
      else if(oPRIPJxIVD == NnSYtbnYEx){oqJUUgThtV = true;}
      if(eRhaKtDpLW == XWsAOwoVWp){WMGqEAFRJH = true;}
      else if(XWsAOwoVWp == eRhaKtDpLW){MldXHYyQlj = true;}
      if(KRbQpkLhIC == YFZVSFHHlM){fuMBuoPXjK = true;}
      else if(YFZVSFHHlM == KRbQpkLhIC){kIRQQlAgkB = true;}
      if(YoyGACuout == JfZnreBHdU){feZzaLFxQT = true;}
      else if(JfZnreBHdU == YoyGACuout){cocXdzgmxn = true;}
      if(IIsmIIprRO == jHrxgTzFWh){HrgPjbyZOQ = true;}
      else if(jHrxgTzFWh == IIsmIIprRO){sYkTmqeiKf = true;}
      if(XqZkFwLBhJ == MWUYujowpK){oTXuJahuqy = true;}
      else if(MWUYujowpK == XqZkFwLBhJ){BsliHgZrEi = true;}
      if(PGPBXoTaZI == CpVJtqwFIj){OHiIwrmHQs = true;}
      if(yNtQOCXoIg == tgqBFRNcoy){uHApAmOwQT = true;}
      if(tTQtehPNBE == FBjEzlLAsH){ppISVMGepz = true;}
      while(CpVJtqwFIj == PGPBXoTaZI){glxssXIGsI = true;}
      while(tgqBFRNcoy == tgqBFRNcoy){qKSyqMWxdY = true;}
      while(FBjEzlLAsH == FBjEzlLAsH){GQWEzjDsPx = true;}
      if(oFRTRtkhCo == true){oFRTRtkhCo = false;}
      if(WtwlmeeSTc == true){WtwlmeeSTc = false;}
      if(WMGqEAFRJH == true){WMGqEAFRJH = false;}
      if(fuMBuoPXjK == true){fuMBuoPXjK = false;}
      if(feZzaLFxQT == true){feZzaLFxQT = false;}
      if(HrgPjbyZOQ == true){HrgPjbyZOQ = false;}
      if(oTXuJahuqy == true){oTXuJahuqy = false;}
      if(OHiIwrmHQs == true){OHiIwrmHQs = false;}
      if(uHApAmOwQT == true){uHApAmOwQT = false;}
      if(ppISVMGepz == true){ppISVMGepz = false;}
      if(cJGSEzJYTr == true){cJGSEzJYTr = false;}
      if(oqJUUgThtV == true){oqJUUgThtV = false;}
      if(MldXHYyQlj == true){MldXHYyQlj = false;}
      if(kIRQQlAgkB == true){kIRQQlAgkB = false;}
      if(cocXdzgmxn == true){cocXdzgmxn = false;}
      if(sYkTmqeiKf == true){sYkTmqeiKf = false;}
      if(BsliHgZrEi == true){BsliHgZrEi = false;}
      if(glxssXIGsI == true){glxssXIGsI = false;}
      if(qKSyqMWxdY == true){qKSyqMWxdY = false;}
      if(GQWEzjDsPx == true){GQWEzjDsPx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAPESVIJAD
{ 
  void jdnQriaUXx()
  { 
      bool PDxDLBCMOo = false;
      bool aaNkdNpUXV = false;
      bool drBiMdapQD = false;
      bool uqkerqOHRa = false;
      bool EnwNOhUiWh = false;
      bool xEtmFWBNph = false;
      bool ZLuLtiphsl = false;
      bool ziCxRpwnTe = false;
      bool IqShGpxyYU = false;
      bool oAQjArrjTe = false;
      bool qlpjiOBxVO = false;
      bool aNtLYhrMFD = false;
      bool lrIXxyRSxY = false;
      bool yLTomWBizr = false;
      bool nzcKtaGEKR = false;
      bool zeePszcRlj = false;
      bool wizwQOsEYC = false;
      bool gJNMPlOydV = false;
      bool rNHeYTgEwm = false;
      bool sjwOuFAfsf = false;
      string lFXJTXNEpX;
      string AQuGRbGUri;
      string WzmqWjdSsg;
      string UdwyGEEGKr;
      string CRRnZhAIhw;
      string FuCFhlRgmj;
      string tuKJDVTxzN;
      string XzJAgFhzQn;
      string iVjwaYbqPT;
      string lWTZxHGHjE;
      string NDIUYFkCYc;
      string ESPyBYKNhe;
      string tcgeaAfjCY;
      string zZPMZeMOXU;
      string nYSmPSGUYY;
      string xrZEJkVdsX;
      string YBzzceDDXV;
      string MwpMpUKtPI;
      string tLKdbGAKCo;
      string JiUAwmZSJj;
      if(lFXJTXNEpX == NDIUYFkCYc){PDxDLBCMOo = true;}
      else if(NDIUYFkCYc == lFXJTXNEpX){qlpjiOBxVO = true;}
      if(AQuGRbGUri == ESPyBYKNhe){aaNkdNpUXV = true;}
      else if(ESPyBYKNhe == AQuGRbGUri){aNtLYhrMFD = true;}
      if(WzmqWjdSsg == tcgeaAfjCY){drBiMdapQD = true;}
      else if(tcgeaAfjCY == WzmqWjdSsg){lrIXxyRSxY = true;}
      if(UdwyGEEGKr == zZPMZeMOXU){uqkerqOHRa = true;}
      else if(zZPMZeMOXU == UdwyGEEGKr){yLTomWBizr = true;}
      if(CRRnZhAIhw == nYSmPSGUYY){EnwNOhUiWh = true;}
      else if(nYSmPSGUYY == CRRnZhAIhw){nzcKtaGEKR = true;}
      if(FuCFhlRgmj == xrZEJkVdsX){xEtmFWBNph = true;}
      else if(xrZEJkVdsX == FuCFhlRgmj){zeePszcRlj = true;}
      if(tuKJDVTxzN == YBzzceDDXV){ZLuLtiphsl = true;}
      else if(YBzzceDDXV == tuKJDVTxzN){wizwQOsEYC = true;}
      if(XzJAgFhzQn == MwpMpUKtPI){ziCxRpwnTe = true;}
      if(iVjwaYbqPT == tLKdbGAKCo){IqShGpxyYU = true;}
      if(lWTZxHGHjE == JiUAwmZSJj){oAQjArrjTe = true;}
      while(MwpMpUKtPI == XzJAgFhzQn){gJNMPlOydV = true;}
      while(tLKdbGAKCo == tLKdbGAKCo){rNHeYTgEwm = true;}
      while(JiUAwmZSJj == JiUAwmZSJj){sjwOuFAfsf = true;}
      if(PDxDLBCMOo == true){PDxDLBCMOo = false;}
      if(aaNkdNpUXV == true){aaNkdNpUXV = false;}
      if(drBiMdapQD == true){drBiMdapQD = false;}
      if(uqkerqOHRa == true){uqkerqOHRa = false;}
      if(EnwNOhUiWh == true){EnwNOhUiWh = false;}
      if(xEtmFWBNph == true){xEtmFWBNph = false;}
      if(ZLuLtiphsl == true){ZLuLtiphsl = false;}
      if(ziCxRpwnTe == true){ziCxRpwnTe = false;}
      if(IqShGpxyYU == true){IqShGpxyYU = false;}
      if(oAQjArrjTe == true){oAQjArrjTe = false;}
      if(qlpjiOBxVO == true){qlpjiOBxVO = false;}
      if(aNtLYhrMFD == true){aNtLYhrMFD = false;}
      if(lrIXxyRSxY == true){lrIXxyRSxY = false;}
      if(yLTomWBizr == true){yLTomWBizr = false;}
      if(nzcKtaGEKR == true){nzcKtaGEKR = false;}
      if(zeePszcRlj == true){zeePszcRlj = false;}
      if(wizwQOsEYC == true){wizwQOsEYC = false;}
      if(gJNMPlOydV == true){gJNMPlOydV = false;}
      if(rNHeYTgEwm == true){rNHeYTgEwm = false;}
      if(sjwOuFAfsf == true){sjwOuFAfsf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MMCGUDHMZO
{ 
  void MqsTYtINPT()
  { 
      bool YecFUXPtZc = false;
      bool gnUrrAEwNo = false;
      bool hhdfSwotfW = false;
      bool nszbaQQhsO = false;
      bool bEPqIcKPQt = false;
      bool RyYcMqAwlY = false;
      bool hVODomnrRb = false;
      bool jVDyMdRmXp = false;
      bool kYclEpUWPi = false;
      bool PTuTfFpMBU = false;
      bool nRxoJutZPi = false;
      bool YNYwmJsbyz = false;
      bool SRchLPZiRG = false;
      bool nFkCBTamcJ = false;
      bool utGfKCuzgW = false;
      bool MNNCBWnPds = false;
      bool VKIJtSbVuS = false;
      bool hFzoDYKxWJ = false;
      bool TaCtsaqiAd = false;
      bool fLJimjkxlq = false;
      string kJNaaOhdMV;
      string ThcVNKpXWU;
      string TcwzVZuzOY;
      string fEWTnoYaxP;
      string ylXOQpfbLA;
      string zwccaHMOEA;
      string SiPnpPLJhX;
      string kOZHVhFghf;
      string sSmNYiasrf;
      string bKWwwPVjYB;
      string dWtnPkVVGs;
      string CffXGAuCOG;
      string nRQBwaqdKG;
      string LUIgBWYzyn;
      string NFlzcwdyow;
      string TTVSMLFsqn;
      string srKAghXzVj;
      string bwDarieRXz;
      string wsnNlrzoUo;
      string QeHJtVtlRu;
      if(kJNaaOhdMV == dWtnPkVVGs){YecFUXPtZc = true;}
      else if(dWtnPkVVGs == kJNaaOhdMV){nRxoJutZPi = true;}
      if(ThcVNKpXWU == CffXGAuCOG){gnUrrAEwNo = true;}
      else if(CffXGAuCOG == ThcVNKpXWU){YNYwmJsbyz = true;}
      if(TcwzVZuzOY == nRQBwaqdKG){hhdfSwotfW = true;}
      else if(nRQBwaqdKG == TcwzVZuzOY){SRchLPZiRG = true;}
      if(fEWTnoYaxP == LUIgBWYzyn){nszbaQQhsO = true;}
      else if(LUIgBWYzyn == fEWTnoYaxP){nFkCBTamcJ = true;}
      if(ylXOQpfbLA == NFlzcwdyow){bEPqIcKPQt = true;}
      else if(NFlzcwdyow == ylXOQpfbLA){utGfKCuzgW = true;}
      if(zwccaHMOEA == TTVSMLFsqn){RyYcMqAwlY = true;}
      else if(TTVSMLFsqn == zwccaHMOEA){MNNCBWnPds = true;}
      if(SiPnpPLJhX == srKAghXzVj){hVODomnrRb = true;}
      else if(srKAghXzVj == SiPnpPLJhX){VKIJtSbVuS = true;}
      if(kOZHVhFghf == bwDarieRXz){jVDyMdRmXp = true;}
      if(sSmNYiasrf == wsnNlrzoUo){kYclEpUWPi = true;}
      if(bKWwwPVjYB == QeHJtVtlRu){PTuTfFpMBU = true;}
      while(bwDarieRXz == kOZHVhFghf){hFzoDYKxWJ = true;}
      while(wsnNlrzoUo == wsnNlrzoUo){TaCtsaqiAd = true;}
      while(QeHJtVtlRu == QeHJtVtlRu){fLJimjkxlq = true;}
      if(YecFUXPtZc == true){YecFUXPtZc = false;}
      if(gnUrrAEwNo == true){gnUrrAEwNo = false;}
      if(hhdfSwotfW == true){hhdfSwotfW = false;}
      if(nszbaQQhsO == true){nszbaQQhsO = false;}
      if(bEPqIcKPQt == true){bEPqIcKPQt = false;}
      if(RyYcMqAwlY == true){RyYcMqAwlY = false;}
      if(hVODomnrRb == true){hVODomnrRb = false;}
      if(jVDyMdRmXp == true){jVDyMdRmXp = false;}
      if(kYclEpUWPi == true){kYclEpUWPi = false;}
      if(PTuTfFpMBU == true){PTuTfFpMBU = false;}
      if(nRxoJutZPi == true){nRxoJutZPi = false;}
      if(YNYwmJsbyz == true){YNYwmJsbyz = false;}
      if(SRchLPZiRG == true){SRchLPZiRG = false;}
      if(nFkCBTamcJ == true){nFkCBTamcJ = false;}
      if(utGfKCuzgW == true){utGfKCuzgW = false;}
      if(MNNCBWnPds == true){MNNCBWnPds = false;}
      if(VKIJtSbVuS == true){VKIJtSbVuS = false;}
      if(hFzoDYKxWJ == true){hFzoDYKxWJ = false;}
      if(TaCtsaqiAd == true){TaCtsaqiAd = false;}
      if(fLJimjkxlq == true){fLJimjkxlq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AOTBZOKVWZ
{ 
  void EwBUtZWQxq()
  { 
      bool dpxAVgUpjA = false;
      bool bOpysnJwAM = false;
      bool fQdoBGfYYw = false;
      bool OwrBQfgYNS = false;
      bool eYPqgQSxYu = false;
      bool VDdndNMIzP = false;
      bool BwQmleVngM = false;
      bool HjhggHBlHk = false;
      bool mhzcZKSDXD = false;
      bool TYYyRiHbFC = false;
      bool tdQLnkUwHW = false;
      bool LZAObSwnMa = false;
      bool MSQcshKjPy = false;
      bool zYgFpJRmoo = false;
      bool oWwArtXKVz = false;
      bool mTPdoaMmSF = false;
      bool ZkgIWlsuXS = false;
      bool AIyXkpWQky = false;
      bool KANPLfJCPO = false;
      bool weTiOEomcF = false;
      string SDjUetUafx;
      string qoKYbHcZJI;
      string DmMsjKiaNY;
      string BRoPsNgtTZ;
      string VBQyfKJBzb;
      string cwkxaeppkT;
      string KtNGuYzufN;
      string aiGjlBWONY;
      string BhakuEfqnN;
      string WpIzObnJCG;
      string LOUkBspBLZ;
      string IbcMScSbKq;
      string rHHRqjaGVJ;
      string MNLGNlMpjC;
      string OefNFuMwgl;
      string JMyLNDHDtQ;
      string SifBMtQWyf;
      string PbrIbNasMu;
      string WdZiAAOzrJ;
      string eJwSjezeBK;
      if(SDjUetUafx == LOUkBspBLZ){dpxAVgUpjA = true;}
      else if(LOUkBspBLZ == SDjUetUafx){tdQLnkUwHW = true;}
      if(qoKYbHcZJI == IbcMScSbKq){bOpysnJwAM = true;}
      else if(IbcMScSbKq == qoKYbHcZJI){LZAObSwnMa = true;}
      if(DmMsjKiaNY == rHHRqjaGVJ){fQdoBGfYYw = true;}
      else if(rHHRqjaGVJ == DmMsjKiaNY){MSQcshKjPy = true;}
      if(BRoPsNgtTZ == MNLGNlMpjC){OwrBQfgYNS = true;}
      else if(MNLGNlMpjC == BRoPsNgtTZ){zYgFpJRmoo = true;}
      if(VBQyfKJBzb == OefNFuMwgl){eYPqgQSxYu = true;}
      else if(OefNFuMwgl == VBQyfKJBzb){oWwArtXKVz = true;}
      if(cwkxaeppkT == JMyLNDHDtQ){VDdndNMIzP = true;}
      else if(JMyLNDHDtQ == cwkxaeppkT){mTPdoaMmSF = true;}
      if(KtNGuYzufN == SifBMtQWyf){BwQmleVngM = true;}
      else if(SifBMtQWyf == KtNGuYzufN){ZkgIWlsuXS = true;}
      if(aiGjlBWONY == PbrIbNasMu){HjhggHBlHk = true;}
      if(BhakuEfqnN == WdZiAAOzrJ){mhzcZKSDXD = true;}
      if(WpIzObnJCG == eJwSjezeBK){TYYyRiHbFC = true;}
      while(PbrIbNasMu == aiGjlBWONY){AIyXkpWQky = true;}
      while(WdZiAAOzrJ == WdZiAAOzrJ){KANPLfJCPO = true;}
      while(eJwSjezeBK == eJwSjezeBK){weTiOEomcF = true;}
      if(dpxAVgUpjA == true){dpxAVgUpjA = false;}
      if(bOpysnJwAM == true){bOpysnJwAM = false;}
      if(fQdoBGfYYw == true){fQdoBGfYYw = false;}
      if(OwrBQfgYNS == true){OwrBQfgYNS = false;}
      if(eYPqgQSxYu == true){eYPqgQSxYu = false;}
      if(VDdndNMIzP == true){VDdndNMIzP = false;}
      if(BwQmleVngM == true){BwQmleVngM = false;}
      if(HjhggHBlHk == true){HjhggHBlHk = false;}
      if(mhzcZKSDXD == true){mhzcZKSDXD = false;}
      if(TYYyRiHbFC == true){TYYyRiHbFC = false;}
      if(tdQLnkUwHW == true){tdQLnkUwHW = false;}
      if(LZAObSwnMa == true){LZAObSwnMa = false;}
      if(MSQcshKjPy == true){MSQcshKjPy = false;}
      if(zYgFpJRmoo == true){zYgFpJRmoo = false;}
      if(oWwArtXKVz == true){oWwArtXKVz = false;}
      if(mTPdoaMmSF == true){mTPdoaMmSF = false;}
      if(ZkgIWlsuXS == true){ZkgIWlsuXS = false;}
      if(AIyXkpWQky == true){AIyXkpWQky = false;}
      if(KANPLfJCPO == true){KANPLfJCPO = false;}
      if(weTiOEomcF == true){weTiOEomcF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUGOBMDKNC
{ 
  void zxuPkcZabo()
  { 
      bool oqDnSRNlOc = false;
      bool hhopjBntRh = false;
      bool ROgrsPEpUn = false;
      bool PsXkLORHVV = false;
      bool rXBodzJqkQ = false;
      bool mltHMaKKuC = false;
      bool NXQaMoKEdV = false;
      bool jfYwpsMrOs = false;
      bool GMEEAdyQXj = false;
      bool DGMSHUHabn = false;
      bool oEMOgGNyRS = false;
      bool OSwBuBSLZi = false;
      bool qtfsRcTFnV = false;
      bool lkPaECzpXt = false;
      bool PAyFVkKKWF = false;
      bool BuBswuXTwD = false;
      bool lHJufcDVxs = false;
      bool CbnfSquaXg = false;
      bool SJhiTqjVdI = false;
      bool dftTHIpCYs = false;
      string pPReglKipQ;
      string lJjwoaUfUO;
      string rxnzNEpPNb;
      string iBUrJXyeyx;
      string IRNmWAhMdO;
      string nbdDtsbSRb;
      string wuVNgjorlR;
      string bpgXFaiBcM;
      string VdkymGWQyQ;
      string ufMVANwAFl;
      string LpZMmyuGyT;
      string KaoFGSJWaa;
      string MXsVVwcLWr;
      string eiuqAeDXLn;
      string LQSeGUpHPh;
      string DYYeYnxEqp;
      string VjjGnbeyEa;
      string OkLmPwFOOA;
      string FUuonFJQRM;
      string hygURagMpd;
      if(pPReglKipQ == LpZMmyuGyT){oqDnSRNlOc = true;}
      else if(LpZMmyuGyT == pPReglKipQ){oEMOgGNyRS = true;}
      if(lJjwoaUfUO == KaoFGSJWaa){hhopjBntRh = true;}
      else if(KaoFGSJWaa == lJjwoaUfUO){OSwBuBSLZi = true;}
      if(rxnzNEpPNb == MXsVVwcLWr){ROgrsPEpUn = true;}
      else if(MXsVVwcLWr == rxnzNEpPNb){qtfsRcTFnV = true;}
      if(iBUrJXyeyx == eiuqAeDXLn){PsXkLORHVV = true;}
      else if(eiuqAeDXLn == iBUrJXyeyx){lkPaECzpXt = true;}
      if(IRNmWAhMdO == LQSeGUpHPh){rXBodzJqkQ = true;}
      else if(LQSeGUpHPh == IRNmWAhMdO){PAyFVkKKWF = true;}
      if(nbdDtsbSRb == DYYeYnxEqp){mltHMaKKuC = true;}
      else if(DYYeYnxEqp == nbdDtsbSRb){BuBswuXTwD = true;}
      if(wuVNgjorlR == VjjGnbeyEa){NXQaMoKEdV = true;}
      else if(VjjGnbeyEa == wuVNgjorlR){lHJufcDVxs = true;}
      if(bpgXFaiBcM == OkLmPwFOOA){jfYwpsMrOs = true;}
      if(VdkymGWQyQ == FUuonFJQRM){GMEEAdyQXj = true;}
      if(ufMVANwAFl == hygURagMpd){DGMSHUHabn = true;}
      while(OkLmPwFOOA == bpgXFaiBcM){CbnfSquaXg = true;}
      while(FUuonFJQRM == FUuonFJQRM){SJhiTqjVdI = true;}
      while(hygURagMpd == hygURagMpd){dftTHIpCYs = true;}
      if(oqDnSRNlOc == true){oqDnSRNlOc = false;}
      if(hhopjBntRh == true){hhopjBntRh = false;}
      if(ROgrsPEpUn == true){ROgrsPEpUn = false;}
      if(PsXkLORHVV == true){PsXkLORHVV = false;}
      if(rXBodzJqkQ == true){rXBodzJqkQ = false;}
      if(mltHMaKKuC == true){mltHMaKKuC = false;}
      if(NXQaMoKEdV == true){NXQaMoKEdV = false;}
      if(jfYwpsMrOs == true){jfYwpsMrOs = false;}
      if(GMEEAdyQXj == true){GMEEAdyQXj = false;}
      if(DGMSHUHabn == true){DGMSHUHabn = false;}
      if(oEMOgGNyRS == true){oEMOgGNyRS = false;}
      if(OSwBuBSLZi == true){OSwBuBSLZi = false;}
      if(qtfsRcTFnV == true){qtfsRcTFnV = false;}
      if(lkPaECzpXt == true){lkPaECzpXt = false;}
      if(PAyFVkKKWF == true){PAyFVkKKWF = false;}
      if(BuBswuXTwD == true){BuBswuXTwD = false;}
      if(lHJufcDVxs == true){lHJufcDVxs = false;}
      if(CbnfSquaXg == true){CbnfSquaXg = false;}
      if(SJhiTqjVdI == true){SJhiTqjVdI = false;}
      if(dftTHIpCYs == true){dftTHIpCYs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KPZVTPJOSS
{ 
  void hDkOQdOTWJ()
  { 
      bool GyKufhlucs = false;
      bool ewgkJKcccp = false;
      bool PtmrbRUYfk = false;
      bool AoJnMmldcj = false;
      bool zdbjskwxGw = false;
      bool VRZcDLLSSO = false;
      bool MMOqsolsXV = false;
      bool XyAsplRCzq = false;
      bool UWRjPhPgjA = false;
      bool bTKOWmPkqD = false;
      bool zDYkXWRglR = false;
      bool sJSbtptdaK = false;
      bool ZFIXtDnkWD = false;
      bool WgLwrQxgMs = false;
      bool PitSGSAiTf = false;
      bool rkJfcstBqT = false;
      bool ifKhuMxWjc = false;
      bool rMRgtqKpQb = false;
      bool CEQpLkXeSy = false;
      bool WwprKjXMXt = false;
      string GMIiUluSog;
      string qKUJyQdmFP;
      string hUfnKCynGr;
      string OGYOoDROmd;
      string jpfPDzBZXw;
      string wgzdfkgTYR;
      string mHMwRkkFUu;
      string zPAbfqoPkK;
      string BYPJugGuiE;
      string WypVpcdixS;
      string NuFcxggXxn;
      string uQiNPOqCBk;
      string dpWQYBZekD;
      string MGRRwGSmMN;
      string AhxtIFObFb;
      string kbhMnXYoEu;
      string HCmtaozQQJ;
      string uDpmjurcHS;
      string lxYJRkYEdY;
      string gdiQGyuCST;
      if(GMIiUluSog == NuFcxggXxn){GyKufhlucs = true;}
      else if(NuFcxggXxn == GMIiUluSog){zDYkXWRglR = true;}
      if(qKUJyQdmFP == uQiNPOqCBk){ewgkJKcccp = true;}
      else if(uQiNPOqCBk == qKUJyQdmFP){sJSbtptdaK = true;}
      if(hUfnKCynGr == dpWQYBZekD){PtmrbRUYfk = true;}
      else if(dpWQYBZekD == hUfnKCynGr){ZFIXtDnkWD = true;}
      if(OGYOoDROmd == MGRRwGSmMN){AoJnMmldcj = true;}
      else if(MGRRwGSmMN == OGYOoDROmd){WgLwrQxgMs = true;}
      if(jpfPDzBZXw == AhxtIFObFb){zdbjskwxGw = true;}
      else if(AhxtIFObFb == jpfPDzBZXw){PitSGSAiTf = true;}
      if(wgzdfkgTYR == kbhMnXYoEu){VRZcDLLSSO = true;}
      else if(kbhMnXYoEu == wgzdfkgTYR){rkJfcstBqT = true;}
      if(mHMwRkkFUu == HCmtaozQQJ){MMOqsolsXV = true;}
      else if(HCmtaozQQJ == mHMwRkkFUu){ifKhuMxWjc = true;}
      if(zPAbfqoPkK == uDpmjurcHS){XyAsplRCzq = true;}
      if(BYPJugGuiE == lxYJRkYEdY){UWRjPhPgjA = true;}
      if(WypVpcdixS == gdiQGyuCST){bTKOWmPkqD = true;}
      while(uDpmjurcHS == zPAbfqoPkK){rMRgtqKpQb = true;}
      while(lxYJRkYEdY == lxYJRkYEdY){CEQpLkXeSy = true;}
      while(gdiQGyuCST == gdiQGyuCST){WwprKjXMXt = true;}
      if(GyKufhlucs == true){GyKufhlucs = false;}
      if(ewgkJKcccp == true){ewgkJKcccp = false;}
      if(PtmrbRUYfk == true){PtmrbRUYfk = false;}
      if(AoJnMmldcj == true){AoJnMmldcj = false;}
      if(zdbjskwxGw == true){zdbjskwxGw = false;}
      if(VRZcDLLSSO == true){VRZcDLLSSO = false;}
      if(MMOqsolsXV == true){MMOqsolsXV = false;}
      if(XyAsplRCzq == true){XyAsplRCzq = false;}
      if(UWRjPhPgjA == true){UWRjPhPgjA = false;}
      if(bTKOWmPkqD == true){bTKOWmPkqD = false;}
      if(zDYkXWRglR == true){zDYkXWRglR = false;}
      if(sJSbtptdaK == true){sJSbtptdaK = false;}
      if(ZFIXtDnkWD == true){ZFIXtDnkWD = false;}
      if(WgLwrQxgMs == true){WgLwrQxgMs = false;}
      if(PitSGSAiTf == true){PitSGSAiTf = false;}
      if(rkJfcstBqT == true){rkJfcstBqT = false;}
      if(ifKhuMxWjc == true){ifKhuMxWjc = false;}
      if(rMRgtqKpQb == true){rMRgtqKpQb = false;}
      if(CEQpLkXeSy == true){CEQpLkXeSy = false;}
      if(WwprKjXMXt == true){WwprKjXMXt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RSVWQDCUPA
{ 
  void LfqlfcsjBS()
  { 
      bool thdrCRzlXx = false;
      bool mMODkEBYbN = false;
      bool XprEZRMqSW = false;
      bool ZSBFSHyAap = false;
      bool CdNAFXJdTH = false;
      bool wrJkcDpZRk = false;
      bool FITBXULJjd = false;
      bool GAylKscqzB = false;
      bool IhXLagJPcO = false;
      bool RXhpktKMck = false;
      bool MAspAutWZi = false;
      bool ayaQcWjIaq = false;
      bool KugVLiRHAQ = false;
      bool iQOOoHogKe = false;
      bool llosnSxRNO = false;
      bool JBkkZQTXeR = false;
      bool cmVIAJjLaU = false;
      bool gDxuFYFmgr = false;
      bool kAslHgednX = false;
      bool nRCsBzPgre = false;
      string QSXLYkAllY;
      string ZBGVftLDVO;
      string ETdBYpoLig;
      string fRAQKSZwuX;
      string rduwKURdNK;
      string ByWZnwnVli;
      string uoDErHBpLN;
      string TOIyVZYhqE;
      string YLxYfgtZbN;
      string dEJMbCapDC;
      string TaSAqlpYDN;
      string XGehJiqdYL;
      string MaNxjPEwVS;
      string yhdnkysxgt;
      string qUVNpWYbDr;
      string LwRrorMUQb;
      string htDjPocqxK;
      string psxeTqEAGM;
      string pcrdHBQlyr;
      string kXgFLxRlyB;
      if(QSXLYkAllY == TaSAqlpYDN){thdrCRzlXx = true;}
      else if(TaSAqlpYDN == QSXLYkAllY){MAspAutWZi = true;}
      if(ZBGVftLDVO == XGehJiqdYL){mMODkEBYbN = true;}
      else if(XGehJiqdYL == ZBGVftLDVO){ayaQcWjIaq = true;}
      if(ETdBYpoLig == MaNxjPEwVS){XprEZRMqSW = true;}
      else if(MaNxjPEwVS == ETdBYpoLig){KugVLiRHAQ = true;}
      if(fRAQKSZwuX == yhdnkysxgt){ZSBFSHyAap = true;}
      else if(yhdnkysxgt == fRAQKSZwuX){iQOOoHogKe = true;}
      if(rduwKURdNK == qUVNpWYbDr){CdNAFXJdTH = true;}
      else if(qUVNpWYbDr == rduwKURdNK){llosnSxRNO = true;}
      if(ByWZnwnVli == LwRrorMUQb){wrJkcDpZRk = true;}
      else if(LwRrorMUQb == ByWZnwnVli){JBkkZQTXeR = true;}
      if(uoDErHBpLN == htDjPocqxK){FITBXULJjd = true;}
      else if(htDjPocqxK == uoDErHBpLN){cmVIAJjLaU = true;}
      if(TOIyVZYhqE == psxeTqEAGM){GAylKscqzB = true;}
      if(YLxYfgtZbN == pcrdHBQlyr){IhXLagJPcO = true;}
      if(dEJMbCapDC == kXgFLxRlyB){RXhpktKMck = true;}
      while(psxeTqEAGM == TOIyVZYhqE){gDxuFYFmgr = true;}
      while(pcrdHBQlyr == pcrdHBQlyr){kAslHgednX = true;}
      while(kXgFLxRlyB == kXgFLxRlyB){nRCsBzPgre = true;}
      if(thdrCRzlXx == true){thdrCRzlXx = false;}
      if(mMODkEBYbN == true){mMODkEBYbN = false;}
      if(XprEZRMqSW == true){XprEZRMqSW = false;}
      if(ZSBFSHyAap == true){ZSBFSHyAap = false;}
      if(CdNAFXJdTH == true){CdNAFXJdTH = false;}
      if(wrJkcDpZRk == true){wrJkcDpZRk = false;}
      if(FITBXULJjd == true){FITBXULJjd = false;}
      if(GAylKscqzB == true){GAylKscqzB = false;}
      if(IhXLagJPcO == true){IhXLagJPcO = false;}
      if(RXhpktKMck == true){RXhpktKMck = false;}
      if(MAspAutWZi == true){MAspAutWZi = false;}
      if(ayaQcWjIaq == true){ayaQcWjIaq = false;}
      if(KugVLiRHAQ == true){KugVLiRHAQ = false;}
      if(iQOOoHogKe == true){iQOOoHogKe = false;}
      if(llosnSxRNO == true){llosnSxRNO = false;}
      if(JBkkZQTXeR == true){JBkkZQTXeR = false;}
      if(cmVIAJjLaU == true){cmVIAJjLaU = false;}
      if(gDxuFYFmgr == true){gDxuFYFmgr = false;}
      if(kAslHgednX == true){kAslHgednX = false;}
      if(nRCsBzPgre == true){nRCsBzPgre = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XPXZHXXAJE
{ 
  void swYSRFRWtw()
  { 
      bool DfHPRfwmmY = false;
      bool TnSfcJtJIM = false;
      bool VCPrJBClnh = false;
      bool ZGjqWaVGSO = false;
      bool SdMtJGatox = false;
      bool UYUNrAPPFP = false;
      bool dJzFzMDaIC = false;
      bool nmqtsqpViC = false;
      bool aHxpMBlWzW = false;
      bool KGACjIeGux = false;
      bool CzklIghaTA = false;
      bool JtgCoVMIrx = false;
      bool ZgalrhmnJk = false;
      bool MiZkzaWKge = false;
      bool TLDzMPYyMO = false;
      bool wVOxWVXzta = false;
      bool tsQimZTuCO = false;
      bool zCaMdNcbZb = false;
      bool InbtnpUbOc = false;
      bool DWPGkZtUMl = false;
      string lPPZZPKEFU;
      string nVShImWlxS;
      string DccDWUKgnY;
      string FfRNsgOiac;
      string wbFddWPQNe;
      string iSLdTImLCF;
      string FcQfPHDEoa;
      string YnLTWbXzYA;
      string FsTIplUmsj;
      string tCfUXSKYNV;
      string TKbmGuGqHr;
      string knmCALJIpc;
      string mPLEgVHpwE;
      string QzkCgtQgCu;
      string edfAzGPdUL;
      string JChkiDzXGj;
      string mPtDalCjVF;
      string tcFuxJjKEZ;
      string GdVjtOQzTc;
      string usZSHPicZN;
      if(lPPZZPKEFU == TKbmGuGqHr){DfHPRfwmmY = true;}
      else if(TKbmGuGqHr == lPPZZPKEFU){CzklIghaTA = true;}
      if(nVShImWlxS == knmCALJIpc){TnSfcJtJIM = true;}
      else if(knmCALJIpc == nVShImWlxS){JtgCoVMIrx = true;}
      if(DccDWUKgnY == mPLEgVHpwE){VCPrJBClnh = true;}
      else if(mPLEgVHpwE == DccDWUKgnY){ZgalrhmnJk = true;}
      if(FfRNsgOiac == QzkCgtQgCu){ZGjqWaVGSO = true;}
      else if(QzkCgtQgCu == FfRNsgOiac){MiZkzaWKge = true;}
      if(wbFddWPQNe == edfAzGPdUL){SdMtJGatox = true;}
      else if(edfAzGPdUL == wbFddWPQNe){TLDzMPYyMO = true;}
      if(iSLdTImLCF == JChkiDzXGj){UYUNrAPPFP = true;}
      else if(JChkiDzXGj == iSLdTImLCF){wVOxWVXzta = true;}
      if(FcQfPHDEoa == mPtDalCjVF){dJzFzMDaIC = true;}
      else if(mPtDalCjVF == FcQfPHDEoa){tsQimZTuCO = true;}
      if(YnLTWbXzYA == tcFuxJjKEZ){nmqtsqpViC = true;}
      if(FsTIplUmsj == GdVjtOQzTc){aHxpMBlWzW = true;}
      if(tCfUXSKYNV == usZSHPicZN){KGACjIeGux = true;}
      while(tcFuxJjKEZ == YnLTWbXzYA){zCaMdNcbZb = true;}
      while(GdVjtOQzTc == GdVjtOQzTc){InbtnpUbOc = true;}
      while(usZSHPicZN == usZSHPicZN){DWPGkZtUMl = true;}
      if(DfHPRfwmmY == true){DfHPRfwmmY = false;}
      if(TnSfcJtJIM == true){TnSfcJtJIM = false;}
      if(VCPrJBClnh == true){VCPrJBClnh = false;}
      if(ZGjqWaVGSO == true){ZGjqWaVGSO = false;}
      if(SdMtJGatox == true){SdMtJGatox = false;}
      if(UYUNrAPPFP == true){UYUNrAPPFP = false;}
      if(dJzFzMDaIC == true){dJzFzMDaIC = false;}
      if(nmqtsqpViC == true){nmqtsqpViC = false;}
      if(aHxpMBlWzW == true){aHxpMBlWzW = false;}
      if(KGACjIeGux == true){KGACjIeGux = false;}
      if(CzklIghaTA == true){CzklIghaTA = false;}
      if(JtgCoVMIrx == true){JtgCoVMIrx = false;}
      if(ZgalrhmnJk == true){ZgalrhmnJk = false;}
      if(MiZkzaWKge == true){MiZkzaWKge = false;}
      if(TLDzMPYyMO == true){TLDzMPYyMO = false;}
      if(wVOxWVXzta == true){wVOxWVXzta = false;}
      if(tsQimZTuCO == true){tsQimZTuCO = false;}
      if(zCaMdNcbZb == true){zCaMdNcbZb = false;}
      if(InbtnpUbOc == true){InbtnpUbOc = false;}
      if(DWPGkZtUMl == true){DWPGkZtUMl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YBGABZXXOR
{ 
  void bubZKkHIpY()
  { 
      bool ypfIdhdgfb = false;
      bool JLqhAGdptG = false;
      bool bOHeNOhtwm = false;
      bool EbkqXpqfOM = false;
      bool hFKjcMbRsb = false;
      bool MTBxtihAtP = false;
      bool zijrXhaAJK = false;
      bool OxbhXWDXCA = false;
      bool lPATZjZnxo = false;
      bool HqlyMyUSMt = false;
      bool lbHiMPrTYX = false;
      bool eKysdiiQRm = false;
      bool IlDUCXLcUY = false;
      bool BkKHOJHRHK = false;
      bool qFOZJwsrUd = false;
      bool PEAZlzYmfo = false;
      bool EPzzVtApeT = false;
      bool aQIGuDWcLG = false;
      bool dSIqJxjkVO = false;
      bool kUkRGbGPDO = false;
      string XFSFTSWyZI;
      string qztKydAxiq;
      string uIzsCVfyoV;
      string GACTNOGqFH;
      string bmGAqnlBOs;
      string JtQPCOFZCx;
      string lXIDBqwaxi;
      string WJqaPHBzCN;
      string jdjuMMilQy;
      string JgnHUEdDyz;
      string rKEeVzCoAu;
      string MFWoMInNqn;
      string IJJzZpVjGL;
      string cyADVZZFZM;
      string JslVkDJyuM;
      string QQLKqhAFEf;
      string dSioROFTSm;
      string hhmeeOXnNW;
      string fWnstLlpMm;
      string YTAshqKwDV;
      if(XFSFTSWyZI == rKEeVzCoAu){ypfIdhdgfb = true;}
      else if(rKEeVzCoAu == XFSFTSWyZI){lbHiMPrTYX = true;}
      if(qztKydAxiq == MFWoMInNqn){JLqhAGdptG = true;}
      else if(MFWoMInNqn == qztKydAxiq){eKysdiiQRm = true;}
      if(uIzsCVfyoV == IJJzZpVjGL){bOHeNOhtwm = true;}
      else if(IJJzZpVjGL == uIzsCVfyoV){IlDUCXLcUY = true;}
      if(GACTNOGqFH == cyADVZZFZM){EbkqXpqfOM = true;}
      else if(cyADVZZFZM == GACTNOGqFH){BkKHOJHRHK = true;}
      if(bmGAqnlBOs == JslVkDJyuM){hFKjcMbRsb = true;}
      else if(JslVkDJyuM == bmGAqnlBOs){qFOZJwsrUd = true;}
      if(JtQPCOFZCx == QQLKqhAFEf){MTBxtihAtP = true;}
      else if(QQLKqhAFEf == JtQPCOFZCx){PEAZlzYmfo = true;}
      if(lXIDBqwaxi == dSioROFTSm){zijrXhaAJK = true;}
      else if(dSioROFTSm == lXIDBqwaxi){EPzzVtApeT = true;}
      if(WJqaPHBzCN == hhmeeOXnNW){OxbhXWDXCA = true;}
      if(jdjuMMilQy == fWnstLlpMm){lPATZjZnxo = true;}
      if(JgnHUEdDyz == YTAshqKwDV){HqlyMyUSMt = true;}
      while(hhmeeOXnNW == WJqaPHBzCN){aQIGuDWcLG = true;}
      while(fWnstLlpMm == fWnstLlpMm){dSIqJxjkVO = true;}
      while(YTAshqKwDV == YTAshqKwDV){kUkRGbGPDO = true;}
      if(ypfIdhdgfb == true){ypfIdhdgfb = false;}
      if(JLqhAGdptG == true){JLqhAGdptG = false;}
      if(bOHeNOhtwm == true){bOHeNOhtwm = false;}
      if(EbkqXpqfOM == true){EbkqXpqfOM = false;}
      if(hFKjcMbRsb == true){hFKjcMbRsb = false;}
      if(MTBxtihAtP == true){MTBxtihAtP = false;}
      if(zijrXhaAJK == true){zijrXhaAJK = false;}
      if(OxbhXWDXCA == true){OxbhXWDXCA = false;}
      if(lPATZjZnxo == true){lPATZjZnxo = false;}
      if(HqlyMyUSMt == true){HqlyMyUSMt = false;}
      if(lbHiMPrTYX == true){lbHiMPrTYX = false;}
      if(eKysdiiQRm == true){eKysdiiQRm = false;}
      if(IlDUCXLcUY == true){IlDUCXLcUY = false;}
      if(BkKHOJHRHK == true){BkKHOJHRHK = false;}
      if(qFOZJwsrUd == true){qFOZJwsrUd = false;}
      if(PEAZlzYmfo == true){PEAZlzYmfo = false;}
      if(EPzzVtApeT == true){EPzzVtApeT = false;}
      if(aQIGuDWcLG == true){aQIGuDWcLG = false;}
      if(dSIqJxjkVO == true){dSIqJxjkVO = false;}
      if(kUkRGbGPDO == true){kUkRGbGPDO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LMZVWNRWMW
{ 
  void WUrfpiyxPt()
  { 
      bool IyUJNLmqaU = false;
      bool HPunhBkTui = false;
      bool hnFXrNWGXO = false;
      bool gVJNdUPKeJ = false;
      bool QQEFaYpfgu = false;
      bool XArUtUsxQz = false;
      bool ogTMmlFhKN = false;
      bool lZnkRRizwT = false;
      bool XpZcqgcoSJ = false;
      bool bStfUjxqRo = false;
      bool SIVTJyLHDc = false;
      bool ksAxayHpUG = false;
      bool IQOAkSfIPh = false;
      bool UqhHAOUFSr = false;
      bool UVkpXiSwEW = false;
      bool bGWLfCsUhq = false;
      bool SCqVIsLsxM = false;
      bool dBXckmeYbC = false;
      bool AiEsFNUWay = false;
      bool UzWbZSePge = false;
      string wbKririUXD;
      string etzQbsLkRV;
      string DxOfJiCNTg;
      string oCpBcnmQmb;
      string KuJyeggicF;
      string uMGzIyNdhz;
      string pVAqObDxnn;
      string GuxpLInPAb;
      string BSjOkcwqrd;
      string ZIhmkntSjD;
      string ciuoyAOQmA;
      string KydGyXlkFk;
      string fMFJNxMJFW;
      string NUexzRXuPj;
      string NeDqSbeboN;
      string CIMzWQdlaB;
      string mFLPmpTfGf;
      string AqVVXBIOpl;
      string SkUrUEHfai;
      string nlUOxITmEc;
      if(wbKririUXD == ciuoyAOQmA){IyUJNLmqaU = true;}
      else if(ciuoyAOQmA == wbKririUXD){SIVTJyLHDc = true;}
      if(etzQbsLkRV == KydGyXlkFk){HPunhBkTui = true;}
      else if(KydGyXlkFk == etzQbsLkRV){ksAxayHpUG = true;}
      if(DxOfJiCNTg == fMFJNxMJFW){hnFXrNWGXO = true;}
      else if(fMFJNxMJFW == DxOfJiCNTg){IQOAkSfIPh = true;}
      if(oCpBcnmQmb == NUexzRXuPj){gVJNdUPKeJ = true;}
      else if(NUexzRXuPj == oCpBcnmQmb){UqhHAOUFSr = true;}
      if(KuJyeggicF == NeDqSbeboN){QQEFaYpfgu = true;}
      else if(NeDqSbeboN == KuJyeggicF){UVkpXiSwEW = true;}
      if(uMGzIyNdhz == CIMzWQdlaB){XArUtUsxQz = true;}
      else if(CIMzWQdlaB == uMGzIyNdhz){bGWLfCsUhq = true;}
      if(pVAqObDxnn == mFLPmpTfGf){ogTMmlFhKN = true;}
      else if(mFLPmpTfGf == pVAqObDxnn){SCqVIsLsxM = true;}
      if(GuxpLInPAb == AqVVXBIOpl){lZnkRRizwT = true;}
      if(BSjOkcwqrd == SkUrUEHfai){XpZcqgcoSJ = true;}
      if(ZIhmkntSjD == nlUOxITmEc){bStfUjxqRo = true;}
      while(AqVVXBIOpl == GuxpLInPAb){dBXckmeYbC = true;}
      while(SkUrUEHfai == SkUrUEHfai){AiEsFNUWay = true;}
      while(nlUOxITmEc == nlUOxITmEc){UzWbZSePge = true;}
      if(IyUJNLmqaU == true){IyUJNLmqaU = false;}
      if(HPunhBkTui == true){HPunhBkTui = false;}
      if(hnFXrNWGXO == true){hnFXrNWGXO = false;}
      if(gVJNdUPKeJ == true){gVJNdUPKeJ = false;}
      if(QQEFaYpfgu == true){QQEFaYpfgu = false;}
      if(XArUtUsxQz == true){XArUtUsxQz = false;}
      if(ogTMmlFhKN == true){ogTMmlFhKN = false;}
      if(lZnkRRizwT == true){lZnkRRizwT = false;}
      if(XpZcqgcoSJ == true){XpZcqgcoSJ = false;}
      if(bStfUjxqRo == true){bStfUjxqRo = false;}
      if(SIVTJyLHDc == true){SIVTJyLHDc = false;}
      if(ksAxayHpUG == true){ksAxayHpUG = false;}
      if(IQOAkSfIPh == true){IQOAkSfIPh = false;}
      if(UqhHAOUFSr == true){UqhHAOUFSr = false;}
      if(UVkpXiSwEW == true){UVkpXiSwEW = false;}
      if(bGWLfCsUhq == true){bGWLfCsUhq = false;}
      if(SCqVIsLsxM == true){SCqVIsLsxM = false;}
      if(dBXckmeYbC == true){dBXckmeYbC = false;}
      if(AiEsFNUWay == true){AiEsFNUWay = false;}
      if(UzWbZSePge == true){UzWbZSePge = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LSGXAJCSGO
{ 
  void QiAQAfXnVB()
  { 
      bool gJJYGdENdB = false;
      bool ucAuxEMqXt = false;
      bool WOciGJxqZg = false;
      bool ezMGWOBXKV = false;
      bool iLwajlXLwF = false;
      bool arREjSgZRx = false;
      bool fMmxWuQtYh = false;
      bool CngBLLSCzU = false;
      bool kltUGmgHWD = false;
      bool haGMpWXyEn = false;
      bool VdmOClLPsX = false;
      bool AeawMtRSqi = false;
      bool NJWUAahTLn = false;
      bool nTxLzGzfST = false;
      bool bQNyDDAJAw = false;
      bool EEHUZLGRNa = false;
      bool EqEFjfgOxF = false;
      bool tkAWHwuXQw = false;
      bool aXTPiiLclm = false;
      bool AgSqPjMINW = false;
      string nWdPZXOVIY;
      string LjQPAlktQW;
      string pjTKZMjTrT;
      string KsJbbohthy;
      string qUAdrRYSlQ;
      string qMimgEDSoN;
      string ntdnOSaomL;
      string EpLRfUjoSI;
      string mRhbcxKVtX;
      string kPFUKwqLPY;
      string qjeZLBAQHL;
      string UOzfZVMBLQ;
      string IEtPaokqHi;
      string cYYsRDmHQa;
      string wsOhCWPYto;
      string iozyQloOzW;
      string QJJXhwoFOV;
      string hFkkTOpLNE;
      string YLwRAnYace;
      string OYHsKmjpzG;
      if(nWdPZXOVIY == qjeZLBAQHL){gJJYGdENdB = true;}
      else if(qjeZLBAQHL == nWdPZXOVIY){VdmOClLPsX = true;}
      if(LjQPAlktQW == UOzfZVMBLQ){ucAuxEMqXt = true;}
      else if(UOzfZVMBLQ == LjQPAlktQW){AeawMtRSqi = true;}
      if(pjTKZMjTrT == IEtPaokqHi){WOciGJxqZg = true;}
      else if(IEtPaokqHi == pjTKZMjTrT){NJWUAahTLn = true;}
      if(KsJbbohthy == cYYsRDmHQa){ezMGWOBXKV = true;}
      else if(cYYsRDmHQa == KsJbbohthy){nTxLzGzfST = true;}
      if(qUAdrRYSlQ == wsOhCWPYto){iLwajlXLwF = true;}
      else if(wsOhCWPYto == qUAdrRYSlQ){bQNyDDAJAw = true;}
      if(qMimgEDSoN == iozyQloOzW){arREjSgZRx = true;}
      else if(iozyQloOzW == qMimgEDSoN){EEHUZLGRNa = true;}
      if(ntdnOSaomL == QJJXhwoFOV){fMmxWuQtYh = true;}
      else if(QJJXhwoFOV == ntdnOSaomL){EqEFjfgOxF = true;}
      if(EpLRfUjoSI == hFkkTOpLNE){CngBLLSCzU = true;}
      if(mRhbcxKVtX == YLwRAnYace){kltUGmgHWD = true;}
      if(kPFUKwqLPY == OYHsKmjpzG){haGMpWXyEn = true;}
      while(hFkkTOpLNE == EpLRfUjoSI){tkAWHwuXQw = true;}
      while(YLwRAnYace == YLwRAnYace){aXTPiiLclm = true;}
      while(OYHsKmjpzG == OYHsKmjpzG){AgSqPjMINW = true;}
      if(gJJYGdENdB == true){gJJYGdENdB = false;}
      if(ucAuxEMqXt == true){ucAuxEMqXt = false;}
      if(WOciGJxqZg == true){WOciGJxqZg = false;}
      if(ezMGWOBXKV == true){ezMGWOBXKV = false;}
      if(iLwajlXLwF == true){iLwajlXLwF = false;}
      if(arREjSgZRx == true){arREjSgZRx = false;}
      if(fMmxWuQtYh == true){fMmxWuQtYh = false;}
      if(CngBLLSCzU == true){CngBLLSCzU = false;}
      if(kltUGmgHWD == true){kltUGmgHWD = false;}
      if(haGMpWXyEn == true){haGMpWXyEn = false;}
      if(VdmOClLPsX == true){VdmOClLPsX = false;}
      if(AeawMtRSqi == true){AeawMtRSqi = false;}
      if(NJWUAahTLn == true){NJWUAahTLn = false;}
      if(nTxLzGzfST == true){nTxLzGzfST = false;}
      if(bQNyDDAJAw == true){bQNyDDAJAw = false;}
      if(EEHUZLGRNa == true){EEHUZLGRNa = false;}
      if(EqEFjfgOxF == true){EqEFjfgOxF = false;}
      if(tkAWHwuXQw == true){tkAWHwuXQw = false;}
      if(aXTPiiLclm == true){aXTPiiLclm = false;}
      if(AgSqPjMINW == true){AgSqPjMINW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIHHIKZHBB
{ 
  void XqROecCUFO()
  { 
      bool ahwnaIPRTU = false;
      bool QIMbQCaCJb = false;
      bool rTmeAMuBTN = false;
      bool wisflzaBfF = false;
      bool ytMQVXLsai = false;
      bool XZTceGuQmN = false;
      bool NOxGYhPfoQ = false;
      bool aZVEdyHVJc = false;
      bool BBZkoVPPBf = false;
      bool EKNRqiwFrn = false;
      bool HfEKHxEOzg = false;
      bool zZGKMLnMQD = false;
      bool SAdJMPLDMt = false;
      bool BBcUUVxPcr = false;
      bool QAQUfdDDFf = false;
      bool ujnoVHBuxq = false;
      bool kABFfywlop = false;
      bool NYjYlRiJch = false;
      bool MIygzRMnzN = false;
      bool UCRkGPyLng = false;
      string DnCQzoRcHl;
      string XleSKCaCCE;
      string QuBNYodBQT;
      string SyLeWdBpBw;
      string QDZcdRArLn;
      string xbizYHmnrK;
      string KQLmTZZzug;
      string BkBFmNUXjH;
      string okocWqPMGO;
      string qMyqkAqlJD;
      string qAwemLacLL;
      string mOEjVYaiPc;
      string KNsfpolKTm;
      string VhNfQnnKpK;
      string PlBtbbHOUM;
      string YIVgsdHQoy;
      string ZQJXoEAYSg;
      string kQsEMXMyEN;
      string gWoHNNLglm;
      string gXUqkzbcFX;
      if(DnCQzoRcHl == qAwemLacLL){ahwnaIPRTU = true;}
      else if(qAwemLacLL == DnCQzoRcHl){HfEKHxEOzg = true;}
      if(XleSKCaCCE == mOEjVYaiPc){QIMbQCaCJb = true;}
      else if(mOEjVYaiPc == XleSKCaCCE){zZGKMLnMQD = true;}
      if(QuBNYodBQT == KNsfpolKTm){rTmeAMuBTN = true;}
      else if(KNsfpolKTm == QuBNYodBQT){SAdJMPLDMt = true;}
      if(SyLeWdBpBw == VhNfQnnKpK){wisflzaBfF = true;}
      else if(VhNfQnnKpK == SyLeWdBpBw){BBcUUVxPcr = true;}
      if(QDZcdRArLn == PlBtbbHOUM){ytMQVXLsai = true;}
      else if(PlBtbbHOUM == QDZcdRArLn){QAQUfdDDFf = true;}
      if(xbizYHmnrK == YIVgsdHQoy){XZTceGuQmN = true;}
      else if(YIVgsdHQoy == xbizYHmnrK){ujnoVHBuxq = true;}
      if(KQLmTZZzug == ZQJXoEAYSg){NOxGYhPfoQ = true;}
      else if(ZQJXoEAYSg == KQLmTZZzug){kABFfywlop = true;}
      if(BkBFmNUXjH == kQsEMXMyEN){aZVEdyHVJc = true;}
      if(okocWqPMGO == gWoHNNLglm){BBZkoVPPBf = true;}
      if(qMyqkAqlJD == gXUqkzbcFX){EKNRqiwFrn = true;}
      while(kQsEMXMyEN == BkBFmNUXjH){NYjYlRiJch = true;}
      while(gWoHNNLglm == gWoHNNLglm){MIygzRMnzN = true;}
      while(gXUqkzbcFX == gXUqkzbcFX){UCRkGPyLng = true;}
      if(ahwnaIPRTU == true){ahwnaIPRTU = false;}
      if(QIMbQCaCJb == true){QIMbQCaCJb = false;}
      if(rTmeAMuBTN == true){rTmeAMuBTN = false;}
      if(wisflzaBfF == true){wisflzaBfF = false;}
      if(ytMQVXLsai == true){ytMQVXLsai = false;}
      if(XZTceGuQmN == true){XZTceGuQmN = false;}
      if(NOxGYhPfoQ == true){NOxGYhPfoQ = false;}
      if(aZVEdyHVJc == true){aZVEdyHVJc = false;}
      if(BBZkoVPPBf == true){BBZkoVPPBf = false;}
      if(EKNRqiwFrn == true){EKNRqiwFrn = false;}
      if(HfEKHxEOzg == true){HfEKHxEOzg = false;}
      if(zZGKMLnMQD == true){zZGKMLnMQD = false;}
      if(SAdJMPLDMt == true){SAdJMPLDMt = false;}
      if(BBcUUVxPcr == true){BBcUUVxPcr = false;}
      if(QAQUfdDDFf == true){QAQUfdDDFf = false;}
      if(ujnoVHBuxq == true){ujnoVHBuxq = false;}
      if(kABFfywlop == true){kABFfywlop = false;}
      if(NYjYlRiJch == true){NYjYlRiJch = false;}
      if(MIygzRMnzN == true){MIygzRMnzN = false;}
      if(UCRkGPyLng == true){UCRkGPyLng = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DHOGHFYFNT
{ 
  void rkYWwXTdzi()
  { 
      bool qrPlVdOsxU = false;
      bool XLbEpaNsLX = false;
      bool nIBjWIUPSm = false;
      bool mJZdyVrVeH = false;
      bool DKYtBmaubG = false;
      bool JmbHdhqePM = false;
      bool IzaKgNlxFU = false;
      bool iqNDTdiHii = false;
      bool hYmMcAhRAP = false;
      bool eMGRzEjONn = false;
      bool BcoHXRYXmA = false;
      bool ziwfejMNgg = false;
      bool eTwppVjwEP = false;
      bool sTttgEifoK = false;
      bool aJeAQuQamP = false;
      bool rVhgIhgzRB = false;
      bool gcSXGeoBya = false;
      bool AgYWFVowZt = false;
      bool EJIoXWlNlz = false;
      bool XjNmcxpHtk = false;
      string UhTPssDmNC;
      string aHIKUitnSW;
      string gUiOLCyreN;
      string UfCEBdhhhQ;
      string YMLscKuptd;
      string dpdgazyEEp;
      string uLHAguFEJp;
      string ALFCyUIokA;
      string GIxBidBUcB;
      string ecdqUNELLh;
      string FqfEcRjbiG;
      string pJTEjmNGRD;
      string sjaHKXhOhk;
      string PxdDtObsXQ;
      string sZlVKVJZGg;
      string zxsHnVQYsF;
      string jVsypreQJU;
      string LUhAKTyEwo;
      string OIHAlSEWOY;
      string yCzSgXfneR;
      if(UhTPssDmNC == FqfEcRjbiG){qrPlVdOsxU = true;}
      else if(FqfEcRjbiG == UhTPssDmNC){BcoHXRYXmA = true;}
      if(aHIKUitnSW == pJTEjmNGRD){XLbEpaNsLX = true;}
      else if(pJTEjmNGRD == aHIKUitnSW){ziwfejMNgg = true;}
      if(gUiOLCyreN == sjaHKXhOhk){nIBjWIUPSm = true;}
      else if(sjaHKXhOhk == gUiOLCyreN){eTwppVjwEP = true;}
      if(UfCEBdhhhQ == PxdDtObsXQ){mJZdyVrVeH = true;}
      else if(PxdDtObsXQ == UfCEBdhhhQ){sTttgEifoK = true;}
      if(YMLscKuptd == sZlVKVJZGg){DKYtBmaubG = true;}
      else if(sZlVKVJZGg == YMLscKuptd){aJeAQuQamP = true;}
      if(dpdgazyEEp == zxsHnVQYsF){JmbHdhqePM = true;}
      else if(zxsHnVQYsF == dpdgazyEEp){rVhgIhgzRB = true;}
      if(uLHAguFEJp == jVsypreQJU){IzaKgNlxFU = true;}
      else if(jVsypreQJU == uLHAguFEJp){gcSXGeoBya = true;}
      if(ALFCyUIokA == LUhAKTyEwo){iqNDTdiHii = true;}
      if(GIxBidBUcB == OIHAlSEWOY){hYmMcAhRAP = true;}
      if(ecdqUNELLh == yCzSgXfneR){eMGRzEjONn = true;}
      while(LUhAKTyEwo == ALFCyUIokA){AgYWFVowZt = true;}
      while(OIHAlSEWOY == OIHAlSEWOY){EJIoXWlNlz = true;}
      while(yCzSgXfneR == yCzSgXfneR){XjNmcxpHtk = true;}
      if(qrPlVdOsxU == true){qrPlVdOsxU = false;}
      if(XLbEpaNsLX == true){XLbEpaNsLX = false;}
      if(nIBjWIUPSm == true){nIBjWIUPSm = false;}
      if(mJZdyVrVeH == true){mJZdyVrVeH = false;}
      if(DKYtBmaubG == true){DKYtBmaubG = false;}
      if(JmbHdhqePM == true){JmbHdhqePM = false;}
      if(IzaKgNlxFU == true){IzaKgNlxFU = false;}
      if(iqNDTdiHii == true){iqNDTdiHii = false;}
      if(hYmMcAhRAP == true){hYmMcAhRAP = false;}
      if(eMGRzEjONn == true){eMGRzEjONn = false;}
      if(BcoHXRYXmA == true){BcoHXRYXmA = false;}
      if(ziwfejMNgg == true){ziwfejMNgg = false;}
      if(eTwppVjwEP == true){eTwppVjwEP = false;}
      if(sTttgEifoK == true){sTttgEifoK = false;}
      if(aJeAQuQamP == true){aJeAQuQamP = false;}
      if(rVhgIhgzRB == true){rVhgIhgzRB = false;}
      if(gcSXGeoBya == true){gcSXGeoBya = false;}
      if(AgYWFVowZt == true){AgYWFVowZt = false;}
      if(EJIoXWlNlz == true){EJIoXWlNlz = false;}
      if(XjNmcxpHtk == true){XjNmcxpHtk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NVPPKAQBDB
{ 
  void NcjxfYasbP()
  { 
      bool XJQogKkpNy = false;
      bool YkPKOfdBkz = false;
      bool FuGYIsIMux = false;
      bool huOsWlHDUr = false;
      bool AdmjWHTgKr = false;
      bool NocRibCqfn = false;
      bool CXuQQcWVmc = false;
      bool XagryaIWBB = false;
      bool YaBCirRwKu = false;
      bool iPWgobiVTs = false;
      bool jxshUmIjSH = false;
      bool SfpeOaWrhX = false;
      bool LZLrtHDzDW = false;
      bool qlDHRahShu = false;
      bool jgdCbDZrRO = false;
      bool EqnuhJlBnN = false;
      bool jIguQgciNm = false;
      bool sDKlnewIQq = false;
      bool hKhnSAxHYH = false;
      bool ofeULazilt = false;
      string MMGJoPhAim;
      string YrMWXfDAbn;
      string LYxNkYhVmx;
      string LyanHloIQz;
      string TIoiQLTIFw;
      string HppWunPsYP;
      string hMNkaaQXPk;
      string qtjbUDiNwY;
      string FYPppVHErT;
      string WwjARGuEIp;
      string twsTFNGNBr;
      string EBwzKIwXuF;
      string SMewOuJiKN;
      string IdEGdJfwkb;
      string PtCAOUzkpI;
      string KXJDWhQxEK;
      string EWDnjZxpUB;
      string bzlSoYJegt;
      string uYrBDkUBiw;
      string riqZXrqOQn;
      if(MMGJoPhAim == twsTFNGNBr){XJQogKkpNy = true;}
      else if(twsTFNGNBr == MMGJoPhAim){jxshUmIjSH = true;}
      if(YrMWXfDAbn == EBwzKIwXuF){YkPKOfdBkz = true;}
      else if(EBwzKIwXuF == YrMWXfDAbn){SfpeOaWrhX = true;}
      if(LYxNkYhVmx == SMewOuJiKN){FuGYIsIMux = true;}
      else if(SMewOuJiKN == LYxNkYhVmx){LZLrtHDzDW = true;}
      if(LyanHloIQz == IdEGdJfwkb){huOsWlHDUr = true;}
      else if(IdEGdJfwkb == LyanHloIQz){qlDHRahShu = true;}
      if(TIoiQLTIFw == PtCAOUzkpI){AdmjWHTgKr = true;}
      else if(PtCAOUzkpI == TIoiQLTIFw){jgdCbDZrRO = true;}
      if(HppWunPsYP == KXJDWhQxEK){NocRibCqfn = true;}
      else if(KXJDWhQxEK == HppWunPsYP){EqnuhJlBnN = true;}
      if(hMNkaaQXPk == EWDnjZxpUB){CXuQQcWVmc = true;}
      else if(EWDnjZxpUB == hMNkaaQXPk){jIguQgciNm = true;}
      if(qtjbUDiNwY == bzlSoYJegt){XagryaIWBB = true;}
      if(FYPppVHErT == uYrBDkUBiw){YaBCirRwKu = true;}
      if(WwjARGuEIp == riqZXrqOQn){iPWgobiVTs = true;}
      while(bzlSoYJegt == qtjbUDiNwY){sDKlnewIQq = true;}
      while(uYrBDkUBiw == uYrBDkUBiw){hKhnSAxHYH = true;}
      while(riqZXrqOQn == riqZXrqOQn){ofeULazilt = true;}
      if(XJQogKkpNy == true){XJQogKkpNy = false;}
      if(YkPKOfdBkz == true){YkPKOfdBkz = false;}
      if(FuGYIsIMux == true){FuGYIsIMux = false;}
      if(huOsWlHDUr == true){huOsWlHDUr = false;}
      if(AdmjWHTgKr == true){AdmjWHTgKr = false;}
      if(NocRibCqfn == true){NocRibCqfn = false;}
      if(CXuQQcWVmc == true){CXuQQcWVmc = false;}
      if(XagryaIWBB == true){XagryaIWBB = false;}
      if(YaBCirRwKu == true){YaBCirRwKu = false;}
      if(iPWgobiVTs == true){iPWgobiVTs = false;}
      if(jxshUmIjSH == true){jxshUmIjSH = false;}
      if(SfpeOaWrhX == true){SfpeOaWrhX = false;}
      if(LZLrtHDzDW == true){LZLrtHDzDW = false;}
      if(qlDHRahShu == true){qlDHRahShu = false;}
      if(jgdCbDZrRO == true){jgdCbDZrRO = false;}
      if(EqnuhJlBnN == true){EqnuhJlBnN = false;}
      if(jIguQgciNm == true){jIguQgciNm = false;}
      if(sDKlnewIQq == true){sDKlnewIQq = false;}
      if(hKhnSAxHYH == true){hKhnSAxHYH = false;}
      if(ofeULazilt == true){ofeULazilt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TEUVEMPFOE
{ 
  void gajBLWzdOI()
  { 
      bool MZmGBnzmUu = false;
      bool kUqiyIrKDu = false;
      bool TUmoPNzkTx = false;
      bool yrOQIjgTkL = false;
      bool gewMKDYbJG = false;
      bool jcKoBqlypm = false;
      bool oNTWxsGaZO = false;
      bool aYYrOoXadM = false;
      bool oWaMNUgZOR = false;
      bool yidxVSKZPR = false;
      bool wyBueLDRaM = false;
      bool SLTcyRmHIb = false;
      bool LgMHQqtbVu = false;
      bool dyKMQpVegC = false;
      bool ROyBymPBzE = false;
      bool fDQmFPlsem = false;
      bool QbweiTAHMH = false;
      bool wHZGKwhKIc = false;
      bool bsbRPZhWGA = false;
      bool EbAtloSTSe = false;
      string qWspXPwyTU;
      string LkLdtYQaWI;
      string AbuPMVXhgc;
      string Rospyakadx;
      string lVoSXIzEsb;
      string NjoYeObdcC;
      string rOQqCVrVeT;
      string mpwYWdmcqD;
      string VSoFPhATLj;
      string yHxaFXEyPC;
      string PdYZnWmQCA;
      string azlYgYZLbU;
      string UYJuUfsUSy;
      string YoMonrtPRs;
      string tjRKIzVXtf;
      string ysVugqTdEI;
      string cSxDalmwkn;
      string eJtiZkGylV;
      string JUZmzfSRIw;
      string XQKIPbmOjV;
      if(qWspXPwyTU == PdYZnWmQCA){MZmGBnzmUu = true;}
      else if(PdYZnWmQCA == qWspXPwyTU){wyBueLDRaM = true;}
      if(LkLdtYQaWI == azlYgYZLbU){kUqiyIrKDu = true;}
      else if(azlYgYZLbU == LkLdtYQaWI){SLTcyRmHIb = true;}
      if(AbuPMVXhgc == UYJuUfsUSy){TUmoPNzkTx = true;}
      else if(UYJuUfsUSy == AbuPMVXhgc){LgMHQqtbVu = true;}
      if(Rospyakadx == YoMonrtPRs){yrOQIjgTkL = true;}
      else if(YoMonrtPRs == Rospyakadx){dyKMQpVegC = true;}
      if(lVoSXIzEsb == tjRKIzVXtf){gewMKDYbJG = true;}
      else if(tjRKIzVXtf == lVoSXIzEsb){ROyBymPBzE = true;}
      if(NjoYeObdcC == ysVugqTdEI){jcKoBqlypm = true;}
      else if(ysVugqTdEI == NjoYeObdcC){fDQmFPlsem = true;}
      if(rOQqCVrVeT == cSxDalmwkn){oNTWxsGaZO = true;}
      else if(cSxDalmwkn == rOQqCVrVeT){QbweiTAHMH = true;}
      if(mpwYWdmcqD == eJtiZkGylV){aYYrOoXadM = true;}
      if(VSoFPhATLj == JUZmzfSRIw){oWaMNUgZOR = true;}
      if(yHxaFXEyPC == XQKIPbmOjV){yidxVSKZPR = true;}
      while(eJtiZkGylV == mpwYWdmcqD){wHZGKwhKIc = true;}
      while(JUZmzfSRIw == JUZmzfSRIw){bsbRPZhWGA = true;}
      while(XQKIPbmOjV == XQKIPbmOjV){EbAtloSTSe = true;}
      if(MZmGBnzmUu == true){MZmGBnzmUu = false;}
      if(kUqiyIrKDu == true){kUqiyIrKDu = false;}
      if(TUmoPNzkTx == true){TUmoPNzkTx = false;}
      if(yrOQIjgTkL == true){yrOQIjgTkL = false;}
      if(gewMKDYbJG == true){gewMKDYbJG = false;}
      if(jcKoBqlypm == true){jcKoBqlypm = false;}
      if(oNTWxsGaZO == true){oNTWxsGaZO = false;}
      if(aYYrOoXadM == true){aYYrOoXadM = false;}
      if(oWaMNUgZOR == true){oWaMNUgZOR = false;}
      if(yidxVSKZPR == true){yidxVSKZPR = false;}
      if(wyBueLDRaM == true){wyBueLDRaM = false;}
      if(SLTcyRmHIb == true){SLTcyRmHIb = false;}
      if(LgMHQqtbVu == true){LgMHQqtbVu = false;}
      if(dyKMQpVegC == true){dyKMQpVegC = false;}
      if(ROyBymPBzE == true){ROyBymPBzE = false;}
      if(fDQmFPlsem == true){fDQmFPlsem = false;}
      if(QbweiTAHMH == true){QbweiTAHMH = false;}
      if(wHZGKwhKIc == true){wHZGKwhKIc = false;}
      if(bsbRPZhWGA == true){bsbRPZhWGA = false;}
      if(EbAtloSTSe == true){EbAtloSTSe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IALPDCGHJU
{ 
  void lndFbNgapm()
  { 
      bool FKVBxSgzNm = false;
      bool fRybRAFppN = false;
      bool YaXARUhNWV = false;
      bool aCUTPTNpRm = false;
      bool UNjGTDxuZE = false;
      bool FnbuXdlVic = false;
      bool kScqLcwdMy = false;
      bool mOXCsKqRfN = false;
      bool WlnRPlaZwk = false;
      bool gqGoCBkrtq = false;
      bool HTibRqQYBM = false;
      bool mToVGzeLbY = false;
      bool CWgaRuHiAq = false;
      bool ZyWoGCCLzY = false;
      bool VBXixMBkiC = false;
      bool WZQUoklIJV = false;
      bool jgYKmowAOD = false;
      bool wSLCCAzxdE = false;
      bool sVzxTAhCAV = false;
      bool PtBcnocMwI = false;
      string ojDfSzwNBR;
      string jWihkynnHS;
      string ldpYtxzGdB;
      string pWwCWpLJOo;
      string nQsMzJfZpn;
      string UDBGZLtdlV;
      string ApjzbMZfKt;
      string mdYRdVjcYk;
      string QYPoglUpcK;
      string ugXrnygtjl;
      string jzOuBpdibD;
      string bREBEaZtSo;
      string riDzzFGgce;
      string normARKTnp;
      string IkOYidbWnN;
      string YmbusAwOwu;
      string jxGwPlYRAm;
      string QFGbgGUeQU;
      string djrPGBNxsA;
      string UuXrFKeRJw;
      if(ojDfSzwNBR == jzOuBpdibD){FKVBxSgzNm = true;}
      else if(jzOuBpdibD == ojDfSzwNBR){HTibRqQYBM = true;}
      if(jWihkynnHS == bREBEaZtSo){fRybRAFppN = true;}
      else if(bREBEaZtSo == jWihkynnHS){mToVGzeLbY = true;}
      if(ldpYtxzGdB == riDzzFGgce){YaXARUhNWV = true;}
      else if(riDzzFGgce == ldpYtxzGdB){CWgaRuHiAq = true;}
      if(pWwCWpLJOo == normARKTnp){aCUTPTNpRm = true;}
      else if(normARKTnp == pWwCWpLJOo){ZyWoGCCLzY = true;}
      if(nQsMzJfZpn == IkOYidbWnN){UNjGTDxuZE = true;}
      else if(IkOYidbWnN == nQsMzJfZpn){VBXixMBkiC = true;}
      if(UDBGZLtdlV == YmbusAwOwu){FnbuXdlVic = true;}
      else if(YmbusAwOwu == UDBGZLtdlV){WZQUoklIJV = true;}
      if(ApjzbMZfKt == jxGwPlYRAm){kScqLcwdMy = true;}
      else if(jxGwPlYRAm == ApjzbMZfKt){jgYKmowAOD = true;}
      if(mdYRdVjcYk == QFGbgGUeQU){mOXCsKqRfN = true;}
      if(QYPoglUpcK == djrPGBNxsA){WlnRPlaZwk = true;}
      if(ugXrnygtjl == UuXrFKeRJw){gqGoCBkrtq = true;}
      while(QFGbgGUeQU == mdYRdVjcYk){wSLCCAzxdE = true;}
      while(djrPGBNxsA == djrPGBNxsA){sVzxTAhCAV = true;}
      while(UuXrFKeRJw == UuXrFKeRJw){PtBcnocMwI = true;}
      if(FKVBxSgzNm == true){FKVBxSgzNm = false;}
      if(fRybRAFppN == true){fRybRAFppN = false;}
      if(YaXARUhNWV == true){YaXARUhNWV = false;}
      if(aCUTPTNpRm == true){aCUTPTNpRm = false;}
      if(UNjGTDxuZE == true){UNjGTDxuZE = false;}
      if(FnbuXdlVic == true){FnbuXdlVic = false;}
      if(kScqLcwdMy == true){kScqLcwdMy = false;}
      if(mOXCsKqRfN == true){mOXCsKqRfN = false;}
      if(WlnRPlaZwk == true){WlnRPlaZwk = false;}
      if(gqGoCBkrtq == true){gqGoCBkrtq = false;}
      if(HTibRqQYBM == true){HTibRqQYBM = false;}
      if(mToVGzeLbY == true){mToVGzeLbY = false;}
      if(CWgaRuHiAq == true){CWgaRuHiAq = false;}
      if(ZyWoGCCLzY == true){ZyWoGCCLzY = false;}
      if(VBXixMBkiC == true){VBXixMBkiC = false;}
      if(WZQUoklIJV == true){WZQUoklIJV = false;}
      if(jgYKmowAOD == true){jgYKmowAOD = false;}
      if(wSLCCAzxdE == true){wSLCCAzxdE = false;}
      if(sVzxTAhCAV == true){sVzxTAhCAV = false;}
      if(PtBcnocMwI == true){PtBcnocMwI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QKPMCNBYTF
{ 
  void ZoMpsHFubM()
  { 
      bool fQpdPttoQO = false;
      bool qynAINuFRx = false;
      bool NNdJtqQbEJ = false;
      bool lSHeQiLFOu = false;
      bool qbXBYloxeI = false;
      bool sUQrlRlgiX = false;
      bool dRkGcYpJjY = false;
      bool CppVGlpbjH = false;
      bool CTxuQQBPry = false;
      bool xeVqRYqQYA = false;
      bool weMGGDeulA = false;
      bool bJwaUKUopL = false;
      bool WZQkbWUyDg = false;
      bool tZDjLXGqoM = false;
      bool lGdrWmhtWH = false;
      bool ECZMcVNaei = false;
      bool hgqEFBGMOx = false;
      bool DczcZQwYOn = false;
      bool oZawcrzqGp = false;
      bool JfMGeFOYlU = false;
      string uYpDHGCRKh;
      string HMfQEfDqTR;
      string NXePWwKUqa;
      string YbWDOjXhfA;
      string zuNrbawgxb;
      string EhSYxWtZfL;
      string wgZjJeocCU;
      string IULTRRKmnu;
      string AcXPVpJxFq;
      string oxBTESVdiw;
      string kTebTiWzHf;
      string MGlkLSJKNS;
      string VrWKeLSqPz;
      string wgEqKgxuum;
      string TJpYehKQIk;
      string IKPPaswTxI;
      string PejHjeCtae;
      string VOPayLBxew;
      string ACieplQnQQ;
      string jdxmWoZhoA;
      if(uYpDHGCRKh == kTebTiWzHf){fQpdPttoQO = true;}
      else if(kTebTiWzHf == uYpDHGCRKh){weMGGDeulA = true;}
      if(HMfQEfDqTR == MGlkLSJKNS){qynAINuFRx = true;}
      else if(MGlkLSJKNS == HMfQEfDqTR){bJwaUKUopL = true;}
      if(NXePWwKUqa == VrWKeLSqPz){NNdJtqQbEJ = true;}
      else if(VrWKeLSqPz == NXePWwKUqa){WZQkbWUyDg = true;}
      if(YbWDOjXhfA == wgEqKgxuum){lSHeQiLFOu = true;}
      else if(wgEqKgxuum == YbWDOjXhfA){tZDjLXGqoM = true;}
      if(zuNrbawgxb == TJpYehKQIk){qbXBYloxeI = true;}
      else if(TJpYehKQIk == zuNrbawgxb){lGdrWmhtWH = true;}
      if(EhSYxWtZfL == IKPPaswTxI){sUQrlRlgiX = true;}
      else if(IKPPaswTxI == EhSYxWtZfL){ECZMcVNaei = true;}
      if(wgZjJeocCU == PejHjeCtae){dRkGcYpJjY = true;}
      else if(PejHjeCtae == wgZjJeocCU){hgqEFBGMOx = true;}
      if(IULTRRKmnu == VOPayLBxew){CppVGlpbjH = true;}
      if(AcXPVpJxFq == ACieplQnQQ){CTxuQQBPry = true;}
      if(oxBTESVdiw == jdxmWoZhoA){xeVqRYqQYA = true;}
      while(VOPayLBxew == IULTRRKmnu){DczcZQwYOn = true;}
      while(ACieplQnQQ == ACieplQnQQ){oZawcrzqGp = true;}
      while(jdxmWoZhoA == jdxmWoZhoA){JfMGeFOYlU = true;}
      if(fQpdPttoQO == true){fQpdPttoQO = false;}
      if(qynAINuFRx == true){qynAINuFRx = false;}
      if(NNdJtqQbEJ == true){NNdJtqQbEJ = false;}
      if(lSHeQiLFOu == true){lSHeQiLFOu = false;}
      if(qbXBYloxeI == true){qbXBYloxeI = false;}
      if(sUQrlRlgiX == true){sUQrlRlgiX = false;}
      if(dRkGcYpJjY == true){dRkGcYpJjY = false;}
      if(CppVGlpbjH == true){CppVGlpbjH = false;}
      if(CTxuQQBPry == true){CTxuQQBPry = false;}
      if(xeVqRYqQYA == true){xeVqRYqQYA = false;}
      if(weMGGDeulA == true){weMGGDeulA = false;}
      if(bJwaUKUopL == true){bJwaUKUopL = false;}
      if(WZQkbWUyDg == true){WZQkbWUyDg = false;}
      if(tZDjLXGqoM == true){tZDjLXGqoM = false;}
      if(lGdrWmhtWH == true){lGdrWmhtWH = false;}
      if(ECZMcVNaei == true){ECZMcVNaei = false;}
      if(hgqEFBGMOx == true){hgqEFBGMOx = false;}
      if(DczcZQwYOn == true){DczcZQwYOn = false;}
      if(oZawcrzqGp == true){oZawcrzqGp = false;}
      if(JfMGeFOYlU == true){JfMGeFOYlU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IBBWPOAAFB
{ 
  void mzqDeAlKLi()
  { 
      bool rhaycueYAh = false;
      bool sUBexKTqEA = false;
      bool uuitugTlWU = false;
      bool HiORswrIQq = false;
      bool ZwJcxXpSGf = false;
      bool yJhIKwyfCw = false;
      bool bsBeaJGikB = false;
      bool SLZNazlGxX = false;
      bool pAepWxBFHw = false;
      bool xMFUOftdBm = false;
      bool QGhFNliUhL = false;
      bool KrieFaNLHc = false;
      bool IAbnDFFFyt = false;
      bool FHEJGjSYck = false;
      bool OfWwlEcaOn = false;
      bool SiWYeQesCH = false;
      bool fdVmFDmZXV = false;
      bool InhWObceCy = false;
      bool ceqKbWjfdp = false;
      bool EYWUEjKjpi = false;
      string lwcVcfoLwe;
      string IZiBxqCGGf;
      string sbdrHkDtbc;
      string kqExHQKRCT;
      string masNDkSPgO;
      string uXUjzJRkNq;
      string ctiSsQUksg;
      string fjDmsSiQnV;
      string SmNNhMVUxx;
      string yYDKpsqZTl;
      string PgVzhKThpg;
      string aBwqYofVkf;
      string uAnwiGfswz;
      string aJwBGkROeW;
      string smdPWwcMlB;
      string MVnmqPsZQa;
      string ealqFQEtkm;
      string XRpOmIVXYl;
      string dTGtlFUJKp;
      string rqxDqRBmJG;
      if(lwcVcfoLwe == PgVzhKThpg){rhaycueYAh = true;}
      else if(PgVzhKThpg == lwcVcfoLwe){QGhFNliUhL = true;}
      if(IZiBxqCGGf == aBwqYofVkf){sUBexKTqEA = true;}
      else if(aBwqYofVkf == IZiBxqCGGf){KrieFaNLHc = true;}
      if(sbdrHkDtbc == uAnwiGfswz){uuitugTlWU = true;}
      else if(uAnwiGfswz == sbdrHkDtbc){IAbnDFFFyt = true;}
      if(kqExHQKRCT == aJwBGkROeW){HiORswrIQq = true;}
      else if(aJwBGkROeW == kqExHQKRCT){FHEJGjSYck = true;}
      if(masNDkSPgO == smdPWwcMlB){ZwJcxXpSGf = true;}
      else if(smdPWwcMlB == masNDkSPgO){OfWwlEcaOn = true;}
      if(uXUjzJRkNq == MVnmqPsZQa){yJhIKwyfCw = true;}
      else if(MVnmqPsZQa == uXUjzJRkNq){SiWYeQesCH = true;}
      if(ctiSsQUksg == ealqFQEtkm){bsBeaJGikB = true;}
      else if(ealqFQEtkm == ctiSsQUksg){fdVmFDmZXV = true;}
      if(fjDmsSiQnV == XRpOmIVXYl){SLZNazlGxX = true;}
      if(SmNNhMVUxx == dTGtlFUJKp){pAepWxBFHw = true;}
      if(yYDKpsqZTl == rqxDqRBmJG){xMFUOftdBm = true;}
      while(XRpOmIVXYl == fjDmsSiQnV){InhWObceCy = true;}
      while(dTGtlFUJKp == dTGtlFUJKp){ceqKbWjfdp = true;}
      while(rqxDqRBmJG == rqxDqRBmJG){EYWUEjKjpi = true;}
      if(rhaycueYAh == true){rhaycueYAh = false;}
      if(sUBexKTqEA == true){sUBexKTqEA = false;}
      if(uuitugTlWU == true){uuitugTlWU = false;}
      if(HiORswrIQq == true){HiORswrIQq = false;}
      if(ZwJcxXpSGf == true){ZwJcxXpSGf = false;}
      if(yJhIKwyfCw == true){yJhIKwyfCw = false;}
      if(bsBeaJGikB == true){bsBeaJGikB = false;}
      if(SLZNazlGxX == true){SLZNazlGxX = false;}
      if(pAepWxBFHw == true){pAepWxBFHw = false;}
      if(xMFUOftdBm == true){xMFUOftdBm = false;}
      if(QGhFNliUhL == true){QGhFNliUhL = false;}
      if(KrieFaNLHc == true){KrieFaNLHc = false;}
      if(IAbnDFFFyt == true){IAbnDFFFyt = false;}
      if(FHEJGjSYck == true){FHEJGjSYck = false;}
      if(OfWwlEcaOn == true){OfWwlEcaOn = false;}
      if(SiWYeQesCH == true){SiWYeQesCH = false;}
      if(fdVmFDmZXV == true){fdVmFDmZXV = false;}
      if(InhWObceCy == true){InhWObceCy = false;}
      if(ceqKbWjfdp == true){ceqKbWjfdp = false;}
      if(EYWUEjKjpi == true){EYWUEjKjpi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQHQSUKXIW
{ 
  void IDnSWWPxnb()
  { 
      bool VBjVgmTJJP = false;
      bool xrRtuckDmo = false;
      bool tSsyUWkhsl = false;
      bool jiykjzxNqL = false;
      bool qqFFDMfJxV = false;
      bool sdZRyCHlBK = false;
      bool BkPXfNsfJw = false;
      bool eWMbyCNmtI = false;
      bool pbkWsGJglh = false;
      bool rLMfJFahZp = false;
      bool SAzBqWQySw = false;
      bool nTqsTZAseY = false;
      bool EMsbDTJfRr = false;
      bool afNEopbifV = false;
      bool oKNpsYTTMi = false;
      bool FhCBlGGXyW = false;
      bool MjfaUIGmDd = false;
      bool yRMIisyCie = false;
      bool ApTilrcLRh = false;
      bool iDkJJFdmUj = false;
      string BtyNuAPuqg;
      string siUxYYCdfZ;
      string IunOjCcJXF;
      string OEZrrjUHUo;
      string aloIyzmTxS;
      string VMsMdFFjds;
      string XFXkRnJbFn;
      string DtJqyVGfPj;
      string OIMFjCLNOm;
      string dkdaQVODpK;
      string oLOJOaDBNH;
      string yZUtdOrSBP;
      string bwMSJRQhZb;
      string HDpEtDtDpI;
      string zJzHnEQixB;
      string cwCZhsywzw;
      string JVblAuiPza;
      string UobrPSwFdF;
      string BgjXyLBPVA;
      string FyDsydhNGs;
      if(BtyNuAPuqg == oLOJOaDBNH){VBjVgmTJJP = true;}
      else if(oLOJOaDBNH == BtyNuAPuqg){SAzBqWQySw = true;}
      if(siUxYYCdfZ == yZUtdOrSBP){xrRtuckDmo = true;}
      else if(yZUtdOrSBP == siUxYYCdfZ){nTqsTZAseY = true;}
      if(IunOjCcJXF == bwMSJRQhZb){tSsyUWkhsl = true;}
      else if(bwMSJRQhZb == IunOjCcJXF){EMsbDTJfRr = true;}
      if(OEZrrjUHUo == HDpEtDtDpI){jiykjzxNqL = true;}
      else if(HDpEtDtDpI == OEZrrjUHUo){afNEopbifV = true;}
      if(aloIyzmTxS == zJzHnEQixB){qqFFDMfJxV = true;}
      else if(zJzHnEQixB == aloIyzmTxS){oKNpsYTTMi = true;}
      if(VMsMdFFjds == cwCZhsywzw){sdZRyCHlBK = true;}
      else if(cwCZhsywzw == VMsMdFFjds){FhCBlGGXyW = true;}
      if(XFXkRnJbFn == JVblAuiPza){BkPXfNsfJw = true;}
      else if(JVblAuiPza == XFXkRnJbFn){MjfaUIGmDd = true;}
      if(DtJqyVGfPj == UobrPSwFdF){eWMbyCNmtI = true;}
      if(OIMFjCLNOm == BgjXyLBPVA){pbkWsGJglh = true;}
      if(dkdaQVODpK == FyDsydhNGs){rLMfJFahZp = true;}
      while(UobrPSwFdF == DtJqyVGfPj){yRMIisyCie = true;}
      while(BgjXyLBPVA == BgjXyLBPVA){ApTilrcLRh = true;}
      while(FyDsydhNGs == FyDsydhNGs){iDkJJFdmUj = true;}
      if(VBjVgmTJJP == true){VBjVgmTJJP = false;}
      if(xrRtuckDmo == true){xrRtuckDmo = false;}
      if(tSsyUWkhsl == true){tSsyUWkhsl = false;}
      if(jiykjzxNqL == true){jiykjzxNqL = false;}
      if(qqFFDMfJxV == true){qqFFDMfJxV = false;}
      if(sdZRyCHlBK == true){sdZRyCHlBK = false;}
      if(BkPXfNsfJw == true){BkPXfNsfJw = false;}
      if(eWMbyCNmtI == true){eWMbyCNmtI = false;}
      if(pbkWsGJglh == true){pbkWsGJglh = false;}
      if(rLMfJFahZp == true){rLMfJFahZp = false;}
      if(SAzBqWQySw == true){SAzBqWQySw = false;}
      if(nTqsTZAseY == true){nTqsTZAseY = false;}
      if(EMsbDTJfRr == true){EMsbDTJfRr = false;}
      if(afNEopbifV == true){afNEopbifV = false;}
      if(oKNpsYTTMi == true){oKNpsYTTMi = false;}
      if(FhCBlGGXyW == true){FhCBlGGXyW = false;}
      if(MjfaUIGmDd == true){MjfaUIGmDd = false;}
      if(yRMIisyCie == true){yRMIisyCie = false;}
      if(ApTilrcLRh == true){ApTilrcLRh = false;}
      if(iDkJJFdmUj == true){iDkJJFdmUj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUUNJQXUGD
{ 
  void uVDItgbPjF()
  { 
      bool GxnGmrTfWX = false;
      bool gFhodQEXoR = false;
      bool QylZMFxuYD = false;
      bool SehzqDcRFq = false;
      bool IymlTOVuQX = false;
      bool WHLBpHLNth = false;
      bool tYHTFBXiyZ = false;
      bool nmRyISLAGy = false;
      bool jCdAfKSfIi = false;
      bool rOXXwjqSfR = false;
      bool plwqjjoNrX = false;
      bool wKHuxruGmt = false;
      bool hqaPhYPtBY = false;
      bool arTnHxGmQw = false;
      bool VFmjlgHbZE = false;
      bool ojflizLgJL = false;
      bool UuMTwDqSnA = false;
      bool kIppXcDpcA = false;
      bool QmTwiqMhEI = false;
      bool kYcFbasTnh = false;
      string QlyGuIsECW;
      string LIDQEOQOiw;
      string AxQVelQSph;
      string rHmpmGyfFr;
      string GnxQWrlawp;
      string yyAasSVbbJ;
      string raOTdDUNcx;
      string QjIqpLAzzl;
      string ApVzjtHMwU;
      string kVEwzeYcmS;
      string WYxzZNoJjg;
      string RVcoICEPjj;
      string wIQIMtfMqK;
      string lWMfObrWZW;
      string ExbOCOsOnx;
      string aJsCWOHnle;
      string hcRZuuIwag;
      string JhoNeygBGx;
      string BQXsjcdKJA;
      string TDjtnbfBTH;
      if(QlyGuIsECW == WYxzZNoJjg){GxnGmrTfWX = true;}
      else if(WYxzZNoJjg == QlyGuIsECW){plwqjjoNrX = true;}
      if(LIDQEOQOiw == RVcoICEPjj){gFhodQEXoR = true;}
      else if(RVcoICEPjj == LIDQEOQOiw){wKHuxruGmt = true;}
      if(AxQVelQSph == wIQIMtfMqK){QylZMFxuYD = true;}
      else if(wIQIMtfMqK == AxQVelQSph){hqaPhYPtBY = true;}
      if(rHmpmGyfFr == lWMfObrWZW){SehzqDcRFq = true;}
      else if(lWMfObrWZW == rHmpmGyfFr){arTnHxGmQw = true;}
      if(GnxQWrlawp == ExbOCOsOnx){IymlTOVuQX = true;}
      else if(ExbOCOsOnx == GnxQWrlawp){VFmjlgHbZE = true;}
      if(yyAasSVbbJ == aJsCWOHnle){WHLBpHLNth = true;}
      else if(aJsCWOHnle == yyAasSVbbJ){ojflizLgJL = true;}
      if(raOTdDUNcx == hcRZuuIwag){tYHTFBXiyZ = true;}
      else if(hcRZuuIwag == raOTdDUNcx){UuMTwDqSnA = true;}
      if(QjIqpLAzzl == JhoNeygBGx){nmRyISLAGy = true;}
      if(ApVzjtHMwU == BQXsjcdKJA){jCdAfKSfIi = true;}
      if(kVEwzeYcmS == TDjtnbfBTH){rOXXwjqSfR = true;}
      while(JhoNeygBGx == QjIqpLAzzl){kIppXcDpcA = true;}
      while(BQXsjcdKJA == BQXsjcdKJA){QmTwiqMhEI = true;}
      while(TDjtnbfBTH == TDjtnbfBTH){kYcFbasTnh = true;}
      if(GxnGmrTfWX == true){GxnGmrTfWX = false;}
      if(gFhodQEXoR == true){gFhodQEXoR = false;}
      if(QylZMFxuYD == true){QylZMFxuYD = false;}
      if(SehzqDcRFq == true){SehzqDcRFq = false;}
      if(IymlTOVuQX == true){IymlTOVuQX = false;}
      if(WHLBpHLNth == true){WHLBpHLNth = false;}
      if(tYHTFBXiyZ == true){tYHTFBXiyZ = false;}
      if(nmRyISLAGy == true){nmRyISLAGy = false;}
      if(jCdAfKSfIi == true){jCdAfKSfIi = false;}
      if(rOXXwjqSfR == true){rOXXwjqSfR = false;}
      if(plwqjjoNrX == true){plwqjjoNrX = false;}
      if(wKHuxruGmt == true){wKHuxruGmt = false;}
      if(hqaPhYPtBY == true){hqaPhYPtBY = false;}
      if(arTnHxGmQw == true){arTnHxGmQw = false;}
      if(VFmjlgHbZE == true){VFmjlgHbZE = false;}
      if(ojflizLgJL == true){ojflizLgJL = false;}
      if(UuMTwDqSnA == true){UuMTwDqSnA = false;}
      if(kIppXcDpcA == true){kIppXcDpcA = false;}
      if(QmTwiqMhEI == true){QmTwiqMhEI = false;}
      if(kYcFbasTnh == true){kYcFbasTnh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SXKZBDJLTE
{ 
  void GHinbZMhOe()
  { 
      bool JNXUiisNeO = false;
      bool zNXHijRMJs = false;
      bool sjCkXriXLW = false;
      bool hxutQwDFAX = false;
      bool UHgeOhJCbm = false;
      bool rbsIwYKmwp = false;
      bool AUBHgCScql = false;
      bool fMMkXkDXWo = false;
      bool ifuYeFDmxq = false;
      bool lQIJWAGZyL = false;
      bool PfLpGePIjL = false;
      bool VmPHGUZcba = false;
      bool zffzAPDCNX = false;
      bool edYKZCUFRA = false;
      bool puDlVzABDC = false;
      bool adyXMiAMoq = false;
      bool bMtLfrOFgD = false;
      bool zTKbkEcscB = false;
      bool OBzLxAeBxp = false;
      bool CIPaXcAqFd = false;
      string RAAoIGQrup;
      string HGbVVuPxmA;
      string bFLzrGGZmk;
      string waRNxPngRX;
      string DUYpZJgVTU;
      string rlCxEMoBwB;
      string zpFKtfoOYG;
      string HiePwGfUYi;
      string ZkFRrJYUIj;
      string ZljQXMPOws;
      string URwNNJHmAy;
      string fUbNbOkmRj;
      string HUGnfUyOqi;
      string pRXeNHorEi;
      string CkTJEFKWnI;
      string bbwMkAKHhs;
      string LruQHOwwzT;
      string ZriigWAxjZ;
      string JaZiHOULtN;
      string wgJLWKoDBp;
      if(RAAoIGQrup == URwNNJHmAy){JNXUiisNeO = true;}
      else if(URwNNJHmAy == RAAoIGQrup){PfLpGePIjL = true;}
      if(HGbVVuPxmA == fUbNbOkmRj){zNXHijRMJs = true;}
      else if(fUbNbOkmRj == HGbVVuPxmA){VmPHGUZcba = true;}
      if(bFLzrGGZmk == HUGnfUyOqi){sjCkXriXLW = true;}
      else if(HUGnfUyOqi == bFLzrGGZmk){zffzAPDCNX = true;}
      if(waRNxPngRX == pRXeNHorEi){hxutQwDFAX = true;}
      else if(pRXeNHorEi == waRNxPngRX){edYKZCUFRA = true;}
      if(DUYpZJgVTU == CkTJEFKWnI){UHgeOhJCbm = true;}
      else if(CkTJEFKWnI == DUYpZJgVTU){puDlVzABDC = true;}
      if(rlCxEMoBwB == bbwMkAKHhs){rbsIwYKmwp = true;}
      else if(bbwMkAKHhs == rlCxEMoBwB){adyXMiAMoq = true;}
      if(zpFKtfoOYG == LruQHOwwzT){AUBHgCScql = true;}
      else if(LruQHOwwzT == zpFKtfoOYG){bMtLfrOFgD = true;}
      if(HiePwGfUYi == ZriigWAxjZ){fMMkXkDXWo = true;}
      if(ZkFRrJYUIj == JaZiHOULtN){ifuYeFDmxq = true;}
      if(ZljQXMPOws == wgJLWKoDBp){lQIJWAGZyL = true;}
      while(ZriigWAxjZ == HiePwGfUYi){zTKbkEcscB = true;}
      while(JaZiHOULtN == JaZiHOULtN){OBzLxAeBxp = true;}
      while(wgJLWKoDBp == wgJLWKoDBp){CIPaXcAqFd = true;}
      if(JNXUiisNeO == true){JNXUiisNeO = false;}
      if(zNXHijRMJs == true){zNXHijRMJs = false;}
      if(sjCkXriXLW == true){sjCkXriXLW = false;}
      if(hxutQwDFAX == true){hxutQwDFAX = false;}
      if(UHgeOhJCbm == true){UHgeOhJCbm = false;}
      if(rbsIwYKmwp == true){rbsIwYKmwp = false;}
      if(AUBHgCScql == true){AUBHgCScql = false;}
      if(fMMkXkDXWo == true){fMMkXkDXWo = false;}
      if(ifuYeFDmxq == true){ifuYeFDmxq = false;}
      if(lQIJWAGZyL == true){lQIJWAGZyL = false;}
      if(PfLpGePIjL == true){PfLpGePIjL = false;}
      if(VmPHGUZcba == true){VmPHGUZcba = false;}
      if(zffzAPDCNX == true){zffzAPDCNX = false;}
      if(edYKZCUFRA == true){edYKZCUFRA = false;}
      if(puDlVzABDC == true){puDlVzABDC = false;}
      if(adyXMiAMoq == true){adyXMiAMoq = false;}
      if(bMtLfrOFgD == true){bMtLfrOFgD = false;}
      if(zTKbkEcscB == true){zTKbkEcscB = false;}
      if(OBzLxAeBxp == true){OBzLxAeBxp = false;}
      if(CIPaXcAqFd == true){CIPaXcAqFd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YNAEHGYGMU
{ 
  void oYByDhdmXM()
  { 
      bool sBkEOjNJMl = false;
      bool ahjWEpjgDg = false;
      bool jkmsGnuUUM = false;
      bool zHUMGKbNTq = false;
      bool cXssSZrPKI = false;
      bool WQaPYHNrxa = false;
      bool oroAmTNXPt = false;
      bool OWMMEMrtZg = false;
      bool ueKMohfFmz = false;
      bool wjPsCjisFz = false;
      bool MUzQtzEOLM = false;
      bool PTRQeJhbKE = false;
      bool mIkQxdHTKT = false;
      bool cznaTafsRp = false;
      bool dQsZicRyNr = false;
      bool BGhBLDjiSP = false;
      bool qjEqiQepwE = false;
      bool doJUaWOKhU = false;
      bool MJGRSWQmPQ = false;
      bool qwZCysMCqR = false;
      string PGzWPlzPDt;
      string QmLywkqpRa;
      string PZfFHwwkSo;
      string SPJturyjLW;
      string XLNjuoCIPl;
      string xTYaOoasOS;
      string oNxNaBdQDE;
      string lHeuDDLuKS;
      string tnVfrypheF;
      string QEUrgKOzIt;
      string KkEKzpocXL;
      string deiwXBrQVc;
      string KwkxmhllOs;
      string nLmPIIjKgC;
      string JMJTblVYTf;
      string RydfjNAGXR;
      string DCOeWRrTmP;
      string QhjTSxlRVA;
      string MNRhaphGft;
      string IclPyGyewJ;
      if(PGzWPlzPDt == KkEKzpocXL){sBkEOjNJMl = true;}
      else if(KkEKzpocXL == PGzWPlzPDt){MUzQtzEOLM = true;}
      if(QmLywkqpRa == deiwXBrQVc){ahjWEpjgDg = true;}
      else if(deiwXBrQVc == QmLywkqpRa){PTRQeJhbKE = true;}
      if(PZfFHwwkSo == KwkxmhllOs){jkmsGnuUUM = true;}
      else if(KwkxmhllOs == PZfFHwwkSo){mIkQxdHTKT = true;}
      if(SPJturyjLW == nLmPIIjKgC){zHUMGKbNTq = true;}
      else if(nLmPIIjKgC == SPJturyjLW){cznaTafsRp = true;}
      if(XLNjuoCIPl == JMJTblVYTf){cXssSZrPKI = true;}
      else if(JMJTblVYTf == XLNjuoCIPl){dQsZicRyNr = true;}
      if(xTYaOoasOS == RydfjNAGXR){WQaPYHNrxa = true;}
      else if(RydfjNAGXR == xTYaOoasOS){BGhBLDjiSP = true;}
      if(oNxNaBdQDE == DCOeWRrTmP){oroAmTNXPt = true;}
      else if(DCOeWRrTmP == oNxNaBdQDE){qjEqiQepwE = true;}
      if(lHeuDDLuKS == QhjTSxlRVA){OWMMEMrtZg = true;}
      if(tnVfrypheF == MNRhaphGft){ueKMohfFmz = true;}
      if(QEUrgKOzIt == IclPyGyewJ){wjPsCjisFz = true;}
      while(QhjTSxlRVA == lHeuDDLuKS){doJUaWOKhU = true;}
      while(MNRhaphGft == MNRhaphGft){MJGRSWQmPQ = true;}
      while(IclPyGyewJ == IclPyGyewJ){qwZCysMCqR = true;}
      if(sBkEOjNJMl == true){sBkEOjNJMl = false;}
      if(ahjWEpjgDg == true){ahjWEpjgDg = false;}
      if(jkmsGnuUUM == true){jkmsGnuUUM = false;}
      if(zHUMGKbNTq == true){zHUMGKbNTq = false;}
      if(cXssSZrPKI == true){cXssSZrPKI = false;}
      if(WQaPYHNrxa == true){WQaPYHNrxa = false;}
      if(oroAmTNXPt == true){oroAmTNXPt = false;}
      if(OWMMEMrtZg == true){OWMMEMrtZg = false;}
      if(ueKMohfFmz == true){ueKMohfFmz = false;}
      if(wjPsCjisFz == true){wjPsCjisFz = false;}
      if(MUzQtzEOLM == true){MUzQtzEOLM = false;}
      if(PTRQeJhbKE == true){PTRQeJhbKE = false;}
      if(mIkQxdHTKT == true){mIkQxdHTKT = false;}
      if(cznaTafsRp == true){cznaTafsRp = false;}
      if(dQsZicRyNr == true){dQsZicRyNr = false;}
      if(BGhBLDjiSP == true){BGhBLDjiSP = false;}
      if(qjEqiQepwE == true){qjEqiQepwE = false;}
      if(doJUaWOKhU == true){doJUaWOKhU = false;}
      if(MJGRSWQmPQ == true){MJGRSWQmPQ = false;}
      if(qwZCysMCqR == true){qwZCysMCqR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MGRGHZBULP
{ 
  void lgMJIxPYXE()
  { 
      bool nUpKVjZSdZ = false;
      bool zxOhhhYxGW = false;
      bool tJqLSLorDh = false;
      bool NAQripIMmD = false;
      bool wJprxJMFfM = false;
      bool EVTatdddrK = false;
      bool tgOwMyfVyr = false;
      bool ZLJCZjTzNJ = false;
      bool yiMpcrgpxE = false;
      bool MdUcIOusey = false;
      bool cqGmmsLQAJ = false;
      bool JdPiLLUXTT = false;
      bool RpYtfwqftL = false;
      bool naTPfHbYDi = false;
      bool fPpmthNlQx = false;
      bool tXYKglSMHq = false;
      bool CeWoUiJACE = false;
      bool iuTknBzkzx = false;
      bool hEPxQQBIht = false;
      bool oPRMgAsASK = false;
      string SKOtftjmwl;
      string HwjDhgisbV;
      string HOgwUBXdeO;
      string UFnohkdFIp;
      string nFatMcOKql;
      string HoJazEcRYe;
      string WGIhRBHuVx;
      string CckkhBmmjr;
      string lMlrGewNoc;
      string HMfcTgxscL;
      string USotjdEXsx;
      string QohgsKUPal;
      string EtGsopxHRA;
      string EtKXXTXrIb;
      string aYTqLSezjI;
      string MgRpGZMuEs;
      string gwFssWeJIY;
      string mcHzLfaOgW;
      string KyXImWbURx;
      string GbmOudSZxo;
      if(SKOtftjmwl == USotjdEXsx){nUpKVjZSdZ = true;}
      else if(USotjdEXsx == SKOtftjmwl){cqGmmsLQAJ = true;}
      if(HwjDhgisbV == QohgsKUPal){zxOhhhYxGW = true;}
      else if(QohgsKUPal == HwjDhgisbV){JdPiLLUXTT = true;}
      if(HOgwUBXdeO == EtGsopxHRA){tJqLSLorDh = true;}
      else if(EtGsopxHRA == HOgwUBXdeO){RpYtfwqftL = true;}
      if(UFnohkdFIp == EtKXXTXrIb){NAQripIMmD = true;}
      else if(EtKXXTXrIb == UFnohkdFIp){naTPfHbYDi = true;}
      if(nFatMcOKql == aYTqLSezjI){wJprxJMFfM = true;}
      else if(aYTqLSezjI == nFatMcOKql){fPpmthNlQx = true;}
      if(HoJazEcRYe == MgRpGZMuEs){EVTatdddrK = true;}
      else if(MgRpGZMuEs == HoJazEcRYe){tXYKglSMHq = true;}
      if(WGIhRBHuVx == gwFssWeJIY){tgOwMyfVyr = true;}
      else if(gwFssWeJIY == WGIhRBHuVx){CeWoUiJACE = true;}
      if(CckkhBmmjr == mcHzLfaOgW){ZLJCZjTzNJ = true;}
      if(lMlrGewNoc == KyXImWbURx){yiMpcrgpxE = true;}
      if(HMfcTgxscL == GbmOudSZxo){MdUcIOusey = true;}
      while(mcHzLfaOgW == CckkhBmmjr){iuTknBzkzx = true;}
      while(KyXImWbURx == KyXImWbURx){hEPxQQBIht = true;}
      while(GbmOudSZxo == GbmOudSZxo){oPRMgAsASK = true;}
      if(nUpKVjZSdZ == true){nUpKVjZSdZ = false;}
      if(zxOhhhYxGW == true){zxOhhhYxGW = false;}
      if(tJqLSLorDh == true){tJqLSLorDh = false;}
      if(NAQripIMmD == true){NAQripIMmD = false;}
      if(wJprxJMFfM == true){wJprxJMFfM = false;}
      if(EVTatdddrK == true){EVTatdddrK = false;}
      if(tgOwMyfVyr == true){tgOwMyfVyr = false;}
      if(ZLJCZjTzNJ == true){ZLJCZjTzNJ = false;}
      if(yiMpcrgpxE == true){yiMpcrgpxE = false;}
      if(MdUcIOusey == true){MdUcIOusey = false;}
      if(cqGmmsLQAJ == true){cqGmmsLQAJ = false;}
      if(JdPiLLUXTT == true){JdPiLLUXTT = false;}
      if(RpYtfwqftL == true){RpYtfwqftL = false;}
      if(naTPfHbYDi == true){naTPfHbYDi = false;}
      if(fPpmthNlQx == true){fPpmthNlQx = false;}
      if(tXYKglSMHq == true){tXYKglSMHq = false;}
      if(CeWoUiJACE == true){CeWoUiJACE = false;}
      if(iuTknBzkzx == true){iuTknBzkzx = false;}
      if(hEPxQQBIht == true){hEPxQQBIht = false;}
      if(oPRMgAsASK == true){oPRMgAsASK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ILTRTYTOZX
{ 
  void KnxKoJdLqi()
  { 
      bool MrpDJFwrVB = false;
      bool YnOEdXXMPL = false;
      bool dHTBlTTiwt = false;
      bool CbgQwHxfhK = false;
      bool GosTOnJgyt = false;
      bool QPCCPEXoRo = false;
      bool lNwazxGyHW = false;
      bool ZqdEEoNzlx = false;
      bool KlkCdmYdAr = false;
      bool iINsYssRUR = false;
      bool hLZaTYkyya = false;
      bool pXCUezctxL = false;
      bool YbyOmRdkfL = false;
      bool uweUOyMJhF = false;
      bool CafYBKFsOZ = false;
      bool QzUIsGNKmB = false;
      bool tARletshFf = false;
      bool mSLrJyuYNc = false;
      bool MkVGuwaWbI = false;
      bool kBVfKBIssG = false;
      string OFEqHqhUmk;
      string EHuNfNojSR;
      string xfOVcKIZjm;
      string EQIQoPHrpd;
      string YKwNdKnQVR;
      string dClBMiqiOx;
      string iIjzfnzdYQ;
      string GxtnrliBqR;
      string WqDRJCdGEG;
      string YYcrtQawhp;
      string LJrELfHyIa;
      string zpqwarERpc;
      string JrZRrgUBtb;
      string LmTBGMzyGc;
      string tfydGihfRC;
      string LIFEfSjZMd;
      string LGDfOLWooN;
      string sFLNhdtwLI;
      string zniqQDgOVn;
      string bYkcRnbROt;
      if(OFEqHqhUmk == LJrELfHyIa){MrpDJFwrVB = true;}
      else if(LJrELfHyIa == OFEqHqhUmk){hLZaTYkyya = true;}
      if(EHuNfNojSR == zpqwarERpc){YnOEdXXMPL = true;}
      else if(zpqwarERpc == EHuNfNojSR){pXCUezctxL = true;}
      if(xfOVcKIZjm == JrZRrgUBtb){dHTBlTTiwt = true;}
      else if(JrZRrgUBtb == xfOVcKIZjm){YbyOmRdkfL = true;}
      if(EQIQoPHrpd == LmTBGMzyGc){CbgQwHxfhK = true;}
      else if(LmTBGMzyGc == EQIQoPHrpd){uweUOyMJhF = true;}
      if(YKwNdKnQVR == tfydGihfRC){GosTOnJgyt = true;}
      else if(tfydGihfRC == YKwNdKnQVR){CafYBKFsOZ = true;}
      if(dClBMiqiOx == LIFEfSjZMd){QPCCPEXoRo = true;}
      else if(LIFEfSjZMd == dClBMiqiOx){QzUIsGNKmB = true;}
      if(iIjzfnzdYQ == LGDfOLWooN){lNwazxGyHW = true;}
      else if(LGDfOLWooN == iIjzfnzdYQ){tARletshFf = true;}
      if(GxtnrliBqR == sFLNhdtwLI){ZqdEEoNzlx = true;}
      if(WqDRJCdGEG == zniqQDgOVn){KlkCdmYdAr = true;}
      if(YYcrtQawhp == bYkcRnbROt){iINsYssRUR = true;}
      while(sFLNhdtwLI == GxtnrliBqR){mSLrJyuYNc = true;}
      while(zniqQDgOVn == zniqQDgOVn){MkVGuwaWbI = true;}
      while(bYkcRnbROt == bYkcRnbROt){kBVfKBIssG = true;}
      if(MrpDJFwrVB == true){MrpDJFwrVB = false;}
      if(YnOEdXXMPL == true){YnOEdXXMPL = false;}
      if(dHTBlTTiwt == true){dHTBlTTiwt = false;}
      if(CbgQwHxfhK == true){CbgQwHxfhK = false;}
      if(GosTOnJgyt == true){GosTOnJgyt = false;}
      if(QPCCPEXoRo == true){QPCCPEXoRo = false;}
      if(lNwazxGyHW == true){lNwazxGyHW = false;}
      if(ZqdEEoNzlx == true){ZqdEEoNzlx = false;}
      if(KlkCdmYdAr == true){KlkCdmYdAr = false;}
      if(iINsYssRUR == true){iINsYssRUR = false;}
      if(hLZaTYkyya == true){hLZaTYkyya = false;}
      if(pXCUezctxL == true){pXCUezctxL = false;}
      if(YbyOmRdkfL == true){YbyOmRdkfL = false;}
      if(uweUOyMJhF == true){uweUOyMJhF = false;}
      if(CafYBKFsOZ == true){CafYBKFsOZ = false;}
      if(QzUIsGNKmB == true){QzUIsGNKmB = false;}
      if(tARletshFf == true){tARletshFf = false;}
      if(mSLrJyuYNc == true){mSLrJyuYNc = false;}
      if(MkVGuwaWbI == true){MkVGuwaWbI = false;}
      if(kBVfKBIssG == true){kBVfKBIssG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZBKZOJVAGN
{ 
  void wmnUzWZRZV()
  { 
      bool isRyiuzHkk = false;
      bool RARNQYgDKi = false;
      bool ZWnKOqcQny = false;
      bool rNqTjxCmys = false;
      bool LonxPFzfPt = false;
      bool PWHtpMFHiq = false;
      bool RiTmsEIycT = false;
      bool WsFQXkhptJ = false;
      bool rwBshUFwdX = false;
      bool rtEGbbVBEK = false;
      bool wBDuWWQqWF = false;
      bool dPMYzVgZFX = false;
      bool zMTEbcozou = false;
      bool OgkjNqsFVK = false;
      bool EOZYtcgeHF = false;
      bool uuugLigyTt = false;
      bool gRBapwdcKI = false;
      bool cbDtTjmtKz = false;
      bool uJriATlDXe = false;
      bool JtkbdlMzix = false;
      string EqgxPjhkVg;
      string heymVeqVqw;
      string UcoExdLZuS;
      string gfGaulBfBt;
      string XajqjVmRRr;
      string irIfyaCczl;
      string XHpCzCYWrj;
      string dLTwXtryTb;
      string ptICjnXZcU;
      string jXgOWQkgqh;
      string wPZgNXXLHD;
      string hDIWudymSK;
      string eytWAGdFZH;
      string JKGleaTaoM;
      string PLSYmfPJSr;
      string SyOfDyVCgH;
      string sSkztWxWqU;
      string JWyGuSfUjT;
      string pTlgoKwZig;
      string FRtgSxaSdP;
      if(EqgxPjhkVg == wPZgNXXLHD){isRyiuzHkk = true;}
      else if(wPZgNXXLHD == EqgxPjhkVg){wBDuWWQqWF = true;}
      if(heymVeqVqw == hDIWudymSK){RARNQYgDKi = true;}
      else if(hDIWudymSK == heymVeqVqw){dPMYzVgZFX = true;}
      if(UcoExdLZuS == eytWAGdFZH){ZWnKOqcQny = true;}
      else if(eytWAGdFZH == UcoExdLZuS){zMTEbcozou = true;}
      if(gfGaulBfBt == JKGleaTaoM){rNqTjxCmys = true;}
      else if(JKGleaTaoM == gfGaulBfBt){OgkjNqsFVK = true;}
      if(XajqjVmRRr == PLSYmfPJSr){LonxPFzfPt = true;}
      else if(PLSYmfPJSr == XajqjVmRRr){EOZYtcgeHF = true;}
      if(irIfyaCczl == SyOfDyVCgH){PWHtpMFHiq = true;}
      else if(SyOfDyVCgH == irIfyaCczl){uuugLigyTt = true;}
      if(XHpCzCYWrj == sSkztWxWqU){RiTmsEIycT = true;}
      else if(sSkztWxWqU == XHpCzCYWrj){gRBapwdcKI = true;}
      if(dLTwXtryTb == JWyGuSfUjT){WsFQXkhptJ = true;}
      if(ptICjnXZcU == pTlgoKwZig){rwBshUFwdX = true;}
      if(jXgOWQkgqh == FRtgSxaSdP){rtEGbbVBEK = true;}
      while(JWyGuSfUjT == dLTwXtryTb){cbDtTjmtKz = true;}
      while(pTlgoKwZig == pTlgoKwZig){uJriATlDXe = true;}
      while(FRtgSxaSdP == FRtgSxaSdP){JtkbdlMzix = true;}
      if(isRyiuzHkk == true){isRyiuzHkk = false;}
      if(RARNQYgDKi == true){RARNQYgDKi = false;}
      if(ZWnKOqcQny == true){ZWnKOqcQny = false;}
      if(rNqTjxCmys == true){rNqTjxCmys = false;}
      if(LonxPFzfPt == true){LonxPFzfPt = false;}
      if(PWHtpMFHiq == true){PWHtpMFHiq = false;}
      if(RiTmsEIycT == true){RiTmsEIycT = false;}
      if(WsFQXkhptJ == true){WsFQXkhptJ = false;}
      if(rwBshUFwdX == true){rwBshUFwdX = false;}
      if(rtEGbbVBEK == true){rtEGbbVBEK = false;}
      if(wBDuWWQqWF == true){wBDuWWQqWF = false;}
      if(dPMYzVgZFX == true){dPMYzVgZFX = false;}
      if(zMTEbcozou == true){zMTEbcozou = false;}
      if(OgkjNqsFVK == true){OgkjNqsFVK = false;}
      if(EOZYtcgeHF == true){EOZYtcgeHF = false;}
      if(uuugLigyTt == true){uuugLigyTt = false;}
      if(gRBapwdcKI == true){gRBapwdcKI = false;}
      if(cbDtTjmtKz == true){cbDtTjmtKz = false;}
      if(uJriATlDXe == true){uJriATlDXe = false;}
      if(JtkbdlMzix == true){JtkbdlMzix = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IEALDLEASM
{ 
  void yiAjreDLrN()
  { 
      bool IECkeWxYVY = false;
      bool gGXzbZLyyi = false;
      bool PFNaGdgNxZ = false;
      bool kjOMfmbfLN = false;
      bool hwsGQNWLuz = false;
      bool DaXVpDqaeA = false;
      bool pjbumxqKSn = false;
      bool xflkBTLHJs = false;
      bool HURyWKMsWc = false;
      bool wABKWxUyST = false;
      bool VLsHBXnmUV = false;
      bool qjQkrVSdYb = false;
      bool jxnorwdaOD = false;
      bool zMnpWwbJwy = false;
      bool WYYAlMjPRB = false;
      bool epZpiXWDOE = false;
      bool sMYQWduaNw = false;
      bool sIgZFLYnDe = false;
      bool MOIMXImxGz = false;
      bool ZXuqFJAHdH = false;
      string ICbdiltscq;
      string NXhRbcdTND;
      string VrnzgFrzKq;
      string MpZzLlgjJG;
      string zufVdxxHuG;
      string EPrlDPNbwc;
      string sthkdWyiGp;
      string utJHEaLSUj;
      string IkEElxymuu;
      string XEngMEMtrH;
      string yNBFLJFjhb;
      string DuGLUIpdzg;
      string XKmKRpGcuz;
      string NRaNltjyrc;
      string qNETrcybLD;
      string OiuKimZpnU;
      string DcoiOlUsZa;
      string YqkVoKGTSo;
      string rdQqjeVPey;
      string TtKXYOYVEG;
      if(ICbdiltscq == yNBFLJFjhb){IECkeWxYVY = true;}
      else if(yNBFLJFjhb == ICbdiltscq){VLsHBXnmUV = true;}
      if(NXhRbcdTND == DuGLUIpdzg){gGXzbZLyyi = true;}
      else if(DuGLUIpdzg == NXhRbcdTND){qjQkrVSdYb = true;}
      if(VrnzgFrzKq == XKmKRpGcuz){PFNaGdgNxZ = true;}
      else if(XKmKRpGcuz == VrnzgFrzKq){jxnorwdaOD = true;}
      if(MpZzLlgjJG == NRaNltjyrc){kjOMfmbfLN = true;}
      else if(NRaNltjyrc == MpZzLlgjJG){zMnpWwbJwy = true;}
      if(zufVdxxHuG == qNETrcybLD){hwsGQNWLuz = true;}
      else if(qNETrcybLD == zufVdxxHuG){WYYAlMjPRB = true;}
      if(EPrlDPNbwc == OiuKimZpnU){DaXVpDqaeA = true;}
      else if(OiuKimZpnU == EPrlDPNbwc){epZpiXWDOE = true;}
      if(sthkdWyiGp == DcoiOlUsZa){pjbumxqKSn = true;}
      else if(DcoiOlUsZa == sthkdWyiGp){sMYQWduaNw = true;}
      if(utJHEaLSUj == YqkVoKGTSo){xflkBTLHJs = true;}
      if(IkEElxymuu == rdQqjeVPey){HURyWKMsWc = true;}
      if(XEngMEMtrH == TtKXYOYVEG){wABKWxUyST = true;}
      while(YqkVoKGTSo == utJHEaLSUj){sIgZFLYnDe = true;}
      while(rdQqjeVPey == rdQqjeVPey){MOIMXImxGz = true;}
      while(TtKXYOYVEG == TtKXYOYVEG){ZXuqFJAHdH = true;}
      if(IECkeWxYVY == true){IECkeWxYVY = false;}
      if(gGXzbZLyyi == true){gGXzbZLyyi = false;}
      if(PFNaGdgNxZ == true){PFNaGdgNxZ = false;}
      if(kjOMfmbfLN == true){kjOMfmbfLN = false;}
      if(hwsGQNWLuz == true){hwsGQNWLuz = false;}
      if(DaXVpDqaeA == true){DaXVpDqaeA = false;}
      if(pjbumxqKSn == true){pjbumxqKSn = false;}
      if(xflkBTLHJs == true){xflkBTLHJs = false;}
      if(HURyWKMsWc == true){HURyWKMsWc = false;}
      if(wABKWxUyST == true){wABKWxUyST = false;}
      if(VLsHBXnmUV == true){VLsHBXnmUV = false;}
      if(qjQkrVSdYb == true){qjQkrVSdYb = false;}
      if(jxnorwdaOD == true){jxnorwdaOD = false;}
      if(zMnpWwbJwy == true){zMnpWwbJwy = false;}
      if(WYYAlMjPRB == true){WYYAlMjPRB = false;}
      if(epZpiXWDOE == true){epZpiXWDOE = false;}
      if(sMYQWduaNw == true){sMYQWduaNw = false;}
      if(sIgZFLYnDe == true){sIgZFLYnDe = false;}
      if(MOIMXImxGz == true){MOIMXImxGz = false;}
      if(ZXuqFJAHdH == true){ZXuqFJAHdH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FVEETFIXAB
{ 
  void WgMAFwfeZS()
  { 
      bool mPmNSmQZuc = false;
      bool IXpUbRBURN = false;
      bool toMmXjPFfj = false;
      bool dDUlZPWSjI = false;
      bool AwXhLDiyVw = false;
      bool hPDYLxCAoi = false;
      bool WLtKyEDEuL = false;
      bool tijJNxRdaU = false;
      bool BQjjBOAwZb = false;
      bool MWcBknCMjH = false;
      bool AeDJCzetKO = false;
      bool fXZUgFbJJj = false;
      bool EGdTzWFiXY = false;
      bool tEtTTWNZgB = false;
      bool jFkLunxITf = false;
      bool MsCACsAjKe = false;
      bool suWlTadFAK = false;
      bool rBcHzzVSXK = false;
      bool ZxPqLBCtRa = false;
      bool VcOBIoiyqU = false;
      string YxREnULWdO;
      string blRoNxVzmM;
      string XPUUBVAgmT;
      string hqRLqQNIlN;
      string mLQiBJKunJ;
      string undEcJcwCR;
      string UejKgkUGxw;
      string jMNYZMzkTr;
      string KEscYsNMhh;
      string mQGTsIaGCP;
      string oExqZhaEeQ;
      string KqcKGQkGkm;
      string XHYPJSGsfR;
      string krhECGGBDp;
      string SIhRXwnuNc;
      string WTUPrhehhG;
      string bhXMeRIYHz;
      string JjDtUOYHrM;
      string eKfDuQWSLU;
      string bYTxNjjUlG;
      if(YxREnULWdO == oExqZhaEeQ){mPmNSmQZuc = true;}
      else if(oExqZhaEeQ == YxREnULWdO){AeDJCzetKO = true;}
      if(blRoNxVzmM == KqcKGQkGkm){IXpUbRBURN = true;}
      else if(KqcKGQkGkm == blRoNxVzmM){fXZUgFbJJj = true;}
      if(XPUUBVAgmT == XHYPJSGsfR){toMmXjPFfj = true;}
      else if(XHYPJSGsfR == XPUUBVAgmT){EGdTzWFiXY = true;}
      if(hqRLqQNIlN == krhECGGBDp){dDUlZPWSjI = true;}
      else if(krhECGGBDp == hqRLqQNIlN){tEtTTWNZgB = true;}
      if(mLQiBJKunJ == SIhRXwnuNc){AwXhLDiyVw = true;}
      else if(SIhRXwnuNc == mLQiBJKunJ){jFkLunxITf = true;}
      if(undEcJcwCR == WTUPrhehhG){hPDYLxCAoi = true;}
      else if(WTUPrhehhG == undEcJcwCR){MsCACsAjKe = true;}
      if(UejKgkUGxw == bhXMeRIYHz){WLtKyEDEuL = true;}
      else if(bhXMeRIYHz == UejKgkUGxw){suWlTadFAK = true;}
      if(jMNYZMzkTr == JjDtUOYHrM){tijJNxRdaU = true;}
      if(KEscYsNMhh == eKfDuQWSLU){BQjjBOAwZb = true;}
      if(mQGTsIaGCP == bYTxNjjUlG){MWcBknCMjH = true;}
      while(JjDtUOYHrM == jMNYZMzkTr){rBcHzzVSXK = true;}
      while(eKfDuQWSLU == eKfDuQWSLU){ZxPqLBCtRa = true;}
      while(bYTxNjjUlG == bYTxNjjUlG){VcOBIoiyqU = true;}
      if(mPmNSmQZuc == true){mPmNSmQZuc = false;}
      if(IXpUbRBURN == true){IXpUbRBURN = false;}
      if(toMmXjPFfj == true){toMmXjPFfj = false;}
      if(dDUlZPWSjI == true){dDUlZPWSjI = false;}
      if(AwXhLDiyVw == true){AwXhLDiyVw = false;}
      if(hPDYLxCAoi == true){hPDYLxCAoi = false;}
      if(WLtKyEDEuL == true){WLtKyEDEuL = false;}
      if(tijJNxRdaU == true){tijJNxRdaU = false;}
      if(BQjjBOAwZb == true){BQjjBOAwZb = false;}
      if(MWcBknCMjH == true){MWcBknCMjH = false;}
      if(AeDJCzetKO == true){AeDJCzetKO = false;}
      if(fXZUgFbJJj == true){fXZUgFbJJj = false;}
      if(EGdTzWFiXY == true){EGdTzWFiXY = false;}
      if(tEtTTWNZgB == true){tEtTTWNZgB = false;}
      if(jFkLunxITf == true){jFkLunxITf = false;}
      if(MsCACsAjKe == true){MsCACsAjKe = false;}
      if(suWlTadFAK == true){suWlTadFAK = false;}
      if(rBcHzzVSXK == true){rBcHzzVSXK = false;}
      if(ZxPqLBCtRa == true){ZxPqLBCtRa = false;}
      if(VcOBIoiyqU == true){VcOBIoiyqU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AYLCLGOAWU
{ 
  void GPaBgzChar()
  { 
      bool KjVFaaGJnI = false;
      bool gtLGrXECjX = false;
      bool jIahQRHHdT = false;
      bool BsVNBGmdPJ = false;
      bool TtDqDDVoqy = false;
      bool gEnKXCImnI = false;
      bool SzfTGmXyEl = false;
      bool kalZDoFjeN = false;
      bool wRPelwEKpz = false;
      bool xzoGpUNijP = false;
      bool eXjENGSNHh = false;
      bool wXIaMAiBgK = false;
      bool iNHFnkkeji = false;
      bool aWAOiXhKQf = false;
      bool dpDHCYpOto = false;
      bool kMBZgQPdQb = false;
      bool VmcXGZXsqo = false;
      bool SXjBfrKADP = false;
      bool uVkuxOUahR = false;
      bool HDtoKpMeAb = false;
      string TCQbDOfAmD;
      string FttCWmVHkT;
      string pjyihKhMpA;
      string zkLCjBiiXZ;
      string MNDhtqcRJn;
      string RdXmyjDgsr;
      string gSJmDUhqSU;
      string EmjLGbfQoq;
      string hPCBhVMYEA;
      string xCpersEPdY;
      string IkzojdsMgV;
      string DmqBKQPHFh;
      string IJmRWBxESM;
      string XPmPiwPNRE;
      string bArhwKLnUb;
      string cwKuQyyhRh;
      string gosTynAaSO;
      string ACpAGIREVL;
      string pIjqjaEqzj;
      string xhuiWlGXiH;
      if(TCQbDOfAmD == IkzojdsMgV){KjVFaaGJnI = true;}
      else if(IkzojdsMgV == TCQbDOfAmD){eXjENGSNHh = true;}
      if(FttCWmVHkT == DmqBKQPHFh){gtLGrXECjX = true;}
      else if(DmqBKQPHFh == FttCWmVHkT){wXIaMAiBgK = true;}
      if(pjyihKhMpA == IJmRWBxESM){jIahQRHHdT = true;}
      else if(IJmRWBxESM == pjyihKhMpA){iNHFnkkeji = true;}
      if(zkLCjBiiXZ == XPmPiwPNRE){BsVNBGmdPJ = true;}
      else if(XPmPiwPNRE == zkLCjBiiXZ){aWAOiXhKQf = true;}
      if(MNDhtqcRJn == bArhwKLnUb){TtDqDDVoqy = true;}
      else if(bArhwKLnUb == MNDhtqcRJn){dpDHCYpOto = true;}
      if(RdXmyjDgsr == cwKuQyyhRh){gEnKXCImnI = true;}
      else if(cwKuQyyhRh == RdXmyjDgsr){kMBZgQPdQb = true;}
      if(gSJmDUhqSU == gosTynAaSO){SzfTGmXyEl = true;}
      else if(gosTynAaSO == gSJmDUhqSU){VmcXGZXsqo = true;}
      if(EmjLGbfQoq == ACpAGIREVL){kalZDoFjeN = true;}
      if(hPCBhVMYEA == pIjqjaEqzj){wRPelwEKpz = true;}
      if(xCpersEPdY == xhuiWlGXiH){xzoGpUNijP = true;}
      while(ACpAGIREVL == EmjLGbfQoq){SXjBfrKADP = true;}
      while(pIjqjaEqzj == pIjqjaEqzj){uVkuxOUahR = true;}
      while(xhuiWlGXiH == xhuiWlGXiH){HDtoKpMeAb = true;}
      if(KjVFaaGJnI == true){KjVFaaGJnI = false;}
      if(gtLGrXECjX == true){gtLGrXECjX = false;}
      if(jIahQRHHdT == true){jIahQRHHdT = false;}
      if(BsVNBGmdPJ == true){BsVNBGmdPJ = false;}
      if(TtDqDDVoqy == true){TtDqDDVoqy = false;}
      if(gEnKXCImnI == true){gEnKXCImnI = false;}
      if(SzfTGmXyEl == true){SzfTGmXyEl = false;}
      if(kalZDoFjeN == true){kalZDoFjeN = false;}
      if(wRPelwEKpz == true){wRPelwEKpz = false;}
      if(xzoGpUNijP == true){xzoGpUNijP = false;}
      if(eXjENGSNHh == true){eXjENGSNHh = false;}
      if(wXIaMAiBgK == true){wXIaMAiBgK = false;}
      if(iNHFnkkeji == true){iNHFnkkeji = false;}
      if(aWAOiXhKQf == true){aWAOiXhKQf = false;}
      if(dpDHCYpOto == true){dpDHCYpOto = false;}
      if(kMBZgQPdQb == true){kMBZgQPdQb = false;}
      if(VmcXGZXsqo == true){VmcXGZXsqo = false;}
      if(SXjBfrKADP == true){SXjBfrKADP = false;}
      if(uVkuxOUahR == true){uVkuxOUahR = false;}
      if(HDtoKpMeAb == true){HDtoKpMeAb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXOWYGYTPU
{ 
  void YomZzXxGDQ()
  { 
      bool CrwLMnhXqq = false;
      bool QMOWLwqNqO = false;
      bool uxBMRESBNz = false;
      bool NbqZtcrKbo = false;
      bool XcDVFrDQaL = false;
      bool qHUGWFqjtI = false;
      bool UgJrdnUnch = false;
      bool DglBpSteHY = false;
      bool BBZCHFGkCn = false;
      bool lIQTUqSKrQ = false;
      bool WOmrIJVSPE = false;
      bool LLbUGSGHkY = false;
      bool gjlowtQSgz = false;
      bool zimqCmNhtx = false;
      bool jnUycZguMB = false;
      bool kLZSimbyuN = false;
      bool sDlQEbYkST = false;
      bool EXNmnsOmLV = false;
      bool NUFeNnJTHO = false;
      bool KPlgEgBEsA = false;
      string eLuYqKYUeS;
      string mGmZzcBiTl;
      string agYRTgYlfO;
      string XdJsHxnstQ;
      string zTazsUXiPz;
      string OHdhEymcFK;
      string lmoQtIwsRC;
      string nHnClGFYYy;
      string IpVfAPAboI;
      string JLmjeMeKEj;
      string YdQNLGSaux;
      string sNDHBuQIPe;
      string IUEIscUEXZ;
      string buUoZeYIUt;
      string xYgqPwHehi;
      string wVtZaDZHTh;
      string lNCUVxsOhW;
      string VHnVhimNsx;
      string VoWodGBuNV;
      string ERnmHiVLVS;
      if(eLuYqKYUeS == YdQNLGSaux){CrwLMnhXqq = true;}
      else if(YdQNLGSaux == eLuYqKYUeS){WOmrIJVSPE = true;}
      if(mGmZzcBiTl == sNDHBuQIPe){QMOWLwqNqO = true;}
      else if(sNDHBuQIPe == mGmZzcBiTl){LLbUGSGHkY = true;}
      if(agYRTgYlfO == IUEIscUEXZ){uxBMRESBNz = true;}
      else if(IUEIscUEXZ == agYRTgYlfO){gjlowtQSgz = true;}
      if(XdJsHxnstQ == buUoZeYIUt){NbqZtcrKbo = true;}
      else if(buUoZeYIUt == XdJsHxnstQ){zimqCmNhtx = true;}
      if(zTazsUXiPz == xYgqPwHehi){XcDVFrDQaL = true;}
      else if(xYgqPwHehi == zTazsUXiPz){jnUycZguMB = true;}
      if(OHdhEymcFK == wVtZaDZHTh){qHUGWFqjtI = true;}
      else if(wVtZaDZHTh == OHdhEymcFK){kLZSimbyuN = true;}
      if(lmoQtIwsRC == lNCUVxsOhW){UgJrdnUnch = true;}
      else if(lNCUVxsOhW == lmoQtIwsRC){sDlQEbYkST = true;}
      if(nHnClGFYYy == VHnVhimNsx){DglBpSteHY = true;}
      if(IpVfAPAboI == VoWodGBuNV){BBZCHFGkCn = true;}
      if(JLmjeMeKEj == ERnmHiVLVS){lIQTUqSKrQ = true;}
      while(VHnVhimNsx == nHnClGFYYy){EXNmnsOmLV = true;}
      while(VoWodGBuNV == VoWodGBuNV){NUFeNnJTHO = true;}
      while(ERnmHiVLVS == ERnmHiVLVS){KPlgEgBEsA = true;}
      if(CrwLMnhXqq == true){CrwLMnhXqq = false;}
      if(QMOWLwqNqO == true){QMOWLwqNqO = false;}
      if(uxBMRESBNz == true){uxBMRESBNz = false;}
      if(NbqZtcrKbo == true){NbqZtcrKbo = false;}
      if(XcDVFrDQaL == true){XcDVFrDQaL = false;}
      if(qHUGWFqjtI == true){qHUGWFqjtI = false;}
      if(UgJrdnUnch == true){UgJrdnUnch = false;}
      if(DglBpSteHY == true){DglBpSteHY = false;}
      if(BBZCHFGkCn == true){BBZCHFGkCn = false;}
      if(lIQTUqSKrQ == true){lIQTUqSKrQ = false;}
      if(WOmrIJVSPE == true){WOmrIJVSPE = false;}
      if(LLbUGSGHkY == true){LLbUGSGHkY = false;}
      if(gjlowtQSgz == true){gjlowtQSgz = false;}
      if(zimqCmNhtx == true){zimqCmNhtx = false;}
      if(jnUycZguMB == true){jnUycZguMB = false;}
      if(kLZSimbyuN == true){kLZSimbyuN = false;}
      if(sDlQEbYkST == true){sDlQEbYkST = false;}
      if(EXNmnsOmLV == true){EXNmnsOmLV = false;}
      if(NUFeNnJTHO == true){NUFeNnJTHO = false;}
      if(KPlgEgBEsA == true){KPlgEgBEsA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BKIVNXFBTE
{ 
  void qyugtLBrPZ()
  { 
      bool ECKtgQkIIA = false;
      bool BeYQOLHSQp = false;
      bool AyYSdXwOoH = false;
      bool SKDuOkEWGW = false;
      bool lyQNBSutMB = false;
      bool EYkCaFcqQJ = false;
      bool TVTAgqbcBd = false;
      bool GkLtEChLRL = false;
      bool bBCmCtYAUJ = false;
      bool HMFxCPePfJ = false;
      bool qSshtTMqyX = false;
      bool WRZEgRTfym = false;
      bool RaIrVseNqo = false;
      bool XSeHUJITri = false;
      bool ghCxlpmAPj = false;
      bool uyRsrPJAMB = false;
      bool ozzJzEmSjX = false;
      bool IAmPFiYLFe = false;
      bool GdxHsYAkPE = false;
      bool zHGqshisxg = false;
      string HXnJKFipwV;
      string BMiLGiVryr;
      string JRQjWDfEPw;
      string UcXPxIFGfF;
      string FTAhrWyOcI;
      string lXLBApHDmH;
      string YdZABYoSNx;
      string dPMslpQhrz;
      string FQaHKwQVPH;
      string BBTYfasAgS;
      string heBfeVLSPJ;
      string YYLmCHDSpE;
      string ISCFubumML;
      string xQBYRZPucn;
      string jxGGibofWY;
      string XZKbKObujC;
      string aXGDMHXmVb;
      string rHoBTKMwWT;
      string mPQnmWGYNC;
      string yULaMMqCsa;
      if(HXnJKFipwV == heBfeVLSPJ){ECKtgQkIIA = true;}
      else if(heBfeVLSPJ == HXnJKFipwV){qSshtTMqyX = true;}
      if(BMiLGiVryr == YYLmCHDSpE){BeYQOLHSQp = true;}
      else if(YYLmCHDSpE == BMiLGiVryr){WRZEgRTfym = true;}
      if(JRQjWDfEPw == ISCFubumML){AyYSdXwOoH = true;}
      else if(ISCFubumML == JRQjWDfEPw){RaIrVseNqo = true;}
      if(UcXPxIFGfF == xQBYRZPucn){SKDuOkEWGW = true;}
      else if(xQBYRZPucn == UcXPxIFGfF){XSeHUJITri = true;}
      if(FTAhrWyOcI == jxGGibofWY){lyQNBSutMB = true;}
      else if(jxGGibofWY == FTAhrWyOcI){ghCxlpmAPj = true;}
      if(lXLBApHDmH == XZKbKObujC){EYkCaFcqQJ = true;}
      else if(XZKbKObujC == lXLBApHDmH){uyRsrPJAMB = true;}
      if(YdZABYoSNx == aXGDMHXmVb){TVTAgqbcBd = true;}
      else if(aXGDMHXmVb == YdZABYoSNx){ozzJzEmSjX = true;}
      if(dPMslpQhrz == rHoBTKMwWT){GkLtEChLRL = true;}
      if(FQaHKwQVPH == mPQnmWGYNC){bBCmCtYAUJ = true;}
      if(BBTYfasAgS == yULaMMqCsa){HMFxCPePfJ = true;}
      while(rHoBTKMwWT == dPMslpQhrz){IAmPFiYLFe = true;}
      while(mPQnmWGYNC == mPQnmWGYNC){GdxHsYAkPE = true;}
      while(yULaMMqCsa == yULaMMqCsa){zHGqshisxg = true;}
      if(ECKtgQkIIA == true){ECKtgQkIIA = false;}
      if(BeYQOLHSQp == true){BeYQOLHSQp = false;}
      if(AyYSdXwOoH == true){AyYSdXwOoH = false;}
      if(SKDuOkEWGW == true){SKDuOkEWGW = false;}
      if(lyQNBSutMB == true){lyQNBSutMB = false;}
      if(EYkCaFcqQJ == true){EYkCaFcqQJ = false;}
      if(TVTAgqbcBd == true){TVTAgqbcBd = false;}
      if(GkLtEChLRL == true){GkLtEChLRL = false;}
      if(bBCmCtYAUJ == true){bBCmCtYAUJ = false;}
      if(HMFxCPePfJ == true){HMFxCPePfJ = false;}
      if(qSshtTMqyX == true){qSshtTMqyX = false;}
      if(WRZEgRTfym == true){WRZEgRTfym = false;}
      if(RaIrVseNqo == true){RaIrVseNqo = false;}
      if(XSeHUJITri == true){XSeHUJITri = false;}
      if(ghCxlpmAPj == true){ghCxlpmAPj = false;}
      if(uyRsrPJAMB == true){uyRsrPJAMB = false;}
      if(ozzJzEmSjX == true){ozzJzEmSjX = false;}
      if(IAmPFiYLFe == true){IAmPFiYLFe = false;}
      if(GdxHsYAkPE == true){GdxHsYAkPE = false;}
      if(zHGqshisxg == true){zHGqshisxg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LWRNNPATIF
{ 
  void VVUWcXGlrY()
  { 
      bool YlCsSeOgQu = false;
      bool OdYDNIHSxn = false;
      bool kIHOsrHAgs = false;
      bool jIIAsGCfxL = false;
      bool iBOIlYYlrN = false;
      bool qIdGFQdmAa = false;
      bool XOzWLGUXJH = false;
      bool GbUkFjszcT = false;
      bool SUHTCadCuc = false;
      bool bOfWnTBqwe = false;
      bool EBcjGPmsAV = false;
      bool WdJfHCGfUj = false;
      bool bRcgequywk = false;
      bool hCDxPRqXMl = false;
      bool njBZFxEzPk = false;
      bool NUVMDlYuEP = false;
      bool ToxPmUaLQo = false;
      bool LiThwrQCah = false;
      bool luiKXNfptc = false;
      bool swSwSzmlmk = false;
      string qSJZImXsKJ;
      string IDNUXhrgqU;
      string aQNDPeAuPE;
      string GShuVyYpyC;
      string PSbmRSgRdF;
      string kdyMLZFGKd;
      string mbdFCpURyZ;
      string ICioFHnakw;
      string yhRKSbTVjw;
      string rSfTOmoWjb;
      string xOSExiuJGE;
      string keUNeFKTlZ;
      string VzhCgpVOZS;
      string SRpJyiONMi;
      string gKPeKNxRoJ;
      string bUjKGyfQWG;
      string MgimkTnLPw;
      string pxGDsKjCrS;
      string rEYQpxhfDA;
      string CypGVzabtq;
      if(qSJZImXsKJ == xOSExiuJGE){YlCsSeOgQu = true;}
      else if(xOSExiuJGE == qSJZImXsKJ){EBcjGPmsAV = true;}
      if(IDNUXhrgqU == keUNeFKTlZ){OdYDNIHSxn = true;}
      else if(keUNeFKTlZ == IDNUXhrgqU){WdJfHCGfUj = true;}
      if(aQNDPeAuPE == VzhCgpVOZS){kIHOsrHAgs = true;}
      else if(VzhCgpVOZS == aQNDPeAuPE){bRcgequywk = true;}
      if(GShuVyYpyC == SRpJyiONMi){jIIAsGCfxL = true;}
      else if(SRpJyiONMi == GShuVyYpyC){hCDxPRqXMl = true;}
      if(PSbmRSgRdF == gKPeKNxRoJ){iBOIlYYlrN = true;}
      else if(gKPeKNxRoJ == PSbmRSgRdF){njBZFxEzPk = true;}
      if(kdyMLZFGKd == bUjKGyfQWG){qIdGFQdmAa = true;}
      else if(bUjKGyfQWG == kdyMLZFGKd){NUVMDlYuEP = true;}
      if(mbdFCpURyZ == MgimkTnLPw){XOzWLGUXJH = true;}
      else if(MgimkTnLPw == mbdFCpURyZ){ToxPmUaLQo = true;}
      if(ICioFHnakw == pxGDsKjCrS){GbUkFjszcT = true;}
      if(yhRKSbTVjw == rEYQpxhfDA){SUHTCadCuc = true;}
      if(rSfTOmoWjb == CypGVzabtq){bOfWnTBqwe = true;}
      while(pxGDsKjCrS == ICioFHnakw){LiThwrQCah = true;}
      while(rEYQpxhfDA == rEYQpxhfDA){luiKXNfptc = true;}
      while(CypGVzabtq == CypGVzabtq){swSwSzmlmk = true;}
      if(YlCsSeOgQu == true){YlCsSeOgQu = false;}
      if(OdYDNIHSxn == true){OdYDNIHSxn = false;}
      if(kIHOsrHAgs == true){kIHOsrHAgs = false;}
      if(jIIAsGCfxL == true){jIIAsGCfxL = false;}
      if(iBOIlYYlrN == true){iBOIlYYlrN = false;}
      if(qIdGFQdmAa == true){qIdGFQdmAa = false;}
      if(XOzWLGUXJH == true){XOzWLGUXJH = false;}
      if(GbUkFjszcT == true){GbUkFjszcT = false;}
      if(SUHTCadCuc == true){SUHTCadCuc = false;}
      if(bOfWnTBqwe == true){bOfWnTBqwe = false;}
      if(EBcjGPmsAV == true){EBcjGPmsAV = false;}
      if(WdJfHCGfUj == true){WdJfHCGfUj = false;}
      if(bRcgequywk == true){bRcgequywk = false;}
      if(hCDxPRqXMl == true){hCDxPRqXMl = false;}
      if(njBZFxEzPk == true){njBZFxEzPk = false;}
      if(NUVMDlYuEP == true){NUVMDlYuEP = false;}
      if(ToxPmUaLQo == true){ToxPmUaLQo = false;}
      if(LiThwrQCah == true){LiThwrQCah = false;}
      if(luiKXNfptc == true){luiKXNfptc = false;}
      if(swSwSzmlmk == true){swSwSzmlmk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWCSVBZPWI
{ 
  void REZkrZHyip()
  { 
      bool AwlYqocRgs = false;
      bool aITpKXyCzF = false;
      bool RyRXYYDrPy = false;
      bool MFGfmgZNbR = false;
      bool aMFGIINggA = false;
      bool bITVKCdNAR = false;
      bool kjBhfVCnCc = false;
      bool ykZgeErKPQ = false;
      bool LVLPVEkkVk = false;
      bool CLMKfqKWal = false;
      bool GZeDCqhlqF = false;
      bool JTxiFPXlMb = false;
      bool jRSQalXPBm = false;
      bool tUjcKlpHMe = false;
      bool VztPbiOdEP = false;
      bool SYKzCoHOcQ = false;
      bool TSjDKnjUYT = false;
      bool ZPYgFkXCnq = false;
      bool XsLkTUJjaV = false;
      bool ebewLDOpEm = false;
      string KDLxajiHfj;
      string KoIFINEBXp;
      string upxlZIDzgi;
      string EkqdXTXKis;
      string bCBSwtonrV;
      string jGQpSUGZXS;
      string fiawfYxdhn;
      string psSeOrodof;
      string SPGKzxTAKC;
      string NymPNrbEmW;
      string wKGEfpmlbZ;
      string fbjrzPcPxh;
      string FwSeZqGCQV;
      string QjqRiIJCeI;
      string KgYkWkOtPx;
      string PMGERzqbdn;
      string jjVFJukRIq;
      string GajoXYXhHn;
      string cLlSGDdlAj;
      string RgXqYZLSbb;
      if(KDLxajiHfj == wKGEfpmlbZ){AwlYqocRgs = true;}
      else if(wKGEfpmlbZ == KDLxajiHfj){GZeDCqhlqF = true;}
      if(KoIFINEBXp == fbjrzPcPxh){aITpKXyCzF = true;}
      else if(fbjrzPcPxh == KoIFINEBXp){JTxiFPXlMb = true;}
      if(upxlZIDzgi == FwSeZqGCQV){RyRXYYDrPy = true;}
      else if(FwSeZqGCQV == upxlZIDzgi){jRSQalXPBm = true;}
      if(EkqdXTXKis == QjqRiIJCeI){MFGfmgZNbR = true;}
      else if(QjqRiIJCeI == EkqdXTXKis){tUjcKlpHMe = true;}
      if(bCBSwtonrV == KgYkWkOtPx){aMFGIINggA = true;}
      else if(KgYkWkOtPx == bCBSwtonrV){VztPbiOdEP = true;}
      if(jGQpSUGZXS == PMGERzqbdn){bITVKCdNAR = true;}
      else if(PMGERzqbdn == jGQpSUGZXS){SYKzCoHOcQ = true;}
      if(fiawfYxdhn == jjVFJukRIq){kjBhfVCnCc = true;}
      else if(jjVFJukRIq == fiawfYxdhn){TSjDKnjUYT = true;}
      if(psSeOrodof == GajoXYXhHn){ykZgeErKPQ = true;}
      if(SPGKzxTAKC == cLlSGDdlAj){LVLPVEkkVk = true;}
      if(NymPNrbEmW == RgXqYZLSbb){CLMKfqKWal = true;}
      while(GajoXYXhHn == psSeOrodof){ZPYgFkXCnq = true;}
      while(cLlSGDdlAj == cLlSGDdlAj){XsLkTUJjaV = true;}
      while(RgXqYZLSbb == RgXqYZLSbb){ebewLDOpEm = true;}
      if(AwlYqocRgs == true){AwlYqocRgs = false;}
      if(aITpKXyCzF == true){aITpKXyCzF = false;}
      if(RyRXYYDrPy == true){RyRXYYDrPy = false;}
      if(MFGfmgZNbR == true){MFGfmgZNbR = false;}
      if(aMFGIINggA == true){aMFGIINggA = false;}
      if(bITVKCdNAR == true){bITVKCdNAR = false;}
      if(kjBhfVCnCc == true){kjBhfVCnCc = false;}
      if(ykZgeErKPQ == true){ykZgeErKPQ = false;}
      if(LVLPVEkkVk == true){LVLPVEkkVk = false;}
      if(CLMKfqKWal == true){CLMKfqKWal = false;}
      if(GZeDCqhlqF == true){GZeDCqhlqF = false;}
      if(JTxiFPXlMb == true){JTxiFPXlMb = false;}
      if(jRSQalXPBm == true){jRSQalXPBm = false;}
      if(tUjcKlpHMe == true){tUjcKlpHMe = false;}
      if(VztPbiOdEP == true){VztPbiOdEP = false;}
      if(SYKzCoHOcQ == true){SYKzCoHOcQ = false;}
      if(TSjDKnjUYT == true){TSjDKnjUYT = false;}
      if(ZPYgFkXCnq == true){ZPYgFkXCnq = false;}
      if(XsLkTUJjaV == true){XsLkTUJjaV = false;}
      if(ebewLDOpEm == true){ebewLDOpEm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EGIEVOASDU
{ 
  void ezcWtldrAn()
  { 
      bool UbEZkdSEOx = false;
      bool abjfQJMGkA = false;
      bool SrEALfVgDD = false;
      bool PpiUqPOBVx = false;
      bool qRxIHFOiaE = false;
      bool NVFntcXDNE = false;
      bool HkAKhkrPnB = false;
      bool tLjmIAtusG = false;
      bool QlGyptktZO = false;
      bool rLmRpFQlaW = false;
      bool MzuYKCkRfs = false;
      bool hbKHmUeCUn = false;
      bool AypYJiXSxD = false;
      bool jHUVsRqgnm = false;
      bool ISOffPAfdU = false;
      bool aORlWOJVPb = false;
      bool dSUbJaHnOV = false;
      bool dxOgegjJrs = false;
      bool hrnbbVohzd = false;
      bool IURLIpylVF = false;
      string pkUXwFOZOc;
      string GKfGHylVRr;
      string ElgtROoiId;
      string fzQummVRde;
      string ojOlckIUxR;
      string DdXHhEEZFh;
      string QeQjxHskST;
      string bTrlCUWtRg;
      string FTkpaBaJMi;
      string iwMwOJSeoV;
      string qXCdojklFM;
      string gJHYbxtZIu;
      string fjXjkfGwXr;
      string CrFwohRHBq;
      string PoDzCYnmTQ;
      string PrVsoHARrJ;
      string coNNKnELit;
      string flYReqfXhM;
      string rTbHbKVMGh;
      string hzPrNabpoN;
      if(pkUXwFOZOc == qXCdojklFM){UbEZkdSEOx = true;}
      else if(qXCdojklFM == pkUXwFOZOc){MzuYKCkRfs = true;}
      if(GKfGHylVRr == gJHYbxtZIu){abjfQJMGkA = true;}
      else if(gJHYbxtZIu == GKfGHylVRr){hbKHmUeCUn = true;}
      if(ElgtROoiId == fjXjkfGwXr){SrEALfVgDD = true;}
      else if(fjXjkfGwXr == ElgtROoiId){AypYJiXSxD = true;}
      if(fzQummVRde == CrFwohRHBq){PpiUqPOBVx = true;}
      else if(CrFwohRHBq == fzQummVRde){jHUVsRqgnm = true;}
      if(ojOlckIUxR == PoDzCYnmTQ){qRxIHFOiaE = true;}
      else if(PoDzCYnmTQ == ojOlckIUxR){ISOffPAfdU = true;}
      if(DdXHhEEZFh == PrVsoHARrJ){NVFntcXDNE = true;}
      else if(PrVsoHARrJ == DdXHhEEZFh){aORlWOJVPb = true;}
      if(QeQjxHskST == coNNKnELit){HkAKhkrPnB = true;}
      else if(coNNKnELit == QeQjxHskST){dSUbJaHnOV = true;}
      if(bTrlCUWtRg == flYReqfXhM){tLjmIAtusG = true;}
      if(FTkpaBaJMi == rTbHbKVMGh){QlGyptktZO = true;}
      if(iwMwOJSeoV == hzPrNabpoN){rLmRpFQlaW = true;}
      while(flYReqfXhM == bTrlCUWtRg){dxOgegjJrs = true;}
      while(rTbHbKVMGh == rTbHbKVMGh){hrnbbVohzd = true;}
      while(hzPrNabpoN == hzPrNabpoN){IURLIpylVF = true;}
      if(UbEZkdSEOx == true){UbEZkdSEOx = false;}
      if(abjfQJMGkA == true){abjfQJMGkA = false;}
      if(SrEALfVgDD == true){SrEALfVgDD = false;}
      if(PpiUqPOBVx == true){PpiUqPOBVx = false;}
      if(qRxIHFOiaE == true){qRxIHFOiaE = false;}
      if(NVFntcXDNE == true){NVFntcXDNE = false;}
      if(HkAKhkrPnB == true){HkAKhkrPnB = false;}
      if(tLjmIAtusG == true){tLjmIAtusG = false;}
      if(QlGyptktZO == true){QlGyptktZO = false;}
      if(rLmRpFQlaW == true){rLmRpFQlaW = false;}
      if(MzuYKCkRfs == true){MzuYKCkRfs = false;}
      if(hbKHmUeCUn == true){hbKHmUeCUn = false;}
      if(AypYJiXSxD == true){AypYJiXSxD = false;}
      if(jHUVsRqgnm == true){jHUVsRqgnm = false;}
      if(ISOffPAfdU == true){ISOffPAfdU = false;}
      if(aORlWOJVPb == true){aORlWOJVPb = false;}
      if(dSUbJaHnOV == true){dSUbJaHnOV = false;}
      if(dxOgegjJrs == true){dxOgegjJrs = false;}
      if(hrnbbVohzd == true){hrnbbVohzd = false;}
      if(IURLIpylVF == true){IURLIpylVF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OEQRZSDLSN
{ 
  void dBlkgOJNJk()
  { 
      bool ySQEQyOpcD = false;
      bool TQFgZtdOwk = false;
      bool eYVzCBqymS = false;
      bool WtMLOxUKnZ = false;
      bool OQoFJVCLAW = false;
      bool PeEweZxQCP = false;
      bool HQDJfZEsRc = false;
      bool ZSaWVOiPpf = false;
      bool zexQCrpPgo = false;
      bool ADIYRyMeYj = false;
      bool QIsXwxEgZP = false;
      bool pgZVQbTmGn = false;
      bool inMccWKBEX = false;
      bool CDpGPpkYTF = false;
      bool mJpRzScmIp = false;
      bool eZYkAcwQuZ = false;
      bool lCbCNlpTGZ = false;
      bool qtTBAZyudJ = false;
      bool sXsOsbeFGl = false;
      bool sUcsTkgmDM = false;
      string jgIVJHjwaS;
      string LwTYoINIzV;
      string dAeWWVfdnR;
      string dRhAUspQTx;
      string KkEesuUzsU;
      string JpCkYjBkyn;
      string aGIJntNSEu;
      string RxnCKswAca;
      string AfjSInOwbk;
      string rFRfVEcuqz;
      string gCuxCLBAae;
      string nBHWmuVoAA;
      string eRqTDMfIfG;
      string QBJcsyklQw;
      string mNVwwpxtsa;
      string hmtpUPLbso;
      string frTUOlrdco;
      string JjYDNQutWM;
      string PkOFXcGSId;
      string lIraQttAhK;
      if(jgIVJHjwaS == gCuxCLBAae){ySQEQyOpcD = true;}
      else if(gCuxCLBAae == jgIVJHjwaS){QIsXwxEgZP = true;}
      if(LwTYoINIzV == nBHWmuVoAA){TQFgZtdOwk = true;}
      else if(nBHWmuVoAA == LwTYoINIzV){pgZVQbTmGn = true;}
      if(dAeWWVfdnR == eRqTDMfIfG){eYVzCBqymS = true;}
      else if(eRqTDMfIfG == dAeWWVfdnR){inMccWKBEX = true;}
      if(dRhAUspQTx == QBJcsyklQw){WtMLOxUKnZ = true;}
      else if(QBJcsyklQw == dRhAUspQTx){CDpGPpkYTF = true;}
      if(KkEesuUzsU == mNVwwpxtsa){OQoFJVCLAW = true;}
      else if(mNVwwpxtsa == KkEesuUzsU){mJpRzScmIp = true;}
      if(JpCkYjBkyn == hmtpUPLbso){PeEweZxQCP = true;}
      else if(hmtpUPLbso == JpCkYjBkyn){eZYkAcwQuZ = true;}
      if(aGIJntNSEu == frTUOlrdco){HQDJfZEsRc = true;}
      else if(frTUOlrdco == aGIJntNSEu){lCbCNlpTGZ = true;}
      if(RxnCKswAca == JjYDNQutWM){ZSaWVOiPpf = true;}
      if(AfjSInOwbk == PkOFXcGSId){zexQCrpPgo = true;}
      if(rFRfVEcuqz == lIraQttAhK){ADIYRyMeYj = true;}
      while(JjYDNQutWM == RxnCKswAca){qtTBAZyudJ = true;}
      while(PkOFXcGSId == PkOFXcGSId){sXsOsbeFGl = true;}
      while(lIraQttAhK == lIraQttAhK){sUcsTkgmDM = true;}
      if(ySQEQyOpcD == true){ySQEQyOpcD = false;}
      if(TQFgZtdOwk == true){TQFgZtdOwk = false;}
      if(eYVzCBqymS == true){eYVzCBqymS = false;}
      if(WtMLOxUKnZ == true){WtMLOxUKnZ = false;}
      if(OQoFJVCLAW == true){OQoFJVCLAW = false;}
      if(PeEweZxQCP == true){PeEweZxQCP = false;}
      if(HQDJfZEsRc == true){HQDJfZEsRc = false;}
      if(ZSaWVOiPpf == true){ZSaWVOiPpf = false;}
      if(zexQCrpPgo == true){zexQCrpPgo = false;}
      if(ADIYRyMeYj == true){ADIYRyMeYj = false;}
      if(QIsXwxEgZP == true){QIsXwxEgZP = false;}
      if(pgZVQbTmGn == true){pgZVQbTmGn = false;}
      if(inMccWKBEX == true){inMccWKBEX = false;}
      if(CDpGPpkYTF == true){CDpGPpkYTF = false;}
      if(mJpRzScmIp == true){mJpRzScmIp = false;}
      if(eZYkAcwQuZ == true){eZYkAcwQuZ = false;}
      if(lCbCNlpTGZ == true){lCbCNlpTGZ = false;}
      if(qtTBAZyudJ == true){qtTBAZyudJ = false;}
      if(sXsOsbeFGl == true){sXsOsbeFGl = false;}
      if(sUcsTkgmDM == true){sUcsTkgmDM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EQQUKTSQHR
{ 
  void QRHUwwXpKN()
  { 
      bool OFbPMPuEBj = false;
      bool LEGRNRGgmf = false;
      bool AuVcrZzmHh = false;
      bool rzXbjUSQSO = false;
      bool xSnputFUxC = false;
      bool JkAIqTjzWl = false;
      bool PHxSqLgdhr = false;
      bool ypNXihHfgy = false;
      bool TeoEXHzOkQ = false;
      bool jTsgyoVUyi = false;
      bool MblFETWbZJ = false;
      bool MERYRkSruj = false;
      bool MRsRIewgZs = false;
      bool MlgxkrrjAD = false;
      bool jXnaEfBUON = false;
      bool WcYOWuiUxY = false;
      bool XpCgwZWUmZ = false;
      bool rirqzndRMb = false;
      bool caSLWiMSZp = false;
      bool JXmaftVHde = false;
      string IyUGLDGitl;
      string dHMeMirWAR;
      string drfyXygAXh;
      string DSRMGqniYu;
      string wBAltdqiiJ;
      string eXwRnQSVhM;
      string WFKLhKpzYV;
      string tJyEVcqsEs;
      string GxQNDeVzYo;
      string XSBLYppnDi;
      string nqKNOVZrwK;
      string ZZQoFZoxID;
      string npajxbHlee;
      string lCoUFOmDyg;
      string EdDNPyBMFz;
      string BsfAtyQaQm;
      string NmMQYWjwjp;
      string llyazKlMTy;
      string ZuffdrWoZG;
      string yMlKTQRmor;
      if(IyUGLDGitl == nqKNOVZrwK){OFbPMPuEBj = true;}
      else if(nqKNOVZrwK == IyUGLDGitl){MblFETWbZJ = true;}
      if(dHMeMirWAR == ZZQoFZoxID){LEGRNRGgmf = true;}
      else if(ZZQoFZoxID == dHMeMirWAR){MERYRkSruj = true;}
      if(drfyXygAXh == npajxbHlee){AuVcrZzmHh = true;}
      else if(npajxbHlee == drfyXygAXh){MRsRIewgZs = true;}
      if(DSRMGqniYu == lCoUFOmDyg){rzXbjUSQSO = true;}
      else if(lCoUFOmDyg == DSRMGqniYu){MlgxkrrjAD = true;}
      if(wBAltdqiiJ == EdDNPyBMFz){xSnputFUxC = true;}
      else if(EdDNPyBMFz == wBAltdqiiJ){jXnaEfBUON = true;}
      if(eXwRnQSVhM == BsfAtyQaQm){JkAIqTjzWl = true;}
      else if(BsfAtyQaQm == eXwRnQSVhM){WcYOWuiUxY = true;}
      if(WFKLhKpzYV == NmMQYWjwjp){PHxSqLgdhr = true;}
      else if(NmMQYWjwjp == WFKLhKpzYV){XpCgwZWUmZ = true;}
      if(tJyEVcqsEs == llyazKlMTy){ypNXihHfgy = true;}
      if(GxQNDeVzYo == ZuffdrWoZG){TeoEXHzOkQ = true;}
      if(XSBLYppnDi == yMlKTQRmor){jTsgyoVUyi = true;}
      while(llyazKlMTy == tJyEVcqsEs){rirqzndRMb = true;}
      while(ZuffdrWoZG == ZuffdrWoZG){caSLWiMSZp = true;}
      while(yMlKTQRmor == yMlKTQRmor){JXmaftVHde = true;}
      if(OFbPMPuEBj == true){OFbPMPuEBj = false;}
      if(LEGRNRGgmf == true){LEGRNRGgmf = false;}
      if(AuVcrZzmHh == true){AuVcrZzmHh = false;}
      if(rzXbjUSQSO == true){rzXbjUSQSO = false;}
      if(xSnputFUxC == true){xSnputFUxC = false;}
      if(JkAIqTjzWl == true){JkAIqTjzWl = false;}
      if(PHxSqLgdhr == true){PHxSqLgdhr = false;}
      if(ypNXihHfgy == true){ypNXihHfgy = false;}
      if(TeoEXHzOkQ == true){TeoEXHzOkQ = false;}
      if(jTsgyoVUyi == true){jTsgyoVUyi = false;}
      if(MblFETWbZJ == true){MblFETWbZJ = false;}
      if(MERYRkSruj == true){MERYRkSruj = false;}
      if(MRsRIewgZs == true){MRsRIewgZs = false;}
      if(MlgxkrrjAD == true){MlgxkrrjAD = false;}
      if(jXnaEfBUON == true){jXnaEfBUON = false;}
      if(WcYOWuiUxY == true){WcYOWuiUxY = false;}
      if(XpCgwZWUmZ == true){XpCgwZWUmZ = false;}
      if(rirqzndRMb == true){rirqzndRMb = false;}
      if(caSLWiMSZp == true){caSLWiMSZp = false;}
      if(JXmaftVHde == true){JXmaftVHde = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ICYZVIKQDW
{ 
  void plpXxLgGpX()
  { 
      bool KIutSHbEEP = false;
      bool qGEzyktPxW = false;
      bool eRxUxZONUW = false;
      bool NlpgMYnDPx = false;
      bool tuGEsSUbZt = false;
      bool iHyHzrLZxs = false;
      bool sNjgCFQWmY = false;
      bool wpAzciLrbd = false;
      bool EmmZmFnihU = false;
      bool NNGVEfLYCn = false;
      bool CynBxsHyeQ = false;
      bool fSySnGaJsw = false;
      bool RhnSLhjduw = false;
      bool XlonbFylbt = false;
      bool yoEQntPmhx = false;
      bool FCeGVTJUoP = false;
      bool IdDhssdJpi = false;
      bool HogzybdXeQ = false;
      bool SwwxqVGiRI = false;
      bool ucwMlUkVXt = false;
      string HJcdQrTlXy;
      string DdHuGABkgr;
      string cQXMzaaBCR;
      string tbwQhQexeY;
      string EnJfikIzWJ;
      string KOHsRpkQdp;
      string QSiFDagpNp;
      string VEFInnHrcN;
      string SberGfUCzr;
      string fNSoHkEDcH;
      string DRlgnGIyFc;
      string hrmQXonqzX;
      string GeqVJHlPAC;
      string jDPVJApyEz;
      string WVxWJmZBRS;
      string xNDEAYaQWf;
      string UryCrecRGW;
      string zplzAkgTMW;
      string gjyhFVzKUk;
      string ZYaYedXude;
      if(HJcdQrTlXy == DRlgnGIyFc){KIutSHbEEP = true;}
      else if(DRlgnGIyFc == HJcdQrTlXy){CynBxsHyeQ = true;}
      if(DdHuGABkgr == hrmQXonqzX){qGEzyktPxW = true;}
      else if(hrmQXonqzX == DdHuGABkgr){fSySnGaJsw = true;}
      if(cQXMzaaBCR == GeqVJHlPAC){eRxUxZONUW = true;}
      else if(GeqVJHlPAC == cQXMzaaBCR){RhnSLhjduw = true;}
      if(tbwQhQexeY == jDPVJApyEz){NlpgMYnDPx = true;}
      else if(jDPVJApyEz == tbwQhQexeY){XlonbFylbt = true;}
      if(EnJfikIzWJ == WVxWJmZBRS){tuGEsSUbZt = true;}
      else if(WVxWJmZBRS == EnJfikIzWJ){yoEQntPmhx = true;}
      if(KOHsRpkQdp == xNDEAYaQWf){iHyHzrLZxs = true;}
      else if(xNDEAYaQWf == KOHsRpkQdp){FCeGVTJUoP = true;}
      if(QSiFDagpNp == UryCrecRGW){sNjgCFQWmY = true;}
      else if(UryCrecRGW == QSiFDagpNp){IdDhssdJpi = true;}
      if(VEFInnHrcN == zplzAkgTMW){wpAzciLrbd = true;}
      if(SberGfUCzr == gjyhFVzKUk){EmmZmFnihU = true;}
      if(fNSoHkEDcH == ZYaYedXude){NNGVEfLYCn = true;}
      while(zplzAkgTMW == VEFInnHrcN){HogzybdXeQ = true;}
      while(gjyhFVzKUk == gjyhFVzKUk){SwwxqVGiRI = true;}
      while(ZYaYedXude == ZYaYedXude){ucwMlUkVXt = true;}
      if(KIutSHbEEP == true){KIutSHbEEP = false;}
      if(qGEzyktPxW == true){qGEzyktPxW = false;}
      if(eRxUxZONUW == true){eRxUxZONUW = false;}
      if(NlpgMYnDPx == true){NlpgMYnDPx = false;}
      if(tuGEsSUbZt == true){tuGEsSUbZt = false;}
      if(iHyHzrLZxs == true){iHyHzrLZxs = false;}
      if(sNjgCFQWmY == true){sNjgCFQWmY = false;}
      if(wpAzciLrbd == true){wpAzciLrbd = false;}
      if(EmmZmFnihU == true){EmmZmFnihU = false;}
      if(NNGVEfLYCn == true){NNGVEfLYCn = false;}
      if(CynBxsHyeQ == true){CynBxsHyeQ = false;}
      if(fSySnGaJsw == true){fSySnGaJsw = false;}
      if(RhnSLhjduw == true){RhnSLhjduw = false;}
      if(XlonbFylbt == true){XlonbFylbt = false;}
      if(yoEQntPmhx == true){yoEQntPmhx = false;}
      if(FCeGVTJUoP == true){FCeGVTJUoP = false;}
      if(IdDhssdJpi == true){IdDhssdJpi = false;}
      if(HogzybdXeQ == true){HogzybdXeQ = false;}
      if(SwwxqVGiRI == true){SwwxqVGiRI = false;}
      if(ucwMlUkVXt == true){ucwMlUkVXt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMVLOAZTNV
{ 
  void GXbNAgRRkf()
  { 
      bool mHDYPFBwAo = false;
      bool amVNpKVSRz = false;
      bool FUwDQNRWlx = false;
      bool jypCnrUMoz = false;
      bool ZqgiVkeVMc = false;
      bool VHcwfSLzHB = false;
      bool meKDEcwSZx = false;
      bool oJdSZOmMgf = false;
      bool iwJJacVtWU = false;
      bool gUEmLtfdds = false;
      bool nLuOmMdKWR = false;
      bool ezRbSqUBbb = false;
      bool GCwEQUEpGe = false;
      bool hIhnqWAuVN = false;
      bool zLXEogCbTU = false;
      bool ZeBClkPqxS = false;
      bool ImDqiWQdkw = false;
      bool pZeObteqOj = false;
      bool RbVlFDGeBF = false;
      bool GJxDFMHfVS = false;
      string qHjNLsYTOU;
      string RrsQaypmKf;
      string fNdHtjbTjo;
      string WCefMsyqgV;
      string mfobYtyjnU;
      string JOwcdccbSb;
      string RFjZxPNMEh;
      string zzGnszYChz;
      string kqePeIGBCj;
      string QVXFEgwPeJ;
      string gkfGUKIHid;
      string DZsTpZZUto;
      string JLKUQcbAiM;
      string DJXYSzLYtU;
      string zyRXfpcDOd;
      string GbVoAUaKoq;
      string hHXWatCUAp;
      string OBZYoKsmoa;
      string AXlFFanhYx;
      string YAiDmrZtwl;
      if(qHjNLsYTOU == gkfGUKIHid){mHDYPFBwAo = true;}
      else if(gkfGUKIHid == qHjNLsYTOU){nLuOmMdKWR = true;}
      if(RrsQaypmKf == DZsTpZZUto){amVNpKVSRz = true;}
      else if(DZsTpZZUto == RrsQaypmKf){ezRbSqUBbb = true;}
      if(fNdHtjbTjo == JLKUQcbAiM){FUwDQNRWlx = true;}
      else if(JLKUQcbAiM == fNdHtjbTjo){GCwEQUEpGe = true;}
      if(WCefMsyqgV == DJXYSzLYtU){jypCnrUMoz = true;}
      else if(DJXYSzLYtU == WCefMsyqgV){hIhnqWAuVN = true;}
      if(mfobYtyjnU == zyRXfpcDOd){ZqgiVkeVMc = true;}
      else if(zyRXfpcDOd == mfobYtyjnU){zLXEogCbTU = true;}
      if(JOwcdccbSb == GbVoAUaKoq){VHcwfSLzHB = true;}
      else if(GbVoAUaKoq == JOwcdccbSb){ZeBClkPqxS = true;}
      if(RFjZxPNMEh == hHXWatCUAp){meKDEcwSZx = true;}
      else if(hHXWatCUAp == RFjZxPNMEh){ImDqiWQdkw = true;}
      if(zzGnszYChz == OBZYoKsmoa){oJdSZOmMgf = true;}
      if(kqePeIGBCj == AXlFFanhYx){iwJJacVtWU = true;}
      if(QVXFEgwPeJ == YAiDmrZtwl){gUEmLtfdds = true;}
      while(OBZYoKsmoa == zzGnszYChz){pZeObteqOj = true;}
      while(AXlFFanhYx == AXlFFanhYx){RbVlFDGeBF = true;}
      while(YAiDmrZtwl == YAiDmrZtwl){GJxDFMHfVS = true;}
      if(mHDYPFBwAo == true){mHDYPFBwAo = false;}
      if(amVNpKVSRz == true){amVNpKVSRz = false;}
      if(FUwDQNRWlx == true){FUwDQNRWlx = false;}
      if(jypCnrUMoz == true){jypCnrUMoz = false;}
      if(ZqgiVkeVMc == true){ZqgiVkeVMc = false;}
      if(VHcwfSLzHB == true){VHcwfSLzHB = false;}
      if(meKDEcwSZx == true){meKDEcwSZx = false;}
      if(oJdSZOmMgf == true){oJdSZOmMgf = false;}
      if(iwJJacVtWU == true){iwJJacVtWU = false;}
      if(gUEmLtfdds == true){gUEmLtfdds = false;}
      if(nLuOmMdKWR == true){nLuOmMdKWR = false;}
      if(ezRbSqUBbb == true){ezRbSqUBbb = false;}
      if(GCwEQUEpGe == true){GCwEQUEpGe = false;}
      if(hIhnqWAuVN == true){hIhnqWAuVN = false;}
      if(zLXEogCbTU == true){zLXEogCbTU = false;}
      if(ZeBClkPqxS == true){ZeBClkPqxS = false;}
      if(ImDqiWQdkw == true){ImDqiWQdkw = false;}
      if(pZeObteqOj == true){pZeObteqOj = false;}
      if(RbVlFDGeBF == true){RbVlFDGeBF = false;}
      if(GJxDFMHfVS == true){GJxDFMHfVS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NJCWFCYKRB
{ 
  void JLQyqIZAaO()
  { 
      bool aXEQhXJbHb = false;
      bool fMVxxEjDGq = false;
      bool WmHtVwQBqi = false;
      bool KmwUhyrDSh = false;
      bool NUBpFXBcxA = false;
      bool YePwNnQKtl = false;
      bool HHkYRrPAOz = false;
      bool MfkYcCkQnx = false;
      bool umDpKeWAHt = false;
      bool hhIfZGicYM = false;
      bool IANynrtpSK = false;
      bool CzVwqTDtNm = false;
      bool VPrUReXEyW = false;
      bool SIrbotZFCS = false;
      bool jggwrhLLoG = false;
      bool CoOkqrHsgJ = false;
      bool UorurtHsHx = false;
      bool tyquCnhwbi = false;
      bool SLPrTcsGkx = false;
      bool lgXrytnlEx = false;
      string KwTSyeLnkO;
      string oVZrIzaXkn;
      string cUbPDpdSZs;
      string EQJnkyREUS;
      string fgVOZuWsyW;
      string EyXqppTEOH;
      string BrOrKXMlGK;
      string hWDSIwzNoI;
      string SjUCnGrSxu;
      string dNoMRmRcDB;
      string hklmnhtFit;
      string pGOFoQXLDD;
      string fsnKgUgqBU;
      string dVJnZhygOG;
      string LmjDEXyjXA;
      string OGYAUoxaGT;
      string BDDNPTwZeG;
      string SpxxrsJjFJ;
      string VwTAGXwJSk;
      string kWZuFIiWnk;
      if(KwTSyeLnkO == hklmnhtFit){aXEQhXJbHb = true;}
      else if(hklmnhtFit == KwTSyeLnkO){IANynrtpSK = true;}
      if(oVZrIzaXkn == pGOFoQXLDD){fMVxxEjDGq = true;}
      else if(pGOFoQXLDD == oVZrIzaXkn){CzVwqTDtNm = true;}
      if(cUbPDpdSZs == fsnKgUgqBU){WmHtVwQBqi = true;}
      else if(fsnKgUgqBU == cUbPDpdSZs){VPrUReXEyW = true;}
      if(EQJnkyREUS == dVJnZhygOG){KmwUhyrDSh = true;}
      else if(dVJnZhygOG == EQJnkyREUS){SIrbotZFCS = true;}
      if(fgVOZuWsyW == LmjDEXyjXA){NUBpFXBcxA = true;}
      else if(LmjDEXyjXA == fgVOZuWsyW){jggwrhLLoG = true;}
      if(EyXqppTEOH == OGYAUoxaGT){YePwNnQKtl = true;}
      else if(OGYAUoxaGT == EyXqppTEOH){CoOkqrHsgJ = true;}
      if(BrOrKXMlGK == BDDNPTwZeG){HHkYRrPAOz = true;}
      else if(BDDNPTwZeG == BrOrKXMlGK){UorurtHsHx = true;}
      if(hWDSIwzNoI == SpxxrsJjFJ){MfkYcCkQnx = true;}
      if(SjUCnGrSxu == VwTAGXwJSk){umDpKeWAHt = true;}
      if(dNoMRmRcDB == kWZuFIiWnk){hhIfZGicYM = true;}
      while(SpxxrsJjFJ == hWDSIwzNoI){tyquCnhwbi = true;}
      while(VwTAGXwJSk == VwTAGXwJSk){SLPrTcsGkx = true;}
      while(kWZuFIiWnk == kWZuFIiWnk){lgXrytnlEx = true;}
      if(aXEQhXJbHb == true){aXEQhXJbHb = false;}
      if(fMVxxEjDGq == true){fMVxxEjDGq = false;}
      if(WmHtVwQBqi == true){WmHtVwQBqi = false;}
      if(KmwUhyrDSh == true){KmwUhyrDSh = false;}
      if(NUBpFXBcxA == true){NUBpFXBcxA = false;}
      if(YePwNnQKtl == true){YePwNnQKtl = false;}
      if(HHkYRrPAOz == true){HHkYRrPAOz = false;}
      if(MfkYcCkQnx == true){MfkYcCkQnx = false;}
      if(umDpKeWAHt == true){umDpKeWAHt = false;}
      if(hhIfZGicYM == true){hhIfZGicYM = false;}
      if(IANynrtpSK == true){IANynrtpSK = false;}
      if(CzVwqTDtNm == true){CzVwqTDtNm = false;}
      if(VPrUReXEyW == true){VPrUReXEyW = false;}
      if(SIrbotZFCS == true){SIrbotZFCS = false;}
      if(jggwrhLLoG == true){jggwrhLLoG = false;}
      if(CoOkqrHsgJ == true){CoOkqrHsgJ = false;}
      if(UorurtHsHx == true){UorurtHsHx = false;}
      if(tyquCnhwbi == true){tyquCnhwbi = false;}
      if(SLPrTcsGkx == true){SLPrTcsGkx = false;}
      if(lgXrytnlEx == true){lgXrytnlEx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ERXGFGZFFV
{ 
  void EYuzRoUCUn()
  { 
      bool scZFOVZXKp = false;
      bool FUUrwLgCGF = false;
      bool HfgyPMODXL = false;
      bool WteXcgfShO = false;
      bool QGnmtxlJqO = false;
      bool TNMMKMwaoC = false;
      bool HWzzTKpxOP = false;
      bool eNUroArtES = false;
      bool ZEMIqIhRNQ = false;
      bool jFcfGtGoSi = false;
      bool HouaiFsTXK = false;
      bool UBVWbCJpHL = false;
      bool cXixeZknkt = false;
      bool sCbVLkJkZk = false;
      bool PNsCwhiFEE = false;
      bool kPgHFiFxwI = false;
      bool UEidQRZALp = false;
      bool sXQWuPegBw = false;
      bool qejgJcUTPb = false;
      bool eLoQPKdPld = false;
      string DHlUWhNqlF;
      string qjVZETfQtb;
      string tFucwjSDHF;
      string NmlknkOMun;
      string fjrimnRrcJ;
      string PnnLPyMIXl;
      string PJifrEyjkT;
      string ESVFuJMLpH;
      string SaayoYzaVp;
      string YGnIYWBMpi;
      string pgGJEwShPF;
      string lARPTnijpT;
      string EXOttyeMgY;
      string IAVHRkTRsr;
      string GQKQEXnXnj;
      string mQVWdSSLOG;
      string RFAqxleKyh;
      string URpyMmMypW;
      string KGYxkqdycz;
      string SHCmZBQSSR;
      if(DHlUWhNqlF == pgGJEwShPF){scZFOVZXKp = true;}
      else if(pgGJEwShPF == DHlUWhNqlF){HouaiFsTXK = true;}
      if(qjVZETfQtb == lARPTnijpT){FUUrwLgCGF = true;}
      else if(lARPTnijpT == qjVZETfQtb){UBVWbCJpHL = true;}
      if(tFucwjSDHF == EXOttyeMgY){HfgyPMODXL = true;}
      else if(EXOttyeMgY == tFucwjSDHF){cXixeZknkt = true;}
      if(NmlknkOMun == IAVHRkTRsr){WteXcgfShO = true;}
      else if(IAVHRkTRsr == NmlknkOMun){sCbVLkJkZk = true;}
      if(fjrimnRrcJ == GQKQEXnXnj){QGnmtxlJqO = true;}
      else if(GQKQEXnXnj == fjrimnRrcJ){PNsCwhiFEE = true;}
      if(PnnLPyMIXl == mQVWdSSLOG){TNMMKMwaoC = true;}
      else if(mQVWdSSLOG == PnnLPyMIXl){kPgHFiFxwI = true;}
      if(PJifrEyjkT == RFAqxleKyh){HWzzTKpxOP = true;}
      else if(RFAqxleKyh == PJifrEyjkT){UEidQRZALp = true;}
      if(ESVFuJMLpH == URpyMmMypW){eNUroArtES = true;}
      if(SaayoYzaVp == KGYxkqdycz){ZEMIqIhRNQ = true;}
      if(YGnIYWBMpi == SHCmZBQSSR){jFcfGtGoSi = true;}
      while(URpyMmMypW == ESVFuJMLpH){sXQWuPegBw = true;}
      while(KGYxkqdycz == KGYxkqdycz){qejgJcUTPb = true;}
      while(SHCmZBQSSR == SHCmZBQSSR){eLoQPKdPld = true;}
      if(scZFOVZXKp == true){scZFOVZXKp = false;}
      if(FUUrwLgCGF == true){FUUrwLgCGF = false;}
      if(HfgyPMODXL == true){HfgyPMODXL = false;}
      if(WteXcgfShO == true){WteXcgfShO = false;}
      if(QGnmtxlJqO == true){QGnmtxlJqO = false;}
      if(TNMMKMwaoC == true){TNMMKMwaoC = false;}
      if(HWzzTKpxOP == true){HWzzTKpxOP = false;}
      if(eNUroArtES == true){eNUroArtES = false;}
      if(ZEMIqIhRNQ == true){ZEMIqIhRNQ = false;}
      if(jFcfGtGoSi == true){jFcfGtGoSi = false;}
      if(HouaiFsTXK == true){HouaiFsTXK = false;}
      if(UBVWbCJpHL == true){UBVWbCJpHL = false;}
      if(cXixeZknkt == true){cXixeZknkt = false;}
      if(sCbVLkJkZk == true){sCbVLkJkZk = false;}
      if(PNsCwhiFEE == true){PNsCwhiFEE = false;}
      if(kPgHFiFxwI == true){kPgHFiFxwI = false;}
      if(UEidQRZALp == true){UEidQRZALp = false;}
      if(sXQWuPegBw == true){sXQWuPegBw = false;}
      if(qejgJcUTPb == true){qejgJcUTPb = false;}
      if(eLoQPKdPld == true){eLoQPKdPld = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TDPCNFHBCU
{ 
  void EJKzAKOknK()
  { 
      bool gKMEEYdNSs = false;
      bool lzEYiAwyNh = false;
      bool AeBQexiAJQ = false;
      bool iaGLPpWBcV = false;
      bool zJbxiHJulW = false;
      bool OiVslBIwZH = false;
      bool pdECKKrrJr = false;
      bool ctVqiqCDgW = false;
      bool mmOlBzFMZO = false;
      bool gabVfUEZmX = false;
      bool OQlssUMdKu = false;
      bool zFOCTCPRBK = false;
      bool FfSuKCRAKN = false;
      bool lbQJHVAUsf = false;
      bool mbCdObMZBc = false;
      bool FmXbSiyqhq = false;
      bool DMSwJXnFtx = false;
      bool CtYUXcdofi = false;
      bool pryhHzDnpY = false;
      bool XIlCcZIFTq = false;
      string tDZITMgtHa;
      string cVZFpVSxng;
      string sCMulAFTco;
      string YHyXsOYbjz;
      string kpBlHVHZBj;
      string LLRarqqeVT;
      string HMRRCUXCLa;
      string xpMnuCBZmQ;
      string seRrdMpWeB;
      string XtFQqXYijm;
      string yENZmVzcfp;
      string pQqFZbuZno;
      string dBWKDDjwwX;
      string cRpzSnRqEH;
      string NNqoLGCApP;
      string czttJwgDVj;
      string kCfIMXZqml;
      string KDUfbQKhzw;
      string BjGgtdXupV;
      string GNUUWLgibm;
      if(tDZITMgtHa == yENZmVzcfp){gKMEEYdNSs = true;}
      else if(yENZmVzcfp == tDZITMgtHa){OQlssUMdKu = true;}
      if(cVZFpVSxng == pQqFZbuZno){lzEYiAwyNh = true;}
      else if(pQqFZbuZno == cVZFpVSxng){zFOCTCPRBK = true;}
      if(sCMulAFTco == dBWKDDjwwX){AeBQexiAJQ = true;}
      else if(dBWKDDjwwX == sCMulAFTco){FfSuKCRAKN = true;}
      if(YHyXsOYbjz == cRpzSnRqEH){iaGLPpWBcV = true;}
      else if(cRpzSnRqEH == YHyXsOYbjz){lbQJHVAUsf = true;}
      if(kpBlHVHZBj == NNqoLGCApP){zJbxiHJulW = true;}
      else if(NNqoLGCApP == kpBlHVHZBj){mbCdObMZBc = true;}
      if(LLRarqqeVT == czttJwgDVj){OiVslBIwZH = true;}
      else if(czttJwgDVj == LLRarqqeVT){FmXbSiyqhq = true;}
      if(HMRRCUXCLa == kCfIMXZqml){pdECKKrrJr = true;}
      else if(kCfIMXZqml == HMRRCUXCLa){DMSwJXnFtx = true;}
      if(xpMnuCBZmQ == KDUfbQKhzw){ctVqiqCDgW = true;}
      if(seRrdMpWeB == BjGgtdXupV){mmOlBzFMZO = true;}
      if(XtFQqXYijm == GNUUWLgibm){gabVfUEZmX = true;}
      while(KDUfbQKhzw == xpMnuCBZmQ){CtYUXcdofi = true;}
      while(BjGgtdXupV == BjGgtdXupV){pryhHzDnpY = true;}
      while(GNUUWLgibm == GNUUWLgibm){XIlCcZIFTq = true;}
      if(gKMEEYdNSs == true){gKMEEYdNSs = false;}
      if(lzEYiAwyNh == true){lzEYiAwyNh = false;}
      if(AeBQexiAJQ == true){AeBQexiAJQ = false;}
      if(iaGLPpWBcV == true){iaGLPpWBcV = false;}
      if(zJbxiHJulW == true){zJbxiHJulW = false;}
      if(OiVslBIwZH == true){OiVslBIwZH = false;}
      if(pdECKKrrJr == true){pdECKKrrJr = false;}
      if(ctVqiqCDgW == true){ctVqiqCDgW = false;}
      if(mmOlBzFMZO == true){mmOlBzFMZO = false;}
      if(gabVfUEZmX == true){gabVfUEZmX = false;}
      if(OQlssUMdKu == true){OQlssUMdKu = false;}
      if(zFOCTCPRBK == true){zFOCTCPRBK = false;}
      if(FfSuKCRAKN == true){FfSuKCRAKN = false;}
      if(lbQJHVAUsf == true){lbQJHVAUsf = false;}
      if(mbCdObMZBc == true){mbCdObMZBc = false;}
      if(FmXbSiyqhq == true){FmXbSiyqhq = false;}
      if(DMSwJXnFtx == true){DMSwJXnFtx = false;}
      if(CtYUXcdofi == true){CtYUXcdofi = false;}
      if(pryhHzDnpY == true){pryhHzDnpY = false;}
      if(XIlCcZIFTq == true){XIlCcZIFTq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ROPYYEMLKE
{ 
  void WplItNPnyu()
  { 
      bool kkiSgsuCYQ = false;
      bool rnLOVhxOmt = false;
      bool PHnrlVIUYC = false;
      bool GLuddKnlby = false;
      bool SOmoLQyBBr = false;
      bool rLuGmcxqgK = false;
      bool jZcVKgsgkL = false;
      bool sLlobBTyfU = false;
      bool XHTgKtQnqA = false;
      bool NxFRNrkRee = false;
      bool XRQpzgZFel = false;
      bool JyKLmcGwLP = false;
      bool PEpjxuGTai = false;
      bool PCSBxFpchc = false;
      bool UKJEqOlsdj = false;
      bool lnFPOSafrD = false;
      bool aFeuWHfINg = false;
      bool mcOhtFuksi = false;
      bool IMopxawDme = false;
      bool dKkdCPfNhi = false;
      string DrFWFOYwsV;
      string XLVhtLOLFC;
      string IDTbxrUKfW;
      string eBxyhZHrFn;
      string CkDqxKMJRy;
      string fWKqfzYcZN;
      string tNPVqVOWzU;
      string EVGQAWAcel;
      string fLrhpHqFRi;
      string BdSqtnVgza;
      string uoJxsJQsqJ;
      string zwymghUhfi;
      string dIEQTaDOVL;
      string BScDqpCuof;
      string qxOIiEeeJM;
      string TnBQxmkrdR;
      string GBXfHgTtwq;
      string fZrzrftwgO;
      string uXEJrNQMGD;
      string FJQXZoZiAC;
      if(DrFWFOYwsV == uoJxsJQsqJ){kkiSgsuCYQ = true;}
      else if(uoJxsJQsqJ == DrFWFOYwsV){XRQpzgZFel = true;}
      if(XLVhtLOLFC == zwymghUhfi){rnLOVhxOmt = true;}
      else if(zwymghUhfi == XLVhtLOLFC){JyKLmcGwLP = true;}
      if(IDTbxrUKfW == dIEQTaDOVL){PHnrlVIUYC = true;}
      else if(dIEQTaDOVL == IDTbxrUKfW){PEpjxuGTai = true;}
      if(eBxyhZHrFn == BScDqpCuof){GLuddKnlby = true;}
      else if(BScDqpCuof == eBxyhZHrFn){PCSBxFpchc = true;}
      if(CkDqxKMJRy == qxOIiEeeJM){SOmoLQyBBr = true;}
      else if(qxOIiEeeJM == CkDqxKMJRy){UKJEqOlsdj = true;}
      if(fWKqfzYcZN == TnBQxmkrdR){rLuGmcxqgK = true;}
      else if(TnBQxmkrdR == fWKqfzYcZN){lnFPOSafrD = true;}
      if(tNPVqVOWzU == GBXfHgTtwq){jZcVKgsgkL = true;}
      else if(GBXfHgTtwq == tNPVqVOWzU){aFeuWHfINg = true;}
      if(EVGQAWAcel == fZrzrftwgO){sLlobBTyfU = true;}
      if(fLrhpHqFRi == uXEJrNQMGD){XHTgKtQnqA = true;}
      if(BdSqtnVgza == FJQXZoZiAC){NxFRNrkRee = true;}
      while(fZrzrftwgO == EVGQAWAcel){mcOhtFuksi = true;}
      while(uXEJrNQMGD == uXEJrNQMGD){IMopxawDme = true;}
      while(FJQXZoZiAC == FJQXZoZiAC){dKkdCPfNhi = true;}
      if(kkiSgsuCYQ == true){kkiSgsuCYQ = false;}
      if(rnLOVhxOmt == true){rnLOVhxOmt = false;}
      if(PHnrlVIUYC == true){PHnrlVIUYC = false;}
      if(GLuddKnlby == true){GLuddKnlby = false;}
      if(SOmoLQyBBr == true){SOmoLQyBBr = false;}
      if(rLuGmcxqgK == true){rLuGmcxqgK = false;}
      if(jZcVKgsgkL == true){jZcVKgsgkL = false;}
      if(sLlobBTyfU == true){sLlobBTyfU = false;}
      if(XHTgKtQnqA == true){XHTgKtQnqA = false;}
      if(NxFRNrkRee == true){NxFRNrkRee = false;}
      if(XRQpzgZFel == true){XRQpzgZFel = false;}
      if(JyKLmcGwLP == true){JyKLmcGwLP = false;}
      if(PEpjxuGTai == true){PEpjxuGTai = false;}
      if(PCSBxFpchc == true){PCSBxFpchc = false;}
      if(UKJEqOlsdj == true){UKJEqOlsdj = false;}
      if(lnFPOSafrD == true){lnFPOSafrD = false;}
      if(aFeuWHfINg == true){aFeuWHfINg = false;}
      if(mcOhtFuksi == true){mcOhtFuksi = false;}
      if(IMopxawDme == true){IMopxawDme = false;}
      if(dKkdCPfNhi == true){dKkdCPfNhi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class THMJLQNLXQ
{ 
  void WUKwreRedL()
  { 
      bool VesZIQfTFJ = false;
      bool NVxDPtiSVR = false;
      bool VGhlTXZdxM = false;
      bool cdsyXnqQgV = false;
      bool jBFiNCTuDb = false;
      bool oPEDdPxGFj = false;
      bool qBVrgibzfa = false;
      bool CRkAhUAyYQ = false;
      bool EeaVWMZpTH = false;
      bool pkKweheMCe = false;
      bool ZUObYWeDUJ = false;
      bool PzhnfLaAVU = false;
      bool JleXkRHnVz = false;
      bool omwtqiPywA = false;
      bool hVUJqpDVPS = false;
      bool HeqgUnpqpH = false;
      bool PphVUcDnxx = false;
      bool wbEVmmQUft = false;
      bool OkXDqJuOYD = false;
      bool rYIojqmzoO = false;
      string jLmfdXAEqF;
      string cKfnpBgHBE;
      string LSQHUPSzsz;
      string oizfHBcZgH;
      string NnBoTSDSVh;
      string cIqczRteKN;
      string EALrPtKzfo;
      string XGaspWRbnC;
      string MAdLWfqVfp;
      string GxPSDMcIZY;
      string HDlfJVhylb;
      string zSqIBEWzUi;
      string DoSphZqIoc;
      string tIBPtINxCA;
      string yrjDqnGGRz;
      string pdnpVSkwyi;
      string dZJIhpRaNr;
      string pYxTkLFOyt;
      string TjppmPULsb;
      string XRzSWYiaVA;
      if(jLmfdXAEqF == HDlfJVhylb){VesZIQfTFJ = true;}
      else if(HDlfJVhylb == jLmfdXAEqF){ZUObYWeDUJ = true;}
      if(cKfnpBgHBE == zSqIBEWzUi){NVxDPtiSVR = true;}
      else if(zSqIBEWzUi == cKfnpBgHBE){PzhnfLaAVU = true;}
      if(LSQHUPSzsz == DoSphZqIoc){VGhlTXZdxM = true;}
      else if(DoSphZqIoc == LSQHUPSzsz){JleXkRHnVz = true;}
      if(oizfHBcZgH == tIBPtINxCA){cdsyXnqQgV = true;}
      else if(tIBPtINxCA == oizfHBcZgH){omwtqiPywA = true;}
      if(NnBoTSDSVh == yrjDqnGGRz){jBFiNCTuDb = true;}
      else if(yrjDqnGGRz == NnBoTSDSVh){hVUJqpDVPS = true;}
      if(cIqczRteKN == pdnpVSkwyi){oPEDdPxGFj = true;}
      else if(pdnpVSkwyi == cIqczRteKN){HeqgUnpqpH = true;}
      if(EALrPtKzfo == dZJIhpRaNr){qBVrgibzfa = true;}
      else if(dZJIhpRaNr == EALrPtKzfo){PphVUcDnxx = true;}
      if(XGaspWRbnC == pYxTkLFOyt){CRkAhUAyYQ = true;}
      if(MAdLWfqVfp == TjppmPULsb){EeaVWMZpTH = true;}
      if(GxPSDMcIZY == XRzSWYiaVA){pkKweheMCe = true;}
      while(pYxTkLFOyt == XGaspWRbnC){wbEVmmQUft = true;}
      while(TjppmPULsb == TjppmPULsb){OkXDqJuOYD = true;}
      while(XRzSWYiaVA == XRzSWYiaVA){rYIojqmzoO = true;}
      if(VesZIQfTFJ == true){VesZIQfTFJ = false;}
      if(NVxDPtiSVR == true){NVxDPtiSVR = false;}
      if(VGhlTXZdxM == true){VGhlTXZdxM = false;}
      if(cdsyXnqQgV == true){cdsyXnqQgV = false;}
      if(jBFiNCTuDb == true){jBFiNCTuDb = false;}
      if(oPEDdPxGFj == true){oPEDdPxGFj = false;}
      if(qBVrgibzfa == true){qBVrgibzfa = false;}
      if(CRkAhUAyYQ == true){CRkAhUAyYQ = false;}
      if(EeaVWMZpTH == true){EeaVWMZpTH = false;}
      if(pkKweheMCe == true){pkKweheMCe = false;}
      if(ZUObYWeDUJ == true){ZUObYWeDUJ = false;}
      if(PzhnfLaAVU == true){PzhnfLaAVU = false;}
      if(JleXkRHnVz == true){JleXkRHnVz = false;}
      if(omwtqiPywA == true){omwtqiPywA = false;}
      if(hVUJqpDVPS == true){hVUJqpDVPS = false;}
      if(HeqgUnpqpH == true){HeqgUnpqpH = false;}
      if(PphVUcDnxx == true){PphVUcDnxx = false;}
      if(wbEVmmQUft == true){wbEVmmQUft = false;}
      if(OkXDqJuOYD == true){OkXDqJuOYD = false;}
      if(rYIojqmzoO == true){rYIojqmzoO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VXVUHOEAEY
{ 
  void MzpmrAdCHp()
  { 
      bool ZYEDRiyRrw = false;
      bool TyFjtEPAGY = false;
      bool BuOApUAUFZ = false;
      bool hkcjIsJrNy = false;
      bool dVXHxaCotJ = false;
      bool eXDuTeKENx = false;
      bool idLSOiUUbB = false;
      bool tWlIueWHDP = false;
      bool RKauuJghPd = false;
      bool iFdQPAJFrN = false;
      bool FgNsPHkuzn = false;
      bool HDAyeXCPWE = false;
      bool BmExSnsVru = false;
      bool VQOoJjwhfn = false;
      bool YlhbWeFekq = false;
      bool xsinLRbQZa = false;
      bool OOCESpnKou = false;
      bool bUjiePFcam = false;
      bool iNkAxbhacr = false;
      bool HfHEZJicJf = false;
      string RPnYqnRBpa;
      string yEfgcdZgsz;
      string KqIxeZBQRB;
      string VeeDwhFQRc;
      string eEdrelqJit;
      string NpVAtZGpsQ;
      string mBioFTZcju;
      string XIPPUGNQRs;
      string hqgXmfJeJV;
      string aOWApdUnlL;
      string LOYmVFZFem;
      string MpXAhuTLCZ;
      string JuSNTJlOZq;
      string kYdFhTSsBh;
      string FDzVIkqWSt;
      string JIlMCQuKSM;
      string SLfnBnLRRO;
      string caJTTFwxFh;
      string ROwegcmQDR;
      string YIZoOtXKTU;
      if(RPnYqnRBpa == LOYmVFZFem){ZYEDRiyRrw = true;}
      else if(LOYmVFZFem == RPnYqnRBpa){FgNsPHkuzn = true;}
      if(yEfgcdZgsz == MpXAhuTLCZ){TyFjtEPAGY = true;}
      else if(MpXAhuTLCZ == yEfgcdZgsz){HDAyeXCPWE = true;}
      if(KqIxeZBQRB == JuSNTJlOZq){BuOApUAUFZ = true;}
      else if(JuSNTJlOZq == KqIxeZBQRB){BmExSnsVru = true;}
      if(VeeDwhFQRc == kYdFhTSsBh){hkcjIsJrNy = true;}
      else if(kYdFhTSsBh == VeeDwhFQRc){VQOoJjwhfn = true;}
      if(eEdrelqJit == FDzVIkqWSt){dVXHxaCotJ = true;}
      else if(FDzVIkqWSt == eEdrelqJit){YlhbWeFekq = true;}
      if(NpVAtZGpsQ == JIlMCQuKSM){eXDuTeKENx = true;}
      else if(JIlMCQuKSM == NpVAtZGpsQ){xsinLRbQZa = true;}
      if(mBioFTZcju == SLfnBnLRRO){idLSOiUUbB = true;}
      else if(SLfnBnLRRO == mBioFTZcju){OOCESpnKou = true;}
      if(XIPPUGNQRs == caJTTFwxFh){tWlIueWHDP = true;}
      if(hqgXmfJeJV == ROwegcmQDR){RKauuJghPd = true;}
      if(aOWApdUnlL == YIZoOtXKTU){iFdQPAJFrN = true;}
      while(caJTTFwxFh == XIPPUGNQRs){bUjiePFcam = true;}
      while(ROwegcmQDR == ROwegcmQDR){iNkAxbhacr = true;}
      while(YIZoOtXKTU == YIZoOtXKTU){HfHEZJicJf = true;}
      if(ZYEDRiyRrw == true){ZYEDRiyRrw = false;}
      if(TyFjtEPAGY == true){TyFjtEPAGY = false;}
      if(BuOApUAUFZ == true){BuOApUAUFZ = false;}
      if(hkcjIsJrNy == true){hkcjIsJrNy = false;}
      if(dVXHxaCotJ == true){dVXHxaCotJ = false;}
      if(eXDuTeKENx == true){eXDuTeKENx = false;}
      if(idLSOiUUbB == true){idLSOiUUbB = false;}
      if(tWlIueWHDP == true){tWlIueWHDP = false;}
      if(RKauuJghPd == true){RKauuJghPd = false;}
      if(iFdQPAJFrN == true){iFdQPAJFrN = false;}
      if(FgNsPHkuzn == true){FgNsPHkuzn = false;}
      if(HDAyeXCPWE == true){HDAyeXCPWE = false;}
      if(BmExSnsVru == true){BmExSnsVru = false;}
      if(VQOoJjwhfn == true){VQOoJjwhfn = false;}
      if(YlhbWeFekq == true){YlhbWeFekq = false;}
      if(xsinLRbQZa == true){xsinLRbQZa = false;}
      if(OOCESpnKou == true){OOCESpnKou = false;}
      if(bUjiePFcam == true){bUjiePFcam = false;}
      if(iNkAxbhacr == true){iNkAxbhacr = false;}
      if(HfHEZJicJf == true){HfHEZJicJf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MOGTOZTPDW
{ 
  void MptwVnVxkw()
  { 
      bool MqjwxctYbC = false;
      bool UOdJsxXrYn = false;
      bool YYjHadzGKj = false;
      bool dRkbNekbLg = false;
      bool EFRQlbboFr = false;
      bool cCgfTnGcVS = false;
      bool dnNqXDcCuN = false;
      bool MugqjSGTUy = false;
      bool CJASGbjFHZ = false;
      bool XHGrDQrasi = false;
      bool yZtqfhVouB = false;
      bool hlHWQTmujw = false;
      bool SXtVpEnnmT = false;
      bool afalzbOJlY = false;
      bool FuJFqkzjbi = false;
      bool cwpxQaeYBb = false;
      bool shBbaCLVWn = false;
      bool FdJKpWNndE = false;
      bool FELEpdodVY = false;
      bool xpHKfXsheo = false;
      string ZGorxRnuSL;
      string CxKVAqFhwL;
      string zcYzcfGehN;
      string ssaBAmhZGh;
      string RfoRHaolEn;
      string RKFPGwgoOR;
      string KIMFSJWIVM;
      string IeaNtSnGrC;
      string pUasuhnKuE;
      string FrKoWITiyx;
      string DgPqfmiqUm;
      string HZxMaogSJk;
      string VMMQGQTlpl;
      string zEHtyJFiNI;
      string ywoHwetyNh;
      string aAZNbqTyjO;
      string SxBinDSDNQ;
      string jyFBlZWFUa;
      string VVYIKzetSG;
      string pGyypBuFTs;
      if(ZGorxRnuSL == DgPqfmiqUm){MqjwxctYbC = true;}
      else if(DgPqfmiqUm == ZGorxRnuSL){yZtqfhVouB = true;}
      if(CxKVAqFhwL == HZxMaogSJk){UOdJsxXrYn = true;}
      else if(HZxMaogSJk == CxKVAqFhwL){hlHWQTmujw = true;}
      if(zcYzcfGehN == VMMQGQTlpl){YYjHadzGKj = true;}
      else if(VMMQGQTlpl == zcYzcfGehN){SXtVpEnnmT = true;}
      if(ssaBAmhZGh == zEHtyJFiNI){dRkbNekbLg = true;}
      else if(zEHtyJFiNI == ssaBAmhZGh){afalzbOJlY = true;}
      if(RfoRHaolEn == ywoHwetyNh){EFRQlbboFr = true;}
      else if(ywoHwetyNh == RfoRHaolEn){FuJFqkzjbi = true;}
      if(RKFPGwgoOR == aAZNbqTyjO){cCgfTnGcVS = true;}
      else if(aAZNbqTyjO == RKFPGwgoOR){cwpxQaeYBb = true;}
      if(KIMFSJWIVM == SxBinDSDNQ){dnNqXDcCuN = true;}
      else if(SxBinDSDNQ == KIMFSJWIVM){shBbaCLVWn = true;}
      if(IeaNtSnGrC == jyFBlZWFUa){MugqjSGTUy = true;}
      if(pUasuhnKuE == VVYIKzetSG){CJASGbjFHZ = true;}
      if(FrKoWITiyx == pGyypBuFTs){XHGrDQrasi = true;}
      while(jyFBlZWFUa == IeaNtSnGrC){FdJKpWNndE = true;}
      while(VVYIKzetSG == VVYIKzetSG){FELEpdodVY = true;}
      while(pGyypBuFTs == pGyypBuFTs){xpHKfXsheo = true;}
      if(MqjwxctYbC == true){MqjwxctYbC = false;}
      if(UOdJsxXrYn == true){UOdJsxXrYn = false;}
      if(YYjHadzGKj == true){YYjHadzGKj = false;}
      if(dRkbNekbLg == true){dRkbNekbLg = false;}
      if(EFRQlbboFr == true){EFRQlbboFr = false;}
      if(cCgfTnGcVS == true){cCgfTnGcVS = false;}
      if(dnNqXDcCuN == true){dnNqXDcCuN = false;}
      if(MugqjSGTUy == true){MugqjSGTUy = false;}
      if(CJASGbjFHZ == true){CJASGbjFHZ = false;}
      if(XHGrDQrasi == true){XHGrDQrasi = false;}
      if(yZtqfhVouB == true){yZtqfhVouB = false;}
      if(hlHWQTmujw == true){hlHWQTmujw = false;}
      if(SXtVpEnnmT == true){SXtVpEnnmT = false;}
      if(afalzbOJlY == true){afalzbOJlY = false;}
      if(FuJFqkzjbi == true){FuJFqkzjbi = false;}
      if(cwpxQaeYBb == true){cwpxQaeYBb = false;}
      if(shBbaCLVWn == true){shBbaCLVWn = false;}
      if(FdJKpWNndE == true){FdJKpWNndE = false;}
      if(FELEpdodVY == true){FELEpdodVY = false;}
      if(xpHKfXsheo == true){xpHKfXsheo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KAPCCQLKEC
{ 
  void UxrXzafWCd()
  { 
      bool xjdjuAFpXz = false;
      bool LuAQLdkaIJ = false;
      bool adKQOlEeOq = false;
      bool AabPkkYSgi = false;
      bool gOYSexzwwC = false;
      bool mORINSZMUI = false;
      bool uabgzkSjfZ = false;
      bool ERsYbLFrkR = false;
      bool mIhLDkITBR = false;
      bool LMyXnGmrSt = false;
      bool dOQWyUUsfC = false;
      bool NhaDVmrPcN = false;
      bool byhNOqTUkV = false;
      bool XNYqmXrLNi = false;
      bool QPmzEdktCA = false;
      bool NXOFRffCIG = false;
      bool AzHKdAIjQx = false;
      bool ugBtwMKiJj = false;
      bool GYSjHAySYH = false;
      bool rpDHhRHcUD = false;
      string XBzwJuGUec;
      string hyZKcebbTz;
      string ASqnBlYIpn;
      string DtOWuqEqCp;
      string xzipKQDrqm;
      string FHoydEKLuW;
      string VxepZmjDOl;
      string ZjYcCBiAcj;
      string hgRCiwEPrp;
      string gsweUzUsQW;
      string gAcENVhLwc;
      string VJhKoofbHc;
      string hUKYFgnsID;
      string fpjGDhDMoM;
      string NsSPTWLkpf;
      string SrkmnMpEzg;
      string gnDrxfZbHG;
      string kSmtPoBuEh;
      string UDDbjmFwRp;
      string rzNIfYoaSn;
      if(XBzwJuGUec == gAcENVhLwc){xjdjuAFpXz = true;}
      else if(gAcENVhLwc == XBzwJuGUec){dOQWyUUsfC = true;}
      if(hyZKcebbTz == VJhKoofbHc){LuAQLdkaIJ = true;}
      else if(VJhKoofbHc == hyZKcebbTz){NhaDVmrPcN = true;}
      if(ASqnBlYIpn == hUKYFgnsID){adKQOlEeOq = true;}
      else if(hUKYFgnsID == ASqnBlYIpn){byhNOqTUkV = true;}
      if(DtOWuqEqCp == fpjGDhDMoM){AabPkkYSgi = true;}
      else if(fpjGDhDMoM == DtOWuqEqCp){XNYqmXrLNi = true;}
      if(xzipKQDrqm == NsSPTWLkpf){gOYSexzwwC = true;}
      else if(NsSPTWLkpf == xzipKQDrqm){QPmzEdktCA = true;}
      if(FHoydEKLuW == SrkmnMpEzg){mORINSZMUI = true;}
      else if(SrkmnMpEzg == FHoydEKLuW){NXOFRffCIG = true;}
      if(VxepZmjDOl == gnDrxfZbHG){uabgzkSjfZ = true;}
      else if(gnDrxfZbHG == VxepZmjDOl){AzHKdAIjQx = true;}
      if(ZjYcCBiAcj == kSmtPoBuEh){ERsYbLFrkR = true;}
      if(hgRCiwEPrp == UDDbjmFwRp){mIhLDkITBR = true;}
      if(gsweUzUsQW == rzNIfYoaSn){LMyXnGmrSt = true;}
      while(kSmtPoBuEh == ZjYcCBiAcj){ugBtwMKiJj = true;}
      while(UDDbjmFwRp == UDDbjmFwRp){GYSjHAySYH = true;}
      while(rzNIfYoaSn == rzNIfYoaSn){rpDHhRHcUD = true;}
      if(xjdjuAFpXz == true){xjdjuAFpXz = false;}
      if(LuAQLdkaIJ == true){LuAQLdkaIJ = false;}
      if(adKQOlEeOq == true){adKQOlEeOq = false;}
      if(AabPkkYSgi == true){AabPkkYSgi = false;}
      if(gOYSexzwwC == true){gOYSexzwwC = false;}
      if(mORINSZMUI == true){mORINSZMUI = false;}
      if(uabgzkSjfZ == true){uabgzkSjfZ = false;}
      if(ERsYbLFrkR == true){ERsYbLFrkR = false;}
      if(mIhLDkITBR == true){mIhLDkITBR = false;}
      if(LMyXnGmrSt == true){LMyXnGmrSt = false;}
      if(dOQWyUUsfC == true){dOQWyUUsfC = false;}
      if(NhaDVmrPcN == true){NhaDVmrPcN = false;}
      if(byhNOqTUkV == true){byhNOqTUkV = false;}
      if(XNYqmXrLNi == true){XNYqmXrLNi = false;}
      if(QPmzEdktCA == true){QPmzEdktCA = false;}
      if(NXOFRffCIG == true){NXOFRffCIG = false;}
      if(AzHKdAIjQx == true){AzHKdAIjQx = false;}
      if(ugBtwMKiJj == true){ugBtwMKiJj = false;}
      if(GYSjHAySYH == true){GYSjHAySYH = false;}
      if(rpDHhRHcUD == true){rpDHhRHcUD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJURXUHXDD
{ 
  void LlGziZmuTS()
  { 
      bool FraPeLYQwt = false;
      bool HIWZuIFPOI = false;
      bool wFRPGcqgEe = false;
      bool JTIKgYIjEp = false;
      bool qURYKWDByw = false;
      bool hmeZWzZLIB = false;
      bool TqLRjnzMrV = false;
      bool zULXQamrFj = false;
      bool ZoiIwVohmg = false;
      bool yxaDWAJAoV = false;
      bool WqIbwMbGJu = false;
      bool MhGYbdIDUN = false;
      bool yRYLWCtIBQ = false;
      bool RmDiMhgGLj = false;
      bool tiYrUQqBbr = false;
      bool qFeaXFSxFt = false;
      bool STFsdZeWMs = false;
      bool xCrkTPsgqG = false;
      bool LrgJYLHbLH = false;
      bool OiAQRZceNt = false;
      string rfVKTMiAad;
      string HJfHzkFdqZ;
      string ZHhKHZUPFo;
      string VVbifSBhLI;
      string FcRgKZwKEq;
      string IXBSljxLCt;
      string rSulHlgwbg;
      string jXRiTxpBzg;
      string dKLNgyUJxu;
      string UoeQQlgeYY;
      string szhXHjFRyo;
      string swMVPgHgFJ;
      string QXzfLtrASg;
      string PLcanecnGw;
      string rDKHCYcIBi;
      string ezZOHUzBMM;
      string qEzQYhTkhk;
      string ESaJRNNqdl;
      string RiziCQkOTS;
      string eabsEmDsiT;
      if(rfVKTMiAad == szhXHjFRyo){FraPeLYQwt = true;}
      else if(szhXHjFRyo == rfVKTMiAad){WqIbwMbGJu = true;}
      if(HJfHzkFdqZ == swMVPgHgFJ){HIWZuIFPOI = true;}
      else if(swMVPgHgFJ == HJfHzkFdqZ){MhGYbdIDUN = true;}
      if(ZHhKHZUPFo == QXzfLtrASg){wFRPGcqgEe = true;}
      else if(QXzfLtrASg == ZHhKHZUPFo){yRYLWCtIBQ = true;}
      if(VVbifSBhLI == PLcanecnGw){JTIKgYIjEp = true;}
      else if(PLcanecnGw == VVbifSBhLI){RmDiMhgGLj = true;}
      if(FcRgKZwKEq == rDKHCYcIBi){qURYKWDByw = true;}
      else if(rDKHCYcIBi == FcRgKZwKEq){tiYrUQqBbr = true;}
      if(IXBSljxLCt == ezZOHUzBMM){hmeZWzZLIB = true;}
      else if(ezZOHUzBMM == IXBSljxLCt){qFeaXFSxFt = true;}
      if(rSulHlgwbg == qEzQYhTkhk){TqLRjnzMrV = true;}
      else if(qEzQYhTkhk == rSulHlgwbg){STFsdZeWMs = true;}
      if(jXRiTxpBzg == ESaJRNNqdl){zULXQamrFj = true;}
      if(dKLNgyUJxu == RiziCQkOTS){ZoiIwVohmg = true;}
      if(UoeQQlgeYY == eabsEmDsiT){yxaDWAJAoV = true;}
      while(ESaJRNNqdl == jXRiTxpBzg){xCrkTPsgqG = true;}
      while(RiziCQkOTS == RiziCQkOTS){LrgJYLHbLH = true;}
      while(eabsEmDsiT == eabsEmDsiT){OiAQRZceNt = true;}
      if(FraPeLYQwt == true){FraPeLYQwt = false;}
      if(HIWZuIFPOI == true){HIWZuIFPOI = false;}
      if(wFRPGcqgEe == true){wFRPGcqgEe = false;}
      if(JTIKgYIjEp == true){JTIKgYIjEp = false;}
      if(qURYKWDByw == true){qURYKWDByw = false;}
      if(hmeZWzZLIB == true){hmeZWzZLIB = false;}
      if(TqLRjnzMrV == true){TqLRjnzMrV = false;}
      if(zULXQamrFj == true){zULXQamrFj = false;}
      if(ZoiIwVohmg == true){ZoiIwVohmg = false;}
      if(yxaDWAJAoV == true){yxaDWAJAoV = false;}
      if(WqIbwMbGJu == true){WqIbwMbGJu = false;}
      if(MhGYbdIDUN == true){MhGYbdIDUN = false;}
      if(yRYLWCtIBQ == true){yRYLWCtIBQ = false;}
      if(RmDiMhgGLj == true){RmDiMhgGLj = false;}
      if(tiYrUQqBbr == true){tiYrUQqBbr = false;}
      if(qFeaXFSxFt == true){qFeaXFSxFt = false;}
      if(STFsdZeWMs == true){STFsdZeWMs = false;}
      if(xCrkTPsgqG == true){xCrkTPsgqG = false;}
      if(LrgJYLHbLH == true){LrgJYLHbLH = false;}
      if(OiAQRZceNt == true){OiAQRZceNt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NNJHFPJVDH
{ 
  void MhRSWSfdFP()
  { 
      bool iWpgNVwxUB = false;
      bool ylBkDeISAU = false;
      bool VfSjFbwlyD = false;
      bool HLEcOsDuRb = false;
      bool CEsANMMNPp = false;
      bool fJlUpCEFak = false;
      bool YKyRsmhXWJ = false;
      bool aMAYRRlSVs = false;
      bool PhVIWyZimL = false;
      bool oyTgCrFbHa = false;
      bool dnqGOSIMCY = false;
      bool QlihVqnptt = false;
      bool MzkKUcsTWZ = false;
      bool LKLuOapPsE = false;
      bool oMfOuCOlKK = false;
      bool DPgMNeDgkk = false;
      bool ZopbMGanSu = false;
      bool AXwpFzSVPR = false;
      bool OGILWwcygj = false;
      bool WJdIeAWEBn = false;
      string irnKWCzDAn;
      string tEMRztaBwb;
      string ptSzJYmcxk;
      string CZVjQYnxSN;
      string RyuOQQKRjh;
      string jfQXJoZoBx;
      string PWGPlTicAZ;
      string GcihKqyDis;
      string NUrOBVJyZa;
      string zyuUyurfcw;
      string hhQJbGxhMR;
      string qVGIjtdqOP;
      string KjCZaIgNjO;
      string zSalKeEhmt;
      string XakIjcqmkD;
      string RAQMkxfpiT;
      string YjyySXtTxE;
      string puETqjysox;
      string QsbfxyBOBM;
      string yNzSVnbmoM;
      if(irnKWCzDAn == hhQJbGxhMR){iWpgNVwxUB = true;}
      else if(hhQJbGxhMR == irnKWCzDAn){dnqGOSIMCY = true;}
      if(tEMRztaBwb == qVGIjtdqOP){ylBkDeISAU = true;}
      else if(qVGIjtdqOP == tEMRztaBwb){QlihVqnptt = true;}
      if(ptSzJYmcxk == KjCZaIgNjO){VfSjFbwlyD = true;}
      else if(KjCZaIgNjO == ptSzJYmcxk){MzkKUcsTWZ = true;}
      if(CZVjQYnxSN == zSalKeEhmt){HLEcOsDuRb = true;}
      else if(zSalKeEhmt == CZVjQYnxSN){LKLuOapPsE = true;}
      if(RyuOQQKRjh == XakIjcqmkD){CEsANMMNPp = true;}
      else if(XakIjcqmkD == RyuOQQKRjh){oMfOuCOlKK = true;}
      if(jfQXJoZoBx == RAQMkxfpiT){fJlUpCEFak = true;}
      else if(RAQMkxfpiT == jfQXJoZoBx){DPgMNeDgkk = true;}
      if(PWGPlTicAZ == YjyySXtTxE){YKyRsmhXWJ = true;}
      else if(YjyySXtTxE == PWGPlTicAZ){ZopbMGanSu = true;}
      if(GcihKqyDis == puETqjysox){aMAYRRlSVs = true;}
      if(NUrOBVJyZa == QsbfxyBOBM){PhVIWyZimL = true;}
      if(zyuUyurfcw == yNzSVnbmoM){oyTgCrFbHa = true;}
      while(puETqjysox == GcihKqyDis){AXwpFzSVPR = true;}
      while(QsbfxyBOBM == QsbfxyBOBM){OGILWwcygj = true;}
      while(yNzSVnbmoM == yNzSVnbmoM){WJdIeAWEBn = true;}
      if(iWpgNVwxUB == true){iWpgNVwxUB = false;}
      if(ylBkDeISAU == true){ylBkDeISAU = false;}
      if(VfSjFbwlyD == true){VfSjFbwlyD = false;}
      if(HLEcOsDuRb == true){HLEcOsDuRb = false;}
      if(CEsANMMNPp == true){CEsANMMNPp = false;}
      if(fJlUpCEFak == true){fJlUpCEFak = false;}
      if(YKyRsmhXWJ == true){YKyRsmhXWJ = false;}
      if(aMAYRRlSVs == true){aMAYRRlSVs = false;}
      if(PhVIWyZimL == true){PhVIWyZimL = false;}
      if(oyTgCrFbHa == true){oyTgCrFbHa = false;}
      if(dnqGOSIMCY == true){dnqGOSIMCY = false;}
      if(QlihVqnptt == true){QlihVqnptt = false;}
      if(MzkKUcsTWZ == true){MzkKUcsTWZ = false;}
      if(LKLuOapPsE == true){LKLuOapPsE = false;}
      if(oMfOuCOlKK == true){oMfOuCOlKK = false;}
      if(DPgMNeDgkk == true){DPgMNeDgkk = false;}
      if(ZopbMGanSu == true){ZopbMGanSu = false;}
      if(AXwpFzSVPR == true){AXwpFzSVPR = false;}
      if(OGILWwcygj == true){OGILWwcygj = false;}
      if(WJdIeAWEBn == true){WJdIeAWEBn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VNRMSENQMT
{ 
  void UhJptiVKLc()
  { 
      bool YXSsLJaWXC = false;
      bool dPBiMYOJfl = false;
      bool GnjxOpOSrD = false;
      bool EswUVnerBs = false;
      bool GkfufuRUNy = false;
      bool SzaKFknUdU = false;
      bool uHeUyjSfNY = false;
      bool sVIlfUInRS = false;
      bool YtFtkFRlOk = false;
      bool zKOfyyGLxu = false;
      bool blHnEwqnej = false;
      bool bACLwACkis = false;
      bool SgQcYiHbng = false;
      bool OxpVplmQoo = false;
      bool OcGeIzHCiy = false;
      bool uVbEcuUdPV = false;
      bool nOAxVeJgUJ = false;
      bool NlutdoalUY = false;
      bool aEsplsUlsu = false;
      bool RIBTAzcJIc = false;
      string oRgqdjYqhP;
      string pkPhDtYJEM;
      string NnWMjyeAGg;
      string JKiUmSXdrm;
      string CyxhnYMlbN;
      string qWXajBuUHf;
      string FYkAFeBtuk;
      string VuRRJOqoXL;
      string lsYrpmlIkl;
      string XDVMhcNwbJ;
      string WRqprwFGQU;
      string JFwwsLAsJS;
      string srJIMSYEif;
      string BtMOnTBhzt;
      string hfrPbRGZSV;
      string cTlIPdIhdY;
      string WAWjTPrhHZ;
      string JSsPkNAsgt;
      string MylNDgIEyJ;
      string KTDZWgIHwM;
      if(oRgqdjYqhP == WRqprwFGQU){YXSsLJaWXC = true;}
      else if(WRqprwFGQU == oRgqdjYqhP){blHnEwqnej = true;}
      if(pkPhDtYJEM == JFwwsLAsJS){dPBiMYOJfl = true;}
      else if(JFwwsLAsJS == pkPhDtYJEM){bACLwACkis = true;}
      if(NnWMjyeAGg == srJIMSYEif){GnjxOpOSrD = true;}
      else if(srJIMSYEif == NnWMjyeAGg){SgQcYiHbng = true;}
      if(JKiUmSXdrm == BtMOnTBhzt){EswUVnerBs = true;}
      else if(BtMOnTBhzt == JKiUmSXdrm){OxpVplmQoo = true;}
      if(CyxhnYMlbN == hfrPbRGZSV){GkfufuRUNy = true;}
      else if(hfrPbRGZSV == CyxhnYMlbN){OcGeIzHCiy = true;}
      if(qWXajBuUHf == cTlIPdIhdY){SzaKFknUdU = true;}
      else if(cTlIPdIhdY == qWXajBuUHf){uVbEcuUdPV = true;}
      if(FYkAFeBtuk == WAWjTPrhHZ){uHeUyjSfNY = true;}
      else if(WAWjTPrhHZ == FYkAFeBtuk){nOAxVeJgUJ = true;}
      if(VuRRJOqoXL == JSsPkNAsgt){sVIlfUInRS = true;}
      if(lsYrpmlIkl == MylNDgIEyJ){YtFtkFRlOk = true;}
      if(XDVMhcNwbJ == KTDZWgIHwM){zKOfyyGLxu = true;}
      while(JSsPkNAsgt == VuRRJOqoXL){NlutdoalUY = true;}
      while(MylNDgIEyJ == MylNDgIEyJ){aEsplsUlsu = true;}
      while(KTDZWgIHwM == KTDZWgIHwM){RIBTAzcJIc = true;}
      if(YXSsLJaWXC == true){YXSsLJaWXC = false;}
      if(dPBiMYOJfl == true){dPBiMYOJfl = false;}
      if(GnjxOpOSrD == true){GnjxOpOSrD = false;}
      if(EswUVnerBs == true){EswUVnerBs = false;}
      if(GkfufuRUNy == true){GkfufuRUNy = false;}
      if(SzaKFknUdU == true){SzaKFknUdU = false;}
      if(uHeUyjSfNY == true){uHeUyjSfNY = false;}
      if(sVIlfUInRS == true){sVIlfUInRS = false;}
      if(YtFtkFRlOk == true){YtFtkFRlOk = false;}
      if(zKOfyyGLxu == true){zKOfyyGLxu = false;}
      if(blHnEwqnej == true){blHnEwqnej = false;}
      if(bACLwACkis == true){bACLwACkis = false;}
      if(SgQcYiHbng == true){SgQcYiHbng = false;}
      if(OxpVplmQoo == true){OxpVplmQoo = false;}
      if(OcGeIzHCiy == true){OcGeIzHCiy = false;}
      if(uVbEcuUdPV == true){uVbEcuUdPV = false;}
      if(nOAxVeJgUJ == true){nOAxVeJgUJ = false;}
      if(NlutdoalUY == true){NlutdoalUY = false;}
      if(aEsplsUlsu == true){aEsplsUlsu = false;}
      if(RIBTAzcJIc == true){RIBTAzcJIc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AFVMVDILMA
{ 
  void iKfJbYTUXc()
  { 
      bool jiKmbmbLJT = false;
      bool zNJzGItdDe = false;
      bool XYMfbidcGq = false;
      bool qiduCtJubz = false;
      bool hTtLRJJdsB = false;
      bool KuSbAKVeLs = false;
      bool IzFSbQjNxM = false;
      bool zyCEwEdBNR = false;
      bool YziEfwPCuq = false;
      bool YejhpiNbiB = false;
      bool ZwggBLrOew = false;
      bool gUQsTIPAlf = false;
      bool AgSFmTOTNN = false;
      bool pBRMrcSCCT = false;
      bool DBXzKEOqOh = false;
      bool SNoCAsdash = false;
      bool xXARFeCDAp = false;
      bool pMxSczJTui = false;
      bool FXEftcLOLz = false;
      bool zqJUWeAFse = false;
      string IZDhisVeAW;
      string yLILoAtQKx;
      string ZNpZUKYsxD;
      string MBIeflMpix;
      string wxbtDZIEoa;
      string KfcYfujdNY;
      string TbhwKwCdfC;
      string mEgMBcluVt;
      string BUDWsfXjyj;
      string CibKdTOejH;
      string XeYmmFyQWD;
      string JoHTWyYKDd;
      string XSfuAEcVig;
      string NGKOWWwQim;
      string gHMuaNaIme;
      string uDbGiEycli;
      string cbhpoCdrxA;
      string CIbPwPFjTl;
      string cUhDlJeEeR;
      string XSdzJEYWGX;
      if(IZDhisVeAW == XeYmmFyQWD){jiKmbmbLJT = true;}
      else if(XeYmmFyQWD == IZDhisVeAW){ZwggBLrOew = true;}
      if(yLILoAtQKx == JoHTWyYKDd){zNJzGItdDe = true;}
      else if(JoHTWyYKDd == yLILoAtQKx){gUQsTIPAlf = true;}
      if(ZNpZUKYsxD == XSfuAEcVig){XYMfbidcGq = true;}
      else if(XSfuAEcVig == ZNpZUKYsxD){AgSFmTOTNN = true;}
      if(MBIeflMpix == NGKOWWwQim){qiduCtJubz = true;}
      else if(NGKOWWwQim == MBIeflMpix){pBRMrcSCCT = true;}
      if(wxbtDZIEoa == gHMuaNaIme){hTtLRJJdsB = true;}
      else if(gHMuaNaIme == wxbtDZIEoa){DBXzKEOqOh = true;}
      if(KfcYfujdNY == uDbGiEycli){KuSbAKVeLs = true;}
      else if(uDbGiEycli == KfcYfujdNY){SNoCAsdash = true;}
      if(TbhwKwCdfC == cbhpoCdrxA){IzFSbQjNxM = true;}
      else if(cbhpoCdrxA == TbhwKwCdfC){xXARFeCDAp = true;}
      if(mEgMBcluVt == CIbPwPFjTl){zyCEwEdBNR = true;}
      if(BUDWsfXjyj == cUhDlJeEeR){YziEfwPCuq = true;}
      if(CibKdTOejH == XSdzJEYWGX){YejhpiNbiB = true;}
      while(CIbPwPFjTl == mEgMBcluVt){pMxSczJTui = true;}
      while(cUhDlJeEeR == cUhDlJeEeR){FXEftcLOLz = true;}
      while(XSdzJEYWGX == XSdzJEYWGX){zqJUWeAFse = true;}
      if(jiKmbmbLJT == true){jiKmbmbLJT = false;}
      if(zNJzGItdDe == true){zNJzGItdDe = false;}
      if(XYMfbidcGq == true){XYMfbidcGq = false;}
      if(qiduCtJubz == true){qiduCtJubz = false;}
      if(hTtLRJJdsB == true){hTtLRJJdsB = false;}
      if(KuSbAKVeLs == true){KuSbAKVeLs = false;}
      if(IzFSbQjNxM == true){IzFSbQjNxM = false;}
      if(zyCEwEdBNR == true){zyCEwEdBNR = false;}
      if(YziEfwPCuq == true){YziEfwPCuq = false;}
      if(YejhpiNbiB == true){YejhpiNbiB = false;}
      if(ZwggBLrOew == true){ZwggBLrOew = false;}
      if(gUQsTIPAlf == true){gUQsTIPAlf = false;}
      if(AgSFmTOTNN == true){AgSFmTOTNN = false;}
      if(pBRMrcSCCT == true){pBRMrcSCCT = false;}
      if(DBXzKEOqOh == true){DBXzKEOqOh = false;}
      if(SNoCAsdash == true){SNoCAsdash = false;}
      if(xXARFeCDAp == true){xXARFeCDAp = false;}
      if(pMxSczJTui == true){pMxSczJTui = false;}
      if(FXEftcLOLz == true){FXEftcLOLz = false;}
      if(zqJUWeAFse == true){zqJUWeAFse = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GNTMKLKSRT
{ 
  void qAgQsaBVyr()
  { 
      bool KXIdJiJepJ = false;
      bool mKoGqawpoG = false;
      bool DRTBXPSFtq = false;
      bool idMzcKfCKW = false;
      bool TzqdLCxjHZ = false;
      bool GZnXgsEHGt = false;
      bool PEkzaIxpdf = false;
      bool usfSmEZooU = false;
      bool SixTjIpnRi = false;
      bool FYuPGONqDD = false;
      bool FGGbeNsUkb = false;
      bool SPRlbgGQOR = false;
      bool SIXtZVxPMX = false;
      bool phllOLcVnW = false;
      bool PUDoPpGJnZ = false;
      bool IxckkwhLBI = false;
      bool PcINljdfWP = false;
      bool EkbrCxFhdj = false;
      bool PnamPsFAAS = false;
      bool cQUfHlMoDf = false;
      string FWuWHYZnhW;
      string KGGtBSUBgI;
      string SYYKEhXxyq;
      string pQEGlaUVoa;
      string SgfsdfJjSl;
      string MkxjNfykSY;
      string BboqftCzIZ;
      string yzLFpksffX;
      string YmeMdFTTrF;
      string cjCPZprnMi;
      string dJbrnMYqtc;
      string mSEtANxcNa;
      string ahHCxNxwfz;
      string rESwtPLlYR;
      string fbYPSJeIPL;
      string sOakIuCYtZ;
      string PcLujhzHzk;
      string BKEutzIqjm;
      string hngUFddhny;
      string NlqzBDQdek;
      if(FWuWHYZnhW == dJbrnMYqtc){KXIdJiJepJ = true;}
      else if(dJbrnMYqtc == FWuWHYZnhW){FGGbeNsUkb = true;}
      if(KGGtBSUBgI == mSEtANxcNa){mKoGqawpoG = true;}
      else if(mSEtANxcNa == KGGtBSUBgI){SPRlbgGQOR = true;}
      if(SYYKEhXxyq == ahHCxNxwfz){DRTBXPSFtq = true;}
      else if(ahHCxNxwfz == SYYKEhXxyq){SIXtZVxPMX = true;}
      if(pQEGlaUVoa == rESwtPLlYR){idMzcKfCKW = true;}
      else if(rESwtPLlYR == pQEGlaUVoa){phllOLcVnW = true;}
      if(SgfsdfJjSl == fbYPSJeIPL){TzqdLCxjHZ = true;}
      else if(fbYPSJeIPL == SgfsdfJjSl){PUDoPpGJnZ = true;}
      if(MkxjNfykSY == sOakIuCYtZ){GZnXgsEHGt = true;}
      else if(sOakIuCYtZ == MkxjNfykSY){IxckkwhLBI = true;}
      if(BboqftCzIZ == PcLujhzHzk){PEkzaIxpdf = true;}
      else if(PcLujhzHzk == BboqftCzIZ){PcINljdfWP = true;}
      if(yzLFpksffX == BKEutzIqjm){usfSmEZooU = true;}
      if(YmeMdFTTrF == hngUFddhny){SixTjIpnRi = true;}
      if(cjCPZprnMi == NlqzBDQdek){FYuPGONqDD = true;}
      while(BKEutzIqjm == yzLFpksffX){EkbrCxFhdj = true;}
      while(hngUFddhny == hngUFddhny){PnamPsFAAS = true;}
      while(NlqzBDQdek == NlqzBDQdek){cQUfHlMoDf = true;}
      if(KXIdJiJepJ == true){KXIdJiJepJ = false;}
      if(mKoGqawpoG == true){mKoGqawpoG = false;}
      if(DRTBXPSFtq == true){DRTBXPSFtq = false;}
      if(idMzcKfCKW == true){idMzcKfCKW = false;}
      if(TzqdLCxjHZ == true){TzqdLCxjHZ = false;}
      if(GZnXgsEHGt == true){GZnXgsEHGt = false;}
      if(PEkzaIxpdf == true){PEkzaIxpdf = false;}
      if(usfSmEZooU == true){usfSmEZooU = false;}
      if(SixTjIpnRi == true){SixTjIpnRi = false;}
      if(FYuPGONqDD == true){FYuPGONqDD = false;}
      if(FGGbeNsUkb == true){FGGbeNsUkb = false;}
      if(SPRlbgGQOR == true){SPRlbgGQOR = false;}
      if(SIXtZVxPMX == true){SIXtZVxPMX = false;}
      if(phllOLcVnW == true){phllOLcVnW = false;}
      if(PUDoPpGJnZ == true){PUDoPpGJnZ = false;}
      if(IxckkwhLBI == true){IxckkwhLBI = false;}
      if(PcINljdfWP == true){PcINljdfWP = false;}
      if(EkbrCxFhdj == true){EkbrCxFhdj = false;}
      if(PnamPsFAAS == true){PnamPsFAAS = false;}
      if(cQUfHlMoDf == true){cQUfHlMoDf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XGGETXRXVU
{ 
  void WmpLGYiqgT()
  { 
      bool wAbTLkbjhh = false;
      bool yYsKVchndR = false;
      bool qiTTyKmqDN = false;
      bool dLbOXJVwgz = false;
      bool BKrItEhriY = false;
      bool dlaJhMfHUA = false;
      bool xkgTEmxdmM = false;
      bool HkHePgqLYt = false;
      bool btHdiqjRfK = false;
      bool cNafCQcXEH = false;
      bool HDFVRrewsB = false;
      bool VUiaXCcDkM = false;
      bool CexbitKbbz = false;
      bool DSGQmYokMq = false;
      bool MnYeoIdAHz = false;
      bool mZmrEcFdlW = false;
      bool hDTsyDORnz = false;
      bool NqqsAOFSma = false;
      bool PJTcLdeOMJ = false;
      bool SLzoJITfgk = false;
      string ycparskUYO;
      string WVVFkpnCIh;
      string ZNNVtFIUFz;
      string NfmZUMUrPb;
      string STApqiyReU;
      string IuCqEkOTgm;
      string kQPZAphwjX;
      string UwmfPGMXeK;
      string GpojpRdwVj;
      string xAKbqCDapA;
      string BChGzMIVby;
      string XqoVgtafji;
      string MkZAaUkKoM;
      string ClgdJEIijd;
      string JHUXLGLnuw;
      string bXpHmPbgee;
      string axgOwlJKMb;
      string kquGYFQCnU;
      string JxPrjduZqs;
      string caDECLaFaZ;
      if(ycparskUYO == BChGzMIVby){wAbTLkbjhh = true;}
      else if(BChGzMIVby == ycparskUYO){HDFVRrewsB = true;}
      if(WVVFkpnCIh == XqoVgtafji){yYsKVchndR = true;}
      else if(XqoVgtafji == WVVFkpnCIh){VUiaXCcDkM = true;}
      if(ZNNVtFIUFz == MkZAaUkKoM){qiTTyKmqDN = true;}
      else if(MkZAaUkKoM == ZNNVtFIUFz){CexbitKbbz = true;}
      if(NfmZUMUrPb == ClgdJEIijd){dLbOXJVwgz = true;}
      else if(ClgdJEIijd == NfmZUMUrPb){DSGQmYokMq = true;}
      if(STApqiyReU == JHUXLGLnuw){BKrItEhriY = true;}
      else if(JHUXLGLnuw == STApqiyReU){MnYeoIdAHz = true;}
      if(IuCqEkOTgm == bXpHmPbgee){dlaJhMfHUA = true;}
      else if(bXpHmPbgee == IuCqEkOTgm){mZmrEcFdlW = true;}
      if(kQPZAphwjX == axgOwlJKMb){xkgTEmxdmM = true;}
      else if(axgOwlJKMb == kQPZAphwjX){hDTsyDORnz = true;}
      if(UwmfPGMXeK == kquGYFQCnU){HkHePgqLYt = true;}
      if(GpojpRdwVj == JxPrjduZqs){btHdiqjRfK = true;}
      if(xAKbqCDapA == caDECLaFaZ){cNafCQcXEH = true;}
      while(kquGYFQCnU == UwmfPGMXeK){NqqsAOFSma = true;}
      while(JxPrjduZqs == JxPrjduZqs){PJTcLdeOMJ = true;}
      while(caDECLaFaZ == caDECLaFaZ){SLzoJITfgk = true;}
      if(wAbTLkbjhh == true){wAbTLkbjhh = false;}
      if(yYsKVchndR == true){yYsKVchndR = false;}
      if(qiTTyKmqDN == true){qiTTyKmqDN = false;}
      if(dLbOXJVwgz == true){dLbOXJVwgz = false;}
      if(BKrItEhriY == true){BKrItEhriY = false;}
      if(dlaJhMfHUA == true){dlaJhMfHUA = false;}
      if(xkgTEmxdmM == true){xkgTEmxdmM = false;}
      if(HkHePgqLYt == true){HkHePgqLYt = false;}
      if(btHdiqjRfK == true){btHdiqjRfK = false;}
      if(cNafCQcXEH == true){cNafCQcXEH = false;}
      if(HDFVRrewsB == true){HDFVRrewsB = false;}
      if(VUiaXCcDkM == true){VUiaXCcDkM = false;}
      if(CexbitKbbz == true){CexbitKbbz = false;}
      if(DSGQmYokMq == true){DSGQmYokMq = false;}
      if(MnYeoIdAHz == true){MnYeoIdAHz = false;}
      if(mZmrEcFdlW == true){mZmrEcFdlW = false;}
      if(hDTsyDORnz == true){hDTsyDORnz = false;}
      if(NqqsAOFSma == true){NqqsAOFSma = false;}
      if(PJTcLdeOMJ == true){PJTcLdeOMJ = false;}
      if(SLzoJITfgk == true){SLzoJITfgk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LASYYBZWTU
{ 
  void hOLPSSTdfz()
  { 
      bool kGbKfrnPRY = false;
      bool tWFiBqeBhJ = false;
      bool iqqFJZddaz = false;
      bool icEGaogeKT = false;
      bool VRkWZwegVJ = false;
      bool VoVQntOWBG = false;
      bool OKnSpRRyHL = false;
      bool KApNnRGTfN = false;
      bool uxHQctHnRf = false;
      bool ZJdEFLcRgH = false;
      bool dfYJzVyHcW = false;
      bool ntpnLQDXpu = false;
      bool JdfblAVlIb = false;
      bool nnmXiPYxRG = false;
      bool wALuqeTprn = false;
      bool IFalyAzwXz = false;
      bool zMyAhAHSEw = false;
      bool rFGizJRkkH = false;
      bool ffsTThMBZi = false;
      bool PbZRHiBLNq = false;
      string dYVrJHYgoe;
      string GpjDKjTqNd;
      string rxxhYPMXIB;
      string jlVtIWRndM;
      string qhGkcZStZD;
      string pNbedfbnSs;
      string tBYnuTUptm;
      string SfNAmJqLEz;
      string wSxELWKpPc;
      string ucUjSoJSpI;
      string EbAmkKzarU;
      string oPiTwbDTbX;
      string JdZRroKdhx;
      string AXVutUSKSA;
      string WiyunftBmp;
      string kopSzaBhuw;
      string AVstUQtmYb;
      string JsAaAZfecM;
      string uIpqLKgCwT;
      string SjPWABpDaW;
      if(dYVrJHYgoe == EbAmkKzarU){kGbKfrnPRY = true;}
      else if(EbAmkKzarU == dYVrJHYgoe){dfYJzVyHcW = true;}
      if(GpjDKjTqNd == oPiTwbDTbX){tWFiBqeBhJ = true;}
      else if(oPiTwbDTbX == GpjDKjTqNd){ntpnLQDXpu = true;}
      if(rxxhYPMXIB == JdZRroKdhx){iqqFJZddaz = true;}
      else if(JdZRroKdhx == rxxhYPMXIB){JdfblAVlIb = true;}
      if(jlVtIWRndM == AXVutUSKSA){icEGaogeKT = true;}
      else if(AXVutUSKSA == jlVtIWRndM){nnmXiPYxRG = true;}
      if(qhGkcZStZD == WiyunftBmp){VRkWZwegVJ = true;}
      else if(WiyunftBmp == qhGkcZStZD){wALuqeTprn = true;}
      if(pNbedfbnSs == kopSzaBhuw){VoVQntOWBG = true;}
      else if(kopSzaBhuw == pNbedfbnSs){IFalyAzwXz = true;}
      if(tBYnuTUptm == AVstUQtmYb){OKnSpRRyHL = true;}
      else if(AVstUQtmYb == tBYnuTUptm){zMyAhAHSEw = true;}
      if(SfNAmJqLEz == JsAaAZfecM){KApNnRGTfN = true;}
      if(wSxELWKpPc == uIpqLKgCwT){uxHQctHnRf = true;}
      if(ucUjSoJSpI == SjPWABpDaW){ZJdEFLcRgH = true;}
      while(JsAaAZfecM == SfNAmJqLEz){rFGizJRkkH = true;}
      while(uIpqLKgCwT == uIpqLKgCwT){ffsTThMBZi = true;}
      while(SjPWABpDaW == SjPWABpDaW){PbZRHiBLNq = true;}
      if(kGbKfrnPRY == true){kGbKfrnPRY = false;}
      if(tWFiBqeBhJ == true){tWFiBqeBhJ = false;}
      if(iqqFJZddaz == true){iqqFJZddaz = false;}
      if(icEGaogeKT == true){icEGaogeKT = false;}
      if(VRkWZwegVJ == true){VRkWZwegVJ = false;}
      if(VoVQntOWBG == true){VoVQntOWBG = false;}
      if(OKnSpRRyHL == true){OKnSpRRyHL = false;}
      if(KApNnRGTfN == true){KApNnRGTfN = false;}
      if(uxHQctHnRf == true){uxHQctHnRf = false;}
      if(ZJdEFLcRgH == true){ZJdEFLcRgH = false;}
      if(dfYJzVyHcW == true){dfYJzVyHcW = false;}
      if(ntpnLQDXpu == true){ntpnLQDXpu = false;}
      if(JdfblAVlIb == true){JdfblAVlIb = false;}
      if(nnmXiPYxRG == true){nnmXiPYxRG = false;}
      if(wALuqeTprn == true){wALuqeTprn = false;}
      if(IFalyAzwXz == true){IFalyAzwXz = false;}
      if(zMyAhAHSEw == true){zMyAhAHSEw = false;}
      if(rFGizJRkkH == true){rFGizJRkkH = false;}
      if(ffsTThMBZi == true){ffsTThMBZi = false;}
      if(PbZRHiBLNq == true){PbZRHiBLNq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDIRIITCXG
{ 
  void jtQnnFluPu()
  { 
      bool tbPjIMqrLR = false;
      bool UMZkLagtEQ = false;
      bool ADpFaVDYhQ = false;
      bool ongUWOiGhX = false;
      bool WQOPLGbNFJ = false;
      bool YdNeQplKIl = false;
      bool IRKucffENw = false;
      bool qZMfsinZsU = false;
      bool toSXqKaCEf = false;
      bool cYyuOFGTme = false;
      bool aWAJRzQgkh = false;
      bool BMQmqSymDS = false;
      bool FczgSSbRQn = false;
      bool cUlOtXoJGr = false;
      bool ssQWeQIKDu = false;
      bool GSPTYxWSpz = false;
      bool WzQxEgZBsT = false;
      bool dnfLYMMcCC = false;
      bool KQNUhJFRpx = false;
      bool AVSHUsbSRx = false;
      string wUMnRGgHQk;
      string DTOOrTezfi;
      string xIqIxGhkkE;
      string QOIKtppktp;
      string OMAArAAtsX;
      string TwxKKndDpL;
      string YuWMToLEUC;
      string dtEoTkIpQx;
      string FmrNjURxAG;
      string MltiRTpmgC;
      string ouZqtZrHpY;
      string enlsFkDJby;
      string WNENoqzUWA;
      string tUJNHKNASK;
      string cJHaaYABdf;
      string PgKhfaqLBC;
      string ZWkoeKeXkt;
      string XCpRVNGdlQ;
      string qyppkNJahf;
      string TByQjFYRwQ;
      if(wUMnRGgHQk == ouZqtZrHpY){tbPjIMqrLR = true;}
      else if(ouZqtZrHpY == wUMnRGgHQk){aWAJRzQgkh = true;}
      if(DTOOrTezfi == enlsFkDJby){UMZkLagtEQ = true;}
      else if(enlsFkDJby == DTOOrTezfi){BMQmqSymDS = true;}
      if(xIqIxGhkkE == WNENoqzUWA){ADpFaVDYhQ = true;}
      else if(WNENoqzUWA == xIqIxGhkkE){FczgSSbRQn = true;}
      if(QOIKtppktp == tUJNHKNASK){ongUWOiGhX = true;}
      else if(tUJNHKNASK == QOIKtppktp){cUlOtXoJGr = true;}
      if(OMAArAAtsX == cJHaaYABdf){WQOPLGbNFJ = true;}
      else if(cJHaaYABdf == OMAArAAtsX){ssQWeQIKDu = true;}
      if(TwxKKndDpL == PgKhfaqLBC){YdNeQplKIl = true;}
      else if(PgKhfaqLBC == TwxKKndDpL){GSPTYxWSpz = true;}
      if(YuWMToLEUC == ZWkoeKeXkt){IRKucffENw = true;}
      else if(ZWkoeKeXkt == YuWMToLEUC){WzQxEgZBsT = true;}
      if(dtEoTkIpQx == XCpRVNGdlQ){qZMfsinZsU = true;}
      if(FmrNjURxAG == qyppkNJahf){toSXqKaCEf = true;}
      if(MltiRTpmgC == TByQjFYRwQ){cYyuOFGTme = true;}
      while(XCpRVNGdlQ == dtEoTkIpQx){dnfLYMMcCC = true;}
      while(qyppkNJahf == qyppkNJahf){KQNUhJFRpx = true;}
      while(TByQjFYRwQ == TByQjFYRwQ){AVSHUsbSRx = true;}
      if(tbPjIMqrLR == true){tbPjIMqrLR = false;}
      if(UMZkLagtEQ == true){UMZkLagtEQ = false;}
      if(ADpFaVDYhQ == true){ADpFaVDYhQ = false;}
      if(ongUWOiGhX == true){ongUWOiGhX = false;}
      if(WQOPLGbNFJ == true){WQOPLGbNFJ = false;}
      if(YdNeQplKIl == true){YdNeQplKIl = false;}
      if(IRKucffENw == true){IRKucffENw = false;}
      if(qZMfsinZsU == true){qZMfsinZsU = false;}
      if(toSXqKaCEf == true){toSXqKaCEf = false;}
      if(cYyuOFGTme == true){cYyuOFGTme = false;}
      if(aWAJRzQgkh == true){aWAJRzQgkh = false;}
      if(BMQmqSymDS == true){BMQmqSymDS = false;}
      if(FczgSSbRQn == true){FczgSSbRQn = false;}
      if(cUlOtXoJGr == true){cUlOtXoJGr = false;}
      if(ssQWeQIKDu == true){ssQWeQIKDu = false;}
      if(GSPTYxWSpz == true){GSPTYxWSpz = false;}
      if(WzQxEgZBsT == true){WzQxEgZBsT = false;}
      if(dnfLYMMcCC == true){dnfLYMMcCC = false;}
      if(KQNUhJFRpx == true){KQNUhJFRpx = false;}
      if(AVSHUsbSRx == true){AVSHUsbSRx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ILMDUTNYYX
{ 
  void BjGjZryPOo()
  { 
      bool WMJgFSYnMD = false;
      bool QzkigQdMOR = false;
      bool kGQyTlQKCP = false;
      bool PgzsJEcGcW = false;
      bool lrSJamEadb = false;
      bool MGqQFPuKNS = false;
      bool BNkwniAqZb = false;
      bool nXirernGWg = false;
      bool gpfaCJoins = false;
      bool JRrKUXHVVr = false;
      bool mNABnoWzlM = false;
      bool bnmglKhKse = false;
      bool sQCfSVeYWG = false;
      bool kRkesToemM = false;
      bool lpwaRUdLXJ = false;
      bool pxcqyVKUhR = false;
      bool KycebKCImR = false;
      bool VCWfsDTaNy = false;
      bool qSAMPmotgX = false;
      bool IUwVCmNRzH = false;
      string UDDRlfwrjI;
      string qAszsOugME;
      string xwkojMVQzF;
      string oUJGPLjUoc;
      string aSFCGoOxlj;
      string RltOMYSOgY;
      string KfseSWpmih;
      string dariceqhiu;
      string xXeOmDZtsp;
      string sVmPSuYaii;
      string zbNEFqtLkh;
      string hjelblBeqP;
      string xusroHmbPh;
      string FPyAuUKZIw;
      string IOIKIIqAng;
      string stiSlDhUPx;
      string DRuDcRleqG;
      string baVuGhmhjf;
      string QmnioKgeNr;
      string moKKrqSFhp;
      if(UDDRlfwrjI == zbNEFqtLkh){WMJgFSYnMD = true;}
      else if(zbNEFqtLkh == UDDRlfwrjI){mNABnoWzlM = true;}
      if(qAszsOugME == hjelblBeqP){QzkigQdMOR = true;}
      else if(hjelblBeqP == qAszsOugME){bnmglKhKse = true;}
      if(xwkojMVQzF == xusroHmbPh){kGQyTlQKCP = true;}
      else if(xusroHmbPh == xwkojMVQzF){sQCfSVeYWG = true;}
      if(oUJGPLjUoc == FPyAuUKZIw){PgzsJEcGcW = true;}
      else if(FPyAuUKZIw == oUJGPLjUoc){kRkesToemM = true;}
      if(aSFCGoOxlj == IOIKIIqAng){lrSJamEadb = true;}
      else if(IOIKIIqAng == aSFCGoOxlj){lpwaRUdLXJ = true;}
      if(RltOMYSOgY == stiSlDhUPx){MGqQFPuKNS = true;}
      else if(stiSlDhUPx == RltOMYSOgY){pxcqyVKUhR = true;}
      if(KfseSWpmih == DRuDcRleqG){BNkwniAqZb = true;}
      else if(DRuDcRleqG == KfseSWpmih){KycebKCImR = true;}
      if(dariceqhiu == baVuGhmhjf){nXirernGWg = true;}
      if(xXeOmDZtsp == QmnioKgeNr){gpfaCJoins = true;}
      if(sVmPSuYaii == moKKrqSFhp){JRrKUXHVVr = true;}
      while(baVuGhmhjf == dariceqhiu){VCWfsDTaNy = true;}
      while(QmnioKgeNr == QmnioKgeNr){qSAMPmotgX = true;}
      while(moKKrqSFhp == moKKrqSFhp){IUwVCmNRzH = true;}
      if(WMJgFSYnMD == true){WMJgFSYnMD = false;}
      if(QzkigQdMOR == true){QzkigQdMOR = false;}
      if(kGQyTlQKCP == true){kGQyTlQKCP = false;}
      if(PgzsJEcGcW == true){PgzsJEcGcW = false;}
      if(lrSJamEadb == true){lrSJamEadb = false;}
      if(MGqQFPuKNS == true){MGqQFPuKNS = false;}
      if(BNkwniAqZb == true){BNkwniAqZb = false;}
      if(nXirernGWg == true){nXirernGWg = false;}
      if(gpfaCJoins == true){gpfaCJoins = false;}
      if(JRrKUXHVVr == true){JRrKUXHVVr = false;}
      if(mNABnoWzlM == true){mNABnoWzlM = false;}
      if(bnmglKhKse == true){bnmglKhKse = false;}
      if(sQCfSVeYWG == true){sQCfSVeYWG = false;}
      if(kRkesToemM == true){kRkesToemM = false;}
      if(lpwaRUdLXJ == true){lpwaRUdLXJ = false;}
      if(pxcqyVKUhR == true){pxcqyVKUhR = false;}
      if(KycebKCImR == true){KycebKCImR = false;}
      if(VCWfsDTaNy == true){VCWfsDTaNy = false;}
      if(qSAMPmotgX == true){qSAMPmotgX = false;}
      if(IUwVCmNRzH == true){IUwVCmNRzH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TBUYBFPFQR
{ 
  void CrakbMeIgF()
  { 
      bool aDJOVBIIab = false;
      bool SklFaejhqz = false;
      bool LKNIzwUcml = false;
      bool czeRtSjAdL = false;
      bool zhpmrSDVjA = false;
      bool nMuKhQoBOZ = false;
      bool gfUnySFTLH = false;
      bool uiDfzcTaQg = false;
      bool rzrmxQDUid = false;
      bool dhkDdTMBnY = false;
      bool NjJbEFIPKF = false;
      bool wOkhhhmhqh = false;
      bool PjkhdMxzBe = false;
      bool PSlqTIoQhr = false;
      bool InJdgPxDVw = false;
      bool geKGJczbyr = false;
      bool HINepdbsNZ = false;
      bool sWzzZaZHAN = false;
      bool PtdFyjHehq = false;
      bool JMRpjzZdmC = false;
      string SatFbrGAyH;
      string YRkXhObZtD;
      string GickXhXFqb;
      string TEewzejsrC;
      string xETGUXWdDf;
      string cOiWPjyJhs;
      string TAJVmUmnXD;
      string dhgrGBPVPz;
      string LsCKzFUIgP;
      string faLziwuxTA;
      string jhFzBugqPO;
      string TcshgZyyWh;
      string AeHHXDWhJK;
      string FRBPPdnCJD;
      string XcrSwCgcRI;
      string xxakzFZxax;
      string YzhEICadSD;
      string lunSKXloLV;
      string WsPANIqQPK;
      string DpaLeXtmJt;
      if(SatFbrGAyH == jhFzBugqPO){aDJOVBIIab = true;}
      else if(jhFzBugqPO == SatFbrGAyH){NjJbEFIPKF = true;}
      if(YRkXhObZtD == TcshgZyyWh){SklFaejhqz = true;}
      else if(TcshgZyyWh == YRkXhObZtD){wOkhhhmhqh = true;}
      if(GickXhXFqb == AeHHXDWhJK){LKNIzwUcml = true;}
      else if(AeHHXDWhJK == GickXhXFqb){PjkhdMxzBe = true;}
      if(TEewzejsrC == FRBPPdnCJD){czeRtSjAdL = true;}
      else if(FRBPPdnCJD == TEewzejsrC){PSlqTIoQhr = true;}
      if(xETGUXWdDf == XcrSwCgcRI){zhpmrSDVjA = true;}
      else if(XcrSwCgcRI == xETGUXWdDf){InJdgPxDVw = true;}
      if(cOiWPjyJhs == xxakzFZxax){nMuKhQoBOZ = true;}
      else if(xxakzFZxax == cOiWPjyJhs){geKGJczbyr = true;}
      if(TAJVmUmnXD == YzhEICadSD){gfUnySFTLH = true;}
      else if(YzhEICadSD == TAJVmUmnXD){HINepdbsNZ = true;}
      if(dhgrGBPVPz == lunSKXloLV){uiDfzcTaQg = true;}
      if(LsCKzFUIgP == WsPANIqQPK){rzrmxQDUid = true;}
      if(faLziwuxTA == DpaLeXtmJt){dhkDdTMBnY = true;}
      while(lunSKXloLV == dhgrGBPVPz){sWzzZaZHAN = true;}
      while(WsPANIqQPK == WsPANIqQPK){PtdFyjHehq = true;}
      while(DpaLeXtmJt == DpaLeXtmJt){JMRpjzZdmC = true;}
      if(aDJOVBIIab == true){aDJOVBIIab = false;}
      if(SklFaejhqz == true){SklFaejhqz = false;}
      if(LKNIzwUcml == true){LKNIzwUcml = false;}
      if(czeRtSjAdL == true){czeRtSjAdL = false;}
      if(zhpmrSDVjA == true){zhpmrSDVjA = false;}
      if(nMuKhQoBOZ == true){nMuKhQoBOZ = false;}
      if(gfUnySFTLH == true){gfUnySFTLH = false;}
      if(uiDfzcTaQg == true){uiDfzcTaQg = false;}
      if(rzrmxQDUid == true){rzrmxQDUid = false;}
      if(dhkDdTMBnY == true){dhkDdTMBnY = false;}
      if(NjJbEFIPKF == true){NjJbEFIPKF = false;}
      if(wOkhhhmhqh == true){wOkhhhmhqh = false;}
      if(PjkhdMxzBe == true){PjkhdMxzBe = false;}
      if(PSlqTIoQhr == true){PSlqTIoQhr = false;}
      if(InJdgPxDVw == true){InJdgPxDVw = false;}
      if(geKGJczbyr == true){geKGJczbyr = false;}
      if(HINepdbsNZ == true){HINepdbsNZ = false;}
      if(sWzzZaZHAN == true){sWzzZaZHAN = false;}
      if(PtdFyjHehq == true){PtdFyjHehq = false;}
      if(JMRpjzZdmC == true){JMRpjzZdmC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DODPAFNXRY
{ 
  void kUJdrsSTrL()
  { 
      bool ZsgclEirYr = false;
      bool NgoMWpeQqg = false;
      bool XhiciGibrS = false;
      bool QpLSeMCyfu = false;
      bool KhCZqUmEFf = false;
      bool FlYgYqKEte = false;
      bool UGAGaWUWhJ = false;
      bool mgkwVofIkN = false;
      bool SeWMMeQdsm = false;
      bool ByEAZDgwzT = false;
      bool zQWurYBcKi = false;
      bool LCSfLpjntw = false;
      bool FpctIobkWS = false;
      bool IjJQOCIaTm = false;
      bool cnSKbzeYni = false;
      bool SsCCOInbmC = false;
      bool xPGrabrBQJ = false;
      bool hITGSRXSRI = false;
      bool KDxmzOgGCF = false;
      bool OfnRpMgajz = false;
      string bVSagyPjtG;
      string UTsnanETSQ;
      string SxgkLLomqO;
      string YEAhFmKjat;
      string ToxFkDgwuI;
      string smutkeohOV;
      string IcrfgQTLim;
      string dUrYxdzbAI;
      string dsqiUlIFwZ;
      string ycVEkqwRXU;
      string iVMHdYtWxH;
      string fNgGrPkJKu;
      string HOOJoBynmG;
      string ghDfYIfjEw;
      string qlHotjuOMV;
      string GmHbMTGDSc;
      string ZGiqZyJBgj;
      string iBEODUGZOF;
      string GjaRAsZaSE;
      string BbRbVkDQOw;
      if(bVSagyPjtG == iVMHdYtWxH){ZsgclEirYr = true;}
      else if(iVMHdYtWxH == bVSagyPjtG){zQWurYBcKi = true;}
      if(UTsnanETSQ == fNgGrPkJKu){NgoMWpeQqg = true;}
      else if(fNgGrPkJKu == UTsnanETSQ){LCSfLpjntw = true;}
      if(SxgkLLomqO == HOOJoBynmG){XhiciGibrS = true;}
      else if(HOOJoBynmG == SxgkLLomqO){FpctIobkWS = true;}
      if(YEAhFmKjat == ghDfYIfjEw){QpLSeMCyfu = true;}
      else if(ghDfYIfjEw == YEAhFmKjat){IjJQOCIaTm = true;}
      if(ToxFkDgwuI == qlHotjuOMV){KhCZqUmEFf = true;}
      else if(qlHotjuOMV == ToxFkDgwuI){cnSKbzeYni = true;}
      if(smutkeohOV == GmHbMTGDSc){FlYgYqKEte = true;}
      else if(GmHbMTGDSc == smutkeohOV){SsCCOInbmC = true;}
      if(IcrfgQTLim == ZGiqZyJBgj){UGAGaWUWhJ = true;}
      else if(ZGiqZyJBgj == IcrfgQTLim){xPGrabrBQJ = true;}
      if(dUrYxdzbAI == iBEODUGZOF){mgkwVofIkN = true;}
      if(dsqiUlIFwZ == GjaRAsZaSE){SeWMMeQdsm = true;}
      if(ycVEkqwRXU == BbRbVkDQOw){ByEAZDgwzT = true;}
      while(iBEODUGZOF == dUrYxdzbAI){hITGSRXSRI = true;}
      while(GjaRAsZaSE == GjaRAsZaSE){KDxmzOgGCF = true;}
      while(BbRbVkDQOw == BbRbVkDQOw){OfnRpMgajz = true;}
      if(ZsgclEirYr == true){ZsgclEirYr = false;}
      if(NgoMWpeQqg == true){NgoMWpeQqg = false;}
      if(XhiciGibrS == true){XhiciGibrS = false;}
      if(QpLSeMCyfu == true){QpLSeMCyfu = false;}
      if(KhCZqUmEFf == true){KhCZqUmEFf = false;}
      if(FlYgYqKEte == true){FlYgYqKEte = false;}
      if(UGAGaWUWhJ == true){UGAGaWUWhJ = false;}
      if(mgkwVofIkN == true){mgkwVofIkN = false;}
      if(SeWMMeQdsm == true){SeWMMeQdsm = false;}
      if(ByEAZDgwzT == true){ByEAZDgwzT = false;}
      if(zQWurYBcKi == true){zQWurYBcKi = false;}
      if(LCSfLpjntw == true){LCSfLpjntw = false;}
      if(FpctIobkWS == true){FpctIobkWS = false;}
      if(IjJQOCIaTm == true){IjJQOCIaTm = false;}
      if(cnSKbzeYni == true){cnSKbzeYni = false;}
      if(SsCCOInbmC == true){SsCCOInbmC = false;}
      if(xPGrabrBQJ == true){xPGrabrBQJ = false;}
      if(hITGSRXSRI == true){hITGSRXSRI = false;}
      if(KDxmzOgGCF == true){KDxmzOgGCF = false;}
      if(OfnRpMgajz == true){OfnRpMgajz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HSPFADZZBY
{ 
  void nEISLEeYuZ()
  { 
      bool nUGtEBRpQA = false;
      bool sNOWtOqIKt = false;
      bool RTPBbTtiAe = false;
      bool eEFMGFazYT = false;
      bool ubmlqBElIK = false;
      bool clHNrUEFRj = false;
      bool GhplVnICQo = false;
      bool nqjpzpfdJZ = false;
      bool OHaoBswqTk = false;
      bool BUgnMMkBQC = false;
      bool sCVTWkCRNB = false;
      bool oZwrUzHBjb = false;
      bool rQhemSKucl = false;
      bool FdNGgMlHRQ = false;
      bool qedSwaYoSN = false;
      bool FiRnKbUpfE = false;
      bool aGnbwKLoKI = false;
      bool MzjTjMmPhM = false;
      bool sVbPfVMZwF = false;
      bool rubMpkqBVk = false;
      string RFlgyfVzNH;
      string BCREtjJCpe;
      string CBaZFShnuW;
      string kEYzbhzFAi;
      string TTFodQXckE;
      string bQPSIPdLae;
      string xhDqWwdSbL;
      string kEBHLiwlun;
      string uFCqtToGpM;
      string EmdVkkQNSh;
      string mEAZSWPIGZ;
      string SqPlirfLxC;
      string GWcPHxZeVa;
      string RiTNAqEbYW;
      string DgzPsMWrlr;
      string FEQPaQakSU;
      string xjlfHjXCkr;
      string nDmZyZXMVu;
      string ZhscVNRElj;
      string PTJDZTtSHJ;
      if(RFlgyfVzNH == mEAZSWPIGZ){nUGtEBRpQA = true;}
      else if(mEAZSWPIGZ == RFlgyfVzNH){sCVTWkCRNB = true;}
      if(BCREtjJCpe == SqPlirfLxC){sNOWtOqIKt = true;}
      else if(SqPlirfLxC == BCREtjJCpe){oZwrUzHBjb = true;}
      if(CBaZFShnuW == GWcPHxZeVa){RTPBbTtiAe = true;}
      else if(GWcPHxZeVa == CBaZFShnuW){rQhemSKucl = true;}
      if(kEYzbhzFAi == RiTNAqEbYW){eEFMGFazYT = true;}
      else if(RiTNAqEbYW == kEYzbhzFAi){FdNGgMlHRQ = true;}
      if(TTFodQXckE == DgzPsMWrlr){ubmlqBElIK = true;}
      else if(DgzPsMWrlr == TTFodQXckE){qedSwaYoSN = true;}
      if(bQPSIPdLae == FEQPaQakSU){clHNrUEFRj = true;}
      else if(FEQPaQakSU == bQPSIPdLae){FiRnKbUpfE = true;}
      if(xhDqWwdSbL == xjlfHjXCkr){GhplVnICQo = true;}
      else if(xjlfHjXCkr == xhDqWwdSbL){aGnbwKLoKI = true;}
      if(kEBHLiwlun == nDmZyZXMVu){nqjpzpfdJZ = true;}
      if(uFCqtToGpM == ZhscVNRElj){OHaoBswqTk = true;}
      if(EmdVkkQNSh == PTJDZTtSHJ){BUgnMMkBQC = true;}
      while(nDmZyZXMVu == kEBHLiwlun){MzjTjMmPhM = true;}
      while(ZhscVNRElj == ZhscVNRElj){sVbPfVMZwF = true;}
      while(PTJDZTtSHJ == PTJDZTtSHJ){rubMpkqBVk = true;}
      if(nUGtEBRpQA == true){nUGtEBRpQA = false;}
      if(sNOWtOqIKt == true){sNOWtOqIKt = false;}
      if(RTPBbTtiAe == true){RTPBbTtiAe = false;}
      if(eEFMGFazYT == true){eEFMGFazYT = false;}
      if(ubmlqBElIK == true){ubmlqBElIK = false;}
      if(clHNrUEFRj == true){clHNrUEFRj = false;}
      if(GhplVnICQo == true){GhplVnICQo = false;}
      if(nqjpzpfdJZ == true){nqjpzpfdJZ = false;}
      if(OHaoBswqTk == true){OHaoBswqTk = false;}
      if(BUgnMMkBQC == true){BUgnMMkBQC = false;}
      if(sCVTWkCRNB == true){sCVTWkCRNB = false;}
      if(oZwrUzHBjb == true){oZwrUzHBjb = false;}
      if(rQhemSKucl == true){rQhemSKucl = false;}
      if(FdNGgMlHRQ == true){FdNGgMlHRQ = false;}
      if(qedSwaYoSN == true){qedSwaYoSN = false;}
      if(FiRnKbUpfE == true){FiRnKbUpfE = false;}
      if(aGnbwKLoKI == true){aGnbwKLoKI = false;}
      if(MzjTjMmPhM == true){MzjTjMmPhM = false;}
      if(sVbPfVMZwF == true){sVbPfVMZwF = false;}
      if(rubMpkqBVk == true){rubMpkqBVk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PARWWDUTXH
{ 
  void zhOMhsbWgJ()
  { 
      bool dgJAwrjfey = false;
      bool QpnbEhaFxK = false;
      bool fIiiCVqTMZ = false;
      bool ihSIeTquwE = false;
      bool HzspNzEhLI = false;
      bool lCkWVUyZxa = false;
      bool AQSEPhXfxj = false;
      bool pfJsCfOsVD = false;
      bool QJHEmgxulJ = false;
      bool VRxUDqfoZe = false;
      bool bYkaSGsrUp = false;
      bool FEDtJqIOQi = false;
      bool jbsmOYhnpK = false;
      bool zZSqarYglg = false;
      bool mFawDQNDKL = false;
      bool iRXptAexLs = false;
      bool XEBJqelMSR = false;
      bool SbcjueAxiy = false;
      bool LecdbgCbwa = false;
      bool NaUrIhDRFX = false;
      string NzVqtMIeZk;
      string fscKuigIDW;
      string oFrEcOuKxM;
      string QchuxqXLAh;
      string nFaKnmHiJT;
      string dUVTxHGROf;
      string RxgMTDKgNE;
      string KVIUhiehPo;
      string GMAciwGOxp;
      string jGwTQqXNpk;
      string cZUFJILBkN;
      string cYBYZFwDdX;
      string wuiWTEYoDq;
      string LQqdLfquTZ;
      string jFciNLEWsL;
      string tTjSohpykE;
      string iWxtCLgXNs;
      string OBiDmpRAJI;
      string ABurwrfYnd;
      string psJPpNHigB;
      if(NzVqtMIeZk == cZUFJILBkN){dgJAwrjfey = true;}
      else if(cZUFJILBkN == NzVqtMIeZk){bYkaSGsrUp = true;}
      if(fscKuigIDW == cYBYZFwDdX){QpnbEhaFxK = true;}
      else if(cYBYZFwDdX == fscKuigIDW){FEDtJqIOQi = true;}
      if(oFrEcOuKxM == wuiWTEYoDq){fIiiCVqTMZ = true;}
      else if(wuiWTEYoDq == oFrEcOuKxM){jbsmOYhnpK = true;}
      if(QchuxqXLAh == LQqdLfquTZ){ihSIeTquwE = true;}
      else if(LQqdLfquTZ == QchuxqXLAh){zZSqarYglg = true;}
      if(nFaKnmHiJT == jFciNLEWsL){HzspNzEhLI = true;}
      else if(jFciNLEWsL == nFaKnmHiJT){mFawDQNDKL = true;}
      if(dUVTxHGROf == tTjSohpykE){lCkWVUyZxa = true;}
      else if(tTjSohpykE == dUVTxHGROf){iRXptAexLs = true;}
      if(RxgMTDKgNE == iWxtCLgXNs){AQSEPhXfxj = true;}
      else if(iWxtCLgXNs == RxgMTDKgNE){XEBJqelMSR = true;}
      if(KVIUhiehPo == OBiDmpRAJI){pfJsCfOsVD = true;}
      if(GMAciwGOxp == ABurwrfYnd){QJHEmgxulJ = true;}
      if(jGwTQqXNpk == psJPpNHigB){VRxUDqfoZe = true;}
      while(OBiDmpRAJI == KVIUhiehPo){SbcjueAxiy = true;}
      while(ABurwrfYnd == ABurwrfYnd){LecdbgCbwa = true;}
      while(psJPpNHigB == psJPpNHigB){NaUrIhDRFX = true;}
      if(dgJAwrjfey == true){dgJAwrjfey = false;}
      if(QpnbEhaFxK == true){QpnbEhaFxK = false;}
      if(fIiiCVqTMZ == true){fIiiCVqTMZ = false;}
      if(ihSIeTquwE == true){ihSIeTquwE = false;}
      if(HzspNzEhLI == true){HzspNzEhLI = false;}
      if(lCkWVUyZxa == true){lCkWVUyZxa = false;}
      if(AQSEPhXfxj == true){AQSEPhXfxj = false;}
      if(pfJsCfOsVD == true){pfJsCfOsVD = false;}
      if(QJHEmgxulJ == true){QJHEmgxulJ = false;}
      if(VRxUDqfoZe == true){VRxUDqfoZe = false;}
      if(bYkaSGsrUp == true){bYkaSGsrUp = false;}
      if(FEDtJqIOQi == true){FEDtJqIOQi = false;}
      if(jbsmOYhnpK == true){jbsmOYhnpK = false;}
      if(zZSqarYglg == true){zZSqarYglg = false;}
      if(mFawDQNDKL == true){mFawDQNDKL = false;}
      if(iRXptAexLs == true){iRXptAexLs = false;}
      if(XEBJqelMSR == true){XEBJqelMSR = false;}
      if(SbcjueAxiy == true){SbcjueAxiy = false;}
      if(LecdbgCbwa == true){LecdbgCbwa = false;}
      if(NaUrIhDRFX == true){NaUrIhDRFX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUUZTHHWQS
{ 
  void RhFRdoXAWa()
  { 
      bool NNrLDiuIyu = false;
      bool iWAQdLmNab = false;
      bool FrYLKffCHY = false;
      bool wlEGgCblsp = false;
      bool nCeXsYcftL = false;
      bool wnqmiUngAX = false;
      bool CsAYzwStja = false;
      bool jATjnDNASl = false;
      bool CzIwbIuQXL = false;
      bool NulVnuCFYw = false;
      bool FiwSbuTGzf = false;
      bool GnNOUCkEwp = false;
      bool ACVXNoOyus = false;
      bool BHbVfTDoUg = false;
      bool nnRrFZgWAk = false;
      bool JxJhwDMYFl = false;
      bool gVKFezLrhB = false;
      bool zuiPBLkdSm = false;
      bool IqxKiDysZc = false;
      bool GejhAScLMF = false;
      string HhmkXAjGYC;
      string CDYhhStHJQ;
      string LSHOJDsCeD;
      string BJchKPjKfD;
      string fptmwkcVGx;
      string QdbXmnaYbT;
      string GhaVBrapXR;
      string hjbGkUXURY;
      string ZXwhlWhEtV;
      string oLiLwyOYkE;
      string JmxnPgBUmR;
      string QFGCsiksjd;
      string KVwBcVAPKl;
      string GzjNOmZHRE;
      string VMRbFiFfRM;
      string MVnGtmqwKt;
      string gkKALQVrmG;
      string JdafIyETut;
      string PUyxZjKcTb;
      string udxXXjBRPo;
      if(HhmkXAjGYC == JmxnPgBUmR){NNrLDiuIyu = true;}
      else if(JmxnPgBUmR == HhmkXAjGYC){FiwSbuTGzf = true;}
      if(CDYhhStHJQ == QFGCsiksjd){iWAQdLmNab = true;}
      else if(QFGCsiksjd == CDYhhStHJQ){GnNOUCkEwp = true;}
      if(LSHOJDsCeD == KVwBcVAPKl){FrYLKffCHY = true;}
      else if(KVwBcVAPKl == LSHOJDsCeD){ACVXNoOyus = true;}
      if(BJchKPjKfD == GzjNOmZHRE){wlEGgCblsp = true;}
      else if(GzjNOmZHRE == BJchKPjKfD){BHbVfTDoUg = true;}
      if(fptmwkcVGx == VMRbFiFfRM){nCeXsYcftL = true;}
      else if(VMRbFiFfRM == fptmwkcVGx){nnRrFZgWAk = true;}
      if(QdbXmnaYbT == MVnGtmqwKt){wnqmiUngAX = true;}
      else if(MVnGtmqwKt == QdbXmnaYbT){JxJhwDMYFl = true;}
      if(GhaVBrapXR == gkKALQVrmG){CsAYzwStja = true;}
      else if(gkKALQVrmG == GhaVBrapXR){gVKFezLrhB = true;}
      if(hjbGkUXURY == JdafIyETut){jATjnDNASl = true;}
      if(ZXwhlWhEtV == PUyxZjKcTb){CzIwbIuQXL = true;}
      if(oLiLwyOYkE == udxXXjBRPo){NulVnuCFYw = true;}
      while(JdafIyETut == hjbGkUXURY){zuiPBLkdSm = true;}
      while(PUyxZjKcTb == PUyxZjKcTb){IqxKiDysZc = true;}
      while(udxXXjBRPo == udxXXjBRPo){GejhAScLMF = true;}
      if(NNrLDiuIyu == true){NNrLDiuIyu = false;}
      if(iWAQdLmNab == true){iWAQdLmNab = false;}
      if(FrYLKffCHY == true){FrYLKffCHY = false;}
      if(wlEGgCblsp == true){wlEGgCblsp = false;}
      if(nCeXsYcftL == true){nCeXsYcftL = false;}
      if(wnqmiUngAX == true){wnqmiUngAX = false;}
      if(CsAYzwStja == true){CsAYzwStja = false;}
      if(jATjnDNASl == true){jATjnDNASl = false;}
      if(CzIwbIuQXL == true){CzIwbIuQXL = false;}
      if(NulVnuCFYw == true){NulVnuCFYw = false;}
      if(FiwSbuTGzf == true){FiwSbuTGzf = false;}
      if(GnNOUCkEwp == true){GnNOUCkEwp = false;}
      if(ACVXNoOyus == true){ACVXNoOyus = false;}
      if(BHbVfTDoUg == true){BHbVfTDoUg = false;}
      if(nnRrFZgWAk == true){nnRrFZgWAk = false;}
      if(JxJhwDMYFl == true){JxJhwDMYFl = false;}
      if(gVKFezLrhB == true){gVKFezLrhB = false;}
      if(zuiPBLkdSm == true){zuiPBLkdSm = false;}
      if(IqxKiDysZc == true){IqxKiDysZc = false;}
      if(GejhAScLMF == true){GejhAScLMF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XCTMFGWSJU
{ 
  void xAbiTwkdkQ()
  { 
      bool InTjmEyadW = false;
      bool ScxBNljcCH = false;
      bool leBOQNHhuH = false;
      bool VOnVILEcaa = false;
      bool gPJCIfkWFM = false;
      bool XlgBXclETZ = false;
      bool wQeVBDnarC = false;
      bool gGCaZVUyGk = false;
      bool bjbhjjhlyf = false;
      bool YAJBdQjnBE = false;
      bool qKdDfQjFbB = false;
      bool HmyhxMnwkQ = false;
      bool VCcMcgxAxJ = false;
      bool lgxBtRFYCT = false;
      bool AbKwXkBaDR = false;
      bool bmCjiogRaz = false;
      bool SiISPZpxne = false;
      bool GPtRQtqgoq = false;
      bool eWxegyeMSF = false;
      bool knyDARSrgx = false;
      string msHFrIHYTf;
      string QaMtgDZUxM;
      string tNBSugtedQ;
      string kdqBAQOBdG;
      string ldcHlSenbS;
      string PLgZjZroJK;
      string NbtDtmiKsQ;
      string oXpqaPksfb;
      string CGDLAZwRQa;
      string YYqSrJiYNy;
      string iTtKdqUpzU;
      string nyJhIHYiDT;
      string qRsRqPgXyQ;
      string gLfhriLrgI;
      string EGSwlZPIKj;
      string kAVsHRZcSN;
      string KxqhmcRboZ;
      string wgBtPjzxfR;
      string AXNOffpmZa;
      string IhYTyHOjIJ;
      if(msHFrIHYTf == iTtKdqUpzU){InTjmEyadW = true;}
      else if(iTtKdqUpzU == msHFrIHYTf){qKdDfQjFbB = true;}
      if(QaMtgDZUxM == nyJhIHYiDT){ScxBNljcCH = true;}
      else if(nyJhIHYiDT == QaMtgDZUxM){HmyhxMnwkQ = true;}
      if(tNBSugtedQ == qRsRqPgXyQ){leBOQNHhuH = true;}
      else if(qRsRqPgXyQ == tNBSugtedQ){VCcMcgxAxJ = true;}
      if(kdqBAQOBdG == gLfhriLrgI){VOnVILEcaa = true;}
      else if(gLfhriLrgI == kdqBAQOBdG){lgxBtRFYCT = true;}
      if(ldcHlSenbS == EGSwlZPIKj){gPJCIfkWFM = true;}
      else if(EGSwlZPIKj == ldcHlSenbS){AbKwXkBaDR = true;}
      if(PLgZjZroJK == kAVsHRZcSN){XlgBXclETZ = true;}
      else if(kAVsHRZcSN == PLgZjZroJK){bmCjiogRaz = true;}
      if(NbtDtmiKsQ == KxqhmcRboZ){wQeVBDnarC = true;}
      else if(KxqhmcRboZ == NbtDtmiKsQ){SiISPZpxne = true;}
      if(oXpqaPksfb == wgBtPjzxfR){gGCaZVUyGk = true;}
      if(CGDLAZwRQa == AXNOffpmZa){bjbhjjhlyf = true;}
      if(YYqSrJiYNy == IhYTyHOjIJ){YAJBdQjnBE = true;}
      while(wgBtPjzxfR == oXpqaPksfb){GPtRQtqgoq = true;}
      while(AXNOffpmZa == AXNOffpmZa){eWxegyeMSF = true;}
      while(IhYTyHOjIJ == IhYTyHOjIJ){knyDARSrgx = true;}
      if(InTjmEyadW == true){InTjmEyadW = false;}
      if(ScxBNljcCH == true){ScxBNljcCH = false;}
      if(leBOQNHhuH == true){leBOQNHhuH = false;}
      if(VOnVILEcaa == true){VOnVILEcaa = false;}
      if(gPJCIfkWFM == true){gPJCIfkWFM = false;}
      if(XlgBXclETZ == true){XlgBXclETZ = false;}
      if(wQeVBDnarC == true){wQeVBDnarC = false;}
      if(gGCaZVUyGk == true){gGCaZVUyGk = false;}
      if(bjbhjjhlyf == true){bjbhjjhlyf = false;}
      if(YAJBdQjnBE == true){YAJBdQjnBE = false;}
      if(qKdDfQjFbB == true){qKdDfQjFbB = false;}
      if(HmyhxMnwkQ == true){HmyhxMnwkQ = false;}
      if(VCcMcgxAxJ == true){VCcMcgxAxJ = false;}
      if(lgxBtRFYCT == true){lgxBtRFYCT = false;}
      if(AbKwXkBaDR == true){AbKwXkBaDR = false;}
      if(bmCjiogRaz == true){bmCjiogRaz = false;}
      if(SiISPZpxne == true){SiISPZpxne = false;}
      if(GPtRQtqgoq == true){GPtRQtqgoq = false;}
      if(eWxegyeMSF == true){eWxegyeMSF = false;}
      if(knyDARSrgx == true){knyDARSrgx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JAKZZXAOXF
{ 
  void rqVDPitZWu()
  { 
      bool fpYSiBseEz = false;
      bool BoWNOFiNdf = false;
      bool lRyOBmrFSG = false;
      bool NsrSbezWVQ = false;
      bool dgMpRaZBea = false;
      bool seHRVOrKQw = false;
      bool ImMxkHxDlj = false;
      bool FMqMBEFHwZ = false;
      bool NpZqNilZxM = false;
      bool loFZIpUOEK = false;
      bool dVPuUgmtPQ = false;
      bool JkNpiSMUiC = false;
      bool UXFYxQGREL = false;
      bool jpClwqadWf = false;
      bool urJfDBbOpp = false;
      bool czeCoGQpyE = false;
      bool ZVoEfThatq = false;
      bool qiyDGcNYUu = false;
      bool nqaOhkKAxp = false;
      bool ajeRGZCEAj = false;
      string eCYlioXDjJ;
      string ohkApilIVJ;
      string CGlSJAkxLC;
      string YRMZURUQhA;
      string dOYJwPgLRy;
      string fYMFGXPFbh;
      string DZqhjWVKeX;
      string OUZUfmhcVt;
      string SZfNWzEHTx;
      string BOozwDWpYY;
      string tWfsiKyrYS;
      string pmjhOctdLk;
      string SNqhWzfZYb;
      string PqEwzwtldL;
      string BMhAGOdGkS;
      string JsenGffyWj;
      string eXTwCyhnhS;
      string iHzziGepaI;
      string UYoFSWMQpS;
      string QwPtgcrkyH;
      if(eCYlioXDjJ == tWfsiKyrYS){fpYSiBseEz = true;}
      else if(tWfsiKyrYS == eCYlioXDjJ){dVPuUgmtPQ = true;}
      if(ohkApilIVJ == pmjhOctdLk){BoWNOFiNdf = true;}
      else if(pmjhOctdLk == ohkApilIVJ){JkNpiSMUiC = true;}
      if(CGlSJAkxLC == SNqhWzfZYb){lRyOBmrFSG = true;}
      else if(SNqhWzfZYb == CGlSJAkxLC){UXFYxQGREL = true;}
      if(YRMZURUQhA == PqEwzwtldL){NsrSbezWVQ = true;}
      else if(PqEwzwtldL == YRMZURUQhA){jpClwqadWf = true;}
      if(dOYJwPgLRy == BMhAGOdGkS){dgMpRaZBea = true;}
      else if(BMhAGOdGkS == dOYJwPgLRy){urJfDBbOpp = true;}
      if(fYMFGXPFbh == JsenGffyWj){seHRVOrKQw = true;}
      else if(JsenGffyWj == fYMFGXPFbh){czeCoGQpyE = true;}
      if(DZqhjWVKeX == eXTwCyhnhS){ImMxkHxDlj = true;}
      else if(eXTwCyhnhS == DZqhjWVKeX){ZVoEfThatq = true;}
      if(OUZUfmhcVt == iHzziGepaI){FMqMBEFHwZ = true;}
      if(SZfNWzEHTx == UYoFSWMQpS){NpZqNilZxM = true;}
      if(BOozwDWpYY == QwPtgcrkyH){loFZIpUOEK = true;}
      while(iHzziGepaI == OUZUfmhcVt){qiyDGcNYUu = true;}
      while(UYoFSWMQpS == UYoFSWMQpS){nqaOhkKAxp = true;}
      while(QwPtgcrkyH == QwPtgcrkyH){ajeRGZCEAj = true;}
      if(fpYSiBseEz == true){fpYSiBseEz = false;}
      if(BoWNOFiNdf == true){BoWNOFiNdf = false;}
      if(lRyOBmrFSG == true){lRyOBmrFSG = false;}
      if(NsrSbezWVQ == true){NsrSbezWVQ = false;}
      if(dgMpRaZBea == true){dgMpRaZBea = false;}
      if(seHRVOrKQw == true){seHRVOrKQw = false;}
      if(ImMxkHxDlj == true){ImMxkHxDlj = false;}
      if(FMqMBEFHwZ == true){FMqMBEFHwZ = false;}
      if(NpZqNilZxM == true){NpZqNilZxM = false;}
      if(loFZIpUOEK == true){loFZIpUOEK = false;}
      if(dVPuUgmtPQ == true){dVPuUgmtPQ = false;}
      if(JkNpiSMUiC == true){JkNpiSMUiC = false;}
      if(UXFYxQGREL == true){UXFYxQGREL = false;}
      if(jpClwqadWf == true){jpClwqadWf = false;}
      if(urJfDBbOpp == true){urJfDBbOpp = false;}
      if(czeCoGQpyE == true){czeCoGQpyE = false;}
      if(ZVoEfThatq == true){ZVoEfThatq = false;}
      if(qiyDGcNYUu == true){qiyDGcNYUu = false;}
      if(nqaOhkKAxp == true){nqaOhkKAxp = false;}
      if(ajeRGZCEAj == true){ajeRGZCEAj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MUBJZYGRKY
{ 
  void mrEaWVsIgW()
  { 
      bool QpUkLnWrkz = false;
      bool enmLjEYWZq = false;
      bool aFCaoczfFk = false;
      bool ETJiIBFUgZ = false;
      bool prSDsTznYw = false;
      bool lZeShKnswi = false;
      bool oplzuLdDCh = false;
      bool zDozAimyhV = false;
      bool cKGJzdoqAy = false;
      bool NLYykAFSHg = false;
      bool owlqxhjeRz = false;
      bool WoLaFeicAQ = false;
      bool WmCETmeqOA = false;
      bool cTpAfgXPLQ = false;
      bool tJYBaXAyrF = false;
      bool QcSqKBshWJ = false;
      bool DrQRVDyKtY = false;
      bool GTQiWNOBcu = false;
      bool mgzIjzAzpe = false;
      bool npsBNBrHeW = false;
      string SJWsrZaoSz;
      string ZuJIjdQtfy;
      string ZCMsSYgWNY;
      string GNuhfQiXMB;
      string ZOgKaUSVDL;
      string SzPNoPwcaS;
      string rDbtrLzbcS;
      string trgdXLVCSy;
      string GLTBGHyhrP;
      string TGxsJWllRO;
      string UqsjQZRkod;
      string ttJcLgiZmk;
      string NQiNznumUB;
      string YijEcPRjkf;
      string oMrOUZwUhb;
      string mLzgADHejb;
      string edPnELJFzw;
      string PyoGwAYTrY;
      string rZFsONjDDY;
      string HlzIBKwEKJ;
      if(SJWsrZaoSz == UqsjQZRkod){QpUkLnWrkz = true;}
      else if(UqsjQZRkod == SJWsrZaoSz){owlqxhjeRz = true;}
      if(ZuJIjdQtfy == ttJcLgiZmk){enmLjEYWZq = true;}
      else if(ttJcLgiZmk == ZuJIjdQtfy){WoLaFeicAQ = true;}
      if(ZCMsSYgWNY == NQiNznumUB){aFCaoczfFk = true;}
      else if(NQiNznumUB == ZCMsSYgWNY){WmCETmeqOA = true;}
      if(GNuhfQiXMB == YijEcPRjkf){ETJiIBFUgZ = true;}
      else if(YijEcPRjkf == GNuhfQiXMB){cTpAfgXPLQ = true;}
      if(ZOgKaUSVDL == oMrOUZwUhb){prSDsTznYw = true;}
      else if(oMrOUZwUhb == ZOgKaUSVDL){tJYBaXAyrF = true;}
      if(SzPNoPwcaS == mLzgADHejb){lZeShKnswi = true;}
      else if(mLzgADHejb == SzPNoPwcaS){QcSqKBshWJ = true;}
      if(rDbtrLzbcS == edPnELJFzw){oplzuLdDCh = true;}
      else if(edPnELJFzw == rDbtrLzbcS){DrQRVDyKtY = true;}
      if(trgdXLVCSy == PyoGwAYTrY){zDozAimyhV = true;}
      if(GLTBGHyhrP == rZFsONjDDY){cKGJzdoqAy = true;}
      if(TGxsJWllRO == HlzIBKwEKJ){NLYykAFSHg = true;}
      while(PyoGwAYTrY == trgdXLVCSy){GTQiWNOBcu = true;}
      while(rZFsONjDDY == rZFsONjDDY){mgzIjzAzpe = true;}
      while(HlzIBKwEKJ == HlzIBKwEKJ){npsBNBrHeW = true;}
      if(QpUkLnWrkz == true){QpUkLnWrkz = false;}
      if(enmLjEYWZq == true){enmLjEYWZq = false;}
      if(aFCaoczfFk == true){aFCaoczfFk = false;}
      if(ETJiIBFUgZ == true){ETJiIBFUgZ = false;}
      if(prSDsTznYw == true){prSDsTznYw = false;}
      if(lZeShKnswi == true){lZeShKnswi = false;}
      if(oplzuLdDCh == true){oplzuLdDCh = false;}
      if(zDozAimyhV == true){zDozAimyhV = false;}
      if(cKGJzdoqAy == true){cKGJzdoqAy = false;}
      if(NLYykAFSHg == true){NLYykAFSHg = false;}
      if(owlqxhjeRz == true){owlqxhjeRz = false;}
      if(WoLaFeicAQ == true){WoLaFeicAQ = false;}
      if(WmCETmeqOA == true){WmCETmeqOA = false;}
      if(cTpAfgXPLQ == true){cTpAfgXPLQ = false;}
      if(tJYBaXAyrF == true){tJYBaXAyrF = false;}
      if(QcSqKBshWJ == true){QcSqKBshWJ = false;}
      if(DrQRVDyKtY == true){DrQRVDyKtY = false;}
      if(GTQiWNOBcu == true){GTQiWNOBcu = false;}
      if(mgzIjzAzpe == true){mgzIjzAzpe = false;}
      if(npsBNBrHeW == true){npsBNBrHeW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KPYKNSIZVW
{ 
  void OjFBzCRqpf()
  { 
      bool iOEddiTzts = false;
      bool JSKZRBbDHr = false;
      bool ofLLwsPWaJ = false;
      bool zEpzHZfTDM = false;
      bool CRhspxfzuU = false;
      bool CcxQiCDrhj = false;
      bool SxXktFcKRq = false;
      bool VIzupWySVy = false;
      bool NQaGGVHZQE = false;
      bool WmkTsFswyj = false;
      bool UUgEytdBaL = false;
      bool EjWiVBVReY = false;
      bool yCtNUhWeBj = false;
      bool dCTkdsjWHM = false;
      bool qFyEAlQCyr = false;
      bool jbRZlRZSiQ = false;
      bool WyAphCQkFb = false;
      bool RyJShsDoNh = false;
      bool QUgJACktzL = false;
      bool SQmqorEIWx = false;
      string PtuUbLFFkf;
      string oXfnSyfoFu;
      string iajAkEtkTh;
      string PuarnWUgLn;
      string XwHtQgdkun;
      string lsxudnKtjX;
      string RUkCQtxmAu;
      string dycRXmTpiD;
      string aIofwVxfOz;
      string MZxnWDKEdW;
      string jqjzKmPfXq;
      string UULfwIeFGt;
      string xQXBiDBouT;
      string bOLMTjYpUI;
      string FRIXdrOQqN;
      string XFxiYSShQH;
      string lakDOFIzMM;
      string jokynfIzXq;
      string ojyguWQbmA;
      string QpYNWegEIX;
      if(PtuUbLFFkf == jqjzKmPfXq){iOEddiTzts = true;}
      else if(jqjzKmPfXq == PtuUbLFFkf){UUgEytdBaL = true;}
      if(oXfnSyfoFu == UULfwIeFGt){JSKZRBbDHr = true;}
      else if(UULfwIeFGt == oXfnSyfoFu){EjWiVBVReY = true;}
      if(iajAkEtkTh == xQXBiDBouT){ofLLwsPWaJ = true;}
      else if(xQXBiDBouT == iajAkEtkTh){yCtNUhWeBj = true;}
      if(PuarnWUgLn == bOLMTjYpUI){zEpzHZfTDM = true;}
      else if(bOLMTjYpUI == PuarnWUgLn){dCTkdsjWHM = true;}
      if(XwHtQgdkun == FRIXdrOQqN){CRhspxfzuU = true;}
      else if(FRIXdrOQqN == XwHtQgdkun){qFyEAlQCyr = true;}
      if(lsxudnKtjX == XFxiYSShQH){CcxQiCDrhj = true;}
      else if(XFxiYSShQH == lsxudnKtjX){jbRZlRZSiQ = true;}
      if(RUkCQtxmAu == lakDOFIzMM){SxXktFcKRq = true;}
      else if(lakDOFIzMM == RUkCQtxmAu){WyAphCQkFb = true;}
      if(dycRXmTpiD == jokynfIzXq){VIzupWySVy = true;}
      if(aIofwVxfOz == ojyguWQbmA){NQaGGVHZQE = true;}
      if(MZxnWDKEdW == QpYNWegEIX){WmkTsFswyj = true;}
      while(jokynfIzXq == dycRXmTpiD){RyJShsDoNh = true;}
      while(ojyguWQbmA == ojyguWQbmA){QUgJACktzL = true;}
      while(QpYNWegEIX == QpYNWegEIX){SQmqorEIWx = true;}
      if(iOEddiTzts == true){iOEddiTzts = false;}
      if(JSKZRBbDHr == true){JSKZRBbDHr = false;}
      if(ofLLwsPWaJ == true){ofLLwsPWaJ = false;}
      if(zEpzHZfTDM == true){zEpzHZfTDM = false;}
      if(CRhspxfzuU == true){CRhspxfzuU = false;}
      if(CcxQiCDrhj == true){CcxQiCDrhj = false;}
      if(SxXktFcKRq == true){SxXktFcKRq = false;}
      if(VIzupWySVy == true){VIzupWySVy = false;}
      if(NQaGGVHZQE == true){NQaGGVHZQE = false;}
      if(WmkTsFswyj == true){WmkTsFswyj = false;}
      if(UUgEytdBaL == true){UUgEytdBaL = false;}
      if(EjWiVBVReY == true){EjWiVBVReY = false;}
      if(yCtNUhWeBj == true){yCtNUhWeBj = false;}
      if(dCTkdsjWHM == true){dCTkdsjWHM = false;}
      if(qFyEAlQCyr == true){qFyEAlQCyr = false;}
      if(jbRZlRZSiQ == true){jbRZlRZSiQ = false;}
      if(WyAphCQkFb == true){WyAphCQkFb = false;}
      if(RyJShsDoNh == true){RyJShsDoNh = false;}
      if(QUgJACktzL == true){QUgJACktzL = false;}
      if(SQmqorEIWx == true){SQmqorEIWx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DFSHDNSHLG
{ 
  void QKYgmLsLTG()
  { 
      bool baLPhXpRox = false;
      bool iNSpJtudWQ = false;
      bool DZInWkjtjK = false;
      bool RfxdjADcOF = false;
      bool lDUmLxbkDQ = false;
      bool eWzoIBRWsx = false;
      bool mwhdfDPoFI = false;
      bool qROQdzFVbY = false;
      bool JzqSftfIUi = false;
      bool ifjRRpVpGI = false;
      bool hlftZMHhLI = false;
      bool wwtUmnFOxk = false;
      bool WHTWZLhwzn = false;
      bool dOPTpWSwsT = false;
      bool myxLlmkPec = false;
      bool jGrUkaSJTN = false;
      bool dLhWehfadQ = false;
      bool VIVdyYKHjm = false;
      bool aSRWDXVthP = false;
      bool EJbeobPZgE = false;
      string YUcDEYaPUa;
      string UttwQdTRhG;
      string TzmZDuzhbR;
      string cMlUWNRGRX;
      string SpiZQQwKdt;
      string efxByZgDzJ;
      string YsmDxHIZYD;
      string LNzKmdPMIm;
      string yoDglwOjVw;
      string fOGIyZDebI;
      string IVkZiQgmNU;
      string KUtMKjoFQB;
      string sXEbXxHqLN;
      string ajkAecDdyU;
      string PbVAlLUsxO;
      string jxOaPjRICl;
      string JoaAtZjshh;
      string fLGwkRBEpM;
      string bOsxdcVJkt;
      string KtaMLaAVGM;
      if(YUcDEYaPUa == IVkZiQgmNU){baLPhXpRox = true;}
      else if(IVkZiQgmNU == YUcDEYaPUa){hlftZMHhLI = true;}
      if(UttwQdTRhG == KUtMKjoFQB){iNSpJtudWQ = true;}
      else if(KUtMKjoFQB == UttwQdTRhG){wwtUmnFOxk = true;}
      if(TzmZDuzhbR == sXEbXxHqLN){DZInWkjtjK = true;}
      else if(sXEbXxHqLN == TzmZDuzhbR){WHTWZLhwzn = true;}
      if(cMlUWNRGRX == ajkAecDdyU){RfxdjADcOF = true;}
      else if(ajkAecDdyU == cMlUWNRGRX){dOPTpWSwsT = true;}
      if(SpiZQQwKdt == PbVAlLUsxO){lDUmLxbkDQ = true;}
      else if(PbVAlLUsxO == SpiZQQwKdt){myxLlmkPec = true;}
      if(efxByZgDzJ == jxOaPjRICl){eWzoIBRWsx = true;}
      else if(jxOaPjRICl == efxByZgDzJ){jGrUkaSJTN = true;}
      if(YsmDxHIZYD == JoaAtZjshh){mwhdfDPoFI = true;}
      else if(JoaAtZjshh == YsmDxHIZYD){dLhWehfadQ = true;}
      if(LNzKmdPMIm == fLGwkRBEpM){qROQdzFVbY = true;}
      if(yoDglwOjVw == bOsxdcVJkt){JzqSftfIUi = true;}
      if(fOGIyZDebI == KtaMLaAVGM){ifjRRpVpGI = true;}
      while(fLGwkRBEpM == LNzKmdPMIm){VIVdyYKHjm = true;}
      while(bOsxdcVJkt == bOsxdcVJkt){aSRWDXVthP = true;}
      while(KtaMLaAVGM == KtaMLaAVGM){EJbeobPZgE = true;}
      if(baLPhXpRox == true){baLPhXpRox = false;}
      if(iNSpJtudWQ == true){iNSpJtudWQ = false;}
      if(DZInWkjtjK == true){DZInWkjtjK = false;}
      if(RfxdjADcOF == true){RfxdjADcOF = false;}
      if(lDUmLxbkDQ == true){lDUmLxbkDQ = false;}
      if(eWzoIBRWsx == true){eWzoIBRWsx = false;}
      if(mwhdfDPoFI == true){mwhdfDPoFI = false;}
      if(qROQdzFVbY == true){qROQdzFVbY = false;}
      if(JzqSftfIUi == true){JzqSftfIUi = false;}
      if(ifjRRpVpGI == true){ifjRRpVpGI = false;}
      if(hlftZMHhLI == true){hlftZMHhLI = false;}
      if(wwtUmnFOxk == true){wwtUmnFOxk = false;}
      if(WHTWZLhwzn == true){WHTWZLhwzn = false;}
      if(dOPTpWSwsT == true){dOPTpWSwsT = false;}
      if(myxLlmkPec == true){myxLlmkPec = false;}
      if(jGrUkaSJTN == true){jGrUkaSJTN = false;}
      if(dLhWehfadQ == true){dLhWehfadQ = false;}
      if(VIVdyYKHjm == true){VIVdyYKHjm = false;}
      if(aSRWDXVthP == true){aSRWDXVthP = false;}
      if(EJbeobPZgE == true){EJbeobPZgE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TBATWORFKH
{ 
  void uaKsEWiVjd()
  { 
      bool EUIEnAgilN = false;
      bool HTNeepClrb = false;
      bool DhVaLXnQct = false;
      bool OFidgdpMUg = false;
      bool LjdNRmwruF = false;
      bool DOFnfVyhrQ = false;
      bool LQFryCjjyA = false;
      bool AoRKPTDHIY = false;
      bool awUXpzzuyK = false;
      bool eITDVudkPP = false;
      bool DMsuENxtXM = false;
      bool RqYToOwgBy = false;
      bool ColnUqUNoT = false;
      bool oRqrUOCYSc = false;
      bool CFWlrniANG = false;
      bool zxjQMNaFZN = false;
      bool riEEWAzfya = false;
      bool MWNYwxRzug = false;
      bool IUAiUrhafH = false;
      bool nwzFkSASOr = false;
      string orEYKGeSXF;
      string zcFPLtBwRF;
      string yAdLTnCnZg;
      string ySNxrSLzou;
      string BMIQTzKTxb;
      string zQxXYoOsFW;
      string DpsqGgPHWr;
      string hCHWElrMqT;
      string ciqxghVpXD;
      string EStRqKTQKm;
      string jCwEsxIZSm;
      string xBBksUzuJX;
      string KZjTnPHoes;
      string RaCEjZlmDj;
      string YuWkGDRJXW;
      string LYHlcKSbPc;
      string oTtZUWyxAT;
      string hLqYzPCzNk;
      string yyQIgsSQaZ;
      string HKWauFAxPi;
      if(orEYKGeSXF == jCwEsxIZSm){EUIEnAgilN = true;}
      else if(jCwEsxIZSm == orEYKGeSXF){DMsuENxtXM = true;}
      if(zcFPLtBwRF == xBBksUzuJX){HTNeepClrb = true;}
      else if(xBBksUzuJX == zcFPLtBwRF){RqYToOwgBy = true;}
      if(yAdLTnCnZg == KZjTnPHoes){DhVaLXnQct = true;}
      else if(KZjTnPHoes == yAdLTnCnZg){ColnUqUNoT = true;}
      if(ySNxrSLzou == RaCEjZlmDj){OFidgdpMUg = true;}
      else if(RaCEjZlmDj == ySNxrSLzou){oRqrUOCYSc = true;}
      if(BMIQTzKTxb == YuWkGDRJXW){LjdNRmwruF = true;}
      else if(YuWkGDRJXW == BMIQTzKTxb){CFWlrniANG = true;}
      if(zQxXYoOsFW == LYHlcKSbPc){DOFnfVyhrQ = true;}
      else if(LYHlcKSbPc == zQxXYoOsFW){zxjQMNaFZN = true;}
      if(DpsqGgPHWr == oTtZUWyxAT){LQFryCjjyA = true;}
      else if(oTtZUWyxAT == DpsqGgPHWr){riEEWAzfya = true;}
      if(hCHWElrMqT == hLqYzPCzNk){AoRKPTDHIY = true;}
      if(ciqxghVpXD == yyQIgsSQaZ){awUXpzzuyK = true;}
      if(EStRqKTQKm == HKWauFAxPi){eITDVudkPP = true;}
      while(hLqYzPCzNk == hCHWElrMqT){MWNYwxRzug = true;}
      while(yyQIgsSQaZ == yyQIgsSQaZ){IUAiUrhafH = true;}
      while(HKWauFAxPi == HKWauFAxPi){nwzFkSASOr = true;}
      if(EUIEnAgilN == true){EUIEnAgilN = false;}
      if(HTNeepClrb == true){HTNeepClrb = false;}
      if(DhVaLXnQct == true){DhVaLXnQct = false;}
      if(OFidgdpMUg == true){OFidgdpMUg = false;}
      if(LjdNRmwruF == true){LjdNRmwruF = false;}
      if(DOFnfVyhrQ == true){DOFnfVyhrQ = false;}
      if(LQFryCjjyA == true){LQFryCjjyA = false;}
      if(AoRKPTDHIY == true){AoRKPTDHIY = false;}
      if(awUXpzzuyK == true){awUXpzzuyK = false;}
      if(eITDVudkPP == true){eITDVudkPP = false;}
      if(DMsuENxtXM == true){DMsuENxtXM = false;}
      if(RqYToOwgBy == true){RqYToOwgBy = false;}
      if(ColnUqUNoT == true){ColnUqUNoT = false;}
      if(oRqrUOCYSc == true){oRqrUOCYSc = false;}
      if(CFWlrniANG == true){CFWlrniANG = false;}
      if(zxjQMNaFZN == true){zxjQMNaFZN = false;}
      if(riEEWAzfya == true){riEEWAzfya = false;}
      if(MWNYwxRzug == true){MWNYwxRzug = false;}
      if(IUAiUrhafH == true){IUAiUrhafH = false;}
      if(nwzFkSASOr == true){nwzFkSASOr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PNHIQJJTAZ
{ 
  void YUsomisKZN()
  { 
      bool sOVhAZVSur = false;
      bool VrXHPkJHlM = false;
      bool NlIpxGSaMq = false;
      bool yyHsWFxaHd = false;
      bool bBZGFucEby = false;
      bool uQKeCHGfks = false;
      bool HuFEtWkekK = false;
      bool nizHjMLBjB = false;
      bool dOyOugmbpO = false;
      bool yRpNWguVLh = false;
      bool JxSRJMRDup = false;
      bool uEuiOsxpIN = false;
      bool jJnVLVrkkC = false;
      bool QpoBqfufEi = false;
      bool PjgATtVHzd = false;
      bool jFMyyAIwGn = false;
      bool TfRrZFOtqi = false;
      bool xQlZyzbnCQ = false;
      bool AklHSLdqDp = false;
      bool WzYQOiRnaN = false;
      string UWxEHouLBQ;
      string liUhIlylVn;
      string DVanGSdFNP;
      string cJPTNTCuZI;
      string JglAAQtIeK;
      string OIrcTzwJyo;
      string LoxlnbTBUo;
      string jDMNdViZmo;
      string YVZCATRlzN;
      string XswjxUiAMY;
      string xsnpaLuezx;
      string PVVIQoPtkU;
      string JgBGRqGcPJ;
      string miNOqfhjbn;
      string XmlCxBWmSH;
      string FnOqOPqgXj;
      string ESOpKgHHRk;
      string HeSwwWtyIP;
      string TTJHEyTVza;
      string nALriFXwqP;
      if(UWxEHouLBQ == xsnpaLuezx){sOVhAZVSur = true;}
      else if(xsnpaLuezx == UWxEHouLBQ){JxSRJMRDup = true;}
      if(liUhIlylVn == PVVIQoPtkU){VrXHPkJHlM = true;}
      else if(PVVIQoPtkU == liUhIlylVn){uEuiOsxpIN = true;}
      if(DVanGSdFNP == JgBGRqGcPJ){NlIpxGSaMq = true;}
      else if(JgBGRqGcPJ == DVanGSdFNP){jJnVLVrkkC = true;}
      if(cJPTNTCuZI == miNOqfhjbn){yyHsWFxaHd = true;}
      else if(miNOqfhjbn == cJPTNTCuZI){QpoBqfufEi = true;}
      if(JglAAQtIeK == XmlCxBWmSH){bBZGFucEby = true;}
      else if(XmlCxBWmSH == JglAAQtIeK){PjgATtVHzd = true;}
      if(OIrcTzwJyo == FnOqOPqgXj){uQKeCHGfks = true;}
      else if(FnOqOPqgXj == OIrcTzwJyo){jFMyyAIwGn = true;}
      if(LoxlnbTBUo == ESOpKgHHRk){HuFEtWkekK = true;}
      else if(ESOpKgHHRk == LoxlnbTBUo){TfRrZFOtqi = true;}
      if(jDMNdViZmo == HeSwwWtyIP){nizHjMLBjB = true;}
      if(YVZCATRlzN == TTJHEyTVza){dOyOugmbpO = true;}
      if(XswjxUiAMY == nALriFXwqP){yRpNWguVLh = true;}
      while(HeSwwWtyIP == jDMNdViZmo){xQlZyzbnCQ = true;}
      while(TTJHEyTVza == TTJHEyTVza){AklHSLdqDp = true;}
      while(nALriFXwqP == nALriFXwqP){WzYQOiRnaN = true;}
      if(sOVhAZVSur == true){sOVhAZVSur = false;}
      if(VrXHPkJHlM == true){VrXHPkJHlM = false;}
      if(NlIpxGSaMq == true){NlIpxGSaMq = false;}
      if(yyHsWFxaHd == true){yyHsWFxaHd = false;}
      if(bBZGFucEby == true){bBZGFucEby = false;}
      if(uQKeCHGfks == true){uQKeCHGfks = false;}
      if(HuFEtWkekK == true){HuFEtWkekK = false;}
      if(nizHjMLBjB == true){nizHjMLBjB = false;}
      if(dOyOugmbpO == true){dOyOugmbpO = false;}
      if(yRpNWguVLh == true){yRpNWguVLh = false;}
      if(JxSRJMRDup == true){JxSRJMRDup = false;}
      if(uEuiOsxpIN == true){uEuiOsxpIN = false;}
      if(jJnVLVrkkC == true){jJnVLVrkkC = false;}
      if(QpoBqfufEi == true){QpoBqfufEi = false;}
      if(PjgATtVHzd == true){PjgATtVHzd = false;}
      if(jFMyyAIwGn == true){jFMyyAIwGn = false;}
      if(TfRrZFOtqi == true){TfRrZFOtqi = false;}
      if(xQlZyzbnCQ == true){xQlZyzbnCQ = false;}
      if(AklHSLdqDp == true){AklHSLdqDp = false;}
      if(WzYQOiRnaN == true){WzYQOiRnaN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENRGHOVNJF
{ 
  void WmftAJJZhq()
  { 
      bool eUSBnFXTOq = false;
      bool bzCPnOqVPU = false;
      bool TmdJFYUgjs = false;
      bool MZiWGOQRDh = false;
      bool cpryWGYHMz = false;
      bool PLCVKqqJwP = false;
      bool kpiUdCPfIY = false;
      bool yYRgrdtely = false;
      bool zMUjcAWNMP = false;
      bool XGVmxlGXTU = false;
      bool qsymBqtVdf = false;
      bool wMXxQXVzqd = false;
      bool eCSsBrCdjG = false;
      bool XWKQHGNhil = false;
      bool GBifSKhYWY = false;
      bool QGfpooZFkJ = false;
      bool nPkWHZBGoJ = false;
      bool JnQFXdSlZp = false;
      bool JdGLoQqUbS = false;
      bool gIwYypPMYs = false;
      string iVCgaRyJcM;
      string WVPFCjtbCQ;
      string MUGHEonwdu;
      string lpykdDcfpz;
      string QsMFHEsqKF;
      string YcyowOPtbl;
      string dCfhagWday;
      string HOkDATHAAA;
      string uwkXWJqJoP;
      string nhDEVONeeZ;
      string gOPLyJrunb;
      string GOsbqgQHLQ;
      string oMoKKYLggk;
      string GcUZSfgYZM;
      string RuUNIYnbMo;
      string xFSNkTZEBY;
      string yKNDVdtSIK;
      string ArhyzsraCk;
      string jiTrnAJGoz;
      string FbXAOGgRqe;
      if(iVCgaRyJcM == gOPLyJrunb){eUSBnFXTOq = true;}
      else if(gOPLyJrunb == iVCgaRyJcM){qsymBqtVdf = true;}
      if(WVPFCjtbCQ == GOsbqgQHLQ){bzCPnOqVPU = true;}
      else if(GOsbqgQHLQ == WVPFCjtbCQ){wMXxQXVzqd = true;}
      if(MUGHEonwdu == oMoKKYLggk){TmdJFYUgjs = true;}
      else if(oMoKKYLggk == MUGHEonwdu){eCSsBrCdjG = true;}
      if(lpykdDcfpz == GcUZSfgYZM){MZiWGOQRDh = true;}
      else if(GcUZSfgYZM == lpykdDcfpz){XWKQHGNhil = true;}
      if(QsMFHEsqKF == RuUNIYnbMo){cpryWGYHMz = true;}
      else if(RuUNIYnbMo == QsMFHEsqKF){GBifSKhYWY = true;}
      if(YcyowOPtbl == xFSNkTZEBY){PLCVKqqJwP = true;}
      else if(xFSNkTZEBY == YcyowOPtbl){QGfpooZFkJ = true;}
      if(dCfhagWday == yKNDVdtSIK){kpiUdCPfIY = true;}
      else if(yKNDVdtSIK == dCfhagWday){nPkWHZBGoJ = true;}
      if(HOkDATHAAA == ArhyzsraCk){yYRgrdtely = true;}
      if(uwkXWJqJoP == jiTrnAJGoz){zMUjcAWNMP = true;}
      if(nhDEVONeeZ == FbXAOGgRqe){XGVmxlGXTU = true;}
      while(ArhyzsraCk == HOkDATHAAA){JnQFXdSlZp = true;}
      while(jiTrnAJGoz == jiTrnAJGoz){JdGLoQqUbS = true;}
      while(FbXAOGgRqe == FbXAOGgRqe){gIwYypPMYs = true;}
      if(eUSBnFXTOq == true){eUSBnFXTOq = false;}
      if(bzCPnOqVPU == true){bzCPnOqVPU = false;}
      if(TmdJFYUgjs == true){TmdJFYUgjs = false;}
      if(MZiWGOQRDh == true){MZiWGOQRDh = false;}
      if(cpryWGYHMz == true){cpryWGYHMz = false;}
      if(PLCVKqqJwP == true){PLCVKqqJwP = false;}
      if(kpiUdCPfIY == true){kpiUdCPfIY = false;}
      if(yYRgrdtely == true){yYRgrdtely = false;}
      if(zMUjcAWNMP == true){zMUjcAWNMP = false;}
      if(XGVmxlGXTU == true){XGVmxlGXTU = false;}
      if(qsymBqtVdf == true){qsymBqtVdf = false;}
      if(wMXxQXVzqd == true){wMXxQXVzqd = false;}
      if(eCSsBrCdjG == true){eCSsBrCdjG = false;}
      if(XWKQHGNhil == true){XWKQHGNhil = false;}
      if(GBifSKhYWY == true){GBifSKhYWY = false;}
      if(QGfpooZFkJ == true){QGfpooZFkJ = false;}
      if(nPkWHZBGoJ == true){nPkWHZBGoJ = false;}
      if(JnQFXdSlZp == true){JnQFXdSlZp = false;}
      if(JdGLoQqUbS == true){JdGLoQqUbS = false;}
      if(gIwYypPMYs == true){gIwYypPMYs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZDSBBFBGDT
{ 
  void ZLRwMLUuLb()
  { 
      bool UnZOhZUgEn = false;
      bool wLWxVqxoch = false;
      bool ZUbNWHfMjN = false;
      bool HBRCRAXwXE = false;
      bool IfOgQYwyID = false;
      bool rrrkTAMMqa = false;
      bool sHwpfutTeU = false;
      bool TBQXYsGuwy = false;
      bool LhEgVOIfhR = false;
      bool nKExLAjXBV = false;
      bool ebTmiqaTLa = false;
      bool tRPsOLDPUQ = false;
      bool lNkMgIwTMX = false;
      bool JhsaSiOQxd = false;
      bool noUHXWuLhA = false;
      bool xTDjiRpGGZ = false;
      bool uHHmRLXoZe = false;
      bool wlRpcxrdoJ = false;
      bool NjlMaodIqA = false;
      bool sHKXigghpL = false;
      string XbreeBYgCJ;
      string oGIfgjQkzQ;
      string gLfAbyGGXQ;
      string VhrNGQZKrP;
      string bALwEeGWuw;
      string shtbhMwrDg;
      string uSIknHOuYP;
      string JGsiogziuw;
      string riKbWmnPft;
      string UhHLUIrZIw;
      string QLxelmoKmA;
      string MMwGnLHfOB;
      string SyPduaygOf;
      string oYZyffkfoi;
      string xcbehHlAWI;
      string BLLHdSwSjL;
      string oHuHLmmxaH;
      string ZbqeDoVjwm;
      string oxKGdcNSUN;
      string jSudtohUSt;
      if(XbreeBYgCJ == QLxelmoKmA){UnZOhZUgEn = true;}
      else if(QLxelmoKmA == XbreeBYgCJ){ebTmiqaTLa = true;}
      if(oGIfgjQkzQ == MMwGnLHfOB){wLWxVqxoch = true;}
      else if(MMwGnLHfOB == oGIfgjQkzQ){tRPsOLDPUQ = true;}
      if(gLfAbyGGXQ == SyPduaygOf){ZUbNWHfMjN = true;}
      else if(SyPduaygOf == gLfAbyGGXQ){lNkMgIwTMX = true;}
      if(VhrNGQZKrP == oYZyffkfoi){HBRCRAXwXE = true;}
      else if(oYZyffkfoi == VhrNGQZKrP){JhsaSiOQxd = true;}
      if(bALwEeGWuw == xcbehHlAWI){IfOgQYwyID = true;}
      else if(xcbehHlAWI == bALwEeGWuw){noUHXWuLhA = true;}
      if(shtbhMwrDg == BLLHdSwSjL){rrrkTAMMqa = true;}
      else if(BLLHdSwSjL == shtbhMwrDg){xTDjiRpGGZ = true;}
      if(uSIknHOuYP == oHuHLmmxaH){sHwpfutTeU = true;}
      else if(oHuHLmmxaH == uSIknHOuYP){uHHmRLXoZe = true;}
      if(JGsiogziuw == ZbqeDoVjwm){TBQXYsGuwy = true;}
      if(riKbWmnPft == oxKGdcNSUN){LhEgVOIfhR = true;}
      if(UhHLUIrZIw == jSudtohUSt){nKExLAjXBV = true;}
      while(ZbqeDoVjwm == JGsiogziuw){wlRpcxrdoJ = true;}
      while(oxKGdcNSUN == oxKGdcNSUN){NjlMaodIqA = true;}
      while(jSudtohUSt == jSudtohUSt){sHKXigghpL = true;}
      if(UnZOhZUgEn == true){UnZOhZUgEn = false;}
      if(wLWxVqxoch == true){wLWxVqxoch = false;}
      if(ZUbNWHfMjN == true){ZUbNWHfMjN = false;}
      if(HBRCRAXwXE == true){HBRCRAXwXE = false;}
      if(IfOgQYwyID == true){IfOgQYwyID = false;}
      if(rrrkTAMMqa == true){rrrkTAMMqa = false;}
      if(sHwpfutTeU == true){sHwpfutTeU = false;}
      if(TBQXYsGuwy == true){TBQXYsGuwy = false;}
      if(LhEgVOIfhR == true){LhEgVOIfhR = false;}
      if(nKExLAjXBV == true){nKExLAjXBV = false;}
      if(ebTmiqaTLa == true){ebTmiqaTLa = false;}
      if(tRPsOLDPUQ == true){tRPsOLDPUQ = false;}
      if(lNkMgIwTMX == true){lNkMgIwTMX = false;}
      if(JhsaSiOQxd == true){JhsaSiOQxd = false;}
      if(noUHXWuLhA == true){noUHXWuLhA = false;}
      if(xTDjiRpGGZ == true){xTDjiRpGGZ = false;}
      if(uHHmRLXoZe == true){uHHmRLXoZe = false;}
      if(wlRpcxrdoJ == true){wlRpcxrdoJ = false;}
      if(NjlMaodIqA == true){NjlMaodIqA = false;}
      if(sHKXigghpL == true){sHKXigghpL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GCKCQRIGMZ
{ 
  void PRfgeMyFPK()
  { 
      bool NAamcoyXVD = false;
      bool LjPDTbzCbJ = false;
      bool sJRWgjLhgL = false;
      bool hzHpQarrJB = false;
      bool FKaxbHabqZ = false;
      bool GNDijDhDFr = false;
      bool cQqKUMbYmr = false;
      bool jHraDhhUuZ = false;
      bool IjqGFUuXFM = false;
      bool snlQYoTQbO = false;
      bool eBoypyUceC = false;
      bool UMHfjsZjFA = false;
      bool QDTZyuVbBO = false;
      bool NRsfuHtrQG = false;
      bool zSrDqffGgf = false;
      bool PjKaxahOzt = false;
      bool csaPnDTajb = false;
      bool ygSzByKPiS = false;
      bool PPtVzdGRiT = false;
      bool YfrWcGqcOn = false;
      string cKVmFXlRFy;
      string mOlJxzDkfy;
      string ZllttknlVd;
      string jDsNNlPVgm;
      string mmLGnrQFrZ;
      string haVCxqYbrU;
      string iAwaNjVYwL;
      string ihDrKmZeGC;
      string TitwwJgqQW;
      string NncMDmqksE;
      string WrIfpzWcqJ;
      string QsUpAAFzeE;
      string CeHYytFqoX;
      string wolCebZNGw;
      string lEzGFTSlLC;
      string gqGnBqjihu;
      string tenSNbGSLY;
      string ZrshSyeATd;
      string bSelqEixAn;
      string qpfKBGPfsd;
      if(cKVmFXlRFy == WrIfpzWcqJ){NAamcoyXVD = true;}
      else if(WrIfpzWcqJ == cKVmFXlRFy){eBoypyUceC = true;}
      if(mOlJxzDkfy == QsUpAAFzeE){LjPDTbzCbJ = true;}
      else if(QsUpAAFzeE == mOlJxzDkfy){UMHfjsZjFA = true;}
      if(ZllttknlVd == CeHYytFqoX){sJRWgjLhgL = true;}
      else if(CeHYytFqoX == ZllttknlVd){QDTZyuVbBO = true;}
      if(jDsNNlPVgm == wolCebZNGw){hzHpQarrJB = true;}
      else if(wolCebZNGw == jDsNNlPVgm){NRsfuHtrQG = true;}
      if(mmLGnrQFrZ == lEzGFTSlLC){FKaxbHabqZ = true;}
      else if(lEzGFTSlLC == mmLGnrQFrZ){zSrDqffGgf = true;}
      if(haVCxqYbrU == gqGnBqjihu){GNDijDhDFr = true;}
      else if(gqGnBqjihu == haVCxqYbrU){PjKaxahOzt = true;}
      if(iAwaNjVYwL == tenSNbGSLY){cQqKUMbYmr = true;}
      else if(tenSNbGSLY == iAwaNjVYwL){csaPnDTajb = true;}
      if(ihDrKmZeGC == ZrshSyeATd){jHraDhhUuZ = true;}
      if(TitwwJgqQW == bSelqEixAn){IjqGFUuXFM = true;}
      if(NncMDmqksE == qpfKBGPfsd){snlQYoTQbO = true;}
      while(ZrshSyeATd == ihDrKmZeGC){ygSzByKPiS = true;}
      while(bSelqEixAn == bSelqEixAn){PPtVzdGRiT = true;}
      while(qpfKBGPfsd == qpfKBGPfsd){YfrWcGqcOn = true;}
      if(NAamcoyXVD == true){NAamcoyXVD = false;}
      if(LjPDTbzCbJ == true){LjPDTbzCbJ = false;}
      if(sJRWgjLhgL == true){sJRWgjLhgL = false;}
      if(hzHpQarrJB == true){hzHpQarrJB = false;}
      if(FKaxbHabqZ == true){FKaxbHabqZ = false;}
      if(GNDijDhDFr == true){GNDijDhDFr = false;}
      if(cQqKUMbYmr == true){cQqKUMbYmr = false;}
      if(jHraDhhUuZ == true){jHraDhhUuZ = false;}
      if(IjqGFUuXFM == true){IjqGFUuXFM = false;}
      if(snlQYoTQbO == true){snlQYoTQbO = false;}
      if(eBoypyUceC == true){eBoypyUceC = false;}
      if(UMHfjsZjFA == true){UMHfjsZjFA = false;}
      if(QDTZyuVbBO == true){QDTZyuVbBO = false;}
      if(NRsfuHtrQG == true){NRsfuHtrQG = false;}
      if(zSrDqffGgf == true){zSrDqffGgf = false;}
      if(PjKaxahOzt == true){PjKaxahOzt = false;}
      if(csaPnDTajb == true){csaPnDTajb = false;}
      if(ygSzByKPiS == true){ygSzByKPiS = false;}
      if(PPtVzdGRiT == true){PPtVzdGRiT = false;}
      if(YfrWcGqcOn == true){YfrWcGqcOn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IANUJODCSS
{ 
  void CzeaFsMAjj()
  { 
      bool gaEBLMBWMS = false;
      bool VZMmtjNgRp = false;
      bool YZCXzYRmrZ = false;
      bool RPucUHCCeh = false;
      bool bKlhwAiMos = false;
      bool aleCTGXgCm = false;
      bool tOemBGeiSl = false;
      bool hKBiNOnUbz = false;
      bool pFyzyfjsIN = false;
      bool iVArmNezgo = false;
      bool UzsCKPjunF = false;
      bool RCECwoPfnU = false;
      bool VlaFDLKJwA = false;
      bool jonmepLuni = false;
      bool uoFCufRyux = false;
      bool xyKLSiXnyz = false;
      bool FazmVcORXG = false;
      bool dTrFYggXJX = false;
      bool tLNyDkdcTu = false;
      bool RWxncUoRgR = false;
      string nXgHKVndEL;
      string JDrXnhOdQo;
      string zzBlQuousx;
      string fppLVbgaGM;
      string dqpdAPtGJq;
      string hXBwdoWtpP;
      string gsjGeSNgCM;
      string AmXDKIIXlB;
      string BhlCPIosgf;
      string EmjpekGiyg;
      string BMEwptAxkV;
      string fyIoOyGhqW;
      string cTzVHNCgXY;
      string BZZEzndoLV;
      string IrILzFeubg;
      string dXraDgNhoc;
      string rSYLTGYDpZ;
      string URWUOkLmVB;
      string iHEqtdgyAR;
      string ZuAicoTwrs;
      if(nXgHKVndEL == BMEwptAxkV){gaEBLMBWMS = true;}
      else if(BMEwptAxkV == nXgHKVndEL){UzsCKPjunF = true;}
      if(JDrXnhOdQo == fyIoOyGhqW){VZMmtjNgRp = true;}
      else if(fyIoOyGhqW == JDrXnhOdQo){RCECwoPfnU = true;}
      if(zzBlQuousx == cTzVHNCgXY){YZCXzYRmrZ = true;}
      else if(cTzVHNCgXY == zzBlQuousx){VlaFDLKJwA = true;}
      if(fppLVbgaGM == BZZEzndoLV){RPucUHCCeh = true;}
      else if(BZZEzndoLV == fppLVbgaGM){jonmepLuni = true;}
      if(dqpdAPtGJq == IrILzFeubg){bKlhwAiMos = true;}
      else if(IrILzFeubg == dqpdAPtGJq){uoFCufRyux = true;}
      if(hXBwdoWtpP == dXraDgNhoc){aleCTGXgCm = true;}
      else if(dXraDgNhoc == hXBwdoWtpP){xyKLSiXnyz = true;}
      if(gsjGeSNgCM == rSYLTGYDpZ){tOemBGeiSl = true;}
      else if(rSYLTGYDpZ == gsjGeSNgCM){FazmVcORXG = true;}
      if(AmXDKIIXlB == URWUOkLmVB){hKBiNOnUbz = true;}
      if(BhlCPIosgf == iHEqtdgyAR){pFyzyfjsIN = true;}
      if(EmjpekGiyg == ZuAicoTwrs){iVArmNezgo = true;}
      while(URWUOkLmVB == AmXDKIIXlB){dTrFYggXJX = true;}
      while(iHEqtdgyAR == iHEqtdgyAR){tLNyDkdcTu = true;}
      while(ZuAicoTwrs == ZuAicoTwrs){RWxncUoRgR = true;}
      if(gaEBLMBWMS == true){gaEBLMBWMS = false;}
      if(VZMmtjNgRp == true){VZMmtjNgRp = false;}
      if(YZCXzYRmrZ == true){YZCXzYRmrZ = false;}
      if(RPucUHCCeh == true){RPucUHCCeh = false;}
      if(bKlhwAiMos == true){bKlhwAiMos = false;}
      if(aleCTGXgCm == true){aleCTGXgCm = false;}
      if(tOemBGeiSl == true){tOemBGeiSl = false;}
      if(hKBiNOnUbz == true){hKBiNOnUbz = false;}
      if(pFyzyfjsIN == true){pFyzyfjsIN = false;}
      if(iVArmNezgo == true){iVArmNezgo = false;}
      if(UzsCKPjunF == true){UzsCKPjunF = false;}
      if(RCECwoPfnU == true){RCECwoPfnU = false;}
      if(VlaFDLKJwA == true){VlaFDLKJwA = false;}
      if(jonmepLuni == true){jonmepLuni = false;}
      if(uoFCufRyux == true){uoFCufRyux = false;}
      if(xyKLSiXnyz == true){xyKLSiXnyz = false;}
      if(FazmVcORXG == true){FazmVcORXG = false;}
      if(dTrFYggXJX == true){dTrFYggXJX = false;}
      if(tLNyDkdcTu == true){tLNyDkdcTu = false;}
      if(RWxncUoRgR == true){RWxncUoRgR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OTCBWCRYXP
{ 
  void jZVcICfaNs()
  { 
      bool FEBMzAncBi = false;
      bool SIOUrxMyOC = false;
      bool lMcDwMouYQ = false;
      bool PCGqQKPLeU = false;
      bool GcGBDBfEXu = false;
      bool mPHffsbxPm = false;
      bool LrEkTPCXEg = false;
      bool gBTtuJFbAu = false;
      bool gkXcczuZLX = false;
      bool iSurJNXVhm = false;
      bool zIzpOlwNjV = false;
      bool mAwTGZUbHT = false;
      bool UbLgyNFakh = false;
      bool ljsMwXkgNq = false;
      bool CgoojiVaki = false;
      bool ruNNSWwSrA = false;
      bool fVcCjCGiWh = false;
      bool onNQRmlWwO = false;
      bool rdoBopVftZ = false;
      bool bRoNKgEmFh = false;
      string qKstWjnOQW;
      string fjfxYhwqDG;
      string HbWzTjpGQc;
      string KyboUHWoTe;
      string bfHdRgKYDB;
      string OzozROmsZm;
      string thxmLgIqbQ;
      string LHXXebUrhl;
      string ZRCOOLJbWF;
      string UcOfkthTSj;
      string YSwmpHaQUp;
      string ttLmNceiYA;
      string WfUWuhrqmj;
      string sBZxNGUPXH;
      string jrGfLZRaSH;
      string OyuRNrxZqI;
      string OjdjxsUNZG;
      string HOKRQdYoKV;
      string PRXeVtGHjV;
      string JuYPrzOWiS;
      if(qKstWjnOQW == YSwmpHaQUp){FEBMzAncBi = true;}
      else if(YSwmpHaQUp == qKstWjnOQW){zIzpOlwNjV = true;}
      if(fjfxYhwqDG == ttLmNceiYA){SIOUrxMyOC = true;}
      else if(ttLmNceiYA == fjfxYhwqDG){mAwTGZUbHT = true;}
      if(HbWzTjpGQc == WfUWuhrqmj){lMcDwMouYQ = true;}
      else if(WfUWuhrqmj == HbWzTjpGQc){UbLgyNFakh = true;}
      if(KyboUHWoTe == sBZxNGUPXH){PCGqQKPLeU = true;}
      else if(sBZxNGUPXH == KyboUHWoTe){ljsMwXkgNq = true;}
      if(bfHdRgKYDB == jrGfLZRaSH){GcGBDBfEXu = true;}
      else if(jrGfLZRaSH == bfHdRgKYDB){CgoojiVaki = true;}
      if(OzozROmsZm == OyuRNrxZqI){mPHffsbxPm = true;}
      else if(OyuRNrxZqI == OzozROmsZm){ruNNSWwSrA = true;}
      if(thxmLgIqbQ == OjdjxsUNZG){LrEkTPCXEg = true;}
      else if(OjdjxsUNZG == thxmLgIqbQ){fVcCjCGiWh = true;}
      if(LHXXebUrhl == HOKRQdYoKV){gBTtuJFbAu = true;}
      if(ZRCOOLJbWF == PRXeVtGHjV){gkXcczuZLX = true;}
      if(UcOfkthTSj == JuYPrzOWiS){iSurJNXVhm = true;}
      while(HOKRQdYoKV == LHXXebUrhl){onNQRmlWwO = true;}
      while(PRXeVtGHjV == PRXeVtGHjV){rdoBopVftZ = true;}
      while(JuYPrzOWiS == JuYPrzOWiS){bRoNKgEmFh = true;}
      if(FEBMzAncBi == true){FEBMzAncBi = false;}
      if(SIOUrxMyOC == true){SIOUrxMyOC = false;}
      if(lMcDwMouYQ == true){lMcDwMouYQ = false;}
      if(PCGqQKPLeU == true){PCGqQKPLeU = false;}
      if(GcGBDBfEXu == true){GcGBDBfEXu = false;}
      if(mPHffsbxPm == true){mPHffsbxPm = false;}
      if(LrEkTPCXEg == true){LrEkTPCXEg = false;}
      if(gBTtuJFbAu == true){gBTtuJFbAu = false;}
      if(gkXcczuZLX == true){gkXcczuZLX = false;}
      if(iSurJNXVhm == true){iSurJNXVhm = false;}
      if(zIzpOlwNjV == true){zIzpOlwNjV = false;}
      if(mAwTGZUbHT == true){mAwTGZUbHT = false;}
      if(UbLgyNFakh == true){UbLgyNFakh = false;}
      if(ljsMwXkgNq == true){ljsMwXkgNq = false;}
      if(CgoojiVaki == true){CgoojiVaki = false;}
      if(ruNNSWwSrA == true){ruNNSWwSrA = false;}
      if(fVcCjCGiWh == true){fVcCjCGiWh = false;}
      if(onNQRmlWwO == true){onNQRmlWwO = false;}
      if(rdoBopVftZ == true){rdoBopVftZ = false;}
      if(bRoNKgEmFh == true){bRoNKgEmFh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YEHZQDVULV
{ 
  void FWqwpcsHMm()
  { 
      bool ObEOUeRheR = false;
      bool FdQjepaHFA = false;
      bool uKLdDrqQWV = false;
      bool fVAtsZpFtp = false;
      bool IGeAsMpOml = false;
      bool YFGqtDQaKb = false;
      bool mBLJljcVpE = false;
      bool zVMOrofLjq = false;
      bool BbcjwZOJAp = false;
      bool JPtRCGuVOJ = false;
      bool iTYhlDsqzF = false;
      bool XFpTaLXaMM = false;
      bool UTVAujauMk = false;
      bool sKwaIhCuys = false;
      bool gXKtSEYaqp = false;
      bool iUIBnOyYmC = false;
      bool cxdOLMIPLr = false;
      bool IccTfwJagp = false;
      bool LzEVBYBtls = false;
      bool jdIuPisuhF = false;
      string cHrYGNinFh;
      string WdHCoMcNXH;
      string XDrTREfXKP;
      string rGKdHfmDSK;
      string NMkLDZJIuR;
      string mURILZOXGB;
      string gKcppQTctJ;
      string YYtMsKRgPr;
      string tXcsbWnBSh;
      string QPwQdDjuUm;
      string FgNkrNZFPA;
      string HgHOHJhiNS;
      string bSKLrJcdip;
      string aWLclNJqAN;
      string wikRajHgJU;
      string UAhBKmWCrh;
      string kwVZZkUect;
      string zpizWsgrkI;
      string CuUOUZoJSz;
      string pHzScAMLqp;
      if(cHrYGNinFh == FgNkrNZFPA){ObEOUeRheR = true;}
      else if(FgNkrNZFPA == cHrYGNinFh){iTYhlDsqzF = true;}
      if(WdHCoMcNXH == HgHOHJhiNS){FdQjepaHFA = true;}
      else if(HgHOHJhiNS == WdHCoMcNXH){XFpTaLXaMM = true;}
      if(XDrTREfXKP == bSKLrJcdip){uKLdDrqQWV = true;}
      else if(bSKLrJcdip == XDrTREfXKP){UTVAujauMk = true;}
      if(rGKdHfmDSK == aWLclNJqAN){fVAtsZpFtp = true;}
      else if(aWLclNJqAN == rGKdHfmDSK){sKwaIhCuys = true;}
      if(NMkLDZJIuR == wikRajHgJU){IGeAsMpOml = true;}
      else if(wikRajHgJU == NMkLDZJIuR){gXKtSEYaqp = true;}
      if(mURILZOXGB == UAhBKmWCrh){YFGqtDQaKb = true;}
      else if(UAhBKmWCrh == mURILZOXGB){iUIBnOyYmC = true;}
      if(gKcppQTctJ == kwVZZkUect){mBLJljcVpE = true;}
      else if(kwVZZkUect == gKcppQTctJ){cxdOLMIPLr = true;}
      if(YYtMsKRgPr == zpizWsgrkI){zVMOrofLjq = true;}
      if(tXcsbWnBSh == CuUOUZoJSz){BbcjwZOJAp = true;}
      if(QPwQdDjuUm == pHzScAMLqp){JPtRCGuVOJ = true;}
      while(zpizWsgrkI == YYtMsKRgPr){IccTfwJagp = true;}
      while(CuUOUZoJSz == CuUOUZoJSz){LzEVBYBtls = true;}
      while(pHzScAMLqp == pHzScAMLqp){jdIuPisuhF = true;}
      if(ObEOUeRheR == true){ObEOUeRheR = false;}
      if(FdQjepaHFA == true){FdQjepaHFA = false;}
      if(uKLdDrqQWV == true){uKLdDrqQWV = false;}
      if(fVAtsZpFtp == true){fVAtsZpFtp = false;}
      if(IGeAsMpOml == true){IGeAsMpOml = false;}
      if(YFGqtDQaKb == true){YFGqtDQaKb = false;}
      if(mBLJljcVpE == true){mBLJljcVpE = false;}
      if(zVMOrofLjq == true){zVMOrofLjq = false;}
      if(BbcjwZOJAp == true){BbcjwZOJAp = false;}
      if(JPtRCGuVOJ == true){JPtRCGuVOJ = false;}
      if(iTYhlDsqzF == true){iTYhlDsqzF = false;}
      if(XFpTaLXaMM == true){XFpTaLXaMM = false;}
      if(UTVAujauMk == true){UTVAujauMk = false;}
      if(sKwaIhCuys == true){sKwaIhCuys = false;}
      if(gXKtSEYaqp == true){gXKtSEYaqp = false;}
      if(iUIBnOyYmC == true){iUIBnOyYmC = false;}
      if(cxdOLMIPLr == true){cxdOLMIPLr = false;}
      if(IccTfwJagp == true){IccTfwJagp = false;}
      if(LzEVBYBtls == true){LzEVBYBtls = false;}
      if(jdIuPisuhF == true){jdIuPisuhF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVLUBHDYFW
{ 
  void HrJbaCSoLA()
  { 
      bool RHIoSaCoUa = false;
      bool kCxXJTuxNy = false;
      bool RdckUJQEGL = false;
      bool yksAkrftfz = false;
      bool nhrZhuJbQh = false;
      bool bKbaQmdWUJ = false;
      bool JxiIczIwlR = false;
      bool mAQNJilCDZ = false;
      bool zonXjmISjy = false;
      bool NIYWppziwh = false;
      bool lNoytasOQg = false;
      bool BaTuJTIKXp = false;
      bool qpLnEdatXS = false;
      bool jCFVmkApdI = false;
      bool stBCwlodNV = false;
      bool hnLGpwBAtP = false;
      bool zzpxwyUyHX = false;
      bool TSgPwxnIqR = false;
      bool oxgBkwqzeq = false;
      bool jzwNJsDEFy = false;
      string dJKbfaqAQd;
      string ifXGDaWYpy;
      string LlySydwgHc;
      string XmrNVapYrT;
      string toCtpDLVQd;
      string IBCIkqKqdC;
      string eJrmGwmJjb;
      string jxgWDViEct;
      string SZQcUVjice;
      string PzupnkxPns;
      string PBlntKUeFO;
      string IGNiiEsOSj;
      string LEgFMkBphR;
      string YTPieRnbiK;
      string BFcOWIlMGi;
      string rhxDhLUfbI;
      string IdwmonqdER;
      string QReHiGaSiD;
      string zoizZqWMBS;
      string xHAZBWIpYh;
      if(dJKbfaqAQd == PBlntKUeFO){RHIoSaCoUa = true;}
      else if(PBlntKUeFO == dJKbfaqAQd){lNoytasOQg = true;}
      if(ifXGDaWYpy == IGNiiEsOSj){kCxXJTuxNy = true;}
      else if(IGNiiEsOSj == ifXGDaWYpy){BaTuJTIKXp = true;}
      if(LlySydwgHc == LEgFMkBphR){RdckUJQEGL = true;}
      else if(LEgFMkBphR == LlySydwgHc){qpLnEdatXS = true;}
      if(XmrNVapYrT == YTPieRnbiK){yksAkrftfz = true;}
      else if(YTPieRnbiK == XmrNVapYrT){jCFVmkApdI = true;}
      if(toCtpDLVQd == BFcOWIlMGi){nhrZhuJbQh = true;}
      else if(BFcOWIlMGi == toCtpDLVQd){stBCwlodNV = true;}
      if(IBCIkqKqdC == rhxDhLUfbI){bKbaQmdWUJ = true;}
      else if(rhxDhLUfbI == IBCIkqKqdC){hnLGpwBAtP = true;}
      if(eJrmGwmJjb == IdwmonqdER){JxiIczIwlR = true;}
      else if(IdwmonqdER == eJrmGwmJjb){zzpxwyUyHX = true;}
      if(jxgWDViEct == QReHiGaSiD){mAQNJilCDZ = true;}
      if(SZQcUVjice == zoizZqWMBS){zonXjmISjy = true;}
      if(PzupnkxPns == xHAZBWIpYh){NIYWppziwh = true;}
      while(QReHiGaSiD == jxgWDViEct){TSgPwxnIqR = true;}
      while(zoizZqWMBS == zoizZqWMBS){oxgBkwqzeq = true;}
      while(xHAZBWIpYh == xHAZBWIpYh){jzwNJsDEFy = true;}
      if(RHIoSaCoUa == true){RHIoSaCoUa = false;}
      if(kCxXJTuxNy == true){kCxXJTuxNy = false;}
      if(RdckUJQEGL == true){RdckUJQEGL = false;}
      if(yksAkrftfz == true){yksAkrftfz = false;}
      if(nhrZhuJbQh == true){nhrZhuJbQh = false;}
      if(bKbaQmdWUJ == true){bKbaQmdWUJ = false;}
      if(JxiIczIwlR == true){JxiIczIwlR = false;}
      if(mAQNJilCDZ == true){mAQNJilCDZ = false;}
      if(zonXjmISjy == true){zonXjmISjy = false;}
      if(NIYWppziwh == true){NIYWppziwh = false;}
      if(lNoytasOQg == true){lNoytasOQg = false;}
      if(BaTuJTIKXp == true){BaTuJTIKXp = false;}
      if(qpLnEdatXS == true){qpLnEdatXS = false;}
      if(jCFVmkApdI == true){jCFVmkApdI = false;}
      if(stBCwlodNV == true){stBCwlodNV = false;}
      if(hnLGpwBAtP == true){hnLGpwBAtP = false;}
      if(zzpxwyUyHX == true){zzpxwyUyHX = false;}
      if(TSgPwxnIqR == true){TSgPwxnIqR = false;}
      if(oxgBkwqzeq == true){oxgBkwqzeq = false;}
      if(jzwNJsDEFy == true){jzwNJsDEFy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GBOGGHAWLO
{ 
  void nRZPEWpKrW()
  { 
      bool uBCwwQVxmM = false;
      bool NRKkmGiywa = false;
      bool JAyOJhpNeE = false;
      bool TQcKpqzoxa = false;
      bool efJPSdybHg = false;
      bool FSdNjtCmlN = false;
      bool ZHRirxnAuw = false;
      bool GtAVudpiue = false;
      bool iOFyyBlOau = false;
      bool nMCjBXOaWV = false;
      bool pxgLZLSISF = false;
      bool DTqGdKBSjq = false;
      bool KYZzItrQTX = false;
      bool PPMZolhtYm = false;
      bool idwUrTUuFp = false;
      bool VupfKQWgDe = false;
      bool TBntpnHRRr = false;
      bool cHtxIgcFHn = false;
      bool ZwLdCTYfOY = false;
      bool OApsTgoBdD = false;
      string pFwUWOHoYW;
      string QDoXIpBIbu;
      string XgQgjgYkcB;
      string CpgeXJrSer;
      string cbFDQjeAAA;
      string skIREJoPjo;
      string oWMXTaWKzz;
      string yicjRubMPA;
      string BYjcHQgPZO;
      string UchpDGOgip;
      string MUABBKHYzI;
      string gbzimPljQC;
      string sHjkdVBmgL;
      string ftdYmgYiax;
      string JIPRgscyCm;
      string TeQfxFjPWf;
      string ITqnbmxawG;
      string qDITskqSEk;
      string rCksqBcxbg;
      string wJMunoQaos;
      if(pFwUWOHoYW == MUABBKHYzI){uBCwwQVxmM = true;}
      else if(MUABBKHYzI == pFwUWOHoYW){pxgLZLSISF = true;}
      if(QDoXIpBIbu == gbzimPljQC){NRKkmGiywa = true;}
      else if(gbzimPljQC == QDoXIpBIbu){DTqGdKBSjq = true;}
      if(XgQgjgYkcB == sHjkdVBmgL){JAyOJhpNeE = true;}
      else if(sHjkdVBmgL == XgQgjgYkcB){KYZzItrQTX = true;}
      if(CpgeXJrSer == ftdYmgYiax){TQcKpqzoxa = true;}
      else if(ftdYmgYiax == CpgeXJrSer){PPMZolhtYm = true;}
      if(cbFDQjeAAA == JIPRgscyCm){efJPSdybHg = true;}
      else if(JIPRgscyCm == cbFDQjeAAA){idwUrTUuFp = true;}
      if(skIREJoPjo == TeQfxFjPWf){FSdNjtCmlN = true;}
      else if(TeQfxFjPWf == skIREJoPjo){VupfKQWgDe = true;}
      if(oWMXTaWKzz == ITqnbmxawG){ZHRirxnAuw = true;}
      else if(ITqnbmxawG == oWMXTaWKzz){TBntpnHRRr = true;}
      if(yicjRubMPA == qDITskqSEk){GtAVudpiue = true;}
      if(BYjcHQgPZO == rCksqBcxbg){iOFyyBlOau = true;}
      if(UchpDGOgip == wJMunoQaos){nMCjBXOaWV = true;}
      while(qDITskqSEk == yicjRubMPA){cHtxIgcFHn = true;}
      while(rCksqBcxbg == rCksqBcxbg){ZwLdCTYfOY = true;}
      while(wJMunoQaos == wJMunoQaos){OApsTgoBdD = true;}
      if(uBCwwQVxmM == true){uBCwwQVxmM = false;}
      if(NRKkmGiywa == true){NRKkmGiywa = false;}
      if(JAyOJhpNeE == true){JAyOJhpNeE = false;}
      if(TQcKpqzoxa == true){TQcKpqzoxa = false;}
      if(efJPSdybHg == true){efJPSdybHg = false;}
      if(FSdNjtCmlN == true){FSdNjtCmlN = false;}
      if(ZHRirxnAuw == true){ZHRirxnAuw = false;}
      if(GtAVudpiue == true){GtAVudpiue = false;}
      if(iOFyyBlOau == true){iOFyyBlOau = false;}
      if(nMCjBXOaWV == true){nMCjBXOaWV = false;}
      if(pxgLZLSISF == true){pxgLZLSISF = false;}
      if(DTqGdKBSjq == true){DTqGdKBSjq = false;}
      if(KYZzItrQTX == true){KYZzItrQTX = false;}
      if(PPMZolhtYm == true){PPMZolhtYm = false;}
      if(idwUrTUuFp == true){idwUrTUuFp = false;}
      if(VupfKQWgDe == true){VupfKQWgDe = false;}
      if(TBntpnHRRr == true){TBntpnHRRr = false;}
      if(cHtxIgcFHn == true){cHtxIgcFHn = false;}
      if(ZwLdCTYfOY == true){ZwLdCTYfOY = false;}
      if(OApsTgoBdD == true){OApsTgoBdD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YAVDASRQVM
{ 
  void BGmpRquYXr()
  { 
      bool ihGSDOcrAK = false;
      bool DJxihwimOk = false;
      bool YiDyhzNein = false;
      bool DlnAcGnaUh = false;
      bool HOcJfzLTXp = false;
      bool wTZTTAeIkE = false;
      bool AyIMGQVwGa = false;
      bool IHSfcJFtRi = false;
      bool msGrrjMTgb = false;
      bool bfoPhJGQCO = false;
      bool dONxhnAsqJ = false;
      bool tkqCQGqPTW = false;
      bool ECPdycSCyS = false;
      bool DnrCEYfIJD = false;
      bool iSbWgpnmza = false;
      bool SpweKazjyF = false;
      bool VyuXGGsnxr = false;
      bool ahGQmlZrwI = false;
      bool neCWANqMrd = false;
      bool YuKEhkWDQa = false;
      string xQmNUKgoNK;
      string HURBejadgh;
      string TKJjtczRdE;
      string sOCyLPVEId;
      string KoYNsYquRg;
      string yDzMAmHDSq;
      string KOLIQsRSoP;
      string OVVCXdlupV;
      string lEAwGoPoyY;
      string HSlQSudPwA;
      string GYFCSbhwoW;
      string BLMxFGOOBb;
      string dbUPHujFjc;
      string AVzpONyxce;
      string HSAbXwFoLL;
      string fOOUVeDotX;
      string qbLLVeMWhr;
      string IRkWTKasrL;
      string ousXxkGdTj;
      string JIDFmeHoFr;
      if(xQmNUKgoNK == GYFCSbhwoW){ihGSDOcrAK = true;}
      else if(GYFCSbhwoW == xQmNUKgoNK){dONxhnAsqJ = true;}
      if(HURBejadgh == BLMxFGOOBb){DJxihwimOk = true;}
      else if(BLMxFGOOBb == HURBejadgh){tkqCQGqPTW = true;}
      if(TKJjtczRdE == dbUPHujFjc){YiDyhzNein = true;}
      else if(dbUPHujFjc == TKJjtczRdE){ECPdycSCyS = true;}
      if(sOCyLPVEId == AVzpONyxce){DlnAcGnaUh = true;}
      else if(AVzpONyxce == sOCyLPVEId){DnrCEYfIJD = true;}
      if(KoYNsYquRg == HSAbXwFoLL){HOcJfzLTXp = true;}
      else if(HSAbXwFoLL == KoYNsYquRg){iSbWgpnmza = true;}
      if(yDzMAmHDSq == fOOUVeDotX){wTZTTAeIkE = true;}
      else if(fOOUVeDotX == yDzMAmHDSq){SpweKazjyF = true;}
      if(KOLIQsRSoP == qbLLVeMWhr){AyIMGQVwGa = true;}
      else if(qbLLVeMWhr == KOLIQsRSoP){VyuXGGsnxr = true;}
      if(OVVCXdlupV == IRkWTKasrL){IHSfcJFtRi = true;}
      if(lEAwGoPoyY == ousXxkGdTj){msGrrjMTgb = true;}
      if(HSlQSudPwA == JIDFmeHoFr){bfoPhJGQCO = true;}
      while(IRkWTKasrL == OVVCXdlupV){ahGQmlZrwI = true;}
      while(ousXxkGdTj == ousXxkGdTj){neCWANqMrd = true;}
      while(JIDFmeHoFr == JIDFmeHoFr){YuKEhkWDQa = true;}
      if(ihGSDOcrAK == true){ihGSDOcrAK = false;}
      if(DJxihwimOk == true){DJxihwimOk = false;}
      if(YiDyhzNein == true){YiDyhzNein = false;}
      if(DlnAcGnaUh == true){DlnAcGnaUh = false;}
      if(HOcJfzLTXp == true){HOcJfzLTXp = false;}
      if(wTZTTAeIkE == true){wTZTTAeIkE = false;}
      if(AyIMGQVwGa == true){AyIMGQVwGa = false;}
      if(IHSfcJFtRi == true){IHSfcJFtRi = false;}
      if(msGrrjMTgb == true){msGrrjMTgb = false;}
      if(bfoPhJGQCO == true){bfoPhJGQCO = false;}
      if(dONxhnAsqJ == true){dONxhnAsqJ = false;}
      if(tkqCQGqPTW == true){tkqCQGqPTW = false;}
      if(ECPdycSCyS == true){ECPdycSCyS = false;}
      if(DnrCEYfIJD == true){DnrCEYfIJD = false;}
      if(iSbWgpnmza == true){iSbWgpnmza = false;}
      if(SpweKazjyF == true){SpweKazjyF = false;}
      if(VyuXGGsnxr == true){VyuXGGsnxr = false;}
      if(ahGQmlZrwI == true){ahGQmlZrwI = false;}
      if(neCWANqMrd == true){neCWANqMrd = false;}
      if(YuKEhkWDQa == true){YuKEhkWDQa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWFIFPASWF
{ 
  void bfcgasYKME()
  { 
      bool ouARAgdAYB = false;
      bool DIIRMlOgRc = false;
      bool EZuXrzoDuI = false;
      bool BVsJkPhnbH = false;
      bool iiFACzAFib = false;
      bool GREaSOzcYB = false;
      bool qaFPzhOygx = false;
      bool DZFKtVTuVs = false;
      bool yiUTCjRRqV = false;
      bool PFOZPIdpAT = false;
      bool jBXlYfMsgx = false;
      bool tEHfDHFlNP = false;
      bool QwHLgxKeuk = false;
      bool rdtBIwLitV = false;
      bool WXksaKyiWH = false;
      bool CqbkDmtMEa = false;
      bool UgyuFQKFXG = false;
      bool wWqqrsLNjW = false;
      bool zbImiABIyU = false;
      bool CydTAoYonK = false;
      string hEBMQGrTmY;
      string MnVMQAiMOd;
      string pFSmOmMnKc;
      string ZAFxWRGIJL;
      string ZDLSXxXaLS;
      string JtxpTclOxc;
      string tEIKyMhXoz;
      string sZDCDltAOQ;
      string OlbqSfCOdt;
      string eqLfRVuATL;
      string OAkMYjqtmh;
      string hkzfOIbRqR;
      string JTttTCOWkg;
      string qsfDBOAPRi;
      string oIbuMtqeRI;
      string scJBCuGqrW;
      string UTJFqnEwdA;
      string IMzIcBqyhZ;
      string KiFbnNjdBG;
      string HJXuNUzVEX;
      if(hEBMQGrTmY == OAkMYjqtmh){ouARAgdAYB = true;}
      else if(OAkMYjqtmh == hEBMQGrTmY){jBXlYfMsgx = true;}
      if(MnVMQAiMOd == hkzfOIbRqR){DIIRMlOgRc = true;}
      else if(hkzfOIbRqR == MnVMQAiMOd){tEHfDHFlNP = true;}
      if(pFSmOmMnKc == JTttTCOWkg){EZuXrzoDuI = true;}
      else if(JTttTCOWkg == pFSmOmMnKc){QwHLgxKeuk = true;}
      if(ZAFxWRGIJL == qsfDBOAPRi){BVsJkPhnbH = true;}
      else if(qsfDBOAPRi == ZAFxWRGIJL){rdtBIwLitV = true;}
      if(ZDLSXxXaLS == oIbuMtqeRI){iiFACzAFib = true;}
      else if(oIbuMtqeRI == ZDLSXxXaLS){WXksaKyiWH = true;}
      if(JtxpTclOxc == scJBCuGqrW){GREaSOzcYB = true;}
      else if(scJBCuGqrW == JtxpTclOxc){CqbkDmtMEa = true;}
      if(tEIKyMhXoz == UTJFqnEwdA){qaFPzhOygx = true;}
      else if(UTJFqnEwdA == tEIKyMhXoz){UgyuFQKFXG = true;}
      if(sZDCDltAOQ == IMzIcBqyhZ){DZFKtVTuVs = true;}
      if(OlbqSfCOdt == KiFbnNjdBG){yiUTCjRRqV = true;}
      if(eqLfRVuATL == HJXuNUzVEX){PFOZPIdpAT = true;}
      while(IMzIcBqyhZ == sZDCDltAOQ){wWqqrsLNjW = true;}
      while(KiFbnNjdBG == KiFbnNjdBG){zbImiABIyU = true;}
      while(HJXuNUzVEX == HJXuNUzVEX){CydTAoYonK = true;}
      if(ouARAgdAYB == true){ouARAgdAYB = false;}
      if(DIIRMlOgRc == true){DIIRMlOgRc = false;}
      if(EZuXrzoDuI == true){EZuXrzoDuI = false;}
      if(BVsJkPhnbH == true){BVsJkPhnbH = false;}
      if(iiFACzAFib == true){iiFACzAFib = false;}
      if(GREaSOzcYB == true){GREaSOzcYB = false;}
      if(qaFPzhOygx == true){qaFPzhOygx = false;}
      if(DZFKtVTuVs == true){DZFKtVTuVs = false;}
      if(yiUTCjRRqV == true){yiUTCjRRqV = false;}
      if(PFOZPIdpAT == true){PFOZPIdpAT = false;}
      if(jBXlYfMsgx == true){jBXlYfMsgx = false;}
      if(tEHfDHFlNP == true){tEHfDHFlNP = false;}
      if(QwHLgxKeuk == true){QwHLgxKeuk = false;}
      if(rdtBIwLitV == true){rdtBIwLitV = false;}
      if(WXksaKyiWH == true){WXksaKyiWH = false;}
      if(CqbkDmtMEa == true){CqbkDmtMEa = false;}
      if(UgyuFQKFXG == true){UgyuFQKFXG = false;}
      if(wWqqrsLNjW == true){wWqqrsLNjW = false;}
      if(zbImiABIyU == true){zbImiABIyU = false;}
      if(CydTAoYonK == true){CydTAoYonK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KNMCQCUGQC
{ 
  void iwRJtHQyCV()
  { 
      bool CGYqBCWmyP = false;
      bool hepGlfAlDE = false;
      bool LtEDknsoTi = false;
      bool hUNOLsnXJU = false;
      bool nMEDSaoJLE = false;
      bool gZrlnICUGM = false;
      bool JhTOhNRatr = false;
      bool rbciQypBjJ = false;
      bool zjcPCHcbZD = false;
      bool qSRwKGsoVF = false;
      bool JNOTMEwIUp = false;
      bool RBkwNYEDMZ = false;
      bool kpAqAZJgXJ = false;
      bool EBedAkUIDx = false;
      bool KTGjkphVhk = false;
      bool BobuUSMXTl = false;
      bool uPkKkPVGwc = false;
      bool EuAPOQjQFK = false;
      bool rnylIOZjJg = false;
      bool XxoQCuiuzU = false;
      string SDrcCIpuVH;
      string QtoiAeArzE;
      string IstAmkndXY;
      string iXbjqXWZft;
      string QEXAHCAXLX;
      string KYjxpZIrpR;
      string TLWxXrRFrc;
      string IaLFmDUtrj;
      string jPSANKnetR;
      string OdjOZEgacO;
      string jufhPjMdJl;
      string FOAFgEsWiN;
      string ElLaNdqxfi;
      string VsRczojjjd;
      string xJVHLzddhV;
      string LKrOKyiEUl;
      string sPxaQLxWFq;
      string TImEQtPEOO;
      string AMPKWLACSB;
      string GePxkgMupA;
      if(SDrcCIpuVH == jufhPjMdJl){CGYqBCWmyP = true;}
      else if(jufhPjMdJl == SDrcCIpuVH){JNOTMEwIUp = true;}
      if(QtoiAeArzE == FOAFgEsWiN){hepGlfAlDE = true;}
      else if(FOAFgEsWiN == QtoiAeArzE){RBkwNYEDMZ = true;}
      if(IstAmkndXY == ElLaNdqxfi){LtEDknsoTi = true;}
      else if(ElLaNdqxfi == IstAmkndXY){kpAqAZJgXJ = true;}
      if(iXbjqXWZft == VsRczojjjd){hUNOLsnXJU = true;}
      else if(VsRczojjjd == iXbjqXWZft){EBedAkUIDx = true;}
      if(QEXAHCAXLX == xJVHLzddhV){nMEDSaoJLE = true;}
      else if(xJVHLzddhV == QEXAHCAXLX){KTGjkphVhk = true;}
      if(KYjxpZIrpR == LKrOKyiEUl){gZrlnICUGM = true;}
      else if(LKrOKyiEUl == KYjxpZIrpR){BobuUSMXTl = true;}
      if(TLWxXrRFrc == sPxaQLxWFq){JhTOhNRatr = true;}
      else if(sPxaQLxWFq == TLWxXrRFrc){uPkKkPVGwc = true;}
      if(IaLFmDUtrj == TImEQtPEOO){rbciQypBjJ = true;}
      if(jPSANKnetR == AMPKWLACSB){zjcPCHcbZD = true;}
      if(OdjOZEgacO == GePxkgMupA){qSRwKGsoVF = true;}
      while(TImEQtPEOO == IaLFmDUtrj){EuAPOQjQFK = true;}
      while(AMPKWLACSB == AMPKWLACSB){rnylIOZjJg = true;}
      while(GePxkgMupA == GePxkgMupA){XxoQCuiuzU = true;}
      if(CGYqBCWmyP == true){CGYqBCWmyP = false;}
      if(hepGlfAlDE == true){hepGlfAlDE = false;}
      if(LtEDknsoTi == true){LtEDknsoTi = false;}
      if(hUNOLsnXJU == true){hUNOLsnXJU = false;}
      if(nMEDSaoJLE == true){nMEDSaoJLE = false;}
      if(gZrlnICUGM == true){gZrlnICUGM = false;}
      if(JhTOhNRatr == true){JhTOhNRatr = false;}
      if(rbciQypBjJ == true){rbciQypBjJ = false;}
      if(zjcPCHcbZD == true){zjcPCHcbZD = false;}
      if(qSRwKGsoVF == true){qSRwKGsoVF = false;}
      if(JNOTMEwIUp == true){JNOTMEwIUp = false;}
      if(RBkwNYEDMZ == true){RBkwNYEDMZ = false;}
      if(kpAqAZJgXJ == true){kpAqAZJgXJ = false;}
      if(EBedAkUIDx == true){EBedAkUIDx = false;}
      if(KTGjkphVhk == true){KTGjkphVhk = false;}
      if(BobuUSMXTl == true){BobuUSMXTl = false;}
      if(uPkKkPVGwc == true){uPkKkPVGwc = false;}
      if(EuAPOQjQFK == true){EuAPOQjQFK = false;}
      if(rnylIOZjJg == true){rnylIOZjJg = false;}
      if(XxoQCuiuzU == true){XxoQCuiuzU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IROHMUGQVH
{ 
  void PTCVSKminC()
  { 
      bool jSIbMCSbeM = false;
      bool QNurLZnxUR = false;
      bool BPTxPyqhOd = false;
      bool AWFqNwxVPo = false;
      bool gSfnRCCwnV = false;
      bool lzEqHUyLMO = false;
      bool LjNBLsHEdO = false;
      bool cShejijffM = false;
      bool wttrqBSOjr = false;
      bool xlJAdxFdbX = false;
      bool tyRYsTRYGX = false;
      bool kRezRQoUKK = false;
      bool asUkRpJgBm = false;
      bool cFEIRycVyX = false;
      bool isHLHeGJiM = false;
      bool IjTRwBcgHD = false;
      bool JkXSueNWgT = false;
      bool nSWlahkJdl = false;
      bool jzyoeslmMQ = false;
      bool UwOuNyVoQb = false;
      string EVsRnQPPfs;
      string jszEkLwwVH;
      string cVHXxGgXDp;
      string bgjSRtokLi;
      string lUPOhFymqA;
      string mZyJaiNVTg;
      string iqLpQDJgmp;
      string WLjlUIFror;
      string IsfDDBiarh;
      string fTQeztIYye;
      string wQAAdapLnR;
      string cUfbXpLHmO;
      string TioEJCuEla;
      string AgtKwrseZb;
      string LWlZFLmoHJ;
      string iAliKNbuqa;
      string fkZMRwaUff;
      string wfhKDxwOzy;
      string OGxbrztLAh;
      string PynzwZwYII;
      if(EVsRnQPPfs == wQAAdapLnR){jSIbMCSbeM = true;}
      else if(wQAAdapLnR == EVsRnQPPfs){tyRYsTRYGX = true;}
      if(jszEkLwwVH == cUfbXpLHmO){QNurLZnxUR = true;}
      else if(cUfbXpLHmO == jszEkLwwVH){kRezRQoUKK = true;}
      if(cVHXxGgXDp == TioEJCuEla){BPTxPyqhOd = true;}
      else if(TioEJCuEla == cVHXxGgXDp){asUkRpJgBm = true;}
      if(bgjSRtokLi == AgtKwrseZb){AWFqNwxVPo = true;}
      else if(AgtKwrseZb == bgjSRtokLi){cFEIRycVyX = true;}
      if(lUPOhFymqA == LWlZFLmoHJ){gSfnRCCwnV = true;}
      else if(LWlZFLmoHJ == lUPOhFymqA){isHLHeGJiM = true;}
      if(mZyJaiNVTg == iAliKNbuqa){lzEqHUyLMO = true;}
      else if(iAliKNbuqa == mZyJaiNVTg){IjTRwBcgHD = true;}
      if(iqLpQDJgmp == fkZMRwaUff){LjNBLsHEdO = true;}
      else if(fkZMRwaUff == iqLpQDJgmp){JkXSueNWgT = true;}
      if(WLjlUIFror == wfhKDxwOzy){cShejijffM = true;}
      if(IsfDDBiarh == OGxbrztLAh){wttrqBSOjr = true;}
      if(fTQeztIYye == PynzwZwYII){xlJAdxFdbX = true;}
      while(wfhKDxwOzy == WLjlUIFror){nSWlahkJdl = true;}
      while(OGxbrztLAh == OGxbrztLAh){jzyoeslmMQ = true;}
      while(PynzwZwYII == PynzwZwYII){UwOuNyVoQb = true;}
      if(jSIbMCSbeM == true){jSIbMCSbeM = false;}
      if(QNurLZnxUR == true){QNurLZnxUR = false;}
      if(BPTxPyqhOd == true){BPTxPyqhOd = false;}
      if(AWFqNwxVPo == true){AWFqNwxVPo = false;}
      if(gSfnRCCwnV == true){gSfnRCCwnV = false;}
      if(lzEqHUyLMO == true){lzEqHUyLMO = false;}
      if(LjNBLsHEdO == true){LjNBLsHEdO = false;}
      if(cShejijffM == true){cShejijffM = false;}
      if(wttrqBSOjr == true){wttrqBSOjr = false;}
      if(xlJAdxFdbX == true){xlJAdxFdbX = false;}
      if(tyRYsTRYGX == true){tyRYsTRYGX = false;}
      if(kRezRQoUKK == true){kRezRQoUKK = false;}
      if(asUkRpJgBm == true){asUkRpJgBm = false;}
      if(cFEIRycVyX == true){cFEIRycVyX = false;}
      if(isHLHeGJiM == true){isHLHeGJiM = false;}
      if(IjTRwBcgHD == true){IjTRwBcgHD = false;}
      if(JkXSueNWgT == true){JkXSueNWgT = false;}
      if(nSWlahkJdl == true){nSWlahkJdl = false;}
      if(jzyoeslmMQ == true){jzyoeslmMQ = false;}
      if(UwOuNyVoQb == true){UwOuNyVoQb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XKAWXHPJSP
{ 
  void ltDGIAYQTi()
  { 
      bool TosAFbWUSu = false;
      bool BxdwbtXVGG = false;
      bool erDqNMepua = false;
      bool pyPkzOZebT = false;
      bool SxiTgwJqMl = false;
      bool buTXfbkCmr = false;
      bool xfZrFChswN = false;
      bool TstlnhJiKQ = false;
      bool DmdIyteqFX = false;
      bool cXqiWmWpNd = false;
      bool OPuzSiBgjx = false;
      bool SBqVnJBQsK = false;
      bool XqnYjuBKOA = false;
      bool KSVgCnrepP = false;
      bool rxGHFagVtN = false;
      bool kGxCFWbVOW = false;
      bool gpRimzfKTA = false;
      bool RVadRZjgSI = false;
      bool OfQBPEUSae = false;
      bool MVQShCfWTF = false;
      string QaDWBxzWJE;
      string AwijtjVsip;
      string JWRSwDqdJo;
      string eLVxNLeeBa;
      string jPmyTFBAex;
      string siAyhtIkax;
      string FUMTZnalWi;
      string FqrIFtiTzp;
      string CqzMwuLWPS;
      string CsEDUPCTXf;
      string eOdwqBqqsn;
      string LoljuOVAWe;
      string bDVDgLmnnp;
      string qOuSKmNDUu;
      string DUdbHNHTIG;
      string tCxsDbrZPf;
      string NDDCwwsSZH;
      string ASebaHZtuS;
      string DTegwoRBPi;
      string tmmngARaeK;
      if(QaDWBxzWJE == eOdwqBqqsn){TosAFbWUSu = true;}
      else if(eOdwqBqqsn == QaDWBxzWJE){OPuzSiBgjx = true;}
      if(AwijtjVsip == LoljuOVAWe){BxdwbtXVGG = true;}
      else if(LoljuOVAWe == AwijtjVsip){SBqVnJBQsK = true;}
      if(JWRSwDqdJo == bDVDgLmnnp){erDqNMepua = true;}
      else if(bDVDgLmnnp == JWRSwDqdJo){XqnYjuBKOA = true;}
      if(eLVxNLeeBa == qOuSKmNDUu){pyPkzOZebT = true;}
      else if(qOuSKmNDUu == eLVxNLeeBa){KSVgCnrepP = true;}
      if(jPmyTFBAex == DUdbHNHTIG){SxiTgwJqMl = true;}
      else if(DUdbHNHTIG == jPmyTFBAex){rxGHFagVtN = true;}
      if(siAyhtIkax == tCxsDbrZPf){buTXfbkCmr = true;}
      else if(tCxsDbrZPf == siAyhtIkax){kGxCFWbVOW = true;}
      if(FUMTZnalWi == NDDCwwsSZH){xfZrFChswN = true;}
      else if(NDDCwwsSZH == FUMTZnalWi){gpRimzfKTA = true;}
      if(FqrIFtiTzp == ASebaHZtuS){TstlnhJiKQ = true;}
      if(CqzMwuLWPS == DTegwoRBPi){DmdIyteqFX = true;}
      if(CsEDUPCTXf == tmmngARaeK){cXqiWmWpNd = true;}
      while(ASebaHZtuS == FqrIFtiTzp){RVadRZjgSI = true;}
      while(DTegwoRBPi == DTegwoRBPi){OfQBPEUSae = true;}
      while(tmmngARaeK == tmmngARaeK){MVQShCfWTF = true;}
      if(TosAFbWUSu == true){TosAFbWUSu = false;}
      if(BxdwbtXVGG == true){BxdwbtXVGG = false;}
      if(erDqNMepua == true){erDqNMepua = false;}
      if(pyPkzOZebT == true){pyPkzOZebT = false;}
      if(SxiTgwJqMl == true){SxiTgwJqMl = false;}
      if(buTXfbkCmr == true){buTXfbkCmr = false;}
      if(xfZrFChswN == true){xfZrFChswN = false;}
      if(TstlnhJiKQ == true){TstlnhJiKQ = false;}
      if(DmdIyteqFX == true){DmdIyteqFX = false;}
      if(cXqiWmWpNd == true){cXqiWmWpNd = false;}
      if(OPuzSiBgjx == true){OPuzSiBgjx = false;}
      if(SBqVnJBQsK == true){SBqVnJBQsK = false;}
      if(XqnYjuBKOA == true){XqnYjuBKOA = false;}
      if(KSVgCnrepP == true){KSVgCnrepP = false;}
      if(rxGHFagVtN == true){rxGHFagVtN = false;}
      if(kGxCFWbVOW == true){kGxCFWbVOW = false;}
      if(gpRimzfKTA == true){gpRimzfKTA = false;}
      if(RVadRZjgSI == true){RVadRZjgSI = false;}
      if(OfQBPEUSae == true){OfQBPEUSae = false;}
      if(MVQShCfWTF == true){MVQShCfWTF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WVOBNGHKSY
{ 
  void BiREFKorYX()
  { 
      bool oUZHHInGMl = false;
      bool HNWwhZbzZn = false;
      bool tFMPXozEYW = false;
      bool OFtWRbhxqQ = false;
      bool rgQrCoNxzJ = false;
      bool GjHPbiHJiS = false;
      bool JigoXBTzdF = false;
      bool rdIJuNnTMi = false;
      bool aBFPQdydti = false;
      bool TXOYHIAbUB = false;
      bool UNTtRbbxTO = false;
      bool tmwzqHdQXs = false;
      bool CoEukTPjCm = false;
      bool MMzLNNhKxo = false;
      bool CBJfngaOgz = false;
      bool eiEayfIYJx = false;
      bool LrugBhnkld = false;
      bool YSSipBeYGE = false;
      bool rBCCHdIYMg = false;
      bool EIBAcKGcdG = false;
      string CwXQkSSPbW;
      string UiaIClXQuk;
      string CWgkOzXxRp;
      string PeFFTSIiHF;
      string PWcwFsDERR;
      string fdTxGePmCk;
      string uVykHpcUni;
      string doJpUftjeV;
      string wSezJkKIzo;
      string DUgWJsYqnP;
      string PhQhnqUdba;
      string jeHfnbpybV;
      string eUVzeJImfb;
      string GCuPFNCxLS;
      string QggXEXMAhh;
      string CaPRjuLRDd;
      string hhxzThiraa;
      string ZslJFxmytG;
      string wHFyYfmdeK;
      string CktgjiigDW;
      if(CwXQkSSPbW == PhQhnqUdba){oUZHHInGMl = true;}
      else if(PhQhnqUdba == CwXQkSSPbW){UNTtRbbxTO = true;}
      if(UiaIClXQuk == jeHfnbpybV){HNWwhZbzZn = true;}
      else if(jeHfnbpybV == UiaIClXQuk){tmwzqHdQXs = true;}
      if(CWgkOzXxRp == eUVzeJImfb){tFMPXozEYW = true;}
      else if(eUVzeJImfb == CWgkOzXxRp){CoEukTPjCm = true;}
      if(PeFFTSIiHF == GCuPFNCxLS){OFtWRbhxqQ = true;}
      else if(GCuPFNCxLS == PeFFTSIiHF){MMzLNNhKxo = true;}
      if(PWcwFsDERR == QggXEXMAhh){rgQrCoNxzJ = true;}
      else if(QggXEXMAhh == PWcwFsDERR){CBJfngaOgz = true;}
      if(fdTxGePmCk == CaPRjuLRDd){GjHPbiHJiS = true;}
      else if(CaPRjuLRDd == fdTxGePmCk){eiEayfIYJx = true;}
      if(uVykHpcUni == hhxzThiraa){JigoXBTzdF = true;}
      else if(hhxzThiraa == uVykHpcUni){LrugBhnkld = true;}
      if(doJpUftjeV == ZslJFxmytG){rdIJuNnTMi = true;}
      if(wSezJkKIzo == wHFyYfmdeK){aBFPQdydti = true;}
      if(DUgWJsYqnP == CktgjiigDW){TXOYHIAbUB = true;}
      while(ZslJFxmytG == doJpUftjeV){YSSipBeYGE = true;}
      while(wHFyYfmdeK == wHFyYfmdeK){rBCCHdIYMg = true;}
      while(CktgjiigDW == CktgjiigDW){EIBAcKGcdG = true;}
      if(oUZHHInGMl == true){oUZHHInGMl = false;}
      if(HNWwhZbzZn == true){HNWwhZbzZn = false;}
      if(tFMPXozEYW == true){tFMPXozEYW = false;}
      if(OFtWRbhxqQ == true){OFtWRbhxqQ = false;}
      if(rgQrCoNxzJ == true){rgQrCoNxzJ = false;}
      if(GjHPbiHJiS == true){GjHPbiHJiS = false;}
      if(JigoXBTzdF == true){JigoXBTzdF = false;}
      if(rdIJuNnTMi == true){rdIJuNnTMi = false;}
      if(aBFPQdydti == true){aBFPQdydti = false;}
      if(TXOYHIAbUB == true){TXOYHIAbUB = false;}
      if(UNTtRbbxTO == true){UNTtRbbxTO = false;}
      if(tmwzqHdQXs == true){tmwzqHdQXs = false;}
      if(CoEukTPjCm == true){CoEukTPjCm = false;}
      if(MMzLNNhKxo == true){MMzLNNhKxo = false;}
      if(CBJfngaOgz == true){CBJfngaOgz = false;}
      if(eiEayfIYJx == true){eiEayfIYJx = false;}
      if(LrugBhnkld == true){LrugBhnkld = false;}
      if(YSSipBeYGE == true){YSSipBeYGE = false;}
      if(rBCCHdIYMg == true){rBCCHdIYMg = false;}
      if(EIBAcKGcdG == true){EIBAcKGcdG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LOPJIUXNXA
{ 
  void CklPxNUnqR()
  { 
      bool crStWKnOjP = false;
      bool MzidAcEACd = false;
      bool HEbJAhEtzD = false;
      bool kVzsRUNbPG = false;
      bool CeMOGqfazn = false;
      bool hfxpIYQJtn = false;
      bool FsOfeqAoMf = false;
      bool PbjuacqMCJ = false;
      bool CduLVFYIkr = false;
      bool DDgbBIPfjP = false;
      bool qpNTYGuBPf = false;
      bool gEGkkayDKZ = false;
      bool SqETbLtItR = false;
      bool MKbmSMPblP = false;
      bool JWsEKzwwpa = false;
      bool KMVKwzktrM = false;
      bool LlHySWbTSX = false;
      bool KVQuPuxAIb = false;
      bool OyRTGAoRpS = false;
      bool bVjZDWPuln = false;
      string OLyHFsKxLh;
      string iZxpHChfhG;
      string KkjxDNNzyD;
      string fkPBWeUegD;
      string QqigQfYmYJ;
      string oiXsPcbADq;
      string eLyHByJuTb;
      string hDydpTBCfX;
      string oaZoNxMVls;
      string DTaoXFraeS;
      string VdTxaljsDw;
      string bYUeCElItE;
      string kmJaYNbJGj;
      string aaXNCKHcNb;
      string NTSoRdzulT;
      string TigahhTrXN;
      string JamSUBBHcq;
      string xJuRpRUTJt;
      string NfWlQqsxeT;
      string qOEARlfzTP;
      if(OLyHFsKxLh == VdTxaljsDw){crStWKnOjP = true;}
      else if(VdTxaljsDw == OLyHFsKxLh){qpNTYGuBPf = true;}
      if(iZxpHChfhG == bYUeCElItE){MzidAcEACd = true;}
      else if(bYUeCElItE == iZxpHChfhG){gEGkkayDKZ = true;}
      if(KkjxDNNzyD == kmJaYNbJGj){HEbJAhEtzD = true;}
      else if(kmJaYNbJGj == KkjxDNNzyD){SqETbLtItR = true;}
      if(fkPBWeUegD == aaXNCKHcNb){kVzsRUNbPG = true;}
      else if(aaXNCKHcNb == fkPBWeUegD){MKbmSMPblP = true;}
      if(QqigQfYmYJ == NTSoRdzulT){CeMOGqfazn = true;}
      else if(NTSoRdzulT == QqigQfYmYJ){JWsEKzwwpa = true;}
      if(oiXsPcbADq == TigahhTrXN){hfxpIYQJtn = true;}
      else if(TigahhTrXN == oiXsPcbADq){KMVKwzktrM = true;}
      if(eLyHByJuTb == JamSUBBHcq){FsOfeqAoMf = true;}
      else if(JamSUBBHcq == eLyHByJuTb){LlHySWbTSX = true;}
      if(hDydpTBCfX == xJuRpRUTJt){PbjuacqMCJ = true;}
      if(oaZoNxMVls == NfWlQqsxeT){CduLVFYIkr = true;}
      if(DTaoXFraeS == qOEARlfzTP){DDgbBIPfjP = true;}
      while(xJuRpRUTJt == hDydpTBCfX){KVQuPuxAIb = true;}
      while(NfWlQqsxeT == NfWlQqsxeT){OyRTGAoRpS = true;}
      while(qOEARlfzTP == qOEARlfzTP){bVjZDWPuln = true;}
      if(crStWKnOjP == true){crStWKnOjP = false;}
      if(MzidAcEACd == true){MzidAcEACd = false;}
      if(HEbJAhEtzD == true){HEbJAhEtzD = false;}
      if(kVzsRUNbPG == true){kVzsRUNbPG = false;}
      if(CeMOGqfazn == true){CeMOGqfazn = false;}
      if(hfxpIYQJtn == true){hfxpIYQJtn = false;}
      if(FsOfeqAoMf == true){FsOfeqAoMf = false;}
      if(PbjuacqMCJ == true){PbjuacqMCJ = false;}
      if(CduLVFYIkr == true){CduLVFYIkr = false;}
      if(DDgbBIPfjP == true){DDgbBIPfjP = false;}
      if(qpNTYGuBPf == true){qpNTYGuBPf = false;}
      if(gEGkkayDKZ == true){gEGkkayDKZ = false;}
      if(SqETbLtItR == true){SqETbLtItR = false;}
      if(MKbmSMPblP == true){MKbmSMPblP = false;}
      if(JWsEKzwwpa == true){JWsEKzwwpa = false;}
      if(KMVKwzktrM == true){KMVKwzktrM = false;}
      if(LlHySWbTSX == true){LlHySWbTSX = false;}
      if(KVQuPuxAIb == true){KVQuPuxAIb = false;}
      if(OyRTGAoRpS == true){OyRTGAoRpS = false;}
      if(bVjZDWPuln == true){bVjZDWPuln = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FUQIEVWILP
{ 
  void jJFenAAEMQ()
  { 
      bool upcARAxyhC = false;
      bool uYqkQcpmgQ = false;
      bool xiOeGsLpJQ = false;
      bool CwDYbgUNHK = false;
      bool FUSWfjFfzy = false;
      bool tWQPkMaytX = false;
      bool oHoQzyUSIi = false;
      bool IbeWKbPryW = false;
      bool nepLWfennP = false;
      bool FVTjVyfBWh = false;
      bool OmXPpSqtEI = false;
      bool xizWjKQdtT = false;
      bool SgdrdlHuAM = false;
      bool wNVQHAGaUE = false;
      bool njieSWWwAL = false;
      bool gBHCOhIelD = false;
      bool KutqLiMhPi = false;
      bool DpIoeixzZG = false;
      bool PKuoeuGTCZ = false;
      bool qanQsspqTi = false;
      string GYrEMJuBLu;
      string fnmqicOODp;
      string oHuelUZFuJ;
      string hibYSdTZnc;
      string VTbltpIbRz;
      string xJTCuzcMSr;
      string jpGBNxMOYE;
      string InaZTUeIku;
      string LymuMXOZcS;
      string AGHwsfNZYx;
      string dtDNqIisha;
      string UUbXfkCKoo;
      string hmkFECgegn;
      string GEjnRQuZED;
      string nVrByfeiPH;
      string cDkiOpIyIn;
      string aEMsUQjnGO;
      string pbFlAMujGX;
      string XyOYLDTBYa;
      string IwQPbjJygh;
      if(GYrEMJuBLu == dtDNqIisha){upcARAxyhC = true;}
      else if(dtDNqIisha == GYrEMJuBLu){OmXPpSqtEI = true;}
      if(fnmqicOODp == UUbXfkCKoo){uYqkQcpmgQ = true;}
      else if(UUbXfkCKoo == fnmqicOODp){xizWjKQdtT = true;}
      if(oHuelUZFuJ == hmkFECgegn){xiOeGsLpJQ = true;}
      else if(hmkFECgegn == oHuelUZFuJ){SgdrdlHuAM = true;}
      if(hibYSdTZnc == GEjnRQuZED){CwDYbgUNHK = true;}
      else if(GEjnRQuZED == hibYSdTZnc){wNVQHAGaUE = true;}
      if(VTbltpIbRz == nVrByfeiPH){FUSWfjFfzy = true;}
      else if(nVrByfeiPH == VTbltpIbRz){njieSWWwAL = true;}
      if(xJTCuzcMSr == cDkiOpIyIn){tWQPkMaytX = true;}
      else if(cDkiOpIyIn == xJTCuzcMSr){gBHCOhIelD = true;}
      if(jpGBNxMOYE == aEMsUQjnGO){oHoQzyUSIi = true;}
      else if(aEMsUQjnGO == jpGBNxMOYE){KutqLiMhPi = true;}
      if(InaZTUeIku == pbFlAMujGX){IbeWKbPryW = true;}
      if(LymuMXOZcS == XyOYLDTBYa){nepLWfennP = true;}
      if(AGHwsfNZYx == IwQPbjJygh){FVTjVyfBWh = true;}
      while(pbFlAMujGX == InaZTUeIku){DpIoeixzZG = true;}
      while(XyOYLDTBYa == XyOYLDTBYa){PKuoeuGTCZ = true;}
      while(IwQPbjJygh == IwQPbjJygh){qanQsspqTi = true;}
      if(upcARAxyhC == true){upcARAxyhC = false;}
      if(uYqkQcpmgQ == true){uYqkQcpmgQ = false;}
      if(xiOeGsLpJQ == true){xiOeGsLpJQ = false;}
      if(CwDYbgUNHK == true){CwDYbgUNHK = false;}
      if(FUSWfjFfzy == true){FUSWfjFfzy = false;}
      if(tWQPkMaytX == true){tWQPkMaytX = false;}
      if(oHoQzyUSIi == true){oHoQzyUSIi = false;}
      if(IbeWKbPryW == true){IbeWKbPryW = false;}
      if(nepLWfennP == true){nepLWfennP = false;}
      if(FVTjVyfBWh == true){FVTjVyfBWh = false;}
      if(OmXPpSqtEI == true){OmXPpSqtEI = false;}
      if(xizWjKQdtT == true){xizWjKQdtT = false;}
      if(SgdrdlHuAM == true){SgdrdlHuAM = false;}
      if(wNVQHAGaUE == true){wNVQHAGaUE = false;}
      if(njieSWWwAL == true){njieSWWwAL = false;}
      if(gBHCOhIelD == true){gBHCOhIelD = false;}
      if(KutqLiMhPi == true){KutqLiMhPi = false;}
      if(DpIoeixzZG == true){DpIoeixzZG = false;}
      if(PKuoeuGTCZ == true){PKuoeuGTCZ = false;}
      if(qanQsspqTi == true){qanQsspqTi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EQXFUYHLEQ
{ 
  void uFpxpBYphc()
  { 
      bool AVIHnJGBfR = false;
      bool GSeVOSSpJu = false;
      bool XBtOTfbUDw = false;
      bool ItFEGrAKUU = false;
      bool wCIzWFBUrf = false;
      bool ibTIBzatnH = false;
      bool glxiJMNZPW = false;
      bool SHVnyVrtqO = false;
      bool eHbXNfawDH = false;
      bool RFWMmKEZoK = false;
      bool raFVNaFeJf = false;
      bool GfDYbZJZUd = false;
      bool lRWHEMkIAn = false;
      bool QSEgWDBFKm = false;
      bool aulWAkCxjN = false;
      bool AeELXaExQA = false;
      bool oxdVPnaVCY = false;
      bool XDPgCpezHT = false;
      bool JmXmmlNrIw = false;
      bool zEoJydRPHM = false;
      string CbHSyiCFBo;
      string EgxutWkhzU;
      string zVgqrTyUiJ;
      string JpfBWuVaWm;
      string xRbwxShPZZ;
      string wQSSQgtQZd;
      string khVreOAuXy;
      string AKLLWgtksZ;
      string lhtJNsXMkp;
      string AEArCPwjQi;
      string RlraYlFHui;
      string mJWzrCmMdl;
      string pnKhyuJSIH;
      string kJTKHzpTja;
      string nQQBCqhAAA;
      string ciFerdbJcc;
      string blynxcpMrr;
      string MSbDyZWIeG;
      string NISIeCEoRd;
      string XfpHzBRcDZ;
      if(CbHSyiCFBo == RlraYlFHui){AVIHnJGBfR = true;}
      else if(RlraYlFHui == CbHSyiCFBo){raFVNaFeJf = true;}
      if(EgxutWkhzU == mJWzrCmMdl){GSeVOSSpJu = true;}
      else if(mJWzrCmMdl == EgxutWkhzU){GfDYbZJZUd = true;}
      if(zVgqrTyUiJ == pnKhyuJSIH){XBtOTfbUDw = true;}
      else if(pnKhyuJSIH == zVgqrTyUiJ){lRWHEMkIAn = true;}
      if(JpfBWuVaWm == kJTKHzpTja){ItFEGrAKUU = true;}
      else if(kJTKHzpTja == JpfBWuVaWm){QSEgWDBFKm = true;}
      if(xRbwxShPZZ == nQQBCqhAAA){wCIzWFBUrf = true;}
      else if(nQQBCqhAAA == xRbwxShPZZ){aulWAkCxjN = true;}
      if(wQSSQgtQZd == ciFerdbJcc){ibTIBzatnH = true;}
      else if(ciFerdbJcc == wQSSQgtQZd){AeELXaExQA = true;}
      if(khVreOAuXy == blynxcpMrr){glxiJMNZPW = true;}
      else if(blynxcpMrr == khVreOAuXy){oxdVPnaVCY = true;}
      if(AKLLWgtksZ == MSbDyZWIeG){SHVnyVrtqO = true;}
      if(lhtJNsXMkp == NISIeCEoRd){eHbXNfawDH = true;}
      if(AEArCPwjQi == XfpHzBRcDZ){RFWMmKEZoK = true;}
      while(MSbDyZWIeG == AKLLWgtksZ){XDPgCpezHT = true;}
      while(NISIeCEoRd == NISIeCEoRd){JmXmmlNrIw = true;}
      while(XfpHzBRcDZ == XfpHzBRcDZ){zEoJydRPHM = true;}
      if(AVIHnJGBfR == true){AVIHnJGBfR = false;}
      if(GSeVOSSpJu == true){GSeVOSSpJu = false;}
      if(XBtOTfbUDw == true){XBtOTfbUDw = false;}
      if(ItFEGrAKUU == true){ItFEGrAKUU = false;}
      if(wCIzWFBUrf == true){wCIzWFBUrf = false;}
      if(ibTIBzatnH == true){ibTIBzatnH = false;}
      if(glxiJMNZPW == true){glxiJMNZPW = false;}
      if(SHVnyVrtqO == true){SHVnyVrtqO = false;}
      if(eHbXNfawDH == true){eHbXNfawDH = false;}
      if(RFWMmKEZoK == true){RFWMmKEZoK = false;}
      if(raFVNaFeJf == true){raFVNaFeJf = false;}
      if(GfDYbZJZUd == true){GfDYbZJZUd = false;}
      if(lRWHEMkIAn == true){lRWHEMkIAn = false;}
      if(QSEgWDBFKm == true){QSEgWDBFKm = false;}
      if(aulWAkCxjN == true){aulWAkCxjN = false;}
      if(AeELXaExQA == true){AeELXaExQA = false;}
      if(oxdVPnaVCY == true){oxdVPnaVCY = false;}
      if(XDPgCpezHT == true){XDPgCpezHT = false;}
      if(JmXmmlNrIw == true){JmXmmlNrIw = false;}
      if(zEoJydRPHM == true){zEoJydRPHM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JDTOTAQGTP
{ 
  void ZZaulmGoOC()
  { 
      bool UlZmXBhSum = false;
      bool XJSWofRDPc = false;
      bool LtRLmGeRHF = false;
      bool EwSCUmiwzQ = false;
      bool YaBzMcaath = false;
      bool BGWwyZTNAR = false;
      bool VQKoibqQBB = false;
      bool xVDzEjsSzJ = false;
      bool eDXZDxYVDu = false;
      bool TUwhtIPMQk = false;
      bool kKZrkfDXqN = false;
      bool gBNpmSrkkk = false;
      bool CUMGhbYVFw = false;
      bool UfCOYUdenW = false;
      bool tAepNRGFua = false;
      bool PeaehPxSKI = false;
      bool GhSusAyzRR = false;
      bool nNwNqCpWrP = false;
      bool VTadfpFXgI = false;
      bool XKTfQMhixN = false;
      string qOeDsMVkcN;
      string iteMlLmHtr;
      string oHUzOkJJGf;
      string uZqpkONxiA;
      string dNKkKNrfkc;
      string JYRrDjsfnH;
      string CLdwSICnaW;
      string yoYsObwjnB;
      string scYdWVIylB;
      string UhJbxRjNRB;
      string KEENeTzXdb;
      string mJqmOYmAYw;
      string zDCZBPexww;
      string qhRmpoYKyC;
      string WkUJOLpWMX;
      string djoUBGBeMO;
      string oCahjEqEwZ;
      string AcBVZOirLo;
      string ZIjXRHswlj;
      string mtyiNTKmYJ;
      if(qOeDsMVkcN == KEENeTzXdb){UlZmXBhSum = true;}
      else if(KEENeTzXdb == qOeDsMVkcN){kKZrkfDXqN = true;}
      if(iteMlLmHtr == mJqmOYmAYw){XJSWofRDPc = true;}
      else if(mJqmOYmAYw == iteMlLmHtr){gBNpmSrkkk = true;}
      if(oHUzOkJJGf == zDCZBPexww){LtRLmGeRHF = true;}
      else if(zDCZBPexww == oHUzOkJJGf){CUMGhbYVFw = true;}
      if(uZqpkONxiA == qhRmpoYKyC){EwSCUmiwzQ = true;}
      else if(qhRmpoYKyC == uZqpkONxiA){UfCOYUdenW = true;}
      if(dNKkKNrfkc == WkUJOLpWMX){YaBzMcaath = true;}
      else if(WkUJOLpWMX == dNKkKNrfkc){tAepNRGFua = true;}
      if(JYRrDjsfnH == djoUBGBeMO){BGWwyZTNAR = true;}
      else if(djoUBGBeMO == JYRrDjsfnH){PeaehPxSKI = true;}
      if(CLdwSICnaW == oCahjEqEwZ){VQKoibqQBB = true;}
      else if(oCahjEqEwZ == CLdwSICnaW){GhSusAyzRR = true;}
      if(yoYsObwjnB == AcBVZOirLo){xVDzEjsSzJ = true;}
      if(scYdWVIylB == ZIjXRHswlj){eDXZDxYVDu = true;}
      if(UhJbxRjNRB == mtyiNTKmYJ){TUwhtIPMQk = true;}
      while(AcBVZOirLo == yoYsObwjnB){nNwNqCpWrP = true;}
      while(ZIjXRHswlj == ZIjXRHswlj){VTadfpFXgI = true;}
      while(mtyiNTKmYJ == mtyiNTKmYJ){XKTfQMhixN = true;}
      if(UlZmXBhSum == true){UlZmXBhSum = false;}
      if(XJSWofRDPc == true){XJSWofRDPc = false;}
      if(LtRLmGeRHF == true){LtRLmGeRHF = false;}
      if(EwSCUmiwzQ == true){EwSCUmiwzQ = false;}
      if(YaBzMcaath == true){YaBzMcaath = false;}
      if(BGWwyZTNAR == true){BGWwyZTNAR = false;}
      if(VQKoibqQBB == true){VQKoibqQBB = false;}
      if(xVDzEjsSzJ == true){xVDzEjsSzJ = false;}
      if(eDXZDxYVDu == true){eDXZDxYVDu = false;}
      if(TUwhtIPMQk == true){TUwhtIPMQk = false;}
      if(kKZrkfDXqN == true){kKZrkfDXqN = false;}
      if(gBNpmSrkkk == true){gBNpmSrkkk = false;}
      if(CUMGhbYVFw == true){CUMGhbYVFw = false;}
      if(UfCOYUdenW == true){UfCOYUdenW = false;}
      if(tAepNRGFua == true){tAepNRGFua = false;}
      if(PeaehPxSKI == true){PeaehPxSKI = false;}
      if(GhSusAyzRR == true){GhSusAyzRR = false;}
      if(nNwNqCpWrP == true){nNwNqCpWrP = false;}
      if(VTadfpFXgI == true){VTadfpFXgI = false;}
      if(XKTfQMhixN == true){XKTfQMhixN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HVRQDGOVIY
{ 
  void kGiVlxzJEH()
  { 
      bool fyJzPsSOIr = false;
      bool yKzShdDylJ = false;
      bool RHSOdjyBET = false;
      bool ymxzWsZtqn = false;
      bool MsKIZMSJYN = false;
      bool DCbuuYftUf = false;
      bool uQJotLMAwo = false;
      bool DIHxxYwJnQ = false;
      bool RncpPuLCDx = false;
      bool MfZLswiVNO = false;
      bool ASMjJuuexW = false;
      bool cWGDNGnSYz = false;
      bool zJwzbXiwDA = false;
      bool oauYQyarfU = false;
      bool AgEgUpYVxm = false;
      bool IPwOOpWNIl = false;
      bool LyaxgBagmP = false;
      bool eulEySFPel = false;
      bool zNzQrZdfJZ = false;
      bool bNjtJBFHzS = false;
      string jIjxWHKDnE;
      string kUAoWWPCCE;
      string EGNgdphDsi;
      string ZreNJdhaTa;
      string DdVtpXwqYZ;
      string ibGYWduDSf;
      string ZGKEeromer;
      string oniaBZjSpG;
      string tqeSAylGpf;
      string ieImBxSQPx;
      string hJLfktseXw;
      string scMLlhaqEf;
      string FiwzJKfuZD;
      string HTCsXjezhG;
      string FGhtlGRwBS;
      string VbMirzMMVZ;
      string NxFToYZTmB;
      string CbJxazBCMC;
      string ritGheHSBY;
      string XScHrHBNEN;
      if(jIjxWHKDnE == hJLfktseXw){fyJzPsSOIr = true;}
      else if(hJLfktseXw == jIjxWHKDnE){ASMjJuuexW = true;}
      if(kUAoWWPCCE == scMLlhaqEf){yKzShdDylJ = true;}
      else if(scMLlhaqEf == kUAoWWPCCE){cWGDNGnSYz = true;}
      if(EGNgdphDsi == FiwzJKfuZD){RHSOdjyBET = true;}
      else if(FiwzJKfuZD == EGNgdphDsi){zJwzbXiwDA = true;}
      if(ZreNJdhaTa == HTCsXjezhG){ymxzWsZtqn = true;}
      else if(HTCsXjezhG == ZreNJdhaTa){oauYQyarfU = true;}
      if(DdVtpXwqYZ == FGhtlGRwBS){MsKIZMSJYN = true;}
      else if(FGhtlGRwBS == DdVtpXwqYZ){AgEgUpYVxm = true;}
      if(ibGYWduDSf == VbMirzMMVZ){DCbuuYftUf = true;}
      else if(VbMirzMMVZ == ibGYWduDSf){IPwOOpWNIl = true;}
      if(ZGKEeromer == NxFToYZTmB){uQJotLMAwo = true;}
      else if(NxFToYZTmB == ZGKEeromer){LyaxgBagmP = true;}
      if(oniaBZjSpG == CbJxazBCMC){DIHxxYwJnQ = true;}
      if(tqeSAylGpf == ritGheHSBY){RncpPuLCDx = true;}
      if(ieImBxSQPx == XScHrHBNEN){MfZLswiVNO = true;}
      while(CbJxazBCMC == oniaBZjSpG){eulEySFPel = true;}
      while(ritGheHSBY == ritGheHSBY){zNzQrZdfJZ = true;}
      while(XScHrHBNEN == XScHrHBNEN){bNjtJBFHzS = true;}
      if(fyJzPsSOIr == true){fyJzPsSOIr = false;}
      if(yKzShdDylJ == true){yKzShdDylJ = false;}
      if(RHSOdjyBET == true){RHSOdjyBET = false;}
      if(ymxzWsZtqn == true){ymxzWsZtqn = false;}
      if(MsKIZMSJYN == true){MsKIZMSJYN = false;}
      if(DCbuuYftUf == true){DCbuuYftUf = false;}
      if(uQJotLMAwo == true){uQJotLMAwo = false;}
      if(DIHxxYwJnQ == true){DIHxxYwJnQ = false;}
      if(RncpPuLCDx == true){RncpPuLCDx = false;}
      if(MfZLswiVNO == true){MfZLswiVNO = false;}
      if(ASMjJuuexW == true){ASMjJuuexW = false;}
      if(cWGDNGnSYz == true){cWGDNGnSYz = false;}
      if(zJwzbXiwDA == true){zJwzbXiwDA = false;}
      if(oauYQyarfU == true){oauYQyarfU = false;}
      if(AgEgUpYVxm == true){AgEgUpYVxm = false;}
      if(IPwOOpWNIl == true){IPwOOpWNIl = false;}
      if(LyaxgBagmP == true){LyaxgBagmP = false;}
      if(eulEySFPel == true){eulEySFPel = false;}
      if(zNzQrZdfJZ == true){zNzQrZdfJZ = false;}
      if(bNjtJBFHzS == true){bNjtJBFHzS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YRKDEOXXDE
{ 
  void LFlkywpERS()
  { 
      bool DKqiwufkNp = false;
      bool lEPRfIlHcN = false;
      bool ITEIXzkeXc = false;
      bool ykAwkBMbAb = false;
      bool sbYlAMfTUb = false;
      bool cazpjjFiKw = false;
      bool KBNkrADSgd = false;
      bool uKGAUfuSHL = false;
      bool TRJuzWkKLB = false;
      bool wdQERrOmsA = false;
      bool IMlqfSTzVE = false;
      bool nlazcsqRlU = false;
      bool OsHfhRtCib = false;
      bool QHZHCGeSOg = false;
      bool DloHMJCRbX = false;
      bool AxBXkPFGJN = false;
      bool XQPsmgMSwV = false;
      bool OYCFRcEzTX = false;
      bool PbaLaTFBWm = false;
      bool BYJAIlVuTe = false;
      string zVyprjfaXs;
      string xuffdXqBdT;
      string VNPbezYRNQ;
      string uzjQfRuffA;
      string uyGKmCULSY;
      string PBUOxkGVKs;
      string KOMGyxLPAL;
      string cLVcXWHFoc;
      string eNznBsdUSt;
      string LYUlogkzLp;
      string pFLGwDfrqa;
      string dAghOxOYFF;
      string SqwFzEqinp;
      string lHszlYBrrx;
      string MlcrPKrmXq;
      string SMsGWzIFGr;
      string MxDAnWHguo;
      string uWfIrfNEpn;
      string LEKwXZNmbl;
      string QwkAkPhbDs;
      if(zVyprjfaXs == pFLGwDfrqa){DKqiwufkNp = true;}
      else if(pFLGwDfrqa == zVyprjfaXs){IMlqfSTzVE = true;}
      if(xuffdXqBdT == dAghOxOYFF){lEPRfIlHcN = true;}
      else if(dAghOxOYFF == xuffdXqBdT){nlazcsqRlU = true;}
      if(VNPbezYRNQ == SqwFzEqinp){ITEIXzkeXc = true;}
      else if(SqwFzEqinp == VNPbezYRNQ){OsHfhRtCib = true;}
      if(uzjQfRuffA == lHszlYBrrx){ykAwkBMbAb = true;}
      else if(lHszlYBrrx == uzjQfRuffA){QHZHCGeSOg = true;}
      if(uyGKmCULSY == MlcrPKrmXq){sbYlAMfTUb = true;}
      else if(MlcrPKrmXq == uyGKmCULSY){DloHMJCRbX = true;}
      if(PBUOxkGVKs == SMsGWzIFGr){cazpjjFiKw = true;}
      else if(SMsGWzIFGr == PBUOxkGVKs){AxBXkPFGJN = true;}
      if(KOMGyxLPAL == MxDAnWHguo){KBNkrADSgd = true;}
      else if(MxDAnWHguo == KOMGyxLPAL){XQPsmgMSwV = true;}
      if(cLVcXWHFoc == uWfIrfNEpn){uKGAUfuSHL = true;}
      if(eNznBsdUSt == LEKwXZNmbl){TRJuzWkKLB = true;}
      if(LYUlogkzLp == QwkAkPhbDs){wdQERrOmsA = true;}
      while(uWfIrfNEpn == cLVcXWHFoc){OYCFRcEzTX = true;}
      while(LEKwXZNmbl == LEKwXZNmbl){PbaLaTFBWm = true;}
      while(QwkAkPhbDs == QwkAkPhbDs){BYJAIlVuTe = true;}
      if(DKqiwufkNp == true){DKqiwufkNp = false;}
      if(lEPRfIlHcN == true){lEPRfIlHcN = false;}
      if(ITEIXzkeXc == true){ITEIXzkeXc = false;}
      if(ykAwkBMbAb == true){ykAwkBMbAb = false;}
      if(sbYlAMfTUb == true){sbYlAMfTUb = false;}
      if(cazpjjFiKw == true){cazpjjFiKw = false;}
      if(KBNkrADSgd == true){KBNkrADSgd = false;}
      if(uKGAUfuSHL == true){uKGAUfuSHL = false;}
      if(TRJuzWkKLB == true){TRJuzWkKLB = false;}
      if(wdQERrOmsA == true){wdQERrOmsA = false;}
      if(IMlqfSTzVE == true){IMlqfSTzVE = false;}
      if(nlazcsqRlU == true){nlazcsqRlU = false;}
      if(OsHfhRtCib == true){OsHfhRtCib = false;}
      if(QHZHCGeSOg == true){QHZHCGeSOg = false;}
      if(DloHMJCRbX == true){DloHMJCRbX = false;}
      if(AxBXkPFGJN == true){AxBXkPFGJN = false;}
      if(XQPsmgMSwV == true){XQPsmgMSwV = false;}
      if(OYCFRcEzTX == true){OYCFRcEzTX = false;}
      if(PbaLaTFBWm == true){PbaLaTFBWm = false;}
      if(BYJAIlVuTe == true){BYJAIlVuTe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WIRDQUVQHA
{ 
  void EWCUgLzjPC()
  { 
      bool hXbDfxPIsC = false;
      bool xAajGjGcQB = false;
      bool QxQtGZPSRP = false;
      bool Djnftnzcsx = false;
      bool wBDsiwjnJF = false;
      bool oGDTwjGgwG = false;
      bool hwqdzNMupS = false;
      bool jdjTEPsXLK = false;
      bool obILZwfTjJ = false;
      bool gRfmOzKZtU = false;
      bool joxqULWjOf = false;
      bool piVlQGneDC = false;
      bool hrKgkSxwEF = false;
      bool ETcpZAdQqO = false;
      bool ZuFDSywtVI = false;
      bool LeVqmqdQGC = false;
      bool NZfJaWFeLP = false;
      bool bWnoclmGNl = false;
      bool VCZusYxkCh = false;
      bool WNKnAzPubu = false;
      string izYCSMjEik;
      string FSGSHTqhJi;
      string GeAWUDLFqe;
      string jzJItZlxej;
      string pddzVxybAu;
      string kbTkBDyBhO;
      string BeNDBFJyYg;
      string gtDZrbBABW;
      string FiEwsHfXHq;
      string akOQiLQayP;
      string mzCSNqYsrY;
      string CxzKJRZRJs;
      string ZkqhFwemqg;
      string LaCliFfkhC;
      string hlfhnckDGQ;
      string lzQEpCIUMR;
      string LlCLNauNaD;
      string kniHLmEIsb;
      string LbfZtMKxwg;
      string wLYQpujUUM;
      if(izYCSMjEik == mzCSNqYsrY){hXbDfxPIsC = true;}
      else if(mzCSNqYsrY == izYCSMjEik){joxqULWjOf = true;}
      if(FSGSHTqhJi == CxzKJRZRJs){xAajGjGcQB = true;}
      else if(CxzKJRZRJs == FSGSHTqhJi){piVlQGneDC = true;}
      if(GeAWUDLFqe == ZkqhFwemqg){QxQtGZPSRP = true;}
      else if(ZkqhFwemqg == GeAWUDLFqe){hrKgkSxwEF = true;}
      if(jzJItZlxej == LaCliFfkhC){Djnftnzcsx = true;}
      else if(LaCliFfkhC == jzJItZlxej){ETcpZAdQqO = true;}
      if(pddzVxybAu == hlfhnckDGQ){wBDsiwjnJF = true;}
      else if(hlfhnckDGQ == pddzVxybAu){ZuFDSywtVI = true;}
      if(kbTkBDyBhO == lzQEpCIUMR){oGDTwjGgwG = true;}
      else if(lzQEpCIUMR == kbTkBDyBhO){LeVqmqdQGC = true;}
      if(BeNDBFJyYg == LlCLNauNaD){hwqdzNMupS = true;}
      else if(LlCLNauNaD == BeNDBFJyYg){NZfJaWFeLP = true;}
      if(gtDZrbBABW == kniHLmEIsb){jdjTEPsXLK = true;}
      if(FiEwsHfXHq == LbfZtMKxwg){obILZwfTjJ = true;}
      if(akOQiLQayP == wLYQpujUUM){gRfmOzKZtU = true;}
      while(kniHLmEIsb == gtDZrbBABW){bWnoclmGNl = true;}
      while(LbfZtMKxwg == LbfZtMKxwg){VCZusYxkCh = true;}
      while(wLYQpujUUM == wLYQpujUUM){WNKnAzPubu = true;}
      if(hXbDfxPIsC == true){hXbDfxPIsC = false;}
      if(xAajGjGcQB == true){xAajGjGcQB = false;}
      if(QxQtGZPSRP == true){QxQtGZPSRP = false;}
      if(Djnftnzcsx == true){Djnftnzcsx = false;}
      if(wBDsiwjnJF == true){wBDsiwjnJF = false;}
      if(oGDTwjGgwG == true){oGDTwjGgwG = false;}
      if(hwqdzNMupS == true){hwqdzNMupS = false;}
      if(jdjTEPsXLK == true){jdjTEPsXLK = false;}
      if(obILZwfTjJ == true){obILZwfTjJ = false;}
      if(gRfmOzKZtU == true){gRfmOzKZtU = false;}
      if(joxqULWjOf == true){joxqULWjOf = false;}
      if(piVlQGneDC == true){piVlQGneDC = false;}
      if(hrKgkSxwEF == true){hrKgkSxwEF = false;}
      if(ETcpZAdQqO == true){ETcpZAdQqO = false;}
      if(ZuFDSywtVI == true){ZuFDSywtVI = false;}
      if(LeVqmqdQGC == true){LeVqmqdQGC = false;}
      if(NZfJaWFeLP == true){NZfJaWFeLP = false;}
      if(bWnoclmGNl == true){bWnoclmGNl = false;}
      if(VCZusYxkCh == true){VCZusYxkCh = false;}
      if(WNKnAzPubu == true){WNKnAzPubu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WFAHWOPYOF
{ 
  void NPSzkEFJZH()
  { 
      bool sEPfYkpGrc = false;
      bool RGHIiLlMzp = false;
      bool DWhbeMEkzi = false;
      bool eDIyWeWCwa = false;
      bool mMCFxxyVbM = false;
      bool QwtelVVnAM = false;
      bool gEHIyOxIkE = false;
      bool niQXCqUcdh = false;
      bool OhImShIdMB = false;
      bool JhCjthFsGi = false;
      bool zokXXhfVbt = false;
      bool BrJRxyuUpP = false;
      bool FTwitFgfdT = false;
      bool laVuiYwkOj = false;
      bool ClCRAQYjlu = false;
      bool lkCqcesBcR = false;
      bool BzrHIZWNiX = false;
      bool CKFFNSRdid = false;
      bool gwthgBXeSD = false;
      bool ftIwiCttJa = false;
      string tLdYFpdHaq;
      string XaiJtuKmwk;
      string bBDOJoalZV;
      string qEboaNCpCZ;
      string yxdnQOxdhT;
      string KCRePsIOPP;
      string PqhFzSysig;
      string sTjWmeWPxt;
      string rwEFLomwZh;
      string EmalKGOYox;
      string QDuAZpRurj;
      string VsQUXSlbsJ;
      string fBSAbGrxMf;
      string QyZAdnADeV;
      string WrEoMLVGOq;
      string TleeROjuYT;
      string xUhLTWSQqi;
      string RiwXlnwdnQ;
      string jlhULdTuhO;
      string DFeLXCJsUo;
      if(tLdYFpdHaq == QDuAZpRurj){sEPfYkpGrc = true;}
      else if(QDuAZpRurj == tLdYFpdHaq){zokXXhfVbt = true;}
      if(XaiJtuKmwk == VsQUXSlbsJ){RGHIiLlMzp = true;}
      else if(VsQUXSlbsJ == XaiJtuKmwk){BrJRxyuUpP = true;}
      if(bBDOJoalZV == fBSAbGrxMf){DWhbeMEkzi = true;}
      else if(fBSAbGrxMf == bBDOJoalZV){FTwitFgfdT = true;}
      if(qEboaNCpCZ == QyZAdnADeV){eDIyWeWCwa = true;}
      else if(QyZAdnADeV == qEboaNCpCZ){laVuiYwkOj = true;}
      if(yxdnQOxdhT == WrEoMLVGOq){mMCFxxyVbM = true;}
      else if(WrEoMLVGOq == yxdnQOxdhT){ClCRAQYjlu = true;}
      if(KCRePsIOPP == TleeROjuYT){QwtelVVnAM = true;}
      else if(TleeROjuYT == KCRePsIOPP){lkCqcesBcR = true;}
      if(PqhFzSysig == xUhLTWSQqi){gEHIyOxIkE = true;}
      else if(xUhLTWSQqi == PqhFzSysig){BzrHIZWNiX = true;}
      if(sTjWmeWPxt == RiwXlnwdnQ){niQXCqUcdh = true;}
      if(rwEFLomwZh == jlhULdTuhO){OhImShIdMB = true;}
      if(EmalKGOYox == DFeLXCJsUo){JhCjthFsGi = true;}
      while(RiwXlnwdnQ == sTjWmeWPxt){CKFFNSRdid = true;}
      while(jlhULdTuhO == jlhULdTuhO){gwthgBXeSD = true;}
      while(DFeLXCJsUo == DFeLXCJsUo){ftIwiCttJa = true;}
      if(sEPfYkpGrc == true){sEPfYkpGrc = false;}
      if(RGHIiLlMzp == true){RGHIiLlMzp = false;}
      if(DWhbeMEkzi == true){DWhbeMEkzi = false;}
      if(eDIyWeWCwa == true){eDIyWeWCwa = false;}
      if(mMCFxxyVbM == true){mMCFxxyVbM = false;}
      if(QwtelVVnAM == true){QwtelVVnAM = false;}
      if(gEHIyOxIkE == true){gEHIyOxIkE = false;}
      if(niQXCqUcdh == true){niQXCqUcdh = false;}
      if(OhImShIdMB == true){OhImShIdMB = false;}
      if(JhCjthFsGi == true){JhCjthFsGi = false;}
      if(zokXXhfVbt == true){zokXXhfVbt = false;}
      if(BrJRxyuUpP == true){BrJRxyuUpP = false;}
      if(FTwitFgfdT == true){FTwitFgfdT = false;}
      if(laVuiYwkOj == true){laVuiYwkOj = false;}
      if(ClCRAQYjlu == true){ClCRAQYjlu = false;}
      if(lkCqcesBcR == true){lkCqcesBcR = false;}
      if(BzrHIZWNiX == true){BzrHIZWNiX = false;}
      if(CKFFNSRdid == true){CKFFNSRdid = false;}
      if(gwthgBXeSD == true){gwthgBXeSD = false;}
      if(ftIwiCttJa == true){ftIwiCttJa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AFWLRVUNAZ
{ 
  void FWkYEKBcuN()
  { 
      bool haFZRRRyRX = false;
      bool mzMTWYVdWt = false;
      bool WZFeJVjCri = false;
      bool TGoHWNiEJA = false;
      bool ElRERmdexL = false;
      bool odQCzHVZQw = false;
      bool hOGiEgKFwJ = false;
      bool oRUVojIBNV = false;
      bool qFFftoolHP = false;
      bool qInMSpfhzk = false;
      bool cXhmVWJtMO = false;
      bool zUMtEcIZoO = false;
      bool qXxgRgcHDz = false;
      bool DZBbrSWRJW = false;
      bool euYsPVwsHp = false;
      bool gGsktEaBVo = false;
      bool tBpNKYTjBk = false;
      bool FpQRiuyEQw = false;
      bool kizNRxgPhn = false;
      bool rUwTbdELhq = false;
      string VaAGcJJCym;
      string eSFnNGPbbZ;
      string flGYwqjLMd;
      string POMPgSrWfx;
      string DfWqGHdERX;
      string lAodZiUaKk;
      string YypTWPFpGu;
      string OrwdWzOPRn;
      string NfsnrPZioy;
      string xQMtXEoCTp;
      string CmyWJsDLGa;
      string TFIVWsEBbG;
      string pVAHxxeCFR;
      string JLwbkZgWey;
      string MNbNdrIpWd;
      string znaMzflpYL;
      string NBFoQHJgjx;
      string MhWctbsmcF;
      string ooeaRVkibE;
      string mqyTkLImxV;
      if(VaAGcJJCym == CmyWJsDLGa){haFZRRRyRX = true;}
      else if(CmyWJsDLGa == VaAGcJJCym){cXhmVWJtMO = true;}
      if(eSFnNGPbbZ == TFIVWsEBbG){mzMTWYVdWt = true;}
      else if(TFIVWsEBbG == eSFnNGPbbZ){zUMtEcIZoO = true;}
      if(flGYwqjLMd == pVAHxxeCFR){WZFeJVjCri = true;}
      else if(pVAHxxeCFR == flGYwqjLMd){qXxgRgcHDz = true;}
      if(POMPgSrWfx == JLwbkZgWey){TGoHWNiEJA = true;}
      else if(JLwbkZgWey == POMPgSrWfx){DZBbrSWRJW = true;}
      if(DfWqGHdERX == MNbNdrIpWd){ElRERmdexL = true;}
      else if(MNbNdrIpWd == DfWqGHdERX){euYsPVwsHp = true;}
      if(lAodZiUaKk == znaMzflpYL){odQCzHVZQw = true;}
      else if(znaMzflpYL == lAodZiUaKk){gGsktEaBVo = true;}
      if(YypTWPFpGu == NBFoQHJgjx){hOGiEgKFwJ = true;}
      else if(NBFoQHJgjx == YypTWPFpGu){tBpNKYTjBk = true;}
      if(OrwdWzOPRn == MhWctbsmcF){oRUVojIBNV = true;}
      if(NfsnrPZioy == ooeaRVkibE){qFFftoolHP = true;}
      if(xQMtXEoCTp == mqyTkLImxV){qInMSpfhzk = true;}
      while(MhWctbsmcF == OrwdWzOPRn){FpQRiuyEQw = true;}
      while(ooeaRVkibE == ooeaRVkibE){kizNRxgPhn = true;}
      while(mqyTkLImxV == mqyTkLImxV){rUwTbdELhq = true;}
      if(haFZRRRyRX == true){haFZRRRyRX = false;}
      if(mzMTWYVdWt == true){mzMTWYVdWt = false;}
      if(WZFeJVjCri == true){WZFeJVjCri = false;}
      if(TGoHWNiEJA == true){TGoHWNiEJA = false;}
      if(ElRERmdexL == true){ElRERmdexL = false;}
      if(odQCzHVZQw == true){odQCzHVZQw = false;}
      if(hOGiEgKFwJ == true){hOGiEgKFwJ = false;}
      if(oRUVojIBNV == true){oRUVojIBNV = false;}
      if(qFFftoolHP == true){qFFftoolHP = false;}
      if(qInMSpfhzk == true){qInMSpfhzk = false;}
      if(cXhmVWJtMO == true){cXhmVWJtMO = false;}
      if(zUMtEcIZoO == true){zUMtEcIZoO = false;}
      if(qXxgRgcHDz == true){qXxgRgcHDz = false;}
      if(DZBbrSWRJW == true){DZBbrSWRJW = false;}
      if(euYsPVwsHp == true){euYsPVwsHp = false;}
      if(gGsktEaBVo == true){gGsktEaBVo = false;}
      if(tBpNKYTjBk == true){tBpNKYTjBk = false;}
      if(FpQRiuyEQw == true){FpQRiuyEQw = false;}
      if(kizNRxgPhn == true){kizNRxgPhn = false;}
      if(rUwTbdELhq == true){rUwTbdELhq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGVVAKEHQU
{ 
  void oMUpbLmtfn()
  { 
      bool mPdBglhbCe = false;
      bool wyepFHlIic = false;
      bool nqJtGSSXPE = false;
      bool asVLAdEAGp = false;
      bool oajPgfYTJu = false;
      bool SmaCawGitN = false;
      bool TJLyDDbSoa = false;
      bool CkCrnNGtMa = false;
      bool syOUkmRSjD = false;
      bool XUGrWeOkLc = false;
      bool DGdirgkiON = false;
      bool pLVSUUuqMP = false;
      bool lJhlChdKUJ = false;
      bool yViiWmTfbD = false;
      bool CiEWNMymXB = false;
      bool jXXuqtXrfK = false;
      bool DaNFPTclwg = false;
      bool AOPINDELXo = false;
      bool iqmTYaxmrb = false;
      bool ObzQAbUzHs = false;
      string eeAbdyAEPF;
      string uzgPgVAUtw;
      string JnqhWBRJak;
      string kxBalglJeR;
      string XyjgRVnRjy;
      string RRQbDqmREc;
      string gqceTyxFcz;
      string iqpcYLDKQB;
      string MzZcSTgYXt;
      string sUFCkfUFMT;
      string XhojOabnDq;
      string nbACPgRALA;
      string QXhhFOknqr;
      string qxywddKoNr;
      string rsVfGRTClD;
      string OTtLCzAGez;
      string omwLAqdDYk;
      string WclSIXCBbn;
      string thBmcWCmtd;
      string dDJOCEwJfP;
      if(eeAbdyAEPF == XhojOabnDq){mPdBglhbCe = true;}
      else if(XhojOabnDq == eeAbdyAEPF){DGdirgkiON = true;}
      if(uzgPgVAUtw == nbACPgRALA){wyepFHlIic = true;}
      else if(nbACPgRALA == uzgPgVAUtw){pLVSUUuqMP = true;}
      if(JnqhWBRJak == QXhhFOknqr){nqJtGSSXPE = true;}
      else if(QXhhFOknqr == JnqhWBRJak){lJhlChdKUJ = true;}
      if(kxBalglJeR == qxywddKoNr){asVLAdEAGp = true;}
      else if(qxywddKoNr == kxBalglJeR){yViiWmTfbD = true;}
      if(XyjgRVnRjy == rsVfGRTClD){oajPgfYTJu = true;}
      else if(rsVfGRTClD == XyjgRVnRjy){CiEWNMymXB = true;}
      if(RRQbDqmREc == OTtLCzAGez){SmaCawGitN = true;}
      else if(OTtLCzAGez == RRQbDqmREc){jXXuqtXrfK = true;}
      if(gqceTyxFcz == omwLAqdDYk){TJLyDDbSoa = true;}
      else if(omwLAqdDYk == gqceTyxFcz){DaNFPTclwg = true;}
      if(iqpcYLDKQB == WclSIXCBbn){CkCrnNGtMa = true;}
      if(MzZcSTgYXt == thBmcWCmtd){syOUkmRSjD = true;}
      if(sUFCkfUFMT == dDJOCEwJfP){XUGrWeOkLc = true;}
      while(WclSIXCBbn == iqpcYLDKQB){AOPINDELXo = true;}
      while(thBmcWCmtd == thBmcWCmtd){iqmTYaxmrb = true;}
      while(dDJOCEwJfP == dDJOCEwJfP){ObzQAbUzHs = true;}
      if(mPdBglhbCe == true){mPdBglhbCe = false;}
      if(wyepFHlIic == true){wyepFHlIic = false;}
      if(nqJtGSSXPE == true){nqJtGSSXPE = false;}
      if(asVLAdEAGp == true){asVLAdEAGp = false;}
      if(oajPgfYTJu == true){oajPgfYTJu = false;}
      if(SmaCawGitN == true){SmaCawGitN = false;}
      if(TJLyDDbSoa == true){TJLyDDbSoa = false;}
      if(CkCrnNGtMa == true){CkCrnNGtMa = false;}
      if(syOUkmRSjD == true){syOUkmRSjD = false;}
      if(XUGrWeOkLc == true){XUGrWeOkLc = false;}
      if(DGdirgkiON == true){DGdirgkiON = false;}
      if(pLVSUUuqMP == true){pLVSUUuqMP = false;}
      if(lJhlChdKUJ == true){lJhlChdKUJ = false;}
      if(yViiWmTfbD == true){yViiWmTfbD = false;}
      if(CiEWNMymXB == true){CiEWNMymXB = false;}
      if(jXXuqtXrfK == true){jXXuqtXrfK = false;}
      if(DaNFPTclwg == true){DaNFPTclwg = false;}
      if(AOPINDELXo == true){AOPINDELXo = false;}
      if(iqmTYaxmrb == true){iqmTYaxmrb = false;}
      if(ObzQAbUzHs == true){ObzQAbUzHs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGQXQUHROU
{ 
  void YIPrtIpgrw()
  { 
      bool TSMHniQgMI = false;
      bool MYJdbEasIJ = false;
      bool lsRhqrunJd = false;
      bool hLNJgqKTSl = false;
      bool BGwtbfqSGM = false;
      bool bqKsKaBeQu = false;
      bool mcXhaBLAwj = false;
      bool tHZVIewWGK = false;
      bool BbgxCqBUzF = false;
      bool peCXyXiNTa = false;
      bool UqVWRUQnje = false;
      bool eeYFsLwZfi = false;
      bool zpAqtOECWj = false;
      bool whCeoKFJeg = false;
      bool aNjTaKGwdm = false;
      bool bJhkaepebD = false;
      bool PNQAiwbsQi = false;
      bool FltyIlFgPi = false;
      bool IHXjImAREK = false;
      bool TZhbQMwjje = false;
      string reahUphpHf;
      string TyCGNprMsq;
      string ZyqPaoVgmJ;
      string EsunlOAufM;
      string xkZHFXCMBc;
      string fPUVYtnKHf;
      string TADxaaCNTy;
      string owgfsnXiJC;
      string lJfJcoXZPr;
      string apnzrwhbfd;
      string VorDmjinbj;
      string VEBEtKUsTl;
      string CcxbXzHgnx;
      string GwCfgxQbWs;
      string FjxfVVnjFg;
      string bnIsbrqPem;
      string bCzdcZBVWx;
      string srWagSeRGB;
      string KXbGVSnIDo;
      string FAxiQCjSDw;
      if(reahUphpHf == VorDmjinbj){TSMHniQgMI = true;}
      else if(VorDmjinbj == reahUphpHf){UqVWRUQnje = true;}
      if(TyCGNprMsq == VEBEtKUsTl){MYJdbEasIJ = true;}
      else if(VEBEtKUsTl == TyCGNprMsq){eeYFsLwZfi = true;}
      if(ZyqPaoVgmJ == CcxbXzHgnx){lsRhqrunJd = true;}
      else if(CcxbXzHgnx == ZyqPaoVgmJ){zpAqtOECWj = true;}
      if(EsunlOAufM == GwCfgxQbWs){hLNJgqKTSl = true;}
      else if(GwCfgxQbWs == EsunlOAufM){whCeoKFJeg = true;}
      if(xkZHFXCMBc == FjxfVVnjFg){BGwtbfqSGM = true;}
      else if(FjxfVVnjFg == xkZHFXCMBc){aNjTaKGwdm = true;}
      if(fPUVYtnKHf == bnIsbrqPem){bqKsKaBeQu = true;}
      else if(bnIsbrqPem == fPUVYtnKHf){bJhkaepebD = true;}
      if(TADxaaCNTy == bCzdcZBVWx){mcXhaBLAwj = true;}
      else if(bCzdcZBVWx == TADxaaCNTy){PNQAiwbsQi = true;}
      if(owgfsnXiJC == srWagSeRGB){tHZVIewWGK = true;}
      if(lJfJcoXZPr == KXbGVSnIDo){BbgxCqBUzF = true;}
      if(apnzrwhbfd == FAxiQCjSDw){peCXyXiNTa = true;}
      while(srWagSeRGB == owgfsnXiJC){FltyIlFgPi = true;}
      while(KXbGVSnIDo == KXbGVSnIDo){IHXjImAREK = true;}
      while(FAxiQCjSDw == FAxiQCjSDw){TZhbQMwjje = true;}
      if(TSMHniQgMI == true){TSMHniQgMI = false;}
      if(MYJdbEasIJ == true){MYJdbEasIJ = false;}
      if(lsRhqrunJd == true){lsRhqrunJd = false;}
      if(hLNJgqKTSl == true){hLNJgqKTSl = false;}
      if(BGwtbfqSGM == true){BGwtbfqSGM = false;}
      if(bqKsKaBeQu == true){bqKsKaBeQu = false;}
      if(mcXhaBLAwj == true){mcXhaBLAwj = false;}
      if(tHZVIewWGK == true){tHZVIewWGK = false;}
      if(BbgxCqBUzF == true){BbgxCqBUzF = false;}
      if(peCXyXiNTa == true){peCXyXiNTa = false;}
      if(UqVWRUQnje == true){UqVWRUQnje = false;}
      if(eeYFsLwZfi == true){eeYFsLwZfi = false;}
      if(zpAqtOECWj == true){zpAqtOECWj = false;}
      if(whCeoKFJeg == true){whCeoKFJeg = false;}
      if(aNjTaKGwdm == true){aNjTaKGwdm = false;}
      if(bJhkaepebD == true){bJhkaepebD = false;}
      if(PNQAiwbsQi == true){PNQAiwbsQi = false;}
      if(FltyIlFgPi == true){FltyIlFgPi = false;}
      if(IHXjImAREK == true){IHXjImAREK = false;}
      if(TZhbQMwjje == true){TZhbQMwjje = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ACNLURWKIH
{ 
  void eEKdjBcWJm()
  { 
      bool jwufGUipFG = false;
      bool SHpqKbXmna = false;
      bool IQkgtqtXkY = false;
      bool YNHSHrXVks = false;
      bool mcwmUFRyCV = false;
      bool CMfitTLNlO = false;
      bool aLEfhFAXjS = false;
      bool ECCtmeUyMo = false;
      bool ZuVOWMgYXm = false;
      bool gJiVSbYPEP = false;
      bool EtOiRzJluP = false;
      bool zMBwoeooIV = false;
      bool XbzwluSgaL = false;
      bool GEswjfglxW = false;
      bool CudInTImgm = false;
      bool ljGirctRxW = false;
      bool gcKiJtTEMJ = false;
      bool xCqlSbypHS = false;
      bool lfzmZVxJEG = false;
      bool kOoapYjtzt = false;
      string RyNMZMIQNL;
      string QBRWWmxeHH;
      string JAUBEyFynM;
      string zGBySDqkIi;
      string YwDNsHPTwK;
      string pkAGBRdMIa;
      string HKbALJATDT;
      string uLWYhMwGIw;
      string hlBcWNGtwB;
      string YebgbNUDBi;
      string GwPcPdObXo;
      string VWDLsVIzcx;
      string DFXCtPioxU;
      string rsFYplVYNs;
      string zdWGfCaQnG;
      string FVZDfBYNiz;
      string tYdCxbReVH;
      string zjljyYhQWq;
      string nSBqOWTBsn;
      string MIoNyZATJD;
      if(RyNMZMIQNL == GwPcPdObXo){jwufGUipFG = true;}
      else if(GwPcPdObXo == RyNMZMIQNL){EtOiRzJluP = true;}
      if(QBRWWmxeHH == VWDLsVIzcx){SHpqKbXmna = true;}
      else if(VWDLsVIzcx == QBRWWmxeHH){zMBwoeooIV = true;}
      if(JAUBEyFynM == DFXCtPioxU){IQkgtqtXkY = true;}
      else if(DFXCtPioxU == JAUBEyFynM){XbzwluSgaL = true;}
      if(zGBySDqkIi == rsFYplVYNs){YNHSHrXVks = true;}
      else if(rsFYplVYNs == zGBySDqkIi){GEswjfglxW = true;}
      if(YwDNsHPTwK == zdWGfCaQnG){mcwmUFRyCV = true;}
      else if(zdWGfCaQnG == YwDNsHPTwK){CudInTImgm = true;}
      if(pkAGBRdMIa == FVZDfBYNiz){CMfitTLNlO = true;}
      else if(FVZDfBYNiz == pkAGBRdMIa){ljGirctRxW = true;}
      if(HKbALJATDT == tYdCxbReVH){aLEfhFAXjS = true;}
      else if(tYdCxbReVH == HKbALJATDT){gcKiJtTEMJ = true;}
      if(uLWYhMwGIw == zjljyYhQWq){ECCtmeUyMo = true;}
      if(hlBcWNGtwB == nSBqOWTBsn){ZuVOWMgYXm = true;}
      if(YebgbNUDBi == MIoNyZATJD){gJiVSbYPEP = true;}
      while(zjljyYhQWq == uLWYhMwGIw){xCqlSbypHS = true;}
      while(nSBqOWTBsn == nSBqOWTBsn){lfzmZVxJEG = true;}
      while(MIoNyZATJD == MIoNyZATJD){kOoapYjtzt = true;}
      if(jwufGUipFG == true){jwufGUipFG = false;}
      if(SHpqKbXmna == true){SHpqKbXmna = false;}
      if(IQkgtqtXkY == true){IQkgtqtXkY = false;}
      if(YNHSHrXVks == true){YNHSHrXVks = false;}
      if(mcwmUFRyCV == true){mcwmUFRyCV = false;}
      if(CMfitTLNlO == true){CMfitTLNlO = false;}
      if(aLEfhFAXjS == true){aLEfhFAXjS = false;}
      if(ECCtmeUyMo == true){ECCtmeUyMo = false;}
      if(ZuVOWMgYXm == true){ZuVOWMgYXm = false;}
      if(gJiVSbYPEP == true){gJiVSbYPEP = false;}
      if(EtOiRzJluP == true){EtOiRzJluP = false;}
      if(zMBwoeooIV == true){zMBwoeooIV = false;}
      if(XbzwluSgaL == true){XbzwluSgaL = false;}
      if(GEswjfglxW == true){GEswjfglxW = false;}
      if(CudInTImgm == true){CudInTImgm = false;}
      if(ljGirctRxW == true){ljGirctRxW = false;}
      if(gcKiJtTEMJ == true){gcKiJtTEMJ = false;}
      if(xCqlSbypHS == true){xCqlSbypHS = false;}
      if(lfzmZVxJEG == true){lfzmZVxJEG = false;}
      if(kOoapYjtzt == true){kOoapYjtzt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCLFWIRDJO
{ 
  void GebOsgkdSR()
  { 
      bool cWTDGlkzdL = false;
      bool QlGwmqRmkz = false;
      bool kzMDKrxyuT = false;
      bool ttBFnnyBXP = false;
      bool zGbwTDOZRK = false;
      bool pghlTcJQsN = false;
      bool olEKQVjBHz = false;
      bool sQOVAeXQjG = false;
      bool dWgkcMLOlK = false;
      bool egIKZMBRfx = false;
      bool TMRSQZRMlo = false;
      bool FsgliSFTgD = false;
      bool JUPxULHEum = false;
      bool cFjlmREOTD = false;
      bool tzcxEkAVbH = false;
      bool HhjbnyxUyE = false;
      bool SNRyLAItzR = false;
      bool NpzdIKrSsi = false;
      bool LkcmftUIyn = false;
      bool TjQOkghdkE = false;
      string LRUXlsLUXx;
      string DqxjFMaLEV;
      string gMSCyWfMGU;
      string YtPJnCNmhi;
      string GKGooeXUQA;
      string YKnLeyyRYO;
      string MyNDXJanwD;
      string yncVPVFdNT;
      string zLwGuOGEeo;
      string DuNTVHwDQe;
      string DjYMBjgRwI;
      string sTDEPBCHHJ;
      string DWJGACaJzH;
      string YBNiQPmiEK;
      string gnIVwiqIDU;
      string FowGafZRMy;
      string JXSnjqGUnA;
      string NSDwcPOnKQ;
      string LRFeCjFGHk;
      string oUVFBIUTlE;
      if(LRUXlsLUXx == DjYMBjgRwI){cWTDGlkzdL = true;}
      else if(DjYMBjgRwI == LRUXlsLUXx){TMRSQZRMlo = true;}
      if(DqxjFMaLEV == sTDEPBCHHJ){QlGwmqRmkz = true;}
      else if(sTDEPBCHHJ == DqxjFMaLEV){FsgliSFTgD = true;}
      if(gMSCyWfMGU == DWJGACaJzH){kzMDKrxyuT = true;}
      else if(DWJGACaJzH == gMSCyWfMGU){JUPxULHEum = true;}
      if(YtPJnCNmhi == YBNiQPmiEK){ttBFnnyBXP = true;}
      else if(YBNiQPmiEK == YtPJnCNmhi){cFjlmREOTD = true;}
      if(GKGooeXUQA == gnIVwiqIDU){zGbwTDOZRK = true;}
      else if(gnIVwiqIDU == GKGooeXUQA){tzcxEkAVbH = true;}
      if(YKnLeyyRYO == FowGafZRMy){pghlTcJQsN = true;}
      else if(FowGafZRMy == YKnLeyyRYO){HhjbnyxUyE = true;}
      if(MyNDXJanwD == JXSnjqGUnA){olEKQVjBHz = true;}
      else if(JXSnjqGUnA == MyNDXJanwD){SNRyLAItzR = true;}
      if(yncVPVFdNT == NSDwcPOnKQ){sQOVAeXQjG = true;}
      if(zLwGuOGEeo == LRFeCjFGHk){dWgkcMLOlK = true;}
      if(DuNTVHwDQe == oUVFBIUTlE){egIKZMBRfx = true;}
      while(NSDwcPOnKQ == yncVPVFdNT){NpzdIKrSsi = true;}
      while(LRFeCjFGHk == LRFeCjFGHk){LkcmftUIyn = true;}
      while(oUVFBIUTlE == oUVFBIUTlE){TjQOkghdkE = true;}
      if(cWTDGlkzdL == true){cWTDGlkzdL = false;}
      if(QlGwmqRmkz == true){QlGwmqRmkz = false;}
      if(kzMDKrxyuT == true){kzMDKrxyuT = false;}
      if(ttBFnnyBXP == true){ttBFnnyBXP = false;}
      if(zGbwTDOZRK == true){zGbwTDOZRK = false;}
      if(pghlTcJQsN == true){pghlTcJQsN = false;}
      if(olEKQVjBHz == true){olEKQVjBHz = false;}
      if(sQOVAeXQjG == true){sQOVAeXQjG = false;}
      if(dWgkcMLOlK == true){dWgkcMLOlK = false;}
      if(egIKZMBRfx == true){egIKZMBRfx = false;}
      if(TMRSQZRMlo == true){TMRSQZRMlo = false;}
      if(FsgliSFTgD == true){FsgliSFTgD = false;}
      if(JUPxULHEum == true){JUPxULHEum = false;}
      if(cFjlmREOTD == true){cFjlmREOTD = false;}
      if(tzcxEkAVbH == true){tzcxEkAVbH = false;}
      if(HhjbnyxUyE == true){HhjbnyxUyE = false;}
      if(SNRyLAItzR == true){SNRyLAItzR = false;}
      if(NpzdIKrSsi == true){NpzdIKrSsi = false;}
      if(LkcmftUIyn == true){LkcmftUIyn = false;}
      if(TjQOkghdkE == true){TjQOkghdkE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QCSMFOANFI
{ 
  void QjBVcqqRkP()
  { 
      bool jDKFIWlxLh = false;
      bool eiXjpfsKNG = false;
      bool FDbeAsyyiL = false;
      bool qpAeejEgGc = false;
      bool jcyLKqDzYq = false;
      bool qCiYafaeEO = false;
      bool YmNzpnisFG = false;
      bool aLDjWcEPUI = false;
      bool pzZrToHaDy = false;
      bool IZbqEwOyVV = false;
      bool IKsSPeyyCy = false;
      bool aKJuYZNVfA = false;
      bool gHoHxBjMfZ = false;
      bool NGtzAeFHbo = false;
      bool qIXFWxPfRe = false;
      bool isSUoAUlUO = false;
      bool ulSbjUQKut = false;
      bool TFsqJYijjz = false;
      bool kDtBqUmYKz = false;
      bool KTmNsFowVB = false;
      string WmFacNBAjH;
      string hEqVbjRnPF;
      string SKZpXKOrND;
      string hhZnensMTJ;
      string eqHqdxKxyg;
      string uTZtcLMPDS;
      string yJlfZzeCqm;
      string pEUFZbDiLZ;
      string zRsgIOHeLT;
      string bdIALUEaRe;
      string RHGKppzUTA;
      string HdDcSgPEXK;
      string rzqWLMuTtF;
      string WcQgIqLhqR;
      string PmLKLxZfgd;
      string EACGmSQizc;
      string ueZOdeNWUb;
      string VhNFuEmgKO;
      string mPlPAWZJto;
      string abiOWjMxff;
      if(WmFacNBAjH == RHGKppzUTA){jDKFIWlxLh = true;}
      else if(RHGKppzUTA == WmFacNBAjH){IKsSPeyyCy = true;}
      if(hEqVbjRnPF == HdDcSgPEXK){eiXjpfsKNG = true;}
      else if(HdDcSgPEXK == hEqVbjRnPF){aKJuYZNVfA = true;}
      if(SKZpXKOrND == rzqWLMuTtF){FDbeAsyyiL = true;}
      else if(rzqWLMuTtF == SKZpXKOrND){gHoHxBjMfZ = true;}
      if(hhZnensMTJ == WcQgIqLhqR){qpAeejEgGc = true;}
      else if(WcQgIqLhqR == hhZnensMTJ){NGtzAeFHbo = true;}
      if(eqHqdxKxyg == PmLKLxZfgd){jcyLKqDzYq = true;}
      else if(PmLKLxZfgd == eqHqdxKxyg){qIXFWxPfRe = true;}
      if(uTZtcLMPDS == EACGmSQizc){qCiYafaeEO = true;}
      else if(EACGmSQizc == uTZtcLMPDS){isSUoAUlUO = true;}
      if(yJlfZzeCqm == ueZOdeNWUb){YmNzpnisFG = true;}
      else if(ueZOdeNWUb == yJlfZzeCqm){ulSbjUQKut = true;}
      if(pEUFZbDiLZ == VhNFuEmgKO){aLDjWcEPUI = true;}
      if(zRsgIOHeLT == mPlPAWZJto){pzZrToHaDy = true;}
      if(bdIALUEaRe == abiOWjMxff){IZbqEwOyVV = true;}
      while(VhNFuEmgKO == pEUFZbDiLZ){TFsqJYijjz = true;}
      while(mPlPAWZJto == mPlPAWZJto){kDtBqUmYKz = true;}
      while(abiOWjMxff == abiOWjMxff){KTmNsFowVB = true;}
      if(jDKFIWlxLh == true){jDKFIWlxLh = false;}
      if(eiXjpfsKNG == true){eiXjpfsKNG = false;}
      if(FDbeAsyyiL == true){FDbeAsyyiL = false;}
      if(qpAeejEgGc == true){qpAeejEgGc = false;}
      if(jcyLKqDzYq == true){jcyLKqDzYq = false;}
      if(qCiYafaeEO == true){qCiYafaeEO = false;}
      if(YmNzpnisFG == true){YmNzpnisFG = false;}
      if(aLDjWcEPUI == true){aLDjWcEPUI = false;}
      if(pzZrToHaDy == true){pzZrToHaDy = false;}
      if(IZbqEwOyVV == true){IZbqEwOyVV = false;}
      if(IKsSPeyyCy == true){IKsSPeyyCy = false;}
      if(aKJuYZNVfA == true){aKJuYZNVfA = false;}
      if(gHoHxBjMfZ == true){gHoHxBjMfZ = false;}
      if(NGtzAeFHbo == true){NGtzAeFHbo = false;}
      if(qIXFWxPfRe == true){qIXFWxPfRe = false;}
      if(isSUoAUlUO == true){isSUoAUlUO = false;}
      if(ulSbjUQKut == true){ulSbjUQKut = false;}
      if(TFsqJYijjz == true){TFsqJYijjz = false;}
      if(kDtBqUmYKz == true){kDtBqUmYKz = false;}
      if(KTmNsFowVB == true){KTmNsFowVB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UXAFIQTCOM
{ 
  void JZeYGQTFzq()
  { 
      bool KVoTaHRVjr = false;
      bool PeqRyhjzjd = false;
      bool XJadUUsQrJ = false;
      bool FLuQGVudkl = false;
      bool RtGcOTYsbJ = false;
      bool pdpBZAtKzF = false;
      bool NBdZmDjaLc = false;
      bool lFNxMcDxOB = false;
      bool wAniTaVtqF = false;
      bool ajeeYQQgpL = false;
      bool iygyWkPrnw = false;
      bool xwwyJMMtFL = false;
      bool hoiFCBZiYw = false;
      bool MWHDRySoMi = false;
      bool KdFuIdngVL = false;
      bool DVadcsObwU = false;
      bool KgSriZorfK = false;
      bool tXhVAEjnwX = false;
      bool NsMNrqucZX = false;
      bool jqrqYdKNLh = false;
      string HkiegJZKtT;
      string ojeVybiRop;
      string wbEqKabRlm;
      string xtzLaBFKSA;
      string VnGhtgtAJW;
      string aTXHNefqUF;
      string hIXGVtkStx;
      string WYzoUIVVxd;
      string gaHPMcWryu;
      string UNoMRNQzMz;
      string uaFMzCUhlF;
      string JJtqYGAHtr;
      string XrUzcJilWH;
      string qVJxhFVuQK;
      string InFskKSymL;
      string MIFTbCGFjo;
      string ShKeNnAxIT;
      string kFqijimaOR;
      string qkyLtiPpVe;
      string yPLaqZdafx;
      if(HkiegJZKtT == uaFMzCUhlF){KVoTaHRVjr = true;}
      else if(uaFMzCUhlF == HkiegJZKtT){iygyWkPrnw = true;}
      if(ojeVybiRop == JJtqYGAHtr){PeqRyhjzjd = true;}
      else if(JJtqYGAHtr == ojeVybiRop){xwwyJMMtFL = true;}
      if(wbEqKabRlm == XrUzcJilWH){XJadUUsQrJ = true;}
      else if(XrUzcJilWH == wbEqKabRlm){hoiFCBZiYw = true;}
      if(xtzLaBFKSA == qVJxhFVuQK){FLuQGVudkl = true;}
      else if(qVJxhFVuQK == xtzLaBFKSA){MWHDRySoMi = true;}
      if(VnGhtgtAJW == InFskKSymL){RtGcOTYsbJ = true;}
      else if(InFskKSymL == VnGhtgtAJW){KdFuIdngVL = true;}
      if(aTXHNefqUF == MIFTbCGFjo){pdpBZAtKzF = true;}
      else if(MIFTbCGFjo == aTXHNefqUF){DVadcsObwU = true;}
      if(hIXGVtkStx == ShKeNnAxIT){NBdZmDjaLc = true;}
      else if(ShKeNnAxIT == hIXGVtkStx){KgSriZorfK = true;}
      if(WYzoUIVVxd == kFqijimaOR){lFNxMcDxOB = true;}
      if(gaHPMcWryu == qkyLtiPpVe){wAniTaVtqF = true;}
      if(UNoMRNQzMz == yPLaqZdafx){ajeeYQQgpL = true;}
      while(kFqijimaOR == WYzoUIVVxd){tXhVAEjnwX = true;}
      while(qkyLtiPpVe == qkyLtiPpVe){NsMNrqucZX = true;}
      while(yPLaqZdafx == yPLaqZdafx){jqrqYdKNLh = true;}
      if(KVoTaHRVjr == true){KVoTaHRVjr = false;}
      if(PeqRyhjzjd == true){PeqRyhjzjd = false;}
      if(XJadUUsQrJ == true){XJadUUsQrJ = false;}
      if(FLuQGVudkl == true){FLuQGVudkl = false;}
      if(RtGcOTYsbJ == true){RtGcOTYsbJ = false;}
      if(pdpBZAtKzF == true){pdpBZAtKzF = false;}
      if(NBdZmDjaLc == true){NBdZmDjaLc = false;}
      if(lFNxMcDxOB == true){lFNxMcDxOB = false;}
      if(wAniTaVtqF == true){wAniTaVtqF = false;}
      if(ajeeYQQgpL == true){ajeeYQQgpL = false;}
      if(iygyWkPrnw == true){iygyWkPrnw = false;}
      if(xwwyJMMtFL == true){xwwyJMMtFL = false;}
      if(hoiFCBZiYw == true){hoiFCBZiYw = false;}
      if(MWHDRySoMi == true){MWHDRySoMi = false;}
      if(KdFuIdngVL == true){KdFuIdngVL = false;}
      if(DVadcsObwU == true){DVadcsObwU = false;}
      if(KgSriZorfK == true){KgSriZorfK = false;}
      if(tXhVAEjnwX == true){tXhVAEjnwX = false;}
      if(NsMNrqucZX == true){NsMNrqucZX = false;}
      if(jqrqYdKNLh == true){jqrqYdKNLh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQZVXUDVMW
{ 
  void aLQuHwuNLd()
  { 
      bool grRwObBFQy = false;
      bool cjZSUXJkek = false;
      bool ewwKdgTyZq = false;
      bool FylMRUuTHq = false;
      bool mjwZmNTHwK = false;
      bool LeWBMjwHRh = false;
      bool ICeZsexNBz = false;
      bool bodmytAVWQ = false;
      bool NLCPeaakzh = false;
      bool YnCYijEVgI = false;
      bool QFGxhVAjDS = false;
      bool iZjBUwAPtR = false;
      bool DLNTZnmEEN = false;
      bool odnNzHFEhJ = false;
      bool ZqhgyzDBEl = false;
      bool jobPEErlWs = false;
      bool hwfodFkVBN = false;
      bool quhkqMdgVa = false;
      bool klARdzCYJt = false;
      bool OShoadLrCr = false;
      string guhnHmWDFd;
      string xSoErKfnIy;
      string yPWJsWTjcU;
      string QLdMCNDKrI;
      string yJXxATVyjR;
      string LJUoUQYYuj;
      string TmajNkobCd;
      string GUwAAorYIY;
      string AUzKJHqnqk;
      string oeOHnKhniO;
      string eswGKpMTnf;
      string YzPViznQZG;
      string sAkQnbGnLp;
      string GDpttGYsAS;
      string tXALMpOsXo;
      string WRNcUdIeRh;
      string jYHyZUJVab;
      string ZtQHLVAYEy;
      string NMPWSnpMYQ;
      string ysaRhUPClq;
      if(guhnHmWDFd == eswGKpMTnf){grRwObBFQy = true;}
      else if(eswGKpMTnf == guhnHmWDFd){QFGxhVAjDS = true;}
      if(xSoErKfnIy == YzPViznQZG){cjZSUXJkek = true;}
      else if(YzPViznQZG == xSoErKfnIy){iZjBUwAPtR = true;}
      if(yPWJsWTjcU == sAkQnbGnLp){ewwKdgTyZq = true;}
      else if(sAkQnbGnLp == yPWJsWTjcU){DLNTZnmEEN = true;}
      if(QLdMCNDKrI == GDpttGYsAS){FylMRUuTHq = true;}
      else if(GDpttGYsAS == QLdMCNDKrI){odnNzHFEhJ = true;}
      if(yJXxATVyjR == tXALMpOsXo){mjwZmNTHwK = true;}
      else if(tXALMpOsXo == yJXxATVyjR){ZqhgyzDBEl = true;}
      if(LJUoUQYYuj == WRNcUdIeRh){LeWBMjwHRh = true;}
      else if(WRNcUdIeRh == LJUoUQYYuj){jobPEErlWs = true;}
      if(TmajNkobCd == jYHyZUJVab){ICeZsexNBz = true;}
      else if(jYHyZUJVab == TmajNkobCd){hwfodFkVBN = true;}
      if(GUwAAorYIY == ZtQHLVAYEy){bodmytAVWQ = true;}
      if(AUzKJHqnqk == NMPWSnpMYQ){NLCPeaakzh = true;}
      if(oeOHnKhniO == ysaRhUPClq){YnCYijEVgI = true;}
      while(ZtQHLVAYEy == GUwAAorYIY){quhkqMdgVa = true;}
      while(NMPWSnpMYQ == NMPWSnpMYQ){klARdzCYJt = true;}
      while(ysaRhUPClq == ysaRhUPClq){OShoadLrCr = true;}
      if(grRwObBFQy == true){grRwObBFQy = false;}
      if(cjZSUXJkek == true){cjZSUXJkek = false;}
      if(ewwKdgTyZq == true){ewwKdgTyZq = false;}
      if(FylMRUuTHq == true){FylMRUuTHq = false;}
      if(mjwZmNTHwK == true){mjwZmNTHwK = false;}
      if(LeWBMjwHRh == true){LeWBMjwHRh = false;}
      if(ICeZsexNBz == true){ICeZsexNBz = false;}
      if(bodmytAVWQ == true){bodmytAVWQ = false;}
      if(NLCPeaakzh == true){NLCPeaakzh = false;}
      if(YnCYijEVgI == true){YnCYijEVgI = false;}
      if(QFGxhVAjDS == true){QFGxhVAjDS = false;}
      if(iZjBUwAPtR == true){iZjBUwAPtR = false;}
      if(DLNTZnmEEN == true){DLNTZnmEEN = false;}
      if(odnNzHFEhJ == true){odnNzHFEhJ = false;}
      if(ZqhgyzDBEl == true){ZqhgyzDBEl = false;}
      if(jobPEErlWs == true){jobPEErlWs = false;}
      if(hwfodFkVBN == true){hwfodFkVBN = false;}
      if(quhkqMdgVa == true){quhkqMdgVa = false;}
      if(klARdzCYJt == true){klARdzCYJt = false;}
      if(OShoadLrCr == true){OShoadLrCr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ETCIYZOBFX
{ 
  void BBsUDemrjC()
  { 
      bool WCHNKKNcaF = false;
      bool tOXXxoqyra = false;
      bool hUdDTJfNQJ = false;
      bool puuUtZRIyN = false;
      bool ACclfyCMPP = false;
      bool JnnOhCXEsB = false;
      bool dALQOySCcX = false;
      bool WhzdZfqqWU = false;
      bool GSxBACHglr = false;
      bool BMOxizpLWg = false;
      bool fzirranJnC = false;
      bool KfhYtKDKQM = false;
      bool qkQkVKSCua = false;
      bool oeTonHjEIY = false;
      bool NxrigUepDX = false;
      bool weuKpthxVh = false;
      bool IlONMfLrkm = false;
      bool ayCqytsgEB = false;
      bool eczWdJjJzs = false;
      bool YlhZQbhdVB = false;
      string HjoeMnGfem;
      string CSQRrTxRyn;
      string juWMQmOtGs;
      string YbkZgWyZNj;
      string acbXfaIIVt;
      string yhXaALMcOY;
      string YMZlOahpjU;
      string UWENMGTyfo;
      string eGYLupDKYU;
      string JULnLODpJF;
      string sRXAYacJNs;
      string qOwZtRnNpX;
      string WXROLALPCy;
      string DdoawNiXlT;
      string NtwfduXlts;
      string ZozkhVAInY;
      string OMHPoMYVdg;
      string iPaVKcalkQ;
      string bZVIXOeErZ;
      string MZjNEAlfpQ;
      if(HjoeMnGfem == sRXAYacJNs){WCHNKKNcaF = true;}
      else if(sRXAYacJNs == HjoeMnGfem){fzirranJnC = true;}
      if(CSQRrTxRyn == qOwZtRnNpX){tOXXxoqyra = true;}
      else if(qOwZtRnNpX == CSQRrTxRyn){KfhYtKDKQM = true;}
      if(juWMQmOtGs == WXROLALPCy){hUdDTJfNQJ = true;}
      else if(WXROLALPCy == juWMQmOtGs){qkQkVKSCua = true;}
      if(YbkZgWyZNj == DdoawNiXlT){puuUtZRIyN = true;}
      else if(DdoawNiXlT == YbkZgWyZNj){oeTonHjEIY = true;}
      if(acbXfaIIVt == NtwfduXlts){ACclfyCMPP = true;}
      else if(NtwfduXlts == acbXfaIIVt){NxrigUepDX = true;}
      if(yhXaALMcOY == ZozkhVAInY){JnnOhCXEsB = true;}
      else if(ZozkhVAInY == yhXaALMcOY){weuKpthxVh = true;}
      if(YMZlOahpjU == OMHPoMYVdg){dALQOySCcX = true;}
      else if(OMHPoMYVdg == YMZlOahpjU){IlONMfLrkm = true;}
      if(UWENMGTyfo == iPaVKcalkQ){WhzdZfqqWU = true;}
      if(eGYLupDKYU == bZVIXOeErZ){GSxBACHglr = true;}
      if(JULnLODpJF == MZjNEAlfpQ){BMOxizpLWg = true;}
      while(iPaVKcalkQ == UWENMGTyfo){ayCqytsgEB = true;}
      while(bZVIXOeErZ == bZVIXOeErZ){eczWdJjJzs = true;}
      while(MZjNEAlfpQ == MZjNEAlfpQ){YlhZQbhdVB = true;}
      if(WCHNKKNcaF == true){WCHNKKNcaF = false;}
      if(tOXXxoqyra == true){tOXXxoqyra = false;}
      if(hUdDTJfNQJ == true){hUdDTJfNQJ = false;}
      if(puuUtZRIyN == true){puuUtZRIyN = false;}
      if(ACclfyCMPP == true){ACclfyCMPP = false;}
      if(JnnOhCXEsB == true){JnnOhCXEsB = false;}
      if(dALQOySCcX == true){dALQOySCcX = false;}
      if(WhzdZfqqWU == true){WhzdZfqqWU = false;}
      if(GSxBACHglr == true){GSxBACHglr = false;}
      if(BMOxizpLWg == true){BMOxizpLWg = false;}
      if(fzirranJnC == true){fzirranJnC = false;}
      if(KfhYtKDKQM == true){KfhYtKDKQM = false;}
      if(qkQkVKSCua == true){qkQkVKSCua = false;}
      if(oeTonHjEIY == true){oeTonHjEIY = false;}
      if(NxrigUepDX == true){NxrigUepDX = false;}
      if(weuKpthxVh == true){weuKpthxVh = false;}
      if(IlONMfLrkm == true){IlONMfLrkm = false;}
      if(ayCqytsgEB == true){ayCqytsgEB = false;}
      if(eczWdJjJzs == true){eczWdJjJzs = false;}
      if(YlhZQbhdVB == true){YlhZQbhdVB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XBPKDINWHD
{ 
  void ckFnRejhdX()
  { 
      bool WqTgWiOjSE = false;
      bool EAsKZyAXxg = false;
      bool IIfTwjfDCY = false;
      bool DacVYNwxYs = false;
      bool qCnGtrFaEK = false;
      bool iZWSROLAkl = false;
      bool DKgtAcWXkL = false;
      bool CCyDpFTYZD = false;
      bool eEzrodEJDK = false;
      bool BwMmpfVtFQ = false;
      bool VhprIgbScL = false;
      bool tmagHyKoFW = false;
      bool XMTZJFpLNJ = false;
      bool jZTIhxOGiI = false;
      bool ClgqPOUefq = false;
      bool UfoisINPiC = false;
      bool pPESbUTSzJ = false;
      bool jEFwUlecJu = false;
      bool jLfVnEkjOZ = false;
      bool jyXgRlgOPu = false;
      string SgkOVnuztc;
      string EcwGtcHqht;
      string zazgNwTAdQ;
      string LtpFqVwCHz;
      string FJKQlbiWPA;
      string XQErerhDBY;
      string UtUdRKmpPX;
      string gEjhopPhtl;
      string Nwjcruoxay;
      string mrBheKngyb;
      string nrHqTSfWDn;
      string czJPKYJqkW;
      string UoPRjnDBCd;
      string ChiSxVorJY;
      string OStlUnilWG;
      string AwubHzcoGe;
      string PeTZltQqRo;
      string jRhLICucww;
      string FQewcFlHLy;
      string rzkdJiyTzZ;
      if(SgkOVnuztc == nrHqTSfWDn){WqTgWiOjSE = true;}
      else if(nrHqTSfWDn == SgkOVnuztc){VhprIgbScL = true;}
      if(EcwGtcHqht == czJPKYJqkW){EAsKZyAXxg = true;}
      else if(czJPKYJqkW == EcwGtcHqht){tmagHyKoFW = true;}
      if(zazgNwTAdQ == UoPRjnDBCd){IIfTwjfDCY = true;}
      else if(UoPRjnDBCd == zazgNwTAdQ){XMTZJFpLNJ = true;}
      if(LtpFqVwCHz == ChiSxVorJY){DacVYNwxYs = true;}
      else if(ChiSxVorJY == LtpFqVwCHz){jZTIhxOGiI = true;}
      if(FJKQlbiWPA == OStlUnilWG){qCnGtrFaEK = true;}
      else if(OStlUnilWG == FJKQlbiWPA){ClgqPOUefq = true;}
      if(XQErerhDBY == AwubHzcoGe){iZWSROLAkl = true;}
      else if(AwubHzcoGe == XQErerhDBY){UfoisINPiC = true;}
      if(UtUdRKmpPX == PeTZltQqRo){DKgtAcWXkL = true;}
      else if(PeTZltQqRo == UtUdRKmpPX){pPESbUTSzJ = true;}
      if(gEjhopPhtl == jRhLICucww){CCyDpFTYZD = true;}
      if(Nwjcruoxay == FQewcFlHLy){eEzrodEJDK = true;}
      if(mrBheKngyb == rzkdJiyTzZ){BwMmpfVtFQ = true;}
      while(jRhLICucww == gEjhopPhtl){jEFwUlecJu = true;}
      while(FQewcFlHLy == FQewcFlHLy){jLfVnEkjOZ = true;}
      while(rzkdJiyTzZ == rzkdJiyTzZ){jyXgRlgOPu = true;}
      if(WqTgWiOjSE == true){WqTgWiOjSE = false;}
      if(EAsKZyAXxg == true){EAsKZyAXxg = false;}
      if(IIfTwjfDCY == true){IIfTwjfDCY = false;}
      if(DacVYNwxYs == true){DacVYNwxYs = false;}
      if(qCnGtrFaEK == true){qCnGtrFaEK = false;}
      if(iZWSROLAkl == true){iZWSROLAkl = false;}
      if(DKgtAcWXkL == true){DKgtAcWXkL = false;}
      if(CCyDpFTYZD == true){CCyDpFTYZD = false;}
      if(eEzrodEJDK == true){eEzrodEJDK = false;}
      if(BwMmpfVtFQ == true){BwMmpfVtFQ = false;}
      if(VhprIgbScL == true){VhprIgbScL = false;}
      if(tmagHyKoFW == true){tmagHyKoFW = false;}
      if(XMTZJFpLNJ == true){XMTZJFpLNJ = false;}
      if(jZTIhxOGiI == true){jZTIhxOGiI = false;}
      if(ClgqPOUefq == true){ClgqPOUefq = false;}
      if(UfoisINPiC == true){UfoisINPiC = false;}
      if(pPESbUTSzJ == true){pPESbUTSzJ = false;}
      if(jEFwUlecJu == true){jEFwUlecJu = false;}
      if(jLfVnEkjOZ == true){jLfVnEkjOZ = false;}
      if(jyXgRlgOPu == true){jyXgRlgOPu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XGDFBKMLDA
{ 
  void QjPpZnYcCm()
  { 
      bool LPoebcWqaB = false;
      bool FQXrbLZPcZ = false;
      bool jUMyiidsAA = false;
      bool wnpmXbuyRJ = false;
      bool WCodfhpqle = false;
      bool EzQEXqCpws = false;
      bool ydqaERZkUA = false;
      bool PayTDgeiSB = false;
      bool smGUuxWlOg = false;
      bool YECXKsLOYO = false;
      bool HEWlPdAwAp = false;
      bool MTXtALWVeH = false;
      bool tnVnaKYZIK = false;
      bool VPJDsnPUFR = false;
      bool wakXTFfHXy = false;
      bool VojRTThiLE = false;
      bool EampTwJUBM = false;
      bool wCPNKTDxTU = false;
      bool eQCKnffrjZ = false;
      bool FgIBMVmtEX = false;
      string dNEgKUMBVr;
      string xhoTtFmKmI;
      string JeKeWDJQJw;
      string xGperIQsmP;
      string NOmQnVNbuI;
      string BSCnnyCZKH;
      string LurZtprJal;
      string osWXtuqtpB;
      string ogVBteEBqt;
      string FpifDRVNVy;
      string cEAISHuess;
      string HIiISdZqeP;
      string kpSggyKqTc;
      string YcXqYjgMhm;
      string iZIylwHZNZ;
      string qeiGMmkSbT;
      string wEKPTdkqjh;
      string xNIqfLgUuj;
      string qkdtlstQek;
      string yNjOqeOsdH;
      if(dNEgKUMBVr == cEAISHuess){LPoebcWqaB = true;}
      else if(cEAISHuess == dNEgKUMBVr){HEWlPdAwAp = true;}
      if(xhoTtFmKmI == HIiISdZqeP){FQXrbLZPcZ = true;}
      else if(HIiISdZqeP == xhoTtFmKmI){MTXtALWVeH = true;}
      if(JeKeWDJQJw == kpSggyKqTc){jUMyiidsAA = true;}
      else if(kpSggyKqTc == JeKeWDJQJw){tnVnaKYZIK = true;}
      if(xGperIQsmP == YcXqYjgMhm){wnpmXbuyRJ = true;}
      else if(YcXqYjgMhm == xGperIQsmP){VPJDsnPUFR = true;}
      if(NOmQnVNbuI == iZIylwHZNZ){WCodfhpqle = true;}
      else if(iZIylwHZNZ == NOmQnVNbuI){wakXTFfHXy = true;}
      if(BSCnnyCZKH == qeiGMmkSbT){EzQEXqCpws = true;}
      else if(qeiGMmkSbT == BSCnnyCZKH){VojRTThiLE = true;}
      if(LurZtprJal == wEKPTdkqjh){ydqaERZkUA = true;}
      else if(wEKPTdkqjh == LurZtprJal){EampTwJUBM = true;}
      if(osWXtuqtpB == xNIqfLgUuj){PayTDgeiSB = true;}
      if(ogVBteEBqt == qkdtlstQek){smGUuxWlOg = true;}
      if(FpifDRVNVy == yNjOqeOsdH){YECXKsLOYO = true;}
      while(xNIqfLgUuj == osWXtuqtpB){wCPNKTDxTU = true;}
      while(qkdtlstQek == qkdtlstQek){eQCKnffrjZ = true;}
      while(yNjOqeOsdH == yNjOqeOsdH){FgIBMVmtEX = true;}
      if(LPoebcWqaB == true){LPoebcWqaB = false;}
      if(FQXrbLZPcZ == true){FQXrbLZPcZ = false;}
      if(jUMyiidsAA == true){jUMyiidsAA = false;}
      if(wnpmXbuyRJ == true){wnpmXbuyRJ = false;}
      if(WCodfhpqle == true){WCodfhpqle = false;}
      if(EzQEXqCpws == true){EzQEXqCpws = false;}
      if(ydqaERZkUA == true){ydqaERZkUA = false;}
      if(PayTDgeiSB == true){PayTDgeiSB = false;}
      if(smGUuxWlOg == true){smGUuxWlOg = false;}
      if(YECXKsLOYO == true){YECXKsLOYO = false;}
      if(HEWlPdAwAp == true){HEWlPdAwAp = false;}
      if(MTXtALWVeH == true){MTXtALWVeH = false;}
      if(tnVnaKYZIK == true){tnVnaKYZIK = false;}
      if(VPJDsnPUFR == true){VPJDsnPUFR = false;}
      if(wakXTFfHXy == true){wakXTFfHXy = false;}
      if(VojRTThiLE == true){VojRTThiLE = false;}
      if(EampTwJUBM == true){EampTwJUBM = false;}
      if(wCPNKTDxTU == true){wCPNKTDxTU = false;}
      if(eQCKnffrjZ == true){eQCKnffrjZ = false;}
      if(FgIBMVmtEX == true){FgIBMVmtEX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IRNPTCXWRC
{ 
  void CQLXURSMxe()
  { 
      bool XPAaVaGlzr = false;
      bool sBjYUgIICV = false;
      bool LaAwgGMNax = false;
      bool WEfSQlcmfy = false;
      bool onWmPLyPGj = false;
      bool WJosowPEtP = false;
      bool OsLBUoURHh = false;
      bool EUcEgXDNgU = false;
      bool IwGpaNOmdU = false;
      bool WXsQiubVRZ = false;
      bool pfIXfBgjLQ = false;
      bool rBWYGRlVaH = false;
      bool ZgnlKfbLUk = false;
      bool whwGebniKY = false;
      bool fdbMbVAUJR = false;
      bool IFtJAIrVMz = false;
      bool ZUPZUKEQse = false;
      bool dDLCauFbJo = false;
      bool eHCDcpmlFW = false;
      bool jRVKzKOBqR = false;
      string oANYNVAnFB;
      string LPrKzuMSTk;
      string QtxzRatYgN;
      string QjEZYVFRLQ;
      string FppqfPqwAL;
      string pLeIjuDNGm;
      string aaHqjaLRkc;
      string puGDeZDFSC;
      string iyYUWFFwpd;
      string SqKYodiyGE;
      string EYKWVuEacJ;
      string qxtEEcCmTd;
      string VObGKyjhOB;
      string qEzOyKmByb;
      string BeSgmVwGUL;
      string budbioxEMW;
      string KVLbRlyfFs;
      string oAnrcpuuTn;
      string CdNCYwZWeI;
      string MinaReSqOA;
      if(oANYNVAnFB == EYKWVuEacJ){XPAaVaGlzr = true;}
      else if(EYKWVuEacJ == oANYNVAnFB){pfIXfBgjLQ = true;}
      if(LPrKzuMSTk == qxtEEcCmTd){sBjYUgIICV = true;}
      else if(qxtEEcCmTd == LPrKzuMSTk){rBWYGRlVaH = true;}
      if(QtxzRatYgN == VObGKyjhOB){LaAwgGMNax = true;}
      else if(VObGKyjhOB == QtxzRatYgN){ZgnlKfbLUk = true;}
      if(QjEZYVFRLQ == qEzOyKmByb){WEfSQlcmfy = true;}
      else if(qEzOyKmByb == QjEZYVFRLQ){whwGebniKY = true;}
      if(FppqfPqwAL == BeSgmVwGUL){onWmPLyPGj = true;}
      else if(BeSgmVwGUL == FppqfPqwAL){fdbMbVAUJR = true;}
      if(pLeIjuDNGm == budbioxEMW){WJosowPEtP = true;}
      else if(budbioxEMW == pLeIjuDNGm){IFtJAIrVMz = true;}
      if(aaHqjaLRkc == KVLbRlyfFs){OsLBUoURHh = true;}
      else if(KVLbRlyfFs == aaHqjaLRkc){ZUPZUKEQse = true;}
      if(puGDeZDFSC == oAnrcpuuTn){EUcEgXDNgU = true;}
      if(iyYUWFFwpd == CdNCYwZWeI){IwGpaNOmdU = true;}
      if(SqKYodiyGE == MinaReSqOA){WXsQiubVRZ = true;}
      while(oAnrcpuuTn == puGDeZDFSC){dDLCauFbJo = true;}
      while(CdNCYwZWeI == CdNCYwZWeI){eHCDcpmlFW = true;}
      while(MinaReSqOA == MinaReSqOA){jRVKzKOBqR = true;}
      if(XPAaVaGlzr == true){XPAaVaGlzr = false;}
      if(sBjYUgIICV == true){sBjYUgIICV = false;}
      if(LaAwgGMNax == true){LaAwgGMNax = false;}
      if(WEfSQlcmfy == true){WEfSQlcmfy = false;}
      if(onWmPLyPGj == true){onWmPLyPGj = false;}
      if(WJosowPEtP == true){WJosowPEtP = false;}
      if(OsLBUoURHh == true){OsLBUoURHh = false;}
      if(EUcEgXDNgU == true){EUcEgXDNgU = false;}
      if(IwGpaNOmdU == true){IwGpaNOmdU = false;}
      if(WXsQiubVRZ == true){WXsQiubVRZ = false;}
      if(pfIXfBgjLQ == true){pfIXfBgjLQ = false;}
      if(rBWYGRlVaH == true){rBWYGRlVaH = false;}
      if(ZgnlKfbLUk == true){ZgnlKfbLUk = false;}
      if(whwGebniKY == true){whwGebniKY = false;}
      if(fdbMbVAUJR == true){fdbMbVAUJR = false;}
      if(IFtJAIrVMz == true){IFtJAIrVMz = false;}
      if(ZUPZUKEQse == true){ZUPZUKEQse = false;}
      if(dDLCauFbJo == true){dDLCauFbJo = false;}
      if(eHCDcpmlFW == true){eHCDcpmlFW = false;}
      if(jRVKzKOBqR == true){jRVKzKOBqR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class COALFGZUYG
{ 
  void LEeSsPkjtK()
  { 
      bool lekLlHsJeE = false;
      bool FubmSGPMjl = false;
      bool UxDBpzzink = false;
      bool WfZEPrCtKO = false;
      bool tTEMatlMhG = false;
      bool bwAWHnbiUm = false;
      bool IJUthZUXWa = false;
      bool EVBVqBspaw = false;
      bool NlBgIZeCxb = false;
      bool QTZXFkyKeB = false;
      bool YOoHCGteeG = false;
      bool ukHXYVInkH = false;
      bool tRauJkwdPG = false;
      bool CiKZWyxsdC = false;
      bool fzWpgeLByj = false;
      bool bJYXGGnsxR = false;
      bool KQPYDLZhAa = false;
      bool XOKiatujOe = false;
      bool YtefdsJlSP = false;
      bool KEwLrPjymU = false;
      string uiBRFzSApK;
      string zRcadXmmBJ;
      string RzQuwtXcPW;
      string lXinIMcaAO;
      string kroXKNhibI;
      string NFuIPwSGUK;
      string aojTXbinSQ;
      string tMllYYJrji;
      string LnBGIgbaXL;
      string tWFpmuHVzi;
      string esQLOASIip;
      string lZVlylndKq;
      string zIPGVXGwyc;
      string RnrBDSXorI;
      string NTqhZTATqB;
      string GdLIjWcJoq;
      string tVKGYxhUif;
      string OzkCcfQhgC;
      string XmFxVmcjRg;
      string oOzBNrIkIb;
      if(uiBRFzSApK == esQLOASIip){lekLlHsJeE = true;}
      else if(esQLOASIip == uiBRFzSApK){YOoHCGteeG = true;}
      if(zRcadXmmBJ == lZVlylndKq){FubmSGPMjl = true;}
      else if(lZVlylndKq == zRcadXmmBJ){ukHXYVInkH = true;}
      if(RzQuwtXcPW == zIPGVXGwyc){UxDBpzzink = true;}
      else if(zIPGVXGwyc == RzQuwtXcPW){tRauJkwdPG = true;}
      if(lXinIMcaAO == RnrBDSXorI){WfZEPrCtKO = true;}
      else if(RnrBDSXorI == lXinIMcaAO){CiKZWyxsdC = true;}
      if(kroXKNhibI == NTqhZTATqB){tTEMatlMhG = true;}
      else if(NTqhZTATqB == kroXKNhibI){fzWpgeLByj = true;}
      if(NFuIPwSGUK == GdLIjWcJoq){bwAWHnbiUm = true;}
      else if(GdLIjWcJoq == NFuIPwSGUK){bJYXGGnsxR = true;}
      if(aojTXbinSQ == tVKGYxhUif){IJUthZUXWa = true;}
      else if(tVKGYxhUif == aojTXbinSQ){KQPYDLZhAa = true;}
      if(tMllYYJrji == OzkCcfQhgC){EVBVqBspaw = true;}
      if(LnBGIgbaXL == XmFxVmcjRg){NlBgIZeCxb = true;}
      if(tWFpmuHVzi == oOzBNrIkIb){QTZXFkyKeB = true;}
      while(OzkCcfQhgC == tMllYYJrji){XOKiatujOe = true;}
      while(XmFxVmcjRg == XmFxVmcjRg){YtefdsJlSP = true;}
      while(oOzBNrIkIb == oOzBNrIkIb){KEwLrPjymU = true;}
      if(lekLlHsJeE == true){lekLlHsJeE = false;}
      if(FubmSGPMjl == true){FubmSGPMjl = false;}
      if(UxDBpzzink == true){UxDBpzzink = false;}
      if(WfZEPrCtKO == true){WfZEPrCtKO = false;}
      if(tTEMatlMhG == true){tTEMatlMhG = false;}
      if(bwAWHnbiUm == true){bwAWHnbiUm = false;}
      if(IJUthZUXWa == true){IJUthZUXWa = false;}
      if(EVBVqBspaw == true){EVBVqBspaw = false;}
      if(NlBgIZeCxb == true){NlBgIZeCxb = false;}
      if(QTZXFkyKeB == true){QTZXFkyKeB = false;}
      if(YOoHCGteeG == true){YOoHCGteeG = false;}
      if(ukHXYVInkH == true){ukHXYVInkH = false;}
      if(tRauJkwdPG == true){tRauJkwdPG = false;}
      if(CiKZWyxsdC == true){CiKZWyxsdC = false;}
      if(fzWpgeLByj == true){fzWpgeLByj = false;}
      if(bJYXGGnsxR == true){bJYXGGnsxR = false;}
      if(KQPYDLZhAa == true){KQPYDLZhAa = false;}
      if(XOKiatujOe == true){XOKiatujOe = false;}
      if(YtefdsJlSP == true){YtefdsJlSP = false;}
      if(KEwLrPjymU == true){KEwLrPjymU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OPZQHZVOHS
{ 
  void GKOQPWRiKr()
  { 
      bool hNdCoUrXfc = false;
      bool XmKUYtnOVA = false;
      bool gRKQdQSgNU = false;
      bool GlXkmeKBWb = false;
      bool axaYUuLYjm = false;
      bool qNtxQQDMYX = false;
      bool BKKKWlOZhs = false;
      bool ilqsZiplwi = false;
      bool FtxadrqZTV = false;
      bool bybzaQmQBi = false;
      bool fkqpDEVBXh = false;
      bool aRQpSHMifd = false;
      bool tnGLRkJrSI = false;
      bool wYjMCTDHWY = false;
      bool VpCluKhlfS = false;
      bool EDjXoreeXS = false;
      bool tdhOkCgDny = false;
      bool EEMGHEkTQH = false;
      bool CXLzErnMXJ = false;
      bool nXiEerHmAs = false;
      string uHBcDBYlcp;
      string KOfcRBawzw;
      string YlEQQLCULm;
      string hEsFAVjeKe;
      string jYTMEiWHPB;
      string JxjKTIDkLr;
      string yDapIGVZbu;
      string RwlULzRqLh;
      string nuFKdjTilr;
      string SySRffydEy;
      string NxeTjMLPyT;
      string pLYdDDyQLX;
      string lmnjcScTne;
      string AnmNTqQkZQ;
      string XDjRBGZnOb;
      string hhSfLaJtqR;
      string iraSTCXLKL;
      string mMptAiCViV;
      string roEMxSVGBs;
      string hVtIgecQyy;
      if(uHBcDBYlcp == NxeTjMLPyT){hNdCoUrXfc = true;}
      else if(NxeTjMLPyT == uHBcDBYlcp){fkqpDEVBXh = true;}
      if(KOfcRBawzw == pLYdDDyQLX){XmKUYtnOVA = true;}
      else if(pLYdDDyQLX == KOfcRBawzw){aRQpSHMifd = true;}
      if(YlEQQLCULm == lmnjcScTne){gRKQdQSgNU = true;}
      else if(lmnjcScTne == YlEQQLCULm){tnGLRkJrSI = true;}
      if(hEsFAVjeKe == AnmNTqQkZQ){GlXkmeKBWb = true;}
      else if(AnmNTqQkZQ == hEsFAVjeKe){wYjMCTDHWY = true;}
      if(jYTMEiWHPB == XDjRBGZnOb){axaYUuLYjm = true;}
      else if(XDjRBGZnOb == jYTMEiWHPB){VpCluKhlfS = true;}
      if(JxjKTIDkLr == hhSfLaJtqR){qNtxQQDMYX = true;}
      else if(hhSfLaJtqR == JxjKTIDkLr){EDjXoreeXS = true;}
      if(yDapIGVZbu == iraSTCXLKL){BKKKWlOZhs = true;}
      else if(iraSTCXLKL == yDapIGVZbu){tdhOkCgDny = true;}
      if(RwlULzRqLh == mMptAiCViV){ilqsZiplwi = true;}
      if(nuFKdjTilr == roEMxSVGBs){FtxadrqZTV = true;}
      if(SySRffydEy == hVtIgecQyy){bybzaQmQBi = true;}
      while(mMptAiCViV == RwlULzRqLh){EEMGHEkTQH = true;}
      while(roEMxSVGBs == roEMxSVGBs){CXLzErnMXJ = true;}
      while(hVtIgecQyy == hVtIgecQyy){nXiEerHmAs = true;}
      if(hNdCoUrXfc == true){hNdCoUrXfc = false;}
      if(XmKUYtnOVA == true){XmKUYtnOVA = false;}
      if(gRKQdQSgNU == true){gRKQdQSgNU = false;}
      if(GlXkmeKBWb == true){GlXkmeKBWb = false;}
      if(axaYUuLYjm == true){axaYUuLYjm = false;}
      if(qNtxQQDMYX == true){qNtxQQDMYX = false;}
      if(BKKKWlOZhs == true){BKKKWlOZhs = false;}
      if(ilqsZiplwi == true){ilqsZiplwi = false;}
      if(FtxadrqZTV == true){FtxadrqZTV = false;}
      if(bybzaQmQBi == true){bybzaQmQBi = false;}
      if(fkqpDEVBXh == true){fkqpDEVBXh = false;}
      if(aRQpSHMifd == true){aRQpSHMifd = false;}
      if(tnGLRkJrSI == true){tnGLRkJrSI = false;}
      if(wYjMCTDHWY == true){wYjMCTDHWY = false;}
      if(VpCluKhlfS == true){VpCluKhlfS = false;}
      if(EDjXoreeXS == true){EDjXoreeXS = false;}
      if(tdhOkCgDny == true){tdhOkCgDny = false;}
      if(EEMGHEkTQH == true){EEMGHEkTQH = false;}
      if(CXLzErnMXJ == true){CXLzErnMXJ = false;}
      if(nXiEerHmAs == true){nXiEerHmAs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JTOHOFUNZJ
{ 
  void fzybZDQYhA()
  { 
      bool YKkuhjwHMT = false;
      bool saxETqQcli = false;
      bool hagsOLVwNW = false;
      bool hdMSSFNhVY = false;
      bool SMfJZqnAoN = false;
      bool IocSGxcqgW = false;
      bool OAtokONelN = false;
      bool chHNPVuXTX = false;
      bool XUGzNsAtLU = false;
      bool cWByKSRpXK = false;
      bool cJOakZhPDk = false;
      bool CFWJzssubr = false;
      bool OTSQkFgIDx = false;
      bool DEAJtNFfNm = false;
      bool LkpaSXAqzQ = false;
      bool YWOfwJqxpe = false;
      bool sYLFgxENOk = false;
      bool nNgngccqyN = false;
      bool FoImXgoUNk = false;
      bool WIphtlYktU = false;
      string xTfktOTYbR;
      string ubcDCbshzF;
      string kRaDUuhJHg;
      string kfxyRFJfNy;
      string xRiDjWincp;
      string zSQWhercQz;
      string fJQugOeekx;
      string SMTBHShXSx;
      string LsgRhROZPm;
      string NfPORnBnWU;
      string rEDfXlzPOP;
      string wUJSmmczNO;
      string zEOyjmwFiT;
      string RtAyFHpBtu;
      string SzKAprVxbe;
      string KBZHUmoEuj;
      string ptguyCTLMf;
      string waFSuAsOHq;
      string QycDIPTrdS;
      string RkFJFYRPBn;
      if(xTfktOTYbR == rEDfXlzPOP){YKkuhjwHMT = true;}
      else if(rEDfXlzPOP == xTfktOTYbR){cJOakZhPDk = true;}
      if(ubcDCbshzF == wUJSmmczNO){saxETqQcli = true;}
      else if(wUJSmmczNO == ubcDCbshzF){CFWJzssubr = true;}
      if(kRaDUuhJHg == zEOyjmwFiT){hagsOLVwNW = true;}
      else if(zEOyjmwFiT == kRaDUuhJHg){OTSQkFgIDx = true;}
      if(kfxyRFJfNy == RtAyFHpBtu){hdMSSFNhVY = true;}
      else if(RtAyFHpBtu == kfxyRFJfNy){DEAJtNFfNm = true;}
      if(xRiDjWincp == SzKAprVxbe){SMfJZqnAoN = true;}
      else if(SzKAprVxbe == xRiDjWincp){LkpaSXAqzQ = true;}
      if(zSQWhercQz == KBZHUmoEuj){IocSGxcqgW = true;}
      else if(KBZHUmoEuj == zSQWhercQz){YWOfwJqxpe = true;}
      if(fJQugOeekx == ptguyCTLMf){OAtokONelN = true;}
      else if(ptguyCTLMf == fJQugOeekx){sYLFgxENOk = true;}
      if(SMTBHShXSx == waFSuAsOHq){chHNPVuXTX = true;}
      if(LsgRhROZPm == QycDIPTrdS){XUGzNsAtLU = true;}
      if(NfPORnBnWU == RkFJFYRPBn){cWByKSRpXK = true;}
      while(waFSuAsOHq == SMTBHShXSx){nNgngccqyN = true;}
      while(QycDIPTrdS == QycDIPTrdS){FoImXgoUNk = true;}
      while(RkFJFYRPBn == RkFJFYRPBn){WIphtlYktU = true;}
      if(YKkuhjwHMT == true){YKkuhjwHMT = false;}
      if(saxETqQcli == true){saxETqQcli = false;}
      if(hagsOLVwNW == true){hagsOLVwNW = false;}
      if(hdMSSFNhVY == true){hdMSSFNhVY = false;}
      if(SMfJZqnAoN == true){SMfJZqnAoN = false;}
      if(IocSGxcqgW == true){IocSGxcqgW = false;}
      if(OAtokONelN == true){OAtokONelN = false;}
      if(chHNPVuXTX == true){chHNPVuXTX = false;}
      if(XUGzNsAtLU == true){XUGzNsAtLU = false;}
      if(cWByKSRpXK == true){cWByKSRpXK = false;}
      if(cJOakZhPDk == true){cJOakZhPDk = false;}
      if(CFWJzssubr == true){CFWJzssubr = false;}
      if(OTSQkFgIDx == true){OTSQkFgIDx = false;}
      if(DEAJtNFfNm == true){DEAJtNFfNm = false;}
      if(LkpaSXAqzQ == true){LkpaSXAqzQ = false;}
      if(YWOfwJqxpe == true){YWOfwJqxpe = false;}
      if(sYLFgxENOk == true){sYLFgxENOk = false;}
      if(nNgngccqyN == true){nNgngccqyN = false;}
      if(FoImXgoUNk == true){FoImXgoUNk = false;}
      if(WIphtlYktU == true){WIphtlYktU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CDLKSMOKYE
{ 
  void gYehVZarAK()
  { 
      bool bElVNMpaQK = false;
      bool jSafIZDzzJ = false;
      bool sPmSLSMBTw = false;
      bool bLgyQKGjMb = false;
      bool ypCaSNiLBe = false;
      bool VyYsfMQTJu = false;
      bool zoGTiYlcOy = false;
      bool STlWKCMMAx = false;
      bool iBznacmmRD = false;
      bool smZRcJjirt = false;
      bool bGwDMCMBic = false;
      bool AESMMypRsF = false;
      bool kzKKEetUtA = false;
      bool SdUFVbEubY = false;
      bool QlDnDoTMEe = false;
      bool SRolJculyg = false;
      bool HqHhKWiNpj = false;
      bool stoTozuWHP = false;
      bool LgPOhAnhws = false;
      bool gSxuQYdUcf = false;
      string qqIwqkweQH;
      string MtCQwBwxWp;
      string dCDELqkflX;
      string szpXzofooc;
      string AooFwVTWkl;
      string djjiennEkz;
      string APsrNMDeRG;
      string UHIspnNyHp;
      string XOuztJOGsK;
      string BbEobkwxqj;
      string RnFeQVbqsq;
      string apxtblUsxE;
      string yxlGFsCSQF;
      string rQGXXiIQhX;
      string hXMBiLdJNp;
      string PCzmkUCyYX;
      string SIZnyKiZWr;
      string cDLYVZjjWs;
      string OsFZooQTlD;
      string gKqKEYyXCY;
      if(qqIwqkweQH == RnFeQVbqsq){bElVNMpaQK = true;}
      else if(RnFeQVbqsq == qqIwqkweQH){bGwDMCMBic = true;}
      if(MtCQwBwxWp == apxtblUsxE){jSafIZDzzJ = true;}
      else if(apxtblUsxE == MtCQwBwxWp){AESMMypRsF = true;}
      if(dCDELqkflX == yxlGFsCSQF){sPmSLSMBTw = true;}
      else if(yxlGFsCSQF == dCDELqkflX){kzKKEetUtA = true;}
      if(szpXzofooc == rQGXXiIQhX){bLgyQKGjMb = true;}
      else if(rQGXXiIQhX == szpXzofooc){SdUFVbEubY = true;}
      if(AooFwVTWkl == hXMBiLdJNp){ypCaSNiLBe = true;}
      else if(hXMBiLdJNp == AooFwVTWkl){QlDnDoTMEe = true;}
      if(djjiennEkz == PCzmkUCyYX){VyYsfMQTJu = true;}
      else if(PCzmkUCyYX == djjiennEkz){SRolJculyg = true;}
      if(APsrNMDeRG == SIZnyKiZWr){zoGTiYlcOy = true;}
      else if(SIZnyKiZWr == APsrNMDeRG){HqHhKWiNpj = true;}
      if(UHIspnNyHp == cDLYVZjjWs){STlWKCMMAx = true;}
      if(XOuztJOGsK == OsFZooQTlD){iBznacmmRD = true;}
      if(BbEobkwxqj == gKqKEYyXCY){smZRcJjirt = true;}
      while(cDLYVZjjWs == UHIspnNyHp){stoTozuWHP = true;}
      while(OsFZooQTlD == OsFZooQTlD){LgPOhAnhws = true;}
      while(gKqKEYyXCY == gKqKEYyXCY){gSxuQYdUcf = true;}
      if(bElVNMpaQK == true){bElVNMpaQK = false;}
      if(jSafIZDzzJ == true){jSafIZDzzJ = false;}
      if(sPmSLSMBTw == true){sPmSLSMBTw = false;}
      if(bLgyQKGjMb == true){bLgyQKGjMb = false;}
      if(ypCaSNiLBe == true){ypCaSNiLBe = false;}
      if(VyYsfMQTJu == true){VyYsfMQTJu = false;}
      if(zoGTiYlcOy == true){zoGTiYlcOy = false;}
      if(STlWKCMMAx == true){STlWKCMMAx = false;}
      if(iBznacmmRD == true){iBznacmmRD = false;}
      if(smZRcJjirt == true){smZRcJjirt = false;}
      if(bGwDMCMBic == true){bGwDMCMBic = false;}
      if(AESMMypRsF == true){AESMMypRsF = false;}
      if(kzKKEetUtA == true){kzKKEetUtA = false;}
      if(SdUFVbEubY == true){SdUFVbEubY = false;}
      if(QlDnDoTMEe == true){QlDnDoTMEe = false;}
      if(SRolJculyg == true){SRolJculyg = false;}
      if(HqHhKWiNpj == true){HqHhKWiNpj = false;}
      if(stoTozuWHP == true){stoTozuWHP = false;}
      if(LgPOhAnhws == true){LgPOhAnhws = false;}
      if(gSxuQYdUcf == true){gSxuQYdUcf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUKTCXHFJL
{ 
  void QTtMhbdyom()
  { 
      bool GHMDktbHEG = false;
      bool opTgzxAOgf = false;
      bool PaaCguJsim = false;
      bool PVPfyblyBY = false;
      bool tZbMyiqSMl = false;
      bool VUxTjegKVp = false;
      bool kiYQpTZnhX = false;
      bool KBMHloyODy = false;
      bool DpfwRuYwuT = false;
      bool tbcLnLALVe = false;
      bool JDkobTHpht = false;
      bool fRGXltDczu = false;
      bool udrOchYBSa = false;
      bool omsYnAFpTx = false;
      bool niNBmcVEYt = false;
      bool IWMajfKVMt = false;
      bool uGWHFsXhik = false;
      bool nMJBGMPqbz = false;
      bool LTbYSRaSoI = false;
      bool pidZChLGut = false;
      string YEtjIAUQle;
      string ksmWBSazyN;
      string qkIILOwhxH;
      string KjGHpOIxpL;
      string mCDQrJHIqf;
      string bWSAwmwkXt;
      string EmSdUBmffl;
      string JcIlZnhrQB;
      string HmqRemQGLC;
      string SWZwHAiYwq;
      string WacFVzOfZH;
      string FEUVlQuByh;
      string jfUcTlDLdY;
      string EIuZefKluf;
      string XkfDxOCDJq;
      string EhaOGpGzki;
      string wCBBDxItqG;
      string FJFSJzAQfE;
      string jzCmTWhgSn;
      string YKAMjVieAz;
      if(YEtjIAUQle == WacFVzOfZH){GHMDktbHEG = true;}
      else if(WacFVzOfZH == YEtjIAUQle){JDkobTHpht = true;}
      if(ksmWBSazyN == FEUVlQuByh){opTgzxAOgf = true;}
      else if(FEUVlQuByh == ksmWBSazyN){fRGXltDczu = true;}
      if(qkIILOwhxH == jfUcTlDLdY){PaaCguJsim = true;}
      else if(jfUcTlDLdY == qkIILOwhxH){udrOchYBSa = true;}
      if(KjGHpOIxpL == EIuZefKluf){PVPfyblyBY = true;}
      else if(EIuZefKluf == KjGHpOIxpL){omsYnAFpTx = true;}
      if(mCDQrJHIqf == XkfDxOCDJq){tZbMyiqSMl = true;}
      else if(XkfDxOCDJq == mCDQrJHIqf){niNBmcVEYt = true;}
      if(bWSAwmwkXt == EhaOGpGzki){VUxTjegKVp = true;}
      else if(EhaOGpGzki == bWSAwmwkXt){IWMajfKVMt = true;}
      if(EmSdUBmffl == wCBBDxItqG){kiYQpTZnhX = true;}
      else if(wCBBDxItqG == EmSdUBmffl){uGWHFsXhik = true;}
      if(JcIlZnhrQB == FJFSJzAQfE){KBMHloyODy = true;}
      if(HmqRemQGLC == jzCmTWhgSn){DpfwRuYwuT = true;}
      if(SWZwHAiYwq == YKAMjVieAz){tbcLnLALVe = true;}
      while(FJFSJzAQfE == JcIlZnhrQB){nMJBGMPqbz = true;}
      while(jzCmTWhgSn == jzCmTWhgSn){LTbYSRaSoI = true;}
      while(YKAMjVieAz == YKAMjVieAz){pidZChLGut = true;}
      if(GHMDktbHEG == true){GHMDktbHEG = false;}
      if(opTgzxAOgf == true){opTgzxAOgf = false;}
      if(PaaCguJsim == true){PaaCguJsim = false;}
      if(PVPfyblyBY == true){PVPfyblyBY = false;}
      if(tZbMyiqSMl == true){tZbMyiqSMl = false;}
      if(VUxTjegKVp == true){VUxTjegKVp = false;}
      if(kiYQpTZnhX == true){kiYQpTZnhX = false;}
      if(KBMHloyODy == true){KBMHloyODy = false;}
      if(DpfwRuYwuT == true){DpfwRuYwuT = false;}
      if(tbcLnLALVe == true){tbcLnLALVe = false;}
      if(JDkobTHpht == true){JDkobTHpht = false;}
      if(fRGXltDczu == true){fRGXltDczu = false;}
      if(udrOchYBSa == true){udrOchYBSa = false;}
      if(omsYnAFpTx == true){omsYnAFpTx = false;}
      if(niNBmcVEYt == true){niNBmcVEYt = false;}
      if(IWMajfKVMt == true){IWMajfKVMt = false;}
      if(uGWHFsXhik == true){uGWHFsXhik = false;}
      if(nMJBGMPqbz == true){nMJBGMPqbz = false;}
      if(LTbYSRaSoI == true){LTbYSRaSoI = false;}
      if(pidZChLGut == true){pidZChLGut = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PUHZCTUMHV
{ 
  void xOLzsEmBLQ()
  { 
      bool cfVfodAcHd = false;
      bool iTNLjTQKEP = false;
      bool TkKnQLEdUh = false;
      bool luJPGzTZbj = false;
      bool dDJHJfTsll = false;
      bool ZcoeEqVgOc = false;
      bool ZWIYqnJyEk = false;
      bool ApiTlQbCdj = false;
      bool qLqhHJFdKP = false;
      bool dlKzKHtjPV = false;
      bool WUnBljsVsn = false;
      bool PSCdkNeZRh = false;
      bool hennGNfjIe = false;
      bool VqmHNVWpwX = false;
      bool PjkVALifNw = false;
      bool bTSgnqgAtX = false;
      bool EJNOSXeuQO = false;
      bool qodsRytRnu = false;
      bool ezVLCBXFTV = false;
      bool oWuYTGVVDb = false;
      string QUaxCLcClZ;
      string HiSFlBwMuK;
      string JuFHETkLDX;
      string BbzJgsgxVl;
      string MnLpYKbmCr;
      string CPkRtVOTsh;
      string aRzNXfjJXs;
      string UypJxUiPhs;
      string ryIKUlpgOL;
      string eMEmKuoxRs;
      string aSOJXEYaUZ;
      string lzkApcInrl;
      string oCtMOHtDzB;
      string elxoRYizmQ;
      string MPMoYebExh;
      string mBFfDYYBuP;
      string JVbStACwhQ;
      string sIAbYZoFni;
      string fpFQOdgQks;
      string AhEWGqmtuY;
      if(QUaxCLcClZ == aSOJXEYaUZ){cfVfodAcHd = true;}
      else if(aSOJXEYaUZ == QUaxCLcClZ){WUnBljsVsn = true;}
      if(HiSFlBwMuK == lzkApcInrl){iTNLjTQKEP = true;}
      else if(lzkApcInrl == HiSFlBwMuK){PSCdkNeZRh = true;}
      if(JuFHETkLDX == oCtMOHtDzB){TkKnQLEdUh = true;}
      else if(oCtMOHtDzB == JuFHETkLDX){hennGNfjIe = true;}
      if(BbzJgsgxVl == elxoRYizmQ){luJPGzTZbj = true;}
      else if(elxoRYizmQ == BbzJgsgxVl){VqmHNVWpwX = true;}
      if(MnLpYKbmCr == MPMoYebExh){dDJHJfTsll = true;}
      else if(MPMoYebExh == MnLpYKbmCr){PjkVALifNw = true;}
      if(CPkRtVOTsh == mBFfDYYBuP){ZcoeEqVgOc = true;}
      else if(mBFfDYYBuP == CPkRtVOTsh){bTSgnqgAtX = true;}
      if(aRzNXfjJXs == JVbStACwhQ){ZWIYqnJyEk = true;}
      else if(JVbStACwhQ == aRzNXfjJXs){EJNOSXeuQO = true;}
      if(UypJxUiPhs == sIAbYZoFni){ApiTlQbCdj = true;}
      if(ryIKUlpgOL == fpFQOdgQks){qLqhHJFdKP = true;}
      if(eMEmKuoxRs == AhEWGqmtuY){dlKzKHtjPV = true;}
      while(sIAbYZoFni == UypJxUiPhs){qodsRytRnu = true;}
      while(fpFQOdgQks == fpFQOdgQks){ezVLCBXFTV = true;}
      while(AhEWGqmtuY == AhEWGqmtuY){oWuYTGVVDb = true;}
      if(cfVfodAcHd == true){cfVfodAcHd = false;}
      if(iTNLjTQKEP == true){iTNLjTQKEP = false;}
      if(TkKnQLEdUh == true){TkKnQLEdUh = false;}
      if(luJPGzTZbj == true){luJPGzTZbj = false;}
      if(dDJHJfTsll == true){dDJHJfTsll = false;}
      if(ZcoeEqVgOc == true){ZcoeEqVgOc = false;}
      if(ZWIYqnJyEk == true){ZWIYqnJyEk = false;}
      if(ApiTlQbCdj == true){ApiTlQbCdj = false;}
      if(qLqhHJFdKP == true){qLqhHJFdKP = false;}
      if(dlKzKHtjPV == true){dlKzKHtjPV = false;}
      if(WUnBljsVsn == true){WUnBljsVsn = false;}
      if(PSCdkNeZRh == true){PSCdkNeZRh = false;}
      if(hennGNfjIe == true){hennGNfjIe = false;}
      if(VqmHNVWpwX == true){VqmHNVWpwX = false;}
      if(PjkVALifNw == true){PjkVALifNw = false;}
      if(bTSgnqgAtX == true){bTSgnqgAtX = false;}
      if(EJNOSXeuQO == true){EJNOSXeuQO = false;}
      if(qodsRytRnu == true){qodsRytRnu = false;}
      if(ezVLCBXFTV == true){ezVLCBXFTV = false;}
      if(oWuYTGVVDb == true){oWuYTGVVDb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CFERTLQENO
{ 
  void jbeqSzELQr()
  { 
      bool tUpMDwJHrN = false;
      bool JCZKHbsOxW = false;
      bool xIkPnBaGFw = false;
      bool ONqVFfrUEr = false;
      bool hGUHYEGglF = false;
      bool WjnaFkiaXB = false;
      bool VCBwywKEEb = false;
      bool jYKFnqndqi = false;
      bool utTAZeZQQU = false;
      bool wRwCWeEYIc = false;
      bool sCbKVxYhlO = false;
      bool xFjnGahBVT = false;
      bool VtnjeRcIiI = false;
      bool lOUNosRJdb = false;
      bool FreBWqhHwu = false;
      bool wDDoHzNrfD = false;
      bool UQzcbhkVyM = false;
      bool IYWsNdPlMn = false;
      bool jULmLiLeGp = false;
      bool eZdaHosBZn = false;
      string ZQKOWHgYfh;
      string cgBFzzIyeV;
      string aWxwwbZgfV;
      string VDsRkZrAAi;
      string iIlUlVeHCr;
      string qOOdkDSNSt;
      string gzrKLZmiUY;
      string GHxwmSjcJa;
      string xSendHoOfg;
      string HehGBiPbJM;
      string hwlckjQRpS;
      string TpDrxOUEgD;
      string kXDmRbYptD;
      string DITxrAfCDs;
      string pWYNNQapJl;
      string OKuFbJrzKI;
      string LaXmPKWGzw;
      string iRBmMOzpYA;
      string AigIorNNUi;
      string HgqthPzkyD;
      if(ZQKOWHgYfh == hwlckjQRpS){tUpMDwJHrN = true;}
      else if(hwlckjQRpS == ZQKOWHgYfh){sCbKVxYhlO = true;}
      if(cgBFzzIyeV == TpDrxOUEgD){JCZKHbsOxW = true;}
      else if(TpDrxOUEgD == cgBFzzIyeV){xFjnGahBVT = true;}
      if(aWxwwbZgfV == kXDmRbYptD){xIkPnBaGFw = true;}
      else if(kXDmRbYptD == aWxwwbZgfV){VtnjeRcIiI = true;}
      if(VDsRkZrAAi == DITxrAfCDs){ONqVFfrUEr = true;}
      else if(DITxrAfCDs == VDsRkZrAAi){lOUNosRJdb = true;}
      if(iIlUlVeHCr == pWYNNQapJl){hGUHYEGglF = true;}
      else if(pWYNNQapJl == iIlUlVeHCr){FreBWqhHwu = true;}
      if(qOOdkDSNSt == OKuFbJrzKI){WjnaFkiaXB = true;}
      else if(OKuFbJrzKI == qOOdkDSNSt){wDDoHzNrfD = true;}
      if(gzrKLZmiUY == LaXmPKWGzw){VCBwywKEEb = true;}
      else if(LaXmPKWGzw == gzrKLZmiUY){UQzcbhkVyM = true;}
      if(GHxwmSjcJa == iRBmMOzpYA){jYKFnqndqi = true;}
      if(xSendHoOfg == AigIorNNUi){utTAZeZQQU = true;}
      if(HehGBiPbJM == HgqthPzkyD){wRwCWeEYIc = true;}
      while(iRBmMOzpYA == GHxwmSjcJa){IYWsNdPlMn = true;}
      while(AigIorNNUi == AigIorNNUi){jULmLiLeGp = true;}
      while(HgqthPzkyD == HgqthPzkyD){eZdaHosBZn = true;}
      if(tUpMDwJHrN == true){tUpMDwJHrN = false;}
      if(JCZKHbsOxW == true){JCZKHbsOxW = false;}
      if(xIkPnBaGFw == true){xIkPnBaGFw = false;}
      if(ONqVFfrUEr == true){ONqVFfrUEr = false;}
      if(hGUHYEGglF == true){hGUHYEGglF = false;}
      if(WjnaFkiaXB == true){WjnaFkiaXB = false;}
      if(VCBwywKEEb == true){VCBwywKEEb = false;}
      if(jYKFnqndqi == true){jYKFnqndqi = false;}
      if(utTAZeZQQU == true){utTAZeZQQU = false;}
      if(wRwCWeEYIc == true){wRwCWeEYIc = false;}
      if(sCbKVxYhlO == true){sCbKVxYhlO = false;}
      if(xFjnGahBVT == true){xFjnGahBVT = false;}
      if(VtnjeRcIiI == true){VtnjeRcIiI = false;}
      if(lOUNosRJdb == true){lOUNosRJdb = false;}
      if(FreBWqhHwu == true){FreBWqhHwu = false;}
      if(wDDoHzNrfD == true){wDDoHzNrfD = false;}
      if(UQzcbhkVyM == true){UQzcbhkVyM = false;}
      if(IYWsNdPlMn == true){IYWsNdPlMn = false;}
      if(jULmLiLeGp == true){jULmLiLeGp = false;}
      if(eZdaHosBZn == true){eZdaHosBZn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LROMVBNJMP
{ 
  void weQmkXtHxx()
  { 
      bool JgZPwyhrnt = false;
      bool gGFEDDDGba = false;
      bool PyKUtXVnWa = false;
      bool BZzpqRUEot = false;
      bool SSGAkAUkWH = false;
      bool uRyXDLWEVX = false;
      bool csUMsHGPNk = false;
      bool iyRhHxqJjs = false;
      bool DjROfibble = false;
      bool uQiQRZxtHd = false;
      bool tFXkYwzPPF = false;
      bool UMUbUsbFfJ = false;
      bool eecipRPAQh = false;
      bool zwBGzxLfpj = false;
      bool iMLfKhwGwX = false;
      bool xqOyyPbouH = false;
      bool gzzhFXLNcW = false;
      bool guPwZSSwYH = false;
      bool VJErjIhDHj = false;
      bool VWkhCjMdZl = false;
      string RQNyrmpGya;
      string OnpuctgtxK;
      string mszSdqpZxk;
      string BgUQgUBVeg;
      string lyihryCgRf;
      string SXpyPXRtTB;
      string xQIMYhSZNH;
      string rKOQYnJQZf;
      string nIHQSdpVBJ;
      string DGBdiUoVIK;
      string ecSKnHIZZa;
      string OAUnMnJrtu;
      string qwXEDkIkgE;
      string ymHOALoxcK;
      string VQwZtClNQu;
      string KxbNThEOGC;
      string zWrVbarFmB;
      string yMOiZZAxJB;
      string yuTksBLtuS;
      string HapZLyYZyT;
      if(RQNyrmpGya == ecSKnHIZZa){JgZPwyhrnt = true;}
      else if(ecSKnHIZZa == RQNyrmpGya){tFXkYwzPPF = true;}
      if(OnpuctgtxK == OAUnMnJrtu){gGFEDDDGba = true;}
      else if(OAUnMnJrtu == OnpuctgtxK){UMUbUsbFfJ = true;}
      if(mszSdqpZxk == qwXEDkIkgE){PyKUtXVnWa = true;}
      else if(qwXEDkIkgE == mszSdqpZxk){eecipRPAQh = true;}
      if(BgUQgUBVeg == ymHOALoxcK){BZzpqRUEot = true;}
      else if(ymHOALoxcK == BgUQgUBVeg){zwBGzxLfpj = true;}
      if(lyihryCgRf == VQwZtClNQu){SSGAkAUkWH = true;}
      else if(VQwZtClNQu == lyihryCgRf){iMLfKhwGwX = true;}
      if(SXpyPXRtTB == KxbNThEOGC){uRyXDLWEVX = true;}
      else if(KxbNThEOGC == SXpyPXRtTB){xqOyyPbouH = true;}
      if(xQIMYhSZNH == zWrVbarFmB){csUMsHGPNk = true;}
      else if(zWrVbarFmB == xQIMYhSZNH){gzzhFXLNcW = true;}
      if(rKOQYnJQZf == yMOiZZAxJB){iyRhHxqJjs = true;}
      if(nIHQSdpVBJ == yuTksBLtuS){DjROfibble = true;}
      if(DGBdiUoVIK == HapZLyYZyT){uQiQRZxtHd = true;}
      while(yMOiZZAxJB == rKOQYnJQZf){guPwZSSwYH = true;}
      while(yuTksBLtuS == yuTksBLtuS){VJErjIhDHj = true;}
      while(HapZLyYZyT == HapZLyYZyT){VWkhCjMdZl = true;}
      if(JgZPwyhrnt == true){JgZPwyhrnt = false;}
      if(gGFEDDDGba == true){gGFEDDDGba = false;}
      if(PyKUtXVnWa == true){PyKUtXVnWa = false;}
      if(BZzpqRUEot == true){BZzpqRUEot = false;}
      if(SSGAkAUkWH == true){SSGAkAUkWH = false;}
      if(uRyXDLWEVX == true){uRyXDLWEVX = false;}
      if(csUMsHGPNk == true){csUMsHGPNk = false;}
      if(iyRhHxqJjs == true){iyRhHxqJjs = false;}
      if(DjROfibble == true){DjROfibble = false;}
      if(uQiQRZxtHd == true){uQiQRZxtHd = false;}
      if(tFXkYwzPPF == true){tFXkYwzPPF = false;}
      if(UMUbUsbFfJ == true){UMUbUsbFfJ = false;}
      if(eecipRPAQh == true){eecipRPAQh = false;}
      if(zwBGzxLfpj == true){zwBGzxLfpj = false;}
      if(iMLfKhwGwX == true){iMLfKhwGwX = false;}
      if(xqOyyPbouH == true){xqOyyPbouH = false;}
      if(gzzhFXLNcW == true){gzzhFXLNcW = false;}
      if(guPwZSSwYH == true){guPwZSSwYH = false;}
      if(VJErjIhDHj == true){VJErjIhDHj = false;}
      if(VWkhCjMdZl == true){VWkhCjMdZl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZREFCQOJUD
{ 
  void zSndGHGCSc()
  { 
      bool WyECcUEKxD = false;
      bool izwDPdKinh = false;
      bool YQjextbfoK = false;
      bool JqytNwURWe = false;
      bool PHimlJLEGY = false;
      bool TbirWFOYEh = false;
      bool rXUmsrABoT = false;
      bool IsLIRQhwsn = false;
      bool hXZQphHGWI = false;
      bool huMnmqlust = false;
      bool IKOmPZPaZG = false;
      bool WSfQAUyEwL = false;
      bool jtdflMgXUZ = false;
      bool emCyeXImAQ = false;
      bool SffQlOPunR = false;
      bool sgyhKNfhAD = false;
      bool sqFzaiPglb = false;
      bool MLEfsDONtW = false;
      bool wkjDgxoTnQ = false;
      bool qZlxWaZfoC = false;
      string eWhCjHzeLL;
      string mZLAxgmSnE;
      string LCCwsoAaea;
      string yVsDZGyiri;
      string LriyzDhpjP;
      string mhRmxcUkJu;
      string GXAkNQfHZq;
      string hEZFsTSDwp;
      string HKpPnQEFGx;
      string kNYxbmryji;
      string WZPsghHLtd;
      string KQnTnwgkwx;
      string LZBcFUecdF;
      string aTSNSgtwhF;
      string IrLclUYFIe;
      string FGBlWxXlnL;
      string DdhnCpxZAG;
      string CjCqoTOYpk;
      string uZTzATRfpU;
      string IHIWCdKWZw;
      if(eWhCjHzeLL == WZPsghHLtd){WyECcUEKxD = true;}
      else if(WZPsghHLtd == eWhCjHzeLL){IKOmPZPaZG = true;}
      if(mZLAxgmSnE == KQnTnwgkwx){izwDPdKinh = true;}
      else if(KQnTnwgkwx == mZLAxgmSnE){WSfQAUyEwL = true;}
      if(LCCwsoAaea == LZBcFUecdF){YQjextbfoK = true;}
      else if(LZBcFUecdF == LCCwsoAaea){jtdflMgXUZ = true;}
      if(yVsDZGyiri == aTSNSgtwhF){JqytNwURWe = true;}
      else if(aTSNSgtwhF == yVsDZGyiri){emCyeXImAQ = true;}
      if(LriyzDhpjP == IrLclUYFIe){PHimlJLEGY = true;}
      else if(IrLclUYFIe == LriyzDhpjP){SffQlOPunR = true;}
      if(mhRmxcUkJu == FGBlWxXlnL){TbirWFOYEh = true;}
      else if(FGBlWxXlnL == mhRmxcUkJu){sgyhKNfhAD = true;}
      if(GXAkNQfHZq == DdhnCpxZAG){rXUmsrABoT = true;}
      else if(DdhnCpxZAG == GXAkNQfHZq){sqFzaiPglb = true;}
      if(hEZFsTSDwp == CjCqoTOYpk){IsLIRQhwsn = true;}
      if(HKpPnQEFGx == uZTzATRfpU){hXZQphHGWI = true;}
      if(kNYxbmryji == IHIWCdKWZw){huMnmqlust = true;}
      while(CjCqoTOYpk == hEZFsTSDwp){MLEfsDONtW = true;}
      while(uZTzATRfpU == uZTzATRfpU){wkjDgxoTnQ = true;}
      while(IHIWCdKWZw == IHIWCdKWZw){qZlxWaZfoC = true;}
      if(WyECcUEKxD == true){WyECcUEKxD = false;}
      if(izwDPdKinh == true){izwDPdKinh = false;}
      if(YQjextbfoK == true){YQjextbfoK = false;}
      if(JqytNwURWe == true){JqytNwURWe = false;}
      if(PHimlJLEGY == true){PHimlJLEGY = false;}
      if(TbirWFOYEh == true){TbirWFOYEh = false;}
      if(rXUmsrABoT == true){rXUmsrABoT = false;}
      if(IsLIRQhwsn == true){IsLIRQhwsn = false;}
      if(hXZQphHGWI == true){hXZQphHGWI = false;}
      if(huMnmqlust == true){huMnmqlust = false;}
      if(IKOmPZPaZG == true){IKOmPZPaZG = false;}
      if(WSfQAUyEwL == true){WSfQAUyEwL = false;}
      if(jtdflMgXUZ == true){jtdflMgXUZ = false;}
      if(emCyeXImAQ == true){emCyeXImAQ = false;}
      if(SffQlOPunR == true){SffQlOPunR = false;}
      if(sgyhKNfhAD == true){sgyhKNfhAD = false;}
      if(sqFzaiPglb == true){sqFzaiPglb = false;}
      if(MLEfsDONtW == true){MLEfsDONtW = false;}
      if(wkjDgxoTnQ == true){wkjDgxoTnQ = false;}
      if(qZlxWaZfoC == true){qZlxWaZfoC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MCEFRQSCLW
{ 
  void PbdcMoPPWQ()
  { 
      bool NAtaJaWzbH = false;
      bool ThHSbsSycR = false;
      bool UqrReiFoQH = false;
      bool nbnJMXecNk = false;
      bool VsCsiDSDDr = false;
      bool mRJqaWHcwa = false;
      bool UhhTSqsxFE = false;
      bool Opjqubozia = false;
      bool PCkXTWSwip = false;
      bool PBgmQmKhZq = false;
      bool KUyzdwgSuy = false;
      bool gItUKSwJAw = false;
      bool YxOOoMJxaH = false;
      bool QHYqQtEltW = false;
      bool ozAjJHHLbx = false;
      bool qAhdSMGiJQ = false;
      bool mjrmgZiCDP = false;
      bool NKPcGYwdFg = false;
      bool ExUcQQZtYE = false;
      bool nUbcjEHNDi = false;
      string bUdRXmWcpg;
      string FNSBEkpmmL;
      string ZVbHDgYKcZ;
      string pQroVSVhQf;
      string EtWZqtWHpf;
      string PqTLaGrVNq;
      string OLzQqnVcek;
      string PIWHHfzCPI;
      string JQUxKyxfNP;
      string ZzTZQstGhD;
      string XsbFQGULEu;
      string GpGEgxpCFr;
      string ppPOLQnwpO;
      string ksTMjPnPfD;
      string dkbSJjsOrS;
      string CrApMhdNsz;
      string SXVoJNVsTQ;
      string JaVBNEOwFa;
      string XYEWMrrdAC;
      string kaVfkGPlIu;
      if(bUdRXmWcpg == XsbFQGULEu){NAtaJaWzbH = true;}
      else if(XsbFQGULEu == bUdRXmWcpg){KUyzdwgSuy = true;}
      if(FNSBEkpmmL == GpGEgxpCFr){ThHSbsSycR = true;}
      else if(GpGEgxpCFr == FNSBEkpmmL){gItUKSwJAw = true;}
      if(ZVbHDgYKcZ == ppPOLQnwpO){UqrReiFoQH = true;}
      else if(ppPOLQnwpO == ZVbHDgYKcZ){YxOOoMJxaH = true;}
      if(pQroVSVhQf == ksTMjPnPfD){nbnJMXecNk = true;}
      else if(ksTMjPnPfD == pQroVSVhQf){QHYqQtEltW = true;}
      if(EtWZqtWHpf == dkbSJjsOrS){VsCsiDSDDr = true;}
      else if(dkbSJjsOrS == EtWZqtWHpf){ozAjJHHLbx = true;}
      if(PqTLaGrVNq == CrApMhdNsz){mRJqaWHcwa = true;}
      else if(CrApMhdNsz == PqTLaGrVNq){qAhdSMGiJQ = true;}
      if(OLzQqnVcek == SXVoJNVsTQ){UhhTSqsxFE = true;}
      else if(SXVoJNVsTQ == OLzQqnVcek){mjrmgZiCDP = true;}
      if(PIWHHfzCPI == JaVBNEOwFa){Opjqubozia = true;}
      if(JQUxKyxfNP == XYEWMrrdAC){PCkXTWSwip = true;}
      if(ZzTZQstGhD == kaVfkGPlIu){PBgmQmKhZq = true;}
      while(JaVBNEOwFa == PIWHHfzCPI){NKPcGYwdFg = true;}
      while(XYEWMrrdAC == XYEWMrrdAC){ExUcQQZtYE = true;}
      while(kaVfkGPlIu == kaVfkGPlIu){nUbcjEHNDi = true;}
      if(NAtaJaWzbH == true){NAtaJaWzbH = false;}
      if(ThHSbsSycR == true){ThHSbsSycR = false;}
      if(UqrReiFoQH == true){UqrReiFoQH = false;}
      if(nbnJMXecNk == true){nbnJMXecNk = false;}
      if(VsCsiDSDDr == true){VsCsiDSDDr = false;}
      if(mRJqaWHcwa == true){mRJqaWHcwa = false;}
      if(UhhTSqsxFE == true){UhhTSqsxFE = false;}
      if(Opjqubozia == true){Opjqubozia = false;}
      if(PCkXTWSwip == true){PCkXTWSwip = false;}
      if(PBgmQmKhZq == true){PBgmQmKhZq = false;}
      if(KUyzdwgSuy == true){KUyzdwgSuy = false;}
      if(gItUKSwJAw == true){gItUKSwJAw = false;}
      if(YxOOoMJxaH == true){YxOOoMJxaH = false;}
      if(QHYqQtEltW == true){QHYqQtEltW = false;}
      if(ozAjJHHLbx == true){ozAjJHHLbx = false;}
      if(qAhdSMGiJQ == true){qAhdSMGiJQ = false;}
      if(mjrmgZiCDP == true){mjrmgZiCDP = false;}
      if(NKPcGYwdFg == true){NKPcGYwdFg = false;}
      if(ExUcQQZtYE == true){ExUcQQZtYE = false;}
      if(nUbcjEHNDi == true){nUbcjEHNDi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NLUEXGLARO
{ 
  void kmFeVMnEFD()
  { 
      bool mqdcBlSuFL = false;
      bool VEtezkQcBh = false;
      bool jZKoMjlFxi = false;
      bool MyAETQKzyo = false;
      bool UrtGpaVDEY = false;
      bool lknkRNfoQR = false;
      bool ANxVyWDoKi = false;
      bool ZQdMMqeDzk = false;
      bool OhAYxbKPlF = false;
      bool jVigoGtXHT = false;
      bool WfrUyVGbXa = false;
      bool hboeDRMYYW = false;
      bool MnCFzEgxWG = false;
      bool wGweOhofZa = false;
      bool VhqLWHfEcW = false;
      bool tVzkGhdmVt = false;
      bool oIERdbfKPU = false;
      bool bgyyBdwphq = false;
      bool XbTALZHKYf = false;
      bool DBJflMcZhu = false;
      string HyrIhIrOhS;
      string MHJCOUsOAm;
      string TINBtBudCG;
      string wXUYkPrSye;
      string JHWwrFQyEK;
      string XHAoyyjpNg;
      string MNLbVnmjRz;
      string caPUdLlRIo;
      string kwYrhnWeal;
      string eBERRuwuZD;
      string SgfFhxrfLl;
      string MRhYwQnTsh;
      string RHIfTaVyCh;
      string PprEWDQTKk;
      string wqToYNTfVB;
      string GbCqlKXAkG;
      string asccVWZcBr;
      string zUJHlanTGG;
      string HocAbnmASM;
      string fPhDKCNpSB;
      if(HyrIhIrOhS == SgfFhxrfLl){mqdcBlSuFL = true;}
      else if(SgfFhxrfLl == HyrIhIrOhS){WfrUyVGbXa = true;}
      if(MHJCOUsOAm == MRhYwQnTsh){VEtezkQcBh = true;}
      else if(MRhYwQnTsh == MHJCOUsOAm){hboeDRMYYW = true;}
      if(TINBtBudCG == RHIfTaVyCh){jZKoMjlFxi = true;}
      else if(RHIfTaVyCh == TINBtBudCG){MnCFzEgxWG = true;}
      if(wXUYkPrSye == PprEWDQTKk){MyAETQKzyo = true;}
      else if(PprEWDQTKk == wXUYkPrSye){wGweOhofZa = true;}
      if(JHWwrFQyEK == wqToYNTfVB){UrtGpaVDEY = true;}
      else if(wqToYNTfVB == JHWwrFQyEK){VhqLWHfEcW = true;}
      if(XHAoyyjpNg == GbCqlKXAkG){lknkRNfoQR = true;}
      else if(GbCqlKXAkG == XHAoyyjpNg){tVzkGhdmVt = true;}
      if(MNLbVnmjRz == asccVWZcBr){ANxVyWDoKi = true;}
      else if(asccVWZcBr == MNLbVnmjRz){oIERdbfKPU = true;}
      if(caPUdLlRIo == zUJHlanTGG){ZQdMMqeDzk = true;}
      if(kwYrhnWeal == HocAbnmASM){OhAYxbKPlF = true;}
      if(eBERRuwuZD == fPhDKCNpSB){jVigoGtXHT = true;}
      while(zUJHlanTGG == caPUdLlRIo){bgyyBdwphq = true;}
      while(HocAbnmASM == HocAbnmASM){XbTALZHKYf = true;}
      while(fPhDKCNpSB == fPhDKCNpSB){DBJflMcZhu = true;}
      if(mqdcBlSuFL == true){mqdcBlSuFL = false;}
      if(VEtezkQcBh == true){VEtezkQcBh = false;}
      if(jZKoMjlFxi == true){jZKoMjlFxi = false;}
      if(MyAETQKzyo == true){MyAETQKzyo = false;}
      if(UrtGpaVDEY == true){UrtGpaVDEY = false;}
      if(lknkRNfoQR == true){lknkRNfoQR = false;}
      if(ANxVyWDoKi == true){ANxVyWDoKi = false;}
      if(ZQdMMqeDzk == true){ZQdMMqeDzk = false;}
      if(OhAYxbKPlF == true){OhAYxbKPlF = false;}
      if(jVigoGtXHT == true){jVigoGtXHT = false;}
      if(WfrUyVGbXa == true){WfrUyVGbXa = false;}
      if(hboeDRMYYW == true){hboeDRMYYW = false;}
      if(MnCFzEgxWG == true){MnCFzEgxWG = false;}
      if(wGweOhofZa == true){wGweOhofZa = false;}
      if(VhqLWHfEcW == true){VhqLWHfEcW = false;}
      if(tVzkGhdmVt == true){tVzkGhdmVt = false;}
      if(oIERdbfKPU == true){oIERdbfKPU = false;}
      if(bgyyBdwphq == true){bgyyBdwphq = false;}
      if(XbTALZHKYf == true){XbTALZHKYf = false;}
      if(DBJflMcZhu == true){DBJflMcZhu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IZPRWTXDBW
{ 
  void IqZlkUgiGt()
  { 
      bool UXYVzWBzDb = false;
      bool ROFhKaHKoU = false;
      bool UECArLoGXc = false;
      bool oSgwjMJsna = false;
      bool kuQtXxhnVb = false;
      bool uEZsuPVXcn = false;
      bool gtbZlzgIyy = false;
      bool RNVNjZnIct = false;
      bool cBkwhjrnBT = false;
      bool pkQAsqTqHY = false;
      bool QZoXJghLJU = false;
      bool bMuhKfJfrC = false;
      bool GsHdHgxVUr = false;
      bool GxAEdDLMlA = false;
      bool BgdfrcphoM = false;
      bool hmyESXSLPc = false;
      bool jMqQNeLqEH = false;
      bool UwsrBYOakd = false;
      bool qPfHKSywlG = false;
      bool jAxJQnpNSN = false;
      string VEHUdCMEgq;
      string IaxnMExYSC;
      string GEgcNCgyjX;
      string wjWXgsADeZ;
      string SZVlZnCREf;
      string CHgCQRWdGb;
      string UOUIuYDYHT;
      string DttsjghtDZ;
      string zPsEUnDTGP;
      string VWwDEDFNqB;
      string jcJjbHNnSj;
      string icZgbFUPmH;
      string UjSrxgypnf;
      string bTDCpWFJbM;
      string aPBWfswPaz;
      string ioZjfAKRmu;
      string JWzlHPYXpF;
      string zLnafEhuME;
      string jhPnxmtTVp;
      string MnWgDDPOOP;
      if(VEHUdCMEgq == jcJjbHNnSj){UXYVzWBzDb = true;}
      else if(jcJjbHNnSj == VEHUdCMEgq){QZoXJghLJU = true;}
      if(IaxnMExYSC == icZgbFUPmH){ROFhKaHKoU = true;}
      else if(icZgbFUPmH == IaxnMExYSC){bMuhKfJfrC = true;}
      if(GEgcNCgyjX == UjSrxgypnf){UECArLoGXc = true;}
      else if(UjSrxgypnf == GEgcNCgyjX){GsHdHgxVUr = true;}
      if(wjWXgsADeZ == bTDCpWFJbM){oSgwjMJsna = true;}
      else if(bTDCpWFJbM == wjWXgsADeZ){GxAEdDLMlA = true;}
      if(SZVlZnCREf == aPBWfswPaz){kuQtXxhnVb = true;}
      else if(aPBWfswPaz == SZVlZnCREf){BgdfrcphoM = true;}
      if(CHgCQRWdGb == ioZjfAKRmu){uEZsuPVXcn = true;}
      else if(ioZjfAKRmu == CHgCQRWdGb){hmyESXSLPc = true;}
      if(UOUIuYDYHT == JWzlHPYXpF){gtbZlzgIyy = true;}
      else if(JWzlHPYXpF == UOUIuYDYHT){jMqQNeLqEH = true;}
      if(DttsjghtDZ == zLnafEhuME){RNVNjZnIct = true;}
      if(zPsEUnDTGP == jhPnxmtTVp){cBkwhjrnBT = true;}
      if(VWwDEDFNqB == MnWgDDPOOP){pkQAsqTqHY = true;}
      while(zLnafEhuME == DttsjghtDZ){UwsrBYOakd = true;}
      while(jhPnxmtTVp == jhPnxmtTVp){qPfHKSywlG = true;}
      while(MnWgDDPOOP == MnWgDDPOOP){jAxJQnpNSN = true;}
      if(UXYVzWBzDb == true){UXYVzWBzDb = false;}
      if(ROFhKaHKoU == true){ROFhKaHKoU = false;}
      if(UECArLoGXc == true){UECArLoGXc = false;}
      if(oSgwjMJsna == true){oSgwjMJsna = false;}
      if(kuQtXxhnVb == true){kuQtXxhnVb = false;}
      if(uEZsuPVXcn == true){uEZsuPVXcn = false;}
      if(gtbZlzgIyy == true){gtbZlzgIyy = false;}
      if(RNVNjZnIct == true){RNVNjZnIct = false;}
      if(cBkwhjrnBT == true){cBkwhjrnBT = false;}
      if(pkQAsqTqHY == true){pkQAsqTqHY = false;}
      if(QZoXJghLJU == true){QZoXJghLJU = false;}
      if(bMuhKfJfrC == true){bMuhKfJfrC = false;}
      if(GsHdHgxVUr == true){GsHdHgxVUr = false;}
      if(GxAEdDLMlA == true){GxAEdDLMlA = false;}
      if(BgdfrcphoM == true){BgdfrcphoM = false;}
      if(hmyESXSLPc == true){hmyESXSLPc = false;}
      if(jMqQNeLqEH == true){jMqQNeLqEH = false;}
      if(UwsrBYOakd == true){UwsrBYOakd = false;}
      if(qPfHKSywlG == true){qPfHKSywlG = false;}
      if(jAxJQnpNSN == true){jAxJQnpNSN = false;}
    } 
}; 
