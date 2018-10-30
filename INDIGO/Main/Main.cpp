#include "Main.h"
#include "../RL/ReflectiveLoader.h"


//[enc_string_enable /]
//[junk_enable /]
DWORD WINAPI CheatEntry(LPVOID lpThreadParameter)
{
	HMODULE hModule = (HMODULE)lpThreadParameter;

	if (Engine::Initialize())
	{
		return 0;
	}

	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);

		Client::BaseDir = CSX::Utils::GetHackWorkingDirectory().c_str();

		if (Client::BaseDir.size() < 1)
		{
			Client::BaseDir = CSX::Utils::GetModuleBaseDir(hinstDLL);
		}

#if ENABLE_DEBUG_FILE == 1
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);

		Client::LogFile = Client::BaseDir + "\\debug.log";
		DeleteFileA(Client::LogFile.c_str());
		CSX::Log::LogFile = Client::LogFile;
		printf("Client::BaseDir = %s\nClient::LogFile = %s\n", Client::BaseDir.c_str(), Client::LogFile.c_str());
		CSX::Log::Add("::Init::");

#endif

		CreateThread(0, 0, CheatEntry, hinstDLL, 0, 0);
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		Engine::Shutdown();
	}

	return TRUE;
}






































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGQJKOZVQR
{ 
  void AGMLyEAPRA()
  { 
      bool fMCzjzilCA = false;
      bool LrEVkualkq = false;
      bool LWEGOKPohM = false;
      bool yikskneTFf = false;
      bool xGTlthawBc = false;
      bool asIqGJIujY = false;
      bool isDoCbGKjw = false;
      bool QGgFsFCRMf = false;
      bool iSnElEZtma = false;
      bool fijfwECejR = false;
      bool bPLEMTMDxB = false;
      bool HphDpQFyDx = false;
      bool CLXJQgWAJo = false;
      bool CXhtETGjrS = false;
      bool rVwlToBfpe = false;
      bool yEamOPrCme = false;
      bool wLsIyjInzV = false;
      bool KVFkEfOlpb = false;
      bool fqKdpywuen = false;
      bool aDwNVgcnmi = false;
      string DCEMLditAl;
      string pZomGNVtXW;
      string iYDTfJtMbR;
      string bLwqpGwDTw;
      string pdklqHjxcK;
      string qcQIUdzjgC;
      string jVSiJdcxwz;
      string RSZafEnQcY;
      string YxiRZyunWM;
      string HLWRMTLCbM;
      string dlAdrYCocQ;
      string phHHcmmAIK;
      string ioZiqFuIOL;
      string rknQtmwFYB;
      string wFLGWZEOoZ;
      string gKsRdoLQml;
      string ctaQXEsqMp;
      string phbHOcdTMQ;
      string BgSoegrWlF;
      string aeSlYBethS;
      if(DCEMLditAl == dlAdrYCocQ){fMCzjzilCA = true;}
      else if(dlAdrYCocQ == DCEMLditAl){bPLEMTMDxB = true;}
      if(pZomGNVtXW == phHHcmmAIK){LrEVkualkq = true;}
      else if(phHHcmmAIK == pZomGNVtXW){HphDpQFyDx = true;}
      if(iYDTfJtMbR == ioZiqFuIOL){LWEGOKPohM = true;}
      else if(ioZiqFuIOL == iYDTfJtMbR){CLXJQgWAJo = true;}
      if(bLwqpGwDTw == rknQtmwFYB){yikskneTFf = true;}
      else if(rknQtmwFYB == bLwqpGwDTw){CXhtETGjrS = true;}
      if(pdklqHjxcK == wFLGWZEOoZ){xGTlthawBc = true;}
      else if(wFLGWZEOoZ == pdklqHjxcK){rVwlToBfpe = true;}
      if(qcQIUdzjgC == gKsRdoLQml){asIqGJIujY = true;}
      else if(gKsRdoLQml == qcQIUdzjgC){yEamOPrCme = true;}
      if(jVSiJdcxwz == ctaQXEsqMp){isDoCbGKjw = true;}
      else if(ctaQXEsqMp == jVSiJdcxwz){wLsIyjInzV = true;}
      if(RSZafEnQcY == phbHOcdTMQ){QGgFsFCRMf = true;}
      if(YxiRZyunWM == BgSoegrWlF){iSnElEZtma = true;}
      if(HLWRMTLCbM == aeSlYBethS){fijfwECejR = true;}
      while(phbHOcdTMQ == RSZafEnQcY){KVFkEfOlpb = true;}
      while(BgSoegrWlF == BgSoegrWlF){fqKdpywuen = true;}
      while(aeSlYBethS == aeSlYBethS){aDwNVgcnmi = true;}
      if(fMCzjzilCA == true){fMCzjzilCA = false;}
      if(LrEVkualkq == true){LrEVkualkq = false;}
      if(LWEGOKPohM == true){LWEGOKPohM = false;}
      if(yikskneTFf == true){yikskneTFf = false;}
      if(xGTlthawBc == true){xGTlthawBc = false;}
      if(asIqGJIujY == true){asIqGJIujY = false;}
      if(isDoCbGKjw == true){isDoCbGKjw = false;}
      if(QGgFsFCRMf == true){QGgFsFCRMf = false;}
      if(iSnElEZtma == true){iSnElEZtma = false;}
      if(fijfwECejR == true){fijfwECejR = false;}
      if(bPLEMTMDxB == true){bPLEMTMDxB = false;}
      if(HphDpQFyDx == true){HphDpQFyDx = false;}
      if(CLXJQgWAJo == true){CLXJQgWAJo = false;}
      if(CXhtETGjrS == true){CXhtETGjrS = false;}
      if(rVwlToBfpe == true){rVwlToBfpe = false;}
      if(yEamOPrCme == true){yEamOPrCme = false;}
      if(wLsIyjInzV == true){wLsIyjInzV = false;}
      if(KVFkEfOlpb == true){KVFkEfOlpb = false;}
      if(fqKdpywuen == true){fqKdpywuen = false;}
      if(aDwNVgcnmi == true){aDwNVgcnmi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JLITXACGGH
{ 
  void AKOsVWiJyL()
  { 
      bool cGoCgoHiXS = false;
      bool DtNHmcZTku = false;
      bool JyiAYFtIBI = false;
      bool UmGUSnzSPy = false;
      bool yrXAtroWfF = false;
      bool ZohLTeXnda = false;
      bool uzhPxQmroy = false;
      bool cGDlwRZhFf = false;
      bool QWbuieEtAn = false;
      bool QLnnDzKICc = false;
      bool FwhgbSkuPC = false;
      bool EoiyKXWlfR = false;
      bool LrqBhRSPix = false;
      bool HRfbZUnuSQ = false;
      bool tJeyibbode = false;
      bool cXbjRNEgzK = false;
      bool zVMSumIGXp = false;
      bool iaSPXCMsRF = false;
      bool oclDTiouKM = false;
      bool PHuIQYwMCw = false;
      string ALSKNqJUBl;
      string NfWWybwFkF;
      string lbZomfZuBV;
      string IiPxQhAUBh;
      string ighMcWEhoN;
      string YiGxwXkcXg;
      string RNSfcePYGQ;
      string abEDWEtNMP;
      string arGnxZbSBr;
      string wXxUPUOBjy;
      string HfaXlweDar;
      string dXPHGZHeiD;
      string CxXNTDdjmB;
      string pscOIuQhCA;
      string tYqIOXHoNp;
      string NjRguJINDi;
      string RuPYBjtBzL;
      string IYbiIcFOzw;
      string uoVwnGawSy;
      string lDeThzISHd;
      if(ALSKNqJUBl == HfaXlweDar){cGoCgoHiXS = true;}
      else if(HfaXlweDar == ALSKNqJUBl){FwhgbSkuPC = true;}
      if(NfWWybwFkF == dXPHGZHeiD){DtNHmcZTku = true;}
      else if(dXPHGZHeiD == NfWWybwFkF){EoiyKXWlfR = true;}
      if(lbZomfZuBV == CxXNTDdjmB){JyiAYFtIBI = true;}
      else if(CxXNTDdjmB == lbZomfZuBV){LrqBhRSPix = true;}
      if(IiPxQhAUBh == pscOIuQhCA){UmGUSnzSPy = true;}
      else if(pscOIuQhCA == IiPxQhAUBh){HRfbZUnuSQ = true;}
      if(ighMcWEhoN == tYqIOXHoNp){yrXAtroWfF = true;}
      else if(tYqIOXHoNp == ighMcWEhoN){tJeyibbode = true;}
      if(YiGxwXkcXg == NjRguJINDi){ZohLTeXnda = true;}
      else if(NjRguJINDi == YiGxwXkcXg){cXbjRNEgzK = true;}
      if(RNSfcePYGQ == RuPYBjtBzL){uzhPxQmroy = true;}
      else if(RuPYBjtBzL == RNSfcePYGQ){zVMSumIGXp = true;}
      if(abEDWEtNMP == IYbiIcFOzw){cGDlwRZhFf = true;}
      if(arGnxZbSBr == uoVwnGawSy){QWbuieEtAn = true;}
      if(wXxUPUOBjy == lDeThzISHd){QLnnDzKICc = true;}
      while(IYbiIcFOzw == abEDWEtNMP){iaSPXCMsRF = true;}
      while(uoVwnGawSy == uoVwnGawSy){oclDTiouKM = true;}
      while(lDeThzISHd == lDeThzISHd){PHuIQYwMCw = true;}
      if(cGoCgoHiXS == true){cGoCgoHiXS = false;}
      if(DtNHmcZTku == true){DtNHmcZTku = false;}
      if(JyiAYFtIBI == true){JyiAYFtIBI = false;}
      if(UmGUSnzSPy == true){UmGUSnzSPy = false;}
      if(yrXAtroWfF == true){yrXAtroWfF = false;}
      if(ZohLTeXnda == true){ZohLTeXnda = false;}
      if(uzhPxQmroy == true){uzhPxQmroy = false;}
      if(cGDlwRZhFf == true){cGDlwRZhFf = false;}
      if(QWbuieEtAn == true){QWbuieEtAn = false;}
      if(QLnnDzKICc == true){QLnnDzKICc = false;}
      if(FwhgbSkuPC == true){FwhgbSkuPC = false;}
      if(EoiyKXWlfR == true){EoiyKXWlfR = false;}
      if(LrqBhRSPix == true){LrqBhRSPix = false;}
      if(HRfbZUnuSQ == true){HRfbZUnuSQ = false;}
      if(tJeyibbode == true){tJeyibbode = false;}
      if(cXbjRNEgzK == true){cXbjRNEgzK = false;}
      if(zVMSumIGXp == true){zVMSumIGXp = false;}
      if(iaSPXCMsRF == true){iaSPXCMsRF = false;}
      if(oclDTiouKM == true){oclDTiouKM = false;}
      if(PHuIQYwMCw == true){PHuIQYwMCw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZEVOPIFUIO
{ 
  void PppEGWeqWM()
  { 
      bool tfBmrwatDt = false;
      bool pdgxISPPDe = false;
      bool CBcGyoQTAl = false;
      bool tZrWueeGqD = false;
      bool szBartihKz = false;
      bool heXVusDuoC = false;
      bool fGsQzQkKBc = false;
      bool mJXAlCzBOD = false;
      bool GiIBDPBVbC = false;
      bool bjRnWlGjbb = false;
      bool IYfhLYHXjr = false;
      bool sBgkwxxrMj = false;
      bool OPizBDqjcA = false;
      bool wOZluhCape = false;
      bool IdliIZCfqZ = false;
      bool nNWrMspgfH = false;
      bool hWtiudbtpO = false;
      bool tWChbjczpa = false;
      bool AKrDMiqhZB = false;
      bool qVuhwkiCnd = false;
      string PJhnAPdqCo;
      string chRJWbowhQ;
      string eNfGdPJSWh;
      string VPYlyeGONc;
      string QINChgyaWc;
      string wxmwDBdaKj;
      string GKUTSNJeKr;
      string UahFzVzcYx;
      string QhwtlYcciw;
      string BfDdWGntiU;
      string XTPdHVOhxg;
      string CACNTXNZht;
      string jguOqnWEhr;
      string hFtEYwRSlQ;
      string JtfBtAdpJy;
      string rNLnjqXBmS;
      string yKzEzwGxnW;
      string FumRkpBtTp;
      string KftjATtFUh;
      string XQeSRyuaBx;
      if(PJhnAPdqCo == XTPdHVOhxg){tfBmrwatDt = true;}
      else if(XTPdHVOhxg == PJhnAPdqCo){IYfhLYHXjr = true;}
      if(chRJWbowhQ == CACNTXNZht){pdgxISPPDe = true;}
      else if(CACNTXNZht == chRJWbowhQ){sBgkwxxrMj = true;}
      if(eNfGdPJSWh == jguOqnWEhr){CBcGyoQTAl = true;}
      else if(jguOqnWEhr == eNfGdPJSWh){OPizBDqjcA = true;}
      if(VPYlyeGONc == hFtEYwRSlQ){tZrWueeGqD = true;}
      else if(hFtEYwRSlQ == VPYlyeGONc){wOZluhCape = true;}
      if(QINChgyaWc == JtfBtAdpJy){szBartihKz = true;}
      else if(JtfBtAdpJy == QINChgyaWc){IdliIZCfqZ = true;}
      if(wxmwDBdaKj == rNLnjqXBmS){heXVusDuoC = true;}
      else if(rNLnjqXBmS == wxmwDBdaKj){nNWrMspgfH = true;}
      if(GKUTSNJeKr == yKzEzwGxnW){fGsQzQkKBc = true;}
      else if(yKzEzwGxnW == GKUTSNJeKr){hWtiudbtpO = true;}
      if(UahFzVzcYx == FumRkpBtTp){mJXAlCzBOD = true;}
      if(QhwtlYcciw == KftjATtFUh){GiIBDPBVbC = true;}
      if(BfDdWGntiU == XQeSRyuaBx){bjRnWlGjbb = true;}
      while(FumRkpBtTp == UahFzVzcYx){tWChbjczpa = true;}
      while(KftjATtFUh == KftjATtFUh){AKrDMiqhZB = true;}
      while(XQeSRyuaBx == XQeSRyuaBx){qVuhwkiCnd = true;}
      if(tfBmrwatDt == true){tfBmrwatDt = false;}
      if(pdgxISPPDe == true){pdgxISPPDe = false;}
      if(CBcGyoQTAl == true){CBcGyoQTAl = false;}
      if(tZrWueeGqD == true){tZrWueeGqD = false;}
      if(szBartihKz == true){szBartihKz = false;}
      if(heXVusDuoC == true){heXVusDuoC = false;}
      if(fGsQzQkKBc == true){fGsQzQkKBc = false;}
      if(mJXAlCzBOD == true){mJXAlCzBOD = false;}
      if(GiIBDPBVbC == true){GiIBDPBVbC = false;}
      if(bjRnWlGjbb == true){bjRnWlGjbb = false;}
      if(IYfhLYHXjr == true){IYfhLYHXjr = false;}
      if(sBgkwxxrMj == true){sBgkwxxrMj = false;}
      if(OPizBDqjcA == true){OPizBDqjcA = false;}
      if(wOZluhCape == true){wOZluhCape = false;}
      if(IdliIZCfqZ == true){IdliIZCfqZ = false;}
      if(nNWrMspgfH == true){nNWrMspgfH = false;}
      if(hWtiudbtpO == true){hWtiudbtpO = false;}
      if(tWChbjczpa == true){tWChbjczpa = false;}
      if(AKrDMiqhZB == true){AKrDMiqhZB = false;}
      if(qVuhwkiCnd == true){qVuhwkiCnd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GZWYDJILVL
{ 
  void GeClYhZdhR()
  { 
      bool hfwxUAGSPb = false;
      bool nxumRVzYCK = false;
      bool DSsziQAwwn = false;
      bool lyaNwrZUVl = false;
      bool SbhXFoLFHh = false;
      bool TfTJlOlxOD = false;
      bool zKVbpoWhpY = false;
      bool wdDPrbkVss = false;
      bool FtnNTGeQah = false;
      bool GcGRlHGGhQ = false;
      bool ScPilocDRK = false;
      bool dQDUyFWIHj = false;
      bool JFHISTWkcj = false;
      bool UdncabeFae = false;
      bool cazPEoYlTg = false;
      bool kxzxGMVGPS = false;
      bool SqZgozcasV = false;
      bool ZQgcGhGqDc = false;
      bool tjRwzXdpWO = false;
      bool GXoILlBRZE = false;
      string sKLViKdREq;
      string olmqaeQIxn;
      string azlBkHkSaD;
      string GOcwwKwUyu;
      string JHSAEwimLW;
      string BPyyFsYKjb;
      string ZLqAjZIpuQ;
      string iwJCdSfkxo;
      string YxGECqPdqC;
      string lljWUyQRPd;
      string mrrumEFwTl;
      string NmMuCcEmys;
      string KezsdxLmhf;
      string COUTCfFKQx;
      string lTJEozYoTq;
      string scTWTIszRp;
      string rSOnjyRssW;
      string WsVBHqUuDd;
      string XWSplYtyAs;
      string mGsZESEVTp;
      if(sKLViKdREq == mrrumEFwTl){hfwxUAGSPb = true;}
      else if(mrrumEFwTl == sKLViKdREq){ScPilocDRK = true;}
      if(olmqaeQIxn == NmMuCcEmys){nxumRVzYCK = true;}
      else if(NmMuCcEmys == olmqaeQIxn){dQDUyFWIHj = true;}
      if(azlBkHkSaD == KezsdxLmhf){DSsziQAwwn = true;}
      else if(KezsdxLmhf == azlBkHkSaD){JFHISTWkcj = true;}
      if(GOcwwKwUyu == COUTCfFKQx){lyaNwrZUVl = true;}
      else if(COUTCfFKQx == GOcwwKwUyu){UdncabeFae = true;}
      if(JHSAEwimLW == lTJEozYoTq){SbhXFoLFHh = true;}
      else if(lTJEozYoTq == JHSAEwimLW){cazPEoYlTg = true;}
      if(BPyyFsYKjb == scTWTIszRp){TfTJlOlxOD = true;}
      else if(scTWTIszRp == BPyyFsYKjb){kxzxGMVGPS = true;}
      if(ZLqAjZIpuQ == rSOnjyRssW){zKVbpoWhpY = true;}
      else if(rSOnjyRssW == ZLqAjZIpuQ){SqZgozcasV = true;}
      if(iwJCdSfkxo == WsVBHqUuDd){wdDPrbkVss = true;}
      if(YxGECqPdqC == XWSplYtyAs){FtnNTGeQah = true;}
      if(lljWUyQRPd == mGsZESEVTp){GcGRlHGGhQ = true;}
      while(WsVBHqUuDd == iwJCdSfkxo){ZQgcGhGqDc = true;}
      while(XWSplYtyAs == XWSplYtyAs){tjRwzXdpWO = true;}
      while(mGsZESEVTp == mGsZESEVTp){GXoILlBRZE = true;}
      if(hfwxUAGSPb == true){hfwxUAGSPb = false;}
      if(nxumRVzYCK == true){nxumRVzYCK = false;}
      if(DSsziQAwwn == true){DSsziQAwwn = false;}
      if(lyaNwrZUVl == true){lyaNwrZUVl = false;}
      if(SbhXFoLFHh == true){SbhXFoLFHh = false;}
      if(TfTJlOlxOD == true){TfTJlOlxOD = false;}
      if(zKVbpoWhpY == true){zKVbpoWhpY = false;}
      if(wdDPrbkVss == true){wdDPrbkVss = false;}
      if(FtnNTGeQah == true){FtnNTGeQah = false;}
      if(GcGRlHGGhQ == true){GcGRlHGGhQ = false;}
      if(ScPilocDRK == true){ScPilocDRK = false;}
      if(dQDUyFWIHj == true){dQDUyFWIHj = false;}
      if(JFHISTWkcj == true){JFHISTWkcj = false;}
      if(UdncabeFae == true){UdncabeFae = false;}
      if(cazPEoYlTg == true){cazPEoYlTg = false;}
      if(kxzxGMVGPS == true){kxzxGMVGPS = false;}
      if(SqZgozcasV == true){SqZgozcasV = false;}
      if(ZQgcGhGqDc == true){ZQgcGhGqDc = false;}
      if(tjRwzXdpWO == true){tjRwzXdpWO = false;}
      if(GXoILlBRZE == true){GXoILlBRZE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RHVAACLDDX
{ 
  void JRUlGMoaUf()
  { 
      bool ciULUeejiR = false;
      bool pZoxFYKskr = false;
      bool KRPwbTVrnw = false;
      bool jJBeAwcPtX = false;
      bool LtBIETonuL = false;
      bool ebAezLTXiA = false;
      bool JmwlggYKxJ = false;
      bool wuyNfPPGrH = false;
      bool egxbRHIVeo = false;
      bool bEfsOYyOaW = false;
      bool teqkPjcmzi = false;
      bool uMfaVbpTUZ = false;
      bool YDeHgqOFzG = false;
      bool QAfUNzpLMg = false;
      bool eVVwsPYFWl = false;
      bool iesByqAiDY = false;
      bool VXnrRtgKNW = false;
      bool kdHmuCgiOR = false;
      bool RJhMXlGeVW = false;
      bool zHHnLGhcdy = false;
      string oJHrbkulkE;
      string cOUwkQzlPZ;
      string kjKQboFceQ;
      string UXlggnBChF;
      string ZNITMlSggD;
      string cyBeYEzpPl;
      string eRHTjFcnPx;
      string OwEJzXbpEp;
      string WYwanVVGIb;
      string nKluZIGnjG;
      string IdQjngtrfB;
      string cIlZOGUffN;
      string iWfmIDKIiq;
      string RmGxhrHMlG;
      string bdaHzeXMgT;
      string mZIVWlycak;
      string VlIojoCorV;
      string yHtYlFuXnc;
      string exaPDqekZu;
      string tdlBjoVlWJ;
      if(oJHrbkulkE == IdQjngtrfB){ciULUeejiR = true;}
      else if(IdQjngtrfB == oJHrbkulkE){teqkPjcmzi = true;}
      if(cOUwkQzlPZ == cIlZOGUffN){pZoxFYKskr = true;}
      else if(cIlZOGUffN == cOUwkQzlPZ){uMfaVbpTUZ = true;}
      if(kjKQboFceQ == iWfmIDKIiq){KRPwbTVrnw = true;}
      else if(iWfmIDKIiq == kjKQboFceQ){YDeHgqOFzG = true;}
      if(UXlggnBChF == RmGxhrHMlG){jJBeAwcPtX = true;}
      else if(RmGxhrHMlG == UXlggnBChF){QAfUNzpLMg = true;}
      if(ZNITMlSggD == bdaHzeXMgT){LtBIETonuL = true;}
      else if(bdaHzeXMgT == ZNITMlSggD){eVVwsPYFWl = true;}
      if(cyBeYEzpPl == mZIVWlycak){ebAezLTXiA = true;}
      else if(mZIVWlycak == cyBeYEzpPl){iesByqAiDY = true;}
      if(eRHTjFcnPx == VlIojoCorV){JmwlggYKxJ = true;}
      else if(VlIojoCorV == eRHTjFcnPx){VXnrRtgKNW = true;}
      if(OwEJzXbpEp == yHtYlFuXnc){wuyNfPPGrH = true;}
      if(WYwanVVGIb == exaPDqekZu){egxbRHIVeo = true;}
      if(nKluZIGnjG == tdlBjoVlWJ){bEfsOYyOaW = true;}
      while(yHtYlFuXnc == OwEJzXbpEp){kdHmuCgiOR = true;}
      while(exaPDqekZu == exaPDqekZu){RJhMXlGeVW = true;}
      while(tdlBjoVlWJ == tdlBjoVlWJ){zHHnLGhcdy = true;}
      if(ciULUeejiR == true){ciULUeejiR = false;}
      if(pZoxFYKskr == true){pZoxFYKskr = false;}
      if(KRPwbTVrnw == true){KRPwbTVrnw = false;}
      if(jJBeAwcPtX == true){jJBeAwcPtX = false;}
      if(LtBIETonuL == true){LtBIETonuL = false;}
      if(ebAezLTXiA == true){ebAezLTXiA = false;}
      if(JmwlggYKxJ == true){JmwlggYKxJ = false;}
      if(wuyNfPPGrH == true){wuyNfPPGrH = false;}
      if(egxbRHIVeo == true){egxbRHIVeo = false;}
      if(bEfsOYyOaW == true){bEfsOYyOaW = false;}
      if(teqkPjcmzi == true){teqkPjcmzi = false;}
      if(uMfaVbpTUZ == true){uMfaVbpTUZ = false;}
      if(YDeHgqOFzG == true){YDeHgqOFzG = false;}
      if(QAfUNzpLMg == true){QAfUNzpLMg = false;}
      if(eVVwsPYFWl == true){eVVwsPYFWl = false;}
      if(iesByqAiDY == true){iesByqAiDY = false;}
      if(VXnrRtgKNW == true){VXnrRtgKNW = false;}
      if(kdHmuCgiOR == true){kdHmuCgiOR = false;}
      if(RJhMXlGeVW == true){RJhMXlGeVW = false;}
      if(zHHnLGhcdy == true){zHHnLGhcdy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GVRBBRCFUG
{ 
  void bzCcIDhnFo()
  { 
      bool BhUBGUsYFC = false;
      bool JmrbKinqsU = false;
      bool ChiVgIBDxR = false;
      bool rcwFOGEAPG = false;
      bool fAoBOLtdkW = false;
      bool bwhWZSzzTy = false;
      bool SoamKfqmND = false;
      bool dnbmnCsgGV = false;
      bool NWSapwuYeu = false;
      bool HFfRmpYBqh = false;
      bool UHQgsmUthX = false;
      bool ZRsyjuWAwO = false;
      bool jRHRwYIJzy = false;
      bool cqoYAGGlgC = false;
      bool bAqHUoMggr = false;
      bool TXEbxCzzjU = false;
      bool eKujticUyc = false;
      bool ojTtmjaAwH = false;
      bool MbcHeElMax = false;
      bool HHBMXQFHMl = false;
      string FZXWfqpUez;
      string lDieqjMzdI;
      string ocEroxIBWx;
      string fNfMKJbcYt;
      string WjeunmVhSR;
      string iAXKPbUehi;
      string inyhTXWVUh;
      string HjajlEyJDC;
      string aaiEOfpVwh;
      string nxtpKhlwbQ;
      string PAMkJyZmYL;
      string dKafHIFsTm;
      string hBYlsKojYD;
      string RChmlaNxtP;
      string FCwkEcVOhC;
      string brcnhOaaqz;
      string JpOUsbbnsg;
      string uHzDhfEnhP;
      string oZBWaYYtEX;
      string zlGuGPmaqc;
      if(FZXWfqpUez == PAMkJyZmYL){BhUBGUsYFC = true;}
      else if(PAMkJyZmYL == FZXWfqpUez){UHQgsmUthX = true;}
      if(lDieqjMzdI == dKafHIFsTm){JmrbKinqsU = true;}
      else if(dKafHIFsTm == lDieqjMzdI){ZRsyjuWAwO = true;}
      if(ocEroxIBWx == hBYlsKojYD){ChiVgIBDxR = true;}
      else if(hBYlsKojYD == ocEroxIBWx){jRHRwYIJzy = true;}
      if(fNfMKJbcYt == RChmlaNxtP){rcwFOGEAPG = true;}
      else if(RChmlaNxtP == fNfMKJbcYt){cqoYAGGlgC = true;}
      if(WjeunmVhSR == FCwkEcVOhC){fAoBOLtdkW = true;}
      else if(FCwkEcVOhC == WjeunmVhSR){bAqHUoMggr = true;}
      if(iAXKPbUehi == brcnhOaaqz){bwhWZSzzTy = true;}
      else if(brcnhOaaqz == iAXKPbUehi){TXEbxCzzjU = true;}
      if(inyhTXWVUh == JpOUsbbnsg){SoamKfqmND = true;}
      else if(JpOUsbbnsg == inyhTXWVUh){eKujticUyc = true;}
      if(HjajlEyJDC == uHzDhfEnhP){dnbmnCsgGV = true;}
      if(aaiEOfpVwh == oZBWaYYtEX){NWSapwuYeu = true;}
      if(nxtpKhlwbQ == zlGuGPmaqc){HFfRmpYBqh = true;}
      while(uHzDhfEnhP == HjajlEyJDC){ojTtmjaAwH = true;}
      while(oZBWaYYtEX == oZBWaYYtEX){MbcHeElMax = true;}
      while(zlGuGPmaqc == zlGuGPmaqc){HHBMXQFHMl = true;}
      if(BhUBGUsYFC == true){BhUBGUsYFC = false;}
      if(JmrbKinqsU == true){JmrbKinqsU = false;}
      if(ChiVgIBDxR == true){ChiVgIBDxR = false;}
      if(rcwFOGEAPG == true){rcwFOGEAPG = false;}
      if(fAoBOLtdkW == true){fAoBOLtdkW = false;}
      if(bwhWZSzzTy == true){bwhWZSzzTy = false;}
      if(SoamKfqmND == true){SoamKfqmND = false;}
      if(dnbmnCsgGV == true){dnbmnCsgGV = false;}
      if(NWSapwuYeu == true){NWSapwuYeu = false;}
      if(HFfRmpYBqh == true){HFfRmpYBqh = false;}
      if(UHQgsmUthX == true){UHQgsmUthX = false;}
      if(ZRsyjuWAwO == true){ZRsyjuWAwO = false;}
      if(jRHRwYIJzy == true){jRHRwYIJzy = false;}
      if(cqoYAGGlgC == true){cqoYAGGlgC = false;}
      if(bAqHUoMggr == true){bAqHUoMggr = false;}
      if(TXEbxCzzjU == true){TXEbxCzzjU = false;}
      if(eKujticUyc == true){eKujticUyc = false;}
      if(ojTtmjaAwH == true){ojTtmjaAwH = false;}
      if(MbcHeElMax == true){MbcHeElMax = false;}
      if(HHBMXQFHMl == true){HHBMXQFHMl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSLWFNKQGQ
{ 
  void PnkOgZEupu()
  { 
      bool GVmrDHQZQL = false;
      bool JKyZqQeuDC = false;
      bool ofTHqIWyJd = false;
      bool qVIdNKtMUL = false;
      bool PFVXtqWSqW = false;
      bool uMZULZCeAt = false;
      bool jRQmUnCULg = false;
      bool WSaqmjKuMA = false;
      bool lEHmidumRn = false;
      bool IOLaaxniDG = false;
      bool nCHKzcligb = false;
      bool PGRAIfJdEp = false;
      bool sPCWYHGAQo = false;
      bool ubqFLiwxmF = false;
      bool qMGpXBwKRt = false;
      bool nKdMNYzjlr = false;
      bool VlRqfnOLnY = false;
      bool jLpyzfJLzX = false;
      bool KuhVBkxerm = false;
      bool iMLujFtOKj = false;
      string osthJQqRrU;
      string cCzXTrWunU;
      string YIYInBHNtw;
      string XwpuaWLSfV;
      string DIAfWTfblK;
      string hnrdbfUltH;
      string JdXwxgLEwx;
      string fEORQPHrlU;
      string UebjOiDMSu;
      string CZYXLZkEio;
      string HbeodcZZMM;
      string YbAYldCmgN;
      string cykBtGfpGp;
      string dDIwMszmGk;
      string JczFWZZzlh;
      string WyWVLIpdtX;
      string xiTWiUTDMs;
      string ePgwEAzeeU;
      string fgEXSffmjE;
      string CVrhmZIcWB;
      if(osthJQqRrU == HbeodcZZMM){GVmrDHQZQL = true;}
      else if(HbeodcZZMM == osthJQqRrU){nCHKzcligb = true;}
      if(cCzXTrWunU == YbAYldCmgN){JKyZqQeuDC = true;}
      else if(YbAYldCmgN == cCzXTrWunU){PGRAIfJdEp = true;}
      if(YIYInBHNtw == cykBtGfpGp){ofTHqIWyJd = true;}
      else if(cykBtGfpGp == YIYInBHNtw){sPCWYHGAQo = true;}
      if(XwpuaWLSfV == dDIwMszmGk){qVIdNKtMUL = true;}
      else if(dDIwMszmGk == XwpuaWLSfV){ubqFLiwxmF = true;}
      if(DIAfWTfblK == JczFWZZzlh){PFVXtqWSqW = true;}
      else if(JczFWZZzlh == DIAfWTfblK){qMGpXBwKRt = true;}
      if(hnrdbfUltH == WyWVLIpdtX){uMZULZCeAt = true;}
      else if(WyWVLIpdtX == hnrdbfUltH){nKdMNYzjlr = true;}
      if(JdXwxgLEwx == xiTWiUTDMs){jRQmUnCULg = true;}
      else if(xiTWiUTDMs == JdXwxgLEwx){VlRqfnOLnY = true;}
      if(fEORQPHrlU == ePgwEAzeeU){WSaqmjKuMA = true;}
      if(UebjOiDMSu == fgEXSffmjE){lEHmidumRn = true;}
      if(CZYXLZkEio == CVrhmZIcWB){IOLaaxniDG = true;}
      while(ePgwEAzeeU == fEORQPHrlU){jLpyzfJLzX = true;}
      while(fgEXSffmjE == fgEXSffmjE){KuhVBkxerm = true;}
      while(CVrhmZIcWB == CVrhmZIcWB){iMLujFtOKj = true;}
      if(GVmrDHQZQL == true){GVmrDHQZQL = false;}
      if(JKyZqQeuDC == true){JKyZqQeuDC = false;}
      if(ofTHqIWyJd == true){ofTHqIWyJd = false;}
      if(qVIdNKtMUL == true){qVIdNKtMUL = false;}
      if(PFVXtqWSqW == true){PFVXtqWSqW = false;}
      if(uMZULZCeAt == true){uMZULZCeAt = false;}
      if(jRQmUnCULg == true){jRQmUnCULg = false;}
      if(WSaqmjKuMA == true){WSaqmjKuMA = false;}
      if(lEHmidumRn == true){lEHmidumRn = false;}
      if(IOLaaxniDG == true){IOLaaxniDG = false;}
      if(nCHKzcligb == true){nCHKzcligb = false;}
      if(PGRAIfJdEp == true){PGRAIfJdEp = false;}
      if(sPCWYHGAQo == true){sPCWYHGAQo = false;}
      if(ubqFLiwxmF == true){ubqFLiwxmF = false;}
      if(qMGpXBwKRt == true){qMGpXBwKRt = false;}
      if(nKdMNYzjlr == true){nKdMNYzjlr = false;}
      if(VlRqfnOLnY == true){VlRqfnOLnY = false;}
      if(jLpyzfJLzX == true){jLpyzfJLzX = false;}
      if(KuhVBkxerm == true){KuhVBkxerm = false;}
      if(iMLujFtOKj == true){iMLujFtOKj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBCITRYQWU
{ 
  void CSFwsdxCRx()
  { 
      bool wEmhSuIwzN = false;
      bool iaWHkNdutR = false;
      bool AATeBPQHDq = false;
      bool TqPeTEqCDZ = false;
      bool TgalLedVix = false;
      bool GpKjXujIgD = false;
      bool dArHsqLrng = false;
      bool VbqUyTZhSW = false;
      bool ktXGkdgfGX = false;
      bool UiVAuSnSrT = false;
      bool SlhCadyokE = false;
      bool VCoKRjckWP = false;
      bool KekPMmFqYe = false;
      bool eHozDzLVfG = false;
      bool eqtCCRsLhL = false;
      bool pDwcImASpm = false;
      bool YGQGYNNpGR = false;
      bool XHFPjTkhMt = false;
      bool ttJNobLMpP = false;
      bool yserhXamdn = false;
      string cCjxgHcrYG;
      string AhUbWodSzx;
      string CuUBdYKQKV;
      string rVUDChwcAV;
      string zKeQFJVEBU;
      string jFyYzhgiSH;
      string wLhCNeNQZo;
      string sBRdyqPEuU;
      string CFOpllWwET;
      string AMJsYmcbCa;
      string wFeMaimUaI;
      string RcnyEpxqQa;
      string HQMFngqYEK;
      string NnBTYxaCOC;
      string zBUuCXXLnh;
      string pkKbTerZXt;
      string rOQPtdaTYG;
      string PtcObFwQDQ;
      string IejVUbcZAt;
      string FAdUKjkEBX;
      if(cCjxgHcrYG == wFeMaimUaI){wEmhSuIwzN = true;}
      else if(wFeMaimUaI == cCjxgHcrYG){SlhCadyokE = true;}
      if(AhUbWodSzx == RcnyEpxqQa){iaWHkNdutR = true;}
      else if(RcnyEpxqQa == AhUbWodSzx){VCoKRjckWP = true;}
      if(CuUBdYKQKV == HQMFngqYEK){AATeBPQHDq = true;}
      else if(HQMFngqYEK == CuUBdYKQKV){KekPMmFqYe = true;}
      if(rVUDChwcAV == NnBTYxaCOC){TqPeTEqCDZ = true;}
      else if(NnBTYxaCOC == rVUDChwcAV){eHozDzLVfG = true;}
      if(zKeQFJVEBU == zBUuCXXLnh){TgalLedVix = true;}
      else if(zBUuCXXLnh == zKeQFJVEBU){eqtCCRsLhL = true;}
      if(jFyYzhgiSH == pkKbTerZXt){GpKjXujIgD = true;}
      else if(pkKbTerZXt == jFyYzhgiSH){pDwcImASpm = true;}
      if(wLhCNeNQZo == rOQPtdaTYG){dArHsqLrng = true;}
      else if(rOQPtdaTYG == wLhCNeNQZo){YGQGYNNpGR = true;}
      if(sBRdyqPEuU == PtcObFwQDQ){VbqUyTZhSW = true;}
      if(CFOpllWwET == IejVUbcZAt){ktXGkdgfGX = true;}
      if(AMJsYmcbCa == FAdUKjkEBX){UiVAuSnSrT = true;}
      while(PtcObFwQDQ == sBRdyqPEuU){XHFPjTkhMt = true;}
      while(IejVUbcZAt == IejVUbcZAt){ttJNobLMpP = true;}
      while(FAdUKjkEBX == FAdUKjkEBX){yserhXamdn = true;}
      if(wEmhSuIwzN == true){wEmhSuIwzN = false;}
      if(iaWHkNdutR == true){iaWHkNdutR = false;}
      if(AATeBPQHDq == true){AATeBPQHDq = false;}
      if(TqPeTEqCDZ == true){TqPeTEqCDZ = false;}
      if(TgalLedVix == true){TgalLedVix = false;}
      if(GpKjXujIgD == true){GpKjXujIgD = false;}
      if(dArHsqLrng == true){dArHsqLrng = false;}
      if(VbqUyTZhSW == true){VbqUyTZhSW = false;}
      if(ktXGkdgfGX == true){ktXGkdgfGX = false;}
      if(UiVAuSnSrT == true){UiVAuSnSrT = false;}
      if(SlhCadyokE == true){SlhCadyokE = false;}
      if(VCoKRjckWP == true){VCoKRjckWP = false;}
      if(KekPMmFqYe == true){KekPMmFqYe = false;}
      if(eHozDzLVfG == true){eHozDzLVfG = false;}
      if(eqtCCRsLhL == true){eqtCCRsLhL = false;}
      if(pDwcImASpm == true){pDwcImASpm = false;}
      if(YGQGYNNpGR == true){YGQGYNNpGR = false;}
      if(XHFPjTkhMt == true){XHFPjTkhMt = false;}
      if(ttJNobLMpP == true){ttJNobLMpP = false;}
      if(yserhXamdn == true){yserhXamdn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZDSMJFZJHX
{ 
  void dKntiCaCTA()
  { 
      bool WJgHGRRaLH = false;
      bool GOrdjBjFlM = false;
      bool FjxyBxIZZP = false;
      bool OxFTrSPLum = false;
      bool WTGepeonUT = false;
      bool qxDgBlMiGJ = false;
      bool IqAurIJXlR = false;
      bool kXJzoldSIV = false;
      bool HUFFXRtXSF = false;
      bool GgFldfSKlg = false;
      bool UQCDiTmErP = false;
      bool IsZjCnluXa = false;
      bool OkEfKDSXUI = false;
      bool STfaBpRCWE = false;
      bool dpfDxMGUjo = false;
      bool tWlLSjMWre = false;
      bool APiiwoNziL = false;
      bool WiYSwXFBhx = false;
      bool wxnfOwgTIR = false;
      bool duJqEOGxGI = false;
      string WWPsYlzONq;
      string uffxCWnJAy;
      string iBCCEDGOJE;
      string MKqDrQFBdw;
      string RAwFnBkFTD;
      string LGBVUUUMnV;
      string fjEJdkocEk;
      string QmeEfhEwOC;
      string RBuFsGIVhW;
      string wrMHPhwmaC;
      string MIAhlYaxom;
      string QXxkEenyQX;
      string cStgnYZWny;
      string lQVMpIAMTU;
      string fLfuGYubDk;
      string sxWDYsOStN;
      string yDIqBzCktu;
      string dbeuqRmzaP;
      string cxTCEotRmw;
      string tgSFVbCosG;
      if(WWPsYlzONq == MIAhlYaxom){WJgHGRRaLH = true;}
      else if(MIAhlYaxom == WWPsYlzONq){UQCDiTmErP = true;}
      if(uffxCWnJAy == QXxkEenyQX){GOrdjBjFlM = true;}
      else if(QXxkEenyQX == uffxCWnJAy){IsZjCnluXa = true;}
      if(iBCCEDGOJE == cStgnYZWny){FjxyBxIZZP = true;}
      else if(cStgnYZWny == iBCCEDGOJE){OkEfKDSXUI = true;}
      if(MKqDrQFBdw == lQVMpIAMTU){OxFTrSPLum = true;}
      else if(lQVMpIAMTU == MKqDrQFBdw){STfaBpRCWE = true;}
      if(RAwFnBkFTD == fLfuGYubDk){WTGepeonUT = true;}
      else if(fLfuGYubDk == RAwFnBkFTD){dpfDxMGUjo = true;}
      if(LGBVUUUMnV == sxWDYsOStN){qxDgBlMiGJ = true;}
      else if(sxWDYsOStN == LGBVUUUMnV){tWlLSjMWre = true;}
      if(fjEJdkocEk == yDIqBzCktu){IqAurIJXlR = true;}
      else if(yDIqBzCktu == fjEJdkocEk){APiiwoNziL = true;}
      if(QmeEfhEwOC == dbeuqRmzaP){kXJzoldSIV = true;}
      if(RBuFsGIVhW == cxTCEotRmw){HUFFXRtXSF = true;}
      if(wrMHPhwmaC == tgSFVbCosG){GgFldfSKlg = true;}
      while(dbeuqRmzaP == QmeEfhEwOC){WiYSwXFBhx = true;}
      while(cxTCEotRmw == cxTCEotRmw){wxnfOwgTIR = true;}
      while(tgSFVbCosG == tgSFVbCosG){duJqEOGxGI = true;}
      if(WJgHGRRaLH == true){WJgHGRRaLH = false;}
      if(GOrdjBjFlM == true){GOrdjBjFlM = false;}
      if(FjxyBxIZZP == true){FjxyBxIZZP = false;}
      if(OxFTrSPLum == true){OxFTrSPLum = false;}
      if(WTGepeonUT == true){WTGepeonUT = false;}
      if(qxDgBlMiGJ == true){qxDgBlMiGJ = false;}
      if(IqAurIJXlR == true){IqAurIJXlR = false;}
      if(kXJzoldSIV == true){kXJzoldSIV = false;}
      if(HUFFXRtXSF == true){HUFFXRtXSF = false;}
      if(GgFldfSKlg == true){GgFldfSKlg = false;}
      if(UQCDiTmErP == true){UQCDiTmErP = false;}
      if(IsZjCnluXa == true){IsZjCnluXa = false;}
      if(OkEfKDSXUI == true){OkEfKDSXUI = false;}
      if(STfaBpRCWE == true){STfaBpRCWE = false;}
      if(dpfDxMGUjo == true){dpfDxMGUjo = false;}
      if(tWlLSjMWre == true){tWlLSjMWre = false;}
      if(APiiwoNziL == true){APiiwoNziL = false;}
      if(WiYSwXFBhx == true){WiYSwXFBhx = false;}
      if(wxnfOwgTIR == true){wxnfOwgTIR = false;}
      if(duJqEOGxGI == true){duJqEOGxGI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SNUKRTLRTQ
{ 
  void WbJojfnseu()
  { 
      bool zdStQruEdc = false;
      bool MSLBWBzfOI = false;
      bool VNrquqQjjA = false;
      bool gsNcrAqooE = false;
      bool oNJutXazyz = false;
      bool MayYXklbzZ = false;
      bool bLTdwTEhJV = false;
      bool JJqKSIDxwW = false;
      bool PQkjmFtoFG = false;
      bool OPpPcdsfyZ = false;
      bool TrpcoDjnFP = false;
      bool hnebJKZipp = false;
      bool ZPcCGtSago = false;
      bool OXyWDXaIui = false;
      bool VFipYZjNGS = false;
      bool DKoIADOmVu = false;
      bool kIHQAKpIYl = false;
      bool jQnGUTgmdf = false;
      bool KEUNkEhpWA = false;
      bool ImmAyMySpO = false;
      string dsAJtBfWNp;
      string kemDPUKwJy;
      string SmhFILmnxK;
      string kTAGTquqHL;
      string QCqDQfTZIA;
      string HolDxqKuBi;
      string OrYCEQegiX;
      string ZSoygPwdob;
      string qMexDwhxJc;
      string gApXwXcozz;
      string BlpjaoAnVg;
      string ufFYqBMbzI;
      string hhXGqYbQBI;
      string lGeoaFWtWN;
      string utabhAtQgu;
      string LBoqRTOjsB;
      string MilMtnBQyl;
      string dSFkMnGuXq;
      string eKjGxkRnXH;
      string pmBUBMHNht;
      if(dsAJtBfWNp == BlpjaoAnVg){zdStQruEdc = true;}
      else if(BlpjaoAnVg == dsAJtBfWNp){TrpcoDjnFP = true;}
      if(kemDPUKwJy == ufFYqBMbzI){MSLBWBzfOI = true;}
      else if(ufFYqBMbzI == kemDPUKwJy){hnebJKZipp = true;}
      if(SmhFILmnxK == hhXGqYbQBI){VNrquqQjjA = true;}
      else if(hhXGqYbQBI == SmhFILmnxK){ZPcCGtSago = true;}
      if(kTAGTquqHL == lGeoaFWtWN){gsNcrAqooE = true;}
      else if(lGeoaFWtWN == kTAGTquqHL){OXyWDXaIui = true;}
      if(QCqDQfTZIA == utabhAtQgu){oNJutXazyz = true;}
      else if(utabhAtQgu == QCqDQfTZIA){VFipYZjNGS = true;}
      if(HolDxqKuBi == LBoqRTOjsB){MayYXklbzZ = true;}
      else if(LBoqRTOjsB == HolDxqKuBi){DKoIADOmVu = true;}
      if(OrYCEQegiX == MilMtnBQyl){bLTdwTEhJV = true;}
      else if(MilMtnBQyl == OrYCEQegiX){kIHQAKpIYl = true;}
      if(ZSoygPwdob == dSFkMnGuXq){JJqKSIDxwW = true;}
      if(qMexDwhxJc == eKjGxkRnXH){PQkjmFtoFG = true;}
      if(gApXwXcozz == pmBUBMHNht){OPpPcdsfyZ = true;}
      while(dSFkMnGuXq == ZSoygPwdob){jQnGUTgmdf = true;}
      while(eKjGxkRnXH == eKjGxkRnXH){KEUNkEhpWA = true;}
      while(pmBUBMHNht == pmBUBMHNht){ImmAyMySpO = true;}
      if(zdStQruEdc == true){zdStQruEdc = false;}
      if(MSLBWBzfOI == true){MSLBWBzfOI = false;}
      if(VNrquqQjjA == true){VNrquqQjjA = false;}
      if(gsNcrAqooE == true){gsNcrAqooE = false;}
      if(oNJutXazyz == true){oNJutXazyz = false;}
      if(MayYXklbzZ == true){MayYXklbzZ = false;}
      if(bLTdwTEhJV == true){bLTdwTEhJV = false;}
      if(JJqKSIDxwW == true){JJqKSIDxwW = false;}
      if(PQkjmFtoFG == true){PQkjmFtoFG = false;}
      if(OPpPcdsfyZ == true){OPpPcdsfyZ = false;}
      if(TrpcoDjnFP == true){TrpcoDjnFP = false;}
      if(hnebJKZipp == true){hnebJKZipp = false;}
      if(ZPcCGtSago == true){ZPcCGtSago = false;}
      if(OXyWDXaIui == true){OXyWDXaIui = false;}
      if(VFipYZjNGS == true){VFipYZjNGS = false;}
      if(DKoIADOmVu == true){DKoIADOmVu = false;}
      if(kIHQAKpIYl == true){kIHQAKpIYl = false;}
      if(jQnGUTgmdf == true){jQnGUTgmdf = false;}
      if(KEUNkEhpWA == true){KEUNkEhpWA = false;}
      if(ImmAyMySpO == true){ImmAyMySpO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DWNFQXDTEB
{ 
  void nKqmkQDJCg()
  { 
      bool IIZUoeMBYI = false;
      bool jYrItFhspA = false;
      bool NeLSTUtNdc = false;
      bool cZFnWAwBFa = false;
      bool YaLdxAmbcl = false;
      bool mzBYRdxHAT = false;
      bool kzXufKTDkt = false;
      bool JfnPbmTgUT = false;
      bool hSjqocYfVs = false;
      bool CnAkoYCPxm = false;
      bool fiqicGLlxe = false;
      bool JPmglSPfFC = false;
      bool kmhqqVeDZC = false;
      bool jDjgnzbAOi = false;
      bool RmiqilATyW = false;
      bool JWJtCrAzrG = false;
      bool aILutGfGrm = false;
      bool qPQWkyEpHE = false;
      bool VKECsNsoeu = false;
      bool ybIIHJanxc = false;
      string bsFYqqeFMB;
      string AwZaMZoAkL;
      string HSYpAuDJAa;
      string SrqzWOmhfT;
      string hOBZpLWHrG;
      string gHmpPITPXu;
      string mUFlhHFaEy;
      string mHTQcsQyAo;
      string YuRstLEAiN;
      string tWJjgMJPrh;
      string FuDsSZmWMW;
      string qVPiWrDLqV;
      string DEqpEPxiiQ;
      string jBGRicrYaU;
      string YgnMVXGaNo;
      string JxYVeAEMnD;
      string bDnwmpPyAs;
      string zdkWxVQeTf;
      string IWVtGlcjmh;
      string YejXrUsqZf;
      if(bsFYqqeFMB == FuDsSZmWMW){IIZUoeMBYI = true;}
      else if(FuDsSZmWMW == bsFYqqeFMB){fiqicGLlxe = true;}
      if(AwZaMZoAkL == qVPiWrDLqV){jYrItFhspA = true;}
      else if(qVPiWrDLqV == AwZaMZoAkL){JPmglSPfFC = true;}
      if(HSYpAuDJAa == DEqpEPxiiQ){NeLSTUtNdc = true;}
      else if(DEqpEPxiiQ == HSYpAuDJAa){kmhqqVeDZC = true;}
      if(SrqzWOmhfT == jBGRicrYaU){cZFnWAwBFa = true;}
      else if(jBGRicrYaU == SrqzWOmhfT){jDjgnzbAOi = true;}
      if(hOBZpLWHrG == YgnMVXGaNo){YaLdxAmbcl = true;}
      else if(YgnMVXGaNo == hOBZpLWHrG){RmiqilATyW = true;}
      if(gHmpPITPXu == JxYVeAEMnD){mzBYRdxHAT = true;}
      else if(JxYVeAEMnD == gHmpPITPXu){JWJtCrAzrG = true;}
      if(mUFlhHFaEy == bDnwmpPyAs){kzXufKTDkt = true;}
      else if(bDnwmpPyAs == mUFlhHFaEy){aILutGfGrm = true;}
      if(mHTQcsQyAo == zdkWxVQeTf){JfnPbmTgUT = true;}
      if(YuRstLEAiN == IWVtGlcjmh){hSjqocYfVs = true;}
      if(tWJjgMJPrh == YejXrUsqZf){CnAkoYCPxm = true;}
      while(zdkWxVQeTf == mHTQcsQyAo){qPQWkyEpHE = true;}
      while(IWVtGlcjmh == IWVtGlcjmh){VKECsNsoeu = true;}
      while(YejXrUsqZf == YejXrUsqZf){ybIIHJanxc = true;}
      if(IIZUoeMBYI == true){IIZUoeMBYI = false;}
      if(jYrItFhspA == true){jYrItFhspA = false;}
      if(NeLSTUtNdc == true){NeLSTUtNdc = false;}
      if(cZFnWAwBFa == true){cZFnWAwBFa = false;}
      if(YaLdxAmbcl == true){YaLdxAmbcl = false;}
      if(mzBYRdxHAT == true){mzBYRdxHAT = false;}
      if(kzXufKTDkt == true){kzXufKTDkt = false;}
      if(JfnPbmTgUT == true){JfnPbmTgUT = false;}
      if(hSjqocYfVs == true){hSjqocYfVs = false;}
      if(CnAkoYCPxm == true){CnAkoYCPxm = false;}
      if(fiqicGLlxe == true){fiqicGLlxe = false;}
      if(JPmglSPfFC == true){JPmglSPfFC = false;}
      if(kmhqqVeDZC == true){kmhqqVeDZC = false;}
      if(jDjgnzbAOi == true){jDjgnzbAOi = false;}
      if(RmiqilATyW == true){RmiqilATyW = false;}
      if(JWJtCrAzrG == true){JWJtCrAzrG = false;}
      if(aILutGfGrm == true){aILutGfGrm = false;}
      if(qPQWkyEpHE == true){qPQWkyEpHE = false;}
      if(VKECsNsoeu == true){VKECsNsoeu = false;}
      if(ybIIHJanxc == true){ybIIHJanxc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MTUEXOIHZR
{ 
  void WFLoHrRmmz()
  { 
      bool MidJwKfjtS = false;
      bool KdsBExhzmH = false;
      bool jASojOdhAW = false;
      bool thGODNDFRP = false;
      bool fGxSkrIpkh = false;
      bool OpyYiLPoYh = false;
      bool fyiXYbWeyq = false;
      bool schXbcDADr = false;
      bool GnwRHDjgfq = false;
      bool xOfiigWYsJ = false;
      bool UcqtolHaxF = false;
      bool IPkgbrCRPU = false;
      bool qpzHsewyot = false;
      bool FdGtXcwBcU = false;
      bool uJiZihczHp = false;
      bool dFIXRddjBJ = false;
      bool oJkCzdIqJy = false;
      bool uAnuZhHYYL = false;
      bool BxqyPAUibs = false;
      bool zMATelXfaE = false;
      string uMSkzEgaII;
      string pncbAUdaJG;
      string zxkwDQhFgh;
      string cMEGZdDHob;
      string nNhFSgaDJD;
      string xKUlVxbWhh;
      string WbsaedjWCW;
      string RVkgSkOecW;
      string pdwdkSqRjb;
      string BgZHFLUHZo;
      string wDBllaZnTj;
      string hxsKrrePpM;
      string lRmaUjwcaG;
      string QHEnZlbJqJ;
      string sCyAsEnOOM;
      string gEQNCdQaRB;
      string dwNMTarEkF;
      string PVXfTiTmgP;
      string wgONZLqqlu;
      string VBqpfwokfS;
      if(uMSkzEgaII == wDBllaZnTj){MidJwKfjtS = true;}
      else if(wDBllaZnTj == uMSkzEgaII){UcqtolHaxF = true;}
      if(pncbAUdaJG == hxsKrrePpM){KdsBExhzmH = true;}
      else if(hxsKrrePpM == pncbAUdaJG){IPkgbrCRPU = true;}
      if(zxkwDQhFgh == lRmaUjwcaG){jASojOdhAW = true;}
      else if(lRmaUjwcaG == zxkwDQhFgh){qpzHsewyot = true;}
      if(cMEGZdDHob == QHEnZlbJqJ){thGODNDFRP = true;}
      else if(QHEnZlbJqJ == cMEGZdDHob){FdGtXcwBcU = true;}
      if(nNhFSgaDJD == sCyAsEnOOM){fGxSkrIpkh = true;}
      else if(sCyAsEnOOM == nNhFSgaDJD){uJiZihczHp = true;}
      if(xKUlVxbWhh == gEQNCdQaRB){OpyYiLPoYh = true;}
      else if(gEQNCdQaRB == xKUlVxbWhh){dFIXRddjBJ = true;}
      if(WbsaedjWCW == dwNMTarEkF){fyiXYbWeyq = true;}
      else if(dwNMTarEkF == WbsaedjWCW){oJkCzdIqJy = true;}
      if(RVkgSkOecW == PVXfTiTmgP){schXbcDADr = true;}
      if(pdwdkSqRjb == wgONZLqqlu){GnwRHDjgfq = true;}
      if(BgZHFLUHZo == VBqpfwokfS){xOfiigWYsJ = true;}
      while(PVXfTiTmgP == RVkgSkOecW){uAnuZhHYYL = true;}
      while(wgONZLqqlu == wgONZLqqlu){BxqyPAUibs = true;}
      while(VBqpfwokfS == VBqpfwokfS){zMATelXfaE = true;}
      if(MidJwKfjtS == true){MidJwKfjtS = false;}
      if(KdsBExhzmH == true){KdsBExhzmH = false;}
      if(jASojOdhAW == true){jASojOdhAW = false;}
      if(thGODNDFRP == true){thGODNDFRP = false;}
      if(fGxSkrIpkh == true){fGxSkrIpkh = false;}
      if(OpyYiLPoYh == true){OpyYiLPoYh = false;}
      if(fyiXYbWeyq == true){fyiXYbWeyq = false;}
      if(schXbcDADr == true){schXbcDADr = false;}
      if(GnwRHDjgfq == true){GnwRHDjgfq = false;}
      if(xOfiigWYsJ == true){xOfiigWYsJ = false;}
      if(UcqtolHaxF == true){UcqtolHaxF = false;}
      if(IPkgbrCRPU == true){IPkgbrCRPU = false;}
      if(qpzHsewyot == true){qpzHsewyot = false;}
      if(FdGtXcwBcU == true){FdGtXcwBcU = false;}
      if(uJiZihczHp == true){uJiZihczHp = false;}
      if(dFIXRddjBJ == true){dFIXRddjBJ = false;}
      if(oJkCzdIqJy == true){oJkCzdIqJy = false;}
      if(uAnuZhHYYL == true){uAnuZhHYYL = false;}
      if(BxqyPAUibs == true){BxqyPAUibs = false;}
      if(zMATelXfaE == true){zMATelXfaE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UXBDRJDOLL
{ 
  void CKYkoxGogT()
  { 
      bool ePVpLsAxtV = false;
      bool iCZbiLDkJc = false;
      bool psBfIgIuDL = false;
      bool UgThMaXQAB = false;
      bool izRzArkAkO = false;
      bool cetXjlNohe = false;
      bool kFthBBhqOI = false;
      bool mljIsqaBfP = false;
      bool uIJniomuxa = false;
      bool MhhVQdEiyy = false;
      bool Jskcbptkes = false;
      bool KMJRibuFzL = false;
      bool OlsnuFENrP = false;
      bool lqCgFCWfMr = false;
      bool tBQEPzXPmn = false;
      bool hzimjXzxgV = false;
      bool lgsOGSKcMf = false;
      bool EPsHQMVoXu = false;
      bool gnaDhmHPwh = false;
      bool DZzpGNICyw = false;
      string hgjpbbWVJG;
      string LkTiPaXTUX;
      string KQPGHjtyNk;
      string YnEMoDNmFT;
      string kiIAbrMxHP;
      string UYNRmRRdhq;
      string gXIYhXfHsM;
      string MjNBmaHPeP;
      string WxqxPAZmYX;
      string kjENlMajSD;
      string MFEtCjKMeL;
      string KBySUjgKIg;
      string xshVaceAOZ;
      string zXxaDRrwte;
      string pNIMNjllsC;
      string eQakFTWhTZ;
      string EKxELmEWPC;
      string qkPdqjjUIq;
      string psGMuiwLVi;
      string tKbUZfPDAa;
      if(hgjpbbWVJG == MFEtCjKMeL){ePVpLsAxtV = true;}
      else if(MFEtCjKMeL == hgjpbbWVJG){Jskcbptkes = true;}
      if(LkTiPaXTUX == KBySUjgKIg){iCZbiLDkJc = true;}
      else if(KBySUjgKIg == LkTiPaXTUX){KMJRibuFzL = true;}
      if(KQPGHjtyNk == xshVaceAOZ){psBfIgIuDL = true;}
      else if(xshVaceAOZ == KQPGHjtyNk){OlsnuFENrP = true;}
      if(YnEMoDNmFT == zXxaDRrwte){UgThMaXQAB = true;}
      else if(zXxaDRrwte == YnEMoDNmFT){lqCgFCWfMr = true;}
      if(kiIAbrMxHP == pNIMNjllsC){izRzArkAkO = true;}
      else if(pNIMNjllsC == kiIAbrMxHP){tBQEPzXPmn = true;}
      if(UYNRmRRdhq == eQakFTWhTZ){cetXjlNohe = true;}
      else if(eQakFTWhTZ == UYNRmRRdhq){hzimjXzxgV = true;}
      if(gXIYhXfHsM == EKxELmEWPC){kFthBBhqOI = true;}
      else if(EKxELmEWPC == gXIYhXfHsM){lgsOGSKcMf = true;}
      if(MjNBmaHPeP == qkPdqjjUIq){mljIsqaBfP = true;}
      if(WxqxPAZmYX == psGMuiwLVi){uIJniomuxa = true;}
      if(kjENlMajSD == tKbUZfPDAa){MhhVQdEiyy = true;}
      while(qkPdqjjUIq == MjNBmaHPeP){EPsHQMVoXu = true;}
      while(psGMuiwLVi == psGMuiwLVi){gnaDhmHPwh = true;}
      while(tKbUZfPDAa == tKbUZfPDAa){DZzpGNICyw = true;}
      if(ePVpLsAxtV == true){ePVpLsAxtV = false;}
      if(iCZbiLDkJc == true){iCZbiLDkJc = false;}
      if(psBfIgIuDL == true){psBfIgIuDL = false;}
      if(UgThMaXQAB == true){UgThMaXQAB = false;}
      if(izRzArkAkO == true){izRzArkAkO = false;}
      if(cetXjlNohe == true){cetXjlNohe = false;}
      if(kFthBBhqOI == true){kFthBBhqOI = false;}
      if(mljIsqaBfP == true){mljIsqaBfP = false;}
      if(uIJniomuxa == true){uIJniomuxa = false;}
      if(MhhVQdEiyy == true){MhhVQdEiyy = false;}
      if(Jskcbptkes == true){Jskcbptkes = false;}
      if(KMJRibuFzL == true){KMJRibuFzL = false;}
      if(OlsnuFENrP == true){OlsnuFENrP = false;}
      if(lqCgFCWfMr == true){lqCgFCWfMr = false;}
      if(tBQEPzXPmn == true){tBQEPzXPmn = false;}
      if(hzimjXzxgV == true){hzimjXzxgV = false;}
      if(lgsOGSKcMf == true){lgsOGSKcMf = false;}
      if(EPsHQMVoXu == true){EPsHQMVoXu = false;}
      if(gnaDhmHPwh == true){gnaDhmHPwh = false;}
      if(DZzpGNICyw == true){DZzpGNICyw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QRWBEWDWEY
{ 
  void EtOnLrxVYi()
  { 
      bool ptBqactVae = false;
      bool RCnmDDaaDD = false;
      bool ofkLXylfDJ = false;
      bool LlITCUfHMz = false;
      bool DYVwjFkpYY = false;
      bool gtBLBKJpSb = false;
      bool qNSQTfsTjh = false;
      bool XSNDAQKnaS = false;
      bool MuHecRjxRr = false;
      bool LonkIoGFbD = false;
      bool LRFqBNfxLk = false;
      bool AUOAOuGnmC = false;
      bool wwBqWhecuK = false;
      bool JEMWGupQcO = false;
      bool klkgrpZnVN = false;
      bool iRRZHPPOTS = false;
      bool iDCAauIrtT = false;
      bool FpKYRKKUzf = false;
      bool HqGgbrllPq = false;
      bool fawJfgikFw = false;
      string sHNiuGdoAF;
      string YyufnzEEnj;
      string EUFxIfxzBO;
      string cVehhnWQzF;
      string wueWfHektR;
      string UzjoMXBQaO;
      string JemkcCTMxA;
      string cmFimIpiQA;
      string BMEjtckoVK;
      string lGpjwRHssc;
      string nRmtogtBCD;
      string hSzZNxZDqA;
      string QdqmNVxUlU;
      string BxomMiYKuM;
      string hjmRbTGPVy;
      string rDBsMJazgS;
      string jZOgCkcLNe;
      string XPIeSgqYLs;
      string PgyncyuwaC;
      string HZcbbIUFPq;
      if(sHNiuGdoAF == nRmtogtBCD){ptBqactVae = true;}
      else if(nRmtogtBCD == sHNiuGdoAF){LRFqBNfxLk = true;}
      if(YyufnzEEnj == hSzZNxZDqA){RCnmDDaaDD = true;}
      else if(hSzZNxZDqA == YyufnzEEnj){AUOAOuGnmC = true;}
      if(EUFxIfxzBO == QdqmNVxUlU){ofkLXylfDJ = true;}
      else if(QdqmNVxUlU == EUFxIfxzBO){wwBqWhecuK = true;}
      if(cVehhnWQzF == BxomMiYKuM){LlITCUfHMz = true;}
      else if(BxomMiYKuM == cVehhnWQzF){JEMWGupQcO = true;}
      if(wueWfHektR == hjmRbTGPVy){DYVwjFkpYY = true;}
      else if(hjmRbTGPVy == wueWfHektR){klkgrpZnVN = true;}
      if(UzjoMXBQaO == rDBsMJazgS){gtBLBKJpSb = true;}
      else if(rDBsMJazgS == UzjoMXBQaO){iRRZHPPOTS = true;}
      if(JemkcCTMxA == jZOgCkcLNe){qNSQTfsTjh = true;}
      else if(jZOgCkcLNe == JemkcCTMxA){iDCAauIrtT = true;}
      if(cmFimIpiQA == XPIeSgqYLs){XSNDAQKnaS = true;}
      if(BMEjtckoVK == PgyncyuwaC){MuHecRjxRr = true;}
      if(lGpjwRHssc == HZcbbIUFPq){LonkIoGFbD = true;}
      while(XPIeSgqYLs == cmFimIpiQA){FpKYRKKUzf = true;}
      while(PgyncyuwaC == PgyncyuwaC){HqGgbrllPq = true;}
      while(HZcbbIUFPq == HZcbbIUFPq){fawJfgikFw = true;}
      if(ptBqactVae == true){ptBqactVae = false;}
      if(RCnmDDaaDD == true){RCnmDDaaDD = false;}
      if(ofkLXylfDJ == true){ofkLXylfDJ = false;}
      if(LlITCUfHMz == true){LlITCUfHMz = false;}
      if(DYVwjFkpYY == true){DYVwjFkpYY = false;}
      if(gtBLBKJpSb == true){gtBLBKJpSb = false;}
      if(qNSQTfsTjh == true){qNSQTfsTjh = false;}
      if(XSNDAQKnaS == true){XSNDAQKnaS = false;}
      if(MuHecRjxRr == true){MuHecRjxRr = false;}
      if(LonkIoGFbD == true){LonkIoGFbD = false;}
      if(LRFqBNfxLk == true){LRFqBNfxLk = false;}
      if(AUOAOuGnmC == true){AUOAOuGnmC = false;}
      if(wwBqWhecuK == true){wwBqWhecuK = false;}
      if(JEMWGupQcO == true){JEMWGupQcO = false;}
      if(klkgrpZnVN == true){klkgrpZnVN = false;}
      if(iRRZHPPOTS == true){iRRZHPPOTS = false;}
      if(iDCAauIrtT == true){iDCAauIrtT = false;}
      if(FpKYRKKUzf == true){FpKYRKKUzf = false;}
      if(HqGgbrllPq == true){HqGgbrllPq = false;}
      if(fawJfgikFw == true){fawJfgikFw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QTKFZUJGUE
{ 
  void rFDWeZsweh()
  { 
      bool AFxJEdfREU = false;
      bool QXsSbZcgqo = false;
      bool MfIqERAoBQ = false;
      bool xCrJtGWwdy = false;
      bool ifntBnLWpF = false;
      bool jINKCTxGFl = false;
      bool cpQnXNejXU = false;
      bool CgDrFfrNpP = false;
      bool GczwfnnhGa = false;
      bool JQqqUrOAWn = false;
      bool JazUCDFVEV = false;
      bool biPofAqUHi = false;
      bool YxcxLlpLWN = false;
      bool QrqCGeddsb = false;
      bool iSckzZABLU = false;
      bool BtrnPLxBIQ = false;
      bool NsyqEirNhA = false;
      bool VMaezFTryl = false;
      bool knABMWzDmu = false;
      bool hbUcOoUlfP = false;
      string USRVESsoHS;
      string NouUAJkGoK;
      string TLixZTjLjD;
      string eoShpIsCFG;
      string xJJyYcbuYw;
      string FRIdTIjTwk;
      string igEEnYWMeq;
      string PhBhMJBjYw;
      string qnlnxNfoOg;
      string XYGTWPFFJA;
      string GOQgfWPaQJ;
      string HzuzsuuQGa;
      string rgyyTpbgKx;
      string EwaXpcXEHZ;
      string xFYFZYdGab;
      string UnyhIYQRNo;
      string uiPTFKYXIQ;
      string XqIfdmIrYt;
      string MUGibPyrPR;
      string LFpSeNoFAO;
      if(USRVESsoHS == GOQgfWPaQJ){AFxJEdfREU = true;}
      else if(GOQgfWPaQJ == USRVESsoHS){JazUCDFVEV = true;}
      if(NouUAJkGoK == HzuzsuuQGa){QXsSbZcgqo = true;}
      else if(HzuzsuuQGa == NouUAJkGoK){biPofAqUHi = true;}
      if(TLixZTjLjD == rgyyTpbgKx){MfIqERAoBQ = true;}
      else if(rgyyTpbgKx == TLixZTjLjD){YxcxLlpLWN = true;}
      if(eoShpIsCFG == EwaXpcXEHZ){xCrJtGWwdy = true;}
      else if(EwaXpcXEHZ == eoShpIsCFG){QrqCGeddsb = true;}
      if(xJJyYcbuYw == xFYFZYdGab){ifntBnLWpF = true;}
      else if(xFYFZYdGab == xJJyYcbuYw){iSckzZABLU = true;}
      if(FRIdTIjTwk == UnyhIYQRNo){jINKCTxGFl = true;}
      else if(UnyhIYQRNo == FRIdTIjTwk){BtrnPLxBIQ = true;}
      if(igEEnYWMeq == uiPTFKYXIQ){cpQnXNejXU = true;}
      else if(uiPTFKYXIQ == igEEnYWMeq){NsyqEirNhA = true;}
      if(PhBhMJBjYw == XqIfdmIrYt){CgDrFfrNpP = true;}
      if(qnlnxNfoOg == MUGibPyrPR){GczwfnnhGa = true;}
      if(XYGTWPFFJA == LFpSeNoFAO){JQqqUrOAWn = true;}
      while(XqIfdmIrYt == PhBhMJBjYw){VMaezFTryl = true;}
      while(MUGibPyrPR == MUGibPyrPR){knABMWzDmu = true;}
      while(LFpSeNoFAO == LFpSeNoFAO){hbUcOoUlfP = true;}
      if(AFxJEdfREU == true){AFxJEdfREU = false;}
      if(QXsSbZcgqo == true){QXsSbZcgqo = false;}
      if(MfIqERAoBQ == true){MfIqERAoBQ = false;}
      if(xCrJtGWwdy == true){xCrJtGWwdy = false;}
      if(ifntBnLWpF == true){ifntBnLWpF = false;}
      if(jINKCTxGFl == true){jINKCTxGFl = false;}
      if(cpQnXNejXU == true){cpQnXNejXU = false;}
      if(CgDrFfrNpP == true){CgDrFfrNpP = false;}
      if(GczwfnnhGa == true){GczwfnnhGa = false;}
      if(JQqqUrOAWn == true){JQqqUrOAWn = false;}
      if(JazUCDFVEV == true){JazUCDFVEV = false;}
      if(biPofAqUHi == true){biPofAqUHi = false;}
      if(YxcxLlpLWN == true){YxcxLlpLWN = false;}
      if(QrqCGeddsb == true){QrqCGeddsb = false;}
      if(iSckzZABLU == true){iSckzZABLU = false;}
      if(BtrnPLxBIQ == true){BtrnPLxBIQ = false;}
      if(NsyqEirNhA == true){NsyqEirNhA = false;}
      if(VMaezFTryl == true){VMaezFTryl = false;}
      if(knABMWzDmu == true){knABMWzDmu = false;}
      if(hbUcOoUlfP == true){hbUcOoUlfP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HUYEXAFWJF
{ 
  void dhfHOEzNqh()
  { 
      bool wuYTmDIaCT = false;
      bool nKGQGKtHbR = false;
      bool KlcKYykFBm = false;
      bool atYHYLLyAw = false;
      bool WKYqbSeMsu = false;
      bool XIMLrJSNuo = false;
      bool RCYPrtlzrt = false;
      bool yuHfuzMkiF = false;
      bool TYLGOShMOO = false;
      bool sxDLdTkJzh = false;
      bool ffUywbBfQr = false;
      bool wgepVspSBY = false;
      bool MYjcBAruBa = false;
      bool ODkAYmDNJl = false;
      bool RBwWRLSNpk = false;
      bool cSHZVGuqxw = false;
      bool jFdodswdQh = false;
      bool ocIOHKcNLo = false;
      bool heFQxuwKeS = false;
      bool qMPNCMWHrY = false;
      string JZVCuiClxL;
      string ZSWEgakuzU;
      string iluYgTUqEJ;
      string pBNcjpqkpa;
      string HMcPmYlsJn;
      string eHgFLXewVb;
      string OLhmUYFtUq;
      string jzEXNWIelH;
      string hagPeiUHQM;
      string KtOOLweptO;
      string TqYRDeCIro;
      string OzKOsmdRHl;
      string DxdHfpjoMR;
      string rSkWmqCOMA;
      string fLPaxLiAVX;
      string RMhILWNQlM;
      string tNwaxuOnbB;
      string jOEHFqhCJU;
      string GjSnzekbLQ;
      string clczFSPndC;
      if(JZVCuiClxL == TqYRDeCIro){wuYTmDIaCT = true;}
      else if(TqYRDeCIro == JZVCuiClxL){ffUywbBfQr = true;}
      if(ZSWEgakuzU == OzKOsmdRHl){nKGQGKtHbR = true;}
      else if(OzKOsmdRHl == ZSWEgakuzU){wgepVspSBY = true;}
      if(iluYgTUqEJ == DxdHfpjoMR){KlcKYykFBm = true;}
      else if(DxdHfpjoMR == iluYgTUqEJ){MYjcBAruBa = true;}
      if(pBNcjpqkpa == rSkWmqCOMA){atYHYLLyAw = true;}
      else if(rSkWmqCOMA == pBNcjpqkpa){ODkAYmDNJl = true;}
      if(HMcPmYlsJn == fLPaxLiAVX){WKYqbSeMsu = true;}
      else if(fLPaxLiAVX == HMcPmYlsJn){RBwWRLSNpk = true;}
      if(eHgFLXewVb == RMhILWNQlM){XIMLrJSNuo = true;}
      else if(RMhILWNQlM == eHgFLXewVb){cSHZVGuqxw = true;}
      if(OLhmUYFtUq == tNwaxuOnbB){RCYPrtlzrt = true;}
      else if(tNwaxuOnbB == OLhmUYFtUq){jFdodswdQh = true;}
      if(jzEXNWIelH == jOEHFqhCJU){yuHfuzMkiF = true;}
      if(hagPeiUHQM == GjSnzekbLQ){TYLGOShMOO = true;}
      if(KtOOLweptO == clczFSPndC){sxDLdTkJzh = true;}
      while(jOEHFqhCJU == jzEXNWIelH){ocIOHKcNLo = true;}
      while(GjSnzekbLQ == GjSnzekbLQ){heFQxuwKeS = true;}
      while(clczFSPndC == clczFSPndC){qMPNCMWHrY = true;}
      if(wuYTmDIaCT == true){wuYTmDIaCT = false;}
      if(nKGQGKtHbR == true){nKGQGKtHbR = false;}
      if(KlcKYykFBm == true){KlcKYykFBm = false;}
      if(atYHYLLyAw == true){atYHYLLyAw = false;}
      if(WKYqbSeMsu == true){WKYqbSeMsu = false;}
      if(XIMLrJSNuo == true){XIMLrJSNuo = false;}
      if(RCYPrtlzrt == true){RCYPrtlzrt = false;}
      if(yuHfuzMkiF == true){yuHfuzMkiF = false;}
      if(TYLGOShMOO == true){TYLGOShMOO = false;}
      if(sxDLdTkJzh == true){sxDLdTkJzh = false;}
      if(ffUywbBfQr == true){ffUywbBfQr = false;}
      if(wgepVspSBY == true){wgepVspSBY = false;}
      if(MYjcBAruBa == true){MYjcBAruBa = false;}
      if(ODkAYmDNJl == true){ODkAYmDNJl = false;}
      if(RBwWRLSNpk == true){RBwWRLSNpk = false;}
      if(cSHZVGuqxw == true){cSHZVGuqxw = false;}
      if(jFdodswdQh == true){jFdodswdQh = false;}
      if(ocIOHKcNLo == true){ocIOHKcNLo = false;}
      if(heFQxuwKeS == true){heFQxuwKeS = false;}
      if(qMPNCMWHrY == true){qMPNCMWHrY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QLVUTVEPAH
{ 
  void fCHWgWlhbR()
  { 
      bool aJyUuJfItg = false;
      bool tUScwXQUKB = false;
      bool FmyZPHFZwk = false;
      bool wCdrBuuVEF = false;
      bool jeFPrZlAAn = false;
      bool ZDpTomLYFn = false;
      bool DGLJkrpaaB = false;
      bool buPFQZghgo = false;
      bool VFYIKsMKCN = false;
      bool iWQQCdSwdz = false;
      bool jLZzLemjDP = false;
      bool FcqPSygDyr = false;
      bool ffXMREdzDl = false;
      bool GkDhFKfZwf = false;
      bool GbHmHGeByE = false;
      bool xPxlTEmMhG = false;
      bool AmgQIUYJJI = false;
      bool RGGRlDXkEK = false;
      bool ZcBzopmROB = false;
      bool WSrpfSupdm = false;
      string EtbfZpmFYp;
      string WxMEHSZXVh;
      string ryTRYhfmbk;
      string kkLCrwJNwl;
      string MAqBCNPqHT;
      string jGNDdFZJHr;
      string JzcnFllKML;
      string JLbjUqHRPK;
      string SnfIBdXIYl;
      string VzGEbMXDwQ;
      string aEewKXechl;
      string yItwYUTUla;
      string OdkZpJFWHH;
      string TEVzjNJjxd;
      string ztalnNEKfH;
      string sDQVBxTEFA;
      string RIVZRsmuLK;
      string LjWIbUCylc;
      string EtqAOQnzxl;
      string tEdwLqXAUt;
      if(EtbfZpmFYp == aEewKXechl){aJyUuJfItg = true;}
      else if(aEewKXechl == EtbfZpmFYp){jLZzLemjDP = true;}
      if(WxMEHSZXVh == yItwYUTUla){tUScwXQUKB = true;}
      else if(yItwYUTUla == WxMEHSZXVh){FcqPSygDyr = true;}
      if(ryTRYhfmbk == OdkZpJFWHH){FmyZPHFZwk = true;}
      else if(OdkZpJFWHH == ryTRYhfmbk){ffXMREdzDl = true;}
      if(kkLCrwJNwl == TEVzjNJjxd){wCdrBuuVEF = true;}
      else if(TEVzjNJjxd == kkLCrwJNwl){GkDhFKfZwf = true;}
      if(MAqBCNPqHT == ztalnNEKfH){jeFPrZlAAn = true;}
      else if(ztalnNEKfH == MAqBCNPqHT){GbHmHGeByE = true;}
      if(jGNDdFZJHr == sDQVBxTEFA){ZDpTomLYFn = true;}
      else if(sDQVBxTEFA == jGNDdFZJHr){xPxlTEmMhG = true;}
      if(JzcnFllKML == RIVZRsmuLK){DGLJkrpaaB = true;}
      else if(RIVZRsmuLK == JzcnFllKML){AmgQIUYJJI = true;}
      if(JLbjUqHRPK == LjWIbUCylc){buPFQZghgo = true;}
      if(SnfIBdXIYl == EtqAOQnzxl){VFYIKsMKCN = true;}
      if(VzGEbMXDwQ == tEdwLqXAUt){iWQQCdSwdz = true;}
      while(LjWIbUCylc == JLbjUqHRPK){RGGRlDXkEK = true;}
      while(EtqAOQnzxl == EtqAOQnzxl){ZcBzopmROB = true;}
      while(tEdwLqXAUt == tEdwLqXAUt){WSrpfSupdm = true;}
      if(aJyUuJfItg == true){aJyUuJfItg = false;}
      if(tUScwXQUKB == true){tUScwXQUKB = false;}
      if(FmyZPHFZwk == true){FmyZPHFZwk = false;}
      if(wCdrBuuVEF == true){wCdrBuuVEF = false;}
      if(jeFPrZlAAn == true){jeFPrZlAAn = false;}
      if(ZDpTomLYFn == true){ZDpTomLYFn = false;}
      if(DGLJkrpaaB == true){DGLJkrpaaB = false;}
      if(buPFQZghgo == true){buPFQZghgo = false;}
      if(VFYIKsMKCN == true){VFYIKsMKCN = false;}
      if(iWQQCdSwdz == true){iWQQCdSwdz = false;}
      if(jLZzLemjDP == true){jLZzLemjDP = false;}
      if(FcqPSygDyr == true){FcqPSygDyr = false;}
      if(ffXMREdzDl == true){ffXMREdzDl = false;}
      if(GkDhFKfZwf == true){GkDhFKfZwf = false;}
      if(GbHmHGeByE == true){GbHmHGeByE = false;}
      if(xPxlTEmMhG == true){xPxlTEmMhG = false;}
      if(AmgQIUYJJI == true){AmgQIUYJJI = false;}
      if(RGGRlDXkEK == true){RGGRlDXkEK = false;}
      if(ZcBzopmROB == true){ZcBzopmROB = false;}
      if(WSrpfSupdm == true){WSrpfSupdm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGMUQKZQVH
{ 
  void WXlycqELpR()
  { 
      bool eqLoxUguLr = false;
      bool KOwoaLmcrJ = false;
      bool CpTrMZWrjN = false;
      bool XpRourJggM = false;
      bool ENtiXPnyhK = false;
      bool bAnoNoXSbX = false;
      bool yoKyTUxHti = false;
      bool CGufEnujUx = false;
      bool kXKZkXCcaF = false;
      bool TpEJNPCuPC = false;
      bool RgEyHVEHjY = false;
      bool snxelZdkNw = false;
      bool RTfnPLBlRo = false;
      bool lATReDTMRO = false;
      bool SusCLesZWn = false;
      bool kRgTkxBPiu = false;
      bool TSptmsTfzh = false;
      bool GQSzcWaccj = false;
      bool SbOdDUSAgg = false;
      bool CEdVtzEyPS = false;
      string qtNfxxxjaL;
      string bQTcUymGLq;
      string EsPuLCgLLV;
      string ZMrBxyWzZU;
      string hdSctiGNnJ;
      string cqjxqyeSUu;
      string QlXEkOXSfV;
      string amfpJaZmBb;
      string wTWCsictJz;
      string TEeeEuFNqe;
      string LmhShoKsnQ;
      string XrRrzwPVKB;
      string kcIfCWHBlN;
      string ULuVQIlETD;
      string YjGsabmmfH;
      string fiCoshdBPK;
      string gIGZuLwuap;
      string KKBHcBWPEa;
      string jUVdhlJGbi;
      string dknIWPcfyP;
      if(qtNfxxxjaL == LmhShoKsnQ){eqLoxUguLr = true;}
      else if(LmhShoKsnQ == qtNfxxxjaL){RgEyHVEHjY = true;}
      if(bQTcUymGLq == XrRrzwPVKB){KOwoaLmcrJ = true;}
      else if(XrRrzwPVKB == bQTcUymGLq){snxelZdkNw = true;}
      if(EsPuLCgLLV == kcIfCWHBlN){CpTrMZWrjN = true;}
      else if(kcIfCWHBlN == EsPuLCgLLV){RTfnPLBlRo = true;}
      if(ZMrBxyWzZU == ULuVQIlETD){XpRourJggM = true;}
      else if(ULuVQIlETD == ZMrBxyWzZU){lATReDTMRO = true;}
      if(hdSctiGNnJ == YjGsabmmfH){ENtiXPnyhK = true;}
      else if(YjGsabmmfH == hdSctiGNnJ){SusCLesZWn = true;}
      if(cqjxqyeSUu == fiCoshdBPK){bAnoNoXSbX = true;}
      else if(fiCoshdBPK == cqjxqyeSUu){kRgTkxBPiu = true;}
      if(QlXEkOXSfV == gIGZuLwuap){yoKyTUxHti = true;}
      else if(gIGZuLwuap == QlXEkOXSfV){TSptmsTfzh = true;}
      if(amfpJaZmBb == KKBHcBWPEa){CGufEnujUx = true;}
      if(wTWCsictJz == jUVdhlJGbi){kXKZkXCcaF = true;}
      if(TEeeEuFNqe == dknIWPcfyP){TpEJNPCuPC = true;}
      while(KKBHcBWPEa == amfpJaZmBb){GQSzcWaccj = true;}
      while(jUVdhlJGbi == jUVdhlJGbi){SbOdDUSAgg = true;}
      while(dknIWPcfyP == dknIWPcfyP){CEdVtzEyPS = true;}
      if(eqLoxUguLr == true){eqLoxUguLr = false;}
      if(KOwoaLmcrJ == true){KOwoaLmcrJ = false;}
      if(CpTrMZWrjN == true){CpTrMZWrjN = false;}
      if(XpRourJggM == true){XpRourJggM = false;}
      if(ENtiXPnyhK == true){ENtiXPnyhK = false;}
      if(bAnoNoXSbX == true){bAnoNoXSbX = false;}
      if(yoKyTUxHti == true){yoKyTUxHti = false;}
      if(CGufEnujUx == true){CGufEnujUx = false;}
      if(kXKZkXCcaF == true){kXKZkXCcaF = false;}
      if(TpEJNPCuPC == true){TpEJNPCuPC = false;}
      if(RgEyHVEHjY == true){RgEyHVEHjY = false;}
      if(snxelZdkNw == true){snxelZdkNw = false;}
      if(RTfnPLBlRo == true){RTfnPLBlRo = false;}
      if(lATReDTMRO == true){lATReDTMRO = false;}
      if(SusCLesZWn == true){SusCLesZWn = false;}
      if(kRgTkxBPiu == true){kRgTkxBPiu = false;}
      if(TSptmsTfzh == true){TSptmsTfzh = false;}
      if(GQSzcWaccj == true){GQSzcWaccj = false;}
      if(SbOdDUSAgg == true){SbOdDUSAgg = false;}
      if(CEdVtzEyPS == true){CEdVtzEyPS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBJOZWOYCB
{ 
  void WogOgSkDqZ()
  { 
      bool zLJkMbkyCD = false;
      bool TXtItojgCp = false;
      bool KzgmqZGjwF = false;
      bool gsccODWkBL = false;
      bool tmGkxmNcyP = false;
      bool hKxOIAdWtm = false;
      bool VBBxWauQtq = false;
      bool RyepwXsuoD = false;
      bool MckfWVwNUO = false;
      bool YApOpskJOW = false;
      bool rwiHxieGSk = false;
      bool GihqZrPVZA = false;
      bool ehweRRHQAC = false;
      bool migSLPtdhn = false;
      bool qptjHpRzny = false;
      bool dPiOqJADpf = false;
      bool aNFQxXBOfK = false;
      bool ylmlJnmLWb = false;
      bool zIcCYXARaB = false;
      bool OpmCMcjdlj = false;
      string sDwMDpnhYH;
      string fwJnZqFbqN;
      string hDGzABIdoF;
      string XdVFiyUKJH;
      string gotDqXTHXd;
      string MimfKowxMB;
      string gJrTiCZDFa;
      string VtRifrJDHc;
      string gAGLropptt;
      string CXyHaXxZTo;
      string xPCwHRQDzS;
      string erojTfCgat;
      string LjJLYyuKII;
      string uiiSeRyKDa;
      string XmpbOJiOnt;
      string UPyYcNFqXJ;
      string VGuqWuJWEC;
      string hrdAWYshwO;
      string PgWNnfkJoR;
      string LHlsERqzFS;
      if(sDwMDpnhYH == xPCwHRQDzS){zLJkMbkyCD = true;}
      else if(xPCwHRQDzS == sDwMDpnhYH){rwiHxieGSk = true;}
      if(fwJnZqFbqN == erojTfCgat){TXtItojgCp = true;}
      else if(erojTfCgat == fwJnZqFbqN){GihqZrPVZA = true;}
      if(hDGzABIdoF == LjJLYyuKII){KzgmqZGjwF = true;}
      else if(LjJLYyuKII == hDGzABIdoF){ehweRRHQAC = true;}
      if(XdVFiyUKJH == uiiSeRyKDa){gsccODWkBL = true;}
      else if(uiiSeRyKDa == XdVFiyUKJH){migSLPtdhn = true;}
      if(gotDqXTHXd == XmpbOJiOnt){tmGkxmNcyP = true;}
      else if(XmpbOJiOnt == gotDqXTHXd){qptjHpRzny = true;}
      if(MimfKowxMB == UPyYcNFqXJ){hKxOIAdWtm = true;}
      else if(UPyYcNFqXJ == MimfKowxMB){dPiOqJADpf = true;}
      if(gJrTiCZDFa == VGuqWuJWEC){VBBxWauQtq = true;}
      else if(VGuqWuJWEC == gJrTiCZDFa){aNFQxXBOfK = true;}
      if(VtRifrJDHc == hrdAWYshwO){RyepwXsuoD = true;}
      if(gAGLropptt == PgWNnfkJoR){MckfWVwNUO = true;}
      if(CXyHaXxZTo == LHlsERqzFS){YApOpskJOW = true;}
      while(hrdAWYshwO == VtRifrJDHc){ylmlJnmLWb = true;}
      while(PgWNnfkJoR == PgWNnfkJoR){zIcCYXARaB = true;}
      while(LHlsERqzFS == LHlsERqzFS){OpmCMcjdlj = true;}
      if(zLJkMbkyCD == true){zLJkMbkyCD = false;}
      if(TXtItojgCp == true){TXtItojgCp = false;}
      if(KzgmqZGjwF == true){KzgmqZGjwF = false;}
      if(gsccODWkBL == true){gsccODWkBL = false;}
      if(tmGkxmNcyP == true){tmGkxmNcyP = false;}
      if(hKxOIAdWtm == true){hKxOIAdWtm = false;}
      if(VBBxWauQtq == true){VBBxWauQtq = false;}
      if(RyepwXsuoD == true){RyepwXsuoD = false;}
      if(MckfWVwNUO == true){MckfWVwNUO = false;}
      if(YApOpskJOW == true){YApOpskJOW = false;}
      if(rwiHxieGSk == true){rwiHxieGSk = false;}
      if(GihqZrPVZA == true){GihqZrPVZA = false;}
      if(ehweRRHQAC == true){ehweRRHQAC = false;}
      if(migSLPtdhn == true){migSLPtdhn = false;}
      if(qptjHpRzny == true){qptjHpRzny = false;}
      if(dPiOqJADpf == true){dPiOqJADpf = false;}
      if(aNFQxXBOfK == true){aNFQxXBOfK = false;}
      if(ylmlJnmLWb == true){ylmlJnmLWb = false;}
      if(zIcCYXARaB == true){zIcCYXARaB = false;}
      if(OpmCMcjdlj == true){OpmCMcjdlj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LZXDEPBLAS
{ 
  void fNaYGWCsXc()
  { 
      bool upitrlUmcx = false;
      bool EXjoZNHbZY = false;
      bool QLoNiqzxjZ = false;
      bool GValCbtrAL = false;
      bool WnmcndPtdl = false;
      bool YLtiLiAVKB = false;
      bool lXDCqixxmx = false;
      bool SObOBcYLYF = false;
      bool aFTxAtarZS = false;
      bool aYgzYzjjkF = false;
      bool fRGfSKjfgi = false;
      bool KowFZgEGCx = false;
      bool HFWTWtgcoC = false;
      bool rnZTYIymdp = false;
      bool KuKpIlbbYr = false;
      bool udhnxatlJY = false;
      bool cGpeqVOcfR = false;
      bool hQbLmMugLj = false;
      bool RFExGNGlWy = false;
      bool NLdFNDFezm = false;
      string QFWgUlmwBW;
      string QoezPzLnwC;
      string KaJXQAOEmW;
      string yEVSCumDtu;
      string IccqIxbgab;
      string TIxkNouyPT;
      string WhIdYLTMxT;
      string LItAshxSPS;
      string YhcLDpHjEM;
      string znmaXZTySw;
      string dPiGPLNxqf;
      string qbiwtoFxai;
      string EiHjUXUSbS;
      string OzASoJyVwq;
      string bJsYUWFqfi;
      string UVXjruHylr;
      string qtUXQrbPHk;
      string piBjGtpiOx;
      string RdmsyrbPas;
      string CziDAgnUHc;
      if(QFWgUlmwBW == dPiGPLNxqf){upitrlUmcx = true;}
      else if(dPiGPLNxqf == QFWgUlmwBW){fRGfSKjfgi = true;}
      if(QoezPzLnwC == qbiwtoFxai){EXjoZNHbZY = true;}
      else if(qbiwtoFxai == QoezPzLnwC){KowFZgEGCx = true;}
      if(KaJXQAOEmW == EiHjUXUSbS){QLoNiqzxjZ = true;}
      else if(EiHjUXUSbS == KaJXQAOEmW){HFWTWtgcoC = true;}
      if(yEVSCumDtu == OzASoJyVwq){GValCbtrAL = true;}
      else if(OzASoJyVwq == yEVSCumDtu){rnZTYIymdp = true;}
      if(IccqIxbgab == bJsYUWFqfi){WnmcndPtdl = true;}
      else if(bJsYUWFqfi == IccqIxbgab){KuKpIlbbYr = true;}
      if(TIxkNouyPT == UVXjruHylr){YLtiLiAVKB = true;}
      else if(UVXjruHylr == TIxkNouyPT){udhnxatlJY = true;}
      if(WhIdYLTMxT == qtUXQrbPHk){lXDCqixxmx = true;}
      else if(qtUXQrbPHk == WhIdYLTMxT){cGpeqVOcfR = true;}
      if(LItAshxSPS == piBjGtpiOx){SObOBcYLYF = true;}
      if(YhcLDpHjEM == RdmsyrbPas){aFTxAtarZS = true;}
      if(znmaXZTySw == CziDAgnUHc){aYgzYzjjkF = true;}
      while(piBjGtpiOx == LItAshxSPS){hQbLmMugLj = true;}
      while(RdmsyrbPas == RdmsyrbPas){RFExGNGlWy = true;}
      while(CziDAgnUHc == CziDAgnUHc){NLdFNDFezm = true;}
      if(upitrlUmcx == true){upitrlUmcx = false;}
      if(EXjoZNHbZY == true){EXjoZNHbZY = false;}
      if(QLoNiqzxjZ == true){QLoNiqzxjZ = false;}
      if(GValCbtrAL == true){GValCbtrAL = false;}
      if(WnmcndPtdl == true){WnmcndPtdl = false;}
      if(YLtiLiAVKB == true){YLtiLiAVKB = false;}
      if(lXDCqixxmx == true){lXDCqixxmx = false;}
      if(SObOBcYLYF == true){SObOBcYLYF = false;}
      if(aFTxAtarZS == true){aFTxAtarZS = false;}
      if(aYgzYzjjkF == true){aYgzYzjjkF = false;}
      if(fRGfSKjfgi == true){fRGfSKjfgi = false;}
      if(KowFZgEGCx == true){KowFZgEGCx = false;}
      if(HFWTWtgcoC == true){HFWTWtgcoC = false;}
      if(rnZTYIymdp == true){rnZTYIymdp = false;}
      if(KuKpIlbbYr == true){KuKpIlbbYr = false;}
      if(udhnxatlJY == true){udhnxatlJY = false;}
      if(cGpeqVOcfR == true){cGpeqVOcfR = false;}
      if(hQbLmMugLj == true){hQbLmMugLj = false;}
      if(RFExGNGlWy == true){RFExGNGlWy = false;}
      if(NLdFNDFezm == true){NLdFNDFezm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SYANRPPUNE
{ 
  void alapCHXJgC()
  { 
      bool PVhhdiHDCu = false;
      bool DsrgtlkMxo = false;
      bool hFnoYRlVUU = false;
      bool ifNfITdUyr = false;
      bool RqSdLYaadh = false;
      bool bVVDwKgrIL = false;
      bool wligLWfLXa = false;
      bool IPNEXqlKcz = false;
      bool qLqmrNKJix = false;
      bool lkLlwfIkRo = false;
      bool rOCDZMHQfF = false;
      bool XWOJTktuoy = false;
      bool MWcZnWDaIr = false;
      bool hArnGcJmNf = false;
      bool FscdZPWCSK = false;
      bool kMwSbVkbPC = false;
      bool IfHnXXeZCq = false;
      bool bGhIrStzAY = false;
      bool ABIxGUDYMk = false;
      bool qgXKXYknGC = false;
      string WsSFGBiIps;
      string pGpZMczrdQ;
      string QOpgWMEqjS;
      string txqbgZUreR;
      string afYRsKdNIQ;
      string DcsTbHDlit;
      string wqXXzrPOrl;
      string HHNMokpXmM;
      string ipiSOQEWzZ;
      string WiJkUjHBSB;
      string tOUVJwPgdq;
      string RfzWLFHEIi;
      string nrOSPYybqE;
      string cnFlRTUNJS;
      string AWsIIqilZO;
      string cDsjMCACFj;
      string ymoZOcaNEr;
      string ktuohQzGKY;
      string oLCcbZuUYP;
      string SSHYUMhSse;
      if(WsSFGBiIps == tOUVJwPgdq){PVhhdiHDCu = true;}
      else if(tOUVJwPgdq == WsSFGBiIps){rOCDZMHQfF = true;}
      if(pGpZMczrdQ == RfzWLFHEIi){DsrgtlkMxo = true;}
      else if(RfzWLFHEIi == pGpZMczrdQ){XWOJTktuoy = true;}
      if(QOpgWMEqjS == nrOSPYybqE){hFnoYRlVUU = true;}
      else if(nrOSPYybqE == QOpgWMEqjS){MWcZnWDaIr = true;}
      if(txqbgZUreR == cnFlRTUNJS){ifNfITdUyr = true;}
      else if(cnFlRTUNJS == txqbgZUreR){hArnGcJmNf = true;}
      if(afYRsKdNIQ == AWsIIqilZO){RqSdLYaadh = true;}
      else if(AWsIIqilZO == afYRsKdNIQ){FscdZPWCSK = true;}
      if(DcsTbHDlit == cDsjMCACFj){bVVDwKgrIL = true;}
      else if(cDsjMCACFj == DcsTbHDlit){kMwSbVkbPC = true;}
      if(wqXXzrPOrl == ymoZOcaNEr){wligLWfLXa = true;}
      else if(ymoZOcaNEr == wqXXzrPOrl){IfHnXXeZCq = true;}
      if(HHNMokpXmM == ktuohQzGKY){IPNEXqlKcz = true;}
      if(ipiSOQEWzZ == oLCcbZuUYP){qLqmrNKJix = true;}
      if(WiJkUjHBSB == SSHYUMhSse){lkLlwfIkRo = true;}
      while(ktuohQzGKY == HHNMokpXmM){bGhIrStzAY = true;}
      while(oLCcbZuUYP == oLCcbZuUYP){ABIxGUDYMk = true;}
      while(SSHYUMhSse == SSHYUMhSse){qgXKXYknGC = true;}
      if(PVhhdiHDCu == true){PVhhdiHDCu = false;}
      if(DsrgtlkMxo == true){DsrgtlkMxo = false;}
      if(hFnoYRlVUU == true){hFnoYRlVUU = false;}
      if(ifNfITdUyr == true){ifNfITdUyr = false;}
      if(RqSdLYaadh == true){RqSdLYaadh = false;}
      if(bVVDwKgrIL == true){bVVDwKgrIL = false;}
      if(wligLWfLXa == true){wligLWfLXa = false;}
      if(IPNEXqlKcz == true){IPNEXqlKcz = false;}
      if(qLqmrNKJix == true){qLqmrNKJix = false;}
      if(lkLlwfIkRo == true){lkLlwfIkRo = false;}
      if(rOCDZMHQfF == true){rOCDZMHQfF = false;}
      if(XWOJTktuoy == true){XWOJTktuoy = false;}
      if(MWcZnWDaIr == true){MWcZnWDaIr = false;}
      if(hArnGcJmNf == true){hArnGcJmNf = false;}
      if(FscdZPWCSK == true){FscdZPWCSK = false;}
      if(kMwSbVkbPC == true){kMwSbVkbPC = false;}
      if(IfHnXXeZCq == true){IfHnXXeZCq = false;}
      if(bGhIrStzAY == true){bGhIrStzAY = false;}
      if(ABIxGUDYMk == true){ABIxGUDYMk = false;}
      if(qgXKXYknGC == true){qgXKXYknGC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MSKEWINNEE
{ 
  void jHAwBeMQnb()
  { 
      bool QCircKAYln = false;
      bool lMJCBfQbmo = false;
      bool EwxEwmtKGp = false;
      bool NtQCYtHVsp = false;
      bool tZuSXZhpYj = false;
      bool MoqLlUEdwp = false;
      bool PpRuZruGcH = false;
      bool YtiwtdBdgW = false;
      bool EDkWdYCFQE = false;
      bool ocZCaEHzse = false;
      bool dbMRLRGtRH = false;
      bool TaxYkLEuRB = false;
      bool opoYRuTfVo = false;
      bool VBjBscqTKL = false;
      bool RImJkOfBRO = false;
      bool AMhrpmmnzQ = false;
      bool yaYclRpufI = false;
      bool UjkGigCemD = false;
      bool OSOHnJSrLF = false;
      bool pCUtNpjKXS = false;
      string giQkuKjIAX;
      string QMJeqBSAxi;
      string PbAsarDsVm;
      string ScOBysJsfm;
      string NjViCBqUbs;
      string lolIxFhWKC;
      string HpmNEmyHfx;
      string qYTJVeFRpY;
      string BiQbBdqFDs;
      string LmicfWxIeP;
      string DioeCMVbmS;
      string AQfkBXYKLa;
      string urDllDopdy;
      string hwlaVRtlYn;
      string HPSksuHybH;
      string xlxETLeCsy;
      string XeynjDdEOi;
      string dmkXSfYRsp;
      string wqOVAuzgHK;
      string mqsaQcReAp;
      if(giQkuKjIAX == DioeCMVbmS){QCircKAYln = true;}
      else if(DioeCMVbmS == giQkuKjIAX){dbMRLRGtRH = true;}
      if(QMJeqBSAxi == AQfkBXYKLa){lMJCBfQbmo = true;}
      else if(AQfkBXYKLa == QMJeqBSAxi){TaxYkLEuRB = true;}
      if(PbAsarDsVm == urDllDopdy){EwxEwmtKGp = true;}
      else if(urDllDopdy == PbAsarDsVm){opoYRuTfVo = true;}
      if(ScOBysJsfm == hwlaVRtlYn){NtQCYtHVsp = true;}
      else if(hwlaVRtlYn == ScOBysJsfm){VBjBscqTKL = true;}
      if(NjViCBqUbs == HPSksuHybH){tZuSXZhpYj = true;}
      else if(HPSksuHybH == NjViCBqUbs){RImJkOfBRO = true;}
      if(lolIxFhWKC == xlxETLeCsy){MoqLlUEdwp = true;}
      else if(xlxETLeCsy == lolIxFhWKC){AMhrpmmnzQ = true;}
      if(HpmNEmyHfx == XeynjDdEOi){PpRuZruGcH = true;}
      else if(XeynjDdEOi == HpmNEmyHfx){yaYclRpufI = true;}
      if(qYTJVeFRpY == dmkXSfYRsp){YtiwtdBdgW = true;}
      if(BiQbBdqFDs == wqOVAuzgHK){EDkWdYCFQE = true;}
      if(LmicfWxIeP == mqsaQcReAp){ocZCaEHzse = true;}
      while(dmkXSfYRsp == qYTJVeFRpY){UjkGigCemD = true;}
      while(wqOVAuzgHK == wqOVAuzgHK){OSOHnJSrLF = true;}
      while(mqsaQcReAp == mqsaQcReAp){pCUtNpjKXS = true;}
      if(QCircKAYln == true){QCircKAYln = false;}
      if(lMJCBfQbmo == true){lMJCBfQbmo = false;}
      if(EwxEwmtKGp == true){EwxEwmtKGp = false;}
      if(NtQCYtHVsp == true){NtQCYtHVsp = false;}
      if(tZuSXZhpYj == true){tZuSXZhpYj = false;}
      if(MoqLlUEdwp == true){MoqLlUEdwp = false;}
      if(PpRuZruGcH == true){PpRuZruGcH = false;}
      if(YtiwtdBdgW == true){YtiwtdBdgW = false;}
      if(EDkWdYCFQE == true){EDkWdYCFQE = false;}
      if(ocZCaEHzse == true){ocZCaEHzse = false;}
      if(dbMRLRGtRH == true){dbMRLRGtRH = false;}
      if(TaxYkLEuRB == true){TaxYkLEuRB = false;}
      if(opoYRuTfVo == true){opoYRuTfVo = false;}
      if(VBjBscqTKL == true){VBjBscqTKL = false;}
      if(RImJkOfBRO == true){RImJkOfBRO = false;}
      if(AMhrpmmnzQ == true){AMhrpmmnzQ = false;}
      if(yaYclRpufI == true){yaYclRpufI = false;}
      if(UjkGigCemD == true){UjkGigCemD = false;}
      if(OSOHnJSrLF == true){OSOHnJSrLF = false;}
      if(pCUtNpjKXS == true){pCUtNpjKXS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OHUSKJPHSO
{ 
  void SblrNGsBod()
  { 
      bool ipwhIZsRyL = false;
      bool MzchwZhLLG = false;
      bool DHcpwPqxaY = false;
      bool cDgLHQPmsy = false;
      bool rgTcqljHpQ = false;
      bool LLpfCbNFks = false;
      bool huqZhISRZf = false;
      bool JtSMOVmzzJ = false;
      bool ejHKMRNAIf = false;
      bool CKBAPwpsui = false;
      bool TShJGRrdRg = false;
      bool nOGbNymgNQ = false;
      bool uRJscyrSwS = false;
      bool fsEPpMBxDu = false;
      bool YjibqnEZlR = false;
      bool IIfdnBIngH = false;
      bool YZgzAtKpkA = false;
      bool wpcRrKhgBo = false;
      bool tSfeJWNZbo = false;
      bool DNQuWzDjax = false;
      string ukelokKzcU;
      string ZytKMbPDCT;
      string GzHQncTbPQ;
      string PBCJpumFPo;
      string knnnTGEpoG;
      string zcOzYwcOyM;
      string QhjLEXujUR;
      string nKnMiSKTwg;
      string YdmIRmlCkt;
      string RYHCYCEciw;
      string KTVXSonBQF;
      string kJRQmluasR;
      string krzZzOCknf;
      string OhjAVFIOpc;
      string ykleIIHpPl;
      string HciRLSTuYD;
      string lDNjqCYRth;
      string dgjQSAFURq;
      string GMUBYkzRnD;
      string kNolptWCmG;
      if(ukelokKzcU == KTVXSonBQF){ipwhIZsRyL = true;}
      else if(KTVXSonBQF == ukelokKzcU){TShJGRrdRg = true;}
      if(ZytKMbPDCT == kJRQmluasR){MzchwZhLLG = true;}
      else if(kJRQmluasR == ZytKMbPDCT){nOGbNymgNQ = true;}
      if(GzHQncTbPQ == krzZzOCknf){DHcpwPqxaY = true;}
      else if(krzZzOCknf == GzHQncTbPQ){uRJscyrSwS = true;}
      if(PBCJpumFPo == OhjAVFIOpc){cDgLHQPmsy = true;}
      else if(OhjAVFIOpc == PBCJpumFPo){fsEPpMBxDu = true;}
      if(knnnTGEpoG == ykleIIHpPl){rgTcqljHpQ = true;}
      else if(ykleIIHpPl == knnnTGEpoG){YjibqnEZlR = true;}
      if(zcOzYwcOyM == HciRLSTuYD){LLpfCbNFks = true;}
      else if(HciRLSTuYD == zcOzYwcOyM){IIfdnBIngH = true;}
      if(QhjLEXujUR == lDNjqCYRth){huqZhISRZf = true;}
      else if(lDNjqCYRth == QhjLEXujUR){YZgzAtKpkA = true;}
      if(nKnMiSKTwg == dgjQSAFURq){JtSMOVmzzJ = true;}
      if(YdmIRmlCkt == GMUBYkzRnD){ejHKMRNAIf = true;}
      if(RYHCYCEciw == kNolptWCmG){CKBAPwpsui = true;}
      while(dgjQSAFURq == nKnMiSKTwg){wpcRrKhgBo = true;}
      while(GMUBYkzRnD == GMUBYkzRnD){tSfeJWNZbo = true;}
      while(kNolptWCmG == kNolptWCmG){DNQuWzDjax = true;}
      if(ipwhIZsRyL == true){ipwhIZsRyL = false;}
      if(MzchwZhLLG == true){MzchwZhLLG = false;}
      if(DHcpwPqxaY == true){DHcpwPqxaY = false;}
      if(cDgLHQPmsy == true){cDgLHQPmsy = false;}
      if(rgTcqljHpQ == true){rgTcqljHpQ = false;}
      if(LLpfCbNFks == true){LLpfCbNFks = false;}
      if(huqZhISRZf == true){huqZhISRZf = false;}
      if(JtSMOVmzzJ == true){JtSMOVmzzJ = false;}
      if(ejHKMRNAIf == true){ejHKMRNAIf = false;}
      if(CKBAPwpsui == true){CKBAPwpsui = false;}
      if(TShJGRrdRg == true){TShJGRrdRg = false;}
      if(nOGbNymgNQ == true){nOGbNymgNQ = false;}
      if(uRJscyrSwS == true){uRJscyrSwS = false;}
      if(fsEPpMBxDu == true){fsEPpMBxDu = false;}
      if(YjibqnEZlR == true){YjibqnEZlR = false;}
      if(IIfdnBIngH == true){IIfdnBIngH = false;}
      if(YZgzAtKpkA == true){YZgzAtKpkA = false;}
      if(wpcRrKhgBo == true){wpcRrKhgBo = false;}
      if(tSfeJWNZbo == true){tSfeJWNZbo = false;}
      if(DNQuWzDjax == true){DNQuWzDjax = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IGJUWFUDCV
{ 
  void cyuDrUruwY()
  { 
      bool WwiPUtBgnm = false;
      bool GxgkiVSMdS = false;
      bool sOEJcAmJel = false;
      bool mmYRsuAnKA = false;
      bool KklEORTxwM = false;
      bool cPPziIqZlU = false;
      bool HrCCASYPrm = false;
      bool VdCcIIbztL = false;
      bool foMSIWXYhk = false;
      bool DZBpsRhjDu = false;
      bool sEFJpyNlpa = false;
      bool fqfanRejsd = false;
      bool uzgHiwcLip = false;
      bool ZrwySbjDbJ = false;
      bool IkiHELtaBa = false;
      bool mypZAsXyZt = false;
      bool VBDABnugIM = false;
      bool hbIjUJQYCW = false;
      bool CBJIDbBWyY = false;
      bool ElchmGhhGP = false;
      string fCLRDWmPjB;
      string Zaazglgtba;
      string twtgjcCSAr;
      string zUXGzGPieW;
      string qCmZuoxMEh;
      string ByBTZiHdha;
      string UUOqCFCUAa;
      string VyPFiqIUlt;
      string foNSpBSDfP;
      string ykBDBWmuWp;
      string lbMdLCiwki;
      string ZmrmueGwAA;
      string lznjbkxLDL;
      string DNxuIDcjGn;
      string SVSxoLrNHW;
      string QqtWDmnbBa;
      string FWsYeMower;
      string BVoMhPfptP;
      string riDfuMSarV;
      string OBifhwcsRc;
      if(fCLRDWmPjB == lbMdLCiwki){WwiPUtBgnm = true;}
      else if(lbMdLCiwki == fCLRDWmPjB){sEFJpyNlpa = true;}
      if(Zaazglgtba == ZmrmueGwAA){GxgkiVSMdS = true;}
      else if(ZmrmueGwAA == Zaazglgtba){fqfanRejsd = true;}
      if(twtgjcCSAr == lznjbkxLDL){sOEJcAmJel = true;}
      else if(lznjbkxLDL == twtgjcCSAr){uzgHiwcLip = true;}
      if(zUXGzGPieW == DNxuIDcjGn){mmYRsuAnKA = true;}
      else if(DNxuIDcjGn == zUXGzGPieW){ZrwySbjDbJ = true;}
      if(qCmZuoxMEh == SVSxoLrNHW){KklEORTxwM = true;}
      else if(SVSxoLrNHW == qCmZuoxMEh){IkiHELtaBa = true;}
      if(ByBTZiHdha == QqtWDmnbBa){cPPziIqZlU = true;}
      else if(QqtWDmnbBa == ByBTZiHdha){mypZAsXyZt = true;}
      if(UUOqCFCUAa == FWsYeMower){HrCCASYPrm = true;}
      else if(FWsYeMower == UUOqCFCUAa){VBDABnugIM = true;}
      if(VyPFiqIUlt == BVoMhPfptP){VdCcIIbztL = true;}
      if(foNSpBSDfP == riDfuMSarV){foMSIWXYhk = true;}
      if(ykBDBWmuWp == OBifhwcsRc){DZBpsRhjDu = true;}
      while(BVoMhPfptP == VyPFiqIUlt){hbIjUJQYCW = true;}
      while(riDfuMSarV == riDfuMSarV){CBJIDbBWyY = true;}
      while(OBifhwcsRc == OBifhwcsRc){ElchmGhhGP = true;}
      if(WwiPUtBgnm == true){WwiPUtBgnm = false;}
      if(GxgkiVSMdS == true){GxgkiVSMdS = false;}
      if(sOEJcAmJel == true){sOEJcAmJel = false;}
      if(mmYRsuAnKA == true){mmYRsuAnKA = false;}
      if(KklEORTxwM == true){KklEORTxwM = false;}
      if(cPPziIqZlU == true){cPPziIqZlU = false;}
      if(HrCCASYPrm == true){HrCCASYPrm = false;}
      if(VdCcIIbztL == true){VdCcIIbztL = false;}
      if(foMSIWXYhk == true){foMSIWXYhk = false;}
      if(DZBpsRhjDu == true){DZBpsRhjDu = false;}
      if(sEFJpyNlpa == true){sEFJpyNlpa = false;}
      if(fqfanRejsd == true){fqfanRejsd = false;}
      if(uzgHiwcLip == true){uzgHiwcLip = false;}
      if(ZrwySbjDbJ == true){ZrwySbjDbJ = false;}
      if(IkiHELtaBa == true){IkiHELtaBa = false;}
      if(mypZAsXyZt == true){mypZAsXyZt = false;}
      if(VBDABnugIM == true){VBDABnugIM = false;}
      if(hbIjUJQYCW == true){hbIjUJQYCW = false;}
      if(CBJIDbBWyY == true){CBJIDbBWyY = false;}
      if(ElchmGhhGP == true){ElchmGhhGP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JKDMGCMOZJ
{ 
  void OdZxWwoUPT()
  { 
      bool aIDtRWUrJj = false;
      bool sFwNGuGiBR = false;
      bool fVKTMwPXLT = false;
      bool FRZhLcLVwa = false;
      bool rzQsTwDKYZ = false;
      bool CCmyCFyigV = false;
      bool GxfpdaeOBc = false;
      bool ikmZYfEQAQ = false;
      bool rEzlQCebeG = false;
      bool ecnaUuSaPr = false;
      bool RnIupQPMYV = false;
      bool AghQcBxtYa = false;
      bool wCjtyGwMFd = false;
      bool NdBIzEwEuz = false;
      bool mRCIGytXyS = false;
      bool yYCnwOENxj = false;
      bool UDHuIWeZQY = false;
      bool FrzYndzanz = false;
      bool MYNlfoaNMk = false;
      bool zhHLejKHzj = false;
      string mMCBKNqTkD;
      string McRPwRPLVC;
      string HsrzxPHrwh;
      string RbkQrCsjQa;
      string WVohoniIGy;
      string qpTnDtUDEt;
      string GyWDkjrAWs;
      string XfuufkDJJJ;
      string gylxpbIwNy;
      string hpfWUXylwE;
      string uilMZKuXHR;
      string pKstNHMZMJ;
      string bulYLhAYaI;
      string lRNFNyMYWe;
      string fjnuHXwkIM;
      string KYZmbAwMBr;
      string KWxzfYwngO;
      string unDgcrGpQm;
      string lPPNyNracM;
      string CzXeUJloPi;
      if(mMCBKNqTkD == uilMZKuXHR){aIDtRWUrJj = true;}
      else if(uilMZKuXHR == mMCBKNqTkD){RnIupQPMYV = true;}
      if(McRPwRPLVC == pKstNHMZMJ){sFwNGuGiBR = true;}
      else if(pKstNHMZMJ == McRPwRPLVC){AghQcBxtYa = true;}
      if(HsrzxPHrwh == bulYLhAYaI){fVKTMwPXLT = true;}
      else if(bulYLhAYaI == HsrzxPHrwh){wCjtyGwMFd = true;}
      if(RbkQrCsjQa == lRNFNyMYWe){FRZhLcLVwa = true;}
      else if(lRNFNyMYWe == RbkQrCsjQa){NdBIzEwEuz = true;}
      if(WVohoniIGy == fjnuHXwkIM){rzQsTwDKYZ = true;}
      else if(fjnuHXwkIM == WVohoniIGy){mRCIGytXyS = true;}
      if(qpTnDtUDEt == KYZmbAwMBr){CCmyCFyigV = true;}
      else if(KYZmbAwMBr == qpTnDtUDEt){yYCnwOENxj = true;}
      if(GyWDkjrAWs == KWxzfYwngO){GxfpdaeOBc = true;}
      else if(KWxzfYwngO == GyWDkjrAWs){UDHuIWeZQY = true;}
      if(XfuufkDJJJ == unDgcrGpQm){ikmZYfEQAQ = true;}
      if(gylxpbIwNy == lPPNyNracM){rEzlQCebeG = true;}
      if(hpfWUXylwE == CzXeUJloPi){ecnaUuSaPr = true;}
      while(unDgcrGpQm == XfuufkDJJJ){FrzYndzanz = true;}
      while(lPPNyNracM == lPPNyNracM){MYNlfoaNMk = true;}
      while(CzXeUJloPi == CzXeUJloPi){zhHLejKHzj = true;}
      if(aIDtRWUrJj == true){aIDtRWUrJj = false;}
      if(sFwNGuGiBR == true){sFwNGuGiBR = false;}
      if(fVKTMwPXLT == true){fVKTMwPXLT = false;}
      if(FRZhLcLVwa == true){FRZhLcLVwa = false;}
      if(rzQsTwDKYZ == true){rzQsTwDKYZ = false;}
      if(CCmyCFyigV == true){CCmyCFyigV = false;}
      if(GxfpdaeOBc == true){GxfpdaeOBc = false;}
      if(ikmZYfEQAQ == true){ikmZYfEQAQ = false;}
      if(rEzlQCebeG == true){rEzlQCebeG = false;}
      if(ecnaUuSaPr == true){ecnaUuSaPr = false;}
      if(RnIupQPMYV == true){RnIupQPMYV = false;}
      if(AghQcBxtYa == true){AghQcBxtYa = false;}
      if(wCjtyGwMFd == true){wCjtyGwMFd = false;}
      if(NdBIzEwEuz == true){NdBIzEwEuz = false;}
      if(mRCIGytXyS == true){mRCIGytXyS = false;}
      if(yYCnwOENxj == true){yYCnwOENxj = false;}
      if(UDHuIWeZQY == true){UDHuIWeZQY = false;}
      if(FrzYndzanz == true){FrzYndzanz = false;}
      if(MYNlfoaNMk == true){MYNlfoaNMk = false;}
      if(zhHLejKHzj == true){zhHLejKHzj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KSQVIWODLS
{ 
  void ThUfGxltKq()
  { 
      bool LkjNiuZTYe = false;
      bool EqNggYsVUk = false;
      bool wIiUCqmESa = false;
      bool iOainHbVQD = false;
      bool bQtTlhAebw = false;
      bool XdJNPDCPKr = false;
      bool IVByupQerY = false;
      bool xXFRJeNOiU = false;
      bool pIbVCFEMTk = false;
      bool FLLYuGPwXu = false;
      bool RVlCzAYrEj = false;
      bool omgpBAseup = false;
      bool kDLGTkMfVC = false;
      bool OQpmCUVYWB = false;
      bool fMIiuReUXt = false;
      bool MkBhKOKfhN = false;
      bool nsVBUYxtmf = false;
      bool eUHsKYtbKC = false;
      bool GqHbpdPIcn = false;
      bool JppJNlpHNW = false;
      string ccmILQXBtQ;
      string CMuGpYfgVT;
      string dBaEcXVUhx;
      string hIGSxCybxM;
      string nDBlRxEEHM;
      string xlWsDbBifm;
      string tDSwhtGbIn;
      string aDiIeZznlf;
      string TRMVAwkNPV;
      string AOwJSkkFDX;
      string qcuTlsCNNc;
      string bMwATcqxwl;
      string IrLmmLHZps;
      string otkOnpVriH;
      string tXzlsmSupp;
      string tmIQPyQHgZ;
      string kcWUmhbhLc;
      string GyNorjsZtz;
      string sLiAzCkTzp;
      string ZOLJVRAeyL;
      if(ccmILQXBtQ == qcuTlsCNNc){LkjNiuZTYe = true;}
      else if(qcuTlsCNNc == ccmILQXBtQ){RVlCzAYrEj = true;}
      if(CMuGpYfgVT == bMwATcqxwl){EqNggYsVUk = true;}
      else if(bMwATcqxwl == CMuGpYfgVT){omgpBAseup = true;}
      if(dBaEcXVUhx == IrLmmLHZps){wIiUCqmESa = true;}
      else if(IrLmmLHZps == dBaEcXVUhx){kDLGTkMfVC = true;}
      if(hIGSxCybxM == otkOnpVriH){iOainHbVQD = true;}
      else if(otkOnpVriH == hIGSxCybxM){OQpmCUVYWB = true;}
      if(nDBlRxEEHM == tXzlsmSupp){bQtTlhAebw = true;}
      else if(tXzlsmSupp == nDBlRxEEHM){fMIiuReUXt = true;}
      if(xlWsDbBifm == tmIQPyQHgZ){XdJNPDCPKr = true;}
      else if(tmIQPyQHgZ == xlWsDbBifm){MkBhKOKfhN = true;}
      if(tDSwhtGbIn == kcWUmhbhLc){IVByupQerY = true;}
      else if(kcWUmhbhLc == tDSwhtGbIn){nsVBUYxtmf = true;}
      if(aDiIeZznlf == GyNorjsZtz){xXFRJeNOiU = true;}
      if(TRMVAwkNPV == sLiAzCkTzp){pIbVCFEMTk = true;}
      if(AOwJSkkFDX == ZOLJVRAeyL){FLLYuGPwXu = true;}
      while(GyNorjsZtz == aDiIeZznlf){eUHsKYtbKC = true;}
      while(sLiAzCkTzp == sLiAzCkTzp){GqHbpdPIcn = true;}
      while(ZOLJVRAeyL == ZOLJVRAeyL){JppJNlpHNW = true;}
      if(LkjNiuZTYe == true){LkjNiuZTYe = false;}
      if(EqNggYsVUk == true){EqNggYsVUk = false;}
      if(wIiUCqmESa == true){wIiUCqmESa = false;}
      if(iOainHbVQD == true){iOainHbVQD = false;}
      if(bQtTlhAebw == true){bQtTlhAebw = false;}
      if(XdJNPDCPKr == true){XdJNPDCPKr = false;}
      if(IVByupQerY == true){IVByupQerY = false;}
      if(xXFRJeNOiU == true){xXFRJeNOiU = false;}
      if(pIbVCFEMTk == true){pIbVCFEMTk = false;}
      if(FLLYuGPwXu == true){FLLYuGPwXu = false;}
      if(RVlCzAYrEj == true){RVlCzAYrEj = false;}
      if(omgpBAseup == true){omgpBAseup = false;}
      if(kDLGTkMfVC == true){kDLGTkMfVC = false;}
      if(OQpmCUVYWB == true){OQpmCUVYWB = false;}
      if(fMIiuReUXt == true){fMIiuReUXt = false;}
      if(MkBhKOKfhN == true){MkBhKOKfhN = false;}
      if(nsVBUYxtmf == true){nsVBUYxtmf = false;}
      if(eUHsKYtbKC == true){eUHsKYtbKC = false;}
      if(GqHbpdPIcn == true){GqHbpdPIcn = false;}
      if(JppJNlpHNW == true){JppJNlpHNW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GRWNWZJDRX
{ 
  void kqXuxpQkyR()
  { 
      bool LecFOdMWTI = false;
      bool AGQoLIZPsI = false;
      bool COINdOeTCl = false;
      bool QAsgMgdhgV = false;
      bool bHIFwBtzWq = false;
      bool BGHiywWPbA = false;
      bool zrUgrzNibd = false;
      bool driXgtFCQb = false;
      bool TfxLjJsJiP = false;
      bool KOFfWjmbNx = false;
      bool nLWrNJXiCD = false;
      bool pTzAgTuIxh = false;
      bool FEAMTPlDAw = false;
      bool HdoTnIIFxZ = false;
      bool lJGfZqOFzD = false;
      bool oddeqiLKXx = false;
      bool WUhGuLdfLY = false;
      bool KoLXwuyTmc = false;
      bool AgDxHdAJcE = false;
      bool wygADRbAjN = false;
      string TbQZUearfn;
      string oKmkmFAGsp;
      string EkcBTKVPmj;
      string wmiUCFCFri;
      string ccmeVXnxXr;
      string HJHBcizOGK;
      string JLEurCaSih;
      string DuNKMbxxeu;
      string VYquclfgqT;
      string FmzgZQXrmT;
      string wUNpnMuwnB;
      string lCjKnjUJSF;
      string WtbPbPwgku;
      string DEKLzBKBGP;
      string qispgDDnro;
      string wOZhwBryNX;
      string POLrxgqXKl;
      string ZSCCOnBkhY;
      string MHnuznecOx;
      string ILnhzbWArA;
      if(TbQZUearfn == wUNpnMuwnB){LecFOdMWTI = true;}
      else if(wUNpnMuwnB == TbQZUearfn){nLWrNJXiCD = true;}
      if(oKmkmFAGsp == lCjKnjUJSF){AGQoLIZPsI = true;}
      else if(lCjKnjUJSF == oKmkmFAGsp){pTzAgTuIxh = true;}
      if(EkcBTKVPmj == WtbPbPwgku){COINdOeTCl = true;}
      else if(WtbPbPwgku == EkcBTKVPmj){FEAMTPlDAw = true;}
      if(wmiUCFCFri == DEKLzBKBGP){QAsgMgdhgV = true;}
      else if(DEKLzBKBGP == wmiUCFCFri){HdoTnIIFxZ = true;}
      if(ccmeVXnxXr == qispgDDnro){bHIFwBtzWq = true;}
      else if(qispgDDnro == ccmeVXnxXr){lJGfZqOFzD = true;}
      if(HJHBcizOGK == wOZhwBryNX){BGHiywWPbA = true;}
      else if(wOZhwBryNX == HJHBcizOGK){oddeqiLKXx = true;}
      if(JLEurCaSih == POLrxgqXKl){zrUgrzNibd = true;}
      else if(POLrxgqXKl == JLEurCaSih){WUhGuLdfLY = true;}
      if(DuNKMbxxeu == ZSCCOnBkhY){driXgtFCQb = true;}
      if(VYquclfgqT == MHnuznecOx){TfxLjJsJiP = true;}
      if(FmzgZQXrmT == ILnhzbWArA){KOFfWjmbNx = true;}
      while(ZSCCOnBkhY == DuNKMbxxeu){KoLXwuyTmc = true;}
      while(MHnuznecOx == MHnuznecOx){AgDxHdAJcE = true;}
      while(ILnhzbWArA == ILnhzbWArA){wygADRbAjN = true;}
      if(LecFOdMWTI == true){LecFOdMWTI = false;}
      if(AGQoLIZPsI == true){AGQoLIZPsI = false;}
      if(COINdOeTCl == true){COINdOeTCl = false;}
      if(QAsgMgdhgV == true){QAsgMgdhgV = false;}
      if(bHIFwBtzWq == true){bHIFwBtzWq = false;}
      if(BGHiywWPbA == true){BGHiywWPbA = false;}
      if(zrUgrzNibd == true){zrUgrzNibd = false;}
      if(driXgtFCQb == true){driXgtFCQb = false;}
      if(TfxLjJsJiP == true){TfxLjJsJiP = false;}
      if(KOFfWjmbNx == true){KOFfWjmbNx = false;}
      if(nLWrNJXiCD == true){nLWrNJXiCD = false;}
      if(pTzAgTuIxh == true){pTzAgTuIxh = false;}
      if(FEAMTPlDAw == true){FEAMTPlDAw = false;}
      if(HdoTnIIFxZ == true){HdoTnIIFxZ = false;}
      if(lJGfZqOFzD == true){lJGfZqOFzD = false;}
      if(oddeqiLKXx == true){oddeqiLKXx = false;}
      if(WUhGuLdfLY == true){WUhGuLdfLY = false;}
      if(KoLXwuyTmc == true){KoLXwuyTmc = false;}
      if(AgDxHdAJcE == true){AgDxHdAJcE = false;}
      if(wygADRbAjN == true){wygADRbAjN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LHBDTAYAUK
{ 
  void nRcVCzzCQm()
  { 
      bool AwKegTrmOR = false;
      bool akjVUKEYXx = false;
      bool WmIOPcKdmO = false;
      bool eTezrOFYNy = false;
      bool DBuXatCxMr = false;
      bool EfFgzNmuOE = false;
      bool JOzzlGFjdG = false;
      bool EeKYtUqkmU = false;
      bool ZMQtJzOyzd = false;
      bool aKJJonBwkU = false;
      bool oSTGmZVfle = false;
      bool VCHtdxyFom = false;
      bool qGjzetUAjF = false;
      bool TuzSfHrJGj = false;
      bool ciMUIYDPer = false;
      bool pwGychhTbs = false;
      bool EUugKaCnNW = false;
      bool EnyFJItPqF = false;
      bool qFUrPWnBox = false;
      bool YYhNeImfJg = false;
      string aMAxxxhHqG;
      string oujVtWhqVq;
      string jgsHqZgefZ;
      string NuGmFLeXSW;
      string OFQUEcXboe;
      string cKKhWtSsFW;
      string PDbRrsowQi;
      string rKYzbdQYCO;
      string BFoBxDjYPL;
      string rkSuGLdybK;
      string naLFmSlLFr;
      string ctpqUJNZUo;
      string IPgEqGqdrP;
      string zRwqZZtiOd;
      string QYSWhyuaZx;
      string yEclCXtGOf;
      string aHTosLxyQu;
      string PdLpXjxJWr;
      string LPDuRunKoC;
      string emThDJEcdW;
      if(aMAxxxhHqG == naLFmSlLFr){AwKegTrmOR = true;}
      else if(naLFmSlLFr == aMAxxxhHqG){oSTGmZVfle = true;}
      if(oujVtWhqVq == ctpqUJNZUo){akjVUKEYXx = true;}
      else if(ctpqUJNZUo == oujVtWhqVq){VCHtdxyFom = true;}
      if(jgsHqZgefZ == IPgEqGqdrP){WmIOPcKdmO = true;}
      else if(IPgEqGqdrP == jgsHqZgefZ){qGjzetUAjF = true;}
      if(NuGmFLeXSW == zRwqZZtiOd){eTezrOFYNy = true;}
      else if(zRwqZZtiOd == NuGmFLeXSW){TuzSfHrJGj = true;}
      if(OFQUEcXboe == QYSWhyuaZx){DBuXatCxMr = true;}
      else if(QYSWhyuaZx == OFQUEcXboe){ciMUIYDPer = true;}
      if(cKKhWtSsFW == yEclCXtGOf){EfFgzNmuOE = true;}
      else if(yEclCXtGOf == cKKhWtSsFW){pwGychhTbs = true;}
      if(PDbRrsowQi == aHTosLxyQu){JOzzlGFjdG = true;}
      else if(aHTosLxyQu == PDbRrsowQi){EUugKaCnNW = true;}
      if(rKYzbdQYCO == PdLpXjxJWr){EeKYtUqkmU = true;}
      if(BFoBxDjYPL == LPDuRunKoC){ZMQtJzOyzd = true;}
      if(rkSuGLdybK == emThDJEcdW){aKJJonBwkU = true;}
      while(PdLpXjxJWr == rKYzbdQYCO){EnyFJItPqF = true;}
      while(LPDuRunKoC == LPDuRunKoC){qFUrPWnBox = true;}
      while(emThDJEcdW == emThDJEcdW){YYhNeImfJg = true;}
      if(AwKegTrmOR == true){AwKegTrmOR = false;}
      if(akjVUKEYXx == true){akjVUKEYXx = false;}
      if(WmIOPcKdmO == true){WmIOPcKdmO = false;}
      if(eTezrOFYNy == true){eTezrOFYNy = false;}
      if(DBuXatCxMr == true){DBuXatCxMr = false;}
      if(EfFgzNmuOE == true){EfFgzNmuOE = false;}
      if(JOzzlGFjdG == true){JOzzlGFjdG = false;}
      if(EeKYtUqkmU == true){EeKYtUqkmU = false;}
      if(ZMQtJzOyzd == true){ZMQtJzOyzd = false;}
      if(aKJJonBwkU == true){aKJJonBwkU = false;}
      if(oSTGmZVfle == true){oSTGmZVfle = false;}
      if(VCHtdxyFom == true){VCHtdxyFom = false;}
      if(qGjzetUAjF == true){qGjzetUAjF = false;}
      if(TuzSfHrJGj == true){TuzSfHrJGj = false;}
      if(ciMUIYDPer == true){ciMUIYDPer = false;}
      if(pwGychhTbs == true){pwGychhTbs = false;}
      if(EUugKaCnNW == true){EUugKaCnNW = false;}
      if(EnyFJItPqF == true){EnyFJItPqF = false;}
      if(qFUrPWnBox == true){qFUrPWnBox = false;}
      if(YYhNeImfJg == true){YYhNeImfJg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVHRBTBNGJ
{ 
  void JaYDuVRdiQ()
  { 
      bool jYVRLrwOYm = false;
      bool nBfZnLYPme = false;
      bool yPbneKpGBi = false;
      bool lRbSnErfCV = false;
      bool CRXGYdDFMm = false;
      bool GpoasTxgmA = false;
      bool BoMoBWZNli = false;
      bool TrMRcfqUPA = false;
      bool HktOcwbAYT = false;
      bool HKsCTMFiFB = false;
      bool EpScTNcWyM = false;
      bool cbQmrQuyLF = false;
      bool tYnSbIzKyP = false;
      bool aIPNuRRQtP = false;
      bool SFCMqesGJC = false;
      bool RGWAHfCAAK = false;
      bool ORYhkTMDqa = false;
      bool zdDwloWabx = false;
      bool OrAuyTkOGP = false;
      bool PQQjBBfTaW = false;
      string xFLqMQboID;
      string dPWnxYbimG;
      string qkRnqOyeIz;
      string iXhiKhMUCs;
      string NKyaKosBhB;
      string QfrXOMnWAx;
      string RxfIUGhndO;
      string MGftsglpcC;
      string VxwGiCfJTx;
      string toUEaPdoFE;
      string GEWSoKzxeh;
      string axtxbUAZZR;
      string ZXUgUXkbTc;
      string DwjYuQZdRY;
      string DidkVwtXcF;
      string OEPmdhjpyQ;
      string YXcBeeMVBK;
      string tWHBOqtiKX;
      string cNyNOzfxtN;
      string fifAzeFbGq;
      if(xFLqMQboID == GEWSoKzxeh){jYVRLrwOYm = true;}
      else if(GEWSoKzxeh == xFLqMQboID){EpScTNcWyM = true;}
      if(dPWnxYbimG == axtxbUAZZR){nBfZnLYPme = true;}
      else if(axtxbUAZZR == dPWnxYbimG){cbQmrQuyLF = true;}
      if(qkRnqOyeIz == ZXUgUXkbTc){yPbneKpGBi = true;}
      else if(ZXUgUXkbTc == qkRnqOyeIz){tYnSbIzKyP = true;}
      if(iXhiKhMUCs == DwjYuQZdRY){lRbSnErfCV = true;}
      else if(DwjYuQZdRY == iXhiKhMUCs){aIPNuRRQtP = true;}
      if(NKyaKosBhB == DidkVwtXcF){CRXGYdDFMm = true;}
      else if(DidkVwtXcF == NKyaKosBhB){SFCMqesGJC = true;}
      if(QfrXOMnWAx == OEPmdhjpyQ){GpoasTxgmA = true;}
      else if(OEPmdhjpyQ == QfrXOMnWAx){RGWAHfCAAK = true;}
      if(RxfIUGhndO == YXcBeeMVBK){BoMoBWZNli = true;}
      else if(YXcBeeMVBK == RxfIUGhndO){ORYhkTMDqa = true;}
      if(MGftsglpcC == tWHBOqtiKX){TrMRcfqUPA = true;}
      if(VxwGiCfJTx == cNyNOzfxtN){HktOcwbAYT = true;}
      if(toUEaPdoFE == fifAzeFbGq){HKsCTMFiFB = true;}
      while(tWHBOqtiKX == MGftsglpcC){zdDwloWabx = true;}
      while(cNyNOzfxtN == cNyNOzfxtN){OrAuyTkOGP = true;}
      while(fifAzeFbGq == fifAzeFbGq){PQQjBBfTaW = true;}
      if(jYVRLrwOYm == true){jYVRLrwOYm = false;}
      if(nBfZnLYPme == true){nBfZnLYPme = false;}
      if(yPbneKpGBi == true){yPbneKpGBi = false;}
      if(lRbSnErfCV == true){lRbSnErfCV = false;}
      if(CRXGYdDFMm == true){CRXGYdDFMm = false;}
      if(GpoasTxgmA == true){GpoasTxgmA = false;}
      if(BoMoBWZNli == true){BoMoBWZNli = false;}
      if(TrMRcfqUPA == true){TrMRcfqUPA = false;}
      if(HktOcwbAYT == true){HktOcwbAYT = false;}
      if(HKsCTMFiFB == true){HKsCTMFiFB = false;}
      if(EpScTNcWyM == true){EpScTNcWyM = false;}
      if(cbQmrQuyLF == true){cbQmrQuyLF = false;}
      if(tYnSbIzKyP == true){tYnSbIzKyP = false;}
      if(aIPNuRRQtP == true){aIPNuRRQtP = false;}
      if(SFCMqesGJC == true){SFCMqesGJC = false;}
      if(RGWAHfCAAK == true){RGWAHfCAAK = false;}
      if(ORYhkTMDqa == true){ORYhkTMDqa = false;}
      if(zdDwloWabx == true){zdDwloWabx = false;}
      if(OrAuyTkOGP == true){OrAuyTkOGP = false;}
      if(PQQjBBfTaW == true){PQQjBBfTaW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SXTTQLROXR
{ 
  void sfhsLkeeBZ()
  { 
      bool FfrhcRVDre = false;
      bool FxFXUNLudm = false;
      bool bODXVPzdZs = false;
      bool ryEHGJjCrS = false;
      bool MJZWBWbmcy = false;
      bool xXOKkpcULN = false;
      bool RrdzmGrxQK = false;
      bool dICKZRofVz = false;
      bool mMBawTjtWP = false;
      bool fPqeBTfaiu = false;
      bool eeVRUnUDjT = false;
      bool BwyMZFqCCS = false;
      bool VxaBdNQXJF = false;
      bool kOxZUIpjGH = false;
      bool yfJDOjRdFu = false;
      bool cdXPYgDUmH = false;
      bool XxsdhmzXrR = false;
      bool OHutUpnXlt = false;
      bool ulSOcHpgBm = false;
      bool EUwyjAlfUa = false;
      string qruPJccIiX;
      string lmexWVAZTO;
      string PJhQeITrjw;
      string GpFkdqMrhp;
      string SDVSjdRPOs;
      string AwqWOhJekA;
      string JjYmQuhtSf;
      string IIqcuLmOgB;
      string qEdquKyhWw;
      string ghHhfiehBn;
      string wWwijrFNaC;
      string ttxjJFGhqG;
      string wzWWyZAIwM;
      string fENsETHuGD;
      string EkHTBlkXXa;
      string cxqtqxzZjJ;
      string qwQNVogEep;
      string xKamCLrCUL;
      string ockVjiNSBH;
      string ThLxMITsxM;
      if(qruPJccIiX == wWwijrFNaC){FfrhcRVDre = true;}
      else if(wWwijrFNaC == qruPJccIiX){eeVRUnUDjT = true;}
      if(lmexWVAZTO == ttxjJFGhqG){FxFXUNLudm = true;}
      else if(ttxjJFGhqG == lmexWVAZTO){BwyMZFqCCS = true;}
      if(PJhQeITrjw == wzWWyZAIwM){bODXVPzdZs = true;}
      else if(wzWWyZAIwM == PJhQeITrjw){VxaBdNQXJF = true;}
      if(GpFkdqMrhp == fENsETHuGD){ryEHGJjCrS = true;}
      else if(fENsETHuGD == GpFkdqMrhp){kOxZUIpjGH = true;}
      if(SDVSjdRPOs == EkHTBlkXXa){MJZWBWbmcy = true;}
      else if(EkHTBlkXXa == SDVSjdRPOs){yfJDOjRdFu = true;}
      if(AwqWOhJekA == cxqtqxzZjJ){xXOKkpcULN = true;}
      else if(cxqtqxzZjJ == AwqWOhJekA){cdXPYgDUmH = true;}
      if(JjYmQuhtSf == qwQNVogEep){RrdzmGrxQK = true;}
      else if(qwQNVogEep == JjYmQuhtSf){XxsdhmzXrR = true;}
      if(IIqcuLmOgB == xKamCLrCUL){dICKZRofVz = true;}
      if(qEdquKyhWw == ockVjiNSBH){mMBawTjtWP = true;}
      if(ghHhfiehBn == ThLxMITsxM){fPqeBTfaiu = true;}
      while(xKamCLrCUL == IIqcuLmOgB){OHutUpnXlt = true;}
      while(ockVjiNSBH == ockVjiNSBH){ulSOcHpgBm = true;}
      while(ThLxMITsxM == ThLxMITsxM){EUwyjAlfUa = true;}
      if(FfrhcRVDre == true){FfrhcRVDre = false;}
      if(FxFXUNLudm == true){FxFXUNLudm = false;}
      if(bODXVPzdZs == true){bODXVPzdZs = false;}
      if(ryEHGJjCrS == true){ryEHGJjCrS = false;}
      if(MJZWBWbmcy == true){MJZWBWbmcy = false;}
      if(xXOKkpcULN == true){xXOKkpcULN = false;}
      if(RrdzmGrxQK == true){RrdzmGrxQK = false;}
      if(dICKZRofVz == true){dICKZRofVz = false;}
      if(mMBawTjtWP == true){mMBawTjtWP = false;}
      if(fPqeBTfaiu == true){fPqeBTfaiu = false;}
      if(eeVRUnUDjT == true){eeVRUnUDjT = false;}
      if(BwyMZFqCCS == true){BwyMZFqCCS = false;}
      if(VxaBdNQXJF == true){VxaBdNQXJF = false;}
      if(kOxZUIpjGH == true){kOxZUIpjGH = false;}
      if(yfJDOjRdFu == true){yfJDOjRdFu = false;}
      if(cdXPYgDUmH == true){cdXPYgDUmH = false;}
      if(XxsdhmzXrR == true){XxsdhmzXrR = false;}
      if(OHutUpnXlt == true){OHutUpnXlt = false;}
      if(ulSOcHpgBm == true){ulSOcHpgBm = false;}
      if(EUwyjAlfUa == true){EUwyjAlfUa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ETKLPUZNAK
{ 
  void ORMhdrLapi()
  { 
      bool GgUUqRICUg = false;
      bool MgleKEqeWI = false;
      bool mFSCLYAMqe = false;
      bool oHGKOnATLH = false;
      bool rrWhfHWlFk = false;
      bool ixunZAOSJR = false;
      bool QwKorEZbQW = false;
      bool DWSOPthjWE = false;
      bool COGGuqMSjN = false;
      bool YhKtqwhgpa = false;
      bool gtVigMefXe = false;
      bool ReuFPBoDtA = false;
      bool rGqCxUMYXT = false;
      bool MBsuWHrXZi = false;
      bool MftFutmEeo = false;
      bool GdmohaDTkL = false;
      bool zFIDRQkziH = false;
      bool JRdKnMLkGD = false;
      bool hHthNhODNw = false;
      bool EYlNiGXqme = false;
      string uOFMJGnQpr;
      string nLBQbwrgfc;
      string sTwSjUHKcP;
      string kmEqkjyRfa;
      string zxHscgDJRO;
      string moQjqaRlbo;
      string zdmZHAHJeq;
      string xaAEdwMDpD;
      string RxrObuWTAK;
      string RLoqaUJglb;
      string YsdZRMoLFu;
      string OOwYWBkYxL;
      string cmITYklIcJ;
      string leRNdXTSwP;
      string GLOFwDPPTZ;
      string jkjZykjKAf;
      string afhwIixhuz;
      string hSbgFRYDXV;
      string VVoDYAuqPr;
      string nIRPoZcRwN;
      if(uOFMJGnQpr == YsdZRMoLFu){GgUUqRICUg = true;}
      else if(YsdZRMoLFu == uOFMJGnQpr){gtVigMefXe = true;}
      if(nLBQbwrgfc == OOwYWBkYxL){MgleKEqeWI = true;}
      else if(OOwYWBkYxL == nLBQbwrgfc){ReuFPBoDtA = true;}
      if(sTwSjUHKcP == cmITYklIcJ){mFSCLYAMqe = true;}
      else if(cmITYklIcJ == sTwSjUHKcP){rGqCxUMYXT = true;}
      if(kmEqkjyRfa == leRNdXTSwP){oHGKOnATLH = true;}
      else if(leRNdXTSwP == kmEqkjyRfa){MBsuWHrXZi = true;}
      if(zxHscgDJRO == GLOFwDPPTZ){rrWhfHWlFk = true;}
      else if(GLOFwDPPTZ == zxHscgDJRO){MftFutmEeo = true;}
      if(moQjqaRlbo == jkjZykjKAf){ixunZAOSJR = true;}
      else if(jkjZykjKAf == moQjqaRlbo){GdmohaDTkL = true;}
      if(zdmZHAHJeq == afhwIixhuz){QwKorEZbQW = true;}
      else if(afhwIixhuz == zdmZHAHJeq){zFIDRQkziH = true;}
      if(xaAEdwMDpD == hSbgFRYDXV){DWSOPthjWE = true;}
      if(RxrObuWTAK == VVoDYAuqPr){COGGuqMSjN = true;}
      if(RLoqaUJglb == nIRPoZcRwN){YhKtqwhgpa = true;}
      while(hSbgFRYDXV == xaAEdwMDpD){JRdKnMLkGD = true;}
      while(VVoDYAuqPr == VVoDYAuqPr){hHthNhODNw = true;}
      while(nIRPoZcRwN == nIRPoZcRwN){EYlNiGXqme = true;}
      if(GgUUqRICUg == true){GgUUqRICUg = false;}
      if(MgleKEqeWI == true){MgleKEqeWI = false;}
      if(mFSCLYAMqe == true){mFSCLYAMqe = false;}
      if(oHGKOnATLH == true){oHGKOnATLH = false;}
      if(rrWhfHWlFk == true){rrWhfHWlFk = false;}
      if(ixunZAOSJR == true){ixunZAOSJR = false;}
      if(QwKorEZbQW == true){QwKorEZbQW = false;}
      if(DWSOPthjWE == true){DWSOPthjWE = false;}
      if(COGGuqMSjN == true){COGGuqMSjN = false;}
      if(YhKtqwhgpa == true){YhKtqwhgpa = false;}
      if(gtVigMefXe == true){gtVigMefXe = false;}
      if(ReuFPBoDtA == true){ReuFPBoDtA = false;}
      if(rGqCxUMYXT == true){rGqCxUMYXT = false;}
      if(MBsuWHrXZi == true){MBsuWHrXZi = false;}
      if(MftFutmEeo == true){MftFutmEeo = false;}
      if(GdmohaDTkL == true){GdmohaDTkL = false;}
      if(zFIDRQkziH == true){zFIDRQkziH = false;}
      if(JRdKnMLkGD == true){JRdKnMLkGD = false;}
      if(hHthNhODNw == true){hHthNhODNw = false;}
      if(EYlNiGXqme == true){EYlNiGXqme = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DKAHPWFZNN
{ 
  void yjXedhnaHz()
  { 
      bool dkbpYKdapF = false;
      bool XhIbKbCLLk = false;
      bool nTgJgQYjCT = false;
      bool jbrrnrTbNp = false;
      bool ryxJSixqwV = false;
      bool QFauhKERJH = false;
      bool ktXWVwpQnR = false;
      bool HZxUroWWqy = false;
      bool ShmgCdAwJd = false;
      bool nBSFEyaanW = false;
      bool rfCeOpHFCr = false;
      bool nhaKnCGpTq = false;
      bool usGKcFHrPs = false;
      bool OuhUFleISM = false;
      bool WusQpGaHQC = false;
      bool rjGwayZrBI = false;
      bool hPoJdrzGFB = false;
      bool XyXHUAApUW = false;
      bool eAaNBeolsG = false;
      bool MmGJdGFjmx = false;
      string oGlupJrxVF;
      string KMAzUcdCWl;
      string xeNYuWLaMk;
      string OBnuGEODgs;
      string ZthseVbNOO;
      string UyHaEJsMAS;
      string yRkkpIYFsP;
      string NaVcLCwTsY;
      string uxLxPQsMqw;
      string LBDNuIJwCV;
      string xVUyAtceOB;
      string MYTbXAFnVZ;
      string PLOxEMWHgD;
      string sAQWbYcNwU;
      string mOyoilhbou;
      string CVacGkHWtn;
      string WUxLIMIwzy;
      string WrqAlANYNR;
      string duSlAWYnPp;
      string RGSHxSQlgV;
      if(oGlupJrxVF == xVUyAtceOB){dkbpYKdapF = true;}
      else if(xVUyAtceOB == oGlupJrxVF){rfCeOpHFCr = true;}
      if(KMAzUcdCWl == MYTbXAFnVZ){XhIbKbCLLk = true;}
      else if(MYTbXAFnVZ == KMAzUcdCWl){nhaKnCGpTq = true;}
      if(xeNYuWLaMk == PLOxEMWHgD){nTgJgQYjCT = true;}
      else if(PLOxEMWHgD == xeNYuWLaMk){usGKcFHrPs = true;}
      if(OBnuGEODgs == sAQWbYcNwU){jbrrnrTbNp = true;}
      else if(sAQWbYcNwU == OBnuGEODgs){OuhUFleISM = true;}
      if(ZthseVbNOO == mOyoilhbou){ryxJSixqwV = true;}
      else if(mOyoilhbou == ZthseVbNOO){WusQpGaHQC = true;}
      if(UyHaEJsMAS == CVacGkHWtn){QFauhKERJH = true;}
      else if(CVacGkHWtn == UyHaEJsMAS){rjGwayZrBI = true;}
      if(yRkkpIYFsP == WUxLIMIwzy){ktXWVwpQnR = true;}
      else if(WUxLIMIwzy == yRkkpIYFsP){hPoJdrzGFB = true;}
      if(NaVcLCwTsY == WrqAlANYNR){HZxUroWWqy = true;}
      if(uxLxPQsMqw == duSlAWYnPp){ShmgCdAwJd = true;}
      if(LBDNuIJwCV == RGSHxSQlgV){nBSFEyaanW = true;}
      while(WrqAlANYNR == NaVcLCwTsY){XyXHUAApUW = true;}
      while(duSlAWYnPp == duSlAWYnPp){eAaNBeolsG = true;}
      while(RGSHxSQlgV == RGSHxSQlgV){MmGJdGFjmx = true;}
      if(dkbpYKdapF == true){dkbpYKdapF = false;}
      if(XhIbKbCLLk == true){XhIbKbCLLk = false;}
      if(nTgJgQYjCT == true){nTgJgQYjCT = false;}
      if(jbrrnrTbNp == true){jbrrnrTbNp = false;}
      if(ryxJSixqwV == true){ryxJSixqwV = false;}
      if(QFauhKERJH == true){QFauhKERJH = false;}
      if(ktXWVwpQnR == true){ktXWVwpQnR = false;}
      if(HZxUroWWqy == true){HZxUroWWqy = false;}
      if(ShmgCdAwJd == true){ShmgCdAwJd = false;}
      if(nBSFEyaanW == true){nBSFEyaanW = false;}
      if(rfCeOpHFCr == true){rfCeOpHFCr = false;}
      if(nhaKnCGpTq == true){nhaKnCGpTq = false;}
      if(usGKcFHrPs == true){usGKcFHrPs = false;}
      if(OuhUFleISM == true){OuhUFleISM = false;}
      if(WusQpGaHQC == true){WusQpGaHQC = false;}
      if(rjGwayZrBI == true){rjGwayZrBI = false;}
      if(hPoJdrzGFB == true){hPoJdrzGFB = false;}
      if(XyXHUAApUW == true){XyXHUAApUW = false;}
      if(eAaNBeolsG == true){eAaNBeolsG = false;}
      if(MmGJdGFjmx == true){MmGJdGFjmx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CEJPQKCXBK
{ 
  void rDFfJQdyzx()
  { 
      bool XMfkBUdrOA = false;
      bool XztXCRHTEO = false;
      bool AaVSORNXqk = false;
      bool oJujLhiyTJ = false;
      bool XZHgndMbSg = false;
      bool yEAZoxqNVj = false;
      bool HGAcKOEKLU = false;
      bool iJzuqZSoek = false;
      bool FlEKmkJUuO = false;
      bool qVbjBRZdVZ = false;
      bool YBPyxnEEhO = false;
      bool dChkeUBppZ = false;
      bool EiPxdNhPsZ = false;
      bool AnSELDVFMy = false;
      bool fFlfjnmqFg = false;
      bool PinuUplSUj = false;
      bool GnKINoidYa = false;
      bool zudrszxiMo = false;
      bool ZpKMJQAXiV = false;
      bool QDkbqrtdRt = false;
      string yBboiMiAWk;
      string ZcmOxTdPPK;
      string oWEuStmpJM;
      string wBqBEsuMVx;
      string wcQhMbKLSh;
      string XwDJEaxgVn;
      string YrpKnXklKD;
      string YQsSOMGWiq;
      string jaXbnAxhwc;
      string wNpgXDlFtn;
      string pXBOIHDjtq;
      string TZxeEyUNWn;
      string ZDohGKZMuL;
      string aBcuALZITf;
      string wMnFIVPKcZ;
      string hYhFNmiTIx;
      string gqoiQSxCer;
      string XMtpqMOiYj;
      string uOiVdBSWgM;
      string cGzVzFXFno;
      if(yBboiMiAWk == pXBOIHDjtq){XMfkBUdrOA = true;}
      else if(pXBOIHDjtq == yBboiMiAWk){YBPyxnEEhO = true;}
      if(ZcmOxTdPPK == TZxeEyUNWn){XztXCRHTEO = true;}
      else if(TZxeEyUNWn == ZcmOxTdPPK){dChkeUBppZ = true;}
      if(oWEuStmpJM == ZDohGKZMuL){AaVSORNXqk = true;}
      else if(ZDohGKZMuL == oWEuStmpJM){EiPxdNhPsZ = true;}
      if(wBqBEsuMVx == aBcuALZITf){oJujLhiyTJ = true;}
      else if(aBcuALZITf == wBqBEsuMVx){AnSELDVFMy = true;}
      if(wcQhMbKLSh == wMnFIVPKcZ){XZHgndMbSg = true;}
      else if(wMnFIVPKcZ == wcQhMbKLSh){fFlfjnmqFg = true;}
      if(XwDJEaxgVn == hYhFNmiTIx){yEAZoxqNVj = true;}
      else if(hYhFNmiTIx == XwDJEaxgVn){PinuUplSUj = true;}
      if(YrpKnXklKD == gqoiQSxCer){HGAcKOEKLU = true;}
      else if(gqoiQSxCer == YrpKnXklKD){GnKINoidYa = true;}
      if(YQsSOMGWiq == XMtpqMOiYj){iJzuqZSoek = true;}
      if(jaXbnAxhwc == uOiVdBSWgM){FlEKmkJUuO = true;}
      if(wNpgXDlFtn == cGzVzFXFno){qVbjBRZdVZ = true;}
      while(XMtpqMOiYj == YQsSOMGWiq){zudrszxiMo = true;}
      while(uOiVdBSWgM == uOiVdBSWgM){ZpKMJQAXiV = true;}
      while(cGzVzFXFno == cGzVzFXFno){QDkbqrtdRt = true;}
      if(XMfkBUdrOA == true){XMfkBUdrOA = false;}
      if(XztXCRHTEO == true){XztXCRHTEO = false;}
      if(AaVSORNXqk == true){AaVSORNXqk = false;}
      if(oJujLhiyTJ == true){oJujLhiyTJ = false;}
      if(XZHgndMbSg == true){XZHgndMbSg = false;}
      if(yEAZoxqNVj == true){yEAZoxqNVj = false;}
      if(HGAcKOEKLU == true){HGAcKOEKLU = false;}
      if(iJzuqZSoek == true){iJzuqZSoek = false;}
      if(FlEKmkJUuO == true){FlEKmkJUuO = false;}
      if(qVbjBRZdVZ == true){qVbjBRZdVZ = false;}
      if(YBPyxnEEhO == true){YBPyxnEEhO = false;}
      if(dChkeUBppZ == true){dChkeUBppZ = false;}
      if(EiPxdNhPsZ == true){EiPxdNhPsZ = false;}
      if(AnSELDVFMy == true){AnSELDVFMy = false;}
      if(fFlfjnmqFg == true){fFlfjnmqFg = false;}
      if(PinuUplSUj == true){PinuUplSUj = false;}
      if(GnKINoidYa == true){GnKINoidYa = false;}
      if(zudrszxiMo == true){zudrszxiMo = false;}
      if(ZpKMJQAXiV == true){ZpKMJQAXiV = false;}
      if(QDkbqrtdRt == true){QDkbqrtdRt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FBXKGIHLZJ
{ 
  void aKwwbzwdyJ()
  { 
      bool AGPnlWXgtF = false;
      bool mfgYXGsBXL = false;
      bool KJVePpeAKI = false;
      bool dhnAORAGxP = false;
      bool rjiKjHLTqj = false;
      bool dTOJupjjYu = false;
      bool qXWkaFrgJG = false;
      bool FlDHTaaLuI = false;
      bool eLJZeKTdEY = false;
      bool gPhBXUNxje = false;
      bool OdJkeqPGpU = false;
      bool PYoPQfNwGP = false;
      bool lNbkYoECjz = false;
      bool NcaQsABYum = false;
      bool uMnjIIaRkq = false;
      bool GQpTrBCYMo = false;
      bool lNWqGlxYWP = false;
      bool eoATUYZqbP = false;
      bool NmQrrwlHXr = false;
      bool ycMFAhpwdW = false;
      string KmcQWYRJtK;
      string hIPtbDWAHy;
      string lgXqeMusGK;
      string deFdptlmkP;
      string URhzMbjiXf;
      string pphSAcPklK;
      string cYCifCDkDg;
      string RjOqcTzXeD;
      string cMVZTnxldM;
      string eAAalwPySJ;
      string XyepOGbppf;
      string dqGhhQCbPr;
      string FQHpCRimFf;
      string EAEUedgfLN;
      string LGwximsSrV;
      string sniaEHpnmw;
      string WnkJbcmlCD;
      string iWPBfzTJGO;
      string YQujlPRcPX;
      string nrrOpXUlVG;
      if(KmcQWYRJtK == XyepOGbppf){AGPnlWXgtF = true;}
      else if(XyepOGbppf == KmcQWYRJtK){OdJkeqPGpU = true;}
      if(hIPtbDWAHy == dqGhhQCbPr){mfgYXGsBXL = true;}
      else if(dqGhhQCbPr == hIPtbDWAHy){PYoPQfNwGP = true;}
      if(lgXqeMusGK == FQHpCRimFf){KJVePpeAKI = true;}
      else if(FQHpCRimFf == lgXqeMusGK){lNbkYoECjz = true;}
      if(deFdptlmkP == EAEUedgfLN){dhnAORAGxP = true;}
      else if(EAEUedgfLN == deFdptlmkP){NcaQsABYum = true;}
      if(URhzMbjiXf == LGwximsSrV){rjiKjHLTqj = true;}
      else if(LGwximsSrV == URhzMbjiXf){uMnjIIaRkq = true;}
      if(pphSAcPklK == sniaEHpnmw){dTOJupjjYu = true;}
      else if(sniaEHpnmw == pphSAcPklK){GQpTrBCYMo = true;}
      if(cYCifCDkDg == WnkJbcmlCD){qXWkaFrgJG = true;}
      else if(WnkJbcmlCD == cYCifCDkDg){lNWqGlxYWP = true;}
      if(RjOqcTzXeD == iWPBfzTJGO){FlDHTaaLuI = true;}
      if(cMVZTnxldM == YQujlPRcPX){eLJZeKTdEY = true;}
      if(eAAalwPySJ == nrrOpXUlVG){gPhBXUNxje = true;}
      while(iWPBfzTJGO == RjOqcTzXeD){eoATUYZqbP = true;}
      while(YQujlPRcPX == YQujlPRcPX){NmQrrwlHXr = true;}
      while(nrrOpXUlVG == nrrOpXUlVG){ycMFAhpwdW = true;}
      if(AGPnlWXgtF == true){AGPnlWXgtF = false;}
      if(mfgYXGsBXL == true){mfgYXGsBXL = false;}
      if(KJVePpeAKI == true){KJVePpeAKI = false;}
      if(dhnAORAGxP == true){dhnAORAGxP = false;}
      if(rjiKjHLTqj == true){rjiKjHLTqj = false;}
      if(dTOJupjjYu == true){dTOJupjjYu = false;}
      if(qXWkaFrgJG == true){qXWkaFrgJG = false;}
      if(FlDHTaaLuI == true){FlDHTaaLuI = false;}
      if(eLJZeKTdEY == true){eLJZeKTdEY = false;}
      if(gPhBXUNxje == true){gPhBXUNxje = false;}
      if(OdJkeqPGpU == true){OdJkeqPGpU = false;}
      if(PYoPQfNwGP == true){PYoPQfNwGP = false;}
      if(lNbkYoECjz == true){lNbkYoECjz = false;}
      if(NcaQsABYum == true){NcaQsABYum = false;}
      if(uMnjIIaRkq == true){uMnjIIaRkq = false;}
      if(GQpTrBCYMo == true){GQpTrBCYMo = false;}
      if(lNWqGlxYWP == true){lNWqGlxYWP = false;}
      if(eoATUYZqbP == true){eoATUYZqbP = false;}
      if(NmQrrwlHXr == true){NmQrrwlHXr = false;}
      if(ycMFAhpwdW == true){ycMFAhpwdW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUFVJILFTQ
{ 
  void KkhdBECmml()
  { 
      bool IllrdunYsF = false;
      bool HWEIzkQhuc = false;
      bool UJECOGJqSs = false;
      bool FsqYxwAJSZ = false;
      bool xdkQuuOwqg = false;
      bool poGaMygidX = false;
      bool lxGAzNefLD = false;
      bool jGOUfpYnHS = false;
      bool qMzkDQmQMy = false;
      bool ORfunAXkQg = false;
      bool QhknwjZkuV = false;
      bool ZsaKfYxUwi = false;
      bool aNTNoSZTge = false;
      bool SmXaBIbLoT = false;
      bool pBVpXUpUOP = false;
      bool CCngFCOXyd = false;
      bool JGEPClVAJX = false;
      bool wlfbsYrcoT = false;
      bool bEEQcQzpUy = false;
      bool tDMKKixFnk = false;
      string oGkJwaXXyU;
      string oVMaYUUtXg;
      string cFCqZKVHNd;
      string danEZNjmcM;
      string HnGKaApWZM;
      string jLqWMjEtjl;
      string EPJUqNgHAK;
      string jgRKYnyqQY;
      string TzhBsRiRrp;
      string JpCqIrekSM;
      string ShVObCsgxX;
      string kMdLREhHbY;
      string ePPKBtdaBf;
      string JMYDFkdSYp;
      string YCTTEwMqYE;
      string KWJthDSKNh;
      string XSeROXnZFg;
      string ZOikAbuwFF;
      string hmCxVlDeVC;
      string STFqSGWCEg;
      if(oGkJwaXXyU == ShVObCsgxX){IllrdunYsF = true;}
      else if(ShVObCsgxX == oGkJwaXXyU){QhknwjZkuV = true;}
      if(oVMaYUUtXg == kMdLREhHbY){HWEIzkQhuc = true;}
      else if(kMdLREhHbY == oVMaYUUtXg){ZsaKfYxUwi = true;}
      if(cFCqZKVHNd == ePPKBtdaBf){UJECOGJqSs = true;}
      else if(ePPKBtdaBf == cFCqZKVHNd){aNTNoSZTge = true;}
      if(danEZNjmcM == JMYDFkdSYp){FsqYxwAJSZ = true;}
      else if(JMYDFkdSYp == danEZNjmcM){SmXaBIbLoT = true;}
      if(HnGKaApWZM == YCTTEwMqYE){xdkQuuOwqg = true;}
      else if(YCTTEwMqYE == HnGKaApWZM){pBVpXUpUOP = true;}
      if(jLqWMjEtjl == KWJthDSKNh){poGaMygidX = true;}
      else if(KWJthDSKNh == jLqWMjEtjl){CCngFCOXyd = true;}
      if(EPJUqNgHAK == XSeROXnZFg){lxGAzNefLD = true;}
      else if(XSeROXnZFg == EPJUqNgHAK){JGEPClVAJX = true;}
      if(jgRKYnyqQY == ZOikAbuwFF){jGOUfpYnHS = true;}
      if(TzhBsRiRrp == hmCxVlDeVC){qMzkDQmQMy = true;}
      if(JpCqIrekSM == STFqSGWCEg){ORfunAXkQg = true;}
      while(ZOikAbuwFF == jgRKYnyqQY){wlfbsYrcoT = true;}
      while(hmCxVlDeVC == hmCxVlDeVC){bEEQcQzpUy = true;}
      while(STFqSGWCEg == STFqSGWCEg){tDMKKixFnk = true;}
      if(IllrdunYsF == true){IllrdunYsF = false;}
      if(HWEIzkQhuc == true){HWEIzkQhuc = false;}
      if(UJECOGJqSs == true){UJECOGJqSs = false;}
      if(FsqYxwAJSZ == true){FsqYxwAJSZ = false;}
      if(xdkQuuOwqg == true){xdkQuuOwqg = false;}
      if(poGaMygidX == true){poGaMygidX = false;}
      if(lxGAzNefLD == true){lxGAzNefLD = false;}
      if(jGOUfpYnHS == true){jGOUfpYnHS = false;}
      if(qMzkDQmQMy == true){qMzkDQmQMy = false;}
      if(ORfunAXkQg == true){ORfunAXkQg = false;}
      if(QhknwjZkuV == true){QhknwjZkuV = false;}
      if(ZsaKfYxUwi == true){ZsaKfYxUwi = false;}
      if(aNTNoSZTge == true){aNTNoSZTge = false;}
      if(SmXaBIbLoT == true){SmXaBIbLoT = false;}
      if(pBVpXUpUOP == true){pBVpXUpUOP = false;}
      if(CCngFCOXyd == true){CCngFCOXyd = false;}
      if(JGEPClVAJX == true){JGEPClVAJX = false;}
      if(wlfbsYrcoT == true){wlfbsYrcoT = false;}
      if(bEEQcQzpUy == true){bEEQcQzpUy = false;}
      if(tDMKKixFnk == true){tDMKKixFnk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JRIEASHXYA
{ 
  void UbXCPWEkVb()
  { 
      bool zhFOCVgYYx = false;
      bool fxICWjQUCb = false;
      bool kibUAwDsza = false;
      bool dhZGRmjTCC = false;
      bool qKuNNVryCs = false;
      bool gQqKNPGjOF = false;
      bool RmYySyXCjj = false;
      bool zwRzjanOGd = false;
      bool EEqGsMpOrB = false;
      bool gAFwkEkwtP = false;
      bool yoOSsjzrZm = false;
      bool bqdjBNwSFF = false;
      bool HIJhCzqUOf = false;
      bool oqTpfOpYNI = false;
      bool NynFZoVUuW = false;
      bool HSqnIoefPs = false;
      bool sdctxjXnDl = false;
      bool WXEwrITDIM = false;
      bool dVYqXVzegq = false;
      bool jKITOiVtHp = false;
      string zDumzNdGkR;
      string yREGcmISuj;
      string iWtTLMwtQR;
      string ehWrEhLNUd;
      string jZCHEBWqjM;
      string ePtagbIbbm;
      string RjoTlPtLCt;
      string buyQzIUmOJ;
      string oEKDmOnwLb;
      string YilgMAkhUo;
      string GKookiQcaX;
      string HVMRyMZkfW;
      string ayAZUrJREz;
      string XlRYCdPUSD;
      string yKVmUDVTiz;
      string ZzCyNIKOTs;
      string ZzYaAUDnOT;
      string xEScYQbMFR;
      string VoiEYXjTLt;
      string TABZcyltmz;
      if(zDumzNdGkR == GKookiQcaX){zhFOCVgYYx = true;}
      else if(GKookiQcaX == zDumzNdGkR){yoOSsjzrZm = true;}
      if(yREGcmISuj == HVMRyMZkfW){fxICWjQUCb = true;}
      else if(HVMRyMZkfW == yREGcmISuj){bqdjBNwSFF = true;}
      if(iWtTLMwtQR == ayAZUrJREz){kibUAwDsza = true;}
      else if(ayAZUrJREz == iWtTLMwtQR){HIJhCzqUOf = true;}
      if(ehWrEhLNUd == XlRYCdPUSD){dhZGRmjTCC = true;}
      else if(XlRYCdPUSD == ehWrEhLNUd){oqTpfOpYNI = true;}
      if(jZCHEBWqjM == yKVmUDVTiz){qKuNNVryCs = true;}
      else if(yKVmUDVTiz == jZCHEBWqjM){NynFZoVUuW = true;}
      if(ePtagbIbbm == ZzCyNIKOTs){gQqKNPGjOF = true;}
      else if(ZzCyNIKOTs == ePtagbIbbm){HSqnIoefPs = true;}
      if(RjoTlPtLCt == ZzYaAUDnOT){RmYySyXCjj = true;}
      else if(ZzYaAUDnOT == RjoTlPtLCt){sdctxjXnDl = true;}
      if(buyQzIUmOJ == xEScYQbMFR){zwRzjanOGd = true;}
      if(oEKDmOnwLb == VoiEYXjTLt){EEqGsMpOrB = true;}
      if(YilgMAkhUo == TABZcyltmz){gAFwkEkwtP = true;}
      while(xEScYQbMFR == buyQzIUmOJ){WXEwrITDIM = true;}
      while(VoiEYXjTLt == VoiEYXjTLt){dVYqXVzegq = true;}
      while(TABZcyltmz == TABZcyltmz){jKITOiVtHp = true;}
      if(zhFOCVgYYx == true){zhFOCVgYYx = false;}
      if(fxICWjQUCb == true){fxICWjQUCb = false;}
      if(kibUAwDsza == true){kibUAwDsza = false;}
      if(dhZGRmjTCC == true){dhZGRmjTCC = false;}
      if(qKuNNVryCs == true){qKuNNVryCs = false;}
      if(gQqKNPGjOF == true){gQqKNPGjOF = false;}
      if(RmYySyXCjj == true){RmYySyXCjj = false;}
      if(zwRzjanOGd == true){zwRzjanOGd = false;}
      if(EEqGsMpOrB == true){EEqGsMpOrB = false;}
      if(gAFwkEkwtP == true){gAFwkEkwtP = false;}
      if(yoOSsjzrZm == true){yoOSsjzrZm = false;}
      if(bqdjBNwSFF == true){bqdjBNwSFF = false;}
      if(HIJhCzqUOf == true){HIJhCzqUOf = false;}
      if(oqTpfOpYNI == true){oqTpfOpYNI = false;}
      if(NynFZoVUuW == true){NynFZoVUuW = false;}
      if(HSqnIoefPs == true){HSqnIoefPs = false;}
      if(sdctxjXnDl == true){sdctxjXnDl = false;}
      if(WXEwrITDIM == true){WXEwrITDIM = false;}
      if(dVYqXVzegq == true){dVYqXVzegq = false;}
      if(jKITOiVtHp == true){jKITOiVtHp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LCIDEPOCFR
{ 
  void LdCBCcbpMD()
  { 
      bool IKlpntbOxk = false;
      bool Yhgliuxdqr = false;
      bool CRjsDkPtZQ = false;
      bool ZdxpaSyKfX = false;
      bool GXDJwHPIUZ = false;
      bool KXiFcpZslD = false;
      bool dhogKtjqLQ = false;
      bool xmxSkdNaww = false;
      bool UHZAGCurMj = false;
      bool rFYbtYiWyC = false;
      bool XXxDcXZQTy = false;
      bool czwpiWInaI = false;
      bool zrdaXqNUYL = false;
      bool tqbsYwJVWi = false;
      bool cdXOHsIhsW = false;
      bool QuwpCesVfk = false;
      bool JEqHDlWCRl = false;
      bool MlQqfUTPTd = false;
      bool ifbBuztlqs = false;
      bool CmplZYlQLV = false;
      string abkTXRpgAt;
      string CKZFWCtOjO;
      string AeHDnsnOVj;
      string ShEuFpIsdj;
      string IAXeIXbtPY;
      string RXpmjuUgee;
      string daLPaTFeAg;
      string tAkzFzGbuQ;
      string QtzwStqRKJ;
      string UaOyGgoIDn;
      string RxsheQlqhk;
      string nrlNNibOxg;
      string bnTpMSkmrX;
      string JyYGzTAQQB;
      string HAjYVcoAkX;
      string FZKWMccCVM;
      string fzyJbpTeOt;
      string iKyuYaEuUi;
      string cjBUSimBtV;
      string pxuDVIBZxe;
      if(abkTXRpgAt == RxsheQlqhk){IKlpntbOxk = true;}
      else if(RxsheQlqhk == abkTXRpgAt){XXxDcXZQTy = true;}
      if(CKZFWCtOjO == nrlNNibOxg){Yhgliuxdqr = true;}
      else if(nrlNNibOxg == CKZFWCtOjO){czwpiWInaI = true;}
      if(AeHDnsnOVj == bnTpMSkmrX){CRjsDkPtZQ = true;}
      else if(bnTpMSkmrX == AeHDnsnOVj){zrdaXqNUYL = true;}
      if(ShEuFpIsdj == JyYGzTAQQB){ZdxpaSyKfX = true;}
      else if(JyYGzTAQQB == ShEuFpIsdj){tqbsYwJVWi = true;}
      if(IAXeIXbtPY == HAjYVcoAkX){GXDJwHPIUZ = true;}
      else if(HAjYVcoAkX == IAXeIXbtPY){cdXOHsIhsW = true;}
      if(RXpmjuUgee == FZKWMccCVM){KXiFcpZslD = true;}
      else if(FZKWMccCVM == RXpmjuUgee){QuwpCesVfk = true;}
      if(daLPaTFeAg == fzyJbpTeOt){dhogKtjqLQ = true;}
      else if(fzyJbpTeOt == daLPaTFeAg){JEqHDlWCRl = true;}
      if(tAkzFzGbuQ == iKyuYaEuUi){xmxSkdNaww = true;}
      if(QtzwStqRKJ == cjBUSimBtV){UHZAGCurMj = true;}
      if(UaOyGgoIDn == pxuDVIBZxe){rFYbtYiWyC = true;}
      while(iKyuYaEuUi == tAkzFzGbuQ){MlQqfUTPTd = true;}
      while(cjBUSimBtV == cjBUSimBtV){ifbBuztlqs = true;}
      while(pxuDVIBZxe == pxuDVIBZxe){CmplZYlQLV = true;}
      if(IKlpntbOxk == true){IKlpntbOxk = false;}
      if(Yhgliuxdqr == true){Yhgliuxdqr = false;}
      if(CRjsDkPtZQ == true){CRjsDkPtZQ = false;}
      if(ZdxpaSyKfX == true){ZdxpaSyKfX = false;}
      if(GXDJwHPIUZ == true){GXDJwHPIUZ = false;}
      if(KXiFcpZslD == true){KXiFcpZslD = false;}
      if(dhogKtjqLQ == true){dhogKtjqLQ = false;}
      if(xmxSkdNaww == true){xmxSkdNaww = false;}
      if(UHZAGCurMj == true){UHZAGCurMj = false;}
      if(rFYbtYiWyC == true){rFYbtYiWyC = false;}
      if(XXxDcXZQTy == true){XXxDcXZQTy = false;}
      if(czwpiWInaI == true){czwpiWInaI = false;}
      if(zrdaXqNUYL == true){zrdaXqNUYL = false;}
      if(tqbsYwJVWi == true){tqbsYwJVWi = false;}
      if(cdXOHsIhsW == true){cdXOHsIhsW = false;}
      if(QuwpCesVfk == true){QuwpCesVfk = false;}
      if(JEqHDlWCRl == true){JEqHDlWCRl = false;}
      if(MlQqfUTPTd == true){MlQqfUTPTd = false;}
      if(ifbBuztlqs == true){ifbBuztlqs = false;}
      if(CmplZYlQLV == true){CmplZYlQLV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JNNXBLYWTV
{ 
  void JLcbqWfBrn()
  { 
      bool qLPDiyEMFN = false;
      bool ifLuOOHckY = false;
      bool JgNJqfgMsM = false;
      bool FUZkEzMrDI = false;
      bool nYEiPDRxkn = false;
      bool uqrWrJxFMC = false;
      bool RqTsIOFZpP = false;
      bool BPZbjkbesn = false;
      bool NibFQOcDru = false;
      bool BHfAqxFLaB = false;
      bool yqGVlfQPlH = false;
      bool gSMXnhPObs = false;
      bool lChuOtiYkm = false;
      bool eQDrpVbFTj = false;
      bool xMQjNitIMI = false;
      bool gqjhPuJKGq = false;
      bool xreybQOUhR = false;
      bool FKuquYkxhe = false;
      bool zaMcGnfVbt = false;
      bool MQybmFhRHw = false;
      string KuMLiliIWF;
      string iqWGDCuAyN;
      string sYpdpugRns;
      string ppeqcOChfk;
      string zacLrKUQLH;
      string GAJlxlFiUm;
      string EQUdOrLfdo;
      string ANTMORuelf;
      string aQGgmogstp;
      string JTMrghGzwz;
      string znmVGrgwXe;
      string qZxoMnKnpZ;
      string LSlmegAbff;
      string LuhlflcjZt;
      string IkUPziWXes;
      string XSIWngCzqZ;
      string qEPrSwrKIa;
      string KZNwQZxWnu;
      string KbwmHslKxz;
      string idsACDUcwC;
      if(KuMLiliIWF == znmVGrgwXe){qLPDiyEMFN = true;}
      else if(znmVGrgwXe == KuMLiliIWF){yqGVlfQPlH = true;}
      if(iqWGDCuAyN == qZxoMnKnpZ){ifLuOOHckY = true;}
      else if(qZxoMnKnpZ == iqWGDCuAyN){gSMXnhPObs = true;}
      if(sYpdpugRns == LSlmegAbff){JgNJqfgMsM = true;}
      else if(LSlmegAbff == sYpdpugRns){lChuOtiYkm = true;}
      if(ppeqcOChfk == LuhlflcjZt){FUZkEzMrDI = true;}
      else if(LuhlflcjZt == ppeqcOChfk){eQDrpVbFTj = true;}
      if(zacLrKUQLH == IkUPziWXes){nYEiPDRxkn = true;}
      else if(IkUPziWXes == zacLrKUQLH){xMQjNitIMI = true;}
      if(GAJlxlFiUm == XSIWngCzqZ){uqrWrJxFMC = true;}
      else if(XSIWngCzqZ == GAJlxlFiUm){gqjhPuJKGq = true;}
      if(EQUdOrLfdo == qEPrSwrKIa){RqTsIOFZpP = true;}
      else if(qEPrSwrKIa == EQUdOrLfdo){xreybQOUhR = true;}
      if(ANTMORuelf == KZNwQZxWnu){BPZbjkbesn = true;}
      if(aQGgmogstp == KbwmHslKxz){NibFQOcDru = true;}
      if(JTMrghGzwz == idsACDUcwC){BHfAqxFLaB = true;}
      while(KZNwQZxWnu == ANTMORuelf){FKuquYkxhe = true;}
      while(KbwmHslKxz == KbwmHslKxz){zaMcGnfVbt = true;}
      while(idsACDUcwC == idsACDUcwC){MQybmFhRHw = true;}
      if(qLPDiyEMFN == true){qLPDiyEMFN = false;}
      if(ifLuOOHckY == true){ifLuOOHckY = false;}
      if(JgNJqfgMsM == true){JgNJqfgMsM = false;}
      if(FUZkEzMrDI == true){FUZkEzMrDI = false;}
      if(nYEiPDRxkn == true){nYEiPDRxkn = false;}
      if(uqrWrJxFMC == true){uqrWrJxFMC = false;}
      if(RqTsIOFZpP == true){RqTsIOFZpP = false;}
      if(BPZbjkbesn == true){BPZbjkbesn = false;}
      if(NibFQOcDru == true){NibFQOcDru = false;}
      if(BHfAqxFLaB == true){BHfAqxFLaB = false;}
      if(yqGVlfQPlH == true){yqGVlfQPlH = false;}
      if(gSMXnhPObs == true){gSMXnhPObs = false;}
      if(lChuOtiYkm == true){lChuOtiYkm = false;}
      if(eQDrpVbFTj == true){eQDrpVbFTj = false;}
      if(xMQjNitIMI == true){xMQjNitIMI = false;}
      if(gqjhPuJKGq == true){gqjhPuJKGq = false;}
      if(xreybQOUhR == true){xreybQOUhR = false;}
      if(FKuquYkxhe == true){FKuquYkxhe = false;}
      if(zaMcGnfVbt == true){zaMcGnfVbt = false;}
      if(MQybmFhRHw == true){MQybmFhRHw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHYWQAUCCX
{ 
  void zTszPMnYUZ()
  { 
      bool sPpgZozoRF = false;
      bool KlSySVpkpu = false;
      bool WwVekmMgBG = false;
      bool rnUdFlgnMX = false;
      bool QDlxlgCjjl = false;
      bool fnofEwsKul = false;
      bool cSmKNWQosf = false;
      bool nBYSdSKYsD = false;
      bool jcxPaDyoYI = false;
      bool rVrZuyQajP = false;
      bool QMpDxdPWBk = false;
      bool kURqCzVWjJ = false;
      bool XbQjnSJzWe = false;
      bool CjndmWlsSw = false;
      bool namnWXEAXu = false;
      bool csqZqnwGPe = false;
      bool UPAViBfnEe = false;
      bool NbEmVwobNQ = false;
      bool OIbbBJrNlz = false;
      bool ZfcnbXaQEU = false;
      string KNbyOjqSUi;
      string spxsYtqfFU;
      string YEOJjhVtca;
      string XnzICpKhbA;
      string JfDNsZJJYu;
      string qXyNGGySNg;
      string OxotKFpnqi;
      string iJDFKrAAPK;
      string XMVhiAolCw;
      string qrUukMqJDn;
      string iUSoLhTrCN;
      string FxCCICbGKJ;
      string PEltrqoIUy;
      string BqxbaDsfWB;
      string gxjnpspRmh;
      string kjytXeiXxT;
      string sLXDMOAZaF;
      string IujJbRTxEy;
      string BWVlNQrDDw;
      string TViCHVZfba;
      if(KNbyOjqSUi == iUSoLhTrCN){sPpgZozoRF = true;}
      else if(iUSoLhTrCN == KNbyOjqSUi){QMpDxdPWBk = true;}
      if(spxsYtqfFU == FxCCICbGKJ){KlSySVpkpu = true;}
      else if(FxCCICbGKJ == spxsYtqfFU){kURqCzVWjJ = true;}
      if(YEOJjhVtca == PEltrqoIUy){WwVekmMgBG = true;}
      else if(PEltrqoIUy == YEOJjhVtca){XbQjnSJzWe = true;}
      if(XnzICpKhbA == BqxbaDsfWB){rnUdFlgnMX = true;}
      else if(BqxbaDsfWB == XnzICpKhbA){CjndmWlsSw = true;}
      if(JfDNsZJJYu == gxjnpspRmh){QDlxlgCjjl = true;}
      else if(gxjnpspRmh == JfDNsZJJYu){namnWXEAXu = true;}
      if(qXyNGGySNg == kjytXeiXxT){fnofEwsKul = true;}
      else if(kjytXeiXxT == qXyNGGySNg){csqZqnwGPe = true;}
      if(OxotKFpnqi == sLXDMOAZaF){cSmKNWQosf = true;}
      else if(sLXDMOAZaF == OxotKFpnqi){UPAViBfnEe = true;}
      if(iJDFKrAAPK == IujJbRTxEy){nBYSdSKYsD = true;}
      if(XMVhiAolCw == BWVlNQrDDw){jcxPaDyoYI = true;}
      if(qrUukMqJDn == TViCHVZfba){rVrZuyQajP = true;}
      while(IujJbRTxEy == iJDFKrAAPK){NbEmVwobNQ = true;}
      while(BWVlNQrDDw == BWVlNQrDDw){OIbbBJrNlz = true;}
      while(TViCHVZfba == TViCHVZfba){ZfcnbXaQEU = true;}
      if(sPpgZozoRF == true){sPpgZozoRF = false;}
      if(KlSySVpkpu == true){KlSySVpkpu = false;}
      if(WwVekmMgBG == true){WwVekmMgBG = false;}
      if(rnUdFlgnMX == true){rnUdFlgnMX = false;}
      if(QDlxlgCjjl == true){QDlxlgCjjl = false;}
      if(fnofEwsKul == true){fnofEwsKul = false;}
      if(cSmKNWQosf == true){cSmKNWQosf = false;}
      if(nBYSdSKYsD == true){nBYSdSKYsD = false;}
      if(jcxPaDyoYI == true){jcxPaDyoYI = false;}
      if(rVrZuyQajP == true){rVrZuyQajP = false;}
      if(QMpDxdPWBk == true){QMpDxdPWBk = false;}
      if(kURqCzVWjJ == true){kURqCzVWjJ = false;}
      if(XbQjnSJzWe == true){XbQjnSJzWe = false;}
      if(CjndmWlsSw == true){CjndmWlsSw = false;}
      if(namnWXEAXu == true){namnWXEAXu = false;}
      if(csqZqnwGPe == true){csqZqnwGPe = false;}
      if(UPAViBfnEe == true){UPAViBfnEe = false;}
      if(NbEmVwobNQ == true){NbEmVwobNQ = false;}
      if(OIbbBJrNlz == true){OIbbBJrNlz = false;}
      if(ZfcnbXaQEU == true){ZfcnbXaQEU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBZIQKAANF
{ 
  void RJUsqapMoK()
  { 
      bool MmFoZlLnQN = false;
      bool IZYIXMowoe = false;
      bool kUfpTYYPQG = false;
      bool PPFdoAgaTe = false;
      bool OUjmlLEmsu = false;
      bool JxNDQrGPUA = false;
      bool MuWJyrUtSW = false;
      bool fNbJPQkrDI = false;
      bool TkVVwRCBNx = false;
      bool sQGTSSxZot = false;
      bool pJTVPuUEnz = false;
      bool GOLMfaZBMf = false;
      bool pSgUdOHIqw = false;
      bool SLDJRKQAFB = false;
      bool xxNNqeFtmq = false;
      bool swMIEXczrA = false;
      bool nLMqgtKCtV = false;
      bool KZuLirFSdy = false;
      bool INVACWytFt = false;
      bool gRHEMkjVfw = false;
      string XSqTXyxyIh;
      string mmxzlACKEY;
      string ZjUwoZtPto;
      string AwYGEYTbyS;
      string QFPPHRhcKz;
      string Ddyksnxtey;
      string DhDShpOptN;
      string gZLkHUTEoX;
      string rRFtkWxmNQ;
      string bYxAOiBwhQ;
      string CqhxScRMdY;
      string TrFGFlcIhL;
      string sbcclHcLWX;
      string SXWYVAiHbI;
      string FjInxiTptc;
      string GrOWWaOFLK;
      string zFpGFuVgkF;
      string CUgZFJSnfC;
      string mmQtQaJABt;
      string kdwQIzsCiB;
      if(XSqTXyxyIh == CqhxScRMdY){MmFoZlLnQN = true;}
      else if(CqhxScRMdY == XSqTXyxyIh){pJTVPuUEnz = true;}
      if(mmxzlACKEY == TrFGFlcIhL){IZYIXMowoe = true;}
      else if(TrFGFlcIhL == mmxzlACKEY){GOLMfaZBMf = true;}
      if(ZjUwoZtPto == sbcclHcLWX){kUfpTYYPQG = true;}
      else if(sbcclHcLWX == ZjUwoZtPto){pSgUdOHIqw = true;}
      if(AwYGEYTbyS == SXWYVAiHbI){PPFdoAgaTe = true;}
      else if(SXWYVAiHbI == AwYGEYTbyS){SLDJRKQAFB = true;}
      if(QFPPHRhcKz == FjInxiTptc){OUjmlLEmsu = true;}
      else if(FjInxiTptc == QFPPHRhcKz){xxNNqeFtmq = true;}
      if(Ddyksnxtey == GrOWWaOFLK){JxNDQrGPUA = true;}
      else if(GrOWWaOFLK == Ddyksnxtey){swMIEXczrA = true;}
      if(DhDShpOptN == zFpGFuVgkF){MuWJyrUtSW = true;}
      else if(zFpGFuVgkF == DhDShpOptN){nLMqgtKCtV = true;}
      if(gZLkHUTEoX == CUgZFJSnfC){fNbJPQkrDI = true;}
      if(rRFtkWxmNQ == mmQtQaJABt){TkVVwRCBNx = true;}
      if(bYxAOiBwhQ == kdwQIzsCiB){sQGTSSxZot = true;}
      while(CUgZFJSnfC == gZLkHUTEoX){KZuLirFSdy = true;}
      while(mmQtQaJABt == mmQtQaJABt){INVACWytFt = true;}
      while(kdwQIzsCiB == kdwQIzsCiB){gRHEMkjVfw = true;}
      if(MmFoZlLnQN == true){MmFoZlLnQN = false;}
      if(IZYIXMowoe == true){IZYIXMowoe = false;}
      if(kUfpTYYPQG == true){kUfpTYYPQG = false;}
      if(PPFdoAgaTe == true){PPFdoAgaTe = false;}
      if(OUjmlLEmsu == true){OUjmlLEmsu = false;}
      if(JxNDQrGPUA == true){JxNDQrGPUA = false;}
      if(MuWJyrUtSW == true){MuWJyrUtSW = false;}
      if(fNbJPQkrDI == true){fNbJPQkrDI = false;}
      if(TkVVwRCBNx == true){TkVVwRCBNx = false;}
      if(sQGTSSxZot == true){sQGTSSxZot = false;}
      if(pJTVPuUEnz == true){pJTVPuUEnz = false;}
      if(GOLMfaZBMf == true){GOLMfaZBMf = false;}
      if(pSgUdOHIqw == true){pSgUdOHIqw = false;}
      if(SLDJRKQAFB == true){SLDJRKQAFB = false;}
      if(xxNNqeFtmq == true){xxNNqeFtmq = false;}
      if(swMIEXczrA == true){swMIEXczrA = false;}
      if(nLMqgtKCtV == true){nLMqgtKCtV = false;}
      if(KZuLirFSdy == true){KZuLirFSdy = false;}
      if(INVACWytFt == true){INVACWytFt = false;}
      if(gRHEMkjVfw == true){gRHEMkjVfw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SPKVNMTMLS
{ 
  void XNMsZVgzRd()
  { 
      bool ygVoseDoIP = false;
      bool ngkSenrUVq = false;
      bool hIyenRVbWU = false;
      bool DbHsPnTAKc = false;
      bool qzICeEhjpl = false;
      bool TEwHOoiqBb = false;
      bool JaRmLLYqCp = false;
      bool TrKszizwAj = false;
      bool iklkBzfAdZ = false;
      bool EcyiTQgVpS = false;
      bool epgzSbsDHf = false;
      bool pmpRrXogkM = false;
      bool fYMblpsbZi = false;
      bool BdFgFsDlSZ = false;
      bool FbryjRmgpu = false;
      bool aAjdmFcENc = false;
      bool hRdYdMgIMy = false;
      bool TDOLGDgOrT = false;
      bool CMkdHAsbsz = false;
      bool PyYoqmySTX = false;
      string ECrNtDdILp;
      string hebADaecFw;
      string ouxjjssRBQ;
      string hAzQZKhzMR;
      string YahYDGpMMM;
      string VCuMxJFIdA;
      string JMHuHheKar;
      string rfPnXOMXgd;
      string DfEotfFlTP;
      string FZULHLSmQV;
      string aelTTplGoh;
      string wgbAxdISBb;
      string brqKmSLEgL;
      string uZGLCYtjUE;
      string tyxkTYxUOc;
      string DAlosimagA;
      string dhYdlWZQyY;
      string jYxwgcuGpO;
      string VpoDHunQRS;
      string kSCUZLZSyx;
      if(ECrNtDdILp == aelTTplGoh){ygVoseDoIP = true;}
      else if(aelTTplGoh == ECrNtDdILp){epgzSbsDHf = true;}
      if(hebADaecFw == wgbAxdISBb){ngkSenrUVq = true;}
      else if(wgbAxdISBb == hebADaecFw){pmpRrXogkM = true;}
      if(ouxjjssRBQ == brqKmSLEgL){hIyenRVbWU = true;}
      else if(brqKmSLEgL == ouxjjssRBQ){fYMblpsbZi = true;}
      if(hAzQZKhzMR == uZGLCYtjUE){DbHsPnTAKc = true;}
      else if(uZGLCYtjUE == hAzQZKhzMR){BdFgFsDlSZ = true;}
      if(YahYDGpMMM == tyxkTYxUOc){qzICeEhjpl = true;}
      else if(tyxkTYxUOc == YahYDGpMMM){FbryjRmgpu = true;}
      if(VCuMxJFIdA == DAlosimagA){TEwHOoiqBb = true;}
      else if(DAlosimagA == VCuMxJFIdA){aAjdmFcENc = true;}
      if(JMHuHheKar == dhYdlWZQyY){JaRmLLYqCp = true;}
      else if(dhYdlWZQyY == JMHuHheKar){hRdYdMgIMy = true;}
      if(rfPnXOMXgd == jYxwgcuGpO){TrKszizwAj = true;}
      if(DfEotfFlTP == VpoDHunQRS){iklkBzfAdZ = true;}
      if(FZULHLSmQV == kSCUZLZSyx){EcyiTQgVpS = true;}
      while(jYxwgcuGpO == rfPnXOMXgd){TDOLGDgOrT = true;}
      while(VpoDHunQRS == VpoDHunQRS){CMkdHAsbsz = true;}
      while(kSCUZLZSyx == kSCUZLZSyx){PyYoqmySTX = true;}
      if(ygVoseDoIP == true){ygVoseDoIP = false;}
      if(ngkSenrUVq == true){ngkSenrUVq = false;}
      if(hIyenRVbWU == true){hIyenRVbWU = false;}
      if(DbHsPnTAKc == true){DbHsPnTAKc = false;}
      if(qzICeEhjpl == true){qzICeEhjpl = false;}
      if(TEwHOoiqBb == true){TEwHOoiqBb = false;}
      if(JaRmLLYqCp == true){JaRmLLYqCp = false;}
      if(TrKszizwAj == true){TrKszizwAj = false;}
      if(iklkBzfAdZ == true){iklkBzfAdZ = false;}
      if(EcyiTQgVpS == true){EcyiTQgVpS = false;}
      if(epgzSbsDHf == true){epgzSbsDHf = false;}
      if(pmpRrXogkM == true){pmpRrXogkM = false;}
      if(fYMblpsbZi == true){fYMblpsbZi = false;}
      if(BdFgFsDlSZ == true){BdFgFsDlSZ = false;}
      if(FbryjRmgpu == true){FbryjRmgpu = false;}
      if(aAjdmFcENc == true){aAjdmFcENc = false;}
      if(hRdYdMgIMy == true){hRdYdMgIMy = false;}
      if(TDOLGDgOrT == true){TDOLGDgOrT = false;}
      if(CMkdHAsbsz == true){CMkdHAsbsz = false;}
      if(PyYoqmySTX == true){PyYoqmySTX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ADSYNVHRPO
{ 
  void VGEzBHZLFS()
  { 
      bool mmWaOKKGwS = false;
      bool xPTYfMHqZl = false;
      bool ppjEEKdHak = false;
      bool XiZRxboCoj = false;
      bool KwAdBBogjX = false;
      bool zJFpfwDSVE = false;
      bool fCfKtOoBaD = false;
      bool XFCpbsoFDD = false;
      bool UxXDkOcjlB = false;
      bool YVfkDIPpil = false;
      bool LnGfztHPOl = false;
      bool GxPSjidbYf = false;
      bool kFPYdBZRlT = false;
      bool dzWQqgpqDq = false;
      bool GNUzubFMBU = false;
      bool dmQDBGXhCx = false;
      bool TpduIGazbD = false;
      bool rlYgYXjQdC = false;
      bool wMPRophSOk = false;
      bool IIoFWQjZpn = false;
      string TDIAnuzhCU;
      string bpQntDTbxO;
      string RsTcxnbPFJ;
      string jXLeFiYrBn;
      string duhJVIuwfL;
      string miqxhaifDz;
      string SicrkEeliL;
      string daZIkVLJHo;
      string sfjsWAfNwe;
      string zsnBVtSoYQ;
      string cINUgLIiLL;
      string OYXOFmzjVj;
      string XQoELklYmp;
      string DVkpLkSOLK;
      string qxBkPaUZui;
      string uhSnsMTIJw;
      string ZjuVHsmgCU;
      string TjXLrZODok;
      string PMcDuUDwxy;
      string QJFPkHBfcW;
      if(TDIAnuzhCU == cINUgLIiLL){mmWaOKKGwS = true;}
      else if(cINUgLIiLL == TDIAnuzhCU){LnGfztHPOl = true;}
      if(bpQntDTbxO == OYXOFmzjVj){xPTYfMHqZl = true;}
      else if(OYXOFmzjVj == bpQntDTbxO){GxPSjidbYf = true;}
      if(RsTcxnbPFJ == XQoELklYmp){ppjEEKdHak = true;}
      else if(XQoELklYmp == RsTcxnbPFJ){kFPYdBZRlT = true;}
      if(jXLeFiYrBn == DVkpLkSOLK){XiZRxboCoj = true;}
      else if(DVkpLkSOLK == jXLeFiYrBn){dzWQqgpqDq = true;}
      if(duhJVIuwfL == qxBkPaUZui){KwAdBBogjX = true;}
      else if(qxBkPaUZui == duhJVIuwfL){GNUzubFMBU = true;}
      if(miqxhaifDz == uhSnsMTIJw){zJFpfwDSVE = true;}
      else if(uhSnsMTIJw == miqxhaifDz){dmQDBGXhCx = true;}
      if(SicrkEeliL == ZjuVHsmgCU){fCfKtOoBaD = true;}
      else if(ZjuVHsmgCU == SicrkEeliL){TpduIGazbD = true;}
      if(daZIkVLJHo == TjXLrZODok){XFCpbsoFDD = true;}
      if(sfjsWAfNwe == PMcDuUDwxy){UxXDkOcjlB = true;}
      if(zsnBVtSoYQ == QJFPkHBfcW){YVfkDIPpil = true;}
      while(TjXLrZODok == daZIkVLJHo){rlYgYXjQdC = true;}
      while(PMcDuUDwxy == PMcDuUDwxy){wMPRophSOk = true;}
      while(QJFPkHBfcW == QJFPkHBfcW){IIoFWQjZpn = true;}
      if(mmWaOKKGwS == true){mmWaOKKGwS = false;}
      if(xPTYfMHqZl == true){xPTYfMHqZl = false;}
      if(ppjEEKdHak == true){ppjEEKdHak = false;}
      if(XiZRxboCoj == true){XiZRxboCoj = false;}
      if(KwAdBBogjX == true){KwAdBBogjX = false;}
      if(zJFpfwDSVE == true){zJFpfwDSVE = false;}
      if(fCfKtOoBaD == true){fCfKtOoBaD = false;}
      if(XFCpbsoFDD == true){XFCpbsoFDD = false;}
      if(UxXDkOcjlB == true){UxXDkOcjlB = false;}
      if(YVfkDIPpil == true){YVfkDIPpil = false;}
      if(LnGfztHPOl == true){LnGfztHPOl = false;}
      if(GxPSjidbYf == true){GxPSjidbYf = false;}
      if(kFPYdBZRlT == true){kFPYdBZRlT = false;}
      if(dzWQqgpqDq == true){dzWQqgpqDq = false;}
      if(GNUzubFMBU == true){GNUzubFMBU = false;}
      if(dmQDBGXhCx == true){dmQDBGXhCx = false;}
      if(TpduIGazbD == true){TpduIGazbD = false;}
      if(rlYgYXjQdC == true){rlYgYXjQdC = false;}
      if(wMPRophSOk == true){wMPRophSOk = false;}
      if(IIoFWQjZpn == true){IIoFWQjZpn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UZFNRIJNUP
{ 
  void VIkfzDAuQf()
  { 
      bool HyhfIHpdkC = false;
      bool WTIBjTHGgf = false;
      bool DfPctkAgIa = false;
      bool HOpNNkDgYQ = false;
      bool kcOiUTIAVx = false;
      bool CpTUtbiFkX = false;
      bool GJUKuHcumy = false;
      bool PahPuaQfIa = false;
      bool cAKLXQuUSl = false;
      bool CyuAJbHEnM = false;
      bool pMMXhbIDZT = false;
      bool KCxKuGzJld = false;
      bool MHbBuRegFS = false;
      bool SMqujPmmdu = false;
      bool IquzaAAkFD = false;
      bool cyRKzhkLbP = false;
      bool xbyGAyKBZe = false;
      bool TLepUUMbZu = false;
      bool QsaCpTtgwC = false;
      bool daLNygsnyb = false;
      string HOIqrkVEMz;
      string hPKPIzYLDk;
      string jYzeHzUoKz;
      string BgBkOHWjnO;
      string RkNltVmrif;
      string iWSHMhPdir;
      string QgsMxAOZBB;
      string boXoTyLMkk;
      string LbFeQeNsXf;
      string qrAuykrAos;
      string HMpgDtydnO;
      string WDsygnaOwR;
      string mUBVJincqh;
      string FLWqdylYaW;
      string giFJJnzCOJ;
      string JdEWFlLUWT;
      string FVmFIKfBTh;
      string BCmZkDPrLV;
      string jlNgYbHAlq;
      string mQBGQKwABy;
      if(HOIqrkVEMz == HMpgDtydnO){HyhfIHpdkC = true;}
      else if(HMpgDtydnO == HOIqrkVEMz){pMMXhbIDZT = true;}
      if(hPKPIzYLDk == WDsygnaOwR){WTIBjTHGgf = true;}
      else if(WDsygnaOwR == hPKPIzYLDk){KCxKuGzJld = true;}
      if(jYzeHzUoKz == mUBVJincqh){DfPctkAgIa = true;}
      else if(mUBVJincqh == jYzeHzUoKz){MHbBuRegFS = true;}
      if(BgBkOHWjnO == FLWqdylYaW){HOpNNkDgYQ = true;}
      else if(FLWqdylYaW == BgBkOHWjnO){SMqujPmmdu = true;}
      if(RkNltVmrif == giFJJnzCOJ){kcOiUTIAVx = true;}
      else if(giFJJnzCOJ == RkNltVmrif){IquzaAAkFD = true;}
      if(iWSHMhPdir == JdEWFlLUWT){CpTUtbiFkX = true;}
      else if(JdEWFlLUWT == iWSHMhPdir){cyRKzhkLbP = true;}
      if(QgsMxAOZBB == FVmFIKfBTh){GJUKuHcumy = true;}
      else if(FVmFIKfBTh == QgsMxAOZBB){xbyGAyKBZe = true;}
      if(boXoTyLMkk == BCmZkDPrLV){PahPuaQfIa = true;}
      if(LbFeQeNsXf == jlNgYbHAlq){cAKLXQuUSl = true;}
      if(qrAuykrAos == mQBGQKwABy){CyuAJbHEnM = true;}
      while(BCmZkDPrLV == boXoTyLMkk){TLepUUMbZu = true;}
      while(jlNgYbHAlq == jlNgYbHAlq){QsaCpTtgwC = true;}
      while(mQBGQKwABy == mQBGQKwABy){daLNygsnyb = true;}
      if(HyhfIHpdkC == true){HyhfIHpdkC = false;}
      if(WTIBjTHGgf == true){WTIBjTHGgf = false;}
      if(DfPctkAgIa == true){DfPctkAgIa = false;}
      if(HOpNNkDgYQ == true){HOpNNkDgYQ = false;}
      if(kcOiUTIAVx == true){kcOiUTIAVx = false;}
      if(CpTUtbiFkX == true){CpTUtbiFkX = false;}
      if(GJUKuHcumy == true){GJUKuHcumy = false;}
      if(PahPuaQfIa == true){PahPuaQfIa = false;}
      if(cAKLXQuUSl == true){cAKLXQuUSl = false;}
      if(CyuAJbHEnM == true){CyuAJbHEnM = false;}
      if(pMMXhbIDZT == true){pMMXhbIDZT = false;}
      if(KCxKuGzJld == true){KCxKuGzJld = false;}
      if(MHbBuRegFS == true){MHbBuRegFS = false;}
      if(SMqujPmmdu == true){SMqujPmmdu = false;}
      if(IquzaAAkFD == true){IquzaAAkFD = false;}
      if(cyRKzhkLbP == true){cyRKzhkLbP = false;}
      if(xbyGAyKBZe == true){xbyGAyKBZe = false;}
      if(TLepUUMbZu == true){TLepUUMbZu = false;}
      if(QsaCpTtgwC == true){QsaCpTtgwC = false;}
      if(daLNygsnyb == true){daLNygsnyb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVTJMXHQIY
{ 
  void TNqQFyuOxM()
  { 
      bool oPpQYoXtHe = false;
      bool runysnqmsg = false;
      bool hTfgAFdBMA = false;
      bool rHwCEsHtDt = false;
      bool fwhnRoiFgA = false;
      bool GrwcCUjJQS = false;
      bool KWhHmkzksA = false;
      bool gwjzBllrOK = false;
      bool WYULszLSAi = false;
      bool JydjiINZAg = false;
      bool pxLfTKHxbP = false;
      bool irtFukBVNn = false;
      bool YgjKpiRAPs = false;
      bool XMqhTZNnri = false;
      bool rNqkARDXnx = false;
      bool HrMMHJMBpk = false;
      bool rHghqVAMkV = false;
      bool XMceuKozJY = false;
      bool etLRkeAeaK = false;
      bool MMyGqkgIsd = false;
      string wfniOIloyn;
      string ANbPOHgohZ;
      string STXYhsLXiW;
      string XqtkyOzaya;
      string QJEVfZxomg;
      string ZGBrybIOAV;
      string xOFbQJSqRA;
      string HGpHIIPBsI;
      string uVjBwQpCmV;
      string GjZccCEbFW;
      string HGXmZTQtip;
      string MGVrZaeDez;
      string TQEwtWfNdG;
      string EmwWBnywbc;
      string AuSwIzOhCB;
      string WAxGDpCasC;
      string mCPckYJzql;
      string chbCyXxHmt;
      string IyLbiDpoTK;
      string kWDZoyfpKj;
      if(wfniOIloyn == HGXmZTQtip){oPpQYoXtHe = true;}
      else if(HGXmZTQtip == wfniOIloyn){pxLfTKHxbP = true;}
      if(ANbPOHgohZ == MGVrZaeDez){runysnqmsg = true;}
      else if(MGVrZaeDez == ANbPOHgohZ){irtFukBVNn = true;}
      if(STXYhsLXiW == TQEwtWfNdG){hTfgAFdBMA = true;}
      else if(TQEwtWfNdG == STXYhsLXiW){YgjKpiRAPs = true;}
      if(XqtkyOzaya == EmwWBnywbc){rHwCEsHtDt = true;}
      else if(EmwWBnywbc == XqtkyOzaya){XMqhTZNnri = true;}
      if(QJEVfZxomg == AuSwIzOhCB){fwhnRoiFgA = true;}
      else if(AuSwIzOhCB == QJEVfZxomg){rNqkARDXnx = true;}
      if(ZGBrybIOAV == WAxGDpCasC){GrwcCUjJQS = true;}
      else if(WAxGDpCasC == ZGBrybIOAV){HrMMHJMBpk = true;}
      if(xOFbQJSqRA == mCPckYJzql){KWhHmkzksA = true;}
      else if(mCPckYJzql == xOFbQJSqRA){rHghqVAMkV = true;}
      if(HGpHIIPBsI == chbCyXxHmt){gwjzBllrOK = true;}
      if(uVjBwQpCmV == IyLbiDpoTK){WYULszLSAi = true;}
      if(GjZccCEbFW == kWDZoyfpKj){JydjiINZAg = true;}
      while(chbCyXxHmt == HGpHIIPBsI){XMceuKozJY = true;}
      while(IyLbiDpoTK == IyLbiDpoTK){etLRkeAeaK = true;}
      while(kWDZoyfpKj == kWDZoyfpKj){MMyGqkgIsd = true;}
      if(oPpQYoXtHe == true){oPpQYoXtHe = false;}
      if(runysnqmsg == true){runysnqmsg = false;}
      if(hTfgAFdBMA == true){hTfgAFdBMA = false;}
      if(rHwCEsHtDt == true){rHwCEsHtDt = false;}
      if(fwhnRoiFgA == true){fwhnRoiFgA = false;}
      if(GrwcCUjJQS == true){GrwcCUjJQS = false;}
      if(KWhHmkzksA == true){KWhHmkzksA = false;}
      if(gwjzBllrOK == true){gwjzBllrOK = false;}
      if(WYULszLSAi == true){WYULszLSAi = false;}
      if(JydjiINZAg == true){JydjiINZAg = false;}
      if(pxLfTKHxbP == true){pxLfTKHxbP = false;}
      if(irtFukBVNn == true){irtFukBVNn = false;}
      if(YgjKpiRAPs == true){YgjKpiRAPs = false;}
      if(XMqhTZNnri == true){XMqhTZNnri = false;}
      if(rNqkARDXnx == true){rNqkARDXnx = false;}
      if(HrMMHJMBpk == true){HrMMHJMBpk = false;}
      if(rHghqVAMkV == true){rHghqVAMkV = false;}
      if(XMceuKozJY == true){XMceuKozJY = false;}
      if(etLRkeAeaK == true){etLRkeAeaK = false;}
      if(MMyGqkgIsd == true){MMyGqkgIsd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SROOGDILLJ
{ 
  void RapRGVWJWs()
  { 
      bool aFurNKLmlT = false;
      bool nSaFWAQoqF = false;
      bool WKGAoFjulX = false;
      bool MScDbBEWST = false;
      bool MMSXOYnQpZ = false;
      bool exCcdPzuCI = false;
      bool ZQANHVpXdV = false;
      bool usVXsKqhlQ = false;
      bool QTEMsPPAZL = false;
      bool BJUKsuLEQs = false;
      bool iPmUdkaeiT = false;
      bool XQJlqGMnUq = false;
      bool FpxRTlYLdx = false;
      bool ymRrgAfjhH = false;
      bool nkQGmkzhSm = false;
      bool iXjYmrSUBr = false;
      bool MPAlUkzQEp = false;
      bool ZcFNCUZqei = false;
      bool lqrqOaDrFo = false;
      bool hLiotYjelC = false;
      string pzIIJrMZrp;
      string uIXPShxhbV;
      string LjKNUeaste;
      string tsyRxHIsKO;
      string WzzxbnGYNO;
      string EuzQiFound;
      string QSeNuBJFSL;
      string YEXNzMkNkg;
      string XBffaztgiq;
      string SNFgxDTlBZ;
      string dBGBoAXlRW;
      string UaJGFPlzmu;
      string HcWasLzqPu;
      string ryLKDWueqa;
      string bIPLWqEyah;
      string RTzGSAdfId;
      string AfVVdVPyCh;
      string UHIMTyMKEC;
      string GAPgdXzFrC;
      string rPWNZulthA;
      if(pzIIJrMZrp == dBGBoAXlRW){aFurNKLmlT = true;}
      else if(dBGBoAXlRW == pzIIJrMZrp){iPmUdkaeiT = true;}
      if(uIXPShxhbV == UaJGFPlzmu){nSaFWAQoqF = true;}
      else if(UaJGFPlzmu == uIXPShxhbV){XQJlqGMnUq = true;}
      if(LjKNUeaste == HcWasLzqPu){WKGAoFjulX = true;}
      else if(HcWasLzqPu == LjKNUeaste){FpxRTlYLdx = true;}
      if(tsyRxHIsKO == ryLKDWueqa){MScDbBEWST = true;}
      else if(ryLKDWueqa == tsyRxHIsKO){ymRrgAfjhH = true;}
      if(WzzxbnGYNO == bIPLWqEyah){MMSXOYnQpZ = true;}
      else if(bIPLWqEyah == WzzxbnGYNO){nkQGmkzhSm = true;}
      if(EuzQiFound == RTzGSAdfId){exCcdPzuCI = true;}
      else if(RTzGSAdfId == EuzQiFound){iXjYmrSUBr = true;}
      if(QSeNuBJFSL == AfVVdVPyCh){ZQANHVpXdV = true;}
      else if(AfVVdVPyCh == QSeNuBJFSL){MPAlUkzQEp = true;}
      if(YEXNzMkNkg == UHIMTyMKEC){usVXsKqhlQ = true;}
      if(XBffaztgiq == GAPgdXzFrC){QTEMsPPAZL = true;}
      if(SNFgxDTlBZ == rPWNZulthA){BJUKsuLEQs = true;}
      while(UHIMTyMKEC == YEXNzMkNkg){ZcFNCUZqei = true;}
      while(GAPgdXzFrC == GAPgdXzFrC){lqrqOaDrFo = true;}
      while(rPWNZulthA == rPWNZulthA){hLiotYjelC = true;}
      if(aFurNKLmlT == true){aFurNKLmlT = false;}
      if(nSaFWAQoqF == true){nSaFWAQoqF = false;}
      if(WKGAoFjulX == true){WKGAoFjulX = false;}
      if(MScDbBEWST == true){MScDbBEWST = false;}
      if(MMSXOYnQpZ == true){MMSXOYnQpZ = false;}
      if(exCcdPzuCI == true){exCcdPzuCI = false;}
      if(ZQANHVpXdV == true){ZQANHVpXdV = false;}
      if(usVXsKqhlQ == true){usVXsKqhlQ = false;}
      if(QTEMsPPAZL == true){QTEMsPPAZL = false;}
      if(BJUKsuLEQs == true){BJUKsuLEQs = false;}
      if(iPmUdkaeiT == true){iPmUdkaeiT = false;}
      if(XQJlqGMnUq == true){XQJlqGMnUq = false;}
      if(FpxRTlYLdx == true){FpxRTlYLdx = false;}
      if(ymRrgAfjhH == true){ymRrgAfjhH = false;}
      if(nkQGmkzhSm == true){nkQGmkzhSm = false;}
      if(iXjYmrSUBr == true){iXjYmrSUBr = false;}
      if(MPAlUkzQEp == true){MPAlUkzQEp = false;}
      if(ZcFNCUZqei == true){ZcFNCUZqei = false;}
      if(lqrqOaDrFo == true){lqrqOaDrFo = false;}
      if(hLiotYjelC == true){hLiotYjelC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WWXJBJIAPR
{ 
  void lBHDYNxNbq()
  { 
      bool WNMFjrfJYL = false;
      bool WQOGMJhiZk = false;
      bool oPkAFQDCFy = false;
      bool tTnmKTzHgc = false;
      bool WnQqsAHqrw = false;
      bool OZOCjGcMAT = false;
      bool ncEaQCcbws = false;
      bool KZCxNAztHE = false;
      bool IMKIiUFkCD = false;
      bool qmHNnsjoZp = false;
      bool XfuzlnXQoi = false;
      bool GiEwLbSuqw = false;
      bool xqYrCXSnIT = false;
      bool QKTQfbRKWu = false;
      bool wnwSxHhKCM = false;
      bool aoxdrgHCxO = false;
      bool ViIUSwOnPj = false;
      bool JIYwzJtFut = false;
      bool pHlusaMoXz = false;
      bool TOMHYNeaAA = false;
      string hSrEIjzZod;
      string EqptYtoAsx;
      string SCmqcSxeqT;
      string OnDczXGOAu;
      string BecVtLKwxP;
      string jknHUffBbp;
      string lUiVPPnMtA;
      string maAxwnZQwR;
      string IAhajcAuIT;
      string qFlJIgwGGd;
      string WxCwbIkpLf;
      string GPEKgkmHll;
      string OrEaIhnpoP;
      string rSJRtKykza;
      string qKjbNbAbbW;
      string tnUTPesbmt;
      string UuBunmFmPW;
      string mBILtEIbMg;
      string gLNRVDyoCP;
      string RWxFFwJnnZ;
      if(hSrEIjzZod == WxCwbIkpLf){WNMFjrfJYL = true;}
      else if(WxCwbIkpLf == hSrEIjzZod){XfuzlnXQoi = true;}
      if(EqptYtoAsx == GPEKgkmHll){WQOGMJhiZk = true;}
      else if(GPEKgkmHll == EqptYtoAsx){GiEwLbSuqw = true;}
      if(SCmqcSxeqT == OrEaIhnpoP){oPkAFQDCFy = true;}
      else if(OrEaIhnpoP == SCmqcSxeqT){xqYrCXSnIT = true;}
      if(OnDczXGOAu == rSJRtKykza){tTnmKTzHgc = true;}
      else if(rSJRtKykza == OnDczXGOAu){QKTQfbRKWu = true;}
      if(BecVtLKwxP == qKjbNbAbbW){WnQqsAHqrw = true;}
      else if(qKjbNbAbbW == BecVtLKwxP){wnwSxHhKCM = true;}
      if(jknHUffBbp == tnUTPesbmt){OZOCjGcMAT = true;}
      else if(tnUTPesbmt == jknHUffBbp){aoxdrgHCxO = true;}
      if(lUiVPPnMtA == UuBunmFmPW){ncEaQCcbws = true;}
      else if(UuBunmFmPW == lUiVPPnMtA){ViIUSwOnPj = true;}
      if(maAxwnZQwR == mBILtEIbMg){KZCxNAztHE = true;}
      if(IAhajcAuIT == gLNRVDyoCP){IMKIiUFkCD = true;}
      if(qFlJIgwGGd == RWxFFwJnnZ){qmHNnsjoZp = true;}
      while(mBILtEIbMg == maAxwnZQwR){JIYwzJtFut = true;}
      while(gLNRVDyoCP == gLNRVDyoCP){pHlusaMoXz = true;}
      while(RWxFFwJnnZ == RWxFFwJnnZ){TOMHYNeaAA = true;}
      if(WNMFjrfJYL == true){WNMFjrfJYL = false;}
      if(WQOGMJhiZk == true){WQOGMJhiZk = false;}
      if(oPkAFQDCFy == true){oPkAFQDCFy = false;}
      if(tTnmKTzHgc == true){tTnmKTzHgc = false;}
      if(WnQqsAHqrw == true){WnQqsAHqrw = false;}
      if(OZOCjGcMAT == true){OZOCjGcMAT = false;}
      if(ncEaQCcbws == true){ncEaQCcbws = false;}
      if(KZCxNAztHE == true){KZCxNAztHE = false;}
      if(IMKIiUFkCD == true){IMKIiUFkCD = false;}
      if(qmHNnsjoZp == true){qmHNnsjoZp = false;}
      if(XfuzlnXQoi == true){XfuzlnXQoi = false;}
      if(GiEwLbSuqw == true){GiEwLbSuqw = false;}
      if(xqYrCXSnIT == true){xqYrCXSnIT = false;}
      if(QKTQfbRKWu == true){QKTQfbRKWu = false;}
      if(wnwSxHhKCM == true){wnwSxHhKCM = false;}
      if(aoxdrgHCxO == true){aoxdrgHCxO = false;}
      if(ViIUSwOnPj == true){ViIUSwOnPj = false;}
      if(JIYwzJtFut == true){JIYwzJtFut = false;}
      if(pHlusaMoXz == true){pHlusaMoXz = false;}
      if(TOMHYNeaAA == true){TOMHYNeaAA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TSBNGEDRIW
{ 
  void upgnPRVrGa()
  { 
      bool rZTGainXBs = false;
      bool srBDhiDnAH = false;
      bool SMWHODDheN = false;
      bool bJRPNpzfbz = false;
      bool yTysjeHYcn = false;
      bool bSrEAfDLrX = false;
      bool fGsnQiZlpq = false;
      bool iWLBIzOcXj = false;
      bool udEqkJRMPg = false;
      bool mnnETrZJbA = false;
      bool EUikEEGpwA = false;
      bool RZmHbBBCDH = false;
      bool RMWIEtiGhQ = false;
      bool YEBXeZuTlf = false;
      bool CaQOPMAfcR = false;
      bool qXGUiryZfK = false;
      bool VzIfbMYPcB = false;
      bool FgQWEpwIrr = false;
      bool tDdPYAxfnm = false;
      bool bVmbKDSkmC = false;
      string fZxSuBaXdL;
      string UFuNzRDCih;
      string wnOyLPDCOG;
      string JFRnwYHTCt;
      string ErXKYMOMuH;
      string IUXJRrLyGe;
      string yYJXCOmGQZ;
      string JjAncDQDYy;
      string ApHHxnhIVE;
      string NJMWwfizIJ;
      string ZHwVyYTifO;
      string aHYIdHQBZN;
      string gekLLAWdrx;
      string TQuPXstkIY;
      string UybGcFjDrn;
      string OgZtbuVjJy;
      string BoqitKMJjk;
      string NesBsiCdhG;
      string PSlDhmqAmc;
      string WJbKWeGrMS;
      if(fZxSuBaXdL == ZHwVyYTifO){rZTGainXBs = true;}
      else if(ZHwVyYTifO == fZxSuBaXdL){EUikEEGpwA = true;}
      if(UFuNzRDCih == aHYIdHQBZN){srBDhiDnAH = true;}
      else if(aHYIdHQBZN == UFuNzRDCih){RZmHbBBCDH = true;}
      if(wnOyLPDCOG == gekLLAWdrx){SMWHODDheN = true;}
      else if(gekLLAWdrx == wnOyLPDCOG){RMWIEtiGhQ = true;}
      if(JFRnwYHTCt == TQuPXstkIY){bJRPNpzfbz = true;}
      else if(TQuPXstkIY == JFRnwYHTCt){YEBXeZuTlf = true;}
      if(ErXKYMOMuH == UybGcFjDrn){yTysjeHYcn = true;}
      else if(UybGcFjDrn == ErXKYMOMuH){CaQOPMAfcR = true;}
      if(IUXJRrLyGe == OgZtbuVjJy){bSrEAfDLrX = true;}
      else if(OgZtbuVjJy == IUXJRrLyGe){qXGUiryZfK = true;}
      if(yYJXCOmGQZ == BoqitKMJjk){fGsnQiZlpq = true;}
      else if(BoqitKMJjk == yYJXCOmGQZ){VzIfbMYPcB = true;}
      if(JjAncDQDYy == NesBsiCdhG){iWLBIzOcXj = true;}
      if(ApHHxnhIVE == PSlDhmqAmc){udEqkJRMPg = true;}
      if(NJMWwfizIJ == WJbKWeGrMS){mnnETrZJbA = true;}
      while(NesBsiCdhG == JjAncDQDYy){FgQWEpwIrr = true;}
      while(PSlDhmqAmc == PSlDhmqAmc){tDdPYAxfnm = true;}
      while(WJbKWeGrMS == WJbKWeGrMS){bVmbKDSkmC = true;}
      if(rZTGainXBs == true){rZTGainXBs = false;}
      if(srBDhiDnAH == true){srBDhiDnAH = false;}
      if(SMWHODDheN == true){SMWHODDheN = false;}
      if(bJRPNpzfbz == true){bJRPNpzfbz = false;}
      if(yTysjeHYcn == true){yTysjeHYcn = false;}
      if(bSrEAfDLrX == true){bSrEAfDLrX = false;}
      if(fGsnQiZlpq == true){fGsnQiZlpq = false;}
      if(iWLBIzOcXj == true){iWLBIzOcXj = false;}
      if(udEqkJRMPg == true){udEqkJRMPg = false;}
      if(mnnETrZJbA == true){mnnETrZJbA = false;}
      if(EUikEEGpwA == true){EUikEEGpwA = false;}
      if(RZmHbBBCDH == true){RZmHbBBCDH = false;}
      if(RMWIEtiGhQ == true){RMWIEtiGhQ = false;}
      if(YEBXeZuTlf == true){YEBXeZuTlf = false;}
      if(CaQOPMAfcR == true){CaQOPMAfcR = false;}
      if(qXGUiryZfK == true){qXGUiryZfK = false;}
      if(VzIfbMYPcB == true){VzIfbMYPcB = false;}
      if(FgQWEpwIrr == true){FgQWEpwIrr = false;}
      if(tDdPYAxfnm == true){tDdPYAxfnm = false;}
      if(bVmbKDSkmC == true){bVmbKDSkmC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MEEQZYCLSB
{ 
  void ZOyNLeAwni()
  { 
      bool GJyZjWHIcP = false;
      bool GgqtzkNZCz = false;
      bool CHMJeoJlsH = false;
      bool wCTYiJCUIk = false;
      bool EArZCtgJKD = false;
      bool swpVKyxout = false;
      bool NVPUTDMRKp = false;
      bool hrQRuCOmHj = false;
      bool HAaoOzMxOj = false;
      bool LNZNXhjXFy = false;
      bool hPyUUAeYaI = false;
      bool jKgKlMuZGU = false;
      bool qODZdUSDsM = false;
      bool RqgICrBGUN = false;
      bool TmWGABfPaK = false;
      bool mKQkHSLXqA = false;
      bool hbeOprcXHt = false;
      bool LoFrADrxZc = false;
      bool nCbiZHawBj = false;
      bool gdPTfqIHPI = false;
      string KOyJIkCnph;
      string VrMyAoxpcJ;
      string XunKTOcFny;
      string AOlfBAYjdW;
      string gcrExHYlIN;
      string RxPeWPZnps;
      string HwzqhGFfxz;
      string QMMFctCjNM;
      string pqwagCzGJl;
      string ZktjOjcBWp;
      string BroJxFkJCb;
      string MpZcDQAYJe;
      string HzWLYeSbqr;
      string QAMXKxCmcb;
      string QoDgYjLQfy;
      string jEqqhCVdjS;
      string lJSKLLcBSG;
      string NMwhOSuolo;
      string SBurHMJVoI;
      string aYDKoHWsVM;
      if(KOyJIkCnph == BroJxFkJCb){GJyZjWHIcP = true;}
      else if(BroJxFkJCb == KOyJIkCnph){hPyUUAeYaI = true;}
      if(VrMyAoxpcJ == MpZcDQAYJe){GgqtzkNZCz = true;}
      else if(MpZcDQAYJe == VrMyAoxpcJ){jKgKlMuZGU = true;}
      if(XunKTOcFny == HzWLYeSbqr){CHMJeoJlsH = true;}
      else if(HzWLYeSbqr == XunKTOcFny){qODZdUSDsM = true;}
      if(AOlfBAYjdW == QAMXKxCmcb){wCTYiJCUIk = true;}
      else if(QAMXKxCmcb == AOlfBAYjdW){RqgICrBGUN = true;}
      if(gcrExHYlIN == QoDgYjLQfy){EArZCtgJKD = true;}
      else if(QoDgYjLQfy == gcrExHYlIN){TmWGABfPaK = true;}
      if(RxPeWPZnps == jEqqhCVdjS){swpVKyxout = true;}
      else if(jEqqhCVdjS == RxPeWPZnps){mKQkHSLXqA = true;}
      if(HwzqhGFfxz == lJSKLLcBSG){NVPUTDMRKp = true;}
      else if(lJSKLLcBSG == HwzqhGFfxz){hbeOprcXHt = true;}
      if(QMMFctCjNM == NMwhOSuolo){hrQRuCOmHj = true;}
      if(pqwagCzGJl == SBurHMJVoI){HAaoOzMxOj = true;}
      if(ZktjOjcBWp == aYDKoHWsVM){LNZNXhjXFy = true;}
      while(NMwhOSuolo == QMMFctCjNM){LoFrADrxZc = true;}
      while(SBurHMJVoI == SBurHMJVoI){nCbiZHawBj = true;}
      while(aYDKoHWsVM == aYDKoHWsVM){gdPTfqIHPI = true;}
      if(GJyZjWHIcP == true){GJyZjWHIcP = false;}
      if(GgqtzkNZCz == true){GgqtzkNZCz = false;}
      if(CHMJeoJlsH == true){CHMJeoJlsH = false;}
      if(wCTYiJCUIk == true){wCTYiJCUIk = false;}
      if(EArZCtgJKD == true){EArZCtgJKD = false;}
      if(swpVKyxout == true){swpVKyxout = false;}
      if(NVPUTDMRKp == true){NVPUTDMRKp = false;}
      if(hrQRuCOmHj == true){hrQRuCOmHj = false;}
      if(HAaoOzMxOj == true){HAaoOzMxOj = false;}
      if(LNZNXhjXFy == true){LNZNXhjXFy = false;}
      if(hPyUUAeYaI == true){hPyUUAeYaI = false;}
      if(jKgKlMuZGU == true){jKgKlMuZGU = false;}
      if(qODZdUSDsM == true){qODZdUSDsM = false;}
      if(RqgICrBGUN == true){RqgICrBGUN = false;}
      if(TmWGABfPaK == true){TmWGABfPaK = false;}
      if(mKQkHSLXqA == true){mKQkHSLXqA = false;}
      if(hbeOprcXHt == true){hbeOprcXHt = false;}
      if(LoFrADrxZc == true){LoFrADrxZc = false;}
      if(nCbiZHawBj == true){nCbiZHawBj = false;}
      if(gdPTfqIHPI == true){gdPTfqIHPI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ADLQOHDPVI
{ 
  void nTjlESxsxj()
  { 
      bool bEkDNQdnLA = false;
      bool yjCjGDOnbK = false;
      bool KcXatWDUsb = false;
      bool VSIVSZXPRh = false;
      bool NjNULgoLcB = false;
      bool otnwqzfJJq = false;
      bool MJtjdebfQg = false;
      bool fyWtxZPDOM = false;
      bool hrqrlbeMeT = false;
      bool sNGaUDodqg = false;
      bool FJtwVqXsyR = false;
      bool jctwJUSCxC = false;
      bool APBxmRqwZs = false;
      bool jkMhHXxuWu = false;
      bool DkNMjQSKRz = false;
      bool kmgngpHxID = false;
      bool zbTFgyQMnk = false;
      bool WWfByPBnNV = false;
      bool ygeZHwEXBR = false;
      bool QAlSwbQHfk = false;
      string RsBHCRQqUa;
      string WgRlLNTxRz;
      string ADCtXffJjo;
      string EfXDumWkRx;
      string uQkeFTnbcC;
      string cyyrONpHiW;
      string lGHeWqIOqX;
      string phfUDjSXnE;
      string rDfgMFhfng;
      string xPCuLoIFHO;
      string KZkFLtSdnd;
      string uSSeehZZRR;
      string JbZJZafjJN;
      string aMPZsRSaUS;
      string lDqKkewWQc;
      string PimpFiAaek;
      string NhUaDiCrlM;
      string OyEzeFjPYu;
      string dJTfyrYYUK;
      string RrujFDiQGC;
      if(RsBHCRQqUa == KZkFLtSdnd){bEkDNQdnLA = true;}
      else if(KZkFLtSdnd == RsBHCRQqUa){FJtwVqXsyR = true;}
      if(WgRlLNTxRz == uSSeehZZRR){yjCjGDOnbK = true;}
      else if(uSSeehZZRR == WgRlLNTxRz){jctwJUSCxC = true;}
      if(ADCtXffJjo == JbZJZafjJN){KcXatWDUsb = true;}
      else if(JbZJZafjJN == ADCtXffJjo){APBxmRqwZs = true;}
      if(EfXDumWkRx == aMPZsRSaUS){VSIVSZXPRh = true;}
      else if(aMPZsRSaUS == EfXDumWkRx){jkMhHXxuWu = true;}
      if(uQkeFTnbcC == lDqKkewWQc){NjNULgoLcB = true;}
      else if(lDqKkewWQc == uQkeFTnbcC){DkNMjQSKRz = true;}
      if(cyyrONpHiW == PimpFiAaek){otnwqzfJJq = true;}
      else if(PimpFiAaek == cyyrONpHiW){kmgngpHxID = true;}
      if(lGHeWqIOqX == NhUaDiCrlM){MJtjdebfQg = true;}
      else if(NhUaDiCrlM == lGHeWqIOqX){zbTFgyQMnk = true;}
      if(phfUDjSXnE == OyEzeFjPYu){fyWtxZPDOM = true;}
      if(rDfgMFhfng == dJTfyrYYUK){hrqrlbeMeT = true;}
      if(xPCuLoIFHO == RrujFDiQGC){sNGaUDodqg = true;}
      while(OyEzeFjPYu == phfUDjSXnE){WWfByPBnNV = true;}
      while(dJTfyrYYUK == dJTfyrYYUK){ygeZHwEXBR = true;}
      while(RrujFDiQGC == RrujFDiQGC){QAlSwbQHfk = true;}
      if(bEkDNQdnLA == true){bEkDNQdnLA = false;}
      if(yjCjGDOnbK == true){yjCjGDOnbK = false;}
      if(KcXatWDUsb == true){KcXatWDUsb = false;}
      if(VSIVSZXPRh == true){VSIVSZXPRh = false;}
      if(NjNULgoLcB == true){NjNULgoLcB = false;}
      if(otnwqzfJJq == true){otnwqzfJJq = false;}
      if(MJtjdebfQg == true){MJtjdebfQg = false;}
      if(fyWtxZPDOM == true){fyWtxZPDOM = false;}
      if(hrqrlbeMeT == true){hrqrlbeMeT = false;}
      if(sNGaUDodqg == true){sNGaUDodqg = false;}
      if(FJtwVqXsyR == true){FJtwVqXsyR = false;}
      if(jctwJUSCxC == true){jctwJUSCxC = false;}
      if(APBxmRqwZs == true){APBxmRqwZs = false;}
      if(jkMhHXxuWu == true){jkMhHXxuWu = false;}
      if(DkNMjQSKRz == true){DkNMjQSKRz = false;}
      if(kmgngpHxID == true){kmgngpHxID = false;}
      if(zbTFgyQMnk == true){zbTFgyQMnk = false;}
      if(WWfByPBnNV == true){WWfByPBnNV = false;}
      if(ygeZHwEXBR == true){ygeZHwEXBR = false;}
      if(QAlSwbQHfk == true){QAlSwbQHfk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YPCAFIFYMY
{ 
  void eiFihyjAtV()
  { 
      bool lcsguZthAR = false;
      bool hBcqyUiUGl = false;
      bool ZblLjISacw = false;
      bool AEFShuqhLG = false;
      bool alnagWHjIs = false;
      bool ecdHJKpgwm = false;
      bool HTEEQcwJID = false;
      bool dBIALmmLeN = false;
      bool AiRiQXaxJX = false;
      bool EJkXzHgjJD = false;
      bool axaFPdTcwV = false;
      bool WeCimXBUms = false;
      bool CyAkyTQkBE = false;
      bool GDCalDHMTm = false;
      bool DxBmAZGCka = false;
      bool FLwPBbwpGu = false;
      bool MibrPTcbwi = false;
      bool QoBzpExMjX = false;
      bool NOzaytGlZJ = false;
      bool GRFXZTVIXg = false;
      string iVyZybFAPu;
      string nVAoRKHQfH;
      string OLQLklozJY;
      string DRxspZiVkk;
      string GeddMKJLbc;
      string ujSmnWEmnL;
      string mFqqrWYGzr;
      string akeuAjhmyZ;
      string ccXfdSyKFS;
      string UwhZyBmmlo;
      string lCMjBJEXlD;
      string oRnOiJhLMZ;
      string YNBfXeDFwz;
      string wtBJmZQndU;
      string NZXBdCHTpo;
      string TbZMQYBfMW;
      string FybmHtQeaJ;
      string sthrLypzCU;
      string XjOHfUTorO;
      string YkaHOOxkti;
      if(iVyZybFAPu == lCMjBJEXlD){lcsguZthAR = true;}
      else if(lCMjBJEXlD == iVyZybFAPu){axaFPdTcwV = true;}
      if(nVAoRKHQfH == oRnOiJhLMZ){hBcqyUiUGl = true;}
      else if(oRnOiJhLMZ == nVAoRKHQfH){WeCimXBUms = true;}
      if(OLQLklozJY == YNBfXeDFwz){ZblLjISacw = true;}
      else if(YNBfXeDFwz == OLQLklozJY){CyAkyTQkBE = true;}
      if(DRxspZiVkk == wtBJmZQndU){AEFShuqhLG = true;}
      else if(wtBJmZQndU == DRxspZiVkk){GDCalDHMTm = true;}
      if(GeddMKJLbc == NZXBdCHTpo){alnagWHjIs = true;}
      else if(NZXBdCHTpo == GeddMKJLbc){DxBmAZGCka = true;}
      if(ujSmnWEmnL == TbZMQYBfMW){ecdHJKpgwm = true;}
      else if(TbZMQYBfMW == ujSmnWEmnL){FLwPBbwpGu = true;}
      if(mFqqrWYGzr == FybmHtQeaJ){HTEEQcwJID = true;}
      else if(FybmHtQeaJ == mFqqrWYGzr){MibrPTcbwi = true;}
      if(akeuAjhmyZ == sthrLypzCU){dBIALmmLeN = true;}
      if(ccXfdSyKFS == XjOHfUTorO){AiRiQXaxJX = true;}
      if(UwhZyBmmlo == YkaHOOxkti){EJkXzHgjJD = true;}
      while(sthrLypzCU == akeuAjhmyZ){QoBzpExMjX = true;}
      while(XjOHfUTorO == XjOHfUTorO){NOzaytGlZJ = true;}
      while(YkaHOOxkti == YkaHOOxkti){GRFXZTVIXg = true;}
      if(lcsguZthAR == true){lcsguZthAR = false;}
      if(hBcqyUiUGl == true){hBcqyUiUGl = false;}
      if(ZblLjISacw == true){ZblLjISacw = false;}
      if(AEFShuqhLG == true){AEFShuqhLG = false;}
      if(alnagWHjIs == true){alnagWHjIs = false;}
      if(ecdHJKpgwm == true){ecdHJKpgwm = false;}
      if(HTEEQcwJID == true){HTEEQcwJID = false;}
      if(dBIALmmLeN == true){dBIALmmLeN = false;}
      if(AiRiQXaxJX == true){AiRiQXaxJX = false;}
      if(EJkXzHgjJD == true){EJkXzHgjJD = false;}
      if(axaFPdTcwV == true){axaFPdTcwV = false;}
      if(WeCimXBUms == true){WeCimXBUms = false;}
      if(CyAkyTQkBE == true){CyAkyTQkBE = false;}
      if(GDCalDHMTm == true){GDCalDHMTm = false;}
      if(DxBmAZGCka == true){DxBmAZGCka = false;}
      if(FLwPBbwpGu == true){FLwPBbwpGu = false;}
      if(MibrPTcbwi == true){MibrPTcbwi = false;}
      if(QoBzpExMjX == true){QoBzpExMjX = false;}
      if(NOzaytGlZJ == true){NOzaytGlZJ = false;}
      if(GRFXZTVIXg == true){GRFXZTVIXg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKMNEAMEKB
{ 
  void fbKXKezuUd()
  { 
      bool hJoQGmipll = false;
      bool xAWfAbSfdC = false;
      bool wIfdTEsaKR = false;
      bool yYMNqIRygp = false;
      bool kKUnFhrSuJ = false;
      bool szkKcZdLwC = false;
      bool sHeUnXnJoq = false;
      bool JUynQlmqXl = false;
      bool LaeBYynCjQ = false;
      bool eGCexceAAh = false;
      bool thcEzYAxsq = false;
      bool mlmKqRbduo = false;
      bool jkZXMDRTpm = false;
      bool GlppqdxaBA = false;
      bool ypIsdrSqne = false;
      bool BAELxIIEqu = false;
      bool GfGGjAuxSM = false;
      bool UAbuptcftT = false;
      bool kafLlGgerh = false;
      bool UrjGtRiBId = false;
      string OxnsULCRLd;
      string TjgrGCXBmq;
      string IpqAiPZXQO;
      string rDlsdtDClF;
      string GqAbMwWgpA;
      string hgSAMYFmJF;
      string keBxkPynNM;
      string zVPhjQoPnm;
      string rrhPgLklfE;
      string nPrgTbpDpw;
      string xiScBLQjPw;
      string iozVMswkQY;
      string eLIIXiciOI;
      string ZlYroJZENU;
      string tAWiVyQVTZ;
      string eFlQQlZKFS;
      string ihUHWwQGgD;
      string TrWwddoYmY;
      string SGOncUAHaD;
      string iPyukMfPMY;
      if(OxnsULCRLd == xiScBLQjPw){hJoQGmipll = true;}
      else if(xiScBLQjPw == OxnsULCRLd){thcEzYAxsq = true;}
      if(TjgrGCXBmq == iozVMswkQY){xAWfAbSfdC = true;}
      else if(iozVMswkQY == TjgrGCXBmq){mlmKqRbduo = true;}
      if(IpqAiPZXQO == eLIIXiciOI){wIfdTEsaKR = true;}
      else if(eLIIXiciOI == IpqAiPZXQO){jkZXMDRTpm = true;}
      if(rDlsdtDClF == ZlYroJZENU){yYMNqIRygp = true;}
      else if(ZlYroJZENU == rDlsdtDClF){GlppqdxaBA = true;}
      if(GqAbMwWgpA == tAWiVyQVTZ){kKUnFhrSuJ = true;}
      else if(tAWiVyQVTZ == GqAbMwWgpA){ypIsdrSqne = true;}
      if(hgSAMYFmJF == eFlQQlZKFS){szkKcZdLwC = true;}
      else if(eFlQQlZKFS == hgSAMYFmJF){BAELxIIEqu = true;}
      if(keBxkPynNM == ihUHWwQGgD){sHeUnXnJoq = true;}
      else if(ihUHWwQGgD == keBxkPynNM){GfGGjAuxSM = true;}
      if(zVPhjQoPnm == TrWwddoYmY){JUynQlmqXl = true;}
      if(rrhPgLklfE == SGOncUAHaD){LaeBYynCjQ = true;}
      if(nPrgTbpDpw == iPyukMfPMY){eGCexceAAh = true;}
      while(TrWwddoYmY == zVPhjQoPnm){UAbuptcftT = true;}
      while(SGOncUAHaD == SGOncUAHaD){kafLlGgerh = true;}
      while(iPyukMfPMY == iPyukMfPMY){UrjGtRiBId = true;}
      if(hJoQGmipll == true){hJoQGmipll = false;}
      if(xAWfAbSfdC == true){xAWfAbSfdC = false;}
      if(wIfdTEsaKR == true){wIfdTEsaKR = false;}
      if(yYMNqIRygp == true){yYMNqIRygp = false;}
      if(kKUnFhrSuJ == true){kKUnFhrSuJ = false;}
      if(szkKcZdLwC == true){szkKcZdLwC = false;}
      if(sHeUnXnJoq == true){sHeUnXnJoq = false;}
      if(JUynQlmqXl == true){JUynQlmqXl = false;}
      if(LaeBYynCjQ == true){LaeBYynCjQ = false;}
      if(eGCexceAAh == true){eGCexceAAh = false;}
      if(thcEzYAxsq == true){thcEzYAxsq = false;}
      if(mlmKqRbduo == true){mlmKqRbduo = false;}
      if(jkZXMDRTpm == true){jkZXMDRTpm = false;}
      if(GlppqdxaBA == true){GlppqdxaBA = false;}
      if(ypIsdrSqne == true){ypIsdrSqne = false;}
      if(BAELxIIEqu == true){BAELxIIEqu = false;}
      if(GfGGjAuxSM == true){GfGGjAuxSM = false;}
      if(UAbuptcftT == true){UAbuptcftT = false;}
      if(kafLlGgerh == true){kafLlGgerh = false;}
      if(UrjGtRiBId == true){UrjGtRiBId = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XLONRWHMYI
{ 
  void tcQTbTjckV()
  { 
      bool OFpZjRMPFx = false;
      bool IPBYTIDWXR = false;
      bool hHJdFXoGtZ = false;
      bool jAEmJoSBqr = false;
      bool hNPNAJPQSP = false;
      bool HpXUuGuMUM = false;
      bool bFUeNHLNOd = false;
      bool pCeeiUqwcu = false;
      bool HYneStbjrD = false;
      bool tGfeQcrkzs = false;
      bool yCBoZFKska = false;
      bool OyjZEDRpMS = false;
      bool eaVLijVAOF = false;
      bool cGxjwEXyEN = false;
      bool jiyQnwVGZN = false;
      bool LBXgNXgoGp = false;
      bool iJdfxHBzcz = false;
      bool eSkziwcEXl = false;
      bool NPZBtahPWY = false;
      bool XirOdZESTf = false;
      string rHPYNpbXgr;
      string gVdRMICDjt;
      string jLgfYZGMrX;
      string MMacuKkgFi;
      string bgDzWbxwOG;
      string aKBHQgZjAn;
      string jOfIeTtBVB;
      string WUyBSCHhIx;
      string bJykxCLSMO;
      string kBgQzMBtTD;
      string guZMjFLAnN;
      string YraDLZPuKb;
      string IaoHQUmgBG;
      string BMNFPfjkBq;
      string pLdyorZdFZ;
      string wGjqtFGSwO;
      string SeyhMLdUme;
      string odsTlxxpRX;
      string uJabKucVKJ;
      string ZRolYLMwld;
      if(rHPYNpbXgr == guZMjFLAnN){OFpZjRMPFx = true;}
      else if(guZMjFLAnN == rHPYNpbXgr){yCBoZFKska = true;}
      if(gVdRMICDjt == YraDLZPuKb){IPBYTIDWXR = true;}
      else if(YraDLZPuKb == gVdRMICDjt){OyjZEDRpMS = true;}
      if(jLgfYZGMrX == IaoHQUmgBG){hHJdFXoGtZ = true;}
      else if(IaoHQUmgBG == jLgfYZGMrX){eaVLijVAOF = true;}
      if(MMacuKkgFi == BMNFPfjkBq){jAEmJoSBqr = true;}
      else if(BMNFPfjkBq == MMacuKkgFi){cGxjwEXyEN = true;}
      if(bgDzWbxwOG == pLdyorZdFZ){hNPNAJPQSP = true;}
      else if(pLdyorZdFZ == bgDzWbxwOG){jiyQnwVGZN = true;}
      if(aKBHQgZjAn == wGjqtFGSwO){HpXUuGuMUM = true;}
      else if(wGjqtFGSwO == aKBHQgZjAn){LBXgNXgoGp = true;}
      if(jOfIeTtBVB == SeyhMLdUme){bFUeNHLNOd = true;}
      else if(SeyhMLdUme == jOfIeTtBVB){iJdfxHBzcz = true;}
      if(WUyBSCHhIx == odsTlxxpRX){pCeeiUqwcu = true;}
      if(bJykxCLSMO == uJabKucVKJ){HYneStbjrD = true;}
      if(kBgQzMBtTD == ZRolYLMwld){tGfeQcrkzs = true;}
      while(odsTlxxpRX == WUyBSCHhIx){eSkziwcEXl = true;}
      while(uJabKucVKJ == uJabKucVKJ){NPZBtahPWY = true;}
      while(ZRolYLMwld == ZRolYLMwld){XirOdZESTf = true;}
      if(OFpZjRMPFx == true){OFpZjRMPFx = false;}
      if(IPBYTIDWXR == true){IPBYTIDWXR = false;}
      if(hHJdFXoGtZ == true){hHJdFXoGtZ = false;}
      if(jAEmJoSBqr == true){jAEmJoSBqr = false;}
      if(hNPNAJPQSP == true){hNPNAJPQSP = false;}
      if(HpXUuGuMUM == true){HpXUuGuMUM = false;}
      if(bFUeNHLNOd == true){bFUeNHLNOd = false;}
      if(pCeeiUqwcu == true){pCeeiUqwcu = false;}
      if(HYneStbjrD == true){HYneStbjrD = false;}
      if(tGfeQcrkzs == true){tGfeQcrkzs = false;}
      if(yCBoZFKska == true){yCBoZFKska = false;}
      if(OyjZEDRpMS == true){OyjZEDRpMS = false;}
      if(eaVLijVAOF == true){eaVLijVAOF = false;}
      if(cGxjwEXyEN == true){cGxjwEXyEN = false;}
      if(jiyQnwVGZN == true){jiyQnwVGZN = false;}
      if(LBXgNXgoGp == true){LBXgNXgoGp = false;}
      if(iJdfxHBzcz == true){iJdfxHBzcz = false;}
      if(eSkziwcEXl == true){eSkziwcEXl = false;}
      if(NPZBtahPWY == true){NPZBtahPWY = false;}
      if(XirOdZESTf == true){XirOdZESTf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KUZHTCHTRU
{ 
  void cMqEtqNhoK()
  { 
      bool JmnNLwYgrq = false;
      bool pVVFlRkjFA = false;
      bool tTYxIwhBGD = false;
      bool LLEInGildw = false;
      bool KgQZkRFhfy = false;
      bool FJYxypOpEP = false;
      bool OXanfeRNQe = false;
      bool izFIoMDzMq = false;
      bool pAVIyBlGKy = false;
      bool rrgOhmGbsG = false;
      bool zrQAOGEQIk = false;
      bool lOdMYOBSpd = false;
      bool sKCSlqRpaC = false;
      bool GaFFqxiUsr = false;
      bool xUyYLdNUpS = false;
      bool kmlPMopxNX = false;
      bool nOpFdLIXUa = false;
      bool egYygXMcGI = false;
      bool cxAHQSopsC = false;
      bool HkGVDiertA = false;
      string PMqJfnKnxa;
      string CzbkXfUSyP;
      string WoqBSFkQRn;
      string nHpwEdXmrM;
      string YhorQJlIiM;
      string ITmBBaUoqZ;
      string CtWImtIegt;
      string HhalpnzzkI;
      string ScgEfTUnuc;
      string IiwRKeLgFW;
      string AHboFasBKM;
      string bVEhHZMSbT;
      string YTjDkYkJaL;
      string cStOIKAqyF;
      string ZTdhBldNJk;
      string RsEkxfXXEg;
      string ojZzjIbpZw;
      string YUTWsFpBBy;
      string tWzpsjOIQb;
      string mbmRQpsexs;
      if(PMqJfnKnxa == AHboFasBKM){JmnNLwYgrq = true;}
      else if(AHboFasBKM == PMqJfnKnxa){zrQAOGEQIk = true;}
      if(CzbkXfUSyP == bVEhHZMSbT){pVVFlRkjFA = true;}
      else if(bVEhHZMSbT == CzbkXfUSyP){lOdMYOBSpd = true;}
      if(WoqBSFkQRn == YTjDkYkJaL){tTYxIwhBGD = true;}
      else if(YTjDkYkJaL == WoqBSFkQRn){sKCSlqRpaC = true;}
      if(nHpwEdXmrM == cStOIKAqyF){LLEInGildw = true;}
      else if(cStOIKAqyF == nHpwEdXmrM){GaFFqxiUsr = true;}
      if(YhorQJlIiM == ZTdhBldNJk){KgQZkRFhfy = true;}
      else if(ZTdhBldNJk == YhorQJlIiM){xUyYLdNUpS = true;}
      if(ITmBBaUoqZ == RsEkxfXXEg){FJYxypOpEP = true;}
      else if(RsEkxfXXEg == ITmBBaUoqZ){kmlPMopxNX = true;}
      if(CtWImtIegt == ojZzjIbpZw){OXanfeRNQe = true;}
      else if(ojZzjIbpZw == CtWImtIegt){nOpFdLIXUa = true;}
      if(HhalpnzzkI == YUTWsFpBBy){izFIoMDzMq = true;}
      if(ScgEfTUnuc == tWzpsjOIQb){pAVIyBlGKy = true;}
      if(IiwRKeLgFW == mbmRQpsexs){rrgOhmGbsG = true;}
      while(YUTWsFpBBy == HhalpnzzkI){egYygXMcGI = true;}
      while(tWzpsjOIQb == tWzpsjOIQb){cxAHQSopsC = true;}
      while(mbmRQpsexs == mbmRQpsexs){HkGVDiertA = true;}
      if(JmnNLwYgrq == true){JmnNLwYgrq = false;}
      if(pVVFlRkjFA == true){pVVFlRkjFA = false;}
      if(tTYxIwhBGD == true){tTYxIwhBGD = false;}
      if(LLEInGildw == true){LLEInGildw = false;}
      if(KgQZkRFhfy == true){KgQZkRFhfy = false;}
      if(FJYxypOpEP == true){FJYxypOpEP = false;}
      if(OXanfeRNQe == true){OXanfeRNQe = false;}
      if(izFIoMDzMq == true){izFIoMDzMq = false;}
      if(pAVIyBlGKy == true){pAVIyBlGKy = false;}
      if(rrgOhmGbsG == true){rrgOhmGbsG = false;}
      if(zrQAOGEQIk == true){zrQAOGEQIk = false;}
      if(lOdMYOBSpd == true){lOdMYOBSpd = false;}
      if(sKCSlqRpaC == true){sKCSlqRpaC = false;}
      if(GaFFqxiUsr == true){GaFFqxiUsr = false;}
      if(xUyYLdNUpS == true){xUyYLdNUpS = false;}
      if(kmlPMopxNX == true){kmlPMopxNX = false;}
      if(nOpFdLIXUa == true){nOpFdLIXUa = false;}
      if(egYygXMcGI == true){egYygXMcGI = false;}
      if(cxAHQSopsC == true){cxAHQSopsC = false;}
      if(HkGVDiertA == true){HkGVDiertA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LCJLDKPKNE
{ 
  void iUOgnrFaoj()
  { 
      bool kkOcWtszkt = false;
      bool ZswppUbBVG = false;
      bool YDighTqnHY = false;
      bool EQckdilnqa = false;
      bool EAtLJZslkm = false;
      bool NxruFhCgtD = false;
      bool CErLoIPLLG = false;
      bool inJuBYIWWH = false;
      bool ZEDULHYheu = false;
      bool gEsnXzHiWB = false;
      bool KhadDZmwtg = false;
      bool ZeKldyBWAh = false;
      bool jhfQZetVXB = false;
      bool QZAVxqdYQl = false;
      bool UbmyVBsHKZ = false;
      bool ykinQcCJEY = false;
      bool eQYrPzdonl = false;
      bool TbGNNItguX = false;
      bool kmLxCfqLEU = false;
      bool oUTrGDCuhV = false;
      string OpnTNyAJWx;
      string PWDFoykgPn;
      string VEzbjSKbPy;
      string aWFyzYgUQd;
      string oEgUHGQhFW;
      string SExZdKqMjt;
      string mYtYVrQFGQ;
      string QQQlzRWdTd;
      string CcWreWZfTo;
      string gUkVqQKIyP;
      string oKbnGBnLZM;
      string mNsFrKCBsy;
      string RklQiwftui;
      string HOeDnqAhld;
      string iOFGCTaedf;
      string OIOAxEXKFK;
      string VsPqEXhoQA;
      string JTPPPDeeOP;
      string UAQOUyzeGj;
      string SpcaHpyOBd;
      if(OpnTNyAJWx == oKbnGBnLZM){kkOcWtszkt = true;}
      else if(oKbnGBnLZM == OpnTNyAJWx){KhadDZmwtg = true;}
      if(PWDFoykgPn == mNsFrKCBsy){ZswppUbBVG = true;}
      else if(mNsFrKCBsy == PWDFoykgPn){ZeKldyBWAh = true;}
      if(VEzbjSKbPy == RklQiwftui){YDighTqnHY = true;}
      else if(RklQiwftui == VEzbjSKbPy){jhfQZetVXB = true;}
      if(aWFyzYgUQd == HOeDnqAhld){EQckdilnqa = true;}
      else if(HOeDnqAhld == aWFyzYgUQd){QZAVxqdYQl = true;}
      if(oEgUHGQhFW == iOFGCTaedf){EAtLJZslkm = true;}
      else if(iOFGCTaedf == oEgUHGQhFW){UbmyVBsHKZ = true;}
      if(SExZdKqMjt == OIOAxEXKFK){NxruFhCgtD = true;}
      else if(OIOAxEXKFK == SExZdKqMjt){ykinQcCJEY = true;}
      if(mYtYVrQFGQ == VsPqEXhoQA){CErLoIPLLG = true;}
      else if(VsPqEXhoQA == mYtYVrQFGQ){eQYrPzdonl = true;}
      if(QQQlzRWdTd == JTPPPDeeOP){inJuBYIWWH = true;}
      if(CcWreWZfTo == UAQOUyzeGj){ZEDULHYheu = true;}
      if(gUkVqQKIyP == SpcaHpyOBd){gEsnXzHiWB = true;}
      while(JTPPPDeeOP == QQQlzRWdTd){TbGNNItguX = true;}
      while(UAQOUyzeGj == UAQOUyzeGj){kmLxCfqLEU = true;}
      while(SpcaHpyOBd == SpcaHpyOBd){oUTrGDCuhV = true;}
      if(kkOcWtszkt == true){kkOcWtszkt = false;}
      if(ZswppUbBVG == true){ZswppUbBVG = false;}
      if(YDighTqnHY == true){YDighTqnHY = false;}
      if(EQckdilnqa == true){EQckdilnqa = false;}
      if(EAtLJZslkm == true){EAtLJZslkm = false;}
      if(NxruFhCgtD == true){NxruFhCgtD = false;}
      if(CErLoIPLLG == true){CErLoIPLLG = false;}
      if(inJuBYIWWH == true){inJuBYIWWH = false;}
      if(ZEDULHYheu == true){ZEDULHYheu = false;}
      if(gEsnXzHiWB == true){gEsnXzHiWB = false;}
      if(KhadDZmwtg == true){KhadDZmwtg = false;}
      if(ZeKldyBWAh == true){ZeKldyBWAh = false;}
      if(jhfQZetVXB == true){jhfQZetVXB = false;}
      if(QZAVxqdYQl == true){QZAVxqdYQl = false;}
      if(UbmyVBsHKZ == true){UbmyVBsHKZ = false;}
      if(ykinQcCJEY == true){ykinQcCJEY = false;}
      if(eQYrPzdonl == true){eQYrPzdonl = false;}
      if(TbGNNItguX == true){TbGNNItguX = false;}
      if(kmLxCfqLEU == true){kmLxCfqLEU = false;}
      if(oUTrGDCuhV == true){oUTrGDCuhV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SHGOJCJJGV
{ 
  void MqVGXfCnbm()
  { 
      bool ZQUpdqfwBZ = false;
      bool QBlgDKhtKJ = false;
      bool QInsDBUdeK = false;
      bool trglSBDfEc = false;
      bool JJzuDiZQVx = false;
      bool WqlCNRbamb = false;
      bool WCQqfYTzOB = false;
      bool GBpgAHIsoT = false;
      bool bDHhmDFeYB = false;
      bool YbsbFGrHPe = false;
      bool OaCTpVBFBG = false;
      bool IilSATtiDb = false;
      bool ToaMbdHNbs = false;
      bool OBdKFAAmrR = false;
      bool CAcSrppZbl = false;
      bool MJEmLYzprL = false;
      bool NmcIqHEaNz = false;
      bool TGqlZTMITl = false;
      bool nhkogEwqzf = false;
      bool AKufDOWTak = false;
      string mPwQLEiyHH;
      string YoIObjqngF;
      string BWiicRoOlz;
      string TPiSfpaLpk;
      string WsUcIdnEnZ;
      string TDztgQfMnt;
      string OTLHnJFphk;
      string IexwiHCGay;
      string ckaMePPnkP;
      string JNXwVDhMoz;
      string XyVCQoGCLY;
      string NZloRdrycY;
      string sRESbtGBZf;
      string ZpQbadPYup;
      string JNcLBibidr;
      string KijQFFtCZV;
      string hEbezXIKNm;
      string OSDmOfosQs;
      string SXWhUpGAVU;
      string jMyYHEkxLd;
      if(mPwQLEiyHH == XyVCQoGCLY){ZQUpdqfwBZ = true;}
      else if(XyVCQoGCLY == mPwQLEiyHH){OaCTpVBFBG = true;}
      if(YoIObjqngF == NZloRdrycY){QBlgDKhtKJ = true;}
      else if(NZloRdrycY == YoIObjqngF){IilSATtiDb = true;}
      if(BWiicRoOlz == sRESbtGBZf){QInsDBUdeK = true;}
      else if(sRESbtGBZf == BWiicRoOlz){ToaMbdHNbs = true;}
      if(TPiSfpaLpk == ZpQbadPYup){trglSBDfEc = true;}
      else if(ZpQbadPYup == TPiSfpaLpk){OBdKFAAmrR = true;}
      if(WsUcIdnEnZ == JNcLBibidr){JJzuDiZQVx = true;}
      else if(JNcLBibidr == WsUcIdnEnZ){CAcSrppZbl = true;}
      if(TDztgQfMnt == KijQFFtCZV){WqlCNRbamb = true;}
      else if(KijQFFtCZV == TDztgQfMnt){MJEmLYzprL = true;}
      if(OTLHnJFphk == hEbezXIKNm){WCQqfYTzOB = true;}
      else if(hEbezXIKNm == OTLHnJFphk){NmcIqHEaNz = true;}
      if(IexwiHCGay == OSDmOfosQs){GBpgAHIsoT = true;}
      if(ckaMePPnkP == SXWhUpGAVU){bDHhmDFeYB = true;}
      if(JNXwVDhMoz == jMyYHEkxLd){YbsbFGrHPe = true;}
      while(OSDmOfosQs == IexwiHCGay){TGqlZTMITl = true;}
      while(SXWhUpGAVU == SXWhUpGAVU){nhkogEwqzf = true;}
      while(jMyYHEkxLd == jMyYHEkxLd){AKufDOWTak = true;}
      if(ZQUpdqfwBZ == true){ZQUpdqfwBZ = false;}
      if(QBlgDKhtKJ == true){QBlgDKhtKJ = false;}
      if(QInsDBUdeK == true){QInsDBUdeK = false;}
      if(trglSBDfEc == true){trglSBDfEc = false;}
      if(JJzuDiZQVx == true){JJzuDiZQVx = false;}
      if(WqlCNRbamb == true){WqlCNRbamb = false;}
      if(WCQqfYTzOB == true){WCQqfYTzOB = false;}
      if(GBpgAHIsoT == true){GBpgAHIsoT = false;}
      if(bDHhmDFeYB == true){bDHhmDFeYB = false;}
      if(YbsbFGrHPe == true){YbsbFGrHPe = false;}
      if(OaCTpVBFBG == true){OaCTpVBFBG = false;}
      if(IilSATtiDb == true){IilSATtiDb = false;}
      if(ToaMbdHNbs == true){ToaMbdHNbs = false;}
      if(OBdKFAAmrR == true){OBdKFAAmrR = false;}
      if(CAcSrppZbl == true){CAcSrppZbl = false;}
      if(MJEmLYzprL == true){MJEmLYzprL = false;}
      if(NmcIqHEaNz == true){NmcIqHEaNz = false;}
      if(TGqlZTMITl == true){TGqlZTMITl = false;}
      if(nhkogEwqzf == true){nhkogEwqzf = false;}
      if(AKufDOWTak == true){AKufDOWTak = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DQSSMDUKUZ
{ 
  void HkGCLtMyna()
  { 
      bool REElpWZBgy = false;
      bool tnqPuOZqwW = false;
      bool ZKmoKcbmYy = false;
      bool RidwNNEtTH = false;
      bool PCuOOqFhxP = false;
      bool mAfalGQPbN = false;
      bool umchgLJuCg = false;
      bool KeWoHWPYZS = false;
      bool WtoIKQDDKH = false;
      bool xnSGMbZMgC = false;
      bool hKfPFIdqSO = false;
      bool qqoIpAxTXP = false;
      bool IFjtjVLQbe = false;
      bool wCqXjMOZDC = false;
      bool mLjuPGyJPL = false;
      bool eFoRtcZkfi = false;
      bool wNOnRozRYd = false;
      bool lXQUcwUned = false;
      bool XBAQzqMZcH = false;
      bool lcsTFZxuda = false;
      string kqbptjAHwn;
      string oieOPhATRG;
      string OamWmKTFbC;
      string WOIVmRhVxD;
      string MXFqmyLYek;
      string PlqyAJDFDj;
      string QtesRaZIay;
      string zeVNtpVuin;
      string ytaqmjWJUd;
      string NbRNmRsLZM;
      string XDxgkjPcEK;
      string nIWOkWTmGg;
      string DQmxkWMIac;
      string wJUVQuwtGC;
      string UtEKoEFDbQ;
      string xGFsIGPzuN;
      string XGBbNdmByp;
      string ZZfDMJLbHf;
      string RJgKepEbNJ;
      string exyseNrcxL;
      if(kqbptjAHwn == XDxgkjPcEK){REElpWZBgy = true;}
      else if(XDxgkjPcEK == kqbptjAHwn){hKfPFIdqSO = true;}
      if(oieOPhATRG == nIWOkWTmGg){tnqPuOZqwW = true;}
      else if(nIWOkWTmGg == oieOPhATRG){qqoIpAxTXP = true;}
      if(OamWmKTFbC == DQmxkWMIac){ZKmoKcbmYy = true;}
      else if(DQmxkWMIac == OamWmKTFbC){IFjtjVLQbe = true;}
      if(WOIVmRhVxD == wJUVQuwtGC){RidwNNEtTH = true;}
      else if(wJUVQuwtGC == WOIVmRhVxD){wCqXjMOZDC = true;}
      if(MXFqmyLYek == UtEKoEFDbQ){PCuOOqFhxP = true;}
      else if(UtEKoEFDbQ == MXFqmyLYek){mLjuPGyJPL = true;}
      if(PlqyAJDFDj == xGFsIGPzuN){mAfalGQPbN = true;}
      else if(xGFsIGPzuN == PlqyAJDFDj){eFoRtcZkfi = true;}
      if(QtesRaZIay == XGBbNdmByp){umchgLJuCg = true;}
      else if(XGBbNdmByp == QtesRaZIay){wNOnRozRYd = true;}
      if(zeVNtpVuin == ZZfDMJLbHf){KeWoHWPYZS = true;}
      if(ytaqmjWJUd == RJgKepEbNJ){WtoIKQDDKH = true;}
      if(NbRNmRsLZM == exyseNrcxL){xnSGMbZMgC = true;}
      while(ZZfDMJLbHf == zeVNtpVuin){lXQUcwUned = true;}
      while(RJgKepEbNJ == RJgKepEbNJ){XBAQzqMZcH = true;}
      while(exyseNrcxL == exyseNrcxL){lcsTFZxuda = true;}
      if(REElpWZBgy == true){REElpWZBgy = false;}
      if(tnqPuOZqwW == true){tnqPuOZqwW = false;}
      if(ZKmoKcbmYy == true){ZKmoKcbmYy = false;}
      if(RidwNNEtTH == true){RidwNNEtTH = false;}
      if(PCuOOqFhxP == true){PCuOOqFhxP = false;}
      if(mAfalGQPbN == true){mAfalGQPbN = false;}
      if(umchgLJuCg == true){umchgLJuCg = false;}
      if(KeWoHWPYZS == true){KeWoHWPYZS = false;}
      if(WtoIKQDDKH == true){WtoIKQDDKH = false;}
      if(xnSGMbZMgC == true){xnSGMbZMgC = false;}
      if(hKfPFIdqSO == true){hKfPFIdqSO = false;}
      if(qqoIpAxTXP == true){qqoIpAxTXP = false;}
      if(IFjtjVLQbe == true){IFjtjVLQbe = false;}
      if(wCqXjMOZDC == true){wCqXjMOZDC = false;}
      if(mLjuPGyJPL == true){mLjuPGyJPL = false;}
      if(eFoRtcZkfi == true){eFoRtcZkfi = false;}
      if(wNOnRozRYd == true){wNOnRozRYd = false;}
      if(lXQUcwUned == true){lXQUcwUned = false;}
      if(XBAQzqMZcH == true){XBAQzqMZcH = false;}
      if(lcsTFZxuda == true){lcsTFZxuda = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NWXNWMMJOH
{ 
  void bSaCkCEzPL()
  { 
      bool ebLzUEfKcS = false;
      bool XaUbFhnrDw = false;
      bool AiVSiUiOhb = false;
      bool yZgPrGEjGE = false;
      bool UMezuWziiH = false;
      bool LWPVZwFsPz = false;
      bool VRcAUysEjz = false;
      bool cElyanEWXL = false;
      bool VAeZQaKKou = false;
      bool ALTGiDjddw = false;
      bool ctyjeHkQtl = false;
      bool qiVEdVlCjt = false;
      bool miPnzRjeOX = false;
      bool DZsaiaButJ = false;
      bool osPDEQoPcN = false;
      bool QgtiJteKjN = false;
      bool WGBWhQpuUC = false;
      bool TqHaFsSLjh = false;
      bool bUBBGWfJQn = false;
      bool upKglhrsUm = false;
      string pWEpaBeDOR;
      string rMxZbUAAyZ;
      string VLtosKzVFz;
      string CIkkHFSRzg;
      string MRKXMRASQn;
      string xoVimebPxP;
      string BJyOPibMRW;
      string BiAQMEBWba;
      string KfEQCNmCyc;
      string cDTjfDSuIc;
      string pnAtmNnEVi;
      string dFmVEUEhMC;
      string wYNotyOPkI;
      string kFOzjWfKdn;
      string YifOyWPxfK;
      string zjhGgQZLzn;
      string yXSNxXqnlg;
      string otEXcNsypX;
      string hQiaJBWHRS;
      string xUKopAPSRa;
      if(pWEpaBeDOR == pnAtmNnEVi){ebLzUEfKcS = true;}
      else if(pnAtmNnEVi == pWEpaBeDOR){ctyjeHkQtl = true;}
      if(rMxZbUAAyZ == dFmVEUEhMC){XaUbFhnrDw = true;}
      else if(dFmVEUEhMC == rMxZbUAAyZ){qiVEdVlCjt = true;}
      if(VLtosKzVFz == wYNotyOPkI){AiVSiUiOhb = true;}
      else if(wYNotyOPkI == VLtosKzVFz){miPnzRjeOX = true;}
      if(CIkkHFSRzg == kFOzjWfKdn){yZgPrGEjGE = true;}
      else if(kFOzjWfKdn == CIkkHFSRzg){DZsaiaButJ = true;}
      if(MRKXMRASQn == YifOyWPxfK){UMezuWziiH = true;}
      else if(YifOyWPxfK == MRKXMRASQn){osPDEQoPcN = true;}
      if(xoVimebPxP == zjhGgQZLzn){LWPVZwFsPz = true;}
      else if(zjhGgQZLzn == xoVimebPxP){QgtiJteKjN = true;}
      if(BJyOPibMRW == yXSNxXqnlg){VRcAUysEjz = true;}
      else if(yXSNxXqnlg == BJyOPibMRW){WGBWhQpuUC = true;}
      if(BiAQMEBWba == otEXcNsypX){cElyanEWXL = true;}
      if(KfEQCNmCyc == hQiaJBWHRS){VAeZQaKKou = true;}
      if(cDTjfDSuIc == xUKopAPSRa){ALTGiDjddw = true;}
      while(otEXcNsypX == BiAQMEBWba){TqHaFsSLjh = true;}
      while(hQiaJBWHRS == hQiaJBWHRS){bUBBGWfJQn = true;}
      while(xUKopAPSRa == xUKopAPSRa){upKglhrsUm = true;}
      if(ebLzUEfKcS == true){ebLzUEfKcS = false;}
      if(XaUbFhnrDw == true){XaUbFhnrDw = false;}
      if(AiVSiUiOhb == true){AiVSiUiOhb = false;}
      if(yZgPrGEjGE == true){yZgPrGEjGE = false;}
      if(UMezuWziiH == true){UMezuWziiH = false;}
      if(LWPVZwFsPz == true){LWPVZwFsPz = false;}
      if(VRcAUysEjz == true){VRcAUysEjz = false;}
      if(cElyanEWXL == true){cElyanEWXL = false;}
      if(VAeZQaKKou == true){VAeZQaKKou = false;}
      if(ALTGiDjddw == true){ALTGiDjddw = false;}
      if(ctyjeHkQtl == true){ctyjeHkQtl = false;}
      if(qiVEdVlCjt == true){qiVEdVlCjt = false;}
      if(miPnzRjeOX == true){miPnzRjeOX = false;}
      if(DZsaiaButJ == true){DZsaiaButJ = false;}
      if(osPDEQoPcN == true){osPDEQoPcN = false;}
      if(QgtiJteKjN == true){QgtiJteKjN = false;}
      if(WGBWhQpuUC == true){WGBWhQpuUC = false;}
      if(TqHaFsSLjh == true){TqHaFsSLjh = false;}
      if(bUBBGWfJQn == true){bUBBGWfJQn = false;}
      if(upKglhrsUm == true){upKglhrsUm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MUAXLOMOZP
{ 
  void apNNXBzeor()
  { 
      bool TqjcUncGfC = false;
      bool kLxdDUYsIG = false;
      bool bHbPRJCxDT = false;
      bool rHExMDiAVD = false;
      bool FjmsoGGyhl = false;
      bool BrZfNLPUKK = false;
      bool keCLJdGzQA = false;
      bool lYXEArUhaK = false;
      bool DDOQRAgXjB = false;
      bool mNoKRZgaiK = false;
      bool zGhgAcUUeU = false;
      bool qgtzHhPltI = false;
      bool wiPPMXiMmZ = false;
      bool LszPKxUgPo = false;
      bool fMrOKGSpDi = false;
      bool KugaOQpSTc = false;
      bool tHhFJxhenJ = false;
      bool MhVFbjpAEG = false;
      bool EsIDPQLYAs = false;
      bool GCMmtXdmFM = false;
      string iLSKlIqhyX;
      string VPyNcoSaTU;
      string TgsNSoiCVR;
      string atyUjjSJPK;
      string ZsDxGQyLdd;
      string pDQFKCSFrw;
      string ZoMgwbRcdr;
      string VJKIuacuGB;
      string pWXraWcrKg;
      string RNQTkjgWAe;
      string zUhkHfsHKi;
      string YWyqFCRTFY;
      string yYSwaIsqXK;
      string tGubBUoljt;
      string dUhaItOZNh;
      string SMQafaCkJy;
      string mCiznRaWoj;
      string NeiKudpqnf;
      string tScpqhpTuZ;
      string SDclHakhlp;
      if(iLSKlIqhyX == zUhkHfsHKi){TqjcUncGfC = true;}
      else if(zUhkHfsHKi == iLSKlIqhyX){zGhgAcUUeU = true;}
      if(VPyNcoSaTU == YWyqFCRTFY){kLxdDUYsIG = true;}
      else if(YWyqFCRTFY == VPyNcoSaTU){qgtzHhPltI = true;}
      if(TgsNSoiCVR == yYSwaIsqXK){bHbPRJCxDT = true;}
      else if(yYSwaIsqXK == TgsNSoiCVR){wiPPMXiMmZ = true;}
      if(atyUjjSJPK == tGubBUoljt){rHExMDiAVD = true;}
      else if(tGubBUoljt == atyUjjSJPK){LszPKxUgPo = true;}
      if(ZsDxGQyLdd == dUhaItOZNh){FjmsoGGyhl = true;}
      else if(dUhaItOZNh == ZsDxGQyLdd){fMrOKGSpDi = true;}
      if(pDQFKCSFrw == SMQafaCkJy){BrZfNLPUKK = true;}
      else if(SMQafaCkJy == pDQFKCSFrw){KugaOQpSTc = true;}
      if(ZoMgwbRcdr == mCiznRaWoj){keCLJdGzQA = true;}
      else if(mCiznRaWoj == ZoMgwbRcdr){tHhFJxhenJ = true;}
      if(VJKIuacuGB == NeiKudpqnf){lYXEArUhaK = true;}
      if(pWXraWcrKg == tScpqhpTuZ){DDOQRAgXjB = true;}
      if(RNQTkjgWAe == SDclHakhlp){mNoKRZgaiK = true;}
      while(NeiKudpqnf == VJKIuacuGB){MhVFbjpAEG = true;}
      while(tScpqhpTuZ == tScpqhpTuZ){EsIDPQLYAs = true;}
      while(SDclHakhlp == SDclHakhlp){GCMmtXdmFM = true;}
      if(TqjcUncGfC == true){TqjcUncGfC = false;}
      if(kLxdDUYsIG == true){kLxdDUYsIG = false;}
      if(bHbPRJCxDT == true){bHbPRJCxDT = false;}
      if(rHExMDiAVD == true){rHExMDiAVD = false;}
      if(FjmsoGGyhl == true){FjmsoGGyhl = false;}
      if(BrZfNLPUKK == true){BrZfNLPUKK = false;}
      if(keCLJdGzQA == true){keCLJdGzQA = false;}
      if(lYXEArUhaK == true){lYXEArUhaK = false;}
      if(DDOQRAgXjB == true){DDOQRAgXjB = false;}
      if(mNoKRZgaiK == true){mNoKRZgaiK = false;}
      if(zGhgAcUUeU == true){zGhgAcUUeU = false;}
      if(qgtzHhPltI == true){qgtzHhPltI = false;}
      if(wiPPMXiMmZ == true){wiPPMXiMmZ = false;}
      if(LszPKxUgPo == true){LszPKxUgPo = false;}
      if(fMrOKGSpDi == true){fMrOKGSpDi = false;}
      if(KugaOQpSTc == true){KugaOQpSTc = false;}
      if(tHhFJxhenJ == true){tHhFJxhenJ = false;}
      if(MhVFbjpAEG == true){MhVFbjpAEG = false;}
      if(EsIDPQLYAs == true){EsIDPQLYAs = false;}
      if(GCMmtXdmFM == true){GCMmtXdmFM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TGTWSQYMUW
{ 
  void ILSyTqqRIb()
  { 
      bool djsunbAtCE = false;
      bool bbdwualymx = false;
      bool MtHqHguCaV = false;
      bool uuJhYEFqEP = false;
      bool LflexTIyig = false;
      bool ULREKjbCnH = false;
      bool gxSfIgSuXp = false;
      bool VusWkgHcsm = false;
      bool YxTtBjcEXn = false;
      bool cCCxiNMGVQ = false;
      bool BMZsLZSuTc = false;
      bool byIAhjdYeY = false;
      bool DOXiMSrunW = false;
      bool UAHblLWZha = false;
      bool QhktMdsCOy = false;
      bool jmbxNmnpfr = false;
      bool gWHwIbqfOV = false;
      bool MDpDHUdcWh = false;
      bool YpfomgYJOz = false;
      bool Wgsotsankj = false;
      string IaUclHuBVl;
      string mnjEMfECMH;
      string LWJbqArCqn;
      string glctlgEPaN;
      string umawRZCTtb;
      string XmrCclQskl;
      string OrKgEALpRe;
      string bnazMXwMJR;
      string xYIOQstZRA;
      string QKenyCcsrQ;
      string OMBOAiLrpE;
      string oDjTopjuQL;
      string GkYQOQJlBK;
      string tCUsCkWtOh;
      string gBjMKMaKzH;
      string RhcfJcnjzj;
      string ZYqeJmiqQE;
      string TpgidFALGC;
      string oymsrMZniZ;
      string wltdHHJFCX;
      if(IaUclHuBVl == OMBOAiLrpE){djsunbAtCE = true;}
      else if(OMBOAiLrpE == IaUclHuBVl){BMZsLZSuTc = true;}
      if(mnjEMfECMH == oDjTopjuQL){bbdwualymx = true;}
      else if(oDjTopjuQL == mnjEMfECMH){byIAhjdYeY = true;}
      if(LWJbqArCqn == GkYQOQJlBK){MtHqHguCaV = true;}
      else if(GkYQOQJlBK == LWJbqArCqn){DOXiMSrunW = true;}
      if(glctlgEPaN == tCUsCkWtOh){uuJhYEFqEP = true;}
      else if(tCUsCkWtOh == glctlgEPaN){UAHblLWZha = true;}
      if(umawRZCTtb == gBjMKMaKzH){LflexTIyig = true;}
      else if(gBjMKMaKzH == umawRZCTtb){QhktMdsCOy = true;}
      if(XmrCclQskl == RhcfJcnjzj){ULREKjbCnH = true;}
      else if(RhcfJcnjzj == XmrCclQskl){jmbxNmnpfr = true;}
      if(OrKgEALpRe == ZYqeJmiqQE){gxSfIgSuXp = true;}
      else if(ZYqeJmiqQE == OrKgEALpRe){gWHwIbqfOV = true;}
      if(bnazMXwMJR == TpgidFALGC){VusWkgHcsm = true;}
      if(xYIOQstZRA == oymsrMZniZ){YxTtBjcEXn = true;}
      if(QKenyCcsrQ == wltdHHJFCX){cCCxiNMGVQ = true;}
      while(TpgidFALGC == bnazMXwMJR){MDpDHUdcWh = true;}
      while(oymsrMZniZ == oymsrMZniZ){YpfomgYJOz = true;}
      while(wltdHHJFCX == wltdHHJFCX){Wgsotsankj = true;}
      if(djsunbAtCE == true){djsunbAtCE = false;}
      if(bbdwualymx == true){bbdwualymx = false;}
      if(MtHqHguCaV == true){MtHqHguCaV = false;}
      if(uuJhYEFqEP == true){uuJhYEFqEP = false;}
      if(LflexTIyig == true){LflexTIyig = false;}
      if(ULREKjbCnH == true){ULREKjbCnH = false;}
      if(gxSfIgSuXp == true){gxSfIgSuXp = false;}
      if(VusWkgHcsm == true){VusWkgHcsm = false;}
      if(YxTtBjcEXn == true){YxTtBjcEXn = false;}
      if(cCCxiNMGVQ == true){cCCxiNMGVQ = false;}
      if(BMZsLZSuTc == true){BMZsLZSuTc = false;}
      if(byIAhjdYeY == true){byIAhjdYeY = false;}
      if(DOXiMSrunW == true){DOXiMSrunW = false;}
      if(UAHblLWZha == true){UAHblLWZha = false;}
      if(QhktMdsCOy == true){QhktMdsCOy = false;}
      if(jmbxNmnpfr == true){jmbxNmnpfr = false;}
      if(gWHwIbqfOV == true){gWHwIbqfOV = false;}
      if(MDpDHUdcWh == true){MDpDHUdcWh = false;}
      if(YpfomgYJOz == true){YpfomgYJOz = false;}
      if(Wgsotsankj == true){Wgsotsankj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SPTWFDYYII
{ 
  void SKwBbPpbBf()
  { 
      bool BuZDHtpgge = false;
      bool glGRAwmkrh = false;
      bool TzInoGGqKJ = false;
      bool grjYfsFFOF = false;
      bool FouFdMFWia = false;
      bool WQpFACllNA = false;
      bool myVXynBglG = false;
      bool qhWmbeDDJc = false;
      bool BjIjlQCeYc = false;
      bool HSqNRGTWHp = false;
      bool KXjbjosDcU = false;
      bool yickyDpkkg = false;
      bool lWIJzYpIUV = false;
      bool LguSRdzfAx = false;
      bool WyCDeXoGOO = false;
      bool PhkaDnOacK = false;
      bool zjhHJRmKSU = false;
      bool DJknJmUEda = false;
      bool iitGFduUOd = false;
      bool OYDoymQusN = false;
      string NTKfuAhNeV;
      string RHQjhrfeBY;
      string iCKMntFzWM;
      string qPBXwpfioA;
      string IGRGHNopBe;
      string elEwRLIxrB;
      string thpReCFsmq;
      string LwoBPbkEEZ;
      string EOyqhELFFj;
      string ghqnFaPzaF;
      string HwCJShxCfo;
      string aEsRwejziZ;
      string qAmCJdFAwo;
      string MkczSIMnYA;
      string GIZPJcoZqZ;
      string pQPANHJAzo;
      string cwGqcoatzn;
      string SwaiTiaWsg;
      string ofIVzuVbkL;
      string yLoiXKBhmT;
      if(NTKfuAhNeV == HwCJShxCfo){BuZDHtpgge = true;}
      else if(HwCJShxCfo == NTKfuAhNeV){KXjbjosDcU = true;}
      if(RHQjhrfeBY == aEsRwejziZ){glGRAwmkrh = true;}
      else if(aEsRwejziZ == RHQjhrfeBY){yickyDpkkg = true;}
      if(iCKMntFzWM == qAmCJdFAwo){TzInoGGqKJ = true;}
      else if(qAmCJdFAwo == iCKMntFzWM){lWIJzYpIUV = true;}
      if(qPBXwpfioA == MkczSIMnYA){grjYfsFFOF = true;}
      else if(MkczSIMnYA == qPBXwpfioA){LguSRdzfAx = true;}
      if(IGRGHNopBe == GIZPJcoZqZ){FouFdMFWia = true;}
      else if(GIZPJcoZqZ == IGRGHNopBe){WyCDeXoGOO = true;}
      if(elEwRLIxrB == pQPANHJAzo){WQpFACllNA = true;}
      else if(pQPANHJAzo == elEwRLIxrB){PhkaDnOacK = true;}
      if(thpReCFsmq == cwGqcoatzn){myVXynBglG = true;}
      else if(cwGqcoatzn == thpReCFsmq){zjhHJRmKSU = true;}
      if(LwoBPbkEEZ == SwaiTiaWsg){qhWmbeDDJc = true;}
      if(EOyqhELFFj == ofIVzuVbkL){BjIjlQCeYc = true;}
      if(ghqnFaPzaF == yLoiXKBhmT){HSqNRGTWHp = true;}
      while(SwaiTiaWsg == LwoBPbkEEZ){DJknJmUEda = true;}
      while(ofIVzuVbkL == ofIVzuVbkL){iitGFduUOd = true;}
      while(yLoiXKBhmT == yLoiXKBhmT){OYDoymQusN = true;}
      if(BuZDHtpgge == true){BuZDHtpgge = false;}
      if(glGRAwmkrh == true){glGRAwmkrh = false;}
      if(TzInoGGqKJ == true){TzInoGGqKJ = false;}
      if(grjYfsFFOF == true){grjYfsFFOF = false;}
      if(FouFdMFWia == true){FouFdMFWia = false;}
      if(WQpFACllNA == true){WQpFACllNA = false;}
      if(myVXynBglG == true){myVXynBglG = false;}
      if(qhWmbeDDJc == true){qhWmbeDDJc = false;}
      if(BjIjlQCeYc == true){BjIjlQCeYc = false;}
      if(HSqNRGTWHp == true){HSqNRGTWHp = false;}
      if(KXjbjosDcU == true){KXjbjosDcU = false;}
      if(yickyDpkkg == true){yickyDpkkg = false;}
      if(lWIJzYpIUV == true){lWIJzYpIUV = false;}
      if(LguSRdzfAx == true){LguSRdzfAx = false;}
      if(WyCDeXoGOO == true){WyCDeXoGOO = false;}
      if(PhkaDnOacK == true){PhkaDnOacK = false;}
      if(zjhHJRmKSU == true){zjhHJRmKSU = false;}
      if(DJknJmUEda == true){DJknJmUEda = false;}
      if(iitGFduUOd == true){iitGFduUOd = false;}
      if(OYDoymQusN == true){OYDoymQusN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WNEFBHFTDR
{ 
  void HwrXdOlHLW()
  { 
      bool fKQxRxmCee = false;
      bool AgLIgiiSDq = false;
      bool mrmWftkGpF = false;
      bool TkJXGIOIsf = false;
      bool fiFeWcJADU = false;
      bool jfsXFnXsRW = false;
      bool MgMYKPWmCY = false;
      bool UaYWKDlHAC = false;
      bool jkCVVnrkSR = false;
      bool kUpWTzWgUH = false;
      bool FVxeAJGVNC = false;
      bool CPsOladpDW = false;
      bool WkUjnzkCDL = false;
      bool fEmrxOmXUM = false;
      bool gWXPPUbajr = false;
      bool UfcxjTBNqB = false;
      bool XESBVxcBRX = false;
      bool nGUppAMEUS = false;
      bool XJSKpzboHc = false;
      bool MYgTnbDVtS = false;
      string EuyekyDZWo;
      string CiprANMCBt;
      string KxwpgLcJhi;
      string MHsEhbWJQP;
      string iBARnipUPT;
      string ITINTGyIyZ;
      string UsrnbtpkJY;
      string pCklLIxeBy;
      string UItOZrzfkb;
      string cOLqtpJMos;
      string rFKpcGiVCK;
      string JTGAEMydOi;
      string uKzhubqsrU;
      string zjpIFPxElT;
      string JccaRJILmg;
      string qeyFxhFbuA;
      string OpdgLYcxto;
      string PtquZSgYQl;
      string SfGLdTlkKX;
      string JUIkETywPr;
      if(EuyekyDZWo == rFKpcGiVCK){fKQxRxmCee = true;}
      else if(rFKpcGiVCK == EuyekyDZWo){FVxeAJGVNC = true;}
      if(CiprANMCBt == JTGAEMydOi){AgLIgiiSDq = true;}
      else if(JTGAEMydOi == CiprANMCBt){CPsOladpDW = true;}
      if(KxwpgLcJhi == uKzhubqsrU){mrmWftkGpF = true;}
      else if(uKzhubqsrU == KxwpgLcJhi){WkUjnzkCDL = true;}
      if(MHsEhbWJQP == zjpIFPxElT){TkJXGIOIsf = true;}
      else if(zjpIFPxElT == MHsEhbWJQP){fEmrxOmXUM = true;}
      if(iBARnipUPT == JccaRJILmg){fiFeWcJADU = true;}
      else if(JccaRJILmg == iBARnipUPT){gWXPPUbajr = true;}
      if(ITINTGyIyZ == qeyFxhFbuA){jfsXFnXsRW = true;}
      else if(qeyFxhFbuA == ITINTGyIyZ){UfcxjTBNqB = true;}
      if(UsrnbtpkJY == OpdgLYcxto){MgMYKPWmCY = true;}
      else if(OpdgLYcxto == UsrnbtpkJY){XESBVxcBRX = true;}
      if(pCklLIxeBy == PtquZSgYQl){UaYWKDlHAC = true;}
      if(UItOZrzfkb == SfGLdTlkKX){jkCVVnrkSR = true;}
      if(cOLqtpJMos == JUIkETywPr){kUpWTzWgUH = true;}
      while(PtquZSgYQl == pCklLIxeBy){nGUppAMEUS = true;}
      while(SfGLdTlkKX == SfGLdTlkKX){XJSKpzboHc = true;}
      while(JUIkETywPr == JUIkETywPr){MYgTnbDVtS = true;}
      if(fKQxRxmCee == true){fKQxRxmCee = false;}
      if(AgLIgiiSDq == true){AgLIgiiSDq = false;}
      if(mrmWftkGpF == true){mrmWftkGpF = false;}
      if(TkJXGIOIsf == true){TkJXGIOIsf = false;}
      if(fiFeWcJADU == true){fiFeWcJADU = false;}
      if(jfsXFnXsRW == true){jfsXFnXsRW = false;}
      if(MgMYKPWmCY == true){MgMYKPWmCY = false;}
      if(UaYWKDlHAC == true){UaYWKDlHAC = false;}
      if(jkCVVnrkSR == true){jkCVVnrkSR = false;}
      if(kUpWTzWgUH == true){kUpWTzWgUH = false;}
      if(FVxeAJGVNC == true){FVxeAJGVNC = false;}
      if(CPsOladpDW == true){CPsOladpDW = false;}
      if(WkUjnzkCDL == true){WkUjnzkCDL = false;}
      if(fEmrxOmXUM == true){fEmrxOmXUM = false;}
      if(gWXPPUbajr == true){gWXPPUbajr = false;}
      if(UfcxjTBNqB == true){UfcxjTBNqB = false;}
      if(XESBVxcBRX == true){XESBVxcBRX = false;}
      if(nGUppAMEUS == true){nGUppAMEUS = false;}
      if(XJSKpzboHc == true){XJSKpzboHc = false;}
      if(MYgTnbDVtS == true){MYgTnbDVtS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JDYQJEXGSF
{ 
  void HmFdAEeBsd()
  { 
      bool sDbpQyqyAR = false;
      bool CzotxBuASn = false;
      bool bYfnPiEwBw = false;
      bool BFQsOxGkSq = false;
      bool BIysLyWIls = false;
      bool GlmTlTWnZg = false;
      bool ttwDPwhufz = false;
      bool tJgalSZmbR = false;
      bool MuJIpPRwGt = false;
      bool ZSLlxGMucO = false;
      bool PbblyxELgS = false;
      bool tiLIUyjnNA = false;
      bool eknkZbyude = false;
      bool GdKMBjTXKs = false;
      bool KFOmAqGDQy = false;
      bool WYhbjdmqMV = false;
      bool yJgCMPYzGj = false;
      bool eMcTpYVAkh = false;
      bool VtdfIhwhcW = false;
      bool xbKntAXMaj = false;
      string ocPBfaGFil;
      string UghgosXoyR;
      string ajlWEqIQQl;
      string oCkioduEZj;
      string GZPRllkulp;
      string NQwQxFpswn;
      string SpnwwSwzqL;
      string xSPOLAUTjS;
      string GNeaXYFTkj;
      string mCHkRQkSVS;
      string pkEZstAhEw;
      string kVIdhEKNYW;
      string MbNGYuLdwu;
      string PByRbUJEhc;
      string XXPoyQtcCM;
      string FWtzGOXxBy;
      string iWkIgjXqBM;
      string uGfuynLYIH;
      string AhajprHzKN;
      string xLCjtBmGHO;
      if(ocPBfaGFil == pkEZstAhEw){sDbpQyqyAR = true;}
      else if(pkEZstAhEw == ocPBfaGFil){PbblyxELgS = true;}
      if(UghgosXoyR == kVIdhEKNYW){CzotxBuASn = true;}
      else if(kVIdhEKNYW == UghgosXoyR){tiLIUyjnNA = true;}
      if(ajlWEqIQQl == MbNGYuLdwu){bYfnPiEwBw = true;}
      else if(MbNGYuLdwu == ajlWEqIQQl){eknkZbyude = true;}
      if(oCkioduEZj == PByRbUJEhc){BFQsOxGkSq = true;}
      else if(PByRbUJEhc == oCkioduEZj){GdKMBjTXKs = true;}
      if(GZPRllkulp == XXPoyQtcCM){BIysLyWIls = true;}
      else if(XXPoyQtcCM == GZPRllkulp){KFOmAqGDQy = true;}
      if(NQwQxFpswn == FWtzGOXxBy){GlmTlTWnZg = true;}
      else if(FWtzGOXxBy == NQwQxFpswn){WYhbjdmqMV = true;}
      if(SpnwwSwzqL == iWkIgjXqBM){ttwDPwhufz = true;}
      else if(iWkIgjXqBM == SpnwwSwzqL){yJgCMPYzGj = true;}
      if(xSPOLAUTjS == uGfuynLYIH){tJgalSZmbR = true;}
      if(GNeaXYFTkj == AhajprHzKN){MuJIpPRwGt = true;}
      if(mCHkRQkSVS == xLCjtBmGHO){ZSLlxGMucO = true;}
      while(uGfuynLYIH == xSPOLAUTjS){eMcTpYVAkh = true;}
      while(AhajprHzKN == AhajprHzKN){VtdfIhwhcW = true;}
      while(xLCjtBmGHO == xLCjtBmGHO){xbKntAXMaj = true;}
      if(sDbpQyqyAR == true){sDbpQyqyAR = false;}
      if(CzotxBuASn == true){CzotxBuASn = false;}
      if(bYfnPiEwBw == true){bYfnPiEwBw = false;}
      if(BFQsOxGkSq == true){BFQsOxGkSq = false;}
      if(BIysLyWIls == true){BIysLyWIls = false;}
      if(GlmTlTWnZg == true){GlmTlTWnZg = false;}
      if(ttwDPwhufz == true){ttwDPwhufz = false;}
      if(tJgalSZmbR == true){tJgalSZmbR = false;}
      if(MuJIpPRwGt == true){MuJIpPRwGt = false;}
      if(ZSLlxGMucO == true){ZSLlxGMucO = false;}
      if(PbblyxELgS == true){PbblyxELgS = false;}
      if(tiLIUyjnNA == true){tiLIUyjnNA = false;}
      if(eknkZbyude == true){eknkZbyude = false;}
      if(GdKMBjTXKs == true){GdKMBjTXKs = false;}
      if(KFOmAqGDQy == true){KFOmAqGDQy = false;}
      if(WYhbjdmqMV == true){WYhbjdmqMV = false;}
      if(yJgCMPYzGj == true){yJgCMPYzGj = false;}
      if(eMcTpYVAkh == true){eMcTpYVAkh = false;}
      if(VtdfIhwhcW == true){VtdfIhwhcW = false;}
      if(xbKntAXMaj == true){xbKntAXMaj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OHHMQRPTGY
{ 
  void AFZmTTVIhp()
  { 
      bool ylwMgDpjiB = false;
      bool qwHLxFwpVp = false;
      bool YGfteYbSKy = false;
      bool XcwdBGBgom = false;
      bool VJUVTBKeDK = false;
      bool WYzDFqFChI = false;
      bool aWYkcOzcKq = false;
      bool DPBhTPlKZc = false;
      bool NxOzbzdsXJ = false;
      bool BzygMyjjrF = false;
      bool ChUMGHXQip = false;
      bool FucEtdIYId = false;
      bool kGEApEQTUV = false;
      bool eCRUafbCrU = false;
      bool bMJhEFVsmh = false;
      bool pKaOUwcUWC = false;
      bool pDwNKCcIdN = false;
      bool BGgnCXwWuj = false;
      bool hWgmeUbCzd = false;
      bool DHepdXQwWC = false;
      string XcBDMdfFHR;
      string qekaLZpUaA;
      string mobVcmyhdl;
      string DpqgCakhde;
      string rwcrFHctHN;
      string MRFiNiAfaY;
      string eybUOBmEYj;
      string nIpwIpLjPU;
      string JEaQYlkIST;
      string ZFHFAtUHdE;
      string TYVWYEbIaX;
      string WQPFOaWLwb;
      string PelFJiAkwN;
      string VEFLAkiDqU;
      string KbguwJpBpY;
      string WJLBnomPMp;
      string DpMMBRKDFc;
      string rTTaRmxpIA;
      string rytWqLsDWL;
      string ySqBQTOUsd;
      if(XcBDMdfFHR == TYVWYEbIaX){ylwMgDpjiB = true;}
      else if(TYVWYEbIaX == XcBDMdfFHR){ChUMGHXQip = true;}
      if(qekaLZpUaA == WQPFOaWLwb){qwHLxFwpVp = true;}
      else if(WQPFOaWLwb == qekaLZpUaA){FucEtdIYId = true;}
      if(mobVcmyhdl == PelFJiAkwN){YGfteYbSKy = true;}
      else if(PelFJiAkwN == mobVcmyhdl){kGEApEQTUV = true;}
      if(DpqgCakhde == VEFLAkiDqU){XcwdBGBgom = true;}
      else if(VEFLAkiDqU == DpqgCakhde){eCRUafbCrU = true;}
      if(rwcrFHctHN == KbguwJpBpY){VJUVTBKeDK = true;}
      else if(KbguwJpBpY == rwcrFHctHN){bMJhEFVsmh = true;}
      if(MRFiNiAfaY == WJLBnomPMp){WYzDFqFChI = true;}
      else if(WJLBnomPMp == MRFiNiAfaY){pKaOUwcUWC = true;}
      if(eybUOBmEYj == DpMMBRKDFc){aWYkcOzcKq = true;}
      else if(DpMMBRKDFc == eybUOBmEYj){pDwNKCcIdN = true;}
      if(nIpwIpLjPU == rTTaRmxpIA){DPBhTPlKZc = true;}
      if(JEaQYlkIST == rytWqLsDWL){NxOzbzdsXJ = true;}
      if(ZFHFAtUHdE == ySqBQTOUsd){BzygMyjjrF = true;}
      while(rTTaRmxpIA == nIpwIpLjPU){BGgnCXwWuj = true;}
      while(rytWqLsDWL == rytWqLsDWL){hWgmeUbCzd = true;}
      while(ySqBQTOUsd == ySqBQTOUsd){DHepdXQwWC = true;}
      if(ylwMgDpjiB == true){ylwMgDpjiB = false;}
      if(qwHLxFwpVp == true){qwHLxFwpVp = false;}
      if(YGfteYbSKy == true){YGfteYbSKy = false;}
      if(XcwdBGBgom == true){XcwdBGBgom = false;}
      if(VJUVTBKeDK == true){VJUVTBKeDK = false;}
      if(WYzDFqFChI == true){WYzDFqFChI = false;}
      if(aWYkcOzcKq == true){aWYkcOzcKq = false;}
      if(DPBhTPlKZc == true){DPBhTPlKZc = false;}
      if(NxOzbzdsXJ == true){NxOzbzdsXJ = false;}
      if(BzygMyjjrF == true){BzygMyjjrF = false;}
      if(ChUMGHXQip == true){ChUMGHXQip = false;}
      if(FucEtdIYId == true){FucEtdIYId = false;}
      if(kGEApEQTUV == true){kGEApEQTUV = false;}
      if(eCRUafbCrU == true){eCRUafbCrU = false;}
      if(bMJhEFVsmh == true){bMJhEFVsmh = false;}
      if(pKaOUwcUWC == true){pKaOUwcUWC = false;}
      if(pDwNKCcIdN == true){pDwNKCcIdN = false;}
      if(BGgnCXwWuj == true){BGgnCXwWuj = false;}
      if(hWgmeUbCzd == true){hWgmeUbCzd = false;}
      if(DHepdXQwWC == true){DHepdXQwWC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RDDHRUCMWA
{ 
  void DiBmzlDSMA()
  { 
      bool ytuVQoFVzD = false;
      bool tCCyYaEzCt = false;
      bool lTnqYaWMNh = false;
      bool ldsOZCiuET = false;
      bool NtOIbTJGmY = false;
      bool MQMMkeFDxp = false;
      bool RrIQRPJnXW = false;
      bool rJthfqFePE = false;
      bool RQYnVUQfcu = false;
      bool wexOCUlxqL = false;
      bool KViQgDWegt = false;
      bool YanrXATTux = false;
      bool ycKbZMLefK = false;
      bool FInDtwhHHR = false;
      bool xlziVVqFqB = false;
      bool BRBsMgKGqT = false;
      bool qqyVnQmjxb = false;
      bool SLMcAMdbFD = false;
      bool UFneJnGtpM = false;
      bool laPmaFnctE = false;
      string oETJodUdfC;
      string VgcdxJufyV;
      string ieNiQUpMVM;
      string WxudnRAaIf;
      string awYQTuWpIW;
      string NdOgyKqjsT;
      string nHHTeXkzpf;
      string ITXStmGxPU;
      string xAEyzsiOed;
      string ZQgnrTnEku;
      string KXAcOsFwlL;
      string EtUXVmCJUl;
      string oVTLFrmjaZ;
      string yBMTKZAaiG;
      string mlbTZfuIRE;
      string QejyGnDnWW;
      string FVVLMCgBNw;
      string mbZNzCtAkY;
      string xdRVJSQNMV;
      string WLEMAQQPGW;
      if(oETJodUdfC == KXAcOsFwlL){ytuVQoFVzD = true;}
      else if(KXAcOsFwlL == oETJodUdfC){KViQgDWegt = true;}
      if(VgcdxJufyV == EtUXVmCJUl){tCCyYaEzCt = true;}
      else if(EtUXVmCJUl == VgcdxJufyV){YanrXATTux = true;}
      if(ieNiQUpMVM == oVTLFrmjaZ){lTnqYaWMNh = true;}
      else if(oVTLFrmjaZ == ieNiQUpMVM){ycKbZMLefK = true;}
      if(WxudnRAaIf == yBMTKZAaiG){ldsOZCiuET = true;}
      else if(yBMTKZAaiG == WxudnRAaIf){FInDtwhHHR = true;}
      if(awYQTuWpIW == mlbTZfuIRE){NtOIbTJGmY = true;}
      else if(mlbTZfuIRE == awYQTuWpIW){xlziVVqFqB = true;}
      if(NdOgyKqjsT == QejyGnDnWW){MQMMkeFDxp = true;}
      else if(QejyGnDnWW == NdOgyKqjsT){BRBsMgKGqT = true;}
      if(nHHTeXkzpf == FVVLMCgBNw){RrIQRPJnXW = true;}
      else if(FVVLMCgBNw == nHHTeXkzpf){qqyVnQmjxb = true;}
      if(ITXStmGxPU == mbZNzCtAkY){rJthfqFePE = true;}
      if(xAEyzsiOed == xdRVJSQNMV){RQYnVUQfcu = true;}
      if(ZQgnrTnEku == WLEMAQQPGW){wexOCUlxqL = true;}
      while(mbZNzCtAkY == ITXStmGxPU){SLMcAMdbFD = true;}
      while(xdRVJSQNMV == xdRVJSQNMV){UFneJnGtpM = true;}
      while(WLEMAQQPGW == WLEMAQQPGW){laPmaFnctE = true;}
      if(ytuVQoFVzD == true){ytuVQoFVzD = false;}
      if(tCCyYaEzCt == true){tCCyYaEzCt = false;}
      if(lTnqYaWMNh == true){lTnqYaWMNh = false;}
      if(ldsOZCiuET == true){ldsOZCiuET = false;}
      if(NtOIbTJGmY == true){NtOIbTJGmY = false;}
      if(MQMMkeFDxp == true){MQMMkeFDxp = false;}
      if(RrIQRPJnXW == true){RrIQRPJnXW = false;}
      if(rJthfqFePE == true){rJthfqFePE = false;}
      if(RQYnVUQfcu == true){RQYnVUQfcu = false;}
      if(wexOCUlxqL == true){wexOCUlxqL = false;}
      if(KViQgDWegt == true){KViQgDWegt = false;}
      if(YanrXATTux == true){YanrXATTux = false;}
      if(ycKbZMLefK == true){ycKbZMLefK = false;}
      if(FInDtwhHHR == true){FInDtwhHHR = false;}
      if(xlziVVqFqB == true){xlziVVqFqB = false;}
      if(BRBsMgKGqT == true){BRBsMgKGqT = false;}
      if(qqyVnQmjxb == true){qqyVnQmjxb = false;}
      if(SLMcAMdbFD == true){SLMcAMdbFD = false;}
      if(UFneJnGtpM == true){UFneJnGtpM = false;}
      if(laPmaFnctE == true){laPmaFnctE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JNFZHLZMPB
{ 
  void raNGUAYKcw()
  { 
      bool ftCZzoJXYC = false;
      bool nDQCjaBFGS = false;
      bool jPmyFGEJKg = false;
      bool xAwgtwpGKp = false;
      bool emYTipWXrE = false;
      bool cPwnWPHDUr = false;
      bool jAMrFmGjHn = false;
      bool jtuQnxqSOP = false;
      bool jgQGDgEHKd = false;
      bool ollRFdZfOw = false;
      bool imPDThUeAY = false;
      bool YnoEHDjGnX = false;
      bool iyYdzxHcLJ = false;
      bool XKESgxRMmV = false;
      bool MYGkFBxhKB = false;
      bool tSrpMjNlEV = false;
      bool ZqTqBOiWXK = false;
      bool lWTSLJqmXy = false;
      bool AZSJOERNFw = false;
      bool ieIQuUFPjq = false;
      string IObwEjdMcw;
      string XVzkmfgcCX;
      string WJaFGdDBxB;
      string VMEXVdcCyP;
      string aAfilDDMEX;
      string PTHfOynVpZ;
      string fbOaZKRbOJ;
      string CdemwVdqTC;
      string aqwZkBFYIX;
      string pHMXiykEIa;
      string laxuVloTis;
      string UwCmzoeopX;
      string EsTqTuRGEx;
      string kYhrQAsBDz;
      string MloPCsEYYt;
      string SuOjVrHFba;
      string ThPkHuNJWy;
      string udlpLSEDnZ;
      string psgJeoKyWX;
      string snZcedVDHH;
      if(IObwEjdMcw == laxuVloTis){ftCZzoJXYC = true;}
      else if(laxuVloTis == IObwEjdMcw){imPDThUeAY = true;}
      if(XVzkmfgcCX == UwCmzoeopX){nDQCjaBFGS = true;}
      else if(UwCmzoeopX == XVzkmfgcCX){YnoEHDjGnX = true;}
      if(WJaFGdDBxB == EsTqTuRGEx){jPmyFGEJKg = true;}
      else if(EsTqTuRGEx == WJaFGdDBxB){iyYdzxHcLJ = true;}
      if(VMEXVdcCyP == kYhrQAsBDz){xAwgtwpGKp = true;}
      else if(kYhrQAsBDz == VMEXVdcCyP){XKESgxRMmV = true;}
      if(aAfilDDMEX == MloPCsEYYt){emYTipWXrE = true;}
      else if(MloPCsEYYt == aAfilDDMEX){MYGkFBxhKB = true;}
      if(PTHfOynVpZ == SuOjVrHFba){cPwnWPHDUr = true;}
      else if(SuOjVrHFba == PTHfOynVpZ){tSrpMjNlEV = true;}
      if(fbOaZKRbOJ == ThPkHuNJWy){jAMrFmGjHn = true;}
      else if(ThPkHuNJWy == fbOaZKRbOJ){ZqTqBOiWXK = true;}
      if(CdemwVdqTC == udlpLSEDnZ){jtuQnxqSOP = true;}
      if(aqwZkBFYIX == psgJeoKyWX){jgQGDgEHKd = true;}
      if(pHMXiykEIa == snZcedVDHH){ollRFdZfOw = true;}
      while(udlpLSEDnZ == CdemwVdqTC){lWTSLJqmXy = true;}
      while(psgJeoKyWX == psgJeoKyWX){AZSJOERNFw = true;}
      while(snZcedVDHH == snZcedVDHH){ieIQuUFPjq = true;}
      if(ftCZzoJXYC == true){ftCZzoJXYC = false;}
      if(nDQCjaBFGS == true){nDQCjaBFGS = false;}
      if(jPmyFGEJKg == true){jPmyFGEJKg = false;}
      if(xAwgtwpGKp == true){xAwgtwpGKp = false;}
      if(emYTipWXrE == true){emYTipWXrE = false;}
      if(cPwnWPHDUr == true){cPwnWPHDUr = false;}
      if(jAMrFmGjHn == true){jAMrFmGjHn = false;}
      if(jtuQnxqSOP == true){jtuQnxqSOP = false;}
      if(jgQGDgEHKd == true){jgQGDgEHKd = false;}
      if(ollRFdZfOw == true){ollRFdZfOw = false;}
      if(imPDThUeAY == true){imPDThUeAY = false;}
      if(YnoEHDjGnX == true){YnoEHDjGnX = false;}
      if(iyYdzxHcLJ == true){iyYdzxHcLJ = false;}
      if(XKESgxRMmV == true){XKESgxRMmV = false;}
      if(MYGkFBxhKB == true){MYGkFBxhKB = false;}
      if(tSrpMjNlEV == true){tSrpMjNlEV = false;}
      if(ZqTqBOiWXK == true){ZqTqBOiWXK = false;}
      if(lWTSLJqmXy == true){lWTSLJqmXy = false;}
      if(AZSJOERNFw == true){AZSJOERNFw = false;}
      if(ieIQuUFPjq == true){ieIQuUFPjq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HKZSJLMVPV
{ 
  void GqazApnfip()
  { 
      bool ZGXnSDGJbT = false;
      bool dhniXeELTi = false;
      bool bcimCfKGfU = false;
      bool MkQLQcTWNo = false;
      bool uTUNMjIJWp = false;
      bool AZUdfwXjkm = false;
      bool szdHGrQcRt = false;
      bool KhydnIIVaS = false;
      bool WAjoUmQleT = false;
      bool FikZwupNGU = false;
      bool SfrbeSaqpX = false;
      bool nCJSQrPnlT = false;
      bool bdxyobxYgs = false;
      bool RtOGAqIHKC = false;
      bool LYwHeCYRJD = false;
      bool eCamrnhslC = false;
      bool UCJxGsnDRY = false;
      bool jIcjIChpSm = false;
      bool CeOcNPTbNL = false;
      bool JOUHgIPzBl = false;
      string aLbtDGXEAP;
      string DskbPmuKRJ;
      string PspSwhbScx;
      string RbDOnwtZfK;
      string gpEtXVMeiI;
      string nOboUgVJyV;
      string eEaCxbpWnS;
      string rVdHbZoutZ;
      string UwiUJDzOsG;
      string akaJebPCwu;
      string fppQPRjUMu;
      string rZOYAiVGrt;
      string cbchqHtUbz;
      string KmzzteFREr;
      string TdByNAWCJw;
      string GIJCRDMIYI;
      string WPrMkFaPdU;
      string cDCAZyZeTp;
      string jrKfsBcxgp;
      string RxruUElnNI;
      if(aLbtDGXEAP == fppQPRjUMu){ZGXnSDGJbT = true;}
      else if(fppQPRjUMu == aLbtDGXEAP){SfrbeSaqpX = true;}
      if(DskbPmuKRJ == rZOYAiVGrt){dhniXeELTi = true;}
      else if(rZOYAiVGrt == DskbPmuKRJ){nCJSQrPnlT = true;}
      if(PspSwhbScx == cbchqHtUbz){bcimCfKGfU = true;}
      else if(cbchqHtUbz == PspSwhbScx){bdxyobxYgs = true;}
      if(RbDOnwtZfK == KmzzteFREr){MkQLQcTWNo = true;}
      else if(KmzzteFREr == RbDOnwtZfK){RtOGAqIHKC = true;}
      if(gpEtXVMeiI == TdByNAWCJw){uTUNMjIJWp = true;}
      else if(TdByNAWCJw == gpEtXVMeiI){LYwHeCYRJD = true;}
      if(nOboUgVJyV == GIJCRDMIYI){AZUdfwXjkm = true;}
      else if(GIJCRDMIYI == nOboUgVJyV){eCamrnhslC = true;}
      if(eEaCxbpWnS == WPrMkFaPdU){szdHGrQcRt = true;}
      else if(WPrMkFaPdU == eEaCxbpWnS){UCJxGsnDRY = true;}
      if(rVdHbZoutZ == cDCAZyZeTp){KhydnIIVaS = true;}
      if(UwiUJDzOsG == jrKfsBcxgp){WAjoUmQleT = true;}
      if(akaJebPCwu == RxruUElnNI){FikZwupNGU = true;}
      while(cDCAZyZeTp == rVdHbZoutZ){jIcjIChpSm = true;}
      while(jrKfsBcxgp == jrKfsBcxgp){CeOcNPTbNL = true;}
      while(RxruUElnNI == RxruUElnNI){JOUHgIPzBl = true;}
      if(ZGXnSDGJbT == true){ZGXnSDGJbT = false;}
      if(dhniXeELTi == true){dhniXeELTi = false;}
      if(bcimCfKGfU == true){bcimCfKGfU = false;}
      if(MkQLQcTWNo == true){MkQLQcTWNo = false;}
      if(uTUNMjIJWp == true){uTUNMjIJWp = false;}
      if(AZUdfwXjkm == true){AZUdfwXjkm = false;}
      if(szdHGrQcRt == true){szdHGrQcRt = false;}
      if(KhydnIIVaS == true){KhydnIIVaS = false;}
      if(WAjoUmQleT == true){WAjoUmQleT = false;}
      if(FikZwupNGU == true){FikZwupNGU = false;}
      if(SfrbeSaqpX == true){SfrbeSaqpX = false;}
      if(nCJSQrPnlT == true){nCJSQrPnlT = false;}
      if(bdxyobxYgs == true){bdxyobxYgs = false;}
      if(RtOGAqIHKC == true){RtOGAqIHKC = false;}
      if(LYwHeCYRJD == true){LYwHeCYRJD = false;}
      if(eCamrnhslC == true){eCamrnhslC = false;}
      if(UCJxGsnDRY == true){UCJxGsnDRY = false;}
      if(jIcjIChpSm == true){jIcjIChpSm = false;}
      if(CeOcNPTbNL == true){CeOcNPTbNL = false;}
      if(JOUHgIPzBl == true){JOUHgIPzBl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTTQWTGQEX
{ 
  void jamWGdSQyW()
  { 
      bool ibRTmZjWUW = false;
      bool cHDbuOjZGH = false;
      bool ZEjsgSpKDQ = false;
      bool qDILQlbgKB = false;
      bool iOLwrTqwQk = false;
      bool eiWVVdqYmU = false;
      bool jYTEfYzrLJ = false;
      bool mDOEYKrnAN = false;
      bool bstSlIflpl = false;
      bool uCtpQJtHQS = false;
      bool UykHxbTRxK = false;
      bool kCYYrpeBSW = false;
      bool rMBYOjIYnO = false;
      bool QkXhrcImUK = false;
      bool nNofArdUxZ = false;
      bool esosZHxLsN = false;
      bool SudhtAeqgP = false;
      bool hqgIidXVYV = false;
      bool GnbNiWweHk = false;
      bool fwtHqsjGlA = false;
      string HTVMmqzYZR;
      string gerqVfullZ;
      string ClohmysrBX;
      string UwapzQMxyR;
      string HYnboGoPzY;
      string fEqQgVemZo;
      string xGWCwkDCqE;
      string TxnTRdyMsg;
      string JdsbqQEKJd;
      string lYXJUBClfD;
      string CmXtFhQXyD;
      string XRsrfTMtLf;
      string gsrNStZezQ;
      string aLgpdVFzWI;
      string AgLFGTffdB;
      string nHZAWJtKaK;
      string IkXhbLkDNJ;
      string NNWCeAglGz;
      string OtBybTlgSU;
      string btXMzOIcdu;
      if(HTVMmqzYZR == CmXtFhQXyD){ibRTmZjWUW = true;}
      else if(CmXtFhQXyD == HTVMmqzYZR){UykHxbTRxK = true;}
      if(gerqVfullZ == XRsrfTMtLf){cHDbuOjZGH = true;}
      else if(XRsrfTMtLf == gerqVfullZ){kCYYrpeBSW = true;}
      if(ClohmysrBX == gsrNStZezQ){ZEjsgSpKDQ = true;}
      else if(gsrNStZezQ == ClohmysrBX){rMBYOjIYnO = true;}
      if(UwapzQMxyR == aLgpdVFzWI){qDILQlbgKB = true;}
      else if(aLgpdVFzWI == UwapzQMxyR){QkXhrcImUK = true;}
      if(HYnboGoPzY == AgLFGTffdB){iOLwrTqwQk = true;}
      else if(AgLFGTffdB == HYnboGoPzY){nNofArdUxZ = true;}
      if(fEqQgVemZo == nHZAWJtKaK){eiWVVdqYmU = true;}
      else if(nHZAWJtKaK == fEqQgVemZo){esosZHxLsN = true;}
      if(xGWCwkDCqE == IkXhbLkDNJ){jYTEfYzrLJ = true;}
      else if(IkXhbLkDNJ == xGWCwkDCqE){SudhtAeqgP = true;}
      if(TxnTRdyMsg == NNWCeAglGz){mDOEYKrnAN = true;}
      if(JdsbqQEKJd == OtBybTlgSU){bstSlIflpl = true;}
      if(lYXJUBClfD == btXMzOIcdu){uCtpQJtHQS = true;}
      while(NNWCeAglGz == TxnTRdyMsg){hqgIidXVYV = true;}
      while(OtBybTlgSU == OtBybTlgSU){GnbNiWweHk = true;}
      while(btXMzOIcdu == btXMzOIcdu){fwtHqsjGlA = true;}
      if(ibRTmZjWUW == true){ibRTmZjWUW = false;}
      if(cHDbuOjZGH == true){cHDbuOjZGH = false;}
      if(ZEjsgSpKDQ == true){ZEjsgSpKDQ = false;}
      if(qDILQlbgKB == true){qDILQlbgKB = false;}
      if(iOLwrTqwQk == true){iOLwrTqwQk = false;}
      if(eiWVVdqYmU == true){eiWVVdqYmU = false;}
      if(jYTEfYzrLJ == true){jYTEfYzrLJ = false;}
      if(mDOEYKrnAN == true){mDOEYKrnAN = false;}
      if(bstSlIflpl == true){bstSlIflpl = false;}
      if(uCtpQJtHQS == true){uCtpQJtHQS = false;}
      if(UykHxbTRxK == true){UykHxbTRxK = false;}
      if(kCYYrpeBSW == true){kCYYrpeBSW = false;}
      if(rMBYOjIYnO == true){rMBYOjIYnO = false;}
      if(QkXhrcImUK == true){QkXhrcImUK = false;}
      if(nNofArdUxZ == true){nNofArdUxZ = false;}
      if(esosZHxLsN == true){esosZHxLsN = false;}
      if(SudhtAeqgP == true){SudhtAeqgP = false;}
      if(hqgIidXVYV == true){hqgIidXVYV = false;}
      if(GnbNiWweHk == true){GnbNiWweHk = false;}
      if(fwtHqsjGlA == true){fwtHqsjGlA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TGCRFFRVBW
{ 
  void aWhiqrZhIK()
  { 
      bool ktoXxrKnfY = false;
      bool zIwSJVExGz = false;
      bool axPSorSMaQ = false;
      bool UVuGxOEaHe = false;
      bool hSmjdahrPW = false;
      bool UfxDdmdVhE = false;
      bool YxNODdNpUu = false;
      bool RdpbRIJfoN = false;
      bool KZwDuoXqcJ = false;
      bool jirDFkFYgA = false;
      bool MqWUFqpVkU = false;
      bool cyfTtyAJTN = false;
      bool FVNLLhkmWf = false;
      bool DkzoASDbxE = false;
      bool zCFHglCXIG = false;
      bool juEStqdLIW = false;
      bool FDyERqzpTa = false;
      bool uXMOOCPGdZ = false;
      bool fNdQwHfgtJ = false;
      bool oqSZzwEBoo = false;
      string RJJRcpVIrg;
      string VBQXsQlbjM;
      string WRUUgVlfmN;
      string jjmnlyOVUg;
      string EAQnmwcrgy;
      string KGdgHznnjH;
      string DpVexkObku;
      string CQHCIWBghk;
      string rsynCcGGgl;
      string JZkMdOekqB;
      string hBGlutzaXk;
      string yHGzPJqgcT;
      string dHtzkceuYt;
      string qPpgCplMsI;
      string dfhwmCTkwT;
      string WyIWXZGHBS;
      string ODCdsiRYwY;
      string WemTpyZyLh;
      string IsyEWsHTJc;
      string jeLZsZcEDE;
      if(RJJRcpVIrg == hBGlutzaXk){ktoXxrKnfY = true;}
      else if(hBGlutzaXk == RJJRcpVIrg){MqWUFqpVkU = true;}
      if(VBQXsQlbjM == yHGzPJqgcT){zIwSJVExGz = true;}
      else if(yHGzPJqgcT == VBQXsQlbjM){cyfTtyAJTN = true;}
      if(WRUUgVlfmN == dHtzkceuYt){axPSorSMaQ = true;}
      else if(dHtzkceuYt == WRUUgVlfmN){FVNLLhkmWf = true;}
      if(jjmnlyOVUg == qPpgCplMsI){UVuGxOEaHe = true;}
      else if(qPpgCplMsI == jjmnlyOVUg){DkzoASDbxE = true;}
      if(EAQnmwcrgy == dfhwmCTkwT){hSmjdahrPW = true;}
      else if(dfhwmCTkwT == EAQnmwcrgy){zCFHglCXIG = true;}
      if(KGdgHznnjH == WyIWXZGHBS){UfxDdmdVhE = true;}
      else if(WyIWXZGHBS == KGdgHznnjH){juEStqdLIW = true;}
      if(DpVexkObku == ODCdsiRYwY){YxNODdNpUu = true;}
      else if(ODCdsiRYwY == DpVexkObku){FDyERqzpTa = true;}
      if(CQHCIWBghk == WemTpyZyLh){RdpbRIJfoN = true;}
      if(rsynCcGGgl == IsyEWsHTJc){KZwDuoXqcJ = true;}
      if(JZkMdOekqB == jeLZsZcEDE){jirDFkFYgA = true;}
      while(WemTpyZyLh == CQHCIWBghk){uXMOOCPGdZ = true;}
      while(IsyEWsHTJc == IsyEWsHTJc){fNdQwHfgtJ = true;}
      while(jeLZsZcEDE == jeLZsZcEDE){oqSZzwEBoo = true;}
      if(ktoXxrKnfY == true){ktoXxrKnfY = false;}
      if(zIwSJVExGz == true){zIwSJVExGz = false;}
      if(axPSorSMaQ == true){axPSorSMaQ = false;}
      if(UVuGxOEaHe == true){UVuGxOEaHe = false;}
      if(hSmjdahrPW == true){hSmjdahrPW = false;}
      if(UfxDdmdVhE == true){UfxDdmdVhE = false;}
      if(YxNODdNpUu == true){YxNODdNpUu = false;}
      if(RdpbRIJfoN == true){RdpbRIJfoN = false;}
      if(KZwDuoXqcJ == true){KZwDuoXqcJ = false;}
      if(jirDFkFYgA == true){jirDFkFYgA = false;}
      if(MqWUFqpVkU == true){MqWUFqpVkU = false;}
      if(cyfTtyAJTN == true){cyfTtyAJTN = false;}
      if(FVNLLhkmWf == true){FVNLLhkmWf = false;}
      if(DkzoASDbxE == true){DkzoASDbxE = false;}
      if(zCFHglCXIG == true){zCFHglCXIG = false;}
      if(juEStqdLIW == true){juEStqdLIW = false;}
      if(FDyERqzpTa == true){FDyERqzpTa = false;}
      if(uXMOOCPGdZ == true){uXMOOCPGdZ = false;}
      if(fNdQwHfgtJ == true){fNdQwHfgtJ = false;}
      if(oqSZzwEBoo == true){oqSZzwEBoo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQCXFYPKGQ
{ 
  void cglKIXGpuo()
  { 
      bool ABQOQSJtWX = false;
      bool prIYLnndVs = false;
      bool aOmKaQmJeU = false;
      bool juPeXTTxoq = false;
      bool hFRDkuFOBJ = false;
      bool YrwWYkNGnz = false;
      bool eAPBmtcdAr = false;
      bool TpodLUwjYe = false;
      bool KYIUwqzrFm = false;
      bool FNJoMhpQPp = false;
      bool RbOJpiDSLE = false;
      bool ndgInGrtEu = false;
      bool ukXNlGfzRc = false;
      bool efTiMiKzeN = false;
      bool nffByafBAG = false;
      bool puMUugDAWi = false;
      bool CEBhYIKywF = false;
      bool usPqHOEWOL = false;
      bool aeyKmiTzne = false;
      bool eJbwKiexbo = false;
      string NiXVdBijwp;
      string RVrNSmrAjm;
      string qNsAHeYLHI;
      string qKbtcpLiEF;
      string cWNzAKIdBu;
      string WmQteApWOz;
      string cWbnzHsyjb;
      string bIweKTzsAw;
      string WuKMlEshOc;
      string AnUFcGuZAs;
      string QJtYTNqliK;
      string BwWRbgMOBu;
      string NLjGbmnpBD;
      string YYsHfNBksX;
      string NGyDbDRCcw;
      string sfXEeEYmxf;
      string ZAjflbDPlO;
      string eaVchGNgeY;
      string UkMFJrAnbb;
      string nOmMyMWRQA;
      if(NiXVdBijwp == QJtYTNqliK){ABQOQSJtWX = true;}
      else if(QJtYTNqliK == NiXVdBijwp){RbOJpiDSLE = true;}
      if(RVrNSmrAjm == BwWRbgMOBu){prIYLnndVs = true;}
      else if(BwWRbgMOBu == RVrNSmrAjm){ndgInGrtEu = true;}
      if(qNsAHeYLHI == NLjGbmnpBD){aOmKaQmJeU = true;}
      else if(NLjGbmnpBD == qNsAHeYLHI){ukXNlGfzRc = true;}
      if(qKbtcpLiEF == YYsHfNBksX){juPeXTTxoq = true;}
      else if(YYsHfNBksX == qKbtcpLiEF){efTiMiKzeN = true;}
      if(cWNzAKIdBu == NGyDbDRCcw){hFRDkuFOBJ = true;}
      else if(NGyDbDRCcw == cWNzAKIdBu){nffByafBAG = true;}
      if(WmQteApWOz == sfXEeEYmxf){YrwWYkNGnz = true;}
      else if(sfXEeEYmxf == WmQteApWOz){puMUugDAWi = true;}
      if(cWbnzHsyjb == ZAjflbDPlO){eAPBmtcdAr = true;}
      else if(ZAjflbDPlO == cWbnzHsyjb){CEBhYIKywF = true;}
      if(bIweKTzsAw == eaVchGNgeY){TpodLUwjYe = true;}
      if(WuKMlEshOc == UkMFJrAnbb){KYIUwqzrFm = true;}
      if(AnUFcGuZAs == nOmMyMWRQA){FNJoMhpQPp = true;}
      while(eaVchGNgeY == bIweKTzsAw){usPqHOEWOL = true;}
      while(UkMFJrAnbb == UkMFJrAnbb){aeyKmiTzne = true;}
      while(nOmMyMWRQA == nOmMyMWRQA){eJbwKiexbo = true;}
      if(ABQOQSJtWX == true){ABQOQSJtWX = false;}
      if(prIYLnndVs == true){prIYLnndVs = false;}
      if(aOmKaQmJeU == true){aOmKaQmJeU = false;}
      if(juPeXTTxoq == true){juPeXTTxoq = false;}
      if(hFRDkuFOBJ == true){hFRDkuFOBJ = false;}
      if(YrwWYkNGnz == true){YrwWYkNGnz = false;}
      if(eAPBmtcdAr == true){eAPBmtcdAr = false;}
      if(TpodLUwjYe == true){TpodLUwjYe = false;}
      if(KYIUwqzrFm == true){KYIUwqzrFm = false;}
      if(FNJoMhpQPp == true){FNJoMhpQPp = false;}
      if(RbOJpiDSLE == true){RbOJpiDSLE = false;}
      if(ndgInGrtEu == true){ndgInGrtEu = false;}
      if(ukXNlGfzRc == true){ukXNlGfzRc = false;}
      if(efTiMiKzeN == true){efTiMiKzeN = false;}
      if(nffByafBAG == true){nffByafBAG = false;}
      if(puMUugDAWi == true){puMUugDAWi = false;}
      if(CEBhYIKywF == true){CEBhYIKywF = false;}
      if(usPqHOEWOL == true){usPqHOEWOL = false;}
      if(aeyKmiTzne == true){aeyKmiTzne = false;}
      if(eJbwKiexbo == true){eJbwKiexbo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UQEASKVGDB
{ 
  void sNPldAwtUu()
  { 
      bool IatUHkkObX = false;
      bool FyEfZfrFla = false;
      bool pWqdNdyMZq = false;
      bool wFeAufNfWi = false;
      bool rbUKGCFeid = false;
      bool JYfGMliPHd = false;
      bool mXnkbzSDjt = false;
      bool SMiChNBgXK = false;
      bool XTdwgWZYnI = false;
      bool wyYrwTnjiG = false;
      bool iCtnLxpcXy = false;
      bool kCqwFStqDE = false;
      bool ZtPayTmpGO = false;
      bool ZQxRbVYokj = false;
      bool gwApXsGcld = false;
      bool ZwfdfnmSpq = false;
      bool KAWJYTEZUj = false;
      bool sEGTXctYDE = false;
      bool NJDcockSkm = false;
      bool hGztYgZpRD = false;
      string NPMeHZqbiM;
      string catsWLSEEe;
      string PTBdjHDZkT;
      string xNgUzbsKJZ;
      string QKwYFTjoMG;
      string nXnktsNhuz;
      string VRpOOOsZsu;
      string SHtdOEWbYP;
      string XOMdfZYwaF;
      string NKPKDzThKp;
      string aKuRngcKWo;
      string VkJebHELio;
      string pxymgHrjZP;
      string koRioMSupy;
      string wOYkjbBjiw;
      string tHyUzcLIjg;
      string nsjHEgTapO;
      string nJVjsaXMDE;
      string GHAdUcpxiL;
      string BKKJKCeRgC;
      if(NPMeHZqbiM == aKuRngcKWo){IatUHkkObX = true;}
      else if(aKuRngcKWo == NPMeHZqbiM){iCtnLxpcXy = true;}
      if(catsWLSEEe == VkJebHELio){FyEfZfrFla = true;}
      else if(VkJebHELio == catsWLSEEe){kCqwFStqDE = true;}
      if(PTBdjHDZkT == pxymgHrjZP){pWqdNdyMZq = true;}
      else if(pxymgHrjZP == PTBdjHDZkT){ZtPayTmpGO = true;}
      if(xNgUzbsKJZ == koRioMSupy){wFeAufNfWi = true;}
      else if(koRioMSupy == xNgUzbsKJZ){ZQxRbVYokj = true;}
      if(QKwYFTjoMG == wOYkjbBjiw){rbUKGCFeid = true;}
      else if(wOYkjbBjiw == QKwYFTjoMG){gwApXsGcld = true;}
      if(nXnktsNhuz == tHyUzcLIjg){JYfGMliPHd = true;}
      else if(tHyUzcLIjg == nXnktsNhuz){ZwfdfnmSpq = true;}
      if(VRpOOOsZsu == nsjHEgTapO){mXnkbzSDjt = true;}
      else if(nsjHEgTapO == VRpOOOsZsu){KAWJYTEZUj = true;}
      if(SHtdOEWbYP == nJVjsaXMDE){SMiChNBgXK = true;}
      if(XOMdfZYwaF == GHAdUcpxiL){XTdwgWZYnI = true;}
      if(NKPKDzThKp == BKKJKCeRgC){wyYrwTnjiG = true;}
      while(nJVjsaXMDE == SHtdOEWbYP){sEGTXctYDE = true;}
      while(GHAdUcpxiL == GHAdUcpxiL){NJDcockSkm = true;}
      while(BKKJKCeRgC == BKKJKCeRgC){hGztYgZpRD = true;}
      if(IatUHkkObX == true){IatUHkkObX = false;}
      if(FyEfZfrFla == true){FyEfZfrFla = false;}
      if(pWqdNdyMZq == true){pWqdNdyMZq = false;}
      if(wFeAufNfWi == true){wFeAufNfWi = false;}
      if(rbUKGCFeid == true){rbUKGCFeid = false;}
      if(JYfGMliPHd == true){JYfGMliPHd = false;}
      if(mXnkbzSDjt == true){mXnkbzSDjt = false;}
      if(SMiChNBgXK == true){SMiChNBgXK = false;}
      if(XTdwgWZYnI == true){XTdwgWZYnI = false;}
      if(wyYrwTnjiG == true){wyYrwTnjiG = false;}
      if(iCtnLxpcXy == true){iCtnLxpcXy = false;}
      if(kCqwFStqDE == true){kCqwFStqDE = false;}
      if(ZtPayTmpGO == true){ZtPayTmpGO = false;}
      if(ZQxRbVYokj == true){ZQxRbVYokj = false;}
      if(gwApXsGcld == true){gwApXsGcld = false;}
      if(ZwfdfnmSpq == true){ZwfdfnmSpq = false;}
      if(KAWJYTEZUj == true){KAWJYTEZUj = false;}
      if(sEGTXctYDE == true){sEGTXctYDE = false;}
      if(NJDcockSkm == true){NJDcockSkm = false;}
      if(hGztYgZpRD == true){hGztYgZpRD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GYCJQWHNXK
{ 
  void twdJrdrJUb()
  { 
      bool XZSGVjzfXl = false;
      bool KTcyFQgErF = false;
      bool PXzGwtjiEh = false;
      bool BjylbRHRXn = false;
      bool KioQFkahop = false;
      bool BAErMAZLKa = false;
      bool AQapjaUpWm = false;
      bool IOfEtghiBK = false;
      bool TBsOgBfGZa = false;
      bool quHxntHzfe = false;
      bool PjLBglTAxf = false;
      bool RqKzHyWMJi = false;
      bool uOQuwMHiPA = false;
      bool YiDVujprgt = false;
      bool gfIsJAkHoo = false;
      bool XtowjASPFT = false;
      bool dkjxGhmnDX = false;
      bool HefOBOGWlu = false;
      bool bzsabetGlt = false;
      bool QalMQwwKla = false;
      string ZoWODriMVh;
      string fKjGoVtqrp;
      string YcHZjqnDcF;
      string JFKJpfXDlQ;
      string YjSObmzeRQ;
      string ynoHrwgweM;
      string DeiQYZzZPI;
      string xpEbRoJsxx;
      string rJlMGVQDQs;
      string ybYZNsACpC;
      string mYOITIiNoD;
      string lnyhTssWJC;
      string JuJWKVRdOX;
      string nHCuJTudry;
      string lDNNHKcqGT;
      string zdrnrrPryx;
      string qEyQPelCXA;
      string yPdLPGgwOz;
      string rZXtYKONCQ;
      string EDfuGhEwxc;
      if(ZoWODriMVh == mYOITIiNoD){XZSGVjzfXl = true;}
      else if(mYOITIiNoD == ZoWODriMVh){PjLBglTAxf = true;}
      if(fKjGoVtqrp == lnyhTssWJC){KTcyFQgErF = true;}
      else if(lnyhTssWJC == fKjGoVtqrp){RqKzHyWMJi = true;}
      if(YcHZjqnDcF == JuJWKVRdOX){PXzGwtjiEh = true;}
      else if(JuJWKVRdOX == YcHZjqnDcF){uOQuwMHiPA = true;}
      if(JFKJpfXDlQ == nHCuJTudry){BjylbRHRXn = true;}
      else if(nHCuJTudry == JFKJpfXDlQ){YiDVujprgt = true;}
      if(YjSObmzeRQ == lDNNHKcqGT){KioQFkahop = true;}
      else if(lDNNHKcqGT == YjSObmzeRQ){gfIsJAkHoo = true;}
      if(ynoHrwgweM == zdrnrrPryx){BAErMAZLKa = true;}
      else if(zdrnrrPryx == ynoHrwgweM){XtowjASPFT = true;}
      if(DeiQYZzZPI == qEyQPelCXA){AQapjaUpWm = true;}
      else if(qEyQPelCXA == DeiQYZzZPI){dkjxGhmnDX = true;}
      if(xpEbRoJsxx == yPdLPGgwOz){IOfEtghiBK = true;}
      if(rJlMGVQDQs == rZXtYKONCQ){TBsOgBfGZa = true;}
      if(ybYZNsACpC == EDfuGhEwxc){quHxntHzfe = true;}
      while(yPdLPGgwOz == xpEbRoJsxx){HefOBOGWlu = true;}
      while(rZXtYKONCQ == rZXtYKONCQ){bzsabetGlt = true;}
      while(EDfuGhEwxc == EDfuGhEwxc){QalMQwwKla = true;}
      if(XZSGVjzfXl == true){XZSGVjzfXl = false;}
      if(KTcyFQgErF == true){KTcyFQgErF = false;}
      if(PXzGwtjiEh == true){PXzGwtjiEh = false;}
      if(BjylbRHRXn == true){BjylbRHRXn = false;}
      if(KioQFkahop == true){KioQFkahop = false;}
      if(BAErMAZLKa == true){BAErMAZLKa = false;}
      if(AQapjaUpWm == true){AQapjaUpWm = false;}
      if(IOfEtghiBK == true){IOfEtghiBK = false;}
      if(TBsOgBfGZa == true){TBsOgBfGZa = false;}
      if(quHxntHzfe == true){quHxntHzfe = false;}
      if(PjLBglTAxf == true){PjLBglTAxf = false;}
      if(RqKzHyWMJi == true){RqKzHyWMJi = false;}
      if(uOQuwMHiPA == true){uOQuwMHiPA = false;}
      if(YiDVujprgt == true){YiDVujprgt = false;}
      if(gfIsJAkHoo == true){gfIsJAkHoo = false;}
      if(XtowjASPFT == true){XtowjASPFT = false;}
      if(dkjxGhmnDX == true){dkjxGhmnDX = false;}
      if(HefOBOGWlu == true){HefOBOGWlu = false;}
      if(bzsabetGlt == true){bzsabetGlt = false;}
      if(QalMQwwKla == true){QalMQwwKla = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UYKHYOLRED
{ 
  void gJccPdYzTh()
  { 
      bool ZoWLiarMRN = false;
      bool hICRWDoFRp = false;
      bool BLfzzlkKtb = false;
      bool SzKCbktoFI = false;
      bool IAYBbtBjme = false;
      bool BPHulOIXMx = false;
      bool ogRouhxAol = false;
      bool JzAIgAldWE = false;
      bool jAWPaCrPPN = false;
      bool bVcHSahjGs = false;
      bool wAtBVBPyNl = false;
      bool beBHNnKCNr = false;
      bool phjbKmWroF = false;
      bool RCXcHiGVsZ = false;
      bool msBdkwUVte = false;
      bool QfVNDOQSqh = false;
      bool eWJITZHYzd = false;
      bool hnInFwgGpN = false;
      bool SByKnlfJYs = false;
      bool SmeLuPjsJL = false;
      string IenwVuoULe;
      string mMCcjqNNIX;
      string jLnEyYbIdC;
      string oKptRxhGWf;
      string DfhbhbmulP;
      string bzkSKwqjxx;
      string TfpIpcVILl;
      string IHqbUEcMWW;
      string lfWNZpYXiU;
      string GyIZMWoYkF;
      string FdiAHUHJyG;
      string SdNaKmJbiA;
      string DyYqeKzQOx;
      string OEbRRHwWGF;
      string hPZcBckgOZ;
      string NNpjBGErUw;
      string VqtBqOCuJC;
      string pmUdSmYwoC;
      string ZRBoiBNqPK;
      string DEBKipUYkm;
      if(IenwVuoULe == FdiAHUHJyG){ZoWLiarMRN = true;}
      else if(FdiAHUHJyG == IenwVuoULe){wAtBVBPyNl = true;}
      if(mMCcjqNNIX == SdNaKmJbiA){hICRWDoFRp = true;}
      else if(SdNaKmJbiA == mMCcjqNNIX){beBHNnKCNr = true;}
      if(jLnEyYbIdC == DyYqeKzQOx){BLfzzlkKtb = true;}
      else if(DyYqeKzQOx == jLnEyYbIdC){phjbKmWroF = true;}
      if(oKptRxhGWf == OEbRRHwWGF){SzKCbktoFI = true;}
      else if(OEbRRHwWGF == oKptRxhGWf){RCXcHiGVsZ = true;}
      if(DfhbhbmulP == hPZcBckgOZ){IAYBbtBjme = true;}
      else if(hPZcBckgOZ == DfhbhbmulP){msBdkwUVte = true;}
      if(bzkSKwqjxx == NNpjBGErUw){BPHulOIXMx = true;}
      else if(NNpjBGErUw == bzkSKwqjxx){QfVNDOQSqh = true;}
      if(TfpIpcVILl == VqtBqOCuJC){ogRouhxAol = true;}
      else if(VqtBqOCuJC == TfpIpcVILl){eWJITZHYzd = true;}
      if(IHqbUEcMWW == pmUdSmYwoC){JzAIgAldWE = true;}
      if(lfWNZpYXiU == ZRBoiBNqPK){jAWPaCrPPN = true;}
      if(GyIZMWoYkF == DEBKipUYkm){bVcHSahjGs = true;}
      while(pmUdSmYwoC == IHqbUEcMWW){hnInFwgGpN = true;}
      while(ZRBoiBNqPK == ZRBoiBNqPK){SByKnlfJYs = true;}
      while(DEBKipUYkm == DEBKipUYkm){SmeLuPjsJL = true;}
      if(ZoWLiarMRN == true){ZoWLiarMRN = false;}
      if(hICRWDoFRp == true){hICRWDoFRp = false;}
      if(BLfzzlkKtb == true){BLfzzlkKtb = false;}
      if(SzKCbktoFI == true){SzKCbktoFI = false;}
      if(IAYBbtBjme == true){IAYBbtBjme = false;}
      if(BPHulOIXMx == true){BPHulOIXMx = false;}
      if(ogRouhxAol == true){ogRouhxAol = false;}
      if(JzAIgAldWE == true){JzAIgAldWE = false;}
      if(jAWPaCrPPN == true){jAWPaCrPPN = false;}
      if(bVcHSahjGs == true){bVcHSahjGs = false;}
      if(wAtBVBPyNl == true){wAtBVBPyNl = false;}
      if(beBHNnKCNr == true){beBHNnKCNr = false;}
      if(phjbKmWroF == true){phjbKmWroF = false;}
      if(RCXcHiGVsZ == true){RCXcHiGVsZ = false;}
      if(msBdkwUVte == true){msBdkwUVte = false;}
      if(QfVNDOQSqh == true){QfVNDOQSqh = false;}
      if(eWJITZHYzd == true){eWJITZHYzd = false;}
      if(hnInFwgGpN == true){hnInFwgGpN = false;}
      if(SByKnlfJYs == true){SByKnlfJYs = false;}
      if(SmeLuPjsJL == true){SmeLuPjsJL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BYKGEZSOWD
{ 
  void mabBrXKltu()
  { 
      bool oAsRgBJjjA = false;
      bool sgLINDhcBn = false;
      bool TymjhClgCq = false;
      bool IWYUIYojcW = false;
      bool SOcjjEGtrB = false;
      bool YxbVspNJie = false;
      bool PbgsqVIpAn = false;
      bool NyzeVEVDzc = false;
      bool wrnBSKtCbR = false;
      bool LfAyHqhjrO = false;
      bool wPtEmZxxAn = false;
      bool UKJGiXmeZf = false;
      bool bFOhbhyBXe = false;
      bool WkKkffxjOr = false;
      bool MxCnxBVtPi = false;
      bool DCJLlqBLbE = false;
      bool bwZVQizXZC = false;
      bool ZDQhTeDaja = false;
      bool LDlnaUazyo = false;
      bool ekHJQQWfWN = false;
      string ldwUydmlzq;
      string YgrlzVfQaA;
      string ttzBPqebaf;
      string lKjNhoJxRg;
      string ypLdxtILOw;
      string LWtqtreuFG;
      string zKLTFOxeDJ;
      string MhytCDhVDU;
      string hTNdUPPrSo;
      string KOrKgmdqYi;
      string xdHEjcXAop;
      string JJqjYfxgzp;
      string yEMNzxpnMO;
      string YqwTWELIsq;
      string qODbfBXHlB;
      string pxrijsRsFm;
      string ljnZQSMWNU;
      string TnmHyjAjhx;
      string ZiBKYbyNjc;
      string lRCGEHadKM;
      if(ldwUydmlzq == xdHEjcXAop){oAsRgBJjjA = true;}
      else if(xdHEjcXAop == ldwUydmlzq){wPtEmZxxAn = true;}
      if(YgrlzVfQaA == JJqjYfxgzp){sgLINDhcBn = true;}
      else if(JJqjYfxgzp == YgrlzVfQaA){UKJGiXmeZf = true;}
      if(ttzBPqebaf == yEMNzxpnMO){TymjhClgCq = true;}
      else if(yEMNzxpnMO == ttzBPqebaf){bFOhbhyBXe = true;}
      if(lKjNhoJxRg == YqwTWELIsq){IWYUIYojcW = true;}
      else if(YqwTWELIsq == lKjNhoJxRg){WkKkffxjOr = true;}
      if(ypLdxtILOw == qODbfBXHlB){SOcjjEGtrB = true;}
      else if(qODbfBXHlB == ypLdxtILOw){MxCnxBVtPi = true;}
      if(LWtqtreuFG == pxrijsRsFm){YxbVspNJie = true;}
      else if(pxrijsRsFm == LWtqtreuFG){DCJLlqBLbE = true;}
      if(zKLTFOxeDJ == ljnZQSMWNU){PbgsqVIpAn = true;}
      else if(ljnZQSMWNU == zKLTFOxeDJ){bwZVQizXZC = true;}
      if(MhytCDhVDU == TnmHyjAjhx){NyzeVEVDzc = true;}
      if(hTNdUPPrSo == ZiBKYbyNjc){wrnBSKtCbR = true;}
      if(KOrKgmdqYi == lRCGEHadKM){LfAyHqhjrO = true;}
      while(TnmHyjAjhx == MhytCDhVDU){ZDQhTeDaja = true;}
      while(ZiBKYbyNjc == ZiBKYbyNjc){LDlnaUazyo = true;}
      while(lRCGEHadKM == lRCGEHadKM){ekHJQQWfWN = true;}
      if(oAsRgBJjjA == true){oAsRgBJjjA = false;}
      if(sgLINDhcBn == true){sgLINDhcBn = false;}
      if(TymjhClgCq == true){TymjhClgCq = false;}
      if(IWYUIYojcW == true){IWYUIYojcW = false;}
      if(SOcjjEGtrB == true){SOcjjEGtrB = false;}
      if(YxbVspNJie == true){YxbVspNJie = false;}
      if(PbgsqVIpAn == true){PbgsqVIpAn = false;}
      if(NyzeVEVDzc == true){NyzeVEVDzc = false;}
      if(wrnBSKtCbR == true){wrnBSKtCbR = false;}
      if(LfAyHqhjrO == true){LfAyHqhjrO = false;}
      if(wPtEmZxxAn == true){wPtEmZxxAn = false;}
      if(UKJGiXmeZf == true){UKJGiXmeZf = false;}
      if(bFOhbhyBXe == true){bFOhbhyBXe = false;}
      if(WkKkffxjOr == true){WkKkffxjOr = false;}
      if(MxCnxBVtPi == true){MxCnxBVtPi = false;}
      if(DCJLlqBLbE == true){DCJLlqBLbE = false;}
      if(bwZVQizXZC == true){bwZVQizXZC = false;}
      if(ZDQhTeDaja == true){ZDQhTeDaja = false;}
      if(LDlnaUazyo == true){LDlnaUazyo = false;}
      if(ekHJQQWfWN == true){ekHJQQWfWN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IRJYIOIOWR
{ 
  void RZRQXgJZSq()
  { 
      bool HOokEplESX = false;
      bool BVbAhueHOT = false;
      bool HVjHRWjRGz = false;
      bool wYEFyonfRo = false;
      bool IynpnTPpDp = false;
      bool OzFsAkegTg = false;
      bool FUySbbRVCs = false;
      bool HzoYLJhsSy = false;
      bool GsNPkwTKFM = false;
      bool JGMjjmAVOM = false;
      bool BsnKiPJghq = false;
      bool DlOUZLGhge = false;
      bool IGQoiBlEoX = false;
      bool ILeGwNFDgV = false;
      bool mmcNIXqqKX = false;
      bool gRnjDucybh = false;
      bool cEqJhqHHXM = false;
      bool GDBLqUcCgK = false;
      bool JutQqqXtCB = false;
      bool kGbzsiuTfQ = false;
      string XMxUJCcIfj;
      string UnFJSDdRbn;
      string lIzIzNwMzb;
      string ycdjutmraW;
      string EeFiGMCnTU;
      string byYZHONnVw;
      string FPIEkrKVOX;
      string PlpFjHCQCm;
      string KIsdAzEDbf;
      string gyVeQnVBxN;
      string BgYwEoISpA;
      string MwlikxWdDk;
      string nGshpRQLow;
      string lBSnkdiwZK;
      string qkNbTkMmsS;
      string QqxMZtnqFm;
      string YxdsOLcxxH;
      string OaErsCsROF;
      string EcRVetDGNp;
      string prplltGTMI;
      if(XMxUJCcIfj == BgYwEoISpA){HOokEplESX = true;}
      else if(BgYwEoISpA == XMxUJCcIfj){BsnKiPJghq = true;}
      if(UnFJSDdRbn == MwlikxWdDk){BVbAhueHOT = true;}
      else if(MwlikxWdDk == UnFJSDdRbn){DlOUZLGhge = true;}
      if(lIzIzNwMzb == nGshpRQLow){HVjHRWjRGz = true;}
      else if(nGshpRQLow == lIzIzNwMzb){IGQoiBlEoX = true;}
      if(ycdjutmraW == lBSnkdiwZK){wYEFyonfRo = true;}
      else if(lBSnkdiwZK == ycdjutmraW){ILeGwNFDgV = true;}
      if(EeFiGMCnTU == qkNbTkMmsS){IynpnTPpDp = true;}
      else if(qkNbTkMmsS == EeFiGMCnTU){mmcNIXqqKX = true;}
      if(byYZHONnVw == QqxMZtnqFm){OzFsAkegTg = true;}
      else if(QqxMZtnqFm == byYZHONnVw){gRnjDucybh = true;}
      if(FPIEkrKVOX == YxdsOLcxxH){FUySbbRVCs = true;}
      else if(YxdsOLcxxH == FPIEkrKVOX){cEqJhqHHXM = true;}
      if(PlpFjHCQCm == OaErsCsROF){HzoYLJhsSy = true;}
      if(KIsdAzEDbf == EcRVetDGNp){GsNPkwTKFM = true;}
      if(gyVeQnVBxN == prplltGTMI){JGMjjmAVOM = true;}
      while(OaErsCsROF == PlpFjHCQCm){GDBLqUcCgK = true;}
      while(EcRVetDGNp == EcRVetDGNp){JutQqqXtCB = true;}
      while(prplltGTMI == prplltGTMI){kGbzsiuTfQ = true;}
      if(HOokEplESX == true){HOokEplESX = false;}
      if(BVbAhueHOT == true){BVbAhueHOT = false;}
      if(HVjHRWjRGz == true){HVjHRWjRGz = false;}
      if(wYEFyonfRo == true){wYEFyonfRo = false;}
      if(IynpnTPpDp == true){IynpnTPpDp = false;}
      if(OzFsAkegTg == true){OzFsAkegTg = false;}
      if(FUySbbRVCs == true){FUySbbRVCs = false;}
      if(HzoYLJhsSy == true){HzoYLJhsSy = false;}
      if(GsNPkwTKFM == true){GsNPkwTKFM = false;}
      if(JGMjjmAVOM == true){JGMjjmAVOM = false;}
      if(BsnKiPJghq == true){BsnKiPJghq = false;}
      if(DlOUZLGhge == true){DlOUZLGhge = false;}
      if(IGQoiBlEoX == true){IGQoiBlEoX = false;}
      if(ILeGwNFDgV == true){ILeGwNFDgV = false;}
      if(mmcNIXqqKX == true){mmcNIXqqKX = false;}
      if(gRnjDucybh == true){gRnjDucybh = false;}
      if(cEqJhqHHXM == true){cEqJhqHHXM = false;}
      if(GDBLqUcCgK == true){GDBLqUcCgK = false;}
      if(JutQqqXtCB == true){JutQqqXtCB = false;}
      if(kGbzsiuTfQ == true){kGbzsiuTfQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NLGEIQBYVT
{ 
  void tZOqXGdrCc()
  { 
      bool tGFpzEnBIC = false;
      bool LuyyRFginY = false;
      bool ggRbjaTHIO = false;
      bool McWiYcbjPE = false;
      bool KXHTUIGpkk = false;
      bool qPATlModFY = false;
      bool kfrspiXPZo = false;
      bool cxSjOJZyGb = false;
      bool TcVWWwcDwL = false;
      bool nydpSdeNcl = false;
      bool jqQwHtwPEc = false;
      bool lqWdEHKUWs = false;
      bool FUSNAeTbQk = false;
      bool eMUTqcMYPc = false;
      bool zMyTZwazlL = false;
      bool SJqjgPYCub = false;
      bool aTyTyZWDmb = false;
      bool ulFssrVznE = false;
      bool ETpFRUVkma = false;
      bool DJcmCfOdUA = false;
      string qpMCTRaeNM;
      string yxeKzGZlGk;
      string iNFdpJsYYZ;
      string zziQemEuur;
      string gVOdVwEIoj;
      string NFIZgckhMK;
      string YBFnNzNOeM;
      string CeqODNzbIs;
      string FkjnMtpJiC;
      string BVhkTfPaPW;
      string hpdchiNsVT;
      string dJZTEmQQaT;
      string IEebKfwGuX;
      string xXLkKPHHFc;
      string fxmOYquOff;
      string OzzwOdKBRC;
      string mHyyWFxoIo;
      string fJKymLRPCS;
      string jhZPJyYPWg;
      string EFoDpYyorT;
      if(qpMCTRaeNM == hpdchiNsVT){tGFpzEnBIC = true;}
      else if(hpdchiNsVT == qpMCTRaeNM){jqQwHtwPEc = true;}
      if(yxeKzGZlGk == dJZTEmQQaT){LuyyRFginY = true;}
      else if(dJZTEmQQaT == yxeKzGZlGk){lqWdEHKUWs = true;}
      if(iNFdpJsYYZ == IEebKfwGuX){ggRbjaTHIO = true;}
      else if(IEebKfwGuX == iNFdpJsYYZ){FUSNAeTbQk = true;}
      if(zziQemEuur == xXLkKPHHFc){McWiYcbjPE = true;}
      else if(xXLkKPHHFc == zziQemEuur){eMUTqcMYPc = true;}
      if(gVOdVwEIoj == fxmOYquOff){KXHTUIGpkk = true;}
      else if(fxmOYquOff == gVOdVwEIoj){zMyTZwazlL = true;}
      if(NFIZgckhMK == OzzwOdKBRC){qPATlModFY = true;}
      else if(OzzwOdKBRC == NFIZgckhMK){SJqjgPYCub = true;}
      if(YBFnNzNOeM == mHyyWFxoIo){kfrspiXPZo = true;}
      else if(mHyyWFxoIo == YBFnNzNOeM){aTyTyZWDmb = true;}
      if(CeqODNzbIs == fJKymLRPCS){cxSjOJZyGb = true;}
      if(FkjnMtpJiC == jhZPJyYPWg){TcVWWwcDwL = true;}
      if(BVhkTfPaPW == EFoDpYyorT){nydpSdeNcl = true;}
      while(fJKymLRPCS == CeqODNzbIs){ulFssrVznE = true;}
      while(jhZPJyYPWg == jhZPJyYPWg){ETpFRUVkma = true;}
      while(EFoDpYyorT == EFoDpYyorT){DJcmCfOdUA = true;}
      if(tGFpzEnBIC == true){tGFpzEnBIC = false;}
      if(LuyyRFginY == true){LuyyRFginY = false;}
      if(ggRbjaTHIO == true){ggRbjaTHIO = false;}
      if(McWiYcbjPE == true){McWiYcbjPE = false;}
      if(KXHTUIGpkk == true){KXHTUIGpkk = false;}
      if(qPATlModFY == true){qPATlModFY = false;}
      if(kfrspiXPZo == true){kfrspiXPZo = false;}
      if(cxSjOJZyGb == true){cxSjOJZyGb = false;}
      if(TcVWWwcDwL == true){TcVWWwcDwL = false;}
      if(nydpSdeNcl == true){nydpSdeNcl = false;}
      if(jqQwHtwPEc == true){jqQwHtwPEc = false;}
      if(lqWdEHKUWs == true){lqWdEHKUWs = false;}
      if(FUSNAeTbQk == true){FUSNAeTbQk = false;}
      if(eMUTqcMYPc == true){eMUTqcMYPc = false;}
      if(zMyTZwazlL == true){zMyTZwazlL = false;}
      if(SJqjgPYCub == true){SJqjgPYCub = false;}
      if(aTyTyZWDmb == true){aTyTyZWDmb = false;}
      if(ulFssrVznE == true){ulFssrVznE = false;}
      if(ETpFRUVkma == true){ETpFRUVkma = false;}
      if(DJcmCfOdUA == true){DJcmCfOdUA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FSWYIMPSRJ
{ 
  void DpPkiWafFj()
  { 
      bool FsyFWHWuHr = false;
      bool FjCMDqNaQO = false;
      bool NRXheVABQj = false;
      bool CHkVxsQAEg = false;
      bool VqohhEzoZZ = false;
      bool mNGazmUPaB = false;
      bool HUdXpxzgOJ = false;
      bool aMWisWcoAZ = false;
      bool VKbpwnAKVJ = false;
      bool XAYDYBMRqj = false;
      bool FSZPzZqWgc = false;
      bool KfPAewsmaC = false;
      bool xoKElZnTKr = false;
      bool JLyPUDkLqW = false;
      bool xccszrjYXc = false;
      bool HZpomPHVdZ = false;
      bool lWMoTzhAeb = false;
      bool LhuEFTMRFs = false;
      bool pOugjiUIcE = false;
      bool uPgRjZPmZz = false;
      string QDpCwLQiLT;
      string ZAXOTaKcab;
      string mBJAuqbrss;
      string uXLzqUsRAs;
      string ApCVUfHFmE;
      string gbGezOspGE;
      string jXoSXBnXXz;
      string hrbgawzneO;
      string jVFoLTRgAb;
      string aDKuJcBjxT;
      string rignVnzZDC;
      string OFKrUNSzGE;
      string iHXuXehfWy;
      string tPpLWAoQTX;
      string TrcxMUrSZw;
      string JCdsjjKlPp;
      string GSCFHzPzUU;
      string YBehkqeaiD;
      string mOFaorlxam;
      string oCBdRAoXoM;
      if(QDpCwLQiLT == rignVnzZDC){FsyFWHWuHr = true;}
      else if(rignVnzZDC == QDpCwLQiLT){FSZPzZqWgc = true;}
      if(ZAXOTaKcab == OFKrUNSzGE){FjCMDqNaQO = true;}
      else if(OFKrUNSzGE == ZAXOTaKcab){KfPAewsmaC = true;}
      if(mBJAuqbrss == iHXuXehfWy){NRXheVABQj = true;}
      else if(iHXuXehfWy == mBJAuqbrss){xoKElZnTKr = true;}
      if(uXLzqUsRAs == tPpLWAoQTX){CHkVxsQAEg = true;}
      else if(tPpLWAoQTX == uXLzqUsRAs){JLyPUDkLqW = true;}
      if(ApCVUfHFmE == TrcxMUrSZw){VqohhEzoZZ = true;}
      else if(TrcxMUrSZw == ApCVUfHFmE){xccszrjYXc = true;}
      if(gbGezOspGE == JCdsjjKlPp){mNGazmUPaB = true;}
      else if(JCdsjjKlPp == gbGezOspGE){HZpomPHVdZ = true;}
      if(jXoSXBnXXz == GSCFHzPzUU){HUdXpxzgOJ = true;}
      else if(GSCFHzPzUU == jXoSXBnXXz){lWMoTzhAeb = true;}
      if(hrbgawzneO == YBehkqeaiD){aMWisWcoAZ = true;}
      if(jVFoLTRgAb == mOFaorlxam){VKbpwnAKVJ = true;}
      if(aDKuJcBjxT == oCBdRAoXoM){XAYDYBMRqj = true;}
      while(YBehkqeaiD == hrbgawzneO){LhuEFTMRFs = true;}
      while(mOFaorlxam == mOFaorlxam){pOugjiUIcE = true;}
      while(oCBdRAoXoM == oCBdRAoXoM){uPgRjZPmZz = true;}
      if(FsyFWHWuHr == true){FsyFWHWuHr = false;}
      if(FjCMDqNaQO == true){FjCMDqNaQO = false;}
      if(NRXheVABQj == true){NRXheVABQj = false;}
      if(CHkVxsQAEg == true){CHkVxsQAEg = false;}
      if(VqohhEzoZZ == true){VqohhEzoZZ = false;}
      if(mNGazmUPaB == true){mNGazmUPaB = false;}
      if(HUdXpxzgOJ == true){HUdXpxzgOJ = false;}
      if(aMWisWcoAZ == true){aMWisWcoAZ = false;}
      if(VKbpwnAKVJ == true){VKbpwnAKVJ = false;}
      if(XAYDYBMRqj == true){XAYDYBMRqj = false;}
      if(FSZPzZqWgc == true){FSZPzZqWgc = false;}
      if(KfPAewsmaC == true){KfPAewsmaC = false;}
      if(xoKElZnTKr == true){xoKElZnTKr = false;}
      if(JLyPUDkLqW == true){JLyPUDkLqW = false;}
      if(xccszrjYXc == true){xccszrjYXc = false;}
      if(HZpomPHVdZ == true){HZpomPHVdZ = false;}
      if(lWMoTzhAeb == true){lWMoTzhAeb = false;}
      if(LhuEFTMRFs == true){LhuEFTMRFs = false;}
      if(pOugjiUIcE == true){pOugjiUIcE = false;}
      if(uPgRjZPmZz == true){uPgRjZPmZz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YXMNXDVHTZ
{ 
  void yAmCwPIVpU()
  { 
      bool GJfgwrYNhX = false;
      bool TBKBPjtobD = false;
      bool qAtRFzEKXE = false;
      bool IncofuGwnI = false;
      bool CIKaZIywNX = false;
      bool efrsJGONbw = false;
      bool mOpdPeXVVT = false;
      bool cyBSAioTqx = false;
      bool BIwzYcwjfY = false;
      bool gsUqVnSfLu = false;
      bool jbasugdYrZ = false;
      bool RuWdueRpEl = false;
      bool inpxmjdJxM = false;
      bool QIHwMZhDEr = false;
      bool yWqFGkVpwq = false;
      bool WbbZLuldFK = false;
      bool CUbfJInaRV = false;
      bool xOlMmMwkpC = false;
      bool NmMGpnghjR = false;
      bool mDxsoduLux = false;
      string UybVVEbmfj;
      string aIIsfndnTO;
      string JTExbBUaTn;
      string NnbHtseWRG;
      string jTxKQRhFNo;
      string HScDJBsdtT;
      string iBSrVlfBym;
      string JGVMdoVtgJ;
      string SPMeftLXxs;
      string zAbxXiAFnd;
      string lgGaeBwPZT;
      string ezwjBSnnLb;
      string aHEFmJdYou;
      string nQFCXlJkze;
      string xwycOADruE;
      string tMtMDdbBnV;
      string WXZdfNstLO;
      string ICnfdeJapm;
      string FlcjBbVszt;
      string JIxdIZVUxB;
      if(UybVVEbmfj == lgGaeBwPZT){GJfgwrYNhX = true;}
      else if(lgGaeBwPZT == UybVVEbmfj){jbasugdYrZ = true;}
      if(aIIsfndnTO == ezwjBSnnLb){TBKBPjtobD = true;}
      else if(ezwjBSnnLb == aIIsfndnTO){RuWdueRpEl = true;}
      if(JTExbBUaTn == aHEFmJdYou){qAtRFzEKXE = true;}
      else if(aHEFmJdYou == JTExbBUaTn){inpxmjdJxM = true;}
      if(NnbHtseWRG == nQFCXlJkze){IncofuGwnI = true;}
      else if(nQFCXlJkze == NnbHtseWRG){QIHwMZhDEr = true;}
      if(jTxKQRhFNo == xwycOADruE){CIKaZIywNX = true;}
      else if(xwycOADruE == jTxKQRhFNo){yWqFGkVpwq = true;}
      if(HScDJBsdtT == tMtMDdbBnV){efrsJGONbw = true;}
      else if(tMtMDdbBnV == HScDJBsdtT){WbbZLuldFK = true;}
      if(iBSrVlfBym == WXZdfNstLO){mOpdPeXVVT = true;}
      else if(WXZdfNstLO == iBSrVlfBym){CUbfJInaRV = true;}
      if(JGVMdoVtgJ == ICnfdeJapm){cyBSAioTqx = true;}
      if(SPMeftLXxs == FlcjBbVszt){BIwzYcwjfY = true;}
      if(zAbxXiAFnd == JIxdIZVUxB){gsUqVnSfLu = true;}
      while(ICnfdeJapm == JGVMdoVtgJ){xOlMmMwkpC = true;}
      while(FlcjBbVszt == FlcjBbVszt){NmMGpnghjR = true;}
      while(JIxdIZVUxB == JIxdIZVUxB){mDxsoduLux = true;}
      if(GJfgwrYNhX == true){GJfgwrYNhX = false;}
      if(TBKBPjtobD == true){TBKBPjtobD = false;}
      if(qAtRFzEKXE == true){qAtRFzEKXE = false;}
      if(IncofuGwnI == true){IncofuGwnI = false;}
      if(CIKaZIywNX == true){CIKaZIywNX = false;}
      if(efrsJGONbw == true){efrsJGONbw = false;}
      if(mOpdPeXVVT == true){mOpdPeXVVT = false;}
      if(cyBSAioTqx == true){cyBSAioTqx = false;}
      if(BIwzYcwjfY == true){BIwzYcwjfY = false;}
      if(gsUqVnSfLu == true){gsUqVnSfLu = false;}
      if(jbasugdYrZ == true){jbasugdYrZ = false;}
      if(RuWdueRpEl == true){RuWdueRpEl = false;}
      if(inpxmjdJxM == true){inpxmjdJxM = false;}
      if(QIHwMZhDEr == true){QIHwMZhDEr = false;}
      if(yWqFGkVpwq == true){yWqFGkVpwq = false;}
      if(WbbZLuldFK == true){WbbZLuldFK = false;}
      if(CUbfJInaRV == true){CUbfJInaRV = false;}
      if(xOlMmMwkpC == true){xOlMmMwkpC = false;}
      if(NmMGpnghjR == true){NmMGpnghjR = false;}
      if(mDxsoduLux == true){mDxsoduLux = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BLENBVMLOE
{ 
  void PdRCuqlsuP()
  { 
      bool gHgXXUllZJ = false;
      bool AXkfbpGfhN = false;
      bool EIGSWGQNlq = false;
      bool cqfFlzeMlF = false;
      bool KkiZubpIDU = false;
      bool tHPHBXAOAQ = false;
      bool EXAhgIrfsb = false;
      bool LstbCTYgXt = false;
      bool QIJQwUaXDN = false;
      bool zQLVBlkArl = false;
      bool jKOaJBNnEg = false;
      bool ySpGzwOilL = false;
      bool hTbfctgYZQ = false;
      bool iYnlKFthGu = false;
      bool HmSWOgaFVF = false;
      bool XBOgDQihyP = false;
      bool ToNnxZdEwt = false;
      bool BfbqDtAEQw = false;
      bool TbCUshJHhs = false;
      bool WLiqaSYeYn = false;
      string iCWlLlbHeO;
      string xKMWWnPxHk;
      string OsflShRewp;
      string NQxPJNjNWf;
      string QzmCDxBDZr;
      string OxgeApVjSd;
      string UxLoAfMwMI;
      string ECZaUOFciU;
      string fOEDaPjRPS;
      string qztsLSmyCX;
      string jFpQnLXFKk;
      string jrByxFrINj;
      string wuftREIfPB;
      string aHaKjZXmOP;
      string rdGeiyxuuF;
      string ZejRboYwzi;
      string DqpIJbRpNX;
      string hFsyrRoBLS;
      string GMkJawWIiu;
      string AanfLBnxUG;
      if(iCWlLlbHeO == jFpQnLXFKk){gHgXXUllZJ = true;}
      else if(jFpQnLXFKk == iCWlLlbHeO){jKOaJBNnEg = true;}
      if(xKMWWnPxHk == jrByxFrINj){AXkfbpGfhN = true;}
      else if(jrByxFrINj == xKMWWnPxHk){ySpGzwOilL = true;}
      if(OsflShRewp == wuftREIfPB){EIGSWGQNlq = true;}
      else if(wuftREIfPB == OsflShRewp){hTbfctgYZQ = true;}
      if(NQxPJNjNWf == aHaKjZXmOP){cqfFlzeMlF = true;}
      else if(aHaKjZXmOP == NQxPJNjNWf){iYnlKFthGu = true;}
      if(QzmCDxBDZr == rdGeiyxuuF){KkiZubpIDU = true;}
      else if(rdGeiyxuuF == QzmCDxBDZr){HmSWOgaFVF = true;}
      if(OxgeApVjSd == ZejRboYwzi){tHPHBXAOAQ = true;}
      else if(ZejRboYwzi == OxgeApVjSd){XBOgDQihyP = true;}
      if(UxLoAfMwMI == DqpIJbRpNX){EXAhgIrfsb = true;}
      else if(DqpIJbRpNX == UxLoAfMwMI){ToNnxZdEwt = true;}
      if(ECZaUOFciU == hFsyrRoBLS){LstbCTYgXt = true;}
      if(fOEDaPjRPS == GMkJawWIiu){QIJQwUaXDN = true;}
      if(qztsLSmyCX == AanfLBnxUG){zQLVBlkArl = true;}
      while(hFsyrRoBLS == ECZaUOFciU){BfbqDtAEQw = true;}
      while(GMkJawWIiu == GMkJawWIiu){TbCUshJHhs = true;}
      while(AanfLBnxUG == AanfLBnxUG){WLiqaSYeYn = true;}
      if(gHgXXUllZJ == true){gHgXXUllZJ = false;}
      if(AXkfbpGfhN == true){AXkfbpGfhN = false;}
      if(EIGSWGQNlq == true){EIGSWGQNlq = false;}
      if(cqfFlzeMlF == true){cqfFlzeMlF = false;}
      if(KkiZubpIDU == true){KkiZubpIDU = false;}
      if(tHPHBXAOAQ == true){tHPHBXAOAQ = false;}
      if(EXAhgIrfsb == true){EXAhgIrfsb = false;}
      if(LstbCTYgXt == true){LstbCTYgXt = false;}
      if(QIJQwUaXDN == true){QIJQwUaXDN = false;}
      if(zQLVBlkArl == true){zQLVBlkArl = false;}
      if(jKOaJBNnEg == true){jKOaJBNnEg = false;}
      if(ySpGzwOilL == true){ySpGzwOilL = false;}
      if(hTbfctgYZQ == true){hTbfctgYZQ = false;}
      if(iYnlKFthGu == true){iYnlKFthGu = false;}
      if(HmSWOgaFVF == true){HmSWOgaFVF = false;}
      if(XBOgDQihyP == true){XBOgDQihyP = false;}
      if(ToNnxZdEwt == true){ToNnxZdEwt = false;}
      if(BfbqDtAEQw == true){BfbqDtAEQw = false;}
      if(TbCUshJHhs == true){TbCUshJHhs = false;}
      if(WLiqaSYeYn == true){WLiqaSYeYn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KRXQEARYWG
{ 
  void gBNQZYWEtT()
  { 
      bool dJJNhuJTdL = false;
      bool OzgxftgFDZ = false;
      bool QbUfAQzNQT = false;
      bool XhuSUROMNF = false;
      bool dEUTQWyhKX = false;
      bool SGCdFCndMR = false;
      bool wuCKmfDObN = false;
      bool eUqywLGAOd = false;
      bool SQCsBRfRMS = false;
      bool ckzwJhCKgk = false;
      bool TjGwrxOEht = false;
      bool unOhyesJIV = false;
      bool zkBIjtUtoN = false;
      bool JwTcKhKFAD = false;
      bool CajSXoVRxd = false;
      bool nrBKkhixMy = false;
      bool bTPTjyTkXQ = false;
      bool TmJESYAhju = false;
      bool YDxKYQuIrb = false;
      bool yMsBaiLQiZ = false;
      string CoEKKIuxqW;
      string YWyXGDGjQa;
      string YnsHemfKEX;
      string YgfGrYhwyI;
      string RIpWlsFEhN;
      string YBmocOuxfX;
      string bjsSyqpreh;
      string VKkIJQyWVk;
      string gbcpzXsqcc;
      string dkPafhPWYt;
      string CNYArNQefM;
      string QYatpAGCTa;
      string yzOBEktJcb;
      string AaxaiTCbyk;
      string GOKPMEJVjf;
      string aNCyuDyWwH;
      string SGCEMoaALW;
      string xeEiTjozoz;
      string aYZwAmYzee;
      string VfepRzLGDW;
      if(CoEKKIuxqW == CNYArNQefM){dJJNhuJTdL = true;}
      else if(CNYArNQefM == CoEKKIuxqW){TjGwrxOEht = true;}
      if(YWyXGDGjQa == QYatpAGCTa){OzgxftgFDZ = true;}
      else if(QYatpAGCTa == YWyXGDGjQa){unOhyesJIV = true;}
      if(YnsHemfKEX == yzOBEktJcb){QbUfAQzNQT = true;}
      else if(yzOBEktJcb == YnsHemfKEX){zkBIjtUtoN = true;}
      if(YgfGrYhwyI == AaxaiTCbyk){XhuSUROMNF = true;}
      else if(AaxaiTCbyk == YgfGrYhwyI){JwTcKhKFAD = true;}
      if(RIpWlsFEhN == GOKPMEJVjf){dEUTQWyhKX = true;}
      else if(GOKPMEJVjf == RIpWlsFEhN){CajSXoVRxd = true;}
      if(YBmocOuxfX == aNCyuDyWwH){SGCdFCndMR = true;}
      else if(aNCyuDyWwH == YBmocOuxfX){nrBKkhixMy = true;}
      if(bjsSyqpreh == SGCEMoaALW){wuCKmfDObN = true;}
      else if(SGCEMoaALW == bjsSyqpreh){bTPTjyTkXQ = true;}
      if(VKkIJQyWVk == xeEiTjozoz){eUqywLGAOd = true;}
      if(gbcpzXsqcc == aYZwAmYzee){SQCsBRfRMS = true;}
      if(dkPafhPWYt == VfepRzLGDW){ckzwJhCKgk = true;}
      while(xeEiTjozoz == VKkIJQyWVk){TmJESYAhju = true;}
      while(aYZwAmYzee == aYZwAmYzee){YDxKYQuIrb = true;}
      while(VfepRzLGDW == VfepRzLGDW){yMsBaiLQiZ = true;}
      if(dJJNhuJTdL == true){dJJNhuJTdL = false;}
      if(OzgxftgFDZ == true){OzgxftgFDZ = false;}
      if(QbUfAQzNQT == true){QbUfAQzNQT = false;}
      if(XhuSUROMNF == true){XhuSUROMNF = false;}
      if(dEUTQWyhKX == true){dEUTQWyhKX = false;}
      if(SGCdFCndMR == true){SGCdFCndMR = false;}
      if(wuCKmfDObN == true){wuCKmfDObN = false;}
      if(eUqywLGAOd == true){eUqywLGAOd = false;}
      if(SQCsBRfRMS == true){SQCsBRfRMS = false;}
      if(ckzwJhCKgk == true){ckzwJhCKgk = false;}
      if(TjGwrxOEht == true){TjGwrxOEht = false;}
      if(unOhyesJIV == true){unOhyesJIV = false;}
      if(zkBIjtUtoN == true){zkBIjtUtoN = false;}
      if(JwTcKhKFAD == true){JwTcKhKFAD = false;}
      if(CajSXoVRxd == true){CajSXoVRxd = false;}
      if(nrBKkhixMy == true){nrBKkhixMy = false;}
      if(bTPTjyTkXQ == true){bTPTjyTkXQ = false;}
      if(TmJESYAhju == true){TmJESYAhju = false;}
      if(YDxKYQuIrb == true){YDxKYQuIrb = false;}
      if(yMsBaiLQiZ == true){yMsBaiLQiZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IUTXZRTHWW
{ 
  void JOtiqaVmzb()
  { 
      bool jQbYCPOrqk = false;
      bool ymLXHtTZne = false;
      bool AssaxqHLlV = false;
      bool ebptSrKeXn = false;
      bool mrVyEmwyyu = false;
      bool zGsNHpXBaL = false;
      bool IDGVGWwQFP = false;
      bool ioCAqHWtWJ = false;
      bool uJNqVXhcmb = false;
      bool TJDMfjkAqg = false;
      bool pfsiLKEsVz = false;
      bool TceRPyoPzi = false;
      bool oTccuZkoTH = false;
      bool WVDoSOQeeL = false;
      bool SnHnIqelwg = false;
      bool tVBIrWCPml = false;
      bool ZOZNcxZoyA = false;
      bool hKjmPAMnUE = false;
      bool tzslNATtxw = false;
      bool MBqslDOsLK = false;
      string HkBBwIQmTI;
      string ppyXtlihOk;
      string yrXUFzMXKT;
      string JkjDwGirOR;
      string PwTNwAYiGV;
      string TrZOQONguw;
      string wrbzyFGtbm;
      string DqTxVCYKXF;
      string acQnAQKUmh;
      string sBwSUWTTOq;
      string tdHTSbYcsO;
      string oCIpVTbmzh;
      string tkHtsBtAbz;
      string hEufLxUxVX;
      string rhbYrqsGxB;
      string tfUgxIVNZQ;
      string hXAsfjHbdX;
      string yeRbpLJiCC;
      string ImDaEBjNiD;
      string aHWFoTghrH;
      if(HkBBwIQmTI == tdHTSbYcsO){jQbYCPOrqk = true;}
      else if(tdHTSbYcsO == HkBBwIQmTI){pfsiLKEsVz = true;}
      if(ppyXtlihOk == oCIpVTbmzh){ymLXHtTZne = true;}
      else if(oCIpVTbmzh == ppyXtlihOk){TceRPyoPzi = true;}
      if(yrXUFzMXKT == tkHtsBtAbz){AssaxqHLlV = true;}
      else if(tkHtsBtAbz == yrXUFzMXKT){oTccuZkoTH = true;}
      if(JkjDwGirOR == hEufLxUxVX){ebptSrKeXn = true;}
      else if(hEufLxUxVX == JkjDwGirOR){WVDoSOQeeL = true;}
      if(PwTNwAYiGV == rhbYrqsGxB){mrVyEmwyyu = true;}
      else if(rhbYrqsGxB == PwTNwAYiGV){SnHnIqelwg = true;}
      if(TrZOQONguw == tfUgxIVNZQ){zGsNHpXBaL = true;}
      else if(tfUgxIVNZQ == TrZOQONguw){tVBIrWCPml = true;}
      if(wrbzyFGtbm == hXAsfjHbdX){IDGVGWwQFP = true;}
      else if(hXAsfjHbdX == wrbzyFGtbm){ZOZNcxZoyA = true;}
      if(DqTxVCYKXF == yeRbpLJiCC){ioCAqHWtWJ = true;}
      if(acQnAQKUmh == ImDaEBjNiD){uJNqVXhcmb = true;}
      if(sBwSUWTTOq == aHWFoTghrH){TJDMfjkAqg = true;}
      while(yeRbpLJiCC == DqTxVCYKXF){hKjmPAMnUE = true;}
      while(ImDaEBjNiD == ImDaEBjNiD){tzslNATtxw = true;}
      while(aHWFoTghrH == aHWFoTghrH){MBqslDOsLK = true;}
      if(jQbYCPOrqk == true){jQbYCPOrqk = false;}
      if(ymLXHtTZne == true){ymLXHtTZne = false;}
      if(AssaxqHLlV == true){AssaxqHLlV = false;}
      if(ebptSrKeXn == true){ebptSrKeXn = false;}
      if(mrVyEmwyyu == true){mrVyEmwyyu = false;}
      if(zGsNHpXBaL == true){zGsNHpXBaL = false;}
      if(IDGVGWwQFP == true){IDGVGWwQFP = false;}
      if(ioCAqHWtWJ == true){ioCAqHWtWJ = false;}
      if(uJNqVXhcmb == true){uJNqVXhcmb = false;}
      if(TJDMfjkAqg == true){TJDMfjkAqg = false;}
      if(pfsiLKEsVz == true){pfsiLKEsVz = false;}
      if(TceRPyoPzi == true){TceRPyoPzi = false;}
      if(oTccuZkoTH == true){oTccuZkoTH = false;}
      if(WVDoSOQeeL == true){WVDoSOQeeL = false;}
      if(SnHnIqelwg == true){SnHnIqelwg = false;}
      if(tVBIrWCPml == true){tVBIrWCPml = false;}
      if(ZOZNcxZoyA == true){ZOZNcxZoyA = false;}
      if(hKjmPAMnUE == true){hKjmPAMnUE = false;}
      if(tzslNATtxw == true){tzslNATtxw = false;}
      if(MBqslDOsLK == true){MBqslDOsLK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NIDEATPPKG
{ 
  void IdeHGwbcem()
  { 
      bool ukGFYzEAfM = false;
      bool fyyVAiFphK = false;
      bool rMMQasaKiY = false;
      bool MLDBQqnCaM = false;
      bool hwLuegafnC = false;
      bool XsDTahYpee = false;
      bool XsRGATuxFJ = false;
      bool uCOVbwARls = false;
      bool RtWfBSHjZh = false;
      bool RyXwnndFtK = false;
      bool ldaeHUehqe = false;
      bool hGDlMdWlEg = false;
      bool LLWXqxeSgn = false;
      bool RtWaGnTrYg = false;
      bool nZruzLtkiK = false;
      bool QrBMyaGCmJ = false;
      bool pLACMmjbeY = false;
      bool JeNWslSbXf = false;
      bool DsjWWZsJcf = false;
      bool gQEOqbZphM = false;
      string TchJWFDHFg;
      string PXlBzxfwNM;
      string bkxByGwLNz;
      string MmcPBJXHuP;
      string hPMwGCIAhk;
      string dkfNBhffKP;
      string JqsGUctVzo;
      string ZXAyeMYBtw;
      string xuccVaHPOT;
      string dqweGpVGad;
      string IlAsLFjhin;
      string IdkORNNQjs;
      string UeHfLhbVqn;
      string qSZQnLtjRP;
      string qYgaKzFgMr;
      string cEVhIdeUhc;
      string dOptxpEUaG;
      string TczUCwygVL;
      string btIzLlxqHK;
      string fZCnlcildT;
      if(TchJWFDHFg == IlAsLFjhin){ukGFYzEAfM = true;}
      else if(IlAsLFjhin == TchJWFDHFg){ldaeHUehqe = true;}
      if(PXlBzxfwNM == IdkORNNQjs){fyyVAiFphK = true;}
      else if(IdkORNNQjs == PXlBzxfwNM){hGDlMdWlEg = true;}
      if(bkxByGwLNz == UeHfLhbVqn){rMMQasaKiY = true;}
      else if(UeHfLhbVqn == bkxByGwLNz){LLWXqxeSgn = true;}
      if(MmcPBJXHuP == qSZQnLtjRP){MLDBQqnCaM = true;}
      else if(qSZQnLtjRP == MmcPBJXHuP){RtWaGnTrYg = true;}
      if(hPMwGCIAhk == qYgaKzFgMr){hwLuegafnC = true;}
      else if(qYgaKzFgMr == hPMwGCIAhk){nZruzLtkiK = true;}
      if(dkfNBhffKP == cEVhIdeUhc){XsDTahYpee = true;}
      else if(cEVhIdeUhc == dkfNBhffKP){QrBMyaGCmJ = true;}
      if(JqsGUctVzo == dOptxpEUaG){XsRGATuxFJ = true;}
      else if(dOptxpEUaG == JqsGUctVzo){pLACMmjbeY = true;}
      if(ZXAyeMYBtw == TczUCwygVL){uCOVbwARls = true;}
      if(xuccVaHPOT == btIzLlxqHK){RtWfBSHjZh = true;}
      if(dqweGpVGad == fZCnlcildT){RyXwnndFtK = true;}
      while(TczUCwygVL == ZXAyeMYBtw){JeNWslSbXf = true;}
      while(btIzLlxqHK == btIzLlxqHK){DsjWWZsJcf = true;}
      while(fZCnlcildT == fZCnlcildT){gQEOqbZphM = true;}
      if(ukGFYzEAfM == true){ukGFYzEAfM = false;}
      if(fyyVAiFphK == true){fyyVAiFphK = false;}
      if(rMMQasaKiY == true){rMMQasaKiY = false;}
      if(MLDBQqnCaM == true){MLDBQqnCaM = false;}
      if(hwLuegafnC == true){hwLuegafnC = false;}
      if(XsDTahYpee == true){XsDTahYpee = false;}
      if(XsRGATuxFJ == true){XsRGATuxFJ = false;}
      if(uCOVbwARls == true){uCOVbwARls = false;}
      if(RtWfBSHjZh == true){RtWfBSHjZh = false;}
      if(RyXwnndFtK == true){RyXwnndFtK = false;}
      if(ldaeHUehqe == true){ldaeHUehqe = false;}
      if(hGDlMdWlEg == true){hGDlMdWlEg = false;}
      if(LLWXqxeSgn == true){LLWXqxeSgn = false;}
      if(RtWaGnTrYg == true){RtWaGnTrYg = false;}
      if(nZruzLtkiK == true){nZruzLtkiK = false;}
      if(QrBMyaGCmJ == true){QrBMyaGCmJ = false;}
      if(pLACMmjbeY == true){pLACMmjbeY = false;}
      if(JeNWslSbXf == true){JeNWslSbXf = false;}
      if(DsjWWZsJcf == true){DsjWWZsJcf = false;}
      if(gQEOqbZphM == true){gQEOqbZphM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BOTGTFPKIQ
{ 
  void DoZEpFZlaj()
  { 
      bool VGBLxXBFMZ = false;
      bool wsFzqhTeSs = false;
      bool ZgGKjrVSmq = false;
      bool TAXMGWaFEF = false;
      bool wVTLApzfCo = false;
      bool sOYxFozqaF = false;
      bool BiRVGuVrrU = false;
      bool HOZNxDMtKs = false;
      bool rpQxxEbZGR = false;
      bool WjdzDNDxFE = false;
      bool UHmhhenLAB = false;
      bool bEfhMKSUXC = false;
      bool TukaxXjaJj = false;
      bool APoFXkDiPS = false;
      bool PPZFoSDwms = false;
      bool uiYDkYVLjK = false;
      bool tNCPBMOZJa = false;
      bool GjEFlDVfle = false;
      bool TnmPoRplUz = false;
      bool PryFYCNJDb = false;
      string dJymCPxpkk;
      string fnjPkhiqPX;
      string hjbcqqqrDN;
      string BhVyScmxDU;
      string mdhGZlrSwq;
      string hUZiJtgUwK;
      string YFmXjxRlwH;
      string tlntkEBUCE;
      string yXwLefHlnY;
      string uRArwhqJVc;
      string TGVnxwgfyF;
      string rMSqMAIbsE;
      string ofxXLbkwyC;
      string NqyZjrCHOh;
      string zbmifizIeu;
      string YOQRmnIxbU;
      string KkhwrANsHT;
      string xBMKFNrOrc;
      string cbQCcyaglw;
      string jFetXNtqqe;
      if(dJymCPxpkk == TGVnxwgfyF){VGBLxXBFMZ = true;}
      else if(TGVnxwgfyF == dJymCPxpkk){UHmhhenLAB = true;}
      if(fnjPkhiqPX == rMSqMAIbsE){wsFzqhTeSs = true;}
      else if(rMSqMAIbsE == fnjPkhiqPX){bEfhMKSUXC = true;}
      if(hjbcqqqrDN == ofxXLbkwyC){ZgGKjrVSmq = true;}
      else if(ofxXLbkwyC == hjbcqqqrDN){TukaxXjaJj = true;}
      if(BhVyScmxDU == NqyZjrCHOh){TAXMGWaFEF = true;}
      else if(NqyZjrCHOh == BhVyScmxDU){APoFXkDiPS = true;}
      if(mdhGZlrSwq == zbmifizIeu){wVTLApzfCo = true;}
      else if(zbmifizIeu == mdhGZlrSwq){PPZFoSDwms = true;}
      if(hUZiJtgUwK == YOQRmnIxbU){sOYxFozqaF = true;}
      else if(YOQRmnIxbU == hUZiJtgUwK){uiYDkYVLjK = true;}
      if(YFmXjxRlwH == KkhwrANsHT){BiRVGuVrrU = true;}
      else if(KkhwrANsHT == YFmXjxRlwH){tNCPBMOZJa = true;}
      if(tlntkEBUCE == xBMKFNrOrc){HOZNxDMtKs = true;}
      if(yXwLefHlnY == cbQCcyaglw){rpQxxEbZGR = true;}
      if(uRArwhqJVc == jFetXNtqqe){WjdzDNDxFE = true;}
      while(xBMKFNrOrc == tlntkEBUCE){GjEFlDVfle = true;}
      while(cbQCcyaglw == cbQCcyaglw){TnmPoRplUz = true;}
      while(jFetXNtqqe == jFetXNtqqe){PryFYCNJDb = true;}
      if(VGBLxXBFMZ == true){VGBLxXBFMZ = false;}
      if(wsFzqhTeSs == true){wsFzqhTeSs = false;}
      if(ZgGKjrVSmq == true){ZgGKjrVSmq = false;}
      if(TAXMGWaFEF == true){TAXMGWaFEF = false;}
      if(wVTLApzfCo == true){wVTLApzfCo = false;}
      if(sOYxFozqaF == true){sOYxFozqaF = false;}
      if(BiRVGuVrrU == true){BiRVGuVrrU = false;}
      if(HOZNxDMtKs == true){HOZNxDMtKs = false;}
      if(rpQxxEbZGR == true){rpQxxEbZGR = false;}
      if(WjdzDNDxFE == true){WjdzDNDxFE = false;}
      if(UHmhhenLAB == true){UHmhhenLAB = false;}
      if(bEfhMKSUXC == true){bEfhMKSUXC = false;}
      if(TukaxXjaJj == true){TukaxXjaJj = false;}
      if(APoFXkDiPS == true){APoFXkDiPS = false;}
      if(PPZFoSDwms == true){PPZFoSDwms = false;}
      if(uiYDkYVLjK == true){uiYDkYVLjK = false;}
      if(tNCPBMOZJa == true){tNCPBMOZJa = false;}
      if(GjEFlDVfle == true){GjEFlDVfle = false;}
      if(TnmPoRplUz == true){TnmPoRplUz = false;}
      if(PryFYCNJDb == true){PryFYCNJDb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SJMIRIHJOU
{ 
  void BlFbxGYFNE()
  { 
      bool LMheCIRLeQ = false;
      bool UpPXJjjmQb = false;
      bool WLxTShDjiZ = false;
      bool KgemKyLUdh = false;
      bool SQkQYTuory = false;
      bool kDLVzAPOLT = false;
      bool EhcFFnLbNK = false;
      bool YOJhIFZfuy = false;
      bool mOrjoHUJnK = false;
      bool hwJJcknfKj = false;
      bool ISagYVtdMs = false;
      bool aiTMfporQy = false;
      bool TBnCbbFzFW = false;
      bool RsUKpUmKLS = false;
      bool Npwuizcwdl = false;
      bool uuPMQGeYEw = false;
      bool QtYoahNIWL = false;
      bool DegxjcFsSc = false;
      bool zJVSbWcIsj = false;
      bool oNFOCSRGTB = false;
      string wnuAcSepdK;
      string YpVDTIhXpz;
      string TcyhTnBpnU;
      string KEoUuziMCp;
      string lPPcBXGMau;
      string oNwiHSpMfn;
      string RnBIzUAAIT;
      string YVVAMDMVgu;
      string hnPsfxHGNb;
      string IWfNXxNGcf;
      string XFEGWSrwVD;
      string GUejFcYIcB;
      string NsmfLCoHbO;
      string pGrAXcjIVM;
      string FLjKVnquHu;
      string YEcaSdSYuT;
      string djTHMzbeMc;
      string sQlQuCJbJW;
      string KszfpkcQgs;
      string KKMBhVqcxV;
      if(wnuAcSepdK == XFEGWSrwVD){LMheCIRLeQ = true;}
      else if(XFEGWSrwVD == wnuAcSepdK){ISagYVtdMs = true;}
      if(YpVDTIhXpz == GUejFcYIcB){UpPXJjjmQb = true;}
      else if(GUejFcYIcB == YpVDTIhXpz){aiTMfporQy = true;}
      if(TcyhTnBpnU == NsmfLCoHbO){WLxTShDjiZ = true;}
      else if(NsmfLCoHbO == TcyhTnBpnU){TBnCbbFzFW = true;}
      if(KEoUuziMCp == pGrAXcjIVM){KgemKyLUdh = true;}
      else if(pGrAXcjIVM == KEoUuziMCp){RsUKpUmKLS = true;}
      if(lPPcBXGMau == FLjKVnquHu){SQkQYTuory = true;}
      else if(FLjKVnquHu == lPPcBXGMau){Npwuizcwdl = true;}
      if(oNwiHSpMfn == YEcaSdSYuT){kDLVzAPOLT = true;}
      else if(YEcaSdSYuT == oNwiHSpMfn){uuPMQGeYEw = true;}
      if(RnBIzUAAIT == djTHMzbeMc){EhcFFnLbNK = true;}
      else if(djTHMzbeMc == RnBIzUAAIT){QtYoahNIWL = true;}
      if(YVVAMDMVgu == sQlQuCJbJW){YOJhIFZfuy = true;}
      if(hnPsfxHGNb == KszfpkcQgs){mOrjoHUJnK = true;}
      if(IWfNXxNGcf == KKMBhVqcxV){hwJJcknfKj = true;}
      while(sQlQuCJbJW == YVVAMDMVgu){DegxjcFsSc = true;}
      while(KszfpkcQgs == KszfpkcQgs){zJVSbWcIsj = true;}
      while(KKMBhVqcxV == KKMBhVqcxV){oNFOCSRGTB = true;}
      if(LMheCIRLeQ == true){LMheCIRLeQ = false;}
      if(UpPXJjjmQb == true){UpPXJjjmQb = false;}
      if(WLxTShDjiZ == true){WLxTShDjiZ = false;}
      if(KgemKyLUdh == true){KgemKyLUdh = false;}
      if(SQkQYTuory == true){SQkQYTuory = false;}
      if(kDLVzAPOLT == true){kDLVzAPOLT = false;}
      if(EhcFFnLbNK == true){EhcFFnLbNK = false;}
      if(YOJhIFZfuy == true){YOJhIFZfuy = false;}
      if(mOrjoHUJnK == true){mOrjoHUJnK = false;}
      if(hwJJcknfKj == true){hwJJcknfKj = false;}
      if(ISagYVtdMs == true){ISagYVtdMs = false;}
      if(aiTMfporQy == true){aiTMfporQy = false;}
      if(TBnCbbFzFW == true){TBnCbbFzFW = false;}
      if(RsUKpUmKLS == true){RsUKpUmKLS = false;}
      if(Npwuizcwdl == true){Npwuizcwdl = false;}
      if(uuPMQGeYEw == true){uuPMQGeYEw = false;}
      if(QtYoahNIWL == true){QtYoahNIWL = false;}
      if(DegxjcFsSc == true){DegxjcFsSc = false;}
      if(zJVSbWcIsj == true){zJVSbWcIsj = false;}
      if(oNFOCSRGTB == true){oNFOCSRGTB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MILIEWNYCF
{ 
  void bdViiFYUWx()
  { 
      bool YxIrjdHxtG = false;
      bool iwYdlruBHM = false;
      bool IaXLPAdDpc = false;
      bool zdrFVFuWNd = false;
      bool FbehsqQcXN = false;
      bool yyVKGxZxci = false;
      bool AEGQHFDTIg = false;
      bool xYmcGfwoRY = false;
      bool iAeceBIhyX = false;
      bool eytecBVOan = false;
      bool mxUqPYLrDZ = false;
      bool BjeDAAYdkG = false;
      bool xUVjBzeIAE = false;
      bool KhOcklfnMF = false;
      bool pPeXVuSpdc = false;
      bool crcUqSbjoQ = false;
      bool tCryPTVCSN = false;
      bool TjQeQgpxNG = false;
      bool gndWbSEtlR = false;
      bool KuywLmXfHB = false;
      string SMXyjDnxtJ;
      string hJziVAVayc;
      string PDkShMeyhw;
      string EPagPoVSTY;
      string XyqzUYpgYf;
      string ycusaOaEPX;
      string XpOxERhSTg;
      string dCGYFRMkxJ;
      string WxYBybUhFA;
      string NQCwAgisuD;
      string pXNrCuVWnI;
      string CpGGBaRNzc;
      string xAMTSMzKXX;
      string iTptSyjgzC;
      string FyswyXJwuZ;
      string PVtRFpLtYo;
      string wLyPZhzMnC;
      string pkNwXzGPUt;
      string CDPxINZYnc;
      string mpHKGtzcWP;
      if(SMXyjDnxtJ == pXNrCuVWnI){YxIrjdHxtG = true;}
      else if(pXNrCuVWnI == SMXyjDnxtJ){mxUqPYLrDZ = true;}
      if(hJziVAVayc == CpGGBaRNzc){iwYdlruBHM = true;}
      else if(CpGGBaRNzc == hJziVAVayc){BjeDAAYdkG = true;}
      if(PDkShMeyhw == xAMTSMzKXX){IaXLPAdDpc = true;}
      else if(xAMTSMzKXX == PDkShMeyhw){xUVjBzeIAE = true;}
      if(EPagPoVSTY == iTptSyjgzC){zdrFVFuWNd = true;}
      else if(iTptSyjgzC == EPagPoVSTY){KhOcklfnMF = true;}
      if(XyqzUYpgYf == FyswyXJwuZ){FbehsqQcXN = true;}
      else if(FyswyXJwuZ == XyqzUYpgYf){pPeXVuSpdc = true;}
      if(ycusaOaEPX == PVtRFpLtYo){yyVKGxZxci = true;}
      else if(PVtRFpLtYo == ycusaOaEPX){crcUqSbjoQ = true;}
      if(XpOxERhSTg == wLyPZhzMnC){AEGQHFDTIg = true;}
      else if(wLyPZhzMnC == XpOxERhSTg){tCryPTVCSN = true;}
      if(dCGYFRMkxJ == pkNwXzGPUt){xYmcGfwoRY = true;}
      if(WxYBybUhFA == CDPxINZYnc){iAeceBIhyX = true;}
      if(NQCwAgisuD == mpHKGtzcWP){eytecBVOan = true;}
      while(pkNwXzGPUt == dCGYFRMkxJ){TjQeQgpxNG = true;}
      while(CDPxINZYnc == CDPxINZYnc){gndWbSEtlR = true;}
      while(mpHKGtzcWP == mpHKGtzcWP){KuywLmXfHB = true;}
      if(YxIrjdHxtG == true){YxIrjdHxtG = false;}
      if(iwYdlruBHM == true){iwYdlruBHM = false;}
      if(IaXLPAdDpc == true){IaXLPAdDpc = false;}
      if(zdrFVFuWNd == true){zdrFVFuWNd = false;}
      if(FbehsqQcXN == true){FbehsqQcXN = false;}
      if(yyVKGxZxci == true){yyVKGxZxci = false;}
      if(AEGQHFDTIg == true){AEGQHFDTIg = false;}
      if(xYmcGfwoRY == true){xYmcGfwoRY = false;}
      if(iAeceBIhyX == true){iAeceBIhyX = false;}
      if(eytecBVOan == true){eytecBVOan = false;}
      if(mxUqPYLrDZ == true){mxUqPYLrDZ = false;}
      if(BjeDAAYdkG == true){BjeDAAYdkG = false;}
      if(xUVjBzeIAE == true){xUVjBzeIAE = false;}
      if(KhOcklfnMF == true){KhOcklfnMF = false;}
      if(pPeXVuSpdc == true){pPeXVuSpdc = false;}
      if(crcUqSbjoQ == true){crcUqSbjoQ = false;}
      if(tCryPTVCSN == true){tCryPTVCSN = false;}
      if(TjQeQgpxNG == true){TjQeQgpxNG = false;}
      if(gndWbSEtlR == true){gndWbSEtlR = false;}
      if(KuywLmXfHB == true){KuywLmXfHB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RBFUCULJIU
{ 
  void iXidUOUQAX()
  { 
      bool LjeTjHOYNq = false;
      bool dVmeKSrfrm = false;
      bool NJCdUfUTLY = false;
      bool LDPxmVCiWA = false;
      bool xAPsPkaJFx = false;
      bool CtarxChAzD = false;
      bool ltNofZGoqn = false;
      bool PJJqoNtIOi = false;
      bool FLOOWQcXAk = false;
      bool nBjSNDmaNo = false;
      bool dkRQgsjjCj = false;
      bool HYkPyafyRO = false;
      bool whoGAOYqcl = false;
      bool ZTtYFTsygc = false;
      bool gsVQcOPUTm = false;
      bool WnIzsuwLPS = false;
      bool TrGPJneMKe = false;
      bool hhRnhDMYcl = false;
      bool yEXpOlKtfJ = false;
      bool WghNJnlFGn = false;
      string lGzKrErGdX;
      string JTxTCTYGOi;
      string cDzFIbmUSm;
      string ZYkdxFRUMx;
      string QCirNYKZZt;
      string mnnrliGsBQ;
      string QWnpxjiSWx;
      string BDtQSZTGqj;
      string QNuXzkksqO;
      string yYTugsOrtc;
      string prDcrjtWZL;
      string PzBQADbPqL;
      string zpaHycjyjZ;
      string LaMOsYJSfP;
      string qNSfzzWCud;
      string QyBicARudP;
      string zumAAnmmXb;
      string sJjbUlWuIz;
      string FgCGIMZdks;
      string HNnPPuaSeK;
      if(lGzKrErGdX == prDcrjtWZL){LjeTjHOYNq = true;}
      else if(prDcrjtWZL == lGzKrErGdX){dkRQgsjjCj = true;}
      if(JTxTCTYGOi == PzBQADbPqL){dVmeKSrfrm = true;}
      else if(PzBQADbPqL == JTxTCTYGOi){HYkPyafyRO = true;}
      if(cDzFIbmUSm == zpaHycjyjZ){NJCdUfUTLY = true;}
      else if(zpaHycjyjZ == cDzFIbmUSm){whoGAOYqcl = true;}
      if(ZYkdxFRUMx == LaMOsYJSfP){LDPxmVCiWA = true;}
      else if(LaMOsYJSfP == ZYkdxFRUMx){ZTtYFTsygc = true;}
      if(QCirNYKZZt == qNSfzzWCud){xAPsPkaJFx = true;}
      else if(qNSfzzWCud == QCirNYKZZt){gsVQcOPUTm = true;}
      if(mnnrliGsBQ == QyBicARudP){CtarxChAzD = true;}
      else if(QyBicARudP == mnnrliGsBQ){WnIzsuwLPS = true;}
      if(QWnpxjiSWx == zumAAnmmXb){ltNofZGoqn = true;}
      else if(zumAAnmmXb == QWnpxjiSWx){TrGPJneMKe = true;}
      if(BDtQSZTGqj == sJjbUlWuIz){PJJqoNtIOi = true;}
      if(QNuXzkksqO == FgCGIMZdks){FLOOWQcXAk = true;}
      if(yYTugsOrtc == HNnPPuaSeK){nBjSNDmaNo = true;}
      while(sJjbUlWuIz == BDtQSZTGqj){hhRnhDMYcl = true;}
      while(FgCGIMZdks == FgCGIMZdks){yEXpOlKtfJ = true;}
      while(HNnPPuaSeK == HNnPPuaSeK){WghNJnlFGn = true;}
      if(LjeTjHOYNq == true){LjeTjHOYNq = false;}
      if(dVmeKSrfrm == true){dVmeKSrfrm = false;}
      if(NJCdUfUTLY == true){NJCdUfUTLY = false;}
      if(LDPxmVCiWA == true){LDPxmVCiWA = false;}
      if(xAPsPkaJFx == true){xAPsPkaJFx = false;}
      if(CtarxChAzD == true){CtarxChAzD = false;}
      if(ltNofZGoqn == true){ltNofZGoqn = false;}
      if(PJJqoNtIOi == true){PJJqoNtIOi = false;}
      if(FLOOWQcXAk == true){FLOOWQcXAk = false;}
      if(nBjSNDmaNo == true){nBjSNDmaNo = false;}
      if(dkRQgsjjCj == true){dkRQgsjjCj = false;}
      if(HYkPyafyRO == true){HYkPyafyRO = false;}
      if(whoGAOYqcl == true){whoGAOYqcl = false;}
      if(ZTtYFTsygc == true){ZTtYFTsygc = false;}
      if(gsVQcOPUTm == true){gsVQcOPUTm = false;}
      if(WnIzsuwLPS == true){WnIzsuwLPS = false;}
      if(TrGPJneMKe == true){TrGPJneMKe = false;}
      if(hhRnhDMYcl == true){hhRnhDMYcl = false;}
      if(yEXpOlKtfJ == true){yEXpOlKtfJ = false;}
      if(WghNJnlFGn == true){WghNJnlFGn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCOMTFJTEU
{ 
  void IzhZHVNkmY()
  { 
      bool InpsCGPauV = false;
      bool XqsqhNIpCa = false;
      bool NlFqhKzIuN = false;
      bool TDTYriINxo = false;
      bool jchInfLhFo = false;
      bool IYQnPVhyKr = false;
      bool GHfhBTXUyy = false;
      bool FusNqkDwDB = false;
      bool yRCFFumfJV = false;
      bool AJCEhbxAHT = false;
      bool IqiHjNfDwd = false;
      bool RltIsoFZcG = false;
      bool gqLbyurneP = false;
      bool nDojsGitVq = false;
      bool PjieEOOsLs = false;
      bool VWWAlQfGJn = false;
      bool UqXgpOwKPl = false;
      bool GKEkqwIfXi = false;
      bool gyclsQfnxb = false;
      bool abkgWXMCnp = false;
      string oxgFxuuZzn;
      string kqjiWkCJJu;
      string DglfExeUnS;
      string cfNgwEtFBD;
      string xnSwANBgkr;
      string AcPWCHKABz;
      string QalgLFdClS;
      string pwHGxOOpfp;
      string wxjuSAPpdn;
      string stECmWClku;
      string iytRBDUJYn;
      string sUUKDSppNK;
      string onYyZwqFTa;
      string MbEjHxCRsP;
      string fFQpuYYszT;
      string fMYaFuZwrF;
      string LOpyaQPjDF;
      string QYwyeiWiCA;
      string XyGzuADdeL;
      string XFYnDQPSOd;
      if(oxgFxuuZzn == iytRBDUJYn){InpsCGPauV = true;}
      else if(iytRBDUJYn == oxgFxuuZzn){IqiHjNfDwd = true;}
      if(kqjiWkCJJu == sUUKDSppNK){XqsqhNIpCa = true;}
      else if(sUUKDSppNK == kqjiWkCJJu){RltIsoFZcG = true;}
      if(DglfExeUnS == onYyZwqFTa){NlFqhKzIuN = true;}
      else if(onYyZwqFTa == DglfExeUnS){gqLbyurneP = true;}
      if(cfNgwEtFBD == MbEjHxCRsP){TDTYriINxo = true;}
      else if(MbEjHxCRsP == cfNgwEtFBD){nDojsGitVq = true;}
      if(xnSwANBgkr == fFQpuYYszT){jchInfLhFo = true;}
      else if(fFQpuYYszT == xnSwANBgkr){PjieEOOsLs = true;}
      if(AcPWCHKABz == fMYaFuZwrF){IYQnPVhyKr = true;}
      else if(fMYaFuZwrF == AcPWCHKABz){VWWAlQfGJn = true;}
      if(QalgLFdClS == LOpyaQPjDF){GHfhBTXUyy = true;}
      else if(LOpyaQPjDF == QalgLFdClS){UqXgpOwKPl = true;}
      if(pwHGxOOpfp == QYwyeiWiCA){FusNqkDwDB = true;}
      if(wxjuSAPpdn == XyGzuADdeL){yRCFFumfJV = true;}
      if(stECmWClku == XFYnDQPSOd){AJCEhbxAHT = true;}
      while(QYwyeiWiCA == pwHGxOOpfp){GKEkqwIfXi = true;}
      while(XyGzuADdeL == XyGzuADdeL){gyclsQfnxb = true;}
      while(XFYnDQPSOd == XFYnDQPSOd){abkgWXMCnp = true;}
      if(InpsCGPauV == true){InpsCGPauV = false;}
      if(XqsqhNIpCa == true){XqsqhNIpCa = false;}
      if(NlFqhKzIuN == true){NlFqhKzIuN = false;}
      if(TDTYriINxo == true){TDTYriINxo = false;}
      if(jchInfLhFo == true){jchInfLhFo = false;}
      if(IYQnPVhyKr == true){IYQnPVhyKr = false;}
      if(GHfhBTXUyy == true){GHfhBTXUyy = false;}
      if(FusNqkDwDB == true){FusNqkDwDB = false;}
      if(yRCFFumfJV == true){yRCFFumfJV = false;}
      if(AJCEhbxAHT == true){AJCEhbxAHT = false;}
      if(IqiHjNfDwd == true){IqiHjNfDwd = false;}
      if(RltIsoFZcG == true){RltIsoFZcG = false;}
      if(gqLbyurneP == true){gqLbyurneP = false;}
      if(nDojsGitVq == true){nDojsGitVq = false;}
      if(PjieEOOsLs == true){PjieEOOsLs = false;}
      if(VWWAlQfGJn == true){VWWAlQfGJn = false;}
      if(UqXgpOwKPl == true){UqXgpOwKPl = false;}
      if(GKEkqwIfXi == true){GKEkqwIfXi = false;}
      if(gyclsQfnxb == true){gyclsQfnxb = false;}
      if(abkgWXMCnp == true){abkgWXMCnp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JMQHMPPXSV
{ 
  void wNTmwoTcFw()
  { 
      bool PMoGULWxBb = false;
      bool QlFehoPWfP = false;
      bool NjrmJoIFgh = false;
      bool WdecpKJBnC = false;
      bool IJWDHpUVRo = false;
      bool uBdeDeUCxe = false;
      bool DQQSEmHbnW = false;
      bool fOhcHEMofS = false;
      bool TmnrlVzzZK = false;
      bool oHEJzqsDyT = false;
      bool isgtJgSBXz = false;
      bool RfWdKPcYgh = false;
      bool mHCchYJYdP = false;
      bool LJpLjaFshE = false;
      bool CybZsJjayi = false;
      bool NTWPgapDLk = false;
      bool XtXHmIpLsj = false;
      bool JipbfoebjY = false;
      bool nhZtCqlZeI = false;
      bool kChxgIaUlj = false;
      string fZibhkmahk;
      string BtlVueDXmN;
      string EmFfHsoqyr;
      string yWQhRSMLFU;
      string MNfLEdejpf;
      string hprfqsUCTn;
      string uubpledEEb;
      string SrRSBqGsbd;
      string OFASJIdjpX;
      string yKqRZQkpZY;
      string zZfONpXYeA;
      string laZpZouJfd;
      string BsOfcHAAsj;
      string GQTCdnZlET;
      string jEFolWjBrj;
      string VaJuXFLzkF;
      string oXfttUHWLk;
      string PJELtwnZtF;
      string XzHIOeHXeY;
      string bZAzeLYKtQ;
      if(fZibhkmahk == zZfONpXYeA){PMoGULWxBb = true;}
      else if(zZfONpXYeA == fZibhkmahk){isgtJgSBXz = true;}
      if(BtlVueDXmN == laZpZouJfd){QlFehoPWfP = true;}
      else if(laZpZouJfd == BtlVueDXmN){RfWdKPcYgh = true;}
      if(EmFfHsoqyr == BsOfcHAAsj){NjrmJoIFgh = true;}
      else if(BsOfcHAAsj == EmFfHsoqyr){mHCchYJYdP = true;}
      if(yWQhRSMLFU == GQTCdnZlET){WdecpKJBnC = true;}
      else if(GQTCdnZlET == yWQhRSMLFU){LJpLjaFshE = true;}
      if(MNfLEdejpf == jEFolWjBrj){IJWDHpUVRo = true;}
      else if(jEFolWjBrj == MNfLEdejpf){CybZsJjayi = true;}
      if(hprfqsUCTn == VaJuXFLzkF){uBdeDeUCxe = true;}
      else if(VaJuXFLzkF == hprfqsUCTn){NTWPgapDLk = true;}
      if(uubpledEEb == oXfttUHWLk){DQQSEmHbnW = true;}
      else if(oXfttUHWLk == uubpledEEb){XtXHmIpLsj = true;}
      if(SrRSBqGsbd == PJELtwnZtF){fOhcHEMofS = true;}
      if(OFASJIdjpX == XzHIOeHXeY){TmnrlVzzZK = true;}
      if(yKqRZQkpZY == bZAzeLYKtQ){oHEJzqsDyT = true;}
      while(PJELtwnZtF == SrRSBqGsbd){JipbfoebjY = true;}
      while(XzHIOeHXeY == XzHIOeHXeY){nhZtCqlZeI = true;}
      while(bZAzeLYKtQ == bZAzeLYKtQ){kChxgIaUlj = true;}
      if(PMoGULWxBb == true){PMoGULWxBb = false;}
      if(QlFehoPWfP == true){QlFehoPWfP = false;}
      if(NjrmJoIFgh == true){NjrmJoIFgh = false;}
      if(WdecpKJBnC == true){WdecpKJBnC = false;}
      if(IJWDHpUVRo == true){IJWDHpUVRo = false;}
      if(uBdeDeUCxe == true){uBdeDeUCxe = false;}
      if(DQQSEmHbnW == true){DQQSEmHbnW = false;}
      if(fOhcHEMofS == true){fOhcHEMofS = false;}
      if(TmnrlVzzZK == true){TmnrlVzzZK = false;}
      if(oHEJzqsDyT == true){oHEJzqsDyT = false;}
      if(isgtJgSBXz == true){isgtJgSBXz = false;}
      if(RfWdKPcYgh == true){RfWdKPcYgh = false;}
      if(mHCchYJYdP == true){mHCchYJYdP = false;}
      if(LJpLjaFshE == true){LJpLjaFshE = false;}
      if(CybZsJjayi == true){CybZsJjayi = false;}
      if(NTWPgapDLk == true){NTWPgapDLk = false;}
      if(XtXHmIpLsj == true){XtXHmIpLsj = false;}
      if(JipbfoebjY == true){JipbfoebjY = false;}
      if(nhZtCqlZeI == true){nhZtCqlZeI = false;}
      if(kChxgIaUlj == true){kChxgIaUlj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ILKJOWDAPU
{ 
  void xHYcfJgmgu()
  { 
      bool BJAVkYcPQj = false;
      bool eKczEnyXqV = false;
      bool AZYMSxkJTg = false;
      bool NEjRYgWAAs = false;
      bool FqwAzMsJOG = false;
      bool JrXoQbjmDm = false;
      bool mSuiWaZKaW = false;
      bool RxWxPJdXMG = false;
      bool EbuNXVfuAw = false;
      bool wixNGmwMdY = false;
      bool lhhrnLUZZH = false;
      bool xMZxiLXgLA = false;
      bool ueJdZhAJqc = false;
      bool NQsnTVsCYL = false;
      bool BFVszjIzeu = false;
      bool OOAddHXERF = false;
      bool KLiwtfSldM = false;
      bool RVHzzpJQeo = false;
      bool ZBdwOzPPJM = false;
      bool xojTBpVYzS = false;
      string WRAYOTXlux;
      string JKSaJFlOVY;
      string ArQUftIYXp;
      string ycusyxMHAU;
      string tMFXAIuABA;
      string GRBZheAfsT;
      string LzOFyfOZcM;
      string seOAemlsUW;
      string zHWWifaULS;
      string wfOfJtyAYT;
      string sUXoHbDBtt;
      string sHLVTEbrVS;
      string EtNJPMPhqk;
      string okTAddjhOG;
      string cZZQZoUrLF;
      string SGdGOzHNZu;
      string LUJJFHmKro;
      string TscOodTwjZ;
      string qWWlSiGNke;
      string WWISuHPPLR;
      if(WRAYOTXlux == sUXoHbDBtt){BJAVkYcPQj = true;}
      else if(sUXoHbDBtt == WRAYOTXlux){lhhrnLUZZH = true;}
      if(JKSaJFlOVY == sHLVTEbrVS){eKczEnyXqV = true;}
      else if(sHLVTEbrVS == JKSaJFlOVY){xMZxiLXgLA = true;}
      if(ArQUftIYXp == EtNJPMPhqk){AZYMSxkJTg = true;}
      else if(EtNJPMPhqk == ArQUftIYXp){ueJdZhAJqc = true;}
      if(ycusyxMHAU == okTAddjhOG){NEjRYgWAAs = true;}
      else if(okTAddjhOG == ycusyxMHAU){NQsnTVsCYL = true;}
      if(tMFXAIuABA == cZZQZoUrLF){FqwAzMsJOG = true;}
      else if(cZZQZoUrLF == tMFXAIuABA){BFVszjIzeu = true;}
      if(GRBZheAfsT == SGdGOzHNZu){JrXoQbjmDm = true;}
      else if(SGdGOzHNZu == GRBZheAfsT){OOAddHXERF = true;}
      if(LzOFyfOZcM == LUJJFHmKro){mSuiWaZKaW = true;}
      else if(LUJJFHmKro == LzOFyfOZcM){KLiwtfSldM = true;}
      if(seOAemlsUW == TscOodTwjZ){RxWxPJdXMG = true;}
      if(zHWWifaULS == qWWlSiGNke){EbuNXVfuAw = true;}
      if(wfOfJtyAYT == WWISuHPPLR){wixNGmwMdY = true;}
      while(TscOodTwjZ == seOAemlsUW){RVHzzpJQeo = true;}
      while(qWWlSiGNke == qWWlSiGNke){ZBdwOzPPJM = true;}
      while(WWISuHPPLR == WWISuHPPLR){xojTBpVYzS = true;}
      if(BJAVkYcPQj == true){BJAVkYcPQj = false;}
      if(eKczEnyXqV == true){eKczEnyXqV = false;}
      if(AZYMSxkJTg == true){AZYMSxkJTg = false;}
      if(NEjRYgWAAs == true){NEjRYgWAAs = false;}
      if(FqwAzMsJOG == true){FqwAzMsJOG = false;}
      if(JrXoQbjmDm == true){JrXoQbjmDm = false;}
      if(mSuiWaZKaW == true){mSuiWaZKaW = false;}
      if(RxWxPJdXMG == true){RxWxPJdXMG = false;}
      if(EbuNXVfuAw == true){EbuNXVfuAw = false;}
      if(wixNGmwMdY == true){wixNGmwMdY = false;}
      if(lhhrnLUZZH == true){lhhrnLUZZH = false;}
      if(xMZxiLXgLA == true){xMZxiLXgLA = false;}
      if(ueJdZhAJqc == true){ueJdZhAJqc = false;}
      if(NQsnTVsCYL == true){NQsnTVsCYL = false;}
      if(BFVszjIzeu == true){BFVszjIzeu = false;}
      if(OOAddHXERF == true){OOAddHXERF = false;}
      if(KLiwtfSldM == true){KLiwtfSldM = false;}
      if(RVHzzpJQeo == true){RVHzzpJQeo = false;}
      if(ZBdwOzPPJM == true){ZBdwOzPPJM = false;}
      if(xojTBpVYzS == true){xojTBpVYzS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MIGFIVZMHJ
{ 
  void nrXjsMtSBd()
  { 
      bool SoCoNcpsDS = false;
      bool QrHXaIljUZ = false;
      bool IqRZclmOEJ = false;
      bool itWBJSpOIc = false;
      bool ppRcXRjQEb = false;
      bool cxEemaXbMa = false;
      bool pbnsiWUFNH = false;
      bool RXarjSYoCK = false;
      bool CVJcflprOh = false;
      bool uOBhlOBXsB = false;
      bool xdCxJFVLuT = false;
      bool CiYBXTRKNx = false;
      bool fcpfMCVsFU = false;
      bool QBuANYSMSa = false;
      bool PdwufMoAJS = false;
      bool wpKwUTnWjH = false;
      bool icFZDBmYnz = false;
      bool BFrlgCfuzA = false;
      bool NVimYZpzfs = false;
      bool kubLrlXVqe = false;
      string rmYWbUHUuf;
      string OHuQAHyWHI;
      string UGWOyWJwEY;
      string XEAViEDgxc;
      string eJfQxPiXBx;
      string cuyOjkPJYE;
      string LKPWHKHZhu;
      string ERYddLaGRi;
      string mktHwbGlkx;
      string ntHsQTsIIm;
      string HJoGsKVTkY;
      string JJqpQZPIZf;
      string DVokGKJfNJ;
      string RRxeadwnOk;
      string GmBMmeCRbq;
      string EkhcilUEzh;
      string ApFaGrLMPl;
      string datoYQUbxb;
      string HrDVFgiUuo;
      string JqnfjPgZFu;
      if(rmYWbUHUuf == HJoGsKVTkY){SoCoNcpsDS = true;}
      else if(HJoGsKVTkY == rmYWbUHUuf){xdCxJFVLuT = true;}
      if(OHuQAHyWHI == JJqpQZPIZf){QrHXaIljUZ = true;}
      else if(JJqpQZPIZf == OHuQAHyWHI){CiYBXTRKNx = true;}
      if(UGWOyWJwEY == DVokGKJfNJ){IqRZclmOEJ = true;}
      else if(DVokGKJfNJ == UGWOyWJwEY){fcpfMCVsFU = true;}
      if(XEAViEDgxc == RRxeadwnOk){itWBJSpOIc = true;}
      else if(RRxeadwnOk == XEAViEDgxc){QBuANYSMSa = true;}
      if(eJfQxPiXBx == GmBMmeCRbq){ppRcXRjQEb = true;}
      else if(GmBMmeCRbq == eJfQxPiXBx){PdwufMoAJS = true;}
      if(cuyOjkPJYE == EkhcilUEzh){cxEemaXbMa = true;}
      else if(EkhcilUEzh == cuyOjkPJYE){wpKwUTnWjH = true;}
      if(LKPWHKHZhu == ApFaGrLMPl){pbnsiWUFNH = true;}
      else if(ApFaGrLMPl == LKPWHKHZhu){icFZDBmYnz = true;}
      if(ERYddLaGRi == datoYQUbxb){RXarjSYoCK = true;}
      if(mktHwbGlkx == HrDVFgiUuo){CVJcflprOh = true;}
      if(ntHsQTsIIm == JqnfjPgZFu){uOBhlOBXsB = true;}
      while(datoYQUbxb == ERYddLaGRi){BFrlgCfuzA = true;}
      while(HrDVFgiUuo == HrDVFgiUuo){NVimYZpzfs = true;}
      while(JqnfjPgZFu == JqnfjPgZFu){kubLrlXVqe = true;}
      if(SoCoNcpsDS == true){SoCoNcpsDS = false;}
      if(QrHXaIljUZ == true){QrHXaIljUZ = false;}
      if(IqRZclmOEJ == true){IqRZclmOEJ = false;}
      if(itWBJSpOIc == true){itWBJSpOIc = false;}
      if(ppRcXRjQEb == true){ppRcXRjQEb = false;}
      if(cxEemaXbMa == true){cxEemaXbMa = false;}
      if(pbnsiWUFNH == true){pbnsiWUFNH = false;}
      if(RXarjSYoCK == true){RXarjSYoCK = false;}
      if(CVJcflprOh == true){CVJcflprOh = false;}
      if(uOBhlOBXsB == true){uOBhlOBXsB = false;}
      if(xdCxJFVLuT == true){xdCxJFVLuT = false;}
      if(CiYBXTRKNx == true){CiYBXTRKNx = false;}
      if(fcpfMCVsFU == true){fcpfMCVsFU = false;}
      if(QBuANYSMSa == true){QBuANYSMSa = false;}
      if(PdwufMoAJS == true){PdwufMoAJS = false;}
      if(wpKwUTnWjH == true){wpKwUTnWjH = false;}
      if(icFZDBmYnz == true){icFZDBmYnz = false;}
      if(BFrlgCfuzA == true){BFrlgCfuzA = false;}
      if(NVimYZpzfs == true){NVimYZpzfs = false;}
      if(kubLrlXVqe == true){kubLrlXVqe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXEKUUGSCZ
{ 
  void WdTpqSJuCn()
  { 
      bool WxqEZsDoAG = false;
      bool KdguAtnQuW = false;
      bool HhIYZabiwP = false;
      bool ZyzjMqcgbE = false;
      bool xSZOPKJhCV = false;
      bool xUdfunnSdy = false;
      bool RUrjfMdwiJ = false;
      bool QHnqYoItIP = false;
      bool RtgaSETTnX = false;
      bool DJCdmcaohC = false;
      bool fMyrEogmGG = false;
      bool fsJNgWnRQa = false;
      bool rKHLGGFJDw = false;
      bool NSLGiFwnVd = false;
      bool XgMhrJznwQ = false;
      bool nIXHJVEmly = false;
      bool jWiKrMgDeb = false;
      bool azwmDKyZSw = false;
      bool GQNmHEtEwN = false;
      bool BICXsAyCoe = false;
      string Otdxkgqfph;
      string WNmTbpBfun;
      string AoOnGRQaHs;
      string doMQSwhoWi;
      string cqnUQYidYL;
      string mmXCYZeopS;
      string PPXwEgAWAe;
      string HLIMKJAtWg;
      string hmBuFpQKqs;
      string QszESNSqQi;
      string YMcsDaeLqP;
      string YkRIkbNcpN;
      string QpeHOOMEsx;
      string qIcmIVKIqe;
      string LESbTeaqTq;
      string zoACShgUen;
      string OZSsYPIdzO;
      string QFkLCMWDni;
      string nUkCyBIZUa;
      string npcCPllYDD;
      if(Otdxkgqfph == YMcsDaeLqP){WxqEZsDoAG = true;}
      else if(YMcsDaeLqP == Otdxkgqfph){fMyrEogmGG = true;}
      if(WNmTbpBfun == YkRIkbNcpN){KdguAtnQuW = true;}
      else if(YkRIkbNcpN == WNmTbpBfun){fsJNgWnRQa = true;}
      if(AoOnGRQaHs == QpeHOOMEsx){HhIYZabiwP = true;}
      else if(QpeHOOMEsx == AoOnGRQaHs){rKHLGGFJDw = true;}
      if(doMQSwhoWi == qIcmIVKIqe){ZyzjMqcgbE = true;}
      else if(qIcmIVKIqe == doMQSwhoWi){NSLGiFwnVd = true;}
      if(cqnUQYidYL == LESbTeaqTq){xSZOPKJhCV = true;}
      else if(LESbTeaqTq == cqnUQYidYL){XgMhrJznwQ = true;}
      if(mmXCYZeopS == zoACShgUen){xUdfunnSdy = true;}
      else if(zoACShgUen == mmXCYZeopS){nIXHJVEmly = true;}
      if(PPXwEgAWAe == OZSsYPIdzO){RUrjfMdwiJ = true;}
      else if(OZSsYPIdzO == PPXwEgAWAe){jWiKrMgDeb = true;}
      if(HLIMKJAtWg == QFkLCMWDni){QHnqYoItIP = true;}
      if(hmBuFpQKqs == nUkCyBIZUa){RtgaSETTnX = true;}
      if(QszESNSqQi == npcCPllYDD){DJCdmcaohC = true;}
      while(QFkLCMWDni == HLIMKJAtWg){azwmDKyZSw = true;}
      while(nUkCyBIZUa == nUkCyBIZUa){GQNmHEtEwN = true;}
      while(npcCPllYDD == npcCPllYDD){BICXsAyCoe = true;}
      if(WxqEZsDoAG == true){WxqEZsDoAG = false;}
      if(KdguAtnQuW == true){KdguAtnQuW = false;}
      if(HhIYZabiwP == true){HhIYZabiwP = false;}
      if(ZyzjMqcgbE == true){ZyzjMqcgbE = false;}
      if(xSZOPKJhCV == true){xSZOPKJhCV = false;}
      if(xUdfunnSdy == true){xUdfunnSdy = false;}
      if(RUrjfMdwiJ == true){RUrjfMdwiJ = false;}
      if(QHnqYoItIP == true){QHnqYoItIP = false;}
      if(RtgaSETTnX == true){RtgaSETTnX = false;}
      if(DJCdmcaohC == true){DJCdmcaohC = false;}
      if(fMyrEogmGG == true){fMyrEogmGG = false;}
      if(fsJNgWnRQa == true){fsJNgWnRQa = false;}
      if(rKHLGGFJDw == true){rKHLGGFJDw = false;}
      if(NSLGiFwnVd == true){NSLGiFwnVd = false;}
      if(XgMhrJznwQ == true){XgMhrJznwQ = false;}
      if(nIXHJVEmly == true){nIXHJVEmly = false;}
      if(jWiKrMgDeb == true){jWiKrMgDeb = false;}
      if(azwmDKyZSw == true){azwmDKyZSw = false;}
      if(GQNmHEtEwN == true){GQNmHEtEwN = false;}
      if(BICXsAyCoe == true){BICXsAyCoe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EHBPUEPIIR
{ 
  void uEkAdWDQlO()
  { 
      bool ocNuEGzfdy = false;
      bool aTgexVBMqL = false;
      bool FKiBhxcABC = false;
      bool WUtCFMVTjL = false;
      bool aqWMuNmXaG = false;
      bool qDipFdsMMH = false;
      bool dzebaFZdZk = false;
      bool AhcekNnWGU = false;
      bool JEYtLTkDxa = false;
      bool SJHbgaMtkp = false;
      bool nJypGIaEEq = false;
      bool pWFryZZkQH = false;
      bool TVfySpaAxJ = false;
      bool BskQfzGimC = false;
      bool sgzGjuDPdH = false;
      bool BbddVSdzXP = false;
      bool hZGtoxloLy = false;
      bool TqxNNmWYNW = false;
      bool lKWpIZPGtN = false;
      bool VGKXTTaERm = false;
      string dVrnfGDijt;
      string kwkZHXitMC;
      string QIgMcPMxmK;
      string rDPYWauLrx;
      string BGzeXhOAAb;
      string ysaQxVnfKQ;
      string sFuZChfMDg;
      string bWCOBKICnu;
      string AMwKLzczbB;
      string lPBbDuKZbp;
      string CBwTzbpLOl;
      string MlrPPgIkOD;
      string EfkCtMVaKF;
      string ziZxryPcLi;
      string IQjonAXkLW;
      string mYLYlVQtZl;
      string GPBJldLtXQ;
      string RfYetmuwNt;
      string ojOnSaXBLV;
      string hUDYcrPaCK;
      if(dVrnfGDijt == CBwTzbpLOl){ocNuEGzfdy = true;}
      else if(CBwTzbpLOl == dVrnfGDijt){nJypGIaEEq = true;}
      if(kwkZHXitMC == MlrPPgIkOD){aTgexVBMqL = true;}
      else if(MlrPPgIkOD == kwkZHXitMC){pWFryZZkQH = true;}
      if(QIgMcPMxmK == EfkCtMVaKF){FKiBhxcABC = true;}
      else if(EfkCtMVaKF == QIgMcPMxmK){TVfySpaAxJ = true;}
      if(rDPYWauLrx == ziZxryPcLi){WUtCFMVTjL = true;}
      else if(ziZxryPcLi == rDPYWauLrx){BskQfzGimC = true;}
      if(BGzeXhOAAb == IQjonAXkLW){aqWMuNmXaG = true;}
      else if(IQjonAXkLW == BGzeXhOAAb){sgzGjuDPdH = true;}
      if(ysaQxVnfKQ == mYLYlVQtZl){qDipFdsMMH = true;}
      else if(mYLYlVQtZl == ysaQxVnfKQ){BbddVSdzXP = true;}
      if(sFuZChfMDg == GPBJldLtXQ){dzebaFZdZk = true;}
      else if(GPBJldLtXQ == sFuZChfMDg){hZGtoxloLy = true;}
      if(bWCOBKICnu == RfYetmuwNt){AhcekNnWGU = true;}
      if(AMwKLzczbB == ojOnSaXBLV){JEYtLTkDxa = true;}
      if(lPBbDuKZbp == hUDYcrPaCK){SJHbgaMtkp = true;}
      while(RfYetmuwNt == bWCOBKICnu){TqxNNmWYNW = true;}
      while(ojOnSaXBLV == ojOnSaXBLV){lKWpIZPGtN = true;}
      while(hUDYcrPaCK == hUDYcrPaCK){VGKXTTaERm = true;}
      if(ocNuEGzfdy == true){ocNuEGzfdy = false;}
      if(aTgexVBMqL == true){aTgexVBMqL = false;}
      if(FKiBhxcABC == true){FKiBhxcABC = false;}
      if(WUtCFMVTjL == true){WUtCFMVTjL = false;}
      if(aqWMuNmXaG == true){aqWMuNmXaG = false;}
      if(qDipFdsMMH == true){qDipFdsMMH = false;}
      if(dzebaFZdZk == true){dzebaFZdZk = false;}
      if(AhcekNnWGU == true){AhcekNnWGU = false;}
      if(JEYtLTkDxa == true){JEYtLTkDxa = false;}
      if(SJHbgaMtkp == true){SJHbgaMtkp = false;}
      if(nJypGIaEEq == true){nJypGIaEEq = false;}
      if(pWFryZZkQH == true){pWFryZZkQH = false;}
      if(TVfySpaAxJ == true){TVfySpaAxJ = false;}
      if(BskQfzGimC == true){BskQfzGimC = false;}
      if(sgzGjuDPdH == true){sgzGjuDPdH = false;}
      if(BbddVSdzXP == true){BbddVSdzXP = false;}
      if(hZGtoxloLy == true){hZGtoxloLy = false;}
      if(TqxNNmWYNW == true){TqxNNmWYNW = false;}
      if(lKWpIZPGtN == true){lKWpIZPGtN = false;}
      if(VGKXTTaERm == true){VGKXTTaERm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JGCNJTYDOS
{ 
  void KuXyKFRhdN()
  { 
      bool sgDXNSBtsV = false;
      bool PFKWYYZeop = false;
      bool EjsBRCjomI = false;
      bool BGVuZdjgVz = false;
      bool dRSlHkiIrm = false;
      bool fDNYFInBGK = false;
      bool hLHkTJjOxu = false;
      bool orIpLmRHsf = false;
      bool TawzcyrwpQ = false;
      bool phaKQSJhRy = false;
      bool BULxxmtWMS = false;
      bool qfIZqGOHHV = false;
      bool QmYgEGRxYs = false;
      bool djoueyPyBo = false;
      bool DViXZJZATJ = false;
      bool DCZugNwesq = false;
      bool VwxTnGpMur = false;
      bool qPFSSuDBGt = false;
      bool gQdPpaJtOQ = false;
      bool CkFKTHXPiS = false;
      string BVlWOGkwJg;
      string MbdTGENVst;
      string PKgYOaofEl;
      string eZrLnsLDLh;
      string ZInHYaeeLX;
      string lcTaQqnNHm;
      string QFqXBmjReM;
      string rKKKTGVYzm;
      string wKTgACFQux;
      string ExuXQTRQGl;
      string qNzyeaRIHJ;
      string VOOTqGkJXz;
      string gSWhItOltA;
      string nESMuhKVCY;
      string kxJkboiagJ;
      string hIsHFYqQpj;
      string MeOGVQwBXI;
      string wPHyNiIkGS;
      string LmFjReLLHW;
      string qsfRLFhCPK;
      if(BVlWOGkwJg == qNzyeaRIHJ){sgDXNSBtsV = true;}
      else if(qNzyeaRIHJ == BVlWOGkwJg){BULxxmtWMS = true;}
      if(MbdTGENVst == VOOTqGkJXz){PFKWYYZeop = true;}
      else if(VOOTqGkJXz == MbdTGENVst){qfIZqGOHHV = true;}
      if(PKgYOaofEl == gSWhItOltA){EjsBRCjomI = true;}
      else if(gSWhItOltA == PKgYOaofEl){QmYgEGRxYs = true;}
      if(eZrLnsLDLh == nESMuhKVCY){BGVuZdjgVz = true;}
      else if(nESMuhKVCY == eZrLnsLDLh){djoueyPyBo = true;}
      if(ZInHYaeeLX == kxJkboiagJ){dRSlHkiIrm = true;}
      else if(kxJkboiagJ == ZInHYaeeLX){DViXZJZATJ = true;}
      if(lcTaQqnNHm == hIsHFYqQpj){fDNYFInBGK = true;}
      else if(hIsHFYqQpj == lcTaQqnNHm){DCZugNwesq = true;}
      if(QFqXBmjReM == MeOGVQwBXI){hLHkTJjOxu = true;}
      else if(MeOGVQwBXI == QFqXBmjReM){VwxTnGpMur = true;}
      if(rKKKTGVYzm == wPHyNiIkGS){orIpLmRHsf = true;}
      if(wKTgACFQux == LmFjReLLHW){TawzcyrwpQ = true;}
      if(ExuXQTRQGl == qsfRLFhCPK){phaKQSJhRy = true;}
      while(wPHyNiIkGS == rKKKTGVYzm){qPFSSuDBGt = true;}
      while(LmFjReLLHW == LmFjReLLHW){gQdPpaJtOQ = true;}
      while(qsfRLFhCPK == qsfRLFhCPK){CkFKTHXPiS = true;}
      if(sgDXNSBtsV == true){sgDXNSBtsV = false;}
      if(PFKWYYZeop == true){PFKWYYZeop = false;}
      if(EjsBRCjomI == true){EjsBRCjomI = false;}
      if(BGVuZdjgVz == true){BGVuZdjgVz = false;}
      if(dRSlHkiIrm == true){dRSlHkiIrm = false;}
      if(fDNYFInBGK == true){fDNYFInBGK = false;}
      if(hLHkTJjOxu == true){hLHkTJjOxu = false;}
      if(orIpLmRHsf == true){orIpLmRHsf = false;}
      if(TawzcyrwpQ == true){TawzcyrwpQ = false;}
      if(phaKQSJhRy == true){phaKQSJhRy = false;}
      if(BULxxmtWMS == true){BULxxmtWMS = false;}
      if(qfIZqGOHHV == true){qfIZqGOHHV = false;}
      if(QmYgEGRxYs == true){QmYgEGRxYs = false;}
      if(djoueyPyBo == true){djoueyPyBo = false;}
      if(DViXZJZATJ == true){DViXZJZATJ = false;}
      if(DCZugNwesq == true){DCZugNwesq = false;}
      if(VwxTnGpMur == true){VwxTnGpMur = false;}
      if(qPFSSuDBGt == true){qPFSSuDBGt = false;}
      if(gQdPpaJtOQ == true){gQdPpaJtOQ = false;}
      if(CkFKTHXPiS == true){CkFKTHXPiS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EZVNZCSXPC
{ 
  void PBRbATAKBy()
  { 
      bool rSmSiwxwXF = false;
      bool NFRwGamNUx = false;
      bool uLwOOZocwo = false;
      bool EJLmHoEKJx = false;
      bool BpJOuzOiJe = false;
      bool PNHuXfWXDJ = false;
      bool HTzhAEsdnQ = false;
      bool WbEWwEChTP = false;
      bool KFSRZqBQOb = false;
      bool SfHzpgpaNp = false;
      bool FjtsHnIjzS = false;
      bool doEmyBBhII = false;
      bool CcPMxqTEgO = false;
      bool OaTcJZLYJk = false;
      bool hRQuxdaTAo = false;
      bool fIRFnbUguQ = false;
      bool TECjEDUbcY = false;
      bool pbXXZjMTPT = false;
      bool PADriGIOnh = false;
      bool EdcsRdPfqs = false;
      string waRVxuTDfg;
      string dJheKczSkx;
      string gOKpFrwKqI;
      string VsQOCtfGdB;
      string WbAljVWJzD;
      string NVXzohPaPF;
      string zIMXKjsSbQ;
      string wsojZEOYFj;
      string UmLmtAVQYU;
      string dEpXCOPbaA;
      string bEgiHUgnZk;
      string TqVfkMxYcK;
      string OcsHlrCQhK;
      string olxFIPFbfZ;
      string ShqnAliKmo;
      string QpzPlzKYwO;
      string SQGOugtPXU;
      string GUsDrfkEGA;
      string IqcrtylhTI;
      string FgfQGCbbsT;
      if(waRVxuTDfg == bEgiHUgnZk){rSmSiwxwXF = true;}
      else if(bEgiHUgnZk == waRVxuTDfg){FjtsHnIjzS = true;}
      if(dJheKczSkx == TqVfkMxYcK){NFRwGamNUx = true;}
      else if(TqVfkMxYcK == dJheKczSkx){doEmyBBhII = true;}
      if(gOKpFrwKqI == OcsHlrCQhK){uLwOOZocwo = true;}
      else if(OcsHlrCQhK == gOKpFrwKqI){CcPMxqTEgO = true;}
      if(VsQOCtfGdB == olxFIPFbfZ){EJLmHoEKJx = true;}
      else if(olxFIPFbfZ == VsQOCtfGdB){OaTcJZLYJk = true;}
      if(WbAljVWJzD == ShqnAliKmo){BpJOuzOiJe = true;}
      else if(ShqnAliKmo == WbAljVWJzD){hRQuxdaTAo = true;}
      if(NVXzohPaPF == QpzPlzKYwO){PNHuXfWXDJ = true;}
      else if(QpzPlzKYwO == NVXzohPaPF){fIRFnbUguQ = true;}
      if(zIMXKjsSbQ == SQGOugtPXU){HTzhAEsdnQ = true;}
      else if(SQGOugtPXU == zIMXKjsSbQ){TECjEDUbcY = true;}
      if(wsojZEOYFj == GUsDrfkEGA){WbEWwEChTP = true;}
      if(UmLmtAVQYU == IqcrtylhTI){KFSRZqBQOb = true;}
      if(dEpXCOPbaA == FgfQGCbbsT){SfHzpgpaNp = true;}
      while(GUsDrfkEGA == wsojZEOYFj){pbXXZjMTPT = true;}
      while(IqcrtylhTI == IqcrtylhTI){PADriGIOnh = true;}
      while(FgfQGCbbsT == FgfQGCbbsT){EdcsRdPfqs = true;}
      if(rSmSiwxwXF == true){rSmSiwxwXF = false;}
      if(NFRwGamNUx == true){NFRwGamNUx = false;}
      if(uLwOOZocwo == true){uLwOOZocwo = false;}
      if(EJLmHoEKJx == true){EJLmHoEKJx = false;}
      if(BpJOuzOiJe == true){BpJOuzOiJe = false;}
      if(PNHuXfWXDJ == true){PNHuXfWXDJ = false;}
      if(HTzhAEsdnQ == true){HTzhAEsdnQ = false;}
      if(WbEWwEChTP == true){WbEWwEChTP = false;}
      if(KFSRZqBQOb == true){KFSRZqBQOb = false;}
      if(SfHzpgpaNp == true){SfHzpgpaNp = false;}
      if(FjtsHnIjzS == true){FjtsHnIjzS = false;}
      if(doEmyBBhII == true){doEmyBBhII = false;}
      if(CcPMxqTEgO == true){CcPMxqTEgO = false;}
      if(OaTcJZLYJk == true){OaTcJZLYJk = false;}
      if(hRQuxdaTAo == true){hRQuxdaTAo = false;}
      if(fIRFnbUguQ == true){fIRFnbUguQ = false;}
      if(TECjEDUbcY == true){TECjEDUbcY = false;}
      if(pbXXZjMTPT == true){pbXXZjMTPT = false;}
      if(PADriGIOnh == true){PADriGIOnh = false;}
      if(EdcsRdPfqs == true){EdcsRdPfqs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SATGDNYMEF
{ 
  void OztcJGFktK()
  { 
      bool XdVxjXfIOG = false;
      bool duJPGqnmiE = false;
      bool XHeylfWLUy = false;
      bool SUcKCoDOxn = false;
      bool SbHixfpnJD = false;
      bool bOdUFQyXLE = false;
      bool BTnPmISyNR = false;
      bool nZpukwzwBG = false;
      bool ohCQWDpHFl = false;
      bool pfCrmznrwn = false;
      bool MqaqPCXijI = false;
      bool QCVEOTRWsi = false;
      bool RKsaaHWyIk = false;
      bool HGzMsyGKBT = false;
      bool fHXwUnJxdS = false;
      bool hRyMVCxzQH = false;
      bool fZayAJCJLP = false;
      bool MGUYDKmxFm = false;
      bool yYUoDpImqq = false;
      bool BGttnFgYuK = false;
      string HYLPtLZdot;
      string YPEEdKtKVn;
      string OijmICRocO;
      string cqFjbUIPoi;
      string GdaaBOyzbt;
      string QpCouYnXGq;
      string sjBaRgJTcI;
      string CdUlgjIJks;
      string ESNhylnQnC;
      string fjIypVbzIU;
      string FdWSqlVQHL;
      string QelNmaWTbe;
      string srfZbRUVwL;
      string HIAQnZwupM;
      string PXJclByuKO;
      string zIXdbMywpZ;
      string QzUuDIdUZN;
      string eacPOViCmZ;
      string SZLgMzjWoa;
      string azEQuQCNZc;
      if(HYLPtLZdot == FdWSqlVQHL){XdVxjXfIOG = true;}
      else if(FdWSqlVQHL == HYLPtLZdot){MqaqPCXijI = true;}
      if(YPEEdKtKVn == QelNmaWTbe){duJPGqnmiE = true;}
      else if(QelNmaWTbe == YPEEdKtKVn){QCVEOTRWsi = true;}
      if(OijmICRocO == srfZbRUVwL){XHeylfWLUy = true;}
      else if(srfZbRUVwL == OijmICRocO){RKsaaHWyIk = true;}
      if(cqFjbUIPoi == HIAQnZwupM){SUcKCoDOxn = true;}
      else if(HIAQnZwupM == cqFjbUIPoi){HGzMsyGKBT = true;}
      if(GdaaBOyzbt == PXJclByuKO){SbHixfpnJD = true;}
      else if(PXJclByuKO == GdaaBOyzbt){fHXwUnJxdS = true;}
      if(QpCouYnXGq == zIXdbMywpZ){bOdUFQyXLE = true;}
      else if(zIXdbMywpZ == QpCouYnXGq){hRyMVCxzQH = true;}
      if(sjBaRgJTcI == QzUuDIdUZN){BTnPmISyNR = true;}
      else if(QzUuDIdUZN == sjBaRgJTcI){fZayAJCJLP = true;}
      if(CdUlgjIJks == eacPOViCmZ){nZpukwzwBG = true;}
      if(ESNhylnQnC == SZLgMzjWoa){ohCQWDpHFl = true;}
      if(fjIypVbzIU == azEQuQCNZc){pfCrmznrwn = true;}
      while(eacPOViCmZ == CdUlgjIJks){MGUYDKmxFm = true;}
      while(SZLgMzjWoa == SZLgMzjWoa){yYUoDpImqq = true;}
      while(azEQuQCNZc == azEQuQCNZc){BGttnFgYuK = true;}
      if(XdVxjXfIOG == true){XdVxjXfIOG = false;}
      if(duJPGqnmiE == true){duJPGqnmiE = false;}
      if(XHeylfWLUy == true){XHeylfWLUy = false;}
      if(SUcKCoDOxn == true){SUcKCoDOxn = false;}
      if(SbHixfpnJD == true){SbHixfpnJD = false;}
      if(bOdUFQyXLE == true){bOdUFQyXLE = false;}
      if(BTnPmISyNR == true){BTnPmISyNR = false;}
      if(nZpukwzwBG == true){nZpukwzwBG = false;}
      if(ohCQWDpHFl == true){ohCQWDpHFl = false;}
      if(pfCrmznrwn == true){pfCrmznrwn = false;}
      if(MqaqPCXijI == true){MqaqPCXijI = false;}
      if(QCVEOTRWsi == true){QCVEOTRWsi = false;}
      if(RKsaaHWyIk == true){RKsaaHWyIk = false;}
      if(HGzMsyGKBT == true){HGzMsyGKBT = false;}
      if(fHXwUnJxdS == true){fHXwUnJxdS = false;}
      if(hRyMVCxzQH == true){hRyMVCxzQH = false;}
      if(fZayAJCJLP == true){fZayAJCJLP = false;}
      if(MGUYDKmxFm == true){MGUYDKmxFm = false;}
      if(yYUoDpImqq == true){yYUoDpImqq = false;}
      if(BGttnFgYuK == true){BGttnFgYuK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XCAWJODPQV
{ 
  void SVedeMPSZe()
  { 
      bool HnhlTUyeFi = false;
      bool wAWWryYjsD = false;
      bool ffCzoPNqjA = false;
      bool cSoSkfXfdh = false;
      bool AmJjyrSRxT = false;
      bool oSiQJbkiwE = false;
      bool HGuFGdLDkL = false;
      bool ZsGKDrVRAx = false;
      bool xwtQKJiYJJ = false;
      bool toiYasrEdU = false;
      bool gPfktwMXNQ = false;
      bool FThzHLMdtx = false;
      bool tlsbRjJgjJ = false;
      bool AQnfPhPIWN = false;
      bool xKLsDaGiRP = false;
      bool fOKfZtVDTJ = false;
      bool menDQneCiZ = false;
      bool uEHfziazYp = false;
      bool dZPUdlGHGV = false;
      bool LLnNaRWHcP = false;
      string FqeKrecAbb;
      string TsLfcdijkE;
      string lyfIeNJHYq;
      string RLaetulpmS;
      string zqqCpeVMrh;
      string gdWdbGKWfd;
      string UUajKHSgkg;
      string rrxSFuHcRz;
      string rwOqKnoxCn;
      string kOJIxdPGrh;
      string MnbLongDXg;
      string zgFglYGiYW;
      string RUexwcinVa;
      string eAkimDTDBW;
      string HkYVnDJbVX;
      string XfhUPrJeOL;
      string ErhwBywVti;
      string ECgCPguIIr;
      string TGSxDySPTu;
      string sonpRODcTo;
      if(FqeKrecAbb == MnbLongDXg){HnhlTUyeFi = true;}
      else if(MnbLongDXg == FqeKrecAbb){gPfktwMXNQ = true;}
      if(TsLfcdijkE == zgFglYGiYW){wAWWryYjsD = true;}
      else if(zgFglYGiYW == TsLfcdijkE){FThzHLMdtx = true;}
      if(lyfIeNJHYq == RUexwcinVa){ffCzoPNqjA = true;}
      else if(RUexwcinVa == lyfIeNJHYq){tlsbRjJgjJ = true;}
      if(RLaetulpmS == eAkimDTDBW){cSoSkfXfdh = true;}
      else if(eAkimDTDBW == RLaetulpmS){AQnfPhPIWN = true;}
      if(zqqCpeVMrh == HkYVnDJbVX){AmJjyrSRxT = true;}
      else if(HkYVnDJbVX == zqqCpeVMrh){xKLsDaGiRP = true;}
      if(gdWdbGKWfd == XfhUPrJeOL){oSiQJbkiwE = true;}
      else if(XfhUPrJeOL == gdWdbGKWfd){fOKfZtVDTJ = true;}
      if(UUajKHSgkg == ErhwBywVti){HGuFGdLDkL = true;}
      else if(ErhwBywVti == UUajKHSgkg){menDQneCiZ = true;}
      if(rrxSFuHcRz == ECgCPguIIr){ZsGKDrVRAx = true;}
      if(rwOqKnoxCn == TGSxDySPTu){xwtQKJiYJJ = true;}
      if(kOJIxdPGrh == sonpRODcTo){toiYasrEdU = true;}
      while(ECgCPguIIr == rrxSFuHcRz){uEHfziazYp = true;}
      while(TGSxDySPTu == TGSxDySPTu){dZPUdlGHGV = true;}
      while(sonpRODcTo == sonpRODcTo){LLnNaRWHcP = true;}
      if(HnhlTUyeFi == true){HnhlTUyeFi = false;}
      if(wAWWryYjsD == true){wAWWryYjsD = false;}
      if(ffCzoPNqjA == true){ffCzoPNqjA = false;}
      if(cSoSkfXfdh == true){cSoSkfXfdh = false;}
      if(AmJjyrSRxT == true){AmJjyrSRxT = false;}
      if(oSiQJbkiwE == true){oSiQJbkiwE = false;}
      if(HGuFGdLDkL == true){HGuFGdLDkL = false;}
      if(ZsGKDrVRAx == true){ZsGKDrVRAx = false;}
      if(xwtQKJiYJJ == true){xwtQKJiYJJ = false;}
      if(toiYasrEdU == true){toiYasrEdU = false;}
      if(gPfktwMXNQ == true){gPfktwMXNQ = false;}
      if(FThzHLMdtx == true){FThzHLMdtx = false;}
      if(tlsbRjJgjJ == true){tlsbRjJgjJ = false;}
      if(AQnfPhPIWN == true){AQnfPhPIWN = false;}
      if(xKLsDaGiRP == true){xKLsDaGiRP = false;}
      if(fOKfZtVDTJ == true){fOKfZtVDTJ = false;}
      if(menDQneCiZ == true){menDQneCiZ = false;}
      if(uEHfziazYp == true){uEHfziazYp = false;}
      if(dZPUdlGHGV == true){dZPUdlGHGV = false;}
      if(LLnNaRWHcP == true){LLnNaRWHcP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QMMCWABOZH
{ 
  void VxHekILEEk()
  { 
      bool eDoTMqcWqm = false;
      bool gwSYsCYByQ = false;
      bool nEYdywxVdw = false;
      bool JrLxxRxeun = false;
      bool mmElRFbwom = false;
      bool sjrXBaeKVP = false;
      bool sGrtdojVaa = false;
      bool EtGKdAzmMr = false;
      bool UBgqCZznuW = false;
      bool llIetfuJIb = false;
      bool UFUNhzchtB = false;
      bool bryctqYAqD = false;
      bool pwaEnRkaPy = false;
      bool FodjWPgSJD = false;
      bool wRssutnejD = false;
      bool GtSFlYdQYP = false;
      bool OCRwwlNOGe = false;
      bool KGqnGXCgIt = false;
      bool dFpMqKWYxy = false;
      bool kPtsntzxxI = false;
      string xXDXlJysSz;
      string GkgrjiIekI;
      string BHJOtPgcHq;
      string MytJcuzoqZ;
      string UURxgKsxxW;
      string PegGJoOocW;
      string bUlalHqXPn;
      string iSnKnfpMhi;
      string VifjbgRmzm;
      string gKMUxzipKY;
      string TVhJmwqWSd;
      string zBHsAsoBzE;
      string pDXbHYGTMo;
      string xABIPABWxe;
      string puUVneCSTE;
      string JgpFiPyGBO;
      string pXJdgyAydA;
      string qSETOuiBmc;
      string VmzIePKwZz;
      string CtUhoRkqop;
      if(xXDXlJysSz == TVhJmwqWSd){eDoTMqcWqm = true;}
      else if(TVhJmwqWSd == xXDXlJysSz){UFUNhzchtB = true;}
      if(GkgrjiIekI == zBHsAsoBzE){gwSYsCYByQ = true;}
      else if(zBHsAsoBzE == GkgrjiIekI){bryctqYAqD = true;}
      if(BHJOtPgcHq == pDXbHYGTMo){nEYdywxVdw = true;}
      else if(pDXbHYGTMo == BHJOtPgcHq){pwaEnRkaPy = true;}
      if(MytJcuzoqZ == xABIPABWxe){JrLxxRxeun = true;}
      else if(xABIPABWxe == MytJcuzoqZ){FodjWPgSJD = true;}
      if(UURxgKsxxW == puUVneCSTE){mmElRFbwom = true;}
      else if(puUVneCSTE == UURxgKsxxW){wRssutnejD = true;}
      if(PegGJoOocW == JgpFiPyGBO){sjrXBaeKVP = true;}
      else if(JgpFiPyGBO == PegGJoOocW){GtSFlYdQYP = true;}
      if(bUlalHqXPn == pXJdgyAydA){sGrtdojVaa = true;}
      else if(pXJdgyAydA == bUlalHqXPn){OCRwwlNOGe = true;}
      if(iSnKnfpMhi == qSETOuiBmc){EtGKdAzmMr = true;}
      if(VifjbgRmzm == VmzIePKwZz){UBgqCZznuW = true;}
      if(gKMUxzipKY == CtUhoRkqop){llIetfuJIb = true;}
      while(qSETOuiBmc == iSnKnfpMhi){KGqnGXCgIt = true;}
      while(VmzIePKwZz == VmzIePKwZz){dFpMqKWYxy = true;}
      while(CtUhoRkqop == CtUhoRkqop){kPtsntzxxI = true;}
      if(eDoTMqcWqm == true){eDoTMqcWqm = false;}
      if(gwSYsCYByQ == true){gwSYsCYByQ = false;}
      if(nEYdywxVdw == true){nEYdywxVdw = false;}
      if(JrLxxRxeun == true){JrLxxRxeun = false;}
      if(mmElRFbwom == true){mmElRFbwom = false;}
      if(sjrXBaeKVP == true){sjrXBaeKVP = false;}
      if(sGrtdojVaa == true){sGrtdojVaa = false;}
      if(EtGKdAzmMr == true){EtGKdAzmMr = false;}
      if(UBgqCZznuW == true){UBgqCZznuW = false;}
      if(llIetfuJIb == true){llIetfuJIb = false;}
      if(UFUNhzchtB == true){UFUNhzchtB = false;}
      if(bryctqYAqD == true){bryctqYAqD = false;}
      if(pwaEnRkaPy == true){pwaEnRkaPy = false;}
      if(FodjWPgSJD == true){FodjWPgSJD = false;}
      if(wRssutnejD == true){wRssutnejD = false;}
      if(GtSFlYdQYP == true){GtSFlYdQYP = false;}
      if(OCRwwlNOGe == true){OCRwwlNOGe = false;}
      if(KGqnGXCgIt == true){KGqnGXCgIt = false;}
      if(dFpMqKWYxy == true){dFpMqKWYxy = false;}
      if(kPtsntzxxI == true){kPtsntzxxI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TKMVHGBZZT
{ 
  void jSIMdLUFbR()
  { 
      bool wzTCjmCCqq = false;
      bool mEYVrlpdbr = false;
      bool YsVFOTLyuc = false;
      bool xBnYmgPUsk = false;
      bool BNBRaKQQIY = false;
      bool QDgVUCcOnP = false;
      bool aEHOskQziL = false;
      bool WVjqpLqEdE = false;
      bool DupVLtUSDj = false;
      bool DBfcJxFmXo = false;
      bool sQgwCtSofJ = false;
      bool KYjiMeOkCz = false;
      bool QywyHUpHgs = false;
      bool FEfnKmOsSQ = false;
      bool aemtYeQwQe = false;
      bool hUjXYuUhoh = false;
      bool ELIlDGrwYZ = false;
      bool QVRkXlLBZb = false;
      bool DspCKkTIPP = false;
      bool RfDkMPWAqS = false;
      string hrLHcwuiwj;
      string eEZmIOkIIQ;
      string uugkqkbqxZ;
      string pxPzlBOmXD;
      string fNVcUJtxdk;
      string tCgukmLaPq;
      string TDlVtgoaBH;
      string AxkEkhYEQh;
      string pdNLfmPTNy;
      string pnWgibbzim;
      string TTwVkxRbJD;
      string OHJhAppZpG;
      string RUMDRLZDVJ;
      string GYUdNWhqai;
      string VmJKjheogr;
      string kBJbUyHrEZ;
      string WNGAwoleUd;
      string IyzGkdLCTi;
      string gjWcXEPsIO;
      string OolALHgJNt;
      if(hrLHcwuiwj == TTwVkxRbJD){wzTCjmCCqq = true;}
      else if(TTwVkxRbJD == hrLHcwuiwj){sQgwCtSofJ = true;}
      if(eEZmIOkIIQ == OHJhAppZpG){mEYVrlpdbr = true;}
      else if(OHJhAppZpG == eEZmIOkIIQ){KYjiMeOkCz = true;}
      if(uugkqkbqxZ == RUMDRLZDVJ){YsVFOTLyuc = true;}
      else if(RUMDRLZDVJ == uugkqkbqxZ){QywyHUpHgs = true;}
      if(pxPzlBOmXD == GYUdNWhqai){xBnYmgPUsk = true;}
      else if(GYUdNWhqai == pxPzlBOmXD){FEfnKmOsSQ = true;}
      if(fNVcUJtxdk == VmJKjheogr){BNBRaKQQIY = true;}
      else if(VmJKjheogr == fNVcUJtxdk){aemtYeQwQe = true;}
      if(tCgukmLaPq == kBJbUyHrEZ){QDgVUCcOnP = true;}
      else if(kBJbUyHrEZ == tCgukmLaPq){hUjXYuUhoh = true;}
      if(TDlVtgoaBH == WNGAwoleUd){aEHOskQziL = true;}
      else if(WNGAwoleUd == TDlVtgoaBH){ELIlDGrwYZ = true;}
      if(AxkEkhYEQh == IyzGkdLCTi){WVjqpLqEdE = true;}
      if(pdNLfmPTNy == gjWcXEPsIO){DupVLtUSDj = true;}
      if(pnWgibbzim == OolALHgJNt){DBfcJxFmXo = true;}
      while(IyzGkdLCTi == AxkEkhYEQh){QVRkXlLBZb = true;}
      while(gjWcXEPsIO == gjWcXEPsIO){DspCKkTIPP = true;}
      while(OolALHgJNt == OolALHgJNt){RfDkMPWAqS = true;}
      if(wzTCjmCCqq == true){wzTCjmCCqq = false;}
      if(mEYVrlpdbr == true){mEYVrlpdbr = false;}
      if(YsVFOTLyuc == true){YsVFOTLyuc = false;}
      if(xBnYmgPUsk == true){xBnYmgPUsk = false;}
      if(BNBRaKQQIY == true){BNBRaKQQIY = false;}
      if(QDgVUCcOnP == true){QDgVUCcOnP = false;}
      if(aEHOskQziL == true){aEHOskQziL = false;}
      if(WVjqpLqEdE == true){WVjqpLqEdE = false;}
      if(DupVLtUSDj == true){DupVLtUSDj = false;}
      if(DBfcJxFmXo == true){DBfcJxFmXo = false;}
      if(sQgwCtSofJ == true){sQgwCtSofJ = false;}
      if(KYjiMeOkCz == true){KYjiMeOkCz = false;}
      if(QywyHUpHgs == true){QywyHUpHgs = false;}
      if(FEfnKmOsSQ == true){FEfnKmOsSQ = false;}
      if(aemtYeQwQe == true){aemtYeQwQe = false;}
      if(hUjXYuUhoh == true){hUjXYuUhoh = false;}
      if(ELIlDGrwYZ == true){ELIlDGrwYZ = false;}
      if(QVRkXlLBZb == true){QVRkXlLBZb = false;}
      if(DspCKkTIPP == true){DspCKkTIPP = false;}
      if(RfDkMPWAqS == true){RfDkMPWAqS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SMDHATLGUS
{ 
  void zAIUWhhKUz()
  { 
      bool QXFrTHtqlY = false;
      bool IaAhnzLbPo = false;
      bool PGREbXauQW = false;
      bool rWZobkqSoC = false;
      bool TdXRQYrysi = false;
      bool SYmRqJFAPu = false;
      bool gzaPgkAKFC = false;
      bool HslNUkiAmC = false;
      bool fcCgDSiIyR = false;
      bool epCtVUDHjf = false;
      bool XgrpaYlZwF = false;
      bool aFMMODwsLN = false;
      bool BrMmXQpqqA = false;
      bool hbQHezkMFe = false;
      bool gILrqZcoeS = false;
      bool XKuVdfUESK = false;
      bool htiwWyoFhP = false;
      bool RjmggsfTwx = false;
      bool mAMXbXgtdy = false;
      bool efsuwlZOUs = false;
      string PoPPBZONgx;
      string ZXxBaIUlEI;
      string LkktbFtort;
      string pelDUBUNBV;
      string EyFwpbuSdb;
      string kmOFDdDVnw;
      string fZVlGtlsgZ;
      string nHkiENfnDz;
      string KaKQIDQfAq;
      string xyYFodbTpu;
      string pBlDmdCeBo;
      string yORnkFOFcC;
      string dFrobphesZ;
      string kLxIJInHcd;
      string BkeKshgjTj;
      string PWpnRjIwaw;
      string wWkaDlQIeb;
      string QHbyBragws;
      string IxKJKOVJqZ;
      string ArfgheADHH;
      if(PoPPBZONgx == pBlDmdCeBo){QXFrTHtqlY = true;}
      else if(pBlDmdCeBo == PoPPBZONgx){XgrpaYlZwF = true;}
      if(ZXxBaIUlEI == yORnkFOFcC){IaAhnzLbPo = true;}
      else if(yORnkFOFcC == ZXxBaIUlEI){aFMMODwsLN = true;}
      if(LkktbFtort == dFrobphesZ){PGREbXauQW = true;}
      else if(dFrobphesZ == LkktbFtort){BrMmXQpqqA = true;}
      if(pelDUBUNBV == kLxIJInHcd){rWZobkqSoC = true;}
      else if(kLxIJInHcd == pelDUBUNBV){hbQHezkMFe = true;}
      if(EyFwpbuSdb == BkeKshgjTj){TdXRQYrysi = true;}
      else if(BkeKshgjTj == EyFwpbuSdb){gILrqZcoeS = true;}
      if(kmOFDdDVnw == PWpnRjIwaw){SYmRqJFAPu = true;}
      else if(PWpnRjIwaw == kmOFDdDVnw){XKuVdfUESK = true;}
      if(fZVlGtlsgZ == wWkaDlQIeb){gzaPgkAKFC = true;}
      else if(wWkaDlQIeb == fZVlGtlsgZ){htiwWyoFhP = true;}
      if(nHkiENfnDz == QHbyBragws){HslNUkiAmC = true;}
      if(KaKQIDQfAq == IxKJKOVJqZ){fcCgDSiIyR = true;}
      if(xyYFodbTpu == ArfgheADHH){epCtVUDHjf = true;}
      while(QHbyBragws == nHkiENfnDz){RjmggsfTwx = true;}
      while(IxKJKOVJqZ == IxKJKOVJqZ){mAMXbXgtdy = true;}
      while(ArfgheADHH == ArfgheADHH){efsuwlZOUs = true;}
      if(QXFrTHtqlY == true){QXFrTHtqlY = false;}
      if(IaAhnzLbPo == true){IaAhnzLbPo = false;}
      if(PGREbXauQW == true){PGREbXauQW = false;}
      if(rWZobkqSoC == true){rWZobkqSoC = false;}
      if(TdXRQYrysi == true){TdXRQYrysi = false;}
      if(SYmRqJFAPu == true){SYmRqJFAPu = false;}
      if(gzaPgkAKFC == true){gzaPgkAKFC = false;}
      if(HslNUkiAmC == true){HslNUkiAmC = false;}
      if(fcCgDSiIyR == true){fcCgDSiIyR = false;}
      if(epCtVUDHjf == true){epCtVUDHjf = false;}
      if(XgrpaYlZwF == true){XgrpaYlZwF = false;}
      if(aFMMODwsLN == true){aFMMODwsLN = false;}
      if(BrMmXQpqqA == true){BrMmXQpqqA = false;}
      if(hbQHezkMFe == true){hbQHezkMFe = false;}
      if(gILrqZcoeS == true){gILrqZcoeS = false;}
      if(XKuVdfUESK == true){XKuVdfUESK = false;}
      if(htiwWyoFhP == true){htiwWyoFhP = false;}
      if(RjmggsfTwx == true){RjmggsfTwx = false;}
      if(mAMXbXgtdy == true){mAMXbXgtdy = false;}
      if(efsuwlZOUs == true){efsuwlZOUs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWZGSBAUON
{ 
  void ZUBJrKpjrT()
  { 
      bool RZMRGewCon = false;
      bool GuJELuZAcG = false;
      bool eFtnpZnkNh = false;
      bool mCibtKWsoT = false;
      bool phhITMxWPS = false;
      bool AzzqbMeXaf = false;
      bool qLoHBDMhJA = false;
      bool XfKIPxXlTc = false;
      bool bRUtgmDqzh = false;
      bool ezRIcdraGQ = false;
      bool APMOuToqbe = false;
      bool orEyEYquZO = false;
      bool AUhbVYOBek = false;
      bool EweDcLFGyN = false;
      bool yMPUsltTED = false;
      bool mxArPehjsW = false;
      bool FmLparNBUr = false;
      bool TjwLPnEMii = false;
      bool dtxaxGwmmy = false;
      bool dUNbIKAZtB = false;
      string MNwVSmLDpu;
      string UERCSOXyGY;
      string fSizNuFlBl;
      string HLtKtUeKXC;
      string bsEBSfIGVg;
      string CljTcsdxIW;
      string gYCEmJKGHx;
      string iMaExmOhgh;
      string mzQTiVaahB;
      string phCAUDqzOI;
      string UBzXxoLeVp;
      string ewPajhIhUR;
      string hiYFGBKait;
      string wOTXMkArWs;
      string JuErWtRaPm;
      string tIdwakcsQu;
      string ejwbtPcrOy;
      string gPLbHlegiM;
      string jjKwzmjWxa;
      string IHaaOZzbxH;
      if(MNwVSmLDpu == UBzXxoLeVp){RZMRGewCon = true;}
      else if(UBzXxoLeVp == MNwVSmLDpu){APMOuToqbe = true;}
      if(UERCSOXyGY == ewPajhIhUR){GuJELuZAcG = true;}
      else if(ewPajhIhUR == UERCSOXyGY){orEyEYquZO = true;}
      if(fSizNuFlBl == hiYFGBKait){eFtnpZnkNh = true;}
      else if(hiYFGBKait == fSizNuFlBl){AUhbVYOBek = true;}
      if(HLtKtUeKXC == wOTXMkArWs){mCibtKWsoT = true;}
      else if(wOTXMkArWs == HLtKtUeKXC){EweDcLFGyN = true;}
      if(bsEBSfIGVg == JuErWtRaPm){phhITMxWPS = true;}
      else if(JuErWtRaPm == bsEBSfIGVg){yMPUsltTED = true;}
      if(CljTcsdxIW == tIdwakcsQu){AzzqbMeXaf = true;}
      else if(tIdwakcsQu == CljTcsdxIW){mxArPehjsW = true;}
      if(gYCEmJKGHx == ejwbtPcrOy){qLoHBDMhJA = true;}
      else if(ejwbtPcrOy == gYCEmJKGHx){FmLparNBUr = true;}
      if(iMaExmOhgh == gPLbHlegiM){XfKIPxXlTc = true;}
      if(mzQTiVaahB == jjKwzmjWxa){bRUtgmDqzh = true;}
      if(phCAUDqzOI == IHaaOZzbxH){ezRIcdraGQ = true;}
      while(gPLbHlegiM == iMaExmOhgh){TjwLPnEMii = true;}
      while(jjKwzmjWxa == jjKwzmjWxa){dtxaxGwmmy = true;}
      while(IHaaOZzbxH == IHaaOZzbxH){dUNbIKAZtB = true;}
      if(RZMRGewCon == true){RZMRGewCon = false;}
      if(GuJELuZAcG == true){GuJELuZAcG = false;}
      if(eFtnpZnkNh == true){eFtnpZnkNh = false;}
      if(mCibtKWsoT == true){mCibtKWsoT = false;}
      if(phhITMxWPS == true){phhITMxWPS = false;}
      if(AzzqbMeXaf == true){AzzqbMeXaf = false;}
      if(qLoHBDMhJA == true){qLoHBDMhJA = false;}
      if(XfKIPxXlTc == true){XfKIPxXlTc = false;}
      if(bRUtgmDqzh == true){bRUtgmDqzh = false;}
      if(ezRIcdraGQ == true){ezRIcdraGQ = false;}
      if(APMOuToqbe == true){APMOuToqbe = false;}
      if(orEyEYquZO == true){orEyEYquZO = false;}
      if(AUhbVYOBek == true){AUhbVYOBek = false;}
      if(EweDcLFGyN == true){EweDcLFGyN = false;}
      if(yMPUsltTED == true){yMPUsltTED = false;}
      if(mxArPehjsW == true){mxArPehjsW = false;}
      if(FmLparNBUr == true){FmLparNBUr = false;}
      if(TjwLPnEMii == true){TjwLPnEMii = false;}
      if(dtxaxGwmmy == true){dtxaxGwmmy = false;}
      if(dUNbIKAZtB == true){dUNbIKAZtB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XYJIIQUZKQ
{ 
  void cnZHilTaRL()
  { 
      bool ukRtnyafmG = false;
      bool VcwjFDYeiu = false;
      bool IwghiVnHuB = false;
      bool MPqzOTkaVJ = false;
      bool AaCNWEozFJ = false;
      bool LbYWjzDjKS = false;
      bool KSjksFkxVk = false;
      bool SxJZuhsTKe = false;
      bool fnClokqUOO = false;
      bool PBQCzgpQTR = false;
      bool SrdTpNRybC = false;
      bool FjYemVQywI = false;
      bool NQhGVRgGaN = false;
      bool qbAsMnJhua = false;
      bool SrrMJebkPc = false;
      bool QrUKDBJXyY = false;
      bool gKXOKdjeSz = false;
      bool LiCVpVXVxp = false;
      bool ouqxxzHopK = false;
      bool dljWsHTdBe = false;
      string ykSYbbxzNq;
      string qoPNTgPaSy;
      string wZbnKebdpR;
      string PewgrrKRtf;
      string sqMTDIVKNV;
      string yHjayYJeNw;
      string ATIwaLriUa;
      string VxfmEEMHkC;
      string IQQUTIuViT;
      string ifDyfZiQrq;
      string QmplzAbxVs;
      string LBtLmiCnbS;
      string QWzArptgHe;
      string VuPslVadUT;
      string fxzoIhkqLw;
      string WtoZZsmotJ;
      string GtpqWPlAZR;
      string HXSIlTXKrJ;
      string ECVKHbGoTr;
      string hljKMkHHSs;
      if(ykSYbbxzNq == QmplzAbxVs){ukRtnyafmG = true;}
      else if(QmplzAbxVs == ykSYbbxzNq){SrdTpNRybC = true;}
      if(qoPNTgPaSy == LBtLmiCnbS){VcwjFDYeiu = true;}
      else if(LBtLmiCnbS == qoPNTgPaSy){FjYemVQywI = true;}
      if(wZbnKebdpR == QWzArptgHe){IwghiVnHuB = true;}
      else if(QWzArptgHe == wZbnKebdpR){NQhGVRgGaN = true;}
      if(PewgrrKRtf == VuPslVadUT){MPqzOTkaVJ = true;}
      else if(VuPslVadUT == PewgrrKRtf){qbAsMnJhua = true;}
      if(sqMTDIVKNV == fxzoIhkqLw){AaCNWEozFJ = true;}
      else if(fxzoIhkqLw == sqMTDIVKNV){SrrMJebkPc = true;}
      if(yHjayYJeNw == WtoZZsmotJ){LbYWjzDjKS = true;}
      else if(WtoZZsmotJ == yHjayYJeNw){QrUKDBJXyY = true;}
      if(ATIwaLriUa == GtpqWPlAZR){KSjksFkxVk = true;}
      else if(GtpqWPlAZR == ATIwaLriUa){gKXOKdjeSz = true;}
      if(VxfmEEMHkC == HXSIlTXKrJ){SxJZuhsTKe = true;}
      if(IQQUTIuViT == ECVKHbGoTr){fnClokqUOO = true;}
      if(ifDyfZiQrq == hljKMkHHSs){PBQCzgpQTR = true;}
      while(HXSIlTXKrJ == VxfmEEMHkC){LiCVpVXVxp = true;}
      while(ECVKHbGoTr == ECVKHbGoTr){ouqxxzHopK = true;}
      while(hljKMkHHSs == hljKMkHHSs){dljWsHTdBe = true;}
      if(ukRtnyafmG == true){ukRtnyafmG = false;}
      if(VcwjFDYeiu == true){VcwjFDYeiu = false;}
      if(IwghiVnHuB == true){IwghiVnHuB = false;}
      if(MPqzOTkaVJ == true){MPqzOTkaVJ = false;}
      if(AaCNWEozFJ == true){AaCNWEozFJ = false;}
      if(LbYWjzDjKS == true){LbYWjzDjKS = false;}
      if(KSjksFkxVk == true){KSjksFkxVk = false;}
      if(SxJZuhsTKe == true){SxJZuhsTKe = false;}
      if(fnClokqUOO == true){fnClokqUOO = false;}
      if(PBQCzgpQTR == true){PBQCzgpQTR = false;}
      if(SrdTpNRybC == true){SrdTpNRybC = false;}
      if(FjYemVQywI == true){FjYemVQywI = false;}
      if(NQhGVRgGaN == true){NQhGVRgGaN = false;}
      if(qbAsMnJhua == true){qbAsMnJhua = false;}
      if(SrrMJebkPc == true){SrrMJebkPc = false;}
      if(QrUKDBJXyY == true){QrUKDBJXyY = false;}
      if(gKXOKdjeSz == true){gKXOKdjeSz = false;}
      if(LiCVpVXVxp == true){LiCVpVXVxp = false;}
      if(ouqxxzHopK == true){ouqxxzHopK = false;}
      if(dljWsHTdBe == true){dljWsHTdBe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QMPRWEGNUO
{ 
  void ePAyNnktFX()
  { 
      bool VVdHVRCxic = false;
      bool CXLyRYMTDs = false;
      bool cXIqbEjClb = false;
      bool yZNItVFPio = false;
      bool enJOeJFCfs = false;
      bool jEPnYxNmeQ = false;
      bool gAKGebJDDw = false;
      bool TwjOOoOtLS = false;
      bool zhVsqtKZjx = false;
      bool ISjSHdcCiC = false;
      bool zByjZnTAZi = false;
      bool iTaLQzdRPk = false;
      bool RjSGmBLRHj = false;
      bool LLKITxilTD = false;
      bool ZJzANoqYBI = false;
      bool ALlyjPirwX = false;
      bool bBspXWIRrS = false;
      bool PqyMKIjSry = false;
      bool JmQyjzZLYD = false;
      bool OppubYQJbq = false;
      string iMMjCWidHy;
      string RuCslqtVos;
      string BHiLkUdDlF;
      string ohacwfODHs;
      string hEjVBnxtWC;
      string jkQdIadAzg;
      string sfrBIjUYwF;
      string cpNwKwXMJx;
      string XjfiVDQwUU;
      string CNEZACLiMR;
      string TXxQZtWUSL;
      string DQqCJIzJfF;
      string SXEaCOlnwI;
      string jnAqcAmOIa;
      string fwdIQlVCQq;
      string CCCHzwSVOK;
      string IiYKaPQAYJ;
      string VkAFYVsuKQ;
      string riWEGhlrqg;
      string gQAySxXThB;
      if(iMMjCWidHy == TXxQZtWUSL){VVdHVRCxic = true;}
      else if(TXxQZtWUSL == iMMjCWidHy){zByjZnTAZi = true;}
      if(RuCslqtVos == DQqCJIzJfF){CXLyRYMTDs = true;}
      else if(DQqCJIzJfF == RuCslqtVos){iTaLQzdRPk = true;}
      if(BHiLkUdDlF == SXEaCOlnwI){cXIqbEjClb = true;}
      else if(SXEaCOlnwI == BHiLkUdDlF){RjSGmBLRHj = true;}
      if(ohacwfODHs == jnAqcAmOIa){yZNItVFPio = true;}
      else if(jnAqcAmOIa == ohacwfODHs){LLKITxilTD = true;}
      if(hEjVBnxtWC == fwdIQlVCQq){enJOeJFCfs = true;}
      else if(fwdIQlVCQq == hEjVBnxtWC){ZJzANoqYBI = true;}
      if(jkQdIadAzg == CCCHzwSVOK){jEPnYxNmeQ = true;}
      else if(CCCHzwSVOK == jkQdIadAzg){ALlyjPirwX = true;}
      if(sfrBIjUYwF == IiYKaPQAYJ){gAKGebJDDw = true;}
      else if(IiYKaPQAYJ == sfrBIjUYwF){bBspXWIRrS = true;}
      if(cpNwKwXMJx == VkAFYVsuKQ){TwjOOoOtLS = true;}
      if(XjfiVDQwUU == riWEGhlrqg){zhVsqtKZjx = true;}
      if(CNEZACLiMR == gQAySxXThB){ISjSHdcCiC = true;}
      while(VkAFYVsuKQ == cpNwKwXMJx){PqyMKIjSry = true;}
      while(riWEGhlrqg == riWEGhlrqg){JmQyjzZLYD = true;}
      while(gQAySxXThB == gQAySxXThB){OppubYQJbq = true;}
      if(VVdHVRCxic == true){VVdHVRCxic = false;}
      if(CXLyRYMTDs == true){CXLyRYMTDs = false;}
      if(cXIqbEjClb == true){cXIqbEjClb = false;}
      if(yZNItVFPio == true){yZNItVFPio = false;}
      if(enJOeJFCfs == true){enJOeJFCfs = false;}
      if(jEPnYxNmeQ == true){jEPnYxNmeQ = false;}
      if(gAKGebJDDw == true){gAKGebJDDw = false;}
      if(TwjOOoOtLS == true){TwjOOoOtLS = false;}
      if(zhVsqtKZjx == true){zhVsqtKZjx = false;}
      if(ISjSHdcCiC == true){ISjSHdcCiC = false;}
      if(zByjZnTAZi == true){zByjZnTAZi = false;}
      if(iTaLQzdRPk == true){iTaLQzdRPk = false;}
      if(RjSGmBLRHj == true){RjSGmBLRHj = false;}
      if(LLKITxilTD == true){LLKITxilTD = false;}
      if(ZJzANoqYBI == true){ZJzANoqYBI = false;}
      if(ALlyjPirwX == true){ALlyjPirwX = false;}
      if(bBspXWIRrS == true){bBspXWIRrS = false;}
      if(PqyMKIjSry == true){PqyMKIjSry = false;}
      if(JmQyjzZLYD == true){JmQyjzZLYD = false;}
      if(OppubYQJbq == true){OppubYQJbq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EOAUTMMKXP
{ 
  void GGciiCEcAh()
  { 
      bool dkhyXedkPd = false;
      bool quZGdWHMCu = false;
      bool CNxUtsXESD = false;
      bool wGXqdWrzSu = false;
      bool eRisFxnJnf = false;
      bool zwYnXQnNEe = false;
      bool GYRLhkXicG = false;
      bool eHtHPkeEPw = false;
      bool EOQlEAhiSM = false;
      bool ietnnFzWLU = false;
      bool YEggBqBRXl = false;
      bool liyIZqIeHg = false;
      bool CoPPXzMFSK = false;
      bool lHrtWzhjkN = false;
      bool yPLgazglOx = false;
      bool xTPdRjoQIB = false;
      bool duzNAdqDlZ = false;
      bool JYtthmcinY = false;
      bool SaqVMRqOcl = false;
      bool KQaiiCQyfx = false;
      string ONJeEsxhRb;
      string jijmaXfDWX;
      string mNzUHcgmDS;
      string BdWrttYNwG;
      string tEbZJXlitz;
      string qxqytANoXa;
      string LJdyaFLqrf;
      string zRGQcilZLi;
      string qxrDaDmYyt;
      string fjoVtjZcyD;
      string MupOAZpZUL;
      string NncoiORZWX;
      string SlryAObkVr;
      string IIaHWwGdDB;
      string MMDlfrGAlf;
      string SAGajZCrOk;
      string yFDbDFNURm;
      string HnWVKFhGRH;
      string HaypZICzXx;
      string sOPRDGJbia;
      if(ONJeEsxhRb == MupOAZpZUL){dkhyXedkPd = true;}
      else if(MupOAZpZUL == ONJeEsxhRb){YEggBqBRXl = true;}
      if(jijmaXfDWX == NncoiORZWX){quZGdWHMCu = true;}
      else if(NncoiORZWX == jijmaXfDWX){liyIZqIeHg = true;}
      if(mNzUHcgmDS == SlryAObkVr){CNxUtsXESD = true;}
      else if(SlryAObkVr == mNzUHcgmDS){CoPPXzMFSK = true;}
      if(BdWrttYNwG == IIaHWwGdDB){wGXqdWrzSu = true;}
      else if(IIaHWwGdDB == BdWrttYNwG){lHrtWzhjkN = true;}
      if(tEbZJXlitz == MMDlfrGAlf){eRisFxnJnf = true;}
      else if(MMDlfrGAlf == tEbZJXlitz){yPLgazglOx = true;}
      if(qxqytANoXa == SAGajZCrOk){zwYnXQnNEe = true;}
      else if(SAGajZCrOk == qxqytANoXa){xTPdRjoQIB = true;}
      if(LJdyaFLqrf == yFDbDFNURm){GYRLhkXicG = true;}
      else if(yFDbDFNURm == LJdyaFLqrf){duzNAdqDlZ = true;}
      if(zRGQcilZLi == HnWVKFhGRH){eHtHPkeEPw = true;}
      if(qxrDaDmYyt == HaypZICzXx){EOQlEAhiSM = true;}
      if(fjoVtjZcyD == sOPRDGJbia){ietnnFzWLU = true;}
      while(HnWVKFhGRH == zRGQcilZLi){JYtthmcinY = true;}
      while(HaypZICzXx == HaypZICzXx){SaqVMRqOcl = true;}
      while(sOPRDGJbia == sOPRDGJbia){KQaiiCQyfx = true;}
      if(dkhyXedkPd == true){dkhyXedkPd = false;}
      if(quZGdWHMCu == true){quZGdWHMCu = false;}
      if(CNxUtsXESD == true){CNxUtsXESD = false;}
      if(wGXqdWrzSu == true){wGXqdWrzSu = false;}
      if(eRisFxnJnf == true){eRisFxnJnf = false;}
      if(zwYnXQnNEe == true){zwYnXQnNEe = false;}
      if(GYRLhkXicG == true){GYRLhkXicG = false;}
      if(eHtHPkeEPw == true){eHtHPkeEPw = false;}
      if(EOQlEAhiSM == true){EOQlEAhiSM = false;}
      if(ietnnFzWLU == true){ietnnFzWLU = false;}
      if(YEggBqBRXl == true){YEggBqBRXl = false;}
      if(liyIZqIeHg == true){liyIZqIeHg = false;}
      if(CoPPXzMFSK == true){CoPPXzMFSK = false;}
      if(lHrtWzhjkN == true){lHrtWzhjkN = false;}
      if(yPLgazglOx == true){yPLgazglOx = false;}
      if(xTPdRjoQIB == true){xTPdRjoQIB = false;}
      if(duzNAdqDlZ == true){duzNAdqDlZ = false;}
      if(JYtthmcinY == true){JYtthmcinY = false;}
      if(SaqVMRqOcl == true){SaqVMRqOcl = false;}
      if(KQaiiCQyfx == true){KQaiiCQyfx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FEODQDSIKU
{ 
  void JgcbOAdfYr()
  { 
      bool RUQdYjBzQq = false;
      bool pQPnwwksTZ = false;
      bool EeQmAYsPCb = false;
      bool RTmGxjgtFh = false;
      bool briuFcUMEw = false;
      bool fXYYkmEdcz = false;
      bool qlxnYVcJpL = false;
      bool PpmkyMwUgX = false;
      bool EfLFwtuNVK = false;
      bool fCQFqpttVi = false;
      bool zLVrgojmaY = false;
      bool qjwFuKaqre = false;
      bool aOmffMZhtI = false;
      bool RByyXrKSYH = false;
      bool JHmwSwGKJf = false;
      bool ODCpIkXpMU = false;
      bool PBsRGokyhC = false;
      bool AHSkVTaqMj = false;
      bool GOXNsOzHpl = false;
      bool UUGDrHNUpd = false;
      string HhdNKktjKm;
      string DViWEjcCpL;
      string VHJCpdmdhx;
      string qJQnTIQBsm;
      string pnqXqynwKz;
      string SNlDizYbWf;
      string xPBNwtEuCu;
      string TaJCVhQkKq;
      string pqShddWMEU;
      string joeNoZldbx;
      string tstPfqEihA;
      string imQfpGwSiS;
      string WqphLdwuMu;
      string wmINxwxDCm;
      string YneDkwYyXi;
      string cSuJZCDLDB;
      string tIWlEwdDhs;
      string JsQusiMmwP;
      string FxXdSdqzmu;
      string skAAsQQrzo;
      if(HhdNKktjKm == tstPfqEihA){RUQdYjBzQq = true;}
      else if(tstPfqEihA == HhdNKktjKm){zLVrgojmaY = true;}
      if(DViWEjcCpL == imQfpGwSiS){pQPnwwksTZ = true;}
      else if(imQfpGwSiS == DViWEjcCpL){qjwFuKaqre = true;}
      if(VHJCpdmdhx == WqphLdwuMu){EeQmAYsPCb = true;}
      else if(WqphLdwuMu == VHJCpdmdhx){aOmffMZhtI = true;}
      if(qJQnTIQBsm == wmINxwxDCm){RTmGxjgtFh = true;}
      else if(wmINxwxDCm == qJQnTIQBsm){RByyXrKSYH = true;}
      if(pnqXqynwKz == YneDkwYyXi){briuFcUMEw = true;}
      else if(YneDkwYyXi == pnqXqynwKz){JHmwSwGKJf = true;}
      if(SNlDizYbWf == cSuJZCDLDB){fXYYkmEdcz = true;}
      else if(cSuJZCDLDB == SNlDizYbWf){ODCpIkXpMU = true;}
      if(xPBNwtEuCu == tIWlEwdDhs){qlxnYVcJpL = true;}
      else if(tIWlEwdDhs == xPBNwtEuCu){PBsRGokyhC = true;}
      if(TaJCVhQkKq == JsQusiMmwP){PpmkyMwUgX = true;}
      if(pqShddWMEU == FxXdSdqzmu){EfLFwtuNVK = true;}
      if(joeNoZldbx == skAAsQQrzo){fCQFqpttVi = true;}
      while(JsQusiMmwP == TaJCVhQkKq){AHSkVTaqMj = true;}
      while(FxXdSdqzmu == FxXdSdqzmu){GOXNsOzHpl = true;}
      while(skAAsQQrzo == skAAsQQrzo){UUGDrHNUpd = true;}
      if(RUQdYjBzQq == true){RUQdYjBzQq = false;}
      if(pQPnwwksTZ == true){pQPnwwksTZ = false;}
      if(EeQmAYsPCb == true){EeQmAYsPCb = false;}
      if(RTmGxjgtFh == true){RTmGxjgtFh = false;}
      if(briuFcUMEw == true){briuFcUMEw = false;}
      if(fXYYkmEdcz == true){fXYYkmEdcz = false;}
      if(qlxnYVcJpL == true){qlxnYVcJpL = false;}
      if(PpmkyMwUgX == true){PpmkyMwUgX = false;}
      if(EfLFwtuNVK == true){EfLFwtuNVK = false;}
      if(fCQFqpttVi == true){fCQFqpttVi = false;}
      if(zLVrgojmaY == true){zLVrgojmaY = false;}
      if(qjwFuKaqre == true){qjwFuKaqre = false;}
      if(aOmffMZhtI == true){aOmffMZhtI = false;}
      if(RByyXrKSYH == true){RByyXrKSYH = false;}
      if(JHmwSwGKJf == true){JHmwSwGKJf = false;}
      if(ODCpIkXpMU == true){ODCpIkXpMU = false;}
      if(PBsRGokyhC == true){PBsRGokyhC = false;}
      if(AHSkVTaqMj == true){AHSkVTaqMj = false;}
      if(GOXNsOzHpl == true){GOXNsOzHpl = false;}
      if(UUGDrHNUpd == true){UUGDrHNUpd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUJQJMPALM
{ 
  void GpwTXNMOVr()
  { 
      bool TuxBrBgxEg = false;
      bool IFLXfcaYzR = false;
      bool ahTlcVofUW = false;
      bool gnPimDxXZg = false;
      bool JidhoaFhOQ = false;
      bool zAKBSlbKYV = false;
      bool MAbhATockc = false;
      bool fDyRIqDkxB = false;
      bool QGREWfdOPA = false;
      bool blyEUIHuhU = false;
      bool kbxkkwCssb = false;
      bool hpNXFFhXKT = false;
      bool pZMjBsEtwz = false;
      bool jIDbQnJfSa = false;
      bool djVnSkYazP = false;
      bool ajkNeKPNjr = false;
      bool qIwtrZlkHQ = false;
      bool wBEjpFEYQP = false;
      bool TdugYAWoxF = false;
      bool YwwaiVnbur = false;
      string XoICHqyaaJ;
      string ufjTfOTNMa;
      string FkZGGIYJoX;
      string XQetnBTSnq;
      string RwxMqAnyBE;
      string CLKXOmPCuy;
      string SolDkdAped;
      string uAZVIImMPF;
      string TZIjUMGHfB;
      string lQXoXcKtbM;
      string AyTWJBknOF;
      string zClodsfChY;
      string XrJdqdckxf;
      string yrkDFVGkaS;
      string aRsaBjehKe;
      string wHMCnHooef;
      string YAqiHHQijI;
      string muaOxGzicG;
      string zuZRipfiOx;
      string fQGutaZKSt;
      if(XoICHqyaaJ == AyTWJBknOF){TuxBrBgxEg = true;}
      else if(AyTWJBknOF == XoICHqyaaJ){kbxkkwCssb = true;}
      if(ufjTfOTNMa == zClodsfChY){IFLXfcaYzR = true;}
      else if(zClodsfChY == ufjTfOTNMa){hpNXFFhXKT = true;}
      if(FkZGGIYJoX == XrJdqdckxf){ahTlcVofUW = true;}
      else if(XrJdqdckxf == FkZGGIYJoX){pZMjBsEtwz = true;}
      if(XQetnBTSnq == yrkDFVGkaS){gnPimDxXZg = true;}
      else if(yrkDFVGkaS == XQetnBTSnq){jIDbQnJfSa = true;}
      if(RwxMqAnyBE == aRsaBjehKe){JidhoaFhOQ = true;}
      else if(aRsaBjehKe == RwxMqAnyBE){djVnSkYazP = true;}
      if(CLKXOmPCuy == wHMCnHooef){zAKBSlbKYV = true;}
      else if(wHMCnHooef == CLKXOmPCuy){ajkNeKPNjr = true;}
      if(SolDkdAped == YAqiHHQijI){MAbhATockc = true;}
      else if(YAqiHHQijI == SolDkdAped){qIwtrZlkHQ = true;}
      if(uAZVIImMPF == muaOxGzicG){fDyRIqDkxB = true;}
      if(TZIjUMGHfB == zuZRipfiOx){QGREWfdOPA = true;}
      if(lQXoXcKtbM == fQGutaZKSt){blyEUIHuhU = true;}
      while(muaOxGzicG == uAZVIImMPF){wBEjpFEYQP = true;}
      while(zuZRipfiOx == zuZRipfiOx){TdugYAWoxF = true;}
      while(fQGutaZKSt == fQGutaZKSt){YwwaiVnbur = true;}
      if(TuxBrBgxEg == true){TuxBrBgxEg = false;}
      if(IFLXfcaYzR == true){IFLXfcaYzR = false;}
      if(ahTlcVofUW == true){ahTlcVofUW = false;}
      if(gnPimDxXZg == true){gnPimDxXZg = false;}
      if(JidhoaFhOQ == true){JidhoaFhOQ = false;}
      if(zAKBSlbKYV == true){zAKBSlbKYV = false;}
      if(MAbhATockc == true){MAbhATockc = false;}
      if(fDyRIqDkxB == true){fDyRIqDkxB = false;}
      if(QGREWfdOPA == true){QGREWfdOPA = false;}
      if(blyEUIHuhU == true){blyEUIHuhU = false;}
      if(kbxkkwCssb == true){kbxkkwCssb = false;}
      if(hpNXFFhXKT == true){hpNXFFhXKT = false;}
      if(pZMjBsEtwz == true){pZMjBsEtwz = false;}
      if(jIDbQnJfSa == true){jIDbQnJfSa = false;}
      if(djVnSkYazP == true){djVnSkYazP = false;}
      if(ajkNeKPNjr == true){ajkNeKPNjr = false;}
      if(qIwtrZlkHQ == true){qIwtrZlkHQ = false;}
      if(wBEjpFEYQP == true){wBEjpFEYQP = false;}
      if(TdugYAWoxF == true){TdugYAWoxF = false;}
      if(YwwaiVnbur == true){YwwaiVnbur = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMMXOUAUTJ
{ 
  void EFZnhYVfzS()
  { 
      bool qryTiQfUUt = false;
      bool NVIlnCXOkm = false;
      bool zowpYsMuqm = false;
      bool uYRUBAdCBI = false;
      bool UTCfyRNwYH = false;
      bool zloSiCuItp = false;
      bool EkdgyoDmjn = false;
      bool YUMbSfmQrG = false;
      bool fPVimJizlz = false;
      bool EVHLDioUgI = false;
      bool NZMjidYNzD = false;
      bool PePnKnPtto = false;
      bool FEBkjCMBXi = false;
      bool pRiirFDlAI = false;
      bool jVzhiYFTAO = false;
      bool TuarDJYazf = false;
      bool RWoPNxwguF = false;
      bool kdskEjESBL = false;
      bool xrBIPtqqfi = false;
      bool fblUqMgiUl = false;
      string hUiphPmise;
      string nKbfxUjtqm;
      string SPBkotzisI;
      string pCqlljEdPL;
      string bittbRAepG;
      string NbPINSTyAn;
      string QDpjokSosN;
      string PGeeLiUGIX;
      string sTrluOliXT;
      string QGcbuXsKFp;
      string yKlcqHxjxd;
      string xMpbuwKDoa;
      string yjRZxJcDjm;
      string pKBRZhhOun;
      string QBksVDQAgy;
      string MoVdqNsLfg;
      string dtAKnmLXCM;
      string OuIAJxzXDs;
      string sbVkZBnWaL;
      string nViNJWBZFh;
      if(hUiphPmise == yKlcqHxjxd){qryTiQfUUt = true;}
      else if(yKlcqHxjxd == hUiphPmise){NZMjidYNzD = true;}
      if(nKbfxUjtqm == xMpbuwKDoa){NVIlnCXOkm = true;}
      else if(xMpbuwKDoa == nKbfxUjtqm){PePnKnPtto = true;}
      if(SPBkotzisI == yjRZxJcDjm){zowpYsMuqm = true;}
      else if(yjRZxJcDjm == SPBkotzisI){FEBkjCMBXi = true;}
      if(pCqlljEdPL == pKBRZhhOun){uYRUBAdCBI = true;}
      else if(pKBRZhhOun == pCqlljEdPL){pRiirFDlAI = true;}
      if(bittbRAepG == QBksVDQAgy){UTCfyRNwYH = true;}
      else if(QBksVDQAgy == bittbRAepG){jVzhiYFTAO = true;}
      if(NbPINSTyAn == MoVdqNsLfg){zloSiCuItp = true;}
      else if(MoVdqNsLfg == NbPINSTyAn){TuarDJYazf = true;}
      if(QDpjokSosN == dtAKnmLXCM){EkdgyoDmjn = true;}
      else if(dtAKnmLXCM == QDpjokSosN){RWoPNxwguF = true;}
      if(PGeeLiUGIX == OuIAJxzXDs){YUMbSfmQrG = true;}
      if(sTrluOliXT == sbVkZBnWaL){fPVimJizlz = true;}
      if(QGcbuXsKFp == nViNJWBZFh){EVHLDioUgI = true;}
      while(OuIAJxzXDs == PGeeLiUGIX){kdskEjESBL = true;}
      while(sbVkZBnWaL == sbVkZBnWaL){xrBIPtqqfi = true;}
      while(nViNJWBZFh == nViNJWBZFh){fblUqMgiUl = true;}
      if(qryTiQfUUt == true){qryTiQfUUt = false;}
      if(NVIlnCXOkm == true){NVIlnCXOkm = false;}
      if(zowpYsMuqm == true){zowpYsMuqm = false;}
      if(uYRUBAdCBI == true){uYRUBAdCBI = false;}
      if(UTCfyRNwYH == true){UTCfyRNwYH = false;}
      if(zloSiCuItp == true){zloSiCuItp = false;}
      if(EkdgyoDmjn == true){EkdgyoDmjn = false;}
      if(YUMbSfmQrG == true){YUMbSfmQrG = false;}
      if(fPVimJizlz == true){fPVimJizlz = false;}
      if(EVHLDioUgI == true){EVHLDioUgI = false;}
      if(NZMjidYNzD == true){NZMjidYNzD = false;}
      if(PePnKnPtto == true){PePnKnPtto = false;}
      if(FEBkjCMBXi == true){FEBkjCMBXi = false;}
      if(pRiirFDlAI == true){pRiirFDlAI = false;}
      if(jVzhiYFTAO == true){jVzhiYFTAO = false;}
      if(TuarDJYazf == true){TuarDJYazf = false;}
      if(RWoPNxwguF == true){RWoPNxwguF = false;}
      if(kdskEjESBL == true){kdskEjESBL = false;}
      if(xrBIPtqqfi == true){xrBIPtqqfi = false;}
      if(fblUqMgiUl == true){fblUqMgiUl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XYKLTLNMFI
{ 
  void idItrIBFAU()
  { 
      bool GRLgNeuZqa = false;
      bool pNWLuPnLju = false;
      bool CorjoQicbH = false;
      bool AUIiFyLOVH = false;
      bool QeWhnyKJfl = false;
      bool KwaOyQZbqx = false;
      bool wRxiaUEmGx = false;
      bool EYpbeXSJuq = false;
      bool GYxpxDttkn = false;
      bool XiXXLygmGT = false;
      bool tWDiglFyia = false;
      bool yPfAqXUHlW = false;
      bool ZKBRYVASQf = false;
      bool peCbwiVNIK = false;
      bool xwKKoICXfn = false;
      bool dZAjtiVkKL = false;
      bool kmhDkTNEDI = false;
      bool BGyaYdzqbQ = false;
      bool SclcCPdSgN = false;
      bool NjDxYKNHYV = false;
      string zsUHlaJIzK;
      string lRVhijbkPW;
      string cDcoIkBZcC;
      string VebETopncW;
      string RYVcCYeNmq;
      string ZXjzVwPeyA;
      string YjewnHpQOt;
      string tnIsEEgAmi;
      string GmlkbyubhW;
      string YKocxhsYnu;
      string iOzswlPqtR;
      string PPrOtlxsUp;
      string LNhrUjyeuW;
      string KIMqArnsnp;
      string iDhQHJSaiL;
      string jzEyiVfHXM;
      string mjuWGGDAOB;
      string xEEdGIfRjL;
      string QXwjmLENId;
      string MgVbCyIKJA;
      if(zsUHlaJIzK == iOzswlPqtR){GRLgNeuZqa = true;}
      else if(iOzswlPqtR == zsUHlaJIzK){tWDiglFyia = true;}
      if(lRVhijbkPW == PPrOtlxsUp){pNWLuPnLju = true;}
      else if(PPrOtlxsUp == lRVhijbkPW){yPfAqXUHlW = true;}
      if(cDcoIkBZcC == LNhrUjyeuW){CorjoQicbH = true;}
      else if(LNhrUjyeuW == cDcoIkBZcC){ZKBRYVASQf = true;}
      if(VebETopncW == KIMqArnsnp){AUIiFyLOVH = true;}
      else if(KIMqArnsnp == VebETopncW){peCbwiVNIK = true;}
      if(RYVcCYeNmq == iDhQHJSaiL){QeWhnyKJfl = true;}
      else if(iDhQHJSaiL == RYVcCYeNmq){xwKKoICXfn = true;}
      if(ZXjzVwPeyA == jzEyiVfHXM){KwaOyQZbqx = true;}
      else if(jzEyiVfHXM == ZXjzVwPeyA){dZAjtiVkKL = true;}
      if(YjewnHpQOt == mjuWGGDAOB){wRxiaUEmGx = true;}
      else if(mjuWGGDAOB == YjewnHpQOt){kmhDkTNEDI = true;}
      if(tnIsEEgAmi == xEEdGIfRjL){EYpbeXSJuq = true;}
      if(GmlkbyubhW == QXwjmLENId){GYxpxDttkn = true;}
      if(YKocxhsYnu == MgVbCyIKJA){XiXXLygmGT = true;}
      while(xEEdGIfRjL == tnIsEEgAmi){BGyaYdzqbQ = true;}
      while(QXwjmLENId == QXwjmLENId){SclcCPdSgN = true;}
      while(MgVbCyIKJA == MgVbCyIKJA){NjDxYKNHYV = true;}
      if(GRLgNeuZqa == true){GRLgNeuZqa = false;}
      if(pNWLuPnLju == true){pNWLuPnLju = false;}
      if(CorjoQicbH == true){CorjoQicbH = false;}
      if(AUIiFyLOVH == true){AUIiFyLOVH = false;}
      if(QeWhnyKJfl == true){QeWhnyKJfl = false;}
      if(KwaOyQZbqx == true){KwaOyQZbqx = false;}
      if(wRxiaUEmGx == true){wRxiaUEmGx = false;}
      if(EYpbeXSJuq == true){EYpbeXSJuq = false;}
      if(GYxpxDttkn == true){GYxpxDttkn = false;}
      if(XiXXLygmGT == true){XiXXLygmGT = false;}
      if(tWDiglFyia == true){tWDiglFyia = false;}
      if(yPfAqXUHlW == true){yPfAqXUHlW = false;}
      if(ZKBRYVASQf == true){ZKBRYVASQf = false;}
      if(peCbwiVNIK == true){peCbwiVNIK = false;}
      if(xwKKoICXfn == true){xwKKoICXfn = false;}
      if(dZAjtiVkKL == true){dZAjtiVkKL = false;}
      if(kmhDkTNEDI == true){kmhDkTNEDI = false;}
      if(BGyaYdzqbQ == true){BGyaYdzqbQ = false;}
      if(SclcCPdSgN == true){SclcCPdSgN = false;}
      if(NjDxYKNHYV == true){NjDxYKNHYV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PLNGFLDYSX
{ 
  void knNjsuDQsk()
  { 
      bool bfGbBnPAeU = false;
      bool GgQfIchBar = false;
      bool yWtGDQIbky = false;
      bool fYEuhpzajt = false;
      bool nrTeGdVeAg = false;
      bool HxRTdFlAXj = false;
      bool enPfngcUyS = false;
      bool cGRfEFCOzY = false;
      bool tdbDpiHjRb = false;
      bool DyCzOzcmqY = false;
      bool BBfgDBfkPX = false;
      bool DXAzpBLLpF = false;
      bool ZrDVOdESRE = false;
      bool bOWaWsxtzo = false;
      bool CVUsYfyDJN = false;
      bool mRxlzJxKSZ = false;
      bool wMTKwnAZbw = false;
      bool DRLACDXJxh = false;
      bool fAJDQKQjaN = false;
      bool umbZrpCJxj = false;
      string gjmnyQSElF;
      string ELiHRCWaxa;
      string ATxXEsetMk;
      string nUhwOXjMTV;
      string DToyDYLXst;
      string ZjEajMlOjF;
      string lXrBRidmss;
      string RJHaXgdyUf;
      string gGBRKDQHMB;
      string kUcOjebngT;
      string uXezcPcdDC;
      string hmtDXeWZqN;
      string SVaqIxfspr;
      string FpRAkIaCot;
      string ZmEJTxZZpF;
      string IBxSAYxnqf;
      string jjmKwqVtSO;
      string DTkwnfRQXK;
      string WGCkiEszzM;
      string LmLIKozsMb;
      if(gjmnyQSElF == uXezcPcdDC){bfGbBnPAeU = true;}
      else if(uXezcPcdDC == gjmnyQSElF){BBfgDBfkPX = true;}
      if(ELiHRCWaxa == hmtDXeWZqN){GgQfIchBar = true;}
      else if(hmtDXeWZqN == ELiHRCWaxa){DXAzpBLLpF = true;}
      if(ATxXEsetMk == SVaqIxfspr){yWtGDQIbky = true;}
      else if(SVaqIxfspr == ATxXEsetMk){ZrDVOdESRE = true;}
      if(nUhwOXjMTV == FpRAkIaCot){fYEuhpzajt = true;}
      else if(FpRAkIaCot == nUhwOXjMTV){bOWaWsxtzo = true;}
      if(DToyDYLXst == ZmEJTxZZpF){nrTeGdVeAg = true;}
      else if(ZmEJTxZZpF == DToyDYLXst){CVUsYfyDJN = true;}
      if(ZjEajMlOjF == IBxSAYxnqf){HxRTdFlAXj = true;}
      else if(IBxSAYxnqf == ZjEajMlOjF){mRxlzJxKSZ = true;}
      if(lXrBRidmss == jjmKwqVtSO){enPfngcUyS = true;}
      else if(jjmKwqVtSO == lXrBRidmss){wMTKwnAZbw = true;}
      if(RJHaXgdyUf == DTkwnfRQXK){cGRfEFCOzY = true;}
      if(gGBRKDQHMB == WGCkiEszzM){tdbDpiHjRb = true;}
      if(kUcOjebngT == LmLIKozsMb){DyCzOzcmqY = true;}
      while(DTkwnfRQXK == RJHaXgdyUf){DRLACDXJxh = true;}
      while(WGCkiEszzM == WGCkiEszzM){fAJDQKQjaN = true;}
      while(LmLIKozsMb == LmLIKozsMb){umbZrpCJxj = true;}
      if(bfGbBnPAeU == true){bfGbBnPAeU = false;}
      if(GgQfIchBar == true){GgQfIchBar = false;}
      if(yWtGDQIbky == true){yWtGDQIbky = false;}
      if(fYEuhpzajt == true){fYEuhpzajt = false;}
      if(nrTeGdVeAg == true){nrTeGdVeAg = false;}
      if(HxRTdFlAXj == true){HxRTdFlAXj = false;}
      if(enPfngcUyS == true){enPfngcUyS = false;}
      if(cGRfEFCOzY == true){cGRfEFCOzY = false;}
      if(tdbDpiHjRb == true){tdbDpiHjRb = false;}
      if(DyCzOzcmqY == true){DyCzOzcmqY = false;}
      if(BBfgDBfkPX == true){BBfgDBfkPX = false;}
      if(DXAzpBLLpF == true){DXAzpBLLpF = false;}
      if(ZrDVOdESRE == true){ZrDVOdESRE = false;}
      if(bOWaWsxtzo == true){bOWaWsxtzo = false;}
      if(CVUsYfyDJN == true){CVUsYfyDJN = false;}
      if(mRxlzJxKSZ == true){mRxlzJxKSZ = false;}
      if(wMTKwnAZbw == true){wMTKwnAZbw = false;}
      if(DRLACDXJxh == true){DRLACDXJxh = false;}
      if(fAJDQKQjaN == true){fAJDQKQjaN = false;}
      if(umbZrpCJxj == true){umbZrpCJxj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TUXOELFMRO
{ 
  void gEIhYVGJLR()
  { 
      bool spWKnDYQWx = false;
      bool BrmyYlKOkx = false;
      bool yejggoXhDj = false;
      bool htWcsTAHaO = false;
      bool iboHzXhKkG = false;
      bool PenOBOGodz = false;
      bool epMmOHVKFE = false;
      bool kDmVNVobhI = false;
      bool HNxxTDGHbe = false;
      bool NLdbisPCsq = false;
      bool CXEgUMqRAe = false;
      bool YdGUqRsPSK = false;
      bool BNhaqZZKmU = false;
      bool GlhpGjIPbH = false;
      bool LnGxFiEIkR = false;
      bool Azjhpnodot = false;
      bool lgefYluPNH = false;
      bool JcmKyNHkUH = false;
      bool VQZUUGCAAS = false;
      bool tdagUeIaXS = false;
      string VrUWjcfjtJ;
      string metFqLmSWE;
      string mJOwfhLCeJ;
      string jUBBzyWBxM;
      string oJtWrsRpAM;
      string WZDTHLcXqC;
      string RdFjZRcrGr;
      string nlUJOdPrEl;
      string PUCRmJRhtm;
      string VyJtuLEJxZ;
      string QYiHYkEsFd;
      string wkTEmwamxP;
      string AuySWobaOC;
      string YFteVpktsB;
      string EXbQpjeFHz;
      string jRMhYUZPki;
      string IddCEqqohw;
      string KgswKbShcl;
      string JWSPRHrMFB;
      string PUIKrasYLz;
      if(VrUWjcfjtJ == QYiHYkEsFd){spWKnDYQWx = true;}
      else if(QYiHYkEsFd == VrUWjcfjtJ){CXEgUMqRAe = true;}
      if(metFqLmSWE == wkTEmwamxP){BrmyYlKOkx = true;}
      else if(wkTEmwamxP == metFqLmSWE){YdGUqRsPSK = true;}
      if(mJOwfhLCeJ == AuySWobaOC){yejggoXhDj = true;}
      else if(AuySWobaOC == mJOwfhLCeJ){BNhaqZZKmU = true;}
      if(jUBBzyWBxM == YFteVpktsB){htWcsTAHaO = true;}
      else if(YFteVpktsB == jUBBzyWBxM){GlhpGjIPbH = true;}
      if(oJtWrsRpAM == EXbQpjeFHz){iboHzXhKkG = true;}
      else if(EXbQpjeFHz == oJtWrsRpAM){LnGxFiEIkR = true;}
      if(WZDTHLcXqC == jRMhYUZPki){PenOBOGodz = true;}
      else if(jRMhYUZPki == WZDTHLcXqC){Azjhpnodot = true;}
      if(RdFjZRcrGr == IddCEqqohw){epMmOHVKFE = true;}
      else if(IddCEqqohw == RdFjZRcrGr){lgefYluPNH = true;}
      if(nlUJOdPrEl == KgswKbShcl){kDmVNVobhI = true;}
      if(PUCRmJRhtm == JWSPRHrMFB){HNxxTDGHbe = true;}
      if(VyJtuLEJxZ == PUIKrasYLz){NLdbisPCsq = true;}
      while(KgswKbShcl == nlUJOdPrEl){JcmKyNHkUH = true;}
      while(JWSPRHrMFB == JWSPRHrMFB){VQZUUGCAAS = true;}
      while(PUIKrasYLz == PUIKrasYLz){tdagUeIaXS = true;}
      if(spWKnDYQWx == true){spWKnDYQWx = false;}
      if(BrmyYlKOkx == true){BrmyYlKOkx = false;}
      if(yejggoXhDj == true){yejggoXhDj = false;}
      if(htWcsTAHaO == true){htWcsTAHaO = false;}
      if(iboHzXhKkG == true){iboHzXhKkG = false;}
      if(PenOBOGodz == true){PenOBOGodz = false;}
      if(epMmOHVKFE == true){epMmOHVKFE = false;}
      if(kDmVNVobhI == true){kDmVNVobhI = false;}
      if(HNxxTDGHbe == true){HNxxTDGHbe = false;}
      if(NLdbisPCsq == true){NLdbisPCsq = false;}
      if(CXEgUMqRAe == true){CXEgUMqRAe = false;}
      if(YdGUqRsPSK == true){YdGUqRsPSK = false;}
      if(BNhaqZZKmU == true){BNhaqZZKmU = false;}
      if(GlhpGjIPbH == true){GlhpGjIPbH = false;}
      if(LnGxFiEIkR == true){LnGxFiEIkR = false;}
      if(Azjhpnodot == true){Azjhpnodot = false;}
      if(lgefYluPNH == true){lgefYluPNH = false;}
      if(JcmKyNHkUH == true){JcmKyNHkUH = false;}
      if(VQZUUGCAAS == true){VQZUUGCAAS = false;}
      if(tdagUeIaXS == true){tdagUeIaXS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NOZJOVRYNA
{ 
  void lzSBudskeS()
  { 
      bool EAiHIkmsGZ = false;
      bool pLWRhlsHfJ = false;
      bool HFVLCSNCko = false;
      bool TndnkurmLc = false;
      bool nHYAwdDaVZ = false;
      bool ZpOmRzdWEo = false;
      bool XkIQFCgigl = false;
      bool tFwCVzfVPY = false;
      bool PmfKOdYpVk = false;
      bool QUiWFDzHts = false;
      bool wUsifUtLRR = false;
      bool SIHfYkExCb = false;
      bool cqMwVYWYxS = false;
      bool AXaWcuswet = false;
      bool jNYDRINCxU = false;
      bool yBFSPEIxNG = false;
      bool yUNzRugjCd = false;
      bool qHRHrPSIdM = false;
      bool LTbcTyRIGX = false;
      bool muiXuOzZlW = false;
      string kVVmUIRfiF;
      string RQBQXhMgnF;
      string hgQETZHWjR;
      string uBCAlYcLQJ;
      string wedpBLzNjc;
      string WCcKKDFRSu;
      string AuuQJQOAey;
      string EBQeIDDZCI;
      string atmGusXqph;
      string TLrUIBiMfj;
      string wyhlXVkyCG;
      string zeOKUGIoVQ;
      string rXKwdsIwVH;
      string UqtRLbLAiY;
      string IZoihoxhAC;
      string sspOrYmkHd;
      string MobtkIjwyr;
      string tHGxIShbOo;
      string wauTOaAeZl;
      string oasELSytxZ;
      if(kVVmUIRfiF == wyhlXVkyCG){EAiHIkmsGZ = true;}
      else if(wyhlXVkyCG == kVVmUIRfiF){wUsifUtLRR = true;}
      if(RQBQXhMgnF == zeOKUGIoVQ){pLWRhlsHfJ = true;}
      else if(zeOKUGIoVQ == RQBQXhMgnF){SIHfYkExCb = true;}
      if(hgQETZHWjR == rXKwdsIwVH){HFVLCSNCko = true;}
      else if(rXKwdsIwVH == hgQETZHWjR){cqMwVYWYxS = true;}
      if(uBCAlYcLQJ == UqtRLbLAiY){TndnkurmLc = true;}
      else if(UqtRLbLAiY == uBCAlYcLQJ){AXaWcuswet = true;}
      if(wedpBLzNjc == IZoihoxhAC){nHYAwdDaVZ = true;}
      else if(IZoihoxhAC == wedpBLzNjc){jNYDRINCxU = true;}
      if(WCcKKDFRSu == sspOrYmkHd){ZpOmRzdWEo = true;}
      else if(sspOrYmkHd == WCcKKDFRSu){yBFSPEIxNG = true;}
      if(AuuQJQOAey == MobtkIjwyr){XkIQFCgigl = true;}
      else if(MobtkIjwyr == AuuQJQOAey){yUNzRugjCd = true;}
      if(EBQeIDDZCI == tHGxIShbOo){tFwCVzfVPY = true;}
      if(atmGusXqph == wauTOaAeZl){PmfKOdYpVk = true;}
      if(TLrUIBiMfj == oasELSytxZ){QUiWFDzHts = true;}
      while(tHGxIShbOo == EBQeIDDZCI){qHRHrPSIdM = true;}
      while(wauTOaAeZl == wauTOaAeZl){LTbcTyRIGX = true;}
      while(oasELSytxZ == oasELSytxZ){muiXuOzZlW = true;}
      if(EAiHIkmsGZ == true){EAiHIkmsGZ = false;}
      if(pLWRhlsHfJ == true){pLWRhlsHfJ = false;}
      if(HFVLCSNCko == true){HFVLCSNCko = false;}
      if(TndnkurmLc == true){TndnkurmLc = false;}
      if(nHYAwdDaVZ == true){nHYAwdDaVZ = false;}
      if(ZpOmRzdWEo == true){ZpOmRzdWEo = false;}
      if(XkIQFCgigl == true){XkIQFCgigl = false;}
      if(tFwCVzfVPY == true){tFwCVzfVPY = false;}
      if(PmfKOdYpVk == true){PmfKOdYpVk = false;}
      if(QUiWFDzHts == true){QUiWFDzHts = false;}
      if(wUsifUtLRR == true){wUsifUtLRR = false;}
      if(SIHfYkExCb == true){SIHfYkExCb = false;}
      if(cqMwVYWYxS == true){cqMwVYWYxS = false;}
      if(AXaWcuswet == true){AXaWcuswet = false;}
      if(jNYDRINCxU == true){jNYDRINCxU = false;}
      if(yBFSPEIxNG == true){yBFSPEIxNG = false;}
      if(yUNzRugjCd == true){yUNzRugjCd = false;}
      if(qHRHrPSIdM == true){qHRHrPSIdM = false;}
      if(LTbcTyRIGX == true){LTbcTyRIGX = false;}
      if(muiXuOzZlW == true){muiXuOzZlW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCARGPWQUW
{ 
  void FkdizWGaEy()
  { 
      bool GEJpQVoctp = false;
      bool OhDKMMuxje = false;
      bool iAWzGHljkC = false;
      bool bxdftyIMPR = false;
      bool MLEOWhMUuA = false;
      bool xzxESFgKiJ = false;
      bool iFrqNQEWQN = false;
      bool EhgSSXwIbX = false;
      bool tRnkFcAYMn = false;
      bool RxcGhGSNAF = false;
      bool doEhwORelu = false;
      bool JYhLORQHlk = false;
      bool QeKbuGEajL = false;
      bool EhHWtFNGnp = false;
      bool LUlQesPRqQ = false;
      bool pLbPoyeblp = false;
      bool KpuZqaQLRI = false;
      bool EKSuZursxC = false;
      bool pmjTVrGrgu = false;
      bool alTyfUZMZD = false;
      string lkCQwlsZRR;
      string dapFAYMdUp;
      string TRgVlZPalu;
      string bGhehzKoSk;
      string PllQlZlSSN;
      string NYhaxTEgdW;
      string WRnVoXsLWB;
      string NXLiZgfPiM;
      string mxIXgDYGgO;
      string tdLwOxyPaO;
      string gauRzpMyAP;
      string nnxQiZJPol;
      string zleIGjMPUb;
      string iPnUfMCqXq;
      string pZGQZGgtMn;
      string nhaoPtwlKP;
      string dxcXgXzbkW;
      string XSrxuYfNhA;
      string DRCfnBoyFk;
      string QPfIMrwhjC;
      if(lkCQwlsZRR == gauRzpMyAP){GEJpQVoctp = true;}
      else if(gauRzpMyAP == lkCQwlsZRR){doEhwORelu = true;}
      if(dapFAYMdUp == nnxQiZJPol){OhDKMMuxje = true;}
      else if(nnxQiZJPol == dapFAYMdUp){JYhLORQHlk = true;}
      if(TRgVlZPalu == zleIGjMPUb){iAWzGHljkC = true;}
      else if(zleIGjMPUb == TRgVlZPalu){QeKbuGEajL = true;}
      if(bGhehzKoSk == iPnUfMCqXq){bxdftyIMPR = true;}
      else if(iPnUfMCqXq == bGhehzKoSk){EhHWtFNGnp = true;}
      if(PllQlZlSSN == pZGQZGgtMn){MLEOWhMUuA = true;}
      else if(pZGQZGgtMn == PllQlZlSSN){LUlQesPRqQ = true;}
      if(NYhaxTEgdW == nhaoPtwlKP){xzxESFgKiJ = true;}
      else if(nhaoPtwlKP == NYhaxTEgdW){pLbPoyeblp = true;}
      if(WRnVoXsLWB == dxcXgXzbkW){iFrqNQEWQN = true;}
      else if(dxcXgXzbkW == WRnVoXsLWB){KpuZqaQLRI = true;}
      if(NXLiZgfPiM == XSrxuYfNhA){EhgSSXwIbX = true;}
      if(mxIXgDYGgO == DRCfnBoyFk){tRnkFcAYMn = true;}
      if(tdLwOxyPaO == QPfIMrwhjC){RxcGhGSNAF = true;}
      while(XSrxuYfNhA == NXLiZgfPiM){EKSuZursxC = true;}
      while(DRCfnBoyFk == DRCfnBoyFk){pmjTVrGrgu = true;}
      while(QPfIMrwhjC == QPfIMrwhjC){alTyfUZMZD = true;}
      if(GEJpQVoctp == true){GEJpQVoctp = false;}
      if(OhDKMMuxje == true){OhDKMMuxje = false;}
      if(iAWzGHljkC == true){iAWzGHljkC = false;}
      if(bxdftyIMPR == true){bxdftyIMPR = false;}
      if(MLEOWhMUuA == true){MLEOWhMUuA = false;}
      if(xzxESFgKiJ == true){xzxESFgKiJ = false;}
      if(iFrqNQEWQN == true){iFrqNQEWQN = false;}
      if(EhgSSXwIbX == true){EhgSSXwIbX = false;}
      if(tRnkFcAYMn == true){tRnkFcAYMn = false;}
      if(RxcGhGSNAF == true){RxcGhGSNAF = false;}
      if(doEhwORelu == true){doEhwORelu = false;}
      if(JYhLORQHlk == true){JYhLORQHlk = false;}
      if(QeKbuGEajL == true){QeKbuGEajL = false;}
      if(EhHWtFNGnp == true){EhHWtFNGnp = false;}
      if(LUlQesPRqQ == true){LUlQesPRqQ = false;}
      if(pLbPoyeblp == true){pLbPoyeblp = false;}
      if(KpuZqaQLRI == true){KpuZqaQLRI = false;}
      if(EKSuZursxC == true){EKSuZursxC = false;}
      if(pmjTVrGrgu == true){pmjTVrGrgu = false;}
      if(alTyfUZMZD == true){alTyfUZMZD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PQMCYJOTKJ
{ 
  void BwzhMzLMqA()
  { 
      bool XcmSIeMlSw = false;
      bool BWIcidzKmt = false;
      bool hgRWGDXORy = false;
      bool UXYWxOERxW = false;
      bool OtfhegGMDw = false;
      bool QbPWmqKQLE = false;
      bool HxTUbcyleT = false;
      bool ZhMQfmAirY = false;
      bool wKKVhsHBiG = false;
      bool EnGrOQZLGB = false;
      bool iUgjVhOzqz = false;
      bool paXlHxmylh = false;
      bool UwDYPlaTBO = false;
      bool Nocppbcazz = false;
      bool dIKiPcPTkQ = false;
      bool dbYYfmQIUj = false;
      bool GuxblByhwe = false;
      bool TLzmDMkUIl = false;
      bool WGijklPEJC = false;
      bool LUGPriLhwO = false;
      string BfuIEywsod;
      string xAxKDHGJkC;
      string QsnRsURfWw;
      string QoEYTKiSor;
      string LyMJVpOVSQ;
      string sSpabHrcOi;
      string fPVrNIwYps;
      string XmUrpRfdwD;
      string GwNGCyzcwM;
      string SGDGLucUwN;
      string toeYrFyxkJ;
      string aNfLbjCOoO;
      string JScdZRiNgu;
      string oLgiIQQnNx;
      string ABrlkEZqda;
      string sNehDbMBya;
      string VjPoUPfxDL;
      string SNBrOHaprV;
      string rrjFCagzef;
      string EPpmaPlCQV;
      if(BfuIEywsod == toeYrFyxkJ){XcmSIeMlSw = true;}
      else if(toeYrFyxkJ == BfuIEywsod){iUgjVhOzqz = true;}
      if(xAxKDHGJkC == aNfLbjCOoO){BWIcidzKmt = true;}
      else if(aNfLbjCOoO == xAxKDHGJkC){paXlHxmylh = true;}
      if(QsnRsURfWw == JScdZRiNgu){hgRWGDXORy = true;}
      else if(JScdZRiNgu == QsnRsURfWw){UwDYPlaTBO = true;}
      if(QoEYTKiSor == oLgiIQQnNx){UXYWxOERxW = true;}
      else if(oLgiIQQnNx == QoEYTKiSor){Nocppbcazz = true;}
      if(LyMJVpOVSQ == ABrlkEZqda){OtfhegGMDw = true;}
      else if(ABrlkEZqda == LyMJVpOVSQ){dIKiPcPTkQ = true;}
      if(sSpabHrcOi == sNehDbMBya){QbPWmqKQLE = true;}
      else if(sNehDbMBya == sSpabHrcOi){dbYYfmQIUj = true;}
      if(fPVrNIwYps == VjPoUPfxDL){HxTUbcyleT = true;}
      else if(VjPoUPfxDL == fPVrNIwYps){GuxblByhwe = true;}
      if(XmUrpRfdwD == SNBrOHaprV){ZhMQfmAirY = true;}
      if(GwNGCyzcwM == rrjFCagzef){wKKVhsHBiG = true;}
      if(SGDGLucUwN == EPpmaPlCQV){EnGrOQZLGB = true;}
      while(SNBrOHaprV == XmUrpRfdwD){TLzmDMkUIl = true;}
      while(rrjFCagzef == rrjFCagzef){WGijklPEJC = true;}
      while(EPpmaPlCQV == EPpmaPlCQV){LUGPriLhwO = true;}
      if(XcmSIeMlSw == true){XcmSIeMlSw = false;}
      if(BWIcidzKmt == true){BWIcidzKmt = false;}
      if(hgRWGDXORy == true){hgRWGDXORy = false;}
      if(UXYWxOERxW == true){UXYWxOERxW = false;}
      if(OtfhegGMDw == true){OtfhegGMDw = false;}
      if(QbPWmqKQLE == true){QbPWmqKQLE = false;}
      if(HxTUbcyleT == true){HxTUbcyleT = false;}
      if(ZhMQfmAirY == true){ZhMQfmAirY = false;}
      if(wKKVhsHBiG == true){wKKVhsHBiG = false;}
      if(EnGrOQZLGB == true){EnGrOQZLGB = false;}
      if(iUgjVhOzqz == true){iUgjVhOzqz = false;}
      if(paXlHxmylh == true){paXlHxmylh = false;}
      if(UwDYPlaTBO == true){UwDYPlaTBO = false;}
      if(Nocppbcazz == true){Nocppbcazz = false;}
      if(dIKiPcPTkQ == true){dIKiPcPTkQ = false;}
      if(dbYYfmQIUj == true){dbYYfmQIUj = false;}
      if(GuxblByhwe == true){GuxblByhwe = false;}
      if(TLzmDMkUIl == true){TLzmDMkUIl = false;}
      if(WGijklPEJC == true){WGijklPEJC = false;}
      if(LUGPriLhwO == true){LUGPriLhwO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HTODOZNVGU
{ 
  void AgGsaqHYCc()
  { 
      bool GBEXJIuZqw = false;
      bool XWwaKBeiyF = false;
      bool QNaWLHXMBt = false;
      bool gmwWkOueba = false;
      bool GRgpogpMJI = false;
      bool UjuLZsahLB = false;
      bool kiYxOkaZpw = false;
      bool GAGWyzgjge = false;
      bool RKCsYxrkwq = false;
      bool mNSapXsiaE = false;
      bool GQWNBUcXMa = false;
      bool LpAgjZfeXR = false;
      bool rocyIsgfga = false;
      bool FxIbXAmnrE = false;
      bool TTXVfxMkpP = false;
      bool qNKJMQnYEI = false;
      bool mxplUNgYJj = false;
      bool mrmSxXQGSL = false;
      bool gwoRiqmzPG = false;
      bool MOjjRVdkAR = false;
      string BsItuzMaxz;
      string kzcPlOIupx;
      string VYWsKdoluX;
      string PxggPLZbKE;
      string JkjxYeRWdt;
      string WJxWWcVPiR;
      string JZeYinRuAa;
      string ogjlmkoYTf;
      string LSIBBGzKJm;
      string pKrsujGKOk;
      string MWWCFoYLjl;
      string mwwDFqQcXb;
      string nHkMkdnqpC;
      string eeKiSowFwL;
      string hnaXzsOonE;
      string TcllwEkJRa;
      string BhUgHIlMjP;
      string tKgLtAgNNq;
      string PzCliCrXlN;
      string ElmUKASsQp;
      if(BsItuzMaxz == MWWCFoYLjl){GBEXJIuZqw = true;}
      else if(MWWCFoYLjl == BsItuzMaxz){GQWNBUcXMa = true;}
      if(kzcPlOIupx == mwwDFqQcXb){XWwaKBeiyF = true;}
      else if(mwwDFqQcXb == kzcPlOIupx){LpAgjZfeXR = true;}
      if(VYWsKdoluX == nHkMkdnqpC){QNaWLHXMBt = true;}
      else if(nHkMkdnqpC == VYWsKdoluX){rocyIsgfga = true;}
      if(PxggPLZbKE == eeKiSowFwL){gmwWkOueba = true;}
      else if(eeKiSowFwL == PxggPLZbKE){FxIbXAmnrE = true;}
      if(JkjxYeRWdt == hnaXzsOonE){GRgpogpMJI = true;}
      else if(hnaXzsOonE == JkjxYeRWdt){TTXVfxMkpP = true;}
      if(WJxWWcVPiR == TcllwEkJRa){UjuLZsahLB = true;}
      else if(TcllwEkJRa == WJxWWcVPiR){qNKJMQnYEI = true;}
      if(JZeYinRuAa == BhUgHIlMjP){kiYxOkaZpw = true;}
      else if(BhUgHIlMjP == JZeYinRuAa){mxplUNgYJj = true;}
      if(ogjlmkoYTf == tKgLtAgNNq){GAGWyzgjge = true;}
      if(LSIBBGzKJm == PzCliCrXlN){RKCsYxrkwq = true;}
      if(pKrsujGKOk == ElmUKASsQp){mNSapXsiaE = true;}
      while(tKgLtAgNNq == ogjlmkoYTf){mrmSxXQGSL = true;}
      while(PzCliCrXlN == PzCliCrXlN){gwoRiqmzPG = true;}
      while(ElmUKASsQp == ElmUKASsQp){MOjjRVdkAR = true;}
      if(GBEXJIuZqw == true){GBEXJIuZqw = false;}
      if(XWwaKBeiyF == true){XWwaKBeiyF = false;}
      if(QNaWLHXMBt == true){QNaWLHXMBt = false;}
      if(gmwWkOueba == true){gmwWkOueba = false;}
      if(GRgpogpMJI == true){GRgpogpMJI = false;}
      if(UjuLZsahLB == true){UjuLZsahLB = false;}
      if(kiYxOkaZpw == true){kiYxOkaZpw = false;}
      if(GAGWyzgjge == true){GAGWyzgjge = false;}
      if(RKCsYxrkwq == true){RKCsYxrkwq = false;}
      if(mNSapXsiaE == true){mNSapXsiaE = false;}
      if(GQWNBUcXMa == true){GQWNBUcXMa = false;}
      if(LpAgjZfeXR == true){LpAgjZfeXR = false;}
      if(rocyIsgfga == true){rocyIsgfga = false;}
      if(FxIbXAmnrE == true){FxIbXAmnrE = false;}
      if(TTXVfxMkpP == true){TTXVfxMkpP = false;}
      if(qNKJMQnYEI == true){qNKJMQnYEI = false;}
      if(mxplUNgYJj == true){mxplUNgYJj = false;}
      if(mrmSxXQGSL == true){mrmSxXQGSL = false;}
      if(gwoRiqmzPG == true){gwoRiqmzPG = false;}
      if(MOjjRVdkAR == true){MOjjRVdkAR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EQQUSMITJI
{ 
  void kObRybGIey()
  { 
      bool tRVPnZqcTa = false;
      bool BcqVmOYBag = false;
      bool BuVpUXjZJt = false;
      bool YwQPQoJwtE = false;
      bool pQYbcANOkt = false;
      bool ftCFNywftP = false;
      bool pQSZCELaEy = false;
      bool EcGWpkWtMT = false;
      bool JUoPNdsLBS = false;
      bool scBdOYyzZX = false;
      bool omJlpDnfOc = false;
      bool bCSZFUbDLX = false;
      bool KAYlFaacIQ = false;
      bool mWToeWLCZK = false;
      bool pNwYppKaYt = false;
      bool xtmBMnOWgO = false;
      bool bKWypEhdti = false;
      bool IYcBhwDAuO = false;
      bool QAEOSriSbq = false;
      bool HnVKheqyhl = false;
      string DHkVVrgBPF;
      string ocnauCUYrW;
      string QNeNDStAVY;
      string LXCzlOmgaU;
      string OlHFPLYDHI;
      string EJHmOpcWRD;
      string xfepsRZnnf;
      string OmxXHdFZyr;
      string tqsNUCPPkw;
      string lPPWWhHQLy;
      string ljOasRLjej;
      string jDYZIFmRVq;
      string BKDrtyWZAZ;
      string WoNzFJbRTD;
      string qfjALiqpOR;
      string uouUwbfWgu;
      string tkjFNuoYTy;
      string cUySAUaDfK;
      string HfLhdgssDd;
      string dFkXIFwdlP;
      if(DHkVVrgBPF == ljOasRLjej){tRVPnZqcTa = true;}
      else if(ljOasRLjej == DHkVVrgBPF){omJlpDnfOc = true;}
      if(ocnauCUYrW == jDYZIFmRVq){BcqVmOYBag = true;}
      else if(jDYZIFmRVq == ocnauCUYrW){bCSZFUbDLX = true;}
      if(QNeNDStAVY == BKDrtyWZAZ){BuVpUXjZJt = true;}
      else if(BKDrtyWZAZ == QNeNDStAVY){KAYlFaacIQ = true;}
      if(LXCzlOmgaU == WoNzFJbRTD){YwQPQoJwtE = true;}
      else if(WoNzFJbRTD == LXCzlOmgaU){mWToeWLCZK = true;}
      if(OlHFPLYDHI == qfjALiqpOR){pQYbcANOkt = true;}
      else if(qfjALiqpOR == OlHFPLYDHI){pNwYppKaYt = true;}
      if(EJHmOpcWRD == uouUwbfWgu){ftCFNywftP = true;}
      else if(uouUwbfWgu == EJHmOpcWRD){xtmBMnOWgO = true;}
      if(xfepsRZnnf == tkjFNuoYTy){pQSZCELaEy = true;}
      else if(tkjFNuoYTy == xfepsRZnnf){bKWypEhdti = true;}
      if(OmxXHdFZyr == cUySAUaDfK){EcGWpkWtMT = true;}
      if(tqsNUCPPkw == HfLhdgssDd){JUoPNdsLBS = true;}
      if(lPPWWhHQLy == dFkXIFwdlP){scBdOYyzZX = true;}
      while(cUySAUaDfK == OmxXHdFZyr){IYcBhwDAuO = true;}
      while(HfLhdgssDd == HfLhdgssDd){QAEOSriSbq = true;}
      while(dFkXIFwdlP == dFkXIFwdlP){HnVKheqyhl = true;}
      if(tRVPnZqcTa == true){tRVPnZqcTa = false;}
      if(BcqVmOYBag == true){BcqVmOYBag = false;}
      if(BuVpUXjZJt == true){BuVpUXjZJt = false;}
      if(YwQPQoJwtE == true){YwQPQoJwtE = false;}
      if(pQYbcANOkt == true){pQYbcANOkt = false;}
      if(ftCFNywftP == true){ftCFNywftP = false;}
      if(pQSZCELaEy == true){pQSZCELaEy = false;}
      if(EcGWpkWtMT == true){EcGWpkWtMT = false;}
      if(JUoPNdsLBS == true){JUoPNdsLBS = false;}
      if(scBdOYyzZX == true){scBdOYyzZX = false;}
      if(omJlpDnfOc == true){omJlpDnfOc = false;}
      if(bCSZFUbDLX == true){bCSZFUbDLX = false;}
      if(KAYlFaacIQ == true){KAYlFaacIQ = false;}
      if(mWToeWLCZK == true){mWToeWLCZK = false;}
      if(pNwYppKaYt == true){pNwYppKaYt = false;}
      if(xtmBMnOWgO == true){xtmBMnOWgO = false;}
      if(bKWypEhdti == true){bKWypEhdti = false;}
      if(IYcBhwDAuO == true){IYcBhwDAuO = false;}
      if(QAEOSriSbq == true){QAEOSriSbq = false;}
      if(HnVKheqyhl == true){HnVKheqyhl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VKLAPSMDRS
{ 
  void fpugmxcift()
  { 
      bool hwBipJBWJO = false;
      bool pOUUakCqbu = false;
      bool FZWVeRcVRD = false;
      bool hqtscIiMSd = false;
      bool llQKwjfHxm = false;
      bool zAwxbHYfDY = false;
      bool gfFFgzTaqS = false;
      bool BoXxISJLZu = false;
      bool kVXdEguxQV = false;
      bool iDJtxFgLcw = false;
      bool PEPekJcynJ = false;
      bool yMFImLHaAA = false;
      bool EWKViyfdAD = false;
      bool kxhcegFssu = false;
      bool EwJGWVxAHk = false;
      bool yGKcrstsum = false;
      bool czykYAebdF = false;
      bool FNhEuHMDyN = false;
      bool AfVOEdlEkl = false;
      bool mLyFRFxYhW = false;
      string OqfznUQifX;
      string mWrtqihlku;
      string rJqBmqqXHk;
      string LLGjmYhYmz;
      string RSqggeYarc;
      string ZEDwqEAeLw;
      string dratMaQHGS;
      string AIylcZSJTI;
      string RPfeKGIJsi;
      string YDNpUZqwUF;
      string OQTYbRGQTR;
      string kpKCdNLwiF;
      string RGOXsxuHQC;
      string hWoNtAwHCs;
      string ArpbxirKLH;
      string OtMOnHCuee;
      string VyAQiOAwIc;
      string REsoFZQmaK;
      string EkuInmJZZl;
      string yAbXXBqYrh;
      if(OqfznUQifX == OQTYbRGQTR){hwBipJBWJO = true;}
      else if(OQTYbRGQTR == OqfznUQifX){PEPekJcynJ = true;}
      if(mWrtqihlku == kpKCdNLwiF){pOUUakCqbu = true;}
      else if(kpKCdNLwiF == mWrtqihlku){yMFImLHaAA = true;}
      if(rJqBmqqXHk == RGOXsxuHQC){FZWVeRcVRD = true;}
      else if(RGOXsxuHQC == rJqBmqqXHk){EWKViyfdAD = true;}
      if(LLGjmYhYmz == hWoNtAwHCs){hqtscIiMSd = true;}
      else if(hWoNtAwHCs == LLGjmYhYmz){kxhcegFssu = true;}
      if(RSqggeYarc == ArpbxirKLH){llQKwjfHxm = true;}
      else if(ArpbxirKLH == RSqggeYarc){EwJGWVxAHk = true;}
      if(ZEDwqEAeLw == OtMOnHCuee){zAwxbHYfDY = true;}
      else if(OtMOnHCuee == ZEDwqEAeLw){yGKcrstsum = true;}
      if(dratMaQHGS == VyAQiOAwIc){gfFFgzTaqS = true;}
      else if(VyAQiOAwIc == dratMaQHGS){czykYAebdF = true;}
      if(AIylcZSJTI == REsoFZQmaK){BoXxISJLZu = true;}
      if(RPfeKGIJsi == EkuInmJZZl){kVXdEguxQV = true;}
      if(YDNpUZqwUF == yAbXXBqYrh){iDJtxFgLcw = true;}
      while(REsoFZQmaK == AIylcZSJTI){FNhEuHMDyN = true;}
      while(EkuInmJZZl == EkuInmJZZl){AfVOEdlEkl = true;}
      while(yAbXXBqYrh == yAbXXBqYrh){mLyFRFxYhW = true;}
      if(hwBipJBWJO == true){hwBipJBWJO = false;}
      if(pOUUakCqbu == true){pOUUakCqbu = false;}
      if(FZWVeRcVRD == true){FZWVeRcVRD = false;}
      if(hqtscIiMSd == true){hqtscIiMSd = false;}
      if(llQKwjfHxm == true){llQKwjfHxm = false;}
      if(zAwxbHYfDY == true){zAwxbHYfDY = false;}
      if(gfFFgzTaqS == true){gfFFgzTaqS = false;}
      if(BoXxISJLZu == true){BoXxISJLZu = false;}
      if(kVXdEguxQV == true){kVXdEguxQV = false;}
      if(iDJtxFgLcw == true){iDJtxFgLcw = false;}
      if(PEPekJcynJ == true){PEPekJcynJ = false;}
      if(yMFImLHaAA == true){yMFImLHaAA = false;}
      if(EWKViyfdAD == true){EWKViyfdAD = false;}
      if(kxhcegFssu == true){kxhcegFssu = false;}
      if(EwJGWVxAHk == true){EwJGWVxAHk = false;}
      if(yGKcrstsum == true){yGKcrstsum = false;}
      if(czykYAebdF == true){czykYAebdF = false;}
      if(FNhEuHMDyN == true){FNhEuHMDyN = false;}
      if(AfVOEdlEkl == true){AfVOEdlEkl = false;}
      if(mLyFRFxYhW == true){mLyFRFxYhW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UPTTMHIPCS
{ 
  void bfIJHrcjcU()
  { 
      bool eHiSbgUCqC = false;
      bool VdSRbmCSeC = false;
      bool gxHcfdnrLJ = false;
      bool akTArwjSIF = false;
      bool AekOOFIXQS = false;
      bool SDBPHhzFlx = false;
      bool sbqhbkJRZf = false;
      bool CjKZCBMsNa = false;
      bool VQbrqWjEsK = false;
      bool wdfKMXnCld = false;
      bool upyjQhsaNF = false;
      bool UGrLbcAyqF = false;
      bool AFYPiXEzNd = false;
      bool MJGjeeSqbJ = false;
      bool dIqmoplTij = false;
      bool XoLgcpRhBs = false;
      bool csNisKAHgw = false;
      bool KJWgaqOkZr = false;
      bool kjQdGXyYGn = false;
      bool NjohfjuHte = false;
      string eMQaSXbKVA;
      string eeuBXKBens;
      string ELcjLHyWLI;
      string tJzcnPDzLx;
      string ZOLRsiMNZW;
      string YbMjnSjgPL;
      string ZFyNGUfRNI;
      string GBTpSpAKpb;
      string ujwojRxPnV;
      string eWjzXUPxLX;
      string DtARPWIVQy;
      string RZpmQoIJdn;
      string XPcrcjQTSy;
      string aCzRYAjeYM;
      string JaypDFfxih;
      string LFTWAmQHof;
      string GnDRXPZYNP;
      string FdkRexRmoW;
      string DTkjmUhbRk;
      string iborFUWfSn;
      if(eMQaSXbKVA == DtARPWIVQy){eHiSbgUCqC = true;}
      else if(DtARPWIVQy == eMQaSXbKVA){upyjQhsaNF = true;}
      if(eeuBXKBens == RZpmQoIJdn){VdSRbmCSeC = true;}
      else if(RZpmQoIJdn == eeuBXKBens){UGrLbcAyqF = true;}
      if(ELcjLHyWLI == XPcrcjQTSy){gxHcfdnrLJ = true;}
      else if(XPcrcjQTSy == ELcjLHyWLI){AFYPiXEzNd = true;}
      if(tJzcnPDzLx == aCzRYAjeYM){akTArwjSIF = true;}
      else if(aCzRYAjeYM == tJzcnPDzLx){MJGjeeSqbJ = true;}
      if(ZOLRsiMNZW == JaypDFfxih){AekOOFIXQS = true;}
      else if(JaypDFfxih == ZOLRsiMNZW){dIqmoplTij = true;}
      if(YbMjnSjgPL == LFTWAmQHof){SDBPHhzFlx = true;}
      else if(LFTWAmQHof == YbMjnSjgPL){XoLgcpRhBs = true;}
      if(ZFyNGUfRNI == GnDRXPZYNP){sbqhbkJRZf = true;}
      else if(GnDRXPZYNP == ZFyNGUfRNI){csNisKAHgw = true;}
      if(GBTpSpAKpb == FdkRexRmoW){CjKZCBMsNa = true;}
      if(ujwojRxPnV == DTkjmUhbRk){VQbrqWjEsK = true;}
      if(eWjzXUPxLX == iborFUWfSn){wdfKMXnCld = true;}
      while(FdkRexRmoW == GBTpSpAKpb){KJWgaqOkZr = true;}
      while(DTkjmUhbRk == DTkjmUhbRk){kjQdGXyYGn = true;}
      while(iborFUWfSn == iborFUWfSn){NjohfjuHte = true;}
      if(eHiSbgUCqC == true){eHiSbgUCqC = false;}
      if(VdSRbmCSeC == true){VdSRbmCSeC = false;}
      if(gxHcfdnrLJ == true){gxHcfdnrLJ = false;}
      if(akTArwjSIF == true){akTArwjSIF = false;}
      if(AekOOFIXQS == true){AekOOFIXQS = false;}
      if(SDBPHhzFlx == true){SDBPHhzFlx = false;}
      if(sbqhbkJRZf == true){sbqhbkJRZf = false;}
      if(CjKZCBMsNa == true){CjKZCBMsNa = false;}
      if(VQbrqWjEsK == true){VQbrqWjEsK = false;}
      if(wdfKMXnCld == true){wdfKMXnCld = false;}
      if(upyjQhsaNF == true){upyjQhsaNF = false;}
      if(UGrLbcAyqF == true){UGrLbcAyqF = false;}
      if(AFYPiXEzNd == true){AFYPiXEzNd = false;}
      if(MJGjeeSqbJ == true){MJGjeeSqbJ = false;}
      if(dIqmoplTij == true){dIqmoplTij = false;}
      if(XoLgcpRhBs == true){XoLgcpRhBs = false;}
      if(csNisKAHgw == true){csNisKAHgw = false;}
      if(KJWgaqOkZr == true){KJWgaqOkZr = false;}
      if(kjQdGXyYGn == true){kjQdGXyYGn = false;}
      if(NjohfjuHte == true){NjohfjuHte = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DXJVGFUPKT
{ 
  void uhUAslDDji()
  { 
      bool qsTkPmxEYB = false;
      bool qibPKUklsq = false;
      bool QdBGkYYfNk = false;
      bool VBwfYjYbnP = false;
      bool dymjYZygVe = false;
      bool cVArWNqNAp = false;
      bool NRpmfolwpZ = false;
      bool uJycMRpRgK = false;
      bool arJhIzBEJK = false;
      bool sKaxCMHAEj = false;
      bool mCqujSXWfE = false;
      bool XZgoPUHIef = false;
      bool mhlegjiAZA = false;
      bool KpNxXYBNyo = false;
      bool beYFmSdkgh = false;
      bool EyUXwEPLOz = false;
      bool jWwetgMiRq = false;
      bool TtKoDIJgqN = false;
      bool GySruLUoBS = false;
      bool JozzEFhsKG = false;
      string GMYlQrAPAC;
      string wLxSGAPkDi;
      string gBSCkWesMK;
      string mRaBzAGPry;
      string OykzhJwnkr;
      string xiMbpEsWAs;
      string NHDpPdkuTF;
      string szrEThQTTb;
      string ZqIUMDEyLt;
      string HiPzkHtujD;
      string YAUeyyqIIH;
      string nZDYTVzicL;
      string ZljYyJjsSL;
      string nUjPCYVcVO;
      string MwpDFgfpfP;
      string ILSXdlPufn;
      string OyowTSomVt;
      string zVNNzcugSQ;
      string csMDCbCLkP;
      string JawgANHsjm;
      if(GMYlQrAPAC == YAUeyyqIIH){qsTkPmxEYB = true;}
      else if(YAUeyyqIIH == GMYlQrAPAC){mCqujSXWfE = true;}
      if(wLxSGAPkDi == nZDYTVzicL){qibPKUklsq = true;}
      else if(nZDYTVzicL == wLxSGAPkDi){XZgoPUHIef = true;}
      if(gBSCkWesMK == ZljYyJjsSL){QdBGkYYfNk = true;}
      else if(ZljYyJjsSL == gBSCkWesMK){mhlegjiAZA = true;}
      if(mRaBzAGPry == nUjPCYVcVO){VBwfYjYbnP = true;}
      else if(nUjPCYVcVO == mRaBzAGPry){KpNxXYBNyo = true;}
      if(OykzhJwnkr == MwpDFgfpfP){dymjYZygVe = true;}
      else if(MwpDFgfpfP == OykzhJwnkr){beYFmSdkgh = true;}
      if(xiMbpEsWAs == ILSXdlPufn){cVArWNqNAp = true;}
      else if(ILSXdlPufn == xiMbpEsWAs){EyUXwEPLOz = true;}
      if(NHDpPdkuTF == OyowTSomVt){NRpmfolwpZ = true;}
      else if(OyowTSomVt == NHDpPdkuTF){jWwetgMiRq = true;}
      if(szrEThQTTb == zVNNzcugSQ){uJycMRpRgK = true;}
      if(ZqIUMDEyLt == csMDCbCLkP){arJhIzBEJK = true;}
      if(HiPzkHtujD == JawgANHsjm){sKaxCMHAEj = true;}
      while(zVNNzcugSQ == szrEThQTTb){TtKoDIJgqN = true;}
      while(csMDCbCLkP == csMDCbCLkP){GySruLUoBS = true;}
      while(JawgANHsjm == JawgANHsjm){JozzEFhsKG = true;}
      if(qsTkPmxEYB == true){qsTkPmxEYB = false;}
      if(qibPKUklsq == true){qibPKUklsq = false;}
      if(QdBGkYYfNk == true){QdBGkYYfNk = false;}
      if(VBwfYjYbnP == true){VBwfYjYbnP = false;}
      if(dymjYZygVe == true){dymjYZygVe = false;}
      if(cVArWNqNAp == true){cVArWNqNAp = false;}
      if(NRpmfolwpZ == true){NRpmfolwpZ = false;}
      if(uJycMRpRgK == true){uJycMRpRgK = false;}
      if(arJhIzBEJK == true){arJhIzBEJK = false;}
      if(sKaxCMHAEj == true){sKaxCMHAEj = false;}
      if(mCqujSXWfE == true){mCqujSXWfE = false;}
      if(XZgoPUHIef == true){XZgoPUHIef = false;}
      if(mhlegjiAZA == true){mhlegjiAZA = false;}
      if(KpNxXYBNyo == true){KpNxXYBNyo = false;}
      if(beYFmSdkgh == true){beYFmSdkgh = false;}
      if(EyUXwEPLOz == true){EyUXwEPLOz = false;}
      if(jWwetgMiRq == true){jWwetgMiRq = false;}
      if(TtKoDIJgqN == true){TtKoDIJgqN = false;}
      if(GySruLUoBS == true){GySruLUoBS = false;}
      if(JozzEFhsKG == true){JozzEFhsKG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IRBCUPXTTT
{ 
  void rWGpGWBnoQ()
  { 
      bool XpNAUDhlVc = false;
      bool jyHYRcjRwC = false;
      bool MUfLViHjrn = false;
      bool AKGrGXofrj = false;
      bool NNQMOLYyVN = false;
      bool AdzAVDJCek = false;
      bool wyshcZqORs = false;
      bool mEYMozDTwK = false;
      bool JINenVLFVD = false;
      bool OmBHmOTijo = false;
      bool UJfbZwElLW = false;
      bool zpFTamjOsH = false;
      bool NksOeADRYZ = false;
      bool fUiHpAclEr = false;
      bool QYtzDXggfA = false;
      bool dFocaiQRwZ = false;
      bool smNkqeGyda = false;
      bool KyJBpopsKG = false;
      bool SVlYuZeGfG = false;
      bool iLoezdLIIY = false;
      string rPeuEscacF;
      string UaSPuRAIom;
      string VLXhYTljGq;
      string CtAFLNtxPY;
      string eTNWWDhMwd;
      string LXqNCgqwWj;
      string GsUkDZZNDg;
      string XDsPHCyBLU;
      string lZnbeeClCe;
      string WxaeRlzbSw;
      string dTIOGIdbGA;
      string hpkBygEsGY;
      string WmLYKZbNxV;
      string CVhOpRQZUW;
      string AafBwfLYgk;
      string hGVtYqIjDg;
      string fQdjyMIVKf;
      string QdXiXwGJbe;
      string ODgMnuzmoz;
      string JgWnpjwuDi;
      if(rPeuEscacF == dTIOGIdbGA){XpNAUDhlVc = true;}
      else if(dTIOGIdbGA == rPeuEscacF){UJfbZwElLW = true;}
      if(UaSPuRAIom == hpkBygEsGY){jyHYRcjRwC = true;}
      else if(hpkBygEsGY == UaSPuRAIom){zpFTamjOsH = true;}
      if(VLXhYTljGq == WmLYKZbNxV){MUfLViHjrn = true;}
      else if(WmLYKZbNxV == VLXhYTljGq){NksOeADRYZ = true;}
      if(CtAFLNtxPY == CVhOpRQZUW){AKGrGXofrj = true;}
      else if(CVhOpRQZUW == CtAFLNtxPY){fUiHpAclEr = true;}
      if(eTNWWDhMwd == AafBwfLYgk){NNQMOLYyVN = true;}
      else if(AafBwfLYgk == eTNWWDhMwd){QYtzDXggfA = true;}
      if(LXqNCgqwWj == hGVtYqIjDg){AdzAVDJCek = true;}
      else if(hGVtYqIjDg == LXqNCgqwWj){dFocaiQRwZ = true;}
      if(GsUkDZZNDg == fQdjyMIVKf){wyshcZqORs = true;}
      else if(fQdjyMIVKf == GsUkDZZNDg){smNkqeGyda = true;}
      if(XDsPHCyBLU == QdXiXwGJbe){mEYMozDTwK = true;}
      if(lZnbeeClCe == ODgMnuzmoz){JINenVLFVD = true;}
      if(WxaeRlzbSw == JgWnpjwuDi){OmBHmOTijo = true;}
      while(QdXiXwGJbe == XDsPHCyBLU){KyJBpopsKG = true;}
      while(ODgMnuzmoz == ODgMnuzmoz){SVlYuZeGfG = true;}
      while(JgWnpjwuDi == JgWnpjwuDi){iLoezdLIIY = true;}
      if(XpNAUDhlVc == true){XpNAUDhlVc = false;}
      if(jyHYRcjRwC == true){jyHYRcjRwC = false;}
      if(MUfLViHjrn == true){MUfLViHjrn = false;}
      if(AKGrGXofrj == true){AKGrGXofrj = false;}
      if(NNQMOLYyVN == true){NNQMOLYyVN = false;}
      if(AdzAVDJCek == true){AdzAVDJCek = false;}
      if(wyshcZqORs == true){wyshcZqORs = false;}
      if(mEYMozDTwK == true){mEYMozDTwK = false;}
      if(JINenVLFVD == true){JINenVLFVD = false;}
      if(OmBHmOTijo == true){OmBHmOTijo = false;}
      if(UJfbZwElLW == true){UJfbZwElLW = false;}
      if(zpFTamjOsH == true){zpFTamjOsH = false;}
      if(NksOeADRYZ == true){NksOeADRYZ = false;}
      if(fUiHpAclEr == true){fUiHpAclEr = false;}
      if(QYtzDXggfA == true){QYtzDXggfA = false;}
      if(dFocaiQRwZ == true){dFocaiQRwZ = false;}
      if(smNkqeGyda == true){smNkqeGyda = false;}
      if(KyJBpopsKG == true){KyJBpopsKG = false;}
      if(SVlYuZeGfG == true){SVlYuZeGfG = false;}
      if(iLoezdLIIY == true){iLoezdLIIY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SCULWKYANY
{ 
  void gVFMymWPpo()
  { 
      bool GyICshtWpZ = false;
      bool WhjeMxQNdW = false;
      bool ItcPQKNShR = false;
      bool glFKpbZQyW = false;
      bool dEtoRXVAdP = false;
      bool sLhDcMUslh = false;
      bool TboXrjcYoj = false;
      bool WAOHsDznxr = false;
      bool oNnSXUDBgc = false;
      bool GgePDBPVwh = false;
      bool uwLtsswaKY = false;
      bool MgwssGmVAW = false;
      bool fbqLdoVyDq = false;
      bool ndrPxrCtYe = false;
      bool XcpHQZkkWx = false;
      bool OsVYBSEAQD = false;
      bool XyWTjhofwA = false;
      bool EsxUyDlitD = false;
      bool EkbGcuISNd = false;
      bool mCdVHZFWWh = false;
      string wRzkWgjtdR;
      string jjWswQoIMr;
      string aRmBwswWaU;
      string RKeecwYQwx;
      string mJQqpVINIt;
      string zqXTmedxoc;
      string kNTJzYFrPA;
      string qXMOFRBuLa;
      string kiOfUamKqy;
      string SbbSMZpGrQ;
      string PPxICbeIOV;
      string dhlOrCzmnY;
      string ktBQgPwsCe;
      string atDtKUkGds;
      string wewUUkoMZK;
      string aDSSfVOfam;
      string fkFitidqEW;
      string QsJucGyfww;
      string ZiTrEXajOo;
      string GFepMKYMak;
      if(wRzkWgjtdR == PPxICbeIOV){GyICshtWpZ = true;}
      else if(PPxICbeIOV == wRzkWgjtdR){uwLtsswaKY = true;}
      if(jjWswQoIMr == dhlOrCzmnY){WhjeMxQNdW = true;}
      else if(dhlOrCzmnY == jjWswQoIMr){MgwssGmVAW = true;}
      if(aRmBwswWaU == ktBQgPwsCe){ItcPQKNShR = true;}
      else if(ktBQgPwsCe == aRmBwswWaU){fbqLdoVyDq = true;}
      if(RKeecwYQwx == atDtKUkGds){glFKpbZQyW = true;}
      else if(atDtKUkGds == RKeecwYQwx){ndrPxrCtYe = true;}
      if(mJQqpVINIt == wewUUkoMZK){dEtoRXVAdP = true;}
      else if(wewUUkoMZK == mJQqpVINIt){XcpHQZkkWx = true;}
      if(zqXTmedxoc == aDSSfVOfam){sLhDcMUslh = true;}
      else if(aDSSfVOfam == zqXTmedxoc){OsVYBSEAQD = true;}
      if(kNTJzYFrPA == fkFitidqEW){TboXrjcYoj = true;}
      else if(fkFitidqEW == kNTJzYFrPA){XyWTjhofwA = true;}
      if(qXMOFRBuLa == QsJucGyfww){WAOHsDznxr = true;}
      if(kiOfUamKqy == ZiTrEXajOo){oNnSXUDBgc = true;}
      if(SbbSMZpGrQ == GFepMKYMak){GgePDBPVwh = true;}
      while(QsJucGyfww == qXMOFRBuLa){EsxUyDlitD = true;}
      while(ZiTrEXajOo == ZiTrEXajOo){EkbGcuISNd = true;}
      while(GFepMKYMak == GFepMKYMak){mCdVHZFWWh = true;}
      if(GyICshtWpZ == true){GyICshtWpZ = false;}
      if(WhjeMxQNdW == true){WhjeMxQNdW = false;}
      if(ItcPQKNShR == true){ItcPQKNShR = false;}
      if(glFKpbZQyW == true){glFKpbZQyW = false;}
      if(dEtoRXVAdP == true){dEtoRXVAdP = false;}
      if(sLhDcMUslh == true){sLhDcMUslh = false;}
      if(TboXrjcYoj == true){TboXrjcYoj = false;}
      if(WAOHsDznxr == true){WAOHsDznxr = false;}
      if(oNnSXUDBgc == true){oNnSXUDBgc = false;}
      if(GgePDBPVwh == true){GgePDBPVwh = false;}
      if(uwLtsswaKY == true){uwLtsswaKY = false;}
      if(MgwssGmVAW == true){MgwssGmVAW = false;}
      if(fbqLdoVyDq == true){fbqLdoVyDq = false;}
      if(ndrPxrCtYe == true){ndrPxrCtYe = false;}
      if(XcpHQZkkWx == true){XcpHQZkkWx = false;}
      if(OsVYBSEAQD == true){OsVYBSEAQD = false;}
      if(XyWTjhofwA == true){XyWTjhofwA = false;}
      if(EsxUyDlitD == true){EsxUyDlitD = false;}
      if(EkbGcuISNd == true){EkbGcuISNd = false;}
      if(mCdVHZFWWh == true){mCdVHZFWWh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QNTBGGYFTQ
{ 
  void oYzZLwMCPP()
  { 
      bool tLJhIKmSMe = false;
      bool fpezwhOqkk = false;
      bool BtzUqkfspq = false;
      bool hegMiGkTGA = false;
      bool RnmVmxooyT = false;
      bool wthxdAMoqX = false;
      bool escVwAJRQp = false;
      bool wtkjSNHdgs = false;
      bool wquVunxiii = false;
      bool swciVXLRYm = false;
      bool nWXIWBJxeP = false;
      bool riHxbmyGZI = false;
      bool DaihwARCOt = false;
      bool CpEsFYSlzt = false;
      bool dzDTpKoeGh = false;
      bool ZEqPjMnpLW = false;
      bool iHijNCdNrC = false;
      bool UMHfdDWOqk = false;
      bool LmufUxzoJr = false;
      bool kbZbKWQSFn = false;
      string axjYhoYyUV;
      string zEQfgWmEwR;
      string sDgUxTuarx;
      string mGpflPdLCF;
      string NiEZGGeyNm;
      string xhboiXQPbO;
      string tyFWhrOktR;
      string sbCpEKyGOp;
      string nwMFAFeAwN;
      string zNimLPcgqN;
      string rtEutVelkX;
      string ZJBlZxkAWc;
      string NNnfSerOdo;
      string hQOAxtrQKe;
      string asOYnoMxNO;
      string dcKOzdFXcP;
      string cPHwpItAne;
      string FToqBUyPrc;
      string StBPKFGABS;
      string nTnuBKlSie;
      if(axjYhoYyUV == rtEutVelkX){tLJhIKmSMe = true;}
      else if(rtEutVelkX == axjYhoYyUV){nWXIWBJxeP = true;}
      if(zEQfgWmEwR == ZJBlZxkAWc){fpezwhOqkk = true;}
      else if(ZJBlZxkAWc == zEQfgWmEwR){riHxbmyGZI = true;}
      if(sDgUxTuarx == NNnfSerOdo){BtzUqkfspq = true;}
      else if(NNnfSerOdo == sDgUxTuarx){DaihwARCOt = true;}
      if(mGpflPdLCF == hQOAxtrQKe){hegMiGkTGA = true;}
      else if(hQOAxtrQKe == mGpflPdLCF){CpEsFYSlzt = true;}
      if(NiEZGGeyNm == asOYnoMxNO){RnmVmxooyT = true;}
      else if(asOYnoMxNO == NiEZGGeyNm){dzDTpKoeGh = true;}
      if(xhboiXQPbO == dcKOzdFXcP){wthxdAMoqX = true;}
      else if(dcKOzdFXcP == xhboiXQPbO){ZEqPjMnpLW = true;}
      if(tyFWhrOktR == cPHwpItAne){escVwAJRQp = true;}
      else if(cPHwpItAne == tyFWhrOktR){iHijNCdNrC = true;}
      if(sbCpEKyGOp == FToqBUyPrc){wtkjSNHdgs = true;}
      if(nwMFAFeAwN == StBPKFGABS){wquVunxiii = true;}
      if(zNimLPcgqN == nTnuBKlSie){swciVXLRYm = true;}
      while(FToqBUyPrc == sbCpEKyGOp){UMHfdDWOqk = true;}
      while(StBPKFGABS == StBPKFGABS){LmufUxzoJr = true;}
      while(nTnuBKlSie == nTnuBKlSie){kbZbKWQSFn = true;}
      if(tLJhIKmSMe == true){tLJhIKmSMe = false;}
      if(fpezwhOqkk == true){fpezwhOqkk = false;}
      if(BtzUqkfspq == true){BtzUqkfspq = false;}
      if(hegMiGkTGA == true){hegMiGkTGA = false;}
      if(RnmVmxooyT == true){RnmVmxooyT = false;}
      if(wthxdAMoqX == true){wthxdAMoqX = false;}
      if(escVwAJRQp == true){escVwAJRQp = false;}
      if(wtkjSNHdgs == true){wtkjSNHdgs = false;}
      if(wquVunxiii == true){wquVunxiii = false;}
      if(swciVXLRYm == true){swciVXLRYm = false;}
      if(nWXIWBJxeP == true){nWXIWBJxeP = false;}
      if(riHxbmyGZI == true){riHxbmyGZI = false;}
      if(DaihwARCOt == true){DaihwARCOt = false;}
      if(CpEsFYSlzt == true){CpEsFYSlzt = false;}
      if(dzDTpKoeGh == true){dzDTpKoeGh = false;}
      if(ZEqPjMnpLW == true){ZEqPjMnpLW = false;}
      if(iHijNCdNrC == true){iHijNCdNrC = false;}
      if(UMHfdDWOqk == true){UMHfdDWOqk = false;}
      if(LmufUxzoJr == true){LmufUxzoJr = false;}
      if(kbZbKWQSFn == true){kbZbKWQSFn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WZAMJECFXL
{ 
  void afoKiFZRzn()
  { 
      bool eIsCVlWOzm = false;
      bool kRdEJRGDgp = false;
      bool HOUGTFmuIz = false;
      bool cuIGEtwJhs = false;
      bool zTUOygYyQy = false;
      bool MXHzIQnmhQ = false;
      bool zbGAJoIWAO = false;
      bool UxVnpmtFHm = false;
      bool foeKlEmJym = false;
      bool GJbQtXNTEI = false;
      bool YCxBcPCTIU = false;
      bool VhetjJwuOF = false;
      bool CyYMHLVEsS = false;
      bool ZZBzOdqchV = false;
      bool BSAcRYdgfj = false;
      bool bREzGZcjsQ = false;
      bool tyapuufefG = false;
      bool RSNsDiywui = false;
      bool gnXIpHVCsn = false;
      bool BHjQaDrJgV = false;
      string SGEtrOHDtM;
      string DYGszOtCRm;
      string MwYPjdQwKr;
      string VqMZsRioRp;
      string UtmOqUxfTa;
      string ljRntWgnKN;
      string xKrCpMLfAh;
      string eEjbSRIKXO;
      string fjcjFkYXeV;
      string jueDrJBkXe;
      string JQflwhzpVc;
      string OVPuhNgIwE;
      string mmBdxiZgiI;
      string PXmsFOEqmX;
      string liCCHNeiVe;
      string csnSqVPBnM;
      string HRHMMqiWpS;
      string IpVYSEkyWi;
      string DpLDfWiTBi;
      string yDCZPTbooQ;
      if(SGEtrOHDtM == JQflwhzpVc){eIsCVlWOzm = true;}
      else if(JQflwhzpVc == SGEtrOHDtM){YCxBcPCTIU = true;}
      if(DYGszOtCRm == OVPuhNgIwE){kRdEJRGDgp = true;}
      else if(OVPuhNgIwE == DYGszOtCRm){VhetjJwuOF = true;}
      if(MwYPjdQwKr == mmBdxiZgiI){HOUGTFmuIz = true;}
      else if(mmBdxiZgiI == MwYPjdQwKr){CyYMHLVEsS = true;}
      if(VqMZsRioRp == PXmsFOEqmX){cuIGEtwJhs = true;}
      else if(PXmsFOEqmX == VqMZsRioRp){ZZBzOdqchV = true;}
      if(UtmOqUxfTa == liCCHNeiVe){zTUOygYyQy = true;}
      else if(liCCHNeiVe == UtmOqUxfTa){BSAcRYdgfj = true;}
      if(ljRntWgnKN == csnSqVPBnM){MXHzIQnmhQ = true;}
      else if(csnSqVPBnM == ljRntWgnKN){bREzGZcjsQ = true;}
      if(xKrCpMLfAh == HRHMMqiWpS){zbGAJoIWAO = true;}
      else if(HRHMMqiWpS == xKrCpMLfAh){tyapuufefG = true;}
      if(eEjbSRIKXO == IpVYSEkyWi){UxVnpmtFHm = true;}
      if(fjcjFkYXeV == DpLDfWiTBi){foeKlEmJym = true;}
      if(jueDrJBkXe == yDCZPTbooQ){GJbQtXNTEI = true;}
      while(IpVYSEkyWi == eEjbSRIKXO){RSNsDiywui = true;}
      while(DpLDfWiTBi == DpLDfWiTBi){gnXIpHVCsn = true;}
      while(yDCZPTbooQ == yDCZPTbooQ){BHjQaDrJgV = true;}
      if(eIsCVlWOzm == true){eIsCVlWOzm = false;}
      if(kRdEJRGDgp == true){kRdEJRGDgp = false;}
      if(HOUGTFmuIz == true){HOUGTFmuIz = false;}
      if(cuIGEtwJhs == true){cuIGEtwJhs = false;}
      if(zTUOygYyQy == true){zTUOygYyQy = false;}
      if(MXHzIQnmhQ == true){MXHzIQnmhQ = false;}
      if(zbGAJoIWAO == true){zbGAJoIWAO = false;}
      if(UxVnpmtFHm == true){UxVnpmtFHm = false;}
      if(foeKlEmJym == true){foeKlEmJym = false;}
      if(GJbQtXNTEI == true){GJbQtXNTEI = false;}
      if(YCxBcPCTIU == true){YCxBcPCTIU = false;}
      if(VhetjJwuOF == true){VhetjJwuOF = false;}
      if(CyYMHLVEsS == true){CyYMHLVEsS = false;}
      if(ZZBzOdqchV == true){ZZBzOdqchV = false;}
      if(BSAcRYdgfj == true){BSAcRYdgfj = false;}
      if(bREzGZcjsQ == true){bREzGZcjsQ = false;}
      if(tyapuufefG == true){tyapuufefG = false;}
      if(RSNsDiywui == true){RSNsDiywui = false;}
      if(gnXIpHVCsn == true){gnXIpHVCsn = false;}
      if(BHjQaDrJgV == true){BHjQaDrJgV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DUQCREAHWV
{ 
  void iNxnBJZTPr()
  { 
      bool tmOgRxfgRh = false;
      bool SLWuOwkYlc = false;
      bool WESQsnnpKB = false;
      bool gNPDlttzTR = false;
      bool cGZucTQtXf = false;
      bool BYVXeoUynd = false;
      bool JpWPBFuTJU = false;
      bool ClFUzQdWmY = false;
      bool XsSdAHrqXw = false;
      bool YwKpHmjKtX = false;
      bool YxkCdPTAXO = false;
      bool KxKPFQWrPs = false;
      bool MEwMuGaOMM = false;
      bool gTcOAaIPAj = false;
      bool mqSIlbkujq = false;
      bool PqtALTAXHW = false;
      bool oEnLhpUuOe = false;
      bool HHqfGUkmaT = false;
      bool UfeUwoZbDf = false;
      bool ZkIcthCHau = false;
      string FtINiIjIVk;
      string AwburqpeQy;
      string NlzdJODYza;
      string kNMfyhCeGt;
      string iclAmDaqIC;
      string BcNIoSueET;
      string FLIuAmiuxJ;
      string oLYWOkzyqF;
      string mLPxYHzDqe;
      string mXZloWTqzA;
      string UftyNpDqsD;
      string SwmyftuLVs;
      string mfDRWRklgq;
      string RIzqkHQRih;
      string EIJmMqjbGu;
      string bIUGMobcbw;
      string FQKClKxwMY;
      string cdbmoeVQFf;
      string gIflPImrdw;
      string fnplcmxHBC;
      if(FtINiIjIVk == UftyNpDqsD){tmOgRxfgRh = true;}
      else if(UftyNpDqsD == FtINiIjIVk){YxkCdPTAXO = true;}
      if(AwburqpeQy == SwmyftuLVs){SLWuOwkYlc = true;}
      else if(SwmyftuLVs == AwburqpeQy){KxKPFQWrPs = true;}
      if(NlzdJODYza == mfDRWRklgq){WESQsnnpKB = true;}
      else if(mfDRWRklgq == NlzdJODYza){MEwMuGaOMM = true;}
      if(kNMfyhCeGt == RIzqkHQRih){gNPDlttzTR = true;}
      else if(RIzqkHQRih == kNMfyhCeGt){gTcOAaIPAj = true;}
      if(iclAmDaqIC == EIJmMqjbGu){cGZucTQtXf = true;}
      else if(EIJmMqjbGu == iclAmDaqIC){mqSIlbkujq = true;}
      if(BcNIoSueET == bIUGMobcbw){BYVXeoUynd = true;}
      else if(bIUGMobcbw == BcNIoSueET){PqtALTAXHW = true;}
      if(FLIuAmiuxJ == FQKClKxwMY){JpWPBFuTJU = true;}
      else if(FQKClKxwMY == FLIuAmiuxJ){oEnLhpUuOe = true;}
      if(oLYWOkzyqF == cdbmoeVQFf){ClFUzQdWmY = true;}
      if(mLPxYHzDqe == gIflPImrdw){XsSdAHrqXw = true;}
      if(mXZloWTqzA == fnplcmxHBC){YwKpHmjKtX = true;}
      while(cdbmoeVQFf == oLYWOkzyqF){HHqfGUkmaT = true;}
      while(gIflPImrdw == gIflPImrdw){UfeUwoZbDf = true;}
      while(fnplcmxHBC == fnplcmxHBC){ZkIcthCHau = true;}
      if(tmOgRxfgRh == true){tmOgRxfgRh = false;}
      if(SLWuOwkYlc == true){SLWuOwkYlc = false;}
      if(WESQsnnpKB == true){WESQsnnpKB = false;}
      if(gNPDlttzTR == true){gNPDlttzTR = false;}
      if(cGZucTQtXf == true){cGZucTQtXf = false;}
      if(BYVXeoUynd == true){BYVXeoUynd = false;}
      if(JpWPBFuTJU == true){JpWPBFuTJU = false;}
      if(ClFUzQdWmY == true){ClFUzQdWmY = false;}
      if(XsSdAHrqXw == true){XsSdAHrqXw = false;}
      if(YwKpHmjKtX == true){YwKpHmjKtX = false;}
      if(YxkCdPTAXO == true){YxkCdPTAXO = false;}
      if(KxKPFQWrPs == true){KxKPFQWrPs = false;}
      if(MEwMuGaOMM == true){MEwMuGaOMM = false;}
      if(gTcOAaIPAj == true){gTcOAaIPAj = false;}
      if(mqSIlbkujq == true){mqSIlbkujq = false;}
      if(PqtALTAXHW == true){PqtALTAXHW = false;}
      if(oEnLhpUuOe == true){oEnLhpUuOe = false;}
      if(HHqfGUkmaT == true){HHqfGUkmaT = false;}
      if(UfeUwoZbDf == true){UfeUwoZbDf = false;}
      if(ZkIcthCHau == true){ZkIcthCHau = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GICRAVLAPA
{ 
  void CjTWarYdna()
  { 
      bool dGdwHJDlTA = false;
      bool nJIfWrrROL = false;
      bool AHXfVlJjYV = false;
      bool hrPPOEIrYd = false;
      bool mCWuJeUeQZ = false;
      bool WBVENVhxZV = false;
      bool ASMySusrRS = false;
      bool jzskYyjcVq = false;
      bool RdTyzgVLCr = false;
      bool VKSCcTpXcO = false;
      bool kbMypWIkeP = false;
      bool lFaiEWzNzk = false;
      bool YhpZwYgpHF = false;
      bool HLAHGoQVIb = false;
      bool YkgmGQiiyG = false;
      bool UbYqoDlmBQ = false;
      bool pRdYHZEScO = false;
      bool FcFXMnACTe = false;
      bool oxrAkfmJSC = false;
      bool DdTqkGGHff = false;
      string DkMBAXjPBw;
      string PJVzaKoufP;
      string fLQZJrEFjq;
      string rdglDnfsEX;
      string NxbmGKXRdx;
      string UTKWBqUlrI;
      string TeeKDlbiul;
      string euqIBiicTy;
      string TmamVXTJkM;
      string SsBuDiSRiU;
      string ioVqSYcCVS;
      string HrSsofErne;
      string SRyiSktuES;
      string QRtyPeQiUx;
      string uQnREaaHGX;
      string dacDCRpmXg;
      string egyDCpxTdK;
      string PUWqjBcfdr;
      string Klognpopwx;
      string ncLmSOSkPO;
      if(DkMBAXjPBw == ioVqSYcCVS){dGdwHJDlTA = true;}
      else if(ioVqSYcCVS == DkMBAXjPBw){kbMypWIkeP = true;}
      if(PJVzaKoufP == HrSsofErne){nJIfWrrROL = true;}
      else if(HrSsofErne == PJVzaKoufP){lFaiEWzNzk = true;}
      if(fLQZJrEFjq == SRyiSktuES){AHXfVlJjYV = true;}
      else if(SRyiSktuES == fLQZJrEFjq){YhpZwYgpHF = true;}
      if(rdglDnfsEX == QRtyPeQiUx){hrPPOEIrYd = true;}
      else if(QRtyPeQiUx == rdglDnfsEX){HLAHGoQVIb = true;}
      if(NxbmGKXRdx == uQnREaaHGX){mCWuJeUeQZ = true;}
      else if(uQnREaaHGX == NxbmGKXRdx){YkgmGQiiyG = true;}
      if(UTKWBqUlrI == dacDCRpmXg){WBVENVhxZV = true;}
      else if(dacDCRpmXg == UTKWBqUlrI){UbYqoDlmBQ = true;}
      if(TeeKDlbiul == egyDCpxTdK){ASMySusrRS = true;}
      else if(egyDCpxTdK == TeeKDlbiul){pRdYHZEScO = true;}
      if(euqIBiicTy == PUWqjBcfdr){jzskYyjcVq = true;}
      if(TmamVXTJkM == Klognpopwx){RdTyzgVLCr = true;}
      if(SsBuDiSRiU == ncLmSOSkPO){VKSCcTpXcO = true;}
      while(PUWqjBcfdr == euqIBiicTy){FcFXMnACTe = true;}
      while(Klognpopwx == Klognpopwx){oxrAkfmJSC = true;}
      while(ncLmSOSkPO == ncLmSOSkPO){DdTqkGGHff = true;}
      if(dGdwHJDlTA == true){dGdwHJDlTA = false;}
      if(nJIfWrrROL == true){nJIfWrrROL = false;}
      if(AHXfVlJjYV == true){AHXfVlJjYV = false;}
      if(hrPPOEIrYd == true){hrPPOEIrYd = false;}
      if(mCWuJeUeQZ == true){mCWuJeUeQZ = false;}
      if(WBVENVhxZV == true){WBVENVhxZV = false;}
      if(ASMySusrRS == true){ASMySusrRS = false;}
      if(jzskYyjcVq == true){jzskYyjcVq = false;}
      if(RdTyzgVLCr == true){RdTyzgVLCr = false;}
      if(VKSCcTpXcO == true){VKSCcTpXcO = false;}
      if(kbMypWIkeP == true){kbMypWIkeP = false;}
      if(lFaiEWzNzk == true){lFaiEWzNzk = false;}
      if(YhpZwYgpHF == true){YhpZwYgpHF = false;}
      if(HLAHGoQVIb == true){HLAHGoQVIb = false;}
      if(YkgmGQiiyG == true){YkgmGQiiyG = false;}
      if(UbYqoDlmBQ == true){UbYqoDlmBQ = false;}
      if(pRdYHZEScO == true){pRdYHZEScO = false;}
      if(FcFXMnACTe == true){FcFXMnACTe = false;}
      if(oxrAkfmJSC == true){oxrAkfmJSC = false;}
      if(DdTqkGGHff == true){DdTqkGGHff = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PHXDLWZPZS
{ 
  void ktaAdTKFcx()
  { 
      bool npzXCfJhCi = false;
      bool RbBnVZQkAi = false;
      bool DnGqoYNgLQ = false;
      bool stCIqzYKxd = false;
      bool qViSHbejUK = false;
      bool YEbeQzjIic = false;
      bool RcVlpXYrwW = false;
      bool BFnWrgEmiN = false;
      bool scLAqnRXrr = false;
      bool OPbTLNzxcj = false;
      bool DlnyJTPFmi = false;
      bool twZUjnQUtB = false;
      bool FBAEHkcULd = false;
      bool hHJyJGoNpX = false;
      bool YMjIxRpGjW = false;
      bool wdCbeClipY = false;
      bool putJBmlaLc = false;
      bool zDdWbsQqHo = false;
      bool uVjogDFhTH = false;
      bool UGXRgcRZHJ = false;
      string mSerBLwBtr;
      string UePUnTaSQV;
      string hEuEyCzFVs;
      string EpsfzHDpIk;
      string qoKtGjtEuR;
      string XMXSMhWasz;
      string LpfAndkjUf;
      string QkKedrsBxN;
      string HuJEVrSaSQ;
      string kbwJYAJKFc;
      string zKiPAmBrnT;
      string oVcfqQgaew;
      string KKQEuooBGd;
      string iiuUOxLsDi;
      string pamzaOzQRH;
      string TheJSoseUL;
      string xAkKjGaIQs;
      string FmXwGiWRcf;
      string oXizJBDlCZ;
      string DgYqkppcOT;
      if(mSerBLwBtr == zKiPAmBrnT){npzXCfJhCi = true;}
      else if(zKiPAmBrnT == mSerBLwBtr){DlnyJTPFmi = true;}
      if(UePUnTaSQV == oVcfqQgaew){RbBnVZQkAi = true;}
      else if(oVcfqQgaew == UePUnTaSQV){twZUjnQUtB = true;}
      if(hEuEyCzFVs == KKQEuooBGd){DnGqoYNgLQ = true;}
      else if(KKQEuooBGd == hEuEyCzFVs){FBAEHkcULd = true;}
      if(EpsfzHDpIk == iiuUOxLsDi){stCIqzYKxd = true;}
      else if(iiuUOxLsDi == EpsfzHDpIk){hHJyJGoNpX = true;}
      if(qoKtGjtEuR == pamzaOzQRH){qViSHbejUK = true;}
      else if(pamzaOzQRH == qoKtGjtEuR){YMjIxRpGjW = true;}
      if(XMXSMhWasz == TheJSoseUL){YEbeQzjIic = true;}
      else if(TheJSoseUL == XMXSMhWasz){wdCbeClipY = true;}
      if(LpfAndkjUf == xAkKjGaIQs){RcVlpXYrwW = true;}
      else if(xAkKjGaIQs == LpfAndkjUf){putJBmlaLc = true;}
      if(QkKedrsBxN == FmXwGiWRcf){BFnWrgEmiN = true;}
      if(HuJEVrSaSQ == oXizJBDlCZ){scLAqnRXrr = true;}
      if(kbwJYAJKFc == DgYqkppcOT){OPbTLNzxcj = true;}
      while(FmXwGiWRcf == QkKedrsBxN){zDdWbsQqHo = true;}
      while(oXizJBDlCZ == oXizJBDlCZ){uVjogDFhTH = true;}
      while(DgYqkppcOT == DgYqkppcOT){UGXRgcRZHJ = true;}
      if(npzXCfJhCi == true){npzXCfJhCi = false;}
      if(RbBnVZQkAi == true){RbBnVZQkAi = false;}
      if(DnGqoYNgLQ == true){DnGqoYNgLQ = false;}
      if(stCIqzYKxd == true){stCIqzYKxd = false;}
      if(qViSHbejUK == true){qViSHbejUK = false;}
      if(YEbeQzjIic == true){YEbeQzjIic = false;}
      if(RcVlpXYrwW == true){RcVlpXYrwW = false;}
      if(BFnWrgEmiN == true){BFnWrgEmiN = false;}
      if(scLAqnRXrr == true){scLAqnRXrr = false;}
      if(OPbTLNzxcj == true){OPbTLNzxcj = false;}
      if(DlnyJTPFmi == true){DlnyJTPFmi = false;}
      if(twZUjnQUtB == true){twZUjnQUtB = false;}
      if(FBAEHkcULd == true){FBAEHkcULd = false;}
      if(hHJyJGoNpX == true){hHJyJGoNpX = false;}
      if(YMjIxRpGjW == true){YMjIxRpGjW = false;}
      if(wdCbeClipY == true){wdCbeClipY = false;}
      if(putJBmlaLc == true){putJBmlaLc = false;}
      if(zDdWbsQqHo == true){zDdWbsQqHo = false;}
      if(uVjogDFhTH == true){uVjogDFhTH = false;}
      if(UGXRgcRZHJ == true){UGXRgcRZHJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFGLTCMMIE
{ 
  void SlcShYkLCD()
  { 
      bool HZnNydnqer = false;
      bool XsTftElNOJ = false;
      bool jFmPEDaOGn = false;
      bool KnliENxkLg = false;
      bool yxySzDlxyk = false;
      bool EWwWuClXJu = false;
      bool CZkqgiGkbf = false;
      bool GACgLmGUQA = false;
      bool QdQVimqPnC = false;
      bool bYbQdYMHlP = false;
      bool xBVSdDUOLH = false;
      bool uRHIdYJOHs = false;
      bool rqxYEgYkDl = false;
      bool ayiBCOHxqf = false;
      bool ScDfGJRSlE = false;
      bool PxArXGDwNx = false;
      bool ejKYgwiFFP = false;
      bool QLXaaOmRSu = false;
      bool OFyzVdxpdw = false;
      bool KLitBiRdyJ = false;
      string zbbQZFVCQw;
      string PAXPIpGwVw;
      string DLBmlsOewH;
      string OMQLroIlHx;
      string xlWxwnWXOa;
      string YmOPznandg;
      string ppFJgDiLWS;
      string gUnYzQnDqy;
      string VqQViayAME;
      string OUHZGGgNPr;
      string ELButDzoQh;
      string zWwfLzYjaG;
      string EhySDLNNRr;
      string jamysJoUae;
      string bIieEqXaOH;
      string hxlJnWMhrh;
      string pkXYxYiymB;
      string JDIuewyTOL;
      string nlzJKmndKW;
      string xGcsopkKge;
      if(zbbQZFVCQw == ELButDzoQh){HZnNydnqer = true;}
      else if(ELButDzoQh == zbbQZFVCQw){xBVSdDUOLH = true;}
      if(PAXPIpGwVw == zWwfLzYjaG){XsTftElNOJ = true;}
      else if(zWwfLzYjaG == PAXPIpGwVw){uRHIdYJOHs = true;}
      if(DLBmlsOewH == EhySDLNNRr){jFmPEDaOGn = true;}
      else if(EhySDLNNRr == DLBmlsOewH){rqxYEgYkDl = true;}
      if(OMQLroIlHx == jamysJoUae){KnliENxkLg = true;}
      else if(jamysJoUae == OMQLroIlHx){ayiBCOHxqf = true;}
      if(xlWxwnWXOa == bIieEqXaOH){yxySzDlxyk = true;}
      else if(bIieEqXaOH == xlWxwnWXOa){ScDfGJRSlE = true;}
      if(YmOPznandg == hxlJnWMhrh){EWwWuClXJu = true;}
      else if(hxlJnWMhrh == YmOPznandg){PxArXGDwNx = true;}
      if(ppFJgDiLWS == pkXYxYiymB){CZkqgiGkbf = true;}
      else if(pkXYxYiymB == ppFJgDiLWS){ejKYgwiFFP = true;}
      if(gUnYzQnDqy == JDIuewyTOL){GACgLmGUQA = true;}
      if(VqQViayAME == nlzJKmndKW){QdQVimqPnC = true;}
      if(OUHZGGgNPr == xGcsopkKge){bYbQdYMHlP = true;}
      while(JDIuewyTOL == gUnYzQnDqy){QLXaaOmRSu = true;}
      while(nlzJKmndKW == nlzJKmndKW){OFyzVdxpdw = true;}
      while(xGcsopkKge == xGcsopkKge){KLitBiRdyJ = true;}
      if(HZnNydnqer == true){HZnNydnqer = false;}
      if(XsTftElNOJ == true){XsTftElNOJ = false;}
      if(jFmPEDaOGn == true){jFmPEDaOGn = false;}
      if(KnliENxkLg == true){KnliENxkLg = false;}
      if(yxySzDlxyk == true){yxySzDlxyk = false;}
      if(EWwWuClXJu == true){EWwWuClXJu = false;}
      if(CZkqgiGkbf == true){CZkqgiGkbf = false;}
      if(GACgLmGUQA == true){GACgLmGUQA = false;}
      if(QdQVimqPnC == true){QdQVimqPnC = false;}
      if(bYbQdYMHlP == true){bYbQdYMHlP = false;}
      if(xBVSdDUOLH == true){xBVSdDUOLH = false;}
      if(uRHIdYJOHs == true){uRHIdYJOHs = false;}
      if(rqxYEgYkDl == true){rqxYEgYkDl = false;}
      if(ayiBCOHxqf == true){ayiBCOHxqf = false;}
      if(ScDfGJRSlE == true){ScDfGJRSlE = false;}
      if(PxArXGDwNx == true){PxArXGDwNx = false;}
      if(ejKYgwiFFP == true){ejKYgwiFFP = false;}
      if(QLXaaOmRSu == true){QLXaaOmRSu = false;}
      if(OFyzVdxpdw == true){OFyzVdxpdw = false;}
      if(KLitBiRdyJ == true){KLitBiRdyJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ITGZHBNEIV
{ 
  void HjHWMVFfea()
  { 
      bool KDYtGGRMGn = false;
      bool sjpXLmKJNs = false;
      bool AcNoIPKJYD = false;
      bool UOunNPDyKZ = false;
      bool tAZWckxdkd = false;
      bool hOTyfhpjlp = false;
      bool uHmDSeoBKw = false;
      bool iLymyACqMX = false;
      bool SgXtVFtwHe = false;
      bool YTMUelNWDx = false;
      bool wuSouVPfAf = false;
      bool fyXNWOisgN = false;
      bool jrseWPzdIL = false;
      bool lenObXNizA = false;
      bool oNwbzawzxQ = false;
      bool CUpoNDBmSf = false;
      bool VlXnsAKIly = false;
      bool AAsfXVwRfu = false;
      bool SAfrJRoyBX = false;
      bool VZPTdDpHhz = false;
      string dYCYEdwCuT;
      string ZmwrEHZfdR;
      string mFuZcgzrQK;
      string EkuXztTERq;
      string ksMMLEgVBN;
      string zjmajXdcwW;
      string eEljOoqYrK;
      string mVNlgssiNY;
      string AcqCLUyUna;
      string QqIuLgHbxW;
      string MHdqadWAsp;
      string euOXWCNiYt;
      string pWjRtuNRZz;
      string kQkpLrzzbh;
      string xyaxuUbjYJ;
      string TYDDfoXLxe;
      string PEZsFOJXLd;
      string DNGqwrwmVY;
      string TcsQfMNgKW;
      string UmCxRrXgrg;
      if(dYCYEdwCuT == MHdqadWAsp){KDYtGGRMGn = true;}
      else if(MHdqadWAsp == dYCYEdwCuT){wuSouVPfAf = true;}
      if(ZmwrEHZfdR == euOXWCNiYt){sjpXLmKJNs = true;}
      else if(euOXWCNiYt == ZmwrEHZfdR){fyXNWOisgN = true;}
      if(mFuZcgzrQK == pWjRtuNRZz){AcNoIPKJYD = true;}
      else if(pWjRtuNRZz == mFuZcgzrQK){jrseWPzdIL = true;}
      if(EkuXztTERq == kQkpLrzzbh){UOunNPDyKZ = true;}
      else if(kQkpLrzzbh == EkuXztTERq){lenObXNizA = true;}
      if(ksMMLEgVBN == xyaxuUbjYJ){tAZWckxdkd = true;}
      else if(xyaxuUbjYJ == ksMMLEgVBN){oNwbzawzxQ = true;}
      if(zjmajXdcwW == TYDDfoXLxe){hOTyfhpjlp = true;}
      else if(TYDDfoXLxe == zjmajXdcwW){CUpoNDBmSf = true;}
      if(eEljOoqYrK == PEZsFOJXLd){uHmDSeoBKw = true;}
      else if(PEZsFOJXLd == eEljOoqYrK){VlXnsAKIly = true;}
      if(mVNlgssiNY == DNGqwrwmVY){iLymyACqMX = true;}
      if(AcqCLUyUna == TcsQfMNgKW){SgXtVFtwHe = true;}
      if(QqIuLgHbxW == UmCxRrXgrg){YTMUelNWDx = true;}
      while(DNGqwrwmVY == mVNlgssiNY){AAsfXVwRfu = true;}
      while(TcsQfMNgKW == TcsQfMNgKW){SAfrJRoyBX = true;}
      while(UmCxRrXgrg == UmCxRrXgrg){VZPTdDpHhz = true;}
      if(KDYtGGRMGn == true){KDYtGGRMGn = false;}
      if(sjpXLmKJNs == true){sjpXLmKJNs = false;}
      if(AcNoIPKJYD == true){AcNoIPKJYD = false;}
      if(UOunNPDyKZ == true){UOunNPDyKZ = false;}
      if(tAZWckxdkd == true){tAZWckxdkd = false;}
      if(hOTyfhpjlp == true){hOTyfhpjlp = false;}
      if(uHmDSeoBKw == true){uHmDSeoBKw = false;}
      if(iLymyACqMX == true){iLymyACqMX = false;}
      if(SgXtVFtwHe == true){SgXtVFtwHe = false;}
      if(YTMUelNWDx == true){YTMUelNWDx = false;}
      if(wuSouVPfAf == true){wuSouVPfAf = false;}
      if(fyXNWOisgN == true){fyXNWOisgN = false;}
      if(jrseWPzdIL == true){jrseWPzdIL = false;}
      if(lenObXNizA == true){lenObXNizA = false;}
      if(oNwbzawzxQ == true){oNwbzawzxQ = false;}
      if(CUpoNDBmSf == true){CUpoNDBmSf = false;}
      if(VlXnsAKIly == true){VlXnsAKIly = false;}
      if(AAsfXVwRfu == true){AAsfXVwRfu = false;}
      if(SAfrJRoyBX == true){SAfrJRoyBX = false;}
      if(VZPTdDpHhz == true){VZPTdDpHhz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SEMEPJVKFO
{ 
  void rGFnqRugaz()
  { 
      bool WWLHdOLAUf = false;
      bool LGyFrWgXPY = false;
      bool FjSHOGyrkW = false;
      bool QhrXzwqTUM = false;
      bool VahEfrwVrt = false;
      bool yZrxcmEDrX = false;
      bool QSPyOdNZFw = false;
      bool eMCDDeBObV = false;
      bool JbzqXppttM = false;
      bool qmaxwCLjoC = false;
      bool dVPwOkXnty = false;
      bool kpbWNnSYaX = false;
      bool mTfsEqlFHB = false;
      bool SRYZqmMDbl = false;
      bool SBAwaBLEiH = false;
      bool imJQOKpWqW = false;
      bool zRgsfTQCea = false;
      bool bPwnFlSiRD = false;
      bool fhWzRfIILf = false;
      bool xoLEmBUHQH = false;
      string DeWFQmNcVf;
      string jkRaepDcVe;
      string aJejZxIaDr;
      string zgoTYYrjZK;
      string BodrenMeOC;
      string JHLiNtAleT;
      string dmZdgDuyCG;
      string yTCKdkflFl;
      string jcLAhrUFFe;
      string YFEFfOOzLb;
      string rOcIEpEAFc;
      string NNfsjBaZuo;
      string hprXgrOxdO;
      string WfZdtVACwr;
      string mTzcQKZLVe;
      string moDWsCVFbL;
      string aHWqGhmCzN;
      string BYcDBNpPGW;
      string SDazagbDjq;
      string ztakRexIWi;
      if(DeWFQmNcVf == rOcIEpEAFc){WWLHdOLAUf = true;}
      else if(rOcIEpEAFc == DeWFQmNcVf){dVPwOkXnty = true;}
      if(jkRaepDcVe == NNfsjBaZuo){LGyFrWgXPY = true;}
      else if(NNfsjBaZuo == jkRaepDcVe){kpbWNnSYaX = true;}
      if(aJejZxIaDr == hprXgrOxdO){FjSHOGyrkW = true;}
      else if(hprXgrOxdO == aJejZxIaDr){mTfsEqlFHB = true;}
      if(zgoTYYrjZK == WfZdtVACwr){QhrXzwqTUM = true;}
      else if(WfZdtVACwr == zgoTYYrjZK){SRYZqmMDbl = true;}
      if(BodrenMeOC == mTzcQKZLVe){VahEfrwVrt = true;}
      else if(mTzcQKZLVe == BodrenMeOC){SBAwaBLEiH = true;}
      if(JHLiNtAleT == moDWsCVFbL){yZrxcmEDrX = true;}
      else if(moDWsCVFbL == JHLiNtAleT){imJQOKpWqW = true;}
      if(dmZdgDuyCG == aHWqGhmCzN){QSPyOdNZFw = true;}
      else if(aHWqGhmCzN == dmZdgDuyCG){zRgsfTQCea = true;}
      if(yTCKdkflFl == BYcDBNpPGW){eMCDDeBObV = true;}
      if(jcLAhrUFFe == SDazagbDjq){JbzqXppttM = true;}
      if(YFEFfOOzLb == ztakRexIWi){qmaxwCLjoC = true;}
      while(BYcDBNpPGW == yTCKdkflFl){bPwnFlSiRD = true;}
      while(SDazagbDjq == SDazagbDjq){fhWzRfIILf = true;}
      while(ztakRexIWi == ztakRexIWi){xoLEmBUHQH = true;}
      if(WWLHdOLAUf == true){WWLHdOLAUf = false;}
      if(LGyFrWgXPY == true){LGyFrWgXPY = false;}
      if(FjSHOGyrkW == true){FjSHOGyrkW = false;}
      if(QhrXzwqTUM == true){QhrXzwqTUM = false;}
      if(VahEfrwVrt == true){VahEfrwVrt = false;}
      if(yZrxcmEDrX == true){yZrxcmEDrX = false;}
      if(QSPyOdNZFw == true){QSPyOdNZFw = false;}
      if(eMCDDeBObV == true){eMCDDeBObV = false;}
      if(JbzqXppttM == true){JbzqXppttM = false;}
      if(qmaxwCLjoC == true){qmaxwCLjoC = false;}
      if(dVPwOkXnty == true){dVPwOkXnty = false;}
      if(kpbWNnSYaX == true){kpbWNnSYaX = false;}
      if(mTfsEqlFHB == true){mTfsEqlFHB = false;}
      if(SRYZqmMDbl == true){SRYZqmMDbl = false;}
      if(SBAwaBLEiH == true){SBAwaBLEiH = false;}
      if(imJQOKpWqW == true){imJQOKpWqW = false;}
      if(zRgsfTQCea == true){zRgsfTQCea = false;}
      if(bPwnFlSiRD == true){bPwnFlSiRD = false;}
      if(fhWzRfIILf == true){fhWzRfIILf = false;}
      if(xoLEmBUHQH == true){xoLEmBUHQH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XYYBUNIEYX
{ 
  void ktYdYpopWI()
  { 
      bool RwtSiyOMus = false;
      bool LrpWDQguMG = false;
      bool BpnQRcplXN = false;
      bool sLEjufGOmw = false;
      bool CzOGfZBwGK = false;
      bool QziKMbIcBG = false;
      bool HcogAAnFaX = false;
      bool JSHPEBbgjq = false;
      bool btfMwtcsXT = false;
      bool WdMfnYJgGf = false;
      bool luUhAyqSGK = false;
      bool zbrKdNxckG = false;
      bool WtgHAfFbbe = false;
      bool qtaDEfZxMy = false;
      bool CJmNTukCBa = false;
      bool agwzIrOMhT = false;
      bool rPqaSFBnFy = false;
      bool mAPlDNGTnE = false;
      bool uCZAEKyauM = false;
      bool RNOrFmSMuO = false;
      string TpfUkFealx;
      string XZLfYRZieT;
      string szVtDUHBDY;
      string LWxNlGtrhB;
      string xTTUgJTKiR;
      string FzUhZUUkQP;
      string xdWMlAbxsS;
      string XgBdWYfBNt;
      string BxSkSLCPnR;
      string lIaRDTxGhf;
      string gVQPtYyqLA;
      string nTWWOALlsZ;
      string yMIbfOFjZD;
      string bZShMefCpt;
      string NLEncSlECD;
      string HKMIgTMojf;
      string SOQIXOAoJj;
      string TIuzMmIUyN;
      string cBgVuRMKAr;
      string SqSJbytwQN;
      if(TpfUkFealx == gVQPtYyqLA){RwtSiyOMus = true;}
      else if(gVQPtYyqLA == TpfUkFealx){luUhAyqSGK = true;}
      if(XZLfYRZieT == nTWWOALlsZ){LrpWDQguMG = true;}
      else if(nTWWOALlsZ == XZLfYRZieT){zbrKdNxckG = true;}
      if(szVtDUHBDY == yMIbfOFjZD){BpnQRcplXN = true;}
      else if(yMIbfOFjZD == szVtDUHBDY){WtgHAfFbbe = true;}
      if(LWxNlGtrhB == bZShMefCpt){sLEjufGOmw = true;}
      else if(bZShMefCpt == LWxNlGtrhB){qtaDEfZxMy = true;}
      if(xTTUgJTKiR == NLEncSlECD){CzOGfZBwGK = true;}
      else if(NLEncSlECD == xTTUgJTKiR){CJmNTukCBa = true;}
      if(FzUhZUUkQP == HKMIgTMojf){QziKMbIcBG = true;}
      else if(HKMIgTMojf == FzUhZUUkQP){agwzIrOMhT = true;}
      if(xdWMlAbxsS == SOQIXOAoJj){HcogAAnFaX = true;}
      else if(SOQIXOAoJj == xdWMlAbxsS){rPqaSFBnFy = true;}
      if(XgBdWYfBNt == TIuzMmIUyN){JSHPEBbgjq = true;}
      if(BxSkSLCPnR == cBgVuRMKAr){btfMwtcsXT = true;}
      if(lIaRDTxGhf == SqSJbytwQN){WdMfnYJgGf = true;}
      while(TIuzMmIUyN == XgBdWYfBNt){mAPlDNGTnE = true;}
      while(cBgVuRMKAr == cBgVuRMKAr){uCZAEKyauM = true;}
      while(SqSJbytwQN == SqSJbytwQN){RNOrFmSMuO = true;}
      if(RwtSiyOMus == true){RwtSiyOMus = false;}
      if(LrpWDQguMG == true){LrpWDQguMG = false;}
      if(BpnQRcplXN == true){BpnQRcplXN = false;}
      if(sLEjufGOmw == true){sLEjufGOmw = false;}
      if(CzOGfZBwGK == true){CzOGfZBwGK = false;}
      if(QziKMbIcBG == true){QziKMbIcBG = false;}
      if(HcogAAnFaX == true){HcogAAnFaX = false;}
      if(JSHPEBbgjq == true){JSHPEBbgjq = false;}
      if(btfMwtcsXT == true){btfMwtcsXT = false;}
      if(WdMfnYJgGf == true){WdMfnYJgGf = false;}
      if(luUhAyqSGK == true){luUhAyqSGK = false;}
      if(zbrKdNxckG == true){zbrKdNxckG = false;}
      if(WtgHAfFbbe == true){WtgHAfFbbe = false;}
      if(qtaDEfZxMy == true){qtaDEfZxMy = false;}
      if(CJmNTukCBa == true){CJmNTukCBa = false;}
      if(agwzIrOMhT == true){agwzIrOMhT = false;}
      if(rPqaSFBnFy == true){rPqaSFBnFy = false;}
      if(mAPlDNGTnE == true){mAPlDNGTnE = false;}
      if(uCZAEKyauM == true){uCZAEKyauM = false;}
      if(RNOrFmSMuO == true){RNOrFmSMuO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OQRQOQJQQA
{ 
  void xXsdXbgVJB()
  { 
      bool QHHaAhDYzt = false;
      bool PkQJkKRYdu = false;
      bool ikFnTmpubi = false;
      bool jEgciJQnjE = false;
      bool PMVNbXRZtT = false;
      bool eYhjJeBSHM = false;
      bool qHwQKKEmZb = false;
      bool tdoYfVOrMu = false;
      bool VQBHDKWwTD = false;
      bool IxfWMHPFDQ = false;
      bool TezSZBjIDm = false;
      bool QJFMqZFoNz = false;
      bool nHTWSwxRMY = false;
      bool GJnwaqRigB = false;
      bool aNrfmyqTfl = false;
      bool CaqEbMKczc = false;
      bool ESwegGVJkz = false;
      bool IVHLXaOmiU = false;
      bool EckZVeRjTO = false;
      bool fojExIRMzf = false;
      string uacEpfNAbl;
      string RBQmqWtHNw;
      string GrYdDmyRSA;
      string uFVCDjRruu;
      string YVagcFVGot;
      string tOihwDCyBD;
      string hwhaqLfOiG;
      string FBMSXkRrBx;
      string QqbXGgWmGz;
      string hSqrMcnApQ;
      string ZHWhosCPKL;
      string lJxDmpTJUK;
      string orIjYlKUGu;
      string wQCjXIUshN;
      string dHbtNYUmEV;
      string IdffbgzmJC;
      string hgJPOUHNfd;
      string VZaGfhQNVA;
      string RXPjlSkVHq;
      string JhieexxLfs;
      if(uacEpfNAbl == ZHWhosCPKL){QHHaAhDYzt = true;}
      else if(ZHWhosCPKL == uacEpfNAbl){TezSZBjIDm = true;}
      if(RBQmqWtHNw == lJxDmpTJUK){PkQJkKRYdu = true;}
      else if(lJxDmpTJUK == RBQmqWtHNw){QJFMqZFoNz = true;}
      if(GrYdDmyRSA == orIjYlKUGu){ikFnTmpubi = true;}
      else if(orIjYlKUGu == GrYdDmyRSA){nHTWSwxRMY = true;}
      if(uFVCDjRruu == wQCjXIUshN){jEgciJQnjE = true;}
      else if(wQCjXIUshN == uFVCDjRruu){GJnwaqRigB = true;}
      if(YVagcFVGot == dHbtNYUmEV){PMVNbXRZtT = true;}
      else if(dHbtNYUmEV == YVagcFVGot){aNrfmyqTfl = true;}
      if(tOihwDCyBD == IdffbgzmJC){eYhjJeBSHM = true;}
      else if(IdffbgzmJC == tOihwDCyBD){CaqEbMKczc = true;}
      if(hwhaqLfOiG == hgJPOUHNfd){qHwQKKEmZb = true;}
      else if(hgJPOUHNfd == hwhaqLfOiG){ESwegGVJkz = true;}
      if(FBMSXkRrBx == VZaGfhQNVA){tdoYfVOrMu = true;}
      if(QqbXGgWmGz == RXPjlSkVHq){VQBHDKWwTD = true;}
      if(hSqrMcnApQ == JhieexxLfs){IxfWMHPFDQ = true;}
      while(VZaGfhQNVA == FBMSXkRrBx){IVHLXaOmiU = true;}
      while(RXPjlSkVHq == RXPjlSkVHq){EckZVeRjTO = true;}
      while(JhieexxLfs == JhieexxLfs){fojExIRMzf = true;}
      if(QHHaAhDYzt == true){QHHaAhDYzt = false;}
      if(PkQJkKRYdu == true){PkQJkKRYdu = false;}
      if(ikFnTmpubi == true){ikFnTmpubi = false;}
      if(jEgciJQnjE == true){jEgciJQnjE = false;}
      if(PMVNbXRZtT == true){PMVNbXRZtT = false;}
      if(eYhjJeBSHM == true){eYhjJeBSHM = false;}
      if(qHwQKKEmZb == true){qHwQKKEmZb = false;}
      if(tdoYfVOrMu == true){tdoYfVOrMu = false;}
      if(VQBHDKWwTD == true){VQBHDKWwTD = false;}
      if(IxfWMHPFDQ == true){IxfWMHPFDQ = false;}
      if(TezSZBjIDm == true){TezSZBjIDm = false;}
      if(QJFMqZFoNz == true){QJFMqZFoNz = false;}
      if(nHTWSwxRMY == true){nHTWSwxRMY = false;}
      if(GJnwaqRigB == true){GJnwaqRigB = false;}
      if(aNrfmyqTfl == true){aNrfmyqTfl = false;}
      if(CaqEbMKczc == true){CaqEbMKczc = false;}
      if(ESwegGVJkz == true){ESwegGVJkz = false;}
      if(IVHLXaOmiU == true){IVHLXaOmiU = false;}
      if(EckZVeRjTO == true){EckZVeRjTO = false;}
      if(fojExIRMzf == true){fojExIRMzf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IGAAWDDMQX
{ 
  void ZMHqCZSbtp()
  { 
      bool aHUtuScUbM = false;
      bool UaxDPVUsFG = false;
      bool tnkIzyJdYz = false;
      bool zdGAkyaUne = false;
      bool UxzwMaWOrF = false;
      bool WhBzFlWLux = false;
      bool IzucMqTwSQ = false;
      bool tzFZkxonwY = false;
      bool bulTbRcHuy = false;
      bool bPZpVVBWiV = false;
      bool GZwaLWbaOH = false;
      bool xhOVVNMbAu = false;
      bool NMAToeZODO = false;
      bool uREaSBzKIE = false;
      bool oBsnAtBDUI = false;
      bool JZVnHsYblf = false;
      bool wMXzLfdnCT = false;
      bool OBTuGLTMTu = false;
      bool dWtuFUwQSY = false;
      bool bWYbHbdsbU = false;
      string uzFUBarXFF;
      string OFyxFGLbFQ;
      string KmGwyLOftp;
      string QCCwVxDNcJ;
      string RMgZeGLlci;
      string WtWuRHrIWp;
      string LMdOoLDBaI;
      string DxyuyyGgQq;
      string zbCLTWfHeN;
      string EtpmxFiRkT;
      string CKKUfYuawT;
      string BLrepjKRuR;
      string fwWNEIHLxs;
      string OnuxnoRhet;
      string aEKKMrCLwN;
      string tQVSnGmxPW;
      string RjcDEMQtpB;
      string RbmBqakMAM;
      string GwOjyyRbJh;
      string BTRIbqaGFz;
      if(uzFUBarXFF == CKKUfYuawT){aHUtuScUbM = true;}
      else if(CKKUfYuawT == uzFUBarXFF){GZwaLWbaOH = true;}
      if(OFyxFGLbFQ == BLrepjKRuR){UaxDPVUsFG = true;}
      else if(BLrepjKRuR == OFyxFGLbFQ){xhOVVNMbAu = true;}
      if(KmGwyLOftp == fwWNEIHLxs){tnkIzyJdYz = true;}
      else if(fwWNEIHLxs == KmGwyLOftp){NMAToeZODO = true;}
      if(QCCwVxDNcJ == OnuxnoRhet){zdGAkyaUne = true;}
      else if(OnuxnoRhet == QCCwVxDNcJ){uREaSBzKIE = true;}
      if(RMgZeGLlci == aEKKMrCLwN){UxzwMaWOrF = true;}
      else if(aEKKMrCLwN == RMgZeGLlci){oBsnAtBDUI = true;}
      if(WtWuRHrIWp == tQVSnGmxPW){WhBzFlWLux = true;}
      else if(tQVSnGmxPW == WtWuRHrIWp){JZVnHsYblf = true;}
      if(LMdOoLDBaI == RjcDEMQtpB){IzucMqTwSQ = true;}
      else if(RjcDEMQtpB == LMdOoLDBaI){wMXzLfdnCT = true;}
      if(DxyuyyGgQq == RbmBqakMAM){tzFZkxonwY = true;}
      if(zbCLTWfHeN == GwOjyyRbJh){bulTbRcHuy = true;}
      if(EtpmxFiRkT == BTRIbqaGFz){bPZpVVBWiV = true;}
      while(RbmBqakMAM == DxyuyyGgQq){OBTuGLTMTu = true;}
      while(GwOjyyRbJh == GwOjyyRbJh){dWtuFUwQSY = true;}
      while(BTRIbqaGFz == BTRIbqaGFz){bWYbHbdsbU = true;}
      if(aHUtuScUbM == true){aHUtuScUbM = false;}
      if(UaxDPVUsFG == true){UaxDPVUsFG = false;}
      if(tnkIzyJdYz == true){tnkIzyJdYz = false;}
      if(zdGAkyaUne == true){zdGAkyaUne = false;}
      if(UxzwMaWOrF == true){UxzwMaWOrF = false;}
      if(WhBzFlWLux == true){WhBzFlWLux = false;}
      if(IzucMqTwSQ == true){IzucMqTwSQ = false;}
      if(tzFZkxonwY == true){tzFZkxonwY = false;}
      if(bulTbRcHuy == true){bulTbRcHuy = false;}
      if(bPZpVVBWiV == true){bPZpVVBWiV = false;}
      if(GZwaLWbaOH == true){GZwaLWbaOH = false;}
      if(xhOVVNMbAu == true){xhOVVNMbAu = false;}
      if(NMAToeZODO == true){NMAToeZODO = false;}
      if(uREaSBzKIE == true){uREaSBzKIE = false;}
      if(oBsnAtBDUI == true){oBsnAtBDUI = false;}
      if(JZVnHsYblf == true){JZVnHsYblf = false;}
      if(wMXzLfdnCT == true){wMXzLfdnCT = false;}
      if(OBTuGLTMTu == true){OBTuGLTMTu = false;}
      if(dWtuFUwQSY == true){dWtuFUwQSY = false;}
      if(bWYbHbdsbU == true){bWYbHbdsbU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHYDWUSQLR
{ 
  void oKaiOMMlhf()
  { 
      bool fqezNqgrWR = false;
      bool ZOHJojhfcC = false;
      bool hfzFmdtOkV = false;
      bool afZLIgOmck = false;
      bool RoQkInaiUo = false;
      bool kSgJazrZMi = false;
      bool xRHAqsowAI = false;
      bool VuCqjsONwy = false;
      bool DLtukIzPkJ = false;
      bool onZtnAgQtO = false;
      bool zeiLTpPoZg = false;
      bool jddOflWLPh = false;
      bool tZLpThUIDj = false;
      bool LxTgzYbibt = false;
      bool rJpDYKKLNC = false;
      bool cVBLUYSrrl = false;
      bool VHloVlJwOH = false;
      bool JnjUokiHRI = false;
      bool WItAHpwIMZ = false;
      bool FjppYkWAgm = false;
      string tQQkfeijST;
      string isDDrejFbi;
      string FlDibcXamH;
      string BYJhihXQpH;
      string RzfKzGVpwk;
      string LNKfNINgJC;
      string GIxLSKjUTJ;
      string HTPTRGGrjV;
      string GhdBumNdUa;
      string UpGmAJBTro;
      string VBVmdqyqNG;
      string BUxmwYduPe;
      string wFAsoQMcSI;
      string FlAuzFLqWE;
      string oWPNYzsTpb;
      string eFEMrPBcyN;
      string dUXFBPTBnq;
      string NmYLpZplUo;
      string XslqczhmCi;
      string DirJZTyJMI;
      if(tQQkfeijST == VBVmdqyqNG){fqezNqgrWR = true;}
      else if(VBVmdqyqNG == tQQkfeijST){zeiLTpPoZg = true;}
      if(isDDrejFbi == BUxmwYduPe){ZOHJojhfcC = true;}
      else if(BUxmwYduPe == isDDrejFbi){jddOflWLPh = true;}
      if(FlDibcXamH == wFAsoQMcSI){hfzFmdtOkV = true;}
      else if(wFAsoQMcSI == FlDibcXamH){tZLpThUIDj = true;}
      if(BYJhihXQpH == FlAuzFLqWE){afZLIgOmck = true;}
      else if(FlAuzFLqWE == BYJhihXQpH){LxTgzYbibt = true;}
      if(RzfKzGVpwk == oWPNYzsTpb){RoQkInaiUo = true;}
      else if(oWPNYzsTpb == RzfKzGVpwk){rJpDYKKLNC = true;}
      if(LNKfNINgJC == eFEMrPBcyN){kSgJazrZMi = true;}
      else if(eFEMrPBcyN == LNKfNINgJC){cVBLUYSrrl = true;}
      if(GIxLSKjUTJ == dUXFBPTBnq){xRHAqsowAI = true;}
      else if(dUXFBPTBnq == GIxLSKjUTJ){VHloVlJwOH = true;}
      if(HTPTRGGrjV == NmYLpZplUo){VuCqjsONwy = true;}
      if(GhdBumNdUa == XslqczhmCi){DLtukIzPkJ = true;}
      if(UpGmAJBTro == DirJZTyJMI){onZtnAgQtO = true;}
      while(NmYLpZplUo == HTPTRGGrjV){JnjUokiHRI = true;}
      while(XslqczhmCi == XslqczhmCi){WItAHpwIMZ = true;}
      while(DirJZTyJMI == DirJZTyJMI){FjppYkWAgm = true;}
      if(fqezNqgrWR == true){fqezNqgrWR = false;}
      if(ZOHJojhfcC == true){ZOHJojhfcC = false;}
      if(hfzFmdtOkV == true){hfzFmdtOkV = false;}
      if(afZLIgOmck == true){afZLIgOmck = false;}
      if(RoQkInaiUo == true){RoQkInaiUo = false;}
      if(kSgJazrZMi == true){kSgJazrZMi = false;}
      if(xRHAqsowAI == true){xRHAqsowAI = false;}
      if(VuCqjsONwy == true){VuCqjsONwy = false;}
      if(DLtukIzPkJ == true){DLtukIzPkJ = false;}
      if(onZtnAgQtO == true){onZtnAgQtO = false;}
      if(zeiLTpPoZg == true){zeiLTpPoZg = false;}
      if(jddOflWLPh == true){jddOflWLPh = false;}
      if(tZLpThUIDj == true){tZLpThUIDj = false;}
      if(LxTgzYbibt == true){LxTgzYbibt = false;}
      if(rJpDYKKLNC == true){rJpDYKKLNC = false;}
      if(cVBLUYSrrl == true){cVBLUYSrrl = false;}
      if(VHloVlJwOH == true){VHloVlJwOH = false;}
      if(JnjUokiHRI == true){JnjUokiHRI = false;}
      if(WItAHpwIMZ == true){WItAHpwIMZ = false;}
      if(FjppYkWAgm == true){FjppYkWAgm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MQMIQLSUXD
{ 
  void qTLTyaLCqM()
  { 
      bool HZXyXDyDsl = false;
      bool POksfutRqZ = false;
      bool FXkiBXbqPY = false;
      bool llpqCllfSh = false;
      bool RPNMEXEyXr = false;
      bool mgHWQionxz = false;
      bool bGmTzdYtps = false;
      bool JOzIIoKXdd = false;
      bool SdSXkFdSZT = false;
      bool xxhTGKbsNa = false;
      bool yKHehYhyOb = false;
      bool XQJTfxnPht = false;
      bool zFUVuLfeCx = false;
      bool NRKDeIVnoM = false;
      bool WeDywfmOnI = false;
      bool WLKSarpkiW = false;
      bool rDwRNFGGoW = false;
      bool bzZVWTBVZO = false;
      bool XRqsZBHqbl = false;
      bool SjFSTTiljp = false;
      string ysxrAHYJMX;
      string odmWyDHoKn;
      string YVnyfGFPKZ;
      string PzyaVcPPIq;
      string shqUHtoIUB;
      string kUFhocEyLt;
      string BIzlHoeMBU;
      string mqfStqeTpk;
      string RxuJnutQls;
      string XRDOpkhEMS;
      string PcHANtolmy;
      string ykHacENpxM;
      string tNaIwVmQcJ;
      string IZGXVnotut;
      string FIcmtlJcll;
      string WrGzXBCzDr;
      string GXIdpXejEn;
      string OStDGlkmNK;
      string LKdplPSGzU;
      string lpqDnhzzxW;
      if(ysxrAHYJMX == PcHANtolmy){HZXyXDyDsl = true;}
      else if(PcHANtolmy == ysxrAHYJMX){yKHehYhyOb = true;}
      if(odmWyDHoKn == ykHacENpxM){POksfutRqZ = true;}
      else if(ykHacENpxM == odmWyDHoKn){XQJTfxnPht = true;}
      if(YVnyfGFPKZ == tNaIwVmQcJ){FXkiBXbqPY = true;}
      else if(tNaIwVmQcJ == YVnyfGFPKZ){zFUVuLfeCx = true;}
      if(PzyaVcPPIq == IZGXVnotut){llpqCllfSh = true;}
      else if(IZGXVnotut == PzyaVcPPIq){NRKDeIVnoM = true;}
      if(shqUHtoIUB == FIcmtlJcll){RPNMEXEyXr = true;}
      else if(FIcmtlJcll == shqUHtoIUB){WeDywfmOnI = true;}
      if(kUFhocEyLt == WrGzXBCzDr){mgHWQionxz = true;}
      else if(WrGzXBCzDr == kUFhocEyLt){WLKSarpkiW = true;}
      if(BIzlHoeMBU == GXIdpXejEn){bGmTzdYtps = true;}
      else if(GXIdpXejEn == BIzlHoeMBU){rDwRNFGGoW = true;}
      if(mqfStqeTpk == OStDGlkmNK){JOzIIoKXdd = true;}
      if(RxuJnutQls == LKdplPSGzU){SdSXkFdSZT = true;}
      if(XRDOpkhEMS == lpqDnhzzxW){xxhTGKbsNa = true;}
      while(OStDGlkmNK == mqfStqeTpk){bzZVWTBVZO = true;}
      while(LKdplPSGzU == LKdplPSGzU){XRqsZBHqbl = true;}
      while(lpqDnhzzxW == lpqDnhzzxW){SjFSTTiljp = true;}
      if(HZXyXDyDsl == true){HZXyXDyDsl = false;}
      if(POksfutRqZ == true){POksfutRqZ = false;}
      if(FXkiBXbqPY == true){FXkiBXbqPY = false;}
      if(llpqCllfSh == true){llpqCllfSh = false;}
      if(RPNMEXEyXr == true){RPNMEXEyXr = false;}
      if(mgHWQionxz == true){mgHWQionxz = false;}
      if(bGmTzdYtps == true){bGmTzdYtps = false;}
      if(JOzIIoKXdd == true){JOzIIoKXdd = false;}
      if(SdSXkFdSZT == true){SdSXkFdSZT = false;}
      if(xxhTGKbsNa == true){xxhTGKbsNa = false;}
      if(yKHehYhyOb == true){yKHehYhyOb = false;}
      if(XQJTfxnPht == true){XQJTfxnPht = false;}
      if(zFUVuLfeCx == true){zFUVuLfeCx = false;}
      if(NRKDeIVnoM == true){NRKDeIVnoM = false;}
      if(WeDywfmOnI == true){WeDywfmOnI = false;}
      if(WLKSarpkiW == true){WLKSarpkiW = false;}
      if(rDwRNFGGoW == true){rDwRNFGGoW = false;}
      if(bzZVWTBVZO == true){bzZVWTBVZO = false;}
      if(XRqsZBHqbl == true){XRqsZBHqbl = false;}
      if(SjFSTTiljp == true){SjFSTTiljp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UATVKGJGJE
{ 
  void tBpaWihIWY()
  { 
      bool OPabHqWxSG = false;
      bool hGywSIRYwz = false;
      bool yGBazMlpla = false;
      bool ojbmibjsXU = false;
      bool nQarcZybLm = false;
      bool JlnhOINzcu = false;
      bool EfKrQxeLMq = false;
      bool XXBbKgfJyY = false;
      bool NKdzQDusXa = false;
      bool OjQcPHFiae = false;
      bool umOUOkjMXh = false;
      bool bDBDgtCLaN = false;
      bool CknkbnHYMD = false;
      bool axhTdauJjf = false;
      bool SiVpyKiMuU = false;
      bool FtHNbJzdra = false;
      bool cLzUGeVhZF = false;
      bool zrbutSPxmR = false;
      bool EtcqxgoTqT = false;
      bool bQRICHiBjS = false;
      string eHWJZojZdR;
      string XJXWoqZpZd;
      string YApkdiJdHc;
      string QpeTMuKqaD;
      string kUdnGxVkCz;
      string YhXOPdQlfp;
      string eFSBBheEKs;
      string fhPVrDWCdf;
      string NXbIEiRPDh;
      string eXLkYeBcmX;
      string SQaJSpSBVL;
      string HOHzbGcKwS;
      string QOBbOHWdxN;
      string CtOGNwwSoO;
      string PPsqaPQLIR;
      string BqfUHDPztK;
      string SnEIJMABkf;
      string JKUhCAUJAy;
      string qKVeLKOszK;
      string fxXeubLkhN;
      if(eHWJZojZdR == SQaJSpSBVL){OPabHqWxSG = true;}
      else if(SQaJSpSBVL == eHWJZojZdR){umOUOkjMXh = true;}
      if(XJXWoqZpZd == HOHzbGcKwS){hGywSIRYwz = true;}
      else if(HOHzbGcKwS == XJXWoqZpZd){bDBDgtCLaN = true;}
      if(YApkdiJdHc == QOBbOHWdxN){yGBazMlpla = true;}
      else if(QOBbOHWdxN == YApkdiJdHc){CknkbnHYMD = true;}
      if(QpeTMuKqaD == CtOGNwwSoO){ojbmibjsXU = true;}
      else if(CtOGNwwSoO == QpeTMuKqaD){axhTdauJjf = true;}
      if(kUdnGxVkCz == PPsqaPQLIR){nQarcZybLm = true;}
      else if(PPsqaPQLIR == kUdnGxVkCz){SiVpyKiMuU = true;}
      if(YhXOPdQlfp == BqfUHDPztK){JlnhOINzcu = true;}
      else if(BqfUHDPztK == YhXOPdQlfp){FtHNbJzdra = true;}
      if(eFSBBheEKs == SnEIJMABkf){EfKrQxeLMq = true;}
      else if(SnEIJMABkf == eFSBBheEKs){cLzUGeVhZF = true;}
      if(fhPVrDWCdf == JKUhCAUJAy){XXBbKgfJyY = true;}
      if(NXbIEiRPDh == qKVeLKOszK){NKdzQDusXa = true;}
      if(eXLkYeBcmX == fxXeubLkhN){OjQcPHFiae = true;}
      while(JKUhCAUJAy == fhPVrDWCdf){zrbutSPxmR = true;}
      while(qKVeLKOszK == qKVeLKOszK){EtcqxgoTqT = true;}
      while(fxXeubLkhN == fxXeubLkhN){bQRICHiBjS = true;}
      if(OPabHqWxSG == true){OPabHqWxSG = false;}
      if(hGywSIRYwz == true){hGywSIRYwz = false;}
      if(yGBazMlpla == true){yGBazMlpla = false;}
      if(ojbmibjsXU == true){ojbmibjsXU = false;}
      if(nQarcZybLm == true){nQarcZybLm = false;}
      if(JlnhOINzcu == true){JlnhOINzcu = false;}
      if(EfKrQxeLMq == true){EfKrQxeLMq = false;}
      if(XXBbKgfJyY == true){XXBbKgfJyY = false;}
      if(NKdzQDusXa == true){NKdzQDusXa = false;}
      if(OjQcPHFiae == true){OjQcPHFiae = false;}
      if(umOUOkjMXh == true){umOUOkjMXh = false;}
      if(bDBDgtCLaN == true){bDBDgtCLaN = false;}
      if(CknkbnHYMD == true){CknkbnHYMD = false;}
      if(axhTdauJjf == true){axhTdauJjf = false;}
      if(SiVpyKiMuU == true){SiVpyKiMuU = false;}
      if(FtHNbJzdra == true){FtHNbJzdra = false;}
      if(cLzUGeVhZF == true){cLzUGeVhZF = false;}
      if(zrbutSPxmR == true){zrbutSPxmR = false;}
      if(EtcqxgoTqT == true){EtcqxgoTqT = false;}
      if(bQRICHiBjS == true){bQRICHiBjS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRQTZIAPBK
{ 
  void ILliHARoOO()
  { 
      bool FoEJEsFVTI = false;
      bool doIkwqZJzi = false;
      bool aTpBtqtVGU = false;
      bool ZFoTYKwNCi = false;
      bool SCWVuRXwlG = false;
      bool dNiLgkyCPM = false;
      bool yjOzhYzoLk = false;
      bool tMHQQXxTFb = false;
      bool SyjApMVcmm = false;
      bool MtyojinXnW = false;
      bool SijALRGRuI = false;
      bool nexmtAANIV = false;
      bool CVBYYANRfg = false;
      bool jZfiJjOjoX = false;
      bool GEhezhxKuj = false;
      bool hZOSTwgLaL = false;
      bool DnkNYOyNdJ = false;
      bool kQYkOynVYq = false;
      bool DDVwzJKMOM = false;
      bool CDIcTRSTGk = false;
      string MPmlTHLoil;
      string LhxBGgMqlY;
      string oxWAHrkaUX;
      string hkANRBEeSm;
      string fNeWTyxBQi;
      string HCxQSOsmda;
      string WkUKEZgijE;
      string bhXyrbSAfJ;
      string tiKlPemiuC;
      string IRAqPurTRs;
      string QNRLGZdzYq;
      string wrHUgnZitZ;
      string mynguKgghx;
      string iyhlrfQyep;
      string AnKDFPKfKb;
      string UJZrGSZjQw;
      string rwQbIyKUbA;
      string XbDEYynkae;
      string zBWGbYXpeZ;
      string GfghxEXiuH;
      if(MPmlTHLoil == QNRLGZdzYq){FoEJEsFVTI = true;}
      else if(QNRLGZdzYq == MPmlTHLoil){SijALRGRuI = true;}
      if(LhxBGgMqlY == wrHUgnZitZ){doIkwqZJzi = true;}
      else if(wrHUgnZitZ == LhxBGgMqlY){nexmtAANIV = true;}
      if(oxWAHrkaUX == mynguKgghx){aTpBtqtVGU = true;}
      else if(mynguKgghx == oxWAHrkaUX){CVBYYANRfg = true;}
      if(hkANRBEeSm == iyhlrfQyep){ZFoTYKwNCi = true;}
      else if(iyhlrfQyep == hkANRBEeSm){jZfiJjOjoX = true;}
      if(fNeWTyxBQi == AnKDFPKfKb){SCWVuRXwlG = true;}
      else if(AnKDFPKfKb == fNeWTyxBQi){GEhezhxKuj = true;}
      if(HCxQSOsmda == UJZrGSZjQw){dNiLgkyCPM = true;}
      else if(UJZrGSZjQw == HCxQSOsmda){hZOSTwgLaL = true;}
      if(WkUKEZgijE == rwQbIyKUbA){yjOzhYzoLk = true;}
      else if(rwQbIyKUbA == WkUKEZgijE){DnkNYOyNdJ = true;}
      if(bhXyrbSAfJ == XbDEYynkae){tMHQQXxTFb = true;}
      if(tiKlPemiuC == zBWGbYXpeZ){SyjApMVcmm = true;}
      if(IRAqPurTRs == GfghxEXiuH){MtyojinXnW = true;}
      while(XbDEYynkae == bhXyrbSAfJ){kQYkOynVYq = true;}
      while(zBWGbYXpeZ == zBWGbYXpeZ){DDVwzJKMOM = true;}
      while(GfghxEXiuH == GfghxEXiuH){CDIcTRSTGk = true;}
      if(FoEJEsFVTI == true){FoEJEsFVTI = false;}
      if(doIkwqZJzi == true){doIkwqZJzi = false;}
      if(aTpBtqtVGU == true){aTpBtqtVGU = false;}
      if(ZFoTYKwNCi == true){ZFoTYKwNCi = false;}
      if(SCWVuRXwlG == true){SCWVuRXwlG = false;}
      if(dNiLgkyCPM == true){dNiLgkyCPM = false;}
      if(yjOzhYzoLk == true){yjOzhYzoLk = false;}
      if(tMHQQXxTFb == true){tMHQQXxTFb = false;}
      if(SyjApMVcmm == true){SyjApMVcmm = false;}
      if(MtyojinXnW == true){MtyojinXnW = false;}
      if(SijALRGRuI == true){SijALRGRuI = false;}
      if(nexmtAANIV == true){nexmtAANIV = false;}
      if(CVBYYANRfg == true){CVBYYANRfg = false;}
      if(jZfiJjOjoX == true){jZfiJjOjoX = false;}
      if(GEhezhxKuj == true){GEhezhxKuj = false;}
      if(hZOSTwgLaL == true){hZOSTwgLaL = false;}
      if(DnkNYOyNdJ == true){DnkNYOyNdJ = false;}
      if(kQYkOynVYq == true){kQYkOynVYq = false;}
      if(DDVwzJKMOM == true){DDVwzJKMOM = false;}
      if(CDIcTRSTGk == true){CDIcTRSTGk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QJMFTUTDKZ
{ 
  void gOcuxwlcOk()
  { 
      bool EdeXnJFIjh = false;
      bool jySihJUccO = false;
      bool HbbDGhmgRD = false;
      bool EMotgkZgDf = false;
      bool WGaOcJLyaH = false;
      bool fzYQcbBaQF = false;
      bool WYqgcXIYCx = false;
      bool jmYxrBBNax = false;
      bool VoFJXEnYQE = false;
      bool iyQxJxOslF = false;
      bool BmwcXraaYa = false;
      bool anATjhSgIX = false;
      bool ijHxNlWamt = false;
      bool lHbVwhrble = false;
      bool dMzpctxxMb = false;
      bool ehkNVQfyOk = false;
      bool VAneoTMeWC = false;
      bool optcsWjRUT = false;
      bool nYNLPEWNze = false;
      bool BtNAJdYUAJ = false;
      string KPYuMeeCqB;
      string tPruwdVegu;
      string UWIjXgYHmi;
      string eGVNXmZwJx;
      string YGMofcqJHS;
      string nmwLcmHnXf;
      string FWPHVmtdXJ;
      string DZVjWNKSEu;
      string oPAUtrJJkj;
      string flYdqBpESr;
      string iMlyOORMnO;
      string cnjcqpWuNd;
      string djsmcRArrU;
      string WFALLbdCFe;
      string ZwVWHrCwlA;
      string euqnOyTyUx;
      string OZTTqWmYQO;
      string MUohDgOVek;
      string OEFqpbOLwM;
      string HehIQAbBfk;
      if(KPYuMeeCqB == iMlyOORMnO){EdeXnJFIjh = true;}
      else if(iMlyOORMnO == KPYuMeeCqB){BmwcXraaYa = true;}
      if(tPruwdVegu == cnjcqpWuNd){jySihJUccO = true;}
      else if(cnjcqpWuNd == tPruwdVegu){anATjhSgIX = true;}
      if(UWIjXgYHmi == djsmcRArrU){HbbDGhmgRD = true;}
      else if(djsmcRArrU == UWIjXgYHmi){ijHxNlWamt = true;}
      if(eGVNXmZwJx == WFALLbdCFe){EMotgkZgDf = true;}
      else if(WFALLbdCFe == eGVNXmZwJx){lHbVwhrble = true;}
      if(YGMofcqJHS == ZwVWHrCwlA){WGaOcJLyaH = true;}
      else if(ZwVWHrCwlA == YGMofcqJHS){dMzpctxxMb = true;}
      if(nmwLcmHnXf == euqnOyTyUx){fzYQcbBaQF = true;}
      else if(euqnOyTyUx == nmwLcmHnXf){ehkNVQfyOk = true;}
      if(FWPHVmtdXJ == OZTTqWmYQO){WYqgcXIYCx = true;}
      else if(OZTTqWmYQO == FWPHVmtdXJ){VAneoTMeWC = true;}
      if(DZVjWNKSEu == MUohDgOVek){jmYxrBBNax = true;}
      if(oPAUtrJJkj == OEFqpbOLwM){VoFJXEnYQE = true;}
      if(flYdqBpESr == HehIQAbBfk){iyQxJxOslF = true;}
      while(MUohDgOVek == DZVjWNKSEu){optcsWjRUT = true;}
      while(OEFqpbOLwM == OEFqpbOLwM){nYNLPEWNze = true;}
      while(HehIQAbBfk == HehIQAbBfk){BtNAJdYUAJ = true;}
      if(EdeXnJFIjh == true){EdeXnJFIjh = false;}
      if(jySihJUccO == true){jySihJUccO = false;}
      if(HbbDGhmgRD == true){HbbDGhmgRD = false;}
      if(EMotgkZgDf == true){EMotgkZgDf = false;}
      if(WGaOcJLyaH == true){WGaOcJLyaH = false;}
      if(fzYQcbBaQF == true){fzYQcbBaQF = false;}
      if(WYqgcXIYCx == true){WYqgcXIYCx = false;}
      if(jmYxrBBNax == true){jmYxrBBNax = false;}
      if(VoFJXEnYQE == true){VoFJXEnYQE = false;}
      if(iyQxJxOslF == true){iyQxJxOslF = false;}
      if(BmwcXraaYa == true){BmwcXraaYa = false;}
      if(anATjhSgIX == true){anATjhSgIX = false;}
      if(ijHxNlWamt == true){ijHxNlWamt = false;}
      if(lHbVwhrble == true){lHbVwhrble = false;}
      if(dMzpctxxMb == true){dMzpctxxMb = false;}
      if(ehkNVQfyOk == true){ehkNVQfyOk = false;}
      if(VAneoTMeWC == true){VAneoTMeWC = false;}
      if(optcsWjRUT == true){optcsWjRUT = false;}
      if(nYNLPEWNze == true){nYNLPEWNze = false;}
      if(BtNAJdYUAJ == true){BtNAJdYUAJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BDDWSCYAIJ
{ 
  void zarbDyzexf()
  { 
      bool pJUwUZAWKC = false;
      bool pXDmYbAIou = false;
      bool jgtVoqYKjE = false;
      bool SNJCbrdroI = false;
      bool SJRPRzWNaB = false;
      bool dewDsJPyHd = false;
      bool BplGicOBKg = false;
      bool xHSgcaPdEo = false;
      bool ULjiZnRFIS = false;
      bool bekLGcWLfn = false;
      bool kVCtDWMOaS = false;
      bool tktRIoGCfu = false;
      bool LIrqESVHZA = false;
      bool DDyQDzIoeC = false;
      bool bCepYpkTCR = false;
      bool VUekbccKok = false;
      bool AEnaOpmdNJ = false;
      bool gQXcTIcBSN = false;
      bool gCFIdiXMna = false;
      bool VxzsCWODbi = false;
      string OWrwSTPRWn;
      string rSJTXcZdfM;
      string iPaGXrWCGa;
      string aGqdWauACO;
      string uHxJIaiEWg;
      string yQiYVywlYa;
      string wNKuMkbewx;
      string hYbQQbSRyw;
      string ISfZcJXRIY;
      string eJabRhwCwW;
      string zDHYzYoRHt;
      string fembRdgkRD;
      string NJWXSXyzyi;
      string ePUaxEKGaE;
      string UGKNrzVzJn;
      string ALjsJogiGa;
      string apSYOPJLdN;
      string SZKNiGzIeS;
      string CzoKiTfbRH;
      string XaAzcemkzc;
      if(OWrwSTPRWn == zDHYzYoRHt){pJUwUZAWKC = true;}
      else if(zDHYzYoRHt == OWrwSTPRWn){kVCtDWMOaS = true;}
      if(rSJTXcZdfM == fembRdgkRD){pXDmYbAIou = true;}
      else if(fembRdgkRD == rSJTXcZdfM){tktRIoGCfu = true;}
      if(iPaGXrWCGa == NJWXSXyzyi){jgtVoqYKjE = true;}
      else if(NJWXSXyzyi == iPaGXrWCGa){LIrqESVHZA = true;}
      if(aGqdWauACO == ePUaxEKGaE){SNJCbrdroI = true;}
      else if(ePUaxEKGaE == aGqdWauACO){DDyQDzIoeC = true;}
      if(uHxJIaiEWg == UGKNrzVzJn){SJRPRzWNaB = true;}
      else if(UGKNrzVzJn == uHxJIaiEWg){bCepYpkTCR = true;}
      if(yQiYVywlYa == ALjsJogiGa){dewDsJPyHd = true;}
      else if(ALjsJogiGa == yQiYVywlYa){VUekbccKok = true;}
      if(wNKuMkbewx == apSYOPJLdN){BplGicOBKg = true;}
      else if(apSYOPJLdN == wNKuMkbewx){AEnaOpmdNJ = true;}
      if(hYbQQbSRyw == SZKNiGzIeS){xHSgcaPdEo = true;}
      if(ISfZcJXRIY == CzoKiTfbRH){ULjiZnRFIS = true;}
      if(eJabRhwCwW == XaAzcemkzc){bekLGcWLfn = true;}
      while(SZKNiGzIeS == hYbQQbSRyw){gQXcTIcBSN = true;}
      while(CzoKiTfbRH == CzoKiTfbRH){gCFIdiXMna = true;}
      while(XaAzcemkzc == XaAzcemkzc){VxzsCWODbi = true;}
      if(pJUwUZAWKC == true){pJUwUZAWKC = false;}
      if(pXDmYbAIou == true){pXDmYbAIou = false;}
      if(jgtVoqYKjE == true){jgtVoqYKjE = false;}
      if(SNJCbrdroI == true){SNJCbrdroI = false;}
      if(SJRPRzWNaB == true){SJRPRzWNaB = false;}
      if(dewDsJPyHd == true){dewDsJPyHd = false;}
      if(BplGicOBKg == true){BplGicOBKg = false;}
      if(xHSgcaPdEo == true){xHSgcaPdEo = false;}
      if(ULjiZnRFIS == true){ULjiZnRFIS = false;}
      if(bekLGcWLfn == true){bekLGcWLfn = false;}
      if(kVCtDWMOaS == true){kVCtDWMOaS = false;}
      if(tktRIoGCfu == true){tktRIoGCfu = false;}
      if(LIrqESVHZA == true){LIrqESVHZA = false;}
      if(DDyQDzIoeC == true){DDyQDzIoeC = false;}
      if(bCepYpkTCR == true){bCepYpkTCR = false;}
      if(VUekbccKok == true){VUekbccKok = false;}
      if(AEnaOpmdNJ == true){AEnaOpmdNJ = false;}
      if(gQXcTIcBSN == true){gQXcTIcBSN = false;}
      if(gCFIdiXMna == true){gCFIdiXMna = false;}
      if(VxzsCWODbi == true){VxzsCWODbi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FQDQDUTZMK
{ 
  void BNQYHBfRZZ()
  { 
      bool XhZlpFRSZJ = false;
      bool SEBZomzZTF = false;
      bool DCezRBULHD = false;
      bool rUsSszhmfb = false;
      bool cTQIRIeals = false;
      bool sBOVCUDaUn = false;
      bool kFLVQxKhgo = false;
      bool EMsrcjkVgI = false;
      bool WsYOJpGXQX = false;
      bool wHSrpXHtqT = false;
      bool xxtwogIVsS = false;
      bool jgtLRqfxMZ = false;
      bool qmQIsxsBBF = false;
      bool bqdMKYycZc = false;
      bool hjdynONGZz = false;
      bool qKhQcKfkDq = false;
      bool mHUnprDgAr = false;
      bool rDXjrHJSUd = false;
      bool jlaCNQIMjA = false;
      bool sMYhoaPpHu = false;
      string soTfozUrjg;
      string iltnchrrUQ;
      string NrkDQKFqQd;
      string eXCUiZqTPJ;
      string SUbmiuyBad;
      string ntFIsBDPOe;
      string tdaFBLiZED;
      string pYbLysPyUV;
      string LEPmpkRtbh;
      string VbEjPosVlX;
      string MXwXmORsKz;
      string kFusSpNnOP;
      string snxVgOTrwI;
      string ztMxImHrAa;
      string SYjbxQfKRY;
      string aFGVdXZapX;
      string uZxBAqrxje;
      string iVnmwUEVYQ;
      string hIZWgtmpSk;
      string NgBbfsbibF;
      if(soTfozUrjg == MXwXmORsKz){XhZlpFRSZJ = true;}
      else if(MXwXmORsKz == soTfozUrjg){xxtwogIVsS = true;}
      if(iltnchrrUQ == kFusSpNnOP){SEBZomzZTF = true;}
      else if(kFusSpNnOP == iltnchrrUQ){jgtLRqfxMZ = true;}
      if(NrkDQKFqQd == snxVgOTrwI){DCezRBULHD = true;}
      else if(snxVgOTrwI == NrkDQKFqQd){qmQIsxsBBF = true;}
      if(eXCUiZqTPJ == ztMxImHrAa){rUsSszhmfb = true;}
      else if(ztMxImHrAa == eXCUiZqTPJ){bqdMKYycZc = true;}
      if(SUbmiuyBad == SYjbxQfKRY){cTQIRIeals = true;}
      else if(SYjbxQfKRY == SUbmiuyBad){hjdynONGZz = true;}
      if(ntFIsBDPOe == aFGVdXZapX){sBOVCUDaUn = true;}
      else if(aFGVdXZapX == ntFIsBDPOe){qKhQcKfkDq = true;}
      if(tdaFBLiZED == uZxBAqrxje){kFLVQxKhgo = true;}
      else if(uZxBAqrxje == tdaFBLiZED){mHUnprDgAr = true;}
      if(pYbLysPyUV == iVnmwUEVYQ){EMsrcjkVgI = true;}
      if(LEPmpkRtbh == hIZWgtmpSk){WsYOJpGXQX = true;}
      if(VbEjPosVlX == NgBbfsbibF){wHSrpXHtqT = true;}
      while(iVnmwUEVYQ == pYbLysPyUV){rDXjrHJSUd = true;}
      while(hIZWgtmpSk == hIZWgtmpSk){jlaCNQIMjA = true;}
      while(NgBbfsbibF == NgBbfsbibF){sMYhoaPpHu = true;}
      if(XhZlpFRSZJ == true){XhZlpFRSZJ = false;}
      if(SEBZomzZTF == true){SEBZomzZTF = false;}
      if(DCezRBULHD == true){DCezRBULHD = false;}
      if(rUsSszhmfb == true){rUsSszhmfb = false;}
      if(cTQIRIeals == true){cTQIRIeals = false;}
      if(sBOVCUDaUn == true){sBOVCUDaUn = false;}
      if(kFLVQxKhgo == true){kFLVQxKhgo = false;}
      if(EMsrcjkVgI == true){EMsrcjkVgI = false;}
      if(WsYOJpGXQX == true){WsYOJpGXQX = false;}
      if(wHSrpXHtqT == true){wHSrpXHtqT = false;}
      if(xxtwogIVsS == true){xxtwogIVsS = false;}
      if(jgtLRqfxMZ == true){jgtLRqfxMZ = false;}
      if(qmQIsxsBBF == true){qmQIsxsBBF = false;}
      if(bqdMKYycZc == true){bqdMKYycZc = false;}
      if(hjdynONGZz == true){hjdynONGZz = false;}
      if(qKhQcKfkDq == true){qKhQcKfkDq = false;}
      if(mHUnprDgAr == true){mHUnprDgAr = false;}
      if(rDXjrHJSUd == true){rDXjrHJSUd = false;}
      if(jlaCNQIMjA == true){jlaCNQIMjA = false;}
      if(sMYhoaPpHu == true){sMYhoaPpHu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WYBEMVOMPV
{ 
  void HZFpRKzWOn()
  { 
      bool SQqnXiOOtB = false;
      bool MtimtPyplk = false;
      bool aPDXxWWIQo = false;
      bool KSHLXEpDKw = false;
      bool zgkSabVROu = false;
      bool bUyEBDMSpB = false;
      bool MGyFqslXPo = false;
      bool ZtfpktdjxV = false;
      bool AFtUMpTDKT = false;
      bool qWMIishebg = false;
      bool oxCYUgnISG = false;
      bool ZcUUBHLcrA = false;
      bool ZiNuyCgXGr = false;
      bool LyHQfCDUAf = false;
      bool CKjDtNBrHb = false;
      bool gFlbGGjGZR = false;
      bool zPBZtaUEny = false;
      bool DpbMxOyJBj = false;
      bool AoPeLGLfJZ = false;
      bool SwuhflJKJS = false;
      string gemEFehWDR;
      string izHQZMIshJ;
      string SNKyPknGla;
      string flgnYUuGHu;
      string xECcbouBnp;
      string jZtUGSTooU;
      string qbjblxSSrF;
      string QBkmMNLhWZ;
      string olRwqFqLgF;
      string AGRlEVTaqd;
      string WcJiYhnHIs;
      string HlROfEKnjf;
      string FGklEJjyhp;
      string tkpsDMchWI;
      string QjDnyOoCGA;
      string KfpKXPqWdO;
      string xpYRzVuYLS;
      string bbQbPVDxmp;
      string UgqheNufUm;
      string VFEILaKkob;
      if(gemEFehWDR == WcJiYhnHIs){SQqnXiOOtB = true;}
      else if(WcJiYhnHIs == gemEFehWDR){oxCYUgnISG = true;}
      if(izHQZMIshJ == HlROfEKnjf){MtimtPyplk = true;}
      else if(HlROfEKnjf == izHQZMIshJ){ZcUUBHLcrA = true;}
      if(SNKyPknGla == FGklEJjyhp){aPDXxWWIQo = true;}
      else if(FGklEJjyhp == SNKyPknGla){ZiNuyCgXGr = true;}
      if(flgnYUuGHu == tkpsDMchWI){KSHLXEpDKw = true;}
      else if(tkpsDMchWI == flgnYUuGHu){LyHQfCDUAf = true;}
      if(xECcbouBnp == QjDnyOoCGA){zgkSabVROu = true;}
      else if(QjDnyOoCGA == xECcbouBnp){CKjDtNBrHb = true;}
      if(jZtUGSTooU == KfpKXPqWdO){bUyEBDMSpB = true;}
      else if(KfpKXPqWdO == jZtUGSTooU){gFlbGGjGZR = true;}
      if(qbjblxSSrF == xpYRzVuYLS){MGyFqslXPo = true;}
      else if(xpYRzVuYLS == qbjblxSSrF){zPBZtaUEny = true;}
      if(QBkmMNLhWZ == bbQbPVDxmp){ZtfpktdjxV = true;}
      if(olRwqFqLgF == UgqheNufUm){AFtUMpTDKT = true;}
      if(AGRlEVTaqd == VFEILaKkob){qWMIishebg = true;}
      while(bbQbPVDxmp == QBkmMNLhWZ){DpbMxOyJBj = true;}
      while(UgqheNufUm == UgqheNufUm){AoPeLGLfJZ = true;}
      while(VFEILaKkob == VFEILaKkob){SwuhflJKJS = true;}
      if(SQqnXiOOtB == true){SQqnXiOOtB = false;}
      if(MtimtPyplk == true){MtimtPyplk = false;}
      if(aPDXxWWIQo == true){aPDXxWWIQo = false;}
      if(KSHLXEpDKw == true){KSHLXEpDKw = false;}
      if(zgkSabVROu == true){zgkSabVROu = false;}
      if(bUyEBDMSpB == true){bUyEBDMSpB = false;}
      if(MGyFqslXPo == true){MGyFqslXPo = false;}
      if(ZtfpktdjxV == true){ZtfpktdjxV = false;}
      if(AFtUMpTDKT == true){AFtUMpTDKT = false;}
      if(qWMIishebg == true){qWMIishebg = false;}
      if(oxCYUgnISG == true){oxCYUgnISG = false;}
      if(ZcUUBHLcrA == true){ZcUUBHLcrA = false;}
      if(ZiNuyCgXGr == true){ZiNuyCgXGr = false;}
      if(LyHQfCDUAf == true){LyHQfCDUAf = false;}
      if(CKjDtNBrHb == true){CKjDtNBrHb = false;}
      if(gFlbGGjGZR == true){gFlbGGjGZR = false;}
      if(zPBZtaUEny == true){zPBZtaUEny = false;}
      if(DpbMxOyJBj == true){DpbMxOyJBj = false;}
      if(AoPeLGLfJZ == true){AoPeLGLfJZ = false;}
      if(SwuhflJKJS == true){SwuhflJKJS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NZXTUBBOGB
{ 
  void JjRcfIkMGI()
  { 
      bool XbAmIdPtkD = false;
      bool hVtAYMiqyz = false;
      bool cFmUeqXsNG = false;
      bool ZWyqslKIqz = false;
      bool KchwWluFpf = false;
      bool CgMZTRnfIR = false;
      bool GVgecLWDHl = false;
      bool BazyoAXqxr = false;
      bool wSDhEsJYXa = false;
      bool yezZsnwCTL = false;
      bool PrxEdagOjT = false;
      bool txhQVmSyaj = false;
      bool BxefmWaZEA = false;
      bool DVXkbDUzDc = false;
      bool LtoDgAwiDG = false;
      bool VxajJRMQQG = false;
      bool AGKjPYZxnR = false;
      bool RStxXHIbzm = false;
      bool aqVydGtmaJ = false;
      bool qEixcEiEnI = false;
      string rutMmoYymb;
      string XjTMErZKnM;
      string sTqoMdjSTp;
      string DOMayWJTYB;
      string QMVJYHKlNA;
      string PlSKDXDFzI;
      string EGdxXIWsNh;
      string hGklwfxhQF;
      string TyETZQuBWZ;
      string SEUPwJhYkP;
      string kQXfRJAfOX;
      string aVntoGBKWH;
      string NUWnOdkVol;
      string yYwBUCZXCQ;
      string POmyzxPZZp;
      string IXBcBPtjRm;
      string XeqbZBYmZm;
      string gdIGqyhXoQ;
      string OLuzdZXTzE;
      string IpFOrkXLYx;
      if(rutMmoYymb == kQXfRJAfOX){XbAmIdPtkD = true;}
      else if(kQXfRJAfOX == rutMmoYymb){PrxEdagOjT = true;}
      if(XjTMErZKnM == aVntoGBKWH){hVtAYMiqyz = true;}
      else if(aVntoGBKWH == XjTMErZKnM){txhQVmSyaj = true;}
      if(sTqoMdjSTp == NUWnOdkVol){cFmUeqXsNG = true;}
      else if(NUWnOdkVol == sTqoMdjSTp){BxefmWaZEA = true;}
      if(DOMayWJTYB == yYwBUCZXCQ){ZWyqslKIqz = true;}
      else if(yYwBUCZXCQ == DOMayWJTYB){DVXkbDUzDc = true;}
      if(QMVJYHKlNA == POmyzxPZZp){KchwWluFpf = true;}
      else if(POmyzxPZZp == QMVJYHKlNA){LtoDgAwiDG = true;}
      if(PlSKDXDFzI == IXBcBPtjRm){CgMZTRnfIR = true;}
      else if(IXBcBPtjRm == PlSKDXDFzI){VxajJRMQQG = true;}
      if(EGdxXIWsNh == XeqbZBYmZm){GVgecLWDHl = true;}
      else if(XeqbZBYmZm == EGdxXIWsNh){AGKjPYZxnR = true;}
      if(hGklwfxhQF == gdIGqyhXoQ){BazyoAXqxr = true;}
      if(TyETZQuBWZ == OLuzdZXTzE){wSDhEsJYXa = true;}
      if(SEUPwJhYkP == IpFOrkXLYx){yezZsnwCTL = true;}
      while(gdIGqyhXoQ == hGklwfxhQF){RStxXHIbzm = true;}
      while(OLuzdZXTzE == OLuzdZXTzE){aqVydGtmaJ = true;}
      while(IpFOrkXLYx == IpFOrkXLYx){qEixcEiEnI = true;}
      if(XbAmIdPtkD == true){XbAmIdPtkD = false;}
      if(hVtAYMiqyz == true){hVtAYMiqyz = false;}
      if(cFmUeqXsNG == true){cFmUeqXsNG = false;}
      if(ZWyqslKIqz == true){ZWyqslKIqz = false;}
      if(KchwWluFpf == true){KchwWluFpf = false;}
      if(CgMZTRnfIR == true){CgMZTRnfIR = false;}
      if(GVgecLWDHl == true){GVgecLWDHl = false;}
      if(BazyoAXqxr == true){BazyoAXqxr = false;}
      if(wSDhEsJYXa == true){wSDhEsJYXa = false;}
      if(yezZsnwCTL == true){yezZsnwCTL = false;}
      if(PrxEdagOjT == true){PrxEdagOjT = false;}
      if(txhQVmSyaj == true){txhQVmSyaj = false;}
      if(BxefmWaZEA == true){BxefmWaZEA = false;}
      if(DVXkbDUzDc == true){DVXkbDUzDc = false;}
      if(LtoDgAwiDG == true){LtoDgAwiDG = false;}
      if(VxajJRMQQG == true){VxajJRMQQG = false;}
      if(AGKjPYZxnR == true){AGKjPYZxnR = false;}
      if(RStxXHIbzm == true){RStxXHIbzm = false;}
      if(aqVydGtmaJ == true){aqVydGtmaJ = false;}
      if(qEixcEiEnI == true){qEixcEiEnI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XJRTFDPSOZ
{ 
  void UtMWkrCfsV()
  { 
      bool tNxgYWjJcV = false;
      bool lxldAyrQGq = false;
      bool taeTFYQbrj = false;
      bool QeFuzqQIFO = false;
      bool rEbxgAgdaJ = false;
      bool ZczqJSicbA = false;
      bool FHQsFGrqeJ = false;
      bool gjLqzozgmE = false;
      bool qmBiJmfNkf = false;
      bool ImgFIjmirZ = false;
      bool IpyRboRHrU = false;
      bool TBpWJSGhiR = false;
      bool ZeGzAtDFhO = false;
      bool BPoMwAniGT = false;
      bool VYUQMGwJwp = false;
      bool dFzZzdjzQh = false;
      bool lLYcSDMdaI = false;
      bool dWaOwBJolt = false;
      bool xsJrjwPOMS = false;
      bool QoRYhJzqxI = false;
      string LsflSwGFzW;
      string QppYlauTVN;
      string LeKyMSycLz;
      string MhhMXaulWL;
      string eUcrPPFxEE;
      string UEBJafihZz;
      string xdszKhIcBL;
      string fJxJiqBRhx;
      string MAYHeHgYlq;
      string qMLWOBadhg;
      string GcurYKHqZi;
      string eQzcmxFlUC;
      string AjqKTSxZuh;
      string PWjApjEfhU;
      string ApyCLaMijQ;
      string unJegWlkXG;
      string MhurTHfylD;
      string rYEACKknys;
      string FNodlbNFTS;
      string yTIbHStFiD;
      if(LsflSwGFzW == GcurYKHqZi){tNxgYWjJcV = true;}
      else if(GcurYKHqZi == LsflSwGFzW){IpyRboRHrU = true;}
      if(QppYlauTVN == eQzcmxFlUC){lxldAyrQGq = true;}
      else if(eQzcmxFlUC == QppYlauTVN){TBpWJSGhiR = true;}
      if(LeKyMSycLz == AjqKTSxZuh){taeTFYQbrj = true;}
      else if(AjqKTSxZuh == LeKyMSycLz){ZeGzAtDFhO = true;}
      if(MhhMXaulWL == PWjApjEfhU){QeFuzqQIFO = true;}
      else if(PWjApjEfhU == MhhMXaulWL){BPoMwAniGT = true;}
      if(eUcrPPFxEE == ApyCLaMijQ){rEbxgAgdaJ = true;}
      else if(ApyCLaMijQ == eUcrPPFxEE){VYUQMGwJwp = true;}
      if(UEBJafihZz == unJegWlkXG){ZczqJSicbA = true;}
      else if(unJegWlkXG == UEBJafihZz){dFzZzdjzQh = true;}
      if(xdszKhIcBL == MhurTHfylD){FHQsFGrqeJ = true;}
      else if(MhurTHfylD == xdszKhIcBL){lLYcSDMdaI = true;}
      if(fJxJiqBRhx == rYEACKknys){gjLqzozgmE = true;}
      if(MAYHeHgYlq == FNodlbNFTS){qmBiJmfNkf = true;}
      if(qMLWOBadhg == yTIbHStFiD){ImgFIjmirZ = true;}
      while(rYEACKknys == fJxJiqBRhx){dWaOwBJolt = true;}
      while(FNodlbNFTS == FNodlbNFTS){xsJrjwPOMS = true;}
      while(yTIbHStFiD == yTIbHStFiD){QoRYhJzqxI = true;}
      if(tNxgYWjJcV == true){tNxgYWjJcV = false;}
      if(lxldAyrQGq == true){lxldAyrQGq = false;}
      if(taeTFYQbrj == true){taeTFYQbrj = false;}
      if(QeFuzqQIFO == true){QeFuzqQIFO = false;}
      if(rEbxgAgdaJ == true){rEbxgAgdaJ = false;}
      if(ZczqJSicbA == true){ZczqJSicbA = false;}
      if(FHQsFGrqeJ == true){FHQsFGrqeJ = false;}
      if(gjLqzozgmE == true){gjLqzozgmE = false;}
      if(qmBiJmfNkf == true){qmBiJmfNkf = false;}
      if(ImgFIjmirZ == true){ImgFIjmirZ = false;}
      if(IpyRboRHrU == true){IpyRboRHrU = false;}
      if(TBpWJSGhiR == true){TBpWJSGhiR = false;}
      if(ZeGzAtDFhO == true){ZeGzAtDFhO = false;}
      if(BPoMwAniGT == true){BPoMwAniGT = false;}
      if(VYUQMGwJwp == true){VYUQMGwJwp = false;}
      if(dFzZzdjzQh == true){dFzZzdjzQh = false;}
      if(lLYcSDMdaI == true){lLYcSDMdaI = false;}
      if(dWaOwBJolt == true){dWaOwBJolt = false;}
      if(xsJrjwPOMS == true){xsJrjwPOMS = false;}
      if(QoRYhJzqxI == true){QoRYhJzqxI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NUQRCXRHLA
{ 
  void KEWMRLpGxl()
  { 
      bool IhSbNLSWWs = false;
      bool yFyTUYzfkp = false;
      bool eTjRBtmMSb = false;
      bool CQBATeLwOB = false;
      bool oVeBAlOiBK = false;
      bool PtwrHoxBaT = false;
      bool YGEuqgDxzo = false;
      bool NCRiBInhQP = false;
      bool fDLHLHUJsd = false;
      bool gKVtciRjKS = false;
      bool hQjLxNcMqy = false;
      bool BOjLmVtwii = false;
      bool MtDUIDfWGR = false;
      bool pDXxhOSAKy = false;
      bool eHRucRZKGG = false;
      bool oVAaGmNOCt = false;
      bool gGFZHxqlcY = false;
      bool CslkDEbIrp = false;
      bool cVPzcUDwqt = false;
      bool BExPQYBrmf = false;
      string QYhKmsYuNw;
      string TqQcdwjJfr;
      string fogiaRKeBW;
      string MSQCdHKdSI;
      string kgGZiDXfar;
      string VIdUJaqyjV;
      string istpiAaNzW;
      string lGpXGyiGAX;
      string sdDIBEousC;
      string PLtxZqmPqh;
      string cKgEGORGOK;
      string rkyLbEokod;
      string LeTwHZMsxP;
      string KTPSuixzCl;
      string migiJeNhUU;
      string BCZNWxqjwg;
      string CXIyzXVfPs;
      string GpiCqcyklc;
      string MdYcNIsBuy;
      string qMDVjOZhil;
      if(QYhKmsYuNw == cKgEGORGOK){IhSbNLSWWs = true;}
      else if(cKgEGORGOK == QYhKmsYuNw){hQjLxNcMqy = true;}
      if(TqQcdwjJfr == rkyLbEokod){yFyTUYzfkp = true;}
      else if(rkyLbEokod == TqQcdwjJfr){BOjLmVtwii = true;}
      if(fogiaRKeBW == LeTwHZMsxP){eTjRBtmMSb = true;}
      else if(LeTwHZMsxP == fogiaRKeBW){MtDUIDfWGR = true;}
      if(MSQCdHKdSI == KTPSuixzCl){CQBATeLwOB = true;}
      else if(KTPSuixzCl == MSQCdHKdSI){pDXxhOSAKy = true;}
      if(kgGZiDXfar == migiJeNhUU){oVeBAlOiBK = true;}
      else if(migiJeNhUU == kgGZiDXfar){eHRucRZKGG = true;}
      if(VIdUJaqyjV == BCZNWxqjwg){PtwrHoxBaT = true;}
      else if(BCZNWxqjwg == VIdUJaqyjV){oVAaGmNOCt = true;}
      if(istpiAaNzW == CXIyzXVfPs){YGEuqgDxzo = true;}
      else if(CXIyzXVfPs == istpiAaNzW){gGFZHxqlcY = true;}
      if(lGpXGyiGAX == GpiCqcyklc){NCRiBInhQP = true;}
      if(sdDIBEousC == MdYcNIsBuy){fDLHLHUJsd = true;}
      if(PLtxZqmPqh == qMDVjOZhil){gKVtciRjKS = true;}
      while(GpiCqcyklc == lGpXGyiGAX){CslkDEbIrp = true;}
      while(MdYcNIsBuy == MdYcNIsBuy){cVPzcUDwqt = true;}
      while(qMDVjOZhil == qMDVjOZhil){BExPQYBrmf = true;}
      if(IhSbNLSWWs == true){IhSbNLSWWs = false;}
      if(yFyTUYzfkp == true){yFyTUYzfkp = false;}
      if(eTjRBtmMSb == true){eTjRBtmMSb = false;}
      if(CQBATeLwOB == true){CQBATeLwOB = false;}
      if(oVeBAlOiBK == true){oVeBAlOiBK = false;}
      if(PtwrHoxBaT == true){PtwrHoxBaT = false;}
      if(YGEuqgDxzo == true){YGEuqgDxzo = false;}
      if(NCRiBInhQP == true){NCRiBInhQP = false;}
      if(fDLHLHUJsd == true){fDLHLHUJsd = false;}
      if(gKVtciRjKS == true){gKVtciRjKS = false;}
      if(hQjLxNcMqy == true){hQjLxNcMqy = false;}
      if(BOjLmVtwii == true){BOjLmVtwii = false;}
      if(MtDUIDfWGR == true){MtDUIDfWGR = false;}
      if(pDXxhOSAKy == true){pDXxhOSAKy = false;}
      if(eHRucRZKGG == true){eHRucRZKGG = false;}
      if(oVAaGmNOCt == true){oVAaGmNOCt = false;}
      if(gGFZHxqlcY == true){gGFZHxqlcY = false;}
      if(CslkDEbIrp == true){CslkDEbIrp = false;}
      if(cVPzcUDwqt == true){cVPzcUDwqt = false;}
      if(BExPQYBrmf == true){BExPQYBrmf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LUNJJMQVQQ
{ 
  void AKfyHnOTrH()
  { 
      bool gWuxYcssBE = false;
      bool eETfRMFbKS = false;
      bool DaGhonrYQi = false;
      bool SfWpffWQTS = false;
      bool RdGqyeJsKZ = false;
      bool apaMQGPMHk = false;
      bool jUcSlygcAk = false;
      bool onHqBZTOjK = false;
      bool dzOpIbFJZZ = false;
      bool QJJiiwAnFz = false;
      bool xgsYklijKq = false;
      bool lBcxGjGmJJ = false;
      bool sXCZUeeXHE = false;
      bool YeIkMxFoEW = false;
      bool sUyimOgLcy = false;
      bool pNewFZdSEF = false;
      bool GKcGRGrrjI = false;
      bool eQhmPXYTmF = false;
      bool ySuINKAMem = false;
      bool SlkzPirrQf = false;
      string fLYzMtjffn;
      string SIiclyZeic;
      string iwyhimcKlp;
      string YAKbckGIKh;
      string FkItgDbjWq;
      string UWGVgjMpQZ;
      string RYspPSyHzB;
      string rQUAXxmEBe;
      string KrnuUBsots;
      string XPrkQfrReO;
      string FUkVyDCFxj;
      string xIokOYkxUN;
      string YINGccYijq;
      string FUYlZpHSxR;
      string ymqKwPZGVq;
      string utxQpwGdrU;
      string eSUGdbiDLY;
      string RSADOkRCKM;
      string DRNswKXIwc;
      string icZbmfRkfT;
      if(fLYzMtjffn == FUkVyDCFxj){gWuxYcssBE = true;}
      else if(FUkVyDCFxj == fLYzMtjffn){xgsYklijKq = true;}
      if(SIiclyZeic == xIokOYkxUN){eETfRMFbKS = true;}
      else if(xIokOYkxUN == SIiclyZeic){lBcxGjGmJJ = true;}
      if(iwyhimcKlp == YINGccYijq){DaGhonrYQi = true;}
      else if(YINGccYijq == iwyhimcKlp){sXCZUeeXHE = true;}
      if(YAKbckGIKh == FUYlZpHSxR){SfWpffWQTS = true;}
      else if(FUYlZpHSxR == YAKbckGIKh){YeIkMxFoEW = true;}
      if(FkItgDbjWq == ymqKwPZGVq){RdGqyeJsKZ = true;}
      else if(ymqKwPZGVq == FkItgDbjWq){sUyimOgLcy = true;}
      if(UWGVgjMpQZ == utxQpwGdrU){apaMQGPMHk = true;}
      else if(utxQpwGdrU == UWGVgjMpQZ){pNewFZdSEF = true;}
      if(RYspPSyHzB == eSUGdbiDLY){jUcSlygcAk = true;}
      else if(eSUGdbiDLY == RYspPSyHzB){GKcGRGrrjI = true;}
      if(rQUAXxmEBe == RSADOkRCKM){onHqBZTOjK = true;}
      if(KrnuUBsots == DRNswKXIwc){dzOpIbFJZZ = true;}
      if(XPrkQfrReO == icZbmfRkfT){QJJiiwAnFz = true;}
      while(RSADOkRCKM == rQUAXxmEBe){eQhmPXYTmF = true;}
      while(DRNswKXIwc == DRNswKXIwc){ySuINKAMem = true;}
      while(icZbmfRkfT == icZbmfRkfT){SlkzPirrQf = true;}
      if(gWuxYcssBE == true){gWuxYcssBE = false;}
      if(eETfRMFbKS == true){eETfRMFbKS = false;}
      if(DaGhonrYQi == true){DaGhonrYQi = false;}
      if(SfWpffWQTS == true){SfWpffWQTS = false;}
      if(RdGqyeJsKZ == true){RdGqyeJsKZ = false;}
      if(apaMQGPMHk == true){apaMQGPMHk = false;}
      if(jUcSlygcAk == true){jUcSlygcAk = false;}
      if(onHqBZTOjK == true){onHqBZTOjK = false;}
      if(dzOpIbFJZZ == true){dzOpIbFJZZ = false;}
      if(QJJiiwAnFz == true){QJJiiwAnFz = false;}
      if(xgsYklijKq == true){xgsYklijKq = false;}
      if(lBcxGjGmJJ == true){lBcxGjGmJJ = false;}
      if(sXCZUeeXHE == true){sXCZUeeXHE = false;}
      if(YeIkMxFoEW == true){YeIkMxFoEW = false;}
      if(sUyimOgLcy == true){sUyimOgLcy = false;}
      if(pNewFZdSEF == true){pNewFZdSEF = false;}
      if(GKcGRGrrjI == true){GKcGRGrrjI = false;}
      if(eQhmPXYTmF == true){eQhmPXYTmF = false;}
      if(ySuINKAMem == true){ySuINKAMem = false;}
      if(SlkzPirrQf == true){SlkzPirrQf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNFBGRVNYR
{ 
  void BrEAAlHGtr()
  { 
      bool XuTBOKSlrg = false;
      bool OTqFsxTXxg = false;
      bool NhzQOgPJFF = false;
      bool TKXqexJOZK = false;
      bool hJPDStShlH = false;
      bool mskFAowDlg = false;
      bool uIflMDwAaw = false;
      bool nEylyDSwxT = false;
      bool OgXxSZZRpo = false;
      bool BFbrPYddpP = false;
      bool ySHoShtyGx = false;
      bool WAGSSNkhTl = false;
      bool ddJkuicGWZ = false;
      bool ZoFhUuYhej = false;
      bool faKsSBzIZB = false;
      bool muJEkUIWtj = false;
      bool FnbgWhtXyW = false;
      bool oDDiGCSQRt = false;
      bool jTgUleeBwA = false;
      bool mCmudqzdVk = false;
      string sRofWpGQYK;
      string qLRJUesQis;
      string cMuSxzKfed;
      string opLbGlnoWj;
      string qCgbhDycIB;
      string aVFGQgVWhW;
      string eZltUAAoDh;
      string pDszCZeSjs;
      string BgXdDSkFKZ;
      string QRHzEQQmGh;
      string DIZZKWcGDq;
      string BClnVyBIqC;
      string PudcQXwstk;
      string JrMCprGxSf;
      string pdBTXNeSdG;
      string OIwERIdwIl;
      string aiMSgJpjyc;
      string qEoKMksKFD;
      string scPnVAuHjh;
      string OKnfFGRhlO;
      if(sRofWpGQYK == DIZZKWcGDq){XuTBOKSlrg = true;}
      else if(DIZZKWcGDq == sRofWpGQYK){ySHoShtyGx = true;}
      if(qLRJUesQis == BClnVyBIqC){OTqFsxTXxg = true;}
      else if(BClnVyBIqC == qLRJUesQis){WAGSSNkhTl = true;}
      if(cMuSxzKfed == PudcQXwstk){NhzQOgPJFF = true;}
      else if(PudcQXwstk == cMuSxzKfed){ddJkuicGWZ = true;}
      if(opLbGlnoWj == JrMCprGxSf){TKXqexJOZK = true;}
      else if(JrMCprGxSf == opLbGlnoWj){ZoFhUuYhej = true;}
      if(qCgbhDycIB == pdBTXNeSdG){hJPDStShlH = true;}
      else if(pdBTXNeSdG == qCgbhDycIB){faKsSBzIZB = true;}
      if(aVFGQgVWhW == OIwERIdwIl){mskFAowDlg = true;}
      else if(OIwERIdwIl == aVFGQgVWhW){muJEkUIWtj = true;}
      if(eZltUAAoDh == aiMSgJpjyc){uIflMDwAaw = true;}
      else if(aiMSgJpjyc == eZltUAAoDh){FnbgWhtXyW = true;}
      if(pDszCZeSjs == qEoKMksKFD){nEylyDSwxT = true;}
      if(BgXdDSkFKZ == scPnVAuHjh){OgXxSZZRpo = true;}
      if(QRHzEQQmGh == OKnfFGRhlO){BFbrPYddpP = true;}
      while(qEoKMksKFD == pDszCZeSjs){oDDiGCSQRt = true;}
      while(scPnVAuHjh == scPnVAuHjh){jTgUleeBwA = true;}
      while(OKnfFGRhlO == OKnfFGRhlO){mCmudqzdVk = true;}
      if(XuTBOKSlrg == true){XuTBOKSlrg = false;}
      if(OTqFsxTXxg == true){OTqFsxTXxg = false;}
      if(NhzQOgPJFF == true){NhzQOgPJFF = false;}
      if(TKXqexJOZK == true){TKXqexJOZK = false;}
      if(hJPDStShlH == true){hJPDStShlH = false;}
      if(mskFAowDlg == true){mskFAowDlg = false;}
      if(uIflMDwAaw == true){uIflMDwAaw = false;}
      if(nEylyDSwxT == true){nEylyDSwxT = false;}
      if(OgXxSZZRpo == true){OgXxSZZRpo = false;}
      if(BFbrPYddpP == true){BFbrPYddpP = false;}
      if(ySHoShtyGx == true){ySHoShtyGx = false;}
      if(WAGSSNkhTl == true){WAGSSNkhTl = false;}
      if(ddJkuicGWZ == true){ddJkuicGWZ = false;}
      if(ZoFhUuYhej == true){ZoFhUuYhej = false;}
      if(faKsSBzIZB == true){faKsSBzIZB = false;}
      if(muJEkUIWtj == true){muJEkUIWtj = false;}
      if(FnbgWhtXyW == true){FnbgWhtXyW = false;}
      if(oDDiGCSQRt == true){oDDiGCSQRt = false;}
      if(jTgUleeBwA == true){jTgUleeBwA = false;}
      if(mCmudqzdVk == true){mCmudqzdVk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GCJOCKRDNA
{ 
  void xTszNiVXlg()
  { 
      bool ikYBKUkXsE = false;
      bool pWebTNAKws = false;
      bool kyIecHxtbe = false;
      bool RCTFfKsKyw = false;
      bool LBehjPPPcU = false;
      bool DaszFkbsXC = false;
      bool XpwNmnDYwI = false;
      bool UpLAhiSauN = false;
      bool rgRHbpIUzt = false;
      bool hzlwYUFQtu = false;
      bool MpTTANPrQW = false;
      bool RBxKKpYnlx = false;
      bool eiZBaUDPbM = false;
      bool cBfABBNyGO = false;
      bool ZQDcbgCblh = false;
      bool uQexPcQSsf = false;
      bool JzQDsQUxJI = false;
      bool cahXWOfwYs = false;
      bool RadsQMWijX = false;
      bool jtFaEazziL = false;
      string aJeHNIcBSe;
      string pmHceXicJS;
      string ooHdFXoHuE;
      string bnxOIfYttD;
      string FlWeSSWtLq;
      string PXtDRlBBBo;
      string TUGNDCorUz;
      string zoiFMDRcKl;
      string BuuDoEstxV;
      string dWsFjjeIbQ;
      string deZMqaonpO;
      string TXpOmXYCYy;
      string IuuyUbucVc;
      string YJBtIWViLN;
      string PEDhBFgdRM;
      string KbicHhiaqP;
      string eLSNpKWuFQ;
      string CpqKiDrMwO;
      string uRLIRwZYmZ;
      string mtrwiDlorq;
      if(aJeHNIcBSe == deZMqaonpO){ikYBKUkXsE = true;}
      else if(deZMqaonpO == aJeHNIcBSe){MpTTANPrQW = true;}
      if(pmHceXicJS == TXpOmXYCYy){pWebTNAKws = true;}
      else if(TXpOmXYCYy == pmHceXicJS){RBxKKpYnlx = true;}
      if(ooHdFXoHuE == IuuyUbucVc){kyIecHxtbe = true;}
      else if(IuuyUbucVc == ooHdFXoHuE){eiZBaUDPbM = true;}
      if(bnxOIfYttD == YJBtIWViLN){RCTFfKsKyw = true;}
      else if(YJBtIWViLN == bnxOIfYttD){cBfABBNyGO = true;}
      if(FlWeSSWtLq == PEDhBFgdRM){LBehjPPPcU = true;}
      else if(PEDhBFgdRM == FlWeSSWtLq){ZQDcbgCblh = true;}
      if(PXtDRlBBBo == KbicHhiaqP){DaszFkbsXC = true;}
      else if(KbicHhiaqP == PXtDRlBBBo){uQexPcQSsf = true;}
      if(TUGNDCorUz == eLSNpKWuFQ){XpwNmnDYwI = true;}
      else if(eLSNpKWuFQ == TUGNDCorUz){JzQDsQUxJI = true;}
      if(zoiFMDRcKl == CpqKiDrMwO){UpLAhiSauN = true;}
      if(BuuDoEstxV == uRLIRwZYmZ){rgRHbpIUzt = true;}
      if(dWsFjjeIbQ == mtrwiDlorq){hzlwYUFQtu = true;}
      while(CpqKiDrMwO == zoiFMDRcKl){cahXWOfwYs = true;}
      while(uRLIRwZYmZ == uRLIRwZYmZ){RadsQMWijX = true;}
      while(mtrwiDlorq == mtrwiDlorq){jtFaEazziL = true;}
      if(ikYBKUkXsE == true){ikYBKUkXsE = false;}
      if(pWebTNAKws == true){pWebTNAKws = false;}
      if(kyIecHxtbe == true){kyIecHxtbe = false;}
      if(RCTFfKsKyw == true){RCTFfKsKyw = false;}
      if(LBehjPPPcU == true){LBehjPPPcU = false;}
      if(DaszFkbsXC == true){DaszFkbsXC = false;}
      if(XpwNmnDYwI == true){XpwNmnDYwI = false;}
      if(UpLAhiSauN == true){UpLAhiSauN = false;}
      if(rgRHbpIUzt == true){rgRHbpIUzt = false;}
      if(hzlwYUFQtu == true){hzlwYUFQtu = false;}
      if(MpTTANPrQW == true){MpTTANPrQW = false;}
      if(RBxKKpYnlx == true){RBxKKpYnlx = false;}
      if(eiZBaUDPbM == true){eiZBaUDPbM = false;}
      if(cBfABBNyGO == true){cBfABBNyGO = false;}
      if(ZQDcbgCblh == true){ZQDcbgCblh = false;}
      if(uQexPcQSsf == true){uQexPcQSsf = false;}
      if(JzQDsQUxJI == true){JzQDsQUxJI = false;}
      if(cahXWOfwYs == true){cahXWOfwYs = false;}
      if(RadsQMWijX == true){RadsQMWijX = false;}
      if(jtFaEazziL == true){jtFaEazziL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TAGPYWQZPZ
{ 
  void MwkpLachqJ()
  { 
      bool IKVaJiTwke = false;
      bool FMAZnYpHAG = false;
      bool PfyPDhhhDS = false;
      bool fPhCmksEgh = false;
      bool dqCCpQeStS = false;
      bool XLUxqcLFWa = false;
      bool AlrRypeymD = false;
      bool elZRcYcwZm = false;
      bool DPnktUtjKK = false;
      bool YmgFhqykDz = false;
      bool lgepmlkDUS = false;
      bool zOfjXjyHWd = false;
      bool utmbeqEUik = false;
      bool ZrsZAWjxxI = false;
      bool iqPqKJHxgx = false;
      bool sqOZErsCLu = false;
      bool hQTirHVGiB = false;
      bool zAJOtEewRU = false;
      bool jHnkridSVI = false;
      bool cglBaSWfyD = false;
      string uHoLylcCST;
      string OGbtrwBHee;
      string sLprONPcda;
      string HVDjeScaCt;
      string BrLymPnuSo;
      string KNuWniRwwj;
      string WAXqMrDrPY;
      string SaFjcBzrFy;
      string ZUJoPsafuu;
      string BgdRXBTTlt;
      string MwetVjIKsl;
      string iZpxKBqibS;
      string QWwUXlwmMb;
      string hfGKlcoPSf;
      string kQlJLbpgHV;
      string KjrSdpzJVj;
      string nVxREDSeLg;
      string MbQuhzjmJw;
      string uOepRxmmgu;
      string ceshqOSUEH;
      if(uHoLylcCST == MwetVjIKsl){IKVaJiTwke = true;}
      else if(MwetVjIKsl == uHoLylcCST){lgepmlkDUS = true;}
      if(OGbtrwBHee == iZpxKBqibS){FMAZnYpHAG = true;}
      else if(iZpxKBqibS == OGbtrwBHee){zOfjXjyHWd = true;}
      if(sLprONPcda == QWwUXlwmMb){PfyPDhhhDS = true;}
      else if(QWwUXlwmMb == sLprONPcda){utmbeqEUik = true;}
      if(HVDjeScaCt == hfGKlcoPSf){fPhCmksEgh = true;}
      else if(hfGKlcoPSf == HVDjeScaCt){ZrsZAWjxxI = true;}
      if(BrLymPnuSo == kQlJLbpgHV){dqCCpQeStS = true;}
      else if(kQlJLbpgHV == BrLymPnuSo){iqPqKJHxgx = true;}
      if(KNuWniRwwj == KjrSdpzJVj){XLUxqcLFWa = true;}
      else if(KjrSdpzJVj == KNuWniRwwj){sqOZErsCLu = true;}
      if(WAXqMrDrPY == nVxREDSeLg){AlrRypeymD = true;}
      else if(nVxREDSeLg == WAXqMrDrPY){hQTirHVGiB = true;}
      if(SaFjcBzrFy == MbQuhzjmJw){elZRcYcwZm = true;}
      if(ZUJoPsafuu == uOepRxmmgu){DPnktUtjKK = true;}
      if(BgdRXBTTlt == ceshqOSUEH){YmgFhqykDz = true;}
      while(MbQuhzjmJw == SaFjcBzrFy){zAJOtEewRU = true;}
      while(uOepRxmmgu == uOepRxmmgu){jHnkridSVI = true;}
      while(ceshqOSUEH == ceshqOSUEH){cglBaSWfyD = true;}
      if(IKVaJiTwke == true){IKVaJiTwke = false;}
      if(FMAZnYpHAG == true){FMAZnYpHAG = false;}
      if(PfyPDhhhDS == true){PfyPDhhhDS = false;}
      if(fPhCmksEgh == true){fPhCmksEgh = false;}
      if(dqCCpQeStS == true){dqCCpQeStS = false;}
      if(XLUxqcLFWa == true){XLUxqcLFWa = false;}
      if(AlrRypeymD == true){AlrRypeymD = false;}
      if(elZRcYcwZm == true){elZRcYcwZm = false;}
      if(DPnktUtjKK == true){DPnktUtjKK = false;}
      if(YmgFhqykDz == true){YmgFhqykDz = false;}
      if(lgepmlkDUS == true){lgepmlkDUS = false;}
      if(zOfjXjyHWd == true){zOfjXjyHWd = false;}
      if(utmbeqEUik == true){utmbeqEUik = false;}
      if(ZrsZAWjxxI == true){ZrsZAWjxxI = false;}
      if(iqPqKJHxgx == true){iqPqKJHxgx = false;}
      if(sqOZErsCLu == true){sqOZErsCLu = false;}
      if(hQTirHVGiB == true){hQTirHVGiB = false;}
      if(zAJOtEewRU == true){zAJOtEewRU = false;}
      if(jHnkridSVI == true){jHnkridSVI = false;}
      if(cglBaSWfyD == true){cglBaSWfyD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UTDTBNAOFL
{ 
  void mKbHELgoAw()
  { 
      bool COjtshjREh = false;
      bool BnJEjcfVfK = false;
      bool olXoAiJPjn = false;
      bool ooKAQgRKfy = false;
      bool zKPigmRkoG = false;
      bool HmGnDQpttK = false;
      bool XThPsLdImC = false;
      bool LVpgLdVoIN = false;
      bool QYZcgCiVxA = false;
      bool qWQUaecAoU = false;
      bool IJxmulxZcY = false;
      bool uAlftztEiq = false;
      bool cHLmKnEUGf = false;
      bool AVzmEHblgu = false;
      bool EIsXFpkjaa = false;
      bool jYQyrByKbH = false;
      bool gbTwYYBybl = false;
      bool XIXmlUNmhU = false;
      bool CUtewbEBuC = false;
      bool JRKZOcoxzf = false;
      string AfJiCQkple;
      string AOTwtDFCrd;
      string antpcYnJJz;
      string uWLWCBLACU;
      string VzGOKJxBtX;
      string tLujcMlTFd;
      string bbfmicDwtr;
      string rFAWIageeT;
      string alOkEjbato;
      string PrtYstTTeg;
      string GAHBfoLXbB;
      string eGnlCoMthz;
      string BbCEcAKacO;
      string HNAyNZeNFO;
      string XDzrKIEIWE;
      string gYkffdyDXf;
      string ejuMsRGpYb;
      string KzoTbxbJsT;
      string uBEYgibTRi;
      string bboZjmIlzs;
      if(AfJiCQkple == GAHBfoLXbB){COjtshjREh = true;}
      else if(GAHBfoLXbB == AfJiCQkple){IJxmulxZcY = true;}
      if(AOTwtDFCrd == eGnlCoMthz){BnJEjcfVfK = true;}
      else if(eGnlCoMthz == AOTwtDFCrd){uAlftztEiq = true;}
      if(antpcYnJJz == BbCEcAKacO){olXoAiJPjn = true;}
      else if(BbCEcAKacO == antpcYnJJz){cHLmKnEUGf = true;}
      if(uWLWCBLACU == HNAyNZeNFO){ooKAQgRKfy = true;}
      else if(HNAyNZeNFO == uWLWCBLACU){AVzmEHblgu = true;}
      if(VzGOKJxBtX == XDzrKIEIWE){zKPigmRkoG = true;}
      else if(XDzrKIEIWE == VzGOKJxBtX){EIsXFpkjaa = true;}
      if(tLujcMlTFd == gYkffdyDXf){HmGnDQpttK = true;}
      else if(gYkffdyDXf == tLujcMlTFd){jYQyrByKbH = true;}
      if(bbfmicDwtr == ejuMsRGpYb){XThPsLdImC = true;}
      else if(ejuMsRGpYb == bbfmicDwtr){gbTwYYBybl = true;}
      if(rFAWIageeT == KzoTbxbJsT){LVpgLdVoIN = true;}
      if(alOkEjbato == uBEYgibTRi){QYZcgCiVxA = true;}
      if(PrtYstTTeg == bboZjmIlzs){qWQUaecAoU = true;}
      while(KzoTbxbJsT == rFAWIageeT){XIXmlUNmhU = true;}
      while(uBEYgibTRi == uBEYgibTRi){CUtewbEBuC = true;}
      while(bboZjmIlzs == bboZjmIlzs){JRKZOcoxzf = true;}
      if(COjtshjREh == true){COjtshjREh = false;}
      if(BnJEjcfVfK == true){BnJEjcfVfK = false;}
      if(olXoAiJPjn == true){olXoAiJPjn = false;}
      if(ooKAQgRKfy == true){ooKAQgRKfy = false;}
      if(zKPigmRkoG == true){zKPigmRkoG = false;}
      if(HmGnDQpttK == true){HmGnDQpttK = false;}
      if(XThPsLdImC == true){XThPsLdImC = false;}
      if(LVpgLdVoIN == true){LVpgLdVoIN = false;}
      if(QYZcgCiVxA == true){QYZcgCiVxA = false;}
      if(qWQUaecAoU == true){qWQUaecAoU = false;}
      if(IJxmulxZcY == true){IJxmulxZcY = false;}
      if(uAlftztEiq == true){uAlftztEiq = false;}
      if(cHLmKnEUGf == true){cHLmKnEUGf = false;}
      if(AVzmEHblgu == true){AVzmEHblgu = false;}
      if(EIsXFpkjaa == true){EIsXFpkjaa = false;}
      if(jYQyrByKbH == true){jYQyrByKbH = false;}
      if(gbTwYYBybl == true){gbTwYYBybl = false;}
      if(XIXmlUNmhU == true){XIXmlUNmhU = false;}
      if(CUtewbEBuC == true){CUtewbEBuC = false;}
      if(JRKZOcoxzf == true){JRKZOcoxzf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FQWHALLLYK
{ 
  void qxOcLjVrpW()
  { 
      bool BcVyQgJgPR = false;
      bool MCZjQZGTWS = false;
      bool SEZbFDOybC = false;
      bool XBdOpRugeR = false;
      bool KdpQfllzYm = false;
      bool QlKFkxDsrN = false;
      bool RLFMsKXKsy = false;
      bool dZoEIoOIuS = false;
      bool ROYoklqYds = false;
      bool OCnRzzYdWV = false;
      bool OaFaJqxFxu = false;
      bool itxYwDmQaH = false;
      bool TzfAiakXEJ = false;
      bool QjkZEpIxet = false;
      bool okahKUEOVw = false;
      bool MICOCOuFrh = false;
      bool GYAneyIXUF = false;
      bool tokgShXxpO = false;
      bool WVCIxIgWXo = false;
      bool uDFwmPkmDL = false;
      string UcSWgFEcGp;
      string BNMCTFnztQ;
      string aJAxqYnztK;
      string ljYcFuxfqR;
      string wVLdQVGpFA;
      string HRUVKKcVeI;
      string RFiwEQoiwX;
      string IIHbUExVfV;
      string RytsCTODSu;
      string SaAiApmPZz;
      string gWsgrzKrAF;
      string MGoJpTKosj;
      string ClQBEgIXbd;
      string RhufnuEMBD;
      string JWCMhMlpsf;
      string exWpxuGrbL;
      string qlPVmdKIUt;
      string PynoaeiDSr;
      string uReuyTLFis;
      string oLjoMXGgYD;
      if(UcSWgFEcGp == gWsgrzKrAF){BcVyQgJgPR = true;}
      else if(gWsgrzKrAF == UcSWgFEcGp){OaFaJqxFxu = true;}
      if(BNMCTFnztQ == MGoJpTKosj){MCZjQZGTWS = true;}
      else if(MGoJpTKosj == BNMCTFnztQ){itxYwDmQaH = true;}
      if(aJAxqYnztK == ClQBEgIXbd){SEZbFDOybC = true;}
      else if(ClQBEgIXbd == aJAxqYnztK){TzfAiakXEJ = true;}
      if(ljYcFuxfqR == RhufnuEMBD){XBdOpRugeR = true;}
      else if(RhufnuEMBD == ljYcFuxfqR){QjkZEpIxet = true;}
      if(wVLdQVGpFA == JWCMhMlpsf){KdpQfllzYm = true;}
      else if(JWCMhMlpsf == wVLdQVGpFA){okahKUEOVw = true;}
      if(HRUVKKcVeI == exWpxuGrbL){QlKFkxDsrN = true;}
      else if(exWpxuGrbL == HRUVKKcVeI){MICOCOuFrh = true;}
      if(RFiwEQoiwX == qlPVmdKIUt){RLFMsKXKsy = true;}
      else if(qlPVmdKIUt == RFiwEQoiwX){GYAneyIXUF = true;}
      if(IIHbUExVfV == PynoaeiDSr){dZoEIoOIuS = true;}
      if(RytsCTODSu == uReuyTLFis){ROYoklqYds = true;}
      if(SaAiApmPZz == oLjoMXGgYD){OCnRzzYdWV = true;}
      while(PynoaeiDSr == IIHbUExVfV){tokgShXxpO = true;}
      while(uReuyTLFis == uReuyTLFis){WVCIxIgWXo = true;}
      while(oLjoMXGgYD == oLjoMXGgYD){uDFwmPkmDL = true;}
      if(BcVyQgJgPR == true){BcVyQgJgPR = false;}
      if(MCZjQZGTWS == true){MCZjQZGTWS = false;}
      if(SEZbFDOybC == true){SEZbFDOybC = false;}
      if(XBdOpRugeR == true){XBdOpRugeR = false;}
      if(KdpQfllzYm == true){KdpQfllzYm = false;}
      if(QlKFkxDsrN == true){QlKFkxDsrN = false;}
      if(RLFMsKXKsy == true){RLFMsKXKsy = false;}
      if(dZoEIoOIuS == true){dZoEIoOIuS = false;}
      if(ROYoklqYds == true){ROYoklqYds = false;}
      if(OCnRzzYdWV == true){OCnRzzYdWV = false;}
      if(OaFaJqxFxu == true){OaFaJqxFxu = false;}
      if(itxYwDmQaH == true){itxYwDmQaH = false;}
      if(TzfAiakXEJ == true){TzfAiakXEJ = false;}
      if(QjkZEpIxet == true){QjkZEpIxet = false;}
      if(okahKUEOVw == true){okahKUEOVw = false;}
      if(MICOCOuFrh == true){MICOCOuFrh = false;}
      if(GYAneyIXUF == true){GYAneyIXUF = false;}
      if(tokgShXxpO == true){tokgShXxpO = false;}
      if(WVCIxIgWXo == true){WVCIxIgWXo = false;}
      if(uDFwmPkmDL == true){uDFwmPkmDL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFVZDNIVDY
{ 
  void KWJbdlIKcW()
  { 
      bool EdnPmaQNrk = false;
      bool faSaxrVraD = false;
      bool MFBsuHpEEE = false;
      bool YSijhjrQUU = false;
      bool XYjtXzWSKK = false;
      bool lzkxKzbtTe = false;
      bool jLJnMNrirM = false;
      bool AFWFenUHVw = false;
      bool kWtsRZgkZh = false;
      bool IxwojMOwhJ = false;
      bool GmaxKfbeSV = false;
      bool eUYXtNQPVl = false;
      bool gHJKECJgVS = false;
      bool YXYLoxwwil = false;
      bool yBSDDmYYuW = false;
      bool uyZuczdPsH = false;
      bool WtJzxGuNhw = false;
      bool QTgjneoGGQ = false;
      bool djlzWZxdho = false;
      bool TfDaODrSGx = false;
      string EUuiTGtRhG;
      string TUOJKXNdax;
      string PeqrioZJjb;
      string FZxjDgayVg;
      string npNeCuRIPg;
      string HanliYcDAd;
      string fkhFBsXdGc;
      string wPItJZQLom;
      string XRsCUdlKBd;
      string DXyqACIHcI;
      string XmBljqStcI;
      string IQNMGOqekX;
      string HMbbYYRQtG;
      string RJigPkPGSc;
      string KqhrVmKkkk;
      string LcWFBKKZML;
      string YCAVqzhgxV;
      string yjMIMPejGl;
      string NffIunlceE;
      string ZptHDIqLBW;
      if(EUuiTGtRhG == XmBljqStcI){EdnPmaQNrk = true;}
      else if(XmBljqStcI == EUuiTGtRhG){GmaxKfbeSV = true;}
      if(TUOJKXNdax == IQNMGOqekX){faSaxrVraD = true;}
      else if(IQNMGOqekX == TUOJKXNdax){eUYXtNQPVl = true;}
      if(PeqrioZJjb == HMbbYYRQtG){MFBsuHpEEE = true;}
      else if(HMbbYYRQtG == PeqrioZJjb){gHJKECJgVS = true;}
      if(FZxjDgayVg == RJigPkPGSc){YSijhjrQUU = true;}
      else if(RJigPkPGSc == FZxjDgayVg){YXYLoxwwil = true;}
      if(npNeCuRIPg == KqhrVmKkkk){XYjtXzWSKK = true;}
      else if(KqhrVmKkkk == npNeCuRIPg){yBSDDmYYuW = true;}
      if(HanliYcDAd == LcWFBKKZML){lzkxKzbtTe = true;}
      else if(LcWFBKKZML == HanliYcDAd){uyZuczdPsH = true;}
      if(fkhFBsXdGc == YCAVqzhgxV){jLJnMNrirM = true;}
      else if(YCAVqzhgxV == fkhFBsXdGc){WtJzxGuNhw = true;}
      if(wPItJZQLom == yjMIMPejGl){AFWFenUHVw = true;}
      if(XRsCUdlKBd == NffIunlceE){kWtsRZgkZh = true;}
      if(DXyqACIHcI == ZptHDIqLBW){IxwojMOwhJ = true;}
      while(yjMIMPejGl == wPItJZQLom){QTgjneoGGQ = true;}
      while(NffIunlceE == NffIunlceE){djlzWZxdho = true;}
      while(ZptHDIqLBW == ZptHDIqLBW){TfDaODrSGx = true;}
      if(EdnPmaQNrk == true){EdnPmaQNrk = false;}
      if(faSaxrVraD == true){faSaxrVraD = false;}
      if(MFBsuHpEEE == true){MFBsuHpEEE = false;}
      if(YSijhjrQUU == true){YSijhjrQUU = false;}
      if(XYjtXzWSKK == true){XYjtXzWSKK = false;}
      if(lzkxKzbtTe == true){lzkxKzbtTe = false;}
      if(jLJnMNrirM == true){jLJnMNrirM = false;}
      if(AFWFenUHVw == true){AFWFenUHVw = false;}
      if(kWtsRZgkZh == true){kWtsRZgkZh = false;}
      if(IxwojMOwhJ == true){IxwojMOwhJ = false;}
      if(GmaxKfbeSV == true){GmaxKfbeSV = false;}
      if(eUYXtNQPVl == true){eUYXtNQPVl = false;}
      if(gHJKECJgVS == true){gHJKECJgVS = false;}
      if(YXYLoxwwil == true){YXYLoxwwil = false;}
      if(yBSDDmYYuW == true){yBSDDmYYuW = false;}
      if(uyZuczdPsH == true){uyZuczdPsH = false;}
      if(WtJzxGuNhw == true){WtJzxGuNhw = false;}
      if(QTgjneoGGQ == true){QTgjneoGGQ = false;}
      if(djlzWZxdho == true){djlzWZxdho = false;}
      if(TfDaODrSGx == true){TfDaODrSGx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGAACTCGNJ
{ 
  void jqXZaPNawd()
  { 
      bool UrGQfGLlAj = false;
      bool WwEOrxuKRY = false;
      bool DOQNycBAhl = false;
      bool ADYMSWczSu = false;
      bool RuTyKcUgEY = false;
      bool FoEOZFasRD = false;
      bool FLDOjTWquU = false;
      bool UwqWHIuSCU = false;
      bool HUuIgKyKmN = false;
      bool wigPpGqENq = false;
      bool GckjEJyhHQ = false;
      bool JIqxukPugZ = false;
      bool UMEhYkObfA = false;
      bool RpEKOdiLEX = false;
      bool MQCVDnrjTF = false;
      bool pwXnWsYCLT = false;
      bool tVBGzSDfhR = false;
      bool BEpJNEJhek = false;
      bool reIaJVSPnU = false;
      bool EgAkcpOuWj = false;
      string hGIxFjIXmc;
      string wPIbbMGHge;
      string jDPZgytYAF;
      string yhkXBmtrEt;
      string ejfSJpAahg;
      string hTeXpepiQG;
      string oiWgdNdkao;
      string RNCmzAWxPp;
      string yTpTXdCNgV;
      string xKbxEuMznw;
      string MOzsOTRrXp;
      string HrTZIVsCIA;
      string KPEEqGlFhE;
      string mWITdjTwEE;
      string MKpqOEqCoh;
      string CJpnkwJtBH;
      string gLKTCkjzuX;
      string BwxEmAZNpm;
      string PjQzBdgUih;
      string ZYuxWAAWnd;
      if(hGIxFjIXmc == MOzsOTRrXp){UrGQfGLlAj = true;}
      else if(MOzsOTRrXp == hGIxFjIXmc){GckjEJyhHQ = true;}
      if(wPIbbMGHge == HrTZIVsCIA){WwEOrxuKRY = true;}
      else if(HrTZIVsCIA == wPIbbMGHge){JIqxukPugZ = true;}
      if(jDPZgytYAF == KPEEqGlFhE){DOQNycBAhl = true;}
      else if(KPEEqGlFhE == jDPZgytYAF){UMEhYkObfA = true;}
      if(yhkXBmtrEt == mWITdjTwEE){ADYMSWczSu = true;}
      else if(mWITdjTwEE == yhkXBmtrEt){RpEKOdiLEX = true;}
      if(ejfSJpAahg == MKpqOEqCoh){RuTyKcUgEY = true;}
      else if(MKpqOEqCoh == ejfSJpAahg){MQCVDnrjTF = true;}
      if(hTeXpepiQG == CJpnkwJtBH){FoEOZFasRD = true;}
      else if(CJpnkwJtBH == hTeXpepiQG){pwXnWsYCLT = true;}
      if(oiWgdNdkao == gLKTCkjzuX){FLDOjTWquU = true;}
      else if(gLKTCkjzuX == oiWgdNdkao){tVBGzSDfhR = true;}
      if(RNCmzAWxPp == BwxEmAZNpm){UwqWHIuSCU = true;}
      if(yTpTXdCNgV == PjQzBdgUih){HUuIgKyKmN = true;}
      if(xKbxEuMznw == ZYuxWAAWnd){wigPpGqENq = true;}
      while(BwxEmAZNpm == RNCmzAWxPp){BEpJNEJhek = true;}
      while(PjQzBdgUih == PjQzBdgUih){reIaJVSPnU = true;}
      while(ZYuxWAAWnd == ZYuxWAAWnd){EgAkcpOuWj = true;}
      if(UrGQfGLlAj == true){UrGQfGLlAj = false;}
      if(WwEOrxuKRY == true){WwEOrxuKRY = false;}
      if(DOQNycBAhl == true){DOQNycBAhl = false;}
      if(ADYMSWczSu == true){ADYMSWczSu = false;}
      if(RuTyKcUgEY == true){RuTyKcUgEY = false;}
      if(FoEOZFasRD == true){FoEOZFasRD = false;}
      if(FLDOjTWquU == true){FLDOjTWquU = false;}
      if(UwqWHIuSCU == true){UwqWHIuSCU = false;}
      if(HUuIgKyKmN == true){HUuIgKyKmN = false;}
      if(wigPpGqENq == true){wigPpGqENq = false;}
      if(GckjEJyhHQ == true){GckjEJyhHQ = false;}
      if(JIqxukPugZ == true){JIqxukPugZ = false;}
      if(UMEhYkObfA == true){UMEhYkObfA = false;}
      if(RpEKOdiLEX == true){RpEKOdiLEX = false;}
      if(MQCVDnrjTF == true){MQCVDnrjTF = false;}
      if(pwXnWsYCLT == true){pwXnWsYCLT = false;}
      if(tVBGzSDfhR == true){tVBGzSDfhR = false;}
      if(BEpJNEJhek == true){BEpJNEJhek = false;}
      if(reIaJVSPnU == true){reIaJVSPnU = false;}
      if(EgAkcpOuWj == true){EgAkcpOuWj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KPEDLKGTPQ
{ 
  void pfGqkyaqnt()
  { 
      bool aFkFhHRxWC = false;
      bool qGnIhEBzZI = false;
      bool RAmULDsWEX = false;
      bool sReqzKOusJ = false;
      bool TzfoReAVAc = false;
      bool RduJraSQse = false;
      bool OtrzJYawJW = false;
      bool pFFQoRTxCg = false;
      bool CWVbFOWUyX = false;
      bool rxCOuYGgfr = false;
      bool DDMcmMXdUZ = false;
      bool GUOLcqXQsu = false;
      bool CGykerCqUQ = false;
      bool KmRJdyKrns = false;
      bool prAXQXiqlD = false;
      bool ApmjpwFayt = false;
      bool JfIEPTCEgd = false;
      bool gebzEJGZTG = false;
      bool JLFRPUAgSg = false;
      bool sitsiJiuIx = false;
      string WRuaiQlxDO;
      string UxEEPkLbJT;
      string BhFerqCwYW;
      string aKzgJLzOhK;
      string GipNLalJsn;
      string PzbATnLQhq;
      string OoXfmKyXtE;
      string lwsyMSrqSQ;
      string ErDjGahzNU;
      string zigpwQKKZB;
      string cOOoCTGcmB;
      string wUxRmVlnZL;
      string bzKZFCPDCw;
      string HhQRmpdOhl;
      string UELMYekPCZ;
      string eWjNZdEoiz;
      string ECaqsODfdx;
      string rXFmqWmyAa;
      string QABbQkxDrJ;
      string koeihSdUSJ;
      if(WRuaiQlxDO == cOOoCTGcmB){aFkFhHRxWC = true;}
      else if(cOOoCTGcmB == WRuaiQlxDO){DDMcmMXdUZ = true;}
      if(UxEEPkLbJT == wUxRmVlnZL){qGnIhEBzZI = true;}
      else if(wUxRmVlnZL == UxEEPkLbJT){GUOLcqXQsu = true;}
      if(BhFerqCwYW == bzKZFCPDCw){RAmULDsWEX = true;}
      else if(bzKZFCPDCw == BhFerqCwYW){CGykerCqUQ = true;}
      if(aKzgJLzOhK == HhQRmpdOhl){sReqzKOusJ = true;}
      else if(HhQRmpdOhl == aKzgJLzOhK){KmRJdyKrns = true;}
      if(GipNLalJsn == UELMYekPCZ){TzfoReAVAc = true;}
      else if(UELMYekPCZ == GipNLalJsn){prAXQXiqlD = true;}
      if(PzbATnLQhq == eWjNZdEoiz){RduJraSQse = true;}
      else if(eWjNZdEoiz == PzbATnLQhq){ApmjpwFayt = true;}
      if(OoXfmKyXtE == ECaqsODfdx){OtrzJYawJW = true;}
      else if(ECaqsODfdx == OoXfmKyXtE){JfIEPTCEgd = true;}
      if(lwsyMSrqSQ == rXFmqWmyAa){pFFQoRTxCg = true;}
      if(ErDjGahzNU == QABbQkxDrJ){CWVbFOWUyX = true;}
      if(zigpwQKKZB == koeihSdUSJ){rxCOuYGgfr = true;}
      while(rXFmqWmyAa == lwsyMSrqSQ){gebzEJGZTG = true;}
      while(QABbQkxDrJ == QABbQkxDrJ){JLFRPUAgSg = true;}
      while(koeihSdUSJ == koeihSdUSJ){sitsiJiuIx = true;}
      if(aFkFhHRxWC == true){aFkFhHRxWC = false;}
      if(qGnIhEBzZI == true){qGnIhEBzZI = false;}
      if(RAmULDsWEX == true){RAmULDsWEX = false;}
      if(sReqzKOusJ == true){sReqzKOusJ = false;}
      if(TzfoReAVAc == true){TzfoReAVAc = false;}
      if(RduJraSQse == true){RduJraSQse = false;}
      if(OtrzJYawJW == true){OtrzJYawJW = false;}
      if(pFFQoRTxCg == true){pFFQoRTxCg = false;}
      if(CWVbFOWUyX == true){CWVbFOWUyX = false;}
      if(rxCOuYGgfr == true){rxCOuYGgfr = false;}
      if(DDMcmMXdUZ == true){DDMcmMXdUZ = false;}
      if(GUOLcqXQsu == true){GUOLcqXQsu = false;}
      if(CGykerCqUQ == true){CGykerCqUQ = false;}
      if(KmRJdyKrns == true){KmRJdyKrns = false;}
      if(prAXQXiqlD == true){prAXQXiqlD = false;}
      if(ApmjpwFayt == true){ApmjpwFayt = false;}
      if(JfIEPTCEgd == true){JfIEPTCEgd = false;}
      if(gebzEJGZTG == true){gebzEJGZTG = false;}
      if(JLFRPUAgSg == true){JLFRPUAgSg = false;}
      if(sitsiJiuIx == true){sitsiJiuIx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AFOHTPNDHQ
{ 
  void zEEAaLEDay()
  { 
      bool PMYIJMGuXL = false;
      bool cbBYRCknZx = false;
      bool SlmggKLTUH = false;
      bool uDMuFdrHaT = false;
      bool wDyHfpBVzr = false;
      bool kxYVIdZqay = false;
      bool AmZQQYPFSm = false;
      bool JdNFBPmeAq = false;
      bool JpTcVxeqmb = false;
      bool DAgcTJchqH = false;
      bool ZuCLhHjSUr = false;
      bool puqjnKSxtT = false;
      bool sYSqjIwjlq = false;
      bool mFnrQOmItN = false;
      bool MLWtkIJxnI = false;
      bool pemWNBcKbZ = false;
      bool LzfcFjHySZ = false;
      bool WKDfHgCXFa = false;
      bool yzucBHRQdO = false;
      bool lcgTCMftnB = false;
      string NGqAWAkScm;
      string aJapWJbFgz;
      string ziqWqLuOOk;
      string jplIBVJCwP;
      string jEhKWMaemU;
      string XjyWqdPUIL;
      string EVDrDkXRoA;
      string AYJROuBgzd;
      string jQatNzqOQW;
      string GosjKNApGl;
      string oIpmUzafIw;
      string chUebntJdD;
      string sJARsLfYHA;
      string tKZNoaanZO;
      string YLGUtXTOIW;
      string TqLDsfIXsI;
      string TBYHBRIGpA;
      string NGjPegCfWU;
      string qQQjgDzWTI;
      string SCtQtWlzSb;
      if(NGqAWAkScm == oIpmUzafIw){PMYIJMGuXL = true;}
      else if(oIpmUzafIw == NGqAWAkScm){ZuCLhHjSUr = true;}
      if(aJapWJbFgz == chUebntJdD){cbBYRCknZx = true;}
      else if(chUebntJdD == aJapWJbFgz){puqjnKSxtT = true;}
      if(ziqWqLuOOk == sJARsLfYHA){SlmggKLTUH = true;}
      else if(sJARsLfYHA == ziqWqLuOOk){sYSqjIwjlq = true;}
      if(jplIBVJCwP == tKZNoaanZO){uDMuFdrHaT = true;}
      else if(tKZNoaanZO == jplIBVJCwP){mFnrQOmItN = true;}
      if(jEhKWMaemU == YLGUtXTOIW){wDyHfpBVzr = true;}
      else if(YLGUtXTOIW == jEhKWMaemU){MLWtkIJxnI = true;}
      if(XjyWqdPUIL == TqLDsfIXsI){kxYVIdZqay = true;}
      else if(TqLDsfIXsI == XjyWqdPUIL){pemWNBcKbZ = true;}
      if(EVDrDkXRoA == TBYHBRIGpA){AmZQQYPFSm = true;}
      else if(TBYHBRIGpA == EVDrDkXRoA){LzfcFjHySZ = true;}
      if(AYJROuBgzd == NGjPegCfWU){JdNFBPmeAq = true;}
      if(jQatNzqOQW == qQQjgDzWTI){JpTcVxeqmb = true;}
      if(GosjKNApGl == SCtQtWlzSb){DAgcTJchqH = true;}
      while(NGjPegCfWU == AYJROuBgzd){WKDfHgCXFa = true;}
      while(qQQjgDzWTI == qQQjgDzWTI){yzucBHRQdO = true;}
      while(SCtQtWlzSb == SCtQtWlzSb){lcgTCMftnB = true;}
      if(PMYIJMGuXL == true){PMYIJMGuXL = false;}
      if(cbBYRCknZx == true){cbBYRCknZx = false;}
      if(SlmggKLTUH == true){SlmggKLTUH = false;}
      if(uDMuFdrHaT == true){uDMuFdrHaT = false;}
      if(wDyHfpBVzr == true){wDyHfpBVzr = false;}
      if(kxYVIdZqay == true){kxYVIdZqay = false;}
      if(AmZQQYPFSm == true){AmZQQYPFSm = false;}
      if(JdNFBPmeAq == true){JdNFBPmeAq = false;}
      if(JpTcVxeqmb == true){JpTcVxeqmb = false;}
      if(DAgcTJchqH == true){DAgcTJchqH = false;}
      if(ZuCLhHjSUr == true){ZuCLhHjSUr = false;}
      if(puqjnKSxtT == true){puqjnKSxtT = false;}
      if(sYSqjIwjlq == true){sYSqjIwjlq = false;}
      if(mFnrQOmItN == true){mFnrQOmItN = false;}
      if(MLWtkIJxnI == true){MLWtkIJxnI = false;}
      if(pemWNBcKbZ == true){pemWNBcKbZ = false;}
      if(LzfcFjHySZ == true){LzfcFjHySZ = false;}
      if(WKDfHgCXFa == true){WKDfHgCXFa = false;}
      if(yzucBHRQdO == true){yzucBHRQdO = false;}
      if(lcgTCMftnB == true){lcgTCMftnB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VQCUPVJPQC
{ 
  void NCcFITynwG()
  { 
      bool WAUIwlXica = false;
      bool xZZeInJFHQ = false;
      bool MMfiDVnWyg = false;
      bool HswTyrlyEs = false;
      bool VoPAnenRbC = false;
      bool BJQcAJUkFZ = false;
      bool xBkuSEdFgQ = false;
      bool BLBNtWxeuX = false;
      bool gWtufybSTn = false;
      bool XAsdwUEThi = false;
      bool AikKBpHChc = false;
      bool MopgsaGpPU = false;
      bool bLkrsBRWRZ = false;
      bool ScxLXykjto = false;
      bool pZjpbhKMkU = false;
      bool NOEMHoxsQz = false;
      bool YjjIKirdIu = false;
      bool oWwZeBauPL = false;
      bool qElwLDXjEi = false;
      bool ArStQFobfr = false;
      string UFEowYJSaL;
      string MqUWHdkYPu;
      string KshHXjKgiZ;
      string XLIfIQmcGy;
      string jKydqcBBms;
      string yGDDmbWxRM;
      string NcjBmBinNp;
      string qIRQLAtEPu;
      string hIsoaRIErg;
      string tpLtjHZxqp;
      string sMnwCpomrl;
      string hSgVdEitZV;
      string rdwgwBwXfE;
      string awNZBVUxlk;
      string cVMFzaIoQf;
      string XfXVxPQHAB;
      string tQGnLkEHUI;
      string ilHorWRphU;
      string rGGAftYrbl;
      string ENxkqLOYtN;
      if(UFEowYJSaL == sMnwCpomrl){WAUIwlXica = true;}
      else if(sMnwCpomrl == UFEowYJSaL){AikKBpHChc = true;}
      if(MqUWHdkYPu == hSgVdEitZV){xZZeInJFHQ = true;}
      else if(hSgVdEitZV == MqUWHdkYPu){MopgsaGpPU = true;}
      if(KshHXjKgiZ == rdwgwBwXfE){MMfiDVnWyg = true;}
      else if(rdwgwBwXfE == KshHXjKgiZ){bLkrsBRWRZ = true;}
      if(XLIfIQmcGy == awNZBVUxlk){HswTyrlyEs = true;}
      else if(awNZBVUxlk == XLIfIQmcGy){ScxLXykjto = true;}
      if(jKydqcBBms == cVMFzaIoQf){VoPAnenRbC = true;}
      else if(cVMFzaIoQf == jKydqcBBms){pZjpbhKMkU = true;}
      if(yGDDmbWxRM == XfXVxPQHAB){BJQcAJUkFZ = true;}
      else if(XfXVxPQHAB == yGDDmbWxRM){NOEMHoxsQz = true;}
      if(NcjBmBinNp == tQGnLkEHUI){xBkuSEdFgQ = true;}
      else if(tQGnLkEHUI == NcjBmBinNp){YjjIKirdIu = true;}
      if(qIRQLAtEPu == ilHorWRphU){BLBNtWxeuX = true;}
      if(hIsoaRIErg == rGGAftYrbl){gWtufybSTn = true;}
      if(tpLtjHZxqp == ENxkqLOYtN){XAsdwUEThi = true;}
      while(ilHorWRphU == qIRQLAtEPu){oWwZeBauPL = true;}
      while(rGGAftYrbl == rGGAftYrbl){qElwLDXjEi = true;}
      while(ENxkqLOYtN == ENxkqLOYtN){ArStQFobfr = true;}
      if(WAUIwlXica == true){WAUIwlXica = false;}
      if(xZZeInJFHQ == true){xZZeInJFHQ = false;}
      if(MMfiDVnWyg == true){MMfiDVnWyg = false;}
      if(HswTyrlyEs == true){HswTyrlyEs = false;}
      if(VoPAnenRbC == true){VoPAnenRbC = false;}
      if(BJQcAJUkFZ == true){BJQcAJUkFZ = false;}
      if(xBkuSEdFgQ == true){xBkuSEdFgQ = false;}
      if(BLBNtWxeuX == true){BLBNtWxeuX = false;}
      if(gWtufybSTn == true){gWtufybSTn = false;}
      if(XAsdwUEThi == true){XAsdwUEThi = false;}
      if(AikKBpHChc == true){AikKBpHChc = false;}
      if(MopgsaGpPU == true){MopgsaGpPU = false;}
      if(bLkrsBRWRZ == true){bLkrsBRWRZ = false;}
      if(ScxLXykjto == true){ScxLXykjto = false;}
      if(pZjpbhKMkU == true){pZjpbhKMkU = false;}
      if(NOEMHoxsQz == true){NOEMHoxsQz = false;}
      if(YjjIKirdIu == true){YjjIKirdIu = false;}
      if(oWwZeBauPL == true){oWwZeBauPL = false;}
      if(qElwLDXjEi == true){qElwLDXjEi = false;}
      if(ArStQFobfr == true){ArStQFobfr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YVAJRHYMJM
{ 
  void CFrzlMXUcO()
  { 
      bool GABanEFTpp = false;
      bool ofexhfQwGG = false;
      bool QNUiofWhuz = false;
      bool jAfCHDHnuB = false;
      bool JHrHZzFtoy = false;
      bool etjjVsfSkI = false;
      bool hWYqFozcoe = false;
      bool XbAFwJVMIo = false;
      bool ZcswTpPwgO = false;
      bool WnDmTlhBCk = false;
      bool AcEJaDsemL = false;
      bool XSKwhEdcWP = false;
      bool YDwaHiYNlJ = false;
      bool aTKWowYiVQ = false;
      bool wkIUpEdHEO = false;
      bool IFdlMxgcCq = false;
      bool dfrdjDImGk = false;
      bool ftHGTmtajD = false;
      bool FRIXAVoXJr = false;
      bool PufdlPsejl = false;
      string fSrLWOwZeU;
      string PfwhsdToFy;
      string IHbhqxywtT;
      string bZqFSIJPbp;
      string lGyAERbEOc;
      string CGizxXpKUZ;
      string PAfKronpPj;
      string UENOLBJadZ;
      string UthQRUqrHt;
      string RzuBZlamIO;
      string ckodHysTmw;
      string OOguEVSOsW;
      string ywhURVJMnZ;
      string aVSOwiEDJT;
      string bWELfDRAwE;
      string TLtkQgCTLl;
      string offNVswRyV;
      string QOFZuaqWoO;
      string DIPiGPbhxP;
      string fkqXewqqpm;
      if(fSrLWOwZeU == ckodHysTmw){GABanEFTpp = true;}
      else if(ckodHysTmw == fSrLWOwZeU){AcEJaDsemL = true;}
      if(PfwhsdToFy == OOguEVSOsW){ofexhfQwGG = true;}
      else if(OOguEVSOsW == PfwhsdToFy){XSKwhEdcWP = true;}
      if(IHbhqxywtT == ywhURVJMnZ){QNUiofWhuz = true;}
      else if(ywhURVJMnZ == IHbhqxywtT){YDwaHiYNlJ = true;}
      if(bZqFSIJPbp == aVSOwiEDJT){jAfCHDHnuB = true;}
      else if(aVSOwiEDJT == bZqFSIJPbp){aTKWowYiVQ = true;}
      if(lGyAERbEOc == bWELfDRAwE){JHrHZzFtoy = true;}
      else if(bWELfDRAwE == lGyAERbEOc){wkIUpEdHEO = true;}
      if(CGizxXpKUZ == TLtkQgCTLl){etjjVsfSkI = true;}
      else if(TLtkQgCTLl == CGizxXpKUZ){IFdlMxgcCq = true;}
      if(PAfKronpPj == offNVswRyV){hWYqFozcoe = true;}
      else if(offNVswRyV == PAfKronpPj){dfrdjDImGk = true;}
      if(UENOLBJadZ == QOFZuaqWoO){XbAFwJVMIo = true;}
      if(UthQRUqrHt == DIPiGPbhxP){ZcswTpPwgO = true;}
      if(RzuBZlamIO == fkqXewqqpm){WnDmTlhBCk = true;}
      while(QOFZuaqWoO == UENOLBJadZ){ftHGTmtajD = true;}
      while(DIPiGPbhxP == DIPiGPbhxP){FRIXAVoXJr = true;}
      while(fkqXewqqpm == fkqXewqqpm){PufdlPsejl = true;}
      if(GABanEFTpp == true){GABanEFTpp = false;}
      if(ofexhfQwGG == true){ofexhfQwGG = false;}
      if(QNUiofWhuz == true){QNUiofWhuz = false;}
      if(jAfCHDHnuB == true){jAfCHDHnuB = false;}
      if(JHrHZzFtoy == true){JHrHZzFtoy = false;}
      if(etjjVsfSkI == true){etjjVsfSkI = false;}
      if(hWYqFozcoe == true){hWYqFozcoe = false;}
      if(XbAFwJVMIo == true){XbAFwJVMIo = false;}
      if(ZcswTpPwgO == true){ZcswTpPwgO = false;}
      if(WnDmTlhBCk == true){WnDmTlhBCk = false;}
      if(AcEJaDsemL == true){AcEJaDsemL = false;}
      if(XSKwhEdcWP == true){XSKwhEdcWP = false;}
      if(YDwaHiYNlJ == true){YDwaHiYNlJ = false;}
      if(aTKWowYiVQ == true){aTKWowYiVQ = false;}
      if(wkIUpEdHEO == true){wkIUpEdHEO = false;}
      if(IFdlMxgcCq == true){IFdlMxgcCq = false;}
      if(dfrdjDImGk == true){dfrdjDImGk = false;}
      if(ftHGTmtajD == true){ftHGTmtajD = false;}
      if(FRIXAVoXJr == true){FRIXAVoXJr = false;}
      if(PufdlPsejl == true){PufdlPsejl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UZGWTFZNPS
{ 
  void cexSaoWmwP()
  { 
      bool fXlmQZsEJP = false;
      bool JfAFkIIIbr = false;
      bool oOZOllTJDj = false;
      bool UBpCcKSlXd = false;
      bool jXsYNfznGe = false;
      bool qnoDZQyWAd = false;
      bool GiBZuHpxca = false;
      bool oWjxIQVABG = false;
      bool leDXrgMmbM = false;
      bool MuksXAWTdF = false;
      bool pCLfoUDqtJ = false;
      bool uxVtrbfchN = false;
      bool uCUPNtkqZI = false;
      bool tCWuQjSWhW = false;
      bool dUrSROZpBw = false;
      bool TtkPKmguRu = false;
      bool iLQkPsaZdH = false;
      bool IItKjZKCyz = false;
      bool UtodnzQGkc = false;
      bool CWFmmRDHDY = false;
      string qyqCHXfDFk;
      string KluEQMZHwU;
      string EmUuYhgbmU;
      string pSzhdrTmky;
      string QYYIifittj;
      string cOlcXEcwdZ;
      string qEQkuqmNZX;
      string slVyEeNLMr;
      string ylgDrbgVJY;
      string PWJLHLHnNq;
      string sUTWpprnYr;
      string qQjkaEXNrT;
      string KQDBHVcKqr;
      string WYyUzcSJMB;
      string isxRhymXkC;
      string ntutgbRSOU;
      string NhxfVRSOlx;
      string lNBqjQSlSJ;
      string iEYnEccDnW;
      string LztrnAwRwP;
      if(qyqCHXfDFk == sUTWpprnYr){fXlmQZsEJP = true;}
      else if(sUTWpprnYr == qyqCHXfDFk){pCLfoUDqtJ = true;}
      if(KluEQMZHwU == qQjkaEXNrT){JfAFkIIIbr = true;}
      else if(qQjkaEXNrT == KluEQMZHwU){uxVtrbfchN = true;}
      if(EmUuYhgbmU == KQDBHVcKqr){oOZOllTJDj = true;}
      else if(KQDBHVcKqr == EmUuYhgbmU){uCUPNtkqZI = true;}
      if(pSzhdrTmky == WYyUzcSJMB){UBpCcKSlXd = true;}
      else if(WYyUzcSJMB == pSzhdrTmky){tCWuQjSWhW = true;}
      if(QYYIifittj == isxRhymXkC){jXsYNfznGe = true;}
      else if(isxRhymXkC == QYYIifittj){dUrSROZpBw = true;}
      if(cOlcXEcwdZ == ntutgbRSOU){qnoDZQyWAd = true;}
      else if(ntutgbRSOU == cOlcXEcwdZ){TtkPKmguRu = true;}
      if(qEQkuqmNZX == NhxfVRSOlx){GiBZuHpxca = true;}
      else if(NhxfVRSOlx == qEQkuqmNZX){iLQkPsaZdH = true;}
      if(slVyEeNLMr == lNBqjQSlSJ){oWjxIQVABG = true;}
      if(ylgDrbgVJY == iEYnEccDnW){leDXrgMmbM = true;}
      if(PWJLHLHnNq == LztrnAwRwP){MuksXAWTdF = true;}
      while(lNBqjQSlSJ == slVyEeNLMr){IItKjZKCyz = true;}
      while(iEYnEccDnW == iEYnEccDnW){UtodnzQGkc = true;}
      while(LztrnAwRwP == LztrnAwRwP){CWFmmRDHDY = true;}
      if(fXlmQZsEJP == true){fXlmQZsEJP = false;}
      if(JfAFkIIIbr == true){JfAFkIIIbr = false;}
      if(oOZOllTJDj == true){oOZOllTJDj = false;}
      if(UBpCcKSlXd == true){UBpCcKSlXd = false;}
      if(jXsYNfznGe == true){jXsYNfznGe = false;}
      if(qnoDZQyWAd == true){qnoDZQyWAd = false;}
      if(GiBZuHpxca == true){GiBZuHpxca = false;}
      if(oWjxIQVABG == true){oWjxIQVABG = false;}
      if(leDXrgMmbM == true){leDXrgMmbM = false;}
      if(MuksXAWTdF == true){MuksXAWTdF = false;}
      if(pCLfoUDqtJ == true){pCLfoUDqtJ = false;}
      if(uxVtrbfchN == true){uxVtrbfchN = false;}
      if(uCUPNtkqZI == true){uCUPNtkqZI = false;}
      if(tCWuQjSWhW == true){tCWuQjSWhW = false;}
      if(dUrSROZpBw == true){dUrSROZpBw = false;}
      if(TtkPKmguRu == true){TtkPKmguRu = false;}
      if(iLQkPsaZdH == true){iLQkPsaZdH = false;}
      if(IItKjZKCyz == true){IItKjZKCyz = false;}
      if(UtodnzQGkc == true){UtodnzQGkc = false;}
      if(CWFmmRDHDY == true){CWFmmRDHDY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NPNOKJYGIQ
{ 
  void rZUBtuRzQi()
  { 
      bool noJgBhQeha = false;
      bool aQZunPZVML = false;
      bool kUWjpGMcmC = false;
      bool DouJbmFSKp = false;
      bool OeqYlCtoRH = false;
      bool nqIICSSYpu = false;
      bool VmreWlUPTB = false;
      bool KHLWxGcxym = false;
      bool LWLfNMflHJ = false;
      bool TfbOTalMCz = false;
      bool heVPxgelKw = false;
      bool oUaDizbLQJ = false;
      bool FhHKgdewDW = false;
      bool TQuyFgAuig = false;
      bool hsaLTzFYfT = false;
      bool yZwrszWLiS = false;
      bool ChinbYYbyC = false;
      bool zfcjbLHwpg = false;
      bool XGQiXsUCFF = false;
      bool KnMPezKlit = false;
      string WfmaxXbYzN;
      string ElymyxeJtN;
      string SXkdZdJWsh;
      string GZUmcwiETK;
      string giUJiVUNMS;
      string cEHWEytJAT;
      string OFeRGeQKJB;
      string NapjgiDauE;
      string JuJaECSxhd;
      string BZDAubECDD;
      string FJDLECOWpV;
      string uSNwJSuEME;
      string MScfznWpnE;
      string dAXqzArxVC;
      string muHMhiLHpc;
      string fzpyqlgXMQ;
      string eYhkqutWxJ;
      string axiKQQLPxQ;
      string bPzLYeKZzM;
      string TUkFWNMVUm;
      if(WfmaxXbYzN == FJDLECOWpV){noJgBhQeha = true;}
      else if(FJDLECOWpV == WfmaxXbYzN){heVPxgelKw = true;}
      if(ElymyxeJtN == uSNwJSuEME){aQZunPZVML = true;}
      else if(uSNwJSuEME == ElymyxeJtN){oUaDizbLQJ = true;}
      if(SXkdZdJWsh == MScfznWpnE){kUWjpGMcmC = true;}
      else if(MScfznWpnE == SXkdZdJWsh){FhHKgdewDW = true;}
      if(GZUmcwiETK == dAXqzArxVC){DouJbmFSKp = true;}
      else if(dAXqzArxVC == GZUmcwiETK){TQuyFgAuig = true;}
      if(giUJiVUNMS == muHMhiLHpc){OeqYlCtoRH = true;}
      else if(muHMhiLHpc == giUJiVUNMS){hsaLTzFYfT = true;}
      if(cEHWEytJAT == fzpyqlgXMQ){nqIICSSYpu = true;}
      else if(fzpyqlgXMQ == cEHWEytJAT){yZwrszWLiS = true;}
      if(OFeRGeQKJB == eYhkqutWxJ){VmreWlUPTB = true;}
      else if(eYhkqutWxJ == OFeRGeQKJB){ChinbYYbyC = true;}
      if(NapjgiDauE == axiKQQLPxQ){KHLWxGcxym = true;}
      if(JuJaECSxhd == bPzLYeKZzM){LWLfNMflHJ = true;}
      if(BZDAubECDD == TUkFWNMVUm){TfbOTalMCz = true;}
      while(axiKQQLPxQ == NapjgiDauE){zfcjbLHwpg = true;}
      while(bPzLYeKZzM == bPzLYeKZzM){XGQiXsUCFF = true;}
      while(TUkFWNMVUm == TUkFWNMVUm){KnMPezKlit = true;}
      if(noJgBhQeha == true){noJgBhQeha = false;}
      if(aQZunPZVML == true){aQZunPZVML = false;}
      if(kUWjpGMcmC == true){kUWjpGMcmC = false;}
      if(DouJbmFSKp == true){DouJbmFSKp = false;}
      if(OeqYlCtoRH == true){OeqYlCtoRH = false;}
      if(nqIICSSYpu == true){nqIICSSYpu = false;}
      if(VmreWlUPTB == true){VmreWlUPTB = false;}
      if(KHLWxGcxym == true){KHLWxGcxym = false;}
      if(LWLfNMflHJ == true){LWLfNMflHJ = false;}
      if(TfbOTalMCz == true){TfbOTalMCz = false;}
      if(heVPxgelKw == true){heVPxgelKw = false;}
      if(oUaDizbLQJ == true){oUaDizbLQJ = false;}
      if(FhHKgdewDW == true){FhHKgdewDW = false;}
      if(TQuyFgAuig == true){TQuyFgAuig = false;}
      if(hsaLTzFYfT == true){hsaLTzFYfT = false;}
      if(yZwrszWLiS == true){yZwrszWLiS = false;}
      if(ChinbYYbyC == true){ChinbYYbyC = false;}
      if(zfcjbLHwpg == true){zfcjbLHwpg = false;}
      if(XGQiXsUCFF == true){XGQiXsUCFF = false;}
      if(KnMPezKlit == true){KnMPezKlit = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TOSENUSUWA
{ 
  void fVgQqoUgEa()
  { 
      bool XOrIxPAppR = false;
      bool lcQCuajltQ = false;
      bool pIRolkwlFO = false;
      bool auIYVaqVwq = false;
      bool ORfxdZnuPT = false;
      bool rykCwPwCWL = false;
      bool SOjaqpUqfU = false;
      bool iNoCBXbTKM = false;
      bool xBVkWbJFcG = false;
      bool dnzjXAgEFm = false;
      bool EwOujdJiAX = false;
      bool mbqKORryEP = false;
      bool gOOZpuOFdB = false;
      bool pXNXHAlZBr = false;
      bool SaFESBxnVG = false;
      bool HiApGogoFo = false;
      bool PDEyhPOTDN = false;
      bool fSxLxGJKHn = false;
      bool yZiWtHXXRR = false;
      bool TxULcOVGVC = false;
      string iOfBdcxGsa;
      string lwSGbCTJby;
      string LoIHXqDSuu;
      string FgnwbruIij;
      string eEtlJbCAdc;
      string ATEmCsFYdl;
      string ZdLyUEIVdj;
      string HLZqSGuVyw;
      string oCnRtkcBti;
      string lVewKAruRE;
      string TfWtVosMTu;
      string yiahxWosEi;
      string aHauxkfdgS;
      string OzEsbIftwE;
      string rPgzjDuxyn;
      string KyqhcMEawj;
      string JPeBfyegFo;
      string puxAqLZbKt;
      string oiesHPIWPP;
      string DEyLtbkeSl;
      if(iOfBdcxGsa == TfWtVosMTu){XOrIxPAppR = true;}
      else if(TfWtVosMTu == iOfBdcxGsa){EwOujdJiAX = true;}
      if(lwSGbCTJby == yiahxWosEi){lcQCuajltQ = true;}
      else if(yiahxWosEi == lwSGbCTJby){mbqKORryEP = true;}
      if(LoIHXqDSuu == aHauxkfdgS){pIRolkwlFO = true;}
      else if(aHauxkfdgS == LoIHXqDSuu){gOOZpuOFdB = true;}
      if(FgnwbruIij == OzEsbIftwE){auIYVaqVwq = true;}
      else if(OzEsbIftwE == FgnwbruIij){pXNXHAlZBr = true;}
      if(eEtlJbCAdc == rPgzjDuxyn){ORfxdZnuPT = true;}
      else if(rPgzjDuxyn == eEtlJbCAdc){SaFESBxnVG = true;}
      if(ATEmCsFYdl == KyqhcMEawj){rykCwPwCWL = true;}
      else if(KyqhcMEawj == ATEmCsFYdl){HiApGogoFo = true;}
      if(ZdLyUEIVdj == JPeBfyegFo){SOjaqpUqfU = true;}
      else if(JPeBfyegFo == ZdLyUEIVdj){PDEyhPOTDN = true;}
      if(HLZqSGuVyw == puxAqLZbKt){iNoCBXbTKM = true;}
      if(oCnRtkcBti == oiesHPIWPP){xBVkWbJFcG = true;}
      if(lVewKAruRE == DEyLtbkeSl){dnzjXAgEFm = true;}
      while(puxAqLZbKt == HLZqSGuVyw){fSxLxGJKHn = true;}
      while(oiesHPIWPP == oiesHPIWPP){yZiWtHXXRR = true;}
      while(DEyLtbkeSl == DEyLtbkeSl){TxULcOVGVC = true;}
      if(XOrIxPAppR == true){XOrIxPAppR = false;}
      if(lcQCuajltQ == true){lcQCuajltQ = false;}
      if(pIRolkwlFO == true){pIRolkwlFO = false;}
      if(auIYVaqVwq == true){auIYVaqVwq = false;}
      if(ORfxdZnuPT == true){ORfxdZnuPT = false;}
      if(rykCwPwCWL == true){rykCwPwCWL = false;}
      if(SOjaqpUqfU == true){SOjaqpUqfU = false;}
      if(iNoCBXbTKM == true){iNoCBXbTKM = false;}
      if(xBVkWbJFcG == true){xBVkWbJFcG = false;}
      if(dnzjXAgEFm == true){dnzjXAgEFm = false;}
      if(EwOujdJiAX == true){EwOujdJiAX = false;}
      if(mbqKORryEP == true){mbqKORryEP = false;}
      if(gOOZpuOFdB == true){gOOZpuOFdB = false;}
      if(pXNXHAlZBr == true){pXNXHAlZBr = false;}
      if(SaFESBxnVG == true){SaFESBxnVG = false;}
      if(HiApGogoFo == true){HiApGogoFo = false;}
      if(PDEyhPOTDN == true){PDEyhPOTDN = false;}
      if(fSxLxGJKHn == true){fSxLxGJKHn = false;}
      if(yZiWtHXXRR == true){yZiWtHXXRR = false;}
      if(TxULcOVGVC == true){TxULcOVGVC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSCBAEKDSX
{ 
  void gSRDwEahNO()
  { 
      bool njfIFRiIcb = false;
      bool iLzhofQTZa = false;
      bool SjjMaYhiXT = false;
      bool ZdaLcFRgrr = false;
      bool wHuOQYbXSP = false;
      bool nFgyJDzTgf = false;
      bool jAkJCEknEi = false;
      bool NibheKnVuC = false;
      bool wKPHeTwcBY = false;
      bool FyzLHwWlLL = false;
      bool mnSiBEdzSy = false;
      bool PdXeiYjcdh = false;
      bool HIledPjPZi = false;
      bool nBJjOIqfFa = false;
      bool pxJDJaZUci = false;
      bool LsIcEeCmFl = false;
      bool TNYjJNUnPa = false;
      bool hDWCrJyiVC = false;
      bool oPmqWurfei = false;
      bool GDaTGbYYsu = false;
      string jBZispoCfp;
      string BfgXUmmHIe;
      string HnHykzZbFk;
      string dBJKkZgWVj;
      string NzUwPSMZIm;
      string lCqRTwtbyt;
      string PNwtLzVVmt;
      string GPlXQHTKhR;
      string lATSybJrqn;
      string fEYbUACZkQ;
      string xplNfWQTAL;
      string cisfHOscwi;
      string ocezOBqKCQ;
      string EsZRTuOFlb;
      string KpqeLxLrUF;
      string GZcBaULmze;
      string eGQjGiIaLL;
      string AnpUXzkzmR;
      string pypxJeQYqz;
      string jaFHwEYHYb;
      if(jBZispoCfp == xplNfWQTAL){njfIFRiIcb = true;}
      else if(xplNfWQTAL == jBZispoCfp){mnSiBEdzSy = true;}
      if(BfgXUmmHIe == cisfHOscwi){iLzhofQTZa = true;}
      else if(cisfHOscwi == BfgXUmmHIe){PdXeiYjcdh = true;}
      if(HnHykzZbFk == ocezOBqKCQ){SjjMaYhiXT = true;}
      else if(ocezOBqKCQ == HnHykzZbFk){HIledPjPZi = true;}
      if(dBJKkZgWVj == EsZRTuOFlb){ZdaLcFRgrr = true;}
      else if(EsZRTuOFlb == dBJKkZgWVj){nBJjOIqfFa = true;}
      if(NzUwPSMZIm == KpqeLxLrUF){wHuOQYbXSP = true;}
      else if(KpqeLxLrUF == NzUwPSMZIm){pxJDJaZUci = true;}
      if(lCqRTwtbyt == GZcBaULmze){nFgyJDzTgf = true;}
      else if(GZcBaULmze == lCqRTwtbyt){LsIcEeCmFl = true;}
      if(PNwtLzVVmt == eGQjGiIaLL){jAkJCEknEi = true;}
      else if(eGQjGiIaLL == PNwtLzVVmt){TNYjJNUnPa = true;}
      if(GPlXQHTKhR == AnpUXzkzmR){NibheKnVuC = true;}
      if(lATSybJrqn == pypxJeQYqz){wKPHeTwcBY = true;}
      if(fEYbUACZkQ == jaFHwEYHYb){FyzLHwWlLL = true;}
      while(AnpUXzkzmR == GPlXQHTKhR){hDWCrJyiVC = true;}
      while(pypxJeQYqz == pypxJeQYqz){oPmqWurfei = true;}
      while(jaFHwEYHYb == jaFHwEYHYb){GDaTGbYYsu = true;}
      if(njfIFRiIcb == true){njfIFRiIcb = false;}
      if(iLzhofQTZa == true){iLzhofQTZa = false;}
      if(SjjMaYhiXT == true){SjjMaYhiXT = false;}
      if(ZdaLcFRgrr == true){ZdaLcFRgrr = false;}
      if(wHuOQYbXSP == true){wHuOQYbXSP = false;}
      if(nFgyJDzTgf == true){nFgyJDzTgf = false;}
      if(jAkJCEknEi == true){jAkJCEknEi = false;}
      if(NibheKnVuC == true){NibheKnVuC = false;}
      if(wKPHeTwcBY == true){wKPHeTwcBY = false;}
      if(FyzLHwWlLL == true){FyzLHwWlLL = false;}
      if(mnSiBEdzSy == true){mnSiBEdzSy = false;}
      if(PdXeiYjcdh == true){PdXeiYjcdh = false;}
      if(HIledPjPZi == true){HIledPjPZi = false;}
      if(nBJjOIqfFa == true){nBJjOIqfFa = false;}
      if(pxJDJaZUci == true){pxJDJaZUci = false;}
      if(LsIcEeCmFl == true){LsIcEeCmFl = false;}
      if(TNYjJNUnPa == true){TNYjJNUnPa = false;}
      if(hDWCrJyiVC == true){hDWCrJyiVC = false;}
      if(oPmqWurfei == true){oPmqWurfei = false;}
      if(GDaTGbYYsu == true){GDaTGbYYsu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DXYZNNTMVA
{ 
  void sKSAcgyuMK()
  { 
      bool CaPfILsnSA = false;
      bool HDHikrHFjt = false;
      bool rYKtFTVVNe = false;
      bool CLMYjURWMu = false;
      bool UyEljBwDaZ = false;
      bool XZQZNdPVZo = false;
      bool oXanywpiyP = false;
      bool ZkrnZtTYJE = false;
      bool WSunHbtmLG = false;
      bool EwwXGwXQmn = false;
      bool LNEKzlgczS = false;
      bool JqLVRWclgV = false;
      bool CCWqLdoUhc = false;
      bool WDkVsJNknU = false;
      bool uRmrxMjZGi = false;
      bool TkjRkIpNyV = false;
      bool xMtWwFGpcH = false;
      bool IryLakOety = false;
      bool sPOyJlSSjj = false;
      bool TAlRXhWQwq = false;
      string MxpEyGDNdZ;
      string sEBDZxVENn;
      string IXMkVPrRwB;
      string dSpPMkrjWL;
      string YSWculfuyE;
      string xjggnnjFih;
      string NlRcuZNkpn;
      string FlgBOpBjoj;
      string ixTqEslJaY;
      string AmBoymAsgV;
      string XtEJzLCeRy;
      string mAPyyQSZYC;
      string nDKRmSkrDa;
      string oHCTLorJrr;
      string pGqclAWCpg;
      string UaUegTjmWg;
      string aKbpIexwlJ;
      string XJgfLgMgem;
      string uhCVGOlXlr;
      string EEmLRfeBTG;
      if(MxpEyGDNdZ == XtEJzLCeRy){CaPfILsnSA = true;}
      else if(XtEJzLCeRy == MxpEyGDNdZ){LNEKzlgczS = true;}
      if(sEBDZxVENn == mAPyyQSZYC){HDHikrHFjt = true;}
      else if(mAPyyQSZYC == sEBDZxVENn){JqLVRWclgV = true;}
      if(IXMkVPrRwB == nDKRmSkrDa){rYKtFTVVNe = true;}
      else if(nDKRmSkrDa == IXMkVPrRwB){CCWqLdoUhc = true;}
      if(dSpPMkrjWL == oHCTLorJrr){CLMYjURWMu = true;}
      else if(oHCTLorJrr == dSpPMkrjWL){WDkVsJNknU = true;}
      if(YSWculfuyE == pGqclAWCpg){UyEljBwDaZ = true;}
      else if(pGqclAWCpg == YSWculfuyE){uRmrxMjZGi = true;}
      if(xjggnnjFih == UaUegTjmWg){XZQZNdPVZo = true;}
      else if(UaUegTjmWg == xjggnnjFih){TkjRkIpNyV = true;}
      if(NlRcuZNkpn == aKbpIexwlJ){oXanywpiyP = true;}
      else if(aKbpIexwlJ == NlRcuZNkpn){xMtWwFGpcH = true;}
      if(FlgBOpBjoj == XJgfLgMgem){ZkrnZtTYJE = true;}
      if(ixTqEslJaY == uhCVGOlXlr){WSunHbtmLG = true;}
      if(AmBoymAsgV == EEmLRfeBTG){EwwXGwXQmn = true;}
      while(XJgfLgMgem == FlgBOpBjoj){IryLakOety = true;}
      while(uhCVGOlXlr == uhCVGOlXlr){sPOyJlSSjj = true;}
      while(EEmLRfeBTG == EEmLRfeBTG){TAlRXhWQwq = true;}
      if(CaPfILsnSA == true){CaPfILsnSA = false;}
      if(HDHikrHFjt == true){HDHikrHFjt = false;}
      if(rYKtFTVVNe == true){rYKtFTVVNe = false;}
      if(CLMYjURWMu == true){CLMYjURWMu = false;}
      if(UyEljBwDaZ == true){UyEljBwDaZ = false;}
      if(XZQZNdPVZo == true){XZQZNdPVZo = false;}
      if(oXanywpiyP == true){oXanywpiyP = false;}
      if(ZkrnZtTYJE == true){ZkrnZtTYJE = false;}
      if(WSunHbtmLG == true){WSunHbtmLG = false;}
      if(EwwXGwXQmn == true){EwwXGwXQmn = false;}
      if(LNEKzlgczS == true){LNEKzlgczS = false;}
      if(JqLVRWclgV == true){JqLVRWclgV = false;}
      if(CCWqLdoUhc == true){CCWqLdoUhc = false;}
      if(WDkVsJNknU == true){WDkVsJNknU = false;}
      if(uRmrxMjZGi == true){uRmrxMjZGi = false;}
      if(TkjRkIpNyV == true){TkjRkIpNyV = false;}
      if(xMtWwFGpcH == true){xMtWwFGpcH = false;}
      if(IryLakOety == true){IryLakOety = false;}
      if(sPOyJlSSjj == true){sPOyJlSSjj = false;}
      if(TAlRXhWQwq == true){TAlRXhWQwq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BXLSQICCTJ
{ 
  void DlUKKYZOyx()
  { 
      bool xZQeTtRDio = false;
      bool MkLrSUcQwb = false;
      bool ZrlirRkUcO = false;
      bool KZNgaBsqGI = false;
      bool gSITKOMfmL = false;
      bool filtwFmgmB = false;
      bool JwaUdlWeRR = false;
      bool alJmuGjSYc = false;
      bool FFgQibnTjU = false;
      bool OMEFyjrnoX = false;
      bool qgNVktZyyp = false;
      bool VUIJwEOJkC = false;
      bool xDtwCOhEoK = false;
      bool NwcAlXqLfo = false;
      bool BpUtztDtIt = false;
      bool UhCmamlRSV = false;
      bool LVInbYrIWY = false;
      bool MDdwAHiAxI = false;
      bool KmutoesoZz = false;
      bool lZrJcfgfRZ = false;
      string GptkDVRWhC;
      string ieoUSIPqHU;
      string zDPemUWIDk;
      string TPCsBsnQQk;
      string LnhYUlyBwL;
      string LSxOcCaOxh;
      string yJTwhScwSY;
      string UzaWILVpKA;
      string VVLqYARmPy;
      string SYShlBUkpB;
      string JChWpLraGR;
      string gjEwLcxbWh;
      string BogTGwfrjG;
      string qjAIqTmnAM;
      string IpgxRhUVWJ;
      string DrNIAUUOQt;
      string fzqzawjuFq;
      string pJaKYKIjCX;
      string aKVZDyWrIW;
      string zYXGgJzhWV;
      if(GptkDVRWhC == JChWpLraGR){xZQeTtRDio = true;}
      else if(JChWpLraGR == GptkDVRWhC){qgNVktZyyp = true;}
      if(ieoUSIPqHU == gjEwLcxbWh){MkLrSUcQwb = true;}
      else if(gjEwLcxbWh == ieoUSIPqHU){VUIJwEOJkC = true;}
      if(zDPemUWIDk == BogTGwfrjG){ZrlirRkUcO = true;}
      else if(BogTGwfrjG == zDPemUWIDk){xDtwCOhEoK = true;}
      if(TPCsBsnQQk == qjAIqTmnAM){KZNgaBsqGI = true;}
      else if(qjAIqTmnAM == TPCsBsnQQk){NwcAlXqLfo = true;}
      if(LnhYUlyBwL == IpgxRhUVWJ){gSITKOMfmL = true;}
      else if(IpgxRhUVWJ == LnhYUlyBwL){BpUtztDtIt = true;}
      if(LSxOcCaOxh == DrNIAUUOQt){filtwFmgmB = true;}
      else if(DrNIAUUOQt == LSxOcCaOxh){UhCmamlRSV = true;}
      if(yJTwhScwSY == fzqzawjuFq){JwaUdlWeRR = true;}
      else if(fzqzawjuFq == yJTwhScwSY){LVInbYrIWY = true;}
      if(UzaWILVpKA == pJaKYKIjCX){alJmuGjSYc = true;}
      if(VVLqYARmPy == aKVZDyWrIW){FFgQibnTjU = true;}
      if(SYShlBUkpB == zYXGgJzhWV){OMEFyjrnoX = true;}
      while(pJaKYKIjCX == UzaWILVpKA){MDdwAHiAxI = true;}
      while(aKVZDyWrIW == aKVZDyWrIW){KmutoesoZz = true;}
      while(zYXGgJzhWV == zYXGgJzhWV){lZrJcfgfRZ = true;}
      if(xZQeTtRDio == true){xZQeTtRDio = false;}
      if(MkLrSUcQwb == true){MkLrSUcQwb = false;}
      if(ZrlirRkUcO == true){ZrlirRkUcO = false;}
      if(KZNgaBsqGI == true){KZNgaBsqGI = false;}
      if(gSITKOMfmL == true){gSITKOMfmL = false;}
      if(filtwFmgmB == true){filtwFmgmB = false;}
      if(JwaUdlWeRR == true){JwaUdlWeRR = false;}
      if(alJmuGjSYc == true){alJmuGjSYc = false;}
      if(FFgQibnTjU == true){FFgQibnTjU = false;}
      if(OMEFyjrnoX == true){OMEFyjrnoX = false;}
      if(qgNVktZyyp == true){qgNVktZyyp = false;}
      if(VUIJwEOJkC == true){VUIJwEOJkC = false;}
      if(xDtwCOhEoK == true){xDtwCOhEoK = false;}
      if(NwcAlXqLfo == true){NwcAlXqLfo = false;}
      if(BpUtztDtIt == true){BpUtztDtIt = false;}
      if(UhCmamlRSV == true){UhCmamlRSV = false;}
      if(LVInbYrIWY == true){LVInbYrIWY = false;}
      if(MDdwAHiAxI == true){MDdwAHiAxI = false;}
      if(KmutoesoZz == true){KmutoesoZz = false;}
      if(lZrJcfgfRZ == true){lZrJcfgfRZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JELCTXHXBB
{ 
  void moABAFIGgI()
  { 
      bool ddmpgtBjgk = false;
      bool cNBDukoxNo = false;
      bool htgGlWjVAR = false;
      bool XoXswIyZQD = false;
      bool OUonnKANhX = false;
      bool RYmzujxfDK = false;
      bool JeiONmoHGl = false;
      bool mPgJaMFrSa = false;
      bool VWncAyCYyM = false;
      bool LRVFtikZaA = false;
      bool UrGukBrdXh = false;
      bool eENcolpGOO = false;
      bool kQJtaUtaPr = false;
      bool beRRGcQsqy = false;
      bool FYAPhGErQH = false;
      bool sdKMODiMUQ = false;
      bool HRNfGzmuVL = false;
      bool VxPQIMQsLT = false;
      bool PBJHyxUFCC = false;
      bool tEXaqnKUJh = false;
      string lflXaXCWXl;
      string NojPEcATBh;
      string PNWaFllGsg;
      string VeQMawIkwq;
      string qnbFbwFAIb;
      string hpLwwXJLRo;
      string kwcpPhXWoI;
      string UOWKpakRzJ;
      string glxRzeTTPC;
      string lwSHFuLlps;
      string XhLAGSTAGU;
      string lrLIIzyKqj;
      string NEHmVXuOEt;
      string PzbFkyawLf;
      string LSNtPtkKzG;
      string wAtFfTaYeh;
      string WEwLFmQGXJ;
      string YCzKYtqMWa;
      string mkPyyPEVZQ;
      string XCRcJGWBoc;
      if(lflXaXCWXl == XhLAGSTAGU){ddmpgtBjgk = true;}
      else if(XhLAGSTAGU == lflXaXCWXl){UrGukBrdXh = true;}
      if(NojPEcATBh == lrLIIzyKqj){cNBDukoxNo = true;}
      else if(lrLIIzyKqj == NojPEcATBh){eENcolpGOO = true;}
      if(PNWaFllGsg == NEHmVXuOEt){htgGlWjVAR = true;}
      else if(NEHmVXuOEt == PNWaFllGsg){kQJtaUtaPr = true;}
      if(VeQMawIkwq == PzbFkyawLf){XoXswIyZQD = true;}
      else if(PzbFkyawLf == VeQMawIkwq){beRRGcQsqy = true;}
      if(qnbFbwFAIb == LSNtPtkKzG){OUonnKANhX = true;}
      else if(LSNtPtkKzG == qnbFbwFAIb){FYAPhGErQH = true;}
      if(hpLwwXJLRo == wAtFfTaYeh){RYmzujxfDK = true;}
      else if(wAtFfTaYeh == hpLwwXJLRo){sdKMODiMUQ = true;}
      if(kwcpPhXWoI == WEwLFmQGXJ){JeiONmoHGl = true;}
      else if(WEwLFmQGXJ == kwcpPhXWoI){HRNfGzmuVL = true;}
      if(UOWKpakRzJ == YCzKYtqMWa){mPgJaMFrSa = true;}
      if(glxRzeTTPC == mkPyyPEVZQ){VWncAyCYyM = true;}
      if(lwSHFuLlps == XCRcJGWBoc){LRVFtikZaA = true;}
      while(YCzKYtqMWa == UOWKpakRzJ){VxPQIMQsLT = true;}
      while(mkPyyPEVZQ == mkPyyPEVZQ){PBJHyxUFCC = true;}
      while(XCRcJGWBoc == XCRcJGWBoc){tEXaqnKUJh = true;}
      if(ddmpgtBjgk == true){ddmpgtBjgk = false;}
      if(cNBDukoxNo == true){cNBDukoxNo = false;}
      if(htgGlWjVAR == true){htgGlWjVAR = false;}
      if(XoXswIyZQD == true){XoXswIyZQD = false;}
      if(OUonnKANhX == true){OUonnKANhX = false;}
      if(RYmzujxfDK == true){RYmzujxfDK = false;}
      if(JeiONmoHGl == true){JeiONmoHGl = false;}
      if(mPgJaMFrSa == true){mPgJaMFrSa = false;}
      if(VWncAyCYyM == true){VWncAyCYyM = false;}
      if(LRVFtikZaA == true){LRVFtikZaA = false;}
      if(UrGukBrdXh == true){UrGukBrdXh = false;}
      if(eENcolpGOO == true){eENcolpGOO = false;}
      if(kQJtaUtaPr == true){kQJtaUtaPr = false;}
      if(beRRGcQsqy == true){beRRGcQsqy = false;}
      if(FYAPhGErQH == true){FYAPhGErQH = false;}
      if(sdKMODiMUQ == true){sdKMODiMUQ = false;}
      if(HRNfGzmuVL == true){HRNfGzmuVL = false;}
      if(VxPQIMQsLT == true){VxPQIMQsLT = false;}
      if(PBJHyxUFCC == true){PBJHyxUFCC = false;}
      if(tEXaqnKUJh == true){tEXaqnKUJh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMLXKNFRGD
{ 
  void qxoSKgGkHP()
  { 
      bool BAzPqxQQBM = false;
      bool dmnBoCAxLp = false;
      bool gpVfErjTuT = false;
      bool zUXdBQaXqh = false;
      bool bEcxZljUjY = false;
      bool VmIVrLdSKy = false;
      bool NxVgNIOKAY = false;
      bool acGcNbMXGS = false;
      bool IPiWxLMBlo = false;
      bool lIMrUeiwjQ = false;
      bool WYTLysgeHP = false;
      bool zFMrpxNyiB = false;
      bool wMYKlRPOIi = false;
      bool rPnouiuXYE = false;
      bool egtVpfwTCW = false;
      bool QkNiUKAJYf = false;
      bool cSWYXiRWxG = false;
      bool CpZdVOSCTF = false;
      bool VwLkRHCETk = false;
      bool ikyraMKUyH = false;
      string htwLYxKatl;
      string eeIoFqwpou;
      string fzoyIDcWOd;
      string EomAVSUtnJ;
      string YucZoNIoRb;
      string nXByVhFyCU;
      string UmLPhoqISm;
      string VBBeVkWOIt;
      string umFlpgmodn;
      string MWqToliNrz;
      string WAWdFlVVbj;
      string LpoIYghZZB;
      string CCdeZzJhpj;
      string CJVIXuQafD;
      string KQMtbWgitH;
      string EJmqxTVrEG;
      string cnfrhCUgjd;
      string QGsVpkpiDD;
      string RanhfrVdKD;
      string YXVZaWkULY;
      if(htwLYxKatl == WAWdFlVVbj){BAzPqxQQBM = true;}
      else if(WAWdFlVVbj == htwLYxKatl){WYTLysgeHP = true;}
      if(eeIoFqwpou == LpoIYghZZB){dmnBoCAxLp = true;}
      else if(LpoIYghZZB == eeIoFqwpou){zFMrpxNyiB = true;}
      if(fzoyIDcWOd == CCdeZzJhpj){gpVfErjTuT = true;}
      else if(CCdeZzJhpj == fzoyIDcWOd){wMYKlRPOIi = true;}
      if(EomAVSUtnJ == CJVIXuQafD){zUXdBQaXqh = true;}
      else if(CJVIXuQafD == EomAVSUtnJ){rPnouiuXYE = true;}
      if(YucZoNIoRb == KQMtbWgitH){bEcxZljUjY = true;}
      else if(KQMtbWgitH == YucZoNIoRb){egtVpfwTCW = true;}
      if(nXByVhFyCU == EJmqxTVrEG){VmIVrLdSKy = true;}
      else if(EJmqxTVrEG == nXByVhFyCU){QkNiUKAJYf = true;}
      if(UmLPhoqISm == cnfrhCUgjd){NxVgNIOKAY = true;}
      else if(cnfrhCUgjd == UmLPhoqISm){cSWYXiRWxG = true;}
      if(VBBeVkWOIt == QGsVpkpiDD){acGcNbMXGS = true;}
      if(umFlpgmodn == RanhfrVdKD){IPiWxLMBlo = true;}
      if(MWqToliNrz == YXVZaWkULY){lIMrUeiwjQ = true;}
      while(QGsVpkpiDD == VBBeVkWOIt){CpZdVOSCTF = true;}
      while(RanhfrVdKD == RanhfrVdKD){VwLkRHCETk = true;}
      while(YXVZaWkULY == YXVZaWkULY){ikyraMKUyH = true;}
      if(BAzPqxQQBM == true){BAzPqxQQBM = false;}
      if(dmnBoCAxLp == true){dmnBoCAxLp = false;}
      if(gpVfErjTuT == true){gpVfErjTuT = false;}
      if(zUXdBQaXqh == true){zUXdBQaXqh = false;}
      if(bEcxZljUjY == true){bEcxZljUjY = false;}
      if(VmIVrLdSKy == true){VmIVrLdSKy = false;}
      if(NxVgNIOKAY == true){NxVgNIOKAY = false;}
      if(acGcNbMXGS == true){acGcNbMXGS = false;}
      if(IPiWxLMBlo == true){IPiWxLMBlo = false;}
      if(lIMrUeiwjQ == true){lIMrUeiwjQ = false;}
      if(WYTLysgeHP == true){WYTLysgeHP = false;}
      if(zFMrpxNyiB == true){zFMrpxNyiB = false;}
      if(wMYKlRPOIi == true){wMYKlRPOIi = false;}
      if(rPnouiuXYE == true){rPnouiuXYE = false;}
      if(egtVpfwTCW == true){egtVpfwTCW = false;}
      if(QkNiUKAJYf == true){QkNiUKAJYf = false;}
      if(cSWYXiRWxG == true){cSWYXiRWxG = false;}
      if(CpZdVOSCTF == true){CpZdVOSCTF = false;}
      if(VwLkRHCETk == true){VwLkRHCETk = false;}
      if(ikyraMKUyH == true){ikyraMKUyH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKZMGEKAGK
{ 
  void QlxxpTIXpk()
  { 
      bool EXjDrfNDGY = false;
      bool ZjcwXCYIWW = false;
      bool LQAHXGywcb = false;
      bool uFxzCjsYSM = false;
      bool JgbyuxUjtg = false;
      bool qfkTgnWbel = false;
      bool hQaddUmcsm = false;
      bool IAoKNdnBLa = false;
      bool kNCujOUdSO = false;
      bool MRsgdrGxUa = false;
      bool KrqGXqqZFD = false;
      bool zVPEATOetP = false;
      bool AIKdZqGHfV = false;
      bool WqgkPsWuXr = false;
      bool WtXOOqBogK = false;
      bool cbCFaBhMgf = false;
      bool kitifIoeoH = false;
      bool xTHCrGkuPi = false;
      bool pRaVsunaJO = false;
      bool KKOqGnzoiG = false;
      string xxzrThTSQP;
      string ULNxDtIlpQ;
      string TEWMaFoGYA;
      string xqlJdJnRhM;
      string mhJdduBUIp;
      string NqFwerZmRO;
      string rMtPRcYDSt;
      string GpEcdltshe;
      string DUyhmFkodl;
      string iBzSUZmsLB;
      string VxBNjWmbSs;
      string xfElKXOLcL;
      string riZgKEpkID;
      string yBhgIFSjxP;
      string SIWknDwNIx;
      string KbQzImXUDf;
      string fBTPtwyXdF;
      string EeNMsjMnrH;
      string IccLrWkhXV;
      string gyfRjQnHqr;
      if(xxzrThTSQP == VxBNjWmbSs){EXjDrfNDGY = true;}
      else if(VxBNjWmbSs == xxzrThTSQP){KrqGXqqZFD = true;}
      if(ULNxDtIlpQ == xfElKXOLcL){ZjcwXCYIWW = true;}
      else if(xfElKXOLcL == ULNxDtIlpQ){zVPEATOetP = true;}
      if(TEWMaFoGYA == riZgKEpkID){LQAHXGywcb = true;}
      else if(riZgKEpkID == TEWMaFoGYA){AIKdZqGHfV = true;}
      if(xqlJdJnRhM == yBhgIFSjxP){uFxzCjsYSM = true;}
      else if(yBhgIFSjxP == xqlJdJnRhM){WqgkPsWuXr = true;}
      if(mhJdduBUIp == SIWknDwNIx){JgbyuxUjtg = true;}
      else if(SIWknDwNIx == mhJdduBUIp){WtXOOqBogK = true;}
      if(NqFwerZmRO == KbQzImXUDf){qfkTgnWbel = true;}
      else if(KbQzImXUDf == NqFwerZmRO){cbCFaBhMgf = true;}
      if(rMtPRcYDSt == fBTPtwyXdF){hQaddUmcsm = true;}
      else if(fBTPtwyXdF == rMtPRcYDSt){kitifIoeoH = true;}
      if(GpEcdltshe == EeNMsjMnrH){IAoKNdnBLa = true;}
      if(DUyhmFkodl == IccLrWkhXV){kNCujOUdSO = true;}
      if(iBzSUZmsLB == gyfRjQnHqr){MRsgdrGxUa = true;}
      while(EeNMsjMnrH == GpEcdltshe){xTHCrGkuPi = true;}
      while(IccLrWkhXV == IccLrWkhXV){pRaVsunaJO = true;}
      while(gyfRjQnHqr == gyfRjQnHqr){KKOqGnzoiG = true;}
      if(EXjDrfNDGY == true){EXjDrfNDGY = false;}
      if(ZjcwXCYIWW == true){ZjcwXCYIWW = false;}
      if(LQAHXGywcb == true){LQAHXGywcb = false;}
      if(uFxzCjsYSM == true){uFxzCjsYSM = false;}
      if(JgbyuxUjtg == true){JgbyuxUjtg = false;}
      if(qfkTgnWbel == true){qfkTgnWbel = false;}
      if(hQaddUmcsm == true){hQaddUmcsm = false;}
      if(IAoKNdnBLa == true){IAoKNdnBLa = false;}
      if(kNCujOUdSO == true){kNCujOUdSO = false;}
      if(MRsgdrGxUa == true){MRsgdrGxUa = false;}
      if(KrqGXqqZFD == true){KrqGXqqZFD = false;}
      if(zVPEATOetP == true){zVPEATOetP = false;}
      if(AIKdZqGHfV == true){AIKdZqGHfV = false;}
      if(WqgkPsWuXr == true){WqgkPsWuXr = false;}
      if(WtXOOqBogK == true){WtXOOqBogK = false;}
      if(cbCFaBhMgf == true){cbCFaBhMgf = false;}
      if(kitifIoeoH == true){kitifIoeoH = false;}
      if(xTHCrGkuPi == true){xTHCrGkuPi = false;}
      if(pRaVsunaJO == true){pRaVsunaJO = false;}
      if(KKOqGnzoiG == true){KKOqGnzoiG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MLRUIFQBPG
{ 
  void bsLaAObFIm()
  { 
      bool RYGWmmQGBB = false;
      bool ytrJxuDkqp = false;
      bool iIMPDQbwJf = false;
      bool cBLatDcorU = false;
      bool fghNrkOdzO = false;
      bool sKDZmILqTV = false;
      bool LTwVYxhQPt = false;
      bool ROrVJBayWR = false;
      bool CxxumSxknk = false;
      bool qkVWJLkMou = false;
      bool CxOEwdRgQl = false;
      bool gNUBSNWBiF = false;
      bool zxcdDgrVMy = false;
      bool QOIaPEirzI = false;
      bool AQUBDcQUDw = false;
      bool oiciwFUkBP = false;
      bool luURUSEslO = false;
      bool ddCZFicaZa = false;
      bool PXSPJgkZeJ = false;
      bool jyqiVFuCgk = false;
      string tYeSZwBIWc;
      string FtHthZYqIm;
      string AImODjsaTw;
      string pAzcSzgVgk;
      string BQJGPffKZu;
      string esfuekkPPo;
      string DZoZmFtdai;
      string sCKXljygzW;
      string EhAYQwTDyg;
      string NQFqgabjTK;
      string kBjqBbiHJu;
      string mEQrkVYQIp;
      string kpesUbxSqK;
      string HOMolCxJWo;
      string NMtDtJANGL;
      string CKadZtWqVZ;
      string eQQzmXqbGi;
      string XPtTcXwbyL;
      string bjMfHxniOq;
      string fGnxJwutQW;
      if(tYeSZwBIWc == kBjqBbiHJu){RYGWmmQGBB = true;}
      else if(kBjqBbiHJu == tYeSZwBIWc){CxOEwdRgQl = true;}
      if(FtHthZYqIm == mEQrkVYQIp){ytrJxuDkqp = true;}
      else if(mEQrkVYQIp == FtHthZYqIm){gNUBSNWBiF = true;}
      if(AImODjsaTw == kpesUbxSqK){iIMPDQbwJf = true;}
      else if(kpesUbxSqK == AImODjsaTw){zxcdDgrVMy = true;}
      if(pAzcSzgVgk == HOMolCxJWo){cBLatDcorU = true;}
      else if(HOMolCxJWo == pAzcSzgVgk){QOIaPEirzI = true;}
      if(BQJGPffKZu == NMtDtJANGL){fghNrkOdzO = true;}
      else if(NMtDtJANGL == BQJGPffKZu){AQUBDcQUDw = true;}
      if(esfuekkPPo == CKadZtWqVZ){sKDZmILqTV = true;}
      else if(CKadZtWqVZ == esfuekkPPo){oiciwFUkBP = true;}
      if(DZoZmFtdai == eQQzmXqbGi){LTwVYxhQPt = true;}
      else if(eQQzmXqbGi == DZoZmFtdai){luURUSEslO = true;}
      if(sCKXljygzW == XPtTcXwbyL){ROrVJBayWR = true;}
      if(EhAYQwTDyg == bjMfHxniOq){CxxumSxknk = true;}
      if(NQFqgabjTK == fGnxJwutQW){qkVWJLkMou = true;}
      while(XPtTcXwbyL == sCKXljygzW){ddCZFicaZa = true;}
      while(bjMfHxniOq == bjMfHxniOq){PXSPJgkZeJ = true;}
      while(fGnxJwutQW == fGnxJwutQW){jyqiVFuCgk = true;}
      if(RYGWmmQGBB == true){RYGWmmQGBB = false;}
      if(ytrJxuDkqp == true){ytrJxuDkqp = false;}
      if(iIMPDQbwJf == true){iIMPDQbwJf = false;}
      if(cBLatDcorU == true){cBLatDcorU = false;}
      if(fghNrkOdzO == true){fghNrkOdzO = false;}
      if(sKDZmILqTV == true){sKDZmILqTV = false;}
      if(LTwVYxhQPt == true){LTwVYxhQPt = false;}
      if(ROrVJBayWR == true){ROrVJBayWR = false;}
      if(CxxumSxknk == true){CxxumSxknk = false;}
      if(qkVWJLkMou == true){qkVWJLkMou = false;}
      if(CxOEwdRgQl == true){CxOEwdRgQl = false;}
      if(gNUBSNWBiF == true){gNUBSNWBiF = false;}
      if(zxcdDgrVMy == true){zxcdDgrVMy = false;}
      if(QOIaPEirzI == true){QOIaPEirzI = false;}
      if(AQUBDcQUDw == true){AQUBDcQUDw = false;}
      if(oiciwFUkBP == true){oiciwFUkBP = false;}
      if(luURUSEslO == true){luURUSEslO = false;}
      if(ddCZFicaZa == true){ddCZFicaZa = false;}
      if(PXSPJgkZeJ == true){PXSPJgkZeJ = false;}
      if(jyqiVFuCgk == true){jyqiVFuCgk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EGBQDTSINF
{ 
  void keSFFbWHSw()
  { 
      bool kcjXhwtVJH = false;
      bool XRUSFAZdTS = false;
      bool MRjkwwsPyX = false;
      bool eHlkSlaFGE = false;
      bool EjuHWkJSyn = false;
      bool OcZtDTszbl = false;
      bool CdXkcQfizT = false;
      bool ZTWPNbVbNL = false;
      bool laQKICgqhz = false;
      bool sadUBaMJeF = false;
      bool EaSeNuGKga = false;
      bool xQkQzbMMcZ = false;
      bool ioAAZzpCNm = false;
      bool PMxIGLHlxN = false;
      bool uWKGBbpNUZ = false;
      bool NAgEWPZREO = false;
      bool EEwsLkTcJn = false;
      bool TaOOdLdtzy = false;
      bool IcgnZOfrkq = false;
      bool lohiIqaQuP = false;
      string keypsFaSpt;
      string qiEWXsTXDr;
      string NmeXeGUsjP;
      string soFNRGMbeU;
      string xrYbITnMBt;
      string cxzrCyAZLm;
      string jgiaACcqER;
      string fqshtVOCPK;
      string RIrolwpMLT;
      string FmQrjQIxaF;
      string pxHiOlEQyf;
      string jyJAUbntnE;
      string LQekLsaBxc;
      string NQbJUUBIZA;
      string rZOfiHcPXI;
      string bOJWtZRWWV;
      string LDSURSWzfz;
      string afTmMlBzBE;
      string PKdoAzGEPu;
      string DdlEonGtNP;
      if(keypsFaSpt == pxHiOlEQyf){kcjXhwtVJH = true;}
      else if(pxHiOlEQyf == keypsFaSpt){EaSeNuGKga = true;}
      if(qiEWXsTXDr == jyJAUbntnE){XRUSFAZdTS = true;}
      else if(jyJAUbntnE == qiEWXsTXDr){xQkQzbMMcZ = true;}
      if(NmeXeGUsjP == LQekLsaBxc){MRjkwwsPyX = true;}
      else if(LQekLsaBxc == NmeXeGUsjP){ioAAZzpCNm = true;}
      if(soFNRGMbeU == NQbJUUBIZA){eHlkSlaFGE = true;}
      else if(NQbJUUBIZA == soFNRGMbeU){PMxIGLHlxN = true;}
      if(xrYbITnMBt == rZOfiHcPXI){EjuHWkJSyn = true;}
      else if(rZOfiHcPXI == xrYbITnMBt){uWKGBbpNUZ = true;}
      if(cxzrCyAZLm == bOJWtZRWWV){OcZtDTszbl = true;}
      else if(bOJWtZRWWV == cxzrCyAZLm){NAgEWPZREO = true;}
      if(jgiaACcqER == LDSURSWzfz){CdXkcQfizT = true;}
      else if(LDSURSWzfz == jgiaACcqER){EEwsLkTcJn = true;}
      if(fqshtVOCPK == afTmMlBzBE){ZTWPNbVbNL = true;}
      if(RIrolwpMLT == PKdoAzGEPu){laQKICgqhz = true;}
      if(FmQrjQIxaF == DdlEonGtNP){sadUBaMJeF = true;}
      while(afTmMlBzBE == fqshtVOCPK){TaOOdLdtzy = true;}
      while(PKdoAzGEPu == PKdoAzGEPu){IcgnZOfrkq = true;}
      while(DdlEonGtNP == DdlEonGtNP){lohiIqaQuP = true;}
      if(kcjXhwtVJH == true){kcjXhwtVJH = false;}
      if(XRUSFAZdTS == true){XRUSFAZdTS = false;}
      if(MRjkwwsPyX == true){MRjkwwsPyX = false;}
      if(eHlkSlaFGE == true){eHlkSlaFGE = false;}
      if(EjuHWkJSyn == true){EjuHWkJSyn = false;}
      if(OcZtDTszbl == true){OcZtDTszbl = false;}
      if(CdXkcQfizT == true){CdXkcQfizT = false;}
      if(ZTWPNbVbNL == true){ZTWPNbVbNL = false;}
      if(laQKICgqhz == true){laQKICgqhz = false;}
      if(sadUBaMJeF == true){sadUBaMJeF = false;}
      if(EaSeNuGKga == true){EaSeNuGKga = false;}
      if(xQkQzbMMcZ == true){xQkQzbMMcZ = false;}
      if(ioAAZzpCNm == true){ioAAZzpCNm = false;}
      if(PMxIGLHlxN == true){PMxIGLHlxN = false;}
      if(uWKGBbpNUZ == true){uWKGBbpNUZ = false;}
      if(NAgEWPZREO == true){NAgEWPZREO = false;}
      if(EEwsLkTcJn == true){EEwsLkTcJn = false;}
      if(TaOOdLdtzy == true){TaOOdLdtzy = false;}
      if(IcgnZOfrkq == true){IcgnZOfrkq = false;}
      if(lohiIqaQuP == true){lohiIqaQuP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IZGLXTMKNV
{ 
  void OAToNFXQXb()
  { 
      bool hDytmhynVX = false;
      bool LoUFwJKziT = false;
      bool ntcABoVIxJ = false;
      bool TVGyAMSkPz = false;
      bool PhEbDIjwEe = false;
      bool AUxrqmZyry = false;
      bool MoqMDohWFi = false;
      bool pZijDFoAws = false;
      bool FYESJzYOGM = false;
      bool lTrQlaqrXN = false;
      bool ZNqUnZkMnl = false;
      bool yYBzsmkYDE = false;
      bool QSQrwVgSxc = false;
      bool OxciSrhidi = false;
      bool NLaTOMSsXz = false;
      bool oSoSwHwyYR = false;
      bool sSOKXAwSfB = false;
      bool ECtTqFrwdi = false;
      bool DmtymuHKlL = false;
      bool ujKMpuwPwN = false;
      string xshifimfhk;
      string bKHxiyUyQu;
      string SSbQDCNNpL;
      string zKJycHjkbB;
      string qTwxlNcoAV;
      string pjBHCdQRfd;
      string VZpVkRBITa;
      string NjVPEyWdeo;
      string YXNTVPIBwy;
      string pSEyeQcZMT;
      string MTUYHGNlDD;
      string HmmqExLVAV;
      string JzLVkueXjm;
      string VwRKbFDoMP;
      string BVxsqDeNsg;
      string FHZpKNHzmL;
      string apCQhKUbOz;
      string tWJkUmCSdh;
      string PReCgNWazO;
      string xEBAnLTfLf;
      if(xshifimfhk == MTUYHGNlDD){hDytmhynVX = true;}
      else if(MTUYHGNlDD == xshifimfhk){ZNqUnZkMnl = true;}
      if(bKHxiyUyQu == HmmqExLVAV){LoUFwJKziT = true;}
      else if(HmmqExLVAV == bKHxiyUyQu){yYBzsmkYDE = true;}
      if(SSbQDCNNpL == JzLVkueXjm){ntcABoVIxJ = true;}
      else if(JzLVkueXjm == SSbQDCNNpL){QSQrwVgSxc = true;}
      if(zKJycHjkbB == VwRKbFDoMP){TVGyAMSkPz = true;}
      else if(VwRKbFDoMP == zKJycHjkbB){OxciSrhidi = true;}
      if(qTwxlNcoAV == BVxsqDeNsg){PhEbDIjwEe = true;}
      else if(BVxsqDeNsg == qTwxlNcoAV){NLaTOMSsXz = true;}
      if(pjBHCdQRfd == FHZpKNHzmL){AUxrqmZyry = true;}
      else if(FHZpKNHzmL == pjBHCdQRfd){oSoSwHwyYR = true;}
      if(VZpVkRBITa == apCQhKUbOz){MoqMDohWFi = true;}
      else if(apCQhKUbOz == VZpVkRBITa){sSOKXAwSfB = true;}
      if(NjVPEyWdeo == tWJkUmCSdh){pZijDFoAws = true;}
      if(YXNTVPIBwy == PReCgNWazO){FYESJzYOGM = true;}
      if(pSEyeQcZMT == xEBAnLTfLf){lTrQlaqrXN = true;}
      while(tWJkUmCSdh == NjVPEyWdeo){ECtTqFrwdi = true;}
      while(PReCgNWazO == PReCgNWazO){DmtymuHKlL = true;}
      while(xEBAnLTfLf == xEBAnLTfLf){ujKMpuwPwN = true;}
      if(hDytmhynVX == true){hDytmhynVX = false;}
      if(LoUFwJKziT == true){LoUFwJKziT = false;}
      if(ntcABoVIxJ == true){ntcABoVIxJ = false;}
      if(TVGyAMSkPz == true){TVGyAMSkPz = false;}
      if(PhEbDIjwEe == true){PhEbDIjwEe = false;}
      if(AUxrqmZyry == true){AUxrqmZyry = false;}
      if(MoqMDohWFi == true){MoqMDohWFi = false;}
      if(pZijDFoAws == true){pZijDFoAws = false;}
      if(FYESJzYOGM == true){FYESJzYOGM = false;}
      if(lTrQlaqrXN == true){lTrQlaqrXN = false;}
      if(ZNqUnZkMnl == true){ZNqUnZkMnl = false;}
      if(yYBzsmkYDE == true){yYBzsmkYDE = false;}
      if(QSQrwVgSxc == true){QSQrwVgSxc = false;}
      if(OxciSrhidi == true){OxciSrhidi = false;}
      if(NLaTOMSsXz == true){NLaTOMSsXz = false;}
      if(oSoSwHwyYR == true){oSoSwHwyYR = false;}
      if(sSOKXAwSfB == true){sSOKXAwSfB = false;}
      if(ECtTqFrwdi == true){ECtTqFrwdi = false;}
      if(DmtymuHKlL == true){DmtymuHKlL = false;}
      if(ujKMpuwPwN == true){ujKMpuwPwN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GHTYTQOHIA
{ 
  void wYcyuhJymy()
  { 
      bool WEeuTOQTMm = false;
      bool XMADoUwEIh = false;
      bool ZOIecKyBSK = false;
      bool MBNPcSBEGm = false;
      bool aSADYXlrsp = false;
      bool NzIgoIwASJ = false;
      bool QPABZWykaW = false;
      bool SryVHHNEFE = false;
      bool XFHcwNrfZT = false;
      bool VBlwVLSydC = false;
      bool ZBRWXVBmZh = false;
      bool trtOkLHWFM = false;
      bool dRKGBRFBzu = false;
      bool oPZDeWmkEZ = false;
      bool LFGrYdGWLK = false;
      bool DusRYHpKUG = false;
      bool PzmereRqiO = false;
      bool XWSeAXLRgW = false;
      bool KhpoqtWIeW = false;
      bool fcPyKMSazt = false;
      string kqyHNBQRBX;
      string EezbSPfhiL;
      string iNNGMkbWyF;
      string dAjPuzpTaI;
      string xDlFHiwTVN;
      string COwkCXdrtc;
      string ZtSusEuifT;
      string YMHZOfaHyc;
      string nHBkDPEzNX;
      string UxYxiCjpMD;
      string nMnBnpGVWW;
      string wWtRoRshrd;
      string zwVHyanJqL;
      string ujutobTzwN;
      string IhcqbyDHIR;
      string JCyhDrqfDM;
      string BxdKaLazbM;
      string xtkeVQTdez;
      string WgAZCrlMpx;
      string jmwiLKERPP;
      if(kqyHNBQRBX == nMnBnpGVWW){WEeuTOQTMm = true;}
      else if(nMnBnpGVWW == kqyHNBQRBX){ZBRWXVBmZh = true;}
      if(EezbSPfhiL == wWtRoRshrd){XMADoUwEIh = true;}
      else if(wWtRoRshrd == EezbSPfhiL){trtOkLHWFM = true;}
      if(iNNGMkbWyF == zwVHyanJqL){ZOIecKyBSK = true;}
      else if(zwVHyanJqL == iNNGMkbWyF){dRKGBRFBzu = true;}
      if(dAjPuzpTaI == ujutobTzwN){MBNPcSBEGm = true;}
      else if(ujutobTzwN == dAjPuzpTaI){oPZDeWmkEZ = true;}
      if(xDlFHiwTVN == IhcqbyDHIR){aSADYXlrsp = true;}
      else if(IhcqbyDHIR == xDlFHiwTVN){LFGrYdGWLK = true;}
      if(COwkCXdrtc == JCyhDrqfDM){NzIgoIwASJ = true;}
      else if(JCyhDrqfDM == COwkCXdrtc){DusRYHpKUG = true;}
      if(ZtSusEuifT == BxdKaLazbM){QPABZWykaW = true;}
      else if(BxdKaLazbM == ZtSusEuifT){PzmereRqiO = true;}
      if(YMHZOfaHyc == xtkeVQTdez){SryVHHNEFE = true;}
      if(nHBkDPEzNX == WgAZCrlMpx){XFHcwNrfZT = true;}
      if(UxYxiCjpMD == jmwiLKERPP){VBlwVLSydC = true;}
      while(xtkeVQTdez == YMHZOfaHyc){XWSeAXLRgW = true;}
      while(WgAZCrlMpx == WgAZCrlMpx){KhpoqtWIeW = true;}
      while(jmwiLKERPP == jmwiLKERPP){fcPyKMSazt = true;}
      if(WEeuTOQTMm == true){WEeuTOQTMm = false;}
      if(XMADoUwEIh == true){XMADoUwEIh = false;}
      if(ZOIecKyBSK == true){ZOIecKyBSK = false;}
      if(MBNPcSBEGm == true){MBNPcSBEGm = false;}
      if(aSADYXlrsp == true){aSADYXlrsp = false;}
      if(NzIgoIwASJ == true){NzIgoIwASJ = false;}
      if(QPABZWykaW == true){QPABZWykaW = false;}
      if(SryVHHNEFE == true){SryVHHNEFE = false;}
      if(XFHcwNrfZT == true){XFHcwNrfZT = false;}
      if(VBlwVLSydC == true){VBlwVLSydC = false;}
      if(ZBRWXVBmZh == true){ZBRWXVBmZh = false;}
      if(trtOkLHWFM == true){trtOkLHWFM = false;}
      if(dRKGBRFBzu == true){dRKGBRFBzu = false;}
      if(oPZDeWmkEZ == true){oPZDeWmkEZ = false;}
      if(LFGrYdGWLK == true){LFGrYdGWLK = false;}
      if(DusRYHpKUG == true){DusRYHpKUG = false;}
      if(PzmereRqiO == true){PzmereRqiO = false;}
      if(XWSeAXLRgW == true){XWSeAXLRgW = false;}
      if(KhpoqtWIeW == true){KhpoqtWIeW = false;}
      if(fcPyKMSazt == true){fcPyKMSazt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MPDZIEETMW
{ 
  void tYpuKbqRQz()
  { 
      bool mBPyecZknc = false;
      bool HNQGCMTwWD = false;
      bool ztQIqqNKPf = false;
      bool DDIlGOLJEs = false;
      bool XNfCipLgxi = false;
      bool GaqiXsjHGm = false;
      bool OPVHZEEeAn = false;
      bool AKqcelNOYB = false;
      bool egNfZbLYNN = false;
      bool dDCQeIqYce = false;
      bool kggIiuiODl = false;
      bool eViFHgBphx = false;
      bool rfRlKwHZxW = false;
      bool tolsQyAEwd = false;
      bool rxVahHUwIy = false;
      bool GBpemFPtyl = false;
      bool mIQgrojooJ = false;
      bool gxsDEtKpEC = false;
      bool bLQzPryHGL = false;
      bool iFFKpjfnir = false;
      string UswWSijIbo;
      string kpWkzWkKGO;
      string woAyoHDJcR;
      string EnPMsXcNKB;
      string twCkfYCwYb;
      string CbUOlerygK;
      string eZfKjxaKrb;
      string sXzFUAmPRP;
      string EHkBOcSBZN;
      string eefzVTPrBh;
      string yrEwhebPsl;
      string rcfQGWoeuH;
      string dYjdwOqAiA;
      string jtOiQLCnTj;
      string BDHnUCyPsz;
      string dkwsDZIZAS;
      string nafsBxOwzt;
      string TBLLFaRuJt;
      string PaHjVyyUeq;
      string DcmAwZXNmW;
      if(UswWSijIbo == yrEwhebPsl){mBPyecZknc = true;}
      else if(yrEwhebPsl == UswWSijIbo){kggIiuiODl = true;}
      if(kpWkzWkKGO == rcfQGWoeuH){HNQGCMTwWD = true;}
      else if(rcfQGWoeuH == kpWkzWkKGO){eViFHgBphx = true;}
      if(woAyoHDJcR == dYjdwOqAiA){ztQIqqNKPf = true;}
      else if(dYjdwOqAiA == woAyoHDJcR){rfRlKwHZxW = true;}
      if(EnPMsXcNKB == jtOiQLCnTj){DDIlGOLJEs = true;}
      else if(jtOiQLCnTj == EnPMsXcNKB){tolsQyAEwd = true;}
      if(twCkfYCwYb == BDHnUCyPsz){XNfCipLgxi = true;}
      else if(BDHnUCyPsz == twCkfYCwYb){rxVahHUwIy = true;}
      if(CbUOlerygK == dkwsDZIZAS){GaqiXsjHGm = true;}
      else if(dkwsDZIZAS == CbUOlerygK){GBpemFPtyl = true;}
      if(eZfKjxaKrb == nafsBxOwzt){OPVHZEEeAn = true;}
      else if(nafsBxOwzt == eZfKjxaKrb){mIQgrojooJ = true;}
      if(sXzFUAmPRP == TBLLFaRuJt){AKqcelNOYB = true;}
      if(EHkBOcSBZN == PaHjVyyUeq){egNfZbLYNN = true;}
      if(eefzVTPrBh == DcmAwZXNmW){dDCQeIqYce = true;}
      while(TBLLFaRuJt == sXzFUAmPRP){gxsDEtKpEC = true;}
      while(PaHjVyyUeq == PaHjVyyUeq){bLQzPryHGL = true;}
      while(DcmAwZXNmW == DcmAwZXNmW){iFFKpjfnir = true;}
      if(mBPyecZknc == true){mBPyecZknc = false;}
      if(HNQGCMTwWD == true){HNQGCMTwWD = false;}
      if(ztQIqqNKPf == true){ztQIqqNKPf = false;}
      if(DDIlGOLJEs == true){DDIlGOLJEs = false;}
      if(XNfCipLgxi == true){XNfCipLgxi = false;}
      if(GaqiXsjHGm == true){GaqiXsjHGm = false;}
      if(OPVHZEEeAn == true){OPVHZEEeAn = false;}
      if(AKqcelNOYB == true){AKqcelNOYB = false;}
      if(egNfZbLYNN == true){egNfZbLYNN = false;}
      if(dDCQeIqYce == true){dDCQeIqYce = false;}
      if(kggIiuiODl == true){kggIiuiODl = false;}
      if(eViFHgBphx == true){eViFHgBphx = false;}
      if(rfRlKwHZxW == true){rfRlKwHZxW = false;}
      if(tolsQyAEwd == true){tolsQyAEwd = false;}
      if(rxVahHUwIy == true){rxVahHUwIy = false;}
      if(GBpemFPtyl == true){GBpemFPtyl = false;}
      if(mIQgrojooJ == true){mIQgrojooJ = false;}
      if(gxsDEtKpEC == true){gxsDEtKpEC = false;}
      if(bLQzPryHGL == true){bLQzPryHGL = false;}
      if(iFFKpjfnir == true){iFFKpjfnir = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PCFQNYOGVW
{ 
  void PWfxyntefJ()
  { 
      bool xtDLYWVAKT = false;
      bool THdqeWyksr = false;
      bool adPrzqzxDw = false;
      bool oyCcPOaESh = false;
      bool kWISWCDQSb = false;
      bool JfTJRSdKMg = false;
      bool WYwNeUEAaP = false;
      bool utRKGEUxVw = false;
      bool midalIesLx = false;
      bool kQrkKMZtnC = false;
      bool xDoDgPOICN = false;
      bool xgoPtntVbV = false;
      bool pLodeeBfzt = false;
      bool daITzjsatV = false;
      bool tVpyzDabqW = false;
      bool RESSLlNLXB = false;
      bool NiIIiWYVQJ = false;
      bool tTaFaTVqea = false;
      bool DZncbYHpHN = false;
      bool VhCrHLNgOb = false;
      string SXaPFjLMSG;
      string cixDLkZAqf;
      string iLSXolkRxu;
      string GSRRXeQRRA;
      string tMdrkSyqrP;
      string biHVsHFDZS;
      string ytOXAKReeg;
      string TIiplVgZmV;
      string nsYhTXKuYQ;
      string YNqyBAyGrZ;
      string BSMLuSzQjW;
      string ZePEdEUgDc;
      string zWGNHGRknk;
      string XahMUVgMlA;
      string XsLBqtxmTw;
      string eQDPZdLzEn;
      string BOcyzyxCiI;
      string XIuCEGKEVM;
      string JeQqFHXSmp;
      string JgIxzIQMCr;
      if(SXaPFjLMSG == BSMLuSzQjW){xtDLYWVAKT = true;}
      else if(BSMLuSzQjW == SXaPFjLMSG){xDoDgPOICN = true;}
      if(cixDLkZAqf == ZePEdEUgDc){THdqeWyksr = true;}
      else if(ZePEdEUgDc == cixDLkZAqf){xgoPtntVbV = true;}
      if(iLSXolkRxu == zWGNHGRknk){adPrzqzxDw = true;}
      else if(zWGNHGRknk == iLSXolkRxu){pLodeeBfzt = true;}
      if(GSRRXeQRRA == XahMUVgMlA){oyCcPOaESh = true;}
      else if(XahMUVgMlA == GSRRXeQRRA){daITzjsatV = true;}
      if(tMdrkSyqrP == XsLBqtxmTw){kWISWCDQSb = true;}
      else if(XsLBqtxmTw == tMdrkSyqrP){tVpyzDabqW = true;}
      if(biHVsHFDZS == eQDPZdLzEn){JfTJRSdKMg = true;}
      else if(eQDPZdLzEn == biHVsHFDZS){RESSLlNLXB = true;}
      if(ytOXAKReeg == BOcyzyxCiI){WYwNeUEAaP = true;}
      else if(BOcyzyxCiI == ytOXAKReeg){NiIIiWYVQJ = true;}
      if(TIiplVgZmV == XIuCEGKEVM){utRKGEUxVw = true;}
      if(nsYhTXKuYQ == JeQqFHXSmp){midalIesLx = true;}
      if(YNqyBAyGrZ == JgIxzIQMCr){kQrkKMZtnC = true;}
      while(XIuCEGKEVM == TIiplVgZmV){tTaFaTVqea = true;}
      while(JeQqFHXSmp == JeQqFHXSmp){DZncbYHpHN = true;}
      while(JgIxzIQMCr == JgIxzIQMCr){VhCrHLNgOb = true;}
      if(xtDLYWVAKT == true){xtDLYWVAKT = false;}
      if(THdqeWyksr == true){THdqeWyksr = false;}
      if(adPrzqzxDw == true){adPrzqzxDw = false;}
      if(oyCcPOaESh == true){oyCcPOaESh = false;}
      if(kWISWCDQSb == true){kWISWCDQSb = false;}
      if(JfTJRSdKMg == true){JfTJRSdKMg = false;}
      if(WYwNeUEAaP == true){WYwNeUEAaP = false;}
      if(utRKGEUxVw == true){utRKGEUxVw = false;}
      if(midalIesLx == true){midalIesLx = false;}
      if(kQrkKMZtnC == true){kQrkKMZtnC = false;}
      if(xDoDgPOICN == true){xDoDgPOICN = false;}
      if(xgoPtntVbV == true){xgoPtntVbV = false;}
      if(pLodeeBfzt == true){pLodeeBfzt = false;}
      if(daITzjsatV == true){daITzjsatV = false;}
      if(tVpyzDabqW == true){tVpyzDabqW = false;}
      if(RESSLlNLXB == true){RESSLlNLXB = false;}
      if(NiIIiWYVQJ == true){NiIIiWYVQJ = false;}
      if(tTaFaTVqea == true){tTaFaTVqea = false;}
      if(DZncbYHpHN == true){DZncbYHpHN = false;}
      if(VhCrHLNgOb == true){VhCrHLNgOb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ASZJTIQNUA
{ 
  void QhpFaOHinR()
  { 
      bool ylZUoSCKhE = false;
      bool UNYHEBOJUR = false;
      bool AnqWseeEjc = false;
      bool uWFJzQMNIR = false;
      bool LqBduSDPms = false;
      bool KAezdKtCbK = false;
      bool nyZFIxIOHn = false;
      bool oBBCFIlNaZ = false;
      bool aPQpRtqFfo = false;
      bool WJkydNQwVx = false;
      bool JnIzEJzbsU = false;
      bool XgbBiYgjnN = false;
      bool GChRRfPDYr = false;
      bool qprdPmGRkH = false;
      bool uPLLRphjOF = false;
      bool ffHHqHFphY = false;
      bool twDAcgoxkw = false;
      bool RPyfSpqWzb = false;
      bool xfnTMLijmI = false;
      bool gQjMNyMKhj = false;
      string UhIKlHDCyC;
      string FWACfYiCtk;
      string ThIJndqUlN;
      string gKdqKqdcqH;
      string gLmdfMLWQQ;
      string rknOBmYyVH;
      string PiQjUurIqn;
      string uFLlDItedb;
      string SUEUVwVPpX;
      string RfGiqyuDJj;
      string TCfbVlZCKs;
      string rtTtouduNY;
      string ZbSSVOyctE;
      string NqUsHPobzi;
      string WSFweXLMtw;
      string UzokKqjMFH;
      string nxIFfBYZlY;
      string GBweCGWVmy;
      string ClhyjNBjiP;
      string fbWruZKAQd;
      if(UhIKlHDCyC == TCfbVlZCKs){ylZUoSCKhE = true;}
      else if(TCfbVlZCKs == UhIKlHDCyC){JnIzEJzbsU = true;}
      if(FWACfYiCtk == rtTtouduNY){UNYHEBOJUR = true;}
      else if(rtTtouduNY == FWACfYiCtk){XgbBiYgjnN = true;}
      if(ThIJndqUlN == ZbSSVOyctE){AnqWseeEjc = true;}
      else if(ZbSSVOyctE == ThIJndqUlN){GChRRfPDYr = true;}
      if(gKdqKqdcqH == NqUsHPobzi){uWFJzQMNIR = true;}
      else if(NqUsHPobzi == gKdqKqdcqH){qprdPmGRkH = true;}
      if(gLmdfMLWQQ == WSFweXLMtw){LqBduSDPms = true;}
      else if(WSFweXLMtw == gLmdfMLWQQ){uPLLRphjOF = true;}
      if(rknOBmYyVH == UzokKqjMFH){KAezdKtCbK = true;}
      else if(UzokKqjMFH == rknOBmYyVH){ffHHqHFphY = true;}
      if(PiQjUurIqn == nxIFfBYZlY){nyZFIxIOHn = true;}
      else if(nxIFfBYZlY == PiQjUurIqn){twDAcgoxkw = true;}
      if(uFLlDItedb == GBweCGWVmy){oBBCFIlNaZ = true;}
      if(SUEUVwVPpX == ClhyjNBjiP){aPQpRtqFfo = true;}
      if(RfGiqyuDJj == fbWruZKAQd){WJkydNQwVx = true;}
      while(GBweCGWVmy == uFLlDItedb){RPyfSpqWzb = true;}
      while(ClhyjNBjiP == ClhyjNBjiP){xfnTMLijmI = true;}
      while(fbWruZKAQd == fbWruZKAQd){gQjMNyMKhj = true;}
      if(ylZUoSCKhE == true){ylZUoSCKhE = false;}
      if(UNYHEBOJUR == true){UNYHEBOJUR = false;}
      if(AnqWseeEjc == true){AnqWseeEjc = false;}
      if(uWFJzQMNIR == true){uWFJzQMNIR = false;}
      if(LqBduSDPms == true){LqBduSDPms = false;}
      if(KAezdKtCbK == true){KAezdKtCbK = false;}
      if(nyZFIxIOHn == true){nyZFIxIOHn = false;}
      if(oBBCFIlNaZ == true){oBBCFIlNaZ = false;}
      if(aPQpRtqFfo == true){aPQpRtqFfo = false;}
      if(WJkydNQwVx == true){WJkydNQwVx = false;}
      if(JnIzEJzbsU == true){JnIzEJzbsU = false;}
      if(XgbBiYgjnN == true){XgbBiYgjnN = false;}
      if(GChRRfPDYr == true){GChRRfPDYr = false;}
      if(qprdPmGRkH == true){qprdPmGRkH = false;}
      if(uPLLRphjOF == true){uPLLRphjOF = false;}
      if(ffHHqHFphY == true){ffHHqHFphY = false;}
      if(twDAcgoxkw == true){twDAcgoxkw = false;}
      if(RPyfSpqWzb == true){RPyfSpqWzb = false;}
      if(xfnTMLijmI == true){xfnTMLijmI = false;}
      if(gQjMNyMKhj == true){gQjMNyMKhj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RDISSGMTSN
{ 
  void aoscJQXcbs()
  { 
      bool GdeyAJaahM = false;
      bool hkFhdccCxS = false;
      bool okLedzfPLb = false;
      bool YmHdAMjrbV = false;
      bool BfkLPuETQX = false;
      bool kcyTuUSATA = false;
      bool cLOGmucagR = false;
      bool sjabQJAzOi = false;
      bool uMympwnnie = false;
      bool siXarpRdXU = false;
      bool RclzeBBVCl = false;
      bool USkkEQNaPq = false;
      bool GnrBXJLAja = false;
      bool qVasQSZzIo = false;
      bool tRlwKaymWa = false;
      bool bpNgOdjjaU = false;
      bool oBlatyrqUk = false;
      bool qORawnCuqx = false;
      bool LYcIzBHsel = false;
      bool ioXmzsfKCL = false;
      string ltsduXGUYR;
      string VwIaSfLtWg;
      string FEJuwFkgFE;
      string seOiFrmjSl;
      string qcOUXGimhQ;
      string rsCongkyhp;
      string lYPTXqgYVZ;
      string raakocpnWo;
      string VxznLAbYuY;
      string HnCczRMuwg;
      string ZJRHYRSQAL;
      string qwasUoZaHX;
      string PIdxSDYylW;
      string PtqpPLeqPt;
      string hKYigLNIHK;
      string rlmYRQfUoU;
      string sTecwwEjcJ;
      string JhKMpEiuPH;
      string pPqbecGSYy;
      string fJCuBNfwmk;
      if(ltsduXGUYR == ZJRHYRSQAL){GdeyAJaahM = true;}
      else if(ZJRHYRSQAL == ltsduXGUYR){RclzeBBVCl = true;}
      if(VwIaSfLtWg == qwasUoZaHX){hkFhdccCxS = true;}
      else if(qwasUoZaHX == VwIaSfLtWg){USkkEQNaPq = true;}
      if(FEJuwFkgFE == PIdxSDYylW){okLedzfPLb = true;}
      else if(PIdxSDYylW == FEJuwFkgFE){GnrBXJLAja = true;}
      if(seOiFrmjSl == PtqpPLeqPt){YmHdAMjrbV = true;}
      else if(PtqpPLeqPt == seOiFrmjSl){qVasQSZzIo = true;}
      if(qcOUXGimhQ == hKYigLNIHK){BfkLPuETQX = true;}
      else if(hKYigLNIHK == qcOUXGimhQ){tRlwKaymWa = true;}
      if(rsCongkyhp == rlmYRQfUoU){kcyTuUSATA = true;}
      else if(rlmYRQfUoU == rsCongkyhp){bpNgOdjjaU = true;}
      if(lYPTXqgYVZ == sTecwwEjcJ){cLOGmucagR = true;}
      else if(sTecwwEjcJ == lYPTXqgYVZ){oBlatyrqUk = true;}
      if(raakocpnWo == JhKMpEiuPH){sjabQJAzOi = true;}
      if(VxznLAbYuY == pPqbecGSYy){uMympwnnie = true;}
      if(HnCczRMuwg == fJCuBNfwmk){siXarpRdXU = true;}
      while(JhKMpEiuPH == raakocpnWo){qORawnCuqx = true;}
      while(pPqbecGSYy == pPqbecGSYy){LYcIzBHsel = true;}
      while(fJCuBNfwmk == fJCuBNfwmk){ioXmzsfKCL = true;}
      if(GdeyAJaahM == true){GdeyAJaahM = false;}
      if(hkFhdccCxS == true){hkFhdccCxS = false;}
      if(okLedzfPLb == true){okLedzfPLb = false;}
      if(YmHdAMjrbV == true){YmHdAMjrbV = false;}
      if(BfkLPuETQX == true){BfkLPuETQX = false;}
      if(kcyTuUSATA == true){kcyTuUSATA = false;}
      if(cLOGmucagR == true){cLOGmucagR = false;}
      if(sjabQJAzOi == true){sjabQJAzOi = false;}
      if(uMympwnnie == true){uMympwnnie = false;}
      if(siXarpRdXU == true){siXarpRdXU = false;}
      if(RclzeBBVCl == true){RclzeBBVCl = false;}
      if(USkkEQNaPq == true){USkkEQNaPq = false;}
      if(GnrBXJLAja == true){GnrBXJLAja = false;}
      if(qVasQSZzIo == true){qVasQSZzIo = false;}
      if(tRlwKaymWa == true){tRlwKaymWa = false;}
      if(bpNgOdjjaU == true){bpNgOdjjaU = false;}
      if(oBlatyrqUk == true){oBlatyrqUk = false;}
      if(qORawnCuqx == true){qORawnCuqx = false;}
      if(LYcIzBHsel == true){LYcIzBHsel = false;}
      if(ioXmzsfKCL == true){ioXmzsfKCL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HLZDXKTMMI
{ 
  void CUpyObPfQY()
  { 
      bool JausAHFlkD = false;
      bool AnIXChPMYB = false;
      bool QYtQJiekDx = false;
      bool jYynBmAXIW = false;
      bool UyhuejrCDn = false;
      bool tfBxzkfdiR = false;
      bool bThnTboTWO = false;
      bool grECgSpylY = false;
      bool pcgPDEWAnQ = false;
      bool GVoqtAPtbC = false;
      bool uXfnGCazQg = false;
      bool thqJaylSkP = false;
      bool EneGHLDNHg = false;
      bool CwWidRxsJA = false;
      bool cXjHWYeePw = false;
      bool NxJMyGrZgu = false;
      bool zNridxKIfJ = false;
      bool BsJjlgEXih = false;
      bool gXxLSFlKkW = false;
      bool YXMNBOfAcY = false;
      string rhdaziDncS;
      string znCryFPyVa;
      string aJSznifdDn;
      string CcnDBZZHko;
      string EtZKtdLdVf;
      string XlxQdiPemQ;
      string CYkoQWAzqX;
      string eHMfWfiIEJ;
      string WCIWPQeWZS;
      string KuUUleJktX;
      string dLlxAQYQtx;
      string zHZcsAQNYz;
      string qcZXNjmrtq;
      string VxNffKPKWz;
      string qOcbSCUqak;
      string NwMtgAlNiQ;
      string cgVCbCstwh;
      string jGqZIczyFK;
      string OuQJdZkTzf;
      string YBaFVKrazQ;
      if(rhdaziDncS == dLlxAQYQtx){JausAHFlkD = true;}
      else if(dLlxAQYQtx == rhdaziDncS){uXfnGCazQg = true;}
      if(znCryFPyVa == zHZcsAQNYz){AnIXChPMYB = true;}
      else if(zHZcsAQNYz == znCryFPyVa){thqJaylSkP = true;}
      if(aJSznifdDn == qcZXNjmrtq){QYtQJiekDx = true;}
      else if(qcZXNjmrtq == aJSznifdDn){EneGHLDNHg = true;}
      if(CcnDBZZHko == VxNffKPKWz){jYynBmAXIW = true;}
      else if(VxNffKPKWz == CcnDBZZHko){CwWidRxsJA = true;}
      if(EtZKtdLdVf == qOcbSCUqak){UyhuejrCDn = true;}
      else if(qOcbSCUqak == EtZKtdLdVf){cXjHWYeePw = true;}
      if(XlxQdiPemQ == NwMtgAlNiQ){tfBxzkfdiR = true;}
      else if(NwMtgAlNiQ == XlxQdiPemQ){NxJMyGrZgu = true;}
      if(CYkoQWAzqX == cgVCbCstwh){bThnTboTWO = true;}
      else if(cgVCbCstwh == CYkoQWAzqX){zNridxKIfJ = true;}
      if(eHMfWfiIEJ == jGqZIczyFK){grECgSpylY = true;}
      if(WCIWPQeWZS == OuQJdZkTzf){pcgPDEWAnQ = true;}
      if(KuUUleJktX == YBaFVKrazQ){GVoqtAPtbC = true;}
      while(jGqZIczyFK == eHMfWfiIEJ){BsJjlgEXih = true;}
      while(OuQJdZkTzf == OuQJdZkTzf){gXxLSFlKkW = true;}
      while(YBaFVKrazQ == YBaFVKrazQ){YXMNBOfAcY = true;}
      if(JausAHFlkD == true){JausAHFlkD = false;}
      if(AnIXChPMYB == true){AnIXChPMYB = false;}
      if(QYtQJiekDx == true){QYtQJiekDx = false;}
      if(jYynBmAXIW == true){jYynBmAXIW = false;}
      if(UyhuejrCDn == true){UyhuejrCDn = false;}
      if(tfBxzkfdiR == true){tfBxzkfdiR = false;}
      if(bThnTboTWO == true){bThnTboTWO = false;}
      if(grECgSpylY == true){grECgSpylY = false;}
      if(pcgPDEWAnQ == true){pcgPDEWAnQ = false;}
      if(GVoqtAPtbC == true){GVoqtAPtbC = false;}
      if(uXfnGCazQg == true){uXfnGCazQg = false;}
      if(thqJaylSkP == true){thqJaylSkP = false;}
      if(EneGHLDNHg == true){EneGHLDNHg = false;}
      if(CwWidRxsJA == true){CwWidRxsJA = false;}
      if(cXjHWYeePw == true){cXjHWYeePw = false;}
      if(NxJMyGrZgu == true){NxJMyGrZgu = false;}
      if(zNridxKIfJ == true){zNridxKIfJ = false;}
      if(BsJjlgEXih == true){BsJjlgEXih = false;}
      if(gXxLSFlKkW == true){gXxLSFlKkW = false;}
      if(YXMNBOfAcY == true){YXMNBOfAcY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MEWGTANWXA
{ 
  void ABtAFkpLyn()
  { 
      bool esnmEBCggA = false;
      bool BhcTWiQGms = false;
      bool MVJSKozBfN = false;
      bool WIfkzbjtOP = false;
      bool CwQBpmrjkB = false;
      bool HhbEWIjUcO = false;
      bool BBBScrCrUu = false;
      bool zWqWpPFHcX = false;
      bool wOPdFofbOp = false;
      bool rOQANBuxXx = false;
      bool kAPpCkpENG = false;
      bool DbrFRmlXMn = false;
      bool LZcdCjFqJo = false;
      bool UIjelwyYaU = false;
      bool zaOHmPWLha = false;
      bool OWjjlLWkmS = false;
      bool ezuYltqNSV = false;
      bool nNwrojKVqm = false;
      bool MsJiZxXAsa = false;
      bool YMkHpAfpVr = false;
      string guUhbgDRfo;
      string KdAikPVDNZ;
      string kcKpcrpTpx;
      string HLwOwVJbSk;
      string txrMmxXepX;
      string YjmEDDjdFi;
      string pibihzhklO;
      string FsjcfmkxDe;
      string ULdRYWYqLr;
      string kfWitKVIen;
      string PlraRezJYP;
      string SlaZOeFJKK;
      string apZtcZWBiV;
      string RbSOPhTCAs;
      string WOSuZzExTP;
      string ELyUMYMxyr;
      string IyZDypTLJg;
      string KDJQmLXdUd;
      string UYgTQFdxCq;
      string VVEIkYnOxi;
      if(guUhbgDRfo == PlraRezJYP){esnmEBCggA = true;}
      else if(PlraRezJYP == guUhbgDRfo){kAPpCkpENG = true;}
      if(KdAikPVDNZ == SlaZOeFJKK){BhcTWiQGms = true;}
      else if(SlaZOeFJKK == KdAikPVDNZ){DbrFRmlXMn = true;}
      if(kcKpcrpTpx == apZtcZWBiV){MVJSKozBfN = true;}
      else if(apZtcZWBiV == kcKpcrpTpx){LZcdCjFqJo = true;}
      if(HLwOwVJbSk == RbSOPhTCAs){WIfkzbjtOP = true;}
      else if(RbSOPhTCAs == HLwOwVJbSk){UIjelwyYaU = true;}
      if(txrMmxXepX == WOSuZzExTP){CwQBpmrjkB = true;}
      else if(WOSuZzExTP == txrMmxXepX){zaOHmPWLha = true;}
      if(YjmEDDjdFi == ELyUMYMxyr){HhbEWIjUcO = true;}
      else if(ELyUMYMxyr == YjmEDDjdFi){OWjjlLWkmS = true;}
      if(pibihzhklO == IyZDypTLJg){BBBScrCrUu = true;}
      else if(IyZDypTLJg == pibihzhklO){ezuYltqNSV = true;}
      if(FsjcfmkxDe == KDJQmLXdUd){zWqWpPFHcX = true;}
      if(ULdRYWYqLr == UYgTQFdxCq){wOPdFofbOp = true;}
      if(kfWitKVIen == VVEIkYnOxi){rOQANBuxXx = true;}
      while(KDJQmLXdUd == FsjcfmkxDe){nNwrojKVqm = true;}
      while(UYgTQFdxCq == UYgTQFdxCq){MsJiZxXAsa = true;}
      while(VVEIkYnOxi == VVEIkYnOxi){YMkHpAfpVr = true;}
      if(esnmEBCggA == true){esnmEBCggA = false;}
      if(BhcTWiQGms == true){BhcTWiQGms = false;}
      if(MVJSKozBfN == true){MVJSKozBfN = false;}
      if(WIfkzbjtOP == true){WIfkzbjtOP = false;}
      if(CwQBpmrjkB == true){CwQBpmrjkB = false;}
      if(HhbEWIjUcO == true){HhbEWIjUcO = false;}
      if(BBBScrCrUu == true){BBBScrCrUu = false;}
      if(zWqWpPFHcX == true){zWqWpPFHcX = false;}
      if(wOPdFofbOp == true){wOPdFofbOp = false;}
      if(rOQANBuxXx == true){rOQANBuxXx = false;}
      if(kAPpCkpENG == true){kAPpCkpENG = false;}
      if(DbrFRmlXMn == true){DbrFRmlXMn = false;}
      if(LZcdCjFqJo == true){LZcdCjFqJo = false;}
      if(UIjelwyYaU == true){UIjelwyYaU = false;}
      if(zaOHmPWLha == true){zaOHmPWLha = false;}
      if(OWjjlLWkmS == true){OWjjlLWkmS = false;}
      if(ezuYltqNSV == true){ezuYltqNSV = false;}
      if(nNwrojKVqm == true){nNwrojKVqm = false;}
      if(MsJiZxXAsa == true){MsJiZxXAsa = false;}
      if(YMkHpAfpVr == true){YMkHpAfpVr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDWYGOSOIX
{ 
  void TeJBjLwFeX()
  { 
      bool QkVbUZNOWQ = false;
      bool qwyINDfJoA = false;
      bool rnsCsEUojn = false;
      bool ZppafKfogi = false;
      bool XJfctityld = false;
      bool pjSlCbrTiP = false;
      bool FYdhqBGWbD = false;
      bool XqcFchIPIK = false;
      bool KVDGyoXEYD = false;
      bool RMGRdzfxlr = false;
      bool bWVhFzHMIT = false;
      bool TcKXEiUXjB = false;
      bool dByXkLkLad = false;
      bool CKcPhnAUAz = false;
      bool hKuEjoBhMu = false;
      bool dINjOaXyxt = false;
      bool NuleRIztoQ = false;
      bool iAXkTTGsnu = false;
      bool KCyfztxsBH = false;
      bool PCWFklXPma = false;
      string GESIIGrLPL;
      string WADOGKlizI;
      string TqbKdAgdbE;
      string wLfGyOyDlC;
      string FhxcULWREo;
      string AMaOKPcHeH;
      string ZNiKOKTwPr;
      string LiwwDlszoR;
      string dOYlEjjQwh;
      string lqXdcqymNK;
      string qZBLdQPeKY;
      string WcRNcKoxFe;
      string ZDAgGULRTM;
      string mFkeZEMMIm;
      string TFFXLIYJBR;
      string CBghknYTFJ;
      string FxLykQqmnY;
      string xbnSLTxcVx;
      string uBQBJkYDtk;
      string erGzhWtHlt;
      if(GESIIGrLPL == qZBLdQPeKY){QkVbUZNOWQ = true;}
      else if(qZBLdQPeKY == GESIIGrLPL){bWVhFzHMIT = true;}
      if(WADOGKlizI == WcRNcKoxFe){qwyINDfJoA = true;}
      else if(WcRNcKoxFe == WADOGKlizI){TcKXEiUXjB = true;}
      if(TqbKdAgdbE == ZDAgGULRTM){rnsCsEUojn = true;}
      else if(ZDAgGULRTM == TqbKdAgdbE){dByXkLkLad = true;}
      if(wLfGyOyDlC == mFkeZEMMIm){ZppafKfogi = true;}
      else if(mFkeZEMMIm == wLfGyOyDlC){CKcPhnAUAz = true;}
      if(FhxcULWREo == TFFXLIYJBR){XJfctityld = true;}
      else if(TFFXLIYJBR == FhxcULWREo){hKuEjoBhMu = true;}
      if(AMaOKPcHeH == CBghknYTFJ){pjSlCbrTiP = true;}
      else if(CBghknYTFJ == AMaOKPcHeH){dINjOaXyxt = true;}
      if(ZNiKOKTwPr == FxLykQqmnY){FYdhqBGWbD = true;}
      else if(FxLykQqmnY == ZNiKOKTwPr){NuleRIztoQ = true;}
      if(LiwwDlszoR == xbnSLTxcVx){XqcFchIPIK = true;}
      if(dOYlEjjQwh == uBQBJkYDtk){KVDGyoXEYD = true;}
      if(lqXdcqymNK == erGzhWtHlt){RMGRdzfxlr = true;}
      while(xbnSLTxcVx == LiwwDlszoR){iAXkTTGsnu = true;}
      while(uBQBJkYDtk == uBQBJkYDtk){KCyfztxsBH = true;}
      while(erGzhWtHlt == erGzhWtHlt){PCWFklXPma = true;}
      if(QkVbUZNOWQ == true){QkVbUZNOWQ = false;}
      if(qwyINDfJoA == true){qwyINDfJoA = false;}
      if(rnsCsEUojn == true){rnsCsEUojn = false;}
      if(ZppafKfogi == true){ZppafKfogi = false;}
      if(XJfctityld == true){XJfctityld = false;}
      if(pjSlCbrTiP == true){pjSlCbrTiP = false;}
      if(FYdhqBGWbD == true){FYdhqBGWbD = false;}
      if(XqcFchIPIK == true){XqcFchIPIK = false;}
      if(KVDGyoXEYD == true){KVDGyoXEYD = false;}
      if(RMGRdzfxlr == true){RMGRdzfxlr = false;}
      if(bWVhFzHMIT == true){bWVhFzHMIT = false;}
      if(TcKXEiUXjB == true){TcKXEiUXjB = false;}
      if(dByXkLkLad == true){dByXkLkLad = false;}
      if(CKcPhnAUAz == true){CKcPhnAUAz = false;}
      if(hKuEjoBhMu == true){hKuEjoBhMu = false;}
      if(dINjOaXyxt == true){dINjOaXyxt = false;}
      if(NuleRIztoQ == true){NuleRIztoQ = false;}
      if(iAXkTTGsnu == true){iAXkTTGsnu = false;}
      if(KCyfztxsBH == true){KCyfztxsBH = false;}
      if(PCWFklXPma == true){PCWFklXPma = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UAFZRNQKZL
{ 
  void yCTnAehnih()
  { 
      bool MTuGMXZOhm = false;
      bool NqBXmmDCoU = false;
      bool koLrcOqHWM = false;
      bool ohyKGPMtuB = false;
      bool eskipHipMt = false;
      bool MdcpUXHCcy = false;
      bool gRqUyfsqRW = false;
      bool ZIGmprDbBV = false;
      bool eBuczKEHpi = false;
      bool IKRxTMBPkK = false;
      bool NqXoUDWozb = false;
      bool TeAGSfVOVm = false;
      bool akBiOOqJTd = false;
      bool pmqqHncGHw = false;
      bool mOHNOcKKdm = false;
      bool qmtyicpnaF = false;
      bool LNVVkfnJze = false;
      bool DPGZzLdmUl = false;
      bool EgfglDsrHe = false;
      bool ynfCjZskbh = false;
      string XZQXGdExfu;
      string SpuqYexada;
      string OeBDritIob;
      string oiJDLecnhw;
      string iSEOEcmMYK;
      string EgMJHsXMfX;
      string iuHEGigqft;
      string BIsgqwZlzP;
      string uhjeXIWzwR;
      string GPIJMnKzIU;
      string wufeIumeRL;
      string SlNQbBKcgx;
      string MgtOmlAiUD;
      string kadeSzCFVb;
      string UqgkyUCrhL;
      string cgSKIOBRqW;
      string uEKOZrHhxb;
      string yEHEcUAJPS;
      string jHAIZEHSWE;
      string yjNzgQfRLF;
      if(XZQXGdExfu == wufeIumeRL){MTuGMXZOhm = true;}
      else if(wufeIumeRL == XZQXGdExfu){NqXoUDWozb = true;}
      if(SpuqYexada == SlNQbBKcgx){NqBXmmDCoU = true;}
      else if(SlNQbBKcgx == SpuqYexada){TeAGSfVOVm = true;}
      if(OeBDritIob == MgtOmlAiUD){koLrcOqHWM = true;}
      else if(MgtOmlAiUD == OeBDritIob){akBiOOqJTd = true;}
      if(oiJDLecnhw == kadeSzCFVb){ohyKGPMtuB = true;}
      else if(kadeSzCFVb == oiJDLecnhw){pmqqHncGHw = true;}
      if(iSEOEcmMYK == UqgkyUCrhL){eskipHipMt = true;}
      else if(UqgkyUCrhL == iSEOEcmMYK){mOHNOcKKdm = true;}
      if(EgMJHsXMfX == cgSKIOBRqW){MdcpUXHCcy = true;}
      else if(cgSKIOBRqW == EgMJHsXMfX){qmtyicpnaF = true;}
      if(iuHEGigqft == uEKOZrHhxb){gRqUyfsqRW = true;}
      else if(uEKOZrHhxb == iuHEGigqft){LNVVkfnJze = true;}
      if(BIsgqwZlzP == yEHEcUAJPS){ZIGmprDbBV = true;}
      if(uhjeXIWzwR == jHAIZEHSWE){eBuczKEHpi = true;}
      if(GPIJMnKzIU == yjNzgQfRLF){IKRxTMBPkK = true;}
      while(yEHEcUAJPS == BIsgqwZlzP){DPGZzLdmUl = true;}
      while(jHAIZEHSWE == jHAIZEHSWE){EgfglDsrHe = true;}
      while(yjNzgQfRLF == yjNzgQfRLF){ynfCjZskbh = true;}
      if(MTuGMXZOhm == true){MTuGMXZOhm = false;}
      if(NqBXmmDCoU == true){NqBXmmDCoU = false;}
      if(koLrcOqHWM == true){koLrcOqHWM = false;}
      if(ohyKGPMtuB == true){ohyKGPMtuB = false;}
      if(eskipHipMt == true){eskipHipMt = false;}
      if(MdcpUXHCcy == true){MdcpUXHCcy = false;}
      if(gRqUyfsqRW == true){gRqUyfsqRW = false;}
      if(ZIGmprDbBV == true){ZIGmprDbBV = false;}
      if(eBuczKEHpi == true){eBuczKEHpi = false;}
      if(IKRxTMBPkK == true){IKRxTMBPkK = false;}
      if(NqXoUDWozb == true){NqXoUDWozb = false;}
      if(TeAGSfVOVm == true){TeAGSfVOVm = false;}
      if(akBiOOqJTd == true){akBiOOqJTd = false;}
      if(pmqqHncGHw == true){pmqqHncGHw = false;}
      if(mOHNOcKKdm == true){mOHNOcKKdm = false;}
      if(qmtyicpnaF == true){qmtyicpnaF = false;}
      if(LNVVkfnJze == true){LNVVkfnJze = false;}
      if(DPGZzLdmUl == true){DPGZzLdmUl = false;}
      if(EgfglDsrHe == true){EgfglDsrHe = false;}
      if(ynfCjZskbh == true){ynfCjZskbh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZLGEUIRUMI
{ 
  void RejYYXGrzm()
  { 
      bool ZcSYRAREYH = false;
      bool psnjwCUhbw = false;
      bool amlsPXyKox = false;
      bool rHcdsfnduq = false;
      bool hETVbzwIWc = false;
      bool idpiklpZJs = false;
      bool CHObPiPKqP = false;
      bool NqljOWSPQP = false;
      bool bomMONQtrG = false;
      bool pOTCoaorGr = false;
      bool jkQHOqqFUO = false;
      bool SZIsQMTBMB = false;
      bool SVRjYyWjum = false;
      bool gZJYfpXexW = false;
      bool VKZdnPGZkc = false;
      bool GmeEZNSghQ = false;
      bool UGKggrQjNa = false;
      bool nnEpfIwnwJ = false;
      bool rwzSgstFzR = false;
      bool WqxgCOzrwu = false;
      string ZCMjLPBblW;
      string SzUCFanmAK;
      string dqhpfbFkrs;
      string KPCMyZWcSK;
      string uhaNaXuWJL;
      string HaYPoiTWDi;
      string JPisLCxHDf;
      string DLToOuPUOI;
      string giagkiqlWP;
      string FAYiBfyhBY;
      string ZmSdIwHiBt;
      string SzHtCZnCIb;
      string LKkmZCljnh;
      string whSphtQxYn;
      string aHkcxGsega;
      string qwYZMPBeDF;
      string JXuSxjgQLI;
      string JqdTAEYIpS;
      string JHCMqAJsdS;
      string rksSeDMReM;
      if(ZCMjLPBblW == ZmSdIwHiBt){ZcSYRAREYH = true;}
      else if(ZmSdIwHiBt == ZCMjLPBblW){jkQHOqqFUO = true;}
      if(SzUCFanmAK == SzHtCZnCIb){psnjwCUhbw = true;}
      else if(SzHtCZnCIb == SzUCFanmAK){SZIsQMTBMB = true;}
      if(dqhpfbFkrs == LKkmZCljnh){amlsPXyKox = true;}
      else if(LKkmZCljnh == dqhpfbFkrs){SVRjYyWjum = true;}
      if(KPCMyZWcSK == whSphtQxYn){rHcdsfnduq = true;}
      else if(whSphtQxYn == KPCMyZWcSK){gZJYfpXexW = true;}
      if(uhaNaXuWJL == aHkcxGsega){hETVbzwIWc = true;}
      else if(aHkcxGsega == uhaNaXuWJL){VKZdnPGZkc = true;}
      if(HaYPoiTWDi == qwYZMPBeDF){idpiklpZJs = true;}
      else if(qwYZMPBeDF == HaYPoiTWDi){GmeEZNSghQ = true;}
      if(JPisLCxHDf == JXuSxjgQLI){CHObPiPKqP = true;}
      else if(JXuSxjgQLI == JPisLCxHDf){UGKggrQjNa = true;}
      if(DLToOuPUOI == JqdTAEYIpS){NqljOWSPQP = true;}
      if(giagkiqlWP == JHCMqAJsdS){bomMONQtrG = true;}
      if(FAYiBfyhBY == rksSeDMReM){pOTCoaorGr = true;}
      while(JqdTAEYIpS == DLToOuPUOI){nnEpfIwnwJ = true;}
      while(JHCMqAJsdS == JHCMqAJsdS){rwzSgstFzR = true;}
      while(rksSeDMReM == rksSeDMReM){WqxgCOzrwu = true;}
      if(ZcSYRAREYH == true){ZcSYRAREYH = false;}
      if(psnjwCUhbw == true){psnjwCUhbw = false;}
      if(amlsPXyKox == true){amlsPXyKox = false;}
      if(rHcdsfnduq == true){rHcdsfnduq = false;}
      if(hETVbzwIWc == true){hETVbzwIWc = false;}
      if(idpiklpZJs == true){idpiklpZJs = false;}
      if(CHObPiPKqP == true){CHObPiPKqP = false;}
      if(NqljOWSPQP == true){NqljOWSPQP = false;}
      if(bomMONQtrG == true){bomMONQtrG = false;}
      if(pOTCoaorGr == true){pOTCoaorGr = false;}
      if(jkQHOqqFUO == true){jkQHOqqFUO = false;}
      if(SZIsQMTBMB == true){SZIsQMTBMB = false;}
      if(SVRjYyWjum == true){SVRjYyWjum = false;}
      if(gZJYfpXexW == true){gZJYfpXexW = false;}
      if(VKZdnPGZkc == true){VKZdnPGZkc = false;}
      if(GmeEZNSghQ == true){GmeEZNSghQ = false;}
      if(UGKggrQjNa == true){UGKggrQjNa = false;}
      if(nnEpfIwnwJ == true){nnEpfIwnwJ = false;}
      if(rwzSgstFzR == true){rwzSgstFzR = false;}
      if(WqxgCOzrwu == true){WqxgCOzrwu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UZOAOCQMWA
{ 
  void GfsNsCOZNV()
  { 
      bool amnzsnwgdz = false;
      bool ynucVLiukU = false;
      bool ScyJhWlhgI = false;
      bool hDyFDeMnyF = false;
      bool LhuwmZjPCz = false;
      bool hMkZwxodRW = false;
      bool BNzVQupoYq = false;
      bool zuxfIkhCWH = false;
      bool mWfhaUSXJF = false;
      bool phWaDyhZeq = false;
      bool jtpLzlPEQL = false;
      bool PlHJjdgRtw = false;
      bool cRfTAQYVbK = false;
      bool CIXeXrgUhn = false;
      bool FNHypEaNqZ = false;
      bool RQeiOROWKi = false;
      bool NscGIGObkq = false;
      bool xMiFpOKhcw = false;
      bool oKdCrlcoQG = false;
      bool dJJzaMkAoi = false;
      string EOhlMUqbgp;
      string hCSBNNgBwx;
      string gFgrWZuyEu;
      string dammRsBFbR;
      string oxbggNeSjB;
      string YgFxYzgoOm;
      string ZsXlMGPejT;
      string MaYeHjczKI;
      string ucOCVxVoNS;
      string LLporwYoUZ;
      string yzhPoxHZoo;
      string VheGrwdUPP;
      string kZRRIAkjmL;
      string LnejKutzNX;
      string ouAYxdgjwu;
      string SDYFoYgPGo;
      string MXmdcgCtuw;
      string BeHrapZsUd;
      string SAnqsHOZul;
      string OerYKRHVuP;
      if(EOhlMUqbgp == yzhPoxHZoo){amnzsnwgdz = true;}
      else if(yzhPoxHZoo == EOhlMUqbgp){jtpLzlPEQL = true;}
      if(hCSBNNgBwx == VheGrwdUPP){ynucVLiukU = true;}
      else if(VheGrwdUPP == hCSBNNgBwx){PlHJjdgRtw = true;}
      if(gFgrWZuyEu == kZRRIAkjmL){ScyJhWlhgI = true;}
      else if(kZRRIAkjmL == gFgrWZuyEu){cRfTAQYVbK = true;}
      if(dammRsBFbR == LnejKutzNX){hDyFDeMnyF = true;}
      else if(LnejKutzNX == dammRsBFbR){CIXeXrgUhn = true;}
      if(oxbggNeSjB == ouAYxdgjwu){LhuwmZjPCz = true;}
      else if(ouAYxdgjwu == oxbggNeSjB){FNHypEaNqZ = true;}
      if(YgFxYzgoOm == SDYFoYgPGo){hMkZwxodRW = true;}
      else if(SDYFoYgPGo == YgFxYzgoOm){RQeiOROWKi = true;}
      if(ZsXlMGPejT == MXmdcgCtuw){BNzVQupoYq = true;}
      else if(MXmdcgCtuw == ZsXlMGPejT){NscGIGObkq = true;}
      if(MaYeHjczKI == BeHrapZsUd){zuxfIkhCWH = true;}
      if(ucOCVxVoNS == SAnqsHOZul){mWfhaUSXJF = true;}
      if(LLporwYoUZ == OerYKRHVuP){phWaDyhZeq = true;}
      while(BeHrapZsUd == MaYeHjczKI){xMiFpOKhcw = true;}
      while(SAnqsHOZul == SAnqsHOZul){oKdCrlcoQG = true;}
      while(OerYKRHVuP == OerYKRHVuP){dJJzaMkAoi = true;}
      if(amnzsnwgdz == true){amnzsnwgdz = false;}
      if(ynucVLiukU == true){ynucVLiukU = false;}
      if(ScyJhWlhgI == true){ScyJhWlhgI = false;}
      if(hDyFDeMnyF == true){hDyFDeMnyF = false;}
      if(LhuwmZjPCz == true){LhuwmZjPCz = false;}
      if(hMkZwxodRW == true){hMkZwxodRW = false;}
      if(BNzVQupoYq == true){BNzVQupoYq = false;}
      if(zuxfIkhCWH == true){zuxfIkhCWH = false;}
      if(mWfhaUSXJF == true){mWfhaUSXJF = false;}
      if(phWaDyhZeq == true){phWaDyhZeq = false;}
      if(jtpLzlPEQL == true){jtpLzlPEQL = false;}
      if(PlHJjdgRtw == true){PlHJjdgRtw = false;}
      if(cRfTAQYVbK == true){cRfTAQYVbK = false;}
      if(CIXeXrgUhn == true){CIXeXrgUhn = false;}
      if(FNHypEaNqZ == true){FNHypEaNqZ = false;}
      if(RQeiOROWKi == true){RQeiOROWKi = false;}
      if(NscGIGObkq == true){NscGIGObkq = false;}
      if(xMiFpOKhcw == true){xMiFpOKhcw = false;}
      if(oKdCrlcoQG == true){oKdCrlcoQG = false;}
      if(dJJzaMkAoi == true){dJJzaMkAoi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LLCTUWDQZK
{ 
  void AbwrjYunOl()
  { 
      bool zqqGMHspNZ = false;
      bool OjPzQeIeRs = false;
      bool ySZsVrFUxh = false;
      bool jECtNNOejD = false;
      bool ePPBXQJpHK = false;
      bool FTMxWgRxkT = false;
      bool CXrepKhUkD = false;
      bool QctOOiCXVF = false;
      bool hPMmcPqEWg = false;
      bool uQtPBGXjKN = false;
      bool ioEEsbZyhn = false;
      bool esafllLEBa = false;
      bool ScxEHzidMH = false;
      bool KSNHVsLHsB = false;
      bool psWhCCpOdP = false;
      bool uShjtGqzxs = false;
      bool sukadLfSJr = false;
      bool ZDLAjZGPCF = false;
      bool JTzxLqjcNP = false;
      bool CMKzIuHuEp = false;
      string sexFrLOJVE;
      string yGquGpApdu;
      string QZrJMfLnHT;
      string dJMCkRQisB;
      string cduoGkUhMs;
      string eJeKPTlmsM;
      string AaCCZntnJn;
      string ZRxbRmdDCa;
      string KcaNnUdBlR;
      string ecofBCbsPS;
      string pfXXSNLDsc;
      string pikRBWznOF;
      string JrCrJxcQaO;
      string KjmjkeFDta;
      string IaIIburXdd;
      string DmdKIydfNV;
      string jubdRFuAgW;
      string RusnwiisQN;
      string EFlxLXGcam;
      string BYoYpNzeqV;
      if(sexFrLOJVE == pfXXSNLDsc){zqqGMHspNZ = true;}
      else if(pfXXSNLDsc == sexFrLOJVE){ioEEsbZyhn = true;}
      if(yGquGpApdu == pikRBWznOF){OjPzQeIeRs = true;}
      else if(pikRBWznOF == yGquGpApdu){esafllLEBa = true;}
      if(QZrJMfLnHT == JrCrJxcQaO){ySZsVrFUxh = true;}
      else if(JrCrJxcQaO == QZrJMfLnHT){ScxEHzidMH = true;}
      if(dJMCkRQisB == KjmjkeFDta){jECtNNOejD = true;}
      else if(KjmjkeFDta == dJMCkRQisB){KSNHVsLHsB = true;}
      if(cduoGkUhMs == IaIIburXdd){ePPBXQJpHK = true;}
      else if(IaIIburXdd == cduoGkUhMs){psWhCCpOdP = true;}
      if(eJeKPTlmsM == DmdKIydfNV){FTMxWgRxkT = true;}
      else if(DmdKIydfNV == eJeKPTlmsM){uShjtGqzxs = true;}
      if(AaCCZntnJn == jubdRFuAgW){CXrepKhUkD = true;}
      else if(jubdRFuAgW == AaCCZntnJn){sukadLfSJr = true;}
      if(ZRxbRmdDCa == RusnwiisQN){QctOOiCXVF = true;}
      if(KcaNnUdBlR == EFlxLXGcam){hPMmcPqEWg = true;}
      if(ecofBCbsPS == BYoYpNzeqV){uQtPBGXjKN = true;}
      while(RusnwiisQN == ZRxbRmdDCa){ZDLAjZGPCF = true;}
      while(EFlxLXGcam == EFlxLXGcam){JTzxLqjcNP = true;}
      while(BYoYpNzeqV == BYoYpNzeqV){CMKzIuHuEp = true;}
      if(zqqGMHspNZ == true){zqqGMHspNZ = false;}
      if(OjPzQeIeRs == true){OjPzQeIeRs = false;}
      if(ySZsVrFUxh == true){ySZsVrFUxh = false;}
      if(jECtNNOejD == true){jECtNNOejD = false;}
      if(ePPBXQJpHK == true){ePPBXQJpHK = false;}
      if(FTMxWgRxkT == true){FTMxWgRxkT = false;}
      if(CXrepKhUkD == true){CXrepKhUkD = false;}
      if(QctOOiCXVF == true){QctOOiCXVF = false;}
      if(hPMmcPqEWg == true){hPMmcPqEWg = false;}
      if(uQtPBGXjKN == true){uQtPBGXjKN = false;}
      if(ioEEsbZyhn == true){ioEEsbZyhn = false;}
      if(esafllLEBa == true){esafllLEBa = false;}
      if(ScxEHzidMH == true){ScxEHzidMH = false;}
      if(KSNHVsLHsB == true){KSNHVsLHsB = false;}
      if(psWhCCpOdP == true){psWhCCpOdP = false;}
      if(uShjtGqzxs == true){uShjtGqzxs = false;}
      if(sukadLfSJr == true){sukadLfSJr = false;}
      if(ZDLAjZGPCF == true){ZDLAjZGPCF = false;}
      if(JTzxLqjcNP == true){JTzxLqjcNP = false;}
      if(CMKzIuHuEp == true){CMKzIuHuEp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DQBSVMENYL
{ 
  void WQBeciPWPA()
  { 
      bool clAXWUZJlN = false;
      bool WxItLSMKjf = false;
      bool EJRgRmCSsi = false;
      bool NpeGwBBmwg = false;
      bool nIDxyjeXPM = false;
      bool kAawsTTTFj = false;
      bool SHPDAgSCxK = false;
      bool QYOCquFUih = false;
      bool HeDfxMOhNc = false;
      bool ghgLOgrAwQ = false;
      bool QcaEwLlYFx = false;
      bool NzjXbnDjFm = false;
      bool RknTdirCnJ = false;
      bool CFXRReDzjl = false;
      bool apbQOhxIiZ = false;
      bool dItJzfoGaN = false;
      bool SijwtIaRGx = false;
      bool jEATMbIXFu = false;
      bool kiSNftLOSl = false;
      bool pxXVSqFfVG = false;
      string zJnToObhEt;
      string eLouJSNDmq;
      string URXJJiwPfF;
      string TbmIbWWJNt;
      string GsHtGtOGIA;
      string dtoNGhleKF;
      string SMCzZCXfTm;
      string wEoskaJcCO;
      string UoGfaZlZCs;
      string kryHatqHTD;
      string VhmVEZEwce;
      string YIbukcFVYA;
      string PydZCDFhRq;
      string jBJyslBkbA;
      string UpwWUbPDWy;
      string oUiSmXENTA;
      string UWdltWzcCz;
      string aTtYfZBGEZ;
      string nCKSCOSpKU;
      string gnRaexLKbx;
      if(zJnToObhEt == VhmVEZEwce){clAXWUZJlN = true;}
      else if(VhmVEZEwce == zJnToObhEt){QcaEwLlYFx = true;}
      if(eLouJSNDmq == YIbukcFVYA){WxItLSMKjf = true;}
      else if(YIbukcFVYA == eLouJSNDmq){NzjXbnDjFm = true;}
      if(URXJJiwPfF == PydZCDFhRq){EJRgRmCSsi = true;}
      else if(PydZCDFhRq == URXJJiwPfF){RknTdirCnJ = true;}
      if(TbmIbWWJNt == jBJyslBkbA){NpeGwBBmwg = true;}
      else if(jBJyslBkbA == TbmIbWWJNt){CFXRReDzjl = true;}
      if(GsHtGtOGIA == UpwWUbPDWy){nIDxyjeXPM = true;}
      else if(UpwWUbPDWy == GsHtGtOGIA){apbQOhxIiZ = true;}
      if(dtoNGhleKF == oUiSmXENTA){kAawsTTTFj = true;}
      else if(oUiSmXENTA == dtoNGhleKF){dItJzfoGaN = true;}
      if(SMCzZCXfTm == UWdltWzcCz){SHPDAgSCxK = true;}
      else if(UWdltWzcCz == SMCzZCXfTm){SijwtIaRGx = true;}
      if(wEoskaJcCO == aTtYfZBGEZ){QYOCquFUih = true;}
      if(UoGfaZlZCs == nCKSCOSpKU){HeDfxMOhNc = true;}
      if(kryHatqHTD == gnRaexLKbx){ghgLOgrAwQ = true;}
      while(aTtYfZBGEZ == wEoskaJcCO){jEATMbIXFu = true;}
      while(nCKSCOSpKU == nCKSCOSpKU){kiSNftLOSl = true;}
      while(gnRaexLKbx == gnRaexLKbx){pxXVSqFfVG = true;}
      if(clAXWUZJlN == true){clAXWUZJlN = false;}
      if(WxItLSMKjf == true){WxItLSMKjf = false;}
      if(EJRgRmCSsi == true){EJRgRmCSsi = false;}
      if(NpeGwBBmwg == true){NpeGwBBmwg = false;}
      if(nIDxyjeXPM == true){nIDxyjeXPM = false;}
      if(kAawsTTTFj == true){kAawsTTTFj = false;}
      if(SHPDAgSCxK == true){SHPDAgSCxK = false;}
      if(QYOCquFUih == true){QYOCquFUih = false;}
      if(HeDfxMOhNc == true){HeDfxMOhNc = false;}
      if(ghgLOgrAwQ == true){ghgLOgrAwQ = false;}
      if(QcaEwLlYFx == true){QcaEwLlYFx = false;}
      if(NzjXbnDjFm == true){NzjXbnDjFm = false;}
      if(RknTdirCnJ == true){RknTdirCnJ = false;}
      if(CFXRReDzjl == true){CFXRReDzjl = false;}
      if(apbQOhxIiZ == true){apbQOhxIiZ = false;}
      if(dItJzfoGaN == true){dItJzfoGaN = false;}
      if(SijwtIaRGx == true){SijwtIaRGx = false;}
      if(jEATMbIXFu == true){jEATMbIXFu = false;}
      if(kiSNftLOSl == true){kiSNftLOSl = false;}
      if(pxXVSqFfVG == true){pxXVSqFfVG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MGFZRKJJXE
{ 
  void LyJxGyknUO()
  { 
      bool jdLuNgNxKS = false;
      bool GSUpPMtwde = false;
      bool xppYedeseA = false;
      bool soRIsGlxyr = false;
      bool fEUDmgLVYl = false;
      bool SDVdLsnmQi = false;
      bool CTSJYRBMwJ = false;
      bool axykysVllx = false;
      bool SIUrhoTmwz = false;
      bool SzfOoMkLdV = false;
      bool fzZOLVFjfS = false;
      bool XBATQtyZbj = false;
      bool xNPwqbRiwl = false;
      bool HKIPRShGgM = false;
      bool jiHdbQyLyu = false;
      bool NLitXRjdWj = false;
      bool DVnsKNrkCy = false;
      bool LrrPzOGkTZ = false;
      bool cFkAYwaOrA = false;
      bool iEixINuOTO = false;
      string VhJLVURowL;
      string nAVUZmAoEu;
      string RyLRVAIKAI;
      string kjBSIFcfUP;
      string CHEPToEaYk;
      string IbhuWWWrpU;
      string MHnnZEzDMT;
      string KTTnsJtuxf;
      string uhkPzJCFul;
      string ijpADuTQpO;
      string oBNFaoHsCN;
      string cbtJYeWXnQ;
      string CsHakZdTky;
      string ocFiptTfoK;
      string BIDgIGofaY;
      string XwbZMwsmTA;
      string LnIDXzWLTe;
      string KphdOsoaRd;
      string jysLZsBfVt;
      string AgLozNAzIJ;
      if(VhJLVURowL == oBNFaoHsCN){jdLuNgNxKS = true;}
      else if(oBNFaoHsCN == VhJLVURowL){fzZOLVFjfS = true;}
      if(nAVUZmAoEu == cbtJYeWXnQ){GSUpPMtwde = true;}
      else if(cbtJYeWXnQ == nAVUZmAoEu){XBATQtyZbj = true;}
      if(RyLRVAIKAI == CsHakZdTky){xppYedeseA = true;}
      else if(CsHakZdTky == RyLRVAIKAI){xNPwqbRiwl = true;}
      if(kjBSIFcfUP == ocFiptTfoK){soRIsGlxyr = true;}
      else if(ocFiptTfoK == kjBSIFcfUP){HKIPRShGgM = true;}
      if(CHEPToEaYk == BIDgIGofaY){fEUDmgLVYl = true;}
      else if(BIDgIGofaY == CHEPToEaYk){jiHdbQyLyu = true;}
      if(IbhuWWWrpU == XwbZMwsmTA){SDVdLsnmQi = true;}
      else if(XwbZMwsmTA == IbhuWWWrpU){NLitXRjdWj = true;}
      if(MHnnZEzDMT == LnIDXzWLTe){CTSJYRBMwJ = true;}
      else if(LnIDXzWLTe == MHnnZEzDMT){DVnsKNrkCy = true;}
      if(KTTnsJtuxf == KphdOsoaRd){axykysVllx = true;}
      if(uhkPzJCFul == jysLZsBfVt){SIUrhoTmwz = true;}
      if(ijpADuTQpO == AgLozNAzIJ){SzfOoMkLdV = true;}
      while(KphdOsoaRd == KTTnsJtuxf){LrrPzOGkTZ = true;}
      while(jysLZsBfVt == jysLZsBfVt){cFkAYwaOrA = true;}
      while(AgLozNAzIJ == AgLozNAzIJ){iEixINuOTO = true;}
      if(jdLuNgNxKS == true){jdLuNgNxKS = false;}
      if(GSUpPMtwde == true){GSUpPMtwde = false;}
      if(xppYedeseA == true){xppYedeseA = false;}
      if(soRIsGlxyr == true){soRIsGlxyr = false;}
      if(fEUDmgLVYl == true){fEUDmgLVYl = false;}
      if(SDVdLsnmQi == true){SDVdLsnmQi = false;}
      if(CTSJYRBMwJ == true){CTSJYRBMwJ = false;}
      if(axykysVllx == true){axykysVllx = false;}
      if(SIUrhoTmwz == true){SIUrhoTmwz = false;}
      if(SzfOoMkLdV == true){SzfOoMkLdV = false;}
      if(fzZOLVFjfS == true){fzZOLVFjfS = false;}
      if(XBATQtyZbj == true){XBATQtyZbj = false;}
      if(xNPwqbRiwl == true){xNPwqbRiwl = false;}
      if(HKIPRShGgM == true){HKIPRShGgM = false;}
      if(jiHdbQyLyu == true){jiHdbQyLyu = false;}
      if(NLitXRjdWj == true){NLitXRjdWj = false;}
      if(DVnsKNrkCy == true){DVnsKNrkCy = false;}
      if(LrrPzOGkTZ == true){LrrPzOGkTZ = false;}
      if(cFkAYwaOrA == true){cFkAYwaOrA = false;}
      if(iEixINuOTO == true){iEixINuOTO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FQBOOLAEBC
{ 
  void MLCIsnbqmg()
  { 
      bool SmknijocWQ = false;
      bool JiCdteLGJV = false;
      bool CmHtQOlmyM = false;
      bool gZIKkgVZCm = false;
      bool CuYiUTAezC = false;
      bool PsbFmefqXT = false;
      bool xCdJjjarsM = false;
      bool JkDWSHOXYw = false;
      bool OGmuxmxCXF = false;
      bool BdChpAQOzk = false;
      bool rHllsdpFle = false;
      bool PHSaFpOiMw = false;
      bool lXUmLeiUgR = false;
      bool pAYnDGUACS = false;
      bool xrQrosLacz = false;
      bool khCCyUmzaN = false;
      bool uUYToPidXz = false;
      bool VNgszsHbxR = false;
      bool THrgfIyVoi = false;
      bool SUZnWcTwCZ = false;
      string dxNOBbiQID;
      string PwNJlqLYmJ;
      string WeznmwdQjf;
      string OSMWWoaKDY;
      string ltmpTkhFku;
      string GQtIFzyZaF;
      string ySfbnxjplx;
      string PBUOWcrIUC;
      string OYeoZyXERW;
      string qAiyaTNKBW;
      string BqSneEwfkc;
      string HoFYpYmqBp;
      string YeYPFPRVmD;
      string OgGxAWGqJU;
      string BrToPBuKHB;
      string fWILxVSChP;
      string mZrgNZiHYT;
      string SwgfngLizD;
      string UHNlXrXuAd;
      string DDJthbzlao;
      if(dxNOBbiQID == BqSneEwfkc){SmknijocWQ = true;}
      else if(BqSneEwfkc == dxNOBbiQID){rHllsdpFle = true;}
      if(PwNJlqLYmJ == HoFYpYmqBp){JiCdteLGJV = true;}
      else if(HoFYpYmqBp == PwNJlqLYmJ){PHSaFpOiMw = true;}
      if(WeznmwdQjf == YeYPFPRVmD){CmHtQOlmyM = true;}
      else if(YeYPFPRVmD == WeznmwdQjf){lXUmLeiUgR = true;}
      if(OSMWWoaKDY == OgGxAWGqJU){gZIKkgVZCm = true;}
      else if(OgGxAWGqJU == OSMWWoaKDY){pAYnDGUACS = true;}
      if(ltmpTkhFku == BrToPBuKHB){CuYiUTAezC = true;}
      else if(BrToPBuKHB == ltmpTkhFku){xrQrosLacz = true;}
      if(GQtIFzyZaF == fWILxVSChP){PsbFmefqXT = true;}
      else if(fWILxVSChP == GQtIFzyZaF){khCCyUmzaN = true;}
      if(ySfbnxjplx == mZrgNZiHYT){xCdJjjarsM = true;}
      else if(mZrgNZiHYT == ySfbnxjplx){uUYToPidXz = true;}
      if(PBUOWcrIUC == SwgfngLizD){JkDWSHOXYw = true;}
      if(OYeoZyXERW == UHNlXrXuAd){OGmuxmxCXF = true;}
      if(qAiyaTNKBW == DDJthbzlao){BdChpAQOzk = true;}
      while(SwgfngLizD == PBUOWcrIUC){VNgszsHbxR = true;}
      while(UHNlXrXuAd == UHNlXrXuAd){THrgfIyVoi = true;}
      while(DDJthbzlao == DDJthbzlao){SUZnWcTwCZ = true;}
      if(SmknijocWQ == true){SmknijocWQ = false;}
      if(JiCdteLGJV == true){JiCdteLGJV = false;}
      if(CmHtQOlmyM == true){CmHtQOlmyM = false;}
      if(gZIKkgVZCm == true){gZIKkgVZCm = false;}
      if(CuYiUTAezC == true){CuYiUTAezC = false;}
      if(PsbFmefqXT == true){PsbFmefqXT = false;}
      if(xCdJjjarsM == true){xCdJjjarsM = false;}
      if(JkDWSHOXYw == true){JkDWSHOXYw = false;}
      if(OGmuxmxCXF == true){OGmuxmxCXF = false;}
      if(BdChpAQOzk == true){BdChpAQOzk = false;}
      if(rHllsdpFle == true){rHllsdpFle = false;}
      if(PHSaFpOiMw == true){PHSaFpOiMw = false;}
      if(lXUmLeiUgR == true){lXUmLeiUgR = false;}
      if(pAYnDGUACS == true){pAYnDGUACS = false;}
      if(xrQrosLacz == true){xrQrosLacz = false;}
      if(khCCyUmzaN == true){khCCyUmzaN = false;}
      if(uUYToPidXz == true){uUYToPidXz = false;}
      if(VNgszsHbxR == true){VNgszsHbxR = false;}
      if(THrgfIyVoi == true){THrgfIyVoi = false;}
      if(SUZnWcTwCZ == true){SUZnWcTwCZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DLRITCDAOG
{ 
  void CNYGAnlSiz()
  { 
      bool MMcByGRkZc = false;
      bool SoPgiCdPij = false;
      bool EECNatGmgt = false;
      bool irtxmcEeNo = false;
      bool TfykbywRLA = false;
      bool WUpPMIKOZD = false;
      bool zdEesZtRsF = false;
      bool yzCtQXGQlc = false;
      bool yoafWOCdke = false;
      bool SoEJoobSqB = false;
      bool DeXGCXSuzn = false;
      bool CsbxFKCYIe = false;
      bool XQgNmIurEa = false;
      bool wmZkYSQUcz = false;
      bool uGewcZNGDe = false;
      bool mDKLcmyJSt = false;
      bool baqXrOSpXm = false;
      bool sguIiRkjkM = false;
      bool tnnYnrbNHl = false;
      bool UGBhWUOHDN = false;
      string SYbkfmZhmE;
      string RzPpPmrRzs;
      string DdcLJTNiUe;
      string cajWmKSAQc;
      string nPzFVWtmeK;
      string rIRrtnuPaM;
      string YpMIbqOsDF;
      string UqBVFndXom;
      string YaEKlTIrby;
      string OCYDDxCqde;
      string HBiYpAHumG;
      string JXanmykCVH;
      string hWQEqRRxSH;
      string kmtKeXqfTl;
      string LNEVnpbkQF;
      string LAUVwkjegY;
      string iKceVWcPIO;
      string GFijuTRuPA;
      string ogfMukRYNt;
      string nLyuDBkZAR;
      if(SYbkfmZhmE == HBiYpAHumG){MMcByGRkZc = true;}
      else if(HBiYpAHumG == SYbkfmZhmE){DeXGCXSuzn = true;}
      if(RzPpPmrRzs == JXanmykCVH){SoPgiCdPij = true;}
      else if(JXanmykCVH == RzPpPmrRzs){CsbxFKCYIe = true;}
      if(DdcLJTNiUe == hWQEqRRxSH){EECNatGmgt = true;}
      else if(hWQEqRRxSH == DdcLJTNiUe){XQgNmIurEa = true;}
      if(cajWmKSAQc == kmtKeXqfTl){irtxmcEeNo = true;}
      else if(kmtKeXqfTl == cajWmKSAQc){wmZkYSQUcz = true;}
      if(nPzFVWtmeK == LNEVnpbkQF){TfykbywRLA = true;}
      else if(LNEVnpbkQF == nPzFVWtmeK){uGewcZNGDe = true;}
      if(rIRrtnuPaM == LAUVwkjegY){WUpPMIKOZD = true;}
      else if(LAUVwkjegY == rIRrtnuPaM){mDKLcmyJSt = true;}
      if(YpMIbqOsDF == iKceVWcPIO){zdEesZtRsF = true;}
      else if(iKceVWcPIO == YpMIbqOsDF){baqXrOSpXm = true;}
      if(UqBVFndXom == GFijuTRuPA){yzCtQXGQlc = true;}
      if(YaEKlTIrby == ogfMukRYNt){yoafWOCdke = true;}
      if(OCYDDxCqde == nLyuDBkZAR){SoEJoobSqB = true;}
      while(GFijuTRuPA == UqBVFndXom){sguIiRkjkM = true;}
      while(ogfMukRYNt == ogfMukRYNt){tnnYnrbNHl = true;}
      while(nLyuDBkZAR == nLyuDBkZAR){UGBhWUOHDN = true;}
      if(MMcByGRkZc == true){MMcByGRkZc = false;}
      if(SoPgiCdPij == true){SoPgiCdPij = false;}
      if(EECNatGmgt == true){EECNatGmgt = false;}
      if(irtxmcEeNo == true){irtxmcEeNo = false;}
      if(TfykbywRLA == true){TfykbywRLA = false;}
      if(WUpPMIKOZD == true){WUpPMIKOZD = false;}
      if(zdEesZtRsF == true){zdEesZtRsF = false;}
      if(yzCtQXGQlc == true){yzCtQXGQlc = false;}
      if(yoafWOCdke == true){yoafWOCdke = false;}
      if(SoEJoobSqB == true){SoEJoobSqB = false;}
      if(DeXGCXSuzn == true){DeXGCXSuzn = false;}
      if(CsbxFKCYIe == true){CsbxFKCYIe = false;}
      if(XQgNmIurEa == true){XQgNmIurEa = false;}
      if(wmZkYSQUcz == true){wmZkYSQUcz = false;}
      if(uGewcZNGDe == true){uGewcZNGDe = false;}
      if(mDKLcmyJSt == true){mDKLcmyJSt = false;}
      if(baqXrOSpXm == true){baqXrOSpXm = false;}
      if(sguIiRkjkM == true){sguIiRkjkM = false;}
      if(tnnYnrbNHl == true){tnnYnrbNHl = false;}
      if(UGBhWUOHDN == true){UGBhWUOHDN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class COTWCCHHOC
{ 
  void sXIpbodwKK()
  { 
      bool WkGNbzSdQY = false;
      bool CfzlAOfOus = false;
      bool IMHZPZJtEk = false;
      bool xSffUmYTpY = false;
      bool DtwZpVVXrP = false;
      bool OiOPZJdfxC = false;
      bool pYYfajASRM = false;
      bool pMYVoNQhjt = false;
      bool EkBnVODQGK = false;
      bool JrVnidUPyG = false;
      bool VCFfZCJsZL = false;
      bool suwDyEXkKM = false;
      bool fiMHCxpkmL = false;
      bool rAjdXBfUOS = false;
      bool EKptROwRod = false;
      bool GjFkalpydc = false;
      bool MYFOSrKSfw = false;
      bool YCVqIUsRom = false;
      bool AXuJEIuzCk = false;
      bool LgqlFeFbbZ = false;
      string stSBbWEwhe;
      string oXaPiipNnF;
      string LRMiyZWrhx;
      string CMXuHOBTZz;
      string mYIPWmPylY;
      string WPKfeagjCB;
      string AMNkbbzeIU;
      string hVmnSmJxLL;
      string JXFIalCrQf;
      string gQQYzZKXmt;
      string mkpRqAcWMr;
      string RjXqqbGEKp;
      string ZHObnRFOor;
      string bkKRXYhmRZ;
      string JeeYOwrZgW;
      string SFNxTeVNdY;
      string uNgUPfZGSS;
      string tTmjfucoNq;
      string YfhSYWXMyr;
      string CUJreuxKJh;
      if(stSBbWEwhe == mkpRqAcWMr){WkGNbzSdQY = true;}
      else if(mkpRqAcWMr == stSBbWEwhe){VCFfZCJsZL = true;}
      if(oXaPiipNnF == RjXqqbGEKp){CfzlAOfOus = true;}
      else if(RjXqqbGEKp == oXaPiipNnF){suwDyEXkKM = true;}
      if(LRMiyZWrhx == ZHObnRFOor){IMHZPZJtEk = true;}
      else if(ZHObnRFOor == LRMiyZWrhx){fiMHCxpkmL = true;}
      if(CMXuHOBTZz == bkKRXYhmRZ){xSffUmYTpY = true;}
      else if(bkKRXYhmRZ == CMXuHOBTZz){rAjdXBfUOS = true;}
      if(mYIPWmPylY == JeeYOwrZgW){DtwZpVVXrP = true;}
      else if(JeeYOwrZgW == mYIPWmPylY){EKptROwRod = true;}
      if(WPKfeagjCB == SFNxTeVNdY){OiOPZJdfxC = true;}
      else if(SFNxTeVNdY == WPKfeagjCB){GjFkalpydc = true;}
      if(AMNkbbzeIU == uNgUPfZGSS){pYYfajASRM = true;}
      else if(uNgUPfZGSS == AMNkbbzeIU){MYFOSrKSfw = true;}
      if(hVmnSmJxLL == tTmjfucoNq){pMYVoNQhjt = true;}
      if(JXFIalCrQf == YfhSYWXMyr){EkBnVODQGK = true;}
      if(gQQYzZKXmt == CUJreuxKJh){JrVnidUPyG = true;}
      while(tTmjfucoNq == hVmnSmJxLL){YCVqIUsRom = true;}
      while(YfhSYWXMyr == YfhSYWXMyr){AXuJEIuzCk = true;}
      while(CUJreuxKJh == CUJreuxKJh){LgqlFeFbbZ = true;}
      if(WkGNbzSdQY == true){WkGNbzSdQY = false;}
      if(CfzlAOfOus == true){CfzlAOfOus = false;}
      if(IMHZPZJtEk == true){IMHZPZJtEk = false;}
      if(xSffUmYTpY == true){xSffUmYTpY = false;}
      if(DtwZpVVXrP == true){DtwZpVVXrP = false;}
      if(OiOPZJdfxC == true){OiOPZJdfxC = false;}
      if(pYYfajASRM == true){pYYfajASRM = false;}
      if(pMYVoNQhjt == true){pMYVoNQhjt = false;}
      if(EkBnVODQGK == true){EkBnVODQGK = false;}
      if(JrVnidUPyG == true){JrVnidUPyG = false;}
      if(VCFfZCJsZL == true){VCFfZCJsZL = false;}
      if(suwDyEXkKM == true){suwDyEXkKM = false;}
      if(fiMHCxpkmL == true){fiMHCxpkmL = false;}
      if(rAjdXBfUOS == true){rAjdXBfUOS = false;}
      if(EKptROwRod == true){EKptROwRod = false;}
      if(GjFkalpydc == true){GjFkalpydc = false;}
      if(MYFOSrKSfw == true){MYFOSrKSfw = false;}
      if(YCVqIUsRom == true){YCVqIUsRom = false;}
      if(AXuJEIuzCk == true){AXuJEIuzCk = false;}
      if(LgqlFeFbbZ == true){LgqlFeFbbZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCFPQQEQPR
{ 
  void YedASWdFZP()
  { 
      bool YnuXHQZepP = false;
      bool IdOILSIOwk = false;
      bool rDnKKJMMVm = false;
      bool oZQFKBDoaP = false;
      bool jztqOVVPcy = false;
      bool UXWoGVzjMy = false;
      bool DMJDZiMIxK = false;
      bool PSngBrJxun = false;
      bool mxiXRQDbyo = false;
      bool BSbbLWppQf = false;
      bool INRShCjpnO = false;
      bool MCoXKFdklJ = false;
      bool ekJIIxqLUd = false;
      bool BSfPfYfQoP = false;
      bool gNmjczdDRF = false;
      bool sEEHAWEJJk = false;
      bool KXUKMsVYrk = false;
      bool ZMwWcRyZeJ = false;
      bool SmtOjxOYPI = false;
      bool UWHEEIrcWi = false;
      string eCpaEICBkL;
      string VAVMdbWLjF;
      string oZJqCQKqql;
      string jnFzumaJCy;
      string RfnwmlILha;
      string HWUysFsyXn;
      string xLJzaguVQq;
      string BNIlnJkMEQ;
      string IzIQdMTGGp;
      string sckNAFVnUF;
      string pltqZtOhKi;
      string TfsHfyDsVO;
      string NoPaxXbtkh;
      string mxqyZVERqi;
      string ykuWVNichC;
      string CcRGrBVTsB;
      string RUxbwWnuhK;
      string tkCmPcsrFj;
      string oyMhfKekGX;
      string zkXoQcmSaz;
      if(eCpaEICBkL == pltqZtOhKi){YnuXHQZepP = true;}
      else if(pltqZtOhKi == eCpaEICBkL){INRShCjpnO = true;}
      if(VAVMdbWLjF == TfsHfyDsVO){IdOILSIOwk = true;}
      else if(TfsHfyDsVO == VAVMdbWLjF){MCoXKFdklJ = true;}
      if(oZJqCQKqql == NoPaxXbtkh){rDnKKJMMVm = true;}
      else if(NoPaxXbtkh == oZJqCQKqql){ekJIIxqLUd = true;}
      if(jnFzumaJCy == mxqyZVERqi){oZQFKBDoaP = true;}
      else if(mxqyZVERqi == jnFzumaJCy){BSfPfYfQoP = true;}
      if(RfnwmlILha == ykuWVNichC){jztqOVVPcy = true;}
      else if(ykuWVNichC == RfnwmlILha){gNmjczdDRF = true;}
      if(HWUysFsyXn == CcRGrBVTsB){UXWoGVzjMy = true;}
      else if(CcRGrBVTsB == HWUysFsyXn){sEEHAWEJJk = true;}
      if(xLJzaguVQq == RUxbwWnuhK){DMJDZiMIxK = true;}
      else if(RUxbwWnuhK == xLJzaguVQq){KXUKMsVYrk = true;}
      if(BNIlnJkMEQ == tkCmPcsrFj){PSngBrJxun = true;}
      if(IzIQdMTGGp == oyMhfKekGX){mxiXRQDbyo = true;}
      if(sckNAFVnUF == zkXoQcmSaz){BSbbLWppQf = true;}
      while(tkCmPcsrFj == BNIlnJkMEQ){ZMwWcRyZeJ = true;}
      while(oyMhfKekGX == oyMhfKekGX){SmtOjxOYPI = true;}
      while(zkXoQcmSaz == zkXoQcmSaz){UWHEEIrcWi = true;}
      if(YnuXHQZepP == true){YnuXHQZepP = false;}
      if(IdOILSIOwk == true){IdOILSIOwk = false;}
      if(rDnKKJMMVm == true){rDnKKJMMVm = false;}
      if(oZQFKBDoaP == true){oZQFKBDoaP = false;}
      if(jztqOVVPcy == true){jztqOVVPcy = false;}
      if(UXWoGVzjMy == true){UXWoGVzjMy = false;}
      if(DMJDZiMIxK == true){DMJDZiMIxK = false;}
      if(PSngBrJxun == true){PSngBrJxun = false;}
      if(mxiXRQDbyo == true){mxiXRQDbyo = false;}
      if(BSbbLWppQf == true){BSbbLWppQf = false;}
      if(INRShCjpnO == true){INRShCjpnO = false;}
      if(MCoXKFdklJ == true){MCoXKFdklJ = false;}
      if(ekJIIxqLUd == true){ekJIIxqLUd = false;}
      if(BSfPfYfQoP == true){BSfPfYfQoP = false;}
      if(gNmjczdDRF == true){gNmjczdDRF = false;}
      if(sEEHAWEJJk == true){sEEHAWEJJk = false;}
      if(KXUKMsVYrk == true){KXUKMsVYrk = false;}
      if(ZMwWcRyZeJ == true){ZMwWcRyZeJ = false;}
      if(SmtOjxOYPI == true){SmtOjxOYPI = false;}
      if(UWHEEIrcWi == true){UWHEEIrcWi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KAUJRKUSSF
{ 
  void CyfbzOUXQn()
  { 
      bool DWoxmPoyIR = false;
      bool qwlHWDJiNH = false;
      bool ZbLMgMikhL = false;
      bool dWVLmzzPIb = false;
      bool bEcRFlGfsS = false;
      bool UUVAiaLcQa = false;
      bool fEQwmUZaTW = false;
      bool DtZleUzsGt = false;
      bool GDqPqJAUcL = false;
      bool nVzgwXnfdj = false;
      bool LeLWOatjUN = false;
      bool bRVVUbMAFd = false;
      bool UFyHigtspH = false;
      bool gSOWharUAP = false;
      bool OPAPjWzcMT = false;
      bool LnazPGgDng = false;
      bool fBtMgICzns = false;
      bool jqzoPEEiXL = false;
      bool hRfVwrrOHa = false;
      bool tngSjNVmhb = false;
      string UgFuSdQRex;
      string YBmNDJkJHU;
      string YIJcDCJQMR;
      string FHgMijXtAT;
      string uJhifOKsYT;
      string WGGIxLWbrP;
      string UAFMqQUZeT;
      string kpJmYOaaxn;
      string rPqrtyBYPW;
      string MwCjyuEUqO;
      string tjOFhfwSii;
      string jwdDXFIMRr;
      string PuKHGonZnd;
      string JGiitIAlKN;
      string BhogmPRyMs;
      string lrCyzyZHys;
      string rWdFYdMuIP;
      string FWCDpgGdUq;
      string WoMuqRDkjw;
      string hsmQVeDjHI;
      if(UgFuSdQRex == tjOFhfwSii){DWoxmPoyIR = true;}
      else if(tjOFhfwSii == UgFuSdQRex){LeLWOatjUN = true;}
      if(YBmNDJkJHU == jwdDXFIMRr){qwlHWDJiNH = true;}
      else if(jwdDXFIMRr == YBmNDJkJHU){bRVVUbMAFd = true;}
      if(YIJcDCJQMR == PuKHGonZnd){ZbLMgMikhL = true;}
      else if(PuKHGonZnd == YIJcDCJQMR){UFyHigtspH = true;}
      if(FHgMijXtAT == JGiitIAlKN){dWVLmzzPIb = true;}
      else if(JGiitIAlKN == FHgMijXtAT){gSOWharUAP = true;}
      if(uJhifOKsYT == BhogmPRyMs){bEcRFlGfsS = true;}
      else if(BhogmPRyMs == uJhifOKsYT){OPAPjWzcMT = true;}
      if(WGGIxLWbrP == lrCyzyZHys){UUVAiaLcQa = true;}
      else if(lrCyzyZHys == WGGIxLWbrP){LnazPGgDng = true;}
      if(UAFMqQUZeT == rWdFYdMuIP){fEQwmUZaTW = true;}
      else if(rWdFYdMuIP == UAFMqQUZeT){fBtMgICzns = true;}
      if(kpJmYOaaxn == FWCDpgGdUq){DtZleUzsGt = true;}
      if(rPqrtyBYPW == WoMuqRDkjw){GDqPqJAUcL = true;}
      if(MwCjyuEUqO == hsmQVeDjHI){nVzgwXnfdj = true;}
      while(FWCDpgGdUq == kpJmYOaaxn){jqzoPEEiXL = true;}
      while(WoMuqRDkjw == WoMuqRDkjw){hRfVwrrOHa = true;}
      while(hsmQVeDjHI == hsmQVeDjHI){tngSjNVmhb = true;}
      if(DWoxmPoyIR == true){DWoxmPoyIR = false;}
      if(qwlHWDJiNH == true){qwlHWDJiNH = false;}
      if(ZbLMgMikhL == true){ZbLMgMikhL = false;}
      if(dWVLmzzPIb == true){dWVLmzzPIb = false;}
      if(bEcRFlGfsS == true){bEcRFlGfsS = false;}
      if(UUVAiaLcQa == true){UUVAiaLcQa = false;}
      if(fEQwmUZaTW == true){fEQwmUZaTW = false;}
      if(DtZleUzsGt == true){DtZleUzsGt = false;}
      if(GDqPqJAUcL == true){GDqPqJAUcL = false;}
      if(nVzgwXnfdj == true){nVzgwXnfdj = false;}
      if(LeLWOatjUN == true){LeLWOatjUN = false;}
      if(bRVVUbMAFd == true){bRVVUbMAFd = false;}
      if(UFyHigtspH == true){UFyHigtspH = false;}
      if(gSOWharUAP == true){gSOWharUAP = false;}
      if(OPAPjWzcMT == true){OPAPjWzcMT = false;}
      if(LnazPGgDng == true){LnazPGgDng = false;}
      if(fBtMgICzns == true){fBtMgICzns = false;}
      if(jqzoPEEiXL == true){jqzoPEEiXL = false;}
      if(hRfVwrrOHa == true){hRfVwrrOHa = false;}
      if(tngSjNVmhb == true){tngSjNVmhb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZYHIPZVHXZ
{ 
  void gyHMtXsAOU()
  { 
      bool uMqgcbQpkg = false;
      bool PSqiBacDQu = false;
      bool AfxNRmAwOP = false;
      bool AGswOcEuMk = false;
      bool mEKoSouMyM = false;
      bool QxyGzPPcPp = false;
      bool aTaUgIYuUX = false;
      bool VhpeIwUHub = false;
      bool qmyCzCImxz = false;
      bool NafWKScpIJ = false;
      bool QArZpiHSyC = false;
      bool tHhmymVYUd = false;
      bool AlyUKtBSUp = false;
      bool SezkLquXLQ = false;
      bool uontEGsrYW = false;
      bool wDUdJdCWPu = false;
      bool gnyIjOHxbH = false;
      bool ryMEhKxDPD = false;
      bool BJtxsOKVbg = false;
      bool oXHPiHqfKp = false;
      string WXBkxHWrta;
      string qxUjfucZAP;
      string LnHqyQDRzL;
      string XNWCNHQpkF;
      string QtqJHbfzAs;
      string sfgNihQJmg;
      string DFshDcZRVX;
      string dlotyRxxjW;
      string jDRFSrgJTe;
      string pGDECLAIGe;
      string CNdbOGqlPQ;
      string jSZPwzmmOK;
      string uPyphWijrl;
      string QoqFUWZpqL;
      string AtsCuXgmHC;
      string YMtuilOmsq;
      string XGsdzubTuZ;
      string ZxwDKBWwuK;
      string pwcpMDuuWh;
      string ImwzntAPCz;
      if(WXBkxHWrta == CNdbOGqlPQ){uMqgcbQpkg = true;}
      else if(CNdbOGqlPQ == WXBkxHWrta){QArZpiHSyC = true;}
      if(qxUjfucZAP == jSZPwzmmOK){PSqiBacDQu = true;}
      else if(jSZPwzmmOK == qxUjfucZAP){tHhmymVYUd = true;}
      if(LnHqyQDRzL == uPyphWijrl){AfxNRmAwOP = true;}
      else if(uPyphWijrl == LnHqyQDRzL){AlyUKtBSUp = true;}
      if(XNWCNHQpkF == QoqFUWZpqL){AGswOcEuMk = true;}
      else if(QoqFUWZpqL == XNWCNHQpkF){SezkLquXLQ = true;}
      if(QtqJHbfzAs == AtsCuXgmHC){mEKoSouMyM = true;}
      else if(AtsCuXgmHC == QtqJHbfzAs){uontEGsrYW = true;}
      if(sfgNihQJmg == YMtuilOmsq){QxyGzPPcPp = true;}
      else if(YMtuilOmsq == sfgNihQJmg){wDUdJdCWPu = true;}
      if(DFshDcZRVX == XGsdzubTuZ){aTaUgIYuUX = true;}
      else if(XGsdzubTuZ == DFshDcZRVX){gnyIjOHxbH = true;}
      if(dlotyRxxjW == ZxwDKBWwuK){VhpeIwUHub = true;}
      if(jDRFSrgJTe == pwcpMDuuWh){qmyCzCImxz = true;}
      if(pGDECLAIGe == ImwzntAPCz){NafWKScpIJ = true;}
      while(ZxwDKBWwuK == dlotyRxxjW){ryMEhKxDPD = true;}
      while(pwcpMDuuWh == pwcpMDuuWh){BJtxsOKVbg = true;}
      while(ImwzntAPCz == ImwzntAPCz){oXHPiHqfKp = true;}
      if(uMqgcbQpkg == true){uMqgcbQpkg = false;}
      if(PSqiBacDQu == true){PSqiBacDQu = false;}
      if(AfxNRmAwOP == true){AfxNRmAwOP = false;}
      if(AGswOcEuMk == true){AGswOcEuMk = false;}
      if(mEKoSouMyM == true){mEKoSouMyM = false;}
      if(QxyGzPPcPp == true){QxyGzPPcPp = false;}
      if(aTaUgIYuUX == true){aTaUgIYuUX = false;}
      if(VhpeIwUHub == true){VhpeIwUHub = false;}
      if(qmyCzCImxz == true){qmyCzCImxz = false;}
      if(NafWKScpIJ == true){NafWKScpIJ = false;}
      if(QArZpiHSyC == true){QArZpiHSyC = false;}
      if(tHhmymVYUd == true){tHhmymVYUd = false;}
      if(AlyUKtBSUp == true){AlyUKtBSUp = false;}
      if(SezkLquXLQ == true){SezkLquXLQ = false;}
      if(uontEGsrYW == true){uontEGsrYW = false;}
      if(wDUdJdCWPu == true){wDUdJdCWPu = false;}
      if(gnyIjOHxbH == true){gnyIjOHxbH = false;}
      if(ryMEhKxDPD == true){ryMEhKxDPD = false;}
      if(BJtxsOKVbg == true){BJtxsOKVbg = false;}
      if(oXHPiHqfKp == true){oXHPiHqfKp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KJIOSCTHCZ
{ 
  void qnVGjKbnMs()
  { 
      bool UHEuQoHtQy = false;
      bool xHKSPrnDRf = false;
      bool XeKhXyUpnA = false;
      bool bexxLXcxjx = false;
      bool ZPFEDkpquy = false;
      bool wuDcDowVXS = false;
      bool URFQWRKMGr = false;
      bool OqTTFIYGem = false;
      bool IctpDfbTsV = false;
      bool aHYQcIJngk = false;
      bool ZckDiFajWu = false;
      bool QoqjJrWOMp = false;
      bool opSjQHRCpx = false;
      bool yjZsMerpHy = false;
      bool FrxxFkPoHk = false;
      bool ktbqwjJAla = false;
      bool nXsYxfPxXd = false;
      bool zfHNkxrVef = false;
      bool qcuFMDIixb = false;
      bool UqEfKgzXAZ = false;
      string EHPBJSPOEn;
      string TcpHEuKmDf;
      string ahzrArfMHw;
      string eNRkxFiUzl;
      string MVcRKgucAH;
      string kZmfJWIXAR;
      string lCGHJFKFKy;
      string MomRSEEhgT;
      string wCMALFZlba;
      string wLThzKOUHE;
      string VpSBuulVME;
      string RapgVipGuE;
      string eYciCAUFRI;
      string piZcxFjKFQ;
      string SEYWJVVmLQ;
      string UIZDZxNjzt;
      string ZgEENhBNiP;
      string zeAelazFYf;
      string ehsAmhJWCA;
      string rAKKpkzUIb;
      if(EHPBJSPOEn == VpSBuulVME){UHEuQoHtQy = true;}
      else if(VpSBuulVME == EHPBJSPOEn){ZckDiFajWu = true;}
      if(TcpHEuKmDf == RapgVipGuE){xHKSPrnDRf = true;}
      else if(RapgVipGuE == TcpHEuKmDf){QoqjJrWOMp = true;}
      if(ahzrArfMHw == eYciCAUFRI){XeKhXyUpnA = true;}
      else if(eYciCAUFRI == ahzrArfMHw){opSjQHRCpx = true;}
      if(eNRkxFiUzl == piZcxFjKFQ){bexxLXcxjx = true;}
      else if(piZcxFjKFQ == eNRkxFiUzl){yjZsMerpHy = true;}
      if(MVcRKgucAH == SEYWJVVmLQ){ZPFEDkpquy = true;}
      else if(SEYWJVVmLQ == MVcRKgucAH){FrxxFkPoHk = true;}
      if(kZmfJWIXAR == UIZDZxNjzt){wuDcDowVXS = true;}
      else if(UIZDZxNjzt == kZmfJWIXAR){ktbqwjJAla = true;}
      if(lCGHJFKFKy == ZgEENhBNiP){URFQWRKMGr = true;}
      else if(ZgEENhBNiP == lCGHJFKFKy){nXsYxfPxXd = true;}
      if(MomRSEEhgT == zeAelazFYf){OqTTFIYGem = true;}
      if(wCMALFZlba == ehsAmhJWCA){IctpDfbTsV = true;}
      if(wLThzKOUHE == rAKKpkzUIb){aHYQcIJngk = true;}
      while(zeAelazFYf == MomRSEEhgT){zfHNkxrVef = true;}
      while(ehsAmhJWCA == ehsAmhJWCA){qcuFMDIixb = true;}
      while(rAKKpkzUIb == rAKKpkzUIb){UqEfKgzXAZ = true;}
      if(UHEuQoHtQy == true){UHEuQoHtQy = false;}
      if(xHKSPrnDRf == true){xHKSPrnDRf = false;}
      if(XeKhXyUpnA == true){XeKhXyUpnA = false;}
      if(bexxLXcxjx == true){bexxLXcxjx = false;}
      if(ZPFEDkpquy == true){ZPFEDkpquy = false;}
      if(wuDcDowVXS == true){wuDcDowVXS = false;}
      if(URFQWRKMGr == true){URFQWRKMGr = false;}
      if(OqTTFIYGem == true){OqTTFIYGem = false;}
      if(IctpDfbTsV == true){IctpDfbTsV = false;}
      if(aHYQcIJngk == true){aHYQcIJngk = false;}
      if(ZckDiFajWu == true){ZckDiFajWu = false;}
      if(QoqjJrWOMp == true){QoqjJrWOMp = false;}
      if(opSjQHRCpx == true){opSjQHRCpx = false;}
      if(yjZsMerpHy == true){yjZsMerpHy = false;}
      if(FrxxFkPoHk == true){FrxxFkPoHk = false;}
      if(ktbqwjJAla == true){ktbqwjJAla = false;}
      if(nXsYxfPxXd == true){nXsYxfPxXd = false;}
      if(zfHNkxrVef == true){zfHNkxrVef = false;}
      if(qcuFMDIixb == true){qcuFMDIixb = false;}
      if(UqEfKgzXAZ == true){UqEfKgzXAZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HXNYTDNZPH
{ 
  void zVheFgSmyc()
  { 
      bool KSJmfeWlbP = false;
      bool fXngKLBXyP = false;
      bool zBpSwPBykp = false;
      bool RwXyNyaGcq = false;
      bool iQgfkzdLQU = false;
      bool LADARIbqpQ = false;
      bool cXBkyizoSL = false;
      bool ktuGghUKgx = false;
      bool kpgQeQrXgF = false;
      bool WiQLOLPuhB = false;
      bool znrFjQFwTi = false;
      bool nRKselpjFg = false;
      bool qbINoBdirU = false;
      bool SYbfxwxbgO = false;
      bool LwDxQEYXfb = false;
      bool UepAKXfePh = false;
      bool mVDyQOodui = false;
      bool oNDqVtYKwj = false;
      bool cGCQAmibUZ = false;
      bool QSLyaorFgC = false;
      string VZJdWYGBff;
      string OZzKSFAxVU;
      string pDrPEuLOTh;
      string NGQOwCnxlf;
      string IKxKKIYBQP;
      string dItcDRgtZa;
      string NqhySHJkOP;
      string QCLoMeGgEu;
      string WJyDDFLmKe;
      string UtXKRRbyrC;
      string zmmAzawEQY;
      string KzodDEretM;
      string wVaitWdAXu;
      string CHoCujVyEc;
      string IGWlTVFsGN;
      string YxEfGdMDFb;
      string wugUVCKliT;
      string htaRDpynPY;
      string RktJVFDIwQ;
      string WSrbfMYCQQ;
      if(VZJdWYGBff == zmmAzawEQY){KSJmfeWlbP = true;}
      else if(zmmAzawEQY == VZJdWYGBff){znrFjQFwTi = true;}
      if(OZzKSFAxVU == KzodDEretM){fXngKLBXyP = true;}
      else if(KzodDEretM == OZzKSFAxVU){nRKselpjFg = true;}
      if(pDrPEuLOTh == wVaitWdAXu){zBpSwPBykp = true;}
      else if(wVaitWdAXu == pDrPEuLOTh){qbINoBdirU = true;}
      if(NGQOwCnxlf == CHoCujVyEc){RwXyNyaGcq = true;}
      else if(CHoCujVyEc == NGQOwCnxlf){SYbfxwxbgO = true;}
      if(IKxKKIYBQP == IGWlTVFsGN){iQgfkzdLQU = true;}
      else if(IGWlTVFsGN == IKxKKIYBQP){LwDxQEYXfb = true;}
      if(dItcDRgtZa == YxEfGdMDFb){LADARIbqpQ = true;}
      else if(YxEfGdMDFb == dItcDRgtZa){UepAKXfePh = true;}
      if(NqhySHJkOP == wugUVCKliT){cXBkyizoSL = true;}
      else if(wugUVCKliT == NqhySHJkOP){mVDyQOodui = true;}
      if(QCLoMeGgEu == htaRDpynPY){ktuGghUKgx = true;}
      if(WJyDDFLmKe == RktJVFDIwQ){kpgQeQrXgF = true;}
      if(UtXKRRbyrC == WSrbfMYCQQ){WiQLOLPuhB = true;}
      while(htaRDpynPY == QCLoMeGgEu){oNDqVtYKwj = true;}
      while(RktJVFDIwQ == RktJVFDIwQ){cGCQAmibUZ = true;}
      while(WSrbfMYCQQ == WSrbfMYCQQ){QSLyaorFgC = true;}
      if(KSJmfeWlbP == true){KSJmfeWlbP = false;}
      if(fXngKLBXyP == true){fXngKLBXyP = false;}
      if(zBpSwPBykp == true){zBpSwPBykp = false;}
      if(RwXyNyaGcq == true){RwXyNyaGcq = false;}
      if(iQgfkzdLQU == true){iQgfkzdLQU = false;}
      if(LADARIbqpQ == true){LADARIbqpQ = false;}
      if(cXBkyizoSL == true){cXBkyizoSL = false;}
      if(ktuGghUKgx == true){ktuGghUKgx = false;}
      if(kpgQeQrXgF == true){kpgQeQrXgF = false;}
      if(WiQLOLPuhB == true){WiQLOLPuhB = false;}
      if(znrFjQFwTi == true){znrFjQFwTi = false;}
      if(nRKselpjFg == true){nRKselpjFg = false;}
      if(qbINoBdirU == true){qbINoBdirU = false;}
      if(SYbfxwxbgO == true){SYbfxwxbgO = false;}
      if(LwDxQEYXfb == true){LwDxQEYXfb = false;}
      if(UepAKXfePh == true){UepAKXfePh = false;}
      if(mVDyQOodui == true){mVDyQOodui = false;}
      if(oNDqVtYKwj == true){oNDqVtYKwj = false;}
      if(cGCQAmibUZ == true){cGCQAmibUZ = false;}
      if(QSLyaorFgC == true){QSLyaorFgC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LAURBCWEHU
{ 
  void schrLuwIQJ()
  { 
      bool bokpQENtOZ = false;
      bool pqyYdLeTsE = false;
      bool KNlkDdByWi = false;
      bool bAEzaUknkq = false;
      bool CNtziisicX = false;
      bool iBhyDOCzlm = false;
      bool COXfxolzxI = false;
      bool ZqhCBxSlCT = false;
      bool jSVyzZSFuM = false;
      bool SlBynnpNCs = false;
      bool wtlTyqTewG = false;
      bool uPxSCirYfW = false;
      bool VfDjonojNN = false;
      bool GFjIWpgBAH = false;
      bool GmJoQDoiuF = false;
      bool uQheXPqBeK = false;
      bool CjRizpenuM = false;
      bool CqXXQhWNSl = false;
      bool yGnISoWEkG = false;
      bool yeWpFWVZpa = false;
      string JmfVyMBFWI;
      string GikbluPAAk;
      string JyoNSpaqMg;
      string HOcdVqaAey;
      string SJPjEQlNaT;
      string ObMPCLyRDH;
      string lKrpBrFGFu;
      string UOUBRziEJB;
      string EMPsReCNaK;
      string rJxWMIRYiM;
      string KeHezzHKxD;
      string csIBDZtzXV;
      string orfuCKRxoI;
      string hJVwqZEjtR;
      string XqPXhzAuTl;
      string NRBMWSzMbn;
      string hJVnUSWLKd;
      string VJEGxxbHND;
      string KWdCuPIJYY;
      string aqHGiOVaDO;
      if(JmfVyMBFWI == KeHezzHKxD){bokpQENtOZ = true;}
      else if(KeHezzHKxD == JmfVyMBFWI){wtlTyqTewG = true;}
      if(GikbluPAAk == csIBDZtzXV){pqyYdLeTsE = true;}
      else if(csIBDZtzXV == GikbluPAAk){uPxSCirYfW = true;}
      if(JyoNSpaqMg == orfuCKRxoI){KNlkDdByWi = true;}
      else if(orfuCKRxoI == JyoNSpaqMg){VfDjonojNN = true;}
      if(HOcdVqaAey == hJVwqZEjtR){bAEzaUknkq = true;}
      else if(hJVwqZEjtR == HOcdVqaAey){GFjIWpgBAH = true;}
      if(SJPjEQlNaT == XqPXhzAuTl){CNtziisicX = true;}
      else if(XqPXhzAuTl == SJPjEQlNaT){GmJoQDoiuF = true;}
      if(ObMPCLyRDH == NRBMWSzMbn){iBhyDOCzlm = true;}
      else if(NRBMWSzMbn == ObMPCLyRDH){uQheXPqBeK = true;}
      if(lKrpBrFGFu == hJVnUSWLKd){COXfxolzxI = true;}
      else if(hJVnUSWLKd == lKrpBrFGFu){CjRizpenuM = true;}
      if(UOUBRziEJB == VJEGxxbHND){ZqhCBxSlCT = true;}
      if(EMPsReCNaK == KWdCuPIJYY){jSVyzZSFuM = true;}
      if(rJxWMIRYiM == aqHGiOVaDO){SlBynnpNCs = true;}
      while(VJEGxxbHND == UOUBRziEJB){CqXXQhWNSl = true;}
      while(KWdCuPIJYY == KWdCuPIJYY){yGnISoWEkG = true;}
      while(aqHGiOVaDO == aqHGiOVaDO){yeWpFWVZpa = true;}
      if(bokpQENtOZ == true){bokpQENtOZ = false;}
      if(pqyYdLeTsE == true){pqyYdLeTsE = false;}
      if(KNlkDdByWi == true){KNlkDdByWi = false;}
      if(bAEzaUknkq == true){bAEzaUknkq = false;}
      if(CNtziisicX == true){CNtziisicX = false;}
      if(iBhyDOCzlm == true){iBhyDOCzlm = false;}
      if(COXfxolzxI == true){COXfxolzxI = false;}
      if(ZqhCBxSlCT == true){ZqhCBxSlCT = false;}
      if(jSVyzZSFuM == true){jSVyzZSFuM = false;}
      if(SlBynnpNCs == true){SlBynnpNCs = false;}
      if(wtlTyqTewG == true){wtlTyqTewG = false;}
      if(uPxSCirYfW == true){uPxSCirYfW = false;}
      if(VfDjonojNN == true){VfDjonojNN = false;}
      if(GFjIWpgBAH == true){GFjIWpgBAH = false;}
      if(GmJoQDoiuF == true){GmJoQDoiuF = false;}
      if(uQheXPqBeK == true){uQheXPqBeK = false;}
      if(CjRizpenuM == true){CjRizpenuM = false;}
      if(CqXXQhWNSl == true){CqXXQhWNSl = false;}
      if(yGnISoWEkG == true){yGnISoWEkG = false;}
      if(yeWpFWVZpa == true){yeWpFWVZpa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JEJJAYQNVA
{ 
  void TtRVMPpjgS()
  { 
      bool bQxyEfqGzL = false;
      bool MXsMBssloZ = false;
      bool XUjYgMFwXt = false;
      bool eEQTfYxxIV = false;
      bool CVHYlVgjwO = false;
      bool LoKafGgYQq = false;
      bool auhFgHGYgb = false;
      bool uudSXBNKlL = false;
      bool fVAJhpspnY = false;
      bool rYgQtGnCrd = false;
      bool OHCTSQLrCe = false;
      bool sVlFLFuYWp = false;
      bool OQkIjWONXQ = false;
      bool NLSIwYSfqR = false;
      bool eBmJeVmaFo = false;
      bool LPeBPyVtiw = false;
      bool CyTlQhDdIl = false;
      bool mOgFLNdacN = false;
      bool jmHiEyfQsy = false;
      bool CXwtPggArx = false;
      string aNBMWwwPDQ;
      string cyZRLhmMSK;
      string McjVAzecVY;
      string TOjRTOrRHo;
      string VNunPZlrdK;
      string YPhQxyceLX;
      string RSsdxOOHyx;
      string pUEcnygwFZ;
      string NlzKAEfTUV;
      string kMFiXDTQqB;
      string LdtgUDKEby;
      string QgZkKeTicr;
      string humbLcOVFk;
      string eQFEOirRow;
      string saqVEDmTYr;
      string ikmySQpRUr;
      string nozqTAbVWa;
      string mCsgyGERXH;
      string puwMCscGky;
      string sZwxIEbzBD;
      if(aNBMWwwPDQ == LdtgUDKEby){bQxyEfqGzL = true;}
      else if(LdtgUDKEby == aNBMWwwPDQ){OHCTSQLrCe = true;}
      if(cyZRLhmMSK == QgZkKeTicr){MXsMBssloZ = true;}
      else if(QgZkKeTicr == cyZRLhmMSK){sVlFLFuYWp = true;}
      if(McjVAzecVY == humbLcOVFk){XUjYgMFwXt = true;}
      else if(humbLcOVFk == McjVAzecVY){OQkIjWONXQ = true;}
      if(TOjRTOrRHo == eQFEOirRow){eEQTfYxxIV = true;}
      else if(eQFEOirRow == TOjRTOrRHo){NLSIwYSfqR = true;}
      if(VNunPZlrdK == saqVEDmTYr){CVHYlVgjwO = true;}
      else if(saqVEDmTYr == VNunPZlrdK){eBmJeVmaFo = true;}
      if(YPhQxyceLX == ikmySQpRUr){LoKafGgYQq = true;}
      else if(ikmySQpRUr == YPhQxyceLX){LPeBPyVtiw = true;}
      if(RSsdxOOHyx == nozqTAbVWa){auhFgHGYgb = true;}
      else if(nozqTAbVWa == RSsdxOOHyx){CyTlQhDdIl = true;}
      if(pUEcnygwFZ == mCsgyGERXH){uudSXBNKlL = true;}
      if(NlzKAEfTUV == puwMCscGky){fVAJhpspnY = true;}
      if(kMFiXDTQqB == sZwxIEbzBD){rYgQtGnCrd = true;}
      while(mCsgyGERXH == pUEcnygwFZ){mOgFLNdacN = true;}
      while(puwMCscGky == puwMCscGky){jmHiEyfQsy = true;}
      while(sZwxIEbzBD == sZwxIEbzBD){CXwtPggArx = true;}
      if(bQxyEfqGzL == true){bQxyEfqGzL = false;}
      if(MXsMBssloZ == true){MXsMBssloZ = false;}
      if(XUjYgMFwXt == true){XUjYgMFwXt = false;}
      if(eEQTfYxxIV == true){eEQTfYxxIV = false;}
      if(CVHYlVgjwO == true){CVHYlVgjwO = false;}
      if(LoKafGgYQq == true){LoKafGgYQq = false;}
      if(auhFgHGYgb == true){auhFgHGYgb = false;}
      if(uudSXBNKlL == true){uudSXBNKlL = false;}
      if(fVAJhpspnY == true){fVAJhpspnY = false;}
      if(rYgQtGnCrd == true){rYgQtGnCrd = false;}
      if(OHCTSQLrCe == true){OHCTSQLrCe = false;}
      if(sVlFLFuYWp == true){sVlFLFuYWp = false;}
      if(OQkIjWONXQ == true){OQkIjWONXQ = false;}
      if(NLSIwYSfqR == true){NLSIwYSfqR = false;}
      if(eBmJeVmaFo == true){eBmJeVmaFo = false;}
      if(LPeBPyVtiw == true){LPeBPyVtiw = false;}
      if(CyTlQhDdIl == true){CyTlQhDdIl = false;}
      if(mOgFLNdacN == true){mOgFLNdacN = false;}
      if(jmHiEyfQsy == true){jmHiEyfQsy = false;}
      if(CXwtPggArx == true){CXwtPggArx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KSSDWKXXWG
{ 
  void XbZIIEBGKe()
  { 
      bool pZUdfUtcqN = false;
      bool FnqQXrlZKI = false;
      bool TgUgxZUcIN = false;
      bool cXeUMgEtbT = false;
      bool fDXXtQZXJc = false;
      bool snXwPIFmgF = false;
      bool zQUckhIWDp = false;
      bool nqypcPJwlf = false;
      bool AxTeTnziFE = false;
      bool bQMVTOitmM = false;
      bool HDTSoBphTz = false;
      bool yIBAFCxoIw = false;
      bool hZQzOXebVN = false;
      bool gPJYYwcApS = false;
      bool yQPFFTOLQR = false;
      bool RskpdhmUER = false;
      bool WNLFSiycbJ = false;
      bool YwzpyQJKtu = false;
      bool ISLEumdStp = false;
      bool JIwXukFJmV = false;
      string jmMDmAiUnX;
      string jXpmOgSWty;
      string lhadzmwyRr;
      string ijiTZsNyIi;
      string heVIsnQxfl;
      string McYiTBMiDz;
      string EkCwoznVMV;
      string TUNKPGMRkL;
      string VySeeFKAzY;
      string fetJewbYTs;
      string ztjJSrPOSM;
      string ntyrcGSWRi;
      string nnWnonZEfS;
      string enyqLbNIMm;
      string pwhmjlgBfY;
      string dEHjFLXwTe;
      string RKhzhAuGgB;
      string rJKdsqGjED;
      string HYYHoZgOlA;
      string ERngVeOiEi;
      if(jmMDmAiUnX == ztjJSrPOSM){pZUdfUtcqN = true;}
      else if(ztjJSrPOSM == jmMDmAiUnX){HDTSoBphTz = true;}
      if(jXpmOgSWty == ntyrcGSWRi){FnqQXrlZKI = true;}
      else if(ntyrcGSWRi == jXpmOgSWty){yIBAFCxoIw = true;}
      if(lhadzmwyRr == nnWnonZEfS){TgUgxZUcIN = true;}
      else if(nnWnonZEfS == lhadzmwyRr){hZQzOXebVN = true;}
      if(ijiTZsNyIi == enyqLbNIMm){cXeUMgEtbT = true;}
      else if(enyqLbNIMm == ijiTZsNyIi){gPJYYwcApS = true;}
      if(heVIsnQxfl == pwhmjlgBfY){fDXXtQZXJc = true;}
      else if(pwhmjlgBfY == heVIsnQxfl){yQPFFTOLQR = true;}
      if(McYiTBMiDz == dEHjFLXwTe){snXwPIFmgF = true;}
      else if(dEHjFLXwTe == McYiTBMiDz){RskpdhmUER = true;}
      if(EkCwoznVMV == RKhzhAuGgB){zQUckhIWDp = true;}
      else if(RKhzhAuGgB == EkCwoznVMV){WNLFSiycbJ = true;}
      if(TUNKPGMRkL == rJKdsqGjED){nqypcPJwlf = true;}
      if(VySeeFKAzY == HYYHoZgOlA){AxTeTnziFE = true;}
      if(fetJewbYTs == ERngVeOiEi){bQMVTOitmM = true;}
      while(rJKdsqGjED == TUNKPGMRkL){YwzpyQJKtu = true;}
      while(HYYHoZgOlA == HYYHoZgOlA){ISLEumdStp = true;}
      while(ERngVeOiEi == ERngVeOiEi){JIwXukFJmV = true;}
      if(pZUdfUtcqN == true){pZUdfUtcqN = false;}
      if(FnqQXrlZKI == true){FnqQXrlZKI = false;}
      if(TgUgxZUcIN == true){TgUgxZUcIN = false;}
      if(cXeUMgEtbT == true){cXeUMgEtbT = false;}
      if(fDXXtQZXJc == true){fDXXtQZXJc = false;}
      if(snXwPIFmgF == true){snXwPIFmgF = false;}
      if(zQUckhIWDp == true){zQUckhIWDp = false;}
      if(nqypcPJwlf == true){nqypcPJwlf = false;}
      if(AxTeTnziFE == true){AxTeTnziFE = false;}
      if(bQMVTOitmM == true){bQMVTOitmM = false;}
      if(HDTSoBphTz == true){HDTSoBphTz = false;}
      if(yIBAFCxoIw == true){yIBAFCxoIw = false;}
      if(hZQzOXebVN == true){hZQzOXebVN = false;}
      if(gPJYYwcApS == true){gPJYYwcApS = false;}
      if(yQPFFTOLQR == true){yQPFFTOLQR = false;}
      if(RskpdhmUER == true){RskpdhmUER = false;}
      if(WNLFSiycbJ == true){WNLFSiycbJ = false;}
      if(YwzpyQJKtu == true){YwzpyQJKtu = false;}
      if(ISLEumdStp == true){ISLEumdStp = false;}
      if(JIwXukFJmV == true){JIwXukFJmV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RPKGNSWJJC
{ 
  void HoCcXuudfO()
  { 
      bool WYTJSSoCaU = false;
      bool QnQnBMIJDA = false;
      bool erIWJuaHbk = false;
      bool gsuUwJEnUD = false;
      bool kuSLGjfepC = false;
      bool OcqlMePwAW = false;
      bool qhaonWsuqr = false;
      bool HUozPjYxQZ = false;
      bool PuQYVDCIHR = false;
      bool sInxLCTdXi = false;
      bool qknyttnqWc = false;
      bool FRfZHwRCSj = false;
      bool UkmYyzfqnN = false;
      bool PuZhieHRdb = false;
      bool OKleLacNpP = false;
      bool jQKmOFxPzu = false;
      bool NxDIMKryqb = false;
      bool ozXqUKyIMW = false;
      bool WSBYcyklSc = false;
      bool gqRiNRHcRB = false;
      string mSDwdnlqoL;
      string ljeUBLQgRg;
      string fkxikjeDHV;
      string rEAcswrtRn;
      string PzGrYxUopz;
      string uNYYWBVUKs;
      string IhiSShjCbE;
      string TWPdQfeEKn;
      string OoMHZdebFr;
      string aXiXehQmZp;
      string MSNlfYyuHq;
      string VRJVeTUaro;
      string CIwidwmqyi;
      string PreTbuaabB;
      string eiTOVJNNsL;
      string MotjnEWdHj;
      string lHwYacloti;
      string rtzqJTnhNT;
      string hYymVaytfW;
      string YwSrPXltmr;
      if(mSDwdnlqoL == MSNlfYyuHq){WYTJSSoCaU = true;}
      else if(MSNlfYyuHq == mSDwdnlqoL){qknyttnqWc = true;}
      if(ljeUBLQgRg == VRJVeTUaro){QnQnBMIJDA = true;}
      else if(VRJVeTUaro == ljeUBLQgRg){FRfZHwRCSj = true;}
      if(fkxikjeDHV == CIwidwmqyi){erIWJuaHbk = true;}
      else if(CIwidwmqyi == fkxikjeDHV){UkmYyzfqnN = true;}
      if(rEAcswrtRn == PreTbuaabB){gsuUwJEnUD = true;}
      else if(PreTbuaabB == rEAcswrtRn){PuZhieHRdb = true;}
      if(PzGrYxUopz == eiTOVJNNsL){kuSLGjfepC = true;}
      else if(eiTOVJNNsL == PzGrYxUopz){OKleLacNpP = true;}
      if(uNYYWBVUKs == MotjnEWdHj){OcqlMePwAW = true;}
      else if(MotjnEWdHj == uNYYWBVUKs){jQKmOFxPzu = true;}
      if(IhiSShjCbE == lHwYacloti){qhaonWsuqr = true;}
      else if(lHwYacloti == IhiSShjCbE){NxDIMKryqb = true;}
      if(TWPdQfeEKn == rtzqJTnhNT){HUozPjYxQZ = true;}
      if(OoMHZdebFr == hYymVaytfW){PuQYVDCIHR = true;}
      if(aXiXehQmZp == YwSrPXltmr){sInxLCTdXi = true;}
      while(rtzqJTnhNT == TWPdQfeEKn){ozXqUKyIMW = true;}
      while(hYymVaytfW == hYymVaytfW){WSBYcyklSc = true;}
      while(YwSrPXltmr == YwSrPXltmr){gqRiNRHcRB = true;}
      if(WYTJSSoCaU == true){WYTJSSoCaU = false;}
      if(QnQnBMIJDA == true){QnQnBMIJDA = false;}
      if(erIWJuaHbk == true){erIWJuaHbk = false;}
      if(gsuUwJEnUD == true){gsuUwJEnUD = false;}
      if(kuSLGjfepC == true){kuSLGjfepC = false;}
      if(OcqlMePwAW == true){OcqlMePwAW = false;}
      if(qhaonWsuqr == true){qhaonWsuqr = false;}
      if(HUozPjYxQZ == true){HUozPjYxQZ = false;}
      if(PuQYVDCIHR == true){PuQYVDCIHR = false;}
      if(sInxLCTdXi == true){sInxLCTdXi = false;}
      if(qknyttnqWc == true){qknyttnqWc = false;}
      if(FRfZHwRCSj == true){FRfZHwRCSj = false;}
      if(UkmYyzfqnN == true){UkmYyzfqnN = false;}
      if(PuZhieHRdb == true){PuZhieHRdb = false;}
      if(OKleLacNpP == true){OKleLacNpP = false;}
      if(jQKmOFxPzu == true){jQKmOFxPzu = false;}
      if(NxDIMKryqb == true){NxDIMKryqb = false;}
      if(ozXqUKyIMW == true){ozXqUKyIMW = false;}
      if(WSBYcyklSc == true){WSBYcyklSc = false;}
      if(gqRiNRHcRB == true){gqRiNRHcRB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMPDIXAUFU
{ 
  void mZanPtbOZn()
  { 
      bool ZMPXqcyEFn = false;
      bool uaubxzQtbe = false;
      bool TKsRxsfKBk = false;
      bool DpJBbaffpo = false;
      bool CXYgRwDSlW = false;
      bool EUeclPSyZy = false;
      bool xnCUjFRszW = false;
      bool SjElbulMAA = false;
      bool pMYefhKfPL = false;
      bool HhGqrOUEwL = false;
      bool eJTPDTQsAp = false;
      bool dGyYIjOXnB = false;
      bool tkdmOkdMsN = false;
      bool ZhPnVfsJbL = false;
      bool RReYhBigiI = false;
      bool AxPuRsefAR = false;
      bool pEzmQwpKCb = false;
      bool qEwbjbGFFM = false;
      bool BwckNcRUVc = false;
      bool BMIJVMSrHk = false;
      string DmmiihAuKI;
      string KhRkgjkJRH;
      string DgLDChfdHQ;
      string DQQwZVBNgb;
      string cyKNKHTVHj;
      string LuhwgWbjfB;
      string BWntEsRULL;
      string hXcpdFVysu;
      string OKVXEIiTPC;
      string sRgeZFKQIR;
      string oyKwBmRrSa;
      string BdpklqBQow;
      string KxFIRPqxPX;
      string uEpbFQAZVR;
      string pqBnBObush;
      string EsbLGrrBdl;
      string uUbtfwnOeV;
      string qatXGSwQGC;
      string nwEgSBcdUN;
      string XyujVUPGHF;
      if(DmmiihAuKI == oyKwBmRrSa){ZMPXqcyEFn = true;}
      else if(oyKwBmRrSa == DmmiihAuKI){eJTPDTQsAp = true;}
      if(KhRkgjkJRH == BdpklqBQow){uaubxzQtbe = true;}
      else if(BdpklqBQow == KhRkgjkJRH){dGyYIjOXnB = true;}
      if(DgLDChfdHQ == KxFIRPqxPX){TKsRxsfKBk = true;}
      else if(KxFIRPqxPX == DgLDChfdHQ){tkdmOkdMsN = true;}
      if(DQQwZVBNgb == uEpbFQAZVR){DpJBbaffpo = true;}
      else if(uEpbFQAZVR == DQQwZVBNgb){ZhPnVfsJbL = true;}
      if(cyKNKHTVHj == pqBnBObush){CXYgRwDSlW = true;}
      else if(pqBnBObush == cyKNKHTVHj){RReYhBigiI = true;}
      if(LuhwgWbjfB == EsbLGrrBdl){EUeclPSyZy = true;}
      else if(EsbLGrrBdl == LuhwgWbjfB){AxPuRsefAR = true;}
      if(BWntEsRULL == uUbtfwnOeV){xnCUjFRszW = true;}
      else if(uUbtfwnOeV == BWntEsRULL){pEzmQwpKCb = true;}
      if(hXcpdFVysu == qatXGSwQGC){SjElbulMAA = true;}
      if(OKVXEIiTPC == nwEgSBcdUN){pMYefhKfPL = true;}
      if(sRgeZFKQIR == XyujVUPGHF){HhGqrOUEwL = true;}
      while(qatXGSwQGC == hXcpdFVysu){qEwbjbGFFM = true;}
      while(nwEgSBcdUN == nwEgSBcdUN){BwckNcRUVc = true;}
      while(XyujVUPGHF == XyujVUPGHF){BMIJVMSrHk = true;}
      if(ZMPXqcyEFn == true){ZMPXqcyEFn = false;}
      if(uaubxzQtbe == true){uaubxzQtbe = false;}
      if(TKsRxsfKBk == true){TKsRxsfKBk = false;}
      if(DpJBbaffpo == true){DpJBbaffpo = false;}
      if(CXYgRwDSlW == true){CXYgRwDSlW = false;}
      if(EUeclPSyZy == true){EUeclPSyZy = false;}
      if(xnCUjFRszW == true){xnCUjFRszW = false;}
      if(SjElbulMAA == true){SjElbulMAA = false;}
      if(pMYefhKfPL == true){pMYefhKfPL = false;}
      if(HhGqrOUEwL == true){HhGqrOUEwL = false;}
      if(eJTPDTQsAp == true){eJTPDTQsAp = false;}
      if(dGyYIjOXnB == true){dGyYIjOXnB = false;}
      if(tkdmOkdMsN == true){tkdmOkdMsN = false;}
      if(ZhPnVfsJbL == true){ZhPnVfsJbL = false;}
      if(RReYhBigiI == true){RReYhBigiI = false;}
      if(AxPuRsefAR == true){AxPuRsefAR = false;}
      if(pEzmQwpKCb == true){pEzmQwpKCb = false;}
      if(qEwbjbGFFM == true){qEwbjbGFFM = false;}
      if(BwckNcRUVc == true){BwckNcRUVc = false;}
      if(BMIJVMSrHk == true){BMIJVMSrHk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YBCKCBCPTO
{ 
  void AzsSNSUFjf()
  { 
      bool CmbXcSPURk = false;
      bool BOmhMjBUuh = false;
      bool BYTccmdcuj = false;
      bool soWGspFPho = false;
      bool XrfwYAjxPh = false;
      bool knjlQcTzto = false;
      bool omZhqMrgnW = false;
      bool ellGKIsXDc = false;
      bool DfMMyFFjoQ = false;
      bool VFUrzjRxEM = false;
      bool HCIsCzBcaI = false;
      bool juwRlIZMik = false;
      bool GIqXAYRsGZ = false;
      bool pwSpUAXSKz = false;
      bool EcJggaJCGp = false;
      bool JFNTGzKjsc = false;
      bool hHVARncFxk = false;
      bool kHBigdyKqZ = false;
      bool POmQQkhzjV = false;
      bool omZgRwGIPs = false;
      string zIMxWAwJAK;
      string pPGQXFDlAG;
      string wQZrWyIRKo;
      string tcpDWRdHCW;
      string asqCrzpJGi;
      string ZbIThhhUZX;
      string qezLQMYCsF;
      string auidfDZXzX;
      string IyLaOSTVUn;
      string jJheeutelf;
      string ZmQAHereme;
      string IJUBOrTYxx;
      string rDgEVRNDyj;
      string ItlTyVhKSj;
      string aohpfZnfQm;
      string bVhnmWFLep;
      string RnfDVNWADr;
      string JJFNVCUqYw;
      string cgmLHmMyga;
      string PWecRlIeTS;
      if(zIMxWAwJAK == ZmQAHereme){CmbXcSPURk = true;}
      else if(ZmQAHereme == zIMxWAwJAK){HCIsCzBcaI = true;}
      if(pPGQXFDlAG == IJUBOrTYxx){BOmhMjBUuh = true;}
      else if(IJUBOrTYxx == pPGQXFDlAG){juwRlIZMik = true;}
      if(wQZrWyIRKo == rDgEVRNDyj){BYTccmdcuj = true;}
      else if(rDgEVRNDyj == wQZrWyIRKo){GIqXAYRsGZ = true;}
      if(tcpDWRdHCW == ItlTyVhKSj){soWGspFPho = true;}
      else if(ItlTyVhKSj == tcpDWRdHCW){pwSpUAXSKz = true;}
      if(asqCrzpJGi == aohpfZnfQm){XrfwYAjxPh = true;}
      else if(aohpfZnfQm == asqCrzpJGi){EcJggaJCGp = true;}
      if(ZbIThhhUZX == bVhnmWFLep){knjlQcTzto = true;}
      else if(bVhnmWFLep == ZbIThhhUZX){JFNTGzKjsc = true;}
      if(qezLQMYCsF == RnfDVNWADr){omZhqMrgnW = true;}
      else if(RnfDVNWADr == qezLQMYCsF){hHVARncFxk = true;}
      if(auidfDZXzX == JJFNVCUqYw){ellGKIsXDc = true;}
      if(IyLaOSTVUn == cgmLHmMyga){DfMMyFFjoQ = true;}
      if(jJheeutelf == PWecRlIeTS){VFUrzjRxEM = true;}
      while(JJFNVCUqYw == auidfDZXzX){kHBigdyKqZ = true;}
      while(cgmLHmMyga == cgmLHmMyga){POmQQkhzjV = true;}
      while(PWecRlIeTS == PWecRlIeTS){omZgRwGIPs = true;}
      if(CmbXcSPURk == true){CmbXcSPURk = false;}
      if(BOmhMjBUuh == true){BOmhMjBUuh = false;}
      if(BYTccmdcuj == true){BYTccmdcuj = false;}
      if(soWGspFPho == true){soWGspFPho = false;}
      if(XrfwYAjxPh == true){XrfwYAjxPh = false;}
      if(knjlQcTzto == true){knjlQcTzto = false;}
      if(omZhqMrgnW == true){omZhqMrgnW = false;}
      if(ellGKIsXDc == true){ellGKIsXDc = false;}
      if(DfMMyFFjoQ == true){DfMMyFFjoQ = false;}
      if(VFUrzjRxEM == true){VFUrzjRxEM = false;}
      if(HCIsCzBcaI == true){HCIsCzBcaI = false;}
      if(juwRlIZMik == true){juwRlIZMik = false;}
      if(GIqXAYRsGZ == true){GIqXAYRsGZ = false;}
      if(pwSpUAXSKz == true){pwSpUAXSKz = false;}
      if(EcJggaJCGp == true){EcJggaJCGp = false;}
      if(JFNTGzKjsc == true){JFNTGzKjsc = false;}
      if(hHVARncFxk == true){hHVARncFxk = false;}
      if(kHBigdyKqZ == true){kHBigdyKqZ = false;}
      if(POmQQkhzjV == true){POmQQkhzjV = false;}
      if(omZgRwGIPs == true){omZgRwGIPs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YARZQNNZVM
{ 
  void jHIdfGJCBt()
  { 
      bool sYKWTYtciu = false;
      bool NIJdeNMwok = false;
      bool jLujyQKmWB = false;
      bool fpUWWPwCAj = false;
      bool sGJwyVglsK = false;
      bool tZwgagdaXC = false;
      bool OGGhPXmmGP = false;
      bool RKwErcBzkc = false;
      bool iXsLGGtnuo = false;
      bool lUdxUlzbfa = false;
      bool htfdsjcqny = false;
      bool edouTpMuaI = false;
      bool czrQdwfyjF = false;
      bool dZSKtorPRW = false;
      bool cDzxJHfide = false;
      bool YEBXxiCOAx = false;
      bool DdHhTFLeAd = false;
      bool xxcDfZztGV = false;
      bool QwUEgZXuML = false;
      bool mcPUTywQcE = false;
      string uZxEKrcnyk;
      string GsLXuccfLi;
      string fyOwDHMYWg;
      string kVrbEwnHFy;
      string nccpVBIYHI;
      string EjYBUxLBBC;
      string eDRQAkAjTy;
      string nVaNtDUXZC;
      string znRNcBxpGG;
      string kmGCSkKMok;
      string AYEIUiJKHQ;
      string bmayDqkEnz;
      string nKcMNAOXuJ;
      string sIinCZiJrs;
      string qlipexLHza;
      string AFXpxourtT;
      string UkPyXTEmwc;
      string HaLuHBbmhQ;
      string oGYTImjrqM;
      string dqPYYGVkRL;
      if(uZxEKrcnyk == AYEIUiJKHQ){sYKWTYtciu = true;}
      else if(AYEIUiJKHQ == uZxEKrcnyk){htfdsjcqny = true;}
      if(GsLXuccfLi == bmayDqkEnz){NIJdeNMwok = true;}
      else if(bmayDqkEnz == GsLXuccfLi){edouTpMuaI = true;}
      if(fyOwDHMYWg == nKcMNAOXuJ){jLujyQKmWB = true;}
      else if(nKcMNAOXuJ == fyOwDHMYWg){czrQdwfyjF = true;}
      if(kVrbEwnHFy == sIinCZiJrs){fpUWWPwCAj = true;}
      else if(sIinCZiJrs == kVrbEwnHFy){dZSKtorPRW = true;}
      if(nccpVBIYHI == qlipexLHza){sGJwyVglsK = true;}
      else if(qlipexLHza == nccpVBIYHI){cDzxJHfide = true;}
      if(EjYBUxLBBC == AFXpxourtT){tZwgagdaXC = true;}
      else if(AFXpxourtT == EjYBUxLBBC){YEBXxiCOAx = true;}
      if(eDRQAkAjTy == UkPyXTEmwc){OGGhPXmmGP = true;}
      else if(UkPyXTEmwc == eDRQAkAjTy){DdHhTFLeAd = true;}
      if(nVaNtDUXZC == HaLuHBbmhQ){RKwErcBzkc = true;}
      if(znRNcBxpGG == oGYTImjrqM){iXsLGGtnuo = true;}
      if(kmGCSkKMok == dqPYYGVkRL){lUdxUlzbfa = true;}
      while(HaLuHBbmhQ == nVaNtDUXZC){xxcDfZztGV = true;}
      while(oGYTImjrqM == oGYTImjrqM){QwUEgZXuML = true;}
      while(dqPYYGVkRL == dqPYYGVkRL){mcPUTywQcE = true;}
      if(sYKWTYtciu == true){sYKWTYtciu = false;}
      if(NIJdeNMwok == true){NIJdeNMwok = false;}
      if(jLujyQKmWB == true){jLujyQKmWB = false;}
      if(fpUWWPwCAj == true){fpUWWPwCAj = false;}
      if(sGJwyVglsK == true){sGJwyVglsK = false;}
      if(tZwgagdaXC == true){tZwgagdaXC = false;}
      if(OGGhPXmmGP == true){OGGhPXmmGP = false;}
      if(RKwErcBzkc == true){RKwErcBzkc = false;}
      if(iXsLGGtnuo == true){iXsLGGtnuo = false;}
      if(lUdxUlzbfa == true){lUdxUlzbfa = false;}
      if(htfdsjcqny == true){htfdsjcqny = false;}
      if(edouTpMuaI == true){edouTpMuaI = false;}
      if(czrQdwfyjF == true){czrQdwfyjF = false;}
      if(dZSKtorPRW == true){dZSKtorPRW = false;}
      if(cDzxJHfide == true){cDzxJHfide = false;}
      if(YEBXxiCOAx == true){YEBXxiCOAx = false;}
      if(DdHhTFLeAd == true){DdHhTFLeAd = false;}
      if(xxcDfZztGV == true){xxcDfZztGV = false;}
      if(QwUEgZXuML == true){QwUEgZXuML = false;}
      if(mcPUTywQcE == true){mcPUTywQcE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AADFCYYMZN
{ 
  void PqAnBqRKTn()
  { 
      bool nzAPGfDCBk = false;
      bool QHMYmgIqXj = false;
      bool dCbpVcYfry = false;
      bool jbxiYdXOHF = false;
      bool QeELAYGZBJ = false;
      bool PmajIkWKtc = false;
      bool HWKCAnKcAI = false;
      bool ItiRSzxQow = false;
      bool WyehhxAMam = false;
      bool GMTdysTBKL = false;
      bool OcZrAUDJRI = false;
      bool nGVxGIrbUC = false;
      bool nxCMCuZETY = false;
      bool fwGdhsXmhN = false;
      bool tquRzAqWXo = false;
      bool BqgHXRaNoF = false;
      bool tyorcqzqPM = false;
      bool jEtHIxBjMB = false;
      bool DDgeXnOyFQ = false;
      bool SKxbSuBDoH = false;
      string THGudRQbkp;
      string yCRpGyViXN;
      string fIetyyMXgX;
      string ItLFoMESIF;
      string HqapBQbFpK;
      string oKnEkLbMwf;
      string FruMgEpLAs;
      string sCZRFngnrh;
      string WHhVixGHUd;
      string jrVcAOwOJx;
      string ZPFwRmkWzw;
      string emTOJyKYdj;
      string xipVJBgxQp;
      string rSeuHGClEw;
      string MiHYzwXHSC;
      string EXkYzqYilQ;
      string FmFIEMIYGC;
      string wYThXOaRWM;
      string cYdOkUhGwQ;
      string gSznpYdyTm;
      if(THGudRQbkp == ZPFwRmkWzw){nzAPGfDCBk = true;}
      else if(ZPFwRmkWzw == THGudRQbkp){OcZrAUDJRI = true;}
      if(yCRpGyViXN == emTOJyKYdj){QHMYmgIqXj = true;}
      else if(emTOJyKYdj == yCRpGyViXN){nGVxGIrbUC = true;}
      if(fIetyyMXgX == xipVJBgxQp){dCbpVcYfry = true;}
      else if(xipVJBgxQp == fIetyyMXgX){nxCMCuZETY = true;}
      if(ItLFoMESIF == rSeuHGClEw){jbxiYdXOHF = true;}
      else if(rSeuHGClEw == ItLFoMESIF){fwGdhsXmhN = true;}
      if(HqapBQbFpK == MiHYzwXHSC){QeELAYGZBJ = true;}
      else if(MiHYzwXHSC == HqapBQbFpK){tquRzAqWXo = true;}
      if(oKnEkLbMwf == EXkYzqYilQ){PmajIkWKtc = true;}
      else if(EXkYzqYilQ == oKnEkLbMwf){BqgHXRaNoF = true;}
      if(FruMgEpLAs == FmFIEMIYGC){HWKCAnKcAI = true;}
      else if(FmFIEMIYGC == FruMgEpLAs){tyorcqzqPM = true;}
      if(sCZRFngnrh == wYThXOaRWM){ItiRSzxQow = true;}
      if(WHhVixGHUd == cYdOkUhGwQ){WyehhxAMam = true;}
      if(jrVcAOwOJx == gSznpYdyTm){GMTdysTBKL = true;}
      while(wYThXOaRWM == sCZRFngnrh){jEtHIxBjMB = true;}
      while(cYdOkUhGwQ == cYdOkUhGwQ){DDgeXnOyFQ = true;}
      while(gSznpYdyTm == gSznpYdyTm){SKxbSuBDoH = true;}
      if(nzAPGfDCBk == true){nzAPGfDCBk = false;}
      if(QHMYmgIqXj == true){QHMYmgIqXj = false;}
      if(dCbpVcYfry == true){dCbpVcYfry = false;}
      if(jbxiYdXOHF == true){jbxiYdXOHF = false;}
      if(QeELAYGZBJ == true){QeELAYGZBJ = false;}
      if(PmajIkWKtc == true){PmajIkWKtc = false;}
      if(HWKCAnKcAI == true){HWKCAnKcAI = false;}
      if(ItiRSzxQow == true){ItiRSzxQow = false;}
      if(WyehhxAMam == true){WyehhxAMam = false;}
      if(GMTdysTBKL == true){GMTdysTBKL = false;}
      if(OcZrAUDJRI == true){OcZrAUDJRI = false;}
      if(nGVxGIrbUC == true){nGVxGIrbUC = false;}
      if(nxCMCuZETY == true){nxCMCuZETY = false;}
      if(fwGdhsXmhN == true){fwGdhsXmhN = false;}
      if(tquRzAqWXo == true){tquRzAqWXo = false;}
      if(BqgHXRaNoF == true){BqgHXRaNoF = false;}
      if(tyorcqzqPM == true){tyorcqzqPM = false;}
      if(jEtHIxBjMB == true){jEtHIxBjMB = false;}
      if(DDgeXnOyFQ == true){DDgeXnOyFQ = false;}
      if(SKxbSuBDoH == true){SKxbSuBDoH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XEHSUYPPWM
{ 
  void HPthcKpHIY()
  { 
      bool epIHRxXcfb = false;
      bool paWrYcWOMT = false;
      bool NZaNIVklJz = false;
      bool RIFibSHpMz = false;
      bool VnjEJgjlhn = false;
      bool yJrghEOtyu = false;
      bool LkSfJhUmQG = false;
      bool UfCMyZpWDb = false;
      bool kzDVBIPYAX = false;
      bool DNqQmjVEtb = false;
      bool LwVbTRHfiI = false;
      bool OrpWJMhwdB = false;
      bool SwlrCGnlYN = false;
      bool ElbbPncbCi = false;
      bool BiorJLWUGZ = false;
      bool CYZsIOKdYM = false;
      bool dUGUEbPOGU = false;
      bool jFttAiGtiq = false;
      bool jSezLeLiSA = false;
      bool dzCoFfcUmg = false;
      string eGahwQrCXM;
      string ttXNLHSetn;
      string aXYqeyJmlw;
      string XEfSgIqqdn;
      string PPOzQtGpfG;
      string GrWthHgiCy;
      string GEPaooOFgD;
      string PaBFXKIZaj;
      string qTHfpehkkZ;
      string aHnegLAnJa;
      string fBJbpfpQWW;
      string yGIRGmwikJ;
      string HcTGbIlVXM;
      string KTQAEoJeoJ;
      string oQONaUzVYt;
      string OQDASDgCzh;
      string sTrJMdpINQ;
      string cQsaUpNGfH;
      string IQxdxsQPgA;
      string HHeHQUYFAw;
      if(eGahwQrCXM == fBJbpfpQWW){epIHRxXcfb = true;}
      else if(fBJbpfpQWW == eGahwQrCXM){LwVbTRHfiI = true;}
      if(ttXNLHSetn == yGIRGmwikJ){paWrYcWOMT = true;}
      else if(yGIRGmwikJ == ttXNLHSetn){OrpWJMhwdB = true;}
      if(aXYqeyJmlw == HcTGbIlVXM){NZaNIVklJz = true;}
      else if(HcTGbIlVXM == aXYqeyJmlw){SwlrCGnlYN = true;}
      if(XEfSgIqqdn == KTQAEoJeoJ){RIFibSHpMz = true;}
      else if(KTQAEoJeoJ == XEfSgIqqdn){ElbbPncbCi = true;}
      if(PPOzQtGpfG == oQONaUzVYt){VnjEJgjlhn = true;}
      else if(oQONaUzVYt == PPOzQtGpfG){BiorJLWUGZ = true;}
      if(GrWthHgiCy == OQDASDgCzh){yJrghEOtyu = true;}
      else if(OQDASDgCzh == GrWthHgiCy){CYZsIOKdYM = true;}
      if(GEPaooOFgD == sTrJMdpINQ){LkSfJhUmQG = true;}
      else if(sTrJMdpINQ == GEPaooOFgD){dUGUEbPOGU = true;}
      if(PaBFXKIZaj == cQsaUpNGfH){UfCMyZpWDb = true;}
      if(qTHfpehkkZ == IQxdxsQPgA){kzDVBIPYAX = true;}
      if(aHnegLAnJa == HHeHQUYFAw){DNqQmjVEtb = true;}
      while(cQsaUpNGfH == PaBFXKIZaj){jFttAiGtiq = true;}
      while(IQxdxsQPgA == IQxdxsQPgA){jSezLeLiSA = true;}
      while(HHeHQUYFAw == HHeHQUYFAw){dzCoFfcUmg = true;}
      if(epIHRxXcfb == true){epIHRxXcfb = false;}
      if(paWrYcWOMT == true){paWrYcWOMT = false;}
      if(NZaNIVklJz == true){NZaNIVklJz = false;}
      if(RIFibSHpMz == true){RIFibSHpMz = false;}
      if(VnjEJgjlhn == true){VnjEJgjlhn = false;}
      if(yJrghEOtyu == true){yJrghEOtyu = false;}
      if(LkSfJhUmQG == true){LkSfJhUmQG = false;}
      if(UfCMyZpWDb == true){UfCMyZpWDb = false;}
      if(kzDVBIPYAX == true){kzDVBIPYAX = false;}
      if(DNqQmjVEtb == true){DNqQmjVEtb = false;}
      if(LwVbTRHfiI == true){LwVbTRHfiI = false;}
      if(OrpWJMhwdB == true){OrpWJMhwdB = false;}
      if(SwlrCGnlYN == true){SwlrCGnlYN = false;}
      if(ElbbPncbCi == true){ElbbPncbCi = false;}
      if(BiorJLWUGZ == true){BiorJLWUGZ = false;}
      if(CYZsIOKdYM == true){CYZsIOKdYM = false;}
      if(dUGUEbPOGU == true){dUGUEbPOGU = false;}
      if(jFttAiGtiq == true){jFttAiGtiq = false;}
      if(jSezLeLiSA == true){jSezLeLiSA = false;}
      if(dzCoFfcUmg == true){dzCoFfcUmg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CZAGYRTOVH
{ 
  void FEpPGmfWNB()
  { 
      bool AxYLDXodZE = false;
      bool MNCiJubebj = false;
      bool aJjUQYyCBc = false;
      bool qgLKJgHwMR = false;
      bool impoKCTeFC = false;
      bool JNcSNpMDue = false;
      bool YmcxMeCrYb = false;
      bool nfSKAmSuKN = false;
      bool FTwyTcErwS = false;
      bool TEBgruKsbe = false;
      bool AaFcOctSSZ = false;
      bool XQrgZEpdci = false;
      bool aKwFIjekRE = false;
      bool cYTfNdNTjp = false;
      bool ikZVuDLTHm = false;
      bool EgPrDpeAUe = false;
      bool yJANxyxMTu = false;
      bool qWsmAojZJE = false;
      bool XKcdzuJabX = false;
      bool zNzFrZjLYx = false;
      string HBpABJOscA;
      string PBSBIkDPWn;
      string rXqiHbkIeD;
      string LqgrCQsYtp;
      string KmbNmcdfWj;
      string DFqTriJHsZ;
      string XGNYoYUZzr;
      string qdUgdEwdwd;
      string xFluAFzMzS;
      string GlfUREZCXN;
      string HDgerZjKpn;
      string lfLObSTSYi;
      string YIafkExAOY;
      string etFhWtXHCZ;
      string UoVLgaaQsy;
      string jGcnnzcBsm;
      string bjuQIrZdrg;
      string uMQzOjlOyK;
      string dfHPoYQQsW;
      string QVNOyksEDn;
      if(HBpABJOscA == HDgerZjKpn){AxYLDXodZE = true;}
      else if(HDgerZjKpn == HBpABJOscA){AaFcOctSSZ = true;}
      if(PBSBIkDPWn == lfLObSTSYi){MNCiJubebj = true;}
      else if(lfLObSTSYi == PBSBIkDPWn){XQrgZEpdci = true;}
      if(rXqiHbkIeD == YIafkExAOY){aJjUQYyCBc = true;}
      else if(YIafkExAOY == rXqiHbkIeD){aKwFIjekRE = true;}
      if(LqgrCQsYtp == etFhWtXHCZ){qgLKJgHwMR = true;}
      else if(etFhWtXHCZ == LqgrCQsYtp){cYTfNdNTjp = true;}
      if(KmbNmcdfWj == UoVLgaaQsy){impoKCTeFC = true;}
      else if(UoVLgaaQsy == KmbNmcdfWj){ikZVuDLTHm = true;}
      if(DFqTriJHsZ == jGcnnzcBsm){JNcSNpMDue = true;}
      else if(jGcnnzcBsm == DFqTriJHsZ){EgPrDpeAUe = true;}
      if(XGNYoYUZzr == bjuQIrZdrg){YmcxMeCrYb = true;}
      else if(bjuQIrZdrg == XGNYoYUZzr){yJANxyxMTu = true;}
      if(qdUgdEwdwd == uMQzOjlOyK){nfSKAmSuKN = true;}
      if(xFluAFzMzS == dfHPoYQQsW){FTwyTcErwS = true;}
      if(GlfUREZCXN == QVNOyksEDn){TEBgruKsbe = true;}
      while(uMQzOjlOyK == qdUgdEwdwd){qWsmAojZJE = true;}
      while(dfHPoYQQsW == dfHPoYQQsW){XKcdzuJabX = true;}
      while(QVNOyksEDn == QVNOyksEDn){zNzFrZjLYx = true;}
      if(AxYLDXodZE == true){AxYLDXodZE = false;}
      if(MNCiJubebj == true){MNCiJubebj = false;}
      if(aJjUQYyCBc == true){aJjUQYyCBc = false;}
      if(qgLKJgHwMR == true){qgLKJgHwMR = false;}
      if(impoKCTeFC == true){impoKCTeFC = false;}
      if(JNcSNpMDue == true){JNcSNpMDue = false;}
      if(YmcxMeCrYb == true){YmcxMeCrYb = false;}
      if(nfSKAmSuKN == true){nfSKAmSuKN = false;}
      if(FTwyTcErwS == true){FTwyTcErwS = false;}
      if(TEBgruKsbe == true){TEBgruKsbe = false;}
      if(AaFcOctSSZ == true){AaFcOctSSZ = false;}
      if(XQrgZEpdci == true){XQrgZEpdci = false;}
      if(aKwFIjekRE == true){aKwFIjekRE = false;}
      if(cYTfNdNTjp == true){cYTfNdNTjp = false;}
      if(ikZVuDLTHm == true){ikZVuDLTHm = false;}
      if(EgPrDpeAUe == true){EgPrDpeAUe = false;}
      if(yJANxyxMTu == true){yJANxyxMTu = false;}
      if(qWsmAojZJE == true){qWsmAojZJE = false;}
      if(XKcdzuJabX == true){XKcdzuJabX = false;}
      if(zNzFrZjLYx == true){zNzFrZjLYx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JALWFRELFZ
{ 
  void JwSsMnkuyC()
  { 
      bool lkekYHxNge = false;
      bool WXiYBeeFNS = false;
      bool YhFnpKwxco = false;
      bool ABjqrkDySo = false;
      bool DhBfemORgf = false;
      bool NFMUbDepuO = false;
      bool LzkqeVmqfQ = false;
      bool afmYPqgZJD = false;
      bool wePwbuoOPn = false;
      bool FNDDdDwJBJ = false;
      bool zWkQFhRmFk = false;
      bool VFfqSfjoPj = false;
      bool fYbrLMcitM = false;
      bool uXYADYtzqs = false;
      bool cBIeSzgLkx = false;
      bool SHsQcZtsEr = false;
      bool Firroygfns = false;
      bool ljxVHdPxZL = false;
      bool eQxxtmdHWc = false;
      bool eBtynsJQoT = false;
      string SHEnjVPkij;
      string rRZfbAmDKB;
      string tjrWgtTHwd;
      string zsMpYfEUkT;
      string iDVoJRLzes;
      string kENWlhPgGp;
      string CIoFjzEjGw;
      string wSSpSqOCMO;
      string hTbDrtepDp;
      string PWNuQaOPFK;
      string NbsixSlWDu;
      string TNTrHiflNp;
      string TOfPfYEWZr;
      string cyxCBGasGY;
      string HIlHWCDVmh;
      string tbCOqzucCX;
      string NOxLSUQRqB;
      string ImenhLbXsd;
      string VijqxAwhLC;
      string KxphLrKanB;
      if(SHEnjVPkij == NbsixSlWDu){lkekYHxNge = true;}
      else if(NbsixSlWDu == SHEnjVPkij){zWkQFhRmFk = true;}
      if(rRZfbAmDKB == TNTrHiflNp){WXiYBeeFNS = true;}
      else if(TNTrHiflNp == rRZfbAmDKB){VFfqSfjoPj = true;}
      if(tjrWgtTHwd == TOfPfYEWZr){YhFnpKwxco = true;}
      else if(TOfPfYEWZr == tjrWgtTHwd){fYbrLMcitM = true;}
      if(zsMpYfEUkT == cyxCBGasGY){ABjqrkDySo = true;}
      else if(cyxCBGasGY == zsMpYfEUkT){uXYADYtzqs = true;}
      if(iDVoJRLzes == HIlHWCDVmh){DhBfemORgf = true;}
      else if(HIlHWCDVmh == iDVoJRLzes){cBIeSzgLkx = true;}
      if(kENWlhPgGp == tbCOqzucCX){NFMUbDepuO = true;}
      else if(tbCOqzucCX == kENWlhPgGp){SHsQcZtsEr = true;}
      if(CIoFjzEjGw == NOxLSUQRqB){LzkqeVmqfQ = true;}
      else if(NOxLSUQRqB == CIoFjzEjGw){Firroygfns = true;}
      if(wSSpSqOCMO == ImenhLbXsd){afmYPqgZJD = true;}
      if(hTbDrtepDp == VijqxAwhLC){wePwbuoOPn = true;}
      if(PWNuQaOPFK == KxphLrKanB){FNDDdDwJBJ = true;}
      while(ImenhLbXsd == wSSpSqOCMO){ljxVHdPxZL = true;}
      while(VijqxAwhLC == VijqxAwhLC){eQxxtmdHWc = true;}
      while(KxphLrKanB == KxphLrKanB){eBtynsJQoT = true;}
      if(lkekYHxNge == true){lkekYHxNge = false;}
      if(WXiYBeeFNS == true){WXiYBeeFNS = false;}
      if(YhFnpKwxco == true){YhFnpKwxco = false;}
      if(ABjqrkDySo == true){ABjqrkDySo = false;}
      if(DhBfemORgf == true){DhBfemORgf = false;}
      if(NFMUbDepuO == true){NFMUbDepuO = false;}
      if(LzkqeVmqfQ == true){LzkqeVmqfQ = false;}
      if(afmYPqgZJD == true){afmYPqgZJD = false;}
      if(wePwbuoOPn == true){wePwbuoOPn = false;}
      if(FNDDdDwJBJ == true){FNDDdDwJBJ = false;}
      if(zWkQFhRmFk == true){zWkQFhRmFk = false;}
      if(VFfqSfjoPj == true){VFfqSfjoPj = false;}
      if(fYbrLMcitM == true){fYbrLMcitM = false;}
      if(uXYADYtzqs == true){uXYADYtzqs = false;}
      if(cBIeSzgLkx == true){cBIeSzgLkx = false;}
      if(SHsQcZtsEr == true){SHsQcZtsEr = false;}
      if(Firroygfns == true){Firroygfns = false;}
      if(ljxVHdPxZL == true){ljxVHdPxZL = false;}
      if(eQxxtmdHWc == true){eQxxtmdHWc = false;}
      if(eBtynsJQoT == true){eBtynsJQoT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AEREBPLBGD
{ 
  void szydPMiEpx()
  { 
      bool CGVQFkNgDw = false;
      bool gyrpyLMFnP = false;
      bool lLUFnWAlIR = false;
      bool lFBkqsWtfJ = false;
      bool tclOPXzNzm = false;
      bool WbTpLqkPci = false;
      bool jaXlKawHzF = false;
      bool oRZeVIYGpQ = false;
      bool XmlUtKkKZA = false;
      bool IGRxYSFADn = false;
      bool arNtyFBoUC = false;
      bool ReZMKxoCrA = false;
      bool olhzxhzbGD = false;
      bool DYCBofYqWn = false;
      bool IwpWhcgFlb = false;
      bool cCHDzoJOxQ = false;
      bool FYiQysbXWd = false;
      bool XxfDqruKQT = false;
      bool BspeZBQzCz = false;
      bool VJtGhiNZXo = false;
      string qLKALlfQTQ;
      string xSTGMWrZHY;
      string krDPMElLzg;
      string leAZoKpHVA;
      string DxoscSkSlR;
      string GQGoRzHunG;
      string zTQmeRRtRB;
      string gkDHUmCJms;
      string TSZhZVYLHp;
      string CuSPAjgCOK;
      string BqBjkVMyTd;
      string wxItmfthMJ;
      string sGlbzlRnGk;
      string GAubrbRoxE;
      string IZqdsElYbU;
      string pyoEQuFZky;
      string EYriXwCfCK;
      string OEkIBTOHht;
      string zrLltHKpLw;
      string VqEyzjhIGx;
      if(qLKALlfQTQ == BqBjkVMyTd){CGVQFkNgDw = true;}
      else if(BqBjkVMyTd == qLKALlfQTQ){arNtyFBoUC = true;}
      if(xSTGMWrZHY == wxItmfthMJ){gyrpyLMFnP = true;}
      else if(wxItmfthMJ == xSTGMWrZHY){ReZMKxoCrA = true;}
      if(krDPMElLzg == sGlbzlRnGk){lLUFnWAlIR = true;}
      else if(sGlbzlRnGk == krDPMElLzg){olhzxhzbGD = true;}
      if(leAZoKpHVA == GAubrbRoxE){lFBkqsWtfJ = true;}
      else if(GAubrbRoxE == leAZoKpHVA){DYCBofYqWn = true;}
      if(DxoscSkSlR == IZqdsElYbU){tclOPXzNzm = true;}
      else if(IZqdsElYbU == DxoscSkSlR){IwpWhcgFlb = true;}
      if(GQGoRzHunG == pyoEQuFZky){WbTpLqkPci = true;}
      else if(pyoEQuFZky == GQGoRzHunG){cCHDzoJOxQ = true;}
      if(zTQmeRRtRB == EYriXwCfCK){jaXlKawHzF = true;}
      else if(EYriXwCfCK == zTQmeRRtRB){FYiQysbXWd = true;}
      if(gkDHUmCJms == OEkIBTOHht){oRZeVIYGpQ = true;}
      if(TSZhZVYLHp == zrLltHKpLw){XmlUtKkKZA = true;}
      if(CuSPAjgCOK == VqEyzjhIGx){IGRxYSFADn = true;}
      while(OEkIBTOHht == gkDHUmCJms){XxfDqruKQT = true;}
      while(zrLltHKpLw == zrLltHKpLw){BspeZBQzCz = true;}
      while(VqEyzjhIGx == VqEyzjhIGx){VJtGhiNZXo = true;}
      if(CGVQFkNgDw == true){CGVQFkNgDw = false;}
      if(gyrpyLMFnP == true){gyrpyLMFnP = false;}
      if(lLUFnWAlIR == true){lLUFnWAlIR = false;}
      if(lFBkqsWtfJ == true){lFBkqsWtfJ = false;}
      if(tclOPXzNzm == true){tclOPXzNzm = false;}
      if(WbTpLqkPci == true){WbTpLqkPci = false;}
      if(jaXlKawHzF == true){jaXlKawHzF = false;}
      if(oRZeVIYGpQ == true){oRZeVIYGpQ = false;}
      if(XmlUtKkKZA == true){XmlUtKkKZA = false;}
      if(IGRxYSFADn == true){IGRxYSFADn = false;}
      if(arNtyFBoUC == true){arNtyFBoUC = false;}
      if(ReZMKxoCrA == true){ReZMKxoCrA = false;}
      if(olhzxhzbGD == true){olhzxhzbGD = false;}
      if(DYCBofYqWn == true){DYCBofYqWn = false;}
      if(IwpWhcgFlb == true){IwpWhcgFlb = false;}
      if(cCHDzoJOxQ == true){cCHDzoJOxQ = false;}
      if(FYiQysbXWd == true){FYiQysbXWd = false;}
      if(XxfDqruKQT == true){XxfDqruKQT = false;}
      if(BspeZBQzCz == true){BspeZBQzCz = false;}
      if(VJtGhiNZXo == true){VJtGhiNZXo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XGOKJEJYGY
{ 
  void xGGwIrQGFM()
  { 
      bool dotQPQOhlQ = false;
      bool wADuqGGesy = false;
      bool GZLUKwZdue = false;
      bool MicotrowOC = false;
      bool CUFNsayVgK = false;
      bool VxmXbEcZGS = false;
      bool qjlHEMWNBz = false;
      bool QJQqulUyaj = false;
      bool yDxjIOuFNp = false;
      bool OPpuKShyIf = false;
      bool DjThtLgwcp = false;
      bool ieyWUmlCyo = false;
      bool RRAKjBTUfb = false;
      bool EWotfOiPpw = false;
      bool hzcXHjQTZW = false;
      bool ffzTOliJxr = false;
      bool rLPAkLoDpG = false;
      bool DWMBGRocDA = false;
      bool jzuJuYWVfs = false;
      bool eZSxEWjblu = false;
      string yyAillpage;
      string igujCRQQYB;
      string wfOJtOklrZ;
      string tVkbRhxIlq;
      string oyUgsTDLJH;
      string nNiBtRjpoX;
      string AEiGjMuSRT;
      string UIdhMxLgPa;
      string LYbjlfljhz;
      string yGSOpjPOxf;
      string XjtpmejBox;
      string GCZNMbczTD;
      string ZLjRUNoPrb;
      string hxjjCadlxH;
      string wktkswfFCN;
      string HQtsFMzcUY;
      string pTINPJRpKk;
      string ypCMHoQzYY;
      string hjNdTQCqdp;
      string aBQXQcbgVi;
      if(yyAillpage == XjtpmejBox){dotQPQOhlQ = true;}
      else if(XjtpmejBox == yyAillpage){DjThtLgwcp = true;}
      if(igujCRQQYB == GCZNMbczTD){wADuqGGesy = true;}
      else if(GCZNMbczTD == igujCRQQYB){ieyWUmlCyo = true;}
      if(wfOJtOklrZ == ZLjRUNoPrb){GZLUKwZdue = true;}
      else if(ZLjRUNoPrb == wfOJtOklrZ){RRAKjBTUfb = true;}
      if(tVkbRhxIlq == hxjjCadlxH){MicotrowOC = true;}
      else if(hxjjCadlxH == tVkbRhxIlq){EWotfOiPpw = true;}
      if(oyUgsTDLJH == wktkswfFCN){CUFNsayVgK = true;}
      else if(wktkswfFCN == oyUgsTDLJH){hzcXHjQTZW = true;}
      if(nNiBtRjpoX == HQtsFMzcUY){VxmXbEcZGS = true;}
      else if(HQtsFMzcUY == nNiBtRjpoX){ffzTOliJxr = true;}
      if(AEiGjMuSRT == pTINPJRpKk){qjlHEMWNBz = true;}
      else if(pTINPJRpKk == AEiGjMuSRT){rLPAkLoDpG = true;}
      if(UIdhMxLgPa == ypCMHoQzYY){QJQqulUyaj = true;}
      if(LYbjlfljhz == hjNdTQCqdp){yDxjIOuFNp = true;}
      if(yGSOpjPOxf == aBQXQcbgVi){OPpuKShyIf = true;}
      while(ypCMHoQzYY == UIdhMxLgPa){DWMBGRocDA = true;}
      while(hjNdTQCqdp == hjNdTQCqdp){jzuJuYWVfs = true;}
      while(aBQXQcbgVi == aBQXQcbgVi){eZSxEWjblu = true;}
      if(dotQPQOhlQ == true){dotQPQOhlQ = false;}
      if(wADuqGGesy == true){wADuqGGesy = false;}
      if(GZLUKwZdue == true){GZLUKwZdue = false;}
      if(MicotrowOC == true){MicotrowOC = false;}
      if(CUFNsayVgK == true){CUFNsayVgK = false;}
      if(VxmXbEcZGS == true){VxmXbEcZGS = false;}
      if(qjlHEMWNBz == true){qjlHEMWNBz = false;}
      if(QJQqulUyaj == true){QJQqulUyaj = false;}
      if(yDxjIOuFNp == true){yDxjIOuFNp = false;}
      if(OPpuKShyIf == true){OPpuKShyIf = false;}
      if(DjThtLgwcp == true){DjThtLgwcp = false;}
      if(ieyWUmlCyo == true){ieyWUmlCyo = false;}
      if(RRAKjBTUfb == true){RRAKjBTUfb = false;}
      if(EWotfOiPpw == true){EWotfOiPpw = false;}
      if(hzcXHjQTZW == true){hzcXHjQTZW = false;}
      if(ffzTOliJxr == true){ffzTOliJxr = false;}
      if(rLPAkLoDpG == true){rLPAkLoDpG = false;}
      if(DWMBGRocDA == true){DWMBGRocDA = false;}
      if(jzuJuYWVfs == true){jzuJuYWVfs = false;}
      if(eZSxEWjblu == true){eZSxEWjblu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QLGEVGLLTA
{ 
  void YllfeRlchf()
  { 
      bool MRxkIjiUAM = false;
      bool VDKzcuWGuY = false;
      bool tQrObeejGB = false;
      bool rABNMYJeKx = false;
      bool PdmqmfNSQR = false;
      bool qreqKwYhIc = false;
      bool EyOzTVBwmD = false;
      bool kqwxJQcBau = false;
      bool QMTnKzUKCQ = false;
      bool zaWgsQOnWR = false;
      bool eRfMfzwhht = false;
      bool SXHNLqeZnU = false;
      bool BqsVEKUPDr = false;
      bool BodJQzgGIL = false;
      bool DlbIyaTJUC = false;
      bool lnzCPnXJIV = false;
      bool dgeorcsxwM = false;
      bool KYRcQOOkXc = false;
      bool pLtBGMpasb = false;
      bool bWylgWHlPU = false;
      string AnbowzwMcw;
      string YAKUrcmlWN;
      string yJqsewsujB;
      string bebbWYDKMY;
      string ZgzDOyMtky;
      string HZBfBqxiKA;
      string GBcbUsYhxT;
      string ZcYxnQKmdf;
      string izKlsCcuZe;
      string aTzMSYEWiU;
      string ZdwRYeAErk;
      string gJFdQGpqhR;
      string QcIRrFcMeP;
      string MmEIFFCrMO;
      string CYDoyROVwL;
      string hNnQEwVdZS;
      string CnYcXsEwXK;
      string DydSPrZSTZ;
      string pGQSgzynEJ;
      string iYSsMOzZQF;
      if(AnbowzwMcw == ZdwRYeAErk){MRxkIjiUAM = true;}
      else if(ZdwRYeAErk == AnbowzwMcw){eRfMfzwhht = true;}
      if(YAKUrcmlWN == gJFdQGpqhR){VDKzcuWGuY = true;}
      else if(gJFdQGpqhR == YAKUrcmlWN){SXHNLqeZnU = true;}
      if(yJqsewsujB == QcIRrFcMeP){tQrObeejGB = true;}
      else if(QcIRrFcMeP == yJqsewsujB){BqsVEKUPDr = true;}
      if(bebbWYDKMY == MmEIFFCrMO){rABNMYJeKx = true;}
      else if(MmEIFFCrMO == bebbWYDKMY){BodJQzgGIL = true;}
      if(ZgzDOyMtky == CYDoyROVwL){PdmqmfNSQR = true;}
      else if(CYDoyROVwL == ZgzDOyMtky){DlbIyaTJUC = true;}
      if(HZBfBqxiKA == hNnQEwVdZS){qreqKwYhIc = true;}
      else if(hNnQEwVdZS == HZBfBqxiKA){lnzCPnXJIV = true;}
      if(GBcbUsYhxT == CnYcXsEwXK){EyOzTVBwmD = true;}
      else if(CnYcXsEwXK == GBcbUsYhxT){dgeorcsxwM = true;}
      if(ZcYxnQKmdf == DydSPrZSTZ){kqwxJQcBau = true;}
      if(izKlsCcuZe == pGQSgzynEJ){QMTnKzUKCQ = true;}
      if(aTzMSYEWiU == iYSsMOzZQF){zaWgsQOnWR = true;}
      while(DydSPrZSTZ == ZcYxnQKmdf){KYRcQOOkXc = true;}
      while(pGQSgzynEJ == pGQSgzynEJ){pLtBGMpasb = true;}
      while(iYSsMOzZQF == iYSsMOzZQF){bWylgWHlPU = true;}
      if(MRxkIjiUAM == true){MRxkIjiUAM = false;}
      if(VDKzcuWGuY == true){VDKzcuWGuY = false;}
      if(tQrObeejGB == true){tQrObeejGB = false;}
      if(rABNMYJeKx == true){rABNMYJeKx = false;}
      if(PdmqmfNSQR == true){PdmqmfNSQR = false;}
      if(qreqKwYhIc == true){qreqKwYhIc = false;}
      if(EyOzTVBwmD == true){EyOzTVBwmD = false;}
      if(kqwxJQcBau == true){kqwxJQcBau = false;}
      if(QMTnKzUKCQ == true){QMTnKzUKCQ = false;}
      if(zaWgsQOnWR == true){zaWgsQOnWR = false;}
      if(eRfMfzwhht == true){eRfMfzwhht = false;}
      if(SXHNLqeZnU == true){SXHNLqeZnU = false;}
      if(BqsVEKUPDr == true){BqsVEKUPDr = false;}
      if(BodJQzgGIL == true){BodJQzgGIL = false;}
      if(DlbIyaTJUC == true){DlbIyaTJUC = false;}
      if(lnzCPnXJIV == true){lnzCPnXJIV = false;}
      if(dgeorcsxwM == true){dgeorcsxwM = false;}
      if(KYRcQOOkXc == true){KYRcQOOkXc = false;}
      if(pLtBGMpasb == true){pLtBGMpasb = false;}
      if(bWylgWHlPU == true){bWylgWHlPU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PFISUIKHFC
{ 
  void NMzqVCcZFq()
  { 
      bool RcuiUwDIkM = false;
      bool QMrhoQTXBf = false;
      bool fsodHarXIU = false;
      bool DZEiqbCoXQ = false;
      bool CfToRGxVGM = false;
      bool ZDZqCYnRat = false;
      bool EfAPIpHJqN = false;
      bool OdzjdzYzLB = false;
      bool cVQwuAzNgS = false;
      bool mkNdMWfEfb = false;
      bool zndrxuDpNC = false;
      bool znFZQhPEUI = false;
      bool psbYZcQUXG = false;
      bool TUSjCorXyz = false;
      bool wJAdSzenNe = false;
      bool GbjXkFLFRU = false;
      bool eiSGieUUXb = false;
      bool oqGULgryGa = false;
      bool ybGrArkuzw = false;
      bool clGdTMqttm = false;
      string jdQzsgWiyf;
      string VYUtRdUpgf;
      string QXVZZZkSNH;
      string ROVFSaxtNz;
      string oEPPTOpFGB;
      string tEcKdMIqYT;
      string wEVqOHDOap;
      string gZchpMIFFL;
      string jeLLMMlKbG;
      string RGUtDkhYBM;
      string KbdPUUauTR;
      string DCkMiRrKdB;
      string UrmTYZFidF;
      string diEsAIAupr;
      string lqpKCPUHKk;
      string rXtAqSoKqt;
      string OrQOmUxqMa;
      string QwTlOdCbRI;
      string ExXsMGoECh;
      string SpEwcsabWh;
      if(jdQzsgWiyf == KbdPUUauTR){RcuiUwDIkM = true;}
      else if(KbdPUUauTR == jdQzsgWiyf){zndrxuDpNC = true;}
      if(VYUtRdUpgf == DCkMiRrKdB){QMrhoQTXBf = true;}
      else if(DCkMiRrKdB == VYUtRdUpgf){znFZQhPEUI = true;}
      if(QXVZZZkSNH == UrmTYZFidF){fsodHarXIU = true;}
      else if(UrmTYZFidF == QXVZZZkSNH){psbYZcQUXG = true;}
      if(ROVFSaxtNz == diEsAIAupr){DZEiqbCoXQ = true;}
      else if(diEsAIAupr == ROVFSaxtNz){TUSjCorXyz = true;}
      if(oEPPTOpFGB == lqpKCPUHKk){CfToRGxVGM = true;}
      else if(lqpKCPUHKk == oEPPTOpFGB){wJAdSzenNe = true;}
      if(tEcKdMIqYT == rXtAqSoKqt){ZDZqCYnRat = true;}
      else if(rXtAqSoKqt == tEcKdMIqYT){GbjXkFLFRU = true;}
      if(wEVqOHDOap == OrQOmUxqMa){EfAPIpHJqN = true;}
      else if(OrQOmUxqMa == wEVqOHDOap){eiSGieUUXb = true;}
      if(gZchpMIFFL == QwTlOdCbRI){OdzjdzYzLB = true;}
      if(jeLLMMlKbG == ExXsMGoECh){cVQwuAzNgS = true;}
      if(RGUtDkhYBM == SpEwcsabWh){mkNdMWfEfb = true;}
      while(QwTlOdCbRI == gZchpMIFFL){oqGULgryGa = true;}
      while(ExXsMGoECh == ExXsMGoECh){ybGrArkuzw = true;}
      while(SpEwcsabWh == SpEwcsabWh){clGdTMqttm = true;}
      if(RcuiUwDIkM == true){RcuiUwDIkM = false;}
      if(QMrhoQTXBf == true){QMrhoQTXBf = false;}
      if(fsodHarXIU == true){fsodHarXIU = false;}
      if(DZEiqbCoXQ == true){DZEiqbCoXQ = false;}
      if(CfToRGxVGM == true){CfToRGxVGM = false;}
      if(ZDZqCYnRat == true){ZDZqCYnRat = false;}
      if(EfAPIpHJqN == true){EfAPIpHJqN = false;}
      if(OdzjdzYzLB == true){OdzjdzYzLB = false;}
      if(cVQwuAzNgS == true){cVQwuAzNgS = false;}
      if(mkNdMWfEfb == true){mkNdMWfEfb = false;}
      if(zndrxuDpNC == true){zndrxuDpNC = false;}
      if(znFZQhPEUI == true){znFZQhPEUI = false;}
      if(psbYZcQUXG == true){psbYZcQUXG = false;}
      if(TUSjCorXyz == true){TUSjCorXyz = false;}
      if(wJAdSzenNe == true){wJAdSzenNe = false;}
      if(GbjXkFLFRU == true){GbjXkFLFRU = false;}
      if(eiSGieUUXb == true){eiSGieUUXb = false;}
      if(oqGULgryGa == true){oqGULgryGa = false;}
      if(ybGrArkuzw == true){ybGrArkuzw = false;}
      if(clGdTMqttm == true){clGdTMqttm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZGGBVKWFOM
{ 
  void iUYRHgDZGH()
  { 
      bool qCgSNwgtsH = false;
      bool czzmYXFTPh = false;
      bool BPddRSQNth = false;
      bool hkmHzhmslB = false;
      bool BuNfyyXnod = false;
      bool UcFsbaYCAu = false;
      bool fSAKYqLqmq = false;
      bool jMhNfGCxeT = false;
      bool tcYPMEftfY = false;
      bool JkrqVitCGH = false;
      bool lgBysIuqMV = false;
      bool YaXgADtkyT = false;
      bool LRLNhzTqrx = false;
      bool LzqXhNbZVD = false;
      bool JngKziMLpS = false;
      bool nIEluTVmQt = false;
      bool oEzPJYizzm = false;
      bool aTPtKWkAOy = false;
      bool mIAZICuEbN = false;
      bool qoJbOFoRAa = false;
      string dSiRnaAqtn;
      string KYeehVGlBn;
      string xnZiWXhRHF;
      string eVDRhkJwcu;
      string StXNYqlleX;
      string JWeVNorAtP;
      string shjnInUNxx;
      string LJJGVCQMJe;
      string luliwHqhEr;
      string rJCMBjKiEj;
      string VYnhLANYzK;
      string XepPdxuArB;
      string xmJEECHwEl;
      string rgIZJNHEXu;
      string sRhsTNSmiE;
      string nJqCmhOjdI;
      string sRUNRqWQFQ;
      string pqcwIeFPjq;
      string jUMAyipGma;
      string yXaOCaxUbc;
      if(dSiRnaAqtn == VYnhLANYzK){qCgSNwgtsH = true;}
      else if(VYnhLANYzK == dSiRnaAqtn){lgBysIuqMV = true;}
      if(KYeehVGlBn == XepPdxuArB){czzmYXFTPh = true;}
      else if(XepPdxuArB == KYeehVGlBn){YaXgADtkyT = true;}
      if(xnZiWXhRHF == xmJEECHwEl){BPddRSQNth = true;}
      else if(xmJEECHwEl == xnZiWXhRHF){LRLNhzTqrx = true;}
      if(eVDRhkJwcu == rgIZJNHEXu){hkmHzhmslB = true;}
      else if(rgIZJNHEXu == eVDRhkJwcu){LzqXhNbZVD = true;}
      if(StXNYqlleX == sRhsTNSmiE){BuNfyyXnod = true;}
      else if(sRhsTNSmiE == StXNYqlleX){JngKziMLpS = true;}
      if(JWeVNorAtP == nJqCmhOjdI){UcFsbaYCAu = true;}
      else if(nJqCmhOjdI == JWeVNorAtP){nIEluTVmQt = true;}
      if(shjnInUNxx == sRUNRqWQFQ){fSAKYqLqmq = true;}
      else if(sRUNRqWQFQ == shjnInUNxx){oEzPJYizzm = true;}
      if(LJJGVCQMJe == pqcwIeFPjq){jMhNfGCxeT = true;}
      if(luliwHqhEr == jUMAyipGma){tcYPMEftfY = true;}
      if(rJCMBjKiEj == yXaOCaxUbc){JkrqVitCGH = true;}
      while(pqcwIeFPjq == LJJGVCQMJe){aTPtKWkAOy = true;}
      while(jUMAyipGma == jUMAyipGma){mIAZICuEbN = true;}
      while(yXaOCaxUbc == yXaOCaxUbc){qoJbOFoRAa = true;}
      if(qCgSNwgtsH == true){qCgSNwgtsH = false;}
      if(czzmYXFTPh == true){czzmYXFTPh = false;}
      if(BPddRSQNth == true){BPddRSQNth = false;}
      if(hkmHzhmslB == true){hkmHzhmslB = false;}
      if(BuNfyyXnod == true){BuNfyyXnod = false;}
      if(UcFsbaYCAu == true){UcFsbaYCAu = false;}
      if(fSAKYqLqmq == true){fSAKYqLqmq = false;}
      if(jMhNfGCxeT == true){jMhNfGCxeT = false;}
      if(tcYPMEftfY == true){tcYPMEftfY = false;}
      if(JkrqVitCGH == true){JkrqVitCGH = false;}
      if(lgBysIuqMV == true){lgBysIuqMV = false;}
      if(YaXgADtkyT == true){YaXgADtkyT = false;}
      if(LRLNhzTqrx == true){LRLNhzTqrx = false;}
      if(LzqXhNbZVD == true){LzqXhNbZVD = false;}
      if(JngKziMLpS == true){JngKziMLpS = false;}
      if(nIEluTVmQt == true){nIEluTVmQt = false;}
      if(oEzPJYizzm == true){oEzPJYizzm = false;}
      if(aTPtKWkAOy == true){aTPtKWkAOy = false;}
      if(mIAZICuEbN == true){mIAZICuEbN = false;}
      if(qoJbOFoRAa == true){qoJbOFoRAa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MCPMCQWSSS
{ 
  void dNbaEMSgOE()
  { 
      bool fFMQTTglEZ = false;
      bool CJWJczVwEw = false;
      bool kbwIkYIkfE = false;
      bool wiBfyXlHpi = false;
      bool tmVkPalVxI = false;
      bool pCyhjDJEet = false;
      bool KuFzdTHqKF = false;
      bool NOFVCyGLrK = false;
      bool mmnXOtjTut = false;
      bool OgcwXygVGw = false;
      bool SuKqubwcfl = false;
      bool xxLUHXHhkj = false;
      bool inuPpflJyE = false;
      bool QjFwqqbxbl = false;
      bool xHnIxRUHoA = false;
      bool qykWMdAtAO = false;
      bool pmebVMrOcP = false;
      bool uKFylbAlSY = false;
      bool KdUxMRzhjM = false;
      bool qhwNwKcMmj = false;
      string EqsnunfBYl;
      string ICZsClCVRN;
      string VaJCMAbHZk;
      string GfXwSMswch;
      string nNHWzRCios;
      string rwEsAchqbt;
      string LYamfbddZo;
      string sGrjZHSlDt;
      string ysRgrJaeup;
      string dBThVOmUqW;
      string nXJzzkDUSs;
      string JwngwSGstV;
      string ByhiLrlJNK;
      string UytfGZjShG;
      string FGLCggNmlD;
      string HsZUUooZmH;
      string zsHHXKBHZV;
      string inLmQulfCd;
      string dzXKDbYZKR;
      string jJeZHLyDdV;
      if(EqsnunfBYl == nXJzzkDUSs){fFMQTTglEZ = true;}
      else if(nXJzzkDUSs == EqsnunfBYl){SuKqubwcfl = true;}
      if(ICZsClCVRN == JwngwSGstV){CJWJczVwEw = true;}
      else if(JwngwSGstV == ICZsClCVRN){xxLUHXHhkj = true;}
      if(VaJCMAbHZk == ByhiLrlJNK){kbwIkYIkfE = true;}
      else if(ByhiLrlJNK == VaJCMAbHZk){inuPpflJyE = true;}
      if(GfXwSMswch == UytfGZjShG){wiBfyXlHpi = true;}
      else if(UytfGZjShG == GfXwSMswch){QjFwqqbxbl = true;}
      if(nNHWzRCios == FGLCggNmlD){tmVkPalVxI = true;}
      else if(FGLCggNmlD == nNHWzRCios){xHnIxRUHoA = true;}
      if(rwEsAchqbt == HsZUUooZmH){pCyhjDJEet = true;}
      else if(HsZUUooZmH == rwEsAchqbt){qykWMdAtAO = true;}
      if(LYamfbddZo == zsHHXKBHZV){KuFzdTHqKF = true;}
      else if(zsHHXKBHZV == LYamfbddZo){pmebVMrOcP = true;}
      if(sGrjZHSlDt == inLmQulfCd){NOFVCyGLrK = true;}
      if(ysRgrJaeup == dzXKDbYZKR){mmnXOtjTut = true;}
      if(dBThVOmUqW == jJeZHLyDdV){OgcwXygVGw = true;}
      while(inLmQulfCd == sGrjZHSlDt){uKFylbAlSY = true;}
      while(dzXKDbYZKR == dzXKDbYZKR){KdUxMRzhjM = true;}
      while(jJeZHLyDdV == jJeZHLyDdV){qhwNwKcMmj = true;}
      if(fFMQTTglEZ == true){fFMQTTglEZ = false;}
      if(CJWJczVwEw == true){CJWJczVwEw = false;}
      if(kbwIkYIkfE == true){kbwIkYIkfE = false;}
      if(wiBfyXlHpi == true){wiBfyXlHpi = false;}
      if(tmVkPalVxI == true){tmVkPalVxI = false;}
      if(pCyhjDJEet == true){pCyhjDJEet = false;}
      if(KuFzdTHqKF == true){KuFzdTHqKF = false;}
      if(NOFVCyGLrK == true){NOFVCyGLrK = false;}
      if(mmnXOtjTut == true){mmnXOtjTut = false;}
      if(OgcwXygVGw == true){OgcwXygVGw = false;}
      if(SuKqubwcfl == true){SuKqubwcfl = false;}
      if(xxLUHXHhkj == true){xxLUHXHhkj = false;}
      if(inuPpflJyE == true){inuPpflJyE = false;}
      if(QjFwqqbxbl == true){QjFwqqbxbl = false;}
      if(xHnIxRUHoA == true){xHnIxRUHoA = false;}
      if(qykWMdAtAO == true){qykWMdAtAO = false;}
      if(pmebVMrOcP == true){pmebVMrOcP = false;}
      if(uKFylbAlSY == true){uKFylbAlSY = false;}
      if(KdUxMRzhjM == true){KdUxMRzhjM = false;}
      if(qhwNwKcMmj == true){qhwNwKcMmj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENDBOBZCDW
{ 
  void QtWSBnDnPY()
  { 
      bool FbTjcEzzBa = false;
      bool rSOlBdFobP = false;
      bool fSRadomuGk = false;
      bool foonRAfKLY = false;
      bool spupmnJHeu = false;
      bool ZdOskmJsFm = false;
      bool RDrPuCdaUA = false;
      bool yudDVpWbmp = false;
      bool efQLLBZuCe = false;
      bool qlEXHpxftj = false;
      bool KhmdweAKXt = false;
      bool PhGPIkmfEt = false;
      bool chXoJMpGwe = false;
      bool sqhCfwslPg = false;
      bool BOWHOIeoOV = false;
      bool CQbAHbKxTi = false;
      bool ntOrBYAEiL = false;
      bool rAQXsNLPaA = false;
      bool hAqaccPhtE = false;
      bool luSfrGAdGp = false;
      string cCTPONymTF;
      string gWMkGFIrmE;
      string HyqeByxEYY;
      string KjaCKLcywM;
      string RaLLRwroxu;
      string PNgIIeLoNQ;
      string PsOtuxuKZt;
      string cKwamfmfME;
      string GIHcJxCStf;
      string AnjfxXMQQU;
      string BhODSFQGUb;
      string rebJJGllkx;
      string tcQtsnaQdP;
      string TVPrDYsEKE;
      string fwxRnVLZVp;
      string lafSZXRUJd;
      string eAcFIVPjFk;
      string NgafRyfyFX;
      string cAtncsowRe;
      string GYtfZfSqJR;
      if(cCTPONymTF == BhODSFQGUb){FbTjcEzzBa = true;}
      else if(BhODSFQGUb == cCTPONymTF){KhmdweAKXt = true;}
      if(gWMkGFIrmE == rebJJGllkx){rSOlBdFobP = true;}
      else if(rebJJGllkx == gWMkGFIrmE){PhGPIkmfEt = true;}
      if(HyqeByxEYY == tcQtsnaQdP){fSRadomuGk = true;}
      else if(tcQtsnaQdP == HyqeByxEYY){chXoJMpGwe = true;}
      if(KjaCKLcywM == TVPrDYsEKE){foonRAfKLY = true;}
      else if(TVPrDYsEKE == KjaCKLcywM){sqhCfwslPg = true;}
      if(RaLLRwroxu == fwxRnVLZVp){spupmnJHeu = true;}
      else if(fwxRnVLZVp == RaLLRwroxu){BOWHOIeoOV = true;}
      if(PNgIIeLoNQ == lafSZXRUJd){ZdOskmJsFm = true;}
      else if(lafSZXRUJd == PNgIIeLoNQ){CQbAHbKxTi = true;}
      if(PsOtuxuKZt == eAcFIVPjFk){RDrPuCdaUA = true;}
      else if(eAcFIVPjFk == PsOtuxuKZt){ntOrBYAEiL = true;}
      if(cKwamfmfME == NgafRyfyFX){yudDVpWbmp = true;}
      if(GIHcJxCStf == cAtncsowRe){efQLLBZuCe = true;}
      if(AnjfxXMQQU == GYtfZfSqJR){qlEXHpxftj = true;}
      while(NgafRyfyFX == cKwamfmfME){rAQXsNLPaA = true;}
      while(cAtncsowRe == cAtncsowRe){hAqaccPhtE = true;}
      while(GYtfZfSqJR == GYtfZfSqJR){luSfrGAdGp = true;}
      if(FbTjcEzzBa == true){FbTjcEzzBa = false;}
      if(rSOlBdFobP == true){rSOlBdFobP = false;}
      if(fSRadomuGk == true){fSRadomuGk = false;}
      if(foonRAfKLY == true){foonRAfKLY = false;}
      if(spupmnJHeu == true){spupmnJHeu = false;}
      if(ZdOskmJsFm == true){ZdOskmJsFm = false;}
      if(RDrPuCdaUA == true){RDrPuCdaUA = false;}
      if(yudDVpWbmp == true){yudDVpWbmp = false;}
      if(efQLLBZuCe == true){efQLLBZuCe = false;}
      if(qlEXHpxftj == true){qlEXHpxftj = false;}
      if(KhmdweAKXt == true){KhmdweAKXt = false;}
      if(PhGPIkmfEt == true){PhGPIkmfEt = false;}
      if(chXoJMpGwe == true){chXoJMpGwe = false;}
      if(sqhCfwslPg == true){sqhCfwslPg = false;}
      if(BOWHOIeoOV == true){BOWHOIeoOV = false;}
      if(CQbAHbKxTi == true){CQbAHbKxTi = false;}
      if(ntOrBYAEiL == true){ntOrBYAEiL = false;}
      if(rAQXsNLPaA == true){rAQXsNLPaA = false;}
      if(hAqaccPhtE == true){hAqaccPhtE = false;}
      if(luSfrGAdGp == true){luSfrGAdGp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CKODPFRZVF
{ 
  void AystqNIbQk()
  { 
      bool jTObgoPrIG = false;
      bool lFbXDmYdZJ = false;
      bool qoASSHsYuI = false;
      bool sMwklQwTXr = false;
      bool ZdnEquAXli = false;
      bool eCGWNtTwIZ = false;
      bool uqwzNZJpll = false;
      bool pEGgiMAuaX = false;
      bool GUlMdpGYXq = false;
      bool xALxxignqQ = false;
      bool kKlArZwYmA = false;
      bool tXUjSZEjVW = false;
      bool TkRuopsIjA = false;
      bool fMEKmwilUD = false;
      bool tgkWxYfadW = false;
      bool dxRTxArqKC = false;
      bool gmomUgTKxW = false;
      bool qSOScmztxQ = false;
      bool KSeMVitjMl = false;
      bool EqaSWGqyCP = false;
      string mYPkTMnYaK;
      string upcKQITdFw;
      string wKyuPjPetw;
      string omDPoAFijp;
      string WDdaexGwCJ;
      string FFSuNbaTVi;
      string wJeeUImMVQ;
      string CjsOZsgXPR;
      string dTbkqjTHCN;
      string YkNBsMXzFW;
      string JsZkGUMEUU;
      string uDEDEcgsnj;
      string oeKIqRVqVN;
      string UhRsHjsqeV;
      string XPmgRVfKwQ;
      string eeKUgeiRto;
      string zUiHANlLuU;
      string ipORMZrcpV;
      string kLuEhpWwLc;
      string BbwpWDgfgE;
      if(mYPkTMnYaK == JsZkGUMEUU){jTObgoPrIG = true;}
      else if(JsZkGUMEUU == mYPkTMnYaK){kKlArZwYmA = true;}
      if(upcKQITdFw == uDEDEcgsnj){lFbXDmYdZJ = true;}
      else if(uDEDEcgsnj == upcKQITdFw){tXUjSZEjVW = true;}
      if(wKyuPjPetw == oeKIqRVqVN){qoASSHsYuI = true;}
      else if(oeKIqRVqVN == wKyuPjPetw){TkRuopsIjA = true;}
      if(omDPoAFijp == UhRsHjsqeV){sMwklQwTXr = true;}
      else if(UhRsHjsqeV == omDPoAFijp){fMEKmwilUD = true;}
      if(WDdaexGwCJ == XPmgRVfKwQ){ZdnEquAXli = true;}
      else if(XPmgRVfKwQ == WDdaexGwCJ){tgkWxYfadW = true;}
      if(FFSuNbaTVi == eeKUgeiRto){eCGWNtTwIZ = true;}
      else if(eeKUgeiRto == FFSuNbaTVi){dxRTxArqKC = true;}
      if(wJeeUImMVQ == zUiHANlLuU){uqwzNZJpll = true;}
      else if(zUiHANlLuU == wJeeUImMVQ){gmomUgTKxW = true;}
      if(CjsOZsgXPR == ipORMZrcpV){pEGgiMAuaX = true;}
      if(dTbkqjTHCN == kLuEhpWwLc){GUlMdpGYXq = true;}
      if(YkNBsMXzFW == BbwpWDgfgE){xALxxignqQ = true;}
      while(ipORMZrcpV == CjsOZsgXPR){qSOScmztxQ = true;}
      while(kLuEhpWwLc == kLuEhpWwLc){KSeMVitjMl = true;}
      while(BbwpWDgfgE == BbwpWDgfgE){EqaSWGqyCP = true;}
      if(jTObgoPrIG == true){jTObgoPrIG = false;}
      if(lFbXDmYdZJ == true){lFbXDmYdZJ = false;}
      if(qoASSHsYuI == true){qoASSHsYuI = false;}
      if(sMwklQwTXr == true){sMwklQwTXr = false;}
      if(ZdnEquAXli == true){ZdnEquAXli = false;}
      if(eCGWNtTwIZ == true){eCGWNtTwIZ = false;}
      if(uqwzNZJpll == true){uqwzNZJpll = false;}
      if(pEGgiMAuaX == true){pEGgiMAuaX = false;}
      if(GUlMdpGYXq == true){GUlMdpGYXq = false;}
      if(xALxxignqQ == true){xALxxignqQ = false;}
      if(kKlArZwYmA == true){kKlArZwYmA = false;}
      if(tXUjSZEjVW == true){tXUjSZEjVW = false;}
      if(TkRuopsIjA == true){TkRuopsIjA = false;}
      if(fMEKmwilUD == true){fMEKmwilUD = false;}
      if(tgkWxYfadW == true){tgkWxYfadW = false;}
      if(dxRTxArqKC == true){dxRTxArqKC = false;}
      if(gmomUgTKxW == true){gmomUgTKxW = false;}
      if(qSOScmztxQ == true){qSOScmztxQ = false;}
      if(KSeMVitjMl == true){KSeMVitjMl = false;}
      if(EqaSWGqyCP == true){EqaSWGqyCP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NOIBSPYOPV
{ 
  void ctBWULMlJH()
  { 
      bool DadOWYwhhL = false;
      bool KRiBowlofu = false;
      bool JEauyizTsz = false;
      bool lwghaQMsSN = false;
      bool ihFyjBZtOH = false;
      bool eTotOzzhQn = false;
      bool YbohZOjAZX = false;
      bool jsVRLbycLw = false;
      bool IFFkTSGmTb = false;
      bool RdbdnHrWYV = false;
      bool RYUpXlxXhl = false;
      bool AWVTeTVEOG = false;
      bool HwfxGFQqcE = false;
      bool ibEpdjjPNh = false;
      bool UiEgbtHHyU = false;
      bool knIROUsWiR = false;
      bool UFtcDXSfpu = false;
      bool jFpflXqzVM = false;
      bool xJsISuTlbJ = false;
      bool qMguNPoadD = false;
      string wBxSCBuADw;
      string SQXhOdkLyD;
      string kKKtEqQoUb;
      string YOusGPOtQo;
      string AIuyqCGWFz;
      string ndreDlpDNK;
      string jGebWDVdaz;
      string OpuJCcPMCC;
      string ktiVntWQpU;
      string YLfGEscSam;
      string fcuGjxiibZ;
      string VdALZpXJmb;
      string gFnFZDKoEI;
      string zwlPVHybkp;
      string LmnQyuLTgO;
      string UTeyFaopfg;
      string mteSaZqjpR;
      string qwXxQtQWGe;
      string rpHpmeQmJt;
      string SIwDDRIUoX;
      if(wBxSCBuADw == fcuGjxiibZ){DadOWYwhhL = true;}
      else if(fcuGjxiibZ == wBxSCBuADw){RYUpXlxXhl = true;}
      if(SQXhOdkLyD == VdALZpXJmb){KRiBowlofu = true;}
      else if(VdALZpXJmb == SQXhOdkLyD){AWVTeTVEOG = true;}
      if(kKKtEqQoUb == gFnFZDKoEI){JEauyizTsz = true;}
      else if(gFnFZDKoEI == kKKtEqQoUb){HwfxGFQqcE = true;}
      if(YOusGPOtQo == zwlPVHybkp){lwghaQMsSN = true;}
      else if(zwlPVHybkp == YOusGPOtQo){ibEpdjjPNh = true;}
      if(AIuyqCGWFz == LmnQyuLTgO){ihFyjBZtOH = true;}
      else if(LmnQyuLTgO == AIuyqCGWFz){UiEgbtHHyU = true;}
      if(ndreDlpDNK == UTeyFaopfg){eTotOzzhQn = true;}
      else if(UTeyFaopfg == ndreDlpDNK){knIROUsWiR = true;}
      if(jGebWDVdaz == mteSaZqjpR){YbohZOjAZX = true;}
      else if(mteSaZqjpR == jGebWDVdaz){UFtcDXSfpu = true;}
      if(OpuJCcPMCC == qwXxQtQWGe){jsVRLbycLw = true;}
      if(ktiVntWQpU == rpHpmeQmJt){IFFkTSGmTb = true;}
      if(YLfGEscSam == SIwDDRIUoX){RdbdnHrWYV = true;}
      while(qwXxQtQWGe == OpuJCcPMCC){jFpflXqzVM = true;}
      while(rpHpmeQmJt == rpHpmeQmJt){xJsISuTlbJ = true;}
      while(SIwDDRIUoX == SIwDDRIUoX){qMguNPoadD = true;}
      if(DadOWYwhhL == true){DadOWYwhhL = false;}
      if(KRiBowlofu == true){KRiBowlofu = false;}
      if(JEauyizTsz == true){JEauyizTsz = false;}
      if(lwghaQMsSN == true){lwghaQMsSN = false;}
      if(ihFyjBZtOH == true){ihFyjBZtOH = false;}
      if(eTotOzzhQn == true){eTotOzzhQn = false;}
      if(YbohZOjAZX == true){YbohZOjAZX = false;}
      if(jsVRLbycLw == true){jsVRLbycLw = false;}
      if(IFFkTSGmTb == true){IFFkTSGmTb = false;}
      if(RdbdnHrWYV == true){RdbdnHrWYV = false;}
      if(RYUpXlxXhl == true){RYUpXlxXhl = false;}
      if(AWVTeTVEOG == true){AWVTeTVEOG = false;}
      if(HwfxGFQqcE == true){HwfxGFQqcE = false;}
      if(ibEpdjjPNh == true){ibEpdjjPNh = false;}
      if(UiEgbtHHyU == true){UiEgbtHHyU = false;}
      if(knIROUsWiR == true){knIROUsWiR = false;}
      if(UFtcDXSfpu == true){UFtcDXSfpu = false;}
      if(jFpflXqzVM == true){jFpflXqzVM = false;}
      if(xJsISuTlbJ == true){xJsISuTlbJ = false;}
      if(qMguNPoadD == true){qMguNPoadD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VOWJJGUGIP
{ 
  void XrrEFeHHXm()
  { 
      bool hGZaWgLkyE = false;
      bool inVKHQoCIG = false;
      bool MXzLKnjUDD = false;
      bool SiZJaPtjzn = false;
      bool ggxibxBdzG = false;
      bool qQeuVJHOQi = false;
      bool xphtlzOLjq = false;
      bool VFDTZfZPiN = false;
      bool lFVwMBEenR = false;
      bool HfTQqpyDwb = false;
      bool hptIjkNLUo = false;
      bool iqeCwqUkhj = false;
      bool ujXRjpkmbi = false;
      bool gWTHewKMLa = false;
      bool nsJyhPAQTA = false;
      bool UNUMgyRbXt = false;
      bool zailHMXXXA = false;
      bool fHYHuBZYjT = false;
      bool oUTbNTBGZf = false;
      bool dioRaNJWqV = false;
      string AoARaKIwJr;
      string qHBnnJmNSi;
      string fQNeRmHhCO;
      string HmwuIbgkIi;
      string QwpjbFwArW;
      string EoOYOjbUAn;
      string DZstjELGfL;
      string bCEjSiZdDL;
      string pGpfKSXXfY;
      string ALkUepCuzX;
      string tpUftCkeGf;
      string JyRnxwjNiR;
      string fnaGLPQiFb;
      string gddeRAkJkI;
      string hsQAOCswXh;
      string GnMhqGONUd;
      string kBYdyeTlWw;
      string LZcajmWarJ;
      string WULWVrRwmL;
      string kWoHWfTmBi;
      if(AoARaKIwJr == tpUftCkeGf){hGZaWgLkyE = true;}
      else if(tpUftCkeGf == AoARaKIwJr){hptIjkNLUo = true;}
      if(qHBnnJmNSi == JyRnxwjNiR){inVKHQoCIG = true;}
      else if(JyRnxwjNiR == qHBnnJmNSi){iqeCwqUkhj = true;}
      if(fQNeRmHhCO == fnaGLPQiFb){MXzLKnjUDD = true;}
      else if(fnaGLPQiFb == fQNeRmHhCO){ujXRjpkmbi = true;}
      if(HmwuIbgkIi == gddeRAkJkI){SiZJaPtjzn = true;}
      else if(gddeRAkJkI == HmwuIbgkIi){gWTHewKMLa = true;}
      if(QwpjbFwArW == hsQAOCswXh){ggxibxBdzG = true;}
      else if(hsQAOCswXh == QwpjbFwArW){nsJyhPAQTA = true;}
      if(EoOYOjbUAn == GnMhqGONUd){qQeuVJHOQi = true;}
      else if(GnMhqGONUd == EoOYOjbUAn){UNUMgyRbXt = true;}
      if(DZstjELGfL == kBYdyeTlWw){xphtlzOLjq = true;}
      else if(kBYdyeTlWw == DZstjELGfL){zailHMXXXA = true;}
      if(bCEjSiZdDL == LZcajmWarJ){VFDTZfZPiN = true;}
      if(pGpfKSXXfY == WULWVrRwmL){lFVwMBEenR = true;}
      if(ALkUepCuzX == kWoHWfTmBi){HfTQqpyDwb = true;}
      while(LZcajmWarJ == bCEjSiZdDL){fHYHuBZYjT = true;}
      while(WULWVrRwmL == WULWVrRwmL){oUTbNTBGZf = true;}
      while(kWoHWfTmBi == kWoHWfTmBi){dioRaNJWqV = true;}
      if(hGZaWgLkyE == true){hGZaWgLkyE = false;}
      if(inVKHQoCIG == true){inVKHQoCIG = false;}
      if(MXzLKnjUDD == true){MXzLKnjUDD = false;}
      if(SiZJaPtjzn == true){SiZJaPtjzn = false;}
      if(ggxibxBdzG == true){ggxibxBdzG = false;}
      if(qQeuVJHOQi == true){qQeuVJHOQi = false;}
      if(xphtlzOLjq == true){xphtlzOLjq = false;}
      if(VFDTZfZPiN == true){VFDTZfZPiN = false;}
      if(lFVwMBEenR == true){lFVwMBEenR = false;}
      if(HfTQqpyDwb == true){HfTQqpyDwb = false;}
      if(hptIjkNLUo == true){hptIjkNLUo = false;}
      if(iqeCwqUkhj == true){iqeCwqUkhj = false;}
      if(ujXRjpkmbi == true){ujXRjpkmbi = false;}
      if(gWTHewKMLa == true){gWTHewKMLa = false;}
      if(nsJyhPAQTA == true){nsJyhPAQTA = false;}
      if(UNUMgyRbXt == true){UNUMgyRbXt = false;}
      if(zailHMXXXA == true){zailHMXXXA = false;}
      if(fHYHuBZYjT == true){fHYHuBZYjT = false;}
      if(oUTbNTBGZf == true){oUTbNTBGZf = false;}
      if(dioRaNJWqV == true){dioRaNJWqV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GBHNGQVQZJ
{ 
  void UkbrYXHGbw()
  { 
      bool MROFGpFTKa = false;
      bool sATfKawWwZ = false;
      bool TrafFtexCs = false;
      bool HcFHhnzQPs = false;
      bool JCzMAQlJqL = false;
      bool UVFXOUqizM = false;
      bool KIQQTQuLyV = false;
      bool beGCQRsNeo = false;
      bool HVFqYkWgsN = false;
      bool xPRChBkisj = false;
      bool VZLUjpPCHx = false;
      bool bcDKEoCZrh = false;
      bool sNSkYLMDUP = false;
      bool fJUuShJkGh = false;
      bool VTZwkULHys = false;
      bool yLqKqIHawX = false;
      bool cMhrQRHIqW = false;
      bool fRTJMYnVzD = false;
      bool zFFbQUSJDJ = false;
      bool ZhnhFJlgeT = false;
      string DesOgfhRjo;
      string dzwpeQQPZc;
      string HXDlPObtax;
      string sgcDcXSgqZ;
      string kOOKJJrlsC;
      string cqXTDfaGyR;
      string EmplwwWsMH;
      string yjYzrsIscF;
      string WoBXUCJJzx;
      string xLhYVxXbON;
      string lzZkErSXaK;
      string XgdsuOkSRt;
      string lNsPKmCAdu;
      string UgeOSXPQTb;
      string ilhoYPgncG;
      string LFJUaYFJaQ;
      string oSsfpqCOZX;
      string zUzpKAeEpt;
      string GNWWiPWJnt;
      string RFoCmQrCyh;
      if(DesOgfhRjo == lzZkErSXaK){MROFGpFTKa = true;}
      else if(lzZkErSXaK == DesOgfhRjo){VZLUjpPCHx = true;}
      if(dzwpeQQPZc == XgdsuOkSRt){sATfKawWwZ = true;}
      else if(XgdsuOkSRt == dzwpeQQPZc){bcDKEoCZrh = true;}
      if(HXDlPObtax == lNsPKmCAdu){TrafFtexCs = true;}
      else if(lNsPKmCAdu == HXDlPObtax){sNSkYLMDUP = true;}
      if(sgcDcXSgqZ == UgeOSXPQTb){HcFHhnzQPs = true;}
      else if(UgeOSXPQTb == sgcDcXSgqZ){fJUuShJkGh = true;}
      if(kOOKJJrlsC == ilhoYPgncG){JCzMAQlJqL = true;}
      else if(ilhoYPgncG == kOOKJJrlsC){VTZwkULHys = true;}
      if(cqXTDfaGyR == LFJUaYFJaQ){UVFXOUqizM = true;}
      else if(LFJUaYFJaQ == cqXTDfaGyR){yLqKqIHawX = true;}
      if(EmplwwWsMH == oSsfpqCOZX){KIQQTQuLyV = true;}
      else if(oSsfpqCOZX == EmplwwWsMH){cMhrQRHIqW = true;}
      if(yjYzrsIscF == zUzpKAeEpt){beGCQRsNeo = true;}
      if(WoBXUCJJzx == GNWWiPWJnt){HVFqYkWgsN = true;}
      if(xLhYVxXbON == RFoCmQrCyh){xPRChBkisj = true;}
      while(zUzpKAeEpt == yjYzrsIscF){fRTJMYnVzD = true;}
      while(GNWWiPWJnt == GNWWiPWJnt){zFFbQUSJDJ = true;}
      while(RFoCmQrCyh == RFoCmQrCyh){ZhnhFJlgeT = true;}
      if(MROFGpFTKa == true){MROFGpFTKa = false;}
      if(sATfKawWwZ == true){sATfKawWwZ = false;}
      if(TrafFtexCs == true){TrafFtexCs = false;}
      if(HcFHhnzQPs == true){HcFHhnzQPs = false;}
      if(JCzMAQlJqL == true){JCzMAQlJqL = false;}
      if(UVFXOUqizM == true){UVFXOUqizM = false;}
      if(KIQQTQuLyV == true){KIQQTQuLyV = false;}
      if(beGCQRsNeo == true){beGCQRsNeo = false;}
      if(HVFqYkWgsN == true){HVFqYkWgsN = false;}
      if(xPRChBkisj == true){xPRChBkisj = false;}
      if(VZLUjpPCHx == true){VZLUjpPCHx = false;}
      if(bcDKEoCZrh == true){bcDKEoCZrh = false;}
      if(sNSkYLMDUP == true){sNSkYLMDUP = false;}
      if(fJUuShJkGh == true){fJUuShJkGh = false;}
      if(VTZwkULHys == true){VTZwkULHys = false;}
      if(yLqKqIHawX == true){yLqKqIHawX = false;}
      if(cMhrQRHIqW == true){cMhrQRHIqW = false;}
      if(fRTJMYnVzD == true){fRTJMYnVzD = false;}
      if(zFFbQUSJDJ == true){zFFbQUSJDJ = false;}
      if(ZhnhFJlgeT == true){ZhnhFJlgeT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PHLUAZINVP
{ 
  void xSFOrzlXyj()
  { 
      bool IOJheWaJHL = false;
      bool HtNaRNSKMb = false;
      bool FSmYKuuNIY = false;
      bool HAVWqpWWVJ = false;
      bool UIBmtjNZZN = false;
      bool kymVIoakWj = false;
      bool bMBiEGYqia = false;
      bool qwnCGwRAda = false;
      bool gVntnINzNB = false;
      bool OlzkhHHRin = false;
      bool KWpyWnJjOM = false;
      bool XaGwDGYGuu = false;
      bool sYcgLEwDTz = false;
      bool nzRpQJeoXz = false;
      bool ycjBdneDhb = false;
      bool hAVmtltIlR = false;
      bool rGPPXXIQfs = false;
      bool ajiwwPnaDX = false;
      bool ZsUrQmceud = false;
      bool PVCFGqMUcF = false;
      string TDopqQoKay;
      string hyOestFVBh;
      string wOChsLThwi;
      string QHSDfFWSlw;
      string tQwVphPVxC;
      string zlUfgFBGxe;
      string wGOrhZfLyn;
      string XmjEmfSgrL;
      string wyjsidmlWZ;
      string EPVGAnCDnP;
      string BDWJeMBQsA;
      string mUOkhxVUID;
      string msoXiHQdEz;
      string cOrbKsaaOW;
      string bVsVmjBjXC;
      string RgujcHOzZW;
      string uXMsXYblao;
      string WuFkbQATkz;
      string FgFBgwSIyC;
      string dbAqbDJzxN;
      if(TDopqQoKay == BDWJeMBQsA){IOJheWaJHL = true;}
      else if(BDWJeMBQsA == TDopqQoKay){KWpyWnJjOM = true;}
      if(hyOestFVBh == mUOkhxVUID){HtNaRNSKMb = true;}
      else if(mUOkhxVUID == hyOestFVBh){XaGwDGYGuu = true;}
      if(wOChsLThwi == msoXiHQdEz){FSmYKuuNIY = true;}
      else if(msoXiHQdEz == wOChsLThwi){sYcgLEwDTz = true;}
      if(QHSDfFWSlw == cOrbKsaaOW){HAVWqpWWVJ = true;}
      else if(cOrbKsaaOW == QHSDfFWSlw){nzRpQJeoXz = true;}
      if(tQwVphPVxC == bVsVmjBjXC){UIBmtjNZZN = true;}
      else if(bVsVmjBjXC == tQwVphPVxC){ycjBdneDhb = true;}
      if(zlUfgFBGxe == RgujcHOzZW){kymVIoakWj = true;}
      else if(RgujcHOzZW == zlUfgFBGxe){hAVmtltIlR = true;}
      if(wGOrhZfLyn == uXMsXYblao){bMBiEGYqia = true;}
      else if(uXMsXYblao == wGOrhZfLyn){rGPPXXIQfs = true;}
      if(XmjEmfSgrL == WuFkbQATkz){qwnCGwRAda = true;}
      if(wyjsidmlWZ == FgFBgwSIyC){gVntnINzNB = true;}
      if(EPVGAnCDnP == dbAqbDJzxN){OlzkhHHRin = true;}
      while(WuFkbQATkz == XmjEmfSgrL){ajiwwPnaDX = true;}
      while(FgFBgwSIyC == FgFBgwSIyC){ZsUrQmceud = true;}
      while(dbAqbDJzxN == dbAqbDJzxN){PVCFGqMUcF = true;}
      if(IOJheWaJHL == true){IOJheWaJHL = false;}
      if(HtNaRNSKMb == true){HtNaRNSKMb = false;}
      if(FSmYKuuNIY == true){FSmYKuuNIY = false;}
      if(HAVWqpWWVJ == true){HAVWqpWWVJ = false;}
      if(UIBmtjNZZN == true){UIBmtjNZZN = false;}
      if(kymVIoakWj == true){kymVIoakWj = false;}
      if(bMBiEGYqia == true){bMBiEGYqia = false;}
      if(qwnCGwRAda == true){qwnCGwRAda = false;}
      if(gVntnINzNB == true){gVntnINzNB = false;}
      if(OlzkhHHRin == true){OlzkhHHRin = false;}
      if(KWpyWnJjOM == true){KWpyWnJjOM = false;}
      if(XaGwDGYGuu == true){XaGwDGYGuu = false;}
      if(sYcgLEwDTz == true){sYcgLEwDTz = false;}
      if(nzRpQJeoXz == true){nzRpQJeoXz = false;}
      if(ycjBdneDhb == true){ycjBdneDhb = false;}
      if(hAVmtltIlR == true){hAVmtltIlR = false;}
      if(rGPPXXIQfs == true){rGPPXXIQfs = false;}
      if(ajiwwPnaDX == true){ajiwwPnaDX = false;}
      if(ZsUrQmceud == true){ZsUrQmceud = false;}
      if(PVCFGqMUcF == true){PVCFGqMUcF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UVBPCTRDAT
{ 
  void ILmxxItCzm()
  { 
      bool adlMAVZFBq = false;
      bool yUmYnuiTZK = false;
      bool dPbkzBWBHy = false;
      bool ROMwUsTuEK = false;
      bool nqtbROFHHD = false;
      bool DduyLKBANz = false;
      bool yYxDZjHqEt = false;
      bool bmOOVlVATj = false;
      bool uOsEumTOjK = false;
      bool qShELPsqBg = false;
      bool GNDMbPOfbY = false;
      bool nBgdDiesHl = false;
      bool QrGsDIFKCG = false;
      bool rezlcgLfbf = false;
      bool YmmLVplEAb = false;
      bool kziOPOGKJT = false;
      bool KEcUfJCtAW = false;
      bool XyRbNdFuWM = false;
      bool WBJZVrujWO = false;
      bool aBWHVTKRfM = false;
      string dBcaAYkokV;
      string KmYWXVPxUf;
      string TKYqiSUXRd;
      string gcnYTJfgmM;
      string sCdpZrwbRz;
      string fGhzdSclrg;
      string EMXHogzzCO;
      string piKImRgiRq;
      string WrFRyZunuB;
      string fsnFHfdWBr;
      string rwZDJwwYMM;
      string ksUAJMGGJO;
      string kKEBhxtEAG;
      string mKhYyaRCIB;
      string dWahPlYnuu;
      string ZXNlGhqYUL;
      string BqYGZaLuBi;
      string tExHkOiVku;
      string XGIFfOxuSQ;
      string jsgwzlxUIo;
      if(dBcaAYkokV == rwZDJwwYMM){adlMAVZFBq = true;}
      else if(rwZDJwwYMM == dBcaAYkokV){GNDMbPOfbY = true;}
      if(KmYWXVPxUf == ksUAJMGGJO){yUmYnuiTZK = true;}
      else if(ksUAJMGGJO == KmYWXVPxUf){nBgdDiesHl = true;}
      if(TKYqiSUXRd == kKEBhxtEAG){dPbkzBWBHy = true;}
      else if(kKEBhxtEAG == TKYqiSUXRd){QrGsDIFKCG = true;}
      if(gcnYTJfgmM == mKhYyaRCIB){ROMwUsTuEK = true;}
      else if(mKhYyaRCIB == gcnYTJfgmM){rezlcgLfbf = true;}
      if(sCdpZrwbRz == dWahPlYnuu){nqtbROFHHD = true;}
      else if(dWahPlYnuu == sCdpZrwbRz){YmmLVplEAb = true;}
      if(fGhzdSclrg == ZXNlGhqYUL){DduyLKBANz = true;}
      else if(ZXNlGhqYUL == fGhzdSclrg){kziOPOGKJT = true;}
      if(EMXHogzzCO == BqYGZaLuBi){yYxDZjHqEt = true;}
      else if(BqYGZaLuBi == EMXHogzzCO){KEcUfJCtAW = true;}
      if(piKImRgiRq == tExHkOiVku){bmOOVlVATj = true;}
      if(WrFRyZunuB == XGIFfOxuSQ){uOsEumTOjK = true;}
      if(fsnFHfdWBr == jsgwzlxUIo){qShELPsqBg = true;}
      while(tExHkOiVku == piKImRgiRq){XyRbNdFuWM = true;}
      while(XGIFfOxuSQ == XGIFfOxuSQ){WBJZVrujWO = true;}
      while(jsgwzlxUIo == jsgwzlxUIo){aBWHVTKRfM = true;}
      if(adlMAVZFBq == true){adlMAVZFBq = false;}
      if(yUmYnuiTZK == true){yUmYnuiTZK = false;}
      if(dPbkzBWBHy == true){dPbkzBWBHy = false;}
      if(ROMwUsTuEK == true){ROMwUsTuEK = false;}
      if(nqtbROFHHD == true){nqtbROFHHD = false;}
      if(DduyLKBANz == true){DduyLKBANz = false;}
      if(yYxDZjHqEt == true){yYxDZjHqEt = false;}
      if(bmOOVlVATj == true){bmOOVlVATj = false;}
      if(uOsEumTOjK == true){uOsEumTOjK = false;}
      if(qShELPsqBg == true){qShELPsqBg = false;}
      if(GNDMbPOfbY == true){GNDMbPOfbY = false;}
      if(nBgdDiesHl == true){nBgdDiesHl = false;}
      if(QrGsDIFKCG == true){QrGsDIFKCG = false;}
      if(rezlcgLfbf == true){rezlcgLfbf = false;}
      if(YmmLVplEAb == true){YmmLVplEAb = false;}
      if(kziOPOGKJT == true){kziOPOGKJT = false;}
      if(KEcUfJCtAW == true){KEcUfJCtAW = false;}
      if(XyRbNdFuWM == true){XyRbNdFuWM = false;}
      if(WBJZVrujWO == true){WBJZVrujWO = false;}
      if(aBWHVTKRfM == true){aBWHVTKRfM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IFOQLQVWED
{ 
  void eXLDgqTNiV()
  { 
      bool baALdRRjBu = false;
      bool rCZzapbkIF = false;
      bool OEzyQfNHxZ = false;
      bool twGYfPeGho = false;
      bool hdQePWZdbs = false;
      bool WOgMoXaBty = false;
      bool DJmbAwuASL = false;
      bool KVCTXkmUit = false;
      bool GjfDCfPtjI = false;
      bool ndLjkXpodS = false;
      bool bYKQiAMNnD = false;
      bool kGRArTdjYU = false;
      bool gAQKWgKRiz = false;
      bool txpPRhZPTC = false;
      bool TBFfWgLLqR = false;
      bool tGQJlaIzsC = false;
      bool pteoJmQBhK = false;
      bool sNPWBeujnp = false;
      bool UyZQFmggcq = false;
      bool ZaWRLYWQWj = false;
      string fGUOXUXLNA;
      string MoTasywVFS;
      string moClIEWrIM;
      string cDOQdTVHKp;
      string RHFPqycIoi;
      string xWjfLqDiFS;
      string xfCBWJaCwY;
      string coKPBfiluK;
      string bOCYOFSiEm;
      string QmBrrlEEsg;
      string WZLQGIMUdf;
      string HQmtqhccmR;
      string qqyIIomSWP;
      string aesOmBClSF;
      string sxEXfzzHBJ;
      string IbQaoebDIQ;
      string VsxOFbWYGp;
      string fqJgYtlZcI;
      string pfRMGzNSZI;
      string YzcCjzzpSD;
      if(fGUOXUXLNA == WZLQGIMUdf){baALdRRjBu = true;}
      else if(WZLQGIMUdf == fGUOXUXLNA){bYKQiAMNnD = true;}
      if(MoTasywVFS == HQmtqhccmR){rCZzapbkIF = true;}
      else if(HQmtqhccmR == MoTasywVFS){kGRArTdjYU = true;}
      if(moClIEWrIM == qqyIIomSWP){OEzyQfNHxZ = true;}
      else if(qqyIIomSWP == moClIEWrIM){gAQKWgKRiz = true;}
      if(cDOQdTVHKp == aesOmBClSF){twGYfPeGho = true;}
      else if(aesOmBClSF == cDOQdTVHKp){txpPRhZPTC = true;}
      if(RHFPqycIoi == sxEXfzzHBJ){hdQePWZdbs = true;}
      else if(sxEXfzzHBJ == RHFPqycIoi){TBFfWgLLqR = true;}
      if(xWjfLqDiFS == IbQaoebDIQ){WOgMoXaBty = true;}
      else if(IbQaoebDIQ == xWjfLqDiFS){tGQJlaIzsC = true;}
      if(xfCBWJaCwY == VsxOFbWYGp){DJmbAwuASL = true;}
      else if(VsxOFbWYGp == xfCBWJaCwY){pteoJmQBhK = true;}
      if(coKPBfiluK == fqJgYtlZcI){KVCTXkmUit = true;}
      if(bOCYOFSiEm == pfRMGzNSZI){GjfDCfPtjI = true;}
      if(QmBrrlEEsg == YzcCjzzpSD){ndLjkXpodS = true;}
      while(fqJgYtlZcI == coKPBfiluK){sNPWBeujnp = true;}
      while(pfRMGzNSZI == pfRMGzNSZI){UyZQFmggcq = true;}
      while(YzcCjzzpSD == YzcCjzzpSD){ZaWRLYWQWj = true;}
      if(baALdRRjBu == true){baALdRRjBu = false;}
      if(rCZzapbkIF == true){rCZzapbkIF = false;}
      if(OEzyQfNHxZ == true){OEzyQfNHxZ = false;}
      if(twGYfPeGho == true){twGYfPeGho = false;}
      if(hdQePWZdbs == true){hdQePWZdbs = false;}
      if(WOgMoXaBty == true){WOgMoXaBty = false;}
      if(DJmbAwuASL == true){DJmbAwuASL = false;}
      if(KVCTXkmUit == true){KVCTXkmUit = false;}
      if(GjfDCfPtjI == true){GjfDCfPtjI = false;}
      if(ndLjkXpodS == true){ndLjkXpodS = false;}
      if(bYKQiAMNnD == true){bYKQiAMNnD = false;}
      if(kGRArTdjYU == true){kGRArTdjYU = false;}
      if(gAQKWgKRiz == true){gAQKWgKRiz = false;}
      if(txpPRhZPTC == true){txpPRhZPTC = false;}
      if(TBFfWgLLqR == true){TBFfWgLLqR = false;}
      if(tGQJlaIzsC == true){tGQJlaIzsC = false;}
      if(pteoJmQBhK == true){pteoJmQBhK = false;}
      if(sNPWBeujnp == true){sNPWBeujnp = false;}
      if(UyZQFmggcq == true){UyZQFmggcq = false;}
      if(ZaWRLYWQWj == true){ZaWRLYWQWj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZDGZKJOPYM
{ 
  void eQCCEomRhr()
  { 
      bool gWGLRdLsut = false;
      bool cXUKAuGcPY = false;
      bool wBlfWnWFPK = false;
      bool RRczBaNccG = false;
      bool JjfPwCtYQY = false;
      bool aWzitejZod = false;
      bool GGdjbLtUJZ = false;
      bool gczIOLVWjU = false;
      bool syopiuRsFW = false;
      bool pnnzADGumk = false;
      bool HZOqryWqUi = false;
      bool JNpTjHRnBg = false;
      bool sBPmirnzIL = false;
      bool EZiyMTixxk = false;
      bool XaYWMcxUPr = false;
      bool lStGqGJbIz = false;
      bool JWhIdidqHP = false;
      bool XTpPIRbsZF = false;
      bool uTjPZlfcGF = false;
      bool JHoybArQrc = false;
      string mEOVecxXGG;
      string JrSoUlNrbN;
      string TBiWnRKxDG;
      string JKFcjXfhDP;
      string UqwHzwlUhW;
      string bkAPblUqgM;
      string RzTzwzmoEw;
      string FfoMrbEbXr;
      string fpPfeYKoBy;
      string DnApxVWxLA;
      string IwQlQuumXz;
      string gsTogbjmTW;
      string nymGrRfzPW;
      string FHPWiiYcPj;
      string dWQCQJTLJU;
      string kicnLKIKsy;
      string PwXBtZcxFx;
      string DGXjsRgkph;
      string xToukVdbKY;
      string ZOjRUhzPIp;
      if(mEOVecxXGG == IwQlQuumXz){gWGLRdLsut = true;}
      else if(IwQlQuumXz == mEOVecxXGG){HZOqryWqUi = true;}
      if(JrSoUlNrbN == gsTogbjmTW){cXUKAuGcPY = true;}
      else if(gsTogbjmTW == JrSoUlNrbN){JNpTjHRnBg = true;}
      if(TBiWnRKxDG == nymGrRfzPW){wBlfWnWFPK = true;}
      else if(nymGrRfzPW == TBiWnRKxDG){sBPmirnzIL = true;}
      if(JKFcjXfhDP == FHPWiiYcPj){RRczBaNccG = true;}
      else if(FHPWiiYcPj == JKFcjXfhDP){EZiyMTixxk = true;}
      if(UqwHzwlUhW == dWQCQJTLJU){JjfPwCtYQY = true;}
      else if(dWQCQJTLJU == UqwHzwlUhW){XaYWMcxUPr = true;}
      if(bkAPblUqgM == kicnLKIKsy){aWzitejZod = true;}
      else if(kicnLKIKsy == bkAPblUqgM){lStGqGJbIz = true;}
      if(RzTzwzmoEw == PwXBtZcxFx){GGdjbLtUJZ = true;}
      else if(PwXBtZcxFx == RzTzwzmoEw){JWhIdidqHP = true;}
      if(FfoMrbEbXr == DGXjsRgkph){gczIOLVWjU = true;}
      if(fpPfeYKoBy == xToukVdbKY){syopiuRsFW = true;}
      if(DnApxVWxLA == ZOjRUhzPIp){pnnzADGumk = true;}
      while(DGXjsRgkph == FfoMrbEbXr){XTpPIRbsZF = true;}
      while(xToukVdbKY == xToukVdbKY){uTjPZlfcGF = true;}
      while(ZOjRUhzPIp == ZOjRUhzPIp){JHoybArQrc = true;}
      if(gWGLRdLsut == true){gWGLRdLsut = false;}
      if(cXUKAuGcPY == true){cXUKAuGcPY = false;}
      if(wBlfWnWFPK == true){wBlfWnWFPK = false;}
      if(RRczBaNccG == true){RRczBaNccG = false;}
      if(JjfPwCtYQY == true){JjfPwCtYQY = false;}
      if(aWzitejZod == true){aWzitejZod = false;}
      if(GGdjbLtUJZ == true){GGdjbLtUJZ = false;}
      if(gczIOLVWjU == true){gczIOLVWjU = false;}
      if(syopiuRsFW == true){syopiuRsFW = false;}
      if(pnnzADGumk == true){pnnzADGumk = false;}
      if(HZOqryWqUi == true){HZOqryWqUi = false;}
      if(JNpTjHRnBg == true){JNpTjHRnBg = false;}
      if(sBPmirnzIL == true){sBPmirnzIL = false;}
      if(EZiyMTixxk == true){EZiyMTixxk = false;}
      if(XaYWMcxUPr == true){XaYWMcxUPr = false;}
      if(lStGqGJbIz == true){lStGqGJbIz = false;}
      if(JWhIdidqHP == true){JWhIdidqHP = false;}
      if(XTpPIRbsZF == true){XTpPIRbsZF = false;}
      if(uTjPZlfcGF == true){uTjPZlfcGF = false;}
      if(JHoybArQrc == true){JHoybArQrc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CREQYMTUSR
{ 
  void kBnTVHZmnL()
  { 
      bool MjaxNyeWpg = false;
      bool yoZRBKigQV = false;
      bool GlwfjNjTTp = false;
      bool yOpjokoTLF = false;
      bool kERkZfnmAi = false;
      bool qdJNfamtNA = false;
      bool NLCzhjzocQ = false;
      bool UOULkCULFD = false;
      bool YxSjzUEbDN = false;
      bool xuGLqZBRCo = false;
      bool gzKjObIycd = false;
      bool GanJbQrSAN = false;
      bool fWlOTYIITK = false;
      bool ACJQWZmiVX = false;
      bool LFyZHVGxia = false;
      bool giRnJJNuQo = false;
      bool SAeRdDRXmC = false;
      bool dJwbCZXMGx = false;
      bool SLZrdRkVGM = false;
      bool LqSgELZgwD = false;
      string dcrOJtVIaW;
      string VINlPAutSK;
      string bLDAIXBFuE;
      string hHNseoMCfX;
      string RLlodUcxDe;
      string OjSFURYrFk;
      string rQMVoOtTGZ;
      string nrOusQZOWn;
      string tDCQpxnIYN;
      string QUxteByPzP;
      string aJqcpVVWMD;
      string rJVRqoNwfr;
      string ZltsJTuUQq;
      string RKPGNkMYZT;
      string aRwUUHyeDp;
      string mCiHonOxTW;
      string aAGUkhtOEF;
      string boWMQIoZXC;
      string UQRZDPaHRY;
      string VOECsZKaim;
      if(dcrOJtVIaW == aJqcpVVWMD){MjaxNyeWpg = true;}
      else if(aJqcpVVWMD == dcrOJtVIaW){gzKjObIycd = true;}
      if(VINlPAutSK == rJVRqoNwfr){yoZRBKigQV = true;}
      else if(rJVRqoNwfr == VINlPAutSK){GanJbQrSAN = true;}
      if(bLDAIXBFuE == ZltsJTuUQq){GlwfjNjTTp = true;}
      else if(ZltsJTuUQq == bLDAIXBFuE){fWlOTYIITK = true;}
      if(hHNseoMCfX == RKPGNkMYZT){yOpjokoTLF = true;}
      else if(RKPGNkMYZT == hHNseoMCfX){ACJQWZmiVX = true;}
      if(RLlodUcxDe == aRwUUHyeDp){kERkZfnmAi = true;}
      else if(aRwUUHyeDp == RLlodUcxDe){LFyZHVGxia = true;}
      if(OjSFURYrFk == mCiHonOxTW){qdJNfamtNA = true;}
      else if(mCiHonOxTW == OjSFURYrFk){giRnJJNuQo = true;}
      if(rQMVoOtTGZ == aAGUkhtOEF){NLCzhjzocQ = true;}
      else if(aAGUkhtOEF == rQMVoOtTGZ){SAeRdDRXmC = true;}
      if(nrOusQZOWn == boWMQIoZXC){UOULkCULFD = true;}
      if(tDCQpxnIYN == UQRZDPaHRY){YxSjzUEbDN = true;}
      if(QUxteByPzP == VOECsZKaim){xuGLqZBRCo = true;}
      while(boWMQIoZXC == nrOusQZOWn){dJwbCZXMGx = true;}
      while(UQRZDPaHRY == UQRZDPaHRY){SLZrdRkVGM = true;}
      while(VOECsZKaim == VOECsZKaim){LqSgELZgwD = true;}
      if(MjaxNyeWpg == true){MjaxNyeWpg = false;}
      if(yoZRBKigQV == true){yoZRBKigQV = false;}
      if(GlwfjNjTTp == true){GlwfjNjTTp = false;}
      if(yOpjokoTLF == true){yOpjokoTLF = false;}
      if(kERkZfnmAi == true){kERkZfnmAi = false;}
      if(qdJNfamtNA == true){qdJNfamtNA = false;}
      if(NLCzhjzocQ == true){NLCzhjzocQ = false;}
      if(UOULkCULFD == true){UOULkCULFD = false;}
      if(YxSjzUEbDN == true){YxSjzUEbDN = false;}
      if(xuGLqZBRCo == true){xuGLqZBRCo = false;}
      if(gzKjObIycd == true){gzKjObIycd = false;}
      if(GanJbQrSAN == true){GanJbQrSAN = false;}
      if(fWlOTYIITK == true){fWlOTYIITK = false;}
      if(ACJQWZmiVX == true){ACJQWZmiVX = false;}
      if(LFyZHVGxia == true){LFyZHVGxia = false;}
      if(giRnJJNuQo == true){giRnJJNuQo = false;}
      if(SAeRdDRXmC == true){SAeRdDRXmC = false;}
      if(dJwbCZXMGx == true){dJwbCZXMGx = false;}
      if(SLZrdRkVGM == true){SLZrdRkVGM = false;}
      if(LqSgELZgwD == true){LqSgELZgwD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IISBJSPYOE
{ 
  void mXRfKBhabQ()
  { 
      bool jWfzJyTpaj = false;
      bool wLNtNDVPCH = false;
      bool lVpxHynSOF = false;
      bool grhGngMGFH = false;
      bool GxdLkyfhaR = false;
      bool mUWTzOgiqL = false;
      bool JAbVCEcGGf = false;
      bool pPJtAnrdMI = false;
      bool SFrwSLVOHY = false;
      bool AdOtxFVHIg = false;
      bool VYbubXLbSK = false;
      bool VCVisDIeDp = false;
      bool iOzgfMAPxt = false;
      bool SjVemsdwUu = false;
      bool AsuxDxHfBs = false;
      bool xpERxGZuOO = false;
      bool WueYrlgquz = false;
      bool ZLKHpoSBdh = false;
      bool EUNDxbeDgg = false;
      bool TihFXEOWEQ = false;
      string MbZAWbRLkP;
      string LgXdHIOQHX;
      string YkRKTJYLOP;
      string bRbPaqGUcw;
      string ejwecOsNQf;
      string woGUXbJPfN;
      string CFwUnsEIDP;
      string CtnKsonmgF;
      string PKuiTmLHqz;
      string gpnPsYnaqj;
      string JkKAcCBubi;
      string mWhaxrKMBA;
      string hwQEiLFYQT;
      string BNuxueAtFR;
      string lPfILKHMSB;
      string OaZpBMTGRR;
      string wbeHgZakfS;
      string rQHiORQIrX;
      string DsGPFZmFuh;
      string KsbnUJkYak;
      if(MbZAWbRLkP == JkKAcCBubi){jWfzJyTpaj = true;}
      else if(JkKAcCBubi == MbZAWbRLkP){VYbubXLbSK = true;}
      if(LgXdHIOQHX == mWhaxrKMBA){wLNtNDVPCH = true;}
      else if(mWhaxrKMBA == LgXdHIOQHX){VCVisDIeDp = true;}
      if(YkRKTJYLOP == hwQEiLFYQT){lVpxHynSOF = true;}
      else if(hwQEiLFYQT == YkRKTJYLOP){iOzgfMAPxt = true;}
      if(bRbPaqGUcw == BNuxueAtFR){grhGngMGFH = true;}
      else if(BNuxueAtFR == bRbPaqGUcw){SjVemsdwUu = true;}
      if(ejwecOsNQf == lPfILKHMSB){GxdLkyfhaR = true;}
      else if(lPfILKHMSB == ejwecOsNQf){AsuxDxHfBs = true;}
      if(woGUXbJPfN == OaZpBMTGRR){mUWTzOgiqL = true;}
      else if(OaZpBMTGRR == woGUXbJPfN){xpERxGZuOO = true;}
      if(CFwUnsEIDP == wbeHgZakfS){JAbVCEcGGf = true;}
      else if(wbeHgZakfS == CFwUnsEIDP){WueYrlgquz = true;}
      if(CtnKsonmgF == rQHiORQIrX){pPJtAnrdMI = true;}
      if(PKuiTmLHqz == DsGPFZmFuh){SFrwSLVOHY = true;}
      if(gpnPsYnaqj == KsbnUJkYak){AdOtxFVHIg = true;}
      while(rQHiORQIrX == CtnKsonmgF){ZLKHpoSBdh = true;}
      while(DsGPFZmFuh == DsGPFZmFuh){EUNDxbeDgg = true;}
      while(KsbnUJkYak == KsbnUJkYak){TihFXEOWEQ = true;}
      if(jWfzJyTpaj == true){jWfzJyTpaj = false;}
      if(wLNtNDVPCH == true){wLNtNDVPCH = false;}
      if(lVpxHynSOF == true){lVpxHynSOF = false;}
      if(grhGngMGFH == true){grhGngMGFH = false;}
      if(GxdLkyfhaR == true){GxdLkyfhaR = false;}
      if(mUWTzOgiqL == true){mUWTzOgiqL = false;}
      if(JAbVCEcGGf == true){JAbVCEcGGf = false;}
      if(pPJtAnrdMI == true){pPJtAnrdMI = false;}
      if(SFrwSLVOHY == true){SFrwSLVOHY = false;}
      if(AdOtxFVHIg == true){AdOtxFVHIg = false;}
      if(VYbubXLbSK == true){VYbubXLbSK = false;}
      if(VCVisDIeDp == true){VCVisDIeDp = false;}
      if(iOzgfMAPxt == true){iOzgfMAPxt = false;}
      if(SjVemsdwUu == true){SjVemsdwUu = false;}
      if(AsuxDxHfBs == true){AsuxDxHfBs = false;}
      if(xpERxGZuOO == true){xpERxGZuOO = false;}
      if(WueYrlgquz == true){WueYrlgquz = false;}
      if(ZLKHpoSBdh == true){ZLKHpoSBdh = false;}
      if(EUNDxbeDgg == true){EUNDxbeDgg = false;}
      if(TihFXEOWEQ == true){TihFXEOWEQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ALZCGRIVUE
{ 
  void BGkbDSnDxU()
  { 
      bool ddRcpwZHIQ = false;
      bool DlZRoyHhgC = false;
      bool xPIcsXHVog = false;
      bool KSqCUCbLhc = false;
      bool xqheoJqqmD = false;
      bool ZaVBuOVniR = false;
      bool oERbFjtXxm = false;
      bool WwzDEFhcnj = false;
      bool fQhkGjxpHF = false;
      bool fnbQnsYGYE = false;
      bool OTtAgdaSwo = false;
      bool frAzlYVfUV = false;
      bool mDPqGiTiOK = false;
      bool fbEiVLWgEb = false;
      bool IetRYnncdP = false;
      bool XskCRKECty = false;
      bool KrDkIEnQdZ = false;
      bool CobsNIJxRS = false;
      bool uqEzmmqBRK = false;
      bool HTmFRPaJJU = false;
      string OUGNWXgkMA;
      string BVObzhpihI;
      string ViTYFSHRDD;
      string bsnnMHAhpX;
      string RDwoZkgRrS;
      string huUjnfAhHE;
      string QPhIYHhZPq;
      string hIrKpRleyU;
      string koZjUfYDAg;
      string HSalGCVmPS;
      string DHCAkZCJtV;
      string sVjmSboxnr;
      string hdZhjPgGDm;
      string uyOfQdlYyu;
      string cOJdmkhmSe;
      string NXzXjYhUQV;
      string ruGGZuGEVo;
      string oQyrOTUuty;
      string gsnXZXyqur;
      string uRIcChICDr;
      if(OUGNWXgkMA == DHCAkZCJtV){ddRcpwZHIQ = true;}
      else if(DHCAkZCJtV == OUGNWXgkMA){OTtAgdaSwo = true;}
      if(BVObzhpihI == sVjmSboxnr){DlZRoyHhgC = true;}
      else if(sVjmSboxnr == BVObzhpihI){frAzlYVfUV = true;}
      if(ViTYFSHRDD == hdZhjPgGDm){xPIcsXHVog = true;}
      else if(hdZhjPgGDm == ViTYFSHRDD){mDPqGiTiOK = true;}
      if(bsnnMHAhpX == uyOfQdlYyu){KSqCUCbLhc = true;}
      else if(uyOfQdlYyu == bsnnMHAhpX){fbEiVLWgEb = true;}
      if(RDwoZkgRrS == cOJdmkhmSe){xqheoJqqmD = true;}
      else if(cOJdmkhmSe == RDwoZkgRrS){IetRYnncdP = true;}
      if(huUjnfAhHE == NXzXjYhUQV){ZaVBuOVniR = true;}
      else if(NXzXjYhUQV == huUjnfAhHE){XskCRKECty = true;}
      if(QPhIYHhZPq == ruGGZuGEVo){oERbFjtXxm = true;}
      else if(ruGGZuGEVo == QPhIYHhZPq){KrDkIEnQdZ = true;}
      if(hIrKpRleyU == oQyrOTUuty){WwzDEFhcnj = true;}
      if(koZjUfYDAg == gsnXZXyqur){fQhkGjxpHF = true;}
      if(HSalGCVmPS == uRIcChICDr){fnbQnsYGYE = true;}
      while(oQyrOTUuty == hIrKpRleyU){CobsNIJxRS = true;}
      while(gsnXZXyqur == gsnXZXyqur){uqEzmmqBRK = true;}
      while(uRIcChICDr == uRIcChICDr){HTmFRPaJJU = true;}
      if(ddRcpwZHIQ == true){ddRcpwZHIQ = false;}
      if(DlZRoyHhgC == true){DlZRoyHhgC = false;}
      if(xPIcsXHVog == true){xPIcsXHVog = false;}
      if(KSqCUCbLhc == true){KSqCUCbLhc = false;}
      if(xqheoJqqmD == true){xqheoJqqmD = false;}
      if(ZaVBuOVniR == true){ZaVBuOVniR = false;}
      if(oERbFjtXxm == true){oERbFjtXxm = false;}
      if(WwzDEFhcnj == true){WwzDEFhcnj = false;}
      if(fQhkGjxpHF == true){fQhkGjxpHF = false;}
      if(fnbQnsYGYE == true){fnbQnsYGYE = false;}
      if(OTtAgdaSwo == true){OTtAgdaSwo = false;}
      if(frAzlYVfUV == true){frAzlYVfUV = false;}
      if(mDPqGiTiOK == true){mDPqGiTiOK = false;}
      if(fbEiVLWgEb == true){fbEiVLWgEb = false;}
      if(IetRYnncdP == true){IetRYnncdP = false;}
      if(XskCRKECty == true){XskCRKECty = false;}
      if(KrDkIEnQdZ == true){KrDkIEnQdZ = false;}
      if(CobsNIJxRS == true){CobsNIJxRS = false;}
      if(uqEzmmqBRK == true){uqEzmmqBRK = false;}
      if(HTmFRPaJJU == true){HTmFRPaJJU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VEXLAFCUQQ
{ 
  void MMGwDnltgx()
  { 
      bool UmEPwlKXGZ = false;
      bool AztAgDOFMp = false;
      bool PacmlIRYuL = false;
      bool HAgSmUlknw = false;
      bool TcfZKhMMIl = false;
      bool egYWcsKRdn = false;
      bool UkbuSzRbNL = false;
      bool RdRPWmuCcD = false;
      bool uEQJgZaKos = false;
      bool KTGzbhAkGK = false;
      bool PkzwUAPJzo = false;
      bool yHnZsPUSNr = false;
      bool XHlTBxWRmo = false;
      bool lJwRnJETof = false;
      bool KRLAtCegGM = false;
      bool MhWOlIyfuW = false;
      bool dxVJCnLWki = false;
      bool KBdhgGukYy = false;
      bool SpLacEmgef = false;
      bool LYYSCMwByG = false;
      string qGyDyfmUFs;
      string hxeHXGnotR;
      string SXUpGDQMmH;
      string WtzxDiUwZF;
      string tyfweDEdox;
      string gOcUqTlIxt;
      string PZhxVnyhEo;
      string krOnWTrYLC;
      string ylWpZIReFj;
      string xMyepUQhZq;
      string FWZAMnznxX;
      string aNxuucCrXN;
      string WTbTrXtjyB;
      string CKyTwbMWdk;
      string IcghIiPDiM;
      string SYJLTltFIn;
      string tPpuUQOcyT;
      string PfNlEtltKI;
      string HpAkidAmAK;
      string gHNopslkMr;
      if(qGyDyfmUFs == FWZAMnznxX){UmEPwlKXGZ = true;}
      else if(FWZAMnznxX == qGyDyfmUFs){PkzwUAPJzo = true;}
      if(hxeHXGnotR == aNxuucCrXN){AztAgDOFMp = true;}
      else if(aNxuucCrXN == hxeHXGnotR){yHnZsPUSNr = true;}
      if(SXUpGDQMmH == WTbTrXtjyB){PacmlIRYuL = true;}
      else if(WTbTrXtjyB == SXUpGDQMmH){XHlTBxWRmo = true;}
      if(WtzxDiUwZF == CKyTwbMWdk){HAgSmUlknw = true;}
      else if(CKyTwbMWdk == WtzxDiUwZF){lJwRnJETof = true;}
      if(tyfweDEdox == IcghIiPDiM){TcfZKhMMIl = true;}
      else if(IcghIiPDiM == tyfweDEdox){KRLAtCegGM = true;}
      if(gOcUqTlIxt == SYJLTltFIn){egYWcsKRdn = true;}
      else if(SYJLTltFIn == gOcUqTlIxt){MhWOlIyfuW = true;}
      if(PZhxVnyhEo == tPpuUQOcyT){UkbuSzRbNL = true;}
      else if(tPpuUQOcyT == PZhxVnyhEo){dxVJCnLWki = true;}
      if(krOnWTrYLC == PfNlEtltKI){RdRPWmuCcD = true;}
      if(ylWpZIReFj == HpAkidAmAK){uEQJgZaKos = true;}
      if(xMyepUQhZq == gHNopslkMr){KTGzbhAkGK = true;}
      while(PfNlEtltKI == krOnWTrYLC){KBdhgGukYy = true;}
      while(HpAkidAmAK == HpAkidAmAK){SpLacEmgef = true;}
      while(gHNopslkMr == gHNopslkMr){LYYSCMwByG = true;}
      if(UmEPwlKXGZ == true){UmEPwlKXGZ = false;}
      if(AztAgDOFMp == true){AztAgDOFMp = false;}
      if(PacmlIRYuL == true){PacmlIRYuL = false;}
      if(HAgSmUlknw == true){HAgSmUlknw = false;}
      if(TcfZKhMMIl == true){TcfZKhMMIl = false;}
      if(egYWcsKRdn == true){egYWcsKRdn = false;}
      if(UkbuSzRbNL == true){UkbuSzRbNL = false;}
      if(RdRPWmuCcD == true){RdRPWmuCcD = false;}
      if(uEQJgZaKos == true){uEQJgZaKos = false;}
      if(KTGzbhAkGK == true){KTGzbhAkGK = false;}
      if(PkzwUAPJzo == true){PkzwUAPJzo = false;}
      if(yHnZsPUSNr == true){yHnZsPUSNr = false;}
      if(XHlTBxWRmo == true){XHlTBxWRmo = false;}
      if(lJwRnJETof == true){lJwRnJETof = false;}
      if(KRLAtCegGM == true){KRLAtCegGM = false;}
      if(MhWOlIyfuW == true){MhWOlIyfuW = false;}
      if(dxVJCnLWki == true){dxVJCnLWki = false;}
      if(KBdhgGukYy == true){KBdhgGukYy = false;}
      if(SpLacEmgef == true){SpLacEmgef = false;}
      if(LYYSCMwByG == true){LYYSCMwByG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPBXWSKWWE
{ 
  void ZoseGIwKFr()
  { 
      bool wEQLDWALKM = false;
      bool sHCLXjPJDG = false;
      bool OLggGgXWDg = false;
      bool XxGOArptMp = false;
      bool MmsJYMVuKz = false;
      bool IduyjjWjEW = false;
      bool zcHcnwBmLe = false;
      bool tUwMsaSWHt = false;
      bool KcMDYtCHeQ = false;
      bool UFpoqjePVc = false;
      bool LijeFmghFI = false;
      bool QzbKLVPEDt = false;
      bool ssHuKneHVJ = false;
      bool uDBdhbshxl = false;
      bool MTCVzUcedU = false;
      bool TaLbiRaoUR = false;
      bool IZLuMNyybi = false;
      bool chGRhZqkuo = false;
      bool KzdApTrZtQ = false;
      bool BDMfdlHGJk = false;
      string yXSnNBpqCV;
      string eFkyXGoJMw;
      string caEbVCYJJA;
      string QrujxQwrOg;
      string fuOUjKHrZi;
      string LJeyVXTpSL;
      string bfhCFlJAAG;
      string KxueQgLirK;
      string ugjanGMxOZ;
      string xFYCFzNMOx;
      string BGqSYONzhn;
      string MjyIPuwHNy;
      string YLlaJEXrZQ;
      string TyUtInoQBZ;
      string sNPZMMHQlJ;
      string DFzQXoTQJT;
      string pUZQUNPDza;
      string FfFmFLwLNx;
      string wGFQNNzDVS;
      string UYHhiXmyFy;
      if(yXSnNBpqCV == BGqSYONzhn){wEQLDWALKM = true;}
      else if(BGqSYONzhn == yXSnNBpqCV){LijeFmghFI = true;}
      if(eFkyXGoJMw == MjyIPuwHNy){sHCLXjPJDG = true;}
      else if(MjyIPuwHNy == eFkyXGoJMw){QzbKLVPEDt = true;}
      if(caEbVCYJJA == YLlaJEXrZQ){OLggGgXWDg = true;}
      else if(YLlaJEXrZQ == caEbVCYJJA){ssHuKneHVJ = true;}
      if(QrujxQwrOg == TyUtInoQBZ){XxGOArptMp = true;}
      else if(TyUtInoQBZ == QrujxQwrOg){uDBdhbshxl = true;}
      if(fuOUjKHrZi == sNPZMMHQlJ){MmsJYMVuKz = true;}
      else if(sNPZMMHQlJ == fuOUjKHrZi){MTCVzUcedU = true;}
      if(LJeyVXTpSL == DFzQXoTQJT){IduyjjWjEW = true;}
      else if(DFzQXoTQJT == LJeyVXTpSL){TaLbiRaoUR = true;}
      if(bfhCFlJAAG == pUZQUNPDza){zcHcnwBmLe = true;}
      else if(pUZQUNPDza == bfhCFlJAAG){IZLuMNyybi = true;}
      if(KxueQgLirK == FfFmFLwLNx){tUwMsaSWHt = true;}
      if(ugjanGMxOZ == wGFQNNzDVS){KcMDYtCHeQ = true;}
      if(xFYCFzNMOx == UYHhiXmyFy){UFpoqjePVc = true;}
      while(FfFmFLwLNx == KxueQgLirK){chGRhZqkuo = true;}
      while(wGFQNNzDVS == wGFQNNzDVS){KzdApTrZtQ = true;}
      while(UYHhiXmyFy == UYHhiXmyFy){BDMfdlHGJk = true;}
      if(wEQLDWALKM == true){wEQLDWALKM = false;}
      if(sHCLXjPJDG == true){sHCLXjPJDG = false;}
      if(OLggGgXWDg == true){OLggGgXWDg = false;}
      if(XxGOArptMp == true){XxGOArptMp = false;}
      if(MmsJYMVuKz == true){MmsJYMVuKz = false;}
      if(IduyjjWjEW == true){IduyjjWjEW = false;}
      if(zcHcnwBmLe == true){zcHcnwBmLe = false;}
      if(tUwMsaSWHt == true){tUwMsaSWHt = false;}
      if(KcMDYtCHeQ == true){KcMDYtCHeQ = false;}
      if(UFpoqjePVc == true){UFpoqjePVc = false;}
      if(LijeFmghFI == true){LijeFmghFI = false;}
      if(QzbKLVPEDt == true){QzbKLVPEDt = false;}
      if(ssHuKneHVJ == true){ssHuKneHVJ = false;}
      if(uDBdhbshxl == true){uDBdhbshxl = false;}
      if(MTCVzUcedU == true){MTCVzUcedU = false;}
      if(TaLbiRaoUR == true){TaLbiRaoUR = false;}
      if(IZLuMNyybi == true){IZLuMNyybi = false;}
      if(chGRhZqkuo == true){chGRhZqkuo = false;}
      if(KzdApTrZtQ == true){KzdApTrZtQ = false;}
      if(BDMfdlHGJk == true){BDMfdlHGJk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZLMEHEFCWQ
{ 
  void kqLuqIKdcF()
  { 
      bool NGApFWLioX = false;
      bool dUIWiYKIhG = false;
      bool ZnFUBDkLPK = false;
      bool PqOubjnTza = false;
      bool dkOorionaZ = false;
      bool KgUmxYBfoB = false;
      bool kzTdHlGMuz = false;
      bool jpJHcnZQbR = false;
      bool OwjpzhVbyC = false;
      bool iIexodRjgF = false;
      bool ccsboUXNKI = false;
      bool zjDWmoPceY = false;
      bool PeNrPaKLRy = false;
      bool VoiWnlDIAd = false;
      bool KHQpCzEIKA = false;
      bool OnFIoyOALN = false;
      bool KLwMmKAghA = false;
      bool kGcAOINXoQ = false;
      bool WBBRihjagp = false;
      bool WCwlTyLEDr = false;
      string pjhmAOHAwY;
      string XixmbOXdgr;
      string hqzxEzFHQO;
      string kocnaIRMlo;
      string nXDgVHlVan;
      string HSOzdykjiB;
      string IAigniGILS;
      string xLqqDKmSbw;
      string MifbHRZdJb;
      string XgdkfmnVrl;
      string BcKHquaXuS;
      string LRHloZUGZW;
      string IcziuQgGKP;
      string WQZpuiYXkL;
      string pChpQFYrwG;
      string SgwVcYdaMa;
      string NUMewtrRqF;
      string BwVNfFtISo;
      string qoKExoUDMV;
      string ExLKyVpDtW;
      if(pjhmAOHAwY == BcKHquaXuS){NGApFWLioX = true;}
      else if(BcKHquaXuS == pjhmAOHAwY){ccsboUXNKI = true;}
      if(XixmbOXdgr == LRHloZUGZW){dUIWiYKIhG = true;}
      else if(LRHloZUGZW == XixmbOXdgr){zjDWmoPceY = true;}
      if(hqzxEzFHQO == IcziuQgGKP){ZnFUBDkLPK = true;}
      else if(IcziuQgGKP == hqzxEzFHQO){PeNrPaKLRy = true;}
      if(kocnaIRMlo == WQZpuiYXkL){PqOubjnTza = true;}
      else if(WQZpuiYXkL == kocnaIRMlo){VoiWnlDIAd = true;}
      if(nXDgVHlVan == pChpQFYrwG){dkOorionaZ = true;}
      else if(pChpQFYrwG == nXDgVHlVan){KHQpCzEIKA = true;}
      if(HSOzdykjiB == SgwVcYdaMa){KgUmxYBfoB = true;}
      else if(SgwVcYdaMa == HSOzdykjiB){OnFIoyOALN = true;}
      if(IAigniGILS == NUMewtrRqF){kzTdHlGMuz = true;}
      else if(NUMewtrRqF == IAigniGILS){KLwMmKAghA = true;}
      if(xLqqDKmSbw == BwVNfFtISo){jpJHcnZQbR = true;}
      if(MifbHRZdJb == qoKExoUDMV){OwjpzhVbyC = true;}
      if(XgdkfmnVrl == ExLKyVpDtW){iIexodRjgF = true;}
      while(BwVNfFtISo == xLqqDKmSbw){kGcAOINXoQ = true;}
      while(qoKExoUDMV == qoKExoUDMV){WBBRihjagp = true;}
      while(ExLKyVpDtW == ExLKyVpDtW){WCwlTyLEDr = true;}
      if(NGApFWLioX == true){NGApFWLioX = false;}
      if(dUIWiYKIhG == true){dUIWiYKIhG = false;}
      if(ZnFUBDkLPK == true){ZnFUBDkLPK = false;}
      if(PqOubjnTza == true){PqOubjnTza = false;}
      if(dkOorionaZ == true){dkOorionaZ = false;}
      if(KgUmxYBfoB == true){KgUmxYBfoB = false;}
      if(kzTdHlGMuz == true){kzTdHlGMuz = false;}
      if(jpJHcnZQbR == true){jpJHcnZQbR = false;}
      if(OwjpzhVbyC == true){OwjpzhVbyC = false;}
      if(iIexodRjgF == true){iIexodRjgF = false;}
      if(ccsboUXNKI == true){ccsboUXNKI = false;}
      if(zjDWmoPceY == true){zjDWmoPceY = false;}
      if(PeNrPaKLRy == true){PeNrPaKLRy = false;}
      if(VoiWnlDIAd == true){VoiWnlDIAd = false;}
      if(KHQpCzEIKA == true){KHQpCzEIKA = false;}
      if(OnFIoyOALN == true){OnFIoyOALN = false;}
      if(KLwMmKAghA == true){KLwMmKAghA = false;}
      if(kGcAOINXoQ == true){kGcAOINXoQ = false;}
      if(WBBRihjagp == true){WBBRihjagp = false;}
      if(WCwlTyLEDr == true){WCwlTyLEDr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KQBIFVFXVZ
{ 
  void qeepAurrGT()
  { 
      bool HzunIWCusN = false;
      bool cyVWlTeLdE = false;
      bool nZQDKhTePL = false;
      bool NheNaUcaxb = false;
      bool jTXlsJPPhA = false;
      bool rZcGeghqca = false;
      bool CWegztSIwQ = false;
      bool qENCUUCdJB = false;
      bool REwOTnFYht = false;
      bool lkxWYMnply = false;
      bool pHTQJnLZkK = false;
      bool dEgbIyaQNL = false;
      bool osZCeGGqdI = false;
      bool gMqLKKjeFe = false;
      bool bemXPhDUOZ = false;
      bool lWbaIxgRlD = false;
      bool gUwcdRMVRy = false;
      bool NuLhiJFClw = false;
      bool ClcDWJjQCN = false;
      bool cSrByHhKsx = false;
      string QoGQkgLgyS;
      string nRILFcpDST;
      string pwhAcqZfmE;
      string kfEfnpzSOt;
      string KXXLXBLcBU;
      string HEZPyUHGmt;
      string GetthIMbWP;
      string dWoXISXWca;
      string eweSwgFohT;
      string iseUnedccP;
      string niGlpjOCGe;
      string xjdLOKAbxA;
      string CXtDfjqUjd;
      string ntsMmwprbM;
      string RDiCVyPTFc;
      string eCfbMQoDFG;
      string rtRcqCqQYR;
      string UHAjiznqgh;
      string TXOGylOQAV;
      string HlmUUXkGLT;
      if(QoGQkgLgyS == niGlpjOCGe){HzunIWCusN = true;}
      else if(niGlpjOCGe == QoGQkgLgyS){pHTQJnLZkK = true;}
      if(nRILFcpDST == xjdLOKAbxA){cyVWlTeLdE = true;}
      else if(xjdLOKAbxA == nRILFcpDST){dEgbIyaQNL = true;}
      if(pwhAcqZfmE == CXtDfjqUjd){nZQDKhTePL = true;}
      else if(CXtDfjqUjd == pwhAcqZfmE){osZCeGGqdI = true;}
      if(kfEfnpzSOt == ntsMmwprbM){NheNaUcaxb = true;}
      else if(ntsMmwprbM == kfEfnpzSOt){gMqLKKjeFe = true;}
      if(KXXLXBLcBU == RDiCVyPTFc){jTXlsJPPhA = true;}
      else if(RDiCVyPTFc == KXXLXBLcBU){bemXPhDUOZ = true;}
      if(HEZPyUHGmt == eCfbMQoDFG){rZcGeghqca = true;}
      else if(eCfbMQoDFG == HEZPyUHGmt){lWbaIxgRlD = true;}
      if(GetthIMbWP == rtRcqCqQYR){CWegztSIwQ = true;}
      else if(rtRcqCqQYR == GetthIMbWP){gUwcdRMVRy = true;}
      if(dWoXISXWca == UHAjiznqgh){qENCUUCdJB = true;}
      if(eweSwgFohT == TXOGylOQAV){REwOTnFYht = true;}
      if(iseUnedccP == HlmUUXkGLT){lkxWYMnply = true;}
      while(UHAjiznqgh == dWoXISXWca){NuLhiJFClw = true;}
      while(TXOGylOQAV == TXOGylOQAV){ClcDWJjQCN = true;}
      while(HlmUUXkGLT == HlmUUXkGLT){cSrByHhKsx = true;}
      if(HzunIWCusN == true){HzunIWCusN = false;}
      if(cyVWlTeLdE == true){cyVWlTeLdE = false;}
      if(nZQDKhTePL == true){nZQDKhTePL = false;}
      if(NheNaUcaxb == true){NheNaUcaxb = false;}
      if(jTXlsJPPhA == true){jTXlsJPPhA = false;}
      if(rZcGeghqca == true){rZcGeghqca = false;}
      if(CWegztSIwQ == true){CWegztSIwQ = false;}
      if(qENCUUCdJB == true){qENCUUCdJB = false;}
      if(REwOTnFYht == true){REwOTnFYht = false;}
      if(lkxWYMnply == true){lkxWYMnply = false;}
      if(pHTQJnLZkK == true){pHTQJnLZkK = false;}
      if(dEgbIyaQNL == true){dEgbIyaQNL = false;}
      if(osZCeGGqdI == true){osZCeGGqdI = false;}
      if(gMqLKKjeFe == true){gMqLKKjeFe = false;}
      if(bemXPhDUOZ == true){bemXPhDUOZ = false;}
      if(lWbaIxgRlD == true){lWbaIxgRlD = false;}
      if(gUwcdRMVRy == true){gUwcdRMVRy = false;}
      if(NuLhiJFClw == true){NuLhiJFClw = false;}
      if(ClcDWJjQCN == true){ClcDWJjQCN = false;}
      if(cSrByHhKsx == true){cSrByHhKsx = false;}
    } 
}; 
