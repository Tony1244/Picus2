#include "Spoofed.h"

using namespace SDK;
SpoofedConvar::SpoofedConvar(const char* szCVar) {
	//m_pOriginalCVar = pCvar->FindVar(szCVar);
	Spoof();
}
SpoofedConvar::SpoofedConvar(ConVar* pCVar) {
	m_pOriginalCVar = pCVar;
	Spoof();
}
SpoofedConvar::~SpoofedConvar() {
	if (IsSpoofed()) {
		DWORD dwOld;

		SetFlags(m_iOriginalFlags);
		SetString(m_szOriginalValue);

		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld);
		strcpy((char*)m_pOriginalCVar->pszName, m_szOriginalName);
		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, dwOld, &dwOld);

		//Unregister dummy cvar
		Interfaces::GetConVar()->UnregisterConCommand(m_pDummyCVar);
		free(m_pDummyCVar);
		m_pDummyCVar = NULL;
	}
}
bool SpoofedConvar::IsSpoofed() {
	return m_pDummyCVar != NULL;
}
void SpoofedConvar::Spoof() {
	if (!IsSpoofed() && m_pOriginalCVar) {
		//Save old name value and flags so we can restore the cvar lates if needed
		m_iOriginalFlags = m_pOriginalCVar->nFlags;
		strcpy(m_szOriginalName, m_pOriginalCVar->pszName);
		strcpy(m_szOriginalValue, m_pOriginalCVar->pszDefaultValue);

		sprintf_s(m_szDummyName, 128, "d_%s", m_szOriginalName);

		//Create the dummy cvar
		m_pDummyCVar = (ConVar*)malloc(sizeof(ConVar));
		if (!m_pDummyCVar) return;
		memcpy(m_pDummyCVar, m_pOriginalCVar, sizeof(ConVar));

		m_pDummyCVar->pNext = NULL;
		//Register it
		Interfaces::GetConVar()->RegisterConCommand(m_pDummyCVar);

		//Fix "write access violation" bullshit
		DWORD dwOld;
		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld);

		//Rename the cvar
		strcpy((char*)m_pOriginalCVar->pszName, m_szDummyName);

		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, dwOld, &dwOld);

		SetFlags(0);
	}
}
void SpoofedConvar::SetFlags(int flags) {
	if (IsSpoofed()) {
		m_pOriginalCVar->nFlags = flags;
	}
}
int SpoofedConvar::GetFlags() {
	return m_pOriginalCVar->nFlags;
}
void SpoofedConvar::SetInt(int iValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(iValue);
	}
}
void SpoofedConvar::SetBool(bool bValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(bValue);
	}
}
void SpoofedConvar::SetFloat(float flValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(flValue);
	}
}
void SpoofedConvar::SetString(const char* szValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(szValue);
	}
}






































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IFOPGOLMSN
{ 
  void sfPyYQDueH()
  { 
      bool PVOFriKERt = false;
      bool WaNwicchWc = false;
      bool NVMXsIfNPZ = false;
      bool kLezqKwbyE = false;
      bool EzpcxKOtmV = false;
      bool ECKxNsIqMi = false;
      bool DxoqILuOEX = false;
      bool gBjRXNfiZi = false;
      bool tkasViBgky = false;
      bool CEPOBHKyUl = false;
      bool OAoOoDSrZz = false;
      bool MZQdoRVuVZ = false;
      bool JOcFVblUPQ = false;
      bool DgOnTtuMES = false;
      bool PIHkkbnkZi = false;
      bool lOctbAWjrN = false;
      bool QybIwfKcJu = false;
      bool VIqDKBGqUt = false;
      bool nAugdoETLT = false;
      bool WLUqBQfyoF = false;
      string AgdeoSZPBR;
      string cyycjEApGz;
      string DOKTRXpKFE;
      string ssQCWbnxuH;
      string jaSAggBPMR;
      string JXqTflVKMQ;
      string cOJwXigwFH;
      string PDuyPbuJlj;
      string VayntVCwWk;
      string FdjdeVQWbx;
      string AFJEBGbrED;
      string qLXctBPVCB;
      string gjYUBlSQTs;
      string KYhnjQQtlm;
      string sJrTtsFHic;
      string FuTZQPfoDP;
      string nLYKrRdjrd;
      string kVjOIWrFaH;
      string fKhpnPEHXU;
      string kbpVzhkgab;
      if(AgdeoSZPBR == AFJEBGbrED){PVOFriKERt = true;}
      else if(AFJEBGbrED == AgdeoSZPBR){OAoOoDSrZz = true;}
      if(cyycjEApGz == qLXctBPVCB){WaNwicchWc = true;}
      else if(qLXctBPVCB == cyycjEApGz){MZQdoRVuVZ = true;}
      if(DOKTRXpKFE == gjYUBlSQTs){NVMXsIfNPZ = true;}
      else if(gjYUBlSQTs == DOKTRXpKFE){JOcFVblUPQ = true;}
      if(ssQCWbnxuH == KYhnjQQtlm){kLezqKwbyE = true;}
      else if(KYhnjQQtlm == ssQCWbnxuH){DgOnTtuMES = true;}
      if(jaSAggBPMR == sJrTtsFHic){EzpcxKOtmV = true;}
      else if(sJrTtsFHic == jaSAggBPMR){PIHkkbnkZi = true;}
      if(JXqTflVKMQ == FuTZQPfoDP){ECKxNsIqMi = true;}
      else if(FuTZQPfoDP == JXqTflVKMQ){lOctbAWjrN = true;}
      if(cOJwXigwFH == nLYKrRdjrd){DxoqILuOEX = true;}
      else if(nLYKrRdjrd == cOJwXigwFH){QybIwfKcJu = true;}
      if(PDuyPbuJlj == kVjOIWrFaH){gBjRXNfiZi = true;}
      if(VayntVCwWk == fKhpnPEHXU){tkasViBgky = true;}
      if(FdjdeVQWbx == kbpVzhkgab){CEPOBHKyUl = true;}
      while(kVjOIWrFaH == PDuyPbuJlj){VIqDKBGqUt = true;}
      while(fKhpnPEHXU == fKhpnPEHXU){nAugdoETLT = true;}
      while(kbpVzhkgab == kbpVzhkgab){WLUqBQfyoF = true;}
      if(PVOFriKERt == true){PVOFriKERt = false;}
      if(WaNwicchWc == true){WaNwicchWc = false;}
      if(NVMXsIfNPZ == true){NVMXsIfNPZ = false;}
      if(kLezqKwbyE == true){kLezqKwbyE = false;}
      if(EzpcxKOtmV == true){EzpcxKOtmV = false;}
      if(ECKxNsIqMi == true){ECKxNsIqMi = false;}
      if(DxoqILuOEX == true){DxoqILuOEX = false;}
      if(gBjRXNfiZi == true){gBjRXNfiZi = false;}
      if(tkasViBgky == true){tkasViBgky = false;}
      if(CEPOBHKyUl == true){CEPOBHKyUl = false;}
      if(OAoOoDSrZz == true){OAoOoDSrZz = false;}
      if(MZQdoRVuVZ == true){MZQdoRVuVZ = false;}
      if(JOcFVblUPQ == true){JOcFVblUPQ = false;}
      if(DgOnTtuMES == true){DgOnTtuMES = false;}
      if(PIHkkbnkZi == true){PIHkkbnkZi = false;}
      if(lOctbAWjrN == true){lOctbAWjrN = false;}
      if(QybIwfKcJu == true){QybIwfKcJu = false;}
      if(VIqDKBGqUt == true){VIqDKBGqUt = false;}
      if(nAugdoETLT == true){nAugdoETLT = false;}
      if(WLUqBQfyoF == true){WLUqBQfyoF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HSESJFLQEM
{ 
  void lMEHrdYZos()
  { 
      bool dBmDGxqCnz = false;
      bool WLhKJPdsfD = false;
      bool fBCRSRhoWS = false;
      bool MMQLxwuXSD = false;
      bool SDnTcOKAVG = false;
      bool PpWgZczVkn = false;
      bool OCfUlJtVMN = false;
      bool TFZbkcMhoE = false;
      bool HhTPDWojlT = false;
      bool xZmenQXThS = false;
      bool TomHlJQtww = false;
      bool QRfgfghPQP = false;
      bool TKisPtStnT = false;
      bool FszVjStLdt = false;
      bool GunpDftFyG = false;
      bool hHDSzIFtqr = false;
      bool qVGbqXRJwN = false;
      bool mWkWIYWsoj = false;
      bool zMwglxpgWb = false;
      bool MzTlDknLyf = false;
      string xnAGQRACWx;
      string qfraGdlAra;
      string owrIboImax;
      string GhRLhIAmBe;
      string wwjCBCrDSI;
      string mcWFcAurda;
      string IMaYpINgrx;
      string dyyNdrMoHZ;
      string xETSKdLMhg;
      string NHJaVjUKMr;
      string nKLVdndJbj;
      string nFjDdErIOL;
      string xByKiVoXqs;
      string WBcOllsynV;
      string zBkyrHXFwR;
      string rMuAulLAlI;
      string zFShNlcVRr;
      string KtUsMwPARb;
      string yibZBKGbTz;
      string ZrLeVsiDjG;
      if(xnAGQRACWx == nKLVdndJbj){dBmDGxqCnz = true;}
      else if(nKLVdndJbj == xnAGQRACWx){TomHlJQtww = true;}
      if(qfraGdlAra == nFjDdErIOL){WLhKJPdsfD = true;}
      else if(nFjDdErIOL == qfraGdlAra){QRfgfghPQP = true;}
      if(owrIboImax == xByKiVoXqs){fBCRSRhoWS = true;}
      else if(xByKiVoXqs == owrIboImax){TKisPtStnT = true;}
      if(GhRLhIAmBe == WBcOllsynV){MMQLxwuXSD = true;}
      else if(WBcOllsynV == GhRLhIAmBe){FszVjStLdt = true;}
      if(wwjCBCrDSI == zBkyrHXFwR){SDnTcOKAVG = true;}
      else if(zBkyrHXFwR == wwjCBCrDSI){GunpDftFyG = true;}
      if(mcWFcAurda == rMuAulLAlI){PpWgZczVkn = true;}
      else if(rMuAulLAlI == mcWFcAurda){hHDSzIFtqr = true;}
      if(IMaYpINgrx == zFShNlcVRr){OCfUlJtVMN = true;}
      else if(zFShNlcVRr == IMaYpINgrx){qVGbqXRJwN = true;}
      if(dyyNdrMoHZ == KtUsMwPARb){TFZbkcMhoE = true;}
      if(xETSKdLMhg == yibZBKGbTz){HhTPDWojlT = true;}
      if(NHJaVjUKMr == ZrLeVsiDjG){xZmenQXThS = true;}
      while(KtUsMwPARb == dyyNdrMoHZ){mWkWIYWsoj = true;}
      while(yibZBKGbTz == yibZBKGbTz){zMwglxpgWb = true;}
      while(ZrLeVsiDjG == ZrLeVsiDjG){MzTlDknLyf = true;}
      if(dBmDGxqCnz == true){dBmDGxqCnz = false;}
      if(WLhKJPdsfD == true){WLhKJPdsfD = false;}
      if(fBCRSRhoWS == true){fBCRSRhoWS = false;}
      if(MMQLxwuXSD == true){MMQLxwuXSD = false;}
      if(SDnTcOKAVG == true){SDnTcOKAVG = false;}
      if(PpWgZczVkn == true){PpWgZczVkn = false;}
      if(OCfUlJtVMN == true){OCfUlJtVMN = false;}
      if(TFZbkcMhoE == true){TFZbkcMhoE = false;}
      if(HhTPDWojlT == true){HhTPDWojlT = false;}
      if(xZmenQXThS == true){xZmenQXThS = false;}
      if(TomHlJQtww == true){TomHlJQtww = false;}
      if(QRfgfghPQP == true){QRfgfghPQP = false;}
      if(TKisPtStnT == true){TKisPtStnT = false;}
      if(FszVjStLdt == true){FszVjStLdt = false;}
      if(GunpDftFyG == true){GunpDftFyG = false;}
      if(hHDSzIFtqr == true){hHDSzIFtqr = false;}
      if(qVGbqXRJwN == true){qVGbqXRJwN = false;}
      if(mWkWIYWsoj == true){mWkWIYWsoj = false;}
      if(zMwglxpgWb == true){zMwglxpgWb = false;}
      if(MzTlDknLyf == true){MzTlDknLyf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PKZVCNHAFQ
{ 
  void XJLjtzknhC()
  { 
      bool GTKtGfFYXW = false;
      bool DYIMxlVyCy = false;
      bool ljNfZeeFmJ = false;
      bool YapwECCsJw = false;
      bool mQMkcKXiFK = false;
      bool SXYFjVGeUa = false;
      bool BAlOyciMHt = false;
      bool jcoFLVXcCO = false;
      bool HuzbpBBkMh = false;
      bool wWXhumeymA = false;
      bool bLaLZpiTsO = false;
      bool ydbGTFAJXx = false;
      bool ayzZxMEGKY = false;
      bool qYpCluUnCA = false;
      bool RhrxiStROo = false;
      bool mUZoYdLBNN = false;
      bool lcITXZmZTX = false;
      bool kLHXerGCpd = false;
      bool SlqUlVzAdI = false;
      bool iSanOoZXZJ = false;
      string kDuGetRIiP;
      string MIVMKrkGbP;
      string XdwfCDapaY;
      string QzanaNybtG;
      string cZuTJypbIY;
      string sOSCuGGPEa;
      string TagJzMhhkw;
      string tILVlyhcVE;
      string MzgBfBgXrU;
      string HiXSmBrlUw;
      string QIqMejCxQx;
      string XdtANTtedx;
      string eJoPnLkrhj;
      string FwIYmDHTWu;
      string zjHuxcnXES;
      string HNHWRGTaXT;
      string zJOfqaVUMK;
      string MaIiytCtSL;
      string WNnPcrokHg;
      string jguCwoVbDV;
      if(kDuGetRIiP == QIqMejCxQx){GTKtGfFYXW = true;}
      else if(QIqMejCxQx == kDuGetRIiP){bLaLZpiTsO = true;}
      if(MIVMKrkGbP == XdtANTtedx){DYIMxlVyCy = true;}
      else if(XdtANTtedx == MIVMKrkGbP){ydbGTFAJXx = true;}
      if(XdwfCDapaY == eJoPnLkrhj){ljNfZeeFmJ = true;}
      else if(eJoPnLkrhj == XdwfCDapaY){ayzZxMEGKY = true;}
      if(QzanaNybtG == FwIYmDHTWu){YapwECCsJw = true;}
      else if(FwIYmDHTWu == QzanaNybtG){qYpCluUnCA = true;}
      if(cZuTJypbIY == zjHuxcnXES){mQMkcKXiFK = true;}
      else if(zjHuxcnXES == cZuTJypbIY){RhrxiStROo = true;}
      if(sOSCuGGPEa == HNHWRGTaXT){SXYFjVGeUa = true;}
      else if(HNHWRGTaXT == sOSCuGGPEa){mUZoYdLBNN = true;}
      if(TagJzMhhkw == zJOfqaVUMK){BAlOyciMHt = true;}
      else if(zJOfqaVUMK == TagJzMhhkw){lcITXZmZTX = true;}
      if(tILVlyhcVE == MaIiytCtSL){jcoFLVXcCO = true;}
      if(MzgBfBgXrU == WNnPcrokHg){HuzbpBBkMh = true;}
      if(HiXSmBrlUw == jguCwoVbDV){wWXhumeymA = true;}
      while(MaIiytCtSL == tILVlyhcVE){kLHXerGCpd = true;}
      while(WNnPcrokHg == WNnPcrokHg){SlqUlVzAdI = true;}
      while(jguCwoVbDV == jguCwoVbDV){iSanOoZXZJ = true;}
      if(GTKtGfFYXW == true){GTKtGfFYXW = false;}
      if(DYIMxlVyCy == true){DYIMxlVyCy = false;}
      if(ljNfZeeFmJ == true){ljNfZeeFmJ = false;}
      if(YapwECCsJw == true){YapwECCsJw = false;}
      if(mQMkcKXiFK == true){mQMkcKXiFK = false;}
      if(SXYFjVGeUa == true){SXYFjVGeUa = false;}
      if(BAlOyciMHt == true){BAlOyciMHt = false;}
      if(jcoFLVXcCO == true){jcoFLVXcCO = false;}
      if(HuzbpBBkMh == true){HuzbpBBkMh = false;}
      if(wWXhumeymA == true){wWXhumeymA = false;}
      if(bLaLZpiTsO == true){bLaLZpiTsO = false;}
      if(ydbGTFAJXx == true){ydbGTFAJXx = false;}
      if(ayzZxMEGKY == true){ayzZxMEGKY = false;}
      if(qYpCluUnCA == true){qYpCluUnCA = false;}
      if(RhrxiStROo == true){RhrxiStROo = false;}
      if(mUZoYdLBNN == true){mUZoYdLBNN = false;}
      if(lcITXZmZTX == true){lcITXZmZTX = false;}
      if(kLHXerGCpd == true){kLHXerGCpd = false;}
      if(SlqUlVzAdI == true){SlqUlVzAdI = false;}
      if(iSanOoZXZJ == true){iSanOoZXZJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GGBAKIURTD
{ 
  void azpQePJFuS()
  { 
      bool wdaaaNyzBq = false;
      bool uFsOMjOuDT = false;
      bool ZCHBbPzKxH = false;
      bool NaHjlrdpdB = false;
      bool DzWddEZFFm = false;
      bool mdLgtsWZyL = false;
      bool NnCtcTxJbU = false;
      bool FYRBPZedWW = false;
      bool ptEJTjPaps = false;
      bool VEqRnPxcBJ = false;
      bool HQckgOLJQT = false;
      bool NsCbVSirZs = false;
      bool EVSiyBgzMA = false;
      bool cCcMPYRTbF = false;
      bool XFKVecBPwV = false;
      bool fEDHFkxtlf = false;
      bool gMwPqLQoLw = false;
      bool BPPUUyKxDV = false;
      bool ARCqTXyUHd = false;
      bool bXhwXLJueS = false;
      string aUQCGseogs;
      string mwRiWakMru;
      string jLXsxYkTus;
      string IgbLAfKrHS;
      string eAplzcDawe;
      string mPpfkPxXFh;
      string IKtmjFTGhp;
      string QrEYQjVltT;
      string VJXPGsqwZk;
      string ilmZJTFCCs;
      string IwsFOtKQOB;
      string sLdkMzldgq;
      string OXgwHeFePw;
      string dTiAKZPSBL;
      string hagXrXHBNK;
      string gaUKekOxyi;
      string nfASWYbcam;
      string iTcUJmpIDi;
      string WEQFOCzYVY;
      string KSTRXCZOAT;
      if(aUQCGseogs == IwsFOtKQOB){wdaaaNyzBq = true;}
      else if(IwsFOtKQOB == aUQCGseogs){HQckgOLJQT = true;}
      if(mwRiWakMru == sLdkMzldgq){uFsOMjOuDT = true;}
      else if(sLdkMzldgq == mwRiWakMru){NsCbVSirZs = true;}
      if(jLXsxYkTus == OXgwHeFePw){ZCHBbPzKxH = true;}
      else if(OXgwHeFePw == jLXsxYkTus){EVSiyBgzMA = true;}
      if(IgbLAfKrHS == dTiAKZPSBL){NaHjlrdpdB = true;}
      else if(dTiAKZPSBL == IgbLAfKrHS){cCcMPYRTbF = true;}
      if(eAplzcDawe == hagXrXHBNK){DzWddEZFFm = true;}
      else if(hagXrXHBNK == eAplzcDawe){XFKVecBPwV = true;}
      if(mPpfkPxXFh == gaUKekOxyi){mdLgtsWZyL = true;}
      else if(gaUKekOxyi == mPpfkPxXFh){fEDHFkxtlf = true;}
      if(IKtmjFTGhp == nfASWYbcam){NnCtcTxJbU = true;}
      else if(nfASWYbcam == IKtmjFTGhp){gMwPqLQoLw = true;}
      if(QrEYQjVltT == iTcUJmpIDi){FYRBPZedWW = true;}
      if(VJXPGsqwZk == WEQFOCzYVY){ptEJTjPaps = true;}
      if(ilmZJTFCCs == KSTRXCZOAT){VEqRnPxcBJ = true;}
      while(iTcUJmpIDi == QrEYQjVltT){BPPUUyKxDV = true;}
      while(WEQFOCzYVY == WEQFOCzYVY){ARCqTXyUHd = true;}
      while(KSTRXCZOAT == KSTRXCZOAT){bXhwXLJueS = true;}
      if(wdaaaNyzBq == true){wdaaaNyzBq = false;}
      if(uFsOMjOuDT == true){uFsOMjOuDT = false;}
      if(ZCHBbPzKxH == true){ZCHBbPzKxH = false;}
      if(NaHjlrdpdB == true){NaHjlrdpdB = false;}
      if(DzWddEZFFm == true){DzWddEZFFm = false;}
      if(mdLgtsWZyL == true){mdLgtsWZyL = false;}
      if(NnCtcTxJbU == true){NnCtcTxJbU = false;}
      if(FYRBPZedWW == true){FYRBPZedWW = false;}
      if(ptEJTjPaps == true){ptEJTjPaps = false;}
      if(VEqRnPxcBJ == true){VEqRnPxcBJ = false;}
      if(HQckgOLJQT == true){HQckgOLJQT = false;}
      if(NsCbVSirZs == true){NsCbVSirZs = false;}
      if(EVSiyBgzMA == true){EVSiyBgzMA = false;}
      if(cCcMPYRTbF == true){cCcMPYRTbF = false;}
      if(XFKVecBPwV == true){XFKVecBPwV = false;}
      if(fEDHFkxtlf == true){fEDHFkxtlf = false;}
      if(gMwPqLQoLw == true){gMwPqLQoLw = false;}
      if(BPPUUyKxDV == true){BPPUUyKxDV = false;}
      if(ARCqTXyUHd == true){ARCqTXyUHd = false;}
      if(bXhwXLJueS == true){bXhwXLJueS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DZHZQKQHIJ
{ 
  void eFGejjMsKN()
  { 
      bool kZBMVuNnyg = false;
      bool JqtnuAAFeR = false;
      bool UErGQQQRBr = false;
      bool DQjbEkXdiK = false;
      bool mqrWaHWFJt = false;
      bool oAYKTfhtwE = false;
      bool dwmGdrGRiJ = false;
      bool bWWTddMUfI = false;
      bool tKHGDDrYIY = false;
      bool DchdgqElrh = false;
      bool BEWARScFgo = false;
      bool TMOmKTnfDa = false;
      bool AgJKFyorml = false;
      bool ZZbxHpnHnj = false;
      bool ZlrSFqOtTN = false;
      bool CXiRgTuLtT = false;
      bool dkStPsjQeU = false;
      bool egqSANopEO = false;
      bool jtXZjBqKQn = false;
      bool tbMUGnTxDL = false;
      string hJnyIfGNzY;
      string kdKGNHdppz;
      string DxVlmcaxfW;
      string RaiFroOLaS;
      string yAeCaiPgYg;
      string KZpyHjnCLf;
      string EIgcGJtFOX;
      string sSOWBDSTLE;
      string NtYzMqjkyH;
      string BMAuNoSBuQ;
      string nKRAmrKTwD;
      string RTpHSKihQO;
      string ZJHGWgRTIL;
      string kQXtPCbXLU;
      string gQntogVscD;
      string FjkgpeDLdG;
      string ZqKjRBwwqP;
      string hKWwhJUMQo;
      string KYqEFAfqDk;
      string yQtFtoFDbn;
      if(hJnyIfGNzY == nKRAmrKTwD){kZBMVuNnyg = true;}
      else if(nKRAmrKTwD == hJnyIfGNzY){BEWARScFgo = true;}
      if(kdKGNHdppz == RTpHSKihQO){JqtnuAAFeR = true;}
      else if(RTpHSKihQO == kdKGNHdppz){TMOmKTnfDa = true;}
      if(DxVlmcaxfW == ZJHGWgRTIL){UErGQQQRBr = true;}
      else if(ZJHGWgRTIL == DxVlmcaxfW){AgJKFyorml = true;}
      if(RaiFroOLaS == kQXtPCbXLU){DQjbEkXdiK = true;}
      else if(kQXtPCbXLU == RaiFroOLaS){ZZbxHpnHnj = true;}
      if(yAeCaiPgYg == gQntogVscD){mqrWaHWFJt = true;}
      else if(gQntogVscD == yAeCaiPgYg){ZlrSFqOtTN = true;}
      if(KZpyHjnCLf == FjkgpeDLdG){oAYKTfhtwE = true;}
      else if(FjkgpeDLdG == KZpyHjnCLf){CXiRgTuLtT = true;}
      if(EIgcGJtFOX == ZqKjRBwwqP){dwmGdrGRiJ = true;}
      else if(ZqKjRBwwqP == EIgcGJtFOX){dkStPsjQeU = true;}
      if(sSOWBDSTLE == hKWwhJUMQo){bWWTddMUfI = true;}
      if(NtYzMqjkyH == KYqEFAfqDk){tKHGDDrYIY = true;}
      if(BMAuNoSBuQ == yQtFtoFDbn){DchdgqElrh = true;}
      while(hKWwhJUMQo == sSOWBDSTLE){egqSANopEO = true;}
      while(KYqEFAfqDk == KYqEFAfqDk){jtXZjBqKQn = true;}
      while(yQtFtoFDbn == yQtFtoFDbn){tbMUGnTxDL = true;}
      if(kZBMVuNnyg == true){kZBMVuNnyg = false;}
      if(JqtnuAAFeR == true){JqtnuAAFeR = false;}
      if(UErGQQQRBr == true){UErGQQQRBr = false;}
      if(DQjbEkXdiK == true){DQjbEkXdiK = false;}
      if(mqrWaHWFJt == true){mqrWaHWFJt = false;}
      if(oAYKTfhtwE == true){oAYKTfhtwE = false;}
      if(dwmGdrGRiJ == true){dwmGdrGRiJ = false;}
      if(bWWTddMUfI == true){bWWTddMUfI = false;}
      if(tKHGDDrYIY == true){tKHGDDrYIY = false;}
      if(DchdgqElrh == true){DchdgqElrh = false;}
      if(BEWARScFgo == true){BEWARScFgo = false;}
      if(TMOmKTnfDa == true){TMOmKTnfDa = false;}
      if(AgJKFyorml == true){AgJKFyorml = false;}
      if(ZZbxHpnHnj == true){ZZbxHpnHnj = false;}
      if(ZlrSFqOtTN == true){ZlrSFqOtTN = false;}
      if(CXiRgTuLtT == true){CXiRgTuLtT = false;}
      if(dkStPsjQeU == true){dkStPsjQeU = false;}
      if(egqSANopEO == true){egqSANopEO = false;}
      if(jtXZjBqKQn == true){jtXZjBqKQn = false;}
      if(tbMUGnTxDL == true){tbMUGnTxDL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PNZBIAJSBY
{ 
  void dVLJEEpYRe()
  { 
      bool fCHNUqhEky = false;
      bool EOVSJTYRii = false;
      bool eHPLmtfdmz = false;
      bool UoBeXDCLMf = false;
      bool HFYiwdCriR = false;
      bool xctxeYmwZa = false;
      bool LERlcONquF = false;
      bool QMFCbYhgOJ = false;
      bool rntVBruDAy = false;
      bool QGllUDnmFg = false;
      bool PKxdAjXqVG = false;
      bool qGgPhWJujk = false;
      bool TJqwoKaShY = false;
      bool jtahsgqQVR = false;
      bool TDhsHKZVDx = false;
      bool ssDTMGTAno = false;
      bool IFJxVwezVB = false;
      bool fsYRRPbxoe = false;
      bool kEOjeqqHUm = false;
      bool MpbfIOtkXK = false;
      string ResmikxMUL;
      string eLneNMLGrz;
      string YhhaKgyQCK;
      string lBRYNdMeUd;
      string mtbUDQCPJW;
      string nCjXyjwRbC;
      string lfJKYctPQj;
      string AfkNLeFMXs;
      string diHeWjRtZc;
      string gtCSqGjRua;
      string WmyZVHQVLT;
      string ditiXDYemo;
      string LAonCGdSVF;
      string tnRwWqjhIO;
      string TuiGzyATtn;
      string hEdGOVxKWP;
      string dxzFYoRxLg;
      string TpWYVQRhnE;
      string GJYhWoKKhA;
      string sYKrkVucgJ;
      if(ResmikxMUL == WmyZVHQVLT){fCHNUqhEky = true;}
      else if(WmyZVHQVLT == ResmikxMUL){PKxdAjXqVG = true;}
      if(eLneNMLGrz == ditiXDYemo){EOVSJTYRii = true;}
      else if(ditiXDYemo == eLneNMLGrz){qGgPhWJujk = true;}
      if(YhhaKgyQCK == LAonCGdSVF){eHPLmtfdmz = true;}
      else if(LAonCGdSVF == YhhaKgyQCK){TJqwoKaShY = true;}
      if(lBRYNdMeUd == tnRwWqjhIO){UoBeXDCLMf = true;}
      else if(tnRwWqjhIO == lBRYNdMeUd){jtahsgqQVR = true;}
      if(mtbUDQCPJW == TuiGzyATtn){HFYiwdCriR = true;}
      else if(TuiGzyATtn == mtbUDQCPJW){TDhsHKZVDx = true;}
      if(nCjXyjwRbC == hEdGOVxKWP){xctxeYmwZa = true;}
      else if(hEdGOVxKWP == nCjXyjwRbC){ssDTMGTAno = true;}
      if(lfJKYctPQj == dxzFYoRxLg){LERlcONquF = true;}
      else if(dxzFYoRxLg == lfJKYctPQj){IFJxVwezVB = true;}
      if(AfkNLeFMXs == TpWYVQRhnE){QMFCbYhgOJ = true;}
      if(diHeWjRtZc == GJYhWoKKhA){rntVBruDAy = true;}
      if(gtCSqGjRua == sYKrkVucgJ){QGllUDnmFg = true;}
      while(TpWYVQRhnE == AfkNLeFMXs){fsYRRPbxoe = true;}
      while(GJYhWoKKhA == GJYhWoKKhA){kEOjeqqHUm = true;}
      while(sYKrkVucgJ == sYKrkVucgJ){MpbfIOtkXK = true;}
      if(fCHNUqhEky == true){fCHNUqhEky = false;}
      if(EOVSJTYRii == true){EOVSJTYRii = false;}
      if(eHPLmtfdmz == true){eHPLmtfdmz = false;}
      if(UoBeXDCLMf == true){UoBeXDCLMf = false;}
      if(HFYiwdCriR == true){HFYiwdCriR = false;}
      if(xctxeYmwZa == true){xctxeYmwZa = false;}
      if(LERlcONquF == true){LERlcONquF = false;}
      if(QMFCbYhgOJ == true){QMFCbYhgOJ = false;}
      if(rntVBruDAy == true){rntVBruDAy = false;}
      if(QGllUDnmFg == true){QGllUDnmFg = false;}
      if(PKxdAjXqVG == true){PKxdAjXqVG = false;}
      if(qGgPhWJujk == true){qGgPhWJujk = false;}
      if(TJqwoKaShY == true){TJqwoKaShY = false;}
      if(jtahsgqQVR == true){jtahsgqQVR = false;}
      if(TDhsHKZVDx == true){TDhsHKZVDx = false;}
      if(ssDTMGTAno == true){ssDTMGTAno = false;}
      if(IFJxVwezVB == true){IFJxVwezVB = false;}
      if(fsYRRPbxoe == true){fsYRRPbxoe = false;}
      if(kEOjeqqHUm == true){kEOjeqqHUm = false;}
      if(MpbfIOtkXK == true){MpbfIOtkXK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NTQCKCGMYS
{ 
  void WNqFhYLlqU()
  { 
      bool zoaIMidxcq = false;
      bool kOHjDjJhsr = false;
      bool FrxVRwOHPX = false;
      bool yUyLygPsSf = false;
      bool WfSdKNaIYK = false;
      bool EpzpUHqFqQ = false;
      bool TVgErQPwkW = false;
      bool UQOMVYYSKD = false;
      bool VGhFTIUIpq = false;
      bool oJCCMAzOks = false;
      bool ydWComamUw = false;
      bool hXtmtNmakj = false;
      bool uHFtgLOLAU = false;
      bool ZKhRFqifPf = false;
      bool ghmtIRPOIz = false;
      bool MXcByqYcUd = false;
      bool YPmzWXpchC = false;
      bool eHLFDNTKkP = false;
      bool uzDBIBgfSO = false;
      bool RFKkGRunXk = false;
      string dGJTcGRcur;
      string QltywwOAxj;
      string ygUFzdgmog;
      string miICZXLZWZ;
      string ElEgCpyOql;
      string ztKtTwlDUz;
      string ZemOFgcrYX;
      string kocXfMbmDI;
      string eRuCgrYOic;
      string lHFXzZypbU;
      string NFoTBKRlNG;
      string UyAMTHikhM;
      string IOJukciFXF;
      string NlKhuYcaBV;
      string ZlAbImHrDr;
      string pNIOMywthY;
      string aLOIshnSRt;
      string eHjLlVNhly;
      string VpBfOAcuUw;
      string chsbuOXriZ;
      if(dGJTcGRcur == NFoTBKRlNG){zoaIMidxcq = true;}
      else if(NFoTBKRlNG == dGJTcGRcur){ydWComamUw = true;}
      if(QltywwOAxj == UyAMTHikhM){kOHjDjJhsr = true;}
      else if(UyAMTHikhM == QltywwOAxj){hXtmtNmakj = true;}
      if(ygUFzdgmog == IOJukciFXF){FrxVRwOHPX = true;}
      else if(IOJukciFXF == ygUFzdgmog){uHFtgLOLAU = true;}
      if(miICZXLZWZ == NlKhuYcaBV){yUyLygPsSf = true;}
      else if(NlKhuYcaBV == miICZXLZWZ){ZKhRFqifPf = true;}
      if(ElEgCpyOql == ZlAbImHrDr){WfSdKNaIYK = true;}
      else if(ZlAbImHrDr == ElEgCpyOql){ghmtIRPOIz = true;}
      if(ztKtTwlDUz == pNIOMywthY){EpzpUHqFqQ = true;}
      else if(pNIOMywthY == ztKtTwlDUz){MXcByqYcUd = true;}
      if(ZemOFgcrYX == aLOIshnSRt){TVgErQPwkW = true;}
      else if(aLOIshnSRt == ZemOFgcrYX){YPmzWXpchC = true;}
      if(kocXfMbmDI == eHjLlVNhly){UQOMVYYSKD = true;}
      if(eRuCgrYOic == VpBfOAcuUw){VGhFTIUIpq = true;}
      if(lHFXzZypbU == chsbuOXriZ){oJCCMAzOks = true;}
      while(eHjLlVNhly == kocXfMbmDI){eHLFDNTKkP = true;}
      while(VpBfOAcuUw == VpBfOAcuUw){uzDBIBgfSO = true;}
      while(chsbuOXriZ == chsbuOXriZ){RFKkGRunXk = true;}
      if(zoaIMidxcq == true){zoaIMidxcq = false;}
      if(kOHjDjJhsr == true){kOHjDjJhsr = false;}
      if(FrxVRwOHPX == true){FrxVRwOHPX = false;}
      if(yUyLygPsSf == true){yUyLygPsSf = false;}
      if(WfSdKNaIYK == true){WfSdKNaIYK = false;}
      if(EpzpUHqFqQ == true){EpzpUHqFqQ = false;}
      if(TVgErQPwkW == true){TVgErQPwkW = false;}
      if(UQOMVYYSKD == true){UQOMVYYSKD = false;}
      if(VGhFTIUIpq == true){VGhFTIUIpq = false;}
      if(oJCCMAzOks == true){oJCCMAzOks = false;}
      if(ydWComamUw == true){ydWComamUw = false;}
      if(hXtmtNmakj == true){hXtmtNmakj = false;}
      if(uHFtgLOLAU == true){uHFtgLOLAU = false;}
      if(ZKhRFqifPf == true){ZKhRFqifPf = false;}
      if(ghmtIRPOIz == true){ghmtIRPOIz = false;}
      if(MXcByqYcUd == true){MXcByqYcUd = false;}
      if(YPmzWXpchC == true){YPmzWXpchC = false;}
      if(eHLFDNTKkP == true){eHLFDNTKkP = false;}
      if(uzDBIBgfSO == true){uzDBIBgfSO = false;}
      if(RFKkGRunXk == true){RFKkGRunXk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MJBYMDPEEB
{ 
  void QsASeyXama()
  { 
      bool mraUJcNVPk = false;
      bool MHxVkeCoIH = false;
      bool IZMCAMQNEG = false;
      bool WGKbzqcYhn = false;
      bool XAuUAcAlzw = false;
      bool PYqIINeXTx = false;
      bool MARINGxVVs = false;
      bool CcHUiHerBW = false;
      bool LdNIqyOBTl = false;
      bool MEFkaXhlGt = false;
      bool fePGslQWZA = false;
      bool hlWwkhlJRP = false;
      bool quCigyXWtL = false;
      bool YrkGqgOHOE = false;
      bool grbSEZhIzr = false;
      bool kYUqDjcfZu = false;
      bool OtbNapAPFD = false;
      bool TdtMhzTieG = false;
      bool QPWBZAWtDG = false;
      bool EihTplPOrN = false;
      string PcsahwQRlX;
      string qesIFrKQOj;
      string IsKNqpglpF;
      string VSaIVenYDi;
      string XrZeeGDPxU;
      string PJaGHWSfir;
      string PeagBYDkmZ;
      string EkMfLPSeik;
      string lQoVoMqUAz;
      string MIpLSrRsdF;
      string CScWQdxttq;
      string DmxyFypEqn;
      string hijmMuuAMT;
      string yYBchTmRFK;
      string OwaIuZLqGU;
      string CMCoWTioJU;
      string iwhZselTQk;
      string KYyfYlHarm;
      string jDtrRlWLGN;
      string kyHkbROAPQ;
      if(PcsahwQRlX == CScWQdxttq){mraUJcNVPk = true;}
      else if(CScWQdxttq == PcsahwQRlX){fePGslQWZA = true;}
      if(qesIFrKQOj == DmxyFypEqn){MHxVkeCoIH = true;}
      else if(DmxyFypEqn == qesIFrKQOj){hlWwkhlJRP = true;}
      if(IsKNqpglpF == hijmMuuAMT){IZMCAMQNEG = true;}
      else if(hijmMuuAMT == IsKNqpglpF){quCigyXWtL = true;}
      if(VSaIVenYDi == yYBchTmRFK){WGKbzqcYhn = true;}
      else if(yYBchTmRFK == VSaIVenYDi){YrkGqgOHOE = true;}
      if(XrZeeGDPxU == OwaIuZLqGU){XAuUAcAlzw = true;}
      else if(OwaIuZLqGU == XrZeeGDPxU){grbSEZhIzr = true;}
      if(PJaGHWSfir == CMCoWTioJU){PYqIINeXTx = true;}
      else if(CMCoWTioJU == PJaGHWSfir){kYUqDjcfZu = true;}
      if(PeagBYDkmZ == iwhZselTQk){MARINGxVVs = true;}
      else if(iwhZselTQk == PeagBYDkmZ){OtbNapAPFD = true;}
      if(EkMfLPSeik == KYyfYlHarm){CcHUiHerBW = true;}
      if(lQoVoMqUAz == jDtrRlWLGN){LdNIqyOBTl = true;}
      if(MIpLSrRsdF == kyHkbROAPQ){MEFkaXhlGt = true;}
      while(KYyfYlHarm == EkMfLPSeik){TdtMhzTieG = true;}
      while(jDtrRlWLGN == jDtrRlWLGN){QPWBZAWtDG = true;}
      while(kyHkbROAPQ == kyHkbROAPQ){EihTplPOrN = true;}
      if(mraUJcNVPk == true){mraUJcNVPk = false;}
      if(MHxVkeCoIH == true){MHxVkeCoIH = false;}
      if(IZMCAMQNEG == true){IZMCAMQNEG = false;}
      if(WGKbzqcYhn == true){WGKbzqcYhn = false;}
      if(XAuUAcAlzw == true){XAuUAcAlzw = false;}
      if(PYqIINeXTx == true){PYqIINeXTx = false;}
      if(MARINGxVVs == true){MARINGxVVs = false;}
      if(CcHUiHerBW == true){CcHUiHerBW = false;}
      if(LdNIqyOBTl == true){LdNIqyOBTl = false;}
      if(MEFkaXhlGt == true){MEFkaXhlGt = false;}
      if(fePGslQWZA == true){fePGslQWZA = false;}
      if(hlWwkhlJRP == true){hlWwkhlJRP = false;}
      if(quCigyXWtL == true){quCigyXWtL = false;}
      if(YrkGqgOHOE == true){YrkGqgOHOE = false;}
      if(grbSEZhIzr == true){grbSEZhIzr = false;}
      if(kYUqDjcfZu == true){kYUqDjcfZu = false;}
      if(OtbNapAPFD == true){OtbNapAPFD = false;}
      if(TdtMhzTieG == true){TdtMhzTieG = false;}
      if(QPWBZAWtDG == true){QPWBZAWtDG = false;}
      if(EihTplPOrN == true){EihTplPOrN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class URJAGJACHU
{ 
  void xeJBlNtVqa()
  { 
      bool rxpqMYiWSG = false;
      bool tckJNmLsMQ = false;
      bool kcHbqUdRAO = false;
      bool QkSrwTxBab = false;
      bool TBTFDdMHkt = false;
      bool aiINEOpNAr = false;
      bool tRVEpIKrNs = false;
      bool oKSkxjJBYM = false;
      bool HWfFmhcEng = false;
      bool diBhgCePPu = false;
      bool TTsqEQQWQT = false;
      bool EnomjXkPQI = false;
      bool fFEfPGIjEu = false;
      bool EtldrncnBW = false;
      bool QFnTbptNxI = false;
      bool QPyHPOONby = false;
      bool HfRVPKBLtw = false;
      bool uxOtqZQjDZ = false;
      bool MtlwdoueNd = false;
      bool YOMCOknSEQ = false;
      string MwaJPpuezu;
      string CzzPtgGEAq;
      string eBGdqimcqS;
      string VqskwTxKBR;
      string thclNzhUUy;
      string cphcSKoxSg;
      string CRmgYLGNSZ;
      string jwDhwxYTPr;
      string BSIrofJPSk;
      string dAqUOctwNC;
      string rUBtOfmzgV;
      string lVhZejJtqs;
      string CpthwjFhST;
      string CcGMzgROdI;
      string rJixzHSQoe;
      string SzETABZTxe;
      string aEgNSJPUay;
      string StQhBsHxhn;
      string RnsmACXlMy;
      string HxQzhmbVdp;
      if(MwaJPpuezu == rUBtOfmzgV){rxpqMYiWSG = true;}
      else if(rUBtOfmzgV == MwaJPpuezu){TTsqEQQWQT = true;}
      if(CzzPtgGEAq == lVhZejJtqs){tckJNmLsMQ = true;}
      else if(lVhZejJtqs == CzzPtgGEAq){EnomjXkPQI = true;}
      if(eBGdqimcqS == CpthwjFhST){kcHbqUdRAO = true;}
      else if(CpthwjFhST == eBGdqimcqS){fFEfPGIjEu = true;}
      if(VqskwTxKBR == CcGMzgROdI){QkSrwTxBab = true;}
      else if(CcGMzgROdI == VqskwTxKBR){EtldrncnBW = true;}
      if(thclNzhUUy == rJixzHSQoe){TBTFDdMHkt = true;}
      else if(rJixzHSQoe == thclNzhUUy){QFnTbptNxI = true;}
      if(cphcSKoxSg == SzETABZTxe){aiINEOpNAr = true;}
      else if(SzETABZTxe == cphcSKoxSg){QPyHPOONby = true;}
      if(CRmgYLGNSZ == aEgNSJPUay){tRVEpIKrNs = true;}
      else if(aEgNSJPUay == CRmgYLGNSZ){HfRVPKBLtw = true;}
      if(jwDhwxYTPr == StQhBsHxhn){oKSkxjJBYM = true;}
      if(BSIrofJPSk == RnsmACXlMy){HWfFmhcEng = true;}
      if(dAqUOctwNC == HxQzhmbVdp){diBhgCePPu = true;}
      while(StQhBsHxhn == jwDhwxYTPr){uxOtqZQjDZ = true;}
      while(RnsmACXlMy == RnsmACXlMy){MtlwdoueNd = true;}
      while(HxQzhmbVdp == HxQzhmbVdp){YOMCOknSEQ = true;}
      if(rxpqMYiWSG == true){rxpqMYiWSG = false;}
      if(tckJNmLsMQ == true){tckJNmLsMQ = false;}
      if(kcHbqUdRAO == true){kcHbqUdRAO = false;}
      if(QkSrwTxBab == true){QkSrwTxBab = false;}
      if(TBTFDdMHkt == true){TBTFDdMHkt = false;}
      if(aiINEOpNAr == true){aiINEOpNAr = false;}
      if(tRVEpIKrNs == true){tRVEpIKrNs = false;}
      if(oKSkxjJBYM == true){oKSkxjJBYM = false;}
      if(HWfFmhcEng == true){HWfFmhcEng = false;}
      if(diBhgCePPu == true){diBhgCePPu = false;}
      if(TTsqEQQWQT == true){TTsqEQQWQT = false;}
      if(EnomjXkPQI == true){EnomjXkPQI = false;}
      if(fFEfPGIjEu == true){fFEfPGIjEu = false;}
      if(EtldrncnBW == true){EtldrncnBW = false;}
      if(QFnTbptNxI == true){QFnTbptNxI = false;}
      if(QPyHPOONby == true){QPyHPOONby = false;}
      if(HfRVPKBLtw == true){HfRVPKBLtw = false;}
      if(uxOtqZQjDZ == true){uxOtqZQjDZ = false;}
      if(MtlwdoueNd == true){MtlwdoueNd = false;}
      if(YOMCOknSEQ == true){YOMCOknSEQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YSJINRSYLP
{ 
  void gqQQwNcQZm()
  { 
      bool UOdipdVckg = false;
      bool yxBlDusnPC = false;
      bool eAnsFnuRqQ = false;
      bool IcpXHUeHzm = false;
      bool XxiJJgFtbK = false;
      bool qUTVIUZkcC = false;
      bool hElTXVGcdh = false;
      bool PlncdhQeiY = false;
      bool iAofZnIUPm = false;
      bool ttdxESLOkn = false;
      bool abPsuEgqqa = false;
      bool DuCEThPFsj = false;
      bool MkMqnVIqYK = false;
      bool WCsuyGkujV = false;
      bool GRdojzrZdW = false;
      bool DFUBaoPXFZ = false;
      bool wpSgDBCGGN = false;
      bool wUUXcuHXHn = false;
      bool dhNBGQgrUI = false;
      bool qNoKYQzwki = false;
      string NCZWDHenGD;
      string aKxmihYNXS;
      string ZbMEqqHirr;
      string QZPjiEmgHy;
      string WduwGiGVJK;
      string mAfxGlpUeM;
      string zuuNmAtMDe;
      string urFZwugPxI;
      string klZgFPtRdx;
      string NRCuyahgJG;
      string ntSePttFBK;
      string EZWVaNVOHW;
      string GchFQcpKaU;
      string NzGqTpTtRK;
      string UnPTsntfTk;
      string ESZmzLLNOl;
      string EjefwFTfBk;
      string taxxBSMOMb;
      string iJppQtZTqI;
      string eGfeFkJjXn;
      if(NCZWDHenGD == ntSePttFBK){UOdipdVckg = true;}
      else if(ntSePttFBK == NCZWDHenGD){abPsuEgqqa = true;}
      if(aKxmihYNXS == EZWVaNVOHW){yxBlDusnPC = true;}
      else if(EZWVaNVOHW == aKxmihYNXS){DuCEThPFsj = true;}
      if(ZbMEqqHirr == GchFQcpKaU){eAnsFnuRqQ = true;}
      else if(GchFQcpKaU == ZbMEqqHirr){MkMqnVIqYK = true;}
      if(QZPjiEmgHy == NzGqTpTtRK){IcpXHUeHzm = true;}
      else if(NzGqTpTtRK == QZPjiEmgHy){WCsuyGkujV = true;}
      if(WduwGiGVJK == UnPTsntfTk){XxiJJgFtbK = true;}
      else if(UnPTsntfTk == WduwGiGVJK){GRdojzrZdW = true;}
      if(mAfxGlpUeM == ESZmzLLNOl){qUTVIUZkcC = true;}
      else if(ESZmzLLNOl == mAfxGlpUeM){DFUBaoPXFZ = true;}
      if(zuuNmAtMDe == EjefwFTfBk){hElTXVGcdh = true;}
      else if(EjefwFTfBk == zuuNmAtMDe){wpSgDBCGGN = true;}
      if(urFZwugPxI == taxxBSMOMb){PlncdhQeiY = true;}
      if(klZgFPtRdx == iJppQtZTqI){iAofZnIUPm = true;}
      if(NRCuyahgJG == eGfeFkJjXn){ttdxESLOkn = true;}
      while(taxxBSMOMb == urFZwugPxI){wUUXcuHXHn = true;}
      while(iJppQtZTqI == iJppQtZTqI){dhNBGQgrUI = true;}
      while(eGfeFkJjXn == eGfeFkJjXn){qNoKYQzwki = true;}
      if(UOdipdVckg == true){UOdipdVckg = false;}
      if(yxBlDusnPC == true){yxBlDusnPC = false;}
      if(eAnsFnuRqQ == true){eAnsFnuRqQ = false;}
      if(IcpXHUeHzm == true){IcpXHUeHzm = false;}
      if(XxiJJgFtbK == true){XxiJJgFtbK = false;}
      if(qUTVIUZkcC == true){qUTVIUZkcC = false;}
      if(hElTXVGcdh == true){hElTXVGcdh = false;}
      if(PlncdhQeiY == true){PlncdhQeiY = false;}
      if(iAofZnIUPm == true){iAofZnIUPm = false;}
      if(ttdxESLOkn == true){ttdxESLOkn = false;}
      if(abPsuEgqqa == true){abPsuEgqqa = false;}
      if(DuCEThPFsj == true){DuCEThPFsj = false;}
      if(MkMqnVIqYK == true){MkMqnVIqYK = false;}
      if(WCsuyGkujV == true){WCsuyGkujV = false;}
      if(GRdojzrZdW == true){GRdojzrZdW = false;}
      if(DFUBaoPXFZ == true){DFUBaoPXFZ = false;}
      if(wpSgDBCGGN == true){wpSgDBCGGN = false;}
      if(wUUXcuHXHn == true){wUUXcuHXHn = false;}
      if(dhNBGQgrUI == true){dhNBGQgrUI = false;}
      if(qNoKYQzwki == true){qNoKYQzwki = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QJLYBLGVUP
{ 
  void PGSiKKJnnb()
  { 
      bool gGncZxQmqX = false;
      bool RgnqMdZuEG = false;
      bool CYiJNTTcqF = false;
      bool rBBEcOSyst = false;
      bool JJamOOeGaM = false;
      bool EVmBhIWdOF = false;
      bool dnulfQfiNx = false;
      bool LbCKwsywtz = false;
      bool nMBeBVNzWU = false;
      bool rnimQVNnGy = false;
      bool huscAbTbEn = false;
      bool JZiOQQlPkK = false;
      bool CfLrFWsPsZ = false;
      bool eJowRsTYeY = false;
      bool CluiLRETVz = false;
      bool jyDwuBiAWc = false;
      bool iDhdIzkmxX = false;
      bool xMkLHQkcgn = false;
      bool RYttpgGsAP = false;
      bool JSBBpyDQZL = false;
      string AEIeKJOwjM;
      string MGZjWAqzLR;
      string HmjEHoYNka;
      string DwfxMdqnDh;
      string feoznTPZdM;
      string aJWnSNUDXV;
      string jAKJIPZbXs;
      string ICuckcxjQm;
      string ZzjYzsZqez;
      string JmQhxeTfpX;
      string tmCkDXNsCp;
      string PkmjukQlKP;
      string phxXiVlMeG;
      string IRsrslxzVb;
      string efooiYAflM;
      string OhUahLpdBh;
      string kANwgyqtqJ;
      string mRQhjJsIoK;
      string UGaSqawRKg;
      string uTxmpdRrHj;
      if(AEIeKJOwjM == tmCkDXNsCp){gGncZxQmqX = true;}
      else if(tmCkDXNsCp == AEIeKJOwjM){huscAbTbEn = true;}
      if(MGZjWAqzLR == PkmjukQlKP){RgnqMdZuEG = true;}
      else if(PkmjukQlKP == MGZjWAqzLR){JZiOQQlPkK = true;}
      if(HmjEHoYNka == phxXiVlMeG){CYiJNTTcqF = true;}
      else if(phxXiVlMeG == HmjEHoYNka){CfLrFWsPsZ = true;}
      if(DwfxMdqnDh == IRsrslxzVb){rBBEcOSyst = true;}
      else if(IRsrslxzVb == DwfxMdqnDh){eJowRsTYeY = true;}
      if(feoznTPZdM == efooiYAflM){JJamOOeGaM = true;}
      else if(efooiYAflM == feoznTPZdM){CluiLRETVz = true;}
      if(aJWnSNUDXV == OhUahLpdBh){EVmBhIWdOF = true;}
      else if(OhUahLpdBh == aJWnSNUDXV){jyDwuBiAWc = true;}
      if(jAKJIPZbXs == kANwgyqtqJ){dnulfQfiNx = true;}
      else if(kANwgyqtqJ == jAKJIPZbXs){iDhdIzkmxX = true;}
      if(ICuckcxjQm == mRQhjJsIoK){LbCKwsywtz = true;}
      if(ZzjYzsZqez == UGaSqawRKg){nMBeBVNzWU = true;}
      if(JmQhxeTfpX == uTxmpdRrHj){rnimQVNnGy = true;}
      while(mRQhjJsIoK == ICuckcxjQm){xMkLHQkcgn = true;}
      while(UGaSqawRKg == UGaSqawRKg){RYttpgGsAP = true;}
      while(uTxmpdRrHj == uTxmpdRrHj){JSBBpyDQZL = true;}
      if(gGncZxQmqX == true){gGncZxQmqX = false;}
      if(RgnqMdZuEG == true){RgnqMdZuEG = false;}
      if(CYiJNTTcqF == true){CYiJNTTcqF = false;}
      if(rBBEcOSyst == true){rBBEcOSyst = false;}
      if(JJamOOeGaM == true){JJamOOeGaM = false;}
      if(EVmBhIWdOF == true){EVmBhIWdOF = false;}
      if(dnulfQfiNx == true){dnulfQfiNx = false;}
      if(LbCKwsywtz == true){LbCKwsywtz = false;}
      if(nMBeBVNzWU == true){nMBeBVNzWU = false;}
      if(rnimQVNnGy == true){rnimQVNnGy = false;}
      if(huscAbTbEn == true){huscAbTbEn = false;}
      if(JZiOQQlPkK == true){JZiOQQlPkK = false;}
      if(CfLrFWsPsZ == true){CfLrFWsPsZ = false;}
      if(eJowRsTYeY == true){eJowRsTYeY = false;}
      if(CluiLRETVz == true){CluiLRETVz = false;}
      if(jyDwuBiAWc == true){jyDwuBiAWc = false;}
      if(iDhdIzkmxX == true){iDhdIzkmxX = false;}
      if(xMkLHQkcgn == true){xMkLHQkcgn = false;}
      if(RYttpgGsAP == true){RYttpgGsAP = false;}
      if(JSBBpyDQZL == true){JSBBpyDQZL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZLWVBUBBRF
{ 
  void FLccQYNGJS()
  { 
      bool lPMQMuzJJz = false;
      bool LzgWjTbPAj = false;
      bool nzYbPRxtyZ = false;
      bool EqrMVMXGjW = false;
      bool xqWPLQurNM = false;
      bool PJMPnmpkAt = false;
      bool yEKiuTGUAX = false;
      bool wUfdmxbJPz = false;
      bool WFglJtecXh = false;
      bool WmGoYrgmTq = false;
      bool KZqpQudibq = false;
      bool KgUBXrXYYA = false;
      bool ncxSBINqEt = false;
      bool PooYnwOpUO = false;
      bool QwBfWoRFRg = false;
      bool UHNSCgcYoH = false;
      bool gmdhaVqwMa = false;
      bool dgEKjrbQuL = false;
      bool qIYXYIaVVG = false;
      bool SoBNgdRSEB = false;
      string WaUedllYeE;
      string oXlbMZQEcG;
      string rywzEQOhPd;
      string kWKKVhHXzX;
      string RFEELOrkiL;
      string sZUiHXdVaN;
      string WEIATRMaFd;
      string SsFEnlsrmo;
      string YdyEkKCaCx;
      string ElxkANxEjt;
      string BQeFsATQtV;
      string elhlnsFEPI;
      string PlYIZfuUDa;
      string ooHsmHysLk;
      string qlgfSRDLxH;
      string HrnadPqWeM;
      string EzMTgoenyf;
      string tMseRdEroI;
      string bjXwSwAfPW;
      string QbOyfqZNzc;
      if(WaUedllYeE == BQeFsATQtV){lPMQMuzJJz = true;}
      else if(BQeFsATQtV == WaUedllYeE){KZqpQudibq = true;}
      if(oXlbMZQEcG == elhlnsFEPI){LzgWjTbPAj = true;}
      else if(elhlnsFEPI == oXlbMZQEcG){KgUBXrXYYA = true;}
      if(rywzEQOhPd == PlYIZfuUDa){nzYbPRxtyZ = true;}
      else if(PlYIZfuUDa == rywzEQOhPd){ncxSBINqEt = true;}
      if(kWKKVhHXzX == ooHsmHysLk){EqrMVMXGjW = true;}
      else if(ooHsmHysLk == kWKKVhHXzX){PooYnwOpUO = true;}
      if(RFEELOrkiL == qlgfSRDLxH){xqWPLQurNM = true;}
      else if(qlgfSRDLxH == RFEELOrkiL){QwBfWoRFRg = true;}
      if(sZUiHXdVaN == HrnadPqWeM){PJMPnmpkAt = true;}
      else if(HrnadPqWeM == sZUiHXdVaN){UHNSCgcYoH = true;}
      if(WEIATRMaFd == EzMTgoenyf){yEKiuTGUAX = true;}
      else if(EzMTgoenyf == WEIATRMaFd){gmdhaVqwMa = true;}
      if(SsFEnlsrmo == tMseRdEroI){wUfdmxbJPz = true;}
      if(YdyEkKCaCx == bjXwSwAfPW){WFglJtecXh = true;}
      if(ElxkANxEjt == QbOyfqZNzc){WmGoYrgmTq = true;}
      while(tMseRdEroI == SsFEnlsrmo){dgEKjrbQuL = true;}
      while(bjXwSwAfPW == bjXwSwAfPW){qIYXYIaVVG = true;}
      while(QbOyfqZNzc == QbOyfqZNzc){SoBNgdRSEB = true;}
      if(lPMQMuzJJz == true){lPMQMuzJJz = false;}
      if(LzgWjTbPAj == true){LzgWjTbPAj = false;}
      if(nzYbPRxtyZ == true){nzYbPRxtyZ = false;}
      if(EqrMVMXGjW == true){EqrMVMXGjW = false;}
      if(xqWPLQurNM == true){xqWPLQurNM = false;}
      if(PJMPnmpkAt == true){PJMPnmpkAt = false;}
      if(yEKiuTGUAX == true){yEKiuTGUAX = false;}
      if(wUfdmxbJPz == true){wUfdmxbJPz = false;}
      if(WFglJtecXh == true){WFglJtecXh = false;}
      if(WmGoYrgmTq == true){WmGoYrgmTq = false;}
      if(KZqpQudibq == true){KZqpQudibq = false;}
      if(KgUBXrXYYA == true){KgUBXrXYYA = false;}
      if(ncxSBINqEt == true){ncxSBINqEt = false;}
      if(PooYnwOpUO == true){PooYnwOpUO = false;}
      if(QwBfWoRFRg == true){QwBfWoRFRg = false;}
      if(UHNSCgcYoH == true){UHNSCgcYoH = false;}
      if(gmdhaVqwMa == true){gmdhaVqwMa = false;}
      if(dgEKjrbQuL == true){dgEKjrbQuL = false;}
      if(qIYXYIaVVG == true){qIYXYIaVVG = false;}
      if(SoBNgdRSEB == true){SoBNgdRSEB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GOBBJREYDW
{ 
  void tPpGYEWaDF()
  { 
      bool kPDOqtKczJ = false;
      bool KkBVxPHgum = false;
      bool eMQPQpnaeK = false;
      bool ZOZelXZVVg = false;
      bool ADVztVblqu = false;
      bool sgrOcYymyB = false;
      bool GixniuLVjZ = false;
      bool okLNlaqRVu = false;
      bool NCijRsWLBN = false;
      bool YmXUaQGgPy = false;
      bool KGCRGIVdcC = false;
      bool ggQCmEANWp = false;
      bool YzUVBBMpmU = false;
      bool UJCXjHARcI = false;
      bool XsiyfqVUhW = false;
      bool QrKZZLkfQE = false;
      bool weqHhWdsSe = false;
      bool EijNRfQVoJ = false;
      bool fqIPDbzbyY = false;
      bool VTAYMrBaQJ = false;
      string toLURoZnHC;
      string qKkmNKLtPX;
      string AVeZlMrrHL;
      string kQuXCpIumt;
      string TxIhWqCeHR;
      string LYntnXJkiE;
      string xgfuRZOMkW;
      string CPHUEDMwDu;
      string KMkpALbAjd;
      string fXMhwlQNQw;
      string botjPwRToj;
      string KNgntkwptF;
      string xNbGpdCYYR;
      string lzfHSURAZE;
      string sILzTSpYnL;
      string paSKyNNnsk;
      string srtXyKgZUY;
      string TuPpLnCbmX;
      string ndkNbLfUIE;
      string HcHoKAOmBI;
      if(toLURoZnHC == botjPwRToj){kPDOqtKczJ = true;}
      else if(botjPwRToj == toLURoZnHC){KGCRGIVdcC = true;}
      if(qKkmNKLtPX == KNgntkwptF){KkBVxPHgum = true;}
      else if(KNgntkwptF == qKkmNKLtPX){ggQCmEANWp = true;}
      if(AVeZlMrrHL == xNbGpdCYYR){eMQPQpnaeK = true;}
      else if(xNbGpdCYYR == AVeZlMrrHL){YzUVBBMpmU = true;}
      if(kQuXCpIumt == lzfHSURAZE){ZOZelXZVVg = true;}
      else if(lzfHSURAZE == kQuXCpIumt){UJCXjHARcI = true;}
      if(TxIhWqCeHR == sILzTSpYnL){ADVztVblqu = true;}
      else if(sILzTSpYnL == TxIhWqCeHR){XsiyfqVUhW = true;}
      if(LYntnXJkiE == paSKyNNnsk){sgrOcYymyB = true;}
      else if(paSKyNNnsk == LYntnXJkiE){QrKZZLkfQE = true;}
      if(xgfuRZOMkW == srtXyKgZUY){GixniuLVjZ = true;}
      else if(srtXyKgZUY == xgfuRZOMkW){weqHhWdsSe = true;}
      if(CPHUEDMwDu == TuPpLnCbmX){okLNlaqRVu = true;}
      if(KMkpALbAjd == ndkNbLfUIE){NCijRsWLBN = true;}
      if(fXMhwlQNQw == HcHoKAOmBI){YmXUaQGgPy = true;}
      while(TuPpLnCbmX == CPHUEDMwDu){EijNRfQVoJ = true;}
      while(ndkNbLfUIE == ndkNbLfUIE){fqIPDbzbyY = true;}
      while(HcHoKAOmBI == HcHoKAOmBI){VTAYMrBaQJ = true;}
      if(kPDOqtKczJ == true){kPDOqtKczJ = false;}
      if(KkBVxPHgum == true){KkBVxPHgum = false;}
      if(eMQPQpnaeK == true){eMQPQpnaeK = false;}
      if(ZOZelXZVVg == true){ZOZelXZVVg = false;}
      if(ADVztVblqu == true){ADVztVblqu = false;}
      if(sgrOcYymyB == true){sgrOcYymyB = false;}
      if(GixniuLVjZ == true){GixniuLVjZ = false;}
      if(okLNlaqRVu == true){okLNlaqRVu = false;}
      if(NCijRsWLBN == true){NCijRsWLBN = false;}
      if(YmXUaQGgPy == true){YmXUaQGgPy = false;}
      if(KGCRGIVdcC == true){KGCRGIVdcC = false;}
      if(ggQCmEANWp == true){ggQCmEANWp = false;}
      if(YzUVBBMpmU == true){YzUVBBMpmU = false;}
      if(UJCXjHARcI == true){UJCXjHARcI = false;}
      if(XsiyfqVUhW == true){XsiyfqVUhW = false;}
      if(QrKZZLkfQE == true){QrKZZLkfQE = false;}
      if(weqHhWdsSe == true){weqHhWdsSe = false;}
      if(EijNRfQVoJ == true){EijNRfQVoJ = false;}
      if(fqIPDbzbyY == true){fqIPDbzbyY = false;}
      if(VTAYMrBaQJ == true){VTAYMrBaQJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TXTOOHJSBW
{ 
  void ooRwysufDB()
  { 
      bool Tbqjinwabi = false;
      bool nFuGkBbdiL = false;
      bool HrjqkfjGdR = false;
      bool dyMKznrsKf = false;
      bool PHhWdpZnYk = false;
      bool OcQZbbqzyD = false;
      bool DpxJEoskHw = false;
      bool JhTDuAJNNu = false;
      bool FwhsDBhlhW = false;
      bool xrtHbZJYRn = false;
      bool wogbafJMdb = false;
      bool RckDxHIEGD = false;
      bool HHCjzRnLaV = false;
      bool pkwZzQOFRX = false;
      bool qUHGFTGpJU = false;
      bool RFSNgolwbJ = false;
      bool qxlIlfgLDg = false;
      bool rClhLmzwee = false;
      bool KxBGEjShrK = false;
      bool dScIfsizTY = false;
      string tFeqXfBVxo;
      string OyccQdViIR;
      string cVXAifuOxO;
      string oNyQPDMWog;
      string HNOnmoVYcB;
      string UtdBLXhdHq;
      string jlXhzAzLNM;
      string RzsaJOGjMt;
      string JWlusuiwFr;
      string ViOyxUofnl;
      string oKLQjVADrw;
      string QyQNgMAbnD;
      string RCGUphjudn;
      string YauaEzLULX;
      string ufEIaWRARj;
      string TMqjUlDpZB;
      string kFYDWpDpJg;
      string BfQQIkyxtS;
      string QictTLiKFR;
      string uVuJmpHAkj;
      if(tFeqXfBVxo == oKLQjVADrw){Tbqjinwabi = true;}
      else if(oKLQjVADrw == tFeqXfBVxo){wogbafJMdb = true;}
      if(OyccQdViIR == QyQNgMAbnD){nFuGkBbdiL = true;}
      else if(QyQNgMAbnD == OyccQdViIR){RckDxHIEGD = true;}
      if(cVXAifuOxO == RCGUphjudn){HrjqkfjGdR = true;}
      else if(RCGUphjudn == cVXAifuOxO){HHCjzRnLaV = true;}
      if(oNyQPDMWog == YauaEzLULX){dyMKznrsKf = true;}
      else if(YauaEzLULX == oNyQPDMWog){pkwZzQOFRX = true;}
      if(HNOnmoVYcB == ufEIaWRARj){PHhWdpZnYk = true;}
      else if(ufEIaWRARj == HNOnmoVYcB){qUHGFTGpJU = true;}
      if(UtdBLXhdHq == TMqjUlDpZB){OcQZbbqzyD = true;}
      else if(TMqjUlDpZB == UtdBLXhdHq){RFSNgolwbJ = true;}
      if(jlXhzAzLNM == kFYDWpDpJg){DpxJEoskHw = true;}
      else if(kFYDWpDpJg == jlXhzAzLNM){qxlIlfgLDg = true;}
      if(RzsaJOGjMt == BfQQIkyxtS){JhTDuAJNNu = true;}
      if(JWlusuiwFr == QictTLiKFR){FwhsDBhlhW = true;}
      if(ViOyxUofnl == uVuJmpHAkj){xrtHbZJYRn = true;}
      while(BfQQIkyxtS == RzsaJOGjMt){rClhLmzwee = true;}
      while(QictTLiKFR == QictTLiKFR){KxBGEjShrK = true;}
      while(uVuJmpHAkj == uVuJmpHAkj){dScIfsizTY = true;}
      if(Tbqjinwabi == true){Tbqjinwabi = false;}
      if(nFuGkBbdiL == true){nFuGkBbdiL = false;}
      if(HrjqkfjGdR == true){HrjqkfjGdR = false;}
      if(dyMKznrsKf == true){dyMKznrsKf = false;}
      if(PHhWdpZnYk == true){PHhWdpZnYk = false;}
      if(OcQZbbqzyD == true){OcQZbbqzyD = false;}
      if(DpxJEoskHw == true){DpxJEoskHw = false;}
      if(JhTDuAJNNu == true){JhTDuAJNNu = false;}
      if(FwhsDBhlhW == true){FwhsDBhlhW = false;}
      if(xrtHbZJYRn == true){xrtHbZJYRn = false;}
      if(wogbafJMdb == true){wogbafJMdb = false;}
      if(RckDxHIEGD == true){RckDxHIEGD = false;}
      if(HHCjzRnLaV == true){HHCjzRnLaV = false;}
      if(pkwZzQOFRX == true){pkwZzQOFRX = false;}
      if(qUHGFTGpJU == true){qUHGFTGpJU = false;}
      if(RFSNgolwbJ == true){RFSNgolwbJ = false;}
      if(qxlIlfgLDg == true){qxlIlfgLDg = false;}
      if(rClhLmzwee == true){rClhLmzwee = false;}
      if(KxBGEjShrK == true){KxBGEjShrK = false;}
      if(dScIfsizTY == true){dScIfsizTY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HTZBSVOTPV
{ 
  void WQDcetNfAq()
  { 
      bool sJaTSebPnU = false;
      bool HHBmLXurje = false;
      bool wMXmIrydyJ = false;
      bool yJRrOAKtxz = false;
      bool SyNRRfaKuU = false;
      bool doYnbfknLa = false;
      bool fxQeWxoJYK = false;
      bool MAtkMyyFVb = false;
      bool QnideIkdQh = false;
      bool OWiWSUhitU = false;
      bool qRkjHcunbc = false;
      bool geSjJrOmzO = false;
      bool MKsqupRWRq = false;
      bool QOKAjzCyVC = false;
      bool NwCmAiEzMa = false;
      bool GtjfHfXtoR = false;
      bool LXWjMSURzK = false;
      bool oPRxBQIGpL = false;
      bool lRJqjVeesE = false;
      bool aIJDpoYRZh = false;
      string HpbHPPcceU;
      string AVxaOlMxpi;
      string EFoNYhmgiy;
      string gZjqPzjjZg;
      string MUhbzEcbbE;
      string LKVqQBBOhh;
      string cutgmakFLO;
      string BbWIWiWMNT;
      string ELFelVDsaN;
      string xVBrEQaBnY;
      string TXPMCimMUg;
      string enANcQoOtR;
      string WreyQfZdEF;
      string HUYoAguscC;
      string iqXshIUnPn;
      string aMHWBasRuV;
      string JJIOZJPLMw;
      string UwkrhfTkPH;
      string KlOQdtNCmZ;
      string ncxGsYhJTX;
      if(HpbHPPcceU == TXPMCimMUg){sJaTSebPnU = true;}
      else if(TXPMCimMUg == HpbHPPcceU){qRkjHcunbc = true;}
      if(AVxaOlMxpi == enANcQoOtR){HHBmLXurje = true;}
      else if(enANcQoOtR == AVxaOlMxpi){geSjJrOmzO = true;}
      if(EFoNYhmgiy == WreyQfZdEF){wMXmIrydyJ = true;}
      else if(WreyQfZdEF == EFoNYhmgiy){MKsqupRWRq = true;}
      if(gZjqPzjjZg == HUYoAguscC){yJRrOAKtxz = true;}
      else if(HUYoAguscC == gZjqPzjjZg){QOKAjzCyVC = true;}
      if(MUhbzEcbbE == iqXshIUnPn){SyNRRfaKuU = true;}
      else if(iqXshIUnPn == MUhbzEcbbE){NwCmAiEzMa = true;}
      if(LKVqQBBOhh == aMHWBasRuV){doYnbfknLa = true;}
      else if(aMHWBasRuV == LKVqQBBOhh){GtjfHfXtoR = true;}
      if(cutgmakFLO == JJIOZJPLMw){fxQeWxoJYK = true;}
      else if(JJIOZJPLMw == cutgmakFLO){LXWjMSURzK = true;}
      if(BbWIWiWMNT == UwkrhfTkPH){MAtkMyyFVb = true;}
      if(ELFelVDsaN == KlOQdtNCmZ){QnideIkdQh = true;}
      if(xVBrEQaBnY == ncxGsYhJTX){OWiWSUhitU = true;}
      while(UwkrhfTkPH == BbWIWiWMNT){oPRxBQIGpL = true;}
      while(KlOQdtNCmZ == KlOQdtNCmZ){lRJqjVeesE = true;}
      while(ncxGsYhJTX == ncxGsYhJTX){aIJDpoYRZh = true;}
      if(sJaTSebPnU == true){sJaTSebPnU = false;}
      if(HHBmLXurje == true){HHBmLXurje = false;}
      if(wMXmIrydyJ == true){wMXmIrydyJ = false;}
      if(yJRrOAKtxz == true){yJRrOAKtxz = false;}
      if(SyNRRfaKuU == true){SyNRRfaKuU = false;}
      if(doYnbfknLa == true){doYnbfknLa = false;}
      if(fxQeWxoJYK == true){fxQeWxoJYK = false;}
      if(MAtkMyyFVb == true){MAtkMyyFVb = false;}
      if(QnideIkdQh == true){QnideIkdQh = false;}
      if(OWiWSUhitU == true){OWiWSUhitU = false;}
      if(qRkjHcunbc == true){qRkjHcunbc = false;}
      if(geSjJrOmzO == true){geSjJrOmzO = false;}
      if(MKsqupRWRq == true){MKsqupRWRq = false;}
      if(QOKAjzCyVC == true){QOKAjzCyVC = false;}
      if(NwCmAiEzMa == true){NwCmAiEzMa = false;}
      if(GtjfHfXtoR == true){GtjfHfXtoR = false;}
      if(LXWjMSURzK == true){LXWjMSURzK = false;}
      if(oPRxBQIGpL == true){oPRxBQIGpL = false;}
      if(lRJqjVeesE == true){lRJqjVeesE = false;}
      if(aIJDpoYRZh == true){aIJDpoYRZh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RJHOPJILLH
{ 
  void ubKrPVYFwa()
  { 
      bool TfYTzuAuPp = false;
      bool nYfWQudhNb = false;
      bool wgTkaKysYF = false;
      bool euHLEoXtjn = false;
      bool puAxKKjUbo = false;
      bool ztTrumLnsn = false;
      bool wHWKLsRUSa = false;
      bool WixYkAgWZP = false;
      bool ZcQjFjaOPR = false;
      bool cjBuriYolR = false;
      bool sPCARPwuHt = false;
      bool GoNdOTplEa = false;
      bool RCEBxlhCgB = false;
      bool bqjIVKaQRp = false;
      bool nfHVKmWWgX = false;
      bool slkKzqKACf = false;
      bool gtNFRPFEHD = false;
      bool rZUOmkuipK = false;
      bool PKUIIpFYIe = false;
      bool zZNlIsRBDu = false;
      string DTirRMmKyd;
      string dALVcHEuCG;
      string almEISWgRl;
      string PHyMcJNqaq;
      string VuBTTXQHGp;
      string LHmCcRfdiz;
      string oFrLOVBzrT;
      string sNULkfjTjk;
      string COabaIUwjL;
      string ciHaBPCoEy;
      string VQPlwylaRw;
      string gLtywaeQkF;
      string AFPgpKGsJU;
      string cuOlOkzneb;
      string WsdmdQoIea;
      string klEzxPBiwl;
      string rrRxSlxIjK;
      string aplIiHbbCY;
      string VxOiiqpPny;
      string jQrrjdbgUq;
      if(DTirRMmKyd == VQPlwylaRw){TfYTzuAuPp = true;}
      else if(VQPlwylaRw == DTirRMmKyd){sPCARPwuHt = true;}
      if(dALVcHEuCG == gLtywaeQkF){nYfWQudhNb = true;}
      else if(gLtywaeQkF == dALVcHEuCG){GoNdOTplEa = true;}
      if(almEISWgRl == AFPgpKGsJU){wgTkaKysYF = true;}
      else if(AFPgpKGsJU == almEISWgRl){RCEBxlhCgB = true;}
      if(PHyMcJNqaq == cuOlOkzneb){euHLEoXtjn = true;}
      else if(cuOlOkzneb == PHyMcJNqaq){bqjIVKaQRp = true;}
      if(VuBTTXQHGp == WsdmdQoIea){puAxKKjUbo = true;}
      else if(WsdmdQoIea == VuBTTXQHGp){nfHVKmWWgX = true;}
      if(LHmCcRfdiz == klEzxPBiwl){ztTrumLnsn = true;}
      else if(klEzxPBiwl == LHmCcRfdiz){slkKzqKACf = true;}
      if(oFrLOVBzrT == rrRxSlxIjK){wHWKLsRUSa = true;}
      else if(rrRxSlxIjK == oFrLOVBzrT){gtNFRPFEHD = true;}
      if(sNULkfjTjk == aplIiHbbCY){WixYkAgWZP = true;}
      if(COabaIUwjL == VxOiiqpPny){ZcQjFjaOPR = true;}
      if(ciHaBPCoEy == jQrrjdbgUq){cjBuriYolR = true;}
      while(aplIiHbbCY == sNULkfjTjk){rZUOmkuipK = true;}
      while(VxOiiqpPny == VxOiiqpPny){PKUIIpFYIe = true;}
      while(jQrrjdbgUq == jQrrjdbgUq){zZNlIsRBDu = true;}
      if(TfYTzuAuPp == true){TfYTzuAuPp = false;}
      if(nYfWQudhNb == true){nYfWQudhNb = false;}
      if(wgTkaKysYF == true){wgTkaKysYF = false;}
      if(euHLEoXtjn == true){euHLEoXtjn = false;}
      if(puAxKKjUbo == true){puAxKKjUbo = false;}
      if(ztTrumLnsn == true){ztTrumLnsn = false;}
      if(wHWKLsRUSa == true){wHWKLsRUSa = false;}
      if(WixYkAgWZP == true){WixYkAgWZP = false;}
      if(ZcQjFjaOPR == true){ZcQjFjaOPR = false;}
      if(cjBuriYolR == true){cjBuriYolR = false;}
      if(sPCARPwuHt == true){sPCARPwuHt = false;}
      if(GoNdOTplEa == true){GoNdOTplEa = false;}
      if(RCEBxlhCgB == true){RCEBxlhCgB = false;}
      if(bqjIVKaQRp == true){bqjIVKaQRp = false;}
      if(nfHVKmWWgX == true){nfHVKmWWgX = false;}
      if(slkKzqKACf == true){slkKzqKACf = false;}
      if(gtNFRPFEHD == true){gtNFRPFEHD = false;}
      if(rZUOmkuipK == true){rZUOmkuipK = false;}
      if(PKUIIpFYIe == true){PKUIIpFYIe = false;}
      if(zZNlIsRBDu == true){zZNlIsRBDu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCQGNMBPNS
{ 
  void LnFOfYWfOQ()
  { 
      bool CiTJuKOuGB = false;
      bool WknGuUmoxi = false;
      bool kArafCRUXN = false;
      bool hXymAaeSLc = false;
      bool KbaFRhHHVd = false;
      bool tBShJBpscr = false;
      bool stXrSzlAGT = false;
      bool pUdTYJYmIy = false;
      bool uJztTgEQcy = false;
      bool jkoSjQEhmS = false;
      bool uGABnYWzJA = false;
      bool cDkexitcYk = false;
      bool tVXIiEeKjI = false;
      bool EqzoCoIyFt = false;
      bool JFGcVgAKVB = false;
      bool VaJBYZirRj = false;
      bool tLOBukDucI = false;
      bool ZwXdanOtmC = false;
      bool EUoildgyQb = false;
      bool FQfVAypFgj = false;
      string OHNyiBTVWF;
      string zRdjedQaHm;
      string hRNKXCOykL;
      string OxGeysTdKw;
      string OuTkoPprfM;
      string pQKmVxsCZg;
      string lVjKpBKylk;
      string KmPLXlycVH;
      string MWRYVymSIB;
      string zQDdJsLItn;
      string EqFtBDAzPi;
      string yPgSUPDKor;
      string NrpjltikBd;
      string apigCUQXXS;
      string xnCZCiijJt;
      string pBSBaMBVIG;
      string TPxlIIgzQz;
      string yflWuYoPgC;
      string KybHnZWgGo;
      string TuOQygqQQt;
      if(OHNyiBTVWF == EqFtBDAzPi){CiTJuKOuGB = true;}
      else if(EqFtBDAzPi == OHNyiBTVWF){uGABnYWzJA = true;}
      if(zRdjedQaHm == yPgSUPDKor){WknGuUmoxi = true;}
      else if(yPgSUPDKor == zRdjedQaHm){cDkexitcYk = true;}
      if(hRNKXCOykL == NrpjltikBd){kArafCRUXN = true;}
      else if(NrpjltikBd == hRNKXCOykL){tVXIiEeKjI = true;}
      if(OxGeysTdKw == apigCUQXXS){hXymAaeSLc = true;}
      else if(apigCUQXXS == OxGeysTdKw){EqzoCoIyFt = true;}
      if(OuTkoPprfM == xnCZCiijJt){KbaFRhHHVd = true;}
      else if(xnCZCiijJt == OuTkoPprfM){JFGcVgAKVB = true;}
      if(pQKmVxsCZg == pBSBaMBVIG){tBShJBpscr = true;}
      else if(pBSBaMBVIG == pQKmVxsCZg){VaJBYZirRj = true;}
      if(lVjKpBKylk == TPxlIIgzQz){stXrSzlAGT = true;}
      else if(TPxlIIgzQz == lVjKpBKylk){tLOBukDucI = true;}
      if(KmPLXlycVH == yflWuYoPgC){pUdTYJYmIy = true;}
      if(MWRYVymSIB == KybHnZWgGo){uJztTgEQcy = true;}
      if(zQDdJsLItn == TuOQygqQQt){jkoSjQEhmS = true;}
      while(yflWuYoPgC == KmPLXlycVH){ZwXdanOtmC = true;}
      while(KybHnZWgGo == KybHnZWgGo){EUoildgyQb = true;}
      while(TuOQygqQQt == TuOQygqQQt){FQfVAypFgj = true;}
      if(CiTJuKOuGB == true){CiTJuKOuGB = false;}
      if(WknGuUmoxi == true){WknGuUmoxi = false;}
      if(kArafCRUXN == true){kArafCRUXN = false;}
      if(hXymAaeSLc == true){hXymAaeSLc = false;}
      if(KbaFRhHHVd == true){KbaFRhHHVd = false;}
      if(tBShJBpscr == true){tBShJBpscr = false;}
      if(stXrSzlAGT == true){stXrSzlAGT = false;}
      if(pUdTYJYmIy == true){pUdTYJYmIy = false;}
      if(uJztTgEQcy == true){uJztTgEQcy = false;}
      if(jkoSjQEhmS == true){jkoSjQEhmS = false;}
      if(uGABnYWzJA == true){uGABnYWzJA = false;}
      if(cDkexitcYk == true){cDkexitcYk = false;}
      if(tVXIiEeKjI == true){tVXIiEeKjI = false;}
      if(EqzoCoIyFt == true){EqzoCoIyFt = false;}
      if(JFGcVgAKVB == true){JFGcVgAKVB = false;}
      if(VaJBYZirRj == true){VaJBYZirRj = false;}
      if(tLOBukDucI == true){tLOBukDucI = false;}
      if(ZwXdanOtmC == true){ZwXdanOtmC = false;}
      if(EUoildgyQb == true){EUoildgyQb = false;}
      if(FQfVAypFgj == true){FQfVAypFgj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LQMWVVSPCR
{ 
  void HotIoKRnIB()
  { 
      bool harBeMLcHx = false;
      bool JwVhdaGltD = false;
      bool CfYLRqbZrc = false;
      bool daqcQiKRDc = false;
      bool rgjYzXCHDV = false;
      bool XVcjjBCgjn = false;
      bool kkjdShErRu = false;
      bool PohRKUwzLs = false;
      bool nUWWFHyHrP = false;
      bool gdgPrGwFGR = false;
      bool TKoIFhnLYP = false;
      bool FCVpAPONYK = false;
      bool jxzCOlHSZE = false;
      bool XpstZdeOQW = false;
      bool TlicJdIpPb = false;
      bool rigugWLmsT = false;
      bool aUlUqPIaQV = false;
      bool jAxBpxOVrj = false;
      bool dQDxMoIxMD = false;
      bool RrUxuyANlt = false;
      string xMDoqJordr;
      string UdnEpjomFK;
      string zqAxSGWoTm;
      string xbJjwyeWHG;
      string UZbUrjGKea;
      string OMyuHFLGVj;
      string lzYqusUDHr;
      string FRfypZOfEh;
      string AMKrYjcNcq;
      string lYBXUUAkYz;
      string PDCmVwgzFg;
      string peBmjZofRK;
      string PGaQFgQHdU;
      string YdGFSxKWWb;
      string DcHuAGWNnt;
      string eUSOiIblgn;
      string eZVjHMYuUl;
      string PRIpGlzeQy;
      string JDSipEKrVJ;
      string UXphxdHXmm;
      if(xMDoqJordr == PDCmVwgzFg){harBeMLcHx = true;}
      else if(PDCmVwgzFg == xMDoqJordr){TKoIFhnLYP = true;}
      if(UdnEpjomFK == peBmjZofRK){JwVhdaGltD = true;}
      else if(peBmjZofRK == UdnEpjomFK){FCVpAPONYK = true;}
      if(zqAxSGWoTm == PGaQFgQHdU){CfYLRqbZrc = true;}
      else if(PGaQFgQHdU == zqAxSGWoTm){jxzCOlHSZE = true;}
      if(xbJjwyeWHG == YdGFSxKWWb){daqcQiKRDc = true;}
      else if(YdGFSxKWWb == xbJjwyeWHG){XpstZdeOQW = true;}
      if(UZbUrjGKea == DcHuAGWNnt){rgjYzXCHDV = true;}
      else if(DcHuAGWNnt == UZbUrjGKea){TlicJdIpPb = true;}
      if(OMyuHFLGVj == eUSOiIblgn){XVcjjBCgjn = true;}
      else if(eUSOiIblgn == OMyuHFLGVj){rigugWLmsT = true;}
      if(lzYqusUDHr == eZVjHMYuUl){kkjdShErRu = true;}
      else if(eZVjHMYuUl == lzYqusUDHr){aUlUqPIaQV = true;}
      if(FRfypZOfEh == PRIpGlzeQy){PohRKUwzLs = true;}
      if(AMKrYjcNcq == JDSipEKrVJ){nUWWFHyHrP = true;}
      if(lYBXUUAkYz == UXphxdHXmm){gdgPrGwFGR = true;}
      while(PRIpGlzeQy == FRfypZOfEh){jAxBpxOVrj = true;}
      while(JDSipEKrVJ == JDSipEKrVJ){dQDxMoIxMD = true;}
      while(UXphxdHXmm == UXphxdHXmm){RrUxuyANlt = true;}
      if(harBeMLcHx == true){harBeMLcHx = false;}
      if(JwVhdaGltD == true){JwVhdaGltD = false;}
      if(CfYLRqbZrc == true){CfYLRqbZrc = false;}
      if(daqcQiKRDc == true){daqcQiKRDc = false;}
      if(rgjYzXCHDV == true){rgjYzXCHDV = false;}
      if(XVcjjBCgjn == true){XVcjjBCgjn = false;}
      if(kkjdShErRu == true){kkjdShErRu = false;}
      if(PohRKUwzLs == true){PohRKUwzLs = false;}
      if(nUWWFHyHrP == true){nUWWFHyHrP = false;}
      if(gdgPrGwFGR == true){gdgPrGwFGR = false;}
      if(TKoIFhnLYP == true){TKoIFhnLYP = false;}
      if(FCVpAPONYK == true){FCVpAPONYK = false;}
      if(jxzCOlHSZE == true){jxzCOlHSZE = false;}
      if(XpstZdeOQW == true){XpstZdeOQW = false;}
      if(TlicJdIpPb == true){TlicJdIpPb = false;}
      if(rigugWLmsT == true){rigugWLmsT = false;}
      if(aUlUqPIaQV == true){aUlUqPIaQV = false;}
      if(jAxBpxOVrj == true){jAxBpxOVrj = false;}
      if(dQDxMoIxMD == true){dQDxMoIxMD = false;}
      if(RrUxuyANlt == true){RrUxuyANlt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KREHIMVSRC
{ 
  void kNmZFhaxsI()
  { 
      bool jIZyDjlFDI = false;
      bool SqpuKUGbPN = false;
      bool DCAocqQFZx = false;
      bool QPEBeEYIoI = false;
      bool nHzabPbZly = false;
      bool WzcAXhHkUL = false;
      bool TffFrDmoQF = false;
      bool uymHYwDYNN = false;
      bool PpTaaQlDcx = false;
      bool wnmcoIbsiX = false;
      bool clIfCXMVbb = false;
      bool eiWHwcLEeb = false;
      bool RiMTJHKJRP = false;
      bool UJpokdhmXC = false;
      bool DPaASNQfgL = false;
      bool wWNGGsZoVu = false;
      bool NDDMGUrgWS = false;
      bool uYfbXBILBw = false;
      bool pebFSywiiq = false;
      bool ErQcoALOtx = false;
      string oEioCmATbp;
      string bhHeUnHMyH;
      string EWoiaDMmza;
      string bNAgmpQeki;
      string CefKFSFirB;
      string HfobbRPANz;
      string ZNUANNhZrd;
      string WbbOEYpddH;
      string xdtyTuXYFU;
      string aQRkJoKewq;
      string kfqNdeEaWC;
      string blWGCwSVgR;
      string pJUWDGKpFO;
      string OKglVRlfTn;
      string qxBCsnsKiM;
      string WnydBbKTKW;
      string UNUInQEkjj;
      string JlCsarISdO;
      string MzHrraMCjt;
      string HRVwTcbsOb;
      if(oEioCmATbp == kfqNdeEaWC){jIZyDjlFDI = true;}
      else if(kfqNdeEaWC == oEioCmATbp){clIfCXMVbb = true;}
      if(bhHeUnHMyH == blWGCwSVgR){SqpuKUGbPN = true;}
      else if(blWGCwSVgR == bhHeUnHMyH){eiWHwcLEeb = true;}
      if(EWoiaDMmza == pJUWDGKpFO){DCAocqQFZx = true;}
      else if(pJUWDGKpFO == EWoiaDMmza){RiMTJHKJRP = true;}
      if(bNAgmpQeki == OKglVRlfTn){QPEBeEYIoI = true;}
      else if(OKglVRlfTn == bNAgmpQeki){UJpokdhmXC = true;}
      if(CefKFSFirB == qxBCsnsKiM){nHzabPbZly = true;}
      else if(qxBCsnsKiM == CefKFSFirB){DPaASNQfgL = true;}
      if(HfobbRPANz == WnydBbKTKW){WzcAXhHkUL = true;}
      else if(WnydBbKTKW == HfobbRPANz){wWNGGsZoVu = true;}
      if(ZNUANNhZrd == UNUInQEkjj){TffFrDmoQF = true;}
      else if(UNUInQEkjj == ZNUANNhZrd){NDDMGUrgWS = true;}
      if(WbbOEYpddH == JlCsarISdO){uymHYwDYNN = true;}
      if(xdtyTuXYFU == MzHrraMCjt){PpTaaQlDcx = true;}
      if(aQRkJoKewq == HRVwTcbsOb){wnmcoIbsiX = true;}
      while(JlCsarISdO == WbbOEYpddH){uYfbXBILBw = true;}
      while(MzHrraMCjt == MzHrraMCjt){pebFSywiiq = true;}
      while(HRVwTcbsOb == HRVwTcbsOb){ErQcoALOtx = true;}
      if(jIZyDjlFDI == true){jIZyDjlFDI = false;}
      if(SqpuKUGbPN == true){SqpuKUGbPN = false;}
      if(DCAocqQFZx == true){DCAocqQFZx = false;}
      if(QPEBeEYIoI == true){QPEBeEYIoI = false;}
      if(nHzabPbZly == true){nHzabPbZly = false;}
      if(WzcAXhHkUL == true){WzcAXhHkUL = false;}
      if(TffFrDmoQF == true){TffFrDmoQF = false;}
      if(uymHYwDYNN == true){uymHYwDYNN = false;}
      if(PpTaaQlDcx == true){PpTaaQlDcx = false;}
      if(wnmcoIbsiX == true){wnmcoIbsiX = false;}
      if(clIfCXMVbb == true){clIfCXMVbb = false;}
      if(eiWHwcLEeb == true){eiWHwcLEeb = false;}
      if(RiMTJHKJRP == true){RiMTJHKJRP = false;}
      if(UJpokdhmXC == true){UJpokdhmXC = false;}
      if(DPaASNQfgL == true){DPaASNQfgL = false;}
      if(wWNGGsZoVu == true){wWNGGsZoVu = false;}
      if(NDDMGUrgWS == true){NDDMGUrgWS = false;}
      if(uYfbXBILBw == true){uYfbXBILBw = false;}
      if(pebFSywiiq == true){pebFSywiiq = false;}
      if(ErQcoALOtx == true){ErQcoALOtx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NTCAOONKOS
{ 
  void OrGRgREhVa()
  { 
      bool RyrrrRxQFi = false;
      bool rlYuAKruoi = false;
      bool rzSFYsxpTD = false;
      bool rWictKBqpg = false;
      bool YfwxjoEwLg = false;
      bool hHpUQRfmTz = false;
      bool UGwCqVCwBp = false;
      bool IAFIJLDVVj = false;
      bool nAelUkgOLb = false;
      bool eOXpMSitGO = false;
      bool lIuUYhCgKF = false;
      bool OJRiKUaKgF = false;
      bool nnkZLtbOup = false;
      bool bIPHyfFKNm = false;
      bool izDFMUxofr = false;
      bool rYNAZyWUId = false;
      bool FmkUdGsKke = false;
      bool PPxsWnjeNq = false;
      bool xmiDyCuPgz = false;
      bool IjBihuNibG = false;
      string sPcnlZtjQj;
      string syjkrBZlyf;
      string fUUCrRdPWp;
      string pKMFlDjaOX;
      string bkKNmCytbi;
      string WeCyVYuZuT;
      string weMathkdyn;
      string RzXZDtJGPo;
      string TjnnTKHOiN;
      string IJftbxYjTE;
      string RTumRXGbta;
      string OnKFALpYHi;
      string aWtjfHTdyG;
      string VZmKXAnAVu;
      string EfTIyTyZsP;
      string HzbkduYKHJ;
      string DcdnFoBzhA;
      string WoCLetCllL;
      string JsjhyVxCgb;
      string adrLraCeDJ;
      if(sPcnlZtjQj == RTumRXGbta){RyrrrRxQFi = true;}
      else if(RTumRXGbta == sPcnlZtjQj){lIuUYhCgKF = true;}
      if(syjkrBZlyf == OnKFALpYHi){rlYuAKruoi = true;}
      else if(OnKFALpYHi == syjkrBZlyf){OJRiKUaKgF = true;}
      if(fUUCrRdPWp == aWtjfHTdyG){rzSFYsxpTD = true;}
      else if(aWtjfHTdyG == fUUCrRdPWp){nnkZLtbOup = true;}
      if(pKMFlDjaOX == VZmKXAnAVu){rWictKBqpg = true;}
      else if(VZmKXAnAVu == pKMFlDjaOX){bIPHyfFKNm = true;}
      if(bkKNmCytbi == EfTIyTyZsP){YfwxjoEwLg = true;}
      else if(EfTIyTyZsP == bkKNmCytbi){izDFMUxofr = true;}
      if(WeCyVYuZuT == HzbkduYKHJ){hHpUQRfmTz = true;}
      else if(HzbkduYKHJ == WeCyVYuZuT){rYNAZyWUId = true;}
      if(weMathkdyn == DcdnFoBzhA){UGwCqVCwBp = true;}
      else if(DcdnFoBzhA == weMathkdyn){FmkUdGsKke = true;}
      if(RzXZDtJGPo == WoCLetCllL){IAFIJLDVVj = true;}
      if(TjnnTKHOiN == JsjhyVxCgb){nAelUkgOLb = true;}
      if(IJftbxYjTE == adrLraCeDJ){eOXpMSitGO = true;}
      while(WoCLetCllL == RzXZDtJGPo){PPxsWnjeNq = true;}
      while(JsjhyVxCgb == JsjhyVxCgb){xmiDyCuPgz = true;}
      while(adrLraCeDJ == adrLraCeDJ){IjBihuNibG = true;}
      if(RyrrrRxQFi == true){RyrrrRxQFi = false;}
      if(rlYuAKruoi == true){rlYuAKruoi = false;}
      if(rzSFYsxpTD == true){rzSFYsxpTD = false;}
      if(rWictKBqpg == true){rWictKBqpg = false;}
      if(YfwxjoEwLg == true){YfwxjoEwLg = false;}
      if(hHpUQRfmTz == true){hHpUQRfmTz = false;}
      if(UGwCqVCwBp == true){UGwCqVCwBp = false;}
      if(IAFIJLDVVj == true){IAFIJLDVVj = false;}
      if(nAelUkgOLb == true){nAelUkgOLb = false;}
      if(eOXpMSitGO == true){eOXpMSitGO = false;}
      if(lIuUYhCgKF == true){lIuUYhCgKF = false;}
      if(OJRiKUaKgF == true){OJRiKUaKgF = false;}
      if(nnkZLtbOup == true){nnkZLtbOup = false;}
      if(bIPHyfFKNm == true){bIPHyfFKNm = false;}
      if(izDFMUxofr == true){izDFMUxofr = false;}
      if(rYNAZyWUId == true){rYNAZyWUId = false;}
      if(FmkUdGsKke == true){FmkUdGsKke = false;}
      if(PPxsWnjeNq == true){PPxsWnjeNq = false;}
      if(xmiDyCuPgz == true){xmiDyCuPgz = false;}
      if(IjBihuNibG == true){IjBihuNibG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SQOQDUHKPB
{ 
  void iMCDhfeqXP()
  { 
      bool dkMCarMheO = false;
      bool KzRmECGRPL = false;
      bool hXopFxcaFn = false;
      bool TNUTauUSif = false;
      bool uphIYyCsuj = false;
      bool XuaALFwVxc = false;
      bool OkcpuwdyMI = false;
      bool gnhiQqpfRG = false;
      bool uieUPYlTHU = false;
      bool zzVFQJMqNb = false;
      bool TEgmCjMqjT = false;
      bool PPEphfFHaW = false;
      bool KKprJhRcSH = false;
      bool ezSomqCrSf = false;
      bool LtjnEiufXk = false;
      bool DFQpRJNodU = false;
      bool SjYboPxODq = false;
      bool cNotKPZBmZ = false;
      bool llEgEZibXd = false;
      bool cNOxNbVHyo = false;
      string HWExlOukFN;
      string GpOOTyRIkL;
      string GPrpZeDcXP;
      string bQOEwoqjuV;
      string CLdJGaELqX;
      string mRuVJqdNXH;
      string KSMpkpbJSe;
      string HhNPItliiy;
      string ZrkAbKUruE;
      string KcMmLizmXQ;
      string zurMPFDfNO;
      string EueZhRhLNZ;
      string UiNNTeUaDZ;
      string uyKSzezYkW;
      string HoefAOxmFs;
      string BmZxuPgerk;
      string jbbnTGkMZC;
      string RJaqSfEhNE;
      string ghVKXHYMWi;
      string xUfzleMqMs;
      if(HWExlOukFN == zurMPFDfNO){dkMCarMheO = true;}
      else if(zurMPFDfNO == HWExlOukFN){TEgmCjMqjT = true;}
      if(GpOOTyRIkL == EueZhRhLNZ){KzRmECGRPL = true;}
      else if(EueZhRhLNZ == GpOOTyRIkL){PPEphfFHaW = true;}
      if(GPrpZeDcXP == UiNNTeUaDZ){hXopFxcaFn = true;}
      else if(UiNNTeUaDZ == GPrpZeDcXP){KKprJhRcSH = true;}
      if(bQOEwoqjuV == uyKSzezYkW){TNUTauUSif = true;}
      else if(uyKSzezYkW == bQOEwoqjuV){ezSomqCrSf = true;}
      if(CLdJGaELqX == HoefAOxmFs){uphIYyCsuj = true;}
      else if(HoefAOxmFs == CLdJGaELqX){LtjnEiufXk = true;}
      if(mRuVJqdNXH == BmZxuPgerk){XuaALFwVxc = true;}
      else if(BmZxuPgerk == mRuVJqdNXH){DFQpRJNodU = true;}
      if(KSMpkpbJSe == jbbnTGkMZC){OkcpuwdyMI = true;}
      else if(jbbnTGkMZC == KSMpkpbJSe){SjYboPxODq = true;}
      if(HhNPItliiy == RJaqSfEhNE){gnhiQqpfRG = true;}
      if(ZrkAbKUruE == ghVKXHYMWi){uieUPYlTHU = true;}
      if(KcMmLizmXQ == xUfzleMqMs){zzVFQJMqNb = true;}
      while(RJaqSfEhNE == HhNPItliiy){cNotKPZBmZ = true;}
      while(ghVKXHYMWi == ghVKXHYMWi){llEgEZibXd = true;}
      while(xUfzleMqMs == xUfzleMqMs){cNOxNbVHyo = true;}
      if(dkMCarMheO == true){dkMCarMheO = false;}
      if(KzRmECGRPL == true){KzRmECGRPL = false;}
      if(hXopFxcaFn == true){hXopFxcaFn = false;}
      if(TNUTauUSif == true){TNUTauUSif = false;}
      if(uphIYyCsuj == true){uphIYyCsuj = false;}
      if(XuaALFwVxc == true){XuaALFwVxc = false;}
      if(OkcpuwdyMI == true){OkcpuwdyMI = false;}
      if(gnhiQqpfRG == true){gnhiQqpfRG = false;}
      if(uieUPYlTHU == true){uieUPYlTHU = false;}
      if(zzVFQJMqNb == true){zzVFQJMqNb = false;}
      if(TEgmCjMqjT == true){TEgmCjMqjT = false;}
      if(PPEphfFHaW == true){PPEphfFHaW = false;}
      if(KKprJhRcSH == true){KKprJhRcSH = false;}
      if(ezSomqCrSf == true){ezSomqCrSf = false;}
      if(LtjnEiufXk == true){LtjnEiufXk = false;}
      if(DFQpRJNodU == true){DFQpRJNodU = false;}
      if(SjYboPxODq == true){SjYboPxODq = false;}
      if(cNotKPZBmZ == true){cNotKPZBmZ = false;}
      if(llEgEZibXd == true){llEgEZibXd = false;}
      if(cNOxNbVHyo == true){cNOxNbVHyo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EIKXLHYCXS
{ 
  void KpHCurwDRa()
  { 
      bool NtQyhiQSDT = false;
      bool MZYkotyRDM = false;
      bool gqgFkoCtYI = false;
      bool HllQrySYWz = false;
      bool NJSocdrVph = false;
      bool gtIDBVNKMs = false;
      bool gVsuLZnHrq = false;
      bool aYuDyXXrcH = false;
      bool wgEqbNdiPV = false;
      bool kIMdSqPXcD = false;
      bool okcyGHzFEc = false;
      bool yUhEwARBSy = false;
      bool uEqWFSLRjG = false;
      bool HAOYRKEFkT = false;
      bool OXdmXPaHgS = false;
      bool ZNEeHktGrm = false;
      bool wgUyUxGIlk = false;
      bool uLQzjXZEyp = false;
      bool rEkRfsujQg = false;
      bool QyNxXgCfRZ = false;
      string QURjUNFLCG;
      string qLNOOJVSNy;
      string AnxlcgLetN;
      string joBjYcFPyl;
      string XyQCuTOFKR;
      string fCqnPbXfGn;
      string BZRoVCKcol;
      string EFUbZCXtqJ;
      string RGUbghyMUx;
      string EZJJjyfbfs;
      string IkQXNagOON;
      string EcnwVuFoHn;
      string DxIrgdwLrb;
      string VuOyAfowOG;
      string AiyGrbkMmn;
      string rqTqoKbYpi;
      string dVWlqJOpuo;
      string GIZBmUyCzF;
      string sjXEiebWJo;
      string DQGfbeMLPi;
      if(QURjUNFLCG == IkQXNagOON){NtQyhiQSDT = true;}
      else if(IkQXNagOON == QURjUNFLCG){okcyGHzFEc = true;}
      if(qLNOOJVSNy == EcnwVuFoHn){MZYkotyRDM = true;}
      else if(EcnwVuFoHn == qLNOOJVSNy){yUhEwARBSy = true;}
      if(AnxlcgLetN == DxIrgdwLrb){gqgFkoCtYI = true;}
      else if(DxIrgdwLrb == AnxlcgLetN){uEqWFSLRjG = true;}
      if(joBjYcFPyl == VuOyAfowOG){HllQrySYWz = true;}
      else if(VuOyAfowOG == joBjYcFPyl){HAOYRKEFkT = true;}
      if(XyQCuTOFKR == AiyGrbkMmn){NJSocdrVph = true;}
      else if(AiyGrbkMmn == XyQCuTOFKR){OXdmXPaHgS = true;}
      if(fCqnPbXfGn == rqTqoKbYpi){gtIDBVNKMs = true;}
      else if(rqTqoKbYpi == fCqnPbXfGn){ZNEeHktGrm = true;}
      if(BZRoVCKcol == dVWlqJOpuo){gVsuLZnHrq = true;}
      else if(dVWlqJOpuo == BZRoVCKcol){wgUyUxGIlk = true;}
      if(EFUbZCXtqJ == GIZBmUyCzF){aYuDyXXrcH = true;}
      if(RGUbghyMUx == sjXEiebWJo){wgEqbNdiPV = true;}
      if(EZJJjyfbfs == DQGfbeMLPi){kIMdSqPXcD = true;}
      while(GIZBmUyCzF == EFUbZCXtqJ){uLQzjXZEyp = true;}
      while(sjXEiebWJo == sjXEiebWJo){rEkRfsujQg = true;}
      while(DQGfbeMLPi == DQGfbeMLPi){QyNxXgCfRZ = true;}
      if(NtQyhiQSDT == true){NtQyhiQSDT = false;}
      if(MZYkotyRDM == true){MZYkotyRDM = false;}
      if(gqgFkoCtYI == true){gqgFkoCtYI = false;}
      if(HllQrySYWz == true){HllQrySYWz = false;}
      if(NJSocdrVph == true){NJSocdrVph = false;}
      if(gtIDBVNKMs == true){gtIDBVNKMs = false;}
      if(gVsuLZnHrq == true){gVsuLZnHrq = false;}
      if(aYuDyXXrcH == true){aYuDyXXrcH = false;}
      if(wgEqbNdiPV == true){wgEqbNdiPV = false;}
      if(kIMdSqPXcD == true){kIMdSqPXcD = false;}
      if(okcyGHzFEc == true){okcyGHzFEc = false;}
      if(yUhEwARBSy == true){yUhEwARBSy = false;}
      if(uEqWFSLRjG == true){uEqWFSLRjG = false;}
      if(HAOYRKEFkT == true){HAOYRKEFkT = false;}
      if(OXdmXPaHgS == true){OXdmXPaHgS = false;}
      if(ZNEeHktGrm == true){ZNEeHktGrm = false;}
      if(wgUyUxGIlk == true){wgUyUxGIlk = false;}
      if(uLQzjXZEyp == true){uLQzjXZEyp = false;}
      if(rEkRfsujQg == true){rEkRfsujQg = false;}
      if(QyNxXgCfRZ == true){QyNxXgCfRZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDNCCDZKXP
{ 
  void IgwgqcTCPi()
  { 
      bool jgwLJqwAuV = false;
      bool jsMTfMfmKY = false;
      bool hreGmLXkhh = false;
      bool ejcfynECBD = false;
      bool HOHkMVEuES = false;
      bool gLLEyrBpXy = false;
      bool TKRMpAPfUq = false;
      bool HclHRSjstQ = false;
      bool HcfPBTYYhG = false;
      bool lOdDjwxtuM = false;
      bool GYZMKDYDle = false;
      bool HIuGppeCLW = false;
      bool aqxNFsziWU = false;
      bool VpyhKhCSEx = false;
      bool tUlDydSXMs = false;
      bool RuiXkOaMHR = false;
      bool EpgRJRJMwH = false;
      bool nLxObGFtPa = false;
      bool ZaVdCZGZww = false;
      bool GpKmrDnTsf = false;
      string JowiuqTGhk;
      string ShWbdkpbnY;
      string KiMXdERhUR;
      string FyrEfwjwVh;
      string SMjZsQeLzr;
      string JcEkxZbXEp;
      string ZkkPfTpSuh;
      string BsGGFxymeN;
      string ZFhcIctHGF;
      string TMqeHgaUsY;
      string ZLPQpPVxez;
      string bnrqQTDIGC;
      string ZiMpOoBbzY;
      string WdsGmNpQls;
      string HwbGdeTANm;
      string dSNqyqyYCB;
      string NtyFcxtlDC;
      string clVNucGFMi;
      string VBNLuDPCHw;
      string OROkeMyVcf;
      if(JowiuqTGhk == ZLPQpPVxez){jgwLJqwAuV = true;}
      else if(ZLPQpPVxez == JowiuqTGhk){GYZMKDYDle = true;}
      if(ShWbdkpbnY == bnrqQTDIGC){jsMTfMfmKY = true;}
      else if(bnrqQTDIGC == ShWbdkpbnY){HIuGppeCLW = true;}
      if(KiMXdERhUR == ZiMpOoBbzY){hreGmLXkhh = true;}
      else if(ZiMpOoBbzY == KiMXdERhUR){aqxNFsziWU = true;}
      if(FyrEfwjwVh == WdsGmNpQls){ejcfynECBD = true;}
      else if(WdsGmNpQls == FyrEfwjwVh){VpyhKhCSEx = true;}
      if(SMjZsQeLzr == HwbGdeTANm){HOHkMVEuES = true;}
      else if(HwbGdeTANm == SMjZsQeLzr){tUlDydSXMs = true;}
      if(JcEkxZbXEp == dSNqyqyYCB){gLLEyrBpXy = true;}
      else if(dSNqyqyYCB == JcEkxZbXEp){RuiXkOaMHR = true;}
      if(ZkkPfTpSuh == NtyFcxtlDC){TKRMpAPfUq = true;}
      else if(NtyFcxtlDC == ZkkPfTpSuh){EpgRJRJMwH = true;}
      if(BsGGFxymeN == clVNucGFMi){HclHRSjstQ = true;}
      if(ZFhcIctHGF == VBNLuDPCHw){HcfPBTYYhG = true;}
      if(TMqeHgaUsY == OROkeMyVcf){lOdDjwxtuM = true;}
      while(clVNucGFMi == BsGGFxymeN){nLxObGFtPa = true;}
      while(VBNLuDPCHw == VBNLuDPCHw){ZaVdCZGZww = true;}
      while(OROkeMyVcf == OROkeMyVcf){GpKmrDnTsf = true;}
      if(jgwLJqwAuV == true){jgwLJqwAuV = false;}
      if(jsMTfMfmKY == true){jsMTfMfmKY = false;}
      if(hreGmLXkhh == true){hreGmLXkhh = false;}
      if(ejcfynECBD == true){ejcfynECBD = false;}
      if(HOHkMVEuES == true){HOHkMVEuES = false;}
      if(gLLEyrBpXy == true){gLLEyrBpXy = false;}
      if(TKRMpAPfUq == true){TKRMpAPfUq = false;}
      if(HclHRSjstQ == true){HclHRSjstQ = false;}
      if(HcfPBTYYhG == true){HcfPBTYYhG = false;}
      if(lOdDjwxtuM == true){lOdDjwxtuM = false;}
      if(GYZMKDYDle == true){GYZMKDYDle = false;}
      if(HIuGppeCLW == true){HIuGppeCLW = false;}
      if(aqxNFsziWU == true){aqxNFsziWU = false;}
      if(VpyhKhCSEx == true){VpyhKhCSEx = false;}
      if(tUlDydSXMs == true){tUlDydSXMs = false;}
      if(RuiXkOaMHR == true){RuiXkOaMHR = false;}
      if(EpgRJRJMwH == true){EpgRJRJMwH = false;}
      if(nLxObGFtPa == true){nLxObGFtPa = false;}
      if(ZaVdCZGZww == true){ZaVdCZGZww = false;}
      if(GpKmrDnTsf == true){GpKmrDnTsf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BGDXVFBHUW
{ 
  void mLdntpiuix()
  { 
      bool DTqVoJFbpu = false;
      bool VxhNdCsGlW = false;
      bool MsFFXnsVAS = false;
      bool fykcMLasUw = false;
      bool bBRyxrKKLk = false;
      bool VLGRTKOlyB = false;
      bool PjbXOWMFBS = false;
      bool bzlpuLbGHe = false;
      bool ciJOwUrSIC = false;
      bool wnuSfrYsja = false;
      bool fFIrJWYQWI = false;
      bool hHdTXgZNbt = false;
      bool etwzVmDSJC = false;
      bool lhWfzXZREZ = false;
      bool uawzToKbuz = false;
      bool RLRowkIJVW = false;
      bool SGGTWAkxTz = false;
      bool HIICzDywfg = false;
      bool cbWKjZQhjN = false;
      bool OPugGnUbcS = false;
      string VQonGJmgel;
      string GFxstCJLqy;
      string TcXsIUdPPW;
      string BxPcBhADyU;
      string TsVNhiMRMJ;
      string KVSDerswfk;
      string eXRIkJpTqL;
      string CGNVdaHJKZ;
      string HMDGLfdLyJ;
      string oEWNowbMcX;
      string rsaAHDIwZD;
      string kikGcSUKwE;
      string fdUhWxizfg;
      string ytglgOkCzI;
      string XhltXGSQjW;
      string bQQXrNXrdJ;
      string UIPrFqCzYO;
      string gRLngxrZJP;
      string eSPJFhdIsT;
      string psYpnORsog;
      if(VQonGJmgel == rsaAHDIwZD){DTqVoJFbpu = true;}
      else if(rsaAHDIwZD == VQonGJmgel){fFIrJWYQWI = true;}
      if(GFxstCJLqy == kikGcSUKwE){VxhNdCsGlW = true;}
      else if(kikGcSUKwE == GFxstCJLqy){hHdTXgZNbt = true;}
      if(TcXsIUdPPW == fdUhWxizfg){MsFFXnsVAS = true;}
      else if(fdUhWxizfg == TcXsIUdPPW){etwzVmDSJC = true;}
      if(BxPcBhADyU == ytglgOkCzI){fykcMLasUw = true;}
      else if(ytglgOkCzI == BxPcBhADyU){lhWfzXZREZ = true;}
      if(TsVNhiMRMJ == XhltXGSQjW){bBRyxrKKLk = true;}
      else if(XhltXGSQjW == TsVNhiMRMJ){uawzToKbuz = true;}
      if(KVSDerswfk == bQQXrNXrdJ){VLGRTKOlyB = true;}
      else if(bQQXrNXrdJ == KVSDerswfk){RLRowkIJVW = true;}
      if(eXRIkJpTqL == UIPrFqCzYO){PjbXOWMFBS = true;}
      else if(UIPrFqCzYO == eXRIkJpTqL){SGGTWAkxTz = true;}
      if(CGNVdaHJKZ == gRLngxrZJP){bzlpuLbGHe = true;}
      if(HMDGLfdLyJ == eSPJFhdIsT){ciJOwUrSIC = true;}
      if(oEWNowbMcX == psYpnORsog){wnuSfrYsja = true;}
      while(gRLngxrZJP == CGNVdaHJKZ){HIICzDywfg = true;}
      while(eSPJFhdIsT == eSPJFhdIsT){cbWKjZQhjN = true;}
      while(psYpnORsog == psYpnORsog){OPugGnUbcS = true;}
      if(DTqVoJFbpu == true){DTqVoJFbpu = false;}
      if(VxhNdCsGlW == true){VxhNdCsGlW = false;}
      if(MsFFXnsVAS == true){MsFFXnsVAS = false;}
      if(fykcMLasUw == true){fykcMLasUw = false;}
      if(bBRyxrKKLk == true){bBRyxrKKLk = false;}
      if(VLGRTKOlyB == true){VLGRTKOlyB = false;}
      if(PjbXOWMFBS == true){PjbXOWMFBS = false;}
      if(bzlpuLbGHe == true){bzlpuLbGHe = false;}
      if(ciJOwUrSIC == true){ciJOwUrSIC = false;}
      if(wnuSfrYsja == true){wnuSfrYsja = false;}
      if(fFIrJWYQWI == true){fFIrJWYQWI = false;}
      if(hHdTXgZNbt == true){hHdTXgZNbt = false;}
      if(etwzVmDSJC == true){etwzVmDSJC = false;}
      if(lhWfzXZREZ == true){lhWfzXZREZ = false;}
      if(uawzToKbuz == true){uawzToKbuz = false;}
      if(RLRowkIJVW == true){RLRowkIJVW = false;}
      if(SGGTWAkxTz == true){SGGTWAkxTz = false;}
      if(HIICzDywfg == true){HIICzDywfg = false;}
      if(cbWKjZQhjN == true){cbWKjZQhjN = false;}
      if(OPugGnUbcS == true){OPugGnUbcS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HPAZZFYGMZ
{ 
  void yEbhuPJIpG()
  { 
      bool TQptbiHDTB = false;
      bool pCbgxCJuPb = false;
      bool IkQXKwWZKX = false;
      bool lQVMBxMLYN = false;
      bool dxEYrEKTyX = false;
      bool FjSGchASie = false;
      bool LhruOYfOfz = false;
      bool pxWCyKgreF = false;
      bool lDalSByPjS = false;
      bool xsbtBuFIKS = false;
      bool YumyhINQIR = false;
      bool BHndsIGGcM = false;
      bool aQdNCwVcAC = false;
      bool FXhLgpPcEK = false;
      bool nhHRQoFyAs = false;
      bool nyfxrHQZul = false;
      bool lkPFMdZbwC = false;
      bool sdCSYsJMxN = false;
      bool pWbHOGrjTZ = false;
      bool YphRXCRBEl = false;
      string MFBImNqFkk;
      string obmeYGFwyy;
      string oOLFNqlOnb;
      string FIRRqKoZmg;
      string LVQFuzZGMz;
      string mrYDuxtuuu;
      string acQIffKVmN;
      string QeJQlSyFJO;
      string QfBooMjNWt;
      string QtdqFhEIZP;
      string nETyhHhHQb;
      string znkgeuabTS;
      string uxyswWBSKE;
      string OpftZMMDGh;
      string ecwutbIxMK;
      string HcoHTqFZBL;
      string GPwMMJIqGR;
      string iXUkmSADyU;
      string ODGAwkBXZi;
      string GlBuaOfihk;
      if(MFBImNqFkk == nETyhHhHQb){TQptbiHDTB = true;}
      else if(nETyhHhHQb == MFBImNqFkk){YumyhINQIR = true;}
      if(obmeYGFwyy == znkgeuabTS){pCbgxCJuPb = true;}
      else if(znkgeuabTS == obmeYGFwyy){BHndsIGGcM = true;}
      if(oOLFNqlOnb == uxyswWBSKE){IkQXKwWZKX = true;}
      else if(uxyswWBSKE == oOLFNqlOnb){aQdNCwVcAC = true;}
      if(FIRRqKoZmg == OpftZMMDGh){lQVMBxMLYN = true;}
      else if(OpftZMMDGh == FIRRqKoZmg){FXhLgpPcEK = true;}
      if(LVQFuzZGMz == ecwutbIxMK){dxEYrEKTyX = true;}
      else if(ecwutbIxMK == LVQFuzZGMz){nhHRQoFyAs = true;}
      if(mrYDuxtuuu == HcoHTqFZBL){FjSGchASie = true;}
      else if(HcoHTqFZBL == mrYDuxtuuu){nyfxrHQZul = true;}
      if(acQIffKVmN == GPwMMJIqGR){LhruOYfOfz = true;}
      else if(GPwMMJIqGR == acQIffKVmN){lkPFMdZbwC = true;}
      if(QeJQlSyFJO == iXUkmSADyU){pxWCyKgreF = true;}
      if(QfBooMjNWt == ODGAwkBXZi){lDalSByPjS = true;}
      if(QtdqFhEIZP == GlBuaOfihk){xsbtBuFIKS = true;}
      while(iXUkmSADyU == QeJQlSyFJO){sdCSYsJMxN = true;}
      while(ODGAwkBXZi == ODGAwkBXZi){pWbHOGrjTZ = true;}
      while(GlBuaOfihk == GlBuaOfihk){YphRXCRBEl = true;}
      if(TQptbiHDTB == true){TQptbiHDTB = false;}
      if(pCbgxCJuPb == true){pCbgxCJuPb = false;}
      if(IkQXKwWZKX == true){IkQXKwWZKX = false;}
      if(lQVMBxMLYN == true){lQVMBxMLYN = false;}
      if(dxEYrEKTyX == true){dxEYrEKTyX = false;}
      if(FjSGchASie == true){FjSGchASie = false;}
      if(LhruOYfOfz == true){LhruOYfOfz = false;}
      if(pxWCyKgreF == true){pxWCyKgreF = false;}
      if(lDalSByPjS == true){lDalSByPjS = false;}
      if(xsbtBuFIKS == true){xsbtBuFIKS = false;}
      if(YumyhINQIR == true){YumyhINQIR = false;}
      if(BHndsIGGcM == true){BHndsIGGcM = false;}
      if(aQdNCwVcAC == true){aQdNCwVcAC = false;}
      if(FXhLgpPcEK == true){FXhLgpPcEK = false;}
      if(nhHRQoFyAs == true){nhHRQoFyAs = false;}
      if(nyfxrHQZul == true){nyfxrHQZul = false;}
      if(lkPFMdZbwC == true){lkPFMdZbwC = false;}
      if(sdCSYsJMxN == true){sdCSYsJMxN = false;}
      if(pWbHOGrjTZ == true){pWbHOGrjTZ = false;}
      if(YphRXCRBEl == true){YphRXCRBEl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IYFVVZMYAE
{ 
  void VzwSQblmiW()
  { 
      bool PlWahGPwnq = false;
      bool ghLYeqxxLh = false;
      bool HzQNuQKcng = false;
      bool PlnqOJEADd = false;
      bool qBXNdttWiO = false;
      bool mGtlqQVJeR = false;
      bool umHGattUKU = false;
      bool lwtgpFaCjA = false;
      bool VmtYtJqBAx = false;
      bool muUlhEsRli = false;
      bool AZMNbpLMuk = false;
      bool oSYeuIsiMR = false;
      bool CrUMhpbHzl = false;
      bool MJQAzuZfwE = false;
      bool xeFOITVopY = false;
      bool LKEUgIFAfk = false;
      bool NDNJYeCYeA = false;
      bool hMlITXlFDN = false;
      bool UlRZaBEuTq = false;
      bool pZzLpsRwpc = false;
      string ejtNkftFVD;
      string elAhrVpbtz;
      string toJWEQueDk;
      string WLAUnfTNKU;
      string iprMlDnpVh;
      string UPzHHpaXJT;
      string jPCjgTkesL;
      string BcQZPDwxjB;
      string bFJVQGMrNy;
      string FwEqjTnIeS;
      string RIwJfryYqD;
      string sdmHreGgSZ;
      string HsRuGFXZpw;
      string OmRQiTIzoY;
      string ImAJEbIwzE;
      string MHoFLYpBDa;
      string TXiuoFLVYX;
      string WGqsRTrIpd;
      string wbakjHxMFK;
      string cGwNFjDFTz;
      if(ejtNkftFVD == RIwJfryYqD){PlWahGPwnq = true;}
      else if(RIwJfryYqD == ejtNkftFVD){AZMNbpLMuk = true;}
      if(elAhrVpbtz == sdmHreGgSZ){ghLYeqxxLh = true;}
      else if(sdmHreGgSZ == elAhrVpbtz){oSYeuIsiMR = true;}
      if(toJWEQueDk == HsRuGFXZpw){HzQNuQKcng = true;}
      else if(HsRuGFXZpw == toJWEQueDk){CrUMhpbHzl = true;}
      if(WLAUnfTNKU == OmRQiTIzoY){PlnqOJEADd = true;}
      else if(OmRQiTIzoY == WLAUnfTNKU){MJQAzuZfwE = true;}
      if(iprMlDnpVh == ImAJEbIwzE){qBXNdttWiO = true;}
      else if(ImAJEbIwzE == iprMlDnpVh){xeFOITVopY = true;}
      if(UPzHHpaXJT == MHoFLYpBDa){mGtlqQVJeR = true;}
      else if(MHoFLYpBDa == UPzHHpaXJT){LKEUgIFAfk = true;}
      if(jPCjgTkesL == TXiuoFLVYX){umHGattUKU = true;}
      else if(TXiuoFLVYX == jPCjgTkesL){NDNJYeCYeA = true;}
      if(BcQZPDwxjB == WGqsRTrIpd){lwtgpFaCjA = true;}
      if(bFJVQGMrNy == wbakjHxMFK){VmtYtJqBAx = true;}
      if(FwEqjTnIeS == cGwNFjDFTz){muUlhEsRli = true;}
      while(WGqsRTrIpd == BcQZPDwxjB){hMlITXlFDN = true;}
      while(wbakjHxMFK == wbakjHxMFK){UlRZaBEuTq = true;}
      while(cGwNFjDFTz == cGwNFjDFTz){pZzLpsRwpc = true;}
      if(PlWahGPwnq == true){PlWahGPwnq = false;}
      if(ghLYeqxxLh == true){ghLYeqxxLh = false;}
      if(HzQNuQKcng == true){HzQNuQKcng = false;}
      if(PlnqOJEADd == true){PlnqOJEADd = false;}
      if(qBXNdttWiO == true){qBXNdttWiO = false;}
      if(mGtlqQVJeR == true){mGtlqQVJeR = false;}
      if(umHGattUKU == true){umHGattUKU = false;}
      if(lwtgpFaCjA == true){lwtgpFaCjA = false;}
      if(VmtYtJqBAx == true){VmtYtJqBAx = false;}
      if(muUlhEsRli == true){muUlhEsRli = false;}
      if(AZMNbpLMuk == true){AZMNbpLMuk = false;}
      if(oSYeuIsiMR == true){oSYeuIsiMR = false;}
      if(CrUMhpbHzl == true){CrUMhpbHzl = false;}
      if(MJQAzuZfwE == true){MJQAzuZfwE = false;}
      if(xeFOITVopY == true){xeFOITVopY = false;}
      if(LKEUgIFAfk == true){LKEUgIFAfk = false;}
      if(NDNJYeCYeA == true){NDNJYeCYeA = false;}
      if(hMlITXlFDN == true){hMlITXlFDN = false;}
      if(UlRZaBEuTq == true){UlRZaBEuTq = false;}
      if(pZzLpsRwpc == true){pZzLpsRwpc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QNNBVRPCIT
{ 
  void heGJUWxbpx()
  { 
      bool GLmFUiBiXV = false;
      bool MZDhHksYxV = false;
      bool QnNpwcPRDe = false;
      bool SeEtYqGPPS = false;
      bool TaAPkSgsZX = false;
      bool UARjlRyxJr = false;
      bool TjfsDhUJJP = false;
      bool dcIeCpnyFd = false;
      bool uVqeJSMUHG = false;
      bool sJFXyjtHLC = false;
      bool xWjJsrqmhu = false;
      bool dzrfwxrAjk = false;
      bool UABCWUWkfR = false;
      bool wglCfYlhlR = false;
      bool aZlLbsRZaB = false;
      bool rsWagwUglX = false;
      bool UGGPzxNozX = false;
      bool KJORJuOpZc = false;
      bool DxJdZCJKUi = false;
      bool DFuNxTSVMe = false;
      string ObFLcqliWs;
      string dNGcieggxk;
      string OhtPsmcxXi;
      string QqKlqHCoDu;
      string yCiQaVPOpE;
      string sIeQZfhoSp;
      string NoKnclDUla;
      string crdBmMzdnX;
      string XNGToHMsLK;
      string ZMWNhJqtmn;
      string RtcPaBeddN;
      string fEAtRzhqzV;
      string ZKJbBPVQTd;
      string VFpAFckprm;
      string chPydUMbui;
      string aAuRNHkAOL;
      string eOJAqaNAno;
      string NqyLsqtKxf;
      string DtVkCVJYly;
      string rkbgINYPGD;
      if(ObFLcqliWs == RtcPaBeddN){GLmFUiBiXV = true;}
      else if(RtcPaBeddN == ObFLcqliWs){xWjJsrqmhu = true;}
      if(dNGcieggxk == fEAtRzhqzV){MZDhHksYxV = true;}
      else if(fEAtRzhqzV == dNGcieggxk){dzrfwxrAjk = true;}
      if(OhtPsmcxXi == ZKJbBPVQTd){QnNpwcPRDe = true;}
      else if(ZKJbBPVQTd == OhtPsmcxXi){UABCWUWkfR = true;}
      if(QqKlqHCoDu == VFpAFckprm){SeEtYqGPPS = true;}
      else if(VFpAFckprm == QqKlqHCoDu){wglCfYlhlR = true;}
      if(yCiQaVPOpE == chPydUMbui){TaAPkSgsZX = true;}
      else if(chPydUMbui == yCiQaVPOpE){aZlLbsRZaB = true;}
      if(sIeQZfhoSp == aAuRNHkAOL){UARjlRyxJr = true;}
      else if(aAuRNHkAOL == sIeQZfhoSp){rsWagwUglX = true;}
      if(NoKnclDUla == eOJAqaNAno){TjfsDhUJJP = true;}
      else if(eOJAqaNAno == NoKnclDUla){UGGPzxNozX = true;}
      if(crdBmMzdnX == NqyLsqtKxf){dcIeCpnyFd = true;}
      if(XNGToHMsLK == DtVkCVJYly){uVqeJSMUHG = true;}
      if(ZMWNhJqtmn == rkbgINYPGD){sJFXyjtHLC = true;}
      while(NqyLsqtKxf == crdBmMzdnX){KJORJuOpZc = true;}
      while(DtVkCVJYly == DtVkCVJYly){DxJdZCJKUi = true;}
      while(rkbgINYPGD == rkbgINYPGD){DFuNxTSVMe = true;}
      if(GLmFUiBiXV == true){GLmFUiBiXV = false;}
      if(MZDhHksYxV == true){MZDhHksYxV = false;}
      if(QnNpwcPRDe == true){QnNpwcPRDe = false;}
      if(SeEtYqGPPS == true){SeEtYqGPPS = false;}
      if(TaAPkSgsZX == true){TaAPkSgsZX = false;}
      if(UARjlRyxJr == true){UARjlRyxJr = false;}
      if(TjfsDhUJJP == true){TjfsDhUJJP = false;}
      if(dcIeCpnyFd == true){dcIeCpnyFd = false;}
      if(uVqeJSMUHG == true){uVqeJSMUHG = false;}
      if(sJFXyjtHLC == true){sJFXyjtHLC = false;}
      if(xWjJsrqmhu == true){xWjJsrqmhu = false;}
      if(dzrfwxrAjk == true){dzrfwxrAjk = false;}
      if(UABCWUWkfR == true){UABCWUWkfR = false;}
      if(wglCfYlhlR == true){wglCfYlhlR = false;}
      if(aZlLbsRZaB == true){aZlLbsRZaB = false;}
      if(rsWagwUglX == true){rsWagwUglX = false;}
      if(UGGPzxNozX == true){UGGPzxNozX = false;}
      if(KJORJuOpZc == true){KJORJuOpZc = false;}
      if(DxJdZCJKUi == true){DxJdZCJKUi = false;}
      if(DFuNxTSVMe == true){DFuNxTSVMe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SCXEQIAYLC
{ 
  void TSZPVdQaBq()
  { 
      bool baGijLWobF = false;
      bool eYiqKnuGho = false;
      bool UUCfBiaChB = false;
      bool IkmYoAuVrX = false;
      bool pExMaQWRuF = false;
      bool mWOAcGXZhB = false;
      bool jUHawskJCJ = false;
      bool rYNJzQWpFj = false;
      bool LJHbOkVluh = false;
      bool bVmqmUwWQg = false;
      bool fNOkNNJFBM = false;
      bool ihTypaNeML = false;
      bool WyOThWlWVd = false;
      bool TAYXExtVOA = false;
      bool bQkhztBnBM = false;
      bool HRJFKgyuDq = false;
      bool bljWsiIwtr = false;
      bool fqPLiGNfUm = false;
      bool UxVIVBpTNW = false;
      bool yzSXYpgNoP = false;
      string CiQYtOREUT;
      string BtOSuDQtCr;
      string AqikswMBFq;
      string jGlFxEFbGb;
      string OcEPkRgLmG;
      string YUKaRLAefx;
      string CQyciuHJVq;
      string xonadWlSAb;
      string PBNzSPwLml;
      string DauIZydbfp;
      string JXowIifjxu;
      string YgeDhACzKT;
      string ywVjmWsfBf;
      string rKmJRqLRqi;
      string iMOrMVwrZY;
      string weQMqMBFIk;
      string oAiRCOtUkp;
      string ojIajlhcWQ;
      string aBFbjMsZRF;
      string oGIFshdwpy;
      if(CiQYtOREUT == JXowIifjxu){baGijLWobF = true;}
      else if(JXowIifjxu == CiQYtOREUT){fNOkNNJFBM = true;}
      if(BtOSuDQtCr == YgeDhACzKT){eYiqKnuGho = true;}
      else if(YgeDhACzKT == BtOSuDQtCr){ihTypaNeML = true;}
      if(AqikswMBFq == ywVjmWsfBf){UUCfBiaChB = true;}
      else if(ywVjmWsfBf == AqikswMBFq){WyOThWlWVd = true;}
      if(jGlFxEFbGb == rKmJRqLRqi){IkmYoAuVrX = true;}
      else if(rKmJRqLRqi == jGlFxEFbGb){TAYXExtVOA = true;}
      if(OcEPkRgLmG == iMOrMVwrZY){pExMaQWRuF = true;}
      else if(iMOrMVwrZY == OcEPkRgLmG){bQkhztBnBM = true;}
      if(YUKaRLAefx == weQMqMBFIk){mWOAcGXZhB = true;}
      else if(weQMqMBFIk == YUKaRLAefx){HRJFKgyuDq = true;}
      if(CQyciuHJVq == oAiRCOtUkp){jUHawskJCJ = true;}
      else if(oAiRCOtUkp == CQyciuHJVq){bljWsiIwtr = true;}
      if(xonadWlSAb == ojIajlhcWQ){rYNJzQWpFj = true;}
      if(PBNzSPwLml == aBFbjMsZRF){LJHbOkVluh = true;}
      if(DauIZydbfp == oGIFshdwpy){bVmqmUwWQg = true;}
      while(ojIajlhcWQ == xonadWlSAb){fqPLiGNfUm = true;}
      while(aBFbjMsZRF == aBFbjMsZRF){UxVIVBpTNW = true;}
      while(oGIFshdwpy == oGIFshdwpy){yzSXYpgNoP = true;}
      if(baGijLWobF == true){baGijLWobF = false;}
      if(eYiqKnuGho == true){eYiqKnuGho = false;}
      if(UUCfBiaChB == true){UUCfBiaChB = false;}
      if(IkmYoAuVrX == true){IkmYoAuVrX = false;}
      if(pExMaQWRuF == true){pExMaQWRuF = false;}
      if(mWOAcGXZhB == true){mWOAcGXZhB = false;}
      if(jUHawskJCJ == true){jUHawskJCJ = false;}
      if(rYNJzQWpFj == true){rYNJzQWpFj = false;}
      if(LJHbOkVluh == true){LJHbOkVluh = false;}
      if(bVmqmUwWQg == true){bVmqmUwWQg = false;}
      if(fNOkNNJFBM == true){fNOkNNJFBM = false;}
      if(ihTypaNeML == true){ihTypaNeML = false;}
      if(WyOThWlWVd == true){WyOThWlWVd = false;}
      if(TAYXExtVOA == true){TAYXExtVOA = false;}
      if(bQkhztBnBM == true){bQkhztBnBM = false;}
      if(HRJFKgyuDq == true){HRJFKgyuDq = false;}
      if(bljWsiIwtr == true){bljWsiIwtr = false;}
      if(fqPLiGNfUm == true){fqPLiGNfUm = false;}
      if(UxVIVBpTNW == true){UxVIVBpTNW = false;}
      if(yzSXYpgNoP == true){yzSXYpgNoP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GZQMNPCRYB
{ 
  void XIVNABbdZf()
  { 
      bool uquckPKAQV = false;
      bool cAUauOlALA = false;
      bool UQppeXSbJI = false;
      bool MJTNoAMxJq = false;
      bool FdxdWYSCnU = false;
      bool NVpnrdAFyN = false;
      bool xhqHJSgGku = false;
      bool BoqUupTLSG = false;
      bool FPnntqSeVL = false;
      bool zHzwsWmoUD = false;
      bool qLRrSYeUsC = false;
      bool JnlqHhsCNR = false;
      bool zCkYutouaX = false;
      bool DepOPtxuVU = false;
      bool LykTCKVHnL = false;
      bool ckaDEoZsxY = false;
      bool iitUyexWaN = false;
      bool kxfsFBQRWj = false;
      bool XhHPtRDmKa = false;
      bool TEyxkcDPUW = false;
      string XYtIwqfYej;
      string sEXqpyNwuN;
      string PkbhUBaiED;
      string hiOBUnrDQJ;
      string uYTwSLtGXT;
      string cAaFsmxMmu;
      string QxTaCKpVVB;
      string GKelRqQfOJ;
      string GULkZgHIHh;
      string qfPVsyFssI;
      string VXjVNSUomC;
      string VQxdnukiAU;
      string CgNmKZtIrT;
      string lWlGnijoWH;
      string MSVFLZhlhx;
      string MVsYFnJwLm;
      string XMwTQyeqpE;
      string LwLrIjLIak;
      string rIauHPdNAz;
      string YmdiiAWCoM;
      if(XYtIwqfYej == VXjVNSUomC){uquckPKAQV = true;}
      else if(VXjVNSUomC == XYtIwqfYej){qLRrSYeUsC = true;}
      if(sEXqpyNwuN == VQxdnukiAU){cAUauOlALA = true;}
      else if(VQxdnukiAU == sEXqpyNwuN){JnlqHhsCNR = true;}
      if(PkbhUBaiED == CgNmKZtIrT){UQppeXSbJI = true;}
      else if(CgNmKZtIrT == PkbhUBaiED){zCkYutouaX = true;}
      if(hiOBUnrDQJ == lWlGnijoWH){MJTNoAMxJq = true;}
      else if(lWlGnijoWH == hiOBUnrDQJ){DepOPtxuVU = true;}
      if(uYTwSLtGXT == MSVFLZhlhx){FdxdWYSCnU = true;}
      else if(MSVFLZhlhx == uYTwSLtGXT){LykTCKVHnL = true;}
      if(cAaFsmxMmu == MVsYFnJwLm){NVpnrdAFyN = true;}
      else if(MVsYFnJwLm == cAaFsmxMmu){ckaDEoZsxY = true;}
      if(QxTaCKpVVB == XMwTQyeqpE){xhqHJSgGku = true;}
      else if(XMwTQyeqpE == QxTaCKpVVB){iitUyexWaN = true;}
      if(GKelRqQfOJ == LwLrIjLIak){BoqUupTLSG = true;}
      if(GULkZgHIHh == rIauHPdNAz){FPnntqSeVL = true;}
      if(qfPVsyFssI == YmdiiAWCoM){zHzwsWmoUD = true;}
      while(LwLrIjLIak == GKelRqQfOJ){kxfsFBQRWj = true;}
      while(rIauHPdNAz == rIauHPdNAz){XhHPtRDmKa = true;}
      while(YmdiiAWCoM == YmdiiAWCoM){TEyxkcDPUW = true;}
      if(uquckPKAQV == true){uquckPKAQV = false;}
      if(cAUauOlALA == true){cAUauOlALA = false;}
      if(UQppeXSbJI == true){UQppeXSbJI = false;}
      if(MJTNoAMxJq == true){MJTNoAMxJq = false;}
      if(FdxdWYSCnU == true){FdxdWYSCnU = false;}
      if(NVpnrdAFyN == true){NVpnrdAFyN = false;}
      if(xhqHJSgGku == true){xhqHJSgGku = false;}
      if(BoqUupTLSG == true){BoqUupTLSG = false;}
      if(FPnntqSeVL == true){FPnntqSeVL = false;}
      if(zHzwsWmoUD == true){zHzwsWmoUD = false;}
      if(qLRrSYeUsC == true){qLRrSYeUsC = false;}
      if(JnlqHhsCNR == true){JnlqHhsCNR = false;}
      if(zCkYutouaX == true){zCkYutouaX = false;}
      if(DepOPtxuVU == true){DepOPtxuVU = false;}
      if(LykTCKVHnL == true){LykTCKVHnL = false;}
      if(ckaDEoZsxY == true){ckaDEoZsxY = false;}
      if(iitUyexWaN == true){iitUyexWaN = false;}
      if(kxfsFBQRWj == true){kxfsFBQRWj = false;}
      if(XhHPtRDmKa == true){XhHPtRDmKa = false;}
      if(TEyxkcDPUW == true){TEyxkcDPUW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VTAIIGTUOT
{ 
  void QZnEbwQrck()
  { 
      bool XlpGeQzHcL = false;
      bool aPOccMdadY = false;
      bool plVgxEczdN = false;
      bool MruJJNkdyb = false;
      bool iSxjZdsYhc = false;
      bool ZrRhNlPIIa = false;
      bool nAdPzhTFTP = false;
      bool bAbBpXnlGT = false;
      bool KDQBmTaMuX = false;
      bool ycUXnhogkr = false;
      bool JmFSAZQPrp = false;
      bool xdCoPjjbce = false;
      bool HHJuQzeENH = false;
      bool iGAOJWyyBM = false;
      bool DKUFZTZfID = false;
      bool yNEFjCdJBB = false;
      bool uMCkHpcmer = false;
      bool lkZPbxlDUx = false;
      bool YzuKIVCudH = false;
      bool snwzRpIjyj = false;
      string TIMSGXwjro;
      string ezzMpHYfqC;
      string gVZakJeKOb;
      string rfQSnCtDxh;
      string YdqasCPiSs;
      string JdinDyhlgw;
      string skUQwzhgXm;
      string MVhJcCdzgi;
      string turVRNwcPo;
      string TIVAonJadt;
      string TiKegnuYLA;
      string TiEyCxrzyi;
      string CFQiTDzhUn;
      string sDVmPLjNnd;
      string RWROUkDXxq;
      string uJbtqORbLc;
      string nNEWHQMRhq;
      string MeKTQemCNh;
      string zajdsiaauB;
      string sICLpDSuGD;
      if(TIMSGXwjro == TiKegnuYLA){XlpGeQzHcL = true;}
      else if(TiKegnuYLA == TIMSGXwjro){JmFSAZQPrp = true;}
      if(ezzMpHYfqC == TiEyCxrzyi){aPOccMdadY = true;}
      else if(TiEyCxrzyi == ezzMpHYfqC){xdCoPjjbce = true;}
      if(gVZakJeKOb == CFQiTDzhUn){plVgxEczdN = true;}
      else if(CFQiTDzhUn == gVZakJeKOb){HHJuQzeENH = true;}
      if(rfQSnCtDxh == sDVmPLjNnd){MruJJNkdyb = true;}
      else if(sDVmPLjNnd == rfQSnCtDxh){iGAOJWyyBM = true;}
      if(YdqasCPiSs == RWROUkDXxq){iSxjZdsYhc = true;}
      else if(RWROUkDXxq == YdqasCPiSs){DKUFZTZfID = true;}
      if(JdinDyhlgw == uJbtqORbLc){ZrRhNlPIIa = true;}
      else if(uJbtqORbLc == JdinDyhlgw){yNEFjCdJBB = true;}
      if(skUQwzhgXm == nNEWHQMRhq){nAdPzhTFTP = true;}
      else if(nNEWHQMRhq == skUQwzhgXm){uMCkHpcmer = true;}
      if(MVhJcCdzgi == MeKTQemCNh){bAbBpXnlGT = true;}
      if(turVRNwcPo == zajdsiaauB){KDQBmTaMuX = true;}
      if(TIVAonJadt == sICLpDSuGD){ycUXnhogkr = true;}
      while(MeKTQemCNh == MVhJcCdzgi){lkZPbxlDUx = true;}
      while(zajdsiaauB == zajdsiaauB){YzuKIVCudH = true;}
      while(sICLpDSuGD == sICLpDSuGD){snwzRpIjyj = true;}
      if(XlpGeQzHcL == true){XlpGeQzHcL = false;}
      if(aPOccMdadY == true){aPOccMdadY = false;}
      if(plVgxEczdN == true){plVgxEczdN = false;}
      if(MruJJNkdyb == true){MruJJNkdyb = false;}
      if(iSxjZdsYhc == true){iSxjZdsYhc = false;}
      if(ZrRhNlPIIa == true){ZrRhNlPIIa = false;}
      if(nAdPzhTFTP == true){nAdPzhTFTP = false;}
      if(bAbBpXnlGT == true){bAbBpXnlGT = false;}
      if(KDQBmTaMuX == true){KDQBmTaMuX = false;}
      if(ycUXnhogkr == true){ycUXnhogkr = false;}
      if(JmFSAZQPrp == true){JmFSAZQPrp = false;}
      if(xdCoPjjbce == true){xdCoPjjbce = false;}
      if(HHJuQzeENH == true){HHJuQzeENH = false;}
      if(iGAOJWyyBM == true){iGAOJWyyBM = false;}
      if(DKUFZTZfID == true){DKUFZTZfID = false;}
      if(yNEFjCdJBB == true){yNEFjCdJBB = false;}
      if(uMCkHpcmer == true){uMCkHpcmer = false;}
      if(lkZPbxlDUx == true){lkZPbxlDUx = false;}
      if(YzuKIVCudH == true){YzuKIVCudH = false;}
      if(snwzRpIjyj == true){snwzRpIjyj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YGMELWQWCR
{ 
  void XxsKxfopGb()
  { 
      bool ThJhCQspIB = false;
      bool PlIfKaeUGe = false;
      bool ZQXyACxXQA = false;
      bool MtRqlpafZg = false;
      bool ikwgXHKKqs = false;
      bool UKIsUDJLhA = false;
      bool TVZHoVTQsT = false;
      bool AyuZuoTqZr = false;
      bool rmfWeBkYWi = false;
      bool gOyZNNKorC = false;
      bool msQWsWPhye = false;
      bool jRloHfoDbm = false;
      bool kutKmlzVMh = false;
      bool eezWEyVJdI = false;
      bool lCaqyObIRg = false;
      bool YHMERrzFiH = false;
      bool WsVPzFSOjI = false;
      bool KfYTAhTCMY = false;
      bool JqDeJXRtFL = false;
      bool zQZWlsfKrr = false;
      string bBfpVfzDjd;
      string jHclCfsVqV;
      string zbxFYgFULu;
      string DkDTBewOjh;
      string yWgeOHJOHe;
      string WXIchzDZRo;
      string ZdqoayDIkX;
      string idlJWcuSqR;
      string XqMfXfcZlB;
      string aWxtHUerEP;
      string DAdjurlzGF;
      string EkhARiQKQt;
      string VdWixMgqBB;
      string xCObNWNckf;
      string tcTfxpnwcY;
      string ETaJsZctmi;
      string LtxEHBVGlt;
      string VmZkArJplG;
      string XjOcxcaFhn;
      string tSpCUAfPXu;
      if(bBfpVfzDjd == DAdjurlzGF){ThJhCQspIB = true;}
      else if(DAdjurlzGF == bBfpVfzDjd){msQWsWPhye = true;}
      if(jHclCfsVqV == EkhARiQKQt){PlIfKaeUGe = true;}
      else if(EkhARiQKQt == jHclCfsVqV){jRloHfoDbm = true;}
      if(zbxFYgFULu == VdWixMgqBB){ZQXyACxXQA = true;}
      else if(VdWixMgqBB == zbxFYgFULu){kutKmlzVMh = true;}
      if(DkDTBewOjh == xCObNWNckf){MtRqlpafZg = true;}
      else if(xCObNWNckf == DkDTBewOjh){eezWEyVJdI = true;}
      if(yWgeOHJOHe == tcTfxpnwcY){ikwgXHKKqs = true;}
      else if(tcTfxpnwcY == yWgeOHJOHe){lCaqyObIRg = true;}
      if(WXIchzDZRo == ETaJsZctmi){UKIsUDJLhA = true;}
      else if(ETaJsZctmi == WXIchzDZRo){YHMERrzFiH = true;}
      if(ZdqoayDIkX == LtxEHBVGlt){TVZHoVTQsT = true;}
      else if(LtxEHBVGlt == ZdqoayDIkX){WsVPzFSOjI = true;}
      if(idlJWcuSqR == VmZkArJplG){AyuZuoTqZr = true;}
      if(XqMfXfcZlB == XjOcxcaFhn){rmfWeBkYWi = true;}
      if(aWxtHUerEP == tSpCUAfPXu){gOyZNNKorC = true;}
      while(VmZkArJplG == idlJWcuSqR){KfYTAhTCMY = true;}
      while(XjOcxcaFhn == XjOcxcaFhn){JqDeJXRtFL = true;}
      while(tSpCUAfPXu == tSpCUAfPXu){zQZWlsfKrr = true;}
      if(ThJhCQspIB == true){ThJhCQspIB = false;}
      if(PlIfKaeUGe == true){PlIfKaeUGe = false;}
      if(ZQXyACxXQA == true){ZQXyACxXQA = false;}
      if(MtRqlpafZg == true){MtRqlpafZg = false;}
      if(ikwgXHKKqs == true){ikwgXHKKqs = false;}
      if(UKIsUDJLhA == true){UKIsUDJLhA = false;}
      if(TVZHoVTQsT == true){TVZHoVTQsT = false;}
      if(AyuZuoTqZr == true){AyuZuoTqZr = false;}
      if(rmfWeBkYWi == true){rmfWeBkYWi = false;}
      if(gOyZNNKorC == true){gOyZNNKorC = false;}
      if(msQWsWPhye == true){msQWsWPhye = false;}
      if(jRloHfoDbm == true){jRloHfoDbm = false;}
      if(kutKmlzVMh == true){kutKmlzVMh = false;}
      if(eezWEyVJdI == true){eezWEyVJdI = false;}
      if(lCaqyObIRg == true){lCaqyObIRg = false;}
      if(YHMERrzFiH == true){YHMERrzFiH = false;}
      if(WsVPzFSOjI == true){WsVPzFSOjI = false;}
      if(KfYTAhTCMY == true){KfYTAhTCMY = false;}
      if(JqDeJXRtFL == true){JqDeJXRtFL = false;}
      if(zQZWlsfKrr == true){zQZWlsfKrr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGEKONBOUC
{ 
  void wuJInXdAxz()
  { 
      bool VGsfRyiZFO = false;
      bool fnMDaXYShN = false;
      bool KelwWLaPoe = false;
      bool outmzSGJYJ = false;
      bool jrnChWKyar = false;
      bool XNHOSqUwIG = false;
      bool XTjZZjsYEI = false;
      bool RPsXdSpiOA = false;
      bool AbnwHbmfTH = false;
      bool xJBSkQHNbx = false;
      bool cltSaHTjkA = false;
      bool AlgHFuemRy = false;
      bool xNEwKHOalM = false;
      bool KcGRXOhUVz = false;
      bool HDuSHLbsMp = false;
      bool kTwdzOgyHT = false;
      bool srxXpXePjq = false;
      bool NJRRpsSlnz = false;
      bool eUNwapfbRI = false;
      bool hjMCGPGWcj = false;
      string TkEJVqSjGo;
      string ZHtjxUnOAC;
      string WSmzKAFEZr;
      string VWnCgpUqpW;
      string pfqoAAjDsk;
      string ZqejrBxEzV;
      string lNJOSDTqCH;
      string AwYcLpayzK;
      string PBLnSeqDKf;
      string sPrUkcWcWw;
      string frAlkcSBYB;
      string ZzFnFjCVwn;
      string LPgWNjEDri;
      string TyaCdWBZDo;
      string LpeJFsKDOB;
      string aAfhkQLdXA;
      string YOJogbXDKi;
      string ibRGcVjWQU;
      string ZAoqHSRsRN;
      string LXBCQxfobd;
      if(TkEJVqSjGo == frAlkcSBYB){VGsfRyiZFO = true;}
      else if(frAlkcSBYB == TkEJVqSjGo){cltSaHTjkA = true;}
      if(ZHtjxUnOAC == ZzFnFjCVwn){fnMDaXYShN = true;}
      else if(ZzFnFjCVwn == ZHtjxUnOAC){AlgHFuemRy = true;}
      if(WSmzKAFEZr == LPgWNjEDri){KelwWLaPoe = true;}
      else if(LPgWNjEDri == WSmzKAFEZr){xNEwKHOalM = true;}
      if(VWnCgpUqpW == TyaCdWBZDo){outmzSGJYJ = true;}
      else if(TyaCdWBZDo == VWnCgpUqpW){KcGRXOhUVz = true;}
      if(pfqoAAjDsk == LpeJFsKDOB){jrnChWKyar = true;}
      else if(LpeJFsKDOB == pfqoAAjDsk){HDuSHLbsMp = true;}
      if(ZqejrBxEzV == aAfhkQLdXA){XNHOSqUwIG = true;}
      else if(aAfhkQLdXA == ZqejrBxEzV){kTwdzOgyHT = true;}
      if(lNJOSDTqCH == YOJogbXDKi){XTjZZjsYEI = true;}
      else if(YOJogbXDKi == lNJOSDTqCH){srxXpXePjq = true;}
      if(AwYcLpayzK == ibRGcVjWQU){RPsXdSpiOA = true;}
      if(PBLnSeqDKf == ZAoqHSRsRN){AbnwHbmfTH = true;}
      if(sPrUkcWcWw == LXBCQxfobd){xJBSkQHNbx = true;}
      while(ibRGcVjWQU == AwYcLpayzK){NJRRpsSlnz = true;}
      while(ZAoqHSRsRN == ZAoqHSRsRN){eUNwapfbRI = true;}
      while(LXBCQxfobd == LXBCQxfobd){hjMCGPGWcj = true;}
      if(VGsfRyiZFO == true){VGsfRyiZFO = false;}
      if(fnMDaXYShN == true){fnMDaXYShN = false;}
      if(KelwWLaPoe == true){KelwWLaPoe = false;}
      if(outmzSGJYJ == true){outmzSGJYJ = false;}
      if(jrnChWKyar == true){jrnChWKyar = false;}
      if(XNHOSqUwIG == true){XNHOSqUwIG = false;}
      if(XTjZZjsYEI == true){XTjZZjsYEI = false;}
      if(RPsXdSpiOA == true){RPsXdSpiOA = false;}
      if(AbnwHbmfTH == true){AbnwHbmfTH = false;}
      if(xJBSkQHNbx == true){xJBSkQHNbx = false;}
      if(cltSaHTjkA == true){cltSaHTjkA = false;}
      if(AlgHFuemRy == true){AlgHFuemRy = false;}
      if(xNEwKHOalM == true){xNEwKHOalM = false;}
      if(KcGRXOhUVz == true){KcGRXOhUVz = false;}
      if(HDuSHLbsMp == true){HDuSHLbsMp = false;}
      if(kTwdzOgyHT == true){kTwdzOgyHT = false;}
      if(srxXpXePjq == true){srxXpXePjq = false;}
      if(NJRRpsSlnz == true){NJRRpsSlnz = false;}
      if(eUNwapfbRI == true){eUNwapfbRI = false;}
      if(hjMCGPGWcj == true){hjMCGPGWcj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EXYHIVIXDC
{ 
  void YSoHbnTmDE()
  { 
      bool fmhPFQecRK = false;
      bool lQjlYDnSAp = false;
      bool lWVuWjzybi = false;
      bool UOIuPEFtBS = false;
      bool ZUIYPJqfbU = false;
      bool CFdZpJRlsV = false;
      bool RfAhpXInVU = false;
      bool ytRhPQNwfM = false;
      bool rTWGgOjhFG = false;
      bool lTAfBtTZir = false;
      bool BCJGWHnwKY = false;
      bool uVFgcxIsBa = false;
      bool mZhPhdskfV = false;
      bool xnNmKoJPjY = false;
      bool anXgKQNTCD = false;
      bool kZYHEaUtYr = false;
      bool OCPnbHHRVm = false;
      bool msJcAzCBEQ = false;
      bool QZickWPGii = false;
      bool UOqqKYXiEC = false;
      string lglgAsIhCE;
      string JNdJphmjNt;
      string SFyMgsXgtM;
      string fYnDDZLJje;
      string akjbeMBxYY;
      string mVdVMgiZzG;
      string UamoXkZaGQ;
      string WdAhShVVgT;
      string raIUYKtRpW;
      string qkKcKAxtEt;
      string maqICJVwCe;
      string KNreOtRSQN;
      string pHjiZkSXWS;
      string jaQmgRiASP;
      string nxOLLcsfNQ;
      string hedqDepHhR;
      string qyZjuiwFyx;
      string KRAAYrsYXw;
      string rmJGjExZjC;
      string aaRBYpXeQb;
      if(lglgAsIhCE == maqICJVwCe){fmhPFQecRK = true;}
      else if(maqICJVwCe == lglgAsIhCE){BCJGWHnwKY = true;}
      if(JNdJphmjNt == KNreOtRSQN){lQjlYDnSAp = true;}
      else if(KNreOtRSQN == JNdJphmjNt){uVFgcxIsBa = true;}
      if(SFyMgsXgtM == pHjiZkSXWS){lWVuWjzybi = true;}
      else if(pHjiZkSXWS == SFyMgsXgtM){mZhPhdskfV = true;}
      if(fYnDDZLJje == jaQmgRiASP){UOIuPEFtBS = true;}
      else if(jaQmgRiASP == fYnDDZLJje){xnNmKoJPjY = true;}
      if(akjbeMBxYY == nxOLLcsfNQ){ZUIYPJqfbU = true;}
      else if(nxOLLcsfNQ == akjbeMBxYY){anXgKQNTCD = true;}
      if(mVdVMgiZzG == hedqDepHhR){CFdZpJRlsV = true;}
      else if(hedqDepHhR == mVdVMgiZzG){kZYHEaUtYr = true;}
      if(UamoXkZaGQ == qyZjuiwFyx){RfAhpXInVU = true;}
      else if(qyZjuiwFyx == UamoXkZaGQ){OCPnbHHRVm = true;}
      if(WdAhShVVgT == KRAAYrsYXw){ytRhPQNwfM = true;}
      if(raIUYKtRpW == rmJGjExZjC){rTWGgOjhFG = true;}
      if(qkKcKAxtEt == aaRBYpXeQb){lTAfBtTZir = true;}
      while(KRAAYrsYXw == WdAhShVVgT){msJcAzCBEQ = true;}
      while(rmJGjExZjC == rmJGjExZjC){QZickWPGii = true;}
      while(aaRBYpXeQb == aaRBYpXeQb){UOqqKYXiEC = true;}
      if(fmhPFQecRK == true){fmhPFQecRK = false;}
      if(lQjlYDnSAp == true){lQjlYDnSAp = false;}
      if(lWVuWjzybi == true){lWVuWjzybi = false;}
      if(UOIuPEFtBS == true){UOIuPEFtBS = false;}
      if(ZUIYPJqfbU == true){ZUIYPJqfbU = false;}
      if(CFdZpJRlsV == true){CFdZpJRlsV = false;}
      if(RfAhpXInVU == true){RfAhpXInVU = false;}
      if(ytRhPQNwfM == true){ytRhPQNwfM = false;}
      if(rTWGgOjhFG == true){rTWGgOjhFG = false;}
      if(lTAfBtTZir == true){lTAfBtTZir = false;}
      if(BCJGWHnwKY == true){BCJGWHnwKY = false;}
      if(uVFgcxIsBa == true){uVFgcxIsBa = false;}
      if(mZhPhdskfV == true){mZhPhdskfV = false;}
      if(xnNmKoJPjY == true){xnNmKoJPjY = false;}
      if(anXgKQNTCD == true){anXgKQNTCD = false;}
      if(kZYHEaUtYr == true){kZYHEaUtYr = false;}
      if(OCPnbHHRVm == true){OCPnbHHRVm = false;}
      if(msJcAzCBEQ == true){msJcAzCBEQ = false;}
      if(QZickWPGii == true){QZickWPGii = false;}
      if(UOqqKYXiEC == true){UOqqKYXiEC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GJIEHTVRDT
{ 
  void KTCLRUGKmO()
  { 
      bool qtmAfxFJNW = false;
      bool pEeWVYoUSp = false;
      bool FSMoOcPeBp = false;
      bool BrYAPBhyPP = false;
      bool cdAzWzcBeP = false;
      bool ekrtzYgykC = false;
      bool haHWUyfdGT = false;
      bool pqFDMaRMSO = false;
      bool AOzlLQzdAq = false;
      bool TjMMhCVdeY = false;
      bool TzuLYmfnhY = false;
      bool GUeVCSbVKE = false;
      bool yCcOzFerVK = false;
      bool EnhtuATmMY = false;
      bool kKwbkzEqKO = false;
      bool aATaaRVfLS = false;
      bool ImSWTSlkZB = false;
      bool znJkSmGBdA = false;
      bool BmgHjETHTd = false;
      bool embsPxrYIS = false;
      string pEqRGWAJYf;
      string KygLPDXaPG;
      string FxFuIOKxxK;
      string xidGZpMKAH;
      string fzlajKKbjj;
      string UhjGBsywIq;
      string MDMOibTalY;
      string qNaHaGLeKy;
      string DhNMoOyXFg;
      string rQBIublXrI;
      string pjpKsGGcet;
      string gTlKndpAYT;
      string cwUFfaMSMy;
      string UmlCHTrCTi;
      string IVrKzYdpUQ;
      string llzYetOjdR;
      string tnPfZsgjCT;
      string knfoLHDJFH;
      string wVyuMinNWN;
      string EHXBnUFLkF;
      if(pEqRGWAJYf == pjpKsGGcet){qtmAfxFJNW = true;}
      else if(pjpKsGGcet == pEqRGWAJYf){TzuLYmfnhY = true;}
      if(KygLPDXaPG == gTlKndpAYT){pEeWVYoUSp = true;}
      else if(gTlKndpAYT == KygLPDXaPG){GUeVCSbVKE = true;}
      if(FxFuIOKxxK == cwUFfaMSMy){FSMoOcPeBp = true;}
      else if(cwUFfaMSMy == FxFuIOKxxK){yCcOzFerVK = true;}
      if(xidGZpMKAH == UmlCHTrCTi){BrYAPBhyPP = true;}
      else if(UmlCHTrCTi == xidGZpMKAH){EnhtuATmMY = true;}
      if(fzlajKKbjj == IVrKzYdpUQ){cdAzWzcBeP = true;}
      else if(IVrKzYdpUQ == fzlajKKbjj){kKwbkzEqKO = true;}
      if(UhjGBsywIq == llzYetOjdR){ekrtzYgykC = true;}
      else if(llzYetOjdR == UhjGBsywIq){aATaaRVfLS = true;}
      if(MDMOibTalY == tnPfZsgjCT){haHWUyfdGT = true;}
      else if(tnPfZsgjCT == MDMOibTalY){ImSWTSlkZB = true;}
      if(qNaHaGLeKy == knfoLHDJFH){pqFDMaRMSO = true;}
      if(DhNMoOyXFg == wVyuMinNWN){AOzlLQzdAq = true;}
      if(rQBIublXrI == EHXBnUFLkF){TjMMhCVdeY = true;}
      while(knfoLHDJFH == qNaHaGLeKy){znJkSmGBdA = true;}
      while(wVyuMinNWN == wVyuMinNWN){BmgHjETHTd = true;}
      while(EHXBnUFLkF == EHXBnUFLkF){embsPxrYIS = true;}
      if(qtmAfxFJNW == true){qtmAfxFJNW = false;}
      if(pEeWVYoUSp == true){pEeWVYoUSp = false;}
      if(FSMoOcPeBp == true){FSMoOcPeBp = false;}
      if(BrYAPBhyPP == true){BrYAPBhyPP = false;}
      if(cdAzWzcBeP == true){cdAzWzcBeP = false;}
      if(ekrtzYgykC == true){ekrtzYgykC = false;}
      if(haHWUyfdGT == true){haHWUyfdGT = false;}
      if(pqFDMaRMSO == true){pqFDMaRMSO = false;}
      if(AOzlLQzdAq == true){AOzlLQzdAq = false;}
      if(TjMMhCVdeY == true){TjMMhCVdeY = false;}
      if(TzuLYmfnhY == true){TzuLYmfnhY = false;}
      if(GUeVCSbVKE == true){GUeVCSbVKE = false;}
      if(yCcOzFerVK == true){yCcOzFerVK = false;}
      if(EnhtuATmMY == true){EnhtuATmMY = false;}
      if(kKwbkzEqKO == true){kKwbkzEqKO = false;}
      if(aATaaRVfLS == true){aATaaRVfLS = false;}
      if(ImSWTSlkZB == true){ImSWTSlkZB = false;}
      if(znJkSmGBdA == true){znJkSmGBdA = false;}
      if(BmgHjETHTd == true){BmgHjETHTd = false;}
      if(embsPxrYIS == true){embsPxrYIS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SQKQADXHGL
{ 
  void MnubqwEAgS()
  { 
      bool JuBWQoaVVL = false;
      bool NMUyJXiVwl = false;
      bool JVdQMXAGgp = false;
      bool DKwPAxiBbz = false;
      bool dJMnMaxiyu = false;
      bool pCbqKmRjJs = false;
      bool nUneHDPEyM = false;
      bool ogswHAJoDk = false;
      bool ZRHkABiFFM = false;
      bool fyqiLIUgfJ = false;
      bool KrjkGIIfiJ = false;
      bool dbfYSVMCeG = false;
      bool UKzlgpoKjz = false;
      bool ecJtZhgVeq = false;
      bool rCWuiESSQp = false;
      bool wSBZoAryEP = false;
      bool TyujeASlyj = false;
      bool npWmNRnDCc = false;
      bool XWttCMaiEZ = false;
      bool oiQPXsHmPh = false;
      string tkzfAiGFdC;
      string jEmmZrbMHq;
      string ayKxBYFOBl;
      string ZYGsuNnoWs;
      string lSsJLmWnrW;
      string XraBquZBea;
      string crDrcLxsqL;
      string DmpOFHEBlN;
      string CRVdNgxFBz;
      string mmJuQsOBgA;
      string ocwfTkBLwi;
      string qYOQYKWZdu;
      string NrqrXQctyL;
      string sCTlYYVoKb;
      string flISIOXsWF;
      string WoXkmxkEHC;
      string IGNkpnEcrA;
      string ohOBPbiYiJ;
      string rjXrnEehza;
      string mRgITYXXcT;
      if(tkzfAiGFdC == ocwfTkBLwi){JuBWQoaVVL = true;}
      else if(ocwfTkBLwi == tkzfAiGFdC){KrjkGIIfiJ = true;}
      if(jEmmZrbMHq == qYOQYKWZdu){NMUyJXiVwl = true;}
      else if(qYOQYKWZdu == jEmmZrbMHq){dbfYSVMCeG = true;}
      if(ayKxBYFOBl == NrqrXQctyL){JVdQMXAGgp = true;}
      else if(NrqrXQctyL == ayKxBYFOBl){UKzlgpoKjz = true;}
      if(ZYGsuNnoWs == sCTlYYVoKb){DKwPAxiBbz = true;}
      else if(sCTlYYVoKb == ZYGsuNnoWs){ecJtZhgVeq = true;}
      if(lSsJLmWnrW == flISIOXsWF){dJMnMaxiyu = true;}
      else if(flISIOXsWF == lSsJLmWnrW){rCWuiESSQp = true;}
      if(XraBquZBea == WoXkmxkEHC){pCbqKmRjJs = true;}
      else if(WoXkmxkEHC == XraBquZBea){wSBZoAryEP = true;}
      if(crDrcLxsqL == IGNkpnEcrA){nUneHDPEyM = true;}
      else if(IGNkpnEcrA == crDrcLxsqL){TyujeASlyj = true;}
      if(DmpOFHEBlN == ohOBPbiYiJ){ogswHAJoDk = true;}
      if(CRVdNgxFBz == rjXrnEehza){ZRHkABiFFM = true;}
      if(mmJuQsOBgA == mRgITYXXcT){fyqiLIUgfJ = true;}
      while(ohOBPbiYiJ == DmpOFHEBlN){npWmNRnDCc = true;}
      while(rjXrnEehza == rjXrnEehza){XWttCMaiEZ = true;}
      while(mRgITYXXcT == mRgITYXXcT){oiQPXsHmPh = true;}
      if(JuBWQoaVVL == true){JuBWQoaVVL = false;}
      if(NMUyJXiVwl == true){NMUyJXiVwl = false;}
      if(JVdQMXAGgp == true){JVdQMXAGgp = false;}
      if(DKwPAxiBbz == true){DKwPAxiBbz = false;}
      if(dJMnMaxiyu == true){dJMnMaxiyu = false;}
      if(pCbqKmRjJs == true){pCbqKmRjJs = false;}
      if(nUneHDPEyM == true){nUneHDPEyM = false;}
      if(ogswHAJoDk == true){ogswHAJoDk = false;}
      if(ZRHkABiFFM == true){ZRHkABiFFM = false;}
      if(fyqiLIUgfJ == true){fyqiLIUgfJ = false;}
      if(KrjkGIIfiJ == true){KrjkGIIfiJ = false;}
      if(dbfYSVMCeG == true){dbfYSVMCeG = false;}
      if(UKzlgpoKjz == true){UKzlgpoKjz = false;}
      if(ecJtZhgVeq == true){ecJtZhgVeq = false;}
      if(rCWuiESSQp == true){rCWuiESSQp = false;}
      if(wSBZoAryEP == true){wSBZoAryEP = false;}
      if(TyujeASlyj == true){TyujeASlyj = false;}
      if(npWmNRnDCc == true){npWmNRnDCc = false;}
      if(XWttCMaiEZ == true){XWttCMaiEZ = false;}
      if(oiQPXsHmPh == true){oiQPXsHmPh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XAKCCZKBGW
{ 
  void HGdGVRrYbo()
  { 
      bool LkhXrkHCLW = false;
      bool TIMWZGkBwQ = false;
      bool JRqsjbsXQM = false;
      bool hkyZfNRFYc = false;
      bool UyszcWxRlc = false;
      bool cloHdttomQ = false;
      bool qjkyniKlqL = false;
      bool nebTuKYqPN = false;
      bool daknjwuqwk = false;
      bool TcSIkkNtKt = false;
      bool MKaZnxJVLS = false;
      bool VCYYlQzwOr = false;
      bool mSpFrLMTiK = false;
      bool xdgVBTAKAl = false;
      bool mYfcPQEsVT = false;
      bool lQeSGtTUhc = false;
      bool jomAVqVCXR = false;
      bool PnwbFNlNpb = false;
      bool GSxOYgyNPH = false;
      bool zecXBxlfHX = false;
      string bgLooxrrrm;
      string heIINOAKHi;
      string hLlzOcuIJc;
      string YkXjepnabG;
      string rxLEQRuSMz;
      string FOQiBPtMZL;
      string BjhPNwHYcW;
      string ZYhBpkAgix;
      string hbuKWJUniO;
      string ubAQEIOupT;
      string JVppYffPrP;
      string PNcccYnWrE;
      string aSpNayXRwh;
      string VEqPmMlFlq;
      string cFwSzhyXne;
      string TrDlrpfbPZ;
      string HOSKtKVNoQ;
      string lijAaVWWOr;
      string zAcRNcBEWw;
      string fKoMjOmlXn;
      if(bgLooxrrrm == JVppYffPrP){LkhXrkHCLW = true;}
      else if(JVppYffPrP == bgLooxrrrm){MKaZnxJVLS = true;}
      if(heIINOAKHi == PNcccYnWrE){TIMWZGkBwQ = true;}
      else if(PNcccYnWrE == heIINOAKHi){VCYYlQzwOr = true;}
      if(hLlzOcuIJc == aSpNayXRwh){JRqsjbsXQM = true;}
      else if(aSpNayXRwh == hLlzOcuIJc){mSpFrLMTiK = true;}
      if(YkXjepnabG == VEqPmMlFlq){hkyZfNRFYc = true;}
      else if(VEqPmMlFlq == YkXjepnabG){xdgVBTAKAl = true;}
      if(rxLEQRuSMz == cFwSzhyXne){UyszcWxRlc = true;}
      else if(cFwSzhyXne == rxLEQRuSMz){mYfcPQEsVT = true;}
      if(FOQiBPtMZL == TrDlrpfbPZ){cloHdttomQ = true;}
      else if(TrDlrpfbPZ == FOQiBPtMZL){lQeSGtTUhc = true;}
      if(BjhPNwHYcW == HOSKtKVNoQ){qjkyniKlqL = true;}
      else if(HOSKtKVNoQ == BjhPNwHYcW){jomAVqVCXR = true;}
      if(ZYhBpkAgix == lijAaVWWOr){nebTuKYqPN = true;}
      if(hbuKWJUniO == zAcRNcBEWw){daknjwuqwk = true;}
      if(ubAQEIOupT == fKoMjOmlXn){TcSIkkNtKt = true;}
      while(lijAaVWWOr == ZYhBpkAgix){PnwbFNlNpb = true;}
      while(zAcRNcBEWw == zAcRNcBEWw){GSxOYgyNPH = true;}
      while(fKoMjOmlXn == fKoMjOmlXn){zecXBxlfHX = true;}
      if(LkhXrkHCLW == true){LkhXrkHCLW = false;}
      if(TIMWZGkBwQ == true){TIMWZGkBwQ = false;}
      if(JRqsjbsXQM == true){JRqsjbsXQM = false;}
      if(hkyZfNRFYc == true){hkyZfNRFYc = false;}
      if(UyszcWxRlc == true){UyszcWxRlc = false;}
      if(cloHdttomQ == true){cloHdttomQ = false;}
      if(qjkyniKlqL == true){qjkyniKlqL = false;}
      if(nebTuKYqPN == true){nebTuKYqPN = false;}
      if(daknjwuqwk == true){daknjwuqwk = false;}
      if(TcSIkkNtKt == true){TcSIkkNtKt = false;}
      if(MKaZnxJVLS == true){MKaZnxJVLS = false;}
      if(VCYYlQzwOr == true){VCYYlQzwOr = false;}
      if(mSpFrLMTiK == true){mSpFrLMTiK = false;}
      if(xdgVBTAKAl == true){xdgVBTAKAl = false;}
      if(mYfcPQEsVT == true){mYfcPQEsVT = false;}
      if(lQeSGtTUhc == true){lQeSGtTUhc = false;}
      if(jomAVqVCXR == true){jomAVqVCXR = false;}
      if(PnwbFNlNpb == true){PnwbFNlNpb = false;}
      if(GSxOYgyNPH == true){GSxOYgyNPH = false;}
      if(zecXBxlfHX == true){zecXBxlfHX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HXORNCYSGH
{ 
  void frRSyTrQnO()
  { 
      bool TLwPTTIZyK = false;
      bool lPnQnQyWMf = false;
      bool wDUgVscuPs = false;
      bool bLRHAuMIua = false;
      bool bfhnjnXGpn = false;
      bool NVpRgQpPta = false;
      bool qNJFiaxfPs = false;
      bool EpbkDQUgwg = false;
      bool UWFbeGUzai = false;
      bool FxNTiOVcFJ = false;
      bool prpwjXtFNQ = false;
      bool uJTNGUIhZb = false;
      bool FyFfmGbHBo = false;
      bool tralpbfIqH = false;
      bool MPlKnwcANO = false;
      bool FmDcErmJJc = false;
      bool wlDXVDhhXd = false;
      bool nApSPoMurq = false;
      bool dbtljGoxhx = false;
      bool oVyOKZLNnj = false;
      string NkxHsnDRKV;
      string qzYkfCrPsq;
      string tMhpfoTdIq;
      string OmspjekEDl;
      string AqPBhgsqLz;
      string YwhMnADHbE;
      string UZJSHDFhAA;
      string QmLGpCxfIz;
      string ucSIRSFgBi;
      string adcyRahwtd;
      string aLpKikjaWl;
      string DWybJqHABo;
      string yYfQZmKNoO;
      string TBldYilHZf;
      string idKPfEeAoZ;
      string ThuFeBeYku;
      string aVlHRCjTDZ;
      string FzZUGUOPkU;
      string HJXOukFgzW;
      string EMWdFMrCyc;
      if(NkxHsnDRKV == aLpKikjaWl){TLwPTTIZyK = true;}
      else if(aLpKikjaWl == NkxHsnDRKV){prpwjXtFNQ = true;}
      if(qzYkfCrPsq == DWybJqHABo){lPnQnQyWMf = true;}
      else if(DWybJqHABo == qzYkfCrPsq){uJTNGUIhZb = true;}
      if(tMhpfoTdIq == yYfQZmKNoO){wDUgVscuPs = true;}
      else if(yYfQZmKNoO == tMhpfoTdIq){FyFfmGbHBo = true;}
      if(OmspjekEDl == TBldYilHZf){bLRHAuMIua = true;}
      else if(TBldYilHZf == OmspjekEDl){tralpbfIqH = true;}
      if(AqPBhgsqLz == idKPfEeAoZ){bfhnjnXGpn = true;}
      else if(idKPfEeAoZ == AqPBhgsqLz){MPlKnwcANO = true;}
      if(YwhMnADHbE == ThuFeBeYku){NVpRgQpPta = true;}
      else if(ThuFeBeYku == YwhMnADHbE){FmDcErmJJc = true;}
      if(UZJSHDFhAA == aVlHRCjTDZ){qNJFiaxfPs = true;}
      else if(aVlHRCjTDZ == UZJSHDFhAA){wlDXVDhhXd = true;}
      if(QmLGpCxfIz == FzZUGUOPkU){EpbkDQUgwg = true;}
      if(ucSIRSFgBi == HJXOukFgzW){UWFbeGUzai = true;}
      if(adcyRahwtd == EMWdFMrCyc){FxNTiOVcFJ = true;}
      while(FzZUGUOPkU == QmLGpCxfIz){nApSPoMurq = true;}
      while(HJXOukFgzW == HJXOukFgzW){dbtljGoxhx = true;}
      while(EMWdFMrCyc == EMWdFMrCyc){oVyOKZLNnj = true;}
      if(TLwPTTIZyK == true){TLwPTTIZyK = false;}
      if(lPnQnQyWMf == true){lPnQnQyWMf = false;}
      if(wDUgVscuPs == true){wDUgVscuPs = false;}
      if(bLRHAuMIua == true){bLRHAuMIua = false;}
      if(bfhnjnXGpn == true){bfhnjnXGpn = false;}
      if(NVpRgQpPta == true){NVpRgQpPta = false;}
      if(qNJFiaxfPs == true){qNJFiaxfPs = false;}
      if(EpbkDQUgwg == true){EpbkDQUgwg = false;}
      if(UWFbeGUzai == true){UWFbeGUzai = false;}
      if(FxNTiOVcFJ == true){FxNTiOVcFJ = false;}
      if(prpwjXtFNQ == true){prpwjXtFNQ = false;}
      if(uJTNGUIhZb == true){uJTNGUIhZb = false;}
      if(FyFfmGbHBo == true){FyFfmGbHBo = false;}
      if(tralpbfIqH == true){tralpbfIqH = false;}
      if(MPlKnwcANO == true){MPlKnwcANO = false;}
      if(FmDcErmJJc == true){FmDcErmJJc = false;}
      if(wlDXVDhhXd == true){wlDXVDhhXd = false;}
      if(nApSPoMurq == true){nApSPoMurq = false;}
      if(dbtljGoxhx == true){dbtljGoxhx = false;}
      if(oVyOKZLNnj == true){oVyOKZLNnj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IYSODXVPQN
{ 
  void HwLyoIAzuS()
  { 
      bool BCLiRVCYCj = false;
      bool sCFNLzomRy = false;
      bool ZhwxuiyAcU = false;
      bool ZyJJeLYVNB = false;
      bool CzasrAUnmt = false;
      bool HIYWxTGOmi = false;
      bool WBwgJtruhA = false;
      bool ZTZQwaGCEu = false;
      bool NKMhNQZlLL = false;
      bool EKhddADsjy = false;
      bool IZGmUniHaW = false;
      bool MDJrUMoNTr = false;
      bool UGiWuPkulu = false;
      bool WNSGlnDYNY = false;
      bool hRLoyBApJQ = false;
      bool LpZqdBpjrE = false;
      bool DmUezzkDFf = false;
      bool JPzuKCttXt = false;
      bool OtlVjgmabk = false;
      bool ySgJUuxfoy = false;
      string xRgqnPUAjj;
      string pEFXPDDUYR;
      string TLitPlpmln;
      string FPRVcCYYRW;
      string CnsISrSlBu;
      string tibzolhlaB;
      string ZhOueZmjuN;
      string ddCCOfSabX;
      string SDkptVnRgp;
      string TmxQwUZxcr;
      string EiqnQPfYjI;
      string THJChVxXBI;
      string lVCEsqflGt;
      string FUxjTjMwYd;
      string pPgXWMcuha;
      string WBwUGhgmtZ;
      string jsSpCyKZiy;
      string IAzWRWoehg;
      string OkEeXEYcck;
      string CZBzsxwqUX;
      if(xRgqnPUAjj == EiqnQPfYjI){BCLiRVCYCj = true;}
      else if(EiqnQPfYjI == xRgqnPUAjj){IZGmUniHaW = true;}
      if(pEFXPDDUYR == THJChVxXBI){sCFNLzomRy = true;}
      else if(THJChVxXBI == pEFXPDDUYR){MDJrUMoNTr = true;}
      if(TLitPlpmln == lVCEsqflGt){ZhwxuiyAcU = true;}
      else if(lVCEsqflGt == TLitPlpmln){UGiWuPkulu = true;}
      if(FPRVcCYYRW == FUxjTjMwYd){ZyJJeLYVNB = true;}
      else if(FUxjTjMwYd == FPRVcCYYRW){WNSGlnDYNY = true;}
      if(CnsISrSlBu == pPgXWMcuha){CzasrAUnmt = true;}
      else if(pPgXWMcuha == CnsISrSlBu){hRLoyBApJQ = true;}
      if(tibzolhlaB == WBwUGhgmtZ){HIYWxTGOmi = true;}
      else if(WBwUGhgmtZ == tibzolhlaB){LpZqdBpjrE = true;}
      if(ZhOueZmjuN == jsSpCyKZiy){WBwgJtruhA = true;}
      else if(jsSpCyKZiy == ZhOueZmjuN){DmUezzkDFf = true;}
      if(ddCCOfSabX == IAzWRWoehg){ZTZQwaGCEu = true;}
      if(SDkptVnRgp == OkEeXEYcck){NKMhNQZlLL = true;}
      if(TmxQwUZxcr == CZBzsxwqUX){EKhddADsjy = true;}
      while(IAzWRWoehg == ddCCOfSabX){JPzuKCttXt = true;}
      while(OkEeXEYcck == OkEeXEYcck){OtlVjgmabk = true;}
      while(CZBzsxwqUX == CZBzsxwqUX){ySgJUuxfoy = true;}
      if(BCLiRVCYCj == true){BCLiRVCYCj = false;}
      if(sCFNLzomRy == true){sCFNLzomRy = false;}
      if(ZhwxuiyAcU == true){ZhwxuiyAcU = false;}
      if(ZyJJeLYVNB == true){ZyJJeLYVNB = false;}
      if(CzasrAUnmt == true){CzasrAUnmt = false;}
      if(HIYWxTGOmi == true){HIYWxTGOmi = false;}
      if(WBwgJtruhA == true){WBwgJtruhA = false;}
      if(ZTZQwaGCEu == true){ZTZQwaGCEu = false;}
      if(NKMhNQZlLL == true){NKMhNQZlLL = false;}
      if(EKhddADsjy == true){EKhddADsjy = false;}
      if(IZGmUniHaW == true){IZGmUniHaW = false;}
      if(MDJrUMoNTr == true){MDJrUMoNTr = false;}
      if(UGiWuPkulu == true){UGiWuPkulu = false;}
      if(WNSGlnDYNY == true){WNSGlnDYNY = false;}
      if(hRLoyBApJQ == true){hRLoyBApJQ = false;}
      if(LpZqdBpjrE == true){LpZqdBpjrE = false;}
      if(DmUezzkDFf == true){DmUezzkDFf = false;}
      if(JPzuKCttXt == true){JPzuKCttXt = false;}
      if(OtlVjgmabk == true){OtlVjgmabk = false;}
      if(ySgJUuxfoy == true){ySgJUuxfoy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVDHQBIXDL
{ 
  void WMYmQdjwzY()
  { 
      bool MjniESlxSW = false;
      bool feuJuqAMNh = false;
      bool lZIGhDQBry = false;
      bool VXNkPLEOSY = false;
      bool iRIayrrudn = false;
      bool JFcOsmagBB = false;
      bool BjFTBIRKti = false;
      bool mlsozTQhHp = false;
      bool LVXEoPuyqb = false;
      bool jWNRXyMnZp = false;
      bool ZgBtAXMnOZ = false;
      bool VsYKpfLAek = false;
      bool NSSRyQXbRB = false;
      bool GcHRPdTdEQ = false;
      bool DGiRGpxCbq = false;
      bool lMIocHOjuj = false;
      bool zjWNSrlHuM = false;
      bool LhwNgGjBKH = false;
      bool SVAZOtTSoI = false;
      bool OjhTRSjUyO = false;
      string nypVlpaBZi;
      string HqEXWdfcmJ;
      string YGzMdIpyQV;
      string XKzICQjcjj;
      string cmMDzywfgW;
      string EdFRWgzcqd;
      string AcjEKwrwUG;
      string sCrCfktuMf;
      string MKQsQsFglV;
      string QGkFjADIrD;
      string FALadBkCkk;
      string mDQLRoLpmQ;
      string qKKzolRlSf;
      string hkCJZLzpPP;
      string ICwAhNpZnt;
      string nMUaLuoLkq;
      string jyjFDCAGkF;
      string pVaXInOKQb;
      string wryXqUPaye;
      string WmEYeJSqxf;
      if(nypVlpaBZi == FALadBkCkk){MjniESlxSW = true;}
      else if(FALadBkCkk == nypVlpaBZi){ZgBtAXMnOZ = true;}
      if(HqEXWdfcmJ == mDQLRoLpmQ){feuJuqAMNh = true;}
      else if(mDQLRoLpmQ == HqEXWdfcmJ){VsYKpfLAek = true;}
      if(YGzMdIpyQV == qKKzolRlSf){lZIGhDQBry = true;}
      else if(qKKzolRlSf == YGzMdIpyQV){NSSRyQXbRB = true;}
      if(XKzICQjcjj == hkCJZLzpPP){VXNkPLEOSY = true;}
      else if(hkCJZLzpPP == XKzICQjcjj){GcHRPdTdEQ = true;}
      if(cmMDzywfgW == ICwAhNpZnt){iRIayrrudn = true;}
      else if(ICwAhNpZnt == cmMDzywfgW){DGiRGpxCbq = true;}
      if(EdFRWgzcqd == nMUaLuoLkq){JFcOsmagBB = true;}
      else if(nMUaLuoLkq == EdFRWgzcqd){lMIocHOjuj = true;}
      if(AcjEKwrwUG == jyjFDCAGkF){BjFTBIRKti = true;}
      else if(jyjFDCAGkF == AcjEKwrwUG){zjWNSrlHuM = true;}
      if(sCrCfktuMf == pVaXInOKQb){mlsozTQhHp = true;}
      if(MKQsQsFglV == wryXqUPaye){LVXEoPuyqb = true;}
      if(QGkFjADIrD == WmEYeJSqxf){jWNRXyMnZp = true;}
      while(pVaXInOKQb == sCrCfktuMf){LhwNgGjBKH = true;}
      while(wryXqUPaye == wryXqUPaye){SVAZOtTSoI = true;}
      while(WmEYeJSqxf == WmEYeJSqxf){OjhTRSjUyO = true;}
      if(MjniESlxSW == true){MjniESlxSW = false;}
      if(feuJuqAMNh == true){feuJuqAMNh = false;}
      if(lZIGhDQBry == true){lZIGhDQBry = false;}
      if(VXNkPLEOSY == true){VXNkPLEOSY = false;}
      if(iRIayrrudn == true){iRIayrrudn = false;}
      if(JFcOsmagBB == true){JFcOsmagBB = false;}
      if(BjFTBIRKti == true){BjFTBIRKti = false;}
      if(mlsozTQhHp == true){mlsozTQhHp = false;}
      if(LVXEoPuyqb == true){LVXEoPuyqb = false;}
      if(jWNRXyMnZp == true){jWNRXyMnZp = false;}
      if(ZgBtAXMnOZ == true){ZgBtAXMnOZ = false;}
      if(VsYKpfLAek == true){VsYKpfLAek = false;}
      if(NSSRyQXbRB == true){NSSRyQXbRB = false;}
      if(GcHRPdTdEQ == true){GcHRPdTdEQ = false;}
      if(DGiRGpxCbq == true){DGiRGpxCbq = false;}
      if(lMIocHOjuj == true){lMIocHOjuj = false;}
      if(zjWNSrlHuM == true){zjWNSrlHuM = false;}
      if(LhwNgGjBKH == true){LhwNgGjBKH = false;}
      if(SVAZOtTSoI == true){SVAZOtTSoI = false;}
      if(OjhTRSjUyO == true){OjhTRSjUyO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JFAXZURXRA
{ 
  void CyJAkYgfWf()
  { 
      bool ZusJBciJxU = false;
      bool oDVwgiJape = false;
      bool DxbDQkFIxn = false;
      bool ulyJApnQAo = false;
      bool lFyqeJuJxt = false;
      bool VZIhwbTosP = false;
      bool WZLJYCFMwq = false;
      bool urZBsxyjXG = false;
      bool pwLDRVdPNX = false;
      bool VyXkRLtoSb = false;
      bool EhNFyczHny = false;
      bool djRlYaOHqC = false;
      bool YozYVxUoig = false;
      bool CJQuBIiFEo = false;
      bool VVbOtlgkLq = false;
      bool xlxPDPinjB = false;
      bool IKXGuTSVjQ = false;
      bool rIDCgCMjdj = false;
      bool QidqjPLArl = false;
      bool ZtVDfLyVSZ = false;
      string MXjiCaOTcN;
      string updYKFxSRz;
      string gmGzBhXeuB;
      string RHYyKqjQMH;
      string NgguelSUjI;
      string tEtBrYRkhT;
      string DiXbwnQeNT;
      string UfGKkAFLTP;
      string ODtlGNNXGl;
      string ZzirDdIFzq;
      string UmGQnNyjPr;
      string TGQSEzolUh;
      string ZsYbtUxNGG;
      string qAMcuawcys;
      string PdHNSTiQmE;
      string oWkQQaOeWS;
      string PjcIASsmXc;
      string CLnaSwlLIZ;
      string lgaCRUPwLT;
      string MQGeceAzNz;
      if(MXjiCaOTcN == UmGQnNyjPr){ZusJBciJxU = true;}
      else if(UmGQnNyjPr == MXjiCaOTcN){EhNFyczHny = true;}
      if(updYKFxSRz == TGQSEzolUh){oDVwgiJape = true;}
      else if(TGQSEzolUh == updYKFxSRz){djRlYaOHqC = true;}
      if(gmGzBhXeuB == ZsYbtUxNGG){DxbDQkFIxn = true;}
      else if(ZsYbtUxNGG == gmGzBhXeuB){YozYVxUoig = true;}
      if(RHYyKqjQMH == qAMcuawcys){ulyJApnQAo = true;}
      else if(qAMcuawcys == RHYyKqjQMH){CJQuBIiFEo = true;}
      if(NgguelSUjI == PdHNSTiQmE){lFyqeJuJxt = true;}
      else if(PdHNSTiQmE == NgguelSUjI){VVbOtlgkLq = true;}
      if(tEtBrYRkhT == oWkQQaOeWS){VZIhwbTosP = true;}
      else if(oWkQQaOeWS == tEtBrYRkhT){xlxPDPinjB = true;}
      if(DiXbwnQeNT == PjcIASsmXc){WZLJYCFMwq = true;}
      else if(PjcIASsmXc == DiXbwnQeNT){IKXGuTSVjQ = true;}
      if(UfGKkAFLTP == CLnaSwlLIZ){urZBsxyjXG = true;}
      if(ODtlGNNXGl == lgaCRUPwLT){pwLDRVdPNX = true;}
      if(ZzirDdIFzq == MQGeceAzNz){VyXkRLtoSb = true;}
      while(CLnaSwlLIZ == UfGKkAFLTP){rIDCgCMjdj = true;}
      while(lgaCRUPwLT == lgaCRUPwLT){QidqjPLArl = true;}
      while(MQGeceAzNz == MQGeceAzNz){ZtVDfLyVSZ = true;}
      if(ZusJBciJxU == true){ZusJBciJxU = false;}
      if(oDVwgiJape == true){oDVwgiJape = false;}
      if(DxbDQkFIxn == true){DxbDQkFIxn = false;}
      if(ulyJApnQAo == true){ulyJApnQAo = false;}
      if(lFyqeJuJxt == true){lFyqeJuJxt = false;}
      if(VZIhwbTosP == true){VZIhwbTosP = false;}
      if(WZLJYCFMwq == true){WZLJYCFMwq = false;}
      if(urZBsxyjXG == true){urZBsxyjXG = false;}
      if(pwLDRVdPNX == true){pwLDRVdPNX = false;}
      if(VyXkRLtoSb == true){VyXkRLtoSb = false;}
      if(EhNFyczHny == true){EhNFyczHny = false;}
      if(djRlYaOHqC == true){djRlYaOHqC = false;}
      if(YozYVxUoig == true){YozYVxUoig = false;}
      if(CJQuBIiFEo == true){CJQuBIiFEo = false;}
      if(VVbOtlgkLq == true){VVbOtlgkLq = false;}
      if(xlxPDPinjB == true){xlxPDPinjB = false;}
      if(IKXGuTSVjQ == true){IKXGuTSVjQ = false;}
      if(rIDCgCMjdj == true){rIDCgCMjdj = false;}
      if(QidqjPLArl == true){QidqjPLArl = false;}
      if(ZtVDfLyVSZ == true){ZtVDfLyVSZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KNRVLHLEBI
{ 
  void ywrTEbXARa()
  { 
      bool LpBFcSZDcF = false;
      bool ueuUJGAJLd = false;
      bool UEaSnSDBoj = false;
      bool VyyxSQsOOc = false;
      bool eORpeGyfXI = false;
      bool dkAoaGPiRK = false;
      bool PXNsiwgyCr = false;
      bool NlthzGmjng = false;
      bool TXdfFkyJVM = false;
      bool BKxENGAXGh = false;
      bool ZAdeurpSpU = false;
      bool Setjprthny = false;
      bool yWboqDnpTr = false;
      bool GOdFHTsykM = false;
      bool tfSBsWPMNV = false;
      bool LSjHjCXnnr = false;
      bool DAyxOEAocW = false;
      bool ywwaERDawU = false;
      bool mbbxfneVVE = false;
      bool wEJsIsgVln = false;
      string kUWFulLOpS;
      string isZlQTJlFV;
      string QSneUlpQwJ;
      string gnTENdtCxi;
      string XKMsdHloaL;
      string zKGYESgqjI;
      string wtSgltYUXl;
      string YHoVxGFtBN;
      string AAokJWguAu;
      string xDRnlcqeHi;
      string hQQnlrVkby;
      string MloWIwFhWP;
      string McTboUoAiT;
      string OZmSeiiAyR;
      string AwSCiKNtfp;
      string XJIrVFwozQ;
      string CVBHilzWrZ;
      string MEiEOQKRsd;
      string HuUrwFRtwZ;
      string ltBgPetLSw;
      if(kUWFulLOpS == hQQnlrVkby){LpBFcSZDcF = true;}
      else if(hQQnlrVkby == kUWFulLOpS){ZAdeurpSpU = true;}
      if(isZlQTJlFV == MloWIwFhWP){ueuUJGAJLd = true;}
      else if(MloWIwFhWP == isZlQTJlFV){Setjprthny = true;}
      if(QSneUlpQwJ == McTboUoAiT){UEaSnSDBoj = true;}
      else if(McTboUoAiT == QSneUlpQwJ){yWboqDnpTr = true;}
      if(gnTENdtCxi == OZmSeiiAyR){VyyxSQsOOc = true;}
      else if(OZmSeiiAyR == gnTENdtCxi){GOdFHTsykM = true;}
      if(XKMsdHloaL == AwSCiKNtfp){eORpeGyfXI = true;}
      else if(AwSCiKNtfp == XKMsdHloaL){tfSBsWPMNV = true;}
      if(zKGYESgqjI == XJIrVFwozQ){dkAoaGPiRK = true;}
      else if(XJIrVFwozQ == zKGYESgqjI){LSjHjCXnnr = true;}
      if(wtSgltYUXl == CVBHilzWrZ){PXNsiwgyCr = true;}
      else if(CVBHilzWrZ == wtSgltYUXl){DAyxOEAocW = true;}
      if(YHoVxGFtBN == MEiEOQKRsd){NlthzGmjng = true;}
      if(AAokJWguAu == HuUrwFRtwZ){TXdfFkyJVM = true;}
      if(xDRnlcqeHi == ltBgPetLSw){BKxENGAXGh = true;}
      while(MEiEOQKRsd == YHoVxGFtBN){ywwaERDawU = true;}
      while(HuUrwFRtwZ == HuUrwFRtwZ){mbbxfneVVE = true;}
      while(ltBgPetLSw == ltBgPetLSw){wEJsIsgVln = true;}
      if(LpBFcSZDcF == true){LpBFcSZDcF = false;}
      if(ueuUJGAJLd == true){ueuUJGAJLd = false;}
      if(UEaSnSDBoj == true){UEaSnSDBoj = false;}
      if(VyyxSQsOOc == true){VyyxSQsOOc = false;}
      if(eORpeGyfXI == true){eORpeGyfXI = false;}
      if(dkAoaGPiRK == true){dkAoaGPiRK = false;}
      if(PXNsiwgyCr == true){PXNsiwgyCr = false;}
      if(NlthzGmjng == true){NlthzGmjng = false;}
      if(TXdfFkyJVM == true){TXdfFkyJVM = false;}
      if(BKxENGAXGh == true){BKxENGAXGh = false;}
      if(ZAdeurpSpU == true){ZAdeurpSpU = false;}
      if(Setjprthny == true){Setjprthny = false;}
      if(yWboqDnpTr == true){yWboqDnpTr = false;}
      if(GOdFHTsykM == true){GOdFHTsykM = false;}
      if(tfSBsWPMNV == true){tfSBsWPMNV = false;}
      if(LSjHjCXnnr == true){LSjHjCXnnr = false;}
      if(DAyxOEAocW == true){DAyxOEAocW = false;}
      if(ywwaERDawU == true){ywwaERDawU = false;}
      if(mbbxfneVVE == true){mbbxfneVVE = false;}
      if(wEJsIsgVln == true){wEJsIsgVln = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BLEIMRXACJ
{ 
  void BdaBGxxPpp()
  { 
      bool LSifQAYRhb = false;
      bool ACbsxBOVGu = false;
      bool oamCGGMILy = false;
      bool UfdrqGLSMo = false;
      bool QZPIFhFjAW = false;
      bool AaWgqjefYK = false;
      bool nQFjGTXjBq = false;
      bool ouJRdOLewY = false;
      bool BcIoytIxBG = false;
      bool aetCBAUfBk = false;
      bool KVhIgERFDb = false;
      bool YAjzILIQlM = false;
      bool KahtQKAGPc = false;
      bool tecLOftzIs = false;
      bool cDsZhZutsp = false;
      bool rDtoZimmrV = false;
      bool EKpagsXYkc = false;
      bool QIHriHgIMp = false;
      bool PGMZjpkmke = false;
      bool rGGloRNSro = false;
      string qMttBZLxqZ;
      string aRAqtGJyeV;
      string ZOPyErhlLl;
      string ZcZJRBrGST;
      string gtMkHoTMbC;
      string jOuTmcxuoJ;
      string qZlFAxrpZr;
      string NDeLoeBdpO;
      string XUJJBLgGVn;
      string EwRIbHIGjK;
      string xdljngijeH;
      string aSEZkWPbEo;
      string PlUlnQkVih;
      string WtsfRthZUT;
      string bxaNMkrqWF;
      string qfCutLJAwW;
      string uMAxkgZYIq;
      string npGjMSKGYC;
      string YtydpprykG;
      string jgcyXOxdbf;
      if(qMttBZLxqZ == xdljngijeH){LSifQAYRhb = true;}
      else if(xdljngijeH == qMttBZLxqZ){KVhIgERFDb = true;}
      if(aRAqtGJyeV == aSEZkWPbEo){ACbsxBOVGu = true;}
      else if(aSEZkWPbEo == aRAqtGJyeV){YAjzILIQlM = true;}
      if(ZOPyErhlLl == PlUlnQkVih){oamCGGMILy = true;}
      else if(PlUlnQkVih == ZOPyErhlLl){KahtQKAGPc = true;}
      if(ZcZJRBrGST == WtsfRthZUT){UfdrqGLSMo = true;}
      else if(WtsfRthZUT == ZcZJRBrGST){tecLOftzIs = true;}
      if(gtMkHoTMbC == bxaNMkrqWF){QZPIFhFjAW = true;}
      else if(bxaNMkrqWF == gtMkHoTMbC){cDsZhZutsp = true;}
      if(jOuTmcxuoJ == qfCutLJAwW){AaWgqjefYK = true;}
      else if(qfCutLJAwW == jOuTmcxuoJ){rDtoZimmrV = true;}
      if(qZlFAxrpZr == uMAxkgZYIq){nQFjGTXjBq = true;}
      else if(uMAxkgZYIq == qZlFAxrpZr){EKpagsXYkc = true;}
      if(NDeLoeBdpO == npGjMSKGYC){ouJRdOLewY = true;}
      if(XUJJBLgGVn == YtydpprykG){BcIoytIxBG = true;}
      if(EwRIbHIGjK == jgcyXOxdbf){aetCBAUfBk = true;}
      while(npGjMSKGYC == NDeLoeBdpO){QIHriHgIMp = true;}
      while(YtydpprykG == YtydpprykG){PGMZjpkmke = true;}
      while(jgcyXOxdbf == jgcyXOxdbf){rGGloRNSro = true;}
      if(LSifQAYRhb == true){LSifQAYRhb = false;}
      if(ACbsxBOVGu == true){ACbsxBOVGu = false;}
      if(oamCGGMILy == true){oamCGGMILy = false;}
      if(UfdrqGLSMo == true){UfdrqGLSMo = false;}
      if(QZPIFhFjAW == true){QZPIFhFjAW = false;}
      if(AaWgqjefYK == true){AaWgqjefYK = false;}
      if(nQFjGTXjBq == true){nQFjGTXjBq = false;}
      if(ouJRdOLewY == true){ouJRdOLewY = false;}
      if(BcIoytIxBG == true){BcIoytIxBG = false;}
      if(aetCBAUfBk == true){aetCBAUfBk = false;}
      if(KVhIgERFDb == true){KVhIgERFDb = false;}
      if(YAjzILIQlM == true){YAjzILIQlM = false;}
      if(KahtQKAGPc == true){KahtQKAGPc = false;}
      if(tecLOftzIs == true){tecLOftzIs = false;}
      if(cDsZhZutsp == true){cDsZhZutsp = false;}
      if(rDtoZimmrV == true){rDtoZimmrV = false;}
      if(EKpagsXYkc == true){EKpagsXYkc = false;}
      if(QIHriHgIMp == true){QIHriHgIMp = false;}
      if(PGMZjpkmke == true){PGMZjpkmke = false;}
      if(rGGloRNSro == true){rGGloRNSro = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LYROGLKFRD
{ 
  void dqdUpclLGc()
  { 
      bool ifrOOXTywn = false;
      bool AVLOmzMEFb = false;
      bool JUKAcTmfHw = false;
      bool UgmINNhbKj = false;
      bool GgPshAOtWs = false;
      bool TOVnPOVqku = false;
      bool kmpATTiDAY = false;
      bool RksVUbEQRb = false;
      bool ErJNbFKzry = false;
      bool qpqPyTpPZN = false;
      bool RKsxbiUzTn = false;
      bool KFYIprdcYN = false;
      bool JjLBgatdWB = false;
      bool lopEJtzLkr = false;
      bool jLeEnlQhZG = false;
      bool oNqMEhzqPA = false;
      bool oqbRBUOUyu = false;
      bool sRqfdxEHNu = false;
      bool KMEQLYydAb = false;
      bool uHukDriNCS = false;
      string oUxHzBXDgY;
      string YAmWfmgPHx;
      string haXafLaQhV;
      string ReYNtguczz;
      string oJdwGgTQXr;
      string cYUwJOwVan;
      string ZHVLHtaYby;
      string rDPIIXwbUz;
      string qKrprsJcDf;
      string kYCLYhnSnL;
      string GtoYzZIMnl;
      string RUAbwPOfTO;
      string jxVuNSAEiZ;
      string idmIrwUTpS;
      string kwoRNQXaOJ;
      string SIzZaJYtLg;
      string YDdNCngriA;
      string tuoAcmIDhx;
      string tZpYHaeMgi;
      string WaIJsgSbPZ;
      if(oUxHzBXDgY == GtoYzZIMnl){ifrOOXTywn = true;}
      else if(GtoYzZIMnl == oUxHzBXDgY){RKsxbiUzTn = true;}
      if(YAmWfmgPHx == RUAbwPOfTO){AVLOmzMEFb = true;}
      else if(RUAbwPOfTO == YAmWfmgPHx){KFYIprdcYN = true;}
      if(haXafLaQhV == jxVuNSAEiZ){JUKAcTmfHw = true;}
      else if(jxVuNSAEiZ == haXafLaQhV){JjLBgatdWB = true;}
      if(ReYNtguczz == idmIrwUTpS){UgmINNhbKj = true;}
      else if(idmIrwUTpS == ReYNtguczz){lopEJtzLkr = true;}
      if(oJdwGgTQXr == kwoRNQXaOJ){GgPshAOtWs = true;}
      else if(kwoRNQXaOJ == oJdwGgTQXr){jLeEnlQhZG = true;}
      if(cYUwJOwVan == SIzZaJYtLg){TOVnPOVqku = true;}
      else if(SIzZaJYtLg == cYUwJOwVan){oNqMEhzqPA = true;}
      if(ZHVLHtaYby == YDdNCngriA){kmpATTiDAY = true;}
      else if(YDdNCngriA == ZHVLHtaYby){oqbRBUOUyu = true;}
      if(rDPIIXwbUz == tuoAcmIDhx){RksVUbEQRb = true;}
      if(qKrprsJcDf == tZpYHaeMgi){ErJNbFKzry = true;}
      if(kYCLYhnSnL == WaIJsgSbPZ){qpqPyTpPZN = true;}
      while(tuoAcmIDhx == rDPIIXwbUz){sRqfdxEHNu = true;}
      while(tZpYHaeMgi == tZpYHaeMgi){KMEQLYydAb = true;}
      while(WaIJsgSbPZ == WaIJsgSbPZ){uHukDriNCS = true;}
      if(ifrOOXTywn == true){ifrOOXTywn = false;}
      if(AVLOmzMEFb == true){AVLOmzMEFb = false;}
      if(JUKAcTmfHw == true){JUKAcTmfHw = false;}
      if(UgmINNhbKj == true){UgmINNhbKj = false;}
      if(GgPshAOtWs == true){GgPshAOtWs = false;}
      if(TOVnPOVqku == true){TOVnPOVqku = false;}
      if(kmpATTiDAY == true){kmpATTiDAY = false;}
      if(RksVUbEQRb == true){RksVUbEQRb = false;}
      if(ErJNbFKzry == true){ErJNbFKzry = false;}
      if(qpqPyTpPZN == true){qpqPyTpPZN = false;}
      if(RKsxbiUzTn == true){RKsxbiUzTn = false;}
      if(KFYIprdcYN == true){KFYIprdcYN = false;}
      if(JjLBgatdWB == true){JjLBgatdWB = false;}
      if(lopEJtzLkr == true){lopEJtzLkr = false;}
      if(jLeEnlQhZG == true){jLeEnlQhZG = false;}
      if(oNqMEhzqPA == true){oNqMEhzqPA = false;}
      if(oqbRBUOUyu == true){oqbRBUOUyu = false;}
      if(sRqfdxEHNu == true){sRqfdxEHNu = false;}
      if(KMEQLYydAb == true){KMEQLYydAb = false;}
      if(uHukDriNCS == true){uHukDriNCS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JIESFLAXEM
{ 
  void KfiFBntRmQ()
  { 
      bool yYotBHxtwW = false;
      bool mBQlftomun = false;
      bool xbpRUcfKJd = false;
      bool WXryAcWZEJ = false;
      bool kTnuODmlVp = false;
      bool kiMzTViXYX = false;
      bool bmjRAOJSlD = false;
      bool XOhlCdnuDR = false;
      bool psnSsnKsde = false;
      bool tzAfgyiVtz = false;
      bool tUzSSWAawp = false;
      bool gmTHhhyQYM = false;
      bool EPnGJXNCEE = false;
      bool uSAEXVsVAW = false;
      bool miwnxGesyz = false;
      bool zRwhtdfsIt = false;
      bool IyWrtOmPjM = false;
      bool ncQCYUTAJC = false;
      bool sUDEEcVRJs = false;
      bool oAMFNoMEsi = false;
      string NagsHJlTak;
      string UFwaKauZVr;
      string DSxiQncTWR;
      string JQxknoUaBg;
      string qElScbgOPV;
      string wYUoNudxcT;
      string gRxIaEILmU;
      string FTXnBzfdGn;
      string GNEAUkuHXr;
      string KWyhAYGcqY;
      string TUbtQcAfnO;
      string OzpnMSNwmp;
      string IAntJhVpmb;
      string rDlhUllJjr;
      string kOTIdLgJUh;
      string LJoBPTghkh;
      string GKsLVLNITa;
      string gEMuEsfeQy;
      string BMUFQhNkRB;
      string FDYCkaVImR;
      if(NagsHJlTak == TUbtQcAfnO){yYotBHxtwW = true;}
      else if(TUbtQcAfnO == NagsHJlTak){tUzSSWAawp = true;}
      if(UFwaKauZVr == OzpnMSNwmp){mBQlftomun = true;}
      else if(OzpnMSNwmp == UFwaKauZVr){gmTHhhyQYM = true;}
      if(DSxiQncTWR == IAntJhVpmb){xbpRUcfKJd = true;}
      else if(IAntJhVpmb == DSxiQncTWR){EPnGJXNCEE = true;}
      if(JQxknoUaBg == rDlhUllJjr){WXryAcWZEJ = true;}
      else if(rDlhUllJjr == JQxknoUaBg){uSAEXVsVAW = true;}
      if(qElScbgOPV == kOTIdLgJUh){kTnuODmlVp = true;}
      else if(kOTIdLgJUh == qElScbgOPV){miwnxGesyz = true;}
      if(wYUoNudxcT == LJoBPTghkh){kiMzTViXYX = true;}
      else if(LJoBPTghkh == wYUoNudxcT){zRwhtdfsIt = true;}
      if(gRxIaEILmU == GKsLVLNITa){bmjRAOJSlD = true;}
      else if(GKsLVLNITa == gRxIaEILmU){IyWrtOmPjM = true;}
      if(FTXnBzfdGn == gEMuEsfeQy){XOhlCdnuDR = true;}
      if(GNEAUkuHXr == BMUFQhNkRB){psnSsnKsde = true;}
      if(KWyhAYGcqY == FDYCkaVImR){tzAfgyiVtz = true;}
      while(gEMuEsfeQy == FTXnBzfdGn){ncQCYUTAJC = true;}
      while(BMUFQhNkRB == BMUFQhNkRB){sUDEEcVRJs = true;}
      while(FDYCkaVImR == FDYCkaVImR){oAMFNoMEsi = true;}
      if(yYotBHxtwW == true){yYotBHxtwW = false;}
      if(mBQlftomun == true){mBQlftomun = false;}
      if(xbpRUcfKJd == true){xbpRUcfKJd = false;}
      if(WXryAcWZEJ == true){WXryAcWZEJ = false;}
      if(kTnuODmlVp == true){kTnuODmlVp = false;}
      if(kiMzTViXYX == true){kiMzTViXYX = false;}
      if(bmjRAOJSlD == true){bmjRAOJSlD = false;}
      if(XOhlCdnuDR == true){XOhlCdnuDR = false;}
      if(psnSsnKsde == true){psnSsnKsde = false;}
      if(tzAfgyiVtz == true){tzAfgyiVtz = false;}
      if(tUzSSWAawp == true){tUzSSWAawp = false;}
      if(gmTHhhyQYM == true){gmTHhhyQYM = false;}
      if(EPnGJXNCEE == true){EPnGJXNCEE = false;}
      if(uSAEXVsVAW == true){uSAEXVsVAW = false;}
      if(miwnxGesyz == true){miwnxGesyz = false;}
      if(zRwhtdfsIt == true){zRwhtdfsIt = false;}
      if(IyWrtOmPjM == true){IyWrtOmPjM = false;}
      if(ncQCYUTAJC == true){ncQCYUTAJC = false;}
      if(sUDEEcVRJs == true){sUDEEcVRJs = false;}
      if(oAMFNoMEsi == true){oAMFNoMEsi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SWIJMGNHOV
{ 
  void WAHbxEZtQH()
  { 
      bool uKXGFQsZOM = false;
      bool mAkQTpgrsi = false;
      bool jTnMefeqCk = false;
      bool KWMntfrZRg = false;
      bool lmnzdoDOuZ = false;
      bool MSSKtbWKaZ = false;
      bool lCWdBPmwVm = false;
      bool yGZMxweohp = false;
      bool bPwbXrECtS = false;
      bool JgyrtjQJxO = false;
      bool CGsHbGsFMx = false;
      bool wgckxVFuGJ = false;
      bool LjBDdQHgRM = false;
      bool fUqSnVWnAR = false;
      bool yyowWbDNuY = false;
      bool dVDmDREodK = false;
      bool yLnARapJxb = false;
      bool zRtnKMuEgB = false;
      bool NslsiKRDPV = false;
      bool QgKoSmKoeu = false;
      string EXJlmPDhqQ;
      string NoewdpXbWS;
      string PLZmTENGNE;
      string AfgMXjeman;
      string UBVwMTmWHZ;
      string JWtNIsxWSh;
      string CwUlPhHSYs;
      string LkBhxNodZA;
      string QpznudlTDe;
      string lITrkXgjfe;
      string LUyNNXVLPu;
      string DTwSQMwgql;
      string wnOtHDQIwY;
      string fFxunwrlZX;
      string HZDIaRLBbY;
      string bArtiWGDFK;
      string GNOqOxWBdU;
      string TKGSeVjGSo;
      string qPgWxfMDMR;
      string onfOQsKMsd;
      if(EXJlmPDhqQ == LUyNNXVLPu){uKXGFQsZOM = true;}
      else if(LUyNNXVLPu == EXJlmPDhqQ){CGsHbGsFMx = true;}
      if(NoewdpXbWS == DTwSQMwgql){mAkQTpgrsi = true;}
      else if(DTwSQMwgql == NoewdpXbWS){wgckxVFuGJ = true;}
      if(PLZmTENGNE == wnOtHDQIwY){jTnMefeqCk = true;}
      else if(wnOtHDQIwY == PLZmTENGNE){LjBDdQHgRM = true;}
      if(AfgMXjeman == fFxunwrlZX){KWMntfrZRg = true;}
      else if(fFxunwrlZX == AfgMXjeman){fUqSnVWnAR = true;}
      if(UBVwMTmWHZ == HZDIaRLBbY){lmnzdoDOuZ = true;}
      else if(HZDIaRLBbY == UBVwMTmWHZ){yyowWbDNuY = true;}
      if(JWtNIsxWSh == bArtiWGDFK){MSSKtbWKaZ = true;}
      else if(bArtiWGDFK == JWtNIsxWSh){dVDmDREodK = true;}
      if(CwUlPhHSYs == GNOqOxWBdU){lCWdBPmwVm = true;}
      else if(GNOqOxWBdU == CwUlPhHSYs){yLnARapJxb = true;}
      if(LkBhxNodZA == TKGSeVjGSo){yGZMxweohp = true;}
      if(QpznudlTDe == qPgWxfMDMR){bPwbXrECtS = true;}
      if(lITrkXgjfe == onfOQsKMsd){JgyrtjQJxO = true;}
      while(TKGSeVjGSo == LkBhxNodZA){zRtnKMuEgB = true;}
      while(qPgWxfMDMR == qPgWxfMDMR){NslsiKRDPV = true;}
      while(onfOQsKMsd == onfOQsKMsd){QgKoSmKoeu = true;}
      if(uKXGFQsZOM == true){uKXGFQsZOM = false;}
      if(mAkQTpgrsi == true){mAkQTpgrsi = false;}
      if(jTnMefeqCk == true){jTnMefeqCk = false;}
      if(KWMntfrZRg == true){KWMntfrZRg = false;}
      if(lmnzdoDOuZ == true){lmnzdoDOuZ = false;}
      if(MSSKtbWKaZ == true){MSSKtbWKaZ = false;}
      if(lCWdBPmwVm == true){lCWdBPmwVm = false;}
      if(yGZMxweohp == true){yGZMxweohp = false;}
      if(bPwbXrECtS == true){bPwbXrECtS = false;}
      if(JgyrtjQJxO == true){JgyrtjQJxO = false;}
      if(CGsHbGsFMx == true){CGsHbGsFMx = false;}
      if(wgckxVFuGJ == true){wgckxVFuGJ = false;}
      if(LjBDdQHgRM == true){LjBDdQHgRM = false;}
      if(fUqSnVWnAR == true){fUqSnVWnAR = false;}
      if(yyowWbDNuY == true){yyowWbDNuY = false;}
      if(dVDmDREodK == true){dVDmDREodK = false;}
      if(yLnARapJxb == true){yLnARapJxb = false;}
      if(zRtnKMuEgB == true){zRtnKMuEgB = false;}
      if(NslsiKRDPV == true){NslsiKRDPV = false;}
      if(QgKoSmKoeu == true){QgKoSmKoeu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YOEXEFYVRV
{ 
  void BUBnCszTta()
  { 
      bool JjLcaTkWYC = false;
      bool YiDczzcsSe = false;
      bool YWhQefdWrM = false;
      bool iYUDJorLFF = false;
      bool eEQOhpdUnn = false;
      bool KctcklBtxu = false;
      bool pNdLTzNzSK = false;
      bool GQmMAUGTin = false;
      bool CJiEBFerSX = false;
      bool mxNJPQZEth = false;
      bool cdBcgtpgcP = false;
      bool fhLIsgeZKN = false;
      bool TUfuWICdxi = false;
      bool tBYBLXIFWH = false;
      bool PyPCrFlFQh = false;
      bool kAtgNHyFFY = false;
      bool qMisVdIJxV = false;
      bool YZDDxVFcDR = false;
      bool WxMOytHrmE = false;
      bool YCzyPDOVgN = false;
      string cwBjfePMDb;
      string wWniGlxhKK;
      string TrapbMiJss;
      string aDPxXSUhpr;
      string XmlgEIiyaz;
      string HgMzmjVLIS;
      string uFSKBsHpKm;
      string ROrRmfGtkS;
      string dkitktpQJm;
      string xJZWxRTbfL;
      string BrmmgsntMH;
      string daZooJWXYG;
      string CpfWpIoVUU;
      string LdOZRkxuMr;
      string GwECJVijgn;
      string uwDYIKLQxY;
      string ERZquzMzXE;
      string MbKfAFlcNT;
      string YEogYPaoQG;
      string YgxnnnWMHJ;
      if(cwBjfePMDb == BrmmgsntMH){JjLcaTkWYC = true;}
      else if(BrmmgsntMH == cwBjfePMDb){cdBcgtpgcP = true;}
      if(wWniGlxhKK == daZooJWXYG){YiDczzcsSe = true;}
      else if(daZooJWXYG == wWniGlxhKK){fhLIsgeZKN = true;}
      if(TrapbMiJss == CpfWpIoVUU){YWhQefdWrM = true;}
      else if(CpfWpIoVUU == TrapbMiJss){TUfuWICdxi = true;}
      if(aDPxXSUhpr == LdOZRkxuMr){iYUDJorLFF = true;}
      else if(LdOZRkxuMr == aDPxXSUhpr){tBYBLXIFWH = true;}
      if(XmlgEIiyaz == GwECJVijgn){eEQOhpdUnn = true;}
      else if(GwECJVijgn == XmlgEIiyaz){PyPCrFlFQh = true;}
      if(HgMzmjVLIS == uwDYIKLQxY){KctcklBtxu = true;}
      else if(uwDYIKLQxY == HgMzmjVLIS){kAtgNHyFFY = true;}
      if(uFSKBsHpKm == ERZquzMzXE){pNdLTzNzSK = true;}
      else if(ERZquzMzXE == uFSKBsHpKm){qMisVdIJxV = true;}
      if(ROrRmfGtkS == MbKfAFlcNT){GQmMAUGTin = true;}
      if(dkitktpQJm == YEogYPaoQG){CJiEBFerSX = true;}
      if(xJZWxRTbfL == YgxnnnWMHJ){mxNJPQZEth = true;}
      while(MbKfAFlcNT == ROrRmfGtkS){YZDDxVFcDR = true;}
      while(YEogYPaoQG == YEogYPaoQG){WxMOytHrmE = true;}
      while(YgxnnnWMHJ == YgxnnnWMHJ){YCzyPDOVgN = true;}
      if(JjLcaTkWYC == true){JjLcaTkWYC = false;}
      if(YiDczzcsSe == true){YiDczzcsSe = false;}
      if(YWhQefdWrM == true){YWhQefdWrM = false;}
      if(iYUDJorLFF == true){iYUDJorLFF = false;}
      if(eEQOhpdUnn == true){eEQOhpdUnn = false;}
      if(KctcklBtxu == true){KctcklBtxu = false;}
      if(pNdLTzNzSK == true){pNdLTzNzSK = false;}
      if(GQmMAUGTin == true){GQmMAUGTin = false;}
      if(CJiEBFerSX == true){CJiEBFerSX = false;}
      if(mxNJPQZEth == true){mxNJPQZEth = false;}
      if(cdBcgtpgcP == true){cdBcgtpgcP = false;}
      if(fhLIsgeZKN == true){fhLIsgeZKN = false;}
      if(TUfuWICdxi == true){TUfuWICdxi = false;}
      if(tBYBLXIFWH == true){tBYBLXIFWH = false;}
      if(PyPCrFlFQh == true){PyPCrFlFQh = false;}
      if(kAtgNHyFFY == true){kAtgNHyFFY = false;}
      if(qMisVdIJxV == true){qMisVdIJxV = false;}
      if(YZDDxVFcDR == true){YZDDxVFcDR = false;}
      if(WxMOytHrmE == true){WxMOytHrmE = false;}
      if(YCzyPDOVgN == true){YCzyPDOVgN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class STFRKJQHFK
{ 
  void ajjiDINPfe()
  { 
      bool UKSRIftwUr = false;
      bool ujhGedsfjS = false;
      bool zVyiQHhNgm = false;
      bool PZrugbELLX = false;
      bool EPxsViwiIo = false;
      bool udTeFyMjBA = false;
      bool xgOgbUrlZD = false;
      bool ZgTLOjYEMg = false;
      bool LzEqrkFMpi = false;
      bool OUJKaXAPQB = false;
      bool pJIFPNJIQV = false;
      bool YIWUoxbXoq = false;
      bool OfwqnEXJkp = false;
      bool iJmLpBpzad = false;
      bool axuTJGxoVc = false;
      bool ubZZlKMRQK = false;
      bool pAXZlPUKdm = false;
      bool GcwKPQjcgh = false;
      bool HhmHtGiMZf = false;
      bool nYhPnaZUgs = false;
      string cxRWBjGjqk;
      string JdYhwDmFcC;
      string LfpTstRPXG;
      string hATngVimpP;
      string SNDnLGRCuT;
      string rSbfKwGycH;
      string RqLjCIKjBa;
      string TAONixbBIm;
      string bPTENOYndj;
      string OkJhxaCTkC;
      string wgAUzrDOwM;
      string TFppeCWGVn;
      string jWGQLhpgPI;
      string uIPFptOzFV;
      string LJrQPJuSCu;
      string EuxxSZaiIR;
      string BWznRKojzj;
      string mXBAbZdpAB;
      string lXdTDzLSlQ;
      string TepmTnKEyF;
      if(cxRWBjGjqk == wgAUzrDOwM){UKSRIftwUr = true;}
      else if(wgAUzrDOwM == cxRWBjGjqk){pJIFPNJIQV = true;}
      if(JdYhwDmFcC == TFppeCWGVn){ujhGedsfjS = true;}
      else if(TFppeCWGVn == JdYhwDmFcC){YIWUoxbXoq = true;}
      if(LfpTstRPXG == jWGQLhpgPI){zVyiQHhNgm = true;}
      else if(jWGQLhpgPI == LfpTstRPXG){OfwqnEXJkp = true;}
      if(hATngVimpP == uIPFptOzFV){PZrugbELLX = true;}
      else if(uIPFptOzFV == hATngVimpP){iJmLpBpzad = true;}
      if(SNDnLGRCuT == LJrQPJuSCu){EPxsViwiIo = true;}
      else if(LJrQPJuSCu == SNDnLGRCuT){axuTJGxoVc = true;}
      if(rSbfKwGycH == EuxxSZaiIR){udTeFyMjBA = true;}
      else if(EuxxSZaiIR == rSbfKwGycH){ubZZlKMRQK = true;}
      if(RqLjCIKjBa == BWznRKojzj){xgOgbUrlZD = true;}
      else if(BWznRKojzj == RqLjCIKjBa){pAXZlPUKdm = true;}
      if(TAONixbBIm == mXBAbZdpAB){ZgTLOjYEMg = true;}
      if(bPTENOYndj == lXdTDzLSlQ){LzEqrkFMpi = true;}
      if(OkJhxaCTkC == TepmTnKEyF){OUJKaXAPQB = true;}
      while(mXBAbZdpAB == TAONixbBIm){GcwKPQjcgh = true;}
      while(lXdTDzLSlQ == lXdTDzLSlQ){HhmHtGiMZf = true;}
      while(TepmTnKEyF == TepmTnKEyF){nYhPnaZUgs = true;}
      if(UKSRIftwUr == true){UKSRIftwUr = false;}
      if(ujhGedsfjS == true){ujhGedsfjS = false;}
      if(zVyiQHhNgm == true){zVyiQHhNgm = false;}
      if(PZrugbELLX == true){PZrugbELLX = false;}
      if(EPxsViwiIo == true){EPxsViwiIo = false;}
      if(udTeFyMjBA == true){udTeFyMjBA = false;}
      if(xgOgbUrlZD == true){xgOgbUrlZD = false;}
      if(ZgTLOjYEMg == true){ZgTLOjYEMg = false;}
      if(LzEqrkFMpi == true){LzEqrkFMpi = false;}
      if(OUJKaXAPQB == true){OUJKaXAPQB = false;}
      if(pJIFPNJIQV == true){pJIFPNJIQV = false;}
      if(YIWUoxbXoq == true){YIWUoxbXoq = false;}
      if(OfwqnEXJkp == true){OfwqnEXJkp = false;}
      if(iJmLpBpzad == true){iJmLpBpzad = false;}
      if(axuTJGxoVc == true){axuTJGxoVc = false;}
      if(ubZZlKMRQK == true){ubZZlKMRQK = false;}
      if(pAXZlPUKdm == true){pAXZlPUKdm = false;}
      if(GcwKPQjcgh == true){GcwKPQjcgh = false;}
      if(HhmHtGiMZf == true){HhmHtGiMZf = false;}
      if(nYhPnaZUgs == true){nYhPnaZUgs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IQAFSUFCFT
{ 
  void UJZllzpcME()
  { 
      bool szKnhrAXri = false;
      bool bzYwlFpekb = false;
      bool AlbEDxrsYs = false;
      bool CgAMFZqohK = false;
      bool HBFmaKSXxt = false;
      bool jxGdOGXFkj = false;
      bool AGyyfuyMpL = false;
      bool NBxaUzgnds = false;
      bool eTwdJFaWxz = false;
      bool ClDxKACGGf = false;
      bool LFhlgizfJP = false;
      bool YibrFfKUna = false;
      bool TbOqJbxAQT = false;
      bool wahygYlJxa = false;
      bool FuMhZSJLqd = false;
      bool phReLjppcE = false;
      bool kzPpSyBdKf = false;
      bool sAWNUYOfQp = false;
      bool RkIlcNIClw = false;
      bool iugroFeWPa = false;
      string jEUXXRacUR;
      string kCXfAezkks;
      string toYeAbaJXG;
      string GcTQeCXBau;
      string AHpmaoJRVq;
      string YLXpHtfoWu;
      string qQFNKHiGAy;
      string HxKprmylEK;
      string SJmfhuEdJk;
      string WideEiCcbS;
      string GCQXjaAgxT;
      string usjLcgcYfP;
      string DFwPbXTflI;
      string kVJlEPrPuG;
      string uXfoocyRBW;
      string FcwMPBGAuL;
      string GUuniZjyHM;
      string oMcYUfYGaz;
      string ZBdPDHYxWC;
      string JqUizacqGO;
      if(jEUXXRacUR == GCQXjaAgxT){szKnhrAXri = true;}
      else if(GCQXjaAgxT == jEUXXRacUR){LFhlgizfJP = true;}
      if(kCXfAezkks == usjLcgcYfP){bzYwlFpekb = true;}
      else if(usjLcgcYfP == kCXfAezkks){YibrFfKUna = true;}
      if(toYeAbaJXG == DFwPbXTflI){AlbEDxrsYs = true;}
      else if(DFwPbXTflI == toYeAbaJXG){TbOqJbxAQT = true;}
      if(GcTQeCXBau == kVJlEPrPuG){CgAMFZqohK = true;}
      else if(kVJlEPrPuG == GcTQeCXBau){wahygYlJxa = true;}
      if(AHpmaoJRVq == uXfoocyRBW){HBFmaKSXxt = true;}
      else if(uXfoocyRBW == AHpmaoJRVq){FuMhZSJLqd = true;}
      if(YLXpHtfoWu == FcwMPBGAuL){jxGdOGXFkj = true;}
      else if(FcwMPBGAuL == YLXpHtfoWu){phReLjppcE = true;}
      if(qQFNKHiGAy == GUuniZjyHM){AGyyfuyMpL = true;}
      else if(GUuniZjyHM == qQFNKHiGAy){kzPpSyBdKf = true;}
      if(HxKprmylEK == oMcYUfYGaz){NBxaUzgnds = true;}
      if(SJmfhuEdJk == ZBdPDHYxWC){eTwdJFaWxz = true;}
      if(WideEiCcbS == JqUizacqGO){ClDxKACGGf = true;}
      while(oMcYUfYGaz == HxKprmylEK){sAWNUYOfQp = true;}
      while(ZBdPDHYxWC == ZBdPDHYxWC){RkIlcNIClw = true;}
      while(JqUizacqGO == JqUizacqGO){iugroFeWPa = true;}
      if(szKnhrAXri == true){szKnhrAXri = false;}
      if(bzYwlFpekb == true){bzYwlFpekb = false;}
      if(AlbEDxrsYs == true){AlbEDxrsYs = false;}
      if(CgAMFZqohK == true){CgAMFZqohK = false;}
      if(HBFmaKSXxt == true){HBFmaKSXxt = false;}
      if(jxGdOGXFkj == true){jxGdOGXFkj = false;}
      if(AGyyfuyMpL == true){AGyyfuyMpL = false;}
      if(NBxaUzgnds == true){NBxaUzgnds = false;}
      if(eTwdJFaWxz == true){eTwdJFaWxz = false;}
      if(ClDxKACGGf == true){ClDxKACGGf = false;}
      if(LFhlgizfJP == true){LFhlgizfJP = false;}
      if(YibrFfKUna == true){YibrFfKUna = false;}
      if(TbOqJbxAQT == true){TbOqJbxAQT = false;}
      if(wahygYlJxa == true){wahygYlJxa = false;}
      if(FuMhZSJLqd == true){FuMhZSJLqd = false;}
      if(phReLjppcE == true){phReLjppcE = false;}
      if(kzPpSyBdKf == true){kzPpSyBdKf = false;}
      if(sAWNUYOfQp == true){sAWNUYOfQp = false;}
      if(RkIlcNIClw == true){RkIlcNIClw = false;}
      if(iugroFeWPa == true){iugroFeWPa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DDXHTBYJCC
{ 
  void PVTAHIUVCu()
  { 
      bool dPeLaVlwih = false;
      bool abqWYATVUf = false;
      bool clIzkaPdVK = false;
      bool qSofTcyByK = false;
      bool AWaRoFsZoc = false;
      bool hKGgJqGfaA = false;
      bool GIZYpImLCw = false;
      bool CSXJeGKqKe = false;
      bool goorbgLIVb = false;
      bool WSZyDrwCag = false;
      bool SgXraPlwCC = false;
      bool gPUuSRShxI = false;
      bool wdoZZirYGl = false;
      bool KIPdMARwQL = false;
      bool tPGSuGydfl = false;
      bool ZNESknrySr = false;
      bool XNoPrXzqiR = false;
      bool zWRkNfXVdS = false;
      bool kOsTMwDxsX = false;
      bool ITcXngZpaX = false;
      string cweBreBkHm;
      string euPSmRjUMa;
      string ExsDclPMzj;
      string jthQXhNRRH;
      string AlcupDLHzl;
      string WbLoBeCaXG;
      string OokXDjNyuE;
      string DSDEZRUyMY;
      string aHMNNHirPs;
      string elsKsKBFqG;
      string oNMthEYGPi;
      string KDOyfGcWJu;
      string AVhBZQYrLO;
      string QOGFiMuReJ;
      string ibbfiaXtel;
      string hdwwGTeKUR;
      string eguBSuxIOS;
      string LLqAMXsCSy;
      string rdMYgmSKzP;
      string hkwNdCgaMm;
      if(cweBreBkHm == oNMthEYGPi){dPeLaVlwih = true;}
      else if(oNMthEYGPi == cweBreBkHm){SgXraPlwCC = true;}
      if(euPSmRjUMa == KDOyfGcWJu){abqWYATVUf = true;}
      else if(KDOyfGcWJu == euPSmRjUMa){gPUuSRShxI = true;}
      if(ExsDclPMzj == AVhBZQYrLO){clIzkaPdVK = true;}
      else if(AVhBZQYrLO == ExsDclPMzj){wdoZZirYGl = true;}
      if(jthQXhNRRH == QOGFiMuReJ){qSofTcyByK = true;}
      else if(QOGFiMuReJ == jthQXhNRRH){KIPdMARwQL = true;}
      if(AlcupDLHzl == ibbfiaXtel){AWaRoFsZoc = true;}
      else if(ibbfiaXtel == AlcupDLHzl){tPGSuGydfl = true;}
      if(WbLoBeCaXG == hdwwGTeKUR){hKGgJqGfaA = true;}
      else if(hdwwGTeKUR == WbLoBeCaXG){ZNESknrySr = true;}
      if(OokXDjNyuE == eguBSuxIOS){GIZYpImLCw = true;}
      else if(eguBSuxIOS == OokXDjNyuE){XNoPrXzqiR = true;}
      if(DSDEZRUyMY == LLqAMXsCSy){CSXJeGKqKe = true;}
      if(aHMNNHirPs == rdMYgmSKzP){goorbgLIVb = true;}
      if(elsKsKBFqG == hkwNdCgaMm){WSZyDrwCag = true;}
      while(LLqAMXsCSy == DSDEZRUyMY){zWRkNfXVdS = true;}
      while(rdMYgmSKzP == rdMYgmSKzP){kOsTMwDxsX = true;}
      while(hkwNdCgaMm == hkwNdCgaMm){ITcXngZpaX = true;}
      if(dPeLaVlwih == true){dPeLaVlwih = false;}
      if(abqWYATVUf == true){abqWYATVUf = false;}
      if(clIzkaPdVK == true){clIzkaPdVK = false;}
      if(qSofTcyByK == true){qSofTcyByK = false;}
      if(AWaRoFsZoc == true){AWaRoFsZoc = false;}
      if(hKGgJqGfaA == true){hKGgJqGfaA = false;}
      if(GIZYpImLCw == true){GIZYpImLCw = false;}
      if(CSXJeGKqKe == true){CSXJeGKqKe = false;}
      if(goorbgLIVb == true){goorbgLIVb = false;}
      if(WSZyDrwCag == true){WSZyDrwCag = false;}
      if(SgXraPlwCC == true){SgXraPlwCC = false;}
      if(gPUuSRShxI == true){gPUuSRShxI = false;}
      if(wdoZZirYGl == true){wdoZZirYGl = false;}
      if(KIPdMARwQL == true){KIPdMARwQL = false;}
      if(tPGSuGydfl == true){tPGSuGydfl = false;}
      if(ZNESknrySr == true){ZNESknrySr = false;}
      if(XNoPrXzqiR == true){XNoPrXzqiR = false;}
      if(zWRkNfXVdS == true){zWRkNfXVdS = false;}
      if(kOsTMwDxsX == true){kOsTMwDxsX = false;}
      if(ITcXngZpaX == true){ITcXngZpaX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EATCLFWBDE
{ 
  void xcWhcOPSRB()
  { 
      bool DNZLNUrawy = false;
      bool xQQBnaihIZ = false;
      bool QcnPWIWTbD = false;
      bool EWrdtyFZWN = false;
      bool idLtYCcrMW = false;
      bool ATaaPaYJoF = false;
      bool yYzrtZXmGp = false;
      bool VIKtplRtqT = false;
      bool eeGEDjwRNT = false;
      bool YukRPKeTzz = false;
      bool dpkWBqJfjd = false;
      bool IeSUZTRtnJ = false;
      bool cGYlQZWref = false;
      bool GytrpnsjCL = false;
      bool aQgjKsbQqw = false;
      bool rkeoVXRyFa = false;
      bool UQBEWKkaek = false;
      bool ZgqbiMZnbW = false;
      bool yGAhmVSEVS = false;
      bool WuebqJObMz = false;
      string GrVoaGDSso;
      string ClreIFIgwy;
      string etzRSZfPqN;
      string ipPEpHbsWL;
      string iJJgpHrakj;
      string LTDbMMsEWB;
      string anbfGMVmoA;
      string dOKkPVjRaK;
      string hEdHBOlnrd;
      string OXWVktgdad;
      string kEkkGxJSMp;
      string bacLTVJUdq;
      string ZhuLkGqnAU;
      string nFqwZcTsAE;
      string ETaCBmtLCP;
      string kMAiEDJZzA;
      string GUSrBVjglp;
      string BPTZmFGsJy;
      string LeljibFHrV;
      string TssAyiBiAf;
      if(GrVoaGDSso == kEkkGxJSMp){DNZLNUrawy = true;}
      else if(kEkkGxJSMp == GrVoaGDSso){dpkWBqJfjd = true;}
      if(ClreIFIgwy == bacLTVJUdq){xQQBnaihIZ = true;}
      else if(bacLTVJUdq == ClreIFIgwy){IeSUZTRtnJ = true;}
      if(etzRSZfPqN == ZhuLkGqnAU){QcnPWIWTbD = true;}
      else if(ZhuLkGqnAU == etzRSZfPqN){cGYlQZWref = true;}
      if(ipPEpHbsWL == nFqwZcTsAE){EWrdtyFZWN = true;}
      else if(nFqwZcTsAE == ipPEpHbsWL){GytrpnsjCL = true;}
      if(iJJgpHrakj == ETaCBmtLCP){idLtYCcrMW = true;}
      else if(ETaCBmtLCP == iJJgpHrakj){aQgjKsbQqw = true;}
      if(LTDbMMsEWB == kMAiEDJZzA){ATaaPaYJoF = true;}
      else if(kMAiEDJZzA == LTDbMMsEWB){rkeoVXRyFa = true;}
      if(anbfGMVmoA == GUSrBVjglp){yYzrtZXmGp = true;}
      else if(GUSrBVjglp == anbfGMVmoA){UQBEWKkaek = true;}
      if(dOKkPVjRaK == BPTZmFGsJy){VIKtplRtqT = true;}
      if(hEdHBOlnrd == LeljibFHrV){eeGEDjwRNT = true;}
      if(OXWVktgdad == TssAyiBiAf){YukRPKeTzz = true;}
      while(BPTZmFGsJy == dOKkPVjRaK){ZgqbiMZnbW = true;}
      while(LeljibFHrV == LeljibFHrV){yGAhmVSEVS = true;}
      while(TssAyiBiAf == TssAyiBiAf){WuebqJObMz = true;}
      if(DNZLNUrawy == true){DNZLNUrawy = false;}
      if(xQQBnaihIZ == true){xQQBnaihIZ = false;}
      if(QcnPWIWTbD == true){QcnPWIWTbD = false;}
      if(EWrdtyFZWN == true){EWrdtyFZWN = false;}
      if(idLtYCcrMW == true){idLtYCcrMW = false;}
      if(ATaaPaYJoF == true){ATaaPaYJoF = false;}
      if(yYzrtZXmGp == true){yYzrtZXmGp = false;}
      if(VIKtplRtqT == true){VIKtplRtqT = false;}
      if(eeGEDjwRNT == true){eeGEDjwRNT = false;}
      if(YukRPKeTzz == true){YukRPKeTzz = false;}
      if(dpkWBqJfjd == true){dpkWBqJfjd = false;}
      if(IeSUZTRtnJ == true){IeSUZTRtnJ = false;}
      if(cGYlQZWref == true){cGYlQZWref = false;}
      if(GytrpnsjCL == true){GytrpnsjCL = false;}
      if(aQgjKsbQqw == true){aQgjKsbQqw = false;}
      if(rkeoVXRyFa == true){rkeoVXRyFa = false;}
      if(UQBEWKkaek == true){UQBEWKkaek = false;}
      if(ZgqbiMZnbW == true){ZgqbiMZnbW = false;}
      if(yGAhmVSEVS == true){yGAhmVSEVS = false;}
      if(WuebqJObMz == true){WuebqJObMz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FFWPXVKWQS
{ 
  void kSWmRjLHXa()
  { 
      bool VmFgFxQBac = false;
      bool ZSfSLBdreT = false;
      bool rBsZmpVMlh = false;
      bool mjUQUcJcqC = false;
      bool AzMarDnxQJ = false;
      bool xxQAqUtftO = false;
      bool bEPsopxPyi = false;
      bool rBBcTsnRgj = false;
      bool CYuckpSTYA = false;
      bool hcibauiTkB = false;
      bool FYzhQuwngy = false;
      bool fbyKMCImIz = false;
      bool XdpxAORZCX = false;
      bool JTgfddZMLo = false;
      bool tdmaTFeYOX = false;
      bool mwLldbhBgC = false;
      bool dVlInMuSfi = false;
      bool cubSFspPdt = false;
      bool jsKdkNHuBC = false;
      bool uXfJLXqelG = false;
      string CTuJKRPVpH;
      string SkBAsEubGU;
      string wfXUEqkUwK;
      string aeksuTPTxL;
      string pYFpAPKTjQ;
      string EUxseVuZFT;
      string fuYffnAIFZ;
      string oaetdWahUn;
      string fRjfFGgqNZ;
      string XoOdftAZJL;
      string PCOKacpDOI;
      string uNFQmOLsZZ;
      string GItfBzMBNi;
      string WAXIYdCYEb;
      string PdbFdKjxpR;
      string iGzjFGHhJb;
      string QooektowrJ;
      string LloxJcfoBp;
      string POKwAQBnDR;
      string VUPcLaowUj;
      if(CTuJKRPVpH == PCOKacpDOI){VmFgFxQBac = true;}
      else if(PCOKacpDOI == CTuJKRPVpH){FYzhQuwngy = true;}
      if(SkBAsEubGU == uNFQmOLsZZ){ZSfSLBdreT = true;}
      else if(uNFQmOLsZZ == SkBAsEubGU){fbyKMCImIz = true;}
      if(wfXUEqkUwK == GItfBzMBNi){rBsZmpVMlh = true;}
      else if(GItfBzMBNi == wfXUEqkUwK){XdpxAORZCX = true;}
      if(aeksuTPTxL == WAXIYdCYEb){mjUQUcJcqC = true;}
      else if(WAXIYdCYEb == aeksuTPTxL){JTgfddZMLo = true;}
      if(pYFpAPKTjQ == PdbFdKjxpR){AzMarDnxQJ = true;}
      else if(PdbFdKjxpR == pYFpAPKTjQ){tdmaTFeYOX = true;}
      if(EUxseVuZFT == iGzjFGHhJb){xxQAqUtftO = true;}
      else if(iGzjFGHhJb == EUxseVuZFT){mwLldbhBgC = true;}
      if(fuYffnAIFZ == QooektowrJ){bEPsopxPyi = true;}
      else if(QooektowrJ == fuYffnAIFZ){dVlInMuSfi = true;}
      if(oaetdWahUn == LloxJcfoBp){rBBcTsnRgj = true;}
      if(fRjfFGgqNZ == POKwAQBnDR){CYuckpSTYA = true;}
      if(XoOdftAZJL == VUPcLaowUj){hcibauiTkB = true;}
      while(LloxJcfoBp == oaetdWahUn){cubSFspPdt = true;}
      while(POKwAQBnDR == POKwAQBnDR){jsKdkNHuBC = true;}
      while(VUPcLaowUj == VUPcLaowUj){uXfJLXqelG = true;}
      if(VmFgFxQBac == true){VmFgFxQBac = false;}
      if(ZSfSLBdreT == true){ZSfSLBdreT = false;}
      if(rBsZmpVMlh == true){rBsZmpVMlh = false;}
      if(mjUQUcJcqC == true){mjUQUcJcqC = false;}
      if(AzMarDnxQJ == true){AzMarDnxQJ = false;}
      if(xxQAqUtftO == true){xxQAqUtftO = false;}
      if(bEPsopxPyi == true){bEPsopxPyi = false;}
      if(rBBcTsnRgj == true){rBBcTsnRgj = false;}
      if(CYuckpSTYA == true){CYuckpSTYA = false;}
      if(hcibauiTkB == true){hcibauiTkB = false;}
      if(FYzhQuwngy == true){FYzhQuwngy = false;}
      if(fbyKMCImIz == true){fbyKMCImIz = false;}
      if(XdpxAORZCX == true){XdpxAORZCX = false;}
      if(JTgfddZMLo == true){JTgfddZMLo = false;}
      if(tdmaTFeYOX == true){tdmaTFeYOX = false;}
      if(mwLldbhBgC == true){mwLldbhBgC = false;}
      if(dVlInMuSfi == true){dVlInMuSfi = false;}
      if(cubSFspPdt == true){cubSFspPdt = false;}
      if(jsKdkNHuBC == true){jsKdkNHuBC = false;}
      if(uXfJLXqelG == true){uXfJLXqelG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZDSTNMKDRC
{ 
  void ULXjTCXmQC()
  { 
      bool nlOYgLfmWc = false;
      bool HYqOXKNGdL = false;
      bool ONGYqUKEaj = false;
      bool WuFcmDHfQh = false;
      bool wEQxpKrpsh = false;
      bool INIQVZfphL = false;
      bool AbLlGLSNbT = false;
      bool ChouPJxJig = false;
      bool cTKsaJmnHN = false;
      bool XRxEhUrdqd = false;
      bool qdOZfaXMBL = false;
      bool bVHBifQSLx = false;
      bool YeGNukjkNt = false;
      bool QTSEpzFkNz = false;
      bool lZmukBKwVB = false;
      bool EZStEMWAdt = false;
      bool plzHtIDCKj = false;
      bool afFLLzqLcs = false;
      bool ZnOMpqAYzd = false;
      bool bEHSIzZeBc = false;
      string KikULgBiOQ;
      string eBVwoAZFVP;
      string mHZhstxkeG;
      string GGGjyPwViL;
      string FGHiGatDfb;
      string rtwDzDICbR;
      string jQDHJYtkxY;
      string EDWJJgzpbS;
      string zsEDOMKDkt;
      string HttRbnCAZh;
      string fIGHXoXlsS;
      string ERaIRqMAsw;
      string OqACQJIEhV;
      string dyQslqmweY;
      string oXJRpoTkzk;
      string bBGdToHDpN;
      string gSDXnFBgWa;
      string DPVTGpgiMb;
      string pWExtcqmZx;
      string iiFQrWTlcj;
      if(KikULgBiOQ == fIGHXoXlsS){nlOYgLfmWc = true;}
      else if(fIGHXoXlsS == KikULgBiOQ){qdOZfaXMBL = true;}
      if(eBVwoAZFVP == ERaIRqMAsw){HYqOXKNGdL = true;}
      else if(ERaIRqMAsw == eBVwoAZFVP){bVHBifQSLx = true;}
      if(mHZhstxkeG == OqACQJIEhV){ONGYqUKEaj = true;}
      else if(OqACQJIEhV == mHZhstxkeG){YeGNukjkNt = true;}
      if(GGGjyPwViL == dyQslqmweY){WuFcmDHfQh = true;}
      else if(dyQslqmweY == GGGjyPwViL){QTSEpzFkNz = true;}
      if(FGHiGatDfb == oXJRpoTkzk){wEQxpKrpsh = true;}
      else if(oXJRpoTkzk == FGHiGatDfb){lZmukBKwVB = true;}
      if(rtwDzDICbR == bBGdToHDpN){INIQVZfphL = true;}
      else if(bBGdToHDpN == rtwDzDICbR){EZStEMWAdt = true;}
      if(jQDHJYtkxY == gSDXnFBgWa){AbLlGLSNbT = true;}
      else if(gSDXnFBgWa == jQDHJYtkxY){plzHtIDCKj = true;}
      if(EDWJJgzpbS == DPVTGpgiMb){ChouPJxJig = true;}
      if(zsEDOMKDkt == pWExtcqmZx){cTKsaJmnHN = true;}
      if(HttRbnCAZh == iiFQrWTlcj){XRxEhUrdqd = true;}
      while(DPVTGpgiMb == EDWJJgzpbS){afFLLzqLcs = true;}
      while(pWExtcqmZx == pWExtcqmZx){ZnOMpqAYzd = true;}
      while(iiFQrWTlcj == iiFQrWTlcj){bEHSIzZeBc = true;}
      if(nlOYgLfmWc == true){nlOYgLfmWc = false;}
      if(HYqOXKNGdL == true){HYqOXKNGdL = false;}
      if(ONGYqUKEaj == true){ONGYqUKEaj = false;}
      if(WuFcmDHfQh == true){WuFcmDHfQh = false;}
      if(wEQxpKrpsh == true){wEQxpKrpsh = false;}
      if(INIQVZfphL == true){INIQVZfphL = false;}
      if(AbLlGLSNbT == true){AbLlGLSNbT = false;}
      if(ChouPJxJig == true){ChouPJxJig = false;}
      if(cTKsaJmnHN == true){cTKsaJmnHN = false;}
      if(XRxEhUrdqd == true){XRxEhUrdqd = false;}
      if(qdOZfaXMBL == true){qdOZfaXMBL = false;}
      if(bVHBifQSLx == true){bVHBifQSLx = false;}
      if(YeGNukjkNt == true){YeGNukjkNt = false;}
      if(QTSEpzFkNz == true){QTSEpzFkNz = false;}
      if(lZmukBKwVB == true){lZmukBKwVB = false;}
      if(EZStEMWAdt == true){EZStEMWAdt = false;}
      if(plzHtIDCKj == true){plzHtIDCKj = false;}
      if(afFLLzqLcs == true){afFLLzqLcs = false;}
      if(ZnOMpqAYzd == true){ZnOMpqAYzd = false;}
      if(bEHSIzZeBc == true){bEHSIzZeBc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VVDRYWYRBE
{ 
  void iYpEBFfNpP()
  { 
      bool EVofUcHrTV = false;
      bool JpuJxNgQiW = false;
      bool ZUdGQaaKbT = false;
      bool VALUfElLDi = false;
      bool dMKrrJKJEs = false;
      bool mRCQwiqiPs = false;
      bool CxPAAIeZcs = false;
      bool bVMzrNJkNG = false;
      bool QRFhfEyuYw = false;
      bool MCuJggwJri = false;
      bool ejfLRRECXi = false;
      bool ZGUIcjqhUu = false;
      bool KiAffYZCSL = false;
      bool QArdbfktQN = false;
      bool AuXpWFgmgw = false;
      bool oOoxYujzes = false;
      bool rBjLRZNqfx = false;
      bool zxQGtOLKIa = false;
      bool qlVVVCKuFg = false;
      bool wlOWUyLLXx = false;
      string WahUkHHEiI;
      string UfkLeGybbt;
      string qbLICHJEgw;
      string QFDiHDVVhZ;
      string feqhQqjkJu;
      string oISrauOZSd;
      string yCXlqOcBEb;
      string jbsCNMkcqL;
      string WYukHImKIL;
      string nwDEbdGEqB;
      string NhfhLMOPdN;
      string KkhGGZHldh;
      string aRssmnXoai;
      string FfloyorNZu;
      string tWftBCNxxB;
      string WTaIauomtW;
      string nYouHeyrIQ;
      string gtMinElyqj;
      string ZarYMkEdOC;
      string AFSCGUhkmV;
      if(WahUkHHEiI == NhfhLMOPdN){EVofUcHrTV = true;}
      else if(NhfhLMOPdN == WahUkHHEiI){ejfLRRECXi = true;}
      if(UfkLeGybbt == KkhGGZHldh){JpuJxNgQiW = true;}
      else if(KkhGGZHldh == UfkLeGybbt){ZGUIcjqhUu = true;}
      if(qbLICHJEgw == aRssmnXoai){ZUdGQaaKbT = true;}
      else if(aRssmnXoai == qbLICHJEgw){KiAffYZCSL = true;}
      if(QFDiHDVVhZ == FfloyorNZu){VALUfElLDi = true;}
      else if(FfloyorNZu == QFDiHDVVhZ){QArdbfktQN = true;}
      if(feqhQqjkJu == tWftBCNxxB){dMKrrJKJEs = true;}
      else if(tWftBCNxxB == feqhQqjkJu){AuXpWFgmgw = true;}
      if(oISrauOZSd == WTaIauomtW){mRCQwiqiPs = true;}
      else if(WTaIauomtW == oISrauOZSd){oOoxYujzes = true;}
      if(yCXlqOcBEb == nYouHeyrIQ){CxPAAIeZcs = true;}
      else if(nYouHeyrIQ == yCXlqOcBEb){rBjLRZNqfx = true;}
      if(jbsCNMkcqL == gtMinElyqj){bVMzrNJkNG = true;}
      if(WYukHImKIL == ZarYMkEdOC){QRFhfEyuYw = true;}
      if(nwDEbdGEqB == AFSCGUhkmV){MCuJggwJri = true;}
      while(gtMinElyqj == jbsCNMkcqL){zxQGtOLKIa = true;}
      while(ZarYMkEdOC == ZarYMkEdOC){qlVVVCKuFg = true;}
      while(AFSCGUhkmV == AFSCGUhkmV){wlOWUyLLXx = true;}
      if(EVofUcHrTV == true){EVofUcHrTV = false;}
      if(JpuJxNgQiW == true){JpuJxNgQiW = false;}
      if(ZUdGQaaKbT == true){ZUdGQaaKbT = false;}
      if(VALUfElLDi == true){VALUfElLDi = false;}
      if(dMKrrJKJEs == true){dMKrrJKJEs = false;}
      if(mRCQwiqiPs == true){mRCQwiqiPs = false;}
      if(CxPAAIeZcs == true){CxPAAIeZcs = false;}
      if(bVMzrNJkNG == true){bVMzrNJkNG = false;}
      if(QRFhfEyuYw == true){QRFhfEyuYw = false;}
      if(MCuJggwJri == true){MCuJggwJri = false;}
      if(ejfLRRECXi == true){ejfLRRECXi = false;}
      if(ZGUIcjqhUu == true){ZGUIcjqhUu = false;}
      if(KiAffYZCSL == true){KiAffYZCSL = false;}
      if(QArdbfktQN == true){QArdbfktQN = false;}
      if(AuXpWFgmgw == true){AuXpWFgmgw = false;}
      if(oOoxYujzes == true){oOoxYujzes = false;}
      if(rBjLRZNqfx == true){rBjLRZNqfx = false;}
      if(zxQGtOLKIa == true){zxQGtOLKIa = false;}
      if(qlVVVCKuFg == true){qlVVVCKuFg = false;}
      if(wlOWUyLLXx == true){wlOWUyLLXx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XMJFYAXGGV
{ 
  void WDMJIByLqe()
  { 
      bool JkxqNohbca = false;
      bool qCCiyFzYjQ = false;
      bool iJtHirzNUQ = false;
      bool TOGKwGFWji = false;
      bool JczUcHuZHS = false;
      bool TwzGmAqoHV = false;
      bool pUGMGburmr = false;
      bool zbnAGFJZdb = false;
      bool xYFCxXOAWw = false;
      bool PQPOsoVmNA = false;
      bool LDmPTqHzzh = false;
      bool pQKfYQOEPi = false;
      bool MtUpbhMZHQ = false;
      bool jWMdPskphF = false;
      bool QPAoGyFipb = false;
      bool ZQWemQhwmk = false;
      bool ehqhxSEgPe = false;
      bool fYWJRwtejc = false;
      bool ccjfqSAgpy = false;
      bool KoCwahYRqm = false;
      string yCEbdgLhei;
      string VzlcrcfDsk;
      string zKHytNzKLn;
      string YXhuMShrjL;
      string HnmnrAgqSE;
      string XeHJNmtGgP;
      string gAWqKxQqQZ;
      string umSgcKXSFt;
      string fIrGQsQYhZ;
      string XbLTdGRwdu;
      string ipZrJjMZfC;
      string PbAmjYIPZQ;
      string frJqCTbyDW;
      string saoKKphzwg;
      string gqseJwaYjE;
      string yBVMPpfipp;
      string INWIInlobs;
      string qISsjnzdgG;
      string rDOyYrFcuT;
      string JyJFXSUjWV;
      if(yCEbdgLhei == ipZrJjMZfC){JkxqNohbca = true;}
      else if(ipZrJjMZfC == yCEbdgLhei){LDmPTqHzzh = true;}
      if(VzlcrcfDsk == PbAmjYIPZQ){qCCiyFzYjQ = true;}
      else if(PbAmjYIPZQ == VzlcrcfDsk){pQKfYQOEPi = true;}
      if(zKHytNzKLn == frJqCTbyDW){iJtHirzNUQ = true;}
      else if(frJqCTbyDW == zKHytNzKLn){MtUpbhMZHQ = true;}
      if(YXhuMShrjL == saoKKphzwg){TOGKwGFWji = true;}
      else if(saoKKphzwg == YXhuMShrjL){jWMdPskphF = true;}
      if(HnmnrAgqSE == gqseJwaYjE){JczUcHuZHS = true;}
      else if(gqseJwaYjE == HnmnrAgqSE){QPAoGyFipb = true;}
      if(XeHJNmtGgP == yBVMPpfipp){TwzGmAqoHV = true;}
      else if(yBVMPpfipp == XeHJNmtGgP){ZQWemQhwmk = true;}
      if(gAWqKxQqQZ == INWIInlobs){pUGMGburmr = true;}
      else if(INWIInlobs == gAWqKxQqQZ){ehqhxSEgPe = true;}
      if(umSgcKXSFt == qISsjnzdgG){zbnAGFJZdb = true;}
      if(fIrGQsQYhZ == rDOyYrFcuT){xYFCxXOAWw = true;}
      if(XbLTdGRwdu == JyJFXSUjWV){PQPOsoVmNA = true;}
      while(qISsjnzdgG == umSgcKXSFt){fYWJRwtejc = true;}
      while(rDOyYrFcuT == rDOyYrFcuT){ccjfqSAgpy = true;}
      while(JyJFXSUjWV == JyJFXSUjWV){KoCwahYRqm = true;}
      if(JkxqNohbca == true){JkxqNohbca = false;}
      if(qCCiyFzYjQ == true){qCCiyFzYjQ = false;}
      if(iJtHirzNUQ == true){iJtHirzNUQ = false;}
      if(TOGKwGFWji == true){TOGKwGFWji = false;}
      if(JczUcHuZHS == true){JczUcHuZHS = false;}
      if(TwzGmAqoHV == true){TwzGmAqoHV = false;}
      if(pUGMGburmr == true){pUGMGburmr = false;}
      if(zbnAGFJZdb == true){zbnAGFJZdb = false;}
      if(xYFCxXOAWw == true){xYFCxXOAWw = false;}
      if(PQPOsoVmNA == true){PQPOsoVmNA = false;}
      if(LDmPTqHzzh == true){LDmPTqHzzh = false;}
      if(pQKfYQOEPi == true){pQKfYQOEPi = false;}
      if(MtUpbhMZHQ == true){MtUpbhMZHQ = false;}
      if(jWMdPskphF == true){jWMdPskphF = false;}
      if(QPAoGyFipb == true){QPAoGyFipb = false;}
      if(ZQWemQhwmk == true){ZQWemQhwmk = false;}
      if(ehqhxSEgPe == true){ehqhxSEgPe = false;}
      if(fYWJRwtejc == true){fYWJRwtejc = false;}
      if(ccjfqSAgpy == true){ccjfqSAgpy = false;}
      if(KoCwahYRqm == true){KoCwahYRqm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYUWJLDHXQ
{ 
  void wEdJrZLKlR()
  { 
      bool ZYsexfMEoP = false;
      bool IeFaXcWEAE = false;
      bool jOsfoMDWXD = false;
      bool jgzDJNslfX = false;
      bool yQWrHGSzUq = false;
      bool yidTVKfMpj = false;
      bool cpgkfbeCQK = false;
      bool jkXbGSrBYi = false;
      bool tEBfEBCfgy = false;
      bool hfwuuIikMe = false;
      bool aQhKHNKCNC = false;
      bool SdnHpYnAfd = false;
      bool ZzURbDnbgx = false;
      bool jHosHcVqYp = false;
      bool pASdfDqoFV = false;
      bool TiEhFbuPhD = false;
      bool YhVPSKouzM = false;
      bool CxbpmYfqlY = false;
      bool LzWKdBCGne = false;
      bool gGIURIeDKV = false;
      string eHgmgGNfRs;
      string oEeBNbAlaH;
      string fQhLHOKQjP;
      string igIexaqCoF;
      string UtZIlJNmiH;
      string oKRFoOZUeR;
      string wwwBJHwADl;
      string jywVmlqYYy;
      string BWhbZYPCpi;
      string BWWXIXxXzd;
      string NMiwXqNuSD;
      string XAwgPYOTak;
      string qsKUkNbYNO;
      string nSZtjnmkDi;
      string KUilLAaoHi;
      string JcxOlTCOLK;
      string OohEOFaBwb;
      string lcQrZWKXJj;
      string mlRdEKULHQ;
      string lYZsTVmdXF;
      if(eHgmgGNfRs == NMiwXqNuSD){ZYsexfMEoP = true;}
      else if(NMiwXqNuSD == eHgmgGNfRs){aQhKHNKCNC = true;}
      if(oEeBNbAlaH == XAwgPYOTak){IeFaXcWEAE = true;}
      else if(XAwgPYOTak == oEeBNbAlaH){SdnHpYnAfd = true;}
      if(fQhLHOKQjP == qsKUkNbYNO){jOsfoMDWXD = true;}
      else if(qsKUkNbYNO == fQhLHOKQjP){ZzURbDnbgx = true;}
      if(igIexaqCoF == nSZtjnmkDi){jgzDJNslfX = true;}
      else if(nSZtjnmkDi == igIexaqCoF){jHosHcVqYp = true;}
      if(UtZIlJNmiH == KUilLAaoHi){yQWrHGSzUq = true;}
      else if(KUilLAaoHi == UtZIlJNmiH){pASdfDqoFV = true;}
      if(oKRFoOZUeR == JcxOlTCOLK){yidTVKfMpj = true;}
      else if(JcxOlTCOLK == oKRFoOZUeR){TiEhFbuPhD = true;}
      if(wwwBJHwADl == OohEOFaBwb){cpgkfbeCQK = true;}
      else if(OohEOFaBwb == wwwBJHwADl){YhVPSKouzM = true;}
      if(jywVmlqYYy == lcQrZWKXJj){jkXbGSrBYi = true;}
      if(BWhbZYPCpi == mlRdEKULHQ){tEBfEBCfgy = true;}
      if(BWWXIXxXzd == lYZsTVmdXF){hfwuuIikMe = true;}
      while(lcQrZWKXJj == jywVmlqYYy){CxbpmYfqlY = true;}
      while(mlRdEKULHQ == mlRdEKULHQ){LzWKdBCGne = true;}
      while(lYZsTVmdXF == lYZsTVmdXF){gGIURIeDKV = true;}
      if(ZYsexfMEoP == true){ZYsexfMEoP = false;}
      if(IeFaXcWEAE == true){IeFaXcWEAE = false;}
      if(jOsfoMDWXD == true){jOsfoMDWXD = false;}
      if(jgzDJNslfX == true){jgzDJNslfX = false;}
      if(yQWrHGSzUq == true){yQWrHGSzUq = false;}
      if(yidTVKfMpj == true){yidTVKfMpj = false;}
      if(cpgkfbeCQK == true){cpgkfbeCQK = false;}
      if(jkXbGSrBYi == true){jkXbGSrBYi = false;}
      if(tEBfEBCfgy == true){tEBfEBCfgy = false;}
      if(hfwuuIikMe == true){hfwuuIikMe = false;}
      if(aQhKHNKCNC == true){aQhKHNKCNC = false;}
      if(SdnHpYnAfd == true){SdnHpYnAfd = false;}
      if(ZzURbDnbgx == true){ZzURbDnbgx = false;}
      if(jHosHcVqYp == true){jHosHcVqYp = false;}
      if(pASdfDqoFV == true){pASdfDqoFV = false;}
      if(TiEhFbuPhD == true){TiEhFbuPhD = false;}
      if(YhVPSKouzM == true){YhVPSKouzM = false;}
      if(CxbpmYfqlY == true){CxbpmYfqlY = false;}
      if(LzWKdBCGne == true){LzWKdBCGne = false;}
      if(gGIURIeDKV == true){gGIURIeDKV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RYHUPPTQHS
{ 
  void FRXbwizhVZ()
  { 
      bool xOSuUUbjoQ = false;
      bool WzXguexeSu = false;
      bool HHESxdTXyr = false;
      bool leWenEwdwf = false;
      bool AWFwzxdzQn = false;
      bool tWpSCpJAxp = false;
      bool BElxdrbssp = false;
      bool iTimukBITA = false;
      bool ATGKyOnEcx = false;
      bool twfGdukISG = false;
      bool UkGZFanCXQ = false;
      bool nBfxpgyazO = false;
      bool DXPuulmcIz = false;
      bool AspMeONfEW = false;
      bool akfMIsPhQx = false;
      bool xJIDCxVKeS = false;
      bool mLsXQuKTSa = false;
      bool SRWbnRqDlC = false;
      bool VEMLBpjlJh = false;
      bool sDBkjPqHuN = false;
      string LmHDCXVaQV;
      string wnyfweOWET;
      string nrVKWehQXC;
      string UsDYSnNLom;
      string abyaxMkpMg;
      string VSejZTRxgW;
      string oEDNBCjYNH;
      string QCgQsMttMJ;
      string trEqgBNTzy;
      string WQeRyVXjZt;
      string bLbEPSlOpM;
      string YWjWcwALgz;
      string nQZOkAXORW;
      string nKUShiPzbO;
      string PzcmYzfIoB;
      string VMCZFLlNSO;
      string tWwTXOCRot;
      string gAjSjonlol;
      string TPYQAbHtMV;
      string wCgMTrCIOJ;
      if(LmHDCXVaQV == bLbEPSlOpM){xOSuUUbjoQ = true;}
      else if(bLbEPSlOpM == LmHDCXVaQV){UkGZFanCXQ = true;}
      if(wnyfweOWET == YWjWcwALgz){WzXguexeSu = true;}
      else if(YWjWcwALgz == wnyfweOWET){nBfxpgyazO = true;}
      if(nrVKWehQXC == nQZOkAXORW){HHESxdTXyr = true;}
      else if(nQZOkAXORW == nrVKWehQXC){DXPuulmcIz = true;}
      if(UsDYSnNLom == nKUShiPzbO){leWenEwdwf = true;}
      else if(nKUShiPzbO == UsDYSnNLom){AspMeONfEW = true;}
      if(abyaxMkpMg == PzcmYzfIoB){AWFwzxdzQn = true;}
      else if(PzcmYzfIoB == abyaxMkpMg){akfMIsPhQx = true;}
      if(VSejZTRxgW == VMCZFLlNSO){tWpSCpJAxp = true;}
      else if(VMCZFLlNSO == VSejZTRxgW){xJIDCxVKeS = true;}
      if(oEDNBCjYNH == tWwTXOCRot){BElxdrbssp = true;}
      else if(tWwTXOCRot == oEDNBCjYNH){mLsXQuKTSa = true;}
      if(QCgQsMttMJ == gAjSjonlol){iTimukBITA = true;}
      if(trEqgBNTzy == TPYQAbHtMV){ATGKyOnEcx = true;}
      if(WQeRyVXjZt == wCgMTrCIOJ){twfGdukISG = true;}
      while(gAjSjonlol == QCgQsMttMJ){SRWbnRqDlC = true;}
      while(TPYQAbHtMV == TPYQAbHtMV){VEMLBpjlJh = true;}
      while(wCgMTrCIOJ == wCgMTrCIOJ){sDBkjPqHuN = true;}
      if(xOSuUUbjoQ == true){xOSuUUbjoQ = false;}
      if(WzXguexeSu == true){WzXguexeSu = false;}
      if(HHESxdTXyr == true){HHESxdTXyr = false;}
      if(leWenEwdwf == true){leWenEwdwf = false;}
      if(AWFwzxdzQn == true){AWFwzxdzQn = false;}
      if(tWpSCpJAxp == true){tWpSCpJAxp = false;}
      if(BElxdrbssp == true){BElxdrbssp = false;}
      if(iTimukBITA == true){iTimukBITA = false;}
      if(ATGKyOnEcx == true){ATGKyOnEcx = false;}
      if(twfGdukISG == true){twfGdukISG = false;}
      if(UkGZFanCXQ == true){UkGZFanCXQ = false;}
      if(nBfxpgyazO == true){nBfxpgyazO = false;}
      if(DXPuulmcIz == true){DXPuulmcIz = false;}
      if(AspMeONfEW == true){AspMeONfEW = false;}
      if(akfMIsPhQx == true){akfMIsPhQx = false;}
      if(xJIDCxVKeS == true){xJIDCxVKeS = false;}
      if(mLsXQuKTSa == true){mLsXQuKTSa = false;}
      if(SRWbnRqDlC == true){SRWbnRqDlC = false;}
      if(VEMLBpjlJh == true){VEMLBpjlJh = false;}
      if(sDBkjPqHuN == true){sDBkjPqHuN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFDKHBPMME
{ 
  void CQbcDcByew()
  { 
      bool sqgmusTITD = false;
      bool GlAQjfnaZa = false;
      bool uffNBFZTmC = false;
      bool qELawGfKEH = false;
      bool wWQMofNhVL = false;
      bool GaOdFNLSlp = false;
      bool TzURLCaZUd = false;
      bool zcVSeYOSYV = false;
      bool qrybuQphUi = false;
      bool tMYNmwByAm = false;
      bool FmNrLcEwyg = false;
      bool yrtQybAsVt = false;
      bool MrFkimEIeh = false;
      bool WPSlQEdGPS = false;
      bool MtimkCSHOL = false;
      bool wIcGaMhbJY = false;
      bool YuQQKhZHAt = false;
      bool xtcDgRJRAf = false;
      bool UwsSlNmMLE = false;
      bool VCxqsRcScC = false;
      string qJRfaZmebY;
      string mlWVRIAREF;
      string zXuhZEmuHe;
      string UzUOqpdAQN;
      string ogAzEYVMiy;
      string wtgKSSOjFV;
      string lqXxEmRHdb;
      string ezAqQSWwcB;
      string haMIhaSJwY;
      string bsutaxIDtQ;
      string GOiGTxsptA;
      string uRGEmLeOPd;
      string UHLFzkEFPT;
      string JTBLtTqFnj;
      string gbPucJmqGP;
      string RtnQwzCcGi;
      string smaapbQuJS;
      string TYZewsrPbp;
      string yNyABPfkPu;
      string ROzFqtBnEB;
      if(qJRfaZmebY == GOiGTxsptA){sqgmusTITD = true;}
      else if(GOiGTxsptA == qJRfaZmebY){FmNrLcEwyg = true;}
      if(mlWVRIAREF == uRGEmLeOPd){GlAQjfnaZa = true;}
      else if(uRGEmLeOPd == mlWVRIAREF){yrtQybAsVt = true;}
      if(zXuhZEmuHe == UHLFzkEFPT){uffNBFZTmC = true;}
      else if(UHLFzkEFPT == zXuhZEmuHe){MrFkimEIeh = true;}
      if(UzUOqpdAQN == JTBLtTqFnj){qELawGfKEH = true;}
      else if(JTBLtTqFnj == UzUOqpdAQN){WPSlQEdGPS = true;}
      if(ogAzEYVMiy == gbPucJmqGP){wWQMofNhVL = true;}
      else if(gbPucJmqGP == ogAzEYVMiy){MtimkCSHOL = true;}
      if(wtgKSSOjFV == RtnQwzCcGi){GaOdFNLSlp = true;}
      else if(RtnQwzCcGi == wtgKSSOjFV){wIcGaMhbJY = true;}
      if(lqXxEmRHdb == smaapbQuJS){TzURLCaZUd = true;}
      else if(smaapbQuJS == lqXxEmRHdb){YuQQKhZHAt = true;}
      if(ezAqQSWwcB == TYZewsrPbp){zcVSeYOSYV = true;}
      if(haMIhaSJwY == yNyABPfkPu){qrybuQphUi = true;}
      if(bsutaxIDtQ == ROzFqtBnEB){tMYNmwByAm = true;}
      while(TYZewsrPbp == ezAqQSWwcB){xtcDgRJRAf = true;}
      while(yNyABPfkPu == yNyABPfkPu){UwsSlNmMLE = true;}
      while(ROzFqtBnEB == ROzFqtBnEB){VCxqsRcScC = true;}
      if(sqgmusTITD == true){sqgmusTITD = false;}
      if(GlAQjfnaZa == true){GlAQjfnaZa = false;}
      if(uffNBFZTmC == true){uffNBFZTmC = false;}
      if(qELawGfKEH == true){qELawGfKEH = false;}
      if(wWQMofNhVL == true){wWQMofNhVL = false;}
      if(GaOdFNLSlp == true){GaOdFNLSlp = false;}
      if(TzURLCaZUd == true){TzURLCaZUd = false;}
      if(zcVSeYOSYV == true){zcVSeYOSYV = false;}
      if(qrybuQphUi == true){qrybuQphUi = false;}
      if(tMYNmwByAm == true){tMYNmwByAm = false;}
      if(FmNrLcEwyg == true){FmNrLcEwyg = false;}
      if(yrtQybAsVt == true){yrtQybAsVt = false;}
      if(MrFkimEIeh == true){MrFkimEIeh = false;}
      if(WPSlQEdGPS == true){WPSlQEdGPS = false;}
      if(MtimkCSHOL == true){MtimkCSHOL = false;}
      if(wIcGaMhbJY == true){wIcGaMhbJY = false;}
      if(YuQQKhZHAt == true){YuQQKhZHAt = false;}
      if(xtcDgRJRAf == true){xtcDgRJRAf = false;}
      if(UwsSlNmMLE == true){UwsSlNmMLE = false;}
      if(VCxqsRcScC == true){VCxqsRcScC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TEKMJDGIFH
{ 
  void HkQdWtFkIw()
  { 
      bool FFixJsClFQ = false;
      bool DKapXisNOQ = false;
      bool yZXGlOLQjz = false;
      bool eewDfInjma = false;
      bool xgcuKaxbyD = false;
      bool zkMwfegcLu = false;
      bool glBGlYNWKP = false;
      bool tIamSRxcwK = false;
      bool QjRgztRAXA = false;
      bool aLYrtLeWJk = false;
      bool MaRiIqJYdN = false;
      bool hDfAdwTUGq = false;
      bool HNzJnhjisG = false;
      bool maTKxpRiXI = false;
      bool krWJSWeXNx = false;
      bool rJPRdzaIuZ = false;
      bool GafWZHjVCn = false;
      bool ekwyGOqpqQ = false;
      bool DMUuNdKBfy = false;
      bool OJnyBJMziL = false;
      string NjOcrRrPhh;
      string eCmGkIWwPc;
      string wSFdgxcyYo;
      string abzOkhUutF;
      string oYRPlehIdc;
      string LeOOdudkut;
      string ospsHCDYUC;
      string mbCJnXBoqB;
      string PUUwcwNkjp;
      string DizzQwiYIj;
      string bImaojcEaG;
      string tostdTYsPK;
      string nRnezEcCsq;
      string obfHYGgtHs;
      string SJKdwNpEUw;
      string XoIxuKUIak;
      string GZKiQRIkUX;
      string melWrdGJhk;
      string NXgwTASiMO;
      string lXSVlrzbMe;
      if(NjOcrRrPhh == bImaojcEaG){FFixJsClFQ = true;}
      else if(bImaojcEaG == NjOcrRrPhh){MaRiIqJYdN = true;}
      if(eCmGkIWwPc == tostdTYsPK){DKapXisNOQ = true;}
      else if(tostdTYsPK == eCmGkIWwPc){hDfAdwTUGq = true;}
      if(wSFdgxcyYo == nRnezEcCsq){yZXGlOLQjz = true;}
      else if(nRnezEcCsq == wSFdgxcyYo){HNzJnhjisG = true;}
      if(abzOkhUutF == obfHYGgtHs){eewDfInjma = true;}
      else if(obfHYGgtHs == abzOkhUutF){maTKxpRiXI = true;}
      if(oYRPlehIdc == SJKdwNpEUw){xgcuKaxbyD = true;}
      else if(SJKdwNpEUw == oYRPlehIdc){krWJSWeXNx = true;}
      if(LeOOdudkut == XoIxuKUIak){zkMwfegcLu = true;}
      else if(XoIxuKUIak == LeOOdudkut){rJPRdzaIuZ = true;}
      if(ospsHCDYUC == GZKiQRIkUX){glBGlYNWKP = true;}
      else if(GZKiQRIkUX == ospsHCDYUC){GafWZHjVCn = true;}
      if(mbCJnXBoqB == melWrdGJhk){tIamSRxcwK = true;}
      if(PUUwcwNkjp == NXgwTASiMO){QjRgztRAXA = true;}
      if(DizzQwiYIj == lXSVlrzbMe){aLYrtLeWJk = true;}
      while(melWrdGJhk == mbCJnXBoqB){ekwyGOqpqQ = true;}
      while(NXgwTASiMO == NXgwTASiMO){DMUuNdKBfy = true;}
      while(lXSVlrzbMe == lXSVlrzbMe){OJnyBJMziL = true;}
      if(FFixJsClFQ == true){FFixJsClFQ = false;}
      if(DKapXisNOQ == true){DKapXisNOQ = false;}
      if(yZXGlOLQjz == true){yZXGlOLQjz = false;}
      if(eewDfInjma == true){eewDfInjma = false;}
      if(xgcuKaxbyD == true){xgcuKaxbyD = false;}
      if(zkMwfegcLu == true){zkMwfegcLu = false;}
      if(glBGlYNWKP == true){glBGlYNWKP = false;}
      if(tIamSRxcwK == true){tIamSRxcwK = false;}
      if(QjRgztRAXA == true){QjRgztRAXA = false;}
      if(aLYrtLeWJk == true){aLYrtLeWJk = false;}
      if(MaRiIqJYdN == true){MaRiIqJYdN = false;}
      if(hDfAdwTUGq == true){hDfAdwTUGq = false;}
      if(HNzJnhjisG == true){HNzJnhjisG = false;}
      if(maTKxpRiXI == true){maTKxpRiXI = false;}
      if(krWJSWeXNx == true){krWJSWeXNx = false;}
      if(rJPRdzaIuZ == true){rJPRdzaIuZ = false;}
      if(GafWZHjVCn == true){GafWZHjVCn = false;}
      if(ekwyGOqpqQ == true){ekwyGOqpqQ = false;}
      if(DMUuNdKBfy == true){DMUuNdKBfy = false;}
      if(OJnyBJMziL == true){OJnyBJMziL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBUQYKLMOW
{ 
  void AfhSlVuDxd()
  { 
      bool SmSowXjLZC = false;
      bool XkDpVtjIQM = false;
      bool fjrAxiZgRx = false;
      bool ojBdJXygFN = false;
      bool BfloUXCgQT = false;
      bool fLSVJhtSqN = false;
      bool xDscMmjYfx = false;
      bool uDDCKzxDeY = false;
      bool grQyQcReUa = false;
      bool dfoqQymJbh = false;
      bool ncASXcIPKK = false;
      bool jqmSgEmuMj = false;
      bool VEDESPOLlM = false;
      bool LnaxkDqxZn = false;
      bool UBUKpmsWKL = false;
      bool LqxrLjYwzI = false;
      bool NxdyywPpgd = false;
      bool NoUYPTjsNf = false;
      bool WrBaBTphkA = false;
      bool duxQZXXVMt = false;
      string AINfxgsKqD;
      string iKhPntMhpA;
      string nHjWYujJqU;
      string URMqOkBuiA;
      string oJWJSscEMI;
      string FXnTTsXqHC;
      string xiTWiRypBD;
      string sQzpLekaDe;
      string RfxhOwcsXU;
      string MKngCFozZA;
      string umDIPnYyHo;
      string IxmbkRklHl;
      string oERfqhcRmF;
      string pkADidcoSa;
      string XekhMOWLwk;
      string TDrnLqUWRg;
      string LGKCzXwjsG;
      string nwSgNJSjTb;
      string LQVBklrMqr;
      string IFWlOQUiio;
      if(AINfxgsKqD == umDIPnYyHo){SmSowXjLZC = true;}
      else if(umDIPnYyHo == AINfxgsKqD){ncASXcIPKK = true;}
      if(iKhPntMhpA == IxmbkRklHl){XkDpVtjIQM = true;}
      else if(IxmbkRklHl == iKhPntMhpA){jqmSgEmuMj = true;}
      if(nHjWYujJqU == oERfqhcRmF){fjrAxiZgRx = true;}
      else if(oERfqhcRmF == nHjWYujJqU){VEDESPOLlM = true;}
      if(URMqOkBuiA == pkADidcoSa){ojBdJXygFN = true;}
      else if(pkADidcoSa == URMqOkBuiA){LnaxkDqxZn = true;}
      if(oJWJSscEMI == XekhMOWLwk){BfloUXCgQT = true;}
      else if(XekhMOWLwk == oJWJSscEMI){UBUKpmsWKL = true;}
      if(FXnTTsXqHC == TDrnLqUWRg){fLSVJhtSqN = true;}
      else if(TDrnLqUWRg == FXnTTsXqHC){LqxrLjYwzI = true;}
      if(xiTWiRypBD == LGKCzXwjsG){xDscMmjYfx = true;}
      else if(LGKCzXwjsG == xiTWiRypBD){NxdyywPpgd = true;}
      if(sQzpLekaDe == nwSgNJSjTb){uDDCKzxDeY = true;}
      if(RfxhOwcsXU == LQVBklrMqr){grQyQcReUa = true;}
      if(MKngCFozZA == IFWlOQUiio){dfoqQymJbh = true;}
      while(nwSgNJSjTb == sQzpLekaDe){NoUYPTjsNf = true;}
      while(LQVBklrMqr == LQVBklrMqr){WrBaBTphkA = true;}
      while(IFWlOQUiio == IFWlOQUiio){duxQZXXVMt = true;}
      if(SmSowXjLZC == true){SmSowXjLZC = false;}
      if(XkDpVtjIQM == true){XkDpVtjIQM = false;}
      if(fjrAxiZgRx == true){fjrAxiZgRx = false;}
      if(ojBdJXygFN == true){ojBdJXygFN = false;}
      if(BfloUXCgQT == true){BfloUXCgQT = false;}
      if(fLSVJhtSqN == true){fLSVJhtSqN = false;}
      if(xDscMmjYfx == true){xDscMmjYfx = false;}
      if(uDDCKzxDeY == true){uDDCKzxDeY = false;}
      if(grQyQcReUa == true){grQyQcReUa = false;}
      if(dfoqQymJbh == true){dfoqQymJbh = false;}
      if(ncASXcIPKK == true){ncASXcIPKK = false;}
      if(jqmSgEmuMj == true){jqmSgEmuMj = false;}
      if(VEDESPOLlM == true){VEDESPOLlM = false;}
      if(LnaxkDqxZn == true){LnaxkDqxZn = false;}
      if(UBUKpmsWKL == true){UBUKpmsWKL = false;}
      if(LqxrLjYwzI == true){LqxrLjYwzI = false;}
      if(NxdyywPpgd == true){NxdyywPpgd = false;}
      if(NoUYPTjsNf == true){NoUYPTjsNf = false;}
      if(WrBaBTphkA == true){WrBaBTphkA = false;}
      if(duxQZXXVMt == true){duxQZXXVMt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QYJHQGOCKV
{ 
  void GStlMBmdOU()
  { 
      bool JcBheIVYmo = false;
      bool UcyaArcKtN = false;
      bool smPZKqHzRh = false;
      bool ErHtLyEJDV = false;
      bool ERODhGASgc = false;
      bool QLDqiWMaWm = false;
      bool AVGEkcVDPB = false;
      bool nTHYIbYMrE = false;
      bool pnRoRroPLo = false;
      bool lclPUiLJRF = false;
      bool jxDeowEdiG = false;
      bool yziSxLDQlr = false;
      bool mFqZPKgrEY = false;
      bool POulTsklzU = false;
      bool nLgEqlsTSI = false;
      bool etXZReFcPd = false;
      bool PMZJpiExzD = false;
      bool aQQREbYlic = false;
      bool QNYutVqUTn = false;
      bool mHWVFbkXNH = false;
      string UCbrFBsBKx;
      string CnPxAMNnzz;
      string LIYmKWQrJw;
      string CuqBMetEbP;
      string FljBRVGqkI;
      string rAgHqMcogh;
      string jAqNtHxOkV;
      string SIMisYYXUn;
      string QZGAECOjKA;
      string CFXseEtVGK;
      string YrFPpjmxNR;
      string mETrRKtqIq;
      string sMDjSNkSDo;
      string dDQKPXTqJU;
      string OQWrMxlebU;
      string KDMPRLnVwb;
      string yUsYnjnIct;
      string pCgncbpLXU;
      string bFqhdapBrD;
      string iythVtWxEc;
      if(UCbrFBsBKx == YrFPpjmxNR){JcBheIVYmo = true;}
      else if(YrFPpjmxNR == UCbrFBsBKx){jxDeowEdiG = true;}
      if(CnPxAMNnzz == mETrRKtqIq){UcyaArcKtN = true;}
      else if(mETrRKtqIq == CnPxAMNnzz){yziSxLDQlr = true;}
      if(LIYmKWQrJw == sMDjSNkSDo){smPZKqHzRh = true;}
      else if(sMDjSNkSDo == LIYmKWQrJw){mFqZPKgrEY = true;}
      if(CuqBMetEbP == dDQKPXTqJU){ErHtLyEJDV = true;}
      else if(dDQKPXTqJU == CuqBMetEbP){POulTsklzU = true;}
      if(FljBRVGqkI == OQWrMxlebU){ERODhGASgc = true;}
      else if(OQWrMxlebU == FljBRVGqkI){nLgEqlsTSI = true;}
      if(rAgHqMcogh == KDMPRLnVwb){QLDqiWMaWm = true;}
      else if(KDMPRLnVwb == rAgHqMcogh){etXZReFcPd = true;}
      if(jAqNtHxOkV == yUsYnjnIct){AVGEkcVDPB = true;}
      else if(yUsYnjnIct == jAqNtHxOkV){PMZJpiExzD = true;}
      if(SIMisYYXUn == pCgncbpLXU){nTHYIbYMrE = true;}
      if(QZGAECOjKA == bFqhdapBrD){pnRoRroPLo = true;}
      if(CFXseEtVGK == iythVtWxEc){lclPUiLJRF = true;}
      while(pCgncbpLXU == SIMisYYXUn){aQQREbYlic = true;}
      while(bFqhdapBrD == bFqhdapBrD){QNYutVqUTn = true;}
      while(iythVtWxEc == iythVtWxEc){mHWVFbkXNH = true;}
      if(JcBheIVYmo == true){JcBheIVYmo = false;}
      if(UcyaArcKtN == true){UcyaArcKtN = false;}
      if(smPZKqHzRh == true){smPZKqHzRh = false;}
      if(ErHtLyEJDV == true){ErHtLyEJDV = false;}
      if(ERODhGASgc == true){ERODhGASgc = false;}
      if(QLDqiWMaWm == true){QLDqiWMaWm = false;}
      if(AVGEkcVDPB == true){AVGEkcVDPB = false;}
      if(nTHYIbYMrE == true){nTHYIbYMrE = false;}
      if(pnRoRroPLo == true){pnRoRroPLo = false;}
      if(lclPUiLJRF == true){lclPUiLJRF = false;}
      if(jxDeowEdiG == true){jxDeowEdiG = false;}
      if(yziSxLDQlr == true){yziSxLDQlr = false;}
      if(mFqZPKgrEY == true){mFqZPKgrEY = false;}
      if(POulTsklzU == true){POulTsklzU = false;}
      if(nLgEqlsTSI == true){nLgEqlsTSI = false;}
      if(etXZReFcPd == true){etXZReFcPd = false;}
      if(PMZJpiExzD == true){PMZJpiExzD = false;}
      if(aQQREbYlic == true){aQQREbYlic = false;}
      if(QNYutVqUTn == true){QNYutVqUTn = false;}
      if(mHWVFbkXNH == true){mHWVFbkXNH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SFQEJGCGYH
{ 
  void kSqKQoqUtX()
  { 
      bool fxSUlJozNa = false;
      bool VdVUITpIgQ = false;
      bool VFXSLExygW = false;
      bool GQdpypIYZm = false;
      bool WUUeCZcYzE = false;
      bool RSQeKZYzIh = false;
      bool MqRpUFzfVS = false;
      bool KRhttBkrQl = false;
      bool aXybFmzyfY = false;
      bool QJPrZeCdKx = false;
      bool axCfsAkVkJ = false;
      bool oghWGnrpkg = false;
      bool FBAxCBBoTO = false;
      bool yHhTLdVShE = false;
      bool CcMWiiarll = false;
      bool mMscrYwFdr = false;
      bool yuCWKhzOLc = false;
      bool SZHfebndNS = false;
      bool aIDhblOFbl = false;
      bool gPnpGHapLB = false;
      string WqiuyNBeEl;
      string gOIZXyrdDC;
      string pHjmJQnXGd;
      string IhSCypPwpM;
      string QdEskYHLfr;
      string cCNNuPGukg;
      string ZdXacywFah;
      string hwnpkMCqCk;
      string JcrNAGTEHi;
      string iUKImmFdPm;
      string bBjyJgOXbi;
      string NPsAXwkKZW;
      string dqyqyNkeCy;
      string GXaPIHrtET;
      string qwbXVTaJkp;
      string BuEsIkDrzw;
      string ujUdbondqP;
      string EqGFegOZVe;
      string masMwLThGX;
      string DztIYHaywf;
      if(WqiuyNBeEl == bBjyJgOXbi){fxSUlJozNa = true;}
      else if(bBjyJgOXbi == WqiuyNBeEl){axCfsAkVkJ = true;}
      if(gOIZXyrdDC == NPsAXwkKZW){VdVUITpIgQ = true;}
      else if(NPsAXwkKZW == gOIZXyrdDC){oghWGnrpkg = true;}
      if(pHjmJQnXGd == dqyqyNkeCy){VFXSLExygW = true;}
      else if(dqyqyNkeCy == pHjmJQnXGd){FBAxCBBoTO = true;}
      if(IhSCypPwpM == GXaPIHrtET){GQdpypIYZm = true;}
      else if(GXaPIHrtET == IhSCypPwpM){yHhTLdVShE = true;}
      if(QdEskYHLfr == qwbXVTaJkp){WUUeCZcYzE = true;}
      else if(qwbXVTaJkp == QdEskYHLfr){CcMWiiarll = true;}
      if(cCNNuPGukg == BuEsIkDrzw){RSQeKZYzIh = true;}
      else if(BuEsIkDrzw == cCNNuPGukg){mMscrYwFdr = true;}
      if(ZdXacywFah == ujUdbondqP){MqRpUFzfVS = true;}
      else if(ujUdbondqP == ZdXacywFah){yuCWKhzOLc = true;}
      if(hwnpkMCqCk == EqGFegOZVe){KRhttBkrQl = true;}
      if(JcrNAGTEHi == masMwLThGX){aXybFmzyfY = true;}
      if(iUKImmFdPm == DztIYHaywf){QJPrZeCdKx = true;}
      while(EqGFegOZVe == hwnpkMCqCk){SZHfebndNS = true;}
      while(masMwLThGX == masMwLThGX){aIDhblOFbl = true;}
      while(DztIYHaywf == DztIYHaywf){gPnpGHapLB = true;}
      if(fxSUlJozNa == true){fxSUlJozNa = false;}
      if(VdVUITpIgQ == true){VdVUITpIgQ = false;}
      if(VFXSLExygW == true){VFXSLExygW = false;}
      if(GQdpypIYZm == true){GQdpypIYZm = false;}
      if(WUUeCZcYzE == true){WUUeCZcYzE = false;}
      if(RSQeKZYzIh == true){RSQeKZYzIh = false;}
      if(MqRpUFzfVS == true){MqRpUFzfVS = false;}
      if(KRhttBkrQl == true){KRhttBkrQl = false;}
      if(aXybFmzyfY == true){aXybFmzyfY = false;}
      if(QJPrZeCdKx == true){QJPrZeCdKx = false;}
      if(axCfsAkVkJ == true){axCfsAkVkJ = false;}
      if(oghWGnrpkg == true){oghWGnrpkg = false;}
      if(FBAxCBBoTO == true){FBAxCBBoTO = false;}
      if(yHhTLdVShE == true){yHhTLdVShE = false;}
      if(CcMWiiarll == true){CcMWiiarll = false;}
      if(mMscrYwFdr == true){mMscrYwFdr = false;}
      if(yuCWKhzOLc == true){yuCWKhzOLc = false;}
      if(SZHfebndNS == true){SZHfebndNS = false;}
      if(aIDhblOFbl == true){aIDhblOFbl = false;}
      if(gPnpGHapLB == true){gPnpGHapLB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXTPAZXITH
{ 
  void MUumQoEmIW()
  { 
      bool dinUqnOVJE = false;
      bool eBwuZhNDlq = false;
      bool udEhrbCxVw = false;
      bool SsPBgIecaR = false;
      bool BwGBNsGTbr = false;
      bool TxJbBAeFbP = false;
      bool kRzNklluNQ = false;
      bool DjbUpyWCUz = false;
      bool UhUdcVinAg = false;
      bool dYBLfiwsQb = false;
      bool HLFLniUokC = false;
      bool cbkctDxVkO = false;
      bool DytgmeiQoH = false;
      bool CclrqIbJps = false;
      bool AsCxDBmXQc = false;
      bool laIBYIRYXJ = false;
      bool zEzdzAprkl = false;
      bool ameqOJwwdk = false;
      bool rKAMUbUjTh = false;
      bool qDkgsusXyD = false;
      string aNRosuFnVp;
      string NYlsqnxKYs;
      string jCBilwQHxk;
      string KmAMejSIag;
      string oXanoXUPxZ;
      string YBEHyYMiDx;
      string expjeZXYNH;
      string VnjrDLaMsN;
      string bAKXMJisNG;
      string XiFdBrgpIO;
      string AuCoEjRMDm;
      string xzooUdlSXV;
      string qeKHjliGpL;
      string ejEdNfyUTb;
      string rWoaJYtPIW;
      string FOSmXUktFR;
      string BKVrHMtKan;
      string fRzwcTpiyK;
      string rSxSFQRQGs;
      string uDOBZgAwTw;
      if(aNRosuFnVp == AuCoEjRMDm){dinUqnOVJE = true;}
      else if(AuCoEjRMDm == aNRosuFnVp){HLFLniUokC = true;}
      if(NYlsqnxKYs == xzooUdlSXV){eBwuZhNDlq = true;}
      else if(xzooUdlSXV == NYlsqnxKYs){cbkctDxVkO = true;}
      if(jCBilwQHxk == qeKHjliGpL){udEhrbCxVw = true;}
      else if(qeKHjliGpL == jCBilwQHxk){DytgmeiQoH = true;}
      if(KmAMejSIag == ejEdNfyUTb){SsPBgIecaR = true;}
      else if(ejEdNfyUTb == KmAMejSIag){CclrqIbJps = true;}
      if(oXanoXUPxZ == rWoaJYtPIW){BwGBNsGTbr = true;}
      else if(rWoaJYtPIW == oXanoXUPxZ){AsCxDBmXQc = true;}
      if(YBEHyYMiDx == FOSmXUktFR){TxJbBAeFbP = true;}
      else if(FOSmXUktFR == YBEHyYMiDx){laIBYIRYXJ = true;}
      if(expjeZXYNH == BKVrHMtKan){kRzNklluNQ = true;}
      else if(BKVrHMtKan == expjeZXYNH){zEzdzAprkl = true;}
      if(VnjrDLaMsN == fRzwcTpiyK){DjbUpyWCUz = true;}
      if(bAKXMJisNG == rSxSFQRQGs){UhUdcVinAg = true;}
      if(XiFdBrgpIO == uDOBZgAwTw){dYBLfiwsQb = true;}
      while(fRzwcTpiyK == VnjrDLaMsN){ameqOJwwdk = true;}
      while(rSxSFQRQGs == rSxSFQRQGs){rKAMUbUjTh = true;}
      while(uDOBZgAwTw == uDOBZgAwTw){qDkgsusXyD = true;}
      if(dinUqnOVJE == true){dinUqnOVJE = false;}
      if(eBwuZhNDlq == true){eBwuZhNDlq = false;}
      if(udEhrbCxVw == true){udEhrbCxVw = false;}
      if(SsPBgIecaR == true){SsPBgIecaR = false;}
      if(BwGBNsGTbr == true){BwGBNsGTbr = false;}
      if(TxJbBAeFbP == true){TxJbBAeFbP = false;}
      if(kRzNklluNQ == true){kRzNklluNQ = false;}
      if(DjbUpyWCUz == true){DjbUpyWCUz = false;}
      if(UhUdcVinAg == true){UhUdcVinAg = false;}
      if(dYBLfiwsQb == true){dYBLfiwsQb = false;}
      if(HLFLniUokC == true){HLFLniUokC = false;}
      if(cbkctDxVkO == true){cbkctDxVkO = false;}
      if(DytgmeiQoH == true){DytgmeiQoH = false;}
      if(CclrqIbJps == true){CclrqIbJps = false;}
      if(AsCxDBmXQc == true){AsCxDBmXQc = false;}
      if(laIBYIRYXJ == true){laIBYIRYXJ = false;}
      if(zEzdzAprkl == true){zEzdzAprkl = false;}
      if(ameqOJwwdk == true){ameqOJwwdk = false;}
      if(rKAMUbUjTh == true){rKAMUbUjTh = false;}
      if(qDkgsusXyD == true){qDkgsusXyD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class URQCDYVGFM
{ 
  void FyATAqoMEm()
  { 
      bool XhwzaWnzeS = false;
      bool fscpnxiIsT = false;
      bool kTWAmksjNS = false;
      bool wDdIjNMcPM = false;
      bool GPEVqKqNsx = false;
      bool ptGCgEKwMp = false;
      bool dElMWcPUFZ = false;
      bool jFsgNUPBIc = false;
      bool sepQbCwaaf = false;
      bool DPQZiBdqyO = false;
      bool uWISMkAZoL = false;
      bool oImiwyNVkU = false;
      bool fnsZWUnTyL = false;
      bool pXCthWVXDp = false;
      bool BWlOptchcj = false;
      bool mIGdhGciwr = false;
      bool xfacVQFsBY = false;
      bool bpRtSJBdib = false;
      bool qGpOXhRYMa = false;
      bool tmaLsUuIsZ = false;
      string KWXqtzdxto;
      string FEolaQlkqc;
      string GyEZjiAqVz;
      string tdNFCEMHnJ;
      string FQKwwJLfFe;
      string OcEDFLSxGK;
      string ylatuaqiiV;
      string EdxhWpnIca;
      string XUlqkRYJzp;
      string lOAcKToQBU;
      string RbwiZjfWfP;
      string XKTfmdziId;
      string ChisjpdTWD;
      string BWGHIwXCRA;
      string kCdjSbtUpg;
      string TGHXSjrDyj;
      string GLzcOADMXq;
      string FxRHrzEzZI;
      string uJcpitPioX;
      string DUDgtYDAVR;
      if(KWXqtzdxto == RbwiZjfWfP){XhwzaWnzeS = true;}
      else if(RbwiZjfWfP == KWXqtzdxto){uWISMkAZoL = true;}
      if(FEolaQlkqc == XKTfmdziId){fscpnxiIsT = true;}
      else if(XKTfmdziId == FEolaQlkqc){oImiwyNVkU = true;}
      if(GyEZjiAqVz == ChisjpdTWD){kTWAmksjNS = true;}
      else if(ChisjpdTWD == GyEZjiAqVz){fnsZWUnTyL = true;}
      if(tdNFCEMHnJ == BWGHIwXCRA){wDdIjNMcPM = true;}
      else if(BWGHIwXCRA == tdNFCEMHnJ){pXCthWVXDp = true;}
      if(FQKwwJLfFe == kCdjSbtUpg){GPEVqKqNsx = true;}
      else if(kCdjSbtUpg == FQKwwJLfFe){BWlOptchcj = true;}
      if(OcEDFLSxGK == TGHXSjrDyj){ptGCgEKwMp = true;}
      else if(TGHXSjrDyj == OcEDFLSxGK){mIGdhGciwr = true;}
      if(ylatuaqiiV == GLzcOADMXq){dElMWcPUFZ = true;}
      else if(GLzcOADMXq == ylatuaqiiV){xfacVQFsBY = true;}
      if(EdxhWpnIca == FxRHrzEzZI){jFsgNUPBIc = true;}
      if(XUlqkRYJzp == uJcpitPioX){sepQbCwaaf = true;}
      if(lOAcKToQBU == DUDgtYDAVR){DPQZiBdqyO = true;}
      while(FxRHrzEzZI == EdxhWpnIca){bpRtSJBdib = true;}
      while(uJcpitPioX == uJcpitPioX){qGpOXhRYMa = true;}
      while(DUDgtYDAVR == DUDgtYDAVR){tmaLsUuIsZ = true;}
      if(XhwzaWnzeS == true){XhwzaWnzeS = false;}
      if(fscpnxiIsT == true){fscpnxiIsT = false;}
      if(kTWAmksjNS == true){kTWAmksjNS = false;}
      if(wDdIjNMcPM == true){wDdIjNMcPM = false;}
      if(GPEVqKqNsx == true){GPEVqKqNsx = false;}
      if(ptGCgEKwMp == true){ptGCgEKwMp = false;}
      if(dElMWcPUFZ == true){dElMWcPUFZ = false;}
      if(jFsgNUPBIc == true){jFsgNUPBIc = false;}
      if(sepQbCwaaf == true){sepQbCwaaf = false;}
      if(DPQZiBdqyO == true){DPQZiBdqyO = false;}
      if(uWISMkAZoL == true){uWISMkAZoL = false;}
      if(oImiwyNVkU == true){oImiwyNVkU = false;}
      if(fnsZWUnTyL == true){fnsZWUnTyL = false;}
      if(pXCthWVXDp == true){pXCthWVXDp = false;}
      if(BWlOptchcj == true){BWlOptchcj = false;}
      if(mIGdhGciwr == true){mIGdhGciwr = false;}
      if(xfacVQFsBY == true){xfacVQFsBY = false;}
      if(bpRtSJBdib == true){bpRtSJBdib = false;}
      if(qGpOXhRYMa == true){qGpOXhRYMa = false;}
      if(tmaLsUuIsZ == true){tmaLsUuIsZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DBXEPAUHMH
{ 
  void xcZmgwywQw()
  { 
      bool kSyiSWFyez = false;
      bool QxRCkOXpru = false;
      bool MnZQJaNmRN = false;
      bool lfjcNycTbN = false;
      bool LnHmDYPIoX = false;
      bool KNZGgwrgYq = false;
      bool JRgQMkNnom = false;
      bool lDNdiXglNk = false;
      bool LEysDYFduR = false;
      bool FuukEsHpaR = false;
      bool KaTBlGzwWJ = false;
      bool PFTmfETmMm = false;
      bool fjrXgpIcZo = false;
      bool QpLuZjkwHx = false;
      bool ZJGlBAbHEz = false;
      bool ZTdmlaiwTu = false;
      bool xWWgrYsXMu = false;
      bool TXfONWcFVg = false;
      bool OAXZPwMYJz = false;
      bool BnbLzClZtb = false;
      string AVeUHMEJFZ;
      string JqOQnddqDN;
      string RdmqHiyrsr;
      string PjmCJgJPYX;
      string uYArtNuQSR;
      string NLmdpVhmMY;
      string OLQNKZDLGH;
      string TNRfRsduxs;
      string ngYadDwILm;
      string yWCAIiIlhT;
      string JiJLyAsHMx;
      string rmpTkgmoiG;
      string duzTJwKRWh;
      string jqMciEXNbd;
      string JnwOuKfiOb;
      string wSDaoOipBB;
      string pakdMAZNkf;
      string IYNFwpykXy;
      string QaDukRmlmT;
      string VhLZmhDSBt;
      if(AVeUHMEJFZ == JiJLyAsHMx){kSyiSWFyez = true;}
      else if(JiJLyAsHMx == AVeUHMEJFZ){KaTBlGzwWJ = true;}
      if(JqOQnddqDN == rmpTkgmoiG){QxRCkOXpru = true;}
      else if(rmpTkgmoiG == JqOQnddqDN){PFTmfETmMm = true;}
      if(RdmqHiyrsr == duzTJwKRWh){MnZQJaNmRN = true;}
      else if(duzTJwKRWh == RdmqHiyrsr){fjrXgpIcZo = true;}
      if(PjmCJgJPYX == jqMciEXNbd){lfjcNycTbN = true;}
      else if(jqMciEXNbd == PjmCJgJPYX){QpLuZjkwHx = true;}
      if(uYArtNuQSR == JnwOuKfiOb){LnHmDYPIoX = true;}
      else if(JnwOuKfiOb == uYArtNuQSR){ZJGlBAbHEz = true;}
      if(NLmdpVhmMY == wSDaoOipBB){KNZGgwrgYq = true;}
      else if(wSDaoOipBB == NLmdpVhmMY){ZTdmlaiwTu = true;}
      if(OLQNKZDLGH == pakdMAZNkf){JRgQMkNnom = true;}
      else if(pakdMAZNkf == OLQNKZDLGH){xWWgrYsXMu = true;}
      if(TNRfRsduxs == IYNFwpykXy){lDNdiXglNk = true;}
      if(ngYadDwILm == QaDukRmlmT){LEysDYFduR = true;}
      if(yWCAIiIlhT == VhLZmhDSBt){FuukEsHpaR = true;}
      while(IYNFwpykXy == TNRfRsduxs){TXfONWcFVg = true;}
      while(QaDukRmlmT == QaDukRmlmT){OAXZPwMYJz = true;}
      while(VhLZmhDSBt == VhLZmhDSBt){BnbLzClZtb = true;}
      if(kSyiSWFyez == true){kSyiSWFyez = false;}
      if(QxRCkOXpru == true){QxRCkOXpru = false;}
      if(MnZQJaNmRN == true){MnZQJaNmRN = false;}
      if(lfjcNycTbN == true){lfjcNycTbN = false;}
      if(LnHmDYPIoX == true){LnHmDYPIoX = false;}
      if(KNZGgwrgYq == true){KNZGgwrgYq = false;}
      if(JRgQMkNnom == true){JRgQMkNnom = false;}
      if(lDNdiXglNk == true){lDNdiXglNk = false;}
      if(LEysDYFduR == true){LEysDYFduR = false;}
      if(FuukEsHpaR == true){FuukEsHpaR = false;}
      if(KaTBlGzwWJ == true){KaTBlGzwWJ = false;}
      if(PFTmfETmMm == true){PFTmfETmMm = false;}
      if(fjrXgpIcZo == true){fjrXgpIcZo = false;}
      if(QpLuZjkwHx == true){QpLuZjkwHx = false;}
      if(ZJGlBAbHEz == true){ZJGlBAbHEz = false;}
      if(ZTdmlaiwTu == true){ZTdmlaiwTu = false;}
      if(xWWgrYsXMu == true){xWWgrYsXMu = false;}
      if(TXfONWcFVg == true){TXfONWcFVg = false;}
      if(OAXZPwMYJz == true){OAXZPwMYJz = false;}
      if(BnbLzClZtb == true){BnbLzClZtb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JNNAANXSVA
{ 
  void yBGQoQTkBi()
  { 
      bool BpRMawCZKc = false;
      bool PWQDxryndP = false;
      bool TnPsYbfqgs = false;
      bool QiQmxeEirC = false;
      bool lVPkqrZNEg = false;
      bool fZGnmNZYnz = false;
      bool QLsRMfFdGS = false;
      bool mPubdyXeBf = false;
      bool BSlzMpbcAi = false;
      bool EfurkZcyXL = false;
      bool lwGltQeeJo = false;
      bool ouXHyyZsEV = false;
      bool DccWOGTCpE = false;
      bool UZGotELAFu = false;
      bool LxSLtIIntm = false;
      bool AjsCHISiWm = false;
      bool xbnFTOnhMs = false;
      bool lYnIKGKRcF = false;
      bool yfHCEkgEhk = false;
      bool kbcRyiINqe = false;
      string GBCALwTckN;
      string naLnLxOTCV;
      string rNkbxiqNny;
      string AuIhHGqNZV;
      string RyMtAlCKYM;
      string FjDYirPZDc;
      string EGomNrSdgF;
      string FAsgEtAqbK;
      string ggnasPriyO;
      string pRKxRLJZgH;
      string TXdSGEpWUo;
      string qYyrwWRNtx;
      string AieRPnowOr;
      string jaJUqIDUUn;
      string YVOJWQTSAu;
      string sueiHjsLDR;
      string OtHcEPOcAn;
      string TxsFXdUVtz;
      string UWuTynuaNH;
      string PqRCYeNkEH;
      if(GBCALwTckN == TXdSGEpWUo){BpRMawCZKc = true;}
      else if(TXdSGEpWUo == GBCALwTckN){lwGltQeeJo = true;}
      if(naLnLxOTCV == qYyrwWRNtx){PWQDxryndP = true;}
      else if(qYyrwWRNtx == naLnLxOTCV){ouXHyyZsEV = true;}
      if(rNkbxiqNny == AieRPnowOr){TnPsYbfqgs = true;}
      else if(AieRPnowOr == rNkbxiqNny){DccWOGTCpE = true;}
      if(AuIhHGqNZV == jaJUqIDUUn){QiQmxeEirC = true;}
      else if(jaJUqIDUUn == AuIhHGqNZV){UZGotELAFu = true;}
      if(RyMtAlCKYM == YVOJWQTSAu){lVPkqrZNEg = true;}
      else if(YVOJWQTSAu == RyMtAlCKYM){LxSLtIIntm = true;}
      if(FjDYirPZDc == sueiHjsLDR){fZGnmNZYnz = true;}
      else if(sueiHjsLDR == FjDYirPZDc){AjsCHISiWm = true;}
      if(EGomNrSdgF == OtHcEPOcAn){QLsRMfFdGS = true;}
      else if(OtHcEPOcAn == EGomNrSdgF){xbnFTOnhMs = true;}
      if(FAsgEtAqbK == TxsFXdUVtz){mPubdyXeBf = true;}
      if(ggnasPriyO == UWuTynuaNH){BSlzMpbcAi = true;}
      if(pRKxRLJZgH == PqRCYeNkEH){EfurkZcyXL = true;}
      while(TxsFXdUVtz == FAsgEtAqbK){lYnIKGKRcF = true;}
      while(UWuTynuaNH == UWuTynuaNH){yfHCEkgEhk = true;}
      while(PqRCYeNkEH == PqRCYeNkEH){kbcRyiINqe = true;}
      if(BpRMawCZKc == true){BpRMawCZKc = false;}
      if(PWQDxryndP == true){PWQDxryndP = false;}
      if(TnPsYbfqgs == true){TnPsYbfqgs = false;}
      if(QiQmxeEirC == true){QiQmxeEirC = false;}
      if(lVPkqrZNEg == true){lVPkqrZNEg = false;}
      if(fZGnmNZYnz == true){fZGnmNZYnz = false;}
      if(QLsRMfFdGS == true){QLsRMfFdGS = false;}
      if(mPubdyXeBf == true){mPubdyXeBf = false;}
      if(BSlzMpbcAi == true){BSlzMpbcAi = false;}
      if(EfurkZcyXL == true){EfurkZcyXL = false;}
      if(lwGltQeeJo == true){lwGltQeeJo = false;}
      if(ouXHyyZsEV == true){ouXHyyZsEV = false;}
      if(DccWOGTCpE == true){DccWOGTCpE = false;}
      if(UZGotELAFu == true){UZGotELAFu = false;}
      if(LxSLtIIntm == true){LxSLtIIntm = false;}
      if(AjsCHISiWm == true){AjsCHISiWm = false;}
      if(xbnFTOnhMs == true){xbnFTOnhMs = false;}
      if(lYnIKGKRcF == true){lYnIKGKRcF = false;}
      if(yfHCEkgEhk == true){yfHCEkgEhk = false;}
      if(kbcRyiINqe == true){kbcRyiINqe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TKIHOPSQEV
{ 
  void eFYNOXdphi()
  { 
      bool EtTsiRSDHM = false;
      bool IGxMnNXLVU = false;
      bool QtGUjyFfuV = false;
      bool wIIwKTfspC = false;
      bool JygNfmRaTb = false;
      bool UeIZEKmzJj = false;
      bool MmIlQzxABT = false;
      bool heVTKRNsnw = false;
      bool gdLSARzirz = false;
      bool ggjFpWptxf = false;
      bool oQZAtpJoOl = false;
      bool xtKMDhaoly = false;
      bool AOIBlAtPcn = false;
      bool bSuIHPEKYJ = false;
      bool IKTGClVWBH = false;
      bool uBIyfZHXNs = false;
      bool usLaJdzCFm = false;
      bool dQQbpouCyA = false;
      bool dXOVsaKwbg = false;
      bool IfweNPzrwY = false;
      string VVMjUQPiPo;
      string DZFpNTCIpZ;
      string ylbJBdZLeg;
      string CDUojboEue;
      string YJObQKUaQY;
      string mfSZSjtCip;
      string pEEimAFQGk;
      string dxNKBnXzrp;
      string IyuFsVjuVA;
      string hlVEnUFenQ;
      string FEUetoSHYe;
      string LtJshqIzoR;
      string PJtFDqbIVg;
      string hrLbjEdPKD;
      string CbWqnncbWx;
      string LGoWAuJObC;
      string NJkqwTihId;
      string NsnlOmmDRP;
      string OzlYUbCnan;
      string tOnIpsqetU;
      if(VVMjUQPiPo == FEUetoSHYe){EtTsiRSDHM = true;}
      else if(FEUetoSHYe == VVMjUQPiPo){oQZAtpJoOl = true;}
      if(DZFpNTCIpZ == LtJshqIzoR){IGxMnNXLVU = true;}
      else if(LtJshqIzoR == DZFpNTCIpZ){xtKMDhaoly = true;}
      if(ylbJBdZLeg == PJtFDqbIVg){QtGUjyFfuV = true;}
      else if(PJtFDqbIVg == ylbJBdZLeg){AOIBlAtPcn = true;}
      if(CDUojboEue == hrLbjEdPKD){wIIwKTfspC = true;}
      else if(hrLbjEdPKD == CDUojboEue){bSuIHPEKYJ = true;}
      if(YJObQKUaQY == CbWqnncbWx){JygNfmRaTb = true;}
      else if(CbWqnncbWx == YJObQKUaQY){IKTGClVWBH = true;}
      if(mfSZSjtCip == LGoWAuJObC){UeIZEKmzJj = true;}
      else if(LGoWAuJObC == mfSZSjtCip){uBIyfZHXNs = true;}
      if(pEEimAFQGk == NJkqwTihId){MmIlQzxABT = true;}
      else if(NJkqwTihId == pEEimAFQGk){usLaJdzCFm = true;}
      if(dxNKBnXzrp == NsnlOmmDRP){heVTKRNsnw = true;}
      if(IyuFsVjuVA == OzlYUbCnan){gdLSARzirz = true;}
      if(hlVEnUFenQ == tOnIpsqetU){ggjFpWptxf = true;}
      while(NsnlOmmDRP == dxNKBnXzrp){dQQbpouCyA = true;}
      while(OzlYUbCnan == OzlYUbCnan){dXOVsaKwbg = true;}
      while(tOnIpsqetU == tOnIpsqetU){IfweNPzrwY = true;}
      if(EtTsiRSDHM == true){EtTsiRSDHM = false;}
      if(IGxMnNXLVU == true){IGxMnNXLVU = false;}
      if(QtGUjyFfuV == true){QtGUjyFfuV = false;}
      if(wIIwKTfspC == true){wIIwKTfspC = false;}
      if(JygNfmRaTb == true){JygNfmRaTb = false;}
      if(UeIZEKmzJj == true){UeIZEKmzJj = false;}
      if(MmIlQzxABT == true){MmIlQzxABT = false;}
      if(heVTKRNsnw == true){heVTKRNsnw = false;}
      if(gdLSARzirz == true){gdLSARzirz = false;}
      if(ggjFpWptxf == true){ggjFpWptxf = false;}
      if(oQZAtpJoOl == true){oQZAtpJoOl = false;}
      if(xtKMDhaoly == true){xtKMDhaoly = false;}
      if(AOIBlAtPcn == true){AOIBlAtPcn = false;}
      if(bSuIHPEKYJ == true){bSuIHPEKYJ = false;}
      if(IKTGClVWBH == true){IKTGClVWBH = false;}
      if(uBIyfZHXNs == true){uBIyfZHXNs = false;}
      if(usLaJdzCFm == true){usLaJdzCFm = false;}
      if(dQQbpouCyA == true){dQQbpouCyA = false;}
      if(dXOVsaKwbg == true){dXOVsaKwbg = false;}
      if(IfweNPzrwY == true){IfweNPzrwY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FIJFEUTREC
{ 
  void RNUYFCcfeD()
  { 
      bool nLJqpOWLsU = false;
      bool ixanTtJAYE = false;
      bool RweRfuLnBN = false;
      bool KwwNZMGTQw = false;
      bool xgIAZDsTIa = false;
      bool cHuHdqgqKt = false;
      bool DhKfJlANOH = false;
      bool moicGjmdqc = false;
      bool CqfZjDBojh = false;
      bool ePIWsOVcqn = false;
      bool CeEAmnXRAt = false;
      bool DDAhqLCjuG = false;
      bool jLdgbXfMjq = false;
      bool NKmCaWmelw = false;
      bool ejnodbOaeh = false;
      bool MlhjEpBXYP = false;
      bool HKhJfsQxHT = false;
      bool YXyyaAXnCz = false;
      bool JFhCdbcCyj = false;
      bool VOFWoUBdJk = false;
      string FWtUpukOVg;
      string IWiHMJDpuG;
      string mBZKFESufY;
      string KsRbxdEiwF;
      string BGkZiaDKjh;
      string fyKiLDwjOl;
      string coixVPEHJh;
      string EUspFfQAbe;
      string AHLxrMiiPs;
      string hUTJbLXnDT;
      string VuBBcLEUdf;
      string muIjlVdkEI;
      string gVqPzjAiNs;
      string HcwIIEFJUg;
      string HOEjGlLjXG;
      string hmitlzEkBr;
      string KUGjYKyAag;
      string PTQWBRQHJN;
      string XQLGKUsCVI;
      string AUIbVmHULu;
      if(FWtUpukOVg == VuBBcLEUdf){nLJqpOWLsU = true;}
      else if(VuBBcLEUdf == FWtUpukOVg){CeEAmnXRAt = true;}
      if(IWiHMJDpuG == muIjlVdkEI){ixanTtJAYE = true;}
      else if(muIjlVdkEI == IWiHMJDpuG){DDAhqLCjuG = true;}
      if(mBZKFESufY == gVqPzjAiNs){RweRfuLnBN = true;}
      else if(gVqPzjAiNs == mBZKFESufY){jLdgbXfMjq = true;}
      if(KsRbxdEiwF == HcwIIEFJUg){KwwNZMGTQw = true;}
      else if(HcwIIEFJUg == KsRbxdEiwF){NKmCaWmelw = true;}
      if(BGkZiaDKjh == HOEjGlLjXG){xgIAZDsTIa = true;}
      else if(HOEjGlLjXG == BGkZiaDKjh){ejnodbOaeh = true;}
      if(fyKiLDwjOl == hmitlzEkBr){cHuHdqgqKt = true;}
      else if(hmitlzEkBr == fyKiLDwjOl){MlhjEpBXYP = true;}
      if(coixVPEHJh == KUGjYKyAag){DhKfJlANOH = true;}
      else if(KUGjYKyAag == coixVPEHJh){HKhJfsQxHT = true;}
      if(EUspFfQAbe == PTQWBRQHJN){moicGjmdqc = true;}
      if(AHLxrMiiPs == XQLGKUsCVI){CqfZjDBojh = true;}
      if(hUTJbLXnDT == AUIbVmHULu){ePIWsOVcqn = true;}
      while(PTQWBRQHJN == EUspFfQAbe){YXyyaAXnCz = true;}
      while(XQLGKUsCVI == XQLGKUsCVI){JFhCdbcCyj = true;}
      while(AUIbVmHULu == AUIbVmHULu){VOFWoUBdJk = true;}
      if(nLJqpOWLsU == true){nLJqpOWLsU = false;}
      if(ixanTtJAYE == true){ixanTtJAYE = false;}
      if(RweRfuLnBN == true){RweRfuLnBN = false;}
      if(KwwNZMGTQw == true){KwwNZMGTQw = false;}
      if(xgIAZDsTIa == true){xgIAZDsTIa = false;}
      if(cHuHdqgqKt == true){cHuHdqgqKt = false;}
      if(DhKfJlANOH == true){DhKfJlANOH = false;}
      if(moicGjmdqc == true){moicGjmdqc = false;}
      if(CqfZjDBojh == true){CqfZjDBojh = false;}
      if(ePIWsOVcqn == true){ePIWsOVcqn = false;}
      if(CeEAmnXRAt == true){CeEAmnXRAt = false;}
      if(DDAhqLCjuG == true){DDAhqLCjuG = false;}
      if(jLdgbXfMjq == true){jLdgbXfMjq = false;}
      if(NKmCaWmelw == true){NKmCaWmelw = false;}
      if(ejnodbOaeh == true){ejnodbOaeh = false;}
      if(MlhjEpBXYP == true){MlhjEpBXYP = false;}
      if(HKhJfsQxHT == true){HKhJfsQxHT = false;}
      if(YXyyaAXnCz == true){YXyyaAXnCz = false;}
      if(JFhCdbcCyj == true){JFhCdbcCyj = false;}
      if(VOFWoUBdJk == true){VOFWoUBdJk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LEBOCDSRJK
{ 
  void sIiOeDpIcL()
  { 
      bool UIwnVgCywn = false;
      bool wOdpoZwnim = false;
      bool iGAugBEyht = false;
      bool LpPLMgknaR = false;
      bool WqYpRCCFOM = false;
      bool GiSsFOIAHU = false;
      bool bDPBcFyRcI = false;
      bool nHNRQrgJdd = false;
      bool yyiVmbXWGy = false;
      bool YkgFoSaXNL = false;
      bool DjcGXzVAbM = false;
      bool hyWcVcUsOA = false;
      bool gbKeiDZHby = false;
      bool RJuRaNVcym = false;
      bool GXttPZNEjL = false;
      bool xgIMdaZyWU = false;
      bool YNYduYCFCH = false;
      bool HquatJhQOI = false;
      bool oVXPAjAimz = false;
      bool nXFcOrzQyq = false;
      string xQPmIEmZtb;
      string KNQagNFyoZ;
      string oZqRHDHuwq;
      string kYprRMRyTs;
      string sUjJAnZCXE;
      string BTfsJWYxfF;
      string xrdDpkXYJT;
      string wGeufTohQS;
      string dEXqoQswit;
      string nTSOwBqgSO;
      string QBsDHuojMo;
      string gqgMarTlNY;
      string rboOfcnPze;
      string cIOBCcLTjs;
      string bIisNxmFmD;
      string gESsWnLeXe;
      string HYkgMYbeJy;
      string gACUxirwAh;
      string ohcwyYoVeO;
      string RfuElCXBgn;
      if(xQPmIEmZtb == QBsDHuojMo){UIwnVgCywn = true;}
      else if(QBsDHuojMo == xQPmIEmZtb){DjcGXzVAbM = true;}
      if(KNQagNFyoZ == gqgMarTlNY){wOdpoZwnim = true;}
      else if(gqgMarTlNY == KNQagNFyoZ){hyWcVcUsOA = true;}
      if(oZqRHDHuwq == rboOfcnPze){iGAugBEyht = true;}
      else if(rboOfcnPze == oZqRHDHuwq){gbKeiDZHby = true;}
      if(kYprRMRyTs == cIOBCcLTjs){LpPLMgknaR = true;}
      else if(cIOBCcLTjs == kYprRMRyTs){RJuRaNVcym = true;}
      if(sUjJAnZCXE == bIisNxmFmD){WqYpRCCFOM = true;}
      else if(bIisNxmFmD == sUjJAnZCXE){GXttPZNEjL = true;}
      if(BTfsJWYxfF == gESsWnLeXe){GiSsFOIAHU = true;}
      else if(gESsWnLeXe == BTfsJWYxfF){xgIMdaZyWU = true;}
      if(xrdDpkXYJT == HYkgMYbeJy){bDPBcFyRcI = true;}
      else if(HYkgMYbeJy == xrdDpkXYJT){YNYduYCFCH = true;}
      if(wGeufTohQS == gACUxirwAh){nHNRQrgJdd = true;}
      if(dEXqoQswit == ohcwyYoVeO){yyiVmbXWGy = true;}
      if(nTSOwBqgSO == RfuElCXBgn){YkgFoSaXNL = true;}
      while(gACUxirwAh == wGeufTohQS){HquatJhQOI = true;}
      while(ohcwyYoVeO == ohcwyYoVeO){oVXPAjAimz = true;}
      while(RfuElCXBgn == RfuElCXBgn){nXFcOrzQyq = true;}
      if(UIwnVgCywn == true){UIwnVgCywn = false;}
      if(wOdpoZwnim == true){wOdpoZwnim = false;}
      if(iGAugBEyht == true){iGAugBEyht = false;}
      if(LpPLMgknaR == true){LpPLMgknaR = false;}
      if(WqYpRCCFOM == true){WqYpRCCFOM = false;}
      if(GiSsFOIAHU == true){GiSsFOIAHU = false;}
      if(bDPBcFyRcI == true){bDPBcFyRcI = false;}
      if(nHNRQrgJdd == true){nHNRQrgJdd = false;}
      if(yyiVmbXWGy == true){yyiVmbXWGy = false;}
      if(YkgFoSaXNL == true){YkgFoSaXNL = false;}
      if(DjcGXzVAbM == true){DjcGXzVAbM = false;}
      if(hyWcVcUsOA == true){hyWcVcUsOA = false;}
      if(gbKeiDZHby == true){gbKeiDZHby = false;}
      if(RJuRaNVcym == true){RJuRaNVcym = false;}
      if(GXttPZNEjL == true){GXttPZNEjL = false;}
      if(xgIMdaZyWU == true){xgIMdaZyWU = false;}
      if(YNYduYCFCH == true){YNYduYCFCH = false;}
      if(HquatJhQOI == true){HquatJhQOI = false;}
      if(oVXPAjAimz == true){oVXPAjAimz = false;}
      if(nXFcOrzQyq == true){nXFcOrzQyq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YGMEIACSFW
{ 
  void giHWOSRstN()
  { 
      bool ucaOfmhJSY = false;
      bool GpUpgdrgfy = false;
      bool oCikObAqVQ = false;
      bool JVmJHxBufS = false;
      bool HRzuCEAGXW = false;
      bool NRgrisspAE = false;
      bool lqmBOkCLij = false;
      bool bxANqXCmhK = false;
      bool btSzCqnuaO = false;
      bool DKubfQdxgQ = false;
      bool BoXntQQTBL = false;
      bool pGHocrXnzX = false;
      bool wHjTgRBYgZ = false;
      bool sEGRIlVeEl = false;
      bool ZUsPXwCFzn = false;
      bool soyITtEDGc = false;
      bool OrlbRkApgp = false;
      bool VrjMxbNUwj = false;
      bool OwZsgDGxxN = false;
      bool hRXbWhhRxl = false;
      string IhtfneeDQc;
      string jquoQStpKs;
      string SRYCMVJhYb;
      string EDcyECchNU;
      string YOztQmbKbC;
      string QMZyLqIqSR;
      string UwdoXfNxjN;
      string pMcoUDSelY;
      string tzFWKrddmN;
      string tkOuzcjKVj;
      string ZeZNLDjjdH;
      string YdFsXVpGdf;
      string CiKWTFxgpr;
      string SHICzOYrLG;
      string IszeoQfUXc;
      string lcfphpUDtG;
      string GCtlnQUDtI;
      string xyuWWIiehD;
      string ZbJMFoaSTJ;
      string tVxEAGzNqX;
      if(IhtfneeDQc == ZeZNLDjjdH){ucaOfmhJSY = true;}
      else if(ZeZNLDjjdH == IhtfneeDQc){BoXntQQTBL = true;}
      if(jquoQStpKs == YdFsXVpGdf){GpUpgdrgfy = true;}
      else if(YdFsXVpGdf == jquoQStpKs){pGHocrXnzX = true;}
      if(SRYCMVJhYb == CiKWTFxgpr){oCikObAqVQ = true;}
      else if(CiKWTFxgpr == SRYCMVJhYb){wHjTgRBYgZ = true;}
      if(EDcyECchNU == SHICzOYrLG){JVmJHxBufS = true;}
      else if(SHICzOYrLG == EDcyECchNU){sEGRIlVeEl = true;}
      if(YOztQmbKbC == IszeoQfUXc){HRzuCEAGXW = true;}
      else if(IszeoQfUXc == YOztQmbKbC){ZUsPXwCFzn = true;}
      if(QMZyLqIqSR == lcfphpUDtG){NRgrisspAE = true;}
      else if(lcfphpUDtG == QMZyLqIqSR){soyITtEDGc = true;}
      if(UwdoXfNxjN == GCtlnQUDtI){lqmBOkCLij = true;}
      else if(GCtlnQUDtI == UwdoXfNxjN){OrlbRkApgp = true;}
      if(pMcoUDSelY == xyuWWIiehD){bxANqXCmhK = true;}
      if(tzFWKrddmN == ZbJMFoaSTJ){btSzCqnuaO = true;}
      if(tkOuzcjKVj == tVxEAGzNqX){DKubfQdxgQ = true;}
      while(xyuWWIiehD == pMcoUDSelY){VrjMxbNUwj = true;}
      while(ZbJMFoaSTJ == ZbJMFoaSTJ){OwZsgDGxxN = true;}
      while(tVxEAGzNqX == tVxEAGzNqX){hRXbWhhRxl = true;}
      if(ucaOfmhJSY == true){ucaOfmhJSY = false;}
      if(GpUpgdrgfy == true){GpUpgdrgfy = false;}
      if(oCikObAqVQ == true){oCikObAqVQ = false;}
      if(JVmJHxBufS == true){JVmJHxBufS = false;}
      if(HRzuCEAGXW == true){HRzuCEAGXW = false;}
      if(NRgrisspAE == true){NRgrisspAE = false;}
      if(lqmBOkCLij == true){lqmBOkCLij = false;}
      if(bxANqXCmhK == true){bxANqXCmhK = false;}
      if(btSzCqnuaO == true){btSzCqnuaO = false;}
      if(DKubfQdxgQ == true){DKubfQdxgQ = false;}
      if(BoXntQQTBL == true){BoXntQQTBL = false;}
      if(pGHocrXnzX == true){pGHocrXnzX = false;}
      if(wHjTgRBYgZ == true){wHjTgRBYgZ = false;}
      if(sEGRIlVeEl == true){sEGRIlVeEl = false;}
      if(ZUsPXwCFzn == true){ZUsPXwCFzn = false;}
      if(soyITtEDGc == true){soyITtEDGc = false;}
      if(OrlbRkApgp == true){OrlbRkApgp = false;}
      if(VrjMxbNUwj == true){VrjMxbNUwj = false;}
      if(OwZsgDGxxN == true){OwZsgDGxxN = false;}
      if(hRXbWhhRxl == true){hRXbWhhRxl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VMABSWNXSU
{ 
  void skzxOYFURY()
  { 
      bool ebGbyMIqkL = false;
      bool qINjyzCkaX = false;
      bool urBcPWOaIN = false;
      bool wsMjHphMFU = false;
      bool AlLWbFRcZZ = false;
      bool tcgHomacLa = false;
      bool xgiXOywdbI = false;
      bool QpeGWIgdBK = false;
      bool ElBhSTLEtU = false;
      bool OEAeWTDmHc = false;
      bool InARJDyajg = false;
      bool GxbAVLeAEu = false;
      bool mqiHsLoAiD = false;
      bool FsVXBPkjYP = false;
      bool UjTNORcAIL = false;
      bool nCiMpQFrYx = false;
      bool NxrgbMaDzG = false;
      bool ZuaoZCXUsa = false;
      bool ioqXOCJJhj = false;
      bool KsLbBXrmlB = false;
      string fPglIJNrYW;
      string kGpGSUGHqn;
      string mfzwBsMqQi;
      string BVrYmOmyOR;
      string UYJOCaXhfd;
      string ndVxMzPjkO;
      string xVaoVPOQSE;
      string hHsZTOWjsZ;
      string VdLltXzuLm;
      string yCNzUyxTsm;
      string MGObwgjudy;
      string cepKsSKotx;
      string PSFfFessFU;
      string QDqGNOPioN;
      string mEQMKSMDFB;
      string nHYuXsBiWQ;
      string npoIgZnjxd;
      string DazgKLBrUl;
      string SonEgIdwiT;
      string NfMXYwOIfk;
      if(fPglIJNrYW == MGObwgjudy){ebGbyMIqkL = true;}
      else if(MGObwgjudy == fPglIJNrYW){InARJDyajg = true;}
      if(kGpGSUGHqn == cepKsSKotx){qINjyzCkaX = true;}
      else if(cepKsSKotx == kGpGSUGHqn){GxbAVLeAEu = true;}
      if(mfzwBsMqQi == PSFfFessFU){urBcPWOaIN = true;}
      else if(PSFfFessFU == mfzwBsMqQi){mqiHsLoAiD = true;}
      if(BVrYmOmyOR == QDqGNOPioN){wsMjHphMFU = true;}
      else if(QDqGNOPioN == BVrYmOmyOR){FsVXBPkjYP = true;}
      if(UYJOCaXhfd == mEQMKSMDFB){AlLWbFRcZZ = true;}
      else if(mEQMKSMDFB == UYJOCaXhfd){UjTNORcAIL = true;}
      if(ndVxMzPjkO == nHYuXsBiWQ){tcgHomacLa = true;}
      else if(nHYuXsBiWQ == ndVxMzPjkO){nCiMpQFrYx = true;}
      if(xVaoVPOQSE == npoIgZnjxd){xgiXOywdbI = true;}
      else if(npoIgZnjxd == xVaoVPOQSE){NxrgbMaDzG = true;}
      if(hHsZTOWjsZ == DazgKLBrUl){QpeGWIgdBK = true;}
      if(VdLltXzuLm == SonEgIdwiT){ElBhSTLEtU = true;}
      if(yCNzUyxTsm == NfMXYwOIfk){OEAeWTDmHc = true;}
      while(DazgKLBrUl == hHsZTOWjsZ){ZuaoZCXUsa = true;}
      while(SonEgIdwiT == SonEgIdwiT){ioqXOCJJhj = true;}
      while(NfMXYwOIfk == NfMXYwOIfk){KsLbBXrmlB = true;}
      if(ebGbyMIqkL == true){ebGbyMIqkL = false;}
      if(qINjyzCkaX == true){qINjyzCkaX = false;}
      if(urBcPWOaIN == true){urBcPWOaIN = false;}
      if(wsMjHphMFU == true){wsMjHphMFU = false;}
      if(AlLWbFRcZZ == true){AlLWbFRcZZ = false;}
      if(tcgHomacLa == true){tcgHomacLa = false;}
      if(xgiXOywdbI == true){xgiXOywdbI = false;}
      if(QpeGWIgdBK == true){QpeGWIgdBK = false;}
      if(ElBhSTLEtU == true){ElBhSTLEtU = false;}
      if(OEAeWTDmHc == true){OEAeWTDmHc = false;}
      if(InARJDyajg == true){InARJDyajg = false;}
      if(GxbAVLeAEu == true){GxbAVLeAEu = false;}
      if(mqiHsLoAiD == true){mqiHsLoAiD = false;}
      if(FsVXBPkjYP == true){FsVXBPkjYP = false;}
      if(UjTNORcAIL == true){UjTNORcAIL = false;}
      if(nCiMpQFrYx == true){nCiMpQFrYx = false;}
      if(NxrgbMaDzG == true){NxrgbMaDzG = false;}
      if(ZuaoZCXUsa == true){ZuaoZCXUsa = false;}
      if(ioqXOCJJhj == true){ioqXOCJJhj = false;}
      if(KsLbBXrmlB == true){KsLbBXrmlB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JUDBPFTJLY
{ 
  void gISIlDHNJi()
  { 
      bool iYLjPcRxRh = false;
      bool stXIyrfBNO = false;
      bool PTPOZJdDas = false;
      bool hTaCkXNVyQ = false;
      bool xzJeztTaVO = false;
      bool cCwmEPJxKG = false;
      bool yOWXzYTVWa = false;
      bool eJCxRPKjPf = false;
      bool oDhMPeXnxV = false;
      bool NPLrSicleZ = false;
      bool ayDtiTAzVo = false;
      bool EZhdQtfJHT = false;
      bool BeYAMPyKeh = false;
      bool mYEoEqAmcw = false;
      bool eYRHRnggbX = false;
      bool DSdLYuZChT = false;
      bool UpTnCfUrZZ = false;
      bool srgKocNQiY = false;
      bool hQhGeTtsQJ = false;
      bool RxFIboEcFk = false;
      string ORsZroLVZy;
      string bKWNuEjnSl;
      string ODOSPPOrWf;
      string NBDpjYoAFg;
      string kdjBEcQcAK;
      string taisWLDZJb;
      string aSztjaHfcV;
      string OiilBkTMNl;
      string ylqLkmRJTY;
      string VOpcFRdoRd;
      string VkzduKrwql;
      string qqMXcnanIx;
      string IxLEAzrFfj;
      string GduiQNmNPZ;
      string tUShgeCSzR;
      string ppgTVXYtdu;
      string RlQHeMucGP;
      string BNXiCmedWU;
      string xZGOsPxaNr;
      string oriTHIEKCU;
      if(ORsZroLVZy == VkzduKrwql){iYLjPcRxRh = true;}
      else if(VkzduKrwql == ORsZroLVZy){ayDtiTAzVo = true;}
      if(bKWNuEjnSl == qqMXcnanIx){stXIyrfBNO = true;}
      else if(qqMXcnanIx == bKWNuEjnSl){EZhdQtfJHT = true;}
      if(ODOSPPOrWf == IxLEAzrFfj){PTPOZJdDas = true;}
      else if(IxLEAzrFfj == ODOSPPOrWf){BeYAMPyKeh = true;}
      if(NBDpjYoAFg == GduiQNmNPZ){hTaCkXNVyQ = true;}
      else if(GduiQNmNPZ == NBDpjYoAFg){mYEoEqAmcw = true;}
      if(kdjBEcQcAK == tUShgeCSzR){xzJeztTaVO = true;}
      else if(tUShgeCSzR == kdjBEcQcAK){eYRHRnggbX = true;}
      if(taisWLDZJb == ppgTVXYtdu){cCwmEPJxKG = true;}
      else if(ppgTVXYtdu == taisWLDZJb){DSdLYuZChT = true;}
      if(aSztjaHfcV == RlQHeMucGP){yOWXzYTVWa = true;}
      else if(RlQHeMucGP == aSztjaHfcV){UpTnCfUrZZ = true;}
      if(OiilBkTMNl == BNXiCmedWU){eJCxRPKjPf = true;}
      if(ylqLkmRJTY == xZGOsPxaNr){oDhMPeXnxV = true;}
      if(VOpcFRdoRd == oriTHIEKCU){NPLrSicleZ = true;}
      while(BNXiCmedWU == OiilBkTMNl){srgKocNQiY = true;}
      while(xZGOsPxaNr == xZGOsPxaNr){hQhGeTtsQJ = true;}
      while(oriTHIEKCU == oriTHIEKCU){RxFIboEcFk = true;}
      if(iYLjPcRxRh == true){iYLjPcRxRh = false;}
      if(stXIyrfBNO == true){stXIyrfBNO = false;}
      if(PTPOZJdDas == true){PTPOZJdDas = false;}
      if(hTaCkXNVyQ == true){hTaCkXNVyQ = false;}
      if(xzJeztTaVO == true){xzJeztTaVO = false;}
      if(cCwmEPJxKG == true){cCwmEPJxKG = false;}
      if(yOWXzYTVWa == true){yOWXzYTVWa = false;}
      if(eJCxRPKjPf == true){eJCxRPKjPf = false;}
      if(oDhMPeXnxV == true){oDhMPeXnxV = false;}
      if(NPLrSicleZ == true){NPLrSicleZ = false;}
      if(ayDtiTAzVo == true){ayDtiTAzVo = false;}
      if(EZhdQtfJHT == true){EZhdQtfJHT = false;}
      if(BeYAMPyKeh == true){BeYAMPyKeh = false;}
      if(mYEoEqAmcw == true){mYEoEqAmcw = false;}
      if(eYRHRnggbX == true){eYRHRnggbX = false;}
      if(DSdLYuZChT == true){DSdLYuZChT = false;}
      if(UpTnCfUrZZ == true){UpTnCfUrZZ = false;}
      if(srgKocNQiY == true){srgKocNQiY = false;}
      if(hQhGeTtsQJ == true){hQhGeTtsQJ = false;}
      if(RxFIboEcFk == true){RxFIboEcFk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WJCXEOESQW
{ 
  void jwXdnngHbi()
  { 
      bool IArmHrjEFn = false;
      bool UJncxYbelW = false;
      bool EKkUopNcqj = false;
      bool UVyNwVftly = false;
      bool ZQGongJSJj = false;
      bool lnACqyPWxR = false;
      bool dHMUTyKZfb = false;
      bool shrnxmDugI = false;
      bool fuTHyfVwWx = false;
      bool GIwUTSDkVo = false;
      bool VilhpDuMFD = false;
      bool tTpnkinFWm = false;
      bool cODiUjlXUd = false;
      bool iSZqmwIkQt = false;
      bool kJqTClRHij = false;
      bool eyNiMHfDMG = false;
      bool RWraTbtzBn = false;
      bool aCncBTXjfh = false;
      bool RdojzkEpde = false;
      bool QEYKbOQPza = false;
      string gHgHzQFCaW;
      string WssFEmdsQH;
      string gxaAzEEUKX;
      string RnkqFAQuSs;
      string ZWMgoKQdWc;
      string ZjjBWjgfHt;
      string LkrDFhHBAE;
      string ViZWgJjsLo;
      string naxgxhEiUV;
      string SjnYgoeJbG;
      string COdSGqJNUM;
      string zmURFkmKFW;
      string dXgekltAor;
      string eZQFmYwdaF;
      string XpOHVePWTw;
      string BTEEbdhyhT;
      string xJXbhZWOdf;
      string nJjzzmIYJF;
      string WXgspKVLdJ;
      string pyuGIOSmZu;
      if(gHgHzQFCaW == COdSGqJNUM){IArmHrjEFn = true;}
      else if(COdSGqJNUM == gHgHzQFCaW){VilhpDuMFD = true;}
      if(WssFEmdsQH == zmURFkmKFW){UJncxYbelW = true;}
      else if(zmURFkmKFW == WssFEmdsQH){tTpnkinFWm = true;}
      if(gxaAzEEUKX == dXgekltAor){EKkUopNcqj = true;}
      else if(dXgekltAor == gxaAzEEUKX){cODiUjlXUd = true;}
      if(RnkqFAQuSs == eZQFmYwdaF){UVyNwVftly = true;}
      else if(eZQFmYwdaF == RnkqFAQuSs){iSZqmwIkQt = true;}
      if(ZWMgoKQdWc == XpOHVePWTw){ZQGongJSJj = true;}
      else if(XpOHVePWTw == ZWMgoKQdWc){kJqTClRHij = true;}
      if(ZjjBWjgfHt == BTEEbdhyhT){lnACqyPWxR = true;}
      else if(BTEEbdhyhT == ZjjBWjgfHt){eyNiMHfDMG = true;}
      if(LkrDFhHBAE == xJXbhZWOdf){dHMUTyKZfb = true;}
      else if(xJXbhZWOdf == LkrDFhHBAE){RWraTbtzBn = true;}
      if(ViZWgJjsLo == nJjzzmIYJF){shrnxmDugI = true;}
      if(naxgxhEiUV == WXgspKVLdJ){fuTHyfVwWx = true;}
      if(SjnYgoeJbG == pyuGIOSmZu){GIwUTSDkVo = true;}
      while(nJjzzmIYJF == ViZWgJjsLo){aCncBTXjfh = true;}
      while(WXgspKVLdJ == WXgspKVLdJ){RdojzkEpde = true;}
      while(pyuGIOSmZu == pyuGIOSmZu){QEYKbOQPza = true;}
      if(IArmHrjEFn == true){IArmHrjEFn = false;}
      if(UJncxYbelW == true){UJncxYbelW = false;}
      if(EKkUopNcqj == true){EKkUopNcqj = false;}
      if(UVyNwVftly == true){UVyNwVftly = false;}
      if(ZQGongJSJj == true){ZQGongJSJj = false;}
      if(lnACqyPWxR == true){lnACqyPWxR = false;}
      if(dHMUTyKZfb == true){dHMUTyKZfb = false;}
      if(shrnxmDugI == true){shrnxmDugI = false;}
      if(fuTHyfVwWx == true){fuTHyfVwWx = false;}
      if(GIwUTSDkVo == true){GIwUTSDkVo = false;}
      if(VilhpDuMFD == true){VilhpDuMFD = false;}
      if(tTpnkinFWm == true){tTpnkinFWm = false;}
      if(cODiUjlXUd == true){cODiUjlXUd = false;}
      if(iSZqmwIkQt == true){iSZqmwIkQt = false;}
      if(kJqTClRHij == true){kJqTClRHij = false;}
      if(eyNiMHfDMG == true){eyNiMHfDMG = false;}
      if(RWraTbtzBn == true){RWraTbtzBn = false;}
      if(aCncBTXjfh == true){aCncBTXjfh = false;}
      if(RdojzkEpde == true){RdojzkEpde = false;}
      if(QEYKbOQPza == true){QEYKbOQPza = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UCXPYMLSMS
{ 
  void WVBkdRWKAD()
  { 
      bool kCghKtqOjJ = false;
      bool HlIMJUsXtl = false;
      bool cLgPRpKASq = false;
      bool gIuFyTiqpI = false;
      bool wjQxTkGAxE = false;
      bool gqYpwZVQQU = false;
      bool jpusbzqDOo = false;
      bool kChlorujwg = false;
      bool iKCOJoiEJY = false;
      bool ySaVYFnWUU = false;
      bool sDlHSdJmBD = false;
      bool dlUikZngim = false;
      bool PmsoqSbLNi = false;
      bool DXObmfYtwe = false;
      bool ewDFtMxqky = false;
      bool RHngEGJwQz = false;
      bool CyYRzGWswF = false;
      bool BskDISimte = false;
      bool UkaORwihWf = false;
      bool VbdwcgXkGn = false;
      string OkWzxemsUr;
      string lKBwptqlsy;
      string uPDSDCCOVf;
      string VQdIgusYqB;
      string ZQzkNLfgZr;
      string sKirryhEwt;
      string cXXoWUfrOu;
      string ARtqXePREq;
      string VUodlKhlQi;
      string NocwYBrKOr;
      string emSeqaQrTM;
      string hPzEYIitDL;
      string ltbegLoxRV;
      string lFDMMiCKlK;
      string tpRDBxoYXQ;
      string SyGCFjKmxe;
      string lSZyZbMmqo;
      string FXHrRwcYdj;
      string VQYBDnzAGb;
      string XPNGYaPTcY;
      if(OkWzxemsUr == emSeqaQrTM){kCghKtqOjJ = true;}
      else if(emSeqaQrTM == OkWzxemsUr){sDlHSdJmBD = true;}
      if(lKBwptqlsy == hPzEYIitDL){HlIMJUsXtl = true;}
      else if(hPzEYIitDL == lKBwptqlsy){dlUikZngim = true;}
      if(uPDSDCCOVf == ltbegLoxRV){cLgPRpKASq = true;}
      else if(ltbegLoxRV == uPDSDCCOVf){PmsoqSbLNi = true;}
      if(VQdIgusYqB == lFDMMiCKlK){gIuFyTiqpI = true;}
      else if(lFDMMiCKlK == VQdIgusYqB){DXObmfYtwe = true;}
      if(ZQzkNLfgZr == tpRDBxoYXQ){wjQxTkGAxE = true;}
      else if(tpRDBxoYXQ == ZQzkNLfgZr){ewDFtMxqky = true;}
      if(sKirryhEwt == SyGCFjKmxe){gqYpwZVQQU = true;}
      else if(SyGCFjKmxe == sKirryhEwt){RHngEGJwQz = true;}
      if(cXXoWUfrOu == lSZyZbMmqo){jpusbzqDOo = true;}
      else if(lSZyZbMmqo == cXXoWUfrOu){CyYRzGWswF = true;}
      if(ARtqXePREq == FXHrRwcYdj){kChlorujwg = true;}
      if(VUodlKhlQi == VQYBDnzAGb){iKCOJoiEJY = true;}
      if(NocwYBrKOr == XPNGYaPTcY){ySaVYFnWUU = true;}
      while(FXHrRwcYdj == ARtqXePREq){BskDISimte = true;}
      while(VQYBDnzAGb == VQYBDnzAGb){UkaORwihWf = true;}
      while(XPNGYaPTcY == XPNGYaPTcY){VbdwcgXkGn = true;}
      if(kCghKtqOjJ == true){kCghKtqOjJ = false;}
      if(HlIMJUsXtl == true){HlIMJUsXtl = false;}
      if(cLgPRpKASq == true){cLgPRpKASq = false;}
      if(gIuFyTiqpI == true){gIuFyTiqpI = false;}
      if(wjQxTkGAxE == true){wjQxTkGAxE = false;}
      if(gqYpwZVQQU == true){gqYpwZVQQU = false;}
      if(jpusbzqDOo == true){jpusbzqDOo = false;}
      if(kChlorujwg == true){kChlorujwg = false;}
      if(iKCOJoiEJY == true){iKCOJoiEJY = false;}
      if(ySaVYFnWUU == true){ySaVYFnWUU = false;}
      if(sDlHSdJmBD == true){sDlHSdJmBD = false;}
      if(dlUikZngim == true){dlUikZngim = false;}
      if(PmsoqSbLNi == true){PmsoqSbLNi = false;}
      if(DXObmfYtwe == true){DXObmfYtwe = false;}
      if(ewDFtMxqky == true){ewDFtMxqky = false;}
      if(RHngEGJwQz == true){RHngEGJwQz = false;}
      if(CyYRzGWswF == true){CyYRzGWswF = false;}
      if(BskDISimte == true){BskDISimte = false;}
      if(UkaORwihWf == true){UkaORwihWf = false;}
      if(VbdwcgXkGn == true){VbdwcgXkGn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DMAPQZZELF
{ 
  void WcAYgyqTEH()
  { 
      bool eDAGfpYwsD = false;
      bool MJcolikGfM = false;
      bool KFnTxqZYCl = false;
      bool rIHubmoqKO = false;
      bool GXPDVCRSgY = false;
      bool xfjNqYPfJo = false;
      bool QzsHKECgNy = false;
      bool ttwRGlpkyu = false;
      bool YHqdoMXtDC = false;
      bool XIhVyGeHrQ = false;
      bool AkEhdCjSGF = false;
      bool iehNPJIPSy = false;
      bool fHcLalLZTA = false;
      bool GhrgtnCJzl = false;
      bool bFmySrZTGn = false;
      bool yPoskrHsGr = false;
      bool qKzGyBlASa = false;
      bool GyPgWaUerh = false;
      bool LrTeBqsywC = false;
      bool fJCHtRFgzR = false;
      string oijyNdLMTP;
      string uSzjPrAppn;
      string FJaEqzwYJg;
      string MjYrSlQgtH;
      string yGkDMIAWYu;
      string juqFleIeGN;
      string glCmDKtHRd;
      string bSwipyYWri;
      string yZAOwQsSFm;
      string dkafZLDxAB;
      string NsEuSQzHPm;
      string GklXOHlmpl;
      string RbBdzprPJd;
      string uaWqUEUEwf;
      string RkCSgszDQS;
      string YPGNjlrZwc;
      string XiylreOuCK;
      string lhqKTfYhxG;
      string qoyqFeUIHh;
      string MtISHhmQaB;
      if(oijyNdLMTP == NsEuSQzHPm){eDAGfpYwsD = true;}
      else if(NsEuSQzHPm == oijyNdLMTP){AkEhdCjSGF = true;}
      if(uSzjPrAppn == GklXOHlmpl){MJcolikGfM = true;}
      else if(GklXOHlmpl == uSzjPrAppn){iehNPJIPSy = true;}
      if(FJaEqzwYJg == RbBdzprPJd){KFnTxqZYCl = true;}
      else if(RbBdzprPJd == FJaEqzwYJg){fHcLalLZTA = true;}
      if(MjYrSlQgtH == uaWqUEUEwf){rIHubmoqKO = true;}
      else if(uaWqUEUEwf == MjYrSlQgtH){GhrgtnCJzl = true;}
      if(yGkDMIAWYu == RkCSgszDQS){GXPDVCRSgY = true;}
      else if(RkCSgszDQS == yGkDMIAWYu){bFmySrZTGn = true;}
      if(juqFleIeGN == YPGNjlrZwc){xfjNqYPfJo = true;}
      else if(YPGNjlrZwc == juqFleIeGN){yPoskrHsGr = true;}
      if(glCmDKtHRd == XiylreOuCK){QzsHKECgNy = true;}
      else if(XiylreOuCK == glCmDKtHRd){qKzGyBlASa = true;}
      if(bSwipyYWri == lhqKTfYhxG){ttwRGlpkyu = true;}
      if(yZAOwQsSFm == qoyqFeUIHh){YHqdoMXtDC = true;}
      if(dkafZLDxAB == MtISHhmQaB){XIhVyGeHrQ = true;}
      while(lhqKTfYhxG == bSwipyYWri){GyPgWaUerh = true;}
      while(qoyqFeUIHh == qoyqFeUIHh){LrTeBqsywC = true;}
      while(MtISHhmQaB == MtISHhmQaB){fJCHtRFgzR = true;}
      if(eDAGfpYwsD == true){eDAGfpYwsD = false;}
      if(MJcolikGfM == true){MJcolikGfM = false;}
      if(KFnTxqZYCl == true){KFnTxqZYCl = false;}
      if(rIHubmoqKO == true){rIHubmoqKO = false;}
      if(GXPDVCRSgY == true){GXPDVCRSgY = false;}
      if(xfjNqYPfJo == true){xfjNqYPfJo = false;}
      if(QzsHKECgNy == true){QzsHKECgNy = false;}
      if(ttwRGlpkyu == true){ttwRGlpkyu = false;}
      if(YHqdoMXtDC == true){YHqdoMXtDC = false;}
      if(XIhVyGeHrQ == true){XIhVyGeHrQ = false;}
      if(AkEhdCjSGF == true){AkEhdCjSGF = false;}
      if(iehNPJIPSy == true){iehNPJIPSy = false;}
      if(fHcLalLZTA == true){fHcLalLZTA = false;}
      if(GhrgtnCJzl == true){GhrgtnCJzl = false;}
      if(bFmySrZTGn == true){bFmySrZTGn = false;}
      if(yPoskrHsGr == true){yPoskrHsGr = false;}
      if(qKzGyBlASa == true){qKzGyBlASa = false;}
      if(GyPgWaUerh == true){GyPgWaUerh = false;}
      if(LrTeBqsywC == true){LrTeBqsywC = false;}
      if(fJCHtRFgzR == true){fJCHtRFgzR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WFADEKAGMX
{ 
  void mUgzFHtQLg()
  { 
      bool HgGKcIYtjq = false;
      bool gbLtxrrfct = false;
      bool GnHtBOqkwz = false;
      bool jxfJJXDWAj = false;
      bool DqlJHzLiAS = false;
      bool jmyoTTYLIO = false;
      bool RmyjGjwCkY = false;
      bool nVfrpPBymC = false;
      bool CHkcPxyqop = false;
      bool yrNlSPrCCX = false;
      bool DJyadOHGyE = false;
      bool RaXFLJCUUJ = false;
      bool kEMtZwHsYZ = false;
      bool WzuOzsIJzA = false;
      bool orskXXTHZJ = false;
      bool NWgsmywDBg = false;
      bool GNgXgSeJGS = false;
      bool ArVTTsLbWC = false;
      bool bzTPMzRCbB = false;
      bool wFIRtaLUDE = false;
      string IQiJyzZJWa;
      string AGYtfJmQJu;
      string uRuHJXYdel;
      string yqtrpiVTLu;
      string jTHTjnrEsj;
      string VANDgpVbAa;
      string ZwdkbIMfDx;
      string nTFNKaKaWV;
      string eTkuPxcpLz;
      string NsTjUnpWqa;
      string bLAuwCuArG;
      string ftEdwGKhUe;
      string fVUDjtzUrW;
      string jmiwtSTozN;
      string CbxFTSopnO;
      string dHBMuFqwLB;
      string CZIVVrKIjc;
      string lUiGbDYPjR;
      string EJgcsblWAo;
      string aXdxKcSbia;
      if(IQiJyzZJWa == bLAuwCuArG){HgGKcIYtjq = true;}
      else if(bLAuwCuArG == IQiJyzZJWa){DJyadOHGyE = true;}
      if(AGYtfJmQJu == ftEdwGKhUe){gbLtxrrfct = true;}
      else if(ftEdwGKhUe == AGYtfJmQJu){RaXFLJCUUJ = true;}
      if(uRuHJXYdel == fVUDjtzUrW){GnHtBOqkwz = true;}
      else if(fVUDjtzUrW == uRuHJXYdel){kEMtZwHsYZ = true;}
      if(yqtrpiVTLu == jmiwtSTozN){jxfJJXDWAj = true;}
      else if(jmiwtSTozN == yqtrpiVTLu){WzuOzsIJzA = true;}
      if(jTHTjnrEsj == CbxFTSopnO){DqlJHzLiAS = true;}
      else if(CbxFTSopnO == jTHTjnrEsj){orskXXTHZJ = true;}
      if(VANDgpVbAa == dHBMuFqwLB){jmyoTTYLIO = true;}
      else if(dHBMuFqwLB == VANDgpVbAa){NWgsmywDBg = true;}
      if(ZwdkbIMfDx == CZIVVrKIjc){RmyjGjwCkY = true;}
      else if(CZIVVrKIjc == ZwdkbIMfDx){GNgXgSeJGS = true;}
      if(nTFNKaKaWV == lUiGbDYPjR){nVfrpPBymC = true;}
      if(eTkuPxcpLz == EJgcsblWAo){CHkcPxyqop = true;}
      if(NsTjUnpWqa == aXdxKcSbia){yrNlSPrCCX = true;}
      while(lUiGbDYPjR == nTFNKaKaWV){ArVTTsLbWC = true;}
      while(EJgcsblWAo == EJgcsblWAo){bzTPMzRCbB = true;}
      while(aXdxKcSbia == aXdxKcSbia){wFIRtaLUDE = true;}
      if(HgGKcIYtjq == true){HgGKcIYtjq = false;}
      if(gbLtxrrfct == true){gbLtxrrfct = false;}
      if(GnHtBOqkwz == true){GnHtBOqkwz = false;}
      if(jxfJJXDWAj == true){jxfJJXDWAj = false;}
      if(DqlJHzLiAS == true){DqlJHzLiAS = false;}
      if(jmyoTTYLIO == true){jmyoTTYLIO = false;}
      if(RmyjGjwCkY == true){RmyjGjwCkY = false;}
      if(nVfrpPBymC == true){nVfrpPBymC = false;}
      if(CHkcPxyqop == true){CHkcPxyqop = false;}
      if(yrNlSPrCCX == true){yrNlSPrCCX = false;}
      if(DJyadOHGyE == true){DJyadOHGyE = false;}
      if(RaXFLJCUUJ == true){RaXFLJCUUJ = false;}
      if(kEMtZwHsYZ == true){kEMtZwHsYZ = false;}
      if(WzuOzsIJzA == true){WzuOzsIJzA = false;}
      if(orskXXTHZJ == true){orskXXTHZJ = false;}
      if(NWgsmywDBg == true){NWgsmywDBg = false;}
      if(GNgXgSeJGS == true){GNgXgSeJGS = false;}
      if(ArVTTsLbWC == true){ArVTTsLbWC = false;}
      if(bzTPMzRCbB == true){bzTPMzRCbB = false;}
      if(wFIRtaLUDE == true){wFIRtaLUDE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSTHWLVJRE
{ 
  void aUIpRVMwxY()
  { 
      bool WNjQKetTXO = false;
      bool EGSyGsWwLj = false;
      bool TgelWEzLgD = false;
      bool holTEflcPJ = false;
      bool cBLJVLlRpA = false;
      bool jPKykoixsF = false;
      bool eilTgOTzta = false;
      bool GtgBGRVUQL = false;
      bool SgUgTRemhO = false;
      bool xoiJdtPqcG = false;
      bool qmXPspiJqT = false;
      bool TNghmyNFAO = false;
      bool jfQedRKWWM = false;
      bool CeqJTeJEmd = false;
      bool iVwOuiHBWf = false;
      bool fJpNWLVrkb = false;
      bool eLldQnVXOH = false;
      bool nISWfNjBiu = false;
      bool JJzpfrocmI = false;
      bool JRTKyWiRxH = false;
      string BwnKKhrDXa;
      string JJZMZWKsyW;
      string RCchUxZGku;
      string zgXrxoIqCf;
      string meHsOhSWaZ;
      string CIhSUzSFpM;
      string HlScabkhOk;
      string OTpRjltjTm;
      string dDfKrqzEXx;
      string VDAoXALeSl;
      string wkHoLiSPih;
      string EhkDiEGIji;
      string cgKQOKSAsi;
      string aPRhpsupyJ;
      string YiVosmRxGT;
      string tDtiIPapZA;
      string PRWAGoQDMo;
      string JPJaKtKUXa;
      string sVtZoWUiYa;
      string REQxsHMVhE;
      if(BwnKKhrDXa == wkHoLiSPih){WNjQKetTXO = true;}
      else if(wkHoLiSPih == BwnKKhrDXa){qmXPspiJqT = true;}
      if(JJZMZWKsyW == EhkDiEGIji){EGSyGsWwLj = true;}
      else if(EhkDiEGIji == JJZMZWKsyW){TNghmyNFAO = true;}
      if(RCchUxZGku == cgKQOKSAsi){TgelWEzLgD = true;}
      else if(cgKQOKSAsi == RCchUxZGku){jfQedRKWWM = true;}
      if(zgXrxoIqCf == aPRhpsupyJ){holTEflcPJ = true;}
      else if(aPRhpsupyJ == zgXrxoIqCf){CeqJTeJEmd = true;}
      if(meHsOhSWaZ == YiVosmRxGT){cBLJVLlRpA = true;}
      else if(YiVosmRxGT == meHsOhSWaZ){iVwOuiHBWf = true;}
      if(CIhSUzSFpM == tDtiIPapZA){jPKykoixsF = true;}
      else if(tDtiIPapZA == CIhSUzSFpM){fJpNWLVrkb = true;}
      if(HlScabkhOk == PRWAGoQDMo){eilTgOTzta = true;}
      else if(PRWAGoQDMo == HlScabkhOk){eLldQnVXOH = true;}
      if(OTpRjltjTm == JPJaKtKUXa){GtgBGRVUQL = true;}
      if(dDfKrqzEXx == sVtZoWUiYa){SgUgTRemhO = true;}
      if(VDAoXALeSl == REQxsHMVhE){xoiJdtPqcG = true;}
      while(JPJaKtKUXa == OTpRjltjTm){nISWfNjBiu = true;}
      while(sVtZoWUiYa == sVtZoWUiYa){JJzpfrocmI = true;}
      while(REQxsHMVhE == REQxsHMVhE){JRTKyWiRxH = true;}
      if(WNjQKetTXO == true){WNjQKetTXO = false;}
      if(EGSyGsWwLj == true){EGSyGsWwLj = false;}
      if(TgelWEzLgD == true){TgelWEzLgD = false;}
      if(holTEflcPJ == true){holTEflcPJ = false;}
      if(cBLJVLlRpA == true){cBLJVLlRpA = false;}
      if(jPKykoixsF == true){jPKykoixsF = false;}
      if(eilTgOTzta == true){eilTgOTzta = false;}
      if(GtgBGRVUQL == true){GtgBGRVUQL = false;}
      if(SgUgTRemhO == true){SgUgTRemhO = false;}
      if(xoiJdtPqcG == true){xoiJdtPqcG = false;}
      if(qmXPspiJqT == true){qmXPspiJqT = false;}
      if(TNghmyNFAO == true){TNghmyNFAO = false;}
      if(jfQedRKWWM == true){jfQedRKWWM = false;}
      if(CeqJTeJEmd == true){CeqJTeJEmd = false;}
      if(iVwOuiHBWf == true){iVwOuiHBWf = false;}
      if(fJpNWLVrkb == true){fJpNWLVrkb = false;}
      if(eLldQnVXOH == true){eLldQnVXOH = false;}
      if(nISWfNjBiu == true){nISWfNjBiu = false;}
      if(JJzpfrocmI == true){JJzpfrocmI = false;}
      if(JRTKyWiRxH == true){JRTKyWiRxH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QJYJZNVBGZ
{ 
  void mPeHKKkTNx()
  { 
      bool fjyypPulVp = false;
      bool hqVpyXZpLx = false;
      bool AoFDXOXzkH = false;
      bool fQEgRTzuVT = false;
      bool UfsTffaVVq = false;
      bool axFscqdtaa = false;
      bool rwBNJRlnYe = false;
      bool YeTqcUulWq = false;
      bool mBcsgiKLEZ = false;
      bool oETtbYdeJN = false;
      bool smxqRucNQI = false;
      bool urXjmpSHga = false;
      bool GajypUKZPE = false;
      bool pQbJxAElbk = false;
      bool FxuwdwgjGk = false;
      bool FVyhHSDyAx = false;
      bool kDyLRePNmm = false;
      bool lffuUJfmTs = false;
      bool mZSdyTRtBd = false;
      bool xFkdACyidy = false;
      string MZoewyebhm;
      string mmbGHmXAFS;
      string FIWTrnoSMb;
      string dZxbanDyJA;
      string xUdSgBnVsm;
      string IzUCdDDVmH;
      string JLOFINpzeT;
      string iYpEVkdElp;
      string ATZYTdEtyW;
      string jhLBqkFYJS;
      string LnpYDiIPgs;
      string YziwHokokd;
      string IuAIjBMnNj;
      string eFtTeLdBVk;
      string VoNExkyPtB;
      string APmeJQmgoB;
      string VUCwNTEORu;
      string LjTAIThwLy;
      string DxtLjPSPJO;
      string XwMTPBmQqd;
      if(MZoewyebhm == LnpYDiIPgs){fjyypPulVp = true;}
      else if(LnpYDiIPgs == MZoewyebhm){smxqRucNQI = true;}
      if(mmbGHmXAFS == YziwHokokd){hqVpyXZpLx = true;}
      else if(YziwHokokd == mmbGHmXAFS){urXjmpSHga = true;}
      if(FIWTrnoSMb == IuAIjBMnNj){AoFDXOXzkH = true;}
      else if(IuAIjBMnNj == FIWTrnoSMb){GajypUKZPE = true;}
      if(dZxbanDyJA == eFtTeLdBVk){fQEgRTzuVT = true;}
      else if(eFtTeLdBVk == dZxbanDyJA){pQbJxAElbk = true;}
      if(xUdSgBnVsm == VoNExkyPtB){UfsTffaVVq = true;}
      else if(VoNExkyPtB == xUdSgBnVsm){FxuwdwgjGk = true;}
      if(IzUCdDDVmH == APmeJQmgoB){axFscqdtaa = true;}
      else if(APmeJQmgoB == IzUCdDDVmH){FVyhHSDyAx = true;}
      if(JLOFINpzeT == VUCwNTEORu){rwBNJRlnYe = true;}
      else if(VUCwNTEORu == JLOFINpzeT){kDyLRePNmm = true;}
      if(iYpEVkdElp == LjTAIThwLy){YeTqcUulWq = true;}
      if(ATZYTdEtyW == DxtLjPSPJO){mBcsgiKLEZ = true;}
      if(jhLBqkFYJS == XwMTPBmQqd){oETtbYdeJN = true;}
      while(LjTAIThwLy == iYpEVkdElp){lffuUJfmTs = true;}
      while(DxtLjPSPJO == DxtLjPSPJO){mZSdyTRtBd = true;}
      while(XwMTPBmQqd == XwMTPBmQqd){xFkdACyidy = true;}
      if(fjyypPulVp == true){fjyypPulVp = false;}
      if(hqVpyXZpLx == true){hqVpyXZpLx = false;}
      if(AoFDXOXzkH == true){AoFDXOXzkH = false;}
      if(fQEgRTzuVT == true){fQEgRTzuVT = false;}
      if(UfsTffaVVq == true){UfsTffaVVq = false;}
      if(axFscqdtaa == true){axFscqdtaa = false;}
      if(rwBNJRlnYe == true){rwBNJRlnYe = false;}
      if(YeTqcUulWq == true){YeTqcUulWq = false;}
      if(mBcsgiKLEZ == true){mBcsgiKLEZ = false;}
      if(oETtbYdeJN == true){oETtbYdeJN = false;}
      if(smxqRucNQI == true){smxqRucNQI = false;}
      if(urXjmpSHga == true){urXjmpSHga = false;}
      if(GajypUKZPE == true){GajypUKZPE = false;}
      if(pQbJxAElbk == true){pQbJxAElbk = false;}
      if(FxuwdwgjGk == true){FxuwdwgjGk = false;}
      if(FVyhHSDyAx == true){FVyhHSDyAx = false;}
      if(kDyLRePNmm == true){kDyLRePNmm = false;}
      if(lffuUJfmTs == true){lffuUJfmTs = false;}
      if(mZSdyTRtBd == true){mZSdyTRtBd = false;}
      if(xFkdACyidy == true){xFkdACyidy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BGGBSUXSOG
{ 
  void MBRconTtrp()
  { 
      bool mszZKsTMiI = false;
      bool MQMAFCUgjB = false;
      bool KbIaaCRnJE = false;
      bool XTniFkHYbM = false;
      bool cKUKYsWYVt = false;
      bool NApiIKjXyH = false;
      bool afDdkrcduU = false;
      bool tuEXYAHyCh = false;
      bool fsSOpXcEZt = false;
      bool AiaUkxHpZf = false;
      bool PscBzSuRKI = false;
      bool DkVPbhMnnM = false;
      bool OYDBTLUjma = false;
      bool sQYVSlPRPX = false;
      bool cKtQqOMKrC = false;
      bool jSCNQqobgn = false;
      bool yLeiPlMAxp = false;
      bool SuXQjDdmKE = false;
      bool yJrjqZOLEb = false;
      bool xmjbYQfKAE = false;
      string mRyLHWtarq;
      string plLtBYSnIU;
      string RuYjsXQLHw;
      string TdYlQRsigo;
      string fbakggYxnO;
      string MlXXVrsNRj;
      string FiSuXMNYci;
      string ejGTopUmDM;
      string zTWsihFAPY;
      string YfQwixJeMU;
      string TzTEiceEif;
      string XFKFklLZMp;
      string GMIEKzSKjr;
      string goZhrzzSKG;
      string CBRjBSVLLx;
      string liSWOHpPsi;
      string JTTqzhfbMk;
      string lrPFmFtYCr;
      string dHzmGxWDTk;
      string JjZawigakT;
      if(mRyLHWtarq == TzTEiceEif){mszZKsTMiI = true;}
      else if(TzTEiceEif == mRyLHWtarq){PscBzSuRKI = true;}
      if(plLtBYSnIU == XFKFklLZMp){MQMAFCUgjB = true;}
      else if(XFKFklLZMp == plLtBYSnIU){DkVPbhMnnM = true;}
      if(RuYjsXQLHw == GMIEKzSKjr){KbIaaCRnJE = true;}
      else if(GMIEKzSKjr == RuYjsXQLHw){OYDBTLUjma = true;}
      if(TdYlQRsigo == goZhrzzSKG){XTniFkHYbM = true;}
      else if(goZhrzzSKG == TdYlQRsigo){sQYVSlPRPX = true;}
      if(fbakggYxnO == CBRjBSVLLx){cKUKYsWYVt = true;}
      else if(CBRjBSVLLx == fbakggYxnO){cKtQqOMKrC = true;}
      if(MlXXVrsNRj == liSWOHpPsi){NApiIKjXyH = true;}
      else if(liSWOHpPsi == MlXXVrsNRj){jSCNQqobgn = true;}
      if(FiSuXMNYci == JTTqzhfbMk){afDdkrcduU = true;}
      else if(JTTqzhfbMk == FiSuXMNYci){yLeiPlMAxp = true;}
      if(ejGTopUmDM == lrPFmFtYCr){tuEXYAHyCh = true;}
      if(zTWsihFAPY == dHzmGxWDTk){fsSOpXcEZt = true;}
      if(YfQwixJeMU == JjZawigakT){AiaUkxHpZf = true;}
      while(lrPFmFtYCr == ejGTopUmDM){SuXQjDdmKE = true;}
      while(dHzmGxWDTk == dHzmGxWDTk){yJrjqZOLEb = true;}
      while(JjZawigakT == JjZawigakT){xmjbYQfKAE = true;}
      if(mszZKsTMiI == true){mszZKsTMiI = false;}
      if(MQMAFCUgjB == true){MQMAFCUgjB = false;}
      if(KbIaaCRnJE == true){KbIaaCRnJE = false;}
      if(XTniFkHYbM == true){XTniFkHYbM = false;}
      if(cKUKYsWYVt == true){cKUKYsWYVt = false;}
      if(NApiIKjXyH == true){NApiIKjXyH = false;}
      if(afDdkrcduU == true){afDdkrcduU = false;}
      if(tuEXYAHyCh == true){tuEXYAHyCh = false;}
      if(fsSOpXcEZt == true){fsSOpXcEZt = false;}
      if(AiaUkxHpZf == true){AiaUkxHpZf = false;}
      if(PscBzSuRKI == true){PscBzSuRKI = false;}
      if(DkVPbhMnnM == true){DkVPbhMnnM = false;}
      if(OYDBTLUjma == true){OYDBTLUjma = false;}
      if(sQYVSlPRPX == true){sQYVSlPRPX = false;}
      if(cKtQqOMKrC == true){cKtQqOMKrC = false;}
      if(jSCNQqobgn == true){jSCNQqobgn = false;}
      if(yLeiPlMAxp == true){yLeiPlMAxp = false;}
      if(SuXQjDdmKE == true){SuXQjDdmKE = false;}
      if(yJrjqZOLEb == true){yJrjqZOLEb = false;}
      if(xmjbYQfKAE == true){xmjbYQfKAE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NESLQXAHKI
{ 
  void aVTlHSWzHs()
  { 
      bool ZAxAeMJHgR = false;
      bool dYeqNwUtPU = false;
      bool YGXTRCBhPG = false;
      bool RbkUZYlNAw = false;
      bool rFnVNqDzng = false;
      bool GMJWVScdhb = false;
      bool LarZzCmJQn = false;
      bool JHsSbSRBGZ = false;
      bool zBthAFROzG = false;
      bool wIeXkQNOWK = false;
      bool EtiAXzSptC = false;
      bool BaXHcKgKZs = false;
      bool jYKKrAbVhK = false;
      bool FDewVFStJA = false;
      bool mbTwFVkXtZ = false;
      bool iCncZfiXHW = false;
      bool WxHiwxualX = false;
      bool rmAYGIENEV = false;
      bool PEaIaDOCVp = false;
      bool VtllcoTjzH = false;
      string hpnJmamSmf;
      string ELumkESXmd;
      string cMjZWcrkcy;
      string yyXUFUQfsM;
      string iKrpBTSXJN;
      string NJwjlVGOmK;
      string hCpnhGnZgP;
      string nmeauRTsYD;
      string KTbPkoBmij;
      string OBshefUEIt;
      string frqsZaeVnT;
      string CMoiANaZDs;
      string EAqxBltwwO;
      string xOkdXRchoK;
      string KfzOgBLJhQ;
      string FtBPpfBtqm;
      string fhZZWmbLLh;
      string krjshYBcPz;
      string ZjNeJCNVmq;
      string QhqCdbGYqt;
      if(hpnJmamSmf == frqsZaeVnT){ZAxAeMJHgR = true;}
      else if(frqsZaeVnT == hpnJmamSmf){EtiAXzSptC = true;}
      if(ELumkESXmd == CMoiANaZDs){dYeqNwUtPU = true;}
      else if(CMoiANaZDs == ELumkESXmd){BaXHcKgKZs = true;}
      if(cMjZWcrkcy == EAqxBltwwO){YGXTRCBhPG = true;}
      else if(EAqxBltwwO == cMjZWcrkcy){jYKKrAbVhK = true;}
      if(yyXUFUQfsM == xOkdXRchoK){RbkUZYlNAw = true;}
      else if(xOkdXRchoK == yyXUFUQfsM){FDewVFStJA = true;}
      if(iKrpBTSXJN == KfzOgBLJhQ){rFnVNqDzng = true;}
      else if(KfzOgBLJhQ == iKrpBTSXJN){mbTwFVkXtZ = true;}
      if(NJwjlVGOmK == FtBPpfBtqm){GMJWVScdhb = true;}
      else if(FtBPpfBtqm == NJwjlVGOmK){iCncZfiXHW = true;}
      if(hCpnhGnZgP == fhZZWmbLLh){LarZzCmJQn = true;}
      else if(fhZZWmbLLh == hCpnhGnZgP){WxHiwxualX = true;}
      if(nmeauRTsYD == krjshYBcPz){JHsSbSRBGZ = true;}
      if(KTbPkoBmij == ZjNeJCNVmq){zBthAFROzG = true;}
      if(OBshefUEIt == QhqCdbGYqt){wIeXkQNOWK = true;}
      while(krjshYBcPz == nmeauRTsYD){rmAYGIENEV = true;}
      while(ZjNeJCNVmq == ZjNeJCNVmq){PEaIaDOCVp = true;}
      while(QhqCdbGYqt == QhqCdbGYqt){VtllcoTjzH = true;}
      if(ZAxAeMJHgR == true){ZAxAeMJHgR = false;}
      if(dYeqNwUtPU == true){dYeqNwUtPU = false;}
      if(YGXTRCBhPG == true){YGXTRCBhPG = false;}
      if(RbkUZYlNAw == true){RbkUZYlNAw = false;}
      if(rFnVNqDzng == true){rFnVNqDzng = false;}
      if(GMJWVScdhb == true){GMJWVScdhb = false;}
      if(LarZzCmJQn == true){LarZzCmJQn = false;}
      if(JHsSbSRBGZ == true){JHsSbSRBGZ = false;}
      if(zBthAFROzG == true){zBthAFROzG = false;}
      if(wIeXkQNOWK == true){wIeXkQNOWK = false;}
      if(EtiAXzSptC == true){EtiAXzSptC = false;}
      if(BaXHcKgKZs == true){BaXHcKgKZs = false;}
      if(jYKKrAbVhK == true){jYKKrAbVhK = false;}
      if(FDewVFStJA == true){FDewVFStJA = false;}
      if(mbTwFVkXtZ == true){mbTwFVkXtZ = false;}
      if(iCncZfiXHW == true){iCncZfiXHW = false;}
      if(WxHiwxualX == true){WxHiwxualX = false;}
      if(rmAYGIENEV == true){rmAYGIENEV = false;}
      if(PEaIaDOCVp == true){PEaIaDOCVp = false;}
      if(VtllcoTjzH == true){VtllcoTjzH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KRYPVODIUG
{ 
  void nkqBamQSmB()
  { 
      bool MLzSufljRU = false;
      bool ofEoZEybtV = false;
      bool EpoQGoCAjU = false;
      bool bsaGxTNxNM = false;
      bool UdZYTKhwjq = false;
      bool tlhIzWWhLG = false;
      bool ckzwruFyqG = false;
      bool pAOgAaQQxw = false;
      bool GGPsZoKSHa = false;
      bool xfkGjidcfX = false;
      bool EjEdBtXAHY = false;
      bool GGkPzWVGVD = false;
      bool kmpQJKOHxQ = false;
      bool xmjZqVBkqf = false;
      bool QJKhUptVHM = false;
      bool NWGbmRsnUp = false;
      bool fQDqbSVLXc = false;
      bool UkPplacIwS = false;
      bool PrzjDZfHmZ = false;
      bool cNQAzAGSFB = false;
      string NcBTdeFCpH;
      string VcxPbcaYRM;
      string VVBKNazsfa;
      string eQZwMZWWwh;
      string FtbcGyzzFk;
      string HZAIIrbpGD;
      string eMVObFDACB;
      string FDbiGbsXEO;
      string bAmuSFPRnU;
      string xfQsCsXNBA;
      string uyxDeExQBg;
      string yDlrbeYauV;
      string okMgEYlhfN;
      string DfWDScCjPO;
      string HzPHWttYRX;
      string UwReKKlPzF;
      string ROjmcSghYy;
      string bnKgNpVFKJ;
      string eNQIsGOqsI;
      string qmkKwsObdD;
      if(NcBTdeFCpH == uyxDeExQBg){MLzSufljRU = true;}
      else if(uyxDeExQBg == NcBTdeFCpH){EjEdBtXAHY = true;}
      if(VcxPbcaYRM == yDlrbeYauV){ofEoZEybtV = true;}
      else if(yDlrbeYauV == VcxPbcaYRM){GGkPzWVGVD = true;}
      if(VVBKNazsfa == okMgEYlhfN){EpoQGoCAjU = true;}
      else if(okMgEYlhfN == VVBKNazsfa){kmpQJKOHxQ = true;}
      if(eQZwMZWWwh == DfWDScCjPO){bsaGxTNxNM = true;}
      else if(DfWDScCjPO == eQZwMZWWwh){xmjZqVBkqf = true;}
      if(FtbcGyzzFk == HzPHWttYRX){UdZYTKhwjq = true;}
      else if(HzPHWttYRX == FtbcGyzzFk){QJKhUptVHM = true;}
      if(HZAIIrbpGD == UwReKKlPzF){tlhIzWWhLG = true;}
      else if(UwReKKlPzF == HZAIIrbpGD){NWGbmRsnUp = true;}
      if(eMVObFDACB == ROjmcSghYy){ckzwruFyqG = true;}
      else if(ROjmcSghYy == eMVObFDACB){fQDqbSVLXc = true;}
      if(FDbiGbsXEO == bnKgNpVFKJ){pAOgAaQQxw = true;}
      if(bAmuSFPRnU == eNQIsGOqsI){GGPsZoKSHa = true;}
      if(xfQsCsXNBA == qmkKwsObdD){xfkGjidcfX = true;}
      while(bnKgNpVFKJ == FDbiGbsXEO){UkPplacIwS = true;}
      while(eNQIsGOqsI == eNQIsGOqsI){PrzjDZfHmZ = true;}
      while(qmkKwsObdD == qmkKwsObdD){cNQAzAGSFB = true;}
      if(MLzSufljRU == true){MLzSufljRU = false;}
      if(ofEoZEybtV == true){ofEoZEybtV = false;}
      if(EpoQGoCAjU == true){EpoQGoCAjU = false;}
      if(bsaGxTNxNM == true){bsaGxTNxNM = false;}
      if(UdZYTKhwjq == true){UdZYTKhwjq = false;}
      if(tlhIzWWhLG == true){tlhIzWWhLG = false;}
      if(ckzwruFyqG == true){ckzwruFyqG = false;}
      if(pAOgAaQQxw == true){pAOgAaQQxw = false;}
      if(GGPsZoKSHa == true){GGPsZoKSHa = false;}
      if(xfkGjidcfX == true){xfkGjidcfX = false;}
      if(EjEdBtXAHY == true){EjEdBtXAHY = false;}
      if(GGkPzWVGVD == true){GGkPzWVGVD = false;}
      if(kmpQJKOHxQ == true){kmpQJKOHxQ = false;}
      if(xmjZqVBkqf == true){xmjZqVBkqf = false;}
      if(QJKhUptVHM == true){QJKhUptVHM = false;}
      if(NWGbmRsnUp == true){NWGbmRsnUp = false;}
      if(fQDqbSVLXc == true){fQDqbSVLXc = false;}
      if(UkPplacIwS == true){UkPplacIwS = false;}
      if(PrzjDZfHmZ == true){PrzjDZfHmZ = false;}
      if(cNQAzAGSFB == true){cNQAzAGSFB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ANRJIKCEJD
{ 
  void RudJdUNZlu()
  { 
      bool nawbkPRgIj = false;
      bool woOCAPaYPT = false;
      bool tCueeNdVqW = false;
      bool wKsTccKolp = false;
      bool GQqQBlVGhF = false;
      bool GPxGGleRxX = false;
      bool lwolmlwtZX = false;
      bool FkmYNdKecr = false;
      bool qWmkPgMlMp = false;
      bool xrrOEJaFcP = false;
      bool pagKAVcYrc = false;
      bool aznFfOIEVG = false;
      bool YJhiZMsYTD = false;
      bool CFCMBQockt = false;
      bool DntiOyDlhp = false;
      bool BWiVqgsyjm = false;
      bool bEEnaVwbDP = false;
      bool YeSaCjPyTa = false;
      bool JGpdCfWfVU = false;
      bool WqrySzjFIs = false;
      string MUFWqtRTsk;
      string OkrrspCYyN;
      string bnyVkTIwMs;
      string lCRABdZEyn;
      string mTyqFsmoqu;
      string zTNEtYWikX;
      string lUHzyMTrpO;
      string QyaJZHpGPq;
      string fSFQtSoMFb;
      string GpSaCRMyss;
      string ZuybeBrDdm;
      string iPStqSPpFe;
      string WGlOIaeAHI;
      string tqNWRkUclr;
      string ZkiSspWYij;
      string CVsNVTIjTD;
      string WrwVrqCwbG;
      string ymEMElXTUR;
      string DGRWFXxAAx;
      string bjJhVhoMZB;
      if(MUFWqtRTsk == ZuybeBrDdm){nawbkPRgIj = true;}
      else if(ZuybeBrDdm == MUFWqtRTsk){pagKAVcYrc = true;}
      if(OkrrspCYyN == iPStqSPpFe){woOCAPaYPT = true;}
      else if(iPStqSPpFe == OkrrspCYyN){aznFfOIEVG = true;}
      if(bnyVkTIwMs == WGlOIaeAHI){tCueeNdVqW = true;}
      else if(WGlOIaeAHI == bnyVkTIwMs){YJhiZMsYTD = true;}
      if(lCRABdZEyn == tqNWRkUclr){wKsTccKolp = true;}
      else if(tqNWRkUclr == lCRABdZEyn){CFCMBQockt = true;}
      if(mTyqFsmoqu == ZkiSspWYij){GQqQBlVGhF = true;}
      else if(ZkiSspWYij == mTyqFsmoqu){DntiOyDlhp = true;}
      if(zTNEtYWikX == CVsNVTIjTD){GPxGGleRxX = true;}
      else if(CVsNVTIjTD == zTNEtYWikX){BWiVqgsyjm = true;}
      if(lUHzyMTrpO == WrwVrqCwbG){lwolmlwtZX = true;}
      else if(WrwVrqCwbG == lUHzyMTrpO){bEEnaVwbDP = true;}
      if(QyaJZHpGPq == ymEMElXTUR){FkmYNdKecr = true;}
      if(fSFQtSoMFb == DGRWFXxAAx){qWmkPgMlMp = true;}
      if(GpSaCRMyss == bjJhVhoMZB){xrrOEJaFcP = true;}
      while(ymEMElXTUR == QyaJZHpGPq){YeSaCjPyTa = true;}
      while(DGRWFXxAAx == DGRWFXxAAx){JGpdCfWfVU = true;}
      while(bjJhVhoMZB == bjJhVhoMZB){WqrySzjFIs = true;}
      if(nawbkPRgIj == true){nawbkPRgIj = false;}
      if(woOCAPaYPT == true){woOCAPaYPT = false;}
      if(tCueeNdVqW == true){tCueeNdVqW = false;}
      if(wKsTccKolp == true){wKsTccKolp = false;}
      if(GQqQBlVGhF == true){GQqQBlVGhF = false;}
      if(GPxGGleRxX == true){GPxGGleRxX = false;}
      if(lwolmlwtZX == true){lwolmlwtZX = false;}
      if(FkmYNdKecr == true){FkmYNdKecr = false;}
      if(qWmkPgMlMp == true){qWmkPgMlMp = false;}
      if(xrrOEJaFcP == true){xrrOEJaFcP = false;}
      if(pagKAVcYrc == true){pagKAVcYrc = false;}
      if(aznFfOIEVG == true){aznFfOIEVG = false;}
      if(YJhiZMsYTD == true){YJhiZMsYTD = false;}
      if(CFCMBQockt == true){CFCMBQockt = false;}
      if(DntiOyDlhp == true){DntiOyDlhp = false;}
      if(BWiVqgsyjm == true){BWiVqgsyjm = false;}
      if(bEEnaVwbDP == true){bEEnaVwbDP = false;}
      if(YeSaCjPyTa == true){YeSaCjPyTa = false;}
      if(JGpdCfWfVU == true){JGpdCfWfVU = false;}
      if(WqrySzjFIs == true){WqrySzjFIs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NVXXTCSHKQ
{ 
  void BbCarpwhwl()
  { 
      bool DzrujoNtqR = false;
      bool XulJBnICzl = false;
      bool glCFOgDQrx = false;
      bool KqlEFgRHLy = false;
      bool QjEUceJewX = false;
      bool NZHhLQxlgD = false;
      bool kxCsGfJhDU = false;
      bool VApAVwhhbj = false;
      bool XYTUjjiDsn = false;
      bool jfaINShKNx = false;
      bool UbbbBMiGLO = false;
      bool iOJxeMcgJW = false;
      bool wFnOkoZhmC = false;
      bool OWUeOwwrSW = false;
      bool AcqdEUVdcB = false;
      bool oABqBPmMqM = false;
      bool lBTJAMtehi = false;
      bool PkOlVTNKJP = false;
      bool TwEkMOVddz = false;
      bool JjBGjzIhcr = false;
      string SJXUAdSxzH;
      string WKCYrEmifE;
      string RlHdBMCyYR;
      string ZYNDbZOypz;
      string BruqSNqjer;
      string yroKwgCsTm;
      string bTYhgywyxR;
      string porgCZqPLn;
      string USTfTgiCHt;
      string XVeDWgTMJT;
      string QslMCJAIIW;
      string pmgeRJArOA;
      string OsqCtUKnJU;
      string FdFrXbfHdK;
      string gatkEknzkN;
      string gayJFWBjSg;
      string yLymQLgoGo;
      string crNDSmzGxJ;
      string fKDwmdeulB;
      string awnxLVcHTr;
      if(SJXUAdSxzH == QslMCJAIIW){DzrujoNtqR = true;}
      else if(QslMCJAIIW == SJXUAdSxzH){UbbbBMiGLO = true;}
      if(WKCYrEmifE == pmgeRJArOA){XulJBnICzl = true;}
      else if(pmgeRJArOA == WKCYrEmifE){iOJxeMcgJW = true;}
      if(RlHdBMCyYR == OsqCtUKnJU){glCFOgDQrx = true;}
      else if(OsqCtUKnJU == RlHdBMCyYR){wFnOkoZhmC = true;}
      if(ZYNDbZOypz == FdFrXbfHdK){KqlEFgRHLy = true;}
      else if(FdFrXbfHdK == ZYNDbZOypz){OWUeOwwrSW = true;}
      if(BruqSNqjer == gatkEknzkN){QjEUceJewX = true;}
      else if(gatkEknzkN == BruqSNqjer){AcqdEUVdcB = true;}
      if(yroKwgCsTm == gayJFWBjSg){NZHhLQxlgD = true;}
      else if(gayJFWBjSg == yroKwgCsTm){oABqBPmMqM = true;}
      if(bTYhgywyxR == yLymQLgoGo){kxCsGfJhDU = true;}
      else if(yLymQLgoGo == bTYhgywyxR){lBTJAMtehi = true;}
      if(porgCZqPLn == crNDSmzGxJ){VApAVwhhbj = true;}
      if(USTfTgiCHt == fKDwmdeulB){XYTUjjiDsn = true;}
      if(XVeDWgTMJT == awnxLVcHTr){jfaINShKNx = true;}
      while(crNDSmzGxJ == porgCZqPLn){PkOlVTNKJP = true;}
      while(fKDwmdeulB == fKDwmdeulB){TwEkMOVddz = true;}
      while(awnxLVcHTr == awnxLVcHTr){JjBGjzIhcr = true;}
      if(DzrujoNtqR == true){DzrujoNtqR = false;}
      if(XulJBnICzl == true){XulJBnICzl = false;}
      if(glCFOgDQrx == true){glCFOgDQrx = false;}
      if(KqlEFgRHLy == true){KqlEFgRHLy = false;}
      if(QjEUceJewX == true){QjEUceJewX = false;}
      if(NZHhLQxlgD == true){NZHhLQxlgD = false;}
      if(kxCsGfJhDU == true){kxCsGfJhDU = false;}
      if(VApAVwhhbj == true){VApAVwhhbj = false;}
      if(XYTUjjiDsn == true){XYTUjjiDsn = false;}
      if(jfaINShKNx == true){jfaINShKNx = false;}
      if(UbbbBMiGLO == true){UbbbBMiGLO = false;}
      if(iOJxeMcgJW == true){iOJxeMcgJW = false;}
      if(wFnOkoZhmC == true){wFnOkoZhmC = false;}
      if(OWUeOwwrSW == true){OWUeOwwrSW = false;}
      if(AcqdEUVdcB == true){AcqdEUVdcB = false;}
      if(oABqBPmMqM == true){oABqBPmMqM = false;}
      if(lBTJAMtehi == true){lBTJAMtehi = false;}
      if(PkOlVTNKJP == true){PkOlVTNKJP = false;}
      if(TwEkMOVddz == true){TwEkMOVddz = false;}
      if(JjBGjzIhcr == true){JjBGjzIhcr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YHCSYBQOUA
{ 
  void XkTnUcMISV()
  { 
      bool pltklaHYci = false;
      bool ZOIKakYJFA = false;
      bool AMGhBFWsfi = false;
      bool JHniffmrmb = false;
      bool EGJhCqzciJ = false;
      bool VemmjdfLjg = false;
      bool EOssYRaYet = false;
      bool xgVdwsDXfK = false;
      bool FsJWMdUAzB = false;
      bool zbIGWpNQJj = false;
      bool PaynMoJJqp = false;
      bool ZIeYaKEVft = false;
      bool xZYcuUXOGF = false;
      bool fmOwteuVKX = false;
      bool UKJIbqxifL = false;
      bool lqjOloBUrq = false;
      bool RuDlKmtheu = false;
      bool PhLIZlQQBE = false;
      bool WohtSnCzJF = false;
      bool cZcSFZHWyn = false;
      string rnhAWWDkfR;
      string RFPYEPPnRZ;
      string eMPJHzaGFa;
      string QNFCJHFLUt;
      string QtrkHbgcqf;
      string JsgHTfXYrW;
      string wweEADAMOw;
      string JETXJkTeCe;
      string RyPYRXgyid;
      string jgSxxTOmkD;
      string bUNtVEYJxh;
      string MsWNExgFmc;
      string VBckMclWZo;
      string VftyCxjVCM;
      string yXAAQpKErz;
      string lJAHgaqbgs;
      string SCiIMfzXKH;
      string NLCaeyAbTW;
      string SgdZCLflRb;
      string FHnJtunrnj;
      if(rnhAWWDkfR == bUNtVEYJxh){pltklaHYci = true;}
      else if(bUNtVEYJxh == rnhAWWDkfR){PaynMoJJqp = true;}
      if(RFPYEPPnRZ == MsWNExgFmc){ZOIKakYJFA = true;}
      else if(MsWNExgFmc == RFPYEPPnRZ){ZIeYaKEVft = true;}
      if(eMPJHzaGFa == VBckMclWZo){AMGhBFWsfi = true;}
      else if(VBckMclWZo == eMPJHzaGFa){xZYcuUXOGF = true;}
      if(QNFCJHFLUt == VftyCxjVCM){JHniffmrmb = true;}
      else if(VftyCxjVCM == QNFCJHFLUt){fmOwteuVKX = true;}
      if(QtrkHbgcqf == yXAAQpKErz){EGJhCqzciJ = true;}
      else if(yXAAQpKErz == QtrkHbgcqf){UKJIbqxifL = true;}
      if(JsgHTfXYrW == lJAHgaqbgs){VemmjdfLjg = true;}
      else if(lJAHgaqbgs == JsgHTfXYrW){lqjOloBUrq = true;}
      if(wweEADAMOw == SCiIMfzXKH){EOssYRaYet = true;}
      else if(SCiIMfzXKH == wweEADAMOw){RuDlKmtheu = true;}
      if(JETXJkTeCe == NLCaeyAbTW){xgVdwsDXfK = true;}
      if(RyPYRXgyid == SgdZCLflRb){FsJWMdUAzB = true;}
      if(jgSxxTOmkD == FHnJtunrnj){zbIGWpNQJj = true;}
      while(NLCaeyAbTW == JETXJkTeCe){PhLIZlQQBE = true;}
      while(SgdZCLflRb == SgdZCLflRb){WohtSnCzJF = true;}
      while(FHnJtunrnj == FHnJtunrnj){cZcSFZHWyn = true;}
      if(pltklaHYci == true){pltklaHYci = false;}
      if(ZOIKakYJFA == true){ZOIKakYJFA = false;}
      if(AMGhBFWsfi == true){AMGhBFWsfi = false;}
      if(JHniffmrmb == true){JHniffmrmb = false;}
      if(EGJhCqzciJ == true){EGJhCqzciJ = false;}
      if(VemmjdfLjg == true){VemmjdfLjg = false;}
      if(EOssYRaYet == true){EOssYRaYet = false;}
      if(xgVdwsDXfK == true){xgVdwsDXfK = false;}
      if(FsJWMdUAzB == true){FsJWMdUAzB = false;}
      if(zbIGWpNQJj == true){zbIGWpNQJj = false;}
      if(PaynMoJJqp == true){PaynMoJJqp = false;}
      if(ZIeYaKEVft == true){ZIeYaKEVft = false;}
      if(xZYcuUXOGF == true){xZYcuUXOGF = false;}
      if(fmOwteuVKX == true){fmOwteuVKX = false;}
      if(UKJIbqxifL == true){UKJIbqxifL = false;}
      if(lqjOloBUrq == true){lqjOloBUrq = false;}
      if(RuDlKmtheu == true){RuDlKmtheu = false;}
      if(PhLIZlQQBE == true){PhLIZlQQBE = false;}
      if(WohtSnCzJF == true){WohtSnCzJF = false;}
      if(cZcSFZHWyn == true){cZcSFZHWyn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LRYZJQZSFD
{ 
  void nSbNynUBSl()
  { 
      bool mzdMadAHTe = false;
      bool GAqkecErFx = false;
      bool zpAkEqpMQQ = false;
      bool UoUZMFtjKB = false;
      bool KCfknazpGo = false;
      bool AjOxMxzsIj = false;
      bool nmqDJRfRXZ = false;
      bool hUhDmxJOwc = false;
      bool qAFaPjaWMP = false;
      bool GBaaNWKbbW = false;
      bool uhRfGfCKKP = false;
      bool mjwfrnhPnY = false;
      bool pJFITgsHpQ = false;
      bool lglZhJhZUj = false;
      bool hQLwbVFuhY = false;
      bool otnCgkbILZ = false;
      bool ltTtdGyWxi = false;
      bool FHuDqZxJgy = false;
      bool axZRaqsjsw = false;
      bool hZNuynwRSU = false;
      string xwouGsjSeV;
      string DUBYqHXcge;
      string ntEBKDhfXY;
      string uPjMjCNmVY;
      string dMAtXRZaDy;
      string UyhOrDqmkD;
      string KEtGanknnn;
      string sjHIAasKcs;
      string dHbZDxgUUf;
      string KZCRNYSsTj;
      string gklOEjpZNQ;
      string JgJrYDcTCc;
      string GPTIdThoub;
      string IAqsLsUMVT;
      string GHGDVdPJrJ;
      string uyppcQQdkj;
      string BBdlIJpQff;
      string hQyiVyJPlA;
      string EXwkfKJAPu;
      string bqalSFcTuM;
      if(xwouGsjSeV == gklOEjpZNQ){mzdMadAHTe = true;}
      else if(gklOEjpZNQ == xwouGsjSeV){uhRfGfCKKP = true;}
      if(DUBYqHXcge == JgJrYDcTCc){GAqkecErFx = true;}
      else if(JgJrYDcTCc == DUBYqHXcge){mjwfrnhPnY = true;}
      if(ntEBKDhfXY == GPTIdThoub){zpAkEqpMQQ = true;}
      else if(GPTIdThoub == ntEBKDhfXY){pJFITgsHpQ = true;}
      if(uPjMjCNmVY == IAqsLsUMVT){UoUZMFtjKB = true;}
      else if(IAqsLsUMVT == uPjMjCNmVY){lglZhJhZUj = true;}
      if(dMAtXRZaDy == GHGDVdPJrJ){KCfknazpGo = true;}
      else if(GHGDVdPJrJ == dMAtXRZaDy){hQLwbVFuhY = true;}
      if(UyhOrDqmkD == uyppcQQdkj){AjOxMxzsIj = true;}
      else if(uyppcQQdkj == UyhOrDqmkD){otnCgkbILZ = true;}
      if(KEtGanknnn == BBdlIJpQff){nmqDJRfRXZ = true;}
      else if(BBdlIJpQff == KEtGanknnn){ltTtdGyWxi = true;}
      if(sjHIAasKcs == hQyiVyJPlA){hUhDmxJOwc = true;}
      if(dHbZDxgUUf == EXwkfKJAPu){qAFaPjaWMP = true;}
      if(KZCRNYSsTj == bqalSFcTuM){GBaaNWKbbW = true;}
      while(hQyiVyJPlA == sjHIAasKcs){FHuDqZxJgy = true;}
      while(EXwkfKJAPu == EXwkfKJAPu){axZRaqsjsw = true;}
      while(bqalSFcTuM == bqalSFcTuM){hZNuynwRSU = true;}
      if(mzdMadAHTe == true){mzdMadAHTe = false;}
      if(GAqkecErFx == true){GAqkecErFx = false;}
      if(zpAkEqpMQQ == true){zpAkEqpMQQ = false;}
      if(UoUZMFtjKB == true){UoUZMFtjKB = false;}
      if(KCfknazpGo == true){KCfknazpGo = false;}
      if(AjOxMxzsIj == true){AjOxMxzsIj = false;}
      if(nmqDJRfRXZ == true){nmqDJRfRXZ = false;}
      if(hUhDmxJOwc == true){hUhDmxJOwc = false;}
      if(qAFaPjaWMP == true){qAFaPjaWMP = false;}
      if(GBaaNWKbbW == true){GBaaNWKbbW = false;}
      if(uhRfGfCKKP == true){uhRfGfCKKP = false;}
      if(mjwfrnhPnY == true){mjwfrnhPnY = false;}
      if(pJFITgsHpQ == true){pJFITgsHpQ = false;}
      if(lglZhJhZUj == true){lglZhJhZUj = false;}
      if(hQLwbVFuhY == true){hQLwbVFuhY = false;}
      if(otnCgkbILZ == true){otnCgkbILZ = false;}
      if(ltTtdGyWxi == true){ltTtdGyWxi = false;}
      if(FHuDqZxJgy == true){FHuDqZxJgy = false;}
      if(axZRaqsjsw == true){axZRaqsjsw = false;}
      if(hZNuynwRSU == true){hZNuynwRSU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IRQSGOXQYE
{ 
  void RODTLrCtUi()
  { 
      bool XsHMDDNIMa = false;
      bool AWLwIQdlDn = false;
      bool ASgwOAwIok = false;
      bool FaprrbEEQY = false;
      bool PLXKNNLIHx = false;
      bool yjxMBFLLxC = false;
      bool GETbUYgTDf = false;
      bool MZUdXnuViA = false;
      bool omArmVddpm = false;
      bool PrGORKquon = false;
      bool grFajXOSnM = false;
      bool JobxNTEboz = false;
      bool uCcPQTTGLM = false;
      bool wzgtTxhZIP = false;
      bool GKocdZPJAy = false;
      bool GPGosdOpKP = false;
      bool DIHaPKIhcQ = false;
      bool keTZsjMzlq = false;
      bool EKGMGgrqBo = false;
      bool hrOrLyDOMS = false;
      string ZGwqdFNbkl;
      string xYODVTjVzc;
      string rjQrRGHTIu;
      string FKTDNhVpha;
      string UXwrupiJtG;
      string yKcXCooDZW;
      string ytTpfmFKom;
      string xsmYIUmYxa;
      string XxZBwugwAY;
      string sRQKbZEGMI;
      string kXUGIFXDOh;
      string CQGzzAURtk;
      string FIJPsfcbwh;
      string PgMnozbSsq;
      string XcgSWcKQLb;
      string FlMaCbOFNc;
      string cuHfRUERJz;
      string XBYDNbbqsQ;
      string ULQUcdUkkN;
      string kWFPNcVAAB;
      if(ZGwqdFNbkl == kXUGIFXDOh){XsHMDDNIMa = true;}
      else if(kXUGIFXDOh == ZGwqdFNbkl){grFajXOSnM = true;}
      if(xYODVTjVzc == CQGzzAURtk){AWLwIQdlDn = true;}
      else if(CQGzzAURtk == xYODVTjVzc){JobxNTEboz = true;}
      if(rjQrRGHTIu == FIJPsfcbwh){ASgwOAwIok = true;}
      else if(FIJPsfcbwh == rjQrRGHTIu){uCcPQTTGLM = true;}
      if(FKTDNhVpha == PgMnozbSsq){FaprrbEEQY = true;}
      else if(PgMnozbSsq == FKTDNhVpha){wzgtTxhZIP = true;}
      if(UXwrupiJtG == XcgSWcKQLb){PLXKNNLIHx = true;}
      else if(XcgSWcKQLb == UXwrupiJtG){GKocdZPJAy = true;}
      if(yKcXCooDZW == FlMaCbOFNc){yjxMBFLLxC = true;}
      else if(FlMaCbOFNc == yKcXCooDZW){GPGosdOpKP = true;}
      if(ytTpfmFKom == cuHfRUERJz){GETbUYgTDf = true;}
      else if(cuHfRUERJz == ytTpfmFKom){DIHaPKIhcQ = true;}
      if(xsmYIUmYxa == XBYDNbbqsQ){MZUdXnuViA = true;}
      if(XxZBwugwAY == ULQUcdUkkN){omArmVddpm = true;}
      if(sRQKbZEGMI == kWFPNcVAAB){PrGORKquon = true;}
      while(XBYDNbbqsQ == xsmYIUmYxa){keTZsjMzlq = true;}
      while(ULQUcdUkkN == ULQUcdUkkN){EKGMGgrqBo = true;}
      while(kWFPNcVAAB == kWFPNcVAAB){hrOrLyDOMS = true;}
      if(XsHMDDNIMa == true){XsHMDDNIMa = false;}
      if(AWLwIQdlDn == true){AWLwIQdlDn = false;}
      if(ASgwOAwIok == true){ASgwOAwIok = false;}
      if(FaprrbEEQY == true){FaprrbEEQY = false;}
      if(PLXKNNLIHx == true){PLXKNNLIHx = false;}
      if(yjxMBFLLxC == true){yjxMBFLLxC = false;}
      if(GETbUYgTDf == true){GETbUYgTDf = false;}
      if(MZUdXnuViA == true){MZUdXnuViA = false;}
      if(omArmVddpm == true){omArmVddpm = false;}
      if(PrGORKquon == true){PrGORKquon = false;}
      if(grFajXOSnM == true){grFajXOSnM = false;}
      if(JobxNTEboz == true){JobxNTEboz = false;}
      if(uCcPQTTGLM == true){uCcPQTTGLM = false;}
      if(wzgtTxhZIP == true){wzgtTxhZIP = false;}
      if(GKocdZPJAy == true){GKocdZPJAy = false;}
      if(GPGosdOpKP == true){GPGosdOpKP = false;}
      if(DIHaPKIhcQ == true){DIHaPKIhcQ = false;}
      if(keTZsjMzlq == true){keTZsjMzlq = false;}
      if(EKGMGgrqBo == true){EKGMGgrqBo = false;}
      if(hrOrLyDOMS == true){hrOrLyDOMS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YDICQLRWYH
{ 
  void MeVXMayqGT()
  { 
      bool ItbHOKIJhW = false;
      bool WQRrUWEUyO = false;
      bool XpYosaDJUe = false;
      bool SFINstOHda = false;
      bool hBdCixKude = false;
      bool CWBRuSVlNm = false;
      bool HznDERIDya = false;
      bool HwpXfWLVGw = false;
      bool QHepbwDqSa = false;
      bool YcspTiMZyR = false;
      bool oGwDXFfdkY = false;
      bool GzfRWzTybI = false;
      bool NQkXCdDADx = false;
      bool JkWoGJLbRV = false;
      bool PZGtUYxaSU = false;
      bool POypDXUYBs = false;
      bool CeZnOUcpKN = false;
      bool nrfFrnKpDc = false;
      bool gbgigumgki = false;
      bool nlaYTkzSfz = false;
      string ugpAoKXiOa;
      string ysnhFdyjAC;
      string sIhkUMPJRj;
      string oHtJRuBhRr;
      string oAxTjSLBSS;
      string rQfkHlzEfb;
      string tOQdlpzdQK;
      string cQSINrKOAB;
      string BNpzqYbICe;
      string wwBoyZjSgt;
      string SgkIpbxXXO;
      string bjEdafYRlM;
      string NpbkNfOdKm;
      string IrgFiTchIP;
      string aEkmDLrXOR;
      string BRgUfcFAtJ;
      string NTMjGiDyuH;
      string DqIWlJFohC;
      string nqOrlqLMZF;
      string NcmzBHqAfT;
      if(ugpAoKXiOa == SgkIpbxXXO){ItbHOKIJhW = true;}
      else if(SgkIpbxXXO == ugpAoKXiOa){oGwDXFfdkY = true;}
      if(ysnhFdyjAC == bjEdafYRlM){WQRrUWEUyO = true;}
      else if(bjEdafYRlM == ysnhFdyjAC){GzfRWzTybI = true;}
      if(sIhkUMPJRj == NpbkNfOdKm){XpYosaDJUe = true;}
      else if(NpbkNfOdKm == sIhkUMPJRj){NQkXCdDADx = true;}
      if(oHtJRuBhRr == IrgFiTchIP){SFINstOHda = true;}
      else if(IrgFiTchIP == oHtJRuBhRr){JkWoGJLbRV = true;}
      if(oAxTjSLBSS == aEkmDLrXOR){hBdCixKude = true;}
      else if(aEkmDLrXOR == oAxTjSLBSS){PZGtUYxaSU = true;}
      if(rQfkHlzEfb == BRgUfcFAtJ){CWBRuSVlNm = true;}
      else if(BRgUfcFAtJ == rQfkHlzEfb){POypDXUYBs = true;}
      if(tOQdlpzdQK == NTMjGiDyuH){HznDERIDya = true;}
      else if(NTMjGiDyuH == tOQdlpzdQK){CeZnOUcpKN = true;}
      if(cQSINrKOAB == DqIWlJFohC){HwpXfWLVGw = true;}
      if(BNpzqYbICe == nqOrlqLMZF){QHepbwDqSa = true;}
      if(wwBoyZjSgt == NcmzBHqAfT){YcspTiMZyR = true;}
      while(DqIWlJFohC == cQSINrKOAB){nrfFrnKpDc = true;}
      while(nqOrlqLMZF == nqOrlqLMZF){gbgigumgki = true;}
      while(NcmzBHqAfT == NcmzBHqAfT){nlaYTkzSfz = true;}
      if(ItbHOKIJhW == true){ItbHOKIJhW = false;}
      if(WQRrUWEUyO == true){WQRrUWEUyO = false;}
      if(XpYosaDJUe == true){XpYosaDJUe = false;}
      if(SFINstOHda == true){SFINstOHda = false;}
      if(hBdCixKude == true){hBdCixKude = false;}
      if(CWBRuSVlNm == true){CWBRuSVlNm = false;}
      if(HznDERIDya == true){HznDERIDya = false;}
      if(HwpXfWLVGw == true){HwpXfWLVGw = false;}
      if(QHepbwDqSa == true){QHepbwDqSa = false;}
      if(YcspTiMZyR == true){YcspTiMZyR = false;}
      if(oGwDXFfdkY == true){oGwDXFfdkY = false;}
      if(GzfRWzTybI == true){GzfRWzTybI = false;}
      if(NQkXCdDADx == true){NQkXCdDADx = false;}
      if(JkWoGJLbRV == true){JkWoGJLbRV = false;}
      if(PZGtUYxaSU == true){PZGtUYxaSU = false;}
      if(POypDXUYBs == true){POypDXUYBs = false;}
      if(CeZnOUcpKN == true){CeZnOUcpKN = false;}
      if(nrfFrnKpDc == true){nrfFrnKpDc = false;}
      if(gbgigumgki == true){gbgigumgki = false;}
      if(nlaYTkzSfz == true){nlaYTkzSfz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NEWEUQMNWR
{ 
  void cKRIYdDXNQ()
  { 
      bool ETHnFGMWID = false;
      bool GfpHgWxgZL = false;
      bool fwMiAMazZD = false;
      bool JRZNcdyYuK = false;
      bool UdGQorFJND = false;
      bool YnnpBHGYns = false;
      bool eNwFsnGbdD = false;
      bool YXkPpBpwtH = false;
      bool HQlVdVcjMV = false;
      bool WYkCfHgAWA = false;
      bool lcfJeADYzz = false;
      bool RKegkNaZaX = false;
      bool KVPIgzmhji = false;
      bool UpZsUdkbqc = false;
      bool REjMDLtDQR = false;
      bool fGYyoPMWce = false;
      bool NUoQebjkLH = false;
      bool bziyFGlCEU = false;
      bool FiQRCNQbDF = false;
      bool QOzMPxOShb = false;
      string OBJwUAwuIb;
      string xknusPBjdI;
      string aIEMezoCSe;
      string BPkjWWgNnM;
      string rGHQwXkQJN;
      string HgOXEFxxRU;
      string LsbdahzEYW;
      string hmuQPTBmPG;
      string OXsFXTANfQ;
      string YiwTBzdcoO;
      string YgrleTlxHj;
      string EJhKGmzVFG;
      string glXHxzqaPQ;
      string pXxBggfGaE;
      string gDFwMPBkNN;
      string zHXiglIjof;
      string cKhqsfLgdY;
      string HsuBZdfbtg;
      string yFNBQhAOTu;
      string YuRuaVUOCg;
      if(OBJwUAwuIb == YgrleTlxHj){ETHnFGMWID = true;}
      else if(YgrleTlxHj == OBJwUAwuIb){lcfJeADYzz = true;}
      if(xknusPBjdI == EJhKGmzVFG){GfpHgWxgZL = true;}
      else if(EJhKGmzVFG == xknusPBjdI){RKegkNaZaX = true;}
      if(aIEMezoCSe == glXHxzqaPQ){fwMiAMazZD = true;}
      else if(glXHxzqaPQ == aIEMezoCSe){KVPIgzmhji = true;}
      if(BPkjWWgNnM == pXxBggfGaE){JRZNcdyYuK = true;}
      else if(pXxBggfGaE == BPkjWWgNnM){UpZsUdkbqc = true;}
      if(rGHQwXkQJN == gDFwMPBkNN){UdGQorFJND = true;}
      else if(gDFwMPBkNN == rGHQwXkQJN){REjMDLtDQR = true;}
      if(HgOXEFxxRU == zHXiglIjof){YnnpBHGYns = true;}
      else if(zHXiglIjof == HgOXEFxxRU){fGYyoPMWce = true;}
      if(LsbdahzEYW == cKhqsfLgdY){eNwFsnGbdD = true;}
      else if(cKhqsfLgdY == LsbdahzEYW){NUoQebjkLH = true;}
      if(hmuQPTBmPG == HsuBZdfbtg){YXkPpBpwtH = true;}
      if(OXsFXTANfQ == yFNBQhAOTu){HQlVdVcjMV = true;}
      if(YiwTBzdcoO == YuRuaVUOCg){WYkCfHgAWA = true;}
      while(HsuBZdfbtg == hmuQPTBmPG){bziyFGlCEU = true;}
      while(yFNBQhAOTu == yFNBQhAOTu){FiQRCNQbDF = true;}
      while(YuRuaVUOCg == YuRuaVUOCg){QOzMPxOShb = true;}
      if(ETHnFGMWID == true){ETHnFGMWID = false;}
      if(GfpHgWxgZL == true){GfpHgWxgZL = false;}
      if(fwMiAMazZD == true){fwMiAMazZD = false;}
      if(JRZNcdyYuK == true){JRZNcdyYuK = false;}
      if(UdGQorFJND == true){UdGQorFJND = false;}
      if(YnnpBHGYns == true){YnnpBHGYns = false;}
      if(eNwFsnGbdD == true){eNwFsnGbdD = false;}
      if(YXkPpBpwtH == true){YXkPpBpwtH = false;}
      if(HQlVdVcjMV == true){HQlVdVcjMV = false;}
      if(WYkCfHgAWA == true){WYkCfHgAWA = false;}
      if(lcfJeADYzz == true){lcfJeADYzz = false;}
      if(RKegkNaZaX == true){RKegkNaZaX = false;}
      if(KVPIgzmhji == true){KVPIgzmhji = false;}
      if(UpZsUdkbqc == true){UpZsUdkbqc = false;}
      if(REjMDLtDQR == true){REjMDLtDQR = false;}
      if(fGYyoPMWce == true){fGYyoPMWce = false;}
      if(NUoQebjkLH == true){NUoQebjkLH = false;}
      if(bziyFGlCEU == true){bziyFGlCEU = false;}
      if(FiQRCNQbDF == true){FiQRCNQbDF = false;}
      if(QOzMPxOShb == true){QOzMPxOShb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UYQRJWORCK
{ 
  void ncCcyGtXaa()
  { 
      bool aNItutUBkd = false;
      bool BWweoLByoV = false;
      bool zFEkIsCrxg = false;
      bool bIOnXdbBzN = false;
      bool lirHpYlVMS = false;
      bool KsxwEUJXkB = false;
      bool qcDECsHHGK = false;
      bool jAzaiPNxuj = false;
      bool GgedVhKRiC = false;
      bool UDQxWJfmEx = false;
      bool QeOBiKtVNo = false;
      bool HLcBuKxYhT = false;
      bool hpXDpfiBEY = false;
      bool jZrySbRduL = false;
      bool nnEtuIaPCL = false;
      bool MGEkOaGKKD = false;
      bool asRnEgSdhT = false;
      bool rTdWeslcIh = false;
      bool ETysMdVHir = false;
      bool UGSrkuWQpN = false;
      string PIJHWfSFfr;
      string BHeAsRNiDW;
      string sWawVllQPj;
      string nxjGehqnmP;
      string hfbkICFryD;
      string qmzsLrgNkk;
      string sBouDDXXUK;
      string ZYwnnMtonT;
      string gtSMrBxpum;
      string BdDCVgqfgE;
      string dgWmcRqLFz;
      string yqZRDzicCC;
      string GgchJwVsRG;
      string VNIiozWeia;
      string JlkwoJEkyW;
      string yOceyxDodg;
      string wxsycjipcE;
      string bDsbsTugsz;
      string rjuuIHjckq;
      string uhABeMrmSE;
      if(PIJHWfSFfr == dgWmcRqLFz){aNItutUBkd = true;}
      else if(dgWmcRqLFz == PIJHWfSFfr){QeOBiKtVNo = true;}
      if(BHeAsRNiDW == yqZRDzicCC){BWweoLByoV = true;}
      else if(yqZRDzicCC == BHeAsRNiDW){HLcBuKxYhT = true;}
      if(sWawVllQPj == GgchJwVsRG){zFEkIsCrxg = true;}
      else if(GgchJwVsRG == sWawVllQPj){hpXDpfiBEY = true;}
      if(nxjGehqnmP == VNIiozWeia){bIOnXdbBzN = true;}
      else if(VNIiozWeia == nxjGehqnmP){jZrySbRduL = true;}
      if(hfbkICFryD == JlkwoJEkyW){lirHpYlVMS = true;}
      else if(JlkwoJEkyW == hfbkICFryD){nnEtuIaPCL = true;}
      if(qmzsLrgNkk == yOceyxDodg){KsxwEUJXkB = true;}
      else if(yOceyxDodg == qmzsLrgNkk){MGEkOaGKKD = true;}
      if(sBouDDXXUK == wxsycjipcE){qcDECsHHGK = true;}
      else if(wxsycjipcE == sBouDDXXUK){asRnEgSdhT = true;}
      if(ZYwnnMtonT == bDsbsTugsz){jAzaiPNxuj = true;}
      if(gtSMrBxpum == rjuuIHjckq){GgedVhKRiC = true;}
      if(BdDCVgqfgE == uhABeMrmSE){UDQxWJfmEx = true;}
      while(bDsbsTugsz == ZYwnnMtonT){rTdWeslcIh = true;}
      while(rjuuIHjckq == rjuuIHjckq){ETysMdVHir = true;}
      while(uhABeMrmSE == uhABeMrmSE){UGSrkuWQpN = true;}
      if(aNItutUBkd == true){aNItutUBkd = false;}
      if(BWweoLByoV == true){BWweoLByoV = false;}
      if(zFEkIsCrxg == true){zFEkIsCrxg = false;}
      if(bIOnXdbBzN == true){bIOnXdbBzN = false;}
      if(lirHpYlVMS == true){lirHpYlVMS = false;}
      if(KsxwEUJXkB == true){KsxwEUJXkB = false;}
      if(qcDECsHHGK == true){qcDECsHHGK = false;}
      if(jAzaiPNxuj == true){jAzaiPNxuj = false;}
      if(GgedVhKRiC == true){GgedVhKRiC = false;}
      if(UDQxWJfmEx == true){UDQxWJfmEx = false;}
      if(QeOBiKtVNo == true){QeOBiKtVNo = false;}
      if(HLcBuKxYhT == true){HLcBuKxYhT = false;}
      if(hpXDpfiBEY == true){hpXDpfiBEY = false;}
      if(jZrySbRduL == true){jZrySbRduL = false;}
      if(nnEtuIaPCL == true){nnEtuIaPCL = false;}
      if(MGEkOaGKKD == true){MGEkOaGKKD = false;}
      if(asRnEgSdhT == true){asRnEgSdhT = false;}
      if(rTdWeslcIh == true){rTdWeslcIh = false;}
      if(ETysMdVHir == true){ETysMdVHir = false;}
      if(UGSrkuWQpN == true){UGSrkuWQpN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XIKKFVMXEY
{ 
  void kbHQxtCcwM()
  { 
      bool seNiAhWYTd = false;
      bool rBZFkxBEnO = false;
      bool pGUVsQYUhR = false;
      bool UtsuCUciWL = false;
      bool LdYEXusZXz = false;
      bool LCLdtmJrpj = false;
      bool JBqBJxIdDP = false;
      bool UShbCMhQxy = false;
      bool WzxhGRiOBP = false;
      bool LjrlCJlWua = false;
      bool mOWHdrUjbh = false;
      bool EsurMKEItq = false;
      bool OtcmEkZuZr = false;
      bool ZKVWLHcpDN = false;
      bool xylSKRoAZr = false;
      bool FdbDLrliDs = false;
      bool SYKiItXXfF = false;
      bool gOEgsPHJbl = false;
      bool uYVgmwhRKS = false;
      bool VslKtYnDKQ = false;
      string NHuQxzqbFH;
      string byOApiXZxr;
      string ThRwJTxgqX;
      string BBWNKVYtfu;
      string jKEQqqRGJc;
      string HHjXpepyGd;
      string BKkhGabAoT;
      string JctBHIdBFS;
      string BqXNPtQyXe;
      string famBtZYWKQ;
      string PQQoTdMhPg;
      string BornbJmXRL;
      string KccKmhorHh;
      string jHpoCkZhtl;
      string ghhpdqhzZj;
      string mBEyGmnGCk;
      string nTahxsyDkp;
      string jEdfebtlfw;
      string zpSWtiCriP;
      string xTfIxMGzsk;
      if(NHuQxzqbFH == PQQoTdMhPg){seNiAhWYTd = true;}
      else if(PQQoTdMhPg == NHuQxzqbFH){mOWHdrUjbh = true;}
      if(byOApiXZxr == BornbJmXRL){rBZFkxBEnO = true;}
      else if(BornbJmXRL == byOApiXZxr){EsurMKEItq = true;}
      if(ThRwJTxgqX == KccKmhorHh){pGUVsQYUhR = true;}
      else if(KccKmhorHh == ThRwJTxgqX){OtcmEkZuZr = true;}
      if(BBWNKVYtfu == jHpoCkZhtl){UtsuCUciWL = true;}
      else if(jHpoCkZhtl == BBWNKVYtfu){ZKVWLHcpDN = true;}
      if(jKEQqqRGJc == ghhpdqhzZj){LdYEXusZXz = true;}
      else if(ghhpdqhzZj == jKEQqqRGJc){xylSKRoAZr = true;}
      if(HHjXpepyGd == mBEyGmnGCk){LCLdtmJrpj = true;}
      else if(mBEyGmnGCk == HHjXpepyGd){FdbDLrliDs = true;}
      if(BKkhGabAoT == nTahxsyDkp){JBqBJxIdDP = true;}
      else if(nTahxsyDkp == BKkhGabAoT){SYKiItXXfF = true;}
      if(JctBHIdBFS == jEdfebtlfw){UShbCMhQxy = true;}
      if(BqXNPtQyXe == zpSWtiCriP){WzxhGRiOBP = true;}
      if(famBtZYWKQ == xTfIxMGzsk){LjrlCJlWua = true;}
      while(jEdfebtlfw == JctBHIdBFS){gOEgsPHJbl = true;}
      while(zpSWtiCriP == zpSWtiCriP){uYVgmwhRKS = true;}
      while(xTfIxMGzsk == xTfIxMGzsk){VslKtYnDKQ = true;}
      if(seNiAhWYTd == true){seNiAhWYTd = false;}
      if(rBZFkxBEnO == true){rBZFkxBEnO = false;}
      if(pGUVsQYUhR == true){pGUVsQYUhR = false;}
      if(UtsuCUciWL == true){UtsuCUciWL = false;}
      if(LdYEXusZXz == true){LdYEXusZXz = false;}
      if(LCLdtmJrpj == true){LCLdtmJrpj = false;}
      if(JBqBJxIdDP == true){JBqBJxIdDP = false;}
      if(UShbCMhQxy == true){UShbCMhQxy = false;}
      if(WzxhGRiOBP == true){WzxhGRiOBP = false;}
      if(LjrlCJlWua == true){LjrlCJlWua = false;}
      if(mOWHdrUjbh == true){mOWHdrUjbh = false;}
      if(EsurMKEItq == true){EsurMKEItq = false;}
      if(OtcmEkZuZr == true){OtcmEkZuZr = false;}
      if(ZKVWLHcpDN == true){ZKVWLHcpDN = false;}
      if(xylSKRoAZr == true){xylSKRoAZr = false;}
      if(FdbDLrliDs == true){FdbDLrliDs = false;}
      if(SYKiItXXfF == true){SYKiItXXfF = false;}
      if(gOEgsPHJbl == true){gOEgsPHJbl = false;}
      if(uYVgmwhRKS == true){uYVgmwhRKS = false;}
      if(VslKtYnDKQ == true){VslKtYnDKQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QSEKBQILIQ
{ 
  void XzxKLrRoWO()
  { 
      bool zImuPcETkH = false;
      bool uRGegNSCOR = false;
      bool wwMEMsqMuh = false;
      bool ndTLQDBDLI = false;
      bool YJbJZtbiUr = false;
      bool oYVGpDwhhV = false;
      bool krXCTRxtNd = false;
      bool LOqGrmUDeR = false;
      bool RIqDrPHMUN = false;
      bool GSUpWgkYpH = false;
      bool wgUqgagOOD = false;
      bool isDQDcAUKD = false;
      bool JkZAWrsBjL = false;
      bool CwMXVkmAVR = false;
      bool hryRdNPEls = false;
      bool fPOlxLHTTn = false;
      bool gfeCBmfftR = false;
      bool ozzrURmHVJ = false;
      bool coOpelgaZJ = false;
      bool dTfhkCMuQq = false;
      string pVnnVrfdKA;
      string jmswMJdhuK;
      string rjtowjYiim;
      string bQlWtgEJAY;
      string tVDPJJrTBx;
      string YRRiMGayql;
      string TwtXYSBWBe;
      string EUgWPVfdfm;
      string qEglNJzCKn;
      string FFROFxafpq;
      string HVRWrEjuSp;
      string ZwSEtOPIKP;
      string TyLMZzCSRS;
      string uznneVmKtI;
      string YEjTNImNTq;
      string hRVaWJJFws;
      string CRczuaIdZY;
      string aENBpPNrzQ;
      string LozakcdMRU;
      string LhNBFHajYm;
      if(pVnnVrfdKA == HVRWrEjuSp){zImuPcETkH = true;}
      else if(HVRWrEjuSp == pVnnVrfdKA){wgUqgagOOD = true;}
      if(jmswMJdhuK == ZwSEtOPIKP){uRGegNSCOR = true;}
      else if(ZwSEtOPIKP == jmswMJdhuK){isDQDcAUKD = true;}
      if(rjtowjYiim == TyLMZzCSRS){wwMEMsqMuh = true;}
      else if(TyLMZzCSRS == rjtowjYiim){JkZAWrsBjL = true;}
      if(bQlWtgEJAY == uznneVmKtI){ndTLQDBDLI = true;}
      else if(uznneVmKtI == bQlWtgEJAY){CwMXVkmAVR = true;}
      if(tVDPJJrTBx == YEjTNImNTq){YJbJZtbiUr = true;}
      else if(YEjTNImNTq == tVDPJJrTBx){hryRdNPEls = true;}
      if(YRRiMGayql == hRVaWJJFws){oYVGpDwhhV = true;}
      else if(hRVaWJJFws == YRRiMGayql){fPOlxLHTTn = true;}
      if(TwtXYSBWBe == CRczuaIdZY){krXCTRxtNd = true;}
      else if(CRczuaIdZY == TwtXYSBWBe){gfeCBmfftR = true;}
      if(EUgWPVfdfm == aENBpPNrzQ){LOqGrmUDeR = true;}
      if(qEglNJzCKn == LozakcdMRU){RIqDrPHMUN = true;}
      if(FFROFxafpq == LhNBFHajYm){GSUpWgkYpH = true;}
      while(aENBpPNrzQ == EUgWPVfdfm){ozzrURmHVJ = true;}
      while(LozakcdMRU == LozakcdMRU){coOpelgaZJ = true;}
      while(LhNBFHajYm == LhNBFHajYm){dTfhkCMuQq = true;}
      if(zImuPcETkH == true){zImuPcETkH = false;}
      if(uRGegNSCOR == true){uRGegNSCOR = false;}
      if(wwMEMsqMuh == true){wwMEMsqMuh = false;}
      if(ndTLQDBDLI == true){ndTLQDBDLI = false;}
      if(YJbJZtbiUr == true){YJbJZtbiUr = false;}
      if(oYVGpDwhhV == true){oYVGpDwhhV = false;}
      if(krXCTRxtNd == true){krXCTRxtNd = false;}
      if(LOqGrmUDeR == true){LOqGrmUDeR = false;}
      if(RIqDrPHMUN == true){RIqDrPHMUN = false;}
      if(GSUpWgkYpH == true){GSUpWgkYpH = false;}
      if(wgUqgagOOD == true){wgUqgagOOD = false;}
      if(isDQDcAUKD == true){isDQDcAUKD = false;}
      if(JkZAWrsBjL == true){JkZAWrsBjL = false;}
      if(CwMXVkmAVR == true){CwMXVkmAVR = false;}
      if(hryRdNPEls == true){hryRdNPEls = false;}
      if(fPOlxLHTTn == true){fPOlxLHTTn = false;}
      if(gfeCBmfftR == true){gfeCBmfftR = false;}
      if(ozzrURmHVJ == true){ozzrURmHVJ = false;}
      if(coOpelgaZJ == true){coOpelgaZJ = false;}
      if(dTfhkCMuQq == true){dTfhkCMuQq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QKBMJOXMHK
{ 
  void lccfHQZXpj()
  { 
      bool dkqtdCnyNE = false;
      bool oWfufwnqKK = false;
      bool eOihwqHjAZ = false;
      bool IALJeQnkaI = false;
      bool nPGHUKilEi = false;
      bool YlJYIOBIxm = false;
      bool tExmunLVPP = false;
      bool HDPBVOHbNl = false;
      bool HVeQBWqmAP = false;
      bool PemmOjRSMf = false;
      bool zMVobUVHCs = false;
      bool HYuLeXYflY = false;
      bool xXVAzbQbml = false;
      bool xoPgmuApof = false;
      bool AijHIpjbIp = false;
      bool KkfniaqUoz = false;
      bool EsUQwRJNXj = false;
      bool XhqGXNnOrI = false;
      bool rnTwaLJbyM = false;
      bool DeBoaGOSKp = false;
      string WkqdIJyfpH;
      string zUXYxtIbFQ;
      string BUnlcpLQJC;
      string hXzGXMixUg;
      string ySHwenDKIa;
      string DdKnIBwEAR;
      string yhVmZaUQBk;
      string LLGXSiNrGn;
      string mAIhzENKxV;
      string PdwDhQwTWE;
      string TlIXPqWlVZ;
      string nExMeyZmnU;
      string NJTeUhPDpB;
      string ltVCTArjSH;
      string ganXhLfjXj;
      string qIeBqKScDh;
      string bTwUnthurd;
      string FoUfmmUuxI;
      string BfeFKcOTLJ;
      string gOgkfNdTjn;
      if(WkqdIJyfpH == TlIXPqWlVZ){dkqtdCnyNE = true;}
      else if(TlIXPqWlVZ == WkqdIJyfpH){zMVobUVHCs = true;}
      if(zUXYxtIbFQ == nExMeyZmnU){oWfufwnqKK = true;}
      else if(nExMeyZmnU == zUXYxtIbFQ){HYuLeXYflY = true;}
      if(BUnlcpLQJC == NJTeUhPDpB){eOihwqHjAZ = true;}
      else if(NJTeUhPDpB == BUnlcpLQJC){xXVAzbQbml = true;}
      if(hXzGXMixUg == ltVCTArjSH){IALJeQnkaI = true;}
      else if(ltVCTArjSH == hXzGXMixUg){xoPgmuApof = true;}
      if(ySHwenDKIa == ganXhLfjXj){nPGHUKilEi = true;}
      else if(ganXhLfjXj == ySHwenDKIa){AijHIpjbIp = true;}
      if(DdKnIBwEAR == qIeBqKScDh){YlJYIOBIxm = true;}
      else if(qIeBqKScDh == DdKnIBwEAR){KkfniaqUoz = true;}
      if(yhVmZaUQBk == bTwUnthurd){tExmunLVPP = true;}
      else if(bTwUnthurd == yhVmZaUQBk){EsUQwRJNXj = true;}
      if(LLGXSiNrGn == FoUfmmUuxI){HDPBVOHbNl = true;}
      if(mAIhzENKxV == BfeFKcOTLJ){HVeQBWqmAP = true;}
      if(PdwDhQwTWE == gOgkfNdTjn){PemmOjRSMf = true;}
      while(FoUfmmUuxI == LLGXSiNrGn){XhqGXNnOrI = true;}
      while(BfeFKcOTLJ == BfeFKcOTLJ){rnTwaLJbyM = true;}
      while(gOgkfNdTjn == gOgkfNdTjn){DeBoaGOSKp = true;}
      if(dkqtdCnyNE == true){dkqtdCnyNE = false;}
      if(oWfufwnqKK == true){oWfufwnqKK = false;}
      if(eOihwqHjAZ == true){eOihwqHjAZ = false;}
      if(IALJeQnkaI == true){IALJeQnkaI = false;}
      if(nPGHUKilEi == true){nPGHUKilEi = false;}
      if(YlJYIOBIxm == true){YlJYIOBIxm = false;}
      if(tExmunLVPP == true){tExmunLVPP = false;}
      if(HDPBVOHbNl == true){HDPBVOHbNl = false;}
      if(HVeQBWqmAP == true){HVeQBWqmAP = false;}
      if(PemmOjRSMf == true){PemmOjRSMf = false;}
      if(zMVobUVHCs == true){zMVobUVHCs = false;}
      if(HYuLeXYflY == true){HYuLeXYflY = false;}
      if(xXVAzbQbml == true){xXVAzbQbml = false;}
      if(xoPgmuApof == true){xoPgmuApof = false;}
      if(AijHIpjbIp == true){AijHIpjbIp = false;}
      if(KkfniaqUoz == true){KkfniaqUoz = false;}
      if(EsUQwRJNXj == true){EsUQwRJNXj = false;}
      if(XhqGXNnOrI == true){XhqGXNnOrI = false;}
      if(rnTwaLJbyM == true){rnTwaLJbyM = false;}
      if(DeBoaGOSKp == true){DeBoaGOSKp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DULJAWVWBY
{ 
  void GYrbhdLHrR()
  { 
      bool IFJGXCnOgQ = false;
      bool QjoJcqoVBr = false;
      bool MMFShPQeqW = false;
      bool EddNszMArZ = false;
      bool KFKSkPrucM = false;
      bool YfkojwzpYI = false;
      bool kIXJMlFaQd = false;
      bool dndbhHBmhR = false;
      bool WVCdyYsndw = false;
      bool zWajnBgBGy = false;
      bool JRdyijBIHc = false;
      bool tMIGkPGsKm = false;
      bool sRwTeHNtmf = false;
      bool ZAgiIFqDuN = false;
      bool WjfBClNTyY = false;
      bool unpSFrUKTb = false;
      bool WHVbDtfZyf = false;
      bool XCyxQJkuRr = false;
      bool ssuOjkJNcQ = false;
      bool kgiSpPNExH = false;
      string ZPiqxdlzRD;
      string bQRaAPPidD;
      string bOfHpqgHBZ;
      string GSmlzKVhWu;
      string pANJdrNNPc;
      string uEGrsLjbBG;
      string weyqxIceao;
      string tgMiMaAVdy;
      string dSqXeCMurn;
      string asgQyLBWMU;
      string OhmZiNrWeR;
      string KNyDccmaMu;
      string whlmOAAukB;
      string ZdJIiufQoQ;
      string JoQZcMudnU;
      string YZJRYguzLh;
      string NwldrfEoTg;
      string wWlukHQLKB;
      string EWHPbzTqjB;
      string zgFGDNCmhw;
      if(ZPiqxdlzRD == OhmZiNrWeR){IFJGXCnOgQ = true;}
      else if(OhmZiNrWeR == ZPiqxdlzRD){JRdyijBIHc = true;}
      if(bQRaAPPidD == KNyDccmaMu){QjoJcqoVBr = true;}
      else if(KNyDccmaMu == bQRaAPPidD){tMIGkPGsKm = true;}
      if(bOfHpqgHBZ == whlmOAAukB){MMFShPQeqW = true;}
      else if(whlmOAAukB == bOfHpqgHBZ){sRwTeHNtmf = true;}
      if(GSmlzKVhWu == ZdJIiufQoQ){EddNszMArZ = true;}
      else if(ZdJIiufQoQ == GSmlzKVhWu){ZAgiIFqDuN = true;}
      if(pANJdrNNPc == JoQZcMudnU){KFKSkPrucM = true;}
      else if(JoQZcMudnU == pANJdrNNPc){WjfBClNTyY = true;}
      if(uEGrsLjbBG == YZJRYguzLh){YfkojwzpYI = true;}
      else if(YZJRYguzLh == uEGrsLjbBG){unpSFrUKTb = true;}
      if(weyqxIceao == NwldrfEoTg){kIXJMlFaQd = true;}
      else if(NwldrfEoTg == weyqxIceao){WHVbDtfZyf = true;}
      if(tgMiMaAVdy == wWlukHQLKB){dndbhHBmhR = true;}
      if(dSqXeCMurn == EWHPbzTqjB){WVCdyYsndw = true;}
      if(asgQyLBWMU == zgFGDNCmhw){zWajnBgBGy = true;}
      while(wWlukHQLKB == tgMiMaAVdy){XCyxQJkuRr = true;}
      while(EWHPbzTqjB == EWHPbzTqjB){ssuOjkJNcQ = true;}
      while(zgFGDNCmhw == zgFGDNCmhw){kgiSpPNExH = true;}
      if(IFJGXCnOgQ == true){IFJGXCnOgQ = false;}
      if(QjoJcqoVBr == true){QjoJcqoVBr = false;}
      if(MMFShPQeqW == true){MMFShPQeqW = false;}
      if(EddNszMArZ == true){EddNszMArZ = false;}
      if(KFKSkPrucM == true){KFKSkPrucM = false;}
      if(YfkojwzpYI == true){YfkojwzpYI = false;}
      if(kIXJMlFaQd == true){kIXJMlFaQd = false;}
      if(dndbhHBmhR == true){dndbhHBmhR = false;}
      if(WVCdyYsndw == true){WVCdyYsndw = false;}
      if(zWajnBgBGy == true){zWajnBgBGy = false;}
      if(JRdyijBIHc == true){JRdyijBIHc = false;}
      if(tMIGkPGsKm == true){tMIGkPGsKm = false;}
      if(sRwTeHNtmf == true){sRwTeHNtmf = false;}
      if(ZAgiIFqDuN == true){ZAgiIFqDuN = false;}
      if(WjfBClNTyY == true){WjfBClNTyY = false;}
      if(unpSFrUKTb == true){unpSFrUKTb = false;}
      if(WHVbDtfZyf == true){WHVbDtfZyf = false;}
      if(XCyxQJkuRr == true){XCyxQJkuRr = false;}
      if(ssuOjkJNcQ == true){ssuOjkJNcQ = false;}
      if(kgiSpPNExH == true){kgiSpPNExH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UNAYBIMQHT
{ 
  void Umulphseit()
  { 
      bool PjqIRSQKhH = false;
      bool mkcApEufiY = false;
      bool JChCwQLoNq = false;
      bool pSqIzWBIDZ = false;
      bool LPXxIofVAL = false;
      bool IhTFNNBoLA = false;
      bool HbwpRTtTBT = false;
      bool DlbIMsejtH = false;
      bool konBiHzktl = false;
      bool ULwCSjTgfn = false;
      bool tLUgIVFKsT = false;
      bool hRuEPRmtGJ = false;
      bool UIYOzqpZpc = false;
      bool ZxEFMYTHsN = false;
      bool BnraDDQrmA = false;
      bool wYZVSllGhQ = false;
      bool ffUPtjNoqp = false;
      bool xfAsHfQyKu = false;
      bool axlofAWhma = false;
      bool mNYchVTbfT = false;
      string NEgDCENqin;
      string tCguemlGlG;
      string yRqeiIAyDx;
      string HswYCbeMbn;
      string mGTUgRSnGk;
      string EkNrRwMCUt;
      string EOnlgAFIrC;
      string HZdxTqxVxQ;
      string pMrSrWfDGF;
      string OcrhjXShmf;
      string LJuEcdHPXZ;
      string zpEDDqWVsK;
      string UBCmneguNu;
      string YPiQFgRmoN;
      string OPffGXXoer;
      string BwocLJHIQx;
      string xLBcBjHmxW;
      string ZifeuEVVfP;
      string HrQVsbZFFu;
      string ZIWqQDODeW;
      if(NEgDCENqin == LJuEcdHPXZ){PjqIRSQKhH = true;}
      else if(LJuEcdHPXZ == NEgDCENqin){tLUgIVFKsT = true;}
      if(tCguemlGlG == zpEDDqWVsK){mkcApEufiY = true;}
      else if(zpEDDqWVsK == tCguemlGlG){hRuEPRmtGJ = true;}
      if(yRqeiIAyDx == UBCmneguNu){JChCwQLoNq = true;}
      else if(UBCmneguNu == yRqeiIAyDx){UIYOzqpZpc = true;}
      if(HswYCbeMbn == YPiQFgRmoN){pSqIzWBIDZ = true;}
      else if(YPiQFgRmoN == HswYCbeMbn){ZxEFMYTHsN = true;}
      if(mGTUgRSnGk == OPffGXXoer){LPXxIofVAL = true;}
      else if(OPffGXXoer == mGTUgRSnGk){BnraDDQrmA = true;}
      if(EkNrRwMCUt == BwocLJHIQx){IhTFNNBoLA = true;}
      else if(BwocLJHIQx == EkNrRwMCUt){wYZVSllGhQ = true;}
      if(EOnlgAFIrC == xLBcBjHmxW){HbwpRTtTBT = true;}
      else if(xLBcBjHmxW == EOnlgAFIrC){ffUPtjNoqp = true;}
      if(HZdxTqxVxQ == ZifeuEVVfP){DlbIMsejtH = true;}
      if(pMrSrWfDGF == HrQVsbZFFu){konBiHzktl = true;}
      if(OcrhjXShmf == ZIWqQDODeW){ULwCSjTgfn = true;}
      while(ZifeuEVVfP == HZdxTqxVxQ){xfAsHfQyKu = true;}
      while(HrQVsbZFFu == HrQVsbZFFu){axlofAWhma = true;}
      while(ZIWqQDODeW == ZIWqQDODeW){mNYchVTbfT = true;}
      if(PjqIRSQKhH == true){PjqIRSQKhH = false;}
      if(mkcApEufiY == true){mkcApEufiY = false;}
      if(JChCwQLoNq == true){JChCwQLoNq = false;}
      if(pSqIzWBIDZ == true){pSqIzWBIDZ = false;}
      if(LPXxIofVAL == true){LPXxIofVAL = false;}
      if(IhTFNNBoLA == true){IhTFNNBoLA = false;}
      if(HbwpRTtTBT == true){HbwpRTtTBT = false;}
      if(DlbIMsejtH == true){DlbIMsejtH = false;}
      if(konBiHzktl == true){konBiHzktl = false;}
      if(ULwCSjTgfn == true){ULwCSjTgfn = false;}
      if(tLUgIVFKsT == true){tLUgIVFKsT = false;}
      if(hRuEPRmtGJ == true){hRuEPRmtGJ = false;}
      if(UIYOzqpZpc == true){UIYOzqpZpc = false;}
      if(ZxEFMYTHsN == true){ZxEFMYTHsN = false;}
      if(BnraDDQrmA == true){BnraDDQrmA = false;}
      if(wYZVSllGhQ == true){wYZVSllGhQ = false;}
      if(ffUPtjNoqp == true){ffUPtjNoqp = false;}
      if(xfAsHfQyKu == true){xfAsHfQyKu = false;}
      if(axlofAWhma == true){axlofAWhma = false;}
      if(mNYchVTbfT == true){mNYchVTbfT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OHTLUTBTIL
{ 
  void GZClRfONQk()
  { 
      bool sinNKuKWkS = false;
      bool DhisYaqqLX = false;
      bool swBiMocVGs = false;
      bool FdwNwuwKJd = false;
      bool GyWWyYdRkz = false;
      bool EDfQgwgEAV = false;
      bool RnQrNYkVxd = false;
      bool dfggQuZdjn = false;
      bool KKjHnByefz = false;
      bool NqKnMRheJY = false;
      bool mIUHUYVyzl = false;
      bool WDTMKHDIDL = false;
      bool aFoxPmVrUy = false;
      bool MtULACpcmP = false;
      bool eAetcKWydE = false;
      bool NYaxygTWqh = false;
      bool DccBYbhILH = false;
      bool QaVnfaatUF = false;
      bool PXOPjmSXNT = false;
      bool hTkELCWdVB = false;
      string VSLGYLMYqM;
      string wYAWLrsBFA;
      string rlTZtapMIU;
      string ejAMOlMxWV;
      string UAqInuUHwm;
      string PyfbnjzlLy;
      string VAPVgMXmHZ;
      string eudiertKkz;
      string GiQVEfEYYe;
      string malYAUjUbb;
      string XgzVHUUwww;
      string onAMrljtQA;
      string IyOcmEJFiK;
      string HZiJaYitNj;
      string LHccoyZYfN;
      string kpDaTYSVhD;
      string KPMknPFqkS;
      string CoffoAVkmo;
      string djYUZQVIpC;
      string GMLKZwuqnZ;
      if(VSLGYLMYqM == XgzVHUUwww){sinNKuKWkS = true;}
      else if(XgzVHUUwww == VSLGYLMYqM){mIUHUYVyzl = true;}
      if(wYAWLrsBFA == onAMrljtQA){DhisYaqqLX = true;}
      else if(onAMrljtQA == wYAWLrsBFA){WDTMKHDIDL = true;}
      if(rlTZtapMIU == IyOcmEJFiK){swBiMocVGs = true;}
      else if(IyOcmEJFiK == rlTZtapMIU){aFoxPmVrUy = true;}
      if(ejAMOlMxWV == HZiJaYitNj){FdwNwuwKJd = true;}
      else if(HZiJaYitNj == ejAMOlMxWV){MtULACpcmP = true;}
      if(UAqInuUHwm == LHccoyZYfN){GyWWyYdRkz = true;}
      else if(LHccoyZYfN == UAqInuUHwm){eAetcKWydE = true;}
      if(PyfbnjzlLy == kpDaTYSVhD){EDfQgwgEAV = true;}
      else if(kpDaTYSVhD == PyfbnjzlLy){NYaxygTWqh = true;}
      if(VAPVgMXmHZ == KPMknPFqkS){RnQrNYkVxd = true;}
      else if(KPMknPFqkS == VAPVgMXmHZ){DccBYbhILH = true;}
      if(eudiertKkz == CoffoAVkmo){dfggQuZdjn = true;}
      if(GiQVEfEYYe == djYUZQVIpC){KKjHnByefz = true;}
      if(malYAUjUbb == GMLKZwuqnZ){NqKnMRheJY = true;}
      while(CoffoAVkmo == eudiertKkz){QaVnfaatUF = true;}
      while(djYUZQVIpC == djYUZQVIpC){PXOPjmSXNT = true;}
      while(GMLKZwuqnZ == GMLKZwuqnZ){hTkELCWdVB = true;}
      if(sinNKuKWkS == true){sinNKuKWkS = false;}
      if(DhisYaqqLX == true){DhisYaqqLX = false;}
      if(swBiMocVGs == true){swBiMocVGs = false;}
      if(FdwNwuwKJd == true){FdwNwuwKJd = false;}
      if(GyWWyYdRkz == true){GyWWyYdRkz = false;}
      if(EDfQgwgEAV == true){EDfQgwgEAV = false;}
      if(RnQrNYkVxd == true){RnQrNYkVxd = false;}
      if(dfggQuZdjn == true){dfggQuZdjn = false;}
      if(KKjHnByefz == true){KKjHnByefz = false;}
      if(NqKnMRheJY == true){NqKnMRheJY = false;}
      if(mIUHUYVyzl == true){mIUHUYVyzl = false;}
      if(WDTMKHDIDL == true){WDTMKHDIDL = false;}
      if(aFoxPmVrUy == true){aFoxPmVrUy = false;}
      if(MtULACpcmP == true){MtULACpcmP = false;}
      if(eAetcKWydE == true){eAetcKWydE = false;}
      if(NYaxygTWqh == true){NYaxygTWqh = false;}
      if(DccBYbhILH == true){DccBYbhILH = false;}
      if(QaVnfaatUF == true){QaVnfaatUF = false;}
      if(PXOPjmSXNT == true){PXOPjmSXNT = false;}
      if(hTkELCWdVB == true){hTkELCWdVB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GIMNBZTBIA
{ 
  void lRgMSmsCOU()
  { 
      bool HGaKNfUFGj = false;
      bool fujofZUFTW = false;
      bool IHIiIXcCMC = false;
      bool MfynKqcHDR = false;
      bool tWuhVNSeXk = false;
      bool NwRBDAyrBp = false;
      bool CRrDXzxuen = false;
      bool xMCBbkLZMu = false;
      bool FxeboPOwkK = false;
      bool sjFNPberJW = false;
      bool PWAimAsPYS = false;
      bool nXeGjEmPOH = false;
      bool jAKUuMGnlA = false;
      bool GTQpeixwnn = false;
      bool WyXRVUEzcK = false;
      bool oOdBlPLfma = false;
      bool tFdYMUHnaB = false;
      bool HqbZkkcsyZ = false;
      bool HGLaKqpOEP = false;
      bool WRINtRUyFA = false;
      string ZyZGDfGflS;
      string enfNSXJGAd;
      string ukCeDlsMCo;
      string HoVPbPTynq;
      string yrnKbkNUsM;
      string FClZenuuCR;
      string msdxLpRPlD;
      string DLSJfDxrDS;
      string XXSpiFCwjn;
      string TYuWDENqyl;
      string SxipIticsa;
      string qDqjsOamNG;
      string mUfxiePwFb;
      string oFsQzanbgo;
      string VYDJxQgLcn;
      string dacqyxRkHd;
      string dmWRkkJajR;
      string ayGXkNRVAR;
      string xESRxObCSB;
      string JCUDKhBkXL;
      if(ZyZGDfGflS == SxipIticsa){HGaKNfUFGj = true;}
      else if(SxipIticsa == ZyZGDfGflS){PWAimAsPYS = true;}
      if(enfNSXJGAd == qDqjsOamNG){fujofZUFTW = true;}
      else if(qDqjsOamNG == enfNSXJGAd){nXeGjEmPOH = true;}
      if(ukCeDlsMCo == mUfxiePwFb){IHIiIXcCMC = true;}
      else if(mUfxiePwFb == ukCeDlsMCo){jAKUuMGnlA = true;}
      if(HoVPbPTynq == oFsQzanbgo){MfynKqcHDR = true;}
      else if(oFsQzanbgo == HoVPbPTynq){GTQpeixwnn = true;}
      if(yrnKbkNUsM == VYDJxQgLcn){tWuhVNSeXk = true;}
      else if(VYDJxQgLcn == yrnKbkNUsM){WyXRVUEzcK = true;}
      if(FClZenuuCR == dacqyxRkHd){NwRBDAyrBp = true;}
      else if(dacqyxRkHd == FClZenuuCR){oOdBlPLfma = true;}
      if(msdxLpRPlD == dmWRkkJajR){CRrDXzxuen = true;}
      else if(dmWRkkJajR == msdxLpRPlD){tFdYMUHnaB = true;}
      if(DLSJfDxrDS == ayGXkNRVAR){xMCBbkLZMu = true;}
      if(XXSpiFCwjn == xESRxObCSB){FxeboPOwkK = true;}
      if(TYuWDENqyl == JCUDKhBkXL){sjFNPberJW = true;}
      while(ayGXkNRVAR == DLSJfDxrDS){HqbZkkcsyZ = true;}
      while(xESRxObCSB == xESRxObCSB){HGLaKqpOEP = true;}
      while(JCUDKhBkXL == JCUDKhBkXL){WRINtRUyFA = true;}
      if(HGaKNfUFGj == true){HGaKNfUFGj = false;}
      if(fujofZUFTW == true){fujofZUFTW = false;}
      if(IHIiIXcCMC == true){IHIiIXcCMC = false;}
      if(MfynKqcHDR == true){MfynKqcHDR = false;}
      if(tWuhVNSeXk == true){tWuhVNSeXk = false;}
      if(NwRBDAyrBp == true){NwRBDAyrBp = false;}
      if(CRrDXzxuen == true){CRrDXzxuen = false;}
      if(xMCBbkLZMu == true){xMCBbkLZMu = false;}
      if(FxeboPOwkK == true){FxeboPOwkK = false;}
      if(sjFNPberJW == true){sjFNPberJW = false;}
      if(PWAimAsPYS == true){PWAimAsPYS = false;}
      if(nXeGjEmPOH == true){nXeGjEmPOH = false;}
      if(jAKUuMGnlA == true){jAKUuMGnlA = false;}
      if(GTQpeixwnn == true){GTQpeixwnn = false;}
      if(WyXRVUEzcK == true){WyXRVUEzcK = false;}
      if(oOdBlPLfma == true){oOdBlPLfma = false;}
      if(tFdYMUHnaB == true){tFdYMUHnaB = false;}
      if(HqbZkkcsyZ == true){HqbZkkcsyZ = false;}
      if(HGLaKqpOEP == true){HGLaKqpOEP = false;}
      if(WRINtRUyFA == true){WRINtRUyFA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCPGDSDTTQ
{ 
  void YnhMXmsYas()
  { 
      bool XHjOPTEZhA = false;
      bool qjOCzupDTW = false;
      bool yPQfrotJwO = false;
      bool IrAVjpFlgg = false;
      bool gzlWtaammJ = false;
      bool KBhJRIqEWa = false;
      bool ZtcTqyjrSJ = false;
      bool oEVlpydtlQ = false;
      bool NGWlEHJpDa = false;
      bool zAPGGlVSeu = false;
      bool qiTdTGeuTT = false;
      bool ewSFMSXqOj = false;
      bool ntoqJonPeD = false;
      bool cKOpZelsSy = false;
      bool bNWjwChJsn = false;
      bool OeDtGwscTe = false;
      bool RPPPqThceg = false;
      bool fdXQHZXEuG = false;
      bool GdVqoxHUic = false;
      bool kJYnfMxGsb = false;
      string hKJwMJqCqu;
      string TWQgEejQKu;
      string UtnRjOYcof;
      string iBLHxeOCxB;
      string CxcRyLxIAJ;
      string LeCRUnWrLy;
      string kNMLLRKJiY;
      string QhTJrXQWSX;
      string QPceTEytlJ;
      string IVpzQnjRFg;
      string BnZbsdLsYw;
      string WAZngUkhqH;
      string SPWYPtrTrE;
      string mzQkWcpBkp;
      string rFVpmHwCSu;
      string DBaxNkRALy;
      string kqATIWinRD;
      string ejxAPNtglI;
      string ypBxAlYTWk;
      string LopmEAEBgP;
      if(hKJwMJqCqu == BnZbsdLsYw){XHjOPTEZhA = true;}
      else if(BnZbsdLsYw == hKJwMJqCqu){qiTdTGeuTT = true;}
      if(TWQgEejQKu == WAZngUkhqH){qjOCzupDTW = true;}
      else if(WAZngUkhqH == TWQgEejQKu){ewSFMSXqOj = true;}
      if(UtnRjOYcof == SPWYPtrTrE){yPQfrotJwO = true;}
      else if(SPWYPtrTrE == UtnRjOYcof){ntoqJonPeD = true;}
      if(iBLHxeOCxB == mzQkWcpBkp){IrAVjpFlgg = true;}
      else if(mzQkWcpBkp == iBLHxeOCxB){cKOpZelsSy = true;}
      if(CxcRyLxIAJ == rFVpmHwCSu){gzlWtaammJ = true;}
      else if(rFVpmHwCSu == CxcRyLxIAJ){bNWjwChJsn = true;}
      if(LeCRUnWrLy == DBaxNkRALy){KBhJRIqEWa = true;}
      else if(DBaxNkRALy == LeCRUnWrLy){OeDtGwscTe = true;}
      if(kNMLLRKJiY == kqATIWinRD){ZtcTqyjrSJ = true;}
      else if(kqATIWinRD == kNMLLRKJiY){RPPPqThceg = true;}
      if(QhTJrXQWSX == ejxAPNtglI){oEVlpydtlQ = true;}
      if(QPceTEytlJ == ypBxAlYTWk){NGWlEHJpDa = true;}
      if(IVpzQnjRFg == LopmEAEBgP){zAPGGlVSeu = true;}
      while(ejxAPNtglI == QhTJrXQWSX){fdXQHZXEuG = true;}
      while(ypBxAlYTWk == ypBxAlYTWk){GdVqoxHUic = true;}
      while(LopmEAEBgP == LopmEAEBgP){kJYnfMxGsb = true;}
      if(XHjOPTEZhA == true){XHjOPTEZhA = false;}
      if(qjOCzupDTW == true){qjOCzupDTW = false;}
      if(yPQfrotJwO == true){yPQfrotJwO = false;}
      if(IrAVjpFlgg == true){IrAVjpFlgg = false;}
      if(gzlWtaammJ == true){gzlWtaammJ = false;}
      if(KBhJRIqEWa == true){KBhJRIqEWa = false;}
      if(ZtcTqyjrSJ == true){ZtcTqyjrSJ = false;}
      if(oEVlpydtlQ == true){oEVlpydtlQ = false;}
      if(NGWlEHJpDa == true){NGWlEHJpDa = false;}
      if(zAPGGlVSeu == true){zAPGGlVSeu = false;}
      if(qiTdTGeuTT == true){qiTdTGeuTT = false;}
      if(ewSFMSXqOj == true){ewSFMSXqOj = false;}
      if(ntoqJonPeD == true){ntoqJonPeD = false;}
      if(cKOpZelsSy == true){cKOpZelsSy = false;}
      if(bNWjwChJsn == true){bNWjwChJsn = false;}
      if(OeDtGwscTe == true){OeDtGwscTe = false;}
      if(RPPPqThceg == true){RPPPqThceg = false;}
      if(fdXQHZXEuG == true){fdXQHZXEuG = false;}
      if(GdVqoxHUic == true){GdVqoxHUic = false;}
      if(kJYnfMxGsb == true){kJYnfMxGsb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SLOGXLFAVX
{ 
  void JPJdHZLSca()
  { 
      bool wzREeJSnZo = false;
      bool qicaBAdned = false;
      bool luOZQukeAD = false;
      bool hVNzmphbtR = false;
      bool yzsZUAYMoX = false;
      bool jaWmOBkqnj = false;
      bool XnnWHUUcmK = false;
      bool RBtMflBoEP = false;
      bool WYobTHyajl = false;
      bool FpnKsKLVRA = false;
      bool fuYeFifKHc = false;
      bool zwlXMzzLDA = false;
      bool WtsBFaMiSU = false;
      bool afWEjbzKWk = false;
      bool anSHmJEPxt = false;
      bool LzSRckBXZd = false;
      bool VxqlBTYgnk = false;
      bool AnoRZhalOu = false;
      bool WwlYJaMFbz = false;
      bool ZajrOdwgFS = false;
      string SCjVmcQtbY;
      string fWhHgkgJZA;
      string zljpgdPnqE;
      string NOMWgCFIPS;
      string hxercHUfkt;
      string cqWjFgRtoJ;
      string NbDWLQJLae;
      string fXsHRBHrNZ;
      string IjDxbVrbRz;
      string jKTGFGtHgL;
      string xJEFNExPSD;
      string YZfOAcXFuo;
      string YhtatUEmBL;
      string GzKCbzeyiX;
      string XbJNZKdEFb;
      string ioLqlPOdKr;
      string zKNHwZOdmB;
      string xYVXQwXfAj;
      string pzgYbRmTPM;
      string jBmqXNOCRA;
      if(SCjVmcQtbY == xJEFNExPSD){wzREeJSnZo = true;}
      else if(xJEFNExPSD == SCjVmcQtbY){fuYeFifKHc = true;}
      if(fWhHgkgJZA == YZfOAcXFuo){qicaBAdned = true;}
      else if(YZfOAcXFuo == fWhHgkgJZA){zwlXMzzLDA = true;}
      if(zljpgdPnqE == YhtatUEmBL){luOZQukeAD = true;}
      else if(YhtatUEmBL == zljpgdPnqE){WtsBFaMiSU = true;}
      if(NOMWgCFIPS == GzKCbzeyiX){hVNzmphbtR = true;}
      else if(GzKCbzeyiX == NOMWgCFIPS){afWEjbzKWk = true;}
      if(hxercHUfkt == XbJNZKdEFb){yzsZUAYMoX = true;}
      else if(XbJNZKdEFb == hxercHUfkt){anSHmJEPxt = true;}
      if(cqWjFgRtoJ == ioLqlPOdKr){jaWmOBkqnj = true;}
      else if(ioLqlPOdKr == cqWjFgRtoJ){LzSRckBXZd = true;}
      if(NbDWLQJLae == zKNHwZOdmB){XnnWHUUcmK = true;}
      else if(zKNHwZOdmB == NbDWLQJLae){VxqlBTYgnk = true;}
      if(fXsHRBHrNZ == xYVXQwXfAj){RBtMflBoEP = true;}
      if(IjDxbVrbRz == pzgYbRmTPM){WYobTHyajl = true;}
      if(jKTGFGtHgL == jBmqXNOCRA){FpnKsKLVRA = true;}
      while(xYVXQwXfAj == fXsHRBHrNZ){AnoRZhalOu = true;}
      while(pzgYbRmTPM == pzgYbRmTPM){WwlYJaMFbz = true;}
      while(jBmqXNOCRA == jBmqXNOCRA){ZajrOdwgFS = true;}
      if(wzREeJSnZo == true){wzREeJSnZo = false;}
      if(qicaBAdned == true){qicaBAdned = false;}
      if(luOZQukeAD == true){luOZQukeAD = false;}
      if(hVNzmphbtR == true){hVNzmphbtR = false;}
      if(yzsZUAYMoX == true){yzsZUAYMoX = false;}
      if(jaWmOBkqnj == true){jaWmOBkqnj = false;}
      if(XnnWHUUcmK == true){XnnWHUUcmK = false;}
      if(RBtMflBoEP == true){RBtMflBoEP = false;}
      if(WYobTHyajl == true){WYobTHyajl = false;}
      if(FpnKsKLVRA == true){FpnKsKLVRA = false;}
      if(fuYeFifKHc == true){fuYeFifKHc = false;}
      if(zwlXMzzLDA == true){zwlXMzzLDA = false;}
      if(WtsBFaMiSU == true){WtsBFaMiSU = false;}
      if(afWEjbzKWk == true){afWEjbzKWk = false;}
      if(anSHmJEPxt == true){anSHmJEPxt = false;}
      if(LzSRckBXZd == true){LzSRckBXZd = false;}
      if(VxqlBTYgnk == true){VxqlBTYgnk = false;}
      if(AnoRZhalOu == true){AnoRZhalOu = false;}
      if(WwlYJaMFbz == true){WwlYJaMFbz = false;}
      if(ZajrOdwgFS == true){ZajrOdwgFS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RHGPMODRJX
{ 
  void rWtBWLfuFf()
  { 
      bool VeujMTnVnx = false;
      bool bzJxgAgGbz = false;
      bool FjhgnbdqeQ = false;
      bool RqwNbSCiia = false;
      bool TMKsTNtxjE = false;
      bool OByVRkwOwj = false;
      bool pwqWfkCuVN = false;
      bool yyWAfsYoMa = false;
      bool hgHZCPsaup = false;
      bool VnmzkWUmNi = false;
      bool KyaVGQexoY = false;
      bool LHBUBIoQUP = false;
      bool rbzfqKLXPI = false;
      bool XlbdPiFkTk = false;
      bool kukWdOlRxb = false;
      bool gDSxpizueu = false;
      bool FGhgAZfWFS = false;
      bool DExiewpbBc = false;
      bool XsambUSdmg = false;
      bool jKGYfdNEWE = false;
      string MqfyDDdkWt;
      string sultdAVINI;
      string jwrSghcaEH;
      string eHUDFmFHlz;
      string LfKcuisimb;
      string hbFKPPzMQU;
      string ZCfOOlZhnp;
      string uNVOxElOXy;
      string otmbYDBKnp;
      string nsqQYIAwNI;
      string IKtxgUFqML;
      string djnSffPDoL;
      string jPsyBCVEoo;
      string EoBOodzpuE;
      string xKybMEEYks;
      string swGCXsQuue;
      string yACXHniYcB;
      string fYIkNZQRlx;
      string xxSwuHhyqw;
      string MDuQFwIZUX;
      if(MqfyDDdkWt == IKtxgUFqML){VeujMTnVnx = true;}
      else if(IKtxgUFqML == MqfyDDdkWt){KyaVGQexoY = true;}
      if(sultdAVINI == djnSffPDoL){bzJxgAgGbz = true;}
      else if(djnSffPDoL == sultdAVINI){LHBUBIoQUP = true;}
      if(jwrSghcaEH == jPsyBCVEoo){FjhgnbdqeQ = true;}
      else if(jPsyBCVEoo == jwrSghcaEH){rbzfqKLXPI = true;}
      if(eHUDFmFHlz == EoBOodzpuE){RqwNbSCiia = true;}
      else if(EoBOodzpuE == eHUDFmFHlz){XlbdPiFkTk = true;}
      if(LfKcuisimb == xKybMEEYks){TMKsTNtxjE = true;}
      else if(xKybMEEYks == LfKcuisimb){kukWdOlRxb = true;}
      if(hbFKPPzMQU == swGCXsQuue){OByVRkwOwj = true;}
      else if(swGCXsQuue == hbFKPPzMQU){gDSxpizueu = true;}
      if(ZCfOOlZhnp == yACXHniYcB){pwqWfkCuVN = true;}
      else if(yACXHniYcB == ZCfOOlZhnp){FGhgAZfWFS = true;}
      if(uNVOxElOXy == fYIkNZQRlx){yyWAfsYoMa = true;}
      if(otmbYDBKnp == xxSwuHhyqw){hgHZCPsaup = true;}
      if(nsqQYIAwNI == MDuQFwIZUX){VnmzkWUmNi = true;}
      while(fYIkNZQRlx == uNVOxElOXy){DExiewpbBc = true;}
      while(xxSwuHhyqw == xxSwuHhyqw){XsambUSdmg = true;}
      while(MDuQFwIZUX == MDuQFwIZUX){jKGYfdNEWE = true;}
      if(VeujMTnVnx == true){VeujMTnVnx = false;}
      if(bzJxgAgGbz == true){bzJxgAgGbz = false;}
      if(FjhgnbdqeQ == true){FjhgnbdqeQ = false;}
      if(RqwNbSCiia == true){RqwNbSCiia = false;}
      if(TMKsTNtxjE == true){TMKsTNtxjE = false;}
      if(OByVRkwOwj == true){OByVRkwOwj = false;}
      if(pwqWfkCuVN == true){pwqWfkCuVN = false;}
      if(yyWAfsYoMa == true){yyWAfsYoMa = false;}
      if(hgHZCPsaup == true){hgHZCPsaup = false;}
      if(VnmzkWUmNi == true){VnmzkWUmNi = false;}
      if(KyaVGQexoY == true){KyaVGQexoY = false;}
      if(LHBUBIoQUP == true){LHBUBIoQUP = false;}
      if(rbzfqKLXPI == true){rbzfqKLXPI = false;}
      if(XlbdPiFkTk == true){XlbdPiFkTk = false;}
      if(kukWdOlRxb == true){kukWdOlRxb = false;}
      if(gDSxpizueu == true){gDSxpizueu = false;}
      if(FGhgAZfWFS == true){FGhgAZfWFS = false;}
      if(DExiewpbBc == true){DExiewpbBc = false;}
      if(XsambUSdmg == true){XsambUSdmg = false;}
      if(jKGYfdNEWE == true){jKGYfdNEWE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NJVRQYNESC
{ 
  void HquFDfLLHk()
  { 
      bool FzOeieHslL = false;
      bool xChLIjQXQO = false;
      bool HTSlTDeYqY = false;
      bool AxBjziQSmX = false;
      bool FFNhTASYOE = false;
      bool wmMnxlfbKe = false;
      bool zhCNLAAxMY = false;
      bool TyjrIBFkSS = false;
      bool kGKmcNjMmN = false;
      bool DnHHYXCAWT = false;
      bool zULojxCTeu = false;
      bool fuJqtsXPkx = false;
      bool PmKzVeqbTk = false;
      bool yFOyTPtUCe = false;
      bool KQhqgHdPNe = false;
      bool zmOYEMKMTE = false;
      bool GZztwafKXd = false;
      bool yCMGmyFSRN = false;
      bool BaOnlKpotG = false;
      bool FhBxXjQmuG = false;
      string CKCuhhLilh;
      string JdItbLxqPn;
      string KoDRRBJuWm;
      string ekqzDbanMo;
      string dbIpLhAOwV;
      string VpdcaMHjcg;
      string XQMzCXlIqA;
      string kIdZKhgMFj;
      string BuyAQnHOYp;
      string UpKfQMPImn;
      string uqWwkMMDRs;
      string eterecRLiO;
      string PXjAetxyJy;
      string RYZRoJXBOD;
      string bExeLZLSAn;
      string uEYYXXHWQq;
      string POsTbGUMDV;
      string EPxelLZEoF;
      string hexVCMzAtQ;
      string CAkXnNKcDE;
      if(CKCuhhLilh == uqWwkMMDRs){FzOeieHslL = true;}
      else if(uqWwkMMDRs == CKCuhhLilh){zULojxCTeu = true;}
      if(JdItbLxqPn == eterecRLiO){xChLIjQXQO = true;}
      else if(eterecRLiO == JdItbLxqPn){fuJqtsXPkx = true;}
      if(KoDRRBJuWm == PXjAetxyJy){HTSlTDeYqY = true;}
      else if(PXjAetxyJy == KoDRRBJuWm){PmKzVeqbTk = true;}
      if(ekqzDbanMo == RYZRoJXBOD){AxBjziQSmX = true;}
      else if(RYZRoJXBOD == ekqzDbanMo){yFOyTPtUCe = true;}
      if(dbIpLhAOwV == bExeLZLSAn){FFNhTASYOE = true;}
      else if(bExeLZLSAn == dbIpLhAOwV){KQhqgHdPNe = true;}
      if(VpdcaMHjcg == uEYYXXHWQq){wmMnxlfbKe = true;}
      else if(uEYYXXHWQq == VpdcaMHjcg){zmOYEMKMTE = true;}
      if(XQMzCXlIqA == POsTbGUMDV){zhCNLAAxMY = true;}
      else if(POsTbGUMDV == XQMzCXlIqA){GZztwafKXd = true;}
      if(kIdZKhgMFj == EPxelLZEoF){TyjrIBFkSS = true;}
      if(BuyAQnHOYp == hexVCMzAtQ){kGKmcNjMmN = true;}
      if(UpKfQMPImn == CAkXnNKcDE){DnHHYXCAWT = true;}
      while(EPxelLZEoF == kIdZKhgMFj){yCMGmyFSRN = true;}
      while(hexVCMzAtQ == hexVCMzAtQ){BaOnlKpotG = true;}
      while(CAkXnNKcDE == CAkXnNKcDE){FhBxXjQmuG = true;}
      if(FzOeieHslL == true){FzOeieHslL = false;}
      if(xChLIjQXQO == true){xChLIjQXQO = false;}
      if(HTSlTDeYqY == true){HTSlTDeYqY = false;}
      if(AxBjziQSmX == true){AxBjziQSmX = false;}
      if(FFNhTASYOE == true){FFNhTASYOE = false;}
      if(wmMnxlfbKe == true){wmMnxlfbKe = false;}
      if(zhCNLAAxMY == true){zhCNLAAxMY = false;}
      if(TyjrIBFkSS == true){TyjrIBFkSS = false;}
      if(kGKmcNjMmN == true){kGKmcNjMmN = false;}
      if(DnHHYXCAWT == true){DnHHYXCAWT = false;}
      if(zULojxCTeu == true){zULojxCTeu = false;}
      if(fuJqtsXPkx == true){fuJqtsXPkx = false;}
      if(PmKzVeqbTk == true){PmKzVeqbTk = false;}
      if(yFOyTPtUCe == true){yFOyTPtUCe = false;}
      if(KQhqgHdPNe == true){KQhqgHdPNe = false;}
      if(zmOYEMKMTE == true){zmOYEMKMTE = false;}
      if(GZztwafKXd == true){GZztwafKXd = false;}
      if(yCMGmyFSRN == true){yCMGmyFSRN = false;}
      if(BaOnlKpotG == true){BaOnlKpotG = false;}
      if(FhBxXjQmuG == true){FhBxXjQmuG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ALGSBSTBEC
{ 
  void zGILeDwpZx()
  { 
      bool tYsOIfpJuB = false;
      bool VMBVeySnah = false;
      bool KXOscWcRoX = false;
      bool rUuDzdtVYo = false;
      bool JmiMnNlVOE = false;
      bool IehGqWJAkk = false;
      bool CXTWJAQyVB = false;
      bool EwPkXWnBFP = false;
      bool kHDkPMmoLc = false;
      bool TskmmkTMDm = false;
      bool wmzNALPwhU = false;
      bool iItVzuUiHw = false;
      bool MblsgKLcyl = false;
      bool DbyRSyHokE = false;
      bool xqGqtLzPmq = false;
      bool QkFHZUBGfo = false;
      bool zlxuQGJcCB = false;
      bool mexCyVUuyU = false;
      bool KwpHVSWqqy = false;
      bool xAIuELtLam = false;
      string qNbDkoaNXE;
      string cFoiMRWmVU;
      string fEncrlSjLg;
      string nLtdDxGYqu;
      string UpXphwNCVx;
      string VCyUYmZzLz;
      string WqBqQQKLfO;
      string KyuaApfytw;
      string YQONKlNZFQ;
      string XGMrYcngYR;
      string kCWGlWGXTi;
      string GaFOZFbmfe;
      string DjFPqEkCBW;
      string ByYcKWtHbn;
      string epGVJwBxRT;
      string ABBtNAwHPh;
      string kDVxhHCcED;
      string KULrzMdjFt;
      string CmkgVzxdOK;
      string ZmqsCaTInC;
      if(qNbDkoaNXE == kCWGlWGXTi){tYsOIfpJuB = true;}
      else if(kCWGlWGXTi == qNbDkoaNXE){wmzNALPwhU = true;}
      if(cFoiMRWmVU == GaFOZFbmfe){VMBVeySnah = true;}
      else if(GaFOZFbmfe == cFoiMRWmVU){iItVzuUiHw = true;}
      if(fEncrlSjLg == DjFPqEkCBW){KXOscWcRoX = true;}
      else if(DjFPqEkCBW == fEncrlSjLg){MblsgKLcyl = true;}
      if(nLtdDxGYqu == ByYcKWtHbn){rUuDzdtVYo = true;}
      else if(ByYcKWtHbn == nLtdDxGYqu){DbyRSyHokE = true;}
      if(UpXphwNCVx == epGVJwBxRT){JmiMnNlVOE = true;}
      else if(epGVJwBxRT == UpXphwNCVx){xqGqtLzPmq = true;}
      if(VCyUYmZzLz == ABBtNAwHPh){IehGqWJAkk = true;}
      else if(ABBtNAwHPh == VCyUYmZzLz){QkFHZUBGfo = true;}
      if(WqBqQQKLfO == kDVxhHCcED){CXTWJAQyVB = true;}
      else if(kDVxhHCcED == WqBqQQKLfO){zlxuQGJcCB = true;}
      if(KyuaApfytw == KULrzMdjFt){EwPkXWnBFP = true;}
      if(YQONKlNZFQ == CmkgVzxdOK){kHDkPMmoLc = true;}
      if(XGMrYcngYR == ZmqsCaTInC){TskmmkTMDm = true;}
      while(KULrzMdjFt == KyuaApfytw){mexCyVUuyU = true;}
      while(CmkgVzxdOK == CmkgVzxdOK){KwpHVSWqqy = true;}
      while(ZmqsCaTInC == ZmqsCaTInC){xAIuELtLam = true;}
      if(tYsOIfpJuB == true){tYsOIfpJuB = false;}
      if(VMBVeySnah == true){VMBVeySnah = false;}
      if(KXOscWcRoX == true){KXOscWcRoX = false;}
      if(rUuDzdtVYo == true){rUuDzdtVYo = false;}
      if(JmiMnNlVOE == true){JmiMnNlVOE = false;}
      if(IehGqWJAkk == true){IehGqWJAkk = false;}
      if(CXTWJAQyVB == true){CXTWJAQyVB = false;}
      if(EwPkXWnBFP == true){EwPkXWnBFP = false;}
      if(kHDkPMmoLc == true){kHDkPMmoLc = false;}
      if(TskmmkTMDm == true){TskmmkTMDm = false;}
      if(wmzNALPwhU == true){wmzNALPwhU = false;}
      if(iItVzuUiHw == true){iItVzuUiHw = false;}
      if(MblsgKLcyl == true){MblsgKLcyl = false;}
      if(DbyRSyHokE == true){DbyRSyHokE = false;}
      if(xqGqtLzPmq == true){xqGqtLzPmq = false;}
      if(QkFHZUBGfo == true){QkFHZUBGfo = false;}
      if(zlxuQGJcCB == true){zlxuQGJcCB = false;}
      if(mexCyVUuyU == true){mexCyVUuyU = false;}
      if(KwpHVSWqqy == true){KwpHVSWqqy = false;}
      if(xAIuELtLam == true){xAIuELtLam = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PEQATULOKI
{ 
  void MOoaiCtGFN()
  { 
      bool XfKFqBFRqX = false;
      bool dKquIRAJMZ = false;
      bool uVkSTHacyZ = false;
      bool mlzLFbsVrR = false;
      bool mImbnlxSHM = false;
      bool qtmtpBtqlj = false;
      bool acTQkrKfpf = false;
      bool XeQulmiJdg = false;
      bool JIUlhrzFUD = false;
      bool hBjIpJoWpw = false;
      bool aRbanMcqHD = false;
      bool RjNEZRHhhr = false;
      bool sFKlyVtIEb = false;
      bool yMTgGqftxU = false;
      bool PHxRkxnehY = false;
      bool CHnxCUHpbR = false;
      bool RUmfEFQfyh = false;
      bool lNjMclIrAB = false;
      bool hPZfZqXVek = false;
      bool jpRfDuTRNe = false;
      string jjwcubgLGO;
      string ccadxfWaJb;
      string rGMbotZxKJ;
      string gXnYajmFOT;
      string BaRcIXjzlk;
      string nmIQbcXUmA;
      string CjAxgEoBDN;
      string sRMpaRniTR;
      string JaKZVtPWwx;
      string MSRNQQZUwE;
      string hiuYrVZRpK;
      string onAVqbZabl;
      string nRFGBZAyYJ;
      string rSmPiaekhz;
      string TxflHXRwWo;
      string pysJPQdoXR;
      string VbsfSVAklQ;
      string xnsbSqlSyc;
      string IDbjTsZdzS;
      string xoNQdrDzTl;
      if(jjwcubgLGO == hiuYrVZRpK){XfKFqBFRqX = true;}
      else if(hiuYrVZRpK == jjwcubgLGO){aRbanMcqHD = true;}
      if(ccadxfWaJb == onAVqbZabl){dKquIRAJMZ = true;}
      else if(onAVqbZabl == ccadxfWaJb){RjNEZRHhhr = true;}
      if(rGMbotZxKJ == nRFGBZAyYJ){uVkSTHacyZ = true;}
      else if(nRFGBZAyYJ == rGMbotZxKJ){sFKlyVtIEb = true;}
      if(gXnYajmFOT == rSmPiaekhz){mlzLFbsVrR = true;}
      else if(rSmPiaekhz == gXnYajmFOT){yMTgGqftxU = true;}
      if(BaRcIXjzlk == TxflHXRwWo){mImbnlxSHM = true;}
      else if(TxflHXRwWo == BaRcIXjzlk){PHxRkxnehY = true;}
      if(nmIQbcXUmA == pysJPQdoXR){qtmtpBtqlj = true;}
      else if(pysJPQdoXR == nmIQbcXUmA){CHnxCUHpbR = true;}
      if(CjAxgEoBDN == VbsfSVAklQ){acTQkrKfpf = true;}
      else if(VbsfSVAklQ == CjAxgEoBDN){RUmfEFQfyh = true;}
      if(sRMpaRniTR == xnsbSqlSyc){XeQulmiJdg = true;}
      if(JaKZVtPWwx == IDbjTsZdzS){JIUlhrzFUD = true;}
      if(MSRNQQZUwE == xoNQdrDzTl){hBjIpJoWpw = true;}
      while(xnsbSqlSyc == sRMpaRniTR){lNjMclIrAB = true;}
      while(IDbjTsZdzS == IDbjTsZdzS){hPZfZqXVek = true;}
      while(xoNQdrDzTl == xoNQdrDzTl){jpRfDuTRNe = true;}
      if(XfKFqBFRqX == true){XfKFqBFRqX = false;}
      if(dKquIRAJMZ == true){dKquIRAJMZ = false;}
      if(uVkSTHacyZ == true){uVkSTHacyZ = false;}
      if(mlzLFbsVrR == true){mlzLFbsVrR = false;}
      if(mImbnlxSHM == true){mImbnlxSHM = false;}
      if(qtmtpBtqlj == true){qtmtpBtqlj = false;}
      if(acTQkrKfpf == true){acTQkrKfpf = false;}
      if(XeQulmiJdg == true){XeQulmiJdg = false;}
      if(JIUlhrzFUD == true){JIUlhrzFUD = false;}
      if(hBjIpJoWpw == true){hBjIpJoWpw = false;}
      if(aRbanMcqHD == true){aRbanMcqHD = false;}
      if(RjNEZRHhhr == true){RjNEZRHhhr = false;}
      if(sFKlyVtIEb == true){sFKlyVtIEb = false;}
      if(yMTgGqftxU == true){yMTgGqftxU = false;}
      if(PHxRkxnehY == true){PHxRkxnehY = false;}
      if(CHnxCUHpbR == true){CHnxCUHpbR = false;}
      if(RUmfEFQfyh == true){RUmfEFQfyh = false;}
      if(lNjMclIrAB == true){lNjMclIrAB = false;}
      if(hPZfZqXVek == true){hPZfZqXVek = false;}
      if(jpRfDuTRNe == true){jpRfDuTRNe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XUTMQUGQBF
{ 
  void sIXdEdzFAK()
  { 
      bool ggWMkVSgHB = false;
      bool LGRDIWhRUL = false;
      bool HDxLbPadRC = false;
      bool cELJFoMwTp = false;
      bool NArousjzpa = false;
      bool JmaYwciKkU = false;
      bool unPFXHuIxS = false;
      bool KlydyGLIQh = false;
      bool fanprpclNc = false;
      bool GBLyuYklQn = false;
      bool yaBWPXowao = false;
      bool RatDoTAYMh = false;
      bool dIuULJaziZ = false;
      bool UYqciEYQZT = false;
      bool AfLXKeGHJa = false;
      bool YLZiJpfgLG = false;
      bool xoNBUsiRUj = false;
      bool tizsgyxXJg = false;
      bool CSpHAJzHSs = false;
      bool YrFTWLSKDR = false;
      string jHSDyiBFar;
      string JzXygwhDYe;
      string oSVhEjUZyV;
      string lrxzeYUciP;
      string xJVnLsCDUy;
      string kKmaARlkzN;
      string OaGEGQBYTI;
      string bETIgewhVL;
      string hQEAkaFWyN;
      string ljdUBVCQgu;
      string qdjLWfpdsU;
      string UDOmfyVGTe;
      string KeZFVqZyHL;
      string ceBaTDfscE;
      string jbdcsiUpoC;
      string zwxBjMDepe;
      string GrWgroCnTb;
      string RccPtiAwMm;
      string WiJEMfhzpH;
      string ABCyyrFwkD;
      if(jHSDyiBFar == qdjLWfpdsU){ggWMkVSgHB = true;}
      else if(qdjLWfpdsU == jHSDyiBFar){yaBWPXowao = true;}
      if(JzXygwhDYe == UDOmfyVGTe){LGRDIWhRUL = true;}
      else if(UDOmfyVGTe == JzXygwhDYe){RatDoTAYMh = true;}
      if(oSVhEjUZyV == KeZFVqZyHL){HDxLbPadRC = true;}
      else if(KeZFVqZyHL == oSVhEjUZyV){dIuULJaziZ = true;}
      if(lrxzeYUciP == ceBaTDfscE){cELJFoMwTp = true;}
      else if(ceBaTDfscE == lrxzeYUciP){UYqciEYQZT = true;}
      if(xJVnLsCDUy == jbdcsiUpoC){NArousjzpa = true;}
      else if(jbdcsiUpoC == xJVnLsCDUy){AfLXKeGHJa = true;}
      if(kKmaARlkzN == zwxBjMDepe){JmaYwciKkU = true;}
      else if(zwxBjMDepe == kKmaARlkzN){YLZiJpfgLG = true;}
      if(OaGEGQBYTI == GrWgroCnTb){unPFXHuIxS = true;}
      else if(GrWgroCnTb == OaGEGQBYTI){xoNBUsiRUj = true;}
      if(bETIgewhVL == RccPtiAwMm){KlydyGLIQh = true;}
      if(hQEAkaFWyN == WiJEMfhzpH){fanprpclNc = true;}
      if(ljdUBVCQgu == ABCyyrFwkD){GBLyuYklQn = true;}
      while(RccPtiAwMm == bETIgewhVL){tizsgyxXJg = true;}
      while(WiJEMfhzpH == WiJEMfhzpH){CSpHAJzHSs = true;}
      while(ABCyyrFwkD == ABCyyrFwkD){YrFTWLSKDR = true;}
      if(ggWMkVSgHB == true){ggWMkVSgHB = false;}
      if(LGRDIWhRUL == true){LGRDIWhRUL = false;}
      if(HDxLbPadRC == true){HDxLbPadRC = false;}
      if(cELJFoMwTp == true){cELJFoMwTp = false;}
      if(NArousjzpa == true){NArousjzpa = false;}
      if(JmaYwciKkU == true){JmaYwciKkU = false;}
      if(unPFXHuIxS == true){unPFXHuIxS = false;}
      if(KlydyGLIQh == true){KlydyGLIQh = false;}
      if(fanprpclNc == true){fanprpclNc = false;}
      if(GBLyuYklQn == true){GBLyuYklQn = false;}
      if(yaBWPXowao == true){yaBWPXowao = false;}
      if(RatDoTAYMh == true){RatDoTAYMh = false;}
      if(dIuULJaziZ == true){dIuULJaziZ = false;}
      if(UYqciEYQZT == true){UYqciEYQZT = false;}
      if(AfLXKeGHJa == true){AfLXKeGHJa = false;}
      if(YLZiJpfgLG == true){YLZiJpfgLG = false;}
      if(xoNBUsiRUj == true){xoNBUsiRUj = false;}
      if(tizsgyxXJg == true){tizsgyxXJg = false;}
      if(CSpHAJzHSs == true){CSpHAJzHSs = false;}
      if(YrFTWLSKDR == true){YrFTWLSKDR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WJCNFMDJLH
{ 
  void xwctaFrgIZ()
  { 
      bool XSNQKfqWSb = false;
      bool CGKIQFKQRc = false;
      bool RBthTiWANy = false;
      bool aKkJtTHWGp = false;
      bool mkjxjAzIXX = false;
      bool XcMxCVXexb = false;
      bool JpITArUAOw = false;
      bool ymKaofRwxS = false;
      bool iOcpayxnHX = false;
      bool ubZdfxcPwq = false;
      bool ezsaZjSkHW = false;
      bool EbhdsuNSsC = false;
      bool tgsqAVNftr = false;
      bool DBAGnjVBPp = false;
      bool eMfjSTtukk = false;
      bool jJWtxyFBZD = false;
      bool WmpPTDaapJ = false;
      bool ZLCCXhAJYf = false;
      bool bRuJHseGIo = false;
      bool dTaMSrVPQP = false;
      string qfDDnnOKPi;
      string daygutlARo;
      string zOFrdAkTEo;
      string KAVzSNpEez;
      string wWimYCMZEh;
      string JzUXwbaLYn;
      string DuGZYcEyNh;
      string EhVRrbfRTa;
      string nKOWfKexDp;
      string leeqwBQIOu;
      string xOLWcbdDfT;
      string wIrxzrfitN;
      string xGuXuZCeUq;
      string LWDXdZyrsD;
      string gbRitclgqE;
      string UgNAyqSnaD;
      string ZyhnHZFTTZ;
      string snpqgVnMdR;
      string mUnQWeIDZl;
      string GKQochtdaT;
      if(qfDDnnOKPi == xOLWcbdDfT){XSNQKfqWSb = true;}
      else if(xOLWcbdDfT == qfDDnnOKPi){ezsaZjSkHW = true;}
      if(daygutlARo == wIrxzrfitN){CGKIQFKQRc = true;}
      else if(wIrxzrfitN == daygutlARo){EbhdsuNSsC = true;}
      if(zOFrdAkTEo == xGuXuZCeUq){RBthTiWANy = true;}
      else if(xGuXuZCeUq == zOFrdAkTEo){tgsqAVNftr = true;}
      if(KAVzSNpEez == LWDXdZyrsD){aKkJtTHWGp = true;}
      else if(LWDXdZyrsD == KAVzSNpEez){DBAGnjVBPp = true;}
      if(wWimYCMZEh == gbRitclgqE){mkjxjAzIXX = true;}
      else if(gbRitclgqE == wWimYCMZEh){eMfjSTtukk = true;}
      if(JzUXwbaLYn == UgNAyqSnaD){XcMxCVXexb = true;}
      else if(UgNAyqSnaD == JzUXwbaLYn){jJWtxyFBZD = true;}
      if(DuGZYcEyNh == ZyhnHZFTTZ){JpITArUAOw = true;}
      else if(ZyhnHZFTTZ == DuGZYcEyNh){WmpPTDaapJ = true;}
      if(EhVRrbfRTa == snpqgVnMdR){ymKaofRwxS = true;}
      if(nKOWfKexDp == mUnQWeIDZl){iOcpayxnHX = true;}
      if(leeqwBQIOu == GKQochtdaT){ubZdfxcPwq = true;}
      while(snpqgVnMdR == EhVRrbfRTa){ZLCCXhAJYf = true;}
      while(mUnQWeIDZl == mUnQWeIDZl){bRuJHseGIo = true;}
      while(GKQochtdaT == GKQochtdaT){dTaMSrVPQP = true;}
      if(XSNQKfqWSb == true){XSNQKfqWSb = false;}
      if(CGKIQFKQRc == true){CGKIQFKQRc = false;}
      if(RBthTiWANy == true){RBthTiWANy = false;}
      if(aKkJtTHWGp == true){aKkJtTHWGp = false;}
      if(mkjxjAzIXX == true){mkjxjAzIXX = false;}
      if(XcMxCVXexb == true){XcMxCVXexb = false;}
      if(JpITArUAOw == true){JpITArUAOw = false;}
      if(ymKaofRwxS == true){ymKaofRwxS = false;}
      if(iOcpayxnHX == true){iOcpayxnHX = false;}
      if(ubZdfxcPwq == true){ubZdfxcPwq = false;}
      if(ezsaZjSkHW == true){ezsaZjSkHW = false;}
      if(EbhdsuNSsC == true){EbhdsuNSsC = false;}
      if(tgsqAVNftr == true){tgsqAVNftr = false;}
      if(DBAGnjVBPp == true){DBAGnjVBPp = false;}
      if(eMfjSTtukk == true){eMfjSTtukk = false;}
      if(jJWtxyFBZD == true){jJWtxyFBZD = false;}
      if(WmpPTDaapJ == true){WmpPTDaapJ = false;}
      if(ZLCCXhAJYf == true){ZLCCXhAJYf = false;}
      if(bRuJHseGIo == true){bRuJHseGIo = false;}
      if(dTaMSrVPQP == true){dTaMSrVPQP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LZIZHITSSD
{ 
  void heeasGnqdH()
  { 
      bool OsofDRtPST = false;
      bool LHxkUxccDZ = false;
      bool XmHfVAmjBq = false;
      bool ituXOFubES = false;
      bool WlOiscFlXR = false;
      bool TROzaakJJC = false;
      bool eKNakRMZWP = false;
      bool CAYkClXYls = false;
      bool tALjXRfuwm = false;
      bool TkSBmMXnyb = false;
      bool PfPIOSrcxo = false;
      bool DLXPIezcDT = false;
      bool lQdjuRhXxp = false;
      bool OjaJcOkCVE = false;
      bool YCyHiHNCrI = false;
      bool NujepzBeNx = false;
      bool kTfGaSkNls = false;
      bool swHytiRWAm = false;
      bool DeenbSzwTd = false;
      bool NFnYTFWqgQ = false;
      string VrZYdABxuU;
      string RgYzTDZEuc;
      string qiTFofjqYm;
      string pbDlUPjYEy;
      string lmDFxUDudo;
      string uewslmXTix;
      string PKYHeocmdE;
      string SBAxpDeOIU;
      string coMirKfJzh;
      string rPoGhbNwZH;
      string qPQZWtdzDh;
      string IILOTaypPT;
      string JSmwLCLtOO;
      string phnAdNXlMy;
      string ffGRYiEalG;
      string dXgGxXcUOT;
      string ijknrZUKkG;
      string DLcQmdMUWc;
      string ykHHkRBhCF;
      string jDXsPwuRZz;
      if(VrZYdABxuU == qPQZWtdzDh){OsofDRtPST = true;}
      else if(qPQZWtdzDh == VrZYdABxuU){PfPIOSrcxo = true;}
      if(RgYzTDZEuc == IILOTaypPT){LHxkUxccDZ = true;}
      else if(IILOTaypPT == RgYzTDZEuc){DLXPIezcDT = true;}
      if(qiTFofjqYm == JSmwLCLtOO){XmHfVAmjBq = true;}
      else if(JSmwLCLtOO == qiTFofjqYm){lQdjuRhXxp = true;}
      if(pbDlUPjYEy == phnAdNXlMy){ituXOFubES = true;}
      else if(phnAdNXlMy == pbDlUPjYEy){OjaJcOkCVE = true;}
      if(lmDFxUDudo == ffGRYiEalG){WlOiscFlXR = true;}
      else if(ffGRYiEalG == lmDFxUDudo){YCyHiHNCrI = true;}
      if(uewslmXTix == dXgGxXcUOT){TROzaakJJC = true;}
      else if(dXgGxXcUOT == uewslmXTix){NujepzBeNx = true;}
      if(PKYHeocmdE == ijknrZUKkG){eKNakRMZWP = true;}
      else if(ijknrZUKkG == PKYHeocmdE){kTfGaSkNls = true;}
      if(SBAxpDeOIU == DLcQmdMUWc){CAYkClXYls = true;}
      if(coMirKfJzh == ykHHkRBhCF){tALjXRfuwm = true;}
      if(rPoGhbNwZH == jDXsPwuRZz){TkSBmMXnyb = true;}
      while(DLcQmdMUWc == SBAxpDeOIU){swHytiRWAm = true;}
      while(ykHHkRBhCF == ykHHkRBhCF){DeenbSzwTd = true;}
      while(jDXsPwuRZz == jDXsPwuRZz){NFnYTFWqgQ = true;}
      if(OsofDRtPST == true){OsofDRtPST = false;}
      if(LHxkUxccDZ == true){LHxkUxccDZ = false;}
      if(XmHfVAmjBq == true){XmHfVAmjBq = false;}
      if(ituXOFubES == true){ituXOFubES = false;}
      if(WlOiscFlXR == true){WlOiscFlXR = false;}
      if(TROzaakJJC == true){TROzaakJJC = false;}
      if(eKNakRMZWP == true){eKNakRMZWP = false;}
      if(CAYkClXYls == true){CAYkClXYls = false;}
      if(tALjXRfuwm == true){tALjXRfuwm = false;}
      if(TkSBmMXnyb == true){TkSBmMXnyb = false;}
      if(PfPIOSrcxo == true){PfPIOSrcxo = false;}
      if(DLXPIezcDT == true){DLXPIezcDT = false;}
      if(lQdjuRhXxp == true){lQdjuRhXxp = false;}
      if(OjaJcOkCVE == true){OjaJcOkCVE = false;}
      if(YCyHiHNCrI == true){YCyHiHNCrI = false;}
      if(NujepzBeNx == true){NujepzBeNx = false;}
      if(kTfGaSkNls == true){kTfGaSkNls = false;}
      if(swHytiRWAm == true){swHytiRWAm = false;}
      if(DeenbSzwTd == true){DeenbSzwTd = false;}
      if(NFnYTFWqgQ == true){NFnYTFWqgQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YGQJWBOSPA
{ 
  void PbLstyFAoJ()
  { 
      bool zOHrWFSVjM = false;
      bool uNZbNtzGXU = false;
      bool SgxYIdnJGA = false;
      bool RxeJAcDaJp = false;
      bool cmhebaDKQr = false;
      bool qQPXiRQhir = false;
      bool QIPjtxhQak = false;
      bool pXxhrezSwh = false;
      bool ZdsNIBhGah = false;
      bool LUrQYTXyje = false;
      bool rlieCTThfD = false;
      bool SylASmPCas = false;
      bool ObpsZUffJX = false;
      bool HBhQpmtNKo = false;
      bool hAaWPNiqyl = false;
      bool EUWqPQupFg = false;
      bool mmXIwRQUKe = false;
      bool rBqlLOATdL = false;
      bool lnhXSldpAZ = false;
      bool qEHdBtbSZx = false;
      string FGdlYpgkwQ;
      string VogbECBpZo;
      string abnAFMfFYx;
      string eQraJMRjWM;
      string urAPFYWrSl;
      string ktJoAdSdgL;
      string KaLylFxGSr;
      string jRTMthbXtf;
      string pmmlMjGCZe;
      string snDKBTfBdA;
      string bQYZBTaxtR;
      string BtiAVWnYlB;
      string ytfnywNIKa;
      string CZtsEYONjr;
      string JJIIczEDoe;
      string eGPbBgkkaF;
      string FSlTPbzpux;
      string IZnsqolXKz;
      string qKSfuuJSrW;
      string ndlemqWnrB;
      if(FGdlYpgkwQ == bQYZBTaxtR){zOHrWFSVjM = true;}
      else if(bQYZBTaxtR == FGdlYpgkwQ){rlieCTThfD = true;}
      if(VogbECBpZo == BtiAVWnYlB){uNZbNtzGXU = true;}
      else if(BtiAVWnYlB == VogbECBpZo){SylASmPCas = true;}
      if(abnAFMfFYx == ytfnywNIKa){SgxYIdnJGA = true;}
      else if(ytfnywNIKa == abnAFMfFYx){ObpsZUffJX = true;}
      if(eQraJMRjWM == CZtsEYONjr){RxeJAcDaJp = true;}
      else if(CZtsEYONjr == eQraJMRjWM){HBhQpmtNKo = true;}
      if(urAPFYWrSl == JJIIczEDoe){cmhebaDKQr = true;}
      else if(JJIIczEDoe == urAPFYWrSl){hAaWPNiqyl = true;}
      if(ktJoAdSdgL == eGPbBgkkaF){qQPXiRQhir = true;}
      else if(eGPbBgkkaF == ktJoAdSdgL){EUWqPQupFg = true;}
      if(KaLylFxGSr == FSlTPbzpux){QIPjtxhQak = true;}
      else if(FSlTPbzpux == KaLylFxGSr){mmXIwRQUKe = true;}
      if(jRTMthbXtf == IZnsqolXKz){pXxhrezSwh = true;}
      if(pmmlMjGCZe == qKSfuuJSrW){ZdsNIBhGah = true;}
      if(snDKBTfBdA == ndlemqWnrB){LUrQYTXyje = true;}
      while(IZnsqolXKz == jRTMthbXtf){rBqlLOATdL = true;}
      while(qKSfuuJSrW == qKSfuuJSrW){lnhXSldpAZ = true;}
      while(ndlemqWnrB == ndlemqWnrB){qEHdBtbSZx = true;}
      if(zOHrWFSVjM == true){zOHrWFSVjM = false;}
      if(uNZbNtzGXU == true){uNZbNtzGXU = false;}
      if(SgxYIdnJGA == true){SgxYIdnJGA = false;}
      if(RxeJAcDaJp == true){RxeJAcDaJp = false;}
      if(cmhebaDKQr == true){cmhebaDKQr = false;}
      if(qQPXiRQhir == true){qQPXiRQhir = false;}
      if(QIPjtxhQak == true){QIPjtxhQak = false;}
      if(pXxhrezSwh == true){pXxhrezSwh = false;}
      if(ZdsNIBhGah == true){ZdsNIBhGah = false;}
      if(LUrQYTXyje == true){LUrQYTXyje = false;}
      if(rlieCTThfD == true){rlieCTThfD = false;}
      if(SylASmPCas == true){SylASmPCas = false;}
      if(ObpsZUffJX == true){ObpsZUffJX = false;}
      if(HBhQpmtNKo == true){HBhQpmtNKo = false;}
      if(hAaWPNiqyl == true){hAaWPNiqyl = false;}
      if(EUWqPQupFg == true){EUWqPQupFg = false;}
      if(mmXIwRQUKe == true){mmXIwRQUKe = false;}
      if(rBqlLOATdL == true){rBqlLOATdL = false;}
      if(lnhXSldpAZ == true){lnhXSldpAZ = false;}
      if(qEHdBtbSZx == true){qEHdBtbSZx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PZRKDXPSRN
{ 
  void ppPbJLkTde()
  { 
      bool RCLRpQgPTU = false;
      bool XHqRaBNAOs = false;
      bool yurJGmQdOZ = false;
      bool LEnDlIZmOs = false;
      bool pxQJDcJDJV = false;
      bool lenMEVKCKC = false;
      bool ADAtISTmfR = false;
      bool bZkUDBeiFd = false;
      bool cMTrnfPazP = false;
      bool yWcMrlwVAk = false;
      bool JWXqsLtTJC = false;
      bool pawgYmjIGb = false;
      bool CrnQTExYbQ = false;
      bool FIhUTGobzb = false;
      bool lwRwYXZumE = false;
      bool CmPYhRhHXn = false;
      bool NVqrwgrbMR = false;
      bool yHJdpGaqqu = false;
      bool dCkXORsJlC = false;
      bool YhEKNQFYzq = false;
      string XjRCjzpbEo;
      string VoPfBDgibQ;
      string TmFXkxsysa;
      string rSrrXofHcY;
      string WRblrMpajw;
      string toreljesRm;
      string GqicxCxWHM;
      string XYFDsCLTfX;
      string GROwfDZNGm;
      string JlppSfhyno;
      string PSSXYViolj;
      string YLMsfnclwt;
      string ciQUCkhPjN;
      string TNepImzqXK;
      string TkbWOyYxKe;
      string CwBtMfCxVm;
      string mTFYQKfWkr;
      string olOlZqHtGD;
      string LkFEKWMjdb;
      string kBUkXAfCFD;
      if(XjRCjzpbEo == PSSXYViolj){RCLRpQgPTU = true;}
      else if(PSSXYViolj == XjRCjzpbEo){JWXqsLtTJC = true;}
      if(VoPfBDgibQ == YLMsfnclwt){XHqRaBNAOs = true;}
      else if(YLMsfnclwt == VoPfBDgibQ){pawgYmjIGb = true;}
      if(TmFXkxsysa == ciQUCkhPjN){yurJGmQdOZ = true;}
      else if(ciQUCkhPjN == TmFXkxsysa){CrnQTExYbQ = true;}
      if(rSrrXofHcY == TNepImzqXK){LEnDlIZmOs = true;}
      else if(TNepImzqXK == rSrrXofHcY){FIhUTGobzb = true;}
      if(WRblrMpajw == TkbWOyYxKe){pxQJDcJDJV = true;}
      else if(TkbWOyYxKe == WRblrMpajw){lwRwYXZumE = true;}
      if(toreljesRm == CwBtMfCxVm){lenMEVKCKC = true;}
      else if(CwBtMfCxVm == toreljesRm){CmPYhRhHXn = true;}
      if(GqicxCxWHM == mTFYQKfWkr){ADAtISTmfR = true;}
      else if(mTFYQKfWkr == GqicxCxWHM){NVqrwgrbMR = true;}
      if(XYFDsCLTfX == olOlZqHtGD){bZkUDBeiFd = true;}
      if(GROwfDZNGm == LkFEKWMjdb){cMTrnfPazP = true;}
      if(JlppSfhyno == kBUkXAfCFD){yWcMrlwVAk = true;}
      while(olOlZqHtGD == XYFDsCLTfX){yHJdpGaqqu = true;}
      while(LkFEKWMjdb == LkFEKWMjdb){dCkXORsJlC = true;}
      while(kBUkXAfCFD == kBUkXAfCFD){YhEKNQFYzq = true;}
      if(RCLRpQgPTU == true){RCLRpQgPTU = false;}
      if(XHqRaBNAOs == true){XHqRaBNAOs = false;}
      if(yurJGmQdOZ == true){yurJGmQdOZ = false;}
      if(LEnDlIZmOs == true){LEnDlIZmOs = false;}
      if(pxQJDcJDJV == true){pxQJDcJDJV = false;}
      if(lenMEVKCKC == true){lenMEVKCKC = false;}
      if(ADAtISTmfR == true){ADAtISTmfR = false;}
      if(bZkUDBeiFd == true){bZkUDBeiFd = false;}
      if(cMTrnfPazP == true){cMTrnfPazP = false;}
      if(yWcMrlwVAk == true){yWcMrlwVAk = false;}
      if(JWXqsLtTJC == true){JWXqsLtTJC = false;}
      if(pawgYmjIGb == true){pawgYmjIGb = false;}
      if(CrnQTExYbQ == true){CrnQTExYbQ = false;}
      if(FIhUTGobzb == true){FIhUTGobzb = false;}
      if(lwRwYXZumE == true){lwRwYXZumE = false;}
      if(CmPYhRhHXn == true){CmPYhRhHXn = false;}
      if(NVqrwgrbMR == true){NVqrwgrbMR = false;}
      if(yHJdpGaqqu == true){yHJdpGaqqu = false;}
      if(dCkXORsJlC == true){dCkXORsJlC = false;}
      if(YhEKNQFYzq == true){YhEKNQFYzq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OUZWPZWXJM
{ 
  void dnOIhqDyVn()
  { 
      bool xStQYgDNbI = false;
      bool YjzTeqoskT = false;
      bool JLFWMWbssY = false;
      bool OLcCSKmiRV = false;
      bool nSnbPPtoCN = false;
      bool cLNuDlMWEC = false;
      bool EJTDtMGwBT = false;
      bool DFaPfqWdHw = false;
      bool blpfwCyhyf = false;
      bool yPePQdyjhC = false;
      bool JyniJXjxPM = false;
      bool PiPIZRTmHq = false;
      bool OYxUUnaLyB = false;
      bool rmuEldyHVY = false;
      bool RASkQPzVpy = false;
      bool KLcqnjASNV = false;
      bool wYyNUbmLVw = false;
      bool TLRiYOGMEE = false;
      bool nEUAqgJEQC = false;
      bool cesAbsBEPn = false;
      string CHHRytUnzS;
      string kUiCYTDXbT;
      string UntDeodUif;
      string rTaJyySaaf;
      string yBHrDaTlAx;
      string oQMdBOMElJ;
      string QzETaQtZDa;
      string BbwuUSgBAD;
      string VqTlqbGwHj;
      string kNnROywnRl;
      string gshZuMTQJh;
      string gLEinZfRby;
      string JxRSpmndgV;
      string WrjNWbItpd;
      string HpmZCYJFdo;
      string SeLScibOjI;
      string YojnLobqLM;
      string QlayqTKqPQ;
      string dhAqCqfQkn;
      string AsJhERFyON;
      if(CHHRytUnzS == gshZuMTQJh){xStQYgDNbI = true;}
      else if(gshZuMTQJh == CHHRytUnzS){JyniJXjxPM = true;}
      if(kUiCYTDXbT == gLEinZfRby){YjzTeqoskT = true;}
      else if(gLEinZfRby == kUiCYTDXbT){PiPIZRTmHq = true;}
      if(UntDeodUif == JxRSpmndgV){JLFWMWbssY = true;}
      else if(JxRSpmndgV == UntDeodUif){OYxUUnaLyB = true;}
      if(rTaJyySaaf == WrjNWbItpd){OLcCSKmiRV = true;}
      else if(WrjNWbItpd == rTaJyySaaf){rmuEldyHVY = true;}
      if(yBHrDaTlAx == HpmZCYJFdo){nSnbPPtoCN = true;}
      else if(HpmZCYJFdo == yBHrDaTlAx){RASkQPzVpy = true;}
      if(oQMdBOMElJ == SeLScibOjI){cLNuDlMWEC = true;}
      else if(SeLScibOjI == oQMdBOMElJ){KLcqnjASNV = true;}
      if(QzETaQtZDa == YojnLobqLM){EJTDtMGwBT = true;}
      else if(YojnLobqLM == QzETaQtZDa){wYyNUbmLVw = true;}
      if(BbwuUSgBAD == QlayqTKqPQ){DFaPfqWdHw = true;}
      if(VqTlqbGwHj == dhAqCqfQkn){blpfwCyhyf = true;}
      if(kNnROywnRl == AsJhERFyON){yPePQdyjhC = true;}
      while(QlayqTKqPQ == BbwuUSgBAD){TLRiYOGMEE = true;}
      while(dhAqCqfQkn == dhAqCqfQkn){nEUAqgJEQC = true;}
      while(AsJhERFyON == AsJhERFyON){cesAbsBEPn = true;}
      if(xStQYgDNbI == true){xStQYgDNbI = false;}
      if(YjzTeqoskT == true){YjzTeqoskT = false;}
      if(JLFWMWbssY == true){JLFWMWbssY = false;}
      if(OLcCSKmiRV == true){OLcCSKmiRV = false;}
      if(nSnbPPtoCN == true){nSnbPPtoCN = false;}
      if(cLNuDlMWEC == true){cLNuDlMWEC = false;}
      if(EJTDtMGwBT == true){EJTDtMGwBT = false;}
      if(DFaPfqWdHw == true){DFaPfqWdHw = false;}
      if(blpfwCyhyf == true){blpfwCyhyf = false;}
      if(yPePQdyjhC == true){yPePQdyjhC = false;}
      if(JyniJXjxPM == true){JyniJXjxPM = false;}
      if(PiPIZRTmHq == true){PiPIZRTmHq = false;}
      if(OYxUUnaLyB == true){OYxUUnaLyB = false;}
      if(rmuEldyHVY == true){rmuEldyHVY = false;}
      if(RASkQPzVpy == true){RASkQPzVpy = false;}
      if(KLcqnjASNV == true){KLcqnjASNV = false;}
      if(wYyNUbmLVw == true){wYyNUbmLVw = false;}
      if(TLRiYOGMEE == true){TLRiYOGMEE = false;}
      if(nEUAqgJEQC == true){nEUAqgJEQC = false;}
      if(cesAbsBEPn == true){cesAbsBEPn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YZWSCGMOYA
{ 
  void fANEwADdws()
  { 
      bool ixtBuUkPKe = false;
      bool WUeYVUFypL = false;
      bool FhUPhysEas = false;
      bool cclQnzCFAT = false;
      bool noBuniuZEj = false;
      bool OgbWqBbeTx = false;
      bool bfoRBthOjV = false;
      bool RAyWWPgZby = false;
      bool CTApewAPYm = false;
      bool WXkDqHzjss = false;
      bool AgohRNiFza = false;
      bool UCDVtIfzlE = false;
      bool sSoxztOteP = false;
      bool QwfhyVdRYQ = false;
      bool NtQySUTPJi = false;
      bool azynzhqriW = false;
      bool znajJXWUWX = false;
      bool dOaUqzCqde = false;
      bool ZykwnQyqhP = false;
      bool eliBRZTgnt = false;
      string LzgNbzigot;
      string FfdLJqKdRe;
      string yCMjUcbDEh;
      string JgKyZxzSRl;
      string dSEFwfHxKB;
      string bTsgFImwrz;
      string XecHkXVekM;
      string rrMfAexGmn;
      string UesDFoncrR;
      string KCZRNzpxUY;
      string KbLyIjHMfZ;
      string KfJEdrlZBu;
      string jrmTBpRtRB;
      string oAkOdsSttV;
      string gaxSGdrUmU;
      string MQuYnSorwS;
      string RMuejKtuak;
      string ZqeeNJuTMX;
      string xwHwoYFMZK;
      string DayaEUfRhw;
      if(LzgNbzigot == KbLyIjHMfZ){ixtBuUkPKe = true;}
      else if(KbLyIjHMfZ == LzgNbzigot){AgohRNiFza = true;}
      if(FfdLJqKdRe == KfJEdrlZBu){WUeYVUFypL = true;}
      else if(KfJEdrlZBu == FfdLJqKdRe){UCDVtIfzlE = true;}
      if(yCMjUcbDEh == jrmTBpRtRB){FhUPhysEas = true;}
      else if(jrmTBpRtRB == yCMjUcbDEh){sSoxztOteP = true;}
      if(JgKyZxzSRl == oAkOdsSttV){cclQnzCFAT = true;}
      else if(oAkOdsSttV == JgKyZxzSRl){QwfhyVdRYQ = true;}
      if(dSEFwfHxKB == gaxSGdrUmU){noBuniuZEj = true;}
      else if(gaxSGdrUmU == dSEFwfHxKB){NtQySUTPJi = true;}
      if(bTsgFImwrz == MQuYnSorwS){OgbWqBbeTx = true;}
      else if(MQuYnSorwS == bTsgFImwrz){azynzhqriW = true;}
      if(XecHkXVekM == RMuejKtuak){bfoRBthOjV = true;}
      else if(RMuejKtuak == XecHkXVekM){znajJXWUWX = true;}
      if(rrMfAexGmn == ZqeeNJuTMX){RAyWWPgZby = true;}
      if(UesDFoncrR == xwHwoYFMZK){CTApewAPYm = true;}
      if(KCZRNzpxUY == DayaEUfRhw){WXkDqHzjss = true;}
      while(ZqeeNJuTMX == rrMfAexGmn){dOaUqzCqde = true;}
      while(xwHwoYFMZK == xwHwoYFMZK){ZykwnQyqhP = true;}
      while(DayaEUfRhw == DayaEUfRhw){eliBRZTgnt = true;}
      if(ixtBuUkPKe == true){ixtBuUkPKe = false;}
      if(WUeYVUFypL == true){WUeYVUFypL = false;}
      if(FhUPhysEas == true){FhUPhysEas = false;}
      if(cclQnzCFAT == true){cclQnzCFAT = false;}
      if(noBuniuZEj == true){noBuniuZEj = false;}
      if(OgbWqBbeTx == true){OgbWqBbeTx = false;}
      if(bfoRBthOjV == true){bfoRBthOjV = false;}
      if(RAyWWPgZby == true){RAyWWPgZby = false;}
      if(CTApewAPYm == true){CTApewAPYm = false;}
      if(WXkDqHzjss == true){WXkDqHzjss = false;}
      if(AgohRNiFza == true){AgohRNiFza = false;}
      if(UCDVtIfzlE == true){UCDVtIfzlE = false;}
      if(sSoxztOteP == true){sSoxztOteP = false;}
      if(QwfhyVdRYQ == true){QwfhyVdRYQ = false;}
      if(NtQySUTPJi == true){NtQySUTPJi = false;}
      if(azynzhqriW == true){azynzhqriW = false;}
      if(znajJXWUWX == true){znajJXWUWX = false;}
      if(dOaUqzCqde == true){dOaUqzCqde = false;}
      if(ZykwnQyqhP == true){ZykwnQyqhP = false;}
      if(eliBRZTgnt == true){eliBRZTgnt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXRYEOXQUX
{ 
  void WemIcCfyLm()
  { 
      bool CjRZfMmgGu = false;
      bool sIWBKXCMRL = false;
      bool IhQonRwRPI = false;
      bool lYyWqfZhDB = false;
      bool bDUFwdpKRM = false;
      bool wcTOIUSclO = false;
      bool QURyIUKzJd = false;
      bool xTJPiFMLrJ = false;
      bool akACLJEjOW = false;
      bool MxwokGlWwa = false;
      bool TpAmObTDeD = false;
      bool IHjbnfUOmz = false;
      bool QakmRAWTec = false;
      bool ToPRpjjMmi = false;
      bool pAEKNENUBE = false;
      bool kWjxJsFMUO = false;
      bool FzYCiSrRlD = false;
      bool uHaDIPVZZM = false;
      bool lCSaqwFRHw = false;
      bool eWrXdqbBbt = false;
      string IaFRGICBdE;
      string ieNGBPfbSg;
      string wtDzRhScHV;
      string FlTQkiBVVG;
      string KXrfkqEgTJ;
      string PZFltNXFzY;
      string pYtIywKwVR;
      string OKFMVXCXNa;
      string ckJxGefhWW;
      string LuVwQkcjgn;
      string fHLBtEUsPV;
      string LzrYwEPwBS;
      string PbZzFToJuj;
      string uSpZtUZHDB;
      string KmRAKLCwAL;
      string UfhOXEhLua;
      string PLxfZsJSea;
      string eIsAHcKYnt;
      string QrIjOOjbBp;
      string mNMbkzpkZR;
      if(IaFRGICBdE == fHLBtEUsPV){CjRZfMmgGu = true;}
      else if(fHLBtEUsPV == IaFRGICBdE){TpAmObTDeD = true;}
      if(ieNGBPfbSg == LzrYwEPwBS){sIWBKXCMRL = true;}
      else if(LzrYwEPwBS == ieNGBPfbSg){IHjbnfUOmz = true;}
      if(wtDzRhScHV == PbZzFToJuj){IhQonRwRPI = true;}
      else if(PbZzFToJuj == wtDzRhScHV){QakmRAWTec = true;}
      if(FlTQkiBVVG == uSpZtUZHDB){lYyWqfZhDB = true;}
      else if(uSpZtUZHDB == FlTQkiBVVG){ToPRpjjMmi = true;}
      if(KXrfkqEgTJ == KmRAKLCwAL){bDUFwdpKRM = true;}
      else if(KmRAKLCwAL == KXrfkqEgTJ){pAEKNENUBE = true;}
      if(PZFltNXFzY == UfhOXEhLua){wcTOIUSclO = true;}
      else if(UfhOXEhLua == PZFltNXFzY){kWjxJsFMUO = true;}
      if(pYtIywKwVR == PLxfZsJSea){QURyIUKzJd = true;}
      else if(PLxfZsJSea == pYtIywKwVR){FzYCiSrRlD = true;}
      if(OKFMVXCXNa == eIsAHcKYnt){xTJPiFMLrJ = true;}
      if(ckJxGefhWW == QrIjOOjbBp){akACLJEjOW = true;}
      if(LuVwQkcjgn == mNMbkzpkZR){MxwokGlWwa = true;}
      while(eIsAHcKYnt == OKFMVXCXNa){uHaDIPVZZM = true;}
      while(QrIjOOjbBp == QrIjOOjbBp){lCSaqwFRHw = true;}
      while(mNMbkzpkZR == mNMbkzpkZR){eWrXdqbBbt = true;}
      if(CjRZfMmgGu == true){CjRZfMmgGu = false;}
      if(sIWBKXCMRL == true){sIWBKXCMRL = false;}
      if(IhQonRwRPI == true){IhQonRwRPI = false;}
      if(lYyWqfZhDB == true){lYyWqfZhDB = false;}
      if(bDUFwdpKRM == true){bDUFwdpKRM = false;}
      if(wcTOIUSclO == true){wcTOIUSclO = false;}
      if(QURyIUKzJd == true){QURyIUKzJd = false;}
      if(xTJPiFMLrJ == true){xTJPiFMLrJ = false;}
      if(akACLJEjOW == true){akACLJEjOW = false;}
      if(MxwokGlWwa == true){MxwokGlWwa = false;}
      if(TpAmObTDeD == true){TpAmObTDeD = false;}
      if(IHjbnfUOmz == true){IHjbnfUOmz = false;}
      if(QakmRAWTec == true){QakmRAWTec = false;}
      if(ToPRpjjMmi == true){ToPRpjjMmi = false;}
      if(pAEKNENUBE == true){pAEKNENUBE = false;}
      if(kWjxJsFMUO == true){kWjxJsFMUO = false;}
      if(FzYCiSrRlD == true){FzYCiSrRlD = false;}
      if(uHaDIPVZZM == true){uHaDIPVZZM = false;}
      if(lCSaqwFRHw == true){lCSaqwFRHw = false;}
      if(eWrXdqbBbt == true){eWrXdqbBbt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYOPRDGREY
{ 
  void BZORtKiOFc()
  { 
      bool SVOsxyjKeN = false;
      bool fAaNEQKMOx = false;
      bool LUYJpWWFMD = false;
      bool fCHXDkMmmR = false;
      bool arnXaRNtEH = false;
      bool CimHqxxFDZ = false;
      bool bdxagcsCKS = false;
      bool DXYxWTgAhY = false;
      bool JbAFBwPAfF = false;
      bool nHjNoxtNpx = false;
      bool XKikDeJokX = false;
      bool QxWdQzcrZj = false;
      bool NsWEewmLIZ = false;
      bool YSJjAyrOBV = false;
      bool mZPIoqjFwo = false;
      bool TCmFjendGG = false;
      bool rygKzxmlcS = false;
      bool GNpDxmcOPn = false;
      bool MgOSFWfDAV = false;
      bool JNIudnrEIq = false;
      string IulMYjojal;
      string xWzArxLaGY;
      string oEGLkPxLbK;
      string hmbsfBrPAz;
      string dtLXWTtNEF;
      string uBzTNDnZaJ;
      string mdIPDKuGTq;
      string FuZGturinR;
      string UjGVPgmHfb;
      string MRnqMAkuTM;
      string YnsNAzarZR;
      string KEkJoCWlAW;
      string WmZqdmGitt;
      string JxPbrfprVP;
      string FthNQHfeCJ;
      string dztwpkNBjM;
      string rryeINoJQI;
      string LePjRbFMaV;
      string HbgkQKCTkH;
      string RoIJXNwCFC;
      if(IulMYjojal == YnsNAzarZR){SVOsxyjKeN = true;}
      else if(YnsNAzarZR == IulMYjojal){XKikDeJokX = true;}
      if(xWzArxLaGY == KEkJoCWlAW){fAaNEQKMOx = true;}
      else if(KEkJoCWlAW == xWzArxLaGY){QxWdQzcrZj = true;}
      if(oEGLkPxLbK == WmZqdmGitt){LUYJpWWFMD = true;}
      else if(WmZqdmGitt == oEGLkPxLbK){NsWEewmLIZ = true;}
      if(hmbsfBrPAz == JxPbrfprVP){fCHXDkMmmR = true;}
      else if(JxPbrfprVP == hmbsfBrPAz){YSJjAyrOBV = true;}
      if(dtLXWTtNEF == FthNQHfeCJ){arnXaRNtEH = true;}
      else if(FthNQHfeCJ == dtLXWTtNEF){mZPIoqjFwo = true;}
      if(uBzTNDnZaJ == dztwpkNBjM){CimHqxxFDZ = true;}
      else if(dztwpkNBjM == uBzTNDnZaJ){TCmFjendGG = true;}
      if(mdIPDKuGTq == rryeINoJQI){bdxagcsCKS = true;}
      else if(rryeINoJQI == mdIPDKuGTq){rygKzxmlcS = true;}
      if(FuZGturinR == LePjRbFMaV){DXYxWTgAhY = true;}
      if(UjGVPgmHfb == HbgkQKCTkH){JbAFBwPAfF = true;}
      if(MRnqMAkuTM == RoIJXNwCFC){nHjNoxtNpx = true;}
      while(LePjRbFMaV == FuZGturinR){GNpDxmcOPn = true;}
      while(HbgkQKCTkH == HbgkQKCTkH){MgOSFWfDAV = true;}
      while(RoIJXNwCFC == RoIJXNwCFC){JNIudnrEIq = true;}
      if(SVOsxyjKeN == true){SVOsxyjKeN = false;}
      if(fAaNEQKMOx == true){fAaNEQKMOx = false;}
      if(LUYJpWWFMD == true){LUYJpWWFMD = false;}
      if(fCHXDkMmmR == true){fCHXDkMmmR = false;}
      if(arnXaRNtEH == true){arnXaRNtEH = false;}
      if(CimHqxxFDZ == true){CimHqxxFDZ = false;}
      if(bdxagcsCKS == true){bdxagcsCKS = false;}
      if(DXYxWTgAhY == true){DXYxWTgAhY = false;}
      if(JbAFBwPAfF == true){JbAFBwPAfF = false;}
      if(nHjNoxtNpx == true){nHjNoxtNpx = false;}
      if(XKikDeJokX == true){XKikDeJokX = false;}
      if(QxWdQzcrZj == true){QxWdQzcrZj = false;}
      if(NsWEewmLIZ == true){NsWEewmLIZ = false;}
      if(YSJjAyrOBV == true){YSJjAyrOBV = false;}
      if(mZPIoqjFwo == true){mZPIoqjFwo = false;}
      if(TCmFjendGG == true){TCmFjendGG = false;}
      if(rygKzxmlcS == true){rygKzxmlcS = false;}
      if(GNpDxmcOPn == true){GNpDxmcOPn = false;}
      if(MgOSFWfDAV == true){MgOSFWfDAV = false;}
      if(JNIudnrEIq == true){JNIudnrEIq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HASFMZYCCJ
{ 
  void bVajlonydL()
  { 
      bool HWHRkjpcyq = false;
      bool rOEyyhBoNz = false;
      bool OteoDQRtPN = false;
      bool xyUCHAdWOY = false;
      bool MmAyjayjPa = false;
      bool ogeDoNrRNU = false;
      bool RuMktstBpx = false;
      bool EeZnlbsgEc = false;
      bool RgeoYPSRNt = false;
      bool IMItGRZPDq = false;
      bool fxsRVJGqQN = false;
      bool TKMjCkPXMd = false;
      bool ZcnworWegT = false;
      bool BdcNxUmNSO = false;
      bool JbAAZxzYrV = false;
      bool BBDZQDJxbd = false;
      bool maJwLphymh = false;
      bool xCFxUybmVr = false;
      bool rymKSzZCxs = false;
      bool LpknahSDnj = false;
      string thpYumqsIx;
      string hOkSIHEVZa;
      string rdpZnkoVhA;
      string psYCwqdopi;
      string BAKxfiwYuN;
      string sTlptPqPkJ;
      string xVLHHnpiWQ;
      string cOeqZqTssF;
      string oPZTGVHhHf;
      string ANEflfoCor;
      string rNCdkdouQD;
      string wyVeUguqBl;
      string gIapQOKzEs;
      string BQDBMbNuic;
      string gMQEiCrYKE;
      string jyBDLjlLMV;
      string TppWCetURs;
      string SAIYETrWHO;
      string WknAJDPzoc;
      string oChNIqWsCE;
      if(thpYumqsIx == rNCdkdouQD){HWHRkjpcyq = true;}
      else if(rNCdkdouQD == thpYumqsIx){fxsRVJGqQN = true;}
      if(hOkSIHEVZa == wyVeUguqBl){rOEyyhBoNz = true;}
      else if(wyVeUguqBl == hOkSIHEVZa){TKMjCkPXMd = true;}
      if(rdpZnkoVhA == gIapQOKzEs){OteoDQRtPN = true;}
      else if(gIapQOKzEs == rdpZnkoVhA){ZcnworWegT = true;}
      if(psYCwqdopi == BQDBMbNuic){xyUCHAdWOY = true;}
      else if(BQDBMbNuic == psYCwqdopi){BdcNxUmNSO = true;}
      if(BAKxfiwYuN == gMQEiCrYKE){MmAyjayjPa = true;}
      else if(gMQEiCrYKE == BAKxfiwYuN){JbAAZxzYrV = true;}
      if(sTlptPqPkJ == jyBDLjlLMV){ogeDoNrRNU = true;}
      else if(jyBDLjlLMV == sTlptPqPkJ){BBDZQDJxbd = true;}
      if(xVLHHnpiWQ == TppWCetURs){RuMktstBpx = true;}
      else if(TppWCetURs == xVLHHnpiWQ){maJwLphymh = true;}
      if(cOeqZqTssF == SAIYETrWHO){EeZnlbsgEc = true;}
      if(oPZTGVHhHf == WknAJDPzoc){RgeoYPSRNt = true;}
      if(ANEflfoCor == oChNIqWsCE){IMItGRZPDq = true;}
      while(SAIYETrWHO == cOeqZqTssF){xCFxUybmVr = true;}
      while(WknAJDPzoc == WknAJDPzoc){rymKSzZCxs = true;}
      while(oChNIqWsCE == oChNIqWsCE){LpknahSDnj = true;}
      if(HWHRkjpcyq == true){HWHRkjpcyq = false;}
      if(rOEyyhBoNz == true){rOEyyhBoNz = false;}
      if(OteoDQRtPN == true){OteoDQRtPN = false;}
      if(xyUCHAdWOY == true){xyUCHAdWOY = false;}
      if(MmAyjayjPa == true){MmAyjayjPa = false;}
      if(ogeDoNrRNU == true){ogeDoNrRNU = false;}
      if(RuMktstBpx == true){RuMktstBpx = false;}
      if(EeZnlbsgEc == true){EeZnlbsgEc = false;}
      if(RgeoYPSRNt == true){RgeoYPSRNt = false;}
      if(IMItGRZPDq == true){IMItGRZPDq = false;}
      if(fxsRVJGqQN == true){fxsRVJGqQN = false;}
      if(TKMjCkPXMd == true){TKMjCkPXMd = false;}
      if(ZcnworWegT == true){ZcnworWegT = false;}
      if(BdcNxUmNSO == true){BdcNxUmNSO = false;}
      if(JbAAZxzYrV == true){JbAAZxzYrV = false;}
      if(BBDZQDJxbd == true){BBDZQDJxbd = false;}
      if(maJwLphymh == true){maJwLphymh = false;}
      if(xCFxUybmVr == true){xCFxUybmVr = false;}
      if(rymKSzZCxs == true){rymKSzZCxs = false;}
      if(LpknahSDnj == true){LpknahSDnj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HGGKEKHEZD
{ 
  void IwlagVsxno()
  { 
      bool jbIJtqcXqk = false;
      bool DgAuKLtoIw = false;
      bool aPYstTtHXH = false;
      bool hTCICDFGGb = false;
      bool wIqOocbOkq = false;
      bool JjRKkTCPPa = false;
      bool wVAjCjdrsG = false;
      bool FnhgARYKDQ = false;
      bool qfWfxxCrWh = false;
      bool AoqfeaIHLF = false;
      bool yjVdkVCkJS = false;
      bool urMyiQyTlE = false;
      bool hlVKFQwCBY = false;
      bool IRyxSHJrta = false;
      bool uQhDlIbswO = false;
      bool bnUHXMNKYU = false;
      bool YzjkJdsOeb = false;
      bool GGZKIQERYx = false;
      bool nDFlxUwqZF = false;
      bool szTYCwgxsI = false;
      string PbZzXOXZzW;
      string mmASGrgrVn;
      string sxbzesLici;
      string pOtJXSsuwp;
      string fRRLooSEoU;
      string VkPzERAaUe;
      string DowQgXrqtm;
      string ykwfHbfQJo;
      string aHsHMFzuFG;
      string SRaRmqUBeQ;
      string waJCWjoirb;
      string ljReDuunDb;
      string XxlnUfKdsP;
      string Gekrrzyqkc;
      string PPDcThAuNq;
      string wgyDsyoUgp;
      string ZKpbVHyYlE;
      string wEDZLHtIUl;
      string fOQBTZfhzs;
      string JcJuCEZaGM;
      if(PbZzXOXZzW == waJCWjoirb){jbIJtqcXqk = true;}
      else if(waJCWjoirb == PbZzXOXZzW){yjVdkVCkJS = true;}
      if(mmASGrgrVn == ljReDuunDb){DgAuKLtoIw = true;}
      else if(ljReDuunDb == mmASGrgrVn){urMyiQyTlE = true;}
      if(sxbzesLici == XxlnUfKdsP){aPYstTtHXH = true;}
      else if(XxlnUfKdsP == sxbzesLici){hlVKFQwCBY = true;}
      if(pOtJXSsuwp == Gekrrzyqkc){hTCICDFGGb = true;}
      else if(Gekrrzyqkc == pOtJXSsuwp){IRyxSHJrta = true;}
      if(fRRLooSEoU == PPDcThAuNq){wIqOocbOkq = true;}
      else if(PPDcThAuNq == fRRLooSEoU){uQhDlIbswO = true;}
      if(VkPzERAaUe == wgyDsyoUgp){JjRKkTCPPa = true;}
      else if(wgyDsyoUgp == VkPzERAaUe){bnUHXMNKYU = true;}
      if(DowQgXrqtm == ZKpbVHyYlE){wVAjCjdrsG = true;}
      else if(ZKpbVHyYlE == DowQgXrqtm){YzjkJdsOeb = true;}
      if(ykwfHbfQJo == wEDZLHtIUl){FnhgARYKDQ = true;}
      if(aHsHMFzuFG == fOQBTZfhzs){qfWfxxCrWh = true;}
      if(SRaRmqUBeQ == JcJuCEZaGM){AoqfeaIHLF = true;}
      while(wEDZLHtIUl == ykwfHbfQJo){GGZKIQERYx = true;}
      while(fOQBTZfhzs == fOQBTZfhzs){nDFlxUwqZF = true;}
      while(JcJuCEZaGM == JcJuCEZaGM){szTYCwgxsI = true;}
      if(jbIJtqcXqk == true){jbIJtqcXqk = false;}
      if(DgAuKLtoIw == true){DgAuKLtoIw = false;}
      if(aPYstTtHXH == true){aPYstTtHXH = false;}
      if(hTCICDFGGb == true){hTCICDFGGb = false;}
      if(wIqOocbOkq == true){wIqOocbOkq = false;}
      if(JjRKkTCPPa == true){JjRKkTCPPa = false;}
      if(wVAjCjdrsG == true){wVAjCjdrsG = false;}
      if(FnhgARYKDQ == true){FnhgARYKDQ = false;}
      if(qfWfxxCrWh == true){qfWfxxCrWh = false;}
      if(AoqfeaIHLF == true){AoqfeaIHLF = false;}
      if(yjVdkVCkJS == true){yjVdkVCkJS = false;}
      if(urMyiQyTlE == true){urMyiQyTlE = false;}
      if(hlVKFQwCBY == true){hlVKFQwCBY = false;}
      if(IRyxSHJrta == true){IRyxSHJrta = false;}
      if(uQhDlIbswO == true){uQhDlIbswO = false;}
      if(bnUHXMNKYU == true){bnUHXMNKYU = false;}
      if(YzjkJdsOeb == true){YzjkJdsOeb = false;}
      if(GGZKIQERYx == true){GGZKIQERYx = false;}
      if(nDFlxUwqZF == true){nDFlxUwqZF = false;}
      if(szTYCwgxsI == true){szTYCwgxsI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NTBGUUKYUI
{ 
  void nySlADqXeQ()
  { 
      bool iZcOppjqgz = false;
      bool ahaAaKtxqy = false;
      bool QaDrXJDehL = false;
      bool JWkEWXqjYi = false;
      bool aNJtwtdFDV = false;
      bool LjxMHIWjpf = false;
      bool lFIUoEwWdC = false;
      bool SJXIWCQIwd = false;
      bool eyaLzZYYwN = false;
      bool BHtrwVEoFq = false;
      bool xHbBDBMooE = false;
      bool qOmLBndwUP = false;
      bool eWZPBLPfMB = false;
      bool xbCFfXWZIx = false;
      bool NjjqWmUhpH = false;
      bool rHTpMagLAq = false;
      bool lfcmGOLhed = false;
      bool REnXBulhrN = false;
      bool phoEIoIMrF = false;
      bool pKZQLgGxkH = false;
      string NJpLLLxVxU;
      string LsJklVgQiO;
      string WtuxZBDBNV;
      string xBhIqWxCgk;
      string RNFokNyTcR;
      string UqcmYTNskK;
      string HuHaXJLBsP;
      string YdjxwJnGLL;
      string DiYwBGYujX;
      string IDRVcWFeQa;
      string CwZMspGepO;
      string eHgYHYVLYR;
      string kPRVGUMNTZ;
      string EJpjJGJMCK;
      string zsEUsBWrOE;
      string AsFzpleDGY;
      string dsLQJURwPA;
      string OJJORqLwcF;
      string xTyOYLEpsW;
      string bFFdfGgnKX;
      if(NJpLLLxVxU == CwZMspGepO){iZcOppjqgz = true;}
      else if(CwZMspGepO == NJpLLLxVxU){xHbBDBMooE = true;}
      if(LsJklVgQiO == eHgYHYVLYR){ahaAaKtxqy = true;}
      else if(eHgYHYVLYR == LsJklVgQiO){qOmLBndwUP = true;}
      if(WtuxZBDBNV == kPRVGUMNTZ){QaDrXJDehL = true;}
      else if(kPRVGUMNTZ == WtuxZBDBNV){eWZPBLPfMB = true;}
      if(xBhIqWxCgk == EJpjJGJMCK){JWkEWXqjYi = true;}
      else if(EJpjJGJMCK == xBhIqWxCgk){xbCFfXWZIx = true;}
      if(RNFokNyTcR == zsEUsBWrOE){aNJtwtdFDV = true;}
      else if(zsEUsBWrOE == RNFokNyTcR){NjjqWmUhpH = true;}
      if(UqcmYTNskK == AsFzpleDGY){LjxMHIWjpf = true;}
      else if(AsFzpleDGY == UqcmYTNskK){rHTpMagLAq = true;}
      if(HuHaXJLBsP == dsLQJURwPA){lFIUoEwWdC = true;}
      else if(dsLQJURwPA == HuHaXJLBsP){lfcmGOLhed = true;}
      if(YdjxwJnGLL == OJJORqLwcF){SJXIWCQIwd = true;}
      if(DiYwBGYujX == xTyOYLEpsW){eyaLzZYYwN = true;}
      if(IDRVcWFeQa == bFFdfGgnKX){BHtrwVEoFq = true;}
      while(OJJORqLwcF == YdjxwJnGLL){REnXBulhrN = true;}
      while(xTyOYLEpsW == xTyOYLEpsW){phoEIoIMrF = true;}
      while(bFFdfGgnKX == bFFdfGgnKX){pKZQLgGxkH = true;}
      if(iZcOppjqgz == true){iZcOppjqgz = false;}
      if(ahaAaKtxqy == true){ahaAaKtxqy = false;}
      if(QaDrXJDehL == true){QaDrXJDehL = false;}
      if(JWkEWXqjYi == true){JWkEWXqjYi = false;}
      if(aNJtwtdFDV == true){aNJtwtdFDV = false;}
      if(LjxMHIWjpf == true){LjxMHIWjpf = false;}
      if(lFIUoEwWdC == true){lFIUoEwWdC = false;}
      if(SJXIWCQIwd == true){SJXIWCQIwd = false;}
      if(eyaLzZYYwN == true){eyaLzZYYwN = false;}
      if(BHtrwVEoFq == true){BHtrwVEoFq = false;}
      if(xHbBDBMooE == true){xHbBDBMooE = false;}
      if(qOmLBndwUP == true){qOmLBndwUP = false;}
      if(eWZPBLPfMB == true){eWZPBLPfMB = false;}
      if(xbCFfXWZIx == true){xbCFfXWZIx = false;}
      if(NjjqWmUhpH == true){NjjqWmUhpH = false;}
      if(rHTpMagLAq == true){rHTpMagLAq = false;}
      if(lfcmGOLhed == true){lfcmGOLhed = false;}
      if(REnXBulhrN == true){REnXBulhrN = false;}
      if(phoEIoIMrF == true){phoEIoIMrF = false;}
      if(pKZQLgGxkH == true){pKZQLgGxkH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XODMBIMNON
{ 
  void ZtUSlUccsX()
  { 
      bool aqNDzhleBK = false;
      bool ZmLcHxzUAh = false;
      bool stBYnVsiWs = false;
      bool QVPpfsKttf = false;
      bool gmdGJuRjrL = false;
      bool PenZwgooPd = false;
      bool nDHIsDWVxN = false;
      bool lEaTBGPtOs = false;
      bool DIqKckhpsy = false;
      bool DVeQrceVNF = false;
      bool XwmdYKETYp = false;
      bool RuaWZeMwfI = false;
      bool VgczJQZJbX = false;
      bool atgIUHVMkR = false;
      bool fNQCfIuIqM = false;
      bool QipEjpTnTI = false;
      bool kurAPXNRBR = false;
      bool JzKNbIPZSB = false;
      bool VQSOHqDbYd = false;
      bool mhrcfkVQmI = false;
      string cDcOLDHeaf;
      string zeCCfxCIwr;
      string dlOPMJoKcO;
      string XtqWfGhEsi;
      string rujpNoXuSA;
      string QlVSXpnMCC;
      string OxBLIFneWZ;
      string OyONzhBXBW;
      string lsqbykXXyo;
      string RUBpTutYhI;
      string BrYskSWITo;
      string nPLeQUFYMW;
      string gPggIswYsE;
      string ncpsVsUyqf;
      string OPEIBBJWZz;
      string oULKbkKqjq;
      string WyOPBKZSIW;
      string zHhgIRLXfH;
      string jYytOTRfQj;
      string hdNzJPAoHp;
      if(cDcOLDHeaf == BrYskSWITo){aqNDzhleBK = true;}
      else if(BrYskSWITo == cDcOLDHeaf){XwmdYKETYp = true;}
      if(zeCCfxCIwr == nPLeQUFYMW){ZmLcHxzUAh = true;}
      else if(nPLeQUFYMW == zeCCfxCIwr){RuaWZeMwfI = true;}
      if(dlOPMJoKcO == gPggIswYsE){stBYnVsiWs = true;}
      else if(gPggIswYsE == dlOPMJoKcO){VgczJQZJbX = true;}
      if(XtqWfGhEsi == ncpsVsUyqf){QVPpfsKttf = true;}
      else if(ncpsVsUyqf == XtqWfGhEsi){atgIUHVMkR = true;}
      if(rujpNoXuSA == OPEIBBJWZz){gmdGJuRjrL = true;}
      else if(OPEIBBJWZz == rujpNoXuSA){fNQCfIuIqM = true;}
      if(QlVSXpnMCC == oULKbkKqjq){PenZwgooPd = true;}
      else if(oULKbkKqjq == QlVSXpnMCC){QipEjpTnTI = true;}
      if(OxBLIFneWZ == WyOPBKZSIW){nDHIsDWVxN = true;}
      else if(WyOPBKZSIW == OxBLIFneWZ){kurAPXNRBR = true;}
      if(OyONzhBXBW == zHhgIRLXfH){lEaTBGPtOs = true;}
      if(lsqbykXXyo == jYytOTRfQj){DIqKckhpsy = true;}
      if(RUBpTutYhI == hdNzJPAoHp){DVeQrceVNF = true;}
      while(zHhgIRLXfH == OyONzhBXBW){JzKNbIPZSB = true;}
      while(jYytOTRfQj == jYytOTRfQj){VQSOHqDbYd = true;}
      while(hdNzJPAoHp == hdNzJPAoHp){mhrcfkVQmI = true;}
      if(aqNDzhleBK == true){aqNDzhleBK = false;}
      if(ZmLcHxzUAh == true){ZmLcHxzUAh = false;}
      if(stBYnVsiWs == true){stBYnVsiWs = false;}
      if(QVPpfsKttf == true){QVPpfsKttf = false;}
      if(gmdGJuRjrL == true){gmdGJuRjrL = false;}
      if(PenZwgooPd == true){PenZwgooPd = false;}
      if(nDHIsDWVxN == true){nDHIsDWVxN = false;}
      if(lEaTBGPtOs == true){lEaTBGPtOs = false;}
      if(DIqKckhpsy == true){DIqKckhpsy = false;}
      if(DVeQrceVNF == true){DVeQrceVNF = false;}
      if(XwmdYKETYp == true){XwmdYKETYp = false;}
      if(RuaWZeMwfI == true){RuaWZeMwfI = false;}
      if(VgczJQZJbX == true){VgczJQZJbX = false;}
      if(atgIUHVMkR == true){atgIUHVMkR = false;}
      if(fNQCfIuIqM == true){fNQCfIuIqM = false;}
      if(QipEjpTnTI == true){QipEjpTnTI = false;}
      if(kurAPXNRBR == true){kurAPXNRBR = false;}
      if(JzKNbIPZSB == true){JzKNbIPZSB = false;}
      if(VQSOHqDbYd == true){VQSOHqDbYd = false;}
      if(mhrcfkVQmI == true){mhrcfkVQmI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TSRNGDJTKZ
{ 
  void katgUPXZFh()
  { 
      bool ZtklSjlXTn = false;
      bool fibyjPfghO = false;
      bool RpLBtBpPTa = false;
      bool gJOhhoQsFK = false;
      bool HiykNjImGP = false;
      bool ADmjtiijqQ = false;
      bool tWErHVUtQt = false;
      bool ylaXHiranK = false;
      bool sCIEacWdmy = false;
      bool GgCoPjdGcq = false;
      bool PNWLRNcPbL = false;
      bool qHwgWqNzQd = false;
      bool zpHRnQjkHW = false;
      bool EkxwtefxmN = false;
      bool AGBaHykVSX = false;
      bool WepzrZGEXA = false;
      bool dqIFHFKzlq = false;
      bool LQMCcsnfKp = false;
      bool eNSizYuyEU = false;
      bool YaZljJxwSB = false;
      string EGpylZVEEZ;
      string HcVCjUpCWi;
      string QGigCZZMsL;
      string ndNwjIGbqx;
      string rUKNoFqSWy;
      string ODHcrxXJwM;
      string zJLrkcPZRa;
      string NOLZqwwVqw;
      string hHotxkWkEl;
      string kxfexhJRbL;
      string pRAwjArhlw;
      string BCRAdrUQuA;
      string GeVepQhfcI;
      string mdsfFPGrKw;
      string royIjhffAE;
      string NrWaFLwVGT;
      string RLEcJXIktO;
      string lcGyHQfNtH;
      string jCfXutGRZs;
      string TjlpefjVyM;
      if(EGpylZVEEZ == pRAwjArhlw){ZtklSjlXTn = true;}
      else if(pRAwjArhlw == EGpylZVEEZ){PNWLRNcPbL = true;}
      if(HcVCjUpCWi == BCRAdrUQuA){fibyjPfghO = true;}
      else if(BCRAdrUQuA == HcVCjUpCWi){qHwgWqNzQd = true;}
      if(QGigCZZMsL == GeVepQhfcI){RpLBtBpPTa = true;}
      else if(GeVepQhfcI == QGigCZZMsL){zpHRnQjkHW = true;}
      if(ndNwjIGbqx == mdsfFPGrKw){gJOhhoQsFK = true;}
      else if(mdsfFPGrKw == ndNwjIGbqx){EkxwtefxmN = true;}
      if(rUKNoFqSWy == royIjhffAE){HiykNjImGP = true;}
      else if(royIjhffAE == rUKNoFqSWy){AGBaHykVSX = true;}
      if(ODHcrxXJwM == NrWaFLwVGT){ADmjtiijqQ = true;}
      else if(NrWaFLwVGT == ODHcrxXJwM){WepzrZGEXA = true;}
      if(zJLrkcPZRa == RLEcJXIktO){tWErHVUtQt = true;}
      else if(RLEcJXIktO == zJLrkcPZRa){dqIFHFKzlq = true;}
      if(NOLZqwwVqw == lcGyHQfNtH){ylaXHiranK = true;}
      if(hHotxkWkEl == jCfXutGRZs){sCIEacWdmy = true;}
      if(kxfexhJRbL == TjlpefjVyM){GgCoPjdGcq = true;}
      while(lcGyHQfNtH == NOLZqwwVqw){LQMCcsnfKp = true;}
      while(jCfXutGRZs == jCfXutGRZs){eNSizYuyEU = true;}
      while(TjlpefjVyM == TjlpefjVyM){YaZljJxwSB = true;}
      if(ZtklSjlXTn == true){ZtklSjlXTn = false;}
      if(fibyjPfghO == true){fibyjPfghO = false;}
      if(RpLBtBpPTa == true){RpLBtBpPTa = false;}
      if(gJOhhoQsFK == true){gJOhhoQsFK = false;}
      if(HiykNjImGP == true){HiykNjImGP = false;}
      if(ADmjtiijqQ == true){ADmjtiijqQ = false;}
      if(tWErHVUtQt == true){tWErHVUtQt = false;}
      if(ylaXHiranK == true){ylaXHiranK = false;}
      if(sCIEacWdmy == true){sCIEacWdmy = false;}
      if(GgCoPjdGcq == true){GgCoPjdGcq = false;}
      if(PNWLRNcPbL == true){PNWLRNcPbL = false;}
      if(qHwgWqNzQd == true){qHwgWqNzQd = false;}
      if(zpHRnQjkHW == true){zpHRnQjkHW = false;}
      if(EkxwtefxmN == true){EkxwtefxmN = false;}
      if(AGBaHykVSX == true){AGBaHykVSX = false;}
      if(WepzrZGEXA == true){WepzrZGEXA = false;}
      if(dqIFHFKzlq == true){dqIFHFKzlq = false;}
      if(LQMCcsnfKp == true){LQMCcsnfKp = false;}
      if(eNSizYuyEU == true){eNSizYuyEU = false;}
      if(YaZljJxwSB == true){YaZljJxwSB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TPFTKMWLDL
{ 
  void nOdZaDOCpD()
  { 
      bool VWRSyzmGno = false;
      bool AnOFLGxaWO = false;
      bool SPorDijILH = false;
      bool lnhmeEtwHT = false;
      bool XClkhbOIKS = false;
      bool xkkPaFhZPO = false;
      bool PetgDMGaaH = false;
      bool MATCpPdEKa = false;
      bool UaxsJADSMZ = false;
      bool VUgsEsIEgV = false;
      bool VnhDGxRhYK = false;
      bool acOnsngBXD = false;
      bool JmNBkrSayx = false;
      bool HYWoFgstlM = false;
      bool hUsBysFszQ = false;
      bool LGgcMhZgRN = false;
      bool dpjbDBFZiM = false;
      bool ulOKVnsLCr = false;
      bool mZbgkAqtbW = false;
      bool GLcYhrjRyw = false;
      string wSqAzZmprr;
      string nsZDSWmVPz;
      string tswPTcShpu;
      string MCrACorguD;
      string THTfTtrxwf;
      string doKmqDWagW;
      string GEzwfkBZAd;
      string eFaMflZPwY;
      string jVlKQWrFIy;
      string RQAYwPHXzh;
      string sSxRAYOxGE;
      string dGdHlkRoeJ;
      string suQBLNFCQQ;
      string dCPOfRXTJr;
      string HtyEULlslK;
      string xSrpnxBuFm;
      string SMgpZbpPaT;
      string MyelCywMgA;
      string aMPFSLJZZh;
      string QcNWZuMIds;
      if(wSqAzZmprr == sSxRAYOxGE){VWRSyzmGno = true;}
      else if(sSxRAYOxGE == wSqAzZmprr){VnhDGxRhYK = true;}
      if(nsZDSWmVPz == dGdHlkRoeJ){AnOFLGxaWO = true;}
      else if(dGdHlkRoeJ == nsZDSWmVPz){acOnsngBXD = true;}
      if(tswPTcShpu == suQBLNFCQQ){SPorDijILH = true;}
      else if(suQBLNFCQQ == tswPTcShpu){JmNBkrSayx = true;}
      if(MCrACorguD == dCPOfRXTJr){lnhmeEtwHT = true;}
      else if(dCPOfRXTJr == MCrACorguD){HYWoFgstlM = true;}
      if(THTfTtrxwf == HtyEULlslK){XClkhbOIKS = true;}
      else if(HtyEULlslK == THTfTtrxwf){hUsBysFszQ = true;}
      if(doKmqDWagW == xSrpnxBuFm){xkkPaFhZPO = true;}
      else if(xSrpnxBuFm == doKmqDWagW){LGgcMhZgRN = true;}
      if(GEzwfkBZAd == SMgpZbpPaT){PetgDMGaaH = true;}
      else if(SMgpZbpPaT == GEzwfkBZAd){dpjbDBFZiM = true;}
      if(eFaMflZPwY == MyelCywMgA){MATCpPdEKa = true;}
      if(jVlKQWrFIy == aMPFSLJZZh){UaxsJADSMZ = true;}
      if(RQAYwPHXzh == QcNWZuMIds){VUgsEsIEgV = true;}
      while(MyelCywMgA == eFaMflZPwY){ulOKVnsLCr = true;}
      while(aMPFSLJZZh == aMPFSLJZZh){mZbgkAqtbW = true;}
      while(QcNWZuMIds == QcNWZuMIds){GLcYhrjRyw = true;}
      if(VWRSyzmGno == true){VWRSyzmGno = false;}
      if(AnOFLGxaWO == true){AnOFLGxaWO = false;}
      if(SPorDijILH == true){SPorDijILH = false;}
      if(lnhmeEtwHT == true){lnhmeEtwHT = false;}
      if(XClkhbOIKS == true){XClkhbOIKS = false;}
      if(xkkPaFhZPO == true){xkkPaFhZPO = false;}
      if(PetgDMGaaH == true){PetgDMGaaH = false;}
      if(MATCpPdEKa == true){MATCpPdEKa = false;}
      if(UaxsJADSMZ == true){UaxsJADSMZ = false;}
      if(VUgsEsIEgV == true){VUgsEsIEgV = false;}
      if(VnhDGxRhYK == true){VnhDGxRhYK = false;}
      if(acOnsngBXD == true){acOnsngBXD = false;}
      if(JmNBkrSayx == true){JmNBkrSayx = false;}
      if(HYWoFgstlM == true){HYWoFgstlM = false;}
      if(hUsBysFszQ == true){hUsBysFszQ = false;}
      if(LGgcMhZgRN == true){LGgcMhZgRN = false;}
      if(dpjbDBFZiM == true){dpjbDBFZiM = false;}
      if(ulOKVnsLCr == true){ulOKVnsLCr = false;}
      if(mZbgkAqtbW == true){mZbgkAqtbW = false;}
      if(GLcYhrjRyw == true){GLcYhrjRyw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OTNSMTZDGY
{ 
  void DbRkxhBTfX()
  { 
      bool CZsJkaIRtY = false;
      bool sRoZzmZOKQ = false;
      bool UusBoFqdmL = false;
      bool JyuhnuUgHt = false;
      bool ZgoeOWNgWU = false;
      bool cbLtoGgqTe = false;
      bool jediOtWGlD = false;
      bool RrGPqnFOmR = false;
      bool qJGSigmAsg = false;
      bool OcMbJtDGPU = false;
      bool AHtSCjVuDA = false;
      bool ASECnZXKzg = false;
      bool HWMEonfdFw = false;
      bool kyyRRjOnQz = false;
      bool LqwsgwYKnj = false;
      bool WrHhNcupdN = false;
      bool DqoGPBTljD = false;
      bool KisAVPZSXr = false;
      bool PVoVZrqQEn = false;
      bool oYKDuUBpce = false;
      string ZVdaBFMpYI;
      string ryrupDUgnW;
      string bTPHoHYdzt;
      string PFybOLRTXR;
      string dnshJjFjRx;
      string TDPTbFFWks;
      string ghqdsmAQfd;
      string lAIWrmagyF;
      string CnLBaMpdzJ;
      string FtiekwxPoV;
      string joEnLStrbo;
      string eXYfqrVoDf;
      string xVQWXqRdku;
      string pKrbVMjXpI;
      string SxBKdhVDmr;
      string ZHMIYNXgQT;
      string APGfyTfwJd;
      string HyztNzUGrp;
      string UNprVhyjDH;
      string oCHVHCpVLJ;
      if(ZVdaBFMpYI == joEnLStrbo){CZsJkaIRtY = true;}
      else if(joEnLStrbo == ZVdaBFMpYI){AHtSCjVuDA = true;}
      if(ryrupDUgnW == eXYfqrVoDf){sRoZzmZOKQ = true;}
      else if(eXYfqrVoDf == ryrupDUgnW){ASECnZXKzg = true;}
      if(bTPHoHYdzt == xVQWXqRdku){UusBoFqdmL = true;}
      else if(xVQWXqRdku == bTPHoHYdzt){HWMEonfdFw = true;}
      if(PFybOLRTXR == pKrbVMjXpI){JyuhnuUgHt = true;}
      else if(pKrbVMjXpI == PFybOLRTXR){kyyRRjOnQz = true;}
      if(dnshJjFjRx == SxBKdhVDmr){ZgoeOWNgWU = true;}
      else if(SxBKdhVDmr == dnshJjFjRx){LqwsgwYKnj = true;}
      if(TDPTbFFWks == ZHMIYNXgQT){cbLtoGgqTe = true;}
      else if(ZHMIYNXgQT == TDPTbFFWks){WrHhNcupdN = true;}
      if(ghqdsmAQfd == APGfyTfwJd){jediOtWGlD = true;}
      else if(APGfyTfwJd == ghqdsmAQfd){DqoGPBTljD = true;}
      if(lAIWrmagyF == HyztNzUGrp){RrGPqnFOmR = true;}
      if(CnLBaMpdzJ == UNprVhyjDH){qJGSigmAsg = true;}
      if(FtiekwxPoV == oCHVHCpVLJ){OcMbJtDGPU = true;}
      while(HyztNzUGrp == lAIWrmagyF){KisAVPZSXr = true;}
      while(UNprVhyjDH == UNprVhyjDH){PVoVZrqQEn = true;}
      while(oCHVHCpVLJ == oCHVHCpVLJ){oYKDuUBpce = true;}
      if(CZsJkaIRtY == true){CZsJkaIRtY = false;}
      if(sRoZzmZOKQ == true){sRoZzmZOKQ = false;}
      if(UusBoFqdmL == true){UusBoFqdmL = false;}
      if(JyuhnuUgHt == true){JyuhnuUgHt = false;}
      if(ZgoeOWNgWU == true){ZgoeOWNgWU = false;}
      if(cbLtoGgqTe == true){cbLtoGgqTe = false;}
      if(jediOtWGlD == true){jediOtWGlD = false;}
      if(RrGPqnFOmR == true){RrGPqnFOmR = false;}
      if(qJGSigmAsg == true){qJGSigmAsg = false;}
      if(OcMbJtDGPU == true){OcMbJtDGPU = false;}
      if(AHtSCjVuDA == true){AHtSCjVuDA = false;}
      if(ASECnZXKzg == true){ASECnZXKzg = false;}
      if(HWMEonfdFw == true){HWMEonfdFw = false;}
      if(kyyRRjOnQz == true){kyyRRjOnQz = false;}
      if(LqwsgwYKnj == true){LqwsgwYKnj = false;}
      if(WrHhNcupdN == true){WrHhNcupdN = false;}
      if(DqoGPBTljD == true){DqoGPBTljD = false;}
      if(KisAVPZSXr == true){KisAVPZSXr = false;}
      if(PVoVZrqQEn == true){PVoVZrqQEn = false;}
      if(oYKDuUBpce == true){oYKDuUBpce = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CKWIPFUSYR
{ 
  void KuGawAUSWx()
  { 
      bool rGiHJrVloG = false;
      bool kGeFUiYCjI = false;
      bool yCpwwBAczy = false;
      bool CTyEKlnBGQ = false;
      bool tEyopfXOeL = false;
      bool nuJBboQlLI = false;
      bool qrmpEQHZth = false;
      bool uWuTNsDAFP = false;
      bool clxmJGKwbU = false;
      bool UBpxYBRHjZ = false;
      bool XxUxQRzomi = false;
      bool lQfufFuzgx = false;
      bool FLyYNtfyuL = false;
      bool buPfreQAWq = false;
      bool HUJsiEUuRS = false;
      bool GRamTMzuiV = false;
      bool kBtbGpAACA = false;
      bool oucookCEoI = false;
      bool YjfbEJUcLf = false;
      bool eVQAGGZgls = false;
      string iDoNCmhpCQ;
      string FLaRePXhjP;
      string DTgakQzNiP;
      string haEPshujJV;
      string gyQnBINeqT;
      string ZFMAsPWObk;
      string mUGmheGKYx;
      string TmXNiFCsZc;
      string CUWOocOEVc;
      string LgHYhLqdFW;
      string BDGsAlhyQn;
      string NcnzhSyrxF;
      string PCouklezeW;
      string OXmCazNcOC;
      string uPnhPhsHpO;
      string NygzGzNKIN;
      string HhSsYoplYh;
      string EUctKzOHeD;
      string sXJQJQqmwb;
      string lDUAuMxtJa;
      if(iDoNCmhpCQ == BDGsAlhyQn){rGiHJrVloG = true;}
      else if(BDGsAlhyQn == iDoNCmhpCQ){XxUxQRzomi = true;}
      if(FLaRePXhjP == NcnzhSyrxF){kGeFUiYCjI = true;}
      else if(NcnzhSyrxF == FLaRePXhjP){lQfufFuzgx = true;}
      if(DTgakQzNiP == PCouklezeW){yCpwwBAczy = true;}
      else if(PCouklezeW == DTgakQzNiP){FLyYNtfyuL = true;}
      if(haEPshujJV == OXmCazNcOC){CTyEKlnBGQ = true;}
      else if(OXmCazNcOC == haEPshujJV){buPfreQAWq = true;}
      if(gyQnBINeqT == uPnhPhsHpO){tEyopfXOeL = true;}
      else if(uPnhPhsHpO == gyQnBINeqT){HUJsiEUuRS = true;}
      if(ZFMAsPWObk == NygzGzNKIN){nuJBboQlLI = true;}
      else if(NygzGzNKIN == ZFMAsPWObk){GRamTMzuiV = true;}
      if(mUGmheGKYx == HhSsYoplYh){qrmpEQHZth = true;}
      else if(HhSsYoplYh == mUGmheGKYx){kBtbGpAACA = true;}
      if(TmXNiFCsZc == EUctKzOHeD){uWuTNsDAFP = true;}
      if(CUWOocOEVc == sXJQJQqmwb){clxmJGKwbU = true;}
      if(LgHYhLqdFW == lDUAuMxtJa){UBpxYBRHjZ = true;}
      while(EUctKzOHeD == TmXNiFCsZc){oucookCEoI = true;}
      while(sXJQJQqmwb == sXJQJQqmwb){YjfbEJUcLf = true;}
      while(lDUAuMxtJa == lDUAuMxtJa){eVQAGGZgls = true;}
      if(rGiHJrVloG == true){rGiHJrVloG = false;}
      if(kGeFUiYCjI == true){kGeFUiYCjI = false;}
      if(yCpwwBAczy == true){yCpwwBAczy = false;}
      if(CTyEKlnBGQ == true){CTyEKlnBGQ = false;}
      if(tEyopfXOeL == true){tEyopfXOeL = false;}
      if(nuJBboQlLI == true){nuJBboQlLI = false;}
      if(qrmpEQHZth == true){qrmpEQHZth = false;}
      if(uWuTNsDAFP == true){uWuTNsDAFP = false;}
      if(clxmJGKwbU == true){clxmJGKwbU = false;}
      if(UBpxYBRHjZ == true){UBpxYBRHjZ = false;}
      if(XxUxQRzomi == true){XxUxQRzomi = false;}
      if(lQfufFuzgx == true){lQfufFuzgx = false;}
      if(FLyYNtfyuL == true){FLyYNtfyuL = false;}
      if(buPfreQAWq == true){buPfreQAWq = false;}
      if(HUJsiEUuRS == true){HUJsiEUuRS = false;}
      if(GRamTMzuiV == true){GRamTMzuiV = false;}
      if(kBtbGpAACA == true){kBtbGpAACA = false;}
      if(oucookCEoI == true){oucookCEoI = false;}
      if(YjfbEJUcLf == true){YjfbEJUcLf = false;}
      if(eVQAGGZgls == true){eVQAGGZgls = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FNJQBNJFQH
{ 
  void aGSHWdNBOc()
  { 
      bool gjpGQYHEnW = false;
      bool QzPkcFKpkK = false;
      bool xrxXQBVLbN = false;
      bool IMApiBBFVY = false;
      bool YUrVYQehEA = false;
      bool nylhmomRpP = false;
      bool CwcZNEzZCb = false;
      bool EETMlczazz = false;
      bool VnGaZJaSDs = false;
      bool OiPFVbqSHU = false;
      bool RFfcwidZuJ = false;
      bool pLSptOoBzD = false;
      bool cgVIMUoOpJ = false;
      bool kgSdhPIdeq = false;
      bool eBWsDDQZLH = false;
      bool moSErjiWQa = false;
      bool sPilYJroHd = false;
      bool FLWIXbJcEI = false;
      bool EPChWuNOlx = false;
      bool fkMDxORkUt = false;
      string ToJJDuHBoS;
      string qexgLTFZiQ;
      string jzVFUjEBlB;
      string rZkKJdgywl;
      string eIMHElGuGN;
      string BAahBUSEnS;
      string qFPmZQtlWh;
      string mGcwlalOBi;
      string cJtXzryDJo;
      string KbJcuYsZhm;
      string rUXYZuWewZ;
      string hEDFohKqmh;
      string RqcgWKwzBM;
      string hLfNqIkVxE;
      string UTGjGFYEmN;
      string OBmAUArpCP;
      string yWdiqWXoOg;
      string woshMyjraQ;
      string lrMmyfYfrp;
      string QuShGyoWrj;
      if(ToJJDuHBoS == rUXYZuWewZ){gjpGQYHEnW = true;}
      else if(rUXYZuWewZ == ToJJDuHBoS){RFfcwidZuJ = true;}
      if(qexgLTFZiQ == hEDFohKqmh){QzPkcFKpkK = true;}
      else if(hEDFohKqmh == qexgLTFZiQ){pLSptOoBzD = true;}
      if(jzVFUjEBlB == RqcgWKwzBM){xrxXQBVLbN = true;}
      else if(RqcgWKwzBM == jzVFUjEBlB){cgVIMUoOpJ = true;}
      if(rZkKJdgywl == hLfNqIkVxE){IMApiBBFVY = true;}
      else if(hLfNqIkVxE == rZkKJdgywl){kgSdhPIdeq = true;}
      if(eIMHElGuGN == UTGjGFYEmN){YUrVYQehEA = true;}
      else if(UTGjGFYEmN == eIMHElGuGN){eBWsDDQZLH = true;}
      if(BAahBUSEnS == OBmAUArpCP){nylhmomRpP = true;}
      else if(OBmAUArpCP == BAahBUSEnS){moSErjiWQa = true;}
      if(qFPmZQtlWh == yWdiqWXoOg){CwcZNEzZCb = true;}
      else if(yWdiqWXoOg == qFPmZQtlWh){sPilYJroHd = true;}
      if(mGcwlalOBi == woshMyjraQ){EETMlczazz = true;}
      if(cJtXzryDJo == lrMmyfYfrp){VnGaZJaSDs = true;}
      if(KbJcuYsZhm == QuShGyoWrj){OiPFVbqSHU = true;}
      while(woshMyjraQ == mGcwlalOBi){FLWIXbJcEI = true;}
      while(lrMmyfYfrp == lrMmyfYfrp){EPChWuNOlx = true;}
      while(QuShGyoWrj == QuShGyoWrj){fkMDxORkUt = true;}
      if(gjpGQYHEnW == true){gjpGQYHEnW = false;}
      if(QzPkcFKpkK == true){QzPkcFKpkK = false;}
      if(xrxXQBVLbN == true){xrxXQBVLbN = false;}
      if(IMApiBBFVY == true){IMApiBBFVY = false;}
      if(YUrVYQehEA == true){YUrVYQehEA = false;}
      if(nylhmomRpP == true){nylhmomRpP = false;}
      if(CwcZNEzZCb == true){CwcZNEzZCb = false;}
      if(EETMlczazz == true){EETMlczazz = false;}
      if(VnGaZJaSDs == true){VnGaZJaSDs = false;}
      if(OiPFVbqSHU == true){OiPFVbqSHU = false;}
      if(RFfcwidZuJ == true){RFfcwidZuJ = false;}
      if(pLSptOoBzD == true){pLSptOoBzD = false;}
      if(cgVIMUoOpJ == true){cgVIMUoOpJ = false;}
      if(kgSdhPIdeq == true){kgSdhPIdeq = false;}
      if(eBWsDDQZLH == true){eBWsDDQZLH = false;}
      if(moSErjiWQa == true){moSErjiWQa = false;}
      if(sPilYJroHd == true){sPilYJroHd = false;}
      if(FLWIXbJcEI == true){FLWIXbJcEI = false;}
      if(EPChWuNOlx == true){EPChWuNOlx = false;}
      if(fkMDxORkUt == true){fkMDxORkUt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ARKJKUMGVL
{ 
  void JRgkrFNGnK()
  { 
      bool FffnHeMedj = false;
      bool cropJfKwFj = false;
      bool EZfJqkHXGa = false;
      bool acBGinHUPO = false;
      bool PafWhtTbYG = false;
      bool HcwJMezWwV = false;
      bool XoXCJzpiHV = false;
      bool YpfqTdtIax = false;
      bool RfyATxfrtD = false;
      bool njXsqaCcNi = false;
      bool DjUChQxFoi = false;
      bool kqwyEqpXiL = false;
      bool SyoDgnSlzr = false;
      bool aQurtgLuSC = false;
      bool AaCLSxnYoA = false;
      bool jesCPEuQVs = false;
      bool yKGxHTwEEW = false;
      bool etFgKrudjj = false;
      bool AsxzIwXrbo = false;
      bool ltZZDpTFDy = false;
      string iPxpjKwfTk;
      string IWSUJzUkOs;
      string LrHopRJNkD;
      string XZjDGSJpnU;
      string OeoSOdDaCH;
      string mqmfoqIHAR;
      string AiuPNhmPOp;
      string oewsefDnZL;
      string NiKcPgmDOP;
      string KBpVTejYFg;
      string qnMLRItsAI;
      string nThnDRYRAg;
      string tiAyfnoaZA;
      string udisTZWyLG;
      string lsCFapTBRC;
      string FSYYlImNfd;
      string TTTAMJknUd;
      string tZFstBftXo;
      string TmIXtcFKHL;
      string lJShmSZCsQ;
      if(iPxpjKwfTk == qnMLRItsAI){FffnHeMedj = true;}
      else if(qnMLRItsAI == iPxpjKwfTk){DjUChQxFoi = true;}
      if(IWSUJzUkOs == nThnDRYRAg){cropJfKwFj = true;}
      else if(nThnDRYRAg == IWSUJzUkOs){kqwyEqpXiL = true;}
      if(LrHopRJNkD == tiAyfnoaZA){EZfJqkHXGa = true;}
      else if(tiAyfnoaZA == LrHopRJNkD){SyoDgnSlzr = true;}
      if(XZjDGSJpnU == udisTZWyLG){acBGinHUPO = true;}
      else if(udisTZWyLG == XZjDGSJpnU){aQurtgLuSC = true;}
      if(OeoSOdDaCH == lsCFapTBRC){PafWhtTbYG = true;}
      else if(lsCFapTBRC == OeoSOdDaCH){AaCLSxnYoA = true;}
      if(mqmfoqIHAR == FSYYlImNfd){HcwJMezWwV = true;}
      else if(FSYYlImNfd == mqmfoqIHAR){jesCPEuQVs = true;}
      if(AiuPNhmPOp == TTTAMJknUd){XoXCJzpiHV = true;}
      else if(TTTAMJknUd == AiuPNhmPOp){yKGxHTwEEW = true;}
      if(oewsefDnZL == tZFstBftXo){YpfqTdtIax = true;}
      if(NiKcPgmDOP == TmIXtcFKHL){RfyATxfrtD = true;}
      if(KBpVTejYFg == lJShmSZCsQ){njXsqaCcNi = true;}
      while(tZFstBftXo == oewsefDnZL){etFgKrudjj = true;}
      while(TmIXtcFKHL == TmIXtcFKHL){AsxzIwXrbo = true;}
      while(lJShmSZCsQ == lJShmSZCsQ){ltZZDpTFDy = true;}
      if(FffnHeMedj == true){FffnHeMedj = false;}
      if(cropJfKwFj == true){cropJfKwFj = false;}
      if(EZfJqkHXGa == true){EZfJqkHXGa = false;}
      if(acBGinHUPO == true){acBGinHUPO = false;}
      if(PafWhtTbYG == true){PafWhtTbYG = false;}
      if(HcwJMezWwV == true){HcwJMezWwV = false;}
      if(XoXCJzpiHV == true){XoXCJzpiHV = false;}
      if(YpfqTdtIax == true){YpfqTdtIax = false;}
      if(RfyATxfrtD == true){RfyATxfrtD = false;}
      if(njXsqaCcNi == true){njXsqaCcNi = false;}
      if(DjUChQxFoi == true){DjUChQxFoi = false;}
      if(kqwyEqpXiL == true){kqwyEqpXiL = false;}
      if(SyoDgnSlzr == true){SyoDgnSlzr = false;}
      if(aQurtgLuSC == true){aQurtgLuSC = false;}
      if(AaCLSxnYoA == true){AaCLSxnYoA = false;}
      if(jesCPEuQVs == true){jesCPEuQVs = false;}
      if(yKGxHTwEEW == true){yKGxHTwEEW = false;}
      if(etFgKrudjj == true){etFgKrudjj = false;}
      if(AsxzIwXrbo == true){AsxzIwXrbo = false;}
      if(ltZZDpTFDy == true){ltZZDpTFDy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PLZTDOIOUB
{ 
  void hHIZGVXQkE()
  { 
      bool irSbQiBSBa = false;
      bool zDwqNLJTnA = false;
      bool cKcsgjPUAR = false;
      bool RZJlmqjceQ = false;
      bool aYuDLiPmxu = false;
      bool MHheLYOZtg = false;
      bool SfRiJZtJEW = false;
      bool afoXYEOZhy = false;
      bool TbXFFKqeaN = false;
      bool cKhyxuGLtk = false;
      bool nGiZUfSKFH = false;
      bool JoqwMqIMdy = false;
      bool hPiptQypZd = false;
      bool yDewJNrxjY = false;
      bool qgYTEnSlkG = false;
      bool mshuDYWsfE = false;
      bool hbkbIGJuly = false;
      bool yKbFHBpPkF = false;
      bool xLETpEVisk = false;
      bool pyQfpOwwKy = false;
      string UjlPVKDsnk;
      string ERDmiVLJaO;
      string bLnUtCjwQD;
      string LzjLFhaDNV;
      string WxomMjhpca;
      string uLfJQIwRVS;
      string aGckYFgrhA;
      string tHuFrdVBHK;
      string UsToIASauw;
      string lJhtuPUDNH;
      string CoIbgmPaQl;
      string muJLyglncY;
      string lGxkNjYBKc;
      string JSmAHejrHU;
      string jrKIJqAWuN;
      string cgaoUwrXNx;
      string NOQncUHIET;
      string wtfHntwobW;
      string iCFwzcqxeK;
      string lMeKGVbWeo;
      if(UjlPVKDsnk == CoIbgmPaQl){irSbQiBSBa = true;}
      else if(CoIbgmPaQl == UjlPVKDsnk){nGiZUfSKFH = true;}
      if(ERDmiVLJaO == muJLyglncY){zDwqNLJTnA = true;}
      else if(muJLyglncY == ERDmiVLJaO){JoqwMqIMdy = true;}
      if(bLnUtCjwQD == lGxkNjYBKc){cKcsgjPUAR = true;}
      else if(lGxkNjYBKc == bLnUtCjwQD){hPiptQypZd = true;}
      if(LzjLFhaDNV == JSmAHejrHU){RZJlmqjceQ = true;}
      else if(JSmAHejrHU == LzjLFhaDNV){yDewJNrxjY = true;}
      if(WxomMjhpca == jrKIJqAWuN){aYuDLiPmxu = true;}
      else if(jrKIJqAWuN == WxomMjhpca){qgYTEnSlkG = true;}
      if(uLfJQIwRVS == cgaoUwrXNx){MHheLYOZtg = true;}
      else if(cgaoUwrXNx == uLfJQIwRVS){mshuDYWsfE = true;}
      if(aGckYFgrhA == NOQncUHIET){SfRiJZtJEW = true;}
      else if(NOQncUHIET == aGckYFgrhA){hbkbIGJuly = true;}
      if(tHuFrdVBHK == wtfHntwobW){afoXYEOZhy = true;}
      if(UsToIASauw == iCFwzcqxeK){TbXFFKqeaN = true;}
      if(lJhtuPUDNH == lMeKGVbWeo){cKhyxuGLtk = true;}
      while(wtfHntwobW == tHuFrdVBHK){yKbFHBpPkF = true;}
      while(iCFwzcqxeK == iCFwzcqxeK){xLETpEVisk = true;}
      while(lMeKGVbWeo == lMeKGVbWeo){pyQfpOwwKy = true;}
      if(irSbQiBSBa == true){irSbQiBSBa = false;}
      if(zDwqNLJTnA == true){zDwqNLJTnA = false;}
      if(cKcsgjPUAR == true){cKcsgjPUAR = false;}
      if(RZJlmqjceQ == true){RZJlmqjceQ = false;}
      if(aYuDLiPmxu == true){aYuDLiPmxu = false;}
      if(MHheLYOZtg == true){MHheLYOZtg = false;}
      if(SfRiJZtJEW == true){SfRiJZtJEW = false;}
      if(afoXYEOZhy == true){afoXYEOZhy = false;}
      if(TbXFFKqeaN == true){TbXFFKqeaN = false;}
      if(cKhyxuGLtk == true){cKhyxuGLtk = false;}
      if(nGiZUfSKFH == true){nGiZUfSKFH = false;}
      if(JoqwMqIMdy == true){JoqwMqIMdy = false;}
      if(hPiptQypZd == true){hPiptQypZd = false;}
      if(yDewJNrxjY == true){yDewJNrxjY = false;}
      if(qgYTEnSlkG == true){qgYTEnSlkG = false;}
      if(mshuDYWsfE == true){mshuDYWsfE = false;}
      if(hbkbIGJuly == true){hbkbIGJuly = false;}
      if(yKbFHBpPkF == true){yKbFHBpPkF = false;}
      if(xLETpEVisk == true){xLETpEVisk = false;}
      if(pyQfpOwwKy == true){pyQfpOwwKy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFIZKDQVHR
{ 
  void LxWBddWWfg()
  { 
      bool ULecJZBMGW = false;
      bool OslnPyGsEG = false;
      bool pmJOVeLgdd = false;
      bool KKtpLeDqHW = false;
      bool uHHYjDCTpo = false;
      bool IxNKEgCQHd = false;
      bool NUicLDzwcj = false;
      bool tOlgKhfjdR = false;
      bool crqoUMxjkd = false;
      bool cljcIaYeNf = false;
      bool EFpFtsLfzV = false;
      bool BRlpAUcsHz = false;
      bool GOLyHHeIYi = false;
      bool JBWyMXBktb = false;
      bool AQjOcKztbn = false;
      bool yeWNYptryl = false;
      bool ODHQLzuncc = false;
      bool TryfyodwVw = false;
      bool IkfkkedIYW = false;
      bool dJmIMxJTCc = false;
      string PIKzUnKGUe;
      string jqGllJwLRX;
      string erxnULkMiG;
      string LVkSjxMZbL;
      string oIdBqrXNMK;
      string dcLaKWLVeI;
      string CxWNSOFnCn;
      string xVjFhVOwwb;
      string mWAYbiJKIM;
      string lpuSJqkPhc;
      string ljLXNIrGrn;
      string IOYCVexxki;
      string EueoCHaRuq;
      string kyNToCLcLT;
      string pCSTEWQrwd;
      string tmdzXqEWUF;
      string gaLADJBFMS;
      string TTlRrBbLjf;
      string piURwxTNwy;
      string xnHFmOqRQt;
      if(PIKzUnKGUe == ljLXNIrGrn){ULecJZBMGW = true;}
      else if(ljLXNIrGrn == PIKzUnKGUe){EFpFtsLfzV = true;}
      if(jqGllJwLRX == IOYCVexxki){OslnPyGsEG = true;}
      else if(IOYCVexxki == jqGllJwLRX){BRlpAUcsHz = true;}
      if(erxnULkMiG == EueoCHaRuq){pmJOVeLgdd = true;}
      else if(EueoCHaRuq == erxnULkMiG){GOLyHHeIYi = true;}
      if(LVkSjxMZbL == kyNToCLcLT){KKtpLeDqHW = true;}
      else if(kyNToCLcLT == LVkSjxMZbL){JBWyMXBktb = true;}
      if(oIdBqrXNMK == pCSTEWQrwd){uHHYjDCTpo = true;}
      else if(pCSTEWQrwd == oIdBqrXNMK){AQjOcKztbn = true;}
      if(dcLaKWLVeI == tmdzXqEWUF){IxNKEgCQHd = true;}
      else if(tmdzXqEWUF == dcLaKWLVeI){yeWNYptryl = true;}
      if(CxWNSOFnCn == gaLADJBFMS){NUicLDzwcj = true;}
      else if(gaLADJBFMS == CxWNSOFnCn){ODHQLzuncc = true;}
      if(xVjFhVOwwb == TTlRrBbLjf){tOlgKhfjdR = true;}
      if(mWAYbiJKIM == piURwxTNwy){crqoUMxjkd = true;}
      if(lpuSJqkPhc == xnHFmOqRQt){cljcIaYeNf = true;}
      while(TTlRrBbLjf == xVjFhVOwwb){TryfyodwVw = true;}
      while(piURwxTNwy == piURwxTNwy){IkfkkedIYW = true;}
      while(xnHFmOqRQt == xnHFmOqRQt){dJmIMxJTCc = true;}
      if(ULecJZBMGW == true){ULecJZBMGW = false;}
      if(OslnPyGsEG == true){OslnPyGsEG = false;}
      if(pmJOVeLgdd == true){pmJOVeLgdd = false;}
      if(KKtpLeDqHW == true){KKtpLeDqHW = false;}
      if(uHHYjDCTpo == true){uHHYjDCTpo = false;}
      if(IxNKEgCQHd == true){IxNKEgCQHd = false;}
      if(NUicLDzwcj == true){NUicLDzwcj = false;}
      if(tOlgKhfjdR == true){tOlgKhfjdR = false;}
      if(crqoUMxjkd == true){crqoUMxjkd = false;}
      if(cljcIaYeNf == true){cljcIaYeNf = false;}
      if(EFpFtsLfzV == true){EFpFtsLfzV = false;}
      if(BRlpAUcsHz == true){BRlpAUcsHz = false;}
      if(GOLyHHeIYi == true){GOLyHHeIYi = false;}
      if(JBWyMXBktb == true){JBWyMXBktb = false;}
      if(AQjOcKztbn == true){AQjOcKztbn = false;}
      if(yeWNYptryl == true){yeWNYptryl = false;}
      if(ODHQLzuncc == true){ODHQLzuncc = false;}
      if(TryfyodwVw == true){TryfyodwVw = false;}
      if(IkfkkedIYW == true){IkfkkedIYW = false;}
      if(dJmIMxJTCc == true){dJmIMxJTCc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RFMISNFXYX
{ 
  void UaSUyeDyMk()
  { 
      bool dsHJiHqIxc = false;
      bool aEzZrKbqdl = false;
      bool FGloMHiBfg = false;
      bool mRUFxKchSb = false;
      bool UMgnkxJaPY = false;
      bool hbEZbXHRwa = false;
      bool XobPpJjtbg = false;
      bool gsXBRrYxDP = false;
      bool xIlHzLNtcY = false;
      bool DLlqEekRyb = false;
      bool NPyiqoDDIj = false;
      bool zJNgdODUQe = false;
      bool uoQCdVHgxl = false;
      bool HGzbBhKDPK = false;
      bool HKlsZsxENo = false;
      bool bPBTfYyuEV = false;
      bool gWGWcrKlfu = false;
      bool EAEGWkDXcj = false;
      bool XCTHKqFeuc = false;
      bool iOyscjEOQg = false;
      string VJzasXacUe;
      string zFibMWFuWH;
      string MqalTUgwJG;
      string sWYPFCQICF;
      string GifwfFzDCF;
      string mdNopdiMGY;
      string qdSNkbfSVJ;
      string GxsRBdKeGO;
      string UcsETOIiYa;
      string TECcObPRKD;
      string YfgrzokwmM;
      string TEGrENkOtV;
      string TwttpCtQDZ;
      string NsTConwBEd;
      string dMwLHOxJYA;
      string pBXojbllBw;
      string uTsNzZkDCP;
      string RiJPqGAhmb;
      string EjrCiMUeRM;
      string CJAHiKShMg;
      if(VJzasXacUe == YfgrzokwmM){dsHJiHqIxc = true;}
      else if(YfgrzokwmM == VJzasXacUe){NPyiqoDDIj = true;}
      if(zFibMWFuWH == TEGrENkOtV){aEzZrKbqdl = true;}
      else if(TEGrENkOtV == zFibMWFuWH){zJNgdODUQe = true;}
      if(MqalTUgwJG == TwttpCtQDZ){FGloMHiBfg = true;}
      else if(TwttpCtQDZ == MqalTUgwJG){uoQCdVHgxl = true;}
      if(sWYPFCQICF == NsTConwBEd){mRUFxKchSb = true;}
      else if(NsTConwBEd == sWYPFCQICF){HGzbBhKDPK = true;}
      if(GifwfFzDCF == dMwLHOxJYA){UMgnkxJaPY = true;}
      else if(dMwLHOxJYA == GifwfFzDCF){HKlsZsxENo = true;}
      if(mdNopdiMGY == pBXojbllBw){hbEZbXHRwa = true;}
      else if(pBXojbllBw == mdNopdiMGY){bPBTfYyuEV = true;}
      if(qdSNkbfSVJ == uTsNzZkDCP){XobPpJjtbg = true;}
      else if(uTsNzZkDCP == qdSNkbfSVJ){gWGWcrKlfu = true;}
      if(GxsRBdKeGO == RiJPqGAhmb){gsXBRrYxDP = true;}
      if(UcsETOIiYa == EjrCiMUeRM){xIlHzLNtcY = true;}
      if(TECcObPRKD == CJAHiKShMg){DLlqEekRyb = true;}
      while(RiJPqGAhmb == GxsRBdKeGO){EAEGWkDXcj = true;}
      while(EjrCiMUeRM == EjrCiMUeRM){XCTHKqFeuc = true;}
      while(CJAHiKShMg == CJAHiKShMg){iOyscjEOQg = true;}
      if(dsHJiHqIxc == true){dsHJiHqIxc = false;}
      if(aEzZrKbqdl == true){aEzZrKbqdl = false;}
      if(FGloMHiBfg == true){FGloMHiBfg = false;}
      if(mRUFxKchSb == true){mRUFxKchSb = false;}
      if(UMgnkxJaPY == true){UMgnkxJaPY = false;}
      if(hbEZbXHRwa == true){hbEZbXHRwa = false;}
      if(XobPpJjtbg == true){XobPpJjtbg = false;}
      if(gsXBRrYxDP == true){gsXBRrYxDP = false;}
      if(xIlHzLNtcY == true){xIlHzLNtcY = false;}
      if(DLlqEekRyb == true){DLlqEekRyb = false;}
      if(NPyiqoDDIj == true){NPyiqoDDIj = false;}
      if(zJNgdODUQe == true){zJNgdODUQe = false;}
      if(uoQCdVHgxl == true){uoQCdVHgxl = false;}
      if(HGzbBhKDPK == true){HGzbBhKDPK = false;}
      if(HKlsZsxENo == true){HKlsZsxENo = false;}
      if(bPBTfYyuEV == true){bPBTfYyuEV = false;}
      if(gWGWcrKlfu == true){gWGWcrKlfu = false;}
      if(EAEGWkDXcj == true){EAEGWkDXcj = false;}
      if(XCTHKqFeuc == true){XCTHKqFeuc = false;}
      if(iOyscjEOQg == true){iOyscjEOQg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WOJTIPSDDF
{ 
  void wuVGLOxRYc()
  { 
      bool jpTZVOJpKz = false;
      bool FVSdMMLgWx = false;
      bool KoTjNSHKAU = false;
      bool jquPLQbGAr = false;
      bool olGHqeQlWe = false;
      bool YxkmgtViMC = false;
      bool GzpoPOaDRw = false;
      bool kEfeHYiLri = false;
      bool CVmVwlFIhQ = false;
      bool tstxkpwQrc = false;
      bool EMTZsTRFeH = false;
      bool LKpcAkLTsc = false;
      bool IRVBBrKhtR = false;
      bool cRTPeoCMbc = false;
      bool UAcZEjCQxA = false;
      bool dbXOTlqSYB = false;
      bool IiLMetpZyK = false;
      bool iyqQIIouwR = false;
      bool otktnBtEus = false;
      bool yjnaTlnQuK = false;
      string yQpJQujUpL;
      string dUikGczYCC;
      string AMANfdIXas;
      string lEYmRrpQtX;
      string KuYWilLhYe;
      string ntaOFlPbdl;
      string mLsxZYuuSN;
      string liedrFmdes;
      string SZzwEqdJhe;
      string bOlIkyBbxJ;
      string pPOKrEOwWA;
      string zlwkSMMxrh;
      string ukNnkXwWss;
      string DLfVCDKoDz;
      string cglgfpRBoX;
      string lDiPNECaYT;
      string HrCdwmFahO;
      string CXtrEOzfHu;
      string GugVGzbQHx;
      string BiPjqjdIjr;
      if(yQpJQujUpL == pPOKrEOwWA){jpTZVOJpKz = true;}
      else if(pPOKrEOwWA == yQpJQujUpL){EMTZsTRFeH = true;}
      if(dUikGczYCC == zlwkSMMxrh){FVSdMMLgWx = true;}
      else if(zlwkSMMxrh == dUikGczYCC){LKpcAkLTsc = true;}
      if(AMANfdIXas == ukNnkXwWss){KoTjNSHKAU = true;}
      else if(ukNnkXwWss == AMANfdIXas){IRVBBrKhtR = true;}
      if(lEYmRrpQtX == DLfVCDKoDz){jquPLQbGAr = true;}
      else if(DLfVCDKoDz == lEYmRrpQtX){cRTPeoCMbc = true;}
      if(KuYWilLhYe == cglgfpRBoX){olGHqeQlWe = true;}
      else if(cglgfpRBoX == KuYWilLhYe){UAcZEjCQxA = true;}
      if(ntaOFlPbdl == lDiPNECaYT){YxkmgtViMC = true;}
      else if(lDiPNECaYT == ntaOFlPbdl){dbXOTlqSYB = true;}
      if(mLsxZYuuSN == HrCdwmFahO){GzpoPOaDRw = true;}
      else if(HrCdwmFahO == mLsxZYuuSN){IiLMetpZyK = true;}
      if(liedrFmdes == CXtrEOzfHu){kEfeHYiLri = true;}
      if(SZzwEqdJhe == GugVGzbQHx){CVmVwlFIhQ = true;}
      if(bOlIkyBbxJ == BiPjqjdIjr){tstxkpwQrc = true;}
      while(CXtrEOzfHu == liedrFmdes){iyqQIIouwR = true;}
      while(GugVGzbQHx == GugVGzbQHx){otktnBtEus = true;}
      while(BiPjqjdIjr == BiPjqjdIjr){yjnaTlnQuK = true;}
      if(jpTZVOJpKz == true){jpTZVOJpKz = false;}
      if(FVSdMMLgWx == true){FVSdMMLgWx = false;}
      if(KoTjNSHKAU == true){KoTjNSHKAU = false;}
      if(jquPLQbGAr == true){jquPLQbGAr = false;}
      if(olGHqeQlWe == true){olGHqeQlWe = false;}
      if(YxkmgtViMC == true){YxkmgtViMC = false;}
      if(GzpoPOaDRw == true){GzpoPOaDRw = false;}
      if(kEfeHYiLri == true){kEfeHYiLri = false;}
      if(CVmVwlFIhQ == true){CVmVwlFIhQ = false;}
      if(tstxkpwQrc == true){tstxkpwQrc = false;}
      if(EMTZsTRFeH == true){EMTZsTRFeH = false;}
      if(LKpcAkLTsc == true){LKpcAkLTsc = false;}
      if(IRVBBrKhtR == true){IRVBBrKhtR = false;}
      if(cRTPeoCMbc == true){cRTPeoCMbc = false;}
      if(UAcZEjCQxA == true){UAcZEjCQxA = false;}
      if(dbXOTlqSYB == true){dbXOTlqSYB = false;}
      if(IiLMetpZyK == true){IiLMetpZyK = false;}
      if(iyqQIIouwR == true){iyqQIIouwR = false;}
      if(otktnBtEus == true){otktnBtEus = false;}
      if(yjnaTlnQuK == true){yjnaTlnQuK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EGJFUHADYS
{ 
  void eSaFpXXAGC()
  { 
      bool oFfUNxbUOf = false;
      bool dQksHjqDtS = false;
      bool grRguXtQfF = false;
      bool uYurlDDOKm = false;
      bool nBYqyhKHln = false;
      bool uSgnExnyZp = false;
      bool DKoIjEVsHE = false;
      bool gbrGdeTahN = false;
      bool MleqJcrGmn = false;
      bool PEoUjdMPGs = false;
      bool MRAhHTZaJY = false;
      bool dMQLcQfxzG = false;
      bool MOFSocmWWA = false;
      bool SDTnBulxjp = false;
      bool DRwNKCndrT = false;
      bool xOQzgxLhre = false;
      bool gCDJGasbJg = false;
      bool eiMJDuRrHm = false;
      bool nJeDDDlTHE = false;
      bool jDEFIANmHj = false;
      string uwyXwVyTqi;
      string naCbWQHlKr;
      string aYOBGJswPK;
      string nmEfOdEZMp;
      string INDHPJhxJh;
      string ZAEpBWhxQl;
      string bBDgtAVWNr;
      string LhZUiNUHkx;
      string bwlgjniNdr;
      string uHJZNHJWMP;
      string nKjRVrZjHm;
      string BZLSKfPVwG;
      string QHrUwEYzGb;
      string DxtVIQLULr;
      string NzGppVupPh;
      string qmZGyfSPUQ;
      string SaceiEfoKt;
      string TtKErRBBda;
      string JijYjQWmXc;
      string ywAtYmVbGl;
      if(uwyXwVyTqi == nKjRVrZjHm){oFfUNxbUOf = true;}
      else if(nKjRVrZjHm == uwyXwVyTqi){MRAhHTZaJY = true;}
      if(naCbWQHlKr == BZLSKfPVwG){dQksHjqDtS = true;}
      else if(BZLSKfPVwG == naCbWQHlKr){dMQLcQfxzG = true;}
      if(aYOBGJswPK == QHrUwEYzGb){grRguXtQfF = true;}
      else if(QHrUwEYzGb == aYOBGJswPK){MOFSocmWWA = true;}
      if(nmEfOdEZMp == DxtVIQLULr){uYurlDDOKm = true;}
      else if(DxtVIQLULr == nmEfOdEZMp){SDTnBulxjp = true;}
      if(INDHPJhxJh == NzGppVupPh){nBYqyhKHln = true;}
      else if(NzGppVupPh == INDHPJhxJh){DRwNKCndrT = true;}
      if(ZAEpBWhxQl == qmZGyfSPUQ){uSgnExnyZp = true;}
      else if(qmZGyfSPUQ == ZAEpBWhxQl){xOQzgxLhre = true;}
      if(bBDgtAVWNr == SaceiEfoKt){DKoIjEVsHE = true;}
      else if(SaceiEfoKt == bBDgtAVWNr){gCDJGasbJg = true;}
      if(LhZUiNUHkx == TtKErRBBda){gbrGdeTahN = true;}
      if(bwlgjniNdr == JijYjQWmXc){MleqJcrGmn = true;}
      if(uHJZNHJWMP == ywAtYmVbGl){PEoUjdMPGs = true;}
      while(TtKErRBBda == LhZUiNUHkx){eiMJDuRrHm = true;}
      while(JijYjQWmXc == JijYjQWmXc){nJeDDDlTHE = true;}
      while(ywAtYmVbGl == ywAtYmVbGl){jDEFIANmHj = true;}
      if(oFfUNxbUOf == true){oFfUNxbUOf = false;}
      if(dQksHjqDtS == true){dQksHjqDtS = false;}
      if(grRguXtQfF == true){grRguXtQfF = false;}
      if(uYurlDDOKm == true){uYurlDDOKm = false;}
      if(nBYqyhKHln == true){nBYqyhKHln = false;}
      if(uSgnExnyZp == true){uSgnExnyZp = false;}
      if(DKoIjEVsHE == true){DKoIjEVsHE = false;}
      if(gbrGdeTahN == true){gbrGdeTahN = false;}
      if(MleqJcrGmn == true){MleqJcrGmn = false;}
      if(PEoUjdMPGs == true){PEoUjdMPGs = false;}
      if(MRAhHTZaJY == true){MRAhHTZaJY = false;}
      if(dMQLcQfxzG == true){dMQLcQfxzG = false;}
      if(MOFSocmWWA == true){MOFSocmWWA = false;}
      if(SDTnBulxjp == true){SDTnBulxjp = false;}
      if(DRwNKCndrT == true){DRwNKCndrT = false;}
      if(xOQzgxLhre == true){xOQzgxLhre = false;}
      if(gCDJGasbJg == true){gCDJGasbJg = false;}
      if(eiMJDuRrHm == true){eiMJDuRrHm = false;}
      if(nJeDDDlTHE == true){nJeDDDlTHE = false;}
      if(jDEFIANmHj == true){jDEFIANmHj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVISSRPBWM
{ 
  void xzwCKsKSFe()
  { 
      bool PTGJTKpBTa = false;
      bool ieNougXGTb = false;
      bool wLVYaZiBhw = false;
      bool qkUcSlNVMC = false;
      bool SgcJzXAotc = false;
      bool MIadzExght = false;
      bool boSWjyJjVI = false;
      bool SBtRIPhMZC = false;
      bool YsGEiiJpdO = false;
      bool ofnSadNGZA = false;
      bool OQSkKLOIUi = false;
      bool VkHfUhhOmA = false;
      bool nSFHTlNaqe = false;
      bool BblYnIZVtX = false;
      bool TBUtrEYHxr = false;
      bool uzSZLuKLRX = false;
      bool ynRpgtyhqM = false;
      bool HMTPfmxLOO = false;
      bool NFcyjCIMMr = false;
      bool xODVYfieMy = false;
      string BnnSUqFAjy;
      string jwtwrdwmNU;
      string dVPytzMDrj;
      string VsrFNEssub;
      string rWwxjZPWTS;
      string nMNwjeYpYV;
      string eBHzcpDoim;
      string jDqkcGYRNT;
      string iojZwIewUh;
      string eDTYxpPxUs;
      string WZnfhjUbTc;
      string GGbFloRhDT;
      string KHTAHgiRnl;
      string qbxUxIBDqL;
      string mDbraYaOlH;
      string YhsAiOGmXB;
      string BCmgkeIHHc;
      string nNqrgHebZi;
      string FUegNJhxkh;
      string COeoJjPtGw;
      if(BnnSUqFAjy == WZnfhjUbTc){PTGJTKpBTa = true;}
      else if(WZnfhjUbTc == BnnSUqFAjy){OQSkKLOIUi = true;}
      if(jwtwrdwmNU == GGbFloRhDT){ieNougXGTb = true;}
      else if(GGbFloRhDT == jwtwrdwmNU){VkHfUhhOmA = true;}
      if(dVPytzMDrj == KHTAHgiRnl){wLVYaZiBhw = true;}
      else if(KHTAHgiRnl == dVPytzMDrj){nSFHTlNaqe = true;}
      if(VsrFNEssub == qbxUxIBDqL){qkUcSlNVMC = true;}
      else if(qbxUxIBDqL == VsrFNEssub){BblYnIZVtX = true;}
      if(rWwxjZPWTS == mDbraYaOlH){SgcJzXAotc = true;}
      else if(mDbraYaOlH == rWwxjZPWTS){TBUtrEYHxr = true;}
      if(nMNwjeYpYV == YhsAiOGmXB){MIadzExght = true;}
      else if(YhsAiOGmXB == nMNwjeYpYV){uzSZLuKLRX = true;}
      if(eBHzcpDoim == BCmgkeIHHc){boSWjyJjVI = true;}
      else if(BCmgkeIHHc == eBHzcpDoim){ynRpgtyhqM = true;}
      if(jDqkcGYRNT == nNqrgHebZi){SBtRIPhMZC = true;}
      if(iojZwIewUh == FUegNJhxkh){YsGEiiJpdO = true;}
      if(eDTYxpPxUs == COeoJjPtGw){ofnSadNGZA = true;}
      while(nNqrgHebZi == jDqkcGYRNT){HMTPfmxLOO = true;}
      while(FUegNJhxkh == FUegNJhxkh){NFcyjCIMMr = true;}
      while(COeoJjPtGw == COeoJjPtGw){xODVYfieMy = true;}
      if(PTGJTKpBTa == true){PTGJTKpBTa = false;}
      if(ieNougXGTb == true){ieNougXGTb = false;}
      if(wLVYaZiBhw == true){wLVYaZiBhw = false;}
      if(qkUcSlNVMC == true){qkUcSlNVMC = false;}
      if(SgcJzXAotc == true){SgcJzXAotc = false;}
      if(MIadzExght == true){MIadzExght = false;}
      if(boSWjyJjVI == true){boSWjyJjVI = false;}
      if(SBtRIPhMZC == true){SBtRIPhMZC = false;}
      if(YsGEiiJpdO == true){YsGEiiJpdO = false;}
      if(ofnSadNGZA == true){ofnSadNGZA = false;}
      if(OQSkKLOIUi == true){OQSkKLOIUi = false;}
      if(VkHfUhhOmA == true){VkHfUhhOmA = false;}
      if(nSFHTlNaqe == true){nSFHTlNaqe = false;}
      if(BblYnIZVtX == true){BblYnIZVtX = false;}
      if(TBUtrEYHxr == true){TBUtrEYHxr = false;}
      if(uzSZLuKLRX == true){uzSZLuKLRX = false;}
      if(ynRpgtyhqM == true){ynRpgtyhqM = false;}
      if(HMTPfmxLOO == true){HMTPfmxLOO = false;}
      if(NFcyjCIMMr == true){NFcyjCIMMr = false;}
      if(xODVYfieMy == true){xODVYfieMy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YDMIDZQTAW
{ 
  void ixRlWZZHZw()
  { 
      bool sDMfQTPCbU = false;
      bool uyAgtGlDhO = false;
      bool pZsqoSuqHi = false;
      bool rMLCkOAfMx = false;
      bool WsKzxWONba = false;
      bool zugNGTJUqx = false;
      bool YXurchlywe = false;
      bool FFqjqwOstR = false;
      bool EgPfiwfyuQ = false;
      bool FenPYyyRWO = false;
      bool jQQwUsExVJ = false;
      bool FPaYsqIOJg = false;
      bool CnCfZaRaLr = false;
      bool ywWehmQSLo = false;
      bool qhblLoDPWg = false;
      bool oiHoMuNkWt = false;
      bool bdlcKIswpF = false;
      bool apDUoTMQTj = false;
      bool WBEdDOogRm = false;
      bool ZeuRMNwyaD = false;
      string OFgEAVeJZm;
      string njQzOfZsSk;
      string xTbRbYZgeH;
      string wZAEFdeXis;
      string DFzqyxObfy;
      string eLjJJudPca;
      string uxdSpNiLsj;
      string ACKZhqTjSd;
      string KxBgckpquK;
      string APtHxFagBj;
      string OCiuxbBJbR;
      string atxyQywxoE;
      string XqQijkICcb;
      string QmhhPHOGiA;
      string jfOcjFSupz;
      string JdqwMWlzLM;
      string TygzBmLOiJ;
      string ioNnUqbmzd;
      string SMMcRmwlUr;
      string UPtWglzPbx;
      if(OFgEAVeJZm == OCiuxbBJbR){sDMfQTPCbU = true;}
      else if(OCiuxbBJbR == OFgEAVeJZm){jQQwUsExVJ = true;}
      if(njQzOfZsSk == atxyQywxoE){uyAgtGlDhO = true;}
      else if(atxyQywxoE == njQzOfZsSk){FPaYsqIOJg = true;}
      if(xTbRbYZgeH == XqQijkICcb){pZsqoSuqHi = true;}
      else if(XqQijkICcb == xTbRbYZgeH){CnCfZaRaLr = true;}
      if(wZAEFdeXis == QmhhPHOGiA){rMLCkOAfMx = true;}
      else if(QmhhPHOGiA == wZAEFdeXis){ywWehmQSLo = true;}
      if(DFzqyxObfy == jfOcjFSupz){WsKzxWONba = true;}
      else if(jfOcjFSupz == DFzqyxObfy){qhblLoDPWg = true;}
      if(eLjJJudPca == JdqwMWlzLM){zugNGTJUqx = true;}
      else if(JdqwMWlzLM == eLjJJudPca){oiHoMuNkWt = true;}
      if(uxdSpNiLsj == TygzBmLOiJ){YXurchlywe = true;}
      else if(TygzBmLOiJ == uxdSpNiLsj){bdlcKIswpF = true;}
      if(ACKZhqTjSd == ioNnUqbmzd){FFqjqwOstR = true;}
      if(KxBgckpquK == SMMcRmwlUr){EgPfiwfyuQ = true;}
      if(APtHxFagBj == UPtWglzPbx){FenPYyyRWO = true;}
      while(ioNnUqbmzd == ACKZhqTjSd){apDUoTMQTj = true;}
      while(SMMcRmwlUr == SMMcRmwlUr){WBEdDOogRm = true;}
      while(UPtWglzPbx == UPtWglzPbx){ZeuRMNwyaD = true;}
      if(sDMfQTPCbU == true){sDMfQTPCbU = false;}
      if(uyAgtGlDhO == true){uyAgtGlDhO = false;}
      if(pZsqoSuqHi == true){pZsqoSuqHi = false;}
      if(rMLCkOAfMx == true){rMLCkOAfMx = false;}
      if(WsKzxWONba == true){WsKzxWONba = false;}
      if(zugNGTJUqx == true){zugNGTJUqx = false;}
      if(YXurchlywe == true){YXurchlywe = false;}
      if(FFqjqwOstR == true){FFqjqwOstR = false;}
      if(EgPfiwfyuQ == true){EgPfiwfyuQ = false;}
      if(FenPYyyRWO == true){FenPYyyRWO = false;}
      if(jQQwUsExVJ == true){jQQwUsExVJ = false;}
      if(FPaYsqIOJg == true){FPaYsqIOJg = false;}
      if(CnCfZaRaLr == true){CnCfZaRaLr = false;}
      if(ywWehmQSLo == true){ywWehmQSLo = false;}
      if(qhblLoDPWg == true){qhblLoDPWg = false;}
      if(oiHoMuNkWt == true){oiHoMuNkWt = false;}
      if(bdlcKIswpF == true){bdlcKIswpF = false;}
      if(apDUoTMQTj == true){apDUoTMQTj = false;}
      if(WBEdDOogRm == true){WBEdDOogRm = false;}
      if(ZeuRMNwyaD == true){ZeuRMNwyaD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XGCVLGBFPC
{ 
  void BpWAwyNrTT()
  { 
      bool ldtpnjMIFa = false;
      bool msgdcwkJsQ = false;
      bool zHdtdcHRoB = false;
      bool BJFVTHcPCK = false;
      bool trVsTZTWEr = false;
      bool GMjYqdAzLK = false;
      bool buTDZdnLJU = false;
      bool SUHhWHlkZD = false;
      bool JjNxunYfep = false;
      bool HcDqhyYRTp = false;
      bool lHMiYlFBBi = false;
      bool qOZIBqhVIl = false;
      bool EHfTNpQQAY = false;
      bool iTQjRBWdXJ = false;
      bool iXeuyrDupp = false;
      bool PCJgldasUi = false;
      bool UnBcAXyppz = false;
      bool TDyyDgckVU = false;
      bool lVaJIgJjxn = false;
      bool ZdInotVCtZ = false;
      string ZgWsXsrpUk;
      string TpjTqqhnIs;
      string FWXnsOaGSl;
      string pprWimegCI;
      string VeIWYeJhNq;
      string oWIyRDJhzJ;
      string RkXiucyNjD;
      string LBlzXaNAPO;
      string ErsbwSgsEf;
      string cwgrqjHZau;
      string fwyJenjJaq;
      string oISjFYrulb;
      string wFIEZPTsIm;
      string SnZThHtjwI;
      string iXRNqUcwmR;
      string rLmyzantiP;
      string TqAnXAiyCx;
      string dIydsXmtMF;
      string lXFptGBaUH;
      string TAAgnqWdop;
      if(ZgWsXsrpUk == fwyJenjJaq){ldtpnjMIFa = true;}
      else if(fwyJenjJaq == ZgWsXsrpUk){lHMiYlFBBi = true;}
      if(TpjTqqhnIs == oISjFYrulb){msgdcwkJsQ = true;}
      else if(oISjFYrulb == TpjTqqhnIs){qOZIBqhVIl = true;}
      if(FWXnsOaGSl == wFIEZPTsIm){zHdtdcHRoB = true;}
      else if(wFIEZPTsIm == FWXnsOaGSl){EHfTNpQQAY = true;}
      if(pprWimegCI == SnZThHtjwI){BJFVTHcPCK = true;}
      else if(SnZThHtjwI == pprWimegCI){iTQjRBWdXJ = true;}
      if(VeIWYeJhNq == iXRNqUcwmR){trVsTZTWEr = true;}
      else if(iXRNqUcwmR == VeIWYeJhNq){iXeuyrDupp = true;}
      if(oWIyRDJhzJ == rLmyzantiP){GMjYqdAzLK = true;}
      else if(rLmyzantiP == oWIyRDJhzJ){PCJgldasUi = true;}
      if(RkXiucyNjD == TqAnXAiyCx){buTDZdnLJU = true;}
      else if(TqAnXAiyCx == RkXiucyNjD){UnBcAXyppz = true;}
      if(LBlzXaNAPO == dIydsXmtMF){SUHhWHlkZD = true;}
      if(ErsbwSgsEf == lXFptGBaUH){JjNxunYfep = true;}
      if(cwgrqjHZau == TAAgnqWdop){HcDqhyYRTp = true;}
      while(dIydsXmtMF == LBlzXaNAPO){TDyyDgckVU = true;}
      while(lXFptGBaUH == lXFptGBaUH){lVaJIgJjxn = true;}
      while(TAAgnqWdop == TAAgnqWdop){ZdInotVCtZ = true;}
      if(ldtpnjMIFa == true){ldtpnjMIFa = false;}
      if(msgdcwkJsQ == true){msgdcwkJsQ = false;}
      if(zHdtdcHRoB == true){zHdtdcHRoB = false;}
      if(BJFVTHcPCK == true){BJFVTHcPCK = false;}
      if(trVsTZTWEr == true){trVsTZTWEr = false;}
      if(GMjYqdAzLK == true){GMjYqdAzLK = false;}
      if(buTDZdnLJU == true){buTDZdnLJU = false;}
      if(SUHhWHlkZD == true){SUHhWHlkZD = false;}
      if(JjNxunYfep == true){JjNxunYfep = false;}
      if(HcDqhyYRTp == true){HcDqhyYRTp = false;}
      if(lHMiYlFBBi == true){lHMiYlFBBi = false;}
      if(qOZIBqhVIl == true){qOZIBqhVIl = false;}
      if(EHfTNpQQAY == true){EHfTNpQQAY = false;}
      if(iTQjRBWdXJ == true){iTQjRBWdXJ = false;}
      if(iXeuyrDupp == true){iXeuyrDupp = false;}
      if(PCJgldasUi == true){PCJgldasUi = false;}
      if(UnBcAXyppz == true){UnBcAXyppz = false;}
      if(TDyyDgckVU == true){TDyyDgckVU = false;}
      if(lVaJIgJjxn == true){lVaJIgJjxn = false;}
      if(ZdInotVCtZ == true){ZdInotVCtZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXZSXLTKCI
{ 
  void DEGPaQbAGy()
  { 
      bool zfOyOCqjUl = false;
      bool KdwTOabkuW = false;
      bool myDYcwsQzr = false;
      bool npXWTBklLP = false;
      bool GHcAQdWeFm = false;
      bool LKYXxBboVS = false;
      bool JZkcyUGZzN = false;
      bool ooYfPeUDIy = false;
      bool ZNKLgdRAZS = false;
      bool YwQsFgWABw = false;
      bool XxfrxVlrHR = false;
      bool fYfWrwOYuU = false;
      bool CGAfnsYeai = false;
      bool IUBMabgSNL = false;
      bool qZrHmAPsAJ = false;
      bool RxEgsQxzDE = false;
      bool wGRXJKWTuP = false;
      bool OwKjccNrsn = false;
      bool cfdQRKQUSJ = false;
      bool ehOJOkHUyb = false;
      string msYwXJRQnM;
      string fXzzXWIqZc;
      string IbSBhzZyuD;
      string DPUJtQucyB;
      string rCkndTRdJc;
      string WYpLBKZXNX;
      string iSVjIQDoFG;
      string besXkGpeWO;
      string hwoRgdYIIi;
      string qWOZRYfBfN;
      string QcYCBqeRat;
      string UuAzpmdDDd;
      string qtfVPEPTFM;
      string aozJyEWlQp;
      string yHhNOuWPie;
      string tcxBWWwDmw;
      string aLLNTewpBk;
      string PrlNfjLRGT;
      string gAjaRxrymb;
      string ITyUOmuUtj;
      if(msYwXJRQnM == QcYCBqeRat){zfOyOCqjUl = true;}
      else if(QcYCBqeRat == msYwXJRQnM){XxfrxVlrHR = true;}
      if(fXzzXWIqZc == UuAzpmdDDd){KdwTOabkuW = true;}
      else if(UuAzpmdDDd == fXzzXWIqZc){fYfWrwOYuU = true;}
      if(IbSBhzZyuD == qtfVPEPTFM){myDYcwsQzr = true;}
      else if(qtfVPEPTFM == IbSBhzZyuD){CGAfnsYeai = true;}
      if(DPUJtQucyB == aozJyEWlQp){npXWTBklLP = true;}
      else if(aozJyEWlQp == DPUJtQucyB){IUBMabgSNL = true;}
      if(rCkndTRdJc == yHhNOuWPie){GHcAQdWeFm = true;}
      else if(yHhNOuWPie == rCkndTRdJc){qZrHmAPsAJ = true;}
      if(WYpLBKZXNX == tcxBWWwDmw){LKYXxBboVS = true;}
      else if(tcxBWWwDmw == WYpLBKZXNX){RxEgsQxzDE = true;}
      if(iSVjIQDoFG == aLLNTewpBk){JZkcyUGZzN = true;}
      else if(aLLNTewpBk == iSVjIQDoFG){wGRXJKWTuP = true;}
      if(besXkGpeWO == PrlNfjLRGT){ooYfPeUDIy = true;}
      if(hwoRgdYIIi == gAjaRxrymb){ZNKLgdRAZS = true;}
      if(qWOZRYfBfN == ITyUOmuUtj){YwQsFgWABw = true;}
      while(PrlNfjLRGT == besXkGpeWO){OwKjccNrsn = true;}
      while(gAjaRxrymb == gAjaRxrymb){cfdQRKQUSJ = true;}
      while(ITyUOmuUtj == ITyUOmuUtj){ehOJOkHUyb = true;}
      if(zfOyOCqjUl == true){zfOyOCqjUl = false;}
      if(KdwTOabkuW == true){KdwTOabkuW = false;}
      if(myDYcwsQzr == true){myDYcwsQzr = false;}
      if(npXWTBklLP == true){npXWTBklLP = false;}
      if(GHcAQdWeFm == true){GHcAQdWeFm = false;}
      if(LKYXxBboVS == true){LKYXxBboVS = false;}
      if(JZkcyUGZzN == true){JZkcyUGZzN = false;}
      if(ooYfPeUDIy == true){ooYfPeUDIy = false;}
      if(ZNKLgdRAZS == true){ZNKLgdRAZS = false;}
      if(YwQsFgWABw == true){YwQsFgWABw = false;}
      if(XxfrxVlrHR == true){XxfrxVlrHR = false;}
      if(fYfWrwOYuU == true){fYfWrwOYuU = false;}
      if(CGAfnsYeai == true){CGAfnsYeai = false;}
      if(IUBMabgSNL == true){IUBMabgSNL = false;}
      if(qZrHmAPsAJ == true){qZrHmAPsAJ = false;}
      if(RxEgsQxzDE == true){RxEgsQxzDE = false;}
      if(wGRXJKWTuP == true){wGRXJKWTuP = false;}
      if(OwKjccNrsn == true){OwKjccNrsn = false;}
      if(cfdQRKQUSJ == true){cfdQRKQUSJ = false;}
      if(ehOJOkHUyb == true){ehOJOkHUyb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDZPCJCAOW
{ 
  void XaPbLtkLtg()
  { 
      bool gPmhUWJhKN = false;
      bool xDwqdOhaLf = false;
      bool JwPsPPEeny = false;
      bool kIcNLWcPAM = false;
      bool ZBeapVuzpE = false;
      bool bMmQqjzsRF = false;
      bool SesMcoZifG = false;
      bool kSZzFIRnDs = false;
      bool TFniWYUMWa = false;
      bool WjyutuIRyA = false;
      bool wMSiTIlnLh = false;
      bool SKoXlNpJoE = false;
      bool TMMFjBUeEK = false;
      bool zzpCwHlFPN = false;
      bool lfBnHMtZIg = false;
      bool EybtfjzNzS = false;
      bool nGiAiTUlad = false;
      bool bktbRnLYyX = false;
      bool GtVXGBWuWM = false;
      bool HXGwYewAFm = false;
      string kEIVCzcXeP;
      string HaVhIJrLGT;
      string MrhHzqRmjI;
      string aQfNIjBOaU;
      string ddTGkBYtSd;
      string skinqrWBWK;
      string hpnVnptIZX;
      string HcjlpiXaVy;
      string SXTGOpgrVP;
      string NArPmnpxRt;
      string GPUtWPAwxI;
      string UufXrKVhHy;
      string ICmJKGkUzC;
      string rZJaqCCZiy;
      string oktMuSUTWc;
      string SIpTlEcKiP;
      string efxuPtlFgo;
      string HuyIIXHZOr;
      string lQxVjjjoom;
      string YrpTTJmzwB;
      if(kEIVCzcXeP == GPUtWPAwxI){gPmhUWJhKN = true;}
      else if(GPUtWPAwxI == kEIVCzcXeP){wMSiTIlnLh = true;}
      if(HaVhIJrLGT == UufXrKVhHy){xDwqdOhaLf = true;}
      else if(UufXrKVhHy == HaVhIJrLGT){SKoXlNpJoE = true;}
      if(MrhHzqRmjI == ICmJKGkUzC){JwPsPPEeny = true;}
      else if(ICmJKGkUzC == MrhHzqRmjI){TMMFjBUeEK = true;}
      if(aQfNIjBOaU == rZJaqCCZiy){kIcNLWcPAM = true;}
      else if(rZJaqCCZiy == aQfNIjBOaU){zzpCwHlFPN = true;}
      if(ddTGkBYtSd == oktMuSUTWc){ZBeapVuzpE = true;}
      else if(oktMuSUTWc == ddTGkBYtSd){lfBnHMtZIg = true;}
      if(skinqrWBWK == SIpTlEcKiP){bMmQqjzsRF = true;}
      else if(SIpTlEcKiP == skinqrWBWK){EybtfjzNzS = true;}
      if(hpnVnptIZX == efxuPtlFgo){SesMcoZifG = true;}
      else if(efxuPtlFgo == hpnVnptIZX){nGiAiTUlad = true;}
      if(HcjlpiXaVy == HuyIIXHZOr){kSZzFIRnDs = true;}
      if(SXTGOpgrVP == lQxVjjjoom){TFniWYUMWa = true;}
      if(NArPmnpxRt == YrpTTJmzwB){WjyutuIRyA = true;}
      while(HuyIIXHZOr == HcjlpiXaVy){bktbRnLYyX = true;}
      while(lQxVjjjoom == lQxVjjjoom){GtVXGBWuWM = true;}
      while(YrpTTJmzwB == YrpTTJmzwB){HXGwYewAFm = true;}
      if(gPmhUWJhKN == true){gPmhUWJhKN = false;}
      if(xDwqdOhaLf == true){xDwqdOhaLf = false;}
      if(JwPsPPEeny == true){JwPsPPEeny = false;}
      if(kIcNLWcPAM == true){kIcNLWcPAM = false;}
      if(ZBeapVuzpE == true){ZBeapVuzpE = false;}
      if(bMmQqjzsRF == true){bMmQqjzsRF = false;}
      if(SesMcoZifG == true){SesMcoZifG = false;}
      if(kSZzFIRnDs == true){kSZzFIRnDs = false;}
      if(TFniWYUMWa == true){TFniWYUMWa = false;}
      if(WjyutuIRyA == true){WjyutuIRyA = false;}
      if(wMSiTIlnLh == true){wMSiTIlnLh = false;}
      if(SKoXlNpJoE == true){SKoXlNpJoE = false;}
      if(TMMFjBUeEK == true){TMMFjBUeEK = false;}
      if(zzpCwHlFPN == true){zzpCwHlFPN = false;}
      if(lfBnHMtZIg == true){lfBnHMtZIg = false;}
      if(EybtfjzNzS == true){EybtfjzNzS = false;}
      if(nGiAiTUlad == true){nGiAiTUlad = false;}
      if(bktbRnLYyX == true){bktbRnLYyX = false;}
      if(GtVXGBWuWM == true){GtVXGBWuWM = false;}
      if(HXGwYewAFm == true){HXGwYewAFm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XNTSWTFDNW
{ 
  void UleHTAVzOT()
  { 
      bool CjFnZDKsEJ = false;
      bool MCNKqMLFns = false;
      bool pIFPkfLCOQ = false;
      bool oofzdguwDc = false;
      bool dSQwRUjSwt = false;
      bool CwUygsdoCt = false;
      bool qIenTXWNfJ = false;
      bool RPBKPXqJxQ = false;
      bool usGUOsThRj = false;
      bool DFsJkVmccs = false;
      bool yVmlcmtKiJ = false;
      bool CUqlyyBKYZ = false;
      bool EnwuGLWqYt = false;
      bool jOfESYFTqb = false;
      bool yJzIhiNGKl = false;
      bool TcDCnJZrfQ = false;
      bool QCkoZmnmTZ = false;
      bool sgSxbtonMX = false;
      bool xPglZGKdPI = false;
      bool yNnaKuXKhu = false;
      string UyoYGSyMEX;
      string pDcKPtdLlX;
      string GKgmNfrMNf;
      string wNCmLjRtbo;
      string qidADmMelx;
      string xKMcsJRCKZ;
      string ZlzYabBpyf;
      string ciiwfXgfia;
      string TNaPhlAZtC;
      string RPiCPFiFZb;
      string lVfFUNbQwV;
      string ckSjFLKjpo;
      string aawwNNAfga;
      string naGGoxhUtU;
      string JjdYYgwzwD;
      string tzOjAKZjqH;
      string NuiUgBeMtI;
      string dpoVeqxXWg;
      string QAjdgnLVGe;
      string WxdmGNBIqW;
      if(UyoYGSyMEX == lVfFUNbQwV){CjFnZDKsEJ = true;}
      else if(lVfFUNbQwV == UyoYGSyMEX){yVmlcmtKiJ = true;}
      if(pDcKPtdLlX == ckSjFLKjpo){MCNKqMLFns = true;}
      else if(ckSjFLKjpo == pDcKPtdLlX){CUqlyyBKYZ = true;}
      if(GKgmNfrMNf == aawwNNAfga){pIFPkfLCOQ = true;}
      else if(aawwNNAfga == GKgmNfrMNf){EnwuGLWqYt = true;}
      if(wNCmLjRtbo == naGGoxhUtU){oofzdguwDc = true;}
      else if(naGGoxhUtU == wNCmLjRtbo){jOfESYFTqb = true;}
      if(qidADmMelx == JjdYYgwzwD){dSQwRUjSwt = true;}
      else if(JjdYYgwzwD == qidADmMelx){yJzIhiNGKl = true;}
      if(xKMcsJRCKZ == tzOjAKZjqH){CwUygsdoCt = true;}
      else if(tzOjAKZjqH == xKMcsJRCKZ){TcDCnJZrfQ = true;}
      if(ZlzYabBpyf == NuiUgBeMtI){qIenTXWNfJ = true;}
      else if(NuiUgBeMtI == ZlzYabBpyf){QCkoZmnmTZ = true;}
      if(ciiwfXgfia == dpoVeqxXWg){RPBKPXqJxQ = true;}
      if(TNaPhlAZtC == QAjdgnLVGe){usGUOsThRj = true;}
      if(RPiCPFiFZb == WxdmGNBIqW){DFsJkVmccs = true;}
      while(dpoVeqxXWg == ciiwfXgfia){sgSxbtonMX = true;}
      while(QAjdgnLVGe == QAjdgnLVGe){xPglZGKdPI = true;}
      while(WxdmGNBIqW == WxdmGNBIqW){yNnaKuXKhu = true;}
      if(CjFnZDKsEJ == true){CjFnZDKsEJ = false;}
      if(MCNKqMLFns == true){MCNKqMLFns = false;}
      if(pIFPkfLCOQ == true){pIFPkfLCOQ = false;}
      if(oofzdguwDc == true){oofzdguwDc = false;}
      if(dSQwRUjSwt == true){dSQwRUjSwt = false;}
      if(CwUygsdoCt == true){CwUygsdoCt = false;}
      if(qIenTXWNfJ == true){qIenTXWNfJ = false;}
      if(RPBKPXqJxQ == true){RPBKPXqJxQ = false;}
      if(usGUOsThRj == true){usGUOsThRj = false;}
      if(DFsJkVmccs == true){DFsJkVmccs = false;}
      if(yVmlcmtKiJ == true){yVmlcmtKiJ = false;}
      if(CUqlyyBKYZ == true){CUqlyyBKYZ = false;}
      if(EnwuGLWqYt == true){EnwuGLWqYt = false;}
      if(jOfESYFTqb == true){jOfESYFTqb = false;}
      if(yJzIhiNGKl == true){yJzIhiNGKl = false;}
      if(TcDCnJZrfQ == true){TcDCnJZrfQ = false;}
      if(QCkoZmnmTZ == true){QCkoZmnmTZ = false;}
      if(sgSxbtonMX == true){sgSxbtonMX = false;}
      if(xPglZGKdPI == true){xPglZGKdPI = false;}
      if(yNnaKuXKhu == true){yNnaKuXKhu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OEBQQKGTEJ
{ 
  void DcXglmxBfG()
  { 
      bool eSYBmpnojA = false;
      bool OnJkPQrQqW = false;
      bool nFOqudYXtt = false;
      bool VYDkNoDmpY = false;
      bool IPlqdWyjic = false;
      bool rIIVuZEgGJ = false;
      bool QPuoeokXXZ = false;
      bool MFaROXSWNX = false;
      bool fooQCNQgpm = false;
      bool jVggHrUxMn = false;
      bool lZLJPlhpHW = false;
      bool HhThcbadmQ = false;
      bool XDhjopYtKV = false;
      bool DVJYlFceAP = false;
      bool eaZSfCCyDf = false;
      bool QpKuPhrbUZ = false;
      bool NnfkTlYtuX = false;
      bool ywcWlxdODm = false;
      bool nZpdEMKNIE = false;
      bool NAKaCqunzt = false;
      string yTmNtlINFf;
      string ulkXCUxWlq;
      string rkGrBuyfoK;
      string kOyiTgQlMk;
      string JdyHrEAhAL;
      string qnxmqNMuMz;
      string nbXttfnCEU;
      string ELKAgOlzAw;
      string uPfdSwQKqF;
      string UUYMxgFEML;
      string QxdeGfdxFc;
      string bNuPEXwtax;
      string PcLyAilxCA;
      string IhlnfxlAWm;
      string RTENdGZJIY;
      string kLcPwmleeX;
      string sgtFUsbGjG;
      string luWneuYxUs;
      string IcncOxFVrr;
      string LHVyskZzsj;
      if(yTmNtlINFf == QxdeGfdxFc){eSYBmpnojA = true;}
      else if(QxdeGfdxFc == yTmNtlINFf){lZLJPlhpHW = true;}
      if(ulkXCUxWlq == bNuPEXwtax){OnJkPQrQqW = true;}
      else if(bNuPEXwtax == ulkXCUxWlq){HhThcbadmQ = true;}
      if(rkGrBuyfoK == PcLyAilxCA){nFOqudYXtt = true;}
      else if(PcLyAilxCA == rkGrBuyfoK){XDhjopYtKV = true;}
      if(kOyiTgQlMk == IhlnfxlAWm){VYDkNoDmpY = true;}
      else if(IhlnfxlAWm == kOyiTgQlMk){DVJYlFceAP = true;}
      if(JdyHrEAhAL == RTENdGZJIY){IPlqdWyjic = true;}
      else if(RTENdGZJIY == JdyHrEAhAL){eaZSfCCyDf = true;}
      if(qnxmqNMuMz == kLcPwmleeX){rIIVuZEgGJ = true;}
      else if(kLcPwmleeX == qnxmqNMuMz){QpKuPhrbUZ = true;}
      if(nbXttfnCEU == sgtFUsbGjG){QPuoeokXXZ = true;}
      else if(sgtFUsbGjG == nbXttfnCEU){NnfkTlYtuX = true;}
      if(ELKAgOlzAw == luWneuYxUs){MFaROXSWNX = true;}
      if(uPfdSwQKqF == IcncOxFVrr){fooQCNQgpm = true;}
      if(UUYMxgFEML == LHVyskZzsj){jVggHrUxMn = true;}
      while(luWneuYxUs == ELKAgOlzAw){ywcWlxdODm = true;}
      while(IcncOxFVrr == IcncOxFVrr){nZpdEMKNIE = true;}
      while(LHVyskZzsj == LHVyskZzsj){NAKaCqunzt = true;}
      if(eSYBmpnojA == true){eSYBmpnojA = false;}
      if(OnJkPQrQqW == true){OnJkPQrQqW = false;}
      if(nFOqudYXtt == true){nFOqudYXtt = false;}
      if(VYDkNoDmpY == true){VYDkNoDmpY = false;}
      if(IPlqdWyjic == true){IPlqdWyjic = false;}
      if(rIIVuZEgGJ == true){rIIVuZEgGJ = false;}
      if(QPuoeokXXZ == true){QPuoeokXXZ = false;}
      if(MFaROXSWNX == true){MFaROXSWNX = false;}
      if(fooQCNQgpm == true){fooQCNQgpm = false;}
      if(jVggHrUxMn == true){jVggHrUxMn = false;}
      if(lZLJPlhpHW == true){lZLJPlhpHW = false;}
      if(HhThcbadmQ == true){HhThcbadmQ = false;}
      if(XDhjopYtKV == true){XDhjopYtKV = false;}
      if(DVJYlFceAP == true){DVJYlFceAP = false;}
      if(eaZSfCCyDf == true){eaZSfCCyDf = false;}
      if(QpKuPhrbUZ == true){QpKuPhrbUZ = false;}
      if(NnfkTlYtuX == true){NnfkTlYtuX = false;}
      if(ywcWlxdODm == true){ywcWlxdODm = false;}
      if(nZpdEMKNIE == true){nZpdEMKNIE = false;}
      if(NAKaCqunzt == true){NAKaCqunzt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DWPLPNYWYO
{ 
  void mhmhcMbcuF()
  { 
      bool YopompKFyY = false;
      bool jrNMHUGauo = false;
      bool OZZTskXzjU = false;
      bool HlANOokdVh = false;
      bool MUTUUuzdRM = false;
      bool tzsCmzPVwC = false;
      bool RKVdQxrzxR = false;
      bool jbEMcsFEyx = false;
      bool ksgXaHsyaP = false;
      bool ZOhTPBzpDX = false;
      bool DzgAcRufZs = false;
      bool sKXyQYcyDJ = false;
      bool EtYhqUtkxa = false;
      bool tPBatlMgtI = false;
      bool MNXgVPpiCq = false;
      bool XAmsSJZzJH = false;
      bool XJiyydIxEe = false;
      bool LwDtxqVrLa = false;
      bool dKhFCscHHj = false;
      bool LNWmkCeZhq = false;
      string nizidNNwCN;
      string aXtQfHxNJD;
      string UmChkOxIZt;
      string bqlWecrCso;
      string PrYBicFVKn;
      string fkzixBfRxP;
      string PEWIljkWkD;
      string OtTTmcOByI;
      string IbykOqqDZd;
      string waEdYKVQOz;
      string rikGZkQfuU;
      string meSoGnGktu;
      string shxHGmppuc;
      string HxlzPZpqLc;
      string ZLHEqRIPWk;
      string EjWTGKkdAl;
      string uZkSMorSYg;
      string xOYQUhZrPn;
      string eaTJXWaSsF;
      string nMpZgAZnrB;
      if(nizidNNwCN == rikGZkQfuU){YopompKFyY = true;}
      else if(rikGZkQfuU == nizidNNwCN){DzgAcRufZs = true;}
      if(aXtQfHxNJD == meSoGnGktu){jrNMHUGauo = true;}
      else if(meSoGnGktu == aXtQfHxNJD){sKXyQYcyDJ = true;}
      if(UmChkOxIZt == shxHGmppuc){OZZTskXzjU = true;}
      else if(shxHGmppuc == UmChkOxIZt){EtYhqUtkxa = true;}
      if(bqlWecrCso == HxlzPZpqLc){HlANOokdVh = true;}
      else if(HxlzPZpqLc == bqlWecrCso){tPBatlMgtI = true;}
      if(PrYBicFVKn == ZLHEqRIPWk){MUTUUuzdRM = true;}
      else if(ZLHEqRIPWk == PrYBicFVKn){MNXgVPpiCq = true;}
      if(fkzixBfRxP == EjWTGKkdAl){tzsCmzPVwC = true;}
      else if(EjWTGKkdAl == fkzixBfRxP){XAmsSJZzJH = true;}
      if(PEWIljkWkD == uZkSMorSYg){RKVdQxrzxR = true;}
      else if(uZkSMorSYg == PEWIljkWkD){XJiyydIxEe = true;}
      if(OtTTmcOByI == xOYQUhZrPn){jbEMcsFEyx = true;}
      if(IbykOqqDZd == eaTJXWaSsF){ksgXaHsyaP = true;}
      if(waEdYKVQOz == nMpZgAZnrB){ZOhTPBzpDX = true;}
      while(xOYQUhZrPn == OtTTmcOByI){LwDtxqVrLa = true;}
      while(eaTJXWaSsF == eaTJXWaSsF){dKhFCscHHj = true;}
      while(nMpZgAZnrB == nMpZgAZnrB){LNWmkCeZhq = true;}
      if(YopompKFyY == true){YopompKFyY = false;}
      if(jrNMHUGauo == true){jrNMHUGauo = false;}
      if(OZZTskXzjU == true){OZZTskXzjU = false;}
      if(HlANOokdVh == true){HlANOokdVh = false;}
      if(MUTUUuzdRM == true){MUTUUuzdRM = false;}
      if(tzsCmzPVwC == true){tzsCmzPVwC = false;}
      if(RKVdQxrzxR == true){RKVdQxrzxR = false;}
      if(jbEMcsFEyx == true){jbEMcsFEyx = false;}
      if(ksgXaHsyaP == true){ksgXaHsyaP = false;}
      if(ZOhTPBzpDX == true){ZOhTPBzpDX = false;}
      if(DzgAcRufZs == true){DzgAcRufZs = false;}
      if(sKXyQYcyDJ == true){sKXyQYcyDJ = false;}
      if(EtYhqUtkxa == true){EtYhqUtkxa = false;}
      if(tPBatlMgtI == true){tPBatlMgtI = false;}
      if(MNXgVPpiCq == true){MNXgVPpiCq = false;}
      if(XAmsSJZzJH == true){XAmsSJZzJH = false;}
      if(XJiyydIxEe == true){XJiyydIxEe = false;}
      if(LwDtxqVrLa == true){LwDtxqVrLa = false;}
      if(dKhFCscHHj == true){dKhFCscHHj = false;}
      if(LNWmkCeZhq == true){LNWmkCeZhq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QPENTZSXKY
{ 
  void bUGKeyEWGw()
  { 
      bool UtdNpACULy = false;
      bool bijPPqiKUf = false;
      bool RLsaKWDuqX = false;
      bool ssVsnSMhMF = false;
      bool jMMEIowCMY = false;
      bool sMnhWIBDCT = false;
      bool xHdmEiNqaw = false;
      bool dAyOuFyoRU = false;
      bool ZAhSegEmVe = false;
      bool RJesIciYzZ = false;
      bool aFbPurNYlR = false;
      bool KMkhswYKIX = false;
      bool dZUueTVEGR = false;
      bool VYorsUYSXm = false;
      bool SfAEUEXxAL = false;
      bool EXQauBkfka = false;
      bool WJRTukXsnX = false;
      bool XFmVFyYPZa = false;
      bool uXEuNyINxr = false;
      bool jrhwPJOgJj = false;
      string trkmzjCrDA;
      string CilTABhpij;
      string fsNscttLbi;
      string OEGGzHtebm;
      string YRBGNtQHfo;
      string TkHPsBerKE;
      string oqPTkyceTr;
      string HCOuKNqHfh;
      string dmemOdwpMy;
      string cCTWxhBgUO;
      string RknnhQWLEe;
      string JWLcaCLbEH;
      string BmRVOEiqxc;
      string LKlQPryqFy;
      string HkkhnFpqwt;
      string VYbMNdTRYc;
      string heNbSzkuMi;
      string DUWGAPBjhJ;
      string NquDGmhYCk;
      string YgRbPbWIOn;
      if(trkmzjCrDA == RknnhQWLEe){UtdNpACULy = true;}
      else if(RknnhQWLEe == trkmzjCrDA){aFbPurNYlR = true;}
      if(CilTABhpij == JWLcaCLbEH){bijPPqiKUf = true;}
      else if(JWLcaCLbEH == CilTABhpij){KMkhswYKIX = true;}
      if(fsNscttLbi == BmRVOEiqxc){RLsaKWDuqX = true;}
      else if(BmRVOEiqxc == fsNscttLbi){dZUueTVEGR = true;}
      if(OEGGzHtebm == LKlQPryqFy){ssVsnSMhMF = true;}
      else if(LKlQPryqFy == OEGGzHtebm){VYorsUYSXm = true;}
      if(YRBGNtQHfo == HkkhnFpqwt){jMMEIowCMY = true;}
      else if(HkkhnFpqwt == YRBGNtQHfo){SfAEUEXxAL = true;}
      if(TkHPsBerKE == VYbMNdTRYc){sMnhWIBDCT = true;}
      else if(VYbMNdTRYc == TkHPsBerKE){EXQauBkfka = true;}
      if(oqPTkyceTr == heNbSzkuMi){xHdmEiNqaw = true;}
      else if(heNbSzkuMi == oqPTkyceTr){WJRTukXsnX = true;}
      if(HCOuKNqHfh == DUWGAPBjhJ){dAyOuFyoRU = true;}
      if(dmemOdwpMy == NquDGmhYCk){ZAhSegEmVe = true;}
      if(cCTWxhBgUO == YgRbPbWIOn){RJesIciYzZ = true;}
      while(DUWGAPBjhJ == HCOuKNqHfh){XFmVFyYPZa = true;}
      while(NquDGmhYCk == NquDGmhYCk){uXEuNyINxr = true;}
      while(YgRbPbWIOn == YgRbPbWIOn){jrhwPJOgJj = true;}
      if(UtdNpACULy == true){UtdNpACULy = false;}
      if(bijPPqiKUf == true){bijPPqiKUf = false;}
      if(RLsaKWDuqX == true){RLsaKWDuqX = false;}
      if(ssVsnSMhMF == true){ssVsnSMhMF = false;}
      if(jMMEIowCMY == true){jMMEIowCMY = false;}
      if(sMnhWIBDCT == true){sMnhWIBDCT = false;}
      if(xHdmEiNqaw == true){xHdmEiNqaw = false;}
      if(dAyOuFyoRU == true){dAyOuFyoRU = false;}
      if(ZAhSegEmVe == true){ZAhSegEmVe = false;}
      if(RJesIciYzZ == true){RJesIciYzZ = false;}
      if(aFbPurNYlR == true){aFbPurNYlR = false;}
      if(KMkhswYKIX == true){KMkhswYKIX = false;}
      if(dZUueTVEGR == true){dZUueTVEGR = false;}
      if(VYorsUYSXm == true){VYorsUYSXm = false;}
      if(SfAEUEXxAL == true){SfAEUEXxAL = false;}
      if(EXQauBkfka == true){EXQauBkfka = false;}
      if(WJRTukXsnX == true){WJRTukXsnX = false;}
      if(XFmVFyYPZa == true){XFmVFyYPZa = false;}
      if(uXEuNyINxr == true){uXEuNyINxr = false;}
      if(jrhwPJOgJj == true){jrhwPJOgJj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CFJMYDHGQI
{ 
  void GwfHCbNplj()
  { 
      bool EMwzuqhWJt = false;
      bool TQVgEgqNST = false;
      bool GSUAFpMmbz = false;
      bool yoypoXgFRd = false;
      bool eyLYPiHgIG = false;
      bool alEQZlrwtF = false;
      bool dtuJueRerg = false;
      bool zlunoIHujV = false;
      bool hfdUYMjhPC = false;
      bool ekLMAjCBdk = false;
      bool RbnbHopPbR = false;
      bool ewMYWxQaki = false;
      bool tiPoBOZinE = false;
      bool FFRzDFrCMi = false;
      bool VUGyXiXmoC = false;
      bool TbPtpiMyZr = false;
      bool OHbWMYdMUQ = false;
      bool FNNBNZcQRS = false;
      bool pmskjcpXIU = false;
      bool rtcTUNsiky = false;
      string qOUzLiHTVC;
      string ZrzOpKrnfZ;
      string twUufCwlok;
      string yViCnXYASu;
      string EOlNTMzzgL;
      string ObpwHtsZSI;
      string mVekEDJxZR;
      string krUkVeJHaS;
      string DwEcVWelts;
      string ezgKHijBJP;
      string DCZOaWGEab;
      string jkyAFqQCOh;
      string XWCfmkLJdm;
      string uIxKPAWoCz;
      string PaKSIsAgEP;
      string RhmbqfAsbo;
      string LwangbnnjF;
      string TazPRxLjWt;
      string jdFNUMVUSj;
      string AdNMnSzWkg;
      if(qOUzLiHTVC == DCZOaWGEab){EMwzuqhWJt = true;}
      else if(DCZOaWGEab == qOUzLiHTVC){RbnbHopPbR = true;}
      if(ZrzOpKrnfZ == jkyAFqQCOh){TQVgEgqNST = true;}
      else if(jkyAFqQCOh == ZrzOpKrnfZ){ewMYWxQaki = true;}
      if(twUufCwlok == XWCfmkLJdm){GSUAFpMmbz = true;}
      else if(XWCfmkLJdm == twUufCwlok){tiPoBOZinE = true;}
      if(yViCnXYASu == uIxKPAWoCz){yoypoXgFRd = true;}
      else if(uIxKPAWoCz == yViCnXYASu){FFRzDFrCMi = true;}
      if(EOlNTMzzgL == PaKSIsAgEP){eyLYPiHgIG = true;}
      else if(PaKSIsAgEP == EOlNTMzzgL){VUGyXiXmoC = true;}
      if(ObpwHtsZSI == RhmbqfAsbo){alEQZlrwtF = true;}
      else if(RhmbqfAsbo == ObpwHtsZSI){TbPtpiMyZr = true;}
      if(mVekEDJxZR == LwangbnnjF){dtuJueRerg = true;}
      else if(LwangbnnjF == mVekEDJxZR){OHbWMYdMUQ = true;}
      if(krUkVeJHaS == TazPRxLjWt){zlunoIHujV = true;}
      if(DwEcVWelts == jdFNUMVUSj){hfdUYMjhPC = true;}
      if(ezgKHijBJP == AdNMnSzWkg){ekLMAjCBdk = true;}
      while(TazPRxLjWt == krUkVeJHaS){FNNBNZcQRS = true;}
      while(jdFNUMVUSj == jdFNUMVUSj){pmskjcpXIU = true;}
      while(AdNMnSzWkg == AdNMnSzWkg){rtcTUNsiky = true;}
      if(EMwzuqhWJt == true){EMwzuqhWJt = false;}
      if(TQVgEgqNST == true){TQVgEgqNST = false;}
      if(GSUAFpMmbz == true){GSUAFpMmbz = false;}
      if(yoypoXgFRd == true){yoypoXgFRd = false;}
      if(eyLYPiHgIG == true){eyLYPiHgIG = false;}
      if(alEQZlrwtF == true){alEQZlrwtF = false;}
      if(dtuJueRerg == true){dtuJueRerg = false;}
      if(zlunoIHujV == true){zlunoIHujV = false;}
      if(hfdUYMjhPC == true){hfdUYMjhPC = false;}
      if(ekLMAjCBdk == true){ekLMAjCBdk = false;}
      if(RbnbHopPbR == true){RbnbHopPbR = false;}
      if(ewMYWxQaki == true){ewMYWxQaki = false;}
      if(tiPoBOZinE == true){tiPoBOZinE = false;}
      if(FFRzDFrCMi == true){FFRzDFrCMi = false;}
      if(VUGyXiXmoC == true){VUGyXiXmoC = false;}
      if(TbPtpiMyZr == true){TbPtpiMyZr = false;}
      if(OHbWMYdMUQ == true){OHbWMYdMUQ = false;}
      if(FNNBNZcQRS == true){FNNBNZcQRS = false;}
      if(pmskjcpXIU == true){pmskjcpXIU = false;}
      if(rtcTUNsiky == true){rtcTUNsiky = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VSVPESNSMZ
{ 
  void XTfdNNUwYT()
  { 
      bool npqfumouyq = false;
      bool pGiEWsfzNk = false;
      bool AWcHXsFQar = false;
      bool GbJnITLCCQ = false;
      bool VRubaNxfdj = false;
      bool NQqKLQNjIC = false;
      bool gYUFkNxuwC = false;
      bool gcwxOiaAfJ = false;
      bool uYmpepkzcr = false;
      bool GatAjxwpqN = false;
      bool QCjaCjTtub = false;
      bool oMEyGHldZt = false;
      bool cxRDuFiwNQ = false;
      bool mkJSssoLmu = false;
      bool WpDACsWusb = false;
      bool LRQwkSkgfx = false;
      bool BXgdoDDkFN = false;
      bool SZpeXltQAB = false;
      bool imCkFUUMhZ = false;
      bool IHfptzIYLy = false;
      string zaJFOnQPPk;
      string DqysKpEMUT;
      string niTyYCRwEy;
      string IkOsQHbIIk;
      string cQsIRGNnFr;
      string KbDqlPGLfM;
      string VUKQcScEcC;
      string NuEjqXoKgS;
      string ndpLnghXHB;
      string AQcwOIFcfy;
      string cILDdOXTAO;
      string audNXrdycu;
      string kFxaBxSHUh;
      string RMehofRmhY;
      string JNWrZElPYW;
      string dGzjNXLjBg;
      string wPyRwNQwXr;
      string aqQDlWhEAw;
      string KDiyDLMtTQ;
      string TgkAcsPFuM;
      if(zaJFOnQPPk == cILDdOXTAO){npqfumouyq = true;}
      else if(cILDdOXTAO == zaJFOnQPPk){QCjaCjTtub = true;}
      if(DqysKpEMUT == audNXrdycu){pGiEWsfzNk = true;}
      else if(audNXrdycu == DqysKpEMUT){oMEyGHldZt = true;}
      if(niTyYCRwEy == kFxaBxSHUh){AWcHXsFQar = true;}
      else if(kFxaBxSHUh == niTyYCRwEy){cxRDuFiwNQ = true;}
      if(IkOsQHbIIk == RMehofRmhY){GbJnITLCCQ = true;}
      else if(RMehofRmhY == IkOsQHbIIk){mkJSssoLmu = true;}
      if(cQsIRGNnFr == JNWrZElPYW){VRubaNxfdj = true;}
      else if(JNWrZElPYW == cQsIRGNnFr){WpDACsWusb = true;}
      if(KbDqlPGLfM == dGzjNXLjBg){NQqKLQNjIC = true;}
      else if(dGzjNXLjBg == KbDqlPGLfM){LRQwkSkgfx = true;}
      if(VUKQcScEcC == wPyRwNQwXr){gYUFkNxuwC = true;}
      else if(wPyRwNQwXr == VUKQcScEcC){BXgdoDDkFN = true;}
      if(NuEjqXoKgS == aqQDlWhEAw){gcwxOiaAfJ = true;}
      if(ndpLnghXHB == KDiyDLMtTQ){uYmpepkzcr = true;}
      if(AQcwOIFcfy == TgkAcsPFuM){GatAjxwpqN = true;}
      while(aqQDlWhEAw == NuEjqXoKgS){SZpeXltQAB = true;}
      while(KDiyDLMtTQ == KDiyDLMtTQ){imCkFUUMhZ = true;}
      while(TgkAcsPFuM == TgkAcsPFuM){IHfptzIYLy = true;}
      if(npqfumouyq == true){npqfumouyq = false;}
      if(pGiEWsfzNk == true){pGiEWsfzNk = false;}
      if(AWcHXsFQar == true){AWcHXsFQar = false;}
      if(GbJnITLCCQ == true){GbJnITLCCQ = false;}
      if(VRubaNxfdj == true){VRubaNxfdj = false;}
      if(NQqKLQNjIC == true){NQqKLQNjIC = false;}
      if(gYUFkNxuwC == true){gYUFkNxuwC = false;}
      if(gcwxOiaAfJ == true){gcwxOiaAfJ = false;}
      if(uYmpepkzcr == true){uYmpepkzcr = false;}
      if(GatAjxwpqN == true){GatAjxwpqN = false;}
      if(QCjaCjTtub == true){QCjaCjTtub = false;}
      if(oMEyGHldZt == true){oMEyGHldZt = false;}
      if(cxRDuFiwNQ == true){cxRDuFiwNQ = false;}
      if(mkJSssoLmu == true){mkJSssoLmu = false;}
      if(WpDACsWusb == true){WpDACsWusb = false;}
      if(LRQwkSkgfx == true){LRQwkSkgfx = false;}
      if(BXgdoDDkFN == true){BXgdoDDkFN = false;}
      if(SZpeXltQAB == true){SZpeXltQAB = false;}
      if(imCkFUUMhZ == true){imCkFUUMhZ = false;}
      if(IHfptzIYLy == true){IHfptzIYLy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UZSGFBJFUO
{ 
  void lizWGXLsjY()
  { 
      bool dbOcsBDstZ = false;
      bool wYJWtEPrIs = false;
      bool uGLFaQNXRc = false;
      bool TOBNBnneMi = false;
      bool zFPLQwpDhg = false;
      bool SxOxAWPICb = false;
      bool neaRGhXuUF = false;
      bool QjeZspqAod = false;
      bool ZJpkKWzENe = false;
      bool YfcjtTdyFh = false;
      bool YthbPiSnDJ = false;
      bool fPTYBeopGi = false;
      bool hThpgjHteY = false;
      bool MruGEfaNUb = false;
      bool DKADyJLEhP = false;
      bool emqVzFMquf = false;
      bool aXIdxnTMTV = false;
      bool DbVefWSdrX = false;
      bool YDLPtYBZGz = false;
      bool SiSoAfCVGK = false;
      string ndHEDuJyql;
      string QbNdLBYFSK;
      string SNBiIqbmWJ;
      string FTmsDGRrRL;
      string dSaHeaMrgj;
      string XsTBDZcXwL;
      string SWahfxnTaE;
      string ifmHgzlsEh;
      string djFmkMzkpc;
      string dswFrGrrah;
      string lsQcArFMTD;
      string miTOgiQmwT;
      string xDcyZojgOZ;
      string HtRVukScms;
      string HmQlouYgYJ;
      string oEwHjhPSCK;
      string HXxswsQxSu;
      string QnADMJlqJe;
      string PCIFkDyKlM;
      string UzabkioXpu;
      if(ndHEDuJyql == lsQcArFMTD){dbOcsBDstZ = true;}
      else if(lsQcArFMTD == ndHEDuJyql){YthbPiSnDJ = true;}
      if(QbNdLBYFSK == miTOgiQmwT){wYJWtEPrIs = true;}
      else if(miTOgiQmwT == QbNdLBYFSK){fPTYBeopGi = true;}
      if(SNBiIqbmWJ == xDcyZojgOZ){uGLFaQNXRc = true;}
      else if(xDcyZojgOZ == SNBiIqbmWJ){hThpgjHteY = true;}
      if(FTmsDGRrRL == HtRVukScms){TOBNBnneMi = true;}
      else if(HtRVukScms == FTmsDGRrRL){MruGEfaNUb = true;}
      if(dSaHeaMrgj == HmQlouYgYJ){zFPLQwpDhg = true;}
      else if(HmQlouYgYJ == dSaHeaMrgj){DKADyJLEhP = true;}
      if(XsTBDZcXwL == oEwHjhPSCK){SxOxAWPICb = true;}
      else if(oEwHjhPSCK == XsTBDZcXwL){emqVzFMquf = true;}
      if(SWahfxnTaE == HXxswsQxSu){neaRGhXuUF = true;}
      else if(HXxswsQxSu == SWahfxnTaE){aXIdxnTMTV = true;}
      if(ifmHgzlsEh == QnADMJlqJe){QjeZspqAod = true;}
      if(djFmkMzkpc == PCIFkDyKlM){ZJpkKWzENe = true;}
      if(dswFrGrrah == UzabkioXpu){YfcjtTdyFh = true;}
      while(QnADMJlqJe == ifmHgzlsEh){DbVefWSdrX = true;}
      while(PCIFkDyKlM == PCIFkDyKlM){YDLPtYBZGz = true;}
      while(UzabkioXpu == UzabkioXpu){SiSoAfCVGK = true;}
      if(dbOcsBDstZ == true){dbOcsBDstZ = false;}
      if(wYJWtEPrIs == true){wYJWtEPrIs = false;}
      if(uGLFaQNXRc == true){uGLFaQNXRc = false;}
      if(TOBNBnneMi == true){TOBNBnneMi = false;}
      if(zFPLQwpDhg == true){zFPLQwpDhg = false;}
      if(SxOxAWPICb == true){SxOxAWPICb = false;}
      if(neaRGhXuUF == true){neaRGhXuUF = false;}
      if(QjeZspqAod == true){QjeZspqAod = false;}
      if(ZJpkKWzENe == true){ZJpkKWzENe = false;}
      if(YfcjtTdyFh == true){YfcjtTdyFh = false;}
      if(YthbPiSnDJ == true){YthbPiSnDJ = false;}
      if(fPTYBeopGi == true){fPTYBeopGi = false;}
      if(hThpgjHteY == true){hThpgjHteY = false;}
      if(MruGEfaNUb == true){MruGEfaNUb = false;}
      if(DKADyJLEhP == true){DKADyJLEhP = false;}
      if(emqVzFMquf == true){emqVzFMquf = false;}
      if(aXIdxnTMTV == true){aXIdxnTMTV = false;}
      if(DbVefWSdrX == true){DbVefWSdrX = false;}
      if(YDLPtYBZGz == true){YDLPtYBZGz = false;}
      if(SiSoAfCVGK == true){SiSoAfCVGK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RXWCSRXQIP
{ 
  void dAbmMHbeWI()
  { 
      bool aCQgacVFrA = false;
      bool xeAUrhVWfu = false;
      bool laqADIbrez = false;
      bool EFkiUVOrlJ = false;
      bool OdwTqremMd = false;
      bool PQfExAKPcS = false;
      bool BcZswrtQzW = false;
      bool TckWgIdXIL = false;
      bool dnfBinYflU = false;
      bool KyOTIkDDXz = false;
      bool xNmoKlfJXo = false;
      bool VmGRoMxYJH = false;
      bool SNeeMUNQNu = false;
      bool FazJNPBpqx = false;
      bool IPIxzWrxdw = false;
      bool ndsPgiiHco = false;
      bool XOwcitmxEY = false;
      bool LGhMzCFhfo = false;
      bool cQlRGahjbd = false;
      bool gsNBYsTfNE = false;
      string hRZFVnQqzK;
      string dhfYXIMLNR;
      string XpaeklJjzM;
      string mdiwwOiWHg;
      string zezQIOQSKb;
      string nfsjeqquTj;
      string dfqmXAyibI;
      string ZoEfRsqKVW;
      string UpZXXHjzRE;
      string WmDWDSnLsI;
      string QgqBCzbMSk;
      string AgZwOmGTPP;
      string PzQWlllgcy;
      string FeRNGnzXVY;
      string fXffEpNGHP;
      string LTwcsQPTPQ;
      string MtjTfUPLpa;
      string niypjrSkSu;
      string XeYNmkinUo;
      string XfHFLkmMzi;
      if(hRZFVnQqzK == QgqBCzbMSk){aCQgacVFrA = true;}
      else if(QgqBCzbMSk == hRZFVnQqzK){xNmoKlfJXo = true;}
      if(dhfYXIMLNR == AgZwOmGTPP){xeAUrhVWfu = true;}
      else if(AgZwOmGTPP == dhfYXIMLNR){VmGRoMxYJH = true;}
      if(XpaeklJjzM == PzQWlllgcy){laqADIbrez = true;}
      else if(PzQWlllgcy == XpaeklJjzM){SNeeMUNQNu = true;}
      if(mdiwwOiWHg == FeRNGnzXVY){EFkiUVOrlJ = true;}
      else if(FeRNGnzXVY == mdiwwOiWHg){FazJNPBpqx = true;}
      if(zezQIOQSKb == fXffEpNGHP){OdwTqremMd = true;}
      else if(fXffEpNGHP == zezQIOQSKb){IPIxzWrxdw = true;}
      if(nfsjeqquTj == LTwcsQPTPQ){PQfExAKPcS = true;}
      else if(LTwcsQPTPQ == nfsjeqquTj){ndsPgiiHco = true;}
      if(dfqmXAyibI == MtjTfUPLpa){BcZswrtQzW = true;}
      else if(MtjTfUPLpa == dfqmXAyibI){XOwcitmxEY = true;}
      if(ZoEfRsqKVW == niypjrSkSu){TckWgIdXIL = true;}
      if(UpZXXHjzRE == XeYNmkinUo){dnfBinYflU = true;}
      if(WmDWDSnLsI == XfHFLkmMzi){KyOTIkDDXz = true;}
      while(niypjrSkSu == ZoEfRsqKVW){LGhMzCFhfo = true;}
      while(XeYNmkinUo == XeYNmkinUo){cQlRGahjbd = true;}
      while(XfHFLkmMzi == XfHFLkmMzi){gsNBYsTfNE = true;}
      if(aCQgacVFrA == true){aCQgacVFrA = false;}
      if(xeAUrhVWfu == true){xeAUrhVWfu = false;}
      if(laqADIbrez == true){laqADIbrez = false;}
      if(EFkiUVOrlJ == true){EFkiUVOrlJ = false;}
      if(OdwTqremMd == true){OdwTqremMd = false;}
      if(PQfExAKPcS == true){PQfExAKPcS = false;}
      if(BcZswrtQzW == true){BcZswrtQzW = false;}
      if(TckWgIdXIL == true){TckWgIdXIL = false;}
      if(dnfBinYflU == true){dnfBinYflU = false;}
      if(KyOTIkDDXz == true){KyOTIkDDXz = false;}
      if(xNmoKlfJXo == true){xNmoKlfJXo = false;}
      if(VmGRoMxYJH == true){VmGRoMxYJH = false;}
      if(SNeeMUNQNu == true){SNeeMUNQNu = false;}
      if(FazJNPBpqx == true){FazJNPBpqx = false;}
      if(IPIxzWrxdw == true){IPIxzWrxdw = false;}
      if(ndsPgiiHco == true){ndsPgiiHco = false;}
      if(XOwcitmxEY == true){XOwcitmxEY = false;}
      if(LGhMzCFhfo == true){LGhMzCFhfo = false;}
      if(cQlRGahjbd == true){cQlRGahjbd = false;}
      if(gsNBYsTfNE == true){gsNBYsTfNE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QELXQTBCLJ
{ 
  void uDpElgycKT()
  { 
      bool gPCopacDZG = false;
      bool qPJzrINuGc = false;
      bool RMbdUILHDs = false;
      bool slSFNrACPj = false;
      bool lXrxdtmTCx = false;
      bool JAHBVTnXUh = false;
      bool PUzfMEwDlA = false;
      bool HKeVpsUeAa = false;
      bool VqEGjseRjs = false;
      bool EchhTQYLkY = false;
      bool xigBpyVkKc = false;
      bool yIXtMYQswS = false;
      bool ZeTrwecwBZ = false;
      bool TJtaclJCPk = false;
      bool XsHHtuFnVu = false;
      bool AePRzSPnFK = false;
      bool VYijIoOwQZ = false;
      bool ONcLugWMxA = false;
      bool YoaGZoscbK = false;
      bool WVxFOzKWyF = false;
      string yzWELgfcck;
      string FRiWnSfJrZ;
      string qhSJHHxXgS;
      string wOTKfgnMal;
      string IWBYZVETHh;
      string jBLCEQgNxE;
      string jIuKoqyYpG;
      string dTiFRTgsik;
      string CcPyhuDRFP;
      string zaOVCzapji;
      string XfcBDQSFkj;
      string ineMBGswbs;
      string mgSZGDEMDR;
      string spIzMWAOtR;
      string cxgVgLuCUw;
      string GdNquqMDtA;
      string LFCSqsefAe;
      string FeBKQoAxst;
      string HCrGLObRDV;
      string JxTtGWuNdm;
      if(yzWELgfcck == XfcBDQSFkj){gPCopacDZG = true;}
      else if(XfcBDQSFkj == yzWELgfcck){xigBpyVkKc = true;}
      if(FRiWnSfJrZ == ineMBGswbs){qPJzrINuGc = true;}
      else if(ineMBGswbs == FRiWnSfJrZ){yIXtMYQswS = true;}
      if(qhSJHHxXgS == mgSZGDEMDR){RMbdUILHDs = true;}
      else if(mgSZGDEMDR == qhSJHHxXgS){ZeTrwecwBZ = true;}
      if(wOTKfgnMal == spIzMWAOtR){slSFNrACPj = true;}
      else if(spIzMWAOtR == wOTKfgnMal){TJtaclJCPk = true;}
      if(IWBYZVETHh == cxgVgLuCUw){lXrxdtmTCx = true;}
      else if(cxgVgLuCUw == IWBYZVETHh){XsHHtuFnVu = true;}
      if(jBLCEQgNxE == GdNquqMDtA){JAHBVTnXUh = true;}
      else if(GdNquqMDtA == jBLCEQgNxE){AePRzSPnFK = true;}
      if(jIuKoqyYpG == LFCSqsefAe){PUzfMEwDlA = true;}
      else if(LFCSqsefAe == jIuKoqyYpG){VYijIoOwQZ = true;}
      if(dTiFRTgsik == FeBKQoAxst){HKeVpsUeAa = true;}
      if(CcPyhuDRFP == HCrGLObRDV){VqEGjseRjs = true;}
      if(zaOVCzapji == JxTtGWuNdm){EchhTQYLkY = true;}
      while(FeBKQoAxst == dTiFRTgsik){ONcLugWMxA = true;}
      while(HCrGLObRDV == HCrGLObRDV){YoaGZoscbK = true;}
      while(JxTtGWuNdm == JxTtGWuNdm){WVxFOzKWyF = true;}
      if(gPCopacDZG == true){gPCopacDZG = false;}
      if(qPJzrINuGc == true){qPJzrINuGc = false;}
      if(RMbdUILHDs == true){RMbdUILHDs = false;}
      if(slSFNrACPj == true){slSFNrACPj = false;}
      if(lXrxdtmTCx == true){lXrxdtmTCx = false;}
      if(JAHBVTnXUh == true){JAHBVTnXUh = false;}
      if(PUzfMEwDlA == true){PUzfMEwDlA = false;}
      if(HKeVpsUeAa == true){HKeVpsUeAa = false;}
      if(VqEGjseRjs == true){VqEGjseRjs = false;}
      if(EchhTQYLkY == true){EchhTQYLkY = false;}
      if(xigBpyVkKc == true){xigBpyVkKc = false;}
      if(yIXtMYQswS == true){yIXtMYQswS = false;}
      if(ZeTrwecwBZ == true){ZeTrwecwBZ = false;}
      if(TJtaclJCPk == true){TJtaclJCPk = false;}
      if(XsHHtuFnVu == true){XsHHtuFnVu = false;}
      if(AePRzSPnFK == true){AePRzSPnFK = false;}
      if(VYijIoOwQZ == true){VYijIoOwQZ = false;}
      if(ONcLugWMxA == true){ONcLugWMxA = false;}
      if(YoaGZoscbK == true){YoaGZoscbK = false;}
      if(WVxFOzKWyF == true){WVxFOzKWyF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OQVTZSJKCZ
{ 
  void tguDsCbcKl()
  { 
      bool xTXqUNIQIK = false;
      bool tQKAGOVCMB = false;
      bool LMnZuFEHZV = false;
      bool WYBNbzXWqy = false;
      bool TlLVkKfcbC = false;
      bool kVdbrkexwP = false;
      bool IBqlmUPxYG = false;
      bool qzLNhZARnj = false;
      bool ZbeWkBuYUq = false;
      bool UZabpSuYiQ = false;
      bool uiEULlJPtS = false;
      bool jMILogVTBk = false;
      bool YpbglRYjXP = false;
      bool daiXopXJLz = false;
      bool qeeBGHQOlI = false;
      bool waXyqEGWit = false;
      bool MZrdoIdkWz = false;
      bool JLICssKZae = false;
      bool AJyOSCDjfj = false;
      bool iAaRlRmAMx = false;
      string CDNKmRyYOk;
      string rpuhnllsin;
      string QpAdonWegl;
      string HdQtETfrHZ;
      string ApElCMiqyo;
      string bAzUfLCiVy;
      string tSrccNYAdU;
      string FtlInZlObb;
      string FfgrJHeuNr;
      string QwVIegyaIo;
      string mhNcihOqfF;
      string ZmHssOkzSV;
      string idmkDIXccH;
      string bKGlnWSDIb;
      string rmOHSdocOQ;
      string uzHlFJubZZ;
      string JkOYdOgUFW;
      string whpqcuPeRY;
      string TuOLMcCUfe;
      string apdiRHXpdE;
      if(CDNKmRyYOk == mhNcihOqfF){xTXqUNIQIK = true;}
      else if(mhNcihOqfF == CDNKmRyYOk){uiEULlJPtS = true;}
      if(rpuhnllsin == ZmHssOkzSV){tQKAGOVCMB = true;}
      else if(ZmHssOkzSV == rpuhnllsin){jMILogVTBk = true;}
      if(QpAdonWegl == idmkDIXccH){LMnZuFEHZV = true;}
      else if(idmkDIXccH == QpAdonWegl){YpbglRYjXP = true;}
      if(HdQtETfrHZ == bKGlnWSDIb){WYBNbzXWqy = true;}
      else if(bKGlnWSDIb == HdQtETfrHZ){daiXopXJLz = true;}
      if(ApElCMiqyo == rmOHSdocOQ){TlLVkKfcbC = true;}
      else if(rmOHSdocOQ == ApElCMiqyo){qeeBGHQOlI = true;}
      if(bAzUfLCiVy == uzHlFJubZZ){kVdbrkexwP = true;}
      else if(uzHlFJubZZ == bAzUfLCiVy){waXyqEGWit = true;}
      if(tSrccNYAdU == JkOYdOgUFW){IBqlmUPxYG = true;}
      else if(JkOYdOgUFW == tSrccNYAdU){MZrdoIdkWz = true;}
      if(FtlInZlObb == whpqcuPeRY){qzLNhZARnj = true;}
      if(FfgrJHeuNr == TuOLMcCUfe){ZbeWkBuYUq = true;}
      if(QwVIegyaIo == apdiRHXpdE){UZabpSuYiQ = true;}
      while(whpqcuPeRY == FtlInZlObb){JLICssKZae = true;}
      while(TuOLMcCUfe == TuOLMcCUfe){AJyOSCDjfj = true;}
      while(apdiRHXpdE == apdiRHXpdE){iAaRlRmAMx = true;}
      if(xTXqUNIQIK == true){xTXqUNIQIK = false;}
      if(tQKAGOVCMB == true){tQKAGOVCMB = false;}
      if(LMnZuFEHZV == true){LMnZuFEHZV = false;}
      if(WYBNbzXWqy == true){WYBNbzXWqy = false;}
      if(TlLVkKfcbC == true){TlLVkKfcbC = false;}
      if(kVdbrkexwP == true){kVdbrkexwP = false;}
      if(IBqlmUPxYG == true){IBqlmUPxYG = false;}
      if(qzLNhZARnj == true){qzLNhZARnj = false;}
      if(ZbeWkBuYUq == true){ZbeWkBuYUq = false;}
      if(UZabpSuYiQ == true){UZabpSuYiQ = false;}
      if(uiEULlJPtS == true){uiEULlJPtS = false;}
      if(jMILogVTBk == true){jMILogVTBk = false;}
      if(YpbglRYjXP == true){YpbglRYjXP = false;}
      if(daiXopXJLz == true){daiXopXJLz = false;}
      if(qeeBGHQOlI == true){qeeBGHQOlI = false;}
      if(waXyqEGWit == true){waXyqEGWit = false;}
      if(MZrdoIdkWz == true){MZrdoIdkWz = false;}
      if(JLICssKZae == true){JLICssKZae = false;}
      if(AJyOSCDjfj == true){AJyOSCDjfj = false;}
      if(iAaRlRmAMx == true){iAaRlRmAMx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XXFPEZHTSL
{ 
  void XEwSFQTZRH()
  { 
      bool XhOknuanEN = false;
      bool KFPFrgundY = false;
      bool qsYwijzpFM = false;
      bool VgOVIozyBL = false;
      bool wqNhSfoCDs = false;
      bool VrfNFeJRCD = false;
      bool wkhrrcpsxC = false;
      bool hxlRbAeqdD = false;
      bool txlLqcBAQd = false;
      bool fhuyPLIVoo = false;
      bool owFALXFNkF = false;
      bool ASnzIyyWAO = false;
      bool bpbSWABmCQ = false;
      bool qIBnNyrkzS = false;
      bool XmOLcMtwoQ = false;
      bool MlUaMyTldL = false;
      bool VRLUNqRzkK = false;
      bool GNWhqoaPpK = false;
      bool GFxlDFnZaO = false;
      bool dFHnwFatyl = false;
      string QWkKssVFpZ;
      string wlIKgzOZWd;
      string NVBYlqFSBQ;
      string meHAiSrSTu;
      string KPyspSDwSx;
      string tYYPgtVMYB;
      string mDDZlQdHbO;
      string GwGbSxXIiT;
      string nJzEVNGqTo;
      string xfsRHHMYGY;
      string nuUEqySxwi;
      string VMdFMdDzDY;
      string KlmlQaCnTL;
      string kzBJesnuMW;
      string uJukSjCnFd;
      string DNUhOBHimQ;
      string uddkxWLTZT;
      string pHlgcBqCSg;
      string XNipHXeSuc;
      string kFIwaQfJmw;
      if(QWkKssVFpZ == nuUEqySxwi){XhOknuanEN = true;}
      else if(nuUEqySxwi == QWkKssVFpZ){owFALXFNkF = true;}
      if(wlIKgzOZWd == VMdFMdDzDY){KFPFrgundY = true;}
      else if(VMdFMdDzDY == wlIKgzOZWd){ASnzIyyWAO = true;}
      if(NVBYlqFSBQ == KlmlQaCnTL){qsYwijzpFM = true;}
      else if(KlmlQaCnTL == NVBYlqFSBQ){bpbSWABmCQ = true;}
      if(meHAiSrSTu == kzBJesnuMW){VgOVIozyBL = true;}
      else if(kzBJesnuMW == meHAiSrSTu){qIBnNyrkzS = true;}
      if(KPyspSDwSx == uJukSjCnFd){wqNhSfoCDs = true;}
      else if(uJukSjCnFd == KPyspSDwSx){XmOLcMtwoQ = true;}
      if(tYYPgtVMYB == DNUhOBHimQ){VrfNFeJRCD = true;}
      else if(DNUhOBHimQ == tYYPgtVMYB){MlUaMyTldL = true;}
      if(mDDZlQdHbO == uddkxWLTZT){wkhrrcpsxC = true;}
      else if(uddkxWLTZT == mDDZlQdHbO){VRLUNqRzkK = true;}
      if(GwGbSxXIiT == pHlgcBqCSg){hxlRbAeqdD = true;}
      if(nJzEVNGqTo == XNipHXeSuc){txlLqcBAQd = true;}
      if(xfsRHHMYGY == kFIwaQfJmw){fhuyPLIVoo = true;}
      while(pHlgcBqCSg == GwGbSxXIiT){GNWhqoaPpK = true;}
      while(XNipHXeSuc == XNipHXeSuc){GFxlDFnZaO = true;}
      while(kFIwaQfJmw == kFIwaQfJmw){dFHnwFatyl = true;}
      if(XhOknuanEN == true){XhOknuanEN = false;}
      if(KFPFrgundY == true){KFPFrgundY = false;}
      if(qsYwijzpFM == true){qsYwijzpFM = false;}
      if(VgOVIozyBL == true){VgOVIozyBL = false;}
      if(wqNhSfoCDs == true){wqNhSfoCDs = false;}
      if(VrfNFeJRCD == true){VrfNFeJRCD = false;}
      if(wkhrrcpsxC == true){wkhrrcpsxC = false;}
      if(hxlRbAeqdD == true){hxlRbAeqdD = false;}
      if(txlLqcBAQd == true){txlLqcBAQd = false;}
      if(fhuyPLIVoo == true){fhuyPLIVoo = false;}
      if(owFALXFNkF == true){owFALXFNkF = false;}
      if(ASnzIyyWAO == true){ASnzIyyWAO = false;}
      if(bpbSWABmCQ == true){bpbSWABmCQ = false;}
      if(qIBnNyrkzS == true){qIBnNyrkzS = false;}
      if(XmOLcMtwoQ == true){XmOLcMtwoQ = false;}
      if(MlUaMyTldL == true){MlUaMyTldL = false;}
      if(VRLUNqRzkK == true){VRLUNqRzkK = false;}
      if(GNWhqoaPpK == true){GNWhqoaPpK = false;}
      if(GFxlDFnZaO == true){GFxlDFnZaO = false;}
      if(dFHnwFatyl == true){dFHnwFatyl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ILCNDXFDAT
{ 
  void HwJkXRUdgG()
  { 
      bool wiLkQqrrXL = false;
      bool EKzjJBZtEN = false;
      bool kYkzChSNDI = false;
      bool LIBkQHmAHU = false;
      bool HOxafQydEb = false;
      bool lLdjJWxMhh = false;
      bool YdnOAuJOSC = false;
      bool NZmjFVbJSl = false;
      bool ioJaWzeQas = false;
      bool JaRYwcZhaj = false;
      bool GjKBOMXtdm = false;
      bool unswyjUNrA = false;
      bool QrmZslHOnc = false;
      bool wsihezdHMJ = false;
      bool aklmyVhVZL = false;
      bool ILoZTOwkIb = false;
      bool EJFBpBFKQz = false;
      bool FNBhZfGzaX = false;
      bool ElnbUjDIOQ = false;
      bool CszjFRejww = false;
      string SMfqAfOILB;
      string cwQUERJeQQ;
      string zgHFEexMEc;
      string aaCLtCWAzo;
      string QRSKUhZXBr;
      string DqOAQkEZmU;
      string iBEiaBsEaB;
      string tIfazhOxjV;
      string FZKMYiLBtI;
      string xxNeGOMijS;
      string nUwAxuLmBi;
      string WHoROJqrKq;
      string prKRDxuAUj;
      string UeNQgkcKOd;
      string WYALlpHuPx;
      string XUYrcwJewA;
      string AKSQNqtYjd;
      string ffcgURrzfM;
      string pzkXMzGUmk;
      string ayNOcLFiyt;
      if(SMfqAfOILB == nUwAxuLmBi){wiLkQqrrXL = true;}
      else if(nUwAxuLmBi == SMfqAfOILB){GjKBOMXtdm = true;}
      if(cwQUERJeQQ == WHoROJqrKq){EKzjJBZtEN = true;}
      else if(WHoROJqrKq == cwQUERJeQQ){unswyjUNrA = true;}
      if(zgHFEexMEc == prKRDxuAUj){kYkzChSNDI = true;}
      else if(prKRDxuAUj == zgHFEexMEc){QrmZslHOnc = true;}
      if(aaCLtCWAzo == UeNQgkcKOd){LIBkQHmAHU = true;}
      else if(UeNQgkcKOd == aaCLtCWAzo){wsihezdHMJ = true;}
      if(QRSKUhZXBr == WYALlpHuPx){HOxafQydEb = true;}
      else if(WYALlpHuPx == QRSKUhZXBr){aklmyVhVZL = true;}
      if(DqOAQkEZmU == XUYrcwJewA){lLdjJWxMhh = true;}
      else if(XUYrcwJewA == DqOAQkEZmU){ILoZTOwkIb = true;}
      if(iBEiaBsEaB == AKSQNqtYjd){YdnOAuJOSC = true;}
      else if(AKSQNqtYjd == iBEiaBsEaB){EJFBpBFKQz = true;}
      if(tIfazhOxjV == ffcgURrzfM){NZmjFVbJSl = true;}
      if(FZKMYiLBtI == pzkXMzGUmk){ioJaWzeQas = true;}
      if(xxNeGOMijS == ayNOcLFiyt){JaRYwcZhaj = true;}
      while(ffcgURrzfM == tIfazhOxjV){FNBhZfGzaX = true;}
      while(pzkXMzGUmk == pzkXMzGUmk){ElnbUjDIOQ = true;}
      while(ayNOcLFiyt == ayNOcLFiyt){CszjFRejww = true;}
      if(wiLkQqrrXL == true){wiLkQqrrXL = false;}
      if(EKzjJBZtEN == true){EKzjJBZtEN = false;}
      if(kYkzChSNDI == true){kYkzChSNDI = false;}
      if(LIBkQHmAHU == true){LIBkQHmAHU = false;}
      if(HOxafQydEb == true){HOxafQydEb = false;}
      if(lLdjJWxMhh == true){lLdjJWxMhh = false;}
      if(YdnOAuJOSC == true){YdnOAuJOSC = false;}
      if(NZmjFVbJSl == true){NZmjFVbJSl = false;}
      if(ioJaWzeQas == true){ioJaWzeQas = false;}
      if(JaRYwcZhaj == true){JaRYwcZhaj = false;}
      if(GjKBOMXtdm == true){GjKBOMXtdm = false;}
      if(unswyjUNrA == true){unswyjUNrA = false;}
      if(QrmZslHOnc == true){QrmZslHOnc = false;}
      if(wsihezdHMJ == true){wsihezdHMJ = false;}
      if(aklmyVhVZL == true){aklmyVhVZL = false;}
      if(ILoZTOwkIb == true){ILoZTOwkIb = false;}
      if(EJFBpBFKQz == true){EJFBpBFKQz = false;}
      if(FNBhZfGzaX == true){FNBhZfGzaX = false;}
      if(ElnbUjDIOQ == true){ElnbUjDIOQ = false;}
      if(CszjFRejww == true){CszjFRejww = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XJJLWCQOLT
{ 
  void SahGGRYkon()
  { 
      bool NSWAsSiJRk = false;
      bool YwNFceQidD = false;
      bool dLARdrzsaU = false;
      bool ZWHEhVsAZf = false;
      bool VTXIpkJZuZ = false;
      bool HwomtCSFWB = false;
      bool TphxLCoJXH = false;
      bool kPIyhKnqar = false;
      bool hYxANcgTJe = false;
      bool CndYMfkaxn = false;
      bool uACnoqmqFj = false;
      bool NaddSurgjh = false;
      bool UVzrEwljkB = false;
      bool ZNtmxhWJLV = false;
      bool poNZQbKzGQ = false;
      bool mDpOSZAJis = false;
      bool ECFDKAgpgj = false;
      bool YiVNrfHYbc = false;
      bool lldUOVWfUW = false;
      bool hMZSQmiJPQ = false;
      string XquFrarlUS;
      string OdMjpjDWAb;
      string pIuzHhfjVW;
      string NLMwUNpPKi;
      string SZTzhVKQoM;
      string ErxlfOwwyK;
      string tHQyFCQPPc;
      string tmMQJPnuQk;
      string WPtIRVOaQF;
      string QsRznLJVte;
      string FtAMSRefcP;
      string ZBfMmeMHfi;
      string nozJLBVMcy;
      string GSAkfbOhpA;
      string piyAfPMELJ;
      string yBoKqPuqBQ;
      string uRDdJHBtgL;
      string PeRfsFqycu;
      string nQBTzFcotP;
      string gXfYEXfTqY;
      if(XquFrarlUS == FtAMSRefcP){NSWAsSiJRk = true;}
      else if(FtAMSRefcP == XquFrarlUS){uACnoqmqFj = true;}
      if(OdMjpjDWAb == ZBfMmeMHfi){YwNFceQidD = true;}
      else if(ZBfMmeMHfi == OdMjpjDWAb){NaddSurgjh = true;}
      if(pIuzHhfjVW == nozJLBVMcy){dLARdrzsaU = true;}
      else if(nozJLBVMcy == pIuzHhfjVW){UVzrEwljkB = true;}
      if(NLMwUNpPKi == GSAkfbOhpA){ZWHEhVsAZf = true;}
      else if(GSAkfbOhpA == NLMwUNpPKi){ZNtmxhWJLV = true;}
      if(SZTzhVKQoM == piyAfPMELJ){VTXIpkJZuZ = true;}
      else if(piyAfPMELJ == SZTzhVKQoM){poNZQbKzGQ = true;}
      if(ErxlfOwwyK == yBoKqPuqBQ){HwomtCSFWB = true;}
      else if(yBoKqPuqBQ == ErxlfOwwyK){mDpOSZAJis = true;}
      if(tHQyFCQPPc == uRDdJHBtgL){TphxLCoJXH = true;}
      else if(uRDdJHBtgL == tHQyFCQPPc){ECFDKAgpgj = true;}
      if(tmMQJPnuQk == PeRfsFqycu){kPIyhKnqar = true;}
      if(WPtIRVOaQF == nQBTzFcotP){hYxANcgTJe = true;}
      if(QsRznLJVte == gXfYEXfTqY){CndYMfkaxn = true;}
      while(PeRfsFqycu == tmMQJPnuQk){YiVNrfHYbc = true;}
      while(nQBTzFcotP == nQBTzFcotP){lldUOVWfUW = true;}
      while(gXfYEXfTqY == gXfYEXfTqY){hMZSQmiJPQ = true;}
      if(NSWAsSiJRk == true){NSWAsSiJRk = false;}
      if(YwNFceQidD == true){YwNFceQidD = false;}
      if(dLARdrzsaU == true){dLARdrzsaU = false;}
      if(ZWHEhVsAZf == true){ZWHEhVsAZf = false;}
      if(VTXIpkJZuZ == true){VTXIpkJZuZ = false;}
      if(HwomtCSFWB == true){HwomtCSFWB = false;}
      if(TphxLCoJXH == true){TphxLCoJXH = false;}
      if(kPIyhKnqar == true){kPIyhKnqar = false;}
      if(hYxANcgTJe == true){hYxANcgTJe = false;}
      if(CndYMfkaxn == true){CndYMfkaxn = false;}
      if(uACnoqmqFj == true){uACnoqmqFj = false;}
      if(NaddSurgjh == true){NaddSurgjh = false;}
      if(UVzrEwljkB == true){UVzrEwljkB = false;}
      if(ZNtmxhWJLV == true){ZNtmxhWJLV = false;}
      if(poNZQbKzGQ == true){poNZQbKzGQ = false;}
      if(mDpOSZAJis == true){mDpOSZAJis = false;}
      if(ECFDKAgpgj == true){ECFDKAgpgj = false;}
      if(YiVNrfHYbc == true){YiVNrfHYbc = false;}
      if(lldUOVWfUW == true){lldUOVWfUW = false;}
      if(hMZSQmiJPQ == true){hMZSQmiJPQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FZZYNXVKPV
{ 
  void WYnzAdLEJl()
  { 
      bool TFCfeAFwnm = false;
      bool MuIfEnpLSm = false;
      bool gSVufbeFFp = false;
      bool AxzpSPGuuc = false;
      bool fmRnVhjXWf = false;
      bool dqRHtAiHAC = false;
      bool VApylOuRMn = false;
      bool gtQpHsBhYx = false;
      bool rGhZLJeqwR = false;
      bool gzurHexSBH = false;
      bool mSLhyjabAA = false;
      bool zAhDKORQmc = false;
      bool iDUtHgyXhb = false;
      bool whfRJYuAab = false;
      bool iDqwSfQrgs = false;
      bool NffYXixQaQ = false;
      bool kCsXDQUQsk = false;
      bool SRpKsfMXba = false;
      bool QGpoOQCGta = false;
      bool beYJpfJSsC = false;
      string HmHCXLpfON;
      string aOsbymMQzR;
      string DULkGQRQuU;
      string ueGLBxrici;
      string OHEMfSnLxt;
      string QYcOtlbWuH;
      string tYktSuIhZA;
      string tdnPDwPyEn;
      string bFSBDWCrRO;
      string VVnVooWKtk;
      string KGlxzmjMKx;
      string VcRHeoFipw;
      string sPPKeYpSaN;
      string YEETcUTVCQ;
      string lohTrrDfpA;
      string jmUyqtqaRZ;
      string xRlwYRYydJ;
      string UigYJDhuRl;
      string UJbZdkjFbi;
      string dsEbTTCkua;
      if(HmHCXLpfON == KGlxzmjMKx){TFCfeAFwnm = true;}
      else if(KGlxzmjMKx == HmHCXLpfON){mSLhyjabAA = true;}
      if(aOsbymMQzR == VcRHeoFipw){MuIfEnpLSm = true;}
      else if(VcRHeoFipw == aOsbymMQzR){zAhDKORQmc = true;}
      if(DULkGQRQuU == sPPKeYpSaN){gSVufbeFFp = true;}
      else if(sPPKeYpSaN == DULkGQRQuU){iDUtHgyXhb = true;}
      if(ueGLBxrici == YEETcUTVCQ){AxzpSPGuuc = true;}
      else if(YEETcUTVCQ == ueGLBxrici){whfRJYuAab = true;}
      if(OHEMfSnLxt == lohTrrDfpA){fmRnVhjXWf = true;}
      else if(lohTrrDfpA == OHEMfSnLxt){iDqwSfQrgs = true;}
      if(QYcOtlbWuH == jmUyqtqaRZ){dqRHtAiHAC = true;}
      else if(jmUyqtqaRZ == QYcOtlbWuH){NffYXixQaQ = true;}
      if(tYktSuIhZA == xRlwYRYydJ){VApylOuRMn = true;}
      else if(xRlwYRYydJ == tYktSuIhZA){kCsXDQUQsk = true;}
      if(tdnPDwPyEn == UigYJDhuRl){gtQpHsBhYx = true;}
      if(bFSBDWCrRO == UJbZdkjFbi){rGhZLJeqwR = true;}
      if(VVnVooWKtk == dsEbTTCkua){gzurHexSBH = true;}
      while(UigYJDhuRl == tdnPDwPyEn){SRpKsfMXba = true;}
      while(UJbZdkjFbi == UJbZdkjFbi){QGpoOQCGta = true;}
      while(dsEbTTCkua == dsEbTTCkua){beYJpfJSsC = true;}
      if(TFCfeAFwnm == true){TFCfeAFwnm = false;}
      if(MuIfEnpLSm == true){MuIfEnpLSm = false;}
      if(gSVufbeFFp == true){gSVufbeFFp = false;}
      if(AxzpSPGuuc == true){AxzpSPGuuc = false;}
      if(fmRnVhjXWf == true){fmRnVhjXWf = false;}
      if(dqRHtAiHAC == true){dqRHtAiHAC = false;}
      if(VApylOuRMn == true){VApylOuRMn = false;}
      if(gtQpHsBhYx == true){gtQpHsBhYx = false;}
      if(rGhZLJeqwR == true){rGhZLJeqwR = false;}
      if(gzurHexSBH == true){gzurHexSBH = false;}
      if(mSLhyjabAA == true){mSLhyjabAA = false;}
      if(zAhDKORQmc == true){zAhDKORQmc = false;}
      if(iDUtHgyXhb == true){iDUtHgyXhb = false;}
      if(whfRJYuAab == true){whfRJYuAab = false;}
      if(iDqwSfQrgs == true){iDqwSfQrgs = false;}
      if(NffYXixQaQ == true){NffYXixQaQ = false;}
      if(kCsXDQUQsk == true){kCsXDQUQsk = false;}
      if(SRpKsfMXba == true){SRpKsfMXba = false;}
      if(QGpoOQCGta == true){QGpoOQCGta = false;}
      if(beYJpfJSsC == true){beYJpfJSsC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHGLYYPZUI
{ 
  void AQsPpDkkDY()
  { 
      bool ZrbyNfsncS = false;
      bool DuTjVmRWHe = false;
      bool InYMVHPxxW = false;
      bool ZAelrLczWr = false;
      bool HzJeBIVIrl = false;
      bool HIKfGlSPcG = false;
      bool QwqFsCQhqK = false;
      bool KSzPXIdsKN = false;
      bool kGEKPQozeG = false;
      bool rNWPbLIEly = false;
      bool rmRhboJuIx = false;
      bool HYEOUJrfpb = false;
      bool NRCkSwwinL = false;
      bool AYHLUxoVia = false;
      bool HsphySIHtR = false;
      bool SbOJkakfOe = false;
      bool rZHwxiRrtX = false;
      bool UVxPUTaUmz = false;
      bool nonVsXKxat = false;
      bool MIHEhgltjP = false;
      string xVhRCudono;
      string xxhdQdlSfd;
      string zzGuIguDGo;
      string YLpYHGyxIR;
      string VnyeEtZDiY;
      string fwSAxyPlJV;
      string zahyQlGIWK;
      string fnJOHLAbpO;
      string GqUhJcrpbJ;
      string pLnmSuFANS;
      string mRgXsrlErk;
      string xnwtOHFAnn;
      string sQfMUTzVwM;
      string FANXboKwnR;
      string pnxpLBPtYK;
      string oFLZYWkUDZ;
      string rPHefxaXRZ;
      string xILWxFSpAS;
      string DFxkXAnmyF;
      string DosOYZfSKO;
      if(xVhRCudono == mRgXsrlErk){ZrbyNfsncS = true;}
      else if(mRgXsrlErk == xVhRCudono){rmRhboJuIx = true;}
      if(xxhdQdlSfd == xnwtOHFAnn){DuTjVmRWHe = true;}
      else if(xnwtOHFAnn == xxhdQdlSfd){HYEOUJrfpb = true;}
      if(zzGuIguDGo == sQfMUTzVwM){InYMVHPxxW = true;}
      else if(sQfMUTzVwM == zzGuIguDGo){NRCkSwwinL = true;}
      if(YLpYHGyxIR == FANXboKwnR){ZAelrLczWr = true;}
      else if(FANXboKwnR == YLpYHGyxIR){AYHLUxoVia = true;}
      if(VnyeEtZDiY == pnxpLBPtYK){HzJeBIVIrl = true;}
      else if(pnxpLBPtYK == VnyeEtZDiY){HsphySIHtR = true;}
      if(fwSAxyPlJV == oFLZYWkUDZ){HIKfGlSPcG = true;}
      else if(oFLZYWkUDZ == fwSAxyPlJV){SbOJkakfOe = true;}
      if(zahyQlGIWK == rPHefxaXRZ){QwqFsCQhqK = true;}
      else if(rPHefxaXRZ == zahyQlGIWK){rZHwxiRrtX = true;}
      if(fnJOHLAbpO == xILWxFSpAS){KSzPXIdsKN = true;}
      if(GqUhJcrpbJ == DFxkXAnmyF){kGEKPQozeG = true;}
      if(pLnmSuFANS == DosOYZfSKO){rNWPbLIEly = true;}
      while(xILWxFSpAS == fnJOHLAbpO){UVxPUTaUmz = true;}
      while(DFxkXAnmyF == DFxkXAnmyF){nonVsXKxat = true;}
      while(DosOYZfSKO == DosOYZfSKO){MIHEhgltjP = true;}
      if(ZrbyNfsncS == true){ZrbyNfsncS = false;}
      if(DuTjVmRWHe == true){DuTjVmRWHe = false;}
      if(InYMVHPxxW == true){InYMVHPxxW = false;}
      if(ZAelrLczWr == true){ZAelrLczWr = false;}
      if(HzJeBIVIrl == true){HzJeBIVIrl = false;}
      if(HIKfGlSPcG == true){HIKfGlSPcG = false;}
      if(QwqFsCQhqK == true){QwqFsCQhqK = false;}
      if(KSzPXIdsKN == true){KSzPXIdsKN = false;}
      if(kGEKPQozeG == true){kGEKPQozeG = false;}
      if(rNWPbLIEly == true){rNWPbLIEly = false;}
      if(rmRhboJuIx == true){rmRhboJuIx = false;}
      if(HYEOUJrfpb == true){HYEOUJrfpb = false;}
      if(NRCkSwwinL == true){NRCkSwwinL = false;}
      if(AYHLUxoVia == true){AYHLUxoVia = false;}
      if(HsphySIHtR == true){HsphySIHtR = false;}
      if(SbOJkakfOe == true){SbOJkakfOe = false;}
      if(rZHwxiRrtX == true){rZHwxiRrtX = false;}
      if(UVxPUTaUmz == true){UVxPUTaUmz = false;}
      if(nonVsXKxat == true){nonVsXKxat = false;}
      if(MIHEhgltjP == true){MIHEhgltjP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBUBSYLHVD
{ 
  void kpwuwLibcf()
  { 
      bool ZGZCkjLpBd = false;
      bool tcoxCNfsEx = false;
      bool OUroiCXHpS = false;
      bool BEwsASwxud = false;
      bool uOwtlJMfyt = false;
      bool SfYEpENkSh = false;
      bool MDAhbpguxi = false;
      bool QixaCzYxCZ = false;
      bool pqJuAVeqCu = false;
      bool FLdNQqONRu = false;
      bool bQiOdjhyCq = false;
      bool fPhsrUtEhG = false;
      bool KpsBdFEjJK = false;
      bool jKfGxYItRQ = false;
      bool mgnLPodkUw = false;
      bool wJfLklXhjX = false;
      bool eyoqGUjawS = false;
      bool LzmQTdBhko = false;
      bool bTOMOaeTVK = false;
      bool BaJslnrxEu = false;
      string nzgAzVcodG;
      string YIsutzLXjV;
      string iugVITahxq;
      string XzRBgwfSpd;
      string izTyIuXZos;
      string unCEPrSKrf;
      string uuqlhYpqNx;
      string SshFmjbhNN;
      string uBsEujxNlo;
      string dUaJimHgQi;
      string EgLqZCFwRf;
      string PkxdksCmqx;
      string bcEXTxSYWz;
      string buReIOoBdr;
      string eAuGZsXwYo;
      string kUoTGbbmXc;
      string jfZSEUSRVV;
      string EAJyRbgyyZ;
      string ZWAgNGFyYg;
      string mBcBIyZcCF;
      if(nzgAzVcodG == EgLqZCFwRf){ZGZCkjLpBd = true;}
      else if(EgLqZCFwRf == nzgAzVcodG){bQiOdjhyCq = true;}
      if(YIsutzLXjV == PkxdksCmqx){tcoxCNfsEx = true;}
      else if(PkxdksCmqx == YIsutzLXjV){fPhsrUtEhG = true;}
      if(iugVITahxq == bcEXTxSYWz){OUroiCXHpS = true;}
      else if(bcEXTxSYWz == iugVITahxq){KpsBdFEjJK = true;}
      if(XzRBgwfSpd == buReIOoBdr){BEwsASwxud = true;}
      else if(buReIOoBdr == XzRBgwfSpd){jKfGxYItRQ = true;}
      if(izTyIuXZos == eAuGZsXwYo){uOwtlJMfyt = true;}
      else if(eAuGZsXwYo == izTyIuXZos){mgnLPodkUw = true;}
      if(unCEPrSKrf == kUoTGbbmXc){SfYEpENkSh = true;}
      else if(kUoTGbbmXc == unCEPrSKrf){wJfLklXhjX = true;}
      if(uuqlhYpqNx == jfZSEUSRVV){MDAhbpguxi = true;}
      else if(jfZSEUSRVV == uuqlhYpqNx){eyoqGUjawS = true;}
      if(SshFmjbhNN == EAJyRbgyyZ){QixaCzYxCZ = true;}
      if(uBsEujxNlo == ZWAgNGFyYg){pqJuAVeqCu = true;}
      if(dUaJimHgQi == mBcBIyZcCF){FLdNQqONRu = true;}
      while(EAJyRbgyyZ == SshFmjbhNN){LzmQTdBhko = true;}
      while(ZWAgNGFyYg == ZWAgNGFyYg){bTOMOaeTVK = true;}
      while(mBcBIyZcCF == mBcBIyZcCF){BaJslnrxEu = true;}
      if(ZGZCkjLpBd == true){ZGZCkjLpBd = false;}
      if(tcoxCNfsEx == true){tcoxCNfsEx = false;}
      if(OUroiCXHpS == true){OUroiCXHpS = false;}
      if(BEwsASwxud == true){BEwsASwxud = false;}
      if(uOwtlJMfyt == true){uOwtlJMfyt = false;}
      if(SfYEpENkSh == true){SfYEpENkSh = false;}
      if(MDAhbpguxi == true){MDAhbpguxi = false;}
      if(QixaCzYxCZ == true){QixaCzYxCZ = false;}
      if(pqJuAVeqCu == true){pqJuAVeqCu = false;}
      if(FLdNQqONRu == true){FLdNQqONRu = false;}
      if(bQiOdjhyCq == true){bQiOdjhyCq = false;}
      if(fPhsrUtEhG == true){fPhsrUtEhG = false;}
      if(KpsBdFEjJK == true){KpsBdFEjJK = false;}
      if(jKfGxYItRQ == true){jKfGxYItRQ = false;}
      if(mgnLPodkUw == true){mgnLPodkUw = false;}
      if(wJfLklXhjX == true){wJfLklXhjX = false;}
      if(eyoqGUjawS == true){eyoqGUjawS = false;}
      if(LzmQTdBhko == true){LzmQTdBhko = false;}
      if(bTOMOaeTVK == true){bTOMOaeTVK = false;}
      if(BaJslnrxEu == true){BaJslnrxEu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MZAAYJCUDG
{ 
  void sjeXogwDaz()
  { 
      bool KcVQgjGJFa = false;
      bool TPInlPtfkZ = false;
      bool TgOEbyeoRb = false;
      bool tdcUZzcqhg = false;
      bool bRFCHKcedr = false;
      bool DHqwxcORni = false;
      bool FQrcgpmnNl = false;
      bool mCyDyBbMwQ = false;
      bool UzLYYlmfXw = false;
      bool kKCzbKZbUR = false;
      bool XoQqFBJmyw = false;
      bool ACUXOGFTEu = false;
      bool CGPRBczzbm = false;
      bool aAqesehTTW = false;
      bool cAhawioejV = false;
      bool EFWZOQYzpc = false;
      bool BKKKUAKpdi = false;
      bool XlAgSBXoUR = false;
      bool mUOGiUcRPb = false;
      bool FicpVRpXGw = false;
      string QjWzXeerYH;
      string pgprlzUmrp;
      string WMGaArmlLn;
      string CJLdYOyjta;
      string QdSKKiGMiQ;
      string BWtbuDdwzf;
      string qrfkFgVMTX;
      string BkrQYrtuPQ;
      string kZCumeOihV;
      string kBjOiXxhFc;
      string NtsLOPedDD;
      string IhfhtRokxZ;
      string SleymzAcgA;
      string tMpmCqgqfW;
      string AjeeMCVBUR;
      string hMjeJaPtXP;
      string OCwDIurrfD;
      string jyFZZhGzlj;
      string czIPRhbKdb;
      string alSQIxnbWQ;
      if(QjWzXeerYH == NtsLOPedDD){KcVQgjGJFa = true;}
      else if(NtsLOPedDD == QjWzXeerYH){XoQqFBJmyw = true;}
      if(pgprlzUmrp == IhfhtRokxZ){TPInlPtfkZ = true;}
      else if(IhfhtRokxZ == pgprlzUmrp){ACUXOGFTEu = true;}
      if(WMGaArmlLn == SleymzAcgA){TgOEbyeoRb = true;}
      else if(SleymzAcgA == WMGaArmlLn){CGPRBczzbm = true;}
      if(CJLdYOyjta == tMpmCqgqfW){tdcUZzcqhg = true;}
      else if(tMpmCqgqfW == CJLdYOyjta){aAqesehTTW = true;}
      if(QdSKKiGMiQ == AjeeMCVBUR){bRFCHKcedr = true;}
      else if(AjeeMCVBUR == QdSKKiGMiQ){cAhawioejV = true;}
      if(BWtbuDdwzf == hMjeJaPtXP){DHqwxcORni = true;}
      else if(hMjeJaPtXP == BWtbuDdwzf){EFWZOQYzpc = true;}
      if(qrfkFgVMTX == OCwDIurrfD){FQrcgpmnNl = true;}
      else if(OCwDIurrfD == qrfkFgVMTX){BKKKUAKpdi = true;}
      if(BkrQYrtuPQ == jyFZZhGzlj){mCyDyBbMwQ = true;}
      if(kZCumeOihV == czIPRhbKdb){UzLYYlmfXw = true;}
      if(kBjOiXxhFc == alSQIxnbWQ){kKCzbKZbUR = true;}
      while(jyFZZhGzlj == BkrQYrtuPQ){XlAgSBXoUR = true;}
      while(czIPRhbKdb == czIPRhbKdb){mUOGiUcRPb = true;}
      while(alSQIxnbWQ == alSQIxnbWQ){FicpVRpXGw = true;}
      if(KcVQgjGJFa == true){KcVQgjGJFa = false;}
      if(TPInlPtfkZ == true){TPInlPtfkZ = false;}
      if(TgOEbyeoRb == true){TgOEbyeoRb = false;}
      if(tdcUZzcqhg == true){tdcUZzcqhg = false;}
      if(bRFCHKcedr == true){bRFCHKcedr = false;}
      if(DHqwxcORni == true){DHqwxcORni = false;}
      if(FQrcgpmnNl == true){FQrcgpmnNl = false;}
      if(mCyDyBbMwQ == true){mCyDyBbMwQ = false;}
      if(UzLYYlmfXw == true){UzLYYlmfXw = false;}
      if(kKCzbKZbUR == true){kKCzbKZbUR = false;}
      if(XoQqFBJmyw == true){XoQqFBJmyw = false;}
      if(ACUXOGFTEu == true){ACUXOGFTEu = false;}
      if(CGPRBczzbm == true){CGPRBczzbm = false;}
      if(aAqesehTTW == true){aAqesehTTW = false;}
      if(cAhawioejV == true){cAhawioejV = false;}
      if(EFWZOQYzpc == true){EFWZOQYzpc = false;}
      if(BKKKUAKpdi == true){BKKKUAKpdi = false;}
      if(XlAgSBXoUR == true){XlAgSBXoUR = false;}
      if(mUOGiUcRPb == true){mUOGiUcRPb = false;}
      if(FicpVRpXGw == true){FicpVRpXGw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CRYMBSKRWK
{ 
  void hhHSUeIMVe()
  { 
      bool LLbljQtDAQ = false;
      bool ZOSLEZeKMU = false;
      bool KEDbfKPyAW = false;
      bool PFEFYfUNWm = false;
      bool JzHEImRdaH = false;
      bool SLqlfHHAFY = false;
      bool BwCcATKNmX = false;
      bool EQnZKKxzSr = false;
      bool slXsEENRZR = false;
      bool XUHxlNwdDn = false;
      bool cEpCCBXRaU = false;
      bool JHhMfPYJYw = false;
      bool GrmUAjIpnx = false;
      bool OSudPnuUpC = false;
      bool fuqFHPmtRW = false;
      bool omFHgjQUCS = false;
      bool shddGqLDxq = false;
      bool TDSWPLBhNj = false;
      bool xNYQIaNnxe = false;
      bool XZSXJyRMyQ = false;
      string SeCAjrNdWJ;
      string flGnclVlrp;
      string fwqDqfkabT;
      string hKsieCeXjf;
      string BcduBJmXge;
      string GDQfDVmyJD;
      string HmBCbVsWIZ;
      string HyCLnCRwCh;
      string rNtxNdtMfI;
      string PfNfYOabSe;
      string PQOHWHBEqA;
      string EpwbKtrDox;
      string bfpAJajVlZ;
      string bpcXRbymaF;
      string coVfEYjlUe;
      string VXmUDiZOxu;
      string XeRQYNMXJi;
      string uFciUmJKuk;
      string qxAHDDDIUh;
      string CjpehxWEGp;
      if(SeCAjrNdWJ == PQOHWHBEqA){LLbljQtDAQ = true;}
      else if(PQOHWHBEqA == SeCAjrNdWJ){cEpCCBXRaU = true;}
      if(flGnclVlrp == EpwbKtrDox){ZOSLEZeKMU = true;}
      else if(EpwbKtrDox == flGnclVlrp){JHhMfPYJYw = true;}
      if(fwqDqfkabT == bfpAJajVlZ){KEDbfKPyAW = true;}
      else if(bfpAJajVlZ == fwqDqfkabT){GrmUAjIpnx = true;}
      if(hKsieCeXjf == bpcXRbymaF){PFEFYfUNWm = true;}
      else if(bpcXRbymaF == hKsieCeXjf){OSudPnuUpC = true;}
      if(BcduBJmXge == coVfEYjlUe){JzHEImRdaH = true;}
      else if(coVfEYjlUe == BcduBJmXge){fuqFHPmtRW = true;}
      if(GDQfDVmyJD == VXmUDiZOxu){SLqlfHHAFY = true;}
      else if(VXmUDiZOxu == GDQfDVmyJD){omFHgjQUCS = true;}
      if(HmBCbVsWIZ == XeRQYNMXJi){BwCcATKNmX = true;}
      else if(XeRQYNMXJi == HmBCbVsWIZ){shddGqLDxq = true;}
      if(HyCLnCRwCh == uFciUmJKuk){EQnZKKxzSr = true;}
      if(rNtxNdtMfI == qxAHDDDIUh){slXsEENRZR = true;}
      if(PfNfYOabSe == CjpehxWEGp){XUHxlNwdDn = true;}
      while(uFciUmJKuk == HyCLnCRwCh){TDSWPLBhNj = true;}
      while(qxAHDDDIUh == qxAHDDDIUh){xNYQIaNnxe = true;}
      while(CjpehxWEGp == CjpehxWEGp){XZSXJyRMyQ = true;}
      if(LLbljQtDAQ == true){LLbljQtDAQ = false;}
      if(ZOSLEZeKMU == true){ZOSLEZeKMU = false;}
      if(KEDbfKPyAW == true){KEDbfKPyAW = false;}
      if(PFEFYfUNWm == true){PFEFYfUNWm = false;}
      if(JzHEImRdaH == true){JzHEImRdaH = false;}
      if(SLqlfHHAFY == true){SLqlfHHAFY = false;}
      if(BwCcATKNmX == true){BwCcATKNmX = false;}
      if(EQnZKKxzSr == true){EQnZKKxzSr = false;}
      if(slXsEENRZR == true){slXsEENRZR = false;}
      if(XUHxlNwdDn == true){XUHxlNwdDn = false;}
      if(cEpCCBXRaU == true){cEpCCBXRaU = false;}
      if(JHhMfPYJYw == true){JHhMfPYJYw = false;}
      if(GrmUAjIpnx == true){GrmUAjIpnx = false;}
      if(OSudPnuUpC == true){OSudPnuUpC = false;}
      if(fuqFHPmtRW == true){fuqFHPmtRW = false;}
      if(omFHgjQUCS == true){omFHgjQUCS = false;}
      if(shddGqLDxq == true){shddGqLDxq = false;}
      if(TDSWPLBhNj == true){TDSWPLBhNj = false;}
      if(xNYQIaNnxe == true){xNYQIaNnxe = false;}
      if(XZSXJyRMyQ == true){XZSXJyRMyQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VILVOBIZKQ
{ 
  void IVFLnWnRxR()
  { 
      bool VAlnCYEIXF = false;
      bool tmaTmVOAto = false;
      bool KpWMYhQYwY = false;
      bool OWzJCUeMYe = false;
      bool yDgZZajKXh = false;
      bool CZByNedYPU = false;
      bool HeMyqXmQRS = false;
      bool pBaPqHJxlx = false;
      bool yFANWnUBwW = false;
      bool qFxEWSqhiC = false;
      bool nTsFqAykHG = false;
      bool VflRVCeybC = false;
      bool ClTtbkEVsY = false;
      bool PbNjJeLuWV = false;
      bool pjtpBKTeiT = false;
      bool mrFgzBzycG = false;
      bool ubqhpsSBIq = false;
      bool qjbGLSrdsR = false;
      bool RYmYkXWgjI = false;
      bool eMRQZNrLAH = false;
      string grdbPhcyHr;
      string gXOTIXYuJX;
      string oUeqGFNEpE;
      string ykwiApSEOc;
      string MCBdfAXGzm;
      string qYhgULNmVJ;
      string TYICtuafSR;
      string FTggLlTBKG;
      string gHECMYDPNn;
      string cfiEIntyik;
      string YrmghWrAVi;
      string rMbPcMTFoV;
      string qLRdoYkcXX;
      string qURYgoTXUp;
      string fCseuQDTbw;
      string UoINtMZIrI;
      string lPcxqWtChm;
      string sukzonRmhX;
      string VQAbDCMEeU;
      string OKeLDQZumY;
      if(grdbPhcyHr == YrmghWrAVi){VAlnCYEIXF = true;}
      else if(YrmghWrAVi == grdbPhcyHr){nTsFqAykHG = true;}
      if(gXOTIXYuJX == rMbPcMTFoV){tmaTmVOAto = true;}
      else if(rMbPcMTFoV == gXOTIXYuJX){VflRVCeybC = true;}
      if(oUeqGFNEpE == qLRdoYkcXX){KpWMYhQYwY = true;}
      else if(qLRdoYkcXX == oUeqGFNEpE){ClTtbkEVsY = true;}
      if(ykwiApSEOc == qURYgoTXUp){OWzJCUeMYe = true;}
      else if(qURYgoTXUp == ykwiApSEOc){PbNjJeLuWV = true;}
      if(MCBdfAXGzm == fCseuQDTbw){yDgZZajKXh = true;}
      else if(fCseuQDTbw == MCBdfAXGzm){pjtpBKTeiT = true;}
      if(qYhgULNmVJ == UoINtMZIrI){CZByNedYPU = true;}
      else if(UoINtMZIrI == qYhgULNmVJ){mrFgzBzycG = true;}
      if(TYICtuafSR == lPcxqWtChm){HeMyqXmQRS = true;}
      else if(lPcxqWtChm == TYICtuafSR){ubqhpsSBIq = true;}
      if(FTggLlTBKG == sukzonRmhX){pBaPqHJxlx = true;}
      if(gHECMYDPNn == VQAbDCMEeU){yFANWnUBwW = true;}
      if(cfiEIntyik == OKeLDQZumY){qFxEWSqhiC = true;}
      while(sukzonRmhX == FTggLlTBKG){qjbGLSrdsR = true;}
      while(VQAbDCMEeU == VQAbDCMEeU){RYmYkXWgjI = true;}
      while(OKeLDQZumY == OKeLDQZumY){eMRQZNrLAH = true;}
      if(VAlnCYEIXF == true){VAlnCYEIXF = false;}
      if(tmaTmVOAto == true){tmaTmVOAto = false;}
      if(KpWMYhQYwY == true){KpWMYhQYwY = false;}
      if(OWzJCUeMYe == true){OWzJCUeMYe = false;}
      if(yDgZZajKXh == true){yDgZZajKXh = false;}
      if(CZByNedYPU == true){CZByNedYPU = false;}
      if(HeMyqXmQRS == true){HeMyqXmQRS = false;}
      if(pBaPqHJxlx == true){pBaPqHJxlx = false;}
      if(yFANWnUBwW == true){yFANWnUBwW = false;}
      if(qFxEWSqhiC == true){qFxEWSqhiC = false;}
      if(nTsFqAykHG == true){nTsFqAykHG = false;}
      if(VflRVCeybC == true){VflRVCeybC = false;}
      if(ClTtbkEVsY == true){ClTtbkEVsY = false;}
      if(PbNjJeLuWV == true){PbNjJeLuWV = false;}
      if(pjtpBKTeiT == true){pjtpBKTeiT = false;}
      if(mrFgzBzycG == true){mrFgzBzycG = false;}
      if(ubqhpsSBIq == true){ubqhpsSBIq = false;}
      if(qjbGLSrdsR == true){qjbGLSrdsR = false;}
      if(RYmYkXWgjI == true){RYmYkXWgjI = false;}
      if(eMRQZNrLAH == true){eMRQZNrLAH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHEIRDHDHH
{ 
  void CqpNHCCmUL()
  { 
      bool cICelxrcJB = false;
      bool PyfHNVILeG = false;
      bool oNaAParhPr = false;
      bool nwTwBLWCnQ = false;
      bool pVPiFTANbD = false;
      bool XRWaqPhCOK = false;
      bool EJMQNSeiFC = false;
      bool zFWOPTxquu = false;
      bool ZeGLTVYsFl = false;
      bool cTndLgIyVl = false;
      bool oRIZERuIKX = false;
      bool RpHSjZDAwq = false;
      bool tkdSYeRsDi = false;
      bool KyUIGIWfHC = false;
      bool aQihUmMUsk = false;
      bool cICerEmoAZ = false;
      bool zCEaMTUyMb = false;
      bool DWstQcBwyl = false;
      bool RxARGBwpQC = false;
      bool UgfhCXLHUB = false;
      string nIeHwLoksH;
      string iEBpCkrSpC;
      string UqYHMCUdsX;
      string ChsQUuJVJg;
      string tGxjBTJZny;
      string MtOcDxjXut;
      string qLrUEALkUG;
      string aVJJINsnFr;
      string rtouKHTPMX;
      string LlaOohOcfA;
      string IYFgWpkFTo;
      string EuRDBwVxJw;
      string guYwuoutTZ;
      string zQIFiSoHXU;
      string WOwWTPUWNs;
      string LQSiTNAIlh;
      string tpksommMUi;
      string HNYoZRyBce;
      string TYgZOiyZkU;
      string SfUpZgcCgf;
      if(nIeHwLoksH == IYFgWpkFTo){cICelxrcJB = true;}
      else if(IYFgWpkFTo == nIeHwLoksH){oRIZERuIKX = true;}
      if(iEBpCkrSpC == EuRDBwVxJw){PyfHNVILeG = true;}
      else if(EuRDBwVxJw == iEBpCkrSpC){RpHSjZDAwq = true;}
      if(UqYHMCUdsX == guYwuoutTZ){oNaAParhPr = true;}
      else if(guYwuoutTZ == UqYHMCUdsX){tkdSYeRsDi = true;}
      if(ChsQUuJVJg == zQIFiSoHXU){nwTwBLWCnQ = true;}
      else if(zQIFiSoHXU == ChsQUuJVJg){KyUIGIWfHC = true;}
      if(tGxjBTJZny == WOwWTPUWNs){pVPiFTANbD = true;}
      else if(WOwWTPUWNs == tGxjBTJZny){aQihUmMUsk = true;}
      if(MtOcDxjXut == LQSiTNAIlh){XRWaqPhCOK = true;}
      else if(LQSiTNAIlh == MtOcDxjXut){cICerEmoAZ = true;}
      if(qLrUEALkUG == tpksommMUi){EJMQNSeiFC = true;}
      else if(tpksommMUi == qLrUEALkUG){zCEaMTUyMb = true;}
      if(aVJJINsnFr == HNYoZRyBce){zFWOPTxquu = true;}
      if(rtouKHTPMX == TYgZOiyZkU){ZeGLTVYsFl = true;}
      if(LlaOohOcfA == SfUpZgcCgf){cTndLgIyVl = true;}
      while(HNYoZRyBce == aVJJINsnFr){DWstQcBwyl = true;}
      while(TYgZOiyZkU == TYgZOiyZkU){RxARGBwpQC = true;}
      while(SfUpZgcCgf == SfUpZgcCgf){UgfhCXLHUB = true;}
      if(cICelxrcJB == true){cICelxrcJB = false;}
      if(PyfHNVILeG == true){PyfHNVILeG = false;}
      if(oNaAParhPr == true){oNaAParhPr = false;}
      if(nwTwBLWCnQ == true){nwTwBLWCnQ = false;}
      if(pVPiFTANbD == true){pVPiFTANbD = false;}
      if(XRWaqPhCOK == true){XRWaqPhCOK = false;}
      if(EJMQNSeiFC == true){EJMQNSeiFC = false;}
      if(zFWOPTxquu == true){zFWOPTxquu = false;}
      if(ZeGLTVYsFl == true){ZeGLTVYsFl = false;}
      if(cTndLgIyVl == true){cTndLgIyVl = false;}
      if(oRIZERuIKX == true){oRIZERuIKX = false;}
      if(RpHSjZDAwq == true){RpHSjZDAwq = false;}
      if(tkdSYeRsDi == true){tkdSYeRsDi = false;}
      if(KyUIGIWfHC == true){KyUIGIWfHC = false;}
      if(aQihUmMUsk == true){aQihUmMUsk = false;}
      if(cICerEmoAZ == true){cICerEmoAZ = false;}
      if(zCEaMTUyMb == true){zCEaMTUyMb = false;}
      if(DWstQcBwyl == true){DWstQcBwyl = false;}
      if(RxARGBwpQC == true){RxARGBwpQC = false;}
      if(UgfhCXLHUB == true){UgfhCXLHUB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PPVGZFOQGZ
{ 
  void LYJGpVxzmo()
  { 
      bool shodOBpccX = false;
      bool jJTrGOHlTr = false;
      bool RoSnDgAMdR = false;
      bool FfxMFxrugg = false;
      bool NKVMhlgEqX = false;
      bool FqabUEOAag = false;
      bool AczKSEMHmJ = false;
      bool VLEmeHSGGQ = false;
      bool AuVFMNFUqA = false;
      bool hqUAfjLKtd = false;
      bool ZZRgBslmxN = false;
      bool kItKfFHsyE = false;
      bool yrPladqEGt = false;
      bool uIMbqZcnDS = false;
      bool bRWdPZxKTZ = false;
      bool cSMoegKfGX = false;
      bool CgfDScwRTG = false;
      bool bSoebgVlWA = false;
      bool gfjfQcwWwJ = false;
      bool PxgfPtkSLl = false;
      string pMBrwAiWHe;
      string ilNROJpOcA;
      string ccdSwpQlmy;
      string XEiPsINdIj;
      string gdCodkIjbz;
      string nqTCzNiiuG;
      string jwiJGdDyYF;
      string uMFsSzZooK;
      string hfKnJfkfQf;
      string ZehCAkushz;
      string hJLVDakZjz;
      string msskXDltzZ;
      string sWhreQeDrg;
      string DgGpcXUnji;
      string uKwQsgkxdx;
      string zAsIFKbSql;
      string whhCuFmDHz;
      string ixKQehZRzy;
      string fhZuhDnyjS;
      string wBxxlNctUm;
      if(pMBrwAiWHe == hJLVDakZjz){shodOBpccX = true;}
      else if(hJLVDakZjz == pMBrwAiWHe){ZZRgBslmxN = true;}
      if(ilNROJpOcA == msskXDltzZ){jJTrGOHlTr = true;}
      else if(msskXDltzZ == ilNROJpOcA){kItKfFHsyE = true;}
      if(ccdSwpQlmy == sWhreQeDrg){RoSnDgAMdR = true;}
      else if(sWhreQeDrg == ccdSwpQlmy){yrPladqEGt = true;}
      if(XEiPsINdIj == DgGpcXUnji){FfxMFxrugg = true;}
      else if(DgGpcXUnji == XEiPsINdIj){uIMbqZcnDS = true;}
      if(gdCodkIjbz == uKwQsgkxdx){NKVMhlgEqX = true;}
      else if(uKwQsgkxdx == gdCodkIjbz){bRWdPZxKTZ = true;}
      if(nqTCzNiiuG == zAsIFKbSql){FqabUEOAag = true;}
      else if(zAsIFKbSql == nqTCzNiiuG){cSMoegKfGX = true;}
      if(jwiJGdDyYF == whhCuFmDHz){AczKSEMHmJ = true;}
      else if(whhCuFmDHz == jwiJGdDyYF){CgfDScwRTG = true;}
      if(uMFsSzZooK == ixKQehZRzy){VLEmeHSGGQ = true;}
      if(hfKnJfkfQf == fhZuhDnyjS){AuVFMNFUqA = true;}
      if(ZehCAkushz == wBxxlNctUm){hqUAfjLKtd = true;}
      while(ixKQehZRzy == uMFsSzZooK){bSoebgVlWA = true;}
      while(fhZuhDnyjS == fhZuhDnyjS){gfjfQcwWwJ = true;}
      while(wBxxlNctUm == wBxxlNctUm){PxgfPtkSLl = true;}
      if(shodOBpccX == true){shodOBpccX = false;}
      if(jJTrGOHlTr == true){jJTrGOHlTr = false;}
      if(RoSnDgAMdR == true){RoSnDgAMdR = false;}
      if(FfxMFxrugg == true){FfxMFxrugg = false;}
      if(NKVMhlgEqX == true){NKVMhlgEqX = false;}
      if(FqabUEOAag == true){FqabUEOAag = false;}
      if(AczKSEMHmJ == true){AczKSEMHmJ = false;}
      if(VLEmeHSGGQ == true){VLEmeHSGGQ = false;}
      if(AuVFMNFUqA == true){AuVFMNFUqA = false;}
      if(hqUAfjLKtd == true){hqUAfjLKtd = false;}
      if(ZZRgBslmxN == true){ZZRgBslmxN = false;}
      if(kItKfFHsyE == true){kItKfFHsyE = false;}
      if(yrPladqEGt == true){yrPladqEGt = false;}
      if(uIMbqZcnDS == true){uIMbqZcnDS = false;}
      if(bRWdPZxKTZ == true){bRWdPZxKTZ = false;}
      if(cSMoegKfGX == true){cSMoegKfGX = false;}
      if(CgfDScwRTG == true){CgfDScwRTG = false;}
      if(bSoebgVlWA == true){bSoebgVlWA = false;}
      if(gfjfQcwWwJ == true){gfjfQcwWwJ = false;}
      if(PxgfPtkSLl == true){PxgfPtkSLl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YBVJJTVVYK
{ 
  void rBEbwtaOGP()
  { 
      bool gLtBKFxxji = false;
      bool AEFehKAuOb = false;
      bool OftVSpeVzZ = false;
      bool SBQBLZmIHr = false;
      bool RnPggobOeG = false;
      bool BhjwXAQYiT = false;
      bool ZbxKPynETI = false;
      bool WqnVJZQMod = false;
      bool NPpsXkQTcK = false;
      bool IOZmRppEQh = false;
      bool AXuWiJtOmx = false;
      bool jDjFFKkEme = false;
      bool gUaIzIRADS = false;
      bool jMwHcpUTJN = false;
      bool qCffaEeThH = false;
      bool ElQlAfxmWa = false;
      bool rsKUNXHccP = false;
      bool pRtYnenuhu = false;
      bool dxRuNxuKHw = false;
      bool sgxiVxrLRC = false;
      string WJprfPWkhG;
      string qGxcXcXlNM;
      string NlCVQtUiNW;
      string TBtmTMtJzd;
      string KTznIXIanH;
      string mVxrikGTbl;
      string tmWKmpMJIK;
      string hNljBtmONr;
      string ltuGjxDBEi;
      string FagNiXxnBR;
      string LyScZYjNpn;
      string xrFjzArPao;
      string lKEYFGfYAd;
      string xyMugmaRgK;
      string NpKPkMVxNi;
      string fgNMeAssXS;
      string sLMMqzfKCL;
      string YZiQbwzomr;
      string khKRyPkAPg;
      string shtNQCcyXl;
      if(WJprfPWkhG == LyScZYjNpn){gLtBKFxxji = true;}
      else if(LyScZYjNpn == WJprfPWkhG){AXuWiJtOmx = true;}
      if(qGxcXcXlNM == xrFjzArPao){AEFehKAuOb = true;}
      else if(xrFjzArPao == qGxcXcXlNM){jDjFFKkEme = true;}
      if(NlCVQtUiNW == lKEYFGfYAd){OftVSpeVzZ = true;}
      else if(lKEYFGfYAd == NlCVQtUiNW){gUaIzIRADS = true;}
      if(TBtmTMtJzd == xyMugmaRgK){SBQBLZmIHr = true;}
      else if(xyMugmaRgK == TBtmTMtJzd){jMwHcpUTJN = true;}
      if(KTznIXIanH == NpKPkMVxNi){RnPggobOeG = true;}
      else if(NpKPkMVxNi == KTznIXIanH){qCffaEeThH = true;}
      if(mVxrikGTbl == fgNMeAssXS){BhjwXAQYiT = true;}
      else if(fgNMeAssXS == mVxrikGTbl){ElQlAfxmWa = true;}
      if(tmWKmpMJIK == sLMMqzfKCL){ZbxKPynETI = true;}
      else if(sLMMqzfKCL == tmWKmpMJIK){rsKUNXHccP = true;}
      if(hNljBtmONr == YZiQbwzomr){WqnVJZQMod = true;}
      if(ltuGjxDBEi == khKRyPkAPg){NPpsXkQTcK = true;}
      if(FagNiXxnBR == shtNQCcyXl){IOZmRppEQh = true;}
      while(YZiQbwzomr == hNljBtmONr){pRtYnenuhu = true;}
      while(khKRyPkAPg == khKRyPkAPg){dxRuNxuKHw = true;}
      while(shtNQCcyXl == shtNQCcyXl){sgxiVxrLRC = true;}
      if(gLtBKFxxji == true){gLtBKFxxji = false;}
      if(AEFehKAuOb == true){AEFehKAuOb = false;}
      if(OftVSpeVzZ == true){OftVSpeVzZ = false;}
      if(SBQBLZmIHr == true){SBQBLZmIHr = false;}
      if(RnPggobOeG == true){RnPggobOeG = false;}
      if(BhjwXAQYiT == true){BhjwXAQYiT = false;}
      if(ZbxKPynETI == true){ZbxKPynETI = false;}
      if(WqnVJZQMod == true){WqnVJZQMod = false;}
      if(NPpsXkQTcK == true){NPpsXkQTcK = false;}
      if(IOZmRppEQh == true){IOZmRppEQh = false;}
      if(AXuWiJtOmx == true){AXuWiJtOmx = false;}
      if(jDjFFKkEme == true){jDjFFKkEme = false;}
      if(gUaIzIRADS == true){gUaIzIRADS = false;}
      if(jMwHcpUTJN == true){jMwHcpUTJN = false;}
      if(qCffaEeThH == true){qCffaEeThH = false;}
      if(ElQlAfxmWa == true){ElQlAfxmWa = false;}
      if(rsKUNXHccP == true){rsKUNXHccP = false;}
      if(pRtYnenuhu == true){pRtYnenuhu = false;}
      if(dxRuNxuKHw == true){dxRuNxuKHw = false;}
      if(sgxiVxrLRC == true){sgxiVxrLRC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AGSWMXEGCZ
{ 
  void zuJfZMbwsI()
  { 
      bool TsPRCYocco = false;
      bool JwOLjegYOS = false;
      bool hyHVuImqUb = false;
      bool mtsbPSPpmD = false;
      bool eTeIlusVVQ = false;
      bool wlxoUVlsVt = false;
      bool kxHBCOCmwQ = false;
      bool PplLnOSziz = false;
      bool PRVEeBwEGs = false;
      bool gVUsRgLdGX = false;
      bool sGYEBFzlAF = false;
      bool DlKVdSbDVB = false;
      bool RyfCjsVssG = false;
      bool DnsLGJsQCZ = false;
      bool BKDBptLzOy = false;
      bool FIIEFtZVUH = false;
      bool jGrtCOsyOU = false;
      bool ZKAwzHueMo = false;
      bool hWeuAtfnGM = false;
      bool iWutouSIyb = false;
      string QjPNZUEinK;
      string obLBxcHqRp;
      string rkrcuNmWVh;
      string STxaiPbfuU;
      string ZzZwgGeamJ;
      string AyVelfrlSM;
      string ggMGqVekRh;
      string BawxPsKuwn;
      string iMiLgUySnD;
      string WoMhnsmTFK;
      string bsJFIZCXOs;
      string UwpecTyAYW;
      string XLwNKLONJW;
      string GppkMoDcDH;
      string RZEuhazhFT;
      string tlthmQxuux;
      string KoOqmeGFRn;
      string QUxREyHBfi;
      string MfHobTwIxw;
      string rIgFwcKMHD;
      if(QjPNZUEinK == bsJFIZCXOs){TsPRCYocco = true;}
      else if(bsJFIZCXOs == QjPNZUEinK){sGYEBFzlAF = true;}
      if(obLBxcHqRp == UwpecTyAYW){JwOLjegYOS = true;}
      else if(UwpecTyAYW == obLBxcHqRp){DlKVdSbDVB = true;}
      if(rkrcuNmWVh == XLwNKLONJW){hyHVuImqUb = true;}
      else if(XLwNKLONJW == rkrcuNmWVh){RyfCjsVssG = true;}
      if(STxaiPbfuU == GppkMoDcDH){mtsbPSPpmD = true;}
      else if(GppkMoDcDH == STxaiPbfuU){DnsLGJsQCZ = true;}
      if(ZzZwgGeamJ == RZEuhazhFT){eTeIlusVVQ = true;}
      else if(RZEuhazhFT == ZzZwgGeamJ){BKDBptLzOy = true;}
      if(AyVelfrlSM == tlthmQxuux){wlxoUVlsVt = true;}
      else if(tlthmQxuux == AyVelfrlSM){FIIEFtZVUH = true;}
      if(ggMGqVekRh == KoOqmeGFRn){kxHBCOCmwQ = true;}
      else if(KoOqmeGFRn == ggMGqVekRh){jGrtCOsyOU = true;}
      if(BawxPsKuwn == QUxREyHBfi){PplLnOSziz = true;}
      if(iMiLgUySnD == MfHobTwIxw){PRVEeBwEGs = true;}
      if(WoMhnsmTFK == rIgFwcKMHD){gVUsRgLdGX = true;}
      while(QUxREyHBfi == BawxPsKuwn){ZKAwzHueMo = true;}
      while(MfHobTwIxw == MfHobTwIxw){hWeuAtfnGM = true;}
      while(rIgFwcKMHD == rIgFwcKMHD){iWutouSIyb = true;}
      if(TsPRCYocco == true){TsPRCYocco = false;}
      if(JwOLjegYOS == true){JwOLjegYOS = false;}
      if(hyHVuImqUb == true){hyHVuImqUb = false;}
      if(mtsbPSPpmD == true){mtsbPSPpmD = false;}
      if(eTeIlusVVQ == true){eTeIlusVVQ = false;}
      if(wlxoUVlsVt == true){wlxoUVlsVt = false;}
      if(kxHBCOCmwQ == true){kxHBCOCmwQ = false;}
      if(PplLnOSziz == true){PplLnOSziz = false;}
      if(PRVEeBwEGs == true){PRVEeBwEGs = false;}
      if(gVUsRgLdGX == true){gVUsRgLdGX = false;}
      if(sGYEBFzlAF == true){sGYEBFzlAF = false;}
      if(DlKVdSbDVB == true){DlKVdSbDVB = false;}
      if(RyfCjsVssG == true){RyfCjsVssG = false;}
      if(DnsLGJsQCZ == true){DnsLGJsQCZ = false;}
      if(BKDBptLzOy == true){BKDBptLzOy = false;}
      if(FIIEFtZVUH == true){FIIEFtZVUH = false;}
      if(jGrtCOsyOU == true){jGrtCOsyOU = false;}
      if(ZKAwzHueMo == true){ZKAwzHueMo = false;}
      if(hWeuAtfnGM == true){hWeuAtfnGM = false;}
      if(iWutouSIyb == true){iWutouSIyb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQUUWAPSWY
{ 
  void VfJidsDDKA()
  { 
      bool KgoWkKqyox = false;
      bool CruYuoesak = false;
      bool YMtGPJJYkm = false;
      bool icmEnGzChw = false;
      bool mDyidlVcXH = false;
      bool MDePaxmhGb = false;
      bool BSNCNZFpkn = false;
      bool pbKeyUOKcd = false;
      bool ngAcafyWdp = false;
      bool SQwGtTpwVD = false;
      bool feqiRkrzRF = false;
      bool icEbmUSkah = false;
      bool bhLtVZeEkd = false;
      bool eRnZxIoQLp = false;
      bool myFXGpLTTY = false;
      bool BEUnbyTxNr = false;
      bool FnOmaQneee = false;
      bool fBYktdbmme = false;
      bool NLkLbZwAyz = false;
      bool oqCTkyiSxo = false;
      string fVarbfGdsS;
      string hSJnGHQmZd;
      string uuLFJasQCO;
      string CitMWcQQXp;
      string uEUKVhgxKV;
      string sKdtTkJVhA;
      string moaeQyXwRc;
      string qzOihpZBib;
      string twFgUqFAsl;
      string TuiXDFcpsX;
      string JjegetutLc;
      string KIlGFqitJZ;
      string rXDfJwQqfc;
      string NiHLSKQYCa;
      string uLnPaLIbRL;
      string VigTelfzWi;
      string dENhPaAamt;
      string aKrhdgimEy;
      string mnZTHdCngf;
      string eQBSxqxGAz;
      if(fVarbfGdsS == JjegetutLc){KgoWkKqyox = true;}
      else if(JjegetutLc == fVarbfGdsS){feqiRkrzRF = true;}
      if(hSJnGHQmZd == KIlGFqitJZ){CruYuoesak = true;}
      else if(KIlGFqitJZ == hSJnGHQmZd){icEbmUSkah = true;}
      if(uuLFJasQCO == rXDfJwQqfc){YMtGPJJYkm = true;}
      else if(rXDfJwQqfc == uuLFJasQCO){bhLtVZeEkd = true;}
      if(CitMWcQQXp == NiHLSKQYCa){icmEnGzChw = true;}
      else if(NiHLSKQYCa == CitMWcQQXp){eRnZxIoQLp = true;}
      if(uEUKVhgxKV == uLnPaLIbRL){mDyidlVcXH = true;}
      else if(uLnPaLIbRL == uEUKVhgxKV){myFXGpLTTY = true;}
      if(sKdtTkJVhA == VigTelfzWi){MDePaxmhGb = true;}
      else if(VigTelfzWi == sKdtTkJVhA){BEUnbyTxNr = true;}
      if(moaeQyXwRc == dENhPaAamt){BSNCNZFpkn = true;}
      else if(dENhPaAamt == moaeQyXwRc){FnOmaQneee = true;}
      if(qzOihpZBib == aKrhdgimEy){pbKeyUOKcd = true;}
      if(twFgUqFAsl == mnZTHdCngf){ngAcafyWdp = true;}
      if(TuiXDFcpsX == eQBSxqxGAz){SQwGtTpwVD = true;}
      while(aKrhdgimEy == qzOihpZBib){fBYktdbmme = true;}
      while(mnZTHdCngf == mnZTHdCngf){NLkLbZwAyz = true;}
      while(eQBSxqxGAz == eQBSxqxGAz){oqCTkyiSxo = true;}
      if(KgoWkKqyox == true){KgoWkKqyox = false;}
      if(CruYuoesak == true){CruYuoesak = false;}
      if(YMtGPJJYkm == true){YMtGPJJYkm = false;}
      if(icmEnGzChw == true){icmEnGzChw = false;}
      if(mDyidlVcXH == true){mDyidlVcXH = false;}
      if(MDePaxmhGb == true){MDePaxmhGb = false;}
      if(BSNCNZFpkn == true){BSNCNZFpkn = false;}
      if(pbKeyUOKcd == true){pbKeyUOKcd = false;}
      if(ngAcafyWdp == true){ngAcafyWdp = false;}
      if(SQwGtTpwVD == true){SQwGtTpwVD = false;}
      if(feqiRkrzRF == true){feqiRkrzRF = false;}
      if(icEbmUSkah == true){icEbmUSkah = false;}
      if(bhLtVZeEkd == true){bhLtVZeEkd = false;}
      if(eRnZxIoQLp == true){eRnZxIoQLp = false;}
      if(myFXGpLTTY == true){myFXGpLTTY = false;}
      if(BEUnbyTxNr == true){BEUnbyTxNr = false;}
      if(FnOmaQneee == true){FnOmaQneee = false;}
      if(fBYktdbmme == true){fBYktdbmme = false;}
      if(NLkLbZwAyz == true){NLkLbZwAyz = false;}
      if(oqCTkyiSxo == true){oqCTkyiSxo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JXCWKYSIZL
{ 
  void YWEkcaXQoC()
  { 
      bool QKeeDGxYmS = false;
      bool ZmVUqiexld = false;
      bool oTirfJiZzl = false;
      bool DGcrSNLBVy = false;
      bool uORwmmNqwH = false;
      bool JWeNoxalzt = false;
      bool WWYAPTJdBc = false;
      bool XcbniZCmEr = false;
      bool wrdrcfbPDV = false;
      bool mYCbbXoQgT = false;
      bool cjpSifuqeO = false;
      bool umhGxesgXj = false;
      bool qtafpyaALK = false;
      bool jkGkOMBKIw = false;
      bool kkjnazqudx = false;
      bool eIrxciJJbk = false;
      bool FteUdJgwqk = false;
      bool chXbyFJlEq = false;
      bool HeVOebrJIf = false;
      bool CriXppGPKQ = false;
      string KSAbIGlKOK;
      string fXZGqgubdw;
      string XIOePtldtu;
      string BZgyokjPlm;
      string XrmCOWTnit;
      string fUlXHBEVLN;
      string THQTJFqbRF;
      string wepqXfVLPs;
      string ZytAPfnJqm;
      string gODXTPbSrI;
      string frWcxAduAa;
      string frFSmVNQEc;
      string RgjdYhaRXH;
      string ECTGMhbQCO;
      string BsJPHoJkkx;
      string CKOOqyHrEP;
      string YMXrWcXyGF;
      string swNobYXUWj;
      string XpgZFsnEON;
      string ZiMmpoUQrd;
      if(KSAbIGlKOK == frWcxAduAa){QKeeDGxYmS = true;}
      else if(frWcxAduAa == KSAbIGlKOK){cjpSifuqeO = true;}
      if(fXZGqgubdw == frFSmVNQEc){ZmVUqiexld = true;}
      else if(frFSmVNQEc == fXZGqgubdw){umhGxesgXj = true;}
      if(XIOePtldtu == RgjdYhaRXH){oTirfJiZzl = true;}
      else if(RgjdYhaRXH == XIOePtldtu){qtafpyaALK = true;}
      if(BZgyokjPlm == ECTGMhbQCO){DGcrSNLBVy = true;}
      else if(ECTGMhbQCO == BZgyokjPlm){jkGkOMBKIw = true;}
      if(XrmCOWTnit == BsJPHoJkkx){uORwmmNqwH = true;}
      else if(BsJPHoJkkx == XrmCOWTnit){kkjnazqudx = true;}
      if(fUlXHBEVLN == CKOOqyHrEP){JWeNoxalzt = true;}
      else if(CKOOqyHrEP == fUlXHBEVLN){eIrxciJJbk = true;}
      if(THQTJFqbRF == YMXrWcXyGF){WWYAPTJdBc = true;}
      else if(YMXrWcXyGF == THQTJFqbRF){FteUdJgwqk = true;}
      if(wepqXfVLPs == swNobYXUWj){XcbniZCmEr = true;}
      if(ZytAPfnJqm == XpgZFsnEON){wrdrcfbPDV = true;}
      if(gODXTPbSrI == ZiMmpoUQrd){mYCbbXoQgT = true;}
      while(swNobYXUWj == wepqXfVLPs){chXbyFJlEq = true;}
      while(XpgZFsnEON == XpgZFsnEON){HeVOebrJIf = true;}
      while(ZiMmpoUQrd == ZiMmpoUQrd){CriXppGPKQ = true;}
      if(QKeeDGxYmS == true){QKeeDGxYmS = false;}
      if(ZmVUqiexld == true){ZmVUqiexld = false;}
      if(oTirfJiZzl == true){oTirfJiZzl = false;}
      if(DGcrSNLBVy == true){DGcrSNLBVy = false;}
      if(uORwmmNqwH == true){uORwmmNqwH = false;}
      if(JWeNoxalzt == true){JWeNoxalzt = false;}
      if(WWYAPTJdBc == true){WWYAPTJdBc = false;}
      if(XcbniZCmEr == true){XcbniZCmEr = false;}
      if(wrdrcfbPDV == true){wrdrcfbPDV = false;}
      if(mYCbbXoQgT == true){mYCbbXoQgT = false;}
      if(cjpSifuqeO == true){cjpSifuqeO = false;}
      if(umhGxesgXj == true){umhGxesgXj = false;}
      if(qtafpyaALK == true){qtafpyaALK = false;}
      if(jkGkOMBKIw == true){jkGkOMBKIw = false;}
      if(kkjnazqudx == true){kkjnazqudx = false;}
      if(eIrxciJJbk == true){eIrxciJJbk = false;}
      if(FteUdJgwqk == true){FteUdJgwqk = false;}
      if(chXbyFJlEq == true){chXbyFJlEq = false;}
      if(HeVOebrJIf == true){HeVOebrJIf = false;}
      if(CriXppGPKQ == true){CriXppGPKQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TMXJXRYYNB
{ 
  void LNWMwpXOjn()
  { 
      bool hIZxYzDygd = false;
      bool cOFYoBGYtr = false;
      bool DuIhWtCllQ = false;
      bool XqPRgbDDHU = false;
      bool bVLRwlSVcL = false;
      bool DohKsmArZe = false;
      bool xRMQFlymrM = false;
      bool xCQYPgjpkk = false;
      bool bgIZMhIFXt = false;
      bool bLccXKJtLK = false;
      bool mecQOBYJtM = false;
      bool DJGoDPJlEW = false;
      bool csOykkYmBF = false;
      bool XoeZxwDqLL = false;
      bool JzKLpSFnZH = false;
      bool BWpnhsPeec = false;
      bool bkHnnNdfrG = false;
      bool LRZrNdhCHS = false;
      bool fkNsEAyqrD = false;
      bool fYMijXqVXc = false;
      string niPfiMZjfO;
      string JmfRBHsolQ;
      string SirNXTDiSB;
      string ZDCxSDeUpL;
      string UXWpcsKEYA;
      string PcEcIEqBIP;
      string JpQeoFkizy;
      string bXyauuMBjd;
      string JyKSkwyYnN;
      string LdLaCdGrAX;
      string IbFaYredgM;
      string roQdFKfysr;
      string GLtklyLWYR;
      string nTBMVhriss;
      string RTrbVWMhVq;
      string xIyHQwgUna;
      string fHFOYYnEHX;
      string RxEAalTSPP;
      string kdBgUfUsuZ;
      string AXtSNKOcCx;
      if(niPfiMZjfO == IbFaYredgM){hIZxYzDygd = true;}
      else if(IbFaYredgM == niPfiMZjfO){mecQOBYJtM = true;}
      if(JmfRBHsolQ == roQdFKfysr){cOFYoBGYtr = true;}
      else if(roQdFKfysr == JmfRBHsolQ){DJGoDPJlEW = true;}
      if(SirNXTDiSB == GLtklyLWYR){DuIhWtCllQ = true;}
      else if(GLtklyLWYR == SirNXTDiSB){csOykkYmBF = true;}
      if(ZDCxSDeUpL == nTBMVhriss){XqPRgbDDHU = true;}
      else if(nTBMVhriss == ZDCxSDeUpL){XoeZxwDqLL = true;}
      if(UXWpcsKEYA == RTrbVWMhVq){bVLRwlSVcL = true;}
      else if(RTrbVWMhVq == UXWpcsKEYA){JzKLpSFnZH = true;}
      if(PcEcIEqBIP == xIyHQwgUna){DohKsmArZe = true;}
      else if(xIyHQwgUna == PcEcIEqBIP){BWpnhsPeec = true;}
      if(JpQeoFkizy == fHFOYYnEHX){xRMQFlymrM = true;}
      else if(fHFOYYnEHX == JpQeoFkizy){bkHnnNdfrG = true;}
      if(bXyauuMBjd == RxEAalTSPP){xCQYPgjpkk = true;}
      if(JyKSkwyYnN == kdBgUfUsuZ){bgIZMhIFXt = true;}
      if(LdLaCdGrAX == AXtSNKOcCx){bLccXKJtLK = true;}
      while(RxEAalTSPP == bXyauuMBjd){LRZrNdhCHS = true;}
      while(kdBgUfUsuZ == kdBgUfUsuZ){fkNsEAyqrD = true;}
      while(AXtSNKOcCx == AXtSNKOcCx){fYMijXqVXc = true;}
      if(hIZxYzDygd == true){hIZxYzDygd = false;}
      if(cOFYoBGYtr == true){cOFYoBGYtr = false;}
      if(DuIhWtCllQ == true){DuIhWtCllQ = false;}
      if(XqPRgbDDHU == true){XqPRgbDDHU = false;}
      if(bVLRwlSVcL == true){bVLRwlSVcL = false;}
      if(DohKsmArZe == true){DohKsmArZe = false;}
      if(xRMQFlymrM == true){xRMQFlymrM = false;}
      if(xCQYPgjpkk == true){xCQYPgjpkk = false;}
      if(bgIZMhIFXt == true){bgIZMhIFXt = false;}
      if(bLccXKJtLK == true){bLccXKJtLK = false;}
      if(mecQOBYJtM == true){mecQOBYJtM = false;}
      if(DJGoDPJlEW == true){DJGoDPJlEW = false;}
      if(csOykkYmBF == true){csOykkYmBF = false;}
      if(XoeZxwDqLL == true){XoeZxwDqLL = false;}
      if(JzKLpSFnZH == true){JzKLpSFnZH = false;}
      if(BWpnhsPeec == true){BWpnhsPeec = false;}
      if(bkHnnNdfrG == true){bkHnnNdfrG = false;}
      if(LRZrNdhCHS == true){LRZrNdhCHS = false;}
      if(fkNsEAyqrD == true){fkNsEAyqrD = false;}
      if(fYMijXqVXc == true){fYMijXqVXc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GOBGKMJMRJ
{ 
  void LWSBkJQWQY()
  { 
      bool GmFFbFHUoW = false;
      bool aXykWnrRIe = false;
      bool FnmRajJcxL = false;
      bool VGCEgHJkau = false;
      bool JjToJyweYr = false;
      bool MncNSRAneq = false;
      bool udXcBTVtDO = false;
      bool eHpNVUUxIc = false;
      bool meDEygcnkP = false;
      bool HVGjzeMpno = false;
      bool cBbJNFyPrx = false;
      bool xCeBDQZSeT = false;
      bool qgJnGJAGNp = false;
      bool IdJSzkCtqr = false;
      bool iMwnSFpEfi = false;
      bool FsLTywrnCE = false;
      bool FqCBnSrMCS = false;
      bool NfalkdjUUB = false;
      bool SuaejORpTD = false;
      bool sOqmmqKtzz = false;
      string cFzEHJBBwR;
      string XaReNBQPst;
      string rzRanWzexX;
      string oMCwYEVdbV;
      string RZjoNeaqYg;
      string NTDRMcnXPj;
      string KVEXcLXVFI;
      string flnWbSPbNJ;
      string uHFPKVIjju;
      string QxOrLuULMC;
      string GFkQBafgot;
      string NMKFnCPnNG;
      string DmlJrhXuLg;
      string xDOKDpWoOj;
      string pbuphDmIDI;
      string fgyFySTaYS;
      string DjUIwJxzCx;
      string fZYdQbrubn;
      string uPqDAQEIMj;
      string WuQwfFGlsX;
      if(cFzEHJBBwR == GFkQBafgot){GmFFbFHUoW = true;}
      else if(GFkQBafgot == cFzEHJBBwR){cBbJNFyPrx = true;}
      if(XaReNBQPst == NMKFnCPnNG){aXykWnrRIe = true;}
      else if(NMKFnCPnNG == XaReNBQPst){xCeBDQZSeT = true;}
      if(rzRanWzexX == DmlJrhXuLg){FnmRajJcxL = true;}
      else if(DmlJrhXuLg == rzRanWzexX){qgJnGJAGNp = true;}
      if(oMCwYEVdbV == xDOKDpWoOj){VGCEgHJkau = true;}
      else if(xDOKDpWoOj == oMCwYEVdbV){IdJSzkCtqr = true;}
      if(RZjoNeaqYg == pbuphDmIDI){JjToJyweYr = true;}
      else if(pbuphDmIDI == RZjoNeaqYg){iMwnSFpEfi = true;}
      if(NTDRMcnXPj == fgyFySTaYS){MncNSRAneq = true;}
      else if(fgyFySTaYS == NTDRMcnXPj){FsLTywrnCE = true;}
      if(KVEXcLXVFI == DjUIwJxzCx){udXcBTVtDO = true;}
      else if(DjUIwJxzCx == KVEXcLXVFI){FqCBnSrMCS = true;}
      if(flnWbSPbNJ == fZYdQbrubn){eHpNVUUxIc = true;}
      if(uHFPKVIjju == uPqDAQEIMj){meDEygcnkP = true;}
      if(QxOrLuULMC == WuQwfFGlsX){HVGjzeMpno = true;}
      while(fZYdQbrubn == flnWbSPbNJ){NfalkdjUUB = true;}
      while(uPqDAQEIMj == uPqDAQEIMj){SuaejORpTD = true;}
      while(WuQwfFGlsX == WuQwfFGlsX){sOqmmqKtzz = true;}
      if(GmFFbFHUoW == true){GmFFbFHUoW = false;}
      if(aXykWnrRIe == true){aXykWnrRIe = false;}
      if(FnmRajJcxL == true){FnmRajJcxL = false;}
      if(VGCEgHJkau == true){VGCEgHJkau = false;}
      if(JjToJyweYr == true){JjToJyweYr = false;}
      if(MncNSRAneq == true){MncNSRAneq = false;}
      if(udXcBTVtDO == true){udXcBTVtDO = false;}
      if(eHpNVUUxIc == true){eHpNVUUxIc = false;}
      if(meDEygcnkP == true){meDEygcnkP = false;}
      if(HVGjzeMpno == true){HVGjzeMpno = false;}
      if(cBbJNFyPrx == true){cBbJNFyPrx = false;}
      if(xCeBDQZSeT == true){xCeBDQZSeT = false;}
      if(qgJnGJAGNp == true){qgJnGJAGNp = false;}
      if(IdJSzkCtqr == true){IdJSzkCtqr = false;}
      if(iMwnSFpEfi == true){iMwnSFpEfi = false;}
      if(FsLTywrnCE == true){FsLTywrnCE = false;}
      if(FqCBnSrMCS == true){FqCBnSrMCS = false;}
      if(NfalkdjUUB == true){NfalkdjUUB = false;}
      if(SuaejORpTD == true){SuaejORpTD = false;}
      if(sOqmmqKtzz == true){sOqmmqKtzz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OPIYSIPHKP
{ 
  void SRAIHAHbJY()
  { 
      bool YPkUKMVjIj = false;
      bool VQzVqDHnDt = false;
      bool LAOkUCzoDI = false;
      bool eQEQZkdMTJ = false;
      bool aXkMdqWtXj = false;
      bool YJgrXYBzAH = false;
      bool NgfzEFLhwG = false;
      bool YuUsSnPBHc = false;
      bool eERTjUjLrB = false;
      bool jdLLutrkIX = false;
      bool foxRKcomZj = false;
      bool IArWcIOLOi = false;
      bool UzouVtiIyX = false;
      bool udsjxpHzJH = false;
      bool fxlIrjloil = false;
      bool efWYCfzCuP = false;
      bool tgnCneHHYm = false;
      bool BOCHDXNgCl = false;
      bool IsZLrOHTgR = false;
      bool pEEsMyIjTN = false;
      string qoSwZDEVql;
      string TehREVNDqf;
      string ojHZhliedi;
      string kYkTKkrtez;
      string CeeIEbrJGz;
      string XtZCZGhsOm;
      string TYqHBttOGT;
      string cSXrcKFyVF;
      string sYXeKqzisD;
      string CzfredmWHJ;
      string hdCmWFVgYO;
      string BjXIsuAMwK;
      string uKVDRclfNz;
      string XhpLWPVkIF;
      string URJdCSbWyi;
      string cZaxNWHzUs;
      string SoSZqSsLkc;
      string YPEqodAqAz;
      string BPhdWxHsxA;
      string HWPOmfyjlj;
      if(qoSwZDEVql == hdCmWFVgYO){YPkUKMVjIj = true;}
      else if(hdCmWFVgYO == qoSwZDEVql){foxRKcomZj = true;}
      if(TehREVNDqf == BjXIsuAMwK){VQzVqDHnDt = true;}
      else if(BjXIsuAMwK == TehREVNDqf){IArWcIOLOi = true;}
      if(ojHZhliedi == uKVDRclfNz){LAOkUCzoDI = true;}
      else if(uKVDRclfNz == ojHZhliedi){UzouVtiIyX = true;}
      if(kYkTKkrtez == XhpLWPVkIF){eQEQZkdMTJ = true;}
      else if(XhpLWPVkIF == kYkTKkrtez){udsjxpHzJH = true;}
      if(CeeIEbrJGz == URJdCSbWyi){aXkMdqWtXj = true;}
      else if(URJdCSbWyi == CeeIEbrJGz){fxlIrjloil = true;}
      if(XtZCZGhsOm == cZaxNWHzUs){YJgrXYBzAH = true;}
      else if(cZaxNWHzUs == XtZCZGhsOm){efWYCfzCuP = true;}
      if(TYqHBttOGT == SoSZqSsLkc){NgfzEFLhwG = true;}
      else if(SoSZqSsLkc == TYqHBttOGT){tgnCneHHYm = true;}
      if(cSXrcKFyVF == YPEqodAqAz){YuUsSnPBHc = true;}
      if(sYXeKqzisD == BPhdWxHsxA){eERTjUjLrB = true;}
      if(CzfredmWHJ == HWPOmfyjlj){jdLLutrkIX = true;}
      while(YPEqodAqAz == cSXrcKFyVF){BOCHDXNgCl = true;}
      while(BPhdWxHsxA == BPhdWxHsxA){IsZLrOHTgR = true;}
      while(HWPOmfyjlj == HWPOmfyjlj){pEEsMyIjTN = true;}
      if(YPkUKMVjIj == true){YPkUKMVjIj = false;}
      if(VQzVqDHnDt == true){VQzVqDHnDt = false;}
      if(LAOkUCzoDI == true){LAOkUCzoDI = false;}
      if(eQEQZkdMTJ == true){eQEQZkdMTJ = false;}
      if(aXkMdqWtXj == true){aXkMdqWtXj = false;}
      if(YJgrXYBzAH == true){YJgrXYBzAH = false;}
      if(NgfzEFLhwG == true){NgfzEFLhwG = false;}
      if(YuUsSnPBHc == true){YuUsSnPBHc = false;}
      if(eERTjUjLrB == true){eERTjUjLrB = false;}
      if(jdLLutrkIX == true){jdLLutrkIX = false;}
      if(foxRKcomZj == true){foxRKcomZj = false;}
      if(IArWcIOLOi == true){IArWcIOLOi = false;}
      if(UzouVtiIyX == true){UzouVtiIyX = false;}
      if(udsjxpHzJH == true){udsjxpHzJH = false;}
      if(fxlIrjloil == true){fxlIrjloil = false;}
      if(efWYCfzCuP == true){efWYCfzCuP = false;}
      if(tgnCneHHYm == true){tgnCneHHYm = false;}
      if(BOCHDXNgCl == true){BOCHDXNgCl = false;}
      if(IsZLrOHTgR == true){IsZLrOHTgR = false;}
      if(pEEsMyIjTN == true){pEEsMyIjTN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IOQZSSYESE
{ 
  void XdSrLIHBpD()
  { 
      bool BXJsYASjNh = false;
      bool xNSqsyfVns = false;
      bool FLMVqYkgbm = false;
      bool DOBroQpIGW = false;
      bool TKhuyONlzt = false;
      bool hYzVIpKmBA = false;
      bool PkHaeiLaCb = false;
      bool IXPRZudQWb = false;
      bool KyhhEdOejz = false;
      bool FCGGGhCGQP = false;
      bool CmjXkKJhwN = false;
      bool MtQYoRDZVA = false;
      bool TgpCVFRJKr = false;
      bool sWzHZXNKws = false;
      bool UgiWmLlgRn = false;
      bool dbjQuVxhBe = false;
      bool sAWETotIzR = false;
      bool EsdcelxTPJ = false;
      bool TjrVNQlhLD = false;
      bool ZeIQAUJeCx = false;
      string PZXVfoodpq;
      string joyBygaTND;
      string VFhcHFZMTM;
      string xbjhVULGOI;
      string UBrHlHHYNH;
      string uCRidKrtOZ;
      string ObKcsHEQec;
      string VTEEhUMZqz;
      string yByLRtKBEK;
      string bRqosspOOe;
      string CqsjlaxMBI;
      string xSDOaNczKy;
      string xCMTBDbPLn;
      string dyLLwHHNZq;
      string xxAuNJObNf;
      string PqDPhAeZih;
      string yhBMezHqST;
      string GOYTBzCQGq;
      string ozBeXltudw;
      string cgdrrOunPN;
      if(PZXVfoodpq == CqsjlaxMBI){BXJsYASjNh = true;}
      else if(CqsjlaxMBI == PZXVfoodpq){CmjXkKJhwN = true;}
      if(joyBygaTND == xSDOaNczKy){xNSqsyfVns = true;}
      else if(xSDOaNczKy == joyBygaTND){MtQYoRDZVA = true;}
      if(VFhcHFZMTM == xCMTBDbPLn){FLMVqYkgbm = true;}
      else if(xCMTBDbPLn == VFhcHFZMTM){TgpCVFRJKr = true;}
      if(xbjhVULGOI == dyLLwHHNZq){DOBroQpIGW = true;}
      else if(dyLLwHHNZq == xbjhVULGOI){sWzHZXNKws = true;}
      if(UBrHlHHYNH == xxAuNJObNf){TKhuyONlzt = true;}
      else if(xxAuNJObNf == UBrHlHHYNH){UgiWmLlgRn = true;}
      if(uCRidKrtOZ == PqDPhAeZih){hYzVIpKmBA = true;}
      else if(PqDPhAeZih == uCRidKrtOZ){dbjQuVxhBe = true;}
      if(ObKcsHEQec == yhBMezHqST){PkHaeiLaCb = true;}
      else if(yhBMezHqST == ObKcsHEQec){sAWETotIzR = true;}
      if(VTEEhUMZqz == GOYTBzCQGq){IXPRZudQWb = true;}
      if(yByLRtKBEK == ozBeXltudw){KyhhEdOejz = true;}
      if(bRqosspOOe == cgdrrOunPN){FCGGGhCGQP = true;}
      while(GOYTBzCQGq == VTEEhUMZqz){EsdcelxTPJ = true;}
      while(ozBeXltudw == ozBeXltudw){TjrVNQlhLD = true;}
      while(cgdrrOunPN == cgdrrOunPN){ZeIQAUJeCx = true;}
      if(BXJsYASjNh == true){BXJsYASjNh = false;}
      if(xNSqsyfVns == true){xNSqsyfVns = false;}
      if(FLMVqYkgbm == true){FLMVqYkgbm = false;}
      if(DOBroQpIGW == true){DOBroQpIGW = false;}
      if(TKhuyONlzt == true){TKhuyONlzt = false;}
      if(hYzVIpKmBA == true){hYzVIpKmBA = false;}
      if(PkHaeiLaCb == true){PkHaeiLaCb = false;}
      if(IXPRZudQWb == true){IXPRZudQWb = false;}
      if(KyhhEdOejz == true){KyhhEdOejz = false;}
      if(FCGGGhCGQP == true){FCGGGhCGQP = false;}
      if(CmjXkKJhwN == true){CmjXkKJhwN = false;}
      if(MtQYoRDZVA == true){MtQYoRDZVA = false;}
      if(TgpCVFRJKr == true){TgpCVFRJKr = false;}
      if(sWzHZXNKws == true){sWzHZXNKws = false;}
      if(UgiWmLlgRn == true){UgiWmLlgRn = false;}
      if(dbjQuVxhBe == true){dbjQuVxhBe = false;}
      if(sAWETotIzR == true){sAWETotIzR = false;}
      if(EsdcelxTPJ == true){EsdcelxTPJ = false;}
      if(TjrVNQlhLD == true){TjrVNQlhLD = false;}
      if(ZeIQAUJeCx == true){ZeIQAUJeCx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SKFADBARHX
{ 
  void FmoSqFEcpT()
  { 
      bool NjuXZykjJD = false;
      bool cWMqkzozFE = false;
      bool BAhgVpdtzQ = false;
      bool mWUefyLKTj = false;
      bool PHzemCeeoi = false;
      bool DRPWHNCNBi = false;
      bool TqksPGChLl = false;
      bool nefVntBCsS = false;
      bool LzEPMVGxXS = false;
      bool wxIjPYWGPg = false;
      bool AxTCuYkthN = false;
      bool MzThXUlUfs = false;
      bool zEJrppWwGP = false;
      bool XtmMSOfCUn = false;
      bool kMOKGwcZLu = false;
      bool mBaWhumaME = false;
      bool ConSoRMHPJ = false;
      bool niAqHlozls = false;
      bool MwjKbVTPdW = false;
      bool bEpPluYwUn = false;
      string cAUfrwOGFj;
      string AlBTATNrhY;
      string DSlBdNhrti;
      string ThzcSXahkx;
      string feOMnOVtfw;
      string ledPjJNTBe;
      string OVLVQRmXAb;
      string rfGjrXEZMP;
      string qmMywoDisI;
      string KHfGiJSrwV;
      string aysDEGXtXL;
      string FmGlnaJNYb;
      string OEerRjAAAi;
      string FLdpnssItp;
      string QJKhDWBsSH;
      string zETUHWTBlT;
      string GWsoFtJQyu;
      string hBTiKEswnt;
      string iGhsiArJhQ;
      string YqWZisQVbJ;
      if(cAUfrwOGFj == aysDEGXtXL){NjuXZykjJD = true;}
      else if(aysDEGXtXL == cAUfrwOGFj){AxTCuYkthN = true;}
      if(AlBTATNrhY == FmGlnaJNYb){cWMqkzozFE = true;}
      else if(FmGlnaJNYb == AlBTATNrhY){MzThXUlUfs = true;}
      if(DSlBdNhrti == OEerRjAAAi){BAhgVpdtzQ = true;}
      else if(OEerRjAAAi == DSlBdNhrti){zEJrppWwGP = true;}
      if(ThzcSXahkx == FLdpnssItp){mWUefyLKTj = true;}
      else if(FLdpnssItp == ThzcSXahkx){XtmMSOfCUn = true;}
      if(feOMnOVtfw == QJKhDWBsSH){PHzemCeeoi = true;}
      else if(QJKhDWBsSH == feOMnOVtfw){kMOKGwcZLu = true;}
      if(ledPjJNTBe == zETUHWTBlT){DRPWHNCNBi = true;}
      else if(zETUHWTBlT == ledPjJNTBe){mBaWhumaME = true;}
      if(OVLVQRmXAb == GWsoFtJQyu){TqksPGChLl = true;}
      else if(GWsoFtJQyu == OVLVQRmXAb){ConSoRMHPJ = true;}
      if(rfGjrXEZMP == hBTiKEswnt){nefVntBCsS = true;}
      if(qmMywoDisI == iGhsiArJhQ){LzEPMVGxXS = true;}
      if(KHfGiJSrwV == YqWZisQVbJ){wxIjPYWGPg = true;}
      while(hBTiKEswnt == rfGjrXEZMP){niAqHlozls = true;}
      while(iGhsiArJhQ == iGhsiArJhQ){MwjKbVTPdW = true;}
      while(YqWZisQVbJ == YqWZisQVbJ){bEpPluYwUn = true;}
      if(NjuXZykjJD == true){NjuXZykjJD = false;}
      if(cWMqkzozFE == true){cWMqkzozFE = false;}
      if(BAhgVpdtzQ == true){BAhgVpdtzQ = false;}
      if(mWUefyLKTj == true){mWUefyLKTj = false;}
      if(PHzemCeeoi == true){PHzemCeeoi = false;}
      if(DRPWHNCNBi == true){DRPWHNCNBi = false;}
      if(TqksPGChLl == true){TqksPGChLl = false;}
      if(nefVntBCsS == true){nefVntBCsS = false;}
      if(LzEPMVGxXS == true){LzEPMVGxXS = false;}
      if(wxIjPYWGPg == true){wxIjPYWGPg = false;}
      if(AxTCuYkthN == true){AxTCuYkthN = false;}
      if(MzThXUlUfs == true){MzThXUlUfs = false;}
      if(zEJrppWwGP == true){zEJrppWwGP = false;}
      if(XtmMSOfCUn == true){XtmMSOfCUn = false;}
      if(kMOKGwcZLu == true){kMOKGwcZLu = false;}
      if(mBaWhumaME == true){mBaWhumaME = false;}
      if(ConSoRMHPJ == true){ConSoRMHPJ = false;}
      if(niAqHlozls == true){niAqHlozls = false;}
      if(MwjKbVTPdW == true){MwjKbVTPdW = false;}
      if(bEpPluYwUn == true){bEpPluYwUn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OUPMLBPHBW
{ 
  void extloWyfcM()
  { 
      bool oKYUjRzaoR = false;
      bool DBUccMUARs = false;
      bool dWKeyyqDyF = false;
      bool KpkZhzFKEV = false;
      bool UCxoVgCYEK = false;
      bool oXoWFRAtWl = false;
      bool ZuciHMPutd = false;
      bool GJuwXaZUIQ = false;
      bool uSymQlBOUP = false;
      bool zLnSuYZNhJ = false;
      bool QHdaEebsyd = false;
      bool rekFpGxoSU = false;
      bool LAZdeuVcAy = false;
      bool BLmzAnnXik = false;
      bool JIPqXUZibo = false;
      bool bkuMxPgAwJ = false;
      bool JzrzcfqkFC = false;
      bool RZGgKDjiFK = false;
      bool UlALWPQZCj = false;
      bool GnaZbKQQNq = false;
      string iuimJtmKlp;
      string KprstRxxHa;
      string wqWEUaoTHk;
      string WLSQRXeczi;
      string YwizyhJHtL;
      string UeKESqYeSh;
      string FTDBSzXbbW;
      string lTxYCzIXGl;
      string RhYuPrANxZ;
      string zAKQdEshfy;
      string KgfXZAgkCT;
      string iAYfQXtHka;
      string yJeBWlJfux;
      string FaqHajCBVO;
      string KOLdqybdAF;
      string KkwFABCdAm;
      string qApENHJQFf;
      string VrlVPixBJX;
      string JefomUdlGZ;
      string hXBhXKYGPi;
      if(iuimJtmKlp == KgfXZAgkCT){oKYUjRzaoR = true;}
      else if(KgfXZAgkCT == iuimJtmKlp){QHdaEebsyd = true;}
      if(KprstRxxHa == iAYfQXtHka){DBUccMUARs = true;}
      else if(iAYfQXtHka == KprstRxxHa){rekFpGxoSU = true;}
      if(wqWEUaoTHk == yJeBWlJfux){dWKeyyqDyF = true;}
      else if(yJeBWlJfux == wqWEUaoTHk){LAZdeuVcAy = true;}
      if(WLSQRXeczi == FaqHajCBVO){KpkZhzFKEV = true;}
      else if(FaqHajCBVO == WLSQRXeczi){BLmzAnnXik = true;}
      if(YwizyhJHtL == KOLdqybdAF){UCxoVgCYEK = true;}
      else if(KOLdqybdAF == YwizyhJHtL){JIPqXUZibo = true;}
      if(UeKESqYeSh == KkwFABCdAm){oXoWFRAtWl = true;}
      else if(KkwFABCdAm == UeKESqYeSh){bkuMxPgAwJ = true;}
      if(FTDBSzXbbW == qApENHJQFf){ZuciHMPutd = true;}
      else if(qApENHJQFf == FTDBSzXbbW){JzrzcfqkFC = true;}
      if(lTxYCzIXGl == VrlVPixBJX){GJuwXaZUIQ = true;}
      if(RhYuPrANxZ == JefomUdlGZ){uSymQlBOUP = true;}
      if(zAKQdEshfy == hXBhXKYGPi){zLnSuYZNhJ = true;}
      while(VrlVPixBJX == lTxYCzIXGl){RZGgKDjiFK = true;}
      while(JefomUdlGZ == JefomUdlGZ){UlALWPQZCj = true;}
      while(hXBhXKYGPi == hXBhXKYGPi){GnaZbKQQNq = true;}
      if(oKYUjRzaoR == true){oKYUjRzaoR = false;}
      if(DBUccMUARs == true){DBUccMUARs = false;}
      if(dWKeyyqDyF == true){dWKeyyqDyF = false;}
      if(KpkZhzFKEV == true){KpkZhzFKEV = false;}
      if(UCxoVgCYEK == true){UCxoVgCYEK = false;}
      if(oXoWFRAtWl == true){oXoWFRAtWl = false;}
      if(ZuciHMPutd == true){ZuciHMPutd = false;}
      if(GJuwXaZUIQ == true){GJuwXaZUIQ = false;}
      if(uSymQlBOUP == true){uSymQlBOUP = false;}
      if(zLnSuYZNhJ == true){zLnSuYZNhJ = false;}
      if(QHdaEebsyd == true){QHdaEebsyd = false;}
      if(rekFpGxoSU == true){rekFpGxoSU = false;}
      if(LAZdeuVcAy == true){LAZdeuVcAy = false;}
      if(BLmzAnnXik == true){BLmzAnnXik = false;}
      if(JIPqXUZibo == true){JIPqXUZibo = false;}
      if(bkuMxPgAwJ == true){bkuMxPgAwJ = false;}
      if(JzrzcfqkFC == true){JzrzcfqkFC = false;}
      if(RZGgKDjiFK == true){RZGgKDjiFK = false;}
      if(UlALWPQZCj == true){UlALWPQZCj = false;}
      if(GnaZbKQQNq == true){GnaZbKQQNq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OOSYUUWKZO
{ 
  void ARXKYyUgFh()
  { 
      bool bxKlCHNZPj = false;
      bool WyRVslZLgq = false;
      bool QNfkdUfErQ = false;
      bool XaneDcBTAH = false;
      bool erFOnomMWc = false;
      bool xCSJrOQYHh = false;
      bool aJhzLwKmRQ = false;
      bool kFLYMXHRxo = false;
      bool gTgOSUHdlo = false;
      bool LbMRfUKFCr = false;
      bool eAtGrqptwT = false;
      bool GybSAHcTfq = false;
      bool nfAcEJssrq = false;
      bool NBPEJgYZVb = false;
      bool eNgSiMztRY = false;
      bool rqYLDzzRCi = false;
      bool ywBEFEiWIT = false;
      bool iCxELayhtq = false;
      bool JzbTzWbEBK = false;
      bool gGXmdhMbMd = false;
      string DmfyWJKakf;
      string qjCRNLhuiK;
      string WOGaLifgLg;
      string sGcbNBgAlq;
      string AFJiVeplEC;
      string zzjtdngEmm;
      string dcPElkHZDL;
      string egIqKRFWFg;
      string rscIgtVhyZ;
      string UbNyMWpFwk;
      string WPirXSpsjM;
      string iJzGtkzGWr;
      string OYbdpDTJdm;
      string bAaUJbKjkO;
      string DcxlqKbHEb;
      string WihEVynEBT;
      string yfOxjhiewS;
      string ZPUInlapmf;
      string aLFCPrRVyL;
      string nFiQPXOABI;
      if(DmfyWJKakf == WPirXSpsjM){bxKlCHNZPj = true;}
      else if(WPirXSpsjM == DmfyWJKakf){eAtGrqptwT = true;}
      if(qjCRNLhuiK == iJzGtkzGWr){WyRVslZLgq = true;}
      else if(iJzGtkzGWr == qjCRNLhuiK){GybSAHcTfq = true;}
      if(WOGaLifgLg == OYbdpDTJdm){QNfkdUfErQ = true;}
      else if(OYbdpDTJdm == WOGaLifgLg){nfAcEJssrq = true;}
      if(sGcbNBgAlq == bAaUJbKjkO){XaneDcBTAH = true;}
      else if(bAaUJbKjkO == sGcbNBgAlq){NBPEJgYZVb = true;}
      if(AFJiVeplEC == DcxlqKbHEb){erFOnomMWc = true;}
      else if(DcxlqKbHEb == AFJiVeplEC){eNgSiMztRY = true;}
      if(zzjtdngEmm == WihEVynEBT){xCSJrOQYHh = true;}
      else if(WihEVynEBT == zzjtdngEmm){rqYLDzzRCi = true;}
      if(dcPElkHZDL == yfOxjhiewS){aJhzLwKmRQ = true;}
      else if(yfOxjhiewS == dcPElkHZDL){ywBEFEiWIT = true;}
      if(egIqKRFWFg == ZPUInlapmf){kFLYMXHRxo = true;}
      if(rscIgtVhyZ == aLFCPrRVyL){gTgOSUHdlo = true;}
      if(UbNyMWpFwk == nFiQPXOABI){LbMRfUKFCr = true;}
      while(ZPUInlapmf == egIqKRFWFg){iCxELayhtq = true;}
      while(aLFCPrRVyL == aLFCPrRVyL){JzbTzWbEBK = true;}
      while(nFiQPXOABI == nFiQPXOABI){gGXmdhMbMd = true;}
      if(bxKlCHNZPj == true){bxKlCHNZPj = false;}
      if(WyRVslZLgq == true){WyRVslZLgq = false;}
      if(QNfkdUfErQ == true){QNfkdUfErQ = false;}
      if(XaneDcBTAH == true){XaneDcBTAH = false;}
      if(erFOnomMWc == true){erFOnomMWc = false;}
      if(xCSJrOQYHh == true){xCSJrOQYHh = false;}
      if(aJhzLwKmRQ == true){aJhzLwKmRQ = false;}
      if(kFLYMXHRxo == true){kFLYMXHRxo = false;}
      if(gTgOSUHdlo == true){gTgOSUHdlo = false;}
      if(LbMRfUKFCr == true){LbMRfUKFCr = false;}
      if(eAtGrqptwT == true){eAtGrqptwT = false;}
      if(GybSAHcTfq == true){GybSAHcTfq = false;}
      if(nfAcEJssrq == true){nfAcEJssrq = false;}
      if(NBPEJgYZVb == true){NBPEJgYZVb = false;}
      if(eNgSiMztRY == true){eNgSiMztRY = false;}
      if(rqYLDzzRCi == true){rqYLDzzRCi = false;}
      if(ywBEFEiWIT == true){ywBEFEiWIT = false;}
      if(iCxELayhtq == true){iCxELayhtq = false;}
      if(JzbTzWbEBK == true){JzbTzWbEBK = false;}
      if(gGXmdhMbMd == true){gGXmdhMbMd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BUFTMQEGPA
{ 
  void zujwIRjdLs()
  { 
      bool GrQBrquDxI = false;
      bool wLWPJkZLYP = false;
      bool IfOUHRnoUJ = false;
      bool KlROjneJET = false;
      bool fadxrimUru = false;
      bool kPgxYadusZ = false;
      bool DGinyJsHeV = false;
      bool GPHEihBQbY = false;
      bool eSwZXuFUpJ = false;
      bool KiQdPZrpyh = false;
      bool oepVoUHbNp = false;
      bool YMTUujJJPD = false;
      bool EYRULXzcoI = false;
      bool oKRsiAcakC = false;
      bool mcGzjxOwif = false;
      bool PhZucQNUJR = false;
      bool VemEAOtZku = false;
      bool HiYNQbRRkN = false;
      bool IDtIsHkWPS = false;
      bool mHQTgIpCyV = false;
      string STsgWgDrRc;
      string xArdQwYtkJ;
      string MslHyaLijr;
      string JVTzSxUsmt;
      string AcqFqBRwfJ;
      string fIOToZhlhw;
      string UTIZTbgsKT;
      string aeGpIiBfPx;
      string IPDZMAHzKs;
      string OiKqZgURlO;
      string UYkLhABXKF;
      string XBVkmFQhMT;
      string UgiRErTPQa;
      string OjtBbjdqqL;
      string yioEUNMYET;
      string QlEStnpTGp;
      string flHiqnHUIC;
      string bYpAUkqdwq;
      string fuLwKbebGn;
      string tJkBfLaFMg;
      if(STsgWgDrRc == UYkLhABXKF){GrQBrquDxI = true;}
      else if(UYkLhABXKF == STsgWgDrRc){oepVoUHbNp = true;}
      if(xArdQwYtkJ == XBVkmFQhMT){wLWPJkZLYP = true;}
      else if(XBVkmFQhMT == xArdQwYtkJ){YMTUujJJPD = true;}
      if(MslHyaLijr == UgiRErTPQa){IfOUHRnoUJ = true;}
      else if(UgiRErTPQa == MslHyaLijr){EYRULXzcoI = true;}
      if(JVTzSxUsmt == OjtBbjdqqL){KlROjneJET = true;}
      else if(OjtBbjdqqL == JVTzSxUsmt){oKRsiAcakC = true;}
      if(AcqFqBRwfJ == yioEUNMYET){fadxrimUru = true;}
      else if(yioEUNMYET == AcqFqBRwfJ){mcGzjxOwif = true;}
      if(fIOToZhlhw == QlEStnpTGp){kPgxYadusZ = true;}
      else if(QlEStnpTGp == fIOToZhlhw){PhZucQNUJR = true;}
      if(UTIZTbgsKT == flHiqnHUIC){DGinyJsHeV = true;}
      else if(flHiqnHUIC == UTIZTbgsKT){VemEAOtZku = true;}
      if(aeGpIiBfPx == bYpAUkqdwq){GPHEihBQbY = true;}
      if(IPDZMAHzKs == fuLwKbebGn){eSwZXuFUpJ = true;}
      if(OiKqZgURlO == tJkBfLaFMg){KiQdPZrpyh = true;}
      while(bYpAUkqdwq == aeGpIiBfPx){HiYNQbRRkN = true;}
      while(fuLwKbebGn == fuLwKbebGn){IDtIsHkWPS = true;}
      while(tJkBfLaFMg == tJkBfLaFMg){mHQTgIpCyV = true;}
      if(GrQBrquDxI == true){GrQBrquDxI = false;}
      if(wLWPJkZLYP == true){wLWPJkZLYP = false;}
      if(IfOUHRnoUJ == true){IfOUHRnoUJ = false;}
      if(KlROjneJET == true){KlROjneJET = false;}
      if(fadxrimUru == true){fadxrimUru = false;}
      if(kPgxYadusZ == true){kPgxYadusZ = false;}
      if(DGinyJsHeV == true){DGinyJsHeV = false;}
      if(GPHEihBQbY == true){GPHEihBQbY = false;}
      if(eSwZXuFUpJ == true){eSwZXuFUpJ = false;}
      if(KiQdPZrpyh == true){KiQdPZrpyh = false;}
      if(oepVoUHbNp == true){oepVoUHbNp = false;}
      if(YMTUujJJPD == true){YMTUujJJPD = false;}
      if(EYRULXzcoI == true){EYRULXzcoI = false;}
      if(oKRsiAcakC == true){oKRsiAcakC = false;}
      if(mcGzjxOwif == true){mcGzjxOwif = false;}
      if(PhZucQNUJR == true){PhZucQNUJR = false;}
      if(VemEAOtZku == true){VemEAOtZku = false;}
      if(HiYNQbRRkN == true){HiYNQbRRkN = false;}
      if(IDtIsHkWPS == true){IDtIsHkWPS = false;}
      if(mHQTgIpCyV == true){mHQTgIpCyV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZCNDZTLML
{ 
  void JqSsLfUhAx()
  { 
      bool NrhRtZhFJT = false;
      bool sGkSknRFjw = false;
      bool REqbhSRLsR = false;
      bool pFzyRpSzxL = false;
      bool oNwYdyuumx = false;
      bool qkhTYIAGja = false;
      bool IWMqdnGlAt = false;
      bool USIYHEHSxi = false;
      bool WWXuZFXfZI = false;
      bool pLOVCSBEtp = false;
      bool rJtsbYcJLT = false;
      bool BgJAElzQRY = false;
      bool QaLqEJDlVo = false;
      bool DCXGqNbeTA = false;
      bool bNTGHJCNQQ = false;
      bool TjmVZQxCnS = false;
      bool UpmWQyICJq = false;
      bool JTxQwCHFju = false;
      bool GoVEVSPCgZ = false;
      bool QYpBflawoI = false;
      string LVJMhnqTdL;
      string dMnexKfRzl;
      string igXTGUenSa;
      string qoAqwVuaeL;
      string yxpaHoVcbt;
      string crUzweyoFM;
      string JCBCUnMxia;
      string PEmmmlpxMR;
      string zBMXyzUAuQ;
      string XFVRBwwmGT;
      string cYsAeXFhMJ;
      string nAcnNHpcEV;
      string SLBRCKiVkq;
      string pCproaILsZ;
      string smnkbWbhEs;
      string FSikAQWaxT;
      string oiwVTkJjzl;
      string zejdbfXQoe;
      string hBRqkWSFrX;
      string EgNYkJpRQq;
      if(LVJMhnqTdL == cYsAeXFhMJ){NrhRtZhFJT = true;}
      else if(cYsAeXFhMJ == LVJMhnqTdL){rJtsbYcJLT = true;}
      if(dMnexKfRzl == nAcnNHpcEV){sGkSknRFjw = true;}
      else if(nAcnNHpcEV == dMnexKfRzl){BgJAElzQRY = true;}
      if(igXTGUenSa == SLBRCKiVkq){REqbhSRLsR = true;}
      else if(SLBRCKiVkq == igXTGUenSa){QaLqEJDlVo = true;}
      if(qoAqwVuaeL == pCproaILsZ){pFzyRpSzxL = true;}
      else if(pCproaILsZ == qoAqwVuaeL){DCXGqNbeTA = true;}
      if(yxpaHoVcbt == smnkbWbhEs){oNwYdyuumx = true;}
      else if(smnkbWbhEs == yxpaHoVcbt){bNTGHJCNQQ = true;}
      if(crUzweyoFM == FSikAQWaxT){qkhTYIAGja = true;}
      else if(FSikAQWaxT == crUzweyoFM){TjmVZQxCnS = true;}
      if(JCBCUnMxia == oiwVTkJjzl){IWMqdnGlAt = true;}
      else if(oiwVTkJjzl == JCBCUnMxia){UpmWQyICJq = true;}
      if(PEmmmlpxMR == zejdbfXQoe){USIYHEHSxi = true;}
      if(zBMXyzUAuQ == hBRqkWSFrX){WWXuZFXfZI = true;}
      if(XFVRBwwmGT == EgNYkJpRQq){pLOVCSBEtp = true;}
      while(zejdbfXQoe == PEmmmlpxMR){JTxQwCHFju = true;}
      while(hBRqkWSFrX == hBRqkWSFrX){GoVEVSPCgZ = true;}
      while(EgNYkJpRQq == EgNYkJpRQq){QYpBflawoI = true;}
      if(NrhRtZhFJT == true){NrhRtZhFJT = false;}
      if(sGkSknRFjw == true){sGkSknRFjw = false;}
      if(REqbhSRLsR == true){REqbhSRLsR = false;}
      if(pFzyRpSzxL == true){pFzyRpSzxL = false;}
      if(oNwYdyuumx == true){oNwYdyuumx = false;}
      if(qkhTYIAGja == true){qkhTYIAGja = false;}
      if(IWMqdnGlAt == true){IWMqdnGlAt = false;}
      if(USIYHEHSxi == true){USIYHEHSxi = false;}
      if(WWXuZFXfZI == true){WWXuZFXfZI = false;}
      if(pLOVCSBEtp == true){pLOVCSBEtp = false;}
      if(rJtsbYcJLT == true){rJtsbYcJLT = false;}
      if(BgJAElzQRY == true){BgJAElzQRY = false;}
      if(QaLqEJDlVo == true){QaLqEJDlVo = false;}
      if(DCXGqNbeTA == true){DCXGqNbeTA = false;}
      if(bNTGHJCNQQ == true){bNTGHJCNQQ = false;}
      if(TjmVZQxCnS == true){TjmVZQxCnS = false;}
      if(UpmWQyICJq == true){UpmWQyICJq = false;}
      if(JTxQwCHFju == true){JTxQwCHFju = false;}
      if(GoVEVSPCgZ == true){GoVEVSPCgZ = false;}
      if(QYpBflawoI == true){QYpBflawoI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JNMSWCZDCF
{ 
  void QUFhTNUWRN()
  { 
      bool tdyxRPyTtG = false;
      bool IEFGUwkwht = false;
      bool LkHGVxGdnK = false;
      bool zMbVETSAXZ = false;
      bool aTudhwNtlr = false;
      bool BUtlMIVqbT = false;
      bool IUfiGuciCB = false;
      bool dkYITrodXY = false;
      bool iMquJeRpJu = false;
      bool xbYDQFnMXl = false;
      bool SeqkOQulRT = false;
      bool TrSCkwdjYa = false;
      bool dmZGDBMVqN = false;
      bool EbGkFEUFfr = false;
      bool jfXobEIVRU = false;
      bool bDmwIfEjgN = false;
      bool EYtDPqlgwg = false;
      bool aXEfqyPjez = false;
      bool spEWlBoJcZ = false;
      bool zjXSnKkTZk = false;
      string KCcSJxqCOm;
      string uAqjeHuxbZ;
      string RJzcAocAhB;
      string uMVHJgUAZl;
      string bOsEbUFrVX;
      string WXzieBDARU;
      string TqUNrhejZx;
      string muWoxCQtAe;
      string ijdJeWMmbI;
      string dUhFRkteMs;
      string pURYjaBJkb;
      string jIzlkiNKhU;
      string UqHRTSMRXM;
      string IkhHoOSFYE;
      string VDBzXUUuTh;
      string WixrXyMzER;
      string OilXTzaqxW;
      string QHkdyRpIty;
      string xRxooYmojp;
      string BTAHomRcfX;
      if(KCcSJxqCOm == pURYjaBJkb){tdyxRPyTtG = true;}
      else if(pURYjaBJkb == KCcSJxqCOm){SeqkOQulRT = true;}
      if(uAqjeHuxbZ == jIzlkiNKhU){IEFGUwkwht = true;}
      else if(jIzlkiNKhU == uAqjeHuxbZ){TrSCkwdjYa = true;}
      if(RJzcAocAhB == UqHRTSMRXM){LkHGVxGdnK = true;}
      else if(UqHRTSMRXM == RJzcAocAhB){dmZGDBMVqN = true;}
      if(uMVHJgUAZl == IkhHoOSFYE){zMbVETSAXZ = true;}
      else if(IkhHoOSFYE == uMVHJgUAZl){EbGkFEUFfr = true;}
      if(bOsEbUFrVX == VDBzXUUuTh){aTudhwNtlr = true;}
      else if(VDBzXUUuTh == bOsEbUFrVX){jfXobEIVRU = true;}
      if(WXzieBDARU == WixrXyMzER){BUtlMIVqbT = true;}
      else if(WixrXyMzER == WXzieBDARU){bDmwIfEjgN = true;}
      if(TqUNrhejZx == OilXTzaqxW){IUfiGuciCB = true;}
      else if(OilXTzaqxW == TqUNrhejZx){EYtDPqlgwg = true;}
      if(muWoxCQtAe == QHkdyRpIty){dkYITrodXY = true;}
      if(ijdJeWMmbI == xRxooYmojp){iMquJeRpJu = true;}
      if(dUhFRkteMs == BTAHomRcfX){xbYDQFnMXl = true;}
      while(QHkdyRpIty == muWoxCQtAe){aXEfqyPjez = true;}
      while(xRxooYmojp == xRxooYmojp){spEWlBoJcZ = true;}
      while(BTAHomRcfX == BTAHomRcfX){zjXSnKkTZk = true;}
      if(tdyxRPyTtG == true){tdyxRPyTtG = false;}
      if(IEFGUwkwht == true){IEFGUwkwht = false;}
      if(LkHGVxGdnK == true){LkHGVxGdnK = false;}
      if(zMbVETSAXZ == true){zMbVETSAXZ = false;}
      if(aTudhwNtlr == true){aTudhwNtlr = false;}
      if(BUtlMIVqbT == true){BUtlMIVqbT = false;}
      if(IUfiGuciCB == true){IUfiGuciCB = false;}
      if(dkYITrodXY == true){dkYITrodXY = false;}
      if(iMquJeRpJu == true){iMquJeRpJu = false;}
      if(xbYDQFnMXl == true){xbYDQFnMXl = false;}
      if(SeqkOQulRT == true){SeqkOQulRT = false;}
      if(TrSCkwdjYa == true){TrSCkwdjYa = false;}
      if(dmZGDBMVqN == true){dmZGDBMVqN = false;}
      if(EbGkFEUFfr == true){EbGkFEUFfr = false;}
      if(jfXobEIVRU == true){jfXobEIVRU = false;}
      if(bDmwIfEjgN == true){bDmwIfEjgN = false;}
      if(EYtDPqlgwg == true){EYtDPqlgwg = false;}
      if(aXEfqyPjez == true){aXEfqyPjez = false;}
      if(spEWlBoJcZ == true){spEWlBoJcZ = false;}
      if(zjXSnKkTZk == true){zjXSnKkTZk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FASVDIDCDP
{ 
  void hZKSLSmbPr()
  { 
      bool ajeEogkkOI = false;
      bool AgzsaEwTCn = false;
      bool GFzsXsnlMj = false;
      bool McddycyCJg = false;
      bool FLLBxyToah = false;
      bool qBNfEUklfw = false;
      bool ryXeuWDUuy = false;
      bool FsJUitsyuY = false;
      bool YzLesLOxZc = false;
      bool qMVNoHngFZ = false;
      bool uzsbbxqrxJ = false;
      bool blpHXsmrkj = false;
      bool IGtRGsWwfa = false;
      bool GLsUcZFiDu = false;
      bool UVzQBEWOpu = false;
      bool UuuVRoEaUh = false;
      bool atMVDPsUdy = false;
      bool nDopOlGdPB = false;
      bool WIGkGKPWDn = false;
      bool UdNUUZJcNl = false;
      string foSXbGFBMk;
      string foJOoaIVPy;
      string pLiAaTmflp;
      string OCwNQITCgp;
      string CUaVoNanfB;
      string nGseRUGSwI;
      string TYPVVdruyg;
      string HFnYuVkMKN;
      string ryAjCIIRww;
      string BBFYWcEEzL;
      string UepythSUjw;
      string itHiQUYeTN;
      string VazBfFzPBS;
      string QgNzrMIBpU;
      string pnhAMHsWIC;
      string EZjlptfnSn;
      string hDSQeCfIqD;
      string MWozWgsyoY;
      string McGzOpwaJy;
      string fTiClmUQUK;
      if(foSXbGFBMk == UepythSUjw){ajeEogkkOI = true;}
      else if(UepythSUjw == foSXbGFBMk){uzsbbxqrxJ = true;}
      if(foJOoaIVPy == itHiQUYeTN){AgzsaEwTCn = true;}
      else if(itHiQUYeTN == foJOoaIVPy){blpHXsmrkj = true;}
      if(pLiAaTmflp == VazBfFzPBS){GFzsXsnlMj = true;}
      else if(VazBfFzPBS == pLiAaTmflp){IGtRGsWwfa = true;}
      if(OCwNQITCgp == QgNzrMIBpU){McddycyCJg = true;}
      else if(QgNzrMIBpU == OCwNQITCgp){GLsUcZFiDu = true;}
      if(CUaVoNanfB == pnhAMHsWIC){FLLBxyToah = true;}
      else if(pnhAMHsWIC == CUaVoNanfB){UVzQBEWOpu = true;}
      if(nGseRUGSwI == EZjlptfnSn){qBNfEUklfw = true;}
      else if(EZjlptfnSn == nGseRUGSwI){UuuVRoEaUh = true;}
      if(TYPVVdruyg == hDSQeCfIqD){ryXeuWDUuy = true;}
      else if(hDSQeCfIqD == TYPVVdruyg){atMVDPsUdy = true;}
      if(HFnYuVkMKN == MWozWgsyoY){FsJUitsyuY = true;}
      if(ryAjCIIRww == McGzOpwaJy){YzLesLOxZc = true;}
      if(BBFYWcEEzL == fTiClmUQUK){qMVNoHngFZ = true;}
      while(MWozWgsyoY == HFnYuVkMKN){nDopOlGdPB = true;}
      while(McGzOpwaJy == McGzOpwaJy){WIGkGKPWDn = true;}
      while(fTiClmUQUK == fTiClmUQUK){UdNUUZJcNl = true;}
      if(ajeEogkkOI == true){ajeEogkkOI = false;}
      if(AgzsaEwTCn == true){AgzsaEwTCn = false;}
      if(GFzsXsnlMj == true){GFzsXsnlMj = false;}
      if(McddycyCJg == true){McddycyCJg = false;}
      if(FLLBxyToah == true){FLLBxyToah = false;}
      if(qBNfEUklfw == true){qBNfEUklfw = false;}
      if(ryXeuWDUuy == true){ryXeuWDUuy = false;}
      if(FsJUitsyuY == true){FsJUitsyuY = false;}
      if(YzLesLOxZc == true){YzLesLOxZc = false;}
      if(qMVNoHngFZ == true){qMVNoHngFZ = false;}
      if(uzsbbxqrxJ == true){uzsbbxqrxJ = false;}
      if(blpHXsmrkj == true){blpHXsmrkj = false;}
      if(IGtRGsWwfa == true){IGtRGsWwfa = false;}
      if(GLsUcZFiDu == true){GLsUcZFiDu = false;}
      if(UVzQBEWOpu == true){UVzQBEWOpu = false;}
      if(UuuVRoEaUh == true){UuuVRoEaUh = false;}
      if(atMVDPsUdy == true){atMVDPsUdy = false;}
      if(nDopOlGdPB == true){nDopOlGdPB = false;}
      if(WIGkGKPWDn == true){WIGkGKPWDn = false;}
      if(UdNUUZJcNl == true){UdNUUZJcNl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UGLVWXZYQF
{ 
  void XJidFfMaMT()
  { 
      bool BjlNKeOMMD = false;
      bool niVrkDogJL = false;
      bool jXHOwxwwnr = false;
      bool KQeFfgshBU = false;
      bool jPCrsntUue = false;
      bool HynESdcXQN = false;
      bool hRYUrWEQME = false;
      bool KGenaTVOUH = false;
      bool CbBIjMcZlC = false;
      bool DURnlRqgzW = false;
      bool jdIqTASzcy = false;
      bool HOCIKGQPjf = false;
      bool tddJApoqCI = false;
      bool cnOyXYTKnj = false;
      bool scwmtnRIcf = false;
      bool BaxTcFAypd = false;
      bool LaxUVTAEkl = false;
      bool mGbAlQhpPL = false;
      bool XfOVHBpuVR = false;
      bool YUTKXSebRa = false;
      string bNJJInYgrI;
      string XHFUrGhDUo;
      string oPYUQoZshm;
      string qGcMDeVGWy;
      string PzdmXFpXJr;
      string XuCWnLnorT;
      string NezEQRdrRN;
      string kbgWYollwL;
      string yCioOuDGYq;
      string qfOCkjAYVG;
      string axFwHwOeyy;
      string ZCrfUKwJoU;
      string NXTaVFNdln;
      string oMPojBwmhS;
      string gXHZQnnhhZ;
      string npjAsDceZC;
      string iksJJNmDuT;
      string OJbWnoPtJh;
      string QewMzycOwg;
      string XQMfiweyPD;
      if(bNJJInYgrI == axFwHwOeyy){BjlNKeOMMD = true;}
      else if(axFwHwOeyy == bNJJInYgrI){jdIqTASzcy = true;}
      if(XHFUrGhDUo == ZCrfUKwJoU){niVrkDogJL = true;}
      else if(ZCrfUKwJoU == XHFUrGhDUo){HOCIKGQPjf = true;}
      if(oPYUQoZshm == NXTaVFNdln){jXHOwxwwnr = true;}
      else if(NXTaVFNdln == oPYUQoZshm){tddJApoqCI = true;}
      if(qGcMDeVGWy == oMPojBwmhS){KQeFfgshBU = true;}
      else if(oMPojBwmhS == qGcMDeVGWy){cnOyXYTKnj = true;}
      if(PzdmXFpXJr == gXHZQnnhhZ){jPCrsntUue = true;}
      else if(gXHZQnnhhZ == PzdmXFpXJr){scwmtnRIcf = true;}
      if(XuCWnLnorT == npjAsDceZC){HynESdcXQN = true;}
      else if(npjAsDceZC == XuCWnLnorT){BaxTcFAypd = true;}
      if(NezEQRdrRN == iksJJNmDuT){hRYUrWEQME = true;}
      else if(iksJJNmDuT == NezEQRdrRN){LaxUVTAEkl = true;}
      if(kbgWYollwL == OJbWnoPtJh){KGenaTVOUH = true;}
      if(yCioOuDGYq == QewMzycOwg){CbBIjMcZlC = true;}
      if(qfOCkjAYVG == XQMfiweyPD){DURnlRqgzW = true;}
      while(OJbWnoPtJh == kbgWYollwL){mGbAlQhpPL = true;}
      while(QewMzycOwg == QewMzycOwg){XfOVHBpuVR = true;}
      while(XQMfiweyPD == XQMfiweyPD){YUTKXSebRa = true;}
      if(BjlNKeOMMD == true){BjlNKeOMMD = false;}
      if(niVrkDogJL == true){niVrkDogJL = false;}
      if(jXHOwxwwnr == true){jXHOwxwwnr = false;}
      if(KQeFfgshBU == true){KQeFfgshBU = false;}
      if(jPCrsntUue == true){jPCrsntUue = false;}
      if(HynESdcXQN == true){HynESdcXQN = false;}
      if(hRYUrWEQME == true){hRYUrWEQME = false;}
      if(KGenaTVOUH == true){KGenaTVOUH = false;}
      if(CbBIjMcZlC == true){CbBIjMcZlC = false;}
      if(DURnlRqgzW == true){DURnlRqgzW = false;}
      if(jdIqTASzcy == true){jdIqTASzcy = false;}
      if(HOCIKGQPjf == true){HOCIKGQPjf = false;}
      if(tddJApoqCI == true){tddJApoqCI = false;}
      if(cnOyXYTKnj == true){cnOyXYTKnj = false;}
      if(scwmtnRIcf == true){scwmtnRIcf = false;}
      if(BaxTcFAypd == true){BaxTcFAypd = false;}
      if(LaxUVTAEkl == true){LaxUVTAEkl = false;}
      if(mGbAlQhpPL == true){mGbAlQhpPL = false;}
      if(XfOVHBpuVR == true){XfOVHBpuVR = false;}
      if(YUTKXSebRa == true){YUTKXSebRa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJDZHAWCEW
{ 
  void gQdWmUipxU()
  { 
      bool CPPncMCCRW = false;
      bool eyCzbiWeIf = false;
      bool VTldVZUNMp = false;
      bool mzWebNIaUm = false;
      bool nUaPzoOGSE = false;
      bool PGwVSidkRD = false;
      bool ropbjfbXWN = false;
      bool ZuKVrBrVdg = false;
      bool KNtHafDAMs = false;
      bool iWJQuzezfT = false;
      bool MqjEdTwadR = false;
      bool pIGkrdthAD = false;
      bool baKdeDlsZr = false;
      bool WsoKTSdpdH = false;
      bool jcWuCaPYYQ = false;
      bool EwycrlgFZa = false;
      bool hDAkuxSwQY = false;
      bool ADEsTzEPaD = false;
      bool mNTJnZtMRh = false;
      bool lXPCYfclAF = false;
      string VoZyltHCDZ;
      string SebJKwptRF;
      string TYExEnyoTF;
      string BWykBBbrPy;
      string RBxUekKigs;
      string DdOkpwkcsx;
      string wShyYufqIJ;
      string TxeTmSajST;
      string dPHZBXIMtE;
      string PzzRBzSzwi;
      string ESaXZGztyW;
      string VAJYTgKIwB;
      string mTwDsTyMSn;
      string AanjPKojAu;
      string XNOXiOpZxU;
      string nKDuwjWWdF;
      string HlbJVtMZJJ;
      string qaHAcYEXTd;
      string dYPxApXsme;
      string mRGtnlkFBo;
      if(VoZyltHCDZ == ESaXZGztyW){CPPncMCCRW = true;}
      else if(ESaXZGztyW == VoZyltHCDZ){MqjEdTwadR = true;}
      if(SebJKwptRF == VAJYTgKIwB){eyCzbiWeIf = true;}
      else if(VAJYTgKIwB == SebJKwptRF){pIGkrdthAD = true;}
      if(TYExEnyoTF == mTwDsTyMSn){VTldVZUNMp = true;}
      else if(mTwDsTyMSn == TYExEnyoTF){baKdeDlsZr = true;}
      if(BWykBBbrPy == AanjPKojAu){mzWebNIaUm = true;}
      else if(AanjPKojAu == BWykBBbrPy){WsoKTSdpdH = true;}
      if(RBxUekKigs == XNOXiOpZxU){nUaPzoOGSE = true;}
      else if(XNOXiOpZxU == RBxUekKigs){jcWuCaPYYQ = true;}
      if(DdOkpwkcsx == nKDuwjWWdF){PGwVSidkRD = true;}
      else if(nKDuwjWWdF == DdOkpwkcsx){EwycrlgFZa = true;}
      if(wShyYufqIJ == HlbJVtMZJJ){ropbjfbXWN = true;}
      else if(HlbJVtMZJJ == wShyYufqIJ){hDAkuxSwQY = true;}
      if(TxeTmSajST == qaHAcYEXTd){ZuKVrBrVdg = true;}
      if(dPHZBXIMtE == dYPxApXsme){KNtHafDAMs = true;}
      if(PzzRBzSzwi == mRGtnlkFBo){iWJQuzezfT = true;}
      while(qaHAcYEXTd == TxeTmSajST){ADEsTzEPaD = true;}
      while(dYPxApXsme == dYPxApXsme){mNTJnZtMRh = true;}
      while(mRGtnlkFBo == mRGtnlkFBo){lXPCYfclAF = true;}
      if(CPPncMCCRW == true){CPPncMCCRW = false;}
      if(eyCzbiWeIf == true){eyCzbiWeIf = false;}
      if(VTldVZUNMp == true){VTldVZUNMp = false;}
      if(mzWebNIaUm == true){mzWebNIaUm = false;}
      if(nUaPzoOGSE == true){nUaPzoOGSE = false;}
      if(PGwVSidkRD == true){PGwVSidkRD = false;}
      if(ropbjfbXWN == true){ropbjfbXWN = false;}
      if(ZuKVrBrVdg == true){ZuKVrBrVdg = false;}
      if(KNtHafDAMs == true){KNtHafDAMs = false;}
      if(iWJQuzezfT == true){iWJQuzezfT = false;}
      if(MqjEdTwadR == true){MqjEdTwadR = false;}
      if(pIGkrdthAD == true){pIGkrdthAD = false;}
      if(baKdeDlsZr == true){baKdeDlsZr = false;}
      if(WsoKTSdpdH == true){WsoKTSdpdH = false;}
      if(jcWuCaPYYQ == true){jcWuCaPYYQ = false;}
      if(EwycrlgFZa == true){EwycrlgFZa = false;}
      if(hDAkuxSwQY == true){hDAkuxSwQY = false;}
      if(ADEsTzEPaD == true){ADEsTzEPaD = false;}
      if(mNTJnZtMRh == true){mNTJnZtMRh = false;}
      if(lXPCYfclAF == true){lXPCYfclAF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SFNHAKFDAC
{ 
  void XfuNwXZLGP()
  { 
      bool dVmcBJySgt = false;
      bool YiPifcSwtU = false;
      bool GuwkNaedIV = false;
      bool PCNmgYcxDT = false;
      bool jojuywReNf = false;
      bool gkDWJiZCPZ = false;
      bool eTKLeWUbBH = false;
      bool zUrakQLAmQ = false;
      bool JzQcndzqdy = false;
      bool yahcnPeXQa = false;
      bool apcFfMrbkr = false;
      bool WYOyQeDhWB = false;
      bool WdxDIYlPlV = false;
      bool lmjLoTWKwb = false;
      bool lWFkaZMjMI = false;
      bool MwAPExrYxH = false;
      bool ZcoPFjnCIx = false;
      bool IrktOzYLci = false;
      bool LBCdIolUHr = false;
      bool bxNnCIgpfp = false;
      string FLuyTigHWC;
      string pRdTOpYjNr;
      string btuRuyXbOm;
      string GFRbynHHDd;
      string IIrMKypWWN;
      string aWCoZKPcDU;
      string KFsiwjACVa;
      string hRfjjSCiHw;
      string HBEAMiDbBm;
      string XdDiTDOIPZ;
      string ynBweIpSFG;
      string IfUGMIAsWN;
      string gXAhCDNxPg;
      string DtThxTAHUE;
      string rjWteqIwVK;
      string CVkCranSta;
      string tsCYDOMmIs;
      string IrXSUxBFDL;
      string uQaFdhIRpW;
      string egNsJzhyqP;
      if(FLuyTigHWC == ynBweIpSFG){dVmcBJySgt = true;}
      else if(ynBweIpSFG == FLuyTigHWC){apcFfMrbkr = true;}
      if(pRdTOpYjNr == IfUGMIAsWN){YiPifcSwtU = true;}
      else if(IfUGMIAsWN == pRdTOpYjNr){WYOyQeDhWB = true;}
      if(btuRuyXbOm == gXAhCDNxPg){GuwkNaedIV = true;}
      else if(gXAhCDNxPg == btuRuyXbOm){WdxDIYlPlV = true;}
      if(GFRbynHHDd == DtThxTAHUE){PCNmgYcxDT = true;}
      else if(DtThxTAHUE == GFRbynHHDd){lmjLoTWKwb = true;}
      if(IIrMKypWWN == rjWteqIwVK){jojuywReNf = true;}
      else if(rjWteqIwVK == IIrMKypWWN){lWFkaZMjMI = true;}
      if(aWCoZKPcDU == CVkCranSta){gkDWJiZCPZ = true;}
      else if(CVkCranSta == aWCoZKPcDU){MwAPExrYxH = true;}
      if(KFsiwjACVa == tsCYDOMmIs){eTKLeWUbBH = true;}
      else if(tsCYDOMmIs == KFsiwjACVa){ZcoPFjnCIx = true;}
      if(hRfjjSCiHw == IrXSUxBFDL){zUrakQLAmQ = true;}
      if(HBEAMiDbBm == uQaFdhIRpW){JzQcndzqdy = true;}
      if(XdDiTDOIPZ == egNsJzhyqP){yahcnPeXQa = true;}
      while(IrXSUxBFDL == hRfjjSCiHw){IrktOzYLci = true;}
      while(uQaFdhIRpW == uQaFdhIRpW){LBCdIolUHr = true;}
      while(egNsJzhyqP == egNsJzhyqP){bxNnCIgpfp = true;}
      if(dVmcBJySgt == true){dVmcBJySgt = false;}
      if(YiPifcSwtU == true){YiPifcSwtU = false;}
      if(GuwkNaedIV == true){GuwkNaedIV = false;}
      if(PCNmgYcxDT == true){PCNmgYcxDT = false;}
      if(jojuywReNf == true){jojuywReNf = false;}
      if(gkDWJiZCPZ == true){gkDWJiZCPZ = false;}
      if(eTKLeWUbBH == true){eTKLeWUbBH = false;}
      if(zUrakQLAmQ == true){zUrakQLAmQ = false;}
      if(JzQcndzqdy == true){JzQcndzqdy = false;}
      if(yahcnPeXQa == true){yahcnPeXQa = false;}
      if(apcFfMrbkr == true){apcFfMrbkr = false;}
      if(WYOyQeDhWB == true){WYOyQeDhWB = false;}
      if(WdxDIYlPlV == true){WdxDIYlPlV = false;}
      if(lmjLoTWKwb == true){lmjLoTWKwb = false;}
      if(lWFkaZMjMI == true){lWFkaZMjMI = false;}
      if(MwAPExrYxH == true){MwAPExrYxH = false;}
      if(ZcoPFjnCIx == true){ZcoPFjnCIx = false;}
      if(IrktOzYLci == true){IrktOzYLci = false;}
      if(LBCdIolUHr == true){LBCdIolUHr = false;}
      if(bxNnCIgpfp == true){bxNnCIgpfp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KWBVSUWYYI
{ 
  void MWZDhEmEzU()
  { 
      bool DUPnFnTBWq = false;
      bool yKyzYFZdoc = false;
      bool cQIZsnokra = false;
      bool APdVAdahkP = false;
      bool kGiJFoxmzk = false;
      bool EibQtmMotQ = false;
      bool ziJwpifcyt = false;
      bool eqrYqVhyUE = false;
      bool qClGWRmNbM = false;
      bool RknTQCxmTV = false;
      bool JUnEGMpCYX = false;
      bool FOUpZwxCYY = false;
      bool uSAkctDYIo = false;
      bool YteyuWNgAJ = false;
      bool bknDHDPytT = false;
      bool EtNtapTDbM = false;
      bool JRsjzKiWuD = false;
      bool iPCPxJdwdY = false;
      bool dEdojdgjWE = false;
      bool CKFnzJqDEw = false;
      string QpwxjUzcTp;
      string EqYCYjFIOQ;
      string GoAdirOLXh;
      string jcedOSMSyT;
      string SnqMZfcgnZ;
      string RKuJjbpSOq;
      string FmElFbLtnG;
      string WmKtxSymDC;
      string PgWyQZhVtl;
      string bsEHNeiFGy;
      string UhshCdzALR;
      string dCOLaXQFUe;
      string tpABddiDfS;
      string irgFhhnowl;
      string agJbIZdrgp;
      string OdjaEdhrDX;
      string uwTshkVJcs;
      string jaJiEMfXsE;
      string zpVpDFIFBD;
      string zwlXpdMQsW;
      if(QpwxjUzcTp == UhshCdzALR){DUPnFnTBWq = true;}
      else if(UhshCdzALR == QpwxjUzcTp){JUnEGMpCYX = true;}
      if(EqYCYjFIOQ == dCOLaXQFUe){yKyzYFZdoc = true;}
      else if(dCOLaXQFUe == EqYCYjFIOQ){FOUpZwxCYY = true;}
      if(GoAdirOLXh == tpABddiDfS){cQIZsnokra = true;}
      else if(tpABddiDfS == GoAdirOLXh){uSAkctDYIo = true;}
      if(jcedOSMSyT == irgFhhnowl){APdVAdahkP = true;}
      else if(irgFhhnowl == jcedOSMSyT){YteyuWNgAJ = true;}
      if(SnqMZfcgnZ == agJbIZdrgp){kGiJFoxmzk = true;}
      else if(agJbIZdrgp == SnqMZfcgnZ){bknDHDPytT = true;}
      if(RKuJjbpSOq == OdjaEdhrDX){EibQtmMotQ = true;}
      else if(OdjaEdhrDX == RKuJjbpSOq){EtNtapTDbM = true;}
      if(FmElFbLtnG == uwTshkVJcs){ziJwpifcyt = true;}
      else if(uwTshkVJcs == FmElFbLtnG){JRsjzKiWuD = true;}
      if(WmKtxSymDC == jaJiEMfXsE){eqrYqVhyUE = true;}
      if(PgWyQZhVtl == zpVpDFIFBD){qClGWRmNbM = true;}
      if(bsEHNeiFGy == zwlXpdMQsW){RknTQCxmTV = true;}
      while(jaJiEMfXsE == WmKtxSymDC){iPCPxJdwdY = true;}
      while(zpVpDFIFBD == zpVpDFIFBD){dEdojdgjWE = true;}
      while(zwlXpdMQsW == zwlXpdMQsW){CKFnzJqDEw = true;}
      if(DUPnFnTBWq == true){DUPnFnTBWq = false;}
      if(yKyzYFZdoc == true){yKyzYFZdoc = false;}
      if(cQIZsnokra == true){cQIZsnokra = false;}
      if(APdVAdahkP == true){APdVAdahkP = false;}
      if(kGiJFoxmzk == true){kGiJFoxmzk = false;}
      if(EibQtmMotQ == true){EibQtmMotQ = false;}
      if(ziJwpifcyt == true){ziJwpifcyt = false;}
      if(eqrYqVhyUE == true){eqrYqVhyUE = false;}
      if(qClGWRmNbM == true){qClGWRmNbM = false;}
      if(RknTQCxmTV == true){RknTQCxmTV = false;}
      if(JUnEGMpCYX == true){JUnEGMpCYX = false;}
      if(FOUpZwxCYY == true){FOUpZwxCYY = false;}
      if(uSAkctDYIo == true){uSAkctDYIo = false;}
      if(YteyuWNgAJ == true){YteyuWNgAJ = false;}
      if(bknDHDPytT == true){bknDHDPytT = false;}
      if(EtNtapTDbM == true){EtNtapTDbM = false;}
      if(JRsjzKiWuD == true){JRsjzKiWuD = false;}
      if(iPCPxJdwdY == true){iPCPxJdwdY = false;}
      if(dEdojdgjWE == true){dEdojdgjWE = false;}
      if(CKFnzJqDEw == true){CKFnzJqDEw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SNRHOXVRSA
{ 
  void egXAOypVAs()
  { 
      bool ZrUcnGApVU = false;
      bool mugXShrCmg = false;
      bool QUBnjlcNwE = false;
      bool QStokLhPuG = false;
      bool HJpDYPTPzf = false;
      bool mPAjwEpgrC = false;
      bool dlsQDTBrlG = false;
      bool AcGfYGdyPU = false;
      bool RMOPRBSKsf = false;
      bool VAWsbVPYzE = false;
      bool NbcsfJITKo = false;
      bool ZrRWjRXdyC = false;
      bool AqzFkzFNED = false;
      bool qFzKHpiUjH = false;
      bool rzADFchzIK = false;
      bool xlZwDVcXHf = false;
      bool EuPGyUsGPt = false;
      bool hCtqKBquzH = false;
      bool RFEsGEeCHk = false;
      bool NLMDDwjsFk = false;
      string NVlrHJMNfA;
      string ycruwmStab;
      string mlAJwFnyNN;
      string eGKwUZxUnS;
      string bzbblERoXh;
      string FJEkPaVbwB;
      string VOzRVqSwZW;
      string pxFHzmKXXq;
      string nzZfIUBYft;
      string EUYmxNAKGt;
      string lVOBqIEwlb;
      string QyDENWoTJA;
      string osPfRVXSKk;
      string mARdERjXnz;
      string QFmEdGRUYa;
      string XfAFFsGijV;
      string kklAnQgZzu;
      string lQfKjjFKCL;
      string DCsjNHzLXL;
      string LAnROeSmQM;
      if(NVlrHJMNfA == lVOBqIEwlb){ZrUcnGApVU = true;}
      else if(lVOBqIEwlb == NVlrHJMNfA){NbcsfJITKo = true;}
      if(ycruwmStab == QyDENWoTJA){mugXShrCmg = true;}
      else if(QyDENWoTJA == ycruwmStab){ZrRWjRXdyC = true;}
      if(mlAJwFnyNN == osPfRVXSKk){QUBnjlcNwE = true;}
      else if(osPfRVXSKk == mlAJwFnyNN){AqzFkzFNED = true;}
      if(eGKwUZxUnS == mARdERjXnz){QStokLhPuG = true;}
      else if(mARdERjXnz == eGKwUZxUnS){qFzKHpiUjH = true;}
      if(bzbblERoXh == QFmEdGRUYa){HJpDYPTPzf = true;}
      else if(QFmEdGRUYa == bzbblERoXh){rzADFchzIK = true;}
      if(FJEkPaVbwB == XfAFFsGijV){mPAjwEpgrC = true;}
      else if(XfAFFsGijV == FJEkPaVbwB){xlZwDVcXHf = true;}
      if(VOzRVqSwZW == kklAnQgZzu){dlsQDTBrlG = true;}
      else if(kklAnQgZzu == VOzRVqSwZW){EuPGyUsGPt = true;}
      if(pxFHzmKXXq == lQfKjjFKCL){AcGfYGdyPU = true;}
      if(nzZfIUBYft == DCsjNHzLXL){RMOPRBSKsf = true;}
      if(EUYmxNAKGt == LAnROeSmQM){VAWsbVPYzE = true;}
      while(lQfKjjFKCL == pxFHzmKXXq){hCtqKBquzH = true;}
      while(DCsjNHzLXL == DCsjNHzLXL){RFEsGEeCHk = true;}
      while(LAnROeSmQM == LAnROeSmQM){NLMDDwjsFk = true;}
      if(ZrUcnGApVU == true){ZrUcnGApVU = false;}
      if(mugXShrCmg == true){mugXShrCmg = false;}
      if(QUBnjlcNwE == true){QUBnjlcNwE = false;}
      if(QStokLhPuG == true){QStokLhPuG = false;}
      if(HJpDYPTPzf == true){HJpDYPTPzf = false;}
      if(mPAjwEpgrC == true){mPAjwEpgrC = false;}
      if(dlsQDTBrlG == true){dlsQDTBrlG = false;}
      if(AcGfYGdyPU == true){AcGfYGdyPU = false;}
      if(RMOPRBSKsf == true){RMOPRBSKsf = false;}
      if(VAWsbVPYzE == true){VAWsbVPYzE = false;}
      if(NbcsfJITKo == true){NbcsfJITKo = false;}
      if(ZrRWjRXdyC == true){ZrRWjRXdyC = false;}
      if(AqzFkzFNED == true){AqzFkzFNED = false;}
      if(qFzKHpiUjH == true){qFzKHpiUjH = false;}
      if(rzADFchzIK == true){rzADFchzIK = false;}
      if(xlZwDVcXHf == true){xlZwDVcXHf = false;}
      if(EuPGyUsGPt == true){EuPGyUsGPt = false;}
      if(hCtqKBquzH == true){hCtqKBquzH = false;}
      if(RFEsGEeCHk == true){RFEsGEeCHk = false;}
      if(NLMDDwjsFk == true){NLMDDwjsFk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YAFPBQPNMU
{ 
  void dViQATmGHK()
  { 
      bool pANySOOtoX = false;
      bool FdFVUziMIO = false;
      bool EuyniMHNME = false;
      bool ufjySdFVCa = false;
      bool hRkmGpZGtf = false;
      bool HtDpQtBYOF = false;
      bool HAgjbZtHCp = false;
      bool tNJgglJLhr = false;
      bool lASgwBbsgX = false;
      bool cfHwTgjBKf = false;
      bool wSEDltjVJd = false;
      bool kpqVSGgAna = false;
      bool yBZdMNFMNA = false;
      bool CIACwTwPtB = false;
      bool QFjCmmokcM = false;
      bool zjNjhtrZpY = false;
      bool nWIIbcooYz = false;
      bool KRFlKsQWqZ = false;
      bool XUjBBRtQTB = false;
      bool aVYVNsxaaK = false;
      string CxCYWLQeGa;
      string yJzEbtAXoR;
      string rGbHFMZTlL;
      string OGLdxNzsFx;
      string mZaoGwwmNi;
      string JrFPPuUuTJ;
      string lxstMqxUHN;
      string tHRrdSfmAI;
      string QlGDBVBuOB;
      string sEYuLpffbP;
      string zafzoCZNlx;
      string PgtKszqpsq;
      string pBGFUohWfn;
      string lzLkJoGGNz;
      string umJQlLKOCL;
      string ypmkZxTZdz;
      string TDgxKQVJAE;
      string sjbswCrpTI;
      string eTTUowLaKL;
      string UfcOfqGLFV;
      if(CxCYWLQeGa == zafzoCZNlx){pANySOOtoX = true;}
      else if(zafzoCZNlx == CxCYWLQeGa){wSEDltjVJd = true;}
      if(yJzEbtAXoR == PgtKszqpsq){FdFVUziMIO = true;}
      else if(PgtKszqpsq == yJzEbtAXoR){kpqVSGgAna = true;}
      if(rGbHFMZTlL == pBGFUohWfn){EuyniMHNME = true;}
      else if(pBGFUohWfn == rGbHFMZTlL){yBZdMNFMNA = true;}
      if(OGLdxNzsFx == lzLkJoGGNz){ufjySdFVCa = true;}
      else if(lzLkJoGGNz == OGLdxNzsFx){CIACwTwPtB = true;}
      if(mZaoGwwmNi == umJQlLKOCL){hRkmGpZGtf = true;}
      else if(umJQlLKOCL == mZaoGwwmNi){QFjCmmokcM = true;}
      if(JrFPPuUuTJ == ypmkZxTZdz){HtDpQtBYOF = true;}
      else if(ypmkZxTZdz == JrFPPuUuTJ){zjNjhtrZpY = true;}
      if(lxstMqxUHN == TDgxKQVJAE){HAgjbZtHCp = true;}
      else if(TDgxKQVJAE == lxstMqxUHN){nWIIbcooYz = true;}
      if(tHRrdSfmAI == sjbswCrpTI){tNJgglJLhr = true;}
      if(QlGDBVBuOB == eTTUowLaKL){lASgwBbsgX = true;}
      if(sEYuLpffbP == UfcOfqGLFV){cfHwTgjBKf = true;}
      while(sjbswCrpTI == tHRrdSfmAI){KRFlKsQWqZ = true;}
      while(eTTUowLaKL == eTTUowLaKL){XUjBBRtQTB = true;}
      while(UfcOfqGLFV == UfcOfqGLFV){aVYVNsxaaK = true;}
      if(pANySOOtoX == true){pANySOOtoX = false;}
      if(FdFVUziMIO == true){FdFVUziMIO = false;}
      if(EuyniMHNME == true){EuyniMHNME = false;}
      if(ufjySdFVCa == true){ufjySdFVCa = false;}
      if(hRkmGpZGtf == true){hRkmGpZGtf = false;}
      if(HtDpQtBYOF == true){HtDpQtBYOF = false;}
      if(HAgjbZtHCp == true){HAgjbZtHCp = false;}
      if(tNJgglJLhr == true){tNJgglJLhr = false;}
      if(lASgwBbsgX == true){lASgwBbsgX = false;}
      if(cfHwTgjBKf == true){cfHwTgjBKf = false;}
      if(wSEDltjVJd == true){wSEDltjVJd = false;}
      if(kpqVSGgAna == true){kpqVSGgAna = false;}
      if(yBZdMNFMNA == true){yBZdMNFMNA = false;}
      if(CIACwTwPtB == true){CIACwTwPtB = false;}
      if(QFjCmmokcM == true){QFjCmmokcM = false;}
      if(zjNjhtrZpY == true){zjNjhtrZpY = false;}
      if(nWIIbcooYz == true){nWIIbcooYz = false;}
      if(KRFlKsQWqZ == true){KRFlKsQWqZ = false;}
      if(XUjBBRtQTB == true){XUjBBRtQTB = false;}
      if(aVYVNsxaaK == true){aVYVNsxaaK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JLBGMJPSCB
{ 
  void ZMHisDICOz()
  { 
      bool iDuRpDOUwU = false;
      bool BMzLghPmqA = false;
      bool UldRfLioSY = false;
      bool NccYpAwWBK = false;
      bool WxMnqICMhA = false;
      bool sWVXNxYcle = false;
      bool UYBXHXiaUf = false;
      bool lskfdWYpaW = false;
      bool JVHReqHEKs = false;
      bool aSjWpxuogS = false;
      bool YaqBOAkptp = false;
      bool XiCPVyRjrQ = false;
      bool QeQbFSIOof = false;
      bool biJIxheFCe = false;
      bool FRKTUrQUBr = false;
      bool fLxPCtKOww = false;
      bool rWAOOoYtRm = false;
      bool TMgNKyTxHN = false;
      bool CnNxzPksFD = false;
      bool XPIGmiQwEe = false;
      string aJrTBUKVeW;
      string wZoOcKbNQg;
      string jhLsnEDzms;
      string ARVXoMgeBr;
      string jGPxjDrJEI;
      string QZAaUsyzex;
      string QKikWdDQZQ;
      string cwMXxcROIj;
      string LsuebaRuDw;
      string NhAEbYXdZG;
      string AbjmeUMbcq;
      string ajptkWOEIu;
      string MINcDuwIwX;
      string FnnCjjJIzH;
      string NoRLVdqFSE;
      string JTVesrOHjj;
      string YEeElmunKB;
      string NGEBhXpBHY;
      string DqorNkRJJr;
      string UCXOhIJMYi;
      if(aJrTBUKVeW == AbjmeUMbcq){iDuRpDOUwU = true;}
      else if(AbjmeUMbcq == aJrTBUKVeW){YaqBOAkptp = true;}
      if(wZoOcKbNQg == ajptkWOEIu){BMzLghPmqA = true;}
      else if(ajptkWOEIu == wZoOcKbNQg){XiCPVyRjrQ = true;}
      if(jhLsnEDzms == MINcDuwIwX){UldRfLioSY = true;}
      else if(MINcDuwIwX == jhLsnEDzms){QeQbFSIOof = true;}
      if(ARVXoMgeBr == FnnCjjJIzH){NccYpAwWBK = true;}
      else if(FnnCjjJIzH == ARVXoMgeBr){biJIxheFCe = true;}
      if(jGPxjDrJEI == NoRLVdqFSE){WxMnqICMhA = true;}
      else if(NoRLVdqFSE == jGPxjDrJEI){FRKTUrQUBr = true;}
      if(QZAaUsyzex == JTVesrOHjj){sWVXNxYcle = true;}
      else if(JTVesrOHjj == QZAaUsyzex){fLxPCtKOww = true;}
      if(QKikWdDQZQ == YEeElmunKB){UYBXHXiaUf = true;}
      else if(YEeElmunKB == QKikWdDQZQ){rWAOOoYtRm = true;}
      if(cwMXxcROIj == NGEBhXpBHY){lskfdWYpaW = true;}
      if(LsuebaRuDw == DqorNkRJJr){JVHReqHEKs = true;}
      if(NhAEbYXdZG == UCXOhIJMYi){aSjWpxuogS = true;}
      while(NGEBhXpBHY == cwMXxcROIj){TMgNKyTxHN = true;}
      while(DqorNkRJJr == DqorNkRJJr){CnNxzPksFD = true;}
      while(UCXOhIJMYi == UCXOhIJMYi){XPIGmiQwEe = true;}
      if(iDuRpDOUwU == true){iDuRpDOUwU = false;}
      if(BMzLghPmqA == true){BMzLghPmqA = false;}
      if(UldRfLioSY == true){UldRfLioSY = false;}
      if(NccYpAwWBK == true){NccYpAwWBK = false;}
      if(WxMnqICMhA == true){WxMnqICMhA = false;}
      if(sWVXNxYcle == true){sWVXNxYcle = false;}
      if(UYBXHXiaUf == true){UYBXHXiaUf = false;}
      if(lskfdWYpaW == true){lskfdWYpaW = false;}
      if(JVHReqHEKs == true){JVHReqHEKs = false;}
      if(aSjWpxuogS == true){aSjWpxuogS = false;}
      if(YaqBOAkptp == true){YaqBOAkptp = false;}
      if(XiCPVyRjrQ == true){XiCPVyRjrQ = false;}
      if(QeQbFSIOof == true){QeQbFSIOof = false;}
      if(biJIxheFCe == true){biJIxheFCe = false;}
      if(FRKTUrQUBr == true){FRKTUrQUBr = false;}
      if(fLxPCtKOww == true){fLxPCtKOww = false;}
      if(rWAOOoYtRm == true){rWAOOoYtRm = false;}
      if(TMgNKyTxHN == true){TMgNKyTxHN = false;}
      if(CnNxzPksFD == true){CnNxzPksFD = false;}
      if(XPIGmiQwEe == true){XPIGmiQwEe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JIVEICEBPW
{ 
  void sWukhUNENL()
  { 
      bool zKnGbksPWB = false;
      bool AdQpCaTKii = false;
      bool wueOQWsCob = false;
      bool VMPojIQGim = false;
      bool UwfePpOILL = false;
      bool UAKPtEeYoE = false;
      bool qpZuemObFs = false;
      bool JMauOAPAza = false;
      bool IkqdGVCztf = false;
      bool cqReueVjzb = false;
      bool alCRBHYOBt = false;
      bool neYNuGzuoJ = false;
      bool kPgZPSuwzi = false;
      bool deAXAVhYcy = false;
      bool xmxzqyRDio = false;
      bool eZtpqLEcCh = false;
      bool MbORPJdBNY = false;
      bool XZRqLxRhhR = false;
      bool AqNKDDjKgn = false;
      bool RFVukUXejh = false;
      string oFwwQLHfhp;
      string FjyDUTyCso;
      string hnuKMAaKmS;
      string rASULyhFGt;
      string rBzazdiUdt;
      string xhJHCAKljQ;
      string kxrOyEQdqW;
      string ksuyxgnTKh;
      string RFfrVJqKRL;
      string nwUpJtJkcu;
      string MEcHJDlKKU;
      string LpaByeQzsn;
      string MGLfhnYEoC;
      string XDqOVMbXiR;
      string WfAxzyVTqd;
      string dJqniGsxZU;
      string ehVHxIyLek;
      string CrQbQgFOfj;
      string SENKYNLDfP;
      string TeyNloKszq;
      if(oFwwQLHfhp == MEcHJDlKKU){zKnGbksPWB = true;}
      else if(MEcHJDlKKU == oFwwQLHfhp){alCRBHYOBt = true;}
      if(FjyDUTyCso == LpaByeQzsn){AdQpCaTKii = true;}
      else if(LpaByeQzsn == FjyDUTyCso){neYNuGzuoJ = true;}
      if(hnuKMAaKmS == MGLfhnYEoC){wueOQWsCob = true;}
      else if(MGLfhnYEoC == hnuKMAaKmS){kPgZPSuwzi = true;}
      if(rASULyhFGt == XDqOVMbXiR){VMPojIQGim = true;}
      else if(XDqOVMbXiR == rASULyhFGt){deAXAVhYcy = true;}
      if(rBzazdiUdt == WfAxzyVTqd){UwfePpOILL = true;}
      else if(WfAxzyVTqd == rBzazdiUdt){xmxzqyRDio = true;}
      if(xhJHCAKljQ == dJqniGsxZU){UAKPtEeYoE = true;}
      else if(dJqniGsxZU == xhJHCAKljQ){eZtpqLEcCh = true;}
      if(kxrOyEQdqW == ehVHxIyLek){qpZuemObFs = true;}
      else if(ehVHxIyLek == kxrOyEQdqW){MbORPJdBNY = true;}
      if(ksuyxgnTKh == CrQbQgFOfj){JMauOAPAza = true;}
      if(RFfrVJqKRL == SENKYNLDfP){IkqdGVCztf = true;}
      if(nwUpJtJkcu == TeyNloKszq){cqReueVjzb = true;}
      while(CrQbQgFOfj == ksuyxgnTKh){XZRqLxRhhR = true;}
      while(SENKYNLDfP == SENKYNLDfP){AqNKDDjKgn = true;}
      while(TeyNloKszq == TeyNloKszq){RFVukUXejh = true;}
      if(zKnGbksPWB == true){zKnGbksPWB = false;}
      if(AdQpCaTKii == true){AdQpCaTKii = false;}
      if(wueOQWsCob == true){wueOQWsCob = false;}
      if(VMPojIQGim == true){VMPojIQGim = false;}
      if(UwfePpOILL == true){UwfePpOILL = false;}
      if(UAKPtEeYoE == true){UAKPtEeYoE = false;}
      if(qpZuemObFs == true){qpZuemObFs = false;}
      if(JMauOAPAza == true){JMauOAPAza = false;}
      if(IkqdGVCztf == true){IkqdGVCztf = false;}
      if(cqReueVjzb == true){cqReueVjzb = false;}
      if(alCRBHYOBt == true){alCRBHYOBt = false;}
      if(neYNuGzuoJ == true){neYNuGzuoJ = false;}
      if(kPgZPSuwzi == true){kPgZPSuwzi = false;}
      if(deAXAVhYcy == true){deAXAVhYcy = false;}
      if(xmxzqyRDio == true){xmxzqyRDio = false;}
      if(eZtpqLEcCh == true){eZtpqLEcCh = false;}
      if(MbORPJdBNY == true){MbORPJdBNY = false;}
      if(XZRqLxRhhR == true){XZRqLxRhhR = false;}
      if(AqNKDDjKgn == true){AqNKDDjKgn = false;}
      if(RFVukUXejh == true){RFVukUXejh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ODODXIOKMQ
{ 
  void fDsTSYcTkm()
  { 
      bool GtFQTgmyty = false;
      bool IwMFOJPfAl = false;
      bool grbHZeAVAo = false;
      bool DOGLeLxUYz = false;
      bool FqzBqwwxni = false;
      bool hCryEORxpo = false;
      bool fQxEutpAaC = false;
      bool LtGAgorZQd = false;
      bool hDhRHBWHHP = false;
      bool sAdiTnttGw = false;
      bool GwWkWmuqRO = false;
      bool WrfMGciexs = false;
      bool XhrKJLPWgr = false;
      bool uxTUWlgwtU = false;
      bool FepsrBTRcp = false;
      bool EOxMYXDLbK = false;
      bool WXKYTZXLoU = false;
      bool wmkcnrqzRH = false;
      bool rytpnfzGuz = false;
      bool hUTjxhURYS = false;
      string gYXwEushAx;
      string ofJDDFWQPF;
      string mDQEMcIbTP;
      string sTaBnQyULA;
      string BXcVwACbKB;
      string fanCAdISja;
      string lQOjDVEHOm;
      string GCEODPZtIL;
      string afRRjSeYBK;
      string HfkjOkJrRZ;
      string wtNWudVYzk;
      string DOKXAGzwAj;
      string qfGEeaQUAS;
      string FgbiPgSuWG;
      string xFYPGsVNjH;
      string kMrgiPmJqT;
      string MAXgeVlaHT;
      string nEYtmkGqxl;
      string FDkrgsotzz;
      string sIDDsxhrjk;
      if(gYXwEushAx == wtNWudVYzk){GtFQTgmyty = true;}
      else if(wtNWudVYzk == gYXwEushAx){GwWkWmuqRO = true;}
      if(ofJDDFWQPF == DOKXAGzwAj){IwMFOJPfAl = true;}
      else if(DOKXAGzwAj == ofJDDFWQPF){WrfMGciexs = true;}
      if(mDQEMcIbTP == qfGEeaQUAS){grbHZeAVAo = true;}
      else if(qfGEeaQUAS == mDQEMcIbTP){XhrKJLPWgr = true;}
      if(sTaBnQyULA == FgbiPgSuWG){DOGLeLxUYz = true;}
      else if(FgbiPgSuWG == sTaBnQyULA){uxTUWlgwtU = true;}
      if(BXcVwACbKB == xFYPGsVNjH){FqzBqwwxni = true;}
      else if(xFYPGsVNjH == BXcVwACbKB){FepsrBTRcp = true;}
      if(fanCAdISja == kMrgiPmJqT){hCryEORxpo = true;}
      else if(kMrgiPmJqT == fanCAdISja){EOxMYXDLbK = true;}
      if(lQOjDVEHOm == MAXgeVlaHT){fQxEutpAaC = true;}
      else if(MAXgeVlaHT == lQOjDVEHOm){WXKYTZXLoU = true;}
      if(GCEODPZtIL == nEYtmkGqxl){LtGAgorZQd = true;}
      if(afRRjSeYBK == FDkrgsotzz){hDhRHBWHHP = true;}
      if(HfkjOkJrRZ == sIDDsxhrjk){sAdiTnttGw = true;}
      while(nEYtmkGqxl == GCEODPZtIL){wmkcnrqzRH = true;}
      while(FDkrgsotzz == FDkrgsotzz){rytpnfzGuz = true;}
      while(sIDDsxhrjk == sIDDsxhrjk){hUTjxhURYS = true;}
      if(GtFQTgmyty == true){GtFQTgmyty = false;}
      if(IwMFOJPfAl == true){IwMFOJPfAl = false;}
      if(grbHZeAVAo == true){grbHZeAVAo = false;}
      if(DOGLeLxUYz == true){DOGLeLxUYz = false;}
      if(FqzBqwwxni == true){FqzBqwwxni = false;}
      if(hCryEORxpo == true){hCryEORxpo = false;}
      if(fQxEutpAaC == true){fQxEutpAaC = false;}
      if(LtGAgorZQd == true){LtGAgorZQd = false;}
      if(hDhRHBWHHP == true){hDhRHBWHHP = false;}
      if(sAdiTnttGw == true){sAdiTnttGw = false;}
      if(GwWkWmuqRO == true){GwWkWmuqRO = false;}
      if(WrfMGciexs == true){WrfMGciexs = false;}
      if(XhrKJLPWgr == true){XhrKJLPWgr = false;}
      if(uxTUWlgwtU == true){uxTUWlgwtU = false;}
      if(FepsrBTRcp == true){FepsrBTRcp = false;}
      if(EOxMYXDLbK == true){EOxMYXDLbK = false;}
      if(WXKYTZXLoU == true){WXKYTZXLoU = false;}
      if(wmkcnrqzRH == true){wmkcnrqzRH = false;}
      if(rytpnfzGuz == true){rytpnfzGuz = false;}
      if(hUTjxhURYS == true){hUTjxhURYS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IYUFHGJXVS
{ 
  void ohBQfAdHbF()
  { 
      bool LlUncGyxNI = false;
      bool AIXhCyGKdy = false;
      bool UBhIkSMfwO = false;
      bool mnkyRauwDi = false;
      bool AokRatkXNP = false;
      bool LwdYBJDLCJ = false;
      bool sSBzUMWYQa = false;
      bool CJHuyfQPhq = false;
      bool goRfDqJMwH = false;
      bool XissohnlwO = false;
      bool WLGlMBniZV = false;
      bool smdLbEAUwd = false;
      bool CJcJDSQNFP = false;
      bool qeTTTVhfTC = false;
      bool CalaNjFgQj = false;
      bool hToSLMixis = false;
      bool jacKdOTJqG = false;
      bool WUBtaaXBuS = false;
      bool NixUhXoAIG = false;
      bool lkwZRbybxz = false;
      string cmzwRrcmnJ;
      string sEDBicwxdp;
      string ImNnwxSXLk;
      string IZUNVipMCI;
      string QwyjPEjYCJ;
      string VxyJCpZKzT;
      string YFbDATiofA;
      string mitVZMndYr;
      string NtUBPLaLLf;
      string JfMhjKTuiu;
      string UtrCWlCcip;
      string BukHGdkZmo;
      string rXdzqHVLlO;
      string rstcXSCRed;
      string IybUeNtFbF;
      string ZsHtDwQrLP;
      string PqqTxHBIjm;
      string bSuJftwIUc;
      string MQjfozlzZa;
      string CJGPNRGIWW;
      if(cmzwRrcmnJ == UtrCWlCcip){LlUncGyxNI = true;}
      else if(UtrCWlCcip == cmzwRrcmnJ){WLGlMBniZV = true;}
      if(sEDBicwxdp == BukHGdkZmo){AIXhCyGKdy = true;}
      else if(BukHGdkZmo == sEDBicwxdp){smdLbEAUwd = true;}
      if(ImNnwxSXLk == rXdzqHVLlO){UBhIkSMfwO = true;}
      else if(rXdzqHVLlO == ImNnwxSXLk){CJcJDSQNFP = true;}
      if(IZUNVipMCI == rstcXSCRed){mnkyRauwDi = true;}
      else if(rstcXSCRed == IZUNVipMCI){qeTTTVhfTC = true;}
      if(QwyjPEjYCJ == IybUeNtFbF){AokRatkXNP = true;}
      else if(IybUeNtFbF == QwyjPEjYCJ){CalaNjFgQj = true;}
      if(VxyJCpZKzT == ZsHtDwQrLP){LwdYBJDLCJ = true;}
      else if(ZsHtDwQrLP == VxyJCpZKzT){hToSLMixis = true;}
      if(YFbDATiofA == PqqTxHBIjm){sSBzUMWYQa = true;}
      else if(PqqTxHBIjm == YFbDATiofA){jacKdOTJqG = true;}
      if(mitVZMndYr == bSuJftwIUc){CJHuyfQPhq = true;}
      if(NtUBPLaLLf == MQjfozlzZa){goRfDqJMwH = true;}
      if(JfMhjKTuiu == CJGPNRGIWW){XissohnlwO = true;}
      while(bSuJftwIUc == mitVZMndYr){WUBtaaXBuS = true;}
      while(MQjfozlzZa == MQjfozlzZa){NixUhXoAIG = true;}
      while(CJGPNRGIWW == CJGPNRGIWW){lkwZRbybxz = true;}
      if(LlUncGyxNI == true){LlUncGyxNI = false;}
      if(AIXhCyGKdy == true){AIXhCyGKdy = false;}
      if(UBhIkSMfwO == true){UBhIkSMfwO = false;}
      if(mnkyRauwDi == true){mnkyRauwDi = false;}
      if(AokRatkXNP == true){AokRatkXNP = false;}
      if(LwdYBJDLCJ == true){LwdYBJDLCJ = false;}
      if(sSBzUMWYQa == true){sSBzUMWYQa = false;}
      if(CJHuyfQPhq == true){CJHuyfQPhq = false;}
      if(goRfDqJMwH == true){goRfDqJMwH = false;}
      if(XissohnlwO == true){XissohnlwO = false;}
      if(WLGlMBniZV == true){WLGlMBniZV = false;}
      if(smdLbEAUwd == true){smdLbEAUwd = false;}
      if(CJcJDSQNFP == true){CJcJDSQNFP = false;}
      if(qeTTTVhfTC == true){qeTTTVhfTC = false;}
      if(CalaNjFgQj == true){CalaNjFgQj = false;}
      if(hToSLMixis == true){hToSLMixis = false;}
      if(jacKdOTJqG == true){jacKdOTJqG = false;}
      if(WUBtaaXBuS == true){WUBtaaXBuS = false;}
      if(NixUhXoAIG == true){NixUhXoAIG = false;}
      if(lkwZRbybxz == true){lkwZRbybxz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XVKSIXWNCR
{ 
  void dTxnCSyPmT()
  { 
      bool iYgeRUyAPX = false;
      bool rQhKBaVRJz = false;
      bool TglSfSPEZN = false;
      bool QPiCpCiMLc = false;
      bool pwrQVqPCGl = false;
      bool PXhUJCmOzz = false;
      bool FtZBHbgeTy = false;
      bool rIFgIXnVxn = false;
      bool CMynyrgOsn = false;
      bool PUNMXwVqJs = false;
      bool KjiHsGSBLl = false;
      bool OQQKwrukDO = false;
      bool uRleiXurIM = false;
      bool BwMDdRdpuq = false;
      bool ZeDHZyDCQe = false;
      bool AjntyryDYV = false;
      bool LZrzjREMge = false;
      bool NFpMnPOeFj = false;
      bool TrbcLQIRFk = false;
      bool SaRYezlEWI = false;
      string oqTAkFEEFc;
      string AfNuarKLPu;
      string ITlnlIWyPk;
      string zTVAUqXXOs;
      string cyBuBQwSSY;
      string JXcTAVEfOc;
      string hGnTcgJNaj;
      string TmxWRKSpmU;
      string LEfpbbpBzy;
      string lrIkKWJgRU;
      string HiqhFWaGCp;
      string DNrtRcZyrB;
      string pHNbybeLLt;
      string AkYRNcMxkE;
      string AjzJuXzNTh;
      string xLnQdzUOjc;
      string rOuHoRoZgn;
      string QbMmAGHEgZ;
      string bQrcxoxInN;
      string IyMHMlorUd;
      if(oqTAkFEEFc == HiqhFWaGCp){iYgeRUyAPX = true;}
      else if(HiqhFWaGCp == oqTAkFEEFc){KjiHsGSBLl = true;}
      if(AfNuarKLPu == DNrtRcZyrB){rQhKBaVRJz = true;}
      else if(DNrtRcZyrB == AfNuarKLPu){OQQKwrukDO = true;}
      if(ITlnlIWyPk == pHNbybeLLt){TglSfSPEZN = true;}
      else if(pHNbybeLLt == ITlnlIWyPk){uRleiXurIM = true;}
      if(zTVAUqXXOs == AkYRNcMxkE){QPiCpCiMLc = true;}
      else if(AkYRNcMxkE == zTVAUqXXOs){BwMDdRdpuq = true;}
      if(cyBuBQwSSY == AjzJuXzNTh){pwrQVqPCGl = true;}
      else if(AjzJuXzNTh == cyBuBQwSSY){ZeDHZyDCQe = true;}
      if(JXcTAVEfOc == xLnQdzUOjc){PXhUJCmOzz = true;}
      else if(xLnQdzUOjc == JXcTAVEfOc){AjntyryDYV = true;}
      if(hGnTcgJNaj == rOuHoRoZgn){FtZBHbgeTy = true;}
      else if(rOuHoRoZgn == hGnTcgJNaj){LZrzjREMge = true;}
      if(TmxWRKSpmU == QbMmAGHEgZ){rIFgIXnVxn = true;}
      if(LEfpbbpBzy == bQrcxoxInN){CMynyrgOsn = true;}
      if(lrIkKWJgRU == IyMHMlorUd){PUNMXwVqJs = true;}
      while(QbMmAGHEgZ == TmxWRKSpmU){NFpMnPOeFj = true;}
      while(bQrcxoxInN == bQrcxoxInN){TrbcLQIRFk = true;}
      while(IyMHMlorUd == IyMHMlorUd){SaRYezlEWI = true;}
      if(iYgeRUyAPX == true){iYgeRUyAPX = false;}
      if(rQhKBaVRJz == true){rQhKBaVRJz = false;}
      if(TglSfSPEZN == true){TglSfSPEZN = false;}
      if(QPiCpCiMLc == true){QPiCpCiMLc = false;}
      if(pwrQVqPCGl == true){pwrQVqPCGl = false;}
      if(PXhUJCmOzz == true){PXhUJCmOzz = false;}
      if(FtZBHbgeTy == true){FtZBHbgeTy = false;}
      if(rIFgIXnVxn == true){rIFgIXnVxn = false;}
      if(CMynyrgOsn == true){CMynyrgOsn = false;}
      if(PUNMXwVqJs == true){PUNMXwVqJs = false;}
      if(KjiHsGSBLl == true){KjiHsGSBLl = false;}
      if(OQQKwrukDO == true){OQQKwrukDO = false;}
      if(uRleiXurIM == true){uRleiXurIM = false;}
      if(BwMDdRdpuq == true){BwMDdRdpuq = false;}
      if(ZeDHZyDCQe == true){ZeDHZyDCQe = false;}
      if(AjntyryDYV == true){AjntyryDYV = false;}
      if(LZrzjREMge == true){LZrzjREMge = false;}
      if(NFpMnPOeFj == true){NFpMnPOeFj = false;}
      if(TrbcLQIRFk == true){TrbcLQIRFk = false;}
      if(SaRYezlEWI == true){SaRYezlEWI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVLTTCXXXT
{ 
  void hlHmxrYxQu()
  { 
      bool RfRYOaywGj = false;
      bool auiQgHynXU = false;
      bool PwHgqLbkMO = false;
      bool XwrHxgwsxc = false;
      bool lOrwtzcyap = false;
      bool RgNrVUYjhC = false;
      bool yMjqLeCaTz = false;
      bool LFpthAEKmq = false;
      bool hcKVwqizkb = false;
      bool IMKteZeAjP = false;
      bool xBeaeMpSJV = false;
      bool PNxqTUCNtU = false;
      bool uCpqqytwPI = false;
      bool VDZXtgyiqi = false;
      bool APpPLtPTaJ = false;
      bool XQFOTtLmjf = false;
      bool StDBzMnYwm = false;
      bool WSVLUfMZfx = false;
      bool iZVFkExKEz = false;
      bool ULzKQFLnPz = false;
      string AfsJXFTgVa;
      string DCUWafyQib;
      string YzSluUUdIP;
      string nSsuIGcOuj;
      string xKsjfMzxae;
      string oOxeuANHOC;
      string jpYGlkJYOT;
      string DiUyeNGhGh;
      string VXCdZZUNAH;
      string rVArzGlmxt;
      string DZiGbFszAg;
      string tfAfgMmtfL;
      string PuYGbhicyX;
      string bSjLdunuBU;
      string gVNSMMUTKm;
      string TqHleIAbet;
      string WQAbFaunCk;
      string XrsKetgFsO;
      string MORLEjLygU;
      string tLPHyQVkNl;
      if(AfsJXFTgVa == DZiGbFszAg){RfRYOaywGj = true;}
      else if(DZiGbFszAg == AfsJXFTgVa){xBeaeMpSJV = true;}
      if(DCUWafyQib == tfAfgMmtfL){auiQgHynXU = true;}
      else if(tfAfgMmtfL == DCUWafyQib){PNxqTUCNtU = true;}
      if(YzSluUUdIP == PuYGbhicyX){PwHgqLbkMO = true;}
      else if(PuYGbhicyX == YzSluUUdIP){uCpqqytwPI = true;}
      if(nSsuIGcOuj == bSjLdunuBU){XwrHxgwsxc = true;}
      else if(bSjLdunuBU == nSsuIGcOuj){VDZXtgyiqi = true;}
      if(xKsjfMzxae == gVNSMMUTKm){lOrwtzcyap = true;}
      else if(gVNSMMUTKm == xKsjfMzxae){APpPLtPTaJ = true;}
      if(oOxeuANHOC == TqHleIAbet){RgNrVUYjhC = true;}
      else if(TqHleIAbet == oOxeuANHOC){XQFOTtLmjf = true;}
      if(jpYGlkJYOT == WQAbFaunCk){yMjqLeCaTz = true;}
      else if(WQAbFaunCk == jpYGlkJYOT){StDBzMnYwm = true;}
      if(DiUyeNGhGh == XrsKetgFsO){LFpthAEKmq = true;}
      if(VXCdZZUNAH == MORLEjLygU){hcKVwqizkb = true;}
      if(rVArzGlmxt == tLPHyQVkNl){IMKteZeAjP = true;}
      while(XrsKetgFsO == DiUyeNGhGh){WSVLUfMZfx = true;}
      while(MORLEjLygU == MORLEjLygU){iZVFkExKEz = true;}
      while(tLPHyQVkNl == tLPHyQVkNl){ULzKQFLnPz = true;}
      if(RfRYOaywGj == true){RfRYOaywGj = false;}
      if(auiQgHynXU == true){auiQgHynXU = false;}
      if(PwHgqLbkMO == true){PwHgqLbkMO = false;}
      if(XwrHxgwsxc == true){XwrHxgwsxc = false;}
      if(lOrwtzcyap == true){lOrwtzcyap = false;}
      if(RgNrVUYjhC == true){RgNrVUYjhC = false;}
      if(yMjqLeCaTz == true){yMjqLeCaTz = false;}
      if(LFpthAEKmq == true){LFpthAEKmq = false;}
      if(hcKVwqizkb == true){hcKVwqizkb = false;}
      if(IMKteZeAjP == true){IMKteZeAjP = false;}
      if(xBeaeMpSJV == true){xBeaeMpSJV = false;}
      if(PNxqTUCNtU == true){PNxqTUCNtU = false;}
      if(uCpqqytwPI == true){uCpqqytwPI = false;}
      if(VDZXtgyiqi == true){VDZXtgyiqi = false;}
      if(APpPLtPTaJ == true){APpPLtPTaJ = false;}
      if(XQFOTtLmjf == true){XQFOTtLmjf = false;}
      if(StDBzMnYwm == true){StDBzMnYwm = false;}
      if(WSVLUfMZfx == true){WSVLUfMZfx = false;}
      if(iZVFkExKEz == true){iZVFkExKEz = false;}
      if(ULzKQFLnPz == true){ULzKQFLnPz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UDRLLTECFH
{ 
  void jCRkEQdXNB()
  { 
      bool XTKrRWGyJU = false;
      bool AwRZADumzr = false;
      bool HxjsPxgFwm = false;
      bool QYyKsDeapy = false;
      bool yOBFuABiSC = false;
      bool qgsPzZiQcU = false;
      bool oACVDbyHfw = false;
      bool XTwBsrweyO = false;
      bool uymswifhKT = false;
      bool UNyVIxMeBS = false;
      bool CtCWeWkqWH = false;
      bool dESNZqNIZU = false;
      bool uPxMaKUarw = false;
      bool eQceLAwPOY = false;
      bool ynLCoQujuR = false;
      bool jDFgXmxouT = false;
      bool BJzZbMamBY = false;
      bool uxtAWHDtWK = false;
      bool OkeaLaLwHY = false;
      bool DGUtWnolZc = false;
      string yyeWGKrpfs;
      string tDqQgUGrtR;
      string DymBHbMNLB;
      string amFuLxyQyA;
      string gYgeOuLgYu;
      string VihnKALdOe;
      string yeeeSGxwEi;
      string VpttjdQHmL;
      string QeoPeqERkL;
      string kUBTCCtBLH;
      string yOcoYfonDf;
      string iEpCOSoOAb;
      string BfLsyBnZrh;
      string jOufNBCzpy;
      string BQNEbgdzFi;
      string MeBjFRDiqX;
      string rPwUwUIKoM;
      string QpYCZkRGRQ;
      string XoTIVENLZu;
      string xTISGlUsHH;
      if(yyeWGKrpfs == yOcoYfonDf){XTKrRWGyJU = true;}
      else if(yOcoYfonDf == yyeWGKrpfs){CtCWeWkqWH = true;}
      if(tDqQgUGrtR == iEpCOSoOAb){AwRZADumzr = true;}
      else if(iEpCOSoOAb == tDqQgUGrtR){dESNZqNIZU = true;}
      if(DymBHbMNLB == BfLsyBnZrh){HxjsPxgFwm = true;}
      else if(BfLsyBnZrh == DymBHbMNLB){uPxMaKUarw = true;}
      if(amFuLxyQyA == jOufNBCzpy){QYyKsDeapy = true;}
      else if(jOufNBCzpy == amFuLxyQyA){eQceLAwPOY = true;}
      if(gYgeOuLgYu == BQNEbgdzFi){yOBFuABiSC = true;}
      else if(BQNEbgdzFi == gYgeOuLgYu){ynLCoQujuR = true;}
      if(VihnKALdOe == MeBjFRDiqX){qgsPzZiQcU = true;}
      else if(MeBjFRDiqX == VihnKALdOe){jDFgXmxouT = true;}
      if(yeeeSGxwEi == rPwUwUIKoM){oACVDbyHfw = true;}
      else if(rPwUwUIKoM == yeeeSGxwEi){BJzZbMamBY = true;}
      if(VpttjdQHmL == QpYCZkRGRQ){XTwBsrweyO = true;}
      if(QeoPeqERkL == XoTIVENLZu){uymswifhKT = true;}
      if(kUBTCCtBLH == xTISGlUsHH){UNyVIxMeBS = true;}
      while(QpYCZkRGRQ == VpttjdQHmL){uxtAWHDtWK = true;}
      while(XoTIVENLZu == XoTIVENLZu){OkeaLaLwHY = true;}
      while(xTISGlUsHH == xTISGlUsHH){DGUtWnolZc = true;}
      if(XTKrRWGyJU == true){XTKrRWGyJU = false;}
      if(AwRZADumzr == true){AwRZADumzr = false;}
      if(HxjsPxgFwm == true){HxjsPxgFwm = false;}
      if(QYyKsDeapy == true){QYyKsDeapy = false;}
      if(yOBFuABiSC == true){yOBFuABiSC = false;}
      if(qgsPzZiQcU == true){qgsPzZiQcU = false;}
      if(oACVDbyHfw == true){oACVDbyHfw = false;}
      if(XTwBsrweyO == true){XTwBsrweyO = false;}
      if(uymswifhKT == true){uymswifhKT = false;}
      if(UNyVIxMeBS == true){UNyVIxMeBS = false;}
      if(CtCWeWkqWH == true){CtCWeWkqWH = false;}
      if(dESNZqNIZU == true){dESNZqNIZU = false;}
      if(uPxMaKUarw == true){uPxMaKUarw = false;}
      if(eQceLAwPOY == true){eQceLAwPOY = false;}
      if(ynLCoQujuR == true){ynLCoQujuR = false;}
      if(jDFgXmxouT == true){jDFgXmxouT = false;}
      if(BJzZbMamBY == true){BJzZbMamBY = false;}
      if(uxtAWHDtWK == true){uxtAWHDtWK = false;}
      if(OkeaLaLwHY == true){OkeaLaLwHY = false;}
      if(DGUtWnolZc == true){DGUtWnolZc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVYXLMOZLQ
{ 
  void qbzjocGkgw()
  { 
      bool xJgdCsbftM = false;
      bool CmhdYKgPLL = false;
      bool yfaHITPYMQ = false;
      bool mkamfhtqSb = false;
      bool YVodRsgdBK = false;
      bool kkfHoQiZUh = false;
      bool cCSdZRMuyq = false;
      bool PowilcqwoP = false;
      bool mkXCfBESxO = false;
      bool yUWkzVCLEz = false;
      bool fleJtwoxUM = false;
      bool ZljEuqeQxX = false;
      bool NsxjsuSLjP = false;
      bool afqpiBFNIi = false;
      bool MHxkoMkRoH = false;
      bool qkNglmnuQy = false;
      bool dcMFksttVs = false;
      bool kRINKFuLug = false;
      bool JAVbYoSKDw = false;
      bool MKxJFjtrzu = false;
      string efhXnqCqAj;
      string TDAHGdUCoF;
      string huBAMSoyWc;
      string QPHGnWUxqs;
      string LmbDedzrit;
      string uDmOkidgLU;
      string CETXSDutTj;
      string IWLwtuTyUi;
      string SwPcgNcsUE;
      string snlVpGSEjb;
      string hFYykXrpTo;
      string PeLcCFoqpF;
      string aCYPqTkoFm;
      string cPOsAMXQqI;
      string VlYenNcJTj;
      string RbNeBfgIHQ;
      string mCkgMAQSbo;
      string hYzhjncsac;
      string qbVUVBBjqU;
      string fOIaVSBrSn;
      if(efhXnqCqAj == hFYykXrpTo){xJgdCsbftM = true;}
      else if(hFYykXrpTo == efhXnqCqAj){fleJtwoxUM = true;}
      if(TDAHGdUCoF == PeLcCFoqpF){CmhdYKgPLL = true;}
      else if(PeLcCFoqpF == TDAHGdUCoF){ZljEuqeQxX = true;}
      if(huBAMSoyWc == aCYPqTkoFm){yfaHITPYMQ = true;}
      else if(aCYPqTkoFm == huBAMSoyWc){NsxjsuSLjP = true;}
      if(QPHGnWUxqs == cPOsAMXQqI){mkamfhtqSb = true;}
      else if(cPOsAMXQqI == QPHGnWUxqs){afqpiBFNIi = true;}
      if(LmbDedzrit == VlYenNcJTj){YVodRsgdBK = true;}
      else if(VlYenNcJTj == LmbDedzrit){MHxkoMkRoH = true;}
      if(uDmOkidgLU == RbNeBfgIHQ){kkfHoQiZUh = true;}
      else if(RbNeBfgIHQ == uDmOkidgLU){qkNglmnuQy = true;}
      if(CETXSDutTj == mCkgMAQSbo){cCSdZRMuyq = true;}
      else if(mCkgMAQSbo == CETXSDutTj){dcMFksttVs = true;}
      if(IWLwtuTyUi == hYzhjncsac){PowilcqwoP = true;}
      if(SwPcgNcsUE == qbVUVBBjqU){mkXCfBESxO = true;}
      if(snlVpGSEjb == fOIaVSBrSn){yUWkzVCLEz = true;}
      while(hYzhjncsac == IWLwtuTyUi){kRINKFuLug = true;}
      while(qbVUVBBjqU == qbVUVBBjqU){JAVbYoSKDw = true;}
      while(fOIaVSBrSn == fOIaVSBrSn){MKxJFjtrzu = true;}
      if(xJgdCsbftM == true){xJgdCsbftM = false;}
      if(CmhdYKgPLL == true){CmhdYKgPLL = false;}
      if(yfaHITPYMQ == true){yfaHITPYMQ = false;}
      if(mkamfhtqSb == true){mkamfhtqSb = false;}
      if(YVodRsgdBK == true){YVodRsgdBK = false;}
      if(kkfHoQiZUh == true){kkfHoQiZUh = false;}
      if(cCSdZRMuyq == true){cCSdZRMuyq = false;}
      if(PowilcqwoP == true){PowilcqwoP = false;}
      if(mkXCfBESxO == true){mkXCfBESxO = false;}
      if(yUWkzVCLEz == true){yUWkzVCLEz = false;}
      if(fleJtwoxUM == true){fleJtwoxUM = false;}
      if(ZljEuqeQxX == true){ZljEuqeQxX = false;}
      if(NsxjsuSLjP == true){NsxjsuSLjP = false;}
      if(afqpiBFNIi == true){afqpiBFNIi = false;}
      if(MHxkoMkRoH == true){MHxkoMkRoH = false;}
      if(qkNglmnuQy == true){qkNglmnuQy = false;}
      if(dcMFksttVs == true){dcMFksttVs = false;}
      if(kRINKFuLug == true){kRINKFuLug = false;}
      if(JAVbYoSKDw == true){JAVbYoSKDw = false;}
      if(MKxJFjtrzu == true){MKxJFjtrzu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OEMFOBOELX
{ 
  void MxzdDqURXC()
  { 
      bool bZOUGTBORE = false;
      bool eIdHxjfIpB = false;
      bool NHYYjimjeb = false;
      bool KwZENipgXo = false;
      bool jScEeXFsze = false;
      bool URfAXUAojW = false;
      bool gRjpshiZtN = false;
      bool sykAQudTtM = false;
      bool dsjAHsPYgs = false;
      bool hAxAIShmLw = false;
      bool ofzlkVgfic = false;
      bool pguXsmgjhA = false;
      bool RJsBesBjry = false;
      bool MpIyWxtyPl = false;
      bool LjpDCBFYHV = false;
      bool lyFLdelyGq = false;
      bool TxnjPzXwAw = false;
      bool siUwnhSoyc = false;
      bool mcbVMNkxUq = false;
      bool KwqXROwFmC = false;
      string hKRJjxlQeA;
      string UDJsHSbcYT;
      string RyUsSjceFj;
      string jJXtDOMgUT;
      string DeBXCURhMd;
      string meziujpXpA;
      string TGLtQLfPps;
      string FtIFPmxwqy;
      string SuSbxFJoyT;
      string XnpTzxSGGq;
      string oBqSXsVtSI;
      string lsgrhYnjxL;
      string BpRWUQDnFS;
      string UqpzIQEzDD;
      string iPWpgeHyla;
      string IhItpyjTxG;
      string ohnznuChiR;
      string TogsclTapp;
      string JFBeJlhuIJ;
      string gjBxOAaWBk;
      if(hKRJjxlQeA == oBqSXsVtSI){bZOUGTBORE = true;}
      else if(oBqSXsVtSI == hKRJjxlQeA){ofzlkVgfic = true;}
      if(UDJsHSbcYT == lsgrhYnjxL){eIdHxjfIpB = true;}
      else if(lsgrhYnjxL == UDJsHSbcYT){pguXsmgjhA = true;}
      if(RyUsSjceFj == BpRWUQDnFS){NHYYjimjeb = true;}
      else if(BpRWUQDnFS == RyUsSjceFj){RJsBesBjry = true;}
      if(jJXtDOMgUT == UqpzIQEzDD){KwZENipgXo = true;}
      else if(UqpzIQEzDD == jJXtDOMgUT){MpIyWxtyPl = true;}
      if(DeBXCURhMd == iPWpgeHyla){jScEeXFsze = true;}
      else if(iPWpgeHyla == DeBXCURhMd){LjpDCBFYHV = true;}
      if(meziujpXpA == IhItpyjTxG){URfAXUAojW = true;}
      else if(IhItpyjTxG == meziujpXpA){lyFLdelyGq = true;}
      if(TGLtQLfPps == ohnznuChiR){gRjpshiZtN = true;}
      else if(ohnznuChiR == TGLtQLfPps){TxnjPzXwAw = true;}
      if(FtIFPmxwqy == TogsclTapp){sykAQudTtM = true;}
      if(SuSbxFJoyT == JFBeJlhuIJ){dsjAHsPYgs = true;}
      if(XnpTzxSGGq == gjBxOAaWBk){hAxAIShmLw = true;}
      while(TogsclTapp == FtIFPmxwqy){siUwnhSoyc = true;}
      while(JFBeJlhuIJ == JFBeJlhuIJ){mcbVMNkxUq = true;}
      while(gjBxOAaWBk == gjBxOAaWBk){KwqXROwFmC = true;}
      if(bZOUGTBORE == true){bZOUGTBORE = false;}
      if(eIdHxjfIpB == true){eIdHxjfIpB = false;}
      if(NHYYjimjeb == true){NHYYjimjeb = false;}
      if(KwZENipgXo == true){KwZENipgXo = false;}
      if(jScEeXFsze == true){jScEeXFsze = false;}
      if(URfAXUAojW == true){URfAXUAojW = false;}
      if(gRjpshiZtN == true){gRjpshiZtN = false;}
      if(sykAQudTtM == true){sykAQudTtM = false;}
      if(dsjAHsPYgs == true){dsjAHsPYgs = false;}
      if(hAxAIShmLw == true){hAxAIShmLw = false;}
      if(ofzlkVgfic == true){ofzlkVgfic = false;}
      if(pguXsmgjhA == true){pguXsmgjhA = false;}
      if(RJsBesBjry == true){RJsBesBjry = false;}
      if(MpIyWxtyPl == true){MpIyWxtyPl = false;}
      if(LjpDCBFYHV == true){LjpDCBFYHV = false;}
      if(lyFLdelyGq == true){lyFLdelyGq = false;}
      if(TxnjPzXwAw == true){TxnjPzXwAw = false;}
      if(siUwnhSoyc == true){siUwnhSoyc = false;}
      if(mcbVMNkxUq == true){mcbVMNkxUq = false;}
      if(KwqXROwFmC == true){KwqXROwFmC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FRUOPJCTST
{ 
  void wguEfMeoQP()
  { 
      bool WdtUbdqKqM = false;
      bool bkDNbZjSKl = false;
      bool LVDnWzbslE = false;
      bool BULHBYRhOq = false;
      bool gCbcjJAlNY = false;
      bool yDmtQBZGxb = false;
      bool CxYlLHYuLC = false;
      bool HBDSEJsaEM = false;
      bool zoeNFxgRqA = false;
      bool yKjmoidpQb = false;
      bool kEZLQxATpH = false;
      bool IyBkcMSKfO = false;
      bool aHDLDwRPdU = false;
      bool eDKbbtOTwI = false;
      bool xMajrAJyKb = false;
      bool QSJCBcBOHT = false;
      bool fjpUbEnZJh = false;
      bool xyNWQNfTTD = false;
      bool mSFBEMsIay = false;
      bool sAMccNWGIm = false;
      string uzrjIgrcls;
      string HUKOFraXtl;
      string cnbMafQSAl;
      string osldqVYNFs;
      string rEOqAasxIZ;
      string HshAfHWfIc;
      string QYczENhgWj;
      string TNRAtYYkLA;
      string lTKZewLkxj;
      string yrEccSbPml;
      string rMaXGtagGH;
      string hlTIpxNCUI;
      string BxilkaInWa;
      string xIxZHYrlTj;
      string UedpBLXwlf;
      string FYudjudnme;
      string llJfJZotBR;
      string EahjmWSrjY;
      string DMCqVXNSpM;
      string uEzoyhVyfb;
      if(uzrjIgrcls == rMaXGtagGH){WdtUbdqKqM = true;}
      else if(rMaXGtagGH == uzrjIgrcls){kEZLQxATpH = true;}
      if(HUKOFraXtl == hlTIpxNCUI){bkDNbZjSKl = true;}
      else if(hlTIpxNCUI == HUKOFraXtl){IyBkcMSKfO = true;}
      if(cnbMafQSAl == BxilkaInWa){LVDnWzbslE = true;}
      else if(BxilkaInWa == cnbMafQSAl){aHDLDwRPdU = true;}
      if(osldqVYNFs == xIxZHYrlTj){BULHBYRhOq = true;}
      else if(xIxZHYrlTj == osldqVYNFs){eDKbbtOTwI = true;}
      if(rEOqAasxIZ == UedpBLXwlf){gCbcjJAlNY = true;}
      else if(UedpBLXwlf == rEOqAasxIZ){xMajrAJyKb = true;}
      if(HshAfHWfIc == FYudjudnme){yDmtQBZGxb = true;}
      else if(FYudjudnme == HshAfHWfIc){QSJCBcBOHT = true;}
      if(QYczENhgWj == llJfJZotBR){CxYlLHYuLC = true;}
      else if(llJfJZotBR == QYczENhgWj){fjpUbEnZJh = true;}
      if(TNRAtYYkLA == EahjmWSrjY){HBDSEJsaEM = true;}
      if(lTKZewLkxj == DMCqVXNSpM){zoeNFxgRqA = true;}
      if(yrEccSbPml == uEzoyhVyfb){yKjmoidpQb = true;}
      while(EahjmWSrjY == TNRAtYYkLA){xyNWQNfTTD = true;}
      while(DMCqVXNSpM == DMCqVXNSpM){mSFBEMsIay = true;}
      while(uEzoyhVyfb == uEzoyhVyfb){sAMccNWGIm = true;}
      if(WdtUbdqKqM == true){WdtUbdqKqM = false;}
      if(bkDNbZjSKl == true){bkDNbZjSKl = false;}
      if(LVDnWzbslE == true){LVDnWzbslE = false;}
      if(BULHBYRhOq == true){BULHBYRhOq = false;}
      if(gCbcjJAlNY == true){gCbcjJAlNY = false;}
      if(yDmtQBZGxb == true){yDmtQBZGxb = false;}
      if(CxYlLHYuLC == true){CxYlLHYuLC = false;}
      if(HBDSEJsaEM == true){HBDSEJsaEM = false;}
      if(zoeNFxgRqA == true){zoeNFxgRqA = false;}
      if(yKjmoidpQb == true){yKjmoidpQb = false;}
      if(kEZLQxATpH == true){kEZLQxATpH = false;}
      if(IyBkcMSKfO == true){IyBkcMSKfO = false;}
      if(aHDLDwRPdU == true){aHDLDwRPdU = false;}
      if(eDKbbtOTwI == true){eDKbbtOTwI = false;}
      if(xMajrAJyKb == true){xMajrAJyKb = false;}
      if(QSJCBcBOHT == true){QSJCBcBOHT = false;}
      if(fjpUbEnZJh == true){fjpUbEnZJh = false;}
      if(xyNWQNfTTD == true){xyNWQNfTTD = false;}
      if(mSFBEMsIay == true){mSFBEMsIay = false;}
      if(sAMccNWGIm == true){sAMccNWGIm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DHRHXLWMCG
{ 
  void BxQJjieKAG()
  { 
      bool BudWWdQVxe = false;
      bool kTYSrJrXkk = false;
      bool WtKkxCELww = false;
      bool eynHeoAKnF = false;
      bool rpkoATXKXs = false;
      bool VPmjSGkrZT = false;
      bool YEYAzmeRnD = false;
      bool IhjesfJVkd = false;
      bool etnDaPLEnX = false;
      bool DHkTfmRjoN = false;
      bool nFVUjmfHpm = false;
      bool wOHuoeQVZj = false;
      bool bZdQzAxPzG = false;
      bool OYgWoYXSSm = false;
      bool jENAanAoeB = false;
      bool VuKEkOaFUj = false;
      bool pPIjYXhjGP = false;
      bool HyDlAXMdoL = false;
      bool AHkxjSObka = false;
      bool xRyiwTwdaD = false;
      string LQfzbAxIkX;
      string DYMLNOIdst;
      string hDDZOHTzFj;
      string UazZyIeFdW;
      string XQLIRxoGNX;
      string XQmnNIMGjT;
      string gyCBCcZlME;
      string jCAWWQquHR;
      string SMkgLEmKMp;
      string uYUJpZOJFo;
      string WCsInVQQRw;
      string QRySBTMUoy;
      string pOZWJLgpgx;
      string CgoStPTcsp;
      string nWsPYdaCIV;
      string NsUHyHcWzc;
      string nZiUticeXk;
      string zibyKSVJxf;
      string jehKjIMhTl;
      string mxdQCNmXUp;
      if(LQfzbAxIkX == WCsInVQQRw){BudWWdQVxe = true;}
      else if(WCsInVQQRw == LQfzbAxIkX){nFVUjmfHpm = true;}
      if(DYMLNOIdst == QRySBTMUoy){kTYSrJrXkk = true;}
      else if(QRySBTMUoy == DYMLNOIdst){wOHuoeQVZj = true;}
      if(hDDZOHTzFj == pOZWJLgpgx){WtKkxCELww = true;}
      else if(pOZWJLgpgx == hDDZOHTzFj){bZdQzAxPzG = true;}
      if(UazZyIeFdW == CgoStPTcsp){eynHeoAKnF = true;}
      else if(CgoStPTcsp == UazZyIeFdW){OYgWoYXSSm = true;}
      if(XQLIRxoGNX == nWsPYdaCIV){rpkoATXKXs = true;}
      else if(nWsPYdaCIV == XQLIRxoGNX){jENAanAoeB = true;}
      if(XQmnNIMGjT == NsUHyHcWzc){VPmjSGkrZT = true;}
      else if(NsUHyHcWzc == XQmnNIMGjT){VuKEkOaFUj = true;}
      if(gyCBCcZlME == nZiUticeXk){YEYAzmeRnD = true;}
      else if(nZiUticeXk == gyCBCcZlME){pPIjYXhjGP = true;}
      if(jCAWWQquHR == zibyKSVJxf){IhjesfJVkd = true;}
      if(SMkgLEmKMp == jehKjIMhTl){etnDaPLEnX = true;}
      if(uYUJpZOJFo == mxdQCNmXUp){DHkTfmRjoN = true;}
      while(zibyKSVJxf == jCAWWQquHR){HyDlAXMdoL = true;}
      while(jehKjIMhTl == jehKjIMhTl){AHkxjSObka = true;}
      while(mxdQCNmXUp == mxdQCNmXUp){xRyiwTwdaD = true;}
      if(BudWWdQVxe == true){BudWWdQVxe = false;}
      if(kTYSrJrXkk == true){kTYSrJrXkk = false;}
      if(WtKkxCELww == true){WtKkxCELww = false;}
      if(eynHeoAKnF == true){eynHeoAKnF = false;}
      if(rpkoATXKXs == true){rpkoATXKXs = false;}
      if(VPmjSGkrZT == true){VPmjSGkrZT = false;}
      if(YEYAzmeRnD == true){YEYAzmeRnD = false;}
      if(IhjesfJVkd == true){IhjesfJVkd = false;}
      if(etnDaPLEnX == true){etnDaPLEnX = false;}
      if(DHkTfmRjoN == true){DHkTfmRjoN = false;}
      if(nFVUjmfHpm == true){nFVUjmfHpm = false;}
      if(wOHuoeQVZj == true){wOHuoeQVZj = false;}
      if(bZdQzAxPzG == true){bZdQzAxPzG = false;}
      if(OYgWoYXSSm == true){OYgWoYXSSm = false;}
      if(jENAanAoeB == true){jENAanAoeB = false;}
      if(VuKEkOaFUj == true){VuKEkOaFUj = false;}
      if(pPIjYXhjGP == true){pPIjYXhjGP = false;}
      if(HyDlAXMdoL == true){HyDlAXMdoL = false;}
      if(AHkxjSObka == true){AHkxjSObka = false;}
      if(xRyiwTwdaD == true){xRyiwTwdaD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XSJZSWAWBW
{ 
  void ikDZwscQQd()
  { 
      bool oboOWPOiko = false;
      bool LqVmzQDZAw = false;
      bool IguMFXlxou = false;
      bool nfFQcfJOkX = false;
      bool YOCHPSdGXC = false;
      bool QoMDFIfbIy = false;
      bool cRsoAelEKS = false;
      bool HoocWtdmxl = false;
      bool tfZmdzSCKT = false;
      bool zgFltHVMHj = false;
      bool gYuEubzjgL = false;
      bool dseVExrGKB = false;
      bool MjspSZiChP = false;
      bool XQfNFUjUqC = false;
      bool zhVzpGCjhx = false;
      bool OPBFXxeElU = false;
      bool rxBQmNMQQi = false;
      bool MWOIBdNtAL = false;
      bool XzTkAIOZpH = false;
      bool ofiVKCgEMc = false;
      string LyRBheRyTA;
      string SgnBaxWhJC;
      string DmhEBOJFiw;
      string qlLGnhQxWn;
      string oxKaXVULYS;
      string SAFkNXPNzS;
      string VMPXIfVhNs;
      string fZLVNFcGff;
      string txfQcqgZrP;
      string RCxDSchmSq;
      string AlyflsojXI;
      string uIgTYXfytR;
      string zuoyadcICj;
      string XpnofHzzej;
      string BwBjTJUdeu;
      string wirArExzFH;
      string PggnjFTrnQ;
      string XgTJPDsFdR;
      string IzcHmnxmwa;
      string KztWTUONzN;
      if(LyRBheRyTA == AlyflsojXI){oboOWPOiko = true;}
      else if(AlyflsojXI == LyRBheRyTA){gYuEubzjgL = true;}
      if(SgnBaxWhJC == uIgTYXfytR){LqVmzQDZAw = true;}
      else if(uIgTYXfytR == SgnBaxWhJC){dseVExrGKB = true;}
      if(DmhEBOJFiw == zuoyadcICj){IguMFXlxou = true;}
      else if(zuoyadcICj == DmhEBOJFiw){MjspSZiChP = true;}
      if(qlLGnhQxWn == XpnofHzzej){nfFQcfJOkX = true;}
      else if(XpnofHzzej == qlLGnhQxWn){XQfNFUjUqC = true;}
      if(oxKaXVULYS == BwBjTJUdeu){YOCHPSdGXC = true;}
      else if(BwBjTJUdeu == oxKaXVULYS){zhVzpGCjhx = true;}
      if(SAFkNXPNzS == wirArExzFH){QoMDFIfbIy = true;}
      else if(wirArExzFH == SAFkNXPNzS){OPBFXxeElU = true;}
      if(VMPXIfVhNs == PggnjFTrnQ){cRsoAelEKS = true;}
      else if(PggnjFTrnQ == VMPXIfVhNs){rxBQmNMQQi = true;}
      if(fZLVNFcGff == XgTJPDsFdR){HoocWtdmxl = true;}
      if(txfQcqgZrP == IzcHmnxmwa){tfZmdzSCKT = true;}
      if(RCxDSchmSq == KztWTUONzN){zgFltHVMHj = true;}
      while(XgTJPDsFdR == fZLVNFcGff){MWOIBdNtAL = true;}
      while(IzcHmnxmwa == IzcHmnxmwa){XzTkAIOZpH = true;}
      while(KztWTUONzN == KztWTUONzN){ofiVKCgEMc = true;}
      if(oboOWPOiko == true){oboOWPOiko = false;}
      if(LqVmzQDZAw == true){LqVmzQDZAw = false;}
      if(IguMFXlxou == true){IguMFXlxou = false;}
      if(nfFQcfJOkX == true){nfFQcfJOkX = false;}
      if(YOCHPSdGXC == true){YOCHPSdGXC = false;}
      if(QoMDFIfbIy == true){QoMDFIfbIy = false;}
      if(cRsoAelEKS == true){cRsoAelEKS = false;}
      if(HoocWtdmxl == true){HoocWtdmxl = false;}
      if(tfZmdzSCKT == true){tfZmdzSCKT = false;}
      if(zgFltHVMHj == true){zgFltHVMHj = false;}
      if(gYuEubzjgL == true){gYuEubzjgL = false;}
      if(dseVExrGKB == true){dseVExrGKB = false;}
      if(MjspSZiChP == true){MjspSZiChP = false;}
      if(XQfNFUjUqC == true){XQfNFUjUqC = false;}
      if(zhVzpGCjhx == true){zhVzpGCjhx = false;}
      if(OPBFXxeElU == true){OPBFXxeElU = false;}
      if(rxBQmNMQQi == true){rxBQmNMQQi = false;}
      if(MWOIBdNtAL == true){MWOIBdNtAL = false;}
      if(XzTkAIOZpH == true){XzTkAIOZpH = false;}
      if(ofiVKCgEMc == true){ofiVKCgEMc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RPEGLYBZOU
{ 
  void TKVyfUVZWC()
  { 
      bool xWhCNLGiVQ = false;
      bool jatAVQbgiQ = false;
      bool dGhCJyxRUt = false;
      bool qTPcCgnzMh = false;
      bool uHmAkmeCsz = false;
      bool EkpafqoerP = false;
      bool OnObYPKRxn = false;
      bool ccUBUVSgRW = false;
      bool TuYUoFdowL = false;
      bool rIGxTHsLaV = false;
      bool bMEFWbQnFJ = false;
      bool XHNVuSPtlT = false;
      bool kVUkuTVXgN = false;
      bool cHGwtGpTxN = false;
      bool ooimnkukBA = false;
      bool ryYHjGrSJD = false;
      bool FrGrfPBQao = false;
      bool cwwYeulhxK = false;
      bool XkWgUdiyMn = false;
      bool OWJtHwhqGX = false;
      string FZoSxhBpHh;
      string UQOFtqZfeE;
      string ZyPuZgtfbs;
      string loldWuFUKD;
      string jYZcqDkkNl;
      string WYtCKHJsrQ;
      string nVNNwfekiz;
      string lFUaTBYmDW;
      string wIRpWMtjTO;
      string kLbtPOLLfL;
      string YzBOARDShI;
      string hWpVTeDWqi;
      string kuRTNZcaLF;
      string pMGqywHDoF;
      string IaBKfNVGZk;
      string LnUwachhAZ;
      string ncHcSVQyXX;
      string XAgkZKsHmA;
      string EWBZsCqJQU;
      string NYCPQfSYqK;
      if(FZoSxhBpHh == YzBOARDShI){xWhCNLGiVQ = true;}
      else if(YzBOARDShI == FZoSxhBpHh){bMEFWbQnFJ = true;}
      if(UQOFtqZfeE == hWpVTeDWqi){jatAVQbgiQ = true;}
      else if(hWpVTeDWqi == UQOFtqZfeE){XHNVuSPtlT = true;}
      if(ZyPuZgtfbs == kuRTNZcaLF){dGhCJyxRUt = true;}
      else if(kuRTNZcaLF == ZyPuZgtfbs){kVUkuTVXgN = true;}
      if(loldWuFUKD == pMGqywHDoF){qTPcCgnzMh = true;}
      else if(pMGqywHDoF == loldWuFUKD){cHGwtGpTxN = true;}
      if(jYZcqDkkNl == IaBKfNVGZk){uHmAkmeCsz = true;}
      else if(IaBKfNVGZk == jYZcqDkkNl){ooimnkukBA = true;}
      if(WYtCKHJsrQ == LnUwachhAZ){EkpafqoerP = true;}
      else if(LnUwachhAZ == WYtCKHJsrQ){ryYHjGrSJD = true;}
      if(nVNNwfekiz == ncHcSVQyXX){OnObYPKRxn = true;}
      else if(ncHcSVQyXX == nVNNwfekiz){FrGrfPBQao = true;}
      if(lFUaTBYmDW == XAgkZKsHmA){ccUBUVSgRW = true;}
      if(wIRpWMtjTO == EWBZsCqJQU){TuYUoFdowL = true;}
      if(kLbtPOLLfL == NYCPQfSYqK){rIGxTHsLaV = true;}
      while(XAgkZKsHmA == lFUaTBYmDW){cwwYeulhxK = true;}
      while(EWBZsCqJQU == EWBZsCqJQU){XkWgUdiyMn = true;}
      while(NYCPQfSYqK == NYCPQfSYqK){OWJtHwhqGX = true;}
      if(xWhCNLGiVQ == true){xWhCNLGiVQ = false;}
      if(jatAVQbgiQ == true){jatAVQbgiQ = false;}
      if(dGhCJyxRUt == true){dGhCJyxRUt = false;}
      if(qTPcCgnzMh == true){qTPcCgnzMh = false;}
      if(uHmAkmeCsz == true){uHmAkmeCsz = false;}
      if(EkpafqoerP == true){EkpafqoerP = false;}
      if(OnObYPKRxn == true){OnObYPKRxn = false;}
      if(ccUBUVSgRW == true){ccUBUVSgRW = false;}
      if(TuYUoFdowL == true){TuYUoFdowL = false;}
      if(rIGxTHsLaV == true){rIGxTHsLaV = false;}
      if(bMEFWbQnFJ == true){bMEFWbQnFJ = false;}
      if(XHNVuSPtlT == true){XHNVuSPtlT = false;}
      if(kVUkuTVXgN == true){kVUkuTVXgN = false;}
      if(cHGwtGpTxN == true){cHGwtGpTxN = false;}
      if(ooimnkukBA == true){ooimnkukBA = false;}
      if(ryYHjGrSJD == true){ryYHjGrSJD = false;}
      if(FrGrfPBQao == true){FrGrfPBQao = false;}
      if(cwwYeulhxK == true){cwwYeulhxK = false;}
      if(XkWgUdiyMn == true){XkWgUdiyMn = false;}
      if(OWJtHwhqGX == true){OWJtHwhqGX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KJLXPGDTDV
{ 
  void NJBAwTkyAg()
  { 
      bool kYdhXjKUfm = false;
      bool FeFtcKNGjp = false;
      bool LyFDkhiIZo = false;
      bool SUZWWbDEkK = false;
      bool yoqiBaZAbI = false;
      bool OxJDnmTZxp = false;
      bool BBtqUjFiXA = false;
      bool HJVYqVGVCK = false;
      bool HigRZUKWii = false;
      bool HcHuJxtANQ = false;
      bool VqcaAEakMR = false;
      bool gxXlhRUcQA = false;
      bool ZiznseCaOt = false;
      bool aGHloPFFRV = false;
      bool sZJRCKFUMq = false;
      bool bRiNqlrnhV = false;
      bool CAVRpaolxR = false;
      bool MPLuGAYhlh = false;
      bool YhOXRJWttC = false;
      bool XRWwSsDrbb = false;
      string VHzKdDtXKX;
      string HHCGeToRHi;
      string mkwFqQECLh;
      string kmFOzMFsiG;
      string hhufVJzbku;
      string JuKpmjKsTN;
      string yrMclTCnHS;
      string OuhBAEpQih;
      string QcQPYpcObO;
      string CLZVHpVRtB;
      string HLUSgNMJoh;
      string tsJkwVbxEu;
      string qmMrQCVLsK;
      string iXWgaFIxiK;
      string dTYsUIBnZk;
      string OYNyKTybCd;
      string rAPezVWbKq;
      string NdNsRWOTWI;
      string BglIuJJXWG;
      string GftEScEssz;
      if(VHzKdDtXKX == HLUSgNMJoh){kYdhXjKUfm = true;}
      else if(HLUSgNMJoh == VHzKdDtXKX){VqcaAEakMR = true;}
      if(HHCGeToRHi == tsJkwVbxEu){FeFtcKNGjp = true;}
      else if(tsJkwVbxEu == HHCGeToRHi){gxXlhRUcQA = true;}
      if(mkwFqQECLh == qmMrQCVLsK){LyFDkhiIZo = true;}
      else if(qmMrQCVLsK == mkwFqQECLh){ZiznseCaOt = true;}
      if(kmFOzMFsiG == iXWgaFIxiK){SUZWWbDEkK = true;}
      else if(iXWgaFIxiK == kmFOzMFsiG){aGHloPFFRV = true;}
      if(hhufVJzbku == dTYsUIBnZk){yoqiBaZAbI = true;}
      else if(dTYsUIBnZk == hhufVJzbku){sZJRCKFUMq = true;}
      if(JuKpmjKsTN == OYNyKTybCd){OxJDnmTZxp = true;}
      else if(OYNyKTybCd == JuKpmjKsTN){bRiNqlrnhV = true;}
      if(yrMclTCnHS == rAPezVWbKq){BBtqUjFiXA = true;}
      else if(rAPezVWbKq == yrMclTCnHS){CAVRpaolxR = true;}
      if(OuhBAEpQih == NdNsRWOTWI){HJVYqVGVCK = true;}
      if(QcQPYpcObO == BglIuJJXWG){HigRZUKWii = true;}
      if(CLZVHpVRtB == GftEScEssz){HcHuJxtANQ = true;}
      while(NdNsRWOTWI == OuhBAEpQih){MPLuGAYhlh = true;}
      while(BglIuJJXWG == BglIuJJXWG){YhOXRJWttC = true;}
      while(GftEScEssz == GftEScEssz){XRWwSsDrbb = true;}
      if(kYdhXjKUfm == true){kYdhXjKUfm = false;}
      if(FeFtcKNGjp == true){FeFtcKNGjp = false;}
      if(LyFDkhiIZo == true){LyFDkhiIZo = false;}
      if(SUZWWbDEkK == true){SUZWWbDEkK = false;}
      if(yoqiBaZAbI == true){yoqiBaZAbI = false;}
      if(OxJDnmTZxp == true){OxJDnmTZxp = false;}
      if(BBtqUjFiXA == true){BBtqUjFiXA = false;}
      if(HJVYqVGVCK == true){HJVYqVGVCK = false;}
      if(HigRZUKWii == true){HigRZUKWii = false;}
      if(HcHuJxtANQ == true){HcHuJxtANQ = false;}
      if(VqcaAEakMR == true){VqcaAEakMR = false;}
      if(gxXlhRUcQA == true){gxXlhRUcQA = false;}
      if(ZiznseCaOt == true){ZiznseCaOt = false;}
      if(aGHloPFFRV == true){aGHloPFFRV = false;}
      if(sZJRCKFUMq == true){sZJRCKFUMq = false;}
      if(bRiNqlrnhV == true){bRiNqlrnhV = false;}
      if(CAVRpaolxR == true){CAVRpaolxR = false;}
      if(MPLuGAYhlh == true){MPLuGAYhlh = false;}
      if(YhOXRJWttC == true){YhOXRJWttC = false;}
      if(XRWwSsDrbb == true){XRWwSsDrbb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QFHKYBPAJG
{ 
  void NBzmsxTeWh()
  { 
      bool XPZJdVOpQz = false;
      bool ROlxWwVnwO = false;
      bool oouSwtkMOW = false;
      bool rIAWxHIihb = false;
      bool mjPpjwOVhb = false;
      bool IwjSKiTGNi = false;
      bool jBatHJNPAP = false;
      bool mmGUbFYEhA = false;
      bool ePdmNuXhMN = false;
      bool mBVyqkIVia = false;
      bool hzURnVpOqF = false;
      bool KOYMETWngL = false;
      bool kfClblQIcp = false;
      bool wCVGSftLyq = false;
      bool FIqGDYbItW = false;
      bool NUoXoBxhpC = false;
      bool EhlAJHsStX = false;
      bool ZLooFcnuiD = false;
      bool JHNGcaNxRQ = false;
      bool iLVwlXWqxw = false;
      string oYFNnzruUz;
      string VCuFbAgZVQ;
      string LtqpFmhgMT;
      string jhwWfxVfhA;
      string bfVceaBXMw;
      string IQIFbthPIA;
      string RKhBPnFYZd;
      string dBqVneYNKd;
      string kJTQKTYqtl;
      string OGXgiQxTNq;
      string UbyhRHYmQx;
      string UUEdPHqRpu;
      string OOenOXcKmX;
      string gEzSIILlzD;
      string tkZxQtBtQa;
      string ZfdRcGxJSt;
      string eOAsPQVlUH;
      string wERmBcnhXU;
      string WhsLxBagpC;
      string KBSFXekfgA;
      if(oYFNnzruUz == UbyhRHYmQx){XPZJdVOpQz = true;}
      else if(UbyhRHYmQx == oYFNnzruUz){hzURnVpOqF = true;}
      if(VCuFbAgZVQ == UUEdPHqRpu){ROlxWwVnwO = true;}
      else if(UUEdPHqRpu == VCuFbAgZVQ){KOYMETWngL = true;}
      if(LtqpFmhgMT == OOenOXcKmX){oouSwtkMOW = true;}
      else if(OOenOXcKmX == LtqpFmhgMT){kfClblQIcp = true;}
      if(jhwWfxVfhA == gEzSIILlzD){rIAWxHIihb = true;}
      else if(gEzSIILlzD == jhwWfxVfhA){wCVGSftLyq = true;}
      if(bfVceaBXMw == tkZxQtBtQa){mjPpjwOVhb = true;}
      else if(tkZxQtBtQa == bfVceaBXMw){FIqGDYbItW = true;}
      if(IQIFbthPIA == ZfdRcGxJSt){IwjSKiTGNi = true;}
      else if(ZfdRcGxJSt == IQIFbthPIA){NUoXoBxhpC = true;}
      if(RKhBPnFYZd == eOAsPQVlUH){jBatHJNPAP = true;}
      else if(eOAsPQVlUH == RKhBPnFYZd){EhlAJHsStX = true;}
      if(dBqVneYNKd == wERmBcnhXU){mmGUbFYEhA = true;}
      if(kJTQKTYqtl == WhsLxBagpC){ePdmNuXhMN = true;}
      if(OGXgiQxTNq == KBSFXekfgA){mBVyqkIVia = true;}
      while(wERmBcnhXU == dBqVneYNKd){ZLooFcnuiD = true;}
      while(WhsLxBagpC == WhsLxBagpC){JHNGcaNxRQ = true;}
      while(KBSFXekfgA == KBSFXekfgA){iLVwlXWqxw = true;}
      if(XPZJdVOpQz == true){XPZJdVOpQz = false;}
      if(ROlxWwVnwO == true){ROlxWwVnwO = false;}
      if(oouSwtkMOW == true){oouSwtkMOW = false;}
      if(rIAWxHIihb == true){rIAWxHIihb = false;}
      if(mjPpjwOVhb == true){mjPpjwOVhb = false;}
      if(IwjSKiTGNi == true){IwjSKiTGNi = false;}
      if(jBatHJNPAP == true){jBatHJNPAP = false;}
      if(mmGUbFYEhA == true){mmGUbFYEhA = false;}
      if(ePdmNuXhMN == true){ePdmNuXhMN = false;}
      if(mBVyqkIVia == true){mBVyqkIVia = false;}
      if(hzURnVpOqF == true){hzURnVpOqF = false;}
      if(KOYMETWngL == true){KOYMETWngL = false;}
      if(kfClblQIcp == true){kfClblQIcp = false;}
      if(wCVGSftLyq == true){wCVGSftLyq = false;}
      if(FIqGDYbItW == true){FIqGDYbItW = false;}
      if(NUoXoBxhpC == true){NUoXoBxhpC = false;}
      if(EhlAJHsStX == true){EhlAJHsStX = false;}
      if(ZLooFcnuiD == true){ZLooFcnuiD = false;}
      if(JHNGcaNxRQ == true){JHNGcaNxRQ = false;}
      if(iLVwlXWqxw == true){iLVwlXWqxw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FNWHHTKGCA
{ 
  void hiVJfTRpDE()
  { 
      bool TPmlMnGIJq = false;
      bool MKeUBtmfwW = false;
      bool jUPxHkgZyn = false;
      bool uNrSujJNal = false;
      bool EDUqbemGcu = false;
      bool xKHWazzoeb = false;
      bool GgKUwzSMYQ = false;
      bool jZEJSfzYVb = false;
      bool yawCqkGUru = false;
      bool jUhzfXsAuc = false;
      bool MahMKWFxEt = false;
      bool AaSCdejHdK = false;
      bool rxUcfPqEdt = false;
      bool mzcsPWsjrT = false;
      bool eIQxuJBeVA = false;
      bool nkWjjOGEft = false;
      bool fATJGBxZmG = false;
      bool lAPJejgWhW = false;
      bool OLicGCbsJA = false;
      bool QnDxneoGps = false;
      string xPojrkSlfH;
      string AXtFCJkKLJ;
      string pMKsiHcQEO;
      string SQHyBlUgGG;
      string TajSIoHCjG;
      string SZekSjEuAk;
      string IBhQniQuEQ;
      string oDEEpOcrks;
      string zafxwrlWfQ;
      string gYgUyRsSdZ;
      string YMxTROVauD;
      string HMJGkgUjUu;
      string xtOmiPWiFX;
      string UKNLTmcLfg;
      string WLbcITOZjR;
      string xJxicexJjB;
      string qlUWhxzymx;
      string EIDnYkRldP;
      string AxznaKMeho;
      string pSadojpEtL;
      if(xPojrkSlfH == YMxTROVauD){TPmlMnGIJq = true;}
      else if(YMxTROVauD == xPojrkSlfH){MahMKWFxEt = true;}
      if(AXtFCJkKLJ == HMJGkgUjUu){MKeUBtmfwW = true;}
      else if(HMJGkgUjUu == AXtFCJkKLJ){AaSCdejHdK = true;}
      if(pMKsiHcQEO == xtOmiPWiFX){jUPxHkgZyn = true;}
      else if(xtOmiPWiFX == pMKsiHcQEO){rxUcfPqEdt = true;}
      if(SQHyBlUgGG == UKNLTmcLfg){uNrSujJNal = true;}
      else if(UKNLTmcLfg == SQHyBlUgGG){mzcsPWsjrT = true;}
      if(TajSIoHCjG == WLbcITOZjR){EDUqbemGcu = true;}
      else if(WLbcITOZjR == TajSIoHCjG){eIQxuJBeVA = true;}
      if(SZekSjEuAk == xJxicexJjB){xKHWazzoeb = true;}
      else if(xJxicexJjB == SZekSjEuAk){nkWjjOGEft = true;}
      if(IBhQniQuEQ == qlUWhxzymx){GgKUwzSMYQ = true;}
      else if(qlUWhxzymx == IBhQniQuEQ){fATJGBxZmG = true;}
      if(oDEEpOcrks == EIDnYkRldP){jZEJSfzYVb = true;}
      if(zafxwrlWfQ == AxznaKMeho){yawCqkGUru = true;}
      if(gYgUyRsSdZ == pSadojpEtL){jUhzfXsAuc = true;}
      while(EIDnYkRldP == oDEEpOcrks){lAPJejgWhW = true;}
      while(AxznaKMeho == AxznaKMeho){OLicGCbsJA = true;}
      while(pSadojpEtL == pSadojpEtL){QnDxneoGps = true;}
      if(TPmlMnGIJq == true){TPmlMnGIJq = false;}
      if(MKeUBtmfwW == true){MKeUBtmfwW = false;}
      if(jUPxHkgZyn == true){jUPxHkgZyn = false;}
      if(uNrSujJNal == true){uNrSujJNal = false;}
      if(EDUqbemGcu == true){EDUqbemGcu = false;}
      if(xKHWazzoeb == true){xKHWazzoeb = false;}
      if(GgKUwzSMYQ == true){GgKUwzSMYQ = false;}
      if(jZEJSfzYVb == true){jZEJSfzYVb = false;}
      if(yawCqkGUru == true){yawCqkGUru = false;}
      if(jUhzfXsAuc == true){jUhzfXsAuc = false;}
      if(MahMKWFxEt == true){MahMKWFxEt = false;}
      if(AaSCdejHdK == true){AaSCdejHdK = false;}
      if(rxUcfPqEdt == true){rxUcfPqEdt = false;}
      if(mzcsPWsjrT == true){mzcsPWsjrT = false;}
      if(eIQxuJBeVA == true){eIQxuJBeVA = false;}
      if(nkWjjOGEft == true){nkWjjOGEft = false;}
      if(fATJGBxZmG == true){fATJGBxZmG = false;}
      if(lAPJejgWhW == true){lAPJejgWhW = false;}
      if(OLicGCbsJA == true){OLicGCbsJA = false;}
      if(QnDxneoGps == true){QnDxneoGps = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSHXTZNHPM
{ 
  void CKKYVJnHAH()
  { 
      bool zeWuFQtafp = false;
      bool nxgOlWiCOr = false;
      bool GWhkiBHPgF = false;
      bool ZEtUJZEcgf = false;
      bool OUdinIXKWF = false;
      bool PnCOFbwkMD = false;
      bool JdtZPiDMEL = false;
      bool RFUhcksyxa = false;
      bool cwsaplCeOh = false;
      bool cSQcWkaDTE = false;
      bool ELGKnJTTkU = false;
      bool ixnlZMjTjd = false;
      bool gYxWiyoqLr = false;
      bool KoesVRphlf = false;
      bool RhttyeeeDJ = false;
      bool AGSoWfNibo = false;
      bool UbIrKsStPI = false;
      bool WCgDLydDYD = false;
      bool SKnBqDVoVp = false;
      bool DGFxLpZCiE = false;
      string hiWRUoZsMQ;
      string IxbgZRQedA;
      string StSAcNjelp;
      string hsQglZyWmr;
      string ZzrdRlBFPC;
      string EJZhwmQWoH;
      string EuHViPftuA;
      string TtqlaTCoiq;
      string MdOikYTiky;
      string IahfmerVtC;
      string GHKPiKSnHc;
      string jbnxtafYkK;
      string uxIwqrLKzu;
      string bgtfkETyza;
      string GebHOgmjkM;
      string ySkjGIyOYq;
      string yHoLBCgHMo;
      string GgYJDQUAgJ;
      string FbYmxIwKZb;
      string GFZIcypQGL;
      if(hiWRUoZsMQ == GHKPiKSnHc){zeWuFQtafp = true;}
      else if(GHKPiKSnHc == hiWRUoZsMQ){ELGKnJTTkU = true;}
      if(IxbgZRQedA == jbnxtafYkK){nxgOlWiCOr = true;}
      else if(jbnxtafYkK == IxbgZRQedA){ixnlZMjTjd = true;}
      if(StSAcNjelp == uxIwqrLKzu){GWhkiBHPgF = true;}
      else if(uxIwqrLKzu == StSAcNjelp){gYxWiyoqLr = true;}
      if(hsQglZyWmr == bgtfkETyza){ZEtUJZEcgf = true;}
      else if(bgtfkETyza == hsQglZyWmr){KoesVRphlf = true;}
      if(ZzrdRlBFPC == GebHOgmjkM){OUdinIXKWF = true;}
      else if(GebHOgmjkM == ZzrdRlBFPC){RhttyeeeDJ = true;}
      if(EJZhwmQWoH == ySkjGIyOYq){PnCOFbwkMD = true;}
      else if(ySkjGIyOYq == EJZhwmQWoH){AGSoWfNibo = true;}
      if(EuHViPftuA == yHoLBCgHMo){JdtZPiDMEL = true;}
      else if(yHoLBCgHMo == EuHViPftuA){UbIrKsStPI = true;}
      if(TtqlaTCoiq == GgYJDQUAgJ){RFUhcksyxa = true;}
      if(MdOikYTiky == FbYmxIwKZb){cwsaplCeOh = true;}
      if(IahfmerVtC == GFZIcypQGL){cSQcWkaDTE = true;}
      while(GgYJDQUAgJ == TtqlaTCoiq){WCgDLydDYD = true;}
      while(FbYmxIwKZb == FbYmxIwKZb){SKnBqDVoVp = true;}
      while(GFZIcypQGL == GFZIcypQGL){DGFxLpZCiE = true;}
      if(zeWuFQtafp == true){zeWuFQtafp = false;}
      if(nxgOlWiCOr == true){nxgOlWiCOr = false;}
      if(GWhkiBHPgF == true){GWhkiBHPgF = false;}
      if(ZEtUJZEcgf == true){ZEtUJZEcgf = false;}
      if(OUdinIXKWF == true){OUdinIXKWF = false;}
      if(PnCOFbwkMD == true){PnCOFbwkMD = false;}
      if(JdtZPiDMEL == true){JdtZPiDMEL = false;}
      if(RFUhcksyxa == true){RFUhcksyxa = false;}
      if(cwsaplCeOh == true){cwsaplCeOh = false;}
      if(cSQcWkaDTE == true){cSQcWkaDTE = false;}
      if(ELGKnJTTkU == true){ELGKnJTTkU = false;}
      if(ixnlZMjTjd == true){ixnlZMjTjd = false;}
      if(gYxWiyoqLr == true){gYxWiyoqLr = false;}
      if(KoesVRphlf == true){KoesVRphlf = false;}
      if(RhttyeeeDJ == true){RhttyeeeDJ = false;}
      if(AGSoWfNibo == true){AGSoWfNibo = false;}
      if(UbIrKsStPI == true){UbIrKsStPI = false;}
      if(WCgDLydDYD == true){WCgDLydDYD = false;}
      if(SKnBqDVoVp == true){SKnBqDVoVp = false;}
      if(DGFxLpZCiE == true){DGFxLpZCiE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FHOCYZULAT
{ 
  void KNfVYxPxji()
  { 
      bool yxxCTmyVGq = false;
      bool kkXDYgMuyr = false;
      bool fUcaoaTFuU = false;
      bool wsYIeYpYla = false;
      bool FLPhujzbjf = false;
      bool hYVlwdUVMr = false;
      bool TsZktrMPYz = false;
      bool pmIXmUEteE = false;
      bool brUOlXXlLA = false;
      bool DTMsHLkdnD = false;
      bool XjCjotPxzb = false;
      bool ZZqHQaYKzW = false;
      bool UZDXwWaOQa = false;
      bool iZGbgrpjZq = false;
      bool HZmjadcEcg = false;
      bool maeQhxgdnS = false;
      bool TAgYrATOaX = false;
      bool jnkHPumSxR = false;
      bool sVkjnItosi = false;
      bool LLwGXGrOra = false;
      string npIYPDlhUd;
      string YJROOzlKZf;
      string QitzMOBJtm;
      string RsQzUVsDkB;
      string cTCgYmkftX;
      string tEySKFwJMA;
      string BbnhMfsSss;
      string GiZXDxfMZY;
      string dUOVrNtxnP;
      string YjqjzAeTUs;
      string tSmBRLdZPN;
      string YiimWgMRpz;
      string kudcTWqoYC;
      string RLrgeKhNDg;
      string iUhaqpAENS;
      string mNdVHyoKhu;
      string TnBNwNqCHL;
      string yzOIPQNDld;
      string VmbFOEgWZg;
      string VXeIMuTUdc;
      if(npIYPDlhUd == tSmBRLdZPN){yxxCTmyVGq = true;}
      else if(tSmBRLdZPN == npIYPDlhUd){XjCjotPxzb = true;}
      if(YJROOzlKZf == YiimWgMRpz){kkXDYgMuyr = true;}
      else if(YiimWgMRpz == YJROOzlKZf){ZZqHQaYKzW = true;}
      if(QitzMOBJtm == kudcTWqoYC){fUcaoaTFuU = true;}
      else if(kudcTWqoYC == QitzMOBJtm){UZDXwWaOQa = true;}
      if(RsQzUVsDkB == RLrgeKhNDg){wsYIeYpYla = true;}
      else if(RLrgeKhNDg == RsQzUVsDkB){iZGbgrpjZq = true;}
      if(cTCgYmkftX == iUhaqpAENS){FLPhujzbjf = true;}
      else if(iUhaqpAENS == cTCgYmkftX){HZmjadcEcg = true;}
      if(tEySKFwJMA == mNdVHyoKhu){hYVlwdUVMr = true;}
      else if(mNdVHyoKhu == tEySKFwJMA){maeQhxgdnS = true;}
      if(BbnhMfsSss == TnBNwNqCHL){TsZktrMPYz = true;}
      else if(TnBNwNqCHL == BbnhMfsSss){TAgYrATOaX = true;}
      if(GiZXDxfMZY == yzOIPQNDld){pmIXmUEteE = true;}
      if(dUOVrNtxnP == VmbFOEgWZg){brUOlXXlLA = true;}
      if(YjqjzAeTUs == VXeIMuTUdc){DTMsHLkdnD = true;}
      while(yzOIPQNDld == GiZXDxfMZY){jnkHPumSxR = true;}
      while(VmbFOEgWZg == VmbFOEgWZg){sVkjnItosi = true;}
      while(VXeIMuTUdc == VXeIMuTUdc){LLwGXGrOra = true;}
      if(yxxCTmyVGq == true){yxxCTmyVGq = false;}
      if(kkXDYgMuyr == true){kkXDYgMuyr = false;}
      if(fUcaoaTFuU == true){fUcaoaTFuU = false;}
      if(wsYIeYpYla == true){wsYIeYpYla = false;}
      if(FLPhujzbjf == true){FLPhujzbjf = false;}
      if(hYVlwdUVMr == true){hYVlwdUVMr = false;}
      if(TsZktrMPYz == true){TsZktrMPYz = false;}
      if(pmIXmUEteE == true){pmIXmUEteE = false;}
      if(brUOlXXlLA == true){brUOlXXlLA = false;}
      if(DTMsHLkdnD == true){DTMsHLkdnD = false;}
      if(XjCjotPxzb == true){XjCjotPxzb = false;}
      if(ZZqHQaYKzW == true){ZZqHQaYKzW = false;}
      if(UZDXwWaOQa == true){UZDXwWaOQa = false;}
      if(iZGbgrpjZq == true){iZGbgrpjZq = false;}
      if(HZmjadcEcg == true){HZmjadcEcg = false;}
      if(maeQhxgdnS == true){maeQhxgdnS = false;}
      if(TAgYrATOaX == true){TAgYrATOaX = false;}
      if(jnkHPumSxR == true){jnkHPumSxR = false;}
      if(sVkjnItosi == true){sVkjnItosi = false;}
      if(LLwGXGrOra == true){LLwGXGrOra = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUTUJECDNB
{ 
  void ykliVTyrmc()
  { 
      bool GFuqKSJkMB = false;
      bool WGTmCUAMeL = false;
      bool uaXZGXPitn = false;
      bool JVjBReISdK = false;
      bool gcgLhqpZeY = false;
      bool meodsehVjm = false;
      bool CapYrBVRVW = false;
      bool MhiTdStMqP = false;
      bool goDVAdgGHl = false;
      bool xmhqHGlITg = false;
      bool UXEHMFuUzZ = false;
      bool kUdUFNWUXN = false;
      bool UOKiZZzqLX = false;
      bool gkrKtJkwIu = false;
      bool iLHhBbIMlt = false;
      bool iQjGMFNUgm = false;
      bool FDJbszcTZw = false;
      bool bZMceIHbhy = false;
      bool QlFQnPBlxn = false;
      bool uPOVoeCfnB = false;
      string xBqPHZKoMB;
      string MxgBJciStG;
      string FeAdOzEYUi;
      string MoRFOeGbjQ;
      string idKDSNYkol;
      string LyMFtRAMBH;
      string VlTdoWfbld;
      string VGhcWaTxLB;
      string aSjiWOcLKw;
      string esacuxKfOw;
      string hxzKPEPihT;
      string xDBzgCBjGZ;
      string sTQozcfFhY;
      string QnhPTcTYTS;
      string yscqzarbus;
      string uZZnCNfJLm;
      string YKBICJUlfD;
      string hcPnbApZpX;
      string kEJodqNsNF;
      string xKNgsnqUoo;
      if(xBqPHZKoMB == hxzKPEPihT){GFuqKSJkMB = true;}
      else if(hxzKPEPihT == xBqPHZKoMB){UXEHMFuUzZ = true;}
      if(MxgBJciStG == xDBzgCBjGZ){WGTmCUAMeL = true;}
      else if(xDBzgCBjGZ == MxgBJciStG){kUdUFNWUXN = true;}
      if(FeAdOzEYUi == sTQozcfFhY){uaXZGXPitn = true;}
      else if(sTQozcfFhY == FeAdOzEYUi){UOKiZZzqLX = true;}
      if(MoRFOeGbjQ == QnhPTcTYTS){JVjBReISdK = true;}
      else if(QnhPTcTYTS == MoRFOeGbjQ){gkrKtJkwIu = true;}
      if(idKDSNYkol == yscqzarbus){gcgLhqpZeY = true;}
      else if(yscqzarbus == idKDSNYkol){iLHhBbIMlt = true;}
      if(LyMFtRAMBH == uZZnCNfJLm){meodsehVjm = true;}
      else if(uZZnCNfJLm == LyMFtRAMBH){iQjGMFNUgm = true;}
      if(VlTdoWfbld == YKBICJUlfD){CapYrBVRVW = true;}
      else if(YKBICJUlfD == VlTdoWfbld){FDJbszcTZw = true;}
      if(VGhcWaTxLB == hcPnbApZpX){MhiTdStMqP = true;}
      if(aSjiWOcLKw == kEJodqNsNF){goDVAdgGHl = true;}
      if(esacuxKfOw == xKNgsnqUoo){xmhqHGlITg = true;}
      while(hcPnbApZpX == VGhcWaTxLB){bZMceIHbhy = true;}
      while(kEJodqNsNF == kEJodqNsNF){QlFQnPBlxn = true;}
      while(xKNgsnqUoo == xKNgsnqUoo){uPOVoeCfnB = true;}
      if(GFuqKSJkMB == true){GFuqKSJkMB = false;}
      if(WGTmCUAMeL == true){WGTmCUAMeL = false;}
      if(uaXZGXPitn == true){uaXZGXPitn = false;}
      if(JVjBReISdK == true){JVjBReISdK = false;}
      if(gcgLhqpZeY == true){gcgLhqpZeY = false;}
      if(meodsehVjm == true){meodsehVjm = false;}
      if(CapYrBVRVW == true){CapYrBVRVW = false;}
      if(MhiTdStMqP == true){MhiTdStMqP = false;}
      if(goDVAdgGHl == true){goDVAdgGHl = false;}
      if(xmhqHGlITg == true){xmhqHGlITg = false;}
      if(UXEHMFuUzZ == true){UXEHMFuUzZ = false;}
      if(kUdUFNWUXN == true){kUdUFNWUXN = false;}
      if(UOKiZZzqLX == true){UOKiZZzqLX = false;}
      if(gkrKtJkwIu == true){gkrKtJkwIu = false;}
      if(iLHhBbIMlt == true){iLHhBbIMlt = false;}
      if(iQjGMFNUgm == true){iQjGMFNUgm = false;}
      if(FDJbszcTZw == true){FDJbszcTZw = false;}
      if(bZMceIHbhy == true){bZMceIHbhy = false;}
      if(QlFQnPBlxn == true){QlFQnPBlxn = false;}
      if(uPOVoeCfnB == true){uPOVoeCfnB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OESQGOSVGJ
{ 
  void dTZHEqcDja()
  { 
      bool QCxkkuyYjB = false;
      bool xbcSdbRhNn = false;
      bool NpuNFrByPU = false;
      bool gUNFXJTopc = false;
      bool aMSdrYTUDn = false;
      bool rjWCAZHjes = false;
      bool tAJOUcNWuU = false;
      bool HbrjNAXQUg = false;
      bool XfubcwyLFx = false;
      bool BjKwhaDDIP = false;
      bool LwZifPrlnz = false;
      bool BpPxUOFglY = false;
      bool dCRxSXRuBm = false;
      bool xUIEVbGMuM = false;
      bool DLWGwKTMaT = false;
      bool VVQikIebPI = false;
      bool xwjBBghKbs = false;
      bool HrlYVSeKBI = false;
      bool DFTgQaDZSM = false;
      bool xdwmPGaVEO = false;
      string RUdOBwIRMF;
      string afxWIjomUm;
      string SoxIspqWMC;
      string PJoShqHVpM;
      string HkEjwUTSVI;
      string fFTZybWUVK;
      string FlFKoRqdnR;
      string cSxIehkMMX;
      string WXADVJoPUF;
      string TlzfGVesue;
      string doeEfMILtP;
      string qKIxngkCnf;
      string caJhxpTRBI;
      string CqRgtgsuWI;
      string BcVEOJdBqZ;
      string kcEOBDfwHp;
      string sqJkNAsaDG;
      string noefezFETn;
      string MRZbXYlCfp;
      string AwngPJSjqN;
      if(RUdOBwIRMF == doeEfMILtP){QCxkkuyYjB = true;}
      else if(doeEfMILtP == RUdOBwIRMF){LwZifPrlnz = true;}
      if(afxWIjomUm == qKIxngkCnf){xbcSdbRhNn = true;}
      else if(qKIxngkCnf == afxWIjomUm){BpPxUOFglY = true;}
      if(SoxIspqWMC == caJhxpTRBI){NpuNFrByPU = true;}
      else if(caJhxpTRBI == SoxIspqWMC){dCRxSXRuBm = true;}
      if(PJoShqHVpM == CqRgtgsuWI){gUNFXJTopc = true;}
      else if(CqRgtgsuWI == PJoShqHVpM){xUIEVbGMuM = true;}
      if(HkEjwUTSVI == BcVEOJdBqZ){aMSdrYTUDn = true;}
      else if(BcVEOJdBqZ == HkEjwUTSVI){DLWGwKTMaT = true;}
      if(fFTZybWUVK == kcEOBDfwHp){rjWCAZHjes = true;}
      else if(kcEOBDfwHp == fFTZybWUVK){VVQikIebPI = true;}
      if(FlFKoRqdnR == sqJkNAsaDG){tAJOUcNWuU = true;}
      else if(sqJkNAsaDG == FlFKoRqdnR){xwjBBghKbs = true;}
      if(cSxIehkMMX == noefezFETn){HbrjNAXQUg = true;}
      if(WXADVJoPUF == MRZbXYlCfp){XfubcwyLFx = true;}
      if(TlzfGVesue == AwngPJSjqN){BjKwhaDDIP = true;}
      while(noefezFETn == cSxIehkMMX){HrlYVSeKBI = true;}
      while(MRZbXYlCfp == MRZbXYlCfp){DFTgQaDZSM = true;}
      while(AwngPJSjqN == AwngPJSjqN){xdwmPGaVEO = true;}
      if(QCxkkuyYjB == true){QCxkkuyYjB = false;}
      if(xbcSdbRhNn == true){xbcSdbRhNn = false;}
      if(NpuNFrByPU == true){NpuNFrByPU = false;}
      if(gUNFXJTopc == true){gUNFXJTopc = false;}
      if(aMSdrYTUDn == true){aMSdrYTUDn = false;}
      if(rjWCAZHjes == true){rjWCAZHjes = false;}
      if(tAJOUcNWuU == true){tAJOUcNWuU = false;}
      if(HbrjNAXQUg == true){HbrjNAXQUg = false;}
      if(XfubcwyLFx == true){XfubcwyLFx = false;}
      if(BjKwhaDDIP == true){BjKwhaDDIP = false;}
      if(LwZifPrlnz == true){LwZifPrlnz = false;}
      if(BpPxUOFglY == true){BpPxUOFglY = false;}
      if(dCRxSXRuBm == true){dCRxSXRuBm = false;}
      if(xUIEVbGMuM == true){xUIEVbGMuM = false;}
      if(DLWGwKTMaT == true){DLWGwKTMaT = false;}
      if(VVQikIebPI == true){VVQikIebPI = false;}
      if(xwjBBghKbs == true){xwjBBghKbs = false;}
      if(HrlYVSeKBI == true){HrlYVSeKBI = false;}
      if(DFTgQaDZSM == true){DFTgQaDZSM = false;}
      if(xdwmPGaVEO == true){xdwmPGaVEO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KANETFTHJI
{ 
  void ugBTkfAAdA()
  { 
      bool yVHSwoVIik = false;
      bool CkDMrhxTts = false;
      bool KiBVEcbZWT = false;
      bool yyeeJTKEJn = false;
      bool LyEheOmLoX = false;
      bool LpmriPTkOT = false;
      bool NwkPlEGXCX = false;
      bool WrKGhLdSqp = false;
      bool oPjzHIKlut = false;
      bool AYppaPMoua = false;
      bool IOJQASegKW = false;
      bool kAtXdxLlHd = false;
      bool sTcIXxCUeS = false;
      bool znWPhaGSyo = false;
      bool ddaXIzeRLd = false;
      bool DahRgnkBrD = false;
      bool QJBrXxddpC = false;
      bool prnSAPrEzY = false;
      bool SjIBOXFFit = false;
      bool oFZuXTbizL = false;
      string MVBEgYHLtg;
      string RqZtEXxrqh;
      string StgOysERGa;
      string htCwmgOmSV;
      string aGkPLKKVXZ;
      string ooPBxRnmGn;
      string ToFSyXndHX;
      string JKYVGLIQCm;
      string hhtgksdBzU;
      string sbfdBlBRQn;
      string VgOAPePttk;
      string IWjTGluXhF;
      string smelegduUU;
      string KqzOQBStQF;
      string cjHNMVqLXO;
      string pcjLtiCcUi;
      string AUZYaRWVDE;
      string SBHbbJfQZI;
      string pSXFdgGnTg;
      string zpYhFIKhlt;
      if(MVBEgYHLtg == VgOAPePttk){yVHSwoVIik = true;}
      else if(VgOAPePttk == MVBEgYHLtg){IOJQASegKW = true;}
      if(RqZtEXxrqh == IWjTGluXhF){CkDMrhxTts = true;}
      else if(IWjTGluXhF == RqZtEXxrqh){kAtXdxLlHd = true;}
      if(StgOysERGa == smelegduUU){KiBVEcbZWT = true;}
      else if(smelegduUU == StgOysERGa){sTcIXxCUeS = true;}
      if(htCwmgOmSV == KqzOQBStQF){yyeeJTKEJn = true;}
      else if(KqzOQBStQF == htCwmgOmSV){znWPhaGSyo = true;}
      if(aGkPLKKVXZ == cjHNMVqLXO){LyEheOmLoX = true;}
      else if(cjHNMVqLXO == aGkPLKKVXZ){ddaXIzeRLd = true;}
      if(ooPBxRnmGn == pcjLtiCcUi){LpmriPTkOT = true;}
      else if(pcjLtiCcUi == ooPBxRnmGn){DahRgnkBrD = true;}
      if(ToFSyXndHX == AUZYaRWVDE){NwkPlEGXCX = true;}
      else if(AUZYaRWVDE == ToFSyXndHX){QJBrXxddpC = true;}
      if(JKYVGLIQCm == SBHbbJfQZI){WrKGhLdSqp = true;}
      if(hhtgksdBzU == pSXFdgGnTg){oPjzHIKlut = true;}
      if(sbfdBlBRQn == zpYhFIKhlt){AYppaPMoua = true;}
      while(SBHbbJfQZI == JKYVGLIQCm){prnSAPrEzY = true;}
      while(pSXFdgGnTg == pSXFdgGnTg){SjIBOXFFit = true;}
      while(zpYhFIKhlt == zpYhFIKhlt){oFZuXTbizL = true;}
      if(yVHSwoVIik == true){yVHSwoVIik = false;}
      if(CkDMrhxTts == true){CkDMrhxTts = false;}
      if(KiBVEcbZWT == true){KiBVEcbZWT = false;}
      if(yyeeJTKEJn == true){yyeeJTKEJn = false;}
      if(LyEheOmLoX == true){LyEheOmLoX = false;}
      if(LpmriPTkOT == true){LpmriPTkOT = false;}
      if(NwkPlEGXCX == true){NwkPlEGXCX = false;}
      if(WrKGhLdSqp == true){WrKGhLdSqp = false;}
      if(oPjzHIKlut == true){oPjzHIKlut = false;}
      if(AYppaPMoua == true){AYppaPMoua = false;}
      if(IOJQASegKW == true){IOJQASegKW = false;}
      if(kAtXdxLlHd == true){kAtXdxLlHd = false;}
      if(sTcIXxCUeS == true){sTcIXxCUeS = false;}
      if(znWPhaGSyo == true){znWPhaGSyo = false;}
      if(ddaXIzeRLd == true){ddaXIzeRLd = false;}
      if(DahRgnkBrD == true){DahRgnkBrD = false;}
      if(QJBrXxddpC == true){QJBrXxddpC = false;}
      if(prnSAPrEzY == true){prnSAPrEzY = false;}
      if(SjIBOXFFit == true){SjIBOXFFit = false;}
      if(oFZuXTbizL == true){oFZuXTbizL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NCPRAGATBA
{ 
  void ZGaxlNgQOh()
  { 
      bool usBJKaYAXI = false;
      bool nbxQKfLkdE = false;
      bool wpsdguCcex = false;
      bool bFttGaUSPw = false;
      bool OKWPEIGjuZ = false;
      bool XRApoEAWbP = false;
      bool YuUagigDKj = false;
      bool LsUgolTcYX = false;
      bool nRgFYJEEEC = false;
      bool axpAXTowiV = false;
      bool bDZLNewSBD = false;
      bool kWyDbGNPBW = false;
      bool dczHINCTJV = false;
      bool xXtCwjqVqt = false;
      bool NlCBRDzmYQ = false;
      bool FYtLrzERCA = false;
      bool cbJeFMcuHq = false;
      bool PrYHJrZxpF = false;
      bool NPurQXchKx = false;
      bool fZTqQkbXuE = false;
      string ftOBLXbHKf;
      string pHrrWxVKjL;
      string YDukDuGdlL;
      string IjCoXSWMLI;
      string CyciouyWGm;
      string GqXPNcycyQ;
      string RxUyXGEDUD;
      string aJzbIZZLwI;
      string wjXzFRLmau;
      string TsOuqFddLi;
      string ptCCMxrwGn;
      string ClgpTgZVsG;
      string tRcYigtDjD;
      string wuANRChUlI;
      string YPgmsgMYaJ;
      string fIkFnYRcSe;
      string CnLCrGlSXR;
      string zEikgejpfC;
      string UVcaXmKuYs;
      string jEBGFjDeul;
      if(ftOBLXbHKf == ptCCMxrwGn){usBJKaYAXI = true;}
      else if(ptCCMxrwGn == ftOBLXbHKf){bDZLNewSBD = true;}
      if(pHrrWxVKjL == ClgpTgZVsG){nbxQKfLkdE = true;}
      else if(ClgpTgZVsG == pHrrWxVKjL){kWyDbGNPBW = true;}
      if(YDukDuGdlL == tRcYigtDjD){wpsdguCcex = true;}
      else if(tRcYigtDjD == YDukDuGdlL){dczHINCTJV = true;}
      if(IjCoXSWMLI == wuANRChUlI){bFttGaUSPw = true;}
      else if(wuANRChUlI == IjCoXSWMLI){xXtCwjqVqt = true;}
      if(CyciouyWGm == YPgmsgMYaJ){OKWPEIGjuZ = true;}
      else if(YPgmsgMYaJ == CyciouyWGm){NlCBRDzmYQ = true;}
      if(GqXPNcycyQ == fIkFnYRcSe){XRApoEAWbP = true;}
      else if(fIkFnYRcSe == GqXPNcycyQ){FYtLrzERCA = true;}
      if(RxUyXGEDUD == CnLCrGlSXR){YuUagigDKj = true;}
      else if(CnLCrGlSXR == RxUyXGEDUD){cbJeFMcuHq = true;}
      if(aJzbIZZLwI == zEikgejpfC){LsUgolTcYX = true;}
      if(wjXzFRLmau == UVcaXmKuYs){nRgFYJEEEC = true;}
      if(TsOuqFddLi == jEBGFjDeul){axpAXTowiV = true;}
      while(zEikgejpfC == aJzbIZZLwI){PrYHJrZxpF = true;}
      while(UVcaXmKuYs == UVcaXmKuYs){NPurQXchKx = true;}
      while(jEBGFjDeul == jEBGFjDeul){fZTqQkbXuE = true;}
      if(usBJKaYAXI == true){usBJKaYAXI = false;}
      if(nbxQKfLkdE == true){nbxQKfLkdE = false;}
      if(wpsdguCcex == true){wpsdguCcex = false;}
      if(bFttGaUSPw == true){bFttGaUSPw = false;}
      if(OKWPEIGjuZ == true){OKWPEIGjuZ = false;}
      if(XRApoEAWbP == true){XRApoEAWbP = false;}
      if(YuUagigDKj == true){YuUagigDKj = false;}
      if(LsUgolTcYX == true){LsUgolTcYX = false;}
      if(nRgFYJEEEC == true){nRgFYJEEEC = false;}
      if(axpAXTowiV == true){axpAXTowiV = false;}
      if(bDZLNewSBD == true){bDZLNewSBD = false;}
      if(kWyDbGNPBW == true){kWyDbGNPBW = false;}
      if(dczHINCTJV == true){dczHINCTJV = false;}
      if(xXtCwjqVqt == true){xXtCwjqVqt = false;}
      if(NlCBRDzmYQ == true){NlCBRDzmYQ = false;}
      if(FYtLrzERCA == true){FYtLrzERCA = false;}
      if(cbJeFMcuHq == true){cbJeFMcuHq = false;}
      if(PrYHJrZxpF == true){PrYHJrZxpF = false;}
      if(NPurQXchKx == true){NPurQXchKx = false;}
      if(fZTqQkbXuE == true){fZTqQkbXuE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NYCBAQWEFE
{ 
  void HeMzCJNddV()
  { 
      bool HrGfhwqgsD = false;
      bool xOPjPEHkdJ = false;
      bool jqCDaWRlUK = false;
      bool gNdAfDBPBf = false;
      bool qeejxbLlRQ = false;
      bool LxSFlQoCEK = false;
      bool eELiWjjOEM = false;
      bool DrjyRFLSFz = false;
      bool KeUDyitYOO = false;
      bool NyKpBlTwNN = false;
      bool rxhENTMUmg = false;
      bool FWxFAzjIjm = false;
      bool oKzoyFgtwe = false;
      bool kOErGNxPpe = false;
      bool WZlgJqAEoC = false;
      bool CLMaXgxrGH = false;
      bool lSXHupREzl = false;
      bool CUREQOYRfG = false;
      bool EcEtcZBdUZ = false;
      bool QEIirDBdlS = false;
      string ZOTHaRSYaD;
      string fLqGWcuqCJ;
      string gLafhGNIft;
      string dbYxOYTeiu;
      string cPdBoIBVfy;
      string nGpADOmnZU;
      string DKsfZEltqx;
      string JPIGfQhZqY;
      string FrbgGWlXsA;
      string lfENqSWxbj;
      string VHdioXyiUl;
      string gNwAPLhLZD;
      string ROAqLdLtON;
      string tjxGCxNsri;
      string XCDHTXiEyf;
      string kKXYSHHmWK;
      string MDTGrwPpxR;
      string xnTqeOKsXm;
      string uHwiciLYmt;
      string paVgVThwOW;
      if(ZOTHaRSYaD == VHdioXyiUl){HrGfhwqgsD = true;}
      else if(VHdioXyiUl == ZOTHaRSYaD){rxhENTMUmg = true;}
      if(fLqGWcuqCJ == gNwAPLhLZD){xOPjPEHkdJ = true;}
      else if(gNwAPLhLZD == fLqGWcuqCJ){FWxFAzjIjm = true;}
      if(gLafhGNIft == ROAqLdLtON){jqCDaWRlUK = true;}
      else if(ROAqLdLtON == gLafhGNIft){oKzoyFgtwe = true;}
      if(dbYxOYTeiu == tjxGCxNsri){gNdAfDBPBf = true;}
      else if(tjxGCxNsri == dbYxOYTeiu){kOErGNxPpe = true;}
      if(cPdBoIBVfy == XCDHTXiEyf){qeejxbLlRQ = true;}
      else if(XCDHTXiEyf == cPdBoIBVfy){WZlgJqAEoC = true;}
      if(nGpADOmnZU == kKXYSHHmWK){LxSFlQoCEK = true;}
      else if(kKXYSHHmWK == nGpADOmnZU){CLMaXgxrGH = true;}
      if(DKsfZEltqx == MDTGrwPpxR){eELiWjjOEM = true;}
      else if(MDTGrwPpxR == DKsfZEltqx){lSXHupREzl = true;}
      if(JPIGfQhZqY == xnTqeOKsXm){DrjyRFLSFz = true;}
      if(FrbgGWlXsA == uHwiciLYmt){KeUDyitYOO = true;}
      if(lfENqSWxbj == paVgVThwOW){NyKpBlTwNN = true;}
      while(xnTqeOKsXm == JPIGfQhZqY){CUREQOYRfG = true;}
      while(uHwiciLYmt == uHwiciLYmt){EcEtcZBdUZ = true;}
      while(paVgVThwOW == paVgVThwOW){QEIirDBdlS = true;}
      if(HrGfhwqgsD == true){HrGfhwqgsD = false;}
      if(xOPjPEHkdJ == true){xOPjPEHkdJ = false;}
      if(jqCDaWRlUK == true){jqCDaWRlUK = false;}
      if(gNdAfDBPBf == true){gNdAfDBPBf = false;}
      if(qeejxbLlRQ == true){qeejxbLlRQ = false;}
      if(LxSFlQoCEK == true){LxSFlQoCEK = false;}
      if(eELiWjjOEM == true){eELiWjjOEM = false;}
      if(DrjyRFLSFz == true){DrjyRFLSFz = false;}
      if(KeUDyitYOO == true){KeUDyitYOO = false;}
      if(NyKpBlTwNN == true){NyKpBlTwNN = false;}
      if(rxhENTMUmg == true){rxhENTMUmg = false;}
      if(FWxFAzjIjm == true){FWxFAzjIjm = false;}
      if(oKzoyFgtwe == true){oKzoyFgtwe = false;}
      if(kOErGNxPpe == true){kOErGNxPpe = false;}
      if(WZlgJqAEoC == true){WZlgJqAEoC = false;}
      if(CLMaXgxrGH == true){CLMaXgxrGH = false;}
      if(lSXHupREzl == true){lSXHupREzl = false;}
      if(CUREQOYRfG == true){CUREQOYRfG = false;}
      if(EcEtcZBdUZ == true){EcEtcZBdUZ = false;}
      if(QEIirDBdlS == true){QEIirDBdlS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LZNFLQBJJB
{ 
  void oQFfaVrioQ()
  { 
      bool CIxpLnmMPF = false;
      bool GVfTXMneil = false;
      bool eEmnfzRKaT = false;
      bool YYQqwCAfML = false;
      bool tdPCreNlgB = false;
      bool sVWQAyVJKM = false;
      bool WckwfhFoXU = false;
      bool LISWqAojuA = false;
      bool kecYZDCzpy = false;
      bool gpUAoQrTWK = false;
      bool ZYOLokCzYA = false;
      bool IkOKaqAMVb = false;
      bool fFzYnVmRgZ = false;
      bool HVMjZMPQio = false;
      bool ACZooubKZy = false;
      bool QfyteUZoXT = false;
      bool xkSzrmXdjN = false;
      bool aicfaceJjr = false;
      bool sbriJbWSEF = false;
      bool lZsOqPjaxB = false;
      string UyAHFyNmfk;
      string DNtWLUKZcJ;
      string yAKUwPkmrB;
      string rnIciGRTkG;
      string kDsDXIuOJC;
      string jtDVAUmeKp;
      string MaterOFRmE;
      string CqnWXtGHwm;
      string TWdoQyklbO;
      string SlIttKIOKJ;
      string DdaEzrFgxF;
      string NfiXWoxFNt;
      string dSoXlPitcN;
      string krwmjowYoX;
      string sEoWBmDkXE;
      string MDBQejnCSj;
      string JKDiTVjumg;
      string sXPoBZdSWy;
      string LxWXAhpeIz;
      string BsGFOhAFCf;
      if(UyAHFyNmfk == DdaEzrFgxF){CIxpLnmMPF = true;}
      else if(DdaEzrFgxF == UyAHFyNmfk){ZYOLokCzYA = true;}
      if(DNtWLUKZcJ == NfiXWoxFNt){GVfTXMneil = true;}
      else if(NfiXWoxFNt == DNtWLUKZcJ){IkOKaqAMVb = true;}
      if(yAKUwPkmrB == dSoXlPitcN){eEmnfzRKaT = true;}
      else if(dSoXlPitcN == yAKUwPkmrB){fFzYnVmRgZ = true;}
      if(rnIciGRTkG == krwmjowYoX){YYQqwCAfML = true;}
      else if(krwmjowYoX == rnIciGRTkG){HVMjZMPQio = true;}
      if(kDsDXIuOJC == sEoWBmDkXE){tdPCreNlgB = true;}
      else if(sEoWBmDkXE == kDsDXIuOJC){ACZooubKZy = true;}
      if(jtDVAUmeKp == MDBQejnCSj){sVWQAyVJKM = true;}
      else if(MDBQejnCSj == jtDVAUmeKp){QfyteUZoXT = true;}
      if(MaterOFRmE == JKDiTVjumg){WckwfhFoXU = true;}
      else if(JKDiTVjumg == MaterOFRmE){xkSzrmXdjN = true;}
      if(CqnWXtGHwm == sXPoBZdSWy){LISWqAojuA = true;}
      if(TWdoQyklbO == LxWXAhpeIz){kecYZDCzpy = true;}
      if(SlIttKIOKJ == BsGFOhAFCf){gpUAoQrTWK = true;}
      while(sXPoBZdSWy == CqnWXtGHwm){aicfaceJjr = true;}
      while(LxWXAhpeIz == LxWXAhpeIz){sbriJbWSEF = true;}
      while(BsGFOhAFCf == BsGFOhAFCf){lZsOqPjaxB = true;}
      if(CIxpLnmMPF == true){CIxpLnmMPF = false;}
      if(GVfTXMneil == true){GVfTXMneil = false;}
      if(eEmnfzRKaT == true){eEmnfzRKaT = false;}
      if(YYQqwCAfML == true){YYQqwCAfML = false;}
      if(tdPCreNlgB == true){tdPCreNlgB = false;}
      if(sVWQAyVJKM == true){sVWQAyVJKM = false;}
      if(WckwfhFoXU == true){WckwfhFoXU = false;}
      if(LISWqAojuA == true){LISWqAojuA = false;}
      if(kecYZDCzpy == true){kecYZDCzpy = false;}
      if(gpUAoQrTWK == true){gpUAoQrTWK = false;}
      if(ZYOLokCzYA == true){ZYOLokCzYA = false;}
      if(IkOKaqAMVb == true){IkOKaqAMVb = false;}
      if(fFzYnVmRgZ == true){fFzYnVmRgZ = false;}
      if(HVMjZMPQio == true){HVMjZMPQio = false;}
      if(ACZooubKZy == true){ACZooubKZy = false;}
      if(QfyteUZoXT == true){QfyteUZoXT = false;}
      if(xkSzrmXdjN == true){xkSzrmXdjN = false;}
      if(aicfaceJjr == true){aicfaceJjr = false;}
      if(sbriJbWSEF == true){sbriJbWSEF = false;}
      if(lZsOqPjaxB == true){lZsOqPjaxB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MDGLMRRVTY
{ 
  void BhFFZRQOKV()
  { 
      bool OlbaJMHrWE = false;
      bool WIpsXUCagf = false;
      bool jBnqOyNjyr = false;
      bool KELQFgkbCY = false;
      bool kVqfDequTV = false;
      bool dRtRAMykLK = false;
      bool yXtdsRwYnq = false;
      bool iaXIuOKHmj = false;
      bool GSPcNsKtQr = false;
      bool iAPqZMbMll = false;
      bool iSHblCslWk = false;
      bool CpxbEfIQQA = false;
      bool GCHuIhLghh = false;
      bool mxVBBnKmpK = false;
      bool AYWepsDmlt = false;
      bool EKwlefKLTE = false;
      bool pLDnyEUwaP = false;
      bool UUaFAgecFO = false;
      bool eYtndcBiVU = false;
      bool czSlUnVigk = false;
      string jARNbzrzPT;
      string sfEVsgdYsG;
      string jDKTPLrZhr;
      string huwyIrZkDA;
      string lMQtmKFpLc;
      string gHelZfoyyP;
      string GRQXlxiFMA;
      string GsUsTXmQgE;
      string GCNFLZQKYb;
      string CbmnsTurHo;
      string azcLVnmlRB;
      string sYQtJEELLL;
      string gYgkydFgAA;
      string ctJrcGYCiX;
      string mdrWidKrdn;
      string OjguHCSrNq;
      string hFlRYyPYQC;
      string eCbnYDfJBT;
      string SNCLksNNjZ;
      string ngorpgraxk;
      if(jARNbzrzPT == azcLVnmlRB){OlbaJMHrWE = true;}
      else if(azcLVnmlRB == jARNbzrzPT){iSHblCslWk = true;}
      if(sfEVsgdYsG == sYQtJEELLL){WIpsXUCagf = true;}
      else if(sYQtJEELLL == sfEVsgdYsG){CpxbEfIQQA = true;}
      if(jDKTPLrZhr == gYgkydFgAA){jBnqOyNjyr = true;}
      else if(gYgkydFgAA == jDKTPLrZhr){GCHuIhLghh = true;}
      if(huwyIrZkDA == ctJrcGYCiX){KELQFgkbCY = true;}
      else if(ctJrcGYCiX == huwyIrZkDA){mxVBBnKmpK = true;}
      if(lMQtmKFpLc == mdrWidKrdn){kVqfDequTV = true;}
      else if(mdrWidKrdn == lMQtmKFpLc){AYWepsDmlt = true;}
      if(gHelZfoyyP == OjguHCSrNq){dRtRAMykLK = true;}
      else if(OjguHCSrNq == gHelZfoyyP){EKwlefKLTE = true;}
      if(GRQXlxiFMA == hFlRYyPYQC){yXtdsRwYnq = true;}
      else if(hFlRYyPYQC == GRQXlxiFMA){pLDnyEUwaP = true;}
      if(GsUsTXmQgE == eCbnYDfJBT){iaXIuOKHmj = true;}
      if(GCNFLZQKYb == SNCLksNNjZ){GSPcNsKtQr = true;}
      if(CbmnsTurHo == ngorpgraxk){iAPqZMbMll = true;}
      while(eCbnYDfJBT == GsUsTXmQgE){UUaFAgecFO = true;}
      while(SNCLksNNjZ == SNCLksNNjZ){eYtndcBiVU = true;}
      while(ngorpgraxk == ngorpgraxk){czSlUnVigk = true;}
      if(OlbaJMHrWE == true){OlbaJMHrWE = false;}
      if(WIpsXUCagf == true){WIpsXUCagf = false;}
      if(jBnqOyNjyr == true){jBnqOyNjyr = false;}
      if(KELQFgkbCY == true){KELQFgkbCY = false;}
      if(kVqfDequTV == true){kVqfDequTV = false;}
      if(dRtRAMykLK == true){dRtRAMykLK = false;}
      if(yXtdsRwYnq == true){yXtdsRwYnq = false;}
      if(iaXIuOKHmj == true){iaXIuOKHmj = false;}
      if(GSPcNsKtQr == true){GSPcNsKtQr = false;}
      if(iAPqZMbMll == true){iAPqZMbMll = false;}
      if(iSHblCslWk == true){iSHblCslWk = false;}
      if(CpxbEfIQQA == true){CpxbEfIQQA = false;}
      if(GCHuIhLghh == true){GCHuIhLghh = false;}
      if(mxVBBnKmpK == true){mxVBBnKmpK = false;}
      if(AYWepsDmlt == true){AYWepsDmlt = false;}
      if(EKwlefKLTE == true){EKwlefKLTE = false;}
      if(pLDnyEUwaP == true){pLDnyEUwaP = false;}
      if(UUaFAgecFO == true){UUaFAgecFO = false;}
      if(eYtndcBiVU == true){eYtndcBiVU = false;}
      if(czSlUnVigk == true){czSlUnVigk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VQYNXXVYKJ
{ 
  void jMVZiCqtyL()
  { 
      bool KrgVCUsasQ = false;
      bool BUGZTkMoxy = false;
      bool uxUpdKQeGf = false;
      bool fSFgZmUsyl = false;
      bool uUVSRRNSuO = false;
      bool lsqnLNWqrq = false;
      bool EOTNjiPZzg = false;
      bool PSqLCaaBXL = false;
      bool xxjrtlbQUM = false;
      bool PcAGggBIhi = false;
      bool CmTNySCekk = false;
      bool lVSftHdaSy = false;
      bool GyFlQmSkeU = false;
      bool ZSSoIJcVsa = false;
      bool jxeiasJULY = false;
      bool DZojcDhgxL = false;
      bool AQAPLSCdWk = false;
      bool eHhrOJSVLW = false;
      bool cxZFRzdiLF = false;
      bool auYgZSxOXI = false;
      string NUpJObEyju;
      string NnmsTHcHaF;
      string OpDniRjUDX;
      string mcDennRFAS;
      string bpmlFummxP;
      string EjfTnWRCaw;
      string qjuMIkkIEe;
      string pXGIdXDQim;
      string exWmSDwjpR;
      string WPdEaruacT;
      string KehSZfcWpQ;
      string SASmQtNHsE;
      string nBRmHasCgk;
      string cbnOcAPDNl;
      string ZYsZyWwqmg;
      string emgYeJMuKy;
      string mapEmpMEJQ;
      string eJtGeOHrnk;
      string eCOAGouOiT;
      string mTsOzyinlH;
      if(NUpJObEyju == KehSZfcWpQ){KrgVCUsasQ = true;}
      else if(KehSZfcWpQ == NUpJObEyju){CmTNySCekk = true;}
      if(NnmsTHcHaF == SASmQtNHsE){BUGZTkMoxy = true;}
      else if(SASmQtNHsE == NnmsTHcHaF){lVSftHdaSy = true;}
      if(OpDniRjUDX == nBRmHasCgk){uxUpdKQeGf = true;}
      else if(nBRmHasCgk == OpDniRjUDX){GyFlQmSkeU = true;}
      if(mcDennRFAS == cbnOcAPDNl){fSFgZmUsyl = true;}
      else if(cbnOcAPDNl == mcDennRFAS){ZSSoIJcVsa = true;}
      if(bpmlFummxP == ZYsZyWwqmg){uUVSRRNSuO = true;}
      else if(ZYsZyWwqmg == bpmlFummxP){jxeiasJULY = true;}
      if(EjfTnWRCaw == emgYeJMuKy){lsqnLNWqrq = true;}
      else if(emgYeJMuKy == EjfTnWRCaw){DZojcDhgxL = true;}
      if(qjuMIkkIEe == mapEmpMEJQ){EOTNjiPZzg = true;}
      else if(mapEmpMEJQ == qjuMIkkIEe){AQAPLSCdWk = true;}
      if(pXGIdXDQim == eJtGeOHrnk){PSqLCaaBXL = true;}
      if(exWmSDwjpR == eCOAGouOiT){xxjrtlbQUM = true;}
      if(WPdEaruacT == mTsOzyinlH){PcAGggBIhi = true;}
      while(eJtGeOHrnk == pXGIdXDQim){eHhrOJSVLW = true;}
      while(eCOAGouOiT == eCOAGouOiT){cxZFRzdiLF = true;}
      while(mTsOzyinlH == mTsOzyinlH){auYgZSxOXI = true;}
      if(KrgVCUsasQ == true){KrgVCUsasQ = false;}
      if(BUGZTkMoxy == true){BUGZTkMoxy = false;}
      if(uxUpdKQeGf == true){uxUpdKQeGf = false;}
      if(fSFgZmUsyl == true){fSFgZmUsyl = false;}
      if(uUVSRRNSuO == true){uUVSRRNSuO = false;}
      if(lsqnLNWqrq == true){lsqnLNWqrq = false;}
      if(EOTNjiPZzg == true){EOTNjiPZzg = false;}
      if(PSqLCaaBXL == true){PSqLCaaBXL = false;}
      if(xxjrtlbQUM == true){xxjrtlbQUM = false;}
      if(PcAGggBIhi == true){PcAGggBIhi = false;}
      if(CmTNySCekk == true){CmTNySCekk = false;}
      if(lVSftHdaSy == true){lVSftHdaSy = false;}
      if(GyFlQmSkeU == true){GyFlQmSkeU = false;}
      if(ZSSoIJcVsa == true){ZSSoIJcVsa = false;}
      if(jxeiasJULY == true){jxeiasJULY = false;}
      if(DZojcDhgxL == true){DZojcDhgxL = false;}
      if(AQAPLSCdWk == true){AQAPLSCdWk = false;}
      if(eHhrOJSVLW == true){eHhrOJSVLW = false;}
      if(cxZFRzdiLF == true){cxZFRzdiLF = false;}
      if(auYgZSxOXI == true){auYgZSxOXI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YEMOKJJSCW
{ 
  void eDQyHguyRD()
  { 
      bool VlLqojlDHC = false;
      bool jrkRpLlTnN = false;
      bool MdpIEtQcqS = false;
      bool JMtRfdGApe = false;
      bool IiaoVsHxbc = false;
      bool cCnnUqwDmu = false;
      bool SILnrWySlL = false;
      bool ElcIEcDAlK = false;
      bool mTAOoGXFxn = false;
      bool hDNuMzWlwy = false;
      bool uoLQXqZejq = false;
      bool nuQbIzHxzl = false;
      bool zrVxcBXhwE = false;
      bool GQEmPyHjqy = false;
      bool grUFzmllmM = false;
      bool qZlKzCSNmW = false;
      bool SqiekXpcLK = false;
      bool qXGBEGXPxo = false;
      bool OlujNgetmM = false;
      bool eswUepJpUb = false;
      string nOxSwuqBAM;
      string RszDqHrKyt;
      string HRndCLnoSQ;
      string hkJBXquijy;
      string hhPxRdrwDD;
      string dgHtIWZTQj;
      string HChidgjyfA;
      string MJazLZBqLX;
      string TrlPlBdOrA;
      string QbRzqfzfSk;
      string ssPCqUGHii;
      string UiHrQOPSxc;
      string CUFeijqaIe;
      string aVXZdZbiXR;
      string uVfJfgTYib;
      string QfioiYnjTG;
      string cezDHyLhNq;
      string lftehfowzB;
      string QRrfOtlhqF;
      string lrPRnPWcBg;
      if(nOxSwuqBAM == ssPCqUGHii){VlLqojlDHC = true;}
      else if(ssPCqUGHii == nOxSwuqBAM){uoLQXqZejq = true;}
      if(RszDqHrKyt == UiHrQOPSxc){jrkRpLlTnN = true;}
      else if(UiHrQOPSxc == RszDqHrKyt){nuQbIzHxzl = true;}
      if(HRndCLnoSQ == CUFeijqaIe){MdpIEtQcqS = true;}
      else if(CUFeijqaIe == HRndCLnoSQ){zrVxcBXhwE = true;}
      if(hkJBXquijy == aVXZdZbiXR){JMtRfdGApe = true;}
      else if(aVXZdZbiXR == hkJBXquijy){GQEmPyHjqy = true;}
      if(hhPxRdrwDD == uVfJfgTYib){IiaoVsHxbc = true;}
      else if(uVfJfgTYib == hhPxRdrwDD){grUFzmllmM = true;}
      if(dgHtIWZTQj == QfioiYnjTG){cCnnUqwDmu = true;}
      else if(QfioiYnjTG == dgHtIWZTQj){qZlKzCSNmW = true;}
      if(HChidgjyfA == cezDHyLhNq){SILnrWySlL = true;}
      else if(cezDHyLhNq == HChidgjyfA){SqiekXpcLK = true;}
      if(MJazLZBqLX == lftehfowzB){ElcIEcDAlK = true;}
      if(TrlPlBdOrA == QRrfOtlhqF){mTAOoGXFxn = true;}
      if(QbRzqfzfSk == lrPRnPWcBg){hDNuMzWlwy = true;}
      while(lftehfowzB == MJazLZBqLX){qXGBEGXPxo = true;}
      while(QRrfOtlhqF == QRrfOtlhqF){OlujNgetmM = true;}
      while(lrPRnPWcBg == lrPRnPWcBg){eswUepJpUb = true;}
      if(VlLqojlDHC == true){VlLqojlDHC = false;}
      if(jrkRpLlTnN == true){jrkRpLlTnN = false;}
      if(MdpIEtQcqS == true){MdpIEtQcqS = false;}
      if(JMtRfdGApe == true){JMtRfdGApe = false;}
      if(IiaoVsHxbc == true){IiaoVsHxbc = false;}
      if(cCnnUqwDmu == true){cCnnUqwDmu = false;}
      if(SILnrWySlL == true){SILnrWySlL = false;}
      if(ElcIEcDAlK == true){ElcIEcDAlK = false;}
      if(mTAOoGXFxn == true){mTAOoGXFxn = false;}
      if(hDNuMzWlwy == true){hDNuMzWlwy = false;}
      if(uoLQXqZejq == true){uoLQXqZejq = false;}
      if(nuQbIzHxzl == true){nuQbIzHxzl = false;}
      if(zrVxcBXhwE == true){zrVxcBXhwE = false;}
      if(GQEmPyHjqy == true){GQEmPyHjqy = false;}
      if(grUFzmllmM == true){grUFzmllmM = false;}
      if(qZlKzCSNmW == true){qZlKzCSNmW = false;}
      if(SqiekXpcLK == true){SqiekXpcLK = false;}
      if(qXGBEGXPxo == true){qXGBEGXPxo = false;}
      if(OlujNgetmM == true){OlujNgetmM = false;}
      if(eswUepJpUb == true){eswUepJpUb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSHTNZPNCP
{ 
  void gIGKNOUbwI()
  { 
      bool kGhaIwWCnl = false;
      bool nsMAZcBAQt = false;
      bool AmjRHXNQFW = false;
      bool JpdRiqOQpz = false;
      bool VJMYHucUIQ = false;
      bool jTSVHyVQSj = false;
      bool hGxQbxOtQh = false;
      bool OkJRXqaKJL = false;
      bool tsHnlpWIKk = false;
      bool UyxGQPLuxJ = false;
      bool giDaCzKBxQ = false;
      bool WLGHooyIdl = false;
      bool ZFjfMQmDAI = false;
      bool eeNAeLoglm = false;
      bool fVLsNJqpQa = false;
      bool QCRKiayXNl = false;
      bool LHBnkrxGbd = false;
      bool ARWqGEtpRD = false;
      bool YxlYrcMCQD = false;
      bool MQSAaXUWIU = false;
      string RYrOeTBKMi;
      string WUwroItrlN;
      string DHBiutYXaJ;
      string GmJwEjikgG;
      string gMXPuyiSTw;
      string YTAVsJXJTj;
      string ucjDciLzmF;
      string YILffqikmw;
      string LGEdjmmmDt;
      string LYRwKEbUmL;
      string mieOXQHToB;
      string alWWYoYFSo;
      string wXwssAqOUb;
      string OOyaJbapGT;
      string eSxCTYCtXV;
      string eWCxPOmkUX;
      string ZszNlLnuMw;
      string NizzJdZtYU;
      string xwqzwrLALu;
      string ooUitlTjPH;
      if(RYrOeTBKMi == mieOXQHToB){kGhaIwWCnl = true;}
      else if(mieOXQHToB == RYrOeTBKMi){giDaCzKBxQ = true;}
      if(WUwroItrlN == alWWYoYFSo){nsMAZcBAQt = true;}
      else if(alWWYoYFSo == WUwroItrlN){WLGHooyIdl = true;}
      if(DHBiutYXaJ == wXwssAqOUb){AmjRHXNQFW = true;}
      else if(wXwssAqOUb == DHBiutYXaJ){ZFjfMQmDAI = true;}
      if(GmJwEjikgG == OOyaJbapGT){JpdRiqOQpz = true;}
      else if(OOyaJbapGT == GmJwEjikgG){eeNAeLoglm = true;}
      if(gMXPuyiSTw == eSxCTYCtXV){VJMYHucUIQ = true;}
      else if(eSxCTYCtXV == gMXPuyiSTw){fVLsNJqpQa = true;}
      if(YTAVsJXJTj == eWCxPOmkUX){jTSVHyVQSj = true;}
      else if(eWCxPOmkUX == YTAVsJXJTj){QCRKiayXNl = true;}
      if(ucjDciLzmF == ZszNlLnuMw){hGxQbxOtQh = true;}
      else if(ZszNlLnuMw == ucjDciLzmF){LHBnkrxGbd = true;}
      if(YILffqikmw == NizzJdZtYU){OkJRXqaKJL = true;}
      if(LGEdjmmmDt == xwqzwrLALu){tsHnlpWIKk = true;}
      if(LYRwKEbUmL == ooUitlTjPH){UyxGQPLuxJ = true;}
      while(NizzJdZtYU == YILffqikmw){ARWqGEtpRD = true;}
      while(xwqzwrLALu == xwqzwrLALu){YxlYrcMCQD = true;}
      while(ooUitlTjPH == ooUitlTjPH){MQSAaXUWIU = true;}
      if(kGhaIwWCnl == true){kGhaIwWCnl = false;}
      if(nsMAZcBAQt == true){nsMAZcBAQt = false;}
      if(AmjRHXNQFW == true){AmjRHXNQFW = false;}
      if(JpdRiqOQpz == true){JpdRiqOQpz = false;}
      if(VJMYHucUIQ == true){VJMYHucUIQ = false;}
      if(jTSVHyVQSj == true){jTSVHyVQSj = false;}
      if(hGxQbxOtQh == true){hGxQbxOtQh = false;}
      if(OkJRXqaKJL == true){OkJRXqaKJL = false;}
      if(tsHnlpWIKk == true){tsHnlpWIKk = false;}
      if(UyxGQPLuxJ == true){UyxGQPLuxJ = false;}
      if(giDaCzKBxQ == true){giDaCzKBxQ = false;}
      if(WLGHooyIdl == true){WLGHooyIdl = false;}
      if(ZFjfMQmDAI == true){ZFjfMQmDAI = false;}
      if(eeNAeLoglm == true){eeNAeLoglm = false;}
      if(fVLsNJqpQa == true){fVLsNJqpQa = false;}
      if(QCRKiayXNl == true){QCRKiayXNl = false;}
      if(LHBnkrxGbd == true){LHBnkrxGbd = false;}
      if(ARWqGEtpRD == true){ARWqGEtpRD = false;}
      if(YxlYrcMCQD == true){YxlYrcMCQD = false;}
      if(MQSAaXUWIU == true){MQSAaXUWIU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EEWTLNVYSO
{ 
  void DzrGIAuGHW()
  { 
      bool zRqUcTKWRB = false;
      bool ujLHZmSgWI = false;
      bool uqzZdpSVpS = false;
      bool wgUWdrDyPc = false;
      bool WgHIVVtiGN = false;
      bool VDWrOHSQpl = false;
      bool AofzFOPocg = false;
      bool iURslNipEH = false;
      bool wjPbwrJcIV = false;
      bool ZlHcbhAHCH = false;
      bool GFGYdBkdGA = false;
      bool YbMhpQYDCM = false;
      bool EmfGHxMnQD = false;
      bool NamwBpcpxu = false;
      bool HfWHxxYYmK = false;
      bool IxEpCTYARg = false;
      bool nwMCmxnQgz = false;
      bool niFHFYPYIK = false;
      bool YmBFtQVxsh = false;
      bool RbYQHKTTTz = false;
      string owIrXLAkTi;
      string bzlLaQjHnx;
      string RRamMsgJcy;
      string ShysxBzsgA;
      string GoKVUMMyDn;
      string DjemOXUUed;
      string epHVPtArOZ;
      string QqamqbHFSz;
      string giFntiCKeY;
      string fdNCVPgoFZ;
      string MTidWLJqwl;
      string QPCexwkTag;
      string qpNpsldXRb;
      string uRzrmMzaQi;
      string ZKOrIPbiFY;
      string dNOYhVGsjk;
      string hkZUqyQJqj;
      string wJCqGgaVgc;
      string KtSrxhDZKQ;
      string GGpfBnktAJ;
      if(owIrXLAkTi == MTidWLJqwl){zRqUcTKWRB = true;}
      else if(MTidWLJqwl == owIrXLAkTi){GFGYdBkdGA = true;}
      if(bzlLaQjHnx == QPCexwkTag){ujLHZmSgWI = true;}
      else if(QPCexwkTag == bzlLaQjHnx){YbMhpQYDCM = true;}
      if(RRamMsgJcy == qpNpsldXRb){uqzZdpSVpS = true;}
      else if(qpNpsldXRb == RRamMsgJcy){EmfGHxMnQD = true;}
      if(ShysxBzsgA == uRzrmMzaQi){wgUWdrDyPc = true;}
      else if(uRzrmMzaQi == ShysxBzsgA){NamwBpcpxu = true;}
      if(GoKVUMMyDn == ZKOrIPbiFY){WgHIVVtiGN = true;}
      else if(ZKOrIPbiFY == GoKVUMMyDn){HfWHxxYYmK = true;}
      if(DjemOXUUed == dNOYhVGsjk){VDWrOHSQpl = true;}
      else if(dNOYhVGsjk == DjemOXUUed){IxEpCTYARg = true;}
      if(epHVPtArOZ == hkZUqyQJqj){AofzFOPocg = true;}
      else if(hkZUqyQJqj == epHVPtArOZ){nwMCmxnQgz = true;}
      if(QqamqbHFSz == wJCqGgaVgc){iURslNipEH = true;}
      if(giFntiCKeY == KtSrxhDZKQ){wjPbwrJcIV = true;}
      if(fdNCVPgoFZ == GGpfBnktAJ){ZlHcbhAHCH = true;}
      while(wJCqGgaVgc == QqamqbHFSz){niFHFYPYIK = true;}
      while(KtSrxhDZKQ == KtSrxhDZKQ){YmBFtQVxsh = true;}
      while(GGpfBnktAJ == GGpfBnktAJ){RbYQHKTTTz = true;}
      if(zRqUcTKWRB == true){zRqUcTKWRB = false;}
      if(ujLHZmSgWI == true){ujLHZmSgWI = false;}
      if(uqzZdpSVpS == true){uqzZdpSVpS = false;}
      if(wgUWdrDyPc == true){wgUWdrDyPc = false;}
      if(WgHIVVtiGN == true){WgHIVVtiGN = false;}
      if(VDWrOHSQpl == true){VDWrOHSQpl = false;}
      if(AofzFOPocg == true){AofzFOPocg = false;}
      if(iURslNipEH == true){iURslNipEH = false;}
      if(wjPbwrJcIV == true){wjPbwrJcIV = false;}
      if(ZlHcbhAHCH == true){ZlHcbhAHCH = false;}
      if(GFGYdBkdGA == true){GFGYdBkdGA = false;}
      if(YbMhpQYDCM == true){YbMhpQYDCM = false;}
      if(EmfGHxMnQD == true){EmfGHxMnQD = false;}
      if(NamwBpcpxu == true){NamwBpcpxu = false;}
      if(HfWHxxYYmK == true){HfWHxxYYmK = false;}
      if(IxEpCTYARg == true){IxEpCTYARg = false;}
      if(nwMCmxnQgz == true){nwMCmxnQgz = false;}
      if(niFHFYPYIK == true){niFHFYPYIK = false;}
      if(YmBFtQVxsh == true){YmBFtQVxsh = false;}
      if(RbYQHKTTTz == true){RbYQHKTTTz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDFFUHRUXL
{ 
  void MrcHMzeJif()
  { 
      bool WeEJFHuuss = false;
      bool ERfsQjrduV = false;
      bool JKsCzLlZAz = false;
      bool XkOYIgZXsb = false;
      bool gxIaWIjGpx = false;
      bool nFeFBMlBKt = false;
      bool UVutVTCGki = false;
      bool KUjSnMBRep = false;
      bool afiDLRFJXu = false;
      bool uXNzHLCNFD = false;
      bool FcVGlTUMQo = false;
      bool KTWTSnlriD = false;
      bool NsiommGkKc = false;
      bool JmLbjxJbQq = false;
      bool wsshkbAsfS = false;
      bool YKeCpMtgTz = false;
      bool MjBmeWHtiV = false;
      bool dJaqGTABEL = false;
      bool lMFqEzIJlX = false;
      bool DcIReMrFCN = false;
      string sGNXfIQZLb;
      string kfbfhdKIVR;
      string jngreTBolK;
      string szDiswwuCy;
      string hiItFHPDaQ;
      string oweqFEZUrL;
      string HamAilbrml;
      string gOGWjBelmW;
      string EyOUVwTLdn;
      string WaDpqGuILS;
      string fWPojZpIHE;
      string ZmhUHJMSdl;
      string SPOzPFLPfc;
      string FWaTqhhZkw;
      string GLEYOishig;
      string tcdYzPHQYd;
      string NZbdyCLNdZ;
      string bmghfGLokf;
      string MdgyicsBTa;
      string ZQAHhfiZaL;
      if(sGNXfIQZLb == fWPojZpIHE){WeEJFHuuss = true;}
      else if(fWPojZpIHE == sGNXfIQZLb){FcVGlTUMQo = true;}
      if(kfbfhdKIVR == ZmhUHJMSdl){ERfsQjrduV = true;}
      else if(ZmhUHJMSdl == kfbfhdKIVR){KTWTSnlriD = true;}
      if(jngreTBolK == SPOzPFLPfc){JKsCzLlZAz = true;}
      else if(SPOzPFLPfc == jngreTBolK){NsiommGkKc = true;}
      if(szDiswwuCy == FWaTqhhZkw){XkOYIgZXsb = true;}
      else if(FWaTqhhZkw == szDiswwuCy){JmLbjxJbQq = true;}
      if(hiItFHPDaQ == GLEYOishig){gxIaWIjGpx = true;}
      else if(GLEYOishig == hiItFHPDaQ){wsshkbAsfS = true;}
      if(oweqFEZUrL == tcdYzPHQYd){nFeFBMlBKt = true;}
      else if(tcdYzPHQYd == oweqFEZUrL){YKeCpMtgTz = true;}
      if(HamAilbrml == NZbdyCLNdZ){UVutVTCGki = true;}
      else if(NZbdyCLNdZ == HamAilbrml){MjBmeWHtiV = true;}
      if(gOGWjBelmW == bmghfGLokf){KUjSnMBRep = true;}
      if(EyOUVwTLdn == MdgyicsBTa){afiDLRFJXu = true;}
      if(WaDpqGuILS == ZQAHhfiZaL){uXNzHLCNFD = true;}
      while(bmghfGLokf == gOGWjBelmW){dJaqGTABEL = true;}
      while(MdgyicsBTa == MdgyicsBTa){lMFqEzIJlX = true;}
      while(ZQAHhfiZaL == ZQAHhfiZaL){DcIReMrFCN = true;}
      if(WeEJFHuuss == true){WeEJFHuuss = false;}
      if(ERfsQjrduV == true){ERfsQjrduV = false;}
      if(JKsCzLlZAz == true){JKsCzLlZAz = false;}
      if(XkOYIgZXsb == true){XkOYIgZXsb = false;}
      if(gxIaWIjGpx == true){gxIaWIjGpx = false;}
      if(nFeFBMlBKt == true){nFeFBMlBKt = false;}
      if(UVutVTCGki == true){UVutVTCGki = false;}
      if(KUjSnMBRep == true){KUjSnMBRep = false;}
      if(afiDLRFJXu == true){afiDLRFJXu = false;}
      if(uXNzHLCNFD == true){uXNzHLCNFD = false;}
      if(FcVGlTUMQo == true){FcVGlTUMQo = false;}
      if(KTWTSnlriD == true){KTWTSnlriD = false;}
      if(NsiommGkKc == true){NsiommGkKc = false;}
      if(JmLbjxJbQq == true){JmLbjxJbQq = false;}
      if(wsshkbAsfS == true){wsshkbAsfS = false;}
      if(YKeCpMtgTz == true){YKeCpMtgTz = false;}
      if(MjBmeWHtiV == true){MjBmeWHtiV = false;}
      if(dJaqGTABEL == true){dJaqGTABEL = false;}
      if(lMFqEzIJlX == true){lMFqEzIJlX = false;}
      if(DcIReMrFCN == true){DcIReMrFCN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EQPCYCIIOP
{ 
  void NuKylbFJSo()
  { 
      bool lJApdATYmZ = false;
      bool MhYPFhcGMo = false;
      bool SoyFHqMirN = false;
      bool PyALwPLerp = false;
      bool cJgTsbPJnm = false;
      bool gsxTGxLthm = false;
      bool mkfZJNhMTo = false;
      bool WyNVLIIdMf = false;
      bool aDtFfWBfFz = false;
      bool EQxEDqcHKe = false;
      bool sDozPiebIx = false;
      bool nhhCLjqasm = false;
      bool MBHUkFBISU = false;
      bool eBTglXNuow = false;
      bool qZXHKWiusS = false;
      bool ACNXSquUNJ = false;
      bool hVJmRmNBPn = false;
      bool VwkwumdAJO = false;
      bool WFPzTcmuOt = false;
      bool brgfOUQjoW = false;
      string XBbgouJfri;
      string BSeKSdiwMl;
      string fQlhYXwwud;
      string QUDADBXIro;
      string KkeMOGabtN;
      string tehIZHPtHQ;
      string zMkNSfPeHQ;
      string FaEWbtlZSS;
      string xTBhjkmtZw;
      string ldBapxAQsi;
      string qwUdHTaKgf;
      string VpbnTeKDdh;
      string sUEKebYcgd;
      string tUfibBzXZP;
      string JcMtZwCMHK;
      string mxlLoVqJye;
      string tycDkAJrMR;
      string flcNYPIJkh;
      string ZLUWqwhTsG;
      string JoZtVKzJJY;
      if(XBbgouJfri == qwUdHTaKgf){lJApdATYmZ = true;}
      else if(qwUdHTaKgf == XBbgouJfri){sDozPiebIx = true;}
      if(BSeKSdiwMl == VpbnTeKDdh){MhYPFhcGMo = true;}
      else if(VpbnTeKDdh == BSeKSdiwMl){nhhCLjqasm = true;}
      if(fQlhYXwwud == sUEKebYcgd){SoyFHqMirN = true;}
      else if(sUEKebYcgd == fQlhYXwwud){MBHUkFBISU = true;}
      if(QUDADBXIro == tUfibBzXZP){PyALwPLerp = true;}
      else if(tUfibBzXZP == QUDADBXIro){eBTglXNuow = true;}
      if(KkeMOGabtN == JcMtZwCMHK){cJgTsbPJnm = true;}
      else if(JcMtZwCMHK == KkeMOGabtN){qZXHKWiusS = true;}
      if(tehIZHPtHQ == mxlLoVqJye){gsxTGxLthm = true;}
      else if(mxlLoVqJye == tehIZHPtHQ){ACNXSquUNJ = true;}
      if(zMkNSfPeHQ == tycDkAJrMR){mkfZJNhMTo = true;}
      else if(tycDkAJrMR == zMkNSfPeHQ){hVJmRmNBPn = true;}
      if(FaEWbtlZSS == flcNYPIJkh){WyNVLIIdMf = true;}
      if(xTBhjkmtZw == ZLUWqwhTsG){aDtFfWBfFz = true;}
      if(ldBapxAQsi == JoZtVKzJJY){EQxEDqcHKe = true;}
      while(flcNYPIJkh == FaEWbtlZSS){VwkwumdAJO = true;}
      while(ZLUWqwhTsG == ZLUWqwhTsG){WFPzTcmuOt = true;}
      while(JoZtVKzJJY == JoZtVKzJJY){brgfOUQjoW = true;}
      if(lJApdATYmZ == true){lJApdATYmZ = false;}
      if(MhYPFhcGMo == true){MhYPFhcGMo = false;}
      if(SoyFHqMirN == true){SoyFHqMirN = false;}
      if(PyALwPLerp == true){PyALwPLerp = false;}
      if(cJgTsbPJnm == true){cJgTsbPJnm = false;}
      if(gsxTGxLthm == true){gsxTGxLthm = false;}
      if(mkfZJNhMTo == true){mkfZJNhMTo = false;}
      if(WyNVLIIdMf == true){WyNVLIIdMf = false;}
      if(aDtFfWBfFz == true){aDtFfWBfFz = false;}
      if(EQxEDqcHKe == true){EQxEDqcHKe = false;}
      if(sDozPiebIx == true){sDozPiebIx = false;}
      if(nhhCLjqasm == true){nhhCLjqasm = false;}
      if(MBHUkFBISU == true){MBHUkFBISU = false;}
      if(eBTglXNuow == true){eBTglXNuow = false;}
      if(qZXHKWiusS == true){qZXHKWiusS = false;}
      if(ACNXSquUNJ == true){ACNXSquUNJ = false;}
      if(hVJmRmNBPn == true){hVJmRmNBPn = false;}
      if(VwkwumdAJO == true){VwkwumdAJO = false;}
      if(WFPzTcmuOt == true){WFPzTcmuOt = false;}
      if(brgfOUQjoW == true){brgfOUQjoW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HPEODMVSKS
{ 
  void yJxtshYcrs()
  { 
      bool ZKLeLHJZcZ = false;
      bool cPhnRmoHSI = false;
      bool NIROsshtPw = false;
      bool eUdLVcNMoR = false;
      bool NiFHXPCAqV = false;
      bool xpsxWRswlS = false;
      bool ZOJftHlWRo = false;
      bool YcSAudCJpc = false;
      bool pgCtyobgnE = false;
      bool jQZVryZYNQ = false;
      bool dfhCxUWsCs = false;
      bool OiFIbrMPhE = false;
      bool fFhNEHCwHx = false;
      bool EdwZzKzAxc = false;
      bool SheupBLRtA = false;
      bool kJpIjYxUyo = false;
      bool SakEnjleIR = false;
      bool rLSFlyamXD = false;
      bool wkCHLtmnpa = false;
      bool NdCHJrwZGF = false;
      string FXIeLTDChl;
      string VNIOLsAZBY;
      string lXcArBbjOE;
      string ifbiVwBrTb;
      string tUVSciwcMu;
      string VjZagguHmJ;
      string rTmcCplYsO;
      string qHGZeRBJXJ;
      string EzWTiyGABn;
      string BtFJiagsPm;
      string wXiyDNdzwP;
      string fkjcFswTtD;
      string jlWENxBwqE;
      string jItkMgPYPU;
      string UGElIQJbEp;
      string dNzLDKAejF;
      string LgIrfWpzQY;
      string dWDYicgkww;
      string nYrAZWJhhB;
      string fknJImxLGk;
      if(FXIeLTDChl == wXiyDNdzwP){ZKLeLHJZcZ = true;}
      else if(wXiyDNdzwP == FXIeLTDChl){dfhCxUWsCs = true;}
      if(VNIOLsAZBY == fkjcFswTtD){cPhnRmoHSI = true;}
      else if(fkjcFswTtD == VNIOLsAZBY){OiFIbrMPhE = true;}
      if(lXcArBbjOE == jlWENxBwqE){NIROsshtPw = true;}
      else if(jlWENxBwqE == lXcArBbjOE){fFhNEHCwHx = true;}
      if(ifbiVwBrTb == jItkMgPYPU){eUdLVcNMoR = true;}
      else if(jItkMgPYPU == ifbiVwBrTb){EdwZzKzAxc = true;}
      if(tUVSciwcMu == UGElIQJbEp){NiFHXPCAqV = true;}
      else if(UGElIQJbEp == tUVSciwcMu){SheupBLRtA = true;}
      if(VjZagguHmJ == dNzLDKAejF){xpsxWRswlS = true;}
      else if(dNzLDKAejF == VjZagguHmJ){kJpIjYxUyo = true;}
      if(rTmcCplYsO == LgIrfWpzQY){ZOJftHlWRo = true;}
      else if(LgIrfWpzQY == rTmcCplYsO){SakEnjleIR = true;}
      if(qHGZeRBJXJ == dWDYicgkww){YcSAudCJpc = true;}
      if(EzWTiyGABn == nYrAZWJhhB){pgCtyobgnE = true;}
      if(BtFJiagsPm == fknJImxLGk){jQZVryZYNQ = true;}
      while(dWDYicgkww == qHGZeRBJXJ){rLSFlyamXD = true;}
      while(nYrAZWJhhB == nYrAZWJhhB){wkCHLtmnpa = true;}
      while(fknJImxLGk == fknJImxLGk){NdCHJrwZGF = true;}
      if(ZKLeLHJZcZ == true){ZKLeLHJZcZ = false;}
      if(cPhnRmoHSI == true){cPhnRmoHSI = false;}
      if(NIROsshtPw == true){NIROsshtPw = false;}
      if(eUdLVcNMoR == true){eUdLVcNMoR = false;}
      if(NiFHXPCAqV == true){NiFHXPCAqV = false;}
      if(xpsxWRswlS == true){xpsxWRswlS = false;}
      if(ZOJftHlWRo == true){ZOJftHlWRo = false;}
      if(YcSAudCJpc == true){YcSAudCJpc = false;}
      if(pgCtyobgnE == true){pgCtyobgnE = false;}
      if(jQZVryZYNQ == true){jQZVryZYNQ = false;}
      if(dfhCxUWsCs == true){dfhCxUWsCs = false;}
      if(OiFIbrMPhE == true){OiFIbrMPhE = false;}
      if(fFhNEHCwHx == true){fFhNEHCwHx = false;}
      if(EdwZzKzAxc == true){EdwZzKzAxc = false;}
      if(SheupBLRtA == true){SheupBLRtA = false;}
      if(kJpIjYxUyo == true){kJpIjYxUyo = false;}
      if(SakEnjleIR == true){SakEnjleIR = false;}
      if(rLSFlyamXD == true){rLSFlyamXD = false;}
      if(wkCHLtmnpa == true){wkCHLtmnpa = false;}
      if(NdCHJrwZGF == true){NdCHJrwZGF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ISUSGASPVD
{ 
  void XKBZVjDtTW()
  { 
      bool BFUuHsNKtW = false;
      bool YMJZacKKti = false;
      bool tmoqtQFjxW = false;
      bool eafoKHUlOB = false;
      bool xjhNFoqOuQ = false;
      bool sufNMOQdBq = false;
      bool ndMWqygTOS = false;
      bool IXwslJFalE = false;
      bool YqogcitSbw = false;
      bool qpkWNSXKVG = false;
      bool IXzbHUzmbD = false;
      bool IorwSwofsH = false;
      bool DNrSbRmZeS = false;
      bool luFewBqMYI = false;
      bool jHqXmCxoDR = false;
      bool dqQNDtegzp = false;
      bool hZHIQNjNAR = false;
      bool EbGkXwWTeZ = false;
      bool TyVNotdqbB = false;
      bool VKNiZKzhGZ = false;
      string ZYkZxRabfa;
      string bOwMofpkVL;
      string LfVtAClPRM;
      string omGJggoqcb;
      string TuZeUByfXX;
      string zZWQqtCqZt;
      string eLKSlnImfH;
      string pyHsqQFpYy;
      string EGqsNOPpRl;
      string dxRhxIkHsf;
      string sLzQhARcYa;
      string nMSapXUQEX;
      string XSUtdsgZwi;
      string eyxrFsGaKM;
      string wmQqxReqrZ;
      string mTCUHapFlo;
      string TrgpupPZVw;
      string RtFqakBcwM;
      string NphWuLubjd;
      string CBnVsEFawH;
      if(ZYkZxRabfa == sLzQhARcYa){BFUuHsNKtW = true;}
      else if(sLzQhARcYa == ZYkZxRabfa){IXzbHUzmbD = true;}
      if(bOwMofpkVL == nMSapXUQEX){YMJZacKKti = true;}
      else if(nMSapXUQEX == bOwMofpkVL){IorwSwofsH = true;}
      if(LfVtAClPRM == XSUtdsgZwi){tmoqtQFjxW = true;}
      else if(XSUtdsgZwi == LfVtAClPRM){DNrSbRmZeS = true;}
      if(omGJggoqcb == eyxrFsGaKM){eafoKHUlOB = true;}
      else if(eyxrFsGaKM == omGJggoqcb){luFewBqMYI = true;}
      if(TuZeUByfXX == wmQqxReqrZ){xjhNFoqOuQ = true;}
      else if(wmQqxReqrZ == TuZeUByfXX){jHqXmCxoDR = true;}
      if(zZWQqtCqZt == mTCUHapFlo){sufNMOQdBq = true;}
      else if(mTCUHapFlo == zZWQqtCqZt){dqQNDtegzp = true;}
      if(eLKSlnImfH == TrgpupPZVw){ndMWqygTOS = true;}
      else if(TrgpupPZVw == eLKSlnImfH){hZHIQNjNAR = true;}
      if(pyHsqQFpYy == RtFqakBcwM){IXwslJFalE = true;}
      if(EGqsNOPpRl == NphWuLubjd){YqogcitSbw = true;}
      if(dxRhxIkHsf == CBnVsEFawH){qpkWNSXKVG = true;}
      while(RtFqakBcwM == pyHsqQFpYy){EbGkXwWTeZ = true;}
      while(NphWuLubjd == NphWuLubjd){TyVNotdqbB = true;}
      while(CBnVsEFawH == CBnVsEFawH){VKNiZKzhGZ = true;}
      if(BFUuHsNKtW == true){BFUuHsNKtW = false;}
      if(YMJZacKKti == true){YMJZacKKti = false;}
      if(tmoqtQFjxW == true){tmoqtQFjxW = false;}
      if(eafoKHUlOB == true){eafoKHUlOB = false;}
      if(xjhNFoqOuQ == true){xjhNFoqOuQ = false;}
      if(sufNMOQdBq == true){sufNMOQdBq = false;}
      if(ndMWqygTOS == true){ndMWqygTOS = false;}
      if(IXwslJFalE == true){IXwslJFalE = false;}
      if(YqogcitSbw == true){YqogcitSbw = false;}
      if(qpkWNSXKVG == true){qpkWNSXKVG = false;}
      if(IXzbHUzmbD == true){IXzbHUzmbD = false;}
      if(IorwSwofsH == true){IorwSwofsH = false;}
      if(DNrSbRmZeS == true){DNrSbRmZeS = false;}
      if(luFewBqMYI == true){luFewBqMYI = false;}
      if(jHqXmCxoDR == true){jHqXmCxoDR = false;}
      if(dqQNDtegzp == true){dqQNDtegzp = false;}
      if(hZHIQNjNAR == true){hZHIQNjNAR = false;}
      if(EbGkXwWTeZ == true){EbGkXwWTeZ = false;}
      if(TyVNotdqbB == true){TyVNotdqbB = false;}
      if(VKNiZKzhGZ == true){VKNiZKzhGZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PTHFQXOFKX
{ 
  void dlAUlNKtii()
  { 
      bool VebekDMkSe = false;
      bool lrHXQClgat = false;
      bool zEauKfVgBb = false;
      bool nQeQeyTGHu = false;
      bool bUITYHqGmg = false;
      bool IpLkbQDfTF = false;
      bool gfipqUNprS = false;
      bool hfYeRdwHWD = false;
      bool oPsUSxEsnN = false;
      bool tmmCNukRcD = false;
      bool sAOUycQgSy = false;
      bool TwJQPRlOXs = false;
      bool PUCdYtsWQW = false;
      bool reeSJnBYVp = false;
      bool fXZpsxdVlw = false;
      bool IWsimYxjuD = false;
      bool jtPwFoRqHb = false;
      bool QNrhNrtLja = false;
      bool QWjUNVkuej = false;
      bool pQcSFkIckE = false;
      string dUOmDmuQiB;
      string tljBnOYZqE;
      string TfeRXLlKDG;
      string tJebMmPFur;
      string sxQkgOhOdb;
      string ucfnrxoxPq;
      string AkMcGjHHoA;
      string zSezLWPtjI;
      string cXfbKQcpiO;
      string xRoDqIjndw;
      string HZZcbbygcV;
      string huMHNbEkRo;
      string GQXZDhdaHD;
      string mbPnBCyDzh;
      string SwMNgBEhoO;
      string EyVoopCzYt;
      string yXYZhFfYGK;
      string dAkjWKEJrB;
      string cwkrynGayK;
      string AydEiuWmeb;
      if(dUOmDmuQiB == HZZcbbygcV){VebekDMkSe = true;}
      else if(HZZcbbygcV == dUOmDmuQiB){sAOUycQgSy = true;}
      if(tljBnOYZqE == huMHNbEkRo){lrHXQClgat = true;}
      else if(huMHNbEkRo == tljBnOYZqE){TwJQPRlOXs = true;}
      if(TfeRXLlKDG == GQXZDhdaHD){zEauKfVgBb = true;}
      else if(GQXZDhdaHD == TfeRXLlKDG){PUCdYtsWQW = true;}
      if(tJebMmPFur == mbPnBCyDzh){nQeQeyTGHu = true;}
      else if(mbPnBCyDzh == tJebMmPFur){reeSJnBYVp = true;}
      if(sxQkgOhOdb == SwMNgBEhoO){bUITYHqGmg = true;}
      else if(SwMNgBEhoO == sxQkgOhOdb){fXZpsxdVlw = true;}
      if(ucfnrxoxPq == EyVoopCzYt){IpLkbQDfTF = true;}
      else if(EyVoopCzYt == ucfnrxoxPq){IWsimYxjuD = true;}
      if(AkMcGjHHoA == yXYZhFfYGK){gfipqUNprS = true;}
      else if(yXYZhFfYGK == AkMcGjHHoA){jtPwFoRqHb = true;}
      if(zSezLWPtjI == dAkjWKEJrB){hfYeRdwHWD = true;}
      if(cXfbKQcpiO == cwkrynGayK){oPsUSxEsnN = true;}
      if(xRoDqIjndw == AydEiuWmeb){tmmCNukRcD = true;}
      while(dAkjWKEJrB == zSezLWPtjI){QNrhNrtLja = true;}
      while(cwkrynGayK == cwkrynGayK){QWjUNVkuej = true;}
      while(AydEiuWmeb == AydEiuWmeb){pQcSFkIckE = true;}
      if(VebekDMkSe == true){VebekDMkSe = false;}
      if(lrHXQClgat == true){lrHXQClgat = false;}
      if(zEauKfVgBb == true){zEauKfVgBb = false;}
      if(nQeQeyTGHu == true){nQeQeyTGHu = false;}
      if(bUITYHqGmg == true){bUITYHqGmg = false;}
      if(IpLkbQDfTF == true){IpLkbQDfTF = false;}
      if(gfipqUNprS == true){gfipqUNprS = false;}
      if(hfYeRdwHWD == true){hfYeRdwHWD = false;}
      if(oPsUSxEsnN == true){oPsUSxEsnN = false;}
      if(tmmCNukRcD == true){tmmCNukRcD = false;}
      if(sAOUycQgSy == true){sAOUycQgSy = false;}
      if(TwJQPRlOXs == true){TwJQPRlOXs = false;}
      if(PUCdYtsWQW == true){PUCdYtsWQW = false;}
      if(reeSJnBYVp == true){reeSJnBYVp = false;}
      if(fXZpsxdVlw == true){fXZpsxdVlw = false;}
      if(IWsimYxjuD == true){IWsimYxjuD = false;}
      if(jtPwFoRqHb == true){jtPwFoRqHb = false;}
      if(QNrhNrtLja == true){QNrhNrtLja = false;}
      if(QWjUNVkuej == true){QWjUNVkuej = false;}
      if(pQcSFkIckE == true){pQcSFkIckE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SDVMISPHDY
{ 
  void lWBVihoViA()
  { 
      bool HNVRQxYhwR = false;
      bool MZBJRqgYtE = false;
      bool RHbQbUYiAc = false;
      bool UolXywROKr = false;
      bool DzFhSfijqa = false;
      bool JCFwDzlEpw = false;
      bool YpgSwXndKU = false;
      bool ZSOCARBsyw = false;
      bool koqZSSioUz = false;
      bool KMYNTMSmkt = false;
      bool qFYVAqmDwk = false;
      bool xrFsKiyGzd = false;
      bool nzILJMtAim = false;
      bool yOIEEfPVYb = false;
      bool efsiBSHeCj = false;
      bool OMmGFrwMMn = false;
      bool wmUIliiAne = false;
      bool TcgXzIFYKp = false;
      bool FOxyYlaCzM = false;
      bool jCIkerLkxR = false;
      string rOTNJfczMB;
      string dRtACnhigV;
      string PKahdJJCMR;
      string bdSSjiMfBc;
      string UeLQkXJXFB;
      string kbCrKgnkjA;
      string WZmuZzybPS;
      string aBhEBkzKxG;
      string zlxLfzaaHC;
      string ubwAGtrPqk;
      string YgHmajtyqZ;
      string hdmdAjcbPZ;
      string XXUMXyFgxH;
      string siTMgSeJjw;
      string FbihURnRAV;
      string QQAQMBMtPb;
      string dNAjgzKawh;
      string ETqSUunlrF;
      string KmfbpchCze;
      string FjtIRqazAU;
      if(rOTNJfczMB == YgHmajtyqZ){HNVRQxYhwR = true;}
      else if(YgHmajtyqZ == rOTNJfczMB){qFYVAqmDwk = true;}
      if(dRtACnhigV == hdmdAjcbPZ){MZBJRqgYtE = true;}
      else if(hdmdAjcbPZ == dRtACnhigV){xrFsKiyGzd = true;}
      if(PKahdJJCMR == XXUMXyFgxH){RHbQbUYiAc = true;}
      else if(XXUMXyFgxH == PKahdJJCMR){nzILJMtAim = true;}
      if(bdSSjiMfBc == siTMgSeJjw){UolXywROKr = true;}
      else if(siTMgSeJjw == bdSSjiMfBc){yOIEEfPVYb = true;}
      if(UeLQkXJXFB == FbihURnRAV){DzFhSfijqa = true;}
      else if(FbihURnRAV == UeLQkXJXFB){efsiBSHeCj = true;}
      if(kbCrKgnkjA == QQAQMBMtPb){JCFwDzlEpw = true;}
      else if(QQAQMBMtPb == kbCrKgnkjA){OMmGFrwMMn = true;}
      if(WZmuZzybPS == dNAjgzKawh){YpgSwXndKU = true;}
      else if(dNAjgzKawh == WZmuZzybPS){wmUIliiAne = true;}
      if(aBhEBkzKxG == ETqSUunlrF){ZSOCARBsyw = true;}
      if(zlxLfzaaHC == KmfbpchCze){koqZSSioUz = true;}
      if(ubwAGtrPqk == FjtIRqazAU){KMYNTMSmkt = true;}
      while(ETqSUunlrF == aBhEBkzKxG){TcgXzIFYKp = true;}
      while(KmfbpchCze == KmfbpchCze){FOxyYlaCzM = true;}
      while(FjtIRqazAU == FjtIRqazAU){jCIkerLkxR = true;}
      if(HNVRQxYhwR == true){HNVRQxYhwR = false;}
      if(MZBJRqgYtE == true){MZBJRqgYtE = false;}
      if(RHbQbUYiAc == true){RHbQbUYiAc = false;}
      if(UolXywROKr == true){UolXywROKr = false;}
      if(DzFhSfijqa == true){DzFhSfijqa = false;}
      if(JCFwDzlEpw == true){JCFwDzlEpw = false;}
      if(YpgSwXndKU == true){YpgSwXndKU = false;}
      if(ZSOCARBsyw == true){ZSOCARBsyw = false;}
      if(koqZSSioUz == true){koqZSSioUz = false;}
      if(KMYNTMSmkt == true){KMYNTMSmkt = false;}
      if(qFYVAqmDwk == true){qFYVAqmDwk = false;}
      if(xrFsKiyGzd == true){xrFsKiyGzd = false;}
      if(nzILJMtAim == true){nzILJMtAim = false;}
      if(yOIEEfPVYb == true){yOIEEfPVYb = false;}
      if(efsiBSHeCj == true){efsiBSHeCj = false;}
      if(OMmGFrwMMn == true){OMmGFrwMMn = false;}
      if(wmUIliiAne == true){wmUIliiAne = false;}
      if(TcgXzIFYKp == true){TcgXzIFYKp = false;}
      if(FOxyYlaCzM == true){FOxyYlaCzM = false;}
      if(jCIkerLkxR == true){jCIkerLkxR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EDLGOAREJK
{ 
  void ItltodTlmT()
  { 
      bool nuRVgstpwD = false;
      bool RUpPsUAKnf = false;
      bool VYlQVVkBQO = false;
      bool XthuItKdHC = false;
      bool CetZSaRRfu = false;
      bool NwzVePIAAL = false;
      bool HsYgfXltHz = false;
      bool KVDldpdLxt = false;
      bool DTUVAatMQr = false;
      bool kJdwuIFMtu = false;
      bool nXJgkqsNqn = false;
      bool lxCFHnXDfE = false;
      bool cZcONBrGqU = false;
      bool kQQCFfJmjJ = false;
      bool hfUcGnGXnG = false;
      bool kBgpROttTj = false;
      bool zlWWCUfAAb = false;
      bool djSWWwFAIY = false;
      bool tUSjjijajq = false;
      bool kOTAKuJxZk = false;
      string nICFQxYzGj;
      string kOoqefomHZ;
      string OmuuZdHESD;
      string nqpybusmsY;
      string snYNOgJnwX;
      string ujiYWAMHfl;
      string pUfDwtYpPi;
      string mCtigaOgfs;
      string TSHtHEHQab;
      string ilGGhYHURU;
      string HTYNksoArw;
      string keamSXMkwr;
      string lHOmAAunAH;
      string StPLkAstJN;
      string OHYeqDKTnK;
      string LVYYhAElMj;
      string xAAjcqOPBR;
      string dSbhcehjuw;
      string pbAouxUpck;
      string wHgZQOHnBA;
      if(nICFQxYzGj == HTYNksoArw){nuRVgstpwD = true;}
      else if(HTYNksoArw == nICFQxYzGj){nXJgkqsNqn = true;}
      if(kOoqefomHZ == keamSXMkwr){RUpPsUAKnf = true;}
      else if(keamSXMkwr == kOoqefomHZ){lxCFHnXDfE = true;}
      if(OmuuZdHESD == lHOmAAunAH){VYlQVVkBQO = true;}
      else if(lHOmAAunAH == OmuuZdHESD){cZcONBrGqU = true;}
      if(nqpybusmsY == StPLkAstJN){XthuItKdHC = true;}
      else if(StPLkAstJN == nqpybusmsY){kQQCFfJmjJ = true;}
      if(snYNOgJnwX == OHYeqDKTnK){CetZSaRRfu = true;}
      else if(OHYeqDKTnK == snYNOgJnwX){hfUcGnGXnG = true;}
      if(ujiYWAMHfl == LVYYhAElMj){NwzVePIAAL = true;}
      else if(LVYYhAElMj == ujiYWAMHfl){kBgpROttTj = true;}
      if(pUfDwtYpPi == xAAjcqOPBR){HsYgfXltHz = true;}
      else if(xAAjcqOPBR == pUfDwtYpPi){zlWWCUfAAb = true;}
      if(mCtigaOgfs == dSbhcehjuw){KVDldpdLxt = true;}
      if(TSHtHEHQab == pbAouxUpck){DTUVAatMQr = true;}
      if(ilGGhYHURU == wHgZQOHnBA){kJdwuIFMtu = true;}
      while(dSbhcehjuw == mCtigaOgfs){djSWWwFAIY = true;}
      while(pbAouxUpck == pbAouxUpck){tUSjjijajq = true;}
      while(wHgZQOHnBA == wHgZQOHnBA){kOTAKuJxZk = true;}
      if(nuRVgstpwD == true){nuRVgstpwD = false;}
      if(RUpPsUAKnf == true){RUpPsUAKnf = false;}
      if(VYlQVVkBQO == true){VYlQVVkBQO = false;}
      if(XthuItKdHC == true){XthuItKdHC = false;}
      if(CetZSaRRfu == true){CetZSaRRfu = false;}
      if(NwzVePIAAL == true){NwzVePIAAL = false;}
      if(HsYgfXltHz == true){HsYgfXltHz = false;}
      if(KVDldpdLxt == true){KVDldpdLxt = false;}
      if(DTUVAatMQr == true){DTUVAatMQr = false;}
      if(kJdwuIFMtu == true){kJdwuIFMtu = false;}
      if(nXJgkqsNqn == true){nXJgkqsNqn = false;}
      if(lxCFHnXDfE == true){lxCFHnXDfE = false;}
      if(cZcONBrGqU == true){cZcONBrGqU = false;}
      if(kQQCFfJmjJ == true){kQQCFfJmjJ = false;}
      if(hfUcGnGXnG == true){hfUcGnGXnG = false;}
      if(kBgpROttTj == true){kBgpROttTj = false;}
      if(zlWWCUfAAb == true){zlWWCUfAAb = false;}
      if(djSWWwFAIY == true){djSWWwFAIY = false;}
      if(tUSjjijajq == true){tUSjjijajq = false;}
      if(kOTAKuJxZk == true){kOTAKuJxZk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUMOJBWPUN
{ 
  void fLWcMnYIyY()
  { 
      bool GazXRbiQTH = false;
      bool NUKHUNZHJx = false;
      bool WhtbphZnKk = false;
      bool FgqDyTidXo = false;
      bool cqxzWblMCk = false;
      bool FBrNkYfWgj = false;
      bool CtFiBfdHIA = false;
      bool ewjTTejtEN = false;
      bool uMlYfEocRZ = false;
      bool mLwnmilOxp = false;
      bool yeEBGJQXtF = false;
      bool nlRTnoHfCx = false;
      bool pAoiNSzwgk = false;
      bool sUxOPQIjSW = false;
      bool mRiLkBsczy = false;
      bool aFLzAyoUnm = false;
      bool JUqIMSoDDW = false;
      bool fWMfKYRdxL = false;
      bool ZVwhKmJxNR = false;
      bool amwfMRZZyR = false;
      string sHzhasZLFu;
      string DuIVnViQJM;
      string XWtHAIHtlU;
      string VyqDVUulke;
      string bUNhrLxTpM;
      string lWMzSVNqhR;
      string keZkYEDFzS;
      string ZxfekCJLOo;
      string LmEZhzlqjA;
      string HDESswubJm;
      string HrUXlnpgOQ;
      string MBcrGxaACY;
      string SLVzLVsNkn;
      string HgCbgTSfmt;
      string IEcTmFaLLw;
      string VuYjUwVVMP;
      string ucwaIezALm;
      string etMIQNiBLF;
      string thCoRLIRGj;
      string xwTXyfIBKI;
      if(sHzhasZLFu == HrUXlnpgOQ){GazXRbiQTH = true;}
      else if(HrUXlnpgOQ == sHzhasZLFu){yeEBGJQXtF = true;}
      if(DuIVnViQJM == MBcrGxaACY){NUKHUNZHJx = true;}
      else if(MBcrGxaACY == DuIVnViQJM){nlRTnoHfCx = true;}
      if(XWtHAIHtlU == SLVzLVsNkn){WhtbphZnKk = true;}
      else if(SLVzLVsNkn == XWtHAIHtlU){pAoiNSzwgk = true;}
      if(VyqDVUulke == HgCbgTSfmt){FgqDyTidXo = true;}
      else if(HgCbgTSfmt == VyqDVUulke){sUxOPQIjSW = true;}
      if(bUNhrLxTpM == IEcTmFaLLw){cqxzWblMCk = true;}
      else if(IEcTmFaLLw == bUNhrLxTpM){mRiLkBsczy = true;}
      if(lWMzSVNqhR == VuYjUwVVMP){FBrNkYfWgj = true;}
      else if(VuYjUwVVMP == lWMzSVNqhR){aFLzAyoUnm = true;}
      if(keZkYEDFzS == ucwaIezALm){CtFiBfdHIA = true;}
      else if(ucwaIezALm == keZkYEDFzS){JUqIMSoDDW = true;}
      if(ZxfekCJLOo == etMIQNiBLF){ewjTTejtEN = true;}
      if(LmEZhzlqjA == thCoRLIRGj){uMlYfEocRZ = true;}
      if(HDESswubJm == xwTXyfIBKI){mLwnmilOxp = true;}
      while(etMIQNiBLF == ZxfekCJLOo){fWMfKYRdxL = true;}
      while(thCoRLIRGj == thCoRLIRGj){ZVwhKmJxNR = true;}
      while(xwTXyfIBKI == xwTXyfIBKI){amwfMRZZyR = true;}
      if(GazXRbiQTH == true){GazXRbiQTH = false;}
      if(NUKHUNZHJx == true){NUKHUNZHJx = false;}
      if(WhtbphZnKk == true){WhtbphZnKk = false;}
      if(FgqDyTidXo == true){FgqDyTidXo = false;}
      if(cqxzWblMCk == true){cqxzWblMCk = false;}
      if(FBrNkYfWgj == true){FBrNkYfWgj = false;}
      if(CtFiBfdHIA == true){CtFiBfdHIA = false;}
      if(ewjTTejtEN == true){ewjTTejtEN = false;}
      if(uMlYfEocRZ == true){uMlYfEocRZ = false;}
      if(mLwnmilOxp == true){mLwnmilOxp = false;}
      if(yeEBGJQXtF == true){yeEBGJQXtF = false;}
      if(nlRTnoHfCx == true){nlRTnoHfCx = false;}
      if(pAoiNSzwgk == true){pAoiNSzwgk = false;}
      if(sUxOPQIjSW == true){sUxOPQIjSW = false;}
      if(mRiLkBsczy == true){mRiLkBsczy = false;}
      if(aFLzAyoUnm == true){aFLzAyoUnm = false;}
      if(JUqIMSoDDW == true){JUqIMSoDDW = false;}
      if(fWMfKYRdxL == true){fWMfKYRdxL = false;}
      if(ZVwhKmJxNR == true){ZVwhKmJxNR = false;}
      if(amwfMRZZyR == true){amwfMRZZyR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TTAZQGTTGZ
{ 
  void GFnnfFfoxX()
  { 
      bool iPjzgUZexI = false;
      bool mRqzBLDVOB = false;
      bool xNalsLMUhk = false;
      bool ZIJddObixI = false;
      bool FPFSiBuoGr = false;
      bool oZtYSVnxFV = false;
      bool IEwLieIMUm = false;
      bool jTYGugIICr = false;
      bool PXNpuzOkLI = false;
      bool ZddbzBTsiE = false;
      bool siTTHVBncl = false;
      bool NftNFkpGPj = false;
      bool PWBMMFpwGt = false;
      bool MOYyygDthZ = false;
      bool yZIZttiPWO = false;
      bool KMcznVgGHC = false;
      bool fFghYyGwOX = false;
      bool gwYpkpObRS = false;
      bool VZYrjAlZJc = false;
      bool AxmfssrZAw = false;
      string lhAXWIwBeC;
      string ZYKbMTBcOk;
      string GnWjkZUNTN;
      string gtMtLEsRou;
      string JCwGejLFiC;
      string KUhTUxKPmw;
      string nhhQVfLQQH;
      string ZimSaDrPFA;
      string OOdQDLMsYN;
      string tcesGaUeky;
      string XtoabbgOrQ;
      string FtKlgYERNJ;
      string TSrCNxEtMA;
      string iMdGcUZCna;
      string eyAIIzSsLg;
      string WDRbeFBlNe;
      string WlBrhrPDJM;
      string zBcldVRjtN;
      string dLiecfuCbW;
      string SmoIEswIZP;
      if(lhAXWIwBeC == XtoabbgOrQ){iPjzgUZexI = true;}
      else if(XtoabbgOrQ == lhAXWIwBeC){siTTHVBncl = true;}
      if(ZYKbMTBcOk == FtKlgYERNJ){mRqzBLDVOB = true;}
      else if(FtKlgYERNJ == ZYKbMTBcOk){NftNFkpGPj = true;}
      if(GnWjkZUNTN == TSrCNxEtMA){xNalsLMUhk = true;}
      else if(TSrCNxEtMA == GnWjkZUNTN){PWBMMFpwGt = true;}
      if(gtMtLEsRou == iMdGcUZCna){ZIJddObixI = true;}
      else if(iMdGcUZCna == gtMtLEsRou){MOYyygDthZ = true;}
      if(JCwGejLFiC == eyAIIzSsLg){FPFSiBuoGr = true;}
      else if(eyAIIzSsLg == JCwGejLFiC){yZIZttiPWO = true;}
      if(KUhTUxKPmw == WDRbeFBlNe){oZtYSVnxFV = true;}
      else if(WDRbeFBlNe == KUhTUxKPmw){KMcznVgGHC = true;}
      if(nhhQVfLQQH == WlBrhrPDJM){IEwLieIMUm = true;}
      else if(WlBrhrPDJM == nhhQVfLQQH){fFghYyGwOX = true;}
      if(ZimSaDrPFA == zBcldVRjtN){jTYGugIICr = true;}
      if(OOdQDLMsYN == dLiecfuCbW){PXNpuzOkLI = true;}
      if(tcesGaUeky == SmoIEswIZP){ZddbzBTsiE = true;}
      while(zBcldVRjtN == ZimSaDrPFA){gwYpkpObRS = true;}
      while(dLiecfuCbW == dLiecfuCbW){VZYrjAlZJc = true;}
      while(SmoIEswIZP == SmoIEswIZP){AxmfssrZAw = true;}
      if(iPjzgUZexI == true){iPjzgUZexI = false;}
      if(mRqzBLDVOB == true){mRqzBLDVOB = false;}
      if(xNalsLMUhk == true){xNalsLMUhk = false;}
      if(ZIJddObixI == true){ZIJddObixI = false;}
      if(FPFSiBuoGr == true){FPFSiBuoGr = false;}
      if(oZtYSVnxFV == true){oZtYSVnxFV = false;}
      if(IEwLieIMUm == true){IEwLieIMUm = false;}
      if(jTYGugIICr == true){jTYGugIICr = false;}
      if(PXNpuzOkLI == true){PXNpuzOkLI = false;}
      if(ZddbzBTsiE == true){ZddbzBTsiE = false;}
      if(siTTHVBncl == true){siTTHVBncl = false;}
      if(NftNFkpGPj == true){NftNFkpGPj = false;}
      if(PWBMMFpwGt == true){PWBMMFpwGt = false;}
      if(MOYyygDthZ == true){MOYyygDthZ = false;}
      if(yZIZttiPWO == true){yZIZttiPWO = false;}
      if(KMcznVgGHC == true){KMcznVgGHC = false;}
      if(fFghYyGwOX == true){fFghYyGwOX = false;}
      if(gwYpkpObRS == true){gwYpkpObRS = false;}
      if(VZYrjAlZJc == true){VZYrjAlZJc = false;}
      if(AxmfssrZAw == true){AxmfssrZAw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PVPAFEWYVY
{ 
  void QPsCsWnpRG()
  { 
      bool cCZdTEaNzw = false;
      bool jwRTCXErJC = false;
      bool spKPKHoSWZ = false;
      bool BhlIucBfxW = false;
      bool OdGktVkpoY = false;
      bool hCushmrJTL = false;
      bool OIqZtBKJXY = false;
      bool WXtmmPiYVn = false;
      bool VzcxqzmrZI = false;
      bool jqMlHGmfqs = false;
      bool LbRQCKIHFS = false;
      bool DTnepOetiu = false;
      bool NRjOofKIeg = false;
      bool bChcbtgMug = false;
      bool pfmHEQChws = false;
      bool arxuetrDaW = false;
      bool zAbXpAlLCu = false;
      bool gSzBEhdbJY = false;
      bool ccLlGjElxh = false;
      bool CdkYgpDPQD = false;
      string UaHupEPuPQ;
      string UqBkjmkCPf;
      string jiRVrVfVdF;
      string SKFYMxzVCV;
      string xmJYDmaZdw;
      string LhAzQlIkCU;
      string YsRKyKkbYm;
      string nPAtixYsSF;
      string tGrgsjKGHa;
      string nNShxEVyar;
      string CyApIwhGPT;
      string MOSxZRAjQO;
      string AdUyyawSwe;
      string aZSZCwGBYx;
      string BDpmNZuUHe;
      string DkhLrXdCrg;
      string zPJkrlwruc;
      string LzKTMwmgjY;
      string ebKRaprGhe;
      string SDJrxltFub;
      if(UaHupEPuPQ == CyApIwhGPT){cCZdTEaNzw = true;}
      else if(CyApIwhGPT == UaHupEPuPQ){LbRQCKIHFS = true;}
      if(UqBkjmkCPf == MOSxZRAjQO){jwRTCXErJC = true;}
      else if(MOSxZRAjQO == UqBkjmkCPf){DTnepOetiu = true;}
      if(jiRVrVfVdF == AdUyyawSwe){spKPKHoSWZ = true;}
      else if(AdUyyawSwe == jiRVrVfVdF){NRjOofKIeg = true;}
      if(SKFYMxzVCV == aZSZCwGBYx){BhlIucBfxW = true;}
      else if(aZSZCwGBYx == SKFYMxzVCV){bChcbtgMug = true;}
      if(xmJYDmaZdw == BDpmNZuUHe){OdGktVkpoY = true;}
      else if(BDpmNZuUHe == xmJYDmaZdw){pfmHEQChws = true;}
      if(LhAzQlIkCU == DkhLrXdCrg){hCushmrJTL = true;}
      else if(DkhLrXdCrg == LhAzQlIkCU){arxuetrDaW = true;}
      if(YsRKyKkbYm == zPJkrlwruc){OIqZtBKJXY = true;}
      else if(zPJkrlwruc == YsRKyKkbYm){zAbXpAlLCu = true;}
      if(nPAtixYsSF == LzKTMwmgjY){WXtmmPiYVn = true;}
      if(tGrgsjKGHa == ebKRaprGhe){VzcxqzmrZI = true;}
      if(nNShxEVyar == SDJrxltFub){jqMlHGmfqs = true;}
      while(LzKTMwmgjY == nPAtixYsSF){gSzBEhdbJY = true;}
      while(ebKRaprGhe == ebKRaprGhe){ccLlGjElxh = true;}
      while(SDJrxltFub == SDJrxltFub){CdkYgpDPQD = true;}
      if(cCZdTEaNzw == true){cCZdTEaNzw = false;}
      if(jwRTCXErJC == true){jwRTCXErJC = false;}
      if(spKPKHoSWZ == true){spKPKHoSWZ = false;}
      if(BhlIucBfxW == true){BhlIucBfxW = false;}
      if(OdGktVkpoY == true){OdGktVkpoY = false;}
      if(hCushmrJTL == true){hCushmrJTL = false;}
      if(OIqZtBKJXY == true){OIqZtBKJXY = false;}
      if(WXtmmPiYVn == true){WXtmmPiYVn = false;}
      if(VzcxqzmrZI == true){VzcxqzmrZI = false;}
      if(jqMlHGmfqs == true){jqMlHGmfqs = false;}
      if(LbRQCKIHFS == true){LbRQCKIHFS = false;}
      if(DTnepOetiu == true){DTnepOetiu = false;}
      if(NRjOofKIeg == true){NRjOofKIeg = false;}
      if(bChcbtgMug == true){bChcbtgMug = false;}
      if(pfmHEQChws == true){pfmHEQChws = false;}
      if(arxuetrDaW == true){arxuetrDaW = false;}
      if(zAbXpAlLCu == true){zAbXpAlLCu = false;}
      if(gSzBEhdbJY == true){gSzBEhdbJY = false;}
      if(ccLlGjElxh == true){ccLlGjElxh = false;}
      if(CdkYgpDPQD == true){CdkYgpDPQD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TXSYXAAXSJ
{ 
  void CbphAtRBrQ()
  { 
      bool LutaTqLVbt = false;
      bool uCsQRBykZg = false;
      bool ePJBHOlgOE = false;
      bool zFcbbzIwCC = false;
      bool pSyTTnMxpt = false;
      bool MhqVHwlsSF = false;
      bool FdHXupZRoR = false;
      bool rBiWqLQpgT = false;
      bool BnpTqRNGUe = false;
      bool NPdwxLKaYd = false;
      bool OuIYBKyTeu = false;
      bool euLzDQnnfc = false;
      bool bTwJEcXlZe = false;
      bool ApRDFGfRSf = false;
      bool SsbZARDesg = false;
      bool XWtuBtyzUY = false;
      bool mLtztodItx = false;
      bool kVVAJhrWJl = false;
      bool YsssHduVBK = false;
      bool HfxssHzbeK = false;
      string hVMtNJoKja;
      string dCMTdilzas;
      string feDcnNlHEH;
      string XqzXAcBPzt;
      string tRSstenwtI;
      string oTyGACSiGz;
      string XhGcClCnSA;
      string gWzfzOMJiI;
      string ZpNwSDrsXx;
      string KSIAVMLpqH;
      string bzctaSURHl;
      string pIzxZhTKJy;
      string sJQUoONyKl;
      string CVSbgZNSUA;
      string hallGBSKan;
      string rBfrNRhHEM;
      string EWHUiUpXQz;
      string TAoJPSWeNm;
      string uDXVtBoaNO;
      string qFOIuLSRCl;
      if(hVMtNJoKja == bzctaSURHl){LutaTqLVbt = true;}
      else if(bzctaSURHl == hVMtNJoKja){OuIYBKyTeu = true;}
      if(dCMTdilzas == pIzxZhTKJy){uCsQRBykZg = true;}
      else if(pIzxZhTKJy == dCMTdilzas){euLzDQnnfc = true;}
      if(feDcnNlHEH == sJQUoONyKl){ePJBHOlgOE = true;}
      else if(sJQUoONyKl == feDcnNlHEH){bTwJEcXlZe = true;}
      if(XqzXAcBPzt == CVSbgZNSUA){zFcbbzIwCC = true;}
      else if(CVSbgZNSUA == XqzXAcBPzt){ApRDFGfRSf = true;}
      if(tRSstenwtI == hallGBSKan){pSyTTnMxpt = true;}
      else if(hallGBSKan == tRSstenwtI){SsbZARDesg = true;}
      if(oTyGACSiGz == rBfrNRhHEM){MhqVHwlsSF = true;}
      else if(rBfrNRhHEM == oTyGACSiGz){XWtuBtyzUY = true;}
      if(XhGcClCnSA == EWHUiUpXQz){FdHXupZRoR = true;}
      else if(EWHUiUpXQz == XhGcClCnSA){mLtztodItx = true;}
      if(gWzfzOMJiI == TAoJPSWeNm){rBiWqLQpgT = true;}
      if(ZpNwSDrsXx == uDXVtBoaNO){BnpTqRNGUe = true;}
      if(KSIAVMLpqH == qFOIuLSRCl){NPdwxLKaYd = true;}
      while(TAoJPSWeNm == gWzfzOMJiI){kVVAJhrWJl = true;}
      while(uDXVtBoaNO == uDXVtBoaNO){YsssHduVBK = true;}
      while(qFOIuLSRCl == qFOIuLSRCl){HfxssHzbeK = true;}
      if(LutaTqLVbt == true){LutaTqLVbt = false;}
      if(uCsQRBykZg == true){uCsQRBykZg = false;}
      if(ePJBHOlgOE == true){ePJBHOlgOE = false;}
      if(zFcbbzIwCC == true){zFcbbzIwCC = false;}
      if(pSyTTnMxpt == true){pSyTTnMxpt = false;}
      if(MhqVHwlsSF == true){MhqVHwlsSF = false;}
      if(FdHXupZRoR == true){FdHXupZRoR = false;}
      if(rBiWqLQpgT == true){rBiWqLQpgT = false;}
      if(BnpTqRNGUe == true){BnpTqRNGUe = false;}
      if(NPdwxLKaYd == true){NPdwxLKaYd = false;}
      if(OuIYBKyTeu == true){OuIYBKyTeu = false;}
      if(euLzDQnnfc == true){euLzDQnnfc = false;}
      if(bTwJEcXlZe == true){bTwJEcXlZe = false;}
      if(ApRDFGfRSf == true){ApRDFGfRSf = false;}
      if(SsbZARDesg == true){SsbZARDesg = false;}
      if(XWtuBtyzUY == true){XWtuBtyzUY = false;}
      if(mLtztodItx == true){mLtztodItx = false;}
      if(kVVAJhrWJl == true){kVVAJhrWJl = false;}
      if(YsssHduVBK == true){YsssHduVBK = false;}
      if(HfxssHzbeK == true){HfxssHzbeK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BYAUEEMOTB
{ 
  void KFxHXaLnNy()
  { 
      bool xlMgmCTmhL = false;
      bool dDbWmVCrwG = false;
      bool KOLrWzAnJl = false;
      bool mWalGkfQMw = false;
      bool dBTDOhLNzC = false;
      bool ljOkaiaTJn = false;
      bool BecwXGcpQB = false;
      bool plfzbIuIco = false;
      bool mmnGADHoLX = false;
      bool KLGXuzXWeH = false;
      bool FVxyMzDOJR = false;
      bool mSqUANpWwU = false;
      bool ymerqdeHEb = false;
      bool jXdUjQpptA = false;
      bool zsfsjqTkXg = false;
      bool IBZJJRqEGh = false;
      bool UwKggOoWki = false;
      bool XzbwVFGkHz = false;
      bool JsjWShxTLR = false;
      bool ZkiLeDhzLV = false;
      string KJBEuUTToE;
      string qhJGLKbNmS;
      string uBzhzkCNCc;
      string MWzCDBwuRQ;
      string sjCPfmrJFJ;
      string kimIIIKSEK;
      string SGQMrUhHCK;
      string OguWZLziCM;
      string ssHrqcjqst;
      string qdpHylSoXL;
      string FjGuuEnPix;
      string JbQrRYyXUO;
      string jqOHTkpnXm;
      string rJKpHIlMxm;
      string oTHwkOMxpY;
      string ntUIbNVybK;
      string OAquEzQZkI;
      string llahZPiRWE;
      string XrxzzyoCOs;
      string lmklYncLqk;
      if(KJBEuUTToE == FjGuuEnPix){xlMgmCTmhL = true;}
      else if(FjGuuEnPix == KJBEuUTToE){FVxyMzDOJR = true;}
      if(qhJGLKbNmS == JbQrRYyXUO){dDbWmVCrwG = true;}
      else if(JbQrRYyXUO == qhJGLKbNmS){mSqUANpWwU = true;}
      if(uBzhzkCNCc == jqOHTkpnXm){KOLrWzAnJl = true;}
      else if(jqOHTkpnXm == uBzhzkCNCc){ymerqdeHEb = true;}
      if(MWzCDBwuRQ == rJKpHIlMxm){mWalGkfQMw = true;}
      else if(rJKpHIlMxm == MWzCDBwuRQ){jXdUjQpptA = true;}
      if(sjCPfmrJFJ == oTHwkOMxpY){dBTDOhLNzC = true;}
      else if(oTHwkOMxpY == sjCPfmrJFJ){zsfsjqTkXg = true;}
      if(kimIIIKSEK == ntUIbNVybK){ljOkaiaTJn = true;}
      else if(ntUIbNVybK == kimIIIKSEK){IBZJJRqEGh = true;}
      if(SGQMrUhHCK == OAquEzQZkI){BecwXGcpQB = true;}
      else if(OAquEzQZkI == SGQMrUhHCK){UwKggOoWki = true;}
      if(OguWZLziCM == llahZPiRWE){plfzbIuIco = true;}
      if(ssHrqcjqst == XrxzzyoCOs){mmnGADHoLX = true;}
      if(qdpHylSoXL == lmklYncLqk){KLGXuzXWeH = true;}
      while(llahZPiRWE == OguWZLziCM){XzbwVFGkHz = true;}
      while(XrxzzyoCOs == XrxzzyoCOs){JsjWShxTLR = true;}
      while(lmklYncLqk == lmklYncLqk){ZkiLeDhzLV = true;}
      if(xlMgmCTmhL == true){xlMgmCTmhL = false;}
      if(dDbWmVCrwG == true){dDbWmVCrwG = false;}
      if(KOLrWzAnJl == true){KOLrWzAnJl = false;}
      if(mWalGkfQMw == true){mWalGkfQMw = false;}
      if(dBTDOhLNzC == true){dBTDOhLNzC = false;}
      if(ljOkaiaTJn == true){ljOkaiaTJn = false;}
      if(BecwXGcpQB == true){BecwXGcpQB = false;}
      if(plfzbIuIco == true){plfzbIuIco = false;}
      if(mmnGADHoLX == true){mmnGADHoLX = false;}
      if(KLGXuzXWeH == true){KLGXuzXWeH = false;}
      if(FVxyMzDOJR == true){FVxyMzDOJR = false;}
      if(mSqUANpWwU == true){mSqUANpWwU = false;}
      if(ymerqdeHEb == true){ymerqdeHEb = false;}
      if(jXdUjQpptA == true){jXdUjQpptA = false;}
      if(zsfsjqTkXg == true){zsfsjqTkXg = false;}
      if(IBZJJRqEGh == true){IBZJJRqEGh = false;}
      if(UwKggOoWki == true){UwKggOoWki = false;}
      if(XzbwVFGkHz == true){XzbwVFGkHz = false;}
      if(JsjWShxTLR == true){JsjWShxTLR = false;}
      if(ZkiLeDhzLV == true){ZkiLeDhzLV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RDSFJDZKQL
{ 
  void qpqdwwYPZr()
  { 
      bool drrRuHWteY = false;
      bool WsHiiIyiCI = false;
      bool GbeRPMHoMP = false;
      bool clFgMjmPSZ = false;
      bool OIMlxnFMge = false;
      bool fpakICNaCi = false;
      bool AhhPwkmZWy = false;
      bool VhPbsxOrTa = false;
      bool HtIgilKUYK = false;
      bool VMNjZgaxoL = false;
      bool AephJyayrK = false;
      bool mUGaaFZAfK = false;
      bool ZSBLbJTeBM = false;
      bool WRDIZcDZXk = false;
      bool LLbNXBFlIU = false;
      bool GaQekhdeFz = false;
      bool duxenURyBy = false;
      bool BzbuyNpmma = false;
      bool DhVgFuBXWr = false;
      bool zYUXHPOxZD = false;
      string dsqRFOpbNA;
      string UTORkFSJzf;
      string LzOXDYbawI;
      string HnAdMMfkVA;
      string AncVhhRgnx;
      string fSgIgddSNg;
      string lOfFsgTkFX;
      string YgmyeWVsoU;
      string HtmzboGqxh;
      string iMWoNlIXcB;
      string OfbPXzeidJ;
      string IjdrYrafcD;
      string ZbmWoLJyks;
      string OyQmGaRWbc;
      string KXNnZyidPV;
      string LbtYblsFaL;
      string ofyjtKTply;
      string ZDEAsCOzxq;
      string cfhOhlDrLU;
      string hMwPndZcsP;
      if(dsqRFOpbNA == OfbPXzeidJ){drrRuHWteY = true;}
      else if(OfbPXzeidJ == dsqRFOpbNA){AephJyayrK = true;}
      if(UTORkFSJzf == IjdrYrafcD){WsHiiIyiCI = true;}
      else if(IjdrYrafcD == UTORkFSJzf){mUGaaFZAfK = true;}
      if(LzOXDYbawI == ZbmWoLJyks){GbeRPMHoMP = true;}
      else if(ZbmWoLJyks == LzOXDYbawI){ZSBLbJTeBM = true;}
      if(HnAdMMfkVA == OyQmGaRWbc){clFgMjmPSZ = true;}
      else if(OyQmGaRWbc == HnAdMMfkVA){WRDIZcDZXk = true;}
      if(AncVhhRgnx == KXNnZyidPV){OIMlxnFMge = true;}
      else if(KXNnZyidPV == AncVhhRgnx){LLbNXBFlIU = true;}
      if(fSgIgddSNg == LbtYblsFaL){fpakICNaCi = true;}
      else if(LbtYblsFaL == fSgIgddSNg){GaQekhdeFz = true;}
      if(lOfFsgTkFX == ofyjtKTply){AhhPwkmZWy = true;}
      else if(ofyjtKTply == lOfFsgTkFX){duxenURyBy = true;}
      if(YgmyeWVsoU == ZDEAsCOzxq){VhPbsxOrTa = true;}
      if(HtmzboGqxh == cfhOhlDrLU){HtIgilKUYK = true;}
      if(iMWoNlIXcB == hMwPndZcsP){VMNjZgaxoL = true;}
      while(ZDEAsCOzxq == YgmyeWVsoU){BzbuyNpmma = true;}
      while(cfhOhlDrLU == cfhOhlDrLU){DhVgFuBXWr = true;}
      while(hMwPndZcsP == hMwPndZcsP){zYUXHPOxZD = true;}
      if(drrRuHWteY == true){drrRuHWteY = false;}
      if(WsHiiIyiCI == true){WsHiiIyiCI = false;}
      if(GbeRPMHoMP == true){GbeRPMHoMP = false;}
      if(clFgMjmPSZ == true){clFgMjmPSZ = false;}
      if(OIMlxnFMge == true){OIMlxnFMge = false;}
      if(fpakICNaCi == true){fpakICNaCi = false;}
      if(AhhPwkmZWy == true){AhhPwkmZWy = false;}
      if(VhPbsxOrTa == true){VhPbsxOrTa = false;}
      if(HtIgilKUYK == true){HtIgilKUYK = false;}
      if(VMNjZgaxoL == true){VMNjZgaxoL = false;}
      if(AephJyayrK == true){AephJyayrK = false;}
      if(mUGaaFZAfK == true){mUGaaFZAfK = false;}
      if(ZSBLbJTeBM == true){ZSBLbJTeBM = false;}
      if(WRDIZcDZXk == true){WRDIZcDZXk = false;}
      if(LLbNXBFlIU == true){LLbNXBFlIU = false;}
      if(GaQekhdeFz == true){GaQekhdeFz = false;}
      if(duxenURyBy == true){duxenURyBy = false;}
      if(BzbuyNpmma == true){BzbuyNpmma = false;}
      if(DhVgFuBXWr == true){DhVgFuBXWr = false;}
      if(zYUXHPOxZD == true){zYUXHPOxZD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FJTZCMVMOB
{ 
  void pbjXVKnkoi()
  { 
      bool fVzLOELVZu = false;
      bool fGOAMyqsAH = false;
      bool lgSnffNSNo = false;
      bool EsJFDKpwcK = false;
      bool taKIXOHqAC = false;
      bool MJTrHzDLei = false;
      bool prHjpmxJwB = false;
      bool HuPoMLVJQQ = false;
      bool XVSLctYQxD = false;
      bool HdQtTCTaSj = false;
      bool RyuytQtdfw = false;
      bool dsuNKUYwGu = false;
      bool OfLrtddUVJ = false;
      bool rtpfzZaUQL = false;
      bool AtkBZOiCjz = false;
      bool cWTXVllCEQ = false;
      bool mYIVDiCOOk = false;
      bool sEfttTuJSf = false;
      bool tbkWgUZSKM = false;
      bool mXQzYalOxp = false;
      string IjVgeCrzPa;
      string VyTuJBfmkj;
      string XYwkBPlPmA;
      string KqcTbHGOQV;
      string TrDddMnKUN;
      string noIErjnkfP;
      string QbMPPeUzTC;
      string uRVOQeURGo;
      string abtYLUhXbq;
      string TViBFqfnNz;
      string qnpSSWStnN;
      string OVdpnngmDu;
      string wxXbhYhUIY;
      string zfDHylkbGo;
      string BnjOcyrrNQ;
      string JrjSDtQOjs;
      string nykPNhRWrB;
      string CFfOsHNJzj;
      string fpHrOGwkEE;
      string VWqMADDTAt;
      if(IjVgeCrzPa == qnpSSWStnN){fVzLOELVZu = true;}
      else if(qnpSSWStnN == IjVgeCrzPa){RyuytQtdfw = true;}
      if(VyTuJBfmkj == OVdpnngmDu){fGOAMyqsAH = true;}
      else if(OVdpnngmDu == VyTuJBfmkj){dsuNKUYwGu = true;}
      if(XYwkBPlPmA == wxXbhYhUIY){lgSnffNSNo = true;}
      else if(wxXbhYhUIY == XYwkBPlPmA){OfLrtddUVJ = true;}
      if(KqcTbHGOQV == zfDHylkbGo){EsJFDKpwcK = true;}
      else if(zfDHylkbGo == KqcTbHGOQV){rtpfzZaUQL = true;}
      if(TrDddMnKUN == BnjOcyrrNQ){taKIXOHqAC = true;}
      else if(BnjOcyrrNQ == TrDddMnKUN){AtkBZOiCjz = true;}
      if(noIErjnkfP == JrjSDtQOjs){MJTrHzDLei = true;}
      else if(JrjSDtQOjs == noIErjnkfP){cWTXVllCEQ = true;}
      if(QbMPPeUzTC == nykPNhRWrB){prHjpmxJwB = true;}
      else if(nykPNhRWrB == QbMPPeUzTC){mYIVDiCOOk = true;}
      if(uRVOQeURGo == CFfOsHNJzj){HuPoMLVJQQ = true;}
      if(abtYLUhXbq == fpHrOGwkEE){XVSLctYQxD = true;}
      if(TViBFqfnNz == VWqMADDTAt){HdQtTCTaSj = true;}
      while(CFfOsHNJzj == uRVOQeURGo){sEfttTuJSf = true;}
      while(fpHrOGwkEE == fpHrOGwkEE){tbkWgUZSKM = true;}
      while(VWqMADDTAt == VWqMADDTAt){mXQzYalOxp = true;}
      if(fVzLOELVZu == true){fVzLOELVZu = false;}
      if(fGOAMyqsAH == true){fGOAMyqsAH = false;}
      if(lgSnffNSNo == true){lgSnffNSNo = false;}
      if(EsJFDKpwcK == true){EsJFDKpwcK = false;}
      if(taKIXOHqAC == true){taKIXOHqAC = false;}
      if(MJTrHzDLei == true){MJTrHzDLei = false;}
      if(prHjpmxJwB == true){prHjpmxJwB = false;}
      if(HuPoMLVJQQ == true){HuPoMLVJQQ = false;}
      if(XVSLctYQxD == true){XVSLctYQxD = false;}
      if(HdQtTCTaSj == true){HdQtTCTaSj = false;}
      if(RyuytQtdfw == true){RyuytQtdfw = false;}
      if(dsuNKUYwGu == true){dsuNKUYwGu = false;}
      if(OfLrtddUVJ == true){OfLrtddUVJ = false;}
      if(rtpfzZaUQL == true){rtpfzZaUQL = false;}
      if(AtkBZOiCjz == true){AtkBZOiCjz = false;}
      if(cWTXVllCEQ == true){cWTXVllCEQ = false;}
      if(mYIVDiCOOk == true){mYIVDiCOOk = false;}
      if(sEfttTuJSf == true){sEfttTuJSf = false;}
      if(tbkWgUZSKM == true){tbkWgUZSKM = false;}
      if(mXQzYalOxp == true){mXQzYalOxp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHCCOSWQFS
{ 
  void CklhJXWOjC()
  { 
      bool MQdEUuUcOG = false;
      bool plOQWVwJPf = false;
      bool ZXMewjciYo = false;
      bool aDMVrHHbrQ = false;
      bool bMKfScHWmL = false;
      bool KFhLDoDyIj = false;
      bool SkDZfmYsXO = false;
      bool NTQzDNNgLS = false;
      bool bFuNdVVBRD = false;
      bool DITHyqJjzf = false;
      bool ENzXyqohHp = false;
      bool bWmoIMoouK = false;
      bool RXbULEzIBM = false;
      bool DcgeONFXPm = false;
      bool fmsabgVezk = false;
      bool BTooOfleMs = false;
      bool qffumyoHZt = false;
      bool HRZIdddAre = false;
      bool iTIQKjnrQi = false;
      bool baKWuAHync = false;
      string MSpmzQMAEI;
      string kdtyJdQAPP;
      string YWJzhMdqMN;
      string ROePXBpJUH;
      string HBUhsQritX;
      string PGSGKpIpEl;
      string mVnqqVzdaI;
      string nGfIIXBaGR;
      string UtwnxKuXFh;
      string rzEhTkNcqW;
      string ROIliJaKyl;
      string ngimRrZztf;
      string aaXsPnCxnW;
      string KXjizFlJFn;
      string jkZSsKQQQa;
      string LNiKwqpOVt;
      string GcVbbPxzmL;
      string GQsGwoBEzF;
      string XkgMLwoYmI;
      string PWmKgGOyqd;
      if(MSpmzQMAEI == ROIliJaKyl){MQdEUuUcOG = true;}
      else if(ROIliJaKyl == MSpmzQMAEI){ENzXyqohHp = true;}
      if(kdtyJdQAPP == ngimRrZztf){plOQWVwJPf = true;}
      else if(ngimRrZztf == kdtyJdQAPP){bWmoIMoouK = true;}
      if(YWJzhMdqMN == aaXsPnCxnW){ZXMewjciYo = true;}
      else if(aaXsPnCxnW == YWJzhMdqMN){RXbULEzIBM = true;}
      if(ROePXBpJUH == KXjizFlJFn){aDMVrHHbrQ = true;}
      else if(KXjizFlJFn == ROePXBpJUH){DcgeONFXPm = true;}
      if(HBUhsQritX == jkZSsKQQQa){bMKfScHWmL = true;}
      else if(jkZSsKQQQa == HBUhsQritX){fmsabgVezk = true;}
      if(PGSGKpIpEl == LNiKwqpOVt){KFhLDoDyIj = true;}
      else if(LNiKwqpOVt == PGSGKpIpEl){BTooOfleMs = true;}
      if(mVnqqVzdaI == GcVbbPxzmL){SkDZfmYsXO = true;}
      else if(GcVbbPxzmL == mVnqqVzdaI){qffumyoHZt = true;}
      if(nGfIIXBaGR == GQsGwoBEzF){NTQzDNNgLS = true;}
      if(UtwnxKuXFh == XkgMLwoYmI){bFuNdVVBRD = true;}
      if(rzEhTkNcqW == PWmKgGOyqd){DITHyqJjzf = true;}
      while(GQsGwoBEzF == nGfIIXBaGR){HRZIdddAre = true;}
      while(XkgMLwoYmI == XkgMLwoYmI){iTIQKjnrQi = true;}
      while(PWmKgGOyqd == PWmKgGOyqd){baKWuAHync = true;}
      if(MQdEUuUcOG == true){MQdEUuUcOG = false;}
      if(plOQWVwJPf == true){plOQWVwJPf = false;}
      if(ZXMewjciYo == true){ZXMewjciYo = false;}
      if(aDMVrHHbrQ == true){aDMVrHHbrQ = false;}
      if(bMKfScHWmL == true){bMKfScHWmL = false;}
      if(KFhLDoDyIj == true){KFhLDoDyIj = false;}
      if(SkDZfmYsXO == true){SkDZfmYsXO = false;}
      if(NTQzDNNgLS == true){NTQzDNNgLS = false;}
      if(bFuNdVVBRD == true){bFuNdVVBRD = false;}
      if(DITHyqJjzf == true){DITHyqJjzf = false;}
      if(ENzXyqohHp == true){ENzXyqohHp = false;}
      if(bWmoIMoouK == true){bWmoIMoouK = false;}
      if(RXbULEzIBM == true){RXbULEzIBM = false;}
      if(DcgeONFXPm == true){DcgeONFXPm = false;}
      if(fmsabgVezk == true){fmsabgVezk = false;}
      if(BTooOfleMs == true){BTooOfleMs = false;}
      if(qffumyoHZt == true){qffumyoHZt = false;}
      if(HRZIdddAre == true){HRZIdddAre = false;}
      if(iTIQKjnrQi == true){iTIQKjnrQi = false;}
      if(baKWuAHync == true){baKWuAHync = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JKDJHGIDPC
{ 
  void DkVZqNuuNU()
  { 
      bool RXGVKqtGtj = false;
      bool CGbuImQPAT = false;
      bool yHdPkEUijg = false;
      bool PqgKtLizuD = false;
      bool gPmQYeWHwX = false;
      bool ALCiAJtpjG = false;
      bool WKWNTKZQAx = false;
      bool DRUwliTMqF = false;
      bool hMmLfEoyKj = false;
      bool RsOofVsYxO = false;
      bool FFHzTiqFwQ = false;
      bool ogzdYKXKgP = false;
      bool VbGPeKCfPQ = false;
      bool otPbAbEmrx = false;
      bool MiBstjsjPV = false;
      bool yirgsdyqTI = false;
      bool fKpfatQXdw = false;
      bool GkRjCmZMVt = false;
      bool RRPtRGCiiW = false;
      bool cNSjQBsVRz = false;
      string kOlzQsVXVR;
      string WcWFFFDGFY;
      string QjZlPMGCGe;
      string LtYlONJyym;
      string QlbCsxKHRb;
      string WIIQiBoziD;
      string lSQqFbDkqq;
      string wEISIeIXsS;
      string CzkdHDlICM;
      string XJPtAxUkwQ;
      string sYPZfSzoHE;
      string rQGQBmhmiC;
      string ouhdSmoNSL;
      string JXbbYcjKyo;
      string DxAyUGCysN;
      string PhBsbxqkHs;
      string dkVwuUodqX;
      string CXntyrujJL;
      string jpUFuaVhAb;
      string lyDFKRbDCz;
      if(kOlzQsVXVR == sYPZfSzoHE){RXGVKqtGtj = true;}
      else if(sYPZfSzoHE == kOlzQsVXVR){FFHzTiqFwQ = true;}
      if(WcWFFFDGFY == rQGQBmhmiC){CGbuImQPAT = true;}
      else if(rQGQBmhmiC == WcWFFFDGFY){ogzdYKXKgP = true;}
      if(QjZlPMGCGe == ouhdSmoNSL){yHdPkEUijg = true;}
      else if(ouhdSmoNSL == QjZlPMGCGe){VbGPeKCfPQ = true;}
      if(LtYlONJyym == JXbbYcjKyo){PqgKtLizuD = true;}
      else if(JXbbYcjKyo == LtYlONJyym){otPbAbEmrx = true;}
      if(QlbCsxKHRb == DxAyUGCysN){gPmQYeWHwX = true;}
      else if(DxAyUGCysN == QlbCsxKHRb){MiBstjsjPV = true;}
      if(WIIQiBoziD == PhBsbxqkHs){ALCiAJtpjG = true;}
      else if(PhBsbxqkHs == WIIQiBoziD){yirgsdyqTI = true;}
      if(lSQqFbDkqq == dkVwuUodqX){WKWNTKZQAx = true;}
      else if(dkVwuUodqX == lSQqFbDkqq){fKpfatQXdw = true;}
      if(wEISIeIXsS == CXntyrujJL){DRUwliTMqF = true;}
      if(CzkdHDlICM == jpUFuaVhAb){hMmLfEoyKj = true;}
      if(XJPtAxUkwQ == lyDFKRbDCz){RsOofVsYxO = true;}
      while(CXntyrujJL == wEISIeIXsS){GkRjCmZMVt = true;}
      while(jpUFuaVhAb == jpUFuaVhAb){RRPtRGCiiW = true;}
      while(lyDFKRbDCz == lyDFKRbDCz){cNSjQBsVRz = true;}
      if(RXGVKqtGtj == true){RXGVKqtGtj = false;}
      if(CGbuImQPAT == true){CGbuImQPAT = false;}
      if(yHdPkEUijg == true){yHdPkEUijg = false;}
      if(PqgKtLizuD == true){PqgKtLizuD = false;}
      if(gPmQYeWHwX == true){gPmQYeWHwX = false;}
      if(ALCiAJtpjG == true){ALCiAJtpjG = false;}
      if(WKWNTKZQAx == true){WKWNTKZQAx = false;}
      if(DRUwliTMqF == true){DRUwliTMqF = false;}
      if(hMmLfEoyKj == true){hMmLfEoyKj = false;}
      if(RsOofVsYxO == true){RsOofVsYxO = false;}
      if(FFHzTiqFwQ == true){FFHzTiqFwQ = false;}
      if(ogzdYKXKgP == true){ogzdYKXKgP = false;}
      if(VbGPeKCfPQ == true){VbGPeKCfPQ = false;}
      if(otPbAbEmrx == true){otPbAbEmrx = false;}
      if(MiBstjsjPV == true){MiBstjsjPV = false;}
      if(yirgsdyqTI == true){yirgsdyqTI = false;}
      if(fKpfatQXdw == true){fKpfatQXdw = false;}
      if(GkRjCmZMVt == true){GkRjCmZMVt = false;}
      if(RRPtRGCiiW == true){RRPtRGCiiW = false;}
      if(cNSjQBsVRz == true){cNSjQBsVRz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBMFVZATYT
{ 
  void lQPHDUsxeM()
  { 
      bool fVEgdAUqbM = false;
      bool VlVjddPwFL = false;
      bool gPOJDPOqXn = false;
      bool AdKmSusgXm = false;
      bool yUIygbNLee = false;
      bool PxfaSPGtdN = false;
      bool ldTmMrahQi = false;
      bool jiXSMLHQcb = false;
      bool CCLsYCyiTD = false;
      bool oyDJBUBVlo = false;
      bool AetwtfYNNG = false;
      bool HoRCLiSZNJ = false;
      bool sqNNslfOQr = false;
      bool KlenaXHOzs = false;
      bool dkUNuzgAyR = false;
      bool BaIcuIQgCH = false;
      bool AKwVwVKcbn = false;
      bool aDaUeIWARt = false;
      bool EeQypidBrR = false;
      bool GaMqsSnzQZ = false;
      string LESDaOdwtM;
      string JeaptykSzZ;
      string LFQNaHlybD;
      string dBLWgBuylx;
      string dueJBCFBGM;
      string caemjFnFcT;
      string bfUpiHTDJr;
      string DlgBwPZHLY;
      string BjrOZDVXma;
      string NoVRVyanas;
      string iBrNJqsdqT;
      string fgsDRqnFPe;
      string lwQheNPOfx;
      string okfSpzrdFi;
      string KrfStfwRAd;
      string JUXwHlkJhu;
      string aeysetAaNS;
      string zJAfTtPyny;
      string RxOCnTMjLD;
      string OiuJIeslmA;
      if(LESDaOdwtM == iBrNJqsdqT){fVEgdAUqbM = true;}
      else if(iBrNJqsdqT == LESDaOdwtM){AetwtfYNNG = true;}
      if(JeaptykSzZ == fgsDRqnFPe){VlVjddPwFL = true;}
      else if(fgsDRqnFPe == JeaptykSzZ){HoRCLiSZNJ = true;}
      if(LFQNaHlybD == lwQheNPOfx){gPOJDPOqXn = true;}
      else if(lwQheNPOfx == LFQNaHlybD){sqNNslfOQr = true;}
      if(dBLWgBuylx == okfSpzrdFi){AdKmSusgXm = true;}
      else if(okfSpzrdFi == dBLWgBuylx){KlenaXHOzs = true;}
      if(dueJBCFBGM == KrfStfwRAd){yUIygbNLee = true;}
      else if(KrfStfwRAd == dueJBCFBGM){dkUNuzgAyR = true;}
      if(caemjFnFcT == JUXwHlkJhu){PxfaSPGtdN = true;}
      else if(JUXwHlkJhu == caemjFnFcT){BaIcuIQgCH = true;}
      if(bfUpiHTDJr == aeysetAaNS){ldTmMrahQi = true;}
      else if(aeysetAaNS == bfUpiHTDJr){AKwVwVKcbn = true;}
      if(DlgBwPZHLY == zJAfTtPyny){jiXSMLHQcb = true;}
      if(BjrOZDVXma == RxOCnTMjLD){CCLsYCyiTD = true;}
      if(NoVRVyanas == OiuJIeslmA){oyDJBUBVlo = true;}
      while(zJAfTtPyny == DlgBwPZHLY){aDaUeIWARt = true;}
      while(RxOCnTMjLD == RxOCnTMjLD){EeQypidBrR = true;}
      while(OiuJIeslmA == OiuJIeslmA){GaMqsSnzQZ = true;}
      if(fVEgdAUqbM == true){fVEgdAUqbM = false;}
      if(VlVjddPwFL == true){VlVjddPwFL = false;}
      if(gPOJDPOqXn == true){gPOJDPOqXn = false;}
      if(AdKmSusgXm == true){AdKmSusgXm = false;}
      if(yUIygbNLee == true){yUIygbNLee = false;}
      if(PxfaSPGtdN == true){PxfaSPGtdN = false;}
      if(ldTmMrahQi == true){ldTmMrahQi = false;}
      if(jiXSMLHQcb == true){jiXSMLHQcb = false;}
      if(CCLsYCyiTD == true){CCLsYCyiTD = false;}
      if(oyDJBUBVlo == true){oyDJBUBVlo = false;}
      if(AetwtfYNNG == true){AetwtfYNNG = false;}
      if(HoRCLiSZNJ == true){HoRCLiSZNJ = false;}
      if(sqNNslfOQr == true){sqNNslfOQr = false;}
      if(KlenaXHOzs == true){KlenaXHOzs = false;}
      if(dkUNuzgAyR == true){dkUNuzgAyR = false;}
      if(BaIcuIQgCH == true){BaIcuIQgCH = false;}
      if(AKwVwVKcbn == true){AKwVwVKcbn = false;}
      if(aDaUeIWARt == true){aDaUeIWARt = false;}
      if(EeQypidBrR == true){EeQypidBrR = false;}
      if(GaMqsSnzQZ == true){GaMqsSnzQZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GJJZBEDVLG
{ 
  void sVmUIpBQdQ()
  { 
      bool LfmuFzJlrF = false;
      bool kUALBPwaPQ = false;
      bool YtVuDmiRxb = false;
      bool foGLPMJBDG = false;
      bool XJBClHNAUH = false;
      bool wGEIFQJqrS = false;
      bool QqoQYuOnuo = false;
      bool GuWJrPsTIw = false;
      bool ZhxoeZkxFy = false;
      bool CRJjpfTjdp = false;
      bool sYFfBBitPp = false;
      bool XphwshtAlz = false;
      bool JQiwlnllSM = false;
      bool wJoSCAcRmd = false;
      bool pphPaMiMqH = false;
      bool lSyefcoItM = false;
      bool OwbDtOAPsr = false;
      bool EbMHITiTUY = false;
      bool EYuKZcKKlZ = false;
      bool LTXZOtOdUM = false;
      string dixWcbzqQz;
      string kmRhoMkqag;
      string BmKSWlktaK;
      string lpZNRStqdA;
      string rSUhsJGziO;
      string JgYLMqXdzp;
      string pEQGNuNDQV;
      string StNZniRcYN;
      string flLLAFQNBZ;
      string uPqmKnCNUy;
      string uChMwPTzWd;
      string YuFkKEsEGH;
      string eACqaCCZPA;
      string fDHaScEyPk;
      string lRpWAzKFcF;
      string tyHNSuApls;
      string MsjVyUndSg;
      string AunUUNJepa;
      string rwxJGhwsHX;
      string cNLVXsgTYe;
      if(dixWcbzqQz == uChMwPTzWd){LfmuFzJlrF = true;}
      else if(uChMwPTzWd == dixWcbzqQz){sYFfBBitPp = true;}
      if(kmRhoMkqag == YuFkKEsEGH){kUALBPwaPQ = true;}
      else if(YuFkKEsEGH == kmRhoMkqag){XphwshtAlz = true;}
      if(BmKSWlktaK == eACqaCCZPA){YtVuDmiRxb = true;}
      else if(eACqaCCZPA == BmKSWlktaK){JQiwlnllSM = true;}
      if(lpZNRStqdA == fDHaScEyPk){foGLPMJBDG = true;}
      else if(fDHaScEyPk == lpZNRStqdA){wJoSCAcRmd = true;}
      if(rSUhsJGziO == lRpWAzKFcF){XJBClHNAUH = true;}
      else if(lRpWAzKFcF == rSUhsJGziO){pphPaMiMqH = true;}
      if(JgYLMqXdzp == tyHNSuApls){wGEIFQJqrS = true;}
      else if(tyHNSuApls == JgYLMqXdzp){lSyefcoItM = true;}
      if(pEQGNuNDQV == MsjVyUndSg){QqoQYuOnuo = true;}
      else if(MsjVyUndSg == pEQGNuNDQV){OwbDtOAPsr = true;}
      if(StNZniRcYN == AunUUNJepa){GuWJrPsTIw = true;}
      if(flLLAFQNBZ == rwxJGhwsHX){ZhxoeZkxFy = true;}
      if(uPqmKnCNUy == cNLVXsgTYe){CRJjpfTjdp = true;}
      while(AunUUNJepa == StNZniRcYN){EbMHITiTUY = true;}
      while(rwxJGhwsHX == rwxJGhwsHX){EYuKZcKKlZ = true;}
      while(cNLVXsgTYe == cNLVXsgTYe){LTXZOtOdUM = true;}
      if(LfmuFzJlrF == true){LfmuFzJlrF = false;}
      if(kUALBPwaPQ == true){kUALBPwaPQ = false;}
      if(YtVuDmiRxb == true){YtVuDmiRxb = false;}
      if(foGLPMJBDG == true){foGLPMJBDG = false;}
      if(XJBClHNAUH == true){XJBClHNAUH = false;}
      if(wGEIFQJqrS == true){wGEIFQJqrS = false;}
      if(QqoQYuOnuo == true){QqoQYuOnuo = false;}
      if(GuWJrPsTIw == true){GuWJrPsTIw = false;}
      if(ZhxoeZkxFy == true){ZhxoeZkxFy = false;}
      if(CRJjpfTjdp == true){CRJjpfTjdp = false;}
      if(sYFfBBitPp == true){sYFfBBitPp = false;}
      if(XphwshtAlz == true){XphwshtAlz = false;}
      if(JQiwlnllSM == true){JQiwlnllSM = false;}
      if(wJoSCAcRmd == true){wJoSCAcRmd = false;}
      if(pphPaMiMqH == true){pphPaMiMqH = false;}
      if(lSyefcoItM == true){lSyefcoItM = false;}
      if(OwbDtOAPsr == true){OwbDtOAPsr = false;}
      if(EbMHITiTUY == true){EbMHITiTUY = false;}
      if(EYuKZcKKlZ == true){EYuKZcKKlZ = false;}
      if(LTXZOtOdUM == true){LTXZOtOdUM = false;}
    } 
}; 
