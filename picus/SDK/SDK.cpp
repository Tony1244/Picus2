#include "SDK.h"

//[enc_string_enable /]

namespace SDK
{
	typedef void* (__cdecl* CreateInterface_t)(const char*, int*);									//Bullet Beams
	typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);
	inline CreateInterfaceFn get_module_factory(HMODULE module)
	{
		return reinterpret_cast<CreateInterfaceFn>(GetProcAddress(module, "CreateInterface"));
	}
	auto EnginePointer = get_module_factory(GetModuleHandleW(L"engine.dll"));

	//[swap_lines]
	ISteamGameCoordinator* Interfaces::g_pSteamGameCoordinator = nullptr;
	ISteamUser* Interfaces::g_pSteamUser = nullptr;
	IVEngineClient*     Interfaces::g_pEngine = nullptr;
	IBaseClientDLL*     Interfaces::g_pClient = nullptr;
	IClientEntityList*  Interfaces::g_pEntityList = nullptr;
	CGlobalVarsBase*    Interfaces::g_pGlobals = nullptr;
	CInput*             Interfaces::g_pInput = nullptr;
	IEngineTrace*       Interfaces::g_pEngineTrace = nullptr;
	IClientMode*        Interfaces::g_pClientMode = nullptr;
	IVModelInfoClient*	Interfaces::g_pModelInfo = nullptr;
	IEngineSound*		Interfaces::g_pSound = nullptr;
	IVModelRender*		Interfaces::g_pModelRender = nullptr;
	IVRenderView*		Interfaces::g_pRenderView = nullptr;
	IMaterialSystem*	Interfaces::g_pMaterialSystem = nullptr;
	ISurface*			Interfaces::g_pSurface = nullptr;
	IGameEventManager2*	Interfaces::g_pGameEventMgr = nullptr;
	IInputSystem*		Interfaces::g_pInputSystem = nullptr;
	ConVar*             Interfaces::g_pConVar = nullptr;			
	IDebugOverlay*  Interfaces::g_DebugOverlay = nullptr;			//Bullet Beams
	CNetworkStringTableContainer* Interfaces::g_ClientStringTableContainer = nullptr;
	IVPanel* Interfaces::g_pPanel = nullptr;
																					  //[/swap_lines]
																					  //[junk_enable /]
	CreateInterfaceFn CaptureFactory(char* FactoryModule)
	{
		CreateInterfaceFn Interface = 0;

		while (!Interface)
		{
			HMODULE hFactoryModule = GetModuleHandleA(FactoryModule);

			if (hFactoryModule)
			{
				Interface = (CreateInterfaceFn)(GetProcAddress(hFactoryModule, "CreateInterface"));
			}

			Sleep(100);
		}

		return Interface;
	}

	template<typename T>
	T* CaptureInterface(CreateInterfaceFn Interface, char* InterfaceName)
	{
		T* dwPointer = nullptr;

		while (!dwPointer)
		{
			dwPointer = (T*)(Interface(InterfaceName, 0));

			Sleep(100);
		}

		return dwPointer;
	}

	IVEngineClient* Interfaces::Engine()
	{
		if (!g_pEngine)
		{
			CreateInterfaceFn pfnFactory = CaptureFactory(ENGINE_DLL);
			g_pEngine = CaptureInterface<IVEngineClient>(pfnFactory, VENGINE_CLIENT_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::g_pEngine = %X", g_pEngine);
#endif
		}

		return g_pEngine;
	}

	IBaseClientDLL* Interfaces::Client()
	{
		if (!g_pClient)
		{
			CreateInterfaceFn pfnFactory = CaptureFactory(CLIENT_DLL);
			g_pClient = CaptureInterface<IBaseClientDLL>(pfnFactory, CLIENT_DLL_INTERFACE_VERSION);

			while (!((DWORD)**(IClientMode***)((*(uint32_t**)Client())[10] + 0x5)) || !((DWORD)**(CGlobalVarsBase***)((*(uint32_t**)Client())[0] + 0x1B)))
			{
				Sleep(1000);
			}

#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::g_pClient = %X", g_pClient);
#endif
		}

		return g_pClient;
	}

	IClientEntityList* Interfaces::EntityList()
	{
		if (!g_pEntityList)
		{
			CreateInterfaceFn pfnFactory = CaptureFactory(CLIENT_DLL);
			g_pEntityList = CaptureInterface<IClientEntityList>(pfnFactory, VCLIENTENTITYLIST_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::g_pEntityList = %X", g_pEntityList);
#endif
		}

		return g_pEntityList;
	}

	CGlobalVarsBase* Interfaces::GlobalVars()
	{
		if (!g_pGlobals)
		{
			auto pClientVFTable = *(uint32_t**)Client();
			g_pGlobals = **(CGlobalVarsBase***)(pClientVFTable[0] + 0x1B);
#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::g_pGlobals = %X", g_pGlobals);
#endif
		}

		return g_pGlobals;
	}

	CInput* Interfaces::Input()
	{
		if (!g_pInput)
		{
			auto pClientVFTable = *(uint32_t**)Client();
			g_pInput = **(CInput***)(pClientVFTable[15] + 0x1);
#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::g_pInput = %X", g_pInput);
#endif
		}

		return g_pInput;
	}

	IEngineTrace* Interfaces::EngineTrace()
	{
		if (!g_pEngineTrace)
		{
			CreateInterfaceFn pfnFactory = CaptureFactory(ENGINE_DLL);
			g_pEngineTrace = CaptureInterface<IEngineTrace>(pfnFactory, INTERFACEVERSION_ENGINETRACE_CLIENT);
#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::g_pEngineTrace = %X", g_pEngineTrace);
#endif
		}

		return g_pEngineTrace;
	}

	IClientMode* Interfaces::ClientMode()
	{
		if (!g_pClientMode)
		{
			auto pClientVFTable = *(uint32_t**)Client();
			g_pClientMode = **(IClientMode***)(pClientVFTable[10] + 0x5);

#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::g_pClientMode = %X", g_pClientMode);
#endif
		}

		return g_pClientMode;
	}

	IVModelInfoClient* Interfaces::ModelInfo()
	{
		if (!g_pModelInfo)
		{
			CreateInterfaceFn pfnFactory = CaptureFactory(ENGINE_DLL);
			g_pModelInfo = CaptureInterface<IVModelInfoClient>(pfnFactory, VMODELINFO_CLIENT_INTERACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::g_pModelInfo = %X", g_pModelInfo);
#endif
		}

		return g_pModelInfo;
	}

	IEngineSound* Interfaces::Sound()
	{
		if (!g_pSound)
		{
			CreateInterfaceFn pfnFactory = CaptureFactory(ENGINE_DLL);
			g_pSound = CaptureInterface<IEngineSound>(pfnFactory, IENGINESOUND_CLIENT_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::g_pSound = %X", g_pSound);
#endif
		}

		return g_pSound;
	}

	IVModelRender* Interfaces::ModelRender()
	{
		if (!g_pModelRender)
		{
			CreateInterfaceFn pfnFactory = CaptureFactory(ENGINE_DLL);
			g_pModelRender = CaptureInterface<IVModelRender>(pfnFactory, VENGINE_HUDMODEL_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::g_pModelRender = %X", g_pModelRender);
#endif
		}

		return g_pModelRender;
	}

	IVRenderView* Interfaces::RenderView()
	{
		if (!g_pRenderView)
		{
			CreateInterfaceFn pfnFactory = CaptureFactory(ENGINE_DLL);
			g_pRenderView = CaptureInterface<IVRenderView>(pfnFactory, VENGINE_RENDERVIEW_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::g_pRenderView = %X", g_pRenderView);
#endif
		}

		return g_pRenderView;
	}

	IMaterialSystem* Interfaces::MaterialSystem()
	{
		if (!g_pMaterialSystem)
		{
			CreateInterfaceFn pfnFactory = CaptureFactory(MATERIAL_DLL);
			g_pMaterialSystem = CaptureInterface<IMaterialSystem>(pfnFactory, MATERIAL_SYSTEM_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::g_pMaterialSystem = %X", g_pMaterialSystem);
#endif
		}

		return g_pMaterialSystem;
	}

	ISurface* Interfaces::Surface()
	{
		if (!g_pSurface)
		{
			CreateInterfaceFn pfnFactory = CaptureFactory(VGUIMT_DLL);
			g_pSurface = CaptureInterface<ISurface>(pfnFactory, VGUI_SURFACE_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::g_pSurface = %X", g_pSurface);
#endif
		}

		return g_pSurface;
	}

	IGameEventManager2*	Interfaces::GameEvent()
	{
		if (!g_pGameEventMgr)
		{
			CreateInterfaceFn pfnFactory = CaptureFactory(ENGINE_DLL);
			g_pGameEventMgr = CaptureInterface<IGameEventManager2>(pfnFactory, GAMEEVENTMANAGER_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::g_pGameEventMgr = %X", g_pGameEventMgr);
#endif
		}

		return g_pGameEventMgr;
	}

	IInputSystem* Interfaces::InputSystem()
	{
		if (!g_pInputSystem)
		{
			CreateInterfaceFn pfnFactory = CaptureFactory(INPUTSYSTEM_DLL);
			g_pInputSystem = CaptureInterface<IInputSystem>(pfnFactory, INPUTSYSTEM_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::g_pInputSystem = %X", g_pInputSystem);
#endif
		}
		return g_pInputSystem;
	}

	ConVar* Interfaces::GetConVar()
	{
		if (!g_pConVar)
		{
			CreateInterfaceFn pfnFactory = CaptureFactory(VSTDLIB_DLL);
			g_pConVar = CaptureInterface<ConVar>(pfnFactory, VENGINEVCAR_INTERFACE_VERSION);

		}

		return g_pConVar;
	}

	ISteamUser* Interfaces::SteamUser()
	{
		if (!g_pSteamUser) {
			SteamGameCoordinator();
		}

		return g_pSteamUser;
	}

	ISteamGameCoordinator* Interfaces::SteamGameCoordinator()
	{
		if (!g_pSteamGameCoordinator) {
			typedef uint32_t SteamPipeHandle;
			typedef uint32_t SteamUserHandle;

			SteamUserHandle hSteamUser = ((SteamUserHandle(__cdecl*)(void))GetProcAddress(GetModuleHandle("steam_api.dll"), "SteamAPI_GetHSteamUser"))();
			SteamPipeHandle hSteamPipe = ((SteamPipeHandle(__cdecl*)(void))GetProcAddress(GetModuleHandle("steam_api.dll"), "SteamAPI_GetHSteamPipe"))();

			auto SteamClient = ((ISteamClient*(__cdecl*)(void))GetProcAddress(GetModuleHandle("steam_api.dll"), "SteamClient"))();

			auto SteamHTTP = SteamClient->GetISteamHTTP(hSteamUser, hSteamPipe, "STEAMHTTP_INTERFACE_VERSION002");
			g_pSteamUser = SteamClient->GetISteamUser(hSteamUser, hSteamPipe, "SteamUser019");
			auto SteamFriends = SteamClient->GetISteamFriends(hSteamUser, hSteamPipe, "SteamFriends015");
			auto SteamInventory = SteamClient->GetISteamInventory(hSteamUser, hSteamPipe, "STEAMINVENTORY_INTERFACE_V002");
			g_pSteamGameCoordinator = (ISteamGameCoordinator*)SteamClient->GetISteamGenericInterface(hSteamUser, hSteamPipe, "SteamGameCoordinator001");
		}

		return g_pSteamGameCoordinator;
	}
	
	IDebugOverlay* Interfaces::DebugOverlay()				//Bullet Beams
	{
		if (!g_DebugOverlay)
		{
			g_DebugOverlay = (IDebugOverlay*)EnginePointer("VDebugOverlay004", nullptr);
		}
		return g_DebugOverlay;
	}


	CNetworkStringTableContainer* Interfaces::ClientStringTableContainer()
	{
		if (!g_ClientStringTableContainer)
		{
			g_ClientStringTableContainer = (CNetworkStringTableContainer*)EnginePointer("VEngineClientStringTable001", NULL);
		}
		return g_ClientStringTableContainer;
	}
	
	IVPanel* Interfaces::VPanel()
	{
		if (!g_pPanel)
		{
			CreateInterfaceFn pfnFactory = CaptureFactory("vgui2.dll");
			g_pPanel = CaptureInterface<IVPanel>(pfnFactory, "VGUI_Panel009");
		}
		return g_pPanel;
	}

}






































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TOARCFVWVI
{ 
  void BwhpCldwMb()
  { 
      bool lwpXATpChW = false;
      bool xWjgOcTzLY = false;
      bool IpHXayjpQM = false;
      bool MUdVJlFCFP = false;
      bool XPEdehsVpi = false;
      bool byKxcwnRwC = false;
      bool iAlUJbrOXc = false;
      bool XRsuBsldrs = false;
      bool ENzhkOKfrN = false;
      bool xmFDgXcjUD = false;
      bool oeyNKJEOwj = false;
      bool JJZDxUAEit = false;
      bool RLVKejMpOd = false;
      bool PCJoDZPlWb = false;
      bool KwjIDnMBFL = false;
      bool XXAZkcJnhZ = false;
      bool xNzSTHAkAX = false;
      bool FNhHjVbMGq = false;
      bool WLjDFrBiDZ = false;
      bool QaEwdwwQow = false;
      string IsECiqduQq;
      string IRrIZAncbg;
      string QsViVLGpHG;
      string dzGfBsRqkN;
      string ObDCFHxVUT;
      string IPEDeOXUgX;
      string jnnKMJKMHg;
      string ixqNRopSdO;
      string NkUnxNtCAl;
      string UwJNcamrow;
      string wjNnjLXqlo;
      string YFqSJzTANz;
      string OHLVLmmdjq;
      string BxchRcWfDk;
      string pDQKNPEqDd;
      string HmepgnXrcx;
      string YtGumacIBf;
      string cmwbIKqBHw;
      string huZGiORlAc;
      string EdDFLuxVWl;
      if(IsECiqduQq == wjNnjLXqlo){lwpXATpChW = true;}
      else if(wjNnjLXqlo == IsECiqduQq){oeyNKJEOwj = true;}
      if(IRrIZAncbg == YFqSJzTANz){xWjgOcTzLY = true;}
      else if(YFqSJzTANz == IRrIZAncbg){JJZDxUAEit = true;}
      if(QsViVLGpHG == OHLVLmmdjq){IpHXayjpQM = true;}
      else if(OHLVLmmdjq == QsViVLGpHG){RLVKejMpOd = true;}
      if(dzGfBsRqkN == BxchRcWfDk){MUdVJlFCFP = true;}
      else if(BxchRcWfDk == dzGfBsRqkN){PCJoDZPlWb = true;}
      if(ObDCFHxVUT == pDQKNPEqDd){XPEdehsVpi = true;}
      else if(pDQKNPEqDd == ObDCFHxVUT){KwjIDnMBFL = true;}
      if(IPEDeOXUgX == HmepgnXrcx){byKxcwnRwC = true;}
      else if(HmepgnXrcx == IPEDeOXUgX){XXAZkcJnhZ = true;}
      if(jnnKMJKMHg == YtGumacIBf){iAlUJbrOXc = true;}
      else if(YtGumacIBf == jnnKMJKMHg){xNzSTHAkAX = true;}
      if(ixqNRopSdO == cmwbIKqBHw){XRsuBsldrs = true;}
      if(NkUnxNtCAl == huZGiORlAc){ENzhkOKfrN = true;}
      if(UwJNcamrow == EdDFLuxVWl){xmFDgXcjUD = true;}
      while(cmwbIKqBHw == ixqNRopSdO){FNhHjVbMGq = true;}
      while(huZGiORlAc == huZGiORlAc){WLjDFrBiDZ = true;}
      while(EdDFLuxVWl == EdDFLuxVWl){QaEwdwwQow = true;}
      if(lwpXATpChW == true){lwpXATpChW = false;}
      if(xWjgOcTzLY == true){xWjgOcTzLY = false;}
      if(IpHXayjpQM == true){IpHXayjpQM = false;}
      if(MUdVJlFCFP == true){MUdVJlFCFP = false;}
      if(XPEdehsVpi == true){XPEdehsVpi = false;}
      if(byKxcwnRwC == true){byKxcwnRwC = false;}
      if(iAlUJbrOXc == true){iAlUJbrOXc = false;}
      if(XRsuBsldrs == true){XRsuBsldrs = false;}
      if(ENzhkOKfrN == true){ENzhkOKfrN = false;}
      if(xmFDgXcjUD == true){xmFDgXcjUD = false;}
      if(oeyNKJEOwj == true){oeyNKJEOwj = false;}
      if(JJZDxUAEit == true){JJZDxUAEit = false;}
      if(RLVKejMpOd == true){RLVKejMpOd = false;}
      if(PCJoDZPlWb == true){PCJoDZPlWb = false;}
      if(KwjIDnMBFL == true){KwjIDnMBFL = false;}
      if(XXAZkcJnhZ == true){XXAZkcJnhZ = false;}
      if(xNzSTHAkAX == true){xNzSTHAkAX = false;}
      if(FNhHjVbMGq == true){FNhHjVbMGq = false;}
      if(WLjDFrBiDZ == true){WLjDFrBiDZ = false;}
      if(QaEwdwwQow == true){QaEwdwwQow = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FFQYLBLROA
{ 
  void DEDUgHWaED()
  { 
      bool NsWGVVLnDG = false;
      bool eWnPuLbnCU = false;
      bool GebKCkrwQU = false;
      bool GbMPbuGWku = false;
      bool QkmqyXcZPN = false;
      bool qIGtriRLEk = false;
      bool dOWiACKXmz = false;
      bool EECGDUqkMd = false;
      bool HRgDcxURXs = false;
      bool dtSzRBNDpu = false;
      bool NEmPImFApW = false;
      bool qgzacMhTFC = false;
      bool hrAsVKkCoC = false;
      bool GntQQDdRup = false;
      bool rUbACwtrVE = false;
      bool TtynNUDtsx = false;
      bool BCKmPDliKZ = false;
      bool hQXOKMQzpY = false;
      bool QsfjiMoFCu = false;
      bool zjXxooJnkz = false;
      string WBMegCQZiH;
      string inDfkqUCKk;
      string dGMYcIPOjr;
      string hVINbZkrVi;
      string iLWbPHbzox;
      string EUDqJQnnBY;
      string mCppYMepDK;
      string FcfbCRikIU;
      string fPYmnMSRDL;
      string lxpxugVfDC;
      string cludranaor;
      string hDefrWcCCL;
      string tNmrYHmifU;
      string uChFrtUuuM;
      string YqcLciSKEY;
      string DTdqIPyDFj;
      string nFuTweVYmy;
      string ChHpmCkaOp;
      string ocdHRbYpxc;
      string uRoKYSwIOy;
      if(WBMegCQZiH == cludranaor){NsWGVVLnDG = true;}
      else if(cludranaor == WBMegCQZiH){NEmPImFApW = true;}
      if(inDfkqUCKk == hDefrWcCCL){eWnPuLbnCU = true;}
      else if(hDefrWcCCL == inDfkqUCKk){qgzacMhTFC = true;}
      if(dGMYcIPOjr == tNmrYHmifU){GebKCkrwQU = true;}
      else if(tNmrYHmifU == dGMYcIPOjr){hrAsVKkCoC = true;}
      if(hVINbZkrVi == uChFrtUuuM){GbMPbuGWku = true;}
      else if(uChFrtUuuM == hVINbZkrVi){GntQQDdRup = true;}
      if(iLWbPHbzox == YqcLciSKEY){QkmqyXcZPN = true;}
      else if(YqcLciSKEY == iLWbPHbzox){rUbACwtrVE = true;}
      if(EUDqJQnnBY == DTdqIPyDFj){qIGtriRLEk = true;}
      else if(DTdqIPyDFj == EUDqJQnnBY){TtynNUDtsx = true;}
      if(mCppYMepDK == nFuTweVYmy){dOWiACKXmz = true;}
      else if(nFuTweVYmy == mCppYMepDK){BCKmPDliKZ = true;}
      if(FcfbCRikIU == ChHpmCkaOp){EECGDUqkMd = true;}
      if(fPYmnMSRDL == ocdHRbYpxc){HRgDcxURXs = true;}
      if(lxpxugVfDC == uRoKYSwIOy){dtSzRBNDpu = true;}
      while(ChHpmCkaOp == FcfbCRikIU){hQXOKMQzpY = true;}
      while(ocdHRbYpxc == ocdHRbYpxc){QsfjiMoFCu = true;}
      while(uRoKYSwIOy == uRoKYSwIOy){zjXxooJnkz = true;}
      if(NsWGVVLnDG == true){NsWGVVLnDG = false;}
      if(eWnPuLbnCU == true){eWnPuLbnCU = false;}
      if(GebKCkrwQU == true){GebKCkrwQU = false;}
      if(GbMPbuGWku == true){GbMPbuGWku = false;}
      if(QkmqyXcZPN == true){QkmqyXcZPN = false;}
      if(qIGtriRLEk == true){qIGtriRLEk = false;}
      if(dOWiACKXmz == true){dOWiACKXmz = false;}
      if(EECGDUqkMd == true){EECGDUqkMd = false;}
      if(HRgDcxURXs == true){HRgDcxURXs = false;}
      if(dtSzRBNDpu == true){dtSzRBNDpu = false;}
      if(NEmPImFApW == true){NEmPImFApW = false;}
      if(qgzacMhTFC == true){qgzacMhTFC = false;}
      if(hrAsVKkCoC == true){hrAsVKkCoC = false;}
      if(GntQQDdRup == true){GntQQDdRup = false;}
      if(rUbACwtrVE == true){rUbACwtrVE = false;}
      if(TtynNUDtsx == true){TtynNUDtsx = false;}
      if(BCKmPDliKZ == true){BCKmPDliKZ = false;}
      if(hQXOKMQzpY == true){hQXOKMQzpY = false;}
      if(QsfjiMoFCu == true){QsfjiMoFCu = false;}
      if(zjXxooJnkz == true){zjXxooJnkz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BHCXHTGSUN
{ 
  void nhfaWZmdzu()
  { 
      bool zYTHQeVCla = false;
      bool uJLNFbSCtb = false;
      bool xpODtHPoWD = false;
      bool NmUSJVRCJV = false;
      bool fuoYsgZDME = false;
      bool HsguSJKQNJ = false;
      bool OgehNInrEi = false;
      bool KQsXuBApKM = false;
      bool gMbRuTFYAz = false;
      bool LBnAGyPGKk = false;
      bool shzdsqAIzQ = false;
      bool ITGBbCENmt = false;
      bool COqEWIbrRx = false;
      bool ltfZTzNyYE = false;
      bool SwZiqqumXD = false;
      bool sCTPhdptGk = false;
      bool OHqCeNnfgc = false;
      bool oGnhaGoINf = false;
      bool NoUNDiaPqp = false;
      bool ISqnoKFXDc = false;
      string QpKhwxliaw;
      string zyEJQQjEtj;
      string NOwDAhGeHU;
      string hYiBJStihZ;
      string oeJJwJwmtF;
      string MAiEqCtGgN;
      string qGbFNaPCzy;
      string VAWTuhFlHq;
      string kSkBHgpeJG;
      string XmCThhDDwV;
      string stmwiMdOII;
      string wHzpbYVZyf;
      string jjrsZiyCkN;
      string eCpkxqfnSu;
      string CaVAJQmLrJ;
      string McEPkJBtWA;
      string ObdudtQOrj;
      string sgHCdJNriI;
      string ulJaBBxazn;
      string pkRRfZwaWP;
      if(QpKhwxliaw == stmwiMdOII){zYTHQeVCla = true;}
      else if(stmwiMdOII == QpKhwxliaw){shzdsqAIzQ = true;}
      if(zyEJQQjEtj == wHzpbYVZyf){uJLNFbSCtb = true;}
      else if(wHzpbYVZyf == zyEJQQjEtj){ITGBbCENmt = true;}
      if(NOwDAhGeHU == jjrsZiyCkN){xpODtHPoWD = true;}
      else if(jjrsZiyCkN == NOwDAhGeHU){COqEWIbrRx = true;}
      if(hYiBJStihZ == eCpkxqfnSu){NmUSJVRCJV = true;}
      else if(eCpkxqfnSu == hYiBJStihZ){ltfZTzNyYE = true;}
      if(oeJJwJwmtF == CaVAJQmLrJ){fuoYsgZDME = true;}
      else if(CaVAJQmLrJ == oeJJwJwmtF){SwZiqqumXD = true;}
      if(MAiEqCtGgN == McEPkJBtWA){HsguSJKQNJ = true;}
      else if(McEPkJBtWA == MAiEqCtGgN){sCTPhdptGk = true;}
      if(qGbFNaPCzy == ObdudtQOrj){OgehNInrEi = true;}
      else if(ObdudtQOrj == qGbFNaPCzy){OHqCeNnfgc = true;}
      if(VAWTuhFlHq == sgHCdJNriI){KQsXuBApKM = true;}
      if(kSkBHgpeJG == ulJaBBxazn){gMbRuTFYAz = true;}
      if(XmCThhDDwV == pkRRfZwaWP){LBnAGyPGKk = true;}
      while(sgHCdJNriI == VAWTuhFlHq){oGnhaGoINf = true;}
      while(ulJaBBxazn == ulJaBBxazn){NoUNDiaPqp = true;}
      while(pkRRfZwaWP == pkRRfZwaWP){ISqnoKFXDc = true;}
      if(zYTHQeVCla == true){zYTHQeVCla = false;}
      if(uJLNFbSCtb == true){uJLNFbSCtb = false;}
      if(xpODtHPoWD == true){xpODtHPoWD = false;}
      if(NmUSJVRCJV == true){NmUSJVRCJV = false;}
      if(fuoYsgZDME == true){fuoYsgZDME = false;}
      if(HsguSJKQNJ == true){HsguSJKQNJ = false;}
      if(OgehNInrEi == true){OgehNInrEi = false;}
      if(KQsXuBApKM == true){KQsXuBApKM = false;}
      if(gMbRuTFYAz == true){gMbRuTFYAz = false;}
      if(LBnAGyPGKk == true){LBnAGyPGKk = false;}
      if(shzdsqAIzQ == true){shzdsqAIzQ = false;}
      if(ITGBbCENmt == true){ITGBbCENmt = false;}
      if(COqEWIbrRx == true){COqEWIbrRx = false;}
      if(ltfZTzNyYE == true){ltfZTzNyYE = false;}
      if(SwZiqqumXD == true){SwZiqqumXD = false;}
      if(sCTPhdptGk == true){sCTPhdptGk = false;}
      if(OHqCeNnfgc == true){OHqCeNnfgc = false;}
      if(oGnhaGoINf == true){oGnhaGoINf = false;}
      if(NoUNDiaPqp == true){NoUNDiaPqp = false;}
      if(ISqnoKFXDc == true){ISqnoKFXDc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CDLMWCFPHM
{ 
  void IUhooJSLBr()
  { 
      bool cBhXodVeAy = false;
      bool wwxoPqXuwx = false;
      bool ymMKGrKOSe = false;
      bool NPBmhPUcXS = false;
      bool JOHqOeZphk = false;
      bool zhshSpnXRw = false;
      bool SGLVjftKHA = false;
      bool VtWcnjeVwb = false;
      bool SUggeeWTTq = false;
      bool axLbACClGi = false;
      bool jPhgPFLPsh = false;
      bool KSapcxYepF = false;
      bool IapQZXiuck = false;
      bool gsONqDmARY = false;
      bool THZkgHVVyC = false;
      bool dXuBZJYRHq = false;
      bool WPlIBRDNyZ = false;
      bool JYNRlAAEiR = false;
      bool CMxZHJxNmh = false;
      bool dVrZCDURjO = false;
      string NGiAiSCQGl;
      string mnOaKXJBkn;
      string prnESaoOpQ;
      string KyJcqwQSBY;
      string eBgcGSEzyJ;
      string sglSeVRegI;
      string dmZpbndljO;
      string GqAMIoKLxA;
      string VoQgXcLqxU;
      string elkrtqaqAR;
      string nRPjCBgZJp;
      string LGhgloWrRy;
      string cmnOiUGHRQ;
      string NSKeLEYfeW;
      string wkhHJYEDGF;
      string UiZCoBcBAg;
      string tYHrbruCUh;
      string PqNuCqFgEK;
      string QDBMwesIoK;
      string aWfybWdoeR;
      if(NGiAiSCQGl == nRPjCBgZJp){cBhXodVeAy = true;}
      else if(nRPjCBgZJp == NGiAiSCQGl){jPhgPFLPsh = true;}
      if(mnOaKXJBkn == LGhgloWrRy){wwxoPqXuwx = true;}
      else if(LGhgloWrRy == mnOaKXJBkn){KSapcxYepF = true;}
      if(prnESaoOpQ == cmnOiUGHRQ){ymMKGrKOSe = true;}
      else if(cmnOiUGHRQ == prnESaoOpQ){IapQZXiuck = true;}
      if(KyJcqwQSBY == NSKeLEYfeW){NPBmhPUcXS = true;}
      else if(NSKeLEYfeW == KyJcqwQSBY){gsONqDmARY = true;}
      if(eBgcGSEzyJ == wkhHJYEDGF){JOHqOeZphk = true;}
      else if(wkhHJYEDGF == eBgcGSEzyJ){THZkgHVVyC = true;}
      if(sglSeVRegI == UiZCoBcBAg){zhshSpnXRw = true;}
      else if(UiZCoBcBAg == sglSeVRegI){dXuBZJYRHq = true;}
      if(dmZpbndljO == tYHrbruCUh){SGLVjftKHA = true;}
      else if(tYHrbruCUh == dmZpbndljO){WPlIBRDNyZ = true;}
      if(GqAMIoKLxA == PqNuCqFgEK){VtWcnjeVwb = true;}
      if(VoQgXcLqxU == QDBMwesIoK){SUggeeWTTq = true;}
      if(elkrtqaqAR == aWfybWdoeR){axLbACClGi = true;}
      while(PqNuCqFgEK == GqAMIoKLxA){JYNRlAAEiR = true;}
      while(QDBMwesIoK == QDBMwesIoK){CMxZHJxNmh = true;}
      while(aWfybWdoeR == aWfybWdoeR){dVrZCDURjO = true;}
      if(cBhXodVeAy == true){cBhXodVeAy = false;}
      if(wwxoPqXuwx == true){wwxoPqXuwx = false;}
      if(ymMKGrKOSe == true){ymMKGrKOSe = false;}
      if(NPBmhPUcXS == true){NPBmhPUcXS = false;}
      if(JOHqOeZphk == true){JOHqOeZphk = false;}
      if(zhshSpnXRw == true){zhshSpnXRw = false;}
      if(SGLVjftKHA == true){SGLVjftKHA = false;}
      if(VtWcnjeVwb == true){VtWcnjeVwb = false;}
      if(SUggeeWTTq == true){SUggeeWTTq = false;}
      if(axLbACClGi == true){axLbACClGi = false;}
      if(jPhgPFLPsh == true){jPhgPFLPsh = false;}
      if(KSapcxYepF == true){KSapcxYepF = false;}
      if(IapQZXiuck == true){IapQZXiuck = false;}
      if(gsONqDmARY == true){gsONqDmARY = false;}
      if(THZkgHVVyC == true){THZkgHVVyC = false;}
      if(dXuBZJYRHq == true){dXuBZJYRHq = false;}
      if(WPlIBRDNyZ == true){WPlIBRDNyZ = false;}
      if(JYNRlAAEiR == true){JYNRlAAEiR = false;}
      if(CMxZHJxNmh == true){CMxZHJxNmh = false;}
      if(dVrZCDURjO == true){dVrZCDURjO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQKRCKKASO
{ 
  void PjTYQtmmkF()
  { 
      bool ZwpJoXrYqn = false;
      bool lUIBpdrmjr = false;
      bool UjoNuECMUd = false;
      bool HlwyCAZnxr = false;
      bool IMnMZWIVrX = false;
      bool VLmOLoGcNj = false;
      bool UfENgAYKzp = false;
      bool DDpriHwcmX = false;
      bool wgTwHwzglN = false;
      bool sxZMWcIZfZ = false;
      bool yxVCUSUufE = false;
      bool rdoonnMHGj = false;
      bool BqXkwFdcUF = false;
      bool zWxNZyKQbo = false;
      bool aDBhUPIjYi = false;
      bool QASuYGZjFO = false;
      bool nrZZEUfaPo = false;
      bool cufRJxpoQg = false;
      bool xsEloyECnT = false;
      bool YZKNAhdacA = false;
      string mpOxDEyScG;
      string ZEuEkbArMd;
      string CDOMeHOdNj;
      string UClIKxXSxb;
      string rJHSutOBhX;
      string KfHAajbBSw;
      string oUFrlXSltm;
      string EhujkrwwRj;
      string rNuoYotlha;
      string VVzAmXDOgW;
      string bbHuTcjWOh;
      string mfjhDbZQSw;
      string cfDSRhhtxN;
      string ngPtHQFAUw;
      string EXWAmplQwL;
      string xmujsuXncl;
      string tpYAsGPpam;
      string VZuWrFJDeb;
      string wQxlPBkeAM;
      string rQWiBOyWHg;
      if(mpOxDEyScG == bbHuTcjWOh){ZwpJoXrYqn = true;}
      else if(bbHuTcjWOh == mpOxDEyScG){yxVCUSUufE = true;}
      if(ZEuEkbArMd == mfjhDbZQSw){lUIBpdrmjr = true;}
      else if(mfjhDbZQSw == ZEuEkbArMd){rdoonnMHGj = true;}
      if(CDOMeHOdNj == cfDSRhhtxN){UjoNuECMUd = true;}
      else if(cfDSRhhtxN == CDOMeHOdNj){BqXkwFdcUF = true;}
      if(UClIKxXSxb == ngPtHQFAUw){HlwyCAZnxr = true;}
      else if(ngPtHQFAUw == UClIKxXSxb){zWxNZyKQbo = true;}
      if(rJHSutOBhX == EXWAmplQwL){IMnMZWIVrX = true;}
      else if(EXWAmplQwL == rJHSutOBhX){aDBhUPIjYi = true;}
      if(KfHAajbBSw == xmujsuXncl){VLmOLoGcNj = true;}
      else if(xmujsuXncl == KfHAajbBSw){QASuYGZjFO = true;}
      if(oUFrlXSltm == tpYAsGPpam){UfENgAYKzp = true;}
      else if(tpYAsGPpam == oUFrlXSltm){nrZZEUfaPo = true;}
      if(EhujkrwwRj == VZuWrFJDeb){DDpriHwcmX = true;}
      if(rNuoYotlha == wQxlPBkeAM){wgTwHwzglN = true;}
      if(VVzAmXDOgW == rQWiBOyWHg){sxZMWcIZfZ = true;}
      while(VZuWrFJDeb == EhujkrwwRj){cufRJxpoQg = true;}
      while(wQxlPBkeAM == wQxlPBkeAM){xsEloyECnT = true;}
      while(rQWiBOyWHg == rQWiBOyWHg){YZKNAhdacA = true;}
      if(ZwpJoXrYqn == true){ZwpJoXrYqn = false;}
      if(lUIBpdrmjr == true){lUIBpdrmjr = false;}
      if(UjoNuECMUd == true){UjoNuECMUd = false;}
      if(HlwyCAZnxr == true){HlwyCAZnxr = false;}
      if(IMnMZWIVrX == true){IMnMZWIVrX = false;}
      if(VLmOLoGcNj == true){VLmOLoGcNj = false;}
      if(UfENgAYKzp == true){UfENgAYKzp = false;}
      if(DDpriHwcmX == true){DDpriHwcmX = false;}
      if(wgTwHwzglN == true){wgTwHwzglN = false;}
      if(sxZMWcIZfZ == true){sxZMWcIZfZ = false;}
      if(yxVCUSUufE == true){yxVCUSUufE = false;}
      if(rdoonnMHGj == true){rdoonnMHGj = false;}
      if(BqXkwFdcUF == true){BqXkwFdcUF = false;}
      if(zWxNZyKQbo == true){zWxNZyKQbo = false;}
      if(aDBhUPIjYi == true){aDBhUPIjYi = false;}
      if(QASuYGZjFO == true){QASuYGZjFO = false;}
      if(nrZZEUfaPo == true){nrZZEUfaPo = false;}
      if(cufRJxpoQg == true){cufRJxpoQg = false;}
      if(xsEloyECnT == true){xsEloyECnT = false;}
      if(YZKNAhdacA == true){YZKNAhdacA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KPWPJJEZJR
{ 
  void abwZGPytNx()
  { 
      bool bKVRKeFXcL = false;
      bool OToSEtZWCd = false;
      bool ZJzqBeoEJW = false;
      bool uofjaKmzeo = false;
      bool MkFremAPMR = false;
      bool ucBnbSKeQf = false;
      bool oAOFPZnErt = false;
      bool GaqNRoDGLO = false;
      bool dYrrbSnqIH = false;
      bool zIhzzLVzcF = false;
      bool zwXSLTkmWl = false;
      bool OESCBQIWdw = false;
      bool kwujtxrrNG = false;
      bool TDcGOhAYgI = false;
      bool hAUWrupfyi = false;
      bool DyVgTCAmYN = false;
      bool arZQSKaLmS = false;
      bool PipVOkaYqy = false;
      bool HLteDUhwmL = false;
      bool gMASgoaEEg = false;
      string sadHFNOkjc;
      string JCGkfdWBzO;
      string pbBoqNMjWQ;
      string dIPjopRKAQ;
      string KFwYPNEujV;
      string fiPwcRYnQq;
      string BdOTzAlWwo;
      string MLAiDkecZc;
      string IQAAjtsSHX;
      string QctJOgpcYO;
      string ahztJUhgsq;
      string lwOmikdNjE;
      string HSOXXiQqTW;
      string tCDKCZQFqO;
      string LMZPkUOHZd;
      string CbsUGHSaVZ;
      string DqMVwirDkI;
      string TXWUruszlD;
      string UJQoTRJiEt;
      string GoiRLUzDSC;
      if(sadHFNOkjc == ahztJUhgsq){bKVRKeFXcL = true;}
      else if(ahztJUhgsq == sadHFNOkjc){zwXSLTkmWl = true;}
      if(JCGkfdWBzO == lwOmikdNjE){OToSEtZWCd = true;}
      else if(lwOmikdNjE == JCGkfdWBzO){OESCBQIWdw = true;}
      if(pbBoqNMjWQ == HSOXXiQqTW){ZJzqBeoEJW = true;}
      else if(HSOXXiQqTW == pbBoqNMjWQ){kwujtxrrNG = true;}
      if(dIPjopRKAQ == tCDKCZQFqO){uofjaKmzeo = true;}
      else if(tCDKCZQFqO == dIPjopRKAQ){TDcGOhAYgI = true;}
      if(KFwYPNEujV == LMZPkUOHZd){MkFremAPMR = true;}
      else if(LMZPkUOHZd == KFwYPNEujV){hAUWrupfyi = true;}
      if(fiPwcRYnQq == CbsUGHSaVZ){ucBnbSKeQf = true;}
      else if(CbsUGHSaVZ == fiPwcRYnQq){DyVgTCAmYN = true;}
      if(BdOTzAlWwo == DqMVwirDkI){oAOFPZnErt = true;}
      else if(DqMVwirDkI == BdOTzAlWwo){arZQSKaLmS = true;}
      if(MLAiDkecZc == TXWUruszlD){GaqNRoDGLO = true;}
      if(IQAAjtsSHX == UJQoTRJiEt){dYrrbSnqIH = true;}
      if(QctJOgpcYO == GoiRLUzDSC){zIhzzLVzcF = true;}
      while(TXWUruszlD == MLAiDkecZc){PipVOkaYqy = true;}
      while(UJQoTRJiEt == UJQoTRJiEt){HLteDUhwmL = true;}
      while(GoiRLUzDSC == GoiRLUzDSC){gMASgoaEEg = true;}
      if(bKVRKeFXcL == true){bKVRKeFXcL = false;}
      if(OToSEtZWCd == true){OToSEtZWCd = false;}
      if(ZJzqBeoEJW == true){ZJzqBeoEJW = false;}
      if(uofjaKmzeo == true){uofjaKmzeo = false;}
      if(MkFremAPMR == true){MkFremAPMR = false;}
      if(ucBnbSKeQf == true){ucBnbSKeQf = false;}
      if(oAOFPZnErt == true){oAOFPZnErt = false;}
      if(GaqNRoDGLO == true){GaqNRoDGLO = false;}
      if(dYrrbSnqIH == true){dYrrbSnqIH = false;}
      if(zIhzzLVzcF == true){zIhzzLVzcF = false;}
      if(zwXSLTkmWl == true){zwXSLTkmWl = false;}
      if(OESCBQIWdw == true){OESCBQIWdw = false;}
      if(kwujtxrrNG == true){kwujtxrrNG = false;}
      if(TDcGOhAYgI == true){TDcGOhAYgI = false;}
      if(hAUWrupfyi == true){hAUWrupfyi = false;}
      if(DyVgTCAmYN == true){DyVgTCAmYN = false;}
      if(arZQSKaLmS == true){arZQSKaLmS = false;}
      if(PipVOkaYqy == true){PipVOkaYqy = false;}
      if(HLteDUhwmL == true){HLteDUhwmL = false;}
      if(gMASgoaEEg == true){gMASgoaEEg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DINCKLOSRE
{ 
  void nRXdwOZroh()
  { 
      bool osZgqVNUTD = false;
      bool zfSjMReXmD = false;
      bool cBTtAQddoi = false;
      bool GPTdWBIeuJ = false;
      bool fmDGSfnCnl = false;
      bool dtuIHnYefZ = false;
      bool rifjwjMoNK = false;
      bool IzcdWoxMbT = false;
      bool capDFLUKVh = false;
      bool cdyUQxHSJh = false;
      bool TzocddRRlR = false;
      bool pLDMxQscek = false;
      bool OCSehdAHMZ = false;
      bool geCsAdkMZa = false;
      bool tDYDrQalXA = false;
      bool DenYTQfKuz = false;
      bool dJELkLIJLT = false;
      bool egCDpLcOmR = false;
      bool DOjMVCpdZi = false;
      bool xaRZxjyMSf = false;
      string HZRrgweiDZ;
      string NVllJasjMC;
      string YPfjAQiXMf;
      string jYhAWOVHwm;
      string uDgsSlnfRe;
      string GlktFqshqP;
      string NGWWponkPu;
      string FkmZHUhlQO;
      string cDGhZymnue;
      string UnPgYngKDd;
      string xCQWYVyKlk;
      string JGQcmKAnwr;
      string BzpjZRUGBT;
      string mWilQZmiID;
      string AbBJVNWltO;
      string msNLbyMfwH;
      string AqJSxlXdMN;
      string XQesrYyfNM;
      string tiMlftIWKR;
      string MGmBDIShMj;
      if(HZRrgweiDZ == xCQWYVyKlk){osZgqVNUTD = true;}
      else if(xCQWYVyKlk == HZRrgweiDZ){TzocddRRlR = true;}
      if(NVllJasjMC == JGQcmKAnwr){zfSjMReXmD = true;}
      else if(JGQcmKAnwr == NVllJasjMC){pLDMxQscek = true;}
      if(YPfjAQiXMf == BzpjZRUGBT){cBTtAQddoi = true;}
      else if(BzpjZRUGBT == YPfjAQiXMf){OCSehdAHMZ = true;}
      if(jYhAWOVHwm == mWilQZmiID){GPTdWBIeuJ = true;}
      else if(mWilQZmiID == jYhAWOVHwm){geCsAdkMZa = true;}
      if(uDgsSlnfRe == AbBJVNWltO){fmDGSfnCnl = true;}
      else if(AbBJVNWltO == uDgsSlnfRe){tDYDrQalXA = true;}
      if(GlktFqshqP == msNLbyMfwH){dtuIHnYefZ = true;}
      else if(msNLbyMfwH == GlktFqshqP){DenYTQfKuz = true;}
      if(NGWWponkPu == AqJSxlXdMN){rifjwjMoNK = true;}
      else if(AqJSxlXdMN == NGWWponkPu){dJELkLIJLT = true;}
      if(FkmZHUhlQO == XQesrYyfNM){IzcdWoxMbT = true;}
      if(cDGhZymnue == tiMlftIWKR){capDFLUKVh = true;}
      if(UnPgYngKDd == MGmBDIShMj){cdyUQxHSJh = true;}
      while(XQesrYyfNM == FkmZHUhlQO){egCDpLcOmR = true;}
      while(tiMlftIWKR == tiMlftIWKR){DOjMVCpdZi = true;}
      while(MGmBDIShMj == MGmBDIShMj){xaRZxjyMSf = true;}
      if(osZgqVNUTD == true){osZgqVNUTD = false;}
      if(zfSjMReXmD == true){zfSjMReXmD = false;}
      if(cBTtAQddoi == true){cBTtAQddoi = false;}
      if(GPTdWBIeuJ == true){GPTdWBIeuJ = false;}
      if(fmDGSfnCnl == true){fmDGSfnCnl = false;}
      if(dtuIHnYefZ == true){dtuIHnYefZ = false;}
      if(rifjwjMoNK == true){rifjwjMoNK = false;}
      if(IzcdWoxMbT == true){IzcdWoxMbT = false;}
      if(capDFLUKVh == true){capDFLUKVh = false;}
      if(cdyUQxHSJh == true){cdyUQxHSJh = false;}
      if(TzocddRRlR == true){TzocddRRlR = false;}
      if(pLDMxQscek == true){pLDMxQscek = false;}
      if(OCSehdAHMZ == true){OCSehdAHMZ = false;}
      if(geCsAdkMZa == true){geCsAdkMZa = false;}
      if(tDYDrQalXA == true){tDYDrQalXA = false;}
      if(DenYTQfKuz == true){DenYTQfKuz = false;}
      if(dJELkLIJLT == true){dJELkLIJLT = false;}
      if(egCDpLcOmR == true){egCDpLcOmR = false;}
      if(DOjMVCpdZi == true){DOjMVCpdZi = false;}
      if(xaRZxjyMSf == true){xaRZxjyMSf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LLIAWUBPPL
{ 
  void jPGOLhKtIO()
  { 
      bool JBYlZRFmJX = false;
      bool wVVOxJHwLk = false;
      bool ekrMYlmmDs = false;
      bool ZpuaaWdiHy = false;
      bool IqHmpgMEBt = false;
      bool JgWugXIMNm = false;
      bool dRjPxFaumZ = false;
      bool fXoMbmdFWr = false;
      bool ZhlJjrTztD = false;
      bool NQVUTpHqoj = false;
      bool FRRaNkrJTs = false;
      bool tDpVNwfZfE = false;
      bool laBjLOBTsk = false;
      bool flPllHQKuy = false;
      bool AJfAJKaAGX = false;
      bool KgLjyeQgPz = false;
      bool iXPiNHmDiF = false;
      bool eVegEbuAaA = false;
      bool mBNUayafnG = false;
      bool qiuuObtwmB = false;
      string bGIXtQDRfS;
      string peqyAgqHYf;
      string dxErMIqLpz;
      string CMaxjCJmdk;
      string rYBqRFAftW;
      string rrwCKeBPLl;
      string ZrafQcEtNx;
      string WDcnnEuMaG;
      string IKQTGJQXlF;
      string AtbrKzyUan;
      string AGRxzoOHOF;
      string jnoEcOaGZG;
      string MgIIxcakcn;
      string GZllFBsTUR;
      string uIIfVLEXOu;
      string YquUbTyJzV;
      string NddazJCDyb;
      string VHlHKEXbmk;
      string YDVgPOeQKl;
      string DiTyEQdhfL;
      if(bGIXtQDRfS == AGRxzoOHOF){JBYlZRFmJX = true;}
      else if(AGRxzoOHOF == bGIXtQDRfS){FRRaNkrJTs = true;}
      if(peqyAgqHYf == jnoEcOaGZG){wVVOxJHwLk = true;}
      else if(jnoEcOaGZG == peqyAgqHYf){tDpVNwfZfE = true;}
      if(dxErMIqLpz == MgIIxcakcn){ekrMYlmmDs = true;}
      else if(MgIIxcakcn == dxErMIqLpz){laBjLOBTsk = true;}
      if(CMaxjCJmdk == GZllFBsTUR){ZpuaaWdiHy = true;}
      else if(GZllFBsTUR == CMaxjCJmdk){flPllHQKuy = true;}
      if(rYBqRFAftW == uIIfVLEXOu){IqHmpgMEBt = true;}
      else if(uIIfVLEXOu == rYBqRFAftW){AJfAJKaAGX = true;}
      if(rrwCKeBPLl == YquUbTyJzV){JgWugXIMNm = true;}
      else if(YquUbTyJzV == rrwCKeBPLl){KgLjyeQgPz = true;}
      if(ZrafQcEtNx == NddazJCDyb){dRjPxFaumZ = true;}
      else if(NddazJCDyb == ZrafQcEtNx){iXPiNHmDiF = true;}
      if(WDcnnEuMaG == VHlHKEXbmk){fXoMbmdFWr = true;}
      if(IKQTGJQXlF == YDVgPOeQKl){ZhlJjrTztD = true;}
      if(AtbrKzyUan == DiTyEQdhfL){NQVUTpHqoj = true;}
      while(VHlHKEXbmk == WDcnnEuMaG){eVegEbuAaA = true;}
      while(YDVgPOeQKl == YDVgPOeQKl){mBNUayafnG = true;}
      while(DiTyEQdhfL == DiTyEQdhfL){qiuuObtwmB = true;}
      if(JBYlZRFmJX == true){JBYlZRFmJX = false;}
      if(wVVOxJHwLk == true){wVVOxJHwLk = false;}
      if(ekrMYlmmDs == true){ekrMYlmmDs = false;}
      if(ZpuaaWdiHy == true){ZpuaaWdiHy = false;}
      if(IqHmpgMEBt == true){IqHmpgMEBt = false;}
      if(JgWugXIMNm == true){JgWugXIMNm = false;}
      if(dRjPxFaumZ == true){dRjPxFaumZ = false;}
      if(fXoMbmdFWr == true){fXoMbmdFWr = false;}
      if(ZhlJjrTztD == true){ZhlJjrTztD = false;}
      if(NQVUTpHqoj == true){NQVUTpHqoj = false;}
      if(FRRaNkrJTs == true){FRRaNkrJTs = false;}
      if(tDpVNwfZfE == true){tDpVNwfZfE = false;}
      if(laBjLOBTsk == true){laBjLOBTsk = false;}
      if(flPllHQKuy == true){flPllHQKuy = false;}
      if(AJfAJKaAGX == true){AJfAJKaAGX = false;}
      if(KgLjyeQgPz == true){KgLjyeQgPz = false;}
      if(iXPiNHmDiF == true){iXPiNHmDiF = false;}
      if(eVegEbuAaA == true){eVegEbuAaA = false;}
      if(mBNUayafnG == true){mBNUayafnG = false;}
      if(qiuuObtwmB == true){qiuuObtwmB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OUPXEFKYQF
{ 
  void pJDspDxFLm()
  { 
      bool UBaVfjXQWq = false;
      bool nuCxdsQxjU = false;
      bool CsMcbfgqkt = false;
      bool cRUJZIAoJy = false;
      bool IHBQfVNMmL = false;
      bool iQLsyanxsz = false;
      bool CffbOVasXU = false;
      bool sbnkMtrwxG = false;
      bool STEYLLGaKy = false;
      bool TDuJubbYCJ = false;
      bool uToRSGcZgD = false;
      bool irAmgibGQC = false;
      bool PziZApfdpj = false;
      bool SSsmKyelGE = false;
      bool hftHObCIcM = false;
      bool AUIAtukORc = false;
      bool ayjwkPzMbi = false;
      bool DoALTjFaKY = false;
      bool mXBdjxKsrP = false;
      bool MPUccjuyWy = false;
      string zJHIpnDyPQ;
      string aMRGJTtxZa;
      string ioWirbneKC;
      string NewqpgFGSE;
      string tfkqUsDNCj;
      string HhZHPJmYQO;
      string AXmMCwPZQb;
      string OneVfDEeOy;
      string YZcateEobf;
      string tgoEDWrYoY;
      string ccwZVTCEaL;
      string FHKRoZtMRW;
      string qayjggyZRJ;
      string LepoVucCEa;
      string cANPamWWOc;
      string beHRgBdMrn;
      string UblRAZRUws;
      string xqHptpNiJt;
      string KaLohfXXHT;
      string QQKQFANuOA;
      if(zJHIpnDyPQ == ccwZVTCEaL){UBaVfjXQWq = true;}
      else if(ccwZVTCEaL == zJHIpnDyPQ){uToRSGcZgD = true;}
      if(aMRGJTtxZa == FHKRoZtMRW){nuCxdsQxjU = true;}
      else if(FHKRoZtMRW == aMRGJTtxZa){irAmgibGQC = true;}
      if(ioWirbneKC == qayjggyZRJ){CsMcbfgqkt = true;}
      else if(qayjggyZRJ == ioWirbneKC){PziZApfdpj = true;}
      if(NewqpgFGSE == LepoVucCEa){cRUJZIAoJy = true;}
      else if(LepoVucCEa == NewqpgFGSE){SSsmKyelGE = true;}
      if(tfkqUsDNCj == cANPamWWOc){IHBQfVNMmL = true;}
      else if(cANPamWWOc == tfkqUsDNCj){hftHObCIcM = true;}
      if(HhZHPJmYQO == beHRgBdMrn){iQLsyanxsz = true;}
      else if(beHRgBdMrn == HhZHPJmYQO){AUIAtukORc = true;}
      if(AXmMCwPZQb == UblRAZRUws){CffbOVasXU = true;}
      else if(UblRAZRUws == AXmMCwPZQb){ayjwkPzMbi = true;}
      if(OneVfDEeOy == xqHptpNiJt){sbnkMtrwxG = true;}
      if(YZcateEobf == KaLohfXXHT){STEYLLGaKy = true;}
      if(tgoEDWrYoY == QQKQFANuOA){TDuJubbYCJ = true;}
      while(xqHptpNiJt == OneVfDEeOy){DoALTjFaKY = true;}
      while(KaLohfXXHT == KaLohfXXHT){mXBdjxKsrP = true;}
      while(QQKQFANuOA == QQKQFANuOA){MPUccjuyWy = true;}
      if(UBaVfjXQWq == true){UBaVfjXQWq = false;}
      if(nuCxdsQxjU == true){nuCxdsQxjU = false;}
      if(CsMcbfgqkt == true){CsMcbfgqkt = false;}
      if(cRUJZIAoJy == true){cRUJZIAoJy = false;}
      if(IHBQfVNMmL == true){IHBQfVNMmL = false;}
      if(iQLsyanxsz == true){iQLsyanxsz = false;}
      if(CffbOVasXU == true){CffbOVasXU = false;}
      if(sbnkMtrwxG == true){sbnkMtrwxG = false;}
      if(STEYLLGaKy == true){STEYLLGaKy = false;}
      if(TDuJubbYCJ == true){TDuJubbYCJ = false;}
      if(uToRSGcZgD == true){uToRSGcZgD = false;}
      if(irAmgibGQC == true){irAmgibGQC = false;}
      if(PziZApfdpj == true){PziZApfdpj = false;}
      if(SSsmKyelGE == true){SSsmKyelGE = false;}
      if(hftHObCIcM == true){hftHObCIcM = false;}
      if(AUIAtukORc == true){AUIAtukORc = false;}
      if(ayjwkPzMbi == true){ayjwkPzMbi = false;}
      if(DoALTjFaKY == true){DoALTjFaKY = false;}
      if(mXBdjxKsrP == true){mXBdjxKsrP = false;}
      if(MPUccjuyWy == true){MPUccjuyWy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDIECHJFVW
{ 
  void hAtxpgiYDP()
  { 
      bool AOLceokZVY = false;
      bool gbUsXWDKqJ = false;
      bool GjmDgVQMUQ = false;
      bool fiKzDXBHUV = false;
      bool TbxwIdrirg = false;
      bool dCjrBQbHuJ = false;
      bool YYEFryQVpA = false;
      bool VwpUpempuD = false;
      bool dhUnldySxl = false;
      bool wtLLxuWqDK = false;
      bool MVrrLhMPBW = false;
      bool dkMreqDPSO = false;
      bool AyXDDajdXt = false;
      bool HulkpHoccE = false;
      bool QiRZILgSfF = false;
      bool qGYoJOyonj = false;
      bool xhqGPiybBX = false;
      bool BamNxRfxuq = false;
      bool tQyRDAVxab = false;
      bool JAnrGiqKKZ = false;
      string ANpAQHhCxY;
      string smHrMOTtHw;
      string NeuWLRpkyr;
      string tbVatLkVxE;
      string zYRSAxBzFz;
      string BkctYVSSoz;
      string QxEEdQQgxA;
      string dyxDwoMbWN;
      string QqeyqJybBY;
      string sSfynBUMoj;
      string fUBEVCmZxj;
      string IpuahYSFNU;
      string RoeYHKRzOt;
      string UAmmgupZbn;
      string VYeRQDWFPO;
      string iOyURqocxL;
      string jnLCPHCIsm;
      string iscYysKNHD;
      string mMjALFBSUp;
      string FMbQEhMbCI;
      if(ANpAQHhCxY == fUBEVCmZxj){AOLceokZVY = true;}
      else if(fUBEVCmZxj == ANpAQHhCxY){MVrrLhMPBW = true;}
      if(smHrMOTtHw == IpuahYSFNU){gbUsXWDKqJ = true;}
      else if(IpuahYSFNU == smHrMOTtHw){dkMreqDPSO = true;}
      if(NeuWLRpkyr == RoeYHKRzOt){GjmDgVQMUQ = true;}
      else if(RoeYHKRzOt == NeuWLRpkyr){AyXDDajdXt = true;}
      if(tbVatLkVxE == UAmmgupZbn){fiKzDXBHUV = true;}
      else if(UAmmgupZbn == tbVatLkVxE){HulkpHoccE = true;}
      if(zYRSAxBzFz == VYeRQDWFPO){TbxwIdrirg = true;}
      else if(VYeRQDWFPO == zYRSAxBzFz){QiRZILgSfF = true;}
      if(BkctYVSSoz == iOyURqocxL){dCjrBQbHuJ = true;}
      else if(iOyURqocxL == BkctYVSSoz){qGYoJOyonj = true;}
      if(QxEEdQQgxA == jnLCPHCIsm){YYEFryQVpA = true;}
      else if(jnLCPHCIsm == QxEEdQQgxA){xhqGPiybBX = true;}
      if(dyxDwoMbWN == iscYysKNHD){VwpUpempuD = true;}
      if(QqeyqJybBY == mMjALFBSUp){dhUnldySxl = true;}
      if(sSfynBUMoj == FMbQEhMbCI){wtLLxuWqDK = true;}
      while(iscYysKNHD == dyxDwoMbWN){BamNxRfxuq = true;}
      while(mMjALFBSUp == mMjALFBSUp){tQyRDAVxab = true;}
      while(FMbQEhMbCI == FMbQEhMbCI){JAnrGiqKKZ = true;}
      if(AOLceokZVY == true){AOLceokZVY = false;}
      if(gbUsXWDKqJ == true){gbUsXWDKqJ = false;}
      if(GjmDgVQMUQ == true){GjmDgVQMUQ = false;}
      if(fiKzDXBHUV == true){fiKzDXBHUV = false;}
      if(TbxwIdrirg == true){TbxwIdrirg = false;}
      if(dCjrBQbHuJ == true){dCjrBQbHuJ = false;}
      if(YYEFryQVpA == true){YYEFryQVpA = false;}
      if(VwpUpempuD == true){VwpUpempuD = false;}
      if(dhUnldySxl == true){dhUnldySxl = false;}
      if(wtLLxuWqDK == true){wtLLxuWqDK = false;}
      if(MVrrLhMPBW == true){MVrrLhMPBW = false;}
      if(dkMreqDPSO == true){dkMreqDPSO = false;}
      if(AyXDDajdXt == true){AyXDDajdXt = false;}
      if(HulkpHoccE == true){HulkpHoccE = false;}
      if(QiRZILgSfF == true){QiRZILgSfF = false;}
      if(qGYoJOyonj == true){qGYoJOyonj = false;}
      if(xhqGPiybBX == true){xhqGPiybBX = false;}
      if(BamNxRfxuq == true){BamNxRfxuq = false;}
      if(tQyRDAVxab == true){tQyRDAVxab = false;}
      if(JAnrGiqKKZ == true){JAnrGiqKKZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VVHKVLVKQV
{ 
  void exFSIFbnTB()
  { 
      bool qNgcOSOKTS = false;
      bool skogWoYfll = false;
      bool VwHDEMOlZL = false;
      bool sKWKjnkeci = false;
      bool BGBtaeeeLx = false;
      bool WeeCitFcYB = false;
      bool EbjIZhOexh = false;
      bool DtDDkOtNcY = false;
      bool hiacoNeUao = false;
      bool iHFaeZWsTr = false;
      bool QzgctbabRU = false;
      bool zrAzTUAHSM = false;
      bool CtDIzwncXK = false;
      bool qBsjIhCyhM = false;
      bool lDDGopGGGJ = false;
      bool YPZHoVuYcx = false;
      bool myDGcyzQpl = false;
      bool SCYFZzqxTJ = false;
      bool ohVOlbbktl = false;
      bool ldVkZmAwcp = false;
      string gqshNeXKfn;
      string ZtGxGWQSoj;
      string ZiSpaOiOKx;
      string orRISxtZfz;
      string yMOJrgzsBo;
      string WZzXOxXDHy;
      string wIziygcxdJ;
      string cpmolMUIxt;
      string PoMVaOsstU;
      string YpSgCoNfKL;
      string EBOrMfmJlC;
      string bPGNiHudIi;
      string niDJjlXFlw;
      string zoxkoNZUIt;
      string biHqsJiFyu;
      string tiXbXUxFIZ;
      string HgWoCmRVXU;
      string gaUNHEbLPa;
      string CSHqCPQVNT;
      string QUMimuLRoF;
      if(gqshNeXKfn == EBOrMfmJlC){qNgcOSOKTS = true;}
      else if(EBOrMfmJlC == gqshNeXKfn){QzgctbabRU = true;}
      if(ZtGxGWQSoj == bPGNiHudIi){skogWoYfll = true;}
      else if(bPGNiHudIi == ZtGxGWQSoj){zrAzTUAHSM = true;}
      if(ZiSpaOiOKx == niDJjlXFlw){VwHDEMOlZL = true;}
      else if(niDJjlXFlw == ZiSpaOiOKx){CtDIzwncXK = true;}
      if(orRISxtZfz == zoxkoNZUIt){sKWKjnkeci = true;}
      else if(zoxkoNZUIt == orRISxtZfz){qBsjIhCyhM = true;}
      if(yMOJrgzsBo == biHqsJiFyu){BGBtaeeeLx = true;}
      else if(biHqsJiFyu == yMOJrgzsBo){lDDGopGGGJ = true;}
      if(WZzXOxXDHy == tiXbXUxFIZ){WeeCitFcYB = true;}
      else if(tiXbXUxFIZ == WZzXOxXDHy){YPZHoVuYcx = true;}
      if(wIziygcxdJ == HgWoCmRVXU){EbjIZhOexh = true;}
      else if(HgWoCmRVXU == wIziygcxdJ){myDGcyzQpl = true;}
      if(cpmolMUIxt == gaUNHEbLPa){DtDDkOtNcY = true;}
      if(PoMVaOsstU == CSHqCPQVNT){hiacoNeUao = true;}
      if(YpSgCoNfKL == QUMimuLRoF){iHFaeZWsTr = true;}
      while(gaUNHEbLPa == cpmolMUIxt){SCYFZzqxTJ = true;}
      while(CSHqCPQVNT == CSHqCPQVNT){ohVOlbbktl = true;}
      while(QUMimuLRoF == QUMimuLRoF){ldVkZmAwcp = true;}
      if(qNgcOSOKTS == true){qNgcOSOKTS = false;}
      if(skogWoYfll == true){skogWoYfll = false;}
      if(VwHDEMOlZL == true){VwHDEMOlZL = false;}
      if(sKWKjnkeci == true){sKWKjnkeci = false;}
      if(BGBtaeeeLx == true){BGBtaeeeLx = false;}
      if(WeeCitFcYB == true){WeeCitFcYB = false;}
      if(EbjIZhOexh == true){EbjIZhOexh = false;}
      if(DtDDkOtNcY == true){DtDDkOtNcY = false;}
      if(hiacoNeUao == true){hiacoNeUao = false;}
      if(iHFaeZWsTr == true){iHFaeZWsTr = false;}
      if(QzgctbabRU == true){QzgctbabRU = false;}
      if(zrAzTUAHSM == true){zrAzTUAHSM = false;}
      if(CtDIzwncXK == true){CtDIzwncXK = false;}
      if(qBsjIhCyhM == true){qBsjIhCyhM = false;}
      if(lDDGopGGGJ == true){lDDGopGGGJ = false;}
      if(YPZHoVuYcx == true){YPZHoVuYcx = false;}
      if(myDGcyzQpl == true){myDGcyzQpl = false;}
      if(SCYFZzqxTJ == true){SCYFZzqxTJ = false;}
      if(ohVOlbbktl == true){ohVOlbbktl = false;}
      if(ldVkZmAwcp == true){ldVkZmAwcp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JMMKUMLZUG
{ 
  void MprcQQtAgl()
  { 
      bool YalGkUMftY = false;
      bool QDSGoaxOzr = false;
      bool doLQKWPKQd = false;
      bool cGActpeAAI = false;
      bool FFACBskpBh = false;
      bool WFqcViOUuO = false;
      bool EBPPwKDpLz = false;
      bool wxOqmYoJPR = false;
      bool kZIhHWOXHK = false;
      bool aJEkEDojGp = false;
      bool pudCkZqAow = false;
      bool tFEdcergIY = false;
      bool wehBXmrcli = false;
      bool iFDZapuGwg = false;
      bool fOhKQVEaIY = false;
      bool KHagtKNcey = false;
      bool gONGNoCeCl = false;
      bool jljbsgxWjB = false;
      bool hQUNYadVfQ = false;
      bool cRayzQAbxb = false;
      string xfoCVLDwsQ;
      string pLZWYLojqN;
      string uOAOXsupJk;
      string pEhEGNbPUE;
      string gBosaKwFOW;
      string EokWihfadb;
      string QMmHZkdVQK;
      string iYOlftZHnN;
      string xobmgATLUX;
      string hBlsnTOgSo;
      string gaoDneaypo;
      string IYmQeakAaY;
      string RRBrcgmVyM;
      string ernygWAXyB;
      string ZUUePJOVOM;
      string hNGsWOZwaH;
      string rEAdJPjniH;
      string aNBZzxxVcT;
      string RQGldRltbR;
      string xExqIUTqUz;
      if(xfoCVLDwsQ == gaoDneaypo){YalGkUMftY = true;}
      else if(gaoDneaypo == xfoCVLDwsQ){pudCkZqAow = true;}
      if(pLZWYLojqN == IYmQeakAaY){QDSGoaxOzr = true;}
      else if(IYmQeakAaY == pLZWYLojqN){tFEdcergIY = true;}
      if(uOAOXsupJk == RRBrcgmVyM){doLQKWPKQd = true;}
      else if(RRBrcgmVyM == uOAOXsupJk){wehBXmrcli = true;}
      if(pEhEGNbPUE == ernygWAXyB){cGActpeAAI = true;}
      else if(ernygWAXyB == pEhEGNbPUE){iFDZapuGwg = true;}
      if(gBosaKwFOW == ZUUePJOVOM){FFACBskpBh = true;}
      else if(ZUUePJOVOM == gBosaKwFOW){fOhKQVEaIY = true;}
      if(EokWihfadb == hNGsWOZwaH){WFqcViOUuO = true;}
      else if(hNGsWOZwaH == EokWihfadb){KHagtKNcey = true;}
      if(QMmHZkdVQK == rEAdJPjniH){EBPPwKDpLz = true;}
      else if(rEAdJPjniH == QMmHZkdVQK){gONGNoCeCl = true;}
      if(iYOlftZHnN == aNBZzxxVcT){wxOqmYoJPR = true;}
      if(xobmgATLUX == RQGldRltbR){kZIhHWOXHK = true;}
      if(hBlsnTOgSo == xExqIUTqUz){aJEkEDojGp = true;}
      while(aNBZzxxVcT == iYOlftZHnN){jljbsgxWjB = true;}
      while(RQGldRltbR == RQGldRltbR){hQUNYadVfQ = true;}
      while(xExqIUTqUz == xExqIUTqUz){cRayzQAbxb = true;}
      if(YalGkUMftY == true){YalGkUMftY = false;}
      if(QDSGoaxOzr == true){QDSGoaxOzr = false;}
      if(doLQKWPKQd == true){doLQKWPKQd = false;}
      if(cGActpeAAI == true){cGActpeAAI = false;}
      if(FFACBskpBh == true){FFACBskpBh = false;}
      if(WFqcViOUuO == true){WFqcViOUuO = false;}
      if(EBPPwKDpLz == true){EBPPwKDpLz = false;}
      if(wxOqmYoJPR == true){wxOqmYoJPR = false;}
      if(kZIhHWOXHK == true){kZIhHWOXHK = false;}
      if(aJEkEDojGp == true){aJEkEDojGp = false;}
      if(pudCkZqAow == true){pudCkZqAow = false;}
      if(tFEdcergIY == true){tFEdcergIY = false;}
      if(wehBXmrcli == true){wehBXmrcli = false;}
      if(iFDZapuGwg == true){iFDZapuGwg = false;}
      if(fOhKQVEaIY == true){fOhKQVEaIY = false;}
      if(KHagtKNcey == true){KHagtKNcey = false;}
      if(gONGNoCeCl == true){gONGNoCeCl = false;}
      if(jljbsgxWjB == true){jljbsgxWjB = false;}
      if(hQUNYadVfQ == true){hQUNYadVfQ = false;}
      if(cRayzQAbxb == true){cRayzQAbxb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CJEOWVTFEM
{ 
  void ItMBbwurVf()
  { 
      bool mcckuEfXzw = false;
      bool xIWQzzgMZp = false;
      bool kNGVdtKMaa = false;
      bool uxMHgRTUzn = false;
      bool EreqXSRhSs = false;
      bool jHhylYVHGA = false;
      bool sTwXBzuOih = false;
      bool fLMlksiOxK = false;
      bool ccshqnPNVH = false;
      bool uLNztkwGpY = false;
      bool WDykNYuwMr = false;
      bool pHJwXPZNgM = false;
      bool jhsblTxNqA = false;
      bool xcYYnYeHTR = false;
      bool sSAcRnCRae = false;
      bool KhYcooKWzs = false;
      bool agFMuNijIy = false;
      bool kStOTQgPJx = false;
      bool RelMpPDujy = false;
      bool OIIapLNnhE = false;
      string AIGtCPJxkp;
      string UNNoKIIXJe;
      string WeiGWuqwcV;
      string FVhJCRUHpd;
      string SWTYCOfscC;
      string QRMjWUYAWG;
      string XMTPkzeElr;
      string nBgfLzLKDH;
      string OxTaEnIylh;
      string sUjiFGDDnC;
      string jbGjNOjgXW;
      string JOwPrarrKw;
      string pgREzTRxZF;
      string wHVAXlqiNp;
      string DaaPYeXUqe;
      string NLrrMDKCkt;
      string wmHRaBruqF;
      string iJeUrPFBeT;
      string uxGurkPdnU;
      string boySsQTIoX;
      if(AIGtCPJxkp == jbGjNOjgXW){mcckuEfXzw = true;}
      else if(jbGjNOjgXW == AIGtCPJxkp){WDykNYuwMr = true;}
      if(UNNoKIIXJe == JOwPrarrKw){xIWQzzgMZp = true;}
      else if(JOwPrarrKw == UNNoKIIXJe){pHJwXPZNgM = true;}
      if(WeiGWuqwcV == pgREzTRxZF){kNGVdtKMaa = true;}
      else if(pgREzTRxZF == WeiGWuqwcV){jhsblTxNqA = true;}
      if(FVhJCRUHpd == wHVAXlqiNp){uxMHgRTUzn = true;}
      else if(wHVAXlqiNp == FVhJCRUHpd){xcYYnYeHTR = true;}
      if(SWTYCOfscC == DaaPYeXUqe){EreqXSRhSs = true;}
      else if(DaaPYeXUqe == SWTYCOfscC){sSAcRnCRae = true;}
      if(QRMjWUYAWG == NLrrMDKCkt){jHhylYVHGA = true;}
      else if(NLrrMDKCkt == QRMjWUYAWG){KhYcooKWzs = true;}
      if(XMTPkzeElr == wmHRaBruqF){sTwXBzuOih = true;}
      else if(wmHRaBruqF == XMTPkzeElr){agFMuNijIy = true;}
      if(nBgfLzLKDH == iJeUrPFBeT){fLMlksiOxK = true;}
      if(OxTaEnIylh == uxGurkPdnU){ccshqnPNVH = true;}
      if(sUjiFGDDnC == boySsQTIoX){uLNztkwGpY = true;}
      while(iJeUrPFBeT == nBgfLzLKDH){kStOTQgPJx = true;}
      while(uxGurkPdnU == uxGurkPdnU){RelMpPDujy = true;}
      while(boySsQTIoX == boySsQTIoX){OIIapLNnhE = true;}
      if(mcckuEfXzw == true){mcckuEfXzw = false;}
      if(xIWQzzgMZp == true){xIWQzzgMZp = false;}
      if(kNGVdtKMaa == true){kNGVdtKMaa = false;}
      if(uxMHgRTUzn == true){uxMHgRTUzn = false;}
      if(EreqXSRhSs == true){EreqXSRhSs = false;}
      if(jHhylYVHGA == true){jHhylYVHGA = false;}
      if(sTwXBzuOih == true){sTwXBzuOih = false;}
      if(fLMlksiOxK == true){fLMlksiOxK = false;}
      if(ccshqnPNVH == true){ccshqnPNVH = false;}
      if(uLNztkwGpY == true){uLNztkwGpY = false;}
      if(WDykNYuwMr == true){WDykNYuwMr = false;}
      if(pHJwXPZNgM == true){pHJwXPZNgM = false;}
      if(jhsblTxNqA == true){jhsblTxNqA = false;}
      if(xcYYnYeHTR == true){xcYYnYeHTR = false;}
      if(sSAcRnCRae == true){sSAcRnCRae = false;}
      if(KhYcooKWzs == true){KhYcooKWzs = false;}
      if(agFMuNijIy == true){agFMuNijIy = false;}
      if(kStOTQgPJx == true){kStOTQgPJx = false;}
      if(RelMpPDujy == true){RelMpPDujy = false;}
      if(OIIapLNnhE == true){OIIapLNnhE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FVQWOUBCCC
{ 
  void TSPPsSUxco()
  { 
      bool dlobzHmhdK = false;
      bool SmqKyTITiJ = false;
      bool ZmYtGuDrHe = false;
      bool UxABzitdbK = false;
      bool bimYGYNJLa = false;
      bool OAOtdpNtUD = false;
      bool EtZyoVlpKP = false;
      bool ZdrYhpAznh = false;
      bool hsggQTiGWJ = false;
      bool UzJXFgIoik = false;
      bool lWzwAkIoLn = false;
      bool pNFlUKNsgU = false;
      bool lfTBtZUUSB = false;
      bool gKQDwKtjfe = false;
      bool LsthSHsWCt = false;
      bool SPHOyFDyCZ = false;
      bool QmVKHfxCoK = false;
      bool QcNCJrlkhl = false;
      bool fxRYhRCBFq = false;
      bool HwhGOXWial = false;
      string ysZDqiwwxR;
      string huHFBUigiG;
      string ASZrxqhHzC;
      string enDRSETXPD;
      string yVgHBAOjyk;
      string HeBFJeThFz;
      string Anwumtqomx;
      string AKQeHelRqx;
      string cyIOtzmxHm;
      string kkRQDKYkTH;
      string IYwAjwNWye;
      string rBqIVCehAn;
      string GtgzMPrAax;
      string FBxinDBIey;
      string kQyctitJtA;
      string epjfAOqwnT;
      string DNuBYqEHUS;
      string AWDCCpuEEd;
      string ViFaRORQiZ;
      string LFTKtWUxDD;
      if(ysZDqiwwxR == IYwAjwNWye){dlobzHmhdK = true;}
      else if(IYwAjwNWye == ysZDqiwwxR){lWzwAkIoLn = true;}
      if(huHFBUigiG == rBqIVCehAn){SmqKyTITiJ = true;}
      else if(rBqIVCehAn == huHFBUigiG){pNFlUKNsgU = true;}
      if(ASZrxqhHzC == GtgzMPrAax){ZmYtGuDrHe = true;}
      else if(GtgzMPrAax == ASZrxqhHzC){lfTBtZUUSB = true;}
      if(enDRSETXPD == FBxinDBIey){UxABzitdbK = true;}
      else if(FBxinDBIey == enDRSETXPD){gKQDwKtjfe = true;}
      if(yVgHBAOjyk == kQyctitJtA){bimYGYNJLa = true;}
      else if(kQyctitJtA == yVgHBAOjyk){LsthSHsWCt = true;}
      if(HeBFJeThFz == epjfAOqwnT){OAOtdpNtUD = true;}
      else if(epjfAOqwnT == HeBFJeThFz){SPHOyFDyCZ = true;}
      if(Anwumtqomx == DNuBYqEHUS){EtZyoVlpKP = true;}
      else if(DNuBYqEHUS == Anwumtqomx){QmVKHfxCoK = true;}
      if(AKQeHelRqx == AWDCCpuEEd){ZdrYhpAznh = true;}
      if(cyIOtzmxHm == ViFaRORQiZ){hsggQTiGWJ = true;}
      if(kkRQDKYkTH == LFTKtWUxDD){UzJXFgIoik = true;}
      while(AWDCCpuEEd == AKQeHelRqx){QcNCJrlkhl = true;}
      while(ViFaRORQiZ == ViFaRORQiZ){fxRYhRCBFq = true;}
      while(LFTKtWUxDD == LFTKtWUxDD){HwhGOXWial = true;}
      if(dlobzHmhdK == true){dlobzHmhdK = false;}
      if(SmqKyTITiJ == true){SmqKyTITiJ = false;}
      if(ZmYtGuDrHe == true){ZmYtGuDrHe = false;}
      if(UxABzitdbK == true){UxABzitdbK = false;}
      if(bimYGYNJLa == true){bimYGYNJLa = false;}
      if(OAOtdpNtUD == true){OAOtdpNtUD = false;}
      if(EtZyoVlpKP == true){EtZyoVlpKP = false;}
      if(ZdrYhpAznh == true){ZdrYhpAznh = false;}
      if(hsggQTiGWJ == true){hsggQTiGWJ = false;}
      if(UzJXFgIoik == true){UzJXFgIoik = false;}
      if(lWzwAkIoLn == true){lWzwAkIoLn = false;}
      if(pNFlUKNsgU == true){pNFlUKNsgU = false;}
      if(lfTBtZUUSB == true){lfTBtZUUSB = false;}
      if(gKQDwKtjfe == true){gKQDwKtjfe = false;}
      if(LsthSHsWCt == true){LsthSHsWCt = false;}
      if(SPHOyFDyCZ == true){SPHOyFDyCZ = false;}
      if(QmVKHfxCoK == true){QmVKHfxCoK = false;}
      if(QcNCJrlkhl == true){QcNCJrlkhl = false;}
      if(fxRYhRCBFq == true){fxRYhRCBFq = false;}
      if(HwhGOXWial == true){HwhGOXWial = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KPWZJNNDNP
{ 
  void UFxXLCPJkF()
  { 
      bool BfDshdaOsZ = false;
      bool AWAHgWfZUq = false;
      bool mqBsfqtxZA = false;
      bool AfMskUiYHW = false;
      bool EhJWgkqOlB = false;
      bool IKuoAKeKNp = false;
      bool jdnrYUKGVL = false;
      bool mGRymEgdMt = false;
      bool zfLYrojWsa = false;
      bool pYLQmZtRxL = false;
      bool akraNBrxCw = false;
      bool cAxSqDSOAi = false;
      bool jmNuVOuBLM = false;
      bool KPgATOnjLq = false;
      bool wmUwxoarZi = false;
      bool HeQNbmWwEy = false;
      bool FqlpkNTxyb = false;
      bool OhDJlxSRyg = false;
      bool mDabEfzSYg = false;
      bool rrfMkFAeKj = false;
      string mmaFauHZgt;
      string zjMkIFJhnZ;
      string ZoPQkhWgqp;
      string gltWOyrFmC;
      string BrkVLWAImb;
      string ftLoaxXJUs;
      string YZhqNNopVJ;
      string NDulXgDsFN;
      string gNsPKlZEuQ;
      string ahktdbKtIy;
      string hJmcNbzYRs;
      string seEGLKgSga;
      string mjtEieRAIw;
      string WJjHfXaPBh;
      string lBmCXwdehS;
      string trMgKyPhth;
      string JyPVVjtxan;
      string jQQynkxrgm;
      string BmSpBewCwg;
      string IrVSXnkQfm;
      if(mmaFauHZgt == hJmcNbzYRs){BfDshdaOsZ = true;}
      else if(hJmcNbzYRs == mmaFauHZgt){akraNBrxCw = true;}
      if(zjMkIFJhnZ == seEGLKgSga){AWAHgWfZUq = true;}
      else if(seEGLKgSga == zjMkIFJhnZ){cAxSqDSOAi = true;}
      if(ZoPQkhWgqp == mjtEieRAIw){mqBsfqtxZA = true;}
      else if(mjtEieRAIw == ZoPQkhWgqp){jmNuVOuBLM = true;}
      if(gltWOyrFmC == WJjHfXaPBh){AfMskUiYHW = true;}
      else if(WJjHfXaPBh == gltWOyrFmC){KPgATOnjLq = true;}
      if(BrkVLWAImb == lBmCXwdehS){EhJWgkqOlB = true;}
      else if(lBmCXwdehS == BrkVLWAImb){wmUwxoarZi = true;}
      if(ftLoaxXJUs == trMgKyPhth){IKuoAKeKNp = true;}
      else if(trMgKyPhth == ftLoaxXJUs){HeQNbmWwEy = true;}
      if(YZhqNNopVJ == JyPVVjtxan){jdnrYUKGVL = true;}
      else if(JyPVVjtxan == YZhqNNopVJ){FqlpkNTxyb = true;}
      if(NDulXgDsFN == jQQynkxrgm){mGRymEgdMt = true;}
      if(gNsPKlZEuQ == BmSpBewCwg){zfLYrojWsa = true;}
      if(ahktdbKtIy == IrVSXnkQfm){pYLQmZtRxL = true;}
      while(jQQynkxrgm == NDulXgDsFN){OhDJlxSRyg = true;}
      while(BmSpBewCwg == BmSpBewCwg){mDabEfzSYg = true;}
      while(IrVSXnkQfm == IrVSXnkQfm){rrfMkFAeKj = true;}
      if(BfDshdaOsZ == true){BfDshdaOsZ = false;}
      if(AWAHgWfZUq == true){AWAHgWfZUq = false;}
      if(mqBsfqtxZA == true){mqBsfqtxZA = false;}
      if(AfMskUiYHW == true){AfMskUiYHW = false;}
      if(EhJWgkqOlB == true){EhJWgkqOlB = false;}
      if(IKuoAKeKNp == true){IKuoAKeKNp = false;}
      if(jdnrYUKGVL == true){jdnrYUKGVL = false;}
      if(mGRymEgdMt == true){mGRymEgdMt = false;}
      if(zfLYrojWsa == true){zfLYrojWsa = false;}
      if(pYLQmZtRxL == true){pYLQmZtRxL = false;}
      if(akraNBrxCw == true){akraNBrxCw = false;}
      if(cAxSqDSOAi == true){cAxSqDSOAi = false;}
      if(jmNuVOuBLM == true){jmNuVOuBLM = false;}
      if(KPgATOnjLq == true){KPgATOnjLq = false;}
      if(wmUwxoarZi == true){wmUwxoarZi = false;}
      if(HeQNbmWwEy == true){HeQNbmWwEy = false;}
      if(FqlpkNTxyb == true){FqlpkNTxyb = false;}
      if(OhDJlxSRyg == true){OhDJlxSRyg = false;}
      if(mDabEfzSYg == true){mDabEfzSYg = false;}
      if(rrfMkFAeKj == true){rrfMkFAeKj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JZOIZSICUF
{ 
  void GyQiPofVVr()
  { 
      bool hEWDexSxNT = false;
      bool ilZyVcexRL = false;
      bool CnZgPIAHeB = false;
      bool HBapBVEVqD = false;
      bool CoomPVecAV = false;
      bool QjSecsdpnW = false;
      bool wLSLMhLjwz = false;
      bool YJGOJNzmQs = false;
      bool dXGJjWhwMI = false;
      bool qNgTGqVcag = false;
      bool KtfBwGdEUO = false;
      bool tqYtsYFJao = false;
      bool APWnIKblHS = false;
      bool rVLiiiqFMd = false;
      bool scaxNzomag = false;
      bool lMBlguXqrl = false;
      bool dqwCWXfoKK = false;
      bool gzwxwWnZZI = false;
      bool VoLageUZCn = false;
      bool KAMazBgXap = false;
      string VJBGSCNIUa;
      string QzDRtxTWlX;
      string dwgnZWxdjC;
      string XqQlzGykIN;
      string qRZLYsMGeH;
      string QSGWMZbNgu;
      string FiYRCZiQRn;
      string yhNXgMVVPf;
      string JpzbkFjsZZ;
      string ekENIIsHIy;
      string KwnqJhEipA;
      string DFyBlPjwgx;
      string poqrINdAPY;
      string SNNQUNBISC;
      string ABDYVZmCbs;
      string XxaKIVEwhw;
      string EETRhoqhfX;
      string NaddxolRVi;
      string aaYVAVlCHz;
      string IFaWywgkqf;
      if(VJBGSCNIUa == KwnqJhEipA){hEWDexSxNT = true;}
      else if(KwnqJhEipA == VJBGSCNIUa){KtfBwGdEUO = true;}
      if(QzDRtxTWlX == DFyBlPjwgx){ilZyVcexRL = true;}
      else if(DFyBlPjwgx == QzDRtxTWlX){tqYtsYFJao = true;}
      if(dwgnZWxdjC == poqrINdAPY){CnZgPIAHeB = true;}
      else if(poqrINdAPY == dwgnZWxdjC){APWnIKblHS = true;}
      if(XqQlzGykIN == SNNQUNBISC){HBapBVEVqD = true;}
      else if(SNNQUNBISC == XqQlzGykIN){rVLiiiqFMd = true;}
      if(qRZLYsMGeH == ABDYVZmCbs){CoomPVecAV = true;}
      else if(ABDYVZmCbs == qRZLYsMGeH){scaxNzomag = true;}
      if(QSGWMZbNgu == XxaKIVEwhw){QjSecsdpnW = true;}
      else if(XxaKIVEwhw == QSGWMZbNgu){lMBlguXqrl = true;}
      if(FiYRCZiQRn == EETRhoqhfX){wLSLMhLjwz = true;}
      else if(EETRhoqhfX == FiYRCZiQRn){dqwCWXfoKK = true;}
      if(yhNXgMVVPf == NaddxolRVi){YJGOJNzmQs = true;}
      if(JpzbkFjsZZ == aaYVAVlCHz){dXGJjWhwMI = true;}
      if(ekENIIsHIy == IFaWywgkqf){qNgTGqVcag = true;}
      while(NaddxolRVi == yhNXgMVVPf){gzwxwWnZZI = true;}
      while(aaYVAVlCHz == aaYVAVlCHz){VoLageUZCn = true;}
      while(IFaWywgkqf == IFaWywgkqf){KAMazBgXap = true;}
      if(hEWDexSxNT == true){hEWDexSxNT = false;}
      if(ilZyVcexRL == true){ilZyVcexRL = false;}
      if(CnZgPIAHeB == true){CnZgPIAHeB = false;}
      if(HBapBVEVqD == true){HBapBVEVqD = false;}
      if(CoomPVecAV == true){CoomPVecAV = false;}
      if(QjSecsdpnW == true){QjSecsdpnW = false;}
      if(wLSLMhLjwz == true){wLSLMhLjwz = false;}
      if(YJGOJNzmQs == true){YJGOJNzmQs = false;}
      if(dXGJjWhwMI == true){dXGJjWhwMI = false;}
      if(qNgTGqVcag == true){qNgTGqVcag = false;}
      if(KtfBwGdEUO == true){KtfBwGdEUO = false;}
      if(tqYtsYFJao == true){tqYtsYFJao = false;}
      if(APWnIKblHS == true){APWnIKblHS = false;}
      if(rVLiiiqFMd == true){rVLiiiqFMd = false;}
      if(scaxNzomag == true){scaxNzomag = false;}
      if(lMBlguXqrl == true){lMBlguXqrl = false;}
      if(dqwCWXfoKK == true){dqwCWXfoKK = false;}
      if(gzwxwWnZZI == true){gzwxwWnZZI = false;}
      if(VoLageUZCn == true){VoLageUZCn = false;}
      if(KAMazBgXap == true){KAMazBgXap = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LYCBSSWPRR
{ 
  void ihBkQGEmIc()
  { 
      bool MIgbyBBdEo = false;
      bool opSpJHwyhX = false;
      bool VMNKVZzThU = false;
      bool WZrOJwTaEi = false;
      bool WpjLnqCrPl = false;
      bool hwiXhAuVFX = false;
      bool CgujROyEgM = false;
      bool mVtyBfbCWe = false;
      bool XGEwlapUgI = false;
      bool AxUfgouAsY = false;
      bool syLCyMCkVC = false;
      bool XszaAuczxq = false;
      bool XdWXMpANRM = false;
      bool jbIxlYtCxZ = false;
      bool XFydkHytek = false;
      bool LuCCAOanpI = false;
      bool MnSJRwjBob = false;
      bool BaBWSSfsmE = false;
      bool rGifAoYFxW = false;
      bool yFMoNjloMn = false;
      string baOBKzPtAa;
      string BzuUaLZVDY;
      string WzEOhUmolt;
      string hoxIqfrlmJ;
      string ogobjNxesI;
      string QSsXDcWASo;
      string LZIGsMClct;
      string SnhtjpJbeU;
      string XIuccOwYFO;
      string JqSyxOYiiX;
      string KLByobjynN;
      string StUyQDeecd;
      string PcfOkaUjxU;
      string QasHKMHwmA;
      string exkruOWUgt;
      string jsFEHgelNO;
      string HABSwqBNnE;
      string uhrbzSrnSW;
      string EADCkXUoAc;
      string hViYseuRwE;
      if(baOBKzPtAa == KLByobjynN){MIgbyBBdEo = true;}
      else if(KLByobjynN == baOBKzPtAa){syLCyMCkVC = true;}
      if(BzuUaLZVDY == StUyQDeecd){opSpJHwyhX = true;}
      else if(StUyQDeecd == BzuUaLZVDY){XszaAuczxq = true;}
      if(WzEOhUmolt == PcfOkaUjxU){VMNKVZzThU = true;}
      else if(PcfOkaUjxU == WzEOhUmolt){XdWXMpANRM = true;}
      if(hoxIqfrlmJ == QasHKMHwmA){WZrOJwTaEi = true;}
      else if(QasHKMHwmA == hoxIqfrlmJ){jbIxlYtCxZ = true;}
      if(ogobjNxesI == exkruOWUgt){WpjLnqCrPl = true;}
      else if(exkruOWUgt == ogobjNxesI){XFydkHytek = true;}
      if(QSsXDcWASo == jsFEHgelNO){hwiXhAuVFX = true;}
      else if(jsFEHgelNO == QSsXDcWASo){LuCCAOanpI = true;}
      if(LZIGsMClct == HABSwqBNnE){CgujROyEgM = true;}
      else if(HABSwqBNnE == LZIGsMClct){MnSJRwjBob = true;}
      if(SnhtjpJbeU == uhrbzSrnSW){mVtyBfbCWe = true;}
      if(XIuccOwYFO == EADCkXUoAc){XGEwlapUgI = true;}
      if(JqSyxOYiiX == hViYseuRwE){AxUfgouAsY = true;}
      while(uhrbzSrnSW == SnhtjpJbeU){BaBWSSfsmE = true;}
      while(EADCkXUoAc == EADCkXUoAc){rGifAoYFxW = true;}
      while(hViYseuRwE == hViYseuRwE){yFMoNjloMn = true;}
      if(MIgbyBBdEo == true){MIgbyBBdEo = false;}
      if(opSpJHwyhX == true){opSpJHwyhX = false;}
      if(VMNKVZzThU == true){VMNKVZzThU = false;}
      if(WZrOJwTaEi == true){WZrOJwTaEi = false;}
      if(WpjLnqCrPl == true){WpjLnqCrPl = false;}
      if(hwiXhAuVFX == true){hwiXhAuVFX = false;}
      if(CgujROyEgM == true){CgujROyEgM = false;}
      if(mVtyBfbCWe == true){mVtyBfbCWe = false;}
      if(XGEwlapUgI == true){XGEwlapUgI = false;}
      if(AxUfgouAsY == true){AxUfgouAsY = false;}
      if(syLCyMCkVC == true){syLCyMCkVC = false;}
      if(XszaAuczxq == true){XszaAuczxq = false;}
      if(XdWXMpANRM == true){XdWXMpANRM = false;}
      if(jbIxlYtCxZ == true){jbIxlYtCxZ = false;}
      if(XFydkHytek == true){XFydkHytek = false;}
      if(LuCCAOanpI == true){LuCCAOanpI = false;}
      if(MnSJRwjBob == true){MnSJRwjBob = false;}
      if(BaBWSSfsmE == true){BaBWSSfsmE = false;}
      if(rGifAoYFxW == true){rGifAoYFxW = false;}
      if(yFMoNjloMn == true){yFMoNjloMn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BVEEFJSUOL
{ 
  void kbMGUFTZIV()
  { 
      bool keoiqxZBSQ = false;
      bool TVSPhEpFyT = false;
      bool iWgbAIxcUF = false;
      bool zKclHdUbUq = false;
      bool kLWXgcdUQU = false;
      bool gUrgXOxNii = false;
      bool AxfMQIrfHE = false;
      bool iOjGiWzItX = false;
      bool dbMAYeSuOr = false;
      bool fHrkqmfJHX = false;
      bool jyMLkRjlyB = false;
      bool OoSLEXkenl = false;
      bool pxRPXbVyPw = false;
      bool ppBWmfPAOG = false;
      bool tfxNdpnggT = false;
      bool CBVUglfxmI = false;
      bool ukVCKYnwXY = false;
      bool IjPgqJAEkg = false;
      bool noRwsoTfoB = false;
      bool zRMFKIKuCF = false;
      string gmUgOKzNmM;
      string tEmIKDrKIK;
      string MlHeEHfcDV;
      string oKfBCZqulo;
      string eexWqbxNiM;
      string oTspatfocH;
      string eVJQXiXlFj;
      string LwXSehojnb;
      string KRsqgURpZI;
      string sCSeKJUfzH;
      string ELIzAruZKr;
      string FwBAxNcSjD;
      string RhLwpJcsIV;
      string NJkfXyItpo;
      string ZqegDxAShw;
      string fCwupWALIq;
      string PCRnewLVcy;
      string EhbucZCdss;
      string IKLMoKMooB;
      string ywkzZXZqBG;
      if(gmUgOKzNmM == ELIzAruZKr){keoiqxZBSQ = true;}
      else if(ELIzAruZKr == gmUgOKzNmM){jyMLkRjlyB = true;}
      if(tEmIKDrKIK == FwBAxNcSjD){TVSPhEpFyT = true;}
      else if(FwBAxNcSjD == tEmIKDrKIK){OoSLEXkenl = true;}
      if(MlHeEHfcDV == RhLwpJcsIV){iWgbAIxcUF = true;}
      else if(RhLwpJcsIV == MlHeEHfcDV){pxRPXbVyPw = true;}
      if(oKfBCZqulo == NJkfXyItpo){zKclHdUbUq = true;}
      else if(NJkfXyItpo == oKfBCZqulo){ppBWmfPAOG = true;}
      if(eexWqbxNiM == ZqegDxAShw){kLWXgcdUQU = true;}
      else if(ZqegDxAShw == eexWqbxNiM){tfxNdpnggT = true;}
      if(oTspatfocH == fCwupWALIq){gUrgXOxNii = true;}
      else if(fCwupWALIq == oTspatfocH){CBVUglfxmI = true;}
      if(eVJQXiXlFj == PCRnewLVcy){AxfMQIrfHE = true;}
      else if(PCRnewLVcy == eVJQXiXlFj){ukVCKYnwXY = true;}
      if(LwXSehojnb == EhbucZCdss){iOjGiWzItX = true;}
      if(KRsqgURpZI == IKLMoKMooB){dbMAYeSuOr = true;}
      if(sCSeKJUfzH == ywkzZXZqBG){fHrkqmfJHX = true;}
      while(EhbucZCdss == LwXSehojnb){IjPgqJAEkg = true;}
      while(IKLMoKMooB == IKLMoKMooB){noRwsoTfoB = true;}
      while(ywkzZXZqBG == ywkzZXZqBG){zRMFKIKuCF = true;}
      if(keoiqxZBSQ == true){keoiqxZBSQ = false;}
      if(TVSPhEpFyT == true){TVSPhEpFyT = false;}
      if(iWgbAIxcUF == true){iWgbAIxcUF = false;}
      if(zKclHdUbUq == true){zKclHdUbUq = false;}
      if(kLWXgcdUQU == true){kLWXgcdUQU = false;}
      if(gUrgXOxNii == true){gUrgXOxNii = false;}
      if(AxfMQIrfHE == true){AxfMQIrfHE = false;}
      if(iOjGiWzItX == true){iOjGiWzItX = false;}
      if(dbMAYeSuOr == true){dbMAYeSuOr = false;}
      if(fHrkqmfJHX == true){fHrkqmfJHX = false;}
      if(jyMLkRjlyB == true){jyMLkRjlyB = false;}
      if(OoSLEXkenl == true){OoSLEXkenl = false;}
      if(pxRPXbVyPw == true){pxRPXbVyPw = false;}
      if(ppBWmfPAOG == true){ppBWmfPAOG = false;}
      if(tfxNdpnggT == true){tfxNdpnggT = false;}
      if(CBVUglfxmI == true){CBVUglfxmI = false;}
      if(ukVCKYnwXY == true){ukVCKYnwXY = false;}
      if(IjPgqJAEkg == true){IjPgqJAEkg = false;}
      if(noRwsoTfoB == true){noRwsoTfoB = false;}
      if(zRMFKIKuCF == true){zRMFKIKuCF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VNJEAUAOZI
{ 
  void CpMVtRVLth()
  { 
      bool buRxoSMWsI = false;
      bool WRBFwxgQbF = false;
      bool iTDATCjslM = false;
      bool tuykNRjzOk = false;
      bool rkhfKFeuBA = false;
      bool VGXoZIqQdl = false;
      bool hTkfNbSQrd = false;
      bool MhBqMxlXpO = false;
      bool XnqlqmXJLF = false;
      bool ZTUcCYABRh = false;
      bool lODWmmEfbb = false;
      bool VTZPOsbznZ = false;
      bool EIElDsNYon = false;
      bool xjFHbJkUyE = false;
      bool hqhjiGsFOI = false;
      bool wAMqdcJQTt = false;
      bool ZfqmdlOSmE = false;
      bool IHAjqMaTDx = false;
      bool zHKfrwXNdy = false;
      bool zTAEeCzuFw = false;
      string iOszBCIsMH;
      string EijanCoghJ;
      string cWrlZhTYch;
      string MDrHVYDGgT;
      string SRSAlinxVJ;
      string iPMbfMWHYS;
      string iiQetBpbFO;
      string yizNpKDqzq;
      string tVCSyxpQbJ;
      string CwgNkjBnGk;
      string rLrHLAPykU;
      string IeHhYMfxgx;
      string KZAuMBBlcG;
      string JPjOzhcuHx;
      string greGBWnznY;
      string DDGJZRLwtJ;
      string zdUeLrurhq;
      string ikpjPRusto;
      string NBxEDFIaog;
      string WgAxxCXztI;
      if(iOszBCIsMH == rLrHLAPykU){buRxoSMWsI = true;}
      else if(rLrHLAPykU == iOszBCIsMH){lODWmmEfbb = true;}
      if(EijanCoghJ == IeHhYMfxgx){WRBFwxgQbF = true;}
      else if(IeHhYMfxgx == EijanCoghJ){VTZPOsbznZ = true;}
      if(cWrlZhTYch == KZAuMBBlcG){iTDATCjslM = true;}
      else if(KZAuMBBlcG == cWrlZhTYch){EIElDsNYon = true;}
      if(MDrHVYDGgT == JPjOzhcuHx){tuykNRjzOk = true;}
      else if(JPjOzhcuHx == MDrHVYDGgT){xjFHbJkUyE = true;}
      if(SRSAlinxVJ == greGBWnznY){rkhfKFeuBA = true;}
      else if(greGBWnznY == SRSAlinxVJ){hqhjiGsFOI = true;}
      if(iPMbfMWHYS == DDGJZRLwtJ){VGXoZIqQdl = true;}
      else if(DDGJZRLwtJ == iPMbfMWHYS){wAMqdcJQTt = true;}
      if(iiQetBpbFO == zdUeLrurhq){hTkfNbSQrd = true;}
      else if(zdUeLrurhq == iiQetBpbFO){ZfqmdlOSmE = true;}
      if(yizNpKDqzq == ikpjPRusto){MhBqMxlXpO = true;}
      if(tVCSyxpQbJ == NBxEDFIaog){XnqlqmXJLF = true;}
      if(CwgNkjBnGk == WgAxxCXztI){ZTUcCYABRh = true;}
      while(ikpjPRusto == yizNpKDqzq){IHAjqMaTDx = true;}
      while(NBxEDFIaog == NBxEDFIaog){zHKfrwXNdy = true;}
      while(WgAxxCXztI == WgAxxCXztI){zTAEeCzuFw = true;}
      if(buRxoSMWsI == true){buRxoSMWsI = false;}
      if(WRBFwxgQbF == true){WRBFwxgQbF = false;}
      if(iTDATCjslM == true){iTDATCjslM = false;}
      if(tuykNRjzOk == true){tuykNRjzOk = false;}
      if(rkhfKFeuBA == true){rkhfKFeuBA = false;}
      if(VGXoZIqQdl == true){VGXoZIqQdl = false;}
      if(hTkfNbSQrd == true){hTkfNbSQrd = false;}
      if(MhBqMxlXpO == true){MhBqMxlXpO = false;}
      if(XnqlqmXJLF == true){XnqlqmXJLF = false;}
      if(ZTUcCYABRh == true){ZTUcCYABRh = false;}
      if(lODWmmEfbb == true){lODWmmEfbb = false;}
      if(VTZPOsbznZ == true){VTZPOsbznZ = false;}
      if(EIElDsNYon == true){EIElDsNYon = false;}
      if(xjFHbJkUyE == true){xjFHbJkUyE = false;}
      if(hqhjiGsFOI == true){hqhjiGsFOI = false;}
      if(wAMqdcJQTt == true){wAMqdcJQTt = false;}
      if(ZfqmdlOSmE == true){ZfqmdlOSmE = false;}
      if(IHAjqMaTDx == true){IHAjqMaTDx = false;}
      if(zHKfrwXNdy == true){zHKfrwXNdy = false;}
      if(zTAEeCzuFw == true){zTAEeCzuFw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TPBGNYUTOH
{ 
  void ieUZfdCCnu()
  { 
      bool CQYYAdHPWx = false;
      bool sAmBykORaM = false;
      bool boNAikGtsL = false;
      bool NctjSdeuak = false;
      bool PUiPkUHLIn = false;
      bool rdNzhMCYoO = false;
      bool XNVKiPGCiU = false;
      bool GSqpwGGyON = false;
      bool dukETiPtCF = false;
      bool bGGLMCzYfV = false;
      bool OEcnhYmXCb = false;
      bool GDJakcbQpz = false;
      bool zLAcszMect = false;
      bool HhSrzYSxWt = false;
      bool urrayXweZj = false;
      bool ahhfVCEzuh = false;
      bool MItHTYkRbM = false;
      bool KdtuDHTYdU = false;
      bool ChFrTYzlVw = false;
      bool TSCnhmxjGZ = false;
      string SPzIkWwVmL;
      string jgDicjVwWp;
      string xBeaoQnUkp;
      string ZrAiRWKpiY;
      string czPkzpdOuE;
      string cyARRQjXSU;
      string ibjxkqgTQF;
      string YeNyNyltby;
      string lZYfNaqiQB;
      string mmXNoAOSzH;
      string JJxoexjBDT;
      string eouThICDiJ;
      string AxCPSlHAIM;
      string iTtUocbjBP;
      string qoexVxqDeg;
      string xKioHLGgWs;
      string pjspkLtadF;
      string fSCTSKSFtU;
      string tEUbPXjFMd;
      string VtMHZGwoLJ;
      if(SPzIkWwVmL == JJxoexjBDT){CQYYAdHPWx = true;}
      else if(JJxoexjBDT == SPzIkWwVmL){OEcnhYmXCb = true;}
      if(jgDicjVwWp == eouThICDiJ){sAmBykORaM = true;}
      else if(eouThICDiJ == jgDicjVwWp){GDJakcbQpz = true;}
      if(xBeaoQnUkp == AxCPSlHAIM){boNAikGtsL = true;}
      else if(AxCPSlHAIM == xBeaoQnUkp){zLAcszMect = true;}
      if(ZrAiRWKpiY == iTtUocbjBP){NctjSdeuak = true;}
      else if(iTtUocbjBP == ZrAiRWKpiY){HhSrzYSxWt = true;}
      if(czPkzpdOuE == qoexVxqDeg){PUiPkUHLIn = true;}
      else if(qoexVxqDeg == czPkzpdOuE){urrayXweZj = true;}
      if(cyARRQjXSU == xKioHLGgWs){rdNzhMCYoO = true;}
      else if(xKioHLGgWs == cyARRQjXSU){ahhfVCEzuh = true;}
      if(ibjxkqgTQF == pjspkLtadF){XNVKiPGCiU = true;}
      else if(pjspkLtadF == ibjxkqgTQF){MItHTYkRbM = true;}
      if(YeNyNyltby == fSCTSKSFtU){GSqpwGGyON = true;}
      if(lZYfNaqiQB == tEUbPXjFMd){dukETiPtCF = true;}
      if(mmXNoAOSzH == VtMHZGwoLJ){bGGLMCzYfV = true;}
      while(fSCTSKSFtU == YeNyNyltby){KdtuDHTYdU = true;}
      while(tEUbPXjFMd == tEUbPXjFMd){ChFrTYzlVw = true;}
      while(VtMHZGwoLJ == VtMHZGwoLJ){TSCnhmxjGZ = true;}
      if(CQYYAdHPWx == true){CQYYAdHPWx = false;}
      if(sAmBykORaM == true){sAmBykORaM = false;}
      if(boNAikGtsL == true){boNAikGtsL = false;}
      if(NctjSdeuak == true){NctjSdeuak = false;}
      if(PUiPkUHLIn == true){PUiPkUHLIn = false;}
      if(rdNzhMCYoO == true){rdNzhMCYoO = false;}
      if(XNVKiPGCiU == true){XNVKiPGCiU = false;}
      if(GSqpwGGyON == true){GSqpwGGyON = false;}
      if(dukETiPtCF == true){dukETiPtCF = false;}
      if(bGGLMCzYfV == true){bGGLMCzYfV = false;}
      if(OEcnhYmXCb == true){OEcnhYmXCb = false;}
      if(GDJakcbQpz == true){GDJakcbQpz = false;}
      if(zLAcszMect == true){zLAcszMect = false;}
      if(HhSrzYSxWt == true){HhSrzYSxWt = false;}
      if(urrayXweZj == true){urrayXweZj = false;}
      if(ahhfVCEzuh == true){ahhfVCEzuh = false;}
      if(MItHTYkRbM == true){MItHTYkRbM = false;}
      if(KdtuDHTYdU == true){KdtuDHTYdU = false;}
      if(ChFrTYzlVw == true){ChFrTYzlVw = false;}
      if(TSCnhmxjGZ == true){TSCnhmxjGZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VUUIAZRRCD
{ 
  void AHDVlYWwcU()
  { 
      bool wNHMKpNxby = false;
      bool yWBicqdxCI = false;
      bool gbAgtgpjCp = false;
      bool XGIVYldgpc = false;
      bool GiliNwdDRW = false;
      bool pgrHKUMZSc = false;
      bool zctkarOfKp = false;
      bool NwGYBxoRTx = false;
      bool CmRfzpOALD = false;
      bool YDOMddnAIU = false;
      bool gysaJtZSFM = false;
      bool fuGUZLLNkj = false;
      bool dNTGRJhttX = false;
      bool JnIyQEtpWF = false;
      bool QutyXdwslS = false;
      bool SaPYpTdlJz = false;
      bool MeXhDqmIEV = false;
      bool QUqfSiSVin = false;
      bool NnHbFiYjHw = false;
      bool ZIgXskWMtf = false;
      string TsjPsdMcam;
      string ttiHmtfbZb;
      string ByPKhpotdM;
      string AVEgeElmFU;
      string EsibBFOKsg;
      string GPZfyUdYgD;
      string nSyNmYoBbh;
      string IrWEXHPnJb;
      string beAwFkwYiJ;
      string aMFCgkuVnb;
      string QMhKYOrUIp;
      string FoPFbJSCHC;
      string cQRRGwlUXl;
      string MszgLOwpXq;
      string raQsElwAZW;
      string SrNlzzuPDc;
      string cXxVcMohsN;
      string MceQKBAXNU;
      string zktATUfNhM;
      string SfltNTdtPq;
      if(TsjPsdMcam == QMhKYOrUIp){wNHMKpNxby = true;}
      else if(QMhKYOrUIp == TsjPsdMcam){gysaJtZSFM = true;}
      if(ttiHmtfbZb == FoPFbJSCHC){yWBicqdxCI = true;}
      else if(FoPFbJSCHC == ttiHmtfbZb){fuGUZLLNkj = true;}
      if(ByPKhpotdM == cQRRGwlUXl){gbAgtgpjCp = true;}
      else if(cQRRGwlUXl == ByPKhpotdM){dNTGRJhttX = true;}
      if(AVEgeElmFU == MszgLOwpXq){XGIVYldgpc = true;}
      else if(MszgLOwpXq == AVEgeElmFU){JnIyQEtpWF = true;}
      if(EsibBFOKsg == raQsElwAZW){GiliNwdDRW = true;}
      else if(raQsElwAZW == EsibBFOKsg){QutyXdwslS = true;}
      if(GPZfyUdYgD == SrNlzzuPDc){pgrHKUMZSc = true;}
      else if(SrNlzzuPDc == GPZfyUdYgD){SaPYpTdlJz = true;}
      if(nSyNmYoBbh == cXxVcMohsN){zctkarOfKp = true;}
      else if(cXxVcMohsN == nSyNmYoBbh){MeXhDqmIEV = true;}
      if(IrWEXHPnJb == MceQKBAXNU){NwGYBxoRTx = true;}
      if(beAwFkwYiJ == zktATUfNhM){CmRfzpOALD = true;}
      if(aMFCgkuVnb == SfltNTdtPq){YDOMddnAIU = true;}
      while(MceQKBAXNU == IrWEXHPnJb){QUqfSiSVin = true;}
      while(zktATUfNhM == zktATUfNhM){NnHbFiYjHw = true;}
      while(SfltNTdtPq == SfltNTdtPq){ZIgXskWMtf = true;}
      if(wNHMKpNxby == true){wNHMKpNxby = false;}
      if(yWBicqdxCI == true){yWBicqdxCI = false;}
      if(gbAgtgpjCp == true){gbAgtgpjCp = false;}
      if(XGIVYldgpc == true){XGIVYldgpc = false;}
      if(GiliNwdDRW == true){GiliNwdDRW = false;}
      if(pgrHKUMZSc == true){pgrHKUMZSc = false;}
      if(zctkarOfKp == true){zctkarOfKp = false;}
      if(NwGYBxoRTx == true){NwGYBxoRTx = false;}
      if(CmRfzpOALD == true){CmRfzpOALD = false;}
      if(YDOMddnAIU == true){YDOMddnAIU = false;}
      if(gysaJtZSFM == true){gysaJtZSFM = false;}
      if(fuGUZLLNkj == true){fuGUZLLNkj = false;}
      if(dNTGRJhttX == true){dNTGRJhttX = false;}
      if(JnIyQEtpWF == true){JnIyQEtpWF = false;}
      if(QutyXdwslS == true){QutyXdwslS = false;}
      if(SaPYpTdlJz == true){SaPYpTdlJz = false;}
      if(MeXhDqmIEV == true){MeXhDqmIEV = false;}
      if(QUqfSiSVin == true){QUqfSiSVin = false;}
      if(NnHbFiYjHw == true){NnHbFiYjHw = false;}
      if(ZIgXskWMtf == true){ZIgXskWMtf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PTPYEMLSDI
{ 
  void LPOfjgNnKZ()
  { 
      bool QxhMfqsdDY = false;
      bool cVZKRxRBab = false;
      bool fXRZNSEYqU = false;
      bool jlShLHWEjq = false;
      bool DGqsTElVmS = false;
      bool tXfQFsfIyM = false;
      bool lUlinpCqzK = false;
      bool ZMQiYZfXGI = false;
      bool fhkXaMFCcS = false;
      bool bOFXEhTHFc = false;
      bool CtWcsgHxre = false;
      bool MHCpfDiNIa = false;
      bool jAOghKHrep = false;
      bool FYScGkLIet = false;
      bool FIJxFTMPqA = false;
      bool zFzdsBfpth = false;
      bool YORBZnoZjt = false;
      bool raiOVapQaO = false;
      bool yrBdqzYnjE = false;
      bool FVOwUqpIXR = false;
      string TEbLbtmrAZ;
      string mBhMKrfZZJ;
      string UBRFYMoLzs;
      string GCFxFSndLB;
      string MWScUbtUqN;
      string NNRSoSlVlO;
      string FarGSkukGr;
      string EBNXxxhokx;
      string RTTlesjlIl;
      string fRrwwkdMJi;
      string fJNzIMzsVq;
      string kxknwkHGaZ;
      string AJbULlJQbM;
      string TUeBRIFUcS;
      string sqQQBigEAK;
      string dWkjiVgsmW;
      string ChRJXPSjVn;
      string eldHfJsLTb;
      string EFQQiwjuSw;
      string aMgFQLYGrk;
      if(TEbLbtmrAZ == fJNzIMzsVq){QxhMfqsdDY = true;}
      else if(fJNzIMzsVq == TEbLbtmrAZ){CtWcsgHxre = true;}
      if(mBhMKrfZZJ == kxknwkHGaZ){cVZKRxRBab = true;}
      else if(kxknwkHGaZ == mBhMKrfZZJ){MHCpfDiNIa = true;}
      if(UBRFYMoLzs == AJbULlJQbM){fXRZNSEYqU = true;}
      else if(AJbULlJQbM == UBRFYMoLzs){jAOghKHrep = true;}
      if(GCFxFSndLB == TUeBRIFUcS){jlShLHWEjq = true;}
      else if(TUeBRIFUcS == GCFxFSndLB){FYScGkLIet = true;}
      if(MWScUbtUqN == sqQQBigEAK){DGqsTElVmS = true;}
      else if(sqQQBigEAK == MWScUbtUqN){FIJxFTMPqA = true;}
      if(NNRSoSlVlO == dWkjiVgsmW){tXfQFsfIyM = true;}
      else if(dWkjiVgsmW == NNRSoSlVlO){zFzdsBfpth = true;}
      if(FarGSkukGr == ChRJXPSjVn){lUlinpCqzK = true;}
      else if(ChRJXPSjVn == FarGSkukGr){YORBZnoZjt = true;}
      if(EBNXxxhokx == eldHfJsLTb){ZMQiYZfXGI = true;}
      if(RTTlesjlIl == EFQQiwjuSw){fhkXaMFCcS = true;}
      if(fRrwwkdMJi == aMgFQLYGrk){bOFXEhTHFc = true;}
      while(eldHfJsLTb == EBNXxxhokx){raiOVapQaO = true;}
      while(EFQQiwjuSw == EFQQiwjuSw){yrBdqzYnjE = true;}
      while(aMgFQLYGrk == aMgFQLYGrk){FVOwUqpIXR = true;}
      if(QxhMfqsdDY == true){QxhMfqsdDY = false;}
      if(cVZKRxRBab == true){cVZKRxRBab = false;}
      if(fXRZNSEYqU == true){fXRZNSEYqU = false;}
      if(jlShLHWEjq == true){jlShLHWEjq = false;}
      if(DGqsTElVmS == true){DGqsTElVmS = false;}
      if(tXfQFsfIyM == true){tXfQFsfIyM = false;}
      if(lUlinpCqzK == true){lUlinpCqzK = false;}
      if(ZMQiYZfXGI == true){ZMQiYZfXGI = false;}
      if(fhkXaMFCcS == true){fhkXaMFCcS = false;}
      if(bOFXEhTHFc == true){bOFXEhTHFc = false;}
      if(CtWcsgHxre == true){CtWcsgHxre = false;}
      if(MHCpfDiNIa == true){MHCpfDiNIa = false;}
      if(jAOghKHrep == true){jAOghKHrep = false;}
      if(FYScGkLIet == true){FYScGkLIet = false;}
      if(FIJxFTMPqA == true){FIJxFTMPqA = false;}
      if(zFzdsBfpth == true){zFzdsBfpth = false;}
      if(YORBZnoZjt == true){YORBZnoZjt = false;}
      if(raiOVapQaO == true){raiOVapQaO = false;}
      if(yrBdqzYnjE == true){yrBdqzYnjE = false;}
      if(FVOwUqpIXR == true){FVOwUqpIXR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HRERLVNQOA
{ 
  void lhQAoFYbfO()
  { 
      bool taUewGlCsz = false;
      bool zZXdLWLxiy = false;
      bool EGgHAEBwMu = false;
      bool qlSCpqOsgU = false;
      bool HjClHOaGNV = false;
      bool HUkOnnsMdr = false;
      bool EopyHNGVmT = false;
      bool HSQOqTDtAl = false;
      bool cuhqmWBENC = false;
      bool yBPnPRtEes = false;
      bool HETsNoDVWT = false;
      bool jzMrOJHyKj = false;
      bool LBIjVGDbzZ = false;
      bool ZzPGdYaody = false;
      bool SfhtSyoWZF = false;
      bool KusthFwiXG = false;
      bool kaVwsjjFNp = false;
      bool iSUMRfTNRW = false;
      bool RfCtPdGUYX = false;
      bool brQWMqJlAh = false;
      string jrrbqrLUFH;
      string IoSJXrYbGP;
      string orGXtSIcAd;
      string HFrfLnasdG;
      string ODmbPoetgG;
      string FZFgfqkUhY;
      string jhUbADwlyj;
      string QfxAAkFeHF;
      string nOwtXgzKAU;
      string CFLFVfiLaM;
      string rrwwoZcFft;
      string kFMbkVlaDS;
      string DllchLTrdU;
      string CtDtNuRzEy;
      string EseFiwsjTA;
      string sIHIJGGSOd;
      string GjaKrpCROo;
      string DlVFOJGftk;
      string SiXdaslukG;
      string ozkZrTSTMr;
      if(jrrbqrLUFH == rrwwoZcFft){taUewGlCsz = true;}
      else if(rrwwoZcFft == jrrbqrLUFH){HETsNoDVWT = true;}
      if(IoSJXrYbGP == kFMbkVlaDS){zZXdLWLxiy = true;}
      else if(kFMbkVlaDS == IoSJXrYbGP){jzMrOJHyKj = true;}
      if(orGXtSIcAd == DllchLTrdU){EGgHAEBwMu = true;}
      else if(DllchLTrdU == orGXtSIcAd){LBIjVGDbzZ = true;}
      if(HFrfLnasdG == CtDtNuRzEy){qlSCpqOsgU = true;}
      else if(CtDtNuRzEy == HFrfLnasdG){ZzPGdYaody = true;}
      if(ODmbPoetgG == EseFiwsjTA){HjClHOaGNV = true;}
      else if(EseFiwsjTA == ODmbPoetgG){SfhtSyoWZF = true;}
      if(FZFgfqkUhY == sIHIJGGSOd){HUkOnnsMdr = true;}
      else if(sIHIJGGSOd == FZFgfqkUhY){KusthFwiXG = true;}
      if(jhUbADwlyj == GjaKrpCROo){EopyHNGVmT = true;}
      else if(GjaKrpCROo == jhUbADwlyj){kaVwsjjFNp = true;}
      if(QfxAAkFeHF == DlVFOJGftk){HSQOqTDtAl = true;}
      if(nOwtXgzKAU == SiXdaslukG){cuhqmWBENC = true;}
      if(CFLFVfiLaM == ozkZrTSTMr){yBPnPRtEes = true;}
      while(DlVFOJGftk == QfxAAkFeHF){iSUMRfTNRW = true;}
      while(SiXdaslukG == SiXdaslukG){RfCtPdGUYX = true;}
      while(ozkZrTSTMr == ozkZrTSTMr){brQWMqJlAh = true;}
      if(taUewGlCsz == true){taUewGlCsz = false;}
      if(zZXdLWLxiy == true){zZXdLWLxiy = false;}
      if(EGgHAEBwMu == true){EGgHAEBwMu = false;}
      if(qlSCpqOsgU == true){qlSCpqOsgU = false;}
      if(HjClHOaGNV == true){HjClHOaGNV = false;}
      if(HUkOnnsMdr == true){HUkOnnsMdr = false;}
      if(EopyHNGVmT == true){EopyHNGVmT = false;}
      if(HSQOqTDtAl == true){HSQOqTDtAl = false;}
      if(cuhqmWBENC == true){cuhqmWBENC = false;}
      if(yBPnPRtEes == true){yBPnPRtEes = false;}
      if(HETsNoDVWT == true){HETsNoDVWT = false;}
      if(jzMrOJHyKj == true){jzMrOJHyKj = false;}
      if(LBIjVGDbzZ == true){LBIjVGDbzZ = false;}
      if(ZzPGdYaody == true){ZzPGdYaody = false;}
      if(SfhtSyoWZF == true){SfhtSyoWZF = false;}
      if(KusthFwiXG == true){KusthFwiXG = false;}
      if(kaVwsjjFNp == true){kaVwsjjFNp = false;}
      if(iSUMRfTNRW == true){iSUMRfTNRW = false;}
      if(RfCtPdGUYX == true){RfCtPdGUYX = false;}
      if(brQWMqJlAh == true){brQWMqJlAh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WHDBKOXPQG
{ 
  void kAHenVgVzY()
  { 
      bool xDnJcRYWqY = false;
      bool YqXHuFMbwC = false;
      bool xLIgUeueji = false;
      bool hhVZGUDMCI = false;
      bool csOOaqxohK = false;
      bool PItVhluHoy = false;
      bool WtmIppUxAZ = false;
      bool CzYnZEwtGc = false;
      bool gFxYSZnAqU = false;
      bool ZuWEkhFGXj = false;
      bool VznHIPiFwd = false;
      bool pBBLQQxNoQ = false;
      bool CUGfAGbUCq = false;
      bool yoVVGhRoQD = false;
      bool phENeXtLmU = false;
      bool krQGhBsIGB = false;
      bool mODEeAeeEi = false;
      bool zHxlZTPrAb = false;
      bool MQggFGYPnF = false;
      bool nJhPPbdzhe = false;
      string kQRdTSLSjR;
      string fWCSLiQHhi;
      string tHGHUSuabt;
      string RLQSYBkGly;
      string rbdYXoqVoo;
      string UnBxFdKKIA;
      string XjqpzUFjsK;
      string yKVjqSchif;
      string bZlmZdJTNt;
      string qaxlaHknYD;
      string iHbdqKSRGl;
      string BbacXxyDPV;
      string KlVySXMjJi;
      string hnJfwUyHwO;
      string KrNbsPzUNc;
      string IgXCrxkcKS;
      string xiHWDNRufD;
      string zqHBKSYtFD;
      string XrVfZBPGmz;
      string iUwcQbjpXf;
      if(kQRdTSLSjR == iHbdqKSRGl){xDnJcRYWqY = true;}
      else if(iHbdqKSRGl == kQRdTSLSjR){VznHIPiFwd = true;}
      if(fWCSLiQHhi == BbacXxyDPV){YqXHuFMbwC = true;}
      else if(BbacXxyDPV == fWCSLiQHhi){pBBLQQxNoQ = true;}
      if(tHGHUSuabt == KlVySXMjJi){xLIgUeueji = true;}
      else if(KlVySXMjJi == tHGHUSuabt){CUGfAGbUCq = true;}
      if(RLQSYBkGly == hnJfwUyHwO){hhVZGUDMCI = true;}
      else if(hnJfwUyHwO == RLQSYBkGly){yoVVGhRoQD = true;}
      if(rbdYXoqVoo == KrNbsPzUNc){csOOaqxohK = true;}
      else if(KrNbsPzUNc == rbdYXoqVoo){phENeXtLmU = true;}
      if(UnBxFdKKIA == IgXCrxkcKS){PItVhluHoy = true;}
      else if(IgXCrxkcKS == UnBxFdKKIA){krQGhBsIGB = true;}
      if(XjqpzUFjsK == xiHWDNRufD){WtmIppUxAZ = true;}
      else if(xiHWDNRufD == XjqpzUFjsK){mODEeAeeEi = true;}
      if(yKVjqSchif == zqHBKSYtFD){CzYnZEwtGc = true;}
      if(bZlmZdJTNt == XrVfZBPGmz){gFxYSZnAqU = true;}
      if(qaxlaHknYD == iUwcQbjpXf){ZuWEkhFGXj = true;}
      while(zqHBKSYtFD == yKVjqSchif){zHxlZTPrAb = true;}
      while(XrVfZBPGmz == XrVfZBPGmz){MQggFGYPnF = true;}
      while(iUwcQbjpXf == iUwcQbjpXf){nJhPPbdzhe = true;}
      if(xDnJcRYWqY == true){xDnJcRYWqY = false;}
      if(YqXHuFMbwC == true){YqXHuFMbwC = false;}
      if(xLIgUeueji == true){xLIgUeueji = false;}
      if(hhVZGUDMCI == true){hhVZGUDMCI = false;}
      if(csOOaqxohK == true){csOOaqxohK = false;}
      if(PItVhluHoy == true){PItVhluHoy = false;}
      if(WtmIppUxAZ == true){WtmIppUxAZ = false;}
      if(CzYnZEwtGc == true){CzYnZEwtGc = false;}
      if(gFxYSZnAqU == true){gFxYSZnAqU = false;}
      if(ZuWEkhFGXj == true){ZuWEkhFGXj = false;}
      if(VznHIPiFwd == true){VznHIPiFwd = false;}
      if(pBBLQQxNoQ == true){pBBLQQxNoQ = false;}
      if(CUGfAGbUCq == true){CUGfAGbUCq = false;}
      if(yoVVGhRoQD == true){yoVVGhRoQD = false;}
      if(phENeXtLmU == true){phENeXtLmU = false;}
      if(krQGhBsIGB == true){krQGhBsIGB = false;}
      if(mODEeAeeEi == true){mODEeAeeEi = false;}
      if(zHxlZTPrAb == true){zHxlZTPrAb = false;}
      if(MQggFGYPnF == true){MQggFGYPnF = false;}
      if(nJhPPbdzhe == true){nJhPPbdzhe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JJQKTPQAOX
{ 
  void bdAAlHZPwx()
  { 
      bool ZWFiYxaHGE = false;
      bool ljnrflLHtk = false;
      bool WILAzmMwLC = false;
      bool HYuHSnqcOO = false;
      bool MjDSrHIhGL = false;
      bool UccGlRKFik = false;
      bool kduExNnfZq = false;
      bool tisfXmEsHq = false;
      bool edoAgdwoVB = false;
      bool dkscdhozVd = false;
      bool TbIPQliwhz = false;
      bool MQxrGGouWS = false;
      bool RzKXNJoPCo = false;
      bool xFXdXDVZiu = false;
      bool tzGWnMmAWW = false;
      bool stcCMURjBH = false;
      bool wStrBHsTUC = false;
      bool jOLbYRrmjB = false;
      bool VnseuDbVQC = false;
      bool lkYayaENVf = false;
      string GFDGRDtSRq;
      string BgjOJiCCUG;
      string sRHHqRUIUa;
      string qFWmhKGrhc;
      string XVAdRTYZXj;
      string bdhnwnxuPA;
      string hkxqAuJwgz;
      string bKTqiWRdpX;
      string rukkzNWiqs;
      string MKbhulXJcV;
      string JcsXHRJqEY;
      string WTErHlAMrm;
      string YaFmlQhlwx;
      string zIAUNPCMcg;
      string DfdRWsGjZI;
      string kKRpxiXFlp;
      string iWuGZNSjdq;
      string jmiKirwmQs;
      string KxLmMnqKXd;
      string rwamygkXrI;
      if(GFDGRDtSRq == JcsXHRJqEY){ZWFiYxaHGE = true;}
      else if(JcsXHRJqEY == GFDGRDtSRq){TbIPQliwhz = true;}
      if(BgjOJiCCUG == WTErHlAMrm){ljnrflLHtk = true;}
      else if(WTErHlAMrm == BgjOJiCCUG){MQxrGGouWS = true;}
      if(sRHHqRUIUa == YaFmlQhlwx){WILAzmMwLC = true;}
      else if(YaFmlQhlwx == sRHHqRUIUa){RzKXNJoPCo = true;}
      if(qFWmhKGrhc == zIAUNPCMcg){HYuHSnqcOO = true;}
      else if(zIAUNPCMcg == qFWmhKGrhc){xFXdXDVZiu = true;}
      if(XVAdRTYZXj == DfdRWsGjZI){MjDSrHIhGL = true;}
      else if(DfdRWsGjZI == XVAdRTYZXj){tzGWnMmAWW = true;}
      if(bdhnwnxuPA == kKRpxiXFlp){UccGlRKFik = true;}
      else if(kKRpxiXFlp == bdhnwnxuPA){stcCMURjBH = true;}
      if(hkxqAuJwgz == iWuGZNSjdq){kduExNnfZq = true;}
      else if(iWuGZNSjdq == hkxqAuJwgz){wStrBHsTUC = true;}
      if(bKTqiWRdpX == jmiKirwmQs){tisfXmEsHq = true;}
      if(rukkzNWiqs == KxLmMnqKXd){edoAgdwoVB = true;}
      if(MKbhulXJcV == rwamygkXrI){dkscdhozVd = true;}
      while(jmiKirwmQs == bKTqiWRdpX){jOLbYRrmjB = true;}
      while(KxLmMnqKXd == KxLmMnqKXd){VnseuDbVQC = true;}
      while(rwamygkXrI == rwamygkXrI){lkYayaENVf = true;}
      if(ZWFiYxaHGE == true){ZWFiYxaHGE = false;}
      if(ljnrflLHtk == true){ljnrflLHtk = false;}
      if(WILAzmMwLC == true){WILAzmMwLC = false;}
      if(HYuHSnqcOO == true){HYuHSnqcOO = false;}
      if(MjDSrHIhGL == true){MjDSrHIhGL = false;}
      if(UccGlRKFik == true){UccGlRKFik = false;}
      if(kduExNnfZq == true){kduExNnfZq = false;}
      if(tisfXmEsHq == true){tisfXmEsHq = false;}
      if(edoAgdwoVB == true){edoAgdwoVB = false;}
      if(dkscdhozVd == true){dkscdhozVd = false;}
      if(TbIPQliwhz == true){TbIPQliwhz = false;}
      if(MQxrGGouWS == true){MQxrGGouWS = false;}
      if(RzKXNJoPCo == true){RzKXNJoPCo = false;}
      if(xFXdXDVZiu == true){xFXdXDVZiu = false;}
      if(tzGWnMmAWW == true){tzGWnMmAWW = false;}
      if(stcCMURjBH == true){stcCMURjBH = false;}
      if(wStrBHsTUC == true){wStrBHsTUC = false;}
      if(jOLbYRrmjB == true){jOLbYRrmjB = false;}
      if(VnseuDbVQC == true){VnseuDbVQC = false;}
      if(lkYayaENVf == true){lkYayaENVf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IKJVUPKTOU
{ 
  void VmpbVejyJm()
  { 
      bool fOjSnFDwlr = false;
      bool TIBXqcMbwD = false;
      bool nlUQXqtEck = false;
      bool ezNkHdycys = false;
      bool iAdnKWbfVi = false;
      bool gwDfjstSux = false;
      bool KyTANTuPPM = false;
      bool ejcCUnIgGA = false;
      bool POisDhwgBO = false;
      bool jegBhjgcZp = false;
      bool aLPIExSAKu = false;
      bool kMMtguPZxf = false;
      bool XNOBbACbTk = false;
      bool HfGPYEyZoF = false;
      bool OuWFcXRmUm = false;
      bool TGetRNwOgD = false;
      bool tqfZnEFxUc = false;
      bool xpkqQbqJXE = false;
      bool hPHgQBAMxL = false;
      bool HiskLXPwRY = false;
      string zGzwxOcMPr;
      string UoKdTEBzBz;
      string rupByppQAE;
      string haHPgguSUn;
      string dyMJhrYZTF;
      string GFZQrDPyxH;
      string XLLLKshuwm;
      string IheNUtigSG;
      string QQxuxcBpXd;
      string QxVMQSlAzo;
      string KdcgwYZMwx;
      string TifqpHOQOh;
      string rrWSVLMRwC;
      string HigcwlmPyY;
      string CnsZJhReWI;
      string DVlRwRGKLk;
      string LHPtpkBCtD;
      string UyRoeDyxJn;
      string shumylwPgd;
      string fcDNMtYzjX;
      if(zGzwxOcMPr == KdcgwYZMwx){fOjSnFDwlr = true;}
      else if(KdcgwYZMwx == zGzwxOcMPr){aLPIExSAKu = true;}
      if(UoKdTEBzBz == TifqpHOQOh){TIBXqcMbwD = true;}
      else if(TifqpHOQOh == UoKdTEBzBz){kMMtguPZxf = true;}
      if(rupByppQAE == rrWSVLMRwC){nlUQXqtEck = true;}
      else if(rrWSVLMRwC == rupByppQAE){XNOBbACbTk = true;}
      if(haHPgguSUn == HigcwlmPyY){ezNkHdycys = true;}
      else if(HigcwlmPyY == haHPgguSUn){HfGPYEyZoF = true;}
      if(dyMJhrYZTF == CnsZJhReWI){iAdnKWbfVi = true;}
      else if(CnsZJhReWI == dyMJhrYZTF){OuWFcXRmUm = true;}
      if(GFZQrDPyxH == DVlRwRGKLk){gwDfjstSux = true;}
      else if(DVlRwRGKLk == GFZQrDPyxH){TGetRNwOgD = true;}
      if(XLLLKshuwm == LHPtpkBCtD){KyTANTuPPM = true;}
      else if(LHPtpkBCtD == XLLLKshuwm){tqfZnEFxUc = true;}
      if(IheNUtigSG == UyRoeDyxJn){ejcCUnIgGA = true;}
      if(QQxuxcBpXd == shumylwPgd){POisDhwgBO = true;}
      if(QxVMQSlAzo == fcDNMtYzjX){jegBhjgcZp = true;}
      while(UyRoeDyxJn == IheNUtigSG){xpkqQbqJXE = true;}
      while(shumylwPgd == shumylwPgd){hPHgQBAMxL = true;}
      while(fcDNMtYzjX == fcDNMtYzjX){HiskLXPwRY = true;}
      if(fOjSnFDwlr == true){fOjSnFDwlr = false;}
      if(TIBXqcMbwD == true){TIBXqcMbwD = false;}
      if(nlUQXqtEck == true){nlUQXqtEck = false;}
      if(ezNkHdycys == true){ezNkHdycys = false;}
      if(iAdnKWbfVi == true){iAdnKWbfVi = false;}
      if(gwDfjstSux == true){gwDfjstSux = false;}
      if(KyTANTuPPM == true){KyTANTuPPM = false;}
      if(ejcCUnIgGA == true){ejcCUnIgGA = false;}
      if(POisDhwgBO == true){POisDhwgBO = false;}
      if(jegBhjgcZp == true){jegBhjgcZp = false;}
      if(aLPIExSAKu == true){aLPIExSAKu = false;}
      if(kMMtguPZxf == true){kMMtguPZxf = false;}
      if(XNOBbACbTk == true){XNOBbACbTk = false;}
      if(HfGPYEyZoF == true){HfGPYEyZoF = false;}
      if(OuWFcXRmUm == true){OuWFcXRmUm = false;}
      if(TGetRNwOgD == true){TGetRNwOgD = false;}
      if(tqfZnEFxUc == true){tqfZnEFxUc = false;}
      if(xpkqQbqJXE == true){xpkqQbqJXE = false;}
      if(hPHgQBAMxL == true){hPHgQBAMxL = false;}
      if(HiskLXPwRY == true){HiskLXPwRY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XXVVDKAXCW
{ 
  void ilAePtdQSD()
  { 
      bool cAiQnELURw = false;
      bool ooOcgSaQTs = false;
      bool zCGBcqlcmr = false;
      bool RXbmpMcPbG = false;
      bool KOIHonLyjS = false;
      bool taThYZtgnw = false;
      bool SigYeRMamU = false;
      bool pKoMijsyMn = false;
      bool emrUypEtOP = false;
      bool RwbenagicW = false;
      bool ajLPcilGzn = false;
      bool gwUzQeqMan = false;
      bool NSMWCsiKYH = false;
      bool CKVoMubcrO = false;
      bool ExtZiVacNI = false;
      bool jUHnJIXnMi = false;
      bool AagqkWZflV = false;
      bool CNTMjPYlng = false;
      bool SGxQXhCgfE = false;
      bool WnPJOcQDoM = false;
      string jCXMfwEjnE;
      string YWupQKtLZQ;
      string eInArkiaBb;
      string TQSOyCEtAi;
      string hruJziWmhX;
      string FaqqebNXUu;
      string NdhLkIEfqN;
      string FALphmNeBJ;
      string OurcVsYajW;
      string ogZFVEKiXp;
      string dpuUSFOAIr;
      string NiVKfRkEor;
      string icwUYYaGTd;
      string bdGLeYAXKQ;
      string dYRqIFLOYE;
      string SFtfGAtawt;
      string eIfePjcKfH;
      string QNsYNKKELS;
      string MLgPLWjaEd;
      string dZbQkVrmbY;
      if(jCXMfwEjnE == dpuUSFOAIr){cAiQnELURw = true;}
      else if(dpuUSFOAIr == jCXMfwEjnE){ajLPcilGzn = true;}
      if(YWupQKtLZQ == NiVKfRkEor){ooOcgSaQTs = true;}
      else if(NiVKfRkEor == YWupQKtLZQ){gwUzQeqMan = true;}
      if(eInArkiaBb == icwUYYaGTd){zCGBcqlcmr = true;}
      else if(icwUYYaGTd == eInArkiaBb){NSMWCsiKYH = true;}
      if(TQSOyCEtAi == bdGLeYAXKQ){RXbmpMcPbG = true;}
      else if(bdGLeYAXKQ == TQSOyCEtAi){CKVoMubcrO = true;}
      if(hruJziWmhX == dYRqIFLOYE){KOIHonLyjS = true;}
      else if(dYRqIFLOYE == hruJziWmhX){ExtZiVacNI = true;}
      if(FaqqebNXUu == SFtfGAtawt){taThYZtgnw = true;}
      else if(SFtfGAtawt == FaqqebNXUu){jUHnJIXnMi = true;}
      if(NdhLkIEfqN == eIfePjcKfH){SigYeRMamU = true;}
      else if(eIfePjcKfH == NdhLkIEfqN){AagqkWZflV = true;}
      if(FALphmNeBJ == QNsYNKKELS){pKoMijsyMn = true;}
      if(OurcVsYajW == MLgPLWjaEd){emrUypEtOP = true;}
      if(ogZFVEKiXp == dZbQkVrmbY){RwbenagicW = true;}
      while(QNsYNKKELS == FALphmNeBJ){CNTMjPYlng = true;}
      while(MLgPLWjaEd == MLgPLWjaEd){SGxQXhCgfE = true;}
      while(dZbQkVrmbY == dZbQkVrmbY){WnPJOcQDoM = true;}
      if(cAiQnELURw == true){cAiQnELURw = false;}
      if(ooOcgSaQTs == true){ooOcgSaQTs = false;}
      if(zCGBcqlcmr == true){zCGBcqlcmr = false;}
      if(RXbmpMcPbG == true){RXbmpMcPbG = false;}
      if(KOIHonLyjS == true){KOIHonLyjS = false;}
      if(taThYZtgnw == true){taThYZtgnw = false;}
      if(SigYeRMamU == true){SigYeRMamU = false;}
      if(pKoMijsyMn == true){pKoMijsyMn = false;}
      if(emrUypEtOP == true){emrUypEtOP = false;}
      if(RwbenagicW == true){RwbenagicW = false;}
      if(ajLPcilGzn == true){ajLPcilGzn = false;}
      if(gwUzQeqMan == true){gwUzQeqMan = false;}
      if(NSMWCsiKYH == true){NSMWCsiKYH = false;}
      if(CKVoMubcrO == true){CKVoMubcrO = false;}
      if(ExtZiVacNI == true){ExtZiVacNI = false;}
      if(jUHnJIXnMi == true){jUHnJIXnMi = false;}
      if(AagqkWZflV == true){AagqkWZflV = false;}
      if(CNTMjPYlng == true){CNTMjPYlng = false;}
      if(SGxQXhCgfE == true){SGxQXhCgfE = false;}
      if(WnPJOcQDoM == true){WnPJOcQDoM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WMCVCZZAXI
{ 
  void BDYZENigVD()
  { 
      bool JZtzNITmgJ = false;
      bool grFNMJUnHn = false;
      bool iQcRNFBDgh = false;
      bool GDlUNihslD = false;
      bool eSWVNtGHrs = false;
      bool mJTKerxckH = false;
      bool HPGyDcGkzd = false;
      bool bbBDJPtGDT = false;
      bool ysKnuwjaoV = false;
      bool lFHduOMXSj = false;
      bool mVIOQKHQBO = false;
      bool ypZRINFSDG = false;
      bool sfwdrVTWIt = false;
      bool DWnSfckuWj = false;
      bool oSZZXufpVg = false;
      bool JtTMqHZeWu = false;
      bool qkHGLaCGke = false;
      bool cJuTRZGVGw = false;
      bool pcBakIDabX = false;
      bool DFYbsDLSNw = false;
      string lpqpPLiQXf;
      string sFTUKNJKZh;
      string hxirWhOLlp;
      string rAVzLhjwzu;
      string gsaXuYSkQs;
      string gQxNCoHyTh;
      string wXdgnrjTJc;
      string dMKdBoWLwx;
      string PctrJbDHxW;
      string akcRzIOsjC;
      string ozbnPUFSMM;
      string RwCVRTclXL;
      string obVmCrirer;
      string acasIQBGcn;
      string VkukEdiHAf;
      string fcVXNNcnkW;
      string lNmTloUIMB;
      string RWIipEfkiX;
      string JbrzMyGDfu;
      string mMUFCIxbyO;
      if(lpqpPLiQXf == ozbnPUFSMM){JZtzNITmgJ = true;}
      else if(ozbnPUFSMM == lpqpPLiQXf){mVIOQKHQBO = true;}
      if(sFTUKNJKZh == RwCVRTclXL){grFNMJUnHn = true;}
      else if(RwCVRTclXL == sFTUKNJKZh){ypZRINFSDG = true;}
      if(hxirWhOLlp == obVmCrirer){iQcRNFBDgh = true;}
      else if(obVmCrirer == hxirWhOLlp){sfwdrVTWIt = true;}
      if(rAVzLhjwzu == acasIQBGcn){GDlUNihslD = true;}
      else if(acasIQBGcn == rAVzLhjwzu){DWnSfckuWj = true;}
      if(gsaXuYSkQs == VkukEdiHAf){eSWVNtGHrs = true;}
      else if(VkukEdiHAf == gsaXuYSkQs){oSZZXufpVg = true;}
      if(gQxNCoHyTh == fcVXNNcnkW){mJTKerxckH = true;}
      else if(fcVXNNcnkW == gQxNCoHyTh){JtTMqHZeWu = true;}
      if(wXdgnrjTJc == lNmTloUIMB){HPGyDcGkzd = true;}
      else if(lNmTloUIMB == wXdgnrjTJc){qkHGLaCGke = true;}
      if(dMKdBoWLwx == RWIipEfkiX){bbBDJPtGDT = true;}
      if(PctrJbDHxW == JbrzMyGDfu){ysKnuwjaoV = true;}
      if(akcRzIOsjC == mMUFCIxbyO){lFHduOMXSj = true;}
      while(RWIipEfkiX == dMKdBoWLwx){cJuTRZGVGw = true;}
      while(JbrzMyGDfu == JbrzMyGDfu){pcBakIDabX = true;}
      while(mMUFCIxbyO == mMUFCIxbyO){DFYbsDLSNw = true;}
      if(JZtzNITmgJ == true){JZtzNITmgJ = false;}
      if(grFNMJUnHn == true){grFNMJUnHn = false;}
      if(iQcRNFBDgh == true){iQcRNFBDgh = false;}
      if(GDlUNihslD == true){GDlUNihslD = false;}
      if(eSWVNtGHrs == true){eSWVNtGHrs = false;}
      if(mJTKerxckH == true){mJTKerxckH = false;}
      if(HPGyDcGkzd == true){HPGyDcGkzd = false;}
      if(bbBDJPtGDT == true){bbBDJPtGDT = false;}
      if(ysKnuwjaoV == true){ysKnuwjaoV = false;}
      if(lFHduOMXSj == true){lFHduOMXSj = false;}
      if(mVIOQKHQBO == true){mVIOQKHQBO = false;}
      if(ypZRINFSDG == true){ypZRINFSDG = false;}
      if(sfwdrVTWIt == true){sfwdrVTWIt = false;}
      if(DWnSfckuWj == true){DWnSfckuWj = false;}
      if(oSZZXufpVg == true){oSZZXufpVg = false;}
      if(JtTMqHZeWu == true){JtTMqHZeWu = false;}
      if(qkHGLaCGke == true){qkHGLaCGke = false;}
      if(cJuTRZGVGw == true){cJuTRZGVGw = false;}
      if(pcBakIDabX == true){pcBakIDabX = false;}
      if(DFYbsDLSNw == true){DFYbsDLSNw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PYDNZFAZRW
{ 
  void yOrtPQhVED()
  { 
      bool ikrJNHPZpM = false;
      bool WrbPEtoVtY = false;
      bool uRjOKIdpDe = false;
      bool phyRzLeQtK = false;
      bool CfFBIJVtJX = false;
      bool iMUXLQAczF = false;
      bool cYVLWotJQr = false;
      bool PXaiVPLiGA = false;
      bool ligfucNZFh = false;
      bool KCRogdJtdT = false;
      bool OMdQIKkkCw = false;
      bool ERVyTtrpPs = false;
      bool aTDhhMGlBr = false;
      bool GRElkYFPWk = false;
      bool rbXJdrfSVm = false;
      bool lTdksuIwiw = false;
      bool DzjKplMjMt = false;
      bool obSeBzwtEo = false;
      bool fmQNFlnTsp = false;
      bool QIgagrqNTq = false;
      string mZNyADkJEQ;
      string cLROJRPHRp;
      string YexsKkOyti;
      string calQTdCWnP;
      string gBYXXSXeKx;
      string VeIjAIcTnP;
      string olPUnCZAtf;
      string PsTCIWFYVr;
      string NjnwNxRBQL;
      string AhiXZtlEjV;
      string rWjdhbKFac;
      string CDyuCFySHp;
      string jXiiegKubO;
      string kBozApzJOk;
      string mLanIwjmVT;
      string wSwskTnByB;
      string ROdMqBNyuM;
      string GnDWCXxuZh;
      string xWZISRFwOf;
      string CyKNSXhOxH;
      if(mZNyADkJEQ == rWjdhbKFac){ikrJNHPZpM = true;}
      else if(rWjdhbKFac == mZNyADkJEQ){OMdQIKkkCw = true;}
      if(cLROJRPHRp == CDyuCFySHp){WrbPEtoVtY = true;}
      else if(CDyuCFySHp == cLROJRPHRp){ERVyTtrpPs = true;}
      if(YexsKkOyti == jXiiegKubO){uRjOKIdpDe = true;}
      else if(jXiiegKubO == YexsKkOyti){aTDhhMGlBr = true;}
      if(calQTdCWnP == kBozApzJOk){phyRzLeQtK = true;}
      else if(kBozApzJOk == calQTdCWnP){GRElkYFPWk = true;}
      if(gBYXXSXeKx == mLanIwjmVT){CfFBIJVtJX = true;}
      else if(mLanIwjmVT == gBYXXSXeKx){rbXJdrfSVm = true;}
      if(VeIjAIcTnP == wSwskTnByB){iMUXLQAczF = true;}
      else if(wSwskTnByB == VeIjAIcTnP){lTdksuIwiw = true;}
      if(olPUnCZAtf == ROdMqBNyuM){cYVLWotJQr = true;}
      else if(ROdMqBNyuM == olPUnCZAtf){DzjKplMjMt = true;}
      if(PsTCIWFYVr == GnDWCXxuZh){PXaiVPLiGA = true;}
      if(NjnwNxRBQL == xWZISRFwOf){ligfucNZFh = true;}
      if(AhiXZtlEjV == CyKNSXhOxH){KCRogdJtdT = true;}
      while(GnDWCXxuZh == PsTCIWFYVr){obSeBzwtEo = true;}
      while(xWZISRFwOf == xWZISRFwOf){fmQNFlnTsp = true;}
      while(CyKNSXhOxH == CyKNSXhOxH){QIgagrqNTq = true;}
      if(ikrJNHPZpM == true){ikrJNHPZpM = false;}
      if(WrbPEtoVtY == true){WrbPEtoVtY = false;}
      if(uRjOKIdpDe == true){uRjOKIdpDe = false;}
      if(phyRzLeQtK == true){phyRzLeQtK = false;}
      if(CfFBIJVtJX == true){CfFBIJVtJX = false;}
      if(iMUXLQAczF == true){iMUXLQAczF = false;}
      if(cYVLWotJQr == true){cYVLWotJQr = false;}
      if(PXaiVPLiGA == true){PXaiVPLiGA = false;}
      if(ligfucNZFh == true){ligfucNZFh = false;}
      if(KCRogdJtdT == true){KCRogdJtdT = false;}
      if(OMdQIKkkCw == true){OMdQIKkkCw = false;}
      if(ERVyTtrpPs == true){ERVyTtrpPs = false;}
      if(aTDhhMGlBr == true){aTDhhMGlBr = false;}
      if(GRElkYFPWk == true){GRElkYFPWk = false;}
      if(rbXJdrfSVm == true){rbXJdrfSVm = false;}
      if(lTdksuIwiw == true){lTdksuIwiw = false;}
      if(DzjKplMjMt == true){DzjKplMjMt = false;}
      if(obSeBzwtEo == true){obSeBzwtEo = false;}
      if(fmQNFlnTsp == true){fmQNFlnTsp = false;}
      if(QIgagrqNTq == true){QIgagrqNTq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAQUWOOSJA
{ 
  void xUZFwhEtPk()
  { 
      bool LnzLCizWEX = false;
      bool QERTZGdBTj = false;
      bool yqHgHrAomu = false;
      bool nCyLIlVgXa = false;
      bool JbEeTpwXCz = false;
      bool gNHLPTfSEJ = false;
      bool iJjJjNGGLm = false;
      bool kxcsZVmcNQ = false;
      bool ublnOZumun = false;
      bool GDbNqArtuF = false;
      bool jpMPNjjOlt = false;
      bool gDFnOHWutJ = false;
      bool STLWghUOBZ = false;
      bool crhHfEPWZe = false;
      bool pgABHCynzj = false;
      bool cxAklQeoif = false;
      bool OUMMQnVxHJ = false;
      bool qAUPTlSKPd = false;
      bool jfPRwerwUP = false;
      bool ZZntPUUnjS = false;
      string tEuIbmEjpL;
      string QfHOegfIiO;
      string xWRLxBjemR;
      string MVZPyTVama;
      string aJPyOlYwej;
      string TATDHWmjKZ;
      string CZxXzuGqPL;
      string KEUHnmHSwL;
      string bnACxLCVIb;
      string flQMXBMqyT;
      string fgfTZPeLPT;
      string OUmyxOZuam;
      string sjhmeYmIjl;
      string aQTcftHgch;
      string gpFnNLyROJ;
      string bRQKZuzrnA;
      string bWbdsyAKRD;
      string HrRsGCdtZT;
      string aVsZJJzICk;
      string uOrbFKObuO;
      if(tEuIbmEjpL == fgfTZPeLPT){LnzLCizWEX = true;}
      else if(fgfTZPeLPT == tEuIbmEjpL){jpMPNjjOlt = true;}
      if(QfHOegfIiO == OUmyxOZuam){QERTZGdBTj = true;}
      else if(OUmyxOZuam == QfHOegfIiO){gDFnOHWutJ = true;}
      if(xWRLxBjemR == sjhmeYmIjl){yqHgHrAomu = true;}
      else if(sjhmeYmIjl == xWRLxBjemR){STLWghUOBZ = true;}
      if(MVZPyTVama == aQTcftHgch){nCyLIlVgXa = true;}
      else if(aQTcftHgch == MVZPyTVama){crhHfEPWZe = true;}
      if(aJPyOlYwej == gpFnNLyROJ){JbEeTpwXCz = true;}
      else if(gpFnNLyROJ == aJPyOlYwej){pgABHCynzj = true;}
      if(TATDHWmjKZ == bRQKZuzrnA){gNHLPTfSEJ = true;}
      else if(bRQKZuzrnA == TATDHWmjKZ){cxAklQeoif = true;}
      if(CZxXzuGqPL == bWbdsyAKRD){iJjJjNGGLm = true;}
      else if(bWbdsyAKRD == CZxXzuGqPL){OUMMQnVxHJ = true;}
      if(KEUHnmHSwL == HrRsGCdtZT){kxcsZVmcNQ = true;}
      if(bnACxLCVIb == aVsZJJzICk){ublnOZumun = true;}
      if(flQMXBMqyT == uOrbFKObuO){GDbNqArtuF = true;}
      while(HrRsGCdtZT == KEUHnmHSwL){qAUPTlSKPd = true;}
      while(aVsZJJzICk == aVsZJJzICk){jfPRwerwUP = true;}
      while(uOrbFKObuO == uOrbFKObuO){ZZntPUUnjS = true;}
      if(LnzLCizWEX == true){LnzLCizWEX = false;}
      if(QERTZGdBTj == true){QERTZGdBTj = false;}
      if(yqHgHrAomu == true){yqHgHrAomu = false;}
      if(nCyLIlVgXa == true){nCyLIlVgXa = false;}
      if(JbEeTpwXCz == true){JbEeTpwXCz = false;}
      if(gNHLPTfSEJ == true){gNHLPTfSEJ = false;}
      if(iJjJjNGGLm == true){iJjJjNGGLm = false;}
      if(kxcsZVmcNQ == true){kxcsZVmcNQ = false;}
      if(ublnOZumun == true){ublnOZumun = false;}
      if(GDbNqArtuF == true){GDbNqArtuF = false;}
      if(jpMPNjjOlt == true){jpMPNjjOlt = false;}
      if(gDFnOHWutJ == true){gDFnOHWutJ = false;}
      if(STLWghUOBZ == true){STLWghUOBZ = false;}
      if(crhHfEPWZe == true){crhHfEPWZe = false;}
      if(pgABHCynzj == true){pgABHCynzj = false;}
      if(cxAklQeoif == true){cxAklQeoif = false;}
      if(OUMMQnVxHJ == true){OUMMQnVxHJ = false;}
      if(qAUPTlSKPd == true){qAUPTlSKPd = false;}
      if(jfPRwerwUP == true){jfPRwerwUP = false;}
      if(ZZntPUUnjS == true){ZZntPUUnjS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LDNHBXBZOD
{ 
  void mQXhiJDwlg()
  { 
      bool gYCHRYeeCX = false;
      bool INHYozGuQG = false;
      bool metuNbUsdQ = false;
      bool wCRWVLNLQt = false;
      bool tlzBhkzxMO = false;
      bool IdVFLCeGsp = false;
      bool ElAlaGujDc = false;
      bool kueVMAerNc = false;
      bool cWgPHSfLKT = false;
      bool fHRapHkMaa = false;
      bool oOticNyzsK = false;
      bool WmsPMhFjdI = false;
      bool ZjYjwdcEfE = false;
      bool PSQlnNcymt = false;
      bool TfRzwsNCNI = false;
      bool CBiRBEoKlz = false;
      bool jtTouEVHay = false;
      bool EHxiotRYmD = false;
      bool PZpXCOizki = false;
      bool YSLnJYMcEr = false;
      string QYNsVQEtKz;
      string TIrmgKPqbU;
      string trRqRMKarp;
      string aeCySlBsfZ;
      string gyMcGQHWlM;
      string rXPJaXGWbI;
      string GcBTXnGsTu;
      string IWKCnwfojA;
      string FmneyCPsWt;
      string eeQXTDwrER;
      string KOCqDUMMUe;
      string qRlbDSnVUV;
      string YMVYPdFmij;
      string znkSopjxbc;
      string oDXrCNroTA;
      string PZWisyrdaZ;
      string PZdkfDgTmM;
      string hptrfVodVC;
      string kQShTYQBZq;
      string yGVBNPYmMz;
      if(QYNsVQEtKz == KOCqDUMMUe){gYCHRYeeCX = true;}
      else if(KOCqDUMMUe == QYNsVQEtKz){oOticNyzsK = true;}
      if(TIrmgKPqbU == qRlbDSnVUV){INHYozGuQG = true;}
      else if(qRlbDSnVUV == TIrmgKPqbU){WmsPMhFjdI = true;}
      if(trRqRMKarp == YMVYPdFmij){metuNbUsdQ = true;}
      else if(YMVYPdFmij == trRqRMKarp){ZjYjwdcEfE = true;}
      if(aeCySlBsfZ == znkSopjxbc){wCRWVLNLQt = true;}
      else if(znkSopjxbc == aeCySlBsfZ){PSQlnNcymt = true;}
      if(gyMcGQHWlM == oDXrCNroTA){tlzBhkzxMO = true;}
      else if(oDXrCNroTA == gyMcGQHWlM){TfRzwsNCNI = true;}
      if(rXPJaXGWbI == PZWisyrdaZ){IdVFLCeGsp = true;}
      else if(PZWisyrdaZ == rXPJaXGWbI){CBiRBEoKlz = true;}
      if(GcBTXnGsTu == PZdkfDgTmM){ElAlaGujDc = true;}
      else if(PZdkfDgTmM == GcBTXnGsTu){jtTouEVHay = true;}
      if(IWKCnwfojA == hptrfVodVC){kueVMAerNc = true;}
      if(FmneyCPsWt == kQShTYQBZq){cWgPHSfLKT = true;}
      if(eeQXTDwrER == yGVBNPYmMz){fHRapHkMaa = true;}
      while(hptrfVodVC == IWKCnwfojA){EHxiotRYmD = true;}
      while(kQShTYQBZq == kQShTYQBZq){PZpXCOizki = true;}
      while(yGVBNPYmMz == yGVBNPYmMz){YSLnJYMcEr = true;}
      if(gYCHRYeeCX == true){gYCHRYeeCX = false;}
      if(INHYozGuQG == true){INHYozGuQG = false;}
      if(metuNbUsdQ == true){metuNbUsdQ = false;}
      if(wCRWVLNLQt == true){wCRWVLNLQt = false;}
      if(tlzBhkzxMO == true){tlzBhkzxMO = false;}
      if(IdVFLCeGsp == true){IdVFLCeGsp = false;}
      if(ElAlaGujDc == true){ElAlaGujDc = false;}
      if(kueVMAerNc == true){kueVMAerNc = false;}
      if(cWgPHSfLKT == true){cWgPHSfLKT = false;}
      if(fHRapHkMaa == true){fHRapHkMaa = false;}
      if(oOticNyzsK == true){oOticNyzsK = false;}
      if(WmsPMhFjdI == true){WmsPMhFjdI = false;}
      if(ZjYjwdcEfE == true){ZjYjwdcEfE = false;}
      if(PSQlnNcymt == true){PSQlnNcymt = false;}
      if(TfRzwsNCNI == true){TfRzwsNCNI = false;}
      if(CBiRBEoKlz == true){CBiRBEoKlz = false;}
      if(jtTouEVHay == true){jtTouEVHay = false;}
      if(EHxiotRYmD == true){EHxiotRYmD = false;}
      if(PZpXCOizki == true){PZpXCOizki = false;}
      if(YSLnJYMcEr == true){YSLnJYMcEr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BEYHEJBQNZ
{ 
  void bJXgrgYMBP()
  { 
      bool NDnHzfqFWF = false;
      bool ANYqRFUABP = false;
      bool ZYmebBNByE = false;
      bool HaywfzldHz = false;
      bool TNcoqJHWAm = false;
      bool ZiztdnQIfy = false;
      bool SpHRxZPcLR = false;
      bool TqsCwLwxnS = false;
      bool spBKeXaDRq = false;
      bool icyJgcGKrQ = false;
      bool seLhShoxyR = false;
      bool rSUMEbnxmZ = false;
      bool yLKTiqsjUS = false;
      bool FkFWYOeTqw = false;
      bool hdFzzQHkEF = false;
      bool oIXSShUrzb = false;
      bool oFbfMHMynp = false;
      bool wUFqqUGKTR = false;
      bool iIfPdwMmDq = false;
      bool smTOGcBZmr = false;
      string qFaTyfjZzu;
      string MPuGgPqrAy;
      string SARbQxLrQs;
      string sqyUzUMEAp;
      string ZcUYCGofcP;
      string DrEsmpmzCA;
      string UqJGCVQZHM;
      string DmrJXpesYK;
      string IePAoBlEgI;
      string gMCzViTOWg;
      string oOYQMQztVx;
      string KtaqroaIQB;
      string iLryfpjrmn;
      string WQVrUsGznY;
      string BqijxllKGg;
      string ILxVxcVZkV;
      string fGHgasYhWz;
      string hbTqzrcIAs;
      string DZlGfKTzuq;
      string WgORstjBJE;
      if(qFaTyfjZzu == oOYQMQztVx){NDnHzfqFWF = true;}
      else if(oOYQMQztVx == qFaTyfjZzu){seLhShoxyR = true;}
      if(MPuGgPqrAy == KtaqroaIQB){ANYqRFUABP = true;}
      else if(KtaqroaIQB == MPuGgPqrAy){rSUMEbnxmZ = true;}
      if(SARbQxLrQs == iLryfpjrmn){ZYmebBNByE = true;}
      else if(iLryfpjrmn == SARbQxLrQs){yLKTiqsjUS = true;}
      if(sqyUzUMEAp == WQVrUsGznY){HaywfzldHz = true;}
      else if(WQVrUsGznY == sqyUzUMEAp){FkFWYOeTqw = true;}
      if(ZcUYCGofcP == BqijxllKGg){TNcoqJHWAm = true;}
      else if(BqijxllKGg == ZcUYCGofcP){hdFzzQHkEF = true;}
      if(DrEsmpmzCA == ILxVxcVZkV){ZiztdnQIfy = true;}
      else if(ILxVxcVZkV == DrEsmpmzCA){oIXSShUrzb = true;}
      if(UqJGCVQZHM == fGHgasYhWz){SpHRxZPcLR = true;}
      else if(fGHgasYhWz == UqJGCVQZHM){oFbfMHMynp = true;}
      if(DmrJXpesYK == hbTqzrcIAs){TqsCwLwxnS = true;}
      if(IePAoBlEgI == DZlGfKTzuq){spBKeXaDRq = true;}
      if(gMCzViTOWg == WgORstjBJE){icyJgcGKrQ = true;}
      while(hbTqzrcIAs == DmrJXpesYK){wUFqqUGKTR = true;}
      while(DZlGfKTzuq == DZlGfKTzuq){iIfPdwMmDq = true;}
      while(WgORstjBJE == WgORstjBJE){smTOGcBZmr = true;}
      if(NDnHzfqFWF == true){NDnHzfqFWF = false;}
      if(ANYqRFUABP == true){ANYqRFUABP = false;}
      if(ZYmebBNByE == true){ZYmebBNByE = false;}
      if(HaywfzldHz == true){HaywfzldHz = false;}
      if(TNcoqJHWAm == true){TNcoqJHWAm = false;}
      if(ZiztdnQIfy == true){ZiztdnQIfy = false;}
      if(SpHRxZPcLR == true){SpHRxZPcLR = false;}
      if(TqsCwLwxnS == true){TqsCwLwxnS = false;}
      if(spBKeXaDRq == true){spBKeXaDRq = false;}
      if(icyJgcGKrQ == true){icyJgcGKrQ = false;}
      if(seLhShoxyR == true){seLhShoxyR = false;}
      if(rSUMEbnxmZ == true){rSUMEbnxmZ = false;}
      if(yLKTiqsjUS == true){yLKTiqsjUS = false;}
      if(FkFWYOeTqw == true){FkFWYOeTqw = false;}
      if(hdFzzQHkEF == true){hdFzzQHkEF = false;}
      if(oIXSShUrzb == true){oIXSShUrzb = false;}
      if(oFbfMHMynp == true){oFbfMHMynp = false;}
      if(wUFqqUGKTR == true){wUFqqUGKTR = false;}
      if(iIfPdwMmDq == true){iIfPdwMmDq = false;}
      if(smTOGcBZmr == true){smTOGcBZmr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QLKLWPGBRC
{ 
  void jfRXRTXOxn()
  { 
      bool uEbrdcYFYM = false;
      bool zbdHFwghnz = false;
      bool fyVPJDokZZ = false;
      bool JBVtbZTjGn = false;
      bool bDebNAMuem = false;
      bool awFjxwiMha = false;
      bool mnfyDxFjfe = false;
      bool bwbzXcTsBJ = false;
      bool ptFlzMwlxe = false;
      bool qHCfAnXgYQ = false;
      bool ucOzKdUFLU = false;
      bool cpKXjshszq = false;
      bool ASmAnUtwzj = false;
      bool FmUjOMeGbU = false;
      bool qqabCBwduG = false;
      bool FdghPbpOKp = false;
      bool jYGbOpUZJW = false;
      bool OaQdzJqKxm = false;
      bool XPArdaFmUl = false;
      bool WPukjSjzNM = false;
      string wfNwyWStGF;
      string czaZVRLfEi;
      string NSBeQWxMzD;
      string aRPGGpCUAj;
      string BgzkyWqLfw;
      string jttZbddiea;
      string YGuCeKiTSf;
      string OqeThfSQft;
      string flgDTfXpec;
      string LSpYLulxFn;
      string mWrzgsOaru;
      string KNCjumZqiz;
      string lsopUuBGHm;
      string tVKqHJsgVa;
      string QxyjRxQFdX;
      string UtNGBtgCek;
      string qISFAnCLcl;
      string trVIhntFXW;
      string eubjRAIDoN;
      string bqCkiHesid;
      if(wfNwyWStGF == mWrzgsOaru){uEbrdcYFYM = true;}
      else if(mWrzgsOaru == wfNwyWStGF){ucOzKdUFLU = true;}
      if(czaZVRLfEi == KNCjumZqiz){zbdHFwghnz = true;}
      else if(KNCjumZqiz == czaZVRLfEi){cpKXjshszq = true;}
      if(NSBeQWxMzD == lsopUuBGHm){fyVPJDokZZ = true;}
      else if(lsopUuBGHm == NSBeQWxMzD){ASmAnUtwzj = true;}
      if(aRPGGpCUAj == tVKqHJsgVa){JBVtbZTjGn = true;}
      else if(tVKqHJsgVa == aRPGGpCUAj){FmUjOMeGbU = true;}
      if(BgzkyWqLfw == QxyjRxQFdX){bDebNAMuem = true;}
      else if(QxyjRxQFdX == BgzkyWqLfw){qqabCBwduG = true;}
      if(jttZbddiea == UtNGBtgCek){awFjxwiMha = true;}
      else if(UtNGBtgCek == jttZbddiea){FdghPbpOKp = true;}
      if(YGuCeKiTSf == qISFAnCLcl){mnfyDxFjfe = true;}
      else if(qISFAnCLcl == YGuCeKiTSf){jYGbOpUZJW = true;}
      if(OqeThfSQft == trVIhntFXW){bwbzXcTsBJ = true;}
      if(flgDTfXpec == eubjRAIDoN){ptFlzMwlxe = true;}
      if(LSpYLulxFn == bqCkiHesid){qHCfAnXgYQ = true;}
      while(trVIhntFXW == OqeThfSQft){OaQdzJqKxm = true;}
      while(eubjRAIDoN == eubjRAIDoN){XPArdaFmUl = true;}
      while(bqCkiHesid == bqCkiHesid){WPukjSjzNM = true;}
      if(uEbrdcYFYM == true){uEbrdcYFYM = false;}
      if(zbdHFwghnz == true){zbdHFwghnz = false;}
      if(fyVPJDokZZ == true){fyVPJDokZZ = false;}
      if(JBVtbZTjGn == true){JBVtbZTjGn = false;}
      if(bDebNAMuem == true){bDebNAMuem = false;}
      if(awFjxwiMha == true){awFjxwiMha = false;}
      if(mnfyDxFjfe == true){mnfyDxFjfe = false;}
      if(bwbzXcTsBJ == true){bwbzXcTsBJ = false;}
      if(ptFlzMwlxe == true){ptFlzMwlxe = false;}
      if(qHCfAnXgYQ == true){qHCfAnXgYQ = false;}
      if(ucOzKdUFLU == true){ucOzKdUFLU = false;}
      if(cpKXjshszq == true){cpKXjshszq = false;}
      if(ASmAnUtwzj == true){ASmAnUtwzj = false;}
      if(FmUjOMeGbU == true){FmUjOMeGbU = false;}
      if(qqabCBwduG == true){qqabCBwduG = false;}
      if(FdghPbpOKp == true){FdghPbpOKp = false;}
      if(jYGbOpUZJW == true){jYGbOpUZJW = false;}
      if(OaQdzJqKxm == true){OaQdzJqKxm = false;}
      if(XPArdaFmUl == true){XPArdaFmUl = false;}
      if(WPukjSjzNM == true){WPukjSjzNM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DECVQOQTTX
{ 
  void oGCeikMKKZ()
  { 
      bool muTVVpiolk = false;
      bool upEUdYOVhn = false;
      bool qGhYXYMChL = false;
      bool pYEISOBtOo = false;
      bool ElVRaAYpNa = false;
      bool dfHlCfMtxx = false;
      bool cfHZuWluBP = false;
      bool WUHrjFkQyW = false;
      bool zVnGhKQRGm = false;
      bool BGxRMXewVE = false;
      bool OcnyDIXPCx = false;
      bool uuwZxGrAqj = false;
      bool FToONPWoeL = false;
      bool ZnutIVgoDY = false;
      bool lBPIqGKWTF = false;
      bool fdEkytmZkn = false;
      bool lhjpWGABRb = false;
      bool YCxRyEEgWG = false;
      bool EAVZfwiJuN = false;
      bool hHEOmDQYkk = false;
      string IBkAtoFKei;
      string eOowTODXlV;
      string HsUJPzmabf;
      string AIkKxwZbIP;
      string DmwCAGiZGS;
      string GukZNPgakt;
      string CeizhWdezX;
      string obOVSUwSJJ;
      string QMUIYEWKwg;
      string PyqNNYDxTc;
      string cDZhdefOHs;
      string SNRbcoKZac;
      string zShRHpkBIt;
      string QzyffNlles;
      string XHDCOBgOkX;
      string NdWpcKVIam;
      string teGNbTOkuP;
      string CXtgErOeDF;
      string JVPjfmbHCV;
      string qdLrzsBpat;
      if(IBkAtoFKei == cDZhdefOHs){muTVVpiolk = true;}
      else if(cDZhdefOHs == IBkAtoFKei){OcnyDIXPCx = true;}
      if(eOowTODXlV == SNRbcoKZac){upEUdYOVhn = true;}
      else if(SNRbcoKZac == eOowTODXlV){uuwZxGrAqj = true;}
      if(HsUJPzmabf == zShRHpkBIt){qGhYXYMChL = true;}
      else if(zShRHpkBIt == HsUJPzmabf){FToONPWoeL = true;}
      if(AIkKxwZbIP == QzyffNlles){pYEISOBtOo = true;}
      else if(QzyffNlles == AIkKxwZbIP){ZnutIVgoDY = true;}
      if(DmwCAGiZGS == XHDCOBgOkX){ElVRaAYpNa = true;}
      else if(XHDCOBgOkX == DmwCAGiZGS){lBPIqGKWTF = true;}
      if(GukZNPgakt == NdWpcKVIam){dfHlCfMtxx = true;}
      else if(NdWpcKVIam == GukZNPgakt){fdEkytmZkn = true;}
      if(CeizhWdezX == teGNbTOkuP){cfHZuWluBP = true;}
      else if(teGNbTOkuP == CeizhWdezX){lhjpWGABRb = true;}
      if(obOVSUwSJJ == CXtgErOeDF){WUHrjFkQyW = true;}
      if(QMUIYEWKwg == JVPjfmbHCV){zVnGhKQRGm = true;}
      if(PyqNNYDxTc == qdLrzsBpat){BGxRMXewVE = true;}
      while(CXtgErOeDF == obOVSUwSJJ){YCxRyEEgWG = true;}
      while(JVPjfmbHCV == JVPjfmbHCV){EAVZfwiJuN = true;}
      while(qdLrzsBpat == qdLrzsBpat){hHEOmDQYkk = true;}
      if(muTVVpiolk == true){muTVVpiolk = false;}
      if(upEUdYOVhn == true){upEUdYOVhn = false;}
      if(qGhYXYMChL == true){qGhYXYMChL = false;}
      if(pYEISOBtOo == true){pYEISOBtOo = false;}
      if(ElVRaAYpNa == true){ElVRaAYpNa = false;}
      if(dfHlCfMtxx == true){dfHlCfMtxx = false;}
      if(cfHZuWluBP == true){cfHZuWluBP = false;}
      if(WUHrjFkQyW == true){WUHrjFkQyW = false;}
      if(zVnGhKQRGm == true){zVnGhKQRGm = false;}
      if(BGxRMXewVE == true){BGxRMXewVE = false;}
      if(OcnyDIXPCx == true){OcnyDIXPCx = false;}
      if(uuwZxGrAqj == true){uuwZxGrAqj = false;}
      if(FToONPWoeL == true){FToONPWoeL = false;}
      if(ZnutIVgoDY == true){ZnutIVgoDY = false;}
      if(lBPIqGKWTF == true){lBPIqGKWTF = false;}
      if(fdEkytmZkn == true){fdEkytmZkn = false;}
      if(lhjpWGABRb == true){lhjpWGABRb = false;}
      if(YCxRyEEgWG == true){YCxRyEEgWG = false;}
      if(EAVZfwiJuN == true){EAVZfwiJuN = false;}
      if(hHEOmDQYkk == true){hHEOmDQYkk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TSFAVKJBUE
{ 
  void YUHoqLpFjn()
  { 
      bool fpDELxjdCO = false;
      bool FLBZlFkUnd = false;
      bool bpZxYXWmzx = false;
      bool eaMVMOlByP = false;
      bool dHnxOSUTBd = false;
      bool ZReuWpPGen = false;
      bool aweEjdzfMX = false;
      bool TjWXzTBbiF = false;
      bool CDkUXNwRyV = false;
      bool yeVJohciNj = false;
      bool SnGdKptGuC = false;
      bool omWYkXKJgV = false;
      bool hhhpZnNNiR = false;
      bool qROzmOwHKh = false;
      bool SoVugLIxXR = false;
      bool XSCqBkGQDV = false;
      bool bfWdLWYXlW = false;
      bool aCzyDrLlIN = false;
      bool eQpRsXOWxB = false;
      bool HfEnFlSrjJ = false;
      string fZZfnDdeDq;
      string UOmTFynJsa;
      string WuSeMZOOUG;
      string VUyxKDFXEh;
      string HdWsResObQ;
      string VLGyLjHtSN;
      string nPKxVzPpIC;
      string rQEKTsXYMh;
      string gAlDjJOAkZ;
      string uKFptqSZWS;
      string ODFZXFGweS;
      string MhhjgncHML;
      string kPEiGgKOQb;
      string ZyBtSctMed;
      string DSVSNMcUIG;
      string OLMKgzyWSq;
      string ureCrNfmRE;
      string tQbhIStlUs;
      string EoGJNOlpMT;
      string eWsniLmSZz;
      if(fZZfnDdeDq == ODFZXFGweS){fpDELxjdCO = true;}
      else if(ODFZXFGweS == fZZfnDdeDq){SnGdKptGuC = true;}
      if(UOmTFynJsa == MhhjgncHML){FLBZlFkUnd = true;}
      else if(MhhjgncHML == UOmTFynJsa){omWYkXKJgV = true;}
      if(WuSeMZOOUG == kPEiGgKOQb){bpZxYXWmzx = true;}
      else if(kPEiGgKOQb == WuSeMZOOUG){hhhpZnNNiR = true;}
      if(VUyxKDFXEh == ZyBtSctMed){eaMVMOlByP = true;}
      else if(ZyBtSctMed == VUyxKDFXEh){qROzmOwHKh = true;}
      if(HdWsResObQ == DSVSNMcUIG){dHnxOSUTBd = true;}
      else if(DSVSNMcUIG == HdWsResObQ){SoVugLIxXR = true;}
      if(VLGyLjHtSN == OLMKgzyWSq){ZReuWpPGen = true;}
      else if(OLMKgzyWSq == VLGyLjHtSN){XSCqBkGQDV = true;}
      if(nPKxVzPpIC == ureCrNfmRE){aweEjdzfMX = true;}
      else if(ureCrNfmRE == nPKxVzPpIC){bfWdLWYXlW = true;}
      if(rQEKTsXYMh == tQbhIStlUs){TjWXzTBbiF = true;}
      if(gAlDjJOAkZ == EoGJNOlpMT){CDkUXNwRyV = true;}
      if(uKFptqSZWS == eWsniLmSZz){yeVJohciNj = true;}
      while(tQbhIStlUs == rQEKTsXYMh){aCzyDrLlIN = true;}
      while(EoGJNOlpMT == EoGJNOlpMT){eQpRsXOWxB = true;}
      while(eWsniLmSZz == eWsniLmSZz){HfEnFlSrjJ = true;}
      if(fpDELxjdCO == true){fpDELxjdCO = false;}
      if(FLBZlFkUnd == true){FLBZlFkUnd = false;}
      if(bpZxYXWmzx == true){bpZxYXWmzx = false;}
      if(eaMVMOlByP == true){eaMVMOlByP = false;}
      if(dHnxOSUTBd == true){dHnxOSUTBd = false;}
      if(ZReuWpPGen == true){ZReuWpPGen = false;}
      if(aweEjdzfMX == true){aweEjdzfMX = false;}
      if(TjWXzTBbiF == true){TjWXzTBbiF = false;}
      if(CDkUXNwRyV == true){CDkUXNwRyV = false;}
      if(yeVJohciNj == true){yeVJohciNj = false;}
      if(SnGdKptGuC == true){SnGdKptGuC = false;}
      if(omWYkXKJgV == true){omWYkXKJgV = false;}
      if(hhhpZnNNiR == true){hhhpZnNNiR = false;}
      if(qROzmOwHKh == true){qROzmOwHKh = false;}
      if(SoVugLIxXR == true){SoVugLIxXR = false;}
      if(XSCqBkGQDV == true){XSCqBkGQDV = false;}
      if(bfWdLWYXlW == true){bfWdLWYXlW = false;}
      if(aCzyDrLlIN == true){aCzyDrLlIN = false;}
      if(eQpRsXOWxB == true){eQpRsXOWxB = false;}
      if(HfEnFlSrjJ == true){HfEnFlSrjJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMCLXQHOFM
{ 
  void xkMEZjWROH()
  { 
      bool IDLbMZVEUR = false;
      bool HDLYnSEHBL = false;
      bool AdACnKKcTl = false;
      bool kDJAMMXouD = false;
      bool rEoSihPnWK = false;
      bool JimLKdCJmB = false;
      bool PsjifEtLMa = false;
      bool uPMxTuogTF = false;
      bool uVFJcCPxoh = false;
      bool KOBsnzUGmd = false;
      bool mEbwOsVprP = false;
      bool oUogGsnZGd = false;
      bool oxVdQgOSJU = false;
      bool ahtoSqtJti = false;
      bool fYEYsoYTmt = false;
      bool KtAIophxfh = false;
      bool eDgXnGaAOP = false;
      bool zeeWxPrxka = false;
      bool HtfOJghkAc = false;
      bool IwcMDcrfjl = false;
      string iQSqUFPZBj;
      string sYTSRoNxEe;
      string iYFsCkWRuz;
      string ailnzedfhQ;
      string athQlzwWyU;
      string ZCILoKKYoj;
      string ixeCJJmeTl;
      string KgPmEopnHD;
      string nASZYXaazn;
      string TFqxhcPfHc;
      string LQCLJrmUGA;
      string TWQkwieEdk;
      string hLffSFpRFb;
      string ZKgeqWxGQf;
      string jFTyTxoFBy;
      string xKBVtAkWsE;
      string CVOeaIoktZ;
      string lXnxAbrgLU;
      string QjQHdOIKkq;
      string kaNLcOqoXL;
      if(iQSqUFPZBj == LQCLJrmUGA){IDLbMZVEUR = true;}
      else if(LQCLJrmUGA == iQSqUFPZBj){mEbwOsVprP = true;}
      if(sYTSRoNxEe == TWQkwieEdk){HDLYnSEHBL = true;}
      else if(TWQkwieEdk == sYTSRoNxEe){oUogGsnZGd = true;}
      if(iYFsCkWRuz == hLffSFpRFb){AdACnKKcTl = true;}
      else if(hLffSFpRFb == iYFsCkWRuz){oxVdQgOSJU = true;}
      if(ailnzedfhQ == ZKgeqWxGQf){kDJAMMXouD = true;}
      else if(ZKgeqWxGQf == ailnzedfhQ){ahtoSqtJti = true;}
      if(athQlzwWyU == jFTyTxoFBy){rEoSihPnWK = true;}
      else if(jFTyTxoFBy == athQlzwWyU){fYEYsoYTmt = true;}
      if(ZCILoKKYoj == xKBVtAkWsE){JimLKdCJmB = true;}
      else if(xKBVtAkWsE == ZCILoKKYoj){KtAIophxfh = true;}
      if(ixeCJJmeTl == CVOeaIoktZ){PsjifEtLMa = true;}
      else if(CVOeaIoktZ == ixeCJJmeTl){eDgXnGaAOP = true;}
      if(KgPmEopnHD == lXnxAbrgLU){uPMxTuogTF = true;}
      if(nASZYXaazn == QjQHdOIKkq){uVFJcCPxoh = true;}
      if(TFqxhcPfHc == kaNLcOqoXL){KOBsnzUGmd = true;}
      while(lXnxAbrgLU == KgPmEopnHD){zeeWxPrxka = true;}
      while(QjQHdOIKkq == QjQHdOIKkq){HtfOJghkAc = true;}
      while(kaNLcOqoXL == kaNLcOqoXL){IwcMDcrfjl = true;}
      if(IDLbMZVEUR == true){IDLbMZVEUR = false;}
      if(HDLYnSEHBL == true){HDLYnSEHBL = false;}
      if(AdACnKKcTl == true){AdACnKKcTl = false;}
      if(kDJAMMXouD == true){kDJAMMXouD = false;}
      if(rEoSihPnWK == true){rEoSihPnWK = false;}
      if(JimLKdCJmB == true){JimLKdCJmB = false;}
      if(PsjifEtLMa == true){PsjifEtLMa = false;}
      if(uPMxTuogTF == true){uPMxTuogTF = false;}
      if(uVFJcCPxoh == true){uVFJcCPxoh = false;}
      if(KOBsnzUGmd == true){KOBsnzUGmd = false;}
      if(mEbwOsVprP == true){mEbwOsVprP = false;}
      if(oUogGsnZGd == true){oUogGsnZGd = false;}
      if(oxVdQgOSJU == true){oxVdQgOSJU = false;}
      if(ahtoSqtJti == true){ahtoSqtJti = false;}
      if(fYEYsoYTmt == true){fYEYsoYTmt = false;}
      if(KtAIophxfh == true){KtAIophxfh = false;}
      if(eDgXnGaAOP == true){eDgXnGaAOP = false;}
      if(zeeWxPrxka == true){zeeWxPrxka = false;}
      if(HtfOJghkAc == true){HtfOJghkAc = false;}
      if(IwcMDcrfjl == true){IwcMDcrfjl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LWGMMLIYQT
{ 
  void jQZWwyoxAo()
  { 
      bool HkUCqtCCJA = false;
      bool ZGLEoRCRhJ = false;
      bool PDqLofoDwc = false;
      bool XbOkBkdbVe = false;
      bool bjhixJhbrt = false;
      bool MJaFtEsJNL = false;
      bool FzFgcxqaCD = false;
      bool mZuCheVIOf = false;
      bool xMLCPOBIqw = false;
      bool rUOKYbeAGA = false;
      bool RHZnHmNXXO = false;
      bool ikthNsnDQN = false;
      bool uiiGLSKjcF = false;
      bool AUBONpmWtc = false;
      bool BdjbMGZgwf = false;
      bool najsEhXSbo = false;
      bool bctSOOjfTX = false;
      bool GQImMRyGsF = false;
      bool rdnxRYjIJe = false;
      bool RTuFAXiRNy = false;
      string gDYrzriJhq;
      string fEqjSfPkNo;
      string WheWcaAypw;
      string kGlAOOZmkl;
      string RljuffIjcB;
      string xUmWpzXCPX;
      string rjTkFYRqVD;
      string GbAaXkxjpw;
      string SPUoyQSPJO;
      string qXXNtgSypG;
      string NROZtVTMyF;
      string BnLSFbPeln;
      string FCgHMiEmgp;
      string RzsjiABttc;
      string wGQDMCLEHS;
      string QmLBALjGNL;
      string QgfHnCtaiF;
      string aVkJrzkduJ;
      string WzeNZdmqjX;
      string PtghMOaIPJ;
      if(gDYrzriJhq == NROZtVTMyF){HkUCqtCCJA = true;}
      else if(NROZtVTMyF == gDYrzriJhq){RHZnHmNXXO = true;}
      if(fEqjSfPkNo == BnLSFbPeln){ZGLEoRCRhJ = true;}
      else if(BnLSFbPeln == fEqjSfPkNo){ikthNsnDQN = true;}
      if(WheWcaAypw == FCgHMiEmgp){PDqLofoDwc = true;}
      else if(FCgHMiEmgp == WheWcaAypw){uiiGLSKjcF = true;}
      if(kGlAOOZmkl == RzsjiABttc){XbOkBkdbVe = true;}
      else if(RzsjiABttc == kGlAOOZmkl){AUBONpmWtc = true;}
      if(RljuffIjcB == wGQDMCLEHS){bjhixJhbrt = true;}
      else if(wGQDMCLEHS == RljuffIjcB){BdjbMGZgwf = true;}
      if(xUmWpzXCPX == QmLBALjGNL){MJaFtEsJNL = true;}
      else if(QmLBALjGNL == xUmWpzXCPX){najsEhXSbo = true;}
      if(rjTkFYRqVD == QgfHnCtaiF){FzFgcxqaCD = true;}
      else if(QgfHnCtaiF == rjTkFYRqVD){bctSOOjfTX = true;}
      if(GbAaXkxjpw == aVkJrzkduJ){mZuCheVIOf = true;}
      if(SPUoyQSPJO == WzeNZdmqjX){xMLCPOBIqw = true;}
      if(qXXNtgSypG == PtghMOaIPJ){rUOKYbeAGA = true;}
      while(aVkJrzkduJ == GbAaXkxjpw){GQImMRyGsF = true;}
      while(WzeNZdmqjX == WzeNZdmqjX){rdnxRYjIJe = true;}
      while(PtghMOaIPJ == PtghMOaIPJ){RTuFAXiRNy = true;}
      if(HkUCqtCCJA == true){HkUCqtCCJA = false;}
      if(ZGLEoRCRhJ == true){ZGLEoRCRhJ = false;}
      if(PDqLofoDwc == true){PDqLofoDwc = false;}
      if(XbOkBkdbVe == true){XbOkBkdbVe = false;}
      if(bjhixJhbrt == true){bjhixJhbrt = false;}
      if(MJaFtEsJNL == true){MJaFtEsJNL = false;}
      if(FzFgcxqaCD == true){FzFgcxqaCD = false;}
      if(mZuCheVIOf == true){mZuCheVIOf = false;}
      if(xMLCPOBIqw == true){xMLCPOBIqw = false;}
      if(rUOKYbeAGA == true){rUOKYbeAGA = false;}
      if(RHZnHmNXXO == true){RHZnHmNXXO = false;}
      if(ikthNsnDQN == true){ikthNsnDQN = false;}
      if(uiiGLSKjcF == true){uiiGLSKjcF = false;}
      if(AUBONpmWtc == true){AUBONpmWtc = false;}
      if(BdjbMGZgwf == true){BdjbMGZgwf = false;}
      if(najsEhXSbo == true){najsEhXSbo = false;}
      if(bctSOOjfTX == true){bctSOOjfTX = false;}
      if(GQImMRyGsF == true){GQImMRyGsF = false;}
      if(rdnxRYjIJe == true){rdnxRYjIJe = false;}
      if(RTuFAXiRNy == true){RTuFAXiRNy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CAFFQRFSCE
{ 
  void GioUhWOOaz()
  { 
      bool QoEQtdsZcf = false;
      bool hHThtOQIeF = false;
      bool eIRFTlrqBc = false;
      bool foHEQpbNDZ = false;
      bool KjrFWRzHlY = false;
      bool XNOhtIWywH = false;
      bool lCXzzszPRE = false;
      bool lCFFttQMiB = false;
      bool mjEbFSaZKI = false;
      bool TcQunILrFd = false;
      bool SiohmVHJmz = false;
      bool qKPuTBxutf = false;
      bool SYFIkIkJQk = false;
      bool hYGEiDtWoi = false;
      bool LQlKQIMVam = false;
      bool KQxYLsdgxd = false;
      bool kxrBQSELLQ = false;
      bool GaGLUBltqb = false;
      bool wOhdZRagso = false;
      bool ZNYLxNXksy = false;
      string hrVKpoDeQB;
      string QmxbSPfBRG;
      string yDiMYtNNtP;
      string dDuZHzajdx;
      string pgoUbWTINn;
      string nIWRwdIJkw;
      string aokAWMqWUT;
      string owWTQRONjC;
      string ZEAFbUgdcc;
      string pRzgVAwnxP;
      string exntyrkDAe;
      string PuYiWWneYC;
      string fNsqcXxoxQ;
      string UZQUWcQGHi;
      string jcdxNurPKz;
      string LQPuiRDxQZ;
      string uuGjJodDLs;
      string FhXoRDiuch;
      string egexEEKUkF;
      string ZTpgnnWtmY;
      if(hrVKpoDeQB == exntyrkDAe){QoEQtdsZcf = true;}
      else if(exntyrkDAe == hrVKpoDeQB){SiohmVHJmz = true;}
      if(QmxbSPfBRG == PuYiWWneYC){hHThtOQIeF = true;}
      else if(PuYiWWneYC == QmxbSPfBRG){qKPuTBxutf = true;}
      if(yDiMYtNNtP == fNsqcXxoxQ){eIRFTlrqBc = true;}
      else if(fNsqcXxoxQ == yDiMYtNNtP){SYFIkIkJQk = true;}
      if(dDuZHzajdx == UZQUWcQGHi){foHEQpbNDZ = true;}
      else if(UZQUWcQGHi == dDuZHzajdx){hYGEiDtWoi = true;}
      if(pgoUbWTINn == jcdxNurPKz){KjrFWRzHlY = true;}
      else if(jcdxNurPKz == pgoUbWTINn){LQlKQIMVam = true;}
      if(nIWRwdIJkw == LQPuiRDxQZ){XNOhtIWywH = true;}
      else if(LQPuiRDxQZ == nIWRwdIJkw){KQxYLsdgxd = true;}
      if(aokAWMqWUT == uuGjJodDLs){lCXzzszPRE = true;}
      else if(uuGjJodDLs == aokAWMqWUT){kxrBQSELLQ = true;}
      if(owWTQRONjC == FhXoRDiuch){lCFFttQMiB = true;}
      if(ZEAFbUgdcc == egexEEKUkF){mjEbFSaZKI = true;}
      if(pRzgVAwnxP == ZTpgnnWtmY){TcQunILrFd = true;}
      while(FhXoRDiuch == owWTQRONjC){GaGLUBltqb = true;}
      while(egexEEKUkF == egexEEKUkF){wOhdZRagso = true;}
      while(ZTpgnnWtmY == ZTpgnnWtmY){ZNYLxNXksy = true;}
      if(QoEQtdsZcf == true){QoEQtdsZcf = false;}
      if(hHThtOQIeF == true){hHThtOQIeF = false;}
      if(eIRFTlrqBc == true){eIRFTlrqBc = false;}
      if(foHEQpbNDZ == true){foHEQpbNDZ = false;}
      if(KjrFWRzHlY == true){KjrFWRzHlY = false;}
      if(XNOhtIWywH == true){XNOhtIWywH = false;}
      if(lCXzzszPRE == true){lCXzzszPRE = false;}
      if(lCFFttQMiB == true){lCFFttQMiB = false;}
      if(mjEbFSaZKI == true){mjEbFSaZKI = false;}
      if(TcQunILrFd == true){TcQunILrFd = false;}
      if(SiohmVHJmz == true){SiohmVHJmz = false;}
      if(qKPuTBxutf == true){qKPuTBxutf = false;}
      if(SYFIkIkJQk == true){SYFIkIkJQk = false;}
      if(hYGEiDtWoi == true){hYGEiDtWoi = false;}
      if(LQlKQIMVam == true){LQlKQIMVam = false;}
      if(KQxYLsdgxd == true){KQxYLsdgxd = false;}
      if(kxrBQSELLQ == true){kxrBQSELLQ = false;}
      if(GaGLUBltqb == true){GaGLUBltqb = false;}
      if(wOhdZRagso == true){wOhdZRagso = false;}
      if(ZNYLxNXksy == true){ZNYLxNXksy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ATTUUWTEIE
{ 
  void zmJusywBln()
  { 
      bool VUrNCkgmjf = false;
      bool jLhMICxhRP = false;
      bool gIniUnCyDk = false;
      bool yIBgkiHSTh = false;
      bool dxdIEeBGNP = false;
      bool OAtKwMgJrO = false;
      bool iijzhaJBbY = false;
      bool ueOilidedo = false;
      bool mujmVxOpjX = false;
      bool CxZFztNead = false;
      bool UAdoUjlKYN = false;
      bool iCeDbmywdj = false;
      bool MTQEWxEJjq = false;
      bool UzDATmQuSk = false;
      bool KDRVnzSWdL = false;
      bool wQBpRBiZRX = false;
      bool fcagrjzein = false;
      bool WDdrZICuPW = false;
      bool egfYuEyMhS = false;
      bool EqctFhbjcE = false;
      string doCCNEADbr;
      string ToMaJgNRLY;
      string dXDhSdikyz;
      string dIMuOyzQys;
      string gLckuAiKdy;
      string NCTDGGlTjj;
      string VPEcOKbRML;
      string hwSSqStSmR;
      string tXGAlaoJnH;
      string LegNWQGAVj;
      string XQxSQQiALm;
      string LTgRoxJEpn;
      string VScFzDOFua;
      string MtwDtdamjU;
      string qnxBuryPYZ;
      string HBJhNFmrTM;
      string BdEkaRWcXL;
      string WVUVxhVbKG;
      string EzfVTKkOon;
      string piTWSMiMad;
      if(doCCNEADbr == XQxSQQiALm){VUrNCkgmjf = true;}
      else if(XQxSQQiALm == doCCNEADbr){UAdoUjlKYN = true;}
      if(ToMaJgNRLY == LTgRoxJEpn){jLhMICxhRP = true;}
      else if(LTgRoxJEpn == ToMaJgNRLY){iCeDbmywdj = true;}
      if(dXDhSdikyz == VScFzDOFua){gIniUnCyDk = true;}
      else if(VScFzDOFua == dXDhSdikyz){MTQEWxEJjq = true;}
      if(dIMuOyzQys == MtwDtdamjU){yIBgkiHSTh = true;}
      else if(MtwDtdamjU == dIMuOyzQys){UzDATmQuSk = true;}
      if(gLckuAiKdy == qnxBuryPYZ){dxdIEeBGNP = true;}
      else if(qnxBuryPYZ == gLckuAiKdy){KDRVnzSWdL = true;}
      if(NCTDGGlTjj == HBJhNFmrTM){OAtKwMgJrO = true;}
      else if(HBJhNFmrTM == NCTDGGlTjj){wQBpRBiZRX = true;}
      if(VPEcOKbRML == BdEkaRWcXL){iijzhaJBbY = true;}
      else if(BdEkaRWcXL == VPEcOKbRML){fcagrjzein = true;}
      if(hwSSqStSmR == WVUVxhVbKG){ueOilidedo = true;}
      if(tXGAlaoJnH == EzfVTKkOon){mujmVxOpjX = true;}
      if(LegNWQGAVj == piTWSMiMad){CxZFztNead = true;}
      while(WVUVxhVbKG == hwSSqStSmR){WDdrZICuPW = true;}
      while(EzfVTKkOon == EzfVTKkOon){egfYuEyMhS = true;}
      while(piTWSMiMad == piTWSMiMad){EqctFhbjcE = true;}
      if(VUrNCkgmjf == true){VUrNCkgmjf = false;}
      if(jLhMICxhRP == true){jLhMICxhRP = false;}
      if(gIniUnCyDk == true){gIniUnCyDk = false;}
      if(yIBgkiHSTh == true){yIBgkiHSTh = false;}
      if(dxdIEeBGNP == true){dxdIEeBGNP = false;}
      if(OAtKwMgJrO == true){OAtKwMgJrO = false;}
      if(iijzhaJBbY == true){iijzhaJBbY = false;}
      if(ueOilidedo == true){ueOilidedo = false;}
      if(mujmVxOpjX == true){mujmVxOpjX = false;}
      if(CxZFztNead == true){CxZFztNead = false;}
      if(UAdoUjlKYN == true){UAdoUjlKYN = false;}
      if(iCeDbmywdj == true){iCeDbmywdj = false;}
      if(MTQEWxEJjq == true){MTQEWxEJjq = false;}
      if(UzDATmQuSk == true){UzDATmQuSk = false;}
      if(KDRVnzSWdL == true){KDRVnzSWdL = false;}
      if(wQBpRBiZRX == true){wQBpRBiZRX = false;}
      if(fcagrjzein == true){fcagrjzein = false;}
      if(WDdrZICuPW == true){WDdrZICuPW = false;}
      if(egfYuEyMhS == true){egfYuEyMhS = false;}
      if(EqctFhbjcE == true){EqctFhbjcE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AGJATQFIUL
{ 
  void kaFsDkynYS()
  { 
      bool OPRrWPLZhD = false;
      bool DVFimIdUfS = false;
      bool wpzhGHUInP = false;
      bool DryQOrRmZi = false;
      bool gsVWbnkxqH = false;
      bool WxmdLXQjkO = false;
      bool uClSzKXnUu = false;
      bool pquxlDTbFS = false;
      bool WWRfrGFTFp = false;
      bool ahCKneHDWR = false;
      bool QwcwRfBorI = false;
      bool EodRrXjFZs = false;
      bool FDieTIokIG = false;
      bool uQEnBatVOM = false;
      bool EPbwkkDjSQ = false;
      bool uBddMNNybI = false;
      bool pQfkMnjpQQ = false;
      bool cNqMnoblsh = false;
      bool FESrLslZbn = false;
      bool NwtFVnipjx = false;
      string LOpWceJIFf;
      string kTlbWgSiLS;
      string yInkwlNbab;
      string wKPUpfTOrF;
      string rtTKFcnOmG;
      string LmpVHCaEaq;
      string RhhcjZERkp;
      string MDpGZEodeS;
      string yyoTQITtMm;
      string FOnBnKMqaf;
      string YWcwsHxjuD;
      string NxYHrSsNMb;
      string GKFykyPnRP;
      string qxDztbUrZI;
      string KjyJYIofJU;
      string QydzYOReLu;
      string rJReLQtYNQ;
      string yBmEQVLuZc;
      string IjewyrTDZe;
      string JpfdPBRSxI;
      if(LOpWceJIFf == YWcwsHxjuD){OPRrWPLZhD = true;}
      else if(YWcwsHxjuD == LOpWceJIFf){QwcwRfBorI = true;}
      if(kTlbWgSiLS == NxYHrSsNMb){DVFimIdUfS = true;}
      else if(NxYHrSsNMb == kTlbWgSiLS){EodRrXjFZs = true;}
      if(yInkwlNbab == GKFykyPnRP){wpzhGHUInP = true;}
      else if(GKFykyPnRP == yInkwlNbab){FDieTIokIG = true;}
      if(wKPUpfTOrF == qxDztbUrZI){DryQOrRmZi = true;}
      else if(qxDztbUrZI == wKPUpfTOrF){uQEnBatVOM = true;}
      if(rtTKFcnOmG == KjyJYIofJU){gsVWbnkxqH = true;}
      else if(KjyJYIofJU == rtTKFcnOmG){EPbwkkDjSQ = true;}
      if(LmpVHCaEaq == QydzYOReLu){WxmdLXQjkO = true;}
      else if(QydzYOReLu == LmpVHCaEaq){uBddMNNybI = true;}
      if(RhhcjZERkp == rJReLQtYNQ){uClSzKXnUu = true;}
      else if(rJReLQtYNQ == RhhcjZERkp){pQfkMnjpQQ = true;}
      if(MDpGZEodeS == yBmEQVLuZc){pquxlDTbFS = true;}
      if(yyoTQITtMm == IjewyrTDZe){WWRfrGFTFp = true;}
      if(FOnBnKMqaf == JpfdPBRSxI){ahCKneHDWR = true;}
      while(yBmEQVLuZc == MDpGZEodeS){cNqMnoblsh = true;}
      while(IjewyrTDZe == IjewyrTDZe){FESrLslZbn = true;}
      while(JpfdPBRSxI == JpfdPBRSxI){NwtFVnipjx = true;}
      if(OPRrWPLZhD == true){OPRrWPLZhD = false;}
      if(DVFimIdUfS == true){DVFimIdUfS = false;}
      if(wpzhGHUInP == true){wpzhGHUInP = false;}
      if(DryQOrRmZi == true){DryQOrRmZi = false;}
      if(gsVWbnkxqH == true){gsVWbnkxqH = false;}
      if(WxmdLXQjkO == true){WxmdLXQjkO = false;}
      if(uClSzKXnUu == true){uClSzKXnUu = false;}
      if(pquxlDTbFS == true){pquxlDTbFS = false;}
      if(WWRfrGFTFp == true){WWRfrGFTFp = false;}
      if(ahCKneHDWR == true){ahCKneHDWR = false;}
      if(QwcwRfBorI == true){QwcwRfBorI = false;}
      if(EodRrXjFZs == true){EodRrXjFZs = false;}
      if(FDieTIokIG == true){FDieTIokIG = false;}
      if(uQEnBatVOM == true){uQEnBatVOM = false;}
      if(EPbwkkDjSQ == true){EPbwkkDjSQ = false;}
      if(uBddMNNybI == true){uBddMNNybI = false;}
      if(pQfkMnjpQQ == true){pQfkMnjpQQ = false;}
      if(cNqMnoblsh == true){cNqMnoblsh = false;}
      if(FESrLslZbn == true){FESrLslZbn = false;}
      if(NwtFVnipjx == true){NwtFVnipjx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXVOJHFJFF
{ 
  void GqIhORaFDm()
  { 
      bool NmYrXukbSl = false;
      bool hbQrYacPQC = false;
      bool ECWQzTIJUu = false;
      bool tBYNEJCKAT = false;
      bool dpOPdXFNHX = false;
      bool hTsnpLPHrD = false;
      bool laHWrgCCmP = false;
      bool YSOwXOmHmb = false;
      bool NuCwMaHkXs = false;
      bool stSwgDiqXw = false;
      bool VDZqzPEwPa = false;
      bool XIUQoqYKKQ = false;
      bool YRdtWeARPU = false;
      bool fujpFKUKxx = false;
      bool VLUwVkYBHo = false;
      bool dXgGXDYfUU = false;
      bool PlfuubXeKe = false;
      bool WONNuMwhXl = false;
      bool FyKaqIOdSB = false;
      bool lnpcgieZBs = false;
      string jgehbQpwkk;
      string FTXKKrmYRh;
      string zMNCwVgSXd;
      string WGVgcHfXrh;
      string PqbjRtJibq;
      string uGJYPXTblF;
      string iWYGNzyqgC;
      string MOgjSIjckC;
      string LxqfiQxwQF;
      string mDllyrSUVS;
      string uSBZdfZYGH;
      string mpqiskfrXx;
      string BBZbOIctka;
      string oPGSGsuQCC;
      string pXpJSxMCrM;
      string LaxYQtrZKV;
      string CenfRWiYcA;
      string oPpUGdLQJR;
      string waCXPOSgBM;
      string AVGfzLiJqu;
      if(jgehbQpwkk == uSBZdfZYGH){NmYrXukbSl = true;}
      else if(uSBZdfZYGH == jgehbQpwkk){VDZqzPEwPa = true;}
      if(FTXKKrmYRh == mpqiskfrXx){hbQrYacPQC = true;}
      else if(mpqiskfrXx == FTXKKrmYRh){XIUQoqYKKQ = true;}
      if(zMNCwVgSXd == BBZbOIctka){ECWQzTIJUu = true;}
      else if(BBZbOIctka == zMNCwVgSXd){YRdtWeARPU = true;}
      if(WGVgcHfXrh == oPGSGsuQCC){tBYNEJCKAT = true;}
      else if(oPGSGsuQCC == WGVgcHfXrh){fujpFKUKxx = true;}
      if(PqbjRtJibq == pXpJSxMCrM){dpOPdXFNHX = true;}
      else if(pXpJSxMCrM == PqbjRtJibq){VLUwVkYBHo = true;}
      if(uGJYPXTblF == LaxYQtrZKV){hTsnpLPHrD = true;}
      else if(LaxYQtrZKV == uGJYPXTblF){dXgGXDYfUU = true;}
      if(iWYGNzyqgC == CenfRWiYcA){laHWrgCCmP = true;}
      else if(CenfRWiYcA == iWYGNzyqgC){PlfuubXeKe = true;}
      if(MOgjSIjckC == oPpUGdLQJR){YSOwXOmHmb = true;}
      if(LxqfiQxwQF == waCXPOSgBM){NuCwMaHkXs = true;}
      if(mDllyrSUVS == AVGfzLiJqu){stSwgDiqXw = true;}
      while(oPpUGdLQJR == MOgjSIjckC){WONNuMwhXl = true;}
      while(waCXPOSgBM == waCXPOSgBM){FyKaqIOdSB = true;}
      while(AVGfzLiJqu == AVGfzLiJqu){lnpcgieZBs = true;}
      if(NmYrXukbSl == true){NmYrXukbSl = false;}
      if(hbQrYacPQC == true){hbQrYacPQC = false;}
      if(ECWQzTIJUu == true){ECWQzTIJUu = false;}
      if(tBYNEJCKAT == true){tBYNEJCKAT = false;}
      if(dpOPdXFNHX == true){dpOPdXFNHX = false;}
      if(hTsnpLPHrD == true){hTsnpLPHrD = false;}
      if(laHWrgCCmP == true){laHWrgCCmP = false;}
      if(YSOwXOmHmb == true){YSOwXOmHmb = false;}
      if(NuCwMaHkXs == true){NuCwMaHkXs = false;}
      if(stSwgDiqXw == true){stSwgDiqXw = false;}
      if(VDZqzPEwPa == true){VDZqzPEwPa = false;}
      if(XIUQoqYKKQ == true){XIUQoqYKKQ = false;}
      if(YRdtWeARPU == true){YRdtWeARPU = false;}
      if(fujpFKUKxx == true){fujpFKUKxx = false;}
      if(VLUwVkYBHo == true){VLUwVkYBHo = false;}
      if(dXgGXDYfUU == true){dXgGXDYfUU = false;}
      if(PlfuubXeKe == true){PlfuubXeKe = false;}
      if(WONNuMwhXl == true){WONNuMwhXl = false;}
      if(FyKaqIOdSB == true){FyKaqIOdSB = false;}
      if(lnpcgieZBs == true){lnpcgieZBs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUONZVPXSA
{ 
  void yclSJSTpdh()
  { 
      bool pzDKsYTbJX = false;
      bool rjXpWtADYZ = false;
      bool bsedxEAFzZ = false;
      bool xcbGKeQMrm = false;
      bool hCUJBltMPR = false;
      bool iZsWcwTYMo = false;
      bool YNbjZPIQfr = false;
      bool dmLlrZYUcK = false;
      bool KmphqWiFdN = false;
      bool KqzCOTZkik = false;
      bool dcgWnuOHdD = false;
      bool XzwCekXtsD = false;
      bool fDmRhlmJWX = false;
      bool AnlqggGStu = false;
      bool IbaapLtxXc = false;
      bool uerfFaoOoB = false;
      bool IFjFCjMFUx = false;
      bool dFAxtDcMbW = false;
      bool qoksbUwFkG = false;
      bool qrcrmDqUXF = false;
      string ObrJpMDWzu;
      string tnZPrPnzNi;
      string KuVYhEcHMa;
      string toNMFqWJQX;
      string VDAlyMSSHi;
      string oKflxTFTak;
      string iwKYBEaMJA;
      string rdioMHtiaU;
      string kKAdkjJbPk;
      string kDhenYsbkt;
      string lFIGpKbpYp;
      string ZWrGAYwfmR;
      string tyxXPowDBn;
      string OSygheCsna;
      string HSDYLOKbeP;
      string bMnTznIjqB;
      string OYokbGXLXU;
      string VDrLJbuXMA;
      string dTXkLBdegt;
      string WRCmMidRwF;
      if(ObrJpMDWzu == lFIGpKbpYp){pzDKsYTbJX = true;}
      else if(lFIGpKbpYp == ObrJpMDWzu){dcgWnuOHdD = true;}
      if(tnZPrPnzNi == ZWrGAYwfmR){rjXpWtADYZ = true;}
      else if(ZWrGAYwfmR == tnZPrPnzNi){XzwCekXtsD = true;}
      if(KuVYhEcHMa == tyxXPowDBn){bsedxEAFzZ = true;}
      else if(tyxXPowDBn == KuVYhEcHMa){fDmRhlmJWX = true;}
      if(toNMFqWJQX == OSygheCsna){xcbGKeQMrm = true;}
      else if(OSygheCsna == toNMFqWJQX){AnlqggGStu = true;}
      if(VDAlyMSSHi == HSDYLOKbeP){hCUJBltMPR = true;}
      else if(HSDYLOKbeP == VDAlyMSSHi){IbaapLtxXc = true;}
      if(oKflxTFTak == bMnTznIjqB){iZsWcwTYMo = true;}
      else if(bMnTznIjqB == oKflxTFTak){uerfFaoOoB = true;}
      if(iwKYBEaMJA == OYokbGXLXU){YNbjZPIQfr = true;}
      else if(OYokbGXLXU == iwKYBEaMJA){IFjFCjMFUx = true;}
      if(rdioMHtiaU == VDrLJbuXMA){dmLlrZYUcK = true;}
      if(kKAdkjJbPk == dTXkLBdegt){KmphqWiFdN = true;}
      if(kDhenYsbkt == WRCmMidRwF){KqzCOTZkik = true;}
      while(VDrLJbuXMA == rdioMHtiaU){dFAxtDcMbW = true;}
      while(dTXkLBdegt == dTXkLBdegt){qoksbUwFkG = true;}
      while(WRCmMidRwF == WRCmMidRwF){qrcrmDqUXF = true;}
      if(pzDKsYTbJX == true){pzDKsYTbJX = false;}
      if(rjXpWtADYZ == true){rjXpWtADYZ = false;}
      if(bsedxEAFzZ == true){bsedxEAFzZ = false;}
      if(xcbGKeQMrm == true){xcbGKeQMrm = false;}
      if(hCUJBltMPR == true){hCUJBltMPR = false;}
      if(iZsWcwTYMo == true){iZsWcwTYMo = false;}
      if(YNbjZPIQfr == true){YNbjZPIQfr = false;}
      if(dmLlrZYUcK == true){dmLlrZYUcK = false;}
      if(KmphqWiFdN == true){KmphqWiFdN = false;}
      if(KqzCOTZkik == true){KqzCOTZkik = false;}
      if(dcgWnuOHdD == true){dcgWnuOHdD = false;}
      if(XzwCekXtsD == true){XzwCekXtsD = false;}
      if(fDmRhlmJWX == true){fDmRhlmJWX = false;}
      if(AnlqggGStu == true){AnlqggGStu = false;}
      if(IbaapLtxXc == true){IbaapLtxXc = false;}
      if(uerfFaoOoB == true){uerfFaoOoB = false;}
      if(IFjFCjMFUx == true){IFjFCjMFUx = false;}
      if(dFAxtDcMbW == true){dFAxtDcMbW = false;}
      if(qoksbUwFkG == true){qoksbUwFkG = false;}
      if(qrcrmDqUXF == true){qrcrmDqUXF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FPXMZSCTLZ
{ 
  void AmkRSbgOna()
  { 
      bool zoOgcSOVYP = false;
      bool djKKQkMqKh = false;
      bool ZnSNPcrAXe = false;
      bool FAusqSZycq = false;
      bool oxUOCVBopU = false;
      bool BKwuELWBRz = false;
      bool aOxtKdoRSy = false;
      bool LONSscSDKs = false;
      bool bCJDduDznf = false;
      bool wYfcQazaEX = false;
      bool giWqJlwcCb = false;
      bool sSpYXXEtPP = false;
      bool ZodlBmijCR = false;
      bool cqzmLrfRsq = false;
      bool yaxLmdhHFr = false;
      bool WFLnxrFjpW = false;
      bool DMZjzBSCMf = false;
      bool rlAYRzqRzX = false;
      bool EbeKuXfKoT = false;
      bool mubWnlBNMl = false;
      string cMPuducHyU;
      string tboAHKhNpB;
      string mqkizdkFOn;
      string jTeXUFWPoN;
      string bCQDDPPKcK;
      string mAyOukbguz;
      string KWrJjaxQeC;
      string mRYbZjZgej;
      string NZcEAiUPbi;
      string cpUoDEKHTc;
      string SyeaWVbVoL;
      string LuBLkktnIA;
      string FgowYxxiYU;
      string ZRMCRPuBge;
      string HyaPXhnIDS;
      string KVzSWkJiBZ;
      string YrxTlshytV;
      string orHdsGGYXq;
      string InfGJDSteg;
      string GMAHFOBGde;
      if(cMPuducHyU == SyeaWVbVoL){zoOgcSOVYP = true;}
      else if(SyeaWVbVoL == cMPuducHyU){giWqJlwcCb = true;}
      if(tboAHKhNpB == LuBLkktnIA){djKKQkMqKh = true;}
      else if(LuBLkktnIA == tboAHKhNpB){sSpYXXEtPP = true;}
      if(mqkizdkFOn == FgowYxxiYU){ZnSNPcrAXe = true;}
      else if(FgowYxxiYU == mqkizdkFOn){ZodlBmijCR = true;}
      if(jTeXUFWPoN == ZRMCRPuBge){FAusqSZycq = true;}
      else if(ZRMCRPuBge == jTeXUFWPoN){cqzmLrfRsq = true;}
      if(bCQDDPPKcK == HyaPXhnIDS){oxUOCVBopU = true;}
      else if(HyaPXhnIDS == bCQDDPPKcK){yaxLmdhHFr = true;}
      if(mAyOukbguz == KVzSWkJiBZ){BKwuELWBRz = true;}
      else if(KVzSWkJiBZ == mAyOukbguz){WFLnxrFjpW = true;}
      if(KWrJjaxQeC == YrxTlshytV){aOxtKdoRSy = true;}
      else if(YrxTlshytV == KWrJjaxQeC){DMZjzBSCMf = true;}
      if(mRYbZjZgej == orHdsGGYXq){LONSscSDKs = true;}
      if(NZcEAiUPbi == InfGJDSteg){bCJDduDznf = true;}
      if(cpUoDEKHTc == GMAHFOBGde){wYfcQazaEX = true;}
      while(orHdsGGYXq == mRYbZjZgej){rlAYRzqRzX = true;}
      while(InfGJDSteg == InfGJDSteg){EbeKuXfKoT = true;}
      while(GMAHFOBGde == GMAHFOBGde){mubWnlBNMl = true;}
      if(zoOgcSOVYP == true){zoOgcSOVYP = false;}
      if(djKKQkMqKh == true){djKKQkMqKh = false;}
      if(ZnSNPcrAXe == true){ZnSNPcrAXe = false;}
      if(FAusqSZycq == true){FAusqSZycq = false;}
      if(oxUOCVBopU == true){oxUOCVBopU = false;}
      if(BKwuELWBRz == true){BKwuELWBRz = false;}
      if(aOxtKdoRSy == true){aOxtKdoRSy = false;}
      if(LONSscSDKs == true){LONSscSDKs = false;}
      if(bCJDduDznf == true){bCJDduDznf = false;}
      if(wYfcQazaEX == true){wYfcQazaEX = false;}
      if(giWqJlwcCb == true){giWqJlwcCb = false;}
      if(sSpYXXEtPP == true){sSpYXXEtPP = false;}
      if(ZodlBmijCR == true){ZodlBmijCR = false;}
      if(cqzmLrfRsq == true){cqzmLrfRsq = false;}
      if(yaxLmdhHFr == true){yaxLmdhHFr = false;}
      if(WFLnxrFjpW == true){WFLnxrFjpW = false;}
      if(DMZjzBSCMf == true){DMZjzBSCMf = false;}
      if(rlAYRzqRzX == true){rlAYRzqRzX = false;}
      if(EbeKuXfKoT == true){EbeKuXfKoT = false;}
      if(mubWnlBNMl == true){mubWnlBNMl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VWEKXUDVQS
{ 
  void RcxfRMiheL()
  { 
      bool JJddlritAp = false;
      bool WLBQLjcSwm = false;
      bool efwVxczwiu = false;
      bool DUDgXplQeb = false;
      bool iXgxwqJXXI = false;
      bool SZIQgdMIfI = false;
      bool smLFlCHUrV = false;
      bool yMmUDHyzZG = false;
      bool SaXabcLlAt = false;
      bool cdjViwMbKt = false;
      bool ioeBJGlnMY = false;
      bool eNhZpROkcJ = false;
      bool pUTyrTbRkH = false;
      bool tWofWdwWQV = false;
      bool pXYaOPwKfQ = false;
      bool hbyADNVgIp = false;
      bool dUCFeIYCCL = false;
      bool VqUGSRwric = false;
      bool XQlUZSXnbI = false;
      bool IONZrVUTwG = false;
      string xHKrfIjRfI;
      string YkJQhkyFpl;
      string fcxTdCFNtc;
      string kxGyQTqneZ;
      string eLuXkVuzTw;
      string wVrWETKpNd;
      string CVXCXbdKAO;
      string sKZQHTgYhH;
      string GGsxfOEjsw;
      string IBZBXInrAJ;
      string qjzFDlwbOk;
      string llIFWwcZVJ;
      string XtQDFrjYrz;
      string foYYQVHntt;
      string SbUIJWsTda;
      string fNVqkxTuzK;
      string BWiPExNioA;
      string onebpuZHsh;
      string zQtQTRSgmT;
      string CLoisurEEL;
      if(xHKrfIjRfI == qjzFDlwbOk){JJddlritAp = true;}
      else if(qjzFDlwbOk == xHKrfIjRfI){ioeBJGlnMY = true;}
      if(YkJQhkyFpl == llIFWwcZVJ){WLBQLjcSwm = true;}
      else if(llIFWwcZVJ == YkJQhkyFpl){eNhZpROkcJ = true;}
      if(fcxTdCFNtc == XtQDFrjYrz){efwVxczwiu = true;}
      else if(XtQDFrjYrz == fcxTdCFNtc){pUTyrTbRkH = true;}
      if(kxGyQTqneZ == foYYQVHntt){DUDgXplQeb = true;}
      else if(foYYQVHntt == kxGyQTqneZ){tWofWdwWQV = true;}
      if(eLuXkVuzTw == SbUIJWsTda){iXgxwqJXXI = true;}
      else if(SbUIJWsTda == eLuXkVuzTw){pXYaOPwKfQ = true;}
      if(wVrWETKpNd == fNVqkxTuzK){SZIQgdMIfI = true;}
      else if(fNVqkxTuzK == wVrWETKpNd){hbyADNVgIp = true;}
      if(CVXCXbdKAO == BWiPExNioA){smLFlCHUrV = true;}
      else if(BWiPExNioA == CVXCXbdKAO){dUCFeIYCCL = true;}
      if(sKZQHTgYhH == onebpuZHsh){yMmUDHyzZG = true;}
      if(GGsxfOEjsw == zQtQTRSgmT){SaXabcLlAt = true;}
      if(IBZBXInrAJ == CLoisurEEL){cdjViwMbKt = true;}
      while(onebpuZHsh == sKZQHTgYhH){VqUGSRwric = true;}
      while(zQtQTRSgmT == zQtQTRSgmT){XQlUZSXnbI = true;}
      while(CLoisurEEL == CLoisurEEL){IONZrVUTwG = true;}
      if(JJddlritAp == true){JJddlritAp = false;}
      if(WLBQLjcSwm == true){WLBQLjcSwm = false;}
      if(efwVxczwiu == true){efwVxczwiu = false;}
      if(DUDgXplQeb == true){DUDgXplQeb = false;}
      if(iXgxwqJXXI == true){iXgxwqJXXI = false;}
      if(SZIQgdMIfI == true){SZIQgdMIfI = false;}
      if(smLFlCHUrV == true){smLFlCHUrV = false;}
      if(yMmUDHyzZG == true){yMmUDHyzZG = false;}
      if(SaXabcLlAt == true){SaXabcLlAt = false;}
      if(cdjViwMbKt == true){cdjViwMbKt = false;}
      if(ioeBJGlnMY == true){ioeBJGlnMY = false;}
      if(eNhZpROkcJ == true){eNhZpROkcJ = false;}
      if(pUTyrTbRkH == true){pUTyrTbRkH = false;}
      if(tWofWdwWQV == true){tWofWdwWQV = false;}
      if(pXYaOPwKfQ == true){pXYaOPwKfQ = false;}
      if(hbyADNVgIp == true){hbyADNVgIp = false;}
      if(dUCFeIYCCL == true){dUCFeIYCCL = false;}
      if(VqUGSRwric == true){VqUGSRwric = false;}
      if(XQlUZSXnbI == true){XQlUZSXnbI = false;}
      if(IONZrVUTwG == true){IONZrVUTwG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZPMJEEIIMF
{ 
  void fZGssXzAHJ()
  { 
      bool jQjoViTgan = false;
      bool GsjKbJDkNj = false;
      bool bkOfMSjHaE = false;
      bool rDCBAYfBDy = false;
      bool UwlbiSpcAF = false;
      bool rTjiNyBEcC = false;
      bool yLFWuDqhKD = false;
      bool cChPPfzlxt = false;
      bool bHHVMXSTnC = false;
      bool WbYAAIpOgf = false;
      bool aISxbolUSh = false;
      bool yOGiapEiKW = false;
      bool jXtHfBcgOH = false;
      bool ojEQSToJtW = false;
      bool kyAFEIUoZJ = false;
      bool DGEKuDNKQZ = false;
      bool MFFLrNJpQG = false;
      bool BtonkkWnDX = false;
      bool gnGEDhftVO = false;
      bool FdsTKesoNp = false;
      string VzYtMKBhpw;
      string soWkCenpMT;
      string dQGlaGEyKb;
      string NNQzCNQrVO;
      string REPAhaBsBP;
      string qVxmpFslSG;
      string FDXOifYWhn;
      string OuUxCYAFEz;
      string FLwtjrQdJx;
      string UdYOINgBRB;
      string CdKNBwAzjQ;
      string EmhSAtGcdq;
      string PtNjSjVFnn;
      string rznCxbAisn;
      string qQsrshuFOO;
      string GDWalHPZuQ;
      string ZuKuYEyeVY;
      string sXjpzyBVpj;
      string oPqZgncMQo;
      string MZmbOuFyTo;
      if(VzYtMKBhpw == CdKNBwAzjQ){jQjoViTgan = true;}
      else if(CdKNBwAzjQ == VzYtMKBhpw){aISxbolUSh = true;}
      if(soWkCenpMT == EmhSAtGcdq){GsjKbJDkNj = true;}
      else if(EmhSAtGcdq == soWkCenpMT){yOGiapEiKW = true;}
      if(dQGlaGEyKb == PtNjSjVFnn){bkOfMSjHaE = true;}
      else if(PtNjSjVFnn == dQGlaGEyKb){jXtHfBcgOH = true;}
      if(NNQzCNQrVO == rznCxbAisn){rDCBAYfBDy = true;}
      else if(rznCxbAisn == NNQzCNQrVO){ojEQSToJtW = true;}
      if(REPAhaBsBP == qQsrshuFOO){UwlbiSpcAF = true;}
      else if(qQsrshuFOO == REPAhaBsBP){kyAFEIUoZJ = true;}
      if(qVxmpFslSG == GDWalHPZuQ){rTjiNyBEcC = true;}
      else if(GDWalHPZuQ == qVxmpFslSG){DGEKuDNKQZ = true;}
      if(FDXOifYWhn == ZuKuYEyeVY){yLFWuDqhKD = true;}
      else if(ZuKuYEyeVY == FDXOifYWhn){MFFLrNJpQG = true;}
      if(OuUxCYAFEz == sXjpzyBVpj){cChPPfzlxt = true;}
      if(FLwtjrQdJx == oPqZgncMQo){bHHVMXSTnC = true;}
      if(UdYOINgBRB == MZmbOuFyTo){WbYAAIpOgf = true;}
      while(sXjpzyBVpj == OuUxCYAFEz){BtonkkWnDX = true;}
      while(oPqZgncMQo == oPqZgncMQo){gnGEDhftVO = true;}
      while(MZmbOuFyTo == MZmbOuFyTo){FdsTKesoNp = true;}
      if(jQjoViTgan == true){jQjoViTgan = false;}
      if(GsjKbJDkNj == true){GsjKbJDkNj = false;}
      if(bkOfMSjHaE == true){bkOfMSjHaE = false;}
      if(rDCBAYfBDy == true){rDCBAYfBDy = false;}
      if(UwlbiSpcAF == true){UwlbiSpcAF = false;}
      if(rTjiNyBEcC == true){rTjiNyBEcC = false;}
      if(yLFWuDqhKD == true){yLFWuDqhKD = false;}
      if(cChPPfzlxt == true){cChPPfzlxt = false;}
      if(bHHVMXSTnC == true){bHHVMXSTnC = false;}
      if(WbYAAIpOgf == true){WbYAAIpOgf = false;}
      if(aISxbolUSh == true){aISxbolUSh = false;}
      if(yOGiapEiKW == true){yOGiapEiKW = false;}
      if(jXtHfBcgOH == true){jXtHfBcgOH = false;}
      if(ojEQSToJtW == true){ojEQSToJtW = false;}
      if(kyAFEIUoZJ == true){kyAFEIUoZJ = false;}
      if(DGEKuDNKQZ == true){DGEKuDNKQZ = false;}
      if(MFFLrNJpQG == true){MFFLrNJpQG = false;}
      if(BtonkkWnDX == true){BtonkkWnDX = false;}
      if(gnGEDhftVO == true){gnGEDhftVO = false;}
      if(FdsTKesoNp == true){FdsTKesoNp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLAJGNUXDV
{ 
  void jzrSDiARDK()
  { 
      bool wSyqfVaAzD = false;
      bool FgotVuXuuK = false;
      bool qJgKRlQixb = false;
      bool ugwtkatDOY = false;
      bool NbmtDQRncR = false;
      bool fICPImkmYs = false;
      bool EqDXHYjtIt = false;
      bool BUfWxPVmHA = false;
      bool TcGeumdfly = false;
      bool pGdUTVXPle = false;
      bool fWfhQLbeSs = false;
      bool QxfYZbjYbU = false;
      bool tEIKEtqLCa = false;
      bool qGBbTxwYOj = false;
      bool KyMsgraFur = false;
      bool lzmQkbOVdV = false;
      bool UQbrBKwEEb = false;
      bool eLJrKuqPcL = false;
      bool SkPKoqTjpr = false;
      bool haurPtWUqW = false;
      string PCWayNZLBk;
      string zHwsMakWWA;
      string XtitObjBup;
      string ozuZzbGsuo;
      string EUifwQXsma;
      string pwsBBUScMV;
      string cYPLwzMWsj;
      string UrbguDLDxy;
      string DqNUzrGsYd;
      string JcgYLfEWjw;
      string DBzDGyULFx;
      string JPfORlKuLD;
      string sSxPaqKCUP;
      string ynTAtBqKNB;
      string WtnaUsxSHZ;
      string VILfCkDjbP;
      string mSppzUweTP;
      string tzhKfzeWth;
      string srtutocmxJ;
      string yHhyNEDyaA;
      if(PCWayNZLBk == DBzDGyULFx){wSyqfVaAzD = true;}
      else if(DBzDGyULFx == PCWayNZLBk){fWfhQLbeSs = true;}
      if(zHwsMakWWA == JPfORlKuLD){FgotVuXuuK = true;}
      else if(JPfORlKuLD == zHwsMakWWA){QxfYZbjYbU = true;}
      if(XtitObjBup == sSxPaqKCUP){qJgKRlQixb = true;}
      else if(sSxPaqKCUP == XtitObjBup){tEIKEtqLCa = true;}
      if(ozuZzbGsuo == ynTAtBqKNB){ugwtkatDOY = true;}
      else if(ynTAtBqKNB == ozuZzbGsuo){qGBbTxwYOj = true;}
      if(EUifwQXsma == WtnaUsxSHZ){NbmtDQRncR = true;}
      else if(WtnaUsxSHZ == EUifwQXsma){KyMsgraFur = true;}
      if(pwsBBUScMV == VILfCkDjbP){fICPImkmYs = true;}
      else if(VILfCkDjbP == pwsBBUScMV){lzmQkbOVdV = true;}
      if(cYPLwzMWsj == mSppzUweTP){EqDXHYjtIt = true;}
      else if(mSppzUweTP == cYPLwzMWsj){UQbrBKwEEb = true;}
      if(UrbguDLDxy == tzhKfzeWth){BUfWxPVmHA = true;}
      if(DqNUzrGsYd == srtutocmxJ){TcGeumdfly = true;}
      if(JcgYLfEWjw == yHhyNEDyaA){pGdUTVXPle = true;}
      while(tzhKfzeWth == UrbguDLDxy){eLJrKuqPcL = true;}
      while(srtutocmxJ == srtutocmxJ){SkPKoqTjpr = true;}
      while(yHhyNEDyaA == yHhyNEDyaA){haurPtWUqW = true;}
      if(wSyqfVaAzD == true){wSyqfVaAzD = false;}
      if(FgotVuXuuK == true){FgotVuXuuK = false;}
      if(qJgKRlQixb == true){qJgKRlQixb = false;}
      if(ugwtkatDOY == true){ugwtkatDOY = false;}
      if(NbmtDQRncR == true){NbmtDQRncR = false;}
      if(fICPImkmYs == true){fICPImkmYs = false;}
      if(EqDXHYjtIt == true){EqDXHYjtIt = false;}
      if(BUfWxPVmHA == true){BUfWxPVmHA = false;}
      if(TcGeumdfly == true){TcGeumdfly = false;}
      if(pGdUTVXPle == true){pGdUTVXPle = false;}
      if(fWfhQLbeSs == true){fWfhQLbeSs = false;}
      if(QxfYZbjYbU == true){QxfYZbjYbU = false;}
      if(tEIKEtqLCa == true){tEIKEtqLCa = false;}
      if(qGBbTxwYOj == true){qGBbTxwYOj = false;}
      if(KyMsgraFur == true){KyMsgraFur = false;}
      if(lzmQkbOVdV == true){lzmQkbOVdV = false;}
      if(UQbrBKwEEb == true){UQbrBKwEEb = false;}
      if(eLJrKuqPcL == true){eLJrKuqPcL = false;}
      if(SkPKoqTjpr == true){SkPKoqTjpr = false;}
      if(haurPtWUqW == true){haurPtWUqW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QASNEURUPX
{ 
  void bDQWqAIQwl()
  { 
      bool tdwpRlTosE = false;
      bool YGiaVNScCX = false;
      bool onfZFzZEWP = false;
      bool KwLgIQwkTp = false;
      bool okHHinKiGt = false;
      bool OJnkmFyVjR = false;
      bool MPSdscuCRF = false;
      bool QhJMhEfYqQ = false;
      bool npxbABHatC = false;
      bool SZABcZRcNG = false;
      bool sIRBcgzbDh = false;
      bool ZYeTcVRqdr = false;
      bool UUIOlqgHiH = false;
      bool lDLkWfYwzT = false;
      bool BfXLctugYG = false;
      bool IazVkYACOl = false;
      bool ArruwWMtwx = false;
      bool xUqJqoxwlq = false;
      bool uzibyKDpzy = false;
      bool eVhMTJmbOG = false;
      string lXDVLBFOPr;
      string YpxlKucYxV;
      string TOifbglbIb;
      string fMcHdGAZrI;
      string ZhDbOjZDVe;
      string hrAabXnWsd;
      string PdFnMMNoIE;
      string tDfoulKHQq;
      string GhFdsmMCfF;
      string RcfNrubOOC;
      string WjuQjdLKep;
      string MgGCWgYatY;
      string zKJCmRWRwz;
      string JurOTVmntP;
      string bBWosjWdqL;
      string WAUpCMardR;
      string GtOfgQorhA;
      string tjgexymTJD;
      string usakcIaBLH;
      string utKcIgmqIb;
      if(lXDVLBFOPr == WjuQjdLKep){tdwpRlTosE = true;}
      else if(WjuQjdLKep == lXDVLBFOPr){sIRBcgzbDh = true;}
      if(YpxlKucYxV == MgGCWgYatY){YGiaVNScCX = true;}
      else if(MgGCWgYatY == YpxlKucYxV){ZYeTcVRqdr = true;}
      if(TOifbglbIb == zKJCmRWRwz){onfZFzZEWP = true;}
      else if(zKJCmRWRwz == TOifbglbIb){UUIOlqgHiH = true;}
      if(fMcHdGAZrI == JurOTVmntP){KwLgIQwkTp = true;}
      else if(JurOTVmntP == fMcHdGAZrI){lDLkWfYwzT = true;}
      if(ZhDbOjZDVe == bBWosjWdqL){okHHinKiGt = true;}
      else if(bBWosjWdqL == ZhDbOjZDVe){BfXLctugYG = true;}
      if(hrAabXnWsd == WAUpCMardR){OJnkmFyVjR = true;}
      else if(WAUpCMardR == hrAabXnWsd){IazVkYACOl = true;}
      if(PdFnMMNoIE == GtOfgQorhA){MPSdscuCRF = true;}
      else if(GtOfgQorhA == PdFnMMNoIE){ArruwWMtwx = true;}
      if(tDfoulKHQq == tjgexymTJD){QhJMhEfYqQ = true;}
      if(GhFdsmMCfF == usakcIaBLH){npxbABHatC = true;}
      if(RcfNrubOOC == utKcIgmqIb){SZABcZRcNG = true;}
      while(tjgexymTJD == tDfoulKHQq){xUqJqoxwlq = true;}
      while(usakcIaBLH == usakcIaBLH){uzibyKDpzy = true;}
      while(utKcIgmqIb == utKcIgmqIb){eVhMTJmbOG = true;}
      if(tdwpRlTosE == true){tdwpRlTosE = false;}
      if(YGiaVNScCX == true){YGiaVNScCX = false;}
      if(onfZFzZEWP == true){onfZFzZEWP = false;}
      if(KwLgIQwkTp == true){KwLgIQwkTp = false;}
      if(okHHinKiGt == true){okHHinKiGt = false;}
      if(OJnkmFyVjR == true){OJnkmFyVjR = false;}
      if(MPSdscuCRF == true){MPSdscuCRF = false;}
      if(QhJMhEfYqQ == true){QhJMhEfYqQ = false;}
      if(npxbABHatC == true){npxbABHatC = false;}
      if(SZABcZRcNG == true){SZABcZRcNG = false;}
      if(sIRBcgzbDh == true){sIRBcgzbDh = false;}
      if(ZYeTcVRqdr == true){ZYeTcVRqdr = false;}
      if(UUIOlqgHiH == true){UUIOlqgHiH = false;}
      if(lDLkWfYwzT == true){lDLkWfYwzT = false;}
      if(BfXLctugYG == true){BfXLctugYG = false;}
      if(IazVkYACOl == true){IazVkYACOl = false;}
      if(ArruwWMtwx == true){ArruwWMtwx = false;}
      if(xUqJqoxwlq == true){xUqJqoxwlq = false;}
      if(uzibyKDpzy == true){uzibyKDpzy = false;}
      if(eVhMTJmbOG == true){eVhMTJmbOG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZSQVTOUQDJ
{ 
  void AnWtPUFSer()
  { 
      bool pyKQkwhuRB = false;
      bool oLBmZOMUls = false;
      bool eJrjjNTBmL = false;
      bool bJpNmUNtlD = false;
      bool BSKAiybjjf = false;
      bool dwiMsgGafW = false;
      bool bfHFYfVmzF = false;
      bool BShirLyqAk = false;
      bool liRHhfZcTG = false;
      bool OmNOaULFbD = false;
      bool cokdeKOAUh = false;
      bool iOZtksOzXs = false;
      bool FrTsqNESHX = false;
      bool ArOxIxxmcW = false;
      bool RZIlWzMSdg = false;
      bool FLgixjVrmQ = false;
      bool GurxgpAckm = false;
      bool ubWAafjgVr = false;
      bool BkoZRnLfzY = false;
      bool bFALQVgLEg = false;
      string ZUjjicxXaT;
      string jguhEOlkoS;
      string MEyyeOLEDA;
      string tfMcYjUZrD;
      string LcSMCbHBrx;
      string oldfoVVlEU;
      string RrUZZETSIU;
      string sLskGjkkuC;
      string HJMGKHBgmD;
      string NiUXkTHsmy;
      string InsXDcsrYE;
      string kkqCMIfOPR;
      string DmfEGKqUAm;
      string bqyxtSQnCg;
      string OJHiScrSKc;
      string mscUuUInQr;
      string lXrlbsltIt;
      string qqLhDsfwld;
      string SXKXziNcCY;
      string KcXJtqQVGY;
      if(ZUjjicxXaT == InsXDcsrYE){pyKQkwhuRB = true;}
      else if(InsXDcsrYE == ZUjjicxXaT){cokdeKOAUh = true;}
      if(jguhEOlkoS == kkqCMIfOPR){oLBmZOMUls = true;}
      else if(kkqCMIfOPR == jguhEOlkoS){iOZtksOzXs = true;}
      if(MEyyeOLEDA == DmfEGKqUAm){eJrjjNTBmL = true;}
      else if(DmfEGKqUAm == MEyyeOLEDA){FrTsqNESHX = true;}
      if(tfMcYjUZrD == bqyxtSQnCg){bJpNmUNtlD = true;}
      else if(bqyxtSQnCg == tfMcYjUZrD){ArOxIxxmcW = true;}
      if(LcSMCbHBrx == OJHiScrSKc){BSKAiybjjf = true;}
      else if(OJHiScrSKc == LcSMCbHBrx){RZIlWzMSdg = true;}
      if(oldfoVVlEU == mscUuUInQr){dwiMsgGafW = true;}
      else if(mscUuUInQr == oldfoVVlEU){FLgixjVrmQ = true;}
      if(RrUZZETSIU == lXrlbsltIt){bfHFYfVmzF = true;}
      else if(lXrlbsltIt == RrUZZETSIU){GurxgpAckm = true;}
      if(sLskGjkkuC == qqLhDsfwld){BShirLyqAk = true;}
      if(HJMGKHBgmD == SXKXziNcCY){liRHhfZcTG = true;}
      if(NiUXkTHsmy == KcXJtqQVGY){OmNOaULFbD = true;}
      while(qqLhDsfwld == sLskGjkkuC){ubWAafjgVr = true;}
      while(SXKXziNcCY == SXKXziNcCY){BkoZRnLfzY = true;}
      while(KcXJtqQVGY == KcXJtqQVGY){bFALQVgLEg = true;}
      if(pyKQkwhuRB == true){pyKQkwhuRB = false;}
      if(oLBmZOMUls == true){oLBmZOMUls = false;}
      if(eJrjjNTBmL == true){eJrjjNTBmL = false;}
      if(bJpNmUNtlD == true){bJpNmUNtlD = false;}
      if(BSKAiybjjf == true){BSKAiybjjf = false;}
      if(dwiMsgGafW == true){dwiMsgGafW = false;}
      if(bfHFYfVmzF == true){bfHFYfVmzF = false;}
      if(BShirLyqAk == true){BShirLyqAk = false;}
      if(liRHhfZcTG == true){liRHhfZcTG = false;}
      if(OmNOaULFbD == true){OmNOaULFbD = false;}
      if(cokdeKOAUh == true){cokdeKOAUh = false;}
      if(iOZtksOzXs == true){iOZtksOzXs = false;}
      if(FrTsqNESHX == true){FrTsqNESHX = false;}
      if(ArOxIxxmcW == true){ArOxIxxmcW = false;}
      if(RZIlWzMSdg == true){RZIlWzMSdg = false;}
      if(FLgixjVrmQ == true){FLgixjVrmQ = false;}
      if(GurxgpAckm == true){GurxgpAckm = false;}
      if(ubWAafjgVr == true){ubWAafjgVr = false;}
      if(BkoZRnLfzY == true){BkoZRnLfzY = false;}
      if(bFALQVgLEg == true){bFALQVgLEg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KEEOUIPUTM
{ 
  void HxQKknyXJY()
  { 
      bool atNDxqIPRP = false;
      bool LtyWJgJhhR = false;
      bool xZWVHxNbSe = false;
      bool GnZKwlKxLm = false;
      bool aeMTDYptEU = false;
      bool bYrGgAWquA = false;
      bool cfxmIXTnaX = false;
      bool WLVupSNDSi = false;
      bool GSWxChuTcu = false;
      bool OSCLJtgYKe = false;
      bool ECSgyPCwPN = false;
      bool lSYLsJJAka = false;
      bool bAKfIDJKlu = false;
      bool kosmeDzpyl = false;
      bool eyDOJuspRz = false;
      bool kgmiCDrmXu = false;
      bool GqKTcxZkgo = false;
      bool KTByudwuWN = false;
      bool JSrlKEBKja = false;
      bool LLRDennjlL = false;
      string lhIgjjJkYd;
      string DcCbbwQekg;
      string ESGkpVqHIL;
      string cJcWQZrRgs;
      string QZZxhZtMyc;
      string aobcOSbWqO;
      string sBcMAszeLB;
      string DyyrQesJCP;
      string adJejmhzIx;
      string yVaRzOwMwo;
      string ZPBxYcqjMi;
      string ZSTamPrxbM;
      string LAWNChXfsB;
      string ifNNoLcMGH;
      string wxlYXfBzej;
      string WzkidZrmtq;
      string FKqLAsEGka;
      string lfqUQNNyoW;
      string gXBIdiueiP;
      string SoROClGZXe;
      if(lhIgjjJkYd == ZPBxYcqjMi){atNDxqIPRP = true;}
      else if(ZPBxYcqjMi == lhIgjjJkYd){ECSgyPCwPN = true;}
      if(DcCbbwQekg == ZSTamPrxbM){LtyWJgJhhR = true;}
      else if(ZSTamPrxbM == DcCbbwQekg){lSYLsJJAka = true;}
      if(ESGkpVqHIL == LAWNChXfsB){xZWVHxNbSe = true;}
      else if(LAWNChXfsB == ESGkpVqHIL){bAKfIDJKlu = true;}
      if(cJcWQZrRgs == ifNNoLcMGH){GnZKwlKxLm = true;}
      else if(ifNNoLcMGH == cJcWQZrRgs){kosmeDzpyl = true;}
      if(QZZxhZtMyc == wxlYXfBzej){aeMTDYptEU = true;}
      else if(wxlYXfBzej == QZZxhZtMyc){eyDOJuspRz = true;}
      if(aobcOSbWqO == WzkidZrmtq){bYrGgAWquA = true;}
      else if(WzkidZrmtq == aobcOSbWqO){kgmiCDrmXu = true;}
      if(sBcMAszeLB == FKqLAsEGka){cfxmIXTnaX = true;}
      else if(FKqLAsEGka == sBcMAszeLB){GqKTcxZkgo = true;}
      if(DyyrQesJCP == lfqUQNNyoW){WLVupSNDSi = true;}
      if(adJejmhzIx == gXBIdiueiP){GSWxChuTcu = true;}
      if(yVaRzOwMwo == SoROClGZXe){OSCLJtgYKe = true;}
      while(lfqUQNNyoW == DyyrQesJCP){KTByudwuWN = true;}
      while(gXBIdiueiP == gXBIdiueiP){JSrlKEBKja = true;}
      while(SoROClGZXe == SoROClGZXe){LLRDennjlL = true;}
      if(atNDxqIPRP == true){atNDxqIPRP = false;}
      if(LtyWJgJhhR == true){LtyWJgJhhR = false;}
      if(xZWVHxNbSe == true){xZWVHxNbSe = false;}
      if(GnZKwlKxLm == true){GnZKwlKxLm = false;}
      if(aeMTDYptEU == true){aeMTDYptEU = false;}
      if(bYrGgAWquA == true){bYrGgAWquA = false;}
      if(cfxmIXTnaX == true){cfxmIXTnaX = false;}
      if(WLVupSNDSi == true){WLVupSNDSi = false;}
      if(GSWxChuTcu == true){GSWxChuTcu = false;}
      if(OSCLJtgYKe == true){OSCLJtgYKe = false;}
      if(ECSgyPCwPN == true){ECSgyPCwPN = false;}
      if(lSYLsJJAka == true){lSYLsJJAka = false;}
      if(bAKfIDJKlu == true){bAKfIDJKlu = false;}
      if(kosmeDzpyl == true){kosmeDzpyl = false;}
      if(eyDOJuspRz == true){eyDOJuspRz = false;}
      if(kgmiCDrmXu == true){kgmiCDrmXu = false;}
      if(GqKTcxZkgo == true){GqKTcxZkgo = false;}
      if(KTByudwuWN == true){KTByudwuWN = false;}
      if(JSrlKEBKja == true){JSrlKEBKja = false;}
      if(LLRDennjlL == true){LLRDennjlL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BUIKSKFNCV
{ 
  void sBeXgqfWzk()
  { 
      bool HgDeOIjGTh = false;
      bool sYOhftUHmO = false;
      bool OkmYCnnqYS = false;
      bool GSDkxIxsKl = false;
      bool KDEDQrCyCo = false;
      bool nJBNHVsebZ = false;
      bool TrhAaZUdkW = false;
      bool waxAELgiHJ = false;
      bool looidxRoca = false;
      bool PSQjRRUDcp = false;
      bool WXNesNMAJw = false;
      bool oJWSndDzWd = false;
      bool IeBKGdJNhl = false;
      bool pcGRlNbJoQ = false;
      bool jRfgkGuyun = false;
      bool OVgyhrWDXP = false;
      bool DyRWFMCFfa = false;
      bool CtJFsqzUYA = false;
      bool hLRtXUwHjt = false;
      bool qXkZNlzJaY = false;
      string LfAzPETMYl;
      string RdaYgpfgqc;
      string iiKGTgrCLU;
      string qRZIXPTLVd;
      string koGSggobZn;
      string EZoyHbUsfh;
      string MRADtAESAQ;
      string WTKMrscrZm;
      string rQcWPQbbAw;
      string tZfnRSnCXf;
      string bWaIRjPcGO;
      string zcTsouodnc;
      string YbREVwnWuY;
      string EZTsKVoTEe;
      string BzVlwRGlyV;
      string dKOuHAEWlV;
      string urggJZJZiT;
      string GVZIbYGfHE;
      string oBXYttKXlJ;
      string QRghjIRnbW;
      if(LfAzPETMYl == bWaIRjPcGO){HgDeOIjGTh = true;}
      else if(bWaIRjPcGO == LfAzPETMYl){WXNesNMAJw = true;}
      if(RdaYgpfgqc == zcTsouodnc){sYOhftUHmO = true;}
      else if(zcTsouodnc == RdaYgpfgqc){oJWSndDzWd = true;}
      if(iiKGTgrCLU == YbREVwnWuY){OkmYCnnqYS = true;}
      else if(YbREVwnWuY == iiKGTgrCLU){IeBKGdJNhl = true;}
      if(qRZIXPTLVd == EZTsKVoTEe){GSDkxIxsKl = true;}
      else if(EZTsKVoTEe == qRZIXPTLVd){pcGRlNbJoQ = true;}
      if(koGSggobZn == BzVlwRGlyV){KDEDQrCyCo = true;}
      else if(BzVlwRGlyV == koGSggobZn){jRfgkGuyun = true;}
      if(EZoyHbUsfh == dKOuHAEWlV){nJBNHVsebZ = true;}
      else if(dKOuHAEWlV == EZoyHbUsfh){OVgyhrWDXP = true;}
      if(MRADtAESAQ == urggJZJZiT){TrhAaZUdkW = true;}
      else if(urggJZJZiT == MRADtAESAQ){DyRWFMCFfa = true;}
      if(WTKMrscrZm == GVZIbYGfHE){waxAELgiHJ = true;}
      if(rQcWPQbbAw == oBXYttKXlJ){looidxRoca = true;}
      if(tZfnRSnCXf == QRghjIRnbW){PSQjRRUDcp = true;}
      while(GVZIbYGfHE == WTKMrscrZm){CtJFsqzUYA = true;}
      while(oBXYttKXlJ == oBXYttKXlJ){hLRtXUwHjt = true;}
      while(QRghjIRnbW == QRghjIRnbW){qXkZNlzJaY = true;}
      if(HgDeOIjGTh == true){HgDeOIjGTh = false;}
      if(sYOhftUHmO == true){sYOhftUHmO = false;}
      if(OkmYCnnqYS == true){OkmYCnnqYS = false;}
      if(GSDkxIxsKl == true){GSDkxIxsKl = false;}
      if(KDEDQrCyCo == true){KDEDQrCyCo = false;}
      if(nJBNHVsebZ == true){nJBNHVsebZ = false;}
      if(TrhAaZUdkW == true){TrhAaZUdkW = false;}
      if(waxAELgiHJ == true){waxAELgiHJ = false;}
      if(looidxRoca == true){looidxRoca = false;}
      if(PSQjRRUDcp == true){PSQjRRUDcp = false;}
      if(WXNesNMAJw == true){WXNesNMAJw = false;}
      if(oJWSndDzWd == true){oJWSndDzWd = false;}
      if(IeBKGdJNhl == true){IeBKGdJNhl = false;}
      if(pcGRlNbJoQ == true){pcGRlNbJoQ = false;}
      if(jRfgkGuyun == true){jRfgkGuyun = false;}
      if(OVgyhrWDXP == true){OVgyhrWDXP = false;}
      if(DyRWFMCFfa == true){DyRWFMCFfa = false;}
      if(CtJFsqzUYA == true){CtJFsqzUYA = false;}
      if(hLRtXUwHjt == true){hLRtXUwHjt = false;}
      if(qXkZNlzJaY == true){qXkZNlzJaY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SDLHZXNVSY
{ 
  void WwXxTymYeK()
  { 
      bool SRbFfsSTNa = false;
      bool OnDONnkmgT = false;
      bool ShMJDjYYMO = false;
      bool sxQAbiqgSH = false;
      bool FbJMGWsPID = false;
      bool qhsLUjFSBu = false;
      bool TsGygRWDle = false;
      bool wETZNpYzCg = false;
      bool qJQIWLDEfr = false;
      bool cYeWnMUKfn = false;
      bool ApdcGmOSxd = false;
      bool KFPUEKbxbV = false;
      bool NRWsBXYwkB = false;
      bool UNTOfBemCj = false;
      bool wjHBgXIKRc = false;
      bool jWiJahSjbi = false;
      bool NRhwIxlBnD = false;
      bool eourYcKVLd = false;
      bool OOdIRyeJny = false;
      bool huLSWeCKsj = false;
      string rzoaxMXQVR;
      string WYtkkdXfTd;
      string aMsXOiWQRi;
      string uxDSNMNEtY;
      string ssPTjngCBy;
      string AQsPNeGRMN;
      string oGzmWZUaWY;
      string PSlujgxYna;
      string CTPSheEnFi;
      string FwrfimtcxK;
      string SGebhhdxef;
      string hgdlLVpfEr;
      string UfVnSTZGLx;
      string mTbcHwnmjz;
      string AGIYAXSGUN;
      string wNXEolkqJO;
      string HXkhsNFAdP;
      string gDuEqOXwmt;
      string BTlyAYuWmU;
      string LxdVrcUafm;
      if(rzoaxMXQVR == SGebhhdxef){SRbFfsSTNa = true;}
      else if(SGebhhdxef == rzoaxMXQVR){ApdcGmOSxd = true;}
      if(WYtkkdXfTd == hgdlLVpfEr){OnDONnkmgT = true;}
      else if(hgdlLVpfEr == WYtkkdXfTd){KFPUEKbxbV = true;}
      if(aMsXOiWQRi == UfVnSTZGLx){ShMJDjYYMO = true;}
      else if(UfVnSTZGLx == aMsXOiWQRi){NRWsBXYwkB = true;}
      if(uxDSNMNEtY == mTbcHwnmjz){sxQAbiqgSH = true;}
      else if(mTbcHwnmjz == uxDSNMNEtY){UNTOfBemCj = true;}
      if(ssPTjngCBy == AGIYAXSGUN){FbJMGWsPID = true;}
      else if(AGIYAXSGUN == ssPTjngCBy){wjHBgXIKRc = true;}
      if(AQsPNeGRMN == wNXEolkqJO){qhsLUjFSBu = true;}
      else if(wNXEolkqJO == AQsPNeGRMN){jWiJahSjbi = true;}
      if(oGzmWZUaWY == HXkhsNFAdP){TsGygRWDle = true;}
      else if(HXkhsNFAdP == oGzmWZUaWY){NRhwIxlBnD = true;}
      if(PSlujgxYna == gDuEqOXwmt){wETZNpYzCg = true;}
      if(CTPSheEnFi == BTlyAYuWmU){qJQIWLDEfr = true;}
      if(FwrfimtcxK == LxdVrcUafm){cYeWnMUKfn = true;}
      while(gDuEqOXwmt == PSlujgxYna){eourYcKVLd = true;}
      while(BTlyAYuWmU == BTlyAYuWmU){OOdIRyeJny = true;}
      while(LxdVrcUafm == LxdVrcUafm){huLSWeCKsj = true;}
      if(SRbFfsSTNa == true){SRbFfsSTNa = false;}
      if(OnDONnkmgT == true){OnDONnkmgT = false;}
      if(ShMJDjYYMO == true){ShMJDjYYMO = false;}
      if(sxQAbiqgSH == true){sxQAbiqgSH = false;}
      if(FbJMGWsPID == true){FbJMGWsPID = false;}
      if(qhsLUjFSBu == true){qhsLUjFSBu = false;}
      if(TsGygRWDle == true){TsGygRWDle = false;}
      if(wETZNpYzCg == true){wETZNpYzCg = false;}
      if(qJQIWLDEfr == true){qJQIWLDEfr = false;}
      if(cYeWnMUKfn == true){cYeWnMUKfn = false;}
      if(ApdcGmOSxd == true){ApdcGmOSxd = false;}
      if(KFPUEKbxbV == true){KFPUEKbxbV = false;}
      if(NRWsBXYwkB == true){NRWsBXYwkB = false;}
      if(UNTOfBemCj == true){UNTOfBemCj = false;}
      if(wjHBgXIKRc == true){wjHBgXIKRc = false;}
      if(jWiJahSjbi == true){jWiJahSjbi = false;}
      if(NRhwIxlBnD == true){NRhwIxlBnD = false;}
      if(eourYcKVLd == true){eourYcKVLd = false;}
      if(OOdIRyeJny == true){OOdIRyeJny = false;}
      if(huLSWeCKsj == true){huLSWeCKsj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWHLECKDWO
{ 
  void wuenSiWDAj()
  { 
      bool cYMKJrMKfQ = false;
      bool jhJIknqueE = false;
      bool DFgqJPIlSi = false;
      bool BrApUVVEwO = false;
      bool OEUrVYoqCT = false;
      bool CbcrpXrVBs = false;
      bool iZrxOqhSmP = false;
      bool RlyPozjnVj = false;
      bool aRiyfYPIAw = false;
      bool cACDeoMXcd = false;
      bool qVDmBPdMDq = false;
      bool nDzQRRpsQp = false;
      bool bZRplRiukA = false;
      bool lLKqsENwwQ = false;
      bool uCEJIZAlkM = false;
      bool ySGmCRDMAj = false;
      bool fhbCEbrIXM = false;
      bool EtwAtZUIhM = false;
      bool RxKXBTFWob = false;
      bool BAwMjNZCFf = false;
      string tUHAxyeaKA;
      string knNXAFILbw;
      string liHbmxHVUI;
      string ZlFPrPmNiU;
      string YorLmODWZJ;
      string LajRrKNfNA;
      string qJGBazixek;
      string RtbGXxqunX;
      string tjuLwyBnXg;
      string CHAidPhpkn;
      string fFroqRzcst;
      string TRqoFGOuFb;
      string xuZyiKtrcH;
      string OAKAqnrFUe;
      string zXtcNjPKcX;
      string AmkIpkftGf;
      string WGAlfSGqxR;
      string NIaZbYAxjy;
      string tiPFGbPBJG;
      string HyznHsXIwt;
      if(tUHAxyeaKA == fFroqRzcst){cYMKJrMKfQ = true;}
      else if(fFroqRzcst == tUHAxyeaKA){qVDmBPdMDq = true;}
      if(knNXAFILbw == TRqoFGOuFb){jhJIknqueE = true;}
      else if(TRqoFGOuFb == knNXAFILbw){nDzQRRpsQp = true;}
      if(liHbmxHVUI == xuZyiKtrcH){DFgqJPIlSi = true;}
      else if(xuZyiKtrcH == liHbmxHVUI){bZRplRiukA = true;}
      if(ZlFPrPmNiU == OAKAqnrFUe){BrApUVVEwO = true;}
      else if(OAKAqnrFUe == ZlFPrPmNiU){lLKqsENwwQ = true;}
      if(YorLmODWZJ == zXtcNjPKcX){OEUrVYoqCT = true;}
      else if(zXtcNjPKcX == YorLmODWZJ){uCEJIZAlkM = true;}
      if(LajRrKNfNA == AmkIpkftGf){CbcrpXrVBs = true;}
      else if(AmkIpkftGf == LajRrKNfNA){ySGmCRDMAj = true;}
      if(qJGBazixek == WGAlfSGqxR){iZrxOqhSmP = true;}
      else if(WGAlfSGqxR == qJGBazixek){fhbCEbrIXM = true;}
      if(RtbGXxqunX == NIaZbYAxjy){RlyPozjnVj = true;}
      if(tjuLwyBnXg == tiPFGbPBJG){aRiyfYPIAw = true;}
      if(CHAidPhpkn == HyznHsXIwt){cACDeoMXcd = true;}
      while(NIaZbYAxjy == RtbGXxqunX){EtwAtZUIhM = true;}
      while(tiPFGbPBJG == tiPFGbPBJG){RxKXBTFWob = true;}
      while(HyznHsXIwt == HyznHsXIwt){BAwMjNZCFf = true;}
      if(cYMKJrMKfQ == true){cYMKJrMKfQ = false;}
      if(jhJIknqueE == true){jhJIknqueE = false;}
      if(DFgqJPIlSi == true){DFgqJPIlSi = false;}
      if(BrApUVVEwO == true){BrApUVVEwO = false;}
      if(OEUrVYoqCT == true){OEUrVYoqCT = false;}
      if(CbcrpXrVBs == true){CbcrpXrVBs = false;}
      if(iZrxOqhSmP == true){iZrxOqhSmP = false;}
      if(RlyPozjnVj == true){RlyPozjnVj = false;}
      if(aRiyfYPIAw == true){aRiyfYPIAw = false;}
      if(cACDeoMXcd == true){cACDeoMXcd = false;}
      if(qVDmBPdMDq == true){qVDmBPdMDq = false;}
      if(nDzQRRpsQp == true){nDzQRRpsQp = false;}
      if(bZRplRiukA == true){bZRplRiukA = false;}
      if(lLKqsENwwQ == true){lLKqsENwwQ = false;}
      if(uCEJIZAlkM == true){uCEJIZAlkM = false;}
      if(ySGmCRDMAj == true){ySGmCRDMAj = false;}
      if(fhbCEbrIXM == true){fhbCEbrIXM = false;}
      if(EtwAtZUIhM == true){EtwAtZUIhM = false;}
      if(RxKXBTFWob == true){RxKXBTFWob = false;}
      if(BAwMjNZCFf == true){BAwMjNZCFf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YZTCSRISWY
{ 
  void AsEoMzufZa()
  { 
      bool noiKmtmhof = false;
      bool FSVctzclfT = false;
      bool NjjAnNwAoz = false;
      bool wbnOBbLedQ = false;
      bool JrXBjfLmwN = false;
      bool daMQDEEhWY = false;
      bool xlroiceGbS = false;
      bool nxHPJUMiPH = false;
      bool BIEaVVOWLw = false;
      bool WcIESXzhRH = false;
      bool BFLdZgSxGh = false;
      bool rVSOXohRTN = false;
      bool NIueuLnCxl = false;
      bool UdQIGwwZBo = false;
      bool CRPcDBJtgc = false;
      bool phOEssKfiN = false;
      bool rQAUNOEKHa = false;
      bool rHQdLurRas = false;
      bool BsUTulPMON = false;
      bool kPqmwlRtPo = false;
      string uQLbkwMKLZ;
      string cQEHyiemZt;
      string xlaoZwxnhe;
      string KjSjPfRgTM;
      string azcqFdlcLz;
      string KbQapJpWCo;
      string zYbfOrxTqR;
      string RxTNSyIjiw;
      string JUciUhTrtG;
      string ptedNCWwbN;
      string fRlshMIDHr;
      string AFnFedusKf;
      string YFZkaWSoAQ;
      string aMIVPqiiBH;
      string ZPjBFkGYyi;
      string GdkunaqBSK;
      string sSDqQnwRpn;
      string uMqDGIVYeo;
      string QtpRKwaMgo;
      string zhQpNGMskQ;
      if(uQLbkwMKLZ == fRlshMIDHr){noiKmtmhof = true;}
      else if(fRlshMIDHr == uQLbkwMKLZ){BFLdZgSxGh = true;}
      if(cQEHyiemZt == AFnFedusKf){FSVctzclfT = true;}
      else if(AFnFedusKf == cQEHyiemZt){rVSOXohRTN = true;}
      if(xlaoZwxnhe == YFZkaWSoAQ){NjjAnNwAoz = true;}
      else if(YFZkaWSoAQ == xlaoZwxnhe){NIueuLnCxl = true;}
      if(KjSjPfRgTM == aMIVPqiiBH){wbnOBbLedQ = true;}
      else if(aMIVPqiiBH == KjSjPfRgTM){UdQIGwwZBo = true;}
      if(azcqFdlcLz == ZPjBFkGYyi){JrXBjfLmwN = true;}
      else if(ZPjBFkGYyi == azcqFdlcLz){CRPcDBJtgc = true;}
      if(KbQapJpWCo == GdkunaqBSK){daMQDEEhWY = true;}
      else if(GdkunaqBSK == KbQapJpWCo){phOEssKfiN = true;}
      if(zYbfOrxTqR == sSDqQnwRpn){xlroiceGbS = true;}
      else if(sSDqQnwRpn == zYbfOrxTqR){rQAUNOEKHa = true;}
      if(RxTNSyIjiw == uMqDGIVYeo){nxHPJUMiPH = true;}
      if(JUciUhTrtG == QtpRKwaMgo){BIEaVVOWLw = true;}
      if(ptedNCWwbN == zhQpNGMskQ){WcIESXzhRH = true;}
      while(uMqDGIVYeo == RxTNSyIjiw){rHQdLurRas = true;}
      while(QtpRKwaMgo == QtpRKwaMgo){BsUTulPMON = true;}
      while(zhQpNGMskQ == zhQpNGMskQ){kPqmwlRtPo = true;}
      if(noiKmtmhof == true){noiKmtmhof = false;}
      if(FSVctzclfT == true){FSVctzclfT = false;}
      if(NjjAnNwAoz == true){NjjAnNwAoz = false;}
      if(wbnOBbLedQ == true){wbnOBbLedQ = false;}
      if(JrXBjfLmwN == true){JrXBjfLmwN = false;}
      if(daMQDEEhWY == true){daMQDEEhWY = false;}
      if(xlroiceGbS == true){xlroiceGbS = false;}
      if(nxHPJUMiPH == true){nxHPJUMiPH = false;}
      if(BIEaVVOWLw == true){BIEaVVOWLw = false;}
      if(WcIESXzhRH == true){WcIESXzhRH = false;}
      if(BFLdZgSxGh == true){BFLdZgSxGh = false;}
      if(rVSOXohRTN == true){rVSOXohRTN = false;}
      if(NIueuLnCxl == true){NIueuLnCxl = false;}
      if(UdQIGwwZBo == true){UdQIGwwZBo = false;}
      if(CRPcDBJtgc == true){CRPcDBJtgc = false;}
      if(phOEssKfiN == true){phOEssKfiN = false;}
      if(rQAUNOEKHa == true){rQAUNOEKHa = false;}
      if(rHQdLurRas == true){rHQdLurRas = false;}
      if(BsUTulPMON == true){BsUTulPMON = false;}
      if(kPqmwlRtPo == true){kPqmwlRtPo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OYZUXXYKKJ
{ 
  void fgCjszCmpd()
  { 
      bool IiCmEjYhAC = false;
      bool spkUabWgHd = false;
      bool onEFGVwyNo = false;
      bool SAxRyfotpD = false;
      bool wApQqDJBEG = false;
      bool VWzEPTdwgh = false;
      bool mZTKjssSVt = false;
      bool lcpEgoynOC = false;
      bool MutHSwBrBd = false;
      bool CsNIPVfegx = false;
      bool KpeJTsftWa = false;
      bool VpgdUrfLrn = false;
      bool rARrrsOhoL = false;
      bool ISGRrWQkmY = false;
      bool PGVaHLLjmW = false;
      bool pUmsEKXmQa = false;
      bool dxFLRCiPky = false;
      bool buXSXldqjg = false;
      bool geuRUnfNMh = false;
      bool ydTMuSAKIF = false;
      string qFBZDSOTYV;
      string qkLxYzAhdR;
      string HTLRCrjcmT;
      string RSmxjlGsMX;
      string GifUyHuWIE;
      string MtwytWtiXL;
      string hkgEEXxNNl;
      string rHVFLYmpSu;
      string wNUhGWVnCM;
      string rWVBpUBbQa;
      string JgJWLFYqlV;
      string iEPbOUQzxg;
      string BILAtVkTPq;
      string WLYrkODxVB;
      string yeBfcmGslU;
      string DCdiYAVIbp;
      string TEauyXeXqz;
      string QSdwiWGeXG;
      string OrgtmUhpSk;
      string stVehsDGhF;
      if(qFBZDSOTYV == JgJWLFYqlV){IiCmEjYhAC = true;}
      else if(JgJWLFYqlV == qFBZDSOTYV){KpeJTsftWa = true;}
      if(qkLxYzAhdR == iEPbOUQzxg){spkUabWgHd = true;}
      else if(iEPbOUQzxg == qkLxYzAhdR){VpgdUrfLrn = true;}
      if(HTLRCrjcmT == BILAtVkTPq){onEFGVwyNo = true;}
      else if(BILAtVkTPq == HTLRCrjcmT){rARrrsOhoL = true;}
      if(RSmxjlGsMX == WLYrkODxVB){SAxRyfotpD = true;}
      else if(WLYrkODxVB == RSmxjlGsMX){ISGRrWQkmY = true;}
      if(GifUyHuWIE == yeBfcmGslU){wApQqDJBEG = true;}
      else if(yeBfcmGslU == GifUyHuWIE){PGVaHLLjmW = true;}
      if(MtwytWtiXL == DCdiYAVIbp){VWzEPTdwgh = true;}
      else if(DCdiYAVIbp == MtwytWtiXL){pUmsEKXmQa = true;}
      if(hkgEEXxNNl == TEauyXeXqz){mZTKjssSVt = true;}
      else if(TEauyXeXqz == hkgEEXxNNl){dxFLRCiPky = true;}
      if(rHVFLYmpSu == QSdwiWGeXG){lcpEgoynOC = true;}
      if(wNUhGWVnCM == OrgtmUhpSk){MutHSwBrBd = true;}
      if(rWVBpUBbQa == stVehsDGhF){CsNIPVfegx = true;}
      while(QSdwiWGeXG == rHVFLYmpSu){buXSXldqjg = true;}
      while(OrgtmUhpSk == OrgtmUhpSk){geuRUnfNMh = true;}
      while(stVehsDGhF == stVehsDGhF){ydTMuSAKIF = true;}
      if(IiCmEjYhAC == true){IiCmEjYhAC = false;}
      if(spkUabWgHd == true){spkUabWgHd = false;}
      if(onEFGVwyNo == true){onEFGVwyNo = false;}
      if(SAxRyfotpD == true){SAxRyfotpD = false;}
      if(wApQqDJBEG == true){wApQqDJBEG = false;}
      if(VWzEPTdwgh == true){VWzEPTdwgh = false;}
      if(mZTKjssSVt == true){mZTKjssSVt = false;}
      if(lcpEgoynOC == true){lcpEgoynOC = false;}
      if(MutHSwBrBd == true){MutHSwBrBd = false;}
      if(CsNIPVfegx == true){CsNIPVfegx = false;}
      if(KpeJTsftWa == true){KpeJTsftWa = false;}
      if(VpgdUrfLrn == true){VpgdUrfLrn = false;}
      if(rARrrsOhoL == true){rARrrsOhoL = false;}
      if(ISGRrWQkmY == true){ISGRrWQkmY = false;}
      if(PGVaHLLjmW == true){PGVaHLLjmW = false;}
      if(pUmsEKXmQa == true){pUmsEKXmQa = false;}
      if(dxFLRCiPky == true){dxFLRCiPky = false;}
      if(buXSXldqjg == true){buXSXldqjg = false;}
      if(geuRUnfNMh == true){geuRUnfNMh = false;}
      if(ydTMuSAKIF == true){ydTMuSAKIF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QHTPGYYVLD
{ 
  void GJsoDnAkPb()
  { 
      bool rSVtPEgsOK = false;
      bool BpxNBIJcKo = false;
      bool CththcrSfg = false;
      bool OdBtYAFFFW = false;
      bool riVadEMLbl = false;
      bool HhttmykbMl = false;
      bool LOMhuXoCoA = false;
      bool CEWmxTXGPc = false;
      bool PgptYfjGHZ = false;
      bool PdrSLdVmfG = false;
      bool OKWaiDLGxS = false;
      bool ZeLjWdXRIP = false;
      bool nitOkYLDaS = false;
      bool xkZJNFJOKV = false;
      bool UcJnzkRIwg = false;
      bool FDdQSfPIoK = false;
      bool qHedVoECVR = false;
      bool TIGmtKYGOA = false;
      bool HDHtNsGJqg = false;
      bool oBYAeMxfSK = false;
      string pIDugRdsBP;
      string QzInAoKDpf;
      string KsyWfxKhdG;
      string kDBGqKIAHm;
      string nlVPgHOhJG;
      string ScYapxKfOi;
      string GuPueNyBxo;
      string gJuDqXWhpY;
      string ibYWnHdZQs;
      string AblXfsVajT;
      string IMkTYIgUjR;
      string ZcppAdWsGX;
      string iYkDoFXXWy;
      string CwxWPWqExe;
      string ZIpzTXlwXC;
      string WcTMjjbgeT;
      string jJxlPdeTZc;
      string mRuaxZhkjR;
      string SbzUaZbklf;
      string uJYctQKEjo;
      if(pIDugRdsBP == IMkTYIgUjR){rSVtPEgsOK = true;}
      else if(IMkTYIgUjR == pIDugRdsBP){OKWaiDLGxS = true;}
      if(QzInAoKDpf == ZcppAdWsGX){BpxNBIJcKo = true;}
      else if(ZcppAdWsGX == QzInAoKDpf){ZeLjWdXRIP = true;}
      if(KsyWfxKhdG == iYkDoFXXWy){CththcrSfg = true;}
      else if(iYkDoFXXWy == KsyWfxKhdG){nitOkYLDaS = true;}
      if(kDBGqKIAHm == CwxWPWqExe){OdBtYAFFFW = true;}
      else if(CwxWPWqExe == kDBGqKIAHm){xkZJNFJOKV = true;}
      if(nlVPgHOhJG == ZIpzTXlwXC){riVadEMLbl = true;}
      else if(ZIpzTXlwXC == nlVPgHOhJG){UcJnzkRIwg = true;}
      if(ScYapxKfOi == WcTMjjbgeT){HhttmykbMl = true;}
      else if(WcTMjjbgeT == ScYapxKfOi){FDdQSfPIoK = true;}
      if(GuPueNyBxo == jJxlPdeTZc){LOMhuXoCoA = true;}
      else if(jJxlPdeTZc == GuPueNyBxo){qHedVoECVR = true;}
      if(gJuDqXWhpY == mRuaxZhkjR){CEWmxTXGPc = true;}
      if(ibYWnHdZQs == SbzUaZbklf){PgptYfjGHZ = true;}
      if(AblXfsVajT == uJYctQKEjo){PdrSLdVmfG = true;}
      while(mRuaxZhkjR == gJuDqXWhpY){TIGmtKYGOA = true;}
      while(SbzUaZbklf == SbzUaZbklf){HDHtNsGJqg = true;}
      while(uJYctQKEjo == uJYctQKEjo){oBYAeMxfSK = true;}
      if(rSVtPEgsOK == true){rSVtPEgsOK = false;}
      if(BpxNBIJcKo == true){BpxNBIJcKo = false;}
      if(CththcrSfg == true){CththcrSfg = false;}
      if(OdBtYAFFFW == true){OdBtYAFFFW = false;}
      if(riVadEMLbl == true){riVadEMLbl = false;}
      if(HhttmykbMl == true){HhttmykbMl = false;}
      if(LOMhuXoCoA == true){LOMhuXoCoA = false;}
      if(CEWmxTXGPc == true){CEWmxTXGPc = false;}
      if(PgptYfjGHZ == true){PgptYfjGHZ = false;}
      if(PdrSLdVmfG == true){PdrSLdVmfG = false;}
      if(OKWaiDLGxS == true){OKWaiDLGxS = false;}
      if(ZeLjWdXRIP == true){ZeLjWdXRIP = false;}
      if(nitOkYLDaS == true){nitOkYLDaS = false;}
      if(xkZJNFJOKV == true){xkZJNFJOKV = false;}
      if(UcJnzkRIwg == true){UcJnzkRIwg = false;}
      if(FDdQSfPIoK == true){FDdQSfPIoK = false;}
      if(qHedVoECVR == true){qHedVoECVR = false;}
      if(TIGmtKYGOA == true){TIGmtKYGOA = false;}
      if(HDHtNsGJqg == true){HDHtNsGJqg = false;}
      if(oBYAeMxfSK == true){oBYAeMxfSK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DVKVQSDSPR
{ 
  void QsVQVVjmNl()
  { 
      bool iZrVTCKcSu = false;
      bool dWlkYtxdAh = false;
      bool KVsGwQlIDZ = false;
      bool MSMrIEibdo = false;
      bool AoIqpJRMnh = false;
      bool IMkwKMgkYD = false;
      bool PBZshKJsbU = false;
      bool LVzKhVNCPm = false;
      bool zYUVQzhQgw = false;
      bool WxDaYyOOIf = false;
      bool zXkTVmMaNo = false;
      bool yeVkEqgDch = false;
      bool brLfxNRYki = false;
      bool GzsjnanAzc = false;
      bool mHCrxrbRVh = false;
      bool RLkZDGLEVH = false;
      bool Vmoehzkkxd = false;
      bool CfEAuTpSiF = false;
      bool lzDCRuNSfg = false;
      bool OieqHzRXKx = false;
      string TwNJIrpdGY;
      string IhUxNxaZAL;
      string NwPoPRCEqO;
      string yzzAcksnKB;
      string iEfHgxwicp;
      string BFOzsWfYsp;
      string plmqZJhUUb;
      string DmPybIQHIR;
      string USaBMrjAGF;
      string EUtTLxRngX;
      string PbOAlOpPWj;
      string GXPbVXKkdh;
      string YgNOXisume;
      string qbakBsDaPy;
      string BUcWzfERyn;
      string lfJzzhNAcC;
      string VucrrdxeZc;
      string TjVffEEqOq;
      string daxyrKSalT;
      string fDxMcGqkdV;
      if(TwNJIrpdGY == PbOAlOpPWj){iZrVTCKcSu = true;}
      else if(PbOAlOpPWj == TwNJIrpdGY){zXkTVmMaNo = true;}
      if(IhUxNxaZAL == GXPbVXKkdh){dWlkYtxdAh = true;}
      else if(GXPbVXKkdh == IhUxNxaZAL){yeVkEqgDch = true;}
      if(NwPoPRCEqO == YgNOXisume){KVsGwQlIDZ = true;}
      else if(YgNOXisume == NwPoPRCEqO){brLfxNRYki = true;}
      if(yzzAcksnKB == qbakBsDaPy){MSMrIEibdo = true;}
      else if(qbakBsDaPy == yzzAcksnKB){GzsjnanAzc = true;}
      if(iEfHgxwicp == BUcWzfERyn){AoIqpJRMnh = true;}
      else if(BUcWzfERyn == iEfHgxwicp){mHCrxrbRVh = true;}
      if(BFOzsWfYsp == lfJzzhNAcC){IMkwKMgkYD = true;}
      else if(lfJzzhNAcC == BFOzsWfYsp){RLkZDGLEVH = true;}
      if(plmqZJhUUb == VucrrdxeZc){PBZshKJsbU = true;}
      else if(VucrrdxeZc == plmqZJhUUb){Vmoehzkkxd = true;}
      if(DmPybIQHIR == TjVffEEqOq){LVzKhVNCPm = true;}
      if(USaBMrjAGF == daxyrKSalT){zYUVQzhQgw = true;}
      if(EUtTLxRngX == fDxMcGqkdV){WxDaYyOOIf = true;}
      while(TjVffEEqOq == DmPybIQHIR){CfEAuTpSiF = true;}
      while(daxyrKSalT == daxyrKSalT){lzDCRuNSfg = true;}
      while(fDxMcGqkdV == fDxMcGqkdV){OieqHzRXKx = true;}
      if(iZrVTCKcSu == true){iZrVTCKcSu = false;}
      if(dWlkYtxdAh == true){dWlkYtxdAh = false;}
      if(KVsGwQlIDZ == true){KVsGwQlIDZ = false;}
      if(MSMrIEibdo == true){MSMrIEibdo = false;}
      if(AoIqpJRMnh == true){AoIqpJRMnh = false;}
      if(IMkwKMgkYD == true){IMkwKMgkYD = false;}
      if(PBZshKJsbU == true){PBZshKJsbU = false;}
      if(LVzKhVNCPm == true){LVzKhVNCPm = false;}
      if(zYUVQzhQgw == true){zYUVQzhQgw = false;}
      if(WxDaYyOOIf == true){WxDaYyOOIf = false;}
      if(zXkTVmMaNo == true){zXkTVmMaNo = false;}
      if(yeVkEqgDch == true){yeVkEqgDch = false;}
      if(brLfxNRYki == true){brLfxNRYki = false;}
      if(GzsjnanAzc == true){GzsjnanAzc = false;}
      if(mHCrxrbRVh == true){mHCrxrbRVh = false;}
      if(RLkZDGLEVH == true){RLkZDGLEVH = false;}
      if(Vmoehzkkxd == true){Vmoehzkkxd = false;}
      if(CfEAuTpSiF == true){CfEAuTpSiF = false;}
      if(lzDCRuNSfg == true){lzDCRuNSfg = false;}
      if(OieqHzRXKx == true){OieqHzRXKx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XVDRJCLNQI
{ 
  void IEuaJNFNtB()
  { 
      bool QoXSACAWVO = false;
      bool kmBeodzEPt = false;
      bool tpScydjTmW = false;
      bool hPpNEjBZKR = false;
      bool MczcGOJTgy = false;
      bool EYGqMZWuTV = false;
      bool RfiyfUxmaF = false;
      bool cZtxgQqpVj = false;
      bool TQmoRJJyBd = false;
      bool NGFnAfsAwl = false;
      bool QVsbVedIJw = false;
      bool ifYiBBstfW = false;
      bool KykwqWTFwA = false;
      bool WpsjSyWKSm = false;
      bool eAoFuggWly = false;
      bool mzTZaSjwkz = false;
      bool KYMIYrmoQD = false;
      bool eiasrKJfBJ = false;
      bool oxTyNXVTJA = false;
      bool NZZTbGnffC = false;
      string aoQlYRZhUR;
      string sARBTLbxPY;
      string EPaocHWuaS;
      string wgMruSFjBF;
      string ydnoqBHxyw;
      string OyYQmKNaJQ;
      string teHCVMmYGB;
      string FruKZaakxb;
      string zYwdDyHwEj;
      string EeZjKTVlTe;
      string NiqxqVCOpM;
      string icdhRVhdyW;
      string EqTVxaRKzG;
      string FoRSNQgzmg;
      string usFrBbArSo;
      string krnwaVOVAP;
      string EqPjHtKKTA;
      string oiqQaLkaUU;
      string ZZrKUNAUrq;
      string BKyWcEdVkG;
      if(aoQlYRZhUR == NiqxqVCOpM){QoXSACAWVO = true;}
      else if(NiqxqVCOpM == aoQlYRZhUR){QVsbVedIJw = true;}
      if(sARBTLbxPY == icdhRVhdyW){kmBeodzEPt = true;}
      else if(icdhRVhdyW == sARBTLbxPY){ifYiBBstfW = true;}
      if(EPaocHWuaS == EqTVxaRKzG){tpScydjTmW = true;}
      else if(EqTVxaRKzG == EPaocHWuaS){KykwqWTFwA = true;}
      if(wgMruSFjBF == FoRSNQgzmg){hPpNEjBZKR = true;}
      else if(FoRSNQgzmg == wgMruSFjBF){WpsjSyWKSm = true;}
      if(ydnoqBHxyw == usFrBbArSo){MczcGOJTgy = true;}
      else if(usFrBbArSo == ydnoqBHxyw){eAoFuggWly = true;}
      if(OyYQmKNaJQ == krnwaVOVAP){EYGqMZWuTV = true;}
      else if(krnwaVOVAP == OyYQmKNaJQ){mzTZaSjwkz = true;}
      if(teHCVMmYGB == EqPjHtKKTA){RfiyfUxmaF = true;}
      else if(EqPjHtKKTA == teHCVMmYGB){KYMIYrmoQD = true;}
      if(FruKZaakxb == oiqQaLkaUU){cZtxgQqpVj = true;}
      if(zYwdDyHwEj == ZZrKUNAUrq){TQmoRJJyBd = true;}
      if(EeZjKTVlTe == BKyWcEdVkG){NGFnAfsAwl = true;}
      while(oiqQaLkaUU == FruKZaakxb){eiasrKJfBJ = true;}
      while(ZZrKUNAUrq == ZZrKUNAUrq){oxTyNXVTJA = true;}
      while(BKyWcEdVkG == BKyWcEdVkG){NZZTbGnffC = true;}
      if(QoXSACAWVO == true){QoXSACAWVO = false;}
      if(kmBeodzEPt == true){kmBeodzEPt = false;}
      if(tpScydjTmW == true){tpScydjTmW = false;}
      if(hPpNEjBZKR == true){hPpNEjBZKR = false;}
      if(MczcGOJTgy == true){MczcGOJTgy = false;}
      if(EYGqMZWuTV == true){EYGqMZWuTV = false;}
      if(RfiyfUxmaF == true){RfiyfUxmaF = false;}
      if(cZtxgQqpVj == true){cZtxgQqpVj = false;}
      if(TQmoRJJyBd == true){TQmoRJJyBd = false;}
      if(NGFnAfsAwl == true){NGFnAfsAwl = false;}
      if(QVsbVedIJw == true){QVsbVedIJw = false;}
      if(ifYiBBstfW == true){ifYiBBstfW = false;}
      if(KykwqWTFwA == true){KykwqWTFwA = false;}
      if(WpsjSyWKSm == true){WpsjSyWKSm = false;}
      if(eAoFuggWly == true){eAoFuggWly = false;}
      if(mzTZaSjwkz == true){mzTZaSjwkz = false;}
      if(KYMIYrmoQD == true){KYMIYrmoQD = false;}
      if(eiasrKJfBJ == true){eiasrKJfBJ = false;}
      if(oxTyNXVTJA == true){oxTyNXVTJA = false;}
      if(NZZTbGnffC == true){NZZTbGnffC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TQSOVEEOUQ
{ 
  void zlWuwmWRZy()
  { 
      bool ILgRZAibUE = false;
      bool GqORVPATcR = false;
      bool rdtCMGNLTw = false;
      bool ntxFFOPzpA = false;
      bool ALrfphiYdK = false;
      bool ijIcedQdES = false;
      bool mWHXQMsIMH = false;
      bool ABcbQgkNLe = false;
      bool WnhJMEkUaa = false;
      bool xktXNdDTPd = false;
      bool nZLWJgGgLy = false;
      bool rDSZuyoxKL = false;
      bool aYhlKPGFOm = false;
      bool cRxgpwbKAf = false;
      bool xEIbhsRUbO = false;
      bool nGIEDPqZMt = false;
      bool ZBSYUaGljy = false;
      bool WdxeOVQFDQ = false;
      bool xldAyWIsdZ = false;
      bool EByFFwliHH = false;
      string gBSBtYJDTR;
      string PVNdPDNqAK;
      string ybCqyUPToK;
      string uQYtABgTXg;
      string WQMFdepBFh;
      string hFxYPFzbDZ;
      string IoNIWzwScN;
      string VsSSmhOwMS;
      string eOOGboSAdu;
      string BFQyYgCDid;
      string hWYqLomdkh;
      string qDOjttaGgh;
      string gungLQcUtG;
      string fKMijHoWul;
      string BnPwEyqfDd;
      string FuWAxmiqeu;
      string MRjdCfpezl;
      string EELtfrfqcN;
      string ZwQPBjnMkx;
      string YyqzZjEktX;
      if(gBSBtYJDTR == hWYqLomdkh){ILgRZAibUE = true;}
      else if(hWYqLomdkh == gBSBtYJDTR){nZLWJgGgLy = true;}
      if(PVNdPDNqAK == qDOjttaGgh){GqORVPATcR = true;}
      else if(qDOjttaGgh == PVNdPDNqAK){rDSZuyoxKL = true;}
      if(ybCqyUPToK == gungLQcUtG){rdtCMGNLTw = true;}
      else if(gungLQcUtG == ybCqyUPToK){aYhlKPGFOm = true;}
      if(uQYtABgTXg == fKMijHoWul){ntxFFOPzpA = true;}
      else if(fKMijHoWul == uQYtABgTXg){cRxgpwbKAf = true;}
      if(WQMFdepBFh == BnPwEyqfDd){ALrfphiYdK = true;}
      else if(BnPwEyqfDd == WQMFdepBFh){xEIbhsRUbO = true;}
      if(hFxYPFzbDZ == FuWAxmiqeu){ijIcedQdES = true;}
      else if(FuWAxmiqeu == hFxYPFzbDZ){nGIEDPqZMt = true;}
      if(IoNIWzwScN == MRjdCfpezl){mWHXQMsIMH = true;}
      else if(MRjdCfpezl == IoNIWzwScN){ZBSYUaGljy = true;}
      if(VsSSmhOwMS == EELtfrfqcN){ABcbQgkNLe = true;}
      if(eOOGboSAdu == ZwQPBjnMkx){WnhJMEkUaa = true;}
      if(BFQyYgCDid == YyqzZjEktX){xktXNdDTPd = true;}
      while(EELtfrfqcN == VsSSmhOwMS){WdxeOVQFDQ = true;}
      while(ZwQPBjnMkx == ZwQPBjnMkx){xldAyWIsdZ = true;}
      while(YyqzZjEktX == YyqzZjEktX){EByFFwliHH = true;}
      if(ILgRZAibUE == true){ILgRZAibUE = false;}
      if(GqORVPATcR == true){GqORVPATcR = false;}
      if(rdtCMGNLTw == true){rdtCMGNLTw = false;}
      if(ntxFFOPzpA == true){ntxFFOPzpA = false;}
      if(ALrfphiYdK == true){ALrfphiYdK = false;}
      if(ijIcedQdES == true){ijIcedQdES = false;}
      if(mWHXQMsIMH == true){mWHXQMsIMH = false;}
      if(ABcbQgkNLe == true){ABcbQgkNLe = false;}
      if(WnhJMEkUaa == true){WnhJMEkUaa = false;}
      if(xktXNdDTPd == true){xktXNdDTPd = false;}
      if(nZLWJgGgLy == true){nZLWJgGgLy = false;}
      if(rDSZuyoxKL == true){rDSZuyoxKL = false;}
      if(aYhlKPGFOm == true){aYhlKPGFOm = false;}
      if(cRxgpwbKAf == true){cRxgpwbKAf = false;}
      if(xEIbhsRUbO == true){xEIbhsRUbO = false;}
      if(nGIEDPqZMt == true){nGIEDPqZMt = false;}
      if(ZBSYUaGljy == true){ZBSYUaGljy = false;}
      if(WdxeOVQFDQ == true){WdxeOVQFDQ = false;}
      if(xldAyWIsdZ == true){xldAyWIsdZ = false;}
      if(EByFFwliHH == true){EByFFwliHH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBSFNRPQYF
{ 
  void YtMUXkdnZa()
  { 
      bool BZqksgHVad = false;
      bool nKeKDpLByx = false;
      bool jTTMEgUcWt = false;
      bool pbsKyymqaF = false;
      bool LidalyyrTH = false;
      bool npQLGgGdfL = false;
      bool LeygnLQUME = false;
      bool CUarlBpraG = false;
      bool hcIPFAKhDQ = false;
      bool rJKOtfkxma = false;
      bool hdeOETPYZF = false;
      bool qNDYdhVham = false;
      bool AiQwMsJLyF = false;
      bool QrFAYDxtLl = false;
      bool klIyYeFlkL = false;
      bool KCWzZyNiCL = false;
      bool JEaTozIDAZ = false;
      bool kbWoCOZSWh = false;
      bool mXZltNVFZZ = false;
      bool pNqzbgKnJZ = false;
      string hCBEmmWDhK;
      string HSmVMOclWJ;
      string ncVlerpmGC;
      string YCssWJDwcX;
      string ZEGpMzhOoJ;
      string IWtNbFgPYt;
      string xjxekEZszD;
      string KfIziiVfZf;
      string KayxsCIfRQ;
      string bnXhapHaEH;
      string ZnPkycNtdr;
      string jApsjVkzki;
      string usbiaWIZYr;
      string btaRGVKMzQ;
      string nNBYgaydyE;
      string FIpVLfMgKb;
      string TmVlQoZYmN;
      string LXATthrCBz;
      string XdbTmSEFFZ;
      string IdCWxAqPIq;
      if(hCBEmmWDhK == ZnPkycNtdr){BZqksgHVad = true;}
      else if(ZnPkycNtdr == hCBEmmWDhK){hdeOETPYZF = true;}
      if(HSmVMOclWJ == jApsjVkzki){nKeKDpLByx = true;}
      else if(jApsjVkzki == HSmVMOclWJ){qNDYdhVham = true;}
      if(ncVlerpmGC == usbiaWIZYr){jTTMEgUcWt = true;}
      else if(usbiaWIZYr == ncVlerpmGC){AiQwMsJLyF = true;}
      if(YCssWJDwcX == btaRGVKMzQ){pbsKyymqaF = true;}
      else if(btaRGVKMzQ == YCssWJDwcX){QrFAYDxtLl = true;}
      if(ZEGpMzhOoJ == nNBYgaydyE){LidalyyrTH = true;}
      else if(nNBYgaydyE == ZEGpMzhOoJ){klIyYeFlkL = true;}
      if(IWtNbFgPYt == FIpVLfMgKb){npQLGgGdfL = true;}
      else if(FIpVLfMgKb == IWtNbFgPYt){KCWzZyNiCL = true;}
      if(xjxekEZszD == TmVlQoZYmN){LeygnLQUME = true;}
      else if(TmVlQoZYmN == xjxekEZszD){JEaTozIDAZ = true;}
      if(KfIziiVfZf == LXATthrCBz){CUarlBpraG = true;}
      if(KayxsCIfRQ == XdbTmSEFFZ){hcIPFAKhDQ = true;}
      if(bnXhapHaEH == IdCWxAqPIq){rJKOtfkxma = true;}
      while(LXATthrCBz == KfIziiVfZf){kbWoCOZSWh = true;}
      while(XdbTmSEFFZ == XdbTmSEFFZ){mXZltNVFZZ = true;}
      while(IdCWxAqPIq == IdCWxAqPIq){pNqzbgKnJZ = true;}
      if(BZqksgHVad == true){BZqksgHVad = false;}
      if(nKeKDpLByx == true){nKeKDpLByx = false;}
      if(jTTMEgUcWt == true){jTTMEgUcWt = false;}
      if(pbsKyymqaF == true){pbsKyymqaF = false;}
      if(LidalyyrTH == true){LidalyyrTH = false;}
      if(npQLGgGdfL == true){npQLGgGdfL = false;}
      if(LeygnLQUME == true){LeygnLQUME = false;}
      if(CUarlBpraG == true){CUarlBpraG = false;}
      if(hcIPFAKhDQ == true){hcIPFAKhDQ = false;}
      if(rJKOtfkxma == true){rJKOtfkxma = false;}
      if(hdeOETPYZF == true){hdeOETPYZF = false;}
      if(qNDYdhVham == true){qNDYdhVham = false;}
      if(AiQwMsJLyF == true){AiQwMsJLyF = false;}
      if(QrFAYDxtLl == true){QrFAYDxtLl = false;}
      if(klIyYeFlkL == true){klIyYeFlkL = false;}
      if(KCWzZyNiCL == true){KCWzZyNiCL = false;}
      if(JEaTozIDAZ == true){JEaTozIDAZ = false;}
      if(kbWoCOZSWh == true){kbWoCOZSWh = false;}
      if(mXZltNVFZZ == true){mXZltNVFZZ = false;}
      if(pNqzbgKnJZ == true){pNqzbgKnJZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UFSZXEQEBA
{ 
  void lSrjkTbdgM()
  { 
      bool ojuIQTsWUn = false;
      bool arNzTowJQC = false;
      bool rNPwPhhClg = false;
      bool rdymUlnLWR = false;
      bool mgZVqwmkzO = false;
      bool uMVWQaTzrh = false;
      bool kpjmuxsaeg = false;
      bool AkmyPLntES = false;
      bool uxDXkfIaVt = false;
      bool SoSnfxwlZt = false;
      bool CLGSNKYWHF = false;
      bool lYtYlnlMCP = false;
      bool oSEkNLRzRS = false;
      bool OCTKPjqkJa = false;
      bool HkTQHstsBr = false;
      bool KjjKEjGVEC = false;
      bool rZEoqjEiIC = false;
      bool wBCaHDyncU = false;
      bool QXxZHdRJGe = false;
      bool cVgHhggdZW = false;
      string uhFOEQFnLz;
      string KxiuEHzGpC;
      string tmYVfiBfdx;
      string MWXKaCeTxI;
      string bErLYXZfSy;
      string AHSEUHJihV;
      string OZKOlmZYUB;
      string bfJgaptNxI;
      string IVMewFEToS;
      string swkasBtdZk;
      string yBLRVTxkce;
      string MwlZMsNeRf;
      string hGiBHfuhmZ;
      string uQmLKHKtIb;
      string HTpJFxJLNA;
      string mOMsCqRJJp;
      string YPxDiwIZPF;
      string iSVoYOQYuJ;
      string WjTmlfEtJS;
      string oAkSDqVlZI;
      if(uhFOEQFnLz == yBLRVTxkce){ojuIQTsWUn = true;}
      else if(yBLRVTxkce == uhFOEQFnLz){CLGSNKYWHF = true;}
      if(KxiuEHzGpC == MwlZMsNeRf){arNzTowJQC = true;}
      else if(MwlZMsNeRf == KxiuEHzGpC){lYtYlnlMCP = true;}
      if(tmYVfiBfdx == hGiBHfuhmZ){rNPwPhhClg = true;}
      else if(hGiBHfuhmZ == tmYVfiBfdx){oSEkNLRzRS = true;}
      if(MWXKaCeTxI == uQmLKHKtIb){rdymUlnLWR = true;}
      else if(uQmLKHKtIb == MWXKaCeTxI){OCTKPjqkJa = true;}
      if(bErLYXZfSy == HTpJFxJLNA){mgZVqwmkzO = true;}
      else if(HTpJFxJLNA == bErLYXZfSy){HkTQHstsBr = true;}
      if(AHSEUHJihV == mOMsCqRJJp){uMVWQaTzrh = true;}
      else if(mOMsCqRJJp == AHSEUHJihV){KjjKEjGVEC = true;}
      if(OZKOlmZYUB == YPxDiwIZPF){kpjmuxsaeg = true;}
      else if(YPxDiwIZPF == OZKOlmZYUB){rZEoqjEiIC = true;}
      if(bfJgaptNxI == iSVoYOQYuJ){AkmyPLntES = true;}
      if(IVMewFEToS == WjTmlfEtJS){uxDXkfIaVt = true;}
      if(swkasBtdZk == oAkSDqVlZI){SoSnfxwlZt = true;}
      while(iSVoYOQYuJ == bfJgaptNxI){wBCaHDyncU = true;}
      while(WjTmlfEtJS == WjTmlfEtJS){QXxZHdRJGe = true;}
      while(oAkSDqVlZI == oAkSDqVlZI){cVgHhggdZW = true;}
      if(ojuIQTsWUn == true){ojuIQTsWUn = false;}
      if(arNzTowJQC == true){arNzTowJQC = false;}
      if(rNPwPhhClg == true){rNPwPhhClg = false;}
      if(rdymUlnLWR == true){rdymUlnLWR = false;}
      if(mgZVqwmkzO == true){mgZVqwmkzO = false;}
      if(uMVWQaTzrh == true){uMVWQaTzrh = false;}
      if(kpjmuxsaeg == true){kpjmuxsaeg = false;}
      if(AkmyPLntES == true){AkmyPLntES = false;}
      if(uxDXkfIaVt == true){uxDXkfIaVt = false;}
      if(SoSnfxwlZt == true){SoSnfxwlZt = false;}
      if(CLGSNKYWHF == true){CLGSNKYWHF = false;}
      if(lYtYlnlMCP == true){lYtYlnlMCP = false;}
      if(oSEkNLRzRS == true){oSEkNLRzRS = false;}
      if(OCTKPjqkJa == true){OCTKPjqkJa = false;}
      if(HkTQHstsBr == true){HkTQHstsBr = false;}
      if(KjjKEjGVEC == true){KjjKEjGVEC = false;}
      if(rZEoqjEiIC == true){rZEoqjEiIC = false;}
      if(wBCaHDyncU == true){wBCaHDyncU = false;}
      if(QXxZHdRJGe == true){QXxZHdRJGe = false;}
      if(cVgHhggdZW == true){cVgHhggdZW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JFLZDDSRWV
{ 
  void UJsKGSSYgJ()
  { 
      bool VabcUqXYWO = false;
      bool nGsFpyPDQH = false;
      bool wLcyNBkjDe = false;
      bool ZXAgcKpkAn = false;
      bool uqVeBQQmOc = false;
      bool HLOLGJycOS = false;
      bool FmUroQFLbe = false;
      bool IdCcLFpxww = false;
      bool kyUZXNIoaT = false;
      bool MMWhhHVdpk = false;
      bool LEKjUcIlzB = false;
      bool TAgSgHSuTa = false;
      bool IPjISwHUtD = false;
      bool iMGLkfnkFt = false;
      bool FVpZALeDAa = false;
      bool oaJPcuTBQX = false;
      bool VnruRGsUgA = false;
      bool TgoZVlZKIG = false;
      bool QDUTOIDqio = false;
      bool MlTgXRdtIs = false;
      string YsNUzNWYkx;
      string TWbYbduohq;
      string JseJmftWKS;
      string mZQQbIYWPz;
      string uwulcewbwR;
      string YeJqSeNDgS;
      string SAORKtFKxS;
      string FYYhuMxrgI;
      string jSZssHPYyw;
      string tUoxfuhcbh;
      string YldcMAGawF;
      string gUVXiAaUYC;
      string dgLAYjibBz;
      string eUQyixnxfs;
      string BocrPZyQNf;
      string UMEYErZdEb;
      string QdYwZMEXok;
      string LdnfBoDTjy;
      string lROUeSPrtp;
      string XJrEbWPfSC;
      if(YsNUzNWYkx == YldcMAGawF){VabcUqXYWO = true;}
      else if(YldcMAGawF == YsNUzNWYkx){LEKjUcIlzB = true;}
      if(TWbYbduohq == gUVXiAaUYC){nGsFpyPDQH = true;}
      else if(gUVXiAaUYC == TWbYbduohq){TAgSgHSuTa = true;}
      if(JseJmftWKS == dgLAYjibBz){wLcyNBkjDe = true;}
      else if(dgLAYjibBz == JseJmftWKS){IPjISwHUtD = true;}
      if(mZQQbIYWPz == eUQyixnxfs){ZXAgcKpkAn = true;}
      else if(eUQyixnxfs == mZQQbIYWPz){iMGLkfnkFt = true;}
      if(uwulcewbwR == BocrPZyQNf){uqVeBQQmOc = true;}
      else if(BocrPZyQNf == uwulcewbwR){FVpZALeDAa = true;}
      if(YeJqSeNDgS == UMEYErZdEb){HLOLGJycOS = true;}
      else if(UMEYErZdEb == YeJqSeNDgS){oaJPcuTBQX = true;}
      if(SAORKtFKxS == QdYwZMEXok){FmUroQFLbe = true;}
      else if(QdYwZMEXok == SAORKtFKxS){VnruRGsUgA = true;}
      if(FYYhuMxrgI == LdnfBoDTjy){IdCcLFpxww = true;}
      if(jSZssHPYyw == lROUeSPrtp){kyUZXNIoaT = true;}
      if(tUoxfuhcbh == XJrEbWPfSC){MMWhhHVdpk = true;}
      while(LdnfBoDTjy == FYYhuMxrgI){TgoZVlZKIG = true;}
      while(lROUeSPrtp == lROUeSPrtp){QDUTOIDqio = true;}
      while(XJrEbWPfSC == XJrEbWPfSC){MlTgXRdtIs = true;}
      if(VabcUqXYWO == true){VabcUqXYWO = false;}
      if(nGsFpyPDQH == true){nGsFpyPDQH = false;}
      if(wLcyNBkjDe == true){wLcyNBkjDe = false;}
      if(ZXAgcKpkAn == true){ZXAgcKpkAn = false;}
      if(uqVeBQQmOc == true){uqVeBQQmOc = false;}
      if(HLOLGJycOS == true){HLOLGJycOS = false;}
      if(FmUroQFLbe == true){FmUroQFLbe = false;}
      if(IdCcLFpxww == true){IdCcLFpxww = false;}
      if(kyUZXNIoaT == true){kyUZXNIoaT = false;}
      if(MMWhhHVdpk == true){MMWhhHVdpk = false;}
      if(LEKjUcIlzB == true){LEKjUcIlzB = false;}
      if(TAgSgHSuTa == true){TAgSgHSuTa = false;}
      if(IPjISwHUtD == true){IPjISwHUtD = false;}
      if(iMGLkfnkFt == true){iMGLkfnkFt = false;}
      if(FVpZALeDAa == true){FVpZALeDAa = false;}
      if(oaJPcuTBQX == true){oaJPcuTBQX = false;}
      if(VnruRGsUgA == true){VnruRGsUgA = false;}
      if(TgoZVlZKIG == true){TgoZVlZKIG = false;}
      if(QDUTOIDqio == true){QDUTOIDqio = false;}
      if(MlTgXRdtIs == true){MlTgXRdtIs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BKYEYFSRYQ
{ 
  void SDHARZFYtp()
  { 
      bool jraVhrxBft = false;
      bool UokNLgraGi = false;
      bool eLbTRruNXR = false;
      bool NpXRpcoMhY = false;
      bool tdOWVFZybE = false;
      bool ebnYEXQHEp = false;
      bool widNgeQSXi = false;
      bool qergnBwExL = false;
      bool RwlSlkCyMR = false;
      bool MhIrcLzBoq = false;
      bool nGasMAjGkD = false;
      bool aLJrXAxKbw = false;
      bool bRGFVJVzEc = false;
      bool BuPGWLUrFl = false;
      bool BuNIqAXQUb = false;
      bool OoZsOWAVWD = false;
      bool ejBHCewDUL = false;
      bool eEEpugDxNV = false;
      bool lEdcNMVVqA = false;
      bool KzVCHQtFGL = false;
      string ZQlsmmxzzq;
      string RfCmtrBREm;
      string WbQRdIGmPY;
      string KSTjtObHoR;
      string QHepTWFaiE;
      string rTfLgyzUOe;
      string fJiZfyMSrf;
      string PsbmWOwayH;
      string CfDKgqmHCw;
      string OHrKkGXEKV;
      string KlhDoyrsoS;
      string BXVHbAGXsn;
      string KEQwQHBQBQ;
      string qqQcxPxzVi;
      string ytSjtqlkhk;
      string zzLVKGVlmh;
      string xaqXaKHsKL;
      string CHCJoPkgBZ;
      string VPiQQqeuRp;
      string tKMnlXCuIj;
      if(ZQlsmmxzzq == KlhDoyrsoS){jraVhrxBft = true;}
      else if(KlhDoyrsoS == ZQlsmmxzzq){nGasMAjGkD = true;}
      if(RfCmtrBREm == BXVHbAGXsn){UokNLgraGi = true;}
      else if(BXVHbAGXsn == RfCmtrBREm){aLJrXAxKbw = true;}
      if(WbQRdIGmPY == KEQwQHBQBQ){eLbTRruNXR = true;}
      else if(KEQwQHBQBQ == WbQRdIGmPY){bRGFVJVzEc = true;}
      if(KSTjtObHoR == qqQcxPxzVi){NpXRpcoMhY = true;}
      else if(qqQcxPxzVi == KSTjtObHoR){BuPGWLUrFl = true;}
      if(QHepTWFaiE == ytSjtqlkhk){tdOWVFZybE = true;}
      else if(ytSjtqlkhk == QHepTWFaiE){BuNIqAXQUb = true;}
      if(rTfLgyzUOe == zzLVKGVlmh){ebnYEXQHEp = true;}
      else if(zzLVKGVlmh == rTfLgyzUOe){OoZsOWAVWD = true;}
      if(fJiZfyMSrf == xaqXaKHsKL){widNgeQSXi = true;}
      else if(xaqXaKHsKL == fJiZfyMSrf){ejBHCewDUL = true;}
      if(PsbmWOwayH == CHCJoPkgBZ){qergnBwExL = true;}
      if(CfDKgqmHCw == VPiQQqeuRp){RwlSlkCyMR = true;}
      if(OHrKkGXEKV == tKMnlXCuIj){MhIrcLzBoq = true;}
      while(CHCJoPkgBZ == PsbmWOwayH){eEEpugDxNV = true;}
      while(VPiQQqeuRp == VPiQQqeuRp){lEdcNMVVqA = true;}
      while(tKMnlXCuIj == tKMnlXCuIj){KzVCHQtFGL = true;}
      if(jraVhrxBft == true){jraVhrxBft = false;}
      if(UokNLgraGi == true){UokNLgraGi = false;}
      if(eLbTRruNXR == true){eLbTRruNXR = false;}
      if(NpXRpcoMhY == true){NpXRpcoMhY = false;}
      if(tdOWVFZybE == true){tdOWVFZybE = false;}
      if(ebnYEXQHEp == true){ebnYEXQHEp = false;}
      if(widNgeQSXi == true){widNgeQSXi = false;}
      if(qergnBwExL == true){qergnBwExL = false;}
      if(RwlSlkCyMR == true){RwlSlkCyMR = false;}
      if(MhIrcLzBoq == true){MhIrcLzBoq = false;}
      if(nGasMAjGkD == true){nGasMAjGkD = false;}
      if(aLJrXAxKbw == true){aLJrXAxKbw = false;}
      if(bRGFVJVzEc == true){bRGFVJVzEc = false;}
      if(BuPGWLUrFl == true){BuPGWLUrFl = false;}
      if(BuNIqAXQUb == true){BuNIqAXQUb = false;}
      if(OoZsOWAVWD == true){OoZsOWAVWD = false;}
      if(ejBHCewDUL == true){ejBHCewDUL = false;}
      if(eEEpugDxNV == true){eEEpugDxNV = false;}
      if(lEdcNMVVqA == true){lEdcNMVVqA = false;}
      if(KzVCHQtFGL == true){KzVCHQtFGL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CURCUNFRUY
{ 
  void NoKsBbmpZT()
  { 
      bool wxVsjLTram = false;
      bool ndojZlPpqO = false;
      bool ODcDyVPFcs = false;
      bool KBpnHQCBeh = false;
      bool HwnpoDMgRC = false;
      bool AbYoNsUSuN = false;
      bool uNOgclmBcJ = false;
      bool iOLJHROlOt = false;
      bool JhnZrhcBaN = false;
      bool wjGQlshHMC = false;
      bool QLEHSlQOgu = false;
      bool dhDAENYnnu = false;
      bool JkaONzHtXN = false;
      bool jHYMdxdfHF = false;
      bool ROTejNgFLX = false;
      bool UsSRrekotT = false;
      bool dVpTLWIqWG = false;
      bool isgicuQueA = false;
      bool RCizsqoHTz = false;
      bool MnlmawXATN = false;
      string CttyDHRmhY;
      string rxSHgrnzCm;
      string ISzfYxIUTY;
      string ZpGCVdTrRo;
      string ZRnYTPdrJe;
      string jOpjZjtNYF;
      string ywTIyBpQkC;
      string XwgMNpeaMI;
      string TQLnoKAWcl;
      string iFTLpcxeZR;
      string ZMGGHngcVi;
      string ETBPlhkfTn;
      string BTnzSSbVWk;
      string sABtiGJEgB;
      string cXBsgPEDZI;
      string qRKkQGYHmn;
      string LLFkoESGgf;
      string XfySKcRtRD;
      string NYuOsaoPdc;
      string gCQroQSQDc;
      if(CttyDHRmhY == ZMGGHngcVi){wxVsjLTram = true;}
      else if(ZMGGHngcVi == CttyDHRmhY){QLEHSlQOgu = true;}
      if(rxSHgrnzCm == ETBPlhkfTn){ndojZlPpqO = true;}
      else if(ETBPlhkfTn == rxSHgrnzCm){dhDAENYnnu = true;}
      if(ISzfYxIUTY == BTnzSSbVWk){ODcDyVPFcs = true;}
      else if(BTnzSSbVWk == ISzfYxIUTY){JkaONzHtXN = true;}
      if(ZpGCVdTrRo == sABtiGJEgB){KBpnHQCBeh = true;}
      else if(sABtiGJEgB == ZpGCVdTrRo){jHYMdxdfHF = true;}
      if(ZRnYTPdrJe == cXBsgPEDZI){HwnpoDMgRC = true;}
      else if(cXBsgPEDZI == ZRnYTPdrJe){ROTejNgFLX = true;}
      if(jOpjZjtNYF == qRKkQGYHmn){AbYoNsUSuN = true;}
      else if(qRKkQGYHmn == jOpjZjtNYF){UsSRrekotT = true;}
      if(ywTIyBpQkC == LLFkoESGgf){uNOgclmBcJ = true;}
      else if(LLFkoESGgf == ywTIyBpQkC){dVpTLWIqWG = true;}
      if(XwgMNpeaMI == XfySKcRtRD){iOLJHROlOt = true;}
      if(TQLnoKAWcl == NYuOsaoPdc){JhnZrhcBaN = true;}
      if(iFTLpcxeZR == gCQroQSQDc){wjGQlshHMC = true;}
      while(XfySKcRtRD == XwgMNpeaMI){isgicuQueA = true;}
      while(NYuOsaoPdc == NYuOsaoPdc){RCizsqoHTz = true;}
      while(gCQroQSQDc == gCQroQSQDc){MnlmawXATN = true;}
      if(wxVsjLTram == true){wxVsjLTram = false;}
      if(ndojZlPpqO == true){ndojZlPpqO = false;}
      if(ODcDyVPFcs == true){ODcDyVPFcs = false;}
      if(KBpnHQCBeh == true){KBpnHQCBeh = false;}
      if(HwnpoDMgRC == true){HwnpoDMgRC = false;}
      if(AbYoNsUSuN == true){AbYoNsUSuN = false;}
      if(uNOgclmBcJ == true){uNOgclmBcJ = false;}
      if(iOLJHROlOt == true){iOLJHROlOt = false;}
      if(JhnZrhcBaN == true){JhnZrhcBaN = false;}
      if(wjGQlshHMC == true){wjGQlshHMC = false;}
      if(QLEHSlQOgu == true){QLEHSlQOgu = false;}
      if(dhDAENYnnu == true){dhDAENYnnu = false;}
      if(JkaONzHtXN == true){JkaONzHtXN = false;}
      if(jHYMdxdfHF == true){jHYMdxdfHF = false;}
      if(ROTejNgFLX == true){ROTejNgFLX = false;}
      if(UsSRrekotT == true){UsSRrekotT = false;}
      if(dVpTLWIqWG == true){dVpTLWIqWG = false;}
      if(isgicuQueA == true){isgicuQueA = false;}
      if(RCizsqoHTz == true){RCizsqoHTz = false;}
      if(MnlmawXATN == true){MnlmawXATN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RHZUBDDMUN
{ 
  void fuuUUuiIkY()
  { 
      bool hfDkmdFOzD = false;
      bool MgrZQqnPaS = false;
      bool eiGhRlByJy = false;
      bool djWIJZThUZ = false;
      bool yUDCEksbOl = false;
      bool HRZouyYUSA = false;
      bool cGFBZcKiQq = false;
      bool XGtBTKfDcg = false;
      bool sYiWqLJgNL = false;
      bool AyOTwqOCcb = false;
      bool ZJLXNAWYVk = false;
      bool SVrlHDXhJN = false;
      bool ScVEpZqaEb = false;
      bool udZBGiNKIp = false;
      bool nkLcsdGcMs = false;
      bool TfrOJxnGgn = false;
      bool JwUsonupeX = false;
      bool pMZSZhQsLL = false;
      bool TNNLHPkLqJ = false;
      bool tGdUgqQSmE = false;
      string jGhOUbPcgS;
      string LZuWswOQOT;
      string WPgtQKbsYT;
      string TAIAJdSSry;
      string bTuqqiONtA;
      string kTGJMUZnyJ;
      string AWENyKRuNP;
      string duXQqCTpDg;
      string wNyXhAtzmo;
      string DeUixFPhrf;
      string QSAdVowoRJ;
      string AjkQNlXfey;
      string QSHXLzanSl;
      string mlxWPcNUCr;
      string DEgdoTsDUL;
      string giCtPyKbRW;
      string OHWfWOlNAj;
      string YDdmtLkdir;
      string FWSHEDiDGR;
      string RlCfduhBHZ;
      if(jGhOUbPcgS == QSAdVowoRJ){hfDkmdFOzD = true;}
      else if(QSAdVowoRJ == jGhOUbPcgS){ZJLXNAWYVk = true;}
      if(LZuWswOQOT == AjkQNlXfey){MgrZQqnPaS = true;}
      else if(AjkQNlXfey == LZuWswOQOT){SVrlHDXhJN = true;}
      if(WPgtQKbsYT == QSHXLzanSl){eiGhRlByJy = true;}
      else if(QSHXLzanSl == WPgtQKbsYT){ScVEpZqaEb = true;}
      if(TAIAJdSSry == mlxWPcNUCr){djWIJZThUZ = true;}
      else if(mlxWPcNUCr == TAIAJdSSry){udZBGiNKIp = true;}
      if(bTuqqiONtA == DEgdoTsDUL){yUDCEksbOl = true;}
      else if(DEgdoTsDUL == bTuqqiONtA){nkLcsdGcMs = true;}
      if(kTGJMUZnyJ == giCtPyKbRW){HRZouyYUSA = true;}
      else if(giCtPyKbRW == kTGJMUZnyJ){TfrOJxnGgn = true;}
      if(AWENyKRuNP == OHWfWOlNAj){cGFBZcKiQq = true;}
      else if(OHWfWOlNAj == AWENyKRuNP){JwUsonupeX = true;}
      if(duXQqCTpDg == YDdmtLkdir){XGtBTKfDcg = true;}
      if(wNyXhAtzmo == FWSHEDiDGR){sYiWqLJgNL = true;}
      if(DeUixFPhrf == RlCfduhBHZ){AyOTwqOCcb = true;}
      while(YDdmtLkdir == duXQqCTpDg){pMZSZhQsLL = true;}
      while(FWSHEDiDGR == FWSHEDiDGR){TNNLHPkLqJ = true;}
      while(RlCfduhBHZ == RlCfduhBHZ){tGdUgqQSmE = true;}
      if(hfDkmdFOzD == true){hfDkmdFOzD = false;}
      if(MgrZQqnPaS == true){MgrZQqnPaS = false;}
      if(eiGhRlByJy == true){eiGhRlByJy = false;}
      if(djWIJZThUZ == true){djWIJZThUZ = false;}
      if(yUDCEksbOl == true){yUDCEksbOl = false;}
      if(HRZouyYUSA == true){HRZouyYUSA = false;}
      if(cGFBZcKiQq == true){cGFBZcKiQq = false;}
      if(XGtBTKfDcg == true){XGtBTKfDcg = false;}
      if(sYiWqLJgNL == true){sYiWqLJgNL = false;}
      if(AyOTwqOCcb == true){AyOTwqOCcb = false;}
      if(ZJLXNAWYVk == true){ZJLXNAWYVk = false;}
      if(SVrlHDXhJN == true){SVrlHDXhJN = false;}
      if(ScVEpZqaEb == true){ScVEpZqaEb = false;}
      if(udZBGiNKIp == true){udZBGiNKIp = false;}
      if(nkLcsdGcMs == true){nkLcsdGcMs = false;}
      if(TfrOJxnGgn == true){TfrOJxnGgn = false;}
      if(JwUsonupeX == true){JwUsonupeX = false;}
      if(pMZSZhQsLL == true){pMZSZhQsLL = false;}
      if(TNNLHPkLqJ == true){TNNLHPkLqJ = false;}
      if(tGdUgqQSmE == true){tGdUgqQSmE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BLBQVQRKXR
{ 
  void AmgfwEbuem()
  { 
      bool RpYJFonCxK = false;
      bool mLoAtcQQBW = false;
      bool ZARwzAxfXd = false;
      bool bBNCJcGsib = false;
      bool kfBWGBgxwN = false;
      bool iXLhiRYcKE = false;
      bool rIeThlylqQ = false;
      bool WWhZltytox = false;
      bool TziKuEpeSr = false;
      bool EdidibBhoU = false;
      bool DuGepLpkwo = false;
      bool SdmMksZTXd = false;
      bool uSSzMrnDpJ = false;
      bool rPFTtYrDTj = false;
      bool NEidYZpVsp = false;
      bool ChJKYjbHSy = false;
      bool WlulxDXTSL = false;
      bool AVznPqioZl = false;
      bool BSJAHJFutK = false;
      bool wkkVMaJwgV = false;
      string hLWMlxWJhX;
      string CVokETfYMh;
      string KnkNhqxDHL;
      string LabmZSJgWX;
      string ZmEkPoArHg;
      string ExKbEtZIeu;
      string ASBWMbsCKl;
      string KyCoIWizyr;
      string pFwaGOPzie;
      string rACbXGlhYn;
      string wygVWFtVTg;
      string LaKlEuVaPx;
      string LtTfsJwZQB;
      string kBaKwrXaDA;
      string TtfBTRpPWc;
      string jLRabBdBbM;
      string JUESwJzzpM;
      string WuWOdROSMb;
      string SfDnQZizht;
      string NVyppzoMEJ;
      if(hLWMlxWJhX == wygVWFtVTg){RpYJFonCxK = true;}
      else if(wygVWFtVTg == hLWMlxWJhX){DuGepLpkwo = true;}
      if(CVokETfYMh == LaKlEuVaPx){mLoAtcQQBW = true;}
      else if(LaKlEuVaPx == CVokETfYMh){SdmMksZTXd = true;}
      if(KnkNhqxDHL == LtTfsJwZQB){ZARwzAxfXd = true;}
      else if(LtTfsJwZQB == KnkNhqxDHL){uSSzMrnDpJ = true;}
      if(LabmZSJgWX == kBaKwrXaDA){bBNCJcGsib = true;}
      else if(kBaKwrXaDA == LabmZSJgWX){rPFTtYrDTj = true;}
      if(ZmEkPoArHg == TtfBTRpPWc){kfBWGBgxwN = true;}
      else if(TtfBTRpPWc == ZmEkPoArHg){NEidYZpVsp = true;}
      if(ExKbEtZIeu == jLRabBdBbM){iXLhiRYcKE = true;}
      else if(jLRabBdBbM == ExKbEtZIeu){ChJKYjbHSy = true;}
      if(ASBWMbsCKl == JUESwJzzpM){rIeThlylqQ = true;}
      else if(JUESwJzzpM == ASBWMbsCKl){WlulxDXTSL = true;}
      if(KyCoIWizyr == WuWOdROSMb){WWhZltytox = true;}
      if(pFwaGOPzie == SfDnQZizht){TziKuEpeSr = true;}
      if(rACbXGlhYn == NVyppzoMEJ){EdidibBhoU = true;}
      while(WuWOdROSMb == KyCoIWizyr){AVznPqioZl = true;}
      while(SfDnQZizht == SfDnQZizht){BSJAHJFutK = true;}
      while(NVyppzoMEJ == NVyppzoMEJ){wkkVMaJwgV = true;}
      if(RpYJFonCxK == true){RpYJFonCxK = false;}
      if(mLoAtcQQBW == true){mLoAtcQQBW = false;}
      if(ZARwzAxfXd == true){ZARwzAxfXd = false;}
      if(bBNCJcGsib == true){bBNCJcGsib = false;}
      if(kfBWGBgxwN == true){kfBWGBgxwN = false;}
      if(iXLhiRYcKE == true){iXLhiRYcKE = false;}
      if(rIeThlylqQ == true){rIeThlylqQ = false;}
      if(WWhZltytox == true){WWhZltytox = false;}
      if(TziKuEpeSr == true){TziKuEpeSr = false;}
      if(EdidibBhoU == true){EdidibBhoU = false;}
      if(DuGepLpkwo == true){DuGepLpkwo = false;}
      if(SdmMksZTXd == true){SdmMksZTXd = false;}
      if(uSSzMrnDpJ == true){uSSzMrnDpJ = false;}
      if(rPFTtYrDTj == true){rPFTtYrDTj = false;}
      if(NEidYZpVsp == true){NEidYZpVsp = false;}
      if(ChJKYjbHSy == true){ChJKYjbHSy = false;}
      if(WlulxDXTSL == true){WlulxDXTSL = false;}
      if(AVznPqioZl == true){AVznPqioZl = false;}
      if(BSJAHJFutK == true){BSJAHJFutK = false;}
      if(wkkVMaJwgV == true){wkkVMaJwgV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TTVORDJXGL
{ 
  void VeHsPozsjy()
  { 
      bool XQpYQpxXIX = false;
      bool oKWByeOjTQ = false;
      bool ihQARcBpha = false;
      bool TqOBGkBpJz = false;
      bool lZMMyfELXD = false;
      bool ffUXgpAoGn = false;
      bool oHogDxwVtN = false;
      bool dYaTdJUDCk = false;
      bool XoRetnWpUQ = false;
      bool kLiUKejfIA = false;
      bool jiRKZHFAtW = false;
      bool UwmVPzoKlO = false;
      bool ZFAccRoFJz = false;
      bool YouBAnXHEm = false;
      bool iWwxwoYMFK = false;
      bool oYstZehngI = false;
      bool RAqtyeBkUb = false;
      bool bhGzfDJDgn = false;
      bool rcAyJAuAbV = false;
      bool FiZuUieBzQ = false;
      string FVblcdxbMD;
      string PsHLwBZKLN;
      string RkqViCtHxo;
      string LYOaiJSdUZ;
      string EakRJbodZD;
      string pOrNnTdGDa;
      string jpeXrqdgcl;
      string hwokJqAZLG;
      string NPgszxgBmP;
      string fMatoNwNZS;
      string xIAmVsYGEw;
      string SEtwNTIkXt;
      string KctMGUVuwu;
      string umAsIEPtXG;
      string XZxpwbSdgV;
      string FKoeHUNmfA;
      string WcKJBfDBnI;
      string EOMRVjfDQe;
      string CqOZojxVkm;
      string qbNWiuPnoP;
      if(FVblcdxbMD == xIAmVsYGEw){XQpYQpxXIX = true;}
      else if(xIAmVsYGEw == FVblcdxbMD){jiRKZHFAtW = true;}
      if(PsHLwBZKLN == SEtwNTIkXt){oKWByeOjTQ = true;}
      else if(SEtwNTIkXt == PsHLwBZKLN){UwmVPzoKlO = true;}
      if(RkqViCtHxo == KctMGUVuwu){ihQARcBpha = true;}
      else if(KctMGUVuwu == RkqViCtHxo){ZFAccRoFJz = true;}
      if(LYOaiJSdUZ == umAsIEPtXG){TqOBGkBpJz = true;}
      else if(umAsIEPtXG == LYOaiJSdUZ){YouBAnXHEm = true;}
      if(EakRJbodZD == XZxpwbSdgV){lZMMyfELXD = true;}
      else if(XZxpwbSdgV == EakRJbodZD){iWwxwoYMFK = true;}
      if(pOrNnTdGDa == FKoeHUNmfA){ffUXgpAoGn = true;}
      else if(FKoeHUNmfA == pOrNnTdGDa){oYstZehngI = true;}
      if(jpeXrqdgcl == WcKJBfDBnI){oHogDxwVtN = true;}
      else if(WcKJBfDBnI == jpeXrqdgcl){RAqtyeBkUb = true;}
      if(hwokJqAZLG == EOMRVjfDQe){dYaTdJUDCk = true;}
      if(NPgszxgBmP == CqOZojxVkm){XoRetnWpUQ = true;}
      if(fMatoNwNZS == qbNWiuPnoP){kLiUKejfIA = true;}
      while(EOMRVjfDQe == hwokJqAZLG){bhGzfDJDgn = true;}
      while(CqOZojxVkm == CqOZojxVkm){rcAyJAuAbV = true;}
      while(qbNWiuPnoP == qbNWiuPnoP){FiZuUieBzQ = true;}
      if(XQpYQpxXIX == true){XQpYQpxXIX = false;}
      if(oKWByeOjTQ == true){oKWByeOjTQ = false;}
      if(ihQARcBpha == true){ihQARcBpha = false;}
      if(TqOBGkBpJz == true){TqOBGkBpJz = false;}
      if(lZMMyfELXD == true){lZMMyfELXD = false;}
      if(ffUXgpAoGn == true){ffUXgpAoGn = false;}
      if(oHogDxwVtN == true){oHogDxwVtN = false;}
      if(dYaTdJUDCk == true){dYaTdJUDCk = false;}
      if(XoRetnWpUQ == true){XoRetnWpUQ = false;}
      if(kLiUKejfIA == true){kLiUKejfIA = false;}
      if(jiRKZHFAtW == true){jiRKZHFAtW = false;}
      if(UwmVPzoKlO == true){UwmVPzoKlO = false;}
      if(ZFAccRoFJz == true){ZFAccRoFJz = false;}
      if(YouBAnXHEm == true){YouBAnXHEm = false;}
      if(iWwxwoYMFK == true){iWwxwoYMFK = false;}
      if(oYstZehngI == true){oYstZehngI = false;}
      if(RAqtyeBkUb == true){RAqtyeBkUb = false;}
      if(bhGzfDJDgn == true){bhGzfDJDgn = false;}
      if(rcAyJAuAbV == true){rcAyJAuAbV = false;}
      if(FiZuUieBzQ == true){FiZuUieBzQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DCAIYAUTHG
{ 
  void SenoCRMiuk()
  { 
      bool YBYcIQUzqN = false;
      bool cFgxogZeSJ = false;
      bool KKddxShtPN = false;
      bool gFlpHnJLae = false;
      bool fRyIgtVfxX = false;
      bool uLnoINWtfp = false;
      bool hZjcgWTqpB = false;
      bool WOEncrMVwC = false;
      bool wCxrSUQxhs = false;
      bool QOfkwGhUaJ = false;
      bool aepwAgHALP = false;
      bool BBycsfcqJM = false;
      bool GWIwkHiSqW = false;
      bool KrtlbRLBql = false;
      bool NPkRrOQCrQ = false;
      bool cpKODEWsLs = false;
      bool xnJoFJHLBa = false;
      bool TbAXyqkqEV = false;
      bool qfaZsTgfiX = false;
      bool uSpynYFwMi = false;
      string cNgsANlqFD;
      string sFOjJmJLSl;
      string qTmBhiFXGm;
      string VdQtTPmMgF;
      string OlZbeLFNeT;
      string IIrJUIaeKR;
      string IOkShPnTQt;
      string zxeMXFsKWW;
      string cqsleNkGZK;
      string oIBPxzBHtP;
      string WkwjUKdelP;
      string OPHnoQVymT;
      string dgtFFpuOPY;
      string ElPHzqtIQT;
      string jGUJwYBMaf;
      string cCTakopqdd;
      string POONLcAAnx;
      string WMgTjXMkJf;
      string oinjuBRoVK;
      string ADdlEVqHyS;
      if(cNgsANlqFD == WkwjUKdelP){YBYcIQUzqN = true;}
      else if(WkwjUKdelP == cNgsANlqFD){aepwAgHALP = true;}
      if(sFOjJmJLSl == OPHnoQVymT){cFgxogZeSJ = true;}
      else if(OPHnoQVymT == sFOjJmJLSl){BBycsfcqJM = true;}
      if(qTmBhiFXGm == dgtFFpuOPY){KKddxShtPN = true;}
      else if(dgtFFpuOPY == qTmBhiFXGm){GWIwkHiSqW = true;}
      if(VdQtTPmMgF == ElPHzqtIQT){gFlpHnJLae = true;}
      else if(ElPHzqtIQT == VdQtTPmMgF){KrtlbRLBql = true;}
      if(OlZbeLFNeT == jGUJwYBMaf){fRyIgtVfxX = true;}
      else if(jGUJwYBMaf == OlZbeLFNeT){NPkRrOQCrQ = true;}
      if(IIrJUIaeKR == cCTakopqdd){uLnoINWtfp = true;}
      else if(cCTakopqdd == IIrJUIaeKR){cpKODEWsLs = true;}
      if(IOkShPnTQt == POONLcAAnx){hZjcgWTqpB = true;}
      else if(POONLcAAnx == IOkShPnTQt){xnJoFJHLBa = true;}
      if(zxeMXFsKWW == WMgTjXMkJf){WOEncrMVwC = true;}
      if(cqsleNkGZK == oinjuBRoVK){wCxrSUQxhs = true;}
      if(oIBPxzBHtP == ADdlEVqHyS){QOfkwGhUaJ = true;}
      while(WMgTjXMkJf == zxeMXFsKWW){TbAXyqkqEV = true;}
      while(oinjuBRoVK == oinjuBRoVK){qfaZsTgfiX = true;}
      while(ADdlEVqHyS == ADdlEVqHyS){uSpynYFwMi = true;}
      if(YBYcIQUzqN == true){YBYcIQUzqN = false;}
      if(cFgxogZeSJ == true){cFgxogZeSJ = false;}
      if(KKddxShtPN == true){KKddxShtPN = false;}
      if(gFlpHnJLae == true){gFlpHnJLae = false;}
      if(fRyIgtVfxX == true){fRyIgtVfxX = false;}
      if(uLnoINWtfp == true){uLnoINWtfp = false;}
      if(hZjcgWTqpB == true){hZjcgWTqpB = false;}
      if(WOEncrMVwC == true){WOEncrMVwC = false;}
      if(wCxrSUQxhs == true){wCxrSUQxhs = false;}
      if(QOfkwGhUaJ == true){QOfkwGhUaJ = false;}
      if(aepwAgHALP == true){aepwAgHALP = false;}
      if(BBycsfcqJM == true){BBycsfcqJM = false;}
      if(GWIwkHiSqW == true){GWIwkHiSqW = false;}
      if(KrtlbRLBql == true){KrtlbRLBql = false;}
      if(NPkRrOQCrQ == true){NPkRrOQCrQ = false;}
      if(cpKODEWsLs == true){cpKODEWsLs = false;}
      if(xnJoFJHLBa == true){xnJoFJHLBa = false;}
      if(TbAXyqkqEV == true){TbAXyqkqEV = false;}
      if(qfaZsTgfiX == true){qfaZsTgfiX = false;}
      if(uSpynYFwMi == true){uSpynYFwMi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UHIEMQTHSZ
{ 
  void fTDDBJltfk()
  { 
      bool LZyTOZbqcp = false;
      bool UdOFOlDmcU = false;
      bool AMLLtbtehP = false;
      bool QmTGlzWUsG = false;
      bool WVQTPeCzNe = false;
      bool jNOgoyOmZm = false;
      bool exINZgJITP = false;
      bool OisWyduquO = false;
      bool YuRCeDYmRm = false;
      bool kjuGbZMDth = false;
      bool VtexQBTriL = false;
      bool CWqKNifGiV = false;
      bool HWpfddnmtX = false;
      bool QrxNrdQTlc = false;
      bool igDGjOsjrr = false;
      bool tGUXazEzTl = false;
      bool NgxKtKZdRi = false;
      bool SLTFmaSjuP = false;
      bool jDtCdJXYms = false;
      bool ZQAzPBjrLZ = false;
      string rFXzdWwCjF;
      string pYjYxiRujC;
      string yGdoBOONAN;
      string jRXRGdWZzn;
      string OIlkwiLblX;
      string PAIErlbiyP;
      string IhBWUYBSSS;
      string LqwwmoTrrR;
      string ClacxjJTYU;
      string CnajefHPQX;
      string hsJTLXEMQC;
      string RiqfMWGXYj;
      string OgsyQWQLQG;
      string hEbTjJcHQY;
      string fwCWCSxtWI;
      string ZipgIAAKCo;
      string HruKTNHWwD;
      string szGzDSeWux;
      string ZVnIgzNtKj;
      string IREbRnBqCo;
      if(rFXzdWwCjF == hsJTLXEMQC){LZyTOZbqcp = true;}
      else if(hsJTLXEMQC == rFXzdWwCjF){VtexQBTriL = true;}
      if(pYjYxiRujC == RiqfMWGXYj){UdOFOlDmcU = true;}
      else if(RiqfMWGXYj == pYjYxiRujC){CWqKNifGiV = true;}
      if(yGdoBOONAN == OgsyQWQLQG){AMLLtbtehP = true;}
      else if(OgsyQWQLQG == yGdoBOONAN){HWpfddnmtX = true;}
      if(jRXRGdWZzn == hEbTjJcHQY){QmTGlzWUsG = true;}
      else if(hEbTjJcHQY == jRXRGdWZzn){QrxNrdQTlc = true;}
      if(OIlkwiLblX == fwCWCSxtWI){WVQTPeCzNe = true;}
      else if(fwCWCSxtWI == OIlkwiLblX){igDGjOsjrr = true;}
      if(PAIErlbiyP == ZipgIAAKCo){jNOgoyOmZm = true;}
      else if(ZipgIAAKCo == PAIErlbiyP){tGUXazEzTl = true;}
      if(IhBWUYBSSS == HruKTNHWwD){exINZgJITP = true;}
      else if(HruKTNHWwD == IhBWUYBSSS){NgxKtKZdRi = true;}
      if(LqwwmoTrrR == szGzDSeWux){OisWyduquO = true;}
      if(ClacxjJTYU == ZVnIgzNtKj){YuRCeDYmRm = true;}
      if(CnajefHPQX == IREbRnBqCo){kjuGbZMDth = true;}
      while(szGzDSeWux == LqwwmoTrrR){SLTFmaSjuP = true;}
      while(ZVnIgzNtKj == ZVnIgzNtKj){jDtCdJXYms = true;}
      while(IREbRnBqCo == IREbRnBqCo){ZQAzPBjrLZ = true;}
      if(LZyTOZbqcp == true){LZyTOZbqcp = false;}
      if(UdOFOlDmcU == true){UdOFOlDmcU = false;}
      if(AMLLtbtehP == true){AMLLtbtehP = false;}
      if(QmTGlzWUsG == true){QmTGlzWUsG = false;}
      if(WVQTPeCzNe == true){WVQTPeCzNe = false;}
      if(jNOgoyOmZm == true){jNOgoyOmZm = false;}
      if(exINZgJITP == true){exINZgJITP = false;}
      if(OisWyduquO == true){OisWyduquO = false;}
      if(YuRCeDYmRm == true){YuRCeDYmRm = false;}
      if(kjuGbZMDth == true){kjuGbZMDth = false;}
      if(VtexQBTriL == true){VtexQBTriL = false;}
      if(CWqKNifGiV == true){CWqKNifGiV = false;}
      if(HWpfddnmtX == true){HWpfddnmtX = false;}
      if(QrxNrdQTlc == true){QrxNrdQTlc = false;}
      if(igDGjOsjrr == true){igDGjOsjrr = false;}
      if(tGUXazEzTl == true){tGUXazEzTl = false;}
      if(NgxKtKZdRi == true){NgxKtKZdRi = false;}
      if(SLTFmaSjuP == true){SLTFmaSjuP = false;}
      if(jDtCdJXYms == true){jDtCdJXYms = false;}
      if(ZQAzPBjrLZ == true){ZQAzPBjrLZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HUHLCKFRAJ
{ 
  void DPEWxcMTsn()
  { 
      bool GbDZHxIore = false;
      bool aERTUSahqW = false;
      bool MRUUWPAVpC = false;
      bool WrYSZNKOsX = false;
      bool sLSMdjxRVh = false;
      bool wyOwxnGiDq = false;
      bool xlzpHifztH = false;
      bool IMnSdAzIqm = false;
      bool RhAHGYdbVl = false;
      bool HbLBZGMcEu = false;
      bool DyXNZiJuSw = false;
      bool oxqPYPkqii = false;
      bool EEdIAfBlsW = false;
      bool nVDwjTJlhX = false;
      bool OiJYwJjubK = false;
      bool UUtVpzUPNs = false;
      bool hWCuHSsufF = false;
      bool FzJLTVuELp = false;
      bool wFKhCTbhFk = false;
      bool ztXnoqfNRd = false;
      string NDygnIKutV;
      string TSLbWDlJaE;
      string xbjgIXSfoL;
      string dQSoGMuIzO;
      string npmXEoEPbx;
      string DAghBkTRYQ;
      string pdGhqCAWVJ;
      string IcJLPGnLcT;
      string SCEqIdjjmU;
      string sdjiYJjFgB;
      string ngtRoZpUSu;
      string wInFxmZOYN;
      string SPjAQesZlF;
      string WheaelImBh;
      string mORrXjoekl;
      string jUgSiYxsAK;
      string gPhMXOdNaL;
      string dlMqZDxrbf;
      string oOnAVBBLrF;
      string nOlqAWfFTJ;
      if(NDygnIKutV == ngtRoZpUSu){GbDZHxIore = true;}
      else if(ngtRoZpUSu == NDygnIKutV){DyXNZiJuSw = true;}
      if(TSLbWDlJaE == wInFxmZOYN){aERTUSahqW = true;}
      else if(wInFxmZOYN == TSLbWDlJaE){oxqPYPkqii = true;}
      if(xbjgIXSfoL == SPjAQesZlF){MRUUWPAVpC = true;}
      else if(SPjAQesZlF == xbjgIXSfoL){EEdIAfBlsW = true;}
      if(dQSoGMuIzO == WheaelImBh){WrYSZNKOsX = true;}
      else if(WheaelImBh == dQSoGMuIzO){nVDwjTJlhX = true;}
      if(npmXEoEPbx == mORrXjoekl){sLSMdjxRVh = true;}
      else if(mORrXjoekl == npmXEoEPbx){OiJYwJjubK = true;}
      if(DAghBkTRYQ == jUgSiYxsAK){wyOwxnGiDq = true;}
      else if(jUgSiYxsAK == DAghBkTRYQ){UUtVpzUPNs = true;}
      if(pdGhqCAWVJ == gPhMXOdNaL){xlzpHifztH = true;}
      else if(gPhMXOdNaL == pdGhqCAWVJ){hWCuHSsufF = true;}
      if(IcJLPGnLcT == dlMqZDxrbf){IMnSdAzIqm = true;}
      if(SCEqIdjjmU == oOnAVBBLrF){RhAHGYdbVl = true;}
      if(sdjiYJjFgB == nOlqAWfFTJ){HbLBZGMcEu = true;}
      while(dlMqZDxrbf == IcJLPGnLcT){FzJLTVuELp = true;}
      while(oOnAVBBLrF == oOnAVBBLrF){wFKhCTbhFk = true;}
      while(nOlqAWfFTJ == nOlqAWfFTJ){ztXnoqfNRd = true;}
      if(GbDZHxIore == true){GbDZHxIore = false;}
      if(aERTUSahqW == true){aERTUSahqW = false;}
      if(MRUUWPAVpC == true){MRUUWPAVpC = false;}
      if(WrYSZNKOsX == true){WrYSZNKOsX = false;}
      if(sLSMdjxRVh == true){sLSMdjxRVh = false;}
      if(wyOwxnGiDq == true){wyOwxnGiDq = false;}
      if(xlzpHifztH == true){xlzpHifztH = false;}
      if(IMnSdAzIqm == true){IMnSdAzIqm = false;}
      if(RhAHGYdbVl == true){RhAHGYdbVl = false;}
      if(HbLBZGMcEu == true){HbLBZGMcEu = false;}
      if(DyXNZiJuSw == true){DyXNZiJuSw = false;}
      if(oxqPYPkqii == true){oxqPYPkqii = false;}
      if(EEdIAfBlsW == true){EEdIAfBlsW = false;}
      if(nVDwjTJlhX == true){nVDwjTJlhX = false;}
      if(OiJYwJjubK == true){OiJYwJjubK = false;}
      if(UUtVpzUPNs == true){UUtVpzUPNs = false;}
      if(hWCuHSsufF == true){hWCuHSsufF = false;}
      if(FzJLTVuELp == true){FzJLTVuELp = false;}
      if(wFKhCTbhFk == true){wFKhCTbhFk = false;}
      if(ztXnoqfNRd == true){ztXnoqfNRd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CLIQCKZXRL
{ 
  void APNWIOnqHw()
  { 
      bool wcCaImoRXi = false;
      bool KYzaGyaZqF = false;
      bool zzCaCfCXPb = false;
      bool GKTGOsnmhH = false;
      bool ALmYRdodCQ = false;
      bool feoTmwaaXb = false;
      bool jRBwbzFsLM = false;
      bool KmqiFnMcJY = false;
      bool qXUzwaUASR = false;
      bool SMPGWiJqwR = false;
      bool YuSoGsmFNy = false;
      bool jxQzjMwCAA = false;
      bool dEZstxWkMW = false;
      bool eVfrAuFesD = false;
      bool nPlUhVwQVK = false;
      bool lHqwmTVYuI = false;
      bool VCsqTOQYyo = false;
      bool GQIwMOSFLX = false;
      bool AGOCjXejFf = false;
      bool ZgjjgkVtAT = false;
      string JfkUwAnQec;
      string kxTwTCppZL;
      string jEzszSMyXI;
      string SwwgVRqGlW;
      string fiAuPLRbFx;
      string TnoEGFgqUc;
      string npsWJnAmZB;
      string KiDDeADDdn;
      string BjsZneHqZQ;
      string jAlIhpodka;
      string KeBDmkjlZG;
      string BcMgbEwThd;
      string gJMIRJwuUn;
      string LYSCcVhplD;
      string uVRTPGmFgd;
      string sVwHtBSskc;
      string ooQktcKKDG;
      string VGgdiLqssK;
      string WpNqtocLIb;
      string DoEJOGEfYm;
      if(JfkUwAnQec == KeBDmkjlZG){wcCaImoRXi = true;}
      else if(KeBDmkjlZG == JfkUwAnQec){YuSoGsmFNy = true;}
      if(kxTwTCppZL == BcMgbEwThd){KYzaGyaZqF = true;}
      else if(BcMgbEwThd == kxTwTCppZL){jxQzjMwCAA = true;}
      if(jEzszSMyXI == gJMIRJwuUn){zzCaCfCXPb = true;}
      else if(gJMIRJwuUn == jEzszSMyXI){dEZstxWkMW = true;}
      if(SwwgVRqGlW == LYSCcVhplD){GKTGOsnmhH = true;}
      else if(LYSCcVhplD == SwwgVRqGlW){eVfrAuFesD = true;}
      if(fiAuPLRbFx == uVRTPGmFgd){ALmYRdodCQ = true;}
      else if(uVRTPGmFgd == fiAuPLRbFx){nPlUhVwQVK = true;}
      if(TnoEGFgqUc == sVwHtBSskc){feoTmwaaXb = true;}
      else if(sVwHtBSskc == TnoEGFgqUc){lHqwmTVYuI = true;}
      if(npsWJnAmZB == ooQktcKKDG){jRBwbzFsLM = true;}
      else if(ooQktcKKDG == npsWJnAmZB){VCsqTOQYyo = true;}
      if(KiDDeADDdn == VGgdiLqssK){KmqiFnMcJY = true;}
      if(BjsZneHqZQ == WpNqtocLIb){qXUzwaUASR = true;}
      if(jAlIhpodka == DoEJOGEfYm){SMPGWiJqwR = true;}
      while(VGgdiLqssK == KiDDeADDdn){GQIwMOSFLX = true;}
      while(WpNqtocLIb == WpNqtocLIb){AGOCjXejFf = true;}
      while(DoEJOGEfYm == DoEJOGEfYm){ZgjjgkVtAT = true;}
      if(wcCaImoRXi == true){wcCaImoRXi = false;}
      if(KYzaGyaZqF == true){KYzaGyaZqF = false;}
      if(zzCaCfCXPb == true){zzCaCfCXPb = false;}
      if(GKTGOsnmhH == true){GKTGOsnmhH = false;}
      if(ALmYRdodCQ == true){ALmYRdodCQ = false;}
      if(feoTmwaaXb == true){feoTmwaaXb = false;}
      if(jRBwbzFsLM == true){jRBwbzFsLM = false;}
      if(KmqiFnMcJY == true){KmqiFnMcJY = false;}
      if(qXUzwaUASR == true){qXUzwaUASR = false;}
      if(SMPGWiJqwR == true){SMPGWiJqwR = false;}
      if(YuSoGsmFNy == true){YuSoGsmFNy = false;}
      if(jxQzjMwCAA == true){jxQzjMwCAA = false;}
      if(dEZstxWkMW == true){dEZstxWkMW = false;}
      if(eVfrAuFesD == true){eVfrAuFesD = false;}
      if(nPlUhVwQVK == true){nPlUhVwQVK = false;}
      if(lHqwmTVYuI == true){lHqwmTVYuI = false;}
      if(VCsqTOQYyo == true){VCsqTOQYyo = false;}
      if(GQIwMOSFLX == true){GQIwMOSFLX = false;}
      if(AGOCjXejFf == true){AGOCjXejFf = false;}
      if(ZgjjgkVtAT == true){ZgjjgkVtAT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WNAMZVPNJU
{ 
  void QSBndfjZDp()
  { 
      bool HcVCXOgThF = false;
      bool kzAlGAoklC = false;
      bool SCCzHeoYxl = false;
      bool mVkrJTOqUF = false;
      bool wjgSWkDHKF = false;
      bool HTUxfFaVtr = false;
      bool ZHVuSPOHcl = false;
      bool lxQfGiUibW = false;
      bool bhNreTAmLE = false;
      bool srwbfnNkAH = false;
      bool WueYSJCnqx = false;
      bool jqsWQrsdPy = false;
      bool OauYstBnAR = false;
      bool UjiUzfCoYV = false;
      bool QMwOTByYKm = false;
      bool uiUBrwzFeY = false;
      bool HNmZbAHYXk = false;
      bool oDEthCegEq = false;
      bool ubdNWkOgbD = false;
      bool fxJANDYVmT = false;
      string bDERszZXsf;
      string LtGfkFktqG;
      string DoyJLFaylK;
      string TXObDZzOwI;
      string GTzpNjgdFL;
      string UTLZPmFuGm;
      string YakiMnfdbK;
      string GWxhzipIwa;
      string YwsZoAMnMQ;
      string UDIJifhPcY;
      string ECBtFyVcZf;
      string wwyeOchKsM;
      string aqRLpCNnzS;
      string AZeWWVtyUp;
      string diOfUYFdtG;
      string yWWQyNkpED;
      string jhdHfVQbIr;
      string hipDhrckpR;
      string xjsrUcDOYI;
      string jDtQFwEHAy;
      if(bDERszZXsf == ECBtFyVcZf){HcVCXOgThF = true;}
      else if(ECBtFyVcZf == bDERszZXsf){WueYSJCnqx = true;}
      if(LtGfkFktqG == wwyeOchKsM){kzAlGAoklC = true;}
      else if(wwyeOchKsM == LtGfkFktqG){jqsWQrsdPy = true;}
      if(DoyJLFaylK == aqRLpCNnzS){SCCzHeoYxl = true;}
      else if(aqRLpCNnzS == DoyJLFaylK){OauYstBnAR = true;}
      if(TXObDZzOwI == AZeWWVtyUp){mVkrJTOqUF = true;}
      else if(AZeWWVtyUp == TXObDZzOwI){UjiUzfCoYV = true;}
      if(GTzpNjgdFL == diOfUYFdtG){wjgSWkDHKF = true;}
      else if(diOfUYFdtG == GTzpNjgdFL){QMwOTByYKm = true;}
      if(UTLZPmFuGm == yWWQyNkpED){HTUxfFaVtr = true;}
      else if(yWWQyNkpED == UTLZPmFuGm){uiUBrwzFeY = true;}
      if(YakiMnfdbK == jhdHfVQbIr){ZHVuSPOHcl = true;}
      else if(jhdHfVQbIr == YakiMnfdbK){HNmZbAHYXk = true;}
      if(GWxhzipIwa == hipDhrckpR){lxQfGiUibW = true;}
      if(YwsZoAMnMQ == xjsrUcDOYI){bhNreTAmLE = true;}
      if(UDIJifhPcY == jDtQFwEHAy){srwbfnNkAH = true;}
      while(hipDhrckpR == GWxhzipIwa){oDEthCegEq = true;}
      while(xjsrUcDOYI == xjsrUcDOYI){ubdNWkOgbD = true;}
      while(jDtQFwEHAy == jDtQFwEHAy){fxJANDYVmT = true;}
      if(HcVCXOgThF == true){HcVCXOgThF = false;}
      if(kzAlGAoklC == true){kzAlGAoklC = false;}
      if(SCCzHeoYxl == true){SCCzHeoYxl = false;}
      if(mVkrJTOqUF == true){mVkrJTOqUF = false;}
      if(wjgSWkDHKF == true){wjgSWkDHKF = false;}
      if(HTUxfFaVtr == true){HTUxfFaVtr = false;}
      if(ZHVuSPOHcl == true){ZHVuSPOHcl = false;}
      if(lxQfGiUibW == true){lxQfGiUibW = false;}
      if(bhNreTAmLE == true){bhNreTAmLE = false;}
      if(srwbfnNkAH == true){srwbfnNkAH = false;}
      if(WueYSJCnqx == true){WueYSJCnqx = false;}
      if(jqsWQrsdPy == true){jqsWQrsdPy = false;}
      if(OauYstBnAR == true){OauYstBnAR = false;}
      if(UjiUzfCoYV == true){UjiUzfCoYV = false;}
      if(QMwOTByYKm == true){QMwOTByYKm = false;}
      if(uiUBrwzFeY == true){uiUBrwzFeY = false;}
      if(HNmZbAHYXk == true){HNmZbAHYXk = false;}
      if(oDEthCegEq == true){oDEthCegEq = false;}
      if(ubdNWkOgbD == true){ubdNWkOgbD = false;}
      if(fxJANDYVmT == true){fxJANDYVmT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BTSISLVVZK
{ 
  void LLzFWTQggn()
  { 
      bool mpTszqEnql = false;
      bool ieolXeqRBK = false;
      bool GVgdbEnqmI = false;
      bool JScBklDiAG = false;
      bool txQuYhLHzx = false;
      bool OCaDmRIoRu = false;
      bool CMBhbQCmAk = false;
      bool aIQtQIElEt = false;
      bool rfrosGqYOT = false;
      bool dNRFDguiTI = false;
      bool fYHNVGlgmd = false;
      bool MWkWDVULoU = false;
      bool YcXgHNqLpi = false;
      bool MVRuOSYdSm = false;
      bool UKljGGbtBh = false;
      bool MjsyiCAZFI = false;
      bool PapDRqEpIj = false;
      bool wprCAOqnaA = false;
      bool kwJIVcbSLL = false;
      bool SzXKWtUhSP = false;
      string CIhMNNBYrn;
      string MXSlTHrGop;
      string TiDpDXTIiq;
      string tjEBlRJltn;
      string FwxqKSDRCe;
      string jpYGASFrIp;
      string srpAtcSQzC;
      string yFMAkXlLek;
      string TCFDHDKxBS;
      string LRcDuMFwwh;
      string zlRAgdcXVb;
      string gsMXVpmlsp;
      string RVPgpgbJFX;
      string SoOxlhkEWd;
      string amaYkREFgE;
      string ZTDGPcVjKz;
      string BTSyJrdOln;
      string EiOOPdtquY;
      string bWbAxykIgI;
      string MAtWbGUbOs;
      if(CIhMNNBYrn == zlRAgdcXVb){mpTszqEnql = true;}
      else if(zlRAgdcXVb == CIhMNNBYrn){fYHNVGlgmd = true;}
      if(MXSlTHrGop == gsMXVpmlsp){ieolXeqRBK = true;}
      else if(gsMXVpmlsp == MXSlTHrGop){MWkWDVULoU = true;}
      if(TiDpDXTIiq == RVPgpgbJFX){GVgdbEnqmI = true;}
      else if(RVPgpgbJFX == TiDpDXTIiq){YcXgHNqLpi = true;}
      if(tjEBlRJltn == SoOxlhkEWd){JScBklDiAG = true;}
      else if(SoOxlhkEWd == tjEBlRJltn){MVRuOSYdSm = true;}
      if(FwxqKSDRCe == amaYkREFgE){txQuYhLHzx = true;}
      else if(amaYkREFgE == FwxqKSDRCe){UKljGGbtBh = true;}
      if(jpYGASFrIp == ZTDGPcVjKz){OCaDmRIoRu = true;}
      else if(ZTDGPcVjKz == jpYGASFrIp){MjsyiCAZFI = true;}
      if(srpAtcSQzC == BTSyJrdOln){CMBhbQCmAk = true;}
      else if(BTSyJrdOln == srpAtcSQzC){PapDRqEpIj = true;}
      if(yFMAkXlLek == EiOOPdtquY){aIQtQIElEt = true;}
      if(TCFDHDKxBS == bWbAxykIgI){rfrosGqYOT = true;}
      if(LRcDuMFwwh == MAtWbGUbOs){dNRFDguiTI = true;}
      while(EiOOPdtquY == yFMAkXlLek){wprCAOqnaA = true;}
      while(bWbAxykIgI == bWbAxykIgI){kwJIVcbSLL = true;}
      while(MAtWbGUbOs == MAtWbGUbOs){SzXKWtUhSP = true;}
      if(mpTszqEnql == true){mpTszqEnql = false;}
      if(ieolXeqRBK == true){ieolXeqRBK = false;}
      if(GVgdbEnqmI == true){GVgdbEnqmI = false;}
      if(JScBklDiAG == true){JScBklDiAG = false;}
      if(txQuYhLHzx == true){txQuYhLHzx = false;}
      if(OCaDmRIoRu == true){OCaDmRIoRu = false;}
      if(CMBhbQCmAk == true){CMBhbQCmAk = false;}
      if(aIQtQIElEt == true){aIQtQIElEt = false;}
      if(rfrosGqYOT == true){rfrosGqYOT = false;}
      if(dNRFDguiTI == true){dNRFDguiTI = false;}
      if(fYHNVGlgmd == true){fYHNVGlgmd = false;}
      if(MWkWDVULoU == true){MWkWDVULoU = false;}
      if(YcXgHNqLpi == true){YcXgHNqLpi = false;}
      if(MVRuOSYdSm == true){MVRuOSYdSm = false;}
      if(UKljGGbtBh == true){UKljGGbtBh = false;}
      if(MjsyiCAZFI == true){MjsyiCAZFI = false;}
      if(PapDRqEpIj == true){PapDRqEpIj = false;}
      if(wprCAOqnaA == true){wprCAOqnaA = false;}
      if(kwJIVcbSLL == true){kwJIVcbSLL = false;}
      if(SzXKWtUhSP == true){SzXKWtUhSP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WMREAXCCQF
{ 
  void lGfkULqisH()
  { 
      bool PpyPKHsWkO = false;
      bool CIfAFtdOJq = false;
      bool wAtagyRWRc = false;
      bool KfgAiNpztf = false;
      bool fCIeMjSstj = false;
      bool kjPsRPwWiM = false;
      bool pWEIDVaeQr = false;
      bool EdTcLsrPNx = false;
      bool eXbgqaQmiT = false;
      bool RSQgoJyAbq = false;
      bool IncBfGQlhX = false;
      bool XfIkhRtWQb = false;
      bool FmwwakNlmB = false;
      bool uqnWoptaBk = false;
      bool KdFKwkKezX = false;
      bool OajzlUrfau = false;
      bool sdyfbfrlwq = false;
      bool WTVfRahkAp = false;
      bool ZhmPmUHnjU = false;
      bool yOAGqfeZhP = false;
      string dZWJaEOCLH;
      string ZFYfreGQpO;
      string TqAxoaaERX;
      string uwFzjDKYfc;
      string ihTteiRnzN;
      string ukuhrlYYUA;
      string dKknMdzZuo;
      string UhkMelXFSG;
      string JlEDbJAXHx;
      string dkDfzYxegB;
      string irsKsNzhCF;
      string NTGOpqFgLC;
      string caSyKidFNG;
      string orYRWRstKO;
      string JSVBiKeooI;
      string SPTdXHZtAK;
      string itTwQUtnqY;
      string xLWxsJFROz;
      string EoPFmYYtsP;
      string rztAePyYjN;
      if(dZWJaEOCLH == irsKsNzhCF){PpyPKHsWkO = true;}
      else if(irsKsNzhCF == dZWJaEOCLH){IncBfGQlhX = true;}
      if(ZFYfreGQpO == NTGOpqFgLC){CIfAFtdOJq = true;}
      else if(NTGOpqFgLC == ZFYfreGQpO){XfIkhRtWQb = true;}
      if(TqAxoaaERX == caSyKidFNG){wAtagyRWRc = true;}
      else if(caSyKidFNG == TqAxoaaERX){FmwwakNlmB = true;}
      if(uwFzjDKYfc == orYRWRstKO){KfgAiNpztf = true;}
      else if(orYRWRstKO == uwFzjDKYfc){uqnWoptaBk = true;}
      if(ihTteiRnzN == JSVBiKeooI){fCIeMjSstj = true;}
      else if(JSVBiKeooI == ihTteiRnzN){KdFKwkKezX = true;}
      if(ukuhrlYYUA == SPTdXHZtAK){kjPsRPwWiM = true;}
      else if(SPTdXHZtAK == ukuhrlYYUA){OajzlUrfau = true;}
      if(dKknMdzZuo == itTwQUtnqY){pWEIDVaeQr = true;}
      else if(itTwQUtnqY == dKknMdzZuo){sdyfbfrlwq = true;}
      if(UhkMelXFSG == xLWxsJFROz){EdTcLsrPNx = true;}
      if(JlEDbJAXHx == EoPFmYYtsP){eXbgqaQmiT = true;}
      if(dkDfzYxegB == rztAePyYjN){RSQgoJyAbq = true;}
      while(xLWxsJFROz == UhkMelXFSG){WTVfRahkAp = true;}
      while(EoPFmYYtsP == EoPFmYYtsP){ZhmPmUHnjU = true;}
      while(rztAePyYjN == rztAePyYjN){yOAGqfeZhP = true;}
      if(PpyPKHsWkO == true){PpyPKHsWkO = false;}
      if(CIfAFtdOJq == true){CIfAFtdOJq = false;}
      if(wAtagyRWRc == true){wAtagyRWRc = false;}
      if(KfgAiNpztf == true){KfgAiNpztf = false;}
      if(fCIeMjSstj == true){fCIeMjSstj = false;}
      if(kjPsRPwWiM == true){kjPsRPwWiM = false;}
      if(pWEIDVaeQr == true){pWEIDVaeQr = false;}
      if(EdTcLsrPNx == true){EdTcLsrPNx = false;}
      if(eXbgqaQmiT == true){eXbgqaQmiT = false;}
      if(RSQgoJyAbq == true){RSQgoJyAbq = false;}
      if(IncBfGQlhX == true){IncBfGQlhX = false;}
      if(XfIkhRtWQb == true){XfIkhRtWQb = false;}
      if(FmwwakNlmB == true){FmwwakNlmB = false;}
      if(uqnWoptaBk == true){uqnWoptaBk = false;}
      if(KdFKwkKezX == true){KdFKwkKezX = false;}
      if(OajzlUrfau == true){OajzlUrfau = false;}
      if(sdyfbfrlwq == true){sdyfbfrlwq = false;}
      if(WTVfRahkAp == true){WTVfRahkAp = false;}
      if(ZhmPmUHnjU == true){ZhmPmUHnjU = false;}
      if(yOAGqfeZhP == true){yOAGqfeZhP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KXYNMOSJIP
{ 
  void SxiHkopPTF()
  { 
      bool FrjdRTFiND = false;
      bool EAgucjAHhF = false;
      bool tUZcKngFyy = false;
      bool IUKrUspaCd = false;
      bool PGkJMylDjB = false;
      bool xJKTwjSGTc = false;
      bool lzjPujpoZi = false;
      bool sYEEonjPQL = false;
      bool BcVxAzJpwj = false;
      bool ajHYqQVUOb = false;
      bool HwdAHYEGeH = false;
      bool ADoHbIdmPw = false;
      bool ZAsoIIRfMY = false;
      bool SOAnDFzUob = false;
      bool tCKnjWtzxh = false;
      bool lhFSCHCnry = false;
      bool GXtGolCADV = false;
      bool JIxmBWoFFk = false;
      bool NRhdljIhlw = false;
      bool CKbpUVIEyx = false;
      string unNSlPSRfo;
      string SdGyMrBPby;
      string etmDtjNXPp;
      string ipjAUFSjkS;
      string xTmRVBcDdG;
      string fddfeAAKYC;
      string BuCoFcsGdG;
      string ZQdJAKHVhs;
      string HJsIKELEUT;
      string FHLiQCRyLr;
      string HWZXgPAUeU;
      string sebftqBseA;
      string QnkJBRFtsy;
      string sIJokkjUau;
      string EqZAaafenY;
      string AXSKbTkQVO;
      string JGafajUmuJ;
      string HfRjwYOjia;
      string lZFTyVozNR;
      string zTzMkyQsZp;
      if(unNSlPSRfo == HWZXgPAUeU){FrjdRTFiND = true;}
      else if(HWZXgPAUeU == unNSlPSRfo){HwdAHYEGeH = true;}
      if(SdGyMrBPby == sebftqBseA){EAgucjAHhF = true;}
      else if(sebftqBseA == SdGyMrBPby){ADoHbIdmPw = true;}
      if(etmDtjNXPp == QnkJBRFtsy){tUZcKngFyy = true;}
      else if(QnkJBRFtsy == etmDtjNXPp){ZAsoIIRfMY = true;}
      if(ipjAUFSjkS == sIJokkjUau){IUKrUspaCd = true;}
      else if(sIJokkjUau == ipjAUFSjkS){SOAnDFzUob = true;}
      if(xTmRVBcDdG == EqZAaafenY){PGkJMylDjB = true;}
      else if(EqZAaafenY == xTmRVBcDdG){tCKnjWtzxh = true;}
      if(fddfeAAKYC == AXSKbTkQVO){xJKTwjSGTc = true;}
      else if(AXSKbTkQVO == fddfeAAKYC){lhFSCHCnry = true;}
      if(BuCoFcsGdG == JGafajUmuJ){lzjPujpoZi = true;}
      else if(JGafajUmuJ == BuCoFcsGdG){GXtGolCADV = true;}
      if(ZQdJAKHVhs == HfRjwYOjia){sYEEonjPQL = true;}
      if(HJsIKELEUT == lZFTyVozNR){BcVxAzJpwj = true;}
      if(FHLiQCRyLr == zTzMkyQsZp){ajHYqQVUOb = true;}
      while(HfRjwYOjia == ZQdJAKHVhs){JIxmBWoFFk = true;}
      while(lZFTyVozNR == lZFTyVozNR){NRhdljIhlw = true;}
      while(zTzMkyQsZp == zTzMkyQsZp){CKbpUVIEyx = true;}
      if(FrjdRTFiND == true){FrjdRTFiND = false;}
      if(EAgucjAHhF == true){EAgucjAHhF = false;}
      if(tUZcKngFyy == true){tUZcKngFyy = false;}
      if(IUKrUspaCd == true){IUKrUspaCd = false;}
      if(PGkJMylDjB == true){PGkJMylDjB = false;}
      if(xJKTwjSGTc == true){xJKTwjSGTc = false;}
      if(lzjPujpoZi == true){lzjPujpoZi = false;}
      if(sYEEonjPQL == true){sYEEonjPQL = false;}
      if(BcVxAzJpwj == true){BcVxAzJpwj = false;}
      if(ajHYqQVUOb == true){ajHYqQVUOb = false;}
      if(HwdAHYEGeH == true){HwdAHYEGeH = false;}
      if(ADoHbIdmPw == true){ADoHbIdmPw = false;}
      if(ZAsoIIRfMY == true){ZAsoIIRfMY = false;}
      if(SOAnDFzUob == true){SOAnDFzUob = false;}
      if(tCKnjWtzxh == true){tCKnjWtzxh = false;}
      if(lhFSCHCnry == true){lhFSCHCnry = false;}
      if(GXtGolCADV == true){GXtGolCADV = false;}
      if(JIxmBWoFFk == true){JIxmBWoFFk = false;}
      if(NRhdljIhlw == true){NRhdljIhlw = false;}
      if(CKbpUVIEyx == true){CKbpUVIEyx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EDWSRCECPU
{ 
  void JTDoFrasuR()
  { 
      bool yLJTBESAVJ = false;
      bool cdoQKFqthA = false;
      bool JlEqtoajyN = false;
      bool BGawaQCfTy = false;
      bool BtfCxZbmzg = false;
      bool NhYiVMGRZL = false;
      bool chCIHWCsot = false;
      bool DLajzPFCsT = false;
      bool MnkQzThraO = false;
      bool JjGHVTrXta = false;
      bool WixFdBHojG = false;
      bool GEXFzowkIn = false;
      bool oKRajSFTOe = false;
      bool XhHSxcpelx = false;
      bool MrIUIEMAHg = false;
      bool WGOGlMRVUL = false;
      bool wmaEhXwFHV = false;
      bool yRyKawCxSe = false;
      bool FEMhIQTAgk = false;
      bool LTJaBYRDlj = false;
      string cBGdDfyJHJ;
      string KAQxXOGPeZ;
      string ZiYefSZbbJ;
      string mDfuPtSIqD;
      string emZbTQXLfm;
      string BgSRotbayj;
      string FVgyWHTUhd;
      string uxXaumIwLO;
      string uOwoIGjOGU;
      string RqKGyJFbFL;
      string wCdBqDIqWC;
      string kePioqZrpQ;
      string XFOMLElQbl;
      string ggqzRrjtxE;
      string xrrEjlbaRH;
      string iNlonqnRpm;
      string QqOjUEnPRx;
      string GeukSeNKbY;
      string bLzUCTtCLa;
      string DREKmFcHie;
      if(cBGdDfyJHJ == wCdBqDIqWC){yLJTBESAVJ = true;}
      else if(wCdBqDIqWC == cBGdDfyJHJ){WixFdBHojG = true;}
      if(KAQxXOGPeZ == kePioqZrpQ){cdoQKFqthA = true;}
      else if(kePioqZrpQ == KAQxXOGPeZ){GEXFzowkIn = true;}
      if(ZiYefSZbbJ == XFOMLElQbl){JlEqtoajyN = true;}
      else if(XFOMLElQbl == ZiYefSZbbJ){oKRajSFTOe = true;}
      if(mDfuPtSIqD == ggqzRrjtxE){BGawaQCfTy = true;}
      else if(ggqzRrjtxE == mDfuPtSIqD){XhHSxcpelx = true;}
      if(emZbTQXLfm == xrrEjlbaRH){BtfCxZbmzg = true;}
      else if(xrrEjlbaRH == emZbTQXLfm){MrIUIEMAHg = true;}
      if(BgSRotbayj == iNlonqnRpm){NhYiVMGRZL = true;}
      else if(iNlonqnRpm == BgSRotbayj){WGOGlMRVUL = true;}
      if(FVgyWHTUhd == QqOjUEnPRx){chCIHWCsot = true;}
      else if(QqOjUEnPRx == FVgyWHTUhd){wmaEhXwFHV = true;}
      if(uxXaumIwLO == GeukSeNKbY){DLajzPFCsT = true;}
      if(uOwoIGjOGU == bLzUCTtCLa){MnkQzThraO = true;}
      if(RqKGyJFbFL == DREKmFcHie){JjGHVTrXta = true;}
      while(GeukSeNKbY == uxXaumIwLO){yRyKawCxSe = true;}
      while(bLzUCTtCLa == bLzUCTtCLa){FEMhIQTAgk = true;}
      while(DREKmFcHie == DREKmFcHie){LTJaBYRDlj = true;}
      if(yLJTBESAVJ == true){yLJTBESAVJ = false;}
      if(cdoQKFqthA == true){cdoQKFqthA = false;}
      if(JlEqtoajyN == true){JlEqtoajyN = false;}
      if(BGawaQCfTy == true){BGawaQCfTy = false;}
      if(BtfCxZbmzg == true){BtfCxZbmzg = false;}
      if(NhYiVMGRZL == true){NhYiVMGRZL = false;}
      if(chCIHWCsot == true){chCIHWCsot = false;}
      if(DLajzPFCsT == true){DLajzPFCsT = false;}
      if(MnkQzThraO == true){MnkQzThraO = false;}
      if(JjGHVTrXta == true){JjGHVTrXta = false;}
      if(WixFdBHojG == true){WixFdBHojG = false;}
      if(GEXFzowkIn == true){GEXFzowkIn = false;}
      if(oKRajSFTOe == true){oKRajSFTOe = false;}
      if(XhHSxcpelx == true){XhHSxcpelx = false;}
      if(MrIUIEMAHg == true){MrIUIEMAHg = false;}
      if(WGOGlMRVUL == true){WGOGlMRVUL = false;}
      if(wmaEhXwFHV == true){wmaEhXwFHV = false;}
      if(yRyKawCxSe == true){yRyKawCxSe = false;}
      if(FEMhIQTAgk == true){FEMhIQTAgk = false;}
      if(LTJaBYRDlj == true){LTJaBYRDlj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TICXWRPFSU
{ 
  void EBgxgbwCQf()
  { 
      bool WhMIlMblyR = false;
      bool dmHcDhKOFy = false;
      bool wNIxScBFkY = false;
      bool rncMbCSnxj = false;
      bool EsqWkGnRFU = false;
      bool aBPZwIZOpJ = false;
      bool KWBYZpKuBA = false;
      bool PVRUtCWkML = false;
      bool njAPypYDPS = false;
      bool cDynYgrRxt = false;
      bool wrPEEEjtft = false;
      bool lnCdUZWkZi = false;
      bool RHfhXMXcuM = false;
      bool KEmSPwUuKt = false;
      bool GdWUgnBTSy = false;
      bool KGqOcnLhfr = false;
      bool fGySjgAiOX = false;
      bool FaafcmjKBi = false;
      bool LEKwCDMYpa = false;
      bool jlPRNzeDkA = false;
      string fEMjFpQkqt;
      string QeuAsXWbIz;
      string zLqnyfMaSA;
      string alUkXqPaqV;
      string RWXfbcDPDN;
      string OJeoeUNYkY;
      string dpRqTeKKcC;
      string HujlhcmKMV;
      string cwWEkQHeFC;
      string cqpRrbEgLx;
      string SsmAFTYrHC;
      string hCLPwgSNGC;
      string WfEZYQFRtF;
      string XGyOCiIVyR;
      string rOWDUaeZVK;
      string IqaJZmoMbo;
      string NGyCebDxMM;
      string YwOnKIIBFy;
      string kewiwgeonP;
      string tutJDkQUXs;
      if(fEMjFpQkqt == SsmAFTYrHC){WhMIlMblyR = true;}
      else if(SsmAFTYrHC == fEMjFpQkqt){wrPEEEjtft = true;}
      if(QeuAsXWbIz == hCLPwgSNGC){dmHcDhKOFy = true;}
      else if(hCLPwgSNGC == QeuAsXWbIz){lnCdUZWkZi = true;}
      if(zLqnyfMaSA == WfEZYQFRtF){wNIxScBFkY = true;}
      else if(WfEZYQFRtF == zLqnyfMaSA){RHfhXMXcuM = true;}
      if(alUkXqPaqV == XGyOCiIVyR){rncMbCSnxj = true;}
      else if(XGyOCiIVyR == alUkXqPaqV){KEmSPwUuKt = true;}
      if(RWXfbcDPDN == rOWDUaeZVK){EsqWkGnRFU = true;}
      else if(rOWDUaeZVK == RWXfbcDPDN){GdWUgnBTSy = true;}
      if(OJeoeUNYkY == IqaJZmoMbo){aBPZwIZOpJ = true;}
      else if(IqaJZmoMbo == OJeoeUNYkY){KGqOcnLhfr = true;}
      if(dpRqTeKKcC == NGyCebDxMM){KWBYZpKuBA = true;}
      else if(NGyCebDxMM == dpRqTeKKcC){fGySjgAiOX = true;}
      if(HujlhcmKMV == YwOnKIIBFy){PVRUtCWkML = true;}
      if(cwWEkQHeFC == kewiwgeonP){njAPypYDPS = true;}
      if(cqpRrbEgLx == tutJDkQUXs){cDynYgrRxt = true;}
      while(YwOnKIIBFy == HujlhcmKMV){FaafcmjKBi = true;}
      while(kewiwgeonP == kewiwgeonP){LEKwCDMYpa = true;}
      while(tutJDkQUXs == tutJDkQUXs){jlPRNzeDkA = true;}
      if(WhMIlMblyR == true){WhMIlMblyR = false;}
      if(dmHcDhKOFy == true){dmHcDhKOFy = false;}
      if(wNIxScBFkY == true){wNIxScBFkY = false;}
      if(rncMbCSnxj == true){rncMbCSnxj = false;}
      if(EsqWkGnRFU == true){EsqWkGnRFU = false;}
      if(aBPZwIZOpJ == true){aBPZwIZOpJ = false;}
      if(KWBYZpKuBA == true){KWBYZpKuBA = false;}
      if(PVRUtCWkML == true){PVRUtCWkML = false;}
      if(njAPypYDPS == true){njAPypYDPS = false;}
      if(cDynYgrRxt == true){cDynYgrRxt = false;}
      if(wrPEEEjtft == true){wrPEEEjtft = false;}
      if(lnCdUZWkZi == true){lnCdUZWkZi = false;}
      if(RHfhXMXcuM == true){RHfhXMXcuM = false;}
      if(KEmSPwUuKt == true){KEmSPwUuKt = false;}
      if(GdWUgnBTSy == true){GdWUgnBTSy = false;}
      if(KGqOcnLhfr == true){KGqOcnLhfr = false;}
      if(fGySjgAiOX == true){fGySjgAiOX = false;}
      if(FaafcmjKBi == true){FaafcmjKBi = false;}
      if(LEKwCDMYpa == true){LEKwCDMYpa = false;}
      if(jlPRNzeDkA == true){jlPRNzeDkA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HLSSGBOUEU
{ 
  void YZORiiJhDD()
  { 
      bool DYluVupzcq = false;
      bool ojGflTwTcy = false;
      bool LkmpdJyDQE = false;
      bool RiHwKQSiGj = false;
      bool EYRtidGAfM = false;
      bool hTrxTSlwQL = false;
      bool wlhYYGbKVU = false;
      bool BMMrtlSrHA = false;
      bool DyXEVypKbq = false;
      bool eVStnRpsUb = false;
      bool CueKLUHADg = false;
      bool zsoPIxOdCa = false;
      bool PRhdoetREb = false;
      bool uZWeyHTMsA = false;
      bool ppGtqkgClq = false;
      bool DMpsMjNAVf = false;
      bool apublZWJRB = false;
      bool cBjBkYKmlD = false;
      bool xqfNXhjcRN = false;
      bool tTqMZAteIR = false;
      string fXkeetyuyV;
      string CSIzahDMpo;
      string iIiEBAEaVI;
      string nIqXpImMME;
      string DBnfgERhIL;
      string VqEzhWnfdd;
      string pXZohsajIR;
      string upzkkhTDWw;
      string iVRJlwDrpS;
      string UGihOfazxm;
      string dgYqPfqTNA;
      string DkIgtUFPCl;
      string pispxnGRWF;
      string GTFjSBwatF;
      string EjdoOiyBmt;
      string ZLwKxtnitb;
      string ZZwIsieYOr;
      string XeVxhFEDbN;
      string pFdcetXtlX;
      string NNfRfdmVwe;
      if(fXkeetyuyV == dgYqPfqTNA){DYluVupzcq = true;}
      else if(dgYqPfqTNA == fXkeetyuyV){CueKLUHADg = true;}
      if(CSIzahDMpo == DkIgtUFPCl){ojGflTwTcy = true;}
      else if(DkIgtUFPCl == CSIzahDMpo){zsoPIxOdCa = true;}
      if(iIiEBAEaVI == pispxnGRWF){LkmpdJyDQE = true;}
      else if(pispxnGRWF == iIiEBAEaVI){PRhdoetREb = true;}
      if(nIqXpImMME == GTFjSBwatF){RiHwKQSiGj = true;}
      else if(GTFjSBwatF == nIqXpImMME){uZWeyHTMsA = true;}
      if(DBnfgERhIL == EjdoOiyBmt){EYRtidGAfM = true;}
      else if(EjdoOiyBmt == DBnfgERhIL){ppGtqkgClq = true;}
      if(VqEzhWnfdd == ZLwKxtnitb){hTrxTSlwQL = true;}
      else if(ZLwKxtnitb == VqEzhWnfdd){DMpsMjNAVf = true;}
      if(pXZohsajIR == ZZwIsieYOr){wlhYYGbKVU = true;}
      else if(ZZwIsieYOr == pXZohsajIR){apublZWJRB = true;}
      if(upzkkhTDWw == XeVxhFEDbN){BMMrtlSrHA = true;}
      if(iVRJlwDrpS == pFdcetXtlX){DyXEVypKbq = true;}
      if(UGihOfazxm == NNfRfdmVwe){eVStnRpsUb = true;}
      while(XeVxhFEDbN == upzkkhTDWw){cBjBkYKmlD = true;}
      while(pFdcetXtlX == pFdcetXtlX){xqfNXhjcRN = true;}
      while(NNfRfdmVwe == NNfRfdmVwe){tTqMZAteIR = true;}
      if(DYluVupzcq == true){DYluVupzcq = false;}
      if(ojGflTwTcy == true){ojGflTwTcy = false;}
      if(LkmpdJyDQE == true){LkmpdJyDQE = false;}
      if(RiHwKQSiGj == true){RiHwKQSiGj = false;}
      if(EYRtidGAfM == true){EYRtidGAfM = false;}
      if(hTrxTSlwQL == true){hTrxTSlwQL = false;}
      if(wlhYYGbKVU == true){wlhYYGbKVU = false;}
      if(BMMrtlSrHA == true){BMMrtlSrHA = false;}
      if(DyXEVypKbq == true){DyXEVypKbq = false;}
      if(eVStnRpsUb == true){eVStnRpsUb = false;}
      if(CueKLUHADg == true){CueKLUHADg = false;}
      if(zsoPIxOdCa == true){zsoPIxOdCa = false;}
      if(PRhdoetREb == true){PRhdoetREb = false;}
      if(uZWeyHTMsA == true){uZWeyHTMsA = false;}
      if(ppGtqkgClq == true){ppGtqkgClq = false;}
      if(DMpsMjNAVf == true){DMpsMjNAVf = false;}
      if(apublZWJRB == true){apublZWJRB = false;}
      if(cBjBkYKmlD == true){cBjBkYKmlD = false;}
      if(xqfNXhjcRN == true){xqfNXhjcRN = false;}
      if(tTqMZAteIR == true){tTqMZAteIR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZVRKBOSCZU
{ 
  void ghBPCdMEwh()
  { 
      bool NaLFOwPdfC = false;
      bool bBgisCgDzb = false;
      bool BujQkEufFU = false;
      bool bwJOprdwor = false;
      bool QIuZgnqdtl = false;
      bool aLmeLSquTK = false;
      bool BjXLZfqRrA = false;
      bool YjNHKszKix = false;
      bool MRkTtPJeDX = false;
      bool BhbepgkjzB = false;
      bool wZksMpyeTR = false;
      bool SgLWxjyDRJ = false;
      bool VMOUzpIiQc = false;
      bool IPKgAlfrHD = false;
      bool ReKkFUWFgG = false;
      bool igSpfiKQtW = false;
      bool hOOqJDVeVL = false;
      bool DGwNqqCcOe = false;
      bool TDCJtaxUBR = false;
      bool aPxjVDPTaB = false;
      string lhhRzSWtHi;
      string GQuhsDhjfG;
      string DgMXdRlkJg;
      string LVycEMeWsi;
      string ylYAsmOQIq;
      string fFyooFUKmh;
      string gkkaXkRScg;
      string YLqwHQHMdq;
      string CVbRAFXImz;
      string rTiKCNBybH;
      string UwmbSUOBhX;
      string xHgwfKISZS;
      string NJednFbfts;
      string PJkVVFhAzf;
      string pVaOBjlmeq;
      string EiXItLQJmM;
      string rhGnInWLaZ;
      string cIStcqiPbE;
      string ToBDoglbbJ;
      string oYMmnHPlGN;
      if(lhhRzSWtHi == UwmbSUOBhX){NaLFOwPdfC = true;}
      else if(UwmbSUOBhX == lhhRzSWtHi){wZksMpyeTR = true;}
      if(GQuhsDhjfG == xHgwfKISZS){bBgisCgDzb = true;}
      else if(xHgwfKISZS == GQuhsDhjfG){SgLWxjyDRJ = true;}
      if(DgMXdRlkJg == NJednFbfts){BujQkEufFU = true;}
      else if(NJednFbfts == DgMXdRlkJg){VMOUzpIiQc = true;}
      if(LVycEMeWsi == PJkVVFhAzf){bwJOprdwor = true;}
      else if(PJkVVFhAzf == LVycEMeWsi){IPKgAlfrHD = true;}
      if(ylYAsmOQIq == pVaOBjlmeq){QIuZgnqdtl = true;}
      else if(pVaOBjlmeq == ylYAsmOQIq){ReKkFUWFgG = true;}
      if(fFyooFUKmh == EiXItLQJmM){aLmeLSquTK = true;}
      else if(EiXItLQJmM == fFyooFUKmh){igSpfiKQtW = true;}
      if(gkkaXkRScg == rhGnInWLaZ){BjXLZfqRrA = true;}
      else if(rhGnInWLaZ == gkkaXkRScg){hOOqJDVeVL = true;}
      if(YLqwHQHMdq == cIStcqiPbE){YjNHKszKix = true;}
      if(CVbRAFXImz == ToBDoglbbJ){MRkTtPJeDX = true;}
      if(rTiKCNBybH == oYMmnHPlGN){BhbepgkjzB = true;}
      while(cIStcqiPbE == YLqwHQHMdq){DGwNqqCcOe = true;}
      while(ToBDoglbbJ == ToBDoglbbJ){TDCJtaxUBR = true;}
      while(oYMmnHPlGN == oYMmnHPlGN){aPxjVDPTaB = true;}
      if(NaLFOwPdfC == true){NaLFOwPdfC = false;}
      if(bBgisCgDzb == true){bBgisCgDzb = false;}
      if(BujQkEufFU == true){BujQkEufFU = false;}
      if(bwJOprdwor == true){bwJOprdwor = false;}
      if(QIuZgnqdtl == true){QIuZgnqdtl = false;}
      if(aLmeLSquTK == true){aLmeLSquTK = false;}
      if(BjXLZfqRrA == true){BjXLZfqRrA = false;}
      if(YjNHKszKix == true){YjNHKszKix = false;}
      if(MRkTtPJeDX == true){MRkTtPJeDX = false;}
      if(BhbepgkjzB == true){BhbepgkjzB = false;}
      if(wZksMpyeTR == true){wZksMpyeTR = false;}
      if(SgLWxjyDRJ == true){SgLWxjyDRJ = false;}
      if(VMOUzpIiQc == true){VMOUzpIiQc = false;}
      if(IPKgAlfrHD == true){IPKgAlfrHD = false;}
      if(ReKkFUWFgG == true){ReKkFUWFgG = false;}
      if(igSpfiKQtW == true){igSpfiKQtW = false;}
      if(hOOqJDVeVL == true){hOOqJDVeVL = false;}
      if(DGwNqqCcOe == true){DGwNqqCcOe = false;}
      if(TDCJtaxUBR == true){TDCJtaxUBR = false;}
      if(aPxjVDPTaB == true){aPxjVDPTaB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGOUYJXRWR
{ 
  void ZSjjktJFHo()
  { 
      bool kWfefizuKT = false;
      bool RiItiwWnJk = false;
      bool eaRIUhmnDA = false;
      bool aVRhNntTaO = false;
      bool xxzHJWdGPx = false;
      bool lGywDKEWJx = false;
      bool wKqJsuQagu = false;
      bool BDMtmgaKzx = false;
      bool DgYGOUWUdD = false;
      bool iWJcSlGpNN = false;
      bool FDYTuisDJV = false;
      bool itXMtOlktX = false;
      bool YwwdMesiaB = false;
      bool akwkqAHEKf = false;
      bool aSLITozxiE = false;
      bool AVwpoJGtHQ = false;
      bool pJcItyxlUs = false;
      bool GgZNxFjnKW = false;
      bool euAWAFnGwg = false;
      bool tMxtpQpDNV = false;
      string fAwLtYbftE;
      string opDszEHDOc;
      string RiuTrnkhkF;
      string IlBEKqCrcX;
      string ANsGDeydXW;
      string bBtGVwEbTG;
      string nstowCoyiI;
      string BOaqbDonQM;
      string oGKNcGrtiN;
      string laXViGTEKA;
      string pztPUNaDdS;
      string HPKHQgifMp;
      string KtPVVaqEIV;
      string jjdQWpMtrP;
      string foQPFWQQFB;
      string XmrUouiYst;
      string VVtIhWksja;
      string UnmxJVdAPz;
      string KZzGyxrJaa;
      string GmBysJtIhh;
      if(fAwLtYbftE == pztPUNaDdS){kWfefizuKT = true;}
      else if(pztPUNaDdS == fAwLtYbftE){FDYTuisDJV = true;}
      if(opDszEHDOc == HPKHQgifMp){RiItiwWnJk = true;}
      else if(HPKHQgifMp == opDszEHDOc){itXMtOlktX = true;}
      if(RiuTrnkhkF == KtPVVaqEIV){eaRIUhmnDA = true;}
      else if(KtPVVaqEIV == RiuTrnkhkF){YwwdMesiaB = true;}
      if(IlBEKqCrcX == jjdQWpMtrP){aVRhNntTaO = true;}
      else if(jjdQWpMtrP == IlBEKqCrcX){akwkqAHEKf = true;}
      if(ANsGDeydXW == foQPFWQQFB){xxzHJWdGPx = true;}
      else if(foQPFWQQFB == ANsGDeydXW){aSLITozxiE = true;}
      if(bBtGVwEbTG == XmrUouiYst){lGywDKEWJx = true;}
      else if(XmrUouiYst == bBtGVwEbTG){AVwpoJGtHQ = true;}
      if(nstowCoyiI == VVtIhWksja){wKqJsuQagu = true;}
      else if(VVtIhWksja == nstowCoyiI){pJcItyxlUs = true;}
      if(BOaqbDonQM == UnmxJVdAPz){BDMtmgaKzx = true;}
      if(oGKNcGrtiN == KZzGyxrJaa){DgYGOUWUdD = true;}
      if(laXViGTEKA == GmBysJtIhh){iWJcSlGpNN = true;}
      while(UnmxJVdAPz == BOaqbDonQM){GgZNxFjnKW = true;}
      while(KZzGyxrJaa == KZzGyxrJaa){euAWAFnGwg = true;}
      while(GmBysJtIhh == GmBysJtIhh){tMxtpQpDNV = true;}
      if(kWfefizuKT == true){kWfefizuKT = false;}
      if(RiItiwWnJk == true){RiItiwWnJk = false;}
      if(eaRIUhmnDA == true){eaRIUhmnDA = false;}
      if(aVRhNntTaO == true){aVRhNntTaO = false;}
      if(xxzHJWdGPx == true){xxzHJWdGPx = false;}
      if(lGywDKEWJx == true){lGywDKEWJx = false;}
      if(wKqJsuQagu == true){wKqJsuQagu = false;}
      if(BDMtmgaKzx == true){BDMtmgaKzx = false;}
      if(DgYGOUWUdD == true){DgYGOUWUdD = false;}
      if(iWJcSlGpNN == true){iWJcSlGpNN = false;}
      if(FDYTuisDJV == true){FDYTuisDJV = false;}
      if(itXMtOlktX == true){itXMtOlktX = false;}
      if(YwwdMesiaB == true){YwwdMesiaB = false;}
      if(akwkqAHEKf == true){akwkqAHEKf = false;}
      if(aSLITozxiE == true){aSLITozxiE = false;}
      if(AVwpoJGtHQ == true){AVwpoJGtHQ = false;}
      if(pJcItyxlUs == true){pJcItyxlUs = false;}
      if(GgZNxFjnKW == true){GgZNxFjnKW = false;}
      if(euAWAFnGwg == true){euAWAFnGwg = false;}
      if(tMxtpQpDNV == true){tMxtpQpDNV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SRWJDDUPMA
{ 
  void WAjVSoMzDk()
  { 
      bool eIfkFNaBXI = false;
      bool RmhFyPmpMd = false;
      bool fLnAzSAGTi = false;
      bool IxResKlkIQ = false;
      bool OAhhUniibm = false;
      bool WEYEXSTfkm = false;
      bool NThnzUVDLm = false;
      bool dBhwPedFeL = false;
      bool iRegLEXMGZ = false;
      bool pFzUDtSshz = false;
      bool ReWnJUVbor = false;
      bool oOAZDuoAbu = false;
      bool wJwkxXCNrU = false;
      bool MjXesEtpWq = false;
      bool huXOjbFYRI = false;
      bool FRQlCIhkqk = false;
      bool SIjTfFpUgz = false;
      bool AzdkNBkhBV = false;
      bool ScwjPtSkcj = false;
      bool VIylXYLDie = false;
      string RhtCdIfxLG;
      string lhyfUrAmCT;
      string DzwtadWLJA;
      string kZTWOSTUCr;
      string cVqybaUDyu;
      string xbRQARkAaz;
      string kTnKVLOaRB;
      string YekJqgIySA;
      string JTNNCJHCWw;
      string hTtCGIhgbP;
      string MslwVSqIZS;
      string JlgapRFZHL;
      string DLEUTFkhDh;
      string yaVCnPhQqj;
      string SzcDlulSLo;
      string CIYQMAnQcQ;
      string gIErThQdma;
      string iohWsDhBhX;
      string SRVNeoCFpm;
      string aQnaDJukiD;
      if(RhtCdIfxLG == MslwVSqIZS){eIfkFNaBXI = true;}
      else if(MslwVSqIZS == RhtCdIfxLG){ReWnJUVbor = true;}
      if(lhyfUrAmCT == JlgapRFZHL){RmhFyPmpMd = true;}
      else if(JlgapRFZHL == lhyfUrAmCT){oOAZDuoAbu = true;}
      if(DzwtadWLJA == DLEUTFkhDh){fLnAzSAGTi = true;}
      else if(DLEUTFkhDh == DzwtadWLJA){wJwkxXCNrU = true;}
      if(kZTWOSTUCr == yaVCnPhQqj){IxResKlkIQ = true;}
      else if(yaVCnPhQqj == kZTWOSTUCr){MjXesEtpWq = true;}
      if(cVqybaUDyu == SzcDlulSLo){OAhhUniibm = true;}
      else if(SzcDlulSLo == cVqybaUDyu){huXOjbFYRI = true;}
      if(xbRQARkAaz == CIYQMAnQcQ){WEYEXSTfkm = true;}
      else if(CIYQMAnQcQ == xbRQARkAaz){FRQlCIhkqk = true;}
      if(kTnKVLOaRB == gIErThQdma){NThnzUVDLm = true;}
      else if(gIErThQdma == kTnKVLOaRB){SIjTfFpUgz = true;}
      if(YekJqgIySA == iohWsDhBhX){dBhwPedFeL = true;}
      if(JTNNCJHCWw == SRVNeoCFpm){iRegLEXMGZ = true;}
      if(hTtCGIhgbP == aQnaDJukiD){pFzUDtSshz = true;}
      while(iohWsDhBhX == YekJqgIySA){AzdkNBkhBV = true;}
      while(SRVNeoCFpm == SRVNeoCFpm){ScwjPtSkcj = true;}
      while(aQnaDJukiD == aQnaDJukiD){VIylXYLDie = true;}
      if(eIfkFNaBXI == true){eIfkFNaBXI = false;}
      if(RmhFyPmpMd == true){RmhFyPmpMd = false;}
      if(fLnAzSAGTi == true){fLnAzSAGTi = false;}
      if(IxResKlkIQ == true){IxResKlkIQ = false;}
      if(OAhhUniibm == true){OAhhUniibm = false;}
      if(WEYEXSTfkm == true){WEYEXSTfkm = false;}
      if(NThnzUVDLm == true){NThnzUVDLm = false;}
      if(dBhwPedFeL == true){dBhwPedFeL = false;}
      if(iRegLEXMGZ == true){iRegLEXMGZ = false;}
      if(pFzUDtSshz == true){pFzUDtSshz = false;}
      if(ReWnJUVbor == true){ReWnJUVbor = false;}
      if(oOAZDuoAbu == true){oOAZDuoAbu = false;}
      if(wJwkxXCNrU == true){wJwkxXCNrU = false;}
      if(MjXesEtpWq == true){MjXesEtpWq = false;}
      if(huXOjbFYRI == true){huXOjbFYRI = false;}
      if(FRQlCIhkqk == true){FRQlCIhkqk = false;}
      if(SIjTfFpUgz == true){SIjTfFpUgz = false;}
      if(AzdkNBkhBV == true){AzdkNBkhBV = false;}
      if(ScwjPtSkcj == true){ScwjPtSkcj = false;}
      if(VIylXYLDie == true){VIylXYLDie = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZDCLRUNTDH
{ 
  void CLGnaJxiia()
  { 
      bool KZeBeIgNGl = false;
      bool AXYiQbrTgb = false;
      bool clVRnsJcZc = false;
      bool bLFMaXzUai = false;
      bool oJkwjcwxpe = false;
      bool FuJGOYENNk = false;
      bool yEncKnRLIs = false;
      bool bWrylTAZgL = false;
      bool wMluXfCyyB = false;
      bool TkHokkVHkw = false;
      bool KkoxChCLTu = false;
      bool XdgColRsFd = false;
      bool lSNGYpOCNB = false;
      bool yrnjALWnro = false;
      bool cpdCdoEFAy = false;
      bool SbCHJqWiXM = false;
      bool TAySxepwBd = false;
      bool OcBPAuoKbj = false;
      bool lJCOiVpgaI = false;
      bool nmPeVcrLFz = false;
      string sxunMioCSB;
      string igKkIzQowI;
      string JVyOjRzEfp;
      string WrfUfqackp;
      string awQBxXXcKP;
      string HgeyAWzgDt;
      string jkWbeqBpEQ;
      string XmEGgNFwRL;
      string sWsPhpMgTI;
      string qtZqGpYnWG;
      string WhXsrUcYQm;
      string RDPqAMqHto;
      string dTVuZcNNzq;
      string nRZKoLyAWN;
      string NnQgqnehps;
      string zRthbDLcTP;
      string GPYZyAdECn;
      string OpjfapCnDk;
      string yeWFrWWqhk;
      string AVfHGyOqiq;
      if(sxunMioCSB == WhXsrUcYQm){KZeBeIgNGl = true;}
      else if(WhXsrUcYQm == sxunMioCSB){KkoxChCLTu = true;}
      if(igKkIzQowI == RDPqAMqHto){AXYiQbrTgb = true;}
      else if(RDPqAMqHto == igKkIzQowI){XdgColRsFd = true;}
      if(JVyOjRzEfp == dTVuZcNNzq){clVRnsJcZc = true;}
      else if(dTVuZcNNzq == JVyOjRzEfp){lSNGYpOCNB = true;}
      if(WrfUfqackp == nRZKoLyAWN){bLFMaXzUai = true;}
      else if(nRZKoLyAWN == WrfUfqackp){yrnjALWnro = true;}
      if(awQBxXXcKP == NnQgqnehps){oJkwjcwxpe = true;}
      else if(NnQgqnehps == awQBxXXcKP){cpdCdoEFAy = true;}
      if(HgeyAWzgDt == zRthbDLcTP){FuJGOYENNk = true;}
      else if(zRthbDLcTP == HgeyAWzgDt){SbCHJqWiXM = true;}
      if(jkWbeqBpEQ == GPYZyAdECn){yEncKnRLIs = true;}
      else if(GPYZyAdECn == jkWbeqBpEQ){TAySxepwBd = true;}
      if(XmEGgNFwRL == OpjfapCnDk){bWrylTAZgL = true;}
      if(sWsPhpMgTI == yeWFrWWqhk){wMluXfCyyB = true;}
      if(qtZqGpYnWG == AVfHGyOqiq){TkHokkVHkw = true;}
      while(OpjfapCnDk == XmEGgNFwRL){OcBPAuoKbj = true;}
      while(yeWFrWWqhk == yeWFrWWqhk){lJCOiVpgaI = true;}
      while(AVfHGyOqiq == AVfHGyOqiq){nmPeVcrLFz = true;}
      if(KZeBeIgNGl == true){KZeBeIgNGl = false;}
      if(AXYiQbrTgb == true){AXYiQbrTgb = false;}
      if(clVRnsJcZc == true){clVRnsJcZc = false;}
      if(bLFMaXzUai == true){bLFMaXzUai = false;}
      if(oJkwjcwxpe == true){oJkwjcwxpe = false;}
      if(FuJGOYENNk == true){FuJGOYENNk = false;}
      if(yEncKnRLIs == true){yEncKnRLIs = false;}
      if(bWrylTAZgL == true){bWrylTAZgL = false;}
      if(wMluXfCyyB == true){wMluXfCyyB = false;}
      if(TkHokkVHkw == true){TkHokkVHkw = false;}
      if(KkoxChCLTu == true){KkoxChCLTu = false;}
      if(XdgColRsFd == true){XdgColRsFd = false;}
      if(lSNGYpOCNB == true){lSNGYpOCNB = false;}
      if(yrnjALWnro == true){yrnjALWnro = false;}
      if(cpdCdoEFAy == true){cpdCdoEFAy = false;}
      if(SbCHJqWiXM == true){SbCHJqWiXM = false;}
      if(TAySxepwBd == true){TAySxepwBd = false;}
      if(OcBPAuoKbj == true){OcBPAuoKbj = false;}
      if(lJCOiVpgaI == true){lJCOiVpgaI = false;}
      if(nmPeVcrLFz == true){nmPeVcrLFz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GICYEHIJPM
{ 
  void CPOQcfsDgo()
  { 
      bool TXihCbVNHR = false;
      bool ajEYYlllBq = false;
      bool gBKTQbDUIm = false;
      bool tAfQwaxbRJ = false;
      bool ZNFHEfQddy = false;
      bool NpYUNRNPRZ = false;
      bool YBFTXaDmbx = false;
      bool nKTrQSwDOk = false;
      bool LYqJZDbLCd = false;
      bool NgKqkYIkjc = false;
      bool ccBfKDVgDu = false;
      bool VKAgOzKutT = false;
      bool zqjxjGAcHr = false;
      bool JKSkHiWKzV = false;
      bool gtIHIDgcck = false;
      bool OMqQdkrEwD = false;
      bool CsZKkKqOYf = false;
      bool bAwXlEicof = false;
      bool ZWzVdwTCHW = false;
      bool pSNwTnUxVy = false;
      string EdjxjGsGjI;
      string HrOkLeHliE;
      string jZWZlAHRAA;
      string EodsZKQbXg;
      string FzmjOIoqmt;
      string OkdGOdHJLj;
      string yaFiESOVKA;
      string OfNCzjmmKc;
      string LQdGlTLWdu;
      string CGQnhesDfw;
      string tTfmehWbHd;
      string qUyhYhwzxk;
      string HqqPyHPZUT;
      string piGOiqkqaD;
      string xjOzDhIhPz;
      string htGtoDbPoX;
      string SwGnmINjzg;
      string xFXsmWbrLQ;
      string zgKUlwbMYf;
      string PUCCkAcaLu;
      if(EdjxjGsGjI == tTfmehWbHd){TXihCbVNHR = true;}
      else if(tTfmehWbHd == EdjxjGsGjI){ccBfKDVgDu = true;}
      if(HrOkLeHliE == qUyhYhwzxk){ajEYYlllBq = true;}
      else if(qUyhYhwzxk == HrOkLeHliE){VKAgOzKutT = true;}
      if(jZWZlAHRAA == HqqPyHPZUT){gBKTQbDUIm = true;}
      else if(HqqPyHPZUT == jZWZlAHRAA){zqjxjGAcHr = true;}
      if(EodsZKQbXg == piGOiqkqaD){tAfQwaxbRJ = true;}
      else if(piGOiqkqaD == EodsZKQbXg){JKSkHiWKzV = true;}
      if(FzmjOIoqmt == xjOzDhIhPz){ZNFHEfQddy = true;}
      else if(xjOzDhIhPz == FzmjOIoqmt){gtIHIDgcck = true;}
      if(OkdGOdHJLj == htGtoDbPoX){NpYUNRNPRZ = true;}
      else if(htGtoDbPoX == OkdGOdHJLj){OMqQdkrEwD = true;}
      if(yaFiESOVKA == SwGnmINjzg){YBFTXaDmbx = true;}
      else if(SwGnmINjzg == yaFiESOVKA){CsZKkKqOYf = true;}
      if(OfNCzjmmKc == xFXsmWbrLQ){nKTrQSwDOk = true;}
      if(LQdGlTLWdu == zgKUlwbMYf){LYqJZDbLCd = true;}
      if(CGQnhesDfw == PUCCkAcaLu){NgKqkYIkjc = true;}
      while(xFXsmWbrLQ == OfNCzjmmKc){bAwXlEicof = true;}
      while(zgKUlwbMYf == zgKUlwbMYf){ZWzVdwTCHW = true;}
      while(PUCCkAcaLu == PUCCkAcaLu){pSNwTnUxVy = true;}
      if(TXihCbVNHR == true){TXihCbVNHR = false;}
      if(ajEYYlllBq == true){ajEYYlllBq = false;}
      if(gBKTQbDUIm == true){gBKTQbDUIm = false;}
      if(tAfQwaxbRJ == true){tAfQwaxbRJ = false;}
      if(ZNFHEfQddy == true){ZNFHEfQddy = false;}
      if(NpYUNRNPRZ == true){NpYUNRNPRZ = false;}
      if(YBFTXaDmbx == true){YBFTXaDmbx = false;}
      if(nKTrQSwDOk == true){nKTrQSwDOk = false;}
      if(LYqJZDbLCd == true){LYqJZDbLCd = false;}
      if(NgKqkYIkjc == true){NgKqkYIkjc = false;}
      if(ccBfKDVgDu == true){ccBfKDVgDu = false;}
      if(VKAgOzKutT == true){VKAgOzKutT = false;}
      if(zqjxjGAcHr == true){zqjxjGAcHr = false;}
      if(JKSkHiWKzV == true){JKSkHiWKzV = false;}
      if(gtIHIDgcck == true){gtIHIDgcck = false;}
      if(OMqQdkrEwD == true){OMqQdkrEwD = false;}
      if(CsZKkKqOYf == true){CsZKkKqOYf = false;}
      if(bAwXlEicof == true){bAwXlEicof = false;}
      if(ZWzVdwTCHW == true){ZWzVdwTCHW = false;}
      if(pSNwTnUxVy == true){pSNwTnUxVy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EXWXRVJAQA
{ 
  void OandjDiRpQ()
  { 
      bool wJGWrMbbsy = false;
      bool ioCKPAOetG = false;
      bool KeToyxVwwS = false;
      bool XIHLrKVfkT = false;
      bool SzRqeyKLtO = false;
      bool HznYnQoRYt = false;
      bool pffZaZhpRE = false;
      bool disZnKNcKA = false;
      bool mKBgLYUhXb = false;
      bool UEHqclTrPF = false;
      bool QTsokYFNkc = false;
      bool DMGYHfdyOB = false;
      bool FzSojYbCxB = false;
      bool qVMEiTQLwm = false;
      bool SGxtYIxhix = false;
      bool IUcOAQAEFL = false;
      bool wDQilhzCon = false;
      bool ORCbhyCYQb = false;
      bool asTzsVryES = false;
      bool SMGjpPoNHq = false;
      string eYUlTxgTre;
      string wMnhYKMKWa;
      string RTbmYydYAZ;
      string cflFyWCSiF;
      string YDLQGEhscg;
      string MHFOrKxgNU;
      string THTRBPaijB;
      string ItbQBNIKgT;
      string QjuSMVaXMm;
      string ZUFOlQjsPp;
      string dzJaXSfnMe;
      string ClAtEjLBFf;
      string oCVwbnoNek;
      string dPupoRZUts;
      string omKhkmTLJB;
      string EimjBacNzj;
      string dSIbBlqJEl;
      string JqGLpCrnKo;
      string UcDdgtbLoO;
      string nMVKPWdify;
      if(eYUlTxgTre == dzJaXSfnMe){wJGWrMbbsy = true;}
      else if(dzJaXSfnMe == eYUlTxgTre){QTsokYFNkc = true;}
      if(wMnhYKMKWa == ClAtEjLBFf){ioCKPAOetG = true;}
      else if(ClAtEjLBFf == wMnhYKMKWa){DMGYHfdyOB = true;}
      if(RTbmYydYAZ == oCVwbnoNek){KeToyxVwwS = true;}
      else if(oCVwbnoNek == RTbmYydYAZ){FzSojYbCxB = true;}
      if(cflFyWCSiF == dPupoRZUts){XIHLrKVfkT = true;}
      else if(dPupoRZUts == cflFyWCSiF){qVMEiTQLwm = true;}
      if(YDLQGEhscg == omKhkmTLJB){SzRqeyKLtO = true;}
      else if(omKhkmTLJB == YDLQGEhscg){SGxtYIxhix = true;}
      if(MHFOrKxgNU == EimjBacNzj){HznYnQoRYt = true;}
      else if(EimjBacNzj == MHFOrKxgNU){IUcOAQAEFL = true;}
      if(THTRBPaijB == dSIbBlqJEl){pffZaZhpRE = true;}
      else if(dSIbBlqJEl == THTRBPaijB){wDQilhzCon = true;}
      if(ItbQBNIKgT == JqGLpCrnKo){disZnKNcKA = true;}
      if(QjuSMVaXMm == UcDdgtbLoO){mKBgLYUhXb = true;}
      if(ZUFOlQjsPp == nMVKPWdify){UEHqclTrPF = true;}
      while(JqGLpCrnKo == ItbQBNIKgT){ORCbhyCYQb = true;}
      while(UcDdgtbLoO == UcDdgtbLoO){asTzsVryES = true;}
      while(nMVKPWdify == nMVKPWdify){SMGjpPoNHq = true;}
      if(wJGWrMbbsy == true){wJGWrMbbsy = false;}
      if(ioCKPAOetG == true){ioCKPAOetG = false;}
      if(KeToyxVwwS == true){KeToyxVwwS = false;}
      if(XIHLrKVfkT == true){XIHLrKVfkT = false;}
      if(SzRqeyKLtO == true){SzRqeyKLtO = false;}
      if(HznYnQoRYt == true){HznYnQoRYt = false;}
      if(pffZaZhpRE == true){pffZaZhpRE = false;}
      if(disZnKNcKA == true){disZnKNcKA = false;}
      if(mKBgLYUhXb == true){mKBgLYUhXb = false;}
      if(UEHqclTrPF == true){UEHqclTrPF = false;}
      if(QTsokYFNkc == true){QTsokYFNkc = false;}
      if(DMGYHfdyOB == true){DMGYHfdyOB = false;}
      if(FzSojYbCxB == true){FzSojYbCxB = false;}
      if(qVMEiTQLwm == true){qVMEiTQLwm = false;}
      if(SGxtYIxhix == true){SGxtYIxhix = false;}
      if(IUcOAQAEFL == true){IUcOAQAEFL = false;}
      if(wDQilhzCon == true){wDQilhzCon = false;}
      if(ORCbhyCYQb == true){ORCbhyCYQb = false;}
      if(asTzsVryES == true){asTzsVryES = false;}
      if(SMGjpPoNHq == true){SMGjpPoNHq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UJQPPPOXZV
{ 
  void VrziFFhNxr()
  { 
      bool OHlQecoUFp = false;
      bool HpxVuEQzVB = false;
      bool VlmeELHuUd = false;
      bool soSHkeffJh = false;
      bool dKBYAZlZEd = false;
      bool madQCcTGLT = false;
      bool UtAaxRWokP = false;
      bool XkomXKkOee = false;
      bool ZhqpqRLCFH = false;
      bool KYTpMjKZbh = false;
      bool CwonFCkprq = false;
      bool rEbgtmDJje = false;
      bool FUicFyRzan = false;
      bool AKmxbcsCjo = false;
      bool gVJOPFxlwZ = false;
      bool fBpwbgNMhH = false;
      bool kkOEqgRdER = false;
      bool tAYuxjLUMz = false;
      bool BeDBHyUpUt = false;
      bool OfTcEuGEWh = false;
      string EJNRUStCaE;
      string dweUWKfeeO;
      string IGlTIURcSt;
      string pXXxfSdYyh;
      string TtQCAofWgJ;
      string XbCSlxXtJA;
      string BQjgNGYhnD;
      string fHfwtNoiST;
      string ntuJVNVEKh;
      string ujPxgCKjnt;
      string PxidcPwFYX;
      string InapLGVaKA;
      string jUWFHurhPr;
      string DFuYDqLRfG;
      string RQflZHJYlZ;
      string gjYnJuacVg;
      string XNofUCrCmU;
      string tDtDhTnjfA;
      string lSwoKTfGOH;
      string PiuziEazRX;
      if(EJNRUStCaE == PxidcPwFYX){OHlQecoUFp = true;}
      else if(PxidcPwFYX == EJNRUStCaE){CwonFCkprq = true;}
      if(dweUWKfeeO == InapLGVaKA){HpxVuEQzVB = true;}
      else if(InapLGVaKA == dweUWKfeeO){rEbgtmDJje = true;}
      if(IGlTIURcSt == jUWFHurhPr){VlmeELHuUd = true;}
      else if(jUWFHurhPr == IGlTIURcSt){FUicFyRzan = true;}
      if(pXXxfSdYyh == DFuYDqLRfG){soSHkeffJh = true;}
      else if(DFuYDqLRfG == pXXxfSdYyh){AKmxbcsCjo = true;}
      if(TtQCAofWgJ == RQflZHJYlZ){dKBYAZlZEd = true;}
      else if(RQflZHJYlZ == TtQCAofWgJ){gVJOPFxlwZ = true;}
      if(XbCSlxXtJA == gjYnJuacVg){madQCcTGLT = true;}
      else if(gjYnJuacVg == XbCSlxXtJA){fBpwbgNMhH = true;}
      if(BQjgNGYhnD == XNofUCrCmU){UtAaxRWokP = true;}
      else if(XNofUCrCmU == BQjgNGYhnD){kkOEqgRdER = true;}
      if(fHfwtNoiST == tDtDhTnjfA){XkomXKkOee = true;}
      if(ntuJVNVEKh == lSwoKTfGOH){ZhqpqRLCFH = true;}
      if(ujPxgCKjnt == PiuziEazRX){KYTpMjKZbh = true;}
      while(tDtDhTnjfA == fHfwtNoiST){tAYuxjLUMz = true;}
      while(lSwoKTfGOH == lSwoKTfGOH){BeDBHyUpUt = true;}
      while(PiuziEazRX == PiuziEazRX){OfTcEuGEWh = true;}
      if(OHlQecoUFp == true){OHlQecoUFp = false;}
      if(HpxVuEQzVB == true){HpxVuEQzVB = false;}
      if(VlmeELHuUd == true){VlmeELHuUd = false;}
      if(soSHkeffJh == true){soSHkeffJh = false;}
      if(dKBYAZlZEd == true){dKBYAZlZEd = false;}
      if(madQCcTGLT == true){madQCcTGLT = false;}
      if(UtAaxRWokP == true){UtAaxRWokP = false;}
      if(XkomXKkOee == true){XkomXKkOee = false;}
      if(ZhqpqRLCFH == true){ZhqpqRLCFH = false;}
      if(KYTpMjKZbh == true){KYTpMjKZbh = false;}
      if(CwonFCkprq == true){CwonFCkprq = false;}
      if(rEbgtmDJje == true){rEbgtmDJje = false;}
      if(FUicFyRzan == true){FUicFyRzan = false;}
      if(AKmxbcsCjo == true){AKmxbcsCjo = false;}
      if(gVJOPFxlwZ == true){gVJOPFxlwZ = false;}
      if(fBpwbgNMhH == true){fBpwbgNMhH = false;}
      if(kkOEqgRdER == true){kkOEqgRdER = false;}
      if(tAYuxjLUMz == true){tAYuxjLUMz = false;}
      if(BeDBHyUpUt == true){BeDBHyUpUt = false;}
      if(OfTcEuGEWh == true){OfTcEuGEWh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PADZICEZDS
{ 
  void iTaTkkzkJT()
  { 
      bool yxlTgzcUjb = false;
      bool xqdYGPLVIO = false;
      bool DPrfXZyahe = false;
      bool DejNUJOyba = false;
      bool dRSQbGAOXM = false;
      bool BybkDhFFwG = false;
      bool BClFXSHPEw = false;
      bool ANshklxaEQ = false;
      bool ZjCVcFCzKl = false;
      bool EIBVYbeNrJ = false;
      bool zjJaLmEtzR = false;
      bool kdBffQzPbS = false;
      bool PHFRqqMXIJ = false;
      bool GjitQoZbJo = false;
      bool AIzsBaHVoI = false;
      bool bPkYsqeqjU = false;
      bool aglpKAuGOp = false;
      bool qXFmSHHLQQ = false;
      bool jphAgqyJBY = false;
      bool KhqoNSWJhA = false;
      string rMOIeNPuwd;
      string HVygGBwiRu;
      string okVZdbhnCq;
      string NNXKKFAQoA;
      string fWldNtUmdF;
      string ohpKcGpndC;
      string ebrEQsxmVA;
      string BftQPSzrLj;
      string HuJwBfXNgE;
      string PLllVDdgNU;
      string wgQdEJmYtK;
      string HxctujRwCk;
      string ViGRkpsItL;
      string nReqmZdfrr;
      string ryTVwRhrpl;
      string kgebyNazrN;
      string QddhVpSkGV;
      string FlEKrWPjUT;
      string HASIZGlCrZ;
      string yemdbNTkzG;
      if(rMOIeNPuwd == wgQdEJmYtK){yxlTgzcUjb = true;}
      else if(wgQdEJmYtK == rMOIeNPuwd){zjJaLmEtzR = true;}
      if(HVygGBwiRu == HxctujRwCk){xqdYGPLVIO = true;}
      else if(HxctujRwCk == HVygGBwiRu){kdBffQzPbS = true;}
      if(okVZdbhnCq == ViGRkpsItL){DPrfXZyahe = true;}
      else if(ViGRkpsItL == okVZdbhnCq){PHFRqqMXIJ = true;}
      if(NNXKKFAQoA == nReqmZdfrr){DejNUJOyba = true;}
      else if(nReqmZdfrr == NNXKKFAQoA){GjitQoZbJo = true;}
      if(fWldNtUmdF == ryTVwRhrpl){dRSQbGAOXM = true;}
      else if(ryTVwRhrpl == fWldNtUmdF){AIzsBaHVoI = true;}
      if(ohpKcGpndC == kgebyNazrN){BybkDhFFwG = true;}
      else if(kgebyNazrN == ohpKcGpndC){bPkYsqeqjU = true;}
      if(ebrEQsxmVA == QddhVpSkGV){BClFXSHPEw = true;}
      else if(QddhVpSkGV == ebrEQsxmVA){aglpKAuGOp = true;}
      if(BftQPSzrLj == FlEKrWPjUT){ANshklxaEQ = true;}
      if(HuJwBfXNgE == HASIZGlCrZ){ZjCVcFCzKl = true;}
      if(PLllVDdgNU == yemdbNTkzG){EIBVYbeNrJ = true;}
      while(FlEKrWPjUT == BftQPSzrLj){qXFmSHHLQQ = true;}
      while(HASIZGlCrZ == HASIZGlCrZ){jphAgqyJBY = true;}
      while(yemdbNTkzG == yemdbNTkzG){KhqoNSWJhA = true;}
      if(yxlTgzcUjb == true){yxlTgzcUjb = false;}
      if(xqdYGPLVIO == true){xqdYGPLVIO = false;}
      if(DPrfXZyahe == true){DPrfXZyahe = false;}
      if(DejNUJOyba == true){DejNUJOyba = false;}
      if(dRSQbGAOXM == true){dRSQbGAOXM = false;}
      if(BybkDhFFwG == true){BybkDhFFwG = false;}
      if(BClFXSHPEw == true){BClFXSHPEw = false;}
      if(ANshklxaEQ == true){ANshklxaEQ = false;}
      if(ZjCVcFCzKl == true){ZjCVcFCzKl = false;}
      if(EIBVYbeNrJ == true){EIBVYbeNrJ = false;}
      if(zjJaLmEtzR == true){zjJaLmEtzR = false;}
      if(kdBffQzPbS == true){kdBffQzPbS = false;}
      if(PHFRqqMXIJ == true){PHFRqqMXIJ = false;}
      if(GjitQoZbJo == true){GjitQoZbJo = false;}
      if(AIzsBaHVoI == true){AIzsBaHVoI = false;}
      if(bPkYsqeqjU == true){bPkYsqeqjU = false;}
      if(aglpKAuGOp == true){aglpKAuGOp = false;}
      if(qXFmSHHLQQ == true){qXFmSHHLQQ = false;}
      if(jphAgqyJBY == true){jphAgqyJBY = false;}
      if(KhqoNSWJhA == true){KhqoNSWJhA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DRSHNJMHTN
{ 
  void uePLmffEzH()
  { 
      bool KtiXoDTZHl = false;
      bool gIizoyJIMZ = false;
      bool VzHoMgAgiQ = false;
      bool EdnOjDULZR = false;
      bool tyZxFlAZzI = false;
      bool IBZVTLmtKH = false;
      bool ClpqhDTUPl = false;
      bool cxhueXZKiZ = false;
      bool fahaHCDStY = false;
      bool QZASOHHiPC = false;
      bool SfJNeKTepw = false;
      bool kbLkbbEPie = false;
      bool AAZpUDxOfW = false;
      bool PptfGAQUux = false;
      bool hXcymnNPpl = false;
      bool DrAjCSGTrb = false;
      bool NEyTfuhedb = false;
      bool LjTkxbXaDg = false;
      bool ohYtTXoKdn = false;
      bool sxbTidZJSq = false;
      string WESPuTLZLT;
      string KcyznhtDCh;
      string WpwEjCdRbj;
      string KltEwEeFQk;
      string PioqVQEeQb;
      string IsLwegINfr;
      string otxaJXhsDi;
      string ComRSnAEiS;
      string yzBAbQayZP;
      string wRYYuUkNhx;
      string hLbgYSGsdp;
      string fEdMtoswyr;
      string wjSmmkQNVx;
      string CmWkkmXTbI;
      string KhTiirmLeG;
      string bnOoBxrntm;
      string CrXgnsgrbH;
      string QYUohOQjEu;
      string yEiPUNXgjm;
      string tjYnGRJmup;
      if(WESPuTLZLT == hLbgYSGsdp){KtiXoDTZHl = true;}
      else if(hLbgYSGsdp == WESPuTLZLT){SfJNeKTepw = true;}
      if(KcyznhtDCh == fEdMtoswyr){gIizoyJIMZ = true;}
      else if(fEdMtoswyr == KcyznhtDCh){kbLkbbEPie = true;}
      if(WpwEjCdRbj == wjSmmkQNVx){VzHoMgAgiQ = true;}
      else if(wjSmmkQNVx == WpwEjCdRbj){AAZpUDxOfW = true;}
      if(KltEwEeFQk == CmWkkmXTbI){EdnOjDULZR = true;}
      else if(CmWkkmXTbI == KltEwEeFQk){PptfGAQUux = true;}
      if(PioqVQEeQb == KhTiirmLeG){tyZxFlAZzI = true;}
      else if(KhTiirmLeG == PioqVQEeQb){hXcymnNPpl = true;}
      if(IsLwegINfr == bnOoBxrntm){IBZVTLmtKH = true;}
      else if(bnOoBxrntm == IsLwegINfr){DrAjCSGTrb = true;}
      if(otxaJXhsDi == CrXgnsgrbH){ClpqhDTUPl = true;}
      else if(CrXgnsgrbH == otxaJXhsDi){NEyTfuhedb = true;}
      if(ComRSnAEiS == QYUohOQjEu){cxhueXZKiZ = true;}
      if(yzBAbQayZP == yEiPUNXgjm){fahaHCDStY = true;}
      if(wRYYuUkNhx == tjYnGRJmup){QZASOHHiPC = true;}
      while(QYUohOQjEu == ComRSnAEiS){LjTkxbXaDg = true;}
      while(yEiPUNXgjm == yEiPUNXgjm){ohYtTXoKdn = true;}
      while(tjYnGRJmup == tjYnGRJmup){sxbTidZJSq = true;}
      if(KtiXoDTZHl == true){KtiXoDTZHl = false;}
      if(gIizoyJIMZ == true){gIizoyJIMZ = false;}
      if(VzHoMgAgiQ == true){VzHoMgAgiQ = false;}
      if(EdnOjDULZR == true){EdnOjDULZR = false;}
      if(tyZxFlAZzI == true){tyZxFlAZzI = false;}
      if(IBZVTLmtKH == true){IBZVTLmtKH = false;}
      if(ClpqhDTUPl == true){ClpqhDTUPl = false;}
      if(cxhueXZKiZ == true){cxhueXZKiZ = false;}
      if(fahaHCDStY == true){fahaHCDStY = false;}
      if(QZASOHHiPC == true){QZASOHHiPC = false;}
      if(SfJNeKTepw == true){SfJNeKTepw = false;}
      if(kbLkbbEPie == true){kbLkbbEPie = false;}
      if(AAZpUDxOfW == true){AAZpUDxOfW = false;}
      if(PptfGAQUux == true){PptfGAQUux = false;}
      if(hXcymnNPpl == true){hXcymnNPpl = false;}
      if(DrAjCSGTrb == true){DrAjCSGTrb = false;}
      if(NEyTfuhedb == true){NEyTfuhedb = false;}
      if(LjTkxbXaDg == true){LjTkxbXaDg = false;}
      if(ohYtTXoKdn == true){ohYtTXoKdn = false;}
      if(sxbTidZJSq == true){sxbTidZJSq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CLDQKQEDLV
{ 
  void brxRzpcwzL()
  { 
      bool xmUCViSDXs = false;
      bool VLlCQMWRkQ = false;
      bool cHRfEykUeE = false;
      bool cHXEKKuyxE = false;
      bool xJkcPYtjxI = false;
      bool ccVfJpUoxX = false;
      bool xxYTQOmgrG = false;
      bool RXTgTSWoQe = false;
      bool EAXVbAkruT = false;
      bool oFAZGzkRMB = false;
      bool lMrqqEIoMq = false;
      bool TfYSSwZCqQ = false;
      bool culXQMXsaT = false;
      bool gFbPsqIgeX = false;
      bool qwfDAIghHJ = false;
      bool ZhZuXqaUZe = false;
      bool fPNrKODJZa = false;
      bool nrXTZgOhWH = false;
      bool eplRsyefqB = false;
      bool QmGzqbhmsl = false;
      string grHTLFrVUG;
      string tlsPqYqsyu;
      string gEDUeHJuoo;
      string sEpOLErOCm;
      string YxiPLbKBSV;
      string IGRpjbomoD;
      string wxgfMpwdDl;
      string fcpKViUmJC;
      string xHcTfllAei;
      string PFZypbQDCU;
      string ffxfofPGTA;
      string HBcmGoUNza;
      string DuzTVZCrUt;
      string SQknVQJwdz;
      string WfgdbOblqB;
      string HCDbRkfdJO;
      string cWkYgpQoQo;
      string eXjADXOUqH;
      string yQATmQNIWk;
      string kflOVztHxl;
      if(grHTLFrVUG == ffxfofPGTA){xmUCViSDXs = true;}
      else if(ffxfofPGTA == grHTLFrVUG){lMrqqEIoMq = true;}
      if(tlsPqYqsyu == HBcmGoUNza){VLlCQMWRkQ = true;}
      else if(HBcmGoUNza == tlsPqYqsyu){TfYSSwZCqQ = true;}
      if(gEDUeHJuoo == DuzTVZCrUt){cHRfEykUeE = true;}
      else if(DuzTVZCrUt == gEDUeHJuoo){culXQMXsaT = true;}
      if(sEpOLErOCm == SQknVQJwdz){cHXEKKuyxE = true;}
      else if(SQknVQJwdz == sEpOLErOCm){gFbPsqIgeX = true;}
      if(YxiPLbKBSV == WfgdbOblqB){xJkcPYtjxI = true;}
      else if(WfgdbOblqB == YxiPLbKBSV){qwfDAIghHJ = true;}
      if(IGRpjbomoD == HCDbRkfdJO){ccVfJpUoxX = true;}
      else if(HCDbRkfdJO == IGRpjbomoD){ZhZuXqaUZe = true;}
      if(wxgfMpwdDl == cWkYgpQoQo){xxYTQOmgrG = true;}
      else if(cWkYgpQoQo == wxgfMpwdDl){fPNrKODJZa = true;}
      if(fcpKViUmJC == eXjADXOUqH){RXTgTSWoQe = true;}
      if(xHcTfllAei == yQATmQNIWk){EAXVbAkruT = true;}
      if(PFZypbQDCU == kflOVztHxl){oFAZGzkRMB = true;}
      while(eXjADXOUqH == fcpKViUmJC){nrXTZgOhWH = true;}
      while(yQATmQNIWk == yQATmQNIWk){eplRsyefqB = true;}
      while(kflOVztHxl == kflOVztHxl){QmGzqbhmsl = true;}
      if(xmUCViSDXs == true){xmUCViSDXs = false;}
      if(VLlCQMWRkQ == true){VLlCQMWRkQ = false;}
      if(cHRfEykUeE == true){cHRfEykUeE = false;}
      if(cHXEKKuyxE == true){cHXEKKuyxE = false;}
      if(xJkcPYtjxI == true){xJkcPYtjxI = false;}
      if(ccVfJpUoxX == true){ccVfJpUoxX = false;}
      if(xxYTQOmgrG == true){xxYTQOmgrG = false;}
      if(RXTgTSWoQe == true){RXTgTSWoQe = false;}
      if(EAXVbAkruT == true){EAXVbAkruT = false;}
      if(oFAZGzkRMB == true){oFAZGzkRMB = false;}
      if(lMrqqEIoMq == true){lMrqqEIoMq = false;}
      if(TfYSSwZCqQ == true){TfYSSwZCqQ = false;}
      if(culXQMXsaT == true){culXQMXsaT = false;}
      if(gFbPsqIgeX == true){gFbPsqIgeX = false;}
      if(qwfDAIghHJ == true){qwfDAIghHJ = false;}
      if(ZhZuXqaUZe == true){ZhZuXqaUZe = false;}
      if(fPNrKODJZa == true){fPNrKODJZa = false;}
      if(nrXTZgOhWH == true){nrXTZgOhWH = false;}
      if(eplRsyefqB == true){eplRsyefqB = false;}
      if(QmGzqbhmsl == true){QmGzqbhmsl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QOVMJWVSAP
{ 
  void hZGDIErghi()
  { 
      bool fecZzezyoU = false;
      bool JlOjFruzXa = false;
      bool HafHBTPhBK = false;
      bool sojKbEqyaa = false;
      bool XWLykXTEHx = false;
      bool QEpKMFzVYe = false;
      bool OQxdbUCDHA = false;
      bool BwYwCkPhWc = false;
      bool ALZDsnyZxV = false;
      bool FVZuLHYgVQ = false;
      bool UPwHwUftHb = false;
      bool pRyueDptjn = false;
      bool VcFkueWcju = false;
      bool LhLGHkOSGY = false;
      bool HERVfmWdQI = false;
      bool QewhtrJKLQ = false;
      bool xDJMPHGrms = false;
      bool oWmLgQKjEH = false;
      bool IrLbdglcLO = false;
      bool bDHobDuFGY = false;
      string SNGQARnzZP;
      string GDjiaJLoUH;
      string SkynltmMpR;
      string FtsfTMgUSL;
      string uEqWHTQmXh;
      string CyLfehPRdF;
      string eaIHJLJEOO;
      string cpVILOtagS;
      string cAoIOHhNAl;
      string xOqNfUuiNu;
      string JLXIEMbDUQ;
      string nnjKbekAsB;
      string cwEcQOzIcp;
      string SKMlIRbfEC;
      string eerixIdfkB;
      string juoLSNHtrp;
      string MSadycbyCK;
      string CEwqWxDUeI;
      string jTXaGWUASu;
      string JhnNpLEOkU;
      if(SNGQARnzZP == JLXIEMbDUQ){fecZzezyoU = true;}
      else if(JLXIEMbDUQ == SNGQARnzZP){UPwHwUftHb = true;}
      if(GDjiaJLoUH == nnjKbekAsB){JlOjFruzXa = true;}
      else if(nnjKbekAsB == GDjiaJLoUH){pRyueDptjn = true;}
      if(SkynltmMpR == cwEcQOzIcp){HafHBTPhBK = true;}
      else if(cwEcQOzIcp == SkynltmMpR){VcFkueWcju = true;}
      if(FtsfTMgUSL == SKMlIRbfEC){sojKbEqyaa = true;}
      else if(SKMlIRbfEC == FtsfTMgUSL){LhLGHkOSGY = true;}
      if(uEqWHTQmXh == eerixIdfkB){XWLykXTEHx = true;}
      else if(eerixIdfkB == uEqWHTQmXh){HERVfmWdQI = true;}
      if(CyLfehPRdF == juoLSNHtrp){QEpKMFzVYe = true;}
      else if(juoLSNHtrp == CyLfehPRdF){QewhtrJKLQ = true;}
      if(eaIHJLJEOO == MSadycbyCK){OQxdbUCDHA = true;}
      else if(MSadycbyCK == eaIHJLJEOO){xDJMPHGrms = true;}
      if(cpVILOtagS == CEwqWxDUeI){BwYwCkPhWc = true;}
      if(cAoIOHhNAl == jTXaGWUASu){ALZDsnyZxV = true;}
      if(xOqNfUuiNu == JhnNpLEOkU){FVZuLHYgVQ = true;}
      while(CEwqWxDUeI == cpVILOtagS){oWmLgQKjEH = true;}
      while(jTXaGWUASu == jTXaGWUASu){IrLbdglcLO = true;}
      while(JhnNpLEOkU == JhnNpLEOkU){bDHobDuFGY = true;}
      if(fecZzezyoU == true){fecZzezyoU = false;}
      if(JlOjFruzXa == true){JlOjFruzXa = false;}
      if(HafHBTPhBK == true){HafHBTPhBK = false;}
      if(sojKbEqyaa == true){sojKbEqyaa = false;}
      if(XWLykXTEHx == true){XWLykXTEHx = false;}
      if(QEpKMFzVYe == true){QEpKMFzVYe = false;}
      if(OQxdbUCDHA == true){OQxdbUCDHA = false;}
      if(BwYwCkPhWc == true){BwYwCkPhWc = false;}
      if(ALZDsnyZxV == true){ALZDsnyZxV = false;}
      if(FVZuLHYgVQ == true){FVZuLHYgVQ = false;}
      if(UPwHwUftHb == true){UPwHwUftHb = false;}
      if(pRyueDptjn == true){pRyueDptjn = false;}
      if(VcFkueWcju == true){VcFkueWcju = false;}
      if(LhLGHkOSGY == true){LhLGHkOSGY = false;}
      if(HERVfmWdQI == true){HERVfmWdQI = false;}
      if(QewhtrJKLQ == true){QewhtrJKLQ = false;}
      if(xDJMPHGrms == true){xDJMPHGrms = false;}
      if(oWmLgQKjEH == true){oWmLgQKjEH = false;}
      if(IrLbdglcLO == true){IrLbdglcLO = false;}
      if(bDHobDuFGY == true){bDHobDuFGY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FETFVVHJMR
{ 
  void mcCDIhzHiL()
  { 
      bool rIwETdAZiz = false;
      bool CtIiIbfEau = false;
      bool lrkNVGAqyx = false;
      bool ZjqcLfeyJQ = false;
      bool uwLwuUCDuX = false;
      bool OFElbzWhhN = false;
      bool dJblYSDfWc = false;
      bool whuJApgoSB = false;
      bool DxwZhUeEBL = false;
      bool IwQwmlTZWb = false;
      bool RVfRagKulk = false;
      bool RhPfJgMBDE = false;
      bool nyeLUzRyWN = false;
      bool VHRpjhRdyA = false;
      bool KjSPsagjmG = false;
      bool YSVSnSqUxa = false;
      bool OLXXOKPYwa = false;
      bool PiCDsEfORs = false;
      bool SgLQoDkzCQ = false;
      bool pwfWkzLtBi = false;
      string ESKPGalFgI;
      string RLsimedmnT;
      string FhpKmhZifr;
      string hFIiuQBLjN;
      string eSOXVmeAqE;
      string DdUWXVbAbY;
      string ADYoZLCKmW;
      string dRDZnmTSnA;
      string DYrbnEkkKY;
      string nAiLMbtYxJ;
      string jTNUZkatik;
      string CILbUbKxBV;
      string aRzNhchrNM;
      string stVePiKXBC;
      string dqCZWeoHpj;
      string QwXaiRTAlx;
      string ChgVrImgLl;
      string QluyrjPZqD;
      string naCcuwVtux;
      string PKlEAuJfhN;
      if(ESKPGalFgI == jTNUZkatik){rIwETdAZiz = true;}
      else if(jTNUZkatik == ESKPGalFgI){RVfRagKulk = true;}
      if(RLsimedmnT == CILbUbKxBV){CtIiIbfEau = true;}
      else if(CILbUbKxBV == RLsimedmnT){RhPfJgMBDE = true;}
      if(FhpKmhZifr == aRzNhchrNM){lrkNVGAqyx = true;}
      else if(aRzNhchrNM == FhpKmhZifr){nyeLUzRyWN = true;}
      if(hFIiuQBLjN == stVePiKXBC){ZjqcLfeyJQ = true;}
      else if(stVePiKXBC == hFIiuQBLjN){VHRpjhRdyA = true;}
      if(eSOXVmeAqE == dqCZWeoHpj){uwLwuUCDuX = true;}
      else if(dqCZWeoHpj == eSOXVmeAqE){KjSPsagjmG = true;}
      if(DdUWXVbAbY == QwXaiRTAlx){OFElbzWhhN = true;}
      else if(QwXaiRTAlx == DdUWXVbAbY){YSVSnSqUxa = true;}
      if(ADYoZLCKmW == ChgVrImgLl){dJblYSDfWc = true;}
      else if(ChgVrImgLl == ADYoZLCKmW){OLXXOKPYwa = true;}
      if(dRDZnmTSnA == QluyrjPZqD){whuJApgoSB = true;}
      if(DYrbnEkkKY == naCcuwVtux){DxwZhUeEBL = true;}
      if(nAiLMbtYxJ == PKlEAuJfhN){IwQwmlTZWb = true;}
      while(QluyrjPZqD == dRDZnmTSnA){PiCDsEfORs = true;}
      while(naCcuwVtux == naCcuwVtux){SgLQoDkzCQ = true;}
      while(PKlEAuJfhN == PKlEAuJfhN){pwfWkzLtBi = true;}
      if(rIwETdAZiz == true){rIwETdAZiz = false;}
      if(CtIiIbfEau == true){CtIiIbfEau = false;}
      if(lrkNVGAqyx == true){lrkNVGAqyx = false;}
      if(ZjqcLfeyJQ == true){ZjqcLfeyJQ = false;}
      if(uwLwuUCDuX == true){uwLwuUCDuX = false;}
      if(OFElbzWhhN == true){OFElbzWhhN = false;}
      if(dJblYSDfWc == true){dJblYSDfWc = false;}
      if(whuJApgoSB == true){whuJApgoSB = false;}
      if(DxwZhUeEBL == true){DxwZhUeEBL = false;}
      if(IwQwmlTZWb == true){IwQwmlTZWb = false;}
      if(RVfRagKulk == true){RVfRagKulk = false;}
      if(RhPfJgMBDE == true){RhPfJgMBDE = false;}
      if(nyeLUzRyWN == true){nyeLUzRyWN = false;}
      if(VHRpjhRdyA == true){VHRpjhRdyA = false;}
      if(KjSPsagjmG == true){KjSPsagjmG = false;}
      if(YSVSnSqUxa == true){YSVSnSqUxa = false;}
      if(OLXXOKPYwa == true){OLXXOKPYwa = false;}
      if(PiCDsEfORs == true){PiCDsEfORs = false;}
      if(SgLQoDkzCQ == true){SgLQoDkzCQ = false;}
      if(pwfWkzLtBi == true){pwfWkzLtBi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TVOXSXSBGU
{ 
  void nUTpxKmKhi()
  { 
      bool XUGsLjkpff = false;
      bool iuAZtrCrcf = false;
      bool ZEZopLTieq = false;
      bool fnkBVjBlmI = false;
      bool MktJgHsjgZ = false;
      bool dYXEdTtQDA = false;
      bool PBKnztJzDK = false;
      bool qQFUSnJQIi = false;
      bool RjCFMHPgWC = false;
      bool ojhmrLaGJl = false;
      bool xsfViNSCkp = false;
      bool JdIUhfyFar = false;
      bool ebcBVGhSbH = false;
      bool NDGVkXEfVz = false;
      bool nMugrKbNEM = false;
      bool MUeQHVQdAb = false;
      bool eAacbGWljJ = false;
      bool aSibERgwJK = false;
      bool eUNPusYpOP = false;
      bool HaetUmlREk = false;
      string KqykdCSFfg;
      string pOFuzHwxqw;
      string IYMNTuZRGe;
      string eQDiKpCWgB;
      string UgFrJwYFYr;
      string sPyDxkdkRi;
      string bAzBBYLVkI;
      string EYPpaaTUDX;
      string WUsNlORzkY;
      string LQFyYUhDpj;
      string jCTPmTzIbW;
      string RJhsMHGlPm;
      string GMkMwnTRQG;
      string sPdSmTBcaR;
      string OJWOGCiLlR;
      string NunDdXRGTz;
      string zhrVcCeOFr;
      string FdKxXxoWFs;
      string EHfzrxbaoP;
      string CtJbRgRBkE;
      if(KqykdCSFfg == jCTPmTzIbW){XUGsLjkpff = true;}
      else if(jCTPmTzIbW == KqykdCSFfg){xsfViNSCkp = true;}
      if(pOFuzHwxqw == RJhsMHGlPm){iuAZtrCrcf = true;}
      else if(RJhsMHGlPm == pOFuzHwxqw){JdIUhfyFar = true;}
      if(IYMNTuZRGe == GMkMwnTRQG){ZEZopLTieq = true;}
      else if(GMkMwnTRQG == IYMNTuZRGe){ebcBVGhSbH = true;}
      if(eQDiKpCWgB == sPdSmTBcaR){fnkBVjBlmI = true;}
      else if(sPdSmTBcaR == eQDiKpCWgB){NDGVkXEfVz = true;}
      if(UgFrJwYFYr == OJWOGCiLlR){MktJgHsjgZ = true;}
      else if(OJWOGCiLlR == UgFrJwYFYr){nMugrKbNEM = true;}
      if(sPyDxkdkRi == NunDdXRGTz){dYXEdTtQDA = true;}
      else if(NunDdXRGTz == sPyDxkdkRi){MUeQHVQdAb = true;}
      if(bAzBBYLVkI == zhrVcCeOFr){PBKnztJzDK = true;}
      else if(zhrVcCeOFr == bAzBBYLVkI){eAacbGWljJ = true;}
      if(EYPpaaTUDX == FdKxXxoWFs){qQFUSnJQIi = true;}
      if(WUsNlORzkY == EHfzrxbaoP){RjCFMHPgWC = true;}
      if(LQFyYUhDpj == CtJbRgRBkE){ojhmrLaGJl = true;}
      while(FdKxXxoWFs == EYPpaaTUDX){aSibERgwJK = true;}
      while(EHfzrxbaoP == EHfzrxbaoP){eUNPusYpOP = true;}
      while(CtJbRgRBkE == CtJbRgRBkE){HaetUmlREk = true;}
      if(XUGsLjkpff == true){XUGsLjkpff = false;}
      if(iuAZtrCrcf == true){iuAZtrCrcf = false;}
      if(ZEZopLTieq == true){ZEZopLTieq = false;}
      if(fnkBVjBlmI == true){fnkBVjBlmI = false;}
      if(MktJgHsjgZ == true){MktJgHsjgZ = false;}
      if(dYXEdTtQDA == true){dYXEdTtQDA = false;}
      if(PBKnztJzDK == true){PBKnztJzDK = false;}
      if(qQFUSnJQIi == true){qQFUSnJQIi = false;}
      if(RjCFMHPgWC == true){RjCFMHPgWC = false;}
      if(ojhmrLaGJl == true){ojhmrLaGJl = false;}
      if(xsfViNSCkp == true){xsfViNSCkp = false;}
      if(JdIUhfyFar == true){JdIUhfyFar = false;}
      if(ebcBVGhSbH == true){ebcBVGhSbH = false;}
      if(NDGVkXEfVz == true){NDGVkXEfVz = false;}
      if(nMugrKbNEM == true){nMugrKbNEM = false;}
      if(MUeQHVQdAb == true){MUeQHVQdAb = false;}
      if(eAacbGWljJ == true){eAacbGWljJ = false;}
      if(aSibERgwJK == true){aSibERgwJK = false;}
      if(eUNPusYpOP == true){eUNPusYpOP = false;}
      if(HaetUmlREk == true){HaetUmlREk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WGCJOOPDPI
{ 
  void qoJTdUWsQr()
  { 
      bool RBMQfBLmDo = false;
      bool AQepkMZzEl = false;
      bool OGDMWExRoe = false;
      bool WJRAAlhjdI = false;
      bool xKUHZpGmwi = false;
      bool fDOyJLxzsa = false;
      bool EsxXSqzdoy = false;
      bool eoVuoDlumg = false;
      bool yJUFzTtTqn = false;
      bool ohpDEDMwoh = false;
      bool qbxyEpgSIF = false;
      bool ZBMMctXrYy = false;
      bool welBIxzSqk = false;
      bool qoGEoVMWBI = false;
      bool lbKlOmUcZK = false;
      bool eUWpkLpwoG = false;
      bool qOaXOjuHWG = false;
      bool gBpQMUUAmV = false;
      bool cVrgGVSPTd = false;
      bool fQgtQWBmWd = false;
      string PwlrqQDNpl;
      string MqSMxyIgGf;
      string YwoIMHmint;
      string TWDqlusWjc;
      string HpKXsYdmZT;
      string nRTXxTHcei;
      string dUZwSpnbaC;
      string FlwdXikRPn;
      string dAIUFBCesS;
      string mPqAymPOEC;
      string kCLXOBVozN;
      string hpNqFdLFpQ;
      string mIhIOotuek;
      string SWMMDankGD;
      string fMfejwBAuU;
      string bKYnPcTDIY;
      string HZJNtLdAmd;
      string oZzlkZbCYS;
      string mtAJJIxXxa;
      string HkcgwFDSjX;
      if(PwlrqQDNpl == kCLXOBVozN){RBMQfBLmDo = true;}
      else if(kCLXOBVozN == PwlrqQDNpl){qbxyEpgSIF = true;}
      if(MqSMxyIgGf == hpNqFdLFpQ){AQepkMZzEl = true;}
      else if(hpNqFdLFpQ == MqSMxyIgGf){ZBMMctXrYy = true;}
      if(YwoIMHmint == mIhIOotuek){OGDMWExRoe = true;}
      else if(mIhIOotuek == YwoIMHmint){welBIxzSqk = true;}
      if(TWDqlusWjc == SWMMDankGD){WJRAAlhjdI = true;}
      else if(SWMMDankGD == TWDqlusWjc){qoGEoVMWBI = true;}
      if(HpKXsYdmZT == fMfejwBAuU){xKUHZpGmwi = true;}
      else if(fMfejwBAuU == HpKXsYdmZT){lbKlOmUcZK = true;}
      if(nRTXxTHcei == bKYnPcTDIY){fDOyJLxzsa = true;}
      else if(bKYnPcTDIY == nRTXxTHcei){eUWpkLpwoG = true;}
      if(dUZwSpnbaC == HZJNtLdAmd){EsxXSqzdoy = true;}
      else if(HZJNtLdAmd == dUZwSpnbaC){qOaXOjuHWG = true;}
      if(FlwdXikRPn == oZzlkZbCYS){eoVuoDlumg = true;}
      if(dAIUFBCesS == mtAJJIxXxa){yJUFzTtTqn = true;}
      if(mPqAymPOEC == HkcgwFDSjX){ohpDEDMwoh = true;}
      while(oZzlkZbCYS == FlwdXikRPn){gBpQMUUAmV = true;}
      while(mtAJJIxXxa == mtAJJIxXxa){cVrgGVSPTd = true;}
      while(HkcgwFDSjX == HkcgwFDSjX){fQgtQWBmWd = true;}
      if(RBMQfBLmDo == true){RBMQfBLmDo = false;}
      if(AQepkMZzEl == true){AQepkMZzEl = false;}
      if(OGDMWExRoe == true){OGDMWExRoe = false;}
      if(WJRAAlhjdI == true){WJRAAlhjdI = false;}
      if(xKUHZpGmwi == true){xKUHZpGmwi = false;}
      if(fDOyJLxzsa == true){fDOyJLxzsa = false;}
      if(EsxXSqzdoy == true){EsxXSqzdoy = false;}
      if(eoVuoDlumg == true){eoVuoDlumg = false;}
      if(yJUFzTtTqn == true){yJUFzTtTqn = false;}
      if(ohpDEDMwoh == true){ohpDEDMwoh = false;}
      if(qbxyEpgSIF == true){qbxyEpgSIF = false;}
      if(ZBMMctXrYy == true){ZBMMctXrYy = false;}
      if(welBIxzSqk == true){welBIxzSqk = false;}
      if(qoGEoVMWBI == true){qoGEoVMWBI = false;}
      if(lbKlOmUcZK == true){lbKlOmUcZK = false;}
      if(eUWpkLpwoG == true){eUWpkLpwoG = false;}
      if(qOaXOjuHWG == true){qOaXOjuHWG = false;}
      if(gBpQMUUAmV == true){gBpQMUUAmV = false;}
      if(cVrgGVSPTd == true){cVrgGVSPTd = false;}
      if(fQgtQWBmWd == true){fQgtQWBmWd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PTKICWXQPM
{ 
  void KIZJNTSTrB()
  { 
      bool IUdbeCmJdQ = false;
      bool ZiBUbJbyqU = false;
      bool CUnlCLfCUu = false;
      bool tnKFUFHBpb = false;
      bool UAAdxwAAZa = false;
      bool ghlzSngqZS = false;
      bool VkniVkXwAV = false;
      bool CZIOACTJnF = false;
      bool LfctNMCLlg = false;
      bool YPbWFiMRIL = false;
      bool XDADYHZWzP = false;
      bool TWDTHpIsVI = false;
      bool iMJTxlxkJQ = false;
      bool pCBcgHeYVG = false;
      bool meLWMBMHPP = false;
      bool aSwzbLtgFm = false;
      bool JnNhYRVZlz = false;
      bool KiXPUDAlGw = false;
      bool YoUsoXGBAV = false;
      bool NySiwzRcxu = false;
      string kUMtwjcMyB;
      string dpEMKCpYoN;
      string oVqlzhdAUI;
      string aRUAiAzFzp;
      string CqsbfcuOuj;
      string FShPaOcatN;
      string FbroaLUDdJ;
      string CjYzKycOFW;
      string lOFkCHjEZU;
      string WXLkjayDBT;
      string HrkkgUsiFb;
      string lNUXbqVHmS;
      string bQcIldYmOi;
      string zZNlOtdTDg;
      string OAzxhJDmJs;
      string EqPhqqObyC;
      string wFUVcMAhJh;
      string NCDGEaRfac;
      string aldVeHJetW;
      string eBVBkIfcUV;
      if(kUMtwjcMyB == HrkkgUsiFb){IUdbeCmJdQ = true;}
      else if(HrkkgUsiFb == kUMtwjcMyB){XDADYHZWzP = true;}
      if(dpEMKCpYoN == lNUXbqVHmS){ZiBUbJbyqU = true;}
      else if(lNUXbqVHmS == dpEMKCpYoN){TWDTHpIsVI = true;}
      if(oVqlzhdAUI == bQcIldYmOi){CUnlCLfCUu = true;}
      else if(bQcIldYmOi == oVqlzhdAUI){iMJTxlxkJQ = true;}
      if(aRUAiAzFzp == zZNlOtdTDg){tnKFUFHBpb = true;}
      else if(zZNlOtdTDg == aRUAiAzFzp){pCBcgHeYVG = true;}
      if(CqsbfcuOuj == OAzxhJDmJs){UAAdxwAAZa = true;}
      else if(OAzxhJDmJs == CqsbfcuOuj){meLWMBMHPP = true;}
      if(FShPaOcatN == EqPhqqObyC){ghlzSngqZS = true;}
      else if(EqPhqqObyC == FShPaOcatN){aSwzbLtgFm = true;}
      if(FbroaLUDdJ == wFUVcMAhJh){VkniVkXwAV = true;}
      else if(wFUVcMAhJh == FbroaLUDdJ){JnNhYRVZlz = true;}
      if(CjYzKycOFW == NCDGEaRfac){CZIOACTJnF = true;}
      if(lOFkCHjEZU == aldVeHJetW){LfctNMCLlg = true;}
      if(WXLkjayDBT == eBVBkIfcUV){YPbWFiMRIL = true;}
      while(NCDGEaRfac == CjYzKycOFW){KiXPUDAlGw = true;}
      while(aldVeHJetW == aldVeHJetW){YoUsoXGBAV = true;}
      while(eBVBkIfcUV == eBVBkIfcUV){NySiwzRcxu = true;}
      if(IUdbeCmJdQ == true){IUdbeCmJdQ = false;}
      if(ZiBUbJbyqU == true){ZiBUbJbyqU = false;}
      if(CUnlCLfCUu == true){CUnlCLfCUu = false;}
      if(tnKFUFHBpb == true){tnKFUFHBpb = false;}
      if(UAAdxwAAZa == true){UAAdxwAAZa = false;}
      if(ghlzSngqZS == true){ghlzSngqZS = false;}
      if(VkniVkXwAV == true){VkniVkXwAV = false;}
      if(CZIOACTJnF == true){CZIOACTJnF = false;}
      if(LfctNMCLlg == true){LfctNMCLlg = false;}
      if(YPbWFiMRIL == true){YPbWFiMRIL = false;}
      if(XDADYHZWzP == true){XDADYHZWzP = false;}
      if(TWDTHpIsVI == true){TWDTHpIsVI = false;}
      if(iMJTxlxkJQ == true){iMJTxlxkJQ = false;}
      if(pCBcgHeYVG == true){pCBcgHeYVG = false;}
      if(meLWMBMHPP == true){meLWMBMHPP = false;}
      if(aSwzbLtgFm == true){aSwzbLtgFm = false;}
      if(JnNhYRVZlz == true){JnNhYRVZlz = false;}
      if(KiXPUDAlGw == true){KiXPUDAlGw = false;}
      if(YoUsoXGBAV == true){YoUsoXGBAV = false;}
      if(NySiwzRcxu == true){NySiwzRcxu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KIVDCHEXYI
{ 
  void tJjdwpdacR()
  { 
      bool DhTdUrGFnU = false;
      bool VYrPIFbQZb = false;
      bool PbOuEWbPYq = false;
      bool sZTyRhDpHL = false;
      bool unMUlyRVgb = false;
      bool VUrSLbSXZy = false;
      bool QqgxawFtxZ = false;
      bool ClJOfbOtIF = false;
      bool FFiwUXgAlo = false;
      bool PeQJtDHPsp = false;
      bool rXXGZjLdlj = false;
      bool NXPTrKHjbD = false;
      bool OFHHKWUzTc = false;
      bool TyBRNhgbWk = false;
      bool LDNCbqPxQj = false;
      bool wWmoblPQwD = false;
      bool OMKJPOWxFK = false;
      bool dfNqrLrFfS = false;
      bool GXhjgxLMoa = false;
      bool RQeSVzrDmM = false;
      string VOgAiJmKGM;
      string AurOnKtnZm;
      string aTKkAJsrCD;
      string KeXrDtbzSd;
      string llhQiZYngL;
      string TrVneBDuAY;
      string PuICCVXzLs;
      string itUuAoltCZ;
      string kFKpjRIiNB;
      string pfytOqceON;
      string CZbnbYWamo;
      string PJsanKkRSj;
      string MnlKCDuagJ;
      string MGfoWLcWNL;
      string tguXkglXGD;
      string GKMdAOmRkY;
      string cwtccJcEDb;
      string hNEGofrNYV;
      string QXTcDBtBoI;
      string XKlohylSta;
      if(VOgAiJmKGM == CZbnbYWamo){DhTdUrGFnU = true;}
      else if(CZbnbYWamo == VOgAiJmKGM){rXXGZjLdlj = true;}
      if(AurOnKtnZm == PJsanKkRSj){VYrPIFbQZb = true;}
      else if(PJsanKkRSj == AurOnKtnZm){NXPTrKHjbD = true;}
      if(aTKkAJsrCD == MnlKCDuagJ){PbOuEWbPYq = true;}
      else if(MnlKCDuagJ == aTKkAJsrCD){OFHHKWUzTc = true;}
      if(KeXrDtbzSd == MGfoWLcWNL){sZTyRhDpHL = true;}
      else if(MGfoWLcWNL == KeXrDtbzSd){TyBRNhgbWk = true;}
      if(llhQiZYngL == tguXkglXGD){unMUlyRVgb = true;}
      else if(tguXkglXGD == llhQiZYngL){LDNCbqPxQj = true;}
      if(TrVneBDuAY == GKMdAOmRkY){VUrSLbSXZy = true;}
      else if(GKMdAOmRkY == TrVneBDuAY){wWmoblPQwD = true;}
      if(PuICCVXzLs == cwtccJcEDb){QqgxawFtxZ = true;}
      else if(cwtccJcEDb == PuICCVXzLs){OMKJPOWxFK = true;}
      if(itUuAoltCZ == hNEGofrNYV){ClJOfbOtIF = true;}
      if(kFKpjRIiNB == QXTcDBtBoI){FFiwUXgAlo = true;}
      if(pfytOqceON == XKlohylSta){PeQJtDHPsp = true;}
      while(hNEGofrNYV == itUuAoltCZ){dfNqrLrFfS = true;}
      while(QXTcDBtBoI == QXTcDBtBoI){GXhjgxLMoa = true;}
      while(XKlohylSta == XKlohylSta){RQeSVzrDmM = true;}
      if(DhTdUrGFnU == true){DhTdUrGFnU = false;}
      if(VYrPIFbQZb == true){VYrPIFbQZb = false;}
      if(PbOuEWbPYq == true){PbOuEWbPYq = false;}
      if(sZTyRhDpHL == true){sZTyRhDpHL = false;}
      if(unMUlyRVgb == true){unMUlyRVgb = false;}
      if(VUrSLbSXZy == true){VUrSLbSXZy = false;}
      if(QqgxawFtxZ == true){QqgxawFtxZ = false;}
      if(ClJOfbOtIF == true){ClJOfbOtIF = false;}
      if(FFiwUXgAlo == true){FFiwUXgAlo = false;}
      if(PeQJtDHPsp == true){PeQJtDHPsp = false;}
      if(rXXGZjLdlj == true){rXXGZjLdlj = false;}
      if(NXPTrKHjbD == true){NXPTrKHjbD = false;}
      if(OFHHKWUzTc == true){OFHHKWUzTc = false;}
      if(TyBRNhgbWk == true){TyBRNhgbWk = false;}
      if(LDNCbqPxQj == true){LDNCbqPxQj = false;}
      if(wWmoblPQwD == true){wWmoblPQwD = false;}
      if(OMKJPOWxFK == true){OMKJPOWxFK = false;}
      if(dfNqrLrFfS == true){dfNqrLrFfS = false;}
      if(GXhjgxLMoa == true){GXhjgxLMoa = false;}
      if(RQeSVzrDmM == true){RQeSVzrDmM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NHNFYHMRSH
{ 
  void lCSjXarseB()
  { 
      bool kelkJYrolX = false;
      bool jbKzjXaqiJ = false;
      bool fMFMfCRNKO = false;
      bool PtPwrEnMJU = false;
      bool zFyTGHzocD = false;
      bool ajexSYZZEH = false;
      bool HedXHoMOGf = false;
      bool iOgOKZOkFY = false;
      bool CcjHmfOSdT = false;
      bool dOHCMTbaLQ = false;
      bool ukhxTLDPmr = false;
      bool JnTfEeuVjb = false;
      bool ZtjlBUGdCp = false;
      bool ynYndRtlnb = false;
      bool czekKotbyh = false;
      bool YGqjpABuwy = false;
      bool FYNwtVPeBm = false;
      bool jIhHyaOybL = false;
      bool aefTRrwnyc = false;
      bool PzpoWDkiqn = false;
      string xiIdKkPxlL;
      string DVaSPUcJVP;
      string drRHQxMhen;
      string UlZWajenLa;
      string lrjkJniTXT;
      string CVxfzEQANM;
      string YhRxqRuDqf;
      string ooytclIgyb;
      string NsJLlzntWV;
      string SdZzCDZltq;
      string sebqeMXCCN;
      string wjCkyeYGLr;
      string cAfUNKOyqY;
      string LVlGihRSgY;
      string alrJZibnAX;
      string eSaCOrzGdT;
      string yYKcCaxwCP;
      string NFZlQqIWud;
      string iZxTsrtjqp;
      string iKnMaCaOHy;
      if(xiIdKkPxlL == sebqeMXCCN){kelkJYrolX = true;}
      else if(sebqeMXCCN == xiIdKkPxlL){ukhxTLDPmr = true;}
      if(DVaSPUcJVP == wjCkyeYGLr){jbKzjXaqiJ = true;}
      else if(wjCkyeYGLr == DVaSPUcJVP){JnTfEeuVjb = true;}
      if(drRHQxMhen == cAfUNKOyqY){fMFMfCRNKO = true;}
      else if(cAfUNKOyqY == drRHQxMhen){ZtjlBUGdCp = true;}
      if(UlZWajenLa == LVlGihRSgY){PtPwrEnMJU = true;}
      else if(LVlGihRSgY == UlZWajenLa){ynYndRtlnb = true;}
      if(lrjkJniTXT == alrJZibnAX){zFyTGHzocD = true;}
      else if(alrJZibnAX == lrjkJniTXT){czekKotbyh = true;}
      if(CVxfzEQANM == eSaCOrzGdT){ajexSYZZEH = true;}
      else if(eSaCOrzGdT == CVxfzEQANM){YGqjpABuwy = true;}
      if(YhRxqRuDqf == yYKcCaxwCP){HedXHoMOGf = true;}
      else if(yYKcCaxwCP == YhRxqRuDqf){FYNwtVPeBm = true;}
      if(ooytclIgyb == NFZlQqIWud){iOgOKZOkFY = true;}
      if(NsJLlzntWV == iZxTsrtjqp){CcjHmfOSdT = true;}
      if(SdZzCDZltq == iKnMaCaOHy){dOHCMTbaLQ = true;}
      while(NFZlQqIWud == ooytclIgyb){jIhHyaOybL = true;}
      while(iZxTsrtjqp == iZxTsrtjqp){aefTRrwnyc = true;}
      while(iKnMaCaOHy == iKnMaCaOHy){PzpoWDkiqn = true;}
      if(kelkJYrolX == true){kelkJYrolX = false;}
      if(jbKzjXaqiJ == true){jbKzjXaqiJ = false;}
      if(fMFMfCRNKO == true){fMFMfCRNKO = false;}
      if(PtPwrEnMJU == true){PtPwrEnMJU = false;}
      if(zFyTGHzocD == true){zFyTGHzocD = false;}
      if(ajexSYZZEH == true){ajexSYZZEH = false;}
      if(HedXHoMOGf == true){HedXHoMOGf = false;}
      if(iOgOKZOkFY == true){iOgOKZOkFY = false;}
      if(CcjHmfOSdT == true){CcjHmfOSdT = false;}
      if(dOHCMTbaLQ == true){dOHCMTbaLQ = false;}
      if(ukhxTLDPmr == true){ukhxTLDPmr = false;}
      if(JnTfEeuVjb == true){JnTfEeuVjb = false;}
      if(ZtjlBUGdCp == true){ZtjlBUGdCp = false;}
      if(ynYndRtlnb == true){ynYndRtlnb = false;}
      if(czekKotbyh == true){czekKotbyh = false;}
      if(YGqjpABuwy == true){YGqjpABuwy = false;}
      if(FYNwtVPeBm == true){FYNwtVPeBm = false;}
      if(jIhHyaOybL == true){jIhHyaOybL = false;}
      if(aefTRrwnyc == true){aefTRrwnyc = false;}
      if(PzpoWDkiqn == true){PzpoWDkiqn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ISLEMVSOET
{ 
  void GRUpecgWWp()
  { 
      bool cOIHBBZOuj = false;
      bool mQAqmEIUSw = false;
      bool ubGVtinkbM = false;
      bool lMGVszdLdK = false;
      bool GFSURlldyP = false;
      bool frznhAHmMS = false;
      bool MnmixaKeyn = false;
      bool ZxpHooJlDI = false;
      bool xKlLftNRmr = false;
      bool rqyLySRiWq = false;
      bool aGfKohBqzs = false;
      bool qUiEVBBbCC = false;
      bool NsqFuizeIW = false;
      bool WZOMgpebWy = false;
      bool rVRtBWHsow = false;
      bool QpgTdhPZOG = false;
      bool iWicVRGWXf = false;
      bool WZEEKqaxEY = false;
      bool bFoLGfstiz = false;
      bool aFMPPVmoXi = false;
      string ownwjlfLeg;
      string ZGhQCPGZsS;
      string dwVGgFCyZx;
      string yxgKhsFypM;
      string nrywXRiYLz;
      string WihhqsZgOd;
      string igkghbYXhI;
      string KHifekxYiP;
      string WclaaPPzTo;
      string TXjMcGHROu;
      string rLqCnPzCCG;
      string wAyzHGtKGR;
      string MZDromXWCX;
      string dfKmXKkjmL;
      string QMwMsSYjEW;
      string LxKwiRHzNA;
      string qbAecPpKbx;
      string UKWuBzdpyV;
      string NmSeMgUNEF;
      string ClVlToMRjc;
      if(ownwjlfLeg == rLqCnPzCCG){cOIHBBZOuj = true;}
      else if(rLqCnPzCCG == ownwjlfLeg){aGfKohBqzs = true;}
      if(ZGhQCPGZsS == wAyzHGtKGR){mQAqmEIUSw = true;}
      else if(wAyzHGtKGR == ZGhQCPGZsS){qUiEVBBbCC = true;}
      if(dwVGgFCyZx == MZDromXWCX){ubGVtinkbM = true;}
      else if(MZDromXWCX == dwVGgFCyZx){NsqFuizeIW = true;}
      if(yxgKhsFypM == dfKmXKkjmL){lMGVszdLdK = true;}
      else if(dfKmXKkjmL == yxgKhsFypM){WZOMgpebWy = true;}
      if(nrywXRiYLz == QMwMsSYjEW){GFSURlldyP = true;}
      else if(QMwMsSYjEW == nrywXRiYLz){rVRtBWHsow = true;}
      if(WihhqsZgOd == LxKwiRHzNA){frznhAHmMS = true;}
      else if(LxKwiRHzNA == WihhqsZgOd){QpgTdhPZOG = true;}
      if(igkghbYXhI == qbAecPpKbx){MnmixaKeyn = true;}
      else if(qbAecPpKbx == igkghbYXhI){iWicVRGWXf = true;}
      if(KHifekxYiP == UKWuBzdpyV){ZxpHooJlDI = true;}
      if(WclaaPPzTo == NmSeMgUNEF){xKlLftNRmr = true;}
      if(TXjMcGHROu == ClVlToMRjc){rqyLySRiWq = true;}
      while(UKWuBzdpyV == KHifekxYiP){WZEEKqaxEY = true;}
      while(NmSeMgUNEF == NmSeMgUNEF){bFoLGfstiz = true;}
      while(ClVlToMRjc == ClVlToMRjc){aFMPPVmoXi = true;}
      if(cOIHBBZOuj == true){cOIHBBZOuj = false;}
      if(mQAqmEIUSw == true){mQAqmEIUSw = false;}
      if(ubGVtinkbM == true){ubGVtinkbM = false;}
      if(lMGVszdLdK == true){lMGVszdLdK = false;}
      if(GFSURlldyP == true){GFSURlldyP = false;}
      if(frznhAHmMS == true){frznhAHmMS = false;}
      if(MnmixaKeyn == true){MnmixaKeyn = false;}
      if(ZxpHooJlDI == true){ZxpHooJlDI = false;}
      if(xKlLftNRmr == true){xKlLftNRmr = false;}
      if(rqyLySRiWq == true){rqyLySRiWq = false;}
      if(aGfKohBqzs == true){aGfKohBqzs = false;}
      if(qUiEVBBbCC == true){qUiEVBBbCC = false;}
      if(NsqFuizeIW == true){NsqFuizeIW = false;}
      if(WZOMgpebWy == true){WZOMgpebWy = false;}
      if(rVRtBWHsow == true){rVRtBWHsow = false;}
      if(QpgTdhPZOG == true){QpgTdhPZOG = false;}
      if(iWicVRGWXf == true){iWicVRGWXf = false;}
      if(WZEEKqaxEY == true){WZEEKqaxEY = false;}
      if(bFoLGfstiz == true){bFoLGfstiz = false;}
      if(aFMPPVmoXi == true){aFMPPVmoXi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OYFUITCRGV
{ 
  void sZdojOdwwC()
  { 
      bool ihimGiIXIh = false;
      bool DyEATxcHrs = false;
      bool RMCPUptRee = false;
      bool MNZniqVqtE = false;
      bool HJdmAQkfGL = false;
      bool JpqpxWfTRQ = false;
      bool oqrcVpXPQc = false;
      bool akMmlHiPOE = false;
      bool EOLTVWWiqM = false;
      bool LCZdPPRARK = false;
      bool rVOdjYcDDo = false;
      bool nQENLZeYHy = false;
      bool ToYERYLiXV = false;
      bool phyEMiAhjx = false;
      bool sSeBYtxMRo = false;
      bool ksrSqCwJMK = false;
      bool MtehzFSzAc = false;
      bool YxnJEAJWfW = false;
      bool ayQhkxoeNJ = false;
      bool lpUYjznxCS = false;
      string nPPSHVcDoB;
      string eOIhDctqVO;
      string HoCEgTVitR;
      string mIIhHIDLOQ;
      string eYiBfRlzPz;
      string tjDNLzNKlm;
      string ztIXOVFaZu;
      string YhbFiiFAXO;
      string hWTuXCEtWI;
      string tsZbQkPLmJ;
      string LLYTZLIyec;
      string sMlWFcZNAL;
      string QLDRAfIAny;
      string SsNODVxzUL;
      string tGPtOhGCVm;
      string KCLarzHHSt;
      string DHJfJzzXTi;
      string fasnRKwJDS;
      string ZFdBnPhlVD;
      string OpfaIlxijO;
      if(nPPSHVcDoB == LLYTZLIyec){ihimGiIXIh = true;}
      else if(LLYTZLIyec == nPPSHVcDoB){rVOdjYcDDo = true;}
      if(eOIhDctqVO == sMlWFcZNAL){DyEATxcHrs = true;}
      else if(sMlWFcZNAL == eOIhDctqVO){nQENLZeYHy = true;}
      if(HoCEgTVitR == QLDRAfIAny){RMCPUptRee = true;}
      else if(QLDRAfIAny == HoCEgTVitR){ToYERYLiXV = true;}
      if(mIIhHIDLOQ == SsNODVxzUL){MNZniqVqtE = true;}
      else if(SsNODVxzUL == mIIhHIDLOQ){phyEMiAhjx = true;}
      if(eYiBfRlzPz == tGPtOhGCVm){HJdmAQkfGL = true;}
      else if(tGPtOhGCVm == eYiBfRlzPz){sSeBYtxMRo = true;}
      if(tjDNLzNKlm == KCLarzHHSt){JpqpxWfTRQ = true;}
      else if(KCLarzHHSt == tjDNLzNKlm){ksrSqCwJMK = true;}
      if(ztIXOVFaZu == DHJfJzzXTi){oqrcVpXPQc = true;}
      else if(DHJfJzzXTi == ztIXOVFaZu){MtehzFSzAc = true;}
      if(YhbFiiFAXO == fasnRKwJDS){akMmlHiPOE = true;}
      if(hWTuXCEtWI == ZFdBnPhlVD){EOLTVWWiqM = true;}
      if(tsZbQkPLmJ == OpfaIlxijO){LCZdPPRARK = true;}
      while(fasnRKwJDS == YhbFiiFAXO){YxnJEAJWfW = true;}
      while(ZFdBnPhlVD == ZFdBnPhlVD){ayQhkxoeNJ = true;}
      while(OpfaIlxijO == OpfaIlxijO){lpUYjznxCS = true;}
      if(ihimGiIXIh == true){ihimGiIXIh = false;}
      if(DyEATxcHrs == true){DyEATxcHrs = false;}
      if(RMCPUptRee == true){RMCPUptRee = false;}
      if(MNZniqVqtE == true){MNZniqVqtE = false;}
      if(HJdmAQkfGL == true){HJdmAQkfGL = false;}
      if(JpqpxWfTRQ == true){JpqpxWfTRQ = false;}
      if(oqrcVpXPQc == true){oqrcVpXPQc = false;}
      if(akMmlHiPOE == true){akMmlHiPOE = false;}
      if(EOLTVWWiqM == true){EOLTVWWiqM = false;}
      if(LCZdPPRARK == true){LCZdPPRARK = false;}
      if(rVOdjYcDDo == true){rVOdjYcDDo = false;}
      if(nQENLZeYHy == true){nQENLZeYHy = false;}
      if(ToYERYLiXV == true){ToYERYLiXV = false;}
      if(phyEMiAhjx == true){phyEMiAhjx = false;}
      if(sSeBYtxMRo == true){sSeBYtxMRo = false;}
      if(ksrSqCwJMK == true){ksrSqCwJMK = false;}
      if(MtehzFSzAc == true){MtehzFSzAc = false;}
      if(YxnJEAJWfW == true){YxnJEAJWfW = false;}
      if(ayQhkxoeNJ == true){ayQhkxoeNJ = false;}
      if(lpUYjznxCS == true){lpUYjznxCS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XGGHTGBDQS
{ 
  void eTMuBlCutG()
  { 
      bool ncGaMXhjYi = false;
      bool cbzDmMHXgE = false;
      bool qpoSayIKwL = false;
      bool lDAUEVQeSx = false;
      bool yIJHRTxKDs = false;
      bool TLODhynmzN = false;
      bool OXnNxYbezR = false;
      bool wbEiGhfhBH = false;
      bool ByGCrZowlF = false;
      bool hcfFiaTwJr = false;
      bool qSLlxqHexA = false;
      bool RFlqMQQkVX = false;
      bool ifrsiSwzAf = false;
      bool OjXIPhlTFA = false;
      bool RKzlnbpnsR = false;
      bool JialILZRCd = false;
      bool tIdQkhgdad = false;
      bool dweUFYfGFH = false;
      bool bHFiWeJlAE = false;
      bool HURbFJghAG = false;
      string eZsbhqzSuR;
      string qpdegTjdHM;
      string xCQHqJPFPk;
      string eEadBrXoYX;
      string VRpczqnarq;
      string UWaJgbIkjX;
      string btDJllPAco;
      string utEjqeMmIz;
      string UnMYQIdQwY;
      string ilEAuaOfqM;
      string bnxCuZRqSC;
      string PVbkDmgesd;
      string IyDDGJpDnP;
      string QfwuXfqKcp;
      string pmytJNJSxI;
      string tjmMEcktwl;
      string jODCkjYgMW;
      string wWBCnVzItr;
      string zWGeUfriqt;
      string uxNqGbiuIZ;
      if(eZsbhqzSuR == bnxCuZRqSC){ncGaMXhjYi = true;}
      else if(bnxCuZRqSC == eZsbhqzSuR){qSLlxqHexA = true;}
      if(qpdegTjdHM == PVbkDmgesd){cbzDmMHXgE = true;}
      else if(PVbkDmgesd == qpdegTjdHM){RFlqMQQkVX = true;}
      if(xCQHqJPFPk == IyDDGJpDnP){qpoSayIKwL = true;}
      else if(IyDDGJpDnP == xCQHqJPFPk){ifrsiSwzAf = true;}
      if(eEadBrXoYX == QfwuXfqKcp){lDAUEVQeSx = true;}
      else if(QfwuXfqKcp == eEadBrXoYX){OjXIPhlTFA = true;}
      if(VRpczqnarq == pmytJNJSxI){yIJHRTxKDs = true;}
      else if(pmytJNJSxI == VRpczqnarq){RKzlnbpnsR = true;}
      if(UWaJgbIkjX == tjmMEcktwl){TLODhynmzN = true;}
      else if(tjmMEcktwl == UWaJgbIkjX){JialILZRCd = true;}
      if(btDJllPAco == jODCkjYgMW){OXnNxYbezR = true;}
      else if(jODCkjYgMW == btDJllPAco){tIdQkhgdad = true;}
      if(utEjqeMmIz == wWBCnVzItr){wbEiGhfhBH = true;}
      if(UnMYQIdQwY == zWGeUfriqt){ByGCrZowlF = true;}
      if(ilEAuaOfqM == uxNqGbiuIZ){hcfFiaTwJr = true;}
      while(wWBCnVzItr == utEjqeMmIz){dweUFYfGFH = true;}
      while(zWGeUfriqt == zWGeUfriqt){bHFiWeJlAE = true;}
      while(uxNqGbiuIZ == uxNqGbiuIZ){HURbFJghAG = true;}
      if(ncGaMXhjYi == true){ncGaMXhjYi = false;}
      if(cbzDmMHXgE == true){cbzDmMHXgE = false;}
      if(qpoSayIKwL == true){qpoSayIKwL = false;}
      if(lDAUEVQeSx == true){lDAUEVQeSx = false;}
      if(yIJHRTxKDs == true){yIJHRTxKDs = false;}
      if(TLODhynmzN == true){TLODhynmzN = false;}
      if(OXnNxYbezR == true){OXnNxYbezR = false;}
      if(wbEiGhfhBH == true){wbEiGhfhBH = false;}
      if(ByGCrZowlF == true){ByGCrZowlF = false;}
      if(hcfFiaTwJr == true){hcfFiaTwJr = false;}
      if(qSLlxqHexA == true){qSLlxqHexA = false;}
      if(RFlqMQQkVX == true){RFlqMQQkVX = false;}
      if(ifrsiSwzAf == true){ifrsiSwzAf = false;}
      if(OjXIPhlTFA == true){OjXIPhlTFA = false;}
      if(RKzlnbpnsR == true){RKzlnbpnsR = false;}
      if(JialILZRCd == true){JialILZRCd = false;}
      if(tIdQkhgdad == true){tIdQkhgdad = false;}
      if(dweUFYfGFH == true){dweUFYfGFH = false;}
      if(bHFiWeJlAE == true){bHFiWeJlAE = false;}
      if(HURbFJghAG == true){HURbFJghAG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KRUVDOTLWW
{ 
  void FDRjnXxGaS()
  { 
      bool lViczVODeb = false;
      bool gULcWKTEzN = false;
      bool wmBYqeuWbs = false;
      bool LslpHZQdFL = false;
      bool YBHdpIeVJb = false;
      bool ZFOaIzTJlT = false;
      bool aqblPmiUUx = false;
      bool spzmoueWhh = false;
      bool AYNzTFeLhI = false;
      bool FGqkkgZVND = false;
      bool ZJBLhiGalN = false;
      bool TwaESBdbRK = false;
      bool HWmLrmyNCH = false;
      bool VIIeHqXCQj = false;
      bool zEZUnIelSj = false;
      bool DxEDwDVoTu = false;
      bool ksYdqLnwxb = false;
      bool caKgKDxSXi = false;
      bool HMuSDXEEiE = false;
      bool UhiVzGfucc = false;
      string kdIaLKDsjs;
      string dQJVIBNiTk;
      string xRQKRYnixp;
      string jqoptHmwhI;
      string DSVjWQijgG;
      string FhrOoSNyIl;
      string WTutJmbTbB;
      string NRBKhewgmA;
      string pECqjBzaBa;
      string somuliWaaj;
      string oOHernggfJ;
      string VgKHwRRDJH;
      string mBSAHYdFYz;
      string HUGDLawWzw;
      string URtqFMdeyT;
      string QSQSwnwGXS;
      string JaIgCAaHwU;
      string UtENmUGaut;
      string uzHEhnEmGX;
      string dpzglsJNnE;
      if(kdIaLKDsjs == oOHernggfJ){lViczVODeb = true;}
      else if(oOHernggfJ == kdIaLKDsjs){ZJBLhiGalN = true;}
      if(dQJVIBNiTk == VgKHwRRDJH){gULcWKTEzN = true;}
      else if(VgKHwRRDJH == dQJVIBNiTk){TwaESBdbRK = true;}
      if(xRQKRYnixp == mBSAHYdFYz){wmBYqeuWbs = true;}
      else if(mBSAHYdFYz == xRQKRYnixp){HWmLrmyNCH = true;}
      if(jqoptHmwhI == HUGDLawWzw){LslpHZQdFL = true;}
      else if(HUGDLawWzw == jqoptHmwhI){VIIeHqXCQj = true;}
      if(DSVjWQijgG == URtqFMdeyT){YBHdpIeVJb = true;}
      else if(URtqFMdeyT == DSVjWQijgG){zEZUnIelSj = true;}
      if(FhrOoSNyIl == QSQSwnwGXS){ZFOaIzTJlT = true;}
      else if(QSQSwnwGXS == FhrOoSNyIl){DxEDwDVoTu = true;}
      if(WTutJmbTbB == JaIgCAaHwU){aqblPmiUUx = true;}
      else if(JaIgCAaHwU == WTutJmbTbB){ksYdqLnwxb = true;}
      if(NRBKhewgmA == UtENmUGaut){spzmoueWhh = true;}
      if(pECqjBzaBa == uzHEhnEmGX){AYNzTFeLhI = true;}
      if(somuliWaaj == dpzglsJNnE){FGqkkgZVND = true;}
      while(UtENmUGaut == NRBKhewgmA){caKgKDxSXi = true;}
      while(uzHEhnEmGX == uzHEhnEmGX){HMuSDXEEiE = true;}
      while(dpzglsJNnE == dpzglsJNnE){UhiVzGfucc = true;}
      if(lViczVODeb == true){lViczVODeb = false;}
      if(gULcWKTEzN == true){gULcWKTEzN = false;}
      if(wmBYqeuWbs == true){wmBYqeuWbs = false;}
      if(LslpHZQdFL == true){LslpHZQdFL = false;}
      if(YBHdpIeVJb == true){YBHdpIeVJb = false;}
      if(ZFOaIzTJlT == true){ZFOaIzTJlT = false;}
      if(aqblPmiUUx == true){aqblPmiUUx = false;}
      if(spzmoueWhh == true){spzmoueWhh = false;}
      if(AYNzTFeLhI == true){AYNzTFeLhI = false;}
      if(FGqkkgZVND == true){FGqkkgZVND = false;}
      if(ZJBLhiGalN == true){ZJBLhiGalN = false;}
      if(TwaESBdbRK == true){TwaESBdbRK = false;}
      if(HWmLrmyNCH == true){HWmLrmyNCH = false;}
      if(VIIeHqXCQj == true){VIIeHqXCQj = false;}
      if(zEZUnIelSj == true){zEZUnIelSj = false;}
      if(DxEDwDVoTu == true){DxEDwDVoTu = false;}
      if(ksYdqLnwxb == true){ksYdqLnwxb = false;}
      if(caKgKDxSXi == true){caKgKDxSXi = false;}
      if(HMuSDXEEiE == true){HMuSDXEEiE = false;}
      if(UhiVzGfucc == true){UhiVzGfucc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZDJTNXGYM
{ 
  void rIHiLQJPVo()
  { 
      bool nYYfmFDryk = false;
      bool XliCRVoyBs = false;
      bool BKVmrLbdCz = false;
      bool cVRfJuSFOS = false;
      bool HLHNgiNRRB = false;
      bool ucMqhdDkma = false;
      bool cYozIBUCrV = false;
      bool CijhloDHGJ = false;
      bool yJMAEAIZyf = false;
      bool rhRmohWIFe = false;
      bool NKZuzLseFr = false;
      bool auddcSMntI = false;
      bool rtELdURwrD = false;
      bool SuBawmjQBs = false;
      bool GdUGFwDnJV = false;
      bool VhNxmSGNQd = false;
      bool twlCZesDgp = false;
      bool iulBBOZyFh = false;
      bool RclWgjgEnc = false;
      bool fVzXyKrSgZ = false;
      string bbxknlclZf;
      string ctfSqiAbKC;
      string bxFglbdmiH;
      string UXhXueSVdJ;
      string IBwnYrmbPO;
      string ADytEdVQzM;
      string HoCRLELIWL;
      string PexAsZBQHs;
      string nBXTGQZnSR;
      string ICWRCTzdcT;
      string fdEDzVGyAe;
      string bEIFXFRhLt;
      string eXpFCNIeyZ;
      string aWnnMJwUUk;
      string KannoEsQtw;
      string BQShoHnzAk;
      string MaAZDFQUrN;
      string IwNajDjBPy;
      string TqkBXKDFzE;
      string UxTiXjaNji;
      if(bbxknlclZf == fdEDzVGyAe){nYYfmFDryk = true;}
      else if(fdEDzVGyAe == bbxknlclZf){NKZuzLseFr = true;}
      if(ctfSqiAbKC == bEIFXFRhLt){XliCRVoyBs = true;}
      else if(bEIFXFRhLt == ctfSqiAbKC){auddcSMntI = true;}
      if(bxFglbdmiH == eXpFCNIeyZ){BKVmrLbdCz = true;}
      else if(eXpFCNIeyZ == bxFglbdmiH){rtELdURwrD = true;}
      if(UXhXueSVdJ == aWnnMJwUUk){cVRfJuSFOS = true;}
      else if(aWnnMJwUUk == UXhXueSVdJ){SuBawmjQBs = true;}
      if(IBwnYrmbPO == KannoEsQtw){HLHNgiNRRB = true;}
      else if(KannoEsQtw == IBwnYrmbPO){GdUGFwDnJV = true;}
      if(ADytEdVQzM == BQShoHnzAk){ucMqhdDkma = true;}
      else if(BQShoHnzAk == ADytEdVQzM){VhNxmSGNQd = true;}
      if(HoCRLELIWL == MaAZDFQUrN){cYozIBUCrV = true;}
      else if(MaAZDFQUrN == HoCRLELIWL){twlCZesDgp = true;}
      if(PexAsZBQHs == IwNajDjBPy){CijhloDHGJ = true;}
      if(nBXTGQZnSR == TqkBXKDFzE){yJMAEAIZyf = true;}
      if(ICWRCTzdcT == UxTiXjaNji){rhRmohWIFe = true;}
      while(IwNajDjBPy == PexAsZBQHs){iulBBOZyFh = true;}
      while(TqkBXKDFzE == TqkBXKDFzE){RclWgjgEnc = true;}
      while(UxTiXjaNji == UxTiXjaNji){fVzXyKrSgZ = true;}
      if(nYYfmFDryk == true){nYYfmFDryk = false;}
      if(XliCRVoyBs == true){XliCRVoyBs = false;}
      if(BKVmrLbdCz == true){BKVmrLbdCz = false;}
      if(cVRfJuSFOS == true){cVRfJuSFOS = false;}
      if(HLHNgiNRRB == true){HLHNgiNRRB = false;}
      if(ucMqhdDkma == true){ucMqhdDkma = false;}
      if(cYozIBUCrV == true){cYozIBUCrV = false;}
      if(CijhloDHGJ == true){CijhloDHGJ = false;}
      if(yJMAEAIZyf == true){yJMAEAIZyf = false;}
      if(rhRmohWIFe == true){rhRmohWIFe = false;}
      if(NKZuzLseFr == true){NKZuzLseFr = false;}
      if(auddcSMntI == true){auddcSMntI = false;}
      if(rtELdURwrD == true){rtELdURwrD = false;}
      if(SuBawmjQBs == true){SuBawmjQBs = false;}
      if(GdUGFwDnJV == true){GdUGFwDnJV = false;}
      if(VhNxmSGNQd == true){VhNxmSGNQd = false;}
      if(twlCZesDgp == true){twlCZesDgp = false;}
      if(iulBBOZyFh == true){iulBBOZyFh = false;}
      if(RclWgjgEnc == true){RclWgjgEnc = false;}
      if(fVzXyKrSgZ == true){fVzXyKrSgZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQLWYQGAKE
{ 
  void wLcatqiYHA()
  { 
      bool JJCyaCPcjn = false;
      bool UYBUnOYSAu = false;
      bool OHqBTUEYEZ = false;
      bool GHIMqJdtdJ = false;
      bool gWFCOBqoTj = false;
      bool uKuMjBSBeF = false;
      bool ypXJhMPoce = false;
      bool kdnpOqCnlR = false;
      bool cPEUeuMwbp = false;
      bool qbPXLpyuUC = false;
      bool lCMozQWFyr = false;
      bool zdPMcilDel = false;
      bool ATMmmIOQeX = false;
      bool sGTjfaDOVN = false;
      bool YGxjqMMCuc = false;
      bool EtQhBRoYBp = false;
      bool CFaazsKefB = false;
      bool fWhQNsVcwa = false;
      bool uLVBSyokhN = false;
      bool kdMeLTfWjy = false;
      string RTFakSSjqQ;
      string goYBHLVoRz;
      string RHTinuIRCe;
      string qfdQTZLTwQ;
      string LcslKuSSKS;
      string SzPebKAWlo;
      string JAgLZALIhg;
      string ACsAnoOgYs;
      string cpHiMrPznJ;
      string ZogGHKugMJ;
      string jKkcSQFPpm;
      string wSxsMSsyzg;
      string kLTXHKUmrd;
      string tgUPIRFeQu;
      string lAIBNGqnsn;
      string QxgeYYqMUH;
      string wSWMrOxhkt;
      string NOgEtjDRKA;
      string TgsEMxApqj;
      string asJIzTduIy;
      if(RTFakSSjqQ == jKkcSQFPpm){JJCyaCPcjn = true;}
      else if(jKkcSQFPpm == RTFakSSjqQ){lCMozQWFyr = true;}
      if(goYBHLVoRz == wSxsMSsyzg){UYBUnOYSAu = true;}
      else if(wSxsMSsyzg == goYBHLVoRz){zdPMcilDel = true;}
      if(RHTinuIRCe == kLTXHKUmrd){OHqBTUEYEZ = true;}
      else if(kLTXHKUmrd == RHTinuIRCe){ATMmmIOQeX = true;}
      if(qfdQTZLTwQ == tgUPIRFeQu){GHIMqJdtdJ = true;}
      else if(tgUPIRFeQu == qfdQTZLTwQ){sGTjfaDOVN = true;}
      if(LcslKuSSKS == lAIBNGqnsn){gWFCOBqoTj = true;}
      else if(lAIBNGqnsn == LcslKuSSKS){YGxjqMMCuc = true;}
      if(SzPebKAWlo == QxgeYYqMUH){uKuMjBSBeF = true;}
      else if(QxgeYYqMUH == SzPebKAWlo){EtQhBRoYBp = true;}
      if(JAgLZALIhg == wSWMrOxhkt){ypXJhMPoce = true;}
      else if(wSWMrOxhkt == JAgLZALIhg){CFaazsKefB = true;}
      if(ACsAnoOgYs == NOgEtjDRKA){kdnpOqCnlR = true;}
      if(cpHiMrPznJ == TgsEMxApqj){cPEUeuMwbp = true;}
      if(ZogGHKugMJ == asJIzTduIy){qbPXLpyuUC = true;}
      while(NOgEtjDRKA == ACsAnoOgYs){fWhQNsVcwa = true;}
      while(TgsEMxApqj == TgsEMxApqj){uLVBSyokhN = true;}
      while(asJIzTduIy == asJIzTduIy){kdMeLTfWjy = true;}
      if(JJCyaCPcjn == true){JJCyaCPcjn = false;}
      if(UYBUnOYSAu == true){UYBUnOYSAu = false;}
      if(OHqBTUEYEZ == true){OHqBTUEYEZ = false;}
      if(GHIMqJdtdJ == true){GHIMqJdtdJ = false;}
      if(gWFCOBqoTj == true){gWFCOBqoTj = false;}
      if(uKuMjBSBeF == true){uKuMjBSBeF = false;}
      if(ypXJhMPoce == true){ypXJhMPoce = false;}
      if(kdnpOqCnlR == true){kdnpOqCnlR = false;}
      if(cPEUeuMwbp == true){cPEUeuMwbp = false;}
      if(qbPXLpyuUC == true){qbPXLpyuUC = false;}
      if(lCMozQWFyr == true){lCMozQWFyr = false;}
      if(zdPMcilDel == true){zdPMcilDel = false;}
      if(ATMmmIOQeX == true){ATMmmIOQeX = false;}
      if(sGTjfaDOVN == true){sGTjfaDOVN = false;}
      if(YGxjqMMCuc == true){YGxjqMMCuc = false;}
      if(EtQhBRoYBp == true){EtQhBRoYBp = false;}
      if(CFaazsKefB == true){CFaazsKefB = false;}
      if(fWhQNsVcwa == true){fWhQNsVcwa = false;}
      if(uLVBSyokhN == true){uLVBSyokhN = false;}
      if(kdMeLTfWjy == true){kdMeLTfWjy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YYQIJLQLDW
{ 
  void TfhRExeelJ()
  { 
      bool dddnVijMJD = false;
      bool WsVPfdEwgg = false;
      bool MYcUTFwHiU = false;
      bool EDyXODOlJI = false;
      bool jpFxrACqHK = false;
      bool yXTiqFAITQ = false;
      bool mccoyTuyAb = false;
      bool OSlXwWTfbT = false;
      bool CEAYVfjOgJ = false;
      bool DFRsVHMQyY = false;
      bool EDqewflulT = false;
      bool kTgANhcESS = false;
      bool ifRpYIAsBo = false;
      bool JChDOzMUcp = false;
      bool tnbMXiYRem = false;
      bool eIyeoXkAGm = false;
      bool estxKilckO = false;
      bool VHbbYuEFSo = false;
      bool ihNOKBDCOp = false;
      bool NMNoLAteBo = false;
      string ujkRlacOkn;
      string WPwjlCCPqt;
      string DqQCzfPWNN;
      string qtLuWVxGWL;
      string LbniaGoDkI;
      string YAnkbESiSF;
      string LFAWwbDAMP;
      string EusfiaDhbs;
      string qMlEopFaTS;
      string DOnQzFaRly;
      string DopVDdHIBB;
      string AjGZOzTwhF;
      string VbgsMpHbfd;
      string zlucpBVQBK;
      string hxYRSSHNBz;
      string leifbaIxIN;
      string WfbXBOndjN;
      string dDuWWYDOas;
      string hsafqUCOAO;
      string sYHmnCUAQD;
      if(ujkRlacOkn == DopVDdHIBB){dddnVijMJD = true;}
      else if(DopVDdHIBB == ujkRlacOkn){EDqewflulT = true;}
      if(WPwjlCCPqt == AjGZOzTwhF){WsVPfdEwgg = true;}
      else if(AjGZOzTwhF == WPwjlCCPqt){kTgANhcESS = true;}
      if(DqQCzfPWNN == VbgsMpHbfd){MYcUTFwHiU = true;}
      else if(VbgsMpHbfd == DqQCzfPWNN){ifRpYIAsBo = true;}
      if(qtLuWVxGWL == zlucpBVQBK){EDyXODOlJI = true;}
      else if(zlucpBVQBK == qtLuWVxGWL){JChDOzMUcp = true;}
      if(LbniaGoDkI == hxYRSSHNBz){jpFxrACqHK = true;}
      else if(hxYRSSHNBz == LbniaGoDkI){tnbMXiYRem = true;}
      if(YAnkbESiSF == leifbaIxIN){yXTiqFAITQ = true;}
      else if(leifbaIxIN == YAnkbESiSF){eIyeoXkAGm = true;}
      if(LFAWwbDAMP == WfbXBOndjN){mccoyTuyAb = true;}
      else if(WfbXBOndjN == LFAWwbDAMP){estxKilckO = true;}
      if(EusfiaDhbs == dDuWWYDOas){OSlXwWTfbT = true;}
      if(qMlEopFaTS == hsafqUCOAO){CEAYVfjOgJ = true;}
      if(DOnQzFaRly == sYHmnCUAQD){DFRsVHMQyY = true;}
      while(dDuWWYDOas == EusfiaDhbs){VHbbYuEFSo = true;}
      while(hsafqUCOAO == hsafqUCOAO){ihNOKBDCOp = true;}
      while(sYHmnCUAQD == sYHmnCUAQD){NMNoLAteBo = true;}
      if(dddnVijMJD == true){dddnVijMJD = false;}
      if(WsVPfdEwgg == true){WsVPfdEwgg = false;}
      if(MYcUTFwHiU == true){MYcUTFwHiU = false;}
      if(EDyXODOlJI == true){EDyXODOlJI = false;}
      if(jpFxrACqHK == true){jpFxrACqHK = false;}
      if(yXTiqFAITQ == true){yXTiqFAITQ = false;}
      if(mccoyTuyAb == true){mccoyTuyAb = false;}
      if(OSlXwWTfbT == true){OSlXwWTfbT = false;}
      if(CEAYVfjOgJ == true){CEAYVfjOgJ = false;}
      if(DFRsVHMQyY == true){DFRsVHMQyY = false;}
      if(EDqewflulT == true){EDqewflulT = false;}
      if(kTgANhcESS == true){kTgANhcESS = false;}
      if(ifRpYIAsBo == true){ifRpYIAsBo = false;}
      if(JChDOzMUcp == true){JChDOzMUcp = false;}
      if(tnbMXiYRem == true){tnbMXiYRem = false;}
      if(eIyeoXkAGm == true){eIyeoXkAGm = false;}
      if(estxKilckO == true){estxKilckO = false;}
      if(VHbbYuEFSo == true){VHbbYuEFSo = false;}
      if(ihNOKBDCOp == true){ihNOKBDCOp = false;}
      if(NMNoLAteBo == true){NMNoLAteBo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWZRDFMGYG
{ 
  void KFfwOoxxAL()
  { 
      bool IfyjjKQWZY = false;
      bool dlHCARMZuZ = false;
      bool BYcHKnktWW = false;
      bool xxpLGVqhsa = false;
      bool SwbKGwImPd = false;
      bool NOdUniCqZw = false;
      bool YVzCbguuud = false;
      bool ZdfUGEwRAN = false;
      bool eyesJhTVXW = false;
      bool SAIxBxxYiZ = false;
      bool BMqkEihINi = false;
      bool mkqLQapFss = false;
      bool MYXXLZViSJ = false;
      bool HXiZMSHtoZ = false;
      bool AKInjhJxga = false;
      bool GqfoNboTYe = false;
      bool NzoDbOBQyy = false;
      bool TuQSsBQjmc = false;
      bool PYBrDQqtLk = false;
      bool cmUKMBUEMU = false;
      string tSXqFfaLuX;
      string WxRjUybRXM;
      string QuQaqoKWPh;
      string kZGFllzXsm;
      string WBZOnWXRzy;
      string qBIuiyCwAQ;
      string UEuMmxpLyi;
      string zDYkpPVBmT;
      string RrWRqiQLWm;
      string jDWbRSFMbq;
      string fLTQymcXET;
      string cAJfycgdVE;
      string fdnKywfwSW;
      string KIZumFYGSD;
      string GsGDJisqdn;
      string kapXLBWIRC;
      string HfEgITaNrs;
      string EaKSxlWkBP;
      string CoSdliSBjk;
      string hPoPuaoZto;
      if(tSXqFfaLuX == fLTQymcXET){IfyjjKQWZY = true;}
      else if(fLTQymcXET == tSXqFfaLuX){BMqkEihINi = true;}
      if(WxRjUybRXM == cAJfycgdVE){dlHCARMZuZ = true;}
      else if(cAJfycgdVE == WxRjUybRXM){mkqLQapFss = true;}
      if(QuQaqoKWPh == fdnKywfwSW){BYcHKnktWW = true;}
      else if(fdnKywfwSW == QuQaqoKWPh){MYXXLZViSJ = true;}
      if(kZGFllzXsm == KIZumFYGSD){xxpLGVqhsa = true;}
      else if(KIZumFYGSD == kZGFllzXsm){HXiZMSHtoZ = true;}
      if(WBZOnWXRzy == GsGDJisqdn){SwbKGwImPd = true;}
      else if(GsGDJisqdn == WBZOnWXRzy){AKInjhJxga = true;}
      if(qBIuiyCwAQ == kapXLBWIRC){NOdUniCqZw = true;}
      else if(kapXLBWIRC == qBIuiyCwAQ){GqfoNboTYe = true;}
      if(UEuMmxpLyi == HfEgITaNrs){YVzCbguuud = true;}
      else if(HfEgITaNrs == UEuMmxpLyi){NzoDbOBQyy = true;}
      if(zDYkpPVBmT == EaKSxlWkBP){ZdfUGEwRAN = true;}
      if(RrWRqiQLWm == CoSdliSBjk){eyesJhTVXW = true;}
      if(jDWbRSFMbq == hPoPuaoZto){SAIxBxxYiZ = true;}
      while(EaKSxlWkBP == zDYkpPVBmT){TuQSsBQjmc = true;}
      while(CoSdliSBjk == CoSdliSBjk){PYBrDQqtLk = true;}
      while(hPoPuaoZto == hPoPuaoZto){cmUKMBUEMU = true;}
      if(IfyjjKQWZY == true){IfyjjKQWZY = false;}
      if(dlHCARMZuZ == true){dlHCARMZuZ = false;}
      if(BYcHKnktWW == true){BYcHKnktWW = false;}
      if(xxpLGVqhsa == true){xxpLGVqhsa = false;}
      if(SwbKGwImPd == true){SwbKGwImPd = false;}
      if(NOdUniCqZw == true){NOdUniCqZw = false;}
      if(YVzCbguuud == true){YVzCbguuud = false;}
      if(ZdfUGEwRAN == true){ZdfUGEwRAN = false;}
      if(eyesJhTVXW == true){eyesJhTVXW = false;}
      if(SAIxBxxYiZ == true){SAIxBxxYiZ = false;}
      if(BMqkEihINi == true){BMqkEihINi = false;}
      if(mkqLQapFss == true){mkqLQapFss = false;}
      if(MYXXLZViSJ == true){MYXXLZViSJ = false;}
      if(HXiZMSHtoZ == true){HXiZMSHtoZ = false;}
      if(AKInjhJxga == true){AKInjhJxga = false;}
      if(GqfoNboTYe == true){GqfoNboTYe = false;}
      if(NzoDbOBQyy == true){NzoDbOBQyy = false;}
      if(TuQSsBQjmc == true){TuQSsBQjmc = false;}
      if(PYBrDQqtLk == true){PYBrDQqtLk = false;}
      if(cmUKMBUEMU == true){cmUKMBUEMU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHQNFOKUPM
{ 
  void fzcwBggaCE()
  { 
      bool WdKBnLHTDZ = false;
      bool KsYQLocqgu = false;
      bool alQBmKSixP = false;
      bool NBZPCyeFak = false;
      bool KZnUBEODsW = false;
      bool AONhwjMINc = false;
      bool rYWmMISINN = false;
      bool JWPujBxuAi = false;
      bool wOoZOynrTR = false;
      bool kWryrkCAIr = false;
      bool kFofMczSxu = false;
      bool mQHdgdixXO = false;
      bool UZowbmeRCy = false;
      bool yxmHypZJMl = false;
      bool zVuXeTONRO = false;
      bool CFbtXKQsEZ = false;
      bool ygPyxodzfp = false;
      bool DZklPzeQQH = false;
      bool YQAnwsUsjm = false;
      bool ZfEmmRGwap = false;
      string MuMWDuBEda;
      string VdFCOQEsNH;
      string OQnurmEeSt;
      string eSLriYHjha;
      string RSNyeuCLFQ;
      string LnuOYwGQdP;
      string pVliwDRMSp;
      string JTLmpwCpPw;
      string jrYCipWxSl;
      string RpFRkugdCa;
      string cprOHrcIYc;
      string sQAheyxjAF;
      string gUsfYSNsCu;
      string PXmoTtzJtq;
      string MNXpsApXll;
      string yxdwsHwMpo;
      string djGdNVcLNk;
      string ymoJrTwDmY;
      string coGPwStquL;
      string xmTFMcGtcX;
      if(MuMWDuBEda == cprOHrcIYc){WdKBnLHTDZ = true;}
      else if(cprOHrcIYc == MuMWDuBEda){kFofMczSxu = true;}
      if(VdFCOQEsNH == sQAheyxjAF){KsYQLocqgu = true;}
      else if(sQAheyxjAF == VdFCOQEsNH){mQHdgdixXO = true;}
      if(OQnurmEeSt == gUsfYSNsCu){alQBmKSixP = true;}
      else if(gUsfYSNsCu == OQnurmEeSt){UZowbmeRCy = true;}
      if(eSLriYHjha == PXmoTtzJtq){NBZPCyeFak = true;}
      else if(PXmoTtzJtq == eSLriYHjha){yxmHypZJMl = true;}
      if(RSNyeuCLFQ == MNXpsApXll){KZnUBEODsW = true;}
      else if(MNXpsApXll == RSNyeuCLFQ){zVuXeTONRO = true;}
      if(LnuOYwGQdP == yxdwsHwMpo){AONhwjMINc = true;}
      else if(yxdwsHwMpo == LnuOYwGQdP){CFbtXKQsEZ = true;}
      if(pVliwDRMSp == djGdNVcLNk){rYWmMISINN = true;}
      else if(djGdNVcLNk == pVliwDRMSp){ygPyxodzfp = true;}
      if(JTLmpwCpPw == ymoJrTwDmY){JWPujBxuAi = true;}
      if(jrYCipWxSl == coGPwStquL){wOoZOynrTR = true;}
      if(RpFRkugdCa == xmTFMcGtcX){kWryrkCAIr = true;}
      while(ymoJrTwDmY == JTLmpwCpPw){DZklPzeQQH = true;}
      while(coGPwStquL == coGPwStquL){YQAnwsUsjm = true;}
      while(xmTFMcGtcX == xmTFMcGtcX){ZfEmmRGwap = true;}
      if(WdKBnLHTDZ == true){WdKBnLHTDZ = false;}
      if(KsYQLocqgu == true){KsYQLocqgu = false;}
      if(alQBmKSixP == true){alQBmKSixP = false;}
      if(NBZPCyeFak == true){NBZPCyeFak = false;}
      if(KZnUBEODsW == true){KZnUBEODsW = false;}
      if(AONhwjMINc == true){AONhwjMINc = false;}
      if(rYWmMISINN == true){rYWmMISINN = false;}
      if(JWPujBxuAi == true){JWPujBxuAi = false;}
      if(wOoZOynrTR == true){wOoZOynrTR = false;}
      if(kWryrkCAIr == true){kWryrkCAIr = false;}
      if(kFofMczSxu == true){kFofMczSxu = false;}
      if(mQHdgdixXO == true){mQHdgdixXO = false;}
      if(UZowbmeRCy == true){UZowbmeRCy = false;}
      if(yxmHypZJMl == true){yxmHypZJMl = false;}
      if(zVuXeTONRO == true){zVuXeTONRO = false;}
      if(CFbtXKQsEZ == true){CFbtXKQsEZ = false;}
      if(ygPyxodzfp == true){ygPyxodzfp = false;}
      if(DZklPzeQQH == true){DZklPzeQQH = false;}
      if(YQAnwsUsjm == true){YQAnwsUsjm = false;}
      if(ZfEmmRGwap == true){ZfEmmRGwap = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LYMEXLDZJN
{ 
  void nUfrGRmnty()
  { 
      bool WBzuuKGpiE = false;
      bool fXbwLyQrYf = false;
      bool unEspmIXhn = false;
      bool HzAEpkuQJL = false;
      bool uwYhLrPxeR = false;
      bool nUmGWixFFI = false;
      bool BhHtwgWXFZ = false;
      bool CzhMkzOVhx = false;
      bool WKsQzmLtgG = false;
      bool npLBJMneke = false;
      bool UrqEOnlaUX = false;
      bool UaWHkqoquJ = false;
      bool UcpylMmgCY = false;
      bool KjkCbeSnCL = false;
      bool AkYJlMSEPS = false;
      bool XxiaKrBsSB = false;
      bool AEXuMkpUeG = false;
      bool XAojIiEfMZ = false;
      bool tiQjBNAJrj = false;
      bool cZVAKuMcxA = false;
      string wWOSLsMBja;
      string TLAWCuHGNL;
      string qMArEmKPcs;
      string UzJVrVSVHh;
      string NwmKZKuzWH;
      string LrKayiVVOY;
      string ixXpFUBeef;
      string clyfytYoRs;
      string qLsUhcoiXI;
      string zwGizPYxFF;
      string JQTpeYsdcD;
      string JfDVgWEDHc;
      string fRGVgffOgh;
      string VbjMiZqCoJ;
      string iKGTzSrkCb;
      string LUobZqJyJz;
      string sdxthhwqlG;
      string fBOysULlVN;
      string mtMFVBlImr;
      string PrspPFMLlR;
      if(wWOSLsMBja == JQTpeYsdcD){WBzuuKGpiE = true;}
      else if(JQTpeYsdcD == wWOSLsMBja){UrqEOnlaUX = true;}
      if(TLAWCuHGNL == JfDVgWEDHc){fXbwLyQrYf = true;}
      else if(JfDVgWEDHc == TLAWCuHGNL){UaWHkqoquJ = true;}
      if(qMArEmKPcs == fRGVgffOgh){unEspmIXhn = true;}
      else if(fRGVgffOgh == qMArEmKPcs){UcpylMmgCY = true;}
      if(UzJVrVSVHh == VbjMiZqCoJ){HzAEpkuQJL = true;}
      else if(VbjMiZqCoJ == UzJVrVSVHh){KjkCbeSnCL = true;}
      if(NwmKZKuzWH == iKGTzSrkCb){uwYhLrPxeR = true;}
      else if(iKGTzSrkCb == NwmKZKuzWH){AkYJlMSEPS = true;}
      if(LrKayiVVOY == LUobZqJyJz){nUmGWixFFI = true;}
      else if(LUobZqJyJz == LrKayiVVOY){XxiaKrBsSB = true;}
      if(ixXpFUBeef == sdxthhwqlG){BhHtwgWXFZ = true;}
      else if(sdxthhwqlG == ixXpFUBeef){AEXuMkpUeG = true;}
      if(clyfytYoRs == fBOysULlVN){CzhMkzOVhx = true;}
      if(qLsUhcoiXI == mtMFVBlImr){WKsQzmLtgG = true;}
      if(zwGizPYxFF == PrspPFMLlR){npLBJMneke = true;}
      while(fBOysULlVN == clyfytYoRs){XAojIiEfMZ = true;}
      while(mtMFVBlImr == mtMFVBlImr){tiQjBNAJrj = true;}
      while(PrspPFMLlR == PrspPFMLlR){cZVAKuMcxA = true;}
      if(WBzuuKGpiE == true){WBzuuKGpiE = false;}
      if(fXbwLyQrYf == true){fXbwLyQrYf = false;}
      if(unEspmIXhn == true){unEspmIXhn = false;}
      if(HzAEpkuQJL == true){HzAEpkuQJL = false;}
      if(uwYhLrPxeR == true){uwYhLrPxeR = false;}
      if(nUmGWixFFI == true){nUmGWixFFI = false;}
      if(BhHtwgWXFZ == true){BhHtwgWXFZ = false;}
      if(CzhMkzOVhx == true){CzhMkzOVhx = false;}
      if(WKsQzmLtgG == true){WKsQzmLtgG = false;}
      if(npLBJMneke == true){npLBJMneke = false;}
      if(UrqEOnlaUX == true){UrqEOnlaUX = false;}
      if(UaWHkqoquJ == true){UaWHkqoquJ = false;}
      if(UcpylMmgCY == true){UcpylMmgCY = false;}
      if(KjkCbeSnCL == true){KjkCbeSnCL = false;}
      if(AkYJlMSEPS == true){AkYJlMSEPS = false;}
      if(XxiaKrBsSB == true){XxiaKrBsSB = false;}
      if(AEXuMkpUeG == true){AEXuMkpUeG = false;}
      if(XAojIiEfMZ == true){XAojIiEfMZ = false;}
      if(tiQjBNAJrj == true){tiQjBNAJrj = false;}
      if(cZVAKuMcxA == true){cZVAKuMcxA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BKMPDAZKPI
{ 
  void XrkLhoQdeE()
  { 
      bool bNqeJzVqBf = false;
      bool JxqknaRpej = false;
      bool RcJELHRYDb = false;
      bool PSoaAMtfXM = false;
      bool TCoyDKsyGt = false;
      bool cwJmlyDmTC = false;
      bool hwnZQpHQka = false;
      bool gkSSPOnLAB = false;
      bool OSRIzTICoB = false;
      bool IGMUdXOOhN = false;
      bool DcMeNqcqWW = false;
      bool KrlSnOdeaw = false;
      bool gFaiSZXxnr = false;
      bool AYdmxlFmuH = false;
      bool pReSpQTtgP = false;
      bool sinkfyBdMn = false;
      bool TfCdVlOzUB = false;
      bool IqjSGPZIrB = false;
      bool FdPYzRjrHz = false;
      bool jbZGnKPAwE = false;
      string GYopJdHCtw;
      string oagQApiGCx;
      string BCGgLgLYWx;
      string qKCNnxLiMS;
      string iATXYcpqoV;
      string HgrRHDRIdb;
      string SiewEdYScC;
      string eAtjNAhhHh;
      string pUjBoKRjFj;
      string eCEjAAUXSt;
      string EXOlqHmHEG;
      string ViBulyzdGt;
      string MnMrXbuJjM;
      string fKPMdSFxJh;
      string XKfyOuBJyC;
      string BpQYhQKVNO;
      string McXqaKTnRS;
      string rBTYWBHNdb;
      string ZlLhLpsqdM;
      string HjjuUtloXD;
      if(GYopJdHCtw == EXOlqHmHEG){bNqeJzVqBf = true;}
      else if(EXOlqHmHEG == GYopJdHCtw){DcMeNqcqWW = true;}
      if(oagQApiGCx == ViBulyzdGt){JxqknaRpej = true;}
      else if(ViBulyzdGt == oagQApiGCx){KrlSnOdeaw = true;}
      if(BCGgLgLYWx == MnMrXbuJjM){RcJELHRYDb = true;}
      else if(MnMrXbuJjM == BCGgLgLYWx){gFaiSZXxnr = true;}
      if(qKCNnxLiMS == fKPMdSFxJh){PSoaAMtfXM = true;}
      else if(fKPMdSFxJh == qKCNnxLiMS){AYdmxlFmuH = true;}
      if(iATXYcpqoV == XKfyOuBJyC){TCoyDKsyGt = true;}
      else if(XKfyOuBJyC == iATXYcpqoV){pReSpQTtgP = true;}
      if(HgrRHDRIdb == BpQYhQKVNO){cwJmlyDmTC = true;}
      else if(BpQYhQKVNO == HgrRHDRIdb){sinkfyBdMn = true;}
      if(SiewEdYScC == McXqaKTnRS){hwnZQpHQka = true;}
      else if(McXqaKTnRS == SiewEdYScC){TfCdVlOzUB = true;}
      if(eAtjNAhhHh == rBTYWBHNdb){gkSSPOnLAB = true;}
      if(pUjBoKRjFj == ZlLhLpsqdM){OSRIzTICoB = true;}
      if(eCEjAAUXSt == HjjuUtloXD){IGMUdXOOhN = true;}
      while(rBTYWBHNdb == eAtjNAhhHh){IqjSGPZIrB = true;}
      while(ZlLhLpsqdM == ZlLhLpsqdM){FdPYzRjrHz = true;}
      while(HjjuUtloXD == HjjuUtloXD){jbZGnKPAwE = true;}
      if(bNqeJzVqBf == true){bNqeJzVqBf = false;}
      if(JxqknaRpej == true){JxqknaRpej = false;}
      if(RcJELHRYDb == true){RcJELHRYDb = false;}
      if(PSoaAMtfXM == true){PSoaAMtfXM = false;}
      if(TCoyDKsyGt == true){TCoyDKsyGt = false;}
      if(cwJmlyDmTC == true){cwJmlyDmTC = false;}
      if(hwnZQpHQka == true){hwnZQpHQka = false;}
      if(gkSSPOnLAB == true){gkSSPOnLAB = false;}
      if(OSRIzTICoB == true){OSRIzTICoB = false;}
      if(IGMUdXOOhN == true){IGMUdXOOhN = false;}
      if(DcMeNqcqWW == true){DcMeNqcqWW = false;}
      if(KrlSnOdeaw == true){KrlSnOdeaw = false;}
      if(gFaiSZXxnr == true){gFaiSZXxnr = false;}
      if(AYdmxlFmuH == true){AYdmxlFmuH = false;}
      if(pReSpQTtgP == true){pReSpQTtgP = false;}
      if(sinkfyBdMn == true){sinkfyBdMn = false;}
      if(TfCdVlOzUB == true){TfCdVlOzUB = false;}
      if(IqjSGPZIrB == true){IqjSGPZIrB = false;}
      if(FdPYzRjrHz == true){FdPYzRjrHz = false;}
      if(jbZGnKPAwE == true){jbZGnKPAwE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ANSHWUBRXD
{ 
  void qLfPLyxquS()
  { 
      bool BucfSCkOIZ = false;
      bool XcsMYguSLA = false;
      bool CeNmbhELnz = false;
      bool ktgMiMwkhs = false;
      bool kfqYKRKLEN = false;
      bool WaRYQVgpDk = false;
      bool yZaJndufdM = false;
      bool kJjSPVmocK = false;
      bool XrGZbJcHwN = false;
      bool eGgwtLFhjf = false;
      bool VdhqcNpyJt = false;
      bool hqNrNFSAgd = false;
      bool BnjQhebnXD = false;
      bool QFFwosJOxO = false;
      bool TdyBemroio = false;
      bool sFAFegtRJx = false;
      bool kCaGdclQDT = false;
      bool uDDRKWohkt = false;
      bool lmEiKLEzQH = false;
      bool zrFzdQDqXB = false;
      string DZuEqylyBS;
      string TlYmwaIsKS;
      string EgWeTYgDqi;
      string MmIFfqnkVj;
      string NhDadhGfTj;
      string BDzopVDQkS;
      string QiHSFfcSHF;
      string mWWZFWdwAk;
      string RBjHgJmTPJ;
      string nXzDTeZjVx;
      string FmXNwefZiS;
      string rGPAAOyAlu;
      string rIDyQPXTFa;
      string wtaDeddVKC;
      string dNkwRgHyCE;
      string fZyZEwjZxg;
      string GLTHWyfMVW;
      string kcojQeXGgj;
      string HYQBuVuAyi;
      string tDYduRsdZT;
      if(DZuEqylyBS == FmXNwefZiS){BucfSCkOIZ = true;}
      else if(FmXNwefZiS == DZuEqylyBS){VdhqcNpyJt = true;}
      if(TlYmwaIsKS == rGPAAOyAlu){XcsMYguSLA = true;}
      else if(rGPAAOyAlu == TlYmwaIsKS){hqNrNFSAgd = true;}
      if(EgWeTYgDqi == rIDyQPXTFa){CeNmbhELnz = true;}
      else if(rIDyQPXTFa == EgWeTYgDqi){BnjQhebnXD = true;}
      if(MmIFfqnkVj == wtaDeddVKC){ktgMiMwkhs = true;}
      else if(wtaDeddVKC == MmIFfqnkVj){QFFwosJOxO = true;}
      if(NhDadhGfTj == dNkwRgHyCE){kfqYKRKLEN = true;}
      else if(dNkwRgHyCE == NhDadhGfTj){TdyBemroio = true;}
      if(BDzopVDQkS == fZyZEwjZxg){WaRYQVgpDk = true;}
      else if(fZyZEwjZxg == BDzopVDQkS){sFAFegtRJx = true;}
      if(QiHSFfcSHF == GLTHWyfMVW){yZaJndufdM = true;}
      else if(GLTHWyfMVW == QiHSFfcSHF){kCaGdclQDT = true;}
      if(mWWZFWdwAk == kcojQeXGgj){kJjSPVmocK = true;}
      if(RBjHgJmTPJ == HYQBuVuAyi){XrGZbJcHwN = true;}
      if(nXzDTeZjVx == tDYduRsdZT){eGgwtLFhjf = true;}
      while(kcojQeXGgj == mWWZFWdwAk){uDDRKWohkt = true;}
      while(HYQBuVuAyi == HYQBuVuAyi){lmEiKLEzQH = true;}
      while(tDYduRsdZT == tDYduRsdZT){zrFzdQDqXB = true;}
      if(BucfSCkOIZ == true){BucfSCkOIZ = false;}
      if(XcsMYguSLA == true){XcsMYguSLA = false;}
      if(CeNmbhELnz == true){CeNmbhELnz = false;}
      if(ktgMiMwkhs == true){ktgMiMwkhs = false;}
      if(kfqYKRKLEN == true){kfqYKRKLEN = false;}
      if(WaRYQVgpDk == true){WaRYQVgpDk = false;}
      if(yZaJndufdM == true){yZaJndufdM = false;}
      if(kJjSPVmocK == true){kJjSPVmocK = false;}
      if(XrGZbJcHwN == true){XrGZbJcHwN = false;}
      if(eGgwtLFhjf == true){eGgwtLFhjf = false;}
      if(VdhqcNpyJt == true){VdhqcNpyJt = false;}
      if(hqNrNFSAgd == true){hqNrNFSAgd = false;}
      if(BnjQhebnXD == true){BnjQhebnXD = false;}
      if(QFFwosJOxO == true){QFFwosJOxO = false;}
      if(TdyBemroio == true){TdyBemroio = false;}
      if(sFAFegtRJx == true){sFAFegtRJx = false;}
      if(kCaGdclQDT == true){kCaGdclQDT = false;}
      if(uDDRKWohkt == true){uDDRKWohkt = false;}
      if(lmEiKLEzQH == true){lmEiKLEzQH = false;}
      if(zrFzdQDqXB == true){zrFzdQDqXB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DKNGKZLMFR
{ 
  void fSDOpQMENz()
  { 
      bool WuacGEYpVb = false;
      bool PCenEYcPeG = false;
      bool XKVZhWPjOI = false;
      bool ThGszwydwi = false;
      bool pPujuDIIKt = false;
      bool cGpRRLYAtj = false;
      bool nnbMIgwloI = false;
      bool azTwQIOlde = false;
      bool OHZTfMqobm = false;
      bool WxiLtCmiaO = false;
      bool HVSCTcltAJ = false;
      bool wmVPUfNIfu = false;
      bool oHKCkcPHBN = false;
      bool UfKPXrnXzC = false;
      bool ZxnRpibTpN = false;
      bool neCfZzLQQq = false;
      bool MdrmnQcGrc = false;
      bool rpIdUqTrMC = false;
      bool AwRmYoddoX = false;
      bool gXGHouEAcY = false;
      string oLeMtzbqxf;
      string abPWypxfLn;
      string zbnnFZRRCx;
      string aPYmpAfiNL;
      string wZYuJOhydZ;
      string walNiMWqHT;
      string gJoAEKCbfy;
      string JNSzqYDrdq;
      string rTncAzcKDc;
      string cobsemkXpz;
      string LFRfQiImWJ;
      string JdMPbMVMzF;
      string grXCUTkYUE;
      string neCeemCHLR;
      string ppntTzcLRR;
      string RYYkSTgOKw;
      string xjSRVdbhko;
      string KNAhOpEdiV;
      string qYGCmOGQLK;
      string GnxPTGWVXo;
      if(oLeMtzbqxf == LFRfQiImWJ){WuacGEYpVb = true;}
      else if(LFRfQiImWJ == oLeMtzbqxf){HVSCTcltAJ = true;}
      if(abPWypxfLn == JdMPbMVMzF){PCenEYcPeG = true;}
      else if(JdMPbMVMzF == abPWypxfLn){wmVPUfNIfu = true;}
      if(zbnnFZRRCx == grXCUTkYUE){XKVZhWPjOI = true;}
      else if(grXCUTkYUE == zbnnFZRRCx){oHKCkcPHBN = true;}
      if(aPYmpAfiNL == neCeemCHLR){ThGszwydwi = true;}
      else if(neCeemCHLR == aPYmpAfiNL){UfKPXrnXzC = true;}
      if(wZYuJOhydZ == ppntTzcLRR){pPujuDIIKt = true;}
      else if(ppntTzcLRR == wZYuJOhydZ){ZxnRpibTpN = true;}
      if(walNiMWqHT == RYYkSTgOKw){cGpRRLYAtj = true;}
      else if(RYYkSTgOKw == walNiMWqHT){neCfZzLQQq = true;}
      if(gJoAEKCbfy == xjSRVdbhko){nnbMIgwloI = true;}
      else if(xjSRVdbhko == gJoAEKCbfy){MdrmnQcGrc = true;}
      if(JNSzqYDrdq == KNAhOpEdiV){azTwQIOlde = true;}
      if(rTncAzcKDc == qYGCmOGQLK){OHZTfMqobm = true;}
      if(cobsemkXpz == GnxPTGWVXo){WxiLtCmiaO = true;}
      while(KNAhOpEdiV == JNSzqYDrdq){rpIdUqTrMC = true;}
      while(qYGCmOGQLK == qYGCmOGQLK){AwRmYoddoX = true;}
      while(GnxPTGWVXo == GnxPTGWVXo){gXGHouEAcY = true;}
      if(WuacGEYpVb == true){WuacGEYpVb = false;}
      if(PCenEYcPeG == true){PCenEYcPeG = false;}
      if(XKVZhWPjOI == true){XKVZhWPjOI = false;}
      if(ThGszwydwi == true){ThGszwydwi = false;}
      if(pPujuDIIKt == true){pPujuDIIKt = false;}
      if(cGpRRLYAtj == true){cGpRRLYAtj = false;}
      if(nnbMIgwloI == true){nnbMIgwloI = false;}
      if(azTwQIOlde == true){azTwQIOlde = false;}
      if(OHZTfMqobm == true){OHZTfMqobm = false;}
      if(WxiLtCmiaO == true){WxiLtCmiaO = false;}
      if(HVSCTcltAJ == true){HVSCTcltAJ = false;}
      if(wmVPUfNIfu == true){wmVPUfNIfu = false;}
      if(oHKCkcPHBN == true){oHKCkcPHBN = false;}
      if(UfKPXrnXzC == true){UfKPXrnXzC = false;}
      if(ZxnRpibTpN == true){ZxnRpibTpN = false;}
      if(neCfZzLQQq == true){neCfZzLQQq = false;}
      if(MdrmnQcGrc == true){MdrmnQcGrc = false;}
      if(rpIdUqTrMC == true){rpIdUqTrMC = false;}
      if(AwRmYoddoX == true){AwRmYoddoX = false;}
      if(gXGHouEAcY == true){gXGHouEAcY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OLOEYBIRCW
{ 
  void DKkGKCjHNt()
  { 
      bool woGpmQtKdV = false;
      bool phArultIUV = false;
      bool jyDtyxJZrs = false;
      bool aQFNEGhxod = false;
      bool PYLTJdxsRj = false;
      bool zgIDSxkLro = false;
      bool HTRktZcmno = false;
      bool ExSqFLljkT = false;
      bool zPIIstIBtG = false;
      bool UVFzWuGaYj = false;
      bool BKFbeCNRxH = false;
      bool KBZXprLJqA = false;
      bool QashUhqTTJ = false;
      bool ELKBSoJfcq = false;
      bool gqElwTuhJd = false;
      bool ixjYSaQWHx = false;
      bool LsxnCzpYFA = false;
      bool hfgATZWGlA = false;
      bool lJJpZHblir = false;
      bool XmYfemtPjw = false;
      string WYUSmDrtbN;
      string oihIiLnOmV;
      string ICnufhTGcB;
      string wagTTRdRpf;
      string ZqKypYLwwD;
      string mwERoTkZlF;
      string jlRZQNBNnR;
      string hVYHuRroEH;
      string VXKZOAWOdz;
      string gEfjunZjhc;
      string WxHdUQWwWX;
      string buUeiMbrLQ;
      string pljokdpnLG;
      string rHHbjYQfEx;
      string cZrFXkiBAi;
      string MgYRljMRsq;
      string aikPfTnstK;
      string wumOmPteQA;
      string unnbtKipoz;
      string MylNVtocYD;
      if(WYUSmDrtbN == WxHdUQWwWX){woGpmQtKdV = true;}
      else if(WxHdUQWwWX == WYUSmDrtbN){BKFbeCNRxH = true;}
      if(oihIiLnOmV == buUeiMbrLQ){phArultIUV = true;}
      else if(buUeiMbrLQ == oihIiLnOmV){KBZXprLJqA = true;}
      if(ICnufhTGcB == pljokdpnLG){jyDtyxJZrs = true;}
      else if(pljokdpnLG == ICnufhTGcB){QashUhqTTJ = true;}
      if(wagTTRdRpf == rHHbjYQfEx){aQFNEGhxod = true;}
      else if(rHHbjYQfEx == wagTTRdRpf){ELKBSoJfcq = true;}
      if(ZqKypYLwwD == cZrFXkiBAi){PYLTJdxsRj = true;}
      else if(cZrFXkiBAi == ZqKypYLwwD){gqElwTuhJd = true;}
      if(mwERoTkZlF == MgYRljMRsq){zgIDSxkLro = true;}
      else if(MgYRljMRsq == mwERoTkZlF){ixjYSaQWHx = true;}
      if(jlRZQNBNnR == aikPfTnstK){HTRktZcmno = true;}
      else if(aikPfTnstK == jlRZQNBNnR){LsxnCzpYFA = true;}
      if(hVYHuRroEH == wumOmPteQA){ExSqFLljkT = true;}
      if(VXKZOAWOdz == unnbtKipoz){zPIIstIBtG = true;}
      if(gEfjunZjhc == MylNVtocYD){UVFzWuGaYj = true;}
      while(wumOmPteQA == hVYHuRroEH){hfgATZWGlA = true;}
      while(unnbtKipoz == unnbtKipoz){lJJpZHblir = true;}
      while(MylNVtocYD == MylNVtocYD){XmYfemtPjw = true;}
      if(woGpmQtKdV == true){woGpmQtKdV = false;}
      if(phArultIUV == true){phArultIUV = false;}
      if(jyDtyxJZrs == true){jyDtyxJZrs = false;}
      if(aQFNEGhxod == true){aQFNEGhxod = false;}
      if(PYLTJdxsRj == true){PYLTJdxsRj = false;}
      if(zgIDSxkLro == true){zgIDSxkLro = false;}
      if(HTRktZcmno == true){HTRktZcmno = false;}
      if(ExSqFLljkT == true){ExSqFLljkT = false;}
      if(zPIIstIBtG == true){zPIIstIBtG = false;}
      if(UVFzWuGaYj == true){UVFzWuGaYj = false;}
      if(BKFbeCNRxH == true){BKFbeCNRxH = false;}
      if(KBZXprLJqA == true){KBZXprLJqA = false;}
      if(QashUhqTTJ == true){QashUhqTTJ = false;}
      if(ELKBSoJfcq == true){ELKBSoJfcq = false;}
      if(gqElwTuhJd == true){gqElwTuhJd = false;}
      if(ixjYSaQWHx == true){ixjYSaQWHx = false;}
      if(LsxnCzpYFA == true){LsxnCzpYFA = false;}
      if(hfgATZWGlA == true){hfgATZWGlA = false;}
      if(lJJpZHblir == true){lJJpZHblir = false;}
      if(XmYfemtPjw == true){XmYfemtPjw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHUVDHBMBY
{ 
  void FHUDVZXcxd()
  { 
      bool BHDCrnhfUq = false;
      bool ZynnKOFjek = false;
      bool HoGjVWCiet = false;
      bool XKAmnyORFn = false;
      bool wRwHPYfIzn = false;
      bool RllpFLBTfU = false;
      bool kzAaTOyAAL = false;
      bool AneqoosyTx = false;
      bool qtjqckXJgb = false;
      bool wtkjCxRVnA = false;
      bool ZeHmmdGtAQ = false;
      bool RCzicqOJxh = false;
      bool qnTXOGCunr = false;
      bool XXJSWMlwEy = false;
      bool ecIPJtuCGL = false;
      bool hHXGJkKiYg = false;
      bool aLGIstrgMQ = false;
      bool ESEzCNfDOU = false;
      bool KAncKPzDIk = false;
      bool BCXXXSWAWO = false;
      string OdmyElYoLX;
      string QtQtIlsTLX;
      string TFJaoVXuNf;
      string XxyhroPDTw;
      string rUMBExcIsF;
      string SndCUJTMIi;
      string NcafzSuhBS;
      string VpAOfzrHVr;
      string rOBINjTuNi;
      string UDtkhPsgCk;
      string BuGaicnOWV;
      string QMpQpzaSSO;
      string zAUSxSuOgP;
      string FLFkqxHaZj;
      string wEXrRIMcui;
      string naNmlBZncP;
      string gYhGPEHFZs;
      string qArhRtbbAo;
      string FRTxbdxRzo;
      string WTxJDXWQbM;
      if(OdmyElYoLX == BuGaicnOWV){BHDCrnhfUq = true;}
      else if(BuGaicnOWV == OdmyElYoLX){ZeHmmdGtAQ = true;}
      if(QtQtIlsTLX == QMpQpzaSSO){ZynnKOFjek = true;}
      else if(QMpQpzaSSO == QtQtIlsTLX){RCzicqOJxh = true;}
      if(TFJaoVXuNf == zAUSxSuOgP){HoGjVWCiet = true;}
      else if(zAUSxSuOgP == TFJaoVXuNf){qnTXOGCunr = true;}
      if(XxyhroPDTw == FLFkqxHaZj){XKAmnyORFn = true;}
      else if(FLFkqxHaZj == XxyhroPDTw){XXJSWMlwEy = true;}
      if(rUMBExcIsF == wEXrRIMcui){wRwHPYfIzn = true;}
      else if(wEXrRIMcui == rUMBExcIsF){ecIPJtuCGL = true;}
      if(SndCUJTMIi == naNmlBZncP){RllpFLBTfU = true;}
      else if(naNmlBZncP == SndCUJTMIi){hHXGJkKiYg = true;}
      if(NcafzSuhBS == gYhGPEHFZs){kzAaTOyAAL = true;}
      else if(gYhGPEHFZs == NcafzSuhBS){aLGIstrgMQ = true;}
      if(VpAOfzrHVr == qArhRtbbAo){AneqoosyTx = true;}
      if(rOBINjTuNi == FRTxbdxRzo){qtjqckXJgb = true;}
      if(UDtkhPsgCk == WTxJDXWQbM){wtkjCxRVnA = true;}
      while(qArhRtbbAo == VpAOfzrHVr){ESEzCNfDOU = true;}
      while(FRTxbdxRzo == FRTxbdxRzo){KAncKPzDIk = true;}
      while(WTxJDXWQbM == WTxJDXWQbM){BCXXXSWAWO = true;}
      if(BHDCrnhfUq == true){BHDCrnhfUq = false;}
      if(ZynnKOFjek == true){ZynnKOFjek = false;}
      if(HoGjVWCiet == true){HoGjVWCiet = false;}
      if(XKAmnyORFn == true){XKAmnyORFn = false;}
      if(wRwHPYfIzn == true){wRwHPYfIzn = false;}
      if(RllpFLBTfU == true){RllpFLBTfU = false;}
      if(kzAaTOyAAL == true){kzAaTOyAAL = false;}
      if(AneqoosyTx == true){AneqoosyTx = false;}
      if(qtjqckXJgb == true){qtjqckXJgb = false;}
      if(wtkjCxRVnA == true){wtkjCxRVnA = false;}
      if(ZeHmmdGtAQ == true){ZeHmmdGtAQ = false;}
      if(RCzicqOJxh == true){RCzicqOJxh = false;}
      if(qnTXOGCunr == true){qnTXOGCunr = false;}
      if(XXJSWMlwEy == true){XXJSWMlwEy = false;}
      if(ecIPJtuCGL == true){ecIPJtuCGL = false;}
      if(hHXGJkKiYg == true){hHXGJkKiYg = false;}
      if(aLGIstrgMQ == true){aLGIstrgMQ = false;}
      if(ESEzCNfDOU == true){ESEzCNfDOU = false;}
      if(KAncKPzDIk == true){KAncKPzDIk = false;}
      if(BCXXXSWAWO == true){BCXXXSWAWO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UMPKHTEHUV
{ 
  void SuRIBxhRXD()
  { 
      bool BxJUrgOmtI = false;
      bool mUXXgEqzRT = false;
      bool KkIMTXdNIl = false;
      bool yHPyuleXbk = false;
      bool udnEHnKgjU = false;
      bool HmUfqQnxAU = false;
      bool DBeIKfEYcu = false;
      bool ZTXfXgwEEf = false;
      bool MxcmeKmiGd = false;
      bool xhWHhtzftb = false;
      bool ikDounPnIK = false;
      bool UjrUHFXqdz = false;
      bool rVSyxqwQyc = false;
      bool gPKbwbsnrp = false;
      bool uzawJNoCAb = false;
      bool WHBtjNSFrD = false;
      bool qyoecEYQXe = false;
      bool MjzmEstWni = false;
      bool CtQWGZOQri = false;
      bool JmunzwKwSF = false;
      string SXmfCYDnpL;
      string qIVwUNVTPF;
      string rteRUJxdUY;
      string mGINTxQNLm;
      string yclTXwliNR;
      string HgNWzXrVKr;
      string bZSQXkzIcX;
      string xIIcGPHKsY;
      string WNPDQGrkOu;
      string EuCSKYJUwm;
      string wdGoTyYkQj;
      string PhbkVNJOAR;
      string rOtgTCFoRg;
      string FmNGcrHaiR;
      string gGUdfVSRxx;
      string PtUetgjYVR;
      string riTidcTUHc;
      string FifhjksPBx;
      string jnrTRKRiMu;
      string IhERYymlAC;
      if(SXmfCYDnpL == wdGoTyYkQj){BxJUrgOmtI = true;}
      else if(wdGoTyYkQj == SXmfCYDnpL){ikDounPnIK = true;}
      if(qIVwUNVTPF == PhbkVNJOAR){mUXXgEqzRT = true;}
      else if(PhbkVNJOAR == qIVwUNVTPF){UjrUHFXqdz = true;}
      if(rteRUJxdUY == rOtgTCFoRg){KkIMTXdNIl = true;}
      else if(rOtgTCFoRg == rteRUJxdUY){rVSyxqwQyc = true;}
      if(mGINTxQNLm == FmNGcrHaiR){yHPyuleXbk = true;}
      else if(FmNGcrHaiR == mGINTxQNLm){gPKbwbsnrp = true;}
      if(yclTXwliNR == gGUdfVSRxx){udnEHnKgjU = true;}
      else if(gGUdfVSRxx == yclTXwliNR){uzawJNoCAb = true;}
      if(HgNWzXrVKr == PtUetgjYVR){HmUfqQnxAU = true;}
      else if(PtUetgjYVR == HgNWzXrVKr){WHBtjNSFrD = true;}
      if(bZSQXkzIcX == riTidcTUHc){DBeIKfEYcu = true;}
      else if(riTidcTUHc == bZSQXkzIcX){qyoecEYQXe = true;}
      if(xIIcGPHKsY == FifhjksPBx){ZTXfXgwEEf = true;}
      if(WNPDQGrkOu == jnrTRKRiMu){MxcmeKmiGd = true;}
      if(EuCSKYJUwm == IhERYymlAC){xhWHhtzftb = true;}
      while(FifhjksPBx == xIIcGPHKsY){MjzmEstWni = true;}
      while(jnrTRKRiMu == jnrTRKRiMu){CtQWGZOQri = true;}
      while(IhERYymlAC == IhERYymlAC){JmunzwKwSF = true;}
      if(BxJUrgOmtI == true){BxJUrgOmtI = false;}
      if(mUXXgEqzRT == true){mUXXgEqzRT = false;}
      if(KkIMTXdNIl == true){KkIMTXdNIl = false;}
      if(yHPyuleXbk == true){yHPyuleXbk = false;}
      if(udnEHnKgjU == true){udnEHnKgjU = false;}
      if(HmUfqQnxAU == true){HmUfqQnxAU = false;}
      if(DBeIKfEYcu == true){DBeIKfEYcu = false;}
      if(ZTXfXgwEEf == true){ZTXfXgwEEf = false;}
      if(MxcmeKmiGd == true){MxcmeKmiGd = false;}
      if(xhWHhtzftb == true){xhWHhtzftb = false;}
      if(ikDounPnIK == true){ikDounPnIK = false;}
      if(UjrUHFXqdz == true){UjrUHFXqdz = false;}
      if(rVSyxqwQyc == true){rVSyxqwQyc = false;}
      if(gPKbwbsnrp == true){gPKbwbsnrp = false;}
      if(uzawJNoCAb == true){uzawJNoCAb = false;}
      if(WHBtjNSFrD == true){WHBtjNSFrD = false;}
      if(qyoecEYQXe == true){qyoecEYQXe = false;}
      if(MjzmEstWni == true){MjzmEstWni = false;}
      if(CtQWGZOQri == true){CtQWGZOQri = false;}
      if(JmunzwKwSF == true){JmunzwKwSF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LYJKMZCNRQ
{ 
  void MnRLPAAcLX()
  { 
      bool nZecknneQS = false;
      bool WbweklpGIz = false;
      bool CdpdSDyMKc = false;
      bool cWdnPVdAjt = false;
      bool bfdcqbWDMP = false;
      bool QHxHZJiAJg = false;
      bool obTmpAyHOO = false;
      bool HpVNXVANmq = false;
      bool guzuMVZVOG = false;
      bool mdpCFAMqmq = false;
      bool dOnxHakiiD = false;
      bool JVNSztbXaU = false;
      bool absIbdzTIX = false;
      bool JIZuNSHBnk = false;
      bool jpmLwRPXCL = false;
      bool XnPSQBVeVd = false;
      bool bRaLsAuSFg = false;
      bool lZjojjnhMK = false;
      bool NaQxzUrHeL = false;
      bool xceKJSPbRw = false;
      string JrEbmoemGd;
      string PSknPPueGz;
      string wpLNdNjQcU;
      string qoDcZPyeMQ;
      string ewlBQochAH;
      string sQtNcTfqxY;
      string FNKkmaPHNA;
      string QPRoTzDKwo;
      string kBQVaatpAG;
      string iHgnLRlBNp;
      string ZUUzpdyFsc;
      string PVtImDxnJM;
      string fZHHQJhddC;
      string NCwGOQfQex;
      string bowWpNNYAI;
      string TxqBJAMNhg;
      string uUbpPNZmsW;
      string WfJMkqckQD;
      string wJdUhPKuwO;
      string DShxBHNFHb;
      if(JrEbmoemGd == ZUUzpdyFsc){nZecknneQS = true;}
      else if(ZUUzpdyFsc == JrEbmoemGd){dOnxHakiiD = true;}
      if(PSknPPueGz == PVtImDxnJM){WbweklpGIz = true;}
      else if(PVtImDxnJM == PSknPPueGz){JVNSztbXaU = true;}
      if(wpLNdNjQcU == fZHHQJhddC){CdpdSDyMKc = true;}
      else if(fZHHQJhddC == wpLNdNjQcU){absIbdzTIX = true;}
      if(qoDcZPyeMQ == NCwGOQfQex){cWdnPVdAjt = true;}
      else if(NCwGOQfQex == qoDcZPyeMQ){JIZuNSHBnk = true;}
      if(ewlBQochAH == bowWpNNYAI){bfdcqbWDMP = true;}
      else if(bowWpNNYAI == ewlBQochAH){jpmLwRPXCL = true;}
      if(sQtNcTfqxY == TxqBJAMNhg){QHxHZJiAJg = true;}
      else if(TxqBJAMNhg == sQtNcTfqxY){XnPSQBVeVd = true;}
      if(FNKkmaPHNA == uUbpPNZmsW){obTmpAyHOO = true;}
      else if(uUbpPNZmsW == FNKkmaPHNA){bRaLsAuSFg = true;}
      if(QPRoTzDKwo == WfJMkqckQD){HpVNXVANmq = true;}
      if(kBQVaatpAG == wJdUhPKuwO){guzuMVZVOG = true;}
      if(iHgnLRlBNp == DShxBHNFHb){mdpCFAMqmq = true;}
      while(WfJMkqckQD == QPRoTzDKwo){lZjojjnhMK = true;}
      while(wJdUhPKuwO == wJdUhPKuwO){NaQxzUrHeL = true;}
      while(DShxBHNFHb == DShxBHNFHb){xceKJSPbRw = true;}
      if(nZecknneQS == true){nZecknneQS = false;}
      if(WbweklpGIz == true){WbweklpGIz = false;}
      if(CdpdSDyMKc == true){CdpdSDyMKc = false;}
      if(cWdnPVdAjt == true){cWdnPVdAjt = false;}
      if(bfdcqbWDMP == true){bfdcqbWDMP = false;}
      if(QHxHZJiAJg == true){QHxHZJiAJg = false;}
      if(obTmpAyHOO == true){obTmpAyHOO = false;}
      if(HpVNXVANmq == true){HpVNXVANmq = false;}
      if(guzuMVZVOG == true){guzuMVZVOG = false;}
      if(mdpCFAMqmq == true){mdpCFAMqmq = false;}
      if(dOnxHakiiD == true){dOnxHakiiD = false;}
      if(JVNSztbXaU == true){JVNSztbXaU = false;}
      if(absIbdzTIX == true){absIbdzTIX = false;}
      if(JIZuNSHBnk == true){JIZuNSHBnk = false;}
      if(jpmLwRPXCL == true){jpmLwRPXCL = false;}
      if(XnPSQBVeVd == true){XnPSQBVeVd = false;}
      if(bRaLsAuSFg == true){bRaLsAuSFg = false;}
      if(lZjojjnhMK == true){lZjojjnhMK = false;}
      if(NaQxzUrHeL == true){NaQxzUrHeL = false;}
      if(xceKJSPbRw == true){xceKJSPbRw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWCYHVRQMO
{ 
  void mdooVOcqFC()
  { 
      bool jLAqZemXDI = false;
      bool FxXfKSGSCh = false;
      bool maLWADFPQD = false;
      bool pYrwBjlYIS = false;
      bool ndHuNMitzN = false;
      bool RAZuSJAdqV = false;
      bool ZXHzSfEbea = false;
      bool ggKisISQIm = false;
      bool ULPCkpzwdq = false;
      bool iHglsQVHch = false;
      bool IGOYfjopCJ = false;
      bool pjUDBNHENb = false;
      bool gHymqYzYoc = false;
      bool lKmaeNwqVB = false;
      bool AItTAzmdjf = false;
      bool IRtAAAIbgH = false;
      bool jQBZWfwtXm = false;
      bool QQhMbXMdlr = false;
      bool lVnJTUQmZe = false;
      bool FUJOQjHUwU = false;
      string eZbmfampto;
      string RIeBctSrRP;
      string inDaLkeyFo;
      string gBqgxVMhjX;
      string WoKKKBcagL;
      string TwNDspVAau;
      string unkFHPRyEH;
      string hkHtrtcsPK;
      string HEQsVjmmmH;
      string zLHobhEFCt;
      string jdWZcioSKz;
      string McjQmqWqjW;
      string cdKwHWcSSJ;
      string oXpUZcgqQl;
      string uTcntWaqBj;
      string LNVeRGTZRG;
      string FWAAJolOpJ;
      string KfZxbIBWCk;
      string ulQhybCLDT;
      string JGZKgXSbdF;
      if(eZbmfampto == jdWZcioSKz){jLAqZemXDI = true;}
      else if(jdWZcioSKz == eZbmfampto){IGOYfjopCJ = true;}
      if(RIeBctSrRP == McjQmqWqjW){FxXfKSGSCh = true;}
      else if(McjQmqWqjW == RIeBctSrRP){pjUDBNHENb = true;}
      if(inDaLkeyFo == cdKwHWcSSJ){maLWADFPQD = true;}
      else if(cdKwHWcSSJ == inDaLkeyFo){gHymqYzYoc = true;}
      if(gBqgxVMhjX == oXpUZcgqQl){pYrwBjlYIS = true;}
      else if(oXpUZcgqQl == gBqgxVMhjX){lKmaeNwqVB = true;}
      if(WoKKKBcagL == uTcntWaqBj){ndHuNMitzN = true;}
      else if(uTcntWaqBj == WoKKKBcagL){AItTAzmdjf = true;}
      if(TwNDspVAau == LNVeRGTZRG){RAZuSJAdqV = true;}
      else if(LNVeRGTZRG == TwNDspVAau){IRtAAAIbgH = true;}
      if(unkFHPRyEH == FWAAJolOpJ){ZXHzSfEbea = true;}
      else if(FWAAJolOpJ == unkFHPRyEH){jQBZWfwtXm = true;}
      if(hkHtrtcsPK == KfZxbIBWCk){ggKisISQIm = true;}
      if(HEQsVjmmmH == ulQhybCLDT){ULPCkpzwdq = true;}
      if(zLHobhEFCt == JGZKgXSbdF){iHglsQVHch = true;}
      while(KfZxbIBWCk == hkHtrtcsPK){QQhMbXMdlr = true;}
      while(ulQhybCLDT == ulQhybCLDT){lVnJTUQmZe = true;}
      while(JGZKgXSbdF == JGZKgXSbdF){FUJOQjHUwU = true;}
      if(jLAqZemXDI == true){jLAqZemXDI = false;}
      if(FxXfKSGSCh == true){FxXfKSGSCh = false;}
      if(maLWADFPQD == true){maLWADFPQD = false;}
      if(pYrwBjlYIS == true){pYrwBjlYIS = false;}
      if(ndHuNMitzN == true){ndHuNMitzN = false;}
      if(RAZuSJAdqV == true){RAZuSJAdqV = false;}
      if(ZXHzSfEbea == true){ZXHzSfEbea = false;}
      if(ggKisISQIm == true){ggKisISQIm = false;}
      if(ULPCkpzwdq == true){ULPCkpzwdq = false;}
      if(iHglsQVHch == true){iHglsQVHch = false;}
      if(IGOYfjopCJ == true){IGOYfjopCJ = false;}
      if(pjUDBNHENb == true){pjUDBNHENb = false;}
      if(gHymqYzYoc == true){gHymqYzYoc = false;}
      if(lKmaeNwqVB == true){lKmaeNwqVB = false;}
      if(AItTAzmdjf == true){AItTAzmdjf = false;}
      if(IRtAAAIbgH == true){IRtAAAIbgH = false;}
      if(jQBZWfwtXm == true){jQBZWfwtXm = false;}
      if(QQhMbXMdlr == true){QQhMbXMdlr = false;}
      if(lVnJTUQmZe == true){lVnJTUQmZe = false;}
      if(FUJOQjHUwU == true){FUJOQjHUwU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZLIZXZKXVT
{ 
  void hubuwkhmds()
  { 
      bool hzFgFMYLyh = false;
      bool PupOxcRtVC = false;
      bool TUIIYVRhak = false;
      bool ByZooYyaoS = false;
      bool OaLCtUmcDP = false;
      bool GfojaNpwHj = false;
      bool upjMgQUAZY = false;
      bool epEDmsIGNE = false;
      bool hndLdUJoOa = false;
      bool hBSFWXpyUd = false;
      bool zmCejPbkwg = false;
      bool EjhDBHMXhL = false;
      bool HflypcXygO = false;
      bool DJkjEulzbO = false;
      bool sXsgWxTPEP = false;
      bool LRPJVTAEnG = false;
      bool rcEgdtzxyF = false;
      bool VNwTRjlFbr = false;
      bool JHtQDktbOj = false;
      bool ugKUVQSLCb = false;
      string IZrEuPsMbU;
      string RVQyZRTayC;
      string uszETQqJtz;
      string POgNmiTNNj;
      string rhCTFlyYLj;
      string PPFOyOamke;
      string XjRcFCoCKq;
      string xFMNKMqezg;
      string RSxKizIROY;
      string HgciLIQYND;
      string xuNUlJCrEl;
      string XunDMFlHsG;
      string sXnliQcdBC;
      string wRRujWFcXZ;
      string xQNbBMrYWG;
      string VIeHKZGakV;
      string gYpCpGdsTo;
      string AIjTJbJLkW;
      string XDHufmlJjK;
      string PdqBrXaLlu;
      if(IZrEuPsMbU == xuNUlJCrEl){hzFgFMYLyh = true;}
      else if(xuNUlJCrEl == IZrEuPsMbU){zmCejPbkwg = true;}
      if(RVQyZRTayC == XunDMFlHsG){PupOxcRtVC = true;}
      else if(XunDMFlHsG == RVQyZRTayC){EjhDBHMXhL = true;}
      if(uszETQqJtz == sXnliQcdBC){TUIIYVRhak = true;}
      else if(sXnliQcdBC == uszETQqJtz){HflypcXygO = true;}
      if(POgNmiTNNj == wRRujWFcXZ){ByZooYyaoS = true;}
      else if(wRRujWFcXZ == POgNmiTNNj){DJkjEulzbO = true;}
      if(rhCTFlyYLj == xQNbBMrYWG){OaLCtUmcDP = true;}
      else if(xQNbBMrYWG == rhCTFlyYLj){sXsgWxTPEP = true;}
      if(PPFOyOamke == VIeHKZGakV){GfojaNpwHj = true;}
      else if(VIeHKZGakV == PPFOyOamke){LRPJVTAEnG = true;}
      if(XjRcFCoCKq == gYpCpGdsTo){upjMgQUAZY = true;}
      else if(gYpCpGdsTo == XjRcFCoCKq){rcEgdtzxyF = true;}
      if(xFMNKMqezg == AIjTJbJLkW){epEDmsIGNE = true;}
      if(RSxKizIROY == XDHufmlJjK){hndLdUJoOa = true;}
      if(HgciLIQYND == PdqBrXaLlu){hBSFWXpyUd = true;}
      while(AIjTJbJLkW == xFMNKMqezg){VNwTRjlFbr = true;}
      while(XDHufmlJjK == XDHufmlJjK){JHtQDktbOj = true;}
      while(PdqBrXaLlu == PdqBrXaLlu){ugKUVQSLCb = true;}
      if(hzFgFMYLyh == true){hzFgFMYLyh = false;}
      if(PupOxcRtVC == true){PupOxcRtVC = false;}
      if(TUIIYVRhak == true){TUIIYVRhak = false;}
      if(ByZooYyaoS == true){ByZooYyaoS = false;}
      if(OaLCtUmcDP == true){OaLCtUmcDP = false;}
      if(GfojaNpwHj == true){GfojaNpwHj = false;}
      if(upjMgQUAZY == true){upjMgQUAZY = false;}
      if(epEDmsIGNE == true){epEDmsIGNE = false;}
      if(hndLdUJoOa == true){hndLdUJoOa = false;}
      if(hBSFWXpyUd == true){hBSFWXpyUd = false;}
      if(zmCejPbkwg == true){zmCejPbkwg = false;}
      if(EjhDBHMXhL == true){EjhDBHMXhL = false;}
      if(HflypcXygO == true){HflypcXygO = false;}
      if(DJkjEulzbO == true){DJkjEulzbO = false;}
      if(sXsgWxTPEP == true){sXsgWxTPEP = false;}
      if(LRPJVTAEnG == true){LRPJVTAEnG = false;}
      if(rcEgdtzxyF == true){rcEgdtzxyF = false;}
      if(VNwTRjlFbr == true){VNwTRjlFbr = false;}
      if(JHtQDktbOj == true){JHtQDktbOj = false;}
      if(ugKUVQSLCb == true){ugKUVQSLCb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QCOMISNRLI
{ 
  void pafhtnyNgR()
  { 
      bool RhZpULVinB = false;
      bool jtoCQxlcJl = false;
      bool zVmBqbwwBl = false;
      bool AVemuOzwFp = false;
      bool xGrCjcjTuV = false;
      bool BZbGbuuYzr = false;
      bool PYgBBOOCGC = false;
      bool xoWSorcjQO = false;
      bool rcBekasYLz = false;
      bool SZxNaXYqAV = false;
      bool NgMrXLDIQi = false;
      bool RKIkzmXCQa = false;
      bool UpqGiXrJrR = false;
      bool TliuALPJHZ = false;
      bool XkHbhHRMNn = false;
      bool AWaZBXpFJA = false;
      bool TtQzOfbMjn = false;
      bool WOtpDjhOYa = false;
      bool FfuDRxLItc = false;
      bool UKAGFdTINB = false;
      string AOgjjDclRO;
      string ZutFUxLsoo;
      string TNRGxzOlrX;
      string wIzSgRAOsp;
      string YHHTgqREBg;
      string oRAJPlxZlj;
      string nptsRRuaXD;
      string wxAzPLGxYG;
      string gJkKieHpDu;
      string UZbIBiNNBP;
      string uqgyjrRBsD;
      string fzAfDeEiKm;
      string JEXchVUrxg;
      string yruJKpclZp;
      string MGxzOUYuEW;
      string deDOFqSDPN;
      string WZDLFnDqUN;
      string BSIUZDGYNN;
      string xZmaCSogET;
      string WYVLSmCksa;
      if(AOgjjDclRO == uqgyjrRBsD){RhZpULVinB = true;}
      else if(uqgyjrRBsD == AOgjjDclRO){NgMrXLDIQi = true;}
      if(ZutFUxLsoo == fzAfDeEiKm){jtoCQxlcJl = true;}
      else if(fzAfDeEiKm == ZutFUxLsoo){RKIkzmXCQa = true;}
      if(TNRGxzOlrX == JEXchVUrxg){zVmBqbwwBl = true;}
      else if(JEXchVUrxg == TNRGxzOlrX){UpqGiXrJrR = true;}
      if(wIzSgRAOsp == yruJKpclZp){AVemuOzwFp = true;}
      else if(yruJKpclZp == wIzSgRAOsp){TliuALPJHZ = true;}
      if(YHHTgqREBg == MGxzOUYuEW){xGrCjcjTuV = true;}
      else if(MGxzOUYuEW == YHHTgqREBg){XkHbhHRMNn = true;}
      if(oRAJPlxZlj == deDOFqSDPN){BZbGbuuYzr = true;}
      else if(deDOFqSDPN == oRAJPlxZlj){AWaZBXpFJA = true;}
      if(nptsRRuaXD == WZDLFnDqUN){PYgBBOOCGC = true;}
      else if(WZDLFnDqUN == nptsRRuaXD){TtQzOfbMjn = true;}
      if(wxAzPLGxYG == BSIUZDGYNN){xoWSorcjQO = true;}
      if(gJkKieHpDu == xZmaCSogET){rcBekasYLz = true;}
      if(UZbIBiNNBP == WYVLSmCksa){SZxNaXYqAV = true;}
      while(BSIUZDGYNN == wxAzPLGxYG){WOtpDjhOYa = true;}
      while(xZmaCSogET == xZmaCSogET){FfuDRxLItc = true;}
      while(WYVLSmCksa == WYVLSmCksa){UKAGFdTINB = true;}
      if(RhZpULVinB == true){RhZpULVinB = false;}
      if(jtoCQxlcJl == true){jtoCQxlcJl = false;}
      if(zVmBqbwwBl == true){zVmBqbwwBl = false;}
      if(AVemuOzwFp == true){AVemuOzwFp = false;}
      if(xGrCjcjTuV == true){xGrCjcjTuV = false;}
      if(BZbGbuuYzr == true){BZbGbuuYzr = false;}
      if(PYgBBOOCGC == true){PYgBBOOCGC = false;}
      if(xoWSorcjQO == true){xoWSorcjQO = false;}
      if(rcBekasYLz == true){rcBekasYLz = false;}
      if(SZxNaXYqAV == true){SZxNaXYqAV = false;}
      if(NgMrXLDIQi == true){NgMrXLDIQi = false;}
      if(RKIkzmXCQa == true){RKIkzmXCQa = false;}
      if(UpqGiXrJrR == true){UpqGiXrJrR = false;}
      if(TliuALPJHZ == true){TliuALPJHZ = false;}
      if(XkHbhHRMNn == true){XkHbhHRMNn = false;}
      if(AWaZBXpFJA == true){AWaZBXpFJA = false;}
      if(TtQzOfbMjn == true){TtQzOfbMjn = false;}
      if(WOtpDjhOYa == true){WOtpDjhOYa = false;}
      if(FfuDRxLItc == true){FfuDRxLItc = false;}
      if(UKAGFdTINB == true){UKAGFdTINB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KTBEIMTOFN
{ 
  void aPHIgUmgCQ()
  { 
      bool ssSCCgjimg = false;
      bool TrjGZsfBIG = false;
      bool tkWsIJSjYB = false;
      bool AIfxfZMzKz = false;
      bool pfdKYmxSFR = false;
      bool TmMwtIVYsr = false;
      bool NzKkfKLlaA = false;
      bool gfpIQNHMUV = false;
      bool MzdHgNujDX = false;
      bool EmFSlqVrdN = false;
      bool aKrFjmwEff = false;
      bool AIDXfOUCES = false;
      bool PbiDwsZXWZ = false;
      bool qOhHtCHYWs = false;
      bool QqDWWujhlX = false;
      bool VSnLyzanJp = false;
      bool MYgGokZwdc = false;
      bool GwfKBXXLgA = false;
      bool JrkzDXaVIt = false;
      bool aTOffrKxhk = false;
      string nRVLQBnIex;
      string XcgiEzAQxN;
      string sXjQIQsfXR;
      string JAhSHhojmy;
      string gaBKmgLhXd;
      string YDXbZPgFDA;
      string HHjMnWtNbW;
      string KPdzfRWZdb;
      string ELHtrGcGsq;
      string BiflpZqnVP;
      string lxGBTIYXuI;
      string sGbbuwzpUh;
      string tnUjUajrIG;
      string aiENoHEGZj;
      string gEKkyuHEpt;
      string ZATnVxbWfs;
      string YgPogJBOln;
      string qsQjBodjlY;
      string SeBNgZPQqr;
      string ehZfLzoVDn;
      if(nRVLQBnIex == lxGBTIYXuI){ssSCCgjimg = true;}
      else if(lxGBTIYXuI == nRVLQBnIex){aKrFjmwEff = true;}
      if(XcgiEzAQxN == sGbbuwzpUh){TrjGZsfBIG = true;}
      else if(sGbbuwzpUh == XcgiEzAQxN){AIDXfOUCES = true;}
      if(sXjQIQsfXR == tnUjUajrIG){tkWsIJSjYB = true;}
      else if(tnUjUajrIG == sXjQIQsfXR){PbiDwsZXWZ = true;}
      if(JAhSHhojmy == aiENoHEGZj){AIfxfZMzKz = true;}
      else if(aiENoHEGZj == JAhSHhojmy){qOhHtCHYWs = true;}
      if(gaBKmgLhXd == gEKkyuHEpt){pfdKYmxSFR = true;}
      else if(gEKkyuHEpt == gaBKmgLhXd){QqDWWujhlX = true;}
      if(YDXbZPgFDA == ZATnVxbWfs){TmMwtIVYsr = true;}
      else if(ZATnVxbWfs == YDXbZPgFDA){VSnLyzanJp = true;}
      if(HHjMnWtNbW == YgPogJBOln){NzKkfKLlaA = true;}
      else if(YgPogJBOln == HHjMnWtNbW){MYgGokZwdc = true;}
      if(KPdzfRWZdb == qsQjBodjlY){gfpIQNHMUV = true;}
      if(ELHtrGcGsq == SeBNgZPQqr){MzdHgNujDX = true;}
      if(BiflpZqnVP == ehZfLzoVDn){EmFSlqVrdN = true;}
      while(qsQjBodjlY == KPdzfRWZdb){GwfKBXXLgA = true;}
      while(SeBNgZPQqr == SeBNgZPQqr){JrkzDXaVIt = true;}
      while(ehZfLzoVDn == ehZfLzoVDn){aTOffrKxhk = true;}
      if(ssSCCgjimg == true){ssSCCgjimg = false;}
      if(TrjGZsfBIG == true){TrjGZsfBIG = false;}
      if(tkWsIJSjYB == true){tkWsIJSjYB = false;}
      if(AIfxfZMzKz == true){AIfxfZMzKz = false;}
      if(pfdKYmxSFR == true){pfdKYmxSFR = false;}
      if(TmMwtIVYsr == true){TmMwtIVYsr = false;}
      if(NzKkfKLlaA == true){NzKkfKLlaA = false;}
      if(gfpIQNHMUV == true){gfpIQNHMUV = false;}
      if(MzdHgNujDX == true){MzdHgNujDX = false;}
      if(EmFSlqVrdN == true){EmFSlqVrdN = false;}
      if(aKrFjmwEff == true){aKrFjmwEff = false;}
      if(AIDXfOUCES == true){AIDXfOUCES = false;}
      if(PbiDwsZXWZ == true){PbiDwsZXWZ = false;}
      if(qOhHtCHYWs == true){qOhHtCHYWs = false;}
      if(QqDWWujhlX == true){QqDWWujhlX = false;}
      if(VSnLyzanJp == true){VSnLyzanJp = false;}
      if(MYgGokZwdc == true){MYgGokZwdc = false;}
      if(GwfKBXXLgA == true){GwfKBXXLgA = false;}
      if(JrkzDXaVIt == true){JrkzDXaVIt = false;}
      if(aTOffrKxhk == true){aTOffrKxhk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHBJJRQHIH
{ 
  void rKLHOmeASB()
  { 
      bool SOJVJnWLoG = false;
      bool HmEIsyeYoV = false;
      bool SinjYuziCs = false;
      bool MTfkPPmwkO = false;
      bool ZOhnYhgeCS = false;
      bool zeSBTiaYxO = false;
      bool nmJusnHSsd = false;
      bool LimZwDBzLq = false;
      bool NTgithAdQf = false;
      bool nOyWZlFluj = false;
      bool aNlXHPqsFQ = false;
      bool haNGBTGZAK = false;
      bool ncCMoxjQzJ = false;
      bool xOEaPzhIbe = false;
      bool qHXAyNArUG = false;
      bool ffkjwxLZiK = false;
      bool easwSTVlpB = false;
      bool lxyVTgEBOa = false;
      bool wruscRcUeS = false;
      bool mHZQzPNbgd = false;
      string dOkpmRLJAs;
      string fRiuqBxUMX;
      string SEUHhlVKri;
      string lMTdHNbQTk;
      string wRgUdHpWdY;
      string BfhxTYsdIA;
      string wAQQGSxFnc;
      string ZgBbaAXAca;
      string wyfShGdVKh;
      string TxITowAPNL;
      string KkiAzTeGWS;
      string BsAgExTyiA;
      string natFJbXgle;
      string zHlRPKPfSN;
      string bXzqgaxaPq;
      string bCgNWipcqX;
      string wxTqTsHhRs;
      string gneUXQaDYh;
      string dxRuCxaXtg;
      string UlnuRdDHXm;
      if(dOkpmRLJAs == KkiAzTeGWS){SOJVJnWLoG = true;}
      else if(KkiAzTeGWS == dOkpmRLJAs){aNlXHPqsFQ = true;}
      if(fRiuqBxUMX == BsAgExTyiA){HmEIsyeYoV = true;}
      else if(BsAgExTyiA == fRiuqBxUMX){haNGBTGZAK = true;}
      if(SEUHhlVKri == natFJbXgle){SinjYuziCs = true;}
      else if(natFJbXgle == SEUHhlVKri){ncCMoxjQzJ = true;}
      if(lMTdHNbQTk == zHlRPKPfSN){MTfkPPmwkO = true;}
      else if(zHlRPKPfSN == lMTdHNbQTk){xOEaPzhIbe = true;}
      if(wRgUdHpWdY == bXzqgaxaPq){ZOhnYhgeCS = true;}
      else if(bXzqgaxaPq == wRgUdHpWdY){qHXAyNArUG = true;}
      if(BfhxTYsdIA == bCgNWipcqX){zeSBTiaYxO = true;}
      else if(bCgNWipcqX == BfhxTYsdIA){ffkjwxLZiK = true;}
      if(wAQQGSxFnc == wxTqTsHhRs){nmJusnHSsd = true;}
      else if(wxTqTsHhRs == wAQQGSxFnc){easwSTVlpB = true;}
      if(ZgBbaAXAca == gneUXQaDYh){LimZwDBzLq = true;}
      if(wyfShGdVKh == dxRuCxaXtg){NTgithAdQf = true;}
      if(TxITowAPNL == UlnuRdDHXm){nOyWZlFluj = true;}
      while(gneUXQaDYh == ZgBbaAXAca){lxyVTgEBOa = true;}
      while(dxRuCxaXtg == dxRuCxaXtg){wruscRcUeS = true;}
      while(UlnuRdDHXm == UlnuRdDHXm){mHZQzPNbgd = true;}
      if(SOJVJnWLoG == true){SOJVJnWLoG = false;}
      if(HmEIsyeYoV == true){HmEIsyeYoV = false;}
      if(SinjYuziCs == true){SinjYuziCs = false;}
      if(MTfkPPmwkO == true){MTfkPPmwkO = false;}
      if(ZOhnYhgeCS == true){ZOhnYhgeCS = false;}
      if(zeSBTiaYxO == true){zeSBTiaYxO = false;}
      if(nmJusnHSsd == true){nmJusnHSsd = false;}
      if(LimZwDBzLq == true){LimZwDBzLq = false;}
      if(NTgithAdQf == true){NTgithAdQf = false;}
      if(nOyWZlFluj == true){nOyWZlFluj = false;}
      if(aNlXHPqsFQ == true){aNlXHPqsFQ = false;}
      if(haNGBTGZAK == true){haNGBTGZAK = false;}
      if(ncCMoxjQzJ == true){ncCMoxjQzJ = false;}
      if(xOEaPzhIbe == true){xOEaPzhIbe = false;}
      if(qHXAyNArUG == true){qHXAyNArUG = false;}
      if(ffkjwxLZiK == true){ffkjwxLZiK = false;}
      if(easwSTVlpB == true){easwSTVlpB = false;}
      if(lxyVTgEBOa == true){lxyVTgEBOa = false;}
      if(wruscRcUeS == true){wruscRcUeS = false;}
      if(mHZQzPNbgd == true){mHZQzPNbgd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JHRFTUJWMP
{ 
  void LKzrIWCeKA()
  { 
      bool fqIfEjqZDV = false;
      bool bouyZrSnxj = false;
      bool pBzOwVFIHe = false;
      bool gRfILIVuXa = false;
      bool gNhASbcaiw = false;
      bool URIiCdqtjh = false;
      bool dhRYnKJllQ = false;
      bool WWPWDcSyuU = false;
      bool rdZKJOIxGg = false;
      bool RaLpwyuJLI = false;
      bool RqnRZyCkfZ = false;
      bool LszPpAIHOY = false;
      bool BMfFzwLZaE = false;
      bool gImmCBpHkL = false;
      bool MXRfVXbuzw = false;
      bool onulHFKiSc = false;
      bool lcJarCGLNo = false;
      bool JBVCMctzia = false;
      bool TPZePrNAew = false;
      bool pHnHZjNqmS = false;
      string snfkHMGFNB;
      string QmlabibiQu;
      string XOIjAVCwiV;
      string ztFwpxJHzZ;
      string QfXZmSCIfM;
      string nAgLgdfwkl;
      string KJWqBVgokd;
      string ZTipeqphwg;
      string SsQVgzMtPL;
      string RMWNPGJfYR;
      string lNWBmUQqfo;
      string nxAESQsAJB;
      string IlYZLMxVaX;
      string gJJetFVOiM;
      string hVOaWTMSty;
      string NIWWIznxpZ;
      string WtPHHdnVJN;
      string tdRxSmXyCq;
      string AebbKXmlVu;
      string RYYIonFGSs;
      if(snfkHMGFNB == lNWBmUQqfo){fqIfEjqZDV = true;}
      else if(lNWBmUQqfo == snfkHMGFNB){RqnRZyCkfZ = true;}
      if(QmlabibiQu == nxAESQsAJB){bouyZrSnxj = true;}
      else if(nxAESQsAJB == QmlabibiQu){LszPpAIHOY = true;}
      if(XOIjAVCwiV == IlYZLMxVaX){pBzOwVFIHe = true;}
      else if(IlYZLMxVaX == XOIjAVCwiV){BMfFzwLZaE = true;}
      if(ztFwpxJHzZ == gJJetFVOiM){gRfILIVuXa = true;}
      else if(gJJetFVOiM == ztFwpxJHzZ){gImmCBpHkL = true;}
      if(QfXZmSCIfM == hVOaWTMSty){gNhASbcaiw = true;}
      else if(hVOaWTMSty == QfXZmSCIfM){MXRfVXbuzw = true;}
      if(nAgLgdfwkl == NIWWIznxpZ){URIiCdqtjh = true;}
      else if(NIWWIznxpZ == nAgLgdfwkl){onulHFKiSc = true;}
      if(KJWqBVgokd == WtPHHdnVJN){dhRYnKJllQ = true;}
      else if(WtPHHdnVJN == KJWqBVgokd){lcJarCGLNo = true;}
      if(ZTipeqphwg == tdRxSmXyCq){WWPWDcSyuU = true;}
      if(SsQVgzMtPL == AebbKXmlVu){rdZKJOIxGg = true;}
      if(RMWNPGJfYR == RYYIonFGSs){RaLpwyuJLI = true;}
      while(tdRxSmXyCq == ZTipeqphwg){JBVCMctzia = true;}
      while(AebbKXmlVu == AebbKXmlVu){TPZePrNAew = true;}
      while(RYYIonFGSs == RYYIonFGSs){pHnHZjNqmS = true;}
      if(fqIfEjqZDV == true){fqIfEjqZDV = false;}
      if(bouyZrSnxj == true){bouyZrSnxj = false;}
      if(pBzOwVFIHe == true){pBzOwVFIHe = false;}
      if(gRfILIVuXa == true){gRfILIVuXa = false;}
      if(gNhASbcaiw == true){gNhASbcaiw = false;}
      if(URIiCdqtjh == true){URIiCdqtjh = false;}
      if(dhRYnKJllQ == true){dhRYnKJllQ = false;}
      if(WWPWDcSyuU == true){WWPWDcSyuU = false;}
      if(rdZKJOIxGg == true){rdZKJOIxGg = false;}
      if(RaLpwyuJLI == true){RaLpwyuJLI = false;}
      if(RqnRZyCkfZ == true){RqnRZyCkfZ = false;}
      if(LszPpAIHOY == true){LszPpAIHOY = false;}
      if(BMfFzwLZaE == true){BMfFzwLZaE = false;}
      if(gImmCBpHkL == true){gImmCBpHkL = false;}
      if(MXRfVXbuzw == true){MXRfVXbuzw = false;}
      if(onulHFKiSc == true){onulHFKiSc = false;}
      if(lcJarCGLNo == true){lcJarCGLNo = false;}
      if(JBVCMctzia == true){JBVCMctzia = false;}
      if(TPZePrNAew == true){TPZePrNAew = false;}
      if(pHnHZjNqmS == true){pHnHZjNqmS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VADBWFXYLD
{ 
  void PctNCUNAlA()
  { 
      bool bSQsxfaciH = false;
      bool XYbZzjkGRj = false;
      bool uBmbenhmPo = false;
      bool OTsTxHtGIf = false;
      bool LkxhpIMfjK = false;
      bool RrEaUZenNJ = false;
      bool xnNssEfIcr = false;
      bool pdxkYKEElW = false;
      bool aCCFXVPRzW = false;
      bool bFsziWXDol = false;
      bool bEDrTntSCJ = false;
      bool UZCpitkHUW = false;
      bool nOIFPjkyCB = false;
      bool mAPztVzKkj = false;
      bool bxPoCCDCPn = false;
      bool lQhSxNwxbj = false;
      bool CwPBWTKCwM = false;
      bool uaVkuqySDN = false;
      bool ghhOOWSxCf = false;
      bool ZBhBgfgOSh = false;
      string kkRdLDYoKM;
      string WDooifTJEf;
      string hggaeOxwEI;
      string DrHNqCZaaO;
      string nQpRXyoVMA;
      string FYkAYDEpzx;
      string GbkCJewayf;
      string FsipqQqOCf;
      string YajECdGHom;
      string yiadHLfnHr;
      string COXftMpuIH;
      string MomTXfrgAf;
      string XnkKhVRFhe;
      string kCHKcKCDJo;
      string mLygZJwHFa;
      string TynbTNcMyY;
      string tjMcWJhcqM;
      string dnXKrMpDjY;
      string ZKzGLlOfpO;
      string hoFjtCyVKQ;
      if(kkRdLDYoKM == COXftMpuIH){bSQsxfaciH = true;}
      else if(COXftMpuIH == kkRdLDYoKM){bEDrTntSCJ = true;}
      if(WDooifTJEf == MomTXfrgAf){XYbZzjkGRj = true;}
      else if(MomTXfrgAf == WDooifTJEf){UZCpitkHUW = true;}
      if(hggaeOxwEI == XnkKhVRFhe){uBmbenhmPo = true;}
      else if(XnkKhVRFhe == hggaeOxwEI){nOIFPjkyCB = true;}
      if(DrHNqCZaaO == kCHKcKCDJo){OTsTxHtGIf = true;}
      else if(kCHKcKCDJo == DrHNqCZaaO){mAPztVzKkj = true;}
      if(nQpRXyoVMA == mLygZJwHFa){LkxhpIMfjK = true;}
      else if(mLygZJwHFa == nQpRXyoVMA){bxPoCCDCPn = true;}
      if(FYkAYDEpzx == TynbTNcMyY){RrEaUZenNJ = true;}
      else if(TynbTNcMyY == FYkAYDEpzx){lQhSxNwxbj = true;}
      if(GbkCJewayf == tjMcWJhcqM){xnNssEfIcr = true;}
      else if(tjMcWJhcqM == GbkCJewayf){CwPBWTKCwM = true;}
      if(FsipqQqOCf == dnXKrMpDjY){pdxkYKEElW = true;}
      if(YajECdGHom == ZKzGLlOfpO){aCCFXVPRzW = true;}
      if(yiadHLfnHr == hoFjtCyVKQ){bFsziWXDol = true;}
      while(dnXKrMpDjY == FsipqQqOCf){uaVkuqySDN = true;}
      while(ZKzGLlOfpO == ZKzGLlOfpO){ghhOOWSxCf = true;}
      while(hoFjtCyVKQ == hoFjtCyVKQ){ZBhBgfgOSh = true;}
      if(bSQsxfaciH == true){bSQsxfaciH = false;}
      if(XYbZzjkGRj == true){XYbZzjkGRj = false;}
      if(uBmbenhmPo == true){uBmbenhmPo = false;}
      if(OTsTxHtGIf == true){OTsTxHtGIf = false;}
      if(LkxhpIMfjK == true){LkxhpIMfjK = false;}
      if(RrEaUZenNJ == true){RrEaUZenNJ = false;}
      if(xnNssEfIcr == true){xnNssEfIcr = false;}
      if(pdxkYKEElW == true){pdxkYKEElW = false;}
      if(aCCFXVPRzW == true){aCCFXVPRzW = false;}
      if(bFsziWXDol == true){bFsziWXDol = false;}
      if(bEDrTntSCJ == true){bEDrTntSCJ = false;}
      if(UZCpitkHUW == true){UZCpitkHUW = false;}
      if(nOIFPjkyCB == true){nOIFPjkyCB = false;}
      if(mAPztVzKkj == true){mAPztVzKkj = false;}
      if(bxPoCCDCPn == true){bxPoCCDCPn = false;}
      if(lQhSxNwxbj == true){lQhSxNwxbj = false;}
      if(CwPBWTKCwM == true){CwPBWTKCwM = false;}
      if(uaVkuqySDN == true){uaVkuqySDN = false;}
      if(ghhOOWSxCf == true){ghhOOWSxCf = false;}
      if(ZBhBgfgOSh == true){ZBhBgfgOSh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMIWVYPPDK
{ 
  void EeMOkbdHXE()
  { 
      bool rgYEOpjBCs = false;
      bool iuguDeDYSG = false;
      bool QiBkjtFUBI = false;
      bool pjddmbEuCM = false;
      bool AwsDqJWXlL = false;
      bool QtxMjJenUT = false;
      bool kOAtDyQDIa = false;
      bool ZHWGFUoxsZ = false;
      bool XhiprumRsc = false;
      bool wPahbkwzAs = false;
      bool sTOKkIXpGP = false;
      bool UhuuwCfKBI = false;
      bool KzJeeKfodT = false;
      bool XpwAgESXEi = false;
      bool XxKdINUfkZ = false;
      bool FkxqhsKiea = false;
      bool bhLlqektNr = false;
      bool iIFSkNoeWQ = false;
      bool pADEOmrFSm = false;
      bool tjrdHokXlc = false;
      string VZWYhmgmfT;
      string DjaddbeEVe;
      string GhJwVqznXQ;
      string yETmLuGJZP;
      string cVCBWmpaNV;
      string rbZqGmPZDp;
      string msOPVyPnSi;
      string UUdGCkfHZh;
      string BYZCXVdbfX;
      string efGibiGmfX;
      string XBHeAXyToV;
      string HHAVoOTMrA;
      string TmIuDnOtdS;
      string erbBKzQtBz;
      string XKmKPXfjtM;
      string PttfDjsMaL;
      string IDpWqOezLo;
      string yYKrcJAxef;
      string IdAQDjywxa;
      string FDSopTTPTB;
      if(VZWYhmgmfT == XBHeAXyToV){rgYEOpjBCs = true;}
      else if(XBHeAXyToV == VZWYhmgmfT){sTOKkIXpGP = true;}
      if(DjaddbeEVe == HHAVoOTMrA){iuguDeDYSG = true;}
      else if(HHAVoOTMrA == DjaddbeEVe){UhuuwCfKBI = true;}
      if(GhJwVqznXQ == TmIuDnOtdS){QiBkjtFUBI = true;}
      else if(TmIuDnOtdS == GhJwVqznXQ){KzJeeKfodT = true;}
      if(yETmLuGJZP == erbBKzQtBz){pjddmbEuCM = true;}
      else if(erbBKzQtBz == yETmLuGJZP){XpwAgESXEi = true;}
      if(cVCBWmpaNV == XKmKPXfjtM){AwsDqJWXlL = true;}
      else if(XKmKPXfjtM == cVCBWmpaNV){XxKdINUfkZ = true;}
      if(rbZqGmPZDp == PttfDjsMaL){QtxMjJenUT = true;}
      else if(PttfDjsMaL == rbZqGmPZDp){FkxqhsKiea = true;}
      if(msOPVyPnSi == IDpWqOezLo){kOAtDyQDIa = true;}
      else if(IDpWqOezLo == msOPVyPnSi){bhLlqektNr = true;}
      if(UUdGCkfHZh == yYKrcJAxef){ZHWGFUoxsZ = true;}
      if(BYZCXVdbfX == IdAQDjywxa){XhiprumRsc = true;}
      if(efGibiGmfX == FDSopTTPTB){wPahbkwzAs = true;}
      while(yYKrcJAxef == UUdGCkfHZh){iIFSkNoeWQ = true;}
      while(IdAQDjywxa == IdAQDjywxa){pADEOmrFSm = true;}
      while(FDSopTTPTB == FDSopTTPTB){tjrdHokXlc = true;}
      if(rgYEOpjBCs == true){rgYEOpjBCs = false;}
      if(iuguDeDYSG == true){iuguDeDYSG = false;}
      if(QiBkjtFUBI == true){QiBkjtFUBI = false;}
      if(pjddmbEuCM == true){pjddmbEuCM = false;}
      if(AwsDqJWXlL == true){AwsDqJWXlL = false;}
      if(QtxMjJenUT == true){QtxMjJenUT = false;}
      if(kOAtDyQDIa == true){kOAtDyQDIa = false;}
      if(ZHWGFUoxsZ == true){ZHWGFUoxsZ = false;}
      if(XhiprumRsc == true){XhiprumRsc = false;}
      if(wPahbkwzAs == true){wPahbkwzAs = false;}
      if(sTOKkIXpGP == true){sTOKkIXpGP = false;}
      if(UhuuwCfKBI == true){UhuuwCfKBI = false;}
      if(KzJeeKfodT == true){KzJeeKfodT = false;}
      if(XpwAgESXEi == true){XpwAgESXEi = false;}
      if(XxKdINUfkZ == true){XxKdINUfkZ = false;}
      if(FkxqhsKiea == true){FkxqhsKiea = false;}
      if(bhLlqektNr == true){bhLlqektNr = false;}
      if(iIFSkNoeWQ == true){iIFSkNoeWQ = false;}
      if(pADEOmrFSm == true){pADEOmrFSm = false;}
      if(tjrdHokXlc == true){tjrdHokXlc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IPPNHTHKSW
{ 
  void yyBXEQoHTO()
  { 
      bool jCEzznkbqy = false;
      bool iRKLoExirY = false;
      bool fqJVEWWzrC = false;
      bool YRNBtJQUMG = false;
      bool qGqDqFHsGa = false;
      bool WKirprshtb = false;
      bool RljoYRDIRf = false;
      bool ncVkgYAFdy = false;
      bool PcsQfOiVLB = false;
      bool QhZjoFVBdZ = false;
      bool CyaZmsnyKQ = false;
      bool rmEuMnsSJK = false;
      bool hhxQPGDkub = false;
      bool CybEwQBSdl = false;
      bool ajLtIcddXB = false;
      bool MDrTqUAKKg = false;
      bool pCChNtLzzw = false;
      bool lZnWiyVCIm = false;
      bool bZNtOzFHMb = false;
      bool PqHxwXhcgO = false;
      string rkWjitTkGn;
      string sbnlphRygj;
      string UdwBsbSWTX;
      string gFIQwVOreE;
      string knNcKEQdxu;
      string VgWwoNoUpG;
      string bxQhHnTXpT;
      string TYTcyfPSpo;
      string LnYYCzhLah;
      string fsCXcnXfVW;
      string krndbwNtxJ;
      string yWeBunXreH;
      string FHwHmZWwAK;
      string HjwTESzuxG;
      string kmNRjJNBbn;
      string PfBNQcugpB;
      string ZRtlBOZLwb;
      string obtYWRsdWd;
      string LUTLtbihCa;
      string WRFufTsaQV;
      if(rkWjitTkGn == krndbwNtxJ){jCEzznkbqy = true;}
      else if(krndbwNtxJ == rkWjitTkGn){CyaZmsnyKQ = true;}
      if(sbnlphRygj == yWeBunXreH){iRKLoExirY = true;}
      else if(yWeBunXreH == sbnlphRygj){rmEuMnsSJK = true;}
      if(UdwBsbSWTX == FHwHmZWwAK){fqJVEWWzrC = true;}
      else if(FHwHmZWwAK == UdwBsbSWTX){hhxQPGDkub = true;}
      if(gFIQwVOreE == HjwTESzuxG){YRNBtJQUMG = true;}
      else if(HjwTESzuxG == gFIQwVOreE){CybEwQBSdl = true;}
      if(knNcKEQdxu == kmNRjJNBbn){qGqDqFHsGa = true;}
      else if(kmNRjJNBbn == knNcKEQdxu){ajLtIcddXB = true;}
      if(VgWwoNoUpG == PfBNQcugpB){WKirprshtb = true;}
      else if(PfBNQcugpB == VgWwoNoUpG){MDrTqUAKKg = true;}
      if(bxQhHnTXpT == ZRtlBOZLwb){RljoYRDIRf = true;}
      else if(ZRtlBOZLwb == bxQhHnTXpT){pCChNtLzzw = true;}
      if(TYTcyfPSpo == obtYWRsdWd){ncVkgYAFdy = true;}
      if(LnYYCzhLah == LUTLtbihCa){PcsQfOiVLB = true;}
      if(fsCXcnXfVW == WRFufTsaQV){QhZjoFVBdZ = true;}
      while(obtYWRsdWd == TYTcyfPSpo){lZnWiyVCIm = true;}
      while(LUTLtbihCa == LUTLtbihCa){bZNtOzFHMb = true;}
      while(WRFufTsaQV == WRFufTsaQV){PqHxwXhcgO = true;}
      if(jCEzznkbqy == true){jCEzznkbqy = false;}
      if(iRKLoExirY == true){iRKLoExirY = false;}
      if(fqJVEWWzrC == true){fqJVEWWzrC = false;}
      if(YRNBtJQUMG == true){YRNBtJQUMG = false;}
      if(qGqDqFHsGa == true){qGqDqFHsGa = false;}
      if(WKirprshtb == true){WKirprshtb = false;}
      if(RljoYRDIRf == true){RljoYRDIRf = false;}
      if(ncVkgYAFdy == true){ncVkgYAFdy = false;}
      if(PcsQfOiVLB == true){PcsQfOiVLB = false;}
      if(QhZjoFVBdZ == true){QhZjoFVBdZ = false;}
      if(CyaZmsnyKQ == true){CyaZmsnyKQ = false;}
      if(rmEuMnsSJK == true){rmEuMnsSJK = false;}
      if(hhxQPGDkub == true){hhxQPGDkub = false;}
      if(CybEwQBSdl == true){CybEwQBSdl = false;}
      if(ajLtIcddXB == true){ajLtIcddXB = false;}
      if(MDrTqUAKKg == true){MDrTqUAKKg = false;}
      if(pCChNtLzzw == true){pCChNtLzzw = false;}
      if(lZnWiyVCIm == true){lZnWiyVCIm = false;}
      if(bZNtOzFHMb == true){bZNtOzFHMb = false;}
      if(PqHxwXhcgO == true){PqHxwXhcgO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RVYBVFZCHA
{ 
  void xYJHmTZudc()
  { 
      bool LnWndpeGIG = false;
      bool XrSVeuyWTQ = false;
      bool izJOhpcUTe = false;
      bool nrekzYDBSF = false;
      bool IMIMPYnhWm = false;
      bool adcVZLdIGm = false;
      bool NJldSfNgWG = false;
      bool qxDNIWqxzI = false;
      bool BuyfEKOILm = false;
      bool uutfryZdti = false;
      bool LHKPucZONC = false;
      bool UgJxkSLFZH = false;
      bool QEVjLwDXVK = false;
      bool wMCPxtjika = false;
      bool jAuISNkwtY = false;
      bool lTEmRGlaEy = false;
      bool ZCrCFIesAq = false;
      bool icUyXQJMQx = false;
      bool KGcxXcHPxp = false;
      bool IIdlBhHsCK = false;
      string FwEzxIGTDm;
      string swwFrKVhPY;
      string TlosfVDigW;
      string nWuwJfUtpy;
      string NHudaQWPeN;
      string wJJwHTHKSa;
      string FWlfyWBAuL;
      string oarQLMpKSP;
      string znETZeMyno;
      string YKbOspVOfE;
      string PWTTXVRrku;
      string dwrCbRSSGS;
      string JCLGmezcXU;
      string paeOAcTkuE;
      string NUNrLbRYma;
      string XCINuMLMfs;
      string VnTQECQdCz;
      string xgWCEnoStK;
      string NaowwnSRTm;
      string QHEChZAwmJ;
      if(FwEzxIGTDm == PWTTXVRrku){LnWndpeGIG = true;}
      else if(PWTTXVRrku == FwEzxIGTDm){LHKPucZONC = true;}
      if(swwFrKVhPY == dwrCbRSSGS){XrSVeuyWTQ = true;}
      else if(dwrCbRSSGS == swwFrKVhPY){UgJxkSLFZH = true;}
      if(TlosfVDigW == JCLGmezcXU){izJOhpcUTe = true;}
      else if(JCLGmezcXU == TlosfVDigW){QEVjLwDXVK = true;}
      if(nWuwJfUtpy == paeOAcTkuE){nrekzYDBSF = true;}
      else if(paeOAcTkuE == nWuwJfUtpy){wMCPxtjika = true;}
      if(NHudaQWPeN == NUNrLbRYma){IMIMPYnhWm = true;}
      else if(NUNrLbRYma == NHudaQWPeN){jAuISNkwtY = true;}
      if(wJJwHTHKSa == XCINuMLMfs){adcVZLdIGm = true;}
      else if(XCINuMLMfs == wJJwHTHKSa){lTEmRGlaEy = true;}
      if(FWlfyWBAuL == VnTQECQdCz){NJldSfNgWG = true;}
      else if(VnTQECQdCz == FWlfyWBAuL){ZCrCFIesAq = true;}
      if(oarQLMpKSP == xgWCEnoStK){qxDNIWqxzI = true;}
      if(znETZeMyno == NaowwnSRTm){BuyfEKOILm = true;}
      if(YKbOspVOfE == QHEChZAwmJ){uutfryZdti = true;}
      while(xgWCEnoStK == oarQLMpKSP){icUyXQJMQx = true;}
      while(NaowwnSRTm == NaowwnSRTm){KGcxXcHPxp = true;}
      while(QHEChZAwmJ == QHEChZAwmJ){IIdlBhHsCK = true;}
      if(LnWndpeGIG == true){LnWndpeGIG = false;}
      if(XrSVeuyWTQ == true){XrSVeuyWTQ = false;}
      if(izJOhpcUTe == true){izJOhpcUTe = false;}
      if(nrekzYDBSF == true){nrekzYDBSF = false;}
      if(IMIMPYnhWm == true){IMIMPYnhWm = false;}
      if(adcVZLdIGm == true){adcVZLdIGm = false;}
      if(NJldSfNgWG == true){NJldSfNgWG = false;}
      if(qxDNIWqxzI == true){qxDNIWqxzI = false;}
      if(BuyfEKOILm == true){BuyfEKOILm = false;}
      if(uutfryZdti == true){uutfryZdti = false;}
      if(LHKPucZONC == true){LHKPucZONC = false;}
      if(UgJxkSLFZH == true){UgJxkSLFZH = false;}
      if(QEVjLwDXVK == true){QEVjLwDXVK = false;}
      if(wMCPxtjika == true){wMCPxtjika = false;}
      if(jAuISNkwtY == true){jAuISNkwtY = false;}
      if(lTEmRGlaEy == true){lTEmRGlaEy = false;}
      if(ZCrCFIesAq == true){ZCrCFIesAq = false;}
      if(icUyXQJMQx == true){icUyXQJMQx = false;}
      if(KGcxXcHPxp == true){KGcxXcHPxp = false;}
      if(IIdlBhHsCK == true){IIdlBhHsCK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LQOLBSHMOD
{ 
  void YfsMCrNbBC()
  { 
      bool ghMWlMNisj = false;
      bool wTPRAATPUP = false;
      bool BGOpixHtqk = false;
      bool CTmpRYPDQu = false;
      bool ckKrQMyAYa = false;
      bool JTbkuaSWmo = false;
      bool ETrHgbgYzb = false;
      bool jQyZmPuVYW = false;
      bool zHUQbiqBup = false;
      bool FrPbpIsDKn = false;
      bool eYAxprUCye = false;
      bool fxyPpxybfy = false;
      bool kedIVqAWid = false;
      bool WrKkqaGXZi = false;
      bool NoDPKItAlr = false;
      bool KQWMDAtqaz = false;
      bool rySUImlMXP = false;
      bool pZCxjuaOyN = false;
      bool wAjqSFUygp = false;
      bool fPwZpOVhHW = false;
      string yrjYaAzQdB;
      string boDPwMjpzb;
      string CMPhSdACzh;
      string kQDVxqRymY;
      string pxSJWokaMh;
      string HItIilcBGw;
      string AwQwPLkhRF;
      string ukCZlEsGKc;
      string rYoRZcWulL;
      string OPrpYsfWtL;
      string DDIHlVFTVe;
      string rWpcEaHzVl;
      string opuGqfsLAs;
      string XVLzZnQhfD;
      string WCYHSrYPlx;
      string lgBHWMICQG;
      string csSbGWKqCP;
      string KYTROlQnmz;
      string GcZDHqUEcM;
      string fNRYadixAw;
      if(yrjYaAzQdB == DDIHlVFTVe){ghMWlMNisj = true;}
      else if(DDIHlVFTVe == yrjYaAzQdB){eYAxprUCye = true;}
      if(boDPwMjpzb == rWpcEaHzVl){wTPRAATPUP = true;}
      else if(rWpcEaHzVl == boDPwMjpzb){fxyPpxybfy = true;}
      if(CMPhSdACzh == opuGqfsLAs){BGOpixHtqk = true;}
      else if(opuGqfsLAs == CMPhSdACzh){kedIVqAWid = true;}
      if(kQDVxqRymY == XVLzZnQhfD){CTmpRYPDQu = true;}
      else if(XVLzZnQhfD == kQDVxqRymY){WrKkqaGXZi = true;}
      if(pxSJWokaMh == WCYHSrYPlx){ckKrQMyAYa = true;}
      else if(WCYHSrYPlx == pxSJWokaMh){NoDPKItAlr = true;}
      if(HItIilcBGw == lgBHWMICQG){JTbkuaSWmo = true;}
      else if(lgBHWMICQG == HItIilcBGw){KQWMDAtqaz = true;}
      if(AwQwPLkhRF == csSbGWKqCP){ETrHgbgYzb = true;}
      else if(csSbGWKqCP == AwQwPLkhRF){rySUImlMXP = true;}
      if(ukCZlEsGKc == KYTROlQnmz){jQyZmPuVYW = true;}
      if(rYoRZcWulL == GcZDHqUEcM){zHUQbiqBup = true;}
      if(OPrpYsfWtL == fNRYadixAw){FrPbpIsDKn = true;}
      while(KYTROlQnmz == ukCZlEsGKc){pZCxjuaOyN = true;}
      while(GcZDHqUEcM == GcZDHqUEcM){wAjqSFUygp = true;}
      while(fNRYadixAw == fNRYadixAw){fPwZpOVhHW = true;}
      if(ghMWlMNisj == true){ghMWlMNisj = false;}
      if(wTPRAATPUP == true){wTPRAATPUP = false;}
      if(BGOpixHtqk == true){BGOpixHtqk = false;}
      if(CTmpRYPDQu == true){CTmpRYPDQu = false;}
      if(ckKrQMyAYa == true){ckKrQMyAYa = false;}
      if(JTbkuaSWmo == true){JTbkuaSWmo = false;}
      if(ETrHgbgYzb == true){ETrHgbgYzb = false;}
      if(jQyZmPuVYW == true){jQyZmPuVYW = false;}
      if(zHUQbiqBup == true){zHUQbiqBup = false;}
      if(FrPbpIsDKn == true){FrPbpIsDKn = false;}
      if(eYAxprUCye == true){eYAxprUCye = false;}
      if(fxyPpxybfy == true){fxyPpxybfy = false;}
      if(kedIVqAWid == true){kedIVqAWid = false;}
      if(WrKkqaGXZi == true){WrKkqaGXZi = false;}
      if(NoDPKItAlr == true){NoDPKItAlr = false;}
      if(KQWMDAtqaz == true){KQWMDAtqaz = false;}
      if(rySUImlMXP == true){rySUImlMXP = false;}
      if(pZCxjuaOyN == true){pZCxjuaOyN = false;}
      if(wAjqSFUygp == true){wAjqSFUygp = false;}
      if(fPwZpOVhHW == true){fPwZpOVhHW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JYQTEBOAHT
{ 
  void eTzHbchxYu()
  { 
      bool hnpOBZqtuS = false;
      bool huLLFyQgIu = false;
      bool ZchXgyjVqM = false;
      bool AQRLOBKCaO = false;
      bool oSEUklGwXy = false;
      bool AoLHhFFShC = false;
      bool oVDiSQdzxD = false;
      bool nOFtFHYMlu = false;
      bool rmyrMKFKdI = false;
      bool wqTYYTPUCT = false;
      bool HHzTJkiQBZ = false;
      bool gsfmKBXKWH = false;
      bool KSVnHwtgUl = false;
      bool rDKSmkndia = false;
      bool bnJDbCKgNW = false;
      bool wExtJokLLN = false;
      bool pBwOhciNzZ = false;
      bool NsbufVJRLE = false;
      bool kNSypmGPIy = false;
      bool zcRUkZrtUz = false;
      string hMeYflPUFq;
      string GbxTLtbwMH;
      string umiGsHfUau;
      string lQGSZpimNl;
      string XIaHintnlG;
      string TKfmmudYfY;
      string FtsKEoUesU;
      string KnhajmLbXE;
      string MqiUabkTed;
      string MKHnfdOQCs;
      string TPtQufbEDA;
      string iBAaLNKXic;
      string DBzPHAgstG;
      string XuYdkxxRYu;
      string zgQeuKJfcR;
      string SqhYpSPeIu;
      string yhJwbmcVpN;
      string QszmdWkUTx;
      string pAQcngNznS;
      string gRIcwRWTCH;
      if(hMeYflPUFq == TPtQufbEDA){hnpOBZqtuS = true;}
      else if(TPtQufbEDA == hMeYflPUFq){HHzTJkiQBZ = true;}
      if(GbxTLtbwMH == iBAaLNKXic){huLLFyQgIu = true;}
      else if(iBAaLNKXic == GbxTLtbwMH){gsfmKBXKWH = true;}
      if(umiGsHfUau == DBzPHAgstG){ZchXgyjVqM = true;}
      else if(DBzPHAgstG == umiGsHfUau){KSVnHwtgUl = true;}
      if(lQGSZpimNl == XuYdkxxRYu){AQRLOBKCaO = true;}
      else if(XuYdkxxRYu == lQGSZpimNl){rDKSmkndia = true;}
      if(XIaHintnlG == zgQeuKJfcR){oSEUklGwXy = true;}
      else if(zgQeuKJfcR == XIaHintnlG){bnJDbCKgNW = true;}
      if(TKfmmudYfY == SqhYpSPeIu){AoLHhFFShC = true;}
      else if(SqhYpSPeIu == TKfmmudYfY){wExtJokLLN = true;}
      if(FtsKEoUesU == yhJwbmcVpN){oVDiSQdzxD = true;}
      else if(yhJwbmcVpN == FtsKEoUesU){pBwOhciNzZ = true;}
      if(KnhajmLbXE == QszmdWkUTx){nOFtFHYMlu = true;}
      if(MqiUabkTed == pAQcngNznS){rmyrMKFKdI = true;}
      if(MKHnfdOQCs == gRIcwRWTCH){wqTYYTPUCT = true;}
      while(QszmdWkUTx == KnhajmLbXE){NsbufVJRLE = true;}
      while(pAQcngNznS == pAQcngNznS){kNSypmGPIy = true;}
      while(gRIcwRWTCH == gRIcwRWTCH){zcRUkZrtUz = true;}
      if(hnpOBZqtuS == true){hnpOBZqtuS = false;}
      if(huLLFyQgIu == true){huLLFyQgIu = false;}
      if(ZchXgyjVqM == true){ZchXgyjVqM = false;}
      if(AQRLOBKCaO == true){AQRLOBKCaO = false;}
      if(oSEUklGwXy == true){oSEUklGwXy = false;}
      if(AoLHhFFShC == true){AoLHhFFShC = false;}
      if(oVDiSQdzxD == true){oVDiSQdzxD = false;}
      if(nOFtFHYMlu == true){nOFtFHYMlu = false;}
      if(rmyrMKFKdI == true){rmyrMKFKdI = false;}
      if(wqTYYTPUCT == true){wqTYYTPUCT = false;}
      if(HHzTJkiQBZ == true){HHzTJkiQBZ = false;}
      if(gsfmKBXKWH == true){gsfmKBXKWH = false;}
      if(KSVnHwtgUl == true){KSVnHwtgUl = false;}
      if(rDKSmkndia == true){rDKSmkndia = false;}
      if(bnJDbCKgNW == true){bnJDbCKgNW = false;}
      if(wExtJokLLN == true){wExtJokLLN = false;}
      if(pBwOhciNzZ == true){pBwOhciNzZ = false;}
      if(NsbufVJRLE == true){NsbufVJRLE = false;}
      if(kNSypmGPIy == true){kNSypmGPIy = false;}
      if(zcRUkZrtUz == true){zcRUkZrtUz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RZFGXJWKBW
{ 
  void iqrPazhukw()
  { 
      bool IJMMBctZzS = false;
      bool BXzIhgmwAy = false;
      bool weuDtyHQPE = false;
      bool YqPynyzJnB = false;
      bool DQobkjDJIq = false;
      bool TFXQIdNIRC = false;
      bool VdKusJIBTj = false;
      bool gdHyteoTRJ = false;
      bool tyIXkSTyoK = false;
      bool jpqkfZFthb = false;
      bool aCoXJoxYVc = false;
      bool nsqHHWVmKZ = false;
      bool oKLJzqlWSU = false;
      bool ZukpirIjNu = false;
      bool UubLVpzicI = false;
      bool ESjHlQqeXS = false;
      bool CaFBDrHAYP = false;
      bool NkZOEthzmI = false;
      bool rCsJQHLdDR = false;
      bool AdLtrtoaId = false;
      string pcYoWmGibQ;
      string qrAfZysQbj;
      string yYUtGBcEQw;
      string ZGJyBEKfzV;
      string BIzeuSuaBl;
      string VMltnRIehU;
      string JBSepkhBdV;
      string mNQFhpYozn;
      string FCDeZMUPKj;
      string wfxeLAoToK;
      string jtwfyIufMy;
      string rTetOHxnFc;
      string PSqtZHPltg;
      string AFAoDLFXgR;
      string RnDMqbADPD;
      string CBOLtQCCFp;
      string sJlexmTppD;
      string CZHnLaPdCx;
      string HLVpeyqntm;
      string IDRpYHCXOE;
      if(pcYoWmGibQ == jtwfyIufMy){IJMMBctZzS = true;}
      else if(jtwfyIufMy == pcYoWmGibQ){aCoXJoxYVc = true;}
      if(qrAfZysQbj == rTetOHxnFc){BXzIhgmwAy = true;}
      else if(rTetOHxnFc == qrAfZysQbj){nsqHHWVmKZ = true;}
      if(yYUtGBcEQw == PSqtZHPltg){weuDtyHQPE = true;}
      else if(PSqtZHPltg == yYUtGBcEQw){oKLJzqlWSU = true;}
      if(ZGJyBEKfzV == AFAoDLFXgR){YqPynyzJnB = true;}
      else if(AFAoDLFXgR == ZGJyBEKfzV){ZukpirIjNu = true;}
      if(BIzeuSuaBl == RnDMqbADPD){DQobkjDJIq = true;}
      else if(RnDMqbADPD == BIzeuSuaBl){UubLVpzicI = true;}
      if(VMltnRIehU == CBOLtQCCFp){TFXQIdNIRC = true;}
      else if(CBOLtQCCFp == VMltnRIehU){ESjHlQqeXS = true;}
      if(JBSepkhBdV == sJlexmTppD){VdKusJIBTj = true;}
      else if(sJlexmTppD == JBSepkhBdV){CaFBDrHAYP = true;}
      if(mNQFhpYozn == CZHnLaPdCx){gdHyteoTRJ = true;}
      if(FCDeZMUPKj == HLVpeyqntm){tyIXkSTyoK = true;}
      if(wfxeLAoToK == IDRpYHCXOE){jpqkfZFthb = true;}
      while(CZHnLaPdCx == mNQFhpYozn){NkZOEthzmI = true;}
      while(HLVpeyqntm == HLVpeyqntm){rCsJQHLdDR = true;}
      while(IDRpYHCXOE == IDRpYHCXOE){AdLtrtoaId = true;}
      if(IJMMBctZzS == true){IJMMBctZzS = false;}
      if(BXzIhgmwAy == true){BXzIhgmwAy = false;}
      if(weuDtyHQPE == true){weuDtyHQPE = false;}
      if(YqPynyzJnB == true){YqPynyzJnB = false;}
      if(DQobkjDJIq == true){DQobkjDJIq = false;}
      if(TFXQIdNIRC == true){TFXQIdNIRC = false;}
      if(VdKusJIBTj == true){VdKusJIBTj = false;}
      if(gdHyteoTRJ == true){gdHyteoTRJ = false;}
      if(tyIXkSTyoK == true){tyIXkSTyoK = false;}
      if(jpqkfZFthb == true){jpqkfZFthb = false;}
      if(aCoXJoxYVc == true){aCoXJoxYVc = false;}
      if(nsqHHWVmKZ == true){nsqHHWVmKZ = false;}
      if(oKLJzqlWSU == true){oKLJzqlWSU = false;}
      if(ZukpirIjNu == true){ZukpirIjNu = false;}
      if(UubLVpzicI == true){UubLVpzicI = false;}
      if(ESjHlQqeXS == true){ESjHlQqeXS = false;}
      if(CaFBDrHAYP == true){CaFBDrHAYP = false;}
      if(NkZOEthzmI == true){NkZOEthzmI = false;}
      if(rCsJQHLdDR == true){rCsJQHLdDR = false;}
      if(AdLtrtoaId == true){AdLtrtoaId = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTHEJSXDJE
{ 
  void AhwjkFoHGz()
  { 
      bool KhRJFnMPEa = false;
      bool JzTWaDmwVX = false;
      bool QbMOYNluzG = false;
      bool IgAKaJUlaS = false;
      bool mzWWXJxmAx = false;
      bool WYVZJiUDjq = false;
      bool BRPySbyIwR = false;
      bool iAUDkQEopO = false;
      bool PztCijLaBr = false;
      bool nRCiQUiYEw = false;
      bool KnqiOVDSor = false;
      bool efMVaCXNOi = false;
      bool QXHEdQyklP = false;
      bool gfktDbHKmN = false;
      bool fskIMHFfIN = false;
      bool xVJUfmgmFx = false;
      bool XSfYKzuRRz = false;
      bool uMaBCWlyqV = false;
      bool LRcXSLVPOQ = false;
      bool tTFppNMMxN = false;
      string PSWXDwtGbp;
      string yySYNuNWHm;
      string DSmaOmaBqC;
      string NiJWOwDkzG;
      string sQfIsTNGZt;
      string UwsQtxfwIP;
      string UrOYbOnwJQ;
      string qcXBtlldhu;
      string YTbxhRorcR;
      string QHbikBCGfd;
      string eRxICqXrWH;
      string KBONpBPRqK;
      string ZuSrAjBnPr;
      string jeyDQHWStp;
      string swVUGOsOrj;
      string kjPVEiyFIS;
      string pibdWfDKwi;
      string ewWAQcZykl;
      string qlwfHzObyg;
      string JQKbAKUrxZ;
      if(PSWXDwtGbp == eRxICqXrWH){KhRJFnMPEa = true;}
      else if(eRxICqXrWH == PSWXDwtGbp){KnqiOVDSor = true;}
      if(yySYNuNWHm == KBONpBPRqK){JzTWaDmwVX = true;}
      else if(KBONpBPRqK == yySYNuNWHm){efMVaCXNOi = true;}
      if(DSmaOmaBqC == ZuSrAjBnPr){QbMOYNluzG = true;}
      else if(ZuSrAjBnPr == DSmaOmaBqC){QXHEdQyklP = true;}
      if(NiJWOwDkzG == jeyDQHWStp){IgAKaJUlaS = true;}
      else if(jeyDQHWStp == NiJWOwDkzG){gfktDbHKmN = true;}
      if(sQfIsTNGZt == swVUGOsOrj){mzWWXJxmAx = true;}
      else if(swVUGOsOrj == sQfIsTNGZt){fskIMHFfIN = true;}
      if(UwsQtxfwIP == kjPVEiyFIS){WYVZJiUDjq = true;}
      else if(kjPVEiyFIS == UwsQtxfwIP){xVJUfmgmFx = true;}
      if(UrOYbOnwJQ == pibdWfDKwi){BRPySbyIwR = true;}
      else if(pibdWfDKwi == UrOYbOnwJQ){XSfYKzuRRz = true;}
      if(qcXBtlldhu == ewWAQcZykl){iAUDkQEopO = true;}
      if(YTbxhRorcR == qlwfHzObyg){PztCijLaBr = true;}
      if(QHbikBCGfd == JQKbAKUrxZ){nRCiQUiYEw = true;}
      while(ewWAQcZykl == qcXBtlldhu){uMaBCWlyqV = true;}
      while(qlwfHzObyg == qlwfHzObyg){LRcXSLVPOQ = true;}
      while(JQKbAKUrxZ == JQKbAKUrxZ){tTFppNMMxN = true;}
      if(KhRJFnMPEa == true){KhRJFnMPEa = false;}
      if(JzTWaDmwVX == true){JzTWaDmwVX = false;}
      if(QbMOYNluzG == true){QbMOYNluzG = false;}
      if(IgAKaJUlaS == true){IgAKaJUlaS = false;}
      if(mzWWXJxmAx == true){mzWWXJxmAx = false;}
      if(WYVZJiUDjq == true){WYVZJiUDjq = false;}
      if(BRPySbyIwR == true){BRPySbyIwR = false;}
      if(iAUDkQEopO == true){iAUDkQEopO = false;}
      if(PztCijLaBr == true){PztCijLaBr = false;}
      if(nRCiQUiYEw == true){nRCiQUiYEw = false;}
      if(KnqiOVDSor == true){KnqiOVDSor = false;}
      if(efMVaCXNOi == true){efMVaCXNOi = false;}
      if(QXHEdQyklP == true){QXHEdQyklP = false;}
      if(gfktDbHKmN == true){gfktDbHKmN = false;}
      if(fskIMHFfIN == true){fskIMHFfIN = false;}
      if(xVJUfmgmFx == true){xVJUfmgmFx = false;}
      if(XSfYKzuRRz == true){XSfYKzuRRz = false;}
      if(uMaBCWlyqV == true){uMaBCWlyqV = false;}
      if(LRcXSLVPOQ == true){LRcXSLVPOQ = false;}
      if(tTFppNMMxN == true){tTFppNMMxN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RNDZSUFSUY
{ 
  void kybeqwBNBM()
  { 
      bool oVkslJWMbW = false;
      bool PrwADGLNsL = false;
      bool BVurAoDUuO = false;
      bool OcRHMaQkkD = false;
      bool TbiCtHAlpl = false;
      bool uccxISZrrx = false;
      bool FBQMHlZnmb = false;
      bool pacoqYmrys = false;
      bool nQeJTlAUzt = false;
      bool BXrnyRLVuH = false;
      bool hLzNwTAmFi = false;
      bool fhtyIoWGsV = false;
      bool lFosaRhoqZ = false;
      bool NRxpLbQQMA = false;
      bool kNOQNTdteI = false;
      bool uEcYVbWGle = false;
      bool kKwfUOjDmg = false;
      bool XFtrjYpYeH = false;
      bool mnJhdIoYUi = false;
      bool FKehPaQhuz = false;
      string jqnXCQXWzl;
      string BebxQsRofR;
      string PUYIeKZcaH;
      string HKHwxerKFN;
      string ZqkwzOkgMp;
      string GxBLEPSesr;
      string puurdpXeAk;
      string AHjSqYibJQ;
      string YrQkAKJwrg;
      string MMQMWewsSI;
      string pGgaoyNhTf;
      string gpVcSxeKqT;
      string gbmSYnpWwM;
      string cpJAZSLouC;
      string xbbLAVqnsY;
      string zlByaOSOCB;
      string IpkGCpgUDA;
      string lpOoWEzaRC;
      string xBdXNqnKYK;
      string zxltsHpVJK;
      if(jqnXCQXWzl == pGgaoyNhTf){oVkslJWMbW = true;}
      else if(pGgaoyNhTf == jqnXCQXWzl){hLzNwTAmFi = true;}
      if(BebxQsRofR == gpVcSxeKqT){PrwADGLNsL = true;}
      else if(gpVcSxeKqT == BebxQsRofR){fhtyIoWGsV = true;}
      if(PUYIeKZcaH == gbmSYnpWwM){BVurAoDUuO = true;}
      else if(gbmSYnpWwM == PUYIeKZcaH){lFosaRhoqZ = true;}
      if(HKHwxerKFN == cpJAZSLouC){OcRHMaQkkD = true;}
      else if(cpJAZSLouC == HKHwxerKFN){NRxpLbQQMA = true;}
      if(ZqkwzOkgMp == xbbLAVqnsY){TbiCtHAlpl = true;}
      else if(xbbLAVqnsY == ZqkwzOkgMp){kNOQNTdteI = true;}
      if(GxBLEPSesr == zlByaOSOCB){uccxISZrrx = true;}
      else if(zlByaOSOCB == GxBLEPSesr){uEcYVbWGle = true;}
      if(puurdpXeAk == IpkGCpgUDA){FBQMHlZnmb = true;}
      else if(IpkGCpgUDA == puurdpXeAk){kKwfUOjDmg = true;}
      if(AHjSqYibJQ == lpOoWEzaRC){pacoqYmrys = true;}
      if(YrQkAKJwrg == xBdXNqnKYK){nQeJTlAUzt = true;}
      if(MMQMWewsSI == zxltsHpVJK){BXrnyRLVuH = true;}
      while(lpOoWEzaRC == AHjSqYibJQ){XFtrjYpYeH = true;}
      while(xBdXNqnKYK == xBdXNqnKYK){mnJhdIoYUi = true;}
      while(zxltsHpVJK == zxltsHpVJK){FKehPaQhuz = true;}
      if(oVkslJWMbW == true){oVkslJWMbW = false;}
      if(PrwADGLNsL == true){PrwADGLNsL = false;}
      if(BVurAoDUuO == true){BVurAoDUuO = false;}
      if(OcRHMaQkkD == true){OcRHMaQkkD = false;}
      if(TbiCtHAlpl == true){TbiCtHAlpl = false;}
      if(uccxISZrrx == true){uccxISZrrx = false;}
      if(FBQMHlZnmb == true){FBQMHlZnmb = false;}
      if(pacoqYmrys == true){pacoqYmrys = false;}
      if(nQeJTlAUzt == true){nQeJTlAUzt = false;}
      if(BXrnyRLVuH == true){BXrnyRLVuH = false;}
      if(hLzNwTAmFi == true){hLzNwTAmFi = false;}
      if(fhtyIoWGsV == true){fhtyIoWGsV = false;}
      if(lFosaRhoqZ == true){lFosaRhoqZ = false;}
      if(NRxpLbQQMA == true){NRxpLbQQMA = false;}
      if(kNOQNTdteI == true){kNOQNTdteI = false;}
      if(uEcYVbWGle == true){uEcYVbWGle = false;}
      if(kKwfUOjDmg == true){kKwfUOjDmg = false;}
      if(XFtrjYpYeH == true){XFtrjYpYeH = false;}
      if(mnJhdIoYUi == true){mnJhdIoYUi = false;}
      if(FKehPaQhuz == true){FKehPaQhuz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CJTPMPLLXX
{ 
  void NxTUmHBPmf()
  { 
      bool PftlCYhbSP = false;
      bool yntqZdqxAM = false;
      bool inhZekokCP = false;
      bool OSSBTFhoRq = false;
      bool phwBoKxnZW = false;
      bool DTDDHayUHQ = false;
      bool jwZCAfUrWU = false;
      bool uCfJVBrfjU = false;
      bool nALeMtOPts = false;
      bool HNgAHtHsAJ = false;
      bool oEQFaBntgF = false;
      bool iRjmciktpG = false;
      bool QFydMhUeBb = false;
      bool syfaejiFEK = false;
      bool FThnKpctXX = false;
      bool JNDtrjGmrr = false;
      bool gJsFLjkJHr = false;
      bool zepfAxWJSW = false;
      bool FZHcSfuliu = false;
      bool cwNLdwZcbZ = false;
      string jfgakItKJl;
      string MwiaZhoHWO;
      string OYoweEHhXC;
      string qzFSdGaZym;
      string iEwuXGYMxi;
      string ETAHnLpjwf;
      string BMlHtNqPwS;
      string HOJjfKcsXY;
      string etknxWyxeS;
      string PqdRkVRnAK;
      string PIQdbpKPbd;
      string hwLWAGbyJX;
      string OskcCQjrzK;
      string rnrMJWdGMG;
      string MhVBjSeHQe;
      string tTecwVXmaL;
      string GRQQksDyNd;
      string bUlCKfXiri;
      string kbaTQYJPQm;
      string zqfAAtREPq;
      if(jfgakItKJl == PIQdbpKPbd){PftlCYhbSP = true;}
      else if(PIQdbpKPbd == jfgakItKJl){oEQFaBntgF = true;}
      if(MwiaZhoHWO == hwLWAGbyJX){yntqZdqxAM = true;}
      else if(hwLWAGbyJX == MwiaZhoHWO){iRjmciktpG = true;}
      if(OYoweEHhXC == OskcCQjrzK){inhZekokCP = true;}
      else if(OskcCQjrzK == OYoweEHhXC){QFydMhUeBb = true;}
      if(qzFSdGaZym == rnrMJWdGMG){OSSBTFhoRq = true;}
      else if(rnrMJWdGMG == qzFSdGaZym){syfaejiFEK = true;}
      if(iEwuXGYMxi == MhVBjSeHQe){phwBoKxnZW = true;}
      else if(MhVBjSeHQe == iEwuXGYMxi){FThnKpctXX = true;}
      if(ETAHnLpjwf == tTecwVXmaL){DTDDHayUHQ = true;}
      else if(tTecwVXmaL == ETAHnLpjwf){JNDtrjGmrr = true;}
      if(BMlHtNqPwS == GRQQksDyNd){jwZCAfUrWU = true;}
      else if(GRQQksDyNd == BMlHtNqPwS){gJsFLjkJHr = true;}
      if(HOJjfKcsXY == bUlCKfXiri){uCfJVBrfjU = true;}
      if(etknxWyxeS == kbaTQYJPQm){nALeMtOPts = true;}
      if(PqdRkVRnAK == zqfAAtREPq){HNgAHtHsAJ = true;}
      while(bUlCKfXiri == HOJjfKcsXY){zepfAxWJSW = true;}
      while(kbaTQYJPQm == kbaTQYJPQm){FZHcSfuliu = true;}
      while(zqfAAtREPq == zqfAAtREPq){cwNLdwZcbZ = true;}
      if(PftlCYhbSP == true){PftlCYhbSP = false;}
      if(yntqZdqxAM == true){yntqZdqxAM = false;}
      if(inhZekokCP == true){inhZekokCP = false;}
      if(OSSBTFhoRq == true){OSSBTFhoRq = false;}
      if(phwBoKxnZW == true){phwBoKxnZW = false;}
      if(DTDDHayUHQ == true){DTDDHayUHQ = false;}
      if(jwZCAfUrWU == true){jwZCAfUrWU = false;}
      if(uCfJVBrfjU == true){uCfJVBrfjU = false;}
      if(nALeMtOPts == true){nALeMtOPts = false;}
      if(HNgAHtHsAJ == true){HNgAHtHsAJ = false;}
      if(oEQFaBntgF == true){oEQFaBntgF = false;}
      if(iRjmciktpG == true){iRjmciktpG = false;}
      if(QFydMhUeBb == true){QFydMhUeBb = false;}
      if(syfaejiFEK == true){syfaejiFEK = false;}
      if(FThnKpctXX == true){FThnKpctXX = false;}
      if(JNDtrjGmrr == true){JNDtrjGmrr = false;}
      if(gJsFLjkJHr == true){gJsFLjkJHr = false;}
      if(zepfAxWJSW == true){zepfAxWJSW = false;}
      if(FZHcSfuliu == true){FZHcSfuliu = false;}
      if(cwNLdwZcbZ == true){cwNLdwZcbZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WKWVYBVUZL
{ 
  void tWRepaSonL()
  { 
      bool kuDITOciPN = false;
      bool notcjjRXGN = false;
      bool EVzcbcwYTW = false;
      bool ofYpEMKKBn = false;
      bool uePNnSsaHs = false;
      bool eIaEbOuafp = false;
      bool RDPsYHQDYW = false;
      bool YGWSSYGkoJ = false;
      bool iVRZrfEUOo = false;
      bool RjeKVqPWof = false;
      bool CpCjUXlIkD = false;
      bool IKlWGwkoAr = false;
      bool DuoiFnbLwa = false;
      bool IiuIHsShFU = false;
      bool twiKfGyHEZ = false;
      bool FaVxcGBTdf = false;
      bool uZLJtYOcPN = false;
      bool dDjfyGLdCy = false;
      bool pTHWUhNyfA = false;
      bool ryEYYTjZQG = false;
      string scXunkljNm;
      string IfXNtcjokp;
      string SeOsWwUsXn;
      string GlEVbPnRJX;
      string hGdQCjdZZO;
      string obMjOONdXq;
      string QsLYfVaCkd;
      string oReNHLAyqm;
      string RtTJzeZUGN;
      string BJsSHouFjf;
      string IbouYWxzbC;
      string NPmjZWYBYB;
      string wGuWbfXLFS;
      string QtOLeoFXkb;
      string hZrDzlWJrk;
      string PsfiiCgRSs;
      string yksJkSBaFj;
      string QBQxSVOqXp;
      string IOSUCXOebb;
      string InEqcwghRg;
      if(scXunkljNm == IbouYWxzbC){kuDITOciPN = true;}
      else if(IbouYWxzbC == scXunkljNm){CpCjUXlIkD = true;}
      if(IfXNtcjokp == NPmjZWYBYB){notcjjRXGN = true;}
      else if(NPmjZWYBYB == IfXNtcjokp){IKlWGwkoAr = true;}
      if(SeOsWwUsXn == wGuWbfXLFS){EVzcbcwYTW = true;}
      else if(wGuWbfXLFS == SeOsWwUsXn){DuoiFnbLwa = true;}
      if(GlEVbPnRJX == QtOLeoFXkb){ofYpEMKKBn = true;}
      else if(QtOLeoFXkb == GlEVbPnRJX){IiuIHsShFU = true;}
      if(hGdQCjdZZO == hZrDzlWJrk){uePNnSsaHs = true;}
      else if(hZrDzlWJrk == hGdQCjdZZO){twiKfGyHEZ = true;}
      if(obMjOONdXq == PsfiiCgRSs){eIaEbOuafp = true;}
      else if(PsfiiCgRSs == obMjOONdXq){FaVxcGBTdf = true;}
      if(QsLYfVaCkd == yksJkSBaFj){RDPsYHQDYW = true;}
      else if(yksJkSBaFj == QsLYfVaCkd){uZLJtYOcPN = true;}
      if(oReNHLAyqm == QBQxSVOqXp){YGWSSYGkoJ = true;}
      if(RtTJzeZUGN == IOSUCXOebb){iVRZrfEUOo = true;}
      if(BJsSHouFjf == InEqcwghRg){RjeKVqPWof = true;}
      while(QBQxSVOqXp == oReNHLAyqm){dDjfyGLdCy = true;}
      while(IOSUCXOebb == IOSUCXOebb){pTHWUhNyfA = true;}
      while(InEqcwghRg == InEqcwghRg){ryEYYTjZQG = true;}
      if(kuDITOciPN == true){kuDITOciPN = false;}
      if(notcjjRXGN == true){notcjjRXGN = false;}
      if(EVzcbcwYTW == true){EVzcbcwYTW = false;}
      if(ofYpEMKKBn == true){ofYpEMKKBn = false;}
      if(uePNnSsaHs == true){uePNnSsaHs = false;}
      if(eIaEbOuafp == true){eIaEbOuafp = false;}
      if(RDPsYHQDYW == true){RDPsYHQDYW = false;}
      if(YGWSSYGkoJ == true){YGWSSYGkoJ = false;}
      if(iVRZrfEUOo == true){iVRZrfEUOo = false;}
      if(RjeKVqPWof == true){RjeKVqPWof = false;}
      if(CpCjUXlIkD == true){CpCjUXlIkD = false;}
      if(IKlWGwkoAr == true){IKlWGwkoAr = false;}
      if(DuoiFnbLwa == true){DuoiFnbLwa = false;}
      if(IiuIHsShFU == true){IiuIHsShFU = false;}
      if(twiKfGyHEZ == true){twiKfGyHEZ = false;}
      if(FaVxcGBTdf == true){FaVxcGBTdf = false;}
      if(uZLJtYOcPN == true){uZLJtYOcPN = false;}
      if(dDjfyGLdCy == true){dDjfyGLdCy = false;}
      if(pTHWUhNyfA == true){pTHWUhNyfA = false;}
      if(ryEYYTjZQG == true){ryEYYTjZQG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TRTTFGMLEG
{ 
  void FNVSBhfwff()
  { 
      bool NAFRNDmlTI = false;
      bool VMGLMtYKYI = false;
      bool uPfsDAgAdC = false;
      bool YBeaUpphRU = false;
      bool HHxSFArIbA = false;
      bool FFKiZxTMNN = false;
      bool VlHRjUhfqW = false;
      bool EprEAmSNnD = false;
      bool HYYdwTpuAW = false;
      bool VdUDyUzeik = false;
      bool RLRFwOMGil = false;
      bool eGYJFxNdUP = false;
      bool dlfTBZVoFe = false;
      bool nmdCkuGSgg = false;
      bool GjMNqOELxB = false;
      bool HVJSHffyEV = false;
      bool sXADyrbVXK = false;
      bool qtxmJsZRbl = false;
      bool UKqEXRcLuF = false;
      bool OHOKniiIOz = false;
      string keyiyFjMai;
      string NRYuPiyfoc;
      string WLdwSnnfkQ;
      string pemifsswEf;
      string amhbbGqZsq;
      string QhqcLYACQJ;
      string QDbKridoOV;
      string oCbIBjcBTL;
      string xOlszInJWG;
      string sqetPWLWjs;
      string bBLWBNFhbb;
      string uyhEMCRhLi;
      string uTRHcyWgrd;
      string XGRZiuCOrk;
      string CFhuLtIahN;
      string FcLAyHiDtC;
      string pXoxDogIUQ;
      string zCpZgolWwh;
      string pwzeXutQbb;
      string MzUoudPjrV;
      if(keyiyFjMai == bBLWBNFhbb){NAFRNDmlTI = true;}
      else if(bBLWBNFhbb == keyiyFjMai){RLRFwOMGil = true;}
      if(NRYuPiyfoc == uyhEMCRhLi){VMGLMtYKYI = true;}
      else if(uyhEMCRhLi == NRYuPiyfoc){eGYJFxNdUP = true;}
      if(WLdwSnnfkQ == uTRHcyWgrd){uPfsDAgAdC = true;}
      else if(uTRHcyWgrd == WLdwSnnfkQ){dlfTBZVoFe = true;}
      if(pemifsswEf == XGRZiuCOrk){YBeaUpphRU = true;}
      else if(XGRZiuCOrk == pemifsswEf){nmdCkuGSgg = true;}
      if(amhbbGqZsq == CFhuLtIahN){HHxSFArIbA = true;}
      else if(CFhuLtIahN == amhbbGqZsq){GjMNqOELxB = true;}
      if(QhqcLYACQJ == FcLAyHiDtC){FFKiZxTMNN = true;}
      else if(FcLAyHiDtC == QhqcLYACQJ){HVJSHffyEV = true;}
      if(QDbKridoOV == pXoxDogIUQ){VlHRjUhfqW = true;}
      else if(pXoxDogIUQ == QDbKridoOV){sXADyrbVXK = true;}
      if(oCbIBjcBTL == zCpZgolWwh){EprEAmSNnD = true;}
      if(xOlszInJWG == pwzeXutQbb){HYYdwTpuAW = true;}
      if(sqetPWLWjs == MzUoudPjrV){VdUDyUzeik = true;}
      while(zCpZgolWwh == oCbIBjcBTL){qtxmJsZRbl = true;}
      while(pwzeXutQbb == pwzeXutQbb){UKqEXRcLuF = true;}
      while(MzUoudPjrV == MzUoudPjrV){OHOKniiIOz = true;}
      if(NAFRNDmlTI == true){NAFRNDmlTI = false;}
      if(VMGLMtYKYI == true){VMGLMtYKYI = false;}
      if(uPfsDAgAdC == true){uPfsDAgAdC = false;}
      if(YBeaUpphRU == true){YBeaUpphRU = false;}
      if(HHxSFArIbA == true){HHxSFArIbA = false;}
      if(FFKiZxTMNN == true){FFKiZxTMNN = false;}
      if(VlHRjUhfqW == true){VlHRjUhfqW = false;}
      if(EprEAmSNnD == true){EprEAmSNnD = false;}
      if(HYYdwTpuAW == true){HYYdwTpuAW = false;}
      if(VdUDyUzeik == true){VdUDyUzeik = false;}
      if(RLRFwOMGil == true){RLRFwOMGil = false;}
      if(eGYJFxNdUP == true){eGYJFxNdUP = false;}
      if(dlfTBZVoFe == true){dlfTBZVoFe = false;}
      if(nmdCkuGSgg == true){nmdCkuGSgg = false;}
      if(GjMNqOELxB == true){GjMNqOELxB = false;}
      if(HVJSHffyEV == true){HVJSHffyEV = false;}
      if(sXADyrbVXK == true){sXADyrbVXK = false;}
      if(qtxmJsZRbl == true){qtxmJsZRbl = false;}
      if(UKqEXRcLuF == true){UKqEXRcLuF = false;}
      if(OHOKniiIOz == true){OHOKniiIOz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JWLGYOLRWN
{ 
  void PltsqUTyAF()
  { 
      bool LRnrKSPsbo = false;
      bool KpiIwFNyNl = false;
      bool CKkQEqLwjU = false;
      bool JSgnEphVUt = false;
      bool IUoEpbFdeY = false;
      bool KgPPUBfXmT = false;
      bool GSJGeqJuEF = false;
      bool WrcTchUgZc = false;
      bool khQKKcCRSD = false;
      bool KKhBmoLiYy = false;
      bool SJZZBSDwll = false;
      bool fzxKhYByuC = false;
      bool oqbBuMKbfm = false;
      bool WlHbJbHqIr = false;
      bool YFefWKNWSN = false;
      bool nMmWJahYdo = false;
      bool HbQzPsqVAG = false;
      bool RJpDciLudk = false;
      bool ymIRzKzkRh = false;
      bool siNSjwofQd = false;
      string CpKooCYMRc;
      string IxwqZWoUiq;
      string BPXAtMFXNg;
      string ZtfQOUNcJE;
      string fsOTtazYhU;
      string SRgSfmSKtc;
      string xBzkCNQebF;
      string JLLeKHADFT;
      string MgosOHNNjb;
      string BChfHetdQf;
      string KTwcLGGCHX;
      string mOFaPPLFVu;
      string ACtADGdeWf;
      string NVmZIrjMgH;
      string AKFLomxGQq;
      string SnHVeHYuYF;
      string cbebKQbeRX;
      string fzYOtpxiLP;
      string IWNfNYNQtB;
      string SombeYfdBX;
      if(CpKooCYMRc == KTwcLGGCHX){LRnrKSPsbo = true;}
      else if(KTwcLGGCHX == CpKooCYMRc){SJZZBSDwll = true;}
      if(IxwqZWoUiq == mOFaPPLFVu){KpiIwFNyNl = true;}
      else if(mOFaPPLFVu == IxwqZWoUiq){fzxKhYByuC = true;}
      if(BPXAtMFXNg == ACtADGdeWf){CKkQEqLwjU = true;}
      else if(ACtADGdeWf == BPXAtMFXNg){oqbBuMKbfm = true;}
      if(ZtfQOUNcJE == NVmZIrjMgH){JSgnEphVUt = true;}
      else if(NVmZIrjMgH == ZtfQOUNcJE){WlHbJbHqIr = true;}
      if(fsOTtazYhU == AKFLomxGQq){IUoEpbFdeY = true;}
      else if(AKFLomxGQq == fsOTtazYhU){YFefWKNWSN = true;}
      if(SRgSfmSKtc == SnHVeHYuYF){KgPPUBfXmT = true;}
      else if(SnHVeHYuYF == SRgSfmSKtc){nMmWJahYdo = true;}
      if(xBzkCNQebF == cbebKQbeRX){GSJGeqJuEF = true;}
      else if(cbebKQbeRX == xBzkCNQebF){HbQzPsqVAG = true;}
      if(JLLeKHADFT == fzYOtpxiLP){WrcTchUgZc = true;}
      if(MgosOHNNjb == IWNfNYNQtB){khQKKcCRSD = true;}
      if(BChfHetdQf == SombeYfdBX){KKhBmoLiYy = true;}
      while(fzYOtpxiLP == JLLeKHADFT){RJpDciLudk = true;}
      while(IWNfNYNQtB == IWNfNYNQtB){ymIRzKzkRh = true;}
      while(SombeYfdBX == SombeYfdBX){siNSjwofQd = true;}
      if(LRnrKSPsbo == true){LRnrKSPsbo = false;}
      if(KpiIwFNyNl == true){KpiIwFNyNl = false;}
      if(CKkQEqLwjU == true){CKkQEqLwjU = false;}
      if(JSgnEphVUt == true){JSgnEphVUt = false;}
      if(IUoEpbFdeY == true){IUoEpbFdeY = false;}
      if(KgPPUBfXmT == true){KgPPUBfXmT = false;}
      if(GSJGeqJuEF == true){GSJGeqJuEF = false;}
      if(WrcTchUgZc == true){WrcTchUgZc = false;}
      if(khQKKcCRSD == true){khQKKcCRSD = false;}
      if(KKhBmoLiYy == true){KKhBmoLiYy = false;}
      if(SJZZBSDwll == true){SJZZBSDwll = false;}
      if(fzxKhYByuC == true){fzxKhYByuC = false;}
      if(oqbBuMKbfm == true){oqbBuMKbfm = false;}
      if(WlHbJbHqIr == true){WlHbJbHqIr = false;}
      if(YFefWKNWSN == true){YFefWKNWSN = false;}
      if(nMmWJahYdo == true){nMmWJahYdo = false;}
      if(HbQzPsqVAG == true){HbQzPsqVAG = false;}
      if(RJpDciLudk == true){RJpDciLudk = false;}
      if(ymIRzKzkRh == true){ymIRzKzkRh = false;}
      if(siNSjwofQd == true){siNSjwofQd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NTCFLVXUHH
{ 
  void FjqhcQYgON()
  { 
      bool KOLCxtXuEQ = false;
      bool JxOCbiUPba = false;
      bool aqnfIPbfqc = false;
      bool cNAFKhgEPR = false;
      bool jtpWkjpPBP = false;
      bool GgVTTTZeth = false;
      bool SqEamuxIrt = false;
      bool CQzJpgARuY = false;
      bool ZLdaWwrfkp = false;
      bool HBJhzsoOio = false;
      bool lgXHNogLdm = false;
      bool THjUHHMdEq = false;
      bool DRXBlAGRKx = false;
      bool rkiFlsmWNh = false;
      bool OgCyWzQoZq = false;
      bool fKKqlUJVUM = false;
      bool iPAfthYeiO = false;
      bool TpQVcWPYem = false;
      bool jRqTRgZqTQ = false;
      bool jRCAzyfVDn = false;
      string AobLKVEqzJ;
      string KZApLNUkXX;
      string MeayhxmjNA;
      string VbxTZDbJYm;
      string uZBFawCrAy;
      string SorTNVNddN;
      string hUdynibgQI;
      string kLMjcmdVWk;
      string uuiPhfidGD;
      string oyfLEawCQq;
      string TUbrMHcIqa;
      string rqHrRmkNQH;
      string AyaMTmfAeC;
      string paEeQaSqDa;
      string DZleLxqmsR;
      string ohkJqVsOXY;
      string bbcojQlbap;
      string TtKpEZLuAV;
      string wrHNMIoumu;
      string hESdzaxxuu;
      if(AobLKVEqzJ == TUbrMHcIqa){KOLCxtXuEQ = true;}
      else if(TUbrMHcIqa == AobLKVEqzJ){lgXHNogLdm = true;}
      if(KZApLNUkXX == rqHrRmkNQH){JxOCbiUPba = true;}
      else if(rqHrRmkNQH == KZApLNUkXX){THjUHHMdEq = true;}
      if(MeayhxmjNA == AyaMTmfAeC){aqnfIPbfqc = true;}
      else if(AyaMTmfAeC == MeayhxmjNA){DRXBlAGRKx = true;}
      if(VbxTZDbJYm == paEeQaSqDa){cNAFKhgEPR = true;}
      else if(paEeQaSqDa == VbxTZDbJYm){rkiFlsmWNh = true;}
      if(uZBFawCrAy == DZleLxqmsR){jtpWkjpPBP = true;}
      else if(DZleLxqmsR == uZBFawCrAy){OgCyWzQoZq = true;}
      if(SorTNVNddN == ohkJqVsOXY){GgVTTTZeth = true;}
      else if(ohkJqVsOXY == SorTNVNddN){fKKqlUJVUM = true;}
      if(hUdynibgQI == bbcojQlbap){SqEamuxIrt = true;}
      else if(bbcojQlbap == hUdynibgQI){iPAfthYeiO = true;}
      if(kLMjcmdVWk == TtKpEZLuAV){CQzJpgARuY = true;}
      if(uuiPhfidGD == wrHNMIoumu){ZLdaWwrfkp = true;}
      if(oyfLEawCQq == hESdzaxxuu){HBJhzsoOio = true;}
      while(TtKpEZLuAV == kLMjcmdVWk){TpQVcWPYem = true;}
      while(wrHNMIoumu == wrHNMIoumu){jRqTRgZqTQ = true;}
      while(hESdzaxxuu == hESdzaxxuu){jRCAzyfVDn = true;}
      if(KOLCxtXuEQ == true){KOLCxtXuEQ = false;}
      if(JxOCbiUPba == true){JxOCbiUPba = false;}
      if(aqnfIPbfqc == true){aqnfIPbfqc = false;}
      if(cNAFKhgEPR == true){cNAFKhgEPR = false;}
      if(jtpWkjpPBP == true){jtpWkjpPBP = false;}
      if(GgVTTTZeth == true){GgVTTTZeth = false;}
      if(SqEamuxIrt == true){SqEamuxIrt = false;}
      if(CQzJpgARuY == true){CQzJpgARuY = false;}
      if(ZLdaWwrfkp == true){ZLdaWwrfkp = false;}
      if(HBJhzsoOio == true){HBJhzsoOio = false;}
      if(lgXHNogLdm == true){lgXHNogLdm = false;}
      if(THjUHHMdEq == true){THjUHHMdEq = false;}
      if(DRXBlAGRKx == true){DRXBlAGRKx = false;}
      if(rkiFlsmWNh == true){rkiFlsmWNh = false;}
      if(OgCyWzQoZq == true){OgCyWzQoZq = false;}
      if(fKKqlUJVUM == true){fKKqlUJVUM = false;}
      if(iPAfthYeiO == true){iPAfthYeiO = false;}
      if(TpQVcWPYem == true){TpQVcWPYem = false;}
      if(jRqTRgZqTQ == true){jRqTRgZqTQ = false;}
      if(jRCAzyfVDn == true){jRCAzyfVDn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IAULZUYFLD
{ 
  void ypwwncUMui()
  { 
      bool lbxxSfFWMl = false;
      bool woCaDDgVrR = false;
      bool XbQUKfLyAw = false;
      bool jYeInZFEmh = false;
      bool ltdUaYkmzh = false;
      bool JIuEDKKclm = false;
      bool THWPBWJtmc = false;
      bool xchKecywsl = false;
      bool uYyRlbcaEc = false;
      bool PcRANeXNSD = false;
      bool OpzVjgZkZa = false;
      bool MNizqtIEdY = false;
      bool thoJNUKgwA = false;
      bool FjcpXEZchE = false;
      bool BqAdQBsRIT = false;
      bool VSjsJfBoIP = false;
      bool WsoZUbkrbm = false;
      bool UfWYXChKrM = false;
      bool asXcdlzjgq = false;
      bool DjTShICaIo = false;
      string gNISfzMdEw;
      string WyokRVjZUD;
      string GJDyxZmYEn;
      string FYRQDXogEs;
      string kpzCUyxWan;
      string zbwtZXJJVF;
      string LnZPpxfYgs;
      string gCVaSQJBdy;
      string cQxPndbXpf;
      string NeLyhxQjLW;
      string RYogHxFVbJ;
      string OIeWcupJbL;
      string VIhBfBqWsU;
      string zYpHfEaPIq;
      string YGufQFznVl;
      string GGHzBJpmBF;
      string FhbGJoSXqX;
      string TZBkmONBjZ;
      string CCBGOrRpGW;
      string NmOCkpdnVb;
      if(gNISfzMdEw == RYogHxFVbJ){lbxxSfFWMl = true;}
      else if(RYogHxFVbJ == gNISfzMdEw){OpzVjgZkZa = true;}
      if(WyokRVjZUD == OIeWcupJbL){woCaDDgVrR = true;}
      else if(OIeWcupJbL == WyokRVjZUD){MNizqtIEdY = true;}
      if(GJDyxZmYEn == VIhBfBqWsU){XbQUKfLyAw = true;}
      else if(VIhBfBqWsU == GJDyxZmYEn){thoJNUKgwA = true;}
      if(FYRQDXogEs == zYpHfEaPIq){jYeInZFEmh = true;}
      else if(zYpHfEaPIq == FYRQDXogEs){FjcpXEZchE = true;}
      if(kpzCUyxWan == YGufQFznVl){ltdUaYkmzh = true;}
      else if(YGufQFznVl == kpzCUyxWan){BqAdQBsRIT = true;}
      if(zbwtZXJJVF == GGHzBJpmBF){JIuEDKKclm = true;}
      else if(GGHzBJpmBF == zbwtZXJJVF){VSjsJfBoIP = true;}
      if(LnZPpxfYgs == FhbGJoSXqX){THWPBWJtmc = true;}
      else if(FhbGJoSXqX == LnZPpxfYgs){WsoZUbkrbm = true;}
      if(gCVaSQJBdy == TZBkmONBjZ){xchKecywsl = true;}
      if(cQxPndbXpf == CCBGOrRpGW){uYyRlbcaEc = true;}
      if(NeLyhxQjLW == NmOCkpdnVb){PcRANeXNSD = true;}
      while(TZBkmONBjZ == gCVaSQJBdy){UfWYXChKrM = true;}
      while(CCBGOrRpGW == CCBGOrRpGW){asXcdlzjgq = true;}
      while(NmOCkpdnVb == NmOCkpdnVb){DjTShICaIo = true;}
      if(lbxxSfFWMl == true){lbxxSfFWMl = false;}
      if(woCaDDgVrR == true){woCaDDgVrR = false;}
      if(XbQUKfLyAw == true){XbQUKfLyAw = false;}
      if(jYeInZFEmh == true){jYeInZFEmh = false;}
      if(ltdUaYkmzh == true){ltdUaYkmzh = false;}
      if(JIuEDKKclm == true){JIuEDKKclm = false;}
      if(THWPBWJtmc == true){THWPBWJtmc = false;}
      if(xchKecywsl == true){xchKecywsl = false;}
      if(uYyRlbcaEc == true){uYyRlbcaEc = false;}
      if(PcRANeXNSD == true){PcRANeXNSD = false;}
      if(OpzVjgZkZa == true){OpzVjgZkZa = false;}
      if(MNizqtIEdY == true){MNizqtIEdY = false;}
      if(thoJNUKgwA == true){thoJNUKgwA = false;}
      if(FjcpXEZchE == true){FjcpXEZchE = false;}
      if(BqAdQBsRIT == true){BqAdQBsRIT = false;}
      if(VSjsJfBoIP == true){VSjsJfBoIP = false;}
      if(WsoZUbkrbm == true){WsoZUbkrbm = false;}
      if(UfWYXChKrM == true){UfWYXChKrM = false;}
      if(asXcdlzjgq == true){asXcdlzjgq = false;}
      if(DjTShICaIo == true){DjTShICaIo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HZNOZQQNSJ
{ 
  void iGfbTMtlGO()
  { 
      bool PnFRnfesrW = false;
      bool DXWwIwFREF = false;
      bool GQJwwdmhJK = false;
      bool fToDCAhYZx = false;
      bool HkDRUcFtYX = false;
      bool xLpCTzdJUK = false;
      bool rwjhqihStH = false;
      bool OgqGxUNraT = false;
      bool XsJkMUdljC = false;
      bool VXDPELBUak = false;
      bool tlzQJPTiFy = false;
      bool llhBlzlyUV = false;
      bool FwirlpcbBl = false;
      bool TrRpYlssbw = false;
      bool BtglQipCdF = false;
      bool YDAEeyDHdS = false;
      bool mrhSetUqbA = false;
      bool GsWYULOwaC = false;
      bool zZywMPrMKZ = false;
      bool hkOIJJLNGV = false;
      string nhlxmzEAlF;
      string qqjfCiqhNd;
      string zuBsqcxFGB;
      string qXDOqUAqsd;
      string tgogUunepG;
      string ypYFqrfsGJ;
      string BzskNSnUnh;
      string izojiSFTXw;
      string oSOADAyyXy;
      string nHkibumESB;
      string GSpIXyBoVX;
      string mMUKThjrhM;
      string TpxosaOFIn;
      string fBAWoVcFcE;
      string zJbzLblaPs;
      string KtWFgQUAOw;
      string jwfhqkLyUx;
      string FdPcNJNxdR;
      string nmpOdleuoX;
      string AbqgTDdtIZ;
      if(nhlxmzEAlF == GSpIXyBoVX){PnFRnfesrW = true;}
      else if(GSpIXyBoVX == nhlxmzEAlF){tlzQJPTiFy = true;}
      if(qqjfCiqhNd == mMUKThjrhM){DXWwIwFREF = true;}
      else if(mMUKThjrhM == qqjfCiqhNd){llhBlzlyUV = true;}
      if(zuBsqcxFGB == TpxosaOFIn){GQJwwdmhJK = true;}
      else if(TpxosaOFIn == zuBsqcxFGB){FwirlpcbBl = true;}
      if(qXDOqUAqsd == fBAWoVcFcE){fToDCAhYZx = true;}
      else if(fBAWoVcFcE == qXDOqUAqsd){TrRpYlssbw = true;}
      if(tgogUunepG == zJbzLblaPs){HkDRUcFtYX = true;}
      else if(zJbzLblaPs == tgogUunepG){BtglQipCdF = true;}
      if(ypYFqrfsGJ == KtWFgQUAOw){xLpCTzdJUK = true;}
      else if(KtWFgQUAOw == ypYFqrfsGJ){YDAEeyDHdS = true;}
      if(BzskNSnUnh == jwfhqkLyUx){rwjhqihStH = true;}
      else if(jwfhqkLyUx == BzskNSnUnh){mrhSetUqbA = true;}
      if(izojiSFTXw == FdPcNJNxdR){OgqGxUNraT = true;}
      if(oSOADAyyXy == nmpOdleuoX){XsJkMUdljC = true;}
      if(nHkibumESB == AbqgTDdtIZ){VXDPELBUak = true;}
      while(FdPcNJNxdR == izojiSFTXw){GsWYULOwaC = true;}
      while(nmpOdleuoX == nmpOdleuoX){zZywMPrMKZ = true;}
      while(AbqgTDdtIZ == AbqgTDdtIZ){hkOIJJLNGV = true;}
      if(PnFRnfesrW == true){PnFRnfesrW = false;}
      if(DXWwIwFREF == true){DXWwIwFREF = false;}
      if(GQJwwdmhJK == true){GQJwwdmhJK = false;}
      if(fToDCAhYZx == true){fToDCAhYZx = false;}
      if(HkDRUcFtYX == true){HkDRUcFtYX = false;}
      if(xLpCTzdJUK == true){xLpCTzdJUK = false;}
      if(rwjhqihStH == true){rwjhqihStH = false;}
      if(OgqGxUNraT == true){OgqGxUNraT = false;}
      if(XsJkMUdljC == true){XsJkMUdljC = false;}
      if(VXDPELBUak == true){VXDPELBUak = false;}
      if(tlzQJPTiFy == true){tlzQJPTiFy = false;}
      if(llhBlzlyUV == true){llhBlzlyUV = false;}
      if(FwirlpcbBl == true){FwirlpcbBl = false;}
      if(TrRpYlssbw == true){TrRpYlssbw = false;}
      if(BtglQipCdF == true){BtglQipCdF = false;}
      if(YDAEeyDHdS == true){YDAEeyDHdS = false;}
      if(mrhSetUqbA == true){mrhSetUqbA = false;}
      if(GsWYULOwaC == true){GsWYULOwaC = false;}
      if(zZywMPrMKZ == true){zZywMPrMKZ = false;}
      if(hkOIJJLNGV == true){hkOIJJLNGV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TLJNXSFPXV
{ 
  void hkigSQGJKS()
  { 
      bool YyrlXkmiKX = false;
      bool sXLXFTBUId = false;
      bool qTSNpLoykD = false;
      bool MUQQKgZkHe = false;
      bool rtoetbfgoX = false;
      bool cmfnAFeewM = false;
      bool woxHKXHuMY = false;
      bool sPMckwenTO = false;
      bool eHJMZYobPF = false;
      bool CunuiDxgTV = false;
      bool TkTPeMaCDE = false;
      bool ZqKhgnfjhk = false;
      bool iefHWyaRth = false;
      bool zxTxttmshM = false;
      bool ymYLeKjGNu = false;
      bool XMzimnFMsg = false;
      bool kJIUEcXNnm = false;
      bool AlCUmwGUcL = false;
      bool NUDyKlxkKF = false;
      bool naABaodDGC = false;
      string ZBXQXKVkww;
      string REymWPoZMd;
      string SGRkGBpQrQ;
      string fXsoroatyM;
      string syytQmblSZ;
      string qCHHpSimKW;
      string UFrfPtKJuh;
      string nubzjTIWTS;
      string YDxRYdQlyY;
      string FnjarmGSeW;
      string bRqjlwZHWW;
      string KMSqxQHZGl;
      string dYKWcAKBHx;
      string MorwpHMMfc;
      string DIObNsUrcb;
      string fgLrsDGUHk;
      string kYAZJUTWAp;
      string DtschUJiIj;
      string eRXfQfdzDm;
      string ArFuqeIoRr;
      if(ZBXQXKVkww == bRqjlwZHWW){YyrlXkmiKX = true;}
      else if(bRqjlwZHWW == ZBXQXKVkww){TkTPeMaCDE = true;}
      if(REymWPoZMd == KMSqxQHZGl){sXLXFTBUId = true;}
      else if(KMSqxQHZGl == REymWPoZMd){ZqKhgnfjhk = true;}
      if(SGRkGBpQrQ == dYKWcAKBHx){qTSNpLoykD = true;}
      else if(dYKWcAKBHx == SGRkGBpQrQ){iefHWyaRth = true;}
      if(fXsoroatyM == MorwpHMMfc){MUQQKgZkHe = true;}
      else if(MorwpHMMfc == fXsoroatyM){zxTxttmshM = true;}
      if(syytQmblSZ == DIObNsUrcb){rtoetbfgoX = true;}
      else if(DIObNsUrcb == syytQmblSZ){ymYLeKjGNu = true;}
      if(qCHHpSimKW == fgLrsDGUHk){cmfnAFeewM = true;}
      else if(fgLrsDGUHk == qCHHpSimKW){XMzimnFMsg = true;}
      if(UFrfPtKJuh == kYAZJUTWAp){woxHKXHuMY = true;}
      else if(kYAZJUTWAp == UFrfPtKJuh){kJIUEcXNnm = true;}
      if(nubzjTIWTS == DtschUJiIj){sPMckwenTO = true;}
      if(YDxRYdQlyY == eRXfQfdzDm){eHJMZYobPF = true;}
      if(FnjarmGSeW == ArFuqeIoRr){CunuiDxgTV = true;}
      while(DtschUJiIj == nubzjTIWTS){AlCUmwGUcL = true;}
      while(eRXfQfdzDm == eRXfQfdzDm){NUDyKlxkKF = true;}
      while(ArFuqeIoRr == ArFuqeIoRr){naABaodDGC = true;}
      if(YyrlXkmiKX == true){YyrlXkmiKX = false;}
      if(sXLXFTBUId == true){sXLXFTBUId = false;}
      if(qTSNpLoykD == true){qTSNpLoykD = false;}
      if(MUQQKgZkHe == true){MUQQKgZkHe = false;}
      if(rtoetbfgoX == true){rtoetbfgoX = false;}
      if(cmfnAFeewM == true){cmfnAFeewM = false;}
      if(woxHKXHuMY == true){woxHKXHuMY = false;}
      if(sPMckwenTO == true){sPMckwenTO = false;}
      if(eHJMZYobPF == true){eHJMZYobPF = false;}
      if(CunuiDxgTV == true){CunuiDxgTV = false;}
      if(TkTPeMaCDE == true){TkTPeMaCDE = false;}
      if(ZqKhgnfjhk == true){ZqKhgnfjhk = false;}
      if(iefHWyaRth == true){iefHWyaRth = false;}
      if(zxTxttmshM == true){zxTxttmshM = false;}
      if(ymYLeKjGNu == true){ymYLeKjGNu = false;}
      if(XMzimnFMsg == true){XMzimnFMsg = false;}
      if(kJIUEcXNnm == true){kJIUEcXNnm = false;}
      if(AlCUmwGUcL == true){AlCUmwGUcL = false;}
      if(NUDyKlxkKF == true){NUDyKlxkKF = false;}
      if(naABaodDGC == true){naABaodDGC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NECYQXCPQD
{ 
  void hPybglsiYQ()
  { 
      bool amZENbkySl = false;
      bool cSwbUThqko = false;
      bool yGQOjxXrsI = false;
      bool oCMtfYKHij = false;
      bool dDRUinhngs = false;
      bool bTPhKUWLTQ = false;
      bool EsEKwZGCwu = false;
      bool JaIALunwew = false;
      bool OiLzfVmdjK = false;
      bool CymRfkyHXJ = false;
      bool gfrkjAKOWO = false;
      bool fZfXBUgEda = false;
      bool mcSlsKnqUa = false;
      bool wgYVOiqZPe = false;
      bool LXGUebSOQK = false;
      bool DtcxVENFrZ = false;
      bool MTswSyBJJS = false;
      bool dHoyOOVxHQ = false;
      bool rZZKWCDbAK = false;
      bool VkgpSrdKBf = false;
      string rOnUThZNis;
      string EJbqgYOlZr;
      string iyTqdmjZuC;
      string OejjLaYJes;
      string HcLnLFJrPF;
      string tIGLGttwpf;
      string xASgdYYqeG;
      string AEGgkFlffX;
      string cqJoHGYYdR;
      string gbSzuHJeJl;
      string fRNJFpBZaA;
      string HNQRDFpdYX;
      string zANNZXkHkd;
      string uHWsqLdAiR;
      string EzxcJSKAwo;
      string RfFlmfDzig;
      string EtnxEAqXaq;
      string botHSADjDG;
      string MjLwMPBkGL;
      string HdQBNKKAXJ;
      if(rOnUThZNis == fRNJFpBZaA){amZENbkySl = true;}
      else if(fRNJFpBZaA == rOnUThZNis){gfrkjAKOWO = true;}
      if(EJbqgYOlZr == HNQRDFpdYX){cSwbUThqko = true;}
      else if(HNQRDFpdYX == EJbqgYOlZr){fZfXBUgEda = true;}
      if(iyTqdmjZuC == zANNZXkHkd){yGQOjxXrsI = true;}
      else if(zANNZXkHkd == iyTqdmjZuC){mcSlsKnqUa = true;}
      if(OejjLaYJes == uHWsqLdAiR){oCMtfYKHij = true;}
      else if(uHWsqLdAiR == OejjLaYJes){wgYVOiqZPe = true;}
      if(HcLnLFJrPF == EzxcJSKAwo){dDRUinhngs = true;}
      else if(EzxcJSKAwo == HcLnLFJrPF){LXGUebSOQK = true;}
      if(tIGLGttwpf == RfFlmfDzig){bTPhKUWLTQ = true;}
      else if(RfFlmfDzig == tIGLGttwpf){DtcxVENFrZ = true;}
      if(xASgdYYqeG == EtnxEAqXaq){EsEKwZGCwu = true;}
      else if(EtnxEAqXaq == xASgdYYqeG){MTswSyBJJS = true;}
      if(AEGgkFlffX == botHSADjDG){JaIALunwew = true;}
      if(cqJoHGYYdR == MjLwMPBkGL){OiLzfVmdjK = true;}
      if(gbSzuHJeJl == HdQBNKKAXJ){CymRfkyHXJ = true;}
      while(botHSADjDG == AEGgkFlffX){dHoyOOVxHQ = true;}
      while(MjLwMPBkGL == MjLwMPBkGL){rZZKWCDbAK = true;}
      while(HdQBNKKAXJ == HdQBNKKAXJ){VkgpSrdKBf = true;}
      if(amZENbkySl == true){amZENbkySl = false;}
      if(cSwbUThqko == true){cSwbUThqko = false;}
      if(yGQOjxXrsI == true){yGQOjxXrsI = false;}
      if(oCMtfYKHij == true){oCMtfYKHij = false;}
      if(dDRUinhngs == true){dDRUinhngs = false;}
      if(bTPhKUWLTQ == true){bTPhKUWLTQ = false;}
      if(EsEKwZGCwu == true){EsEKwZGCwu = false;}
      if(JaIALunwew == true){JaIALunwew = false;}
      if(OiLzfVmdjK == true){OiLzfVmdjK = false;}
      if(CymRfkyHXJ == true){CymRfkyHXJ = false;}
      if(gfrkjAKOWO == true){gfrkjAKOWO = false;}
      if(fZfXBUgEda == true){fZfXBUgEda = false;}
      if(mcSlsKnqUa == true){mcSlsKnqUa = false;}
      if(wgYVOiqZPe == true){wgYVOiqZPe = false;}
      if(LXGUebSOQK == true){LXGUebSOQK = false;}
      if(DtcxVENFrZ == true){DtcxVENFrZ = false;}
      if(MTswSyBJJS == true){MTswSyBJJS = false;}
      if(dHoyOOVxHQ == true){dHoyOOVxHQ = false;}
      if(rZZKWCDbAK == true){rZZKWCDbAK = false;}
      if(VkgpSrdKBf == true){VkgpSrdKBf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AORRLNHNUJ
{ 
  void ceYwBPhoOl()
  { 
      bool SBaqVAZRfF = false;
      bool IcSAFVLadJ = false;
      bool CRcgjGOrOW = false;
      bool azAIPOSGhk = false;
      bool hbmOduhJHY = false;
      bool BAtpGAYsHP = false;
      bool khDIeIcJkp = false;
      bool CFrrbaeODn = false;
      bool XFkoUZFKCO = false;
      bool pZzSAAYdiU = false;
      bool SXXQWwICOf = false;
      bool UJoSrexNmF = false;
      bool CRHVAcFZqa = false;
      bool CBehVzgTSY = false;
      bool RDuVsfjfZU = false;
      bool CKpcRAQBQs = false;
      bool phKmcTeGxr = false;
      bool ycuOnzWkcT = false;
      bool rZzVXqLBQV = false;
      bool ieDYiirIrZ = false;
      string bAJWwoSxRm;
      string LQZEJeubKX;
      string esXoalCopj;
      string yhqiHAraTI;
      string VYcOtRmGcW;
      string WQOcLicTuJ;
      string mdGgocZpxI;
      string mTICCGQItJ;
      string zuMSNgTNXY;
      string XXfKUqSuYR;
      string qwJTjDIMaF;
      string RTZkKrRmTI;
      string JLSYkOnygK;
      string mUicRCkrhK;
      string XGmRGDytzc;
      string YeaQIfdkhV;
      string PKePRwkxTI;
      string GYEJjCXARh;
      string PsyEkItSTl;
      string XAJMuNbXAJ;
      if(bAJWwoSxRm == qwJTjDIMaF){SBaqVAZRfF = true;}
      else if(qwJTjDIMaF == bAJWwoSxRm){SXXQWwICOf = true;}
      if(LQZEJeubKX == RTZkKrRmTI){IcSAFVLadJ = true;}
      else if(RTZkKrRmTI == LQZEJeubKX){UJoSrexNmF = true;}
      if(esXoalCopj == JLSYkOnygK){CRcgjGOrOW = true;}
      else if(JLSYkOnygK == esXoalCopj){CRHVAcFZqa = true;}
      if(yhqiHAraTI == mUicRCkrhK){azAIPOSGhk = true;}
      else if(mUicRCkrhK == yhqiHAraTI){CBehVzgTSY = true;}
      if(VYcOtRmGcW == XGmRGDytzc){hbmOduhJHY = true;}
      else if(XGmRGDytzc == VYcOtRmGcW){RDuVsfjfZU = true;}
      if(WQOcLicTuJ == YeaQIfdkhV){BAtpGAYsHP = true;}
      else if(YeaQIfdkhV == WQOcLicTuJ){CKpcRAQBQs = true;}
      if(mdGgocZpxI == PKePRwkxTI){khDIeIcJkp = true;}
      else if(PKePRwkxTI == mdGgocZpxI){phKmcTeGxr = true;}
      if(mTICCGQItJ == GYEJjCXARh){CFrrbaeODn = true;}
      if(zuMSNgTNXY == PsyEkItSTl){XFkoUZFKCO = true;}
      if(XXfKUqSuYR == XAJMuNbXAJ){pZzSAAYdiU = true;}
      while(GYEJjCXARh == mTICCGQItJ){ycuOnzWkcT = true;}
      while(PsyEkItSTl == PsyEkItSTl){rZzVXqLBQV = true;}
      while(XAJMuNbXAJ == XAJMuNbXAJ){ieDYiirIrZ = true;}
      if(SBaqVAZRfF == true){SBaqVAZRfF = false;}
      if(IcSAFVLadJ == true){IcSAFVLadJ = false;}
      if(CRcgjGOrOW == true){CRcgjGOrOW = false;}
      if(azAIPOSGhk == true){azAIPOSGhk = false;}
      if(hbmOduhJHY == true){hbmOduhJHY = false;}
      if(BAtpGAYsHP == true){BAtpGAYsHP = false;}
      if(khDIeIcJkp == true){khDIeIcJkp = false;}
      if(CFrrbaeODn == true){CFrrbaeODn = false;}
      if(XFkoUZFKCO == true){XFkoUZFKCO = false;}
      if(pZzSAAYdiU == true){pZzSAAYdiU = false;}
      if(SXXQWwICOf == true){SXXQWwICOf = false;}
      if(UJoSrexNmF == true){UJoSrexNmF = false;}
      if(CRHVAcFZqa == true){CRHVAcFZqa = false;}
      if(CBehVzgTSY == true){CBehVzgTSY = false;}
      if(RDuVsfjfZU == true){RDuVsfjfZU = false;}
      if(CKpcRAQBQs == true){CKpcRAQBQs = false;}
      if(phKmcTeGxr == true){phKmcTeGxr = false;}
      if(ycuOnzWkcT == true){ycuOnzWkcT = false;}
      if(rZzVXqLBQV == true){rZzVXqLBQV = false;}
      if(ieDYiirIrZ == true){ieDYiirIrZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NBKOHANTOB
{ 
  void DIZNDVCSQB()
  { 
      bool kKWGDpmGYe = false;
      bool jYMRqrZrZL = false;
      bool OEfqlFdLgC = false;
      bool UsdcikAwUs = false;
      bool HxaFTSlPQW = false;
      bool bgMStfeeUx = false;
      bool MbYWKquihF = false;
      bool qdXfEQdZXT = false;
      bool SNtKZmfLiD = false;
      bool GVbWgfXDub = false;
      bool XDhLeyJgNc = false;
      bool BEHAdygOwX = false;
      bool LiAezUBAyX = false;
      bool rZeuuPfieb = false;
      bool cyxFBBOarh = false;
      bool yJHXQnDDLJ = false;
      bool wJipjaZLEO = false;
      bool SyiUtMktcy = false;
      bool GaHPYiSGeH = false;
      bool MbWVeSPHUZ = false;
      string cKCBfkuWWV;
      string rXORjiicDu;
      string RVjDXWczzM;
      string pUEZGzELzQ;
      string ctlshLSVhq;
      string ctiNfHZycJ;
      string HwXJeWSoLj;
      string dXdmRXiqVM;
      string EHQIiulqtz;
      string YFhpIgVcNK;
      string rcKxMFQuuI;
      string XicPEAePZi;
      string kbtMKYonek;
      string BGdLUawTud;
      string epwkapcRkH;
      string BGCdZPhylm;
      string PcQJGRERud;
      string ELTwEtfJlU;
      string wXCXjtDzkE;
      string rygIOCZleI;
      if(cKCBfkuWWV == rcKxMFQuuI){kKWGDpmGYe = true;}
      else if(rcKxMFQuuI == cKCBfkuWWV){XDhLeyJgNc = true;}
      if(rXORjiicDu == XicPEAePZi){jYMRqrZrZL = true;}
      else if(XicPEAePZi == rXORjiicDu){BEHAdygOwX = true;}
      if(RVjDXWczzM == kbtMKYonek){OEfqlFdLgC = true;}
      else if(kbtMKYonek == RVjDXWczzM){LiAezUBAyX = true;}
      if(pUEZGzELzQ == BGdLUawTud){UsdcikAwUs = true;}
      else if(BGdLUawTud == pUEZGzELzQ){rZeuuPfieb = true;}
      if(ctlshLSVhq == epwkapcRkH){HxaFTSlPQW = true;}
      else if(epwkapcRkH == ctlshLSVhq){cyxFBBOarh = true;}
      if(ctiNfHZycJ == BGCdZPhylm){bgMStfeeUx = true;}
      else if(BGCdZPhylm == ctiNfHZycJ){yJHXQnDDLJ = true;}
      if(HwXJeWSoLj == PcQJGRERud){MbYWKquihF = true;}
      else if(PcQJGRERud == HwXJeWSoLj){wJipjaZLEO = true;}
      if(dXdmRXiqVM == ELTwEtfJlU){qdXfEQdZXT = true;}
      if(EHQIiulqtz == wXCXjtDzkE){SNtKZmfLiD = true;}
      if(YFhpIgVcNK == rygIOCZleI){GVbWgfXDub = true;}
      while(ELTwEtfJlU == dXdmRXiqVM){SyiUtMktcy = true;}
      while(wXCXjtDzkE == wXCXjtDzkE){GaHPYiSGeH = true;}
      while(rygIOCZleI == rygIOCZleI){MbWVeSPHUZ = true;}
      if(kKWGDpmGYe == true){kKWGDpmGYe = false;}
      if(jYMRqrZrZL == true){jYMRqrZrZL = false;}
      if(OEfqlFdLgC == true){OEfqlFdLgC = false;}
      if(UsdcikAwUs == true){UsdcikAwUs = false;}
      if(HxaFTSlPQW == true){HxaFTSlPQW = false;}
      if(bgMStfeeUx == true){bgMStfeeUx = false;}
      if(MbYWKquihF == true){MbYWKquihF = false;}
      if(qdXfEQdZXT == true){qdXfEQdZXT = false;}
      if(SNtKZmfLiD == true){SNtKZmfLiD = false;}
      if(GVbWgfXDub == true){GVbWgfXDub = false;}
      if(XDhLeyJgNc == true){XDhLeyJgNc = false;}
      if(BEHAdygOwX == true){BEHAdygOwX = false;}
      if(LiAezUBAyX == true){LiAezUBAyX = false;}
      if(rZeuuPfieb == true){rZeuuPfieb = false;}
      if(cyxFBBOarh == true){cyxFBBOarh = false;}
      if(yJHXQnDDLJ == true){yJHXQnDDLJ = false;}
      if(wJipjaZLEO == true){wJipjaZLEO = false;}
      if(SyiUtMktcy == true){SyiUtMktcy = false;}
      if(GaHPYiSGeH == true){GaHPYiSGeH = false;}
      if(MbWVeSPHUZ == true){MbWVeSPHUZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EKCULMMBTF
{ 
  void WIuPsSAaCW()
  { 
      bool gFlnPbRUbt = false;
      bool fYoepMcjKN = false;
      bool NeOxndMLQK = false;
      bool UGkDSLgEFB = false;
      bool KSrLPbUuiQ = false;
      bool KKoZOCqnzk = false;
      bool OFDRYYmlLe = false;
      bool fYeIDtlDgM = false;
      bool IQcAzKQKoQ = false;
      bool UrFTlEPalp = false;
      bool nhjEklefWT = false;
      bool PnHlbycDRO = false;
      bool HbxtKnSLWy = false;
      bool eKQqXagYPM = false;
      bool ejnUAfjSqn = false;
      bool bMIXhLkotw = false;
      bool STJYoEWQNB = false;
      bool RDnEjXnbtd = false;
      bool DATiWSCsIM = false;
      bool oreStKZOfw = false;
      string RgborMnmHj;
      string sJWGugptxP;
      string amNEDDhejP;
      string dBxUNqfpGC;
      string QYNmQqCXOB;
      string cdYeWeSWlo;
      string eJCrGrLBrE;
      string BAmuzBZanM;
      string AKQilzcSyi;
      string XIDRWHWVgY;
      string eBeKAcpceU;
      string FriZnTrTFG;
      string OsCJfrwVXr;
      string eDtOgzfFhJ;
      string IzmddfZdcD;
      string ODPZJlyVeI;
      string fUEmoByTro;
      string nmkuyPGYfA;
      string RSrUcbmTFu;
      string AKaZdntznb;
      if(RgborMnmHj == eBeKAcpceU){gFlnPbRUbt = true;}
      else if(eBeKAcpceU == RgborMnmHj){nhjEklefWT = true;}
      if(sJWGugptxP == FriZnTrTFG){fYoepMcjKN = true;}
      else if(FriZnTrTFG == sJWGugptxP){PnHlbycDRO = true;}
      if(amNEDDhejP == OsCJfrwVXr){NeOxndMLQK = true;}
      else if(OsCJfrwVXr == amNEDDhejP){HbxtKnSLWy = true;}
      if(dBxUNqfpGC == eDtOgzfFhJ){UGkDSLgEFB = true;}
      else if(eDtOgzfFhJ == dBxUNqfpGC){eKQqXagYPM = true;}
      if(QYNmQqCXOB == IzmddfZdcD){KSrLPbUuiQ = true;}
      else if(IzmddfZdcD == QYNmQqCXOB){ejnUAfjSqn = true;}
      if(cdYeWeSWlo == ODPZJlyVeI){KKoZOCqnzk = true;}
      else if(ODPZJlyVeI == cdYeWeSWlo){bMIXhLkotw = true;}
      if(eJCrGrLBrE == fUEmoByTro){OFDRYYmlLe = true;}
      else if(fUEmoByTro == eJCrGrLBrE){STJYoEWQNB = true;}
      if(BAmuzBZanM == nmkuyPGYfA){fYeIDtlDgM = true;}
      if(AKQilzcSyi == RSrUcbmTFu){IQcAzKQKoQ = true;}
      if(XIDRWHWVgY == AKaZdntznb){UrFTlEPalp = true;}
      while(nmkuyPGYfA == BAmuzBZanM){RDnEjXnbtd = true;}
      while(RSrUcbmTFu == RSrUcbmTFu){DATiWSCsIM = true;}
      while(AKaZdntznb == AKaZdntznb){oreStKZOfw = true;}
      if(gFlnPbRUbt == true){gFlnPbRUbt = false;}
      if(fYoepMcjKN == true){fYoepMcjKN = false;}
      if(NeOxndMLQK == true){NeOxndMLQK = false;}
      if(UGkDSLgEFB == true){UGkDSLgEFB = false;}
      if(KSrLPbUuiQ == true){KSrLPbUuiQ = false;}
      if(KKoZOCqnzk == true){KKoZOCqnzk = false;}
      if(OFDRYYmlLe == true){OFDRYYmlLe = false;}
      if(fYeIDtlDgM == true){fYeIDtlDgM = false;}
      if(IQcAzKQKoQ == true){IQcAzKQKoQ = false;}
      if(UrFTlEPalp == true){UrFTlEPalp = false;}
      if(nhjEklefWT == true){nhjEklefWT = false;}
      if(PnHlbycDRO == true){PnHlbycDRO = false;}
      if(HbxtKnSLWy == true){HbxtKnSLWy = false;}
      if(eKQqXagYPM == true){eKQqXagYPM = false;}
      if(ejnUAfjSqn == true){ejnUAfjSqn = false;}
      if(bMIXhLkotw == true){bMIXhLkotw = false;}
      if(STJYoEWQNB == true){STJYoEWQNB = false;}
      if(RDnEjXnbtd == true){RDnEjXnbtd = false;}
      if(DATiWSCsIM == true){DATiWSCsIM = false;}
      if(oreStKZOfw == true){oreStKZOfw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CZRUSTKHVO
{ 
  void GeAmJcfYrU()
  { 
      bool GrDWmarIIu = false;
      bool XbBdpplAnA = false;
      bool swrWOZUteb = false;
      bool yZOKdVaAnU = false;
      bool WZbKlNTgxS = false;
      bool JuCJDJAgHN = false;
      bool GydgxxNpAT = false;
      bool PkLScTUgkB = false;
      bool FmwLSCXEGU = false;
      bool VtsaOXwuMn = false;
      bool zcfdDYijfj = false;
      bool oSwFHSCRNu = false;
      bool ZIjfxVqkDE = false;
      bool WYUwBcGRIt = false;
      bool TnYVeDxmTw = false;
      bool VdhRNqsAgg = false;
      bool gyfaMQyzDd = false;
      bool LjJTaljNAs = false;
      bool XDRHirqChK = false;
      bool jGkaMVHxIO = false;
      string zyYaDIipLb;
      string gYNwabHXNz;
      string auXcPTRNKd;
      string mJTgjNhbEx;
      string hhyxckeAAF;
      string PaBEzEZuKi;
      string pUfhnXFfLM;
      string sfTQQrwaAe;
      string oRNEOLHOgf;
      string nmQUGNBQIE;
      string fznmLjHknG;
      string HzuftYGaTb;
      string PqyfYGOyJD;
      string pfRuzodZse;
      string EWZZYnqjah;
      string GaxgooAIOE;
      string UJbjPbhzgE;
      string ufhoXsQXHj;
      string OdWawPhkGK;
      string oULnJuupJx;
      if(zyYaDIipLb == fznmLjHknG){GrDWmarIIu = true;}
      else if(fznmLjHknG == zyYaDIipLb){zcfdDYijfj = true;}
      if(gYNwabHXNz == HzuftYGaTb){XbBdpplAnA = true;}
      else if(HzuftYGaTb == gYNwabHXNz){oSwFHSCRNu = true;}
      if(auXcPTRNKd == PqyfYGOyJD){swrWOZUteb = true;}
      else if(PqyfYGOyJD == auXcPTRNKd){ZIjfxVqkDE = true;}
      if(mJTgjNhbEx == pfRuzodZse){yZOKdVaAnU = true;}
      else if(pfRuzodZse == mJTgjNhbEx){WYUwBcGRIt = true;}
      if(hhyxckeAAF == EWZZYnqjah){WZbKlNTgxS = true;}
      else if(EWZZYnqjah == hhyxckeAAF){TnYVeDxmTw = true;}
      if(PaBEzEZuKi == GaxgooAIOE){JuCJDJAgHN = true;}
      else if(GaxgooAIOE == PaBEzEZuKi){VdhRNqsAgg = true;}
      if(pUfhnXFfLM == UJbjPbhzgE){GydgxxNpAT = true;}
      else if(UJbjPbhzgE == pUfhnXFfLM){gyfaMQyzDd = true;}
      if(sfTQQrwaAe == ufhoXsQXHj){PkLScTUgkB = true;}
      if(oRNEOLHOgf == OdWawPhkGK){FmwLSCXEGU = true;}
      if(nmQUGNBQIE == oULnJuupJx){VtsaOXwuMn = true;}
      while(ufhoXsQXHj == sfTQQrwaAe){LjJTaljNAs = true;}
      while(OdWawPhkGK == OdWawPhkGK){XDRHirqChK = true;}
      while(oULnJuupJx == oULnJuupJx){jGkaMVHxIO = true;}
      if(GrDWmarIIu == true){GrDWmarIIu = false;}
      if(XbBdpplAnA == true){XbBdpplAnA = false;}
      if(swrWOZUteb == true){swrWOZUteb = false;}
      if(yZOKdVaAnU == true){yZOKdVaAnU = false;}
      if(WZbKlNTgxS == true){WZbKlNTgxS = false;}
      if(JuCJDJAgHN == true){JuCJDJAgHN = false;}
      if(GydgxxNpAT == true){GydgxxNpAT = false;}
      if(PkLScTUgkB == true){PkLScTUgkB = false;}
      if(FmwLSCXEGU == true){FmwLSCXEGU = false;}
      if(VtsaOXwuMn == true){VtsaOXwuMn = false;}
      if(zcfdDYijfj == true){zcfdDYijfj = false;}
      if(oSwFHSCRNu == true){oSwFHSCRNu = false;}
      if(ZIjfxVqkDE == true){ZIjfxVqkDE = false;}
      if(WYUwBcGRIt == true){WYUwBcGRIt = false;}
      if(TnYVeDxmTw == true){TnYVeDxmTw = false;}
      if(VdhRNqsAgg == true){VdhRNqsAgg = false;}
      if(gyfaMQyzDd == true){gyfaMQyzDd = false;}
      if(LjJTaljNAs == true){LjJTaljNAs = false;}
      if(XDRHirqChK == true){XDRHirqChK = false;}
      if(jGkaMVHxIO == true){jGkaMVHxIO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FWWXZMXBMR
{ 
  void qiogYKHyRw()
  { 
      bool slBypDNoBU = false;
      bool celtFldKdw = false;
      bool BgqlnLwmmr = false;
      bool hHZVEtWrYg = false;
      bool ZgWCDkWlZb = false;
      bool bZGsGMuPJe = false;
      bool GaCImUFPoL = false;
      bool OlkwVTJohD = false;
      bool nKNKPIAfPr = false;
      bool yHhsazeNOh = false;
      bool fGwNMpnJXl = false;
      bool CGgGpuMqre = false;
      bool UYAxMHDrVV = false;
      bool owZAWhOzxZ = false;
      bool TpIcorZbDf = false;
      bool lnUjNHGyBF = false;
      bool mwnBxGfgiI = false;
      bool fNsSKdPWIU = false;
      bool gbnojAaplP = false;
      bool bQxrmXBGfi = false;
      string HQYjXFzhFd;
      string dfkNkiCAkx;
      string QqmZAHIhNG;
      string QrIPiIZWkD;
      string yiOmAkHGSc;
      string gbhclPdziQ;
      string wQTzNkWUeb;
      string IeOhyhczZP;
      string zBPkZnJedT;
      string damUGhOPZO;
      string NmbpTBNAeD;
      string leZTRtBiYY;
      string arqLxhqsaQ;
      string TNYKBMZYQX;
      string ZJzZgzBTDL;
      string fepAmUuQrl;
      string JTZOjYFORF;
      string UcRByRrQdy;
      string fXpPjnWYXf;
      string QJfeNGjkpI;
      if(HQYjXFzhFd == NmbpTBNAeD){slBypDNoBU = true;}
      else if(NmbpTBNAeD == HQYjXFzhFd){fGwNMpnJXl = true;}
      if(dfkNkiCAkx == leZTRtBiYY){celtFldKdw = true;}
      else if(leZTRtBiYY == dfkNkiCAkx){CGgGpuMqre = true;}
      if(QqmZAHIhNG == arqLxhqsaQ){BgqlnLwmmr = true;}
      else if(arqLxhqsaQ == QqmZAHIhNG){UYAxMHDrVV = true;}
      if(QrIPiIZWkD == TNYKBMZYQX){hHZVEtWrYg = true;}
      else if(TNYKBMZYQX == QrIPiIZWkD){owZAWhOzxZ = true;}
      if(yiOmAkHGSc == ZJzZgzBTDL){ZgWCDkWlZb = true;}
      else if(ZJzZgzBTDL == yiOmAkHGSc){TpIcorZbDf = true;}
      if(gbhclPdziQ == fepAmUuQrl){bZGsGMuPJe = true;}
      else if(fepAmUuQrl == gbhclPdziQ){lnUjNHGyBF = true;}
      if(wQTzNkWUeb == JTZOjYFORF){GaCImUFPoL = true;}
      else if(JTZOjYFORF == wQTzNkWUeb){mwnBxGfgiI = true;}
      if(IeOhyhczZP == UcRByRrQdy){OlkwVTJohD = true;}
      if(zBPkZnJedT == fXpPjnWYXf){nKNKPIAfPr = true;}
      if(damUGhOPZO == QJfeNGjkpI){yHhsazeNOh = true;}
      while(UcRByRrQdy == IeOhyhczZP){fNsSKdPWIU = true;}
      while(fXpPjnWYXf == fXpPjnWYXf){gbnojAaplP = true;}
      while(QJfeNGjkpI == QJfeNGjkpI){bQxrmXBGfi = true;}
      if(slBypDNoBU == true){slBypDNoBU = false;}
      if(celtFldKdw == true){celtFldKdw = false;}
      if(BgqlnLwmmr == true){BgqlnLwmmr = false;}
      if(hHZVEtWrYg == true){hHZVEtWrYg = false;}
      if(ZgWCDkWlZb == true){ZgWCDkWlZb = false;}
      if(bZGsGMuPJe == true){bZGsGMuPJe = false;}
      if(GaCImUFPoL == true){GaCImUFPoL = false;}
      if(OlkwVTJohD == true){OlkwVTJohD = false;}
      if(nKNKPIAfPr == true){nKNKPIAfPr = false;}
      if(yHhsazeNOh == true){yHhsazeNOh = false;}
      if(fGwNMpnJXl == true){fGwNMpnJXl = false;}
      if(CGgGpuMqre == true){CGgGpuMqre = false;}
      if(UYAxMHDrVV == true){UYAxMHDrVV = false;}
      if(owZAWhOzxZ == true){owZAWhOzxZ = false;}
      if(TpIcorZbDf == true){TpIcorZbDf = false;}
      if(lnUjNHGyBF == true){lnUjNHGyBF = false;}
      if(mwnBxGfgiI == true){mwnBxGfgiI = false;}
      if(fNsSKdPWIU == true){fNsSKdPWIU = false;}
      if(gbnojAaplP == true){gbnojAaplP = false;}
      if(bQxrmXBGfi == true){bQxrmXBGfi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QHFBVVMYJB
{ 
  void QAbomkWdfJ()
  { 
      bool sdEjNHHHGl = false;
      bool uLCjfYhsbz = false;
      bool YmIlNKtlKM = false;
      bool oWJwotlonA = false;
      bool nngrancNhz = false;
      bool IBXbVGVRWD = false;
      bool MVwswYBFtl = false;
      bool msEaLjFPKY = false;
      bool ggELEmyhZi = false;
      bool YTSjmSrmwC = false;
      bool lWSwLPxwPl = false;
      bool BFGxVfRjoJ = false;
      bool aTeLMSZTmr = false;
      bool rRTIlJNHAn = false;
      bool pBRngSNVOH = false;
      bool BIylbSqGis = false;
      bool pcIWsjlyKL = false;
      bool RJiBSYBqet = false;
      bool FEFeqjTggT = false;
      bool RGXHyNrtux = false;
      string wJxSIoSeRe;
      string jLtynkfElf;
      string qqRLKtzQzm;
      string tShKYmqRXK;
      string NIqBNApZZm;
      string gNbIjEqlHO;
      string pCfdkQdjZB;
      string tNgaShzPxK;
      string DZqLGgqYZT;
      string wEKIUKcNPw;
      string VGzYsSfBpC;
      string FanxKQKTWE;
      string ZEJFEoDXGH;
      string FlzBnxZRSn;
      string AoiXOUQMyE;
      string zIpLVRxtTE;
      string PItiwTamIN;
      string prAiEjVkqi;
      string XpZBHwuneW;
      string AfyOXquzbt;
      if(wJxSIoSeRe == VGzYsSfBpC){sdEjNHHHGl = true;}
      else if(VGzYsSfBpC == wJxSIoSeRe){lWSwLPxwPl = true;}
      if(jLtynkfElf == FanxKQKTWE){uLCjfYhsbz = true;}
      else if(FanxKQKTWE == jLtynkfElf){BFGxVfRjoJ = true;}
      if(qqRLKtzQzm == ZEJFEoDXGH){YmIlNKtlKM = true;}
      else if(ZEJFEoDXGH == qqRLKtzQzm){aTeLMSZTmr = true;}
      if(tShKYmqRXK == FlzBnxZRSn){oWJwotlonA = true;}
      else if(FlzBnxZRSn == tShKYmqRXK){rRTIlJNHAn = true;}
      if(NIqBNApZZm == AoiXOUQMyE){nngrancNhz = true;}
      else if(AoiXOUQMyE == NIqBNApZZm){pBRngSNVOH = true;}
      if(gNbIjEqlHO == zIpLVRxtTE){IBXbVGVRWD = true;}
      else if(zIpLVRxtTE == gNbIjEqlHO){BIylbSqGis = true;}
      if(pCfdkQdjZB == PItiwTamIN){MVwswYBFtl = true;}
      else if(PItiwTamIN == pCfdkQdjZB){pcIWsjlyKL = true;}
      if(tNgaShzPxK == prAiEjVkqi){msEaLjFPKY = true;}
      if(DZqLGgqYZT == XpZBHwuneW){ggELEmyhZi = true;}
      if(wEKIUKcNPw == AfyOXquzbt){YTSjmSrmwC = true;}
      while(prAiEjVkqi == tNgaShzPxK){RJiBSYBqet = true;}
      while(XpZBHwuneW == XpZBHwuneW){FEFeqjTggT = true;}
      while(AfyOXquzbt == AfyOXquzbt){RGXHyNrtux = true;}
      if(sdEjNHHHGl == true){sdEjNHHHGl = false;}
      if(uLCjfYhsbz == true){uLCjfYhsbz = false;}
      if(YmIlNKtlKM == true){YmIlNKtlKM = false;}
      if(oWJwotlonA == true){oWJwotlonA = false;}
      if(nngrancNhz == true){nngrancNhz = false;}
      if(IBXbVGVRWD == true){IBXbVGVRWD = false;}
      if(MVwswYBFtl == true){MVwswYBFtl = false;}
      if(msEaLjFPKY == true){msEaLjFPKY = false;}
      if(ggELEmyhZi == true){ggELEmyhZi = false;}
      if(YTSjmSrmwC == true){YTSjmSrmwC = false;}
      if(lWSwLPxwPl == true){lWSwLPxwPl = false;}
      if(BFGxVfRjoJ == true){BFGxVfRjoJ = false;}
      if(aTeLMSZTmr == true){aTeLMSZTmr = false;}
      if(rRTIlJNHAn == true){rRTIlJNHAn = false;}
      if(pBRngSNVOH == true){pBRngSNVOH = false;}
      if(BIylbSqGis == true){BIylbSqGis = false;}
      if(pcIWsjlyKL == true){pcIWsjlyKL = false;}
      if(RJiBSYBqet == true){RJiBSYBqet = false;}
      if(FEFeqjTggT == true){FEFeqjTggT = false;}
      if(RGXHyNrtux == true){RGXHyNrtux = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FKTLNNYHMB
{ 
  void xTVFGDIEmg()
  { 
      bool lLRTeRETcU = false;
      bool fWMHAMILhx = false;
      bool dibIUZlPmZ = false;
      bool yjXqHQeDgz = false;
      bool EOVAATjyXr = false;
      bool GilVKCjJzF = false;
      bool engCWuzVAj = false;
      bool hFehsONaHA = false;
      bool pnruSOxBfE = false;
      bool gVEaUPhSdE = false;
      bool UOynKBEDbw = false;
      bool oIByPqwkjH = false;
      bool yyouDLBDNd = false;
      bool ftwCfapDkR = false;
      bool KtYjOXTFLc = false;
      bool SwhWGWYCjy = false;
      bool zAoyPtLySn = false;
      bool BrASxDYEge = false;
      bool rurkKiLZuJ = false;
      bool CmSlRJEZTT = false;
      string mHCDPQpXza;
      string pfRYVScyYQ;
      string ZQnHONkTOO;
      string LWJUfmmGyu;
      string fqCSuibTxw;
      string kgQMoVTuoC;
      string eVIjPTWxrh;
      string eWzdkiNUMe;
      string kRWScdGwfJ;
      string TrRwPJhSDb;
      string MeaPQOhlbG;
      string IzhJQNzpGk;
      string NZQhNmFCOb;
      string AuQjSFpHCO;
      string uTUZBUJIeC;
      string JrLSOlOsBd;
      string JfXzFMhxpL;
      string WrnrosFqfs;
      string cxWLRIiyVg;
      string qxFXEPuUTo;
      if(mHCDPQpXza == MeaPQOhlbG){lLRTeRETcU = true;}
      else if(MeaPQOhlbG == mHCDPQpXza){UOynKBEDbw = true;}
      if(pfRYVScyYQ == IzhJQNzpGk){fWMHAMILhx = true;}
      else if(IzhJQNzpGk == pfRYVScyYQ){oIByPqwkjH = true;}
      if(ZQnHONkTOO == NZQhNmFCOb){dibIUZlPmZ = true;}
      else if(NZQhNmFCOb == ZQnHONkTOO){yyouDLBDNd = true;}
      if(LWJUfmmGyu == AuQjSFpHCO){yjXqHQeDgz = true;}
      else if(AuQjSFpHCO == LWJUfmmGyu){ftwCfapDkR = true;}
      if(fqCSuibTxw == uTUZBUJIeC){EOVAATjyXr = true;}
      else if(uTUZBUJIeC == fqCSuibTxw){KtYjOXTFLc = true;}
      if(kgQMoVTuoC == JrLSOlOsBd){GilVKCjJzF = true;}
      else if(JrLSOlOsBd == kgQMoVTuoC){SwhWGWYCjy = true;}
      if(eVIjPTWxrh == JfXzFMhxpL){engCWuzVAj = true;}
      else if(JfXzFMhxpL == eVIjPTWxrh){zAoyPtLySn = true;}
      if(eWzdkiNUMe == WrnrosFqfs){hFehsONaHA = true;}
      if(kRWScdGwfJ == cxWLRIiyVg){pnruSOxBfE = true;}
      if(TrRwPJhSDb == qxFXEPuUTo){gVEaUPhSdE = true;}
      while(WrnrosFqfs == eWzdkiNUMe){BrASxDYEge = true;}
      while(cxWLRIiyVg == cxWLRIiyVg){rurkKiLZuJ = true;}
      while(qxFXEPuUTo == qxFXEPuUTo){CmSlRJEZTT = true;}
      if(lLRTeRETcU == true){lLRTeRETcU = false;}
      if(fWMHAMILhx == true){fWMHAMILhx = false;}
      if(dibIUZlPmZ == true){dibIUZlPmZ = false;}
      if(yjXqHQeDgz == true){yjXqHQeDgz = false;}
      if(EOVAATjyXr == true){EOVAATjyXr = false;}
      if(GilVKCjJzF == true){GilVKCjJzF = false;}
      if(engCWuzVAj == true){engCWuzVAj = false;}
      if(hFehsONaHA == true){hFehsONaHA = false;}
      if(pnruSOxBfE == true){pnruSOxBfE = false;}
      if(gVEaUPhSdE == true){gVEaUPhSdE = false;}
      if(UOynKBEDbw == true){UOynKBEDbw = false;}
      if(oIByPqwkjH == true){oIByPqwkjH = false;}
      if(yyouDLBDNd == true){yyouDLBDNd = false;}
      if(ftwCfapDkR == true){ftwCfapDkR = false;}
      if(KtYjOXTFLc == true){KtYjOXTFLc = false;}
      if(SwhWGWYCjy == true){SwhWGWYCjy = false;}
      if(zAoyPtLySn == true){zAoyPtLySn = false;}
      if(BrASxDYEge == true){BrASxDYEge = false;}
      if(rurkKiLZuJ == true){rurkKiLZuJ = false;}
      if(CmSlRJEZTT == true){CmSlRJEZTT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BHVXAGBRBV
{ 
  void hrKmxdYyCp()
  { 
      bool IdPaYngNTP = false;
      bool MaWtbiiBbe = false;
      bool WDiDIsNZHA = false;
      bool mzRrPutKAF = false;
      bool abTWDaTkMe = false;
      bool BZXFpEtMRe = false;
      bool aHFScNJdef = false;
      bool nXBWEujMzh = false;
      bool ZbNczMaLCL = false;
      bool AgsUeSVAtp = false;
      bool RoGfpcYBAu = false;
      bool ThNiFytcTP = false;
      bool lxbTeGegqk = false;
      bool YjRIPjUglV = false;
      bool nYKGqSTKOf = false;
      bool YsgdDTNmAj = false;
      bool yqJOVjPESU = false;
      bool dMpxbNlUcM = false;
      bool lURLMfCmFu = false;
      bool WgfCXwOwkG = false;
      string sAFpGJWgki;
      string BJzXNRKDpM;
      string VWbxjecmLK;
      string rUTIgHzkDt;
      string KTlmeYuAxt;
      string NsGzsVXHGa;
      string fiUZpfppqG;
      string SYAwCCkoRK;
      string jcpRwyNTPK;
      string iqecNayMwy;
      string iEIpborKxq;
      string kipuqDsDcq;
      string SWafXatXia;
      string DXrSbeTzoH;
      string GDWYZzBilJ;
      string huiFfLccSB;
      string tUaVmMqWSL;
      string jsNVkPzCGX;
      string ZKkYsHommP;
      string CpfnNkbAkN;
      if(sAFpGJWgki == iEIpborKxq){IdPaYngNTP = true;}
      else if(iEIpborKxq == sAFpGJWgki){RoGfpcYBAu = true;}
      if(BJzXNRKDpM == kipuqDsDcq){MaWtbiiBbe = true;}
      else if(kipuqDsDcq == BJzXNRKDpM){ThNiFytcTP = true;}
      if(VWbxjecmLK == SWafXatXia){WDiDIsNZHA = true;}
      else if(SWafXatXia == VWbxjecmLK){lxbTeGegqk = true;}
      if(rUTIgHzkDt == DXrSbeTzoH){mzRrPutKAF = true;}
      else if(DXrSbeTzoH == rUTIgHzkDt){YjRIPjUglV = true;}
      if(KTlmeYuAxt == GDWYZzBilJ){abTWDaTkMe = true;}
      else if(GDWYZzBilJ == KTlmeYuAxt){nYKGqSTKOf = true;}
      if(NsGzsVXHGa == huiFfLccSB){BZXFpEtMRe = true;}
      else if(huiFfLccSB == NsGzsVXHGa){YsgdDTNmAj = true;}
      if(fiUZpfppqG == tUaVmMqWSL){aHFScNJdef = true;}
      else if(tUaVmMqWSL == fiUZpfppqG){yqJOVjPESU = true;}
      if(SYAwCCkoRK == jsNVkPzCGX){nXBWEujMzh = true;}
      if(jcpRwyNTPK == ZKkYsHommP){ZbNczMaLCL = true;}
      if(iqecNayMwy == CpfnNkbAkN){AgsUeSVAtp = true;}
      while(jsNVkPzCGX == SYAwCCkoRK){dMpxbNlUcM = true;}
      while(ZKkYsHommP == ZKkYsHommP){lURLMfCmFu = true;}
      while(CpfnNkbAkN == CpfnNkbAkN){WgfCXwOwkG = true;}
      if(IdPaYngNTP == true){IdPaYngNTP = false;}
      if(MaWtbiiBbe == true){MaWtbiiBbe = false;}
      if(WDiDIsNZHA == true){WDiDIsNZHA = false;}
      if(mzRrPutKAF == true){mzRrPutKAF = false;}
      if(abTWDaTkMe == true){abTWDaTkMe = false;}
      if(BZXFpEtMRe == true){BZXFpEtMRe = false;}
      if(aHFScNJdef == true){aHFScNJdef = false;}
      if(nXBWEujMzh == true){nXBWEujMzh = false;}
      if(ZbNczMaLCL == true){ZbNczMaLCL = false;}
      if(AgsUeSVAtp == true){AgsUeSVAtp = false;}
      if(RoGfpcYBAu == true){RoGfpcYBAu = false;}
      if(ThNiFytcTP == true){ThNiFytcTP = false;}
      if(lxbTeGegqk == true){lxbTeGegqk = false;}
      if(YjRIPjUglV == true){YjRIPjUglV = false;}
      if(nYKGqSTKOf == true){nYKGqSTKOf = false;}
      if(YsgdDTNmAj == true){YsgdDTNmAj = false;}
      if(yqJOVjPESU == true){yqJOVjPESU = false;}
      if(dMpxbNlUcM == true){dMpxbNlUcM = false;}
      if(lURLMfCmFu == true){lURLMfCmFu = false;}
      if(WgfCXwOwkG == true){WgfCXwOwkG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CQSKJXWTUO
{ 
  void WgalDRbYYh()
  { 
      bool EnDcGmWEOf = false;
      bool rwYIlMNeGT = false;
      bool YJZmhpDJwX = false;
      bool wTSsKbgpBr = false;
      bool PdIWjzwVrI = false;
      bool JZoZZuOPtP = false;
      bool iNHqiXdexK = false;
      bool eXcNEuBCCi = false;
      bool shRnNWesSO = false;
      bool MQukICVQmL = false;
      bool URXgclwaVe = false;
      bool tLNLVAuTcM = false;
      bool skMiyObqEB = false;
      bool YjPpNbKjKb = false;
      bool aDWnUADiPI = false;
      bool GBnZSjFoiO = false;
      bool KEVTFJwWyt = false;
      bool pLIAlpNYNx = false;
      bool KrbwuWwoXc = false;
      bool WVAwRWgDhK = false;
      string APDHbtJABu;
      string HeLPBLkQLU;
      string DZMgPQqzMu;
      string iJMrtBAMBT;
      string PVNVWYomXu;
      string aWErmZDWrK;
      string DKnFLxSSUz;
      string LYPqFgMpJq;
      string bEaRULEUFU;
      string ydUpQEhHJZ;
      string FVRYjBHNlF;
      string MMMBiyiVkA;
      string rxMABgEZZA;
      string yFgjkFlBgS;
      string EqhAHkQTGS;
      string ULWJgIJQXC;
      string xgmlGHfcPd;
      string LhoRuBPMrP;
      string PkSHemhWCc;
      string wUdeUXEusz;
      if(APDHbtJABu == FVRYjBHNlF){EnDcGmWEOf = true;}
      else if(FVRYjBHNlF == APDHbtJABu){URXgclwaVe = true;}
      if(HeLPBLkQLU == MMMBiyiVkA){rwYIlMNeGT = true;}
      else if(MMMBiyiVkA == HeLPBLkQLU){tLNLVAuTcM = true;}
      if(DZMgPQqzMu == rxMABgEZZA){YJZmhpDJwX = true;}
      else if(rxMABgEZZA == DZMgPQqzMu){skMiyObqEB = true;}
      if(iJMrtBAMBT == yFgjkFlBgS){wTSsKbgpBr = true;}
      else if(yFgjkFlBgS == iJMrtBAMBT){YjPpNbKjKb = true;}
      if(PVNVWYomXu == EqhAHkQTGS){PdIWjzwVrI = true;}
      else if(EqhAHkQTGS == PVNVWYomXu){aDWnUADiPI = true;}
      if(aWErmZDWrK == ULWJgIJQXC){JZoZZuOPtP = true;}
      else if(ULWJgIJQXC == aWErmZDWrK){GBnZSjFoiO = true;}
      if(DKnFLxSSUz == xgmlGHfcPd){iNHqiXdexK = true;}
      else if(xgmlGHfcPd == DKnFLxSSUz){KEVTFJwWyt = true;}
      if(LYPqFgMpJq == LhoRuBPMrP){eXcNEuBCCi = true;}
      if(bEaRULEUFU == PkSHemhWCc){shRnNWesSO = true;}
      if(ydUpQEhHJZ == wUdeUXEusz){MQukICVQmL = true;}
      while(LhoRuBPMrP == LYPqFgMpJq){pLIAlpNYNx = true;}
      while(PkSHemhWCc == PkSHemhWCc){KrbwuWwoXc = true;}
      while(wUdeUXEusz == wUdeUXEusz){WVAwRWgDhK = true;}
      if(EnDcGmWEOf == true){EnDcGmWEOf = false;}
      if(rwYIlMNeGT == true){rwYIlMNeGT = false;}
      if(YJZmhpDJwX == true){YJZmhpDJwX = false;}
      if(wTSsKbgpBr == true){wTSsKbgpBr = false;}
      if(PdIWjzwVrI == true){PdIWjzwVrI = false;}
      if(JZoZZuOPtP == true){JZoZZuOPtP = false;}
      if(iNHqiXdexK == true){iNHqiXdexK = false;}
      if(eXcNEuBCCi == true){eXcNEuBCCi = false;}
      if(shRnNWesSO == true){shRnNWesSO = false;}
      if(MQukICVQmL == true){MQukICVQmL = false;}
      if(URXgclwaVe == true){URXgclwaVe = false;}
      if(tLNLVAuTcM == true){tLNLVAuTcM = false;}
      if(skMiyObqEB == true){skMiyObqEB = false;}
      if(YjPpNbKjKb == true){YjPpNbKjKb = false;}
      if(aDWnUADiPI == true){aDWnUADiPI = false;}
      if(GBnZSjFoiO == true){GBnZSjFoiO = false;}
      if(KEVTFJwWyt == true){KEVTFJwWyt = false;}
      if(pLIAlpNYNx == true){pLIAlpNYNx = false;}
      if(KrbwuWwoXc == true){KrbwuWwoXc = false;}
      if(WVAwRWgDhK == true){WVAwRWgDhK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QTELBKGTID
{ 
  void gNukAukxJq()
  { 
      bool tPRDMbAHro = false;
      bool rUrNdlnkkC = false;
      bool xtLGMfSCSf = false;
      bool safUEVIrYz = false;
      bool UQJNSVGVSR = false;
      bool gAszqAELqg = false;
      bool IxnLwRnXII = false;
      bool dwMkgfjxmq = false;
      bool ZxiAzsggdE = false;
      bool QxArpXcxRB = false;
      bool ghNKnknHSK = false;
      bool PHXAGLNnMC = false;
      bool jHtDqfuTtJ = false;
      bool DlelJqiYLO = false;
      bool FZNToJYAke = false;
      bool JnkOQZnJSH = false;
      bool pTMIGcblqO = false;
      bool bnbyxKsZOh = false;
      bool HtiPzOBPUi = false;
      bool DYGEYkMEML = false;
      string JmRkuzgTOh;
      string PPZgEcSKcJ;
      string FQwtEtxhLk;
      string jOJxcbrtEa;
      string aVuzKAnZgR;
      string wrDAdspXgB;
      string CzHcyAFbDb;
      string kYFBhjUxiE;
      string FWAtorLJTi;
      string kTNCXbNSAK;
      string tLVEgXlBRs;
      string YsncwfyNnG;
      string owITqQKCdF;
      string VCwYJsAwNQ;
      string FJqZKqekGr;
      string dAdtUyDCMP;
      string MjXMXVwPSC;
      string eCAWBeFiJz;
      string kZwlbVXCDL;
      string pyixEUldCn;
      if(JmRkuzgTOh == tLVEgXlBRs){tPRDMbAHro = true;}
      else if(tLVEgXlBRs == JmRkuzgTOh){ghNKnknHSK = true;}
      if(PPZgEcSKcJ == YsncwfyNnG){rUrNdlnkkC = true;}
      else if(YsncwfyNnG == PPZgEcSKcJ){PHXAGLNnMC = true;}
      if(FQwtEtxhLk == owITqQKCdF){xtLGMfSCSf = true;}
      else if(owITqQKCdF == FQwtEtxhLk){jHtDqfuTtJ = true;}
      if(jOJxcbrtEa == VCwYJsAwNQ){safUEVIrYz = true;}
      else if(VCwYJsAwNQ == jOJxcbrtEa){DlelJqiYLO = true;}
      if(aVuzKAnZgR == FJqZKqekGr){UQJNSVGVSR = true;}
      else if(FJqZKqekGr == aVuzKAnZgR){FZNToJYAke = true;}
      if(wrDAdspXgB == dAdtUyDCMP){gAszqAELqg = true;}
      else if(dAdtUyDCMP == wrDAdspXgB){JnkOQZnJSH = true;}
      if(CzHcyAFbDb == MjXMXVwPSC){IxnLwRnXII = true;}
      else if(MjXMXVwPSC == CzHcyAFbDb){pTMIGcblqO = true;}
      if(kYFBhjUxiE == eCAWBeFiJz){dwMkgfjxmq = true;}
      if(FWAtorLJTi == kZwlbVXCDL){ZxiAzsggdE = true;}
      if(kTNCXbNSAK == pyixEUldCn){QxArpXcxRB = true;}
      while(eCAWBeFiJz == kYFBhjUxiE){bnbyxKsZOh = true;}
      while(kZwlbVXCDL == kZwlbVXCDL){HtiPzOBPUi = true;}
      while(pyixEUldCn == pyixEUldCn){DYGEYkMEML = true;}
      if(tPRDMbAHro == true){tPRDMbAHro = false;}
      if(rUrNdlnkkC == true){rUrNdlnkkC = false;}
      if(xtLGMfSCSf == true){xtLGMfSCSf = false;}
      if(safUEVIrYz == true){safUEVIrYz = false;}
      if(UQJNSVGVSR == true){UQJNSVGVSR = false;}
      if(gAszqAELqg == true){gAszqAELqg = false;}
      if(IxnLwRnXII == true){IxnLwRnXII = false;}
      if(dwMkgfjxmq == true){dwMkgfjxmq = false;}
      if(ZxiAzsggdE == true){ZxiAzsggdE = false;}
      if(QxArpXcxRB == true){QxArpXcxRB = false;}
      if(ghNKnknHSK == true){ghNKnknHSK = false;}
      if(PHXAGLNnMC == true){PHXAGLNnMC = false;}
      if(jHtDqfuTtJ == true){jHtDqfuTtJ = false;}
      if(DlelJqiYLO == true){DlelJqiYLO = false;}
      if(FZNToJYAke == true){FZNToJYAke = false;}
      if(JnkOQZnJSH == true){JnkOQZnJSH = false;}
      if(pTMIGcblqO == true){pTMIGcblqO = false;}
      if(bnbyxKsZOh == true){bnbyxKsZOh = false;}
      if(HtiPzOBPUi == true){HtiPzOBPUi = false;}
      if(DYGEYkMEML == true){DYGEYkMEML = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KQJHNAGVPJ
{ 
  void JmnxkxqkFb()
  { 
      bool AVQWHhCTNs = false;
      bool WEbkdZLSmG = false;
      bool LUVQWEssRg = false;
      bool CaCiTHIRqP = false;
      bool npJLSqTqcJ = false;
      bool CWOMSfzzAC = false;
      bool oJCgqwCsQV = false;
      bool QtbWSULKye = false;
      bool kBPHdeLoQn = false;
      bool HJQnZenbTV = false;
      bool nZaGsIuqtx = false;
      bool UoBURmstDM = false;
      bool kMccNHcmxm = false;
      bool giqbqKaIOV = false;
      bool iTuSSSHuWm = false;
      bool lsYHjaxxsk = false;
      bool eItGPlxZdG = false;
      bool MjfgcRRJJu = false;
      bool AgQJBnJiqQ = false;
      bool McPcpaYnCg = false;
      string rtrLRmCfFk;
      string oRIEOAiLae;
      string qFXwKrJwTp;
      string gIbNnlKTDX;
      string RdUXSFITtX;
      string LmaBElWuBY;
      string cGLPEgpuPb;
      string oPICNMkzcE;
      string jpBwesgaIB;
      string OOSduKSFTl;
      string PNDShwdYmr;
      string BWRwomFPjK;
      string APlNMZwdHC;
      string tefqoWliOi;
      string OHmQArxWoI;
      string EDUIlzapFH;
      string zARkxVqaGS;
      string AWABurcVNU;
      string cZnyxqKWEo;
      string wwcHiOpCSd;
      if(rtrLRmCfFk == PNDShwdYmr){AVQWHhCTNs = true;}
      else if(PNDShwdYmr == rtrLRmCfFk){nZaGsIuqtx = true;}
      if(oRIEOAiLae == BWRwomFPjK){WEbkdZLSmG = true;}
      else if(BWRwomFPjK == oRIEOAiLae){UoBURmstDM = true;}
      if(qFXwKrJwTp == APlNMZwdHC){LUVQWEssRg = true;}
      else if(APlNMZwdHC == qFXwKrJwTp){kMccNHcmxm = true;}
      if(gIbNnlKTDX == tefqoWliOi){CaCiTHIRqP = true;}
      else if(tefqoWliOi == gIbNnlKTDX){giqbqKaIOV = true;}
      if(RdUXSFITtX == OHmQArxWoI){npJLSqTqcJ = true;}
      else if(OHmQArxWoI == RdUXSFITtX){iTuSSSHuWm = true;}
      if(LmaBElWuBY == EDUIlzapFH){CWOMSfzzAC = true;}
      else if(EDUIlzapFH == LmaBElWuBY){lsYHjaxxsk = true;}
      if(cGLPEgpuPb == zARkxVqaGS){oJCgqwCsQV = true;}
      else if(zARkxVqaGS == cGLPEgpuPb){eItGPlxZdG = true;}
      if(oPICNMkzcE == AWABurcVNU){QtbWSULKye = true;}
      if(jpBwesgaIB == cZnyxqKWEo){kBPHdeLoQn = true;}
      if(OOSduKSFTl == wwcHiOpCSd){HJQnZenbTV = true;}
      while(AWABurcVNU == oPICNMkzcE){MjfgcRRJJu = true;}
      while(cZnyxqKWEo == cZnyxqKWEo){AgQJBnJiqQ = true;}
      while(wwcHiOpCSd == wwcHiOpCSd){McPcpaYnCg = true;}
      if(AVQWHhCTNs == true){AVQWHhCTNs = false;}
      if(WEbkdZLSmG == true){WEbkdZLSmG = false;}
      if(LUVQWEssRg == true){LUVQWEssRg = false;}
      if(CaCiTHIRqP == true){CaCiTHIRqP = false;}
      if(npJLSqTqcJ == true){npJLSqTqcJ = false;}
      if(CWOMSfzzAC == true){CWOMSfzzAC = false;}
      if(oJCgqwCsQV == true){oJCgqwCsQV = false;}
      if(QtbWSULKye == true){QtbWSULKye = false;}
      if(kBPHdeLoQn == true){kBPHdeLoQn = false;}
      if(HJQnZenbTV == true){HJQnZenbTV = false;}
      if(nZaGsIuqtx == true){nZaGsIuqtx = false;}
      if(UoBURmstDM == true){UoBURmstDM = false;}
      if(kMccNHcmxm == true){kMccNHcmxm = false;}
      if(giqbqKaIOV == true){giqbqKaIOV = false;}
      if(iTuSSSHuWm == true){iTuSSSHuWm = false;}
      if(lsYHjaxxsk == true){lsYHjaxxsk = false;}
      if(eItGPlxZdG == true){eItGPlxZdG = false;}
      if(MjfgcRRJJu == true){MjfgcRRJJu = false;}
      if(AgQJBnJiqQ == true){AgQJBnJiqQ = false;}
      if(McPcpaYnCg == true){McPcpaYnCg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EIENDYUDJM
{ 
  void PPMPZGzffk()
  { 
      bool pyejCeSHAF = false;
      bool uWETYrMBeB = false;
      bool yVAOIGmSdu = false;
      bool OmPdCGmxFm = false;
      bool iBWztYIhpR = false;
      bool ZLNzZUyPaw = false;
      bool rzdFqHHaQS = false;
      bool FOwrRwzBUj = false;
      bool xEcMUDYPDh = false;
      bool IXWJtjXRHl = false;
      bool RhQWMKOVhc = false;
      bool UwtpymVQjn = false;
      bool hqWiJhrmxh = false;
      bool YhtiSOmFAJ = false;
      bool nDhaMLcfKG = false;
      bool NGgSDZLhNd = false;
      bool SbXAEmCLXi = false;
      bool APQZAeJwVy = false;
      bool ELbqTSAaer = false;
      bool DErVqLfgWZ = false;
      string oCRALJXhpW;
      string whZuoNsJnH;
      string OMFGQeRIZy;
      string MmguUeGnJA;
      string qjzFoAmMBs;
      string QQbDkbxKjf;
      string qOHqKJBeZK;
      string GFzmQeNzRP;
      string rFHggwKdJs;
      string gwDcIcbHue;
      string zIlqmLQnlF;
      string NxrUnlGaKN;
      string yXUgcJBWdn;
      string CGElQiSQsU;
      string fWqEeiEioV;
      string VAxhgamFNd;
      string KtJyDHsFEE;
      string TphogafQBs;
      string FRgISBJWFo;
      string uMCOKlMsAX;
      if(oCRALJXhpW == zIlqmLQnlF){pyejCeSHAF = true;}
      else if(zIlqmLQnlF == oCRALJXhpW){RhQWMKOVhc = true;}
      if(whZuoNsJnH == NxrUnlGaKN){uWETYrMBeB = true;}
      else if(NxrUnlGaKN == whZuoNsJnH){UwtpymVQjn = true;}
      if(OMFGQeRIZy == yXUgcJBWdn){yVAOIGmSdu = true;}
      else if(yXUgcJBWdn == OMFGQeRIZy){hqWiJhrmxh = true;}
      if(MmguUeGnJA == CGElQiSQsU){OmPdCGmxFm = true;}
      else if(CGElQiSQsU == MmguUeGnJA){YhtiSOmFAJ = true;}
      if(qjzFoAmMBs == fWqEeiEioV){iBWztYIhpR = true;}
      else if(fWqEeiEioV == qjzFoAmMBs){nDhaMLcfKG = true;}
      if(QQbDkbxKjf == VAxhgamFNd){ZLNzZUyPaw = true;}
      else if(VAxhgamFNd == QQbDkbxKjf){NGgSDZLhNd = true;}
      if(qOHqKJBeZK == KtJyDHsFEE){rzdFqHHaQS = true;}
      else if(KtJyDHsFEE == qOHqKJBeZK){SbXAEmCLXi = true;}
      if(GFzmQeNzRP == TphogafQBs){FOwrRwzBUj = true;}
      if(rFHggwKdJs == FRgISBJWFo){xEcMUDYPDh = true;}
      if(gwDcIcbHue == uMCOKlMsAX){IXWJtjXRHl = true;}
      while(TphogafQBs == GFzmQeNzRP){APQZAeJwVy = true;}
      while(FRgISBJWFo == FRgISBJWFo){ELbqTSAaer = true;}
      while(uMCOKlMsAX == uMCOKlMsAX){DErVqLfgWZ = true;}
      if(pyejCeSHAF == true){pyejCeSHAF = false;}
      if(uWETYrMBeB == true){uWETYrMBeB = false;}
      if(yVAOIGmSdu == true){yVAOIGmSdu = false;}
      if(OmPdCGmxFm == true){OmPdCGmxFm = false;}
      if(iBWztYIhpR == true){iBWztYIhpR = false;}
      if(ZLNzZUyPaw == true){ZLNzZUyPaw = false;}
      if(rzdFqHHaQS == true){rzdFqHHaQS = false;}
      if(FOwrRwzBUj == true){FOwrRwzBUj = false;}
      if(xEcMUDYPDh == true){xEcMUDYPDh = false;}
      if(IXWJtjXRHl == true){IXWJtjXRHl = false;}
      if(RhQWMKOVhc == true){RhQWMKOVhc = false;}
      if(UwtpymVQjn == true){UwtpymVQjn = false;}
      if(hqWiJhrmxh == true){hqWiJhrmxh = false;}
      if(YhtiSOmFAJ == true){YhtiSOmFAJ = false;}
      if(nDhaMLcfKG == true){nDhaMLcfKG = false;}
      if(NGgSDZLhNd == true){NGgSDZLhNd = false;}
      if(SbXAEmCLXi == true){SbXAEmCLXi = false;}
      if(APQZAeJwVy == true){APQZAeJwVy = false;}
      if(ELbqTSAaer == true){ELbqTSAaer = false;}
      if(DErVqLfgWZ == true){DErVqLfgWZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YXKXTWXEQK
{ 
  void VqlVqUPxcT()
  { 
      bool YqrFWRWOCA = false;
      bool PksVVyAGul = false;
      bool OtuRVDVLfE = false;
      bool cpPESbwCYA = false;
      bool yYtNzPFLZs = false;
      bool mTGELeuZjT = false;
      bool uLhxXYUoDt = false;
      bool BxhumoAhRF = false;
      bool xKkmQIjLrn = false;
      bool fVSEEmpwoa = false;
      bool tPHeqplKQW = false;
      bool dNIdVkZugP = false;
      bool oJxPNfecpA = false;
      bool yDrqKhDGua = false;
      bool WYtVJRMniT = false;
      bool MuPZkkSrRK = false;
      bool KITQXaVRTm = false;
      bool gTAFsQPaGu = false;
      bool TpsWmDnSFZ = false;
      bool PKojPNEdyi = false;
      string ZAxEwSKuxz;
      string SunILLEYqu;
      string ehrRRsqsHS;
      string RnZewFLOuY;
      string lJTROiEpbK;
      string oYnJaqHflD;
      string aQneheVILF;
      string AodRIUOZCi;
      string nBRwcrzPEE;
      string xebryUVnjj;
      string MweVKzuWAG;
      string cgcDOYzrBo;
      string fGEGHUNlTm;
      string yapSVrWukd;
      string xcOxbPBYcY;
      string VdmtEGqXNo;
      string lJCNHCqKgW;
      string CDGXrDqGdq;
      string TnIuRUnwOP;
      string AyguqnaBpZ;
      if(ZAxEwSKuxz == MweVKzuWAG){YqrFWRWOCA = true;}
      else if(MweVKzuWAG == ZAxEwSKuxz){tPHeqplKQW = true;}
      if(SunILLEYqu == cgcDOYzrBo){PksVVyAGul = true;}
      else if(cgcDOYzrBo == SunILLEYqu){dNIdVkZugP = true;}
      if(ehrRRsqsHS == fGEGHUNlTm){OtuRVDVLfE = true;}
      else if(fGEGHUNlTm == ehrRRsqsHS){oJxPNfecpA = true;}
      if(RnZewFLOuY == yapSVrWukd){cpPESbwCYA = true;}
      else if(yapSVrWukd == RnZewFLOuY){yDrqKhDGua = true;}
      if(lJTROiEpbK == xcOxbPBYcY){yYtNzPFLZs = true;}
      else if(xcOxbPBYcY == lJTROiEpbK){WYtVJRMniT = true;}
      if(oYnJaqHflD == VdmtEGqXNo){mTGELeuZjT = true;}
      else if(VdmtEGqXNo == oYnJaqHflD){MuPZkkSrRK = true;}
      if(aQneheVILF == lJCNHCqKgW){uLhxXYUoDt = true;}
      else if(lJCNHCqKgW == aQneheVILF){KITQXaVRTm = true;}
      if(AodRIUOZCi == CDGXrDqGdq){BxhumoAhRF = true;}
      if(nBRwcrzPEE == TnIuRUnwOP){xKkmQIjLrn = true;}
      if(xebryUVnjj == AyguqnaBpZ){fVSEEmpwoa = true;}
      while(CDGXrDqGdq == AodRIUOZCi){gTAFsQPaGu = true;}
      while(TnIuRUnwOP == TnIuRUnwOP){TpsWmDnSFZ = true;}
      while(AyguqnaBpZ == AyguqnaBpZ){PKojPNEdyi = true;}
      if(YqrFWRWOCA == true){YqrFWRWOCA = false;}
      if(PksVVyAGul == true){PksVVyAGul = false;}
      if(OtuRVDVLfE == true){OtuRVDVLfE = false;}
      if(cpPESbwCYA == true){cpPESbwCYA = false;}
      if(yYtNzPFLZs == true){yYtNzPFLZs = false;}
      if(mTGELeuZjT == true){mTGELeuZjT = false;}
      if(uLhxXYUoDt == true){uLhxXYUoDt = false;}
      if(BxhumoAhRF == true){BxhumoAhRF = false;}
      if(xKkmQIjLrn == true){xKkmQIjLrn = false;}
      if(fVSEEmpwoa == true){fVSEEmpwoa = false;}
      if(tPHeqplKQW == true){tPHeqplKQW = false;}
      if(dNIdVkZugP == true){dNIdVkZugP = false;}
      if(oJxPNfecpA == true){oJxPNfecpA = false;}
      if(yDrqKhDGua == true){yDrqKhDGua = false;}
      if(WYtVJRMniT == true){WYtVJRMniT = false;}
      if(MuPZkkSrRK == true){MuPZkkSrRK = false;}
      if(KITQXaVRTm == true){KITQXaVRTm = false;}
      if(gTAFsQPaGu == true){gTAFsQPaGu = false;}
      if(TpsWmDnSFZ == true){TpsWmDnSFZ = false;}
      if(PKojPNEdyi == true){PKojPNEdyi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUDACYFIXA
{ 
  void hswEEipUIm()
  { 
      bool YiEZYctltu = false;
      bool FKTSzWLEWH = false;
      bool TOfwZuyuFi = false;
      bool toytALruCX = false;
      bool ljnawTgLqt = false;
      bool opeEuJCHAd = false;
      bool eyfKBPLYSm = false;
      bool dQCzViaFzG = false;
      bool OmDLsDKszq = false;
      bool IjuXsmEcYf = false;
      bool HHrDPYnfhM = false;
      bool ixHsPquUQx = false;
      bool FRZbetVdGi = false;
      bool dxfTzGtAuU = false;
      bool OeKlHKcBIB = false;
      bool riMbaogQYV = false;
      bool DKYzhkRntI = false;
      bool xuYwhZGmTT = false;
      bool QTUEqukDrK = false;
      bool YdaZREFLDV = false;
      string cJuIHDsqcJ;
      string gPUfhpQzff;
      string sOnbwXGfKV;
      string cQuJoDOORq;
      string SgUdShqiTB;
      string UNPqLOUTMj;
      string xMfHgQTKpd;
      string bCgoMMsKJN;
      string fWMJBOADya;
      string huChsGBNxB;
      string NgsoZSfZdy;
      string VKJzDZAVFS;
      string PQLPwfzzuG;
      string KeMHzzdWji;
      string hZYAFWkDdT;
      string FeIdkxVdrs;
      string SgeXmpxCzD;
      string uckVjoqKJZ;
      string twUaAfWiVC;
      string dAdpQBuBMO;
      if(cJuIHDsqcJ == NgsoZSfZdy){YiEZYctltu = true;}
      else if(NgsoZSfZdy == cJuIHDsqcJ){HHrDPYnfhM = true;}
      if(gPUfhpQzff == VKJzDZAVFS){FKTSzWLEWH = true;}
      else if(VKJzDZAVFS == gPUfhpQzff){ixHsPquUQx = true;}
      if(sOnbwXGfKV == PQLPwfzzuG){TOfwZuyuFi = true;}
      else if(PQLPwfzzuG == sOnbwXGfKV){FRZbetVdGi = true;}
      if(cQuJoDOORq == KeMHzzdWji){toytALruCX = true;}
      else if(KeMHzzdWji == cQuJoDOORq){dxfTzGtAuU = true;}
      if(SgUdShqiTB == hZYAFWkDdT){ljnawTgLqt = true;}
      else if(hZYAFWkDdT == SgUdShqiTB){OeKlHKcBIB = true;}
      if(UNPqLOUTMj == FeIdkxVdrs){opeEuJCHAd = true;}
      else if(FeIdkxVdrs == UNPqLOUTMj){riMbaogQYV = true;}
      if(xMfHgQTKpd == SgeXmpxCzD){eyfKBPLYSm = true;}
      else if(SgeXmpxCzD == xMfHgQTKpd){DKYzhkRntI = true;}
      if(bCgoMMsKJN == uckVjoqKJZ){dQCzViaFzG = true;}
      if(fWMJBOADya == twUaAfWiVC){OmDLsDKszq = true;}
      if(huChsGBNxB == dAdpQBuBMO){IjuXsmEcYf = true;}
      while(uckVjoqKJZ == bCgoMMsKJN){xuYwhZGmTT = true;}
      while(twUaAfWiVC == twUaAfWiVC){QTUEqukDrK = true;}
      while(dAdpQBuBMO == dAdpQBuBMO){YdaZREFLDV = true;}
      if(YiEZYctltu == true){YiEZYctltu = false;}
      if(FKTSzWLEWH == true){FKTSzWLEWH = false;}
      if(TOfwZuyuFi == true){TOfwZuyuFi = false;}
      if(toytALruCX == true){toytALruCX = false;}
      if(ljnawTgLqt == true){ljnawTgLqt = false;}
      if(opeEuJCHAd == true){opeEuJCHAd = false;}
      if(eyfKBPLYSm == true){eyfKBPLYSm = false;}
      if(dQCzViaFzG == true){dQCzViaFzG = false;}
      if(OmDLsDKszq == true){OmDLsDKszq = false;}
      if(IjuXsmEcYf == true){IjuXsmEcYf = false;}
      if(HHrDPYnfhM == true){HHrDPYnfhM = false;}
      if(ixHsPquUQx == true){ixHsPquUQx = false;}
      if(FRZbetVdGi == true){FRZbetVdGi = false;}
      if(dxfTzGtAuU == true){dxfTzGtAuU = false;}
      if(OeKlHKcBIB == true){OeKlHKcBIB = false;}
      if(riMbaogQYV == true){riMbaogQYV = false;}
      if(DKYzhkRntI == true){DKYzhkRntI = false;}
      if(xuYwhZGmTT == true){xuYwhZGmTT = false;}
      if(QTUEqukDrK == true){QTUEqukDrK = false;}
      if(YdaZREFLDV == true){YdaZREFLDV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DLRJUBYXWW
{ 
  void zcWJaEjZSa()
  { 
      bool CmrITnUEeV = false;
      bool aQZsqTgfAP = false;
      bool utVRxIbTWu = false;
      bool unlXxHaXLC = false;
      bool xCzjRtKAVd = false;
      bool zFghiHQZLK = false;
      bool MBhiZleCuj = false;
      bool sIUxRrukAC = false;
      bool yayrwpHDnp = false;
      bool pAMApwUPJe = false;
      bool OHFkkqjiQp = false;
      bool MeYILkDomj = false;
      bool eaNFsruTHU = false;
      bool XebUnqVMHF = false;
      bool FXmxcKaEnE = false;
      bool secYAmszrr = false;
      bool uPbuSgDEUU = false;
      bool PphheGnQbh = false;
      bool QqfCbrCCUA = false;
      bool xVTOJourdw = false;
      string EzmNnUOfif;
      string CklXcoNTOI;
      string OCXJfpnuCf;
      string CUbnVNeliB;
      string mLkHQzNOkG;
      string jwSLFCadgx;
      string gTcDchJyCO;
      string KajNUDQPrf;
      string bZJwuGCPhS;
      string mAElUThhdi;
      string pPLVwJLEqC;
      string kKkBUGJgHW;
      string esPibJVysA;
      string UhlJpMNnzl;
      string txXfgbODQN;
      string JBaHDwAcsl;
      string mNLqhCYbLI;
      string sVgVbgViCA;
      string tSgepSHdGs;
      string LktNyflgxd;
      if(EzmNnUOfif == pPLVwJLEqC){CmrITnUEeV = true;}
      else if(pPLVwJLEqC == EzmNnUOfif){OHFkkqjiQp = true;}
      if(CklXcoNTOI == kKkBUGJgHW){aQZsqTgfAP = true;}
      else if(kKkBUGJgHW == CklXcoNTOI){MeYILkDomj = true;}
      if(OCXJfpnuCf == esPibJVysA){utVRxIbTWu = true;}
      else if(esPibJVysA == OCXJfpnuCf){eaNFsruTHU = true;}
      if(CUbnVNeliB == UhlJpMNnzl){unlXxHaXLC = true;}
      else if(UhlJpMNnzl == CUbnVNeliB){XebUnqVMHF = true;}
      if(mLkHQzNOkG == txXfgbODQN){xCzjRtKAVd = true;}
      else if(txXfgbODQN == mLkHQzNOkG){FXmxcKaEnE = true;}
      if(jwSLFCadgx == JBaHDwAcsl){zFghiHQZLK = true;}
      else if(JBaHDwAcsl == jwSLFCadgx){secYAmszrr = true;}
      if(gTcDchJyCO == mNLqhCYbLI){MBhiZleCuj = true;}
      else if(mNLqhCYbLI == gTcDchJyCO){uPbuSgDEUU = true;}
      if(KajNUDQPrf == sVgVbgViCA){sIUxRrukAC = true;}
      if(bZJwuGCPhS == tSgepSHdGs){yayrwpHDnp = true;}
      if(mAElUThhdi == LktNyflgxd){pAMApwUPJe = true;}
      while(sVgVbgViCA == KajNUDQPrf){PphheGnQbh = true;}
      while(tSgepSHdGs == tSgepSHdGs){QqfCbrCCUA = true;}
      while(LktNyflgxd == LktNyflgxd){xVTOJourdw = true;}
      if(CmrITnUEeV == true){CmrITnUEeV = false;}
      if(aQZsqTgfAP == true){aQZsqTgfAP = false;}
      if(utVRxIbTWu == true){utVRxIbTWu = false;}
      if(unlXxHaXLC == true){unlXxHaXLC = false;}
      if(xCzjRtKAVd == true){xCzjRtKAVd = false;}
      if(zFghiHQZLK == true){zFghiHQZLK = false;}
      if(MBhiZleCuj == true){MBhiZleCuj = false;}
      if(sIUxRrukAC == true){sIUxRrukAC = false;}
      if(yayrwpHDnp == true){yayrwpHDnp = false;}
      if(pAMApwUPJe == true){pAMApwUPJe = false;}
      if(OHFkkqjiQp == true){OHFkkqjiQp = false;}
      if(MeYILkDomj == true){MeYILkDomj = false;}
      if(eaNFsruTHU == true){eaNFsruTHU = false;}
      if(XebUnqVMHF == true){XebUnqVMHF = false;}
      if(FXmxcKaEnE == true){FXmxcKaEnE = false;}
      if(secYAmszrr == true){secYAmszrr = false;}
      if(uPbuSgDEUU == true){uPbuSgDEUU = false;}
      if(PphheGnQbh == true){PphheGnQbh = false;}
      if(QqfCbrCCUA == true){QqfCbrCCUA = false;}
      if(xVTOJourdw == true){xVTOJourdw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ETHKILUVMZ
{ 
  void bcJOfwWEKp()
  { 
      bool HAiguUIKkA = false;
      bool xTufxWoDYr = false;
      bool wxYKpBOaDd = false;
      bool lrezglhqCM = false;
      bool CJdupEleRY = false;
      bool mjqxbKbXpt = false;
      bool GhHGOEouyL = false;
      bool oxBMplTcUl = false;
      bool OjIdqBAhWW = false;
      bool JJBHGTBWfk = false;
      bool PqfGjpheHo = false;
      bool pyCEeVZcPN = false;
      bool DGXbBeutFV = false;
      bool kxxjWXDBtA = false;
      bool TVahfKGxbj = false;
      bool tXGSgISEFE = false;
      bool tnZlEsBSgH = false;
      bool SXiOshfpup = false;
      bool YyRUaNpeCO = false;
      bool EywpFeuodm = false;
      string eYopkQCnkc;
      string NOsqCnYPNt;
      string WQIjOqDmGg;
      string FgWWxESATZ;
      string QWuMWfZYbN;
      string LePOOOQFat;
      string NPhDWfqWtx;
      string VYumdAUwNi;
      string QeKrVZRIHh;
      string nNZZMAoqop;
      string oDddrmjbjO;
      string tTrrciFphx;
      string OhOLJIyVac;
      string KdHWsNAfzi;
      string poYsnUVgwd;
      string tzJraGoSUj;
      string nNBHDPMUyP;
      string hZpyGZJUXo;
      string mQYxhLTOwm;
      string YgKPubnQoX;
      if(eYopkQCnkc == oDddrmjbjO){HAiguUIKkA = true;}
      else if(oDddrmjbjO == eYopkQCnkc){PqfGjpheHo = true;}
      if(NOsqCnYPNt == tTrrciFphx){xTufxWoDYr = true;}
      else if(tTrrciFphx == NOsqCnYPNt){pyCEeVZcPN = true;}
      if(WQIjOqDmGg == OhOLJIyVac){wxYKpBOaDd = true;}
      else if(OhOLJIyVac == WQIjOqDmGg){DGXbBeutFV = true;}
      if(FgWWxESATZ == KdHWsNAfzi){lrezglhqCM = true;}
      else if(KdHWsNAfzi == FgWWxESATZ){kxxjWXDBtA = true;}
      if(QWuMWfZYbN == poYsnUVgwd){CJdupEleRY = true;}
      else if(poYsnUVgwd == QWuMWfZYbN){TVahfKGxbj = true;}
      if(LePOOOQFat == tzJraGoSUj){mjqxbKbXpt = true;}
      else if(tzJraGoSUj == LePOOOQFat){tXGSgISEFE = true;}
      if(NPhDWfqWtx == nNBHDPMUyP){GhHGOEouyL = true;}
      else if(nNBHDPMUyP == NPhDWfqWtx){tnZlEsBSgH = true;}
      if(VYumdAUwNi == hZpyGZJUXo){oxBMplTcUl = true;}
      if(QeKrVZRIHh == mQYxhLTOwm){OjIdqBAhWW = true;}
      if(nNZZMAoqop == YgKPubnQoX){JJBHGTBWfk = true;}
      while(hZpyGZJUXo == VYumdAUwNi){SXiOshfpup = true;}
      while(mQYxhLTOwm == mQYxhLTOwm){YyRUaNpeCO = true;}
      while(YgKPubnQoX == YgKPubnQoX){EywpFeuodm = true;}
      if(HAiguUIKkA == true){HAiguUIKkA = false;}
      if(xTufxWoDYr == true){xTufxWoDYr = false;}
      if(wxYKpBOaDd == true){wxYKpBOaDd = false;}
      if(lrezglhqCM == true){lrezglhqCM = false;}
      if(CJdupEleRY == true){CJdupEleRY = false;}
      if(mjqxbKbXpt == true){mjqxbKbXpt = false;}
      if(GhHGOEouyL == true){GhHGOEouyL = false;}
      if(oxBMplTcUl == true){oxBMplTcUl = false;}
      if(OjIdqBAhWW == true){OjIdqBAhWW = false;}
      if(JJBHGTBWfk == true){JJBHGTBWfk = false;}
      if(PqfGjpheHo == true){PqfGjpheHo = false;}
      if(pyCEeVZcPN == true){pyCEeVZcPN = false;}
      if(DGXbBeutFV == true){DGXbBeutFV = false;}
      if(kxxjWXDBtA == true){kxxjWXDBtA = false;}
      if(TVahfKGxbj == true){TVahfKGxbj = false;}
      if(tXGSgISEFE == true){tXGSgISEFE = false;}
      if(tnZlEsBSgH == true){tnZlEsBSgH = false;}
      if(SXiOshfpup == true){SXiOshfpup = false;}
      if(YyRUaNpeCO == true){YyRUaNpeCO = false;}
      if(EywpFeuodm == true){EywpFeuodm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JUCRJWMLQS
{ 
  void LHkzIknocF()
  { 
      bool kRLrDemHcg = false;
      bool Zuspqdnnfl = false;
      bool tlFQGRoDQm = false;
      bool dCSrwYmhic = false;
      bool pXWXhQkNsR = false;
      bool MRxSTzLulk = false;
      bool oipoDWbBtR = false;
      bool pGFDuWOhho = false;
      bool gaKzZLEzYx = false;
      bool MrwxmHggTK = false;
      bool njTaaGMtWw = false;
      bool jdNwENYpOr = false;
      bool RbbxFyKIPn = false;
      bool phNWBwHiYT = false;
      bool yJccMhezrZ = false;
      bool hpRarLHVVc = false;
      bool uEeiFBPptI = false;
      bool GoRusIzzjW = false;
      bool TKPoFAQldp = false;
      bool okNuXtetWK = false;
      string TegPJenUge;
      string XXWGAYgejA;
      string plkuKaeLwH;
      string HOkrwUuanZ;
      string XFfuqrnFHd;
      string TqVyEgtlEi;
      string AbYYWIleJe;
      string cGqKckGpES;
      string mZESmQrmmO;
      string aJVFZwgGXh;
      string FJubANALUT;
      string ZDgluZWFlF;
      string QzquESjkkg;
      string EARWNddcRY;
      string QgSTnWbjKz;
      string YaURRGRAXh;
      string dOZnPZlKXR;
      string wtnMojgWGg;
      string pzZlHcezFH;
      string LdEjuBGdEO;
      if(TegPJenUge == FJubANALUT){kRLrDemHcg = true;}
      else if(FJubANALUT == TegPJenUge){njTaaGMtWw = true;}
      if(XXWGAYgejA == ZDgluZWFlF){Zuspqdnnfl = true;}
      else if(ZDgluZWFlF == XXWGAYgejA){jdNwENYpOr = true;}
      if(plkuKaeLwH == QzquESjkkg){tlFQGRoDQm = true;}
      else if(QzquESjkkg == plkuKaeLwH){RbbxFyKIPn = true;}
      if(HOkrwUuanZ == EARWNddcRY){dCSrwYmhic = true;}
      else if(EARWNddcRY == HOkrwUuanZ){phNWBwHiYT = true;}
      if(XFfuqrnFHd == QgSTnWbjKz){pXWXhQkNsR = true;}
      else if(QgSTnWbjKz == XFfuqrnFHd){yJccMhezrZ = true;}
      if(TqVyEgtlEi == YaURRGRAXh){MRxSTzLulk = true;}
      else if(YaURRGRAXh == TqVyEgtlEi){hpRarLHVVc = true;}
      if(AbYYWIleJe == dOZnPZlKXR){oipoDWbBtR = true;}
      else if(dOZnPZlKXR == AbYYWIleJe){uEeiFBPptI = true;}
      if(cGqKckGpES == wtnMojgWGg){pGFDuWOhho = true;}
      if(mZESmQrmmO == pzZlHcezFH){gaKzZLEzYx = true;}
      if(aJVFZwgGXh == LdEjuBGdEO){MrwxmHggTK = true;}
      while(wtnMojgWGg == cGqKckGpES){GoRusIzzjW = true;}
      while(pzZlHcezFH == pzZlHcezFH){TKPoFAQldp = true;}
      while(LdEjuBGdEO == LdEjuBGdEO){okNuXtetWK = true;}
      if(kRLrDemHcg == true){kRLrDemHcg = false;}
      if(Zuspqdnnfl == true){Zuspqdnnfl = false;}
      if(tlFQGRoDQm == true){tlFQGRoDQm = false;}
      if(dCSrwYmhic == true){dCSrwYmhic = false;}
      if(pXWXhQkNsR == true){pXWXhQkNsR = false;}
      if(MRxSTzLulk == true){MRxSTzLulk = false;}
      if(oipoDWbBtR == true){oipoDWbBtR = false;}
      if(pGFDuWOhho == true){pGFDuWOhho = false;}
      if(gaKzZLEzYx == true){gaKzZLEzYx = false;}
      if(MrwxmHggTK == true){MrwxmHggTK = false;}
      if(njTaaGMtWw == true){njTaaGMtWw = false;}
      if(jdNwENYpOr == true){jdNwENYpOr = false;}
      if(RbbxFyKIPn == true){RbbxFyKIPn = false;}
      if(phNWBwHiYT == true){phNWBwHiYT = false;}
      if(yJccMhezrZ == true){yJccMhezrZ = false;}
      if(hpRarLHVVc == true){hpRarLHVVc = false;}
      if(uEeiFBPptI == true){uEeiFBPptI = false;}
      if(GoRusIzzjW == true){GoRusIzzjW = false;}
      if(TKPoFAQldp == true){TKPoFAQldp = false;}
      if(okNuXtetWK == true){okNuXtetWK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GICGJZZPKG
{ 
  void oxcpiOUGkT()
  { 
      bool kxhxInalAy = false;
      bool iUFUcrJoWl = false;
      bool cQrezsfPcL = false;
      bool bNMMEcTiTV = false;
      bool IqWMNKJwss = false;
      bool uttPBTFDyO = false;
      bool HKIoVVIrQz = false;
      bool XaUBckseQn = false;
      bool jiWjPgSxLj = false;
      bool XQjFNxhhpq = false;
      bool CQftUUZslP = false;
      bool ZZmJeYnYYn = false;
      bool CLgfaHpPme = false;
      bool CLoYlSDcOu = false;
      bool HZKuJydaZo = false;
      bool JJIBopjzSN = false;
      bool dKFGMOjNWL = false;
      bool VKKdgcBlWc = false;
      bool dPoyVsCmjw = false;
      bool iDJBQwUDhu = false;
      string fJDaROXquo;
      string XGJmbiqpPp;
      string GPJnojKxcI;
      string fyFfmGlhGm;
      string kklnwpyZua;
      string RjlgoPAOlg;
      string EaNmIYAcAV;
      string xJibFUdUrz;
      string kkBCpwLYqW;
      string FWwZiKXyeW;
      string oVZZdIAKaT;
      string leWluSYKxM;
      string MblcPZMJru;
      string xepUKPLbYh;
      string uBxXkazJdP;
      string kMBRJNiwJD;
      string upRfVGoCbf;
      string HxlPQLdNqo;
      string aCfcJjdXKx;
      string fORVlFjQBe;
      if(fJDaROXquo == oVZZdIAKaT){kxhxInalAy = true;}
      else if(oVZZdIAKaT == fJDaROXquo){CQftUUZslP = true;}
      if(XGJmbiqpPp == leWluSYKxM){iUFUcrJoWl = true;}
      else if(leWluSYKxM == XGJmbiqpPp){ZZmJeYnYYn = true;}
      if(GPJnojKxcI == MblcPZMJru){cQrezsfPcL = true;}
      else if(MblcPZMJru == GPJnojKxcI){CLgfaHpPme = true;}
      if(fyFfmGlhGm == xepUKPLbYh){bNMMEcTiTV = true;}
      else if(xepUKPLbYh == fyFfmGlhGm){CLoYlSDcOu = true;}
      if(kklnwpyZua == uBxXkazJdP){IqWMNKJwss = true;}
      else if(uBxXkazJdP == kklnwpyZua){HZKuJydaZo = true;}
      if(RjlgoPAOlg == kMBRJNiwJD){uttPBTFDyO = true;}
      else if(kMBRJNiwJD == RjlgoPAOlg){JJIBopjzSN = true;}
      if(EaNmIYAcAV == upRfVGoCbf){HKIoVVIrQz = true;}
      else if(upRfVGoCbf == EaNmIYAcAV){dKFGMOjNWL = true;}
      if(xJibFUdUrz == HxlPQLdNqo){XaUBckseQn = true;}
      if(kkBCpwLYqW == aCfcJjdXKx){jiWjPgSxLj = true;}
      if(FWwZiKXyeW == fORVlFjQBe){XQjFNxhhpq = true;}
      while(HxlPQLdNqo == xJibFUdUrz){VKKdgcBlWc = true;}
      while(aCfcJjdXKx == aCfcJjdXKx){dPoyVsCmjw = true;}
      while(fORVlFjQBe == fORVlFjQBe){iDJBQwUDhu = true;}
      if(kxhxInalAy == true){kxhxInalAy = false;}
      if(iUFUcrJoWl == true){iUFUcrJoWl = false;}
      if(cQrezsfPcL == true){cQrezsfPcL = false;}
      if(bNMMEcTiTV == true){bNMMEcTiTV = false;}
      if(IqWMNKJwss == true){IqWMNKJwss = false;}
      if(uttPBTFDyO == true){uttPBTFDyO = false;}
      if(HKIoVVIrQz == true){HKIoVVIrQz = false;}
      if(XaUBckseQn == true){XaUBckseQn = false;}
      if(jiWjPgSxLj == true){jiWjPgSxLj = false;}
      if(XQjFNxhhpq == true){XQjFNxhhpq = false;}
      if(CQftUUZslP == true){CQftUUZslP = false;}
      if(ZZmJeYnYYn == true){ZZmJeYnYYn = false;}
      if(CLgfaHpPme == true){CLgfaHpPme = false;}
      if(CLoYlSDcOu == true){CLoYlSDcOu = false;}
      if(HZKuJydaZo == true){HZKuJydaZo = false;}
      if(JJIBopjzSN == true){JJIBopjzSN = false;}
      if(dKFGMOjNWL == true){dKFGMOjNWL = false;}
      if(VKKdgcBlWc == true){VKKdgcBlWc = false;}
      if(dPoyVsCmjw == true){dPoyVsCmjw = false;}
      if(iDJBQwUDhu == true){iDJBQwUDhu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSUOPVGHZR
{ 
  void JaijxebPhg()
  { 
      bool wmXGpbGYdi = false;
      bool DAXsfexNWs = false;
      bool FYKOmacBaK = false;
      bool WSrPNhyCrB = false;
      bool IixwPtaxai = false;
      bool mYnGyXbJSP = false;
      bool yFyTMjHIex = false;
      bool ftVVjWaNyr = false;
      bool zfarWxekRp = false;
      bool FoibCDjdjf = false;
      bool lSRcCrDSWa = false;
      bool wOKaQSeGwP = false;
      bool EVqnrqLsSg = false;
      bool lxdSGgNxod = false;
      bool sMOptqdILj = false;
      bool YdgUaQbckK = false;
      bool gJzpozkrTi = false;
      bool EgQRVrHAtA = false;
      bool NChiHIPJqp = false;
      bool FjMdwiNYAu = false;
      string PHzVjToPah;
      string eMqJNMEVxH;
      string EuxWReiVug;
      string DGnqWIUpOR;
      string axJnLuuPQp;
      string pJaEuUKbDF;
      string jSTsdYYzmF;
      string qNGffHkJLW;
      string iTFFqseiwB;
      string xslJgIcPJl;
      string WucLybDuXm;
      string iAPgVQNOCk;
      string soCkHyaxyX;
      string dVAYAnptGO;
      string pjKJRxcEnQ;
      string uOMYsgsqDA;
      string BFwAINApgh;
      string ZSHntJdsTK;
      string UVIhcPIbfS;
      string tzpGNjmKAD;
      if(PHzVjToPah == WucLybDuXm){wmXGpbGYdi = true;}
      else if(WucLybDuXm == PHzVjToPah){lSRcCrDSWa = true;}
      if(eMqJNMEVxH == iAPgVQNOCk){DAXsfexNWs = true;}
      else if(iAPgVQNOCk == eMqJNMEVxH){wOKaQSeGwP = true;}
      if(EuxWReiVug == soCkHyaxyX){FYKOmacBaK = true;}
      else if(soCkHyaxyX == EuxWReiVug){EVqnrqLsSg = true;}
      if(DGnqWIUpOR == dVAYAnptGO){WSrPNhyCrB = true;}
      else if(dVAYAnptGO == DGnqWIUpOR){lxdSGgNxod = true;}
      if(axJnLuuPQp == pjKJRxcEnQ){IixwPtaxai = true;}
      else if(pjKJRxcEnQ == axJnLuuPQp){sMOptqdILj = true;}
      if(pJaEuUKbDF == uOMYsgsqDA){mYnGyXbJSP = true;}
      else if(uOMYsgsqDA == pJaEuUKbDF){YdgUaQbckK = true;}
      if(jSTsdYYzmF == BFwAINApgh){yFyTMjHIex = true;}
      else if(BFwAINApgh == jSTsdYYzmF){gJzpozkrTi = true;}
      if(qNGffHkJLW == ZSHntJdsTK){ftVVjWaNyr = true;}
      if(iTFFqseiwB == UVIhcPIbfS){zfarWxekRp = true;}
      if(xslJgIcPJl == tzpGNjmKAD){FoibCDjdjf = true;}
      while(ZSHntJdsTK == qNGffHkJLW){EgQRVrHAtA = true;}
      while(UVIhcPIbfS == UVIhcPIbfS){NChiHIPJqp = true;}
      while(tzpGNjmKAD == tzpGNjmKAD){FjMdwiNYAu = true;}
      if(wmXGpbGYdi == true){wmXGpbGYdi = false;}
      if(DAXsfexNWs == true){DAXsfexNWs = false;}
      if(FYKOmacBaK == true){FYKOmacBaK = false;}
      if(WSrPNhyCrB == true){WSrPNhyCrB = false;}
      if(IixwPtaxai == true){IixwPtaxai = false;}
      if(mYnGyXbJSP == true){mYnGyXbJSP = false;}
      if(yFyTMjHIex == true){yFyTMjHIex = false;}
      if(ftVVjWaNyr == true){ftVVjWaNyr = false;}
      if(zfarWxekRp == true){zfarWxekRp = false;}
      if(FoibCDjdjf == true){FoibCDjdjf = false;}
      if(lSRcCrDSWa == true){lSRcCrDSWa = false;}
      if(wOKaQSeGwP == true){wOKaQSeGwP = false;}
      if(EVqnrqLsSg == true){EVqnrqLsSg = false;}
      if(lxdSGgNxod == true){lxdSGgNxod = false;}
      if(sMOptqdILj == true){sMOptqdILj = false;}
      if(YdgUaQbckK == true){YdgUaQbckK = false;}
      if(gJzpozkrTi == true){gJzpozkrTi = false;}
      if(EgQRVrHAtA == true){EgQRVrHAtA = false;}
      if(NChiHIPJqp == true){NChiHIPJqp = false;}
      if(FjMdwiNYAu == true){FjMdwiNYAu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OLWYEEXVPR
{ 
  void AdaVwecYOR()
  { 
      bool qGppGcSTUD = false;
      bool pgdbtSMewR = false;
      bool UbaEthCwcW = false;
      bool uGZnskhzZI = false;
      bool yNFaNBXcGE = false;
      bool LEuTlOekwY = false;
      bool aWpyHiGphI = false;
      bool jMFnSGWAqr = false;
      bool JZpYKqKGCe = false;
      bool GxDBgbWGSd = false;
      bool uhtxTyzHAe = false;
      bool qetDPBfQnP = false;
      bool YAnDBmJDGq = false;
      bool iPgNxberFL = false;
      bool rDGWmaDzke = false;
      bool uGSDEttqwg = false;
      bool ouAJuayfFn = false;
      bool WmLbXVtQPZ = false;
      bool jJSbucxdIC = false;
      bool gnwYWxCwbL = false;
      string ojiRlDqJrj;
      string CJsJXBRInN;
      string nEQrPjqNyE;
      string erJewGTyaO;
      string jIVpUMknGW;
      string esKfukTpCC;
      string MdKmFJAOMQ;
      string gShZceiaXD;
      string yCGbZkhciK;
      string mdwXBGyhjK;
      string LWapoMLkDP;
      string CsRzEKWiNU;
      string bXeCdDVJXV;
      string gApMqaaQlN;
      string ZwZTHsLxTp;
      string jPTPinrYLl;
      string pBMhiBCFHc;
      string jGwAteyKtj;
      string rXogkRgadD;
      string iCEAWXjqkG;
      if(ojiRlDqJrj == LWapoMLkDP){qGppGcSTUD = true;}
      else if(LWapoMLkDP == ojiRlDqJrj){uhtxTyzHAe = true;}
      if(CJsJXBRInN == CsRzEKWiNU){pgdbtSMewR = true;}
      else if(CsRzEKWiNU == CJsJXBRInN){qetDPBfQnP = true;}
      if(nEQrPjqNyE == bXeCdDVJXV){UbaEthCwcW = true;}
      else if(bXeCdDVJXV == nEQrPjqNyE){YAnDBmJDGq = true;}
      if(erJewGTyaO == gApMqaaQlN){uGZnskhzZI = true;}
      else if(gApMqaaQlN == erJewGTyaO){iPgNxberFL = true;}
      if(jIVpUMknGW == ZwZTHsLxTp){yNFaNBXcGE = true;}
      else if(ZwZTHsLxTp == jIVpUMknGW){rDGWmaDzke = true;}
      if(esKfukTpCC == jPTPinrYLl){LEuTlOekwY = true;}
      else if(jPTPinrYLl == esKfukTpCC){uGSDEttqwg = true;}
      if(MdKmFJAOMQ == pBMhiBCFHc){aWpyHiGphI = true;}
      else if(pBMhiBCFHc == MdKmFJAOMQ){ouAJuayfFn = true;}
      if(gShZceiaXD == jGwAteyKtj){jMFnSGWAqr = true;}
      if(yCGbZkhciK == rXogkRgadD){JZpYKqKGCe = true;}
      if(mdwXBGyhjK == iCEAWXjqkG){GxDBgbWGSd = true;}
      while(jGwAteyKtj == gShZceiaXD){WmLbXVtQPZ = true;}
      while(rXogkRgadD == rXogkRgadD){jJSbucxdIC = true;}
      while(iCEAWXjqkG == iCEAWXjqkG){gnwYWxCwbL = true;}
      if(qGppGcSTUD == true){qGppGcSTUD = false;}
      if(pgdbtSMewR == true){pgdbtSMewR = false;}
      if(UbaEthCwcW == true){UbaEthCwcW = false;}
      if(uGZnskhzZI == true){uGZnskhzZI = false;}
      if(yNFaNBXcGE == true){yNFaNBXcGE = false;}
      if(LEuTlOekwY == true){LEuTlOekwY = false;}
      if(aWpyHiGphI == true){aWpyHiGphI = false;}
      if(jMFnSGWAqr == true){jMFnSGWAqr = false;}
      if(JZpYKqKGCe == true){JZpYKqKGCe = false;}
      if(GxDBgbWGSd == true){GxDBgbWGSd = false;}
      if(uhtxTyzHAe == true){uhtxTyzHAe = false;}
      if(qetDPBfQnP == true){qetDPBfQnP = false;}
      if(YAnDBmJDGq == true){YAnDBmJDGq = false;}
      if(iPgNxberFL == true){iPgNxberFL = false;}
      if(rDGWmaDzke == true){rDGWmaDzke = false;}
      if(uGSDEttqwg == true){uGSDEttqwg = false;}
      if(ouAJuayfFn == true){ouAJuayfFn = false;}
      if(WmLbXVtQPZ == true){WmLbXVtQPZ = false;}
      if(jJSbucxdIC == true){jJSbucxdIC = false;}
      if(gnwYWxCwbL == true){gnwYWxCwbL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KQTDBOSIHZ
{ 
  void SEYxIkzJZV()
  { 
      bool XeERExhKzb = false;
      bool QsyNOfFUHC = false;
      bool wRWczCBgfS = false;
      bool rKOmiLYPmR = false;
      bool crLRMZxbzE = false;
      bool KoqitFHbSC = false;
      bool wAdgjGdKeD = false;
      bool HpgpYDGFPY = false;
      bool EYhaHCSerc = false;
      bool DwwjUbNdhG = false;
      bool ulxuwUHBJq = false;
      bool yCLsxXSDZg = false;
      bool mzRBzLsxUx = false;
      bool pcWJdSbldl = false;
      bool uRVBdAjClx = false;
      bool JKEBSwUwwk = false;
      bool bKgMBVfCPe = false;
      bool ufYmlUcQWy = false;
      bool bpKWmeYVpg = false;
      bool yfpsKkjIAI = false;
      string VhtdYpkKKC;
      string FCaLzcGfbX;
      string zTqeEqDxhD;
      string BDVeWQCuxJ;
      string dTxYEpmkKU;
      string JoYWfBqPYh;
      string mnbHACgwoh;
      string aKhRteVSZO;
      string DSlNtLdzyU;
      string ZlVPWpqpXC;
      string JquctyGHbA;
      string eXoKeUBONn;
      string XgyTInnStE;
      string nftXEMWJTu;
      string EWWypBxKkC;
      string occidbsbTF;
      string JnMXMzdRFS;
      string xquRiBKzdG;
      string qchrPKDLtc;
      string SuoNkQJzkp;
      if(VhtdYpkKKC == JquctyGHbA){XeERExhKzb = true;}
      else if(JquctyGHbA == VhtdYpkKKC){ulxuwUHBJq = true;}
      if(FCaLzcGfbX == eXoKeUBONn){QsyNOfFUHC = true;}
      else if(eXoKeUBONn == FCaLzcGfbX){yCLsxXSDZg = true;}
      if(zTqeEqDxhD == XgyTInnStE){wRWczCBgfS = true;}
      else if(XgyTInnStE == zTqeEqDxhD){mzRBzLsxUx = true;}
      if(BDVeWQCuxJ == nftXEMWJTu){rKOmiLYPmR = true;}
      else if(nftXEMWJTu == BDVeWQCuxJ){pcWJdSbldl = true;}
      if(dTxYEpmkKU == EWWypBxKkC){crLRMZxbzE = true;}
      else if(EWWypBxKkC == dTxYEpmkKU){uRVBdAjClx = true;}
      if(JoYWfBqPYh == occidbsbTF){KoqitFHbSC = true;}
      else if(occidbsbTF == JoYWfBqPYh){JKEBSwUwwk = true;}
      if(mnbHACgwoh == JnMXMzdRFS){wAdgjGdKeD = true;}
      else if(JnMXMzdRFS == mnbHACgwoh){bKgMBVfCPe = true;}
      if(aKhRteVSZO == xquRiBKzdG){HpgpYDGFPY = true;}
      if(DSlNtLdzyU == qchrPKDLtc){EYhaHCSerc = true;}
      if(ZlVPWpqpXC == SuoNkQJzkp){DwwjUbNdhG = true;}
      while(xquRiBKzdG == aKhRteVSZO){ufYmlUcQWy = true;}
      while(qchrPKDLtc == qchrPKDLtc){bpKWmeYVpg = true;}
      while(SuoNkQJzkp == SuoNkQJzkp){yfpsKkjIAI = true;}
      if(XeERExhKzb == true){XeERExhKzb = false;}
      if(QsyNOfFUHC == true){QsyNOfFUHC = false;}
      if(wRWczCBgfS == true){wRWczCBgfS = false;}
      if(rKOmiLYPmR == true){rKOmiLYPmR = false;}
      if(crLRMZxbzE == true){crLRMZxbzE = false;}
      if(KoqitFHbSC == true){KoqitFHbSC = false;}
      if(wAdgjGdKeD == true){wAdgjGdKeD = false;}
      if(HpgpYDGFPY == true){HpgpYDGFPY = false;}
      if(EYhaHCSerc == true){EYhaHCSerc = false;}
      if(DwwjUbNdhG == true){DwwjUbNdhG = false;}
      if(ulxuwUHBJq == true){ulxuwUHBJq = false;}
      if(yCLsxXSDZg == true){yCLsxXSDZg = false;}
      if(mzRBzLsxUx == true){mzRBzLsxUx = false;}
      if(pcWJdSbldl == true){pcWJdSbldl = false;}
      if(uRVBdAjClx == true){uRVBdAjClx = false;}
      if(JKEBSwUwwk == true){JKEBSwUwwk = false;}
      if(bKgMBVfCPe == true){bKgMBVfCPe = false;}
      if(ufYmlUcQWy == true){ufYmlUcQWy = false;}
      if(bpKWmeYVpg == true){bpKWmeYVpg = false;}
      if(yfpsKkjIAI == true){yfpsKkjIAI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPRHGMPJIL
{ 
  void ZZBKsIRBhB()
  { 
      bool SdqjnbhcJU = false;
      bool IIkKnkZHWb = false;
      bool WWnPMijdXu = false;
      bool tELogKnAkI = false;
      bool XjIoTimNZb = false;
      bool oAQnhwpbWF = false;
      bool rEEOZDxudc = false;
      bool wYWOEmOyud = false;
      bool uWDwGsnWGk = false;
      bool UMceQTesOP = false;
      bool lqjxePdCju = false;
      bool hqfsJUAIIg = false;
      bool PZorHiuqyj = false;
      bool HUieqDmGQp = false;
      bool OlmLDdgjVu = false;
      bool SWkhALCqow = false;
      bool TmDzmMHBBG = false;
      bool htqRRclcod = false;
      bool CLVCQkiBdf = false;
      bool AuQUWbhnYp = false;
      string SBUQEFXmiW;
      string yXPBAOQbRh;
      string fEhqZmXXMK;
      string gSHZPEmwjo;
      string elAruFACRX;
      string AZcgJOScpR;
      string hzZXpfPplw;
      string bUqbCsDowU;
      string lVFnJHoaPB;
      string lJFSHfMbCO;
      string pKQVwfhAeQ;
      string LcgVeMskOi;
      string qnajJSOXUW;
      string gamhdaEjrd;
      string YnuzpJcimu;
      string laNTWBjfLd;
      string QKfHijpyrD;
      string HJrkJCrbtA;
      string ofjYkGMSKc;
      string qYYOMOInPF;
      if(SBUQEFXmiW == pKQVwfhAeQ){SdqjnbhcJU = true;}
      else if(pKQVwfhAeQ == SBUQEFXmiW){lqjxePdCju = true;}
      if(yXPBAOQbRh == LcgVeMskOi){IIkKnkZHWb = true;}
      else if(LcgVeMskOi == yXPBAOQbRh){hqfsJUAIIg = true;}
      if(fEhqZmXXMK == qnajJSOXUW){WWnPMijdXu = true;}
      else if(qnajJSOXUW == fEhqZmXXMK){PZorHiuqyj = true;}
      if(gSHZPEmwjo == gamhdaEjrd){tELogKnAkI = true;}
      else if(gamhdaEjrd == gSHZPEmwjo){HUieqDmGQp = true;}
      if(elAruFACRX == YnuzpJcimu){XjIoTimNZb = true;}
      else if(YnuzpJcimu == elAruFACRX){OlmLDdgjVu = true;}
      if(AZcgJOScpR == laNTWBjfLd){oAQnhwpbWF = true;}
      else if(laNTWBjfLd == AZcgJOScpR){SWkhALCqow = true;}
      if(hzZXpfPplw == QKfHijpyrD){rEEOZDxudc = true;}
      else if(QKfHijpyrD == hzZXpfPplw){TmDzmMHBBG = true;}
      if(bUqbCsDowU == HJrkJCrbtA){wYWOEmOyud = true;}
      if(lVFnJHoaPB == ofjYkGMSKc){uWDwGsnWGk = true;}
      if(lJFSHfMbCO == qYYOMOInPF){UMceQTesOP = true;}
      while(HJrkJCrbtA == bUqbCsDowU){htqRRclcod = true;}
      while(ofjYkGMSKc == ofjYkGMSKc){CLVCQkiBdf = true;}
      while(qYYOMOInPF == qYYOMOInPF){AuQUWbhnYp = true;}
      if(SdqjnbhcJU == true){SdqjnbhcJU = false;}
      if(IIkKnkZHWb == true){IIkKnkZHWb = false;}
      if(WWnPMijdXu == true){WWnPMijdXu = false;}
      if(tELogKnAkI == true){tELogKnAkI = false;}
      if(XjIoTimNZb == true){XjIoTimNZb = false;}
      if(oAQnhwpbWF == true){oAQnhwpbWF = false;}
      if(rEEOZDxudc == true){rEEOZDxudc = false;}
      if(wYWOEmOyud == true){wYWOEmOyud = false;}
      if(uWDwGsnWGk == true){uWDwGsnWGk = false;}
      if(UMceQTesOP == true){UMceQTesOP = false;}
      if(lqjxePdCju == true){lqjxePdCju = false;}
      if(hqfsJUAIIg == true){hqfsJUAIIg = false;}
      if(PZorHiuqyj == true){PZorHiuqyj = false;}
      if(HUieqDmGQp == true){HUieqDmGQp = false;}
      if(OlmLDdgjVu == true){OlmLDdgjVu = false;}
      if(SWkhALCqow == true){SWkhALCqow = false;}
      if(TmDzmMHBBG == true){TmDzmMHBBG = false;}
      if(htqRRclcod == true){htqRRclcod = false;}
      if(CLVCQkiBdf == true){CLVCQkiBdf = false;}
      if(AuQUWbhnYp == true){AuQUWbhnYp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GQNHKPDJSN
{ 
  void zlyUlQTVzu()
  { 
      bool bEDhWeJiwh = false;
      bool bOBerzWpiS = false;
      bool BzYpylNhgU = false;
      bool JlhriiFizo = false;
      bool sOqSMVznLX = false;
      bool kueZNcfNik = false;
      bool QaBbYpgIuI = false;
      bool smptZmHFdc = false;
      bool mZWJjOHIeF = false;
      bool DrAOXSMPtV = false;
      bool npsCdxFjAa = false;
      bool VaiGyqDrqJ = false;
      bool iYdoFAmaWH = false;
      bool ZrKHnwgUel = false;
      bool JWHEjcJsQf = false;
      bool OUXjmPLDxc = false;
      bool KdMrAcPbRB = false;
      bool KiMFALQZEc = false;
      bool qsJqrFTZTX = false;
      bool jcWBbeJODG = false;
      string jGXlljzpcx;
      string XlpHLwPKtA;
      string huyPbQshlK;
      string EjRQmWspyB;
      string STooMOHBHC;
      string bkoQgoIIJU;
      string qQESrnTZUo;
      string DZMsgNGIDM;
      string JqaihTtBix;
      string OjfcKBPVwX;
      string uhfRzCXwiT;
      string izFxLzpUjX;
      string tSqWaSsiif;
      string xjMeRbKJif;
      string wyRPOOeiRL;
      string LulYdcqJpf;
      string JnNDVzmZei;
      string nfkDbuAbHL;
      string nJRWTCxmBo;
      string kBSDWHkOsP;
      if(jGXlljzpcx == uhfRzCXwiT){bEDhWeJiwh = true;}
      else if(uhfRzCXwiT == jGXlljzpcx){npsCdxFjAa = true;}
      if(XlpHLwPKtA == izFxLzpUjX){bOBerzWpiS = true;}
      else if(izFxLzpUjX == XlpHLwPKtA){VaiGyqDrqJ = true;}
      if(huyPbQshlK == tSqWaSsiif){BzYpylNhgU = true;}
      else if(tSqWaSsiif == huyPbQshlK){iYdoFAmaWH = true;}
      if(EjRQmWspyB == xjMeRbKJif){JlhriiFizo = true;}
      else if(xjMeRbKJif == EjRQmWspyB){ZrKHnwgUel = true;}
      if(STooMOHBHC == wyRPOOeiRL){sOqSMVznLX = true;}
      else if(wyRPOOeiRL == STooMOHBHC){JWHEjcJsQf = true;}
      if(bkoQgoIIJU == LulYdcqJpf){kueZNcfNik = true;}
      else if(LulYdcqJpf == bkoQgoIIJU){OUXjmPLDxc = true;}
      if(qQESrnTZUo == JnNDVzmZei){QaBbYpgIuI = true;}
      else if(JnNDVzmZei == qQESrnTZUo){KdMrAcPbRB = true;}
      if(DZMsgNGIDM == nfkDbuAbHL){smptZmHFdc = true;}
      if(JqaihTtBix == nJRWTCxmBo){mZWJjOHIeF = true;}
      if(OjfcKBPVwX == kBSDWHkOsP){DrAOXSMPtV = true;}
      while(nfkDbuAbHL == DZMsgNGIDM){KiMFALQZEc = true;}
      while(nJRWTCxmBo == nJRWTCxmBo){qsJqrFTZTX = true;}
      while(kBSDWHkOsP == kBSDWHkOsP){jcWBbeJODG = true;}
      if(bEDhWeJiwh == true){bEDhWeJiwh = false;}
      if(bOBerzWpiS == true){bOBerzWpiS = false;}
      if(BzYpylNhgU == true){BzYpylNhgU = false;}
      if(JlhriiFizo == true){JlhriiFizo = false;}
      if(sOqSMVznLX == true){sOqSMVznLX = false;}
      if(kueZNcfNik == true){kueZNcfNik = false;}
      if(QaBbYpgIuI == true){QaBbYpgIuI = false;}
      if(smptZmHFdc == true){smptZmHFdc = false;}
      if(mZWJjOHIeF == true){mZWJjOHIeF = false;}
      if(DrAOXSMPtV == true){DrAOXSMPtV = false;}
      if(npsCdxFjAa == true){npsCdxFjAa = false;}
      if(VaiGyqDrqJ == true){VaiGyqDrqJ = false;}
      if(iYdoFAmaWH == true){iYdoFAmaWH = false;}
      if(ZrKHnwgUel == true){ZrKHnwgUel = false;}
      if(JWHEjcJsQf == true){JWHEjcJsQf = false;}
      if(OUXjmPLDxc == true){OUXjmPLDxc = false;}
      if(KdMrAcPbRB == true){KdMrAcPbRB = false;}
      if(KiMFALQZEc == true){KiMFALQZEc = false;}
      if(qsJqrFTZTX == true){qsJqrFTZTX = false;}
      if(jcWBbeJODG == true){jcWBbeJODG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FNQBMRFGYT
{ 
  void tYODmhmkBK()
  { 
      bool thgCQXlBei = false;
      bool NixGywsWAF = false;
      bool ZkYAySeeXY = false;
      bool DmlhWEkrkW = false;
      bool kQxEyYoyql = false;
      bool wCsrUJJgDx = false;
      bool rGdGfawPjt = false;
      bool KBlcUJnTCZ = false;
      bool dgnkbAstNN = false;
      bool tDomddlpXW = false;
      bool bZOxauQQXK = false;
      bool VpdcTLSref = false;
      bool gCBVzHMyyp = false;
      bool WxweyDRpJf = false;
      bool icWCrEZLSS = false;
      bool LtKrpZXsyT = false;
      bool iRRgmXsyeQ = false;
      bool tciywDezdu = false;
      bool gAefeclDoX = false;
      bool eYrpxRLpOT = false;
      string WICsQwgsDb;
      string gSLcCAlckn;
      string bVNzzbUpCc;
      string LJKUGlKJgT;
      string NtlDKZVOOI;
      string EnOXnBtCto;
      string appaQWIqVQ;
      string pcwQZhjJoY;
      string GGbtXWulfF;
      string qIPrrWDKmn;
      string RdrxSbrxxG;
      string RjNUiUOwCs;
      string aVKQYhMDYC;
      string dYWAHbOdaw;
      string eynZmHutJW;
      string IHHtMuTaXk;
      string OnXtbrNMMG;
      string GkUFOcgjcR;
      string mStBtWRbnM;
      string HmFphpZtxu;
      if(WICsQwgsDb == RdrxSbrxxG){thgCQXlBei = true;}
      else if(RdrxSbrxxG == WICsQwgsDb){bZOxauQQXK = true;}
      if(gSLcCAlckn == RjNUiUOwCs){NixGywsWAF = true;}
      else if(RjNUiUOwCs == gSLcCAlckn){VpdcTLSref = true;}
      if(bVNzzbUpCc == aVKQYhMDYC){ZkYAySeeXY = true;}
      else if(aVKQYhMDYC == bVNzzbUpCc){gCBVzHMyyp = true;}
      if(LJKUGlKJgT == dYWAHbOdaw){DmlhWEkrkW = true;}
      else if(dYWAHbOdaw == LJKUGlKJgT){WxweyDRpJf = true;}
      if(NtlDKZVOOI == eynZmHutJW){kQxEyYoyql = true;}
      else if(eynZmHutJW == NtlDKZVOOI){icWCrEZLSS = true;}
      if(EnOXnBtCto == IHHtMuTaXk){wCsrUJJgDx = true;}
      else if(IHHtMuTaXk == EnOXnBtCto){LtKrpZXsyT = true;}
      if(appaQWIqVQ == OnXtbrNMMG){rGdGfawPjt = true;}
      else if(OnXtbrNMMG == appaQWIqVQ){iRRgmXsyeQ = true;}
      if(pcwQZhjJoY == GkUFOcgjcR){KBlcUJnTCZ = true;}
      if(GGbtXWulfF == mStBtWRbnM){dgnkbAstNN = true;}
      if(qIPrrWDKmn == HmFphpZtxu){tDomddlpXW = true;}
      while(GkUFOcgjcR == pcwQZhjJoY){tciywDezdu = true;}
      while(mStBtWRbnM == mStBtWRbnM){gAefeclDoX = true;}
      while(HmFphpZtxu == HmFphpZtxu){eYrpxRLpOT = true;}
      if(thgCQXlBei == true){thgCQXlBei = false;}
      if(NixGywsWAF == true){NixGywsWAF = false;}
      if(ZkYAySeeXY == true){ZkYAySeeXY = false;}
      if(DmlhWEkrkW == true){DmlhWEkrkW = false;}
      if(kQxEyYoyql == true){kQxEyYoyql = false;}
      if(wCsrUJJgDx == true){wCsrUJJgDx = false;}
      if(rGdGfawPjt == true){rGdGfawPjt = false;}
      if(KBlcUJnTCZ == true){KBlcUJnTCZ = false;}
      if(dgnkbAstNN == true){dgnkbAstNN = false;}
      if(tDomddlpXW == true){tDomddlpXW = false;}
      if(bZOxauQQXK == true){bZOxauQQXK = false;}
      if(VpdcTLSref == true){VpdcTLSref = false;}
      if(gCBVzHMyyp == true){gCBVzHMyyp = false;}
      if(WxweyDRpJf == true){WxweyDRpJf = false;}
      if(icWCrEZLSS == true){icWCrEZLSS = false;}
      if(LtKrpZXsyT == true){LtKrpZXsyT = false;}
      if(iRRgmXsyeQ == true){iRRgmXsyeQ = false;}
      if(tciywDezdu == true){tciywDezdu = false;}
      if(gAefeclDoX == true){gAefeclDoX = false;}
      if(eYrpxRLpOT == true){eYrpxRLpOT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YTCRTFCTFB
{ 
  void ExdsNSJlKg()
  { 
      bool pbEAMfUYMc = false;
      bool jeRhatuIDy = false;
      bool sIErJoqrQK = false;
      bool uykOVknqnT = false;
      bool aacQUjozNm = false;
      bool qpwgKgXLpX = false;
      bool obIChltDMp = false;
      bool GDTiXRenWZ = false;
      bool zqedSEBDDn = false;
      bool MbAQeySahi = false;
      bool plmXgmWNJr = false;
      bool BjnPXyxeic = false;
      bool jpzXcdCDEZ = false;
      bool zEFnjNEGxf = false;
      bool hntKmbnksg = false;
      bool BmqFzzlOtD = false;
      bool jTJisweAfJ = false;
      bool tphDuuunkB = false;
      bool oRKXYLNznj = false;
      bool boLtuOeKRp = false;
      string BkFwosgepD;
      string YEjVGerZat;
      string sWHwfCRHNW;
      string GwlYsRzGyW;
      string ggJbDEAbjH;
      string TeVXFddIPm;
      string bZRTxcRLcn;
      string elbDNMNesb;
      string BoXGCbZOSO;
      string nppKuHOoea;
      string loyubhDRKr;
      string QyPmklBLRU;
      string CDrOAnuQIG;
      string yXzRoLpcdT;
      string YHEaxoaCZI;
      string FCWJXixitn;
      string llIEtsyyyY;
      string uYhywtyRRL;
      string NrqAAuAptF;
      string OGhoglzAfD;
      if(BkFwosgepD == loyubhDRKr){pbEAMfUYMc = true;}
      else if(loyubhDRKr == BkFwosgepD){plmXgmWNJr = true;}
      if(YEjVGerZat == QyPmklBLRU){jeRhatuIDy = true;}
      else if(QyPmklBLRU == YEjVGerZat){BjnPXyxeic = true;}
      if(sWHwfCRHNW == CDrOAnuQIG){sIErJoqrQK = true;}
      else if(CDrOAnuQIG == sWHwfCRHNW){jpzXcdCDEZ = true;}
      if(GwlYsRzGyW == yXzRoLpcdT){uykOVknqnT = true;}
      else if(yXzRoLpcdT == GwlYsRzGyW){zEFnjNEGxf = true;}
      if(ggJbDEAbjH == YHEaxoaCZI){aacQUjozNm = true;}
      else if(YHEaxoaCZI == ggJbDEAbjH){hntKmbnksg = true;}
      if(TeVXFddIPm == FCWJXixitn){qpwgKgXLpX = true;}
      else if(FCWJXixitn == TeVXFddIPm){BmqFzzlOtD = true;}
      if(bZRTxcRLcn == llIEtsyyyY){obIChltDMp = true;}
      else if(llIEtsyyyY == bZRTxcRLcn){jTJisweAfJ = true;}
      if(elbDNMNesb == uYhywtyRRL){GDTiXRenWZ = true;}
      if(BoXGCbZOSO == NrqAAuAptF){zqedSEBDDn = true;}
      if(nppKuHOoea == OGhoglzAfD){MbAQeySahi = true;}
      while(uYhywtyRRL == elbDNMNesb){tphDuuunkB = true;}
      while(NrqAAuAptF == NrqAAuAptF){oRKXYLNznj = true;}
      while(OGhoglzAfD == OGhoglzAfD){boLtuOeKRp = true;}
      if(pbEAMfUYMc == true){pbEAMfUYMc = false;}
      if(jeRhatuIDy == true){jeRhatuIDy = false;}
      if(sIErJoqrQK == true){sIErJoqrQK = false;}
      if(uykOVknqnT == true){uykOVknqnT = false;}
      if(aacQUjozNm == true){aacQUjozNm = false;}
      if(qpwgKgXLpX == true){qpwgKgXLpX = false;}
      if(obIChltDMp == true){obIChltDMp = false;}
      if(GDTiXRenWZ == true){GDTiXRenWZ = false;}
      if(zqedSEBDDn == true){zqedSEBDDn = false;}
      if(MbAQeySahi == true){MbAQeySahi = false;}
      if(plmXgmWNJr == true){plmXgmWNJr = false;}
      if(BjnPXyxeic == true){BjnPXyxeic = false;}
      if(jpzXcdCDEZ == true){jpzXcdCDEZ = false;}
      if(zEFnjNEGxf == true){zEFnjNEGxf = false;}
      if(hntKmbnksg == true){hntKmbnksg = false;}
      if(BmqFzzlOtD == true){BmqFzzlOtD = false;}
      if(jTJisweAfJ == true){jTJisweAfJ = false;}
      if(tphDuuunkB == true){tphDuuunkB = false;}
      if(oRKXYLNznj == true){oRKXYLNznj = false;}
      if(boLtuOeKRp == true){boLtuOeKRp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HTSHIYYHMV
{ 
  void ZoIfjnWnYF()
  { 
      bool njqVEhHMNi = false;
      bool bdpPHijNRq = false;
      bool grlVwePALG = false;
      bool TCNiRQzQJS = false;
      bool WIEUJcRxmG = false;
      bool bonduuyUZY = false;
      bool SGAHPYQGxq = false;
      bool iSEzUXnQLS = false;
      bool MRNEedOjnV = false;
      bool RdqjzQIxFk = false;
      bool MKzuXIkoJW = false;
      bool HgIGLAswbl = false;
      bool JgSbZEbTzE = false;
      bool PpLaGCSRfW = false;
      bool rZZQNjVjYy = false;
      bool WMUSafqWVT = false;
      bool fRoFHQVgzJ = false;
      bool haPFsjGCNo = false;
      bool iruBgCVrAa = false;
      bool KuwMpakUIw = false;
      string qTJOsnITEY;
      string zHHUGzJgaW;
      string fpeowPsqdJ;
      string GkTlPuwsZh;
      string nsazWHItjn;
      string epYOpAnTRd;
      string uRouRNnVEK;
      string DPHrhlOfSo;
      string GyHodQLFuP;
      string GbaumVEegI;
      string SmpYkOhgfE;
      string kIBcWwKARA;
      string CiZoDboLEM;
      string hiyKVTIhEP;
      string heZqdyayYq;
      string LDNfGjMBUI;
      string ZWbSVCKpGD;
      string mcwBSWIiKF;
      string AqlNBdUREk;
      string GHMupLDGUb;
      if(qTJOsnITEY == SmpYkOhgfE){njqVEhHMNi = true;}
      else if(SmpYkOhgfE == qTJOsnITEY){MKzuXIkoJW = true;}
      if(zHHUGzJgaW == kIBcWwKARA){bdpPHijNRq = true;}
      else if(kIBcWwKARA == zHHUGzJgaW){HgIGLAswbl = true;}
      if(fpeowPsqdJ == CiZoDboLEM){grlVwePALG = true;}
      else if(CiZoDboLEM == fpeowPsqdJ){JgSbZEbTzE = true;}
      if(GkTlPuwsZh == hiyKVTIhEP){TCNiRQzQJS = true;}
      else if(hiyKVTIhEP == GkTlPuwsZh){PpLaGCSRfW = true;}
      if(nsazWHItjn == heZqdyayYq){WIEUJcRxmG = true;}
      else if(heZqdyayYq == nsazWHItjn){rZZQNjVjYy = true;}
      if(epYOpAnTRd == LDNfGjMBUI){bonduuyUZY = true;}
      else if(LDNfGjMBUI == epYOpAnTRd){WMUSafqWVT = true;}
      if(uRouRNnVEK == ZWbSVCKpGD){SGAHPYQGxq = true;}
      else if(ZWbSVCKpGD == uRouRNnVEK){fRoFHQVgzJ = true;}
      if(DPHrhlOfSo == mcwBSWIiKF){iSEzUXnQLS = true;}
      if(GyHodQLFuP == AqlNBdUREk){MRNEedOjnV = true;}
      if(GbaumVEegI == GHMupLDGUb){RdqjzQIxFk = true;}
      while(mcwBSWIiKF == DPHrhlOfSo){haPFsjGCNo = true;}
      while(AqlNBdUREk == AqlNBdUREk){iruBgCVrAa = true;}
      while(GHMupLDGUb == GHMupLDGUb){KuwMpakUIw = true;}
      if(njqVEhHMNi == true){njqVEhHMNi = false;}
      if(bdpPHijNRq == true){bdpPHijNRq = false;}
      if(grlVwePALG == true){grlVwePALG = false;}
      if(TCNiRQzQJS == true){TCNiRQzQJS = false;}
      if(WIEUJcRxmG == true){WIEUJcRxmG = false;}
      if(bonduuyUZY == true){bonduuyUZY = false;}
      if(SGAHPYQGxq == true){SGAHPYQGxq = false;}
      if(iSEzUXnQLS == true){iSEzUXnQLS = false;}
      if(MRNEedOjnV == true){MRNEedOjnV = false;}
      if(RdqjzQIxFk == true){RdqjzQIxFk = false;}
      if(MKzuXIkoJW == true){MKzuXIkoJW = false;}
      if(HgIGLAswbl == true){HgIGLAswbl = false;}
      if(JgSbZEbTzE == true){JgSbZEbTzE = false;}
      if(PpLaGCSRfW == true){PpLaGCSRfW = false;}
      if(rZZQNjVjYy == true){rZZQNjVjYy = false;}
      if(WMUSafqWVT == true){WMUSafqWVT = false;}
      if(fRoFHQVgzJ == true){fRoFHQVgzJ = false;}
      if(haPFsjGCNo == true){haPFsjGCNo = false;}
      if(iruBgCVrAa == true){iruBgCVrAa = false;}
      if(KuwMpakUIw == true){KuwMpakUIw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VWJKMSMAEL
{ 
  void NpagrXaZkT()
  { 
      bool WPlprmoZMc = false;
      bool HpIhQZyTJB = false;
      bool PlpMCOeJcw = false;
      bool XwRZhUpmHw = false;
      bool zxstewsWMm = false;
      bool mmuQXjZZmd = false;
      bool HewPFKYizu = false;
      bool iKMMCRruhF = false;
      bool UHxpJjBABy = false;
      bool uQzcoTBcoU = false;
      bool XKXQEbahOG = false;
      bool qergIAgGFU = false;
      bool IXgBASLjXh = false;
      bool QOGMgKjfkh = false;
      bool JTktGQYSTn = false;
      bool mtXTLAcVQl = false;
      bool QpJgpbXezy = false;
      bool PAUWKolluj = false;
      bool srPiuVqlBg = false;
      bool gNPzRSJEEd = false;
      string JHSLbCKPjS;
      string tBZdTIZFWh;
      string NWXYMughCu;
      string ZiDXnqTeNR;
      string bFLgaHSziG;
      string McfFMliszf;
      string VbMorKyCpb;
      string ouqEGILpyE;
      string cgzuhxDyLB;
      string IZfhwzrWoQ;
      string JQJGQRkbzE;
      string asutCncQGt;
      string HApnTPOJHG;
      string PnAguMXrdP;
      string MayGaOdkfI;
      string WbQtJJZVmB;
      string CbTsomrNyp;
      string PjlphfBiME;
      string kcczinXGXl;
      string mBFcMkHFRm;
      if(JHSLbCKPjS == JQJGQRkbzE){WPlprmoZMc = true;}
      else if(JQJGQRkbzE == JHSLbCKPjS){XKXQEbahOG = true;}
      if(tBZdTIZFWh == asutCncQGt){HpIhQZyTJB = true;}
      else if(asutCncQGt == tBZdTIZFWh){qergIAgGFU = true;}
      if(NWXYMughCu == HApnTPOJHG){PlpMCOeJcw = true;}
      else if(HApnTPOJHG == NWXYMughCu){IXgBASLjXh = true;}
      if(ZiDXnqTeNR == PnAguMXrdP){XwRZhUpmHw = true;}
      else if(PnAguMXrdP == ZiDXnqTeNR){QOGMgKjfkh = true;}
      if(bFLgaHSziG == MayGaOdkfI){zxstewsWMm = true;}
      else if(MayGaOdkfI == bFLgaHSziG){JTktGQYSTn = true;}
      if(McfFMliszf == WbQtJJZVmB){mmuQXjZZmd = true;}
      else if(WbQtJJZVmB == McfFMliszf){mtXTLAcVQl = true;}
      if(VbMorKyCpb == CbTsomrNyp){HewPFKYizu = true;}
      else if(CbTsomrNyp == VbMorKyCpb){QpJgpbXezy = true;}
      if(ouqEGILpyE == PjlphfBiME){iKMMCRruhF = true;}
      if(cgzuhxDyLB == kcczinXGXl){UHxpJjBABy = true;}
      if(IZfhwzrWoQ == mBFcMkHFRm){uQzcoTBcoU = true;}
      while(PjlphfBiME == ouqEGILpyE){PAUWKolluj = true;}
      while(kcczinXGXl == kcczinXGXl){srPiuVqlBg = true;}
      while(mBFcMkHFRm == mBFcMkHFRm){gNPzRSJEEd = true;}
      if(WPlprmoZMc == true){WPlprmoZMc = false;}
      if(HpIhQZyTJB == true){HpIhQZyTJB = false;}
      if(PlpMCOeJcw == true){PlpMCOeJcw = false;}
      if(XwRZhUpmHw == true){XwRZhUpmHw = false;}
      if(zxstewsWMm == true){zxstewsWMm = false;}
      if(mmuQXjZZmd == true){mmuQXjZZmd = false;}
      if(HewPFKYizu == true){HewPFKYizu = false;}
      if(iKMMCRruhF == true){iKMMCRruhF = false;}
      if(UHxpJjBABy == true){UHxpJjBABy = false;}
      if(uQzcoTBcoU == true){uQzcoTBcoU = false;}
      if(XKXQEbahOG == true){XKXQEbahOG = false;}
      if(qergIAgGFU == true){qergIAgGFU = false;}
      if(IXgBASLjXh == true){IXgBASLjXh = false;}
      if(QOGMgKjfkh == true){QOGMgKjfkh = false;}
      if(JTktGQYSTn == true){JTktGQYSTn = false;}
      if(mtXTLAcVQl == true){mtXTLAcVQl = false;}
      if(QpJgpbXezy == true){QpJgpbXezy = false;}
      if(PAUWKolluj == true){PAUWKolluj = false;}
      if(srPiuVqlBg == true){srPiuVqlBg = false;}
      if(gNPzRSJEEd == true){gNPzRSJEEd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQWFSRPTZG
{ 
  void kgmatVJyRS()
  { 
      bool ojzkzbuYSR = false;
      bool EDXfpIVEUn = false;
      bool MyrwAeuxdJ = false;
      bool UKHBGtwaWb = false;
      bool jWuUXSpCYb = false;
      bool nfarxpqCkU = false;
      bool fytIxsuWYu = false;
      bool MthrDoCXYg = false;
      bool nrXCVojPEP = false;
      bool CspCwlclXd = false;
      bool WTccPsyhnH = false;
      bool mTdEfmZrmH = false;
      bool JfRIrSEewR = false;
      bool MQztKUPulb = false;
      bool qCaxciPlWI = false;
      bool MkyPUpBTjx = false;
      bool oSlWtWUisK = false;
      bool XdFLQHFTfJ = false;
      bool CSInEbRiZU = false;
      bool TwKomXPDCF = false;
      string SXtiiUqBXW;
      string ESjVmxlcoU;
      string cwKEsJPSKA;
      string MnntgbwcQp;
      string RqRJERSDjO;
      string iPnkpWNppZ;
      string FXpXKQdpoK;
      string AILzDldAzb;
      string pMiwQxzCDK;
      string OGmqksAtzn;
      string mcNYNaDohE;
      string rMpNirntGM;
      string QaldwtUUOJ;
      string kjAKnMyKhp;
      string sKUySBPYHr;
      string FGnlXLqjbT;
      string FiZYSIMfZV;
      string sdLPTFGmLu;
      string dwMVDeuNmc;
      string VOhOkJjufJ;
      if(SXtiiUqBXW == mcNYNaDohE){ojzkzbuYSR = true;}
      else if(mcNYNaDohE == SXtiiUqBXW){WTccPsyhnH = true;}
      if(ESjVmxlcoU == rMpNirntGM){EDXfpIVEUn = true;}
      else if(rMpNirntGM == ESjVmxlcoU){mTdEfmZrmH = true;}
      if(cwKEsJPSKA == QaldwtUUOJ){MyrwAeuxdJ = true;}
      else if(QaldwtUUOJ == cwKEsJPSKA){JfRIrSEewR = true;}
      if(MnntgbwcQp == kjAKnMyKhp){UKHBGtwaWb = true;}
      else if(kjAKnMyKhp == MnntgbwcQp){MQztKUPulb = true;}
      if(RqRJERSDjO == sKUySBPYHr){jWuUXSpCYb = true;}
      else if(sKUySBPYHr == RqRJERSDjO){qCaxciPlWI = true;}
      if(iPnkpWNppZ == FGnlXLqjbT){nfarxpqCkU = true;}
      else if(FGnlXLqjbT == iPnkpWNppZ){MkyPUpBTjx = true;}
      if(FXpXKQdpoK == FiZYSIMfZV){fytIxsuWYu = true;}
      else if(FiZYSIMfZV == FXpXKQdpoK){oSlWtWUisK = true;}
      if(AILzDldAzb == sdLPTFGmLu){MthrDoCXYg = true;}
      if(pMiwQxzCDK == dwMVDeuNmc){nrXCVojPEP = true;}
      if(OGmqksAtzn == VOhOkJjufJ){CspCwlclXd = true;}
      while(sdLPTFGmLu == AILzDldAzb){XdFLQHFTfJ = true;}
      while(dwMVDeuNmc == dwMVDeuNmc){CSInEbRiZU = true;}
      while(VOhOkJjufJ == VOhOkJjufJ){TwKomXPDCF = true;}
      if(ojzkzbuYSR == true){ojzkzbuYSR = false;}
      if(EDXfpIVEUn == true){EDXfpIVEUn = false;}
      if(MyrwAeuxdJ == true){MyrwAeuxdJ = false;}
      if(UKHBGtwaWb == true){UKHBGtwaWb = false;}
      if(jWuUXSpCYb == true){jWuUXSpCYb = false;}
      if(nfarxpqCkU == true){nfarxpqCkU = false;}
      if(fytIxsuWYu == true){fytIxsuWYu = false;}
      if(MthrDoCXYg == true){MthrDoCXYg = false;}
      if(nrXCVojPEP == true){nrXCVojPEP = false;}
      if(CspCwlclXd == true){CspCwlclXd = false;}
      if(WTccPsyhnH == true){WTccPsyhnH = false;}
      if(mTdEfmZrmH == true){mTdEfmZrmH = false;}
      if(JfRIrSEewR == true){JfRIrSEewR = false;}
      if(MQztKUPulb == true){MQztKUPulb = false;}
      if(qCaxciPlWI == true){qCaxciPlWI = false;}
      if(MkyPUpBTjx == true){MkyPUpBTjx = false;}
      if(oSlWtWUisK == true){oSlWtWUisK = false;}
      if(XdFLQHFTfJ == true){XdFLQHFTfJ = false;}
      if(CSInEbRiZU == true){CSInEbRiZU = false;}
      if(TwKomXPDCF == true){TwKomXPDCF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VSTVVAFPMH
{ 
  void PalQDxjiol()
  { 
      bool OsDRKpiXKP = false;
      bool allkDlhJoO = false;
      bool hYdXwPXCYO = false;
      bool RQiXjwSsRT = false;
      bool RtKYfwljwg = false;
      bool TMbrSpOeUu = false;
      bool SfzuxJCOBG = false;
      bool SoqVwmNFrA = false;
      bool cmFquEoqEs = false;
      bool hmXWAluPaV = false;
      bool sXipNdUFwf = false;
      bool bJlURfZHAr = false;
      bool ULKHYfRUUJ = false;
      bool qydWGFDPcQ = false;
      bool jitXRXACET = false;
      bool LnOhAgNbRh = false;
      bool MAklocfPOM = false;
      bool cKdjIlRlpA = false;
      bool eOPBxCjuVY = false;
      bool qaxuDjyHin = false;
      string cSWAaWxqtB;
      string IrlMtxWbUG;
      string pTmRlgZBGi;
      string rmhzwiapgU;
      string dTxzXQdCDR;
      string tuOWYIfEOs;
      string xukKJVJmPL;
      string WfuAcVWmtU;
      string CXxnowXLZn;
      string CVbmXhiloB;
      string GqmrtNAOtC;
      string krKsqYywUN;
      string xyNaIBEHbt;
      string mjyrOLkFsb;
      string uJQWCJLhwz;
      string jlRbDHcLjs;
      string IsmzPBtRee;
      string nsDsRngqYy;
      string pWKcKBSVnG;
      string hYVATCWQHB;
      if(cSWAaWxqtB == GqmrtNAOtC){OsDRKpiXKP = true;}
      else if(GqmrtNAOtC == cSWAaWxqtB){sXipNdUFwf = true;}
      if(IrlMtxWbUG == krKsqYywUN){allkDlhJoO = true;}
      else if(krKsqYywUN == IrlMtxWbUG){bJlURfZHAr = true;}
      if(pTmRlgZBGi == xyNaIBEHbt){hYdXwPXCYO = true;}
      else if(xyNaIBEHbt == pTmRlgZBGi){ULKHYfRUUJ = true;}
      if(rmhzwiapgU == mjyrOLkFsb){RQiXjwSsRT = true;}
      else if(mjyrOLkFsb == rmhzwiapgU){qydWGFDPcQ = true;}
      if(dTxzXQdCDR == uJQWCJLhwz){RtKYfwljwg = true;}
      else if(uJQWCJLhwz == dTxzXQdCDR){jitXRXACET = true;}
      if(tuOWYIfEOs == jlRbDHcLjs){TMbrSpOeUu = true;}
      else if(jlRbDHcLjs == tuOWYIfEOs){LnOhAgNbRh = true;}
      if(xukKJVJmPL == IsmzPBtRee){SfzuxJCOBG = true;}
      else if(IsmzPBtRee == xukKJVJmPL){MAklocfPOM = true;}
      if(WfuAcVWmtU == nsDsRngqYy){SoqVwmNFrA = true;}
      if(CXxnowXLZn == pWKcKBSVnG){cmFquEoqEs = true;}
      if(CVbmXhiloB == hYVATCWQHB){hmXWAluPaV = true;}
      while(nsDsRngqYy == WfuAcVWmtU){cKdjIlRlpA = true;}
      while(pWKcKBSVnG == pWKcKBSVnG){eOPBxCjuVY = true;}
      while(hYVATCWQHB == hYVATCWQHB){qaxuDjyHin = true;}
      if(OsDRKpiXKP == true){OsDRKpiXKP = false;}
      if(allkDlhJoO == true){allkDlhJoO = false;}
      if(hYdXwPXCYO == true){hYdXwPXCYO = false;}
      if(RQiXjwSsRT == true){RQiXjwSsRT = false;}
      if(RtKYfwljwg == true){RtKYfwljwg = false;}
      if(TMbrSpOeUu == true){TMbrSpOeUu = false;}
      if(SfzuxJCOBG == true){SfzuxJCOBG = false;}
      if(SoqVwmNFrA == true){SoqVwmNFrA = false;}
      if(cmFquEoqEs == true){cmFquEoqEs = false;}
      if(hmXWAluPaV == true){hmXWAluPaV = false;}
      if(sXipNdUFwf == true){sXipNdUFwf = false;}
      if(bJlURfZHAr == true){bJlURfZHAr = false;}
      if(ULKHYfRUUJ == true){ULKHYfRUUJ = false;}
      if(qydWGFDPcQ == true){qydWGFDPcQ = false;}
      if(jitXRXACET == true){jitXRXACET = false;}
      if(LnOhAgNbRh == true){LnOhAgNbRh = false;}
      if(MAklocfPOM == true){MAklocfPOM = false;}
      if(cKdjIlRlpA == true){cKdjIlRlpA = false;}
      if(eOPBxCjuVY == true){eOPBxCjuVY = false;}
      if(qaxuDjyHin == true){qaxuDjyHin = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FKKIXTUAWJ
{ 
  void TrjaXEQIVE()
  { 
      bool QPcsijmhng = false;
      bool EnTGorANPI = false;
      bool NaxdDQKfab = false;
      bool SkJYiXrEkk = false;
      bool FdGpTaPrbl = false;
      bool LJVmLoSzoS = false;
      bool ZHHMOSdtXR = false;
      bool AubeDjTGJc = false;
      bool BSDoPJPVNs = false;
      bool ErOSLyWtbB = false;
      bool xUTJkPgqjb = false;
      bool ULoMQGDSwF = false;
      bool DHgdNIgJTE = false;
      bool NZeIfgytDz = false;
      bool bXlkXrCCCE = false;
      bool tDyVyonpwc = false;
      bool iXXeNuggfj = false;
      bool IIPwceVuFU = false;
      bool FdHPJJbIKp = false;
      bool rHyZQEAGWc = false;
      string FmDZYqTQSk;
      string MysaBHqUzf;
      string WmqXCnTKaJ;
      string VWkMwegGXJ;
      string NRxqJhfyOd;
      string AEcQjSweWj;
      string XIoIPoMgdV;
      string akxpSFpAOU;
      string IVwxIQsTcd;
      string iBinkEbnbT;
      string UzTrCPGmyd;
      string buQCbBMrzy;
      string wsEAmYBJEN;
      string cBYuAJBDts;
      string JGVyBmkfLi;
      string rjocWatSFc;
      string NxijBaWUCS;
      string zIxGnpWGzz;
      string nVxUUrMuXY;
      string OiyReMWkwZ;
      if(FmDZYqTQSk == UzTrCPGmyd){QPcsijmhng = true;}
      else if(UzTrCPGmyd == FmDZYqTQSk){xUTJkPgqjb = true;}
      if(MysaBHqUzf == buQCbBMrzy){EnTGorANPI = true;}
      else if(buQCbBMrzy == MysaBHqUzf){ULoMQGDSwF = true;}
      if(WmqXCnTKaJ == wsEAmYBJEN){NaxdDQKfab = true;}
      else if(wsEAmYBJEN == WmqXCnTKaJ){DHgdNIgJTE = true;}
      if(VWkMwegGXJ == cBYuAJBDts){SkJYiXrEkk = true;}
      else if(cBYuAJBDts == VWkMwegGXJ){NZeIfgytDz = true;}
      if(NRxqJhfyOd == JGVyBmkfLi){FdGpTaPrbl = true;}
      else if(JGVyBmkfLi == NRxqJhfyOd){bXlkXrCCCE = true;}
      if(AEcQjSweWj == rjocWatSFc){LJVmLoSzoS = true;}
      else if(rjocWatSFc == AEcQjSweWj){tDyVyonpwc = true;}
      if(XIoIPoMgdV == NxijBaWUCS){ZHHMOSdtXR = true;}
      else if(NxijBaWUCS == XIoIPoMgdV){iXXeNuggfj = true;}
      if(akxpSFpAOU == zIxGnpWGzz){AubeDjTGJc = true;}
      if(IVwxIQsTcd == nVxUUrMuXY){BSDoPJPVNs = true;}
      if(iBinkEbnbT == OiyReMWkwZ){ErOSLyWtbB = true;}
      while(zIxGnpWGzz == akxpSFpAOU){IIPwceVuFU = true;}
      while(nVxUUrMuXY == nVxUUrMuXY){FdHPJJbIKp = true;}
      while(OiyReMWkwZ == OiyReMWkwZ){rHyZQEAGWc = true;}
      if(QPcsijmhng == true){QPcsijmhng = false;}
      if(EnTGorANPI == true){EnTGorANPI = false;}
      if(NaxdDQKfab == true){NaxdDQKfab = false;}
      if(SkJYiXrEkk == true){SkJYiXrEkk = false;}
      if(FdGpTaPrbl == true){FdGpTaPrbl = false;}
      if(LJVmLoSzoS == true){LJVmLoSzoS = false;}
      if(ZHHMOSdtXR == true){ZHHMOSdtXR = false;}
      if(AubeDjTGJc == true){AubeDjTGJc = false;}
      if(BSDoPJPVNs == true){BSDoPJPVNs = false;}
      if(ErOSLyWtbB == true){ErOSLyWtbB = false;}
      if(xUTJkPgqjb == true){xUTJkPgqjb = false;}
      if(ULoMQGDSwF == true){ULoMQGDSwF = false;}
      if(DHgdNIgJTE == true){DHgdNIgJTE = false;}
      if(NZeIfgytDz == true){NZeIfgytDz = false;}
      if(bXlkXrCCCE == true){bXlkXrCCCE = false;}
      if(tDyVyonpwc == true){tDyVyonpwc = false;}
      if(iXXeNuggfj == true){iXXeNuggfj = false;}
      if(IIPwceVuFU == true){IIPwceVuFU = false;}
      if(FdHPJJbIKp == true){FdHPJJbIKp = false;}
      if(rHyZQEAGWc == true){rHyZQEAGWc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZGDICFJCDD
{ 
  void aiusiJpqtP()
  { 
      bool wtLwxndWDZ = false;
      bool VkkkwKKRPr = false;
      bool ciPxyMdgNA = false;
      bool VWkCVcmQDb = false;
      bool nugKfCzYZb = false;
      bool pEHXbMeOyk = false;
      bool JwJDDzzhPS = false;
      bool WsOmEgCFQw = false;
      bool MEGkJQONaI = false;
      bool yYRRSqkdGg = false;
      bool CRJHFwpTSu = false;
      bool KYxCXEoYsm = false;
      bool jkGGTybwUM = false;
      bool uXyjstuzeM = false;
      bool ZuufyYaPsN = false;
      bool BMkSwRKDmG = false;
      bool UsyFzlaNIc = false;
      bool JpsfMopaHt = false;
      bool XLDGLimenb = false;
      bool jqLYrgxofL = false;
      string AyxJYdBzAO;
      string TtjgURSknG;
      string WBRqMVZydg;
      string ygXVlIDbwY;
      string hwnwmiewxB;
      string NHdwjzgGwC;
      string ECVSQlWOuL;
      string OqoPXZMVDd;
      string qdAbTpDakm;
      string bwetUfaVeB;
      string LQAllVSNXK;
      string lKCSLZCsyZ;
      string hwcIiSLuur;
      string zppCSZcNpx;
      string XpCaAQtMht;
      string cgXFSPmrDT;
      string KWSeKuUzAk;
      string woDABrsCHR;
      string XzMAPRSkjC;
      string mjKVmBWWQE;
      if(AyxJYdBzAO == LQAllVSNXK){wtLwxndWDZ = true;}
      else if(LQAllVSNXK == AyxJYdBzAO){CRJHFwpTSu = true;}
      if(TtjgURSknG == lKCSLZCsyZ){VkkkwKKRPr = true;}
      else if(lKCSLZCsyZ == TtjgURSknG){KYxCXEoYsm = true;}
      if(WBRqMVZydg == hwcIiSLuur){ciPxyMdgNA = true;}
      else if(hwcIiSLuur == WBRqMVZydg){jkGGTybwUM = true;}
      if(ygXVlIDbwY == zppCSZcNpx){VWkCVcmQDb = true;}
      else if(zppCSZcNpx == ygXVlIDbwY){uXyjstuzeM = true;}
      if(hwnwmiewxB == XpCaAQtMht){nugKfCzYZb = true;}
      else if(XpCaAQtMht == hwnwmiewxB){ZuufyYaPsN = true;}
      if(NHdwjzgGwC == cgXFSPmrDT){pEHXbMeOyk = true;}
      else if(cgXFSPmrDT == NHdwjzgGwC){BMkSwRKDmG = true;}
      if(ECVSQlWOuL == KWSeKuUzAk){JwJDDzzhPS = true;}
      else if(KWSeKuUzAk == ECVSQlWOuL){UsyFzlaNIc = true;}
      if(OqoPXZMVDd == woDABrsCHR){WsOmEgCFQw = true;}
      if(qdAbTpDakm == XzMAPRSkjC){MEGkJQONaI = true;}
      if(bwetUfaVeB == mjKVmBWWQE){yYRRSqkdGg = true;}
      while(woDABrsCHR == OqoPXZMVDd){JpsfMopaHt = true;}
      while(XzMAPRSkjC == XzMAPRSkjC){XLDGLimenb = true;}
      while(mjKVmBWWQE == mjKVmBWWQE){jqLYrgxofL = true;}
      if(wtLwxndWDZ == true){wtLwxndWDZ = false;}
      if(VkkkwKKRPr == true){VkkkwKKRPr = false;}
      if(ciPxyMdgNA == true){ciPxyMdgNA = false;}
      if(VWkCVcmQDb == true){VWkCVcmQDb = false;}
      if(nugKfCzYZb == true){nugKfCzYZb = false;}
      if(pEHXbMeOyk == true){pEHXbMeOyk = false;}
      if(JwJDDzzhPS == true){JwJDDzzhPS = false;}
      if(WsOmEgCFQw == true){WsOmEgCFQw = false;}
      if(MEGkJQONaI == true){MEGkJQONaI = false;}
      if(yYRRSqkdGg == true){yYRRSqkdGg = false;}
      if(CRJHFwpTSu == true){CRJHFwpTSu = false;}
      if(KYxCXEoYsm == true){KYxCXEoYsm = false;}
      if(jkGGTybwUM == true){jkGGTybwUM = false;}
      if(uXyjstuzeM == true){uXyjstuzeM = false;}
      if(ZuufyYaPsN == true){ZuufyYaPsN = false;}
      if(BMkSwRKDmG == true){BMkSwRKDmG = false;}
      if(UsyFzlaNIc == true){UsyFzlaNIc = false;}
      if(JpsfMopaHt == true){JpsfMopaHt = false;}
      if(XLDGLimenb == true){XLDGLimenb = false;}
      if(jqLYrgxofL == true){jqLYrgxofL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMTRSXCGDF
{ 
  void pRrTrGDaSd()
  { 
      bool AeRGfxIByT = false;
      bool csBQXUmqsn = false;
      bool JIpqBCiYZA = false;
      bool KefXpPNyeK = false;
      bool QJVmJPLczo = false;
      bool OYsAUrnZEd = false;
      bool NiaxJyNcZH = false;
      bool GoMhXAlChk = false;
      bool pGZklkkfDy = false;
      bool amsAwghXdL = false;
      bool ChCqhZMLcU = false;
      bool FlrTmHJpLX = false;
      bool NhZbfSwLlp = false;
      bool RNYVhIDhCM = false;
      bool YZCisouYNn = false;
      bool WrMFyUIaKP = false;
      bool cBYlCqMVle = false;
      bool Ebmzzmeqhq = false;
      bool XWxxTYBTXN = false;
      bool zcWmiXAQfB = false;
      string gToGtRFilj;
      string yUShfNqIdx;
      string dnIAKEGyRE;
      string karELkPEnp;
      string KIMsKcxeVm;
      string PfyVLsLnuo;
      string KGRhzWcOVt;
      string xlTmlUaOoh;
      string GbcenEcWrS;
      string ZaJzfEqetn;
      string AiIbodLKiq;
      string RwzMhidlst;
      string sFVDTWcUHh;
      string dwTBhWSBpK;
      string rSnBAcbwQw;
      string ZEkzttNFHS;
      string AqCAMVcxeK;
      string PcwiBaRUDq;
      string tfELHYLTHm;
      string JNsWJBPmne;
      if(gToGtRFilj == AiIbodLKiq){AeRGfxIByT = true;}
      else if(AiIbodLKiq == gToGtRFilj){ChCqhZMLcU = true;}
      if(yUShfNqIdx == RwzMhidlst){csBQXUmqsn = true;}
      else if(RwzMhidlst == yUShfNqIdx){FlrTmHJpLX = true;}
      if(dnIAKEGyRE == sFVDTWcUHh){JIpqBCiYZA = true;}
      else if(sFVDTWcUHh == dnIAKEGyRE){NhZbfSwLlp = true;}
      if(karELkPEnp == dwTBhWSBpK){KefXpPNyeK = true;}
      else if(dwTBhWSBpK == karELkPEnp){RNYVhIDhCM = true;}
      if(KIMsKcxeVm == rSnBAcbwQw){QJVmJPLczo = true;}
      else if(rSnBAcbwQw == KIMsKcxeVm){YZCisouYNn = true;}
      if(PfyVLsLnuo == ZEkzttNFHS){OYsAUrnZEd = true;}
      else if(ZEkzttNFHS == PfyVLsLnuo){WrMFyUIaKP = true;}
      if(KGRhzWcOVt == AqCAMVcxeK){NiaxJyNcZH = true;}
      else if(AqCAMVcxeK == KGRhzWcOVt){cBYlCqMVle = true;}
      if(xlTmlUaOoh == PcwiBaRUDq){GoMhXAlChk = true;}
      if(GbcenEcWrS == tfELHYLTHm){pGZklkkfDy = true;}
      if(ZaJzfEqetn == JNsWJBPmne){amsAwghXdL = true;}
      while(PcwiBaRUDq == xlTmlUaOoh){Ebmzzmeqhq = true;}
      while(tfELHYLTHm == tfELHYLTHm){XWxxTYBTXN = true;}
      while(JNsWJBPmne == JNsWJBPmne){zcWmiXAQfB = true;}
      if(AeRGfxIByT == true){AeRGfxIByT = false;}
      if(csBQXUmqsn == true){csBQXUmqsn = false;}
      if(JIpqBCiYZA == true){JIpqBCiYZA = false;}
      if(KefXpPNyeK == true){KefXpPNyeK = false;}
      if(QJVmJPLczo == true){QJVmJPLczo = false;}
      if(OYsAUrnZEd == true){OYsAUrnZEd = false;}
      if(NiaxJyNcZH == true){NiaxJyNcZH = false;}
      if(GoMhXAlChk == true){GoMhXAlChk = false;}
      if(pGZklkkfDy == true){pGZklkkfDy = false;}
      if(amsAwghXdL == true){amsAwghXdL = false;}
      if(ChCqhZMLcU == true){ChCqhZMLcU = false;}
      if(FlrTmHJpLX == true){FlrTmHJpLX = false;}
      if(NhZbfSwLlp == true){NhZbfSwLlp = false;}
      if(RNYVhIDhCM == true){RNYVhIDhCM = false;}
      if(YZCisouYNn == true){YZCisouYNn = false;}
      if(WrMFyUIaKP == true){WrMFyUIaKP = false;}
      if(cBYlCqMVle == true){cBYlCqMVle = false;}
      if(Ebmzzmeqhq == true){Ebmzzmeqhq = false;}
      if(XWxxTYBTXN == true){XWxxTYBTXN = false;}
      if(zcWmiXAQfB == true){zcWmiXAQfB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMMDGLMEGO
{ 
  void LMQCcZypPu()
  { 
      bool bDiirGYTIx = false;
      bool qIpgEWdnKb = false;
      bool nTPPDcPoth = false;
      bool ZbbhzleEmB = false;
      bool fmwhOITYLq = false;
      bool JthUhHmTeP = false;
      bool piZZXOgIhR = false;
      bool rYBIwBXhAu = false;
      bool IqdDYesHAq = false;
      bool zKYWLwMVKz = false;
      bool bKptzjrYXf = false;
      bool jFTjHzEVBr = false;
      bool VZIpSgzexA = false;
      bool nBWATyAjEo = false;
      bool lUiTHsqoOM = false;
      bool qqUSdCBzaR = false;
      bool jNaXrhhSQJ = false;
      bool yURMFBpoiY = false;
      bool oKPkIxgEWQ = false;
      bool wAIlEYsKbY = false;
      string YZrFJOEIoh;
      string qSgQjiImUy;
      string gWgKEJCTzZ;
      string qyTlyANtWk;
      string zDAtJrchTF;
      string TaPDsBshAz;
      string MkJOpsytRi;
      string UNQjycVlBM;
      string fUztFPhQsx;
      string HftXXNtlEP;
      string thPjjFKfEP;
      string eGfnSrkPIa;
      string KhBUboTrLk;
      string ijhkSyEOJz;
      string FCMcRAzFEf;
      string cdcdFLgtIt;
      string lRTSguYuVU;
      string mVFIUIUXDa;
      string pOnfIEGEeG;
      string QKGPNmhswV;
      if(YZrFJOEIoh == thPjjFKfEP){bDiirGYTIx = true;}
      else if(thPjjFKfEP == YZrFJOEIoh){bKptzjrYXf = true;}
      if(qSgQjiImUy == eGfnSrkPIa){qIpgEWdnKb = true;}
      else if(eGfnSrkPIa == qSgQjiImUy){jFTjHzEVBr = true;}
      if(gWgKEJCTzZ == KhBUboTrLk){nTPPDcPoth = true;}
      else if(KhBUboTrLk == gWgKEJCTzZ){VZIpSgzexA = true;}
      if(qyTlyANtWk == ijhkSyEOJz){ZbbhzleEmB = true;}
      else if(ijhkSyEOJz == qyTlyANtWk){nBWATyAjEo = true;}
      if(zDAtJrchTF == FCMcRAzFEf){fmwhOITYLq = true;}
      else if(FCMcRAzFEf == zDAtJrchTF){lUiTHsqoOM = true;}
      if(TaPDsBshAz == cdcdFLgtIt){JthUhHmTeP = true;}
      else if(cdcdFLgtIt == TaPDsBshAz){qqUSdCBzaR = true;}
      if(MkJOpsytRi == lRTSguYuVU){piZZXOgIhR = true;}
      else if(lRTSguYuVU == MkJOpsytRi){jNaXrhhSQJ = true;}
      if(UNQjycVlBM == mVFIUIUXDa){rYBIwBXhAu = true;}
      if(fUztFPhQsx == pOnfIEGEeG){IqdDYesHAq = true;}
      if(HftXXNtlEP == QKGPNmhswV){zKYWLwMVKz = true;}
      while(mVFIUIUXDa == UNQjycVlBM){yURMFBpoiY = true;}
      while(pOnfIEGEeG == pOnfIEGEeG){oKPkIxgEWQ = true;}
      while(QKGPNmhswV == QKGPNmhswV){wAIlEYsKbY = true;}
      if(bDiirGYTIx == true){bDiirGYTIx = false;}
      if(qIpgEWdnKb == true){qIpgEWdnKb = false;}
      if(nTPPDcPoth == true){nTPPDcPoth = false;}
      if(ZbbhzleEmB == true){ZbbhzleEmB = false;}
      if(fmwhOITYLq == true){fmwhOITYLq = false;}
      if(JthUhHmTeP == true){JthUhHmTeP = false;}
      if(piZZXOgIhR == true){piZZXOgIhR = false;}
      if(rYBIwBXhAu == true){rYBIwBXhAu = false;}
      if(IqdDYesHAq == true){IqdDYesHAq = false;}
      if(zKYWLwMVKz == true){zKYWLwMVKz = false;}
      if(bKptzjrYXf == true){bKptzjrYXf = false;}
      if(jFTjHzEVBr == true){jFTjHzEVBr = false;}
      if(VZIpSgzexA == true){VZIpSgzexA = false;}
      if(nBWATyAjEo == true){nBWATyAjEo = false;}
      if(lUiTHsqoOM == true){lUiTHsqoOM = false;}
      if(qqUSdCBzaR == true){qqUSdCBzaR = false;}
      if(jNaXrhhSQJ == true){jNaXrhhSQJ = false;}
      if(yURMFBpoiY == true){yURMFBpoiY = false;}
      if(oKPkIxgEWQ == true){oKPkIxgEWQ = false;}
      if(wAIlEYsKbY == true){wAIlEYsKbY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EAKJHPDQPN
{ 
  void PgjHKNLcty()
  { 
      bool FwBDQykMqn = false;
      bool YzdUngmiRr = false;
      bool ztrCGPRbzq = false;
      bool krwUkUWTPJ = false;
      bool yMuIohYWkH = false;
      bool clBXdLDzwA = false;
      bool fJMzCgDJiT = false;
      bool JTTHslyjMY = false;
      bool puqrOzqYqZ = false;
      bool QXWOcoAuFI = false;
      bool ePmQxISsdq = false;
      bool MTmXKkRTjD = false;
      bool peRIDlxFeD = false;
      bool lDdDsZHZuF = false;
      bool fxtANxkyDr = false;
      bool XfKCSAyeNL = false;
      bool LNOaEJoidk = false;
      bool crYeWrjQtG = false;
      bool AyBlfGrbjs = false;
      bool bcLitShTwE = false;
      string fPkaTkSiyC;
      string wDnEQzTPjP;
      string jXgYUZfMOU;
      string ToOpGkeqWm;
      string bpNPseOYTb;
      string aSadwHhMGt;
      string FFTciGoyxe;
      string UbrxmtJReo;
      string KGrlsAOjty;
      string CSjbhVVjgm;
      string oQaoHyZdqB;
      string xQgQiyNgjh;
      string qEEzcCrPOQ;
      string YZkrztfDeu;
      string ZjsrBkkSsi;
      string InAyukLbLF;
      string GKOZcXfoRo;
      string SJCnHHLLxq;
      string QYWfIjYlwO;
      string hDqZnPVSPc;
      if(fPkaTkSiyC == oQaoHyZdqB){FwBDQykMqn = true;}
      else if(oQaoHyZdqB == fPkaTkSiyC){ePmQxISsdq = true;}
      if(wDnEQzTPjP == xQgQiyNgjh){YzdUngmiRr = true;}
      else if(xQgQiyNgjh == wDnEQzTPjP){MTmXKkRTjD = true;}
      if(jXgYUZfMOU == qEEzcCrPOQ){ztrCGPRbzq = true;}
      else if(qEEzcCrPOQ == jXgYUZfMOU){peRIDlxFeD = true;}
      if(ToOpGkeqWm == YZkrztfDeu){krwUkUWTPJ = true;}
      else if(YZkrztfDeu == ToOpGkeqWm){lDdDsZHZuF = true;}
      if(bpNPseOYTb == ZjsrBkkSsi){yMuIohYWkH = true;}
      else if(ZjsrBkkSsi == bpNPseOYTb){fxtANxkyDr = true;}
      if(aSadwHhMGt == InAyukLbLF){clBXdLDzwA = true;}
      else if(InAyukLbLF == aSadwHhMGt){XfKCSAyeNL = true;}
      if(FFTciGoyxe == GKOZcXfoRo){fJMzCgDJiT = true;}
      else if(GKOZcXfoRo == FFTciGoyxe){LNOaEJoidk = true;}
      if(UbrxmtJReo == SJCnHHLLxq){JTTHslyjMY = true;}
      if(KGrlsAOjty == QYWfIjYlwO){puqrOzqYqZ = true;}
      if(CSjbhVVjgm == hDqZnPVSPc){QXWOcoAuFI = true;}
      while(SJCnHHLLxq == UbrxmtJReo){crYeWrjQtG = true;}
      while(QYWfIjYlwO == QYWfIjYlwO){AyBlfGrbjs = true;}
      while(hDqZnPVSPc == hDqZnPVSPc){bcLitShTwE = true;}
      if(FwBDQykMqn == true){FwBDQykMqn = false;}
      if(YzdUngmiRr == true){YzdUngmiRr = false;}
      if(ztrCGPRbzq == true){ztrCGPRbzq = false;}
      if(krwUkUWTPJ == true){krwUkUWTPJ = false;}
      if(yMuIohYWkH == true){yMuIohYWkH = false;}
      if(clBXdLDzwA == true){clBXdLDzwA = false;}
      if(fJMzCgDJiT == true){fJMzCgDJiT = false;}
      if(JTTHslyjMY == true){JTTHslyjMY = false;}
      if(puqrOzqYqZ == true){puqrOzqYqZ = false;}
      if(QXWOcoAuFI == true){QXWOcoAuFI = false;}
      if(ePmQxISsdq == true){ePmQxISsdq = false;}
      if(MTmXKkRTjD == true){MTmXKkRTjD = false;}
      if(peRIDlxFeD == true){peRIDlxFeD = false;}
      if(lDdDsZHZuF == true){lDdDsZHZuF = false;}
      if(fxtANxkyDr == true){fxtANxkyDr = false;}
      if(XfKCSAyeNL == true){XfKCSAyeNL = false;}
      if(LNOaEJoidk == true){LNOaEJoidk = false;}
      if(crYeWrjQtG == true){crYeWrjQtG = false;}
      if(AyBlfGrbjs == true){AyBlfGrbjs = false;}
      if(bcLitShTwE == true){bcLitShTwE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NWYZJMGJJB
{ 
  void pZMRmYtmVZ()
  { 
      bool slKKQccYcn = false;
      bool OZAQeXmzlP = false;
      bool daOTRJEKpB = false;
      bool ZNzREXUdbd = false;
      bool xUmipgEPaU = false;
      bool BGhULRXqsH = false;
      bool YSiaOAZhMG = false;
      bool CIXHSJnedj = false;
      bool EniUATedGm = false;
      bool AdkUEekLUo = false;
      bool HWDURrhZCB = false;
      bool crMICkjNat = false;
      bool VwaZFXXDDn = false;
      bool YbKnchjODI = false;
      bool lEaFJIQbST = false;
      bool tWkaTKudOt = false;
      bool UeWObBgYfT = false;
      bool AVKRIQUVQx = false;
      bool GujjsBqjUR = false;
      bool lGzJnGhMdH = false;
      string fDVepwJVLt;
      string SfYHtXMEJp;
      string RUPuIKcilP;
      string STIYyAghFb;
      string WphDAOVlpP;
      string yABglLnaVe;
      string SZiwayWzIt;
      string pdyhSalMtt;
      string nprVRSSbmm;
      string LFMZIwGlbB;
      string rWdwZUBSOK;
      string YbfbpbhMdI;
      string fuMVhjQYZV;
      string UAjsCRMwww;
      string RzMbNjYkif;
      string OsHTUxKHOp;
      string DcsrpXqmZY;
      string OkQhpfhjHx;
      string KfosGasPXF;
      string HFgGroGTko;
      if(fDVepwJVLt == rWdwZUBSOK){slKKQccYcn = true;}
      else if(rWdwZUBSOK == fDVepwJVLt){HWDURrhZCB = true;}
      if(SfYHtXMEJp == YbfbpbhMdI){OZAQeXmzlP = true;}
      else if(YbfbpbhMdI == SfYHtXMEJp){crMICkjNat = true;}
      if(RUPuIKcilP == fuMVhjQYZV){daOTRJEKpB = true;}
      else if(fuMVhjQYZV == RUPuIKcilP){VwaZFXXDDn = true;}
      if(STIYyAghFb == UAjsCRMwww){ZNzREXUdbd = true;}
      else if(UAjsCRMwww == STIYyAghFb){YbKnchjODI = true;}
      if(WphDAOVlpP == RzMbNjYkif){xUmipgEPaU = true;}
      else if(RzMbNjYkif == WphDAOVlpP){lEaFJIQbST = true;}
      if(yABglLnaVe == OsHTUxKHOp){BGhULRXqsH = true;}
      else if(OsHTUxKHOp == yABglLnaVe){tWkaTKudOt = true;}
      if(SZiwayWzIt == DcsrpXqmZY){YSiaOAZhMG = true;}
      else if(DcsrpXqmZY == SZiwayWzIt){UeWObBgYfT = true;}
      if(pdyhSalMtt == OkQhpfhjHx){CIXHSJnedj = true;}
      if(nprVRSSbmm == KfosGasPXF){EniUATedGm = true;}
      if(LFMZIwGlbB == HFgGroGTko){AdkUEekLUo = true;}
      while(OkQhpfhjHx == pdyhSalMtt){AVKRIQUVQx = true;}
      while(KfosGasPXF == KfosGasPXF){GujjsBqjUR = true;}
      while(HFgGroGTko == HFgGroGTko){lGzJnGhMdH = true;}
      if(slKKQccYcn == true){slKKQccYcn = false;}
      if(OZAQeXmzlP == true){OZAQeXmzlP = false;}
      if(daOTRJEKpB == true){daOTRJEKpB = false;}
      if(ZNzREXUdbd == true){ZNzREXUdbd = false;}
      if(xUmipgEPaU == true){xUmipgEPaU = false;}
      if(BGhULRXqsH == true){BGhULRXqsH = false;}
      if(YSiaOAZhMG == true){YSiaOAZhMG = false;}
      if(CIXHSJnedj == true){CIXHSJnedj = false;}
      if(EniUATedGm == true){EniUATedGm = false;}
      if(AdkUEekLUo == true){AdkUEekLUo = false;}
      if(HWDURrhZCB == true){HWDURrhZCB = false;}
      if(crMICkjNat == true){crMICkjNat = false;}
      if(VwaZFXXDDn == true){VwaZFXXDDn = false;}
      if(YbKnchjODI == true){YbKnchjODI = false;}
      if(lEaFJIQbST == true){lEaFJIQbST = false;}
      if(tWkaTKudOt == true){tWkaTKudOt = false;}
      if(UeWObBgYfT == true){UeWObBgYfT = false;}
      if(AVKRIQUVQx == true){AVKRIQUVQx = false;}
      if(GujjsBqjUR == true){GujjsBqjUR = false;}
      if(lGzJnGhMdH == true){lGzJnGhMdH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EWRNMJTONN
{ 
  void STjbTWagcj()
  { 
      bool sYdtqPWfZA = false;
      bool JlsQBoIaom = false;
      bool kVqMLFFMpQ = false;
      bool TdFKroQKxo = false;
      bool ujYXjLQUzf = false;
      bool RVNogXhRhk = false;
      bool JJoIgffiXL = false;
      bool XyczqAxTbA = false;
      bool nkNKzxPQcU = false;
      bool HzbMeltPpE = false;
      bool ehwnHSsNxg = false;
      bool aNogwXweJj = false;
      bool PPFDDYVQTF = false;
      bool FgcXUGoYCf = false;
      bool EBSwttKtPH = false;
      bool pPGGnPcski = false;
      bool xbsraskQLp = false;
      bool iWcceNxJIJ = false;
      bool OaAMPpaWjF = false;
      bool dwmThbHZUA = false;
      string cfOJZAGDdJ;
      string nrTZgXkDNF;
      string pFobKtxlrt;
      string VnJNzldbNJ;
      string GZqgsEptwK;
      string YMPFYWplyf;
      string CULjmAiFZt;
      string sJpEyQOIhG;
      string DCogUJXEoc;
      string uqcgHlOGts;
      string UkUBQPVLGH;
      string IhDrczedPd;
      string bdPxzBfIwM;
      string CHOokShmPE;
      string mLxhTNmkEI;
      string HjqPQqUWCP;
      string jNOtFBTOGJ;
      string QqNKpQghcl;
      string OtEnFRQyXt;
      string xKkAUZwDbS;
      if(cfOJZAGDdJ == UkUBQPVLGH){sYdtqPWfZA = true;}
      else if(UkUBQPVLGH == cfOJZAGDdJ){ehwnHSsNxg = true;}
      if(nrTZgXkDNF == IhDrczedPd){JlsQBoIaom = true;}
      else if(IhDrczedPd == nrTZgXkDNF){aNogwXweJj = true;}
      if(pFobKtxlrt == bdPxzBfIwM){kVqMLFFMpQ = true;}
      else if(bdPxzBfIwM == pFobKtxlrt){PPFDDYVQTF = true;}
      if(VnJNzldbNJ == CHOokShmPE){TdFKroQKxo = true;}
      else if(CHOokShmPE == VnJNzldbNJ){FgcXUGoYCf = true;}
      if(GZqgsEptwK == mLxhTNmkEI){ujYXjLQUzf = true;}
      else if(mLxhTNmkEI == GZqgsEptwK){EBSwttKtPH = true;}
      if(YMPFYWplyf == HjqPQqUWCP){RVNogXhRhk = true;}
      else if(HjqPQqUWCP == YMPFYWplyf){pPGGnPcski = true;}
      if(CULjmAiFZt == jNOtFBTOGJ){JJoIgffiXL = true;}
      else if(jNOtFBTOGJ == CULjmAiFZt){xbsraskQLp = true;}
      if(sJpEyQOIhG == QqNKpQghcl){XyczqAxTbA = true;}
      if(DCogUJXEoc == OtEnFRQyXt){nkNKzxPQcU = true;}
      if(uqcgHlOGts == xKkAUZwDbS){HzbMeltPpE = true;}
      while(QqNKpQghcl == sJpEyQOIhG){iWcceNxJIJ = true;}
      while(OtEnFRQyXt == OtEnFRQyXt){OaAMPpaWjF = true;}
      while(xKkAUZwDbS == xKkAUZwDbS){dwmThbHZUA = true;}
      if(sYdtqPWfZA == true){sYdtqPWfZA = false;}
      if(JlsQBoIaom == true){JlsQBoIaom = false;}
      if(kVqMLFFMpQ == true){kVqMLFFMpQ = false;}
      if(TdFKroQKxo == true){TdFKroQKxo = false;}
      if(ujYXjLQUzf == true){ujYXjLQUzf = false;}
      if(RVNogXhRhk == true){RVNogXhRhk = false;}
      if(JJoIgffiXL == true){JJoIgffiXL = false;}
      if(XyczqAxTbA == true){XyczqAxTbA = false;}
      if(nkNKzxPQcU == true){nkNKzxPQcU = false;}
      if(HzbMeltPpE == true){HzbMeltPpE = false;}
      if(ehwnHSsNxg == true){ehwnHSsNxg = false;}
      if(aNogwXweJj == true){aNogwXweJj = false;}
      if(PPFDDYVQTF == true){PPFDDYVQTF = false;}
      if(FgcXUGoYCf == true){FgcXUGoYCf = false;}
      if(EBSwttKtPH == true){EBSwttKtPH = false;}
      if(pPGGnPcski == true){pPGGnPcski = false;}
      if(xbsraskQLp == true){xbsraskQLp = false;}
      if(iWcceNxJIJ == true){iWcceNxJIJ = false;}
      if(OaAMPpaWjF == true){OaAMPpaWjF = false;}
      if(dwmThbHZUA == true){dwmThbHZUA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GQDDXBJRXH
{ 
  void BsPGtdCNNw()
  { 
      bool njyQLyqWbN = false;
      bool QsDdxhsmcG = false;
      bool qCbVOoWPRk = false;
      bool PJzwlWfAJT = false;
      bool QGppWFENOT = false;
      bool IGgpDkIbCV = false;
      bool baEqxGsHra = false;
      bool CrcJpjMkzI = false;
      bool kJBxbIcJsB = false;
      bool ODynqoCyrP = false;
      bool MwVnRPdXAS = false;
      bool YWcskRZGOn = false;
      bool djOpMztoRA = false;
      bool hNrjwnnNfM = false;
      bool eFIZbqZECZ = false;
      bool OujDlbheaS = false;
      bool UoFzjLdsxw = false;
      bool dMaBJXanOU = false;
      bool YplrkmdnxT = false;
      bool GJlMrpAJoQ = false;
      string tJJNbjMukK;
      string QNkCsfkrIZ;
      string iLQswoaPKp;
      string wQJcnBmHRT;
      string UwTYiNESeT;
      string cfbechrQQl;
      string JwjuNADHOq;
      string sdaoEmrqJh;
      string kHjqMQoeAF;
      string IWqfKYLXLi;
      string JwEnazFmZo;
      string oAGhBBLrhx;
      string LYHIiWmuee;
      string aTfaYnDwQN;
      string LBEKQIPIdI;
      string NSpNWkouEE;
      string LJIuOUUfJN;
      string xObTlJTwqZ;
      string GdQVRHdRDm;
      string yHrLBBsJwu;
      if(tJJNbjMukK == JwEnazFmZo){njyQLyqWbN = true;}
      else if(JwEnazFmZo == tJJNbjMukK){MwVnRPdXAS = true;}
      if(QNkCsfkrIZ == oAGhBBLrhx){QsDdxhsmcG = true;}
      else if(oAGhBBLrhx == QNkCsfkrIZ){YWcskRZGOn = true;}
      if(iLQswoaPKp == LYHIiWmuee){qCbVOoWPRk = true;}
      else if(LYHIiWmuee == iLQswoaPKp){djOpMztoRA = true;}
      if(wQJcnBmHRT == aTfaYnDwQN){PJzwlWfAJT = true;}
      else if(aTfaYnDwQN == wQJcnBmHRT){hNrjwnnNfM = true;}
      if(UwTYiNESeT == LBEKQIPIdI){QGppWFENOT = true;}
      else if(LBEKQIPIdI == UwTYiNESeT){eFIZbqZECZ = true;}
      if(cfbechrQQl == NSpNWkouEE){IGgpDkIbCV = true;}
      else if(NSpNWkouEE == cfbechrQQl){OujDlbheaS = true;}
      if(JwjuNADHOq == LJIuOUUfJN){baEqxGsHra = true;}
      else if(LJIuOUUfJN == JwjuNADHOq){UoFzjLdsxw = true;}
      if(sdaoEmrqJh == xObTlJTwqZ){CrcJpjMkzI = true;}
      if(kHjqMQoeAF == GdQVRHdRDm){kJBxbIcJsB = true;}
      if(IWqfKYLXLi == yHrLBBsJwu){ODynqoCyrP = true;}
      while(xObTlJTwqZ == sdaoEmrqJh){dMaBJXanOU = true;}
      while(GdQVRHdRDm == GdQVRHdRDm){YplrkmdnxT = true;}
      while(yHrLBBsJwu == yHrLBBsJwu){GJlMrpAJoQ = true;}
      if(njyQLyqWbN == true){njyQLyqWbN = false;}
      if(QsDdxhsmcG == true){QsDdxhsmcG = false;}
      if(qCbVOoWPRk == true){qCbVOoWPRk = false;}
      if(PJzwlWfAJT == true){PJzwlWfAJT = false;}
      if(QGppWFENOT == true){QGppWFENOT = false;}
      if(IGgpDkIbCV == true){IGgpDkIbCV = false;}
      if(baEqxGsHra == true){baEqxGsHra = false;}
      if(CrcJpjMkzI == true){CrcJpjMkzI = false;}
      if(kJBxbIcJsB == true){kJBxbIcJsB = false;}
      if(ODynqoCyrP == true){ODynqoCyrP = false;}
      if(MwVnRPdXAS == true){MwVnRPdXAS = false;}
      if(YWcskRZGOn == true){YWcskRZGOn = false;}
      if(djOpMztoRA == true){djOpMztoRA = false;}
      if(hNrjwnnNfM == true){hNrjwnnNfM = false;}
      if(eFIZbqZECZ == true){eFIZbqZECZ = false;}
      if(OujDlbheaS == true){OujDlbheaS = false;}
      if(UoFzjLdsxw == true){UoFzjLdsxw = false;}
      if(dMaBJXanOU == true){dMaBJXanOU = false;}
      if(YplrkmdnxT == true){YplrkmdnxT = false;}
      if(GJlMrpAJoQ == true){GJlMrpAJoQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HOKNFVHXOC
{ 
  void jlwlKPmCXp()
  { 
      bool DdZpRWbzgg = false;
      bool WJXoJFtPpw = false;
      bool pLyUBPAUaX = false;
      bool GwWszqhKOM = false;
      bool ogGOfCBhBM = false;
      bool xtQgErfFoC = false;
      bool VGYIaameoR = false;
      bool XiBcGJEiny = false;
      bool NSSOaLeooH = false;
      bool LbULqhIynF = false;
      bool PWrjoNsmZt = false;
      bool nwQqnCmJhO = false;
      bool wxohGuNolY = false;
      bool BFuihqaiZM = false;
      bool SqOtSPLdXn = false;
      bool uyPYJSgKct = false;
      bool AEABshAhIw = false;
      bool bDjVwEhtOq = false;
      bool jjQydCpWYP = false;
      bool KPGeMOpMBk = false;
      string OCpOKZPcne;
      string EdAVGQorky;
      string ZbfpZAsLqR;
      string ktFbBKLlyP;
      string kSltckanwc;
      string UwFRulWAoJ;
      string gDlVsKYXUu;
      string ECtVMHplMo;
      string YFPOxoomfO;
      string nLxnihgQAS;
      string LCSAXRBiFn;
      string wjnAjbmXXD;
      string VkrGHsEFme;
      string aYkscWlPpe;
      string mFhqRDXxEH;
      string tIrxxZKMse;
      string NuuZNWztWN;
      string oXgsPPDAnD;
      string UHBfjRgnwC;
      string MZWLRrJHdt;
      if(OCpOKZPcne == LCSAXRBiFn){DdZpRWbzgg = true;}
      else if(LCSAXRBiFn == OCpOKZPcne){PWrjoNsmZt = true;}
      if(EdAVGQorky == wjnAjbmXXD){WJXoJFtPpw = true;}
      else if(wjnAjbmXXD == EdAVGQorky){nwQqnCmJhO = true;}
      if(ZbfpZAsLqR == VkrGHsEFme){pLyUBPAUaX = true;}
      else if(VkrGHsEFme == ZbfpZAsLqR){wxohGuNolY = true;}
      if(ktFbBKLlyP == aYkscWlPpe){GwWszqhKOM = true;}
      else if(aYkscWlPpe == ktFbBKLlyP){BFuihqaiZM = true;}
      if(kSltckanwc == mFhqRDXxEH){ogGOfCBhBM = true;}
      else if(mFhqRDXxEH == kSltckanwc){SqOtSPLdXn = true;}
      if(UwFRulWAoJ == tIrxxZKMse){xtQgErfFoC = true;}
      else if(tIrxxZKMse == UwFRulWAoJ){uyPYJSgKct = true;}
      if(gDlVsKYXUu == NuuZNWztWN){VGYIaameoR = true;}
      else if(NuuZNWztWN == gDlVsKYXUu){AEABshAhIw = true;}
      if(ECtVMHplMo == oXgsPPDAnD){XiBcGJEiny = true;}
      if(YFPOxoomfO == UHBfjRgnwC){NSSOaLeooH = true;}
      if(nLxnihgQAS == MZWLRrJHdt){LbULqhIynF = true;}
      while(oXgsPPDAnD == ECtVMHplMo){bDjVwEhtOq = true;}
      while(UHBfjRgnwC == UHBfjRgnwC){jjQydCpWYP = true;}
      while(MZWLRrJHdt == MZWLRrJHdt){KPGeMOpMBk = true;}
      if(DdZpRWbzgg == true){DdZpRWbzgg = false;}
      if(WJXoJFtPpw == true){WJXoJFtPpw = false;}
      if(pLyUBPAUaX == true){pLyUBPAUaX = false;}
      if(GwWszqhKOM == true){GwWszqhKOM = false;}
      if(ogGOfCBhBM == true){ogGOfCBhBM = false;}
      if(xtQgErfFoC == true){xtQgErfFoC = false;}
      if(VGYIaameoR == true){VGYIaameoR = false;}
      if(XiBcGJEiny == true){XiBcGJEiny = false;}
      if(NSSOaLeooH == true){NSSOaLeooH = false;}
      if(LbULqhIynF == true){LbULqhIynF = false;}
      if(PWrjoNsmZt == true){PWrjoNsmZt = false;}
      if(nwQqnCmJhO == true){nwQqnCmJhO = false;}
      if(wxohGuNolY == true){wxohGuNolY = false;}
      if(BFuihqaiZM == true){BFuihqaiZM = false;}
      if(SqOtSPLdXn == true){SqOtSPLdXn = false;}
      if(uyPYJSgKct == true){uyPYJSgKct = false;}
      if(AEABshAhIw == true){AEABshAhIw = false;}
      if(bDjVwEhtOq == true){bDjVwEhtOq = false;}
      if(jjQydCpWYP == true){jjQydCpWYP = false;}
      if(KPGeMOpMBk == true){KPGeMOpMBk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FWUFVSXJBT
{ 
  void osmzxXcepM()
  { 
      bool eGqBZbHOkP = false;
      bool xPdUdfoztW = false;
      bool jtGkXqgfHA = false;
      bool ZNihnzIUqu = false;
      bool jWzLJlALxl = false;
      bool zSCYujAFch = false;
      bool ubHjoifufe = false;
      bool XUIymNttal = false;
      bool pVhUAHLKmD = false;
      bool zCqIzIOPWa = false;
      bool FEeSOeKDkg = false;
      bool pFeqqZsmih = false;
      bool XUIcfUdzze = false;
      bool yeXAfkpPGV = false;
      bool wHZFNsXzQZ = false;
      bool ObfnCjwClt = false;
      bool BKEGiLhdLF = false;
      bool idgNkPuDOm = false;
      bool wdhYPWyixu = false;
      bool oncLTkDSVC = false;
      string QMisESqelX;
      string lXXrsqTJOW;
      string litwqwwaTC;
      string VuHxfRqsJL;
      string mtwSbwLSqc;
      string oKhOOhRlBI;
      string VPKjBpQZMb;
      string zZADjqlbUt;
      string jcipMLNrix;
      string zFqBoWjLQk;
      string flGPdOKdeW;
      string wpRHYsgTXp;
      string cXqObsizNN;
      string HZLjOxWTMy;
      string AiNLBJnicw;
      string oPnaIHuqmj;
      string fLQRPVegra;
      string WNHZosKeNS;
      string FzWQXrljaH;
      string CefbRoSwue;
      if(QMisESqelX == flGPdOKdeW){eGqBZbHOkP = true;}
      else if(flGPdOKdeW == QMisESqelX){FEeSOeKDkg = true;}
      if(lXXrsqTJOW == wpRHYsgTXp){xPdUdfoztW = true;}
      else if(wpRHYsgTXp == lXXrsqTJOW){pFeqqZsmih = true;}
      if(litwqwwaTC == cXqObsizNN){jtGkXqgfHA = true;}
      else if(cXqObsizNN == litwqwwaTC){XUIcfUdzze = true;}
      if(VuHxfRqsJL == HZLjOxWTMy){ZNihnzIUqu = true;}
      else if(HZLjOxWTMy == VuHxfRqsJL){yeXAfkpPGV = true;}
      if(mtwSbwLSqc == AiNLBJnicw){jWzLJlALxl = true;}
      else if(AiNLBJnicw == mtwSbwLSqc){wHZFNsXzQZ = true;}
      if(oKhOOhRlBI == oPnaIHuqmj){zSCYujAFch = true;}
      else if(oPnaIHuqmj == oKhOOhRlBI){ObfnCjwClt = true;}
      if(VPKjBpQZMb == fLQRPVegra){ubHjoifufe = true;}
      else if(fLQRPVegra == VPKjBpQZMb){BKEGiLhdLF = true;}
      if(zZADjqlbUt == WNHZosKeNS){XUIymNttal = true;}
      if(jcipMLNrix == FzWQXrljaH){pVhUAHLKmD = true;}
      if(zFqBoWjLQk == CefbRoSwue){zCqIzIOPWa = true;}
      while(WNHZosKeNS == zZADjqlbUt){idgNkPuDOm = true;}
      while(FzWQXrljaH == FzWQXrljaH){wdhYPWyixu = true;}
      while(CefbRoSwue == CefbRoSwue){oncLTkDSVC = true;}
      if(eGqBZbHOkP == true){eGqBZbHOkP = false;}
      if(xPdUdfoztW == true){xPdUdfoztW = false;}
      if(jtGkXqgfHA == true){jtGkXqgfHA = false;}
      if(ZNihnzIUqu == true){ZNihnzIUqu = false;}
      if(jWzLJlALxl == true){jWzLJlALxl = false;}
      if(zSCYujAFch == true){zSCYujAFch = false;}
      if(ubHjoifufe == true){ubHjoifufe = false;}
      if(XUIymNttal == true){XUIymNttal = false;}
      if(pVhUAHLKmD == true){pVhUAHLKmD = false;}
      if(zCqIzIOPWa == true){zCqIzIOPWa = false;}
      if(FEeSOeKDkg == true){FEeSOeKDkg = false;}
      if(pFeqqZsmih == true){pFeqqZsmih = false;}
      if(XUIcfUdzze == true){XUIcfUdzze = false;}
      if(yeXAfkpPGV == true){yeXAfkpPGV = false;}
      if(wHZFNsXzQZ == true){wHZFNsXzQZ = false;}
      if(ObfnCjwClt == true){ObfnCjwClt = false;}
      if(BKEGiLhdLF == true){BKEGiLhdLF = false;}
      if(idgNkPuDOm == true){idgNkPuDOm = false;}
      if(wdhYPWyixu == true){wdhYPWyixu = false;}
      if(oncLTkDSVC == true){oncLTkDSVC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OQCVZQSZAV
{ 
  void BAnrRHHAzl()
  { 
      bool sVPpHfXEgp = false;
      bool dhqiQacXjb = false;
      bool waLdTKqgBh = false;
      bool sopWDdNVDN = false;
      bool zMGnlNsZgW = false;
      bool qYQuiSJlVw = false;
      bool oqCyxnrUfl = false;
      bool MGTVbjTXqG = false;
      bool RQAeqTXtnk = false;
      bool UaAHXIJHqx = false;
      bool VYstJjEuTz = false;
      bool zltPeYpXHc = false;
      bool QxfuRlGMxS = false;
      bool ZLftjrWFVG = false;
      bool Obaolhfkcz = false;
      bool RlANfXrybW = false;
      bool cryAYmFAel = false;
      bool BjBANnVqJj = false;
      bool FVjxBmLRNL = false;
      bool AYdzcWdaPy = false;
      string cCkUYlYwwn;
      string OroNBSKfVi;
      string QTuQTqnJGF;
      string JQmDmCmmxc;
      string lotaAuRRiL;
      string NqoCDIHUBh;
      string yPpqdxFkaz;
      string fXirxaYUPY;
      string YWZtqRbjAd;
      string uRkPeWzDwD;
      string ogqjepIwFb;
      string jmEcIaouzM;
      string VUkwENlSNa;
      string bVXMireoPA;
      string JeeXtHNIGD;
      string gDDjgTutfR;
      string DohdAOOqsQ;
      string wAeyCppNCw;
      string AcMKtXRneP;
      string wkJyxTxBWf;
      if(cCkUYlYwwn == ogqjepIwFb){sVPpHfXEgp = true;}
      else if(ogqjepIwFb == cCkUYlYwwn){VYstJjEuTz = true;}
      if(OroNBSKfVi == jmEcIaouzM){dhqiQacXjb = true;}
      else if(jmEcIaouzM == OroNBSKfVi){zltPeYpXHc = true;}
      if(QTuQTqnJGF == VUkwENlSNa){waLdTKqgBh = true;}
      else if(VUkwENlSNa == QTuQTqnJGF){QxfuRlGMxS = true;}
      if(JQmDmCmmxc == bVXMireoPA){sopWDdNVDN = true;}
      else if(bVXMireoPA == JQmDmCmmxc){ZLftjrWFVG = true;}
      if(lotaAuRRiL == JeeXtHNIGD){zMGnlNsZgW = true;}
      else if(JeeXtHNIGD == lotaAuRRiL){Obaolhfkcz = true;}
      if(NqoCDIHUBh == gDDjgTutfR){qYQuiSJlVw = true;}
      else if(gDDjgTutfR == NqoCDIHUBh){RlANfXrybW = true;}
      if(yPpqdxFkaz == DohdAOOqsQ){oqCyxnrUfl = true;}
      else if(DohdAOOqsQ == yPpqdxFkaz){cryAYmFAel = true;}
      if(fXirxaYUPY == wAeyCppNCw){MGTVbjTXqG = true;}
      if(YWZtqRbjAd == AcMKtXRneP){RQAeqTXtnk = true;}
      if(uRkPeWzDwD == wkJyxTxBWf){UaAHXIJHqx = true;}
      while(wAeyCppNCw == fXirxaYUPY){BjBANnVqJj = true;}
      while(AcMKtXRneP == AcMKtXRneP){FVjxBmLRNL = true;}
      while(wkJyxTxBWf == wkJyxTxBWf){AYdzcWdaPy = true;}
      if(sVPpHfXEgp == true){sVPpHfXEgp = false;}
      if(dhqiQacXjb == true){dhqiQacXjb = false;}
      if(waLdTKqgBh == true){waLdTKqgBh = false;}
      if(sopWDdNVDN == true){sopWDdNVDN = false;}
      if(zMGnlNsZgW == true){zMGnlNsZgW = false;}
      if(qYQuiSJlVw == true){qYQuiSJlVw = false;}
      if(oqCyxnrUfl == true){oqCyxnrUfl = false;}
      if(MGTVbjTXqG == true){MGTVbjTXqG = false;}
      if(RQAeqTXtnk == true){RQAeqTXtnk = false;}
      if(UaAHXIJHqx == true){UaAHXIJHqx = false;}
      if(VYstJjEuTz == true){VYstJjEuTz = false;}
      if(zltPeYpXHc == true){zltPeYpXHc = false;}
      if(QxfuRlGMxS == true){QxfuRlGMxS = false;}
      if(ZLftjrWFVG == true){ZLftjrWFVG = false;}
      if(Obaolhfkcz == true){Obaolhfkcz = false;}
      if(RlANfXrybW == true){RlANfXrybW = false;}
      if(cryAYmFAel == true){cryAYmFAel = false;}
      if(BjBANnVqJj == true){BjBANnVqJj = false;}
      if(FVjxBmLRNL == true){FVjxBmLRNL = false;}
      if(AYdzcWdaPy == true){AYdzcWdaPy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MQBXURHNHT
{ 
  void bLoGEnmzpr()
  { 
      bool omIoEINXcw = false;
      bool yfffayZuAU = false;
      bool hqopuhEKug = false;
      bool FtrrPcXfRy = false;
      bool OOmqqeyfMg = false;
      bool qZGgEyyRsW = false;
      bool EDcupEmnQx = false;
      bool atdCGTExzP = false;
      bool jXxNpfmLmR = false;
      bool eFltsLlqBm = false;
      bool rJPOGwwEZk = false;
      bool sASclgFOFK = false;
      bool QaAzSUIiIu = false;
      bool hMwMXZIhHs = false;
      bool iilCXdmIIM = false;
      bool FWlpVRJPwl = false;
      bool nNueCfEFFM = false;
      bool XWHLbhoyao = false;
      bool gzawoKaFqG = false;
      bool QrlVFVmGzq = false;
      string fgPaohZmhZ;
      string ElTyXUXkQM;
      string uBDhutqYIn;
      string oBPttYkqhJ;
      string pTdYmmrClG;
      string ePKLLddhet;
      string pBeskDVZDy;
      string ifDGVbWetH;
      string CnlBIYpEhP;
      string uDLmSonjmj;
      string RRznWyLEoj;
      string HymWqCOckL;
      string MQrmCfUQmg;
      string mlqKpkoyeJ;
      string MlPxIxPouQ;
      string ZLzbWAZLkq;
      string duQHwUHcgG;
      string MQyayaBteF;
      string PfUVHbmPmp;
      string KdMnfRUHBm;
      if(fgPaohZmhZ == RRznWyLEoj){omIoEINXcw = true;}
      else if(RRznWyLEoj == fgPaohZmhZ){rJPOGwwEZk = true;}
      if(ElTyXUXkQM == HymWqCOckL){yfffayZuAU = true;}
      else if(HymWqCOckL == ElTyXUXkQM){sASclgFOFK = true;}
      if(uBDhutqYIn == MQrmCfUQmg){hqopuhEKug = true;}
      else if(MQrmCfUQmg == uBDhutqYIn){QaAzSUIiIu = true;}
      if(oBPttYkqhJ == mlqKpkoyeJ){FtrrPcXfRy = true;}
      else if(mlqKpkoyeJ == oBPttYkqhJ){hMwMXZIhHs = true;}
      if(pTdYmmrClG == MlPxIxPouQ){OOmqqeyfMg = true;}
      else if(MlPxIxPouQ == pTdYmmrClG){iilCXdmIIM = true;}
      if(ePKLLddhet == ZLzbWAZLkq){qZGgEyyRsW = true;}
      else if(ZLzbWAZLkq == ePKLLddhet){FWlpVRJPwl = true;}
      if(pBeskDVZDy == duQHwUHcgG){EDcupEmnQx = true;}
      else if(duQHwUHcgG == pBeskDVZDy){nNueCfEFFM = true;}
      if(ifDGVbWetH == MQyayaBteF){atdCGTExzP = true;}
      if(CnlBIYpEhP == PfUVHbmPmp){jXxNpfmLmR = true;}
      if(uDLmSonjmj == KdMnfRUHBm){eFltsLlqBm = true;}
      while(MQyayaBteF == ifDGVbWetH){XWHLbhoyao = true;}
      while(PfUVHbmPmp == PfUVHbmPmp){gzawoKaFqG = true;}
      while(KdMnfRUHBm == KdMnfRUHBm){QrlVFVmGzq = true;}
      if(omIoEINXcw == true){omIoEINXcw = false;}
      if(yfffayZuAU == true){yfffayZuAU = false;}
      if(hqopuhEKug == true){hqopuhEKug = false;}
      if(FtrrPcXfRy == true){FtrrPcXfRy = false;}
      if(OOmqqeyfMg == true){OOmqqeyfMg = false;}
      if(qZGgEyyRsW == true){qZGgEyyRsW = false;}
      if(EDcupEmnQx == true){EDcupEmnQx = false;}
      if(atdCGTExzP == true){atdCGTExzP = false;}
      if(jXxNpfmLmR == true){jXxNpfmLmR = false;}
      if(eFltsLlqBm == true){eFltsLlqBm = false;}
      if(rJPOGwwEZk == true){rJPOGwwEZk = false;}
      if(sASclgFOFK == true){sASclgFOFK = false;}
      if(QaAzSUIiIu == true){QaAzSUIiIu = false;}
      if(hMwMXZIhHs == true){hMwMXZIhHs = false;}
      if(iilCXdmIIM == true){iilCXdmIIM = false;}
      if(FWlpVRJPwl == true){FWlpVRJPwl = false;}
      if(nNueCfEFFM == true){nNueCfEFFM = false;}
      if(XWHLbhoyao == true){XWHLbhoyao = false;}
      if(gzawoKaFqG == true){gzawoKaFqG = false;}
      if(QrlVFVmGzq == true){QrlVFVmGzq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWMESLORLJ
{ 
  void fPWHpKnDwe()
  { 
      bool JbHbbYysqc = false;
      bool WdjQUDhYTK = false;
      bool GitGbUcgCm = false;
      bool JqysTJssZA = false;
      bool pWEVzHXaTj = false;
      bool drumNZhBAH = false;
      bool wQpDTffpwL = false;
      bool JnyTUidYGT = false;
      bool wBNSJRuLfs = false;
      bool arsSDYfBBS = false;
      bool bheIZosbSd = false;
      bool wItfLuDXsB = false;
      bool jTKCjQufPu = false;
      bool DbWmrNWEsT = false;
      bool XTsBxSyMGI = false;
      bool UIIAiHXbYI = false;
      bool sNLWZUlGmx = false;
      bool XyeYcQaIFR = false;
      bool SiYHZuTWEk = false;
      bool pufjaKIVbc = false;
      string jwOqtBkKwD;
      string zoyIhKnmRc;
      string wznrUrPfod;
      string MEECuMmlPX;
      string HEiwRcOLgi;
      string tkcizkIVVC;
      string kFURqtjuMV;
      string WCXsVrPqZr;
      string dEyFjbbVDK;
      string EQPNlBiQFW;
      string rSzLLqMiNH;
      string UQwdYgHPhO;
      string SOrCQGmJHT;
      string IylCALEltr;
      string OrIwomUkoE;
      string tTipEcZwtF;
      string EDbsyVdsdM;
      string bUVpzaGwMc;
      string kBUCZnPuyW;
      string kHrnmLQOxT;
      if(jwOqtBkKwD == rSzLLqMiNH){JbHbbYysqc = true;}
      else if(rSzLLqMiNH == jwOqtBkKwD){bheIZosbSd = true;}
      if(zoyIhKnmRc == UQwdYgHPhO){WdjQUDhYTK = true;}
      else if(UQwdYgHPhO == zoyIhKnmRc){wItfLuDXsB = true;}
      if(wznrUrPfod == SOrCQGmJHT){GitGbUcgCm = true;}
      else if(SOrCQGmJHT == wznrUrPfod){jTKCjQufPu = true;}
      if(MEECuMmlPX == IylCALEltr){JqysTJssZA = true;}
      else if(IylCALEltr == MEECuMmlPX){DbWmrNWEsT = true;}
      if(HEiwRcOLgi == OrIwomUkoE){pWEVzHXaTj = true;}
      else if(OrIwomUkoE == HEiwRcOLgi){XTsBxSyMGI = true;}
      if(tkcizkIVVC == tTipEcZwtF){drumNZhBAH = true;}
      else if(tTipEcZwtF == tkcizkIVVC){UIIAiHXbYI = true;}
      if(kFURqtjuMV == EDbsyVdsdM){wQpDTffpwL = true;}
      else if(EDbsyVdsdM == kFURqtjuMV){sNLWZUlGmx = true;}
      if(WCXsVrPqZr == bUVpzaGwMc){JnyTUidYGT = true;}
      if(dEyFjbbVDK == kBUCZnPuyW){wBNSJRuLfs = true;}
      if(EQPNlBiQFW == kHrnmLQOxT){arsSDYfBBS = true;}
      while(bUVpzaGwMc == WCXsVrPqZr){XyeYcQaIFR = true;}
      while(kBUCZnPuyW == kBUCZnPuyW){SiYHZuTWEk = true;}
      while(kHrnmLQOxT == kHrnmLQOxT){pufjaKIVbc = true;}
      if(JbHbbYysqc == true){JbHbbYysqc = false;}
      if(WdjQUDhYTK == true){WdjQUDhYTK = false;}
      if(GitGbUcgCm == true){GitGbUcgCm = false;}
      if(JqysTJssZA == true){JqysTJssZA = false;}
      if(pWEVzHXaTj == true){pWEVzHXaTj = false;}
      if(drumNZhBAH == true){drumNZhBAH = false;}
      if(wQpDTffpwL == true){wQpDTffpwL = false;}
      if(JnyTUidYGT == true){JnyTUidYGT = false;}
      if(wBNSJRuLfs == true){wBNSJRuLfs = false;}
      if(arsSDYfBBS == true){arsSDYfBBS = false;}
      if(bheIZosbSd == true){bheIZosbSd = false;}
      if(wItfLuDXsB == true){wItfLuDXsB = false;}
      if(jTKCjQufPu == true){jTKCjQufPu = false;}
      if(DbWmrNWEsT == true){DbWmrNWEsT = false;}
      if(XTsBxSyMGI == true){XTsBxSyMGI = false;}
      if(UIIAiHXbYI == true){UIIAiHXbYI = false;}
      if(sNLWZUlGmx == true){sNLWZUlGmx = false;}
      if(XyeYcQaIFR == true){XyeYcQaIFR = false;}
      if(SiYHZuTWEk == true){SiYHZuTWEk = false;}
      if(pufjaKIVbc == true){pufjaKIVbc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TUIXMJPBNN
{ 
  void OktfzkuGJL()
  { 
      bool MoSjpmxfLp = false;
      bool ptimsCffXO = false;
      bool FupTHAusVI = false;
      bool DnVwOmeiAy = false;
      bool ZxxCZUGnug = false;
      bool BAuWnQzzco = false;
      bool qEJDmCXmYG = false;
      bool WxfYoHxmsm = false;
      bool sGyoGCryIy = false;
      bool neFKGVntPX = false;
      bool wSPoJEUVhf = false;
      bool SLGpukGUwk = false;
      bool JYeZRqqUST = false;
      bool TDXVpapJeB = false;
      bool gWQbebYPPU = false;
      bool OTxdNWmpWR = false;
      bool MADOLPnjzU = false;
      bool uxotDmICup = false;
      bool SaFxEAFsHS = false;
      bool mAlMogSCQP = false;
      string nzaZPMpPRl;
      string lSPTKxnDGD;
      string Zwwlkazdmo;
      string EzEXVjRmiz;
      string jAEJCsaqgD;
      string CuBXMrDnnn;
      string NLbchlOqxZ;
      string eAUHTYrmjr;
      string AIxilIyfLd;
      string gcztkXXbaP;
      string eisGXCZsEm;
      string APEwnFNspY;
      string nhfTrBBZWu;
      string BPLUMROqKj;
      string hEbXdQYCGf;
      string JelCawCYOW;
      string AAWIkjEjiV;
      string pWhFpjGIpa;
      string cyTpkWdJsP;
      string OpbnihgSls;
      if(nzaZPMpPRl == eisGXCZsEm){MoSjpmxfLp = true;}
      else if(eisGXCZsEm == nzaZPMpPRl){wSPoJEUVhf = true;}
      if(lSPTKxnDGD == APEwnFNspY){ptimsCffXO = true;}
      else if(APEwnFNspY == lSPTKxnDGD){SLGpukGUwk = true;}
      if(Zwwlkazdmo == nhfTrBBZWu){FupTHAusVI = true;}
      else if(nhfTrBBZWu == Zwwlkazdmo){JYeZRqqUST = true;}
      if(EzEXVjRmiz == BPLUMROqKj){DnVwOmeiAy = true;}
      else if(BPLUMROqKj == EzEXVjRmiz){TDXVpapJeB = true;}
      if(jAEJCsaqgD == hEbXdQYCGf){ZxxCZUGnug = true;}
      else if(hEbXdQYCGf == jAEJCsaqgD){gWQbebYPPU = true;}
      if(CuBXMrDnnn == JelCawCYOW){BAuWnQzzco = true;}
      else if(JelCawCYOW == CuBXMrDnnn){OTxdNWmpWR = true;}
      if(NLbchlOqxZ == AAWIkjEjiV){qEJDmCXmYG = true;}
      else if(AAWIkjEjiV == NLbchlOqxZ){MADOLPnjzU = true;}
      if(eAUHTYrmjr == pWhFpjGIpa){WxfYoHxmsm = true;}
      if(AIxilIyfLd == cyTpkWdJsP){sGyoGCryIy = true;}
      if(gcztkXXbaP == OpbnihgSls){neFKGVntPX = true;}
      while(pWhFpjGIpa == eAUHTYrmjr){uxotDmICup = true;}
      while(cyTpkWdJsP == cyTpkWdJsP){SaFxEAFsHS = true;}
      while(OpbnihgSls == OpbnihgSls){mAlMogSCQP = true;}
      if(MoSjpmxfLp == true){MoSjpmxfLp = false;}
      if(ptimsCffXO == true){ptimsCffXO = false;}
      if(FupTHAusVI == true){FupTHAusVI = false;}
      if(DnVwOmeiAy == true){DnVwOmeiAy = false;}
      if(ZxxCZUGnug == true){ZxxCZUGnug = false;}
      if(BAuWnQzzco == true){BAuWnQzzco = false;}
      if(qEJDmCXmYG == true){qEJDmCXmYG = false;}
      if(WxfYoHxmsm == true){WxfYoHxmsm = false;}
      if(sGyoGCryIy == true){sGyoGCryIy = false;}
      if(neFKGVntPX == true){neFKGVntPX = false;}
      if(wSPoJEUVhf == true){wSPoJEUVhf = false;}
      if(SLGpukGUwk == true){SLGpukGUwk = false;}
      if(JYeZRqqUST == true){JYeZRqqUST = false;}
      if(TDXVpapJeB == true){TDXVpapJeB = false;}
      if(gWQbebYPPU == true){gWQbebYPPU = false;}
      if(OTxdNWmpWR == true){OTxdNWmpWR = false;}
      if(MADOLPnjzU == true){MADOLPnjzU = false;}
      if(uxotDmICup == true){uxotDmICup = false;}
      if(SaFxEAFsHS == true){SaFxEAFsHS = false;}
      if(mAlMogSCQP == true){mAlMogSCQP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LZAVVOAPPC
{ 
  void dbBkiRFXfb()
  { 
      bool UKrHyYIxOA = false;
      bool RXgDUCmcyg = false;
      bool RIrfmPiBQd = false;
      bool ElbQnZqbNa = false;
      bool ROqgtgUIEG = false;
      bool mxuDMLRMTi = false;
      bool oGgkueuPPt = false;
      bool LKOXPDQLkG = false;
      bool tawJpGqYDc = false;
      bool HdHelKgGkO = false;
      bool kFsJuciXnJ = false;
      bool tFaNnOJWto = false;
      bool nVLmmgCjlE = false;
      bool VKaWUohmON = false;
      bool XTkthBCtpX = false;
      bool AKLwZOsFWN = false;
      bool ZzlimjeErz = false;
      bool fWIgQUkREk = false;
      bool dIsNDLyewF = false;
      bool wbQAnYhBGy = false;
      string TAPYxrFmjc;
      string ZbokaogKYE;
      string BhRpnjcEaP;
      string YwraHIwXte;
      string rCJXDHEMYU;
      string PVMfQkiYjM;
      string OBMTDdjOcS;
      string sIQsLzXsmg;
      string eQfGACiLJW;
      string YWngPqooTZ;
      string WpjFaGFTTR;
      string MolCgyVFSA;
      string tYEGsVUidU;
      string JiZMKofZet;
      string wPrrJjkkzQ;
      string UiWSeykdMF;
      string lWoyHdPZrr;
      string RwaYEefMwI;
      string kijMzZLGgM;
      string ECMYIZZsje;
      if(TAPYxrFmjc == WpjFaGFTTR){UKrHyYIxOA = true;}
      else if(WpjFaGFTTR == TAPYxrFmjc){kFsJuciXnJ = true;}
      if(ZbokaogKYE == MolCgyVFSA){RXgDUCmcyg = true;}
      else if(MolCgyVFSA == ZbokaogKYE){tFaNnOJWto = true;}
      if(BhRpnjcEaP == tYEGsVUidU){RIrfmPiBQd = true;}
      else if(tYEGsVUidU == BhRpnjcEaP){nVLmmgCjlE = true;}
      if(YwraHIwXte == JiZMKofZet){ElbQnZqbNa = true;}
      else if(JiZMKofZet == YwraHIwXte){VKaWUohmON = true;}
      if(rCJXDHEMYU == wPrrJjkkzQ){ROqgtgUIEG = true;}
      else if(wPrrJjkkzQ == rCJXDHEMYU){XTkthBCtpX = true;}
      if(PVMfQkiYjM == UiWSeykdMF){mxuDMLRMTi = true;}
      else if(UiWSeykdMF == PVMfQkiYjM){AKLwZOsFWN = true;}
      if(OBMTDdjOcS == lWoyHdPZrr){oGgkueuPPt = true;}
      else if(lWoyHdPZrr == OBMTDdjOcS){ZzlimjeErz = true;}
      if(sIQsLzXsmg == RwaYEefMwI){LKOXPDQLkG = true;}
      if(eQfGACiLJW == kijMzZLGgM){tawJpGqYDc = true;}
      if(YWngPqooTZ == ECMYIZZsje){HdHelKgGkO = true;}
      while(RwaYEefMwI == sIQsLzXsmg){fWIgQUkREk = true;}
      while(kijMzZLGgM == kijMzZLGgM){dIsNDLyewF = true;}
      while(ECMYIZZsje == ECMYIZZsje){wbQAnYhBGy = true;}
      if(UKrHyYIxOA == true){UKrHyYIxOA = false;}
      if(RXgDUCmcyg == true){RXgDUCmcyg = false;}
      if(RIrfmPiBQd == true){RIrfmPiBQd = false;}
      if(ElbQnZqbNa == true){ElbQnZqbNa = false;}
      if(ROqgtgUIEG == true){ROqgtgUIEG = false;}
      if(mxuDMLRMTi == true){mxuDMLRMTi = false;}
      if(oGgkueuPPt == true){oGgkueuPPt = false;}
      if(LKOXPDQLkG == true){LKOXPDQLkG = false;}
      if(tawJpGqYDc == true){tawJpGqYDc = false;}
      if(HdHelKgGkO == true){HdHelKgGkO = false;}
      if(kFsJuciXnJ == true){kFsJuciXnJ = false;}
      if(tFaNnOJWto == true){tFaNnOJWto = false;}
      if(nVLmmgCjlE == true){nVLmmgCjlE = false;}
      if(VKaWUohmON == true){VKaWUohmON = false;}
      if(XTkthBCtpX == true){XTkthBCtpX = false;}
      if(AKLwZOsFWN == true){AKLwZOsFWN = false;}
      if(ZzlimjeErz == true){ZzlimjeErz = false;}
      if(fWIgQUkREk == true){fWIgQUkREk = false;}
      if(dIsNDLyewF == true){dIsNDLyewF = false;}
      if(wbQAnYhBGy == true){wbQAnYhBGy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LGGJEPZDGW
{ 
  void XlbulqWthU()
  { 
      bool XaTdpNuIEj = false;
      bool TtGcZwCoQQ = false;
      bool RDSOlnAyrb = false;
      bool LjnPlEOlAY = false;
      bool VBzWccwQdc = false;
      bool mDTYMUHFrB = false;
      bool NxQcXjGppV = false;
      bool gPnrtPDwlI = false;
      bool riTOnIPODQ = false;
      bool wItyKYjVzr = false;
      bool VFaIuXObdw = false;
      bool RLTjJdcCoP = false;
      bool TqmYYYVpgV = false;
      bool ehxslmHLSP = false;
      bool snkGzkoJof = false;
      bool uhfiYeSBiW = false;
      bool CXuIRiNaxV = false;
      bool WQiZVeGfYm = false;
      bool jLBAZwBNTH = false;
      bool UGcwNUscoQ = false;
      string mkSjheimnL;
      string syGjZGhNgA;
      string krdkMKcuhX;
      string ClImOUDwPe;
      string WNLFYiqWim;
      string cVHZTtGhXX;
      string BmFQIHoTUF;
      string CkxCcWgXMc;
      string SGLtugdiTT;
      string OVYrciIuxR;
      string sXCdkqXFww;
      string NhUtEubKUa;
      string cGAApfMEYs;
      string OkauiuDgID;
      string JYlWGfAdmh;
      string HxZWnmXBmF;
      string dTfChbHZKJ;
      string qtBRRETctK;
      string ehQqlQKEGw;
      string XCtDYprjod;
      if(mkSjheimnL == sXCdkqXFww){XaTdpNuIEj = true;}
      else if(sXCdkqXFww == mkSjheimnL){VFaIuXObdw = true;}
      if(syGjZGhNgA == NhUtEubKUa){TtGcZwCoQQ = true;}
      else if(NhUtEubKUa == syGjZGhNgA){RLTjJdcCoP = true;}
      if(krdkMKcuhX == cGAApfMEYs){RDSOlnAyrb = true;}
      else if(cGAApfMEYs == krdkMKcuhX){TqmYYYVpgV = true;}
      if(ClImOUDwPe == OkauiuDgID){LjnPlEOlAY = true;}
      else if(OkauiuDgID == ClImOUDwPe){ehxslmHLSP = true;}
      if(WNLFYiqWim == JYlWGfAdmh){VBzWccwQdc = true;}
      else if(JYlWGfAdmh == WNLFYiqWim){snkGzkoJof = true;}
      if(cVHZTtGhXX == HxZWnmXBmF){mDTYMUHFrB = true;}
      else if(HxZWnmXBmF == cVHZTtGhXX){uhfiYeSBiW = true;}
      if(BmFQIHoTUF == dTfChbHZKJ){NxQcXjGppV = true;}
      else if(dTfChbHZKJ == BmFQIHoTUF){CXuIRiNaxV = true;}
      if(CkxCcWgXMc == qtBRRETctK){gPnrtPDwlI = true;}
      if(SGLtugdiTT == ehQqlQKEGw){riTOnIPODQ = true;}
      if(OVYrciIuxR == XCtDYprjod){wItyKYjVzr = true;}
      while(qtBRRETctK == CkxCcWgXMc){WQiZVeGfYm = true;}
      while(ehQqlQKEGw == ehQqlQKEGw){jLBAZwBNTH = true;}
      while(XCtDYprjod == XCtDYprjod){UGcwNUscoQ = true;}
      if(XaTdpNuIEj == true){XaTdpNuIEj = false;}
      if(TtGcZwCoQQ == true){TtGcZwCoQQ = false;}
      if(RDSOlnAyrb == true){RDSOlnAyrb = false;}
      if(LjnPlEOlAY == true){LjnPlEOlAY = false;}
      if(VBzWccwQdc == true){VBzWccwQdc = false;}
      if(mDTYMUHFrB == true){mDTYMUHFrB = false;}
      if(NxQcXjGppV == true){NxQcXjGppV = false;}
      if(gPnrtPDwlI == true){gPnrtPDwlI = false;}
      if(riTOnIPODQ == true){riTOnIPODQ = false;}
      if(wItyKYjVzr == true){wItyKYjVzr = false;}
      if(VFaIuXObdw == true){VFaIuXObdw = false;}
      if(RLTjJdcCoP == true){RLTjJdcCoP = false;}
      if(TqmYYYVpgV == true){TqmYYYVpgV = false;}
      if(ehxslmHLSP == true){ehxslmHLSP = false;}
      if(snkGzkoJof == true){snkGzkoJof = false;}
      if(uhfiYeSBiW == true){uhfiYeSBiW = false;}
      if(CXuIRiNaxV == true){CXuIRiNaxV = false;}
      if(WQiZVeGfYm == true){WQiZVeGfYm = false;}
      if(jLBAZwBNTH == true){jLBAZwBNTH = false;}
      if(UGcwNUscoQ == true){UGcwNUscoQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QYVNGIETTD
{ 
  void DliWsBLjtt()
  { 
      bool RMePokpGNZ = false;
      bool KNbnbAeZQq = false;
      bool LwRDGMVVlZ = false;
      bool PQaSbTagEK = false;
      bool dGZQOFLtTG = false;
      bool kQHUoUtbJb = false;
      bool PTTnJslILI = false;
      bool ZyVGMFWBoB = false;
      bool BbCfnyIFdG = false;
      bool YzXctJlkGU = false;
      bool SCiKfmuAHi = false;
      bool yslHZmRnAL = false;
      bool kfeEjZZsLC = false;
      bool TltUhysqzB = false;
      bool DHytIeNPCH = false;
      bool rxkuilXeaG = false;
      bool MBoEPMyQZb = false;
      bool tZnyHchkuE = false;
      bool MKpEKVAzkw = false;
      bool aOPsoBSsdw = false;
      string YTEgcYQMUg;
      string EkYWPCfWoS;
      string XSKChGRBac;
      string pXaERnBIDg;
      string YQyefidtGL;
      string shKrtFIBzV;
      string HOlqqfJTFb;
      string BXTItGTfWy;
      string cXuPjHNiKL;
      string ezJhYJeHnz;
      string ZJoeKVOCxm;
      string lceBrjTWHi;
      string SZJswBOlik;
      string bMrWXSiPEN;
      string sLkWZCUHoo;
      string oHzEgzAuhI;
      string GbTMKYjHcY;
      string ADRspHolTt;
      string fGwsuTMnpY;
      string SmhuGQqYLA;
      if(YTEgcYQMUg == ZJoeKVOCxm){RMePokpGNZ = true;}
      else if(ZJoeKVOCxm == YTEgcYQMUg){SCiKfmuAHi = true;}
      if(EkYWPCfWoS == lceBrjTWHi){KNbnbAeZQq = true;}
      else if(lceBrjTWHi == EkYWPCfWoS){yslHZmRnAL = true;}
      if(XSKChGRBac == SZJswBOlik){LwRDGMVVlZ = true;}
      else if(SZJswBOlik == XSKChGRBac){kfeEjZZsLC = true;}
      if(pXaERnBIDg == bMrWXSiPEN){PQaSbTagEK = true;}
      else if(bMrWXSiPEN == pXaERnBIDg){TltUhysqzB = true;}
      if(YQyefidtGL == sLkWZCUHoo){dGZQOFLtTG = true;}
      else if(sLkWZCUHoo == YQyefidtGL){DHytIeNPCH = true;}
      if(shKrtFIBzV == oHzEgzAuhI){kQHUoUtbJb = true;}
      else if(oHzEgzAuhI == shKrtFIBzV){rxkuilXeaG = true;}
      if(HOlqqfJTFb == GbTMKYjHcY){PTTnJslILI = true;}
      else if(GbTMKYjHcY == HOlqqfJTFb){MBoEPMyQZb = true;}
      if(BXTItGTfWy == ADRspHolTt){ZyVGMFWBoB = true;}
      if(cXuPjHNiKL == fGwsuTMnpY){BbCfnyIFdG = true;}
      if(ezJhYJeHnz == SmhuGQqYLA){YzXctJlkGU = true;}
      while(ADRspHolTt == BXTItGTfWy){tZnyHchkuE = true;}
      while(fGwsuTMnpY == fGwsuTMnpY){MKpEKVAzkw = true;}
      while(SmhuGQqYLA == SmhuGQqYLA){aOPsoBSsdw = true;}
      if(RMePokpGNZ == true){RMePokpGNZ = false;}
      if(KNbnbAeZQq == true){KNbnbAeZQq = false;}
      if(LwRDGMVVlZ == true){LwRDGMVVlZ = false;}
      if(PQaSbTagEK == true){PQaSbTagEK = false;}
      if(dGZQOFLtTG == true){dGZQOFLtTG = false;}
      if(kQHUoUtbJb == true){kQHUoUtbJb = false;}
      if(PTTnJslILI == true){PTTnJslILI = false;}
      if(ZyVGMFWBoB == true){ZyVGMFWBoB = false;}
      if(BbCfnyIFdG == true){BbCfnyIFdG = false;}
      if(YzXctJlkGU == true){YzXctJlkGU = false;}
      if(SCiKfmuAHi == true){SCiKfmuAHi = false;}
      if(yslHZmRnAL == true){yslHZmRnAL = false;}
      if(kfeEjZZsLC == true){kfeEjZZsLC = false;}
      if(TltUhysqzB == true){TltUhysqzB = false;}
      if(DHytIeNPCH == true){DHytIeNPCH = false;}
      if(rxkuilXeaG == true){rxkuilXeaG = false;}
      if(MBoEPMyQZb == true){MBoEPMyQZb = false;}
      if(tZnyHchkuE == true){tZnyHchkuE = false;}
      if(MKpEKVAzkw == true){MKpEKVAzkw = false;}
      if(aOPsoBSsdw == true){aOPsoBSsdw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CFBNMVOWNZ
{ 
  void OfcdADnrpG()
  { 
      bool iZlSOjKFGo = false;
      bool SprWMlNNBr = false;
      bool EmpWxHMgHd = false;
      bool LdkDMGYnSB = false;
      bool GcSNrGIohx = false;
      bool AuDrlwiPUG = false;
      bool WcxccnEoKF = false;
      bool MZtzkbTcdq = false;
      bool zXyJcQarRP = false;
      bool XJTLdcepjD = false;
      bool BSdcjaADHJ = false;
      bool bFlcHzdnzM = false;
      bool NLXthDGhUH = false;
      bool xdrZofsVYC = false;
      bool PWkInRWpEe = false;
      bool zqpXpoujtg = false;
      bool TRhzMyNLmb = false;
      bool FIOwwqaOGQ = false;
      bool fPdpIGmUjA = false;
      bool jJbrixnlwp = false;
      string SNLGTTfFYw;
      string ITDYAByinX;
      string SEaJUhYhDm;
      string wdSfIWbBAP;
      string NHFaNdyapT;
      string aXZsXOmClk;
      string uxCkAdAWQc;
      string ZwiYKKyAwp;
      string iyriMXEZHs;
      string jZPOTPFUai;
      string caJMteoAhN;
      string QmFuCwFSYb;
      string YaPWsAfTEu;
      string EdYMNHnfog;
      string iEqscxTUMW;
      string JmwzJBLmSs;
      string yUumIlNsht;
      string IZcqrUiVtw;
      string gLGhkQhZCL;
      string wBMuiOIEkp;
      if(SNLGTTfFYw == caJMteoAhN){iZlSOjKFGo = true;}
      else if(caJMteoAhN == SNLGTTfFYw){BSdcjaADHJ = true;}
      if(ITDYAByinX == QmFuCwFSYb){SprWMlNNBr = true;}
      else if(QmFuCwFSYb == ITDYAByinX){bFlcHzdnzM = true;}
      if(SEaJUhYhDm == YaPWsAfTEu){EmpWxHMgHd = true;}
      else if(YaPWsAfTEu == SEaJUhYhDm){NLXthDGhUH = true;}
      if(wdSfIWbBAP == EdYMNHnfog){LdkDMGYnSB = true;}
      else if(EdYMNHnfog == wdSfIWbBAP){xdrZofsVYC = true;}
      if(NHFaNdyapT == iEqscxTUMW){GcSNrGIohx = true;}
      else if(iEqscxTUMW == NHFaNdyapT){PWkInRWpEe = true;}
      if(aXZsXOmClk == JmwzJBLmSs){AuDrlwiPUG = true;}
      else if(JmwzJBLmSs == aXZsXOmClk){zqpXpoujtg = true;}
      if(uxCkAdAWQc == yUumIlNsht){WcxccnEoKF = true;}
      else if(yUumIlNsht == uxCkAdAWQc){TRhzMyNLmb = true;}
      if(ZwiYKKyAwp == IZcqrUiVtw){MZtzkbTcdq = true;}
      if(iyriMXEZHs == gLGhkQhZCL){zXyJcQarRP = true;}
      if(jZPOTPFUai == wBMuiOIEkp){XJTLdcepjD = true;}
      while(IZcqrUiVtw == ZwiYKKyAwp){FIOwwqaOGQ = true;}
      while(gLGhkQhZCL == gLGhkQhZCL){fPdpIGmUjA = true;}
      while(wBMuiOIEkp == wBMuiOIEkp){jJbrixnlwp = true;}
      if(iZlSOjKFGo == true){iZlSOjKFGo = false;}
      if(SprWMlNNBr == true){SprWMlNNBr = false;}
      if(EmpWxHMgHd == true){EmpWxHMgHd = false;}
      if(LdkDMGYnSB == true){LdkDMGYnSB = false;}
      if(GcSNrGIohx == true){GcSNrGIohx = false;}
      if(AuDrlwiPUG == true){AuDrlwiPUG = false;}
      if(WcxccnEoKF == true){WcxccnEoKF = false;}
      if(MZtzkbTcdq == true){MZtzkbTcdq = false;}
      if(zXyJcQarRP == true){zXyJcQarRP = false;}
      if(XJTLdcepjD == true){XJTLdcepjD = false;}
      if(BSdcjaADHJ == true){BSdcjaADHJ = false;}
      if(bFlcHzdnzM == true){bFlcHzdnzM = false;}
      if(NLXthDGhUH == true){NLXthDGhUH = false;}
      if(xdrZofsVYC == true){xdrZofsVYC = false;}
      if(PWkInRWpEe == true){PWkInRWpEe = false;}
      if(zqpXpoujtg == true){zqpXpoujtg = false;}
      if(TRhzMyNLmb == true){TRhzMyNLmb = false;}
      if(FIOwwqaOGQ == true){FIOwwqaOGQ = false;}
      if(fPdpIGmUjA == true){fPdpIGmUjA = false;}
      if(jJbrixnlwp == true){jJbrixnlwp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RIERTCSAPV
{ 
  void NgBcypqFFY()
  { 
      bool lJHsAYaBRC = false;
      bool WAuPjPTHbM = false;
      bool doskEedYTk = false;
      bool GLknUUKEHk = false;
      bool DwZRyBnxtg = false;
      bool ZSZDVwPWoV = false;
      bool uChguLOHuP = false;
      bool FOAqJgPblD = false;
      bool pfdmKnkhSY = false;
      bool FnPkoBOrVm = false;
      bool lgCebKRisn = false;
      bool gnjkfPXtVH = false;
      bool ZgnVJQzPBI = false;
      bool RWFyQJczLA = false;
      bool WCndqRDdFZ = false;
      bool dTWONFrfVK = false;
      bool LBgkWKhlUW = false;
      bool lYiVjXrKer = false;
      bool MUKbexAqjK = false;
      bool QwdAnUUDHg = false;
      string QdryUBJVON;
      string knUhFBwmPZ;
      string ZofRnwCxNV;
      string xjiAxnNlgw;
      string FlIDHsfjOE;
      string ZVGhpayZJY;
      string zLIrQBEUkQ;
      string nJGTUngbJu;
      string PRiJuacBKV;
      string pmcIwsdPmG;
      string nLyyPPPmMB;
      string tWQNIgcywp;
      string XCKPaBgxWa;
      string JRoDHDSktf;
      string LpnIbTWOzO;
      string QeSwikBiWO;
      string iRPlqbgNGF;
      string OqEQegNBmH;
      string dSyHKdyrTV;
      string BjNexsZCQz;
      if(QdryUBJVON == nLyyPPPmMB){lJHsAYaBRC = true;}
      else if(nLyyPPPmMB == QdryUBJVON){lgCebKRisn = true;}
      if(knUhFBwmPZ == tWQNIgcywp){WAuPjPTHbM = true;}
      else if(tWQNIgcywp == knUhFBwmPZ){gnjkfPXtVH = true;}
      if(ZofRnwCxNV == XCKPaBgxWa){doskEedYTk = true;}
      else if(XCKPaBgxWa == ZofRnwCxNV){ZgnVJQzPBI = true;}
      if(xjiAxnNlgw == JRoDHDSktf){GLknUUKEHk = true;}
      else if(JRoDHDSktf == xjiAxnNlgw){RWFyQJczLA = true;}
      if(FlIDHsfjOE == LpnIbTWOzO){DwZRyBnxtg = true;}
      else if(LpnIbTWOzO == FlIDHsfjOE){WCndqRDdFZ = true;}
      if(ZVGhpayZJY == QeSwikBiWO){ZSZDVwPWoV = true;}
      else if(QeSwikBiWO == ZVGhpayZJY){dTWONFrfVK = true;}
      if(zLIrQBEUkQ == iRPlqbgNGF){uChguLOHuP = true;}
      else if(iRPlqbgNGF == zLIrQBEUkQ){LBgkWKhlUW = true;}
      if(nJGTUngbJu == OqEQegNBmH){FOAqJgPblD = true;}
      if(PRiJuacBKV == dSyHKdyrTV){pfdmKnkhSY = true;}
      if(pmcIwsdPmG == BjNexsZCQz){FnPkoBOrVm = true;}
      while(OqEQegNBmH == nJGTUngbJu){lYiVjXrKer = true;}
      while(dSyHKdyrTV == dSyHKdyrTV){MUKbexAqjK = true;}
      while(BjNexsZCQz == BjNexsZCQz){QwdAnUUDHg = true;}
      if(lJHsAYaBRC == true){lJHsAYaBRC = false;}
      if(WAuPjPTHbM == true){WAuPjPTHbM = false;}
      if(doskEedYTk == true){doskEedYTk = false;}
      if(GLknUUKEHk == true){GLknUUKEHk = false;}
      if(DwZRyBnxtg == true){DwZRyBnxtg = false;}
      if(ZSZDVwPWoV == true){ZSZDVwPWoV = false;}
      if(uChguLOHuP == true){uChguLOHuP = false;}
      if(FOAqJgPblD == true){FOAqJgPblD = false;}
      if(pfdmKnkhSY == true){pfdmKnkhSY = false;}
      if(FnPkoBOrVm == true){FnPkoBOrVm = false;}
      if(lgCebKRisn == true){lgCebKRisn = false;}
      if(gnjkfPXtVH == true){gnjkfPXtVH = false;}
      if(ZgnVJQzPBI == true){ZgnVJQzPBI = false;}
      if(RWFyQJczLA == true){RWFyQJczLA = false;}
      if(WCndqRDdFZ == true){WCndqRDdFZ = false;}
      if(dTWONFrfVK == true){dTWONFrfVK = false;}
      if(LBgkWKhlUW == true){LBgkWKhlUW = false;}
      if(lYiVjXrKer == true){lYiVjXrKer = false;}
      if(MUKbexAqjK == true){MUKbexAqjK = false;}
      if(QwdAnUUDHg == true){QwdAnUUDHg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQRNQVVJPS
{ 
  void JTGpDBEcCo()
  { 
      bool HxgMZGSeuh = false;
      bool ZESAwwgnfs = false;
      bool AEgztTCHHy = false;
      bool XbJohdCRcn = false;
      bool TAuIfPfSun = false;
      bool lhSFLDQgRF = false;
      bool DLXwJyucSR = false;
      bool tPKrZzIYTe = false;
      bool njMSMpJDcd = false;
      bool NUzXkHcyyg = false;
      bool UCzctWXafL = false;
      bool trNmQTzEjT = false;
      bool oqAnDYQlGS = false;
      bool WJZlKljiXo = false;
      bool SiXQjUHLGQ = false;
      bool HXNercCKYV = false;
      bool FkTNojSace = false;
      bool iQgtAGSiEi = false;
      bool REfpKzuutg = false;
      bool iYJCigPKbz = false;
      string FhtOTXBRYj;
      string aokEQRzjTV;
      string NpSzpmHaRw;
      string qQMhmTHZFs;
      string keIDufEcgf;
      string buOkSOPuXf;
      string PazcsKcCQx;
      string JYdajihOEK;
      string ieslTwCbOX;
      string DMBYdKefKk;
      string CBMiVDQnAj;
      string gAqNxkgNIw;
      string HBnrsxWFwY;
      string DBESHhRKPQ;
      string eNaeqDVnbs;
      string dRWNcBNTpY;
      string fLqbfeuXGO;
      string SWyrRtaIBo;
      string bidDuleqpG;
      string UyTqkTVyzL;
      if(FhtOTXBRYj == CBMiVDQnAj){HxgMZGSeuh = true;}
      else if(CBMiVDQnAj == FhtOTXBRYj){UCzctWXafL = true;}
      if(aokEQRzjTV == gAqNxkgNIw){ZESAwwgnfs = true;}
      else if(gAqNxkgNIw == aokEQRzjTV){trNmQTzEjT = true;}
      if(NpSzpmHaRw == HBnrsxWFwY){AEgztTCHHy = true;}
      else if(HBnrsxWFwY == NpSzpmHaRw){oqAnDYQlGS = true;}
      if(qQMhmTHZFs == DBESHhRKPQ){XbJohdCRcn = true;}
      else if(DBESHhRKPQ == qQMhmTHZFs){WJZlKljiXo = true;}
      if(keIDufEcgf == eNaeqDVnbs){TAuIfPfSun = true;}
      else if(eNaeqDVnbs == keIDufEcgf){SiXQjUHLGQ = true;}
      if(buOkSOPuXf == dRWNcBNTpY){lhSFLDQgRF = true;}
      else if(dRWNcBNTpY == buOkSOPuXf){HXNercCKYV = true;}
      if(PazcsKcCQx == fLqbfeuXGO){DLXwJyucSR = true;}
      else if(fLqbfeuXGO == PazcsKcCQx){FkTNojSace = true;}
      if(JYdajihOEK == SWyrRtaIBo){tPKrZzIYTe = true;}
      if(ieslTwCbOX == bidDuleqpG){njMSMpJDcd = true;}
      if(DMBYdKefKk == UyTqkTVyzL){NUzXkHcyyg = true;}
      while(SWyrRtaIBo == JYdajihOEK){iQgtAGSiEi = true;}
      while(bidDuleqpG == bidDuleqpG){REfpKzuutg = true;}
      while(UyTqkTVyzL == UyTqkTVyzL){iYJCigPKbz = true;}
      if(HxgMZGSeuh == true){HxgMZGSeuh = false;}
      if(ZESAwwgnfs == true){ZESAwwgnfs = false;}
      if(AEgztTCHHy == true){AEgztTCHHy = false;}
      if(XbJohdCRcn == true){XbJohdCRcn = false;}
      if(TAuIfPfSun == true){TAuIfPfSun = false;}
      if(lhSFLDQgRF == true){lhSFLDQgRF = false;}
      if(DLXwJyucSR == true){DLXwJyucSR = false;}
      if(tPKrZzIYTe == true){tPKrZzIYTe = false;}
      if(njMSMpJDcd == true){njMSMpJDcd = false;}
      if(NUzXkHcyyg == true){NUzXkHcyyg = false;}
      if(UCzctWXafL == true){UCzctWXafL = false;}
      if(trNmQTzEjT == true){trNmQTzEjT = false;}
      if(oqAnDYQlGS == true){oqAnDYQlGS = false;}
      if(WJZlKljiXo == true){WJZlKljiXo = false;}
      if(SiXQjUHLGQ == true){SiXQjUHLGQ = false;}
      if(HXNercCKYV == true){HXNercCKYV = false;}
      if(FkTNojSace == true){FkTNojSace = false;}
      if(iQgtAGSiEi == true){iQgtAGSiEi = false;}
      if(REfpKzuutg == true){REfpKzuutg = false;}
      if(iYJCigPKbz == true){iYJCigPKbz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JNRJDYBZZE
{ 
  void YAOaQAxqcn()
  { 
      bool PRYoxJLnTW = false;
      bool NYWSrCEdEO = false;
      bool PAgwQcIgiZ = false;
      bool ohUyCacbIw = false;
      bool stTgyGigrM = false;
      bool jUAnUPkbXU = false;
      bool AeFtgfDXQR = false;
      bool YbUHVVfzyK = false;
      bool saoVpUggdm = false;
      bool pBDnuOnZAR = false;
      bool CKQZnHzsRy = false;
      bool ikcNaZojEL = false;
      bool yVtcbXYgLG = false;
      bool hGzgHhJOhi = false;
      bool VnOeEEXpMV = false;
      bool YEUnSfQnyQ = false;
      bool iRgLQblwGr = false;
      bool PaBVpJGPYW = false;
      bool zhUphckKNa = false;
      bool RVQQzDHDNb = false;
      string orJAVPmYHo;
      string cWqLxBYWgw;
      string GzAKQcftih;
      string dyWYqIClFO;
      string HHbTMCIsyf;
      string aqqXBpryjs;
      string jrpYLeARTn;
      string zlQSnzXfxO;
      string TlwCHlHyXB;
      string QDCMePQDIh;
      string CqYJgnaYiB;
      string SLAUZxwmQZ;
      string WBtSXujEnY;
      string hTWPMcNmVT;
      string KiOViEChlg;
      string ScliKAxGlk;
      string EWjKTyokIx;
      string jJRxOnlXiS;
      string rCRGGEhnEL;
      string fGAjOnyECk;
      if(orJAVPmYHo == CqYJgnaYiB){PRYoxJLnTW = true;}
      else if(CqYJgnaYiB == orJAVPmYHo){CKQZnHzsRy = true;}
      if(cWqLxBYWgw == SLAUZxwmQZ){NYWSrCEdEO = true;}
      else if(SLAUZxwmQZ == cWqLxBYWgw){ikcNaZojEL = true;}
      if(GzAKQcftih == WBtSXujEnY){PAgwQcIgiZ = true;}
      else if(WBtSXujEnY == GzAKQcftih){yVtcbXYgLG = true;}
      if(dyWYqIClFO == hTWPMcNmVT){ohUyCacbIw = true;}
      else if(hTWPMcNmVT == dyWYqIClFO){hGzgHhJOhi = true;}
      if(HHbTMCIsyf == KiOViEChlg){stTgyGigrM = true;}
      else if(KiOViEChlg == HHbTMCIsyf){VnOeEEXpMV = true;}
      if(aqqXBpryjs == ScliKAxGlk){jUAnUPkbXU = true;}
      else if(ScliKAxGlk == aqqXBpryjs){YEUnSfQnyQ = true;}
      if(jrpYLeARTn == EWjKTyokIx){AeFtgfDXQR = true;}
      else if(EWjKTyokIx == jrpYLeARTn){iRgLQblwGr = true;}
      if(zlQSnzXfxO == jJRxOnlXiS){YbUHVVfzyK = true;}
      if(TlwCHlHyXB == rCRGGEhnEL){saoVpUggdm = true;}
      if(QDCMePQDIh == fGAjOnyECk){pBDnuOnZAR = true;}
      while(jJRxOnlXiS == zlQSnzXfxO){PaBVpJGPYW = true;}
      while(rCRGGEhnEL == rCRGGEhnEL){zhUphckKNa = true;}
      while(fGAjOnyECk == fGAjOnyECk){RVQQzDHDNb = true;}
      if(PRYoxJLnTW == true){PRYoxJLnTW = false;}
      if(NYWSrCEdEO == true){NYWSrCEdEO = false;}
      if(PAgwQcIgiZ == true){PAgwQcIgiZ = false;}
      if(ohUyCacbIw == true){ohUyCacbIw = false;}
      if(stTgyGigrM == true){stTgyGigrM = false;}
      if(jUAnUPkbXU == true){jUAnUPkbXU = false;}
      if(AeFtgfDXQR == true){AeFtgfDXQR = false;}
      if(YbUHVVfzyK == true){YbUHVVfzyK = false;}
      if(saoVpUggdm == true){saoVpUggdm = false;}
      if(pBDnuOnZAR == true){pBDnuOnZAR = false;}
      if(CKQZnHzsRy == true){CKQZnHzsRy = false;}
      if(ikcNaZojEL == true){ikcNaZojEL = false;}
      if(yVtcbXYgLG == true){yVtcbXYgLG = false;}
      if(hGzgHhJOhi == true){hGzgHhJOhi = false;}
      if(VnOeEEXpMV == true){VnOeEEXpMV = false;}
      if(YEUnSfQnyQ == true){YEUnSfQnyQ = false;}
      if(iRgLQblwGr == true){iRgLQblwGr = false;}
      if(PaBVpJGPYW == true){PaBVpJGPYW = false;}
      if(zhUphckKNa == true){zhUphckKNa = false;}
      if(RVQQzDHDNb == true){RVQQzDHDNb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TFENNDLAUD
{ 
  void qrXkbiITPz()
  { 
      bool GNBcVNdscr = false;
      bool gqzGumJDxN = false;
      bool dfWLortHoV = false;
      bool nOfNQFbGUL = false;
      bool RBLDYdsanz = false;
      bool OMxXBZqomd = false;
      bool SWEGESKlop = false;
      bool KCikwbUTlL = false;
      bool zSSpHaQHLp = false;
      bool OlSqrtxEzG = false;
      bool SGkyoLdLbY = false;
      bool FXDbezDNzc = false;
      bool BDazbXjqrB = false;
      bool ePTerrgUBu = false;
      bool wEeljpiqMr = false;
      bool piEVEPflWQ = false;
      bool bmTatpDXil = false;
      bool SiMEfxXnOk = false;
      bool ordzKuKyac = false;
      bool LuxjTJkErt = false;
      string TfRymUJgEa;
      string GMIxlGyHPC;
      string zLJxQBRdZJ;
      string mghaDdNRLj;
      string JUuTnyDmlJ;
      string tJZeEHVUhk;
      string DfHtmYehtH;
      string sfuesdQpIR;
      string yeqPPdHDVu;
      string HrjZfdMAfP;
      string TUrePNNtka;
      string pfLQmXnqeJ;
      string RbMyAAwVzO;
      string RQKsyclMzC;
      string PMRuFbgSlH;
      string oVVVxqIsdP;
      string QruWIZUSRJ;
      string lbqbsFJRsX;
      string TdiqYuunuG;
      string UshjlXQulf;
      if(TfRymUJgEa == TUrePNNtka){GNBcVNdscr = true;}
      else if(TUrePNNtka == TfRymUJgEa){SGkyoLdLbY = true;}
      if(GMIxlGyHPC == pfLQmXnqeJ){gqzGumJDxN = true;}
      else if(pfLQmXnqeJ == GMIxlGyHPC){FXDbezDNzc = true;}
      if(zLJxQBRdZJ == RbMyAAwVzO){dfWLortHoV = true;}
      else if(RbMyAAwVzO == zLJxQBRdZJ){BDazbXjqrB = true;}
      if(mghaDdNRLj == RQKsyclMzC){nOfNQFbGUL = true;}
      else if(RQKsyclMzC == mghaDdNRLj){ePTerrgUBu = true;}
      if(JUuTnyDmlJ == PMRuFbgSlH){RBLDYdsanz = true;}
      else if(PMRuFbgSlH == JUuTnyDmlJ){wEeljpiqMr = true;}
      if(tJZeEHVUhk == oVVVxqIsdP){OMxXBZqomd = true;}
      else if(oVVVxqIsdP == tJZeEHVUhk){piEVEPflWQ = true;}
      if(DfHtmYehtH == QruWIZUSRJ){SWEGESKlop = true;}
      else if(QruWIZUSRJ == DfHtmYehtH){bmTatpDXil = true;}
      if(sfuesdQpIR == lbqbsFJRsX){KCikwbUTlL = true;}
      if(yeqPPdHDVu == TdiqYuunuG){zSSpHaQHLp = true;}
      if(HrjZfdMAfP == UshjlXQulf){OlSqrtxEzG = true;}
      while(lbqbsFJRsX == sfuesdQpIR){SiMEfxXnOk = true;}
      while(TdiqYuunuG == TdiqYuunuG){ordzKuKyac = true;}
      while(UshjlXQulf == UshjlXQulf){LuxjTJkErt = true;}
      if(GNBcVNdscr == true){GNBcVNdscr = false;}
      if(gqzGumJDxN == true){gqzGumJDxN = false;}
      if(dfWLortHoV == true){dfWLortHoV = false;}
      if(nOfNQFbGUL == true){nOfNQFbGUL = false;}
      if(RBLDYdsanz == true){RBLDYdsanz = false;}
      if(OMxXBZqomd == true){OMxXBZqomd = false;}
      if(SWEGESKlop == true){SWEGESKlop = false;}
      if(KCikwbUTlL == true){KCikwbUTlL = false;}
      if(zSSpHaQHLp == true){zSSpHaQHLp = false;}
      if(OlSqrtxEzG == true){OlSqrtxEzG = false;}
      if(SGkyoLdLbY == true){SGkyoLdLbY = false;}
      if(FXDbezDNzc == true){FXDbezDNzc = false;}
      if(BDazbXjqrB == true){BDazbXjqrB = false;}
      if(ePTerrgUBu == true){ePTerrgUBu = false;}
      if(wEeljpiqMr == true){wEeljpiqMr = false;}
      if(piEVEPflWQ == true){piEVEPflWQ = false;}
      if(bmTatpDXil == true){bmTatpDXil = false;}
      if(SiMEfxXnOk == true){SiMEfxXnOk = false;}
      if(ordzKuKyac == true){ordzKuKyac = false;}
      if(LuxjTJkErt == true){LuxjTJkErt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PSMOJFGAQV
{ 
  void AKcugJtTHx()
  { 
      bool rmiLrSQqVA = false;
      bool JGViFPtnnq = false;
      bool VcgmKIxTjo = false;
      bool pUinCuVSaX = false;
      bool ITHAaLaEfV = false;
      bool oGjgJOGuBi = false;
      bool VwHfKoXggK = false;
      bool taMPiBVfMz = false;
      bool hrmNzjjCem = false;
      bool oaRrCLMapk = false;
      bool msWVbOsUxI = false;
      bool sZiBBcJsfZ = false;
      bool FVCsUSJUNW = false;
      bool otpaLnVQlk = false;
      bool qOEWtPrPqZ = false;
      bool CSuPfRpcBI = false;
      bool EYHaSyjHpM = false;
      bool GrGtipRfzF = false;
      bool atdmTVzZut = false;
      bool xrPdgSHcDu = false;
      string sshMwnRYQs;
      string TbNqccwOAu;
      string LWNzMxkcTz;
      string KGCPpIcRwt;
      string tKHLmYHZpw;
      string LJeZNVfizy;
      string DoFRiNYxBU;
      string AdRGABPBMm;
      string pKmXnAacBT;
      string ctSxpFEpcY;
      string zJXVugrYYM;
      string GdWLIrChch;
      string mwwhrGLTQt;
      string wYXmnfmQbH;
      string ICDoNyWGox;
      string DWNulDNpco;
      string UYHeQgGiXc;
      string FkGVYksGTt;
      string iEeTqYLcBj;
      string RwmlljtYXf;
      if(sshMwnRYQs == zJXVugrYYM){rmiLrSQqVA = true;}
      else if(zJXVugrYYM == sshMwnRYQs){msWVbOsUxI = true;}
      if(TbNqccwOAu == GdWLIrChch){JGViFPtnnq = true;}
      else if(GdWLIrChch == TbNqccwOAu){sZiBBcJsfZ = true;}
      if(LWNzMxkcTz == mwwhrGLTQt){VcgmKIxTjo = true;}
      else if(mwwhrGLTQt == LWNzMxkcTz){FVCsUSJUNW = true;}
      if(KGCPpIcRwt == wYXmnfmQbH){pUinCuVSaX = true;}
      else if(wYXmnfmQbH == KGCPpIcRwt){otpaLnVQlk = true;}
      if(tKHLmYHZpw == ICDoNyWGox){ITHAaLaEfV = true;}
      else if(ICDoNyWGox == tKHLmYHZpw){qOEWtPrPqZ = true;}
      if(LJeZNVfizy == DWNulDNpco){oGjgJOGuBi = true;}
      else if(DWNulDNpco == LJeZNVfizy){CSuPfRpcBI = true;}
      if(DoFRiNYxBU == UYHeQgGiXc){VwHfKoXggK = true;}
      else if(UYHeQgGiXc == DoFRiNYxBU){EYHaSyjHpM = true;}
      if(AdRGABPBMm == FkGVYksGTt){taMPiBVfMz = true;}
      if(pKmXnAacBT == iEeTqYLcBj){hrmNzjjCem = true;}
      if(ctSxpFEpcY == RwmlljtYXf){oaRrCLMapk = true;}
      while(FkGVYksGTt == AdRGABPBMm){GrGtipRfzF = true;}
      while(iEeTqYLcBj == iEeTqYLcBj){atdmTVzZut = true;}
      while(RwmlljtYXf == RwmlljtYXf){xrPdgSHcDu = true;}
      if(rmiLrSQqVA == true){rmiLrSQqVA = false;}
      if(JGViFPtnnq == true){JGViFPtnnq = false;}
      if(VcgmKIxTjo == true){VcgmKIxTjo = false;}
      if(pUinCuVSaX == true){pUinCuVSaX = false;}
      if(ITHAaLaEfV == true){ITHAaLaEfV = false;}
      if(oGjgJOGuBi == true){oGjgJOGuBi = false;}
      if(VwHfKoXggK == true){VwHfKoXggK = false;}
      if(taMPiBVfMz == true){taMPiBVfMz = false;}
      if(hrmNzjjCem == true){hrmNzjjCem = false;}
      if(oaRrCLMapk == true){oaRrCLMapk = false;}
      if(msWVbOsUxI == true){msWVbOsUxI = false;}
      if(sZiBBcJsfZ == true){sZiBBcJsfZ = false;}
      if(FVCsUSJUNW == true){FVCsUSJUNW = false;}
      if(otpaLnVQlk == true){otpaLnVQlk = false;}
      if(qOEWtPrPqZ == true){qOEWtPrPqZ = false;}
      if(CSuPfRpcBI == true){CSuPfRpcBI = false;}
      if(EYHaSyjHpM == true){EYHaSyjHpM = false;}
      if(GrGtipRfzF == true){GrGtipRfzF = false;}
      if(atdmTVzZut == true){atdmTVzZut = false;}
      if(xrPdgSHcDu == true){xrPdgSHcDu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCTSPSTLYE
{ 
  void eTeUZxAKOp()
  { 
      bool NfzggoIlVT = false;
      bool ttAykydHoT = false;
      bool gQtoAmWBRH = false;
      bool TFUBeOAXHR = false;
      bool RsgAsRaFwL = false;
      bool koatAxlKgs = false;
      bool SHUOznYzTW = false;
      bool xFzWCnjtui = false;
      bool MREFVddaAg = false;
      bool bpqNzJXRAE = false;
      bool rbkYNepEqM = false;
      bool NrOxgACOrU = false;
      bool KyyltHNkWr = false;
      bool PRtqqkgerq = false;
      bool nYinTjbtgz = false;
      bool HJYetscyeF = false;
      bool QEhzwuxXGw = false;
      bool TWVBgkOJSJ = false;
      bool fTEXkGsOwx = false;
      bool HhAlZiqjrY = false;
      string IDxCOMnoVT;
      string yczdtkfKYg;
      string WKceSyPDJA;
      string POMlyWgsNS;
      string WSTSePjrpZ;
      string OfneQxZSjQ;
      string xjeVEjQNeX;
      string DlxGKEqKzD;
      string NXNjkiZgUB;
      string xNJxVlmyOu;
      string zWMRVbigUM;
      string GPSgDYVujV;
      string JirdapczkX;
      string RsuEDpKuNI;
      string zsMIthuctw;
      string PqNskPdiqf;
      string zjwwtMTOcM;
      string OahaWQViis;
      string uAFoHafCTm;
      string LaDgJOwQOh;
      if(IDxCOMnoVT == zWMRVbigUM){NfzggoIlVT = true;}
      else if(zWMRVbigUM == IDxCOMnoVT){rbkYNepEqM = true;}
      if(yczdtkfKYg == GPSgDYVujV){ttAykydHoT = true;}
      else if(GPSgDYVujV == yczdtkfKYg){NrOxgACOrU = true;}
      if(WKceSyPDJA == JirdapczkX){gQtoAmWBRH = true;}
      else if(JirdapczkX == WKceSyPDJA){KyyltHNkWr = true;}
      if(POMlyWgsNS == RsuEDpKuNI){TFUBeOAXHR = true;}
      else if(RsuEDpKuNI == POMlyWgsNS){PRtqqkgerq = true;}
      if(WSTSePjrpZ == zsMIthuctw){RsgAsRaFwL = true;}
      else if(zsMIthuctw == WSTSePjrpZ){nYinTjbtgz = true;}
      if(OfneQxZSjQ == PqNskPdiqf){koatAxlKgs = true;}
      else if(PqNskPdiqf == OfneQxZSjQ){HJYetscyeF = true;}
      if(xjeVEjQNeX == zjwwtMTOcM){SHUOznYzTW = true;}
      else if(zjwwtMTOcM == xjeVEjQNeX){QEhzwuxXGw = true;}
      if(DlxGKEqKzD == OahaWQViis){xFzWCnjtui = true;}
      if(NXNjkiZgUB == uAFoHafCTm){MREFVddaAg = true;}
      if(xNJxVlmyOu == LaDgJOwQOh){bpqNzJXRAE = true;}
      while(OahaWQViis == DlxGKEqKzD){TWVBgkOJSJ = true;}
      while(uAFoHafCTm == uAFoHafCTm){fTEXkGsOwx = true;}
      while(LaDgJOwQOh == LaDgJOwQOh){HhAlZiqjrY = true;}
      if(NfzggoIlVT == true){NfzggoIlVT = false;}
      if(ttAykydHoT == true){ttAykydHoT = false;}
      if(gQtoAmWBRH == true){gQtoAmWBRH = false;}
      if(TFUBeOAXHR == true){TFUBeOAXHR = false;}
      if(RsgAsRaFwL == true){RsgAsRaFwL = false;}
      if(koatAxlKgs == true){koatAxlKgs = false;}
      if(SHUOznYzTW == true){SHUOznYzTW = false;}
      if(xFzWCnjtui == true){xFzWCnjtui = false;}
      if(MREFVddaAg == true){MREFVddaAg = false;}
      if(bpqNzJXRAE == true){bpqNzJXRAE = false;}
      if(rbkYNepEqM == true){rbkYNepEqM = false;}
      if(NrOxgACOrU == true){NrOxgACOrU = false;}
      if(KyyltHNkWr == true){KyyltHNkWr = false;}
      if(PRtqqkgerq == true){PRtqqkgerq = false;}
      if(nYinTjbtgz == true){nYinTjbtgz = false;}
      if(HJYetscyeF == true){HJYetscyeF = false;}
      if(QEhzwuxXGw == true){QEhzwuxXGw = false;}
      if(TWVBgkOJSJ == true){TWVBgkOJSJ = false;}
      if(fTEXkGsOwx == true){fTEXkGsOwx = false;}
      if(HhAlZiqjrY == true){HhAlZiqjrY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BODUYCQDTA
{ 
  void WTexVPwWbw()
  { 
      bool rcWkeBtQbu = false;
      bool oQECKnBkJt = false;
      bool oUgIosRgSr = false;
      bool gFeeKQnPHq = false;
      bool UCWItGEUru = false;
      bool fOtxWXuNwk = false;
      bool jMxjNikYrt = false;
      bool zlcRYmyXNi = false;
      bool owoXLSLgHm = false;
      bool UZTVGIEltL = false;
      bool UecyutkbYj = false;
      bool ZXANwnWZXu = false;
      bool WDRFYZSHLQ = false;
      bool iLcCNKSqbR = false;
      bool hjIXMxZGZR = false;
      bool kdNznRNXYV = false;
      bool adQHBNtxzk = false;
      bool VfxGNmtsrb = false;
      bool zLgsfEydOu = false;
      bool xuRGpDTBWz = false;
      string aGpnyWmkoI;
      string mlwgMychTc;
      string BnXMRGBSWw;
      string KSdVDPJMNK;
      string fkwKAVkmSC;
      string oWCjSlhdVr;
      string VUNrxUIZdw;
      string oQUJwQqNLu;
      string UOAUHmQsCQ;
      string gfpUnLWEMf;
      string NKJVNYCrmC;
      string uURaWGTrkK;
      string EOWMPIZzUk;
      string smBfhKEdHh;
      string kXFAUMOPyg;
      string qeTCbymwGE;
      string yCXCIITkrM;
      string CojCZfJWrD;
      string tKBmsOSzEj;
      string WIXDihzDqM;
      if(aGpnyWmkoI == NKJVNYCrmC){rcWkeBtQbu = true;}
      else if(NKJVNYCrmC == aGpnyWmkoI){UecyutkbYj = true;}
      if(mlwgMychTc == uURaWGTrkK){oQECKnBkJt = true;}
      else if(uURaWGTrkK == mlwgMychTc){ZXANwnWZXu = true;}
      if(BnXMRGBSWw == EOWMPIZzUk){oUgIosRgSr = true;}
      else if(EOWMPIZzUk == BnXMRGBSWw){WDRFYZSHLQ = true;}
      if(KSdVDPJMNK == smBfhKEdHh){gFeeKQnPHq = true;}
      else if(smBfhKEdHh == KSdVDPJMNK){iLcCNKSqbR = true;}
      if(fkwKAVkmSC == kXFAUMOPyg){UCWItGEUru = true;}
      else if(kXFAUMOPyg == fkwKAVkmSC){hjIXMxZGZR = true;}
      if(oWCjSlhdVr == qeTCbymwGE){fOtxWXuNwk = true;}
      else if(qeTCbymwGE == oWCjSlhdVr){kdNznRNXYV = true;}
      if(VUNrxUIZdw == yCXCIITkrM){jMxjNikYrt = true;}
      else if(yCXCIITkrM == VUNrxUIZdw){adQHBNtxzk = true;}
      if(oQUJwQqNLu == CojCZfJWrD){zlcRYmyXNi = true;}
      if(UOAUHmQsCQ == tKBmsOSzEj){owoXLSLgHm = true;}
      if(gfpUnLWEMf == WIXDihzDqM){UZTVGIEltL = true;}
      while(CojCZfJWrD == oQUJwQqNLu){VfxGNmtsrb = true;}
      while(tKBmsOSzEj == tKBmsOSzEj){zLgsfEydOu = true;}
      while(WIXDihzDqM == WIXDihzDqM){xuRGpDTBWz = true;}
      if(rcWkeBtQbu == true){rcWkeBtQbu = false;}
      if(oQECKnBkJt == true){oQECKnBkJt = false;}
      if(oUgIosRgSr == true){oUgIosRgSr = false;}
      if(gFeeKQnPHq == true){gFeeKQnPHq = false;}
      if(UCWItGEUru == true){UCWItGEUru = false;}
      if(fOtxWXuNwk == true){fOtxWXuNwk = false;}
      if(jMxjNikYrt == true){jMxjNikYrt = false;}
      if(zlcRYmyXNi == true){zlcRYmyXNi = false;}
      if(owoXLSLgHm == true){owoXLSLgHm = false;}
      if(UZTVGIEltL == true){UZTVGIEltL = false;}
      if(UecyutkbYj == true){UecyutkbYj = false;}
      if(ZXANwnWZXu == true){ZXANwnWZXu = false;}
      if(WDRFYZSHLQ == true){WDRFYZSHLQ = false;}
      if(iLcCNKSqbR == true){iLcCNKSqbR = false;}
      if(hjIXMxZGZR == true){hjIXMxZGZR = false;}
      if(kdNznRNXYV == true){kdNznRNXYV = false;}
      if(adQHBNtxzk == true){adQHBNtxzk = false;}
      if(VfxGNmtsrb == true){VfxGNmtsrb = false;}
      if(zLgsfEydOu == true){zLgsfEydOu = false;}
      if(xuRGpDTBWz == true){xuRGpDTBWz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSKHJQJNHK
{ 
  void QDJnUCpTdO()
  { 
      bool ppRbYKMEYK = false;
      bool nhfEXTakAu = false;
      bool wSYdKpAnNj = false;
      bool knzLhkaUPC = false;
      bool fsGFQdjHuI = false;
      bool slCgDXRmQi = false;
      bool JYpnYAhTWm = false;
      bool sGUyPDLSNg = false;
      bool FssEpzlSIJ = false;
      bool SnDfrHCSfQ = false;
      bool uPkHPmQDRz = false;
      bool LyZjcQflxZ = false;
      bool OPKMTECoFH = false;
      bool AslxkoIkoD = false;
      bool hhBIyTNTDa = false;
      bool bQUGBeFXnK = false;
      bool kbyJySMcym = false;
      bool ItxtrgOBOz = false;
      bool pikdfjYfuF = false;
      bool jjwdRGiqJe = false;
      string lQKOFFJrrg;
      string qqrewyQsSN;
      string CcYcboodrO;
      string UuVeqmlFGH;
      string EtGnUHQkzS;
      string RGEHKJrgmP;
      string QfzdMwVNmI;
      string MLlKIHVkIU;
      string YEeYwNpOTh;
      string uERpqYtcbY;
      string kDxpGGUsyC;
      string mGYRqMBZgy;
      string FGsFMHswTj;
      string NsIiiUGoSp;
      string sxQRtnfAye;
      string WTudSeJqcz;
      string MYZNotyoiW;
      string FMHqEIpbLX;
      string asxoMsxeQE;
      string LPLScUWCcz;
      if(lQKOFFJrrg == kDxpGGUsyC){ppRbYKMEYK = true;}
      else if(kDxpGGUsyC == lQKOFFJrrg){uPkHPmQDRz = true;}
      if(qqrewyQsSN == mGYRqMBZgy){nhfEXTakAu = true;}
      else if(mGYRqMBZgy == qqrewyQsSN){LyZjcQflxZ = true;}
      if(CcYcboodrO == FGsFMHswTj){wSYdKpAnNj = true;}
      else if(FGsFMHswTj == CcYcboodrO){OPKMTECoFH = true;}
      if(UuVeqmlFGH == NsIiiUGoSp){knzLhkaUPC = true;}
      else if(NsIiiUGoSp == UuVeqmlFGH){AslxkoIkoD = true;}
      if(EtGnUHQkzS == sxQRtnfAye){fsGFQdjHuI = true;}
      else if(sxQRtnfAye == EtGnUHQkzS){hhBIyTNTDa = true;}
      if(RGEHKJrgmP == WTudSeJqcz){slCgDXRmQi = true;}
      else if(WTudSeJqcz == RGEHKJrgmP){bQUGBeFXnK = true;}
      if(QfzdMwVNmI == MYZNotyoiW){JYpnYAhTWm = true;}
      else if(MYZNotyoiW == QfzdMwVNmI){kbyJySMcym = true;}
      if(MLlKIHVkIU == FMHqEIpbLX){sGUyPDLSNg = true;}
      if(YEeYwNpOTh == asxoMsxeQE){FssEpzlSIJ = true;}
      if(uERpqYtcbY == LPLScUWCcz){SnDfrHCSfQ = true;}
      while(FMHqEIpbLX == MLlKIHVkIU){ItxtrgOBOz = true;}
      while(asxoMsxeQE == asxoMsxeQE){pikdfjYfuF = true;}
      while(LPLScUWCcz == LPLScUWCcz){jjwdRGiqJe = true;}
      if(ppRbYKMEYK == true){ppRbYKMEYK = false;}
      if(nhfEXTakAu == true){nhfEXTakAu = false;}
      if(wSYdKpAnNj == true){wSYdKpAnNj = false;}
      if(knzLhkaUPC == true){knzLhkaUPC = false;}
      if(fsGFQdjHuI == true){fsGFQdjHuI = false;}
      if(slCgDXRmQi == true){slCgDXRmQi = false;}
      if(JYpnYAhTWm == true){JYpnYAhTWm = false;}
      if(sGUyPDLSNg == true){sGUyPDLSNg = false;}
      if(FssEpzlSIJ == true){FssEpzlSIJ = false;}
      if(SnDfrHCSfQ == true){SnDfrHCSfQ = false;}
      if(uPkHPmQDRz == true){uPkHPmQDRz = false;}
      if(LyZjcQflxZ == true){LyZjcQflxZ = false;}
      if(OPKMTECoFH == true){OPKMTECoFH = false;}
      if(AslxkoIkoD == true){AslxkoIkoD = false;}
      if(hhBIyTNTDa == true){hhBIyTNTDa = false;}
      if(bQUGBeFXnK == true){bQUGBeFXnK = false;}
      if(kbyJySMcym == true){kbyJySMcym = false;}
      if(ItxtrgOBOz == true){ItxtrgOBOz = false;}
      if(pikdfjYfuF == true){pikdfjYfuF = false;}
      if(jjwdRGiqJe == true){jjwdRGiqJe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PXFWUGRKLA
{ 
  void XsVCbTywgE()
  { 
      bool sxETjjztzC = false;
      bool wmqMtiNyAZ = false;
      bool xJomJXwjVs = false;
      bool XuNnJdslaJ = false;
      bool cswscMEYxY = false;
      bool dSZMfjHRJM = false;
      bool nOXGeBZCCQ = false;
      bool oaXqxDMuJw = false;
      bool TWlxOEUAIZ = false;
      bool VbbOVNUpOb = false;
      bool mBWgiCuiPb = false;
      bool WLHNsQcaqZ = false;
      bool fZtbtNyIVi = false;
      bool iWghJRAFOM = false;
      bool IljgDJTOUE = false;
      bool jtznuMGtlV = false;
      bool DlMfszeZDa = false;
      bool QXLdRtoNYj = false;
      bool sjnQznXrlw = false;
      bool KFSsJVYEmD = false;
      string DLGttpedWC;
      string mWwGXGQLiY;
      string PALekcZZuS;
      string mSBOPkkfur;
      string IxuxegKfFB;
      string hUQXVCAaIR;
      string QEhDPUVhqm;
      string UkPpQRENzD;
      string RsUskRCcrM;
      string kKWdaDPqhK;
      string KcnSfwFZHD;
      string ylaFzXjoSx;
      string RroeCKOkOM;
      string CMforoEBNn;
      string MbVnNyiQeD;
      string SaYjrSnIPV;
      string gUKtBkFlMK;
      string ShadkoVARD;
      string ayGLsbnuwZ;
      string AulqHrRamc;
      if(DLGttpedWC == KcnSfwFZHD){sxETjjztzC = true;}
      else if(KcnSfwFZHD == DLGttpedWC){mBWgiCuiPb = true;}
      if(mWwGXGQLiY == ylaFzXjoSx){wmqMtiNyAZ = true;}
      else if(ylaFzXjoSx == mWwGXGQLiY){WLHNsQcaqZ = true;}
      if(PALekcZZuS == RroeCKOkOM){xJomJXwjVs = true;}
      else if(RroeCKOkOM == PALekcZZuS){fZtbtNyIVi = true;}
      if(mSBOPkkfur == CMforoEBNn){XuNnJdslaJ = true;}
      else if(CMforoEBNn == mSBOPkkfur){iWghJRAFOM = true;}
      if(IxuxegKfFB == MbVnNyiQeD){cswscMEYxY = true;}
      else if(MbVnNyiQeD == IxuxegKfFB){IljgDJTOUE = true;}
      if(hUQXVCAaIR == SaYjrSnIPV){dSZMfjHRJM = true;}
      else if(SaYjrSnIPV == hUQXVCAaIR){jtznuMGtlV = true;}
      if(QEhDPUVhqm == gUKtBkFlMK){nOXGeBZCCQ = true;}
      else if(gUKtBkFlMK == QEhDPUVhqm){DlMfszeZDa = true;}
      if(UkPpQRENzD == ShadkoVARD){oaXqxDMuJw = true;}
      if(RsUskRCcrM == ayGLsbnuwZ){TWlxOEUAIZ = true;}
      if(kKWdaDPqhK == AulqHrRamc){VbbOVNUpOb = true;}
      while(ShadkoVARD == UkPpQRENzD){QXLdRtoNYj = true;}
      while(ayGLsbnuwZ == ayGLsbnuwZ){sjnQznXrlw = true;}
      while(AulqHrRamc == AulqHrRamc){KFSsJVYEmD = true;}
      if(sxETjjztzC == true){sxETjjztzC = false;}
      if(wmqMtiNyAZ == true){wmqMtiNyAZ = false;}
      if(xJomJXwjVs == true){xJomJXwjVs = false;}
      if(XuNnJdslaJ == true){XuNnJdslaJ = false;}
      if(cswscMEYxY == true){cswscMEYxY = false;}
      if(dSZMfjHRJM == true){dSZMfjHRJM = false;}
      if(nOXGeBZCCQ == true){nOXGeBZCCQ = false;}
      if(oaXqxDMuJw == true){oaXqxDMuJw = false;}
      if(TWlxOEUAIZ == true){TWlxOEUAIZ = false;}
      if(VbbOVNUpOb == true){VbbOVNUpOb = false;}
      if(mBWgiCuiPb == true){mBWgiCuiPb = false;}
      if(WLHNsQcaqZ == true){WLHNsQcaqZ = false;}
      if(fZtbtNyIVi == true){fZtbtNyIVi = false;}
      if(iWghJRAFOM == true){iWghJRAFOM = false;}
      if(IljgDJTOUE == true){IljgDJTOUE = false;}
      if(jtznuMGtlV == true){jtznuMGtlV = false;}
      if(DlMfszeZDa == true){DlMfszeZDa = false;}
      if(QXLdRtoNYj == true){QXLdRtoNYj = false;}
      if(sjnQznXrlw == true){sjnQznXrlw = false;}
      if(KFSsJVYEmD == true){KFSsJVYEmD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TEQLZLOQEM
{ 
  void WoxcdOAfEW()
  { 
      bool JJCtTxiwaH = false;
      bool PrDsfBEpTq = false;
      bool yFcGbolFuI = false;
      bool aRLRoAzuVx = false;
      bool MTRISEqUag = false;
      bool ENfnsDguSd = false;
      bool LcARgxflEf = false;
      bool CITWeenTnW = false;
      bool yQeNENkXYk = false;
      bool TDcqljSzbU = false;
      bool YFQueusJIO = false;
      bool PMHwftylNT = false;
      bool LINTMyfbku = false;
      bool LnrTxrAiiI = false;
      bool UbOJUGwfLq = false;
      bool kflIIPrwhf = false;
      bool PQYNCbTnyn = false;
      bool sODEyjsDzF = false;
      bool CAQsJfBjKh = false;
      bool zEADsDCBGs = false;
      string LaefPhRjWa;
      string ImlZXRVtga;
      string SYrdxgxCWV;
      string xiicxZCfJk;
      string XTqraSEHwU;
      string loXLdliAii;
      string jPMAdZEJcx;
      string PojuCygzDd;
      string boGCiILXyL;
      string qBwaAIGqOA;
      string OteyExEbIe;
      string EixEGuIKQV;
      string OfKQGOsJut;
      string rpkDPgJHxl;
      string DjOSGHEqTF;
      string zwZrlhjOrp;
      string DtfOmOytoY;
      string kBMdRdRqKy;
      string KBppuuPrQh;
      string xuOHiIDzer;
      if(LaefPhRjWa == OteyExEbIe){JJCtTxiwaH = true;}
      else if(OteyExEbIe == LaefPhRjWa){YFQueusJIO = true;}
      if(ImlZXRVtga == EixEGuIKQV){PrDsfBEpTq = true;}
      else if(EixEGuIKQV == ImlZXRVtga){PMHwftylNT = true;}
      if(SYrdxgxCWV == OfKQGOsJut){yFcGbolFuI = true;}
      else if(OfKQGOsJut == SYrdxgxCWV){LINTMyfbku = true;}
      if(xiicxZCfJk == rpkDPgJHxl){aRLRoAzuVx = true;}
      else if(rpkDPgJHxl == xiicxZCfJk){LnrTxrAiiI = true;}
      if(XTqraSEHwU == DjOSGHEqTF){MTRISEqUag = true;}
      else if(DjOSGHEqTF == XTqraSEHwU){UbOJUGwfLq = true;}
      if(loXLdliAii == zwZrlhjOrp){ENfnsDguSd = true;}
      else if(zwZrlhjOrp == loXLdliAii){kflIIPrwhf = true;}
      if(jPMAdZEJcx == DtfOmOytoY){LcARgxflEf = true;}
      else if(DtfOmOytoY == jPMAdZEJcx){PQYNCbTnyn = true;}
      if(PojuCygzDd == kBMdRdRqKy){CITWeenTnW = true;}
      if(boGCiILXyL == KBppuuPrQh){yQeNENkXYk = true;}
      if(qBwaAIGqOA == xuOHiIDzer){TDcqljSzbU = true;}
      while(kBMdRdRqKy == PojuCygzDd){sODEyjsDzF = true;}
      while(KBppuuPrQh == KBppuuPrQh){CAQsJfBjKh = true;}
      while(xuOHiIDzer == xuOHiIDzer){zEADsDCBGs = true;}
      if(JJCtTxiwaH == true){JJCtTxiwaH = false;}
      if(PrDsfBEpTq == true){PrDsfBEpTq = false;}
      if(yFcGbolFuI == true){yFcGbolFuI = false;}
      if(aRLRoAzuVx == true){aRLRoAzuVx = false;}
      if(MTRISEqUag == true){MTRISEqUag = false;}
      if(ENfnsDguSd == true){ENfnsDguSd = false;}
      if(LcARgxflEf == true){LcARgxflEf = false;}
      if(CITWeenTnW == true){CITWeenTnW = false;}
      if(yQeNENkXYk == true){yQeNENkXYk = false;}
      if(TDcqljSzbU == true){TDcqljSzbU = false;}
      if(YFQueusJIO == true){YFQueusJIO = false;}
      if(PMHwftylNT == true){PMHwftylNT = false;}
      if(LINTMyfbku == true){LINTMyfbku = false;}
      if(LnrTxrAiiI == true){LnrTxrAiiI = false;}
      if(UbOJUGwfLq == true){UbOJUGwfLq = false;}
      if(kflIIPrwhf == true){kflIIPrwhf = false;}
      if(PQYNCbTnyn == true){PQYNCbTnyn = false;}
      if(sODEyjsDzF == true){sODEyjsDzF = false;}
      if(CAQsJfBjKh == true){CAQsJfBjKh = false;}
      if(zEADsDCBGs == true){zEADsDCBGs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TOZZQCEGKQ
{ 
  void YmMrrztbIH()
  { 
      bool xOPcZooVzI = false;
      bool CkfEfQRVxO = false;
      bool hsFkIsNwJz = false;
      bool hyBmMhZlkf = false;
      bool oAmodwQNKG = false;
      bool AtmzyEJeUg = false;
      bool asMAZDjsry = false;
      bool qfkQZgFPGL = false;
      bool bzkDynLBoI = false;
      bool XtRDFwmmOa = false;
      bool MWVMOUJVZQ = false;
      bool ysXIEaHJBl = false;
      bool rhEiZwOgLc = false;
      bool tSAfyEdXnd = false;
      bool dobXJeVIzd = false;
      bool ndkcieSlmR = false;
      bool FcJxWfrrKz = false;
      bool xjUXICGfYt = false;
      bool ZGhgnPgXxS = false;
      bool lqkVXBfeBd = false;
      string ojUgAJnRms;
      string qtcEreaJSK;
      string tUJGJPXoxV;
      string Kqxxjpnnen;
      string iEfTBUFXFj;
      string OtlkoTaNXj;
      string lyURiAxfTC;
      string plddapooFn;
      string JzjMGQELHP;
      string OaPtCjiOjB;
      string WZDCscPIJz;
      string ekHialOHKS;
      string ukXDmPViaq;
      string GZFERjwgTd;
      string AwCHkdSgTP;
      string VbDRGkBzOc;
      string GggSsEfDRq;
      string pgmgSyiPSJ;
      string xoOKUdWmxf;
      string hwSqWSPjOf;
      if(ojUgAJnRms == WZDCscPIJz){xOPcZooVzI = true;}
      else if(WZDCscPIJz == ojUgAJnRms){MWVMOUJVZQ = true;}
      if(qtcEreaJSK == ekHialOHKS){CkfEfQRVxO = true;}
      else if(ekHialOHKS == qtcEreaJSK){ysXIEaHJBl = true;}
      if(tUJGJPXoxV == ukXDmPViaq){hsFkIsNwJz = true;}
      else if(ukXDmPViaq == tUJGJPXoxV){rhEiZwOgLc = true;}
      if(Kqxxjpnnen == GZFERjwgTd){hyBmMhZlkf = true;}
      else if(GZFERjwgTd == Kqxxjpnnen){tSAfyEdXnd = true;}
      if(iEfTBUFXFj == AwCHkdSgTP){oAmodwQNKG = true;}
      else if(AwCHkdSgTP == iEfTBUFXFj){dobXJeVIzd = true;}
      if(OtlkoTaNXj == VbDRGkBzOc){AtmzyEJeUg = true;}
      else if(VbDRGkBzOc == OtlkoTaNXj){ndkcieSlmR = true;}
      if(lyURiAxfTC == GggSsEfDRq){asMAZDjsry = true;}
      else if(GggSsEfDRq == lyURiAxfTC){FcJxWfrrKz = true;}
      if(plddapooFn == pgmgSyiPSJ){qfkQZgFPGL = true;}
      if(JzjMGQELHP == xoOKUdWmxf){bzkDynLBoI = true;}
      if(OaPtCjiOjB == hwSqWSPjOf){XtRDFwmmOa = true;}
      while(pgmgSyiPSJ == plddapooFn){xjUXICGfYt = true;}
      while(xoOKUdWmxf == xoOKUdWmxf){ZGhgnPgXxS = true;}
      while(hwSqWSPjOf == hwSqWSPjOf){lqkVXBfeBd = true;}
      if(xOPcZooVzI == true){xOPcZooVzI = false;}
      if(CkfEfQRVxO == true){CkfEfQRVxO = false;}
      if(hsFkIsNwJz == true){hsFkIsNwJz = false;}
      if(hyBmMhZlkf == true){hyBmMhZlkf = false;}
      if(oAmodwQNKG == true){oAmodwQNKG = false;}
      if(AtmzyEJeUg == true){AtmzyEJeUg = false;}
      if(asMAZDjsry == true){asMAZDjsry = false;}
      if(qfkQZgFPGL == true){qfkQZgFPGL = false;}
      if(bzkDynLBoI == true){bzkDynLBoI = false;}
      if(XtRDFwmmOa == true){XtRDFwmmOa = false;}
      if(MWVMOUJVZQ == true){MWVMOUJVZQ = false;}
      if(ysXIEaHJBl == true){ysXIEaHJBl = false;}
      if(rhEiZwOgLc == true){rhEiZwOgLc = false;}
      if(tSAfyEdXnd == true){tSAfyEdXnd = false;}
      if(dobXJeVIzd == true){dobXJeVIzd = false;}
      if(ndkcieSlmR == true){ndkcieSlmR = false;}
      if(FcJxWfrrKz == true){FcJxWfrrKz = false;}
      if(xjUXICGfYt == true){xjUXICGfYt = false;}
      if(ZGhgnPgXxS == true){ZGhgnPgXxS = false;}
      if(lqkVXBfeBd == true){lqkVXBfeBd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PAQHCEXIRP
{ 
  void EOpNrorwXz()
  { 
      bool kEAoycgGil = false;
      bool ruCsCBPtkw = false;
      bool bCLkwGYRMm = false;
      bool ZDraqqKTjE = false;
      bool rsRtpMXQay = false;
      bool GCjUjhsOsq = false;
      bool DOtuMnCbBK = false;
      bool quKgDikQui = false;
      bool iIqOgWTWpJ = false;
      bool yuarAdzWhB = false;
      bool JuOPHLrCQA = false;
      bool wbTJIuXeNo = false;
      bool TekrMuTRfZ = false;
      bool jNisYmtaGV = false;
      bool eQGoMWaRjF = false;
      bool GTIrgdKVDM = false;
      bool qZWqQirajU = false;
      bool AwYrJDYufp = false;
      bool TChZTQEqLu = false;
      bool cXWtdFtOYd = false;
      string EDtetogVAh;
      string QAoHbgHuBU;
      string nsOPdRJEgS;
      string HCiiwZInkI;
      string BmcXUyFbnO;
      string LljfYLndAb;
      string ecnhaORGLC;
      string XSKrSAPquf;
      string LgPRGVRCKj;
      string kenIdYyuxF;
      string fzQlqraqNX;
      string wxhTPxMWaE;
      string wOuaQseCOs;
      string BTspALQdaN;
      string uZolnnxTsf;
      string LbTrIREpUy;
      string NYcTVbDrTD;
      string ghuNJWYImb;
      string wLJhhZzAgh;
      string HZJcAVwVQM;
      if(EDtetogVAh == fzQlqraqNX){kEAoycgGil = true;}
      else if(fzQlqraqNX == EDtetogVAh){JuOPHLrCQA = true;}
      if(QAoHbgHuBU == wxhTPxMWaE){ruCsCBPtkw = true;}
      else if(wxhTPxMWaE == QAoHbgHuBU){wbTJIuXeNo = true;}
      if(nsOPdRJEgS == wOuaQseCOs){bCLkwGYRMm = true;}
      else if(wOuaQseCOs == nsOPdRJEgS){TekrMuTRfZ = true;}
      if(HCiiwZInkI == BTspALQdaN){ZDraqqKTjE = true;}
      else if(BTspALQdaN == HCiiwZInkI){jNisYmtaGV = true;}
      if(BmcXUyFbnO == uZolnnxTsf){rsRtpMXQay = true;}
      else if(uZolnnxTsf == BmcXUyFbnO){eQGoMWaRjF = true;}
      if(LljfYLndAb == LbTrIREpUy){GCjUjhsOsq = true;}
      else if(LbTrIREpUy == LljfYLndAb){GTIrgdKVDM = true;}
      if(ecnhaORGLC == NYcTVbDrTD){DOtuMnCbBK = true;}
      else if(NYcTVbDrTD == ecnhaORGLC){qZWqQirajU = true;}
      if(XSKrSAPquf == ghuNJWYImb){quKgDikQui = true;}
      if(LgPRGVRCKj == wLJhhZzAgh){iIqOgWTWpJ = true;}
      if(kenIdYyuxF == HZJcAVwVQM){yuarAdzWhB = true;}
      while(ghuNJWYImb == XSKrSAPquf){AwYrJDYufp = true;}
      while(wLJhhZzAgh == wLJhhZzAgh){TChZTQEqLu = true;}
      while(HZJcAVwVQM == HZJcAVwVQM){cXWtdFtOYd = true;}
      if(kEAoycgGil == true){kEAoycgGil = false;}
      if(ruCsCBPtkw == true){ruCsCBPtkw = false;}
      if(bCLkwGYRMm == true){bCLkwGYRMm = false;}
      if(ZDraqqKTjE == true){ZDraqqKTjE = false;}
      if(rsRtpMXQay == true){rsRtpMXQay = false;}
      if(GCjUjhsOsq == true){GCjUjhsOsq = false;}
      if(DOtuMnCbBK == true){DOtuMnCbBK = false;}
      if(quKgDikQui == true){quKgDikQui = false;}
      if(iIqOgWTWpJ == true){iIqOgWTWpJ = false;}
      if(yuarAdzWhB == true){yuarAdzWhB = false;}
      if(JuOPHLrCQA == true){JuOPHLrCQA = false;}
      if(wbTJIuXeNo == true){wbTJIuXeNo = false;}
      if(TekrMuTRfZ == true){TekrMuTRfZ = false;}
      if(jNisYmtaGV == true){jNisYmtaGV = false;}
      if(eQGoMWaRjF == true){eQGoMWaRjF = false;}
      if(GTIrgdKVDM == true){GTIrgdKVDM = false;}
      if(qZWqQirajU == true){qZWqQirajU = false;}
      if(AwYrJDYufp == true){AwYrJDYufp = false;}
      if(TChZTQEqLu == true){TChZTQEqLu = false;}
      if(cXWtdFtOYd == true){cXWtdFtOYd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DLSMBEMYNC
{ 
  void EPQbELYzJQ()
  { 
      bool mueLUKpdSo = false;
      bool ZefXCiGYuL = false;
      bool GfDFzzDMNZ = false;
      bool yykuZsKKtt = false;
      bool MDDcnUjhQY = false;
      bool mBZjnHrZMV = false;
      bool GcPrpbtjxJ = false;
      bool XweByDbaQd = false;
      bool OVuomxXAHS = false;
      bool BkyXmimKlM = false;
      bool azkHApVYkk = false;
      bool eQIhGkhaEs = false;
      bool DscdHlxGNO = false;
      bool PRnDDOknnx = false;
      bool azPVnjbQQC = false;
      bool BLFsJhWGzO = false;
      bool sOKWUMcEer = false;
      bool AslHREdGoX = false;
      bool JgpLMELutV = false;
      bool rdnZELnrAb = false;
      string grIgXuAXXW;
      string WGFhCTJyKw;
      string tfraNAJUZZ;
      string xeSSEzystX;
      string AJyEsWmZpS;
      string eOaVWBzgSX;
      string kexxZrmlcC;
      string VPDlujgngq;
      string MjeHuhDxwD;
      string AQaVlULAeB;
      string iBwmwOKnal;
      string TLAbKBApBq;
      string nppZCFogzZ;
      string XfJeHLmqKg;
      string WOWJioQzKj;
      string UVzmNsLWkq;
      string YcnANnBUTz;
      string OJfUTYTfqN;
      string opWPFCgVRO;
      string APFSHsZVuu;
      if(grIgXuAXXW == iBwmwOKnal){mueLUKpdSo = true;}
      else if(iBwmwOKnal == grIgXuAXXW){azkHApVYkk = true;}
      if(WGFhCTJyKw == TLAbKBApBq){ZefXCiGYuL = true;}
      else if(TLAbKBApBq == WGFhCTJyKw){eQIhGkhaEs = true;}
      if(tfraNAJUZZ == nppZCFogzZ){GfDFzzDMNZ = true;}
      else if(nppZCFogzZ == tfraNAJUZZ){DscdHlxGNO = true;}
      if(xeSSEzystX == XfJeHLmqKg){yykuZsKKtt = true;}
      else if(XfJeHLmqKg == xeSSEzystX){PRnDDOknnx = true;}
      if(AJyEsWmZpS == WOWJioQzKj){MDDcnUjhQY = true;}
      else if(WOWJioQzKj == AJyEsWmZpS){azPVnjbQQC = true;}
      if(eOaVWBzgSX == UVzmNsLWkq){mBZjnHrZMV = true;}
      else if(UVzmNsLWkq == eOaVWBzgSX){BLFsJhWGzO = true;}
      if(kexxZrmlcC == YcnANnBUTz){GcPrpbtjxJ = true;}
      else if(YcnANnBUTz == kexxZrmlcC){sOKWUMcEer = true;}
      if(VPDlujgngq == OJfUTYTfqN){XweByDbaQd = true;}
      if(MjeHuhDxwD == opWPFCgVRO){OVuomxXAHS = true;}
      if(AQaVlULAeB == APFSHsZVuu){BkyXmimKlM = true;}
      while(OJfUTYTfqN == VPDlujgngq){AslHREdGoX = true;}
      while(opWPFCgVRO == opWPFCgVRO){JgpLMELutV = true;}
      while(APFSHsZVuu == APFSHsZVuu){rdnZELnrAb = true;}
      if(mueLUKpdSo == true){mueLUKpdSo = false;}
      if(ZefXCiGYuL == true){ZefXCiGYuL = false;}
      if(GfDFzzDMNZ == true){GfDFzzDMNZ = false;}
      if(yykuZsKKtt == true){yykuZsKKtt = false;}
      if(MDDcnUjhQY == true){MDDcnUjhQY = false;}
      if(mBZjnHrZMV == true){mBZjnHrZMV = false;}
      if(GcPrpbtjxJ == true){GcPrpbtjxJ = false;}
      if(XweByDbaQd == true){XweByDbaQd = false;}
      if(OVuomxXAHS == true){OVuomxXAHS = false;}
      if(BkyXmimKlM == true){BkyXmimKlM = false;}
      if(azkHApVYkk == true){azkHApVYkk = false;}
      if(eQIhGkhaEs == true){eQIhGkhaEs = false;}
      if(DscdHlxGNO == true){DscdHlxGNO = false;}
      if(PRnDDOknnx == true){PRnDDOknnx = false;}
      if(azPVnjbQQC == true){azPVnjbQQC = false;}
      if(BLFsJhWGzO == true){BLFsJhWGzO = false;}
      if(sOKWUMcEer == true){sOKWUMcEer = false;}
      if(AslHREdGoX == true){AslHREdGoX = false;}
      if(JgpLMELutV == true){JgpLMELutV = false;}
      if(rdnZELnrAb == true){rdnZELnrAb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWXSYJQUML
{ 
  void lAAEkbSWMu()
  { 
      bool mlhYqcCsga = false;
      bool oMFQMLYbVb = false;
      bool oNONwpadGD = false;
      bool roeCNVcggh = false;
      bool AqXuCTqbja = false;
      bool nLxmjZWUcB = false;
      bool CXlchzgCCq = false;
      bool iqtmbyoTKb = false;
      bool yysfPfrqRn = false;
      bool yHEffcEuMD = false;
      bool loZsqwRJLl = false;
      bool kDKACDeGMB = false;
      bool HojOrbmNHy = false;
      bool tsHGpJYznS = false;
      bool OhffDuwEdb = false;
      bool yyhKwwEKBP = false;
      bool JDCMqqwEJs = false;
      bool eeRtlYJDKx = false;
      bool ehjfAwKwJt = false;
      bool ENyXILfSoM = false;
      string CpTDspQsQg;
      string KaUntWJzIn;
      string noIyJlfwgh;
      string qwYWLJGbYI;
      string ziZxqLxnJP;
      string CMEfPMhVsG;
      string KTLioNCxbj;
      string PgZAoEOLGy;
      string oqmReerrGy;
      string bkiSxeXqIc;
      string IzLZzVlDqL;
      string yVOuRSgtDJ;
      string VKqcHeyHDJ;
      string fXDdpofMSJ;
      string rnBuAFWmBd;
      string ydmyHyIhSU;
      string WeAgeZSjFb;
      string mUbtRgJucB;
      string HKGYLCjFVr;
      string fxsxmNnTPZ;
      if(CpTDspQsQg == IzLZzVlDqL){mlhYqcCsga = true;}
      else if(IzLZzVlDqL == CpTDspQsQg){loZsqwRJLl = true;}
      if(KaUntWJzIn == yVOuRSgtDJ){oMFQMLYbVb = true;}
      else if(yVOuRSgtDJ == KaUntWJzIn){kDKACDeGMB = true;}
      if(noIyJlfwgh == VKqcHeyHDJ){oNONwpadGD = true;}
      else if(VKqcHeyHDJ == noIyJlfwgh){HojOrbmNHy = true;}
      if(qwYWLJGbYI == fXDdpofMSJ){roeCNVcggh = true;}
      else if(fXDdpofMSJ == qwYWLJGbYI){tsHGpJYznS = true;}
      if(ziZxqLxnJP == rnBuAFWmBd){AqXuCTqbja = true;}
      else if(rnBuAFWmBd == ziZxqLxnJP){OhffDuwEdb = true;}
      if(CMEfPMhVsG == ydmyHyIhSU){nLxmjZWUcB = true;}
      else if(ydmyHyIhSU == CMEfPMhVsG){yyhKwwEKBP = true;}
      if(KTLioNCxbj == WeAgeZSjFb){CXlchzgCCq = true;}
      else if(WeAgeZSjFb == KTLioNCxbj){JDCMqqwEJs = true;}
      if(PgZAoEOLGy == mUbtRgJucB){iqtmbyoTKb = true;}
      if(oqmReerrGy == HKGYLCjFVr){yysfPfrqRn = true;}
      if(bkiSxeXqIc == fxsxmNnTPZ){yHEffcEuMD = true;}
      while(mUbtRgJucB == PgZAoEOLGy){eeRtlYJDKx = true;}
      while(HKGYLCjFVr == HKGYLCjFVr){ehjfAwKwJt = true;}
      while(fxsxmNnTPZ == fxsxmNnTPZ){ENyXILfSoM = true;}
      if(mlhYqcCsga == true){mlhYqcCsga = false;}
      if(oMFQMLYbVb == true){oMFQMLYbVb = false;}
      if(oNONwpadGD == true){oNONwpadGD = false;}
      if(roeCNVcggh == true){roeCNVcggh = false;}
      if(AqXuCTqbja == true){AqXuCTqbja = false;}
      if(nLxmjZWUcB == true){nLxmjZWUcB = false;}
      if(CXlchzgCCq == true){CXlchzgCCq = false;}
      if(iqtmbyoTKb == true){iqtmbyoTKb = false;}
      if(yysfPfrqRn == true){yysfPfrqRn = false;}
      if(yHEffcEuMD == true){yHEffcEuMD = false;}
      if(loZsqwRJLl == true){loZsqwRJLl = false;}
      if(kDKACDeGMB == true){kDKACDeGMB = false;}
      if(HojOrbmNHy == true){HojOrbmNHy = false;}
      if(tsHGpJYznS == true){tsHGpJYznS = false;}
      if(OhffDuwEdb == true){OhffDuwEdb = false;}
      if(yyhKwwEKBP == true){yyhKwwEKBP = false;}
      if(JDCMqqwEJs == true){JDCMqqwEJs = false;}
      if(eeRtlYJDKx == true){eeRtlYJDKx = false;}
      if(ehjfAwKwJt == true){ehjfAwKwJt = false;}
      if(ENyXILfSoM == true){ENyXILfSoM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GFULPCFXWB
{ 
  void nSAlUTfCBR()
  { 
      bool uSrxAyMosi = false;
      bool HHnlVbxWqT = false;
      bool GaqGTLrqpF = false;
      bool fgOZfdObGj = false;
      bool MirejaQRPp = false;
      bool RVPnaUalcn = false;
      bool GVynDZsOFq = false;
      bool NUQGGWiMWr = false;
      bool tZaAmJRZzL = false;
      bool DczRdqkEaK = false;
      bool hCMYcxFIhD = false;
      bool kOPjsftyAs = false;
      bool HSPsnkVybO = false;
      bool lekLKrNCWp = false;
      bool EIruaoNOYx = false;
      bool xlEhCOmSkr = false;
      bool aGgSRFcDZB = false;
      bool SrbJnzaTRz = false;
      bool XHZdRzaDJu = false;
      bool FtQePybYdV = false;
      string aLTSgLHZpD;
      string NntoKgtejh;
      string iodLcDXZBt;
      string PofJDDJSqY;
      string suGJfYnDGJ;
      string JhNtxlhIpd;
      string mhYwnYHklH;
      string WbmKomhUeE;
      string PTSqjgalMQ;
      string VBcNkKWKUH;
      string QCRzmhuDEJ;
      string DMclOTPgLG;
      string xVYUkUyYYd;
      string PXzXmMCSEC;
      string lXgCNIXqzR;
      string upyOJudwOS;
      string iWdatfMFyC;
      string RwcJUZnWHb;
      string wHZGiZYkNq;
      string hFElSOsGIh;
      if(aLTSgLHZpD == QCRzmhuDEJ){uSrxAyMosi = true;}
      else if(QCRzmhuDEJ == aLTSgLHZpD){hCMYcxFIhD = true;}
      if(NntoKgtejh == DMclOTPgLG){HHnlVbxWqT = true;}
      else if(DMclOTPgLG == NntoKgtejh){kOPjsftyAs = true;}
      if(iodLcDXZBt == xVYUkUyYYd){GaqGTLrqpF = true;}
      else if(xVYUkUyYYd == iodLcDXZBt){HSPsnkVybO = true;}
      if(PofJDDJSqY == PXzXmMCSEC){fgOZfdObGj = true;}
      else if(PXzXmMCSEC == PofJDDJSqY){lekLKrNCWp = true;}
      if(suGJfYnDGJ == lXgCNIXqzR){MirejaQRPp = true;}
      else if(lXgCNIXqzR == suGJfYnDGJ){EIruaoNOYx = true;}
      if(JhNtxlhIpd == upyOJudwOS){RVPnaUalcn = true;}
      else if(upyOJudwOS == JhNtxlhIpd){xlEhCOmSkr = true;}
      if(mhYwnYHklH == iWdatfMFyC){GVynDZsOFq = true;}
      else if(iWdatfMFyC == mhYwnYHklH){aGgSRFcDZB = true;}
      if(WbmKomhUeE == RwcJUZnWHb){NUQGGWiMWr = true;}
      if(PTSqjgalMQ == wHZGiZYkNq){tZaAmJRZzL = true;}
      if(VBcNkKWKUH == hFElSOsGIh){DczRdqkEaK = true;}
      while(RwcJUZnWHb == WbmKomhUeE){SrbJnzaTRz = true;}
      while(wHZGiZYkNq == wHZGiZYkNq){XHZdRzaDJu = true;}
      while(hFElSOsGIh == hFElSOsGIh){FtQePybYdV = true;}
      if(uSrxAyMosi == true){uSrxAyMosi = false;}
      if(HHnlVbxWqT == true){HHnlVbxWqT = false;}
      if(GaqGTLrqpF == true){GaqGTLrqpF = false;}
      if(fgOZfdObGj == true){fgOZfdObGj = false;}
      if(MirejaQRPp == true){MirejaQRPp = false;}
      if(RVPnaUalcn == true){RVPnaUalcn = false;}
      if(GVynDZsOFq == true){GVynDZsOFq = false;}
      if(NUQGGWiMWr == true){NUQGGWiMWr = false;}
      if(tZaAmJRZzL == true){tZaAmJRZzL = false;}
      if(DczRdqkEaK == true){DczRdqkEaK = false;}
      if(hCMYcxFIhD == true){hCMYcxFIhD = false;}
      if(kOPjsftyAs == true){kOPjsftyAs = false;}
      if(HSPsnkVybO == true){HSPsnkVybO = false;}
      if(lekLKrNCWp == true){lekLKrNCWp = false;}
      if(EIruaoNOYx == true){EIruaoNOYx = false;}
      if(xlEhCOmSkr == true){xlEhCOmSkr = false;}
      if(aGgSRFcDZB == true){aGgSRFcDZB = false;}
      if(SrbJnzaTRz == true){SrbJnzaTRz = false;}
      if(XHZdRzaDJu == true){XHZdRzaDJu = false;}
      if(FtQePybYdV == true){FtQePybYdV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ODBKPIQQAZ
{ 
  void KfCGpWgDWk()
  { 
      bool wKAWhaGAOd = false;
      bool OjChpfJezT = false;
      bool BsjTTHcbUL = false;
      bool AAmbqasqHP = false;
      bool OFABdVCQnH = false;
      bool OWsWSCZfCZ = false;
      bool ydfDdNxaqP = false;
      bool mSWjEusipx = false;
      bool FLmMwdGQJo = false;
      bool BMnhRkZwWQ = false;
      bool YbZYTwzJRW = false;
      bool IqpFUlqSHA = false;
      bool HgRBOadoST = false;
      bool VxLZYdkNsz = false;
      bool dxzlfJWiMe = false;
      bool sGoWIrKXKs = false;
      bool SJqxALfPfq = false;
      bool AcZHVJheVE = false;
      bool DucmZOHnQg = false;
      bool SNCzgTGBlT = false;
      string RIXOaYCJZj;
      string rqDCQOGrGd;
      string wuocQieUzI;
      string WmwnZwyZlH;
      string ilxtKfnBjD;
      string NpHdiWSuyq;
      string thJRMEuPcU;
      string PgGztKxuSk;
      string tcjutfeSED;
      string cDatMBbfgF;
      string jYYOnfiHiX;
      string ZXcNwQyOWg;
      string YcKZrLGLls;
      string iQOMAVEVHN;
      string wWifcEaNxu;
      string DNJzfHOyVb;
      string ZXVpoIIQMa;
      string MbHIjBsdwm;
      string ksNppVGOfr;
      string GFzenYBsqU;
      if(RIXOaYCJZj == jYYOnfiHiX){wKAWhaGAOd = true;}
      else if(jYYOnfiHiX == RIXOaYCJZj){YbZYTwzJRW = true;}
      if(rqDCQOGrGd == ZXcNwQyOWg){OjChpfJezT = true;}
      else if(ZXcNwQyOWg == rqDCQOGrGd){IqpFUlqSHA = true;}
      if(wuocQieUzI == YcKZrLGLls){BsjTTHcbUL = true;}
      else if(YcKZrLGLls == wuocQieUzI){HgRBOadoST = true;}
      if(WmwnZwyZlH == iQOMAVEVHN){AAmbqasqHP = true;}
      else if(iQOMAVEVHN == WmwnZwyZlH){VxLZYdkNsz = true;}
      if(ilxtKfnBjD == wWifcEaNxu){OFABdVCQnH = true;}
      else if(wWifcEaNxu == ilxtKfnBjD){dxzlfJWiMe = true;}
      if(NpHdiWSuyq == DNJzfHOyVb){OWsWSCZfCZ = true;}
      else if(DNJzfHOyVb == NpHdiWSuyq){sGoWIrKXKs = true;}
      if(thJRMEuPcU == ZXVpoIIQMa){ydfDdNxaqP = true;}
      else if(ZXVpoIIQMa == thJRMEuPcU){SJqxALfPfq = true;}
      if(PgGztKxuSk == MbHIjBsdwm){mSWjEusipx = true;}
      if(tcjutfeSED == ksNppVGOfr){FLmMwdGQJo = true;}
      if(cDatMBbfgF == GFzenYBsqU){BMnhRkZwWQ = true;}
      while(MbHIjBsdwm == PgGztKxuSk){AcZHVJheVE = true;}
      while(ksNppVGOfr == ksNppVGOfr){DucmZOHnQg = true;}
      while(GFzenYBsqU == GFzenYBsqU){SNCzgTGBlT = true;}
      if(wKAWhaGAOd == true){wKAWhaGAOd = false;}
      if(OjChpfJezT == true){OjChpfJezT = false;}
      if(BsjTTHcbUL == true){BsjTTHcbUL = false;}
      if(AAmbqasqHP == true){AAmbqasqHP = false;}
      if(OFABdVCQnH == true){OFABdVCQnH = false;}
      if(OWsWSCZfCZ == true){OWsWSCZfCZ = false;}
      if(ydfDdNxaqP == true){ydfDdNxaqP = false;}
      if(mSWjEusipx == true){mSWjEusipx = false;}
      if(FLmMwdGQJo == true){FLmMwdGQJo = false;}
      if(BMnhRkZwWQ == true){BMnhRkZwWQ = false;}
      if(YbZYTwzJRW == true){YbZYTwzJRW = false;}
      if(IqpFUlqSHA == true){IqpFUlqSHA = false;}
      if(HgRBOadoST == true){HgRBOadoST = false;}
      if(VxLZYdkNsz == true){VxLZYdkNsz = false;}
      if(dxzlfJWiMe == true){dxzlfJWiMe = false;}
      if(sGoWIrKXKs == true){sGoWIrKXKs = false;}
      if(SJqxALfPfq == true){SJqxALfPfq = false;}
      if(AcZHVJheVE == true){AcZHVJheVE = false;}
      if(DucmZOHnQg == true){DucmZOHnQg = false;}
      if(SNCzgTGBlT == true){SNCzgTGBlT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSLZBIAPWP
{ 
  void DKhmiunzoy()
  { 
      bool RPhJUrpYuU = false;
      bool uLrTqpmBtX = false;
      bool IctiAQrRmW = false;
      bool YbDrnrIuOa = false;
      bool afXzlnAIxD = false;
      bool IGmdzoVyID = false;
      bool zXlXwSIzez = false;
      bool gqlSxbFuxL = false;
      bool PjUiORoYsz = false;
      bool VJlKbCtzCS = false;
      bool eAcyVQTUfW = false;
      bool iaBxmPDCJd = false;
      bool djGfcXFaqu = false;
      bool hFrdfPGVMx = false;
      bool yTrVQuIoWM = false;
      bool yqpXoutxUy = false;
      bool LrdkochXRX = false;
      bool IgpLfJqjPg = false;
      bool PQEdwpPTnj = false;
      bool UIBNlFpGgm = false;
      string yPUAnhltaB;
      string wyANpBwVMj;
      string aygmAnjLUR;
      string wfEHubxCdX;
      string OSXbqDHhKq;
      string RAnPLzigzA;
      string xaYIEQtrSN;
      string DsroUHZEww;
      string gBAcAwrouu;
      string rPCcansOWZ;
      string JOPwnXHztD;
      string ZdkDSuZwII;
      string YExWUmpOOg;
      string OLhVlRlEob;
      string nrtqVOezJe;
      string NxFOBFRsaA;
      string grkMoNwOQA;
      string JVGgTfJFAG;
      string IqEiSQFSUg;
      string AscotwHgCH;
      if(yPUAnhltaB == JOPwnXHztD){RPhJUrpYuU = true;}
      else if(JOPwnXHztD == yPUAnhltaB){eAcyVQTUfW = true;}
      if(wyANpBwVMj == ZdkDSuZwII){uLrTqpmBtX = true;}
      else if(ZdkDSuZwII == wyANpBwVMj){iaBxmPDCJd = true;}
      if(aygmAnjLUR == YExWUmpOOg){IctiAQrRmW = true;}
      else if(YExWUmpOOg == aygmAnjLUR){djGfcXFaqu = true;}
      if(wfEHubxCdX == OLhVlRlEob){YbDrnrIuOa = true;}
      else if(OLhVlRlEob == wfEHubxCdX){hFrdfPGVMx = true;}
      if(OSXbqDHhKq == nrtqVOezJe){afXzlnAIxD = true;}
      else if(nrtqVOezJe == OSXbqDHhKq){yTrVQuIoWM = true;}
      if(RAnPLzigzA == NxFOBFRsaA){IGmdzoVyID = true;}
      else if(NxFOBFRsaA == RAnPLzigzA){yqpXoutxUy = true;}
      if(xaYIEQtrSN == grkMoNwOQA){zXlXwSIzez = true;}
      else if(grkMoNwOQA == xaYIEQtrSN){LrdkochXRX = true;}
      if(DsroUHZEww == JVGgTfJFAG){gqlSxbFuxL = true;}
      if(gBAcAwrouu == IqEiSQFSUg){PjUiORoYsz = true;}
      if(rPCcansOWZ == AscotwHgCH){VJlKbCtzCS = true;}
      while(JVGgTfJFAG == DsroUHZEww){IgpLfJqjPg = true;}
      while(IqEiSQFSUg == IqEiSQFSUg){PQEdwpPTnj = true;}
      while(AscotwHgCH == AscotwHgCH){UIBNlFpGgm = true;}
      if(RPhJUrpYuU == true){RPhJUrpYuU = false;}
      if(uLrTqpmBtX == true){uLrTqpmBtX = false;}
      if(IctiAQrRmW == true){IctiAQrRmW = false;}
      if(YbDrnrIuOa == true){YbDrnrIuOa = false;}
      if(afXzlnAIxD == true){afXzlnAIxD = false;}
      if(IGmdzoVyID == true){IGmdzoVyID = false;}
      if(zXlXwSIzez == true){zXlXwSIzez = false;}
      if(gqlSxbFuxL == true){gqlSxbFuxL = false;}
      if(PjUiORoYsz == true){PjUiORoYsz = false;}
      if(VJlKbCtzCS == true){VJlKbCtzCS = false;}
      if(eAcyVQTUfW == true){eAcyVQTUfW = false;}
      if(iaBxmPDCJd == true){iaBxmPDCJd = false;}
      if(djGfcXFaqu == true){djGfcXFaqu = false;}
      if(hFrdfPGVMx == true){hFrdfPGVMx = false;}
      if(yTrVQuIoWM == true){yTrVQuIoWM = false;}
      if(yqpXoutxUy == true){yqpXoutxUy = false;}
      if(LrdkochXRX == true){LrdkochXRX = false;}
      if(IgpLfJqjPg == true){IgpLfJqjPg = false;}
      if(PQEdwpPTnj == true){PQEdwpPTnj = false;}
      if(UIBNlFpGgm == true){UIBNlFpGgm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IBWDMSIRDE
{ 
  void bTLRtLNNlt()
  { 
      bool udXaepkniG = false;
      bool zQQcaKcfLy = false;
      bool EdOIKbVIhE = false;
      bool mcBXLCultM = false;
      bool PRYAYKaoXY = false;
      bool owUSVRPOQD = false;
      bool UcGdTWPrQX = false;
      bool OqkyimFNjz = false;
      bool BgjJPqHhBt = false;
      bool mfVqrlLtgC = false;
      bool thXAJyLWji = false;
      bool MBeQBnrxOc = false;
      bool OhpWjhVsGw = false;
      bool aKggFSJizQ = false;
      bool ekxShlBEoE = false;
      bool tOfEnMqAPa = false;
      bool cRQnHBUyLi = false;
      bool dIxxxdjXoy = false;
      bool gQDCCMdbss = false;
      bool bISXnNTJLf = false;
      string kDiZKhoWEu;
      string CwpSChbZCs;
      string OUBhMjBWPL;
      string jpwAYhBhlF;
      string oOazhPHttU;
      string wGcCrPBAMa;
      string gSHrKMApsU;
      string gtmxEAsCAx;
      string cGbtOcNtHI;
      string fAULYVGhnV;
      string PRAYnCSexr;
      string VzAPxZqNdh;
      string yFhkngYbYh;
      string sKNdhLGCGM;
      string JiwPlgzFNy;
      string esEGWJiPkH;
      string dqGPyKkVgl;
      string SnHQXPJRzH;
      string gSNZDAFHHY;
      string bqRyiSbgQa;
      if(kDiZKhoWEu == PRAYnCSexr){udXaepkniG = true;}
      else if(PRAYnCSexr == kDiZKhoWEu){thXAJyLWji = true;}
      if(CwpSChbZCs == VzAPxZqNdh){zQQcaKcfLy = true;}
      else if(VzAPxZqNdh == CwpSChbZCs){MBeQBnrxOc = true;}
      if(OUBhMjBWPL == yFhkngYbYh){EdOIKbVIhE = true;}
      else if(yFhkngYbYh == OUBhMjBWPL){OhpWjhVsGw = true;}
      if(jpwAYhBhlF == sKNdhLGCGM){mcBXLCultM = true;}
      else if(sKNdhLGCGM == jpwAYhBhlF){aKggFSJizQ = true;}
      if(oOazhPHttU == JiwPlgzFNy){PRYAYKaoXY = true;}
      else if(JiwPlgzFNy == oOazhPHttU){ekxShlBEoE = true;}
      if(wGcCrPBAMa == esEGWJiPkH){owUSVRPOQD = true;}
      else if(esEGWJiPkH == wGcCrPBAMa){tOfEnMqAPa = true;}
      if(gSHrKMApsU == dqGPyKkVgl){UcGdTWPrQX = true;}
      else if(dqGPyKkVgl == gSHrKMApsU){cRQnHBUyLi = true;}
      if(gtmxEAsCAx == SnHQXPJRzH){OqkyimFNjz = true;}
      if(cGbtOcNtHI == gSNZDAFHHY){BgjJPqHhBt = true;}
      if(fAULYVGhnV == bqRyiSbgQa){mfVqrlLtgC = true;}
      while(SnHQXPJRzH == gtmxEAsCAx){dIxxxdjXoy = true;}
      while(gSNZDAFHHY == gSNZDAFHHY){gQDCCMdbss = true;}
      while(bqRyiSbgQa == bqRyiSbgQa){bISXnNTJLf = true;}
      if(udXaepkniG == true){udXaepkniG = false;}
      if(zQQcaKcfLy == true){zQQcaKcfLy = false;}
      if(EdOIKbVIhE == true){EdOIKbVIhE = false;}
      if(mcBXLCultM == true){mcBXLCultM = false;}
      if(PRYAYKaoXY == true){PRYAYKaoXY = false;}
      if(owUSVRPOQD == true){owUSVRPOQD = false;}
      if(UcGdTWPrQX == true){UcGdTWPrQX = false;}
      if(OqkyimFNjz == true){OqkyimFNjz = false;}
      if(BgjJPqHhBt == true){BgjJPqHhBt = false;}
      if(mfVqrlLtgC == true){mfVqrlLtgC = false;}
      if(thXAJyLWji == true){thXAJyLWji = false;}
      if(MBeQBnrxOc == true){MBeQBnrxOc = false;}
      if(OhpWjhVsGw == true){OhpWjhVsGw = false;}
      if(aKggFSJizQ == true){aKggFSJizQ = false;}
      if(ekxShlBEoE == true){ekxShlBEoE = false;}
      if(tOfEnMqAPa == true){tOfEnMqAPa = false;}
      if(cRQnHBUyLi == true){cRQnHBUyLi = false;}
      if(dIxxxdjXoy == true){dIxxxdjXoy = false;}
      if(gQDCCMdbss == true){gQDCCMdbss = false;}
      if(bISXnNTJLf == true){bISXnNTJLf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RDIDWDIYWN
{ 
  void PpyZKSdxqU()
  { 
      bool MAXmHtfXPQ = false;
      bool WenXSGkXHP = false;
      bool CJLyHSiYZD = false;
      bool jzUmItnMEZ = false;
      bool RXHaGIWciB = false;
      bool cdKTEDoZfn = false;
      bool LGyLfXJBOX = false;
      bool RYShxdBjqy = false;
      bool wFoYaGnBhF = false;
      bool FOfPNKZwui = false;
      bool zUOKiELcVa = false;
      bool BEhgrFRYjY = false;
      bool jHSJSCrCTl = false;
      bool DFnIzaqdoV = false;
      bool uKfHDAgzXI = false;
      bool sBLWzqBErf = false;
      bool LIJjWuQZhQ = false;
      bool OmjOdYbLFS = false;
      bool VsdLrCtRIH = false;
      bool YllIJlBwjH = false;
      string LjAWlGrwLK;
      string urteRQUNHA;
      string FsriHKLJiw;
      string XFHdYWRLcC;
      string rHcmPmBlFJ;
      string pEljPSqQPb;
      string uiNOlpkQFu;
      string zJjEIxQFTU;
      string IYEYGTSXOG;
      string eAuBHItNAZ;
      string BkfJKfTgbR;
      string BkxuSVdnHS;
      string WNByPyNixz;
      string DCEtSWrtOZ;
      string zkuxFsDAik;
      string eFFhCnigsM;
      string SkjcNyfDcu;
      string djZhSlREsV;
      string tMzMUywWqd;
      string nKABHOBSiG;
      if(LjAWlGrwLK == BkfJKfTgbR){MAXmHtfXPQ = true;}
      else if(BkfJKfTgbR == LjAWlGrwLK){zUOKiELcVa = true;}
      if(urteRQUNHA == BkxuSVdnHS){WenXSGkXHP = true;}
      else if(BkxuSVdnHS == urteRQUNHA){BEhgrFRYjY = true;}
      if(FsriHKLJiw == WNByPyNixz){CJLyHSiYZD = true;}
      else if(WNByPyNixz == FsriHKLJiw){jHSJSCrCTl = true;}
      if(XFHdYWRLcC == DCEtSWrtOZ){jzUmItnMEZ = true;}
      else if(DCEtSWrtOZ == XFHdYWRLcC){DFnIzaqdoV = true;}
      if(rHcmPmBlFJ == zkuxFsDAik){RXHaGIWciB = true;}
      else if(zkuxFsDAik == rHcmPmBlFJ){uKfHDAgzXI = true;}
      if(pEljPSqQPb == eFFhCnigsM){cdKTEDoZfn = true;}
      else if(eFFhCnigsM == pEljPSqQPb){sBLWzqBErf = true;}
      if(uiNOlpkQFu == SkjcNyfDcu){LGyLfXJBOX = true;}
      else if(SkjcNyfDcu == uiNOlpkQFu){LIJjWuQZhQ = true;}
      if(zJjEIxQFTU == djZhSlREsV){RYShxdBjqy = true;}
      if(IYEYGTSXOG == tMzMUywWqd){wFoYaGnBhF = true;}
      if(eAuBHItNAZ == nKABHOBSiG){FOfPNKZwui = true;}
      while(djZhSlREsV == zJjEIxQFTU){OmjOdYbLFS = true;}
      while(tMzMUywWqd == tMzMUywWqd){VsdLrCtRIH = true;}
      while(nKABHOBSiG == nKABHOBSiG){YllIJlBwjH = true;}
      if(MAXmHtfXPQ == true){MAXmHtfXPQ = false;}
      if(WenXSGkXHP == true){WenXSGkXHP = false;}
      if(CJLyHSiYZD == true){CJLyHSiYZD = false;}
      if(jzUmItnMEZ == true){jzUmItnMEZ = false;}
      if(RXHaGIWciB == true){RXHaGIWciB = false;}
      if(cdKTEDoZfn == true){cdKTEDoZfn = false;}
      if(LGyLfXJBOX == true){LGyLfXJBOX = false;}
      if(RYShxdBjqy == true){RYShxdBjqy = false;}
      if(wFoYaGnBhF == true){wFoYaGnBhF = false;}
      if(FOfPNKZwui == true){FOfPNKZwui = false;}
      if(zUOKiELcVa == true){zUOKiELcVa = false;}
      if(BEhgrFRYjY == true){BEhgrFRYjY = false;}
      if(jHSJSCrCTl == true){jHSJSCrCTl = false;}
      if(DFnIzaqdoV == true){DFnIzaqdoV = false;}
      if(uKfHDAgzXI == true){uKfHDAgzXI = false;}
      if(sBLWzqBErf == true){sBLWzqBErf = false;}
      if(LIJjWuQZhQ == true){LIJjWuQZhQ = false;}
      if(OmjOdYbLFS == true){OmjOdYbLFS = false;}
      if(VsdLrCtRIH == true){VsdLrCtRIH = false;}
      if(YllIJlBwjH == true){YllIJlBwjH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WLYMHWXXCP
{ 
  void BoFPcsqVsb()
  { 
      bool hnbkjGJtHR = false;
      bool djdQXjRYEb = false;
      bool WNFZXybzHE = false;
      bool TdEXqtzquV = false;
      bool qJudZBCTYp = false;
      bool TqQoTUhBMl = false;
      bool eJlDyAeGZd = false;
      bool kZdhkNRbAW = false;
      bool uIZRjcNODV = false;
      bool LyeJqgWrfY = false;
      bool WwsuFtNhDG = false;
      bool CGBppViTSV = false;
      bool mPCDSmtTpD = false;
      bool pZuazyOeMo = false;
      bool OeLxSEwnSV = false;
      bool xCYKlGtocS = false;
      bool zsqAPcLZpr = false;
      bool GEHcGHEEjN = false;
      bool pGBUGmBjns = false;
      bool DYCspVnLhp = false;
      string GGcprcZRPN;
      string uycHwJehjs;
      string LXQaVdZtfR;
      string paQgFHsjLW;
      string mtusXLQaEw;
      string mpKjBhoCTO;
      string DekyXThuCo;
      string PuVNFQcWCJ;
      string MypjdAQgeW;
      string RqPxTIIwVE;
      string dVYOfqTxdk;
      string FSAJBEnBUW;
      string CBPfXYfYsw;
      string HfBxfqZaEl;
      string gSCtQypFuO;
      string THbyBcFrpG;
      string LtDgcZQCdK;
      string eMxhpiyVOY;
      string hacecADDwD;
      string lgkxalPUQq;
      if(GGcprcZRPN == dVYOfqTxdk){hnbkjGJtHR = true;}
      else if(dVYOfqTxdk == GGcprcZRPN){WwsuFtNhDG = true;}
      if(uycHwJehjs == FSAJBEnBUW){djdQXjRYEb = true;}
      else if(FSAJBEnBUW == uycHwJehjs){CGBppViTSV = true;}
      if(LXQaVdZtfR == CBPfXYfYsw){WNFZXybzHE = true;}
      else if(CBPfXYfYsw == LXQaVdZtfR){mPCDSmtTpD = true;}
      if(paQgFHsjLW == HfBxfqZaEl){TdEXqtzquV = true;}
      else if(HfBxfqZaEl == paQgFHsjLW){pZuazyOeMo = true;}
      if(mtusXLQaEw == gSCtQypFuO){qJudZBCTYp = true;}
      else if(gSCtQypFuO == mtusXLQaEw){OeLxSEwnSV = true;}
      if(mpKjBhoCTO == THbyBcFrpG){TqQoTUhBMl = true;}
      else if(THbyBcFrpG == mpKjBhoCTO){xCYKlGtocS = true;}
      if(DekyXThuCo == LtDgcZQCdK){eJlDyAeGZd = true;}
      else if(LtDgcZQCdK == DekyXThuCo){zsqAPcLZpr = true;}
      if(PuVNFQcWCJ == eMxhpiyVOY){kZdhkNRbAW = true;}
      if(MypjdAQgeW == hacecADDwD){uIZRjcNODV = true;}
      if(RqPxTIIwVE == lgkxalPUQq){LyeJqgWrfY = true;}
      while(eMxhpiyVOY == PuVNFQcWCJ){GEHcGHEEjN = true;}
      while(hacecADDwD == hacecADDwD){pGBUGmBjns = true;}
      while(lgkxalPUQq == lgkxalPUQq){DYCspVnLhp = true;}
      if(hnbkjGJtHR == true){hnbkjGJtHR = false;}
      if(djdQXjRYEb == true){djdQXjRYEb = false;}
      if(WNFZXybzHE == true){WNFZXybzHE = false;}
      if(TdEXqtzquV == true){TdEXqtzquV = false;}
      if(qJudZBCTYp == true){qJudZBCTYp = false;}
      if(TqQoTUhBMl == true){TqQoTUhBMl = false;}
      if(eJlDyAeGZd == true){eJlDyAeGZd = false;}
      if(kZdhkNRbAW == true){kZdhkNRbAW = false;}
      if(uIZRjcNODV == true){uIZRjcNODV = false;}
      if(LyeJqgWrfY == true){LyeJqgWrfY = false;}
      if(WwsuFtNhDG == true){WwsuFtNhDG = false;}
      if(CGBppViTSV == true){CGBppViTSV = false;}
      if(mPCDSmtTpD == true){mPCDSmtTpD = false;}
      if(pZuazyOeMo == true){pZuazyOeMo = false;}
      if(OeLxSEwnSV == true){OeLxSEwnSV = false;}
      if(xCYKlGtocS == true){xCYKlGtocS = false;}
      if(zsqAPcLZpr == true){zsqAPcLZpr = false;}
      if(GEHcGHEEjN == true){GEHcGHEEjN = false;}
      if(pGBUGmBjns == true){pGBUGmBjns = false;}
      if(DYCspVnLhp == true){DYCspVnLhp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DQMMQKKXUG
{ 
  void RyEIwmSYVV()
  { 
      bool pDcNBFbiFY = false;
      bool wDMrxRMWEy = false;
      bool eCuQoQlkoi = false;
      bool gZnGUVGcVV = false;
      bool aDwFOQLFPI = false;
      bool fwzKjmHMYk = false;
      bool SqsWrVPGXb = false;
      bool LjBhWaGpBX = false;
      bool EgUgDkacWh = false;
      bool NsDkDiJZMs = false;
      bool BEgnxwtQnI = false;
      bool fRKAfkWMSH = false;
      bool tljoNRfQen = false;
      bool RgcIWAzgjH = false;
      bool pKoNBwiDER = false;
      bool LxGFyOTrZe = false;
      bool PdlzpzoCce = false;
      bool kpcLQjwVnR = false;
      bool icLMcUaWKH = false;
      bool fHGEqLXpXC = false;
      string zZkhslJhQn;
      string NHGtJgHcPR;
      string qVqQyjELoK;
      string zcRJLSZBLR;
      string ZCuxZbFQAf;
      string tiGnTciUjJ;
      string hxrGokpxip;
      string HFQxrnasqW;
      string dmLJPPWdoh;
      string jFRCjbKoIn;
      string lIhJYoSIue;
      string CocMetlipZ;
      string OLHAFBnONQ;
      string dkkDkVFBja;
      string xOhKftcEXp;
      string oayiYZBgDW;
      string ADteBREYbJ;
      string njyPcAcxUK;
      string YiqWaDlCdL;
      string TXxNZsTDIO;
      if(zZkhslJhQn == lIhJYoSIue){pDcNBFbiFY = true;}
      else if(lIhJYoSIue == zZkhslJhQn){BEgnxwtQnI = true;}
      if(NHGtJgHcPR == CocMetlipZ){wDMrxRMWEy = true;}
      else if(CocMetlipZ == NHGtJgHcPR){fRKAfkWMSH = true;}
      if(qVqQyjELoK == OLHAFBnONQ){eCuQoQlkoi = true;}
      else if(OLHAFBnONQ == qVqQyjELoK){tljoNRfQen = true;}
      if(zcRJLSZBLR == dkkDkVFBja){gZnGUVGcVV = true;}
      else if(dkkDkVFBja == zcRJLSZBLR){RgcIWAzgjH = true;}
      if(ZCuxZbFQAf == xOhKftcEXp){aDwFOQLFPI = true;}
      else if(xOhKftcEXp == ZCuxZbFQAf){pKoNBwiDER = true;}
      if(tiGnTciUjJ == oayiYZBgDW){fwzKjmHMYk = true;}
      else if(oayiYZBgDW == tiGnTciUjJ){LxGFyOTrZe = true;}
      if(hxrGokpxip == ADteBREYbJ){SqsWrVPGXb = true;}
      else if(ADteBREYbJ == hxrGokpxip){PdlzpzoCce = true;}
      if(HFQxrnasqW == njyPcAcxUK){LjBhWaGpBX = true;}
      if(dmLJPPWdoh == YiqWaDlCdL){EgUgDkacWh = true;}
      if(jFRCjbKoIn == TXxNZsTDIO){NsDkDiJZMs = true;}
      while(njyPcAcxUK == HFQxrnasqW){kpcLQjwVnR = true;}
      while(YiqWaDlCdL == YiqWaDlCdL){icLMcUaWKH = true;}
      while(TXxNZsTDIO == TXxNZsTDIO){fHGEqLXpXC = true;}
      if(pDcNBFbiFY == true){pDcNBFbiFY = false;}
      if(wDMrxRMWEy == true){wDMrxRMWEy = false;}
      if(eCuQoQlkoi == true){eCuQoQlkoi = false;}
      if(gZnGUVGcVV == true){gZnGUVGcVV = false;}
      if(aDwFOQLFPI == true){aDwFOQLFPI = false;}
      if(fwzKjmHMYk == true){fwzKjmHMYk = false;}
      if(SqsWrVPGXb == true){SqsWrVPGXb = false;}
      if(LjBhWaGpBX == true){LjBhWaGpBX = false;}
      if(EgUgDkacWh == true){EgUgDkacWh = false;}
      if(NsDkDiJZMs == true){NsDkDiJZMs = false;}
      if(BEgnxwtQnI == true){BEgnxwtQnI = false;}
      if(fRKAfkWMSH == true){fRKAfkWMSH = false;}
      if(tljoNRfQen == true){tljoNRfQen = false;}
      if(RgcIWAzgjH == true){RgcIWAzgjH = false;}
      if(pKoNBwiDER == true){pKoNBwiDER = false;}
      if(LxGFyOTrZe == true){LxGFyOTrZe = false;}
      if(PdlzpzoCce == true){PdlzpzoCce = false;}
      if(kpcLQjwVnR == true){kpcLQjwVnR = false;}
      if(icLMcUaWKH == true){icLMcUaWKH = false;}
      if(fHGEqLXpXC == true){fHGEqLXpXC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQTDHEBAJX
{ 
  void RzLXqOZaaW()
  { 
      bool SfOfyJbrab = false;
      bool OjYwIeGhSz = false;
      bool aRTBUhCFkT = false;
      bool pLPSWxnnye = false;
      bool sjCjUzYGZP = false;
      bool bpiTBALMLQ = false;
      bool HVGHlDTFZL = false;
      bool pSjmGqPjgV = false;
      bool IufVrzbuRV = false;
      bool kbcgXWcuxR = false;
      bool eSgOYIGuNJ = false;
      bool jbeoILpkOl = false;
      bool aXnDZOpCPj = false;
      bool OUlPpoORwi = false;
      bool sfhIlJwmYL = false;
      bool gqfLpHecnJ = false;
      bool RDfdtPpPzS = false;
      bool xYnesuofRQ = false;
      bool SDdECXnZYi = false;
      bool KkcmRoAENV = false;
      string EpkCBbNPNX;
      string rfWUmXBrsx;
      string rZpqwzQnIu;
      string VSqHMRnCto;
      string igwsgmFCKL;
      string ieJXOeAsFB;
      string LYGSCZoPHU;
      string jzyENKcxKJ;
      string sNdxLpISrg;
      string RtwrcKZdpH;
      string yptobjgFKE;
      string CDiwHytJGM;
      string QVWaDoCFaD;
      string jzHCLCSoUb;
      string JCImeOLzkd;
      string PPWdpbTTkl;
      string gadGTCufkE;
      string fFneCONiuo;
      string cCTwnUbdMi;
      string iyDithXBTb;
      if(EpkCBbNPNX == yptobjgFKE){SfOfyJbrab = true;}
      else if(yptobjgFKE == EpkCBbNPNX){eSgOYIGuNJ = true;}
      if(rfWUmXBrsx == CDiwHytJGM){OjYwIeGhSz = true;}
      else if(CDiwHytJGM == rfWUmXBrsx){jbeoILpkOl = true;}
      if(rZpqwzQnIu == QVWaDoCFaD){aRTBUhCFkT = true;}
      else if(QVWaDoCFaD == rZpqwzQnIu){aXnDZOpCPj = true;}
      if(VSqHMRnCto == jzHCLCSoUb){pLPSWxnnye = true;}
      else if(jzHCLCSoUb == VSqHMRnCto){OUlPpoORwi = true;}
      if(igwsgmFCKL == JCImeOLzkd){sjCjUzYGZP = true;}
      else if(JCImeOLzkd == igwsgmFCKL){sfhIlJwmYL = true;}
      if(ieJXOeAsFB == PPWdpbTTkl){bpiTBALMLQ = true;}
      else if(PPWdpbTTkl == ieJXOeAsFB){gqfLpHecnJ = true;}
      if(LYGSCZoPHU == gadGTCufkE){HVGHlDTFZL = true;}
      else if(gadGTCufkE == LYGSCZoPHU){RDfdtPpPzS = true;}
      if(jzyENKcxKJ == fFneCONiuo){pSjmGqPjgV = true;}
      if(sNdxLpISrg == cCTwnUbdMi){IufVrzbuRV = true;}
      if(RtwrcKZdpH == iyDithXBTb){kbcgXWcuxR = true;}
      while(fFneCONiuo == jzyENKcxKJ){xYnesuofRQ = true;}
      while(cCTwnUbdMi == cCTwnUbdMi){SDdECXnZYi = true;}
      while(iyDithXBTb == iyDithXBTb){KkcmRoAENV = true;}
      if(SfOfyJbrab == true){SfOfyJbrab = false;}
      if(OjYwIeGhSz == true){OjYwIeGhSz = false;}
      if(aRTBUhCFkT == true){aRTBUhCFkT = false;}
      if(pLPSWxnnye == true){pLPSWxnnye = false;}
      if(sjCjUzYGZP == true){sjCjUzYGZP = false;}
      if(bpiTBALMLQ == true){bpiTBALMLQ = false;}
      if(HVGHlDTFZL == true){HVGHlDTFZL = false;}
      if(pSjmGqPjgV == true){pSjmGqPjgV = false;}
      if(IufVrzbuRV == true){IufVrzbuRV = false;}
      if(kbcgXWcuxR == true){kbcgXWcuxR = false;}
      if(eSgOYIGuNJ == true){eSgOYIGuNJ = false;}
      if(jbeoILpkOl == true){jbeoILpkOl = false;}
      if(aXnDZOpCPj == true){aXnDZOpCPj = false;}
      if(OUlPpoORwi == true){OUlPpoORwi = false;}
      if(sfhIlJwmYL == true){sfhIlJwmYL = false;}
      if(gqfLpHecnJ == true){gqfLpHecnJ = false;}
      if(RDfdtPpPzS == true){RDfdtPpPzS = false;}
      if(xYnesuofRQ == true){xYnesuofRQ = false;}
      if(SDdECXnZYi == true){SDdECXnZYi = false;}
      if(KkcmRoAENV == true){KkcmRoAENV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YTSNCSBRZX
{ 
  void fSrhBlzdiB()
  { 
      bool AoSUMUgXmE = false;
      bool VcZpwKTBYY = false;
      bool jCXSFFbXSk = false;
      bool KfJbqgEJIc = false;
      bool POzlcpSEJO = false;
      bool gtnknyRzPH = false;
      bool sJFCtoSyyO = false;
      bool FJrwIVCkpO = false;
      bool lWOEEPrYms = false;
      bool PEtBiGJxrn = false;
      bool WUGuIWBrbS = false;
      bool wfJAVWtAxd = false;
      bool wtLFyAPqMC = false;
      bool MFsBqQQSug = false;
      bool NAwUxiuteL = false;
      bool LIzOqcJAwH = false;
      bool HKeZFpmHIE = false;
      bool GaEQPwxqIO = false;
      bool FVLApEFeKO = false;
      bool HPWnZDVWOG = false;
      string PIPTcthfyF;
      string hVWkqQcuzV;
      string EXkOeXjmKG;
      string zlsLPPUFmn;
      string miGOeWJrrp;
      string MdPuArXAoE;
      string JuVrFucLUa;
      string uXHLhVRVjI;
      string OquTtUWyKX;
      string rTQidrNNJi;
      string txXRtnWENe;
      string aBPfoRACxj;
      string YdAxibHXgp;
      string IDMBOQTdYF;
      string ySjfwpEjsL;
      string rKQYKPxahS;
      string gyWWVXoORY;
      string yWdrlFtTAr;
      string WWeVyxmmpy;
      string TsuFYAuNJY;
      if(PIPTcthfyF == txXRtnWENe){AoSUMUgXmE = true;}
      else if(txXRtnWENe == PIPTcthfyF){WUGuIWBrbS = true;}
      if(hVWkqQcuzV == aBPfoRACxj){VcZpwKTBYY = true;}
      else if(aBPfoRACxj == hVWkqQcuzV){wfJAVWtAxd = true;}
      if(EXkOeXjmKG == YdAxibHXgp){jCXSFFbXSk = true;}
      else if(YdAxibHXgp == EXkOeXjmKG){wtLFyAPqMC = true;}
      if(zlsLPPUFmn == IDMBOQTdYF){KfJbqgEJIc = true;}
      else if(IDMBOQTdYF == zlsLPPUFmn){MFsBqQQSug = true;}
      if(miGOeWJrrp == ySjfwpEjsL){POzlcpSEJO = true;}
      else if(ySjfwpEjsL == miGOeWJrrp){NAwUxiuteL = true;}
      if(MdPuArXAoE == rKQYKPxahS){gtnknyRzPH = true;}
      else if(rKQYKPxahS == MdPuArXAoE){LIzOqcJAwH = true;}
      if(JuVrFucLUa == gyWWVXoORY){sJFCtoSyyO = true;}
      else if(gyWWVXoORY == JuVrFucLUa){HKeZFpmHIE = true;}
      if(uXHLhVRVjI == yWdrlFtTAr){FJrwIVCkpO = true;}
      if(OquTtUWyKX == WWeVyxmmpy){lWOEEPrYms = true;}
      if(rTQidrNNJi == TsuFYAuNJY){PEtBiGJxrn = true;}
      while(yWdrlFtTAr == uXHLhVRVjI){GaEQPwxqIO = true;}
      while(WWeVyxmmpy == WWeVyxmmpy){FVLApEFeKO = true;}
      while(TsuFYAuNJY == TsuFYAuNJY){HPWnZDVWOG = true;}
      if(AoSUMUgXmE == true){AoSUMUgXmE = false;}
      if(VcZpwKTBYY == true){VcZpwKTBYY = false;}
      if(jCXSFFbXSk == true){jCXSFFbXSk = false;}
      if(KfJbqgEJIc == true){KfJbqgEJIc = false;}
      if(POzlcpSEJO == true){POzlcpSEJO = false;}
      if(gtnknyRzPH == true){gtnknyRzPH = false;}
      if(sJFCtoSyyO == true){sJFCtoSyyO = false;}
      if(FJrwIVCkpO == true){FJrwIVCkpO = false;}
      if(lWOEEPrYms == true){lWOEEPrYms = false;}
      if(PEtBiGJxrn == true){PEtBiGJxrn = false;}
      if(WUGuIWBrbS == true){WUGuIWBrbS = false;}
      if(wfJAVWtAxd == true){wfJAVWtAxd = false;}
      if(wtLFyAPqMC == true){wtLFyAPqMC = false;}
      if(MFsBqQQSug == true){MFsBqQQSug = false;}
      if(NAwUxiuteL == true){NAwUxiuteL = false;}
      if(LIzOqcJAwH == true){LIzOqcJAwH = false;}
      if(HKeZFpmHIE == true){HKeZFpmHIE = false;}
      if(GaEQPwxqIO == true){GaEQPwxqIO = false;}
      if(FVLApEFeKO == true){FVLApEFeKO = false;}
      if(HPWnZDVWOG == true){HPWnZDVWOG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FYTZPBWUWE
{ 
  void DsLbVoKxnh()
  { 
      bool LhSZwXmdRs = false;
      bool wAmrAuYUsB = false;
      bool xqGKwocOcD = false;
      bool opSUNwRmNq = false;
      bool JPZUuWVXTV = false;
      bool XxyrdUbHdG = false;
      bool tYANDFgSdE = false;
      bool ckGBrhRlOZ = false;
      bool TFtHfqrapr = false;
      bool UJJGxjOLQo = false;
      bool oCsPrlpwzw = false;
      bool DosDloerhM = false;
      bool NGbliTbADI = false;
      bool SGUZkQLdPt = false;
      bool BuatoeQFTI = false;
      bool EWdEbiaHfX = false;
      bool KprqdwTSSV = false;
      bool cAcnKRegwE = false;
      bool CVfuDucQxC = false;
      bool pExqiKCjQs = false;
      string TdLOjRKotq;
      string lTQMBLuJLJ;
      string baZHLehPsT;
      string eDzCUrqwCV;
      string lCrNmeepug;
      string jBYLrrEEDE;
      string iuuaMhUNqI;
      string UyGpXZiLTf;
      string AqTMicemJc;
      string nmrylqGQBE;
      string KQylMlthnS;
      string JsjXDqairi;
      string DgDOUgFIEf;
      string TSJOVjshzx;
      string iwzqSuCUtt;
      string QWYSBdMjRe;
      string fldIyqiUCT;
      string ysitAHgMwZ;
      string djNJOxsqNq;
      string WIPUQwRqsb;
      if(TdLOjRKotq == KQylMlthnS){LhSZwXmdRs = true;}
      else if(KQylMlthnS == TdLOjRKotq){oCsPrlpwzw = true;}
      if(lTQMBLuJLJ == JsjXDqairi){wAmrAuYUsB = true;}
      else if(JsjXDqairi == lTQMBLuJLJ){DosDloerhM = true;}
      if(baZHLehPsT == DgDOUgFIEf){xqGKwocOcD = true;}
      else if(DgDOUgFIEf == baZHLehPsT){NGbliTbADI = true;}
      if(eDzCUrqwCV == TSJOVjshzx){opSUNwRmNq = true;}
      else if(TSJOVjshzx == eDzCUrqwCV){SGUZkQLdPt = true;}
      if(lCrNmeepug == iwzqSuCUtt){JPZUuWVXTV = true;}
      else if(iwzqSuCUtt == lCrNmeepug){BuatoeQFTI = true;}
      if(jBYLrrEEDE == QWYSBdMjRe){XxyrdUbHdG = true;}
      else if(QWYSBdMjRe == jBYLrrEEDE){EWdEbiaHfX = true;}
      if(iuuaMhUNqI == fldIyqiUCT){tYANDFgSdE = true;}
      else if(fldIyqiUCT == iuuaMhUNqI){KprqdwTSSV = true;}
      if(UyGpXZiLTf == ysitAHgMwZ){ckGBrhRlOZ = true;}
      if(AqTMicemJc == djNJOxsqNq){TFtHfqrapr = true;}
      if(nmrylqGQBE == WIPUQwRqsb){UJJGxjOLQo = true;}
      while(ysitAHgMwZ == UyGpXZiLTf){cAcnKRegwE = true;}
      while(djNJOxsqNq == djNJOxsqNq){CVfuDucQxC = true;}
      while(WIPUQwRqsb == WIPUQwRqsb){pExqiKCjQs = true;}
      if(LhSZwXmdRs == true){LhSZwXmdRs = false;}
      if(wAmrAuYUsB == true){wAmrAuYUsB = false;}
      if(xqGKwocOcD == true){xqGKwocOcD = false;}
      if(opSUNwRmNq == true){opSUNwRmNq = false;}
      if(JPZUuWVXTV == true){JPZUuWVXTV = false;}
      if(XxyrdUbHdG == true){XxyrdUbHdG = false;}
      if(tYANDFgSdE == true){tYANDFgSdE = false;}
      if(ckGBrhRlOZ == true){ckGBrhRlOZ = false;}
      if(TFtHfqrapr == true){TFtHfqrapr = false;}
      if(UJJGxjOLQo == true){UJJGxjOLQo = false;}
      if(oCsPrlpwzw == true){oCsPrlpwzw = false;}
      if(DosDloerhM == true){DosDloerhM = false;}
      if(NGbliTbADI == true){NGbliTbADI = false;}
      if(SGUZkQLdPt == true){SGUZkQLdPt = false;}
      if(BuatoeQFTI == true){BuatoeQFTI = false;}
      if(EWdEbiaHfX == true){EWdEbiaHfX = false;}
      if(KprqdwTSSV == true){KprqdwTSSV = false;}
      if(cAcnKRegwE == true){cAcnKRegwE = false;}
      if(CVfuDucQxC == true){CVfuDucQxC = false;}
      if(pExqiKCjQs == true){pExqiKCjQs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZSAPUIUCRR
{ 
  void YZpcfmyRSh()
  { 
      bool wJjDgTnVfq = false;
      bool UtTVMsJgtF = false;
      bool wScOEhqhyf = false;
      bool licAYadAQp = false;
      bool xdOFcuCYLh = false;
      bool DHyCWdgVzy = false;
      bool bGXAFkRTxk = false;
      bool OJPEIRDWlI = false;
      bool fSVQcdkZct = false;
      bool tIBSNqGOAq = false;
      bool chaaSsrstE = false;
      bool ZJipSIjHWb = false;
      bool ArpCqGIxpQ = false;
      bool KnWtfxruxj = false;
      bool kqfYUkZLAF = false;
      bool GzrYqkqYiM = false;
      bool kuCcsklnJU = false;
      bool QoJmpILRhG = false;
      bool fxwkKLwyDu = false;
      bool GTLkypnCei = false;
      string aSpzWncVDa;
      string GRJEPxqfaz;
      string mbTTbRuzGn;
      string QdbyKryaRr;
      string GkWEpLcPrR;
      string jbwLZzyVXE;
      string sdPOJcoKsX;
      string yPNhrBEPdQ;
      string neGnEohPYK;
      string scDMzcVHtN;
      string VSVUSTNNSX;
      string tiqGPNWaKU;
      string tYlidVLAiO;
      string fxUQtVJkUj;
      string aTxAPJkxxk;
      string FtwZSxfmpx;
      string INeErxNaMt;
      string ElFZsabkSU;
      string kODxJlAuxx;
      string pVtXbMorIS;
      if(aSpzWncVDa == VSVUSTNNSX){wJjDgTnVfq = true;}
      else if(VSVUSTNNSX == aSpzWncVDa){chaaSsrstE = true;}
      if(GRJEPxqfaz == tiqGPNWaKU){UtTVMsJgtF = true;}
      else if(tiqGPNWaKU == GRJEPxqfaz){ZJipSIjHWb = true;}
      if(mbTTbRuzGn == tYlidVLAiO){wScOEhqhyf = true;}
      else if(tYlidVLAiO == mbTTbRuzGn){ArpCqGIxpQ = true;}
      if(QdbyKryaRr == fxUQtVJkUj){licAYadAQp = true;}
      else if(fxUQtVJkUj == QdbyKryaRr){KnWtfxruxj = true;}
      if(GkWEpLcPrR == aTxAPJkxxk){xdOFcuCYLh = true;}
      else if(aTxAPJkxxk == GkWEpLcPrR){kqfYUkZLAF = true;}
      if(jbwLZzyVXE == FtwZSxfmpx){DHyCWdgVzy = true;}
      else if(FtwZSxfmpx == jbwLZzyVXE){GzrYqkqYiM = true;}
      if(sdPOJcoKsX == INeErxNaMt){bGXAFkRTxk = true;}
      else if(INeErxNaMt == sdPOJcoKsX){kuCcsklnJU = true;}
      if(yPNhrBEPdQ == ElFZsabkSU){OJPEIRDWlI = true;}
      if(neGnEohPYK == kODxJlAuxx){fSVQcdkZct = true;}
      if(scDMzcVHtN == pVtXbMorIS){tIBSNqGOAq = true;}
      while(ElFZsabkSU == yPNhrBEPdQ){QoJmpILRhG = true;}
      while(kODxJlAuxx == kODxJlAuxx){fxwkKLwyDu = true;}
      while(pVtXbMorIS == pVtXbMorIS){GTLkypnCei = true;}
      if(wJjDgTnVfq == true){wJjDgTnVfq = false;}
      if(UtTVMsJgtF == true){UtTVMsJgtF = false;}
      if(wScOEhqhyf == true){wScOEhqhyf = false;}
      if(licAYadAQp == true){licAYadAQp = false;}
      if(xdOFcuCYLh == true){xdOFcuCYLh = false;}
      if(DHyCWdgVzy == true){DHyCWdgVzy = false;}
      if(bGXAFkRTxk == true){bGXAFkRTxk = false;}
      if(OJPEIRDWlI == true){OJPEIRDWlI = false;}
      if(fSVQcdkZct == true){fSVQcdkZct = false;}
      if(tIBSNqGOAq == true){tIBSNqGOAq = false;}
      if(chaaSsrstE == true){chaaSsrstE = false;}
      if(ZJipSIjHWb == true){ZJipSIjHWb = false;}
      if(ArpCqGIxpQ == true){ArpCqGIxpQ = false;}
      if(KnWtfxruxj == true){KnWtfxruxj = false;}
      if(kqfYUkZLAF == true){kqfYUkZLAF = false;}
      if(GzrYqkqYiM == true){GzrYqkqYiM = false;}
      if(kuCcsklnJU == true){kuCcsklnJU = false;}
      if(QoJmpILRhG == true){QoJmpILRhG = false;}
      if(fxwkKLwyDu == true){fxwkKLwyDu = false;}
      if(GTLkypnCei == true){GTLkypnCei = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ODRSBAHHBT
{ 
  void kkJnsEfUsu()
  { 
      bool FeFhcdfToz = false;
      bool RfaaTrwFOg = false;
      bool FMxjTBHzWy = false;
      bool RdbbkuJDNy = false;
      bool hqNLuxmyPJ = false;
      bool DNyhmshVNb = false;
      bool VfwphnEypX = false;
      bool irrQzOyknV = false;
      bool OJjNtEetor = false;
      bool NnokbBtWcH = false;
      bool snIraLUhiY = false;
      bool twgqMMwiwd = false;
      bool IJJyKtCGnx = false;
      bool TbIgcZBrli = false;
      bool ixLQxRHyXP = false;
      bool FLazyieJgf = false;
      bool INtkESnzOl = false;
      bool LEwMuLysAs = false;
      bool mEhYqIAJhs = false;
      bool uqKFZUDZLe = false;
      string pXAHESmxhs;
      string aSmlqjNAXG;
      string cmAOKeMqzI;
      string ddmGfAdVEW;
      string gYDlhiEeUO;
      string UugEaDWkwZ;
      string GwxYPxefFp;
      string GrwAYDiOgb;
      string ZhWkmhwifc;
      string drYeQkaeVk;
      string EYYdHbzfeW;
      string TIEUzXZMkh;
      string AuAcMNTQjn;
      string bErwWBIrcL;
      string hPEIIVmDer;
      string LOsnjJXuRs;
      string IhwqtPPIxx;
      string OhiZzjqqUp;
      string ZPlqbNKDLN;
      string dNZiCASMOr;
      if(pXAHESmxhs == EYYdHbzfeW){FeFhcdfToz = true;}
      else if(EYYdHbzfeW == pXAHESmxhs){snIraLUhiY = true;}
      if(aSmlqjNAXG == TIEUzXZMkh){RfaaTrwFOg = true;}
      else if(TIEUzXZMkh == aSmlqjNAXG){twgqMMwiwd = true;}
      if(cmAOKeMqzI == AuAcMNTQjn){FMxjTBHzWy = true;}
      else if(AuAcMNTQjn == cmAOKeMqzI){IJJyKtCGnx = true;}
      if(ddmGfAdVEW == bErwWBIrcL){RdbbkuJDNy = true;}
      else if(bErwWBIrcL == ddmGfAdVEW){TbIgcZBrli = true;}
      if(gYDlhiEeUO == hPEIIVmDer){hqNLuxmyPJ = true;}
      else if(hPEIIVmDer == gYDlhiEeUO){ixLQxRHyXP = true;}
      if(UugEaDWkwZ == LOsnjJXuRs){DNyhmshVNb = true;}
      else if(LOsnjJXuRs == UugEaDWkwZ){FLazyieJgf = true;}
      if(GwxYPxefFp == IhwqtPPIxx){VfwphnEypX = true;}
      else if(IhwqtPPIxx == GwxYPxefFp){INtkESnzOl = true;}
      if(GrwAYDiOgb == OhiZzjqqUp){irrQzOyknV = true;}
      if(ZhWkmhwifc == ZPlqbNKDLN){OJjNtEetor = true;}
      if(drYeQkaeVk == dNZiCASMOr){NnokbBtWcH = true;}
      while(OhiZzjqqUp == GrwAYDiOgb){LEwMuLysAs = true;}
      while(ZPlqbNKDLN == ZPlqbNKDLN){mEhYqIAJhs = true;}
      while(dNZiCASMOr == dNZiCASMOr){uqKFZUDZLe = true;}
      if(FeFhcdfToz == true){FeFhcdfToz = false;}
      if(RfaaTrwFOg == true){RfaaTrwFOg = false;}
      if(FMxjTBHzWy == true){FMxjTBHzWy = false;}
      if(RdbbkuJDNy == true){RdbbkuJDNy = false;}
      if(hqNLuxmyPJ == true){hqNLuxmyPJ = false;}
      if(DNyhmshVNb == true){DNyhmshVNb = false;}
      if(VfwphnEypX == true){VfwphnEypX = false;}
      if(irrQzOyknV == true){irrQzOyknV = false;}
      if(OJjNtEetor == true){OJjNtEetor = false;}
      if(NnokbBtWcH == true){NnokbBtWcH = false;}
      if(snIraLUhiY == true){snIraLUhiY = false;}
      if(twgqMMwiwd == true){twgqMMwiwd = false;}
      if(IJJyKtCGnx == true){IJJyKtCGnx = false;}
      if(TbIgcZBrli == true){TbIgcZBrli = false;}
      if(ixLQxRHyXP == true){ixLQxRHyXP = false;}
      if(FLazyieJgf == true){FLazyieJgf = false;}
      if(INtkESnzOl == true){INtkESnzOl = false;}
      if(LEwMuLysAs == true){LEwMuLysAs = false;}
      if(mEhYqIAJhs == true){mEhYqIAJhs = false;}
      if(uqKFZUDZLe == true){uqKFZUDZLe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QCENWGZNJD
{ 
  void UHakNnLqTD()
  { 
      bool cuEVJmHgIL = false;
      bool UpwdlIXTgh = false;
      bool sFhFpYOytV = false;
      bool mAQZHzhpjH = false;
      bool cYYAFWMaSf = false;
      bool UnDHWXNyfj = false;
      bool YIllYUZVVl = false;
      bool ZhjZFTghAT = false;
      bool MmfOAywIDj = false;
      bool ljJzhTmlak = false;
      bool wpFfGlEdBC = false;
      bool pexMWkcXla = false;
      bool XRRlAoXjql = false;
      bool guGPWVhzHN = false;
      bool tSHAtGlxbw = false;
      bool pOzAMeYSfQ = false;
      bool OTlPVuYhoB = false;
      bool DdPXfFJQrt = false;
      bool DZHuuSuGCr = false;
      bool xOTqzZfrey = false;
      string rhWgCzhKLj;
      string TPVQUHRtxY;
      string wMYLhSfHOp;
      string rdXjUOPwWp;
      string XxEGQwxpVJ;
      string nsHfMfIKyi;
      string TauUqoqluG;
      string qUXHAyHSul;
      string VpkFCyWrWn;
      string FFxmVxCjOa;
      string ELtPSSVzeO;
      string XpOMNdopSr;
      string SyOHAkXklC;
      string wXDUgKuUli;
      string cWNIQPpkYr;
      string HLQWHGwmPg;
      string ujNbSAltfD;
      string hUDiOukFpk;
      string umLsujGgMZ;
      string NIFFnsIkoP;
      if(rhWgCzhKLj == ELtPSSVzeO){cuEVJmHgIL = true;}
      else if(ELtPSSVzeO == rhWgCzhKLj){wpFfGlEdBC = true;}
      if(TPVQUHRtxY == XpOMNdopSr){UpwdlIXTgh = true;}
      else if(XpOMNdopSr == TPVQUHRtxY){pexMWkcXla = true;}
      if(wMYLhSfHOp == SyOHAkXklC){sFhFpYOytV = true;}
      else if(SyOHAkXklC == wMYLhSfHOp){XRRlAoXjql = true;}
      if(rdXjUOPwWp == wXDUgKuUli){mAQZHzhpjH = true;}
      else if(wXDUgKuUli == rdXjUOPwWp){guGPWVhzHN = true;}
      if(XxEGQwxpVJ == cWNIQPpkYr){cYYAFWMaSf = true;}
      else if(cWNIQPpkYr == XxEGQwxpVJ){tSHAtGlxbw = true;}
      if(nsHfMfIKyi == HLQWHGwmPg){UnDHWXNyfj = true;}
      else if(HLQWHGwmPg == nsHfMfIKyi){pOzAMeYSfQ = true;}
      if(TauUqoqluG == ujNbSAltfD){YIllYUZVVl = true;}
      else if(ujNbSAltfD == TauUqoqluG){OTlPVuYhoB = true;}
      if(qUXHAyHSul == hUDiOukFpk){ZhjZFTghAT = true;}
      if(VpkFCyWrWn == umLsujGgMZ){MmfOAywIDj = true;}
      if(FFxmVxCjOa == NIFFnsIkoP){ljJzhTmlak = true;}
      while(hUDiOukFpk == qUXHAyHSul){DdPXfFJQrt = true;}
      while(umLsujGgMZ == umLsujGgMZ){DZHuuSuGCr = true;}
      while(NIFFnsIkoP == NIFFnsIkoP){xOTqzZfrey = true;}
      if(cuEVJmHgIL == true){cuEVJmHgIL = false;}
      if(UpwdlIXTgh == true){UpwdlIXTgh = false;}
      if(sFhFpYOytV == true){sFhFpYOytV = false;}
      if(mAQZHzhpjH == true){mAQZHzhpjH = false;}
      if(cYYAFWMaSf == true){cYYAFWMaSf = false;}
      if(UnDHWXNyfj == true){UnDHWXNyfj = false;}
      if(YIllYUZVVl == true){YIllYUZVVl = false;}
      if(ZhjZFTghAT == true){ZhjZFTghAT = false;}
      if(MmfOAywIDj == true){MmfOAywIDj = false;}
      if(ljJzhTmlak == true){ljJzhTmlak = false;}
      if(wpFfGlEdBC == true){wpFfGlEdBC = false;}
      if(pexMWkcXla == true){pexMWkcXla = false;}
      if(XRRlAoXjql == true){XRRlAoXjql = false;}
      if(guGPWVhzHN == true){guGPWVhzHN = false;}
      if(tSHAtGlxbw == true){tSHAtGlxbw = false;}
      if(pOzAMeYSfQ == true){pOzAMeYSfQ = false;}
      if(OTlPVuYhoB == true){OTlPVuYhoB = false;}
      if(DdPXfFJQrt == true){DdPXfFJQrt = false;}
      if(DZHuuSuGCr == true){DZHuuSuGCr = false;}
      if(xOTqzZfrey == true){xOTqzZfrey = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SNRIJBWUNI
{ 
  void FSNekdGuyM()
  { 
      bool jrdtqdsVGq = false;
      bool qUBbKwyyCY = false;
      bool JbZUNszcLF = false;
      bool OfapVodTLs = false;
      bool aBCBYtkXUt = false;
      bool ORfUDISJfy = false;
      bool eQKAcLsLFV = false;
      bool SdmIyHYYuT = false;
      bool IbIQpwzFmN = false;
      bool WTmNOKqBXM = false;
      bool AZSzbjeWWw = false;
      bool isNLoCIsJg = false;
      bool LnYqyyqYsm = false;
      bool QWAhThJIoG = false;
      bool QchpdcFbYL = false;
      bool CxrqBLAaAd = false;
      bool sGcjeMsfqG = false;
      bool szEDPiFhNV = false;
      bool rPAgkSeJgH = false;
      bool hiHLNJzyLR = false;
      string IhZuAmoaNL;
      string nnurPCXahx;
      string lLTDnQTPir;
      string CsdfVBPdmN;
      string jcqXRnNYXY;
      string VixpaxNVHj;
      string SYrUJuKOVO;
      string mtmUNJTwlz;
      string DuqJWTumFX;
      string mtWDtKkWOW;
      string cyDJkbubcR;
      string dRiHgXghxp;
      string zXIxbsWjZC;
      string XwgPVErhYu;
      string XTJntULOWW;
      string dDYXWFoFhr;
      string ELCasgjSkc;
      string fzJCRfNUDG;
      string hHNDXUXIrQ;
      string OlzfqMQhtM;
      if(IhZuAmoaNL == cyDJkbubcR){jrdtqdsVGq = true;}
      else if(cyDJkbubcR == IhZuAmoaNL){AZSzbjeWWw = true;}
      if(nnurPCXahx == dRiHgXghxp){qUBbKwyyCY = true;}
      else if(dRiHgXghxp == nnurPCXahx){isNLoCIsJg = true;}
      if(lLTDnQTPir == zXIxbsWjZC){JbZUNszcLF = true;}
      else if(zXIxbsWjZC == lLTDnQTPir){LnYqyyqYsm = true;}
      if(CsdfVBPdmN == XwgPVErhYu){OfapVodTLs = true;}
      else if(XwgPVErhYu == CsdfVBPdmN){QWAhThJIoG = true;}
      if(jcqXRnNYXY == XTJntULOWW){aBCBYtkXUt = true;}
      else if(XTJntULOWW == jcqXRnNYXY){QchpdcFbYL = true;}
      if(VixpaxNVHj == dDYXWFoFhr){ORfUDISJfy = true;}
      else if(dDYXWFoFhr == VixpaxNVHj){CxrqBLAaAd = true;}
      if(SYrUJuKOVO == ELCasgjSkc){eQKAcLsLFV = true;}
      else if(ELCasgjSkc == SYrUJuKOVO){sGcjeMsfqG = true;}
      if(mtmUNJTwlz == fzJCRfNUDG){SdmIyHYYuT = true;}
      if(DuqJWTumFX == hHNDXUXIrQ){IbIQpwzFmN = true;}
      if(mtWDtKkWOW == OlzfqMQhtM){WTmNOKqBXM = true;}
      while(fzJCRfNUDG == mtmUNJTwlz){szEDPiFhNV = true;}
      while(hHNDXUXIrQ == hHNDXUXIrQ){rPAgkSeJgH = true;}
      while(OlzfqMQhtM == OlzfqMQhtM){hiHLNJzyLR = true;}
      if(jrdtqdsVGq == true){jrdtqdsVGq = false;}
      if(qUBbKwyyCY == true){qUBbKwyyCY = false;}
      if(JbZUNszcLF == true){JbZUNszcLF = false;}
      if(OfapVodTLs == true){OfapVodTLs = false;}
      if(aBCBYtkXUt == true){aBCBYtkXUt = false;}
      if(ORfUDISJfy == true){ORfUDISJfy = false;}
      if(eQKAcLsLFV == true){eQKAcLsLFV = false;}
      if(SdmIyHYYuT == true){SdmIyHYYuT = false;}
      if(IbIQpwzFmN == true){IbIQpwzFmN = false;}
      if(WTmNOKqBXM == true){WTmNOKqBXM = false;}
      if(AZSzbjeWWw == true){AZSzbjeWWw = false;}
      if(isNLoCIsJg == true){isNLoCIsJg = false;}
      if(LnYqyyqYsm == true){LnYqyyqYsm = false;}
      if(QWAhThJIoG == true){QWAhThJIoG = false;}
      if(QchpdcFbYL == true){QchpdcFbYL = false;}
      if(CxrqBLAaAd == true){CxrqBLAaAd = false;}
      if(sGcjeMsfqG == true){sGcjeMsfqG = false;}
      if(szEDPiFhNV == true){szEDPiFhNV = false;}
      if(rPAgkSeJgH == true){rPAgkSeJgH = false;}
      if(hiHLNJzyLR == true){hiHLNJzyLR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EWSUDMPQVF
{ 
  void oFjzMFmVZu()
  { 
      bool pXoizfzCQp = false;
      bool kMqdiUuFQx = false;
      bool VAbRFpblyS = false;
      bool OFKYTWiiJZ = false;
      bool QtXiNIVlGI = false;
      bool DNrsPouXcI = false;
      bool EMExbeCRJL = false;
      bool lLupgacsEx = false;
      bool UoeoOBMRId = false;
      bool bKFAVDpZHi = false;
      bool FDbtWqRCLo = false;
      bool MBTfnOhOhZ = false;
      bool RkIejaFuTd = false;
      bool jClUqQMjSW = false;
      bool jKFTRZqZLH = false;
      bool VaqgQUtxJw = false;
      bool lWhhEJPynX = false;
      bool BxwLpGeoMK = false;
      bool ifiMIJKFEW = false;
      bool VPaWkNcXOI = false;
      string PRVWjMRZIQ;
      string dIhJSycVzr;
      string ATXnPaNqKR;
      string lJfXukFcbT;
      string tlRpFWafKq;
      string XjEyRwsgHI;
      string zaOqeTbKOg;
      string sAtexNChir;
      string zgfStBFgGz;
      string qXUSUSWaLk;
      string tQRcyXoYBD;
      string tLyOISuwxc;
      string NtDPoUebKd;
      string paWxyhODTV;
      string LgfDEfZGJC;
      string XadhXzNCmd;
      string sNNWMSoBQa;
      string DqbaRgOAKJ;
      string uYRIGPxnYy;
      string UMPpcySIpk;
      if(PRVWjMRZIQ == tQRcyXoYBD){pXoizfzCQp = true;}
      else if(tQRcyXoYBD == PRVWjMRZIQ){FDbtWqRCLo = true;}
      if(dIhJSycVzr == tLyOISuwxc){kMqdiUuFQx = true;}
      else if(tLyOISuwxc == dIhJSycVzr){MBTfnOhOhZ = true;}
      if(ATXnPaNqKR == NtDPoUebKd){VAbRFpblyS = true;}
      else if(NtDPoUebKd == ATXnPaNqKR){RkIejaFuTd = true;}
      if(lJfXukFcbT == paWxyhODTV){OFKYTWiiJZ = true;}
      else if(paWxyhODTV == lJfXukFcbT){jClUqQMjSW = true;}
      if(tlRpFWafKq == LgfDEfZGJC){QtXiNIVlGI = true;}
      else if(LgfDEfZGJC == tlRpFWafKq){jKFTRZqZLH = true;}
      if(XjEyRwsgHI == XadhXzNCmd){DNrsPouXcI = true;}
      else if(XadhXzNCmd == XjEyRwsgHI){VaqgQUtxJw = true;}
      if(zaOqeTbKOg == sNNWMSoBQa){EMExbeCRJL = true;}
      else if(sNNWMSoBQa == zaOqeTbKOg){lWhhEJPynX = true;}
      if(sAtexNChir == DqbaRgOAKJ){lLupgacsEx = true;}
      if(zgfStBFgGz == uYRIGPxnYy){UoeoOBMRId = true;}
      if(qXUSUSWaLk == UMPpcySIpk){bKFAVDpZHi = true;}
      while(DqbaRgOAKJ == sAtexNChir){BxwLpGeoMK = true;}
      while(uYRIGPxnYy == uYRIGPxnYy){ifiMIJKFEW = true;}
      while(UMPpcySIpk == UMPpcySIpk){VPaWkNcXOI = true;}
      if(pXoizfzCQp == true){pXoizfzCQp = false;}
      if(kMqdiUuFQx == true){kMqdiUuFQx = false;}
      if(VAbRFpblyS == true){VAbRFpblyS = false;}
      if(OFKYTWiiJZ == true){OFKYTWiiJZ = false;}
      if(QtXiNIVlGI == true){QtXiNIVlGI = false;}
      if(DNrsPouXcI == true){DNrsPouXcI = false;}
      if(EMExbeCRJL == true){EMExbeCRJL = false;}
      if(lLupgacsEx == true){lLupgacsEx = false;}
      if(UoeoOBMRId == true){UoeoOBMRId = false;}
      if(bKFAVDpZHi == true){bKFAVDpZHi = false;}
      if(FDbtWqRCLo == true){FDbtWqRCLo = false;}
      if(MBTfnOhOhZ == true){MBTfnOhOhZ = false;}
      if(RkIejaFuTd == true){RkIejaFuTd = false;}
      if(jClUqQMjSW == true){jClUqQMjSW = false;}
      if(jKFTRZqZLH == true){jKFTRZqZLH = false;}
      if(VaqgQUtxJw == true){VaqgQUtxJw = false;}
      if(lWhhEJPynX == true){lWhhEJPynX = false;}
      if(BxwLpGeoMK == true){BxwLpGeoMK = false;}
      if(ifiMIJKFEW == true){ifiMIJKFEW = false;}
      if(VPaWkNcXOI == true){VPaWkNcXOI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DMRIKSUVEF
{ 
  void UgJciPoKtI()
  { 
      bool JbjJHOLFbY = false;
      bool OQAfxCZYME = false;
      bool tppKCTQzdO = false;
      bool JMTMdXwOwS = false;
      bool BDPWuqpaNt = false;
      bool WGoJsSlYGm = false;
      bool xMaNOCxmCZ = false;
      bool GLbsDqZSOL = false;
      bool dokjqCWJTL = false;
      bool kWHIUobCIs = false;
      bool sCYnnLeuGC = false;
      bool rTJuJIaqVL = false;
      bool emTpniDTYN = false;
      bool OXJVRaQwuf = false;
      bool XaDRSRNLyM = false;
      bool OjgxOFihAF = false;
      bool HKWsmUJnch = false;
      bool qdwpmDjCXW = false;
      bool VrUMyepMHL = false;
      bool riwpXNEJdx = false;
      string MqDGZujsZo;
      string tnWxZCmzrP;
      string HiGkamJJFQ;
      string AqWURpcqWE;
      string LeAhOCRZik;
      string PQlPhdkSfl;
      string kZnJoDQCfj;
      string YwbnEchXVY;
      string VjaTAiFGmm;
      string EKLjSkqqsL;
      string lOszLToxLE;
      string uNwHQBzTIF;
      string xJPreOjqVS;
      string kqeKlGqbIg;
      string tHuhrqOETR;
      string lXhmOcyATx;
      string ixbsSDhlUK;
      string JXLbLoNhAm;
      string AfXDgNJrwJ;
      string HpHLxwfBOn;
      if(MqDGZujsZo == lOszLToxLE){JbjJHOLFbY = true;}
      else if(lOszLToxLE == MqDGZujsZo){sCYnnLeuGC = true;}
      if(tnWxZCmzrP == uNwHQBzTIF){OQAfxCZYME = true;}
      else if(uNwHQBzTIF == tnWxZCmzrP){rTJuJIaqVL = true;}
      if(HiGkamJJFQ == xJPreOjqVS){tppKCTQzdO = true;}
      else if(xJPreOjqVS == HiGkamJJFQ){emTpniDTYN = true;}
      if(AqWURpcqWE == kqeKlGqbIg){JMTMdXwOwS = true;}
      else if(kqeKlGqbIg == AqWURpcqWE){OXJVRaQwuf = true;}
      if(LeAhOCRZik == tHuhrqOETR){BDPWuqpaNt = true;}
      else if(tHuhrqOETR == LeAhOCRZik){XaDRSRNLyM = true;}
      if(PQlPhdkSfl == lXhmOcyATx){WGoJsSlYGm = true;}
      else if(lXhmOcyATx == PQlPhdkSfl){OjgxOFihAF = true;}
      if(kZnJoDQCfj == ixbsSDhlUK){xMaNOCxmCZ = true;}
      else if(ixbsSDhlUK == kZnJoDQCfj){HKWsmUJnch = true;}
      if(YwbnEchXVY == JXLbLoNhAm){GLbsDqZSOL = true;}
      if(VjaTAiFGmm == AfXDgNJrwJ){dokjqCWJTL = true;}
      if(EKLjSkqqsL == HpHLxwfBOn){kWHIUobCIs = true;}
      while(JXLbLoNhAm == YwbnEchXVY){qdwpmDjCXW = true;}
      while(AfXDgNJrwJ == AfXDgNJrwJ){VrUMyepMHL = true;}
      while(HpHLxwfBOn == HpHLxwfBOn){riwpXNEJdx = true;}
      if(JbjJHOLFbY == true){JbjJHOLFbY = false;}
      if(OQAfxCZYME == true){OQAfxCZYME = false;}
      if(tppKCTQzdO == true){tppKCTQzdO = false;}
      if(JMTMdXwOwS == true){JMTMdXwOwS = false;}
      if(BDPWuqpaNt == true){BDPWuqpaNt = false;}
      if(WGoJsSlYGm == true){WGoJsSlYGm = false;}
      if(xMaNOCxmCZ == true){xMaNOCxmCZ = false;}
      if(GLbsDqZSOL == true){GLbsDqZSOL = false;}
      if(dokjqCWJTL == true){dokjqCWJTL = false;}
      if(kWHIUobCIs == true){kWHIUobCIs = false;}
      if(sCYnnLeuGC == true){sCYnnLeuGC = false;}
      if(rTJuJIaqVL == true){rTJuJIaqVL = false;}
      if(emTpniDTYN == true){emTpniDTYN = false;}
      if(OXJVRaQwuf == true){OXJVRaQwuf = false;}
      if(XaDRSRNLyM == true){XaDRSRNLyM = false;}
      if(OjgxOFihAF == true){OjgxOFihAF = false;}
      if(HKWsmUJnch == true){HKWsmUJnch = false;}
      if(qdwpmDjCXW == true){qdwpmDjCXW = false;}
      if(VrUMyepMHL == true){VrUMyepMHL = false;}
      if(riwpXNEJdx == true){riwpXNEJdx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JIQGNSTHIF
{ 
  void OPtSiKOaRh()
  { 
      bool qFZPxDTQcF = false;
      bool fMpmaHOdRt = false;
      bool sdBTFpOcFV = false;
      bool ToepUHVKwQ = false;
      bool mrJqulxVIg = false;
      bool KBuSaNEGJG = false;
      bool opKHlqgASS = false;
      bool lDgBGATJXS = false;
      bool ssUYLRtLOH = false;
      bool DPApawgBFE = false;
      bool EwCouGTtLZ = false;
      bool sthpMuVlwT = false;
      bool wUkLPVCqZK = false;
      bool TRESOwpecE = false;
      bool yzAoOJgJdf = false;
      bool auFlHiLqYY = false;
      bool DcUBGaoPbP = false;
      bool EpIqUxUuwG = false;
      bool orNsiYMRLe = false;
      bool kyGEAVezim = false;
      string LFYPwKtShU;
      string FDtEAiYTwQ;
      string dVlPNbXpFe;
      string JFUngANdwg;
      string McCsHSODQb;
      string PIImnoTIBU;
      string mEMCKziFWz;
      string VtWPEBTsIu;
      string MUYcOAxgAq;
      string gEbbtHPzhH;
      string jJfQFVkshm;
      string VZzGHSfinK;
      string CBFfSRRuUw;
      string lTKBKDnHWs;
      string PDyNVGEVTa;
      string bfLXEiEAyn;
      string DpXlABPyuE;
      string dXMtuzCrJL;
      string NwasUGIlwb;
      string ymIioYeMMT;
      if(LFYPwKtShU == jJfQFVkshm){qFZPxDTQcF = true;}
      else if(jJfQFVkshm == LFYPwKtShU){EwCouGTtLZ = true;}
      if(FDtEAiYTwQ == VZzGHSfinK){fMpmaHOdRt = true;}
      else if(VZzGHSfinK == FDtEAiYTwQ){sthpMuVlwT = true;}
      if(dVlPNbXpFe == CBFfSRRuUw){sdBTFpOcFV = true;}
      else if(CBFfSRRuUw == dVlPNbXpFe){wUkLPVCqZK = true;}
      if(JFUngANdwg == lTKBKDnHWs){ToepUHVKwQ = true;}
      else if(lTKBKDnHWs == JFUngANdwg){TRESOwpecE = true;}
      if(McCsHSODQb == PDyNVGEVTa){mrJqulxVIg = true;}
      else if(PDyNVGEVTa == McCsHSODQb){yzAoOJgJdf = true;}
      if(PIImnoTIBU == bfLXEiEAyn){KBuSaNEGJG = true;}
      else if(bfLXEiEAyn == PIImnoTIBU){auFlHiLqYY = true;}
      if(mEMCKziFWz == DpXlABPyuE){opKHlqgASS = true;}
      else if(DpXlABPyuE == mEMCKziFWz){DcUBGaoPbP = true;}
      if(VtWPEBTsIu == dXMtuzCrJL){lDgBGATJXS = true;}
      if(MUYcOAxgAq == NwasUGIlwb){ssUYLRtLOH = true;}
      if(gEbbtHPzhH == ymIioYeMMT){DPApawgBFE = true;}
      while(dXMtuzCrJL == VtWPEBTsIu){EpIqUxUuwG = true;}
      while(NwasUGIlwb == NwasUGIlwb){orNsiYMRLe = true;}
      while(ymIioYeMMT == ymIioYeMMT){kyGEAVezim = true;}
      if(qFZPxDTQcF == true){qFZPxDTQcF = false;}
      if(fMpmaHOdRt == true){fMpmaHOdRt = false;}
      if(sdBTFpOcFV == true){sdBTFpOcFV = false;}
      if(ToepUHVKwQ == true){ToepUHVKwQ = false;}
      if(mrJqulxVIg == true){mrJqulxVIg = false;}
      if(KBuSaNEGJG == true){KBuSaNEGJG = false;}
      if(opKHlqgASS == true){opKHlqgASS = false;}
      if(lDgBGATJXS == true){lDgBGATJXS = false;}
      if(ssUYLRtLOH == true){ssUYLRtLOH = false;}
      if(DPApawgBFE == true){DPApawgBFE = false;}
      if(EwCouGTtLZ == true){EwCouGTtLZ = false;}
      if(sthpMuVlwT == true){sthpMuVlwT = false;}
      if(wUkLPVCqZK == true){wUkLPVCqZK = false;}
      if(TRESOwpecE == true){TRESOwpecE = false;}
      if(yzAoOJgJdf == true){yzAoOJgJdf = false;}
      if(auFlHiLqYY == true){auFlHiLqYY = false;}
      if(DcUBGaoPbP == true){DcUBGaoPbP = false;}
      if(EpIqUxUuwG == true){EpIqUxUuwG = false;}
      if(orNsiYMRLe == true){orNsiYMRLe = false;}
      if(kyGEAVezim == true){kyGEAVezim = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JUOMXALYUL
{ 
  void PLjwuJKxEy()
  { 
      bool rDRaEecETy = false;
      bool XpGAjtxLyX = false;
      bool KxLZwlwEMr = false;
      bool KQdKlOUqfL = false;
      bool bVEKVUDFjU = false;
      bool pqQmftqqdR = false;
      bool hYranHMwOV = false;
      bool YGelwnrBDb = false;
      bool ipUqBSApeq = false;
      bool WdNOcDcdWO = false;
      bool IHqNwjLdqr = false;
      bool CpnChqEAYU = false;
      bool GVRXzusQJs = false;
      bool KOdnTbzGuR = false;
      bool HVzlnfoLfl = false;
      bool ybEBHlpSOA = false;
      bool qtUygnMzhG = false;
      bool qxFHNjVeiS = false;
      bool FgjXthJbgg = false;
      bool kgqtZMBBFA = false;
      string BBCdbIRfNg;
      string OOVZJMnbmA;
      string MtzPXWnaUl;
      string aTQPaKDKpk;
      string KIgpUlRjUD;
      string jEkBoGClFF;
      string TqLaGuyFyz;
      string JdlCoDNItl;
      string EEFQCVhOaU;
      string HRFjQSwFjY;
      string mLlVtFRhLk;
      string stqSAPluYj;
      string NiecqrYCkW;
      string HHXVyrSjWw;
      string DzDobNZliA;
      string gBgzLEgIdC;
      string gPwndkVVUI;
      string wCXbfNfpBd;
      string RmSjpFaYJt;
      string LKFTPnDOLp;
      if(BBCdbIRfNg == mLlVtFRhLk){rDRaEecETy = true;}
      else if(mLlVtFRhLk == BBCdbIRfNg){IHqNwjLdqr = true;}
      if(OOVZJMnbmA == stqSAPluYj){XpGAjtxLyX = true;}
      else if(stqSAPluYj == OOVZJMnbmA){CpnChqEAYU = true;}
      if(MtzPXWnaUl == NiecqrYCkW){KxLZwlwEMr = true;}
      else if(NiecqrYCkW == MtzPXWnaUl){GVRXzusQJs = true;}
      if(aTQPaKDKpk == HHXVyrSjWw){KQdKlOUqfL = true;}
      else if(HHXVyrSjWw == aTQPaKDKpk){KOdnTbzGuR = true;}
      if(KIgpUlRjUD == DzDobNZliA){bVEKVUDFjU = true;}
      else if(DzDobNZliA == KIgpUlRjUD){HVzlnfoLfl = true;}
      if(jEkBoGClFF == gBgzLEgIdC){pqQmftqqdR = true;}
      else if(gBgzLEgIdC == jEkBoGClFF){ybEBHlpSOA = true;}
      if(TqLaGuyFyz == gPwndkVVUI){hYranHMwOV = true;}
      else if(gPwndkVVUI == TqLaGuyFyz){qtUygnMzhG = true;}
      if(JdlCoDNItl == wCXbfNfpBd){YGelwnrBDb = true;}
      if(EEFQCVhOaU == RmSjpFaYJt){ipUqBSApeq = true;}
      if(HRFjQSwFjY == LKFTPnDOLp){WdNOcDcdWO = true;}
      while(wCXbfNfpBd == JdlCoDNItl){qxFHNjVeiS = true;}
      while(RmSjpFaYJt == RmSjpFaYJt){FgjXthJbgg = true;}
      while(LKFTPnDOLp == LKFTPnDOLp){kgqtZMBBFA = true;}
      if(rDRaEecETy == true){rDRaEecETy = false;}
      if(XpGAjtxLyX == true){XpGAjtxLyX = false;}
      if(KxLZwlwEMr == true){KxLZwlwEMr = false;}
      if(KQdKlOUqfL == true){KQdKlOUqfL = false;}
      if(bVEKVUDFjU == true){bVEKVUDFjU = false;}
      if(pqQmftqqdR == true){pqQmftqqdR = false;}
      if(hYranHMwOV == true){hYranHMwOV = false;}
      if(YGelwnrBDb == true){YGelwnrBDb = false;}
      if(ipUqBSApeq == true){ipUqBSApeq = false;}
      if(WdNOcDcdWO == true){WdNOcDcdWO = false;}
      if(IHqNwjLdqr == true){IHqNwjLdqr = false;}
      if(CpnChqEAYU == true){CpnChqEAYU = false;}
      if(GVRXzusQJs == true){GVRXzusQJs = false;}
      if(KOdnTbzGuR == true){KOdnTbzGuR = false;}
      if(HVzlnfoLfl == true){HVzlnfoLfl = false;}
      if(ybEBHlpSOA == true){ybEBHlpSOA = false;}
      if(qtUygnMzhG == true){qtUygnMzhG = false;}
      if(qxFHNjVeiS == true){qxFHNjVeiS = false;}
      if(FgjXthJbgg == true){FgjXthJbgg = false;}
      if(kgqtZMBBFA == true){kgqtZMBBFA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LTTIYKGEKO
{ 
  void YIwRQWbouW()
  { 
      bool ARTrlNugel = false;
      bool tbppuWwWBj = false;
      bool DkRpiCNJyC = false;
      bool xHTqHsUyAg = false;
      bool ENSPOkxPoA = false;
      bool IWDtnOAdIi = false;
      bool zkibomHzhB = false;
      bool CyWUepRBbx = false;
      bool FyUysZDZCr = false;
      bool sqoQhTeqZa = false;
      bool dxgmxKAhOy = false;
      bool wyCKdAPjhP = false;
      bool ihwpIKJFmL = false;
      bool LaaATHQhAi = false;
      bool YVKEutodmg = false;
      bool DuIKqwBqem = false;
      bool BtuCmVXBqV = false;
      bool ihiypNWrtN = false;
      bool VeSFHQRQJX = false;
      bool GZCNhdZHRZ = false;
      string hLAuZltPZo;
      string NRaIpWbplB;
      string WbUxtOYdiP;
      string ereatunjkr;
      string UHTxsImMkm;
      string LVQEnFqDBL;
      string NQgJJVmzNu;
      string iqEsfPIXDk;
      string aLsuDJaZmn;
      string DkiZeEZJmX;
      string UmzoEURXXY;
      string xTzPkCWkFA;
      string tNMZqxHeOb;
      string oyjfQnMDqi;
      string rDBNpjlSob;
      string goDldHZYxG;
      string MlIwjyiTzw;
      string pTtVHqMyiH;
      string LopltzuxCJ;
      string NmFjWFtEdr;
      if(hLAuZltPZo == UmzoEURXXY){ARTrlNugel = true;}
      else if(UmzoEURXXY == hLAuZltPZo){dxgmxKAhOy = true;}
      if(NRaIpWbplB == xTzPkCWkFA){tbppuWwWBj = true;}
      else if(xTzPkCWkFA == NRaIpWbplB){wyCKdAPjhP = true;}
      if(WbUxtOYdiP == tNMZqxHeOb){DkRpiCNJyC = true;}
      else if(tNMZqxHeOb == WbUxtOYdiP){ihwpIKJFmL = true;}
      if(ereatunjkr == oyjfQnMDqi){xHTqHsUyAg = true;}
      else if(oyjfQnMDqi == ereatunjkr){LaaATHQhAi = true;}
      if(UHTxsImMkm == rDBNpjlSob){ENSPOkxPoA = true;}
      else if(rDBNpjlSob == UHTxsImMkm){YVKEutodmg = true;}
      if(LVQEnFqDBL == goDldHZYxG){IWDtnOAdIi = true;}
      else if(goDldHZYxG == LVQEnFqDBL){DuIKqwBqem = true;}
      if(NQgJJVmzNu == MlIwjyiTzw){zkibomHzhB = true;}
      else if(MlIwjyiTzw == NQgJJVmzNu){BtuCmVXBqV = true;}
      if(iqEsfPIXDk == pTtVHqMyiH){CyWUepRBbx = true;}
      if(aLsuDJaZmn == LopltzuxCJ){FyUysZDZCr = true;}
      if(DkiZeEZJmX == NmFjWFtEdr){sqoQhTeqZa = true;}
      while(pTtVHqMyiH == iqEsfPIXDk){ihiypNWrtN = true;}
      while(LopltzuxCJ == LopltzuxCJ){VeSFHQRQJX = true;}
      while(NmFjWFtEdr == NmFjWFtEdr){GZCNhdZHRZ = true;}
      if(ARTrlNugel == true){ARTrlNugel = false;}
      if(tbppuWwWBj == true){tbppuWwWBj = false;}
      if(DkRpiCNJyC == true){DkRpiCNJyC = false;}
      if(xHTqHsUyAg == true){xHTqHsUyAg = false;}
      if(ENSPOkxPoA == true){ENSPOkxPoA = false;}
      if(IWDtnOAdIi == true){IWDtnOAdIi = false;}
      if(zkibomHzhB == true){zkibomHzhB = false;}
      if(CyWUepRBbx == true){CyWUepRBbx = false;}
      if(FyUysZDZCr == true){FyUysZDZCr = false;}
      if(sqoQhTeqZa == true){sqoQhTeqZa = false;}
      if(dxgmxKAhOy == true){dxgmxKAhOy = false;}
      if(wyCKdAPjhP == true){wyCKdAPjhP = false;}
      if(ihwpIKJFmL == true){ihwpIKJFmL = false;}
      if(LaaATHQhAi == true){LaaATHQhAi = false;}
      if(YVKEutodmg == true){YVKEutodmg = false;}
      if(DuIKqwBqem == true){DuIKqwBqem = false;}
      if(BtuCmVXBqV == true){BtuCmVXBqV = false;}
      if(ihiypNWrtN == true){ihiypNWrtN = false;}
      if(VeSFHQRQJX == true){VeSFHQRQJX = false;}
      if(GZCNhdZHRZ == true){GZCNhdZHRZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WQYCHTMFRS
{ 
  void byWojUftIk()
  { 
      bool lsAaiqAzhp = false;
      bool rOtKsLXLxQ = false;
      bool ENjQCbUqdk = false;
      bool sitYQWCVaD = false;
      bool nNhNfVMUEG = false;
      bool WbEYcYJjXH = false;
      bool VJUxwITVtW = false;
      bool ICktbqfWjg = false;
      bool OAlXNReUur = false;
      bool MSySgesjQW = false;
      bool BpahyUpJwl = false;
      bool rmzprVXxie = false;
      bool dzaBJpDSNx = false;
      bool yuFMfYYDYs = false;
      bool aUYIzZSHZK = false;
      bool GuBlsBPYYH = false;
      bool RXwymxglJT = false;
      bool wTXpDIZRBj = false;
      bool WwrCpCsTTd = false;
      bool IAeRaCYZVC = false;
      string mCDopIZhyO;
      string mrDQVrXKxo;
      string VczAgHDCTd;
      string UoknjcyrQM;
      string MCtGLStnaC;
      string nYhJFJCDHh;
      string FXOTsxHPgs;
      string tesjcSisnO;
      string NObQpwHaiZ;
      string ZukiHomZMN;
      string KeHgIIfyfl;
      string ZJOsUpuxdx;
      string pfgGSytKbn;
      string eIfaDhHtIg;
      string QJtwzPgqNR;
      string spwPWdyANK;
      string OUVrGRdmpm;
      string hBoxggkjGD;
      string QDwKuoMQDY;
      string jGfySumCph;
      if(mCDopIZhyO == KeHgIIfyfl){lsAaiqAzhp = true;}
      else if(KeHgIIfyfl == mCDopIZhyO){BpahyUpJwl = true;}
      if(mrDQVrXKxo == ZJOsUpuxdx){rOtKsLXLxQ = true;}
      else if(ZJOsUpuxdx == mrDQVrXKxo){rmzprVXxie = true;}
      if(VczAgHDCTd == pfgGSytKbn){ENjQCbUqdk = true;}
      else if(pfgGSytKbn == VczAgHDCTd){dzaBJpDSNx = true;}
      if(UoknjcyrQM == eIfaDhHtIg){sitYQWCVaD = true;}
      else if(eIfaDhHtIg == UoknjcyrQM){yuFMfYYDYs = true;}
      if(MCtGLStnaC == QJtwzPgqNR){nNhNfVMUEG = true;}
      else if(QJtwzPgqNR == MCtGLStnaC){aUYIzZSHZK = true;}
      if(nYhJFJCDHh == spwPWdyANK){WbEYcYJjXH = true;}
      else if(spwPWdyANK == nYhJFJCDHh){GuBlsBPYYH = true;}
      if(FXOTsxHPgs == OUVrGRdmpm){VJUxwITVtW = true;}
      else if(OUVrGRdmpm == FXOTsxHPgs){RXwymxglJT = true;}
      if(tesjcSisnO == hBoxggkjGD){ICktbqfWjg = true;}
      if(NObQpwHaiZ == QDwKuoMQDY){OAlXNReUur = true;}
      if(ZukiHomZMN == jGfySumCph){MSySgesjQW = true;}
      while(hBoxggkjGD == tesjcSisnO){wTXpDIZRBj = true;}
      while(QDwKuoMQDY == QDwKuoMQDY){WwrCpCsTTd = true;}
      while(jGfySumCph == jGfySumCph){IAeRaCYZVC = true;}
      if(lsAaiqAzhp == true){lsAaiqAzhp = false;}
      if(rOtKsLXLxQ == true){rOtKsLXLxQ = false;}
      if(ENjQCbUqdk == true){ENjQCbUqdk = false;}
      if(sitYQWCVaD == true){sitYQWCVaD = false;}
      if(nNhNfVMUEG == true){nNhNfVMUEG = false;}
      if(WbEYcYJjXH == true){WbEYcYJjXH = false;}
      if(VJUxwITVtW == true){VJUxwITVtW = false;}
      if(ICktbqfWjg == true){ICktbqfWjg = false;}
      if(OAlXNReUur == true){OAlXNReUur = false;}
      if(MSySgesjQW == true){MSySgesjQW = false;}
      if(BpahyUpJwl == true){BpahyUpJwl = false;}
      if(rmzprVXxie == true){rmzprVXxie = false;}
      if(dzaBJpDSNx == true){dzaBJpDSNx = false;}
      if(yuFMfYYDYs == true){yuFMfYYDYs = false;}
      if(aUYIzZSHZK == true){aUYIzZSHZK = false;}
      if(GuBlsBPYYH == true){GuBlsBPYYH = false;}
      if(RXwymxglJT == true){RXwymxglJT = false;}
      if(wTXpDIZRBj == true){wTXpDIZRBj = false;}
      if(WwrCpCsTTd == true){WwrCpCsTTd = false;}
      if(IAeRaCYZVC == true){IAeRaCYZVC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PTZWOHDYBF
{ 
  void QgKmgcdVuG()
  { 
      bool JKEGWMzNci = false;
      bool kBYMZpaiQD = false;
      bool wCUlGHaYgX = false;
      bool WWBfZKkuzE = false;
      bool ROaHFPTuCd = false;
      bool qFGkhGoRAP = false;
      bool lagELOzslP = false;
      bool FeiLkgbMgp = false;
      bool neVDgRPQyS = false;
      bool USuiSphWwp = false;
      bool QZIlXLVuzA = false;
      bool eckKbGFcWt = false;
      bool ziuSuljArt = false;
      bool zEPqYNVjeU = false;
      bool uTQxnqhkHM = false;
      bool kEzCphepqk = false;
      bool bVCFBZMtkO = false;
      bool jUyByeRyeD = false;
      bool EzrfJtFNAq = false;
      bool hfrssYRLuO = false;
      string AoSkYFYgHK;
      string pCYZuIkrAV;
      string wafkjoCmBF;
      string PpzbsCAhwE;
      string WESCAhncns;
      string EGwweZIhBi;
      string ClfBuzCwgs;
      string IDuwzqIdkB;
      string BYzHAItDxT;
      string tSgNBjYQGA;
      string eqwtkBLAxm;
      string QdwzhcmXAm;
      string FzzMzpVhtO;
      string SrXkWJcEWz;
      string wtFJCPVgeX;
      string wAPTteriut;
      string edFhUYGLcX;
      string AiABpLtpKi;
      string UoCWRRcDpq;
      string RsIbTSnWnd;
      if(AoSkYFYgHK == eqwtkBLAxm){JKEGWMzNci = true;}
      else if(eqwtkBLAxm == AoSkYFYgHK){QZIlXLVuzA = true;}
      if(pCYZuIkrAV == QdwzhcmXAm){kBYMZpaiQD = true;}
      else if(QdwzhcmXAm == pCYZuIkrAV){eckKbGFcWt = true;}
      if(wafkjoCmBF == FzzMzpVhtO){wCUlGHaYgX = true;}
      else if(FzzMzpVhtO == wafkjoCmBF){ziuSuljArt = true;}
      if(PpzbsCAhwE == SrXkWJcEWz){WWBfZKkuzE = true;}
      else if(SrXkWJcEWz == PpzbsCAhwE){zEPqYNVjeU = true;}
      if(WESCAhncns == wtFJCPVgeX){ROaHFPTuCd = true;}
      else if(wtFJCPVgeX == WESCAhncns){uTQxnqhkHM = true;}
      if(EGwweZIhBi == wAPTteriut){qFGkhGoRAP = true;}
      else if(wAPTteriut == EGwweZIhBi){kEzCphepqk = true;}
      if(ClfBuzCwgs == edFhUYGLcX){lagELOzslP = true;}
      else if(edFhUYGLcX == ClfBuzCwgs){bVCFBZMtkO = true;}
      if(IDuwzqIdkB == AiABpLtpKi){FeiLkgbMgp = true;}
      if(BYzHAItDxT == UoCWRRcDpq){neVDgRPQyS = true;}
      if(tSgNBjYQGA == RsIbTSnWnd){USuiSphWwp = true;}
      while(AiABpLtpKi == IDuwzqIdkB){jUyByeRyeD = true;}
      while(UoCWRRcDpq == UoCWRRcDpq){EzrfJtFNAq = true;}
      while(RsIbTSnWnd == RsIbTSnWnd){hfrssYRLuO = true;}
      if(JKEGWMzNci == true){JKEGWMzNci = false;}
      if(kBYMZpaiQD == true){kBYMZpaiQD = false;}
      if(wCUlGHaYgX == true){wCUlGHaYgX = false;}
      if(WWBfZKkuzE == true){WWBfZKkuzE = false;}
      if(ROaHFPTuCd == true){ROaHFPTuCd = false;}
      if(qFGkhGoRAP == true){qFGkhGoRAP = false;}
      if(lagELOzslP == true){lagELOzslP = false;}
      if(FeiLkgbMgp == true){FeiLkgbMgp = false;}
      if(neVDgRPQyS == true){neVDgRPQyS = false;}
      if(USuiSphWwp == true){USuiSphWwp = false;}
      if(QZIlXLVuzA == true){QZIlXLVuzA = false;}
      if(eckKbGFcWt == true){eckKbGFcWt = false;}
      if(ziuSuljArt == true){ziuSuljArt = false;}
      if(zEPqYNVjeU == true){zEPqYNVjeU = false;}
      if(uTQxnqhkHM == true){uTQxnqhkHM = false;}
      if(kEzCphepqk == true){kEzCphepqk = false;}
      if(bVCFBZMtkO == true){bVCFBZMtkO = false;}
      if(jUyByeRyeD == true){jUyByeRyeD = false;}
      if(EzrfJtFNAq == true){EzrfJtFNAq = false;}
      if(hfrssYRLuO == true){hfrssYRLuO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CEZTFABXZR
{ 
  void HXplFAelkl()
  { 
      bool mwfshBBWWQ = false;
      bool NMPcJfuUAo = false;
      bool jrlZsXSpiu = false;
      bool VuDAufCYUq = false;
      bool ckfNQPwQyz = false;
      bool RkTnttKGAJ = false;
      bool iLmauRJPgd = false;
      bool dVAILyMYIc = false;
      bool bBqjdkbPFB = false;
      bool UwXKIRxERz = false;
      bool GgjUVujLbu = false;
      bool glyXhhTDwK = false;
      bool psJfIgxpAt = false;
      bool BHGJVtRWNi = false;
      bool AQmJTiyAbZ = false;
      bool ysIHIMWDLn = false;
      bool xsLhtZenBn = false;
      bool QwpNJZFzMY = false;
      bool ixOZwHzyAI = false;
      bool WNLYkHEFPt = false;
      string JjTnutgKXT;
      string XrItKKqtcN;
      string ofNEMEDjsg;
      string NsBclhRZBz;
      string bNnSeyGDDU;
      string BpVlcdWObq;
      string qxRpGdqfIb;
      string rRrclbqtZO;
      string yAfXeXWOzH;
      string KCxJIduxMA;
      string GZtbbjxrAB;
      string lcoMspQtKh;
      string GcfAQpTiUH;
      string ftgYIXFEuu;
      string ZdNyVhNkPR;
      string NBletcttKl;
      string PNXsUquQEV;
      string jLzPHcPgdh;
      string biSCseHCee;
      string cLsIfMGTdd;
      if(JjTnutgKXT == GZtbbjxrAB){mwfshBBWWQ = true;}
      else if(GZtbbjxrAB == JjTnutgKXT){GgjUVujLbu = true;}
      if(XrItKKqtcN == lcoMspQtKh){NMPcJfuUAo = true;}
      else if(lcoMspQtKh == XrItKKqtcN){glyXhhTDwK = true;}
      if(ofNEMEDjsg == GcfAQpTiUH){jrlZsXSpiu = true;}
      else if(GcfAQpTiUH == ofNEMEDjsg){psJfIgxpAt = true;}
      if(NsBclhRZBz == ftgYIXFEuu){VuDAufCYUq = true;}
      else if(ftgYIXFEuu == NsBclhRZBz){BHGJVtRWNi = true;}
      if(bNnSeyGDDU == ZdNyVhNkPR){ckfNQPwQyz = true;}
      else if(ZdNyVhNkPR == bNnSeyGDDU){AQmJTiyAbZ = true;}
      if(BpVlcdWObq == NBletcttKl){RkTnttKGAJ = true;}
      else if(NBletcttKl == BpVlcdWObq){ysIHIMWDLn = true;}
      if(qxRpGdqfIb == PNXsUquQEV){iLmauRJPgd = true;}
      else if(PNXsUquQEV == qxRpGdqfIb){xsLhtZenBn = true;}
      if(rRrclbqtZO == jLzPHcPgdh){dVAILyMYIc = true;}
      if(yAfXeXWOzH == biSCseHCee){bBqjdkbPFB = true;}
      if(KCxJIduxMA == cLsIfMGTdd){UwXKIRxERz = true;}
      while(jLzPHcPgdh == rRrclbqtZO){QwpNJZFzMY = true;}
      while(biSCseHCee == biSCseHCee){ixOZwHzyAI = true;}
      while(cLsIfMGTdd == cLsIfMGTdd){WNLYkHEFPt = true;}
      if(mwfshBBWWQ == true){mwfshBBWWQ = false;}
      if(NMPcJfuUAo == true){NMPcJfuUAo = false;}
      if(jrlZsXSpiu == true){jrlZsXSpiu = false;}
      if(VuDAufCYUq == true){VuDAufCYUq = false;}
      if(ckfNQPwQyz == true){ckfNQPwQyz = false;}
      if(RkTnttKGAJ == true){RkTnttKGAJ = false;}
      if(iLmauRJPgd == true){iLmauRJPgd = false;}
      if(dVAILyMYIc == true){dVAILyMYIc = false;}
      if(bBqjdkbPFB == true){bBqjdkbPFB = false;}
      if(UwXKIRxERz == true){UwXKIRxERz = false;}
      if(GgjUVujLbu == true){GgjUVujLbu = false;}
      if(glyXhhTDwK == true){glyXhhTDwK = false;}
      if(psJfIgxpAt == true){psJfIgxpAt = false;}
      if(BHGJVtRWNi == true){BHGJVtRWNi = false;}
      if(AQmJTiyAbZ == true){AQmJTiyAbZ = false;}
      if(ysIHIMWDLn == true){ysIHIMWDLn = false;}
      if(xsLhtZenBn == true){xsLhtZenBn = false;}
      if(QwpNJZFzMY == true){QwpNJZFzMY = false;}
      if(ixOZwHzyAI == true){ixOZwHzyAI = false;}
      if(WNLYkHEFPt == true){WNLYkHEFPt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FIXKVMJBNE
{ 
  void WtpqYGsFkl()
  { 
      bool GIHrBzLinK = false;
      bool PLVqwfcIsE = false;
      bool MzeAexaFYs = false;
      bool qLGhUmphtP = false;
      bool YBRZOkymOQ = false;
      bool BUBmyGdHME = false;
      bool YFKtTDFnWI = false;
      bool puOcfLhFks = false;
      bool zmpHqVKTiO = false;
      bool IiUoqSpWGK = false;
      bool fJQGZGGXGm = false;
      bool YYVTFkPCCx = false;
      bool skFIzHZYlM = false;
      bool ULzaNoWjgk = false;
      bool PlMupjMBjF = false;
      bool DnTIQtEIGS = false;
      bool fhltSMYuFP = false;
      bool OeURgHXJRP = false;
      bool tYnfJgqpJS = false;
      bool kNdOFhAScc = false;
      string KuYNmVAmwK;
      string TaGXPLilNC;
      string nfmrADRnCJ;
      string ZMmrZqlfma;
      string WfoDrTEPgl;
      string SuHHJdHgMi;
      string EMjmkHnNyX;
      string ZDyleIqjAg;
      string yCHPpeEehu;
      string jESEVKwBRj;
      string fpRIMOxUcB;
      string mXffjCFTwF;
      string DIfCnUktPU;
      string LoRQBIjzDa;
      string hiCgIMYlTT;
      string FbELfWKPTr;
      string dCEHoxFPeb;
      string RGQVXUGysb;
      string wyZwOjkFje;
      string xUeLwedtrL;
      if(KuYNmVAmwK == fpRIMOxUcB){GIHrBzLinK = true;}
      else if(fpRIMOxUcB == KuYNmVAmwK){fJQGZGGXGm = true;}
      if(TaGXPLilNC == mXffjCFTwF){PLVqwfcIsE = true;}
      else if(mXffjCFTwF == TaGXPLilNC){YYVTFkPCCx = true;}
      if(nfmrADRnCJ == DIfCnUktPU){MzeAexaFYs = true;}
      else if(DIfCnUktPU == nfmrADRnCJ){skFIzHZYlM = true;}
      if(ZMmrZqlfma == LoRQBIjzDa){qLGhUmphtP = true;}
      else if(LoRQBIjzDa == ZMmrZqlfma){ULzaNoWjgk = true;}
      if(WfoDrTEPgl == hiCgIMYlTT){YBRZOkymOQ = true;}
      else if(hiCgIMYlTT == WfoDrTEPgl){PlMupjMBjF = true;}
      if(SuHHJdHgMi == FbELfWKPTr){BUBmyGdHME = true;}
      else if(FbELfWKPTr == SuHHJdHgMi){DnTIQtEIGS = true;}
      if(EMjmkHnNyX == dCEHoxFPeb){YFKtTDFnWI = true;}
      else if(dCEHoxFPeb == EMjmkHnNyX){fhltSMYuFP = true;}
      if(ZDyleIqjAg == RGQVXUGysb){puOcfLhFks = true;}
      if(yCHPpeEehu == wyZwOjkFje){zmpHqVKTiO = true;}
      if(jESEVKwBRj == xUeLwedtrL){IiUoqSpWGK = true;}
      while(RGQVXUGysb == ZDyleIqjAg){OeURgHXJRP = true;}
      while(wyZwOjkFje == wyZwOjkFje){tYnfJgqpJS = true;}
      while(xUeLwedtrL == xUeLwedtrL){kNdOFhAScc = true;}
      if(GIHrBzLinK == true){GIHrBzLinK = false;}
      if(PLVqwfcIsE == true){PLVqwfcIsE = false;}
      if(MzeAexaFYs == true){MzeAexaFYs = false;}
      if(qLGhUmphtP == true){qLGhUmphtP = false;}
      if(YBRZOkymOQ == true){YBRZOkymOQ = false;}
      if(BUBmyGdHME == true){BUBmyGdHME = false;}
      if(YFKtTDFnWI == true){YFKtTDFnWI = false;}
      if(puOcfLhFks == true){puOcfLhFks = false;}
      if(zmpHqVKTiO == true){zmpHqVKTiO = false;}
      if(IiUoqSpWGK == true){IiUoqSpWGK = false;}
      if(fJQGZGGXGm == true){fJQGZGGXGm = false;}
      if(YYVTFkPCCx == true){YYVTFkPCCx = false;}
      if(skFIzHZYlM == true){skFIzHZYlM = false;}
      if(ULzaNoWjgk == true){ULzaNoWjgk = false;}
      if(PlMupjMBjF == true){PlMupjMBjF = false;}
      if(DnTIQtEIGS == true){DnTIQtEIGS = false;}
      if(fhltSMYuFP == true){fhltSMYuFP = false;}
      if(OeURgHXJRP == true){OeURgHXJRP = false;}
      if(tYnfJgqpJS == true){tYnfJgqpJS = false;}
      if(kNdOFhAScc == true){kNdOFhAScc = false;}
    } 
}; 
