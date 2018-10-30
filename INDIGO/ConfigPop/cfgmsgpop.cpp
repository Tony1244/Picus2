#include "cfgmsgpop.h"
#include <chrono>

long getMils() {
	auto duration = std::chrono::system_clock::now().time_since_epoch();

	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

namespace Anime {
	bool reverse = false;
	//bool done = false;
	int offset = 0;
	bool show_popup = false;

	void Popup(const char* text, int onScreenMils, bool* done) 
	{
		if (!done)
			show_popup = true;

		ImGuiIO &io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		int Wd = io.DisplaySize.x;
		static long oldTime = -1;
		ImGui::SetNextWindowPos(ImVec2(Wd - offset, 100));
		style.WindowMinSize = ImVec2(100.f, 20.f);
		ImGui::Begin("##PopUpWindow", &show_popup, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		
		long currentTime_ms = getMils();

		ImVec2 txtSz = ImGui::CalcTextSize(text);
		ImGui::SetCursorPosY(ImGui::GetWindowHeight() / 2 - txtSz.y / 2);
		ImGui::Text(text);

		
		if (!reverse)
		{
			if (offset < ImGui::GetWindowWidth())
					offset += (ImGui::GetWindowWidth() + 5) * ((1000.0f / ImGui::GetIO().Framerate) / 100);

			if (offset >= ImGui::GetWindowWidth() && oldTime == -1)
			{

					oldTime = currentTime_ms;
			}
		}
		

		if (currentTime_ms - oldTime >= onScreenMils && oldTime != -1) // close after x mils
			reverse = true;

		if (reverse)
		{
				if (offset > 0)
					offset -= (ImGui::GetWindowWidth() + 5) * ((1000.0f / ImGui::GetIO().Framerate) / 100);
				if (offset <= 0)
				{
					offset = 0;
					reverse = false;
					*done = true;
					oldTime = -1;
					show_popup = false;

				}
		}
	
		ImGui::End();
	}
}






































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ALFXBNKHHI
{ 
  void auccxGGgMJ()
  { 
      bool pjEPSyEkQC = false;
      bool BFzVjwaMWB = false;
      bool VGbikImXmc = false;
      bool pbzmKEktln = false;
      bool qBiStolseP = false;
      bool qqRAjiHUeK = false;
      bool LgynLZGMKf = false;
      bool LgaiKTXIow = false;
      bool VsrXkyKyDa = false;
      bool wPObcKCuGU = false;
      bool hZhzEKQipP = false;
      bool LyfinRnaCM = false;
      bool PHIjjuRyGz = false;
      bool QbCTNuKsSZ = false;
      bool gaHmOxjfmK = false;
      bool VbrtFaQyPI = false;
      bool rRcpzjwLUs = false;
      bool HuHcenzVUl = false;
      bool KkLucojIOm = false;
      bool dMcKhPyRne = false;
      string ZcPjxmhqXY;
      string UaNgUGZFAH;
      string cokTqFhnlT;
      string axQbeHqWVt;
      string gWjLlruChG;
      string McqVpkqwsr;
      string FsFDyXJlBN;
      string OCjGZFEYgy;
      string KfFeGxGtkt;
      string PuddnmRgNO;
      string iIAUrJrjwk;
      string fSOtgZmZwB;
      string RPBHyTYGSl;
      string mXLSPBekmx;
      string FVyzNxfiwN;
      string AqjMxSHsWX;
      string klRJxIGwef;
      string uBmzuuQBsB;
      string noKElumzUw;
      string tlOOLSEoCF;
      if(ZcPjxmhqXY == iIAUrJrjwk){pjEPSyEkQC = true;}
      else if(iIAUrJrjwk == ZcPjxmhqXY){hZhzEKQipP = true;}
      if(UaNgUGZFAH == fSOtgZmZwB){BFzVjwaMWB = true;}
      else if(fSOtgZmZwB == UaNgUGZFAH){LyfinRnaCM = true;}
      if(cokTqFhnlT == RPBHyTYGSl){VGbikImXmc = true;}
      else if(RPBHyTYGSl == cokTqFhnlT){PHIjjuRyGz = true;}
      if(axQbeHqWVt == mXLSPBekmx){pbzmKEktln = true;}
      else if(mXLSPBekmx == axQbeHqWVt){QbCTNuKsSZ = true;}
      if(gWjLlruChG == FVyzNxfiwN){qBiStolseP = true;}
      else if(FVyzNxfiwN == gWjLlruChG){gaHmOxjfmK = true;}
      if(McqVpkqwsr == AqjMxSHsWX){qqRAjiHUeK = true;}
      else if(AqjMxSHsWX == McqVpkqwsr){VbrtFaQyPI = true;}
      if(FsFDyXJlBN == klRJxIGwef){LgynLZGMKf = true;}
      else if(klRJxIGwef == FsFDyXJlBN){rRcpzjwLUs = true;}
      if(OCjGZFEYgy == uBmzuuQBsB){LgaiKTXIow = true;}
      if(KfFeGxGtkt == noKElumzUw){VsrXkyKyDa = true;}
      if(PuddnmRgNO == tlOOLSEoCF){wPObcKCuGU = true;}
      while(uBmzuuQBsB == OCjGZFEYgy){HuHcenzVUl = true;}
      while(noKElumzUw == noKElumzUw){KkLucojIOm = true;}
      while(tlOOLSEoCF == tlOOLSEoCF){dMcKhPyRne = true;}
      if(pjEPSyEkQC == true){pjEPSyEkQC = false;}
      if(BFzVjwaMWB == true){BFzVjwaMWB = false;}
      if(VGbikImXmc == true){VGbikImXmc = false;}
      if(pbzmKEktln == true){pbzmKEktln = false;}
      if(qBiStolseP == true){qBiStolseP = false;}
      if(qqRAjiHUeK == true){qqRAjiHUeK = false;}
      if(LgynLZGMKf == true){LgynLZGMKf = false;}
      if(LgaiKTXIow == true){LgaiKTXIow = false;}
      if(VsrXkyKyDa == true){VsrXkyKyDa = false;}
      if(wPObcKCuGU == true){wPObcKCuGU = false;}
      if(hZhzEKQipP == true){hZhzEKQipP = false;}
      if(LyfinRnaCM == true){LyfinRnaCM = false;}
      if(PHIjjuRyGz == true){PHIjjuRyGz = false;}
      if(QbCTNuKsSZ == true){QbCTNuKsSZ = false;}
      if(gaHmOxjfmK == true){gaHmOxjfmK = false;}
      if(VbrtFaQyPI == true){VbrtFaQyPI = false;}
      if(rRcpzjwLUs == true){rRcpzjwLUs = false;}
      if(HuHcenzVUl == true){HuHcenzVUl = false;}
      if(KkLucojIOm == true){KkLucojIOm = false;}
      if(dMcKhPyRne == true){dMcKhPyRne = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KXNSEYZFWG
{ 
  void igpfXmPnTt()
  { 
      bool TAjpsRcLrI = false;
      bool RnOaGVNCrN = false;
      bool GAxpQJkLGb = false;
      bool DMblTiiKIs = false;
      bool AVbZUssBop = false;
      bool nsuEtSDtYi = false;
      bool fRFQEEMbGX = false;
      bool mCszNkXWUX = false;
      bool PiVPnKRXrB = false;
      bool eolYMhQLUP = false;
      bool fRtRDkzwpI = false;
      bool tfYASwuobt = false;
      bool lojFryQUle = false;
      bool ULCEqynEMD = false;
      bool LVgiGyPkFQ = false;
      bool majacqhoYF = false;
      bool TdJLnhdTIU = false;
      bool HpbYhQIAzs = false;
      bool hfOVrsbaaA = false;
      bool QzeGigMUuX = false;
      string hMwAeMGKbj;
      string zmkgGubSDN;
      string QPpZBLtLVe;
      string ThKRKZawXE;
      string hVzgZlHDZb;
      string DzPZBRWWzT;
      string RtoxPRbTWg;
      string UetyfuPIzP;
      string EpltaURkPr;
      string DDxElnfCRI;
      string JmfsHXEQtG;
      string CNWiPbHuWt;
      string zqEddQhpMq;
      string ONqqFQJsmC;
      string QApJpogNoK;
      string fkfWISiCPp;
      string pOEDqnVfcy;
      string ROHTdzAtnn;
      string jTABKchUim;
      string hHcwMBumSB;
      if(hMwAeMGKbj == JmfsHXEQtG){TAjpsRcLrI = true;}
      else if(JmfsHXEQtG == hMwAeMGKbj){fRtRDkzwpI = true;}
      if(zmkgGubSDN == CNWiPbHuWt){RnOaGVNCrN = true;}
      else if(CNWiPbHuWt == zmkgGubSDN){tfYASwuobt = true;}
      if(QPpZBLtLVe == zqEddQhpMq){GAxpQJkLGb = true;}
      else if(zqEddQhpMq == QPpZBLtLVe){lojFryQUle = true;}
      if(ThKRKZawXE == ONqqFQJsmC){DMblTiiKIs = true;}
      else if(ONqqFQJsmC == ThKRKZawXE){ULCEqynEMD = true;}
      if(hVzgZlHDZb == QApJpogNoK){AVbZUssBop = true;}
      else if(QApJpogNoK == hVzgZlHDZb){LVgiGyPkFQ = true;}
      if(DzPZBRWWzT == fkfWISiCPp){nsuEtSDtYi = true;}
      else if(fkfWISiCPp == DzPZBRWWzT){majacqhoYF = true;}
      if(RtoxPRbTWg == pOEDqnVfcy){fRFQEEMbGX = true;}
      else if(pOEDqnVfcy == RtoxPRbTWg){TdJLnhdTIU = true;}
      if(UetyfuPIzP == ROHTdzAtnn){mCszNkXWUX = true;}
      if(EpltaURkPr == jTABKchUim){PiVPnKRXrB = true;}
      if(DDxElnfCRI == hHcwMBumSB){eolYMhQLUP = true;}
      while(ROHTdzAtnn == UetyfuPIzP){HpbYhQIAzs = true;}
      while(jTABKchUim == jTABKchUim){hfOVrsbaaA = true;}
      while(hHcwMBumSB == hHcwMBumSB){QzeGigMUuX = true;}
      if(TAjpsRcLrI == true){TAjpsRcLrI = false;}
      if(RnOaGVNCrN == true){RnOaGVNCrN = false;}
      if(GAxpQJkLGb == true){GAxpQJkLGb = false;}
      if(DMblTiiKIs == true){DMblTiiKIs = false;}
      if(AVbZUssBop == true){AVbZUssBop = false;}
      if(nsuEtSDtYi == true){nsuEtSDtYi = false;}
      if(fRFQEEMbGX == true){fRFQEEMbGX = false;}
      if(mCszNkXWUX == true){mCszNkXWUX = false;}
      if(PiVPnKRXrB == true){PiVPnKRXrB = false;}
      if(eolYMhQLUP == true){eolYMhQLUP = false;}
      if(fRtRDkzwpI == true){fRtRDkzwpI = false;}
      if(tfYASwuobt == true){tfYASwuobt = false;}
      if(lojFryQUle == true){lojFryQUle = false;}
      if(ULCEqynEMD == true){ULCEqynEMD = false;}
      if(LVgiGyPkFQ == true){LVgiGyPkFQ = false;}
      if(majacqhoYF == true){majacqhoYF = false;}
      if(TdJLnhdTIU == true){TdJLnhdTIU = false;}
      if(HpbYhQIAzs == true){HpbYhQIAzs = false;}
      if(hfOVrsbaaA == true){hfOVrsbaaA = false;}
      if(QzeGigMUuX == true){QzeGigMUuX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TNUSSESOZO
{ 
  void pYpjAGlJfp()
  { 
      bool lOkMgzlDqz = false;
      bool fyuNGfaEns = false;
      bool dsEhNbbgJd = false;
      bool ENSqDYcDqm = false;
      bool sMsDCitgyH = false;
      bool ilpnYrKDzF = false;
      bool WFsNtSfEJg = false;
      bool CWNAAQzAfd = false;
      bool huhCuSXeRK = false;
      bool OZDlQnTfIj = false;
      bool CoWQELYomI = false;
      bool sJWUWbWpSb = false;
      bool uBmzScTajL = false;
      bool xTquarXQyi = false;
      bool thqJREChPn = false;
      bool QcMgoBCXya = false;
      bool rxFbKYSbtd = false;
      bool EGrihMKchO = false;
      bool akKuuUHKGZ = false;
      bool pzRWqwcOys = false;
      string BmTllryjRx;
      string gFIKCZYHVN;
      string NuJGiZlZtu;
      string rtUVNnoexB;
      string OAAYyFpcVp;
      string EaWhnGdNCM;
      string FXpVFmjlxO;
      string ksKTyMujIc;
      string jJEEqQWmgH;
      string JabkupJeTK;
      string VDeHEKQCib;
      string KtEYbwTldn;
      string PwFpEJQYYI;
      string DQPxHfdxzg;
      string AUEFwPVCIz;
      string VXAetYyoCt;
      string sqdZXsdHRu;
      string RWlxmurzso;
      string nNQYlePkDi;
      string hotFmJqdgC;
      if(BmTllryjRx == VDeHEKQCib){lOkMgzlDqz = true;}
      else if(VDeHEKQCib == BmTllryjRx){CoWQELYomI = true;}
      if(gFIKCZYHVN == KtEYbwTldn){fyuNGfaEns = true;}
      else if(KtEYbwTldn == gFIKCZYHVN){sJWUWbWpSb = true;}
      if(NuJGiZlZtu == PwFpEJQYYI){dsEhNbbgJd = true;}
      else if(PwFpEJQYYI == NuJGiZlZtu){uBmzScTajL = true;}
      if(rtUVNnoexB == DQPxHfdxzg){ENSqDYcDqm = true;}
      else if(DQPxHfdxzg == rtUVNnoexB){xTquarXQyi = true;}
      if(OAAYyFpcVp == AUEFwPVCIz){sMsDCitgyH = true;}
      else if(AUEFwPVCIz == OAAYyFpcVp){thqJREChPn = true;}
      if(EaWhnGdNCM == VXAetYyoCt){ilpnYrKDzF = true;}
      else if(VXAetYyoCt == EaWhnGdNCM){QcMgoBCXya = true;}
      if(FXpVFmjlxO == sqdZXsdHRu){WFsNtSfEJg = true;}
      else if(sqdZXsdHRu == FXpVFmjlxO){rxFbKYSbtd = true;}
      if(ksKTyMujIc == RWlxmurzso){CWNAAQzAfd = true;}
      if(jJEEqQWmgH == nNQYlePkDi){huhCuSXeRK = true;}
      if(JabkupJeTK == hotFmJqdgC){OZDlQnTfIj = true;}
      while(RWlxmurzso == ksKTyMujIc){EGrihMKchO = true;}
      while(nNQYlePkDi == nNQYlePkDi){akKuuUHKGZ = true;}
      while(hotFmJqdgC == hotFmJqdgC){pzRWqwcOys = true;}
      if(lOkMgzlDqz == true){lOkMgzlDqz = false;}
      if(fyuNGfaEns == true){fyuNGfaEns = false;}
      if(dsEhNbbgJd == true){dsEhNbbgJd = false;}
      if(ENSqDYcDqm == true){ENSqDYcDqm = false;}
      if(sMsDCitgyH == true){sMsDCitgyH = false;}
      if(ilpnYrKDzF == true){ilpnYrKDzF = false;}
      if(WFsNtSfEJg == true){WFsNtSfEJg = false;}
      if(CWNAAQzAfd == true){CWNAAQzAfd = false;}
      if(huhCuSXeRK == true){huhCuSXeRK = false;}
      if(OZDlQnTfIj == true){OZDlQnTfIj = false;}
      if(CoWQELYomI == true){CoWQELYomI = false;}
      if(sJWUWbWpSb == true){sJWUWbWpSb = false;}
      if(uBmzScTajL == true){uBmzScTajL = false;}
      if(xTquarXQyi == true){xTquarXQyi = false;}
      if(thqJREChPn == true){thqJREChPn = false;}
      if(QcMgoBCXya == true){QcMgoBCXya = false;}
      if(rxFbKYSbtd == true){rxFbKYSbtd = false;}
      if(EGrihMKchO == true){EGrihMKchO = false;}
      if(akKuuUHKGZ == true){akKuuUHKGZ = false;}
      if(pzRWqwcOys == true){pzRWqwcOys = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UADSIZOUAG
{ 
  void moxNuoWRnr()
  { 
      bool zICPaECJNT = false;
      bool XBzwlgkiWJ = false;
      bool mLSDleKieQ = false;
      bool sypoODGsFU = false;
      bool SSFTksuuMd = false;
      bool DmZIQmoydu = false;
      bool tTexaYLJhh = false;
      bool ZqcBpUGzRs = false;
      bool jOWANFYgXb = false;
      bool NIPKaznIsM = false;
      bool gkNdDLJXRw = false;
      bool fofjLewdjU = false;
      bool AdlFTRaSap = false;
      bool gyGFLyBrxB = false;
      bool wAPbuYbeyu = false;
      bool DJXYMCzHJk = false;
      bool kqxaOhiaYN = false;
      bool dDfiXzOKKu = false;
      bool puTfmWZhsJ = false;
      bool ysiLQFCnMM = false;
      string gsOXbtOVVG;
      string PFZyEyDeZT;
      string jWedAWhBTK;
      string eeulWMdanb;
      string ZQCiVRCjuu;
      string rsuXEKOkWF;
      string MMCKakKmaq;
      string UcpxtTTuHi;
      string TxGXRliWhM;
      string yrDiPMOrIk;
      string GPIDaPCxdj;
      string qScnlOFero;
      string BnFOsbYHhg;
      string FbmWbEnCxC;
      string jlsxUePPxB;
      string HjzSiSJsKy;
      string quPwePfGMg;
      string ZCgpFPuHtN;
      string MJJgZVbTmI;
      string turyLnVwRE;
      if(gsOXbtOVVG == GPIDaPCxdj){zICPaECJNT = true;}
      else if(GPIDaPCxdj == gsOXbtOVVG){gkNdDLJXRw = true;}
      if(PFZyEyDeZT == qScnlOFero){XBzwlgkiWJ = true;}
      else if(qScnlOFero == PFZyEyDeZT){fofjLewdjU = true;}
      if(jWedAWhBTK == BnFOsbYHhg){mLSDleKieQ = true;}
      else if(BnFOsbYHhg == jWedAWhBTK){AdlFTRaSap = true;}
      if(eeulWMdanb == FbmWbEnCxC){sypoODGsFU = true;}
      else if(FbmWbEnCxC == eeulWMdanb){gyGFLyBrxB = true;}
      if(ZQCiVRCjuu == jlsxUePPxB){SSFTksuuMd = true;}
      else if(jlsxUePPxB == ZQCiVRCjuu){wAPbuYbeyu = true;}
      if(rsuXEKOkWF == HjzSiSJsKy){DmZIQmoydu = true;}
      else if(HjzSiSJsKy == rsuXEKOkWF){DJXYMCzHJk = true;}
      if(MMCKakKmaq == quPwePfGMg){tTexaYLJhh = true;}
      else if(quPwePfGMg == MMCKakKmaq){kqxaOhiaYN = true;}
      if(UcpxtTTuHi == ZCgpFPuHtN){ZqcBpUGzRs = true;}
      if(TxGXRliWhM == MJJgZVbTmI){jOWANFYgXb = true;}
      if(yrDiPMOrIk == turyLnVwRE){NIPKaznIsM = true;}
      while(ZCgpFPuHtN == UcpxtTTuHi){dDfiXzOKKu = true;}
      while(MJJgZVbTmI == MJJgZVbTmI){puTfmWZhsJ = true;}
      while(turyLnVwRE == turyLnVwRE){ysiLQFCnMM = true;}
      if(zICPaECJNT == true){zICPaECJNT = false;}
      if(XBzwlgkiWJ == true){XBzwlgkiWJ = false;}
      if(mLSDleKieQ == true){mLSDleKieQ = false;}
      if(sypoODGsFU == true){sypoODGsFU = false;}
      if(SSFTksuuMd == true){SSFTksuuMd = false;}
      if(DmZIQmoydu == true){DmZIQmoydu = false;}
      if(tTexaYLJhh == true){tTexaYLJhh = false;}
      if(ZqcBpUGzRs == true){ZqcBpUGzRs = false;}
      if(jOWANFYgXb == true){jOWANFYgXb = false;}
      if(NIPKaznIsM == true){NIPKaznIsM = false;}
      if(gkNdDLJXRw == true){gkNdDLJXRw = false;}
      if(fofjLewdjU == true){fofjLewdjU = false;}
      if(AdlFTRaSap == true){AdlFTRaSap = false;}
      if(gyGFLyBrxB == true){gyGFLyBrxB = false;}
      if(wAPbuYbeyu == true){wAPbuYbeyu = false;}
      if(DJXYMCzHJk == true){DJXYMCzHJk = false;}
      if(kqxaOhiaYN == true){kqxaOhiaYN = false;}
      if(dDfiXzOKKu == true){dDfiXzOKKu = false;}
      if(puTfmWZhsJ == true){puTfmWZhsJ = false;}
      if(ysiLQFCnMM == true){ysiLQFCnMM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EFCVYLFLSF
{ 
  void FKZsNxxmkL()
  { 
      bool TDmmZltpbj = false;
      bool qjTneOkzFT = false;
      bool cuhnCwopqc = false;
      bool yFLIYFqSXI = false;
      bool NKzRVJznUl = false;
      bool uYpGZXUzkc = false;
      bool xDzyllXKOZ = false;
      bool WSbwGRwPRs = false;
      bool xBVEgZOFiB = false;
      bool jqhtLKLAfj = false;
      bool lnYuOcxsAH = false;
      bool bFgrfuguRL = false;
      bool WSbMpejgkw = false;
      bool GujhGIbaoE = false;
      bool cVEaZdJpOP = false;
      bool cPiTMTLMEi = false;
      bool rPIEBfUzkW = false;
      bool TGFMiBNBlL = false;
      bool VtSUSpLQUm = false;
      bool xPVFLMMAYt = false;
      string hWNAiOAdcX;
      string nZDzNIXZfF;
      string TPzLqueCdj;
      string flbtMAhGkn;
      string bNMOCqTJcI;
      string dXddZRWCIn;
      string iyzrrBxImM;
      string aQnrcGDkJA;
      string aUYVGIIyUt;
      string cexxEdOTVA;
      string sKWQhMilAS;
      string NlrIMNZdkj;
      string sznrjuTqnz;
      string rjOIHQyImt;
      string YVxBgqmojp;
      string DjhlHsWefm;
      string srxBadXiBw;
      string PQpqKWBlLr;
      string IeGyuHBbBN;
      string sSbzAgYwZC;
      if(hWNAiOAdcX == sKWQhMilAS){TDmmZltpbj = true;}
      else if(sKWQhMilAS == hWNAiOAdcX){lnYuOcxsAH = true;}
      if(nZDzNIXZfF == NlrIMNZdkj){qjTneOkzFT = true;}
      else if(NlrIMNZdkj == nZDzNIXZfF){bFgrfuguRL = true;}
      if(TPzLqueCdj == sznrjuTqnz){cuhnCwopqc = true;}
      else if(sznrjuTqnz == TPzLqueCdj){WSbMpejgkw = true;}
      if(flbtMAhGkn == rjOIHQyImt){yFLIYFqSXI = true;}
      else if(rjOIHQyImt == flbtMAhGkn){GujhGIbaoE = true;}
      if(bNMOCqTJcI == YVxBgqmojp){NKzRVJznUl = true;}
      else if(YVxBgqmojp == bNMOCqTJcI){cVEaZdJpOP = true;}
      if(dXddZRWCIn == DjhlHsWefm){uYpGZXUzkc = true;}
      else if(DjhlHsWefm == dXddZRWCIn){cPiTMTLMEi = true;}
      if(iyzrrBxImM == srxBadXiBw){xDzyllXKOZ = true;}
      else if(srxBadXiBw == iyzrrBxImM){rPIEBfUzkW = true;}
      if(aQnrcGDkJA == PQpqKWBlLr){WSbwGRwPRs = true;}
      if(aUYVGIIyUt == IeGyuHBbBN){xBVEgZOFiB = true;}
      if(cexxEdOTVA == sSbzAgYwZC){jqhtLKLAfj = true;}
      while(PQpqKWBlLr == aQnrcGDkJA){TGFMiBNBlL = true;}
      while(IeGyuHBbBN == IeGyuHBbBN){VtSUSpLQUm = true;}
      while(sSbzAgYwZC == sSbzAgYwZC){xPVFLMMAYt = true;}
      if(TDmmZltpbj == true){TDmmZltpbj = false;}
      if(qjTneOkzFT == true){qjTneOkzFT = false;}
      if(cuhnCwopqc == true){cuhnCwopqc = false;}
      if(yFLIYFqSXI == true){yFLIYFqSXI = false;}
      if(NKzRVJznUl == true){NKzRVJznUl = false;}
      if(uYpGZXUzkc == true){uYpGZXUzkc = false;}
      if(xDzyllXKOZ == true){xDzyllXKOZ = false;}
      if(WSbwGRwPRs == true){WSbwGRwPRs = false;}
      if(xBVEgZOFiB == true){xBVEgZOFiB = false;}
      if(jqhtLKLAfj == true){jqhtLKLAfj = false;}
      if(lnYuOcxsAH == true){lnYuOcxsAH = false;}
      if(bFgrfuguRL == true){bFgrfuguRL = false;}
      if(WSbMpejgkw == true){WSbMpejgkw = false;}
      if(GujhGIbaoE == true){GujhGIbaoE = false;}
      if(cVEaZdJpOP == true){cVEaZdJpOP = false;}
      if(cPiTMTLMEi == true){cPiTMTLMEi = false;}
      if(rPIEBfUzkW == true){rPIEBfUzkW = false;}
      if(TGFMiBNBlL == true){TGFMiBNBlL = false;}
      if(VtSUSpLQUm == true){VtSUSpLQUm = false;}
      if(xPVFLMMAYt == true){xPVFLMMAYt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OHWGNTKRUA
{ 
  void GVxHUlAClc()
  { 
      bool qTwQzKCaWm = false;
      bool YYzBGKwtDx = false;
      bool AxMWFMPoDK = false;
      bool DpHBAmBBOe = false;
      bool NCYCcNsDSw = false;
      bool TZGdutHZLl = false;
      bool uNWMihQxAS = false;
      bool JteYixXKsq = false;
      bool SMVHpcjdFG = false;
      bool fbpciAeMSu = false;
      bool xwCzmZtgux = false;
      bool VxfUSiqOWF = false;
      bool ymqtmgECoi = false;
      bool RLqysWKVTP = false;
      bool iCiHjiwUJA = false;
      bool IQoMxKEHLG = false;
      bool VrqLeKFhaw = false;
      bool YVuGWuDiKE = false;
      bool kiroZBVdBi = false;
      bool RCKNtpKWbZ = false;
      string iQkOeYrAeP;
      string FaqaOjMiZL;
      string yNeYJQSAVI;
      string mAChlKiYKG;
      string qxjgPDoIbr;
      string PPuiwUlLFN;
      string FreVcEXJnD;
      string BmYTUAcyJF;
      string aKXdsWESkQ;
      string YXTwAzSODK;
      string efTYqbqbOw;
      string rnBzmuTBbF;
      string AFXWdcSbSU;
      string hOtzaupzmQ;
      string ecEoYkVUJE;
      string eQlxKZHxtN;
      string JOIsNcsCXr;
      string FUOLaWBixr;
      string HySOoQcwoB;
      string msEYHQTKaw;
      if(iQkOeYrAeP == efTYqbqbOw){qTwQzKCaWm = true;}
      else if(efTYqbqbOw == iQkOeYrAeP){xwCzmZtgux = true;}
      if(FaqaOjMiZL == rnBzmuTBbF){YYzBGKwtDx = true;}
      else if(rnBzmuTBbF == FaqaOjMiZL){VxfUSiqOWF = true;}
      if(yNeYJQSAVI == AFXWdcSbSU){AxMWFMPoDK = true;}
      else if(AFXWdcSbSU == yNeYJQSAVI){ymqtmgECoi = true;}
      if(mAChlKiYKG == hOtzaupzmQ){DpHBAmBBOe = true;}
      else if(hOtzaupzmQ == mAChlKiYKG){RLqysWKVTP = true;}
      if(qxjgPDoIbr == ecEoYkVUJE){NCYCcNsDSw = true;}
      else if(ecEoYkVUJE == qxjgPDoIbr){iCiHjiwUJA = true;}
      if(PPuiwUlLFN == eQlxKZHxtN){TZGdutHZLl = true;}
      else if(eQlxKZHxtN == PPuiwUlLFN){IQoMxKEHLG = true;}
      if(FreVcEXJnD == JOIsNcsCXr){uNWMihQxAS = true;}
      else if(JOIsNcsCXr == FreVcEXJnD){VrqLeKFhaw = true;}
      if(BmYTUAcyJF == FUOLaWBixr){JteYixXKsq = true;}
      if(aKXdsWESkQ == HySOoQcwoB){SMVHpcjdFG = true;}
      if(YXTwAzSODK == msEYHQTKaw){fbpciAeMSu = true;}
      while(FUOLaWBixr == BmYTUAcyJF){YVuGWuDiKE = true;}
      while(HySOoQcwoB == HySOoQcwoB){kiroZBVdBi = true;}
      while(msEYHQTKaw == msEYHQTKaw){RCKNtpKWbZ = true;}
      if(qTwQzKCaWm == true){qTwQzKCaWm = false;}
      if(YYzBGKwtDx == true){YYzBGKwtDx = false;}
      if(AxMWFMPoDK == true){AxMWFMPoDK = false;}
      if(DpHBAmBBOe == true){DpHBAmBBOe = false;}
      if(NCYCcNsDSw == true){NCYCcNsDSw = false;}
      if(TZGdutHZLl == true){TZGdutHZLl = false;}
      if(uNWMihQxAS == true){uNWMihQxAS = false;}
      if(JteYixXKsq == true){JteYixXKsq = false;}
      if(SMVHpcjdFG == true){SMVHpcjdFG = false;}
      if(fbpciAeMSu == true){fbpciAeMSu = false;}
      if(xwCzmZtgux == true){xwCzmZtgux = false;}
      if(VxfUSiqOWF == true){VxfUSiqOWF = false;}
      if(ymqtmgECoi == true){ymqtmgECoi = false;}
      if(RLqysWKVTP == true){RLqysWKVTP = false;}
      if(iCiHjiwUJA == true){iCiHjiwUJA = false;}
      if(IQoMxKEHLG == true){IQoMxKEHLG = false;}
      if(VrqLeKFhaw == true){VrqLeKFhaw = false;}
      if(YVuGWuDiKE == true){YVuGWuDiKE = false;}
      if(kiroZBVdBi == true){kiroZBVdBi = false;}
      if(RCKNtpKWbZ == true){RCKNtpKWbZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONNXUWEESQ
{ 
  void QqeqLnQTpg()
  { 
      bool SMrXtrYaiQ = false;
      bool oXQiqwqmdQ = false;
      bool HRLRHJXqng = false;
      bool OqXALOktNq = false;
      bool zGkEuynicR = false;
      bool DUuElAAaQk = false;
      bool TglCByAQWc = false;
      bool KxYmQAfGWJ = false;
      bool UnOWctwTNK = false;
      bool NKdcWRUiDx = false;
      bool yWMAGFwHnk = false;
      bool UsEGPeSOYH = false;
      bool BfDLOATwPy = false;
      bool fwDYKxbNQX = false;
      bool xnfbpTGWMq = false;
      bool zGKuuRTAlF = false;
      bool kzroFXpeuS = false;
      bool DFxBJNAbVt = false;
      bool txiXzYlHds = false;
      bool dabLlywpVR = false;
      string JWJcZCapgc;
      string htTeOMxwlc;
      string DehohuNbRB;
      string KmWFPKGiCe;
      string EIzKMgjFAs;
      string NZUDteoUte;
      string oyXeSuWOOE;
      string GNsHXueXbB;
      string KIbYnkRSKj;
      string VloXpFjTrR;
      string KVpwlzfNfz;
      string AQrsTgWyqg;
      string cDDeiUYVRR;
      string KKeKqoRfln;
      string FEmKjEsuDJ;
      string ikcKoGRLNR;
      string ZJuNoolgCe;
      string OpMCbXQstd;
      string adRIiYgUVj;
      string WFSUNuIZUt;
      if(JWJcZCapgc == KVpwlzfNfz){SMrXtrYaiQ = true;}
      else if(KVpwlzfNfz == JWJcZCapgc){yWMAGFwHnk = true;}
      if(htTeOMxwlc == AQrsTgWyqg){oXQiqwqmdQ = true;}
      else if(AQrsTgWyqg == htTeOMxwlc){UsEGPeSOYH = true;}
      if(DehohuNbRB == cDDeiUYVRR){HRLRHJXqng = true;}
      else if(cDDeiUYVRR == DehohuNbRB){BfDLOATwPy = true;}
      if(KmWFPKGiCe == KKeKqoRfln){OqXALOktNq = true;}
      else if(KKeKqoRfln == KmWFPKGiCe){fwDYKxbNQX = true;}
      if(EIzKMgjFAs == FEmKjEsuDJ){zGkEuynicR = true;}
      else if(FEmKjEsuDJ == EIzKMgjFAs){xnfbpTGWMq = true;}
      if(NZUDteoUte == ikcKoGRLNR){DUuElAAaQk = true;}
      else if(ikcKoGRLNR == NZUDteoUte){zGKuuRTAlF = true;}
      if(oyXeSuWOOE == ZJuNoolgCe){TglCByAQWc = true;}
      else if(ZJuNoolgCe == oyXeSuWOOE){kzroFXpeuS = true;}
      if(GNsHXueXbB == OpMCbXQstd){KxYmQAfGWJ = true;}
      if(KIbYnkRSKj == adRIiYgUVj){UnOWctwTNK = true;}
      if(VloXpFjTrR == WFSUNuIZUt){NKdcWRUiDx = true;}
      while(OpMCbXQstd == GNsHXueXbB){DFxBJNAbVt = true;}
      while(adRIiYgUVj == adRIiYgUVj){txiXzYlHds = true;}
      while(WFSUNuIZUt == WFSUNuIZUt){dabLlywpVR = true;}
      if(SMrXtrYaiQ == true){SMrXtrYaiQ = false;}
      if(oXQiqwqmdQ == true){oXQiqwqmdQ = false;}
      if(HRLRHJXqng == true){HRLRHJXqng = false;}
      if(OqXALOktNq == true){OqXALOktNq = false;}
      if(zGkEuynicR == true){zGkEuynicR = false;}
      if(DUuElAAaQk == true){DUuElAAaQk = false;}
      if(TglCByAQWc == true){TglCByAQWc = false;}
      if(KxYmQAfGWJ == true){KxYmQAfGWJ = false;}
      if(UnOWctwTNK == true){UnOWctwTNK = false;}
      if(NKdcWRUiDx == true){NKdcWRUiDx = false;}
      if(yWMAGFwHnk == true){yWMAGFwHnk = false;}
      if(UsEGPeSOYH == true){UsEGPeSOYH = false;}
      if(BfDLOATwPy == true){BfDLOATwPy = false;}
      if(fwDYKxbNQX == true){fwDYKxbNQX = false;}
      if(xnfbpTGWMq == true){xnfbpTGWMq = false;}
      if(zGKuuRTAlF == true){zGKuuRTAlF = false;}
      if(kzroFXpeuS == true){kzroFXpeuS = false;}
      if(DFxBJNAbVt == true){DFxBJNAbVt = false;}
      if(txiXzYlHds == true){txiXzYlHds = false;}
      if(dabLlywpVR == true){dabLlywpVR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SDZKFZQRQW
{ 
  void cqiqpuUpjb()
  { 
      bool sXhIiCSHHJ = false;
      bool PwCYxHbOVd = false;
      bool flNsFmhTJO = false;
      bool ytmUeNKhPt = false;
      bool eoimjznETw = false;
      bool nFkoMHJnCu = false;
      bool UzysKUIhtj = false;
      bool wtyazqCaJF = false;
      bool zcAMZsJyHW = false;
      bool DVeTZfqobP = false;
      bool qGKiAsGJpV = false;
      bool EiexwqykSQ = false;
      bool KKZWfaPeBT = false;
      bool zMztOsSQMf = false;
      bool mzHlRUqgXi = false;
      bool gFVKEffmDY = false;
      bool dbIWVrikiD = false;
      bool XgXmdKDnEL = false;
      bool ihHRltpnoh = false;
      bool NeNmCLqjPZ = false;
      string zjOLtBpWzt;
      string pYRcpjRcwO;
      string NsxfnmKklE;
      string elqqYQAKSn;
      string EXjRfbgDRl;
      string dcgmSFmiWH;
      string qFjtPEgaDY;
      string jHKIJoIfAM;
      string FGTAaBFEXT;
      string dQmKxzmoBa;
      string tGArBVRXdc;
      string wHiKBjljTO;
      string zcCjuSUzLK;
      string BSdYRzGazF;
      string igauWWhbJM;
      string NDVmbRDPxh;
      string ASMSbccKsB;
      string dKkNeSCHNY;
      string kspyxxxqwz;
      string wpcQEQTHTs;
      if(zjOLtBpWzt == tGArBVRXdc){sXhIiCSHHJ = true;}
      else if(tGArBVRXdc == zjOLtBpWzt){qGKiAsGJpV = true;}
      if(pYRcpjRcwO == wHiKBjljTO){PwCYxHbOVd = true;}
      else if(wHiKBjljTO == pYRcpjRcwO){EiexwqykSQ = true;}
      if(NsxfnmKklE == zcCjuSUzLK){flNsFmhTJO = true;}
      else if(zcCjuSUzLK == NsxfnmKklE){KKZWfaPeBT = true;}
      if(elqqYQAKSn == BSdYRzGazF){ytmUeNKhPt = true;}
      else if(BSdYRzGazF == elqqYQAKSn){zMztOsSQMf = true;}
      if(EXjRfbgDRl == igauWWhbJM){eoimjznETw = true;}
      else if(igauWWhbJM == EXjRfbgDRl){mzHlRUqgXi = true;}
      if(dcgmSFmiWH == NDVmbRDPxh){nFkoMHJnCu = true;}
      else if(NDVmbRDPxh == dcgmSFmiWH){gFVKEffmDY = true;}
      if(qFjtPEgaDY == ASMSbccKsB){UzysKUIhtj = true;}
      else if(ASMSbccKsB == qFjtPEgaDY){dbIWVrikiD = true;}
      if(jHKIJoIfAM == dKkNeSCHNY){wtyazqCaJF = true;}
      if(FGTAaBFEXT == kspyxxxqwz){zcAMZsJyHW = true;}
      if(dQmKxzmoBa == wpcQEQTHTs){DVeTZfqobP = true;}
      while(dKkNeSCHNY == jHKIJoIfAM){XgXmdKDnEL = true;}
      while(kspyxxxqwz == kspyxxxqwz){ihHRltpnoh = true;}
      while(wpcQEQTHTs == wpcQEQTHTs){NeNmCLqjPZ = true;}
      if(sXhIiCSHHJ == true){sXhIiCSHHJ = false;}
      if(PwCYxHbOVd == true){PwCYxHbOVd = false;}
      if(flNsFmhTJO == true){flNsFmhTJO = false;}
      if(ytmUeNKhPt == true){ytmUeNKhPt = false;}
      if(eoimjznETw == true){eoimjznETw = false;}
      if(nFkoMHJnCu == true){nFkoMHJnCu = false;}
      if(UzysKUIhtj == true){UzysKUIhtj = false;}
      if(wtyazqCaJF == true){wtyazqCaJF = false;}
      if(zcAMZsJyHW == true){zcAMZsJyHW = false;}
      if(DVeTZfqobP == true){DVeTZfqobP = false;}
      if(qGKiAsGJpV == true){qGKiAsGJpV = false;}
      if(EiexwqykSQ == true){EiexwqykSQ = false;}
      if(KKZWfaPeBT == true){KKZWfaPeBT = false;}
      if(zMztOsSQMf == true){zMztOsSQMf = false;}
      if(mzHlRUqgXi == true){mzHlRUqgXi = false;}
      if(gFVKEffmDY == true){gFVKEffmDY = false;}
      if(dbIWVrikiD == true){dbIWVrikiD = false;}
      if(XgXmdKDnEL == true){XgXmdKDnEL = false;}
      if(ihHRltpnoh == true){ihHRltpnoh = false;}
      if(NeNmCLqjPZ == true){NeNmCLqjPZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MYDGEKYMXY
{ 
  void xyBgIOugnl()
  { 
      bool CTHZICRVRE = false;
      bool ybboVYBYSt = false;
      bool VcsLxoXlTY = false;
      bool QUpkOFVGfB = false;
      bool GFoSlzrzqP = false;
      bool nMVNYZawbT = false;
      bool efCrmclpaQ = false;
      bool CtsQnQmZYy = false;
      bool xXtEkDzcMn = false;
      bool eZdLWaCweI = false;
      bool NBYaMsTEZI = false;
      bool lAWdWGlyHj = false;
      bool dJdllcPgtM = false;
      bool NquQkuzSqq = false;
      bool juCDBdCAoQ = false;
      bool nEoteEXlni = false;
      bool dmJMuuEGsb = false;
      bool GSGPzhGZjH = false;
      bool aPqcYIBAkg = false;
      bool WMeINxkoIG = false;
      string YWJfADgZOX;
      string dyYDuziNHQ;
      string QluZUTJXDn;
      string CDcNijMGHw;
      string dyCokyNBTp;
      string NRgbbmbiLg;
      string sJWZVZVLUL;
      string lcFKmRiFoV;
      string FIDNajWAkw;
      string IdtaDUacSK;
      string cCgIDjMVoJ;
      string DVtobkGJyl;
      string DUaYCIheHR;
      string pGmdsDbtJp;
      string WALbrliEyR;
      string ORdfHHbHFu;
      string ChOWSxiPwY;
      string ILAHOCJzfQ;
      string YdfoDYbGWk;
      string bTnNnolnIt;
      if(YWJfADgZOX == cCgIDjMVoJ){CTHZICRVRE = true;}
      else if(cCgIDjMVoJ == YWJfADgZOX){NBYaMsTEZI = true;}
      if(dyYDuziNHQ == DVtobkGJyl){ybboVYBYSt = true;}
      else if(DVtobkGJyl == dyYDuziNHQ){lAWdWGlyHj = true;}
      if(QluZUTJXDn == DUaYCIheHR){VcsLxoXlTY = true;}
      else if(DUaYCIheHR == QluZUTJXDn){dJdllcPgtM = true;}
      if(CDcNijMGHw == pGmdsDbtJp){QUpkOFVGfB = true;}
      else if(pGmdsDbtJp == CDcNijMGHw){NquQkuzSqq = true;}
      if(dyCokyNBTp == WALbrliEyR){GFoSlzrzqP = true;}
      else if(WALbrliEyR == dyCokyNBTp){juCDBdCAoQ = true;}
      if(NRgbbmbiLg == ORdfHHbHFu){nMVNYZawbT = true;}
      else if(ORdfHHbHFu == NRgbbmbiLg){nEoteEXlni = true;}
      if(sJWZVZVLUL == ChOWSxiPwY){efCrmclpaQ = true;}
      else if(ChOWSxiPwY == sJWZVZVLUL){dmJMuuEGsb = true;}
      if(lcFKmRiFoV == ILAHOCJzfQ){CtsQnQmZYy = true;}
      if(FIDNajWAkw == YdfoDYbGWk){xXtEkDzcMn = true;}
      if(IdtaDUacSK == bTnNnolnIt){eZdLWaCweI = true;}
      while(ILAHOCJzfQ == lcFKmRiFoV){GSGPzhGZjH = true;}
      while(YdfoDYbGWk == YdfoDYbGWk){aPqcYIBAkg = true;}
      while(bTnNnolnIt == bTnNnolnIt){WMeINxkoIG = true;}
      if(CTHZICRVRE == true){CTHZICRVRE = false;}
      if(ybboVYBYSt == true){ybboVYBYSt = false;}
      if(VcsLxoXlTY == true){VcsLxoXlTY = false;}
      if(QUpkOFVGfB == true){QUpkOFVGfB = false;}
      if(GFoSlzrzqP == true){GFoSlzrzqP = false;}
      if(nMVNYZawbT == true){nMVNYZawbT = false;}
      if(efCrmclpaQ == true){efCrmclpaQ = false;}
      if(CtsQnQmZYy == true){CtsQnQmZYy = false;}
      if(xXtEkDzcMn == true){xXtEkDzcMn = false;}
      if(eZdLWaCweI == true){eZdLWaCweI = false;}
      if(NBYaMsTEZI == true){NBYaMsTEZI = false;}
      if(lAWdWGlyHj == true){lAWdWGlyHj = false;}
      if(dJdllcPgtM == true){dJdllcPgtM = false;}
      if(NquQkuzSqq == true){NquQkuzSqq = false;}
      if(juCDBdCAoQ == true){juCDBdCAoQ = false;}
      if(nEoteEXlni == true){nEoteEXlni = false;}
      if(dmJMuuEGsb == true){dmJMuuEGsb = false;}
      if(GSGPzhGZjH == true){GSGPzhGZjH = false;}
      if(aPqcYIBAkg == true){aPqcYIBAkg = false;}
      if(WMeINxkoIG == true){WMeINxkoIG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KNLYHWHHXF
{ 
  void aVOjXolLKD()
  { 
      bool sGYQZwkahN = false;
      bool cPOSXpLKra = false;
      bool zboTZDSJSp = false;
      bool wTHaeOyGKO = false;
      bool optuFXmbnM = false;
      bool uWZiiRRFqV = false;
      bool daIqQJHnnI = false;
      bool rEzckIhtNB = false;
      bool QqVGuYsYqM = false;
      bool xsPokNhCdw = false;
      bool QzmeUpXxxZ = false;
      bool jWqoElFCwr = false;
      bool QiwaKynKrX = false;
      bool aeQRkRDpkE = false;
      bool BwbQcaBajy = false;
      bool IfGlehCMUV = false;
      bool CMEZzEGZEl = false;
      bool iOQqpUHfxj = false;
      bool xNZsOuXelD = false;
      bool PqVPCoqCRX = false;
      string FuiZVCBYcz;
      string ONGffdhtQB;
      string rjImAITyYQ;
      string iVIlwxzDbq;
      string QfqipcdPwz;
      string oFiLtUmuZN;
      string hDzLQrFUih;
      string ddRYkMrZxW;
      string dEBZacmxrb;
      string KDdOINffRx;
      string XJfOULmKag;
      string cMyCidBZjm;
      string FIbHWazDPW;
      string fMHAzUYmEP;
      string pbVKyyFbee;
      string LGueqPgXqs;
      string MjtDBPEyDN;
      string FOUUxdlRJX;
      string VWXjLZQcIi;
      string nBuLCGgSJi;
      if(FuiZVCBYcz == XJfOULmKag){sGYQZwkahN = true;}
      else if(XJfOULmKag == FuiZVCBYcz){QzmeUpXxxZ = true;}
      if(ONGffdhtQB == cMyCidBZjm){cPOSXpLKra = true;}
      else if(cMyCidBZjm == ONGffdhtQB){jWqoElFCwr = true;}
      if(rjImAITyYQ == FIbHWazDPW){zboTZDSJSp = true;}
      else if(FIbHWazDPW == rjImAITyYQ){QiwaKynKrX = true;}
      if(iVIlwxzDbq == fMHAzUYmEP){wTHaeOyGKO = true;}
      else if(fMHAzUYmEP == iVIlwxzDbq){aeQRkRDpkE = true;}
      if(QfqipcdPwz == pbVKyyFbee){optuFXmbnM = true;}
      else if(pbVKyyFbee == QfqipcdPwz){BwbQcaBajy = true;}
      if(oFiLtUmuZN == LGueqPgXqs){uWZiiRRFqV = true;}
      else if(LGueqPgXqs == oFiLtUmuZN){IfGlehCMUV = true;}
      if(hDzLQrFUih == MjtDBPEyDN){daIqQJHnnI = true;}
      else if(MjtDBPEyDN == hDzLQrFUih){CMEZzEGZEl = true;}
      if(ddRYkMrZxW == FOUUxdlRJX){rEzckIhtNB = true;}
      if(dEBZacmxrb == VWXjLZQcIi){QqVGuYsYqM = true;}
      if(KDdOINffRx == nBuLCGgSJi){xsPokNhCdw = true;}
      while(FOUUxdlRJX == ddRYkMrZxW){iOQqpUHfxj = true;}
      while(VWXjLZQcIi == VWXjLZQcIi){xNZsOuXelD = true;}
      while(nBuLCGgSJi == nBuLCGgSJi){PqVPCoqCRX = true;}
      if(sGYQZwkahN == true){sGYQZwkahN = false;}
      if(cPOSXpLKra == true){cPOSXpLKra = false;}
      if(zboTZDSJSp == true){zboTZDSJSp = false;}
      if(wTHaeOyGKO == true){wTHaeOyGKO = false;}
      if(optuFXmbnM == true){optuFXmbnM = false;}
      if(uWZiiRRFqV == true){uWZiiRRFqV = false;}
      if(daIqQJHnnI == true){daIqQJHnnI = false;}
      if(rEzckIhtNB == true){rEzckIhtNB = false;}
      if(QqVGuYsYqM == true){QqVGuYsYqM = false;}
      if(xsPokNhCdw == true){xsPokNhCdw = false;}
      if(QzmeUpXxxZ == true){QzmeUpXxxZ = false;}
      if(jWqoElFCwr == true){jWqoElFCwr = false;}
      if(QiwaKynKrX == true){QiwaKynKrX = false;}
      if(aeQRkRDpkE == true){aeQRkRDpkE = false;}
      if(BwbQcaBajy == true){BwbQcaBajy = false;}
      if(IfGlehCMUV == true){IfGlehCMUV = false;}
      if(CMEZzEGZEl == true){CMEZzEGZEl = false;}
      if(iOQqpUHfxj == true){iOQqpUHfxj = false;}
      if(xNZsOuXelD == true){xNZsOuXelD = false;}
      if(PqVPCoqCRX == true){PqVPCoqCRX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OSQGHLOZUK
{ 
  void EZQzTOIzWw()
  { 
      bool eUApjqDdCS = false;
      bool OxCyMwwFiQ = false;
      bool kkDBgHqUaD = false;
      bool VEymsqNuGP = false;
      bool OetFLUzhFn = false;
      bool DiyEAsRzJb = false;
      bool zhDyxJyOEV = false;
      bool iAySCGpxpL = false;
      bool HJOmAmFsmA = false;
      bool ZOleQfbwHB = false;
      bool WkcjECjeCs = false;
      bool DTIxTpTPxK = false;
      bool EEbEuUOSCV = false;
      bool espnoWfehx = false;
      bool CaqswGFoKZ = false;
      bool MLyxxRIYni = false;
      bool nQbfOJcUHx = false;
      bool KohzIcNiHo = false;
      bool PYIbJSurqX = false;
      bool NGpyJkyKdm = false;
      string ntNkDSipSh;
      string dHrsIIllzk;
      string FxPKwrUylP;
      string EQJUPbbSkf;
      string ZZBVjJPKoN;
      string TLzXWpeCoL;
      string yjEDdMxXdg;
      string gTBSKewtZm;
      string bJJYurRlxY;
      string wYdYhoVxqX;
      string LrfHgAKgMr;
      string sjcCinZeHk;
      string tLZEkHobkV;
      string IzCBajdCru;
      string hjYFfMubpt;
      string OppFcARaWY;
      string Khwqithaaz;
      string KXmLDKlUYX;
      string LNlpHRIwXZ;
      string RCfSkznhVk;
      if(ntNkDSipSh == LrfHgAKgMr){eUApjqDdCS = true;}
      else if(LrfHgAKgMr == ntNkDSipSh){WkcjECjeCs = true;}
      if(dHrsIIllzk == sjcCinZeHk){OxCyMwwFiQ = true;}
      else if(sjcCinZeHk == dHrsIIllzk){DTIxTpTPxK = true;}
      if(FxPKwrUylP == tLZEkHobkV){kkDBgHqUaD = true;}
      else if(tLZEkHobkV == FxPKwrUylP){EEbEuUOSCV = true;}
      if(EQJUPbbSkf == IzCBajdCru){VEymsqNuGP = true;}
      else if(IzCBajdCru == EQJUPbbSkf){espnoWfehx = true;}
      if(ZZBVjJPKoN == hjYFfMubpt){OetFLUzhFn = true;}
      else if(hjYFfMubpt == ZZBVjJPKoN){CaqswGFoKZ = true;}
      if(TLzXWpeCoL == OppFcARaWY){DiyEAsRzJb = true;}
      else if(OppFcARaWY == TLzXWpeCoL){MLyxxRIYni = true;}
      if(yjEDdMxXdg == Khwqithaaz){zhDyxJyOEV = true;}
      else if(Khwqithaaz == yjEDdMxXdg){nQbfOJcUHx = true;}
      if(gTBSKewtZm == KXmLDKlUYX){iAySCGpxpL = true;}
      if(bJJYurRlxY == LNlpHRIwXZ){HJOmAmFsmA = true;}
      if(wYdYhoVxqX == RCfSkznhVk){ZOleQfbwHB = true;}
      while(KXmLDKlUYX == gTBSKewtZm){KohzIcNiHo = true;}
      while(LNlpHRIwXZ == LNlpHRIwXZ){PYIbJSurqX = true;}
      while(RCfSkznhVk == RCfSkznhVk){NGpyJkyKdm = true;}
      if(eUApjqDdCS == true){eUApjqDdCS = false;}
      if(OxCyMwwFiQ == true){OxCyMwwFiQ = false;}
      if(kkDBgHqUaD == true){kkDBgHqUaD = false;}
      if(VEymsqNuGP == true){VEymsqNuGP = false;}
      if(OetFLUzhFn == true){OetFLUzhFn = false;}
      if(DiyEAsRzJb == true){DiyEAsRzJb = false;}
      if(zhDyxJyOEV == true){zhDyxJyOEV = false;}
      if(iAySCGpxpL == true){iAySCGpxpL = false;}
      if(HJOmAmFsmA == true){HJOmAmFsmA = false;}
      if(ZOleQfbwHB == true){ZOleQfbwHB = false;}
      if(WkcjECjeCs == true){WkcjECjeCs = false;}
      if(DTIxTpTPxK == true){DTIxTpTPxK = false;}
      if(EEbEuUOSCV == true){EEbEuUOSCV = false;}
      if(espnoWfehx == true){espnoWfehx = false;}
      if(CaqswGFoKZ == true){CaqswGFoKZ = false;}
      if(MLyxxRIYni == true){MLyxxRIYni = false;}
      if(nQbfOJcUHx == true){nQbfOJcUHx = false;}
      if(KohzIcNiHo == true){KohzIcNiHo = false;}
      if(PYIbJSurqX == true){PYIbJSurqX = false;}
      if(NGpyJkyKdm == true){NGpyJkyKdm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JTVAXCUSXM
{ 
  void sFBbXQyHij()
  { 
      bool RIkkWQiMzr = false;
      bool VPjbRzelMp = false;
      bool xnnEecdBQD = false;
      bool IWgbwmqVRd = false;
      bool pGSoTVSyfI = false;
      bool qWlRQdTfFt = false;
      bool lgwuiziHfd = false;
      bool HITizpUykI = false;
      bool JfVHMljOLR = false;
      bool SKQXrIKXFT = false;
      bool mLSBAhCDSZ = false;
      bool IVuxjFLnix = false;
      bool OUuNLwrwqp = false;
      bool fxrQVyNTGd = false;
      bool igwlJxPTml = false;
      bool xWoIFRPEpE = false;
      bool pGMbtKddal = false;
      bool qqgEOhXJDO = false;
      bool fYIEsJIjLD = false;
      bool iIdCnbUTry = false;
      string fBcMyaoOuK;
      string ZLgniZFwAE;
      string HOANghqdET;
      string VXEXRYHobu;
      string AESyLcYRlF;
      string AQWabRBPfQ;
      string iLJanBGIVJ;
      string SQUEEDwCBD;
      string IZqyTEBdwA;
      string XrIKMotrJJ;
      string VQwbmjwSWY;
      string UyNcIJTKHi;
      string AcLVlZIJqP;
      string IErqhqdPLi;
      string IiGXeYdfCC;
      string UijZJrEZoN;
      string blaHPQGVtR;
      string fEzXaQWnpN;
      string ucHotZTSho;
      string lDZyHWIzHN;
      if(fBcMyaoOuK == VQwbmjwSWY){RIkkWQiMzr = true;}
      else if(VQwbmjwSWY == fBcMyaoOuK){mLSBAhCDSZ = true;}
      if(ZLgniZFwAE == UyNcIJTKHi){VPjbRzelMp = true;}
      else if(UyNcIJTKHi == ZLgniZFwAE){IVuxjFLnix = true;}
      if(HOANghqdET == AcLVlZIJqP){xnnEecdBQD = true;}
      else if(AcLVlZIJqP == HOANghqdET){OUuNLwrwqp = true;}
      if(VXEXRYHobu == IErqhqdPLi){IWgbwmqVRd = true;}
      else if(IErqhqdPLi == VXEXRYHobu){fxrQVyNTGd = true;}
      if(AESyLcYRlF == IiGXeYdfCC){pGSoTVSyfI = true;}
      else if(IiGXeYdfCC == AESyLcYRlF){igwlJxPTml = true;}
      if(AQWabRBPfQ == UijZJrEZoN){qWlRQdTfFt = true;}
      else if(UijZJrEZoN == AQWabRBPfQ){xWoIFRPEpE = true;}
      if(iLJanBGIVJ == blaHPQGVtR){lgwuiziHfd = true;}
      else if(blaHPQGVtR == iLJanBGIVJ){pGMbtKddal = true;}
      if(SQUEEDwCBD == fEzXaQWnpN){HITizpUykI = true;}
      if(IZqyTEBdwA == ucHotZTSho){JfVHMljOLR = true;}
      if(XrIKMotrJJ == lDZyHWIzHN){SKQXrIKXFT = true;}
      while(fEzXaQWnpN == SQUEEDwCBD){qqgEOhXJDO = true;}
      while(ucHotZTSho == ucHotZTSho){fYIEsJIjLD = true;}
      while(lDZyHWIzHN == lDZyHWIzHN){iIdCnbUTry = true;}
      if(RIkkWQiMzr == true){RIkkWQiMzr = false;}
      if(VPjbRzelMp == true){VPjbRzelMp = false;}
      if(xnnEecdBQD == true){xnnEecdBQD = false;}
      if(IWgbwmqVRd == true){IWgbwmqVRd = false;}
      if(pGSoTVSyfI == true){pGSoTVSyfI = false;}
      if(qWlRQdTfFt == true){qWlRQdTfFt = false;}
      if(lgwuiziHfd == true){lgwuiziHfd = false;}
      if(HITizpUykI == true){HITizpUykI = false;}
      if(JfVHMljOLR == true){JfVHMljOLR = false;}
      if(SKQXrIKXFT == true){SKQXrIKXFT = false;}
      if(mLSBAhCDSZ == true){mLSBAhCDSZ = false;}
      if(IVuxjFLnix == true){IVuxjFLnix = false;}
      if(OUuNLwrwqp == true){OUuNLwrwqp = false;}
      if(fxrQVyNTGd == true){fxrQVyNTGd = false;}
      if(igwlJxPTml == true){igwlJxPTml = false;}
      if(xWoIFRPEpE == true){xWoIFRPEpE = false;}
      if(pGMbtKddal == true){pGMbtKddal = false;}
      if(qqgEOhXJDO == true){qqgEOhXJDO = false;}
      if(fYIEsJIjLD == true){fYIEsJIjLD = false;}
      if(iIdCnbUTry == true){iIdCnbUTry = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ITCMJBXUST
{ 
  void DHUbTrcJnU()
  { 
      bool ZxSRDgQwYe = false;
      bool mEnlePcqWI = false;
      bool KkBtPtpekF = false;
      bool GReOxfzTbt = false;
      bool gZXbYTupor = false;
      bool ababynuYCJ = false;
      bool qlLSXUZYoz = false;
      bool QJOcajMZVu = false;
      bool yzosdepDQI = false;
      bool kaRSCuOFDD = false;
      bool tWAobRMyAO = false;
      bool aUDGKqwRns = false;
      bool dWIfOpruZf = false;
      bool UHVRAbzzQM = false;
      bool RrCBgPXKHK = false;
      bool zwQKYXOTal = false;
      bool ZQXUsTzkGi = false;
      bool rwBbalTGzy = false;
      bool ShnOfYqKsc = false;
      bool NeYemBThIN = false;
      string pXudMCFWea;
      string bNzPiqgXeV;
      string sLPsdLCWZd;
      string SjdiPfetpI;
      string noZVLzqcsE;
      string NpIHXeICzB;
      string zhxAHqiQAD;
      string MlgWgEktge;
      string TYcUQcbWKj;
      string XbtnIFqYNU;
      string PacpraIlZT;
      string sOVUhZFbie;
      string PMGPfjrsOb;
      string MLfMOswmcp;
      string UpwqqIGZGh;
      string APoiEDTMJI;
      string hPWyGgiJGn;
      string dSzsKZPPYW;
      string cSlfaxWxHL;
      string YicUHESyjJ;
      if(pXudMCFWea == PacpraIlZT){ZxSRDgQwYe = true;}
      else if(PacpraIlZT == pXudMCFWea){tWAobRMyAO = true;}
      if(bNzPiqgXeV == sOVUhZFbie){mEnlePcqWI = true;}
      else if(sOVUhZFbie == bNzPiqgXeV){aUDGKqwRns = true;}
      if(sLPsdLCWZd == PMGPfjrsOb){KkBtPtpekF = true;}
      else if(PMGPfjrsOb == sLPsdLCWZd){dWIfOpruZf = true;}
      if(SjdiPfetpI == MLfMOswmcp){GReOxfzTbt = true;}
      else if(MLfMOswmcp == SjdiPfetpI){UHVRAbzzQM = true;}
      if(noZVLzqcsE == UpwqqIGZGh){gZXbYTupor = true;}
      else if(UpwqqIGZGh == noZVLzqcsE){RrCBgPXKHK = true;}
      if(NpIHXeICzB == APoiEDTMJI){ababynuYCJ = true;}
      else if(APoiEDTMJI == NpIHXeICzB){zwQKYXOTal = true;}
      if(zhxAHqiQAD == hPWyGgiJGn){qlLSXUZYoz = true;}
      else if(hPWyGgiJGn == zhxAHqiQAD){ZQXUsTzkGi = true;}
      if(MlgWgEktge == dSzsKZPPYW){QJOcajMZVu = true;}
      if(TYcUQcbWKj == cSlfaxWxHL){yzosdepDQI = true;}
      if(XbtnIFqYNU == YicUHESyjJ){kaRSCuOFDD = true;}
      while(dSzsKZPPYW == MlgWgEktge){rwBbalTGzy = true;}
      while(cSlfaxWxHL == cSlfaxWxHL){ShnOfYqKsc = true;}
      while(YicUHESyjJ == YicUHESyjJ){NeYemBThIN = true;}
      if(ZxSRDgQwYe == true){ZxSRDgQwYe = false;}
      if(mEnlePcqWI == true){mEnlePcqWI = false;}
      if(KkBtPtpekF == true){KkBtPtpekF = false;}
      if(GReOxfzTbt == true){GReOxfzTbt = false;}
      if(gZXbYTupor == true){gZXbYTupor = false;}
      if(ababynuYCJ == true){ababynuYCJ = false;}
      if(qlLSXUZYoz == true){qlLSXUZYoz = false;}
      if(QJOcajMZVu == true){QJOcajMZVu = false;}
      if(yzosdepDQI == true){yzosdepDQI = false;}
      if(kaRSCuOFDD == true){kaRSCuOFDD = false;}
      if(tWAobRMyAO == true){tWAobRMyAO = false;}
      if(aUDGKqwRns == true){aUDGKqwRns = false;}
      if(dWIfOpruZf == true){dWIfOpruZf = false;}
      if(UHVRAbzzQM == true){UHVRAbzzQM = false;}
      if(RrCBgPXKHK == true){RrCBgPXKHK = false;}
      if(zwQKYXOTal == true){zwQKYXOTal = false;}
      if(ZQXUsTzkGi == true){ZQXUsTzkGi = false;}
      if(rwBbalTGzy == true){rwBbalTGzy = false;}
      if(ShnOfYqKsc == true){ShnOfYqKsc = false;}
      if(NeYemBThIN == true){NeYemBThIN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QTITYNKUEC
{ 
  void kihGUfLgZV()
  { 
      bool mMpYdQSMpw = false;
      bool hFYgszoajz = false;
      bool WhVTADAymL = false;
      bool DKYhifssUN = false;
      bool noQtRxbdpp = false;
      bool dszNzFqWYa = false;
      bool QUZerWfqxN = false;
      bool FwFVLgQaBD = false;
      bool bVIwgJKLhd = false;
      bool oWUtxTPlCu = false;
      bool QkgckhncCS = false;
      bool oPUUztLcxh = false;
      bool LUITXiaLYr = false;
      bool RdYGlqoeLy = false;
      bool VhIPnYBzuC = false;
      bool HmnTiwbNFB = false;
      bool HbDJAKqOiI = false;
      bool EfRzLdLrey = false;
      bool gaQWjeoEWo = false;
      bool ObZJqtdzOc = false;
      string aDweoiIlis;
      string qQSTVrEqGF;
      string LcaTistQCf;
      string FPCWJYaDVG;
      string ustSRjxmzY;
      string dYJgjybbwu;
      string oqjDnaNuKw;
      string RBVzKShICz;
      string wGRdBfFUmK;
      string wyHaQDIqdp;
      string VBcCGcDJVR;
      string PTYwyhZGBI;
      string UsIzzStuiH;
      string JqdMcudOWY;
      string cwyVucZKbi;
      string cCoVUcrcDm;
      string iIaOHYoMTD;
      string ELicfYtmEW;
      string sjSzeHBHqA;
      string CAKjoTUjNV;
      if(aDweoiIlis == VBcCGcDJVR){mMpYdQSMpw = true;}
      else if(VBcCGcDJVR == aDweoiIlis){QkgckhncCS = true;}
      if(qQSTVrEqGF == PTYwyhZGBI){hFYgszoajz = true;}
      else if(PTYwyhZGBI == qQSTVrEqGF){oPUUztLcxh = true;}
      if(LcaTistQCf == UsIzzStuiH){WhVTADAymL = true;}
      else if(UsIzzStuiH == LcaTistQCf){LUITXiaLYr = true;}
      if(FPCWJYaDVG == JqdMcudOWY){DKYhifssUN = true;}
      else if(JqdMcudOWY == FPCWJYaDVG){RdYGlqoeLy = true;}
      if(ustSRjxmzY == cwyVucZKbi){noQtRxbdpp = true;}
      else if(cwyVucZKbi == ustSRjxmzY){VhIPnYBzuC = true;}
      if(dYJgjybbwu == cCoVUcrcDm){dszNzFqWYa = true;}
      else if(cCoVUcrcDm == dYJgjybbwu){HmnTiwbNFB = true;}
      if(oqjDnaNuKw == iIaOHYoMTD){QUZerWfqxN = true;}
      else if(iIaOHYoMTD == oqjDnaNuKw){HbDJAKqOiI = true;}
      if(RBVzKShICz == ELicfYtmEW){FwFVLgQaBD = true;}
      if(wGRdBfFUmK == sjSzeHBHqA){bVIwgJKLhd = true;}
      if(wyHaQDIqdp == CAKjoTUjNV){oWUtxTPlCu = true;}
      while(ELicfYtmEW == RBVzKShICz){EfRzLdLrey = true;}
      while(sjSzeHBHqA == sjSzeHBHqA){gaQWjeoEWo = true;}
      while(CAKjoTUjNV == CAKjoTUjNV){ObZJqtdzOc = true;}
      if(mMpYdQSMpw == true){mMpYdQSMpw = false;}
      if(hFYgszoajz == true){hFYgszoajz = false;}
      if(WhVTADAymL == true){WhVTADAymL = false;}
      if(DKYhifssUN == true){DKYhifssUN = false;}
      if(noQtRxbdpp == true){noQtRxbdpp = false;}
      if(dszNzFqWYa == true){dszNzFqWYa = false;}
      if(QUZerWfqxN == true){QUZerWfqxN = false;}
      if(FwFVLgQaBD == true){FwFVLgQaBD = false;}
      if(bVIwgJKLhd == true){bVIwgJKLhd = false;}
      if(oWUtxTPlCu == true){oWUtxTPlCu = false;}
      if(QkgckhncCS == true){QkgckhncCS = false;}
      if(oPUUztLcxh == true){oPUUztLcxh = false;}
      if(LUITXiaLYr == true){LUITXiaLYr = false;}
      if(RdYGlqoeLy == true){RdYGlqoeLy = false;}
      if(VhIPnYBzuC == true){VhIPnYBzuC = false;}
      if(HmnTiwbNFB == true){HmnTiwbNFB = false;}
      if(HbDJAKqOiI == true){HbDJAKqOiI = false;}
      if(EfRzLdLrey == true){EfRzLdLrey = false;}
      if(gaQWjeoEWo == true){gaQWjeoEWo = false;}
      if(ObZJqtdzOc == true){ObZJqtdzOc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class USXPKFLBPA
{ 
  void eJtXbBlIFk()
  { 
      bool UJdWcMNtoP = false;
      bool LpQGtglScc = false;
      bool etpEnLlYQu = false;
      bool HjnTHkOADO = false;
      bool fVhSKHnGuu = false;
      bool ENZhnZSZhQ = false;
      bool ZoctHaCwyJ = false;
      bool SkPNwIMXsg = false;
      bool XecVpsKFfg = false;
      bool RnSloqsnKj = false;
      bool EqIkbSyLle = false;
      bool NufAsuMHDN = false;
      bool QwQQrdRcYF = false;
      bool PYMJcfWqsW = false;
      bool tyTATWISst = false;
      bool dkjxSIarsy = false;
      bool AVmfPohWXN = false;
      bool YUNfSRcQxV = false;
      bool VzjeadnOpU = false;
      bool FeyuWYKmjd = false;
      string kdpPYbKSGV;
      string JmbZAhEeEB;
      string GtBSEpmQdm;
      string teqRHfOJQI;
      string DLEoFpfYTi;
      string PDWpoqbXKh;
      string ntoTbdwJST;
      string SuNuxtpLMO;
      string JOxuWpIAcP;
      string DqzhUJWkNa;
      string tWFzPUoast;
      string BQKuYZxtwl;
      string VugCPaufan;
      string XFylUmIxeC;
      string AgHhOmgDIt;
      string McnaEyoDio;
      string YJzEWuRXZl;
      string QzOtlomymc;
      string trWgbtQWhV;
      string xENpcpgCKS;
      if(kdpPYbKSGV == tWFzPUoast){UJdWcMNtoP = true;}
      else if(tWFzPUoast == kdpPYbKSGV){EqIkbSyLle = true;}
      if(JmbZAhEeEB == BQKuYZxtwl){LpQGtglScc = true;}
      else if(BQKuYZxtwl == JmbZAhEeEB){NufAsuMHDN = true;}
      if(GtBSEpmQdm == VugCPaufan){etpEnLlYQu = true;}
      else if(VugCPaufan == GtBSEpmQdm){QwQQrdRcYF = true;}
      if(teqRHfOJQI == XFylUmIxeC){HjnTHkOADO = true;}
      else if(XFylUmIxeC == teqRHfOJQI){PYMJcfWqsW = true;}
      if(DLEoFpfYTi == AgHhOmgDIt){fVhSKHnGuu = true;}
      else if(AgHhOmgDIt == DLEoFpfYTi){tyTATWISst = true;}
      if(PDWpoqbXKh == McnaEyoDio){ENZhnZSZhQ = true;}
      else if(McnaEyoDio == PDWpoqbXKh){dkjxSIarsy = true;}
      if(ntoTbdwJST == YJzEWuRXZl){ZoctHaCwyJ = true;}
      else if(YJzEWuRXZl == ntoTbdwJST){AVmfPohWXN = true;}
      if(SuNuxtpLMO == QzOtlomymc){SkPNwIMXsg = true;}
      if(JOxuWpIAcP == trWgbtQWhV){XecVpsKFfg = true;}
      if(DqzhUJWkNa == xENpcpgCKS){RnSloqsnKj = true;}
      while(QzOtlomymc == SuNuxtpLMO){YUNfSRcQxV = true;}
      while(trWgbtQWhV == trWgbtQWhV){VzjeadnOpU = true;}
      while(xENpcpgCKS == xENpcpgCKS){FeyuWYKmjd = true;}
      if(UJdWcMNtoP == true){UJdWcMNtoP = false;}
      if(LpQGtglScc == true){LpQGtglScc = false;}
      if(etpEnLlYQu == true){etpEnLlYQu = false;}
      if(HjnTHkOADO == true){HjnTHkOADO = false;}
      if(fVhSKHnGuu == true){fVhSKHnGuu = false;}
      if(ENZhnZSZhQ == true){ENZhnZSZhQ = false;}
      if(ZoctHaCwyJ == true){ZoctHaCwyJ = false;}
      if(SkPNwIMXsg == true){SkPNwIMXsg = false;}
      if(XecVpsKFfg == true){XecVpsKFfg = false;}
      if(RnSloqsnKj == true){RnSloqsnKj = false;}
      if(EqIkbSyLle == true){EqIkbSyLle = false;}
      if(NufAsuMHDN == true){NufAsuMHDN = false;}
      if(QwQQrdRcYF == true){QwQQrdRcYF = false;}
      if(PYMJcfWqsW == true){PYMJcfWqsW = false;}
      if(tyTATWISst == true){tyTATWISst = false;}
      if(dkjxSIarsy == true){dkjxSIarsy = false;}
      if(AVmfPohWXN == true){AVmfPohWXN = false;}
      if(YUNfSRcQxV == true){YUNfSRcQxV = false;}
      if(VzjeadnOpU == true){VzjeadnOpU = false;}
      if(FeyuWYKmjd == true){FeyuWYKmjd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XMEHIVNBPL
{ 
  void cyUcyoqSXL()
  { 
      bool upMowTIssz = false;
      bool WYmbDLIJmE = false;
      bool yZxKAYxANB = false;
      bool wmkuJLSBIE = false;
      bool rXhUBDKhSX = false;
      bool QrfhzUsBoW = false;
      bool WIerDjmrRr = false;
      bool sGAiMarbJx = false;
      bool NPhpkDHDwn = false;
      bool SQMlgiroRR = false;
      bool PSPaeJqwUX = false;
      bool cQrrIHZoHz = false;
      bool bjucYbtOBc = false;
      bool hCKrguzHLa = false;
      bool LKhXLBYTcZ = false;
      bool JDhSoeWlBC = false;
      bool PcurpaGzKN = false;
      bool HRcfmRBXRX = false;
      bool DZkbTeTrCC = false;
      bool XMGJLiPpgj = false;
      string BceRjMWNrB;
      string ICbXCOAjhR;
      string pFQOMwtBRZ;
      string TmZffGJoHn;
      string sbhAhsJccW;
      string ekhiBuMQFn;
      string RUuSgUcuqu;
      string ELbtXNXPfS;
      string mQXuthFpek;
      string tsiSVXgPTN;
      string QNlhRTJnLm;
      string XxjlBBxAXz;
      string PlQGBLbIYz;
      string gIuSCYdpca;
      string YQerNwIwRT;
      string afqTydxffG;
      string qAOLFPBRjb;
      string XGWxZyGXsE;
      string CeqFXBQbUY;
      string byJViYCTlx;
      if(BceRjMWNrB == QNlhRTJnLm){upMowTIssz = true;}
      else if(QNlhRTJnLm == BceRjMWNrB){PSPaeJqwUX = true;}
      if(ICbXCOAjhR == XxjlBBxAXz){WYmbDLIJmE = true;}
      else if(XxjlBBxAXz == ICbXCOAjhR){cQrrIHZoHz = true;}
      if(pFQOMwtBRZ == PlQGBLbIYz){yZxKAYxANB = true;}
      else if(PlQGBLbIYz == pFQOMwtBRZ){bjucYbtOBc = true;}
      if(TmZffGJoHn == gIuSCYdpca){wmkuJLSBIE = true;}
      else if(gIuSCYdpca == TmZffGJoHn){hCKrguzHLa = true;}
      if(sbhAhsJccW == YQerNwIwRT){rXhUBDKhSX = true;}
      else if(YQerNwIwRT == sbhAhsJccW){LKhXLBYTcZ = true;}
      if(ekhiBuMQFn == afqTydxffG){QrfhzUsBoW = true;}
      else if(afqTydxffG == ekhiBuMQFn){JDhSoeWlBC = true;}
      if(RUuSgUcuqu == qAOLFPBRjb){WIerDjmrRr = true;}
      else if(qAOLFPBRjb == RUuSgUcuqu){PcurpaGzKN = true;}
      if(ELbtXNXPfS == XGWxZyGXsE){sGAiMarbJx = true;}
      if(mQXuthFpek == CeqFXBQbUY){NPhpkDHDwn = true;}
      if(tsiSVXgPTN == byJViYCTlx){SQMlgiroRR = true;}
      while(XGWxZyGXsE == ELbtXNXPfS){HRcfmRBXRX = true;}
      while(CeqFXBQbUY == CeqFXBQbUY){DZkbTeTrCC = true;}
      while(byJViYCTlx == byJViYCTlx){XMGJLiPpgj = true;}
      if(upMowTIssz == true){upMowTIssz = false;}
      if(WYmbDLIJmE == true){WYmbDLIJmE = false;}
      if(yZxKAYxANB == true){yZxKAYxANB = false;}
      if(wmkuJLSBIE == true){wmkuJLSBIE = false;}
      if(rXhUBDKhSX == true){rXhUBDKhSX = false;}
      if(QrfhzUsBoW == true){QrfhzUsBoW = false;}
      if(WIerDjmrRr == true){WIerDjmrRr = false;}
      if(sGAiMarbJx == true){sGAiMarbJx = false;}
      if(NPhpkDHDwn == true){NPhpkDHDwn = false;}
      if(SQMlgiroRR == true){SQMlgiroRR = false;}
      if(PSPaeJqwUX == true){PSPaeJqwUX = false;}
      if(cQrrIHZoHz == true){cQrrIHZoHz = false;}
      if(bjucYbtOBc == true){bjucYbtOBc = false;}
      if(hCKrguzHLa == true){hCKrguzHLa = false;}
      if(LKhXLBYTcZ == true){LKhXLBYTcZ = false;}
      if(JDhSoeWlBC == true){JDhSoeWlBC = false;}
      if(PcurpaGzKN == true){PcurpaGzKN = false;}
      if(HRcfmRBXRX == true){HRcfmRBXRX = false;}
      if(DZkbTeTrCC == true){DZkbTeTrCC = false;}
      if(XMGJLiPpgj == true){XMGJLiPpgj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KBUHGBADWL
{ 
  void xTrWEBukor()
  { 
      bool IQeFRMYpIK = false;
      bool wkNXhuCwcQ = false;
      bool EBIfjGlwkx = false;
      bool OKlslpyjux = false;
      bool fjKQgwWZTs = false;
      bool uUclYGIzVK = false;
      bool abEKwkyUlr = false;
      bool wSBekUpqzn = false;
      bool iLbrCtgzUf = false;
      bool gzOjVDezUu = false;
      bool xCnbxcSxBE = false;
      bool QQzhaPAMIB = false;
      bool EzzFKwEQJh = false;
      bool opWDpgWzuY = false;
      bool ajyQPPAfJF = false;
      bool DSqSqyChRA = false;
      bool YCnTOZtwqt = false;
      bool sARiaUAipt = false;
      bool wXHDdWzDMr = false;
      bool dnhtAXueBo = false;
      string VuGwsWJgBm;
      string AwuQcqGaWV;
      string hzlijXTxBF;
      string GjwJDgczSb;
      string MrBWPXZemM;
      string zMbFmVJWLV;
      string DMeufPAkNu;
      string OGIuIoyPSM;
      string xnJoGtIpWg;
      string WFnwYANFpz;
      string WoRqyrEgwx;
      string XtEzYOCpnl;
      string HKOfXISMWI;
      string brYToHWRqN;
      string patYJcBnWJ;
      string xXQEqMakSo;
      string YrJnVfUjJQ;
      string rjyZwfQoWt;
      string HdoMKEaTbc;
      string gkyCoyRFDc;
      if(VuGwsWJgBm == WoRqyrEgwx){IQeFRMYpIK = true;}
      else if(WoRqyrEgwx == VuGwsWJgBm){xCnbxcSxBE = true;}
      if(AwuQcqGaWV == XtEzYOCpnl){wkNXhuCwcQ = true;}
      else if(XtEzYOCpnl == AwuQcqGaWV){QQzhaPAMIB = true;}
      if(hzlijXTxBF == HKOfXISMWI){EBIfjGlwkx = true;}
      else if(HKOfXISMWI == hzlijXTxBF){EzzFKwEQJh = true;}
      if(GjwJDgczSb == brYToHWRqN){OKlslpyjux = true;}
      else if(brYToHWRqN == GjwJDgczSb){opWDpgWzuY = true;}
      if(MrBWPXZemM == patYJcBnWJ){fjKQgwWZTs = true;}
      else if(patYJcBnWJ == MrBWPXZemM){ajyQPPAfJF = true;}
      if(zMbFmVJWLV == xXQEqMakSo){uUclYGIzVK = true;}
      else if(xXQEqMakSo == zMbFmVJWLV){DSqSqyChRA = true;}
      if(DMeufPAkNu == YrJnVfUjJQ){abEKwkyUlr = true;}
      else if(YrJnVfUjJQ == DMeufPAkNu){YCnTOZtwqt = true;}
      if(OGIuIoyPSM == rjyZwfQoWt){wSBekUpqzn = true;}
      if(xnJoGtIpWg == HdoMKEaTbc){iLbrCtgzUf = true;}
      if(WFnwYANFpz == gkyCoyRFDc){gzOjVDezUu = true;}
      while(rjyZwfQoWt == OGIuIoyPSM){sARiaUAipt = true;}
      while(HdoMKEaTbc == HdoMKEaTbc){wXHDdWzDMr = true;}
      while(gkyCoyRFDc == gkyCoyRFDc){dnhtAXueBo = true;}
      if(IQeFRMYpIK == true){IQeFRMYpIK = false;}
      if(wkNXhuCwcQ == true){wkNXhuCwcQ = false;}
      if(EBIfjGlwkx == true){EBIfjGlwkx = false;}
      if(OKlslpyjux == true){OKlslpyjux = false;}
      if(fjKQgwWZTs == true){fjKQgwWZTs = false;}
      if(uUclYGIzVK == true){uUclYGIzVK = false;}
      if(abEKwkyUlr == true){abEKwkyUlr = false;}
      if(wSBekUpqzn == true){wSBekUpqzn = false;}
      if(iLbrCtgzUf == true){iLbrCtgzUf = false;}
      if(gzOjVDezUu == true){gzOjVDezUu = false;}
      if(xCnbxcSxBE == true){xCnbxcSxBE = false;}
      if(QQzhaPAMIB == true){QQzhaPAMIB = false;}
      if(EzzFKwEQJh == true){EzzFKwEQJh = false;}
      if(opWDpgWzuY == true){opWDpgWzuY = false;}
      if(ajyQPPAfJF == true){ajyQPPAfJF = false;}
      if(DSqSqyChRA == true){DSqSqyChRA = false;}
      if(YCnTOZtwqt == true){YCnTOZtwqt = false;}
      if(sARiaUAipt == true){sARiaUAipt = false;}
      if(wXHDdWzDMr == true){wXHDdWzDMr = false;}
      if(dnhtAXueBo == true){dnhtAXueBo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SFWLKUQUWK
{ 
  void jrfUWnYokT()
  { 
      bool BKlmUuzZuK = false;
      bool tILjdSrroq = false;
      bool atVuVwmsgO = false;
      bool gLtLWJfAdk = false;
      bool CuHzEIGrkR = false;
      bool OgeOgGnpRX = false;
      bool HGrgdiNANT = false;
      bool mqOEnfmVpM = false;
      bool ouHOzzffeP = false;
      bool UoiFcuCZVV = false;
      bool uGdQdXSaZB = false;
      bool SSzEiMycgd = false;
      bool ChVxzyHIar = false;
      bool cMAURiQpkb = false;
      bool fFFcxCoeWQ = false;
      bool xYsqSMjgRf = false;
      bool QKzgXFRelA = false;
      bool wHrFyxbrAx = false;
      bool IbkKuETJBF = false;
      bool yiYELVFYFq = false;
      string VRGcgxChce;
      string OqrtHsinrm;
      string FTJbomiiri;
      string lyTrMWfmiL;
      string hSZRHTGiQV;
      string eCGRpBHens;
      string NTpsrQXAgk;
      string MwFgElsrUU;
      string fARVEjqCBL;
      string OBzoxNbgYq;
      string wGBfJhwZMD;
      string IPJSNNCUnI;
      string YVyVWLxPiq;
      string JMScYZylMV;
      string mRpyDyqfbj;
      string LHrQSZHeIx;
      string kfqUsuxgtn;
      string PQHSUHfzSX;
      string TRnyfCUCKy;
      string RScOkGZUFH;
      if(VRGcgxChce == wGBfJhwZMD){BKlmUuzZuK = true;}
      else if(wGBfJhwZMD == VRGcgxChce){uGdQdXSaZB = true;}
      if(OqrtHsinrm == IPJSNNCUnI){tILjdSrroq = true;}
      else if(IPJSNNCUnI == OqrtHsinrm){SSzEiMycgd = true;}
      if(FTJbomiiri == YVyVWLxPiq){atVuVwmsgO = true;}
      else if(YVyVWLxPiq == FTJbomiiri){ChVxzyHIar = true;}
      if(lyTrMWfmiL == JMScYZylMV){gLtLWJfAdk = true;}
      else if(JMScYZylMV == lyTrMWfmiL){cMAURiQpkb = true;}
      if(hSZRHTGiQV == mRpyDyqfbj){CuHzEIGrkR = true;}
      else if(mRpyDyqfbj == hSZRHTGiQV){fFFcxCoeWQ = true;}
      if(eCGRpBHens == LHrQSZHeIx){OgeOgGnpRX = true;}
      else if(LHrQSZHeIx == eCGRpBHens){xYsqSMjgRf = true;}
      if(NTpsrQXAgk == kfqUsuxgtn){HGrgdiNANT = true;}
      else if(kfqUsuxgtn == NTpsrQXAgk){QKzgXFRelA = true;}
      if(MwFgElsrUU == PQHSUHfzSX){mqOEnfmVpM = true;}
      if(fARVEjqCBL == TRnyfCUCKy){ouHOzzffeP = true;}
      if(OBzoxNbgYq == RScOkGZUFH){UoiFcuCZVV = true;}
      while(PQHSUHfzSX == MwFgElsrUU){wHrFyxbrAx = true;}
      while(TRnyfCUCKy == TRnyfCUCKy){IbkKuETJBF = true;}
      while(RScOkGZUFH == RScOkGZUFH){yiYELVFYFq = true;}
      if(BKlmUuzZuK == true){BKlmUuzZuK = false;}
      if(tILjdSrroq == true){tILjdSrroq = false;}
      if(atVuVwmsgO == true){atVuVwmsgO = false;}
      if(gLtLWJfAdk == true){gLtLWJfAdk = false;}
      if(CuHzEIGrkR == true){CuHzEIGrkR = false;}
      if(OgeOgGnpRX == true){OgeOgGnpRX = false;}
      if(HGrgdiNANT == true){HGrgdiNANT = false;}
      if(mqOEnfmVpM == true){mqOEnfmVpM = false;}
      if(ouHOzzffeP == true){ouHOzzffeP = false;}
      if(UoiFcuCZVV == true){UoiFcuCZVV = false;}
      if(uGdQdXSaZB == true){uGdQdXSaZB = false;}
      if(SSzEiMycgd == true){SSzEiMycgd = false;}
      if(ChVxzyHIar == true){ChVxzyHIar = false;}
      if(cMAURiQpkb == true){cMAURiQpkb = false;}
      if(fFFcxCoeWQ == true){fFFcxCoeWQ = false;}
      if(xYsqSMjgRf == true){xYsqSMjgRf = false;}
      if(QKzgXFRelA == true){QKzgXFRelA = false;}
      if(wHrFyxbrAx == true){wHrFyxbrAx = false;}
      if(IbkKuETJBF == true){IbkKuETJBF = false;}
      if(yiYELVFYFq == true){yiYELVFYFq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EPIDVEUDAI
{ 
  void xSMExysMrQ()
  { 
      bool AsRDlCbcRf = false;
      bool lSuklXjXVY = false;
      bool VxLrxkgcbI = false;
      bool ENbytXdYmx = false;
      bool IYchhrItab = false;
      bool hNoEkCgYGA = false;
      bool VyAIaYqwqO = false;
      bool sLkYPwTdKE = false;
      bool clCzaqXXNq = false;
      bool pERlbKYTGJ = false;
      bool BMDMiVcPnn = false;
      bool hDNBXiuAhj = false;
      bool ATizXnsyxF = false;
      bool XzXBDPhoQE = false;
      bool OIiYImqPOr = false;
      bool OXlVIhcDou = false;
      bool bdRiQieLyH = false;
      bool AGjdVrjJqj = false;
      bool xcjFpzNBsU = false;
      bool mdAVbjpzIZ = false;
      string EiPWFAHeKS;
      string xjhqskAzWx;
      string XRUZkJSENB;
      string fuKqxjTGCC;
      string rrJjupHdZG;
      string nzRqrmOoku;
      string hDQImBZqtI;
      string QtwUEeHjdu;
      string BndHMgdSzJ;
      string VeUHUobAxt;
      string QQjRpsCwlM;
      string edKptsYIuF;
      string XGrjllZoAP;
      string DGljdkDLRT;
      string egglerTdMa;
      string PSErVKYAfE;
      string TMwVJXqZMJ;
      string oNqbapYFFt;
      string RwbYzjBtNT;
      string LDfNzRkLcG;
      if(EiPWFAHeKS == QQjRpsCwlM){AsRDlCbcRf = true;}
      else if(QQjRpsCwlM == EiPWFAHeKS){BMDMiVcPnn = true;}
      if(xjhqskAzWx == edKptsYIuF){lSuklXjXVY = true;}
      else if(edKptsYIuF == xjhqskAzWx){hDNBXiuAhj = true;}
      if(XRUZkJSENB == XGrjllZoAP){VxLrxkgcbI = true;}
      else if(XGrjllZoAP == XRUZkJSENB){ATizXnsyxF = true;}
      if(fuKqxjTGCC == DGljdkDLRT){ENbytXdYmx = true;}
      else if(DGljdkDLRT == fuKqxjTGCC){XzXBDPhoQE = true;}
      if(rrJjupHdZG == egglerTdMa){IYchhrItab = true;}
      else if(egglerTdMa == rrJjupHdZG){OIiYImqPOr = true;}
      if(nzRqrmOoku == PSErVKYAfE){hNoEkCgYGA = true;}
      else if(PSErVKYAfE == nzRqrmOoku){OXlVIhcDou = true;}
      if(hDQImBZqtI == TMwVJXqZMJ){VyAIaYqwqO = true;}
      else if(TMwVJXqZMJ == hDQImBZqtI){bdRiQieLyH = true;}
      if(QtwUEeHjdu == oNqbapYFFt){sLkYPwTdKE = true;}
      if(BndHMgdSzJ == RwbYzjBtNT){clCzaqXXNq = true;}
      if(VeUHUobAxt == LDfNzRkLcG){pERlbKYTGJ = true;}
      while(oNqbapYFFt == QtwUEeHjdu){AGjdVrjJqj = true;}
      while(RwbYzjBtNT == RwbYzjBtNT){xcjFpzNBsU = true;}
      while(LDfNzRkLcG == LDfNzRkLcG){mdAVbjpzIZ = true;}
      if(AsRDlCbcRf == true){AsRDlCbcRf = false;}
      if(lSuklXjXVY == true){lSuklXjXVY = false;}
      if(VxLrxkgcbI == true){VxLrxkgcbI = false;}
      if(ENbytXdYmx == true){ENbytXdYmx = false;}
      if(IYchhrItab == true){IYchhrItab = false;}
      if(hNoEkCgYGA == true){hNoEkCgYGA = false;}
      if(VyAIaYqwqO == true){VyAIaYqwqO = false;}
      if(sLkYPwTdKE == true){sLkYPwTdKE = false;}
      if(clCzaqXXNq == true){clCzaqXXNq = false;}
      if(pERlbKYTGJ == true){pERlbKYTGJ = false;}
      if(BMDMiVcPnn == true){BMDMiVcPnn = false;}
      if(hDNBXiuAhj == true){hDNBXiuAhj = false;}
      if(ATizXnsyxF == true){ATizXnsyxF = false;}
      if(XzXBDPhoQE == true){XzXBDPhoQE = false;}
      if(OIiYImqPOr == true){OIiYImqPOr = false;}
      if(OXlVIhcDou == true){OXlVIhcDou = false;}
      if(bdRiQieLyH == true){bdRiQieLyH = false;}
      if(AGjdVrjJqj == true){AGjdVrjJqj = false;}
      if(xcjFpzNBsU == true){xcjFpzNBsU = false;}
      if(mdAVbjpzIZ == true){mdAVbjpzIZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KYGZFKDDCR
{ 
  void dwAGPielFk()
  { 
      bool doegPqBpkw = false;
      bool tfwowuHkjH = false;
      bool BcMDpmygUh = false;
      bool NFJJpbhNkZ = false;
      bool BtHxBRNHiM = false;
      bool UITCxBcaqc = false;
      bool rUVDinVlyU = false;
      bool NtzJGHVOCY = false;
      bool YpxIMFlHMo = false;
      bool yGVIgfYDOM = false;
      bool uaJNyaIKup = false;
      bool fOYSDBWNqd = false;
      bool COZJVHXqbZ = false;
      bool hRzocygiJk = false;
      bool waLVJjgDEf = false;
      bool JLMkKgAArp = false;
      bool DRhVINOjpF = false;
      bool UnDFgaCEzl = false;
      bool aTlwQWENdw = false;
      bool xfqTherpNu = false;
      string quMbjdefyk;
      string znrIdSQFyV;
      string ZkHMLLwsIn;
      string saNHiyDtfI;
      string bpVdSsYbIo;
      string WsqBLFnAQX;
      string hlXKqYakZe;
      string PVYotiOcsR;
      string lTjSRAiLwc;
      string KCdHaoSLmt;
      string SnCdZATBGb;
      string pKGylNCEsq;
      string oOnwTMrQOF;
      string QDozzxQGrQ;
      string fgFUlzweVM;
      string mNSwEDzGJM;
      string ICmBKmVGzn;
      string xuMbKHJTJU;
      string QMuBRCkstu;
      string yKweHctDJz;
      if(quMbjdefyk == SnCdZATBGb){doegPqBpkw = true;}
      else if(SnCdZATBGb == quMbjdefyk){uaJNyaIKup = true;}
      if(znrIdSQFyV == pKGylNCEsq){tfwowuHkjH = true;}
      else if(pKGylNCEsq == znrIdSQFyV){fOYSDBWNqd = true;}
      if(ZkHMLLwsIn == oOnwTMrQOF){BcMDpmygUh = true;}
      else if(oOnwTMrQOF == ZkHMLLwsIn){COZJVHXqbZ = true;}
      if(saNHiyDtfI == QDozzxQGrQ){NFJJpbhNkZ = true;}
      else if(QDozzxQGrQ == saNHiyDtfI){hRzocygiJk = true;}
      if(bpVdSsYbIo == fgFUlzweVM){BtHxBRNHiM = true;}
      else if(fgFUlzweVM == bpVdSsYbIo){waLVJjgDEf = true;}
      if(WsqBLFnAQX == mNSwEDzGJM){UITCxBcaqc = true;}
      else if(mNSwEDzGJM == WsqBLFnAQX){JLMkKgAArp = true;}
      if(hlXKqYakZe == ICmBKmVGzn){rUVDinVlyU = true;}
      else if(ICmBKmVGzn == hlXKqYakZe){DRhVINOjpF = true;}
      if(PVYotiOcsR == xuMbKHJTJU){NtzJGHVOCY = true;}
      if(lTjSRAiLwc == QMuBRCkstu){YpxIMFlHMo = true;}
      if(KCdHaoSLmt == yKweHctDJz){yGVIgfYDOM = true;}
      while(xuMbKHJTJU == PVYotiOcsR){UnDFgaCEzl = true;}
      while(QMuBRCkstu == QMuBRCkstu){aTlwQWENdw = true;}
      while(yKweHctDJz == yKweHctDJz){xfqTherpNu = true;}
      if(doegPqBpkw == true){doegPqBpkw = false;}
      if(tfwowuHkjH == true){tfwowuHkjH = false;}
      if(BcMDpmygUh == true){BcMDpmygUh = false;}
      if(NFJJpbhNkZ == true){NFJJpbhNkZ = false;}
      if(BtHxBRNHiM == true){BtHxBRNHiM = false;}
      if(UITCxBcaqc == true){UITCxBcaqc = false;}
      if(rUVDinVlyU == true){rUVDinVlyU = false;}
      if(NtzJGHVOCY == true){NtzJGHVOCY = false;}
      if(YpxIMFlHMo == true){YpxIMFlHMo = false;}
      if(yGVIgfYDOM == true){yGVIgfYDOM = false;}
      if(uaJNyaIKup == true){uaJNyaIKup = false;}
      if(fOYSDBWNqd == true){fOYSDBWNqd = false;}
      if(COZJVHXqbZ == true){COZJVHXqbZ = false;}
      if(hRzocygiJk == true){hRzocygiJk = false;}
      if(waLVJjgDEf == true){waLVJjgDEf = false;}
      if(JLMkKgAArp == true){JLMkKgAArp = false;}
      if(DRhVINOjpF == true){DRhVINOjpF = false;}
      if(UnDFgaCEzl == true){UnDFgaCEzl = false;}
      if(aTlwQWENdw == true){aTlwQWENdw = false;}
      if(xfqTherpNu == true){xfqTherpNu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RNOMIEEXAC
{ 
  void ofpXqMEXyH()
  { 
      bool pGATtUailn = false;
      bool SixIAYkhzY = false;
      bool GCCdqFUGoP = false;
      bool DlwygmJLkf = false;
      bool FqaIjDCASw = false;
      bool VoQcJnEVbn = false;
      bool ATsWjflyaM = false;
      bool OYwSTObstn = false;
      bool DUnssNUSos = false;
      bool iniwfkxEXD = false;
      bool QEYFgxsxJt = false;
      bool MKbnkeeAcW = false;
      bool LSJhcaozmi = false;
      bool RWUpWzuhLw = false;
      bool UXJtgXMuLA = false;
      bool GxaBrytqcF = false;
      bool HsKabookRl = false;
      bool iwngBnIOAE = false;
      bool OtnlbUwTyX = false;
      bool EEFGobMiRq = false;
      string TNBqQQJPaG;
      string KTzngiXkRL;
      string BlxCeFPlUf;
      string pVkxeIQxJS;
      string qhGUPUrfjM;
      string AWrUEgPzML;
      string BWuuPohBIX;
      string SaayUSfcmJ;
      string MiCHeTdQsy;
      string sRjxRTmKFa;
      string lqWLtZusAk;
      string BmLDzRUmPu;
      string LRIKeApdfA;
      string fUWMWULpME;
      string YjPIwGFgyA;
      string zAtJOUiLgt;
      string iQNAFfPzfd;
      string FdZLWaBzOX;
      string tJffAfZNxC;
      string lAJSVHWPCP;
      if(TNBqQQJPaG == lqWLtZusAk){pGATtUailn = true;}
      else if(lqWLtZusAk == TNBqQQJPaG){QEYFgxsxJt = true;}
      if(KTzngiXkRL == BmLDzRUmPu){SixIAYkhzY = true;}
      else if(BmLDzRUmPu == KTzngiXkRL){MKbnkeeAcW = true;}
      if(BlxCeFPlUf == LRIKeApdfA){GCCdqFUGoP = true;}
      else if(LRIKeApdfA == BlxCeFPlUf){LSJhcaozmi = true;}
      if(pVkxeIQxJS == fUWMWULpME){DlwygmJLkf = true;}
      else if(fUWMWULpME == pVkxeIQxJS){RWUpWzuhLw = true;}
      if(qhGUPUrfjM == YjPIwGFgyA){FqaIjDCASw = true;}
      else if(YjPIwGFgyA == qhGUPUrfjM){UXJtgXMuLA = true;}
      if(AWrUEgPzML == zAtJOUiLgt){VoQcJnEVbn = true;}
      else if(zAtJOUiLgt == AWrUEgPzML){GxaBrytqcF = true;}
      if(BWuuPohBIX == iQNAFfPzfd){ATsWjflyaM = true;}
      else if(iQNAFfPzfd == BWuuPohBIX){HsKabookRl = true;}
      if(SaayUSfcmJ == FdZLWaBzOX){OYwSTObstn = true;}
      if(MiCHeTdQsy == tJffAfZNxC){DUnssNUSos = true;}
      if(sRjxRTmKFa == lAJSVHWPCP){iniwfkxEXD = true;}
      while(FdZLWaBzOX == SaayUSfcmJ){iwngBnIOAE = true;}
      while(tJffAfZNxC == tJffAfZNxC){OtnlbUwTyX = true;}
      while(lAJSVHWPCP == lAJSVHWPCP){EEFGobMiRq = true;}
      if(pGATtUailn == true){pGATtUailn = false;}
      if(SixIAYkhzY == true){SixIAYkhzY = false;}
      if(GCCdqFUGoP == true){GCCdqFUGoP = false;}
      if(DlwygmJLkf == true){DlwygmJLkf = false;}
      if(FqaIjDCASw == true){FqaIjDCASw = false;}
      if(VoQcJnEVbn == true){VoQcJnEVbn = false;}
      if(ATsWjflyaM == true){ATsWjflyaM = false;}
      if(OYwSTObstn == true){OYwSTObstn = false;}
      if(DUnssNUSos == true){DUnssNUSos = false;}
      if(iniwfkxEXD == true){iniwfkxEXD = false;}
      if(QEYFgxsxJt == true){QEYFgxsxJt = false;}
      if(MKbnkeeAcW == true){MKbnkeeAcW = false;}
      if(LSJhcaozmi == true){LSJhcaozmi = false;}
      if(RWUpWzuhLw == true){RWUpWzuhLw = false;}
      if(UXJtgXMuLA == true){UXJtgXMuLA = false;}
      if(GxaBrytqcF == true){GxaBrytqcF = false;}
      if(HsKabookRl == true){HsKabookRl = false;}
      if(iwngBnIOAE == true){iwngBnIOAE = false;}
      if(OtnlbUwTyX == true){OtnlbUwTyX = false;}
      if(EEFGobMiRq == true){EEFGobMiRq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GURDJNYOVZ
{ 
  void dLixTbAnPl()
  { 
      bool YYsLWUAFkE = false;
      bool bFDLGfdyoC = false;
      bool kJLjjrnjSh = false;
      bool rWsxeItnZo = false;
      bool BzsmwjDftt = false;
      bool lclmZPNJbe = false;
      bool gPmCLFMGfy = false;
      bool loYzBlQXnz = false;
      bool oHoXwOjFWP = false;
      bool ujMtIkMpaq = false;
      bool XxzwIwElln = false;
      bool zoVboYaOGx = false;
      bool UGiQCBcdqP = false;
      bool ZZwxaqHrOz = false;
      bool KxThPFNjFi = false;
      bool JxjdVQNitH = false;
      bool TZuVOZrYAy = false;
      bool QizGlWmBAw = false;
      bool mrYHGboRaJ = false;
      bool dXxHejCxTp = false;
      string ALmUVlaOBA;
      string pNmojOLOLN;
      string cQTgOXZAyK;
      string yKzafFFNnC;
      string OcbdxPchLI;
      string HpXKpiqGFy;
      string LaQpBeOMIe;
      string JxaJzzopjz;
      string trnoDIlnjx;
      string NzHopmMkbR;
      string AQYgzJOOLp;
      string tBVGDTmamr;
      string rabLQKokTL;
      string lDNRydTHpt;
      string sXbsCMcBkW;
      string AkyjZZnMPn;
      string TduADpmEHZ;
      string zeksyUyiJE;
      string hnzwKBFdrX;
      string pGqBZPbbpL;
      if(ALmUVlaOBA == AQYgzJOOLp){YYsLWUAFkE = true;}
      else if(AQYgzJOOLp == ALmUVlaOBA){XxzwIwElln = true;}
      if(pNmojOLOLN == tBVGDTmamr){bFDLGfdyoC = true;}
      else if(tBVGDTmamr == pNmojOLOLN){zoVboYaOGx = true;}
      if(cQTgOXZAyK == rabLQKokTL){kJLjjrnjSh = true;}
      else if(rabLQKokTL == cQTgOXZAyK){UGiQCBcdqP = true;}
      if(yKzafFFNnC == lDNRydTHpt){rWsxeItnZo = true;}
      else if(lDNRydTHpt == yKzafFFNnC){ZZwxaqHrOz = true;}
      if(OcbdxPchLI == sXbsCMcBkW){BzsmwjDftt = true;}
      else if(sXbsCMcBkW == OcbdxPchLI){KxThPFNjFi = true;}
      if(HpXKpiqGFy == AkyjZZnMPn){lclmZPNJbe = true;}
      else if(AkyjZZnMPn == HpXKpiqGFy){JxjdVQNitH = true;}
      if(LaQpBeOMIe == TduADpmEHZ){gPmCLFMGfy = true;}
      else if(TduADpmEHZ == LaQpBeOMIe){TZuVOZrYAy = true;}
      if(JxaJzzopjz == zeksyUyiJE){loYzBlQXnz = true;}
      if(trnoDIlnjx == hnzwKBFdrX){oHoXwOjFWP = true;}
      if(NzHopmMkbR == pGqBZPbbpL){ujMtIkMpaq = true;}
      while(zeksyUyiJE == JxaJzzopjz){QizGlWmBAw = true;}
      while(hnzwKBFdrX == hnzwKBFdrX){mrYHGboRaJ = true;}
      while(pGqBZPbbpL == pGqBZPbbpL){dXxHejCxTp = true;}
      if(YYsLWUAFkE == true){YYsLWUAFkE = false;}
      if(bFDLGfdyoC == true){bFDLGfdyoC = false;}
      if(kJLjjrnjSh == true){kJLjjrnjSh = false;}
      if(rWsxeItnZo == true){rWsxeItnZo = false;}
      if(BzsmwjDftt == true){BzsmwjDftt = false;}
      if(lclmZPNJbe == true){lclmZPNJbe = false;}
      if(gPmCLFMGfy == true){gPmCLFMGfy = false;}
      if(loYzBlQXnz == true){loYzBlQXnz = false;}
      if(oHoXwOjFWP == true){oHoXwOjFWP = false;}
      if(ujMtIkMpaq == true){ujMtIkMpaq = false;}
      if(XxzwIwElln == true){XxzwIwElln = false;}
      if(zoVboYaOGx == true){zoVboYaOGx = false;}
      if(UGiQCBcdqP == true){UGiQCBcdqP = false;}
      if(ZZwxaqHrOz == true){ZZwxaqHrOz = false;}
      if(KxThPFNjFi == true){KxThPFNjFi = false;}
      if(JxjdVQNitH == true){JxjdVQNitH = false;}
      if(TZuVOZrYAy == true){TZuVOZrYAy = false;}
      if(QizGlWmBAw == true){QizGlWmBAw = false;}
      if(mrYHGboRaJ == true){mrYHGboRaJ = false;}
      if(dXxHejCxTp == true){dXxHejCxTp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZVSTGVTUJP
{ 
  void FPTkKkjnWA()
  { 
      bool QYYlHDpwkq = false;
      bool BpELShUxUJ = false;
      bool LBtEmpErfS = false;
      bool rjMpqlVOxt = false;
      bool dpgIAfyrBC = false;
      bool ySNcWOeTyR = false;
      bool yxQSyQcNUg = false;
      bool LGzZfUUlEG = false;
      bool qMqdTZWjTb = false;
      bool HCPfufZNJi = false;
      bool DkWUprSmwB = false;
      bool trPqZlGmzY = false;
      bool trsrYJpTdz = false;
      bool tHbUDGoWma = false;
      bool GimRhOlYFJ = false;
      bool ZmNkoKqeug = false;
      bool CyJwHmPtnS = false;
      bool xizXRKFbKJ = false;
      bool WROUZGsqer = false;
      bool PKaFYIZpKt = false;
      string DMGkmUEdnN;
      string DPjzdOWQlT;
      string XSPrzBhkIw;
      string iGPEOqYqDK;
      string NkfbVokTzz;
      string hdhjmjxOkl;
      string lTUqexAfjm;
      string oeNbFmmmWK;
      string QOkIOEXfQd;
      string tKFRXtPnxY;
      string oEiMJCQGdA;
      string xJqaVXhMbZ;
      string ZUPFreZuEK;
      string WypyULeYzM;
      string nRBPgjSduz;
      string MDLXyTocTe;
      string cUBSdyTsFJ;
      string rIMPlHSzYH;
      string LuAEyTmRzB;
      string WCETjTPhlh;
      if(DMGkmUEdnN == oEiMJCQGdA){QYYlHDpwkq = true;}
      else if(oEiMJCQGdA == DMGkmUEdnN){DkWUprSmwB = true;}
      if(DPjzdOWQlT == xJqaVXhMbZ){BpELShUxUJ = true;}
      else if(xJqaVXhMbZ == DPjzdOWQlT){trPqZlGmzY = true;}
      if(XSPrzBhkIw == ZUPFreZuEK){LBtEmpErfS = true;}
      else if(ZUPFreZuEK == XSPrzBhkIw){trsrYJpTdz = true;}
      if(iGPEOqYqDK == WypyULeYzM){rjMpqlVOxt = true;}
      else if(WypyULeYzM == iGPEOqYqDK){tHbUDGoWma = true;}
      if(NkfbVokTzz == nRBPgjSduz){dpgIAfyrBC = true;}
      else if(nRBPgjSduz == NkfbVokTzz){GimRhOlYFJ = true;}
      if(hdhjmjxOkl == MDLXyTocTe){ySNcWOeTyR = true;}
      else if(MDLXyTocTe == hdhjmjxOkl){ZmNkoKqeug = true;}
      if(lTUqexAfjm == cUBSdyTsFJ){yxQSyQcNUg = true;}
      else if(cUBSdyTsFJ == lTUqexAfjm){CyJwHmPtnS = true;}
      if(oeNbFmmmWK == rIMPlHSzYH){LGzZfUUlEG = true;}
      if(QOkIOEXfQd == LuAEyTmRzB){qMqdTZWjTb = true;}
      if(tKFRXtPnxY == WCETjTPhlh){HCPfufZNJi = true;}
      while(rIMPlHSzYH == oeNbFmmmWK){xizXRKFbKJ = true;}
      while(LuAEyTmRzB == LuAEyTmRzB){WROUZGsqer = true;}
      while(WCETjTPhlh == WCETjTPhlh){PKaFYIZpKt = true;}
      if(QYYlHDpwkq == true){QYYlHDpwkq = false;}
      if(BpELShUxUJ == true){BpELShUxUJ = false;}
      if(LBtEmpErfS == true){LBtEmpErfS = false;}
      if(rjMpqlVOxt == true){rjMpqlVOxt = false;}
      if(dpgIAfyrBC == true){dpgIAfyrBC = false;}
      if(ySNcWOeTyR == true){ySNcWOeTyR = false;}
      if(yxQSyQcNUg == true){yxQSyQcNUg = false;}
      if(LGzZfUUlEG == true){LGzZfUUlEG = false;}
      if(qMqdTZWjTb == true){qMqdTZWjTb = false;}
      if(HCPfufZNJi == true){HCPfufZNJi = false;}
      if(DkWUprSmwB == true){DkWUprSmwB = false;}
      if(trPqZlGmzY == true){trPqZlGmzY = false;}
      if(trsrYJpTdz == true){trsrYJpTdz = false;}
      if(tHbUDGoWma == true){tHbUDGoWma = false;}
      if(GimRhOlYFJ == true){GimRhOlYFJ = false;}
      if(ZmNkoKqeug == true){ZmNkoKqeug = false;}
      if(CyJwHmPtnS == true){CyJwHmPtnS = false;}
      if(xizXRKFbKJ == true){xizXRKFbKJ = false;}
      if(WROUZGsqer == true){WROUZGsqer = false;}
      if(PKaFYIZpKt == true){PKaFYIZpKt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZKFYPZYJTC
{ 
  void YVpYYbMybj()
  { 
      bool GFNNiIgSyI = false;
      bool CSBsLiLhkW = false;
      bool GxtdisbEEq = false;
      bool ZLJDWunxHx = false;
      bool PZruyPETcy = false;
      bool XojmHJLidp = false;
      bool fcOHiqJyVQ = false;
      bool tNZmHgFyfT = false;
      bool oHbGTkaWuN = false;
      bool jETRRlKkMG = false;
      bool GFxMDJOxeZ = false;
      bool DMDKBXBImx = false;
      bool PlCIfotIVU = false;
      bool WUlYMiJOCJ = false;
      bool VdqUJXBIPs = false;
      bool kCxOqTDofN = false;
      bool OFaKDiZexS = false;
      bool OlFcalugyH = false;
      bool nlsciTWXhr = false;
      bool eUhouQCfRZ = false;
      string SzMjxSuMft;
      string QjQGomrYlA;
      string aPaxCDTrye;
      string safAOUYoNF;
      string ZiJGnkzsOe;
      string gZfVhCXPgs;
      string zDNBAoEPrU;
      string NCLfarFUIR;
      string EZdSxTuJSL;
      string xJITGWUIFz;
      string fiAtQeNzup;
      string xCGPnYYuDg;
      string suwgXDtqZD;
      string WxPJkVZjBR;
      string GwNcOtCrfh;
      string xZEYFjlTWM;
      string kWZqSzmxeS;
      string yoskZxhTRc;
      string ABKqGwrpDA;
      string iFNogiWVJO;
      if(SzMjxSuMft == fiAtQeNzup){GFNNiIgSyI = true;}
      else if(fiAtQeNzup == SzMjxSuMft){GFxMDJOxeZ = true;}
      if(QjQGomrYlA == xCGPnYYuDg){CSBsLiLhkW = true;}
      else if(xCGPnYYuDg == QjQGomrYlA){DMDKBXBImx = true;}
      if(aPaxCDTrye == suwgXDtqZD){GxtdisbEEq = true;}
      else if(suwgXDtqZD == aPaxCDTrye){PlCIfotIVU = true;}
      if(safAOUYoNF == WxPJkVZjBR){ZLJDWunxHx = true;}
      else if(WxPJkVZjBR == safAOUYoNF){WUlYMiJOCJ = true;}
      if(ZiJGnkzsOe == GwNcOtCrfh){PZruyPETcy = true;}
      else if(GwNcOtCrfh == ZiJGnkzsOe){VdqUJXBIPs = true;}
      if(gZfVhCXPgs == xZEYFjlTWM){XojmHJLidp = true;}
      else if(xZEYFjlTWM == gZfVhCXPgs){kCxOqTDofN = true;}
      if(zDNBAoEPrU == kWZqSzmxeS){fcOHiqJyVQ = true;}
      else if(kWZqSzmxeS == zDNBAoEPrU){OFaKDiZexS = true;}
      if(NCLfarFUIR == yoskZxhTRc){tNZmHgFyfT = true;}
      if(EZdSxTuJSL == ABKqGwrpDA){oHbGTkaWuN = true;}
      if(xJITGWUIFz == iFNogiWVJO){jETRRlKkMG = true;}
      while(yoskZxhTRc == NCLfarFUIR){OlFcalugyH = true;}
      while(ABKqGwrpDA == ABKqGwrpDA){nlsciTWXhr = true;}
      while(iFNogiWVJO == iFNogiWVJO){eUhouQCfRZ = true;}
      if(GFNNiIgSyI == true){GFNNiIgSyI = false;}
      if(CSBsLiLhkW == true){CSBsLiLhkW = false;}
      if(GxtdisbEEq == true){GxtdisbEEq = false;}
      if(ZLJDWunxHx == true){ZLJDWunxHx = false;}
      if(PZruyPETcy == true){PZruyPETcy = false;}
      if(XojmHJLidp == true){XojmHJLidp = false;}
      if(fcOHiqJyVQ == true){fcOHiqJyVQ = false;}
      if(tNZmHgFyfT == true){tNZmHgFyfT = false;}
      if(oHbGTkaWuN == true){oHbGTkaWuN = false;}
      if(jETRRlKkMG == true){jETRRlKkMG = false;}
      if(GFxMDJOxeZ == true){GFxMDJOxeZ = false;}
      if(DMDKBXBImx == true){DMDKBXBImx = false;}
      if(PlCIfotIVU == true){PlCIfotIVU = false;}
      if(WUlYMiJOCJ == true){WUlYMiJOCJ = false;}
      if(VdqUJXBIPs == true){VdqUJXBIPs = false;}
      if(kCxOqTDofN == true){kCxOqTDofN = false;}
      if(OFaKDiZexS == true){OFaKDiZexS = false;}
      if(OlFcalugyH == true){OlFcalugyH = false;}
      if(nlsciTWXhr == true){nlsciTWXhr = false;}
      if(eUhouQCfRZ == true){eUhouQCfRZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NGVZMOVSLS
{ 
  void rZGarSRafX()
  { 
      bool rLJBVSpOmg = false;
      bool FSZaVGLRFu = false;
      bool IuQOMXJPBe = false;
      bool frtoTiOXMp = false;
      bool GYrFFssGHx = false;
      bool DGgaFwutox = false;
      bool JaNHBMXjHm = false;
      bool rnFOnjDLIS = false;
      bool dDHDbYLTjW = false;
      bool nTiOgeLjDs = false;
      bool UJyUFPBRmU = false;
      bool sjkVSFTJfb = false;
      bool BEzkyXEphI = false;
      bool YSHPyUElyM = false;
      bool XtfPcDhNwa = false;
      bool LBEbqPJNVg = false;
      bool KLiduacUWy = false;
      bool BgKSEHXjHu = false;
      bool oqsHxXOfXh = false;
      bool LqPQCLKCUC = false;
      string noiOjssVQz;
      string dPqEkTnZnE;
      string tYFNkALuHL;
      string RZCVctOeel;
      string RmLMVblUJh;
      string sfAUgPjUci;
      string gxNFhEMVbp;
      string FIuCmGMsqJ;
      string NqlYSlYhoM;
      string KsCuEUYGeR;
      string OQsScjkygZ;
      string CpcTVpKomw;
      string eefOfLGzxS;
      string gGOZtwyTuh;
      string AZAOKTPhZO;
      string JjThljjdmR;
      string dkBOrwbDYY;
      string rpsEuEeREL;
      string uXYiIxmfmK;
      string MTgdDPYlWO;
      if(noiOjssVQz == OQsScjkygZ){rLJBVSpOmg = true;}
      else if(OQsScjkygZ == noiOjssVQz){UJyUFPBRmU = true;}
      if(dPqEkTnZnE == CpcTVpKomw){FSZaVGLRFu = true;}
      else if(CpcTVpKomw == dPqEkTnZnE){sjkVSFTJfb = true;}
      if(tYFNkALuHL == eefOfLGzxS){IuQOMXJPBe = true;}
      else if(eefOfLGzxS == tYFNkALuHL){BEzkyXEphI = true;}
      if(RZCVctOeel == gGOZtwyTuh){frtoTiOXMp = true;}
      else if(gGOZtwyTuh == RZCVctOeel){YSHPyUElyM = true;}
      if(RmLMVblUJh == AZAOKTPhZO){GYrFFssGHx = true;}
      else if(AZAOKTPhZO == RmLMVblUJh){XtfPcDhNwa = true;}
      if(sfAUgPjUci == JjThljjdmR){DGgaFwutox = true;}
      else if(JjThljjdmR == sfAUgPjUci){LBEbqPJNVg = true;}
      if(gxNFhEMVbp == dkBOrwbDYY){JaNHBMXjHm = true;}
      else if(dkBOrwbDYY == gxNFhEMVbp){KLiduacUWy = true;}
      if(FIuCmGMsqJ == rpsEuEeREL){rnFOnjDLIS = true;}
      if(NqlYSlYhoM == uXYiIxmfmK){dDHDbYLTjW = true;}
      if(KsCuEUYGeR == MTgdDPYlWO){nTiOgeLjDs = true;}
      while(rpsEuEeREL == FIuCmGMsqJ){BgKSEHXjHu = true;}
      while(uXYiIxmfmK == uXYiIxmfmK){oqsHxXOfXh = true;}
      while(MTgdDPYlWO == MTgdDPYlWO){LqPQCLKCUC = true;}
      if(rLJBVSpOmg == true){rLJBVSpOmg = false;}
      if(FSZaVGLRFu == true){FSZaVGLRFu = false;}
      if(IuQOMXJPBe == true){IuQOMXJPBe = false;}
      if(frtoTiOXMp == true){frtoTiOXMp = false;}
      if(GYrFFssGHx == true){GYrFFssGHx = false;}
      if(DGgaFwutox == true){DGgaFwutox = false;}
      if(JaNHBMXjHm == true){JaNHBMXjHm = false;}
      if(rnFOnjDLIS == true){rnFOnjDLIS = false;}
      if(dDHDbYLTjW == true){dDHDbYLTjW = false;}
      if(nTiOgeLjDs == true){nTiOgeLjDs = false;}
      if(UJyUFPBRmU == true){UJyUFPBRmU = false;}
      if(sjkVSFTJfb == true){sjkVSFTJfb = false;}
      if(BEzkyXEphI == true){BEzkyXEphI = false;}
      if(YSHPyUElyM == true){YSHPyUElyM = false;}
      if(XtfPcDhNwa == true){XtfPcDhNwa = false;}
      if(LBEbqPJNVg == true){LBEbqPJNVg = false;}
      if(KLiduacUWy == true){KLiduacUWy = false;}
      if(BgKSEHXjHu == true){BgKSEHXjHu = false;}
      if(oqsHxXOfXh == true){oqsHxXOfXh = false;}
      if(LqPQCLKCUC == true){LqPQCLKCUC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GICZIPLWWL
{ 
  void GODiboktFP()
  { 
      bool PBpsbqUDpO = false;
      bool KzILxJmwlB = false;
      bool RFToynakOd = false;
      bool FuXkyRpknu = false;
      bool LhrfbRESQA = false;
      bool nJjJPJhAum = false;
      bool PjoLIPbXMf = false;
      bool TCIqojNnNg = false;
      bool jHTNpuLNUo = false;
      bool jopBfbsfXM = false;
      bool ofGjglBsUf = false;
      bool utmOCIPbVM = false;
      bool DODXudLHLN = false;
      bool qhPBqDBjgE = false;
      bool tRsnspCbyW = false;
      bool LQJKIachoD = false;
      bool ZshGoNdlWz = false;
      bool GftRSkUOeF = false;
      bool ajInBZXFrP = false;
      bool aTtdeAjlzf = false;
      string RXyNDhhluP;
      string zXTFLALJzA;
      string NgamQcSdXh;
      string PtDNrUNFyj;
      string KMPxKKRuho;
      string tPUyjkxLwa;
      string OENNAETGNp;
      string lGKOoARcbF;
      string LXuinzYFcG;
      string XBIXUFzCxG;
      string qLhqCnFFIi;
      string TTjqOqJeYA;
      string eNcGRkxmsi;
      string BPeVOzoDfA;
      string tSwsmEQRId;
      string wTcwacibYR;
      string pRMZhEnObP;
      string CFzYGMRiSN;
      string TfdPmglhtl;
      string QNdNKbGWLh;
      if(RXyNDhhluP == qLhqCnFFIi){PBpsbqUDpO = true;}
      else if(qLhqCnFFIi == RXyNDhhluP){ofGjglBsUf = true;}
      if(zXTFLALJzA == TTjqOqJeYA){KzILxJmwlB = true;}
      else if(TTjqOqJeYA == zXTFLALJzA){utmOCIPbVM = true;}
      if(NgamQcSdXh == eNcGRkxmsi){RFToynakOd = true;}
      else if(eNcGRkxmsi == NgamQcSdXh){DODXudLHLN = true;}
      if(PtDNrUNFyj == BPeVOzoDfA){FuXkyRpknu = true;}
      else if(BPeVOzoDfA == PtDNrUNFyj){qhPBqDBjgE = true;}
      if(KMPxKKRuho == tSwsmEQRId){LhrfbRESQA = true;}
      else if(tSwsmEQRId == KMPxKKRuho){tRsnspCbyW = true;}
      if(tPUyjkxLwa == wTcwacibYR){nJjJPJhAum = true;}
      else if(wTcwacibYR == tPUyjkxLwa){LQJKIachoD = true;}
      if(OENNAETGNp == pRMZhEnObP){PjoLIPbXMf = true;}
      else if(pRMZhEnObP == OENNAETGNp){ZshGoNdlWz = true;}
      if(lGKOoARcbF == CFzYGMRiSN){TCIqojNnNg = true;}
      if(LXuinzYFcG == TfdPmglhtl){jHTNpuLNUo = true;}
      if(XBIXUFzCxG == QNdNKbGWLh){jopBfbsfXM = true;}
      while(CFzYGMRiSN == lGKOoARcbF){GftRSkUOeF = true;}
      while(TfdPmglhtl == TfdPmglhtl){ajInBZXFrP = true;}
      while(QNdNKbGWLh == QNdNKbGWLh){aTtdeAjlzf = true;}
      if(PBpsbqUDpO == true){PBpsbqUDpO = false;}
      if(KzILxJmwlB == true){KzILxJmwlB = false;}
      if(RFToynakOd == true){RFToynakOd = false;}
      if(FuXkyRpknu == true){FuXkyRpknu = false;}
      if(LhrfbRESQA == true){LhrfbRESQA = false;}
      if(nJjJPJhAum == true){nJjJPJhAum = false;}
      if(PjoLIPbXMf == true){PjoLIPbXMf = false;}
      if(TCIqojNnNg == true){TCIqojNnNg = false;}
      if(jHTNpuLNUo == true){jHTNpuLNUo = false;}
      if(jopBfbsfXM == true){jopBfbsfXM = false;}
      if(ofGjglBsUf == true){ofGjglBsUf = false;}
      if(utmOCIPbVM == true){utmOCIPbVM = false;}
      if(DODXudLHLN == true){DODXudLHLN = false;}
      if(qhPBqDBjgE == true){qhPBqDBjgE = false;}
      if(tRsnspCbyW == true){tRsnspCbyW = false;}
      if(LQJKIachoD == true){LQJKIachoD = false;}
      if(ZshGoNdlWz == true){ZshGoNdlWz = false;}
      if(GftRSkUOeF == true){GftRSkUOeF = false;}
      if(ajInBZXFrP == true){ajInBZXFrP = false;}
      if(aTtdeAjlzf == true){aTtdeAjlzf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GGMLHXZMQR
{ 
  void rEcdKuNyHK()
  { 
      bool tjrFYtuJuh = false;
      bool CDfQmfJSWg = false;
      bool UpOoWMWBAi = false;
      bool BdxlsSIDEp = false;
      bool eLuEunTlHP = false;
      bool zzcFAEVChM = false;
      bool XsILfXGsWT = false;
      bool WFOgCJtKti = false;
      bool rktjjBBqkn = false;
      bool wGUqSkDjXW = false;
      bool gZOmssjwDq = false;
      bool KKIzTmzXad = false;
      bool WOIhXQjWOQ = false;
      bool FJmWBSVHqp = false;
      bool RFntdkyVXf = false;
      bool leIsASRgPc = false;
      bool JMglkAXkxA = false;
      bool QrgkMQZNEl = false;
      bool SNzidZAtWi = false;
      bool BnqOgEXCJd = false;
      string iWatwkxFwD;
      string kuZEcyqwRM;
      string JHePcHuqIf;
      string MdmeGcjODW;
      string GUywrcLDRr;
      string ooERNbrLRo;
      string oFwQpHIuxz;
      string NcruFoJiWz;
      string urZPpXYURe;
      string kYxOhAXgFj;
      string UQFSeMwJMX;
      string SJnRsxfgaS;
      string imcSOnfdNE;
      string QbcmeelGkc;
      string aOIsLakeUj;
      string TqGlBgmmEp;
      string gSwHGpfAmO;
      string LZwxqTejHm;
      string DAJcjZVplx;
      string qzCtwISAlU;
      if(iWatwkxFwD == UQFSeMwJMX){tjrFYtuJuh = true;}
      else if(UQFSeMwJMX == iWatwkxFwD){gZOmssjwDq = true;}
      if(kuZEcyqwRM == SJnRsxfgaS){CDfQmfJSWg = true;}
      else if(SJnRsxfgaS == kuZEcyqwRM){KKIzTmzXad = true;}
      if(JHePcHuqIf == imcSOnfdNE){UpOoWMWBAi = true;}
      else if(imcSOnfdNE == JHePcHuqIf){WOIhXQjWOQ = true;}
      if(MdmeGcjODW == QbcmeelGkc){BdxlsSIDEp = true;}
      else if(QbcmeelGkc == MdmeGcjODW){FJmWBSVHqp = true;}
      if(GUywrcLDRr == aOIsLakeUj){eLuEunTlHP = true;}
      else if(aOIsLakeUj == GUywrcLDRr){RFntdkyVXf = true;}
      if(ooERNbrLRo == TqGlBgmmEp){zzcFAEVChM = true;}
      else if(TqGlBgmmEp == ooERNbrLRo){leIsASRgPc = true;}
      if(oFwQpHIuxz == gSwHGpfAmO){XsILfXGsWT = true;}
      else if(gSwHGpfAmO == oFwQpHIuxz){JMglkAXkxA = true;}
      if(NcruFoJiWz == LZwxqTejHm){WFOgCJtKti = true;}
      if(urZPpXYURe == DAJcjZVplx){rktjjBBqkn = true;}
      if(kYxOhAXgFj == qzCtwISAlU){wGUqSkDjXW = true;}
      while(LZwxqTejHm == NcruFoJiWz){QrgkMQZNEl = true;}
      while(DAJcjZVplx == DAJcjZVplx){SNzidZAtWi = true;}
      while(qzCtwISAlU == qzCtwISAlU){BnqOgEXCJd = true;}
      if(tjrFYtuJuh == true){tjrFYtuJuh = false;}
      if(CDfQmfJSWg == true){CDfQmfJSWg = false;}
      if(UpOoWMWBAi == true){UpOoWMWBAi = false;}
      if(BdxlsSIDEp == true){BdxlsSIDEp = false;}
      if(eLuEunTlHP == true){eLuEunTlHP = false;}
      if(zzcFAEVChM == true){zzcFAEVChM = false;}
      if(XsILfXGsWT == true){XsILfXGsWT = false;}
      if(WFOgCJtKti == true){WFOgCJtKti = false;}
      if(rktjjBBqkn == true){rktjjBBqkn = false;}
      if(wGUqSkDjXW == true){wGUqSkDjXW = false;}
      if(gZOmssjwDq == true){gZOmssjwDq = false;}
      if(KKIzTmzXad == true){KKIzTmzXad = false;}
      if(WOIhXQjWOQ == true){WOIhXQjWOQ = false;}
      if(FJmWBSVHqp == true){FJmWBSVHqp = false;}
      if(RFntdkyVXf == true){RFntdkyVXf = false;}
      if(leIsASRgPc == true){leIsASRgPc = false;}
      if(JMglkAXkxA == true){JMglkAXkxA = false;}
      if(QrgkMQZNEl == true){QrgkMQZNEl = false;}
      if(SNzidZAtWi == true){SNzidZAtWi = false;}
      if(BnqOgEXCJd == true){BnqOgEXCJd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SNOGMSNLEN
{ 
  void gyTYLAyLSn()
  { 
      bool DQKrGuPBGe = false;
      bool bxwkJhiSsH = false;
      bool KhDadoBeXi = false;
      bool iiHcANtCas = false;
      bool iHYlIomsGM = false;
      bool FIAIdUMjOR = false;
      bool tkdWusoTju = false;
      bool mfqzXCJRRn = false;
      bool BHXKdZhyye = false;
      bool AKmJyxdBpP = false;
      bool zTIKYYRBjb = false;
      bool KuRZPlMTrU = false;
      bool KpVEucrgAa = false;
      bool YHaBohzNkF = false;
      bool IgOVUErNtL = false;
      bool jJJVEIxDOw = false;
      bool fkAJCCUQkg = false;
      bool mzilMdbzjp = false;
      bool jelnpOyFxf = false;
      bool juynZWfFSR = false;
      string VbsiFXPzIw;
      string louurASFTk;
      string gVdjjNPqrJ;
      string KLLRJjWUXH;
      string xPUDClrbPi;
      string MNXlgzxJyr;
      string IYGykZddkH;
      string dxhLnRAahx;
      string UmaIxxnZkJ;
      string mNWezYIVRb;
      string INpIEOfMxO;
      string zWaAWUxyBn;
      string lEsbTQaCLP;
      string IdIGoGxRDi;
      string QbbVKQlVId;
      string aKUdoEUNnn;
      string mcAhFUNULP;
      string XetSWKcXRD;
      string eFthoyJeQk;
      string lidPunasPo;
      if(VbsiFXPzIw == INpIEOfMxO){DQKrGuPBGe = true;}
      else if(INpIEOfMxO == VbsiFXPzIw){zTIKYYRBjb = true;}
      if(louurASFTk == zWaAWUxyBn){bxwkJhiSsH = true;}
      else if(zWaAWUxyBn == louurASFTk){KuRZPlMTrU = true;}
      if(gVdjjNPqrJ == lEsbTQaCLP){KhDadoBeXi = true;}
      else if(lEsbTQaCLP == gVdjjNPqrJ){KpVEucrgAa = true;}
      if(KLLRJjWUXH == IdIGoGxRDi){iiHcANtCas = true;}
      else if(IdIGoGxRDi == KLLRJjWUXH){YHaBohzNkF = true;}
      if(xPUDClrbPi == QbbVKQlVId){iHYlIomsGM = true;}
      else if(QbbVKQlVId == xPUDClrbPi){IgOVUErNtL = true;}
      if(MNXlgzxJyr == aKUdoEUNnn){FIAIdUMjOR = true;}
      else if(aKUdoEUNnn == MNXlgzxJyr){jJJVEIxDOw = true;}
      if(IYGykZddkH == mcAhFUNULP){tkdWusoTju = true;}
      else if(mcAhFUNULP == IYGykZddkH){fkAJCCUQkg = true;}
      if(dxhLnRAahx == XetSWKcXRD){mfqzXCJRRn = true;}
      if(UmaIxxnZkJ == eFthoyJeQk){BHXKdZhyye = true;}
      if(mNWezYIVRb == lidPunasPo){AKmJyxdBpP = true;}
      while(XetSWKcXRD == dxhLnRAahx){mzilMdbzjp = true;}
      while(eFthoyJeQk == eFthoyJeQk){jelnpOyFxf = true;}
      while(lidPunasPo == lidPunasPo){juynZWfFSR = true;}
      if(DQKrGuPBGe == true){DQKrGuPBGe = false;}
      if(bxwkJhiSsH == true){bxwkJhiSsH = false;}
      if(KhDadoBeXi == true){KhDadoBeXi = false;}
      if(iiHcANtCas == true){iiHcANtCas = false;}
      if(iHYlIomsGM == true){iHYlIomsGM = false;}
      if(FIAIdUMjOR == true){FIAIdUMjOR = false;}
      if(tkdWusoTju == true){tkdWusoTju = false;}
      if(mfqzXCJRRn == true){mfqzXCJRRn = false;}
      if(BHXKdZhyye == true){BHXKdZhyye = false;}
      if(AKmJyxdBpP == true){AKmJyxdBpP = false;}
      if(zTIKYYRBjb == true){zTIKYYRBjb = false;}
      if(KuRZPlMTrU == true){KuRZPlMTrU = false;}
      if(KpVEucrgAa == true){KpVEucrgAa = false;}
      if(YHaBohzNkF == true){YHaBohzNkF = false;}
      if(IgOVUErNtL == true){IgOVUErNtL = false;}
      if(jJJVEIxDOw == true){jJJVEIxDOw = false;}
      if(fkAJCCUQkg == true){fkAJCCUQkg = false;}
      if(mzilMdbzjp == true){mzilMdbzjp = false;}
      if(jelnpOyFxf == true){jelnpOyFxf = false;}
      if(juynZWfFSR == true){juynZWfFSR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UZBSFRORKI
{ 
  void gCPOmaLblf()
  { 
      bool IdsyhwXAkh = false;
      bool FtPxKcGbkN = false;
      bool AEfNyQEHQx = false;
      bool cMRrzmLZdD = false;
      bool ORInOXqgTa = false;
      bool VIJPVExeAQ = false;
      bool qQimFrbWyX = false;
      bool RfyhyhurzZ = false;
      bool ZWmpbTDCWu = false;
      bool ofZNLyiUhV = false;
      bool wTiwJoKbQm = false;
      bool JFfZqTcsLk = false;
      bool oZAChkGjVA = false;
      bool yaJddFmpfl = false;
      bool JakiliAzVq = false;
      bool VpIxfVTfNX = false;
      bool hZGQnhuCwl = false;
      bool fmMZaOoQQz = false;
      bool kGOdeIRMxH = false;
      bool kGbHEjUTtD = false;
      string bwdbwRgasf;
      string yeeScTSPVO;
      string ZCyIZwsCCl;
      string VataUFVtmm;
      string gZjBGnVdsW;
      string luqxxYyUCz;
      string XdXHJWkEyX;
      string yXbhhzRwBl;
      string ZPIezaiwcu;
      string HArnOCCcrj;
      string DRfVYNSIPy;
      string HBTQYIVrHh;
      string nnaCPxfmTe;
      string xnDRhIjlGl;
      string HZfenGfaOG;
      string fJVKuOpcGb;
      string hfokASxChQ;
      string XjlVZNIwNI;
      string QEYMzmSsVT;
      string RGeeEbkudV;
      if(bwdbwRgasf == DRfVYNSIPy){IdsyhwXAkh = true;}
      else if(DRfVYNSIPy == bwdbwRgasf){wTiwJoKbQm = true;}
      if(yeeScTSPVO == HBTQYIVrHh){FtPxKcGbkN = true;}
      else if(HBTQYIVrHh == yeeScTSPVO){JFfZqTcsLk = true;}
      if(ZCyIZwsCCl == nnaCPxfmTe){AEfNyQEHQx = true;}
      else if(nnaCPxfmTe == ZCyIZwsCCl){oZAChkGjVA = true;}
      if(VataUFVtmm == xnDRhIjlGl){cMRrzmLZdD = true;}
      else if(xnDRhIjlGl == VataUFVtmm){yaJddFmpfl = true;}
      if(gZjBGnVdsW == HZfenGfaOG){ORInOXqgTa = true;}
      else if(HZfenGfaOG == gZjBGnVdsW){JakiliAzVq = true;}
      if(luqxxYyUCz == fJVKuOpcGb){VIJPVExeAQ = true;}
      else if(fJVKuOpcGb == luqxxYyUCz){VpIxfVTfNX = true;}
      if(XdXHJWkEyX == hfokASxChQ){qQimFrbWyX = true;}
      else if(hfokASxChQ == XdXHJWkEyX){hZGQnhuCwl = true;}
      if(yXbhhzRwBl == XjlVZNIwNI){RfyhyhurzZ = true;}
      if(ZPIezaiwcu == QEYMzmSsVT){ZWmpbTDCWu = true;}
      if(HArnOCCcrj == RGeeEbkudV){ofZNLyiUhV = true;}
      while(XjlVZNIwNI == yXbhhzRwBl){fmMZaOoQQz = true;}
      while(QEYMzmSsVT == QEYMzmSsVT){kGOdeIRMxH = true;}
      while(RGeeEbkudV == RGeeEbkudV){kGbHEjUTtD = true;}
      if(IdsyhwXAkh == true){IdsyhwXAkh = false;}
      if(FtPxKcGbkN == true){FtPxKcGbkN = false;}
      if(AEfNyQEHQx == true){AEfNyQEHQx = false;}
      if(cMRrzmLZdD == true){cMRrzmLZdD = false;}
      if(ORInOXqgTa == true){ORInOXqgTa = false;}
      if(VIJPVExeAQ == true){VIJPVExeAQ = false;}
      if(qQimFrbWyX == true){qQimFrbWyX = false;}
      if(RfyhyhurzZ == true){RfyhyhurzZ = false;}
      if(ZWmpbTDCWu == true){ZWmpbTDCWu = false;}
      if(ofZNLyiUhV == true){ofZNLyiUhV = false;}
      if(wTiwJoKbQm == true){wTiwJoKbQm = false;}
      if(JFfZqTcsLk == true){JFfZqTcsLk = false;}
      if(oZAChkGjVA == true){oZAChkGjVA = false;}
      if(yaJddFmpfl == true){yaJddFmpfl = false;}
      if(JakiliAzVq == true){JakiliAzVq = false;}
      if(VpIxfVTfNX == true){VpIxfVTfNX = false;}
      if(hZGQnhuCwl == true){hZGQnhuCwl = false;}
      if(fmMZaOoQQz == true){fmMZaOoQQz = false;}
      if(kGOdeIRMxH == true){kGOdeIRMxH = false;}
      if(kGbHEjUTtD == true){kGbHEjUTtD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENARKCCATT
{ 
  void jGfglROLIo()
  { 
      bool hQIbbAgpcZ = false;
      bool lERbIwneOA = false;
      bool GZSNQnPeTh = false;
      bool keTWmkkjdQ = false;
      bool nyWTewKTiL = false;
      bool xFCtxIyuKn = false;
      bool kCVtoGjuoW = false;
      bool LEAyMICzhU = false;
      bool cwuHkebZYd = false;
      bool moYpfkbbeX = false;
      bool LPdMAsEEgo = false;
      bool FzMpKnHOJJ = false;
      bool dKVKjVeKRa = false;
      bool faUKINRiGr = false;
      bool aWsjXmcifq = false;
      bool dNSUsBsSce = false;
      bool NsmFIeeChx = false;
      bool WXHRhGRlmw = false;
      bool rueaxSIzQH = false;
      bool TyFadhjmbs = false;
      string pSgOSSdQgc;
      string STHgDPQVrt;
      string znyGIMnBxl;
      string fWRNExEUkL;
      string uwnzgfsxgC;
      string RoQJzCUZFF;
      string ebTuwwCscF;
      string KujgyDzzZc;
      string TpUtTqFINC;
      string cdPegTcsCk;
      string czTaqVFjKw;
      string CVAclnGYaF;
      string ptfacffEze;
      string ZGwnzTWtCy;
      string lUxQzHdlss;
      string NESwtiSsxK;
      string pAkfWuYMdR;
      string RMWbTUwOaV;
      string CsLFRVnzsQ;
      string AcwqIkjRtE;
      if(pSgOSSdQgc == czTaqVFjKw){hQIbbAgpcZ = true;}
      else if(czTaqVFjKw == pSgOSSdQgc){LPdMAsEEgo = true;}
      if(STHgDPQVrt == CVAclnGYaF){lERbIwneOA = true;}
      else if(CVAclnGYaF == STHgDPQVrt){FzMpKnHOJJ = true;}
      if(znyGIMnBxl == ptfacffEze){GZSNQnPeTh = true;}
      else if(ptfacffEze == znyGIMnBxl){dKVKjVeKRa = true;}
      if(fWRNExEUkL == ZGwnzTWtCy){keTWmkkjdQ = true;}
      else if(ZGwnzTWtCy == fWRNExEUkL){faUKINRiGr = true;}
      if(uwnzgfsxgC == lUxQzHdlss){nyWTewKTiL = true;}
      else if(lUxQzHdlss == uwnzgfsxgC){aWsjXmcifq = true;}
      if(RoQJzCUZFF == NESwtiSsxK){xFCtxIyuKn = true;}
      else if(NESwtiSsxK == RoQJzCUZFF){dNSUsBsSce = true;}
      if(ebTuwwCscF == pAkfWuYMdR){kCVtoGjuoW = true;}
      else if(pAkfWuYMdR == ebTuwwCscF){NsmFIeeChx = true;}
      if(KujgyDzzZc == RMWbTUwOaV){LEAyMICzhU = true;}
      if(TpUtTqFINC == CsLFRVnzsQ){cwuHkebZYd = true;}
      if(cdPegTcsCk == AcwqIkjRtE){moYpfkbbeX = true;}
      while(RMWbTUwOaV == KujgyDzzZc){WXHRhGRlmw = true;}
      while(CsLFRVnzsQ == CsLFRVnzsQ){rueaxSIzQH = true;}
      while(AcwqIkjRtE == AcwqIkjRtE){TyFadhjmbs = true;}
      if(hQIbbAgpcZ == true){hQIbbAgpcZ = false;}
      if(lERbIwneOA == true){lERbIwneOA = false;}
      if(GZSNQnPeTh == true){GZSNQnPeTh = false;}
      if(keTWmkkjdQ == true){keTWmkkjdQ = false;}
      if(nyWTewKTiL == true){nyWTewKTiL = false;}
      if(xFCtxIyuKn == true){xFCtxIyuKn = false;}
      if(kCVtoGjuoW == true){kCVtoGjuoW = false;}
      if(LEAyMICzhU == true){LEAyMICzhU = false;}
      if(cwuHkebZYd == true){cwuHkebZYd = false;}
      if(moYpfkbbeX == true){moYpfkbbeX = false;}
      if(LPdMAsEEgo == true){LPdMAsEEgo = false;}
      if(FzMpKnHOJJ == true){FzMpKnHOJJ = false;}
      if(dKVKjVeKRa == true){dKVKjVeKRa = false;}
      if(faUKINRiGr == true){faUKINRiGr = false;}
      if(aWsjXmcifq == true){aWsjXmcifq = false;}
      if(dNSUsBsSce == true){dNSUsBsSce = false;}
      if(NsmFIeeChx == true){NsmFIeeChx = false;}
      if(WXHRhGRlmw == true){WXHRhGRlmw = false;}
      if(rueaxSIzQH == true){rueaxSIzQH = false;}
      if(TyFadhjmbs == true){TyFadhjmbs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XHTDKRWIWH
{ 
  void jzMBQIINxF()
  { 
      bool gMRINrjgHc = false;
      bool aOSEIDmfcC = false;
      bool ZoEcUYuUTp = false;
      bool YlqWGtxNHi = false;
      bool ypHKjYnbxG = false;
      bool xZOAarIomn = false;
      bool xPNQEoWuyO = false;
      bool GYXsDigssw = false;
      bool kTWNsyWqwN = false;
      bool lIZTlicpGu = false;
      bool BrcizXBUxq = false;
      bool KOupDdszXF = false;
      bool RfzjcyzEHU = false;
      bool GplytspmNV = false;
      bool wCtFDWMiPH = false;
      bool ocSBdVssGB = false;
      bool YxNbjUbxwJ = false;
      bool nFkCIOlsgF = false;
      bool kPnzedWkUY = false;
      bool AwfMwzoRVi = false;
      string iNbxVHOdMC;
      string utCNDekUBe;
      string HyKxAeTWhl;
      string shTBOpXGML;
      string MEtKHFrKfi;
      string TEHThjCdxq;
      string mruaIMaBzN;
      string GeIoRCDApt;
      string mJqySoZzSd;
      string ntIVYUITCt;
      string eqLRbowSCe;
      string gCnCEdAxHT;
      string lahUZMVmQw;
      string tjxuOwxYVc;
      string sHxmxlFGQt;
      string TLLhHEIprP;
      string SICFkxErnI;
      string fbadaddtXn;
      string HPVVbiXPnK;
      string mGfGJjFqCA;
      if(iNbxVHOdMC == eqLRbowSCe){gMRINrjgHc = true;}
      else if(eqLRbowSCe == iNbxVHOdMC){BrcizXBUxq = true;}
      if(utCNDekUBe == gCnCEdAxHT){aOSEIDmfcC = true;}
      else if(gCnCEdAxHT == utCNDekUBe){KOupDdszXF = true;}
      if(HyKxAeTWhl == lahUZMVmQw){ZoEcUYuUTp = true;}
      else if(lahUZMVmQw == HyKxAeTWhl){RfzjcyzEHU = true;}
      if(shTBOpXGML == tjxuOwxYVc){YlqWGtxNHi = true;}
      else if(tjxuOwxYVc == shTBOpXGML){GplytspmNV = true;}
      if(MEtKHFrKfi == sHxmxlFGQt){ypHKjYnbxG = true;}
      else if(sHxmxlFGQt == MEtKHFrKfi){wCtFDWMiPH = true;}
      if(TEHThjCdxq == TLLhHEIprP){xZOAarIomn = true;}
      else if(TLLhHEIprP == TEHThjCdxq){ocSBdVssGB = true;}
      if(mruaIMaBzN == SICFkxErnI){xPNQEoWuyO = true;}
      else if(SICFkxErnI == mruaIMaBzN){YxNbjUbxwJ = true;}
      if(GeIoRCDApt == fbadaddtXn){GYXsDigssw = true;}
      if(mJqySoZzSd == HPVVbiXPnK){kTWNsyWqwN = true;}
      if(ntIVYUITCt == mGfGJjFqCA){lIZTlicpGu = true;}
      while(fbadaddtXn == GeIoRCDApt){nFkCIOlsgF = true;}
      while(HPVVbiXPnK == HPVVbiXPnK){kPnzedWkUY = true;}
      while(mGfGJjFqCA == mGfGJjFqCA){AwfMwzoRVi = true;}
      if(gMRINrjgHc == true){gMRINrjgHc = false;}
      if(aOSEIDmfcC == true){aOSEIDmfcC = false;}
      if(ZoEcUYuUTp == true){ZoEcUYuUTp = false;}
      if(YlqWGtxNHi == true){YlqWGtxNHi = false;}
      if(ypHKjYnbxG == true){ypHKjYnbxG = false;}
      if(xZOAarIomn == true){xZOAarIomn = false;}
      if(xPNQEoWuyO == true){xPNQEoWuyO = false;}
      if(GYXsDigssw == true){GYXsDigssw = false;}
      if(kTWNsyWqwN == true){kTWNsyWqwN = false;}
      if(lIZTlicpGu == true){lIZTlicpGu = false;}
      if(BrcizXBUxq == true){BrcizXBUxq = false;}
      if(KOupDdszXF == true){KOupDdszXF = false;}
      if(RfzjcyzEHU == true){RfzjcyzEHU = false;}
      if(GplytspmNV == true){GplytspmNV = false;}
      if(wCtFDWMiPH == true){wCtFDWMiPH = false;}
      if(ocSBdVssGB == true){ocSBdVssGB = false;}
      if(YxNbjUbxwJ == true){YxNbjUbxwJ = false;}
      if(nFkCIOlsgF == true){nFkCIOlsgF = false;}
      if(kPnzedWkUY == true){kPnzedWkUY = false;}
      if(AwfMwzoRVi == true){AwfMwzoRVi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NDTJZBFULN
{ 
  void MlEfkqcTST()
  { 
      bool rFqOYDFqon = false;
      bool iJWcRJGUxD = false;
      bool NYoiBBELoB = false;
      bool wqzYbbrsdb = false;
      bool CwSQbuMyJc = false;
      bool uMrmeTQHMW = false;
      bool ztCmqqKxAp = false;
      bool QNpVARFYHF = false;
      bool oFBLGjyLsH = false;
      bool LkfHbIseYj = false;
      bool kOxTMhVWmN = false;
      bool OqAHgssqgH = false;
      bool ryEsdfgisr = false;
      bool XZzWUaIgzX = false;
      bool NbYfsTkYZi = false;
      bool PCyQrlKEpf = false;
      bool AmduonrclG = false;
      bool kLrItQZXAK = false;
      bool tIJJbVbidi = false;
      bool QDqSXZxdpE = false;
      string NHeeUNbRop;
      string aUFLGBrFaM;
      string uTJsTIjHqj;
      string LDIrxFCRtw;
      string IjhsWbHNrg;
      string nCOxZtylLM;
      string dTaEdWLMOB;
      string yZKdELkQVq;
      string AVPKuIoLSC;
      string HQFhRnJcOz;
      string QtzqhOrjrO;
      string IhQUMHEPJU;
      string hAtLshUcMP;
      string CHBVaFWYbg;
      string QESDtYAkUJ;
      string jsTsRPAnxA;
      string sOXcMBfttG;
      string kfmbEcgpRU;
      string hjHCfInHEK;
      string FiabmCgpqr;
      if(NHeeUNbRop == QtzqhOrjrO){rFqOYDFqon = true;}
      else if(QtzqhOrjrO == NHeeUNbRop){kOxTMhVWmN = true;}
      if(aUFLGBrFaM == IhQUMHEPJU){iJWcRJGUxD = true;}
      else if(IhQUMHEPJU == aUFLGBrFaM){OqAHgssqgH = true;}
      if(uTJsTIjHqj == hAtLshUcMP){NYoiBBELoB = true;}
      else if(hAtLshUcMP == uTJsTIjHqj){ryEsdfgisr = true;}
      if(LDIrxFCRtw == CHBVaFWYbg){wqzYbbrsdb = true;}
      else if(CHBVaFWYbg == LDIrxFCRtw){XZzWUaIgzX = true;}
      if(IjhsWbHNrg == QESDtYAkUJ){CwSQbuMyJc = true;}
      else if(QESDtYAkUJ == IjhsWbHNrg){NbYfsTkYZi = true;}
      if(nCOxZtylLM == jsTsRPAnxA){uMrmeTQHMW = true;}
      else if(jsTsRPAnxA == nCOxZtylLM){PCyQrlKEpf = true;}
      if(dTaEdWLMOB == sOXcMBfttG){ztCmqqKxAp = true;}
      else if(sOXcMBfttG == dTaEdWLMOB){AmduonrclG = true;}
      if(yZKdELkQVq == kfmbEcgpRU){QNpVARFYHF = true;}
      if(AVPKuIoLSC == hjHCfInHEK){oFBLGjyLsH = true;}
      if(HQFhRnJcOz == FiabmCgpqr){LkfHbIseYj = true;}
      while(kfmbEcgpRU == yZKdELkQVq){kLrItQZXAK = true;}
      while(hjHCfInHEK == hjHCfInHEK){tIJJbVbidi = true;}
      while(FiabmCgpqr == FiabmCgpqr){QDqSXZxdpE = true;}
      if(rFqOYDFqon == true){rFqOYDFqon = false;}
      if(iJWcRJGUxD == true){iJWcRJGUxD = false;}
      if(NYoiBBELoB == true){NYoiBBELoB = false;}
      if(wqzYbbrsdb == true){wqzYbbrsdb = false;}
      if(CwSQbuMyJc == true){CwSQbuMyJc = false;}
      if(uMrmeTQHMW == true){uMrmeTQHMW = false;}
      if(ztCmqqKxAp == true){ztCmqqKxAp = false;}
      if(QNpVARFYHF == true){QNpVARFYHF = false;}
      if(oFBLGjyLsH == true){oFBLGjyLsH = false;}
      if(LkfHbIseYj == true){LkfHbIseYj = false;}
      if(kOxTMhVWmN == true){kOxTMhVWmN = false;}
      if(OqAHgssqgH == true){OqAHgssqgH = false;}
      if(ryEsdfgisr == true){ryEsdfgisr = false;}
      if(XZzWUaIgzX == true){XZzWUaIgzX = false;}
      if(NbYfsTkYZi == true){NbYfsTkYZi = false;}
      if(PCyQrlKEpf == true){PCyQrlKEpf = false;}
      if(AmduonrclG == true){AmduonrclG = false;}
      if(kLrItQZXAK == true){kLrItQZXAK = false;}
      if(tIJJbVbidi == true){tIJJbVbidi = false;}
      if(QDqSXZxdpE == true){QDqSXZxdpE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBTLNRXYQV
{ 
  void CKhaGElEPY()
  { 
      bool cTcfOYDIqg = false;
      bool JttOlmFNmO = false;
      bool TDNYndjwol = false;
      bool ybDOBjawDi = false;
      bool UADlDxYObH = false;
      bool PpAtVYFDqj = false;
      bool nHSEhgpfMC = false;
      bool LIKEsTzaUq = false;
      bool FUUgWIbJsb = false;
      bool dWEStNgyDW = false;
      bool HrCYuHfwBB = false;
      bool YeiAeTmlhZ = false;
      bool FglkXoDqJf = false;
      bool lBWyjMSukP = false;
      bool beIqCynEna = false;
      bool auPdRaGQAG = false;
      bool DomVPXIjQR = false;
      bool ArASxZXuiZ = false;
      bool AzChFqksgJ = false;
      bool GCtdLmrmbd = false;
      string xwACDkuokR;
      string xImMqqjSlp;
      string uBzlOJfrfQ;
      string fMhIrRAbkf;
      string ZikuJBuqXj;
      string SEQHluxOms;
      string EDIUkjaeTZ;
      string pIgFQMQDcN;
      string OoTwxawZVw;
      string UloqaVZPJY;
      string ZPWysKXKpZ;
      string dskZePiMWK;
      string nAIXFESodt;
      string lBtEmyRVCm;
      string DkjwSbAOML;
      string lNrzjZGzro;
      string qhgumcyglf;
      string xNJjHDQMEd;
      string DEcSIYIuTN;
      string qScNuUEnIp;
      if(xwACDkuokR == ZPWysKXKpZ){cTcfOYDIqg = true;}
      else if(ZPWysKXKpZ == xwACDkuokR){HrCYuHfwBB = true;}
      if(xImMqqjSlp == dskZePiMWK){JttOlmFNmO = true;}
      else if(dskZePiMWK == xImMqqjSlp){YeiAeTmlhZ = true;}
      if(uBzlOJfrfQ == nAIXFESodt){TDNYndjwol = true;}
      else if(nAIXFESodt == uBzlOJfrfQ){FglkXoDqJf = true;}
      if(fMhIrRAbkf == lBtEmyRVCm){ybDOBjawDi = true;}
      else if(lBtEmyRVCm == fMhIrRAbkf){lBWyjMSukP = true;}
      if(ZikuJBuqXj == DkjwSbAOML){UADlDxYObH = true;}
      else if(DkjwSbAOML == ZikuJBuqXj){beIqCynEna = true;}
      if(SEQHluxOms == lNrzjZGzro){PpAtVYFDqj = true;}
      else if(lNrzjZGzro == SEQHluxOms){auPdRaGQAG = true;}
      if(EDIUkjaeTZ == qhgumcyglf){nHSEhgpfMC = true;}
      else if(qhgumcyglf == EDIUkjaeTZ){DomVPXIjQR = true;}
      if(pIgFQMQDcN == xNJjHDQMEd){LIKEsTzaUq = true;}
      if(OoTwxawZVw == DEcSIYIuTN){FUUgWIbJsb = true;}
      if(UloqaVZPJY == qScNuUEnIp){dWEStNgyDW = true;}
      while(xNJjHDQMEd == pIgFQMQDcN){ArASxZXuiZ = true;}
      while(DEcSIYIuTN == DEcSIYIuTN){AzChFqksgJ = true;}
      while(qScNuUEnIp == qScNuUEnIp){GCtdLmrmbd = true;}
      if(cTcfOYDIqg == true){cTcfOYDIqg = false;}
      if(JttOlmFNmO == true){JttOlmFNmO = false;}
      if(TDNYndjwol == true){TDNYndjwol = false;}
      if(ybDOBjawDi == true){ybDOBjawDi = false;}
      if(UADlDxYObH == true){UADlDxYObH = false;}
      if(PpAtVYFDqj == true){PpAtVYFDqj = false;}
      if(nHSEhgpfMC == true){nHSEhgpfMC = false;}
      if(LIKEsTzaUq == true){LIKEsTzaUq = false;}
      if(FUUgWIbJsb == true){FUUgWIbJsb = false;}
      if(dWEStNgyDW == true){dWEStNgyDW = false;}
      if(HrCYuHfwBB == true){HrCYuHfwBB = false;}
      if(YeiAeTmlhZ == true){YeiAeTmlhZ = false;}
      if(FglkXoDqJf == true){FglkXoDqJf = false;}
      if(lBWyjMSukP == true){lBWyjMSukP = false;}
      if(beIqCynEna == true){beIqCynEna = false;}
      if(auPdRaGQAG == true){auPdRaGQAG = false;}
      if(DomVPXIjQR == true){DomVPXIjQR = false;}
      if(ArASxZXuiZ == true){ArASxZXuiZ = false;}
      if(AzChFqksgJ == true){AzChFqksgJ = false;}
      if(GCtdLmrmbd == true){GCtdLmrmbd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LVFBHJZUZU
{ 
  void dpsJqtPYXF()
  { 
      bool DJLOzZWZwb = false;
      bool adgKxHMTcD = false;
      bool QzJeOuBuHh = false;
      bool THduAgTUfP = false;
      bool HYYyjNjLCi = false;
      bool IsTDCEAgzD = false;
      bool YbROHSAlJQ = false;
      bool nrnMwqaKtA = false;
      bool LprYYanZrw = false;
      bool flUbqfHJpQ = false;
      bool NyBluQEGHL = false;
      bool dolyrhisog = false;
      bool eatNjBWMVP = false;
      bool jQUcmMnGdI = false;
      bool VgRfSqzWiI = false;
      bool wOUJlmEnCs = false;
      bool trkqaMUILe = false;
      bool tcOfKxINtr = false;
      bool BzcMTVuLqz = false;
      bool IzDkOcuZFF = false;
      string DjjssIpVBr;
      string cKABlGMcIg;
      string ytBhaiXHad;
      string EfUDgwMzqZ;
      string nxWJymmPgQ;
      string glbzgJhBSJ;
      string jitXnxoxUp;
      string sNlisAWrjm;
      string wIaKwREVVW;
      string NKghoFCzVB;
      string yptpWTArGf;
      string mpReMbHjaV;
      string rSaybigDsm;
      string yWVhoGNjnc;
      string RLPpiXrBUN;
      string xSXAIeOwOm;
      string mwzShPUioG;
      string NWuyDgDkOE;
      string peifpezUZK;
      string qRVApVMwHT;
      if(DjjssIpVBr == yptpWTArGf){DJLOzZWZwb = true;}
      else if(yptpWTArGf == DjjssIpVBr){NyBluQEGHL = true;}
      if(cKABlGMcIg == mpReMbHjaV){adgKxHMTcD = true;}
      else if(mpReMbHjaV == cKABlGMcIg){dolyrhisog = true;}
      if(ytBhaiXHad == rSaybigDsm){QzJeOuBuHh = true;}
      else if(rSaybigDsm == ytBhaiXHad){eatNjBWMVP = true;}
      if(EfUDgwMzqZ == yWVhoGNjnc){THduAgTUfP = true;}
      else if(yWVhoGNjnc == EfUDgwMzqZ){jQUcmMnGdI = true;}
      if(nxWJymmPgQ == RLPpiXrBUN){HYYyjNjLCi = true;}
      else if(RLPpiXrBUN == nxWJymmPgQ){VgRfSqzWiI = true;}
      if(glbzgJhBSJ == xSXAIeOwOm){IsTDCEAgzD = true;}
      else if(xSXAIeOwOm == glbzgJhBSJ){wOUJlmEnCs = true;}
      if(jitXnxoxUp == mwzShPUioG){YbROHSAlJQ = true;}
      else if(mwzShPUioG == jitXnxoxUp){trkqaMUILe = true;}
      if(sNlisAWrjm == NWuyDgDkOE){nrnMwqaKtA = true;}
      if(wIaKwREVVW == peifpezUZK){LprYYanZrw = true;}
      if(NKghoFCzVB == qRVApVMwHT){flUbqfHJpQ = true;}
      while(NWuyDgDkOE == sNlisAWrjm){tcOfKxINtr = true;}
      while(peifpezUZK == peifpezUZK){BzcMTVuLqz = true;}
      while(qRVApVMwHT == qRVApVMwHT){IzDkOcuZFF = true;}
      if(DJLOzZWZwb == true){DJLOzZWZwb = false;}
      if(adgKxHMTcD == true){adgKxHMTcD = false;}
      if(QzJeOuBuHh == true){QzJeOuBuHh = false;}
      if(THduAgTUfP == true){THduAgTUfP = false;}
      if(HYYyjNjLCi == true){HYYyjNjLCi = false;}
      if(IsTDCEAgzD == true){IsTDCEAgzD = false;}
      if(YbROHSAlJQ == true){YbROHSAlJQ = false;}
      if(nrnMwqaKtA == true){nrnMwqaKtA = false;}
      if(LprYYanZrw == true){LprYYanZrw = false;}
      if(flUbqfHJpQ == true){flUbqfHJpQ = false;}
      if(NyBluQEGHL == true){NyBluQEGHL = false;}
      if(dolyrhisog == true){dolyrhisog = false;}
      if(eatNjBWMVP == true){eatNjBWMVP = false;}
      if(jQUcmMnGdI == true){jQUcmMnGdI = false;}
      if(VgRfSqzWiI == true){VgRfSqzWiI = false;}
      if(wOUJlmEnCs == true){wOUJlmEnCs = false;}
      if(trkqaMUILe == true){trkqaMUILe = false;}
      if(tcOfKxINtr == true){tcOfKxINtr = false;}
      if(BzcMTVuLqz == true){BzcMTVuLqz = false;}
      if(IzDkOcuZFF == true){IzDkOcuZFF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCFBUACTRD
{ 
  void WnJBhqwsup()
  { 
      bool EOuGkblMVP = false;
      bool JJFpTUnUQO = false;
      bool UwAwJKHynZ = false;
      bool heeDOkllMr = false;
      bool EKPloxdzeJ = false;
      bool QCBwBHNyxZ = false;
      bool TmXwheeBbh = false;
      bool iBIXKJfOHL = false;
      bool fITeIeciCG = false;
      bool XnolYQlTDJ = false;
      bool ScWwaOtckq = false;
      bool byplsKTsmC = false;
      bool BwzVKuMVzs = false;
      bool WMLysDkWEt = false;
      bool kAxKdYxCsN = false;
      bool wsfAHVcBlf = false;
      bool BXdrUOmqso = false;
      bool ZwosRBznqk = false;
      bool xJbkwdfKpW = false;
      bool ajkYsMVFpP = false;
      string zEESzKHJtC;
      string kUxAzOSpHE;
      string jRcoFQNtsq;
      string yCjxujGEdm;
      string kMhWArFaer;
      string mLPzBgaONi;
      string xNPDEhkAEO;
      string HOLTSWiFoM;
      string LlPBElljuN;
      string IqqupXxeSR;
      string HEWPjYzwfe;
      string xVZAXKxOyR;
      string uAFpGQWQcu;
      string ZEmXFGPzRf;
      string mpDPPmQpXf;
      string ZifAVGzfJS;
      string BhSkFsiCuQ;
      string tywSeFwoaS;
      string zgsxUpXlBy;
      string HjpydFXRKW;
      if(zEESzKHJtC == HEWPjYzwfe){EOuGkblMVP = true;}
      else if(HEWPjYzwfe == zEESzKHJtC){ScWwaOtckq = true;}
      if(kUxAzOSpHE == xVZAXKxOyR){JJFpTUnUQO = true;}
      else if(xVZAXKxOyR == kUxAzOSpHE){byplsKTsmC = true;}
      if(jRcoFQNtsq == uAFpGQWQcu){UwAwJKHynZ = true;}
      else if(uAFpGQWQcu == jRcoFQNtsq){BwzVKuMVzs = true;}
      if(yCjxujGEdm == ZEmXFGPzRf){heeDOkllMr = true;}
      else if(ZEmXFGPzRf == yCjxujGEdm){WMLysDkWEt = true;}
      if(kMhWArFaer == mpDPPmQpXf){EKPloxdzeJ = true;}
      else if(mpDPPmQpXf == kMhWArFaer){kAxKdYxCsN = true;}
      if(mLPzBgaONi == ZifAVGzfJS){QCBwBHNyxZ = true;}
      else if(ZifAVGzfJS == mLPzBgaONi){wsfAHVcBlf = true;}
      if(xNPDEhkAEO == BhSkFsiCuQ){TmXwheeBbh = true;}
      else if(BhSkFsiCuQ == xNPDEhkAEO){BXdrUOmqso = true;}
      if(HOLTSWiFoM == tywSeFwoaS){iBIXKJfOHL = true;}
      if(LlPBElljuN == zgsxUpXlBy){fITeIeciCG = true;}
      if(IqqupXxeSR == HjpydFXRKW){XnolYQlTDJ = true;}
      while(tywSeFwoaS == HOLTSWiFoM){ZwosRBznqk = true;}
      while(zgsxUpXlBy == zgsxUpXlBy){xJbkwdfKpW = true;}
      while(HjpydFXRKW == HjpydFXRKW){ajkYsMVFpP = true;}
      if(EOuGkblMVP == true){EOuGkblMVP = false;}
      if(JJFpTUnUQO == true){JJFpTUnUQO = false;}
      if(UwAwJKHynZ == true){UwAwJKHynZ = false;}
      if(heeDOkllMr == true){heeDOkllMr = false;}
      if(EKPloxdzeJ == true){EKPloxdzeJ = false;}
      if(QCBwBHNyxZ == true){QCBwBHNyxZ = false;}
      if(TmXwheeBbh == true){TmXwheeBbh = false;}
      if(iBIXKJfOHL == true){iBIXKJfOHL = false;}
      if(fITeIeciCG == true){fITeIeciCG = false;}
      if(XnolYQlTDJ == true){XnolYQlTDJ = false;}
      if(ScWwaOtckq == true){ScWwaOtckq = false;}
      if(byplsKTsmC == true){byplsKTsmC = false;}
      if(BwzVKuMVzs == true){BwzVKuMVzs = false;}
      if(WMLysDkWEt == true){WMLysDkWEt = false;}
      if(kAxKdYxCsN == true){kAxKdYxCsN = false;}
      if(wsfAHVcBlf == true){wsfAHVcBlf = false;}
      if(BXdrUOmqso == true){BXdrUOmqso = false;}
      if(ZwosRBznqk == true){ZwosRBznqk = false;}
      if(xJbkwdfKpW == true){xJbkwdfKpW = false;}
      if(ajkYsMVFpP == true){ajkYsMVFpP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PFUINDJPRR
{ 
  void kMRLkuzbht()
  { 
      bool kdDxSukXNX = false;
      bool RcIUYKLdfE = false;
      bool mJUmPJQYpe = false;
      bool iLntQMaYpS = false;
      bool TcWOJskBor = false;
      bool qANySbIPgI = false;
      bool dMgioGnOEM = false;
      bool immNkJlGcW = false;
      bool YOixmixpan = false;
      bool DKrhnGwnZD = false;
      bool FVxbJEMANI = false;
      bool oClKjPciuG = false;
      bool IymPIXuFYd = false;
      bool NyfZRCQGni = false;
      bool VxcRzBXhxY = false;
      bool cMrTtGihTk = false;
      bool JHaiupVMrg = false;
      bool yVtMjLVVPH = false;
      bool zNHzBBGMeK = false;
      bool TimDZNVtWI = false;
      string SWuplnQEOW;
      string iKCeOordMF;
      string upBYKqSmOx;
      string fRjBfbqNJA;
      string sdUFisaGpq;
      string RHfDDcVWfu;
      string UdoQqRaBzm;
      string xeTLMRVupR;
      string QLwXeXlfxC;
      string FTgOePoDOQ;
      string RYHDsmmTqk;
      string HagOeIgQlS;
      string etDwgcxFfw;
      string bSgYzqEsdr;
      string kRoMuelSjW;
      string iXQukXUKWP;
      string ogmtIntIPm;
      string EmmshNFqBB;
      string peVJNEBkmb;
      string WtWNDDdtDG;
      if(SWuplnQEOW == RYHDsmmTqk){kdDxSukXNX = true;}
      else if(RYHDsmmTqk == SWuplnQEOW){FVxbJEMANI = true;}
      if(iKCeOordMF == HagOeIgQlS){RcIUYKLdfE = true;}
      else if(HagOeIgQlS == iKCeOordMF){oClKjPciuG = true;}
      if(upBYKqSmOx == etDwgcxFfw){mJUmPJQYpe = true;}
      else if(etDwgcxFfw == upBYKqSmOx){IymPIXuFYd = true;}
      if(fRjBfbqNJA == bSgYzqEsdr){iLntQMaYpS = true;}
      else if(bSgYzqEsdr == fRjBfbqNJA){NyfZRCQGni = true;}
      if(sdUFisaGpq == kRoMuelSjW){TcWOJskBor = true;}
      else if(kRoMuelSjW == sdUFisaGpq){VxcRzBXhxY = true;}
      if(RHfDDcVWfu == iXQukXUKWP){qANySbIPgI = true;}
      else if(iXQukXUKWP == RHfDDcVWfu){cMrTtGihTk = true;}
      if(UdoQqRaBzm == ogmtIntIPm){dMgioGnOEM = true;}
      else if(ogmtIntIPm == UdoQqRaBzm){JHaiupVMrg = true;}
      if(xeTLMRVupR == EmmshNFqBB){immNkJlGcW = true;}
      if(QLwXeXlfxC == peVJNEBkmb){YOixmixpan = true;}
      if(FTgOePoDOQ == WtWNDDdtDG){DKrhnGwnZD = true;}
      while(EmmshNFqBB == xeTLMRVupR){yVtMjLVVPH = true;}
      while(peVJNEBkmb == peVJNEBkmb){zNHzBBGMeK = true;}
      while(WtWNDDdtDG == WtWNDDdtDG){TimDZNVtWI = true;}
      if(kdDxSukXNX == true){kdDxSukXNX = false;}
      if(RcIUYKLdfE == true){RcIUYKLdfE = false;}
      if(mJUmPJQYpe == true){mJUmPJQYpe = false;}
      if(iLntQMaYpS == true){iLntQMaYpS = false;}
      if(TcWOJskBor == true){TcWOJskBor = false;}
      if(qANySbIPgI == true){qANySbIPgI = false;}
      if(dMgioGnOEM == true){dMgioGnOEM = false;}
      if(immNkJlGcW == true){immNkJlGcW = false;}
      if(YOixmixpan == true){YOixmixpan = false;}
      if(DKrhnGwnZD == true){DKrhnGwnZD = false;}
      if(FVxbJEMANI == true){FVxbJEMANI = false;}
      if(oClKjPciuG == true){oClKjPciuG = false;}
      if(IymPIXuFYd == true){IymPIXuFYd = false;}
      if(NyfZRCQGni == true){NyfZRCQGni = false;}
      if(VxcRzBXhxY == true){VxcRzBXhxY = false;}
      if(cMrTtGihTk == true){cMrTtGihTk = false;}
      if(JHaiupVMrg == true){JHaiupVMrg = false;}
      if(yVtMjLVVPH == true){yVtMjLVVPH = false;}
      if(zNHzBBGMeK == true){zNHzBBGMeK = false;}
      if(TimDZNVtWI == true){TimDZNVtWI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OYDYPEKRYM
{ 
  void gOOFxfgrIJ()
  { 
      bool sUKAAfdloL = false;
      bool puLenlteDK = false;
      bool xPdbNmrkQt = false;
      bool hsJPQAoEiN = false;
      bool QsBQeobCTB = false;
      bool NHisGcphmN = false;
      bool nrVtcwkuNn = false;
      bool wouosDONwX = false;
      bool KoROfZJQJn = false;
      bool JHRVZYXGmi = false;
      bool EfnfFYLtzC = false;
      bool OclPCyaGOC = false;
      bool mUlZdoWZOU = false;
      bool eIZNTdBkIG = false;
      bool NPRGZgUCTb = false;
      bool xRqkuitOCQ = false;
      bool BleeWFDXwX = false;
      bool xoxHnWCeAx = false;
      bool TUFmWNQoRj = false;
      bool jlirFbjliT = false;
      string FiGYiEiPSl;
      string pXRGIORMuS;
      string fMKZINLRaT;
      string OmbLYLXMON;
      string SaUZJflMwy;
      string zCIwdrXfQV;
      string rRoyXDuFgx;
      string pExgAErjPb;
      string byVbUMdfhg;
      string mrwsVBkVCG;
      string kgezItEawY;
      string AnPnstwNdK;
      string YPWAJxIELz;
      string SWhJquSWSZ;
      string IDjJgzbHza;
      string FXqqgVJeoK;
      string lzPxFcGGxy;
      string aYtECVfNTK;
      string VAFjtufpbU;
      string kngImImlDD;
      if(FiGYiEiPSl == kgezItEawY){sUKAAfdloL = true;}
      else if(kgezItEawY == FiGYiEiPSl){EfnfFYLtzC = true;}
      if(pXRGIORMuS == AnPnstwNdK){puLenlteDK = true;}
      else if(AnPnstwNdK == pXRGIORMuS){OclPCyaGOC = true;}
      if(fMKZINLRaT == YPWAJxIELz){xPdbNmrkQt = true;}
      else if(YPWAJxIELz == fMKZINLRaT){mUlZdoWZOU = true;}
      if(OmbLYLXMON == SWhJquSWSZ){hsJPQAoEiN = true;}
      else if(SWhJquSWSZ == OmbLYLXMON){eIZNTdBkIG = true;}
      if(SaUZJflMwy == IDjJgzbHza){QsBQeobCTB = true;}
      else if(IDjJgzbHza == SaUZJflMwy){NPRGZgUCTb = true;}
      if(zCIwdrXfQV == FXqqgVJeoK){NHisGcphmN = true;}
      else if(FXqqgVJeoK == zCIwdrXfQV){xRqkuitOCQ = true;}
      if(rRoyXDuFgx == lzPxFcGGxy){nrVtcwkuNn = true;}
      else if(lzPxFcGGxy == rRoyXDuFgx){BleeWFDXwX = true;}
      if(pExgAErjPb == aYtECVfNTK){wouosDONwX = true;}
      if(byVbUMdfhg == VAFjtufpbU){KoROfZJQJn = true;}
      if(mrwsVBkVCG == kngImImlDD){JHRVZYXGmi = true;}
      while(aYtECVfNTK == pExgAErjPb){xoxHnWCeAx = true;}
      while(VAFjtufpbU == VAFjtufpbU){TUFmWNQoRj = true;}
      while(kngImImlDD == kngImImlDD){jlirFbjliT = true;}
      if(sUKAAfdloL == true){sUKAAfdloL = false;}
      if(puLenlteDK == true){puLenlteDK = false;}
      if(xPdbNmrkQt == true){xPdbNmrkQt = false;}
      if(hsJPQAoEiN == true){hsJPQAoEiN = false;}
      if(QsBQeobCTB == true){QsBQeobCTB = false;}
      if(NHisGcphmN == true){NHisGcphmN = false;}
      if(nrVtcwkuNn == true){nrVtcwkuNn = false;}
      if(wouosDONwX == true){wouosDONwX = false;}
      if(KoROfZJQJn == true){KoROfZJQJn = false;}
      if(JHRVZYXGmi == true){JHRVZYXGmi = false;}
      if(EfnfFYLtzC == true){EfnfFYLtzC = false;}
      if(OclPCyaGOC == true){OclPCyaGOC = false;}
      if(mUlZdoWZOU == true){mUlZdoWZOU = false;}
      if(eIZNTdBkIG == true){eIZNTdBkIG = false;}
      if(NPRGZgUCTb == true){NPRGZgUCTb = false;}
      if(xRqkuitOCQ == true){xRqkuitOCQ = false;}
      if(BleeWFDXwX == true){BleeWFDXwX = false;}
      if(xoxHnWCeAx == true){xoxHnWCeAx = false;}
      if(TUFmWNQoRj == true){TUFmWNQoRj = false;}
      if(jlirFbjliT == true){jlirFbjliT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XAEOVDIPXT
{ 
  void PRfeYcVMjO()
  { 
      bool MkiJLWWutg = false;
      bool RwNJePJonn = false;
      bool txADwDGNgG = false;
      bool VngcfcStml = false;
      bool wsSJDAuyAg = false;
      bool nlMtnOkfMH = false;
      bool QJOnLcOjcB = false;
      bool wOCBqAdpzu = false;
      bool HHMzRjalnR = false;
      bool rmheVmeeya = false;
      bool kKUzjYjLCn = false;
      bool jtfQzIwOVa = false;
      bool BcwLIJfWfE = false;
      bool UzqYJxmNPr = false;
      bool zPizgxHQeM = false;
      bool pPIXYIOJpa = false;
      bool rNeySkCGHC = false;
      bool VizcblswdK = false;
      bool BPqSNEqTAB = false;
      bool icWoAljkfw = false;
      string DgsVGNRGWN;
      string WTejINBymQ;
      string ebiIxchOen;
      string Rdnrptchiy;
      string MLyJoaDwiU;
      string xjBwLaxjXc;
      string fDbhwrflsO;
      string jTOoETdZTW;
      string ZkeJqgcqgP;
      string wsJGSJiPNw;
      string tQDUkcVLrq;
      string xXPBCtYSqO;
      string PnFdRqKHWt;
      string jNLXbIhKYO;
      string LQzoRYcIDX;
      string kQYyfGLYCs;
      string RNoxHiLrYt;
      string MNscDyoPLs;
      string OCEzJToNqU;
      string xIHfwxbBhi;
      if(DgsVGNRGWN == tQDUkcVLrq){MkiJLWWutg = true;}
      else if(tQDUkcVLrq == DgsVGNRGWN){kKUzjYjLCn = true;}
      if(WTejINBymQ == xXPBCtYSqO){RwNJePJonn = true;}
      else if(xXPBCtYSqO == WTejINBymQ){jtfQzIwOVa = true;}
      if(ebiIxchOen == PnFdRqKHWt){txADwDGNgG = true;}
      else if(PnFdRqKHWt == ebiIxchOen){BcwLIJfWfE = true;}
      if(Rdnrptchiy == jNLXbIhKYO){VngcfcStml = true;}
      else if(jNLXbIhKYO == Rdnrptchiy){UzqYJxmNPr = true;}
      if(MLyJoaDwiU == LQzoRYcIDX){wsSJDAuyAg = true;}
      else if(LQzoRYcIDX == MLyJoaDwiU){zPizgxHQeM = true;}
      if(xjBwLaxjXc == kQYyfGLYCs){nlMtnOkfMH = true;}
      else if(kQYyfGLYCs == xjBwLaxjXc){pPIXYIOJpa = true;}
      if(fDbhwrflsO == RNoxHiLrYt){QJOnLcOjcB = true;}
      else if(RNoxHiLrYt == fDbhwrflsO){rNeySkCGHC = true;}
      if(jTOoETdZTW == MNscDyoPLs){wOCBqAdpzu = true;}
      if(ZkeJqgcqgP == OCEzJToNqU){HHMzRjalnR = true;}
      if(wsJGSJiPNw == xIHfwxbBhi){rmheVmeeya = true;}
      while(MNscDyoPLs == jTOoETdZTW){VizcblswdK = true;}
      while(OCEzJToNqU == OCEzJToNqU){BPqSNEqTAB = true;}
      while(xIHfwxbBhi == xIHfwxbBhi){icWoAljkfw = true;}
      if(MkiJLWWutg == true){MkiJLWWutg = false;}
      if(RwNJePJonn == true){RwNJePJonn = false;}
      if(txADwDGNgG == true){txADwDGNgG = false;}
      if(VngcfcStml == true){VngcfcStml = false;}
      if(wsSJDAuyAg == true){wsSJDAuyAg = false;}
      if(nlMtnOkfMH == true){nlMtnOkfMH = false;}
      if(QJOnLcOjcB == true){QJOnLcOjcB = false;}
      if(wOCBqAdpzu == true){wOCBqAdpzu = false;}
      if(HHMzRjalnR == true){HHMzRjalnR = false;}
      if(rmheVmeeya == true){rmheVmeeya = false;}
      if(kKUzjYjLCn == true){kKUzjYjLCn = false;}
      if(jtfQzIwOVa == true){jtfQzIwOVa = false;}
      if(BcwLIJfWfE == true){BcwLIJfWfE = false;}
      if(UzqYJxmNPr == true){UzqYJxmNPr = false;}
      if(zPizgxHQeM == true){zPizgxHQeM = false;}
      if(pPIXYIOJpa == true){pPIXYIOJpa = false;}
      if(rNeySkCGHC == true){rNeySkCGHC = false;}
      if(VizcblswdK == true){VizcblswdK = false;}
      if(BPqSNEqTAB == true){BPqSNEqTAB = false;}
      if(icWoAljkfw == true){icWoAljkfw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LZNQCCEJRV
{ 
  void CrzSMdqYkc()
  { 
      bool WdceKBAyIu = false;
      bool ddWnmPGWiQ = false;
      bool UlwMzwnxSU = false;
      bool MFghRhxcVf = false;
      bool TYNWQBHfmk = false;
      bool FtfZkjhPfN = false;
      bool MDfmhYxnWE = false;
      bool ScACxwYZwx = false;
      bool oHJgPSZHxg = false;
      bool AhxHTPsZnr = false;
      bool ESJhSbscco = false;
      bool LHThYFsyXP = false;
      bool ypqpDjfsig = false;
      bool DzkDsWxaNn = false;
      bool YwdIVrOOiN = false;
      bool WtCYtNaTdi = false;
      bool uAtukLWPnC = false;
      bool HRjipCLhTL = false;
      bool VRJUKIxMJf = false;
      bool udxerYChWJ = false;
      string GCuXZAQStw;
      string YowAASfEZX;
      string NDXbchyPnq;
      string fiBtieQhOE;
      string QAhONkBNTI;
      string zWrOpDdStr;
      string CBdDQpmCQV;
      string CyoVGNUJOr;
      string fkufrIqmDf;
      string AxmWCPVexX;
      string yzwyFAhWHc;
      string hUECLQFxLH;
      string yzykUFKSSq;
      string rpLpsgoxaq;
      string aUeaxfrkKl;
      string JXSoYyBKcA;
      string oODQkrINIe;
      string aIWTgdTWno;
      string MZIghTWVRu;
      string fdUZBLQOpF;
      if(GCuXZAQStw == yzwyFAhWHc){WdceKBAyIu = true;}
      else if(yzwyFAhWHc == GCuXZAQStw){ESJhSbscco = true;}
      if(YowAASfEZX == hUECLQFxLH){ddWnmPGWiQ = true;}
      else if(hUECLQFxLH == YowAASfEZX){LHThYFsyXP = true;}
      if(NDXbchyPnq == yzykUFKSSq){UlwMzwnxSU = true;}
      else if(yzykUFKSSq == NDXbchyPnq){ypqpDjfsig = true;}
      if(fiBtieQhOE == rpLpsgoxaq){MFghRhxcVf = true;}
      else if(rpLpsgoxaq == fiBtieQhOE){DzkDsWxaNn = true;}
      if(QAhONkBNTI == aUeaxfrkKl){TYNWQBHfmk = true;}
      else if(aUeaxfrkKl == QAhONkBNTI){YwdIVrOOiN = true;}
      if(zWrOpDdStr == JXSoYyBKcA){FtfZkjhPfN = true;}
      else if(JXSoYyBKcA == zWrOpDdStr){WtCYtNaTdi = true;}
      if(CBdDQpmCQV == oODQkrINIe){MDfmhYxnWE = true;}
      else if(oODQkrINIe == CBdDQpmCQV){uAtukLWPnC = true;}
      if(CyoVGNUJOr == aIWTgdTWno){ScACxwYZwx = true;}
      if(fkufrIqmDf == MZIghTWVRu){oHJgPSZHxg = true;}
      if(AxmWCPVexX == fdUZBLQOpF){AhxHTPsZnr = true;}
      while(aIWTgdTWno == CyoVGNUJOr){HRjipCLhTL = true;}
      while(MZIghTWVRu == MZIghTWVRu){VRJUKIxMJf = true;}
      while(fdUZBLQOpF == fdUZBLQOpF){udxerYChWJ = true;}
      if(WdceKBAyIu == true){WdceKBAyIu = false;}
      if(ddWnmPGWiQ == true){ddWnmPGWiQ = false;}
      if(UlwMzwnxSU == true){UlwMzwnxSU = false;}
      if(MFghRhxcVf == true){MFghRhxcVf = false;}
      if(TYNWQBHfmk == true){TYNWQBHfmk = false;}
      if(FtfZkjhPfN == true){FtfZkjhPfN = false;}
      if(MDfmhYxnWE == true){MDfmhYxnWE = false;}
      if(ScACxwYZwx == true){ScACxwYZwx = false;}
      if(oHJgPSZHxg == true){oHJgPSZHxg = false;}
      if(AhxHTPsZnr == true){AhxHTPsZnr = false;}
      if(ESJhSbscco == true){ESJhSbscco = false;}
      if(LHThYFsyXP == true){LHThYFsyXP = false;}
      if(ypqpDjfsig == true){ypqpDjfsig = false;}
      if(DzkDsWxaNn == true){DzkDsWxaNn = false;}
      if(YwdIVrOOiN == true){YwdIVrOOiN = false;}
      if(WtCYtNaTdi == true){WtCYtNaTdi = false;}
      if(uAtukLWPnC == true){uAtukLWPnC = false;}
      if(HRjipCLhTL == true){HRjipCLhTL = false;}
      if(VRJUKIxMJf == true){VRJUKIxMJf = false;}
      if(udxerYChWJ == true){udxerYChWJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BUESPPLBGJ
{ 
  void VVKeGFoiZV()
  { 
      bool npxedtSBDI = false;
      bool kqdsPdAszz = false;
      bool cLksAAeskF = false;
      bool EVilyOXDDr = false;
      bool hocodQTZOI = false;
      bool YejxFcEDed = false;
      bool PZPxEOHqtB = false;
      bool GxoHQniwOj = false;
      bool gEdcfZlkgV = false;
      bool JTXZbHYekP = false;
      bool IbfNBbocfQ = false;
      bool tIouwLwmQd = false;
      bool cVKXrmZOeI = false;
      bool PDKzaEXPaE = false;
      bool jJFPbBeccQ = false;
      bool LkOHlmQHVO = false;
      bool BaxWBqypTq = false;
      bool mfMMsTQuwq = false;
      bool IwkNxeoDMn = false;
      bool mQtLCJLhNj = false;
      string jSkwKVKyAV;
      string OpFexmEjWL;
      string sCUTHtELZf;
      string QDZnTmMJon;
      string olDeWhQiKa;
      string UATmzhyQnP;
      string QzXUFKPRKJ;
      string auuhVGypwY;
      string dVAzKPjmol;
      string ouUYXpOiZM;
      string SzXBzYFkQr;
      string iIUOluyXJp;
      string abcYUeZVKe;
      string rPPjGdxzzl;
      string JyVwCgaFmb;
      string rqYikqWzfU;
      string zialATrjIH;
      string yyXXfbFfVm;
      string EUhhlBpfyP;
      string HxTemZXjwi;
      if(jSkwKVKyAV == SzXBzYFkQr){npxedtSBDI = true;}
      else if(SzXBzYFkQr == jSkwKVKyAV){IbfNBbocfQ = true;}
      if(OpFexmEjWL == iIUOluyXJp){kqdsPdAszz = true;}
      else if(iIUOluyXJp == OpFexmEjWL){tIouwLwmQd = true;}
      if(sCUTHtELZf == abcYUeZVKe){cLksAAeskF = true;}
      else if(abcYUeZVKe == sCUTHtELZf){cVKXrmZOeI = true;}
      if(QDZnTmMJon == rPPjGdxzzl){EVilyOXDDr = true;}
      else if(rPPjGdxzzl == QDZnTmMJon){PDKzaEXPaE = true;}
      if(olDeWhQiKa == JyVwCgaFmb){hocodQTZOI = true;}
      else if(JyVwCgaFmb == olDeWhQiKa){jJFPbBeccQ = true;}
      if(UATmzhyQnP == rqYikqWzfU){YejxFcEDed = true;}
      else if(rqYikqWzfU == UATmzhyQnP){LkOHlmQHVO = true;}
      if(QzXUFKPRKJ == zialATrjIH){PZPxEOHqtB = true;}
      else if(zialATrjIH == QzXUFKPRKJ){BaxWBqypTq = true;}
      if(auuhVGypwY == yyXXfbFfVm){GxoHQniwOj = true;}
      if(dVAzKPjmol == EUhhlBpfyP){gEdcfZlkgV = true;}
      if(ouUYXpOiZM == HxTemZXjwi){JTXZbHYekP = true;}
      while(yyXXfbFfVm == auuhVGypwY){mfMMsTQuwq = true;}
      while(EUhhlBpfyP == EUhhlBpfyP){IwkNxeoDMn = true;}
      while(HxTemZXjwi == HxTemZXjwi){mQtLCJLhNj = true;}
      if(npxedtSBDI == true){npxedtSBDI = false;}
      if(kqdsPdAszz == true){kqdsPdAszz = false;}
      if(cLksAAeskF == true){cLksAAeskF = false;}
      if(EVilyOXDDr == true){EVilyOXDDr = false;}
      if(hocodQTZOI == true){hocodQTZOI = false;}
      if(YejxFcEDed == true){YejxFcEDed = false;}
      if(PZPxEOHqtB == true){PZPxEOHqtB = false;}
      if(GxoHQniwOj == true){GxoHQniwOj = false;}
      if(gEdcfZlkgV == true){gEdcfZlkgV = false;}
      if(JTXZbHYekP == true){JTXZbHYekP = false;}
      if(IbfNBbocfQ == true){IbfNBbocfQ = false;}
      if(tIouwLwmQd == true){tIouwLwmQd = false;}
      if(cVKXrmZOeI == true){cVKXrmZOeI = false;}
      if(PDKzaEXPaE == true){PDKzaEXPaE = false;}
      if(jJFPbBeccQ == true){jJFPbBeccQ = false;}
      if(LkOHlmQHVO == true){LkOHlmQHVO = false;}
      if(BaxWBqypTq == true){BaxWBqypTq = false;}
      if(mfMMsTQuwq == true){mfMMsTQuwq = false;}
      if(IwkNxeoDMn == true){IwkNxeoDMn = false;}
      if(mQtLCJLhNj == true){mQtLCJLhNj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UYNVAGGXCA
{ 
  void rCSXeukUJh()
  { 
      bool CxalYAIoKw = false;
      bool oOgiUEjIhN = false;
      bool IIiCQVixVo = false;
      bool sNxzkVDSwo = false;
      bool RqDzrkXVdJ = false;
      bool uslUWsNXVD = false;
      bool RKTVDbRhxz = false;
      bool BQLswRFjKe = false;
      bool yMTLtzbbbr = false;
      bool HexsXGXhuQ = false;
      bool TpYdHdhsYF = false;
      bool mdNpEFqHaE = false;
      bool zoFFrWTSUo = false;
      bool sXntKInoEP = false;
      bool RiCWEdQGnS = false;
      bool PPGqQdjTlk = false;
      bool JPXiLPoTfw = false;
      bool RBDKmPlhAN = false;
      bool FNdCZcQxcg = false;
      bool XTDSGBLTLn = false;
      string ZdOddRWDmu;
      string EMSfbQnjWN;
      string OUulgczxxj;
      string mulbSYYxOJ;
      string duJedamXla;
      string OTNnmFhbwA;
      string SZGDIJZqND;
      string qpVNiTLQIG;
      string paKVVSgyoN;
      string pwBNqEoGVT;
      string AwKiiXxAES;
      string sRTpKqPjgp;
      string bbBzMuoIVe;
      string eEtnFtQamx;
      string UfsVTYcKCA;
      string oFYfrXtLVn;
      string iodYmoWejQ;
      string anwjUuhfem;
      string SdFVpZfNwh;
      string zEEzOeCUhe;
      if(ZdOddRWDmu == AwKiiXxAES){CxalYAIoKw = true;}
      else if(AwKiiXxAES == ZdOddRWDmu){TpYdHdhsYF = true;}
      if(EMSfbQnjWN == sRTpKqPjgp){oOgiUEjIhN = true;}
      else if(sRTpKqPjgp == EMSfbQnjWN){mdNpEFqHaE = true;}
      if(OUulgczxxj == bbBzMuoIVe){IIiCQVixVo = true;}
      else if(bbBzMuoIVe == OUulgczxxj){zoFFrWTSUo = true;}
      if(mulbSYYxOJ == eEtnFtQamx){sNxzkVDSwo = true;}
      else if(eEtnFtQamx == mulbSYYxOJ){sXntKInoEP = true;}
      if(duJedamXla == UfsVTYcKCA){RqDzrkXVdJ = true;}
      else if(UfsVTYcKCA == duJedamXla){RiCWEdQGnS = true;}
      if(OTNnmFhbwA == oFYfrXtLVn){uslUWsNXVD = true;}
      else if(oFYfrXtLVn == OTNnmFhbwA){PPGqQdjTlk = true;}
      if(SZGDIJZqND == iodYmoWejQ){RKTVDbRhxz = true;}
      else if(iodYmoWejQ == SZGDIJZqND){JPXiLPoTfw = true;}
      if(qpVNiTLQIG == anwjUuhfem){BQLswRFjKe = true;}
      if(paKVVSgyoN == SdFVpZfNwh){yMTLtzbbbr = true;}
      if(pwBNqEoGVT == zEEzOeCUhe){HexsXGXhuQ = true;}
      while(anwjUuhfem == qpVNiTLQIG){RBDKmPlhAN = true;}
      while(SdFVpZfNwh == SdFVpZfNwh){FNdCZcQxcg = true;}
      while(zEEzOeCUhe == zEEzOeCUhe){XTDSGBLTLn = true;}
      if(CxalYAIoKw == true){CxalYAIoKw = false;}
      if(oOgiUEjIhN == true){oOgiUEjIhN = false;}
      if(IIiCQVixVo == true){IIiCQVixVo = false;}
      if(sNxzkVDSwo == true){sNxzkVDSwo = false;}
      if(RqDzrkXVdJ == true){RqDzrkXVdJ = false;}
      if(uslUWsNXVD == true){uslUWsNXVD = false;}
      if(RKTVDbRhxz == true){RKTVDbRhxz = false;}
      if(BQLswRFjKe == true){BQLswRFjKe = false;}
      if(yMTLtzbbbr == true){yMTLtzbbbr = false;}
      if(HexsXGXhuQ == true){HexsXGXhuQ = false;}
      if(TpYdHdhsYF == true){TpYdHdhsYF = false;}
      if(mdNpEFqHaE == true){mdNpEFqHaE = false;}
      if(zoFFrWTSUo == true){zoFFrWTSUo = false;}
      if(sXntKInoEP == true){sXntKInoEP = false;}
      if(RiCWEdQGnS == true){RiCWEdQGnS = false;}
      if(PPGqQdjTlk == true){PPGqQdjTlk = false;}
      if(JPXiLPoTfw == true){JPXiLPoTfw = false;}
      if(RBDKmPlhAN == true){RBDKmPlhAN = false;}
      if(FNdCZcQxcg == true){FNdCZcQxcg = false;}
      if(XTDSGBLTLn == true){XTDSGBLTLn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EQHKPQRTJP
{ 
  void VOdnkfnQVB()
  { 
      bool VUkOLGPjHC = false;
      bool ESVuHzfsaq = false;
      bool jjusETmcWM = false;
      bool rChNiMxagA = false;
      bool JVkfFtYJXe = false;
      bool AGnmjkZrKr = false;
      bool TmMuJBjHMu = false;
      bool BFMahNzOnJ = false;
      bool tcErLlOucx = false;
      bool mFPngVJoVD = false;
      bool JQxccutNEW = false;
      bool lLEAyphUjX = false;
      bool moeOHwoXsL = false;
      bool EJrjAdfaOQ = false;
      bool rBpGKaBPpp = false;
      bool nnFyQUlhUg = false;
      bool FVTsRcSTAU = false;
      bool KGFSelyXDg = false;
      bool uZhDXPDsTe = false;
      bool qxGhLVgxoh = false;
      string LFJTOumcEA;
      string XnfRLJbqFG;
      string XfnxObkhFV;
      string ECiSbmUedy;
      string BYjtssymaM;
      string CHLtLfQMFm;
      string KEWhuUFNoY;
      string owNGEyusDU;
      string cxHsSxpnGu;
      string VIYpnxCCzY;
      string nkyCWFsFpM;
      string jXIjJNxdPx;
      string dQGsCgXWSH;
      string wstdgrzEVM;
      string DkytLyzngZ;
      string zXlBuWeEzp;
      string hWliPqcdDR;
      string OrICsrSMhE;
      string hiprHYGsiJ;
      string MtFfegzPdU;
      if(LFJTOumcEA == nkyCWFsFpM){VUkOLGPjHC = true;}
      else if(nkyCWFsFpM == LFJTOumcEA){JQxccutNEW = true;}
      if(XnfRLJbqFG == jXIjJNxdPx){ESVuHzfsaq = true;}
      else if(jXIjJNxdPx == XnfRLJbqFG){lLEAyphUjX = true;}
      if(XfnxObkhFV == dQGsCgXWSH){jjusETmcWM = true;}
      else if(dQGsCgXWSH == XfnxObkhFV){moeOHwoXsL = true;}
      if(ECiSbmUedy == wstdgrzEVM){rChNiMxagA = true;}
      else if(wstdgrzEVM == ECiSbmUedy){EJrjAdfaOQ = true;}
      if(BYjtssymaM == DkytLyzngZ){JVkfFtYJXe = true;}
      else if(DkytLyzngZ == BYjtssymaM){rBpGKaBPpp = true;}
      if(CHLtLfQMFm == zXlBuWeEzp){AGnmjkZrKr = true;}
      else if(zXlBuWeEzp == CHLtLfQMFm){nnFyQUlhUg = true;}
      if(KEWhuUFNoY == hWliPqcdDR){TmMuJBjHMu = true;}
      else if(hWliPqcdDR == KEWhuUFNoY){FVTsRcSTAU = true;}
      if(owNGEyusDU == OrICsrSMhE){BFMahNzOnJ = true;}
      if(cxHsSxpnGu == hiprHYGsiJ){tcErLlOucx = true;}
      if(VIYpnxCCzY == MtFfegzPdU){mFPngVJoVD = true;}
      while(OrICsrSMhE == owNGEyusDU){KGFSelyXDg = true;}
      while(hiprHYGsiJ == hiprHYGsiJ){uZhDXPDsTe = true;}
      while(MtFfegzPdU == MtFfegzPdU){qxGhLVgxoh = true;}
      if(VUkOLGPjHC == true){VUkOLGPjHC = false;}
      if(ESVuHzfsaq == true){ESVuHzfsaq = false;}
      if(jjusETmcWM == true){jjusETmcWM = false;}
      if(rChNiMxagA == true){rChNiMxagA = false;}
      if(JVkfFtYJXe == true){JVkfFtYJXe = false;}
      if(AGnmjkZrKr == true){AGnmjkZrKr = false;}
      if(TmMuJBjHMu == true){TmMuJBjHMu = false;}
      if(BFMahNzOnJ == true){BFMahNzOnJ = false;}
      if(tcErLlOucx == true){tcErLlOucx = false;}
      if(mFPngVJoVD == true){mFPngVJoVD = false;}
      if(JQxccutNEW == true){JQxccutNEW = false;}
      if(lLEAyphUjX == true){lLEAyphUjX = false;}
      if(moeOHwoXsL == true){moeOHwoXsL = false;}
      if(EJrjAdfaOQ == true){EJrjAdfaOQ = false;}
      if(rBpGKaBPpp == true){rBpGKaBPpp = false;}
      if(nnFyQUlhUg == true){nnFyQUlhUg = false;}
      if(FVTsRcSTAU == true){FVTsRcSTAU = false;}
      if(KGFSelyXDg == true){KGFSelyXDg = false;}
      if(uZhDXPDsTe == true){uZhDXPDsTe = false;}
      if(qxGhLVgxoh == true){qxGhLVgxoh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HXVALDOUNN
{ 
  void nOMJxrsNSF()
  { 
      bool zTRcFctVer = false;
      bool lWObaClAgY = false;
      bool ssYoBfZMdt = false;
      bool kxFDpEkrlb = false;
      bool tKAIqyRbaC = false;
      bool uJLNQFubaY = false;
      bool DgrkGoRKkV = false;
      bool RsOEehsQxD = false;
      bool Oylazbkqmj = false;
      bool JIRMYNSPBC = false;
      bool gGpEkCtGih = false;
      bool MeeXKFtQkd = false;
      bool DZXAMIbBfR = false;
      bool PcOuVIHhpw = false;
      bool heHEXddsCT = false;
      bool SCdWzGhoqb = false;
      bool ZrZRRiPiBC = false;
      bool xMZowXSTch = false;
      bool ehzMyMyrwO = false;
      bool ZRpOWoEpln = false;
      string RAEcHqlsmI;
      string zpBcSXhiaU;
      string cZXPAHslKq;
      string XxqulPxlGh;
      string EGrKnwOOjr;
      string oFtNhrbocz;
      string xAhujByGpD;
      string ZwbsPVgNaD;
      string reCSCSDcMt;
      string mHJGjEXwZl;
      string xIXgRrcByL;
      string KNOYGSyPrR;
      string yUswPSmUIL;
      string xjnoFjGUAK;
      string oCeBiZsjzQ;
      string GIEHnbOaRz;
      string FHrlNZZYSW;
      string LcOhbuprMp;
      string YCVqFoffAd;
      string UfDBEhJrmJ;
      if(RAEcHqlsmI == xIXgRrcByL){zTRcFctVer = true;}
      else if(xIXgRrcByL == RAEcHqlsmI){gGpEkCtGih = true;}
      if(zpBcSXhiaU == KNOYGSyPrR){lWObaClAgY = true;}
      else if(KNOYGSyPrR == zpBcSXhiaU){MeeXKFtQkd = true;}
      if(cZXPAHslKq == yUswPSmUIL){ssYoBfZMdt = true;}
      else if(yUswPSmUIL == cZXPAHslKq){DZXAMIbBfR = true;}
      if(XxqulPxlGh == xjnoFjGUAK){kxFDpEkrlb = true;}
      else if(xjnoFjGUAK == XxqulPxlGh){PcOuVIHhpw = true;}
      if(EGrKnwOOjr == oCeBiZsjzQ){tKAIqyRbaC = true;}
      else if(oCeBiZsjzQ == EGrKnwOOjr){heHEXddsCT = true;}
      if(oFtNhrbocz == GIEHnbOaRz){uJLNQFubaY = true;}
      else if(GIEHnbOaRz == oFtNhrbocz){SCdWzGhoqb = true;}
      if(xAhujByGpD == FHrlNZZYSW){DgrkGoRKkV = true;}
      else if(FHrlNZZYSW == xAhujByGpD){ZrZRRiPiBC = true;}
      if(ZwbsPVgNaD == LcOhbuprMp){RsOEehsQxD = true;}
      if(reCSCSDcMt == YCVqFoffAd){Oylazbkqmj = true;}
      if(mHJGjEXwZl == UfDBEhJrmJ){JIRMYNSPBC = true;}
      while(LcOhbuprMp == ZwbsPVgNaD){xMZowXSTch = true;}
      while(YCVqFoffAd == YCVqFoffAd){ehzMyMyrwO = true;}
      while(UfDBEhJrmJ == UfDBEhJrmJ){ZRpOWoEpln = true;}
      if(zTRcFctVer == true){zTRcFctVer = false;}
      if(lWObaClAgY == true){lWObaClAgY = false;}
      if(ssYoBfZMdt == true){ssYoBfZMdt = false;}
      if(kxFDpEkrlb == true){kxFDpEkrlb = false;}
      if(tKAIqyRbaC == true){tKAIqyRbaC = false;}
      if(uJLNQFubaY == true){uJLNQFubaY = false;}
      if(DgrkGoRKkV == true){DgrkGoRKkV = false;}
      if(RsOEehsQxD == true){RsOEehsQxD = false;}
      if(Oylazbkqmj == true){Oylazbkqmj = false;}
      if(JIRMYNSPBC == true){JIRMYNSPBC = false;}
      if(gGpEkCtGih == true){gGpEkCtGih = false;}
      if(MeeXKFtQkd == true){MeeXKFtQkd = false;}
      if(DZXAMIbBfR == true){DZXAMIbBfR = false;}
      if(PcOuVIHhpw == true){PcOuVIHhpw = false;}
      if(heHEXddsCT == true){heHEXddsCT = false;}
      if(SCdWzGhoqb == true){SCdWzGhoqb = false;}
      if(ZrZRRiPiBC == true){ZrZRRiPiBC = false;}
      if(xMZowXSTch == true){xMZowXSTch = false;}
      if(ehzMyMyrwO == true){ehzMyMyrwO = false;}
      if(ZRpOWoEpln == true){ZRpOWoEpln = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DKPVINERJN
{ 
  void mmUQpPoGip()
  { 
      bool BUTukrOBTa = false;
      bool yZcsSNsijk = false;
      bool FiUWgrEJiT = false;
      bool PfyZNclqhQ = false;
      bool txyXCxLGFd = false;
      bool TfVrlSzxOr = false;
      bool nFRzKSaDeo = false;
      bool bCASqHkwUi = false;
      bool fxEFAjKGmu = false;
      bool cocpbnezNj = false;
      bool WIaPCReCBd = false;
      bool hCceLpAMzZ = false;
      bool ITPjMlZJpC = false;
      bool clijMXVoDi = false;
      bool FHFJNZMxek = false;
      bool mRAmaCsqCP = false;
      bool qULyAuTrRm = false;
      bool TLJPUAOFVl = false;
      bool ZbeEOKluIK = false;
      bool eelmqjuGIR = false;
      string sZyWzytyVY;
      string TwOncxUmMT;
      string uXJPHxpzpD;
      string mPNrxmxRbq;
      string EYhOGCXyPB;
      string WcJPVVPhOB;
      string IuISlDiVpo;
      string ACLUPVpuIF;
      string ZqinfKGyWb;
      string WODZiIQObD;
      string TBIaBTQnzz;
      string fTZJbQMTma;
      string xjzNRlzklG;
      string FaSFkXiImL;
      string sRyWwCnsyS;
      string wwbBGjBtIP;
      string UfCstEBTYD;
      string gDgahekbRP;
      string xGlTJIzRzB;
      string WozXqNOFcq;
      if(sZyWzytyVY == TBIaBTQnzz){BUTukrOBTa = true;}
      else if(TBIaBTQnzz == sZyWzytyVY){WIaPCReCBd = true;}
      if(TwOncxUmMT == fTZJbQMTma){yZcsSNsijk = true;}
      else if(fTZJbQMTma == TwOncxUmMT){hCceLpAMzZ = true;}
      if(uXJPHxpzpD == xjzNRlzklG){FiUWgrEJiT = true;}
      else if(xjzNRlzklG == uXJPHxpzpD){ITPjMlZJpC = true;}
      if(mPNrxmxRbq == FaSFkXiImL){PfyZNclqhQ = true;}
      else if(FaSFkXiImL == mPNrxmxRbq){clijMXVoDi = true;}
      if(EYhOGCXyPB == sRyWwCnsyS){txyXCxLGFd = true;}
      else if(sRyWwCnsyS == EYhOGCXyPB){FHFJNZMxek = true;}
      if(WcJPVVPhOB == wwbBGjBtIP){TfVrlSzxOr = true;}
      else if(wwbBGjBtIP == WcJPVVPhOB){mRAmaCsqCP = true;}
      if(IuISlDiVpo == UfCstEBTYD){nFRzKSaDeo = true;}
      else if(UfCstEBTYD == IuISlDiVpo){qULyAuTrRm = true;}
      if(ACLUPVpuIF == gDgahekbRP){bCASqHkwUi = true;}
      if(ZqinfKGyWb == xGlTJIzRzB){fxEFAjKGmu = true;}
      if(WODZiIQObD == WozXqNOFcq){cocpbnezNj = true;}
      while(gDgahekbRP == ACLUPVpuIF){TLJPUAOFVl = true;}
      while(xGlTJIzRzB == xGlTJIzRzB){ZbeEOKluIK = true;}
      while(WozXqNOFcq == WozXqNOFcq){eelmqjuGIR = true;}
      if(BUTukrOBTa == true){BUTukrOBTa = false;}
      if(yZcsSNsijk == true){yZcsSNsijk = false;}
      if(FiUWgrEJiT == true){FiUWgrEJiT = false;}
      if(PfyZNclqhQ == true){PfyZNclqhQ = false;}
      if(txyXCxLGFd == true){txyXCxLGFd = false;}
      if(TfVrlSzxOr == true){TfVrlSzxOr = false;}
      if(nFRzKSaDeo == true){nFRzKSaDeo = false;}
      if(bCASqHkwUi == true){bCASqHkwUi = false;}
      if(fxEFAjKGmu == true){fxEFAjKGmu = false;}
      if(cocpbnezNj == true){cocpbnezNj = false;}
      if(WIaPCReCBd == true){WIaPCReCBd = false;}
      if(hCceLpAMzZ == true){hCceLpAMzZ = false;}
      if(ITPjMlZJpC == true){ITPjMlZJpC = false;}
      if(clijMXVoDi == true){clijMXVoDi = false;}
      if(FHFJNZMxek == true){FHFJNZMxek = false;}
      if(mRAmaCsqCP == true){mRAmaCsqCP = false;}
      if(qULyAuTrRm == true){qULyAuTrRm = false;}
      if(TLJPUAOFVl == true){TLJPUAOFVl = false;}
      if(ZbeEOKluIK == true){ZbeEOKluIK = false;}
      if(eelmqjuGIR == true){eelmqjuGIR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZYNVMXDBHM
{ 
  void waWKbxIkYq()
  { 
      bool epHyYEzJTe = false;
      bool TdHxdqskRI = false;
      bool HNlNBYptME = false;
      bool nQDgjIfSto = false;
      bool xMPMYHncjD = false;
      bool OIpaTRDsxz = false;
      bool OFxOpDZaNU = false;
      bool KZpcLuxYos = false;
      bool kNJJofZbMS = false;
      bool ElVuarPBVU = false;
      bool gNOPrnRNPY = false;
      bool TeEDNAumYK = false;
      bool dyNuPYEuBT = false;
      bool ewDTLXytRB = false;
      bool OLLnyZgRga = false;
      bool wcbLqizTAS = false;
      bool jVLwsWajqp = false;
      bool BBVXuRlYwo = false;
      bool qlNaWCUqcc = false;
      bool XetyRrAPta = false;
      string ehdRyeVpjd;
      string XzqTNJjnkC;
      string BXttANIcFx;
      string UYJQfemZLx;
      string PqkTtbSSlS;
      string qpGNSGniRj;
      string WrklIzoZnh;
      string WKcnlJmaAY;
      string upplFeRwyZ;
      string pDHaZXFyKt;
      string lrdEwgMSaI;
      string SNisofCygd;
      string gsbOrSCCNO;
      string DnPFlCLlpY;
      string RzUoGcTOkt;
      string UHRfNsQPMc;
      string eJFLFexdGm;
      string UPHHMhYmIO;
      string zmQTtwWjrs;
      string kuZNtHsIja;
      if(ehdRyeVpjd == lrdEwgMSaI){epHyYEzJTe = true;}
      else if(lrdEwgMSaI == ehdRyeVpjd){gNOPrnRNPY = true;}
      if(XzqTNJjnkC == SNisofCygd){TdHxdqskRI = true;}
      else if(SNisofCygd == XzqTNJjnkC){TeEDNAumYK = true;}
      if(BXttANIcFx == gsbOrSCCNO){HNlNBYptME = true;}
      else if(gsbOrSCCNO == BXttANIcFx){dyNuPYEuBT = true;}
      if(UYJQfemZLx == DnPFlCLlpY){nQDgjIfSto = true;}
      else if(DnPFlCLlpY == UYJQfemZLx){ewDTLXytRB = true;}
      if(PqkTtbSSlS == RzUoGcTOkt){xMPMYHncjD = true;}
      else if(RzUoGcTOkt == PqkTtbSSlS){OLLnyZgRga = true;}
      if(qpGNSGniRj == UHRfNsQPMc){OIpaTRDsxz = true;}
      else if(UHRfNsQPMc == qpGNSGniRj){wcbLqizTAS = true;}
      if(WrklIzoZnh == eJFLFexdGm){OFxOpDZaNU = true;}
      else if(eJFLFexdGm == WrklIzoZnh){jVLwsWajqp = true;}
      if(WKcnlJmaAY == UPHHMhYmIO){KZpcLuxYos = true;}
      if(upplFeRwyZ == zmQTtwWjrs){kNJJofZbMS = true;}
      if(pDHaZXFyKt == kuZNtHsIja){ElVuarPBVU = true;}
      while(UPHHMhYmIO == WKcnlJmaAY){BBVXuRlYwo = true;}
      while(zmQTtwWjrs == zmQTtwWjrs){qlNaWCUqcc = true;}
      while(kuZNtHsIja == kuZNtHsIja){XetyRrAPta = true;}
      if(epHyYEzJTe == true){epHyYEzJTe = false;}
      if(TdHxdqskRI == true){TdHxdqskRI = false;}
      if(HNlNBYptME == true){HNlNBYptME = false;}
      if(nQDgjIfSto == true){nQDgjIfSto = false;}
      if(xMPMYHncjD == true){xMPMYHncjD = false;}
      if(OIpaTRDsxz == true){OIpaTRDsxz = false;}
      if(OFxOpDZaNU == true){OFxOpDZaNU = false;}
      if(KZpcLuxYos == true){KZpcLuxYos = false;}
      if(kNJJofZbMS == true){kNJJofZbMS = false;}
      if(ElVuarPBVU == true){ElVuarPBVU = false;}
      if(gNOPrnRNPY == true){gNOPrnRNPY = false;}
      if(TeEDNAumYK == true){TeEDNAumYK = false;}
      if(dyNuPYEuBT == true){dyNuPYEuBT = false;}
      if(ewDTLXytRB == true){ewDTLXytRB = false;}
      if(OLLnyZgRga == true){OLLnyZgRga = false;}
      if(wcbLqizTAS == true){wcbLqizTAS = false;}
      if(jVLwsWajqp == true){jVLwsWajqp = false;}
      if(BBVXuRlYwo == true){BBVXuRlYwo = false;}
      if(qlNaWCUqcc == true){qlNaWCUqcc = false;}
      if(XetyRrAPta == true){XetyRrAPta = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CDFRPUQHYR
{ 
  void DeHzcQGNct()
  { 
      bool aDlHETNhOu = false;
      bool lOjOnhgASb = false;
      bool VIXOQrfpKW = false;
      bool pHBNtmFqFu = false;
      bool DOuEBewpqR = false;
      bool pbGeYSeWqL = false;
      bool nXXqFdMWTB = false;
      bool bouWXHMTNl = false;
      bool upyrgNBWnb = false;
      bool HizsHfpDzW = false;
      bool RZVppBgiGR = false;
      bool FLJEQyYfKq = false;
      bool cohrssoBPr = false;
      bool QJUpUVTICf = false;
      bool gRQVWwZucJ = false;
      bool GKsHtbqcww = false;
      bool LeTOAwqSjt = false;
      bool dQceKLYMVx = false;
      bool TtXGkGPMur = false;
      bool dpLFTBxCVZ = false;
      string CmJwJkmGqJ;
      string lHJxaEFhao;
      string KWdqWiyaYV;
      string KuJFDkcYUN;
      string quAFKGkJnV;
      string nKKAJfIRZZ;
      string mMhUypyEtp;
      string afMNyOWYgP;
      string ynmDhAjJuX;
      string bKztadNfGT;
      string IgPytHxxBu;
      string JjjKbyZdlx;
      string FoIWNQgRlT;
      string BpRNHRYoJa;
      string DmHANrZoSc;
      string EisINTXrjd;
      string ZfKhsSRWCK;
      string YkUKtSgIIV;
      string przJPRxJzm;
      string sfEeAWcYGu;
      if(CmJwJkmGqJ == IgPytHxxBu){aDlHETNhOu = true;}
      else if(IgPytHxxBu == CmJwJkmGqJ){RZVppBgiGR = true;}
      if(lHJxaEFhao == JjjKbyZdlx){lOjOnhgASb = true;}
      else if(JjjKbyZdlx == lHJxaEFhao){FLJEQyYfKq = true;}
      if(KWdqWiyaYV == FoIWNQgRlT){VIXOQrfpKW = true;}
      else if(FoIWNQgRlT == KWdqWiyaYV){cohrssoBPr = true;}
      if(KuJFDkcYUN == BpRNHRYoJa){pHBNtmFqFu = true;}
      else if(BpRNHRYoJa == KuJFDkcYUN){QJUpUVTICf = true;}
      if(quAFKGkJnV == DmHANrZoSc){DOuEBewpqR = true;}
      else if(DmHANrZoSc == quAFKGkJnV){gRQVWwZucJ = true;}
      if(nKKAJfIRZZ == EisINTXrjd){pbGeYSeWqL = true;}
      else if(EisINTXrjd == nKKAJfIRZZ){GKsHtbqcww = true;}
      if(mMhUypyEtp == ZfKhsSRWCK){nXXqFdMWTB = true;}
      else if(ZfKhsSRWCK == mMhUypyEtp){LeTOAwqSjt = true;}
      if(afMNyOWYgP == YkUKtSgIIV){bouWXHMTNl = true;}
      if(ynmDhAjJuX == przJPRxJzm){upyrgNBWnb = true;}
      if(bKztadNfGT == sfEeAWcYGu){HizsHfpDzW = true;}
      while(YkUKtSgIIV == afMNyOWYgP){dQceKLYMVx = true;}
      while(przJPRxJzm == przJPRxJzm){TtXGkGPMur = true;}
      while(sfEeAWcYGu == sfEeAWcYGu){dpLFTBxCVZ = true;}
      if(aDlHETNhOu == true){aDlHETNhOu = false;}
      if(lOjOnhgASb == true){lOjOnhgASb = false;}
      if(VIXOQrfpKW == true){VIXOQrfpKW = false;}
      if(pHBNtmFqFu == true){pHBNtmFqFu = false;}
      if(DOuEBewpqR == true){DOuEBewpqR = false;}
      if(pbGeYSeWqL == true){pbGeYSeWqL = false;}
      if(nXXqFdMWTB == true){nXXqFdMWTB = false;}
      if(bouWXHMTNl == true){bouWXHMTNl = false;}
      if(upyrgNBWnb == true){upyrgNBWnb = false;}
      if(HizsHfpDzW == true){HizsHfpDzW = false;}
      if(RZVppBgiGR == true){RZVppBgiGR = false;}
      if(FLJEQyYfKq == true){FLJEQyYfKq = false;}
      if(cohrssoBPr == true){cohrssoBPr = false;}
      if(QJUpUVTICf == true){QJUpUVTICf = false;}
      if(gRQVWwZucJ == true){gRQVWwZucJ = false;}
      if(GKsHtbqcww == true){GKsHtbqcww = false;}
      if(LeTOAwqSjt == true){LeTOAwqSjt = false;}
      if(dQceKLYMVx == true){dQceKLYMVx = false;}
      if(TtXGkGPMur == true){TtXGkGPMur = false;}
      if(dpLFTBxCVZ == true){dpLFTBxCVZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class POQNOPCTOQ
{ 
  void hnJsNrHqpI()
  { 
      bool MPSFDBeaCM = false;
      bool tmqQnafRXK = false;
      bool bKfIFkpGUf = false;
      bool LzsLLZTJIZ = false;
      bool KFmWUIEXkZ = false;
      bool lulggBiKAR = false;
      bool LXFWBusfEO = false;
      bool GWIxAVXJmw = false;
      bool fSUusQMMdK = false;
      bool qJIqOmAPVZ = false;
      bool PYSWTPlngK = false;
      bool dZWDksCKck = false;
      bool hfBtXwNRiN = false;
      bool VHmNgHzyad = false;
      bool dYeSfRmEFV = false;
      bool joljqiWXzW = false;
      bool BUFToWlJWd = false;
      bool sEizHJBiOG = false;
      bool JIMNcfUDVx = false;
      bool kayEcJSLcJ = false;
      string XuWcxdlfpd;
      string wCVloUWSkz;
      string hcBJwDmXrC;
      string pOTuyyfNVP;
      string CjTzkGejRn;
      string zMwDAusMgt;
      string qNnmnhianp;
      string oJwUwxJCYp;
      string YCFDDcRQuC;
      string ETgbYnwfLC;
      string WEwazpPaGC;
      string lqmpUnIkiK;
      string QSeklVcUwH;
      string BcpWSUGdDN;
      string MqJsQNfpGj;
      string fLwAlDYKod;
      string MudzAIAQXA;
      string gegVxYJlTY;
      string olOMaogpjP;
      string uunZARMJrI;
      if(XuWcxdlfpd == WEwazpPaGC){MPSFDBeaCM = true;}
      else if(WEwazpPaGC == XuWcxdlfpd){PYSWTPlngK = true;}
      if(wCVloUWSkz == lqmpUnIkiK){tmqQnafRXK = true;}
      else if(lqmpUnIkiK == wCVloUWSkz){dZWDksCKck = true;}
      if(hcBJwDmXrC == QSeklVcUwH){bKfIFkpGUf = true;}
      else if(QSeklVcUwH == hcBJwDmXrC){hfBtXwNRiN = true;}
      if(pOTuyyfNVP == BcpWSUGdDN){LzsLLZTJIZ = true;}
      else if(BcpWSUGdDN == pOTuyyfNVP){VHmNgHzyad = true;}
      if(CjTzkGejRn == MqJsQNfpGj){KFmWUIEXkZ = true;}
      else if(MqJsQNfpGj == CjTzkGejRn){dYeSfRmEFV = true;}
      if(zMwDAusMgt == fLwAlDYKod){lulggBiKAR = true;}
      else if(fLwAlDYKod == zMwDAusMgt){joljqiWXzW = true;}
      if(qNnmnhianp == MudzAIAQXA){LXFWBusfEO = true;}
      else if(MudzAIAQXA == qNnmnhianp){BUFToWlJWd = true;}
      if(oJwUwxJCYp == gegVxYJlTY){GWIxAVXJmw = true;}
      if(YCFDDcRQuC == olOMaogpjP){fSUusQMMdK = true;}
      if(ETgbYnwfLC == uunZARMJrI){qJIqOmAPVZ = true;}
      while(gegVxYJlTY == oJwUwxJCYp){sEizHJBiOG = true;}
      while(olOMaogpjP == olOMaogpjP){JIMNcfUDVx = true;}
      while(uunZARMJrI == uunZARMJrI){kayEcJSLcJ = true;}
      if(MPSFDBeaCM == true){MPSFDBeaCM = false;}
      if(tmqQnafRXK == true){tmqQnafRXK = false;}
      if(bKfIFkpGUf == true){bKfIFkpGUf = false;}
      if(LzsLLZTJIZ == true){LzsLLZTJIZ = false;}
      if(KFmWUIEXkZ == true){KFmWUIEXkZ = false;}
      if(lulggBiKAR == true){lulggBiKAR = false;}
      if(LXFWBusfEO == true){LXFWBusfEO = false;}
      if(GWIxAVXJmw == true){GWIxAVXJmw = false;}
      if(fSUusQMMdK == true){fSUusQMMdK = false;}
      if(qJIqOmAPVZ == true){qJIqOmAPVZ = false;}
      if(PYSWTPlngK == true){PYSWTPlngK = false;}
      if(dZWDksCKck == true){dZWDksCKck = false;}
      if(hfBtXwNRiN == true){hfBtXwNRiN = false;}
      if(VHmNgHzyad == true){VHmNgHzyad = false;}
      if(dYeSfRmEFV == true){dYeSfRmEFV = false;}
      if(joljqiWXzW == true){joljqiWXzW = false;}
      if(BUFToWlJWd == true){BUFToWlJWd = false;}
      if(sEizHJBiOG == true){sEizHJBiOG = false;}
      if(JIMNcfUDVx == true){JIMNcfUDVx = false;}
      if(kayEcJSLcJ == true){kayEcJSLcJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZRCAFLUVIZ
{ 
  void drAtoQRlcj()
  { 
      bool iVknEMpUaU = false;
      bool RMohTadZzk = false;
      bool FgSaJcBTVo = false;
      bool bzkIYbAoOs = false;
      bool AJVDUazDqD = false;
      bool tlSoUCDKea = false;
      bool LVyksSbgIr = false;
      bool anLFkuKOFi = false;
      bool cycStogwmW = false;
      bool XoKmhdKkKC = false;
      bool yStybGaMDZ = false;
      bool qnEuyNsfqD = false;
      bool kfslTlcYXG = false;
      bool jZDDjKDdpn = false;
      bool OTrMejjPoU = false;
      bool kesGQRYHep = false;
      bool dBoxoRjBKn = false;
      bool JOpCoQngHj = false;
      bool BMjCUFfwlS = false;
      bool kwzAKMetWN = false;
      string KXqRAoCtqi;
      string CggfGygQBh;
      string kMrdmrgAfI;
      string mQKZrHAMEJ;
      string PsxbpssELZ;
      string RiachyeMdI;
      string ICNiwkVGmy;
      string yTLqSrOQmt;
      string ycnFpDphrt;
      string bmiuBMeOfE;
      string XlQMbyXiKo;
      string jOZjJeNIsr;
      string unNsVKkPpF;
      string MAjhVMMbcr;
      string fGWCKNNzlW;
      string zVVmJiXXpR;
      string MHsFbjdqNx;
      string RlfAMoQLiI;
      string xkdSGqdxYm;
      string nokLeXMRZa;
      if(KXqRAoCtqi == XlQMbyXiKo){iVknEMpUaU = true;}
      else if(XlQMbyXiKo == KXqRAoCtqi){yStybGaMDZ = true;}
      if(CggfGygQBh == jOZjJeNIsr){RMohTadZzk = true;}
      else if(jOZjJeNIsr == CggfGygQBh){qnEuyNsfqD = true;}
      if(kMrdmrgAfI == unNsVKkPpF){FgSaJcBTVo = true;}
      else if(unNsVKkPpF == kMrdmrgAfI){kfslTlcYXG = true;}
      if(mQKZrHAMEJ == MAjhVMMbcr){bzkIYbAoOs = true;}
      else if(MAjhVMMbcr == mQKZrHAMEJ){jZDDjKDdpn = true;}
      if(PsxbpssELZ == fGWCKNNzlW){AJVDUazDqD = true;}
      else if(fGWCKNNzlW == PsxbpssELZ){OTrMejjPoU = true;}
      if(RiachyeMdI == zVVmJiXXpR){tlSoUCDKea = true;}
      else if(zVVmJiXXpR == RiachyeMdI){kesGQRYHep = true;}
      if(ICNiwkVGmy == MHsFbjdqNx){LVyksSbgIr = true;}
      else if(MHsFbjdqNx == ICNiwkVGmy){dBoxoRjBKn = true;}
      if(yTLqSrOQmt == RlfAMoQLiI){anLFkuKOFi = true;}
      if(ycnFpDphrt == xkdSGqdxYm){cycStogwmW = true;}
      if(bmiuBMeOfE == nokLeXMRZa){XoKmhdKkKC = true;}
      while(RlfAMoQLiI == yTLqSrOQmt){JOpCoQngHj = true;}
      while(xkdSGqdxYm == xkdSGqdxYm){BMjCUFfwlS = true;}
      while(nokLeXMRZa == nokLeXMRZa){kwzAKMetWN = true;}
      if(iVknEMpUaU == true){iVknEMpUaU = false;}
      if(RMohTadZzk == true){RMohTadZzk = false;}
      if(FgSaJcBTVo == true){FgSaJcBTVo = false;}
      if(bzkIYbAoOs == true){bzkIYbAoOs = false;}
      if(AJVDUazDqD == true){AJVDUazDqD = false;}
      if(tlSoUCDKea == true){tlSoUCDKea = false;}
      if(LVyksSbgIr == true){LVyksSbgIr = false;}
      if(anLFkuKOFi == true){anLFkuKOFi = false;}
      if(cycStogwmW == true){cycStogwmW = false;}
      if(XoKmhdKkKC == true){XoKmhdKkKC = false;}
      if(yStybGaMDZ == true){yStybGaMDZ = false;}
      if(qnEuyNsfqD == true){qnEuyNsfqD = false;}
      if(kfslTlcYXG == true){kfslTlcYXG = false;}
      if(jZDDjKDdpn == true){jZDDjKDdpn = false;}
      if(OTrMejjPoU == true){OTrMejjPoU = false;}
      if(kesGQRYHep == true){kesGQRYHep = false;}
      if(dBoxoRjBKn == true){dBoxoRjBKn = false;}
      if(JOpCoQngHj == true){JOpCoQngHj = false;}
      if(BMjCUFfwlS == true){BMjCUFfwlS = false;}
      if(kwzAKMetWN == true){kwzAKMetWN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JPLXVSEDVT
{ 
  void heipexRUyp()
  { 
      bool BSqNElfcRm = false;
      bool jYgenkGfMp = false;
      bool QfIIjrGaoQ = false;
      bool fsXcJKXuoz = false;
      bool nMhYbzjBxE = false;
      bool VLcihVJicM = false;
      bool fFnAHpBDUc = false;
      bool NLpMCDxifk = false;
      bool HEcjuUQotn = false;
      bool AoRcThYgQk = false;
      bool xgfTpKUPge = false;
      bool XZCqEacEFm = false;
      bool ZLIgbYsNsT = false;
      bool ePRumaYIsk = false;
      bool zAIPQalaXr = false;
      bool FUbdLlXzqR = false;
      bool QHVMAHHGDd = false;
      bool CTKUnYDrQB = false;
      bool lSpBNJnniB = false;
      bool DYQbTqeuPI = false;
      string abbnyEYPHL;
      string eEtostJlFl;
      string dqbLVtDJPW;
      string nppDtZxaey;
      string wHOToDtkDe;
      string HBowtizPRE;
      string BOzkXoOptT;
      string xhGGpVcHWS;
      string zRGjOlAsIL;
      string ZgJaxgIdwz;
      string nEqjhYtiGY;
      string FrsyEiIOVk;
      string nVghsQYeIJ;
      string NzLXduZWCp;
      string qRljFhmKWN;
      string XsIKKSWIpQ;
      string zPZxKGfUTJ;
      string JlMesWixbL;
      string cOItkUpAML;
      string YQfkpbqoYz;
      if(abbnyEYPHL == nEqjhYtiGY){BSqNElfcRm = true;}
      else if(nEqjhYtiGY == abbnyEYPHL){xgfTpKUPge = true;}
      if(eEtostJlFl == FrsyEiIOVk){jYgenkGfMp = true;}
      else if(FrsyEiIOVk == eEtostJlFl){XZCqEacEFm = true;}
      if(dqbLVtDJPW == nVghsQYeIJ){QfIIjrGaoQ = true;}
      else if(nVghsQYeIJ == dqbLVtDJPW){ZLIgbYsNsT = true;}
      if(nppDtZxaey == NzLXduZWCp){fsXcJKXuoz = true;}
      else if(NzLXduZWCp == nppDtZxaey){ePRumaYIsk = true;}
      if(wHOToDtkDe == qRljFhmKWN){nMhYbzjBxE = true;}
      else if(qRljFhmKWN == wHOToDtkDe){zAIPQalaXr = true;}
      if(HBowtizPRE == XsIKKSWIpQ){VLcihVJicM = true;}
      else if(XsIKKSWIpQ == HBowtizPRE){FUbdLlXzqR = true;}
      if(BOzkXoOptT == zPZxKGfUTJ){fFnAHpBDUc = true;}
      else if(zPZxKGfUTJ == BOzkXoOptT){QHVMAHHGDd = true;}
      if(xhGGpVcHWS == JlMesWixbL){NLpMCDxifk = true;}
      if(zRGjOlAsIL == cOItkUpAML){HEcjuUQotn = true;}
      if(ZgJaxgIdwz == YQfkpbqoYz){AoRcThYgQk = true;}
      while(JlMesWixbL == xhGGpVcHWS){CTKUnYDrQB = true;}
      while(cOItkUpAML == cOItkUpAML){lSpBNJnniB = true;}
      while(YQfkpbqoYz == YQfkpbqoYz){DYQbTqeuPI = true;}
      if(BSqNElfcRm == true){BSqNElfcRm = false;}
      if(jYgenkGfMp == true){jYgenkGfMp = false;}
      if(QfIIjrGaoQ == true){QfIIjrGaoQ = false;}
      if(fsXcJKXuoz == true){fsXcJKXuoz = false;}
      if(nMhYbzjBxE == true){nMhYbzjBxE = false;}
      if(VLcihVJicM == true){VLcihVJicM = false;}
      if(fFnAHpBDUc == true){fFnAHpBDUc = false;}
      if(NLpMCDxifk == true){NLpMCDxifk = false;}
      if(HEcjuUQotn == true){HEcjuUQotn = false;}
      if(AoRcThYgQk == true){AoRcThYgQk = false;}
      if(xgfTpKUPge == true){xgfTpKUPge = false;}
      if(XZCqEacEFm == true){XZCqEacEFm = false;}
      if(ZLIgbYsNsT == true){ZLIgbYsNsT = false;}
      if(ePRumaYIsk == true){ePRumaYIsk = false;}
      if(zAIPQalaXr == true){zAIPQalaXr = false;}
      if(FUbdLlXzqR == true){FUbdLlXzqR = false;}
      if(QHVMAHHGDd == true){QHVMAHHGDd = false;}
      if(CTKUnYDrQB == true){CTKUnYDrQB = false;}
      if(lSpBNJnniB == true){lSpBNJnniB = false;}
      if(DYQbTqeuPI == true){DYQbTqeuPI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TFUOOCHCXA
{ 
  void gjlcTOBWUk()
  { 
      bool MrWlejxNuR = false;
      bool lPaFyEMPDi = false;
      bool gdICtrlBYw = false;
      bool ZXMsPqmkYM = false;
      bool bTiqjCLxzT = false;
      bool MWNnShjUql = false;
      bool yunzqODgpH = false;
      bool RaqqGMuQRr = false;
      bool gnCFjDKYZh = false;
      bool GRslOgejzV = false;
      bool ydHqCkfWgF = false;
      bool mSCzFJsiOn = false;
      bool DeGHBzhEbZ = false;
      bool hKRwsCgKCy = false;
      bool XmqTtmPtfF = false;
      bool mwUKRTWzpC = false;
      bool CatGXbBFFD = false;
      bool cifPQPmlNN = false;
      bool inYWllpGeY = false;
      bool egTAwxsjwR = false;
      string MceRQxNfjI;
      string bsNhsQobQV;
      string TVfmPMfTqu;
      string PXroJVHSeK;
      string uSjnBijzCj;
      string oBlAfqwrCE;
      string QsnorEAXYW;
      string IVwGaAlqlf;
      string bfRHFNkrJS;
      string ZPQasCdtux;
      string iMZfaSFfZe;
      string EEFVbjbgjd;
      string SHNGxsEVMX;
      string WqwnxPFlfl;
      string IFSeNUJuyJ;
      string axKReayThh;
      string NjSBINIRXL;
      string dpAxVMoisb;
      string iJWDxYgeJV;
      string RlDyXYlRWz;
      if(MceRQxNfjI == iMZfaSFfZe){MrWlejxNuR = true;}
      else if(iMZfaSFfZe == MceRQxNfjI){ydHqCkfWgF = true;}
      if(bsNhsQobQV == EEFVbjbgjd){lPaFyEMPDi = true;}
      else if(EEFVbjbgjd == bsNhsQobQV){mSCzFJsiOn = true;}
      if(TVfmPMfTqu == SHNGxsEVMX){gdICtrlBYw = true;}
      else if(SHNGxsEVMX == TVfmPMfTqu){DeGHBzhEbZ = true;}
      if(PXroJVHSeK == WqwnxPFlfl){ZXMsPqmkYM = true;}
      else if(WqwnxPFlfl == PXroJVHSeK){hKRwsCgKCy = true;}
      if(uSjnBijzCj == IFSeNUJuyJ){bTiqjCLxzT = true;}
      else if(IFSeNUJuyJ == uSjnBijzCj){XmqTtmPtfF = true;}
      if(oBlAfqwrCE == axKReayThh){MWNnShjUql = true;}
      else if(axKReayThh == oBlAfqwrCE){mwUKRTWzpC = true;}
      if(QsnorEAXYW == NjSBINIRXL){yunzqODgpH = true;}
      else if(NjSBINIRXL == QsnorEAXYW){CatGXbBFFD = true;}
      if(IVwGaAlqlf == dpAxVMoisb){RaqqGMuQRr = true;}
      if(bfRHFNkrJS == iJWDxYgeJV){gnCFjDKYZh = true;}
      if(ZPQasCdtux == RlDyXYlRWz){GRslOgejzV = true;}
      while(dpAxVMoisb == IVwGaAlqlf){cifPQPmlNN = true;}
      while(iJWDxYgeJV == iJWDxYgeJV){inYWllpGeY = true;}
      while(RlDyXYlRWz == RlDyXYlRWz){egTAwxsjwR = true;}
      if(MrWlejxNuR == true){MrWlejxNuR = false;}
      if(lPaFyEMPDi == true){lPaFyEMPDi = false;}
      if(gdICtrlBYw == true){gdICtrlBYw = false;}
      if(ZXMsPqmkYM == true){ZXMsPqmkYM = false;}
      if(bTiqjCLxzT == true){bTiqjCLxzT = false;}
      if(MWNnShjUql == true){MWNnShjUql = false;}
      if(yunzqODgpH == true){yunzqODgpH = false;}
      if(RaqqGMuQRr == true){RaqqGMuQRr = false;}
      if(gnCFjDKYZh == true){gnCFjDKYZh = false;}
      if(GRslOgejzV == true){GRslOgejzV = false;}
      if(ydHqCkfWgF == true){ydHqCkfWgF = false;}
      if(mSCzFJsiOn == true){mSCzFJsiOn = false;}
      if(DeGHBzhEbZ == true){DeGHBzhEbZ = false;}
      if(hKRwsCgKCy == true){hKRwsCgKCy = false;}
      if(XmqTtmPtfF == true){XmqTtmPtfF = false;}
      if(mwUKRTWzpC == true){mwUKRTWzpC = false;}
      if(CatGXbBFFD == true){CatGXbBFFD = false;}
      if(cifPQPmlNN == true){cifPQPmlNN = false;}
      if(inYWllpGeY == true){inYWllpGeY = false;}
      if(egTAwxsjwR == true){egTAwxsjwR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SQSUZEJBVU
{ 
  void wBldAiCEqT()
  { 
      bool OKxfwfIhgQ = false;
      bool OIYYLZbjrn = false;
      bool SowXUGMhKW = false;
      bool plMsPLcCZJ = false;
      bool rNmzqjQMBa = false;
      bool LdDVCYOYKp = false;
      bool TaXKZcufIz = false;
      bool xZJiuFCwfj = false;
      bool pAgiKMiqqp = false;
      bool xDqipRpcYO = false;
      bool njDCdkTTZw = false;
      bool WRsaATtnzN = false;
      bool sEnSBtiZsc = false;
      bool PYWQuFwdFY = false;
      bool rOQtTfJQiV = false;
      bool XBdLUjwkAj = false;
      bool Ctawgytbeu = false;
      bool WPiZUemtyV = false;
      bool jSqWFNuLwL = false;
      bool JLdUWymTMV = false;
      string UnOsrdjYXO;
      string HCKdcKElnh;
      string MSFlEloBLJ;
      string WsOtpewwiG;
      string yKVrHuPZFn;
      string HnDjzBiboG;
      string nhNOqOnPny;
      string NHDgiCxMeI;
      string VPwWBipduo;
      string uTGcRQwHAs;
      string GzlGaAjVAw;
      string EVxfjYlqMI;
      string XKUyDsAaPS;
      string GoLkCWcouB;
      string yTczjYWars;
      string dEtqUwdmDh;
      string zJGhoOJMdM;
      string wxuLKEgVOd;
      string WZhWoBuUPG;
      string rokNBnNuJU;
      if(UnOsrdjYXO == GzlGaAjVAw){OKxfwfIhgQ = true;}
      else if(GzlGaAjVAw == UnOsrdjYXO){njDCdkTTZw = true;}
      if(HCKdcKElnh == EVxfjYlqMI){OIYYLZbjrn = true;}
      else if(EVxfjYlqMI == HCKdcKElnh){WRsaATtnzN = true;}
      if(MSFlEloBLJ == XKUyDsAaPS){SowXUGMhKW = true;}
      else if(XKUyDsAaPS == MSFlEloBLJ){sEnSBtiZsc = true;}
      if(WsOtpewwiG == GoLkCWcouB){plMsPLcCZJ = true;}
      else if(GoLkCWcouB == WsOtpewwiG){PYWQuFwdFY = true;}
      if(yKVrHuPZFn == yTczjYWars){rNmzqjQMBa = true;}
      else if(yTczjYWars == yKVrHuPZFn){rOQtTfJQiV = true;}
      if(HnDjzBiboG == dEtqUwdmDh){LdDVCYOYKp = true;}
      else if(dEtqUwdmDh == HnDjzBiboG){XBdLUjwkAj = true;}
      if(nhNOqOnPny == zJGhoOJMdM){TaXKZcufIz = true;}
      else if(zJGhoOJMdM == nhNOqOnPny){Ctawgytbeu = true;}
      if(NHDgiCxMeI == wxuLKEgVOd){xZJiuFCwfj = true;}
      if(VPwWBipduo == WZhWoBuUPG){pAgiKMiqqp = true;}
      if(uTGcRQwHAs == rokNBnNuJU){xDqipRpcYO = true;}
      while(wxuLKEgVOd == NHDgiCxMeI){WPiZUemtyV = true;}
      while(WZhWoBuUPG == WZhWoBuUPG){jSqWFNuLwL = true;}
      while(rokNBnNuJU == rokNBnNuJU){JLdUWymTMV = true;}
      if(OKxfwfIhgQ == true){OKxfwfIhgQ = false;}
      if(OIYYLZbjrn == true){OIYYLZbjrn = false;}
      if(SowXUGMhKW == true){SowXUGMhKW = false;}
      if(plMsPLcCZJ == true){plMsPLcCZJ = false;}
      if(rNmzqjQMBa == true){rNmzqjQMBa = false;}
      if(LdDVCYOYKp == true){LdDVCYOYKp = false;}
      if(TaXKZcufIz == true){TaXKZcufIz = false;}
      if(xZJiuFCwfj == true){xZJiuFCwfj = false;}
      if(pAgiKMiqqp == true){pAgiKMiqqp = false;}
      if(xDqipRpcYO == true){xDqipRpcYO = false;}
      if(njDCdkTTZw == true){njDCdkTTZw = false;}
      if(WRsaATtnzN == true){WRsaATtnzN = false;}
      if(sEnSBtiZsc == true){sEnSBtiZsc = false;}
      if(PYWQuFwdFY == true){PYWQuFwdFY = false;}
      if(rOQtTfJQiV == true){rOQtTfJQiV = false;}
      if(XBdLUjwkAj == true){XBdLUjwkAj = false;}
      if(Ctawgytbeu == true){Ctawgytbeu = false;}
      if(WPiZUemtyV == true){WPiZUemtyV = false;}
      if(jSqWFNuLwL == true){jSqWFNuLwL = false;}
      if(JLdUWymTMV == true){JLdUWymTMV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BEHDSWXFHO
{ 
  void wUVitYEoOR()
  { 
      bool hBNDCjndza = false;
      bool ZLtHuGLaJW = false;
      bool YxwGYpnDld = false;
      bool wlZjlFjtLq = false;
      bool BNXbcznnmF = false;
      bool mGDxBjEGeL = false;
      bool ukrVenkKVp = false;
      bool WRPSULZUcY = false;
      bool CAPfpoiciB = false;
      bool AcOAuQVBxo = false;
      bool NdSxiUqjbo = false;
      bool KjdFIuULeo = false;
      bool FIaTotCOWE = false;
      bool pXXmKYgRxU = false;
      bool xyAtqPzJqz = false;
      bool uJVHjFCyHo = false;
      bool SbMXylMpuj = false;
      bool NCNKqGIgcY = false;
      bool tsXXIgBPDF = false;
      bool WiJICVkbuE = false;
      string yIyWVupgxM;
      string YMrAEkVQhf;
      string hEVdpTjMOs;
      string WRlFVKZqpB;
      string GRtFOtUmrT;
      string DTMGttlUgB;
      string LcSDoHZmdt;
      string LeZfZQJQOu;
      string zxUtoCEeLb;
      string XFJopczpPH;
      string ThIxIYtfgd;
      string jVFkBNIXOl;
      string CubCVGUjpw;
      string QTAHbRnWkP;
      string IXxgqCzXmb;
      string UabcEXGFaC;
      string DJpkMQUyJj;
      string YklyddytLT;
      string GxxOapqWCD;
      string LiwiLzhMTa;
      if(yIyWVupgxM == ThIxIYtfgd){hBNDCjndza = true;}
      else if(ThIxIYtfgd == yIyWVupgxM){NdSxiUqjbo = true;}
      if(YMrAEkVQhf == jVFkBNIXOl){ZLtHuGLaJW = true;}
      else if(jVFkBNIXOl == YMrAEkVQhf){KjdFIuULeo = true;}
      if(hEVdpTjMOs == CubCVGUjpw){YxwGYpnDld = true;}
      else if(CubCVGUjpw == hEVdpTjMOs){FIaTotCOWE = true;}
      if(WRlFVKZqpB == QTAHbRnWkP){wlZjlFjtLq = true;}
      else if(QTAHbRnWkP == WRlFVKZqpB){pXXmKYgRxU = true;}
      if(GRtFOtUmrT == IXxgqCzXmb){BNXbcznnmF = true;}
      else if(IXxgqCzXmb == GRtFOtUmrT){xyAtqPzJqz = true;}
      if(DTMGttlUgB == UabcEXGFaC){mGDxBjEGeL = true;}
      else if(UabcEXGFaC == DTMGttlUgB){uJVHjFCyHo = true;}
      if(LcSDoHZmdt == DJpkMQUyJj){ukrVenkKVp = true;}
      else if(DJpkMQUyJj == LcSDoHZmdt){SbMXylMpuj = true;}
      if(LeZfZQJQOu == YklyddytLT){WRPSULZUcY = true;}
      if(zxUtoCEeLb == GxxOapqWCD){CAPfpoiciB = true;}
      if(XFJopczpPH == LiwiLzhMTa){AcOAuQVBxo = true;}
      while(YklyddytLT == LeZfZQJQOu){NCNKqGIgcY = true;}
      while(GxxOapqWCD == GxxOapqWCD){tsXXIgBPDF = true;}
      while(LiwiLzhMTa == LiwiLzhMTa){WiJICVkbuE = true;}
      if(hBNDCjndza == true){hBNDCjndza = false;}
      if(ZLtHuGLaJW == true){ZLtHuGLaJW = false;}
      if(YxwGYpnDld == true){YxwGYpnDld = false;}
      if(wlZjlFjtLq == true){wlZjlFjtLq = false;}
      if(BNXbcznnmF == true){BNXbcznnmF = false;}
      if(mGDxBjEGeL == true){mGDxBjEGeL = false;}
      if(ukrVenkKVp == true){ukrVenkKVp = false;}
      if(WRPSULZUcY == true){WRPSULZUcY = false;}
      if(CAPfpoiciB == true){CAPfpoiciB = false;}
      if(AcOAuQVBxo == true){AcOAuQVBxo = false;}
      if(NdSxiUqjbo == true){NdSxiUqjbo = false;}
      if(KjdFIuULeo == true){KjdFIuULeo = false;}
      if(FIaTotCOWE == true){FIaTotCOWE = false;}
      if(pXXmKYgRxU == true){pXXmKYgRxU = false;}
      if(xyAtqPzJqz == true){xyAtqPzJqz = false;}
      if(uJVHjFCyHo == true){uJVHjFCyHo = false;}
      if(SbMXylMpuj == true){SbMXylMpuj = false;}
      if(NCNKqGIgcY == true){NCNKqGIgcY = false;}
      if(tsXXIgBPDF == true){tsXXIgBPDF = false;}
      if(WiJICVkbuE == true){WiJICVkbuE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DDMODZMQVQ
{ 
  void nnmamRecaA()
  { 
      bool pCqMplGSAm = false;
      bool sehZjWDxln = false;
      bool qFnbSFTshG = false;
      bool XCBszqgUul = false;
      bool ChXgzLEbWy = false;
      bool bqAHjkNPtj = false;
      bool SNktPqcoar = false;
      bool oiCAlJgHbH = false;
      bool BrWjdfCtJO = false;
      bool dQaKSoxdRI = false;
      bool iPBeIsnAVa = false;
      bool DGnmiaqAPi = false;
      bool oieMNYHrgw = false;
      bool LDoSYkqqbj = false;
      bool rCXiKXcnaq = false;
      bool yxNiTzjnQi = false;
      bool kwSYOzQUNx = false;
      bool jzXfqmKwBo = false;
      bool uTQoyOpGzY = false;
      bool ACarywiyTK = false;
      string uIYcdbZClT;
      string VeordLuVXG;
      string LRMtlMHrwW;
      string FMHlPHSAQl;
      string dAEHqqXWyb;
      string aumTadweqR;
      string UhGPOIXCbW;
      string stEkcLMFCt;
      string nktTwJYmKl;
      string LnJzRwtosi;
      string SUtbifqBqP;
      string QpcwcinlSF;
      string ikrpKFkESg;
      string RXMTbSqSkP;
      string SWwtUULMWh;
      string IHVmzhcDQd;
      string ulhKysdIUJ;
      string rVACmMnyUp;
      string sYhkXJBYUs;
      string pmBHUfolwb;
      if(uIYcdbZClT == SUtbifqBqP){pCqMplGSAm = true;}
      else if(SUtbifqBqP == uIYcdbZClT){iPBeIsnAVa = true;}
      if(VeordLuVXG == QpcwcinlSF){sehZjWDxln = true;}
      else if(QpcwcinlSF == VeordLuVXG){DGnmiaqAPi = true;}
      if(LRMtlMHrwW == ikrpKFkESg){qFnbSFTshG = true;}
      else if(ikrpKFkESg == LRMtlMHrwW){oieMNYHrgw = true;}
      if(FMHlPHSAQl == RXMTbSqSkP){XCBszqgUul = true;}
      else if(RXMTbSqSkP == FMHlPHSAQl){LDoSYkqqbj = true;}
      if(dAEHqqXWyb == SWwtUULMWh){ChXgzLEbWy = true;}
      else if(SWwtUULMWh == dAEHqqXWyb){rCXiKXcnaq = true;}
      if(aumTadweqR == IHVmzhcDQd){bqAHjkNPtj = true;}
      else if(IHVmzhcDQd == aumTadweqR){yxNiTzjnQi = true;}
      if(UhGPOIXCbW == ulhKysdIUJ){SNktPqcoar = true;}
      else if(ulhKysdIUJ == UhGPOIXCbW){kwSYOzQUNx = true;}
      if(stEkcLMFCt == rVACmMnyUp){oiCAlJgHbH = true;}
      if(nktTwJYmKl == sYhkXJBYUs){BrWjdfCtJO = true;}
      if(LnJzRwtosi == pmBHUfolwb){dQaKSoxdRI = true;}
      while(rVACmMnyUp == stEkcLMFCt){jzXfqmKwBo = true;}
      while(sYhkXJBYUs == sYhkXJBYUs){uTQoyOpGzY = true;}
      while(pmBHUfolwb == pmBHUfolwb){ACarywiyTK = true;}
      if(pCqMplGSAm == true){pCqMplGSAm = false;}
      if(sehZjWDxln == true){sehZjWDxln = false;}
      if(qFnbSFTshG == true){qFnbSFTshG = false;}
      if(XCBszqgUul == true){XCBszqgUul = false;}
      if(ChXgzLEbWy == true){ChXgzLEbWy = false;}
      if(bqAHjkNPtj == true){bqAHjkNPtj = false;}
      if(SNktPqcoar == true){SNktPqcoar = false;}
      if(oiCAlJgHbH == true){oiCAlJgHbH = false;}
      if(BrWjdfCtJO == true){BrWjdfCtJO = false;}
      if(dQaKSoxdRI == true){dQaKSoxdRI = false;}
      if(iPBeIsnAVa == true){iPBeIsnAVa = false;}
      if(DGnmiaqAPi == true){DGnmiaqAPi = false;}
      if(oieMNYHrgw == true){oieMNYHrgw = false;}
      if(LDoSYkqqbj == true){LDoSYkqqbj = false;}
      if(rCXiKXcnaq == true){rCXiKXcnaq = false;}
      if(yxNiTzjnQi == true){yxNiTzjnQi = false;}
      if(kwSYOzQUNx == true){kwSYOzQUNx = false;}
      if(jzXfqmKwBo == true){jzXfqmKwBo = false;}
      if(uTQoyOpGzY == true){uTQoyOpGzY = false;}
      if(ACarywiyTK == true){ACarywiyTK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PWJBVUYOXN
{ 
  void tApxHkNSGk()
  { 
      bool hWoqpCbmPU = false;
      bool niiOLihWSL = false;
      bool uTILFNXggr = false;
      bool lJlGMWOkeh = false;
      bool XtioARCgiY = false;
      bool dyAhWONclb = false;
      bool etGWidxcBo = false;
      bool UwqknBjSLm = false;
      bool KqyIOmJEix = false;
      bool JlyCDcnLGV = false;
      bool UZetDgHPtV = false;
      bool duRyRmwxIu = false;
      bool TrsDehxogK = false;
      bool MYLoSjMEEg = false;
      bool ftKNSOUAkQ = false;
      bool gpDLBbgaOV = false;
      bool iSiiIFibfg = false;
      bool ZrsaPZhfjQ = false;
      bool NxEPcWUAnp = false;
      bool DloiyNLaEN = false;
      string JGISKZomUg;
      string BpizcTYDyj;
      string tzCSjXHDPF;
      string sPCatrmgHC;
      string gGbkhIHiqX;
      string aizQEKEpim;
      string SkWOmknHFk;
      string grwwDnWRja;
      string PXLrdKQkVj;
      string nwxUjuiMxx;
      string UAdGphmDMQ;
      string mmGHWtYdkc;
      string UCkVwjtaLI;
      string EJTmGPtFBu;
      string XMYFwBppyp;
      string WEbUbROIJG;
      string nLrELcSTAG;
      string zTcoEHdfYu;
      string tEcUkzhzKn;
      string BluuHMUTsS;
      if(JGISKZomUg == UAdGphmDMQ){hWoqpCbmPU = true;}
      else if(UAdGphmDMQ == JGISKZomUg){UZetDgHPtV = true;}
      if(BpizcTYDyj == mmGHWtYdkc){niiOLihWSL = true;}
      else if(mmGHWtYdkc == BpizcTYDyj){duRyRmwxIu = true;}
      if(tzCSjXHDPF == UCkVwjtaLI){uTILFNXggr = true;}
      else if(UCkVwjtaLI == tzCSjXHDPF){TrsDehxogK = true;}
      if(sPCatrmgHC == EJTmGPtFBu){lJlGMWOkeh = true;}
      else if(EJTmGPtFBu == sPCatrmgHC){MYLoSjMEEg = true;}
      if(gGbkhIHiqX == XMYFwBppyp){XtioARCgiY = true;}
      else if(XMYFwBppyp == gGbkhIHiqX){ftKNSOUAkQ = true;}
      if(aizQEKEpim == WEbUbROIJG){dyAhWONclb = true;}
      else if(WEbUbROIJG == aizQEKEpim){gpDLBbgaOV = true;}
      if(SkWOmknHFk == nLrELcSTAG){etGWidxcBo = true;}
      else if(nLrELcSTAG == SkWOmknHFk){iSiiIFibfg = true;}
      if(grwwDnWRja == zTcoEHdfYu){UwqknBjSLm = true;}
      if(PXLrdKQkVj == tEcUkzhzKn){KqyIOmJEix = true;}
      if(nwxUjuiMxx == BluuHMUTsS){JlyCDcnLGV = true;}
      while(zTcoEHdfYu == grwwDnWRja){ZrsaPZhfjQ = true;}
      while(tEcUkzhzKn == tEcUkzhzKn){NxEPcWUAnp = true;}
      while(BluuHMUTsS == BluuHMUTsS){DloiyNLaEN = true;}
      if(hWoqpCbmPU == true){hWoqpCbmPU = false;}
      if(niiOLihWSL == true){niiOLihWSL = false;}
      if(uTILFNXggr == true){uTILFNXggr = false;}
      if(lJlGMWOkeh == true){lJlGMWOkeh = false;}
      if(XtioARCgiY == true){XtioARCgiY = false;}
      if(dyAhWONclb == true){dyAhWONclb = false;}
      if(etGWidxcBo == true){etGWidxcBo = false;}
      if(UwqknBjSLm == true){UwqknBjSLm = false;}
      if(KqyIOmJEix == true){KqyIOmJEix = false;}
      if(JlyCDcnLGV == true){JlyCDcnLGV = false;}
      if(UZetDgHPtV == true){UZetDgHPtV = false;}
      if(duRyRmwxIu == true){duRyRmwxIu = false;}
      if(TrsDehxogK == true){TrsDehxogK = false;}
      if(MYLoSjMEEg == true){MYLoSjMEEg = false;}
      if(ftKNSOUAkQ == true){ftKNSOUAkQ = false;}
      if(gpDLBbgaOV == true){gpDLBbgaOV = false;}
      if(iSiiIFibfg == true){iSiiIFibfg = false;}
      if(ZrsaPZhfjQ == true){ZrsaPZhfjQ = false;}
      if(NxEPcWUAnp == true){NxEPcWUAnp = false;}
      if(DloiyNLaEN == true){DloiyNLaEN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NOXGGZDYXG
{ 
  void SCQRAMAQsY()
  { 
      bool kBZVLuclxh = false;
      bool TJzPYsoWIA = false;
      bool HAhxumyUNk = false;
      bool gVetDUYZQT = false;
      bool hRbxnFnFGm = false;
      bool pMWOLjSbZX = false;
      bool wHXMBxdFLD = false;
      bool TOGoSoXkIp = false;
      bool zrNatTzPiT = false;
      bool BwzsWasOwp = false;
      bool aitCSaGgwV = false;
      bool MhSjXEsxSg = false;
      bool yOWrCXOMRr = false;
      bool wIoSOQxLHT = false;
      bool NRTMGTcPUS = false;
      bool guwOrMMCAu = false;
      bool LsPEZErAVH = false;
      bool GhpzTftJkh = false;
      bool tzryKALZZB = false;
      bool DuKMHTCPmC = false;
      string YrBebKgMXx;
      string rBLWzXAPaS;
      string btteoJcJfL;
      string irrQFYeFbw;
      string fjKJAjSWeZ;
      string QCsmpeyWoS;
      string hXgMOAJuRZ;
      string sumdlqijdF;
      string pFdGtgzEZZ;
      string ZHQJOIDyuA;
      string aXEEfVPOBz;
      string uOrjcbsZRg;
      string BEUrAkdcOd;
      string njnddRAZZX;
      string RjDadLPfgm;
      string OcfNzVDMEt;
      string qlzXLLaNFK;
      string aTAtPQBtNo;
      string VywbOKDZeI;
      string OmVefejeOS;
      if(YrBebKgMXx == aXEEfVPOBz){kBZVLuclxh = true;}
      else if(aXEEfVPOBz == YrBebKgMXx){aitCSaGgwV = true;}
      if(rBLWzXAPaS == uOrjcbsZRg){TJzPYsoWIA = true;}
      else if(uOrjcbsZRg == rBLWzXAPaS){MhSjXEsxSg = true;}
      if(btteoJcJfL == BEUrAkdcOd){HAhxumyUNk = true;}
      else if(BEUrAkdcOd == btteoJcJfL){yOWrCXOMRr = true;}
      if(irrQFYeFbw == njnddRAZZX){gVetDUYZQT = true;}
      else if(njnddRAZZX == irrQFYeFbw){wIoSOQxLHT = true;}
      if(fjKJAjSWeZ == RjDadLPfgm){hRbxnFnFGm = true;}
      else if(RjDadLPfgm == fjKJAjSWeZ){NRTMGTcPUS = true;}
      if(QCsmpeyWoS == OcfNzVDMEt){pMWOLjSbZX = true;}
      else if(OcfNzVDMEt == QCsmpeyWoS){guwOrMMCAu = true;}
      if(hXgMOAJuRZ == qlzXLLaNFK){wHXMBxdFLD = true;}
      else if(qlzXLLaNFK == hXgMOAJuRZ){LsPEZErAVH = true;}
      if(sumdlqijdF == aTAtPQBtNo){TOGoSoXkIp = true;}
      if(pFdGtgzEZZ == VywbOKDZeI){zrNatTzPiT = true;}
      if(ZHQJOIDyuA == OmVefejeOS){BwzsWasOwp = true;}
      while(aTAtPQBtNo == sumdlqijdF){GhpzTftJkh = true;}
      while(VywbOKDZeI == VywbOKDZeI){tzryKALZZB = true;}
      while(OmVefejeOS == OmVefejeOS){DuKMHTCPmC = true;}
      if(kBZVLuclxh == true){kBZVLuclxh = false;}
      if(TJzPYsoWIA == true){TJzPYsoWIA = false;}
      if(HAhxumyUNk == true){HAhxumyUNk = false;}
      if(gVetDUYZQT == true){gVetDUYZQT = false;}
      if(hRbxnFnFGm == true){hRbxnFnFGm = false;}
      if(pMWOLjSbZX == true){pMWOLjSbZX = false;}
      if(wHXMBxdFLD == true){wHXMBxdFLD = false;}
      if(TOGoSoXkIp == true){TOGoSoXkIp = false;}
      if(zrNatTzPiT == true){zrNatTzPiT = false;}
      if(BwzsWasOwp == true){BwzsWasOwp = false;}
      if(aitCSaGgwV == true){aitCSaGgwV = false;}
      if(MhSjXEsxSg == true){MhSjXEsxSg = false;}
      if(yOWrCXOMRr == true){yOWrCXOMRr = false;}
      if(wIoSOQxLHT == true){wIoSOQxLHT = false;}
      if(NRTMGTcPUS == true){NRTMGTcPUS = false;}
      if(guwOrMMCAu == true){guwOrMMCAu = false;}
      if(LsPEZErAVH == true){LsPEZErAVH = false;}
      if(GhpzTftJkh == true){GhpzTftJkh = false;}
      if(tzryKALZZB == true){tzryKALZZB = false;}
      if(DuKMHTCPmC == true){DuKMHTCPmC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OHVQCYTLUW
{ 
  void yJLltTQkaB()
  { 
      bool jjKlZPDigu = false;
      bool QkVAOxUNcP = false;
      bool WnbpfgaHVT = false;
      bool sncOZyFwxw = false;
      bool DTqguiwGbm = false;
      bool cIdCPwITFr = false;
      bool ouMMCbHGaP = false;
      bool rYQfMCwuuw = false;
      bool jTfipkJZyc = false;
      bool okpEGIHdeS = false;
      bool bpeLuErypN = false;
      bool zNYJIVPdWQ = false;
      bool SgIyZGhLYE = false;
      bool tSPbUtoTml = false;
      bool rLjkcaMgwk = false;
      bool rcHNAuhgko = false;
      bool VfYlSgxwoN = false;
      bool fwpkXGxXUz = false;
      bool tBPmLRKCbY = false;
      bool MHhyPMmxRu = false;
      string tKhgRWYfrn;
      string pzCmlDGQnq;
      string ejpRbuHojw;
      string AeHurAyqJd;
      string hisEtyagEa;
      string GcqIZKUQEW;
      string PjuwnKrGul;
      string FPHKIuplXd;
      string UajJpWmyUg;
      string eglmOxmwPi;
      string GTkRVpVgAe;
      string ThrZBoAlGR;
      string WslOGXcTwK;
      string HtVnXBoRnz;
      string AGxoMwoMlY;
      string xBpyLMgWKx;
      string NCjpWZMEBA;
      string zhyHQPwwBJ;
      string iPhWMGDXcL;
      string TSHpkxVHSm;
      if(tKhgRWYfrn == GTkRVpVgAe){jjKlZPDigu = true;}
      else if(GTkRVpVgAe == tKhgRWYfrn){bpeLuErypN = true;}
      if(pzCmlDGQnq == ThrZBoAlGR){QkVAOxUNcP = true;}
      else if(ThrZBoAlGR == pzCmlDGQnq){zNYJIVPdWQ = true;}
      if(ejpRbuHojw == WslOGXcTwK){WnbpfgaHVT = true;}
      else if(WslOGXcTwK == ejpRbuHojw){SgIyZGhLYE = true;}
      if(AeHurAyqJd == HtVnXBoRnz){sncOZyFwxw = true;}
      else if(HtVnXBoRnz == AeHurAyqJd){tSPbUtoTml = true;}
      if(hisEtyagEa == AGxoMwoMlY){DTqguiwGbm = true;}
      else if(AGxoMwoMlY == hisEtyagEa){rLjkcaMgwk = true;}
      if(GcqIZKUQEW == xBpyLMgWKx){cIdCPwITFr = true;}
      else if(xBpyLMgWKx == GcqIZKUQEW){rcHNAuhgko = true;}
      if(PjuwnKrGul == NCjpWZMEBA){ouMMCbHGaP = true;}
      else if(NCjpWZMEBA == PjuwnKrGul){VfYlSgxwoN = true;}
      if(FPHKIuplXd == zhyHQPwwBJ){rYQfMCwuuw = true;}
      if(UajJpWmyUg == iPhWMGDXcL){jTfipkJZyc = true;}
      if(eglmOxmwPi == TSHpkxVHSm){okpEGIHdeS = true;}
      while(zhyHQPwwBJ == FPHKIuplXd){fwpkXGxXUz = true;}
      while(iPhWMGDXcL == iPhWMGDXcL){tBPmLRKCbY = true;}
      while(TSHpkxVHSm == TSHpkxVHSm){MHhyPMmxRu = true;}
      if(jjKlZPDigu == true){jjKlZPDigu = false;}
      if(QkVAOxUNcP == true){QkVAOxUNcP = false;}
      if(WnbpfgaHVT == true){WnbpfgaHVT = false;}
      if(sncOZyFwxw == true){sncOZyFwxw = false;}
      if(DTqguiwGbm == true){DTqguiwGbm = false;}
      if(cIdCPwITFr == true){cIdCPwITFr = false;}
      if(ouMMCbHGaP == true){ouMMCbHGaP = false;}
      if(rYQfMCwuuw == true){rYQfMCwuuw = false;}
      if(jTfipkJZyc == true){jTfipkJZyc = false;}
      if(okpEGIHdeS == true){okpEGIHdeS = false;}
      if(bpeLuErypN == true){bpeLuErypN = false;}
      if(zNYJIVPdWQ == true){zNYJIVPdWQ = false;}
      if(SgIyZGhLYE == true){SgIyZGhLYE = false;}
      if(tSPbUtoTml == true){tSPbUtoTml = false;}
      if(rLjkcaMgwk == true){rLjkcaMgwk = false;}
      if(rcHNAuhgko == true){rcHNAuhgko = false;}
      if(VfYlSgxwoN == true){VfYlSgxwoN = false;}
      if(fwpkXGxXUz == true){fwpkXGxXUz = false;}
      if(tBPmLRKCbY == true){tBPmLRKCbY = false;}
      if(MHhyPMmxRu == true){MHhyPMmxRu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KVMPLYALAO
{ 
  void ssFOIEtTwr()
  { 
      bool VdLzeXGjEP = false;
      bool cTGiicMwZm = false;
      bool izpqldOBbj = false;
      bool gxmZPkTKXG = false;
      bool UFAaTJbFoe = false;
      bool GydBzVnTNB = false;
      bool IFIUiegfTx = false;
      bool ICXSSdzOXb = false;
      bool CJMxciTlas = false;
      bool xzwWyOwfro = false;
      bool cwkqVEZKhU = false;
      bool WYwlzzsLqA = false;
      bool KtEaAIFBUD = false;
      bool gSWiyGXUaY = false;
      bool IJEGVXDKWy = false;
      bool VkoqdiqKqN = false;
      bool zYodnECNms = false;
      bool bXjRqBpyEc = false;
      bool EtdVhuceEP = false;
      bool OMcNZjTZSR = false;
      string AZURfAjMhw;
      string nInEdflehq;
      string FrtNllOeUg;
      string PechyXfszl;
      string uURgUVilmY;
      string ecpHHIeHes;
      string kFrAfJfGGF;
      string zrfuwjZNsQ;
      string DcquCmnUZo;
      string sYNFAocRAL;
      string pcfgYmwtLW;
      string hRNOpINwys;
      string ULfQMZeZuG;
      string HIMgaaxJWO;
      string psJDHaKzPq;
      string bfSHpewOUy;
      string HWzFOYEgmP;
      string LDZiDaBbIk;
      string PeKDeaoFqw;
      string dhoXHStEoh;
      if(AZURfAjMhw == pcfgYmwtLW){VdLzeXGjEP = true;}
      else if(pcfgYmwtLW == AZURfAjMhw){cwkqVEZKhU = true;}
      if(nInEdflehq == hRNOpINwys){cTGiicMwZm = true;}
      else if(hRNOpINwys == nInEdflehq){WYwlzzsLqA = true;}
      if(FrtNllOeUg == ULfQMZeZuG){izpqldOBbj = true;}
      else if(ULfQMZeZuG == FrtNllOeUg){KtEaAIFBUD = true;}
      if(PechyXfszl == HIMgaaxJWO){gxmZPkTKXG = true;}
      else if(HIMgaaxJWO == PechyXfszl){gSWiyGXUaY = true;}
      if(uURgUVilmY == psJDHaKzPq){UFAaTJbFoe = true;}
      else if(psJDHaKzPq == uURgUVilmY){IJEGVXDKWy = true;}
      if(ecpHHIeHes == bfSHpewOUy){GydBzVnTNB = true;}
      else if(bfSHpewOUy == ecpHHIeHes){VkoqdiqKqN = true;}
      if(kFrAfJfGGF == HWzFOYEgmP){IFIUiegfTx = true;}
      else if(HWzFOYEgmP == kFrAfJfGGF){zYodnECNms = true;}
      if(zrfuwjZNsQ == LDZiDaBbIk){ICXSSdzOXb = true;}
      if(DcquCmnUZo == PeKDeaoFqw){CJMxciTlas = true;}
      if(sYNFAocRAL == dhoXHStEoh){xzwWyOwfro = true;}
      while(LDZiDaBbIk == zrfuwjZNsQ){bXjRqBpyEc = true;}
      while(PeKDeaoFqw == PeKDeaoFqw){EtdVhuceEP = true;}
      while(dhoXHStEoh == dhoXHStEoh){OMcNZjTZSR = true;}
      if(VdLzeXGjEP == true){VdLzeXGjEP = false;}
      if(cTGiicMwZm == true){cTGiicMwZm = false;}
      if(izpqldOBbj == true){izpqldOBbj = false;}
      if(gxmZPkTKXG == true){gxmZPkTKXG = false;}
      if(UFAaTJbFoe == true){UFAaTJbFoe = false;}
      if(GydBzVnTNB == true){GydBzVnTNB = false;}
      if(IFIUiegfTx == true){IFIUiegfTx = false;}
      if(ICXSSdzOXb == true){ICXSSdzOXb = false;}
      if(CJMxciTlas == true){CJMxciTlas = false;}
      if(xzwWyOwfro == true){xzwWyOwfro = false;}
      if(cwkqVEZKhU == true){cwkqVEZKhU = false;}
      if(WYwlzzsLqA == true){WYwlzzsLqA = false;}
      if(KtEaAIFBUD == true){KtEaAIFBUD = false;}
      if(gSWiyGXUaY == true){gSWiyGXUaY = false;}
      if(IJEGVXDKWy == true){IJEGVXDKWy = false;}
      if(VkoqdiqKqN == true){VkoqdiqKqN = false;}
      if(zYodnECNms == true){zYodnECNms = false;}
      if(bXjRqBpyEc == true){bXjRqBpyEc = false;}
      if(EtdVhuceEP == true){EtdVhuceEP = false;}
      if(OMcNZjTZSR == true){OMcNZjTZSR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IMQKIDDTHM
{ 
  void cTVZJbsXIC()
  { 
      bool RkToxwTKFe = false;
      bool CfPuMsntMi = false;
      bool useaBQXBwd = false;
      bool bWIWbChxqP = false;
      bool hzJCjTqExa = false;
      bool ecuZaXGrnf = false;
      bool YRNbDfWsSK = false;
      bool LpCxAwjbqg = false;
      bool YTEUyybiuD = false;
      bool uoJKqQkhzD = false;
      bool wyklOnZxZe = false;
      bool mdBGHENrcE = false;
      bool EnxPOWgrGi = false;
      bool KCcmkZiRGK = false;
      bool YdJPPRmCDl = false;
      bool CsEuyIBUWr = false;
      bool HhqpUkANVg = false;
      bool UwlSfaegzx = false;
      bool ienTgRxhnc = false;
      bool YNtNCplSue = false;
      string RmzBiIgFtU;
      string SGgzHsGKSA;
      string zeAhGgVYnT;
      string aNHKHlmJqx;
      string mRjnmscXcr;
      string ZZOSzmlRuC;
      string mHRasEzVqU;
      string GxTUMhuLtN;
      string ExwusBznLU;
      string AVOoKfAJti;
      string sHfIkcGsGR;
      string qZXhyoLVgr;
      string FLKWTkhdKg;
      string glRLTwQnKP;
      string uGgscZxgqV;
      string UebCdgxJnA;
      string ubiYkFIMNB;
      string XXLRxydQts;
      string mBmoMCJOgl;
      string zHzJUSWHIW;
      if(RmzBiIgFtU == sHfIkcGsGR){RkToxwTKFe = true;}
      else if(sHfIkcGsGR == RmzBiIgFtU){wyklOnZxZe = true;}
      if(SGgzHsGKSA == qZXhyoLVgr){CfPuMsntMi = true;}
      else if(qZXhyoLVgr == SGgzHsGKSA){mdBGHENrcE = true;}
      if(zeAhGgVYnT == FLKWTkhdKg){useaBQXBwd = true;}
      else if(FLKWTkhdKg == zeAhGgVYnT){EnxPOWgrGi = true;}
      if(aNHKHlmJqx == glRLTwQnKP){bWIWbChxqP = true;}
      else if(glRLTwQnKP == aNHKHlmJqx){KCcmkZiRGK = true;}
      if(mRjnmscXcr == uGgscZxgqV){hzJCjTqExa = true;}
      else if(uGgscZxgqV == mRjnmscXcr){YdJPPRmCDl = true;}
      if(ZZOSzmlRuC == UebCdgxJnA){ecuZaXGrnf = true;}
      else if(UebCdgxJnA == ZZOSzmlRuC){CsEuyIBUWr = true;}
      if(mHRasEzVqU == ubiYkFIMNB){YRNbDfWsSK = true;}
      else if(ubiYkFIMNB == mHRasEzVqU){HhqpUkANVg = true;}
      if(GxTUMhuLtN == XXLRxydQts){LpCxAwjbqg = true;}
      if(ExwusBznLU == mBmoMCJOgl){YTEUyybiuD = true;}
      if(AVOoKfAJti == zHzJUSWHIW){uoJKqQkhzD = true;}
      while(XXLRxydQts == GxTUMhuLtN){UwlSfaegzx = true;}
      while(mBmoMCJOgl == mBmoMCJOgl){ienTgRxhnc = true;}
      while(zHzJUSWHIW == zHzJUSWHIW){YNtNCplSue = true;}
      if(RkToxwTKFe == true){RkToxwTKFe = false;}
      if(CfPuMsntMi == true){CfPuMsntMi = false;}
      if(useaBQXBwd == true){useaBQXBwd = false;}
      if(bWIWbChxqP == true){bWIWbChxqP = false;}
      if(hzJCjTqExa == true){hzJCjTqExa = false;}
      if(ecuZaXGrnf == true){ecuZaXGrnf = false;}
      if(YRNbDfWsSK == true){YRNbDfWsSK = false;}
      if(LpCxAwjbqg == true){LpCxAwjbqg = false;}
      if(YTEUyybiuD == true){YTEUyybiuD = false;}
      if(uoJKqQkhzD == true){uoJKqQkhzD = false;}
      if(wyklOnZxZe == true){wyklOnZxZe = false;}
      if(mdBGHENrcE == true){mdBGHENrcE = false;}
      if(EnxPOWgrGi == true){EnxPOWgrGi = false;}
      if(KCcmkZiRGK == true){KCcmkZiRGK = false;}
      if(YdJPPRmCDl == true){YdJPPRmCDl = false;}
      if(CsEuyIBUWr == true){CsEuyIBUWr = false;}
      if(HhqpUkANVg == true){HhqpUkANVg = false;}
      if(UwlSfaegzx == true){UwlSfaegzx = false;}
      if(ienTgRxhnc == true){ienTgRxhnc = false;}
      if(YNtNCplSue == true){YNtNCplSue = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGVWSZDNWZ
{ 
  void cKVGuiYnuW()
  { 
      bool xRPYDqeLbC = false;
      bool ASfFrKsazb = false;
      bool hDqigkLfXn = false;
      bool uBMXsbFKHF = false;
      bool gorLmxGszX = false;
      bool mBKuitafrS = false;
      bool fynmGyFHLQ = false;
      bool FhTttrKewi = false;
      bool eSgAAtqQny = false;
      bool AYRoZiBEEn = false;
      bool qzgiSFgQBp = false;
      bool jwjJnMQnlM = false;
      bool HoSNPfPeUL = false;
      bool qGZIqekyhu = false;
      bool MZPyODoIBM = false;
      bool RNRrfCfTSl = false;
      bool pCwozcVbRI = false;
      bool bSFqzhYUyL = false;
      bool qGdHtcngbo = false;
      bool zQeuEKdZyk = false;
      string YdwrMftFcA;
      string rjtINEcUKc;
      string GPuwnbdiWF;
      string aOKjNqSMYM;
      string TmJCrGIIeo;
      string DfYGWIhzDj;
      string CKiWZdYJuV;
      string kPuxITFsEg;
      string SVEgCtpENE;
      string JTInJIEmbO;
      string gzMIDmjaxC;
      string CnuWRgGBUe;
      string mTuqMRHHnA;
      string OSQoATIucO;
      string JPHKBUXlWc;
      string CCRxaMDVwl;
      string fclxmjWFVx;
      string YKXGUXMjoq;
      string tUjLxLBTOm;
      string QmyqhfcKWR;
      if(YdwrMftFcA == gzMIDmjaxC){xRPYDqeLbC = true;}
      else if(gzMIDmjaxC == YdwrMftFcA){qzgiSFgQBp = true;}
      if(rjtINEcUKc == CnuWRgGBUe){ASfFrKsazb = true;}
      else if(CnuWRgGBUe == rjtINEcUKc){jwjJnMQnlM = true;}
      if(GPuwnbdiWF == mTuqMRHHnA){hDqigkLfXn = true;}
      else if(mTuqMRHHnA == GPuwnbdiWF){HoSNPfPeUL = true;}
      if(aOKjNqSMYM == OSQoATIucO){uBMXsbFKHF = true;}
      else if(OSQoATIucO == aOKjNqSMYM){qGZIqekyhu = true;}
      if(TmJCrGIIeo == JPHKBUXlWc){gorLmxGszX = true;}
      else if(JPHKBUXlWc == TmJCrGIIeo){MZPyODoIBM = true;}
      if(DfYGWIhzDj == CCRxaMDVwl){mBKuitafrS = true;}
      else if(CCRxaMDVwl == DfYGWIhzDj){RNRrfCfTSl = true;}
      if(CKiWZdYJuV == fclxmjWFVx){fynmGyFHLQ = true;}
      else if(fclxmjWFVx == CKiWZdYJuV){pCwozcVbRI = true;}
      if(kPuxITFsEg == YKXGUXMjoq){FhTttrKewi = true;}
      if(SVEgCtpENE == tUjLxLBTOm){eSgAAtqQny = true;}
      if(JTInJIEmbO == QmyqhfcKWR){AYRoZiBEEn = true;}
      while(YKXGUXMjoq == kPuxITFsEg){bSFqzhYUyL = true;}
      while(tUjLxLBTOm == tUjLxLBTOm){qGdHtcngbo = true;}
      while(QmyqhfcKWR == QmyqhfcKWR){zQeuEKdZyk = true;}
      if(xRPYDqeLbC == true){xRPYDqeLbC = false;}
      if(ASfFrKsazb == true){ASfFrKsazb = false;}
      if(hDqigkLfXn == true){hDqigkLfXn = false;}
      if(uBMXsbFKHF == true){uBMXsbFKHF = false;}
      if(gorLmxGszX == true){gorLmxGszX = false;}
      if(mBKuitafrS == true){mBKuitafrS = false;}
      if(fynmGyFHLQ == true){fynmGyFHLQ = false;}
      if(FhTttrKewi == true){FhTttrKewi = false;}
      if(eSgAAtqQny == true){eSgAAtqQny = false;}
      if(AYRoZiBEEn == true){AYRoZiBEEn = false;}
      if(qzgiSFgQBp == true){qzgiSFgQBp = false;}
      if(jwjJnMQnlM == true){jwjJnMQnlM = false;}
      if(HoSNPfPeUL == true){HoSNPfPeUL = false;}
      if(qGZIqekyhu == true){qGZIqekyhu = false;}
      if(MZPyODoIBM == true){MZPyODoIBM = false;}
      if(RNRrfCfTSl == true){RNRrfCfTSl = false;}
      if(pCwozcVbRI == true){pCwozcVbRI = false;}
      if(bSFqzhYUyL == true){bSFqzhYUyL = false;}
      if(qGdHtcngbo == true){qGdHtcngbo = false;}
      if(zQeuEKdZyk == true){zQeuEKdZyk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBTOBNWIBB
{ 
  void zLJiiJyUCs()
  { 
      bool MinsltSWpD = false;
      bool CaTsMrCMcj = false;
      bool UYEYPdTlIe = false;
      bool XOZhxdspdm = false;
      bool kUFACQAoOo = false;
      bool oQDwTnePdI = false;
      bool afOLenBlwi = false;
      bool zMipzzTDWy = false;
      bool ddWSpHKcOJ = false;
      bool zcLVLEGtVN = false;
      bool ONsfocgNwT = false;
      bool TaredwJuUW = false;
      bool dXXljVAMdt = false;
      bool rZgJjPjpcM = false;
      bool axgtoXkgqP = false;
      bool uKYyjpoGuT = false;
      bool bTiCbtthuO = false;
      bool LSRIwfqdxM = false;
      bool kSVOzhBiZs = false;
      bool ZcuJkGNdSt = false;
      string rgREdCzZss;
      string wAVsIPUTOY;
      string dIibkNYcbL;
      string rEjACHATzV;
      string IurNEzdCut;
      string cqVEGixpSQ;
      string dWygBqQUpA;
      string PBTrQhQUWl;
      string iVggiAiesT;
      string JKAirlxKMN;
      string iIMteaWcnY;
      string ScSggHoQxA;
      string HkaWqEAkAd;
      string jFIJCZJlCH;
      string dGpUAgrSBj;
      string xgMMFxhoDZ;
      string ZlcJnMTIdH;
      string yCOpWBtGVJ;
      string MhiPgDruEE;
      string rTibhqcfgn;
      if(rgREdCzZss == iIMteaWcnY){MinsltSWpD = true;}
      else if(iIMteaWcnY == rgREdCzZss){ONsfocgNwT = true;}
      if(wAVsIPUTOY == ScSggHoQxA){CaTsMrCMcj = true;}
      else if(ScSggHoQxA == wAVsIPUTOY){TaredwJuUW = true;}
      if(dIibkNYcbL == HkaWqEAkAd){UYEYPdTlIe = true;}
      else if(HkaWqEAkAd == dIibkNYcbL){dXXljVAMdt = true;}
      if(rEjACHATzV == jFIJCZJlCH){XOZhxdspdm = true;}
      else if(jFIJCZJlCH == rEjACHATzV){rZgJjPjpcM = true;}
      if(IurNEzdCut == dGpUAgrSBj){kUFACQAoOo = true;}
      else if(dGpUAgrSBj == IurNEzdCut){axgtoXkgqP = true;}
      if(cqVEGixpSQ == xgMMFxhoDZ){oQDwTnePdI = true;}
      else if(xgMMFxhoDZ == cqVEGixpSQ){uKYyjpoGuT = true;}
      if(dWygBqQUpA == ZlcJnMTIdH){afOLenBlwi = true;}
      else if(ZlcJnMTIdH == dWygBqQUpA){bTiCbtthuO = true;}
      if(PBTrQhQUWl == yCOpWBtGVJ){zMipzzTDWy = true;}
      if(iVggiAiesT == MhiPgDruEE){ddWSpHKcOJ = true;}
      if(JKAirlxKMN == rTibhqcfgn){zcLVLEGtVN = true;}
      while(yCOpWBtGVJ == PBTrQhQUWl){LSRIwfqdxM = true;}
      while(MhiPgDruEE == MhiPgDruEE){kSVOzhBiZs = true;}
      while(rTibhqcfgn == rTibhqcfgn){ZcuJkGNdSt = true;}
      if(MinsltSWpD == true){MinsltSWpD = false;}
      if(CaTsMrCMcj == true){CaTsMrCMcj = false;}
      if(UYEYPdTlIe == true){UYEYPdTlIe = false;}
      if(XOZhxdspdm == true){XOZhxdspdm = false;}
      if(kUFACQAoOo == true){kUFACQAoOo = false;}
      if(oQDwTnePdI == true){oQDwTnePdI = false;}
      if(afOLenBlwi == true){afOLenBlwi = false;}
      if(zMipzzTDWy == true){zMipzzTDWy = false;}
      if(ddWSpHKcOJ == true){ddWSpHKcOJ = false;}
      if(zcLVLEGtVN == true){zcLVLEGtVN = false;}
      if(ONsfocgNwT == true){ONsfocgNwT = false;}
      if(TaredwJuUW == true){TaredwJuUW = false;}
      if(dXXljVAMdt == true){dXXljVAMdt = false;}
      if(rZgJjPjpcM == true){rZgJjPjpcM = false;}
      if(axgtoXkgqP == true){axgtoXkgqP = false;}
      if(uKYyjpoGuT == true){uKYyjpoGuT = false;}
      if(bTiCbtthuO == true){bTiCbtthuO = false;}
      if(LSRIwfqdxM == true){LSRIwfqdxM = false;}
      if(kSVOzhBiZs == true){kSVOzhBiZs = false;}
      if(ZcuJkGNdSt == true){ZcuJkGNdSt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FKVTOFNSHO
{ 
  void oeNuhwzbSV()
  { 
      bool FhrgKkXKaf = false;
      bool YEFDGKdAAg = false;
      bool ygHRbAxSWN = false;
      bool aQqjAmYLTW = false;
      bool CHAHwYsfmE = false;
      bool hWfmLXaZEK = false;
      bool mFnNEHMVCS = false;
      bool lSgcdqgAUC = false;
      bool HQfReEjDXb = false;
      bool MyGIixSlCn = false;
      bool LWcTRPpDIU = false;
      bool qZFCDWZViA = false;
      bool WIxZFnLXsg = false;
      bool XtyfpjmLAP = false;
      bool NguDkmsEFM = false;
      bool XxDBRDZDNc = false;
      bool DRJbwxbYMS = false;
      bool iNVTloNtoS = false;
      bool uHSgJapwOm = false;
      bool KjxWLwXSGm = false;
      string eRNItuJAey;
      string OglLppwDeA;
      string jHsCasYPRn;
      string DpVzfXArmf;
      string kDQFEWsCtS;
      string aSSyBWYKhA;
      string VthpuYLmeS;
      string pEQzPgpmyD;
      string AWUzNkWXxI;
      string ypJlJpUaKf;
      string LFWbcVBThU;
      string gkMeAzYicJ;
      string BnoWTzueoY;
      string MPcRrtzrWq;
      string jCocbNcdlK;
      string RkxBeWQAIc;
      string aWeIIQIulF;
      string zgMlZyyLtF;
      string VQrdHaSbmU;
      string dzisPMXgUK;
      if(eRNItuJAey == LFWbcVBThU){FhrgKkXKaf = true;}
      else if(LFWbcVBThU == eRNItuJAey){LWcTRPpDIU = true;}
      if(OglLppwDeA == gkMeAzYicJ){YEFDGKdAAg = true;}
      else if(gkMeAzYicJ == OglLppwDeA){qZFCDWZViA = true;}
      if(jHsCasYPRn == BnoWTzueoY){ygHRbAxSWN = true;}
      else if(BnoWTzueoY == jHsCasYPRn){WIxZFnLXsg = true;}
      if(DpVzfXArmf == MPcRrtzrWq){aQqjAmYLTW = true;}
      else if(MPcRrtzrWq == DpVzfXArmf){XtyfpjmLAP = true;}
      if(kDQFEWsCtS == jCocbNcdlK){CHAHwYsfmE = true;}
      else if(jCocbNcdlK == kDQFEWsCtS){NguDkmsEFM = true;}
      if(aSSyBWYKhA == RkxBeWQAIc){hWfmLXaZEK = true;}
      else if(RkxBeWQAIc == aSSyBWYKhA){XxDBRDZDNc = true;}
      if(VthpuYLmeS == aWeIIQIulF){mFnNEHMVCS = true;}
      else if(aWeIIQIulF == VthpuYLmeS){DRJbwxbYMS = true;}
      if(pEQzPgpmyD == zgMlZyyLtF){lSgcdqgAUC = true;}
      if(AWUzNkWXxI == VQrdHaSbmU){HQfReEjDXb = true;}
      if(ypJlJpUaKf == dzisPMXgUK){MyGIixSlCn = true;}
      while(zgMlZyyLtF == pEQzPgpmyD){iNVTloNtoS = true;}
      while(VQrdHaSbmU == VQrdHaSbmU){uHSgJapwOm = true;}
      while(dzisPMXgUK == dzisPMXgUK){KjxWLwXSGm = true;}
      if(FhrgKkXKaf == true){FhrgKkXKaf = false;}
      if(YEFDGKdAAg == true){YEFDGKdAAg = false;}
      if(ygHRbAxSWN == true){ygHRbAxSWN = false;}
      if(aQqjAmYLTW == true){aQqjAmYLTW = false;}
      if(CHAHwYsfmE == true){CHAHwYsfmE = false;}
      if(hWfmLXaZEK == true){hWfmLXaZEK = false;}
      if(mFnNEHMVCS == true){mFnNEHMVCS = false;}
      if(lSgcdqgAUC == true){lSgcdqgAUC = false;}
      if(HQfReEjDXb == true){HQfReEjDXb = false;}
      if(MyGIixSlCn == true){MyGIixSlCn = false;}
      if(LWcTRPpDIU == true){LWcTRPpDIU = false;}
      if(qZFCDWZViA == true){qZFCDWZViA = false;}
      if(WIxZFnLXsg == true){WIxZFnLXsg = false;}
      if(XtyfpjmLAP == true){XtyfpjmLAP = false;}
      if(NguDkmsEFM == true){NguDkmsEFM = false;}
      if(XxDBRDZDNc == true){XxDBRDZDNc = false;}
      if(DRJbwxbYMS == true){DRJbwxbYMS = false;}
      if(iNVTloNtoS == true){iNVTloNtoS = false;}
      if(uHSgJapwOm == true){uHSgJapwOm = false;}
      if(KjxWLwXSGm == true){KjxWLwXSGm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IXPPFGHBMO
{ 
  void IyWPubGtBM()
  { 
      bool HEPgYiUWiP = false;
      bool uRdyxzgrNH = false;
      bool syPCQzliLX = false;
      bool arWmqmLqis = false;
      bool wSUixBFbKX = false;
      bool YgBIsJoMQY = false;
      bool wkLKnDupHK = false;
      bool npITKadfFO = false;
      bool tJYmzspNtg = false;
      bool xyZKwLGJts = false;
      bool GPUAjiYgyS = false;
      bool eIHBemLXLu = false;
      bool MgwZMoPyXy = false;
      bool TTkLHeoYDQ = false;
      bool UJPbCopYeJ = false;
      bool AiyzgZStmt = false;
      bool SZJAyKXwsA = false;
      bool ymUtZDRUXX = false;
      bool zqSOykVkeh = false;
      bool LtkIxuAPcq = false;
      string eAzEZInpyT;
      string NKlTztqPqC;
      string NNPMCHsXFI;
      string XzhUSNkDuu;
      string xkdyFqzCrI;
      string zQKQeQklBS;
      string OQjpwOcRAl;
      string JmTuEcjRHK;
      string HqewIHnQpC;
      string cyBcfgAmBq;
      string OhCGzLwOMB;
      string fSeqKXkngo;
      string ZLbxIKkqPX;
      string cwQPuZnYwx;
      string KYEnWJTKSH;
      string uLGMQDFExn;
      string ZFzoXiCOuk;
      string iMqidAHmay;
      string qaYHbQpDzr;
      string TjaHXFZOPm;
      if(eAzEZInpyT == OhCGzLwOMB){HEPgYiUWiP = true;}
      else if(OhCGzLwOMB == eAzEZInpyT){GPUAjiYgyS = true;}
      if(NKlTztqPqC == fSeqKXkngo){uRdyxzgrNH = true;}
      else if(fSeqKXkngo == NKlTztqPqC){eIHBemLXLu = true;}
      if(NNPMCHsXFI == ZLbxIKkqPX){syPCQzliLX = true;}
      else if(ZLbxIKkqPX == NNPMCHsXFI){MgwZMoPyXy = true;}
      if(XzhUSNkDuu == cwQPuZnYwx){arWmqmLqis = true;}
      else if(cwQPuZnYwx == XzhUSNkDuu){TTkLHeoYDQ = true;}
      if(xkdyFqzCrI == KYEnWJTKSH){wSUixBFbKX = true;}
      else if(KYEnWJTKSH == xkdyFqzCrI){UJPbCopYeJ = true;}
      if(zQKQeQklBS == uLGMQDFExn){YgBIsJoMQY = true;}
      else if(uLGMQDFExn == zQKQeQklBS){AiyzgZStmt = true;}
      if(OQjpwOcRAl == ZFzoXiCOuk){wkLKnDupHK = true;}
      else if(ZFzoXiCOuk == OQjpwOcRAl){SZJAyKXwsA = true;}
      if(JmTuEcjRHK == iMqidAHmay){npITKadfFO = true;}
      if(HqewIHnQpC == qaYHbQpDzr){tJYmzspNtg = true;}
      if(cyBcfgAmBq == TjaHXFZOPm){xyZKwLGJts = true;}
      while(iMqidAHmay == JmTuEcjRHK){ymUtZDRUXX = true;}
      while(qaYHbQpDzr == qaYHbQpDzr){zqSOykVkeh = true;}
      while(TjaHXFZOPm == TjaHXFZOPm){LtkIxuAPcq = true;}
      if(HEPgYiUWiP == true){HEPgYiUWiP = false;}
      if(uRdyxzgrNH == true){uRdyxzgrNH = false;}
      if(syPCQzliLX == true){syPCQzliLX = false;}
      if(arWmqmLqis == true){arWmqmLqis = false;}
      if(wSUixBFbKX == true){wSUixBFbKX = false;}
      if(YgBIsJoMQY == true){YgBIsJoMQY = false;}
      if(wkLKnDupHK == true){wkLKnDupHK = false;}
      if(npITKadfFO == true){npITKadfFO = false;}
      if(tJYmzspNtg == true){tJYmzspNtg = false;}
      if(xyZKwLGJts == true){xyZKwLGJts = false;}
      if(GPUAjiYgyS == true){GPUAjiYgyS = false;}
      if(eIHBemLXLu == true){eIHBemLXLu = false;}
      if(MgwZMoPyXy == true){MgwZMoPyXy = false;}
      if(TTkLHeoYDQ == true){TTkLHeoYDQ = false;}
      if(UJPbCopYeJ == true){UJPbCopYeJ = false;}
      if(AiyzgZStmt == true){AiyzgZStmt = false;}
      if(SZJAyKXwsA == true){SZJAyKXwsA = false;}
      if(ymUtZDRUXX == true){ymUtZDRUXX = false;}
      if(zqSOykVkeh == true){zqSOykVkeh = false;}
      if(LtkIxuAPcq == true){LtkIxuAPcq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OPQGAIYXKZ
{ 
  void IMFouiCaMc()
  { 
      bool gcomDfVbgu = false;
      bool zUqouwZYiU = false;
      bool QHcokRNuLX = false;
      bool ADzjKIRQph = false;
      bool KBeoaasmjS = false;
      bool JEZEgZAACl = false;
      bool RaPJtwUHel = false;
      bool dIhBKObmOJ = false;
      bool XaKsOuduCj = false;
      bool IRODPjlVtd = false;
      bool GlIyoBWYtR = false;
      bool yMlrOqPWtz = false;
      bool SYEtcMseka = false;
      bool bFsjDlRMDN = false;
      bool YEBklwfVoY = false;
      bool TPbuLggNVb = false;
      bool HqmSorSBob = false;
      bool YCSgZNXTIf = false;
      bool gXoMGMdyXW = false;
      bool FEqbGgRhut = false;
      string UnjZhUPeGO;
      string lgGWYoADCP;
      string HMGAEfBeWY;
      string dxbAbGxdpk;
      string IsftokyssA;
      string mOintIhiVC;
      string TkIgjnFFtS;
      string qVMQHOfLKS;
      string gIkVkPNmGT;
      string XOInQWjzJA;
      string eryaJRCRgf;
      string bVXDULAmuU;
      string ZSzZtbNXzj;
      string dgBKmnJJMT;
      string NwFarCpFTF;
      string WxDoZMsYgg;
      string EdSwBtUNPf;
      string CpabHdMYgr;
      string lHEsNgdMja;
      string ujcePidIYx;
      if(UnjZhUPeGO == eryaJRCRgf){gcomDfVbgu = true;}
      else if(eryaJRCRgf == UnjZhUPeGO){GlIyoBWYtR = true;}
      if(lgGWYoADCP == bVXDULAmuU){zUqouwZYiU = true;}
      else if(bVXDULAmuU == lgGWYoADCP){yMlrOqPWtz = true;}
      if(HMGAEfBeWY == ZSzZtbNXzj){QHcokRNuLX = true;}
      else if(ZSzZtbNXzj == HMGAEfBeWY){SYEtcMseka = true;}
      if(dxbAbGxdpk == dgBKmnJJMT){ADzjKIRQph = true;}
      else if(dgBKmnJJMT == dxbAbGxdpk){bFsjDlRMDN = true;}
      if(IsftokyssA == NwFarCpFTF){KBeoaasmjS = true;}
      else if(NwFarCpFTF == IsftokyssA){YEBklwfVoY = true;}
      if(mOintIhiVC == WxDoZMsYgg){JEZEgZAACl = true;}
      else if(WxDoZMsYgg == mOintIhiVC){TPbuLggNVb = true;}
      if(TkIgjnFFtS == EdSwBtUNPf){RaPJtwUHel = true;}
      else if(EdSwBtUNPf == TkIgjnFFtS){HqmSorSBob = true;}
      if(qVMQHOfLKS == CpabHdMYgr){dIhBKObmOJ = true;}
      if(gIkVkPNmGT == lHEsNgdMja){XaKsOuduCj = true;}
      if(XOInQWjzJA == ujcePidIYx){IRODPjlVtd = true;}
      while(CpabHdMYgr == qVMQHOfLKS){YCSgZNXTIf = true;}
      while(lHEsNgdMja == lHEsNgdMja){gXoMGMdyXW = true;}
      while(ujcePidIYx == ujcePidIYx){FEqbGgRhut = true;}
      if(gcomDfVbgu == true){gcomDfVbgu = false;}
      if(zUqouwZYiU == true){zUqouwZYiU = false;}
      if(QHcokRNuLX == true){QHcokRNuLX = false;}
      if(ADzjKIRQph == true){ADzjKIRQph = false;}
      if(KBeoaasmjS == true){KBeoaasmjS = false;}
      if(JEZEgZAACl == true){JEZEgZAACl = false;}
      if(RaPJtwUHel == true){RaPJtwUHel = false;}
      if(dIhBKObmOJ == true){dIhBKObmOJ = false;}
      if(XaKsOuduCj == true){XaKsOuduCj = false;}
      if(IRODPjlVtd == true){IRODPjlVtd = false;}
      if(GlIyoBWYtR == true){GlIyoBWYtR = false;}
      if(yMlrOqPWtz == true){yMlrOqPWtz = false;}
      if(SYEtcMseka == true){SYEtcMseka = false;}
      if(bFsjDlRMDN == true){bFsjDlRMDN = false;}
      if(YEBklwfVoY == true){YEBklwfVoY = false;}
      if(TPbuLggNVb == true){TPbuLggNVb = false;}
      if(HqmSorSBob == true){HqmSorSBob = false;}
      if(YCSgZNXTIf == true){YCSgZNXTIf = false;}
      if(gXoMGMdyXW == true){gXoMGMdyXW = false;}
      if(FEqbGgRhut == true){FEqbGgRhut = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CSGUONJDCX
{ 
  void xeiJBNdsZF()
  { 
      bool VwSkQkZpzj = false;
      bool NARqeiESQs = false;
      bool KudIrUFIld = false;
      bool iniymXfPZr = false;
      bool KmamcqGLqe = false;
      bool IFMtWZSKsw = false;
      bool eQEVBYRSDH = false;
      bool CnrXiXUpeA = false;
      bool OsQHVcbnaN = false;
      bool FUWcMshEkD = false;
      bool ZmHjbTMnKz = false;
      bool EbfrhkzxAX = false;
      bool xcqpBhROKo = false;
      bool oPEaaalgeB = false;
      bool QmdaIcodua = false;
      bool tkEMFwuQht = false;
      bool BxcUKoWEQG = false;
      bool zSRyHKzQhY = false;
      bool rnSjuEKqUe = false;
      bool eUykASJIQT = false;
      string HbQphhwexU;
      string DCXZOJxfdn;
      string sqXEhKzinC;
      string OYaztiasqF;
      string PxiGKtjefA;
      string ERgnOQELHX;
      string iMpuGeaYef;
      string hDoXYwIQtn;
      string ZUCnywqmjd;
      string ePlSWCGnAe;
      string SLzARAcJPS;
      string HmQTyNJBxJ;
      string nnnBASRWAV;
      string oTQPUOUCVx;
      string TgWRVryRUJ;
      string rFppqdWxzz;
      string iGJtdnVByi;
      string rHfApGQWfI;
      string TzBqcjcaXp;
      string qXCWNMXcnh;
      if(HbQphhwexU == SLzARAcJPS){VwSkQkZpzj = true;}
      else if(SLzARAcJPS == HbQphhwexU){ZmHjbTMnKz = true;}
      if(DCXZOJxfdn == HmQTyNJBxJ){NARqeiESQs = true;}
      else if(HmQTyNJBxJ == DCXZOJxfdn){EbfrhkzxAX = true;}
      if(sqXEhKzinC == nnnBASRWAV){KudIrUFIld = true;}
      else if(nnnBASRWAV == sqXEhKzinC){xcqpBhROKo = true;}
      if(OYaztiasqF == oTQPUOUCVx){iniymXfPZr = true;}
      else if(oTQPUOUCVx == OYaztiasqF){oPEaaalgeB = true;}
      if(PxiGKtjefA == TgWRVryRUJ){KmamcqGLqe = true;}
      else if(TgWRVryRUJ == PxiGKtjefA){QmdaIcodua = true;}
      if(ERgnOQELHX == rFppqdWxzz){IFMtWZSKsw = true;}
      else if(rFppqdWxzz == ERgnOQELHX){tkEMFwuQht = true;}
      if(iMpuGeaYef == iGJtdnVByi){eQEVBYRSDH = true;}
      else if(iGJtdnVByi == iMpuGeaYef){BxcUKoWEQG = true;}
      if(hDoXYwIQtn == rHfApGQWfI){CnrXiXUpeA = true;}
      if(ZUCnywqmjd == TzBqcjcaXp){OsQHVcbnaN = true;}
      if(ePlSWCGnAe == qXCWNMXcnh){FUWcMshEkD = true;}
      while(rHfApGQWfI == hDoXYwIQtn){zSRyHKzQhY = true;}
      while(TzBqcjcaXp == TzBqcjcaXp){rnSjuEKqUe = true;}
      while(qXCWNMXcnh == qXCWNMXcnh){eUykASJIQT = true;}
      if(VwSkQkZpzj == true){VwSkQkZpzj = false;}
      if(NARqeiESQs == true){NARqeiESQs = false;}
      if(KudIrUFIld == true){KudIrUFIld = false;}
      if(iniymXfPZr == true){iniymXfPZr = false;}
      if(KmamcqGLqe == true){KmamcqGLqe = false;}
      if(IFMtWZSKsw == true){IFMtWZSKsw = false;}
      if(eQEVBYRSDH == true){eQEVBYRSDH = false;}
      if(CnrXiXUpeA == true){CnrXiXUpeA = false;}
      if(OsQHVcbnaN == true){OsQHVcbnaN = false;}
      if(FUWcMshEkD == true){FUWcMshEkD = false;}
      if(ZmHjbTMnKz == true){ZmHjbTMnKz = false;}
      if(EbfrhkzxAX == true){EbfrhkzxAX = false;}
      if(xcqpBhROKo == true){xcqpBhROKo = false;}
      if(oPEaaalgeB == true){oPEaaalgeB = false;}
      if(QmdaIcodua == true){QmdaIcodua = false;}
      if(tkEMFwuQht == true){tkEMFwuQht = false;}
      if(BxcUKoWEQG == true){BxcUKoWEQG = false;}
      if(zSRyHKzQhY == true){zSRyHKzQhY = false;}
      if(rnSjuEKqUe == true){rnSjuEKqUe = false;}
      if(eUykASJIQT == true){eUykASJIQT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DGXVJWINFW
{ 
  void mLVgJWexhh()
  { 
      bool QEyqOPerXN = false;
      bool AdITolJpXb = false;
      bool cxDGEoXqqb = false;
      bool QWXLTGPKXM = false;
      bool yRUOFgFIZy = false;
      bool JgAFZSArlZ = false;
      bool rmBwwdGwAh = false;
      bool WySLcKboAX = false;
      bool iORsSiVRlB = false;
      bool FXYxTLQYRb = false;
      bool ZIIqaKOobO = false;
      bool pKqNpcVIcM = false;
      bool HnJycyZUqR = false;
      bool tDXYyZGZRH = false;
      bool UgpXKtfKGp = false;
      bool oIuETkyJOc = false;
      bool ksxKUmmSPP = false;
      bool WuqVrZylmh = false;
      bool SONAblHSEM = false;
      bool bwKoWaifCX = false;
      string nnaEVwpjMb;
      string EyuoXRHYPE;
      string ROdsXpwdzm;
      string zcJyeVbHwF;
      string LsFWUFWjzl;
      string aysnrZKhge;
      string zMjYcbowJC;
      string pAbKsXJGXR;
      string TLdMMBjUGF;
      string KtZRFzJfts;
      string PZawwaVhuT;
      string PDJOKmhXMa;
      string qUpDruZJEt;
      string OcMdBtkgQk;
      string eBZloHjLHR;
      string QlTSCuiWEA;
      string AMdBEmqfMP;
      string CAGauouEOj;
      string LOCmccJsbG;
      string LNcPjSXXgC;
      if(nnaEVwpjMb == PZawwaVhuT){QEyqOPerXN = true;}
      else if(PZawwaVhuT == nnaEVwpjMb){ZIIqaKOobO = true;}
      if(EyuoXRHYPE == PDJOKmhXMa){AdITolJpXb = true;}
      else if(PDJOKmhXMa == EyuoXRHYPE){pKqNpcVIcM = true;}
      if(ROdsXpwdzm == qUpDruZJEt){cxDGEoXqqb = true;}
      else if(qUpDruZJEt == ROdsXpwdzm){HnJycyZUqR = true;}
      if(zcJyeVbHwF == OcMdBtkgQk){QWXLTGPKXM = true;}
      else if(OcMdBtkgQk == zcJyeVbHwF){tDXYyZGZRH = true;}
      if(LsFWUFWjzl == eBZloHjLHR){yRUOFgFIZy = true;}
      else if(eBZloHjLHR == LsFWUFWjzl){UgpXKtfKGp = true;}
      if(aysnrZKhge == QlTSCuiWEA){JgAFZSArlZ = true;}
      else if(QlTSCuiWEA == aysnrZKhge){oIuETkyJOc = true;}
      if(zMjYcbowJC == AMdBEmqfMP){rmBwwdGwAh = true;}
      else if(AMdBEmqfMP == zMjYcbowJC){ksxKUmmSPP = true;}
      if(pAbKsXJGXR == CAGauouEOj){WySLcKboAX = true;}
      if(TLdMMBjUGF == LOCmccJsbG){iORsSiVRlB = true;}
      if(KtZRFzJfts == LNcPjSXXgC){FXYxTLQYRb = true;}
      while(CAGauouEOj == pAbKsXJGXR){WuqVrZylmh = true;}
      while(LOCmccJsbG == LOCmccJsbG){SONAblHSEM = true;}
      while(LNcPjSXXgC == LNcPjSXXgC){bwKoWaifCX = true;}
      if(QEyqOPerXN == true){QEyqOPerXN = false;}
      if(AdITolJpXb == true){AdITolJpXb = false;}
      if(cxDGEoXqqb == true){cxDGEoXqqb = false;}
      if(QWXLTGPKXM == true){QWXLTGPKXM = false;}
      if(yRUOFgFIZy == true){yRUOFgFIZy = false;}
      if(JgAFZSArlZ == true){JgAFZSArlZ = false;}
      if(rmBwwdGwAh == true){rmBwwdGwAh = false;}
      if(WySLcKboAX == true){WySLcKboAX = false;}
      if(iORsSiVRlB == true){iORsSiVRlB = false;}
      if(FXYxTLQYRb == true){FXYxTLQYRb = false;}
      if(ZIIqaKOobO == true){ZIIqaKOobO = false;}
      if(pKqNpcVIcM == true){pKqNpcVIcM = false;}
      if(HnJycyZUqR == true){HnJycyZUqR = false;}
      if(tDXYyZGZRH == true){tDXYyZGZRH = false;}
      if(UgpXKtfKGp == true){UgpXKtfKGp = false;}
      if(oIuETkyJOc == true){oIuETkyJOc = false;}
      if(ksxKUmmSPP == true){ksxKUmmSPP = false;}
      if(WuqVrZylmh == true){WuqVrZylmh = false;}
      if(SONAblHSEM == true){SONAblHSEM = false;}
      if(bwKoWaifCX == true){bwKoWaifCX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CKAFSMBVOX
{ 
  void YkmRdGmeuU()
  { 
      bool dGRYUwKGGJ = false;
      bool jeRuUCgiMg = false;
      bool QBWoKGcOgo = false;
      bool VibZbDmXmX = false;
      bool wkBmBqyVKf = false;
      bool wNxsxbibNO = false;
      bool TwYRnBDrTR = false;
      bool PIwnkeAinT = false;
      bool HHDBsIkhbA = false;
      bool TKKYEAMizA = false;
      bool nGBsPmRIIR = false;
      bool azntHLrWYf = false;
      bool QUPTxEyXjj = false;
      bool SQjmeBFJkF = false;
      bool pbZKYTWQQr = false;
      bool HoKSjTphuL = false;
      bool ntXXyJPAOF = false;
      bool GhlSonuFtd = false;
      bool hhGrcdGQDL = false;
      bool KWNZQwDBLP = false;
      string XSxXKhLnjg;
      string HKKBbolVBA;
      string OOuoFZCiFj;
      string RPrhADeDbP;
      string isaOddZQTb;
      string ocfJUIXHSj;
      string ecizPrRcBY;
      string KitlRVnfLa;
      string zlOcuojhMq;
      string eXkqkFKazk;
      string MwPuRFhtrz;
      string UquqjrOFEZ;
      string IiPJslyDBL;
      string LMgZOCVTLo;
      string HppNVnbsGr;
      string qEVYccgFBe;
      string HdrfmHJUbg;
      string WutPSSrBnF;
      string KExITGqHxl;
      string VQRfhcxJZN;
      if(XSxXKhLnjg == MwPuRFhtrz){dGRYUwKGGJ = true;}
      else if(MwPuRFhtrz == XSxXKhLnjg){nGBsPmRIIR = true;}
      if(HKKBbolVBA == UquqjrOFEZ){jeRuUCgiMg = true;}
      else if(UquqjrOFEZ == HKKBbolVBA){azntHLrWYf = true;}
      if(OOuoFZCiFj == IiPJslyDBL){QBWoKGcOgo = true;}
      else if(IiPJslyDBL == OOuoFZCiFj){QUPTxEyXjj = true;}
      if(RPrhADeDbP == LMgZOCVTLo){VibZbDmXmX = true;}
      else if(LMgZOCVTLo == RPrhADeDbP){SQjmeBFJkF = true;}
      if(isaOddZQTb == HppNVnbsGr){wkBmBqyVKf = true;}
      else if(HppNVnbsGr == isaOddZQTb){pbZKYTWQQr = true;}
      if(ocfJUIXHSj == qEVYccgFBe){wNxsxbibNO = true;}
      else if(qEVYccgFBe == ocfJUIXHSj){HoKSjTphuL = true;}
      if(ecizPrRcBY == HdrfmHJUbg){TwYRnBDrTR = true;}
      else if(HdrfmHJUbg == ecizPrRcBY){ntXXyJPAOF = true;}
      if(KitlRVnfLa == WutPSSrBnF){PIwnkeAinT = true;}
      if(zlOcuojhMq == KExITGqHxl){HHDBsIkhbA = true;}
      if(eXkqkFKazk == VQRfhcxJZN){TKKYEAMizA = true;}
      while(WutPSSrBnF == KitlRVnfLa){GhlSonuFtd = true;}
      while(KExITGqHxl == KExITGqHxl){hhGrcdGQDL = true;}
      while(VQRfhcxJZN == VQRfhcxJZN){KWNZQwDBLP = true;}
      if(dGRYUwKGGJ == true){dGRYUwKGGJ = false;}
      if(jeRuUCgiMg == true){jeRuUCgiMg = false;}
      if(QBWoKGcOgo == true){QBWoKGcOgo = false;}
      if(VibZbDmXmX == true){VibZbDmXmX = false;}
      if(wkBmBqyVKf == true){wkBmBqyVKf = false;}
      if(wNxsxbibNO == true){wNxsxbibNO = false;}
      if(TwYRnBDrTR == true){TwYRnBDrTR = false;}
      if(PIwnkeAinT == true){PIwnkeAinT = false;}
      if(HHDBsIkhbA == true){HHDBsIkhbA = false;}
      if(TKKYEAMizA == true){TKKYEAMizA = false;}
      if(nGBsPmRIIR == true){nGBsPmRIIR = false;}
      if(azntHLrWYf == true){azntHLrWYf = false;}
      if(QUPTxEyXjj == true){QUPTxEyXjj = false;}
      if(SQjmeBFJkF == true){SQjmeBFJkF = false;}
      if(pbZKYTWQQr == true){pbZKYTWQQr = false;}
      if(HoKSjTphuL == true){HoKSjTphuL = false;}
      if(ntXXyJPAOF == true){ntXXyJPAOF = false;}
      if(GhlSonuFtd == true){GhlSonuFtd = false;}
      if(hhGrcdGQDL == true){hhGrcdGQDL = false;}
      if(KWNZQwDBLP == true){KWNZQwDBLP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SHEUKFOMSP
{ 
  void cyjkrgpLQG()
  { 
      bool CHGfaycuhd = false;
      bool kDzRYKPNIP = false;
      bool fLmYAtrXXt = false;
      bool qhxXiOlPwY = false;
      bool JkASmSrldw = false;
      bool YcHfuqTgeg = false;
      bool GEWmmDFahJ = false;
      bool YARiGuLUlh = false;
      bool BGtbVOaRcr = false;
      bool uEjPSENMfi = false;
      bool NRDTXYKXZA = false;
      bool ezuxezJtRY = false;
      bool cnxpOTPCPB = false;
      bool gyoCTjCaEw = false;
      bool DCqbMuImjS = false;
      bool tTtHFZTNED = false;
      bool JIIXTgJsdt = false;
      bool xipVUawUdS = false;
      bool KbRwHNEhwt = false;
      bool QoVBmttTIf = false;
      string YxjrrFCsTJ;
      string CGpgRGJrTP;
      string clzLCoCFNT;
      string PtQEqpIBys;
      string wJPwfRcaMG;
      string IEuTMmyYpD;
      string DwfAtIplpa;
      string xItZTTVCfj;
      string LasGKKywrD;
      string rjKuozcPBW;
      string bqklIAKVAs;
      string RusGqbDYoj;
      string KsslhNxzjT;
      string pFBIHTpHyJ;
      string AbwzlwqEDM;
      string uDZRMixyDu;
      string DLkfCLtjyX;
      string lwaeihxtzk;
      string VruWXlfiwY;
      string WqDCGnqPwa;
      if(YxjrrFCsTJ == bqklIAKVAs){CHGfaycuhd = true;}
      else if(bqklIAKVAs == YxjrrFCsTJ){NRDTXYKXZA = true;}
      if(CGpgRGJrTP == RusGqbDYoj){kDzRYKPNIP = true;}
      else if(RusGqbDYoj == CGpgRGJrTP){ezuxezJtRY = true;}
      if(clzLCoCFNT == KsslhNxzjT){fLmYAtrXXt = true;}
      else if(KsslhNxzjT == clzLCoCFNT){cnxpOTPCPB = true;}
      if(PtQEqpIBys == pFBIHTpHyJ){qhxXiOlPwY = true;}
      else if(pFBIHTpHyJ == PtQEqpIBys){gyoCTjCaEw = true;}
      if(wJPwfRcaMG == AbwzlwqEDM){JkASmSrldw = true;}
      else if(AbwzlwqEDM == wJPwfRcaMG){DCqbMuImjS = true;}
      if(IEuTMmyYpD == uDZRMixyDu){YcHfuqTgeg = true;}
      else if(uDZRMixyDu == IEuTMmyYpD){tTtHFZTNED = true;}
      if(DwfAtIplpa == DLkfCLtjyX){GEWmmDFahJ = true;}
      else if(DLkfCLtjyX == DwfAtIplpa){JIIXTgJsdt = true;}
      if(xItZTTVCfj == lwaeihxtzk){YARiGuLUlh = true;}
      if(LasGKKywrD == VruWXlfiwY){BGtbVOaRcr = true;}
      if(rjKuozcPBW == WqDCGnqPwa){uEjPSENMfi = true;}
      while(lwaeihxtzk == xItZTTVCfj){xipVUawUdS = true;}
      while(VruWXlfiwY == VruWXlfiwY){KbRwHNEhwt = true;}
      while(WqDCGnqPwa == WqDCGnqPwa){QoVBmttTIf = true;}
      if(CHGfaycuhd == true){CHGfaycuhd = false;}
      if(kDzRYKPNIP == true){kDzRYKPNIP = false;}
      if(fLmYAtrXXt == true){fLmYAtrXXt = false;}
      if(qhxXiOlPwY == true){qhxXiOlPwY = false;}
      if(JkASmSrldw == true){JkASmSrldw = false;}
      if(YcHfuqTgeg == true){YcHfuqTgeg = false;}
      if(GEWmmDFahJ == true){GEWmmDFahJ = false;}
      if(YARiGuLUlh == true){YARiGuLUlh = false;}
      if(BGtbVOaRcr == true){BGtbVOaRcr = false;}
      if(uEjPSENMfi == true){uEjPSENMfi = false;}
      if(NRDTXYKXZA == true){NRDTXYKXZA = false;}
      if(ezuxezJtRY == true){ezuxezJtRY = false;}
      if(cnxpOTPCPB == true){cnxpOTPCPB = false;}
      if(gyoCTjCaEw == true){gyoCTjCaEw = false;}
      if(DCqbMuImjS == true){DCqbMuImjS = false;}
      if(tTtHFZTNED == true){tTtHFZTNED = false;}
      if(JIIXTgJsdt == true){JIIXTgJsdt = false;}
      if(xipVUawUdS == true){xipVUawUdS = false;}
      if(KbRwHNEhwt == true){KbRwHNEhwt = false;}
      if(QoVBmttTIf == true){QoVBmttTIf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OGNAAAGGNV
{ 
  void CuEzKqbVxi()
  { 
      bool ncHuoppjwq = false;
      bool YUXRWGazrw = false;
      bool iYhtnquPad = false;
      bool heXOrsesMK = false;
      bool bWnWbbNWTj = false;
      bool XOrfyPtNHy = false;
      bool tZISItwJYc = false;
      bool aglhUMkKSL = false;
      bool dYwqFTlrPc = false;
      bool zQlOPBNVOg = false;
      bool eExpIpbKLk = false;
      bool diuuTUcRMo = false;
      bool IEsudJtXRS = false;
      bool zPwkfZbGhO = false;
      bool qagdyPVptu = false;
      bool XwJYXZKCMz = false;
      bool uEsrlOlJPt = false;
      bool sWjxxgXOxN = false;
      bool nEcWuCGWMF = false;
      bool OZsiTmhnri = false;
      string ARSFnyfyHa;
      string edGYFFdYrG;
      string AnaKwEYrkj;
      string lcmuhIhyUY;
      string jzbCEXXebM;
      string PoppcLqHJj;
      string ZmNWnBpKqx;
      string WeESWAMXGX;
      string fsQXUxmxSW;
      string RaojywlEOC;
      string hNndojjWTb;
      string ySAkDgVoCp;
      string NsqUfwpUTa;
      string NIJDpSElij;
      string NQcpXyZDfR;
      string ZwCYnoVTys;
      string sOCrNpJxuk;
      string bjGRbxPAwg;
      string VmnCARGjOB;
      string xknppyOkch;
      if(ARSFnyfyHa == hNndojjWTb){ncHuoppjwq = true;}
      else if(hNndojjWTb == ARSFnyfyHa){eExpIpbKLk = true;}
      if(edGYFFdYrG == ySAkDgVoCp){YUXRWGazrw = true;}
      else if(ySAkDgVoCp == edGYFFdYrG){diuuTUcRMo = true;}
      if(AnaKwEYrkj == NsqUfwpUTa){iYhtnquPad = true;}
      else if(NsqUfwpUTa == AnaKwEYrkj){IEsudJtXRS = true;}
      if(lcmuhIhyUY == NIJDpSElij){heXOrsesMK = true;}
      else if(NIJDpSElij == lcmuhIhyUY){zPwkfZbGhO = true;}
      if(jzbCEXXebM == NQcpXyZDfR){bWnWbbNWTj = true;}
      else if(NQcpXyZDfR == jzbCEXXebM){qagdyPVptu = true;}
      if(PoppcLqHJj == ZwCYnoVTys){XOrfyPtNHy = true;}
      else if(ZwCYnoVTys == PoppcLqHJj){XwJYXZKCMz = true;}
      if(ZmNWnBpKqx == sOCrNpJxuk){tZISItwJYc = true;}
      else if(sOCrNpJxuk == ZmNWnBpKqx){uEsrlOlJPt = true;}
      if(WeESWAMXGX == bjGRbxPAwg){aglhUMkKSL = true;}
      if(fsQXUxmxSW == VmnCARGjOB){dYwqFTlrPc = true;}
      if(RaojywlEOC == xknppyOkch){zQlOPBNVOg = true;}
      while(bjGRbxPAwg == WeESWAMXGX){sWjxxgXOxN = true;}
      while(VmnCARGjOB == VmnCARGjOB){nEcWuCGWMF = true;}
      while(xknppyOkch == xknppyOkch){OZsiTmhnri = true;}
      if(ncHuoppjwq == true){ncHuoppjwq = false;}
      if(YUXRWGazrw == true){YUXRWGazrw = false;}
      if(iYhtnquPad == true){iYhtnquPad = false;}
      if(heXOrsesMK == true){heXOrsesMK = false;}
      if(bWnWbbNWTj == true){bWnWbbNWTj = false;}
      if(XOrfyPtNHy == true){XOrfyPtNHy = false;}
      if(tZISItwJYc == true){tZISItwJYc = false;}
      if(aglhUMkKSL == true){aglhUMkKSL = false;}
      if(dYwqFTlrPc == true){dYwqFTlrPc = false;}
      if(zQlOPBNVOg == true){zQlOPBNVOg = false;}
      if(eExpIpbKLk == true){eExpIpbKLk = false;}
      if(diuuTUcRMo == true){diuuTUcRMo = false;}
      if(IEsudJtXRS == true){IEsudJtXRS = false;}
      if(zPwkfZbGhO == true){zPwkfZbGhO = false;}
      if(qagdyPVptu == true){qagdyPVptu = false;}
      if(XwJYXZKCMz == true){XwJYXZKCMz = false;}
      if(uEsrlOlJPt == true){uEsrlOlJPt = false;}
      if(sWjxxgXOxN == true){sWjxxgXOxN = false;}
      if(nEcWuCGWMF == true){nEcWuCGWMF = false;}
      if(OZsiTmhnri == true){OZsiTmhnri = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TRPLCRMUVD
{ 
  void RMZFZVkJcA()
  { 
      bool TZKIhNJLuX = false;
      bool sINYXqIqhQ = false;
      bool EEAtFtHawn = false;
      bool tknFHZBdXx = false;
      bool sAqKPtUDic = false;
      bool TwtCBPZQCm = false;
      bool GhOHdHTHRy = false;
      bool pdSkWEModL = false;
      bool ZDqSUyplDq = false;
      bool AjbkqLkjgH = false;
      bool aNlkmpcJex = false;
      bool DjlqNCqumf = false;
      bool QgDZxFChtL = false;
      bool SbIWkMRFfd = false;
      bool UgGFnPxkXn = false;
      bool ToxBpsJLng = false;
      bool muOTdabPFA = false;
      bool jkPIKjaxkh = false;
      bool HRJFqdeGfr = false;
      bool CGRypZRmbM = false;
      string KGlpfZhMWa;
      string oMLknGNoDR;
      string kENBOebzji;
      string QXzQdxQHsr;
      string uiCLoFDNfW;
      string itYZQFsjbB;
      string yhbmKQMtGq;
      string pFuKVCCBMJ;
      string aNTNAVyZAY;
      string DgfqtMGOBX;
      string sIGogcyNDO;
      string CqXSajOOmn;
      string SlshnIZDQJ;
      string umAnPRHdfW;
      string WkWlVLINQK;
      string yrbMFHPYBX;
      string DuxsTPqiCI;
      string cjiPQgOHLb;
      string ALlFKCLmiI;
      string ChcHTbmcSF;
      if(KGlpfZhMWa == sIGogcyNDO){TZKIhNJLuX = true;}
      else if(sIGogcyNDO == KGlpfZhMWa){aNlkmpcJex = true;}
      if(oMLknGNoDR == CqXSajOOmn){sINYXqIqhQ = true;}
      else if(CqXSajOOmn == oMLknGNoDR){DjlqNCqumf = true;}
      if(kENBOebzji == SlshnIZDQJ){EEAtFtHawn = true;}
      else if(SlshnIZDQJ == kENBOebzji){QgDZxFChtL = true;}
      if(QXzQdxQHsr == umAnPRHdfW){tknFHZBdXx = true;}
      else if(umAnPRHdfW == QXzQdxQHsr){SbIWkMRFfd = true;}
      if(uiCLoFDNfW == WkWlVLINQK){sAqKPtUDic = true;}
      else if(WkWlVLINQK == uiCLoFDNfW){UgGFnPxkXn = true;}
      if(itYZQFsjbB == yrbMFHPYBX){TwtCBPZQCm = true;}
      else if(yrbMFHPYBX == itYZQFsjbB){ToxBpsJLng = true;}
      if(yhbmKQMtGq == DuxsTPqiCI){GhOHdHTHRy = true;}
      else if(DuxsTPqiCI == yhbmKQMtGq){muOTdabPFA = true;}
      if(pFuKVCCBMJ == cjiPQgOHLb){pdSkWEModL = true;}
      if(aNTNAVyZAY == ALlFKCLmiI){ZDqSUyplDq = true;}
      if(DgfqtMGOBX == ChcHTbmcSF){AjbkqLkjgH = true;}
      while(cjiPQgOHLb == pFuKVCCBMJ){jkPIKjaxkh = true;}
      while(ALlFKCLmiI == ALlFKCLmiI){HRJFqdeGfr = true;}
      while(ChcHTbmcSF == ChcHTbmcSF){CGRypZRmbM = true;}
      if(TZKIhNJLuX == true){TZKIhNJLuX = false;}
      if(sINYXqIqhQ == true){sINYXqIqhQ = false;}
      if(EEAtFtHawn == true){EEAtFtHawn = false;}
      if(tknFHZBdXx == true){tknFHZBdXx = false;}
      if(sAqKPtUDic == true){sAqKPtUDic = false;}
      if(TwtCBPZQCm == true){TwtCBPZQCm = false;}
      if(GhOHdHTHRy == true){GhOHdHTHRy = false;}
      if(pdSkWEModL == true){pdSkWEModL = false;}
      if(ZDqSUyplDq == true){ZDqSUyplDq = false;}
      if(AjbkqLkjgH == true){AjbkqLkjgH = false;}
      if(aNlkmpcJex == true){aNlkmpcJex = false;}
      if(DjlqNCqumf == true){DjlqNCqumf = false;}
      if(QgDZxFChtL == true){QgDZxFChtL = false;}
      if(SbIWkMRFfd == true){SbIWkMRFfd = false;}
      if(UgGFnPxkXn == true){UgGFnPxkXn = false;}
      if(ToxBpsJLng == true){ToxBpsJLng = false;}
      if(muOTdabPFA == true){muOTdabPFA = false;}
      if(jkPIKjaxkh == true){jkPIKjaxkh = false;}
      if(HRJFqdeGfr == true){HRJFqdeGfr = false;}
      if(CGRypZRmbM == true){CGRypZRmbM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PEOPYVAXOV
{ 
  void TRmhFHfIjk()
  { 
      bool AgGnZDAGbV = false;
      bool kaOxTpxkKF = false;
      bool PGwFZZzEPD = false;
      bool OwUnoMEsZD = false;
      bool cfmFzaLARw = false;
      bool wcihqtjBOA = false;
      bool DwqYGoFZHH = false;
      bool kELGciSpFy = false;
      bool OymSHlMmwu = false;
      bool bDeYzfoOyK = false;
      bool VkrKLqQbFI = false;
      bool atuPlFJXRU = false;
      bool bRcMegZlHw = false;
      bool tEquccGbHP = false;
      bool UjhnThIPmt = false;
      bool WQxdhDHfed = false;
      bool ReUIOWCAlI = false;
      bool ygQBArjorx = false;
      bool YJzMYcHNMZ = false;
      bool VawcypOYZx = false;
      string ixLEWRrTKe;
      string sldTRCFPim;
      string flDMJLfaUU;
      string GGybFZBunx;
      string yeoTLSNdqL;
      string UEwMDwsytK;
      string lRyoYlnBOr;
      string AKaknAwjAq;
      string xBjJzCKkXJ;
      string fCAcLgfzuZ;
      string eMPyKKcKYC;
      string zJyDMkgopV;
      string bCcFLxJxZG;
      string UwnZMkkkyn;
      string YzMUJVExQZ;
      string zqJYybiKmM;
      string BekRhCVXpb;
      string AwpCxcpHup;
      string sLgzGcmObk;
      string CZxllsNtmG;
      if(ixLEWRrTKe == eMPyKKcKYC){AgGnZDAGbV = true;}
      else if(eMPyKKcKYC == ixLEWRrTKe){VkrKLqQbFI = true;}
      if(sldTRCFPim == zJyDMkgopV){kaOxTpxkKF = true;}
      else if(zJyDMkgopV == sldTRCFPim){atuPlFJXRU = true;}
      if(flDMJLfaUU == bCcFLxJxZG){PGwFZZzEPD = true;}
      else if(bCcFLxJxZG == flDMJLfaUU){bRcMegZlHw = true;}
      if(GGybFZBunx == UwnZMkkkyn){OwUnoMEsZD = true;}
      else if(UwnZMkkkyn == GGybFZBunx){tEquccGbHP = true;}
      if(yeoTLSNdqL == YzMUJVExQZ){cfmFzaLARw = true;}
      else if(YzMUJVExQZ == yeoTLSNdqL){UjhnThIPmt = true;}
      if(UEwMDwsytK == zqJYybiKmM){wcihqtjBOA = true;}
      else if(zqJYybiKmM == UEwMDwsytK){WQxdhDHfed = true;}
      if(lRyoYlnBOr == BekRhCVXpb){DwqYGoFZHH = true;}
      else if(BekRhCVXpb == lRyoYlnBOr){ReUIOWCAlI = true;}
      if(AKaknAwjAq == AwpCxcpHup){kELGciSpFy = true;}
      if(xBjJzCKkXJ == sLgzGcmObk){OymSHlMmwu = true;}
      if(fCAcLgfzuZ == CZxllsNtmG){bDeYzfoOyK = true;}
      while(AwpCxcpHup == AKaknAwjAq){ygQBArjorx = true;}
      while(sLgzGcmObk == sLgzGcmObk){YJzMYcHNMZ = true;}
      while(CZxllsNtmG == CZxllsNtmG){VawcypOYZx = true;}
      if(AgGnZDAGbV == true){AgGnZDAGbV = false;}
      if(kaOxTpxkKF == true){kaOxTpxkKF = false;}
      if(PGwFZZzEPD == true){PGwFZZzEPD = false;}
      if(OwUnoMEsZD == true){OwUnoMEsZD = false;}
      if(cfmFzaLARw == true){cfmFzaLARw = false;}
      if(wcihqtjBOA == true){wcihqtjBOA = false;}
      if(DwqYGoFZHH == true){DwqYGoFZHH = false;}
      if(kELGciSpFy == true){kELGciSpFy = false;}
      if(OymSHlMmwu == true){OymSHlMmwu = false;}
      if(bDeYzfoOyK == true){bDeYzfoOyK = false;}
      if(VkrKLqQbFI == true){VkrKLqQbFI = false;}
      if(atuPlFJXRU == true){atuPlFJXRU = false;}
      if(bRcMegZlHw == true){bRcMegZlHw = false;}
      if(tEquccGbHP == true){tEquccGbHP = false;}
      if(UjhnThIPmt == true){UjhnThIPmt = false;}
      if(WQxdhDHfed == true){WQxdhDHfed = false;}
      if(ReUIOWCAlI == true){ReUIOWCAlI = false;}
      if(ygQBArjorx == true){ygQBArjorx = false;}
      if(YJzMYcHNMZ == true){YJzMYcHNMZ = false;}
      if(VawcypOYZx == true){VawcypOYZx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZOLEDSXQMQ
{ 
  void WhbKQFGxkB()
  { 
      bool VbNiIwpxxi = false;
      bool MLzjnLcXPH = false;
      bool CkxexdgzGB = false;
      bool fZFjHPEaCr = false;
      bool ZQMFZLoDKG = false;
      bool mjTfZjdikd = false;
      bool PpquCmFPcX = false;
      bool HBUWhkXqEk = false;
      bool ocoAOwFZJW = false;
      bool kVpYcjZRDm = false;
      bool GZalykPwyn = false;
      bool LmezolBpgF = false;
      bool gfGFmlLwty = false;
      bool LGmQePCCBc = false;
      bool gIaUKypqip = false;
      bool iikxFaTVzM = false;
      bool ZSBAcFzNUZ = false;
      bool jyoEYYEktn = false;
      bool uTMEObVoLD = false;
      bool ufDoCNHaqF = false;
      string tzTrdknFws;
      string KCejBoMBTW;
      string YNTHoswEPC;
      string TSHjdSXIlk;
      string ZFkJtNFarB;
      string ePFIwfeLCk;
      string ojosYrutGi;
      string QDOixTcJNb;
      string mULNXDMzny;
      string mLGBupPqjB;
      string SKUJjaAVLb;
      string CVyaxTXbUU;
      string ewFHuFxNmG;
      string EkZLIbACdw;
      string DpmLuRNeDb;
      string RnWOWVEMNe;
      string dmiEXRulRU;
      string SVyYRnIsMd;
      string qRJLnPOKom;
      string WnnyRQHinc;
      if(tzTrdknFws == SKUJjaAVLb){VbNiIwpxxi = true;}
      else if(SKUJjaAVLb == tzTrdknFws){GZalykPwyn = true;}
      if(KCejBoMBTW == CVyaxTXbUU){MLzjnLcXPH = true;}
      else if(CVyaxTXbUU == KCejBoMBTW){LmezolBpgF = true;}
      if(YNTHoswEPC == ewFHuFxNmG){CkxexdgzGB = true;}
      else if(ewFHuFxNmG == YNTHoswEPC){gfGFmlLwty = true;}
      if(TSHjdSXIlk == EkZLIbACdw){fZFjHPEaCr = true;}
      else if(EkZLIbACdw == TSHjdSXIlk){LGmQePCCBc = true;}
      if(ZFkJtNFarB == DpmLuRNeDb){ZQMFZLoDKG = true;}
      else if(DpmLuRNeDb == ZFkJtNFarB){gIaUKypqip = true;}
      if(ePFIwfeLCk == RnWOWVEMNe){mjTfZjdikd = true;}
      else if(RnWOWVEMNe == ePFIwfeLCk){iikxFaTVzM = true;}
      if(ojosYrutGi == dmiEXRulRU){PpquCmFPcX = true;}
      else if(dmiEXRulRU == ojosYrutGi){ZSBAcFzNUZ = true;}
      if(QDOixTcJNb == SVyYRnIsMd){HBUWhkXqEk = true;}
      if(mULNXDMzny == qRJLnPOKom){ocoAOwFZJW = true;}
      if(mLGBupPqjB == WnnyRQHinc){kVpYcjZRDm = true;}
      while(SVyYRnIsMd == QDOixTcJNb){jyoEYYEktn = true;}
      while(qRJLnPOKom == qRJLnPOKom){uTMEObVoLD = true;}
      while(WnnyRQHinc == WnnyRQHinc){ufDoCNHaqF = true;}
      if(VbNiIwpxxi == true){VbNiIwpxxi = false;}
      if(MLzjnLcXPH == true){MLzjnLcXPH = false;}
      if(CkxexdgzGB == true){CkxexdgzGB = false;}
      if(fZFjHPEaCr == true){fZFjHPEaCr = false;}
      if(ZQMFZLoDKG == true){ZQMFZLoDKG = false;}
      if(mjTfZjdikd == true){mjTfZjdikd = false;}
      if(PpquCmFPcX == true){PpquCmFPcX = false;}
      if(HBUWhkXqEk == true){HBUWhkXqEk = false;}
      if(ocoAOwFZJW == true){ocoAOwFZJW = false;}
      if(kVpYcjZRDm == true){kVpYcjZRDm = false;}
      if(GZalykPwyn == true){GZalykPwyn = false;}
      if(LmezolBpgF == true){LmezolBpgF = false;}
      if(gfGFmlLwty == true){gfGFmlLwty = false;}
      if(LGmQePCCBc == true){LGmQePCCBc = false;}
      if(gIaUKypqip == true){gIaUKypqip = false;}
      if(iikxFaTVzM == true){iikxFaTVzM = false;}
      if(ZSBAcFzNUZ == true){ZSBAcFzNUZ = false;}
      if(jyoEYYEktn == true){jyoEYYEktn = false;}
      if(uTMEObVoLD == true){uTMEObVoLD = false;}
      if(ufDoCNHaqF == true){ufDoCNHaqF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UQGRVJXMMB
{ 
  void FSsuFGZdiB()
  { 
      bool uuaFFeuOXG = false;
      bool UANAdOCIlA = false;
      bool gLeIrkZtiV = false;
      bool RDuOpqZYSb = false;
      bool DXNIhnhnat = false;
      bool SPMArjQSNU = false;
      bool EBeCnRFyJm = false;
      bool odoKxJxVaE = false;
      bool CkSoCCpuWG = false;
      bool aHLyWCrKTP = false;
      bool iidmEoZBDi = false;
      bool ltrJRShpzl = false;
      bool aKbCMgSpmt = false;
      bool RmBKUTGejN = false;
      bool bnqnUgPCgD = false;
      bool UBLhoYHbaW = false;
      bool WjNIQzrhnx = false;
      bool LCFlJlSnhf = false;
      bool RPJjZPaTUw = false;
      bool LeEMprZhWV = false;
      string QmrLYKITqZ;
      string zlsVZfOewu;
      string LlZiiXBchw;
      string ZJIziEGBGX;
      string NBTLfsoUkS;
      string RWOYEdMJbB;
      string JfkuzoctlU;
      string YNXYgKRNCp;
      string hfqPdDtiuF;
      string qwYFOhQYMq;
      string PuiPsEzprt;
      string MyGlScoVRw;
      string tsygdcnRJz;
      string tsBLZlxaVY;
      string DEqBrrpmmk;
      string stGPwWxBlQ;
      string PhfrASxtLg;
      string fOzrrpBwnl;
      string lBeXGzlkPD;
      string nunFIVXyBY;
      if(QmrLYKITqZ == PuiPsEzprt){uuaFFeuOXG = true;}
      else if(PuiPsEzprt == QmrLYKITqZ){iidmEoZBDi = true;}
      if(zlsVZfOewu == MyGlScoVRw){UANAdOCIlA = true;}
      else if(MyGlScoVRw == zlsVZfOewu){ltrJRShpzl = true;}
      if(LlZiiXBchw == tsygdcnRJz){gLeIrkZtiV = true;}
      else if(tsygdcnRJz == LlZiiXBchw){aKbCMgSpmt = true;}
      if(ZJIziEGBGX == tsBLZlxaVY){RDuOpqZYSb = true;}
      else if(tsBLZlxaVY == ZJIziEGBGX){RmBKUTGejN = true;}
      if(NBTLfsoUkS == DEqBrrpmmk){DXNIhnhnat = true;}
      else if(DEqBrrpmmk == NBTLfsoUkS){bnqnUgPCgD = true;}
      if(RWOYEdMJbB == stGPwWxBlQ){SPMArjQSNU = true;}
      else if(stGPwWxBlQ == RWOYEdMJbB){UBLhoYHbaW = true;}
      if(JfkuzoctlU == PhfrASxtLg){EBeCnRFyJm = true;}
      else if(PhfrASxtLg == JfkuzoctlU){WjNIQzrhnx = true;}
      if(YNXYgKRNCp == fOzrrpBwnl){odoKxJxVaE = true;}
      if(hfqPdDtiuF == lBeXGzlkPD){CkSoCCpuWG = true;}
      if(qwYFOhQYMq == nunFIVXyBY){aHLyWCrKTP = true;}
      while(fOzrrpBwnl == YNXYgKRNCp){LCFlJlSnhf = true;}
      while(lBeXGzlkPD == lBeXGzlkPD){RPJjZPaTUw = true;}
      while(nunFIVXyBY == nunFIVXyBY){LeEMprZhWV = true;}
      if(uuaFFeuOXG == true){uuaFFeuOXG = false;}
      if(UANAdOCIlA == true){UANAdOCIlA = false;}
      if(gLeIrkZtiV == true){gLeIrkZtiV = false;}
      if(RDuOpqZYSb == true){RDuOpqZYSb = false;}
      if(DXNIhnhnat == true){DXNIhnhnat = false;}
      if(SPMArjQSNU == true){SPMArjQSNU = false;}
      if(EBeCnRFyJm == true){EBeCnRFyJm = false;}
      if(odoKxJxVaE == true){odoKxJxVaE = false;}
      if(CkSoCCpuWG == true){CkSoCCpuWG = false;}
      if(aHLyWCrKTP == true){aHLyWCrKTP = false;}
      if(iidmEoZBDi == true){iidmEoZBDi = false;}
      if(ltrJRShpzl == true){ltrJRShpzl = false;}
      if(aKbCMgSpmt == true){aKbCMgSpmt = false;}
      if(RmBKUTGejN == true){RmBKUTGejN = false;}
      if(bnqnUgPCgD == true){bnqnUgPCgD = false;}
      if(UBLhoYHbaW == true){UBLhoYHbaW = false;}
      if(WjNIQzrhnx == true){WjNIQzrhnx = false;}
      if(LCFlJlSnhf == true){LCFlJlSnhf = false;}
      if(RPJjZPaTUw == true){RPJjZPaTUw = false;}
      if(LeEMprZhWV == true){LeEMprZhWV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YMSIZQNNXM
{ 
  void FMCGpEKzBC()
  { 
      bool UuocwEKQgb = false;
      bool iJcJLDzjyz = false;
      bool CDoMRPRznf = false;
      bool lJyjpjkzpF = false;
      bool dzEtjXfDKT = false;
      bool EIBayQGbKf = false;
      bool mKbBoZKsTa = false;
      bool RAtsUCzubs = false;
      bool jOoTacHXkY = false;
      bool dInKSTXCEK = false;
      bool NmjiBEOHFw = false;
      bool RLARuXVHZL = false;
      bool SmHtxJLiaB = false;
      bool ewpQfxdFSW = false;
      bool OzRoGSHWOt = false;
      bool xPcrraeolr = false;
      bool segERVUiky = false;
      bool tQoCxSUSme = false;
      bool BnUgDOSxYF = false;
      bool RoTZdiSMXk = false;
      string NXKoVoQVCa;
      string zfgOuEysoW;
      string WQxjTTygyN;
      string uFBUcaWltL;
      string glfNzrhFJJ;
      string lfIquwaZVB;
      string qjWoetdMkU;
      string hMycokjjja;
      string lrWnaOwKYf;
      string AwQrUwOqhF;
      string NVTobZhfBK;
      string MqptPyMhNQ;
      string xTmFTkwFIs;
      string VsCeNPYhMB;
      string gQJOTJGVcV;
      string ifcQIshOUp;
      string dbWInSnLgz;
      string ZeVMjfKYkK;
      string eZclJoQkVT;
      string hJNVXEsAZB;
      if(NXKoVoQVCa == NVTobZhfBK){UuocwEKQgb = true;}
      else if(NVTobZhfBK == NXKoVoQVCa){NmjiBEOHFw = true;}
      if(zfgOuEysoW == MqptPyMhNQ){iJcJLDzjyz = true;}
      else if(MqptPyMhNQ == zfgOuEysoW){RLARuXVHZL = true;}
      if(WQxjTTygyN == xTmFTkwFIs){CDoMRPRznf = true;}
      else if(xTmFTkwFIs == WQxjTTygyN){SmHtxJLiaB = true;}
      if(uFBUcaWltL == VsCeNPYhMB){lJyjpjkzpF = true;}
      else if(VsCeNPYhMB == uFBUcaWltL){ewpQfxdFSW = true;}
      if(glfNzrhFJJ == gQJOTJGVcV){dzEtjXfDKT = true;}
      else if(gQJOTJGVcV == glfNzrhFJJ){OzRoGSHWOt = true;}
      if(lfIquwaZVB == ifcQIshOUp){EIBayQGbKf = true;}
      else if(ifcQIshOUp == lfIquwaZVB){xPcrraeolr = true;}
      if(qjWoetdMkU == dbWInSnLgz){mKbBoZKsTa = true;}
      else if(dbWInSnLgz == qjWoetdMkU){segERVUiky = true;}
      if(hMycokjjja == ZeVMjfKYkK){RAtsUCzubs = true;}
      if(lrWnaOwKYf == eZclJoQkVT){jOoTacHXkY = true;}
      if(AwQrUwOqhF == hJNVXEsAZB){dInKSTXCEK = true;}
      while(ZeVMjfKYkK == hMycokjjja){tQoCxSUSme = true;}
      while(eZclJoQkVT == eZclJoQkVT){BnUgDOSxYF = true;}
      while(hJNVXEsAZB == hJNVXEsAZB){RoTZdiSMXk = true;}
      if(UuocwEKQgb == true){UuocwEKQgb = false;}
      if(iJcJLDzjyz == true){iJcJLDzjyz = false;}
      if(CDoMRPRznf == true){CDoMRPRznf = false;}
      if(lJyjpjkzpF == true){lJyjpjkzpF = false;}
      if(dzEtjXfDKT == true){dzEtjXfDKT = false;}
      if(EIBayQGbKf == true){EIBayQGbKf = false;}
      if(mKbBoZKsTa == true){mKbBoZKsTa = false;}
      if(RAtsUCzubs == true){RAtsUCzubs = false;}
      if(jOoTacHXkY == true){jOoTacHXkY = false;}
      if(dInKSTXCEK == true){dInKSTXCEK = false;}
      if(NmjiBEOHFw == true){NmjiBEOHFw = false;}
      if(RLARuXVHZL == true){RLARuXVHZL = false;}
      if(SmHtxJLiaB == true){SmHtxJLiaB = false;}
      if(ewpQfxdFSW == true){ewpQfxdFSW = false;}
      if(OzRoGSHWOt == true){OzRoGSHWOt = false;}
      if(xPcrraeolr == true){xPcrraeolr = false;}
      if(segERVUiky == true){segERVUiky = false;}
      if(tQoCxSUSme == true){tQoCxSUSme = false;}
      if(BnUgDOSxYF == true){BnUgDOSxYF = false;}
      if(RoTZdiSMXk == true){RoTZdiSMXk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMNQSFHULM
{ 
  void iCRPxLnQKM()
  { 
      bool IIwXaGbEIH = false;
      bool KpPjMhwBOJ = false;
      bool wjhlpurcTn = false;
      bool VIUgeOBOgM = false;
      bool QINXDVgRKs = false;
      bool cHNUQYZJhe = false;
      bool NzkUkBVhFy = false;
      bool ghTBrmVJiU = false;
      bool NaSZKOuAQF = false;
      bool nqgByRXrmB = false;
      bool AzMLLumLbd = false;
      bool CQZNRmfKJV = false;
      bool FURzJpBRDa = false;
      bool OdVgTONGNP = false;
      bool aiYlDXQTjL = false;
      bool kMiRuegMBV = false;
      bool sVIAOYtssC = false;
      bool YZxttWweul = false;
      bool YhgroCuEko = false;
      bool gAEqVFZXXe = false;
      string rsOTFyCyof;
      string cWLpKbOGqd;
      string eFJhHbRkGE;
      string BeJcfwgQKy;
      string manXgFDjmW;
      string WsctZmjfLd;
      string gRqkdyMhJN;
      string tyuspDQkAC;
      string XgxjgHBPCs;
      string MBEgRUiDsi;
      string sVaYcYyjDW;
      string WyeIFzTHDW;
      string wxeQBrsOaU;
      string UNrRJCGYHH;
      string JRLfVOVuaS;
      string BbzVlwpJWj;
      string fiIhCJFNzD;
      string rtAuNelztm;
      string WxmHTrNVfN;
      string MxBWbZIcdM;
      if(rsOTFyCyof == sVaYcYyjDW){IIwXaGbEIH = true;}
      else if(sVaYcYyjDW == rsOTFyCyof){AzMLLumLbd = true;}
      if(cWLpKbOGqd == WyeIFzTHDW){KpPjMhwBOJ = true;}
      else if(WyeIFzTHDW == cWLpKbOGqd){CQZNRmfKJV = true;}
      if(eFJhHbRkGE == wxeQBrsOaU){wjhlpurcTn = true;}
      else if(wxeQBrsOaU == eFJhHbRkGE){FURzJpBRDa = true;}
      if(BeJcfwgQKy == UNrRJCGYHH){VIUgeOBOgM = true;}
      else if(UNrRJCGYHH == BeJcfwgQKy){OdVgTONGNP = true;}
      if(manXgFDjmW == JRLfVOVuaS){QINXDVgRKs = true;}
      else if(JRLfVOVuaS == manXgFDjmW){aiYlDXQTjL = true;}
      if(WsctZmjfLd == BbzVlwpJWj){cHNUQYZJhe = true;}
      else if(BbzVlwpJWj == WsctZmjfLd){kMiRuegMBV = true;}
      if(gRqkdyMhJN == fiIhCJFNzD){NzkUkBVhFy = true;}
      else if(fiIhCJFNzD == gRqkdyMhJN){sVIAOYtssC = true;}
      if(tyuspDQkAC == rtAuNelztm){ghTBrmVJiU = true;}
      if(XgxjgHBPCs == WxmHTrNVfN){NaSZKOuAQF = true;}
      if(MBEgRUiDsi == MxBWbZIcdM){nqgByRXrmB = true;}
      while(rtAuNelztm == tyuspDQkAC){YZxttWweul = true;}
      while(WxmHTrNVfN == WxmHTrNVfN){YhgroCuEko = true;}
      while(MxBWbZIcdM == MxBWbZIcdM){gAEqVFZXXe = true;}
      if(IIwXaGbEIH == true){IIwXaGbEIH = false;}
      if(KpPjMhwBOJ == true){KpPjMhwBOJ = false;}
      if(wjhlpurcTn == true){wjhlpurcTn = false;}
      if(VIUgeOBOgM == true){VIUgeOBOgM = false;}
      if(QINXDVgRKs == true){QINXDVgRKs = false;}
      if(cHNUQYZJhe == true){cHNUQYZJhe = false;}
      if(NzkUkBVhFy == true){NzkUkBVhFy = false;}
      if(ghTBrmVJiU == true){ghTBrmVJiU = false;}
      if(NaSZKOuAQF == true){NaSZKOuAQF = false;}
      if(nqgByRXrmB == true){nqgByRXrmB = false;}
      if(AzMLLumLbd == true){AzMLLumLbd = false;}
      if(CQZNRmfKJV == true){CQZNRmfKJV = false;}
      if(FURzJpBRDa == true){FURzJpBRDa = false;}
      if(OdVgTONGNP == true){OdVgTONGNP = false;}
      if(aiYlDXQTjL == true){aiYlDXQTjL = false;}
      if(kMiRuegMBV == true){kMiRuegMBV = false;}
      if(sVIAOYtssC == true){sVIAOYtssC = false;}
      if(YZxttWweul == true){YZxttWweul = false;}
      if(YhgroCuEko == true){YhgroCuEko = false;}
      if(gAEqVFZXXe == true){gAEqVFZXXe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDHOBNHGUU
{ 
  void klpuzuxbba()
  { 
      bool lGJOfXApSp = false;
      bool uUgVSCKMAk = false;
      bool zdHptSoMek = false;
      bool EucbMbtFUJ = false;
      bool JDazacDIYA = false;
      bool HCcsTIyTTM = false;
      bool inLglArFIp = false;
      bool HFrqauCHPR = false;
      bool PfmddCRjHE = false;
      bool dakHZVrsNZ = false;
      bool jyzhrBJlRX = false;
      bool FpEBxCAgDi = false;
      bool iIxEMgUkQF = false;
      bool DJtohQgFlb = false;
      bool sfRizmViJX = false;
      bool UKoeqbAuUK = false;
      bool gYULUuwOTf = false;
      bool UuubpCpOEZ = false;
      bool LlarjsTOyF = false;
      bool QljauTLFOD = false;
      string izBFWeGzOR;
      string sDkBgGdgHj;
      string EmUrEROLRc;
      string LRCQUbNbfS;
      string DkCeiGfQih;
      string jHnkewdIBF;
      string PthkFaBUfF;
      string rBBnfSjpJx;
      string lxcirDcQlY;
      string xEaaCIDQYH;
      string FKjcohFzFL;
      string LnzESRRyrC;
      string xjhHInaalX;
      string PSQBqaNzsK;
      string xcLaMJFWHk;
      string pFYWKUcbUB;
      string HeNgwsWyMr;
      string ESEhETYHuz;
      string iETAgKtspW;
      string xkdrDSPdeT;
      if(izBFWeGzOR == FKjcohFzFL){lGJOfXApSp = true;}
      else if(FKjcohFzFL == izBFWeGzOR){jyzhrBJlRX = true;}
      if(sDkBgGdgHj == LnzESRRyrC){uUgVSCKMAk = true;}
      else if(LnzESRRyrC == sDkBgGdgHj){FpEBxCAgDi = true;}
      if(EmUrEROLRc == xjhHInaalX){zdHptSoMek = true;}
      else if(xjhHInaalX == EmUrEROLRc){iIxEMgUkQF = true;}
      if(LRCQUbNbfS == PSQBqaNzsK){EucbMbtFUJ = true;}
      else if(PSQBqaNzsK == LRCQUbNbfS){DJtohQgFlb = true;}
      if(DkCeiGfQih == xcLaMJFWHk){JDazacDIYA = true;}
      else if(xcLaMJFWHk == DkCeiGfQih){sfRizmViJX = true;}
      if(jHnkewdIBF == pFYWKUcbUB){HCcsTIyTTM = true;}
      else if(pFYWKUcbUB == jHnkewdIBF){UKoeqbAuUK = true;}
      if(PthkFaBUfF == HeNgwsWyMr){inLglArFIp = true;}
      else if(HeNgwsWyMr == PthkFaBUfF){gYULUuwOTf = true;}
      if(rBBnfSjpJx == ESEhETYHuz){HFrqauCHPR = true;}
      if(lxcirDcQlY == iETAgKtspW){PfmddCRjHE = true;}
      if(xEaaCIDQYH == xkdrDSPdeT){dakHZVrsNZ = true;}
      while(ESEhETYHuz == rBBnfSjpJx){UuubpCpOEZ = true;}
      while(iETAgKtspW == iETAgKtspW){LlarjsTOyF = true;}
      while(xkdrDSPdeT == xkdrDSPdeT){QljauTLFOD = true;}
      if(lGJOfXApSp == true){lGJOfXApSp = false;}
      if(uUgVSCKMAk == true){uUgVSCKMAk = false;}
      if(zdHptSoMek == true){zdHptSoMek = false;}
      if(EucbMbtFUJ == true){EucbMbtFUJ = false;}
      if(JDazacDIYA == true){JDazacDIYA = false;}
      if(HCcsTIyTTM == true){HCcsTIyTTM = false;}
      if(inLglArFIp == true){inLglArFIp = false;}
      if(HFrqauCHPR == true){HFrqauCHPR = false;}
      if(PfmddCRjHE == true){PfmddCRjHE = false;}
      if(dakHZVrsNZ == true){dakHZVrsNZ = false;}
      if(jyzhrBJlRX == true){jyzhrBJlRX = false;}
      if(FpEBxCAgDi == true){FpEBxCAgDi = false;}
      if(iIxEMgUkQF == true){iIxEMgUkQF = false;}
      if(DJtohQgFlb == true){DJtohQgFlb = false;}
      if(sfRizmViJX == true){sfRizmViJX = false;}
      if(UKoeqbAuUK == true){UKoeqbAuUK = false;}
      if(gYULUuwOTf == true){gYULUuwOTf = false;}
      if(UuubpCpOEZ == true){UuubpCpOEZ = false;}
      if(LlarjsTOyF == true){LlarjsTOyF = false;}
      if(QljauTLFOD == true){QljauTLFOD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QPTSWTFSEV
{ 
  void NbNmWgOROm()
  { 
      bool WgSfQTfONo = false;
      bool TwmgfuXedw = false;
      bool hEeCRObhFg = false;
      bool teTPkVzZQr = false;
      bool YkPqEgWZZd = false;
      bool UYSqdRCQNC = false;
      bool rxIguncXwJ = false;
      bool wxNlWxnmxk = false;
      bool qCHbMVLckS = false;
      bool TiLOzbciwP = false;
      bool DydPhWKgTg = false;
      bool cOScKopfTZ = false;
      bool bzmcpMlzlu = false;
      bool UEqhgsYrto = false;
      bool KeIDpEPiDK = false;
      bool kwPWmELAYU = false;
      bool jKtYLYWkuR = false;
      bool QyleOxpimk = false;
      bool xDwbJYoUtc = false;
      bool hXSZEzkjqR = false;
      string jSmcCHzWVO;
      string ONXzZsNCLR;
      string UBQmCruTWn;
      string iyDMEHYNPz;
      string QxuPRWKhUB;
      string ZzwIxhBAZK;
      string LezgfQKKtS;
      string UAmLBWGBUf;
      string gNyVNiBtOW;
      string FXnFnkxNjB;
      string LzmCfZMkGa;
      string aAetcyfdTw;
      string OPuXMwLhXQ;
      string YsRTTgZwon;
      string WQnnuFssbo;
      string ETtmmuDPoi;
      string NdMpBhiLZu;
      string XjneZxbHbH;
      string DSGhLFzdfX;
      string cJHGZrDxmM;
      if(jSmcCHzWVO == LzmCfZMkGa){WgSfQTfONo = true;}
      else if(LzmCfZMkGa == jSmcCHzWVO){DydPhWKgTg = true;}
      if(ONXzZsNCLR == aAetcyfdTw){TwmgfuXedw = true;}
      else if(aAetcyfdTw == ONXzZsNCLR){cOScKopfTZ = true;}
      if(UBQmCruTWn == OPuXMwLhXQ){hEeCRObhFg = true;}
      else if(OPuXMwLhXQ == UBQmCruTWn){bzmcpMlzlu = true;}
      if(iyDMEHYNPz == YsRTTgZwon){teTPkVzZQr = true;}
      else if(YsRTTgZwon == iyDMEHYNPz){UEqhgsYrto = true;}
      if(QxuPRWKhUB == WQnnuFssbo){YkPqEgWZZd = true;}
      else if(WQnnuFssbo == QxuPRWKhUB){KeIDpEPiDK = true;}
      if(ZzwIxhBAZK == ETtmmuDPoi){UYSqdRCQNC = true;}
      else if(ETtmmuDPoi == ZzwIxhBAZK){kwPWmELAYU = true;}
      if(LezgfQKKtS == NdMpBhiLZu){rxIguncXwJ = true;}
      else if(NdMpBhiLZu == LezgfQKKtS){jKtYLYWkuR = true;}
      if(UAmLBWGBUf == XjneZxbHbH){wxNlWxnmxk = true;}
      if(gNyVNiBtOW == DSGhLFzdfX){qCHbMVLckS = true;}
      if(FXnFnkxNjB == cJHGZrDxmM){TiLOzbciwP = true;}
      while(XjneZxbHbH == UAmLBWGBUf){QyleOxpimk = true;}
      while(DSGhLFzdfX == DSGhLFzdfX){xDwbJYoUtc = true;}
      while(cJHGZrDxmM == cJHGZrDxmM){hXSZEzkjqR = true;}
      if(WgSfQTfONo == true){WgSfQTfONo = false;}
      if(TwmgfuXedw == true){TwmgfuXedw = false;}
      if(hEeCRObhFg == true){hEeCRObhFg = false;}
      if(teTPkVzZQr == true){teTPkVzZQr = false;}
      if(YkPqEgWZZd == true){YkPqEgWZZd = false;}
      if(UYSqdRCQNC == true){UYSqdRCQNC = false;}
      if(rxIguncXwJ == true){rxIguncXwJ = false;}
      if(wxNlWxnmxk == true){wxNlWxnmxk = false;}
      if(qCHbMVLckS == true){qCHbMVLckS = false;}
      if(TiLOzbciwP == true){TiLOzbciwP = false;}
      if(DydPhWKgTg == true){DydPhWKgTg = false;}
      if(cOScKopfTZ == true){cOScKopfTZ = false;}
      if(bzmcpMlzlu == true){bzmcpMlzlu = false;}
      if(UEqhgsYrto == true){UEqhgsYrto = false;}
      if(KeIDpEPiDK == true){KeIDpEPiDK = false;}
      if(kwPWmELAYU == true){kwPWmELAYU = false;}
      if(jKtYLYWkuR == true){jKtYLYWkuR = false;}
      if(QyleOxpimk == true){QyleOxpimk = false;}
      if(xDwbJYoUtc == true){xDwbJYoUtc = false;}
      if(hXSZEzkjqR == true){hXSZEzkjqR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHGNTVFMCI
{ 
  void pROwuqhDpJ()
  { 
      bool isqGXXkQzF = false;
      bool POQVhccDBa = false;
      bool NWwOpEmZBY = false;
      bool BkccUgnLhL = false;
      bool BelRQCaUOF = false;
      bool fsOocMwbPS = false;
      bool kKOaEekmBB = false;
      bool nQVoYhjdxm = false;
      bool dRLwrHVmzI = false;
      bool jMuOapQLNl = false;
      bool QmTMROXYQt = false;
      bool bRecoSzShw = false;
      bool IymrQbUHOh = false;
      bool RYQLVpxyec = false;
      bool jwWFfRhSYH = false;
      bool qycQcSzbuo = false;
      bool tPKhcDASGz = false;
      bool VAnEMMbhMz = false;
      bool tChGqTuAhD = false;
      bool pVCoiTknbb = false;
      string XbebSTAOfq;
      string pIZTunrAPL;
      string kqPuOkOUoo;
      string csfTpfrsax;
      string cIReHwjhip;
      string YzCGigMiMg;
      string EfZpNwbGdO;
      string uzYSibYjmS;
      string BfkzPdpYjI;
      string TIgsrxhaQK;
      string TcEUtZZjXG;
      string HbwtfXtaZj;
      string FCVUulRfZl;
      string sxSbyXbQEp;
      string DGBcBqMmNU;
      string CHBgEQHjYH;
      string HtJkMKITuH;
      string wdWjgzBsTD;
      string ZeRFjlwlXg;
      string QqqwhIxQPp;
      if(XbebSTAOfq == TcEUtZZjXG){isqGXXkQzF = true;}
      else if(TcEUtZZjXG == XbebSTAOfq){QmTMROXYQt = true;}
      if(pIZTunrAPL == HbwtfXtaZj){POQVhccDBa = true;}
      else if(HbwtfXtaZj == pIZTunrAPL){bRecoSzShw = true;}
      if(kqPuOkOUoo == FCVUulRfZl){NWwOpEmZBY = true;}
      else if(FCVUulRfZl == kqPuOkOUoo){IymrQbUHOh = true;}
      if(csfTpfrsax == sxSbyXbQEp){BkccUgnLhL = true;}
      else if(sxSbyXbQEp == csfTpfrsax){RYQLVpxyec = true;}
      if(cIReHwjhip == DGBcBqMmNU){BelRQCaUOF = true;}
      else if(DGBcBqMmNU == cIReHwjhip){jwWFfRhSYH = true;}
      if(YzCGigMiMg == CHBgEQHjYH){fsOocMwbPS = true;}
      else if(CHBgEQHjYH == YzCGigMiMg){qycQcSzbuo = true;}
      if(EfZpNwbGdO == HtJkMKITuH){kKOaEekmBB = true;}
      else if(HtJkMKITuH == EfZpNwbGdO){tPKhcDASGz = true;}
      if(uzYSibYjmS == wdWjgzBsTD){nQVoYhjdxm = true;}
      if(BfkzPdpYjI == ZeRFjlwlXg){dRLwrHVmzI = true;}
      if(TIgsrxhaQK == QqqwhIxQPp){jMuOapQLNl = true;}
      while(wdWjgzBsTD == uzYSibYjmS){VAnEMMbhMz = true;}
      while(ZeRFjlwlXg == ZeRFjlwlXg){tChGqTuAhD = true;}
      while(QqqwhIxQPp == QqqwhIxQPp){pVCoiTknbb = true;}
      if(isqGXXkQzF == true){isqGXXkQzF = false;}
      if(POQVhccDBa == true){POQVhccDBa = false;}
      if(NWwOpEmZBY == true){NWwOpEmZBY = false;}
      if(BkccUgnLhL == true){BkccUgnLhL = false;}
      if(BelRQCaUOF == true){BelRQCaUOF = false;}
      if(fsOocMwbPS == true){fsOocMwbPS = false;}
      if(kKOaEekmBB == true){kKOaEekmBB = false;}
      if(nQVoYhjdxm == true){nQVoYhjdxm = false;}
      if(dRLwrHVmzI == true){dRLwrHVmzI = false;}
      if(jMuOapQLNl == true){jMuOapQLNl = false;}
      if(QmTMROXYQt == true){QmTMROXYQt = false;}
      if(bRecoSzShw == true){bRecoSzShw = false;}
      if(IymrQbUHOh == true){IymrQbUHOh = false;}
      if(RYQLVpxyec == true){RYQLVpxyec = false;}
      if(jwWFfRhSYH == true){jwWFfRhSYH = false;}
      if(qycQcSzbuo == true){qycQcSzbuo = false;}
      if(tPKhcDASGz == true){tPKhcDASGz = false;}
      if(VAnEMMbhMz == true){VAnEMMbhMz = false;}
      if(tChGqTuAhD == true){tChGqTuAhD = false;}
      if(pVCoiTknbb == true){pVCoiTknbb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQPWHGXTRD
{ 
  void BUBWfxdSBo()
  { 
      bool UHjafVUGOD = false;
      bool qEHfcgwFxU = false;
      bool kBkoLQmsGK = false;
      bool djFssHrxjt = false;
      bool mVaoAnBgAI = false;
      bool nkUxVSVuOP = false;
      bool iaAEYGzOmV = false;
      bool nyVChOawoW = false;
      bool OFsyVsOIXZ = false;
      bool kxhTLMVWPt = false;
      bool omteUoOSOG = false;
      bool rZFrAdgChf = false;
      bool qqqNjpQBpV = false;
      bool sDfuhaKOcg = false;
      bool dwsQhLrpSg = false;
      bool eTojCywgtd = false;
      bool XMbrNnsKKZ = false;
      bool SRYABtxaeX = false;
      bool yahJqYOuri = false;
      bool edTzIQTBCs = false;
      string OkknAzPntn;
      string KWXdadtOLo;
      string XloSIFKbiq;
      string MVFhsyyPCo;
      string UoEiutlOyW;
      string kjPWKcuRft;
      string onEDanRpkc;
      string feLWUihFXN;
      string SudMGcGhWP;
      string CfjHzgjAHG;
      string cwcUqFXsCb;
      string uptRbsJrxy;
      string hiSUazuEWn;
      string zgyQkWSIUA;
      string ENfuUMkRfG;
      string WqDIXscItq;
      string KTVNcNqdgF;
      string aAWwtUCXAN;
      string OcXPQHcorq;
      string sJNcpjqSSG;
      if(OkknAzPntn == cwcUqFXsCb){UHjafVUGOD = true;}
      else if(cwcUqFXsCb == OkknAzPntn){omteUoOSOG = true;}
      if(KWXdadtOLo == uptRbsJrxy){qEHfcgwFxU = true;}
      else if(uptRbsJrxy == KWXdadtOLo){rZFrAdgChf = true;}
      if(XloSIFKbiq == hiSUazuEWn){kBkoLQmsGK = true;}
      else if(hiSUazuEWn == XloSIFKbiq){qqqNjpQBpV = true;}
      if(MVFhsyyPCo == zgyQkWSIUA){djFssHrxjt = true;}
      else if(zgyQkWSIUA == MVFhsyyPCo){sDfuhaKOcg = true;}
      if(UoEiutlOyW == ENfuUMkRfG){mVaoAnBgAI = true;}
      else if(ENfuUMkRfG == UoEiutlOyW){dwsQhLrpSg = true;}
      if(kjPWKcuRft == WqDIXscItq){nkUxVSVuOP = true;}
      else if(WqDIXscItq == kjPWKcuRft){eTojCywgtd = true;}
      if(onEDanRpkc == KTVNcNqdgF){iaAEYGzOmV = true;}
      else if(KTVNcNqdgF == onEDanRpkc){XMbrNnsKKZ = true;}
      if(feLWUihFXN == aAWwtUCXAN){nyVChOawoW = true;}
      if(SudMGcGhWP == OcXPQHcorq){OFsyVsOIXZ = true;}
      if(CfjHzgjAHG == sJNcpjqSSG){kxhTLMVWPt = true;}
      while(aAWwtUCXAN == feLWUihFXN){SRYABtxaeX = true;}
      while(OcXPQHcorq == OcXPQHcorq){yahJqYOuri = true;}
      while(sJNcpjqSSG == sJNcpjqSSG){edTzIQTBCs = true;}
      if(UHjafVUGOD == true){UHjafVUGOD = false;}
      if(qEHfcgwFxU == true){qEHfcgwFxU = false;}
      if(kBkoLQmsGK == true){kBkoLQmsGK = false;}
      if(djFssHrxjt == true){djFssHrxjt = false;}
      if(mVaoAnBgAI == true){mVaoAnBgAI = false;}
      if(nkUxVSVuOP == true){nkUxVSVuOP = false;}
      if(iaAEYGzOmV == true){iaAEYGzOmV = false;}
      if(nyVChOawoW == true){nyVChOawoW = false;}
      if(OFsyVsOIXZ == true){OFsyVsOIXZ = false;}
      if(kxhTLMVWPt == true){kxhTLMVWPt = false;}
      if(omteUoOSOG == true){omteUoOSOG = false;}
      if(rZFrAdgChf == true){rZFrAdgChf = false;}
      if(qqqNjpQBpV == true){qqqNjpQBpV = false;}
      if(sDfuhaKOcg == true){sDfuhaKOcg = false;}
      if(dwsQhLrpSg == true){dwsQhLrpSg = false;}
      if(eTojCywgtd == true){eTojCywgtd = false;}
      if(XMbrNnsKKZ == true){XMbrNnsKKZ = false;}
      if(SRYABtxaeX == true){SRYABtxaeX = false;}
      if(yahJqYOuri == true){yahJqYOuri = false;}
      if(edTzIQTBCs == true){edTzIQTBCs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTUSKABGFS
{ 
  void lpdoWKynZV()
  { 
      bool xdSFAqEYwj = false;
      bool wJduREhfph = false;
      bool XmYZVxQLSH = false;
      bool hpNbgfZgOG = false;
      bool nLFsjYDgtS = false;
      bool MWjuzJFrjC = false;
      bool ZrGoCGuCOk = false;
      bool eBQisMhepw = false;
      bool sjRzuKGRbW = false;
      bool agwLguEPqd = false;
      bool cBRJnKGABm = false;
      bool baCmJoaGtr = false;
      bool zdZqJxEECy = false;
      bool HRnLSrSHLj = false;
      bool DGPouAdJCr = false;
      bool UyVydzaZzp = false;
      bool GByDeKlpTQ = false;
      bool VSuJnsNjwJ = false;
      bool TuCJdJuogT = false;
      bool QrIUdCHMJk = false;
      string RhhppLQWio;
      string NsCibPKLBk;
      string RmbbBWybCq;
      string rsZGQhoQQj;
      string VIQMYMrbjt;
      string ILGmFdFFoS;
      string NnTrxUSwRs;
      string astRPJWPDn;
      string eVrHiflmAm;
      string ciayWgnXPD;
      string swJpTOQoXw;
      string GpCBmqwLJQ;
      string hfueQqRwti;
      string UyAztiMCnT;
      string OxOEflgZKe;
      string kbOyUNAdZb;
      string wUtnaIoCGE;
      string esXoBkQqzd;
      string KrlOyrjCdg;
      string hhbLWtCadX;
      if(RhhppLQWio == swJpTOQoXw){xdSFAqEYwj = true;}
      else if(swJpTOQoXw == RhhppLQWio){cBRJnKGABm = true;}
      if(NsCibPKLBk == GpCBmqwLJQ){wJduREhfph = true;}
      else if(GpCBmqwLJQ == NsCibPKLBk){baCmJoaGtr = true;}
      if(RmbbBWybCq == hfueQqRwti){XmYZVxQLSH = true;}
      else if(hfueQqRwti == RmbbBWybCq){zdZqJxEECy = true;}
      if(rsZGQhoQQj == UyAztiMCnT){hpNbgfZgOG = true;}
      else if(UyAztiMCnT == rsZGQhoQQj){HRnLSrSHLj = true;}
      if(VIQMYMrbjt == OxOEflgZKe){nLFsjYDgtS = true;}
      else if(OxOEflgZKe == VIQMYMrbjt){DGPouAdJCr = true;}
      if(ILGmFdFFoS == kbOyUNAdZb){MWjuzJFrjC = true;}
      else if(kbOyUNAdZb == ILGmFdFFoS){UyVydzaZzp = true;}
      if(NnTrxUSwRs == wUtnaIoCGE){ZrGoCGuCOk = true;}
      else if(wUtnaIoCGE == NnTrxUSwRs){GByDeKlpTQ = true;}
      if(astRPJWPDn == esXoBkQqzd){eBQisMhepw = true;}
      if(eVrHiflmAm == KrlOyrjCdg){sjRzuKGRbW = true;}
      if(ciayWgnXPD == hhbLWtCadX){agwLguEPqd = true;}
      while(esXoBkQqzd == astRPJWPDn){VSuJnsNjwJ = true;}
      while(KrlOyrjCdg == KrlOyrjCdg){TuCJdJuogT = true;}
      while(hhbLWtCadX == hhbLWtCadX){QrIUdCHMJk = true;}
      if(xdSFAqEYwj == true){xdSFAqEYwj = false;}
      if(wJduREhfph == true){wJduREhfph = false;}
      if(XmYZVxQLSH == true){XmYZVxQLSH = false;}
      if(hpNbgfZgOG == true){hpNbgfZgOG = false;}
      if(nLFsjYDgtS == true){nLFsjYDgtS = false;}
      if(MWjuzJFrjC == true){MWjuzJFrjC = false;}
      if(ZrGoCGuCOk == true){ZrGoCGuCOk = false;}
      if(eBQisMhepw == true){eBQisMhepw = false;}
      if(sjRzuKGRbW == true){sjRzuKGRbW = false;}
      if(agwLguEPqd == true){agwLguEPqd = false;}
      if(cBRJnKGABm == true){cBRJnKGABm = false;}
      if(baCmJoaGtr == true){baCmJoaGtr = false;}
      if(zdZqJxEECy == true){zdZqJxEECy = false;}
      if(HRnLSrSHLj == true){HRnLSrSHLj = false;}
      if(DGPouAdJCr == true){DGPouAdJCr = false;}
      if(UyVydzaZzp == true){UyVydzaZzp = false;}
      if(GByDeKlpTQ == true){GByDeKlpTQ = false;}
      if(VSuJnsNjwJ == true){VSuJnsNjwJ = false;}
      if(TuCJdJuogT == true){TuCJdJuogT = false;}
      if(QrIUdCHMJk == true){QrIUdCHMJk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NDFMYCDHCG
{ 
  void FsoEPwCxjR()
  { 
      bool eWsAnwmfbg = false;
      bool llTZPnaInA = false;
      bool zBIbYhFilW = false;
      bool lDdLBOOuDS = false;
      bool mgEpSiEWEG = false;
      bool SDiBVcOQaG = false;
      bool pEtFuhIIYA = false;
      bool ZfFUNRwRJo = false;
      bool cideDhTcoX = false;
      bool zxTxbhmzuj = false;
      bool auyEfmyOmD = false;
      bool fxHlcHaOBM = false;
      bool OeTAAcLIse = false;
      bool exVYNhkZyQ = false;
      bool iFokqCohUU = false;
      bool HXyhVwbxDD = false;
      bool apUIYiaiXt = false;
      bool WBQjcIphIy = false;
      bool ndnXXHymDR = false;
      bool GmWupsjfMI = false;
      string FiXkLFYQBT;
      string NibKjoQsJj;
      string mAeuBQkPdF;
      string KCjyaXNJYu;
      string PDjhCQDxMR;
      string jgCnbEDbju;
      string TJmuJLzdjM;
      string aGUOUiQxsj;
      string MmDMUcAuVV;
      string TlZdbFQnXp;
      string RZNzpcMmSs;
      string nGizhfGZZf;
      string LDHNsogpmO;
      string RbYCSmYDVr;
      string PMbcgMDZuu;
      string zqOreNRAGB;
      string wVAEaMhfgu;
      string GCDhQybeff;
      string lHuqPaNfXE;
      string VYxUusMXBU;
      if(FiXkLFYQBT == RZNzpcMmSs){eWsAnwmfbg = true;}
      else if(RZNzpcMmSs == FiXkLFYQBT){auyEfmyOmD = true;}
      if(NibKjoQsJj == nGizhfGZZf){llTZPnaInA = true;}
      else if(nGizhfGZZf == NibKjoQsJj){fxHlcHaOBM = true;}
      if(mAeuBQkPdF == LDHNsogpmO){zBIbYhFilW = true;}
      else if(LDHNsogpmO == mAeuBQkPdF){OeTAAcLIse = true;}
      if(KCjyaXNJYu == RbYCSmYDVr){lDdLBOOuDS = true;}
      else if(RbYCSmYDVr == KCjyaXNJYu){exVYNhkZyQ = true;}
      if(PDjhCQDxMR == PMbcgMDZuu){mgEpSiEWEG = true;}
      else if(PMbcgMDZuu == PDjhCQDxMR){iFokqCohUU = true;}
      if(jgCnbEDbju == zqOreNRAGB){SDiBVcOQaG = true;}
      else if(zqOreNRAGB == jgCnbEDbju){HXyhVwbxDD = true;}
      if(TJmuJLzdjM == wVAEaMhfgu){pEtFuhIIYA = true;}
      else if(wVAEaMhfgu == TJmuJLzdjM){apUIYiaiXt = true;}
      if(aGUOUiQxsj == GCDhQybeff){ZfFUNRwRJo = true;}
      if(MmDMUcAuVV == lHuqPaNfXE){cideDhTcoX = true;}
      if(TlZdbFQnXp == VYxUusMXBU){zxTxbhmzuj = true;}
      while(GCDhQybeff == aGUOUiQxsj){WBQjcIphIy = true;}
      while(lHuqPaNfXE == lHuqPaNfXE){ndnXXHymDR = true;}
      while(VYxUusMXBU == VYxUusMXBU){GmWupsjfMI = true;}
      if(eWsAnwmfbg == true){eWsAnwmfbg = false;}
      if(llTZPnaInA == true){llTZPnaInA = false;}
      if(zBIbYhFilW == true){zBIbYhFilW = false;}
      if(lDdLBOOuDS == true){lDdLBOOuDS = false;}
      if(mgEpSiEWEG == true){mgEpSiEWEG = false;}
      if(SDiBVcOQaG == true){SDiBVcOQaG = false;}
      if(pEtFuhIIYA == true){pEtFuhIIYA = false;}
      if(ZfFUNRwRJo == true){ZfFUNRwRJo = false;}
      if(cideDhTcoX == true){cideDhTcoX = false;}
      if(zxTxbhmzuj == true){zxTxbhmzuj = false;}
      if(auyEfmyOmD == true){auyEfmyOmD = false;}
      if(fxHlcHaOBM == true){fxHlcHaOBM = false;}
      if(OeTAAcLIse == true){OeTAAcLIse = false;}
      if(exVYNhkZyQ == true){exVYNhkZyQ = false;}
      if(iFokqCohUU == true){iFokqCohUU = false;}
      if(HXyhVwbxDD == true){HXyhVwbxDD = false;}
      if(apUIYiaiXt == true){apUIYiaiXt = false;}
      if(WBQjcIphIy == true){WBQjcIphIy = false;}
      if(ndnXXHymDR == true){ndnXXHymDR = false;}
      if(GmWupsjfMI == true){GmWupsjfMI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HRDAQKCIKO
{ 
  void nMkPpBTdnk()
  { 
      bool YpOfKUsskL = false;
      bool QZCrGmOzBK = false;
      bool BseERsThUA = false;
      bool CaYRccWFtt = false;
      bool UcJtpPoiXt = false;
      bool LPhilfLJOR = false;
      bool ALXkIoBjOc = false;
      bool PIEHoXikNC = false;
      bool DkJZnmspfx = false;
      bool RMqbtIFYkB = false;
      bool OETueDKZtO = false;
      bool wauMNOBxwV = false;
      bool wLERLCQcNf = false;
      bool SKzMnzQOuj = false;
      bool cSwRApReOe = false;
      bool GHbOEDzCjb = false;
      bool mhMNulaiXO = false;
      bool xmCLscPmQU = false;
      bool kkNhZKhkHk = false;
      bool zOeTxtGhVN = false;
      string lHXfuQEWMn;
      string YKtZxoSnZi;
      string EapNPqIKgL;
      string iPCwKZCkip;
      string YMFTUtclgH;
      string TfpFjKRKPE;
      string HspAFIIxOX;
      string lhEjJqVVsU;
      string NWdZrCYwLz;
      string IrVeheWEOL;
      string leWJUkaGws;
      string ouRtpkPQIC;
      string iLkPOtMZBe;
      string URHghizUEG;
      string aSASKMaanw;
      string PFuMbasHtZ;
      string YAEQYWnjLH;
      string kuLCaQKSEC;
      string TllFOOVuFH;
      string pradgaOism;
      if(lHXfuQEWMn == leWJUkaGws){YpOfKUsskL = true;}
      else if(leWJUkaGws == lHXfuQEWMn){OETueDKZtO = true;}
      if(YKtZxoSnZi == ouRtpkPQIC){QZCrGmOzBK = true;}
      else if(ouRtpkPQIC == YKtZxoSnZi){wauMNOBxwV = true;}
      if(EapNPqIKgL == iLkPOtMZBe){BseERsThUA = true;}
      else if(iLkPOtMZBe == EapNPqIKgL){wLERLCQcNf = true;}
      if(iPCwKZCkip == URHghizUEG){CaYRccWFtt = true;}
      else if(URHghizUEG == iPCwKZCkip){SKzMnzQOuj = true;}
      if(YMFTUtclgH == aSASKMaanw){UcJtpPoiXt = true;}
      else if(aSASKMaanw == YMFTUtclgH){cSwRApReOe = true;}
      if(TfpFjKRKPE == PFuMbasHtZ){LPhilfLJOR = true;}
      else if(PFuMbasHtZ == TfpFjKRKPE){GHbOEDzCjb = true;}
      if(HspAFIIxOX == YAEQYWnjLH){ALXkIoBjOc = true;}
      else if(YAEQYWnjLH == HspAFIIxOX){mhMNulaiXO = true;}
      if(lhEjJqVVsU == kuLCaQKSEC){PIEHoXikNC = true;}
      if(NWdZrCYwLz == TllFOOVuFH){DkJZnmspfx = true;}
      if(IrVeheWEOL == pradgaOism){RMqbtIFYkB = true;}
      while(kuLCaQKSEC == lhEjJqVVsU){xmCLscPmQU = true;}
      while(TllFOOVuFH == TllFOOVuFH){kkNhZKhkHk = true;}
      while(pradgaOism == pradgaOism){zOeTxtGhVN = true;}
      if(YpOfKUsskL == true){YpOfKUsskL = false;}
      if(QZCrGmOzBK == true){QZCrGmOzBK = false;}
      if(BseERsThUA == true){BseERsThUA = false;}
      if(CaYRccWFtt == true){CaYRccWFtt = false;}
      if(UcJtpPoiXt == true){UcJtpPoiXt = false;}
      if(LPhilfLJOR == true){LPhilfLJOR = false;}
      if(ALXkIoBjOc == true){ALXkIoBjOc = false;}
      if(PIEHoXikNC == true){PIEHoXikNC = false;}
      if(DkJZnmspfx == true){DkJZnmspfx = false;}
      if(RMqbtIFYkB == true){RMqbtIFYkB = false;}
      if(OETueDKZtO == true){OETueDKZtO = false;}
      if(wauMNOBxwV == true){wauMNOBxwV = false;}
      if(wLERLCQcNf == true){wLERLCQcNf = false;}
      if(SKzMnzQOuj == true){SKzMnzQOuj = false;}
      if(cSwRApReOe == true){cSwRApReOe = false;}
      if(GHbOEDzCjb == true){GHbOEDzCjb = false;}
      if(mhMNulaiXO == true){mhMNulaiXO = false;}
      if(xmCLscPmQU == true){xmCLscPmQU = false;}
      if(kkNhZKhkHk == true){kkNhZKhkHk = false;}
      if(zOeTxtGhVN == true){zOeTxtGhVN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NQYBWNMENM
{ 
  void dTXjwyLLHb()
  { 
      bool IqyHFENEGP = false;
      bool gkUKVpsQxa = false;
      bool jVDMWewGde = false;
      bool LaHmtYBiKf = false;
      bool BCDmZfNSrT = false;
      bool djUpKlmlka = false;
      bool HHaaDFchQx = false;
      bool oKGQZhSQlq = false;
      bool QdNKBaGQbH = false;
      bool kPyjXtbbiU = false;
      bool CeBueTdDQc = false;
      bool TVztJdsQZc = false;
      bool zMFIMYMVse = false;
      bool FphRnkbSeg = false;
      bool wCAzmOPDZt = false;
      bool BKCGUpZshF = false;
      bool HHKkWdnhFX = false;
      bool BZksfwLFUy = false;
      bool IIwzdunbwy = false;
      bool LikYZorOcJ = false;
      string nAQUXgNWCt;
      string ICTFZZMrUc;
      string gNGZPobuzF;
      string CNJpGmbZtV;
      string PceOTMVUty;
      string wVOLsatqEh;
      string ESWxrtrdzl;
      string ymyzMDhqFC;
      string SGABIfyyxe;
      string rjULQxFgWZ;
      string UqVIAIXPyo;
      string rClCPyRVnL;
      string wtgTsNSmiP;
      string yAUfhakrAA;
      string IiAHlpySwS;
      string eisKcaKCOl;
      string pjghprgGTn;
      string NZUnDNsYgD;
      string PzqPkPHKCH;
      string QhcOJXBRRt;
      if(nAQUXgNWCt == UqVIAIXPyo){IqyHFENEGP = true;}
      else if(UqVIAIXPyo == nAQUXgNWCt){CeBueTdDQc = true;}
      if(ICTFZZMrUc == rClCPyRVnL){gkUKVpsQxa = true;}
      else if(rClCPyRVnL == ICTFZZMrUc){TVztJdsQZc = true;}
      if(gNGZPobuzF == wtgTsNSmiP){jVDMWewGde = true;}
      else if(wtgTsNSmiP == gNGZPobuzF){zMFIMYMVse = true;}
      if(CNJpGmbZtV == yAUfhakrAA){LaHmtYBiKf = true;}
      else if(yAUfhakrAA == CNJpGmbZtV){FphRnkbSeg = true;}
      if(PceOTMVUty == IiAHlpySwS){BCDmZfNSrT = true;}
      else if(IiAHlpySwS == PceOTMVUty){wCAzmOPDZt = true;}
      if(wVOLsatqEh == eisKcaKCOl){djUpKlmlka = true;}
      else if(eisKcaKCOl == wVOLsatqEh){BKCGUpZshF = true;}
      if(ESWxrtrdzl == pjghprgGTn){HHaaDFchQx = true;}
      else if(pjghprgGTn == ESWxrtrdzl){HHKkWdnhFX = true;}
      if(ymyzMDhqFC == NZUnDNsYgD){oKGQZhSQlq = true;}
      if(SGABIfyyxe == PzqPkPHKCH){QdNKBaGQbH = true;}
      if(rjULQxFgWZ == QhcOJXBRRt){kPyjXtbbiU = true;}
      while(NZUnDNsYgD == ymyzMDhqFC){BZksfwLFUy = true;}
      while(PzqPkPHKCH == PzqPkPHKCH){IIwzdunbwy = true;}
      while(QhcOJXBRRt == QhcOJXBRRt){LikYZorOcJ = true;}
      if(IqyHFENEGP == true){IqyHFENEGP = false;}
      if(gkUKVpsQxa == true){gkUKVpsQxa = false;}
      if(jVDMWewGde == true){jVDMWewGde = false;}
      if(LaHmtYBiKf == true){LaHmtYBiKf = false;}
      if(BCDmZfNSrT == true){BCDmZfNSrT = false;}
      if(djUpKlmlka == true){djUpKlmlka = false;}
      if(HHaaDFchQx == true){HHaaDFchQx = false;}
      if(oKGQZhSQlq == true){oKGQZhSQlq = false;}
      if(QdNKBaGQbH == true){QdNKBaGQbH = false;}
      if(kPyjXtbbiU == true){kPyjXtbbiU = false;}
      if(CeBueTdDQc == true){CeBueTdDQc = false;}
      if(TVztJdsQZc == true){TVztJdsQZc = false;}
      if(zMFIMYMVse == true){zMFIMYMVse = false;}
      if(FphRnkbSeg == true){FphRnkbSeg = false;}
      if(wCAzmOPDZt == true){wCAzmOPDZt = false;}
      if(BKCGUpZshF == true){BKCGUpZshF = false;}
      if(HHKkWdnhFX == true){HHKkWdnhFX = false;}
      if(BZksfwLFUy == true){BZksfwLFUy = false;}
      if(IIwzdunbwy == true){IIwzdunbwy = false;}
      if(LikYZorOcJ == true){LikYZorOcJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJIFEQXAGU
{ 
  void DdZbJgFxiT()
  { 
      bool xjySYMDKOc = false;
      bool XhVejdKVUt = false;
      bool kLyqzlrymU = false;
      bool zRLoPPPJSE = false;
      bool EJOFoaxUrf = false;
      bool KPlIFkkHTl = false;
      bool TFWtcGWgOU = false;
      bool OBCQpbxrCX = false;
      bool nXFHKieDjd = false;
      bool dIpgjylUch = false;
      bool EQFWRJNVSc = false;
      bool nsEuxwzPjs = false;
      bool aSwkpFLVfq = false;
      bool pcPTSXRhoB = false;
      bool VJkGokDtjm = false;
      bool zWjiGkTUgL = false;
      bool xqoamLcjcZ = false;
      bool dRaiWRhpuF = false;
      bool CQlrrTrfNg = false;
      bool DxBcDeTJSd = false;
      string rCApqXRaZh;
      string agDMmgoaVX;
      string aToXCDqtYI;
      string kDQoEZWFfo;
      string NUdBYdenHK;
      string tlRRuYMbmn;
      string fXCRxXPNIN;
      string KjufKFpnyX;
      string XClNOykzte;
      string MtRqJoSMEB;
      string NQftAKpkGo;
      string iYdOPdknCy;
      string lQTcBPRDWU;
      string mcixKGWrND;
      string IArFwmQDbe;
      string EeJFOxxCrj;
      string smNkCFpgEI;
      string GrayplYOfN;
      string zObrQHTdhM;
      string JTzcKVlGCq;
      if(rCApqXRaZh == NQftAKpkGo){xjySYMDKOc = true;}
      else if(NQftAKpkGo == rCApqXRaZh){EQFWRJNVSc = true;}
      if(agDMmgoaVX == iYdOPdknCy){XhVejdKVUt = true;}
      else if(iYdOPdknCy == agDMmgoaVX){nsEuxwzPjs = true;}
      if(aToXCDqtYI == lQTcBPRDWU){kLyqzlrymU = true;}
      else if(lQTcBPRDWU == aToXCDqtYI){aSwkpFLVfq = true;}
      if(kDQoEZWFfo == mcixKGWrND){zRLoPPPJSE = true;}
      else if(mcixKGWrND == kDQoEZWFfo){pcPTSXRhoB = true;}
      if(NUdBYdenHK == IArFwmQDbe){EJOFoaxUrf = true;}
      else if(IArFwmQDbe == NUdBYdenHK){VJkGokDtjm = true;}
      if(tlRRuYMbmn == EeJFOxxCrj){KPlIFkkHTl = true;}
      else if(EeJFOxxCrj == tlRRuYMbmn){zWjiGkTUgL = true;}
      if(fXCRxXPNIN == smNkCFpgEI){TFWtcGWgOU = true;}
      else if(smNkCFpgEI == fXCRxXPNIN){xqoamLcjcZ = true;}
      if(KjufKFpnyX == GrayplYOfN){OBCQpbxrCX = true;}
      if(XClNOykzte == zObrQHTdhM){nXFHKieDjd = true;}
      if(MtRqJoSMEB == JTzcKVlGCq){dIpgjylUch = true;}
      while(GrayplYOfN == KjufKFpnyX){dRaiWRhpuF = true;}
      while(zObrQHTdhM == zObrQHTdhM){CQlrrTrfNg = true;}
      while(JTzcKVlGCq == JTzcKVlGCq){DxBcDeTJSd = true;}
      if(xjySYMDKOc == true){xjySYMDKOc = false;}
      if(XhVejdKVUt == true){XhVejdKVUt = false;}
      if(kLyqzlrymU == true){kLyqzlrymU = false;}
      if(zRLoPPPJSE == true){zRLoPPPJSE = false;}
      if(EJOFoaxUrf == true){EJOFoaxUrf = false;}
      if(KPlIFkkHTl == true){KPlIFkkHTl = false;}
      if(TFWtcGWgOU == true){TFWtcGWgOU = false;}
      if(OBCQpbxrCX == true){OBCQpbxrCX = false;}
      if(nXFHKieDjd == true){nXFHKieDjd = false;}
      if(dIpgjylUch == true){dIpgjylUch = false;}
      if(EQFWRJNVSc == true){EQFWRJNVSc = false;}
      if(nsEuxwzPjs == true){nsEuxwzPjs = false;}
      if(aSwkpFLVfq == true){aSwkpFLVfq = false;}
      if(pcPTSXRhoB == true){pcPTSXRhoB = false;}
      if(VJkGokDtjm == true){VJkGokDtjm = false;}
      if(zWjiGkTUgL == true){zWjiGkTUgL = false;}
      if(xqoamLcjcZ == true){xqoamLcjcZ = false;}
      if(dRaiWRhpuF == true){dRaiWRhpuF = false;}
      if(CQlrrTrfNg == true){CQlrrTrfNg = false;}
      if(DxBcDeTJSd == true){DxBcDeTJSd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DORZZXXTHP
{ 
  void EOZCSWVwyd()
  { 
      bool qcfjFiOYrM = false;
      bool rAHwnenIGH = false;
      bool EmjpQdCXyX = false;
      bool mZcdExyIlI = false;
      bool iqljiiSDGY = false;
      bool jUsSSDspTa = false;
      bool gpaUZRWcqp = false;
      bool ffWyYMBzGg = false;
      bool LyRYmRfKLA = false;
      bool EHnKbrQRKQ = false;
      bool LpLQrEyusF = false;
      bool CsjmPhYBgH = false;
      bool lMQqlYqLWg = false;
      bool uiooUUlAfi = false;
      bool TjQGxKXBts = false;
      bool SPjCezZTdT = false;
      bool MlYMJTEtRu = false;
      bool uYUynBuKtb = false;
      bool ApQcNeylJV = false;
      bool uSVMVgLEwc = false;
      string uTIWXSJtqz;
      string XyqHmZtngM;
      string luXCYKpeJZ;
      string esCrGpXHkb;
      string HuJMDmkDrB;
      string YNJebAwGxM;
      string bekQUewyAx;
      string CmCEEqkLyk;
      string ZllIARjXQG;
      string sRJXAcKrrY;
      string qlCuzlLEZk;
      string OkHLmorbQC;
      string uYhtDkcdDb;
      string fsTZtmjqJN;
      string GeyerIKykL;
      string jhbocSDIqO;
      string JgBxFVRgRA;
      string FBSCwQZDBu;
      string aesrqxQdxb;
      string jaztEYdAZW;
      if(uTIWXSJtqz == qlCuzlLEZk){qcfjFiOYrM = true;}
      else if(qlCuzlLEZk == uTIWXSJtqz){LpLQrEyusF = true;}
      if(XyqHmZtngM == OkHLmorbQC){rAHwnenIGH = true;}
      else if(OkHLmorbQC == XyqHmZtngM){CsjmPhYBgH = true;}
      if(luXCYKpeJZ == uYhtDkcdDb){EmjpQdCXyX = true;}
      else if(uYhtDkcdDb == luXCYKpeJZ){lMQqlYqLWg = true;}
      if(esCrGpXHkb == fsTZtmjqJN){mZcdExyIlI = true;}
      else if(fsTZtmjqJN == esCrGpXHkb){uiooUUlAfi = true;}
      if(HuJMDmkDrB == GeyerIKykL){iqljiiSDGY = true;}
      else if(GeyerIKykL == HuJMDmkDrB){TjQGxKXBts = true;}
      if(YNJebAwGxM == jhbocSDIqO){jUsSSDspTa = true;}
      else if(jhbocSDIqO == YNJebAwGxM){SPjCezZTdT = true;}
      if(bekQUewyAx == JgBxFVRgRA){gpaUZRWcqp = true;}
      else if(JgBxFVRgRA == bekQUewyAx){MlYMJTEtRu = true;}
      if(CmCEEqkLyk == FBSCwQZDBu){ffWyYMBzGg = true;}
      if(ZllIARjXQG == aesrqxQdxb){LyRYmRfKLA = true;}
      if(sRJXAcKrrY == jaztEYdAZW){EHnKbrQRKQ = true;}
      while(FBSCwQZDBu == CmCEEqkLyk){uYUynBuKtb = true;}
      while(aesrqxQdxb == aesrqxQdxb){ApQcNeylJV = true;}
      while(jaztEYdAZW == jaztEYdAZW){uSVMVgLEwc = true;}
      if(qcfjFiOYrM == true){qcfjFiOYrM = false;}
      if(rAHwnenIGH == true){rAHwnenIGH = false;}
      if(EmjpQdCXyX == true){EmjpQdCXyX = false;}
      if(mZcdExyIlI == true){mZcdExyIlI = false;}
      if(iqljiiSDGY == true){iqljiiSDGY = false;}
      if(jUsSSDspTa == true){jUsSSDspTa = false;}
      if(gpaUZRWcqp == true){gpaUZRWcqp = false;}
      if(ffWyYMBzGg == true){ffWyYMBzGg = false;}
      if(LyRYmRfKLA == true){LyRYmRfKLA = false;}
      if(EHnKbrQRKQ == true){EHnKbrQRKQ = false;}
      if(LpLQrEyusF == true){LpLQrEyusF = false;}
      if(CsjmPhYBgH == true){CsjmPhYBgH = false;}
      if(lMQqlYqLWg == true){lMQqlYqLWg = false;}
      if(uiooUUlAfi == true){uiooUUlAfi = false;}
      if(TjQGxKXBts == true){TjQGxKXBts = false;}
      if(SPjCezZTdT == true){SPjCezZTdT = false;}
      if(MlYMJTEtRu == true){MlYMJTEtRu = false;}
      if(uYUynBuKtb == true){uYUynBuKtb = false;}
      if(ApQcNeylJV == true){ApQcNeylJV = false;}
      if(uSVMVgLEwc == true){uSVMVgLEwc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QEKNFPDNOX
{ 
  void QRotcgPdCc()
  { 
      bool eoHmfATsVp = false;
      bool zHbDuKWXhn = false;
      bool McXgQVfbCW = false;
      bool rtelXuTUre = false;
      bool DYtUiQXiUx = false;
      bool KOcLiBQZVJ = false;
      bool UqqyyEboeA = false;
      bool qBeCkniCxA = false;
      bool xxHEMdRTDV = false;
      bool esziKLguWd = false;
      bool niDUGIjZZt = false;
      bool RObVLWjllU = false;
      bool mIlJUxCurZ = false;
      bool GneTLOtmyE = false;
      bool sqsIDQRdWm = false;
      bool buICqfwtzJ = false;
      bool FnhAndiIJw = false;
      bool cwngawOdFE = false;
      bool fYYExLebcf = false;
      bool SAmnyFIsTZ = false;
      string njpzEfYuSp;
      string GomgMMfbzm;
      string MNQNWPYpVm;
      string zmZnAcQFPo;
      string LblhAzbyRk;
      string KZgngaTccn;
      string GiZfpSPygj;
      string waLJbkahNX;
      string naYkcZFkHY;
      string JmbbhcBGqg;
      string icQgniNXMu;
      string zkPEzfJoDQ;
      string MdqHaIyiay;
      string jUqfnKJqws;
      string LhYLZYXXbC;
      string SMDaUFlJFf;
      string kdwNLdsiQo;
      string WRrJEdFehC;
      string jaHYfWRPLi;
      string XAlQHglKAu;
      if(njpzEfYuSp == icQgniNXMu){eoHmfATsVp = true;}
      else if(icQgniNXMu == njpzEfYuSp){niDUGIjZZt = true;}
      if(GomgMMfbzm == zkPEzfJoDQ){zHbDuKWXhn = true;}
      else if(zkPEzfJoDQ == GomgMMfbzm){RObVLWjllU = true;}
      if(MNQNWPYpVm == MdqHaIyiay){McXgQVfbCW = true;}
      else if(MdqHaIyiay == MNQNWPYpVm){mIlJUxCurZ = true;}
      if(zmZnAcQFPo == jUqfnKJqws){rtelXuTUre = true;}
      else if(jUqfnKJqws == zmZnAcQFPo){GneTLOtmyE = true;}
      if(LblhAzbyRk == LhYLZYXXbC){DYtUiQXiUx = true;}
      else if(LhYLZYXXbC == LblhAzbyRk){sqsIDQRdWm = true;}
      if(KZgngaTccn == SMDaUFlJFf){KOcLiBQZVJ = true;}
      else if(SMDaUFlJFf == KZgngaTccn){buICqfwtzJ = true;}
      if(GiZfpSPygj == kdwNLdsiQo){UqqyyEboeA = true;}
      else if(kdwNLdsiQo == GiZfpSPygj){FnhAndiIJw = true;}
      if(waLJbkahNX == WRrJEdFehC){qBeCkniCxA = true;}
      if(naYkcZFkHY == jaHYfWRPLi){xxHEMdRTDV = true;}
      if(JmbbhcBGqg == XAlQHglKAu){esziKLguWd = true;}
      while(WRrJEdFehC == waLJbkahNX){cwngawOdFE = true;}
      while(jaHYfWRPLi == jaHYfWRPLi){fYYExLebcf = true;}
      while(XAlQHglKAu == XAlQHglKAu){SAmnyFIsTZ = true;}
      if(eoHmfATsVp == true){eoHmfATsVp = false;}
      if(zHbDuKWXhn == true){zHbDuKWXhn = false;}
      if(McXgQVfbCW == true){McXgQVfbCW = false;}
      if(rtelXuTUre == true){rtelXuTUre = false;}
      if(DYtUiQXiUx == true){DYtUiQXiUx = false;}
      if(KOcLiBQZVJ == true){KOcLiBQZVJ = false;}
      if(UqqyyEboeA == true){UqqyyEboeA = false;}
      if(qBeCkniCxA == true){qBeCkniCxA = false;}
      if(xxHEMdRTDV == true){xxHEMdRTDV = false;}
      if(esziKLguWd == true){esziKLguWd = false;}
      if(niDUGIjZZt == true){niDUGIjZZt = false;}
      if(RObVLWjllU == true){RObVLWjllU = false;}
      if(mIlJUxCurZ == true){mIlJUxCurZ = false;}
      if(GneTLOtmyE == true){GneTLOtmyE = false;}
      if(sqsIDQRdWm == true){sqsIDQRdWm = false;}
      if(buICqfwtzJ == true){buICqfwtzJ = false;}
      if(FnhAndiIJw == true){FnhAndiIJw = false;}
      if(cwngawOdFE == true){cwngawOdFE = false;}
      if(fYYExLebcf == true){fYYExLebcf = false;}
      if(SAmnyFIsTZ == true){SAmnyFIsTZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RPCXKQUIXV
{ 
  void HwFhQFtcdL()
  { 
      bool wumDgOyBMT = false;
      bool RUhBeCCFxM = false;
      bool RDTegJIybI = false;
      bool slFkJTnZNi = false;
      bool attXOqGPMG = false;
      bool ESBYZraIVW = false;
      bool GAYEaeOwrK = false;
      bool ObqNlXJwQp = false;
      bool DrkUDZkgLR = false;
      bool sfEpbaUpxi = false;
      bool cJXCrcammB = false;
      bool ieqfTNOEAA = false;
      bool thkZRhXBlK = false;
      bool DSyhMsUica = false;
      bool zxtJiOnXVN = false;
      bool MQpxnuYxkK = false;
      bool EZBbyPfJSZ = false;
      bool sebZBwmbqC = false;
      bool szeXymbBsR = false;
      bool UXyRVYwRKS = false;
      string jJJVieYNxu;
      string SoDpeDgUfH;
      string fmySGRhfiZ;
      string tdiMBOlKea;
      string gxmgPnSkkg;
      string dyeIkxLqOQ;
      string wseXAoFqnQ;
      string QWpEZhzQCS;
      string zxtCwwzaaE;
      string CuuOdmSPga;
      string hbwUPGHZhC;
      string xunwRzycbE;
      string pePjNVbaZm;
      string PjjbjXAYlo;
      string nYsYGHGzxe;
      string oonbkDLLHt;
      string egAumNLLLs;
      string yZqlPQkqdF;
      string ObdtxZuHqg;
      string LnRrJHXykr;
      if(jJJVieYNxu == hbwUPGHZhC){wumDgOyBMT = true;}
      else if(hbwUPGHZhC == jJJVieYNxu){cJXCrcammB = true;}
      if(SoDpeDgUfH == xunwRzycbE){RUhBeCCFxM = true;}
      else if(xunwRzycbE == SoDpeDgUfH){ieqfTNOEAA = true;}
      if(fmySGRhfiZ == pePjNVbaZm){RDTegJIybI = true;}
      else if(pePjNVbaZm == fmySGRhfiZ){thkZRhXBlK = true;}
      if(tdiMBOlKea == PjjbjXAYlo){slFkJTnZNi = true;}
      else if(PjjbjXAYlo == tdiMBOlKea){DSyhMsUica = true;}
      if(gxmgPnSkkg == nYsYGHGzxe){attXOqGPMG = true;}
      else if(nYsYGHGzxe == gxmgPnSkkg){zxtJiOnXVN = true;}
      if(dyeIkxLqOQ == oonbkDLLHt){ESBYZraIVW = true;}
      else if(oonbkDLLHt == dyeIkxLqOQ){MQpxnuYxkK = true;}
      if(wseXAoFqnQ == egAumNLLLs){GAYEaeOwrK = true;}
      else if(egAumNLLLs == wseXAoFqnQ){EZBbyPfJSZ = true;}
      if(QWpEZhzQCS == yZqlPQkqdF){ObqNlXJwQp = true;}
      if(zxtCwwzaaE == ObdtxZuHqg){DrkUDZkgLR = true;}
      if(CuuOdmSPga == LnRrJHXykr){sfEpbaUpxi = true;}
      while(yZqlPQkqdF == QWpEZhzQCS){sebZBwmbqC = true;}
      while(ObdtxZuHqg == ObdtxZuHqg){szeXymbBsR = true;}
      while(LnRrJHXykr == LnRrJHXykr){UXyRVYwRKS = true;}
      if(wumDgOyBMT == true){wumDgOyBMT = false;}
      if(RUhBeCCFxM == true){RUhBeCCFxM = false;}
      if(RDTegJIybI == true){RDTegJIybI = false;}
      if(slFkJTnZNi == true){slFkJTnZNi = false;}
      if(attXOqGPMG == true){attXOqGPMG = false;}
      if(ESBYZraIVW == true){ESBYZraIVW = false;}
      if(GAYEaeOwrK == true){GAYEaeOwrK = false;}
      if(ObqNlXJwQp == true){ObqNlXJwQp = false;}
      if(DrkUDZkgLR == true){DrkUDZkgLR = false;}
      if(sfEpbaUpxi == true){sfEpbaUpxi = false;}
      if(cJXCrcammB == true){cJXCrcammB = false;}
      if(ieqfTNOEAA == true){ieqfTNOEAA = false;}
      if(thkZRhXBlK == true){thkZRhXBlK = false;}
      if(DSyhMsUica == true){DSyhMsUica = false;}
      if(zxtJiOnXVN == true){zxtJiOnXVN = false;}
      if(MQpxnuYxkK == true){MQpxnuYxkK = false;}
      if(EZBbyPfJSZ == true){EZBbyPfJSZ = false;}
      if(sebZBwmbqC == true){sebZBwmbqC = false;}
      if(szeXymbBsR == true){szeXymbBsR = false;}
      if(UXyRVYwRKS == true){UXyRVYwRKS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GJVTEJZPQF
{ 
  void lUADfNpDTe()
  { 
      bool QYOBIkajww = false;
      bool RoNXVDZqPw = false;
      bool mVegIaEfJp = false;
      bool BPyPndNNVu = false;
      bool yUWemOdWUp = false;
      bool oWWmGusgsg = false;
      bool gtaGtBpyir = false;
      bool oMVUyRyAts = false;
      bool xgKTBesLIr = false;
      bool jgUnNDtQjk = false;
      bool XfmcAcACnn = false;
      bool wslzjAiHFP = false;
      bool IdoqHHrgGt = false;
      bool XhQJVRtgSX = false;
      bool dpWTwpuUEN = false;
      bool TmKTbspuUs = false;
      bool jSutQOccdR = false;
      bool FBnglRHVuR = false;
      bool MWcrZkWwgb = false;
      bool byMZmKtcDg = false;
      string cdXXreFwsy;
      string WYdesZwrpE;
      string FjgcdYPakh;
      string PHkwOPSGRZ;
      string ixbwcwpiRN;
      string zrtkArwttT;
      string OdKLhOmgQd;
      string GpZQVIIkAh;
      string hgJWiWNzuV;
      string SYMyKElPNN;
      string IIRmGJRcOq;
      string jLsLkhUncL;
      string BmluLhcbGR;
      string WrWmZZOVPZ;
      string FkkEkGeAMb;
      string jymCMUWWbY;
      string foVxUroFlL;
      string SyXDFPChJE;
      string CcPegYETaE;
      string DqtqsPOmis;
      if(cdXXreFwsy == IIRmGJRcOq){QYOBIkajww = true;}
      else if(IIRmGJRcOq == cdXXreFwsy){XfmcAcACnn = true;}
      if(WYdesZwrpE == jLsLkhUncL){RoNXVDZqPw = true;}
      else if(jLsLkhUncL == WYdesZwrpE){wslzjAiHFP = true;}
      if(FjgcdYPakh == BmluLhcbGR){mVegIaEfJp = true;}
      else if(BmluLhcbGR == FjgcdYPakh){IdoqHHrgGt = true;}
      if(PHkwOPSGRZ == WrWmZZOVPZ){BPyPndNNVu = true;}
      else if(WrWmZZOVPZ == PHkwOPSGRZ){XhQJVRtgSX = true;}
      if(ixbwcwpiRN == FkkEkGeAMb){yUWemOdWUp = true;}
      else if(FkkEkGeAMb == ixbwcwpiRN){dpWTwpuUEN = true;}
      if(zrtkArwttT == jymCMUWWbY){oWWmGusgsg = true;}
      else if(jymCMUWWbY == zrtkArwttT){TmKTbspuUs = true;}
      if(OdKLhOmgQd == foVxUroFlL){gtaGtBpyir = true;}
      else if(foVxUroFlL == OdKLhOmgQd){jSutQOccdR = true;}
      if(GpZQVIIkAh == SyXDFPChJE){oMVUyRyAts = true;}
      if(hgJWiWNzuV == CcPegYETaE){xgKTBesLIr = true;}
      if(SYMyKElPNN == DqtqsPOmis){jgUnNDtQjk = true;}
      while(SyXDFPChJE == GpZQVIIkAh){FBnglRHVuR = true;}
      while(CcPegYETaE == CcPegYETaE){MWcrZkWwgb = true;}
      while(DqtqsPOmis == DqtqsPOmis){byMZmKtcDg = true;}
      if(QYOBIkajww == true){QYOBIkajww = false;}
      if(RoNXVDZqPw == true){RoNXVDZqPw = false;}
      if(mVegIaEfJp == true){mVegIaEfJp = false;}
      if(BPyPndNNVu == true){BPyPndNNVu = false;}
      if(yUWemOdWUp == true){yUWemOdWUp = false;}
      if(oWWmGusgsg == true){oWWmGusgsg = false;}
      if(gtaGtBpyir == true){gtaGtBpyir = false;}
      if(oMVUyRyAts == true){oMVUyRyAts = false;}
      if(xgKTBesLIr == true){xgKTBesLIr = false;}
      if(jgUnNDtQjk == true){jgUnNDtQjk = false;}
      if(XfmcAcACnn == true){XfmcAcACnn = false;}
      if(wslzjAiHFP == true){wslzjAiHFP = false;}
      if(IdoqHHrgGt == true){IdoqHHrgGt = false;}
      if(XhQJVRtgSX == true){XhQJVRtgSX = false;}
      if(dpWTwpuUEN == true){dpWTwpuUEN = false;}
      if(TmKTbspuUs == true){TmKTbspuUs = false;}
      if(jSutQOccdR == true){jSutQOccdR = false;}
      if(FBnglRHVuR == true){FBnglRHVuR = false;}
      if(MWcrZkWwgb == true){MWcrZkWwgb = false;}
      if(byMZmKtcDg == true){byMZmKtcDg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PFWPFLHZOT
{ 
  void FuDVxmYLKg()
  { 
      bool VTUIVIaPLa = false;
      bool mmwgQAFYLY = false;
      bool LumpxWRNif = false;
      bool YKHplYVSEm = false;
      bool qDeQedZMdf = false;
      bool RTdxWZfeKz = false;
      bool pMgfBbeGur = false;
      bool dlTYhIQVKS = false;
      bool xEjCOEgKSM = false;
      bool rpIFweVzPC = false;
      bool yTRlBezFOO = false;
      bool JJTrClcdRw = false;
      bool uUnhzmdObD = false;
      bool lQGHTdmxBi = false;
      bool FbuDCiWQCK = false;
      bool BqhSHdfilN = false;
      bool BkcLbrDMXY = false;
      bool yechqTYjfQ = false;
      bool QNLRBtimAo = false;
      bool xELmhTyjaK = false;
      string xFAHtZwokf;
      string OoCOghVjde;
      string XEmryBnLSN;
      string nSWDjRYEOl;
      string AVnNBEImVL;
      string dChCusRHJr;
      string lkVWrwSzeP;
      string JQVqeCPZqs;
      string sAoHjkjUHq;
      string zQuWAPzRUF;
      string lJIFCMgqWs;
      string cqQQykuOlG;
      string LyrmQrVzpP;
      string CyEkHiqiFX;
      string EsxNNIzdXP;
      string TjeNsnRVoJ;
      string qgAHqelfJO;
      string sLJOCSAdYI;
      string rqbauRSprS;
      string RVtufWsoVi;
      if(xFAHtZwokf == lJIFCMgqWs){VTUIVIaPLa = true;}
      else if(lJIFCMgqWs == xFAHtZwokf){yTRlBezFOO = true;}
      if(OoCOghVjde == cqQQykuOlG){mmwgQAFYLY = true;}
      else if(cqQQykuOlG == OoCOghVjde){JJTrClcdRw = true;}
      if(XEmryBnLSN == LyrmQrVzpP){LumpxWRNif = true;}
      else if(LyrmQrVzpP == XEmryBnLSN){uUnhzmdObD = true;}
      if(nSWDjRYEOl == CyEkHiqiFX){YKHplYVSEm = true;}
      else if(CyEkHiqiFX == nSWDjRYEOl){lQGHTdmxBi = true;}
      if(AVnNBEImVL == EsxNNIzdXP){qDeQedZMdf = true;}
      else if(EsxNNIzdXP == AVnNBEImVL){FbuDCiWQCK = true;}
      if(dChCusRHJr == TjeNsnRVoJ){RTdxWZfeKz = true;}
      else if(TjeNsnRVoJ == dChCusRHJr){BqhSHdfilN = true;}
      if(lkVWrwSzeP == qgAHqelfJO){pMgfBbeGur = true;}
      else if(qgAHqelfJO == lkVWrwSzeP){BkcLbrDMXY = true;}
      if(JQVqeCPZqs == sLJOCSAdYI){dlTYhIQVKS = true;}
      if(sAoHjkjUHq == rqbauRSprS){xEjCOEgKSM = true;}
      if(zQuWAPzRUF == RVtufWsoVi){rpIFweVzPC = true;}
      while(sLJOCSAdYI == JQVqeCPZqs){yechqTYjfQ = true;}
      while(rqbauRSprS == rqbauRSprS){QNLRBtimAo = true;}
      while(RVtufWsoVi == RVtufWsoVi){xELmhTyjaK = true;}
      if(VTUIVIaPLa == true){VTUIVIaPLa = false;}
      if(mmwgQAFYLY == true){mmwgQAFYLY = false;}
      if(LumpxWRNif == true){LumpxWRNif = false;}
      if(YKHplYVSEm == true){YKHplYVSEm = false;}
      if(qDeQedZMdf == true){qDeQedZMdf = false;}
      if(RTdxWZfeKz == true){RTdxWZfeKz = false;}
      if(pMgfBbeGur == true){pMgfBbeGur = false;}
      if(dlTYhIQVKS == true){dlTYhIQVKS = false;}
      if(xEjCOEgKSM == true){xEjCOEgKSM = false;}
      if(rpIFweVzPC == true){rpIFweVzPC = false;}
      if(yTRlBezFOO == true){yTRlBezFOO = false;}
      if(JJTrClcdRw == true){JJTrClcdRw = false;}
      if(uUnhzmdObD == true){uUnhzmdObD = false;}
      if(lQGHTdmxBi == true){lQGHTdmxBi = false;}
      if(FbuDCiWQCK == true){FbuDCiWQCK = false;}
      if(BqhSHdfilN == true){BqhSHdfilN = false;}
      if(BkcLbrDMXY == true){BkcLbrDMXY = false;}
      if(yechqTYjfQ == true){yechqTYjfQ = false;}
      if(QNLRBtimAo == true){QNLRBtimAo = false;}
      if(xELmhTyjaK == true){xELmhTyjaK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HIQBUDXXBR
{ 
  void VIKLLnPClA()
  { 
      bool cALkBCoumy = false;
      bool zgDWlkdusj = false;
      bool feAANEHXQp = false;
      bool DnKZSbbHFm = false;
      bool OTACKDZiJL = false;
      bool PcQFryzKXx = false;
      bool uQdwuLVcEJ = false;
      bool JWoGUMdxoJ = false;
      bool dXOFaZWFgT = false;
      bool cQjIrxoEHz = false;
      bool hxezBsnKkf = false;
      bool UBVOSXCYUU = false;
      bool nQujgrlgNW = false;
      bool XYppafrODh = false;
      bool lMTBzauUoU = false;
      bool uPilLRCuSJ = false;
      bool GHwNIuLeml = false;
      bool enUmiawtkG = false;
      bool xRqsbHpDeI = false;
      bool dwwtbePGrD = false;
      string rtpuFpqBqS;
      string aPEeGcWbzq;
      string jFeGXIbQNy;
      string xClpYnQRyL;
      string fdmtBVbadH;
      string pehBIlOiXx;
      string OamrUXcNFR;
      string MFdnLFSkFB;
      string fAlGHSUjhm;
      string ZgsAxEqtZc;
      string rNULukBspD;
      string TddVQNnfjC;
      string DsfSreLcqG;
      string OYLbJSfZLW;
      string RateTwCXji;
      string QKJXZyhCTP;
      string ZXCinuSCLy;
      string hNUNjbyBzw;
      string cnsHpEOnBK;
      string jcGwxsYKpY;
      if(rtpuFpqBqS == rNULukBspD){cALkBCoumy = true;}
      else if(rNULukBspD == rtpuFpqBqS){hxezBsnKkf = true;}
      if(aPEeGcWbzq == TddVQNnfjC){zgDWlkdusj = true;}
      else if(TddVQNnfjC == aPEeGcWbzq){UBVOSXCYUU = true;}
      if(jFeGXIbQNy == DsfSreLcqG){feAANEHXQp = true;}
      else if(DsfSreLcqG == jFeGXIbQNy){nQujgrlgNW = true;}
      if(xClpYnQRyL == OYLbJSfZLW){DnKZSbbHFm = true;}
      else if(OYLbJSfZLW == xClpYnQRyL){XYppafrODh = true;}
      if(fdmtBVbadH == RateTwCXji){OTACKDZiJL = true;}
      else if(RateTwCXji == fdmtBVbadH){lMTBzauUoU = true;}
      if(pehBIlOiXx == QKJXZyhCTP){PcQFryzKXx = true;}
      else if(QKJXZyhCTP == pehBIlOiXx){uPilLRCuSJ = true;}
      if(OamrUXcNFR == ZXCinuSCLy){uQdwuLVcEJ = true;}
      else if(ZXCinuSCLy == OamrUXcNFR){GHwNIuLeml = true;}
      if(MFdnLFSkFB == hNUNjbyBzw){JWoGUMdxoJ = true;}
      if(fAlGHSUjhm == cnsHpEOnBK){dXOFaZWFgT = true;}
      if(ZgsAxEqtZc == jcGwxsYKpY){cQjIrxoEHz = true;}
      while(hNUNjbyBzw == MFdnLFSkFB){enUmiawtkG = true;}
      while(cnsHpEOnBK == cnsHpEOnBK){xRqsbHpDeI = true;}
      while(jcGwxsYKpY == jcGwxsYKpY){dwwtbePGrD = true;}
      if(cALkBCoumy == true){cALkBCoumy = false;}
      if(zgDWlkdusj == true){zgDWlkdusj = false;}
      if(feAANEHXQp == true){feAANEHXQp = false;}
      if(DnKZSbbHFm == true){DnKZSbbHFm = false;}
      if(OTACKDZiJL == true){OTACKDZiJL = false;}
      if(PcQFryzKXx == true){PcQFryzKXx = false;}
      if(uQdwuLVcEJ == true){uQdwuLVcEJ = false;}
      if(JWoGUMdxoJ == true){JWoGUMdxoJ = false;}
      if(dXOFaZWFgT == true){dXOFaZWFgT = false;}
      if(cQjIrxoEHz == true){cQjIrxoEHz = false;}
      if(hxezBsnKkf == true){hxezBsnKkf = false;}
      if(UBVOSXCYUU == true){UBVOSXCYUU = false;}
      if(nQujgrlgNW == true){nQujgrlgNW = false;}
      if(XYppafrODh == true){XYppafrODh = false;}
      if(lMTBzauUoU == true){lMTBzauUoU = false;}
      if(uPilLRCuSJ == true){uPilLRCuSJ = false;}
      if(GHwNIuLeml == true){GHwNIuLeml = false;}
      if(enUmiawtkG == true){enUmiawtkG = false;}
      if(xRqsbHpDeI == true){xRqsbHpDeI = false;}
      if(dwwtbePGrD == true){dwwtbePGrD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NNCVEOEFBN
{ 
  void zqzPzceIlK()
  { 
      bool ZjTXSzFmAs = false;
      bool KaajoPzCwi = false;
      bool qArrrYwKYr = false;
      bool aXdhmrEUrT = false;
      bool tBKidlwjpI = false;
      bool VdifQYrbfs = false;
      bool CtNHSmwrxx = false;
      bool KeKcopoJOF = false;
      bool cLUPVwnxQN = false;
      bool AcozQzmDQp = false;
      bool pDmryqTGqa = false;
      bool iiMZQpZxkV = false;
      bool yybixhoLLo = false;
      bool ClsXPYYbRe = false;
      bool cgGpdRQPhZ = false;
      bool ZoRtrqbDuQ = false;
      bool CItBXxpnJq = false;
      bool RxfGrQqkEf = false;
      bool QZclPMTyfX = false;
      bool wUgBbUmFSg = false;
      string fdmSKUoRny;
      string YPEuDNuorh;
      string yEXLTbBngB;
      string mrXjWedjzS;
      string AUhEhDgTWi;
      string ZGMfHbFbzh;
      string SAklKfqUYY;
      string jKoZhdVTdP;
      string thQxbgfrbt;
      string YCkRzziusB;
      string MMtyzOQmxd;
      string GlxjmjinKd;
      string AyrdAgZXZh;
      string tZZcChnSxM;
      string PstynlEBdO;
      string PukOAOUQyR;
      string nsMOifLUgF;
      string wQpxOHDtpN;
      string cYsKSzoLbn;
      string MWUeYVffPH;
      if(fdmSKUoRny == MMtyzOQmxd){ZjTXSzFmAs = true;}
      else if(MMtyzOQmxd == fdmSKUoRny){pDmryqTGqa = true;}
      if(YPEuDNuorh == GlxjmjinKd){KaajoPzCwi = true;}
      else if(GlxjmjinKd == YPEuDNuorh){iiMZQpZxkV = true;}
      if(yEXLTbBngB == AyrdAgZXZh){qArrrYwKYr = true;}
      else if(AyrdAgZXZh == yEXLTbBngB){yybixhoLLo = true;}
      if(mrXjWedjzS == tZZcChnSxM){aXdhmrEUrT = true;}
      else if(tZZcChnSxM == mrXjWedjzS){ClsXPYYbRe = true;}
      if(AUhEhDgTWi == PstynlEBdO){tBKidlwjpI = true;}
      else if(PstynlEBdO == AUhEhDgTWi){cgGpdRQPhZ = true;}
      if(ZGMfHbFbzh == PukOAOUQyR){VdifQYrbfs = true;}
      else if(PukOAOUQyR == ZGMfHbFbzh){ZoRtrqbDuQ = true;}
      if(SAklKfqUYY == nsMOifLUgF){CtNHSmwrxx = true;}
      else if(nsMOifLUgF == SAklKfqUYY){CItBXxpnJq = true;}
      if(jKoZhdVTdP == wQpxOHDtpN){KeKcopoJOF = true;}
      if(thQxbgfrbt == cYsKSzoLbn){cLUPVwnxQN = true;}
      if(YCkRzziusB == MWUeYVffPH){AcozQzmDQp = true;}
      while(wQpxOHDtpN == jKoZhdVTdP){RxfGrQqkEf = true;}
      while(cYsKSzoLbn == cYsKSzoLbn){QZclPMTyfX = true;}
      while(MWUeYVffPH == MWUeYVffPH){wUgBbUmFSg = true;}
      if(ZjTXSzFmAs == true){ZjTXSzFmAs = false;}
      if(KaajoPzCwi == true){KaajoPzCwi = false;}
      if(qArrrYwKYr == true){qArrrYwKYr = false;}
      if(aXdhmrEUrT == true){aXdhmrEUrT = false;}
      if(tBKidlwjpI == true){tBKidlwjpI = false;}
      if(VdifQYrbfs == true){VdifQYrbfs = false;}
      if(CtNHSmwrxx == true){CtNHSmwrxx = false;}
      if(KeKcopoJOF == true){KeKcopoJOF = false;}
      if(cLUPVwnxQN == true){cLUPVwnxQN = false;}
      if(AcozQzmDQp == true){AcozQzmDQp = false;}
      if(pDmryqTGqa == true){pDmryqTGqa = false;}
      if(iiMZQpZxkV == true){iiMZQpZxkV = false;}
      if(yybixhoLLo == true){yybixhoLLo = false;}
      if(ClsXPYYbRe == true){ClsXPYYbRe = false;}
      if(cgGpdRQPhZ == true){cgGpdRQPhZ = false;}
      if(ZoRtrqbDuQ == true){ZoRtrqbDuQ = false;}
      if(CItBXxpnJq == true){CItBXxpnJq = false;}
      if(RxfGrQqkEf == true){RxfGrQqkEf = false;}
      if(QZclPMTyfX == true){QZclPMTyfX = false;}
      if(wUgBbUmFSg == true){wUgBbUmFSg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VIGLWRCSKM
{ 
  void ohLYEINpHG()
  { 
      bool qkTkeZiTJJ = false;
      bool qbtdflojjA = false;
      bool jVKGhyhrHc = false;
      bool SbbxdUJpYm = false;
      bool gJRfIRmEQR = false;
      bool dnFHHVaNCf = false;
      bool qpLgpOzxAK = false;
      bool cyKwTZEdxQ = false;
      bool LcboyeWUoI = false;
      bool tumrwpxjpt = false;
      bool RpDGofcImh = false;
      bool QwQlUNOWiL = false;
      bool qeHrPgLSAd = false;
      bool bTnCyVYVAS = false;
      bool BNgHqyeAWh = false;
      bool baBdCmhLpH = false;
      bool TJIJGwINnz = false;
      bool nsWQJcxAAR = false;
      bool CKuRBASJzK = false;
      bool mNeryqFXAu = false;
      string tSIJwzfuPq;
      string WaGuyhQmne;
      string RAUWZlBlKx;
      string YAiSWROYEK;
      string kgdCaEJDqx;
      string KliuotxljJ;
      string xtkRRVqnXf;
      string TrhdtjVRuU;
      string bytMlmRmdc;
      string UbotMpwLkE;
      string MVeLdSDFAE;
      string XepOhzzXfe;
      string DEJuLqDnQD;
      string nJgpIFSiiT;
      string iMlYFokZMM;
      string pXfFAIMjAl;
      string PPnxQNxAGb;
      string gQoLwqRkoV;
      string GcaEMPdaoz;
      string shiwESXoIq;
      if(tSIJwzfuPq == MVeLdSDFAE){qkTkeZiTJJ = true;}
      else if(MVeLdSDFAE == tSIJwzfuPq){RpDGofcImh = true;}
      if(WaGuyhQmne == XepOhzzXfe){qbtdflojjA = true;}
      else if(XepOhzzXfe == WaGuyhQmne){QwQlUNOWiL = true;}
      if(RAUWZlBlKx == DEJuLqDnQD){jVKGhyhrHc = true;}
      else if(DEJuLqDnQD == RAUWZlBlKx){qeHrPgLSAd = true;}
      if(YAiSWROYEK == nJgpIFSiiT){SbbxdUJpYm = true;}
      else if(nJgpIFSiiT == YAiSWROYEK){bTnCyVYVAS = true;}
      if(kgdCaEJDqx == iMlYFokZMM){gJRfIRmEQR = true;}
      else if(iMlYFokZMM == kgdCaEJDqx){BNgHqyeAWh = true;}
      if(KliuotxljJ == pXfFAIMjAl){dnFHHVaNCf = true;}
      else if(pXfFAIMjAl == KliuotxljJ){baBdCmhLpH = true;}
      if(xtkRRVqnXf == PPnxQNxAGb){qpLgpOzxAK = true;}
      else if(PPnxQNxAGb == xtkRRVqnXf){TJIJGwINnz = true;}
      if(TrhdtjVRuU == gQoLwqRkoV){cyKwTZEdxQ = true;}
      if(bytMlmRmdc == GcaEMPdaoz){LcboyeWUoI = true;}
      if(UbotMpwLkE == shiwESXoIq){tumrwpxjpt = true;}
      while(gQoLwqRkoV == TrhdtjVRuU){nsWQJcxAAR = true;}
      while(GcaEMPdaoz == GcaEMPdaoz){CKuRBASJzK = true;}
      while(shiwESXoIq == shiwESXoIq){mNeryqFXAu = true;}
      if(qkTkeZiTJJ == true){qkTkeZiTJJ = false;}
      if(qbtdflojjA == true){qbtdflojjA = false;}
      if(jVKGhyhrHc == true){jVKGhyhrHc = false;}
      if(SbbxdUJpYm == true){SbbxdUJpYm = false;}
      if(gJRfIRmEQR == true){gJRfIRmEQR = false;}
      if(dnFHHVaNCf == true){dnFHHVaNCf = false;}
      if(qpLgpOzxAK == true){qpLgpOzxAK = false;}
      if(cyKwTZEdxQ == true){cyKwTZEdxQ = false;}
      if(LcboyeWUoI == true){LcboyeWUoI = false;}
      if(tumrwpxjpt == true){tumrwpxjpt = false;}
      if(RpDGofcImh == true){RpDGofcImh = false;}
      if(QwQlUNOWiL == true){QwQlUNOWiL = false;}
      if(qeHrPgLSAd == true){qeHrPgLSAd = false;}
      if(bTnCyVYVAS == true){bTnCyVYVAS = false;}
      if(BNgHqyeAWh == true){BNgHqyeAWh = false;}
      if(baBdCmhLpH == true){baBdCmhLpH = false;}
      if(TJIJGwINnz == true){TJIJGwINnz = false;}
      if(nsWQJcxAAR == true){nsWQJcxAAR = false;}
      if(CKuRBASJzK == true){CKuRBASJzK = false;}
      if(mNeryqFXAu == true){mNeryqFXAu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TEPKUTILND
{ 
  void qzDAOKtQjE()
  { 
      bool CfxcxWmrNV = false;
      bool tpPjVzaEge = false;
      bool flmUYScBJX = false;
      bool HiZYTUWymq = false;
      bool gAyUMLfSxk = false;
      bool BKcYCQscDd = false;
      bool skhoOLQqPA = false;
      bool ccQpyfmSHM = false;
      bool lKDYWxFBVD = false;
      bool bttJxuSIGB = false;
      bool uoCwHYsmaW = false;
      bool cZUprhgISR = false;
      bool GOUMYihHrC = false;
      bool NdMGRwIGQy = false;
      bool DSazZBYDQP = false;
      bool OJpoufUoXY = false;
      bool pktXIyNOYu = false;
      bool ZarTNmnUlX = false;
      bool KeqcnEmXKk = false;
      bool bSirISYCpb = false;
      string tsHpKIjgpU;
      string kuOLJZwIYX;
      string AWCpjmTJtY;
      string cSgBjOoEZh;
      string QFEjlBOOXT;
      string FQcQWWpRGW;
      string nZlRqROMbt;
      string jqipGuSSDh;
      string YFlZSMpPeM;
      string XXxCtpTlsT;
      string mBlciNhlKa;
      string EXNXyhnLze;
      string byhOWMtfwP;
      string bfZiuWTIpE;
      string dEFDHAKZEL;
      string CHmNrnTWGW;
      string TCotzYxdbb;
      string OfUtAWsdHV;
      string BTajNTrLpH;
      string CwCTkbPKEi;
      if(tsHpKIjgpU == mBlciNhlKa){CfxcxWmrNV = true;}
      else if(mBlciNhlKa == tsHpKIjgpU){uoCwHYsmaW = true;}
      if(kuOLJZwIYX == EXNXyhnLze){tpPjVzaEge = true;}
      else if(EXNXyhnLze == kuOLJZwIYX){cZUprhgISR = true;}
      if(AWCpjmTJtY == byhOWMtfwP){flmUYScBJX = true;}
      else if(byhOWMtfwP == AWCpjmTJtY){GOUMYihHrC = true;}
      if(cSgBjOoEZh == bfZiuWTIpE){HiZYTUWymq = true;}
      else if(bfZiuWTIpE == cSgBjOoEZh){NdMGRwIGQy = true;}
      if(QFEjlBOOXT == dEFDHAKZEL){gAyUMLfSxk = true;}
      else if(dEFDHAKZEL == QFEjlBOOXT){DSazZBYDQP = true;}
      if(FQcQWWpRGW == CHmNrnTWGW){BKcYCQscDd = true;}
      else if(CHmNrnTWGW == FQcQWWpRGW){OJpoufUoXY = true;}
      if(nZlRqROMbt == TCotzYxdbb){skhoOLQqPA = true;}
      else if(TCotzYxdbb == nZlRqROMbt){pktXIyNOYu = true;}
      if(jqipGuSSDh == OfUtAWsdHV){ccQpyfmSHM = true;}
      if(YFlZSMpPeM == BTajNTrLpH){lKDYWxFBVD = true;}
      if(XXxCtpTlsT == CwCTkbPKEi){bttJxuSIGB = true;}
      while(OfUtAWsdHV == jqipGuSSDh){ZarTNmnUlX = true;}
      while(BTajNTrLpH == BTajNTrLpH){KeqcnEmXKk = true;}
      while(CwCTkbPKEi == CwCTkbPKEi){bSirISYCpb = true;}
      if(CfxcxWmrNV == true){CfxcxWmrNV = false;}
      if(tpPjVzaEge == true){tpPjVzaEge = false;}
      if(flmUYScBJX == true){flmUYScBJX = false;}
      if(HiZYTUWymq == true){HiZYTUWymq = false;}
      if(gAyUMLfSxk == true){gAyUMLfSxk = false;}
      if(BKcYCQscDd == true){BKcYCQscDd = false;}
      if(skhoOLQqPA == true){skhoOLQqPA = false;}
      if(ccQpyfmSHM == true){ccQpyfmSHM = false;}
      if(lKDYWxFBVD == true){lKDYWxFBVD = false;}
      if(bttJxuSIGB == true){bttJxuSIGB = false;}
      if(uoCwHYsmaW == true){uoCwHYsmaW = false;}
      if(cZUprhgISR == true){cZUprhgISR = false;}
      if(GOUMYihHrC == true){GOUMYihHrC = false;}
      if(NdMGRwIGQy == true){NdMGRwIGQy = false;}
      if(DSazZBYDQP == true){DSazZBYDQP = false;}
      if(OJpoufUoXY == true){OJpoufUoXY = false;}
      if(pktXIyNOYu == true){pktXIyNOYu = false;}
      if(ZarTNmnUlX == true){ZarTNmnUlX = false;}
      if(KeqcnEmXKk == true){KeqcnEmXKk = false;}
      if(bSirISYCpb == true){bSirISYCpb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RVRNJTEBNZ
{ 
  void FfMjjpNHaB()
  { 
      bool rgCRzGapJd = false;
      bool XMggknpTae = false;
      bool AuqKzqzxxB = false;
      bool CXammgIjaj = false;
      bool neLUruzjpD = false;
      bool YDonGworSH = false;
      bool GcrHbzkstE = false;
      bool fGsqpVjWRE = false;
      bool rOHscyimgp = false;
      bool qQQScKlDss = false;
      bool KGplXSJxxj = false;
      bool MSZOPqVzec = false;
      bool PxLDMOoZNe = false;
      bool jfcYtkYUVJ = false;
      bool nkpxcXqCDk = false;
      bool nmXPdMtlYI = false;
      bool cjjRzfpATd = false;
      bool SBcUndHNZn = false;
      bool XlVcqxIMug = false;
      bool qlwMgEBXyw = false;
      string jPmnPYMbFU;
      string DFeNuUMMAV;
      string kwCtaThnKp;
      string SDWAojNrpw;
      string pSeDuQrYLt;
      string IpuKbnMsMw;
      string qXQPCzheYL;
      string GTVDfRQyyK;
      string aJcPgbIMXA;
      string WTftFRCOBu;
      string hNAAmnTqeK;
      string XNuCUhtBiZ;
      string qVGXnmnbxN;
      string PBxDbNIcbr;
      string IQgMcIYcYX;
      string XAfbELGbLA;
      string ArsQtVQqaG;
      string YQYpRZntue;
      string OLCZpPUVzP;
      string HgRbrPXPSH;
      if(jPmnPYMbFU == hNAAmnTqeK){rgCRzGapJd = true;}
      else if(hNAAmnTqeK == jPmnPYMbFU){KGplXSJxxj = true;}
      if(DFeNuUMMAV == XNuCUhtBiZ){XMggknpTae = true;}
      else if(XNuCUhtBiZ == DFeNuUMMAV){MSZOPqVzec = true;}
      if(kwCtaThnKp == qVGXnmnbxN){AuqKzqzxxB = true;}
      else if(qVGXnmnbxN == kwCtaThnKp){PxLDMOoZNe = true;}
      if(SDWAojNrpw == PBxDbNIcbr){CXammgIjaj = true;}
      else if(PBxDbNIcbr == SDWAojNrpw){jfcYtkYUVJ = true;}
      if(pSeDuQrYLt == IQgMcIYcYX){neLUruzjpD = true;}
      else if(IQgMcIYcYX == pSeDuQrYLt){nkpxcXqCDk = true;}
      if(IpuKbnMsMw == XAfbELGbLA){YDonGworSH = true;}
      else if(XAfbELGbLA == IpuKbnMsMw){nmXPdMtlYI = true;}
      if(qXQPCzheYL == ArsQtVQqaG){GcrHbzkstE = true;}
      else if(ArsQtVQqaG == qXQPCzheYL){cjjRzfpATd = true;}
      if(GTVDfRQyyK == YQYpRZntue){fGsqpVjWRE = true;}
      if(aJcPgbIMXA == OLCZpPUVzP){rOHscyimgp = true;}
      if(WTftFRCOBu == HgRbrPXPSH){qQQScKlDss = true;}
      while(YQYpRZntue == GTVDfRQyyK){SBcUndHNZn = true;}
      while(OLCZpPUVzP == OLCZpPUVzP){XlVcqxIMug = true;}
      while(HgRbrPXPSH == HgRbrPXPSH){qlwMgEBXyw = true;}
      if(rgCRzGapJd == true){rgCRzGapJd = false;}
      if(XMggknpTae == true){XMggknpTae = false;}
      if(AuqKzqzxxB == true){AuqKzqzxxB = false;}
      if(CXammgIjaj == true){CXammgIjaj = false;}
      if(neLUruzjpD == true){neLUruzjpD = false;}
      if(YDonGworSH == true){YDonGworSH = false;}
      if(GcrHbzkstE == true){GcrHbzkstE = false;}
      if(fGsqpVjWRE == true){fGsqpVjWRE = false;}
      if(rOHscyimgp == true){rOHscyimgp = false;}
      if(qQQScKlDss == true){qQQScKlDss = false;}
      if(KGplXSJxxj == true){KGplXSJxxj = false;}
      if(MSZOPqVzec == true){MSZOPqVzec = false;}
      if(PxLDMOoZNe == true){PxLDMOoZNe = false;}
      if(jfcYtkYUVJ == true){jfcYtkYUVJ = false;}
      if(nkpxcXqCDk == true){nkpxcXqCDk = false;}
      if(nmXPdMtlYI == true){nmXPdMtlYI = false;}
      if(cjjRzfpATd == true){cjjRzfpATd = false;}
      if(SBcUndHNZn == true){SBcUndHNZn = false;}
      if(XlVcqxIMug == true){XlVcqxIMug = false;}
      if(qlwMgEBXyw == true){qlwMgEBXyw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UAGVAFNUAG
{ 
  void WtNLqBlFFK()
  { 
      bool CNAZEfYANw = false;
      bool gMRxZzGDXD = false;
      bool gfrBLfLFat = false;
      bool QUTzVxzlGy = false;
      bool DolnRoAZgE = false;
      bool kWbzyWVyOY = false;
      bool TTZTfLrSbc = false;
      bool zTwZzrsDjW = false;
      bool elXWIssUBy = false;
      bool bAWhdiOSHG = false;
      bool whyEEQZBzF = false;
      bool cROrthuCKm = false;
      bool RXRcBzxNwQ = false;
      bool cawdZxmTRr = false;
      bool SqVuVJkenu = false;
      bool nMHUnYPVCF = false;
      bool TLFhbCUkRw = false;
      bool ubjSTaBVHq = false;
      bool NRZAcQSaoB = false;
      bool gRQMXHkmTS = false;
      string DpFpHJOAwE;
      string dsHsKiioHX;
      string jeOKPnAROK;
      string fdabRpmdEa;
      string mdyTSpRFxi;
      string GDKeAXataT;
      string JwklXzSeaU;
      string uEkfjGgurY;
      string WtUfEcTwbs;
      string OsDkRqrMuT;
      string XlebmBSdtt;
      string qfCBxObFgu;
      string fVDgGCBzOs;
      string OTzYAjPrrD;
      string JoBgChqBmD;
      string OlezmBhxUk;
      string zSPBeWfcAM;
      string yiMdkpUVeX;
      string KAMLdboAky;
      string BSWHDqZzCf;
      if(DpFpHJOAwE == XlebmBSdtt){CNAZEfYANw = true;}
      else if(XlebmBSdtt == DpFpHJOAwE){whyEEQZBzF = true;}
      if(dsHsKiioHX == qfCBxObFgu){gMRxZzGDXD = true;}
      else if(qfCBxObFgu == dsHsKiioHX){cROrthuCKm = true;}
      if(jeOKPnAROK == fVDgGCBzOs){gfrBLfLFat = true;}
      else if(fVDgGCBzOs == jeOKPnAROK){RXRcBzxNwQ = true;}
      if(fdabRpmdEa == OTzYAjPrrD){QUTzVxzlGy = true;}
      else if(OTzYAjPrrD == fdabRpmdEa){cawdZxmTRr = true;}
      if(mdyTSpRFxi == JoBgChqBmD){DolnRoAZgE = true;}
      else if(JoBgChqBmD == mdyTSpRFxi){SqVuVJkenu = true;}
      if(GDKeAXataT == OlezmBhxUk){kWbzyWVyOY = true;}
      else if(OlezmBhxUk == GDKeAXataT){nMHUnYPVCF = true;}
      if(JwklXzSeaU == zSPBeWfcAM){TTZTfLrSbc = true;}
      else if(zSPBeWfcAM == JwklXzSeaU){TLFhbCUkRw = true;}
      if(uEkfjGgurY == yiMdkpUVeX){zTwZzrsDjW = true;}
      if(WtUfEcTwbs == KAMLdboAky){elXWIssUBy = true;}
      if(OsDkRqrMuT == BSWHDqZzCf){bAWhdiOSHG = true;}
      while(yiMdkpUVeX == uEkfjGgurY){ubjSTaBVHq = true;}
      while(KAMLdboAky == KAMLdboAky){NRZAcQSaoB = true;}
      while(BSWHDqZzCf == BSWHDqZzCf){gRQMXHkmTS = true;}
      if(CNAZEfYANw == true){CNAZEfYANw = false;}
      if(gMRxZzGDXD == true){gMRxZzGDXD = false;}
      if(gfrBLfLFat == true){gfrBLfLFat = false;}
      if(QUTzVxzlGy == true){QUTzVxzlGy = false;}
      if(DolnRoAZgE == true){DolnRoAZgE = false;}
      if(kWbzyWVyOY == true){kWbzyWVyOY = false;}
      if(TTZTfLrSbc == true){TTZTfLrSbc = false;}
      if(zTwZzrsDjW == true){zTwZzrsDjW = false;}
      if(elXWIssUBy == true){elXWIssUBy = false;}
      if(bAWhdiOSHG == true){bAWhdiOSHG = false;}
      if(whyEEQZBzF == true){whyEEQZBzF = false;}
      if(cROrthuCKm == true){cROrthuCKm = false;}
      if(RXRcBzxNwQ == true){RXRcBzxNwQ = false;}
      if(cawdZxmTRr == true){cawdZxmTRr = false;}
      if(SqVuVJkenu == true){SqVuVJkenu = false;}
      if(nMHUnYPVCF == true){nMHUnYPVCF = false;}
      if(TLFhbCUkRw == true){TLFhbCUkRw = false;}
      if(ubjSTaBVHq == true){ubjSTaBVHq = false;}
      if(NRZAcQSaoB == true){NRZAcQSaoB = false;}
      if(gRQMXHkmTS == true){gRQMXHkmTS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BLXDLXVFVG
{ 
  void blIjrYUtPj()
  { 
      bool DlrBhtPhji = false;
      bool GydJWRDqeC = false;
      bool WmpKqJktka = false;
      bool izalKCRgZD = false;
      bool uONJVBRPkj = false;
      bool tudWGQuhKX = false;
      bool JUxIAGXqzT = false;
      bool AWRaHIYgnp = false;
      bool rUJBgmVDfs = false;
      bool GiVBtZQEIP = false;
      bool caQQjWdCPx = false;
      bool qNsTfnLubN = false;
      bool kUKFMQAPgg = false;
      bool qUYYMRErRJ = false;
      bool JTnhCrpBVF = false;
      bool OVcueIPLES = false;
      bool WOVhFWoTHO = false;
      bool jSdRERfcCT = false;
      bool aysaSVqctE = false;
      bool CrnymuxFbe = false;
      string yLHzVFHjca;
      string qTIfiLrXDy;
      string PFtNUsLeYQ;
      string VCIneyxpMa;
      string lyAVCTHLJj;
      string TYVqIsQsec;
      string tbKMEoKTBj;
      string OBLbMRFYLA;
      string lzVowwfQfl;
      string gDKjgKnmQN;
      string ImKZVSNteq;
      string mrheptGVQH;
      string ItnPCKpbtC;
      string cSHyqyowSd;
      string illnynVfsl;
      string ERVJFOztWL;
      string blzcNTkimq;
      string EJCmYVIAQN;
      string nKhHxLwysc;
      string zuYHBxmIZd;
      if(yLHzVFHjca == ImKZVSNteq){DlrBhtPhji = true;}
      else if(ImKZVSNteq == yLHzVFHjca){caQQjWdCPx = true;}
      if(qTIfiLrXDy == mrheptGVQH){GydJWRDqeC = true;}
      else if(mrheptGVQH == qTIfiLrXDy){qNsTfnLubN = true;}
      if(PFtNUsLeYQ == ItnPCKpbtC){WmpKqJktka = true;}
      else if(ItnPCKpbtC == PFtNUsLeYQ){kUKFMQAPgg = true;}
      if(VCIneyxpMa == cSHyqyowSd){izalKCRgZD = true;}
      else if(cSHyqyowSd == VCIneyxpMa){qUYYMRErRJ = true;}
      if(lyAVCTHLJj == illnynVfsl){uONJVBRPkj = true;}
      else if(illnynVfsl == lyAVCTHLJj){JTnhCrpBVF = true;}
      if(TYVqIsQsec == ERVJFOztWL){tudWGQuhKX = true;}
      else if(ERVJFOztWL == TYVqIsQsec){OVcueIPLES = true;}
      if(tbKMEoKTBj == blzcNTkimq){JUxIAGXqzT = true;}
      else if(blzcNTkimq == tbKMEoKTBj){WOVhFWoTHO = true;}
      if(OBLbMRFYLA == EJCmYVIAQN){AWRaHIYgnp = true;}
      if(lzVowwfQfl == nKhHxLwysc){rUJBgmVDfs = true;}
      if(gDKjgKnmQN == zuYHBxmIZd){GiVBtZQEIP = true;}
      while(EJCmYVIAQN == OBLbMRFYLA){jSdRERfcCT = true;}
      while(nKhHxLwysc == nKhHxLwysc){aysaSVqctE = true;}
      while(zuYHBxmIZd == zuYHBxmIZd){CrnymuxFbe = true;}
      if(DlrBhtPhji == true){DlrBhtPhji = false;}
      if(GydJWRDqeC == true){GydJWRDqeC = false;}
      if(WmpKqJktka == true){WmpKqJktka = false;}
      if(izalKCRgZD == true){izalKCRgZD = false;}
      if(uONJVBRPkj == true){uONJVBRPkj = false;}
      if(tudWGQuhKX == true){tudWGQuhKX = false;}
      if(JUxIAGXqzT == true){JUxIAGXqzT = false;}
      if(AWRaHIYgnp == true){AWRaHIYgnp = false;}
      if(rUJBgmVDfs == true){rUJBgmVDfs = false;}
      if(GiVBtZQEIP == true){GiVBtZQEIP = false;}
      if(caQQjWdCPx == true){caQQjWdCPx = false;}
      if(qNsTfnLubN == true){qNsTfnLubN = false;}
      if(kUKFMQAPgg == true){kUKFMQAPgg = false;}
      if(qUYYMRErRJ == true){qUYYMRErRJ = false;}
      if(JTnhCrpBVF == true){JTnhCrpBVF = false;}
      if(OVcueIPLES == true){OVcueIPLES = false;}
      if(WOVhFWoTHO == true){WOVhFWoTHO = false;}
      if(jSdRERfcCT == true){jSdRERfcCT = false;}
      if(aysaSVqctE == true){aysaSVqctE = false;}
      if(CrnymuxFbe == true){CrnymuxFbe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HOGNXPZJAO
{ 
  void PxrBMBsJLt()
  { 
      bool FgFJobcGiX = false;
      bool OyTzaBdSwz = false;
      bool jZybgRrxCQ = false;
      bool fkymVrKpcE = false;
      bool ryKqaXDQyW = false;
      bool sLdbpehdbX = false;
      bool ifESrcAfch = false;
      bool qnpqGkPGAJ = false;
      bool NbyfWTHVxq = false;
      bool JfNEVMtqzy = false;
      bool XWnPeFVlUF = false;
      bool OacSKHhXuX = false;
      bool UdilYKZkVt = false;
      bool pYHCkpmhAR = false;
      bool yVAqbhDutN = false;
      bool eVuacsnCqT = false;
      bool fjQaOpTZgT = false;
      bool TzXcYzcqJp = false;
      bool HdqHOUcgZr = false;
      bool CkpflOEZck = false;
      string LtRsoMYdEz;
      string bGJelKieDE;
      string zwdtGyBFpr;
      string OBsxHagqDi;
      string DiKykBHimx;
      string xTCwIOQXlp;
      string LSnLkZMLWL;
      string drbUBQleJF;
      string qRSrutyxos;
      string KJENXjuyNK;
      string ouMbTErhtq;
      string ckNgzszuQp;
      string aOWdAUmNwR;
      string VmRzPuFqYp;
      string CQDxPYuWNd;
      string jzhXiZXhaz;
      string RdlcVoTORE;
      string nIWanKLZOb;
      string YPASgVFsPo;
      string WWPYXXeZba;
      if(LtRsoMYdEz == ouMbTErhtq){FgFJobcGiX = true;}
      else if(ouMbTErhtq == LtRsoMYdEz){XWnPeFVlUF = true;}
      if(bGJelKieDE == ckNgzszuQp){OyTzaBdSwz = true;}
      else if(ckNgzszuQp == bGJelKieDE){OacSKHhXuX = true;}
      if(zwdtGyBFpr == aOWdAUmNwR){jZybgRrxCQ = true;}
      else if(aOWdAUmNwR == zwdtGyBFpr){UdilYKZkVt = true;}
      if(OBsxHagqDi == VmRzPuFqYp){fkymVrKpcE = true;}
      else if(VmRzPuFqYp == OBsxHagqDi){pYHCkpmhAR = true;}
      if(DiKykBHimx == CQDxPYuWNd){ryKqaXDQyW = true;}
      else if(CQDxPYuWNd == DiKykBHimx){yVAqbhDutN = true;}
      if(xTCwIOQXlp == jzhXiZXhaz){sLdbpehdbX = true;}
      else if(jzhXiZXhaz == xTCwIOQXlp){eVuacsnCqT = true;}
      if(LSnLkZMLWL == RdlcVoTORE){ifESrcAfch = true;}
      else if(RdlcVoTORE == LSnLkZMLWL){fjQaOpTZgT = true;}
      if(drbUBQleJF == nIWanKLZOb){qnpqGkPGAJ = true;}
      if(qRSrutyxos == YPASgVFsPo){NbyfWTHVxq = true;}
      if(KJENXjuyNK == WWPYXXeZba){JfNEVMtqzy = true;}
      while(nIWanKLZOb == drbUBQleJF){TzXcYzcqJp = true;}
      while(YPASgVFsPo == YPASgVFsPo){HdqHOUcgZr = true;}
      while(WWPYXXeZba == WWPYXXeZba){CkpflOEZck = true;}
      if(FgFJobcGiX == true){FgFJobcGiX = false;}
      if(OyTzaBdSwz == true){OyTzaBdSwz = false;}
      if(jZybgRrxCQ == true){jZybgRrxCQ = false;}
      if(fkymVrKpcE == true){fkymVrKpcE = false;}
      if(ryKqaXDQyW == true){ryKqaXDQyW = false;}
      if(sLdbpehdbX == true){sLdbpehdbX = false;}
      if(ifESrcAfch == true){ifESrcAfch = false;}
      if(qnpqGkPGAJ == true){qnpqGkPGAJ = false;}
      if(NbyfWTHVxq == true){NbyfWTHVxq = false;}
      if(JfNEVMtqzy == true){JfNEVMtqzy = false;}
      if(XWnPeFVlUF == true){XWnPeFVlUF = false;}
      if(OacSKHhXuX == true){OacSKHhXuX = false;}
      if(UdilYKZkVt == true){UdilYKZkVt = false;}
      if(pYHCkpmhAR == true){pYHCkpmhAR = false;}
      if(yVAqbhDutN == true){yVAqbhDutN = false;}
      if(eVuacsnCqT == true){eVuacsnCqT = false;}
      if(fjQaOpTZgT == true){fjQaOpTZgT = false;}
      if(TzXcYzcqJp == true){TzXcYzcqJp = false;}
      if(HdqHOUcgZr == true){HdqHOUcgZr = false;}
      if(CkpflOEZck == true){CkpflOEZck = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJICTXDJLZ
{ 
  void thPnueoTCD()
  { 
      bool NODjcalSVL = false;
      bool pMbMkePEoq = false;
      bool HHCzguRroB = false;
      bool pfipoRpJhL = false;
      bool JSPrfcashi = false;
      bool YOfhYFLDDg = false;
      bool IscUUJdkXT = false;
      bool nFVdgorJTE = false;
      bool TYKGbbzBQi = false;
      bool FmGACQouXV = false;
      bool yoVNtTrCAj = false;
      bool NCiyNiiWrr = false;
      bool JbTnOByVaP = false;
      bool zxlxFeDwLI = false;
      bool ixAgVDDImS = false;
      bool hSCeLWUhzs = false;
      bool UWakjQPkri = false;
      bool flKiIMbmSK = false;
      bool xphHhgtGki = false;
      bool JVwSnMVPxE = false;
      string NhrwkEgZPJ;
      string YKeKzQcNgS;
      string ousaGCKlXw;
      string MxBQpnPAWU;
      string nydwoACOmS;
      string TCNqXRoQph;
      string ttCSxbJNUL;
      string AcqLepRxlF;
      string AuzEcJjJsY;
      string zzJoZtwKzM;
      string qotbSqLBMg;
      string zqejhzuxom;
      string rzTwLASBlk;
      string tGxYOKBWkl;
      string yhxLYHUYHa;
      string yyVLUrUyQR;
      string XJPbmrtFVW;
      string yXMDoJBHWD;
      string fstKlwklDV;
      string oCGTNnSVYf;
      if(NhrwkEgZPJ == qotbSqLBMg){NODjcalSVL = true;}
      else if(qotbSqLBMg == NhrwkEgZPJ){yoVNtTrCAj = true;}
      if(YKeKzQcNgS == zqejhzuxom){pMbMkePEoq = true;}
      else if(zqejhzuxom == YKeKzQcNgS){NCiyNiiWrr = true;}
      if(ousaGCKlXw == rzTwLASBlk){HHCzguRroB = true;}
      else if(rzTwLASBlk == ousaGCKlXw){JbTnOByVaP = true;}
      if(MxBQpnPAWU == tGxYOKBWkl){pfipoRpJhL = true;}
      else if(tGxYOKBWkl == MxBQpnPAWU){zxlxFeDwLI = true;}
      if(nydwoACOmS == yhxLYHUYHa){JSPrfcashi = true;}
      else if(yhxLYHUYHa == nydwoACOmS){ixAgVDDImS = true;}
      if(TCNqXRoQph == yyVLUrUyQR){YOfhYFLDDg = true;}
      else if(yyVLUrUyQR == TCNqXRoQph){hSCeLWUhzs = true;}
      if(ttCSxbJNUL == XJPbmrtFVW){IscUUJdkXT = true;}
      else if(XJPbmrtFVW == ttCSxbJNUL){UWakjQPkri = true;}
      if(AcqLepRxlF == yXMDoJBHWD){nFVdgorJTE = true;}
      if(AuzEcJjJsY == fstKlwklDV){TYKGbbzBQi = true;}
      if(zzJoZtwKzM == oCGTNnSVYf){FmGACQouXV = true;}
      while(yXMDoJBHWD == AcqLepRxlF){flKiIMbmSK = true;}
      while(fstKlwklDV == fstKlwklDV){xphHhgtGki = true;}
      while(oCGTNnSVYf == oCGTNnSVYf){JVwSnMVPxE = true;}
      if(NODjcalSVL == true){NODjcalSVL = false;}
      if(pMbMkePEoq == true){pMbMkePEoq = false;}
      if(HHCzguRroB == true){HHCzguRroB = false;}
      if(pfipoRpJhL == true){pfipoRpJhL = false;}
      if(JSPrfcashi == true){JSPrfcashi = false;}
      if(YOfhYFLDDg == true){YOfhYFLDDg = false;}
      if(IscUUJdkXT == true){IscUUJdkXT = false;}
      if(nFVdgorJTE == true){nFVdgorJTE = false;}
      if(TYKGbbzBQi == true){TYKGbbzBQi = false;}
      if(FmGACQouXV == true){FmGACQouXV = false;}
      if(yoVNtTrCAj == true){yoVNtTrCAj = false;}
      if(NCiyNiiWrr == true){NCiyNiiWrr = false;}
      if(JbTnOByVaP == true){JbTnOByVaP = false;}
      if(zxlxFeDwLI == true){zxlxFeDwLI = false;}
      if(ixAgVDDImS == true){ixAgVDDImS = false;}
      if(hSCeLWUhzs == true){hSCeLWUhzs = false;}
      if(UWakjQPkri == true){UWakjQPkri = false;}
      if(flKiIMbmSK == true){flKiIMbmSK = false;}
      if(xphHhgtGki == true){xphHhgtGki = false;}
      if(JVwSnMVPxE == true){JVwSnMVPxE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WLWEAFFPDY
{ 
  void BfIbpdeiWR()
  { 
      bool KWhxzhrTAS = false;
      bool rPMzndrpJO = false;
      bool LMoDOwBAxx = false;
      bool VJTLrFcbVS = false;
      bool jYRUQfyuUj = false;
      bool wnWtjxhdiD = false;
      bool gqWCwiuAGh = false;
      bool AQUpdmtTmi = false;
      bool xFeMAglZbt = false;
      bool XzsSlrBOXh = false;
      bool jynljfTfPw = false;
      bool CNqzFaMJCO = false;
      bool wVXLKBXBEl = false;
      bool kfuFzzQrcU = false;
      bool NGJerKIsNL = false;
      bool erMJlNZcbi = false;
      bool HSbcKWRlAF = false;
      bool JTghBoLsTA = false;
      bool rdmrGsSlSk = false;
      bool ZnQtMudgTU = false;
      string TrNCddubNl;
      string ZpzNVzTwUJ;
      string HYTJoXeJXA;
      string nyZEYAnMLu;
      string HqGfngPTQE;
      string CiPrktYEMG;
      string zkEMybPunU;
      string KGkZBQRmUI;
      string ILrTyEhhTd;
      string bizEuWlsgM;
      string QTeusuxppT;
      string ckjExnrkOt;
      string shbJsbGfde;
      string dXFHqnfxaD;
      string GrqzBpzuHH;
      string dBemThrUCQ;
      string oRMKpEebMJ;
      string HuJLmBpcID;
      string cLYVBbrSmI;
      string uKtJNoegIw;
      if(TrNCddubNl == QTeusuxppT){KWhxzhrTAS = true;}
      else if(QTeusuxppT == TrNCddubNl){jynljfTfPw = true;}
      if(ZpzNVzTwUJ == ckjExnrkOt){rPMzndrpJO = true;}
      else if(ckjExnrkOt == ZpzNVzTwUJ){CNqzFaMJCO = true;}
      if(HYTJoXeJXA == shbJsbGfde){LMoDOwBAxx = true;}
      else if(shbJsbGfde == HYTJoXeJXA){wVXLKBXBEl = true;}
      if(nyZEYAnMLu == dXFHqnfxaD){VJTLrFcbVS = true;}
      else if(dXFHqnfxaD == nyZEYAnMLu){kfuFzzQrcU = true;}
      if(HqGfngPTQE == GrqzBpzuHH){jYRUQfyuUj = true;}
      else if(GrqzBpzuHH == HqGfngPTQE){NGJerKIsNL = true;}
      if(CiPrktYEMG == dBemThrUCQ){wnWtjxhdiD = true;}
      else if(dBemThrUCQ == CiPrktYEMG){erMJlNZcbi = true;}
      if(zkEMybPunU == oRMKpEebMJ){gqWCwiuAGh = true;}
      else if(oRMKpEebMJ == zkEMybPunU){HSbcKWRlAF = true;}
      if(KGkZBQRmUI == HuJLmBpcID){AQUpdmtTmi = true;}
      if(ILrTyEhhTd == cLYVBbrSmI){xFeMAglZbt = true;}
      if(bizEuWlsgM == uKtJNoegIw){XzsSlrBOXh = true;}
      while(HuJLmBpcID == KGkZBQRmUI){JTghBoLsTA = true;}
      while(cLYVBbrSmI == cLYVBbrSmI){rdmrGsSlSk = true;}
      while(uKtJNoegIw == uKtJNoegIw){ZnQtMudgTU = true;}
      if(KWhxzhrTAS == true){KWhxzhrTAS = false;}
      if(rPMzndrpJO == true){rPMzndrpJO = false;}
      if(LMoDOwBAxx == true){LMoDOwBAxx = false;}
      if(VJTLrFcbVS == true){VJTLrFcbVS = false;}
      if(jYRUQfyuUj == true){jYRUQfyuUj = false;}
      if(wnWtjxhdiD == true){wnWtjxhdiD = false;}
      if(gqWCwiuAGh == true){gqWCwiuAGh = false;}
      if(AQUpdmtTmi == true){AQUpdmtTmi = false;}
      if(xFeMAglZbt == true){xFeMAglZbt = false;}
      if(XzsSlrBOXh == true){XzsSlrBOXh = false;}
      if(jynljfTfPw == true){jynljfTfPw = false;}
      if(CNqzFaMJCO == true){CNqzFaMJCO = false;}
      if(wVXLKBXBEl == true){wVXLKBXBEl = false;}
      if(kfuFzzQrcU == true){kfuFzzQrcU = false;}
      if(NGJerKIsNL == true){NGJerKIsNL = false;}
      if(erMJlNZcbi == true){erMJlNZcbi = false;}
      if(HSbcKWRlAF == true){HSbcKWRlAF = false;}
      if(JTghBoLsTA == true){JTghBoLsTA = false;}
      if(rdmrGsSlSk == true){rdmrGsSlSk = false;}
      if(ZnQtMudgTU == true){ZnQtMudgTU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TRCNVTKVNQ
{ 
  void EizDwZOIhM()
  { 
      bool hdhymQzZdx = false;
      bool zrfRKlYorf = false;
      bool gyGiJHhUYz = false;
      bool mUNtZmotgU = false;
      bool XYBcKHGqVq = false;
      bool lKGCnjWzne = false;
      bool idBeKdekqX = false;
      bool xeIWHIwcYC = false;
      bool BpzgMbOKFp = false;
      bool PpFCltWVSf = false;
      bool cUzxtGCitf = false;
      bool msZldrdTRh = false;
      bool PTfBHGZFjN = false;
      bool kZKrYfpBlG = false;
      bool ZePZCVPSXt = false;
      bool PCDjQIoyom = false;
      bool gwzguMhgMx = false;
      bool CbgLIjDFyk = false;
      bool qGgpyhWabQ = false;
      bool prMzYcfidp = false;
      string qFcOisMamI;
      string FHNZicHYna;
      string PsKoCZZEDC;
      string XoJTEEsJQc;
      string shBMwLPgYo;
      string GbUGIxumLJ;
      string THXkjPysVd;
      string jxIKghqxrp;
      string KreNwwTCLG;
      string JGyHJkKQcg;
      string NVKuFISKZZ;
      string FytVybcJon;
      string wugPTczBBu;
      string WaTLbngjIm;
      string cJckALMbIg;
      string IAbnjSnuab;
      string JRJdCedhsJ;
      string trBCKmSwPI;
      string QXrTlWyfaJ;
      string AlJfcLzyhU;
      if(qFcOisMamI == NVKuFISKZZ){hdhymQzZdx = true;}
      else if(NVKuFISKZZ == qFcOisMamI){cUzxtGCitf = true;}
      if(FHNZicHYna == FytVybcJon){zrfRKlYorf = true;}
      else if(FytVybcJon == FHNZicHYna){msZldrdTRh = true;}
      if(PsKoCZZEDC == wugPTczBBu){gyGiJHhUYz = true;}
      else if(wugPTczBBu == PsKoCZZEDC){PTfBHGZFjN = true;}
      if(XoJTEEsJQc == WaTLbngjIm){mUNtZmotgU = true;}
      else if(WaTLbngjIm == XoJTEEsJQc){kZKrYfpBlG = true;}
      if(shBMwLPgYo == cJckALMbIg){XYBcKHGqVq = true;}
      else if(cJckALMbIg == shBMwLPgYo){ZePZCVPSXt = true;}
      if(GbUGIxumLJ == IAbnjSnuab){lKGCnjWzne = true;}
      else if(IAbnjSnuab == GbUGIxumLJ){PCDjQIoyom = true;}
      if(THXkjPysVd == JRJdCedhsJ){idBeKdekqX = true;}
      else if(JRJdCedhsJ == THXkjPysVd){gwzguMhgMx = true;}
      if(jxIKghqxrp == trBCKmSwPI){xeIWHIwcYC = true;}
      if(KreNwwTCLG == QXrTlWyfaJ){BpzgMbOKFp = true;}
      if(JGyHJkKQcg == AlJfcLzyhU){PpFCltWVSf = true;}
      while(trBCKmSwPI == jxIKghqxrp){CbgLIjDFyk = true;}
      while(QXrTlWyfaJ == QXrTlWyfaJ){qGgpyhWabQ = true;}
      while(AlJfcLzyhU == AlJfcLzyhU){prMzYcfidp = true;}
      if(hdhymQzZdx == true){hdhymQzZdx = false;}
      if(zrfRKlYorf == true){zrfRKlYorf = false;}
      if(gyGiJHhUYz == true){gyGiJHhUYz = false;}
      if(mUNtZmotgU == true){mUNtZmotgU = false;}
      if(XYBcKHGqVq == true){XYBcKHGqVq = false;}
      if(lKGCnjWzne == true){lKGCnjWzne = false;}
      if(idBeKdekqX == true){idBeKdekqX = false;}
      if(xeIWHIwcYC == true){xeIWHIwcYC = false;}
      if(BpzgMbOKFp == true){BpzgMbOKFp = false;}
      if(PpFCltWVSf == true){PpFCltWVSf = false;}
      if(cUzxtGCitf == true){cUzxtGCitf = false;}
      if(msZldrdTRh == true){msZldrdTRh = false;}
      if(PTfBHGZFjN == true){PTfBHGZFjN = false;}
      if(kZKrYfpBlG == true){kZKrYfpBlG = false;}
      if(ZePZCVPSXt == true){ZePZCVPSXt = false;}
      if(PCDjQIoyom == true){PCDjQIoyom = false;}
      if(gwzguMhgMx == true){gwzguMhgMx = false;}
      if(CbgLIjDFyk == true){CbgLIjDFyk = false;}
      if(qGgpyhWabQ == true){qGgpyhWabQ = false;}
      if(prMzYcfidp == true){prMzYcfidp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFBNXLHBYG
{ 
  void YNxZZsYheQ()
  { 
      bool oZUFOIfMqm = false;
      bool rzIdzKxMjm = false;
      bool xrLGzJgXVg = false;
      bool XzUETzUVFB = false;
      bool liRQItliom = false;
      bool bZmXixONGE = false;
      bool aHpKPseEJA = false;
      bool oaGiBNZtxE = false;
      bool XyhiFyMwUV = false;
      bool kHPAZdsHBP = false;
      bool PhYoxASDWV = false;
      bool XTPBgbZHER = false;
      bool fhimPhKGJX = false;
      bool URshooZskE = false;
      bool eIZzyQrOSx = false;
      bool DkCjihylYP = false;
      bool oMtzAFZgMr = false;
      bool CfVzlXIjny = false;
      bool pwmLTiOJyH = false;
      bool pmUUPSOayr = false;
      string ufNhQbKelr;
      string VCxlTRUZql;
      string XDNUmAtdEF;
      string pEoWkSyyhr;
      string dteEqRAEoE;
      string orRPrrRsuQ;
      string hgZgCQNZBB;
      string SVqyIdYIcU;
      string zpnzPymYer;
      string AFDQKwTxBa;
      string EZCnlSATHO;
      string TIQZRrsaQE;
      string cnuJBNSamM;
      string JaHBQYmzNx;
      string ySRPYqnczS;
      string CrfxxPesmX;
      string zYgtErBOIs;
      string EtMTFKWfjJ;
      string YobTJRuJDB;
      string stMoxYlWLf;
      if(ufNhQbKelr == EZCnlSATHO){oZUFOIfMqm = true;}
      else if(EZCnlSATHO == ufNhQbKelr){PhYoxASDWV = true;}
      if(VCxlTRUZql == TIQZRrsaQE){rzIdzKxMjm = true;}
      else if(TIQZRrsaQE == VCxlTRUZql){XTPBgbZHER = true;}
      if(XDNUmAtdEF == cnuJBNSamM){xrLGzJgXVg = true;}
      else if(cnuJBNSamM == XDNUmAtdEF){fhimPhKGJX = true;}
      if(pEoWkSyyhr == JaHBQYmzNx){XzUETzUVFB = true;}
      else if(JaHBQYmzNx == pEoWkSyyhr){URshooZskE = true;}
      if(dteEqRAEoE == ySRPYqnczS){liRQItliom = true;}
      else if(ySRPYqnczS == dteEqRAEoE){eIZzyQrOSx = true;}
      if(orRPrrRsuQ == CrfxxPesmX){bZmXixONGE = true;}
      else if(CrfxxPesmX == orRPrrRsuQ){DkCjihylYP = true;}
      if(hgZgCQNZBB == zYgtErBOIs){aHpKPseEJA = true;}
      else if(zYgtErBOIs == hgZgCQNZBB){oMtzAFZgMr = true;}
      if(SVqyIdYIcU == EtMTFKWfjJ){oaGiBNZtxE = true;}
      if(zpnzPymYer == YobTJRuJDB){XyhiFyMwUV = true;}
      if(AFDQKwTxBa == stMoxYlWLf){kHPAZdsHBP = true;}
      while(EtMTFKWfjJ == SVqyIdYIcU){CfVzlXIjny = true;}
      while(YobTJRuJDB == YobTJRuJDB){pwmLTiOJyH = true;}
      while(stMoxYlWLf == stMoxYlWLf){pmUUPSOayr = true;}
      if(oZUFOIfMqm == true){oZUFOIfMqm = false;}
      if(rzIdzKxMjm == true){rzIdzKxMjm = false;}
      if(xrLGzJgXVg == true){xrLGzJgXVg = false;}
      if(XzUETzUVFB == true){XzUETzUVFB = false;}
      if(liRQItliom == true){liRQItliom = false;}
      if(bZmXixONGE == true){bZmXixONGE = false;}
      if(aHpKPseEJA == true){aHpKPseEJA = false;}
      if(oaGiBNZtxE == true){oaGiBNZtxE = false;}
      if(XyhiFyMwUV == true){XyhiFyMwUV = false;}
      if(kHPAZdsHBP == true){kHPAZdsHBP = false;}
      if(PhYoxASDWV == true){PhYoxASDWV = false;}
      if(XTPBgbZHER == true){XTPBgbZHER = false;}
      if(fhimPhKGJX == true){fhimPhKGJX = false;}
      if(URshooZskE == true){URshooZskE = false;}
      if(eIZzyQrOSx == true){eIZzyQrOSx = false;}
      if(DkCjihylYP == true){DkCjihylYP = false;}
      if(oMtzAFZgMr == true){oMtzAFZgMr = false;}
      if(CfVzlXIjny == true){CfVzlXIjny = false;}
      if(pwmLTiOJyH == true){pwmLTiOJyH = false;}
      if(pmUUPSOayr == true){pmUUPSOayr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ECJCRUFFIO
{ 
  void ZmaAmAcDNb()
  { 
      bool CmloSJeVkC = false;
      bool JjetcENByh = false;
      bool tWbdsWdiGl = false;
      bool nebXiVTsQD = false;
      bool dWlsofYsPe = false;
      bool CVOEOeKHww = false;
      bool fuPyOeHHLG = false;
      bool kUktEXjhoN = false;
      bool xjTaiRPWID = false;
      bool KLwUXhGmeK = false;
      bool XRhIshkTAq = false;
      bool tcSiyubnOx = false;
      bool OjyHuYXPWV = false;
      bool QxDeofCKgB = false;
      bool fwWRIhrNWc = false;
      bool FSXgunTZNU = false;
      bool KVxdaxYnsS = false;
      bool sQHNQSNfzM = false;
      bool gJstPyYViB = false;
      bool LbxMqKyrqK = false;
      string niCWHRpzYX;
      string xNytyqDDDb;
      string hzRXZbQYIR;
      string UDXUbRaoBm;
      string bEBFcHVIsW;
      string sfezjoQewe;
      string BQqHDsocRg;
      string QOCPzcxMuS;
      string GIfkYoXYjm;
      string AusVlLNtCi;
      string RrqMGecOzG;
      string qEjdXrkGhO;
      string UQsdgUUgdn;
      string PDKLAORSds;
      string LJYdwwLPyt;
      string aGLmOBzMel;
      string JwkLqmsYcI;
      string aRboCLrOgk;
      string IFhjMIrWwy;
      string PEnriPXMmJ;
      if(niCWHRpzYX == RrqMGecOzG){CmloSJeVkC = true;}
      else if(RrqMGecOzG == niCWHRpzYX){XRhIshkTAq = true;}
      if(xNytyqDDDb == qEjdXrkGhO){JjetcENByh = true;}
      else if(qEjdXrkGhO == xNytyqDDDb){tcSiyubnOx = true;}
      if(hzRXZbQYIR == UQsdgUUgdn){tWbdsWdiGl = true;}
      else if(UQsdgUUgdn == hzRXZbQYIR){OjyHuYXPWV = true;}
      if(UDXUbRaoBm == PDKLAORSds){nebXiVTsQD = true;}
      else if(PDKLAORSds == UDXUbRaoBm){QxDeofCKgB = true;}
      if(bEBFcHVIsW == LJYdwwLPyt){dWlsofYsPe = true;}
      else if(LJYdwwLPyt == bEBFcHVIsW){fwWRIhrNWc = true;}
      if(sfezjoQewe == aGLmOBzMel){CVOEOeKHww = true;}
      else if(aGLmOBzMel == sfezjoQewe){FSXgunTZNU = true;}
      if(BQqHDsocRg == JwkLqmsYcI){fuPyOeHHLG = true;}
      else if(JwkLqmsYcI == BQqHDsocRg){KVxdaxYnsS = true;}
      if(QOCPzcxMuS == aRboCLrOgk){kUktEXjhoN = true;}
      if(GIfkYoXYjm == IFhjMIrWwy){xjTaiRPWID = true;}
      if(AusVlLNtCi == PEnriPXMmJ){KLwUXhGmeK = true;}
      while(aRboCLrOgk == QOCPzcxMuS){sQHNQSNfzM = true;}
      while(IFhjMIrWwy == IFhjMIrWwy){gJstPyYViB = true;}
      while(PEnriPXMmJ == PEnriPXMmJ){LbxMqKyrqK = true;}
      if(CmloSJeVkC == true){CmloSJeVkC = false;}
      if(JjetcENByh == true){JjetcENByh = false;}
      if(tWbdsWdiGl == true){tWbdsWdiGl = false;}
      if(nebXiVTsQD == true){nebXiVTsQD = false;}
      if(dWlsofYsPe == true){dWlsofYsPe = false;}
      if(CVOEOeKHww == true){CVOEOeKHww = false;}
      if(fuPyOeHHLG == true){fuPyOeHHLG = false;}
      if(kUktEXjhoN == true){kUktEXjhoN = false;}
      if(xjTaiRPWID == true){xjTaiRPWID = false;}
      if(KLwUXhGmeK == true){KLwUXhGmeK = false;}
      if(XRhIshkTAq == true){XRhIshkTAq = false;}
      if(tcSiyubnOx == true){tcSiyubnOx = false;}
      if(OjyHuYXPWV == true){OjyHuYXPWV = false;}
      if(QxDeofCKgB == true){QxDeofCKgB = false;}
      if(fwWRIhrNWc == true){fwWRIhrNWc = false;}
      if(FSXgunTZNU == true){FSXgunTZNU = false;}
      if(KVxdaxYnsS == true){KVxdaxYnsS = false;}
      if(sQHNQSNfzM == true){sQHNQSNfzM = false;}
      if(gJstPyYViB == true){gJstPyYViB = false;}
      if(LbxMqKyrqK == true){LbxMqKyrqK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GOGERAMJMF
{ 
  void kqAVFQWpro()
  { 
      bool xoqYyimshJ = false;
      bool abjWOIzXpS = false;
      bool jMSVHVdawP = false;
      bool aKMdNdAjuA = false;
      bool rBuJXbfMSI = false;
      bool wkJbjjVURc = false;
      bool FLwRhPPGJk = false;
      bool IPboZhRIye = false;
      bool oRInTpBjsc = false;
      bool HfSSugEcbH = false;
      bool MZDgAfIUCB = false;
      bool SNWlmmDIyr = false;
      bool OeMfcbxIss = false;
      bool dogpSPOamn = false;
      bool gghqKtJffI = false;
      bool cudjrhMWEY = false;
      bool hAaIXcffTX = false;
      bool YbVKLhwVVh = false;
      bool SRckPhKxyj = false;
      bool CrWOFgFZTg = false;
      string RHeLTzENKL;
      string KYQiqODwiT;
      string mqNMyokasD;
      string nXEsGssfQi;
      string HoygrpLHcz;
      string dhyVXasSNe;
      string NdTHWlTXcx;
      string VXfAMxsgTH;
      string ccxtZGZiUf;
      string zZSlUdVpJG;
      string WnefdFBxIa;
      string gMzGBjfYhQ;
      string MkCwxuEseh;
      string bCWMkoyRQT;
      string EbZtymaMkk;
      string ywIstlkhhi;
      string BISaydplUL;
      string lOIOLjKIyK;
      string TrItjftcSz;
      string EPjhRwJzuT;
      if(RHeLTzENKL == WnefdFBxIa){xoqYyimshJ = true;}
      else if(WnefdFBxIa == RHeLTzENKL){MZDgAfIUCB = true;}
      if(KYQiqODwiT == gMzGBjfYhQ){abjWOIzXpS = true;}
      else if(gMzGBjfYhQ == KYQiqODwiT){SNWlmmDIyr = true;}
      if(mqNMyokasD == MkCwxuEseh){jMSVHVdawP = true;}
      else if(MkCwxuEseh == mqNMyokasD){OeMfcbxIss = true;}
      if(nXEsGssfQi == bCWMkoyRQT){aKMdNdAjuA = true;}
      else if(bCWMkoyRQT == nXEsGssfQi){dogpSPOamn = true;}
      if(HoygrpLHcz == EbZtymaMkk){rBuJXbfMSI = true;}
      else if(EbZtymaMkk == HoygrpLHcz){gghqKtJffI = true;}
      if(dhyVXasSNe == ywIstlkhhi){wkJbjjVURc = true;}
      else if(ywIstlkhhi == dhyVXasSNe){cudjrhMWEY = true;}
      if(NdTHWlTXcx == BISaydplUL){FLwRhPPGJk = true;}
      else if(BISaydplUL == NdTHWlTXcx){hAaIXcffTX = true;}
      if(VXfAMxsgTH == lOIOLjKIyK){IPboZhRIye = true;}
      if(ccxtZGZiUf == TrItjftcSz){oRInTpBjsc = true;}
      if(zZSlUdVpJG == EPjhRwJzuT){HfSSugEcbH = true;}
      while(lOIOLjKIyK == VXfAMxsgTH){YbVKLhwVVh = true;}
      while(TrItjftcSz == TrItjftcSz){SRckPhKxyj = true;}
      while(EPjhRwJzuT == EPjhRwJzuT){CrWOFgFZTg = true;}
      if(xoqYyimshJ == true){xoqYyimshJ = false;}
      if(abjWOIzXpS == true){abjWOIzXpS = false;}
      if(jMSVHVdawP == true){jMSVHVdawP = false;}
      if(aKMdNdAjuA == true){aKMdNdAjuA = false;}
      if(rBuJXbfMSI == true){rBuJXbfMSI = false;}
      if(wkJbjjVURc == true){wkJbjjVURc = false;}
      if(FLwRhPPGJk == true){FLwRhPPGJk = false;}
      if(IPboZhRIye == true){IPboZhRIye = false;}
      if(oRInTpBjsc == true){oRInTpBjsc = false;}
      if(HfSSugEcbH == true){HfSSugEcbH = false;}
      if(MZDgAfIUCB == true){MZDgAfIUCB = false;}
      if(SNWlmmDIyr == true){SNWlmmDIyr = false;}
      if(OeMfcbxIss == true){OeMfcbxIss = false;}
      if(dogpSPOamn == true){dogpSPOamn = false;}
      if(gghqKtJffI == true){gghqKtJffI = false;}
      if(cudjrhMWEY == true){cudjrhMWEY = false;}
      if(hAaIXcffTX == true){hAaIXcffTX = false;}
      if(YbVKLhwVVh == true){YbVKLhwVVh = false;}
      if(SRckPhKxyj == true){SRckPhKxyj = false;}
      if(CrWOFgFZTg == true){CrWOFgFZTg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XTYBBTGCAA
{ 
  void NKzokRPtZD()
  { 
      bool RTXBTWyzWw = false;
      bool AiSEpbYCQt = false;
      bool AThWqidZoT = false;
      bool cPEPTuwoeS = false;
      bool DRonpdSOqG = false;
      bool dWtuIylAJk = false;
      bool rXKDTjdCkt = false;
      bool ejXypidsgM = false;
      bool POiioFVJHU = false;
      bool IuetZfHlUF = false;
      bool zQdwatzuEZ = false;
      bool UsSxUdoaNN = false;
      bool OUtPkiFdYK = false;
      bool arXbMyklHt = false;
      bool GZEhAPchYw = false;
      bool pfXHpdVOKq = false;
      bool oUWtycUqjW = false;
      bool rCSSHoQLOU = false;
      bool GWEbTuTQkh = false;
      bool bVaQFkCJjX = false;
      string nckGgTdZiC;
      string QUZnokJthO;
      string tSwamjyimD;
      string iaqCESxlyI;
      string YlEDRzhbxt;
      string YGMHLVfKTx;
      string UtlfSpdXiW;
      string nWwZoHNrJn;
      string BWlrecNjpi;
      string lmRAmdzYka;
      string VKraGBKmRE;
      string HnAfuyItBp;
      string csgAjBFulK;
      string HoHiRqdKld;
      string SZRlaylkFn;
      string UFWtybdrpF;
      string uOAGwSfRNE;
      string UyHXXCatYl;
      string OTpyoCRMjp;
      string NlTghDZLpI;
      if(nckGgTdZiC == VKraGBKmRE){RTXBTWyzWw = true;}
      else if(VKraGBKmRE == nckGgTdZiC){zQdwatzuEZ = true;}
      if(QUZnokJthO == HnAfuyItBp){AiSEpbYCQt = true;}
      else if(HnAfuyItBp == QUZnokJthO){UsSxUdoaNN = true;}
      if(tSwamjyimD == csgAjBFulK){AThWqidZoT = true;}
      else if(csgAjBFulK == tSwamjyimD){OUtPkiFdYK = true;}
      if(iaqCESxlyI == HoHiRqdKld){cPEPTuwoeS = true;}
      else if(HoHiRqdKld == iaqCESxlyI){arXbMyklHt = true;}
      if(YlEDRzhbxt == SZRlaylkFn){DRonpdSOqG = true;}
      else if(SZRlaylkFn == YlEDRzhbxt){GZEhAPchYw = true;}
      if(YGMHLVfKTx == UFWtybdrpF){dWtuIylAJk = true;}
      else if(UFWtybdrpF == YGMHLVfKTx){pfXHpdVOKq = true;}
      if(UtlfSpdXiW == uOAGwSfRNE){rXKDTjdCkt = true;}
      else if(uOAGwSfRNE == UtlfSpdXiW){oUWtycUqjW = true;}
      if(nWwZoHNrJn == UyHXXCatYl){ejXypidsgM = true;}
      if(BWlrecNjpi == OTpyoCRMjp){POiioFVJHU = true;}
      if(lmRAmdzYka == NlTghDZLpI){IuetZfHlUF = true;}
      while(UyHXXCatYl == nWwZoHNrJn){rCSSHoQLOU = true;}
      while(OTpyoCRMjp == OTpyoCRMjp){GWEbTuTQkh = true;}
      while(NlTghDZLpI == NlTghDZLpI){bVaQFkCJjX = true;}
      if(RTXBTWyzWw == true){RTXBTWyzWw = false;}
      if(AiSEpbYCQt == true){AiSEpbYCQt = false;}
      if(AThWqidZoT == true){AThWqidZoT = false;}
      if(cPEPTuwoeS == true){cPEPTuwoeS = false;}
      if(DRonpdSOqG == true){DRonpdSOqG = false;}
      if(dWtuIylAJk == true){dWtuIylAJk = false;}
      if(rXKDTjdCkt == true){rXKDTjdCkt = false;}
      if(ejXypidsgM == true){ejXypidsgM = false;}
      if(POiioFVJHU == true){POiioFVJHU = false;}
      if(IuetZfHlUF == true){IuetZfHlUF = false;}
      if(zQdwatzuEZ == true){zQdwatzuEZ = false;}
      if(UsSxUdoaNN == true){UsSxUdoaNN = false;}
      if(OUtPkiFdYK == true){OUtPkiFdYK = false;}
      if(arXbMyklHt == true){arXbMyklHt = false;}
      if(GZEhAPchYw == true){GZEhAPchYw = false;}
      if(pfXHpdVOKq == true){pfXHpdVOKq = false;}
      if(oUWtycUqjW == true){oUWtycUqjW = false;}
      if(rCSSHoQLOU == true){rCSSHoQLOU = false;}
      if(GWEbTuTQkh == true){GWEbTuTQkh = false;}
      if(bVaQFkCJjX == true){bVaQFkCJjX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TMIWKBLIZB
{ 
  void fcgwOtIiNI()
  { 
      bool DBOJgzbCgB = false;
      bool wsdaalVlHT = false;
      bool DkcBCxBRyZ = false;
      bool pVEkNDUart = false;
      bool ncMXwWHZtB = false;
      bool yNyEVRYNGj = false;
      bool xJDHLZorMX = false;
      bool RutMeaXFEf = false;
      bool obWwabXAPu = false;
      bool eHTHxeYFLW = false;
      bool hOMWjCTlYu = false;
      bool sSIatVmGfj = false;
      bool CncQsKalPA = false;
      bool CSthxZOzMY = false;
      bool HkaUCLzsNa = false;
      bool qRYbTskwdZ = false;
      bool bhWXrZYZcU = false;
      bool HmtHbQMIOg = false;
      bool KhYnJjtRND = false;
      bool nSVmwZODbb = false;
      string exwNYeoxmc;
      string sjhDmkgnsV;
      string TTdRYSeJPM;
      string MeuWWDCNpa;
      string bkMMHxVraX;
      string jRSqyKTdoF;
      string zegZPNnLgi;
      string hSyRsiGRKa;
      string xmirbtMEYM;
      string jXYjbxDmws;
      string IJKqpRTAxP;
      string DBTNHLuoxU;
      string BimUzJtNow;
      string eTVQSnbrBK;
      string aLHJIiEKcQ;
      string COoaqYWpqf;
      string WGLBjifCuT;
      string iCmmtpbdLQ;
      string FjjYtPetYs;
      string QlAVnUAFYZ;
      if(exwNYeoxmc == IJKqpRTAxP){DBOJgzbCgB = true;}
      else if(IJKqpRTAxP == exwNYeoxmc){hOMWjCTlYu = true;}
      if(sjhDmkgnsV == DBTNHLuoxU){wsdaalVlHT = true;}
      else if(DBTNHLuoxU == sjhDmkgnsV){sSIatVmGfj = true;}
      if(TTdRYSeJPM == BimUzJtNow){DkcBCxBRyZ = true;}
      else if(BimUzJtNow == TTdRYSeJPM){CncQsKalPA = true;}
      if(MeuWWDCNpa == eTVQSnbrBK){pVEkNDUart = true;}
      else if(eTVQSnbrBK == MeuWWDCNpa){CSthxZOzMY = true;}
      if(bkMMHxVraX == aLHJIiEKcQ){ncMXwWHZtB = true;}
      else if(aLHJIiEKcQ == bkMMHxVraX){HkaUCLzsNa = true;}
      if(jRSqyKTdoF == COoaqYWpqf){yNyEVRYNGj = true;}
      else if(COoaqYWpqf == jRSqyKTdoF){qRYbTskwdZ = true;}
      if(zegZPNnLgi == WGLBjifCuT){xJDHLZorMX = true;}
      else if(WGLBjifCuT == zegZPNnLgi){bhWXrZYZcU = true;}
      if(hSyRsiGRKa == iCmmtpbdLQ){RutMeaXFEf = true;}
      if(xmirbtMEYM == FjjYtPetYs){obWwabXAPu = true;}
      if(jXYjbxDmws == QlAVnUAFYZ){eHTHxeYFLW = true;}
      while(iCmmtpbdLQ == hSyRsiGRKa){HmtHbQMIOg = true;}
      while(FjjYtPetYs == FjjYtPetYs){KhYnJjtRND = true;}
      while(QlAVnUAFYZ == QlAVnUAFYZ){nSVmwZODbb = true;}
      if(DBOJgzbCgB == true){DBOJgzbCgB = false;}
      if(wsdaalVlHT == true){wsdaalVlHT = false;}
      if(DkcBCxBRyZ == true){DkcBCxBRyZ = false;}
      if(pVEkNDUart == true){pVEkNDUart = false;}
      if(ncMXwWHZtB == true){ncMXwWHZtB = false;}
      if(yNyEVRYNGj == true){yNyEVRYNGj = false;}
      if(xJDHLZorMX == true){xJDHLZorMX = false;}
      if(RutMeaXFEf == true){RutMeaXFEf = false;}
      if(obWwabXAPu == true){obWwabXAPu = false;}
      if(eHTHxeYFLW == true){eHTHxeYFLW = false;}
      if(hOMWjCTlYu == true){hOMWjCTlYu = false;}
      if(sSIatVmGfj == true){sSIatVmGfj = false;}
      if(CncQsKalPA == true){CncQsKalPA = false;}
      if(CSthxZOzMY == true){CSthxZOzMY = false;}
      if(HkaUCLzsNa == true){HkaUCLzsNa = false;}
      if(qRYbTskwdZ == true){qRYbTskwdZ = false;}
      if(bhWXrZYZcU == true){bhWXrZYZcU = false;}
      if(HmtHbQMIOg == true){HmtHbQMIOg = false;}
      if(KhYnJjtRND == true){KhYnJjtRND = false;}
      if(nSVmwZODbb == true){nSVmwZODbb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XUDQGMHZXE
{ 
  void KlCwxzqAZn()
  { 
      bool pzHDESktCu = false;
      bool kaIJMeWnwz = false;
      bool OHnJtRoWxL = false;
      bool tenaHeyTBr = false;
      bool cqPdmBkcoP = false;
      bool uNneniLxJl = false;
      bool dOxpAFlgBh = false;
      bool gDlDVXqJWr = false;
      bool gLghQfpJmX = false;
      bool TBKPNOtYdg = false;
      bool PDbHiqbkIQ = false;
      bool rBaQFSgPZT = false;
      bool PctcNfsWoH = false;
      bool cSeocciZzY = false;
      bool EFAWfRZsJu = false;
      bool gezKRlJysC = false;
      bool yEuBmYWkmc = false;
      bool iHQAOJbWww = false;
      bool FzNtayTUXp = false;
      bool TkgwZzKzjH = false;
      string zlcKcXdjiN;
      string QKwDgIrCbc;
      string PmruPMgort;
      string QIsKqfYujy;
      string FSBVscngXR;
      string eKulhMsguQ;
      string qnrnxHRkMA;
      string iwRdWxlWCl;
      string XARaPFNHbe;
      string lqzTHQZMXk;
      string LCTWhhrQOk;
      string aWeJrqWQYq;
      string sJJhOqwyWG;
      string XYyQaVfurg;
      string MwsqDPMpaP;
      string tJmgqBslIq;
      string lttHMBYNiW;
      string LbXrdwQRdy;
      string dGWGLNlRZY;
      string csmBuSCkdC;
      if(zlcKcXdjiN == LCTWhhrQOk){pzHDESktCu = true;}
      else if(LCTWhhrQOk == zlcKcXdjiN){PDbHiqbkIQ = true;}
      if(QKwDgIrCbc == aWeJrqWQYq){kaIJMeWnwz = true;}
      else if(aWeJrqWQYq == QKwDgIrCbc){rBaQFSgPZT = true;}
      if(PmruPMgort == sJJhOqwyWG){OHnJtRoWxL = true;}
      else if(sJJhOqwyWG == PmruPMgort){PctcNfsWoH = true;}
      if(QIsKqfYujy == XYyQaVfurg){tenaHeyTBr = true;}
      else if(XYyQaVfurg == QIsKqfYujy){cSeocciZzY = true;}
      if(FSBVscngXR == MwsqDPMpaP){cqPdmBkcoP = true;}
      else if(MwsqDPMpaP == FSBVscngXR){EFAWfRZsJu = true;}
      if(eKulhMsguQ == tJmgqBslIq){uNneniLxJl = true;}
      else if(tJmgqBslIq == eKulhMsguQ){gezKRlJysC = true;}
      if(qnrnxHRkMA == lttHMBYNiW){dOxpAFlgBh = true;}
      else if(lttHMBYNiW == qnrnxHRkMA){yEuBmYWkmc = true;}
      if(iwRdWxlWCl == LbXrdwQRdy){gDlDVXqJWr = true;}
      if(XARaPFNHbe == dGWGLNlRZY){gLghQfpJmX = true;}
      if(lqzTHQZMXk == csmBuSCkdC){TBKPNOtYdg = true;}
      while(LbXrdwQRdy == iwRdWxlWCl){iHQAOJbWww = true;}
      while(dGWGLNlRZY == dGWGLNlRZY){FzNtayTUXp = true;}
      while(csmBuSCkdC == csmBuSCkdC){TkgwZzKzjH = true;}
      if(pzHDESktCu == true){pzHDESktCu = false;}
      if(kaIJMeWnwz == true){kaIJMeWnwz = false;}
      if(OHnJtRoWxL == true){OHnJtRoWxL = false;}
      if(tenaHeyTBr == true){tenaHeyTBr = false;}
      if(cqPdmBkcoP == true){cqPdmBkcoP = false;}
      if(uNneniLxJl == true){uNneniLxJl = false;}
      if(dOxpAFlgBh == true){dOxpAFlgBh = false;}
      if(gDlDVXqJWr == true){gDlDVXqJWr = false;}
      if(gLghQfpJmX == true){gLghQfpJmX = false;}
      if(TBKPNOtYdg == true){TBKPNOtYdg = false;}
      if(PDbHiqbkIQ == true){PDbHiqbkIQ = false;}
      if(rBaQFSgPZT == true){rBaQFSgPZT = false;}
      if(PctcNfsWoH == true){PctcNfsWoH = false;}
      if(cSeocciZzY == true){cSeocciZzY = false;}
      if(EFAWfRZsJu == true){EFAWfRZsJu = false;}
      if(gezKRlJysC == true){gezKRlJysC = false;}
      if(yEuBmYWkmc == true){yEuBmYWkmc = false;}
      if(iHQAOJbWww == true){iHQAOJbWww = false;}
      if(FzNtayTUXp == true){FzNtayTUXp = false;}
      if(TkgwZzKzjH == true){TkgwZzKzjH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MVPXXLFYWV
{ 
  void UlHxhkYhsH()
  { 
      bool nfbkYNocsk = false;
      bool IfPJOmIags = false;
      bool MUDOGBleRP = false;
      bool ArDceSCXdr = false;
      bool OPqpuMaBYP = false;
      bool wwrZoSbMeX = false;
      bool bKKdkQbleu = false;
      bool kjwnewcNTs = false;
      bool ZjFCSDzcnL = false;
      bool qorFQDFNEe = false;
      bool jnWddMAEus = false;
      bool pNskxqEIKg = false;
      bool RyySEwqqXa = false;
      bool qOInJlNbXF = false;
      bool DuhtVcuHHY = false;
      bool zwCXNkpEYh = false;
      bool UIfUBaEEbL = false;
      bool dbkFdVQDwa = false;
      bool AjiyatMkaX = false;
      bool uIDoktOMsu = false;
      string tCJMYswSXw;
      string kepRWsqgJa;
      string IUqagssfcV;
      string SMjabKJYJt;
      string MSpjHzGYBF;
      string JiNSzZLief;
      string zPpCcYuOoL;
      string iSWPNodGSh;
      string lUdWLjzQaC;
      string zZscuwcnHh;
      string DqipVqLyEK;
      string uFPxsdlTps;
      string YdnmMJZsTR;
      string MpzjdulnAU;
      string XBMQHsKujQ;
      string KIxOJZDucM;
      string RSdmxEFeSy;
      string qxSUUXQWfS;
      string ydJDGErkaE;
      string rpLmDFXYTC;
      if(tCJMYswSXw == DqipVqLyEK){nfbkYNocsk = true;}
      else if(DqipVqLyEK == tCJMYswSXw){jnWddMAEus = true;}
      if(kepRWsqgJa == uFPxsdlTps){IfPJOmIags = true;}
      else if(uFPxsdlTps == kepRWsqgJa){pNskxqEIKg = true;}
      if(IUqagssfcV == YdnmMJZsTR){MUDOGBleRP = true;}
      else if(YdnmMJZsTR == IUqagssfcV){RyySEwqqXa = true;}
      if(SMjabKJYJt == MpzjdulnAU){ArDceSCXdr = true;}
      else if(MpzjdulnAU == SMjabKJYJt){qOInJlNbXF = true;}
      if(MSpjHzGYBF == XBMQHsKujQ){OPqpuMaBYP = true;}
      else if(XBMQHsKujQ == MSpjHzGYBF){DuhtVcuHHY = true;}
      if(JiNSzZLief == KIxOJZDucM){wwrZoSbMeX = true;}
      else if(KIxOJZDucM == JiNSzZLief){zwCXNkpEYh = true;}
      if(zPpCcYuOoL == RSdmxEFeSy){bKKdkQbleu = true;}
      else if(RSdmxEFeSy == zPpCcYuOoL){UIfUBaEEbL = true;}
      if(iSWPNodGSh == qxSUUXQWfS){kjwnewcNTs = true;}
      if(lUdWLjzQaC == ydJDGErkaE){ZjFCSDzcnL = true;}
      if(zZscuwcnHh == rpLmDFXYTC){qorFQDFNEe = true;}
      while(qxSUUXQWfS == iSWPNodGSh){dbkFdVQDwa = true;}
      while(ydJDGErkaE == ydJDGErkaE){AjiyatMkaX = true;}
      while(rpLmDFXYTC == rpLmDFXYTC){uIDoktOMsu = true;}
      if(nfbkYNocsk == true){nfbkYNocsk = false;}
      if(IfPJOmIags == true){IfPJOmIags = false;}
      if(MUDOGBleRP == true){MUDOGBleRP = false;}
      if(ArDceSCXdr == true){ArDceSCXdr = false;}
      if(OPqpuMaBYP == true){OPqpuMaBYP = false;}
      if(wwrZoSbMeX == true){wwrZoSbMeX = false;}
      if(bKKdkQbleu == true){bKKdkQbleu = false;}
      if(kjwnewcNTs == true){kjwnewcNTs = false;}
      if(ZjFCSDzcnL == true){ZjFCSDzcnL = false;}
      if(qorFQDFNEe == true){qorFQDFNEe = false;}
      if(jnWddMAEus == true){jnWddMAEus = false;}
      if(pNskxqEIKg == true){pNskxqEIKg = false;}
      if(RyySEwqqXa == true){RyySEwqqXa = false;}
      if(qOInJlNbXF == true){qOInJlNbXF = false;}
      if(DuhtVcuHHY == true){DuhtVcuHHY = false;}
      if(zwCXNkpEYh == true){zwCXNkpEYh = false;}
      if(UIfUBaEEbL == true){UIfUBaEEbL = false;}
      if(dbkFdVQDwa == true){dbkFdVQDwa = false;}
      if(AjiyatMkaX == true){AjiyatMkaX = false;}
      if(uIDoktOMsu == true){uIDoktOMsu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KADMFMJWZW
{ 
  void KyAWgzrabc()
  { 
      bool zBRtzBBrfa = false;
      bool qAMKityUXh = false;
      bool cpfSqNgsAc = false;
      bool JETmwxPDjf = false;
      bool SZiSpkceKp = false;
      bool cIjNSIUyCl = false;
      bool UHqCRmfYOl = false;
      bool dtkqPDHMcF = false;
      bool jBiKAAUFTm = false;
      bool bQAxLKhfBC = false;
      bool EEQXLhWsyP = false;
      bool BIVxCSYgCQ = false;
      bool SaEaKMsmeE = false;
      bool UaKZAfkKyR = false;
      bool cbGDlSuDur = false;
      bool lBckjdzoNy = false;
      bool ojNtuZxuxV = false;
      bool hNhkmqTAoq = false;
      bool RpqlSSxZpV = false;
      bool guxzcsNMIL = false;
      string ssFpMfqaJs;
      string ApQweWJwUR;
      string SifcpuiTbW;
      string eBonpVlEVo;
      string QDNXjcJbPr;
      string hqYObKMbzR;
      string wXzlOzAcFJ;
      string jFZfAOVIsN;
      string kHDionbaMf;
      string IKEErsEaJk;
      string cgVGHcQsNM;
      string oEhlgoTPxZ;
      string WYPZAZAUmH;
      string JtyIkDlwbM;
      string WiNzpEbSWD;
      string YociNDQwGh;
      string bwFFCtFZAc;
      string DWmkDmLQiu;
      string yhxjhUROth;
      string lopsjadHww;
      if(ssFpMfqaJs == cgVGHcQsNM){zBRtzBBrfa = true;}
      else if(cgVGHcQsNM == ssFpMfqaJs){EEQXLhWsyP = true;}
      if(ApQweWJwUR == oEhlgoTPxZ){qAMKityUXh = true;}
      else if(oEhlgoTPxZ == ApQweWJwUR){BIVxCSYgCQ = true;}
      if(SifcpuiTbW == WYPZAZAUmH){cpfSqNgsAc = true;}
      else if(WYPZAZAUmH == SifcpuiTbW){SaEaKMsmeE = true;}
      if(eBonpVlEVo == JtyIkDlwbM){JETmwxPDjf = true;}
      else if(JtyIkDlwbM == eBonpVlEVo){UaKZAfkKyR = true;}
      if(QDNXjcJbPr == WiNzpEbSWD){SZiSpkceKp = true;}
      else if(WiNzpEbSWD == QDNXjcJbPr){cbGDlSuDur = true;}
      if(hqYObKMbzR == YociNDQwGh){cIjNSIUyCl = true;}
      else if(YociNDQwGh == hqYObKMbzR){lBckjdzoNy = true;}
      if(wXzlOzAcFJ == bwFFCtFZAc){UHqCRmfYOl = true;}
      else if(bwFFCtFZAc == wXzlOzAcFJ){ojNtuZxuxV = true;}
      if(jFZfAOVIsN == DWmkDmLQiu){dtkqPDHMcF = true;}
      if(kHDionbaMf == yhxjhUROth){jBiKAAUFTm = true;}
      if(IKEErsEaJk == lopsjadHww){bQAxLKhfBC = true;}
      while(DWmkDmLQiu == jFZfAOVIsN){hNhkmqTAoq = true;}
      while(yhxjhUROth == yhxjhUROth){RpqlSSxZpV = true;}
      while(lopsjadHww == lopsjadHww){guxzcsNMIL = true;}
      if(zBRtzBBrfa == true){zBRtzBBrfa = false;}
      if(qAMKityUXh == true){qAMKityUXh = false;}
      if(cpfSqNgsAc == true){cpfSqNgsAc = false;}
      if(JETmwxPDjf == true){JETmwxPDjf = false;}
      if(SZiSpkceKp == true){SZiSpkceKp = false;}
      if(cIjNSIUyCl == true){cIjNSIUyCl = false;}
      if(UHqCRmfYOl == true){UHqCRmfYOl = false;}
      if(dtkqPDHMcF == true){dtkqPDHMcF = false;}
      if(jBiKAAUFTm == true){jBiKAAUFTm = false;}
      if(bQAxLKhfBC == true){bQAxLKhfBC = false;}
      if(EEQXLhWsyP == true){EEQXLhWsyP = false;}
      if(BIVxCSYgCQ == true){BIVxCSYgCQ = false;}
      if(SaEaKMsmeE == true){SaEaKMsmeE = false;}
      if(UaKZAfkKyR == true){UaKZAfkKyR = false;}
      if(cbGDlSuDur == true){cbGDlSuDur = false;}
      if(lBckjdzoNy == true){lBckjdzoNy = false;}
      if(ojNtuZxuxV == true){ojNtuZxuxV = false;}
      if(hNhkmqTAoq == true){hNhkmqTAoq = false;}
      if(RpqlSSxZpV == true){RpqlSSxZpV = false;}
      if(guxzcsNMIL == true){guxzcsNMIL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FNKMASFFQV
{ 
  void hfLcRliGRa()
  { 
      bool HycdLnZFVH = false;
      bool xPObwHAuVQ = false;
      bool jbTxpSrPyd = false;
      bool ULatptWDzq = false;
      bool FWBKHgEqJs = false;
      bool LfERPeefns = false;
      bool wKGrmlnTkC = false;
      bool kwudKMaJoI = false;
      bool NBGFRoGIdL = false;
      bool PpPGtuQIWV = false;
      bool rkFHIOjZGD = false;
      bool DUqeetEBay = false;
      bool efoZltgnjP = false;
      bool uRlSQcwywC = false;
      bool EfBaHtyjbA = false;
      bool qPhYpMueUN = false;
      bool hupqHliXOC = false;
      bool yFEXszdOSq = false;
      bool wwMiYfiMbD = false;
      bool hQdiTIoKTU = false;
      string FzWbmmSqpq;
      string TuTNtWypyO;
      string wOlNBsbrGk;
      string epZYxBBwSY;
      string eBSHKRIgWo;
      string oEpRTpMJZs;
      string KZkFLdVtPr;
      string VBXYjtueCj;
      string kuVQwazIEH;
      string nqVYOEQNwg;
      string wORdTmgRgZ;
      string thHpIPETIj;
      string dMoHEdfyKf;
      string chiUnVcrxI;
      string thaeMGjfQy;
      string AxFLDiZJZp;
      string HhHBwMzlCl;
      string lLWzpukJtx;
      string sAhLffcWRF;
      string wTSGBLaZiA;
      if(FzWbmmSqpq == wORdTmgRgZ){HycdLnZFVH = true;}
      else if(wORdTmgRgZ == FzWbmmSqpq){rkFHIOjZGD = true;}
      if(TuTNtWypyO == thHpIPETIj){xPObwHAuVQ = true;}
      else if(thHpIPETIj == TuTNtWypyO){DUqeetEBay = true;}
      if(wOlNBsbrGk == dMoHEdfyKf){jbTxpSrPyd = true;}
      else if(dMoHEdfyKf == wOlNBsbrGk){efoZltgnjP = true;}
      if(epZYxBBwSY == chiUnVcrxI){ULatptWDzq = true;}
      else if(chiUnVcrxI == epZYxBBwSY){uRlSQcwywC = true;}
      if(eBSHKRIgWo == thaeMGjfQy){FWBKHgEqJs = true;}
      else if(thaeMGjfQy == eBSHKRIgWo){EfBaHtyjbA = true;}
      if(oEpRTpMJZs == AxFLDiZJZp){LfERPeefns = true;}
      else if(AxFLDiZJZp == oEpRTpMJZs){qPhYpMueUN = true;}
      if(KZkFLdVtPr == HhHBwMzlCl){wKGrmlnTkC = true;}
      else if(HhHBwMzlCl == KZkFLdVtPr){hupqHliXOC = true;}
      if(VBXYjtueCj == lLWzpukJtx){kwudKMaJoI = true;}
      if(kuVQwazIEH == sAhLffcWRF){NBGFRoGIdL = true;}
      if(nqVYOEQNwg == wTSGBLaZiA){PpPGtuQIWV = true;}
      while(lLWzpukJtx == VBXYjtueCj){yFEXszdOSq = true;}
      while(sAhLffcWRF == sAhLffcWRF){wwMiYfiMbD = true;}
      while(wTSGBLaZiA == wTSGBLaZiA){hQdiTIoKTU = true;}
      if(HycdLnZFVH == true){HycdLnZFVH = false;}
      if(xPObwHAuVQ == true){xPObwHAuVQ = false;}
      if(jbTxpSrPyd == true){jbTxpSrPyd = false;}
      if(ULatptWDzq == true){ULatptWDzq = false;}
      if(FWBKHgEqJs == true){FWBKHgEqJs = false;}
      if(LfERPeefns == true){LfERPeefns = false;}
      if(wKGrmlnTkC == true){wKGrmlnTkC = false;}
      if(kwudKMaJoI == true){kwudKMaJoI = false;}
      if(NBGFRoGIdL == true){NBGFRoGIdL = false;}
      if(PpPGtuQIWV == true){PpPGtuQIWV = false;}
      if(rkFHIOjZGD == true){rkFHIOjZGD = false;}
      if(DUqeetEBay == true){DUqeetEBay = false;}
      if(efoZltgnjP == true){efoZltgnjP = false;}
      if(uRlSQcwywC == true){uRlSQcwywC = false;}
      if(EfBaHtyjbA == true){EfBaHtyjbA = false;}
      if(qPhYpMueUN == true){qPhYpMueUN = false;}
      if(hupqHliXOC == true){hupqHliXOC = false;}
      if(yFEXszdOSq == true){yFEXszdOSq = false;}
      if(wwMiYfiMbD == true){wwMiYfiMbD = false;}
      if(hQdiTIoKTU == true){hQdiTIoKTU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DKZBQFAQTO
{ 
  void GDbQZLIUrP()
  { 
      bool udkiGzqnKU = false;
      bool rmLwZiEFOD = false;
      bool uDOkVmegui = false;
      bool CskSqSaqKF = false;
      bool jkpfDeOcMm = false;
      bool mLEKyrPAMS = false;
      bool TJraRyCsFH = false;
      bool HNtJSJMhhp = false;
      bool XCUIwqnZTy = false;
      bool CadrlasPOE = false;
      bool bVXFeYQuqo = false;
      bool fhRWuRojda = false;
      bool JbYGEgjCWr = false;
      bool QwTdOBdOcX = false;
      bool asieSUIHwU = false;
      bool kIlmtAxQAy = false;
      bool nOXyXjNnHs = false;
      bool mZHFzQssnj = false;
      bool XcFCGHJfiO = false;
      bool ENNdiLUjGi = false;
      string NRaVLOXiZi;
      string VoTmhlWLQp;
      string XnDhfdzdfy;
      string lUWLrEsqyx;
      string NsQgwYpxyH;
      string GnaGxYNrph;
      string PtCawBRIuc;
      string sfNScdWWlH;
      string nBeXqytQNS;
      string pBAQhTppju;
      string GhBVOZaHcT;
      string CqGhtNOdiy;
      string GBtclqewkJ;
      string ngmpBFzJJR;
      string WmmtPztSWT;
      string ELGlnFmYiW;
      string ueVTfVEPgn;
      string NFURbTNzMl;
      string wMZQEbZABu;
      string SaZmVrQTOt;
      if(NRaVLOXiZi == GhBVOZaHcT){udkiGzqnKU = true;}
      else if(GhBVOZaHcT == NRaVLOXiZi){bVXFeYQuqo = true;}
      if(VoTmhlWLQp == CqGhtNOdiy){rmLwZiEFOD = true;}
      else if(CqGhtNOdiy == VoTmhlWLQp){fhRWuRojda = true;}
      if(XnDhfdzdfy == GBtclqewkJ){uDOkVmegui = true;}
      else if(GBtclqewkJ == XnDhfdzdfy){JbYGEgjCWr = true;}
      if(lUWLrEsqyx == ngmpBFzJJR){CskSqSaqKF = true;}
      else if(ngmpBFzJJR == lUWLrEsqyx){QwTdOBdOcX = true;}
      if(NsQgwYpxyH == WmmtPztSWT){jkpfDeOcMm = true;}
      else if(WmmtPztSWT == NsQgwYpxyH){asieSUIHwU = true;}
      if(GnaGxYNrph == ELGlnFmYiW){mLEKyrPAMS = true;}
      else if(ELGlnFmYiW == GnaGxYNrph){kIlmtAxQAy = true;}
      if(PtCawBRIuc == ueVTfVEPgn){TJraRyCsFH = true;}
      else if(ueVTfVEPgn == PtCawBRIuc){nOXyXjNnHs = true;}
      if(sfNScdWWlH == NFURbTNzMl){HNtJSJMhhp = true;}
      if(nBeXqytQNS == wMZQEbZABu){XCUIwqnZTy = true;}
      if(pBAQhTppju == SaZmVrQTOt){CadrlasPOE = true;}
      while(NFURbTNzMl == sfNScdWWlH){mZHFzQssnj = true;}
      while(wMZQEbZABu == wMZQEbZABu){XcFCGHJfiO = true;}
      while(SaZmVrQTOt == SaZmVrQTOt){ENNdiLUjGi = true;}
      if(udkiGzqnKU == true){udkiGzqnKU = false;}
      if(rmLwZiEFOD == true){rmLwZiEFOD = false;}
      if(uDOkVmegui == true){uDOkVmegui = false;}
      if(CskSqSaqKF == true){CskSqSaqKF = false;}
      if(jkpfDeOcMm == true){jkpfDeOcMm = false;}
      if(mLEKyrPAMS == true){mLEKyrPAMS = false;}
      if(TJraRyCsFH == true){TJraRyCsFH = false;}
      if(HNtJSJMhhp == true){HNtJSJMhhp = false;}
      if(XCUIwqnZTy == true){XCUIwqnZTy = false;}
      if(CadrlasPOE == true){CadrlasPOE = false;}
      if(bVXFeYQuqo == true){bVXFeYQuqo = false;}
      if(fhRWuRojda == true){fhRWuRojda = false;}
      if(JbYGEgjCWr == true){JbYGEgjCWr = false;}
      if(QwTdOBdOcX == true){QwTdOBdOcX = false;}
      if(asieSUIHwU == true){asieSUIHwU = false;}
      if(kIlmtAxQAy == true){kIlmtAxQAy = false;}
      if(nOXyXjNnHs == true){nOXyXjNnHs = false;}
      if(mZHFzQssnj == true){mZHFzQssnj = false;}
      if(XcFCGHJfiO == true){XcFCGHJfiO = false;}
      if(ENNdiLUjGi == true){ENNdiLUjGi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IBQZRNEHWX
{ 
  void esQlVqStOp()
  { 
      bool zfFkMVZppD = false;
      bool dsPknHTlpt = false;
      bool JjIiuMufFa = false;
      bool qmrbsfyZEw = false;
      bool fSSIsbHEHs = false;
      bool uuuIrPWVpA = false;
      bool ZskOMqBnrI = false;
      bool ItgsNqQzoS = false;
      bool EqYLfurjid = false;
      bool IciEVmhEwC = false;
      bool ZTLykBOBtB = false;
      bool yWfWuiTYiR = false;
      bool zRENzfKbWZ = false;
      bool JMDmrkeZae = false;
      bool fpohflwMJm = false;
      bool TIUeDIOyzE = false;
      bool pldUqkTseJ = false;
      bool DsyEkIcVhN = false;
      bool iySjGBrXjj = false;
      bool WgaVnsLTqt = false;
      string juKeGKQXjn;
      string woIZsSelbs;
      string mrzZEkwXrb;
      string RiwBiauUxN;
      string GFXozLqjkj;
      string mffUpqujaU;
      string OsfIWMrHpS;
      string XKoNmhUJas;
      string tLmHokDaKq;
      string eKtbzNZPSl;
      string SjsRMbqRhI;
      string WkJgaCFXSk;
      string JQwzmMQMOZ;
      string IEqnZJRUuM;
      string tksCUtBMBx;
      string HBwgbBntez;
      string LeDIARtUHQ;
      string jkbGqYXtds;
      string LDKRSGIJMX;
      string VXouBPhkCC;
      if(juKeGKQXjn == SjsRMbqRhI){zfFkMVZppD = true;}
      else if(SjsRMbqRhI == juKeGKQXjn){ZTLykBOBtB = true;}
      if(woIZsSelbs == WkJgaCFXSk){dsPknHTlpt = true;}
      else if(WkJgaCFXSk == woIZsSelbs){yWfWuiTYiR = true;}
      if(mrzZEkwXrb == JQwzmMQMOZ){JjIiuMufFa = true;}
      else if(JQwzmMQMOZ == mrzZEkwXrb){zRENzfKbWZ = true;}
      if(RiwBiauUxN == IEqnZJRUuM){qmrbsfyZEw = true;}
      else if(IEqnZJRUuM == RiwBiauUxN){JMDmrkeZae = true;}
      if(GFXozLqjkj == tksCUtBMBx){fSSIsbHEHs = true;}
      else if(tksCUtBMBx == GFXozLqjkj){fpohflwMJm = true;}
      if(mffUpqujaU == HBwgbBntez){uuuIrPWVpA = true;}
      else if(HBwgbBntez == mffUpqujaU){TIUeDIOyzE = true;}
      if(OsfIWMrHpS == LeDIARtUHQ){ZskOMqBnrI = true;}
      else if(LeDIARtUHQ == OsfIWMrHpS){pldUqkTseJ = true;}
      if(XKoNmhUJas == jkbGqYXtds){ItgsNqQzoS = true;}
      if(tLmHokDaKq == LDKRSGIJMX){EqYLfurjid = true;}
      if(eKtbzNZPSl == VXouBPhkCC){IciEVmhEwC = true;}
      while(jkbGqYXtds == XKoNmhUJas){DsyEkIcVhN = true;}
      while(LDKRSGIJMX == LDKRSGIJMX){iySjGBrXjj = true;}
      while(VXouBPhkCC == VXouBPhkCC){WgaVnsLTqt = true;}
      if(zfFkMVZppD == true){zfFkMVZppD = false;}
      if(dsPknHTlpt == true){dsPknHTlpt = false;}
      if(JjIiuMufFa == true){JjIiuMufFa = false;}
      if(qmrbsfyZEw == true){qmrbsfyZEw = false;}
      if(fSSIsbHEHs == true){fSSIsbHEHs = false;}
      if(uuuIrPWVpA == true){uuuIrPWVpA = false;}
      if(ZskOMqBnrI == true){ZskOMqBnrI = false;}
      if(ItgsNqQzoS == true){ItgsNqQzoS = false;}
      if(EqYLfurjid == true){EqYLfurjid = false;}
      if(IciEVmhEwC == true){IciEVmhEwC = false;}
      if(ZTLykBOBtB == true){ZTLykBOBtB = false;}
      if(yWfWuiTYiR == true){yWfWuiTYiR = false;}
      if(zRENzfKbWZ == true){zRENzfKbWZ = false;}
      if(JMDmrkeZae == true){JMDmrkeZae = false;}
      if(fpohflwMJm == true){fpohflwMJm = false;}
      if(TIUeDIOyzE == true){TIUeDIOyzE = false;}
      if(pldUqkTseJ == true){pldUqkTseJ = false;}
      if(DsyEkIcVhN == true){DsyEkIcVhN = false;}
      if(iySjGBrXjj == true){iySjGBrXjj = false;}
      if(WgaVnsLTqt == true){WgaVnsLTqt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXMGPFFWHC
{ 
  void NTUZjibzow()
  { 
      bool IihwuKcBwZ = false;
      bool IlTYfqNLZC = false;
      bool dLTMytgpcL = false;
      bool bByCGBRQJS = false;
      bool bafZOuzRam = false;
      bool PLNWjxPUxA = false;
      bool cmYkyGmRSe = false;
      bool YxBGaDesyC = false;
      bool uPOouPnaRI = false;
      bool lwSIooBtbH = false;
      bool HhzwNSKGwg = false;
      bool SVVtFNXioi = false;
      bool SMzJsbdsQl = false;
      bool BjRquNQSac = false;
      bool EhekpPaXDb = false;
      bool QSFsouhoDk = false;
      bool oRoKehEezq = false;
      bool xFHMdkhNTd = false;
      bool BFooUieXCz = false;
      bool faOommrTFI = false;
      string ogpzpIdVhn;
      string GCVmDNDaWX;
      string dVlJDHJrUZ;
      string ZwTqircQkc;
      string YzurWJwdLp;
      string uGaOTTtfwi;
      string zkBINJieDK;
      string klpszeZsms;
      string KegdeTVEXP;
      string ywUBdmymeN;
      string aRZBFIPgOo;
      string sBsCYTEWds;
      string ndGnMnRoPM;
      string glNYSrFfYV;
      string EoohVwDRbJ;
      string iaJkYwKloQ;
      string qaQCIGmTjf;
      string NXxHoznYRP;
      string kzMFcFcbAW;
      string hSqHedXmZO;
      if(ogpzpIdVhn == aRZBFIPgOo){IihwuKcBwZ = true;}
      else if(aRZBFIPgOo == ogpzpIdVhn){HhzwNSKGwg = true;}
      if(GCVmDNDaWX == sBsCYTEWds){IlTYfqNLZC = true;}
      else if(sBsCYTEWds == GCVmDNDaWX){SVVtFNXioi = true;}
      if(dVlJDHJrUZ == ndGnMnRoPM){dLTMytgpcL = true;}
      else if(ndGnMnRoPM == dVlJDHJrUZ){SMzJsbdsQl = true;}
      if(ZwTqircQkc == glNYSrFfYV){bByCGBRQJS = true;}
      else if(glNYSrFfYV == ZwTqircQkc){BjRquNQSac = true;}
      if(YzurWJwdLp == EoohVwDRbJ){bafZOuzRam = true;}
      else if(EoohVwDRbJ == YzurWJwdLp){EhekpPaXDb = true;}
      if(uGaOTTtfwi == iaJkYwKloQ){PLNWjxPUxA = true;}
      else if(iaJkYwKloQ == uGaOTTtfwi){QSFsouhoDk = true;}
      if(zkBINJieDK == qaQCIGmTjf){cmYkyGmRSe = true;}
      else if(qaQCIGmTjf == zkBINJieDK){oRoKehEezq = true;}
      if(klpszeZsms == NXxHoznYRP){YxBGaDesyC = true;}
      if(KegdeTVEXP == kzMFcFcbAW){uPOouPnaRI = true;}
      if(ywUBdmymeN == hSqHedXmZO){lwSIooBtbH = true;}
      while(NXxHoznYRP == klpszeZsms){xFHMdkhNTd = true;}
      while(kzMFcFcbAW == kzMFcFcbAW){BFooUieXCz = true;}
      while(hSqHedXmZO == hSqHedXmZO){faOommrTFI = true;}
      if(IihwuKcBwZ == true){IihwuKcBwZ = false;}
      if(IlTYfqNLZC == true){IlTYfqNLZC = false;}
      if(dLTMytgpcL == true){dLTMytgpcL = false;}
      if(bByCGBRQJS == true){bByCGBRQJS = false;}
      if(bafZOuzRam == true){bafZOuzRam = false;}
      if(PLNWjxPUxA == true){PLNWjxPUxA = false;}
      if(cmYkyGmRSe == true){cmYkyGmRSe = false;}
      if(YxBGaDesyC == true){YxBGaDesyC = false;}
      if(uPOouPnaRI == true){uPOouPnaRI = false;}
      if(lwSIooBtbH == true){lwSIooBtbH = false;}
      if(HhzwNSKGwg == true){HhzwNSKGwg = false;}
      if(SVVtFNXioi == true){SVVtFNXioi = false;}
      if(SMzJsbdsQl == true){SMzJsbdsQl = false;}
      if(BjRquNQSac == true){BjRquNQSac = false;}
      if(EhekpPaXDb == true){EhekpPaXDb = false;}
      if(QSFsouhoDk == true){QSFsouhoDk = false;}
      if(oRoKehEezq == true){oRoKehEezq = false;}
      if(xFHMdkhNTd == true){xFHMdkhNTd = false;}
      if(BFooUieXCz == true){BFooUieXCz = false;}
      if(faOommrTFI == true){faOommrTFI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SKFPFUWZTY
{ 
  void cxGUMmebQz()
  { 
      bool DeoyibzYIT = false;
      bool LLmpQOLGeD = false;
      bool eAaHVdVHyY = false;
      bool fjCVtaICoz = false;
      bool PhjyJVZICp = false;
      bool PaeCjCDhbE = false;
      bool GrajnaJRwp = false;
      bool GIRfnwQbxA = false;
      bool DNEHIEFzlq = false;
      bool WZajsWHzKh = false;
      bool MILLjGJzOm = false;
      bool lajbArmSai = false;
      bool VKeFTfhglQ = false;
      bool nQROnuBrXC = false;
      bool uGkyFupyiA = false;
      bool ioXaMBcGrD = false;
      bool XbMxyUJUnF = false;
      bool puuYnOYfzX = false;
      bool pjxkgzrpCl = false;
      bool RuATeSsmzj = false;
      string JqVbqpVEbh;
      string jMrofMPniI;
      string lBsXYcPrsL;
      string mVDafqPbYe;
      string gDQsTbVTWz;
      string QggGqHxxCO;
      string ZcLQuNIRJn;
      string xnODbhkAEw;
      string GwVstGowiX;
      string tRYKEDrzxF;
      string TDJhCbRceI;
      string WwsGHdHRWn;
      string YMiltePEyX;
      string pkCzcClmqR;
      string nLRZAxYSDa;
      string wZcJgGUXnW;
      string MMdGSltscE;
      string rUaEAMuIkx;
      string FxBXbPHsSV;
      string hNzTFagKGO;
      if(JqVbqpVEbh == TDJhCbRceI){DeoyibzYIT = true;}
      else if(TDJhCbRceI == JqVbqpVEbh){MILLjGJzOm = true;}
      if(jMrofMPniI == WwsGHdHRWn){LLmpQOLGeD = true;}
      else if(WwsGHdHRWn == jMrofMPniI){lajbArmSai = true;}
      if(lBsXYcPrsL == YMiltePEyX){eAaHVdVHyY = true;}
      else if(YMiltePEyX == lBsXYcPrsL){VKeFTfhglQ = true;}
      if(mVDafqPbYe == pkCzcClmqR){fjCVtaICoz = true;}
      else if(pkCzcClmqR == mVDafqPbYe){nQROnuBrXC = true;}
      if(gDQsTbVTWz == nLRZAxYSDa){PhjyJVZICp = true;}
      else if(nLRZAxYSDa == gDQsTbVTWz){uGkyFupyiA = true;}
      if(QggGqHxxCO == wZcJgGUXnW){PaeCjCDhbE = true;}
      else if(wZcJgGUXnW == QggGqHxxCO){ioXaMBcGrD = true;}
      if(ZcLQuNIRJn == MMdGSltscE){GrajnaJRwp = true;}
      else if(MMdGSltscE == ZcLQuNIRJn){XbMxyUJUnF = true;}
      if(xnODbhkAEw == rUaEAMuIkx){GIRfnwQbxA = true;}
      if(GwVstGowiX == FxBXbPHsSV){DNEHIEFzlq = true;}
      if(tRYKEDrzxF == hNzTFagKGO){WZajsWHzKh = true;}
      while(rUaEAMuIkx == xnODbhkAEw){puuYnOYfzX = true;}
      while(FxBXbPHsSV == FxBXbPHsSV){pjxkgzrpCl = true;}
      while(hNzTFagKGO == hNzTFagKGO){RuATeSsmzj = true;}
      if(DeoyibzYIT == true){DeoyibzYIT = false;}
      if(LLmpQOLGeD == true){LLmpQOLGeD = false;}
      if(eAaHVdVHyY == true){eAaHVdVHyY = false;}
      if(fjCVtaICoz == true){fjCVtaICoz = false;}
      if(PhjyJVZICp == true){PhjyJVZICp = false;}
      if(PaeCjCDhbE == true){PaeCjCDhbE = false;}
      if(GrajnaJRwp == true){GrajnaJRwp = false;}
      if(GIRfnwQbxA == true){GIRfnwQbxA = false;}
      if(DNEHIEFzlq == true){DNEHIEFzlq = false;}
      if(WZajsWHzKh == true){WZajsWHzKh = false;}
      if(MILLjGJzOm == true){MILLjGJzOm = false;}
      if(lajbArmSai == true){lajbArmSai = false;}
      if(VKeFTfhglQ == true){VKeFTfhglQ = false;}
      if(nQROnuBrXC == true){nQROnuBrXC = false;}
      if(uGkyFupyiA == true){uGkyFupyiA = false;}
      if(ioXaMBcGrD == true){ioXaMBcGrD = false;}
      if(XbMxyUJUnF == true){XbMxyUJUnF = false;}
      if(puuYnOYfzX == true){puuYnOYfzX = false;}
      if(pjxkgzrpCl == true){pjxkgzrpCl = false;}
      if(RuATeSsmzj == true){RuATeSsmzj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CIGZSKVEXI
{ 
  void hiDVACPNfx()
  { 
      bool cFhDfELJdk = false;
      bool qiYJrpxVeC = false;
      bool KRccCxgKib = false;
      bool QTrFCZozZl = false;
      bool sZqKQWjjqo = false;
      bool NAVMlKcFAh = false;
      bool WBaCUWqSHS = false;
      bool AxwrIkZRLf = false;
      bool NxStNQyeTq = false;
      bool xjzqPrznpt = false;
      bool eQcYoQDdDB = false;
      bool jKsTUYignE = false;
      bool YLzPUPxEcQ = false;
      bool kkbRAwTtFx = false;
      bool MUaRGmqfWp = false;
      bool ISAlUSQMDY = false;
      bool TyAmPyhaSY = false;
      bool FoaqqEkhJh = false;
      bool YQhmHRkpxh = false;
      bool eGpfcNTnBH = false;
      string MRDEXXSueu;
      string FRxYHRSVzc;
      string XXokbCXpCX;
      string WEOdiTmBnd;
      string RClmJFlOWL;
      string XwnCnncSbV;
      string AbsGXBCSpm;
      string dRgULUlCaW;
      string PJSpzZQMpt;
      string qUYRcoJeOI;
      string CTXjhGOSpT;
      string CaqFFqJDHx;
      string jpcuuJrPqV;
      string LHmSTwkhIs;
      string KxVWrQcTMl;
      string eGXQXLpbnY;
      string NzbUHumXkJ;
      string GatNmlUGDe;
      string fXCFpFjVuH;
      string GIsjeKVAOx;
      if(MRDEXXSueu == CTXjhGOSpT){cFhDfELJdk = true;}
      else if(CTXjhGOSpT == MRDEXXSueu){eQcYoQDdDB = true;}
      if(FRxYHRSVzc == CaqFFqJDHx){qiYJrpxVeC = true;}
      else if(CaqFFqJDHx == FRxYHRSVzc){jKsTUYignE = true;}
      if(XXokbCXpCX == jpcuuJrPqV){KRccCxgKib = true;}
      else if(jpcuuJrPqV == XXokbCXpCX){YLzPUPxEcQ = true;}
      if(WEOdiTmBnd == LHmSTwkhIs){QTrFCZozZl = true;}
      else if(LHmSTwkhIs == WEOdiTmBnd){kkbRAwTtFx = true;}
      if(RClmJFlOWL == KxVWrQcTMl){sZqKQWjjqo = true;}
      else if(KxVWrQcTMl == RClmJFlOWL){MUaRGmqfWp = true;}
      if(XwnCnncSbV == eGXQXLpbnY){NAVMlKcFAh = true;}
      else if(eGXQXLpbnY == XwnCnncSbV){ISAlUSQMDY = true;}
      if(AbsGXBCSpm == NzbUHumXkJ){WBaCUWqSHS = true;}
      else if(NzbUHumXkJ == AbsGXBCSpm){TyAmPyhaSY = true;}
      if(dRgULUlCaW == GatNmlUGDe){AxwrIkZRLf = true;}
      if(PJSpzZQMpt == fXCFpFjVuH){NxStNQyeTq = true;}
      if(qUYRcoJeOI == GIsjeKVAOx){xjzqPrznpt = true;}
      while(GatNmlUGDe == dRgULUlCaW){FoaqqEkhJh = true;}
      while(fXCFpFjVuH == fXCFpFjVuH){YQhmHRkpxh = true;}
      while(GIsjeKVAOx == GIsjeKVAOx){eGpfcNTnBH = true;}
      if(cFhDfELJdk == true){cFhDfELJdk = false;}
      if(qiYJrpxVeC == true){qiYJrpxVeC = false;}
      if(KRccCxgKib == true){KRccCxgKib = false;}
      if(QTrFCZozZl == true){QTrFCZozZl = false;}
      if(sZqKQWjjqo == true){sZqKQWjjqo = false;}
      if(NAVMlKcFAh == true){NAVMlKcFAh = false;}
      if(WBaCUWqSHS == true){WBaCUWqSHS = false;}
      if(AxwrIkZRLf == true){AxwrIkZRLf = false;}
      if(NxStNQyeTq == true){NxStNQyeTq = false;}
      if(xjzqPrznpt == true){xjzqPrznpt = false;}
      if(eQcYoQDdDB == true){eQcYoQDdDB = false;}
      if(jKsTUYignE == true){jKsTUYignE = false;}
      if(YLzPUPxEcQ == true){YLzPUPxEcQ = false;}
      if(kkbRAwTtFx == true){kkbRAwTtFx = false;}
      if(MUaRGmqfWp == true){MUaRGmqfWp = false;}
      if(ISAlUSQMDY == true){ISAlUSQMDY = false;}
      if(TyAmPyhaSY == true){TyAmPyhaSY = false;}
      if(FoaqqEkhJh == true){FoaqqEkhJh = false;}
      if(YQhmHRkpxh == true){YQhmHRkpxh = false;}
      if(eGpfcNTnBH == true){eGpfcNTnBH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMDDLOZNNA
{ 
  void ljWKiCBVGn()
  { 
      bool HopcWnrJHU = false;
      bool mSFCtzbKiy = false;
      bool PufiBEZfXs = false;
      bool EMHZTnFeLj = false;
      bool qIdOJclthC = false;
      bool kNqwKLJGaR = false;
      bool NLlNQaLfhG = false;
      bool sxyzGGQQYY = false;
      bool ReyUIqUKOH = false;
      bool eyDtVfWPyi = false;
      bool RGMaImOqoD = false;
      bool ushCzhMRFZ = false;
      bool FAQabusEda = false;
      bool jARpHLSXLU = false;
      bool bcULLlQBum = false;
      bool SEKYcQpkzN = false;
      bool tKNOTuaqtn = false;
      bool PoFjyceFOo = false;
      bool eqJqHeosMp = false;
      bool VgXyaQPGrQ = false;
      string ouKtftOeyV;
      string nKjsFZuAtT;
      string buxgSwiyJQ;
      string FdMJoTiCaa;
      string afmgEwbUez;
      string GqPkOtxcaj;
      string KQUgQJyaEk;
      string psZSswIQcW;
      string TOSKKNOauu;
      string VFaqPJLFPt;
      string yBPsINRwrS;
      string kgzEPwxKWC;
      string uWfJPjRhCj;
      string jCAiXRyZBx;
      string wRicJnGWaT;
      string LBiNyaVGcY;
      string uisHhigQfy;
      string xWIYGcnCAa;
      string duHiXiSljx;
      string wrxbBMYauZ;
      if(ouKtftOeyV == yBPsINRwrS){HopcWnrJHU = true;}
      else if(yBPsINRwrS == ouKtftOeyV){RGMaImOqoD = true;}
      if(nKjsFZuAtT == kgzEPwxKWC){mSFCtzbKiy = true;}
      else if(kgzEPwxKWC == nKjsFZuAtT){ushCzhMRFZ = true;}
      if(buxgSwiyJQ == uWfJPjRhCj){PufiBEZfXs = true;}
      else if(uWfJPjRhCj == buxgSwiyJQ){FAQabusEda = true;}
      if(FdMJoTiCaa == jCAiXRyZBx){EMHZTnFeLj = true;}
      else if(jCAiXRyZBx == FdMJoTiCaa){jARpHLSXLU = true;}
      if(afmgEwbUez == wRicJnGWaT){qIdOJclthC = true;}
      else if(wRicJnGWaT == afmgEwbUez){bcULLlQBum = true;}
      if(GqPkOtxcaj == LBiNyaVGcY){kNqwKLJGaR = true;}
      else if(LBiNyaVGcY == GqPkOtxcaj){SEKYcQpkzN = true;}
      if(KQUgQJyaEk == uisHhigQfy){NLlNQaLfhG = true;}
      else if(uisHhigQfy == KQUgQJyaEk){tKNOTuaqtn = true;}
      if(psZSswIQcW == xWIYGcnCAa){sxyzGGQQYY = true;}
      if(TOSKKNOauu == duHiXiSljx){ReyUIqUKOH = true;}
      if(VFaqPJLFPt == wrxbBMYauZ){eyDtVfWPyi = true;}
      while(xWIYGcnCAa == psZSswIQcW){PoFjyceFOo = true;}
      while(duHiXiSljx == duHiXiSljx){eqJqHeosMp = true;}
      while(wrxbBMYauZ == wrxbBMYauZ){VgXyaQPGrQ = true;}
      if(HopcWnrJHU == true){HopcWnrJHU = false;}
      if(mSFCtzbKiy == true){mSFCtzbKiy = false;}
      if(PufiBEZfXs == true){PufiBEZfXs = false;}
      if(EMHZTnFeLj == true){EMHZTnFeLj = false;}
      if(qIdOJclthC == true){qIdOJclthC = false;}
      if(kNqwKLJGaR == true){kNqwKLJGaR = false;}
      if(NLlNQaLfhG == true){NLlNQaLfhG = false;}
      if(sxyzGGQQYY == true){sxyzGGQQYY = false;}
      if(ReyUIqUKOH == true){ReyUIqUKOH = false;}
      if(eyDtVfWPyi == true){eyDtVfWPyi = false;}
      if(RGMaImOqoD == true){RGMaImOqoD = false;}
      if(ushCzhMRFZ == true){ushCzhMRFZ = false;}
      if(FAQabusEda == true){FAQabusEda = false;}
      if(jARpHLSXLU == true){jARpHLSXLU = false;}
      if(bcULLlQBum == true){bcULLlQBum = false;}
      if(SEKYcQpkzN == true){SEKYcQpkzN = false;}
      if(tKNOTuaqtn == true){tKNOTuaqtn = false;}
      if(PoFjyceFOo == true){PoFjyceFOo = false;}
      if(eqJqHeosMp == true){eqJqHeosMp = false;}
      if(VgXyaQPGrQ == true){VgXyaQPGrQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LQYHRMWLZC
{ 
  void PBTpscbIir()
  { 
      bool LffSEQehsE = false;
      bool qNwyMmgOln = false;
      bool qLGIyuwUlD = false;
      bool HnjZdSNIxt = false;
      bool lKxjyspdwD = false;
      bool wULAHzYWUJ = false;
      bool TKupxCdVUt = false;
      bool ZXRrCgOWJE = false;
      bool ESYhGlcjRd = false;
      bool sqnmZaOGmw = false;
      bool PTIBdXDTxa = false;
      bool kCMPEBlMiK = false;
      bool ZsEqBhjeRb = false;
      bool RHiNnkJWEi = false;
      bool hJmqspeXhY = false;
      bool oBWbVVPRAw = false;
      bool nYBVIcSybT = false;
      bool qPIAbQGNxK = false;
      bool CLwrmQkHrR = false;
      bool VrVItJHQhP = false;
      string PzRuMFhcnu;
      string TnpxxtKDIK;
      string xMULDHjjXG;
      string eWTsWMNodu;
      string dNuJlcEBbR;
      string biRcQDdFrE;
      string VyFhPxUwak;
      string gVZNfjQKZZ;
      string DhHFewEpbT;
      string hHwZZfINsn;
      string HHaqkGJEwg;
      string lTfRBnpzCT;
      string reUGDZYAmA;
      string aDQkSuGQUY;
      string mAsuhNaeXl;
      string pJLZwcmUnL;
      string gIQwGiCuzF;
      string gYdcgqkYYo;
      string ysbBKRrpnp;
      string HlcJqdjxoy;
      if(PzRuMFhcnu == HHaqkGJEwg){LffSEQehsE = true;}
      else if(HHaqkGJEwg == PzRuMFhcnu){PTIBdXDTxa = true;}
      if(TnpxxtKDIK == lTfRBnpzCT){qNwyMmgOln = true;}
      else if(lTfRBnpzCT == TnpxxtKDIK){kCMPEBlMiK = true;}
      if(xMULDHjjXG == reUGDZYAmA){qLGIyuwUlD = true;}
      else if(reUGDZYAmA == xMULDHjjXG){ZsEqBhjeRb = true;}
      if(eWTsWMNodu == aDQkSuGQUY){HnjZdSNIxt = true;}
      else if(aDQkSuGQUY == eWTsWMNodu){RHiNnkJWEi = true;}
      if(dNuJlcEBbR == mAsuhNaeXl){lKxjyspdwD = true;}
      else if(mAsuhNaeXl == dNuJlcEBbR){hJmqspeXhY = true;}
      if(biRcQDdFrE == pJLZwcmUnL){wULAHzYWUJ = true;}
      else if(pJLZwcmUnL == biRcQDdFrE){oBWbVVPRAw = true;}
      if(VyFhPxUwak == gIQwGiCuzF){TKupxCdVUt = true;}
      else if(gIQwGiCuzF == VyFhPxUwak){nYBVIcSybT = true;}
      if(gVZNfjQKZZ == gYdcgqkYYo){ZXRrCgOWJE = true;}
      if(DhHFewEpbT == ysbBKRrpnp){ESYhGlcjRd = true;}
      if(hHwZZfINsn == HlcJqdjxoy){sqnmZaOGmw = true;}
      while(gYdcgqkYYo == gVZNfjQKZZ){qPIAbQGNxK = true;}
      while(ysbBKRrpnp == ysbBKRrpnp){CLwrmQkHrR = true;}
      while(HlcJqdjxoy == HlcJqdjxoy){VrVItJHQhP = true;}
      if(LffSEQehsE == true){LffSEQehsE = false;}
      if(qNwyMmgOln == true){qNwyMmgOln = false;}
      if(qLGIyuwUlD == true){qLGIyuwUlD = false;}
      if(HnjZdSNIxt == true){HnjZdSNIxt = false;}
      if(lKxjyspdwD == true){lKxjyspdwD = false;}
      if(wULAHzYWUJ == true){wULAHzYWUJ = false;}
      if(TKupxCdVUt == true){TKupxCdVUt = false;}
      if(ZXRrCgOWJE == true){ZXRrCgOWJE = false;}
      if(ESYhGlcjRd == true){ESYhGlcjRd = false;}
      if(sqnmZaOGmw == true){sqnmZaOGmw = false;}
      if(PTIBdXDTxa == true){PTIBdXDTxa = false;}
      if(kCMPEBlMiK == true){kCMPEBlMiK = false;}
      if(ZsEqBhjeRb == true){ZsEqBhjeRb = false;}
      if(RHiNnkJWEi == true){RHiNnkJWEi = false;}
      if(hJmqspeXhY == true){hJmqspeXhY = false;}
      if(oBWbVVPRAw == true){oBWbVVPRAw = false;}
      if(nYBVIcSybT == true){nYBVIcSybT = false;}
      if(qPIAbQGNxK == true){qPIAbQGNxK = false;}
      if(CLwrmQkHrR == true){CLwrmQkHrR = false;}
      if(VrVItJHQhP == true){VrVItJHQhP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQZEWRZUYZ
{ 
  void xCfjasKEDp()
  { 
      bool XEyIEQJenO = false;
      bool YabDFdarKR = false;
      bool QXcblXzREp = false;
      bool dXADIuDKgc = false;
      bool ChFeJVeTnL = false;
      bool bfCcAzbVVg = false;
      bool QqayjAaXtK = false;
      bool ZPKgOhRyRQ = false;
      bool recsNxUWDJ = false;
      bool SgnALKHHtJ = false;
      bool uGZckMUUOR = false;
      bool hdEFnlOhjl = false;
      bool eDUkqsaKVD = false;
      bool aKDIVkFzHB = false;
      bool czIkaobiLZ = false;
      bool wZWHdqlolq = false;
      bool kJzKqWZwjC = false;
      bool gOZhJetiJB = false;
      bool QrzuGBmwdd = false;
      bool zPNPPSzytE = false;
      string VHNeMLJmoF;
      string hmNdcEmJGC;
      string kgPAWCJTwR;
      string NgiJAZUSET;
      string FWJQVRtqHP;
      string IKigYnrMIK;
      string BoqWrBEEcC;
      string iTFlwNXzeF;
      string ISLfICxBjL;
      string gIKsRQflXU;
      string MpNFfnFwjL;
      string QrgCBicKNp;
      string DCTQUaJLTf;
      string glaKrSEGzT;
      string wBRYunaHri;
      string mUYhQJVxjF;
      string etcDddQWJi;
      string eWLssCkuUg;
      string zBTksMNssh;
      string wHWtoCXNtR;
      if(VHNeMLJmoF == MpNFfnFwjL){XEyIEQJenO = true;}
      else if(MpNFfnFwjL == VHNeMLJmoF){uGZckMUUOR = true;}
      if(hmNdcEmJGC == QrgCBicKNp){YabDFdarKR = true;}
      else if(QrgCBicKNp == hmNdcEmJGC){hdEFnlOhjl = true;}
      if(kgPAWCJTwR == DCTQUaJLTf){QXcblXzREp = true;}
      else if(DCTQUaJLTf == kgPAWCJTwR){eDUkqsaKVD = true;}
      if(NgiJAZUSET == glaKrSEGzT){dXADIuDKgc = true;}
      else if(glaKrSEGzT == NgiJAZUSET){aKDIVkFzHB = true;}
      if(FWJQVRtqHP == wBRYunaHri){ChFeJVeTnL = true;}
      else if(wBRYunaHri == FWJQVRtqHP){czIkaobiLZ = true;}
      if(IKigYnrMIK == mUYhQJVxjF){bfCcAzbVVg = true;}
      else if(mUYhQJVxjF == IKigYnrMIK){wZWHdqlolq = true;}
      if(BoqWrBEEcC == etcDddQWJi){QqayjAaXtK = true;}
      else if(etcDddQWJi == BoqWrBEEcC){kJzKqWZwjC = true;}
      if(iTFlwNXzeF == eWLssCkuUg){ZPKgOhRyRQ = true;}
      if(ISLfICxBjL == zBTksMNssh){recsNxUWDJ = true;}
      if(gIKsRQflXU == wHWtoCXNtR){SgnALKHHtJ = true;}
      while(eWLssCkuUg == iTFlwNXzeF){gOZhJetiJB = true;}
      while(zBTksMNssh == zBTksMNssh){QrzuGBmwdd = true;}
      while(wHWtoCXNtR == wHWtoCXNtR){zPNPPSzytE = true;}
      if(XEyIEQJenO == true){XEyIEQJenO = false;}
      if(YabDFdarKR == true){YabDFdarKR = false;}
      if(QXcblXzREp == true){QXcblXzREp = false;}
      if(dXADIuDKgc == true){dXADIuDKgc = false;}
      if(ChFeJVeTnL == true){ChFeJVeTnL = false;}
      if(bfCcAzbVVg == true){bfCcAzbVVg = false;}
      if(QqayjAaXtK == true){QqayjAaXtK = false;}
      if(ZPKgOhRyRQ == true){ZPKgOhRyRQ = false;}
      if(recsNxUWDJ == true){recsNxUWDJ = false;}
      if(SgnALKHHtJ == true){SgnALKHHtJ = false;}
      if(uGZckMUUOR == true){uGZckMUUOR = false;}
      if(hdEFnlOhjl == true){hdEFnlOhjl = false;}
      if(eDUkqsaKVD == true){eDUkqsaKVD = false;}
      if(aKDIVkFzHB == true){aKDIVkFzHB = false;}
      if(czIkaobiLZ == true){czIkaobiLZ = false;}
      if(wZWHdqlolq == true){wZWHdqlolq = false;}
      if(kJzKqWZwjC == true){kJzKqWZwjC = false;}
      if(gOZhJetiJB == true){gOZhJetiJB = false;}
      if(QrzuGBmwdd == true){QrzuGBmwdd = false;}
      if(zPNPPSzytE == true){zPNPPSzytE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NPHJIBKNEM
{ 
  void PktYwquXMy()
  { 
      bool iyhlRJQpFH = false;
      bool yMziPUjfcG = false;
      bool CaaLGeEbno = false;
      bool LddJMFIcJQ = false;
      bool HqiwFgPStk = false;
      bool WNrNMIWVel = false;
      bool EnCPuTioWJ = false;
      bool MHVMzLqdGZ = false;
      bool PlhDRxkPxD = false;
      bool ilyWLSoTAk = false;
      bool yawkXPrfNB = false;
      bool RrOFWSGzxy = false;
      bool iSrSaZIyAg = false;
      bool WWcVbopxeC = false;
      bool FFCukpXsAs = false;
      bool LpVCBfhcJy = false;
      bool GsegetPrdh = false;
      bool bJTurcPwhk = false;
      bool CPyHUfAaTu = false;
      bool GNmfuMZUQp = false;
      string IVoXdhYmAJ;
      string epIALOHqxl;
      string MpQIiRNfpV;
      string xaBHWKHDBO;
      string tQaSXLHbaJ;
      string DpdjCSEgoM;
      string TrwdLDoBcA;
      string HDohquPykX;
      string JlFfRHxQFD;
      string FZOotBTwGT;
      string VGyZBAAurG;
      string DGwQDhlQLE;
      string GXwZuhnAno;
      string bSqQBDmfdR;
      string HBYyAzdxlM;
      string PDkCMyJYeT;
      string LzHCejPePA;
      string tGltxFzxYu;
      string EpObZXhoED;
      string sOBKFHtVTP;
      if(IVoXdhYmAJ == VGyZBAAurG){iyhlRJQpFH = true;}
      else if(VGyZBAAurG == IVoXdhYmAJ){yawkXPrfNB = true;}
      if(epIALOHqxl == DGwQDhlQLE){yMziPUjfcG = true;}
      else if(DGwQDhlQLE == epIALOHqxl){RrOFWSGzxy = true;}
      if(MpQIiRNfpV == GXwZuhnAno){CaaLGeEbno = true;}
      else if(GXwZuhnAno == MpQIiRNfpV){iSrSaZIyAg = true;}
      if(xaBHWKHDBO == bSqQBDmfdR){LddJMFIcJQ = true;}
      else if(bSqQBDmfdR == xaBHWKHDBO){WWcVbopxeC = true;}
      if(tQaSXLHbaJ == HBYyAzdxlM){HqiwFgPStk = true;}
      else if(HBYyAzdxlM == tQaSXLHbaJ){FFCukpXsAs = true;}
      if(DpdjCSEgoM == PDkCMyJYeT){WNrNMIWVel = true;}
      else if(PDkCMyJYeT == DpdjCSEgoM){LpVCBfhcJy = true;}
      if(TrwdLDoBcA == LzHCejPePA){EnCPuTioWJ = true;}
      else if(LzHCejPePA == TrwdLDoBcA){GsegetPrdh = true;}
      if(HDohquPykX == tGltxFzxYu){MHVMzLqdGZ = true;}
      if(JlFfRHxQFD == EpObZXhoED){PlhDRxkPxD = true;}
      if(FZOotBTwGT == sOBKFHtVTP){ilyWLSoTAk = true;}
      while(tGltxFzxYu == HDohquPykX){bJTurcPwhk = true;}
      while(EpObZXhoED == EpObZXhoED){CPyHUfAaTu = true;}
      while(sOBKFHtVTP == sOBKFHtVTP){GNmfuMZUQp = true;}
      if(iyhlRJQpFH == true){iyhlRJQpFH = false;}
      if(yMziPUjfcG == true){yMziPUjfcG = false;}
      if(CaaLGeEbno == true){CaaLGeEbno = false;}
      if(LddJMFIcJQ == true){LddJMFIcJQ = false;}
      if(HqiwFgPStk == true){HqiwFgPStk = false;}
      if(WNrNMIWVel == true){WNrNMIWVel = false;}
      if(EnCPuTioWJ == true){EnCPuTioWJ = false;}
      if(MHVMzLqdGZ == true){MHVMzLqdGZ = false;}
      if(PlhDRxkPxD == true){PlhDRxkPxD = false;}
      if(ilyWLSoTAk == true){ilyWLSoTAk = false;}
      if(yawkXPrfNB == true){yawkXPrfNB = false;}
      if(RrOFWSGzxy == true){RrOFWSGzxy = false;}
      if(iSrSaZIyAg == true){iSrSaZIyAg = false;}
      if(WWcVbopxeC == true){WWcVbopxeC = false;}
      if(FFCukpXsAs == true){FFCukpXsAs = false;}
      if(LpVCBfhcJy == true){LpVCBfhcJy = false;}
      if(GsegetPrdh == true){GsegetPrdh = false;}
      if(bJTurcPwhk == true){bJTurcPwhk = false;}
      if(CPyHUfAaTu == true){CPyHUfAaTu = false;}
      if(GNmfuMZUQp == true){GNmfuMZUQp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQJPUWQMAR
{ 
  void mSgwfYbYFI()
  { 
      bool jmpsGpElrJ = false;
      bool lWGZYqYwga = false;
      bool xaLYWoJYGQ = false;
      bool RIDmhSUzPq = false;
      bool KVchWAetnw = false;
      bool MjeIkIaRVR = false;
      bool fefaqdSTqG = false;
      bool VZfpQaydBV = false;
      bool JOkJEhdtBY = false;
      bool qDcxKepBps = false;
      bool gLDhamDnrK = false;
      bool KxPzIQtVWJ = false;
      bool AYRSORwhek = false;
      bool kxmInyLDhQ = false;
      bool doCqOsndot = false;
      bool jTdfsIskSJ = false;
      bool qUJGYMJGKJ = false;
      bool EqmFeKVZDV = false;
      bool cSskBQSGPf = false;
      bool FakYZIeuRB = false;
      string kysNGYfduB;
      string mAZcOyzGlR;
      string llVhySilie;
      string wTRpiVGnGL;
      string FNfEahKgiR;
      string zwxbTzcLPm;
      string pttPEThjsr;
      string qKzZMXFQHP;
      string IBDRezVoVi;
      string suYSVLSQAG;
      string zZmqZoxWPu;
      string tMEzenpcjE;
      string xsOKywlfEB;
      string FnPAPiNMqp;
      string CzYZnfpZng;
      string UpfuIGKcrd;
      string CQSNpFwDiu;
      string ZdltCyTnVS;
      string FLrWgOIUrJ;
      string XkTMmkfLji;
      if(kysNGYfduB == zZmqZoxWPu){jmpsGpElrJ = true;}
      else if(zZmqZoxWPu == kysNGYfduB){gLDhamDnrK = true;}
      if(mAZcOyzGlR == tMEzenpcjE){lWGZYqYwga = true;}
      else if(tMEzenpcjE == mAZcOyzGlR){KxPzIQtVWJ = true;}
      if(llVhySilie == xsOKywlfEB){xaLYWoJYGQ = true;}
      else if(xsOKywlfEB == llVhySilie){AYRSORwhek = true;}
      if(wTRpiVGnGL == FnPAPiNMqp){RIDmhSUzPq = true;}
      else if(FnPAPiNMqp == wTRpiVGnGL){kxmInyLDhQ = true;}
      if(FNfEahKgiR == CzYZnfpZng){KVchWAetnw = true;}
      else if(CzYZnfpZng == FNfEahKgiR){doCqOsndot = true;}
      if(zwxbTzcLPm == UpfuIGKcrd){MjeIkIaRVR = true;}
      else if(UpfuIGKcrd == zwxbTzcLPm){jTdfsIskSJ = true;}
      if(pttPEThjsr == CQSNpFwDiu){fefaqdSTqG = true;}
      else if(CQSNpFwDiu == pttPEThjsr){qUJGYMJGKJ = true;}
      if(qKzZMXFQHP == ZdltCyTnVS){VZfpQaydBV = true;}
      if(IBDRezVoVi == FLrWgOIUrJ){JOkJEhdtBY = true;}
      if(suYSVLSQAG == XkTMmkfLji){qDcxKepBps = true;}
      while(ZdltCyTnVS == qKzZMXFQHP){EqmFeKVZDV = true;}
      while(FLrWgOIUrJ == FLrWgOIUrJ){cSskBQSGPf = true;}
      while(XkTMmkfLji == XkTMmkfLji){FakYZIeuRB = true;}
      if(jmpsGpElrJ == true){jmpsGpElrJ = false;}
      if(lWGZYqYwga == true){lWGZYqYwga = false;}
      if(xaLYWoJYGQ == true){xaLYWoJYGQ = false;}
      if(RIDmhSUzPq == true){RIDmhSUzPq = false;}
      if(KVchWAetnw == true){KVchWAetnw = false;}
      if(MjeIkIaRVR == true){MjeIkIaRVR = false;}
      if(fefaqdSTqG == true){fefaqdSTqG = false;}
      if(VZfpQaydBV == true){VZfpQaydBV = false;}
      if(JOkJEhdtBY == true){JOkJEhdtBY = false;}
      if(qDcxKepBps == true){qDcxKepBps = false;}
      if(gLDhamDnrK == true){gLDhamDnrK = false;}
      if(KxPzIQtVWJ == true){KxPzIQtVWJ = false;}
      if(AYRSORwhek == true){AYRSORwhek = false;}
      if(kxmInyLDhQ == true){kxmInyLDhQ = false;}
      if(doCqOsndot == true){doCqOsndot = false;}
      if(jTdfsIskSJ == true){jTdfsIskSJ = false;}
      if(qUJGYMJGKJ == true){qUJGYMJGKJ = false;}
      if(EqmFeKVZDV == true){EqmFeKVZDV = false;}
      if(cSskBQSGPf == true){cSskBQSGPf = false;}
      if(FakYZIeuRB == true){FakYZIeuRB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VCPQBYUQUN
{ 
  void pfUxaODZnU()
  { 
      bool fpyhcgyTVg = false;
      bool AZtBAkpVcH = false;
      bool JLMQwcgSUW = false;
      bool wtViDlhjPg = false;
      bool NyFUiXHfyg = false;
      bool zERgNUdgkz = false;
      bool zezzkGDLyN = false;
      bool DGFwsKGqgY = false;
      bool VBUnXqbnUh = false;
      bool IByPghzFjc = false;
      bool TugkdryVmD = false;
      bool NlzMdyKKbs = false;
      bool dPpPEBHpOL = false;
      bool LAGEEZTjKe = false;
      bool rGARTVBlkh = false;
      bool XodpyEFQfb = false;
      bool jIGbrNeuHD = false;
      bool eazwAXOYwh = false;
      bool AVEgnWVQFz = false;
      bool UCDitjzYZG = false;
      string HGwDcPDqDT;
      string cxBTggJcaH;
      string axICfLXOKt;
      string HMegLOVzZi;
      string SppFflXOGW;
      string JFIpeJysWR;
      string qogJMPRUHS;
      string LJCrnkHCWt;
      string mJHmkBEoBB;
      string PbcHqdJgsP;
      string TDGnLzDPBt;
      string CwWbehhsYK;
      string LcSFDigtBK;
      string baJGaiCSbk;
      string ynmHzTFAcI;
      string wPHhEpkAkc;
      string SIOqSbmPBu;
      string eORmMWpKGj;
      string cgRrNLSaCj;
      string yBhySpZunW;
      if(HGwDcPDqDT == TDGnLzDPBt){fpyhcgyTVg = true;}
      else if(TDGnLzDPBt == HGwDcPDqDT){TugkdryVmD = true;}
      if(cxBTggJcaH == CwWbehhsYK){AZtBAkpVcH = true;}
      else if(CwWbehhsYK == cxBTggJcaH){NlzMdyKKbs = true;}
      if(axICfLXOKt == LcSFDigtBK){JLMQwcgSUW = true;}
      else if(LcSFDigtBK == axICfLXOKt){dPpPEBHpOL = true;}
      if(HMegLOVzZi == baJGaiCSbk){wtViDlhjPg = true;}
      else if(baJGaiCSbk == HMegLOVzZi){LAGEEZTjKe = true;}
      if(SppFflXOGW == ynmHzTFAcI){NyFUiXHfyg = true;}
      else if(ynmHzTFAcI == SppFflXOGW){rGARTVBlkh = true;}
      if(JFIpeJysWR == wPHhEpkAkc){zERgNUdgkz = true;}
      else if(wPHhEpkAkc == JFIpeJysWR){XodpyEFQfb = true;}
      if(qogJMPRUHS == SIOqSbmPBu){zezzkGDLyN = true;}
      else if(SIOqSbmPBu == qogJMPRUHS){jIGbrNeuHD = true;}
      if(LJCrnkHCWt == eORmMWpKGj){DGFwsKGqgY = true;}
      if(mJHmkBEoBB == cgRrNLSaCj){VBUnXqbnUh = true;}
      if(PbcHqdJgsP == yBhySpZunW){IByPghzFjc = true;}
      while(eORmMWpKGj == LJCrnkHCWt){eazwAXOYwh = true;}
      while(cgRrNLSaCj == cgRrNLSaCj){AVEgnWVQFz = true;}
      while(yBhySpZunW == yBhySpZunW){UCDitjzYZG = true;}
      if(fpyhcgyTVg == true){fpyhcgyTVg = false;}
      if(AZtBAkpVcH == true){AZtBAkpVcH = false;}
      if(JLMQwcgSUW == true){JLMQwcgSUW = false;}
      if(wtViDlhjPg == true){wtViDlhjPg = false;}
      if(NyFUiXHfyg == true){NyFUiXHfyg = false;}
      if(zERgNUdgkz == true){zERgNUdgkz = false;}
      if(zezzkGDLyN == true){zezzkGDLyN = false;}
      if(DGFwsKGqgY == true){DGFwsKGqgY = false;}
      if(VBUnXqbnUh == true){VBUnXqbnUh = false;}
      if(IByPghzFjc == true){IByPghzFjc = false;}
      if(TugkdryVmD == true){TugkdryVmD = false;}
      if(NlzMdyKKbs == true){NlzMdyKKbs = false;}
      if(dPpPEBHpOL == true){dPpPEBHpOL = false;}
      if(LAGEEZTjKe == true){LAGEEZTjKe = false;}
      if(rGARTVBlkh == true){rGARTVBlkh = false;}
      if(XodpyEFQfb == true){XodpyEFQfb = false;}
      if(jIGbrNeuHD == true){jIGbrNeuHD = false;}
      if(eazwAXOYwh == true){eazwAXOYwh = false;}
      if(AVEgnWVQFz == true){AVEgnWVQFz = false;}
      if(UCDitjzYZG == true){UCDitjzYZG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LZBVYIFHWM
{ 
  void uHeGMjnOce()
  { 
      bool bCUSPJoKss = false;
      bool EdtUhnpJKS = false;
      bool qRdEPeclnp = false;
      bool KaemoRbkef = false;
      bool KVPyfeHnPG = false;
      bool RDtIcKYPDj = false;
      bool fCVCidzHeP = false;
      bool MEddHUCfYk = false;
      bool WoVgYGgVJe = false;
      bool sLhtzHAMPC = false;
      bool eAIztNYPAH = false;
      bool HsqSMqfndb = false;
      bool xcxAWAWidz = false;
      bool UoPVFWfVmK = false;
      bool gQUBWAUPhH = false;
      bool bLhmFCCIcs = false;
      bool pokBmRcUNp = false;
      bool LJBStfHucV = false;
      bool fGBWXIGcQC = false;
      bool TWstTqeTNE = false;
      string TNYlwVyfln;
      string fVwKIDCMke;
      string dknakAkNww;
      string qctLXGDXGO;
      string OtzrJuVkKx;
      string WxQDaiZxBw;
      string jkjoxCaklC;
      string AdFVQikwRo;
      string dADyYtMqko;
      string gFWJedKKuH;
      string TkyHxrqulq;
      string ycfLRihkPC;
      string ojAxVtHwpl;
      string YaBJUsCuBf;
      string DREsqDYKqw;
      string wYtrRjkAlD;
      string kuEARWaWpY;
      string gljjzXeGGR;
      string UwEtpzfIrk;
      string IBIyuINEaT;
      if(TNYlwVyfln == TkyHxrqulq){bCUSPJoKss = true;}
      else if(TkyHxrqulq == TNYlwVyfln){eAIztNYPAH = true;}
      if(fVwKIDCMke == ycfLRihkPC){EdtUhnpJKS = true;}
      else if(ycfLRihkPC == fVwKIDCMke){HsqSMqfndb = true;}
      if(dknakAkNww == ojAxVtHwpl){qRdEPeclnp = true;}
      else if(ojAxVtHwpl == dknakAkNww){xcxAWAWidz = true;}
      if(qctLXGDXGO == YaBJUsCuBf){KaemoRbkef = true;}
      else if(YaBJUsCuBf == qctLXGDXGO){UoPVFWfVmK = true;}
      if(OtzrJuVkKx == DREsqDYKqw){KVPyfeHnPG = true;}
      else if(DREsqDYKqw == OtzrJuVkKx){gQUBWAUPhH = true;}
      if(WxQDaiZxBw == wYtrRjkAlD){RDtIcKYPDj = true;}
      else if(wYtrRjkAlD == WxQDaiZxBw){bLhmFCCIcs = true;}
      if(jkjoxCaklC == kuEARWaWpY){fCVCidzHeP = true;}
      else if(kuEARWaWpY == jkjoxCaklC){pokBmRcUNp = true;}
      if(AdFVQikwRo == gljjzXeGGR){MEddHUCfYk = true;}
      if(dADyYtMqko == UwEtpzfIrk){WoVgYGgVJe = true;}
      if(gFWJedKKuH == IBIyuINEaT){sLhtzHAMPC = true;}
      while(gljjzXeGGR == AdFVQikwRo){LJBStfHucV = true;}
      while(UwEtpzfIrk == UwEtpzfIrk){fGBWXIGcQC = true;}
      while(IBIyuINEaT == IBIyuINEaT){TWstTqeTNE = true;}
      if(bCUSPJoKss == true){bCUSPJoKss = false;}
      if(EdtUhnpJKS == true){EdtUhnpJKS = false;}
      if(qRdEPeclnp == true){qRdEPeclnp = false;}
      if(KaemoRbkef == true){KaemoRbkef = false;}
      if(KVPyfeHnPG == true){KVPyfeHnPG = false;}
      if(RDtIcKYPDj == true){RDtIcKYPDj = false;}
      if(fCVCidzHeP == true){fCVCidzHeP = false;}
      if(MEddHUCfYk == true){MEddHUCfYk = false;}
      if(WoVgYGgVJe == true){WoVgYGgVJe = false;}
      if(sLhtzHAMPC == true){sLhtzHAMPC = false;}
      if(eAIztNYPAH == true){eAIztNYPAH = false;}
      if(HsqSMqfndb == true){HsqSMqfndb = false;}
      if(xcxAWAWidz == true){xcxAWAWidz = false;}
      if(UoPVFWfVmK == true){UoPVFWfVmK = false;}
      if(gQUBWAUPhH == true){gQUBWAUPhH = false;}
      if(bLhmFCCIcs == true){bLhmFCCIcs = false;}
      if(pokBmRcUNp == true){pokBmRcUNp = false;}
      if(LJBStfHucV == true){LJBStfHucV = false;}
      if(fGBWXIGcQC == true){fGBWXIGcQC = false;}
      if(TWstTqeTNE == true){TWstTqeTNE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GHJCGHSPPM
{ 
  void SLjfayCTWG()
  { 
      bool RfEIOmKuit = false;
      bool HHoBpkutsd = false;
      bool mTTBMcpkxB = false;
      bool xXhSrGSkqR = false;
      bool qyNPujIXLh = false;
      bool aKPhHyMDwk = false;
      bool xYxgwjYVJj = false;
      bool SJCaloFEFb = false;
      bool TRZPamHALt = false;
      bool sPoFURAgSL = false;
      bool KlObOQHouR = false;
      bool sIxTQezhFJ = false;
      bool bYKPpCTwFU = false;
      bool oXktRgDxAJ = false;
      bool eREsBkRUno = false;
      bool RSaIilbykM = false;
      bool xLjZcUWDCi = false;
      bool bBgueKTQOF = false;
      bool kzIQDVwbLe = false;
      bool FELnMTgdQf = false;
      string XjYLFMdEwJ;
      string SrhUGrwAAL;
      string LYXZzcrldm;
      string SKmXONwOkl;
      string xrOfMgwywW;
      string VLJWzyLzMb;
      string UqZJpIEJGs;
      string uhPNOSKrMS;
      string fsoGQHAPXP;
      string BxBIRFREoE;
      string bmrDanwwIg;
      string mTlswbBSri;
      string HnkpqyfGwJ;
      string AFDHpsAleb;
      string LEHqbhKIMp;
      string DyLGxnBCLc;
      string IoAyfgPdDD;
      string aPnQXCftNJ;
      string mXtFFCswKC;
      string qxZCSVEILu;
      if(XjYLFMdEwJ == bmrDanwwIg){RfEIOmKuit = true;}
      else if(bmrDanwwIg == XjYLFMdEwJ){KlObOQHouR = true;}
      if(SrhUGrwAAL == mTlswbBSri){HHoBpkutsd = true;}
      else if(mTlswbBSri == SrhUGrwAAL){sIxTQezhFJ = true;}
      if(LYXZzcrldm == HnkpqyfGwJ){mTTBMcpkxB = true;}
      else if(HnkpqyfGwJ == LYXZzcrldm){bYKPpCTwFU = true;}
      if(SKmXONwOkl == AFDHpsAleb){xXhSrGSkqR = true;}
      else if(AFDHpsAleb == SKmXONwOkl){oXktRgDxAJ = true;}
      if(xrOfMgwywW == LEHqbhKIMp){qyNPujIXLh = true;}
      else if(LEHqbhKIMp == xrOfMgwywW){eREsBkRUno = true;}
      if(VLJWzyLzMb == DyLGxnBCLc){aKPhHyMDwk = true;}
      else if(DyLGxnBCLc == VLJWzyLzMb){RSaIilbykM = true;}
      if(UqZJpIEJGs == IoAyfgPdDD){xYxgwjYVJj = true;}
      else if(IoAyfgPdDD == UqZJpIEJGs){xLjZcUWDCi = true;}
      if(uhPNOSKrMS == aPnQXCftNJ){SJCaloFEFb = true;}
      if(fsoGQHAPXP == mXtFFCswKC){TRZPamHALt = true;}
      if(BxBIRFREoE == qxZCSVEILu){sPoFURAgSL = true;}
      while(aPnQXCftNJ == uhPNOSKrMS){bBgueKTQOF = true;}
      while(mXtFFCswKC == mXtFFCswKC){kzIQDVwbLe = true;}
      while(qxZCSVEILu == qxZCSVEILu){FELnMTgdQf = true;}
      if(RfEIOmKuit == true){RfEIOmKuit = false;}
      if(HHoBpkutsd == true){HHoBpkutsd = false;}
      if(mTTBMcpkxB == true){mTTBMcpkxB = false;}
      if(xXhSrGSkqR == true){xXhSrGSkqR = false;}
      if(qyNPujIXLh == true){qyNPujIXLh = false;}
      if(aKPhHyMDwk == true){aKPhHyMDwk = false;}
      if(xYxgwjYVJj == true){xYxgwjYVJj = false;}
      if(SJCaloFEFb == true){SJCaloFEFb = false;}
      if(TRZPamHALt == true){TRZPamHALt = false;}
      if(sPoFURAgSL == true){sPoFURAgSL = false;}
      if(KlObOQHouR == true){KlObOQHouR = false;}
      if(sIxTQezhFJ == true){sIxTQezhFJ = false;}
      if(bYKPpCTwFU == true){bYKPpCTwFU = false;}
      if(oXktRgDxAJ == true){oXktRgDxAJ = false;}
      if(eREsBkRUno == true){eREsBkRUno = false;}
      if(RSaIilbykM == true){RSaIilbykM = false;}
      if(xLjZcUWDCi == true){xLjZcUWDCi = false;}
      if(bBgueKTQOF == true){bBgueKTQOF = false;}
      if(kzIQDVwbLe == true){kzIQDVwbLe = false;}
      if(FELnMTgdQf == true){FELnMTgdQf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TBVMHTIVBW
{ 
  void MeOkxsuOSt()
  { 
      bool shFLVPWVOy = false;
      bool ZePbsZhUbR = false;
      bool YkBeRdnNou = false;
      bool KGcQBpRjWi = false;
      bool LAnAMDOUyE = false;
      bool scfTCHfZsq = false;
      bool aIfTnTByaD = false;
      bool IxyrFXwBSN = false;
      bool PSPkBgaJNs = false;
      bool JqpeHDTUMs = false;
      bool BQttwuemNe = false;
      bool KeHfbIruRG = false;
      bool srjgtQGSkC = false;
      bool EbnZLyXVoG = false;
      bool CmuiidjKCy = false;
      bool KXCGzJfMAe = false;
      bool nLBLZiqhTd = false;
      bool jWGLEFwAyP = false;
      bool guQmrfYhZC = false;
      bool SLUJRqkjIA = false;
      string ASPIgapJpA;
      string wsSXlbnwVs;
      string xxkbBaXNIa;
      string fdoQfudZxa;
      string ksAhtozOqX;
      string HmfhQDhnHF;
      string DcAPUSDCqq;
      string xOzuHEwCgM;
      string aIVjTrxHzc;
      string NpSqXIrkNb;
      string kxWAZrmkZM;
      string GeGtetGPub;
      string UwCOcHuIWz;
      string LLoFbdlUKa;
      string FMhmViiXMd;
      string BcokGntHWS;
      string xdNZAtoASA;
      string HlFTVIOPrt;
      string YWwryiVDym;
      string idxqdayHlb;
      if(ASPIgapJpA == kxWAZrmkZM){shFLVPWVOy = true;}
      else if(kxWAZrmkZM == ASPIgapJpA){BQttwuemNe = true;}
      if(wsSXlbnwVs == GeGtetGPub){ZePbsZhUbR = true;}
      else if(GeGtetGPub == wsSXlbnwVs){KeHfbIruRG = true;}
      if(xxkbBaXNIa == UwCOcHuIWz){YkBeRdnNou = true;}
      else if(UwCOcHuIWz == xxkbBaXNIa){srjgtQGSkC = true;}
      if(fdoQfudZxa == LLoFbdlUKa){KGcQBpRjWi = true;}
      else if(LLoFbdlUKa == fdoQfudZxa){EbnZLyXVoG = true;}
      if(ksAhtozOqX == FMhmViiXMd){LAnAMDOUyE = true;}
      else if(FMhmViiXMd == ksAhtozOqX){CmuiidjKCy = true;}
      if(HmfhQDhnHF == BcokGntHWS){scfTCHfZsq = true;}
      else if(BcokGntHWS == HmfhQDhnHF){KXCGzJfMAe = true;}
      if(DcAPUSDCqq == xdNZAtoASA){aIfTnTByaD = true;}
      else if(xdNZAtoASA == DcAPUSDCqq){nLBLZiqhTd = true;}
      if(xOzuHEwCgM == HlFTVIOPrt){IxyrFXwBSN = true;}
      if(aIVjTrxHzc == YWwryiVDym){PSPkBgaJNs = true;}
      if(NpSqXIrkNb == idxqdayHlb){JqpeHDTUMs = true;}
      while(HlFTVIOPrt == xOzuHEwCgM){jWGLEFwAyP = true;}
      while(YWwryiVDym == YWwryiVDym){guQmrfYhZC = true;}
      while(idxqdayHlb == idxqdayHlb){SLUJRqkjIA = true;}
      if(shFLVPWVOy == true){shFLVPWVOy = false;}
      if(ZePbsZhUbR == true){ZePbsZhUbR = false;}
      if(YkBeRdnNou == true){YkBeRdnNou = false;}
      if(KGcQBpRjWi == true){KGcQBpRjWi = false;}
      if(LAnAMDOUyE == true){LAnAMDOUyE = false;}
      if(scfTCHfZsq == true){scfTCHfZsq = false;}
      if(aIfTnTByaD == true){aIfTnTByaD = false;}
      if(IxyrFXwBSN == true){IxyrFXwBSN = false;}
      if(PSPkBgaJNs == true){PSPkBgaJNs = false;}
      if(JqpeHDTUMs == true){JqpeHDTUMs = false;}
      if(BQttwuemNe == true){BQttwuemNe = false;}
      if(KeHfbIruRG == true){KeHfbIruRG = false;}
      if(srjgtQGSkC == true){srjgtQGSkC = false;}
      if(EbnZLyXVoG == true){EbnZLyXVoG = false;}
      if(CmuiidjKCy == true){CmuiidjKCy = false;}
      if(KXCGzJfMAe == true){KXCGzJfMAe = false;}
      if(nLBLZiqhTd == true){nLBLZiqhTd = false;}
      if(jWGLEFwAyP == true){jWGLEFwAyP = false;}
      if(guQmrfYhZC == true){guQmrfYhZC = false;}
      if(SLUJRqkjIA == true){SLUJRqkjIA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UTNEDEHNAQ
{ 
  void YLXrknprLD()
  { 
      bool bKQDUqjgGN = false;
      bool BZEolygEPo = false;
      bool nMfgXTUBAl = false;
      bool gaqpzELyDn = false;
      bool ZeEZxHprlP = false;
      bool DGMFeOejfA = false;
      bool VifUfZiNog = false;
      bool lhAbPIIGiP = false;
      bool ccOkhZOkKj = false;
      bool ZbRCSpyjsX = false;
      bool YbDFcUGjpV = false;
      bool GYAQXsUulF = false;
      bool KxDEGJQxIZ = false;
      bool KXMLpAZJHN = false;
      bool TduodAbAeZ = false;
      bool UDymMbYyyT = false;
      bool EIaQLiLoZW = false;
      bool SLnXlfCNaG = false;
      bool hPSiEHYZyO = false;
      bool aaKnIKCddt = false;
      string OCbEaATVkc;
      string lAJleUzXlC;
      string HAehlihcBq;
      string abeMmmjxCX;
      string kdsVzBsmke;
      string COAlxNXtSq;
      string RqUsBJUxzr;
      string jCVORcHJhj;
      string puqVoLbrPY;
      string PpdKFsIzTo;
      string gumsuzslUT;
      string GOLhBVAzEo;
      string hbhacsXKIY;
      string THosDuHxZo;
      string SoXuRAduJi;
      string sJudGEMMQB;
      string ahduzzYSeF;
      string OCYOWsDmIb;
      string PcBYeKLLmy;
      string htgXNjLcuS;
      if(OCbEaATVkc == gumsuzslUT){bKQDUqjgGN = true;}
      else if(gumsuzslUT == OCbEaATVkc){YbDFcUGjpV = true;}
      if(lAJleUzXlC == GOLhBVAzEo){BZEolygEPo = true;}
      else if(GOLhBVAzEo == lAJleUzXlC){GYAQXsUulF = true;}
      if(HAehlihcBq == hbhacsXKIY){nMfgXTUBAl = true;}
      else if(hbhacsXKIY == HAehlihcBq){KxDEGJQxIZ = true;}
      if(abeMmmjxCX == THosDuHxZo){gaqpzELyDn = true;}
      else if(THosDuHxZo == abeMmmjxCX){KXMLpAZJHN = true;}
      if(kdsVzBsmke == SoXuRAduJi){ZeEZxHprlP = true;}
      else if(SoXuRAduJi == kdsVzBsmke){TduodAbAeZ = true;}
      if(COAlxNXtSq == sJudGEMMQB){DGMFeOejfA = true;}
      else if(sJudGEMMQB == COAlxNXtSq){UDymMbYyyT = true;}
      if(RqUsBJUxzr == ahduzzYSeF){VifUfZiNog = true;}
      else if(ahduzzYSeF == RqUsBJUxzr){EIaQLiLoZW = true;}
      if(jCVORcHJhj == OCYOWsDmIb){lhAbPIIGiP = true;}
      if(puqVoLbrPY == PcBYeKLLmy){ccOkhZOkKj = true;}
      if(PpdKFsIzTo == htgXNjLcuS){ZbRCSpyjsX = true;}
      while(OCYOWsDmIb == jCVORcHJhj){SLnXlfCNaG = true;}
      while(PcBYeKLLmy == PcBYeKLLmy){hPSiEHYZyO = true;}
      while(htgXNjLcuS == htgXNjLcuS){aaKnIKCddt = true;}
      if(bKQDUqjgGN == true){bKQDUqjgGN = false;}
      if(BZEolygEPo == true){BZEolygEPo = false;}
      if(nMfgXTUBAl == true){nMfgXTUBAl = false;}
      if(gaqpzELyDn == true){gaqpzELyDn = false;}
      if(ZeEZxHprlP == true){ZeEZxHprlP = false;}
      if(DGMFeOejfA == true){DGMFeOejfA = false;}
      if(VifUfZiNog == true){VifUfZiNog = false;}
      if(lhAbPIIGiP == true){lhAbPIIGiP = false;}
      if(ccOkhZOkKj == true){ccOkhZOkKj = false;}
      if(ZbRCSpyjsX == true){ZbRCSpyjsX = false;}
      if(YbDFcUGjpV == true){YbDFcUGjpV = false;}
      if(GYAQXsUulF == true){GYAQXsUulF = false;}
      if(KxDEGJQxIZ == true){KxDEGJQxIZ = false;}
      if(KXMLpAZJHN == true){KXMLpAZJHN = false;}
      if(TduodAbAeZ == true){TduodAbAeZ = false;}
      if(UDymMbYyyT == true){UDymMbYyyT = false;}
      if(EIaQLiLoZW == true){EIaQLiLoZW = false;}
      if(SLnXlfCNaG == true){SLnXlfCNaG = false;}
      if(hPSiEHYZyO == true){hPSiEHYZyO = false;}
      if(aaKnIKCddt == true){aaKnIKCddt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EZKQUQUEVW
{ 
  void zHZBSgLsXU()
  { 
      bool RHfyPDfmAp = false;
      bool UUcUAXHjwy = false;
      bool VnuKpktJYC = false;
      bool RQlsrAlPeB = false;
      bool nftqCHNzqo = false;
      bool LjKGScMUHe = false;
      bool IWNxXDijbz = false;
      bool krFtJosEHi = false;
      bool XtRiqhGeZO = false;
      bool nQHzsRRxSy = false;
      bool XcWrDTdPwc = false;
      bool jINYGNEdFo = false;
      bool xDJNKUjFBr = false;
      bool XukJKtXYfX = false;
      bool DphxdfDire = false;
      bool MmqcAUTIgi = false;
      bool iYODFnWDNM = false;
      bool peyhlHVLie = false;
      bool QBMVfjEHIp = false;
      bool ZOrwoeadrp = false;
      string idGVKBrdHk;
      string lZDWPBtmOj;
      string brdsfrHpXp;
      string miKxCCkBmL;
      string gpheSofnCT;
      string OzTbFqzNoR;
      string tBGRyCPGUN;
      string QrzDDkJyaq;
      string MTnDanPhrK;
      string CWMVRfjQgP;
      string ZZToCWzQYT;
      string hBmyEaNCpK;
      string lgOJKsfdkX;
      string BsRKQmzyBE;
      string nzIXcBjNQq;
      string RgZWcsLJdJ;
      string pUeBSnibhR;
      string aOBlVmXpgJ;
      string ISNtFTSugX;
      string bpTrNSUHEn;
      if(idGVKBrdHk == ZZToCWzQYT){RHfyPDfmAp = true;}
      else if(ZZToCWzQYT == idGVKBrdHk){XcWrDTdPwc = true;}
      if(lZDWPBtmOj == hBmyEaNCpK){UUcUAXHjwy = true;}
      else if(hBmyEaNCpK == lZDWPBtmOj){jINYGNEdFo = true;}
      if(brdsfrHpXp == lgOJKsfdkX){VnuKpktJYC = true;}
      else if(lgOJKsfdkX == brdsfrHpXp){xDJNKUjFBr = true;}
      if(miKxCCkBmL == BsRKQmzyBE){RQlsrAlPeB = true;}
      else if(BsRKQmzyBE == miKxCCkBmL){XukJKtXYfX = true;}
      if(gpheSofnCT == nzIXcBjNQq){nftqCHNzqo = true;}
      else if(nzIXcBjNQq == gpheSofnCT){DphxdfDire = true;}
      if(OzTbFqzNoR == RgZWcsLJdJ){LjKGScMUHe = true;}
      else if(RgZWcsLJdJ == OzTbFqzNoR){MmqcAUTIgi = true;}
      if(tBGRyCPGUN == pUeBSnibhR){IWNxXDijbz = true;}
      else if(pUeBSnibhR == tBGRyCPGUN){iYODFnWDNM = true;}
      if(QrzDDkJyaq == aOBlVmXpgJ){krFtJosEHi = true;}
      if(MTnDanPhrK == ISNtFTSugX){XtRiqhGeZO = true;}
      if(CWMVRfjQgP == bpTrNSUHEn){nQHzsRRxSy = true;}
      while(aOBlVmXpgJ == QrzDDkJyaq){peyhlHVLie = true;}
      while(ISNtFTSugX == ISNtFTSugX){QBMVfjEHIp = true;}
      while(bpTrNSUHEn == bpTrNSUHEn){ZOrwoeadrp = true;}
      if(RHfyPDfmAp == true){RHfyPDfmAp = false;}
      if(UUcUAXHjwy == true){UUcUAXHjwy = false;}
      if(VnuKpktJYC == true){VnuKpktJYC = false;}
      if(RQlsrAlPeB == true){RQlsrAlPeB = false;}
      if(nftqCHNzqo == true){nftqCHNzqo = false;}
      if(LjKGScMUHe == true){LjKGScMUHe = false;}
      if(IWNxXDijbz == true){IWNxXDijbz = false;}
      if(krFtJosEHi == true){krFtJosEHi = false;}
      if(XtRiqhGeZO == true){XtRiqhGeZO = false;}
      if(nQHzsRRxSy == true){nQHzsRRxSy = false;}
      if(XcWrDTdPwc == true){XcWrDTdPwc = false;}
      if(jINYGNEdFo == true){jINYGNEdFo = false;}
      if(xDJNKUjFBr == true){xDJNKUjFBr = false;}
      if(XukJKtXYfX == true){XukJKtXYfX = false;}
      if(DphxdfDire == true){DphxdfDire = false;}
      if(MmqcAUTIgi == true){MmqcAUTIgi = false;}
      if(iYODFnWDNM == true){iYODFnWDNM = false;}
      if(peyhlHVLie == true){peyhlHVLie = false;}
      if(QBMVfjEHIp == true){QBMVfjEHIp = false;}
      if(ZOrwoeadrp == true){ZOrwoeadrp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TVZZPTERYV
{ 
  void EOgMrEfPTF()
  { 
      bool dzqYwtRPTs = false;
      bool bUbNReOTjG = false;
      bool nyzUUVzEZq = false;
      bool NafyjziKbK = false;
      bool UpRxWljFTV = false;
      bool TxskhfAWEa = false;
      bool uMocfBocdS = false;
      bool wDrYlxgByh = false;
      bool kskEWPgtQD = false;
      bool yMFAPHAoQU = false;
      bool xHbAYQEUzj = false;
      bool zyYVoBbkFP = false;
      bool UtMZTjxqJe = false;
      bool wqkckdRjeG = false;
      bool LLugEzmjKN = false;
      bool ePiBACtCgo = false;
      bool SMLTmHNwjL = false;
      bool jrGzEIyeUT = false;
      bool wNfuzgIjci = false;
      bool iPDonyAbsx = false;
      string wtPZbtclUg;
      string ThrPiFmWZk;
      string pfziqtOOol;
      string LZgHXZYrJB;
      string pwIUHGoYNj;
      string lwTDhPtfig;
      string fOxhUtBkrI;
      string ftNXttXebj;
      string FoAFzPFcZH;
      string esIcUazZzM;
      string FEgFDriuIn;
      string qPEybpNqiF;
      string oYKjcmkjCS;
      string txeOeAIuBH;
      string fJTlPOoKAe;
      string NHqsXgswbP;
      string GyrpstjoSa;
      string hSpaYeEYTO;
      string yajXFlGlpy;
      string GMSkBhRdrV;
      if(wtPZbtclUg == FEgFDriuIn){dzqYwtRPTs = true;}
      else if(FEgFDriuIn == wtPZbtclUg){xHbAYQEUzj = true;}
      if(ThrPiFmWZk == qPEybpNqiF){bUbNReOTjG = true;}
      else if(qPEybpNqiF == ThrPiFmWZk){zyYVoBbkFP = true;}
      if(pfziqtOOol == oYKjcmkjCS){nyzUUVzEZq = true;}
      else if(oYKjcmkjCS == pfziqtOOol){UtMZTjxqJe = true;}
      if(LZgHXZYrJB == txeOeAIuBH){NafyjziKbK = true;}
      else if(txeOeAIuBH == LZgHXZYrJB){wqkckdRjeG = true;}
      if(pwIUHGoYNj == fJTlPOoKAe){UpRxWljFTV = true;}
      else if(fJTlPOoKAe == pwIUHGoYNj){LLugEzmjKN = true;}
      if(lwTDhPtfig == NHqsXgswbP){TxskhfAWEa = true;}
      else if(NHqsXgswbP == lwTDhPtfig){ePiBACtCgo = true;}
      if(fOxhUtBkrI == GyrpstjoSa){uMocfBocdS = true;}
      else if(GyrpstjoSa == fOxhUtBkrI){SMLTmHNwjL = true;}
      if(ftNXttXebj == hSpaYeEYTO){wDrYlxgByh = true;}
      if(FoAFzPFcZH == yajXFlGlpy){kskEWPgtQD = true;}
      if(esIcUazZzM == GMSkBhRdrV){yMFAPHAoQU = true;}
      while(hSpaYeEYTO == ftNXttXebj){jrGzEIyeUT = true;}
      while(yajXFlGlpy == yajXFlGlpy){wNfuzgIjci = true;}
      while(GMSkBhRdrV == GMSkBhRdrV){iPDonyAbsx = true;}
      if(dzqYwtRPTs == true){dzqYwtRPTs = false;}
      if(bUbNReOTjG == true){bUbNReOTjG = false;}
      if(nyzUUVzEZq == true){nyzUUVzEZq = false;}
      if(NafyjziKbK == true){NafyjziKbK = false;}
      if(UpRxWljFTV == true){UpRxWljFTV = false;}
      if(TxskhfAWEa == true){TxskhfAWEa = false;}
      if(uMocfBocdS == true){uMocfBocdS = false;}
      if(wDrYlxgByh == true){wDrYlxgByh = false;}
      if(kskEWPgtQD == true){kskEWPgtQD = false;}
      if(yMFAPHAoQU == true){yMFAPHAoQU = false;}
      if(xHbAYQEUzj == true){xHbAYQEUzj = false;}
      if(zyYVoBbkFP == true){zyYVoBbkFP = false;}
      if(UtMZTjxqJe == true){UtMZTjxqJe = false;}
      if(wqkckdRjeG == true){wqkckdRjeG = false;}
      if(LLugEzmjKN == true){LLugEzmjKN = false;}
      if(ePiBACtCgo == true){ePiBACtCgo = false;}
      if(SMLTmHNwjL == true){SMLTmHNwjL = false;}
      if(jrGzEIyeUT == true){jrGzEIyeUT = false;}
      if(wNfuzgIjci == true){wNfuzgIjci = false;}
      if(iPDonyAbsx == true){iPDonyAbsx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHOGBPURRS
{ 
  void GNIDdcRRpF()
  { 
      bool tUMOnuBjdN = false;
      bool VBucBKpGBr = false;
      bool yCqxHFnyeF = false;
      bool TRSJMEscwz = false;
      bool sObhIwuPlQ = false;
      bool BhdKWrdOGi = false;
      bool GDFXtDikQx = false;
      bool RNJCziZIoL = false;
      bool JYMNEknHmT = false;
      bool adVMroJEnE = false;
      bool NKyozmXaLm = false;
      bool SVZuZhpqTJ = false;
      bool PaywVmrxJJ = false;
      bool ZVTkyzZXNQ = false;
      bool MMwzBFEZmK = false;
      bool yRjenlMCSL = false;
      bool uaRBNwBoxZ = false;
      bool HSdCwDeytP = false;
      bool hRJzKHkowL = false;
      bool mXEBVlutlE = false;
      string pKzYpQAGXT;
      string HwfadqnfUa;
      string pXgRGLOUeV;
      string YaZHXYufYA;
      string RRrwpPHZyF;
      string SChduScgRd;
      string CeaBugVYCF;
      string wIHUJYfkbq;
      string DnVYCVswMF;
      string uNOtylppBJ;
      string siXsJKuNTV;
      string mrFZZNJBzY;
      string mZLxJhtMVX;
      string ioiRyUQbPr;
      string afbpRDInUk;
      string cnqcVTWZjb;
      string QiqwmxImbF;
      string wglGyHxVeG;
      string ZFrkutyGwd;
      string xqrnbrneDU;
      if(pKzYpQAGXT == siXsJKuNTV){tUMOnuBjdN = true;}
      else if(siXsJKuNTV == pKzYpQAGXT){NKyozmXaLm = true;}
      if(HwfadqnfUa == mrFZZNJBzY){VBucBKpGBr = true;}
      else if(mrFZZNJBzY == HwfadqnfUa){SVZuZhpqTJ = true;}
      if(pXgRGLOUeV == mZLxJhtMVX){yCqxHFnyeF = true;}
      else if(mZLxJhtMVX == pXgRGLOUeV){PaywVmrxJJ = true;}
      if(YaZHXYufYA == ioiRyUQbPr){TRSJMEscwz = true;}
      else if(ioiRyUQbPr == YaZHXYufYA){ZVTkyzZXNQ = true;}
      if(RRrwpPHZyF == afbpRDInUk){sObhIwuPlQ = true;}
      else if(afbpRDInUk == RRrwpPHZyF){MMwzBFEZmK = true;}
      if(SChduScgRd == cnqcVTWZjb){BhdKWrdOGi = true;}
      else if(cnqcVTWZjb == SChduScgRd){yRjenlMCSL = true;}
      if(CeaBugVYCF == QiqwmxImbF){GDFXtDikQx = true;}
      else if(QiqwmxImbF == CeaBugVYCF){uaRBNwBoxZ = true;}
      if(wIHUJYfkbq == wglGyHxVeG){RNJCziZIoL = true;}
      if(DnVYCVswMF == ZFrkutyGwd){JYMNEknHmT = true;}
      if(uNOtylppBJ == xqrnbrneDU){adVMroJEnE = true;}
      while(wglGyHxVeG == wIHUJYfkbq){HSdCwDeytP = true;}
      while(ZFrkutyGwd == ZFrkutyGwd){hRJzKHkowL = true;}
      while(xqrnbrneDU == xqrnbrneDU){mXEBVlutlE = true;}
      if(tUMOnuBjdN == true){tUMOnuBjdN = false;}
      if(VBucBKpGBr == true){VBucBKpGBr = false;}
      if(yCqxHFnyeF == true){yCqxHFnyeF = false;}
      if(TRSJMEscwz == true){TRSJMEscwz = false;}
      if(sObhIwuPlQ == true){sObhIwuPlQ = false;}
      if(BhdKWrdOGi == true){BhdKWrdOGi = false;}
      if(GDFXtDikQx == true){GDFXtDikQx = false;}
      if(RNJCziZIoL == true){RNJCziZIoL = false;}
      if(JYMNEknHmT == true){JYMNEknHmT = false;}
      if(adVMroJEnE == true){adVMroJEnE = false;}
      if(NKyozmXaLm == true){NKyozmXaLm = false;}
      if(SVZuZhpqTJ == true){SVZuZhpqTJ = false;}
      if(PaywVmrxJJ == true){PaywVmrxJJ = false;}
      if(ZVTkyzZXNQ == true){ZVTkyzZXNQ = false;}
      if(MMwzBFEZmK == true){MMwzBFEZmK = false;}
      if(yRjenlMCSL == true){yRjenlMCSL = false;}
      if(uaRBNwBoxZ == true){uaRBNwBoxZ = false;}
      if(HSdCwDeytP == true){HSdCwDeytP = false;}
      if(hRJzKHkowL == true){hRJzKHkowL = false;}
      if(mXEBVlutlE == true){mXEBVlutlE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WSJURJUSTD
{ 
  void IzyNVhmIxr()
  { 
      bool TaVGiVTwTL = false;
      bool gdRndNwdCn = false;
      bool QpJgcKmFyw = false;
      bool CZEasXUEFO = false;
      bool gaKqECrjLU = false;
      bool jOJkwdRocX = false;
      bool hNyXIHZptF = false;
      bool srXnHofRbZ = false;
      bool SCtcMmPTdP = false;
      bool GfahfSclhx = false;
      bool cBoFbqpVcH = false;
      bool xzMCFeTULV = false;
      bool rFMezMQpHo = false;
      bool LsjexQMoBU = false;
      bool wsqWRHTXcB = false;
      bool yIaMFWoKFO = false;
      bool aAOnuEOhFn = false;
      bool ReTpYyOpMr = false;
      bool srNFpDSWZZ = false;
      bool aCiltweCaN = false;
      string qVBwwgkdGe;
      string qsbPFpuxUZ;
      string MylKLFkTkJ;
      string sOAPiTyzHl;
      string lUxxnzNaoF;
      string iYstwrjqkq;
      string wQsxkbsMfl;
      string rwpinqBnVL;
      string qKdfaUVGTq;
      string jGOPpUbzMM;
      string GBtDNlhKGE;
      string puUYzkmNVP;
      string GlsoBkgarS;
      string PBaJFoPaRn;
      string mKAOBnloPE;
      string hOdwGTIFBc;
      string FGRmonULTJ;
      string VMugculdnN;
      string yqKnjAXdCl;
      string gKYoifrMYM;
      if(qVBwwgkdGe == GBtDNlhKGE){TaVGiVTwTL = true;}
      else if(GBtDNlhKGE == qVBwwgkdGe){cBoFbqpVcH = true;}
      if(qsbPFpuxUZ == puUYzkmNVP){gdRndNwdCn = true;}
      else if(puUYzkmNVP == qsbPFpuxUZ){xzMCFeTULV = true;}
      if(MylKLFkTkJ == GlsoBkgarS){QpJgcKmFyw = true;}
      else if(GlsoBkgarS == MylKLFkTkJ){rFMezMQpHo = true;}
      if(sOAPiTyzHl == PBaJFoPaRn){CZEasXUEFO = true;}
      else if(PBaJFoPaRn == sOAPiTyzHl){LsjexQMoBU = true;}
      if(lUxxnzNaoF == mKAOBnloPE){gaKqECrjLU = true;}
      else if(mKAOBnloPE == lUxxnzNaoF){wsqWRHTXcB = true;}
      if(iYstwrjqkq == hOdwGTIFBc){jOJkwdRocX = true;}
      else if(hOdwGTIFBc == iYstwrjqkq){yIaMFWoKFO = true;}
      if(wQsxkbsMfl == FGRmonULTJ){hNyXIHZptF = true;}
      else if(FGRmonULTJ == wQsxkbsMfl){aAOnuEOhFn = true;}
      if(rwpinqBnVL == VMugculdnN){srXnHofRbZ = true;}
      if(qKdfaUVGTq == yqKnjAXdCl){SCtcMmPTdP = true;}
      if(jGOPpUbzMM == gKYoifrMYM){GfahfSclhx = true;}
      while(VMugculdnN == rwpinqBnVL){ReTpYyOpMr = true;}
      while(yqKnjAXdCl == yqKnjAXdCl){srNFpDSWZZ = true;}
      while(gKYoifrMYM == gKYoifrMYM){aCiltweCaN = true;}
      if(TaVGiVTwTL == true){TaVGiVTwTL = false;}
      if(gdRndNwdCn == true){gdRndNwdCn = false;}
      if(QpJgcKmFyw == true){QpJgcKmFyw = false;}
      if(CZEasXUEFO == true){CZEasXUEFO = false;}
      if(gaKqECrjLU == true){gaKqECrjLU = false;}
      if(jOJkwdRocX == true){jOJkwdRocX = false;}
      if(hNyXIHZptF == true){hNyXIHZptF = false;}
      if(srXnHofRbZ == true){srXnHofRbZ = false;}
      if(SCtcMmPTdP == true){SCtcMmPTdP = false;}
      if(GfahfSclhx == true){GfahfSclhx = false;}
      if(cBoFbqpVcH == true){cBoFbqpVcH = false;}
      if(xzMCFeTULV == true){xzMCFeTULV = false;}
      if(rFMezMQpHo == true){rFMezMQpHo = false;}
      if(LsjexQMoBU == true){LsjexQMoBU = false;}
      if(wsqWRHTXcB == true){wsqWRHTXcB = false;}
      if(yIaMFWoKFO == true){yIaMFWoKFO = false;}
      if(aAOnuEOhFn == true){aAOnuEOhFn = false;}
      if(ReTpYyOpMr == true){ReTpYyOpMr = false;}
      if(srNFpDSWZZ == true){srNFpDSWZZ = false;}
      if(aCiltweCaN == true){aCiltweCaN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XJDLFDSOJX
{ 
  void DtwzlHQsmP()
  { 
      bool YJtfJoYxJm = false;
      bool tZBedtQLgK = false;
      bool mPSrDXkfTI = false;
      bool lupVFmLdME = false;
      bool CcHGDItdMY = false;
      bool xyTIhIqCcl = false;
      bool DrdBByifYp = false;
      bool imzbHKIMou = false;
      bool cHStLmbhnw = false;
      bool wJBZAJzGFE = false;
      bool YNEVpKyqAW = false;
      bool AeMgIwZioN = false;
      bool WBrbtZkZay = false;
      bool LBGjVOCwEB = false;
      bool ojgQwRwTRE = false;
      bool iPQqhXVbbP = false;
      bool YYQCKyXcLs = false;
      bool scdnXmTafc = false;
      bool dRHWOukOCy = false;
      bool saUobQTeFx = false;
      string AHbBIgrjcD;
      string LECaZaDrrk;
      string rUmmTnOXiI;
      string yuCbpFyxqF;
      string OkOxmQYENW;
      string xEUYOfUnhT;
      string SUBTFPBajU;
      string cGAlVGGoAD;
      string PJJLLsadMJ;
      string kJPWmsjtrX;
      string OxTrtqEhCH;
      string ZeneEJKoIL;
      string oXNajSpczb;
      string WLxbnRoQRU;
      string oraEiFVkSd;
      string iukfiqisIa;
      string AahZkNgLpl;
      string TsWnWwwJqd;
      string xFKVsaZRsx;
      string hwIqTNKASV;
      if(AHbBIgrjcD == OxTrtqEhCH){YJtfJoYxJm = true;}
      else if(OxTrtqEhCH == AHbBIgrjcD){YNEVpKyqAW = true;}
      if(LECaZaDrrk == ZeneEJKoIL){tZBedtQLgK = true;}
      else if(ZeneEJKoIL == LECaZaDrrk){AeMgIwZioN = true;}
      if(rUmmTnOXiI == oXNajSpczb){mPSrDXkfTI = true;}
      else if(oXNajSpczb == rUmmTnOXiI){WBrbtZkZay = true;}
      if(yuCbpFyxqF == WLxbnRoQRU){lupVFmLdME = true;}
      else if(WLxbnRoQRU == yuCbpFyxqF){LBGjVOCwEB = true;}
      if(OkOxmQYENW == oraEiFVkSd){CcHGDItdMY = true;}
      else if(oraEiFVkSd == OkOxmQYENW){ojgQwRwTRE = true;}
      if(xEUYOfUnhT == iukfiqisIa){xyTIhIqCcl = true;}
      else if(iukfiqisIa == xEUYOfUnhT){iPQqhXVbbP = true;}
      if(SUBTFPBajU == AahZkNgLpl){DrdBByifYp = true;}
      else if(AahZkNgLpl == SUBTFPBajU){YYQCKyXcLs = true;}
      if(cGAlVGGoAD == TsWnWwwJqd){imzbHKIMou = true;}
      if(PJJLLsadMJ == xFKVsaZRsx){cHStLmbhnw = true;}
      if(kJPWmsjtrX == hwIqTNKASV){wJBZAJzGFE = true;}
      while(TsWnWwwJqd == cGAlVGGoAD){scdnXmTafc = true;}
      while(xFKVsaZRsx == xFKVsaZRsx){dRHWOukOCy = true;}
      while(hwIqTNKASV == hwIqTNKASV){saUobQTeFx = true;}
      if(YJtfJoYxJm == true){YJtfJoYxJm = false;}
      if(tZBedtQLgK == true){tZBedtQLgK = false;}
      if(mPSrDXkfTI == true){mPSrDXkfTI = false;}
      if(lupVFmLdME == true){lupVFmLdME = false;}
      if(CcHGDItdMY == true){CcHGDItdMY = false;}
      if(xyTIhIqCcl == true){xyTIhIqCcl = false;}
      if(DrdBByifYp == true){DrdBByifYp = false;}
      if(imzbHKIMou == true){imzbHKIMou = false;}
      if(cHStLmbhnw == true){cHStLmbhnw = false;}
      if(wJBZAJzGFE == true){wJBZAJzGFE = false;}
      if(YNEVpKyqAW == true){YNEVpKyqAW = false;}
      if(AeMgIwZioN == true){AeMgIwZioN = false;}
      if(WBrbtZkZay == true){WBrbtZkZay = false;}
      if(LBGjVOCwEB == true){LBGjVOCwEB = false;}
      if(ojgQwRwTRE == true){ojgQwRwTRE = false;}
      if(iPQqhXVbbP == true){iPQqhXVbbP = false;}
      if(YYQCKyXcLs == true){YYQCKyXcLs = false;}
      if(scdnXmTafc == true){scdnXmTafc = false;}
      if(dRHWOukOCy == true){dRHWOukOCy = false;}
      if(saUobQTeFx == true){saUobQTeFx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CTIAQQEUFN
{ 
  void EGxdmIgagG()
  { 
      bool MIdkRfBzHi = false;
      bool FaXwHQQGKu = false;
      bool oCDxwWjbhU = false;
      bool pnNUsFnICa = false;
      bool CZdXpsJqHY = false;
      bool LBpieJEgot = false;
      bool uZQlsRMCDC = false;
      bool bHDjrPYfGC = false;
      bool NsUJJnxeoi = false;
      bool AHTIfbJqdY = false;
      bool fGmEwExGpP = false;
      bool kYalgBFGcE = false;
      bool UhMTBUnuEP = false;
      bool GgCgVGFPNF = false;
      bool qqoYybggad = false;
      bool WCNYEysTDa = false;
      bool PBBZJDVsPZ = false;
      bool wosXNcsmVZ = false;
      bool nGUarDSccX = false;
      bool MlMloooOPt = false;
      string JVDjjSCRSm;
      string IGnnkZlmME;
      string MhFzEGlrxW;
      string GaBsUxXniB;
      string bqQWuIgFuG;
      string XLbESbPDfc;
      string gKTwfgFuSm;
      string CyDKbUQiDu;
      string Ygxpyuzwas;
      string gTIGURWUqO;
      string DllHEZHQcx;
      string KfAjDzNdxk;
      string gIUYGhpxpK;
      string ywroqluolY;
      string miTciATXCV;
      string DsWFhuRNBW;
      string iKaRzNnKsQ;
      string EXqXxyoqpF;
      string OStTGEYlHw;
      string UgmPobHBdU;
      if(JVDjjSCRSm == DllHEZHQcx){MIdkRfBzHi = true;}
      else if(DllHEZHQcx == JVDjjSCRSm){fGmEwExGpP = true;}
      if(IGnnkZlmME == KfAjDzNdxk){FaXwHQQGKu = true;}
      else if(KfAjDzNdxk == IGnnkZlmME){kYalgBFGcE = true;}
      if(MhFzEGlrxW == gIUYGhpxpK){oCDxwWjbhU = true;}
      else if(gIUYGhpxpK == MhFzEGlrxW){UhMTBUnuEP = true;}
      if(GaBsUxXniB == ywroqluolY){pnNUsFnICa = true;}
      else if(ywroqluolY == GaBsUxXniB){GgCgVGFPNF = true;}
      if(bqQWuIgFuG == miTciATXCV){CZdXpsJqHY = true;}
      else if(miTciATXCV == bqQWuIgFuG){qqoYybggad = true;}
      if(XLbESbPDfc == DsWFhuRNBW){LBpieJEgot = true;}
      else if(DsWFhuRNBW == XLbESbPDfc){WCNYEysTDa = true;}
      if(gKTwfgFuSm == iKaRzNnKsQ){uZQlsRMCDC = true;}
      else if(iKaRzNnKsQ == gKTwfgFuSm){PBBZJDVsPZ = true;}
      if(CyDKbUQiDu == EXqXxyoqpF){bHDjrPYfGC = true;}
      if(Ygxpyuzwas == OStTGEYlHw){NsUJJnxeoi = true;}
      if(gTIGURWUqO == UgmPobHBdU){AHTIfbJqdY = true;}
      while(EXqXxyoqpF == CyDKbUQiDu){wosXNcsmVZ = true;}
      while(OStTGEYlHw == OStTGEYlHw){nGUarDSccX = true;}
      while(UgmPobHBdU == UgmPobHBdU){MlMloooOPt = true;}
      if(MIdkRfBzHi == true){MIdkRfBzHi = false;}
      if(FaXwHQQGKu == true){FaXwHQQGKu = false;}
      if(oCDxwWjbhU == true){oCDxwWjbhU = false;}
      if(pnNUsFnICa == true){pnNUsFnICa = false;}
      if(CZdXpsJqHY == true){CZdXpsJqHY = false;}
      if(LBpieJEgot == true){LBpieJEgot = false;}
      if(uZQlsRMCDC == true){uZQlsRMCDC = false;}
      if(bHDjrPYfGC == true){bHDjrPYfGC = false;}
      if(NsUJJnxeoi == true){NsUJJnxeoi = false;}
      if(AHTIfbJqdY == true){AHTIfbJqdY = false;}
      if(fGmEwExGpP == true){fGmEwExGpP = false;}
      if(kYalgBFGcE == true){kYalgBFGcE = false;}
      if(UhMTBUnuEP == true){UhMTBUnuEP = false;}
      if(GgCgVGFPNF == true){GgCgVGFPNF = false;}
      if(qqoYybggad == true){qqoYybggad = false;}
      if(WCNYEysTDa == true){WCNYEysTDa = false;}
      if(PBBZJDVsPZ == true){PBBZJDVsPZ = false;}
      if(wosXNcsmVZ == true){wosXNcsmVZ = false;}
      if(nGUarDSccX == true){nGUarDSccX = false;}
      if(MlMloooOPt == true){MlMloooOPt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EODIPCXWQL
{ 
  void HQfRtchaka()
  { 
      bool nAEjuCntOA = false;
      bool RkHZOdklra = false;
      bool SeOAQbziqe = false;
      bool THijJFqMfM = false;
      bool EseoqMQjzm = false;
      bool lTXSbJlDTS = false;
      bool CEDjgJCXQI = false;
      bool mYFeVYAYJD = false;
      bool LPjDrAiQHA = false;
      bool TmrMKAptIg = false;
      bool KrTpAMNswC = false;
      bool IMtPHmTzqg = false;
      bool ZkPPozfrUV = false;
      bool iFPcsSusDf = false;
      bool lpTEqGscFW = false;
      bool fpDbGYbEAA = false;
      bool fUXaTDxQWn = false;
      bool qauLtjRLXi = false;
      bool GDmxorBnVT = false;
      bool qqrDzQRskn = false;
      string IcDHePgcRp;
      string RXRJdQnEeE;
      string MVHzSgYRfp;
      string uUWLiTeJcz;
      string VOdVPkMtwR;
      string OIQQxmVEny;
      string qPwbuxBFaK;
      string kdbfhyqkih;
      string UeVOblEFNu;
      string xZUdIGSCZS;
      string jGSlfjfkiz;
      string ujUGdMtgzI;
      string ruqfMKJxWb;
      string eoKQxNLjiq;
      string GSWOANENAw;
      string MlCRZoOmYU;
      string ZhNHUFYEJP;
      string AKxICYXcey;
      string FwxaOsmspI;
      string yYKNRXFPtt;
      if(IcDHePgcRp == jGSlfjfkiz){nAEjuCntOA = true;}
      else if(jGSlfjfkiz == IcDHePgcRp){KrTpAMNswC = true;}
      if(RXRJdQnEeE == ujUGdMtgzI){RkHZOdklra = true;}
      else if(ujUGdMtgzI == RXRJdQnEeE){IMtPHmTzqg = true;}
      if(MVHzSgYRfp == ruqfMKJxWb){SeOAQbziqe = true;}
      else if(ruqfMKJxWb == MVHzSgYRfp){ZkPPozfrUV = true;}
      if(uUWLiTeJcz == eoKQxNLjiq){THijJFqMfM = true;}
      else if(eoKQxNLjiq == uUWLiTeJcz){iFPcsSusDf = true;}
      if(VOdVPkMtwR == GSWOANENAw){EseoqMQjzm = true;}
      else if(GSWOANENAw == VOdVPkMtwR){lpTEqGscFW = true;}
      if(OIQQxmVEny == MlCRZoOmYU){lTXSbJlDTS = true;}
      else if(MlCRZoOmYU == OIQQxmVEny){fpDbGYbEAA = true;}
      if(qPwbuxBFaK == ZhNHUFYEJP){CEDjgJCXQI = true;}
      else if(ZhNHUFYEJP == qPwbuxBFaK){fUXaTDxQWn = true;}
      if(kdbfhyqkih == AKxICYXcey){mYFeVYAYJD = true;}
      if(UeVOblEFNu == FwxaOsmspI){LPjDrAiQHA = true;}
      if(xZUdIGSCZS == yYKNRXFPtt){TmrMKAptIg = true;}
      while(AKxICYXcey == kdbfhyqkih){qauLtjRLXi = true;}
      while(FwxaOsmspI == FwxaOsmspI){GDmxorBnVT = true;}
      while(yYKNRXFPtt == yYKNRXFPtt){qqrDzQRskn = true;}
      if(nAEjuCntOA == true){nAEjuCntOA = false;}
      if(RkHZOdklra == true){RkHZOdklra = false;}
      if(SeOAQbziqe == true){SeOAQbziqe = false;}
      if(THijJFqMfM == true){THijJFqMfM = false;}
      if(EseoqMQjzm == true){EseoqMQjzm = false;}
      if(lTXSbJlDTS == true){lTXSbJlDTS = false;}
      if(CEDjgJCXQI == true){CEDjgJCXQI = false;}
      if(mYFeVYAYJD == true){mYFeVYAYJD = false;}
      if(LPjDrAiQHA == true){LPjDrAiQHA = false;}
      if(TmrMKAptIg == true){TmrMKAptIg = false;}
      if(KrTpAMNswC == true){KrTpAMNswC = false;}
      if(IMtPHmTzqg == true){IMtPHmTzqg = false;}
      if(ZkPPozfrUV == true){ZkPPozfrUV = false;}
      if(iFPcsSusDf == true){iFPcsSusDf = false;}
      if(lpTEqGscFW == true){lpTEqGscFW = false;}
      if(fpDbGYbEAA == true){fpDbGYbEAA = false;}
      if(fUXaTDxQWn == true){fUXaTDxQWn = false;}
      if(qauLtjRLXi == true){qauLtjRLXi = false;}
      if(GDmxorBnVT == true){GDmxorBnVT = false;}
      if(qqrDzQRskn == true){qqrDzQRskn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BNWJAZYEXH
{ 
  void nuDkRHtkrf()
  { 
      bool rBhuiSGXix = false;
      bool xxeOrhdmmX = false;
      bool EOdrRLfAgI = false;
      bool NBOZgnAiIE = false;
      bool VxyXhxPEON = false;
      bool iypaKdWpdW = false;
      bool lFqZjwiEgD = false;
      bool gtdhCHPGKU = false;
      bool ubkTZPKnPD = false;
      bool QKFlSPFYnk = false;
      bool NLWLfoTIXC = false;
      bool NQeJaKUXAT = false;
      bool lundmWnrPm = false;
      bool BqSZGjEZmj = false;
      bool uBPNoAfwKH = false;
      bool thYTzSWsXJ = false;
      bool AbskAWyFCq = false;
      bool GtkPYjeaom = false;
      bool qrgHrTSzZm = false;
      bool NLBdjSIdMR = false;
      string OMSxMQUDIp;
      string TWjMbPAtnO;
      string XGsaMKfAsB;
      string eeLgtpIXew;
      string uVuIzHcRne;
      string iMDUqHTqkB;
      string kTKGKoKDRk;
      string HcPrSBKjaE;
      string hOLNSSaqol;
      string WQmcLbLoxK;
      string wZzDXGwLCp;
      string wiPfTVIxnr;
      string OTNeOpomgq;
      string pVmQIHPIoL;
      string VPozonAGIo;
      string SNAFwcMUnh;
      string QIdKAZuzXM;
      string GAHbVyeOoZ;
      string oieqXbVgUe;
      string utTHuMkdzO;
      if(OMSxMQUDIp == wZzDXGwLCp){rBhuiSGXix = true;}
      else if(wZzDXGwLCp == OMSxMQUDIp){NLWLfoTIXC = true;}
      if(TWjMbPAtnO == wiPfTVIxnr){xxeOrhdmmX = true;}
      else if(wiPfTVIxnr == TWjMbPAtnO){NQeJaKUXAT = true;}
      if(XGsaMKfAsB == OTNeOpomgq){EOdrRLfAgI = true;}
      else if(OTNeOpomgq == XGsaMKfAsB){lundmWnrPm = true;}
      if(eeLgtpIXew == pVmQIHPIoL){NBOZgnAiIE = true;}
      else if(pVmQIHPIoL == eeLgtpIXew){BqSZGjEZmj = true;}
      if(uVuIzHcRne == VPozonAGIo){VxyXhxPEON = true;}
      else if(VPozonAGIo == uVuIzHcRne){uBPNoAfwKH = true;}
      if(iMDUqHTqkB == SNAFwcMUnh){iypaKdWpdW = true;}
      else if(SNAFwcMUnh == iMDUqHTqkB){thYTzSWsXJ = true;}
      if(kTKGKoKDRk == QIdKAZuzXM){lFqZjwiEgD = true;}
      else if(QIdKAZuzXM == kTKGKoKDRk){AbskAWyFCq = true;}
      if(HcPrSBKjaE == GAHbVyeOoZ){gtdhCHPGKU = true;}
      if(hOLNSSaqol == oieqXbVgUe){ubkTZPKnPD = true;}
      if(WQmcLbLoxK == utTHuMkdzO){QKFlSPFYnk = true;}
      while(GAHbVyeOoZ == HcPrSBKjaE){GtkPYjeaom = true;}
      while(oieqXbVgUe == oieqXbVgUe){qrgHrTSzZm = true;}
      while(utTHuMkdzO == utTHuMkdzO){NLBdjSIdMR = true;}
      if(rBhuiSGXix == true){rBhuiSGXix = false;}
      if(xxeOrhdmmX == true){xxeOrhdmmX = false;}
      if(EOdrRLfAgI == true){EOdrRLfAgI = false;}
      if(NBOZgnAiIE == true){NBOZgnAiIE = false;}
      if(VxyXhxPEON == true){VxyXhxPEON = false;}
      if(iypaKdWpdW == true){iypaKdWpdW = false;}
      if(lFqZjwiEgD == true){lFqZjwiEgD = false;}
      if(gtdhCHPGKU == true){gtdhCHPGKU = false;}
      if(ubkTZPKnPD == true){ubkTZPKnPD = false;}
      if(QKFlSPFYnk == true){QKFlSPFYnk = false;}
      if(NLWLfoTIXC == true){NLWLfoTIXC = false;}
      if(NQeJaKUXAT == true){NQeJaKUXAT = false;}
      if(lundmWnrPm == true){lundmWnrPm = false;}
      if(BqSZGjEZmj == true){BqSZGjEZmj = false;}
      if(uBPNoAfwKH == true){uBPNoAfwKH = false;}
      if(thYTzSWsXJ == true){thYTzSWsXJ = false;}
      if(AbskAWyFCq == true){AbskAWyFCq = false;}
      if(GtkPYjeaom == true){GtkPYjeaom = false;}
      if(qrgHrTSzZm == true){qrgHrTSzZm = false;}
      if(NLBdjSIdMR == true){NLBdjSIdMR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OUUOEIFCTT
{ 
  void fykwQUSHLm()
  { 
      bool RHVtcnCsxm = false;
      bool mXjQsNdjyk = false;
      bool SKeyszkimV = false;
      bool zqxeTURuLB = false;
      bool LrPKZbMxqS = false;
      bool ThTipGbXBd = false;
      bool CSGbmuaFwX = false;
      bool uhYxZZuUXQ = false;
      bool lnrUCRXNnN = false;
      bool stthyrlnWe = false;
      bool BHASWlJVJP = false;
      bool LGzjqOalYV = false;
      bool WMQieAmpzh = false;
      bool nHxsPdmYxP = false;
      bool HBEYCluJpj = false;
      bool RzOBInqRnV = false;
      bool ySWbaDJGUN = false;
      bool aBoJNUIrfr = false;
      bool FdAOPnrujb = false;
      bool mUkaRoecxy = false;
      string yWYLnADQwQ;
      string ICDHzwLaCn;
      string mflYVkptCr;
      string OSPOkdRqZA;
      string KISEFzRuAN;
      string ozotLSkApC;
      string KIOEBoloVV;
      string dTBCddNgTV;
      string TttoCPdVCS;
      string sQAWoBtNCP;
      string McZdiUylPh;
      string EDfTiQOYBk;
      string KPlCbNTdNb;
      string izeDJpUPFh;
      string RrFTOpjfmY;
      string mVMRFwpXCV;
      string BTYnzFXcKs;
      string wySTTSJRnl;
      string cmpnoNlNxM;
      string AwNjfxSRUJ;
      if(yWYLnADQwQ == McZdiUylPh){RHVtcnCsxm = true;}
      else if(McZdiUylPh == yWYLnADQwQ){BHASWlJVJP = true;}
      if(ICDHzwLaCn == EDfTiQOYBk){mXjQsNdjyk = true;}
      else if(EDfTiQOYBk == ICDHzwLaCn){LGzjqOalYV = true;}
      if(mflYVkptCr == KPlCbNTdNb){SKeyszkimV = true;}
      else if(KPlCbNTdNb == mflYVkptCr){WMQieAmpzh = true;}
      if(OSPOkdRqZA == izeDJpUPFh){zqxeTURuLB = true;}
      else if(izeDJpUPFh == OSPOkdRqZA){nHxsPdmYxP = true;}
      if(KISEFzRuAN == RrFTOpjfmY){LrPKZbMxqS = true;}
      else if(RrFTOpjfmY == KISEFzRuAN){HBEYCluJpj = true;}
      if(ozotLSkApC == mVMRFwpXCV){ThTipGbXBd = true;}
      else if(mVMRFwpXCV == ozotLSkApC){RzOBInqRnV = true;}
      if(KIOEBoloVV == BTYnzFXcKs){CSGbmuaFwX = true;}
      else if(BTYnzFXcKs == KIOEBoloVV){ySWbaDJGUN = true;}
      if(dTBCddNgTV == wySTTSJRnl){uhYxZZuUXQ = true;}
      if(TttoCPdVCS == cmpnoNlNxM){lnrUCRXNnN = true;}
      if(sQAWoBtNCP == AwNjfxSRUJ){stthyrlnWe = true;}
      while(wySTTSJRnl == dTBCddNgTV){aBoJNUIrfr = true;}
      while(cmpnoNlNxM == cmpnoNlNxM){FdAOPnrujb = true;}
      while(AwNjfxSRUJ == AwNjfxSRUJ){mUkaRoecxy = true;}
      if(RHVtcnCsxm == true){RHVtcnCsxm = false;}
      if(mXjQsNdjyk == true){mXjQsNdjyk = false;}
      if(SKeyszkimV == true){SKeyszkimV = false;}
      if(zqxeTURuLB == true){zqxeTURuLB = false;}
      if(LrPKZbMxqS == true){LrPKZbMxqS = false;}
      if(ThTipGbXBd == true){ThTipGbXBd = false;}
      if(CSGbmuaFwX == true){CSGbmuaFwX = false;}
      if(uhYxZZuUXQ == true){uhYxZZuUXQ = false;}
      if(lnrUCRXNnN == true){lnrUCRXNnN = false;}
      if(stthyrlnWe == true){stthyrlnWe = false;}
      if(BHASWlJVJP == true){BHASWlJVJP = false;}
      if(LGzjqOalYV == true){LGzjqOalYV = false;}
      if(WMQieAmpzh == true){WMQieAmpzh = false;}
      if(nHxsPdmYxP == true){nHxsPdmYxP = false;}
      if(HBEYCluJpj == true){HBEYCluJpj = false;}
      if(RzOBInqRnV == true){RzOBInqRnV = false;}
      if(ySWbaDJGUN == true){ySWbaDJGUN = false;}
      if(aBoJNUIrfr == true){aBoJNUIrfr = false;}
      if(FdAOPnrujb == true){FdAOPnrujb = false;}
      if(mUkaRoecxy == true){mUkaRoecxy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HOJIRVICHM
{ 
  void zYhNjCcbBd()
  { 
      bool XHjBFLkWmp = false;
      bool TLdnODStoG = false;
      bool UcGjxKXbpO = false;
      bool cQyhzMcsft = false;
      bool fpXGnrbakg = false;
      bool DamgLtBADt = false;
      bool nJfXMCMunB = false;
      bool ZYOuaeFzuF = false;
      bool ixpIKCdRWE = false;
      bool LcokFWJzsk = false;
      bool efliGdLqGf = false;
      bool oBFyLqSWNK = false;
      bool YuYjpxidoE = false;
      bool UFFJZCKGCf = false;
      bool qlKpPKXqZO = false;
      bool DmliMjHCsJ = false;
      bool thBCLiuuYJ = false;
      bool fMUgSljhTe = false;
      bool ZrEZAhTWxp = false;
      bool tIMrkJjIef = false;
      string cbWrGVGGlU;
      string OYjWuyrIZy;
      string ryfFZGgctz;
      string HZiWkdSKGc;
      string lmNFdVIJJu;
      string oNjLIdwRSA;
      string ocMlNopMkQ;
      string fhCwMFkZaD;
      string xXSzJtoXOH;
      string hArFnIaaqo;
      string fwXsOHKnzC;
      string rVpOCRKMcT;
      string zSydiepxHD;
      string eKhlWBzYjC;
      string iBXLOLKcCW;
      string xNxXoNxsKi;
      string QMfuXhnDrB;
      string RlbajytlOW;
      string UNtkFQMKxI;
      string DGOAkVUcng;
      if(cbWrGVGGlU == fwXsOHKnzC){XHjBFLkWmp = true;}
      else if(fwXsOHKnzC == cbWrGVGGlU){efliGdLqGf = true;}
      if(OYjWuyrIZy == rVpOCRKMcT){TLdnODStoG = true;}
      else if(rVpOCRKMcT == OYjWuyrIZy){oBFyLqSWNK = true;}
      if(ryfFZGgctz == zSydiepxHD){UcGjxKXbpO = true;}
      else if(zSydiepxHD == ryfFZGgctz){YuYjpxidoE = true;}
      if(HZiWkdSKGc == eKhlWBzYjC){cQyhzMcsft = true;}
      else if(eKhlWBzYjC == HZiWkdSKGc){UFFJZCKGCf = true;}
      if(lmNFdVIJJu == iBXLOLKcCW){fpXGnrbakg = true;}
      else if(iBXLOLKcCW == lmNFdVIJJu){qlKpPKXqZO = true;}
      if(oNjLIdwRSA == xNxXoNxsKi){DamgLtBADt = true;}
      else if(xNxXoNxsKi == oNjLIdwRSA){DmliMjHCsJ = true;}
      if(ocMlNopMkQ == QMfuXhnDrB){nJfXMCMunB = true;}
      else if(QMfuXhnDrB == ocMlNopMkQ){thBCLiuuYJ = true;}
      if(fhCwMFkZaD == RlbajytlOW){ZYOuaeFzuF = true;}
      if(xXSzJtoXOH == UNtkFQMKxI){ixpIKCdRWE = true;}
      if(hArFnIaaqo == DGOAkVUcng){LcokFWJzsk = true;}
      while(RlbajytlOW == fhCwMFkZaD){fMUgSljhTe = true;}
      while(UNtkFQMKxI == UNtkFQMKxI){ZrEZAhTWxp = true;}
      while(DGOAkVUcng == DGOAkVUcng){tIMrkJjIef = true;}
      if(XHjBFLkWmp == true){XHjBFLkWmp = false;}
      if(TLdnODStoG == true){TLdnODStoG = false;}
      if(UcGjxKXbpO == true){UcGjxKXbpO = false;}
      if(cQyhzMcsft == true){cQyhzMcsft = false;}
      if(fpXGnrbakg == true){fpXGnrbakg = false;}
      if(DamgLtBADt == true){DamgLtBADt = false;}
      if(nJfXMCMunB == true){nJfXMCMunB = false;}
      if(ZYOuaeFzuF == true){ZYOuaeFzuF = false;}
      if(ixpIKCdRWE == true){ixpIKCdRWE = false;}
      if(LcokFWJzsk == true){LcokFWJzsk = false;}
      if(efliGdLqGf == true){efliGdLqGf = false;}
      if(oBFyLqSWNK == true){oBFyLqSWNK = false;}
      if(YuYjpxidoE == true){YuYjpxidoE = false;}
      if(UFFJZCKGCf == true){UFFJZCKGCf = false;}
      if(qlKpPKXqZO == true){qlKpPKXqZO = false;}
      if(DmliMjHCsJ == true){DmliMjHCsJ = false;}
      if(thBCLiuuYJ == true){thBCLiuuYJ = false;}
      if(fMUgSljhTe == true){fMUgSljhTe = false;}
      if(ZrEZAhTWxp == true){ZrEZAhTWxp = false;}
      if(tIMrkJjIef == true){tIMrkJjIef = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIRCCGOXBS
{ 
  void ggOnznNaTD()
  { 
      bool LAzHzBJrGI = false;
      bool AOpziZhRio = false;
      bool cRkxXqudFQ = false;
      bool ZhBbVbGXch = false;
      bool EdcWlExTXf = false;
      bool RiZfmsPBjH = false;
      bool FfmphSNOcG = false;
      bool SJoAjyoNLS = false;
      bool sbFYzqIVnc = false;
      bool MEnUcXqloT = false;
      bool qiqQNHtYun = false;
      bool DBpQNdZNqq = false;
      bool JraAsOVTXM = false;
      bool HCYrbKjoLq = false;
      bool wjZzYKOWHy = false;
      bool xduyJzHpWz = false;
      bool lZAigBcyoC = false;
      bool skBztZRabi = false;
      bool zyMYOdHZhc = false;
      bool DtRMEWiqSX = false;
      string tBzIdWHETF;
      string NxgzDqmHrx;
      string imlyGuESZO;
      string XrnDzlzAeB;
      string ScIfbSJqrz;
      string HTtuSGOBCi;
      string RndEgUJdAR;
      string rmbqdGeFVm;
      string kNZaGEyrjr;
      string WxywieyDzG;
      string IfpaHUrCRL;
      string bIfOxDODyb;
      string WRtHttoeHz;
      string IbGOdFWzSl;
      string MuaXPNRizf;
      string PtEWiqkhfM;
      string fMtRDzCQjq;
      string fOjLPaqVqg;
      string cFebiOWjem;
      string TnSGGzBIUP;
      if(tBzIdWHETF == IfpaHUrCRL){LAzHzBJrGI = true;}
      else if(IfpaHUrCRL == tBzIdWHETF){qiqQNHtYun = true;}
      if(NxgzDqmHrx == bIfOxDODyb){AOpziZhRio = true;}
      else if(bIfOxDODyb == NxgzDqmHrx){DBpQNdZNqq = true;}
      if(imlyGuESZO == WRtHttoeHz){cRkxXqudFQ = true;}
      else if(WRtHttoeHz == imlyGuESZO){JraAsOVTXM = true;}
      if(XrnDzlzAeB == IbGOdFWzSl){ZhBbVbGXch = true;}
      else if(IbGOdFWzSl == XrnDzlzAeB){HCYrbKjoLq = true;}
      if(ScIfbSJqrz == MuaXPNRizf){EdcWlExTXf = true;}
      else if(MuaXPNRizf == ScIfbSJqrz){wjZzYKOWHy = true;}
      if(HTtuSGOBCi == PtEWiqkhfM){RiZfmsPBjH = true;}
      else if(PtEWiqkhfM == HTtuSGOBCi){xduyJzHpWz = true;}
      if(RndEgUJdAR == fMtRDzCQjq){FfmphSNOcG = true;}
      else if(fMtRDzCQjq == RndEgUJdAR){lZAigBcyoC = true;}
      if(rmbqdGeFVm == fOjLPaqVqg){SJoAjyoNLS = true;}
      if(kNZaGEyrjr == cFebiOWjem){sbFYzqIVnc = true;}
      if(WxywieyDzG == TnSGGzBIUP){MEnUcXqloT = true;}
      while(fOjLPaqVqg == rmbqdGeFVm){skBztZRabi = true;}
      while(cFebiOWjem == cFebiOWjem){zyMYOdHZhc = true;}
      while(TnSGGzBIUP == TnSGGzBIUP){DtRMEWiqSX = true;}
      if(LAzHzBJrGI == true){LAzHzBJrGI = false;}
      if(AOpziZhRio == true){AOpziZhRio = false;}
      if(cRkxXqudFQ == true){cRkxXqudFQ = false;}
      if(ZhBbVbGXch == true){ZhBbVbGXch = false;}
      if(EdcWlExTXf == true){EdcWlExTXf = false;}
      if(RiZfmsPBjH == true){RiZfmsPBjH = false;}
      if(FfmphSNOcG == true){FfmphSNOcG = false;}
      if(SJoAjyoNLS == true){SJoAjyoNLS = false;}
      if(sbFYzqIVnc == true){sbFYzqIVnc = false;}
      if(MEnUcXqloT == true){MEnUcXqloT = false;}
      if(qiqQNHtYun == true){qiqQNHtYun = false;}
      if(DBpQNdZNqq == true){DBpQNdZNqq = false;}
      if(JraAsOVTXM == true){JraAsOVTXM = false;}
      if(HCYrbKjoLq == true){HCYrbKjoLq = false;}
      if(wjZzYKOWHy == true){wjZzYKOWHy = false;}
      if(xduyJzHpWz == true){xduyJzHpWz = false;}
      if(lZAigBcyoC == true){lZAigBcyoC = false;}
      if(skBztZRabi == true){skBztZRabi = false;}
      if(zyMYOdHZhc == true){zyMYOdHZhc = false;}
      if(DtRMEWiqSX == true){DtRMEWiqSX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HASDGASLXW
{ 
  void FUSLupVpsV()
  { 
      bool dmqQxxqAWJ = false;
      bool BGQKmTVjLB = false;
      bool AVuVTGEqrU = false;
      bool bazaotcqDJ = false;
      bool gVCSCUIZzu = false;
      bool pXPPfIrUwp = false;
      bool sAHCgaHpUs = false;
      bool pdgCTeScTz = false;
      bool ydqxdELitf = false;
      bool CItMQgNAka = false;
      bool NREGELpMuB = false;
      bool oPAxrOIKXb = false;
      bool PXunqhiTlm = false;
      bool QSqrlfYkrS = false;
      bool NynsqlHxTB = false;
      bool XCbILoWQPV = false;
      bool bVaIjVXHLM = false;
      bool oXSFORiBxE = false;
      bool alAjONqhgw = false;
      bool IIUVpqXfJU = false;
      string mSoLfAhuUY;
      string uDmLQohuMI;
      string StpCQOjwjk;
      string MKzZwZqwWY;
      string aSAmIFoAMM;
      string KXCsSsbmtR;
      string PlKjLkDMOp;
      string xlYmgAsDsL;
      string YjjXZoHGHD;
      string xEBEJnHQaW;
      string CbkVOXyOLR;
      string zXsireCmJW;
      string cxFLrskUdr;
      string rccVIxzNIC;
      string pstoDYKRLd;
      string lUHDtEVYcV;
      string mdkSYWuXau;
      string fodHfjCPHS;
      string hTIAGXVZbE;
      string aZjmOLHbQg;
      if(mSoLfAhuUY == CbkVOXyOLR){dmqQxxqAWJ = true;}
      else if(CbkVOXyOLR == mSoLfAhuUY){NREGELpMuB = true;}
      if(uDmLQohuMI == zXsireCmJW){BGQKmTVjLB = true;}
      else if(zXsireCmJW == uDmLQohuMI){oPAxrOIKXb = true;}
      if(StpCQOjwjk == cxFLrskUdr){AVuVTGEqrU = true;}
      else if(cxFLrskUdr == StpCQOjwjk){PXunqhiTlm = true;}
      if(MKzZwZqwWY == rccVIxzNIC){bazaotcqDJ = true;}
      else if(rccVIxzNIC == MKzZwZqwWY){QSqrlfYkrS = true;}
      if(aSAmIFoAMM == pstoDYKRLd){gVCSCUIZzu = true;}
      else if(pstoDYKRLd == aSAmIFoAMM){NynsqlHxTB = true;}
      if(KXCsSsbmtR == lUHDtEVYcV){pXPPfIrUwp = true;}
      else if(lUHDtEVYcV == KXCsSsbmtR){XCbILoWQPV = true;}
      if(PlKjLkDMOp == mdkSYWuXau){sAHCgaHpUs = true;}
      else if(mdkSYWuXau == PlKjLkDMOp){bVaIjVXHLM = true;}
      if(xlYmgAsDsL == fodHfjCPHS){pdgCTeScTz = true;}
      if(YjjXZoHGHD == hTIAGXVZbE){ydqxdELitf = true;}
      if(xEBEJnHQaW == aZjmOLHbQg){CItMQgNAka = true;}
      while(fodHfjCPHS == xlYmgAsDsL){oXSFORiBxE = true;}
      while(hTIAGXVZbE == hTIAGXVZbE){alAjONqhgw = true;}
      while(aZjmOLHbQg == aZjmOLHbQg){IIUVpqXfJU = true;}
      if(dmqQxxqAWJ == true){dmqQxxqAWJ = false;}
      if(BGQKmTVjLB == true){BGQKmTVjLB = false;}
      if(AVuVTGEqrU == true){AVuVTGEqrU = false;}
      if(bazaotcqDJ == true){bazaotcqDJ = false;}
      if(gVCSCUIZzu == true){gVCSCUIZzu = false;}
      if(pXPPfIrUwp == true){pXPPfIrUwp = false;}
      if(sAHCgaHpUs == true){sAHCgaHpUs = false;}
      if(pdgCTeScTz == true){pdgCTeScTz = false;}
      if(ydqxdELitf == true){ydqxdELitf = false;}
      if(CItMQgNAka == true){CItMQgNAka = false;}
      if(NREGELpMuB == true){NREGELpMuB = false;}
      if(oPAxrOIKXb == true){oPAxrOIKXb = false;}
      if(PXunqhiTlm == true){PXunqhiTlm = false;}
      if(QSqrlfYkrS == true){QSqrlfYkrS = false;}
      if(NynsqlHxTB == true){NynsqlHxTB = false;}
      if(XCbILoWQPV == true){XCbILoWQPV = false;}
      if(bVaIjVXHLM == true){bVaIjVXHLM = false;}
      if(oXSFORiBxE == true){oXSFORiBxE = false;}
      if(alAjONqhgw == true){alAjONqhgw = false;}
      if(IIUVpqXfJU == true){IIUVpqXfJU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TNBJTOMTQN
{ 
  void cLunHnFdJA()
  { 
      bool bfTlUTzTMN = false;
      bool Ctmqdwlhou = false;
      bool hnSJebxcBU = false;
      bool dQjFELnoGU = false;
      bool hjPszDFYkr = false;
      bool OSupCmMJHr = false;
      bool WWRqjlJhmS = false;
      bool HxaUMyXZJa = false;
      bool WXrJFLUsCQ = false;
      bool ydgNxLRXJN = false;
      bool sXkSjRqZdD = false;
      bool OmAfVyeIlX = false;
      bool QQeVUcPNXA = false;
      bool fzPwgymYYm = false;
      bool UuPyBKdBqy = false;
      bool gIlkwcrPxG = false;
      bool CcCcXPWDyW = false;
      bool LFizDVAfTJ = false;
      bool zOWYTWNezE = false;
      bool GWaRjqrmal = false;
      string PLnFaiKrYX;
      string kufCXQNGnW;
      string MMDiSVfZFH;
      string TNRaWdlgKl;
      string SLJXDwGUpy;
      string XAcDGCIFlF;
      string DjlREXdFft;
      string egwBEBDeeW;
      string OKjGiSjNUT;
      string VftFihYqTf;
      string SBnwTqEazF;
      string ycZPprAfhk;
      string mPkLYylpRV;
      string bMLzENWmlr;
      string OJOOVrGeOq;
      string gsIirCPcWV;
      string ENIdckQZKc;
      string VNsoVdAVof;
      string qHaanhDcHB;
      string xsPPnBAjlj;
      if(PLnFaiKrYX == SBnwTqEazF){bfTlUTzTMN = true;}
      else if(SBnwTqEazF == PLnFaiKrYX){sXkSjRqZdD = true;}
      if(kufCXQNGnW == ycZPprAfhk){Ctmqdwlhou = true;}
      else if(ycZPprAfhk == kufCXQNGnW){OmAfVyeIlX = true;}
      if(MMDiSVfZFH == mPkLYylpRV){hnSJebxcBU = true;}
      else if(mPkLYylpRV == MMDiSVfZFH){QQeVUcPNXA = true;}
      if(TNRaWdlgKl == bMLzENWmlr){dQjFELnoGU = true;}
      else if(bMLzENWmlr == TNRaWdlgKl){fzPwgymYYm = true;}
      if(SLJXDwGUpy == OJOOVrGeOq){hjPszDFYkr = true;}
      else if(OJOOVrGeOq == SLJXDwGUpy){UuPyBKdBqy = true;}
      if(XAcDGCIFlF == gsIirCPcWV){OSupCmMJHr = true;}
      else if(gsIirCPcWV == XAcDGCIFlF){gIlkwcrPxG = true;}
      if(DjlREXdFft == ENIdckQZKc){WWRqjlJhmS = true;}
      else if(ENIdckQZKc == DjlREXdFft){CcCcXPWDyW = true;}
      if(egwBEBDeeW == VNsoVdAVof){HxaUMyXZJa = true;}
      if(OKjGiSjNUT == qHaanhDcHB){WXrJFLUsCQ = true;}
      if(VftFihYqTf == xsPPnBAjlj){ydgNxLRXJN = true;}
      while(VNsoVdAVof == egwBEBDeeW){LFizDVAfTJ = true;}
      while(qHaanhDcHB == qHaanhDcHB){zOWYTWNezE = true;}
      while(xsPPnBAjlj == xsPPnBAjlj){GWaRjqrmal = true;}
      if(bfTlUTzTMN == true){bfTlUTzTMN = false;}
      if(Ctmqdwlhou == true){Ctmqdwlhou = false;}
      if(hnSJebxcBU == true){hnSJebxcBU = false;}
      if(dQjFELnoGU == true){dQjFELnoGU = false;}
      if(hjPszDFYkr == true){hjPszDFYkr = false;}
      if(OSupCmMJHr == true){OSupCmMJHr = false;}
      if(WWRqjlJhmS == true){WWRqjlJhmS = false;}
      if(HxaUMyXZJa == true){HxaUMyXZJa = false;}
      if(WXrJFLUsCQ == true){WXrJFLUsCQ = false;}
      if(ydgNxLRXJN == true){ydgNxLRXJN = false;}
      if(sXkSjRqZdD == true){sXkSjRqZdD = false;}
      if(OmAfVyeIlX == true){OmAfVyeIlX = false;}
      if(QQeVUcPNXA == true){QQeVUcPNXA = false;}
      if(fzPwgymYYm == true){fzPwgymYYm = false;}
      if(UuPyBKdBqy == true){UuPyBKdBqy = false;}
      if(gIlkwcrPxG == true){gIlkwcrPxG = false;}
      if(CcCcXPWDyW == true){CcCcXPWDyW = false;}
      if(LFizDVAfTJ == true){LFizDVAfTJ = false;}
      if(zOWYTWNezE == true){zOWYTWNezE = false;}
      if(GWaRjqrmal == true){GWaRjqrmal = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HJBJELCXOW
{ 
  void OBiBNQcWdF()
  { 
      bool WYVIaKKXFh = false;
      bool qJXWuXmNos = false;
      bool nHaLEDZLFp = false;
      bool sSKGXGCCOT = false;
      bool YQOpoAOgGk = false;
      bool VgZKaPyKDW = false;
      bool kzSOnYyQzn = false;
      bool UjzUUWrjVE = false;
      bool orETUMrAeH = false;
      bool IrzqiYyABQ = false;
      bool BxgRQlhEpD = false;
      bool WNozhrtytb = false;
      bool fylqfckHlu = false;
      bool YrhFCqKmDh = false;
      bool enJbktCAJp = false;
      bool ezGZkDLpln = false;
      bool BaSteefiwq = false;
      bool gHuLxrnJGk = false;
      bool ZkxuQYkIUz = false;
      bool eUAOgEUPwF = false;
      string rVLLxzYOlL;
      string NHqqdnAajk;
      string nDlMUsunNZ;
      string TPUajjRBYp;
      string ZQTCHamLFD;
      string ihFyInjypE;
      string EjBLrxlPHs;
      string WyCtKXjiEs;
      string FiiJqlKWSu;
      string zSKUlpPHKJ;
      string nWELfjeLnk;
      string EAtwyUBqUF;
      string mPxLtEmhHT;
      string HbYuEieWdG;
      string GyihqzXNWR;
      string oXmEWYYrRb;
      string xxDTccbzrO;
      string pdNOzngPUt;
      string fYKpeioTXf;
      string JlECJItOEO;
      if(rVLLxzYOlL == nWELfjeLnk){WYVIaKKXFh = true;}
      else if(nWELfjeLnk == rVLLxzYOlL){BxgRQlhEpD = true;}
      if(NHqqdnAajk == EAtwyUBqUF){qJXWuXmNos = true;}
      else if(EAtwyUBqUF == NHqqdnAajk){WNozhrtytb = true;}
      if(nDlMUsunNZ == mPxLtEmhHT){nHaLEDZLFp = true;}
      else if(mPxLtEmhHT == nDlMUsunNZ){fylqfckHlu = true;}
      if(TPUajjRBYp == HbYuEieWdG){sSKGXGCCOT = true;}
      else if(HbYuEieWdG == TPUajjRBYp){YrhFCqKmDh = true;}
      if(ZQTCHamLFD == GyihqzXNWR){YQOpoAOgGk = true;}
      else if(GyihqzXNWR == ZQTCHamLFD){enJbktCAJp = true;}
      if(ihFyInjypE == oXmEWYYrRb){VgZKaPyKDW = true;}
      else if(oXmEWYYrRb == ihFyInjypE){ezGZkDLpln = true;}
      if(EjBLrxlPHs == xxDTccbzrO){kzSOnYyQzn = true;}
      else if(xxDTccbzrO == EjBLrxlPHs){BaSteefiwq = true;}
      if(WyCtKXjiEs == pdNOzngPUt){UjzUUWrjVE = true;}
      if(FiiJqlKWSu == fYKpeioTXf){orETUMrAeH = true;}
      if(zSKUlpPHKJ == JlECJItOEO){IrzqiYyABQ = true;}
      while(pdNOzngPUt == WyCtKXjiEs){gHuLxrnJGk = true;}
      while(fYKpeioTXf == fYKpeioTXf){ZkxuQYkIUz = true;}
      while(JlECJItOEO == JlECJItOEO){eUAOgEUPwF = true;}
      if(WYVIaKKXFh == true){WYVIaKKXFh = false;}
      if(qJXWuXmNos == true){qJXWuXmNos = false;}
      if(nHaLEDZLFp == true){nHaLEDZLFp = false;}
      if(sSKGXGCCOT == true){sSKGXGCCOT = false;}
      if(YQOpoAOgGk == true){YQOpoAOgGk = false;}
      if(VgZKaPyKDW == true){VgZKaPyKDW = false;}
      if(kzSOnYyQzn == true){kzSOnYyQzn = false;}
      if(UjzUUWrjVE == true){UjzUUWrjVE = false;}
      if(orETUMrAeH == true){orETUMrAeH = false;}
      if(IrzqiYyABQ == true){IrzqiYyABQ = false;}
      if(BxgRQlhEpD == true){BxgRQlhEpD = false;}
      if(WNozhrtytb == true){WNozhrtytb = false;}
      if(fylqfckHlu == true){fylqfckHlu = false;}
      if(YrhFCqKmDh == true){YrhFCqKmDh = false;}
      if(enJbktCAJp == true){enJbktCAJp = false;}
      if(ezGZkDLpln == true){ezGZkDLpln = false;}
      if(BaSteefiwq == true){BaSteefiwq = false;}
      if(gHuLxrnJGk == true){gHuLxrnJGk = false;}
      if(ZkxuQYkIUz == true){ZkxuQYkIUz = false;}
      if(eUAOgEUPwF == true){eUAOgEUPwF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DVJXPPDXTM
{ 
  void KCjVHCkdsq()
  { 
      bool jYtPrUxIpT = false;
      bool ABrmkRalpz = false;
      bool WrnlDYuQaJ = false;
      bool WqHaksDzWO = false;
      bool SOBXOyONwA = false;
      bool efdoZrkHMT = false;
      bool YfgfxIsQCr = false;
      bool ObObgIqPWE = false;
      bool JhTZepMRBs = false;
      bool HulCplhUaG = false;
      bool FxKDkDQCIR = false;
      bool BUkIJqLGAG = false;
      bool ubPJjToMkt = false;
      bool aVoQyMWPnb = false;
      bool YKJiqmKdry = false;
      bool ZaTTKdhBTR = false;
      bool NEQNqeeTJx = false;
      bool TuSYhkSfRx = false;
      bool JKTmTACUGU = false;
      bool dVwWNUsurM = false;
      string gWLbeZMBpo;
      string eykQoFVWyI;
      string ZHYHzfRxCU;
      string CMTCmzrCSi;
      string kfBGlAhLon;
      string cdDxVZyEcy;
      string IOyVmSdhdp;
      string MTDOWsFRUy;
      string xFINrYIVgM;
      string AnZTaWgfTS;
      string VzhybJaoab;
      string UgidACGkcN;
      string JIBQoXsimA;
      string LZxCcxXJli;
      string xTuErTFuSX;
      string QwCGJNyQJD;
      string PqBZPtigBC;
      string ewztPoMxYV;
      string RxPPiPWqrO;
      string zGAhSGSUox;
      if(gWLbeZMBpo == VzhybJaoab){jYtPrUxIpT = true;}
      else if(VzhybJaoab == gWLbeZMBpo){FxKDkDQCIR = true;}
      if(eykQoFVWyI == UgidACGkcN){ABrmkRalpz = true;}
      else if(UgidACGkcN == eykQoFVWyI){BUkIJqLGAG = true;}
      if(ZHYHzfRxCU == JIBQoXsimA){WrnlDYuQaJ = true;}
      else if(JIBQoXsimA == ZHYHzfRxCU){ubPJjToMkt = true;}
      if(CMTCmzrCSi == LZxCcxXJli){WqHaksDzWO = true;}
      else if(LZxCcxXJli == CMTCmzrCSi){aVoQyMWPnb = true;}
      if(kfBGlAhLon == xTuErTFuSX){SOBXOyONwA = true;}
      else if(xTuErTFuSX == kfBGlAhLon){YKJiqmKdry = true;}
      if(cdDxVZyEcy == QwCGJNyQJD){efdoZrkHMT = true;}
      else if(QwCGJNyQJD == cdDxVZyEcy){ZaTTKdhBTR = true;}
      if(IOyVmSdhdp == PqBZPtigBC){YfgfxIsQCr = true;}
      else if(PqBZPtigBC == IOyVmSdhdp){NEQNqeeTJx = true;}
      if(MTDOWsFRUy == ewztPoMxYV){ObObgIqPWE = true;}
      if(xFINrYIVgM == RxPPiPWqrO){JhTZepMRBs = true;}
      if(AnZTaWgfTS == zGAhSGSUox){HulCplhUaG = true;}
      while(ewztPoMxYV == MTDOWsFRUy){TuSYhkSfRx = true;}
      while(RxPPiPWqrO == RxPPiPWqrO){JKTmTACUGU = true;}
      while(zGAhSGSUox == zGAhSGSUox){dVwWNUsurM = true;}
      if(jYtPrUxIpT == true){jYtPrUxIpT = false;}
      if(ABrmkRalpz == true){ABrmkRalpz = false;}
      if(WrnlDYuQaJ == true){WrnlDYuQaJ = false;}
      if(WqHaksDzWO == true){WqHaksDzWO = false;}
      if(SOBXOyONwA == true){SOBXOyONwA = false;}
      if(efdoZrkHMT == true){efdoZrkHMT = false;}
      if(YfgfxIsQCr == true){YfgfxIsQCr = false;}
      if(ObObgIqPWE == true){ObObgIqPWE = false;}
      if(JhTZepMRBs == true){JhTZepMRBs = false;}
      if(HulCplhUaG == true){HulCplhUaG = false;}
      if(FxKDkDQCIR == true){FxKDkDQCIR = false;}
      if(BUkIJqLGAG == true){BUkIJqLGAG = false;}
      if(ubPJjToMkt == true){ubPJjToMkt = false;}
      if(aVoQyMWPnb == true){aVoQyMWPnb = false;}
      if(YKJiqmKdry == true){YKJiqmKdry = false;}
      if(ZaTTKdhBTR == true){ZaTTKdhBTR = false;}
      if(NEQNqeeTJx == true){NEQNqeeTJx = false;}
      if(TuSYhkSfRx == true){TuSYhkSfRx = false;}
      if(JKTmTACUGU == true){JKTmTACUGU = false;}
      if(dVwWNUsurM == true){dVwWNUsurM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WNZVVYXOBR
{ 
  void ukuUGQPFig()
  { 
      bool qamKjNZUMF = false;
      bool iXGGfZNVSa = false;
      bool uctJlLzLRK = false;
      bool zIdnYLJYat = false;
      bool NBBpnCRyUQ = false;
      bool XPrsWNgcXX = false;
      bool NNCBGasShU = false;
      bool QotXNtaDVj = false;
      bool tAqBmiPkRK = false;
      bool efADfAyzjM = false;
      bool IzQAAhVUfb = false;
      bool mcHndMWBOW = false;
      bool LIBWpjnpqN = false;
      bool waTJbtjqAE = false;
      bool MtFoXBYLZS = false;
      bool cwkMAzxtJQ = false;
      bool sfcSfLIxLi = false;
      bool cfBJJRDMyn = false;
      bool KcPXjzpGIc = false;
      bool xpgiLgQlIM = false;
      string xmLcDBtiEh;
      string CNLPYuKQiH;
      string sbLFlAlPJf;
      string UTTJWaySgI;
      string ewZAaDDwSS;
      string eknelUbFqD;
      string OdZXMhtCrx;
      string wriabxCLdi;
      string wpxqAifnWC;
      string zsbdsAWBmr;
      string IBDUVmCNCo;
      string SQbHHXgiWd;
      string CFfpyDQFgb;
      string aAXkaumbUN;
      string gRlhjiQTWV;
      string SmdJpDVNWS;
      string WwgaNRrpgL;
      string kFNJwjTxGP;
      string lwiLImVOuX;
      string ZYFBqkkLTR;
      if(xmLcDBtiEh == IBDUVmCNCo){qamKjNZUMF = true;}
      else if(IBDUVmCNCo == xmLcDBtiEh){IzQAAhVUfb = true;}
      if(CNLPYuKQiH == SQbHHXgiWd){iXGGfZNVSa = true;}
      else if(SQbHHXgiWd == CNLPYuKQiH){mcHndMWBOW = true;}
      if(sbLFlAlPJf == CFfpyDQFgb){uctJlLzLRK = true;}
      else if(CFfpyDQFgb == sbLFlAlPJf){LIBWpjnpqN = true;}
      if(UTTJWaySgI == aAXkaumbUN){zIdnYLJYat = true;}
      else if(aAXkaumbUN == UTTJWaySgI){waTJbtjqAE = true;}
      if(ewZAaDDwSS == gRlhjiQTWV){NBBpnCRyUQ = true;}
      else if(gRlhjiQTWV == ewZAaDDwSS){MtFoXBYLZS = true;}
      if(eknelUbFqD == SmdJpDVNWS){XPrsWNgcXX = true;}
      else if(SmdJpDVNWS == eknelUbFqD){cwkMAzxtJQ = true;}
      if(OdZXMhtCrx == WwgaNRrpgL){NNCBGasShU = true;}
      else if(WwgaNRrpgL == OdZXMhtCrx){sfcSfLIxLi = true;}
      if(wriabxCLdi == kFNJwjTxGP){QotXNtaDVj = true;}
      if(wpxqAifnWC == lwiLImVOuX){tAqBmiPkRK = true;}
      if(zsbdsAWBmr == ZYFBqkkLTR){efADfAyzjM = true;}
      while(kFNJwjTxGP == wriabxCLdi){cfBJJRDMyn = true;}
      while(lwiLImVOuX == lwiLImVOuX){KcPXjzpGIc = true;}
      while(ZYFBqkkLTR == ZYFBqkkLTR){xpgiLgQlIM = true;}
      if(qamKjNZUMF == true){qamKjNZUMF = false;}
      if(iXGGfZNVSa == true){iXGGfZNVSa = false;}
      if(uctJlLzLRK == true){uctJlLzLRK = false;}
      if(zIdnYLJYat == true){zIdnYLJYat = false;}
      if(NBBpnCRyUQ == true){NBBpnCRyUQ = false;}
      if(XPrsWNgcXX == true){XPrsWNgcXX = false;}
      if(NNCBGasShU == true){NNCBGasShU = false;}
      if(QotXNtaDVj == true){QotXNtaDVj = false;}
      if(tAqBmiPkRK == true){tAqBmiPkRK = false;}
      if(efADfAyzjM == true){efADfAyzjM = false;}
      if(IzQAAhVUfb == true){IzQAAhVUfb = false;}
      if(mcHndMWBOW == true){mcHndMWBOW = false;}
      if(LIBWpjnpqN == true){LIBWpjnpqN = false;}
      if(waTJbtjqAE == true){waTJbtjqAE = false;}
      if(MtFoXBYLZS == true){MtFoXBYLZS = false;}
      if(cwkMAzxtJQ == true){cwkMAzxtJQ = false;}
      if(sfcSfLIxLi == true){sfcSfLIxLi = false;}
      if(cfBJJRDMyn == true){cfBJJRDMyn = false;}
      if(KcPXjzpGIc == true){KcPXjzpGIc = false;}
      if(xpgiLgQlIM == true){xpgiLgQlIM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RWNFQXAAFM
{ 
  void CsmwOQLUtr()
  { 
      bool pVGgiOBdiY = false;
      bool QKtBdDtjAJ = false;
      bool kTETVBEymk = false;
      bool joQxNPoDbR = false;
      bool smxIeZfaLx = false;
      bool ZLgnwVQmLg = false;
      bool KDqynbswmN = false;
      bool OpHiQxWuou = false;
      bool VcloLYHbAq = false;
      bool yCrtHowzUD = false;
      bool fimyhjDyXz = false;
      bool zUxPKhRBmP = false;
      bool TQuwPLxNaa = false;
      bool AWalPmonHa = false;
      bool VJEBrcEbiY = false;
      bool XuLEiOmqhV = false;
      bool lpWxybtLAX = false;
      bool rdtLtKMtDl = false;
      bool HVdBCFKWCA = false;
      bool zxFkoelHDP = false;
      string lCCSaYsGns;
      string LnQkNtbAEt;
      string KIPREIMuzd;
      string kgYEzBSkWx;
      string HpRAEqFZMk;
      string JgYxKclkNS;
      string MxHJHeOMkL;
      string bpcGmTqOMM;
      string CmiOUDIasV;
      string PgXDkJiHsZ;
      string brnBJSERKp;
      string lXYAPZOsoE;
      string VnSOwtSYVc;
      string kiVljJyhEB;
      string zpQDjrIWmK;
      string upRnEnZYFO;
      string AeuhFCBmPG;
      string agnnEeXPeD;
      string kwkLguRghw;
      string jZbpBTuhyg;
      if(lCCSaYsGns == brnBJSERKp){pVGgiOBdiY = true;}
      else if(brnBJSERKp == lCCSaYsGns){fimyhjDyXz = true;}
      if(LnQkNtbAEt == lXYAPZOsoE){QKtBdDtjAJ = true;}
      else if(lXYAPZOsoE == LnQkNtbAEt){zUxPKhRBmP = true;}
      if(KIPREIMuzd == VnSOwtSYVc){kTETVBEymk = true;}
      else if(VnSOwtSYVc == KIPREIMuzd){TQuwPLxNaa = true;}
      if(kgYEzBSkWx == kiVljJyhEB){joQxNPoDbR = true;}
      else if(kiVljJyhEB == kgYEzBSkWx){AWalPmonHa = true;}
      if(HpRAEqFZMk == zpQDjrIWmK){smxIeZfaLx = true;}
      else if(zpQDjrIWmK == HpRAEqFZMk){VJEBrcEbiY = true;}
      if(JgYxKclkNS == upRnEnZYFO){ZLgnwVQmLg = true;}
      else if(upRnEnZYFO == JgYxKclkNS){XuLEiOmqhV = true;}
      if(MxHJHeOMkL == AeuhFCBmPG){KDqynbswmN = true;}
      else if(AeuhFCBmPG == MxHJHeOMkL){lpWxybtLAX = true;}
      if(bpcGmTqOMM == agnnEeXPeD){OpHiQxWuou = true;}
      if(CmiOUDIasV == kwkLguRghw){VcloLYHbAq = true;}
      if(PgXDkJiHsZ == jZbpBTuhyg){yCrtHowzUD = true;}
      while(agnnEeXPeD == bpcGmTqOMM){rdtLtKMtDl = true;}
      while(kwkLguRghw == kwkLguRghw){HVdBCFKWCA = true;}
      while(jZbpBTuhyg == jZbpBTuhyg){zxFkoelHDP = true;}
      if(pVGgiOBdiY == true){pVGgiOBdiY = false;}
      if(QKtBdDtjAJ == true){QKtBdDtjAJ = false;}
      if(kTETVBEymk == true){kTETVBEymk = false;}
      if(joQxNPoDbR == true){joQxNPoDbR = false;}
      if(smxIeZfaLx == true){smxIeZfaLx = false;}
      if(ZLgnwVQmLg == true){ZLgnwVQmLg = false;}
      if(KDqynbswmN == true){KDqynbswmN = false;}
      if(OpHiQxWuou == true){OpHiQxWuou = false;}
      if(VcloLYHbAq == true){VcloLYHbAq = false;}
      if(yCrtHowzUD == true){yCrtHowzUD = false;}
      if(fimyhjDyXz == true){fimyhjDyXz = false;}
      if(zUxPKhRBmP == true){zUxPKhRBmP = false;}
      if(TQuwPLxNaa == true){TQuwPLxNaa = false;}
      if(AWalPmonHa == true){AWalPmonHa = false;}
      if(VJEBrcEbiY == true){VJEBrcEbiY = false;}
      if(XuLEiOmqhV == true){XuLEiOmqhV = false;}
      if(lpWxybtLAX == true){lpWxybtLAX = false;}
      if(rdtLtKMtDl == true){rdtLtKMtDl = false;}
      if(HVdBCFKWCA == true){HVdBCFKWCA = false;}
      if(zxFkoelHDP == true){zxFkoelHDP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FTGWCMESMI
{ 
  void zLGqesDsEQ()
  { 
      bool kGtzoxzTJt = false;
      bool XPZEsdAEOR = false;
      bool kDRjNLjuoI = false;
      bool REEhZZiWUl = false;
      bool JqKSwNEGgO = false;
      bool HzqAOgoKkc = false;
      bool NDeAbSLreS = false;
      bool tdicHsrymA = false;
      bool GcNZBSNESr = false;
      bool jYkqXFMKqd = false;
      bool CMaOTdQOrV = false;
      bool npXkVjpEzJ = false;
      bool FHYliVrqEB = false;
      bool fhHJytBzGX = false;
      bool BzLxEtBAVm = false;
      bool PHLgXumofy = false;
      bool kYKpoFhOmb = false;
      bool ipyaHGubho = false;
      bool TqVQlXWakC = false;
      bool HMTHlboUHy = false;
      string IynBssWLVc;
      string ismATsycFj;
      string ezIysYsruE;
      string OXyaPUhORH;
      string sHBmPrKVhD;
      string TwBRcIpoIT;
      string zePROKuLkz;
      string KiLxpWxUhA;
      string NWJrjRVfyH;
      string esGxINrjYE;
      string xzkirjkDaF;
      string KUHHGcUWhx;
      string nONdTRcNoc;
      string eNwcDOlZAA;
      string fSErwJkzqe;
      string rVBaQhkHOZ;
      string HXOyawYdEq;
      string puVhRVKVgK;
      string gdWJjJLUMU;
      string ceLarIDFRz;
      if(IynBssWLVc == xzkirjkDaF){kGtzoxzTJt = true;}
      else if(xzkirjkDaF == IynBssWLVc){CMaOTdQOrV = true;}
      if(ismATsycFj == KUHHGcUWhx){XPZEsdAEOR = true;}
      else if(KUHHGcUWhx == ismATsycFj){npXkVjpEzJ = true;}
      if(ezIysYsruE == nONdTRcNoc){kDRjNLjuoI = true;}
      else if(nONdTRcNoc == ezIysYsruE){FHYliVrqEB = true;}
      if(OXyaPUhORH == eNwcDOlZAA){REEhZZiWUl = true;}
      else if(eNwcDOlZAA == OXyaPUhORH){fhHJytBzGX = true;}
      if(sHBmPrKVhD == fSErwJkzqe){JqKSwNEGgO = true;}
      else if(fSErwJkzqe == sHBmPrKVhD){BzLxEtBAVm = true;}
      if(TwBRcIpoIT == rVBaQhkHOZ){HzqAOgoKkc = true;}
      else if(rVBaQhkHOZ == TwBRcIpoIT){PHLgXumofy = true;}
      if(zePROKuLkz == HXOyawYdEq){NDeAbSLreS = true;}
      else if(HXOyawYdEq == zePROKuLkz){kYKpoFhOmb = true;}
      if(KiLxpWxUhA == puVhRVKVgK){tdicHsrymA = true;}
      if(NWJrjRVfyH == gdWJjJLUMU){GcNZBSNESr = true;}
      if(esGxINrjYE == ceLarIDFRz){jYkqXFMKqd = true;}
      while(puVhRVKVgK == KiLxpWxUhA){ipyaHGubho = true;}
      while(gdWJjJLUMU == gdWJjJLUMU){TqVQlXWakC = true;}
      while(ceLarIDFRz == ceLarIDFRz){HMTHlboUHy = true;}
      if(kGtzoxzTJt == true){kGtzoxzTJt = false;}
      if(XPZEsdAEOR == true){XPZEsdAEOR = false;}
      if(kDRjNLjuoI == true){kDRjNLjuoI = false;}
      if(REEhZZiWUl == true){REEhZZiWUl = false;}
      if(JqKSwNEGgO == true){JqKSwNEGgO = false;}
      if(HzqAOgoKkc == true){HzqAOgoKkc = false;}
      if(NDeAbSLreS == true){NDeAbSLreS = false;}
      if(tdicHsrymA == true){tdicHsrymA = false;}
      if(GcNZBSNESr == true){GcNZBSNESr = false;}
      if(jYkqXFMKqd == true){jYkqXFMKqd = false;}
      if(CMaOTdQOrV == true){CMaOTdQOrV = false;}
      if(npXkVjpEzJ == true){npXkVjpEzJ = false;}
      if(FHYliVrqEB == true){FHYliVrqEB = false;}
      if(fhHJytBzGX == true){fhHJytBzGX = false;}
      if(BzLxEtBAVm == true){BzLxEtBAVm = false;}
      if(PHLgXumofy == true){PHLgXumofy = false;}
      if(kYKpoFhOmb == true){kYKpoFhOmb = false;}
      if(ipyaHGubho == true){ipyaHGubho = false;}
      if(TqVQlXWakC == true){TqVQlXWakC = false;}
      if(HMTHlboUHy == true){HMTHlboUHy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NQBURKYLRE
{ 
  void bwxOYniKfk()
  { 
      bool tyDStoNBCa = false;
      bool SYLCIeugCa = false;
      bool VulINIaLOz = false;
      bool blSWAFYxWs = false;
      bool OqLOQewLgH = false;
      bool gewAtyLuFl = false;
      bool OBmDzfFnBD = false;
      bool FyJIMejXrh = false;
      bool LOeGSwpRbC = false;
      bool sdqkdMEIOk = false;
      bool ZHJcBhVnnO = false;
      bool OnCXZAWfjD = false;
      bool onMzJbGYdz = false;
      bool aaJHHDFBEj = false;
      bool aCcMmFaTKd = false;
      bool pXXLuluJTZ = false;
      bool bwKonnduPV = false;
      bool uUbAblKzME = false;
      bool AmNzJDCxLV = false;
      bool HuhdIdrnYz = false;
      string WEPfeEiQeI;
      string PkpERqPKAo;
      string YRHQoUEVUG;
      string odektGFQjk;
      string tOWPzdBcJb;
      string emquHEwypJ;
      string ANuXSkFFJK;
      string kzaOuKtqRL;
      string TaLraBmjco;
      string KGZZkgSzxN;
      string YuSypfMbAw;
      string JFfeoYBDwR;
      string yUbTAdYAdO;
      string rutElXHMBt;
      string oKjffFaujL;
      string ePCeODTzyM;
      string HLylEOKbrR;
      string QoBBcnkunu;
      string DcPRicrOoi;
      string EIOomcMybQ;
      if(WEPfeEiQeI == YuSypfMbAw){tyDStoNBCa = true;}
      else if(YuSypfMbAw == WEPfeEiQeI){ZHJcBhVnnO = true;}
      if(PkpERqPKAo == JFfeoYBDwR){SYLCIeugCa = true;}
      else if(JFfeoYBDwR == PkpERqPKAo){OnCXZAWfjD = true;}
      if(YRHQoUEVUG == yUbTAdYAdO){VulINIaLOz = true;}
      else if(yUbTAdYAdO == YRHQoUEVUG){onMzJbGYdz = true;}
      if(odektGFQjk == rutElXHMBt){blSWAFYxWs = true;}
      else if(rutElXHMBt == odektGFQjk){aaJHHDFBEj = true;}
      if(tOWPzdBcJb == oKjffFaujL){OqLOQewLgH = true;}
      else if(oKjffFaujL == tOWPzdBcJb){aCcMmFaTKd = true;}
      if(emquHEwypJ == ePCeODTzyM){gewAtyLuFl = true;}
      else if(ePCeODTzyM == emquHEwypJ){pXXLuluJTZ = true;}
      if(ANuXSkFFJK == HLylEOKbrR){OBmDzfFnBD = true;}
      else if(HLylEOKbrR == ANuXSkFFJK){bwKonnduPV = true;}
      if(kzaOuKtqRL == QoBBcnkunu){FyJIMejXrh = true;}
      if(TaLraBmjco == DcPRicrOoi){LOeGSwpRbC = true;}
      if(KGZZkgSzxN == EIOomcMybQ){sdqkdMEIOk = true;}
      while(QoBBcnkunu == kzaOuKtqRL){uUbAblKzME = true;}
      while(DcPRicrOoi == DcPRicrOoi){AmNzJDCxLV = true;}
      while(EIOomcMybQ == EIOomcMybQ){HuhdIdrnYz = true;}
      if(tyDStoNBCa == true){tyDStoNBCa = false;}
      if(SYLCIeugCa == true){SYLCIeugCa = false;}
      if(VulINIaLOz == true){VulINIaLOz = false;}
      if(blSWAFYxWs == true){blSWAFYxWs = false;}
      if(OqLOQewLgH == true){OqLOQewLgH = false;}
      if(gewAtyLuFl == true){gewAtyLuFl = false;}
      if(OBmDzfFnBD == true){OBmDzfFnBD = false;}
      if(FyJIMejXrh == true){FyJIMejXrh = false;}
      if(LOeGSwpRbC == true){LOeGSwpRbC = false;}
      if(sdqkdMEIOk == true){sdqkdMEIOk = false;}
      if(ZHJcBhVnnO == true){ZHJcBhVnnO = false;}
      if(OnCXZAWfjD == true){OnCXZAWfjD = false;}
      if(onMzJbGYdz == true){onMzJbGYdz = false;}
      if(aaJHHDFBEj == true){aaJHHDFBEj = false;}
      if(aCcMmFaTKd == true){aCcMmFaTKd = false;}
      if(pXXLuluJTZ == true){pXXLuluJTZ = false;}
      if(bwKonnduPV == true){bwKonnduPV = false;}
      if(uUbAblKzME == true){uUbAblKzME = false;}
      if(AmNzJDCxLV == true){AmNzJDCxLV = false;}
      if(HuhdIdrnYz == true){HuhdIdrnYz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FLVKNPANSJ
{ 
  void SEebNijkyG()
  { 
      bool gqrKKuKUTt = false;
      bool SVlzGeTCoX = false;
      bool zzOntdhMJo = false;
      bool nWhHUKziCa = false;
      bool kRHpUemyXw = false;
      bool kOLJmhcDPg = false;
      bool MyLeFumdew = false;
      bool ekzNmhrXTP = false;
      bool pjnMDZLYUl = false;
      bool gwSUNlFbkY = false;
      bool rISbRAOyWF = false;
      bool oEjApbJzbf = false;
      bool jNJrOhRezA = false;
      bool bQmtXhRMtC = false;
      bool KNCPxcMSel = false;
      bool cFAFodzZNj = false;
      bool hjyWcYRpbI = false;
      bool KxEYUWLtuk = false;
      bool VzANXWQgEs = false;
      bool hqzKUZOflX = false;
      string xQazMaBeVV;
      string RqGitFdAWD;
      string YkiTmmSKNG;
      string eIkROIjoNb;
      string ywESwguRyX;
      string YzkPuLhHMZ;
      string IqRPqJGoUl;
      string VomtFcgQWF;
      string rBLogeWVVC;
      string abbmTGdnal;
      string aFxMCiMpJS;
      string eRjHhGechM;
      string ljTRLsMzay;
      string yrpjelEzly;
      string SgLCXJqUFN;
      string bBFNzqleBI;
      string WNPLUlbzbu;
      string CfpjtFXQsC;
      string CrsNWwmbkn;
      string AYxdaFQAhl;
      if(xQazMaBeVV == aFxMCiMpJS){gqrKKuKUTt = true;}
      else if(aFxMCiMpJS == xQazMaBeVV){rISbRAOyWF = true;}
      if(RqGitFdAWD == eRjHhGechM){SVlzGeTCoX = true;}
      else if(eRjHhGechM == RqGitFdAWD){oEjApbJzbf = true;}
      if(YkiTmmSKNG == ljTRLsMzay){zzOntdhMJo = true;}
      else if(ljTRLsMzay == YkiTmmSKNG){jNJrOhRezA = true;}
      if(eIkROIjoNb == yrpjelEzly){nWhHUKziCa = true;}
      else if(yrpjelEzly == eIkROIjoNb){bQmtXhRMtC = true;}
      if(ywESwguRyX == SgLCXJqUFN){kRHpUemyXw = true;}
      else if(SgLCXJqUFN == ywESwguRyX){KNCPxcMSel = true;}
      if(YzkPuLhHMZ == bBFNzqleBI){kOLJmhcDPg = true;}
      else if(bBFNzqleBI == YzkPuLhHMZ){cFAFodzZNj = true;}
      if(IqRPqJGoUl == WNPLUlbzbu){MyLeFumdew = true;}
      else if(WNPLUlbzbu == IqRPqJGoUl){hjyWcYRpbI = true;}
      if(VomtFcgQWF == CfpjtFXQsC){ekzNmhrXTP = true;}
      if(rBLogeWVVC == CrsNWwmbkn){pjnMDZLYUl = true;}
      if(abbmTGdnal == AYxdaFQAhl){gwSUNlFbkY = true;}
      while(CfpjtFXQsC == VomtFcgQWF){KxEYUWLtuk = true;}
      while(CrsNWwmbkn == CrsNWwmbkn){VzANXWQgEs = true;}
      while(AYxdaFQAhl == AYxdaFQAhl){hqzKUZOflX = true;}
      if(gqrKKuKUTt == true){gqrKKuKUTt = false;}
      if(SVlzGeTCoX == true){SVlzGeTCoX = false;}
      if(zzOntdhMJo == true){zzOntdhMJo = false;}
      if(nWhHUKziCa == true){nWhHUKziCa = false;}
      if(kRHpUemyXw == true){kRHpUemyXw = false;}
      if(kOLJmhcDPg == true){kOLJmhcDPg = false;}
      if(MyLeFumdew == true){MyLeFumdew = false;}
      if(ekzNmhrXTP == true){ekzNmhrXTP = false;}
      if(pjnMDZLYUl == true){pjnMDZLYUl = false;}
      if(gwSUNlFbkY == true){gwSUNlFbkY = false;}
      if(rISbRAOyWF == true){rISbRAOyWF = false;}
      if(oEjApbJzbf == true){oEjApbJzbf = false;}
      if(jNJrOhRezA == true){jNJrOhRezA = false;}
      if(bQmtXhRMtC == true){bQmtXhRMtC = false;}
      if(KNCPxcMSel == true){KNCPxcMSel = false;}
      if(cFAFodzZNj == true){cFAFodzZNj = false;}
      if(hjyWcYRpbI == true){hjyWcYRpbI = false;}
      if(KxEYUWLtuk == true){KxEYUWLtuk = false;}
      if(VzANXWQgEs == true){VzANXWQgEs = false;}
      if(hqzKUZOflX == true){hqzKUZOflX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AJADZRWWCD
{ 
  void ZZksUaihjj()
  { 
      bool GmaxSZIZeE = false;
      bool xSupOfEZfl = false;
      bool CCrmIYJGtZ = false;
      bool yWlcgAVNSa = false;
      bool fLnATmQRSS = false;
      bool yUniPEtnot = false;
      bool PCeFFafSIN = false;
      bool JqGFGpNrTV = false;
      bool HrnbadhCMc = false;
      bool FhXYLcgits = false;
      bool GyIEJHNhcZ = false;
      bool pBUTmWODeb = false;
      bool rcFeHaShtc = false;
      bool JeyZOJiiSS = false;
      bool PzZmmENEkn = false;
      bool NcERAdrdxh = false;
      bool ofnzPKDtEd = false;
      bool nfjLMsDRrD = false;
      bool NNwFPfafZk = false;
      bool QFljdjKZWb = false;
      string cKVrJUOcUV;
      string JNmoACNnHY;
      string DohQsElawO;
      string UxrYnFqqLZ;
      string jztDMEsrql;
      string dPlPPncEzF;
      string hnfFAMVNAt;
      string LVchoDteDn;
      string LtiJjFLcIz;
      string blqFqwSoCA;
      string heqwaHmDZM;
      string syBLtmEVVu;
      string BsEBSYdWpr;
      string kFbDGfClib;
      string SHCwGdkfLE;
      string qwSHynapdC;
      string dPMganWxEN;
      string kRmsbsqHtn;
      string nxLlAolTER;
      string FMHgyCuUVR;
      if(cKVrJUOcUV == heqwaHmDZM){GmaxSZIZeE = true;}
      else if(heqwaHmDZM == cKVrJUOcUV){GyIEJHNhcZ = true;}
      if(JNmoACNnHY == syBLtmEVVu){xSupOfEZfl = true;}
      else if(syBLtmEVVu == JNmoACNnHY){pBUTmWODeb = true;}
      if(DohQsElawO == BsEBSYdWpr){CCrmIYJGtZ = true;}
      else if(BsEBSYdWpr == DohQsElawO){rcFeHaShtc = true;}
      if(UxrYnFqqLZ == kFbDGfClib){yWlcgAVNSa = true;}
      else if(kFbDGfClib == UxrYnFqqLZ){JeyZOJiiSS = true;}
      if(jztDMEsrql == SHCwGdkfLE){fLnATmQRSS = true;}
      else if(SHCwGdkfLE == jztDMEsrql){PzZmmENEkn = true;}
      if(dPlPPncEzF == qwSHynapdC){yUniPEtnot = true;}
      else if(qwSHynapdC == dPlPPncEzF){NcERAdrdxh = true;}
      if(hnfFAMVNAt == dPMganWxEN){PCeFFafSIN = true;}
      else if(dPMganWxEN == hnfFAMVNAt){ofnzPKDtEd = true;}
      if(LVchoDteDn == kRmsbsqHtn){JqGFGpNrTV = true;}
      if(LtiJjFLcIz == nxLlAolTER){HrnbadhCMc = true;}
      if(blqFqwSoCA == FMHgyCuUVR){FhXYLcgits = true;}
      while(kRmsbsqHtn == LVchoDteDn){nfjLMsDRrD = true;}
      while(nxLlAolTER == nxLlAolTER){NNwFPfafZk = true;}
      while(FMHgyCuUVR == FMHgyCuUVR){QFljdjKZWb = true;}
      if(GmaxSZIZeE == true){GmaxSZIZeE = false;}
      if(xSupOfEZfl == true){xSupOfEZfl = false;}
      if(CCrmIYJGtZ == true){CCrmIYJGtZ = false;}
      if(yWlcgAVNSa == true){yWlcgAVNSa = false;}
      if(fLnATmQRSS == true){fLnATmQRSS = false;}
      if(yUniPEtnot == true){yUniPEtnot = false;}
      if(PCeFFafSIN == true){PCeFFafSIN = false;}
      if(JqGFGpNrTV == true){JqGFGpNrTV = false;}
      if(HrnbadhCMc == true){HrnbadhCMc = false;}
      if(FhXYLcgits == true){FhXYLcgits = false;}
      if(GyIEJHNhcZ == true){GyIEJHNhcZ = false;}
      if(pBUTmWODeb == true){pBUTmWODeb = false;}
      if(rcFeHaShtc == true){rcFeHaShtc = false;}
      if(JeyZOJiiSS == true){JeyZOJiiSS = false;}
      if(PzZmmENEkn == true){PzZmmENEkn = false;}
      if(NcERAdrdxh == true){NcERAdrdxh = false;}
      if(ofnzPKDtEd == true){ofnzPKDtEd = false;}
      if(nfjLMsDRrD == true){nfjLMsDRrD = false;}
      if(NNwFPfafZk == true){NNwFPfafZk = false;}
      if(QFljdjKZWb == true){QFljdjKZWb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WVIQYGXTIH
{ 
  void jBjdptriUj()
  { 
      bool jocCZEqxoE = false;
      bool jQxVZegJOb = false;
      bool DfwNJqqQgi = false;
      bool VnKrGQDgIE = false;
      bool OthENEociT = false;
      bool TAilcDrOsi = false;
      bool MZQGiuGEPI = false;
      bool bzBJNJxrzE = false;
      bool COhNOUEYOC = false;
      bool XnmZrndbVR = false;
      bool yjNZqTzYXT = false;
      bool GAPnfyqCqN = false;
      bool qgoMjmMaRZ = false;
      bool eUVhGSBHVt = false;
      bool VeAuwXYyts = false;
      bool wakHZQuApE = false;
      bool HYHynkdghN = false;
      bool wjfxrLgtQM = false;
      bool ONfXcEjNHo = false;
      bool WARRlwXCGK = false;
      string qWURYVPfhY;
      string SmWwgCgknB;
      string MkyGmGCLwE;
      string YxdBzNHwrK;
      string AMwZqnhUJa;
      string PZLdCFYOdR;
      string TDidzVIUwS;
      string tkrdBznXOz;
      string YgCUnykzzt;
      string osRapwdSZV;
      string eMYpgdhgcD;
      string QBzerlBNoB;
      string jIVCdATRmE;
      string VVxsTMILnJ;
      string QEWwcntmhE;
      string uPdYkVpWMf;
      string KPsYhuDFKe;
      string dpYfjflYZp;
      string GfiiJFrXIx;
      string VlyIyAKyOg;
      if(qWURYVPfhY == eMYpgdhgcD){jocCZEqxoE = true;}
      else if(eMYpgdhgcD == qWURYVPfhY){yjNZqTzYXT = true;}
      if(SmWwgCgknB == QBzerlBNoB){jQxVZegJOb = true;}
      else if(QBzerlBNoB == SmWwgCgknB){GAPnfyqCqN = true;}
      if(MkyGmGCLwE == jIVCdATRmE){DfwNJqqQgi = true;}
      else if(jIVCdATRmE == MkyGmGCLwE){qgoMjmMaRZ = true;}
      if(YxdBzNHwrK == VVxsTMILnJ){VnKrGQDgIE = true;}
      else if(VVxsTMILnJ == YxdBzNHwrK){eUVhGSBHVt = true;}
      if(AMwZqnhUJa == QEWwcntmhE){OthENEociT = true;}
      else if(QEWwcntmhE == AMwZqnhUJa){VeAuwXYyts = true;}
      if(PZLdCFYOdR == uPdYkVpWMf){TAilcDrOsi = true;}
      else if(uPdYkVpWMf == PZLdCFYOdR){wakHZQuApE = true;}
      if(TDidzVIUwS == KPsYhuDFKe){MZQGiuGEPI = true;}
      else if(KPsYhuDFKe == TDidzVIUwS){HYHynkdghN = true;}
      if(tkrdBznXOz == dpYfjflYZp){bzBJNJxrzE = true;}
      if(YgCUnykzzt == GfiiJFrXIx){COhNOUEYOC = true;}
      if(osRapwdSZV == VlyIyAKyOg){XnmZrndbVR = true;}
      while(dpYfjflYZp == tkrdBznXOz){wjfxrLgtQM = true;}
      while(GfiiJFrXIx == GfiiJFrXIx){ONfXcEjNHo = true;}
      while(VlyIyAKyOg == VlyIyAKyOg){WARRlwXCGK = true;}
      if(jocCZEqxoE == true){jocCZEqxoE = false;}
      if(jQxVZegJOb == true){jQxVZegJOb = false;}
      if(DfwNJqqQgi == true){DfwNJqqQgi = false;}
      if(VnKrGQDgIE == true){VnKrGQDgIE = false;}
      if(OthENEociT == true){OthENEociT = false;}
      if(TAilcDrOsi == true){TAilcDrOsi = false;}
      if(MZQGiuGEPI == true){MZQGiuGEPI = false;}
      if(bzBJNJxrzE == true){bzBJNJxrzE = false;}
      if(COhNOUEYOC == true){COhNOUEYOC = false;}
      if(XnmZrndbVR == true){XnmZrndbVR = false;}
      if(yjNZqTzYXT == true){yjNZqTzYXT = false;}
      if(GAPnfyqCqN == true){GAPnfyqCqN = false;}
      if(qgoMjmMaRZ == true){qgoMjmMaRZ = false;}
      if(eUVhGSBHVt == true){eUVhGSBHVt = false;}
      if(VeAuwXYyts == true){VeAuwXYyts = false;}
      if(wakHZQuApE == true){wakHZQuApE = false;}
      if(HYHynkdghN == true){HYHynkdghN = false;}
      if(wjfxrLgtQM == true){wjfxrLgtQM = false;}
      if(ONfXcEjNHo == true){ONfXcEjNHo = false;}
      if(WARRlwXCGK == true){WARRlwXCGK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYOTOKQTYU
{ 
  void IruzXTpVJB()
  { 
      bool fSibNUTQWm = false;
      bool ClRYJzywIl = false;
      bool fGszeaqkSR = false;
      bool KVJDuWZThh = false;
      bool LEVyNRTFwa = false;
      bool YceuSYZjwl = false;
      bool diyFcfbNdl = false;
      bool ZdOaaakukN = false;
      bool HkoqrhpOkW = false;
      bool xoWuDcGQUh = false;
      bool oFbJBtNEUq = false;
      bool neyiersHMu = false;
      bool oNcHnjHTWx = false;
      bool UTaDXBJeox = false;
      bool TltshSqnPL = false;
      bool jzDYrbbUUQ = false;
      bool mtgWWTEtLc = false;
      bool hNRPbDSjYV = false;
      bool sTDKNVQBLw = false;
      bool ZoKXJYEWVN = false;
      string fBEbCUkDlh;
      string eUWPLjdipe;
      string ygVikedrLK;
      string GBETfRHfzf;
      string nzNwCmZECQ;
      string MlWxIzeUpW;
      string prqabdQDis;
      string bxjKpySZgy;
      string FZouyTdGKg;
      string llpcouHmTX;
      string VWVIoOBMGJ;
      string gFnqRPDwcH;
      string AJrBHoGHUu;
      string qeFIbhEfFi;
      string RQzAzfyyKY;
      string rKJMWMdTBA;
      string ItrLSBAeOi;
      string LWqsoiJrBb;
      string pIwuDfVslP;
      string DkeFaXYnhy;
      if(fBEbCUkDlh == VWVIoOBMGJ){fSibNUTQWm = true;}
      else if(VWVIoOBMGJ == fBEbCUkDlh){oFbJBtNEUq = true;}
      if(eUWPLjdipe == gFnqRPDwcH){ClRYJzywIl = true;}
      else if(gFnqRPDwcH == eUWPLjdipe){neyiersHMu = true;}
      if(ygVikedrLK == AJrBHoGHUu){fGszeaqkSR = true;}
      else if(AJrBHoGHUu == ygVikedrLK){oNcHnjHTWx = true;}
      if(GBETfRHfzf == qeFIbhEfFi){KVJDuWZThh = true;}
      else if(qeFIbhEfFi == GBETfRHfzf){UTaDXBJeox = true;}
      if(nzNwCmZECQ == RQzAzfyyKY){LEVyNRTFwa = true;}
      else if(RQzAzfyyKY == nzNwCmZECQ){TltshSqnPL = true;}
      if(MlWxIzeUpW == rKJMWMdTBA){YceuSYZjwl = true;}
      else if(rKJMWMdTBA == MlWxIzeUpW){jzDYrbbUUQ = true;}
      if(prqabdQDis == ItrLSBAeOi){diyFcfbNdl = true;}
      else if(ItrLSBAeOi == prqabdQDis){mtgWWTEtLc = true;}
      if(bxjKpySZgy == LWqsoiJrBb){ZdOaaakukN = true;}
      if(FZouyTdGKg == pIwuDfVslP){HkoqrhpOkW = true;}
      if(llpcouHmTX == DkeFaXYnhy){xoWuDcGQUh = true;}
      while(LWqsoiJrBb == bxjKpySZgy){hNRPbDSjYV = true;}
      while(pIwuDfVslP == pIwuDfVslP){sTDKNVQBLw = true;}
      while(DkeFaXYnhy == DkeFaXYnhy){ZoKXJYEWVN = true;}
      if(fSibNUTQWm == true){fSibNUTQWm = false;}
      if(ClRYJzywIl == true){ClRYJzywIl = false;}
      if(fGszeaqkSR == true){fGszeaqkSR = false;}
      if(KVJDuWZThh == true){KVJDuWZThh = false;}
      if(LEVyNRTFwa == true){LEVyNRTFwa = false;}
      if(YceuSYZjwl == true){YceuSYZjwl = false;}
      if(diyFcfbNdl == true){diyFcfbNdl = false;}
      if(ZdOaaakukN == true){ZdOaaakukN = false;}
      if(HkoqrhpOkW == true){HkoqrhpOkW = false;}
      if(xoWuDcGQUh == true){xoWuDcGQUh = false;}
      if(oFbJBtNEUq == true){oFbJBtNEUq = false;}
      if(neyiersHMu == true){neyiersHMu = false;}
      if(oNcHnjHTWx == true){oNcHnjHTWx = false;}
      if(UTaDXBJeox == true){UTaDXBJeox = false;}
      if(TltshSqnPL == true){TltshSqnPL = false;}
      if(jzDYrbbUUQ == true){jzDYrbbUUQ = false;}
      if(mtgWWTEtLc == true){mtgWWTEtLc = false;}
      if(hNRPbDSjYV == true){hNRPbDSjYV = false;}
      if(sTDKNVQBLw == true){sTDKNVQBLw = false;}
      if(ZoKXJYEWVN == true){ZoKXJYEWVN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VSUUVKVGTO
{ 
  void pefGxJJmzD()
  { 
      bool qhZXHhtLDT = false;
      bool kSWHUWWnoZ = false;
      bool jHnNrPiFFX = false;
      bool VRAfoHVxzn = false;
      bool tzBZBpErhb = false;
      bool KlftGisMer = false;
      bool zoFfxSRqSN = false;
      bool BZnBfkGOLC = false;
      bool KqWcMjlFYG = false;
      bool OIRHoEsVbi = false;
      bool XNYUZkxeOV = false;
      bool beAcgHScSN = false;
      bool gMSLyrHgLa = false;
      bool qklcdxRBCb = false;
      bool lHqCeiInZg = false;
      bool lQCOCLuNVh = false;
      bool cQSmdqsXyj = false;
      bool oQZpbZVPgP = false;
      bool jTHenahWaS = false;
      bool BEfUzUoDYm = false;
      string KVKHNlnKhM;
      string gHKHbPJZVE;
      string rboVsbwCKE;
      string SqIPpMzAIC;
      string aZPjZqmVof;
      string xEUcYhfoOk;
      string okActpzuRP;
      string PIRTdRMEuC;
      string naNdGNWfpH;
      string fKlWNoZlpj;
      string qrEYPomBzG;
      string VbtLxOXWVf;
      string STEJjFVtFn;
      string raOLKwWnNR;
      string aVfilDQaYz;
      string RDPJQXmtnK;
      string SruLOuMhAB;
      string qiIEFxmUWf;
      string ouVGVoKEtm;
      string IbADzhaUUq;
      if(KVKHNlnKhM == qrEYPomBzG){qhZXHhtLDT = true;}
      else if(qrEYPomBzG == KVKHNlnKhM){XNYUZkxeOV = true;}
      if(gHKHbPJZVE == VbtLxOXWVf){kSWHUWWnoZ = true;}
      else if(VbtLxOXWVf == gHKHbPJZVE){beAcgHScSN = true;}
      if(rboVsbwCKE == STEJjFVtFn){jHnNrPiFFX = true;}
      else if(STEJjFVtFn == rboVsbwCKE){gMSLyrHgLa = true;}
      if(SqIPpMzAIC == raOLKwWnNR){VRAfoHVxzn = true;}
      else if(raOLKwWnNR == SqIPpMzAIC){qklcdxRBCb = true;}
      if(aZPjZqmVof == aVfilDQaYz){tzBZBpErhb = true;}
      else if(aVfilDQaYz == aZPjZqmVof){lHqCeiInZg = true;}
      if(xEUcYhfoOk == RDPJQXmtnK){KlftGisMer = true;}
      else if(RDPJQXmtnK == xEUcYhfoOk){lQCOCLuNVh = true;}
      if(okActpzuRP == SruLOuMhAB){zoFfxSRqSN = true;}
      else if(SruLOuMhAB == okActpzuRP){cQSmdqsXyj = true;}
      if(PIRTdRMEuC == qiIEFxmUWf){BZnBfkGOLC = true;}
      if(naNdGNWfpH == ouVGVoKEtm){KqWcMjlFYG = true;}
      if(fKlWNoZlpj == IbADzhaUUq){OIRHoEsVbi = true;}
      while(qiIEFxmUWf == PIRTdRMEuC){oQZpbZVPgP = true;}
      while(ouVGVoKEtm == ouVGVoKEtm){jTHenahWaS = true;}
      while(IbADzhaUUq == IbADzhaUUq){BEfUzUoDYm = true;}
      if(qhZXHhtLDT == true){qhZXHhtLDT = false;}
      if(kSWHUWWnoZ == true){kSWHUWWnoZ = false;}
      if(jHnNrPiFFX == true){jHnNrPiFFX = false;}
      if(VRAfoHVxzn == true){VRAfoHVxzn = false;}
      if(tzBZBpErhb == true){tzBZBpErhb = false;}
      if(KlftGisMer == true){KlftGisMer = false;}
      if(zoFfxSRqSN == true){zoFfxSRqSN = false;}
      if(BZnBfkGOLC == true){BZnBfkGOLC = false;}
      if(KqWcMjlFYG == true){KqWcMjlFYG = false;}
      if(OIRHoEsVbi == true){OIRHoEsVbi = false;}
      if(XNYUZkxeOV == true){XNYUZkxeOV = false;}
      if(beAcgHScSN == true){beAcgHScSN = false;}
      if(gMSLyrHgLa == true){gMSLyrHgLa = false;}
      if(qklcdxRBCb == true){qklcdxRBCb = false;}
      if(lHqCeiInZg == true){lHqCeiInZg = false;}
      if(lQCOCLuNVh == true){lQCOCLuNVh = false;}
      if(cQSmdqsXyj == true){cQSmdqsXyj = false;}
      if(oQZpbZVPgP == true){oQZpbZVPgP = false;}
      if(jTHenahWaS == true){jTHenahWaS = false;}
      if(BEfUzUoDYm == true){BEfUzUoDYm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KXMOLARRTQ
{ 
  void HjEbIzYNco()
  { 
      bool wQIxDhOoKb = false;
      bool gCPocmFGYf = false;
      bool FQTTgYwqwf = false;
      bool OfZygPAmeF = false;
      bool BxwglwNgRp = false;
      bool VSdchewnQd = false;
      bool kXrdNAbRIM = false;
      bool lSaSdHUmgj = false;
      bool KPYFJuCxQC = false;
      bool TMVBUdFRTl = false;
      bool TwYEDDqKza = false;
      bool JJGgSUylTR = false;
      bool yeAFsZwZyA = false;
      bool CDSuPOqUCG = false;
      bool EqxorKFohz = false;
      bool eSxBmouSLc = false;
      bool GQMyYGpKQE = false;
      bool cdjNNGgLNi = false;
      bool UHryVjFRIa = false;
      bool TYJYzmeyQk = false;
      string uNANbwqXVh;
      string ulBRjPYkBV;
      string cqCFlxMeuA;
      string lzTrbZrxaY;
      string WTfmNikKZH;
      string aPGBXDKtbe;
      string jMcVwuSJpK;
      string XaKczILPqC;
      string MBEmYWrSUX;
      string OxVunJpKqS;
      string QaUOjAEdCO;
      string ruCYRiIoxY;
      string CzoRwaEOno;
      string RAXYkkfoDX;
      string ROPFfStwdF;
      string BBNRPQlCSJ;
      string upoMwrWdnf;
      string CSlYHnjilc;
      string fIjhnQlGJT;
      string zdVtcbZDIm;
      if(uNANbwqXVh == QaUOjAEdCO){wQIxDhOoKb = true;}
      else if(QaUOjAEdCO == uNANbwqXVh){TwYEDDqKza = true;}
      if(ulBRjPYkBV == ruCYRiIoxY){gCPocmFGYf = true;}
      else if(ruCYRiIoxY == ulBRjPYkBV){JJGgSUylTR = true;}
      if(cqCFlxMeuA == CzoRwaEOno){FQTTgYwqwf = true;}
      else if(CzoRwaEOno == cqCFlxMeuA){yeAFsZwZyA = true;}
      if(lzTrbZrxaY == RAXYkkfoDX){OfZygPAmeF = true;}
      else if(RAXYkkfoDX == lzTrbZrxaY){CDSuPOqUCG = true;}
      if(WTfmNikKZH == ROPFfStwdF){BxwglwNgRp = true;}
      else if(ROPFfStwdF == WTfmNikKZH){EqxorKFohz = true;}
      if(aPGBXDKtbe == BBNRPQlCSJ){VSdchewnQd = true;}
      else if(BBNRPQlCSJ == aPGBXDKtbe){eSxBmouSLc = true;}
      if(jMcVwuSJpK == upoMwrWdnf){kXrdNAbRIM = true;}
      else if(upoMwrWdnf == jMcVwuSJpK){GQMyYGpKQE = true;}
      if(XaKczILPqC == CSlYHnjilc){lSaSdHUmgj = true;}
      if(MBEmYWrSUX == fIjhnQlGJT){KPYFJuCxQC = true;}
      if(OxVunJpKqS == zdVtcbZDIm){TMVBUdFRTl = true;}
      while(CSlYHnjilc == XaKczILPqC){cdjNNGgLNi = true;}
      while(fIjhnQlGJT == fIjhnQlGJT){UHryVjFRIa = true;}
      while(zdVtcbZDIm == zdVtcbZDIm){TYJYzmeyQk = true;}
      if(wQIxDhOoKb == true){wQIxDhOoKb = false;}
      if(gCPocmFGYf == true){gCPocmFGYf = false;}
      if(FQTTgYwqwf == true){FQTTgYwqwf = false;}
      if(OfZygPAmeF == true){OfZygPAmeF = false;}
      if(BxwglwNgRp == true){BxwglwNgRp = false;}
      if(VSdchewnQd == true){VSdchewnQd = false;}
      if(kXrdNAbRIM == true){kXrdNAbRIM = false;}
      if(lSaSdHUmgj == true){lSaSdHUmgj = false;}
      if(KPYFJuCxQC == true){KPYFJuCxQC = false;}
      if(TMVBUdFRTl == true){TMVBUdFRTl = false;}
      if(TwYEDDqKza == true){TwYEDDqKza = false;}
      if(JJGgSUylTR == true){JJGgSUylTR = false;}
      if(yeAFsZwZyA == true){yeAFsZwZyA = false;}
      if(CDSuPOqUCG == true){CDSuPOqUCG = false;}
      if(EqxorKFohz == true){EqxorKFohz = false;}
      if(eSxBmouSLc == true){eSxBmouSLc = false;}
      if(GQMyYGpKQE == true){GQMyYGpKQE = false;}
      if(cdjNNGgLNi == true){cdjNNGgLNi = false;}
      if(UHryVjFRIa == true){UHryVjFRIa = false;}
      if(TYJYzmeyQk == true){TYJYzmeyQk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HZUQTHMTMO
{ 
  void BcctHnAJOZ()
  { 
      bool kHWLPcMZok = false;
      bool gwIfXGMFgI = false;
      bool zHKZJYgRiK = false;
      bool BKKGnmXqHB = false;
      bool IisAubTpMr = false;
      bool EfpMrcwwBq = false;
      bool wtqejVkCrk = false;
      bool hVxezPNKeg = false;
      bool FqFqFUTxOK = false;
      bool qboQEOrOQY = false;
      bool qQxbKhiKMb = false;
      bool PkRUkFoAYO = false;
      bool BmmhsGgfZk = false;
      bool XztGpnsdfW = false;
      bool lIkluFJTez = false;
      bool YroBWDdPhD = false;
      bool BCjaEPqKdx = false;
      bool LKTBcsCBlm = false;
      bool wMBaMeJsil = false;
      bool JducVjXJge = false;
      string ASnsMEPUob;
      string YVotAMXrUs;
      string CLBwbTbDtg;
      string aoyoRiCjUe;
      string WuAaKDIjWZ;
      string JhIrXnQrRs;
      string cLZHBjWzcR;
      string JmWpVHLZkX;
      string KqgTXrgFRc;
      string RKSbCKVrZa;
      string gJHFQWLRWQ;
      string bpGshkeFjI;
      string CRgzzyUunK;
      string kSAJqAjbDB;
      string gPiAAaDYsQ;
      string fPIQXObHFS;
      string BPcLeJpwCh;
      string BDCibmhfyY;
      string tuCXeVJikb;
      string XbVjzRlXVq;
      if(ASnsMEPUob == gJHFQWLRWQ){kHWLPcMZok = true;}
      else if(gJHFQWLRWQ == ASnsMEPUob){qQxbKhiKMb = true;}
      if(YVotAMXrUs == bpGshkeFjI){gwIfXGMFgI = true;}
      else if(bpGshkeFjI == YVotAMXrUs){PkRUkFoAYO = true;}
      if(CLBwbTbDtg == CRgzzyUunK){zHKZJYgRiK = true;}
      else if(CRgzzyUunK == CLBwbTbDtg){BmmhsGgfZk = true;}
      if(aoyoRiCjUe == kSAJqAjbDB){BKKGnmXqHB = true;}
      else if(kSAJqAjbDB == aoyoRiCjUe){XztGpnsdfW = true;}
      if(WuAaKDIjWZ == gPiAAaDYsQ){IisAubTpMr = true;}
      else if(gPiAAaDYsQ == WuAaKDIjWZ){lIkluFJTez = true;}
      if(JhIrXnQrRs == fPIQXObHFS){EfpMrcwwBq = true;}
      else if(fPIQXObHFS == JhIrXnQrRs){YroBWDdPhD = true;}
      if(cLZHBjWzcR == BPcLeJpwCh){wtqejVkCrk = true;}
      else if(BPcLeJpwCh == cLZHBjWzcR){BCjaEPqKdx = true;}
      if(JmWpVHLZkX == BDCibmhfyY){hVxezPNKeg = true;}
      if(KqgTXrgFRc == tuCXeVJikb){FqFqFUTxOK = true;}
      if(RKSbCKVrZa == XbVjzRlXVq){qboQEOrOQY = true;}
      while(BDCibmhfyY == JmWpVHLZkX){LKTBcsCBlm = true;}
      while(tuCXeVJikb == tuCXeVJikb){wMBaMeJsil = true;}
      while(XbVjzRlXVq == XbVjzRlXVq){JducVjXJge = true;}
      if(kHWLPcMZok == true){kHWLPcMZok = false;}
      if(gwIfXGMFgI == true){gwIfXGMFgI = false;}
      if(zHKZJYgRiK == true){zHKZJYgRiK = false;}
      if(BKKGnmXqHB == true){BKKGnmXqHB = false;}
      if(IisAubTpMr == true){IisAubTpMr = false;}
      if(EfpMrcwwBq == true){EfpMrcwwBq = false;}
      if(wtqejVkCrk == true){wtqejVkCrk = false;}
      if(hVxezPNKeg == true){hVxezPNKeg = false;}
      if(FqFqFUTxOK == true){FqFqFUTxOK = false;}
      if(qboQEOrOQY == true){qboQEOrOQY = false;}
      if(qQxbKhiKMb == true){qQxbKhiKMb = false;}
      if(PkRUkFoAYO == true){PkRUkFoAYO = false;}
      if(BmmhsGgfZk == true){BmmhsGgfZk = false;}
      if(XztGpnsdfW == true){XztGpnsdfW = false;}
      if(lIkluFJTez == true){lIkluFJTez = false;}
      if(YroBWDdPhD == true){YroBWDdPhD = false;}
      if(BCjaEPqKdx == true){BCjaEPqKdx = false;}
      if(LKTBcsCBlm == true){LKTBcsCBlm = false;}
      if(wMBaMeJsil == true){wMBaMeJsil = false;}
      if(JducVjXJge == true){JducVjXJge = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YQNTCRFJLP
{ 
  void jTJAPQhhKz()
  { 
      bool JJQMiBiLIE = false;
      bool grbqfoasLU = false;
      bool bBCsknXLpg = false;
      bool QHMqCKBNyR = false;
      bool UQRIOltVSn = false;
      bool SDfyOIHXat = false;
      bool dXVbmZfjoV = false;
      bool nMttAKisdz = false;
      bool sCrCNMaNcs = false;
      bool DdmEmxuoUn = false;
      bool GKfxAFJlyD = false;
      bool ZOsbAbeSOa = false;
      bool zSHuSJZoHD = false;
      bool PsXpsiVuBH = false;
      bool DoOYTnjKDL = false;
      bool RbatomCkep = false;
      bool fTdumfqDiR = false;
      bool GjQHWJDhbd = false;
      bool ZPlwknScAF = false;
      bool fjQLbiKSkm = false;
      string NpkZHFOQbO;
      string HSmyzSbHPA;
      string UGmDWorsIB;
      string wsluNaCcLA;
      string HPMXSmoXZL;
      string gySddGCgDR;
      string NUIaSNgqjX;
      string PzuPsFtPkj;
      string AUTwTxaIRH;
      string YVZsmmGlEE;
      string FxmCuhCDkX;
      string MmwSRrBLGU;
      string lXYcytYBbF;
      string zIKfdCgQAl;
      string tXXstlZGbt;
      string ltfiShXKDB;
      string IAaeYEbPoP;
      string LjKTaNAfhM;
      string USZhSEbaNw;
      string dWMzdsxrTp;
      if(NpkZHFOQbO == FxmCuhCDkX){JJQMiBiLIE = true;}
      else if(FxmCuhCDkX == NpkZHFOQbO){GKfxAFJlyD = true;}
      if(HSmyzSbHPA == MmwSRrBLGU){grbqfoasLU = true;}
      else if(MmwSRrBLGU == HSmyzSbHPA){ZOsbAbeSOa = true;}
      if(UGmDWorsIB == lXYcytYBbF){bBCsknXLpg = true;}
      else if(lXYcytYBbF == UGmDWorsIB){zSHuSJZoHD = true;}
      if(wsluNaCcLA == zIKfdCgQAl){QHMqCKBNyR = true;}
      else if(zIKfdCgQAl == wsluNaCcLA){PsXpsiVuBH = true;}
      if(HPMXSmoXZL == tXXstlZGbt){UQRIOltVSn = true;}
      else if(tXXstlZGbt == HPMXSmoXZL){DoOYTnjKDL = true;}
      if(gySddGCgDR == ltfiShXKDB){SDfyOIHXat = true;}
      else if(ltfiShXKDB == gySddGCgDR){RbatomCkep = true;}
      if(NUIaSNgqjX == IAaeYEbPoP){dXVbmZfjoV = true;}
      else if(IAaeYEbPoP == NUIaSNgqjX){fTdumfqDiR = true;}
      if(PzuPsFtPkj == LjKTaNAfhM){nMttAKisdz = true;}
      if(AUTwTxaIRH == USZhSEbaNw){sCrCNMaNcs = true;}
      if(YVZsmmGlEE == dWMzdsxrTp){DdmEmxuoUn = true;}
      while(LjKTaNAfhM == PzuPsFtPkj){GjQHWJDhbd = true;}
      while(USZhSEbaNw == USZhSEbaNw){ZPlwknScAF = true;}
      while(dWMzdsxrTp == dWMzdsxrTp){fjQLbiKSkm = true;}
      if(JJQMiBiLIE == true){JJQMiBiLIE = false;}
      if(grbqfoasLU == true){grbqfoasLU = false;}
      if(bBCsknXLpg == true){bBCsknXLpg = false;}
      if(QHMqCKBNyR == true){QHMqCKBNyR = false;}
      if(UQRIOltVSn == true){UQRIOltVSn = false;}
      if(SDfyOIHXat == true){SDfyOIHXat = false;}
      if(dXVbmZfjoV == true){dXVbmZfjoV = false;}
      if(nMttAKisdz == true){nMttAKisdz = false;}
      if(sCrCNMaNcs == true){sCrCNMaNcs = false;}
      if(DdmEmxuoUn == true){DdmEmxuoUn = false;}
      if(GKfxAFJlyD == true){GKfxAFJlyD = false;}
      if(ZOsbAbeSOa == true){ZOsbAbeSOa = false;}
      if(zSHuSJZoHD == true){zSHuSJZoHD = false;}
      if(PsXpsiVuBH == true){PsXpsiVuBH = false;}
      if(DoOYTnjKDL == true){DoOYTnjKDL = false;}
      if(RbatomCkep == true){RbatomCkep = false;}
      if(fTdumfqDiR == true){fTdumfqDiR = false;}
      if(GjQHWJDhbd == true){GjQHWJDhbd = false;}
      if(ZPlwknScAF == true){ZPlwknScAF = false;}
      if(fjQLbiKSkm == true){fjQLbiKSkm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JVGTYLJCPS
{ 
  void GZCLUyGFfc()
  { 
      bool SRdRIIIGWP = false;
      bool gZNbozPPxD = false;
      bool GiiDwujwMh = false;
      bool YRKaJsqhdA = false;
      bool qFfrADhNFM = false;
      bool jMRyrjhZVM = false;
      bool XLsopOPmSu = false;
      bool HgkwMBCpDs = false;
      bool NVqAyMzLhZ = false;
      bool LRMRbeLpCk = false;
      bool mtuKFCaUkq = false;
      bool gqVbzCUsqd = false;
      bool ODFsipUTUh = false;
      bool pMnSFTZfuu = false;
      bool keZqrUujRZ = false;
      bool KRzXVioCaP = false;
      bool hHADAUCDWf = false;
      bool bnyurjcOAO = false;
      bool tjBuWXMPwV = false;
      bool dXFeNcdWpX = false;
      string qaPbJPjiJS;
      string WVZmXPKNhn;
      string cDaXoAVngS;
      string AWDzQuTgpT;
      string woaTzfeELR;
      string hdCmpmzqmJ;
      string suCpSARaWb;
      string wdWNqmcHYI;
      string URcPkVTQIc;
      string wbsfaAmkAy;
      string OEgiUEGowD;
      string KrSeoaSlFw;
      string gBRsfUjqlp;
      string AqGZtPjsuf;
      string OeUFSDJOqz;
      string hAfERNlnDA;
      string UPCFDSkrkY;
      string qZqYgBgMZb;
      string KVAmIzLCIg;
      string cuotLzbOCz;
      if(qaPbJPjiJS == OEgiUEGowD){SRdRIIIGWP = true;}
      else if(OEgiUEGowD == qaPbJPjiJS){mtuKFCaUkq = true;}
      if(WVZmXPKNhn == KrSeoaSlFw){gZNbozPPxD = true;}
      else if(KrSeoaSlFw == WVZmXPKNhn){gqVbzCUsqd = true;}
      if(cDaXoAVngS == gBRsfUjqlp){GiiDwujwMh = true;}
      else if(gBRsfUjqlp == cDaXoAVngS){ODFsipUTUh = true;}
      if(AWDzQuTgpT == AqGZtPjsuf){YRKaJsqhdA = true;}
      else if(AqGZtPjsuf == AWDzQuTgpT){pMnSFTZfuu = true;}
      if(woaTzfeELR == OeUFSDJOqz){qFfrADhNFM = true;}
      else if(OeUFSDJOqz == woaTzfeELR){keZqrUujRZ = true;}
      if(hdCmpmzqmJ == hAfERNlnDA){jMRyrjhZVM = true;}
      else if(hAfERNlnDA == hdCmpmzqmJ){KRzXVioCaP = true;}
      if(suCpSARaWb == UPCFDSkrkY){XLsopOPmSu = true;}
      else if(UPCFDSkrkY == suCpSARaWb){hHADAUCDWf = true;}
      if(wdWNqmcHYI == qZqYgBgMZb){HgkwMBCpDs = true;}
      if(URcPkVTQIc == KVAmIzLCIg){NVqAyMzLhZ = true;}
      if(wbsfaAmkAy == cuotLzbOCz){LRMRbeLpCk = true;}
      while(qZqYgBgMZb == wdWNqmcHYI){bnyurjcOAO = true;}
      while(KVAmIzLCIg == KVAmIzLCIg){tjBuWXMPwV = true;}
      while(cuotLzbOCz == cuotLzbOCz){dXFeNcdWpX = true;}
      if(SRdRIIIGWP == true){SRdRIIIGWP = false;}
      if(gZNbozPPxD == true){gZNbozPPxD = false;}
      if(GiiDwujwMh == true){GiiDwujwMh = false;}
      if(YRKaJsqhdA == true){YRKaJsqhdA = false;}
      if(qFfrADhNFM == true){qFfrADhNFM = false;}
      if(jMRyrjhZVM == true){jMRyrjhZVM = false;}
      if(XLsopOPmSu == true){XLsopOPmSu = false;}
      if(HgkwMBCpDs == true){HgkwMBCpDs = false;}
      if(NVqAyMzLhZ == true){NVqAyMzLhZ = false;}
      if(LRMRbeLpCk == true){LRMRbeLpCk = false;}
      if(mtuKFCaUkq == true){mtuKFCaUkq = false;}
      if(gqVbzCUsqd == true){gqVbzCUsqd = false;}
      if(ODFsipUTUh == true){ODFsipUTUh = false;}
      if(pMnSFTZfuu == true){pMnSFTZfuu = false;}
      if(keZqrUujRZ == true){keZqrUujRZ = false;}
      if(KRzXVioCaP == true){KRzXVioCaP = false;}
      if(hHADAUCDWf == true){hHADAUCDWf = false;}
      if(bnyurjcOAO == true){bnyurjcOAO = false;}
      if(tjBuWXMPwV == true){tjBuWXMPwV = false;}
      if(dXFeNcdWpX == true){dXFeNcdWpX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QBICYAVKYO
{ 
  void EGjhbCaDKJ()
  { 
      bool HdhsFDhmWf = false;
      bool asyIexexAy = false;
      bool bFugWgASQy = false;
      bool aQQPGmUZrw = false;
      bool kcuLrjZXxM = false;
      bool ouIbDCiAWX = false;
      bool COWXEKchCr = false;
      bool cEEDMyJiom = false;
      bool HbVEJeHnMD = false;
      bool EUDUsVGXGg = false;
      bool HqVFijqFOE = false;
      bool rzLiPasSOZ = false;
      bool DnVymIBjKp = false;
      bool qkbHfQGPUY = false;
      bool nCYHLEIUES = false;
      bool cnJgdTUWRa = false;
      bool iGtYMGXEDy = false;
      bool UcxokBOOmi = false;
      bool zffqNDbtcL = false;
      bool uiysphHAtE = false;
      string UGixwDwmZw;
      string kOLIjAdjai;
      string WTnFTxCpMk;
      string XlkTueXjKi;
      string bZnBGNMYVH;
      string jntqMBSccz;
      string BFZnXycrMF;
      string ctZqGxelzF;
      string jdUEBjqtHt;
      string LtGKhVzAdH;
      string jULQeoODjO;
      string WfdWPWkVln;
      string HijSshmOIj;
      string xdIqUORDZL;
      string UmJrWfQjtK;
      string kdNpzBksWw;
      string BztARrXlBA;
      string FguaSTZquN;
      string RDTxzTQSqT;
      string dXgcKUsJae;
      if(UGixwDwmZw == jULQeoODjO){HdhsFDhmWf = true;}
      else if(jULQeoODjO == UGixwDwmZw){HqVFijqFOE = true;}
      if(kOLIjAdjai == WfdWPWkVln){asyIexexAy = true;}
      else if(WfdWPWkVln == kOLIjAdjai){rzLiPasSOZ = true;}
      if(WTnFTxCpMk == HijSshmOIj){bFugWgASQy = true;}
      else if(HijSshmOIj == WTnFTxCpMk){DnVymIBjKp = true;}
      if(XlkTueXjKi == xdIqUORDZL){aQQPGmUZrw = true;}
      else if(xdIqUORDZL == XlkTueXjKi){qkbHfQGPUY = true;}
      if(bZnBGNMYVH == UmJrWfQjtK){kcuLrjZXxM = true;}
      else if(UmJrWfQjtK == bZnBGNMYVH){nCYHLEIUES = true;}
      if(jntqMBSccz == kdNpzBksWw){ouIbDCiAWX = true;}
      else if(kdNpzBksWw == jntqMBSccz){cnJgdTUWRa = true;}
      if(BFZnXycrMF == BztARrXlBA){COWXEKchCr = true;}
      else if(BztARrXlBA == BFZnXycrMF){iGtYMGXEDy = true;}
      if(ctZqGxelzF == FguaSTZquN){cEEDMyJiom = true;}
      if(jdUEBjqtHt == RDTxzTQSqT){HbVEJeHnMD = true;}
      if(LtGKhVzAdH == dXgcKUsJae){EUDUsVGXGg = true;}
      while(FguaSTZquN == ctZqGxelzF){UcxokBOOmi = true;}
      while(RDTxzTQSqT == RDTxzTQSqT){zffqNDbtcL = true;}
      while(dXgcKUsJae == dXgcKUsJae){uiysphHAtE = true;}
      if(HdhsFDhmWf == true){HdhsFDhmWf = false;}
      if(asyIexexAy == true){asyIexexAy = false;}
      if(bFugWgASQy == true){bFugWgASQy = false;}
      if(aQQPGmUZrw == true){aQQPGmUZrw = false;}
      if(kcuLrjZXxM == true){kcuLrjZXxM = false;}
      if(ouIbDCiAWX == true){ouIbDCiAWX = false;}
      if(COWXEKchCr == true){COWXEKchCr = false;}
      if(cEEDMyJiom == true){cEEDMyJiom = false;}
      if(HbVEJeHnMD == true){HbVEJeHnMD = false;}
      if(EUDUsVGXGg == true){EUDUsVGXGg = false;}
      if(HqVFijqFOE == true){HqVFijqFOE = false;}
      if(rzLiPasSOZ == true){rzLiPasSOZ = false;}
      if(DnVymIBjKp == true){DnVymIBjKp = false;}
      if(qkbHfQGPUY == true){qkbHfQGPUY = false;}
      if(nCYHLEIUES == true){nCYHLEIUES = false;}
      if(cnJgdTUWRa == true){cnJgdTUWRa = false;}
      if(iGtYMGXEDy == true){iGtYMGXEDy = false;}
      if(UcxokBOOmi == true){UcxokBOOmi = false;}
      if(zffqNDbtcL == true){zffqNDbtcL = false;}
      if(uiysphHAtE == true){uiysphHAtE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EPOSJGCQGE
{ 
  void bCnafKJlof()
  { 
      bool WWubMbLVxM = false;
      bool aohQxDNdQh = false;
      bool LfoYkYmwaH = false;
      bool efozQpXlth = false;
      bool uepJLKZPWZ = false;
      bool VfXxOphWqm = false;
      bool oOtphtzhzG = false;
      bool eaiimgpfMZ = false;
      bool zXZBkzHqkZ = false;
      bool IBtGsfjAbQ = false;
      bool KrPPutwoKg = false;
      bool ACJQnQnrEi = false;
      bool lHwZxdgcoG = false;
      bool woEwPHIJGp = false;
      bool CSgDYGrcRb = false;
      bool qrusdCuoRR = false;
      bool NTADkLxMAg = false;
      bool IelOfTarBq = false;
      bool kDKNOEtLSN = false;
      bool LSrnciRcSN = false;
      string bjAFpSprSK;
      string aZEzRaskPb;
      string KjWHpplTKS;
      string uLnVPzKRFW;
      string VEeFzVhDAX;
      string XgencqNrPA;
      string fWhzPPlhjR;
      string PberGFFRIT;
      string HiSluNgzrX;
      string lSCEqzWepj;
      string jzTiHwClhX;
      string lujurxDuEC;
      string imoLewZZBG;
      string habXjIPjez;
      string LtQUlqiGLt;
      string ubZnBxJHEK;
      string VbkboLTLLj;
      string gTQEpnVUZm;
      string NSOHKGAmWm;
      string zHfTciJofZ;
      if(bjAFpSprSK == jzTiHwClhX){WWubMbLVxM = true;}
      else if(jzTiHwClhX == bjAFpSprSK){KrPPutwoKg = true;}
      if(aZEzRaskPb == lujurxDuEC){aohQxDNdQh = true;}
      else if(lujurxDuEC == aZEzRaskPb){ACJQnQnrEi = true;}
      if(KjWHpplTKS == imoLewZZBG){LfoYkYmwaH = true;}
      else if(imoLewZZBG == KjWHpplTKS){lHwZxdgcoG = true;}
      if(uLnVPzKRFW == habXjIPjez){efozQpXlth = true;}
      else if(habXjIPjez == uLnVPzKRFW){woEwPHIJGp = true;}
      if(VEeFzVhDAX == LtQUlqiGLt){uepJLKZPWZ = true;}
      else if(LtQUlqiGLt == VEeFzVhDAX){CSgDYGrcRb = true;}
      if(XgencqNrPA == ubZnBxJHEK){VfXxOphWqm = true;}
      else if(ubZnBxJHEK == XgencqNrPA){qrusdCuoRR = true;}
      if(fWhzPPlhjR == VbkboLTLLj){oOtphtzhzG = true;}
      else if(VbkboLTLLj == fWhzPPlhjR){NTADkLxMAg = true;}
      if(PberGFFRIT == gTQEpnVUZm){eaiimgpfMZ = true;}
      if(HiSluNgzrX == NSOHKGAmWm){zXZBkzHqkZ = true;}
      if(lSCEqzWepj == zHfTciJofZ){IBtGsfjAbQ = true;}
      while(gTQEpnVUZm == PberGFFRIT){IelOfTarBq = true;}
      while(NSOHKGAmWm == NSOHKGAmWm){kDKNOEtLSN = true;}
      while(zHfTciJofZ == zHfTciJofZ){LSrnciRcSN = true;}
      if(WWubMbLVxM == true){WWubMbLVxM = false;}
      if(aohQxDNdQh == true){aohQxDNdQh = false;}
      if(LfoYkYmwaH == true){LfoYkYmwaH = false;}
      if(efozQpXlth == true){efozQpXlth = false;}
      if(uepJLKZPWZ == true){uepJLKZPWZ = false;}
      if(VfXxOphWqm == true){VfXxOphWqm = false;}
      if(oOtphtzhzG == true){oOtphtzhzG = false;}
      if(eaiimgpfMZ == true){eaiimgpfMZ = false;}
      if(zXZBkzHqkZ == true){zXZBkzHqkZ = false;}
      if(IBtGsfjAbQ == true){IBtGsfjAbQ = false;}
      if(KrPPutwoKg == true){KrPPutwoKg = false;}
      if(ACJQnQnrEi == true){ACJQnQnrEi = false;}
      if(lHwZxdgcoG == true){lHwZxdgcoG = false;}
      if(woEwPHIJGp == true){woEwPHIJGp = false;}
      if(CSgDYGrcRb == true){CSgDYGrcRb = false;}
      if(qrusdCuoRR == true){qrusdCuoRR = false;}
      if(NTADkLxMAg == true){NTADkLxMAg = false;}
      if(IelOfTarBq == true){IelOfTarBq = false;}
      if(kDKNOEtLSN == true){kDKNOEtLSN = false;}
      if(LSrnciRcSN == true){LSrnciRcSN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MAUQJEFRQX
{ 
  void oEpphxbWVy()
  { 
      bool jgtBMtNOfP = false;
      bool IImcoDIdnC = false;
      bool XCOzDZEAaK = false;
      bool zaFyfwsVhp = false;
      bool hbRHkZAcuw = false;
      bool JsdcegRtym = false;
      bool pMnVPhCows = false;
      bool KlwyUukHOc = false;
      bool YaFdAFwbTz = false;
      bool dyXuAUnuqC = false;
      bool WLfBlWxfIi = false;
      bool uKeUNOHKUJ = false;
      bool laVxPLNBxz = false;
      bool HoPLGNuDqd = false;
      bool IQTjDTTCgl = false;
      bool NcahQwpila = false;
      bool IwiIbGtSOA = false;
      bool TDSqBVGksw = false;
      bool rLTLldOhuK = false;
      bool XLQQUMgLHx = false;
      string HlKBbwnIDL;
      string hefghzNMXd;
      string hVoqXcXiyd;
      string tUiwAojHAn;
      string VzgzWlrnne;
      string WEdYalwScy;
      string XFJYQMwjgs;
      string OFMjHiooUl;
      string kitTHpqJUO;
      string rReBPQoHiJ;
      string oIGtPQqsQq;
      string wHxqNoKpRa;
      string VlOSBxaLUq;
      string tgGLwbbAEp;
      string yxscRkTnmZ;
      string FzpInCsnsS;
      string pfYZxOAltl;
      string NKlabXskAQ;
      string cmXtkuqxWt;
      string hmGkARXSfC;
      if(HlKBbwnIDL == oIGtPQqsQq){jgtBMtNOfP = true;}
      else if(oIGtPQqsQq == HlKBbwnIDL){WLfBlWxfIi = true;}
      if(hefghzNMXd == wHxqNoKpRa){IImcoDIdnC = true;}
      else if(wHxqNoKpRa == hefghzNMXd){uKeUNOHKUJ = true;}
      if(hVoqXcXiyd == VlOSBxaLUq){XCOzDZEAaK = true;}
      else if(VlOSBxaLUq == hVoqXcXiyd){laVxPLNBxz = true;}
      if(tUiwAojHAn == tgGLwbbAEp){zaFyfwsVhp = true;}
      else if(tgGLwbbAEp == tUiwAojHAn){HoPLGNuDqd = true;}
      if(VzgzWlrnne == yxscRkTnmZ){hbRHkZAcuw = true;}
      else if(yxscRkTnmZ == VzgzWlrnne){IQTjDTTCgl = true;}
      if(WEdYalwScy == FzpInCsnsS){JsdcegRtym = true;}
      else if(FzpInCsnsS == WEdYalwScy){NcahQwpila = true;}
      if(XFJYQMwjgs == pfYZxOAltl){pMnVPhCows = true;}
      else if(pfYZxOAltl == XFJYQMwjgs){IwiIbGtSOA = true;}
      if(OFMjHiooUl == NKlabXskAQ){KlwyUukHOc = true;}
      if(kitTHpqJUO == cmXtkuqxWt){YaFdAFwbTz = true;}
      if(rReBPQoHiJ == hmGkARXSfC){dyXuAUnuqC = true;}
      while(NKlabXskAQ == OFMjHiooUl){TDSqBVGksw = true;}
      while(cmXtkuqxWt == cmXtkuqxWt){rLTLldOhuK = true;}
      while(hmGkARXSfC == hmGkARXSfC){XLQQUMgLHx = true;}
      if(jgtBMtNOfP == true){jgtBMtNOfP = false;}
      if(IImcoDIdnC == true){IImcoDIdnC = false;}
      if(XCOzDZEAaK == true){XCOzDZEAaK = false;}
      if(zaFyfwsVhp == true){zaFyfwsVhp = false;}
      if(hbRHkZAcuw == true){hbRHkZAcuw = false;}
      if(JsdcegRtym == true){JsdcegRtym = false;}
      if(pMnVPhCows == true){pMnVPhCows = false;}
      if(KlwyUukHOc == true){KlwyUukHOc = false;}
      if(YaFdAFwbTz == true){YaFdAFwbTz = false;}
      if(dyXuAUnuqC == true){dyXuAUnuqC = false;}
      if(WLfBlWxfIi == true){WLfBlWxfIi = false;}
      if(uKeUNOHKUJ == true){uKeUNOHKUJ = false;}
      if(laVxPLNBxz == true){laVxPLNBxz = false;}
      if(HoPLGNuDqd == true){HoPLGNuDqd = false;}
      if(IQTjDTTCgl == true){IQTjDTTCgl = false;}
      if(NcahQwpila == true){NcahQwpila = false;}
      if(IwiIbGtSOA == true){IwiIbGtSOA = false;}
      if(TDSqBVGksw == true){TDSqBVGksw = false;}
      if(rLTLldOhuK == true){rLTLldOhuK = false;}
      if(XLQQUMgLHx == true){XLQQUMgLHx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UOMHWLIMTS
{ 
  void CclQmHQWqJ()
  { 
      bool WalwbaJpKb = false;
      bool VBiWmbDmTP = false;
      bool axjnQCulIV = false;
      bool IxjrZBZuHy = false;
      bool yNXcylEZaT = false;
      bool njnaxYpxfZ = false;
      bool eXhnTXRqxk = false;
      bool BIeVQMZGpe = false;
      bool xVKnhXIItA = false;
      bool KbOhSafiJZ = false;
      bool UMboReESJk = false;
      bool zjHAbJMsGu = false;
      bool PIxwZZswCp = false;
      bool gpxPKjsVWC = false;
      bool ToyJBaUOFJ = false;
      bool NlcNKLPfPr = false;
      bool lHPTEIlqpq = false;
      bool PqWDbZJmty = false;
      bool EdqsctNjFy = false;
      bool TNFeQLZeFs = false;
      string rsXrgXkXzy;
      string kklythqYin;
      string BgcXHkjrJg;
      string XqqttFTjOk;
      string UzAybcHZHW;
      string CyXEqLQzju;
      string nsNRZtsqEn;
      string NHKyTCgdwe;
      string dJjleZTlDi;
      string oUASwbkhXh;
      string iPVTIumYko;
      string elDERdIbmA;
      string ZHnUzsGrBr;
      string QyGNwNnQci;
      string ltBNECQuAR;
      string SItXHbaATP;
      string nuWsXffpID;
      string przDNfFZQw;
      string cLqjYIEhFT;
      string mnwNuqWIpY;
      if(rsXrgXkXzy == iPVTIumYko){WalwbaJpKb = true;}
      else if(iPVTIumYko == rsXrgXkXzy){UMboReESJk = true;}
      if(kklythqYin == elDERdIbmA){VBiWmbDmTP = true;}
      else if(elDERdIbmA == kklythqYin){zjHAbJMsGu = true;}
      if(BgcXHkjrJg == ZHnUzsGrBr){axjnQCulIV = true;}
      else if(ZHnUzsGrBr == BgcXHkjrJg){PIxwZZswCp = true;}
      if(XqqttFTjOk == QyGNwNnQci){IxjrZBZuHy = true;}
      else if(QyGNwNnQci == XqqttFTjOk){gpxPKjsVWC = true;}
      if(UzAybcHZHW == ltBNECQuAR){yNXcylEZaT = true;}
      else if(ltBNECQuAR == UzAybcHZHW){ToyJBaUOFJ = true;}
      if(CyXEqLQzju == SItXHbaATP){njnaxYpxfZ = true;}
      else if(SItXHbaATP == CyXEqLQzju){NlcNKLPfPr = true;}
      if(nsNRZtsqEn == nuWsXffpID){eXhnTXRqxk = true;}
      else if(nuWsXffpID == nsNRZtsqEn){lHPTEIlqpq = true;}
      if(NHKyTCgdwe == przDNfFZQw){BIeVQMZGpe = true;}
      if(dJjleZTlDi == cLqjYIEhFT){xVKnhXIItA = true;}
      if(oUASwbkhXh == mnwNuqWIpY){KbOhSafiJZ = true;}
      while(przDNfFZQw == NHKyTCgdwe){PqWDbZJmty = true;}
      while(cLqjYIEhFT == cLqjYIEhFT){EdqsctNjFy = true;}
      while(mnwNuqWIpY == mnwNuqWIpY){TNFeQLZeFs = true;}
      if(WalwbaJpKb == true){WalwbaJpKb = false;}
      if(VBiWmbDmTP == true){VBiWmbDmTP = false;}
      if(axjnQCulIV == true){axjnQCulIV = false;}
      if(IxjrZBZuHy == true){IxjrZBZuHy = false;}
      if(yNXcylEZaT == true){yNXcylEZaT = false;}
      if(njnaxYpxfZ == true){njnaxYpxfZ = false;}
      if(eXhnTXRqxk == true){eXhnTXRqxk = false;}
      if(BIeVQMZGpe == true){BIeVQMZGpe = false;}
      if(xVKnhXIItA == true){xVKnhXIItA = false;}
      if(KbOhSafiJZ == true){KbOhSafiJZ = false;}
      if(UMboReESJk == true){UMboReESJk = false;}
      if(zjHAbJMsGu == true){zjHAbJMsGu = false;}
      if(PIxwZZswCp == true){PIxwZZswCp = false;}
      if(gpxPKjsVWC == true){gpxPKjsVWC = false;}
      if(ToyJBaUOFJ == true){ToyJBaUOFJ = false;}
      if(NlcNKLPfPr == true){NlcNKLPfPr = false;}
      if(lHPTEIlqpq == true){lHPTEIlqpq = false;}
      if(PqWDbZJmty == true){PqWDbZJmty = false;}
      if(EdqsctNjFy == true){EdqsctNjFy = false;}
      if(TNFeQLZeFs == true){TNFeQLZeFs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TKREDUMGUY
{ 
  void GJuLLFklux()
  { 
      bool uKEpqfxAwA = false;
      bool sNIXXsVONq = false;
      bool QAUPMjOMIm = false;
      bool wJkkuOqWhC = false;
      bool YuBEuEHcse = false;
      bool tfuwOupocH = false;
      bool RkrIDjcXcJ = false;
      bool BzgLRUyPTH = false;
      bool bkScsPNnVz = false;
      bool YCsajnDsAL = false;
      bool bjAictzjes = false;
      bool xZUVegROPm = false;
      bool VoBckzGFac = false;
      bool REOIfrkjzz = false;
      bool QdIcBygXwD = false;
      bool WncMolhWyd = false;
      bool ntICarKMom = false;
      bool uhOQWrfYal = false;
      bool SiJWGdbCSs = false;
      bool KNkVKVUGBI = false;
      string WPraaCtLco;
      string OZdGNIcEuj;
      string DgTEgUoutY;
      string WuRpUlsINu;
      string bkdTmtARcW;
      string PHFjdpumsF;
      string NzQDRSHmkb;
      string PUpzHSCzRm;
      string TWRXIPphMd;
      string pFOHhcUaBU;
      string lNfBHuQFbL;
      string mwVFlpgstC;
      string bZZHkJFhQe;
      string xbxwBGpQPN;
      string yjGBqtjJVq;
      string wafzrMmYPy;
      string oinwNLyYEf;
      string APdfDrSYPq;
      string ZwMZiWuyEo;
      string SQBRXPuJne;
      if(WPraaCtLco == lNfBHuQFbL){uKEpqfxAwA = true;}
      else if(lNfBHuQFbL == WPraaCtLco){bjAictzjes = true;}
      if(OZdGNIcEuj == mwVFlpgstC){sNIXXsVONq = true;}
      else if(mwVFlpgstC == OZdGNIcEuj){xZUVegROPm = true;}
      if(DgTEgUoutY == bZZHkJFhQe){QAUPMjOMIm = true;}
      else if(bZZHkJFhQe == DgTEgUoutY){VoBckzGFac = true;}
      if(WuRpUlsINu == xbxwBGpQPN){wJkkuOqWhC = true;}
      else if(xbxwBGpQPN == WuRpUlsINu){REOIfrkjzz = true;}
      if(bkdTmtARcW == yjGBqtjJVq){YuBEuEHcse = true;}
      else if(yjGBqtjJVq == bkdTmtARcW){QdIcBygXwD = true;}
      if(PHFjdpumsF == wafzrMmYPy){tfuwOupocH = true;}
      else if(wafzrMmYPy == PHFjdpumsF){WncMolhWyd = true;}
      if(NzQDRSHmkb == oinwNLyYEf){RkrIDjcXcJ = true;}
      else if(oinwNLyYEf == NzQDRSHmkb){ntICarKMom = true;}
      if(PUpzHSCzRm == APdfDrSYPq){BzgLRUyPTH = true;}
      if(TWRXIPphMd == ZwMZiWuyEo){bkScsPNnVz = true;}
      if(pFOHhcUaBU == SQBRXPuJne){YCsajnDsAL = true;}
      while(APdfDrSYPq == PUpzHSCzRm){uhOQWrfYal = true;}
      while(ZwMZiWuyEo == ZwMZiWuyEo){SiJWGdbCSs = true;}
      while(SQBRXPuJne == SQBRXPuJne){KNkVKVUGBI = true;}
      if(uKEpqfxAwA == true){uKEpqfxAwA = false;}
      if(sNIXXsVONq == true){sNIXXsVONq = false;}
      if(QAUPMjOMIm == true){QAUPMjOMIm = false;}
      if(wJkkuOqWhC == true){wJkkuOqWhC = false;}
      if(YuBEuEHcse == true){YuBEuEHcse = false;}
      if(tfuwOupocH == true){tfuwOupocH = false;}
      if(RkrIDjcXcJ == true){RkrIDjcXcJ = false;}
      if(BzgLRUyPTH == true){BzgLRUyPTH = false;}
      if(bkScsPNnVz == true){bkScsPNnVz = false;}
      if(YCsajnDsAL == true){YCsajnDsAL = false;}
      if(bjAictzjes == true){bjAictzjes = false;}
      if(xZUVegROPm == true){xZUVegROPm = false;}
      if(VoBckzGFac == true){VoBckzGFac = false;}
      if(REOIfrkjzz == true){REOIfrkjzz = false;}
      if(QdIcBygXwD == true){QdIcBygXwD = false;}
      if(WncMolhWyd == true){WncMolhWyd = false;}
      if(ntICarKMom == true){ntICarKMom = false;}
      if(uhOQWrfYal == true){uhOQWrfYal = false;}
      if(SiJWGdbCSs == true){SiJWGdbCSs = false;}
      if(KNkVKVUGBI == true){KNkVKVUGBI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class REIRUXNRHH
{ 
  void SoWAmFcVJG()
  { 
      bool PNEgDVykYD = false;
      bool elVuZQzFPb = false;
      bool VxCXkRTFqn = false;
      bool udFDSRTpCI = false;
      bool fWPQwTTkhV = false;
      bool YdrEwRLful = false;
      bool CstkHBfSbI = false;
      bool wJCHuzhkaR = false;
      bool xhXUOQkAHA = false;
      bool FmuPGmbdIu = false;
      bool mBJZYPbkIw = false;
      bool jZFcoUVYWq = false;
      bool PfLaCJNmAI = false;
      bool WDcfduYywy = false;
      bool ozqKQfhRal = false;
      bool RDHRfHphWP = false;
      bool BojAZgxZzs = false;
      bool wXcXBPoBKV = false;
      bool bwLOqSwLzV = false;
      bool FpafwAPpjj = false;
      string xVLxjwaohr;
      string ZZaABZThFB;
      string bGlXClOpek;
      string VYhOlzysrk;
      string SxQQKAJWPw;
      string rIzfcpimuy;
      string hkJxVArLNB;
      string aapUiepVNB;
      string bqZirNZBlw;
      string PKxtChmTtJ;
      string IyJOURRdxy;
      string ANZsVpKaEI;
      string apZRkPcuSB;
      string qWaDsdhKNa;
      string uuEnuCjEYL;
      string WMOliRXqdF;
      string nWLuGdlWzq;
      string IANcMellVi;
      string eXWGeeHoUb;
      string FpgHlYjIgR;
      if(xVLxjwaohr == IyJOURRdxy){PNEgDVykYD = true;}
      else if(IyJOURRdxy == xVLxjwaohr){mBJZYPbkIw = true;}
      if(ZZaABZThFB == ANZsVpKaEI){elVuZQzFPb = true;}
      else if(ANZsVpKaEI == ZZaABZThFB){jZFcoUVYWq = true;}
      if(bGlXClOpek == apZRkPcuSB){VxCXkRTFqn = true;}
      else if(apZRkPcuSB == bGlXClOpek){PfLaCJNmAI = true;}
      if(VYhOlzysrk == qWaDsdhKNa){udFDSRTpCI = true;}
      else if(qWaDsdhKNa == VYhOlzysrk){WDcfduYywy = true;}
      if(SxQQKAJWPw == uuEnuCjEYL){fWPQwTTkhV = true;}
      else if(uuEnuCjEYL == SxQQKAJWPw){ozqKQfhRal = true;}
      if(rIzfcpimuy == WMOliRXqdF){YdrEwRLful = true;}
      else if(WMOliRXqdF == rIzfcpimuy){RDHRfHphWP = true;}
      if(hkJxVArLNB == nWLuGdlWzq){CstkHBfSbI = true;}
      else if(nWLuGdlWzq == hkJxVArLNB){BojAZgxZzs = true;}
      if(aapUiepVNB == IANcMellVi){wJCHuzhkaR = true;}
      if(bqZirNZBlw == eXWGeeHoUb){xhXUOQkAHA = true;}
      if(PKxtChmTtJ == FpgHlYjIgR){FmuPGmbdIu = true;}
      while(IANcMellVi == aapUiepVNB){wXcXBPoBKV = true;}
      while(eXWGeeHoUb == eXWGeeHoUb){bwLOqSwLzV = true;}
      while(FpgHlYjIgR == FpgHlYjIgR){FpafwAPpjj = true;}
      if(PNEgDVykYD == true){PNEgDVykYD = false;}
      if(elVuZQzFPb == true){elVuZQzFPb = false;}
      if(VxCXkRTFqn == true){VxCXkRTFqn = false;}
      if(udFDSRTpCI == true){udFDSRTpCI = false;}
      if(fWPQwTTkhV == true){fWPQwTTkhV = false;}
      if(YdrEwRLful == true){YdrEwRLful = false;}
      if(CstkHBfSbI == true){CstkHBfSbI = false;}
      if(wJCHuzhkaR == true){wJCHuzhkaR = false;}
      if(xhXUOQkAHA == true){xhXUOQkAHA = false;}
      if(FmuPGmbdIu == true){FmuPGmbdIu = false;}
      if(mBJZYPbkIw == true){mBJZYPbkIw = false;}
      if(jZFcoUVYWq == true){jZFcoUVYWq = false;}
      if(PfLaCJNmAI == true){PfLaCJNmAI = false;}
      if(WDcfduYywy == true){WDcfduYywy = false;}
      if(ozqKQfhRal == true){ozqKQfhRal = false;}
      if(RDHRfHphWP == true){RDHRfHphWP = false;}
      if(BojAZgxZzs == true){BojAZgxZzs = false;}
      if(wXcXBPoBKV == true){wXcXBPoBKV = false;}
      if(bwLOqSwLzV == true){bwLOqSwLzV = false;}
      if(FpafwAPpjj == true){FpafwAPpjj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCKCANNZKN
{ 
  void kWjfewwXqB()
  { 
      bool RgDpzERbWx = false;
      bool GnmCGYCtec = false;
      bool jsDdtRcEjM = false;
      bool hBFmBbGNZt = false;
      bool qpSgesTAeP = false;
      bool EJUCOXdZug = false;
      bool bNrJOEizBd = false;
      bool SnTjktaVzB = false;
      bool ycZUIYgDYc = false;
      bool ygSrSdxIRZ = false;
      bool KTzAwPokQT = false;
      bool wHZsiymWBp = false;
      bool XfaXelVaQH = false;
      bool wSEZpedYXs = false;
      bool iwlEfqGYJU = false;
      bool paGbCesaUK = false;
      bool sNTIXdDACE = false;
      bool UOzHHasVqn = false;
      bool exRwQVLcWL = false;
      bool lCDMzUbcgC = false;
      string jJtiAYHjmK;
      string XHGaQnYuDi;
      string pwrssgXnFF;
      string pbijMgIRVd;
      string IbepnMycZR;
      string TBopQnQApT;
      string ASdhTuYVNj;
      string eGYZaNQCFg;
      string iuOmknlsTY;
      string PIbCcoxxVr;
      string mbOplNbPPC;
      string WOtIjFEpwf;
      string IeCoTWdVwk;
      string PTfNsHgYAX;
      string MWdRCANTSX;
      string kHBpiHYZVP;
      string iFSdlDigPc;
      string YfoYTlBklS;
      string IKDYzISodk;
      string hGCknGDzez;
      if(jJtiAYHjmK == mbOplNbPPC){RgDpzERbWx = true;}
      else if(mbOplNbPPC == jJtiAYHjmK){KTzAwPokQT = true;}
      if(XHGaQnYuDi == WOtIjFEpwf){GnmCGYCtec = true;}
      else if(WOtIjFEpwf == XHGaQnYuDi){wHZsiymWBp = true;}
      if(pwrssgXnFF == IeCoTWdVwk){jsDdtRcEjM = true;}
      else if(IeCoTWdVwk == pwrssgXnFF){XfaXelVaQH = true;}
      if(pbijMgIRVd == PTfNsHgYAX){hBFmBbGNZt = true;}
      else if(PTfNsHgYAX == pbijMgIRVd){wSEZpedYXs = true;}
      if(IbepnMycZR == MWdRCANTSX){qpSgesTAeP = true;}
      else if(MWdRCANTSX == IbepnMycZR){iwlEfqGYJU = true;}
      if(TBopQnQApT == kHBpiHYZVP){EJUCOXdZug = true;}
      else if(kHBpiHYZVP == TBopQnQApT){paGbCesaUK = true;}
      if(ASdhTuYVNj == iFSdlDigPc){bNrJOEizBd = true;}
      else if(iFSdlDigPc == ASdhTuYVNj){sNTIXdDACE = true;}
      if(eGYZaNQCFg == YfoYTlBklS){SnTjktaVzB = true;}
      if(iuOmknlsTY == IKDYzISodk){ycZUIYgDYc = true;}
      if(PIbCcoxxVr == hGCknGDzez){ygSrSdxIRZ = true;}
      while(YfoYTlBklS == eGYZaNQCFg){UOzHHasVqn = true;}
      while(IKDYzISodk == IKDYzISodk){exRwQVLcWL = true;}
      while(hGCknGDzez == hGCknGDzez){lCDMzUbcgC = true;}
      if(RgDpzERbWx == true){RgDpzERbWx = false;}
      if(GnmCGYCtec == true){GnmCGYCtec = false;}
      if(jsDdtRcEjM == true){jsDdtRcEjM = false;}
      if(hBFmBbGNZt == true){hBFmBbGNZt = false;}
      if(qpSgesTAeP == true){qpSgesTAeP = false;}
      if(EJUCOXdZug == true){EJUCOXdZug = false;}
      if(bNrJOEizBd == true){bNrJOEizBd = false;}
      if(SnTjktaVzB == true){SnTjktaVzB = false;}
      if(ycZUIYgDYc == true){ycZUIYgDYc = false;}
      if(ygSrSdxIRZ == true){ygSrSdxIRZ = false;}
      if(KTzAwPokQT == true){KTzAwPokQT = false;}
      if(wHZsiymWBp == true){wHZsiymWBp = false;}
      if(XfaXelVaQH == true){XfaXelVaQH = false;}
      if(wSEZpedYXs == true){wSEZpedYXs = false;}
      if(iwlEfqGYJU == true){iwlEfqGYJU = false;}
      if(paGbCesaUK == true){paGbCesaUK = false;}
      if(sNTIXdDACE == true){sNTIXdDACE = false;}
      if(UOzHHasVqn == true){UOzHHasVqn = false;}
      if(exRwQVLcWL == true){exRwQVLcWL = false;}
      if(lCDMzUbcgC == true){lCDMzUbcgC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HDPTGJLXJX
{ 
  void IGpuXmByWW()
  { 
      bool kluIdVQqOr = false;
      bool TVPuyNzWqT = false;
      bool ayyzkIoDhX = false;
      bool dfEioNMFwc = false;
      bool dKlKNtBZdp = false;
      bool HQPjdmnwXU = false;
      bool fNIqOmRgFk = false;
      bool BtaOpPLmlp = false;
      bool HPYrPNQTEC = false;
      bool ZPgawQCuwZ = false;
      bool cTUsoNoBtO = false;
      bool aBKhNPoQaB = false;
      bool WxbCLkMARZ = false;
      bool NQqLMmueCC = false;
      bool XOZpbXFzNg = false;
      bool bkTuDfrRhD = false;
      bool AoiUAKKyUZ = false;
      bool TJNXcHXkam = false;
      bool fNmkycwuIg = false;
      bool udwzBifFpQ = false;
      string niycSyYaKk;
      string kwrxNpfpeQ;
      string iFwGaRAzAS;
      string bUulcUwzIz;
      string GhhEdsNyai;
      string mTHdJhmrCB;
      string yYaqJQBFTs;
      string tggfKAWqbg;
      string DBXReINQcu;
      string gExHBgHpuN;
      string rIehoFmbTI;
      string KwPUxwAJMA;
      string DkcYLojYed;
      string sgwNnuWpcZ;
      string VkwTjknbKE;
      string fxdtKHeFVz;
      string VNxoPdzBfB;
      string ZKgleRnIoa;
      string AHOZyuCBDg;
      string QQUcDHnHEF;
      if(niycSyYaKk == rIehoFmbTI){kluIdVQqOr = true;}
      else if(rIehoFmbTI == niycSyYaKk){cTUsoNoBtO = true;}
      if(kwrxNpfpeQ == KwPUxwAJMA){TVPuyNzWqT = true;}
      else if(KwPUxwAJMA == kwrxNpfpeQ){aBKhNPoQaB = true;}
      if(iFwGaRAzAS == DkcYLojYed){ayyzkIoDhX = true;}
      else if(DkcYLojYed == iFwGaRAzAS){WxbCLkMARZ = true;}
      if(bUulcUwzIz == sgwNnuWpcZ){dfEioNMFwc = true;}
      else if(sgwNnuWpcZ == bUulcUwzIz){NQqLMmueCC = true;}
      if(GhhEdsNyai == VkwTjknbKE){dKlKNtBZdp = true;}
      else if(VkwTjknbKE == GhhEdsNyai){XOZpbXFzNg = true;}
      if(mTHdJhmrCB == fxdtKHeFVz){HQPjdmnwXU = true;}
      else if(fxdtKHeFVz == mTHdJhmrCB){bkTuDfrRhD = true;}
      if(yYaqJQBFTs == VNxoPdzBfB){fNIqOmRgFk = true;}
      else if(VNxoPdzBfB == yYaqJQBFTs){AoiUAKKyUZ = true;}
      if(tggfKAWqbg == ZKgleRnIoa){BtaOpPLmlp = true;}
      if(DBXReINQcu == AHOZyuCBDg){HPYrPNQTEC = true;}
      if(gExHBgHpuN == QQUcDHnHEF){ZPgawQCuwZ = true;}
      while(ZKgleRnIoa == tggfKAWqbg){TJNXcHXkam = true;}
      while(AHOZyuCBDg == AHOZyuCBDg){fNmkycwuIg = true;}
      while(QQUcDHnHEF == QQUcDHnHEF){udwzBifFpQ = true;}
      if(kluIdVQqOr == true){kluIdVQqOr = false;}
      if(TVPuyNzWqT == true){TVPuyNzWqT = false;}
      if(ayyzkIoDhX == true){ayyzkIoDhX = false;}
      if(dfEioNMFwc == true){dfEioNMFwc = false;}
      if(dKlKNtBZdp == true){dKlKNtBZdp = false;}
      if(HQPjdmnwXU == true){HQPjdmnwXU = false;}
      if(fNIqOmRgFk == true){fNIqOmRgFk = false;}
      if(BtaOpPLmlp == true){BtaOpPLmlp = false;}
      if(HPYrPNQTEC == true){HPYrPNQTEC = false;}
      if(ZPgawQCuwZ == true){ZPgawQCuwZ = false;}
      if(cTUsoNoBtO == true){cTUsoNoBtO = false;}
      if(aBKhNPoQaB == true){aBKhNPoQaB = false;}
      if(WxbCLkMARZ == true){WxbCLkMARZ = false;}
      if(NQqLMmueCC == true){NQqLMmueCC = false;}
      if(XOZpbXFzNg == true){XOZpbXFzNg = false;}
      if(bkTuDfrRhD == true){bkTuDfrRhD = false;}
      if(AoiUAKKyUZ == true){AoiUAKKyUZ = false;}
      if(TJNXcHXkam == true){TJNXcHXkam = false;}
      if(fNmkycwuIg == true){fNmkycwuIg = false;}
      if(udwzBifFpQ == true){udwzBifFpQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SCJORGLHSJ
{ 
  void DFaHHGGxVI()
  { 
      bool IyKMsxQyYi = false;
      bool CGQeObGmqK = false;
      bool dsPVwoGcFk = false;
      bool qaLENcinpn = false;
      bool zSrHmOIqKF = false;
      bool XErrKOinQD = false;
      bool qnsmqauLRl = false;
      bool rRwDLKBIig = false;
      bool gORzNlhTsz = false;
      bool ttXmxLYFPL = false;
      bool SxZYNFIofA = false;
      bool MaFiWbVsYE = false;
      bool sbSSrxtJGA = false;
      bool kwrWNjoslI = false;
      bool dsmslSooQU = false;
      bool pefKSqdHgQ = false;
      bool LzifOQhiUm = false;
      bool lbHQaAnYfY = false;
      bool IFrkKFPgEW = false;
      bool FhMUweJHeU = false;
      string QgMzNooXzL;
      string RyNZTNfSYX;
      string ZlSVyBUaNV;
      string hoZdNwLiza;
      string mzGVtKwzNY;
      string hGLYneNqBM;
      string UNJddbYiMX;
      string BxSxkafxan;
      string EVNnnacApi;
      string iUhmGZobqR;
      string kNmpXjnNnM;
      string zPPMIyAUpC;
      string yXrcogOfqK;
      string kDFJCpiXQD;
      string mOMdjSEUdH;
      string ZUloSNUJBq;
      string VIWcauKGKR;
      string ObDmPjKOsV;
      string btBikQRQpo;
      string VZVZgdrjCn;
      if(QgMzNooXzL == kNmpXjnNnM){IyKMsxQyYi = true;}
      else if(kNmpXjnNnM == QgMzNooXzL){SxZYNFIofA = true;}
      if(RyNZTNfSYX == zPPMIyAUpC){CGQeObGmqK = true;}
      else if(zPPMIyAUpC == RyNZTNfSYX){MaFiWbVsYE = true;}
      if(ZlSVyBUaNV == yXrcogOfqK){dsPVwoGcFk = true;}
      else if(yXrcogOfqK == ZlSVyBUaNV){sbSSrxtJGA = true;}
      if(hoZdNwLiza == kDFJCpiXQD){qaLENcinpn = true;}
      else if(kDFJCpiXQD == hoZdNwLiza){kwrWNjoslI = true;}
      if(mzGVtKwzNY == mOMdjSEUdH){zSrHmOIqKF = true;}
      else if(mOMdjSEUdH == mzGVtKwzNY){dsmslSooQU = true;}
      if(hGLYneNqBM == ZUloSNUJBq){XErrKOinQD = true;}
      else if(ZUloSNUJBq == hGLYneNqBM){pefKSqdHgQ = true;}
      if(UNJddbYiMX == VIWcauKGKR){qnsmqauLRl = true;}
      else if(VIWcauKGKR == UNJddbYiMX){LzifOQhiUm = true;}
      if(BxSxkafxan == ObDmPjKOsV){rRwDLKBIig = true;}
      if(EVNnnacApi == btBikQRQpo){gORzNlhTsz = true;}
      if(iUhmGZobqR == VZVZgdrjCn){ttXmxLYFPL = true;}
      while(ObDmPjKOsV == BxSxkafxan){lbHQaAnYfY = true;}
      while(btBikQRQpo == btBikQRQpo){IFrkKFPgEW = true;}
      while(VZVZgdrjCn == VZVZgdrjCn){FhMUweJHeU = true;}
      if(IyKMsxQyYi == true){IyKMsxQyYi = false;}
      if(CGQeObGmqK == true){CGQeObGmqK = false;}
      if(dsPVwoGcFk == true){dsPVwoGcFk = false;}
      if(qaLENcinpn == true){qaLENcinpn = false;}
      if(zSrHmOIqKF == true){zSrHmOIqKF = false;}
      if(XErrKOinQD == true){XErrKOinQD = false;}
      if(qnsmqauLRl == true){qnsmqauLRl = false;}
      if(rRwDLKBIig == true){rRwDLKBIig = false;}
      if(gORzNlhTsz == true){gORzNlhTsz = false;}
      if(ttXmxLYFPL == true){ttXmxLYFPL = false;}
      if(SxZYNFIofA == true){SxZYNFIofA = false;}
      if(MaFiWbVsYE == true){MaFiWbVsYE = false;}
      if(sbSSrxtJGA == true){sbSSrxtJGA = false;}
      if(kwrWNjoslI == true){kwrWNjoslI = false;}
      if(dsmslSooQU == true){dsmslSooQU = false;}
      if(pefKSqdHgQ == true){pefKSqdHgQ = false;}
      if(LzifOQhiUm == true){LzifOQhiUm = false;}
      if(lbHQaAnYfY == true){lbHQaAnYfY = false;}
      if(IFrkKFPgEW == true){IFrkKFPgEW = false;}
      if(FhMUweJHeU == true){FhMUweJHeU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LRBNPCBXPB
{ 
  void VODUknmdfm()
  { 
      bool OtNBwonWdI = false;
      bool EciwOqYpEU = false;
      bool hIEErhZHCa = false;
      bool RgBkVuTwiJ = false;
      bool IJDOxSdhMg = false;
      bool nEDVlGpJIN = false;
      bool PgTCqXbyZT = false;
      bool XbGtLXEpGZ = false;
      bool EqtUmMcfyP = false;
      bool FJnVtboAWZ = false;
      bool qfIsJMxJJO = false;
      bool BzDiJXlzPd = false;
      bool uwAJOOnkAj = false;
      bool iESfhXhALZ = false;
      bool PTViNFFEMV = false;
      bool opjsdufydt = false;
      bool YLIZfxgWBk = false;
      bool pkmoNbZQuJ = false;
      bool IjYetrTYCl = false;
      bool riWQBDKwDQ = false;
      string ifgqsBjPaT;
      string zThAFsqbbK;
      string DgBYwBZlGa;
      string xNJngWuRoP;
      string HwZMiFPwEL;
      string AzEAsCdHtr;
      string axJzVlKtSh;
      string xZmLCGGooq;
      string ldhtZxIJte;
      string snWxoJmZpx;
      string uUcVNaMrxl;
      string unSCFxPPZX;
      string cBAnoJCoWs;
      string TgzqwQBLfy;
      string jQLIiEUUqq;
      string tWzRUsUngD;
      string YXVDROoaGo;
      string uEibnMoqFk;
      string ogyezxggWC;
      string wMdbYMtIpU;
      if(ifgqsBjPaT == uUcVNaMrxl){OtNBwonWdI = true;}
      else if(uUcVNaMrxl == ifgqsBjPaT){qfIsJMxJJO = true;}
      if(zThAFsqbbK == unSCFxPPZX){EciwOqYpEU = true;}
      else if(unSCFxPPZX == zThAFsqbbK){BzDiJXlzPd = true;}
      if(DgBYwBZlGa == cBAnoJCoWs){hIEErhZHCa = true;}
      else if(cBAnoJCoWs == DgBYwBZlGa){uwAJOOnkAj = true;}
      if(xNJngWuRoP == TgzqwQBLfy){RgBkVuTwiJ = true;}
      else if(TgzqwQBLfy == xNJngWuRoP){iESfhXhALZ = true;}
      if(HwZMiFPwEL == jQLIiEUUqq){IJDOxSdhMg = true;}
      else if(jQLIiEUUqq == HwZMiFPwEL){PTViNFFEMV = true;}
      if(AzEAsCdHtr == tWzRUsUngD){nEDVlGpJIN = true;}
      else if(tWzRUsUngD == AzEAsCdHtr){opjsdufydt = true;}
      if(axJzVlKtSh == YXVDROoaGo){PgTCqXbyZT = true;}
      else if(YXVDROoaGo == axJzVlKtSh){YLIZfxgWBk = true;}
      if(xZmLCGGooq == uEibnMoqFk){XbGtLXEpGZ = true;}
      if(ldhtZxIJte == ogyezxggWC){EqtUmMcfyP = true;}
      if(snWxoJmZpx == wMdbYMtIpU){FJnVtboAWZ = true;}
      while(uEibnMoqFk == xZmLCGGooq){pkmoNbZQuJ = true;}
      while(ogyezxggWC == ogyezxggWC){IjYetrTYCl = true;}
      while(wMdbYMtIpU == wMdbYMtIpU){riWQBDKwDQ = true;}
      if(OtNBwonWdI == true){OtNBwonWdI = false;}
      if(EciwOqYpEU == true){EciwOqYpEU = false;}
      if(hIEErhZHCa == true){hIEErhZHCa = false;}
      if(RgBkVuTwiJ == true){RgBkVuTwiJ = false;}
      if(IJDOxSdhMg == true){IJDOxSdhMg = false;}
      if(nEDVlGpJIN == true){nEDVlGpJIN = false;}
      if(PgTCqXbyZT == true){PgTCqXbyZT = false;}
      if(XbGtLXEpGZ == true){XbGtLXEpGZ = false;}
      if(EqtUmMcfyP == true){EqtUmMcfyP = false;}
      if(FJnVtboAWZ == true){FJnVtboAWZ = false;}
      if(qfIsJMxJJO == true){qfIsJMxJJO = false;}
      if(BzDiJXlzPd == true){BzDiJXlzPd = false;}
      if(uwAJOOnkAj == true){uwAJOOnkAj = false;}
      if(iESfhXhALZ == true){iESfhXhALZ = false;}
      if(PTViNFFEMV == true){PTViNFFEMV = false;}
      if(opjsdufydt == true){opjsdufydt = false;}
      if(YLIZfxgWBk == true){YLIZfxgWBk = false;}
      if(pkmoNbZQuJ == true){pkmoNbZQuJ = false;}
      if(IjYetrTYCl == true){IjYetrTYCl = false;}
      if(riWQBDKwDQ == true){riWQBDKwDQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DORZVEBPGQ
{ 
  void BprQzHQPIW()
  { 
      bool sCmVYXiLKI = false;
      bool rMMznqQgjE = false;
      bool gVhhKIYEUX = false;
      bool RsluYzGQUH = false;
      bool EyySbNeQCE = false;
      bool GYOLaXUFLP = false;
      bool yeqmpyaRZo = false;
      bool kzMcziWPFw = false;
      bool dHBQQseaTB = false;
      bool dAFFIZHLbc = false;
      bool mMpNSGMlLr = false;
      bool BFzPkqcaVx = false;
      bool TAyYKjtHTZ = false;
      bool aKncIQQnxJ = false;
      bool grOazYAoTR = false;
      bool wgodImNRCh = false;
      bool MERkQpRWGU = false;
      bool ZndLQbkXYl = false;
      bool iEmCctUJTV = false;
      bool CzlOxbZcJJ = false;
      string oGWbtdRiMD;
      string DeNQQboAZT;
      string esTLUGoGaJ;
      string FWBpcHlFVX;
      string tLdaRVtJRr;
      string FdwfaumKHm;
      string oLICyfcXmJ;
      string oidBZTPrsy;
      string MeohEaaUOh;
      string TbyiihCbcl;
      string sWWHCVztGH;
      string fuQIaJVZyW;
      string FHIFpNjuSq;
      string QnPHFoIgfh;
      string bgOGBXLpHY;
      string MccFgkOQQo;
      string lEaPqreICk;
      string AotQuXsBDR;
      string BtmsemKJaU;
      string arPpwWGzPI;
      if(oGWbtdRiMD == sWWHCVztGH){sCmVYXiLKI = true;}
      else if(sWWHCVztGH == oGWbtdRiMD){mMpNSGMlLr = true;}
      if(DeNQQboAZT == fuQIaJVZyW){rMMznqQgjE = true;}
      else if(fuQIaJVZyW == DeNQQboAZT){BFzPkqcaVx = true;}
      if(esTLUGoGaJ == FHIFpNjuSq){gVhhKIYEUX = true;}
      else if(FHIFpNjuSq == esTLUGoGaJ){TAyYKjtHTZ = true;}
      if(FWBpcHlFVX == QnPHFoIgfh){RsluYzGQUH = true;}
      else if(QnPHFoIgfh == FWBpcHlFVX){aKncIQQnxJ = true;}
      if(tLdaRVtJRr == bgOGBXLpHY){EyySbNeQCE = true;}
      else if(bgOGBXLpHY == tLdaRVtJRr){grOazYAoTR = true;}
      if(FdwfaumKHm == MccFgkOQQo){GYOLaXUFLP = true;}
      else if(MccFgkOQQo == FdwfaumKHm){wgodImNRCh = true;}
      if(oLICyfcXmJ == lEaPqreICk){yeqmpyaRZo = true;}
      else if(lEaPqreICk == oLICyfcXmJ){MERkQpRWGU = true;}
      if(oidBZTPrsy == AotQuXsBDR){kzMcziWPFw = true;}
      if(MeohEaaUOh == BtmsemKJaU){dHBQQseaTB = true;}
      if(TbyiihCbcl == arPpwWGzPI){dAFFIZHLbc = true;}
      while(AotQuXsBDR == oidBZTPrsy){ZndLQbkXYl = true;}
      while(BtmsemKJaU == BtmsemKJaU){iEmCctUJTV = true;}
      while(arPpwWGzPI == arPpwWGzPI){CzlOxbZcJJ = true;}
      if(sCmVYXiLKI == true){sCmVYXiLKI = false;}
      if(rMMznqQgjE == true){rMMznqQgjE = false;}
      if(gVhhKIYEUX == true){gVhhKIYEUX = false;}
      if(RsluYzGQUH == true){RsluYzGQUH = false;}
      if(EyySbNeQCE == true){EyySbNeQCE = false;}
      if(GYOLaXUFLP == true){GYOLaXUFLP = false;}
      if(yeqmpyaRZo == true){yeqmpyaRZo = false;}
      if(kzMcziWPFw == true){kzMcziWPFw = false;}
      if(dHBQQseaTB == true){dHBQQseaTB = false;}
      if(dAFFIZHLbc == true){dAFFIZHLbc = false;}
      if(mMpNSGMlLr == true){mMpNSGMlLr = false;}
      if(BFzPkqcaVx == true){BFzPkqcaVx = false;}
      if(TAyYKjtHTZ == true){TAyYKjtHTZ = false;}
      if(aKncIQQnxJ == true){aKncIQQnxJ = false;}
      if(grOazYAoTR == true){grOazYAoTR = false;}
      if(wgodImNRCh == true){wgodImNRCh = false;}
      if(MERkQpRWGU == true){MERkQpRWGU = false;}
      if(ZndLQbkXYl == true){ZndLQbkXYl = false;}
      if(iEmCctUJTV == true){iEmCctUJTV = false;}
      if(CzlOxbZcJJ == true){CzlOxbZcJJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JTMAFWOHUF
{ 
  void yRJyTHyDXN()
  { 
      bool qAfuEIpPPw = false;
      bool iWfCpmUxoh = false;
      bool EitWNYubGZ = false;
      bool CcckGjoupQ = false;
      bool WXAHlbpZsu = false;
      bool pmDKTHFIhf = false;
      bool MNJpsGtuwF = false;
      bool yZHXLghmjk = false;
      bool hUiKiPYRQy = false;
      bool efNKEINKNf = false;
      bool hudnxQfezl = false;
      bool ZRXwyqezHd = false;
      bool gbdxaSMwTC = false;
      bool TXYEDmptMS = false;
      bool itSeYMHQMM = false;
      bool dODjzGQgMe = false;
      bool DiLwSBsTsK = false;
      bool BjlntmIzXO = false;
      bool KujHYEUoFw = false;
      bool VJhgOAhWMW = false;
      string AWJcEFcnPA;
      string sqzpumRawz;
      string xneewETFzo;
      string HJmrOzRaNs;
      string ILKCmlJqkf;
      string tYqLtMrefz;
      string kXoarjEGbu;
      string VqMDqkcbqK;
      string tcTTtiRaxB;
      string HluNIkWjKC;
      string hCPoJDLnUJ;
      string jQmVFIDUfJ;
      string RcJZniuzuG;
      string OrRnbrMeJq;
      string XdGnQpzZIA;
      string gBEBjFsoBZ;
      string ILsNurzysM;
      string uYLoknVVJy;
      string jUpuYMmQDV;
      string zWciiLkrsY;
      if(AWJcEFcnPA == hCPoJDLnUJ){qAfuEIpPPw = true;}
      else if(hCPoJDLnUJ == AWJcEFcnPA){hudnxQfezl = true;}
      if(sqzpumRawz == jQmVFIDUfJ){iWfCpmUxoh = true;}
      else if(jQmVFIDUfJ == sqzpumRawz){ZRXwyqezHd = true;}
      if(xneewETFzo == RcJZniuzuG){EitWNYubGZ = true;}
      else if(RcJZniuzuG == xneewETFzo){gbdxaSMwTC = true;}
      if(HJmrOzRaNs == OrRnbrMeJq){CcckGjoupQ = true;}
      else if(OrRnbrMeJq == HJmrOzRaNs){TXYEDmptMS = true;}
      if(ILKCmlJqkf == XdGnQpzZIA){WXAHlbpZsu = true;}
      else if(XdGnQpzZIA == ILKCmlJqkf){itSeYMHQMM = true;}
      if(tYqLtMrefz == gBEBjFsoBZ){pmDKTHFIhf = true;}
      else if(gBEBjFsoBZ == tYqLtMrefz){dODjzGQgMe = true;}
      if(kXoarjEGbu == ILsNurzysM){MNJpsGtuwF = true;}
      else if(ILsNurzysM == kXoarjEGbu){DiLwSBsTsK = true;}
      if(VqMDqkcbqK == uYLoknVVJy){yZHXLghmjk = true;}
      if(tcTTtiRaxB == jUpuYMmQDV){hUiKiPYRQy = true;}
      if(HluNIkWjKC == zWciiLkrsY){efNKEINKNf = true;}
      while(uYLoknVVJy == VqMDqkcbqK){BjlntmIzXO = true;}
      while(jUpuYMmQDV == jUpuYMmQDV){KujHYEUoFw = true;}
      while(zWciiLkrsY == zWciiLkrsY){VJhgOAhWMW = true;}
      if(qAfuEIpPPw == true){qAfuEIpPPw = false;}
      if(iWfCpmUxoh == true){iWfCpmUxoh = false;}
      if(EitWNYubGZ == true){EitWNYubGZ = false;}
      if(CcckGjoupQ == true){CcckGjoupQ = false;}
      if(WXAHlbpZsu == true){WXAHlbpZsu = false;}
      if(pmDKTHFIhf == true){pmDKTHFIhf = false;}
      if(MNJpsGtuwF == true){MNJpsGtuwF = false;}
      if(yZHXLghmjk == true){yZHXLghmjk = false;}
      if(hUiKiPYRQy == true){hUiKiPYRQy = false;}
      if(efNKEINKNf == true){efNKEINKNf = false;}
      if(hudnxQfezl == true){hudnxQfezl = false;}
      if(ZRXwyqezHd == true){ZRXwyqezHd = false;}
      if(gbdxaSMwTC == true){gbdxaSMwTC = false;}
      if(TXYEDmptMS == true){TXYEDmptMS = false;}
      if(itSeYMHQMM == true){itSeYMHQMM = false;}
      if(dODjzGQgMe == true){dODjzGQgMe = false;}
      if(DiLwSBsTsK == true){DiLwSBsTsK = false;}
      if(BjlntmIzXO == true){BjlntmIzXO = false;}
      if(KujHYEUoFw == true){KujHYEUoFw = false;}
      if(VJhgOAhWMW == true){VJhgOAhWMW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVJUWWIOSH
{ 
  void HVRrKyhpPZ()
  { 
      bool PqTiYGwufl = false;
      bool EtRemVDTXa = false;
      bool IcqxNgtXhn = false;
      bool RygxszVnzz = false;
      bool ZOIiDcZXEo = false;
      bool UDjTVlAWVq = false;
      bool LYMrTGMTkn = false;
      bool AOUXAsUHsk = false;
      bool HVTrSONMbG = false;
      bool yzSInBBPPx = false;
      bool PGlQoGiLTb = false;
      bool RrckjoFTYF = false;
      bool rAreoAuMjz = false;
      bool rFrwUAiCDL = false;
      bool fCszoGWhXy = false;
      bool uhpKEOOHao = false;
      bool LVbTjMAfPi = false;
      bool FCQNZpHroh = false;
      bool dMnkDKOhrG = false;
      bool lbaOAJaYPc = false;
      string DGmxwfpQMu;
      string FlqawSRzGI;
      string MfSwxfOdit;
      string TWRrmVGAMa;
      string FfZfQXsIGl;
      string sDsqPXmpzQ;
      string RMhSbiTzna;
      string LQmeDgGlfY;
      string mFWwAPcabO;
      string iPAwJsxGEh;
      string EsTfacQNnh;
      string RAKacLokRL;
      string FsWZqwPpVJ;
      string izhxUslqVX;
      string yPltxhEZSy;
      string DMosbLWtnd;
      string MardySSMGj;
      string YxPtMpGcbJ;
      string qpXXGWJoVI;
      string WrDqLXXIue;
      if(DGmxwfpQMu == EsTfacQNnh){PqTiYGwufl = true;}
      else if(EsTfacQNnh == DGmxwfpQMu){PGlQoGiLTb = true;}
      if(FlqawSRzGI == RAKacLokRL){EtRemVDTXa = true;}
      else if(RAKacLokRL == FlqawSRzGI){RrckjoFTYF = true;}
      if(MfSwxfOdit == FsWZqwPpVJ){IcqxNgtXhn = true;}
      else if(FsWZqwPpVJ == MfSwxfOdit){rAreoAuMjz = true;}
      if(TWRrmVGAMa == izhxUslqVX){RygxszVnzz = true;}
      else if(izhxUslqVX == TWRrmVGAMa){rFrwUAiCDL = true;}
      if(FfZfQXsIGl == yPltxhEZSy){ZOIiDcZXEo = true;}
      else if(yPltxhEZSy == FfZfQXsIGl){fCszoGWhXy = true;}
      if(sDsqPXmpzQ == DMosbLWtnd){UDjTVlAWVq = true;}
      else if(DMosbLWtnd == sDsqPXmpzQ){uhpKEOOHao = true;}
      if(RMhSbiTzna == MardySSMGj){LYMrTGMTkn = true;}
      else if(MardySSMGj == RMhSbiTzna){LVbTjMAfPi = true;}
      if(LQmeDgGlfY == YxPtMpGcbJ){AOUXAsUHsk = true;}
      if(mFWwAPcabO == qpXXGWJoVI){HVTrSONMbG = true;}
      if(iPAwJsxGEh == WrDqLXXIue){yzSInBBPPx = true;}
      while(YxPtMpGcbJ == LQmeDgGlfY){FCQNZpHroh = true;}
      while(qpXXGWJoVI == qpXXGWJoVI){dMnkDKOhrG = true;}
      while(WrDqLXXIue == WrDqLXXIue){lbaOAJaYPc = true;}
      if(PqTiYGwufl == true){PqTiYGwufl = false;}
      if(EtRemVDTXa == true){EtRemVDTXa = false;}
      if(IcqxNgtXhn == true){IcqxNgtXhn = false;}
      if(RygxszVnzz == true){RygxszVnzz = false;}
      if(ZOIiDcZXEo == true){ZOIiDcZXEo = false;}
      if(UDjTVlAWVq == true){UDjTVlAWVq = false;}
      if(LYMrTGMTkn == true){LYMrTGMTkn = false;}
      if(AOUXAsUHsk == true){AOUXAsUHsk = false;}
      if(HVTrSONMbG == true){HVTrSONMbG = false;}
      if(yzSInBBPPx == true){yzSInBBPPx = false;}
      if(PGlQoGiLTb == true){PGlQoGiLTb = false;}
      if(RrckjoFTYF == true){RrckjoFTYF = false;}
      if(rAreoAuMjz == true){rAreoAuMjz = false;}
      if(rFrwUAiCDL == true){rFrwUAiCDL = false;}
      if(fCszoGWhXy == true){fCszoGWhXy = false;}
      if(uhpKEOOHao == true){uhpKEOOHao = false;}
      if(LVbTjMAfPi == true){LVbTjMAfPi = false;}
      if(FCQNZpHroh == true){FCQNZpHroh = false;}
      if(dMnkDKOhrG == true){dMnkDKOhrG = false;}
      if(lbaOAJaYPc == true){lbaOAJaYPc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRUPATDHZP
{ 
  void JOUysSBIcr()
  { 
      bool rUadTOblRV = false;
      bool hPyomSreXx = false;
      bool AEfokoyiFx = false;
      bool aXZarwuOgh = false;
      bool wEaUiLnHfL = false;
      bool GPuOumokre = false;
      bool PrfTtJpWwq = false;
      bool XcxoBucKGZ = false;
      bool AqDtpLbKeE = false;
      bool HJVCSDYHZY = false;
      bool VRKondSGMA = false;
      bool KedSdYolci = false;
      bool heqrjNGtVy = false;
      bool WVjhEifNFM = false;
      bool rUxetbfDYt = false;
      bool NldpqpZSFa = false;
      bool WXjOcntwOt = false;
      bool rafPqMgLxH = false;
      bool hDVbkjqspN = false;
      bool INIdpUkiCF = false;
      string TlinjsYZuR;
      string DXTiVfzgeu;
      string ibeHxwVmJg;
      string iFaqhBYTSD;
      string MXockCygSV;
      string WgDKjqGbqn;
      string XkQOiywbAU;
      string GfNbhKmBVu;
      string ynUnKCCQHp;
      string txceeaHatm;
      string FVfyOqSbbY;
      string DEFwojQbDf;
      string ufUKZJChwG;
      string DMHiocIVYS;
      string iZnhmorgpu;
      string JeWOqYBVYF;
      string njfUVpxWGM;
      string buDkwVqlXj;
      string RVrBxXpsqQ;
      string alwTeytTMw;
      if(TlinjsYZuR == FVfyOqSbbY){rUadTOblRV = true;}
      else if(FVfyOqSbbY == TlinjsYZuR){VRKondSGMA = true;}
      if(DXTiVfzgeu == DEFwojQbDf){hPyomSreXx = true;}
      else if(DEFwojQbDf == DXTiVfzgeu){KedSdYolci = true;}
      if(ibeHxwVmJg == ufUKZJChwG){AEfokoyiFx = true;}
      else if(ufUKZJChwG == ibeHxwVmJg){heqrjNGtVy = true;}
      if(iFaqhBYTSD == DMHiocIVYS){aXZarwuOgh = true;}
      else if(DMHiocIVYS == iFaqhBYTSD){WVjhEifNFM = true;}
      if(MXockCygSV == iZnhmorgpu){wEaUiLnHfL = true;}
      else if(iZnhmorgpu == MXockCygSV){rUxetbfDYt = true;}
      if(WgDKjqGbqn == JeWOqYBVYF){GPuOumokre = true;}
      else if(JeWOqYBVYF == WgDKjqGbqn){NldpqpZSFa = true;}
      if(XkQOiywbAU == njfUVpxWGM){PrfTtJpWwq = true;}
      else if(njfUVpxWGM == XkQOiywbAU){WXjOcntwOt = true;}
      if(GfNbhKmBVu == buDkwVqlXj){XcxoBucKGZ = true;}
      if(ynUnKCCQHp == RVrBxXpsqQ){AqDtpLbKeE = true;}
      if(txceeaHatm == alwTeytTMw){HJVCSDYHZY = true;}
      while(buDkwVqlXj == GfNbhKmBVu){rafPqMgLxH = true;}
      while(RVrBxXpsqQ == RVrBxXpsqQ){hDVbkjqspN = true;}
      while(alwTeytTMw == alwTeytTMw){INIdpUkiCF = true;}
      if(rUadTOblRV == true){rUadTOblRV = false;}
      if(hPyomSreXx == true){hPyomSreXx = false;}
      if(AEfokoyiFx == true){AEfokoyiFx = false;}
      if(aXZarwuOgh == true){aXZarwuOgh = false;}
      if(wEaUiLnHfL == true){wEaUiLnHfL = false;}
      if(GPuOumokre == true){GPuOumokre = false;}
      if(PrfTtJpWwq == true){PrfTtJpWwq = false;}
      if(XcxoBucKGZ == true){XcxoBucKGZ = false;}
      if(AqDtpLbKeE == true){AqDtpLbKeE = false;}
      if(HJVCSDYHZY == true){HJVCSDYHZY = false;}
      if(VRKondSGMA == true){VRKondSGMA = false;}
      if(KedSdYolci == true){KedSdYolci = false;}
      if(heqrjNGtVy == true){heqrjNGtVy = false;}
      if(WVjhEifNFM == true){WVjhEifNFM = false;}
      if(rUxetbfDYt == true){rUxetbfDYt = false;}
      if(NldpqpZSFa == true){NldpqpZSFa = false;}
      if(WXjOcntwOt == true){WXjOcntwOt = false;}
      if(rafPqMgLxH == true){rafPqMgLxH = false;}
      if(hDVbkjqspN == true){hDVbkjqspN = false;}
      if(INIdpUkiCF == true){INIdpUkiCF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CFOZXODEDY
{ 
  void lOfNUgYsIe()
  { 
      bool wMOVqrkTPc = false;
      bool CbNCUNWayW = false;
      bool eDEDaTMmha = false;
      bool wGiLwVUHrk = false;
      bool HNkwVphLYx = false;
      bool zErKDsHKuX = false;
      bool eykogwrCFz = false;
      bool rOiMORSHhj = false;
      bool kBNkaqOYHD = false;
      bool NJLTGJbwPZ = false;
      bool xfFYEkVeuk = false;
      bool azcKmcjANo = false;
      bool gTtBlhCOGF = false;
      bool pVrHmEunfp = false;
      bool VjcWcNfBgc = false;
      bool YahasclEmV = false;
      bool hGXptEHVXh = false;
      bool huUXSwqXXY = false;
      bool BBhdgOnROJ = false;
      bool SqBJHPMmbY = false;
      string YarwwMxtRM;
      string QRCJCrGONp;
      string TJMfGTqKkf;
      string bIMNRjOjyw;
      string pIARdSyoJH;
      string xKSXmPOLob;
      string UlIkkHEoqR;
      string cWQRzLIuBm;
      string VBBciQpoZB;
      string VCtVaDzOgW;
      string OIxqeZtAXb;
      string GTKBGTkfCT;
      string ROOouabtpw;
      string LtOeYMDJyI;
      string WoRxuCrrPH;
      string SSMMEzsHwD;
      string xAKbPMFecs;
      string PahsxbxRts;
      string hjdicsgBZY;
      string SwNtKVephi;
      if(YarwwMxtRM == OIxqeZtAXb){wMOVqrkTPc = true;}
      else if(OIxqeZtAXb == YarwwMxtRM){xfFYEkVeuk = true;}
      if(QRCJCrGONp == GTKBGTkfCT){CbNCUNWayW = true;}
      else if(GTKBGTkfCT == QRCJCrGONp){azcKmcjANo = true;}
      if(TJMfGTqKkf == ROOouabtpw){eDEDaTMmha = true;}
      else if(ROOouabtpw == TJMfGTqKkf){gTtBlhCOGF = true;}
      if(bIMNRjOjyw == LtOeYMDJyI){wGiLwVUHrk = true;}
      else if(LtOeYMDJyI == bIMNRjOjyw){pVrHmEunfp = true;}
      if(pIARdSyoJH == WoRxuCrrPH){HNkwVphLYx = true;}
      else if(WoRxuCrrPH == pIARdSyoJH){VjcWcNfBgc = true;}
      if(xKSXmPOLob == SSMMEzsHwD){zErKDsHKuX = true;}
      else if(SSMMEzsHwD == xKSXmPOLob){YahasclEmV = true;}
      if(UlIkkHEoqR == xAKbPMFecs){eykogwrCFz = true;}
      else if(xAKbPMFecs == UlIkkHEoqR){hGXptEHVXh = true;}
      if(cWQRzLIuBm == PahsxbxRts){rOiMORSHhj = true;}
      if(VBBciQpoZB == hjdicsgBZY){kBNkaqOYHD = true;}
      if(VCtVaDzOgW == SwNtKVephi){NJLTGJbwPZ = true;}
      while(PahsxbxRts == cWQRzLIuBm){huUXSwqXXY = true;}
      while(hjdicsgBZY == hjdicsgBZY){BBhdgOnROJ = true;}
      while(SwNtKVephi == SwNtKVephi){SqBJHPMmbY = true;}
      if(wMOVqrkTPc == true){wMOVqrkTPc = false;}
      if(CbNCUNWayW == true){CbNCUNWayW = false;}
      if(eDEDaTMmha == true){eDEDaTMmha = false;}
      if(wGiLwVUHrk == true){wGiLwVUHrk = false;}
      if(HNkwVphLYx == true){HNkwVphLYx = false;}
      if(zErKDsHKuX == true){zErKDsHKuX = false;}
      if(eykogwrCFz == true){eykogwrCFz = false;}
      if(rOiMORSHhj == true){rOiMORSHhj = false;}
      if(kBNkaqOYHD == true){kBNkaqOYHD = false;}
      if(NJLTGJbwPZ == true){NJLTGJbwPZ = false;}
      if(xfFYEkVeuk == true){xfFYEkVeuk = false;}
      if(azcKmcjANo == true){azcKmcjANo = false;}
      if(gTtBlhCOGF == true){gTtBlhCOGF = false;}
      if(pVrHmEunfp == true){pVrHmEunfp = false;}
      if(VjcWcNfBgc == true){VjcWcNfBgc = false;}
      if(YahasclEmV == true){YahasclEmV = false;}
      if(hGXptEHVXh == true){hGXptEHVXh = false;}
      if(huUXSwqXXY == true){huUXSwqXXY = false;}
      if(BBhdgOnROJ == true){BBhdgOnROJ = false;}
      if(SqBJHPMmbY == true){SqBJHPMmbY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MMSHFPRMJY
{ 
  void AUJVwbIEFP()
  { 
      bool plQDtooWPz = false;
      bool SqGHIuuUXI = false;
      bool aYzwwqIoDF = false;
      bool buBIKMoRVV = false;
      bool AyNlekeWKG = false;
      bool bumseQmTGD = false;
      bool fzTJWXpxww = false;
      bool GdzCHcKMQL = false;
      bool MlexdgHHds = false;
      bool ZVKRoBeEOG = false;
      bool ugaNAywkkC = false;
      bool FZDuqtTVfp = false;
      bool QhTCVkSgNG = false;
      bool xGyJPeLQxf = false;
      bool kWWanARPat = false;
      bool gIYYpMNYqP = false;
      bool eOXeEzaseL = false;
      bool iCYzEsLrOV = false;
      bool SDGSYohYSD = false;
      bool RmZgAVzqVn = false;
      string tHnJcUTgUI;
      string HumxeRsQZH;
      string uKFNqKtEql;
      string opdwhSLxrg;
      string RYWaAroBOk;
      string OmRMIiCaRS;
      string aPphSQRqOL;
      string GuXspVndMy;
      string VroFXCYQmy;
      string QkeZFChnIj;
      string aylDdSOXWl;
      string uXNSwiZjKQ;
      string rADQtVQymm;
      string nzVcXWGlbE;
      string mAtACsWLcW;
      string cxdrqZtUII;
      string BQkiywCkuZ;
      string bmIGcrGCOB;
      string zFUPKpVcky;
      string ckdTCWPLBF;
      if(tHnJcUTgUI == aylDdSOXWl){plQDtooWPz = true;}
      else if(aylDdSOXWl == tHnJcUTgUI){ugaNAywkkC = true;}
      if(HumxeRsQZH == uXNSwiZjKQ){SqGHIuuUXI = true;}
      else if(uXNSwiZjKQ == HumxeRsQZH){FZDuqtTVfp = true;}
      if(uKFNqKtEql == rADQtVQymm){aYzwwqIoDF = true;}
      else if(rADQtVQymm == uKFNqKtEql){QhTCVkSgNG = true;}
      if(opdwhSLxrg == nzVcXWGlbE){buBIKMoRVV = true;}
      else if(nzVcXWGlbE == opdwhSLxrg){xGyJPeLQxf = true;}
      if(RYWaAroBOk == mAtACsWLcW){AyNlekeWKG = true;}
      else if(mAtACsWLcW == RYWaAroBOk){kWWanARPat = true;}
      if(OmRMIiCaRS == cxdrqZtUII){bumseQmTGD = true;}
      else if(cxdrqZtUII == OmRMIiCaRS){gIYYpMNYqP = true;}
      if(aPphSQRqOL == BQkiywCkuZ){fzTJWXpxww = true;}
      else if(BQkiywCkuZ == aPphSQRqOL){eOXeEzaseL = true;}
      if(GuXspVndMy == bmIGcrGCOB){GdzCHcKMQL = true;}
      if(VroFXCYQmy == zFUPKpVcky){MlexdgHHds = true;}
      if(QkeZFChnIj == ckdTCWPLBF){ZVKRoBeEOG = true;}
      while(bmIGcrGCOB == GuXspVndMy){iCYzEsLrOV = true;}
      while(zFUPKpVcky == zFUPKpVcky){SDGSYohYSD = true;}
      while(ckdTCWPLBF == ckdTCWPLBF){RmZgAVzqVn = true;}
      if(plQDtooWPz == true){plQDtooWPz = false;}
      if(SqGHIuuUXI == true){SqGHIuuUXI = false;}
      if(aYzwwqIoDF == true){aYzwwqIoDF = false;}
      if(buBIKMoRVV == true){buBIKMoRVV = false;}
      if(AyNlekeWKG == true){AyNlekeWKG = false;}
      if(bumseQmTGD == true){bumseQmTGD = false;}
      if(fzTJWXpxww == true){fzTJWXpxww = false;}
      if(GdzCHcKMQL == true){GdzCHcKMQL = false;}
      if(MlexdgHHds == true){MlexdgHHds = false;}
      if(ZVKRoBeEOG == true){ZVKRoBeEOG = false;}
      if(ugaNAywkkC == true){ugaNAywkkC = false;}
      if(FZDuqtTVfp == true){FZDuqtTVfp = false;}
      if(QhTCVkSgNG == true){QhTCVkSgNG = false;}
      if(xGyJPeLQxf == true){xGyJPeLQxf = false;}
      if(kWWanARPat == true){kWWanARPat = false;}
      if(gIYYpMNYqP == true){gIYYpMNYqP = false;}
      if(eOXeEzaseL == true){eOXeEzaseL = false;}
      if(iCYzEsLrOV == true){iCYzEsLrOV = false;}
      if(SDGSYohYSD == true){SDGSYohYSD = false;}
      if(RmZgAVzqVn == true){RmZgAVzqVn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PJFDQRVMET
{ 
  void zbRjSHRVOO()
  { 
      bool pbCVQCTsVA = false;
      bool aPukBKnUDl = false;
      bool rmbDfcmjuL = false;
      bool kScESVmQjV = false;
      bool wRqVxPxgLK = false;
      bool WpGHuCAypm = false;
      bool OiyKOHlqSf = false;
      bool WWjhoawFFP = false;
      bool eGXknuMVIP = false;
      bool UnZwHNTfGp = false;
      bool dFOfmAFYRU = false;
      bool GtsaIIKMWT = false;
      bool uQiCKhwnab = false;
      bool GQzPlZqrxm = false;
      bool omDnJZuzny = false;
      bool CGImtMWLUF = false;
      bool ERyoOpucoh = false;
      bool QSPjdHMtsk = false;
      bool lxzbZzHMUY = false;
      bool CfXriXoNZS = false;
      string bQuhiqdKoB;
      string zkeMKJlobS;
      string clBmghhBRN;
      string JdVbIMwiKy;
      string GTVsujJcri;
      string XamWtpOHBB;
      string IcraqUPCDx;
      string MCdcLIPHrx;
      string YFIipiqyhS;
      string xohJodatBZ;
      string UGYtWUwJKk;
      string ZGPEcCUJkI;
      string dQUkAXUUmh;
      string hUGRbRgNMU;
      string lgmxrqZdgl;
      string JQJrwDlntz;
      string AaVcDEAxbK;
      string VGxPWwcWrI;
      string xpmBYQLNVX;
      string esSMULKKtn;
      if(bQuhiqdKoB == UGYtWUwJKk){pbCVQCTsVA = true;}
      else if(UGYtWUwJKk == bQuhiqdKoB){dFOfmAFYRU = true;}
      if(zkeMKJlobS == ZGPEcCUJkI){aPukBKnUDl = true;}
      else if(ZGPEcCUJkI == zkeMKJlobS){GtsaIIKMWT = true;}
      if(clBmghhBRN == dQUkAXUUmh){rmbDfcmjuL = true;}
      else if(dQUkAXUUmh == clBmghhBRN){uQiCKhwnab = true;}
      if(JdVbIMwiKy == hUGRbRgNMU){kScESVmQjV = true;}
      else if(hUGRbRgNMU == JdVbIMwiKy){GQzPlZqrxm = true;}
      if(GTVsujJcri == lgmxrqZdgl){wRqVxPxgLK = true;}
      else if(lgmxrqZdgl == GTVsujJcri){omDnJZuzny = true;}
      if(XamWtpOHBB == JQJrwDlntz){WpGHuCAypm = true;}
      else if(JQJrwDlntz == XamWtpOHBB){CGImtMWLUF = true;}
      if(IcraqUPCDx == AaVcDEAxbK){OiyKOHlqSf = true;}
      else if(AaVcDEAxbK == IcraqUPCDx){ERyoOpucoh = true;}
      if(MCdcLIPHrx == VGxPWwcWrI){WWjhoawFFP = true;}
      if(YFIipiqyhS == xpmBYQLNVX){eGXknuMVIP = true;}
      if(xohJodatBZ == esSMULKKtn){UnZwHNTfGp = true;}
      while(VGxPWwcWrI == MCdcLIPHrx){QSPjdHMtsk = true;}
      while(xpmBYQLNVX == xpmBYQLNVX){lxzbZzHMUY = true;}
      while(esSMULKKtn == esSMULKKtn){CfXriXoNZS = true;}
      if(pbCVQCTsVA == true){pbCVQCTsVA = false;}
      if(aPukBKnUDl == true){aPukBKnUDl = false;}
      if(rmbDfcmjuL == true){rmbDfcmjuL = false;}
      if(kScESVmQjV == true){kScESVmQjV = false;}
      if(wRqVxPxgLK == true){wRqVxPxgLK = false;}
      if(WpGHuCAypm == true){WpGHuCAypm = false;}
      if(OiyKOHlqSf == true){OiyKOHlqSf = false;}
      if(WWjhoawFFP == true){WWjhoawFFP = false;}
      if(eGXknuMVIP == true){eGXknuMVIP = false;}
      if(UnZwHNTfGp == true){UnZwHNTfGp = false;}
      if(dFOfmAFYRU == true){dFOfmAFYRU = false;}
      if(GtsaIIKMWT == true){GtsaIIKMWT = false;}
      if(uQiCKhwnab == true){uQiCKhwnab = false;}
      if(GQzPlZqrxm == true){GQzPlZqrxm = false;}
      if(omDnJZuzny == true){omDnJZuzny = false;}
      if(CGImtMWLUF == true){CGImtMWLUF = false;}
      if(ERyoOpucoh == true){ERyoOpucoh = false;}
      if(QSPjdHMtsk == true){QSPjdHMtsk = false;}
      if(lxzbZzHMUY == true){lxzbZzHMUY = false;}
      if(CfXriXoNZS == true){CfXriXoNZS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KVGBQBHMHG
{ 
  void QtTnwBdgHa()
  { 
      bool RaFACYzibe = false;
      bool aiOsLUlOMr = false;
      bool QneLWmCLIz = false;
      bool QxxReqffUV = false;
      bool LzEWFVVzzr = false;
      bool mnWFOdusdO = false;
      bool VmZcOdkwNU = false;
      bool oFspfQiIGA = false;
      bool QDLPMbZrDB = false;
      bool ulCGAYYbHa = false;
      bool kZleDgtfZx = false;
      bool tmmcxSaKQm = false;
      bool DsrMZCCmpH = false;
      bool rHAePqRgLe = false;
      bool gsSGGIyZJg = false;
      bool xOKUXqgYFA = false;
      bool eHpRElmIMF = false;
      bool BtykFKalFQ = false;
      bool EccIKdxeHY = false;
      bool KrbKAZDABU = false;
      string sxumgRyRRh;
      string pkbWLBzDwE;
      string JayCkOMILR;
      string wGAsgmjiFB;
      string optBrQHcyT;
      string HaflGRysCR;
      string FoFAkjkhpX;
      string QQxuPTgxJU;
      string HjJrKUaNmO;
      string nqfmwAktPI;
      string eYmaCpckWl;
      string kBihKVeNoP;
      string JXuajZjJyP;
      string ilgBohwioT;
      string roqAdlIyca;
      string UXEAzHcLpc;
      string GSlHDyUgsb;
      string YwXVXTgtxx;
      string RkgXtLhfCg;
      string FksLNYDixe;
      if(sxumgRyRRh == eYmaCpckWl){RaFACYzibe = true;}
      else if(eYmaCpckWl == sxumgRyRRh){kZleDgtfZx = true;}
      if(pkbWLBzDwE == kBihKVeNoP){aiOsLUlOMr = true;}
      else if(kBihKVeNoP == pkbWLBzDwE){tmmcxSaKQm = true;}
      if(JayCkOMILR == JXuajZjJyP){QneLWmCLIz = true;}
      else if(JXuajZjJyP == JayCkOMILR){DsrMZCCmpH = true;}
      if(wGAsgmjiFB == ilgBohwioT){QxxReqffUV = true;}
      else if(ilgBohwioT == wGAsgmjiFB){rHAePqRgLe = true;}
      if(optBrQHcyT == roqAdlIyca){LzEWFVVzzr = true;}
      else if(roqAdlIyca == optBrQHcyT){gsSGGIyZJg = true;}
      if(HaflGRysCR == UXEAzHcLpc){mnWFOdusdO = true;}
      else if(UXEAzHcLpc == HaflGRysCR){xOKUXqgYFA = true;}
      if(FoFAkjkhpX == GSlHDyUgsb){VmZcOdkwNU = true;}
      else if(GSlHDyUgsb == FoFAkjkhpX){eHpRElmIMF = true;}
      if(QQxuPTgxJU == YwXVXTgtxx){oFspfQiIGA = true;}
      if(HjJrKUaNmO == RkgXtLhfCg){QDLPMbZrDB = true;}
      if(nqfmwAktPI == FksLNYDixe){ulCGAYYbHa = true;}
      while(YwXVXTgtxx == QQxuPTgxJU){BtykFKalFQ = true;}
      while(RkgXtLhfCg == RkgXtLhfCg){EccIKdxeHY = true;}
      while(FksLNYDixe == FksLNYDixe){KrbKAZDABU = true;}
      if(RaFACYzibe == true){RaFACYzibe = false;}
      if(aiOsLUlOMr == true){aiOsLUlOMr = false;}
      if(QneLWmCLIz == true){QneLWmCLIz = false;}
      if(QxxReqffUV == true){QxxReqffUV = false;}
      if(LzEWFVVzzr == true){LzEWFVVzzr = false;}
      if(mnWFOdusdO == true){mnWFOdusdO = false;}
      if(VmZcOdkwNU == true){VmZcOdkwNU = false;}
      if(oFspfQiIGA == true){oFspfQiIGA = false;}
      if(QDLPMbZrDB == true){QDLPMbZrDB = false;}
      if(ulCGAYYbHa == true){ulCGAYYbHa = false;}
      if(kZleDgtfZx == true){kZleDgtfZx = false;}
      if(tmmcxSaKQm == true){tmmcxSaKQm = false;}
      if(DsrMZCCmpH == true){DsrMZCCmpH = false;}
      if(rHAePqRgLe == true){rHAePqRgLe = false;}
      if(gsSGGIyZJg == true){gsSGGIyZJg = false;}
      if(xOKUXqgYFA == true){xOKUXqgYFA = false;}
      if(eHpRElmIMF == true){eHpRElmIMF = false;}
      if(BtykFKalFQ == true){BtykFKalFQ = false;}
      if(EccIKdxeHY == true){EccIKdxeHY = false;}
      if(KrbKAZDABU == true){KrbKAZDABU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QZHANDIYLV
{ 
  void TZlIexqAyk()
  { 
      bool kqymoalzoa = false;
      bool VDRaaWjNZF = false;
      bool BEmBmpHeGE = false;
      bool casuuMYsYw = false;
      bool PGEUuMRRKg = false;
      bool NGfiCfDxAz = false;
      bool SHsjxtJVfN = false;
      bool xpndouARFZ = false;
      bool XpUYpVtJrO = false;
      bool IbsZcHNTWA = false;
      bool DukwjXSCsG = false;
      bool flqZacmTta = false;
      bool AzdQFUxNAh = false;
      bool hguEWcEXoS = false;
      bool DqQkiWkSzz = false;
      bool UtYwADRUqO = false;
      bool aFBLYyqlDy = false;
      bool YOdaXIirhh = false;
      bool jdOAMmHyET = false;
      bool KjgarxpEMj = false;
      string yTuWmHLqur;
      string UAtmpZknJb;
      string dqjDcQDklF;
      string RYRJpDTuSr;
      string CnIlPVAZKN;
      string XLWTBGiqsV;
      string DaEpZwhkwl;
      string FoURYoiynH;
      string QdZXgGBxHj;
      string UcBwnbjSLT;
      string mOcYHhpFtM;
      string XkDkFZAgIT;
      string tkdLQcnYcx;
      string FPlUTBAAPy;
      string PwDuMjZPqO;
      string aDJrYCkQHe;
      string tRbwGHyhRD;
      string YAQKDxghzg;
      string DXgOWBFsuQ;
      string QirkDyUGnE;
      if(yTuWmHLqur == mOcYHhpFtM){kqymoalzoa = true;}
      else if(mOcYHhpFtM == yTuWmHLqur){DukwjXSCsG = true;}
      if(UAtmpZknJb == XkDkFZAgIT){VDRaaWjNZF = true;}
      else if(XkDkFZAgIT == UAtmpZknJb){flqZacmTta = true;}
      if(dqjDcQDklF == tkdLQcnYcx){BEmBmpHeGE = true;}
      else if(tkdLQcnYcx == dqjDcQDklF){AzdQFUxNAh = true;}
      if(RYRJpDTuSr == FPlUTBAAPy){casuuMYsYw = true;}
      else if(FPlUTBAAPy == RYRJpDTuSr){hguEWcEXoS = true;}
      if(CnIlPVAZKN == PwDuMjZPqO){PGEUuMRRKg = true;}
      else if(PwDuMjZPqO == CnIlPVAZKN){DqQkiWkSzz = true;}
      if(XLWTBGiqsV == aDJrYCkQHe){NGfiCfDxAz = true;}
      else if(aDJrYCkQHe == XLWTBGiqsV){UtYwADRUqO = true;}
      if(DaEpZwhkwl == tRbwGHyhRD){SHsjxtJVfN = true;}
      else if(tRbwGHyhRD == DaEpZwhkwl){aFBLYyqlDy = true;}
      if(FoURYoiynH == YAQKDxghzg){xpndouARFZ = true;}
      if(QdZXgGBxHj == DXgOWBFsuQ){XpUYpVtJrO = true;}
      if(UcBwnbjSLT == QirkDyUGnE){IbsZcHNTWA = true;}
      while(YAQKDxghzg == FoURYoiynH){YOdaXIirhh = true;}
      while(DXgOWBFsuQ == DXgOWBFsuQ){jdOAMmHyET = true;}
      while(QirkDyUGnE == QirkDyUGnE){KjgarxpEMj = true;}
      if(kqymoalzoa == true){kqymoalzoa = false;}
      if(VDRaaWjNZF == true){VDRaaWjNZF = false;}
      if(BEmBmpHeGE == true){BEmBmpHeGE = false;}
      if(casuuMYsYw == true){casuuMYsYw = false;}
      if(PGEUuMRRKg == true){PGEUuMRRKg = false;}
      if(NGfiCfDxAz == true){NGfiCfDxAz = false;}
      if(SHsjxtJVfN == true){SHsjxtJVfN = false;}
      if(xpndouARFZ == true){xpndouARFZ = false;}
      if(XpUYpVtJrO == true){XpUYpVtJrO = false;}
      if(IbsZcHNTWA == true){IbsZcHNTWA = false;}
      if(DukwjXSCsG == true){DukwjXSCsG = false;}
      if(flqZacmTta == true){flqZacmTta = false;}
      if(AzdQFUxNAh == true){AzdQFUxNAh = false;}
      if(hguEWcEXoS == true){hguEWcEXoS = false;}
      if(DqQkiWkSzz == true){DqQkiWkSzz = false;}
      if(UtYwADRUqO == true){UtYwADRUqO = false;}
      if(aFBLYyqlDy == true){aFBLYyqlDy = false;}
      if(YOdaXIirhh == true){YOdaXIirhh = false;}
      if(jdOAMmHyET == true){jdOAMmHyET = false;}
      if(KjgarxpEMj == true){KjgarxpEMj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGXRXDRDIZ
{ 
  void owYGPGWhHA()
  { 
      bool tfVIZkBROm = false;
      bool ySnGYZfRak = false;
      bool UrkGyOzdnp = false;
      bool QPFcxQTEtA = false;
      bool RcTgqJwnJV = false;
      bool WfpekBuOKK = false;
      bool lWcYWhMLII = false;
      bool GaWZSqXEPn = false;
      bool SLTSTkZaqw = false;
      bool VEtiOtAuKI = false;
      bool wjfBOuIPLs = false;
      bool dqzVqZCJFk = false;
      bool IkTMmBgnLX = false;
      bool qcsHrhfSDX = false;
      bool cJOyReEXqo = false;
      bool qpoYzLQSNN = false;
      bool OTEnBAxrdJ = false;
      bool sjGgIzVUtH = false;
      bool xIxVfBnTHg = false;
      bool RMEpJIEawR = false;
      string XVWXLsQqYk;
      string gDEhACPquy;
      string bQOclWDXMx;
      string HUdHqwGWQV;
      string MLXaJUaTQB;
      string PSFRBGGtkn;
      string psdbdLZwpD;
      string usZZkPsnSR;
      string wjGLgoOLGk;
      string oMkbfSgwwx;
      string uecNFWrffl;
      string NSaTrFmSto;
      string wNpFOiHytS;
      string hxqUWQGsFK;
      string wifTWVlRjZ;
      string fOBHAgnWyW;
      string OtlNEQbFwa;
      string ztNjrNhVir;
      string xoNUlSuiTp;
      string bjtiuCxRPG;
      if(XVWXLsQqYk == uecNFWrffl){tfVIZkBROm = true;}
      else if(uecNFWrffl == XVWXLsQqYk){wjfBOuIPLs = true;}
      if(gDEhACPquy == NSaTrFmSto){ySnGYZfRak = true;}
      else if(NSaTrFmSto == gDEhACPquy){dqzVqZCJFk = true;}
      if(bQOclWDXMx == wNpFOiHytS){UrkGyOzdnp = true;}
      else if(wNpFOiHytS == bQOclWDXMx){IkTMmBgnLX = true;}
      if(HUdHqwGWQV == hxqUWQGsFK){QPFcxQTEtA = true;}
      else if(hxqUWQGsFK == HUdHqwGWQV){qcsHrhfSDX = true;}
      if(MLXaJUaTQB == wifTWVlRjZ){RcTgqJwnJV = true;}
      else if(wifTWVlRjZ == MLXaJUaTQB){cJOyReEXqo = true;}
      if(PSFRBGGtkn == fOBHAgnWyW){WfpekBuOKK = true;}
      else if(fOBHAgnWyW == PSFRBGGtkn){qpoYzLQSNN = true;}
      if(psdbdLZwpD == OtlNEQbFwa){lWcYWhMLII = true;}
      else if(OtlNEQbFwa == psdbdLZwpD){OTEnBAxrdJ = true;}
      if(usZZkPsnSR == ztNjrNhVir){GaWZSqXEPn = true;}
      if(wjGLgoOLGk == xoNUlSuiTp){SLTSTkZaqw = true;}
      if(oMkbfSgwwx == bjtiuCxRPG){VEtiOtAuKI = true;}
      while(ztNjrNhVir == usZZkPsnSR){sjGgIzVUtH = true;}
      while(xoNUlSuiTp == xoNUlSuiTp){xIxVfBnTHg = true;}
      while(bjtiuCxRPG == bjtiuCxRPG){RMEpJIEawR = true;}
      if(tfVIZkBROm == true){tfVIZkBROm = false;}
      if(ySnGYZfRak == true){ySnGYZfRak = false;}
      if(UrkGyOzdnp == true){UrkGyOzdnp = false;}
      if(QPFcxQTEtA == true){QPFcxQTEtA = false;}
      if(RcTgqJwnJV == true){RcTgqJwnJV = false;}
      if(WfpekBuOKK == true){WfpekBuOKK = false;}
      if(lWcYWhMLII == true){lWcYWhMLII = false;}
      if(GaWZSqXEPn == true){GaWZSqXEPn = false;}
      if(SLTSTkZaqw == true){SLTSTkZaqw = false;}
      if(VEtiOtAuKI == true){VEtiOtAuKI = false;}
      if(wjfBOuIPLs == true){wjfBOuIPLs = false;}
      if(dqzVqZCJFk == true){dqzVqZCJFk = false;}
      if(IkTMmBgnLX == true){IkTMmBgnLX = false;}
      if(qcsHrhfSDX == true){qcsHrhfSDX = false;}
      if(cJOyReEXqo == true){cJOyReEXqo = false;}
      if(qpoYzLQSNN == true){qpoYzLQSNN = false;}
      if(OTEnBAxrdJ == true){OTEnBAxrdJ = false;}
      if(sjGgIzVUtH == true){sjGgIzVUtH = false;}
      if(xIxVfBnTHg == true){xIxVfBnTHg = false;}
      if(RMEpJIEawR == true){RMEpJIEawR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JXSAMMDVMR
{ 
  void rhQfEDNTXL()
  { 
      bool OTdwRQHpwV = false;
      bool rbzjGiHdMO = false;
      bool NYOxyHgNws = false;
      bool wjaNJJuSGt = false;
      bool QGGyoxVJyy = false;
      bool GQBgsoFfxK = false;
      bool jttDYIAlaw = false;
      bool noXRxHRQIB = false;
      bool kXOxlfisTT = false;
      bool EPVwKWMDYg = false;
      bool wjiBKQsiil = false;
      bool XnWuYMewQs = false;
      bool YGRGrYTaGa = false;
      bool uOraFBnNmV = false;
      bool lzJgwPrZXx = false;
      bool qPleIoRbIk = false;
      bool xRcIqIwwoW = false;
      bool XRIuGYxjKc = false;
      bool gsDIjebMSQ = false;
      bool iMEBXUWBpm = false;
      string aVDbrwflcf;
      string iLOzyYRrLq;
      string YwiAXQggYZ;
      string wYNlVKXTsc;
      string SsrfNXjjJS;
      string pFEAQelDEb;
      string PzMDiKxcdm;
      string ByzhXeEDlz;
      string fwXFiqTNVq;
      string YUOQNTfnwD;
      string ZHGVQrFVbk;
      string ZiQEwSbGUr;
      string pjHlNgiiTD;
      string yPGhYYpBop;
      string kxljQpDJTu;
      string qZTDNpzTHj;
      string IWCXmJbifX;
      string caRdHrxXUX;
      string dYOYLYwCTh;
      string YVsEhOuNwH;
      if(aVDbrwflcf == ZHGVQrFVbk){OTdwRQHpwV = true;}
      else if(ZHGVQrFVbk == aVDbrwflcf){wjiBKQsiil = true;}
      if(iLOzyYRrLq == ZiQEwSbGUr){rbzjGiHdMO = true;}
      else if(ZiQEwSbGUr == iLOzyYRrLq){XnWuYMewQs = true;}
      if(YwiAXQggYZ == pjHlNgiiTD){NYOxyHgNws = true;}
      else if(pjHlNgiiTD == YwiAXQggYZ){YGRGrYTaGa = true;}
      if(wYNlVKXTsc == yPGhYYpBop){wjaNJJuSGt = true;}
      else if(yPGhYYpBop == wYNlVKXTsc){uOraFBnNmV = true;}
      if(SsrfNXjjJS == kxljQpDJTu){QGGyoxVJyy = true;}
      else if(kxljQpDJTu == SsrfNXjjJS){lzJgwPrZXx = true;}
      if(pFEAQelDEb == qZTDNpzTHj){GQBgsoFfxK = true;}
      else if(qZTDNpzTHj == pFEAQelDEb){qPleIoRbIk = true;}
      if(PzMDiKxcdm == IWCXmJbifX){jttDYIAlaw = true;}
      else if(IWCXmJbifX == PzMDiKxcdm){xRcIqIwwoW = true;}
      if(ByzhXeEDlz == caRdHrxXUX){noXRxHRQIB = true;}
      if(fwXFiqTNVq == dYOYLYwCTh){kXOxlfisTT = true;}
      if(YUOQNTfnwD == YVsEhOuNwH){EPVwKWMDYg = true;}
      while(caRdHrxXUX == ByzhXeEDlz){XRIuGYxjKc = true;}
      while(dYOYLYwCTh == dYOYLYwCTh){gsDIjebMSQ = true;}
      while(YVsEhOuNwH == YVsEhOuNwH){iMEBXUWBpm = true;}
      if(OTdwRQHpwV == true){OTdwRQHpwV = false;}
      if(rbzjGiHdMO == true){rbzjGiHdMO = false;}
      if(NYOxyHgNws == true){NYOxyHgNws = false;}
      if(wjaNJJuSGt == true){wjaNJJuSGt = false;}
      if(QGGyoxVJyy == true){QGGyoxVJyy = false;}
      if(GQBgsoFfxK == true){GQBgsoFfxK = false;}
      if(jttDYIAlaw == true){jttDYIAlaw = false;}
      if(noXRxHRQIB == true){noXRxHRQIB = false;}
      if(kXOxlfisTT == true){kXOxlfisTT = false;}
      if(EPVwKWMDYg == true){EPVwKWMDYg = false;}
      if(wjiBKQsiil == true){wjiBKQsiil = false;}
      if(XnWuYMewQs == true){XnWuYMewQs = false;}
      if(YGRGrYTaGa == true){YGRGrYTaGa = false;}
      if(uOraFBnNmV == true){uOraFBnNmV = false;}
      if(lzJgwPrZXx == true){lzJgwPrZXx = false;}
      if(qPleIoRbIk == true){qPleIoRbIk = false;}
      if(xRcIqIwwoW == true){xRcIqIwwoW = false;}
      if(XRIuGYxjKc == true){XRIuGYxjKc = false;}
      if(gsDIjebMSQ == true){gsDIjebMSQ = false;}
      if(iMEBXUWBpm == true){iMEBXUWBpm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZPATKRSQRD
{ 
  void nXAtXWAwGg()
  { 
      bool kOSQrlHxGy = false;
      bool lLbdIQogPJ = false;
      bool RynZoiLXkE = false;
      bool cOUxhjouob = false;
      bool dwoyttcbWa = false;
      bool chAstlasaI = false;
      bool aiMBUXpeuX = false;
      bool atqneVJofu = false;
      bool GiBJbuObCw = false;
      bool JwTgAtimdV = false;
      bool DyfyAhpMNY = false;
      bool ckNeBqgDZZ = false;
      bool IObzNeZKmj = false;
      bool lVKJqIDCJs = false;
      bool ECNdSYhneJ = false;
      bool MfNEMoVgjU = false;
      bool IfZdmHZDnr = false;
      bool netfUGBygo = false;
      bool xkecWFHGwC = false;
      bool lVRnkYbjpL = false;
      string uyCrtUJLJP;
      string hysRAQkzgl;
      string oZogxNaoZr;
      string iHggaFsYeG;
      string tolyjIRMpe;
      string TrCoqUIUtg;
      string tTlRfZQLpu;
      string WMUarznpxo;
      string uNztXpEqoG;
      string wXexMZCTSK;
      string qFWuHHXbxq;
      string gRXEkfUqso;
      string UYVjyzhWNS;
      string wTXmypqDmQ;
      string SctxYezZLg;
      string ELZcpRjlxH;
      string YANdtMskGu;
      string nRDcWqeXKT;
      string zILgOktuxg;
      string FEFerROPCM;
      if(uyCrtUJLJP == qFWuHHXbxq){kOSQrlHxGy = true;}
      else if(qFWuHHXbxq == uyCrtUJLJP){DyfyAhpMNY = true;}
      if(hysRAQkzgl == gRXEkfUqso){lLbdIQogPJ = true;}
      else if(gRXEkfUqso == hysRAQkzgl){ckNeBqgDZZ = true;}
      if(oZogxNaoZr == UYVjyzhWNS){RynZoiLXkE = true;}
      else if(UYVjyzhWNS == oZogxNaoZr){IObzNeZKmj = true;}
      if(iHggaFsYeG == wTXmypqDmQ){cOUxhjouob = true;}
      else if(wTXmypqDmQ == iHggaFsYeG){lVKJqIDCJs = true;}
      if(tolyjIRMpe == SctxYezZLg){dwoyttcbWa = true;}
      else if(SctxYezZLg == tolyjIRMpe){ECNdSYhneJ = true;}
      if(TrCoqUIUtg == ELZcpRjlxH){chAstlasaI = true;}
      else if(ELZcpRjlxH == TrCoqUIUtg){MfNEMoVgjU = true;}
      if(tTlRfZQLpu == YANdtMskGu){aiMBUXpeuX = true;}
      else if(YANdtMskGu == tTlRfZQLpu){IfZdmHZDnr = true;}
      if(WMUarznpxo == nRDcWqeXKT){atqneVJofu = true;}
      if(uNztXpEqoG == zILgOktuxg){GiBJbuObCw = true;}
      if(wXexMZCTSK == FEFerROPCM){JwTgAtimdV = true;}
      while(nRDcWqeXKT == WMUarznpxo){netfUGBygo = true;}
      while(zILgOktuxg == zILgOktuxg){xkecWFHGwC = true;}
      while(FEFerROPCM == FEFerROPCM){lVRnkYbjpL = true;}
      if(kOSQrlHxGy == true){kOSQrlHxGy = false;}
      if(lLbdIQogPJ == true){lLbdIQogPJ = false;}
      if(RynZoiLXkE == true){RynZoiLXkE = false;}
      if(cOUxhjouob == true){cOUxhjouob = false;}
      if(dwoyttcbWa == true){dwoyttcbWa = false;}
      if(chAstlasaI == true){chAstlasaI = false;}
      if(aiMBUXpeuX == true){aiMBUXpeuX = false;}
      if(atqneVJofu == true){atqneVJofu = false;}
      if(GiBJbuObCw == true){GiBJbuObCw = false;}
      if(JwTgAtimdV == true){JwTgAtimdV = false;}
      if(DyfyAhpMNY == true){DyfyAhpMNY = false;}
      if(ckNeBqgDZZ == true){ckNeBqgDZZ = false;}
      if(IObzNeZKmj == true){IObzNeZKmj = false;}
      if(lVKJqIDCJs == true){lVKJqIDCJs = false;}
      if(ECNdSYhneJ == true){ECNdSYhneJ = false;}
      if(MfNEMoVgjU == true){MfNEMoVgjU = false;}
      if(IfZdmHZDnr == true){IfZdmHZDnr = false;}
      if(netfUGBygo == true){netfUGBygo = false;}
      if(xkecWFHGwC == true){xkecWFHGwC = false;}
      if(lVRnkYbjpL == true){lVRnkYbjpL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CMUWQLSHGE
{ 
  void SPpSlxkTBo()
  { 
      bool VEEGWZnrNY = false;
      bool shDqngFPWy = false;
      bool DIEUYXXZCt = false;
      bool ZwxhJITdEw = false;
      bool kVjDZZNohJ = false;
      bool RtkopNAjgz = false;
      bool CNoTyxjVhe = false;
      bool MaLaMhXBuy = false;
      bool KhrsbeLIqw = false;
      bool IjxEsXfQEc = false;
      bool orHCwqiJbI = false;
      bool oznioTUwrT = false;
      bool kbelWcdGho = false;
      bool BHwRISaowj = false;
      bool wBghGIuNPY = false;
      bool DjXjqNMVfT = false;
      bool NbbmGgCWZW = false;
      bool sezHXitweN = false;
      bool gPpIlRiMZu = false;
      bool FFJcWTZsaY = false;
      string GhoyxBUSUR;
      string YUdiKwqQuG;
      string KNHtXwxhZJ;
      string JEVnTnwZwE;
      string WwmSOCFgAA;
      string ohVburZuaA;
      string DmrKHTzoOV;
      string zQTpiNaoeU;
      string qPgYUbhssb;
      string NAzwBjDbKt;
      string DPSdBXNfrh;
      string QkPFImGTpe;
      string lFwmIzRXoz;
      string JzdjRbxCXw;
      string NBBLLcksmN;
      string djkfIxSfVC;
      string FpqsXQGfng;
      string pDwsRjEkbe;
      string NYjaVZNybT;
      string IRfVpXKHmt;
      if(GhoyxBUSUR == DPSdBXNfrh){VEEGWZnrNY = true;}
      else if(DPSdBXNfrh == GhoyxBUSUR){orHCwqiJbI = true;}
      if(YUdiKwqQuG == QkPFImGTpe){shDqngFPWy = true;}
      else if(QkPFImGTpe == YUdiKwqQuG){oznioTUwrT = true;}
      if(KNHtXwxhZJ == lFwmIzRXoz){DIEUYXXZCt = true;}
      else if(lFwmIzRXoz == KNHtXwxhZJ){kbelWcdGho = true;}
      if(JEVnTnwZwE == JzdjRbxCXw){ZwxhJITdEw = true;}
      else if(JzdjRbxCXw == JEVnTnwZwE){BHwRISaowj = true;}
      if(WwmSOCFgAA == NBBLLcksmN){kVjDZZNohJ = true;}
      else if(NBBLLcksmN == WwmSOCFgAA){wBghGIuNPY = true;}
      if(ohVburZuaA == djkfIxSfVC){RtkopNAjgz = true;}
      else if(djkfIxSfVC == ohVburZuaA){DjXjqNMVfT = true;}
      if(DmrKHTzoOV == FpqsXQGfng){CNoTyxjVhe = true;}
      else if(FpqsXQGfng == DmrKHTzoOV){NbbmGgCWZW = true;}
      if(zQTpiNaoeU == pDwsRjEkbe){MaLaMhXBuy = true;}
      if(qPgYUbhssb == NYjaVZNybT){KhrsbeLIqw = true;}
      if(NAzwBjDbKt == IRfVpXKHmt){IjxEsXfQEc = true;}
      while(pDwsRjEkbe == zQTpiNaoeU){sezHXitweN = true;}
      while(NYjaVZNybT == NYjaVZNybT){gPpIlRiMZu = true;}
      while(IRfVpXKHmt == IRfVpXKHmt){FFJcWTZsaY = true;}
      if(VEEGWZnrNY == true){VEEGWZnrNY = false;}
      if(shDqngFPWy == true){shDqngFPWy = false;}
      if(DIEUYXXZCt == true){DIEUYXXZCt = false;}
      if(ZwxhJITdEw == true){ZwxhJITdEw = false;}
      if(kVjDZZNohJ == true){kVjDZZNohJ = false;}
      if(RtkopNAjgz == true){RtkopNAjgz = false;}
      if(CNoTyxjVhe == true){CNoTyxjVhe = false;}
      if(MaLaMhXBuy == true){MaLaMhXBuy = false;}
      if(KhrsbeLIqw == true){KhrsbeLIqw = false;}
      if(IjxEsXfQEc == true){IjxEsXfQEc = false;}
      if(orHCwqiJbI == true){orHCwqiJbI = false;}
      if(oznioTUwrT == true){oznioTUwrT = false;}
      if(kbelWcdGho == true){kbelWcdGho = false;}
      if(BHwRISaowj == true){BHwRISaowj = false;}
      if(wBghGIuNPY == true){wBghGIuNPY = false;}
      if(DjXjqNMVfT == true){DjXjqNMVfT = false;}
      if(NbbmGgCWZW == true){NbbmGgCWZW = false;}
      if(sezHXitweN == true){sezHXitweN = false;}
      if(gPpIlRiMZu == true){gPpIlRiMZu = false;}
      if(FFJcWTZsaY == true){FFJcWTZsaY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WGGNTJFJLC
{ 
  void rGiYNkUMWw()
  { 
      bool UBMxulykPj = false;
      bool ubfzMAkABq = false;
      bool XMKdWKiKxi = false;
      bool VMEHgXkmAd = false;
      bool NlnZkjszBr = false;
      bool gtXEsIpiZj = false;
      bool DmmfNhWYSo = false;
      bool PyAWclYjsm = false;
      bool RiJFCboAOY = false;
      bool gCMPaayHMC = false;
      bool MTgMcitAbH = false;
      bool iFpmSUchdl = false;
      bool sWKsHNkjwB = false;
      bool mQXpaxBxbT = false;
      bool hoYHoaLZwF = false;
      bool yQdaIpJmEP = false;
      bool xJDZTShzMV = false;
      bool TfFKEEyDEf = false;
      bool BLnpCWlxgj = false;
      bool mNrMVXkymV = false;
      string bMxkFjGSoA;
      string bunIqyyEuJ;
      string jTAytWCjLt;
      string iFcEPhAjka;
      string XDHYeZJiwd;
      string hGqlSHMzqi;
      string hVGuRVRisI;
      string xOTTkfMaTU;
      string MTngLbOpkH;
      string VBsCsBwLGI;
      string HZomgTmWAl;
      string ukfVVNhZip;
      string HaykmuUQaj;
      string iAUKMmdAAr;
      string nqpyMkVWfe;
      string TWcQAgbEAl;
      string yVwQDuPUJi;
      string jhYqBQkzYB;
      string YykuPLXDJf;
      string LYzNsRtYuQ;
      if(bMxkFjGSoA == HZomgTmWAl){UBMxulykPj = true;}
      else if(HZomgTmWAl == bMxkFjGSoA){MTgMcitAbH = true;}
      if(bunIqyyEuJ == ukfVVNhZip){ubfzMAkABq = true;}
      else if(ukfVVNhZip == bunIqyyEuJ){iFpmSUchdl = true;}
      if(jTAytWCjLt == HaykmuUQaj){XMKdWKiKxi = true;}
      else if(HaykmuUQaj == jTAytWCjLt){sWKsHNkjwB = true;}
      if(iFcEPhAjka == iAUKMmdAAr){VMEHgXkmAd = true;}
      else if(iAUKMmdAAr == iFcEPhAjka){mQXpaxBxbT = true;}
      if(XDHYeZJiwd == nqpyMkVWfe){NlnZkjszBr = true;}
      else if(nqpyMkVWfe == XDHYeZJiwd){hoYHoaLZwF = true;}
      if(hGqlSHMzqi == TWcQAgbEAl){gtXEsIpiZj = true;}
      else if(TWcQAgbEAl == hGqlSHMzqi){yQdaIpJmEP = true;}
      if(hVGuRVRisI == yVwQDuPUJi){DmmfNhWYSo = true;}
      else if(yVwQDuPUJi == hVGuRVRisI){xJDZTShzMV = true;}
      if(xOTTkfMaTU == jhYqBQkzYB){PyAWclYjsm = true;}
      if(MTngLbOpkH == YykuPLXDJf){RiJFCboAOY = true;}
      if(VBsCsBwLGI == LYzNsRtYuQ){gCMPaayHMC = true;}
      while(jhYqBQkzYB == xOTTkfMaTU){TfFKEEyDEf = true;}
      while(YykuPLXDJf == YykuPLXDJf){BLnpCWlxgj = true;}
      while(LYzNsRtYuQ == LYzNsRtYuQ){mNrMVXkymV = true;}
      if(UBMxulykPj == true){UBMxulykPj = false;}
      if(ubfzMAkABq == true){ubfzMAkABq = false;}
      if(XMKdWKiKxi == true){XMKdWKiKxi = false;}
      if(VMEHgXkmAd == true){VMEHgXkmAd = false;}
      if(NlnZkjszBr == true){NlnZkjszBr = false;}
      if(gtXEsIpiZj == true){gtXEsIpiZj = false;}
      if(DmmfNhWYSo == true){DmmfNhWYSo = false;}
      if(PyAWclYjsm == true){PyAWclYjsm = false;}
      if(RiJFCboAOY == true){RiJFCboAOY = false;}
      if(gCMPaayHMC == true){gCMPaayHMC = false;}
      if(MTgMcitAbH == true){MTgMcitAbH = false;}
      if(iFpmSUchdl == true){iFpmSUchdl = false;}
      if(sWKsHNkjwB == true){sWKsHNkjwB = false;}
      if(mQXpaxBxbT == true){mQXpaxBxbT = false;}
      if(hoYHoaLZwF == true){hoYHoaLZwF = false;}
      if(yQdaIpJmEP == true){yQdaIpJmEP = false;}
      if(xJDZTShzMV == true){xJDZTShzMV = false;}
      if(TfFKEEyDEf == true){TfFKEEyDEf = false;}
      if(BLnpCWlxgj == true){BLnpCWlxgj = false;}
      if(mNrMVXkymV == true){mNrMVXkymV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DVDTKVCMXG
{ 
  void fUCIsHLltj()
  { 
      bool irkOZdLkFV = false;
      bool bYpxmnIPos = false;
      bool nQzIgKWsCh = false;
      bool XQqtPXNnYZ = false;
      bool yMVwTqShAy = false;
      bool mewHESrbgO = false;
      bool HRhWyKhugP = false;
      bool ZUqPtatDnp = false;
      bool rnrEusTiow = false;
      bool flGJRgdyyI = false;
      bool IWAkXRmgNc = false;
      bool YnmqWSYcbE = false;
      bool qzGkjnNgxN = false;
      bool xuFfgVnHgc = false;
      bool FlULXqyPmz = false;
      bool HBWsRJPOBi = false;
      bool EFjzfciHJA = false;
      bool dQwyzEdtMs = false;
      bool pxtyFuXLNX = false;
      bool GYGxXzCUfu = false;
      string zIgKrSAFJy;
      string KYpVOpwgYe;
      string iZajrPhYKp;
      string ZPgjOLglWi;
      string kNKtLFTBZn;
      string lnyWaZhxRc;
      string kbuTXtrFGD;
      string JJKpsUPfXm;
      string wfyVDlRJJo;
      string ciUsyJRqVQ;
      string MNtWdccHdF;
      string KCYefEcYPl;
      string chwRZaoQrj;
      string CXKGZhkbqa;
      string IJfDeaKoNs;
      string fsaindRcwD;
      string nMOsClqREy;
      string SBgodSCrmz;
      string PzDzEJxaRu;
      string QIenlutlBs;
      if(zIgKrSAFJy == MNtWdccHdF){irkOZdLkFV = true;}
      else if(MNtWdccHdF == zIgKrSAFJy){IWAkXRmgNc = true;}
      if(KYpVOpwgYe == KCYefEcYPl){bYpxmnIPos = true;}
      else if(KCYefEcYPl == KYpVOpwgYe){YnmqWSYcbE = true;}
      if(iZajrPhYKp == chwRZaoQrj){nQzIgKWsCh = true;}
      else if(chwRZaoQrj == iZajrPhYKp){qzGkjnNgxN = true;}
      if(ZPgjOLglWi == CXKGZhkbqa){XQqtPXNnYZ = true;}
      else if(CXKGZhkbqa == ZPgjOLglWi){xuFfgVnHgc = true;}
      if(kNKtLFTBZn == IJfDeaKoNs){yMVwTqShAy = true;}
      else if(IJfDeaKoNs == kNKtLFTBZn){FlULXqyPmz = true;}
      if(lnyWaZhxRc == fsaindRcwD){mewHESrbgO = true;}
      else if(fsaindRcwD == lnyWaZhxRc){HBWsRJPOBi = true;}
      if(kbuTXtrFGD == nMOsClqREy){HRhWyKhugP = true;}
      else if(nMOsClqREy == kbuTXtrFGD){EFjzfciHJA = true;}
      if(JJKpsUPfXm == SBgodSCrmz){ZUqPtatDnp = true;}
      if(wfyVDlRJJo == PzDzEJxaRu){rnrEusTiow = true;}
      if(ciUsyJRqVQ == QIenlutlBs){flGJRgdyyI = true;}
      while(SBgodSCrmz == JJKpsUPfXm){dQwyzEdtMs = true;}
      while(PzDzEJxaRu == PzDzEJxaRu){pxtyFuXLNX = true;}
      while(QIenlutlBs == QIenlutlBs){GYGxXzCUfu = true;}
      if(irkOZdLkFV == true){irkOZdLkFV = false;}
      if(bYpxmnIPos == true){bYpxmnIPos = false;}
      if(nQzIgKWsCh == true){nQzIgKWsCh = false;}
      if(XQqtPXNnYZ == true){XQqtPXNnYZ = false;}
      if(yMVwTqShAy == true){yMVwTqShAy = false;}
      if(mewHESrbgO == true){mewHESrbgO = false;}
      if(HRhWyKhugP == true){HRhWyKhugP = false;}
      if(ZUqPtatDnp == true){ZUqPtatDnp = false;}
      if(rnrEusTiow == true){rnrEusTiow = false;}
      if(flGJRgdyyI == true){flGJRgdyyI = false;}
      if(IWAkXRmgNc == true){IWAkXRmgNc = false;}
      if(YnmqWSYcbE == true){YnmqWSYcbE = false;}
      if(qzGkjnNgxN == true){qzGkjnNgxN = false;}
      if(xuFfgVnHgc == true){xuFfgVnHgc = false;}
      if(FlULXqyPmz == true){FlULXqyPmz = false;}
      if(HBWsRJPOBi == true){HBWsRJPOBi = false;}
      if(EFjzfciHJA == true){EFjzfciHJA = false;}
      if(dQwyzEdtMs == true){dQwyzEdtMs = false;}
      if(pxtyFuXLNX == true){pxtyFuXLNX = false;}
      if(GYGxXzCUfu == true){GYGxXzCUfu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JINFGLWCBL
{ 
  void KqiyXAzozm()
  { 
      bool WudYuVbUqb = false;
      bool IGxZACVquM = false;
      bool RWCIlajQzy = false;
      bool XGauBLLPlz = false;
      bool PTiFcRYOMO = false;
      bool BdEkQzsUlT = false;
      bool lLUrDBeBYo = false;
      bool qFEuwxnwfU = false;
      bool BVEkxtCpeB = false;
      bool RpcRNEzqBa = false;
      bool lXoWXuYInS = false;
      bool LwoRSQHitJ = false;
      bool zoVXWAclhr = false;
      bool ywuEhcfgNC = false;
      bool UtCLoVBKzx = false;
      bool wPwqbxBRAW = false;
      bool RlZuUPBjio = false;
      bool jZVroFmKhB = false;
      bool yRmkuhADck = false;
      bool bNgpjiTGqZ = false;
      string uPxoNELZra;
      string kYlUpSxkiT;
      string RfdABrUUMF;
      string MECHiqOLRW;
      string xQxboKiepy;
      string qzKEDOlxnV;
      string jpMmOgWdly;
      string DkSMWBiBKp;
      string IpeONMsyDT;
      string FRWwlGDJNI;
      string nFrqtFgygC;
      string fklyNtLyYB;
      string mXZRslOWZQ;
      string xZmCCDxmUI;
      string ftQBnUeYir;
      string tFkMUPeayH;
      string qJYQEFxjuJ;
      string xYcQUsGXdX;
      string GongVrnagl;
      string XVnMQWUzxh;
      if(uPxoNELZra == nFrqtFgygC){WudYuVbUqb = true;}
      else if(nFrqtFgygC == uPxoNELZra){lXoWXuYInS = true;}
      if(kYlUpSxkiT == fklyNtLyYB){IGxZACVquM = true;}
      else if(fklyNtLyYB == kYlUpSxkiT){LwoRSQHitJ = true;}
      if(RfdABrUUMF == mXZRslOWZQ){RWCIlajQzy = true;}
      else if(mXZRslOWZQ == RfdABrUUMF){zoVXWAclhr = true;}
      if(MECHiqOLRW == xZmCCDxmUI){XGauBLLPlz = true;}
      else if(xZmCCDxmUI == MECHiqOLRW){ywuEhcfgNC = true;}
      if(xQxboKiepy == ftQBnUeYir){PTiFcRYOMO = true;}
      else if(ftQBnUeYir == xQxboKiepy){UtCLoVBKzx = true;}
      if(qzKEDOlxnV == tFkMUPeayH){BdEkQzsUlT = true;}
      else if(tFkMUPeayH == qzKEDOlxnV){wPwqbxBRAW = true;}
      if(jpMmOgWdly == qJYQEFxjuJ){lLUrDBeBYo = true;}
      else if(qJYQEFxjuJ == jpMmOgWdly){RlZuUPBjio = true;}
      if(DkSMWBiBKp == xYcQUsGXdX){qFEuwxnwfU = true;}
      if(IpeONMsyDT == GongVrnagl){BVEkxtCpeB = true;}
      if(FRWwlGDJNI == XVnMQWUzxh){RpcRNEzqBa = true;}
      while(xYcQUsGXdX == DkSMWBiBKp){jZVroFmKhB = true;}
      while(GongVrnagl == GongVrnagl){yRmkuhADck = true;}
      while(XVnMQWUzxh == XVnMQWUzxh){bNgpjiTGqZ = true;}
      if(WudYuVbUqb == true){WudYuVbUqb = false;}
      if(IGxZACVquM == true){IGxZACVquM = false;}
      if(RWCIlajQzy == true){RWCIlajQzy = false;}
      if(XGauBLLPlz == true){XGauBLLPlz = false;}
      if(PTiFcRYOMO == true){PTiFcRYOMO = false;}
      if(BdEkQzsUlT == true){BdEkQzsUlT = false;}
      if(lLUrDBeBYo == true){lLUrDBeBYo = false;}
      if(qFEuwxnwfU == true){qFEuwxnwfU = false;}
      if(BVEkxtCpeB == true){BVEkxtCpeB = false;}
      if(RpcRNEzqBa == true){RpcRNEzqBa = false;}
      if(lXoWXuYInS == true){lXoWXuYInS = false;}
      if(LwoRSQHitJ == true){LwoRSQHitJ = false;}
      if(zoVXWAclhr == true){zoVXWAclhr = false;}
      if(ywuEhcfgNC == true){ywuEhcfgNC = false;}
      if(UtCLoVBKzx == true){UtCLoVBKzx = false;}
      if(wPwqbxBRAW == true){wPwqbxBRAW = false;}
      if(RlZuUPBjio == true){RlZuUPBjio = false;}
      if(jZVroFmKhB == true){jZVroFmKhB = false;}
      if(yRmkuhADck == true){yRmkuhADck = false;}
      if(bNgpjiTGqZ == true){bNgpjiTGqZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKCAKYWNGY
{ 
  void oWobmilPGM()
  { 
      bool hTfstZtqHu = false;
      bool pVYYQoFjgt = false;
      bool RlhsrsmTaw = false;
      bool FNEBTZegSW = false;
      bool cNtnCQdoad = false;
      bool mXfczullBA = false;
      bool lZPLocQXFq = false;
      bool JXRKQErtqa = false;
      bool OyrxJhhbCX = false;
      bool nsfRjDxiyZ = false;
      bool AGjjTOGULt = false;
      bool DqtZlngRBG = false;
      bool tnVgCPrzaN = false;
      bool GJuRaINIdu = false;
      bool bMQHTxyFfu = false;
      bool VfhqeMkCgE = false;
      bool VGtymtuczd = false;
      bool aYnGehXNNF = false;
      bool QmTeqabElN = false;
      bool WKaZYURRTZ = false;
      string ulsVaoIabg;
      string MtnFyBshLq;
      string kwmQhOBbOR;
      string QqkkzLYBxX;
      string ziIbwpQFlT;
      string UNmszzzcmL;
      string ngLJQVICGl;
      string bqjmqCmKTq;
      string xuouwCDrlz;
      string MwNljSWyLa;
      string hNzAqddzBx;
      string LoJwNsqQMN;
      string RQQGZfcyDY;
      string eozrJjwoDS;
      string YEponXlRXq;
      string bGkxIQxraL;
      string AfwcRVoRld;
      string wBMtoNabSC;
      string tLZMwXECir;
      string lDOrSrHMWR;
      if(ulsVaoIabg == hNzAqddzBx){hTfstZtqHu = true;}
      else if(hNzAqddzBx == ulsVaoIabg){AGjjTOGULt = true;}
      if(MtnFyBshLq == LoJwNsqQMN){pVYYQoFjgt = true;}
      else if(LoJwNsqQMN == MtnFyBshLq){DqtZlngRBG = true;}
      if(kwmQhOBbOR == RQQGZfcyDY){RlhsrsmTaw = true;}
      else if(RQQGZfcyDY == kwmQhOBbOR){tnVgCPrzaN = true;}
      if(QqkkzLYBxX == eozrJjwoDS){FNEBTZegSW = true;}
      else if(eozrJjwoDS == QqkkzLYBxX){GJuRaINIdu = true;}
      if(ziIbwpQFlT == YEponXlRXq){cNtnCQdoad = true;}
      else if(YEponXlRXq == ziIbwpQFlT){bMQHTxyFfu = true;}
      if(UNmszzzcmL == bGkxIQxraL){mXfczullBA = true;}
      else if(bGkxIQxraL == UNmszzzcmL){VfhqeMkCgE = true;}
      if(ngLJQVICGl == AfwcRVoRld){lZPLocQXFq = true;}
      else if(AfwcRVoRld == ngLJQVICGl){VGtymtuczd = true;}
      if(bqjmqCmKTq == wBMtoNabSC){JXRKQErtqa = true;}
      if(xuouwCDrlz == tLZMwXECir){OyrxJhhbCX = true;}
      if(MwNljSWyLa == lDOrSrHMWR){nsfRjDxiyZ = true;}
      while(wBMtoNabSC == bqjmqCmKTq){aYnGehXNNF = true;}
      while(tLZMwXECir == tLZMwXECir){QmTeqabElN = true;}
      while(lDOrSrHMWR == lDOrSrHMWR){WKaZYURRTZ = true;}
      if(hTfstZtqHu == true){hTfstZtqHu = false;}
      if(pVYYQoFjgt == true){pVYYQoFjgt = false;}
      if(RlhsrsmTaw == true){RlhsrsmTaw = false;}
      if(FNEBTZegSW == true){FNEBTZegSW = false;}
      if(cNtnCQdoad == true){cNtnCQdoad = false;}
      if(mXfczullBA == true){mXfczullBA = false;}
      if(lZPLocQXFq == true){lZPLocQXFq = false;}
      if(JXRKQErtqa == true){JXRKQErtqa = false;}
      if(OyrxJhhbCX == true){OyrxJhhbCX = false;}
      if(nsfRjDxiyZ == true){nsfRjDxiyZ = false;}
      if(AGjjTOGULt == true){AGjjTOGULt = false;}
      if(DqtZlngRBG == true){DqtZlngRBG = false;}
      if(tnVgCPrzaN == true){tnVgCPrzaN = false;}
      if(GJuRaINIdu == true){GJuRaINIdu = false;}
      if(bMQHTxyFfu == true){bMQHTxyFfu = false;}
      if(VfhqeMkCgE == true){VfhqeMkCgE = false;}
      if(VGtymtuczd == true){VGtymtuczd = false;}
      if(aYnGehXNNF == true){aYnGehXNNF = false;}
      if(QmTeqabElN == true){QmTeqabElN = false;}
      if(WKaZYURRTZ == true){WKaZYURRTZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SVMTDBVTBJ
{ 
  void MLLnEzFlaF()
  { 
      bool nmQJQcDpkM = false;
      bool qVyNBZehTQ = false;
      bool HAwceIpVkM = false;
      bool jVLKrnHSGA = false;
      bool npyYaaCrEo = false;
      bool wqtyGmqneH = false;
      bool mgEYcVJmUM = false;
      bool SLbSbQCWBE = false;
      bool GxRuPrbMEF = false;
      bool wSmyMHkZwF = false;
      bool QPWqWjPaWo = false;
      bool kTlaBpOJIj = false;
      bool txiPPzYcFT = false;
      bool fcawmqZaYf = false;
      bool cApOTcgMxW = false;
      bool rbQLLTfHaW = false;
      bool LlUCJIromK = false;
      bool PnjcHsGUum = false;
      bool SLfibELPkT = false;
      bool KSzCTpemEL = false;
      string xWOwsVYRpP;
      string QrywpnxdYt;
      string UFYCqkNayY;
      string ptluGQaILQ;
      string TIYUhbxoZn;
      string YmLZrryMFH;
      string HyTQZWGCpY;
      string MnRHZLfDUP;
      string nYBJzDhLDN;
      string SOCEJVoIuL;
      string VuzAakUDAf;
      string LtroTiwJQV;
      string ntybFylNyD;
      string WXIIsrYAhO;
      string heKXCYWMka;
      string YeqYWawXtc;
      string zHFxInkiwa;
      string JwbBmJiaZg;
      string bYcWdrfjlS;
      string wAGFPaZNOO;
      if(xWOwsVYRpP == VuzAakUDAf){nmQJQcDpkM = true;}
      else if(VuzAakUDAf == xWOwsVYRpP){QPWqWjPaWo = true;}
      if(QrywpnxdYt == LtroTiwJQV){qVyNBZehTQ = true;}
      else if(LtroTiwJQV == QrywpnxdYt){kTlaBpOJIj = true;}
      if(UFYCqkNayY == ntybFylNyD){HAwceIpVkM = true;}
      else if(ntybFylNyD == UFYCqkNayY){txiPPzYcFT = true;}
      if(ptluGQaILQ == WXIIsrYAhO){jVLKrnHSGA = true;}
      else if(WXIIsrYAhO == ptluGQaILQ){fcawmqZaYf = true;}
      if(TIYUhbxoZn == heKXCYWMka){npyYaaCrEo = true;}
      else if(heKXCYWMka == TIYUhbxoZn){cApOTcgMxW = true;}
      if(YmLZrryMFH == YeqYWawXtc){wqtyGmqneH = true;}
      else if(YeqYWawXtc == YmLZrryMFH){rbQLLTfHaW = true;}
      if(HyTQZWGCpY == zHFxInkiwa){mgEYcVJmUM = true;}
      else if(zHFxInkiwa == HyTQZWGCpY){LlUCJIromK = true;}
      if(MnRHZLfDUP == JwbBmJiaZg){SLbSbQCWBE = true;}
      if(nYBJzDhLDN == bYcWdrfjlS){GxRuPrbMEF = true;}
      if(SOCEJVoIuL == wAGFPaZNOO){wSmyMHkZwF = true;}
      while(JwbBmJiaZg == MnRHZLfDUP){PnjcHsGUum = true;}
      while(bYcWdrfjlS == bYcWdrfjlS){SLfibELPkT = true;}
      while(wAGFPaZNOO == wAGFPaZNOO){KSzCTpemEL = true;}
      if(nmQJQcDpkM == true){nmQJQcDpkM = false;}
      if(qVyNBZehTQ == true){qVyNBZehTQ = false;}
      if(HAwceIpVkM == true){HAwceIpVkM = false;}
      if(jVLKrnHSGA == true){jVLKrnHSGA = false;}
      if(npyYaaCrEo == true){npyYaaCrEo = false;}
      if(wqtyGmqneH == true){wqtyGmqneH = false;}
      if(mgEYcVJmUM == true){mgEYcVJmUM = false;}
      if(SLbSbQCWBE == true){SLbSbQCWBE = false;}
      if(GxRuPrbMEF == true){GxRuPrbMEF = false;}
      if(wSmyMHkZwF == true){wSmyMHkZwF = false;}
      if(QPWqWjPaWo == true){QPWqWjPaWo = false;}
      if(kTlaBpOJIj == true){kTlaBpOJIj = false;}
      if(txiPPzYcFT == true){txiPPzYcFT = false;}
      if(fcawmqZaYf == true){fcawmqZaYf = false;}
      if(cApOTcgMxW == true){cApOTcgMxW = false;}
      if(rbQLLTfHaW == true){rbQLLTfHaW = false;}
      if(LlUCJIromK == true){LlUCJIromK = false;}
      if(PnjcHsGUum == true){PnjcHsGUum = false;}
      if(SLfibELPkT == true){SLfibELPkT = false;}
      if(KSzCTpemEL == true){KSzCTpemEL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ADPKRJVUAW
{ 
  void BHZgeyMfMo()
  { 
      bool KeiphstBBJ = false;
      bool qdlfwIrZwy = false;
      bool LMIaGNqlCm = false;
      bool sQukpPfqqO = false;
      bool QGGxaCbKDA = false;
      bool KdJFgyVHjT = false;
      bool BHzNQahBog = false;
      bool bAiggFGKAE = false;
      bool lghCcPHpDr = false;
      bool tXHWNJGrgA = false;
      bool TZVWXJtbYb = false;
      bool rLHfgUZwkA = false;
      bool TrxxlEsLTX = false;
      bool yNczjLKKeS = false;
      bool UeRbziPapr = false;
      bool iJHggbcXkT = false;
      bool QiHAddhIwU = false;
      bool JPRRfnZUxD = false;
      bool nRVbnnFwSH = false;
      bool imZLClWQyU = false;
      string ljPZQQZeya;
      string wuxLIsLNww;
      string WUGNQSegYJ;
      string pMKUTccOZA;
      string cSsuqjRxty;
      string NZcJGRdCJy;
      string lsGnjikbrf;
      string QxmwTEaKWg;
      string AhlawPiBOC;
      string yaFaNiMFLH;
      string ypEOhPlgpB;
      string pTebxEGfrT;
      string AiMogprMhj;
      string rVzOhKcXrf;
      string cCLNMeucdJ;
      string bgNqHPdOgq;
      string XZyFJTTQtm;
      string bhmLpxXzcB;
      string tOhYILIHHS;
      string fNqAICDGDr;
      if(ljPZQQZeya == ypEOhPlgpB){KeiphstBBJ = true;}
      else if(ypEOhPlgpB == ljPZQQZeya){TZVWXJtbYb = true;}
      if(wuxLIsLNww == pTebxEGfrT){qdlfwIrZwy = true;}
      else if(pTebxEGfrT == wuxLIsLNww){rLHfgUZwkA = true;}
      if(WUGNQSegYJ == AiMogprMhj){LMIaGNqlCm = true;}
      else if(AiMogprMhj == WUGNQSegYJ){TrxxlEsLTX = true;}
      if(pMKUTccOZA == rVzOhKcXrf){sQukpPfqqO = true;}
      else if(rVzOhKcXrf == pMKUTccOZA){yNczjLKKeS = true;}
      if(cSsuqjRxty == cCLNMeucdJ){QGGxaCbKDA = true;}
      else if(cCLNMeucdJ == cSsuqjRxty){UeRbziPapr = true;}
      if(NZcJGRdCJy == bgNqHPdOgq){KdJFgyVHjT = true;}
      else if(bgNqHPdOgq == NZcJGRdCJy){iJHggbcXkT = true;}
      if(lsGnjikbrf == XZyFJTTQtm){BHzNQahBog = true;}
      else if(XZyFJTTQtm == lsGnjikbrf){QiHAddhIwU = true;}
      if(QxmwTEaKWg == bhmLpxXzcB){bAiggFGKAE = true;}
      if(AhlawPiBOC == tOhYILIHHS){lghCcPHpDr = true;}
      if(yaFaNiMFLH == fNqAICDGDr){tXHWNJGrgA = true;}
      while(bhmLpxXzcB == QxmwTEaKWg){JPRRfnZUxD = true;}
      while(tOhYILIHHS == tOhYILIHHS){nRVbnnFwSH = true;}
      while(fNqAICDGDr == fNqAICDGDr){imZLClWQyU = true;}
      if(KeiphstBBJ == true){KeiphstBBJ = false;}
      if(qdlfwIrZwy == true){qdlfwIrZwy = false;}
      if(LMIaGNqlCm == true){LMIaGNqlCm = false;}
      if(sQukpPfqqO == true){sQukpPfqqO = false;}
      if(QGGxaCbKDA == true){QGGxaCbKDA = false;}
      if(KdJFgyVHjT == true){KdJFgyVHjT = false;}
      if(BHzNQahBog == true){BHzNQahBog = false;}
      if(bAiggFGKAE == true){bAiggFGKAE = false;}
      if(lghCcPHpDr == true){lghCcPHpDr = false;}
      if(tXHWNJGrgA == true){tXHWNJGrgA = false;}
      if(TZVWXJtbYb == true){TZVWXJtbYb = false;}
      if(rLHfgUZwkA == true){rLHfgUZwkA = false;}
      if(TrxxlEsLTX == true){TrxxlEsLTX = false;}
      if(yNczjLKKeS == true){yNczjLKKeS = false;}
      if(UeRbziPapr == true){UeRbziPapr = false;}
      if(iJHggbcXkT == true){iJHggbcXkT = false;}
      if(QiHAddhIwU == true){QiHAddhIwU = false;}
      if(JPRRfnZUxD == true){JPRRfnZUxD = false;}
      if(nRVbnnFwSH == true){nRVbnnFwSH = false;}
      if(imZLClWQyU == true){imZLClWQyU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MULJOOCUJG
{ 
  void tOModKpiHE()
  { 
      bool tCwOnpSWAy = false;
      bool HCXmUKXkzI = false;
      bool EsTtcaKBcP = false;
      bool nHPYmuMJgL = false;
      bool DxJJnZNSBk = false;
      bool TuwdVAhBlM = false;
      bool eQtkKzmyAY = false;
      bool yOEnFHiJGD = false;
      bool NqArwrKkDl = false;
      bool MLWTflCYzn = false;
      bool lOSbmEqIYN = false;
      bool RYtizmQBnR = false;
      bool nCuNMmqjIS = false;
      bool EKKSQyYYFq = false;
      bool BCMoUnQnUr = false;
      bool UBkhzjTFOA = false;
      bool NGzFIGObRA = false;
      bool OrwwPloFrY = false;
      bool VCPQxDZbSg = false;
      bool dSJFduCHfN = false;
      string wrGVxEzkrq;
      string xunaREoAOi;
      string HEyzzEAdqZ;
      string SchMhPqHAZ;
      string WtDbubzRCI;
      string upPXDrtHVr;
      string EUtRXUMbrB;
      string MgAoLMBWDW;
      string FibidcMJIp;
      string VjlHUBAkDa;
      string OXZAuOoZLq;
      string pXEymUsKnu;
      string HCSBfcusTK;
      string LQSbIgJanO;
      string mlyRAyemUz;
      string IpwITMEXUR;
      string SwFBeYEcpF;
      string LRWYHUEBAg;
      string xIXUBVTKIu;
      string ckGVuqgwla;
      if(wrGVxEzkrq == OXZAuOoZLq){tCwOnpSWAy = true;}
      else if(OXZAuOoZLq == wrGVxEzkrq){lOSbmEqIYN = true;}
      if(xunaREoAOi == pXEymUsKnu){HCXmUKXkzI = true;}
      else if(pXEymUsKnu == xunaREoAOi){RYtizmQBnR = true;}
      if(HEyzzEAdqZ == HCSBfcusTK){EsTtcaKBcP = true;}
      else if(HCSBfcusTK == HEyzzEAdqZ){nCuNMmqjIS = true;}
      if(SchMhPqHAZ == LQSbIgJanO){nHPYmuMJgL = true;}
      else if(LQSbIgJanO == SchMhPqHAZ){EKKSQyYYFq = true;}
      if(WtDbubzRCI == mlyRAyemUz){DxJJnZNSBk = true;}
      else if(mlyRAyemUz == WtDbubzRCI){BCMoUnQnUr = true;}
      if(upPXDrtHVr == IpwITMEXUR){TuwdVAhBlM = true;}
      else if(IpwITMEXUR == upPXDrtHVr){UBkhzjTFOA = true;}
      if(EUtRXUMbrB == SwFBeYEcpF){eQtkKzmyAY = true;}
      else if(SwFBeYEcpF == EUtRXUMbrB){NGzFIGObRA = true;}
      if(MgAoLMBWDW == LRWYHUEBAg){yOEnFHiJGD = true;}
      if(FibidcMJIp == xIXUBVTKIu){NqArwrKkDl = true;}
      if(VjlHUBAkDa == ckGVuqgwla){MLWTflCYzn = true;}
      while(LRWYHUEBAg == MgAoLMBWDW){OrwwPloFrY = true;}
      while(xIXUBVTKIu == xIXUBVTKIu){VCPQxDZbSg = true;}
      while(ckGVuqgwla == ckGVuqgwla){dSJFduCHfN = true;}
      if(tCwOnpSWAy == true){tCwOnpSWAy = false;}
      if(HCXmUKXkzI == true){HCXmUKXkzI = false;}
      if(EsTtcaKBcP == true){EsTtcaKBcP = false;}
      if(nHPYmuMJgL == true){nHPYmuMJgL = false;}
      if(DxJJnZNSBk == true){DxJJnZNSBk = false;}
      if(TuwdVAhBlM == true){TuwdVAhBlM = false;}
      if(eQtkKzmyAY == true){eQtkKzmyAY = false;}
      if(yOEnFHiJGD == true){yOEnFHiJGD = false;}
      if(NqArwrKkDl == true){NqArwrKkDl = false;}
      if(MLWTflCYzn == true){MLWTflCYzn = false;}
      if(lOSbmEqIYN == true){lOSbmEqIYN = false;}
      if(RYtizmQBnR == true){RYtizmQBnR = false;}
      if(nCuNMmqjIS == true){nCuNMmqjIS = false;}
      if(EKKSQyYYFq == true){EKKSQyYYFq = false;}
      if(BCMoUnQnUr == true){BCMoUnQnUr = false;}
      if(UBkhzjTFOA == true){UBkhzjTFOA = false;}
      if(NGzFIGObRA == true){NGzFIGObRA = false;}
      if(OrwwPloFrY == true){OrwwPloFrY = false;}
      if(VCPQxDZbSg == true){VCPQxDZbSg = false;}
      if(dSJFduCHfN == true){dSJFduCHfN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SZKMLEUNEE
{ 
  void udWduRqPXF()
  { 
      bool oBhpcZliQn = false;
      bool OJjoNxKRFi = false;
      bool MfIaLfyCEz = false;
      bool oJlkdJTuQK = false;
      bool VTVehylpEI = false;
      bool blUoCIrHdw = false;
      bool bjeRyFWyKE = false;
      bool dOAuMsJdrM = false;
      bool tHxuWDnwhU = false;
      bool RMQUhknEgc = false;
      bool bmfAdMkZbJ = false;
      bool zOOQBTmitu = false;
      bool QaQolQxfMa = false;
      bool EEwPkHbxQJ = false;
      bool RNUYUCyASO = false;
      bool yFKlMBVpNN = false;
      bool PENAEuRzes = false;
      bool rpRjcDGrTj = false;
      bool SxNycysKDj = false;
      bool kkiDtNATTZ = false;
      string NuJIpxihtJ;
      string HYVfbVebjN;
      string WxapqVPwPM;
      string QydTHkZsZW;
      string GlqOztypZJ;
      string uryjsQUTRT;
      string hlShrJtCXq;
      string ukBNHjFLpw;
      string XYVFQYAsZq;
      string QGbGnTTJVp;
      string AuRiNKpjcI;
      string LIcUwJQMQT;
      string IAbgaoJuYm;
      string QuoAwbGmrG;
      string hPQQfHdGJe;
      string DHsCgzTkHY;
      string AuLorPSbYT;
      string CcUJlsjKBS;
      string KCksjICmSx;
      string HVeSFlDaYP;
      if(NuJIpxihtJ == AuRiNKpjcI){oBhpcZliQn = true;}
      else if(AuRiNKpjcI == NuJIpxihtJ){bmfAdMkZbJ = true;}
      if(HYVfbVebjN == LIcUwJQMQT){OJjoNxKRFi = true;}
      else if(LIcUwJQMQT == HYVfbVebjN){zOOQBTmitu = true;}
      if(WxapqVPwPM == IAbgaoJuYm){MfIaLfyCEz = true;}
      else if(IAbgaoJuYm == WxapqVPwPM){QaQolQxfMa = true;}
      if(QydTHkZsZW == QuoAwbGmrG){oJlkdJTuQK = true;}
      else if(QuoAwbGmrG == QydTHkZsZW){EEwPkHbxQJ = true;}
      if(GlqOztypZJ == hPQQfHdGJe){VTVehylpEI = true;}
      else if(hPQQfHdGJe == GlqOztypZJ){RNUYUCyASO = true;}
      if(uryjsQUTRT == DHsCgzTkHY){blUoCIrHdw = true;}
      else if(DHsCgzTkHY == uryjsQUTRT){yFKlMBVpNN = true;}
      if(hlShrJtCXq == AuLorPSbYT){bjeRyFWyKE = true;}
      else if(AuLorPSbYT == hlShrJtCXq){PENAEuRzes = true;}
      if(ukBNHjFLpw == CcUJlsjKBS){dOAuMsJdrM = true;}
      if(XYVFQYAsZq == KCksjICmSx){tHxuWDnwhU = true;}
      if(QGbGnTTJVp == HVeSFlDaYP){RMQUhknEgc = true;}
      while(CcUJlsjKBS == ukBNHjFLpw){rpRjcDGrTj = true;}
      while(KCksjICmSx == KCksjICmSx){SxNycysKDj = true;}
      while(HVeSFlDaYP == HVeSFlDaYP){kkiDtNATTZ = true;}
      if(oBhpcZliQn == true){oBhpcZliQn = false;}
      if(OJjoNxKRFi == true){OJjoNxKRFi = false;}
      if(MfIaLfyCEz == true){MfIaLfyCEz = false;}
      if(oJlkdJTuQK == true){oJlkdJTuQK = false;}
      if(VTVehylpEI == true){VTVehylpEI = false;}
      if(blUoCIrHdw == true){blUoCIrHdw = false;}
      if(bjeRyFWyKE == true){bjeRyFWyKE = false;}
      if(dOAuMsJdrM == true){dOAuMsJdrM = false;}
      if(tHxuWDnwhU == true){tHxuWDnwhU = false;}
      if(RMQUhknEgc == true){RMQUhknEgc = false;}
      if(bmfAdMkZbJ == true){bmfAdMkZbJ = false;}
      if(zOOQBTmitu == true){zOOQBTmitu = false;}
      if(QaQolQxfMa == true){QaQolQxfMa = false;}
      if(EEwPkHbxQJ == true){EEwPkHbxQJ = false;}
      if(RNUYUCyASO == true){RNUYUCyASO = false;}
      if(yFKlMBVpNN == true){yFKlMBVpNN = false;}
      if(PENAEuRzes == true){PENAEuRzes = false;}
      if(rpRjcDGrTj == true){rpRjcDGrTj = false;}
      if(SxNycysKDj == true){SxNycysKDj = false;}
      if(kkiDtNATTZ == true){kkiDtNATTZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WOPZREXXWE
{ 
  void VcSVzVTryM()
  { 
      bool bzdduCulni = false;
      bool IFRPeUDEOO = false;
      bool XDdESUUsXY = false;
      bool ghBRlnnfqh = false;
      bool zwARgtsjCC = false;
      bool PHgIkXVZKa = false;
      bool hBOOBZDzdq = false;
      bool gXMfPaDLXY = false;
      bool ajpUJZBsfN = false;
      bool SOUQAyhkQG = false;
      bool psFLVrtArJ = false;
      bool TJBlzxKsEa = false;
      bool YKTPYRCufQ = false;
      bool sRtRhgdezR = false;
      bool eAAVtINiQC = false;
      bool nnfpgfZolE = false;
      bool oyUbQCPjDS = false;
      bool TetluYJxVQ = false;
      bool ESeccEkEjC = false;
      bool HnrucfeYFr = false;
      string froiYTFnJl;
      string mORzoBnACm;
      string fzCdZOyRZI;
      string PimCUYxCCe;
      string JNqbbmAMbn;
      string QQbksgoKIK;
      string UnNAWDbPdQ;
      string EkyWdRIaBm;
      string OlokryHCIn;
      string iltrJVAqEY;
      string LkhLjfSEHb;
      string XOIVwiycIX;
      string wYGphRqFNH;
      string RRVcbdDdAM;
      string fCugPUdXwa;
      string WWhgbldrcS;
      string nMqzJGsetS;
      string fUbwrsdYaN;
      string mSJlktioBo;
      string zKAhXSLuXI;
      if(froiYTFnJl == LkhLjfSEHb){bzdduCulni = true;}
      else if(LkhLjfSEHb == froiYTFnJl){psFLVrtArJ = true;}
      if(mORzoBnACm == XOIVwiycIX){IFRPeUDEOO = true;}
      else if(XOIVwiycIX == mORzoBnACm){TJBlzxKsEa = true;}
      if(fzCdZOyRZI == wYGphRqFNH){XDdESUUsXY = true;}
      else if(wYGphRqFNH == fzCdZOyRZI){YKTPYRCufQ = true;}
      if(PimCUYxCCe == RRVcbdDdAM){ghBRlnnfqh = true;}
      else if(RRVcbdDdAM == PimCUYxCCe){sRtRhgdezR = true;}
      if(JNqbbmAMbn == fCugPUdXwa){zwARgtsjCC = true;}
      else if(fCugPUdXwa == JNqbbmAMbn){eAAVtINiQC = true;}
      if(QQbksgoKIK == WWhgbldrcS){PHgIkXVZKa = true;}
      else if(WWhgbldrcS == QQbksgoKIK){nnfpgfZolE = true;}
      if(UnNAWDbPdQ == nMqzJGsetS){hBOOBZDzdq = true;}
      else if(nMqzJGsetS == UnNAWDbPdQ){oyUbQCPjDS = true;}
      if(EkyWdRIaBm == fUbwrsdYaN){gXMfPaDLXY = true;}
      if(OlokryHCIn == mSJlktioBo){ajpUJZBsfN = true;}
      if(iltrJVAqEY == zKAhXSLuXI){SOUQAyhkQG = true;}
      while(fUbwrsdYaN == EkyWdRIaBm){TetluYJxVQ = true;}
      while(mSJlktioBo == mSJlktioBo){ESeccEkEjC = true;}
      while(zKAhXSLuXI == zKAhXSLuXI){HnrucfeYFr = true;}
      if(bzdduCulni == true){bzdduCulni = false;}
      if(IFRPeUDEOO == true){IFRPeUDEOO = false;}
      if(XDdESUUsXY == true){XDdESUUsXY = false;}
      if(ghBRlnnfqh == true){ghBRlnnfqh = false;}
      if(zwARgtsjCC == true){zwARgtsjCC = false;}
      if(PHgIkXVZKa == true){PHgIkXVZKa = false;}
      if(hBOOBZDzdq == true){hBOOBZDzdq = false;}
      if(gXMfPaDLXY == true){gXMfPaDLXY = false;}
      if(ajpUJZBsfN == true){ajpUJZBsfN = false;}
      if(SOUQAyhkQG == true){SOUQAyhkQG = false;}
      if(psFLVrtArJ == true){psFLVrtArJ = false;}
      if(TJBlzxKsEa == true){TJBlzxKsEa = false;}
      if(YKTPYRCufQ == true){YKTPYRCufQ = false;}
      if(sRtRhgdezR == true){sRtRhgdezR = false;}
      if(eAAVtINiQC == true){eAAVtINiQC = false;}
      if(nnfpgfZolE == true){nnfpgfZolE = false;}
      if(oyUbQCPjDS == true){oyUbQCPjDS = false;}
      if(TetluYJxVQ == true){TetluYJxVQ = false;}
      if(ESeccEkEjC == true){ESeccEkEjC = false;}
      if(HnrucfeYFr == true){HnrucfeYFr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUZIHVPRNZ
{ 
  void lGCNFLmPQY()
  { 
      bool XfHzoiKNEf = false;
      bool ARDnqiVKKW = false;
      bool xyxghFLkEd = false;
      bool AHCjCiACdM = false;
      bool RroFSpKmeu = false;
      bool jroToYiaRj = false;
      bool WYJZfrOSkI = false;
      bool iSgyEFJqOq = false;
      bool tYGItHRiud = false;
      bool zYksosiPZZ = false;
      bool bqCWLQLqOj = false;
      bool PqMZpySAeX = false;
      bool aeXHIJhmIL = false;
      bool WtRnPCVixd = false;
      bool waUKOIMKDq = false;
      bool ZijBzwSuNC = false;
      bool iXhCMUYXKm = false;
      bool biCBazKMrz = false;
      bool wWjRlnJQoS = false;
      bool iaUuuYsSys = false;
      string wKZnFXDiQH;
      string RJGOnBDMGj;
      string zmxiPgggmh;
      string zrQiEFHGWK;
      string UzjKtQSAmb;
      string EGDlwINqYX;
      string pWuiHZsXKh;
      string sxpwOzDlny;
      string OftKdsndmu;
      string rQhyTyDBDT;
      string XupEhHPGWw;
      string FbCZJJbkFN;
      string kPjOpcPqcQ;
      string wBiTaSpobV;
      string dgGqpPNHoJ;
      string VSwoiIKbNF;
      string qXdGADrhzp;
      string TmIijDIsXZ;
      string OICSucFtkS;
      string IOaWeFDApm;
      if(wKZnFXDiQH == XupEhHPGWw){XfHzoiKNEf = true;}
      else if(XupEhHPGWw == wKZnFXDiQH){bqCWLQLqOj = true;}
      if(RJGOnBDMGj == FbCZJJbkFN){ARDnqiVKKW = true;}
      else if(FbCZJJbkFN == RJGOnBDMGj){PqMZpySAeX = true;}
      if(zmxiPgggmh == kPjOpcPqcQ){xyxghFLkEd = true;}
      else if(kPjOpcPqcQ == zmxiPgggmh){aeXHIJhmIL = true;}
      if(zrQiEFHGWK == wBiTaSpobV){AHCjCiACdM = true;}
      else if(wBiTaSpobV == zrQiEFHGWK){WtRnPCVixd = true;}
      if(UzjKtQSAmb == dgGqpPNHoJ){RroFSpKmeu = true;}
      else if(dgGqpPNHoJ == UzjKtQSAmb){waUKOIMKDq = true;}
      if(EGDlwINqYX == VSwoiIKbNF){jroToYiaRj = true;}
      else if(VSwoiIKbNF == EGDlwINqYX){ZijBzwSuNC = true;}
      if(pWuiHZsXKh == qXdGADrhzp){WYJZfrOSkI = true;}
      else if(qXdGADrhzp == pWuiHZsXKh){iXhCMUYXKm = true;}
      if(sxpwOzDlny == TmIijDIsXZ){iSgyEFJqOq = true;}
      if(OftKdsndmu == OICSucFtkS){tYGItHRiud = true;}
      if(rQhyTyDBDT == IOaWeFDApm){zYksosiPZZ = true;}
      while(TmIijDIsXZ == sxpwOzDlny){biCBazKMrz = true;}
      while(OICSucFtkS == OICSucFtkS){wWjRlnJQoS = true;}
      while(IOaWeFDApm == IOaWeFDApm){iaUuuYsSys = true;}
      if(XfHzoiKNEf == true){XfHzoiKNEf = false;}
      if(ARDnqiVKKW == true){ARDnqiVKKW = false;}
      if(xyxghFLkEd == true){xyxghFLkEd = false;}
      if(AHCjCiACdM == true){AHCjCiACdM = false;}
      if(RroFSpKmeu == true){RroFSpKmeu = false;}
      if(jroToYiaRj == true){jroToYiaRj = false;}
      if(WYJZfrOSkI == true){WYJZfrOSkI = false;}
      if(iSgyEFJqOq == true){iSgyEFJqOq = false;}
      if(tYGItHRiud == true){tYGItHRiud = false;}
      if(zYksosiPZZ == true){zYksosiPZZ = false;}
      if(bqCWLQLqOj == true){bqCWLQLqOj = false;}
      if(PqMZpySAeX == true){PqMZpySAeX = false;}
      if(aeXHIJhmIL == true){aeXHIJhmIL = false;}
      if(WtRnPCVixd == true){WtRnPCVixd = false;}
      if(waUKOIMKDq == true){waUKOIMKDq = false;}
      if(ZijBzwSuNC == true){ZijBzwSuNC = false;}
      if(iXhCMUYXKm == true){iXhCMUYXKm = false;}
      if(biCBazKMrz == true){biCBazKMrz = false;}
      if(wWjRlnJQoS == true){wWjRlnJQoS = false;}
      if(iaUuuYsSys == true){iaUuuYsSys = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RPPJEDTWOL
{ 
  void XUoulsYtna()
  { 
      bool nLmYuLfrXw = false;
      bool yslhKxTFhb = false;
      bool jdgFdaQOGa = false;
      bool MDwRKJIJHu = false;
      bool tjREkgUFIl = false;
      bool fPsKyKdhuT = false;
      bool uRkwiuwUWA = false;
      bool nKxmgALcTw = false;
      bool GLGTuxJlTA = false;
      bool eaOmzcyUVp = false;
      bool jzhHyUSFcx = false;
      bool yBNyNjKQAl = false;
      bool kKAWUMwJmD = false;
      bool CpGdMGcyVZ = false;
      bool dDIWBdNPZP = false;
      bool ShUjEYzLlk = false;
      bool YISYuItikG = false;
      bool GLtaHhBdVq = false;
      bool zfiXkTVWZm = false;
      bool HRMkAVkjas = false;
      string jRccOcxYpY;
      string WfJbIHZmql;
      string usrtmGZPCV;
      string bqFELnnVqH;
      string XOaZWAEyHL;
      string XKYaXqZipI;
      string DhVTweZEPU;
      string SEujNgSRWm;
      string CbHqxRSdgT;
      string OFeiEprGdq;
      string ZAhmsSOnMq;
      string YHMCGaZeVd;
      string MwXuGNYLfX;
      string nLneNCsUxe;
      string DdQouHrccc;
      string QNjzedblge;
      string tCIoCMSgoE;
      string hEgqaieiAy;
      string UwiCGaboAj;
      string ZGnSjAVblh;
      if(jRccOcxYpY == ZAhmsSOnMq){nLmYuLfrXw = true;}
      else if(ZAhmsSOnMq == jRccOcxYpY){jzhHyUSFcx = true;}
      if(WfJbIHZmql == YHMCGaZeVd){yslhKxTFhb = true;}
      else if(YHMCGaZeVd == WfJbIHZmql){yBNyNjKQAl = true;}
      if(usrtmGZPCV == MwXuGNYLfX){jdgFdaQOGa = true;}
      else if(MwXuGNYLfX == usrtmGZPCV){kKAWUMwJmD = true;}
      if(bqFELnnVqH == nLneNCsUxe){MDwRKJIJHu = true;}
      else if(nLneNCsUxe == bqFELnnVqH){CpGdMGcyVZ = true;}
      if(XOaZWAEyHL == DdQouHrccc){tjREkgUFIl = true;}
      else if(DdQouHrccc == XOaZWAEyHL){dDIWBdNPZP = true;}
      if(XKYaXqZipI == QNjzedblge){fPsKyKdhuT = true;}
      else if(QNjzedblge == XKYaXqZipI){ShUjEYzLlk = true;}
      if(DhVTweZEPU == tCIoCMSgoE){uRkwiuwUWA = true;}
      else if(tCIoCMSgoE == DhVTweZEPU){YISYuItikG = true;}
      if(SEujNgSRWm == hEgqaieiAy){nKxmgALcTw = true;}
      if(CbHqxRSdgT == UwiCGaboAj){GLGTuxJlTA = true;}
      if(OFeiEprGdq == ZGnSjAVblh){eaOmzcyUVp = true;}
      while(hEgqaieiAy == SEujNgSRWm){GLtaHhBdVq = true;}
      while(UwiCGaboAj == UwiCGaboAj){zfiXkTVWZm = true;}
      while(ZGnSjAVblh == ZGnSjAVblh){HRMkAVkjas = true;}
      if(nLmYuLfrXw == true){nLmYuLfrXw = false;}
      if(yslhKxTFhb == true){yslhKxTFhb = false;}
      if(jdgFdaQOGa == true){jdgFdaQOGa = false;}
      if(MDwRKJIJHu == true){MDwRKJIJHu = false;}
      if(tjREkgUFIl == true){tjREkgUFIl = false;}
      if(fPsKyKdhuT == true){fPsKyKdhuT = false;}
      if(uRkwiuwUWA == true){uRkwiuwUWA = false;}
      if(nKxmgALcTw == true){nKxmgALcTw = false;}
      if(GLGTuxJlTA == true){GLGTuxJlTA = false;}
      if(eaOmzcyUVp == true){eaOmzcyUVp = false;}
      if(jzhHyUSFcx == true){jzhHyUSFcx = false;}
      if(yBNyNjKQAl == true){yBNyNjKQAl = false;}
      if(kKAWUMwJmD == true){kKAWUMwJmD = false;}
      if(CpGdMGcyVZ == true){CpGdMGcyVZ = false;}
      if(dDIWBdNPZP == true){dDIWBdNPZP = false;}
      if(ShUjEYzLlk == true){ShUjEYzLlk = false;}
      if(YISYuItikG == true){YISYuItikG = false;}
      if(GLtaHhBdVq == true){GLtaHhBdVq = false;}
      if(zfiXkTVWZm == true){zfiXkTVWZm = false;}
      if(HRMkAVkjas == true){HRMkAVkjas = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WNWUKJZSEP
{ 
  void aWqMaNXSZX()
  { 
      bool wDGlOzTMbB = false;
      bool sDgHKNsLOj = false;
      bool FUbAydPUqL = false;
      bool OaonwsERTb = false;
      bool RJWXHSMogV = false;
      bool MWKiraaFmk = false;
      bool iyUQmSNsKR = false;
      bool JbrmRuyErf = false;
      bool QZmVyrQFuU = false;
      bool RydhrSnGko = false;
      bool ETePMkdXRx = false;
      bool cVMGUJLzRt = false;
      bool BIxpzLxJtz = false;
      bool GrTDbwuXJN = false;
      bool NsnyrwkWNi = false;
      bool HoopnuWnQA = false;
      bool nTcRpkCJeX = false;
      bool NnpDgIUzxD = false;
      bool ZZwKrRCcPf = false;
      bool ZGGIZsPVHH = false;
      string FYGjSTTODI;
      string VmCyrYpSrs;
      string cnBmcZqEsT;
      string fCdcbDuOBz;
      string kPGrrUiAyk;
      string TXIkARXSGs;
      string bPUjcTJZVn;
      string caRsIMgJuH;
      string qqFHAIsrbK;
      string ebHIXUtWPX;
      string LJdJHrFPcm;
      string kOXyCkJNiU;
      string ZQxLJATJUm;
      string SJtWwhMwzI;
      string CcPnYQEIGl;
      string LgmtytLSzH;
      string YwtpUaUBCU;
      string XMNaRxAIlr;
      string wKDhakVzYB;
      string VtxrjGhZTy;
      if(FYGjSTTODI == LJdJHrFPcm){wDGlOzTMbB = true;}
      else if(LJdJHrFPcm == FYGjSTTODI){ETePMkdXRx = true;}
      if(VmCyrYpSrs == kOXyCkJNiU){sDgHKNsLOj = true;}
      else if(kOXyCkJNiU == VmCyrYpSrs){cVMGUJLzRt = true;}
      if(cnBmcZqEsT == ZQxLJATJUm){FUbAydPUqL = true;}
      else if(ZQxLJATJUm == cnBmcZqEsT){BIxpzLxJtz = true;}
      if(fCdcbDuOBz == SJtWwhMwzI){OaonwsERTb = true;}
      else if(SJtWwhMwzI == fCdcbDuOBz){GrTDbwuXJN = true;}
      if(kPGrrUiAyk == CcPnYQEIGl){RJWXHSMogV = true;}
      else if(CcPnYQEIGl == kPGrrUiAyk){NsnyrwkWNi = true;}
      if(TXIkARXSGs == LgmtytLSzH){MWKiraaFmk = true;}
      else if(LgmtytLSzH == TXIkARXSGs){HoopnuWnQA = true;}
      if(bPUjcTJZVn == YwtpUaUBCU){iyUQmSNsKR = true;}
      else if(YwtpUaUBCU == bPUjcTJZVn){nTcRpkCJeX = true;}
      if(caRsIMgJuH == XMNaRxAIlr){JbrmRuyErf = true;}
      if(qqFHAIsrbK == wKDhakVzYB){QZmVyrQFuU = true;}
      if(ebHIXUtWPX == VtxrjGhZTy){RydhrSnGko = true;}
      while(XMNaRxAIlr == caRsIMgJuH){NnpDgIUzxD = true;}
      while(wKDhakVzYB == wKDhakVzYB){ZZwKrRCcPf = true;}
      while(VtxrjGhZTy == VtxrjGhZTy){ZGGIZsPVHH = true;}
      if(wDGlOzTMbB == true){wDGlOzTMbB = false;}
      if(sDgHKNsLOj == true){sDgHKNsLOj = false;}
      if(FUbAydPUqL == true){FUbAydPUqL = false;}
      if(OaonwsERTb == true){OaonwsERTb = false;}
      if(RJWXHSMogV == true){RJWXHSMogV = false;}
      if(MWKiraaFmk == true){MWKiraaFmk = false;}
      if(iyUQmSNsKR == true){iyUQmSNsKR = false;}
      if(JbrmRuyErf == true){JbrmRuyErf = false;}
      if(QZmVyrQFuU == true){QZmVyrQFuU = false;}
      if(RydhrSnGko == true){RydhrSnGko = false;}
      if(ETePMkdXRx == true){ETePMkdXRx = false;}
      if(cVMGUJLzRt == true){cVMGUJLzRt = false;}
      if(BIxpzLxJtz == true){BIxpzLxJtz = false;}
      if(GrTDbwuXJN == true){GrTDbwuXJN = false;}
      if(NsnyrwkWNi == true){NsnyrwkWNi = false;}
      if(HoopnuWnQA == true){HoopnuWnQA = false;}
      if(nTcRpkCJeX == true){nTcRpkCJeX = false;}
      if(NnpDgIUzxD == true){NnpDgIUzxD = false;}
      if(ZZwKrRCcPf == true){ZZwKrRCcPf = false;}
      if(ZGGIZsPVHH == true){ZGGIZsPVHH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FDARWIOGJI
{ 
  void GnucXdaUyV()
  { 
      bool whqBwVrUbR = false;
      bool STeOLFbDxe = false;
      bool sNGpVqVqPl = false;
      bool sRfgufKHRN = false;
      bool wYmItEjZif = false;
      bool VwoBribAeE = false;
      bool AAEpYBnxTe = false;
      bool tUljhTZxwR = false;
      bool GuIjPwbdoL = false;
      bool EKbMNuTwjs = false;
      bool QmGDkAKFTX = false;
      bool IdDNyErUZb = false;
      bool YJHHajrYWl = false;
      bool AdNDASoEyP = false;
      bool lWKRDZGOOI = false;
      bool DzWHTGezcB = false;
      bool IkigXdPAMe = false;
      bool OmWKoBzpDA = false;
      bool cdKNhBHGit = false;
      bool npawHBnctZ = false;
      string XoGpkeuZUF;
      string bKXgfOhtaF;
      string ZmdiVmKbqe;
      string NSRaMmDDso;
      string EUGWdooIMQ;
      string ioTzpjKWUx;
      string UTipqJrxTr;
      string KeAkBEgHFg;
      string xBOawYzSkb;
      string bghuUklQfU;
      string wroUFDohyk;
      string DDRnzSEHtS;
      string JYLqPdwEPQ;
      string SQbkjFMtVr;
      string iRUzYYPtuC;
      string fdWMKWfxFa;
      string GkRhSmbgDt;
      string GKlBjrEMSq;
      string OBINjntOZM;
      string YOntkyzmfk;
      if(XoGpkeuZUF == wroUFDohyk){whqBwVrUbR = true;}
      else if(wroUFDohyk == XoGpkeuZUF){QmGDkAKFTX = true;}
      if(bKXgfOhtaF == DDRnzSEHtS){STeOLFbDxe = true;}
      else if(DDRnzSEHtS == bKXgfOhtaF){IdDNyErUZb = true;}
      if(ZmdiVmKbqe == JYLqPdwEPQ){sNGpVqVqPl = true;}
      else if(JYLqPdwEPQ == ZmdiVmKbqe){YJHHajrYWl = true;}
      if(NSRaMmDDso == SQbkjFMtVr){sRfgufKHRN = true;}
      else if(SQbkjFMtVr == NSRaMmDDso){AdNDASoEyP = true;}
      if(EUGWdooIMQ == iRUzYYPtuC){wYmItEjZif = true;}
      else if(iRUzYYPtuC == EUGWdooIMQ){lWKRDZGOOI = true;}
      if(ioTzpjKWUx == fdWMKWfxFa){VwoBribAeE = true;}
      else if(fdWMKWfxFa == ioTzpjKWUx){DzWHTGezcB = true;}
      if(UTipqJrxTr == GkRhSmbgDt){AAEpYBnxTe = true;}
      else if(GkRhSmbgDt == UTipqJrxTr){IkigXdPAMe = true;}
      if(KeAkBEgHFg == GKlBjrEMSq){tUljhTZxwR = true;}
      if(xBOawYzSkb == OBINjntOZM){GuIjPwbdoL = true;}
      if(bghuUklQfU == YOntkyzmfk){EKbMNuTwjs = true;}
      while(GKlBjrEMSq == KeAkBEgHFg){OmWKoBzpDA = true;}
      while(OBINjntOZM == OBINjntOZM){cdKNhBHGit = true;}
      while(YOntkyzmfk == YOntkyzmfk){npawHBnctZ = true;}
      if(whqBwVrUbR == true){whqBwVrUbR = false;}
      if(STeOLFbDxe == true){STeOLFbDxe = false;}
      if(sNGpVqVqPl == true){sNGpVqVqPl = false;}
      if(sRfgufKHRN == true){sRfgufKHRN = false;}
      if(wYmItEjZif == true){wYmItEjZif = false;}
      if(VwoBribAeE == true){VwoBribAeE = false;}
      if(AAEpYBnxTe == true){AAEpYBnxTe = false;}
      if(tUljhTZxwR == true){tUljhTZxwR = false;}
      if(GuIjPwbdoL == true){GuIjPwbdoL = false;}
      if(EKbMNuTwjs == true){EKbMNuTwjs = false;}
      if(QmGDkAKFTX == true){QmGDkAKFTX = false;}
      if(IdDNyErUZb == true){IdDNyErUZb = false;}
      if(YJHHajrYWl == true){YJHHajrYWl = false;}
      if(AdNDASoEyP == true){AdNDASoEyP = false;}
      if(lWKRDZGOOI == true){lWKRDZGOOI = false;}
      if(DzWHTGezcB == true){DzWHTGezcB = false;}
      if(IkigXdPAMe == true){IkigXdPAMe = false;}
      if(OmWKoBzpDA == true){OmWKoBzpDA = false;}
      if(cdKNhBHGit == true){cdKNhBHGit = false;}
      if(npawHBnctZ == true){npawHBnctZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWFHWUHSXR
{ 
  void qMOalrpHrg()
  { 
      bool ItKZLPmIpQ = false;
      bool dIGCaQuplR = false;
      bool xgiklGtzVh = false;
      bool jRRNEDxBij = false;
      bool LjxONGrPHW = false;
      bool uKLmObKYnE = false;
      bool UmlHfMprxX = false;
      bool StGCGMiUXe = false;
      bool OeqylZFezc = false;
      bool rYNeOXxoiA = false;
      bool QzSiEBDJfB = false;
      bool roBIppwnUF = false;
      bool GLrUetgamh = false;
      bool OtlWOOLHtk = false;
      bool WwyxkCXEoX = false;
      bool bJUctEHxEJ = false;
      bool UbVylyDdsa = false;
      bool dntiiKMtic = false;
      bool WblOFFYIcK = false;
      bool HODjQtZALm = false;
      string zEYNUFNDEX;
      string rHepMIrdkA;
      string WuebUzggaz;
      string xoJbHXAtxY;
      string CptbZpcrtn;
      string RIHLTDYxrU;
      string YgcEaCxChn;
      string IxgLxgBDCd;
      string WommhogyIE;
      string yCBbAVMoBW;
      string sZJFeUawNl;
      string BVtOyjspWl;
      string VztcpFuELb;
      string ULBfkwegHM;
      string NkjWCcImcQ;
      string bVSOBsfgPY;
      string YWklQpTOcC;
      string EMiJYjPWZN;
      string xHbuzzsmeq;
      string PyRinpAxFM;
      if(zEYNUFNDEX == sZJFeUawNl){ItKZLPmIpQ = true;}
      else if(sZJFeUawNl == zEYNUFNDEX){QzSiEBDJfB = true;}
      if(rHepMIrdkA == BVtOyjspWl){dIGCaQuplR = true;}
      else if(BVtOyjspWl == rHepMIrdkA){roBIppwnUF = true;}
      if(WuebUzggaz == VztcpFuELb){xgiklGtzVh = true;}
      else if(VztcpFuELb == WuebUzggaz){GLrUetgamh = true;}
      if(xoJbHXAtxY == ULBfkwegHM){jRRNEDxBij = true;}
      else if(ULBfkwegHM == xoJbHXAtxY){OtlWOOLHtk = true;}
      if(CptbZpcrtn == NkjWCcImcQ){LjxONGrPHW = true;}
      else if(NkjWCcImcQ == CptbZpcrtn){WwyxkCXEoX = true;}
      if(RIHLTDYxrU == bVSOBsfgPY){uKLmObKYnE = true;}
      else if(bVSOBsfgPY == RIHLTDYxrU){bJUctEHxEJ = true;}
      if(YgcEaCxChn == YWklQpTOcC){UmlHfMprxX = true;}
      else if(YWklQpTOcC == YgcEaCxChn){UbVylyDdsa = true;}
      if(IxgLxgBDCd == EMiJYjPWZN){StGCGMiUXe = true;}
      if(WommhogyIE == xHbuzzsmeq){OeqylZFezc = true;}
      if(yCBbAVMoBW == PyRinpAxFM){rYNeOXxoiA = true;}
      while(EMiJYjPWZN == IxgLxgBDCd){dntiiKMtic = true;}
      while(xHbuzzsmeq == xHbuzzsmeq){WblOFFYIcK = true;}
      while(PyRinpAxFM == PyRinpAxFM){HODjQtZALm = true;}
      if(ItKZLPmIpQ == true){ItKZLPmIpQ = false;}
      if(dIGCaQuplR == true){dIGCaQuplR = false;}
      if(xgiklGtzVh == true){xgiklGtzVh = false;}
      if(jRRNEDxBij == true){jRRNEDxBij = false;}
      if(LjxONGrPHW == true){LjxONGrPHW = false;}
      if(uKLmObKYnE == true){uKLmObKYnE = false;}
      if(UmlHfMprxX == true){UmlHfMprxX = false;}
      if(StGCGMiUXe == true){StGCGMiUXe = false;}
      if(OeqylZFezc == true){OeqylZFezc = false;}
      if(rYNeOXxoiA == true){rYNeOXxoiA = false;}
      if(QzSiEBDJfB == true){QzSiEBDJfB = false;}
      if(roBIppwnUF == true){roBIppwnUF = false;}
      if(GLrUetgamh == true){GLrUetgamh = false;}
      if(OtlWOOLHtk == true){OtlWOOLHtk = false;}
      if(WwyxkCXEoX == true){WwyxkCXEoX = false;}
      if(bJUctEHxEJ == true){bJUctEHxEJ = false;}
      if(UbVylyDdsa == true){UbVylyDdsa = false;}
      if(dntiiKMtic == true){dntiiKMtic = false;}
      if(WblOFFYIcK == true){WblOFFYIcK = false;}
      if(HODjQtZALm == true){HODjQtZALm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HZKOWTJUSF
{ 
  void ZqYjUkzhXp()
  { 
      bool SyLhkGeqrO = false;
      bool WbLWxtPbZV = false;
      bool nQDDIpmtgH = false;
      bool aOlQdbziSC = false;
      bool dDSTxOScKl = false;
      bool gbHSgCtIYt = false;
      bool SkJjnHotsV = false;
      bool ugIXqkxjFt = false;
      bool WKjuZzHTjb = false;
      bool gpJYissifp = false;
      bool YXjopASjaw = false;
      bool FKDeWIAOJn = false;
      bool AVKQnEWjny = false;
      bool rODPVzZtEZ = false;
      bool gWrnWWmeBa = false;
      bool rdYroDNSBl = false;
      bool chucEpHmIX = false;
      bool hGKjHccWtQ = false;
      bool RriNFNoLaS = false;
      bool kGsSwybPjf = false;
      string ktduLKJTVN;
      string UIGHdPYosC;
      string exTdNZpSRh;
      string ShtWbGBeNb;
      string uUrctshVjz;
      string uHIsfnazgl;
      string UqCmumNjeX;
      string NsaRHJEpjT;
      string rUhSmKYBpn;
      string eBxbGESEhH;
      string fxpMkBfpkW;
      string ijPMtAJjzj;
      string NLtqrMuzKD;
      string qAIcntdUgl;
      string eiPSEtkjhG;
      string thFxsTDyUY;
      string FgeheibmYz;
      string VnCNFdwalx;
      string aLQDIJtLiU;
      string qeAIfxDgnV;
      if(ktduLKJTVN == fxpMkBfpkW){SyLhkGeqrO = true;}
      else if(fxpMkBfpkW == ktduLKJTVN){YXjopASjaw = true;}
      if(UIGHdPYosC == ijPMtAJjzj){WbLWxtPbZV = true;}
      else if(ijPMtAJjzj == UIGHdPYosC){FKDeWIAOJn = true;}
      if(exTdNZpSRh == NLtqrMuzKD){nQDDIpmtgH = true;}
      else if(NLtqrMuzKD == exTdNZpSRh){AVKQnEWjny = true;}
      if(ShtWbGBeNb == qAIcntdUgl){aOlQdbziSC = true;}
      else if(qAIcntdUgl == ShtWbGBeNb){rODPVzZtEZ = true;}
      if(uUrctshVjz == eiPSEtkjhG){dDSTxOScKl = true;}
      else if(eiPSEtkjhG == uUrctshVjz){gWrnWWmeBa = true;}
      if(uHIsfnazgl == thFxsTDyUY){gbHSgCtIYt = true;}
      else if(thFxsTDyUY == uHIsfnazgl){rdYroDNSBl = true;}
      if(UqCmumNjeX == FgeheibmYz){SkJjnHotsV = true;}
      else if(FgeheibmYz == UqCmumNjeX){chucEpHmIX = true;}
      if(NsaRHJEpjT == VnCNFdwalx){ugIXqkxjFt = true;}
      if(rUhSmKYBpn == aLQDIJtLiU){WKjuZzHTjb = true;}
      if(eBxbGESEhH == qeAIfxDgnV){gpJYissifp = true;}
      while(VnCNFdwalx == NsaRHJEpjT){hGKjHccWtQ = true;}
      while(aLQDIJtLiU == aLQDIJtLiU){RriNFNoLaS = true;}
      while(qeAIfxDgnV == qeAIfxDgnV){kGsSwybPjf = true;}
      if(SyLhkGeqrO == true){SyLhkGeqrO = false;}
      if(WbLWxtPbZV == true){WbLWxtPbZV = false;}
      if(nQDDIpmtgH == true){nQDDIpmtgH = false;}
      if(aOlQdbziSC == true){aOlQdbziSC = false;}
      if(dDSTxOScKl == true){dDSTxOScKl = false;}
      if(gbHSgCtIYt == true){gbHSgCtIYt = false;}
      if(SkJjnHotsV == true){SkJjnHotsV = false;}
      if(ugIXqkxjFt == true){ugIXqkxjFt = false;}
      if(WKjuZzHTjb == true){WKjuZzHTjb = false;}
      if(gpJYissifp == true){gpJYissifp = false;}
      if(YXjopASjaw == true){YXjopASjaw = false;}
      if(FKDeWIAOJn == true){FKDeWIAOJn = false;}
      if(AVKQnEWjny == true){AVKQnEWjny = false;}
      if(rODPVzZtEZ == true){rODPVzZtEZ = false;}
      if(gWrnWWmeBa == true){gWrnWWmeBa = false;}
      if(rdYroDNSBl == true){rdYroDNSBl = false;}
      if(chucEpHmIX == true){chucEpHmIX = false;}
      if(hGKjHccWtQ == true){hGKjHccWtQ = false;}
      if(RriNFNoLaS == true){RriNFNoLaS = false;}
      if(kGsSwybPjf == true){kGsSwybPjf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGJPGZYJXZ
{ 
  void MTpNPIymtH()
  { 
      bool uJBFSlUaSp = false;
      bool zSFOkkpotw = false;
      bool YgfjebcSYP = false;
      bool ddFFNEnuzu = false;
      bool SYsKmbgXlJ = false;
      bool BodFgOdQZp = false;
      bool ICCCLUMABg = false;
      bool wtozdAmUxD = false;
      bool uFfONoAzXz = false;
      bool aWVIlPVpyR = false;
      bool OgWFMHzebg = false;
      bool aITVuDVnoW = false;
      bool TNbCFZYgMN = false;
      bool dwVeoNhaBG = false;
      bool oVXqXSCzMh = false;
      bool thBbyBEUAm = false;
      bool hSRNDdlogh = false;
      bool Vuligyokdl = false;
      bool WYTdTuutfn = false;
      bool INZOXWDKns = false;
      string IXpTWpoBiw;
      string gKCliUcYgJ;
      string tKgSQhKcJm;
      string rxsixNsjQg;
      string rTfYbWpxsf;
      string ehGeLypWDo;
      string fLrwDjRSoV;
      string asIARadIqs;
      string rMicHKqNXy;
      string WWgbAfaiUq;
      string FWIXElYGNj;
      string TgfJwScOns;
      string sDupyEMgzk;
      string zunznVELXU;
      string kkAmeopWfg;
      string DLtayBaRYA;
      string ZrGbjYsgVZ;
      string OQqTIICILJ;
      string OoBRhmAMAl;
      string tmmXtrdXCF;
      if(IXpTWpoBiw == FWIXElYGNj){uJBFSlUaSp = true;}
      else if(FWIXElYGNj == IXpTWpoBiw){OgWFMHzebg = true;}
      if(gKCliUcYgJ == TgfJwScOns){zSFOkkpotw = true;}
      else if(TgfJwScOns == gKCliUcYgJ){aITVuDVnoW = true;}
      if(tKgSQhKcJm == sDupyEMgzk){YgfjebcSYP = true;}
      else if(sDupyEMgzk == tKgSQhKcJm){TNbCFZYgMN = true;}
      if(rxsixNsjQg == zunznVELXU){ddFFNEnuzu = true;}
      else if(zunznVELXU == rxsixNsjQg){dwVeoNhaBG = true;}
      if(rTfYbWpxsf == kkAmeopWfg){SYsKmbgXlJ = true;}
      else if(kkAmeopWfg == rTfYbWpxsf){oVXqXSCzMh = true;}
      if(ehGeLypWDo == DLtayBaRYA){BodFgOdQZp = true;}
      else if(DLtayBaRYA == ehGeLypWDo){thBbyBEUAm = true;}
      if(fLrwDjRSoV == ZrGbjYsgVZ){ICCCLUMABg = true;}
      else if(ZrGbjYsgVZ == fLrwDjRSoV){hSRNDdlogh = true;}
      if(asIARadIqs == OQqTIICILJ){wtozdAmUxD = true;}
      if(rMicHKqNXy == OoBRhmAMAl){uFfONoAzXz = true;}
      if(WWgbAfaiUq == tmmXtrdXCF){aWVIlPVpyR = true;}
      while(OQqTIICILJ == asIARadIqs){Vuligyokdl = true;}
      while(OoBRhmAMAl == OoBRhmAMAl){WYTdTuutfn = true;}
      while(tmmXtrdXCF == tmmXtrdXCF){INZOXWDKns = true;}
      if(uJBFSlUaSp == true){uJBFSlUaSp = false;}
      if(zSFOkkpotw == true){zSFOkkpotw = false;}
      if(YgfjebcSYP == true){YgfjebcSYP = false;}
      if(ddFFNEnuzu == true){ddFFNEnuzu = false;}
      if(SYsKmbgXlJ == true){SYsKmbgXlJ = false;}
      if(BodFgOdQZp == true){BodFgOdQZp = false;}
      if(ICCCLUMABg == true){ICCCLUMABg = false;}
      if(wtozdAmUxD == true){wtozdAmUxD = false;}
      if(uFfONoAzXz == true){uFfONoAzXz = false;}
      if(aWVIlPVpyR == true){aWVIlPVpyR = false;}
      if(OgWFMHzebg == true){OgWFMHzebg = false;}
      if(aITVuDVnoW == true){aITVuDVnoW = false;}
      if(TNbCFZYgMN == true){TNbCFZYgMN = false;}
      if(dwVeoNhaBG == true){dwVeoNhaBG = false;}
      if(oVXqXSCzMh == true){oVXqXSCzMh = false;}
      if(thBbyBEUAm == true){thBbyBEUAm = false;}
      if(hSRNDdlogh == true){hSRNDdlogh = false;}
      if(Vuligyokdl == true){Vuligyokdl = false;}
      if(WYTdTuutfn == true){WYTdTuutfn = false;}
      if(INZOXWDKns == true){INZOXWDKns = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KPUPJSRAZY
{ 
  void MOJTQmOKNi()
  { 
      bool VrUfkmUHhw = false;
      bool aFPPXdXZOT = false;
      bool poaVbxFufq = false;
      bool wKYZJLJUeq = false;
      bool qCmqChqXHY = false;
      bool JGCfrfRzEn = false;
      bool hZbqzQgoFM = false;
      bool TDuWbmBjSs = false;
      bool FgmGgoHrhc = false;
      bool sKQqIRawql = false;
      bool BBStFGLeEE = false;
      bool ehfKhBlVKK = false;
      bool InHcSJlDNK = false;
      bool MFrgrEOrAa = false;
      bool cbncxLdGJH = false;
      bool eEkgcMsobu = false;
      bool TIRsqZoyRd = false;
      bool msUjgfzefH = false;
      bool eftGfITLDe = false;
      bool KYQFGUKtkX = false;
      string WPwXwGnBuf;
      string MtYyFmOnYp;
      string rjKhRMgZZg;
      string XqpxXYtJNw;
      string VFytutKole;
      string MuXZbmENGj;
      string ZObNHUDaaf;
      string rEZbTlkPmX;
      string BrmtTbTQVj;
      string UgDdWHcjma;
      string piNFmIVuFo;
      string BnZhhhahtf;
      string BmFpLKAwFL;
      string IAcMhRdhHL;
      string GXKfifGVuo;
      string gupHYDdWtb;
      string IYpsgAKNAP;
      string DsZiYcbYHe;
      string EeAQeMKVmd;
      string nGmeChgQzh;
      if(WPwXwGnBuf == piNFmIVuFo){VrUfkmUHhw = true;}
      else if(piNFmIVuFo == WPwXwGnBuf){BBStFGLeEE = true;}
      if(MtYyFmOnYp == BnZhhhahtf){aFPPXdXZOT = true;}
      else if(BnZhhhahtf == MtYyFmOnYp){ehfKhBlVKK = true;}
      if(rjKhRMgZZg == BmFpLKAwFL){poaVbxFufq = true;}
      else if(BmFpLKAwFL == rjKhRMgZZg){InHcSJlDNK = true;}
      if(XqpxXYtJNw == IAcMhRdhHL){wKYZJLJUeq = true;}
      else if(IAcMhRdhHL == XqpxXYtJNw){MFrgrEOrAa = true;}
      if(VFytutKole == GXKfifGVuo){qCmqChqXHY = true;}
      else if(GXKfifGVuo == VFytutKole){cbncxLdGJH = true;}
      if(MuXZbmENGj == gupHYDdWtb){JGCfrfRzEn = true;}
      else if(gupHYDdWtb == MuXZbmENGj){eEkgcMsobu = true;}
      if(ZObNHUDaaf == IYpsgAKNAP){hZbqzQgoFM = true;}
      else if(IYpsgAKNAP == ZObNHUDaaf){TIRsqZoyRd = true;}
      if(rEZbTlkPmX == DsZiYcbYHe){TDuWbmBjSs = true;}
      if(BrmtTbTQVj == EeAQeMKVmd){FgmGgoHrhc = true;}
      if(UgDdWHcjma == nGmeChgQzh){sKQqIRawql = true;}
      while(DsZiYcbYHe == rEZbTlkPmX){msUjgfzefH = true;}
      while(EeAQeMKVmd == EeAQeMKVmd){eftGfITLDe = true;}
      while(nGmeChgQzh == nGmeChgQzh){KYQFGUKtkX = true;}
      if(VrUfkmUHhw == true){VrUfkmUHhw = false;}
      if(aFPPXdXZOT == true){aFPPXdXZOT = false;}
      if(poaVbxFufq == true){poaVbxFufq = false;}
      if(wKYZJLJUeq == true){wKYZJLJUeq = false;}
      if(qCmqChqXHY == true){qCmqChqXHY = false;}
      if(JGCfrfRzEn == true){JGCfrfRzEn = false;}
      if(hZbqzQgoFM == true){hZbqzQgoFM = false;}
      if(TDuWbmBjSs == true){TDuWbmBjSs = false;}
      if(FgmGgoHrhc == true){FgmGgoHrhc = false;}
      if(sKQqIRawql == true){sKQqIRawql = false;}
      if(BBStFGLeEE == true){BBStFGLeEE = false;}
      if(ehfKhBlVKK == true){ehfKhBlVKK = false;}
      if(InHcSJlDNK == true){InHcSJlDNK = false;}
      if(MFrgrEOrAa == true){MFrgrEOrAa = false;}
      if(cbncxLdGJH == true){cbncxLdGJH = false;}
      if(eEkgcMsobu == true){eEkgcMsobu = false;}
      if(TIRsqZoyRd == true){TIRsqZoyRd = false;}
      if(msUjgfzefH == true){msUjgfzefH = false;}
      if(eftGfITLDe == true){eftGfITLDe = false;}
      if(KYQFGUKtkX == true){KYQFGUKtkX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GCYTTWPNEM
{ 
  void JqztnUYurW()
  { 
      bool cYEHIkGfqC = false;
      bool GfbIUqbGWM = false;
      bool DdkTFdXDHD = false;
      bool HFWVYpOimh = false;
      bool lwqQqBoosk = false;
      bool BpdOZznjBd = false;
      bool NDYmtBJGid = false;
      bool brSnaGlTcD = false;
      bool ohKVCQaHwZ = false;
      bool CegJUhXDWp = false;
      bool rhGOJIWpmS = false;
      bool MTGynesCkd = false;
      bool ZBJJbwLJSr = false;
      bool iixmLGbuMs = false;
      bool sjTcMiXiUp = false;
      bool oVRrPqYwmM = false;
      bool xNXujcWTlg = false;
      bool Cxorjpggwr = false;
      bool YbncCMQEWU = false;
      bool hfIzwfMYri = false;
      string pbNjtVADkS;
      string zyUiqWiDDp;
      string uhuzmUELIa;
      string mupjqpWuVK;
      string alziORwaCe;
      string nltgfIfOwY;
      string RnuKeEHkqA;
      string AnhrOIhLjU;
      string YcJdmBAJEi;
      string JHywslqnDK;
      string KLjBdzEBRW;
      string ZUdbAoeRXd;
      string DxfIqsolzb;
      string RtIZKMsIzm;
      string wzqgIocVuE;
      string HYQYGMebKk;
      string KSCpFfMERm;
      string uVRjhEGyzB;
      string PTpuTrciSx;
      string hRyOcdxAbc;
      if(pbNjtVADkS == KLjBdzEBRW){cYEHIkGfqC = true;}
      else if(KLjBdzEBRW == pbNjtVADkS){rhGOJIWpmS = true;}
      if(zyUiqWiDDp == ZUdbAoeRXd){GfbIUqbGWM = true;}
      else if(ZUdbAoeRXd == zyUiqWiDDp){MTGynesCkd = true;}
      if(uhuzmUELIa == DxfIqsolzb){DdkTFdXDHD = true;}
      else if(DxfIqsolzb == uhuzmUELIa){ZBJJbwLJSr = true;}
      if(mupjqpWuVK == RtIZKMsIzm){HFWVYpOimh = true;}
      else if(RtIZKMsIzm == mupjqpWuVK){iixmLGbuMs = true;}
      if(alziORwaCe == wzqgIocVuE){lwqQqBoosk = true;}
      else if(wzqgIocVuE == alziORwaCe){sjTcMiXiUp = true;}
      if(nltgfIfOwY == HYQYGMebKk){BpdOZznjBd = true;}
      else if(HYQYGMebKk == nltgfIfOwY){oVRrPqYwmM = true;}
      if(RnuKeEHkqA == KSCpFfMERm){NDYmtBJGid = true;}
      else if(KSCpFfMERm == RnuKeEHkqA){xNXujcWTlg = true;}
      if(AnhrOIhLjU == uVRjhEGyzB){brSnaGlTcD = true;}
      if(YcJdmBAJEi == PTpuTrciSx){ohKVCQaHwZ = true;}
      if(JHywslqnDK == hRyOcdxAbc){CegJUhXDWp = true;}
      while(uVRjhEGyzB == AnhrOIhLjU){Cxorjpggwr = true;}
      while(PTpuTrciSx == PTpuTrciSx){YbncCMQEWU = true;}
      while(hRyOcdxAbc == hRyOcdxAbc){hfIzwfMYri = true;}
      if(cYEHIkGfqC == true){cYEHIkGfqC = false;}
      if(GfbIUqbGWM == true){GfbIUqbGWM = false;}
      if(DdkTFdXDHD == true){DdkTFdXDHD = false;}
      if(HFWVYpOimh == true){HFWVYpOimh = false;}
      if(lwqQqBoosk == true){lwqQqBoosk = false;}
      if(BpdOZznjBd == true){BpdOZznjBd = false;}
      if(NDYmtBJGid == true){NDYmtBJGid = false;}
      if(brSnaGlTcD == true){brSnaGlTcD = false;}
      if(ohKVCQaHwZ == true){ohKVCQaHwZ = false;}
      if(CegJUhXDWp == true){CegJUhXDWp = false;}
      if(rhGOJIWpmS == true){rhGOJIWpmS = false;}
      if(MTGynesCkd == true){MTGynesCkd = false;}
      if(ZBJJbwLJSr == true){ZBJJbwLJSr = false;}
      if(iixmLGbuMs == true){iixmLGbuMs = false;}
      if(sjTcMiXiUp == true){sjTcMiXiUp = false;}
      if(oVRrPqYwmM == true){oVRrPqYwmM = false;}
      if(xNXujcWTlg == true){xNXujcWTlg = false;}
      if(Cxorjpggwr == true){Cxorjpggwr = false;}
      if(YbncCMQEWU == true){YbncCMQEWU = false;}
      if(hfIzwfMYri == true){hfIzwfMYri = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DLQZQZRYNR
{ 
  void DwNElZtCzy()
  { 
      bool eNWWxGxyug = false;
      bool KSAeFeqGze = false;
      bool OGwyYnoKds = false;
      bool OecnDtMHlo = false;
      bool LUPYYLjnxV = false;
      bool gbZJpXQXxJ = false;
      bool QmUCRepMbL = false;
      bool RiUJTspXYN = false;
      bool EAMIMlFSxe = false;
      bool coJcYYANGs = false;
      bool VXMlDxGPpw = false;
      bool gsyjFPZLoe = false;
      bool ZWOxhcYrkt = false;
      bool scQergnaFO = false;
      bool focBxjpZWI = false;
      bool ynXaTyIODZ = false;
      bool YOeuCEcSrY = false;
      bool bzGazktMAy = false;
      bool mzUbwEFoLs = false;
      bool XZXeoQKgys = false;
      string KnBppiAsGe;
      string rBnYqtcUHp;
      string hHBeXTdiLt;
      string yyBEXZWDSc;
      string XXkEumSaJI;
      string bdbZRDmVRV;
      string FQhMftziAR;
      string XZCdSJWwjk;
      string ADZCRUWblU;
      string mAkwXGpYXA;
      string miZrkCaxGI;
      string gpkgUBqetK;
      string WXxfdWnFGL;
      string TxYiyQchRO;
      string sZUdmwPEaV;
      string PKdMdOlsNN;
      string OVquniRBhE;
      string XJNeRxDSrh;
      string HiejwITLFj;
      string ejTDAXiYoE;
      if(KnBppiAsGe == miZrkCaxGI){eNWWxGxyug = true;}
      else if(miZrkCaxGI == KnBppiAsGe){VXMlDxGPpw = true;}
      if(rBnYqtcUHp == gpkgUBqetK){KSAeFeqGze = true;}
      else if(gpkgUBqetK == rBnYqtcUHp){gsyjFPZLoe = true;}
      if(hHBeXTdiLt == WXxfdWnFGL){OGwyYnoKds = true;}
      else if(WXxfdWnFGL == hHBeXTdiLt){ZWOxhcYrkt = true;}
      if(yyBEXZWDSc == TxYiyQchRO){OecnDtMHlo = true;}
      else if(TxYiyQchRO == yyBEXZWDSc){scQergnaFO = true;}
      if(XXkEumSaJI == sZUdmwPEaV){LUPYYLjnxV = true;}
      else if(sZUdmwPEaV == XXkEumSaJI){focBxjpZWI = true;}
      if(bdbZRDmVRV == PKdMdOlsNN){gbZJpXQXxJ = true;}
      else if(PKdMdOlsNN == bdbZRDmVRV){ynXaTyIODZ = true;}
      if(FQhMftziAR == OVquniRBhE){QmUCRepMbL = true;}
      else if(OVquniRBhE == FQhMftziAR){YOeuCEcSrY = true;}
      if(XZCdSJWwjk == XJNeRxDSrh){RiUJTspXYN = true;}
      if(ADZCRUWblU == HiejwITLFj){EAMIMlFSxe = true;}
      if(mAkwXGpYXA == ejTDAXiYoE){coJcYYANGs = true;}
      while(XJNeRxDSrh == XZCdSJWwjk){bzGazktMAy = true;}
      while(HiejwITLFj == HiejwITLFj){mzUbwEFoLs = true;}
      while(ejTDAXiYoE == ejTDAXiYoE){XZXeoQKgys = true;}
      if(eNWWxGxyug == true){eNWWxGxyug = false;}
      if(KSAeFeqGze == true){KSAeFeqGze = false;}
      if(OGwyYnoKds == true){OGwyYnoKds = false;}
      if(OecnDtMHlo == true){OecnDtMHlo = false;}
      if(LUPYYLjnxV == true){LUPYYLjnxV = false;}
      if(gbZJpXQXxJ == true){gbZJpXQXxJ = false;}
      if(QmUCRepMbL == true){QmUCRepMbL = false;}
      if(RiUJTspXYN == true){RiUJTspXYN = false;}
      if(EAMIMlFSxe == true){EAMIMlFSxe = false;}
      if(coJcYYANGs == true){coJcYYANGs = false;}
      if(VXMlDxGPpw == true){VXMlDxGPpw = false;}
      if(gsyjFPZLoe == true){gsyjFPZLoe = false;}
      if(ZWOxhcYrkt == true){ZWOxhcYrkt = false;}
      if(scQergnaFO == true){scQergnaFO = false;}
      if(focBxjpZWI == true){focBxjpZWI = false;}
      if(ynXaTyIODZ == true){ynXaTyIODZ = false;}
      if(YOeuCEcSrY == true){YOeuCEcSrY = false;}
      if(bzGazktMAy == true){bzGazktMAy = false;}
      if(mzUbwEFoLs == true){mzUbwEFoLs = false;}
      if(XZXeoQKgys == true){XZXeoQKgys = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAMFOWQUAQ
{ 
  void FCBEumczFe()
  { 
      bool zPJGdRleXo = false;
      bool WUPGGSGkWB = false;
      bool gRidhmDGAb = false;
      bool JTanqzgFhy = false;
      bool WtebUNiOoQ = false;
      bool tDohngfeXq = false;
      bool NfdwfDtaPG = false;
      bool kADYdllHJT = false;
      bool DoQjgFdrzJ = false;
      bool TChpjqPhwR = false;
      bool THziftAQEB = false;
      bool uYVEnYPsPa = false;
      bool YBbFlhSMnm = false;
      bool WEKqzuogEl = false;
      bool FNnxNtfcCL = false;
      bool aVSVsSfswx = false;
      bool bmbQeqNeEr = false;
      bool ihocULMdqr = false;
      bool CoJcLAkoyf = false;
      bool OwjHJRkWRW = false;
      string EqsRdixVif;
      string knfAZTKaOf;
      string GcQFawtifd;
      string NmTVuUNolN;
      string tzwOYAuNLK;
      string DqZdQaanqh;
      string oNpERyTJEE;
      string GVnAlHgBfZ;
      string BfXVaVMpEU;
      string tYxEYfIrxZ;
      string fkIGDhCZrJ;
      string tZHQgIpTcw;
      string ldFjKgXjbF;
      string ynEGtPXQRs;
      string TmytaURfXP;
      string poOAnCfYwV;
      string JSxlKFUBWR;
      string kYCjcyeKJp;
      string PqMLPJYDRr;
      string iyUuiAoLjU;
      if(EqsRdixVif == fkIGDhCZrJ){zPJGdRleXo = true;}
      else if(fkIGDhCZrJ == EqsRdixVif){THziftAQEB = true;}
      if(knfAZTKaOf == tZHQgIpTcw){WUPGGSGkWB = true;}
      else if(tZHQgIpTcw == knfAZTKaOf){uYVEnYPsPa = true;}
      if(GcQFawtifd == ldFjKgXjbF){gRidhmDGAb = true;}
      else if(ldFjKgXjbF == GcQFawtifd){YBbFlhSMnm = true;}
      if(NmTVuUNolN == ynEGtPXQRs){JTanqzgFhy = true;}
      else if(ynEGtPXQRs == NmTVuUNolN){WEKqzuogEl = true;}
      if(tzwOYAuNLK == TmytaURfXP){WtebUNiOoQ = true;}
      else if(TmytaURfXP == tzwOYAuNLK){FNnxNtfcCL = true;}
      if(DqZdQaanqh == poOAnCfYwV){tDohngfeXq = true;}
      else if(poOAnCfYwV == DqZdQaanqh){aVSVsSfswx = true;}
      if(oNpERyTJEE == JSxlKFUBWR){NfdwfDtaPG = true;}
      else if(JSxlKFUBWR == oNpERyTJEE){bmbQeqNeEr = true;}
      if(GVnAlHgBfZ == kYCjcyeKJp){kADYdllHJT = true;}
      if(BfXVaVMpEU == PqMLPJYDRr){DoQjgFdrzJ = true;}
      if(tYxEYfIrxZ == iyUuiAoLjU){TChpjqPhwR = true;}
      while(kYCjcyeKJp == GVnAlHgBfZ){ihocULMdqr = true;}
      while(PqMLPJYDRr == PqMLPJYDRr){CoJcLAkoyf = true;}
      while(iyUuiAoLjU == iyUuiAoLjU){OwjHJRkWRW = true;}
      if(zPJGdRleXo == true){zPJGdRleXo = false;}
      if(WUPGGSGkWB == true){WUPGGSGkWB = false;}
      if(gRidhmDGAb == true){gRidhmDGAb = false;}
      if(JTanqzgFhy == true){JTanqzgFhy = false;}
      if(WtebUNiOoQ == true){WtebUNiOoQ = false;}
      if(tDohngfeXq == true){tDohngfeXq = false;}
      if(NfdwfDtaPG == true){NfdwfDtaPG = false;}
      if(kADYdllHJT == true){kADYdllHJT = false;}
      if(DoQjgFdrzJ == true){DoQjgFdrzJ = false;}
      if(TChpjqPhwR == true){TChpjqPhwR = false;}
      if(THziftAQEB == true){THziftAQEB = false;}
      if(uYVEnYPsPa == true){uYVEnYPsPa = false;}
      if(YBbFlhSMnm == true){YBbFlhSMnm = false;}
      if(WEKqzuogEl == true){WEKqzuogEl = false;}
      if(FNnxNtfcCL == true){FNnxNtfcCL = false;}
      if(aVSVsSfswx == true){aVSVsSfswx = false;}
      if(bmbQeqNeEr == true){bmbQeqNeEr = false;}
      if(ihocULMdqr == true){ihocULMdqr = false;}
      if(CoJcLAkoyf == true){CoJcLAkoyf = false;}
      if(OwjHJRkWRW == true){OwjHJRkWRW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RXGZCRMTOO
{ 
  void SwHFupGaLS()
  { 
      bool uaSpkytBYZ = false;
      bool oyCjiorTti = false;
      bool cXCJuzQVpJ = false;
      bool QuuEzTmfin = false;
      bool zoAUwrSfFO = false;
      bool OYUugWYJuk = false;
      bool gYLPJtDyjP = false;
      bool CLkGimXgMD = false;
      bool fkPatqazWb = false;
      bool ucjxGadkLC = false;
      bool nUupMCnOLs = false;
      bool zqwrEwIjUS = false;
      bool SEaIUYbmzI = false;
      bool JmVKOLpZOr = false;
      bool CMmdcDgqrK = false;
      bool RsPsijsmVm = false;
      bool aBOCiLUkds = false;
      bool FiUcPGRweQ = false;
      bool qjtnqPWcad = false;
      bool SCDaRBxjtR = false;
      string KxzXJmSaCs;
      string qTGAKAjUJT;
      string GZpTzpidht;
      string WDSpVOfUuS;
      string uaxyOHWmPR;
      string fmFWGjGfYT;
      string EosIVnBQdw;
      string TPZpYfbrEq;
      string TuNQOixuil;
      string HAuaOGgobZ;
      string GFJSxPNPya;
      string HNbgzIacsl;
      string qGhrnTUyaR;
      string ymPdkOltSz;
      string VgwHdsYObG;
      string eEwpizXQed;
      string uOngcTyxuk;
      string VgKtQJKZNt;
      string uFWUlsqZtl;
      string pVPnDGsOeJ;
      if(KxzXJmSaCs == GFJSxPNPya){uaSpkytBYZ = true;}
      else if(GFJSxPNPya == KxzXJmSaCs){nUupMCnOLs = true;}
      if(qTGAKAjUJT == HNbgzIacsl){oyCjiorTti = true;}
      else if(HNbgzIacsl == qTGAKAjUJT){zqwrEwIjUS = true;}
      if(GZpTzpidht == qGhrnTUyaR){cXCJuzQVpJ = true;}
      else if(qGhrnTUyaR == GZpTzpidht){SEaIUYbmzI = true;}
      if(WDSpVOfUuS == ymPdkOltSz){QuuEzTmfin = true;}
      else if(ymPdkOltSz == WDSpVOfUuS){JmVKOLpZOr = true;}
      if(uaxyOHWmPR == VgwHdsYObG){zoAUwrSfFO = true;}
      else if(VgwHdsYObG == uaxyOHWmPR){CMmdcDgqrK = true;}
      if(fmFWGjGfYT == eEwpizXQed){OYUugWYJuk = true;}
      else if(eEwpizXQed == fmFWGjGfYT){RsPsijsmVm = true;}
      if(EosIVnBQdw == uOngcTyxuk){gYLPJtDyjP = true;}
      else if(uOngcTyxuk == EosIVnBQdw){aBOCiLUkds = true;}
      if(TPZpYfbrEq == VgKtQJKZNt){CLkGimXgMD = true;}
      if(TuNQOixuil == uFWUlsqZtl){fkPatqazWb = true;}
      if(HAuaOGgobZ == pVPnDGsOeJ){ucjxGadkLC = true;}
      while(VgKtQJKZNt == TPZpYfbrEq){FiUcPGRweQ = true;}
      while(uFWUlsqZtl == uFWUlsqZtl){qjtnqPWcad = true;}
      while(pVPnDGsOeJ == pVPnDGsOeJ){SCDaRBxjtR = true;}
      if(uaSpkytBYZ == true){uaSpkytBYZ = false;}
      if(oyCjiorTti == true){oyCjiorTti = false;}
      if(cXCJuzQVpJ == true){cXCJuzQVpJ = false;}
      if(QuuEzTmfin == true){QuuEzTmfin = false;}
      if(zoAUwrSfFO == true){zoAUwrSfFO = false;}
      if(OYUugWYJuk == true){OYUugWYJuk = false;}
      if(gYLPJtDyjP == true){gYLPJtDyjP = false;}
      if(CLkGimXgMD == true){CLkGimXgMD = false;}
      if(fkPatqazWb == true){fkPatqazWb = false;}
      if(ucjxGadkLC == true){ucjxGadkLC = false;}
      if(nUupMCnOLs == true){nUupMCnOLs = false;}
      if(zqwrEwIjUS == true){zqwrEwIjUS = false;}
      if(SEaIUYbmzI == true){SEaIUYbmzI = false;}
      if(JmVKOLpZOr == true){JmVKOLpZOr = false;}
      if(CMmdcDgqrK == true){CMmdcDgqrK = false;}
      if(RsPsijsmVm == true){RsPsijsmVm = false;}
      if(aBOCiLUkds == true){aBOCiLUkds = false;}
      if(FiUcPGRweQ == true){FiUcPGRweQ = false;}
      if(qjtnqPWcad == true){qjtnqPWcad = false;}
      if(SCDaRBxjtR == true){SCDaRBxjtR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMYNWUAXLZ
{ 
  void HguMITCYdj()
  { 
      bool WVbhPAKySa = false;
      bool tbWcbRjCeB = false;
      bool zDgLEKRhRp = false;
      bool fPLYrwEhLL = false;
      bool GEPnZilNdG = false;
      bool QpaBUToPcF = false;
      bool icfbudQxke = false;
      bool MBpSuunrlV = false;
      bool XDELZooJEX = false;
      bool HnFFcdXmsu = false;
      bool RocysOzHGZ = false;
      bool ewdGgeXUCG = false;
      bool oGsMXXwkpQ = false;
      bool WBzqEiaGRL = false;
      bool ohDerKKyYx = false;
      bool FDkmFKuPZV = false;
      bool ROQoCdwlCy = false;
      bool EQCpQHDOTM = false;
      bool MxMrKSPLks = false;
      bool mKgwtZQNbO = false;
      string EehLFhdzoO;
      string FWpmfRYwfW;
      string MSDMbFbidQ;
      string IxuwDQAJRm;
      string yIZIDJXRgx;
      string EsjkolaViA;
      string FuUYGIbtiO;
      string QPesYEruJS;
      string gJBgLONJHR;
      string peZQgCmBBt;
      string hdiRfoNpMj;
      string tfLQSusnMq;
      string uRlRYlpNMV;
      string QqsOjCajAW;
      string AWwWWJSIyk;
      string JznKzPqQrt;
      string yAdqTClwfP;
      string UJnpqYVOtO;
      string SgPbLRCiPT;
      string KJqFXArFDU;
      if(EehLFhdzoO == hdiRfoNpMj){WVbhPAKySa = true;}
      else if(hdiRfoNpMj == EehLFhdzoO){RocysOzHGZ = true;}
      if(FWpmfRYwfW == tfLQSusnMq){tbWcbRjCeB = true;}
      else if(tfLQSusnMq == FWpmfRYwfW){ewdGgeXUCG = true;}
      if(MSDMbFbidQ == uRlRYlpNMV){zDgLEKRhRp = true;}
      else if(uRlRYlpNMV == MSDMbFbidQ){oGsMXXwkpQ = true;}
      if(IxuwDQAJRm == QqsOjCajAW){fPLYrwEhLL = true;}
      else if(QqsOjCajAW == IxuwDQAJRm){WBzqEiaGRL = true;}
      if(yIZIDJXRgx == AWwWWJSIyk){GEPnZilNdG = true;}
      else if(AWwWWJSIyk == yIZIDJXRgx){ohDerKKyYx = true;}
      if(EsjkolaViA == JznKzPqQrt){QpaBUToPcF = true;}
      else if(JznKzPqQrt == EsjkolaViA){FDkmFKuPZV = true;}
      if(FuUYGIbtiO == yAdqTClwfP){icfbudQxke = true;}
      else if(yAdqTClwfP == FuUYGIbtiO){ROQoCdwlCy = true;}
      if(QPesYEruJS == UJnpqYVOtO){MBpSuunrlV = true;}
      if(gJBgLONJHR == SgPbLRCiPT){XDELZooJEX = true;}
      if(peZQgCmBBt == KJqFXArFDU){HnFFcdXmsu = true;}
      while(UJnpqYVOtO == QPesYEruJS){EQCpQHDOTM = true;}
      while(SgPbLRCiPT == SgPbLRCiPT){MxMrKSPLks = true;}
      while(KJqFXArFDU == KJqFXArFDU){mKgwtZQNbO = true;}
      if(WVbhPAKySa == true){WVbhPAKySa = false;}
      if(tbWcbRjCeB == true){tbWcbRjCeB = false;}
      if(zDgLEKRhRp == true){zDgLEKRhRp = false;}
      if(fPLYrwEhLL == true){fPLYrwEhLL = false;}
      if(GEPnZilNdG == true){GEPnZilNdG = false;}
      if(QpaBUToPcF == true){QpaBUToPcF = false;}
      if(icfbudQxke == true){icfbudQxke = false;}
      if(MBpSuunrlV == true){MBpSuunrlV = false;}
      if(XDELZooJEX == true){XDELZooJEX = false;}
      if(HnFFcdXmsu == true){HnFFcdXmsu = false;}
      if(RocysOzHGZ == true){RocysOzHGZ = false;}
      if(ewdGgeXUCG == true){ewdGgeXUCG = false;}
      if(oGsMXXwkpQ == true){oGsMXXwkpQ = false;}
      if(WBzqEiaGRL == true){WBzqEiaGRL = false;}
      if(ohDerKKyYx == true){ohDerKKyYx = false;}
      if(FDkmFKuPZV == true){FDkmFKuPZV = false;}
      if(ROQoCdwlCy == true){ROQoCdwlCy = false;}
      if(EQCpQHDOTM == true){EQCpQHDOTM = false;}
      if(MxMrKSPLks == true){MxMrKSPLks = false;}
      if(mKgwtZQNbO == true){mKgwtZQNbO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YSRJUJBWRO
{ 
  void BcWdyxwfSi()
  { 
      bool DlhrGDEfNy = false;
      bool dUGfKwirmf = false;
      bool uDaRbfoSme = false;
      bool kbpSVSLnqr = false;
      bool nYdUJSGKnW = false;
      bool RAMxjALPPZ = false;
      bool OlsiNBenJr = false;
      bool ktAtrWZGIJ = false;
      bool YedPMjOrhV = false;
      bool HwYQdBfuHH = false;
      bool nSBwlWASFN = false;
      bool aEGFBiHcVd = false;
      bool mlFmjnViQp = false;
      bool pdzBVFdhco = false;
      bool jwlUuCoSPt = false;
      bool sCYcTBNNLx = false;
      bool BQCPWwFEjw = false;
      bool FZzfsqzkqh = false;
      bool yDTVwnFVgU = false;
      bool rPWfnSsWxz = false;
      string pniusHQcZf;
      string CKERrHOYjE;
      string RAgIkLrMeZ;
      string OSCsNlxuia;
      string OAEGXZWnkM;
      string qtwEEoGZJg;
      string PDyAQiILEF;
      string JSpIpQwZjK;
      string nDbRhUWxoY;
      string fWlBLKCEoo;
      string RLjfCXEmOm;
      string rfpysLbfRw;
      string MLVeZlgnxe;
      string OrkuscSwOK;
      string QiiCfzgmIz;
      string iVmsbGoFFP;
      string pPpiXAutFP;
      string seQGfdbTyZ;
      string FtfxwrEqSm;
      string nNpyTAsAdf;
      if(pniusHQcZf == RLjfCXEmOm){DlhrGDEfNy = true;}
      else if(RLjfCXEmOm == pniusHQcZf){nSBwlWASFN = true;}
      if(CKERrHOYjE == rfpysLbfRw){dUGfKwirmf = true;}
      else if(rfpysLbfRw == CKERrHOYjE){aEGFBiHcVd = true;}
      if(RAgIkLrMeZ == MLVeZlgnxe){uDaRbfoSme = true;}
      else if(MLVeZlgnxe == RAgIkLrMeZ){mlFmjnViQp = true;}
      if(OSCsNlxuia == OrkuscSwOK){kbpSVSLnqr = true;}
      else if(OrkuscSwOK == OSCsNlxuia){pdzBVFdhco = true;}
      if(OAEGXZWnkM == QiiCfzgmIz){nYdUJSGKnW = true;}
      else if(QiiCfzgmIz == OAEGXZWnkM){jwlUuCoSPt = true;}
      if(qtwEEoGZJg == iVmsbGoFFP){RAMxjALPPZ = true;}
      else if(iVmsbGoFFP == qtwEEoGZJg){sCYcTBNNLx = true;}
      if(PDyAQiILEF == pPpiXAutFP){OlsiNBenJr = true;}
      else if(pPpiXAutFP == PDyAQiILEF){BQCPWwFEjw = true;}
      if(JSpIpQwZjK == seQGfdbTyZ){ktAtrWZGIJ = true;}
      if(nDbRhUWxoY == FtfxwrEqSm){YedPMjOrhV = true;}
      if(fWlBLKCEoo == nNpyTAsAdf){HwYQdBfuHH = true;}
      while(seQGfdbTyZ == JSpIpQwZjK){FZzfsqzkqh = true;}
      while(FtfxwrEqSm == FtfxwrEqSm){yDTVwnFVgU = true;}
      while(nNpyTAsAdf == nNpyTAsAdf){rPWfnSsWxz = true;}
      if(DlhrGDEfNy == true){DlhrGDEfNy = false;}
      if(dUGfKwirmf == true){dUGfKwirmf = false;}
      if(uDaRbfoSme == true){uDaRbfoSme = false;}
      if(kbpSVSLnqr == true){kbpSVSLnqr = false;}
      if(nYdUJSGKnW == true){nYdUJSGKnW = false;}
      if(RAMxjALPPZ == true){RAMxjALPPZ = false;}
      if(OlsiNBenJr == true){OlsiNBenJr = false;}
      if(ktAtrWZGIJ == true){ktAtrWZGIJ = false;}
      if(YedPMjOrhV == true){YedPMjOrhV = false;}
      if(HwYQdBfuHH == true){HwYQdBfuHH = false;}
      if(nSBwlWASFN == true){nSBwlWASFN = false;}
      if(aEGFBiHcVd == true){aEGFBiHcVd = false;}
      if(mlFmjnViQp == true){mlFmjnViQp = false;}
      if(pdzBVFdhco == true){pdzBVFdhco = false;}
      if(jwlUuCoSPt == true){jwlUuCoSPt = false;}
      if(sCYcTBNNLx == true){sCYcTBNNLx = false;}
      if(BQCPWwFEjw == true){BQCPWwFEjw = false;}
      if(FZzfsqzkqh == true){FZzfsqzkqh = false;}
      if(yDTVwnFVgU == true){yDTVwnFVgU = false;}
      if(rPWfnSsWxz == true){rPWfnSsWxz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WHHJLLISYI
{ 
  void rpJqDHlhVU()
  { 
      bool kJrNGInThA = false;
      bool opVVKPCWeF = false;
      bool yQXfjBRcrA = false;
      bool qCIBekVdzd = false;
      bool ZprCleJtgc = false;
      bool wgrkSTlMcF = false;
      bool pKbgJlhTpY = false;
      bool tXWBfIXUsF = false;
      bool qXuOEKKWhL = false;
      bool zIBtmONKsA = false;
      bool wpDIiXJpFK = false;
      bool wQSXNSPNcy = false;
      bool bKkeYkWbOQ = false;
      bool tNarIBUmef = false;
      bool ATQXOhpcfU = false;
      bool yzhtYlEYiy = false;
      bool BgbnPipZOM = false;
      bool ybhxyHsNPq = false;
      bool usutSuefTW = false;
      bool xuEgdSqcHf = false;
      string FqOZfatCom;
      string mgmlhojxWq;
      string SHFUDJZeET;
      string uIgguNBVEo;
      string oXfTBfCXzX;
      string FxEwjyksVW;
      string BOxUreAFqU;
      string nNrgCuakTW;
      string HBfgNyDjxx;
      string bIzhmZZLbV;
      string fxgdjrEWtn;
      string XAYzPAiQGs;
      string aPHsreOKsc;
      string VOIyqJTBwV;
      string sgoIZbjASm;
      string pIEhtPonlF;
      string dtcRSIqaHF;
      string ghUjAtaySQ;
      string tNqGlNJaDb;
      string UePqrzDXpR;
      if(FqOZfatCom == fxgdjrEWtn){kJrNGInThA = true;}
      else if(fxgdjrEWtn == FqOZfatCom){wpDIiXJpFK = true;}
      if(mgmlhojxWq == XAYzPAiQGs){opVVKPCWeF = true;}
      else if(XAYzPAiQGs == mgmlhojxWq){wQSXNSPNcy = true;}
      if(SHFUDJZeET == aPHsreOKsc){yQXfjBRcrA = true;}
      else if(aPHsreOKsc == SHFUDJZeET){bKkeYkWbOQ = true;}
      if(uIgguNBVEo == VOIyqJTBwV){qCIBekVdzd = true;}
      else if(VOIyqJTBwV == uIgguNBVEo){tNarIBUmef = true;}
      if(oXfTBfCXzX == sgoIZbjASm){ZprCleJtgc = true;}
      else if(sgoIZbjASm == oXfTBfCXzX){ATQXOhpcfU = true;}
      if(FxEwjyksVW == pIEhtPonlF){wgrkSTlMcF = true;}
      else if(pIEhtPonlF == FxEwjyksVW){yzhtYlEYiy = true;}
      if(BOxUreAFqU == dtcRSIqaHF){pKbgJlhTpY = true;}
      else if(dtcRSIqaHF == BOxUreAFqU){BgbnPipZOM = true;}
      if(nNrgCuakTW == ghUjAtaySQ){tXWBfIXUsF = true;}
      if(HBfgNyDjxx == tNqGlNJaDb){qXuOEKKWhL = true;}
      if(bIzhmZZLbV == UePqrzDXpR){zIBtmONKsA = true;}
      while(ghUjAtaySQ == nNrgCuakTW){ybhxyHsNPq = true;}
      while(tNqGlNJaDb == tNqGlNJaDb){usutSuefTW = true;}
      while(UePqrzDXpR == UePqrzDXpR){xuEgdSqcHf = true;}
      if(kJrNGInThA == true){kJrNGInThA = false;}
      if(opVVKPCWeF == true){opVVKPCWeF = false;}
      if(yQXfjBRcrA == true){yQXfjBRcrA = false;}
      if(qCIBekVdzd == true){qCIBekVdzd = false;}
      if(ZprCleJtgc == true){ZprCleJtgc = false;}
      if(wgrkSTlMcF == true){wgrkSTlMcF = false;}
      if(pKbgJlhTpY == true){pKbgJlhTpY = false;}
      if(tXWBfIXUsF == true){tXWBfIXUsF = false;}
      if(qXuOEKKWhL == true){qXuOEKKWhL = false;}
      if(zIBtmONKsA == true){zIBtmONKsA = false;}
      if(wpDIiXJpFK == true){wpDIiXJpFK = false;}
      if(wQSXNSPNcy == true){wQSXNSPNcy = false;}
      if(bKkeYkWbOQ == true){bKkeYkWbOQ = false;}
      if(tNarIBUmef == true){tNarIBUmef = false;}
      if(ATQXOhpcfU == true){ATQXOhpcfU = false;}
      if(yzhtYlEYiy == true){yzhtYlEYiy = false;}
      if(BgbnPipZOM == true){BgbnPipZOM = false;}
      if(ybhxyHsNPq == true){ybhxyHsNPq = false;}
      if(usutSuefTW == true){usutSuefTW = false;}
      if(xuEgdSqcHf == true){xuEgdSqcHf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KXIELGNUBV
{ 
  void xDjbclKCNU()
  { 
      bool PuTjcqWoSM = false;
      bool eqFYyuNohA = false;
      bool EbxyjBXYWJ = false;
      bool HlToibeMyV = false;
      bool BVUPDftAYT = false;
      bool uobrYmyUzb = false;
      bool TxRIFrXPpW = false;
      bool PAqLyiHhuD = false;
      bool GWADNRKbPu = false;
      bool dKNVCEDLKK = false;
      bool IdKBDuyPsp = false;
      bool fPZwUwwOum = false;
      bool gwAtsFmUJt = false;
      bool euXjucMzzS = false;
      bool TuhZONjRBG = false;
      bool IoQWdLdPHy = false;
      bool HdGzKkrpAq = false;
      bool iwObTlOZef = false;
      bool UVSDkpdAFi = false;
      bool zxrBKoohPd = false;
      string BRmsqAlfps;
      string peGXIoKnAB;
      string HldgQyMxho;
      string lscxMJbTVq;
      string UGZfadpzAa;
      string kSdbQOnGcs;
      string moxBGwBJLz;
      string NpSIfALyFl;
      string IMwGETPAgx;
      string VVqcEfJYYe;
      string bfnANtAUuP;
      string CoApjZrpxm;
      string fBcOdrzoEA;
      string qmZaJbYusJ;
      string TtEQtfUArd;
      string mSblyaDZWV;
      string tKPuXPPZgI;
      string AwwmSlwLTy;
      string WzxaMXKnbh;
      string XzYWPJdJrd;
      if(BRmsqAlfps == bfnANtAUuP){PuTjcqWoSM = true;}
      else if(bfnANtAUuP == BRmsqAlfps){IdKBDuyPsp = true;}
      if(peGXIoKnAB == CoApjZrpxm){eqFYyuNohA = true;}
      else if(CoApjZrpxm == peGXIoKnAB){fPZwUwwOum = true;}
      if(HldgQyMxho == fBcOdrzoEA){EbxyjBXYWJ = true;}
      else if(fBcOdrzoEA == HldgQyMxho){gwAtsFmUJt = true;}
      if(lscxMJbTVq == qmZaJbYusJ){HlToibeMyV = true;}
      else if(qmZaJbYusJ == lscxMJbTVq){euXjucMzzS = true;}
      if(UGZfadpzAa == TtEQtfUArd){BVUPDftAYT = true;}
      else if(TtEQtfUArd == UGZfadpzAa){TuhZONjRBG = true;}
      if(kSdbQOnGcs == mSblyaDZWV){uobrYmyUzb = true;}
      else if(mSblyaDZWV == kSdbQOnGcs){IoQWdLdPHy = true;}
      if(moxBGwBJLz == tKPuXPPZgI){TxRIFrXPpW = true;}
      else if(tKPuXPPZgI == moxBGwBJLz){HdGzKkrpAq = true;}
      if(NpSIfALyFl == AwwmSlwLTy){PAqLyiHhuD = true;}
      if(IMwGETPAgx == WzxaMXKnbh){GWADNRKbPu = true;}
      if(VVqcEfJYYe == XzYWPJdJrd){dKNVCEDLKK = true;}
      while(AwwmSlwLTy == NpSIfALyFl){iwObTlOZef = true;}
      while(WzxaMXKnbh == WzxaMXKnbh){UVSDkpdAFi = true;}
      while(XzYWPJdJrd == XzYWPJdJrd){zxrBKoohPd = true;}
      if(PuTjcqWoSM == true){PuTjcqWoSM = false;}
      if(eqFYyuNohA == true){eqFYyuNohA = false;}
      if(EbxyjBXYWJ == true){EbxyjBXYWJ = false;}
      if(HlToibeMyV == true){HlToibeMyV = false;}
      if(BVUPDftAYT == true){BVUPDftAYT = false;}
      if(uobrYmyUzb == true){uobrYmyUzb = false;}
      if(TxRIFrXPpW == true){TxRIFrXPpW = false;}
      if(PAqLyiHhuD == true){PAqLyiHhuD = false;}
      if(GWADNRKbPu == true){GWADNRKbPu = false;}
      if(dKNVCEDLKK == true){dKNVCEDLKK = false;}
      if(IdKBDuyPsp == true){IdKBDuyPsp = false;}
      if(fPZwUwwOum == true){fPZwUwwOum = false;}
      if(gwAtsFmUJt == true){gwAtsFmUJt = false;}
      if(euXjucMzzS == true){euXjucMzzS = false;}
      if(TuhZONjRBG == true){TuhZONjRBG = false;}
      if(IoQWdLdPHy == true){IoQWdLdPHy = false;}
      if(HdGzKkrpAq == true){HdGzKkrpAq = false;}
      if(iwObTlOZef == true){iwObTlOZef = false;}
      if(UVSDkpdAFi == true){UVSDkpdAFi = false;}
      if(zxrBKoohPd == true){zxrBKoohPd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class USEVLIMSGI
{ 
  void IQbpWcpORC()
  { 
      bool ABexrRClsj = false;
      bool oMJjUWxNpO = false;
      bool MgytOqCqbx = false;
      bool IgYnMnhCox = false;
      bool iEBCusXDje = false;
      bool RbMsFTDkhB = false;
      bool PLJubHnUXf = false;
      bool ntXseIeuzU = false;
      bool TzGwfgUfis = false;
      bool kxTnhXtFan = false;
      bool FCfEqWDSNx = false;
      bool nHkNgPEMPu = false;
      bool lHldupZjLH = false;
      bool NZUKPRTCFJ = false;
      bool cBSlEcLGGS = false;
      bool SgpeByQBIA = false;
      bool wTHGiNmaxP = false;
      bool uCHFRkozYR = false;
      bool dTcrngioJR = false;
      bool BSsEMJsLCq = false;
      string VRQqFDxikD;
      string cGLcDNjApm;
      string bbKVaBoBQZ;
      string BNYbXKpNsC;
      string fepfgzRyeL;
      string eYhkhtGuPE;
      string NwSKBOgiFs;
      string XVHmHxkenb;
      string iqVFucfmtd;
      string DtynniMedR;
      string SirlnIQtdk;
      string IbHnVWaNPY;
      string isobocXSyX;
      string kFAVJAyjQl;
      string MkJIUbmJSQ;
      string IyPFiYsQxL;
      string jxuGACbkeU;
      string YpwdMyjgGM;
      string pNAhPlptmj;
      string GgmFBOoCHR;
      if(VRQqFDxikD == SirlnIQtdk){ABexrRClsj = true;}
      else if(SirlnIQtdk == VRQqFDxikD){FCfEqWDSNx = true;}
      if(cGLcDNjApm == IbHnVWaNPY){oMJjUWxNpO = true;}
      else if(IbHnVWaNPY == cGLcDNjApm){nHkNgPEMPu = true;}
      if(bbKVaBoBQZ == isobocXSyX){MgytOqCqbx = true;}
      else if(isobocXSyX == bbKVaBoBQZ){lHldupZjLH = true;}
      if(BNYbXKpNsC == kFAVJAyjQl){IgYnMnhCox = true;}
      else if(kFAVJAyjQl == BNYbXKpNsC){NZUKPRTCFJ = true;}
      if(fepfgzRyeL == MkJIUbmJSQ){iEBCusXDje = true;}
      else if(MkJIUbmJSQ == fepfgzRyeL){cBSlEcLGGS = true;}
      if(eYhkhtGuPE == IyPFiYsQxL){RbMsFTDkhB = true;}
      else if(IyPFiYsQxL == eYhkhtGuPE){SgpeByQBIA = true;}
      if(NwSKBOgiFs == jxuGACbkeU){PLJubHnUXf = true;}
      else if(jxuGACbkeU == NwSKBOgiFs){wTHGiNmaxP = true;}
      if(XVHmHxkenb == YpwdMyjgGM){ntXseIeuzU = true;}
      if(iqVFucfmtd == pNAhPlptmj){TzGwfgUfis = true;}
      if(DtynniMedR == GgmFBOoCHR){kxTnhXtFan = true;}
      while(YpwdMyjgGM == XVHmHxkenb){uCHFRkozYR = true;}
      while(pNAhPlptmj == pNAhPlptmj){dTcrngioJR = true;}
      while(GgmFBOoCHR == GgmFBOoCHR){BSsEMJsLCq = true;}
      if(ABexrRClsj == true){ABexrRClsj = false;}
      if(oMJjUWxNpO == true){oMJjUWxNpO = false;}
      if(MgytOqCqbx == true){MgytOqCqbx = false;}
      if(IgYnMnhCox == true){IgYnMnhCox = false;}
      if(iEBCusXDje == true){iEBCusXDje = false;}
      if(RbMsFTDkhB == true){RbMsFTDkhB = false;}
      if(PLJubHnUXf == true){PLJubHnUXf = false;}
      if(ntXseIeuzU == true){ntXseIeuzU = false;}
      if(TzGwfgUfis == true){TzGwfgUfis = false;}
      if(kxTnhXtFan == true){kxTnhXtFan = false;}
      if(FCfEqWDSNx == true){FCfEqWDSNx = false;}
      if(nHkNgPEMPu == true){nHkNgPEMPu = false;}
      if(lHldupZjLH == true){lHldupZjLH = false;}
      if(NZUKPRTCFJ == true){NZUKPRTCFJ = false;}
      if(cBSlEcLGGS == true){cBSlEcLGGS = false;}
      if(SgpeByQBIA == true){SgpeByQBIA = false;}
      if(wTHGiNmaxP == true){wTHGiNmaxP = false;}
      if(uCHFRkozYR == true){uCHFRkozYR = false;}
      if(dTcrngioJR == true){dTcrngioJR = false;}
      if(BSsEMJsLCq == true){BSsEMJsLCq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUTNUPCRUU
{ 
  void BEdxNFzmCW()
  { 
      bool IqZttTDPLD = false;
      bool OJsKDWTZtc = false;
      bool skrNLKVYuC = false;
      bool HsWCnyzjyu = false;
      bool oQrRIQWYlb = false;
      bool riwbUXyMij = false;
      bool ydUJuVlpVF = false;
      bool XiazmcsaEt = false;
      bool mwlSJXwuhQ = false;
      bool zmBNxKuhVl = false;
      bool dfCgEJIwnr = false;
      bool eXHowBrCzX = false;
      bool YqIFFjhMCb = false;
      bool gKFSPGtEOA = false;
      bool PAGplbeLRu = false;
      bool SshxNmXxbT = false;
      bool autLKTSoYp = false;
      bool GmmzIYkSTd = false;
      bool FVuGJnbHEc = false;
      bool ixctYTGteR = false;
      string bgLmzFtglV;
      string XfXedIjUtM;
      string LQfKYAPGLP;
      string XYyNSRHgdK;
      string GkXzKRyaNn;
      string kBQCGLAAOz;
      string omUVxzgJML;
      string ADpjGasgzG;
      string BorWeWHwGG;
      string RGSeVTPBBK;
      string joOBmhKgwf;
      string RTBHyAuyqa;
      string qkCFttkLNm;
      string KqenWMZpiw;
      string LaAaoxEKfU;
      string XRKaTzlJHs;
      string xzSJVaoNjl;
      string aEOtOPjbQx;
      string oZesOrgDUW;
      string aPipzMIqFN;
      if(bgLmzFtglV == joOBmhKgwf){IqZttTDPLD = true;}
      else if(joOBmhKgwf == bgLmzFtglV){dfCgEJIwnr = true;}
      if(XfXedIjUtM == RTBHyAuyqa){OJsKDWTZtc = true;}
      else if(RTBHyAuyqa == XfXedIjUtM){eXHowBrCzX = true;}
      if(LQfKYAPGLP == qkCFttkLNm){skrNLKVYuC = true;}
      else if(qkCFttkLNm == LQfKYAPGLP){YqIFFjhMCb = true;}
      if(XYyNSRHgdK == KqenWMZpiw){HsWCnyzjyu = true;}
      else if(KqenWMZpiw == XYyNSRHgdK){gKFSPGtEOA = true;}
      if(GkXzKRyaNn == LaAaoxEKfU){oQrRIQWYlb = true;}
      else if(LaAaoxEKfU == GkXzKRyaNn){PAGplbeLRu = true;}
      if(kBQCGLAAOz == XRKaTzlJHs){riwbUXyMij = true;}
      else if(XRKaTzlJHs == kBQCGLAAOz){SshxNmXxbT = true;}
      if(omUVxzgJML == xzSJVaoNjl){ydUJuVlpVF = true;}
      else if(xzSJVaoNjl == omUVxzgJML){autLKTSoYp = true;}
      if(ADpjGasgzG == aEOtOPjbQx){XiazmcsaEt = true;}
      if(BorWeWHwGG == oZesOrgDUW){mwlSJXwuhQ = true;}
      if(RGSeVTPBBK == aPipzMIqFN){zmBNxKuhVl = true;}
      while(aEOtOPjbQx == ADpjGasgzG){GmmzIYkSTd = true;}
      while(oZesOrgDUW == oZesOrgDUW){FVuGJnbHEc = true;}
      while(aPipzMIqFN == aPipzMIqFN){ixctYTGteR = true;}
      if(IqZttTDPLD == true){IqZttTDPLD = false;}
      if(OJsKDWTZtc == true){OJsKDWTZtc = false;}
      if(skrNLKVYuC == true){skrNLKVYuC = false;}
      if(HsWCnyzjyu == true){HsWCnyzjyu = false;}
      if(oQrRIQWYlb == true){oQrRIQWYlb = false;}
      if(riwbUXyMij == true){riwbUXyMij = false;}
      if(ydUJuVlpVF == true){ydUJuVlpVF = false;}
      if(XiazmcsaEt == true){XiazmcsaEt = false;}
      if(mwlSJXwuhQ == true){mwlSJXwuhQ = false;}
      if(zmBNxKuhVl == true){zmBNxKuhVl = false;}
      if(dfCgEJIwnr == true){dfCgEJIwnr = false;}
      if(eXHowBrCzX == true){eXHowBrCzX = false;}
      if(YqIFFjhMCb == true){YqIFFjhMCb = false;}
      if(gKFSPGtEOA == true){gKFSPGtEOA = false;}
      if(PAGplbeLRu == true){PAGplbeLRu = false;}
      if(SshxNmXxbT == true){SshxNmXxbT = false;}
      if(autLKTSoYp == true){autLKTSoYp = false;}
      if(GmmzIYkSTd == true){GmmzIYkSTd = false;}
      if(FVuGJnbHEc == true){FVuGJnbHEc = false;}
      if(ixctYTGteR == true){ixctYTGteR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBFMPINUDW
{ 
  void VFqSqCKcYT()
  { 
      bool PzJVnEebRa = false;
      bool AEFLiKGkHI = false;
      bool wYAJcNHxdL = false;
      bool oHbKutXSWc = false;
      bool ihzaKKblaj = false;
      bool QywDHpzAra = false;
      bool xhxGksbtPo = false;
      bool lnNdYOZYzS = false;
      bool lVWtupKYCF = false;
      bool uXZwfBkspQ = false;
      bool hgVlxckSds = false;
      bool QZBZnaKDLt = false;
      bool hDrJtONRxX = false;
      bool dfihjEAjwS = false;
      bool FrtIoUWAHF = false;
      bool pghuieoLri = false;
      bool OTUGPjqSoj = false;
      bool aZGsooIiUY = false;
      bool rMJrgwynyF = false;
      bool PnrMDlWnsE = false;
      string bQQLAnNFlt;
      string eSDRbaeEBt;
      string golBhZtftg;
      string cwmVOtWxnZ;
      string RuSSpwAxWe;
      string mNUKLmdPcZ;
      string shLFQhfhCh;
      string EhQbblWTKl;
      string ZwIOsPabJb;
      string PHUNfjjMBH;
      string PRunaFxshZ;
      string QJEpAwZwMA;
      string HEYaRwMCur;
      string CJSCVHBTnm;
      string RhsjLGCdNi;
      string KmAAALsUWd;
      string suxoXGqCTr;
      string uFHYiZKnPL;
      string thnLhOJRBK;
      string OgxKtWjDME;
      if(bQQLAnNFlt == PRunaFxshZ){PzJVnEebRa = true;}
      else if(PRunaFxshZ == bQQLAnNFlt){hgVlxckSds = true;}
      if(eSDRbaeEBt == QJEpAwZwMA){AEFLiKGkHI = true;}
      else if(QJEpAwZwMA == eSDRbaeEBt){QZBZnaKDLt = true;}
      if(golBhZtftg == HEYaRwMCur){wYAJcNHxdL = true;}
      else if(HEYaRwMCur == golBhZtftg){hDrJtONRxX = true;}
      if(cwmVOtWxnZ == CJSCVHBTnm){oHbKutXSWc = true;}
      else if(CJSCVHBTnm == cwmVOtWxnZ){dfihjEAjwS = true;}
      if(RuSSpwAxWe == RhsjLGCdNi){ihzaKKblaj = true;}
      else if(RhsjLGCdNi == RuSSpwAxWe){FrtIoUWAHF = true;}
      if(mNUKLmdPcZ == KmAAALsUWd){QywDHpzAra = true;}
      else if(KmAAALsUWd == mNUKLmdPcZ){pghuieoLri = true;}
      if(shLFQhfhCh == suxoXGqCTr){xhxGksbtPo = true;}
      else if(suxoXGqCTr == shLFQhfhCh){OTUGPjqSoj = true;}
      if(EhQbblWTKl == uFHYiZKnPL){lnNdYOZYzS = true;}
      if(ZwIOsPabJb == thnLhOJRBK){lVWtupKYCF = true;}
      if(PHUNfjjMBH == OgxKtWjDME){uXZwfBkspQ = true;}
      while(uFHYiZKnPL == EhQbblWTKl){aZGsooIiUY = true;}
      while(thnLhOJRBK == thnLhOJRBK){rMJrgwynyF = true;}
      while(OgxKtWjDME == OgxKtWjDME){PnrMDlWnsE = true;}
      if(PzJVnEebRa == true){PzJVnEebRa = false;}
      if(AEFLiKGkHI == true){AEFLiKGkHI = false;}
      if(wYAJcNHxdL == true){wYAJcNHxdL = false;}
      if(oHbKutXSWc == true){oHbKutXSWc = false;}
      if(ihzaKKblaj == true){ihzaKKblaj = false;}
      if(QywDHpzAra == true){QywDHpzAra = false;}
      if(xhxGksbtPo == true){xhxGksbtPo = false;}
      if(lnNdYOZYzS == true){lnNdYOZYzS = false;}
      if(lVWtupKYCF == true){lVWtupKYCF = false;}
      if(uXZwfBkspQ == true){uXZwfBkspQ = false;}
      if(hgVlxckSds == true){hgVlxckSds = false;}
      if(QZBZnaKDLt == true){QZBZnaKDLt = false;}
      if(hDrJtONRxX == true){hDrJtONRxX = false;}
      if(dfihjEAjwS == true){dfihjEAjwS = false;}
      if(FrtIoUWAHF == true){FrtIoUWAHF = false;}
      if(pghuieoLri == true){pghuieoLri = false;}
      if(OTUGPjqSoj == true){OTUGPjqSoj = false;}
      if(aZGsooIiUY == true){aZGsooIiUY = false;}
      if(rMJrgwynyF == true){rMJrgwynyF = false;}
      if(PnrMDlWnsE == true){PnrMDlWnsE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UHKPJOERVO
{ 
  void XYqKFuAjcP()
  { 
      bool GUgBVoCEhR = false;
      bool geoTmNzCeN = false;
      bool BBYVXSTVCf = false;
      bool ImgBfMJaza = false;
      bool HDPQSJNxfZ = false;
      bool kUgLgFwKcD = false;
      bool VgBBIsxmma = false;
      bool DYCEGykHDN = false;
      bool FWocunGVUa = false;
      bool PzyuEaBNHZ = false;
      bool MZJEVMRcFh = false;
      bool TnHOyzqYGT = false;
      bool mbSMLEZGzf = false;
      bool xWAdBeMkGh = false;
      bool WdPlGbrixF = false;
      bool ibHmljGwsR = false;
      bool lKdZkwmdMS = false;
      bool lGRYxJLgFi = false;
      bool MqJswUPMqR = false;
      bool YProuMzpBK = false;
      string VuahEXsOPK;
      string ZIHWXbeKIm;
      string ofVjJtCPSp;
      string xRHZscFdOH;
      string MQBrfoZcsA;
      string zPkMzpZpXK;
      string UduYMHBgdu;
      string WAwAZXecEU;
      string UZVRqgftZD;
      string COGEmiVbeX;
      string nszydyTkmb;
      string LwlDouIche;
      string aHGarItqMq;
      string CCxfgbaWnr;
      string NuHyqFbDOq;
      string artzxglXGU;
      string EbXuYJzGVN;
      string UkopRfzHil;
      string gqcVQKHxhA;
      string oCQTmkWLZh;
      if(VuahEXsOPK == nszydyTkmb){GUgBVoCEhR = true;}
      else if(nszydyTkmb == VuahEXsOPK){MZJEVMRcFh = true;}
      if(ZIHWXbeKIm == LwlDouIche){geoTmNzCeN = true;}
      else if(LwlDouIche == ZIHWXbeKIm){TnHOyzqYGT = true;}
      if(ofVjJtCPSp == aHGarItqMq){BBYVXSTVCf = true;}
      else if(aHGarItqMq == ofVjJtCPSp){mbSMLEZGzf = true;}
      if(xRHZscFdOH == CCxfgbaWnr){ImgBfMJaza = true;}
      else if(CCxfgbaWnr == xRHZscFdOH){xWAdBeMkGh = true;}
      if(MQBrfoZcsA == NuHyqFbDOq){HDPQSJNxfZ = true;}
      else if(NuHyqFbDOq == MQBrfoZcsA){WdPlGbrixF = true;}
      if(zPkMzpZpXK == artzxglXGU){kUgLgFwKcD = true;}
      else if(artzxglXGU == zPkMzpZpXK){ibHmljGwsR = true;}
      if(UduYMHBgdu == EbXuYJzGVN){VgBBIsxmma = true;}
      else if(EbXuYJzGVN == UduYMHBgdu){lKdZkwmdMS = true;}
      if(WAwAZXecEU == UkopRfzHil){DYCEGykHDN = true;}
      if(UZVRqgftZD == gqcVQKHxhA){FWocunGVUa = true;}
      if(COGEmiVbeX == oCQTmkWLZh){PzyuEaBNHZ = true;}
      while(UkopRfzHil == WAwAZXecEU){lGRYxJLgFi = true;}
      while(gqcVQKHxhA == gqcVQKHxhA){MqJswUPMqR = true;}
      while(oCQTmkWLZh == oCQTmkWLZh){YProuMzpBK = true;}
      if(GUgBVoCEhR == true){GUgBVoCEhR = false;}
      if(geoTmNzCeN == true){geoTmNzCeN = false;}
      if(BBYVXSTVCf == true){BBYVXSTVCf = false;}
      if(ImgBfMJaza == true){ImgBfMJaza = false;}
      if(HDPQSJNxfZ == true){HDPQSJNxfZ = false;}
      if(kUgLgFwKcD == true){kUgLgFwKcD = false;}
      if(VgBBIsxmma == true){VgBBIsxmma = false;}
      if(DYCEGykHDN == true){DYCEGykHDN = false;}
      if(FWocunGVUa == true){FWocunGVUa = false;}
      if(PzyuEaBNHZ == true){PzyuEaBNHZ = false;}
      if(MZJEVMRcFh == true){MZJEVMRcFh = false;}
      if(TnHOyzqYGT == true){TnHOyzqYGT = false;}
      if(mbSMLEZGzf == true){mbSMLEZGzf = false;}
      if(xWAdBeMkGh == true){xWAdBeMkGh = false;}
      if(WdPlGbrixF == true){WdPlGbrixF = false;}
      if(ibHmljGwsR == true){ibHmljGwsR = false;}
      if(lKdZkwmdMS == true){lKdZkwmdMS = false;}
      if(lGRYxJLgFi == true){lGRYxJLgFi = false;}
      if(MqJswUPMqR == true){MqJswUPMqR = false;}
      if(YProuMzpBK == true){YProuMzpBK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OAKJDKIFFE
{ 
  void xSpoYtzXjC()
  { 
      bool yZisDBdQpT = false;
      bool gVjiofWsKW = false;
      bool WHZKTwKOVz = false;
      bool VLZlzLcnBq = false;
      bool HGgOcALfdF = false;
      bool HQoatpzXYH = false;
      bool qPtpyUuxic = false;
      bool CiqSOPaKhT = false;
      bool jdkPqFVyrI = false;
      bool MFOtArLqQH = false;
      bool EOxADYYWMd = false;
      bool PooEXNddzs = false;
      bool zwFZQxTxSV = false;
      bool EitaOVfjMS = false;
      bool gzlOsWPKVm = false;
      bool OgqXIIIWiF = false;
      bool EaDqYfuOoC = false;
      bool gsQfLzKpgt = false;
      bool gJafHWrWSG = false;
      bool MJBHOFwtpN = false;
      string nUTCxEOwQt;
      string dGtDafJnIk;
      string prXGPDsoep;
      string cgODsylPii;
      string UFlyjBPJkn;
      string CZYmquwMms;
      string KYRZQwrqKc;
      string ssFYPkGYVN;
      string niDpmDIaMy;
      string BYcoXwmLhm;
      string JXzIuIUzWF;
      string nWqYFbUbmN;
      string nQeMbTQPBT;
      string xuqhDPiute;
      string iIDGJdhEiw;
      string aLYTzssmfa;
      string rEyDIsfIUp;
      string rZgHdeMXCx;
      string lMgFslWXiJ;
      string VwOSleJAyQ;
      if(nUTCxEOwQt == JXzIuIUzWF){yZisDBdQpT = true;}
      else if(JXzIuIUzWF == nUTCxEOwQt){EOxADYYWMd = true;}
      if(dGtDafJnIk == nWqYFbUbmN){gVjiofWsKW = true;}
      else if(nWqYFbUbmN == dGtDafJnIk){PooEXNddzs = true;}
      if(prXGPDsoep == nQeMbTQPBT){WHZKTwKOVz = true;}
      else if(nQeMbTQPBT == prXGPDsoep){zwFZQxTxSV = true;}
      if(cgODsylPii == xuqhDPiute){VLZlzLcnBq = true;}
      else if(xuqhDPiute == cgODsylPii){EitaOVfjMS = true;}
      if(UFlyjBPJkn == iIDGJdhEiw){HGgOcALfdF = true;}
      else if(iIDGJdhEiw == UFlyjBPJkn){gzlOsWPKVm = true;}
      if(CZYmquwMms == aLYTzssmfa){HQoatpzXYH = true;}
      else if(aLYTzssmfa == CZYmquwMms){OgqXIIIWiF = true;}
      if(KYRZQwrqKc == rEyDIsfIUp){qPtpyUuxic = true;}
      else if(rEyDIsfIUp == KYRZQwrqKc){EaDqYfuOoC = true;}
      if(ssFYPkGYVN == rZgHdeMXCx){CiqSOPaKhT = true;}
      if(niDpmDIaMy == lMgFslWXiJ){jdkPqFVyrI = true;}
      if(BYcoXwmLhm == VwOSleJAyQ){MFOtArLqQH = true;}
      while(rZgHdeMXCx == ssFYPkGYVN){gsQfLzKpgt = true;}
      while(lMgFslWXiJ == lMgFslWXiJ){gJafHWrWSG = true;}
      while(VwOSleJAyQ == VwOSleJAyQ){MJBHOFwtpN = true;}
      if(yZisDBdQpT == true){yZisDBdQpT = false;}
      if(gVjiofWsKW == true){gVjiofWsKW = false;}
      if(WHZKTwKOVz == true){WHZKTwKOVz = false;}
      if(VLZlzLcnBq == true){VLZlzLcnBq = false;}
      if(HGgOcALfdF == true){HGgOcALfdF = false;}
      if(HQoatpzXYH == true){HQoatpzXYH = false;}
      if(qPtpyUuxic == true){qPtpyUuxic = false;}
      if(CiqSOPaKhT == true){CiqSOPaKhT = false;}
      if(jdkPqFVyrI == true){jdkPqFVyrI = false;}
      if(MFOtArLqQH == true){MFOtArLqQH = false;}
      if(EOxADYYWMd == true){EOxADYYWMd = false;}
      if(PooEXNddzs == true){PooEXNddzs = false;}
      if(zwFZQxTxSV == true){zwFZQxTxSV = false;}
      if(EitaOVfjMS == true){EitaOVfjMS = false;}
      if(gzlOsWPKVm == true){gzlOsWPKVm = false;}
      if(OgqXIIIWiF == true){OgqXIIIWiF = false;}
      if(EaDqYfuOoC == true){EaDqYfuOoC = false;}
      if(gsQfLzKpgt == true){gsQfLzKpgt = false;}
      if(gJafHWrWSG == true){gJafHWrWSG = false;}
      if(MJBHOFwtpN == true){MJBHOFwtpN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KNSIAWHSXC
{ 
  void kVWkLiCkhs()
  { 
      bool EKRbseouXX = false;
      bool BNnaYxdagw = false;
      bool YKdygWMoHV = false;
      bool egAnywZATP = false;
      bool NFqDPjNUdr = false;
      bool xsPmTtfStV = false;
      bool RAnCsUMAcc = false;
      bool XcHRiSTaix = false;
      bool JrLOXkQNTD = false;
      bool PHGxyMRoKu = false;
      bool XNrAUTlyDB = false;
      bool aFjxMYoYdH = false;
      bool EyfYMQWJSW = false;
      bool AePmZuAKtE = false;
      bool zSKScKWIjY = false;
      bool XsKCpYhSnE = false;
      bool xbegAwowWR = false;
      bool XdeYIknMuC = false;
      bool sNZsyHTNxA = false;
      bool MhWoHWndSg = false;
      string mXeqDXYwwk;
      string ZddHpDOnom;
      string JCisxPoIjc;
      string hpsrWZIqVu;
      string kSnBORCCZy;
      string kJNLZjoktm;
      string hPLTCjjlkQ;
      string uWStCqOgee;
      string MmhlrYbhSm;
      string kWxhNUHUye;
      string hQRJDNqTJi;
      string UHGOatgZad;
      string HCSxfXZjfg;
      string jtizxuVYhd;
      string hIYiRcQhHS;
      string mgsTXexTcf;
      string nGnbzZYGQe;
      string YIqxwzcjfC;
      string GqcMtCBObR;
      string xBuCoaTwir;
      if(mXeqDXYwwk == hQRJDNqTJi){EKRbseouXX = true;}
      else if(hQRJDNqTJi == mXeqDXYwwk){XNrAUTlyDB = true;}
      if(ZddHpDOnom == UHGOatgZad){BNnaYxdagw = true;}
      else if(UHGOatgZad == ZddHpDOnom){aFjxMYoYdH = true;}
      if(JCisxPoIjc == HCSxfXZjfg){YKdygWMoHV = true;}
      else if(HCSxfXZjfg == JCisxPoIjc){EyfYMQWJSW = true;}
      if(hpsrWZIqVu == jtizxuVYhd){egAnywZATP = true;}
      else if(jtizxuVYhd == hpsrWZIqVu){AePmZuAKtE = true;}
      if(kSnBORCCZy == hIYiRcQhHS){NFqDPjNUdr = true;}
      else if(hIYiRcQhHS == kSnBORCCZy){zSKScKWIjY = true;}
      if(kJNLZjoktm == mgsTXexTcf){xsPmTtfStV = true;}
      else if(mgsTXexTcf == kJNLZjoktm){XsKCpYhSnE = true;}
      if(hPLTCjjlkQ == nGnbzZYGQe){RAnCsUMAcc = true;}
      else if(nGnbzZYGQe == hPLTCjjlkQ){xbegAwowWR = true;}
      if(uWStCqOgee == YIqxwzcjfC){XcHRiSTaix = true;}
      if(MmhlrYbhSm == GqcMtCBObR){JrLOXkQNTD = true;}
      if(kWxhNUHUye == xBuCoaTwir){PHGxyMRoKu = true;}
      while(YIqxwzcjfC == uWStCqOgee){XdeYIknMuC = true;}
      while(GqcMtCBObR == GqcMtCBObR){sNZsyHTNxA = true;}
      while(xBuCoaTwir == xBuCoaTwir){MhWoHWndSg = true;}
      if(EKRbseouXX == true){EKRbseouXX = false;}
      if(BNnaYxdagw == true){BNnaYxdagw = false;}
      if(YKdygWMoHV == true){YKdygWMoHV = false;}
      if(egAnywZATP == true){egAnywZATP = false;}
      if(NFqDPjNUdr == true){NFqDPjNUdr = false;}
      if(xsPmTtfStV == true){xsPmTtfStV = false;}
      if(RAnCsUMAcc == true){RAnCsUMAcc = false;}
      if(XcHRiSTaix == true){XcHRiSTaix = false;}
      if(JrLOXkQNTD == true){JrLOXkQNTD = false;}
      if(PHGxyMRoKu == true){PHGxyMRoKu = false;}
      if(XNrAUTlyDB == true){XNrAUTlyDB = false;}
      if(aFjxMYoYdH == true){aFjxMYoYdH = false;}
      if(EyfYMQWJSW == true){EyfYMQWJSW = false;}
      if(AePmZuAKtE == true){AePmZuAKtE = false;}
      if(zSKScKWIjY == true){zSKScKWIjY = false;}
      if(XsKCpYhSnE == true){XsKCpYhSnE = false;}
      if(xbegAwowWR == true){xbegAwowWR = false;}
      if(XdeYIknMuC == true){XdeYIknMuC = false;}
      if(sNZsyHTNxA == true){sNZsyHTNxA = false;}
      if(MhWoHWndSg == true){MhWoHWndSg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RJSBOMCBQB
{ 
  void bTjsyYFfTC()
  { 
      bool gQwURIoKJN = false;
      bool MBeyZBNoTV = false;
      bool cQEtfwwtLX = false;
      bool tDtSPpFQqp = false;
      bool OganSQgNFD = false;
      bool HuIogQLBnV = false;
      bool LuykTIGMij = false;
      bool uxydHwoQaP = false;
      bool OinIPzuElz = false;
      bool dDbUdTioTK = false;
      bool JUeVHKwdhk = false;
      bool auaYGcGpVU = false;
      bool MCaiFrUczm = false;
      bool NzwQGtERBE = false;
      bool CRWBXhbDOB = false;
      bool MsTzxHsuQO = false;
      bool pTdtWazJRL = false;
      bool XnnRSueYLX = false;
      bool QQOxaUfwSz = false;
      bool AJBmOhmcdx = false;
      string ZBtQjuOpHD;
      string TTWETdLYEk;
      string gTHpVqfNhD;
      string RmNyaRbQgR;
      string kKCCnbVtdL;
      string VuUiRFtDtr;
      string OBIEkfGXcC;
      string BtrmAWQECt;
      string VliVgWRdgU;
      string XXWnDjCyQH;
      string UxQaJaChiu;
      string noBzVcRlWN;
      string ObqIedXDiP;
      string USmtYXUILG;
      string UiukfhWWSZ;
      string RPaCssGIuf;
      string CyySZVBGZx;
      string IJZPsefFcw;
      string GBkIyErkBf;
      string RMMfEVkbLK;
      if(ZBtQjuOpHD == UxQaJaChiu){gQwURIoKJN = true;}
      else if(UxQaJaChiu == ZBtQjuOpHD){JUeVHKwdhk = true;}
      if(TTWETdLYEk == noBzVcRlWN){MBeyZBNoTV = true;}
      else if(noBzVcRlWN == TTWETdLYEk){auaYGcGpVU = true;}
      if(gTHpVqfNhD == ObqIedXDiP){cQEtfwwtLX = true;}
      else if(ObqIedXDiP == gTHpVqfNhD){MCaiFrUczm = true;}
      if(RmNyaRbQgR == USmtYXUILG){tDtSPpFQqp = true;}
      else if(USmtYXUILG == RmNyaRbQgR){NzwQGtERBE = true;}
      if(kKCCnbVtdL == UiukfhWWSZ){OganSQgNFD = true;}
      else if(UiukfhWWSZ == kKCCnbVtdL){CRWBXhbDOB = true;}
      if(VuUiRFtDtr == RPaCssGIuf){HuIogQLBnV = true;}
      else if(RPaCssGIuf == VuUiRFtDtr){MsTzxHsuQO = true;}
      if(OBIEkfGXcC == CyySZVBGZx){LuykTIGMij = true;}
      else if(CyySZVBGZx == OBIEkfGXcC){pTdtWazJRL = true;}
      if(BtrmAWQECt == IJZPsefFcw){uxydHwoQaP = true;}
      if(VliVgWRdgU == GBkIyErkBf){OinIPzuElz = true;}
      if(XXWnDjCyQH == RMMfEVkbLK){dDbUdTioTK = true;}
      while(IJZPsefFcw == BtrmAWQECt){XnnRSueYLX = true;}
      while(GBkIyErkBf == GBkIyErkBf){QQOxaUfwSz = true;}
      while(RMMfEVkbLK == RMMfEVkbLK){AJBmOhmcdx = true;}
      if(gQwURIoKJN == true){gQwURIoKJN = false;}
      if(MBeyZBNoTV == true){MBeyZBNoTV = false;}
      if(cQEtfwwtLX == true){cQEtfwwtLX = false;}
      if(tDtSPpFQqp == true){tDtSPpFQqp = false;}
      if(OganSQgNFD == true){OganSQgNFD = false;}
      if(HuIogQLBnV == true){HuIogQLBnV = false;}
      if(LuykTIGMij == true){LuykTIGMij = false;}
      if(uxydHwoQaP == true){uxydHwoQaP = false;}
      if(OinIPzuElz == true){OinIPzuElz = false;}
      if(dDbUdTioTK == true){dDbUdTioTK = false;}
      if(JUeVHKwdhk == true){JUeVHKwdhk = false;}
      if(auaYGcGpVU == true){auaYGcGpVU = false;}
      if(MCaiFrUczm == true){MCaiFrUczm = false;}
      if(NzwQGtERBE == true){NzwQGtERBE = false;}
      if(CRWBXhbDOB == true){CRWBXhbDOB = false;}
      if(MsTzxHsuQO == true){MsTzxHsuQO = false;}
      if(pTdtWazJRL == true){pTdtWazJRL = false;}
      if(XnnRSueYLX == true){XnnRSueYLX = false;}
      if(QQOxaUfwSz == true){QQOxaUfwSz = false;}
      if(AJBmOhmcdx == true){AJBmOhmcdx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QOZVIATNWF
{ 
  void OtdpAhUJlV()
  { 
      bool qxahdHuxBs = false;
      bool kLHUzIJLPj = false;
      bool YTydGiLkKk = false;
      bool caMabOnQwH = false;
      bool yVUleCMTof = false;
      bool LkGpmWzwau = false;
      bool wKmQQKygrj = false;
      bool UrOIkDyMzE = false;
      bool VqueYqTVmE = false;
      bool PqpAKniEUU = false;
      bool DeaELTVyFj = false;
      bool YmxVZEOHrY = false;
      bool pctnUcCOxw = false;
      bool UtqeBpPpTF = false;
      bool UVQDectTaG = false;
      bool YaMwdakmih = false;
      bool QHAIOeuRUi = false;
      bool nXmlDTLqIr = false;
      bool himqWsgtAa = false;
      bool EcHknNUHnA = false;
      string tqxdbXETHN;
      string XQoDICfOjm;
      string dMtrJmzLsb;
      string njPzwCJhaY;
      string dUnTPgguus;
      string GzFLChxEUn;
      string XsafZmBoHG;
      string synKIJYZbc;
      string FEQAUodDxO;
      string FENlBktItc;
      string eqnnAIKuCr;
      string IWcriTbZKk;
      string IxrrBnkCIX;
      string OQfzxNPbAL;
      string diAEFhbVDh;
      string IUxITgzumL;
      string XIledrqdtU;
      string DAYzGZwmmS;
      string MOyaPtTWeP;
      string NUnnnVwVaM;
      if(tqxdbXETHN == eqnnAIKuCr){qxahdHuxBs = true;}
      else if(eqnnAIKuCr == tqxdbXETHN){DeaELTVyFj = true;}
      if(XQoDICfOjm == IWcriTbZKk){kLHUzIJLPj = true;}
      else if(IWcriTbZKk == XQoDICfOjm){YmxVZEOHrY = true;}
      if(dMtrJmzLsb == IxrrBnkCIX){YTydGiLkKk = true;}
      else if(IxrrBnkCIX == dMtrJmzLsb){pctnUcCOxw = true;}
      if(njPzwCJhaY == OQfzxNPbAL){caMabOnQwH = true;}
      else if(OQfzxNPbAL == njPzwCJhaY){UtqeBpPpTF = true;}
      if(dUnTPgguus == diAEFhbVDh){yVUleCMTof = true;}
      else if(diAEFhbVDh == dUnTPgguus){UVQDectTaG = true;}
      if(GzFLChxEUn == IUxITgzumL){LkGpmWzwau = true;}
      else if(IUxITgzumL == GzFLChxEUn){YaMwdakmih = true;}
      if(XsafZmBoHG == XIledrqdtU){wKmQQKygrj = true;}
      else if(XIledrqdtU == XsafZmBoHG){QHAIOeuRUi = true;}
      if(synKIJYZbc == DAYzGZwmmS){UrOIkDyMzE = true;}
      if(FEQAUodDxO == MOyaPtTWeP){VqueYqTVmE = true;}
      if(FENlBktItc == NUnnnVwVaM){PqpAKniEUU = true;}
      while(DAYzGZwmmS == synKIJYZbc){nXmlDTLqIr = true;}
      while(MOyaPtTWeP == MOyaPtTWeP){himqWsgtAa = true;}
      while(NUnnnVwVaM == NUnnnVwVaM){EcHknNUHnA = true;}
      if(qxahdHuxBs == true){qxahdHuxBs = false;}
      if(kLHUzIJLPj == true){kLHUzIJLPj = false;}
      if(YTydGiLkKk == true){YTydGiLkKk = false;}
      if(caMabOnQwH == true){caMabOnQwH = false;}
      if(yVUleCMTof == true){yVUleCMTof = false;}
      if(LkGpmWzwau == true){LkGpmWzwau = false;}
      if(wKmQQKygrj == true){wKmQQKygrj = false;}
      if(UrOIkDyMzE == true){UrOIkDyMzE = false;}
      if(VqueYqTVmE == true){VqueYqTVmE = false;}
      if(PqpAKniEUU == true){PqpAKniEUU = false;}
      if(DeaELTVyFj == true){DeaELTVyFj = false;}
      if(YmxVZEOHrY == true){YmxVZEOHrY = false;}
      if(pctnUcCOxw == true){pctnUcCOxw = false;}
      if(UtqeBpPpTF == true){UtqeBpPpTF = false;}
      if(UVQDectTaG == true){UVQDectTaG = false;}
      if(YaMwdakmih == true){YaMwdakmih = false;}
      if(QHAIOeuRUi == true){QHAIOeuRUi = false;}
      if(nXmlDTLqIr == true){nXmlDTLqIr = false;}
      if(himqWsgtAa == true){himqWsgtAa = false;}
      if(EcHknNUHnA == true){EcHknNUHnA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class URVHLIHUWO
{ 
  void SSLSdCrRGS()
  { 
      bool pDIEgKWtIF = false;
      bool EfmlOcotOz = false;
      bool dzjBaxMDOi = false;
      bool SBcPgGRzOu = false;
      bool tXPArOQFKd = false;
      bool XtUTHpSHci = false;
      bool xSfYlCDXEH = false;
      bool KofTFGjiJM = false;
      bool gGsjKXgJHq = false;
      bool mKWfyaqpNo = false;
      bool LsACTiOBNB = false;
      bool FiyQCpZwOO = false;
      bool VtPNTASAUd = false;
      bool OtUTAmFpQb = false;
      bool IeuFkELGcH = false;
      bool BubzSRcmiS = false;
      bool POfjlLNdPO = false;
      bool kifmGpyKbP = false;
      bool nMWNcTSVAh = false;
      bool JSHxLtzLSZ = false;
      string MFqoIGBIjg;
      string YTjQwoSuIZ;
      string OEVMliosJG;
      string BignUxhsux;
      string fYZlqSDVui;
      string JXgkWIidCZ;
      string QHzcfplwwz;
      string HYALtoeiUS;
      string eTyZwdBuQL;
      string NDqVfYYwGB;
      string fHZubkXVqg;
      string dAJjtwIZgC;
      string npejkDheeV;
      string QhbSlXtDxK;
      string FfEjhNsGai;
      string PzPENpboKY;
      string DrpUQwXpxW;
      string CFbVwHkuBX;
      string JaDuFQRXFw;
      string uErYHNojSl;
      if(MFqoIGBIjg == fHZubkXVqg){pDIEgKWtIF = true;}
      else if(fHZubkXVqg == MFqoIGBIjg){LsACTiOBNB = true;}
      if(YTjQwoSuIZ == dAJjtwIZgC){EfmlOcotOz = true;}
      else if(dAJjtwIZgC == YTjQwoSuIZ){FiyQCpZwOO = true;}
      if(OEVMliosJG == npejkDheeV){dzjBaxMDOi = true;}
      else if(npejkDheeV == OEVMliosJG){VtPNTASAUd = true;}
      if(BignUxhsux == QhbSlXtDxK){SBcPgGRzOu = true;}
      else if(QhbSlXtDxK == BignUxhsux){OtUTAmFpQb = true;}
      if(fYZlqSDVui == FfEjhNsGai){tXPArOQFKd = true;}
      else if(FfEjhNsGai == fYZlqSDVui){IeuFkELGcH = true;}
      if(JXgkWIidCZ == PzPENpboKY){XtUTHpSHci = true;}
      else if(PzPENpboKY == JXgkWIidCZ){BubzSRcmiS = true;}
      if(QHzcfplwwz == DrpUQwXpxW){xSfYlCDXEH = true;}
      else if(DrpUQwXpxW == QHzcfplwwz){POfjlLNdPO = true;}
      if(HYALtoeiUS == CFbVwHkuBX){KofTFGjiJM = true;}
      if(eTyZwdBuQL == JaDuFQRXFw){gGsjKXgJHq = true;}
      if(NDqVfYYwGB == uErYHNojSl){mKWfyaqpNo = true;}
      while(CFbVwHkuBX == HYALtoeiUS){kifmGpyKbP = true;}
      while(JaDuFQRXFw == JaDuFQRXFw){nMWNcTSVAh = true;}
      while(uErYHNojSl == uErYHNojSl){JSHxLtzLSZ = true;}
      if(pDIEgKWtIF == true){pDIEgKWtIF = false;}
      if(EfmlOcotOz == true){EfmlOcotOz = false;}
      if(dzjBaxMDOi == true){dzjBaxMDOi = false;}
      if(SBcPgGRzOu == true){SBcPgGRzOu = false;}
      if(tXPArOQFKd == true){tXPArOQFKd = false;}
      if(XtUTHpSHci == true){XtUTHpSHci = false;}
      if(xSfYlCDXEH == true){xSfYlCDXEH = false;}
      if(KofTFGjiJM == true){KofTFGjiJM = false;}
      if(gGsjKXgJHq == true){gGsjKXgJHq = false;}
      if(mKWfyaqpNo == true){mKWfyaqpNo = false;}
      if(LsACTiOBNB == true){LsACTiOBNB = false;}
      if(FiyQCpZwOO == true){FiyQCpZwOO = false;}
      if(VtPNTASAUd == true){VtPNTASAUd = false;}
      if(OtUTAmFpQb == true){OtUTAmFpQb = false;}
      if(IeuFkELGcH == true){IeuFkELGcH = false;}
      if(BubzSRcmiS == true){BubzSRcmiS = false;}
      if(POfjlLNdPO == true){POfjlLNdPO = false;}
      if(kifmGpyKbP == true){kifmGpyKbP = false;}
      if(nMWNcTSVAh == true){nMWNcTSVAh = false;}
      if(JSHxLtzLSZ == true){JSHxLtzLSZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LOPDTZYRJE
{ 
  void UCONaixVGp()
  { 
      bool EBmoWCRICq = false;
      bool ycjEHRiLYd = false;
      bool mGNYPXPuZM = false;
      bool CQetOnaQXb = false;
      bool KIfhbogDag = false;
      bool HxRusxnOZy = false;
      bool lVipogyooT = false;
      bool pRnwSdafwa = false;
      bool pMTsEEziBR = false;
      bool ALqYonZprt = false;
      bool qrNHppIUbO = false;
      bool WISyIZBpkj = false;
      bool hOnWSdZOHd = false;
      bool EkmBjyyMCO = false;
      bool wdHltrssQP = false;
      bool mjEIMbDqnL = false;
      bool PtNxKlUQOJ = false;
      bool bomVnEHBbZ = false;
      bool kgxrqUfdoH = false;
      bool tHXqyBPJbI = false;
      string aQPanADDis;
      string kpYjVPMukW;
      string SlGrDkfldR;
      string IelafidqJz;
      string rjBakMQdWQ;
      string EGzkOoKXWC;
      string UQZQkGDxEl;
      string lVkkdijeGp;
      string TCPMNBeBLp;
      string YGTGdaJkpd;
      string JTYkehUOGf;
      string EeQghSBMDj;
      string bCkNNfBeGD;
      string YzocgAcehe;
      string fQtfltomXL;
      string YwgGCGhLWy;
      string gpHDGFonzh;
      string oWeXDLIEaS;
      string pOGudbRiZa;
      string RRHiypJqZg;
      if(aQPanADDis == JTYkehUOGf){EBmoWCRICq = true;}
      else if(JTYkehUOGf == aQPanADDis){qrNHppIUbO = true;}
      if(kpYjVPMukW == EeQghSBMDj){ycjEHRiLYd = true;}
      else if(EeQghSBMDj == kpYjVPMukW){WISyIZBpkj = true;}
      if(SlGrDkfldR == bCkNNfBeGD){mGNYPXPuZM = true;}
      else if(bCkNNfBeGD == SlGrDkfldR){hOnWSdZOHd = true;}
      if(IelafidqJz == YzocgAcehe){CQetOnaQXb = true;}
      else if(YzocgAcehe == IelafidqJz){EkmBjyyMCO = true;}
      if(rjBakMQdWQ == fQtfltomXL){KIfhbogDag = true;}
      else if(fQtfltomXL == rjBakMQdWQ){wdHltrssQP = true;}
      if(EGzkOoKXWC == YwgGCGhLWy){HxRusxnOZy = true;}
      else if(YwgGCGhLWy == EGzkOoKXWC){mjEIMbDqnL = true;}
      if(UQZQkGDxEl == gpHDGFonzh){lVipogyooT = true;}
      else if(gpHDGFonzh == UQZQkGDxEl){PtNxKlUQOJ = true;}
      if(lVkkdijeGp == oWeXDLIEaS){pRnwSdafwa = true;}
      if(TCPMNBeBLp == pOGudbRiZa){pMTsEEziBR = true;}
      if(YGTGdaJkpd == RRHiypJqZg){ALqYonZprt = true;}
      while(oWeXDLIEaS == lVkkdijeGp){bomVnEHBbZ = true;}
      while(pOGudbRiZa == pOGudbRiZa){kgxrqUfdoH = true;}
      while(RRHiypJqZg == RRHiypJqZg){tHXqyBPJbI = true;}
      if(EBmoWCRICq == true){EBmoWCRICq = false;}
      if(ycjEHRiLYd == true){ycjEHRiLYd = false;}
      if(mGNYPXPuZM == true){mGNYPXPuZM = false;}
      if(CQetOnaQXb == true){CQetOnaQXb = false;}
      if(KIfhbogDag == true){KIfhbogDag = false;}
      if(HxRusxnOZy == true){HxRusxnOZy = false;}
      if(lVipogyooT == true){lVipogyooT = false;}
      if(pRnwSdafwa == true){pRnwSdafwa = false;}
      if(pMTsEEziBR == true){pMTsEEziBR = false;}
      if(ALqYonZprt == true){ALqYonZprt = false;}
      if(qrNHppIUbO == true){qrNHppIUbO = false;}
      if(WISyIZBpkj == true){WISyIZBpkj = false;}
      if(hOnWSdZOHd == true){hOnWSdZOHd = false;}
      if(EkmBjyyMCO == true){EkmBjyyMCO = false;}
      if(wdHltrssQP == true){wdHltrssQP = false;}
      if(mjEIMbDqnL == true){mjEIMbDqnL = false;}
      if(PtNxKlUQOJ == true){PtNxKlUQOJ = false;}
      if(bomVnEHBbZ == true){bomVnEHBbZ = false;}
      if(kgxrqUfdoH == true){kgxrqUfdoH = false;}
      if(tHXqyBPJbI == true){tHXqyBPJbI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JXLDPUZXEI
{ 
  void ataKTVEOOr()
  { 
      bool aKJmTkhsfd = false;
      bool WmTzPMmsxf = false;
      bool atyRQyRDpB = false;
      bool PGNEPTVlkf = false;
      bool KYigRSuuXt = false;
      bool AwWgrgLqVU = false;
      bool SdCeOPZPiw = false;
      bool pAIQVBKRAx = false;
      bool DWfuATifLi = false;
      bool HePQMgVESB = false;
      bool seMaEAnGLp = false;
      bool VtqYQwxHet = false;
      bool gsDzoLjqDo = false;
      bool fGzyEXKEqz = false;
      bool fcUVNNmqzQ = false;
      bool iOZXUzbMlr = false;
      bool PwCVJOtrTr = false;
      bool lsPeODYgla = false;
      bool XsqmGRgadE = false;
      bool wxSzjiayLy = false;
      string VbuYIBjwNL;
      string ElcLafBbiP;
      string SVmQhSDfuc;
      string aoKkNTGyqy;
      string BBYsqlUXaS;
      string pfTtHznepo;
      string yEBjjObrxH;
      string ZDkkORxtYw;
      string yfEbmuVPcN;
      string eaIBzxznJc;
      string JcZSsmuifp;
      string CtGsqSzZxn;
      string rLOibyuikQ;
      string RJjumUFlhz;
      string zmjmLkUPJg;
      string yZqUjyOqqt;
      string rLxPYsJKGW;
      string NMrxoFabWq;
      string deYERrRPLn;
      string FOunHmoUNS;
      if(VbuYIBjwNL == JcZSsmuifp){aKJmTkhsfd = true;}
      else if(JcZSsmuifp == VbuYIBjwNL){seMaEAnGLp = true;}
      if(ElcLafBbiP == CtGsqSzZxn){WmTzPMmsxf = true;}
      else if(CtGsqSzZxn == ElcLafBbiP){VtqYQwxHet = true;}
      if(SVmQhSDfuc == rLOibyuikQ){atyRQyRDpB = true;}
      else if(rLOibyuikQ == SVmQhSDfuc){gsDzoLjqDo = true;}
      if(aoKkNTGyqy == RJjumUFlhz){PGNEPTVlkf = true;}
      else if(RJjumUFlhz == aoKkNTGyqy){fGzyEXKEqz = true;}
      if(BBYsqlUXaS == zmjmLkUPJg){KYigRSuuXt = true;}
      else if(zmjmLkUPJg == BBYsqlUXaS){fcUVNNmqzQ = true;}
      if(pfTtHznepo == yZqUjyOqqt){AwWgrgLqVU = true;}
      else if(yZqUjyOqqt == pfTtHznepo){iOZXUzbMlr = true;}
      if(yEBjjObrxH == rLxPYsJKGW){SdCeOPZPiw = true;}
      else if(rLxPYsJKGW == yEBjjObrxH){PwCVJOtrTr = true;}
      if(ZDkkORxtYw == NMrxoFabWq){pAIQVBKRAx = true;}
      if(yfEbmuVPcN == deYERrRPLn){DWfuATifLi = true;}
      if(eaIBzxznJc == FOunHmoUNS){HePQMgVESB = true;}
      while(NMrxoFabWq == ZDkkORxtYw){lsPeODYgla = true;}
      while(deYERrRPLn == deYERrRPLn){XsqmGRgadE = true;}
      while(FOunHmoUNS == FOunHmoUNS){wxSzjiayLy = true;}
      if(aKJmTkhsfd == true){aKJmTkhsfd = false;}
      if(WmTzPMmsxf == true){WmTzPMmsxf = false;}
      if(atyRQyRDpB == true){atyRQyRDpB = false;}
      if(PGNEPTVlkf == true){PGNEPTVlkf = false;}
      if(KYigRSuuXt == true){KYigRSuuXt = false;}
      if(AwWgrgLqVU == true){AwWgrgLqVU = false;}
      if(SdCeOPZPiw == true){SdCeOPZPiw = false;}
      if(pAIQVBKRAx == true){pAIQVBKRAx = false;}
      if(DWfuATifLi == true){DWfuATifLi = false;}
      if(HePQMgVESB == true){HePQMgVESB = false;}
      if(seMaEAnGLp == true){seMaEAnGLp = false;}
      if(VtqYQwxHet == true){VtqYQwxHet = false;}
      if(gsDzoLjqDo == true){gsDzoLjqDo = false;}
      if(fGzyEXKEqz == true){fGzyEXKEqz = false;}
      if(fcUVNNmqzQ == true){fcUVNNmqzQ = false;}
      if(iOZXUzbMlr == true){iOZXUzbMlr = false;}
      if(PwCVJOtrTr == true){PwCVJOtrTr = false;}
      if(lsPeODYgla == true){lsPeODYgla = false;}
      if(XsqmGRgadE == true){XsqmGRgadE = false;}
      if(wxSzjiayLy == true){wxSzjiayLy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class INPZVUBHRS
{ 
  void bkOsNOquSG()
  { 
      bool POASatcnGC = false;
      bool MZYRaMtBek = false;
      bool fkUUhCyLBA = false;
      bool IwODFcqocO = false;
      bool sAxUZqjJic = false;
      bool GBzDUdtejX = false;
      bool wRlFsQLULy = false;
      bool VFXQrenztq = false;
      bool SncXtHxKia = false;
      bool hLFFRbNqbJ = false;
      bool eOykGBciLo = false;
      bool otjsEIoNKk = false;
      bool TBljPJzSyP = false;
      bool QxWkLEoqRs = false;
      bool dOztlmaMAJ = false;
      bool mzfppdcNUw = false;
      bool BKjuXrXzgA = false;
      bool SxwRHFCqyb = false;
      bool hmSocRQfth = false;
      bool bbWUrTdDVs = false;
      string HLnGELpmit;
      string PRJLRUZZDO;
      string NkhmQiXXtx;
      string DjoeejkhjZ;
      string brBFPJIiuA;
      string xUbEBWcApV;
      string nRskpecdgg;
      string irpdmVibWH;
      string ZocsziIjcH;
      string GkqOlJyPPk;
      string feCNQFeyRf;
      string mBdiuyozkG;
      string WsAYayAard;
      string WSMlaulOct;
      string EJSxUEGISm;
      string UzeIOmddmS;
      string EDGnITorIA;
      string LZVqCMaDEV;
      string qqIEIWnDWm;
      string RIbKoBDdoA;
      if(HLnGELpmit == feCNQFeyRf){POASatcnGC = true;}
      else if(feCNQFeyRf == HLnGELpmit){eOykGBciLo = true;}
      if(PRJLRUZZDO == mBdiuyozkG){MZYRaMtBek = true;}
      else if(mBdiuyozkG == PRJLRUZZDO){otjsEIoNKk = true;}
      if(NkhmQiXXtx == WsAYayAard){fkUUhCyLBA = true;}
      else if(WsAYayAard == NkhmQiXXtx){TBljPJzSyP = true;}
      if(DjoeejkhjZ == WSMlaulOct){IwODFcqocO = true;}
      else if(WSMlaulOct == DjoeejkhjZ){QxWkLEoqRs = true;}
      if(brBFPJIiuA == EJSxUEGISm){sAxUZqjJic = true;}
      else if(EJSxUEGISm == brBFPJIiuA){dOztlmaMAJ = true;}
      if(xUbEBWcApV == UzeIOmddmS){GBzDUdtejX = true;}
      else if(UzeIOmddmS == xUbEBWcApV){mzfppdcNUw = true;}
      if(nRskpecdgg == EDGnITorIA){wRlFsQLULy = true;}
      else if(EDGnITorIA == nRskpecdgg){BKjuXrXzgA = true;}
      if(irpdmVibWH == LZVqCMaDEV){VFXQrenztq = true;}
      if(ZocsziIjcH == qqIEIWnDWm){SncXtHxKia = true;}
      if(GkqOlJyPPk == RIbKoBDdoA){hLFFRbNqbJ = true;}
      while(LZVqCMaDEV == irpdmVibWH){SxwRHFCqyb = true;}
      while(qqIEIWnDWm == qqIEIWnDWm){hmSocRQfth = true;}
      while(RIbKoBDdoA == RIbKoBDdoA){bbWUrTdDVs = true;}
      if(POASatcnGC == true){POASatcnGC = false;}
      if(MZYRaMtBek == true){MZYRaMtBek = false;}
      if(fkUUhCyLBA == true){fkUUhCyLBA = false;}
      if(IwODFcqocO == true){IwODFcqocO = false;}
      if(sAxUZqjJic == true){sAxUZqjJic = false;}
      if(GBzDUdtejX == true){GBzDUdtejX = false;}
      if(wRlFsQLULy == true){wRlFsQLULy = false;}
      if(VFXQrenztq == true){VFXQrenztq = false;}
      if(SncXtHxKia == true){SncXtHxKia = false;}
      if(hLFFRbNqbJ == true){hLFFRbNqbJ = false;}
      if(eOykGBciLo == true){eOykGBciLo = false;}
      if(otjsEIoNKk == true){otjsEIoNKk = false;}
      if(TBljPJzSyP == true){TBljPJzSyP = false;}
      if(QxWkLEoqRs == true){QxWkLEoqRs = false;}
      if(dOztlmaMAJ == true){dOztlmaMAJ = false;}
      if(mzfppdcNUw == true){mzfppdcNUw = false;}
      if(BKjuXrXzgA == true){BKjuXrXzgA = false;}
      if(SxwRHFCqyb == true){SxwRHFCqyb = false;}
      if(hmSocRQfth == true){hmSocRQfth = false;}
      if(bbWUrTdDVs == true){bbWUrTdDVs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TNZWZGLMKV
{ 
  void RTRSYuIQmk()
  { 
      bool EAAsfQrWaF = false;
      bool ixBSejTMlD = false;
      bool SmIPiIZTdZ = false;
      bool IpiezmguRr = false;
      bool qzmZxiBqPJ = false;
      bool OVzjtRqkJW = false;
      bool pXrBxrOVTr = false;
      bool CXtsLSAiSA = false;
      bool HiETLmqzkh = false;
      bool uwluCTGkcF = false;
      bool UfXXHpaFXa = false;
      bool QIRJOHTYpK = false;
      bool AOkkwGlzqr = false;
      bool LPGNebLgMU = false;
      bool LlaJQmecft = false;
      bool zhtSEFtlaA = false;
      bool EbNfOBBEdm = false;
      bool wmLVyNnaUI = false;
      bool bJSwrdUnIZ = false;
      bool gYFLPjYtuO = false;
      string rbEgRfumaO;
      string QSWeuTDaib;
      string JhBbfkkNub;
      string WjVSWfjlEt;
      string zdgXPSUzxh;
      string PaohLJacBf;
      string tgqyrgxEIP;
      string jQVobeBcLM;
      string QlPMLutmHM;
      string EGkYzRlhfi;
      string UQphxyFAFf;
      string IyQnPHRelx;
      string lJxwKdfxoJ;
      string rSwcqzwgON;
      string ptgaDGoxIq;
      string AHuixLTsXT;
      string SHKwnpBnwP;
      string LjPYHqbVrE;
      string nhnyJjWNef;
      string fCJuthikmN;
      if(rbEgRfumaO == UQphxyFAFf){EAAsfQrWaF = true;}
      else if(UQphxyFAFf == rbEgRfumaO){UfXXHpaFXa = true;}
      if(QSWeuTDaib == IyQnPHRelx){ixBSejTMlD = true;}
      else if(IyQnPHRelx == QSWeuTDaib){QIRJOHTYpK = true;}
      if(JhBbfkkNub == lJxwKdfxoJ){SmIPiIZTdZ = true;}
      else if(lJxwKdfxoJ == JhBbfkkNub){AOkkwGlzqr = true;}
      if(WjVSWfjlEt == rSwcqzwgON){IpiezmguRr = true;}
      else if(rSwcqzwgON == WjVSWfjlEt){LPGNebLgMU = true;}
      if(zdgXPSUzxh == ptgaDGoxIq){qzmZxiBqPJ = true;}
      else if(ptgaDGoxIq == zdgXPSUzxh){LlaJQmecft = true;}
      if(PaohLJacBf == AHuixLTsXT){OVzjtRqkJW = true;}
      else if(AHuixLTsXT == PaohLJacBf){zhtSEFtlaA = true;}
      if(tgqyrgxEIP == SHKwnpBnwP){pXrBxrOVTr = true;}
      else if(SHKwnpBnwP == tgqyrgxEIP){EbNfOBBEdm = true;}
      if(jQVobeBcLM == LjPYHqbVrE){CXtsLSAiSA = true;}
      if(QlPMLutmHM == nhnyJjWNef){HiETLmqzkh = true;}
      if(EGkYzRlhfi == fCJuthikmN){uwluCTGkcF = true;}
      while(LjPYHqbVrE == jQVobeBcLM){wmLVyNnaUI = true;}
      while(nhnyJjWNef == nhnyJjWNef){bJSwrdUnIZ = true;}
      while(fCJuthikmN == fCJuthikmN){gYFLPjYtuO = true;}
      if(EAAsfQrWaF == true){EAAsfQrWaF = false;}
      if(ixBSejTMlD == true){ixBSejTMlD = false;}
      if(SmIPiIZTdZ == true){SmIPiIZTdZ = false;}
      if(IpiezmguRr == true){IpiezmguRr = false;}
      if(qzmZxiBqPJ == true){qzmZxiBqPJ = false;}
      if(OVzjtRqkJW == true){OVzjtRqkJW = false;}
      if(pXrBxrOVTr == true){pXrBxrOVTr = false;}
      if(CXtsLSAiSA == true){CXtsLSAiSA = false;}
      if(HiETLmqzkh == true){HiETLmqzkh = false;}
      if(uwluCTGkcF == true){uwluCTGkcF = false;}
      if(UfXXHpaFXa == true){UfXXHpaFXa = false;}
      if(QIRJOHTYpK == true){QIRJOHTYpK = false;}
      if(AOkkwGlzqr == true){AOkkwGlzqr = false;}
      if(LPGNebLgMU == true){LPGNebLgMU = false;}
      if(LlaJQmecft == true){LlaJQmecft = false;}
      if(zhtSEFtlaA == true){zhtSEFtlaA = false;}
      if(EbNfOBBEdm == true){EbNfOBBEdm = false;}
      if(wmLVyNnaUI == true){wmLVyNnaUI = false;}
      if(bJSwrdUnIZ == true){bJSwrdUnIZ = false;}
      if(gYFLPjYtuO == true){gYFLPjYtuO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TYTROPVIGD
{ 
  void GUmwwpiMXi()
  { 
      bool IFlKmZeAlD = false;
      bool lFhuXoHTqJ = false;
      bool QRdEyRKFrf = false;
      bool OHwJTjWCuo = false;
      bool OiLYeufTEp = false;
      bool sQPMNqahMU = false;
      bool OYIGndIXam = false;
      bool SEYBuhFFYC = false;
      bool lqBBmyrjwc = false;
      bool JopZZoZFjA = false;
      bool lIrQWnqNRf = false;
      bool kVIJiXXGSo = false;
      bool lYbyddOzbF = false;
      bool HAUYPcyjdy = false;
      bool GeRPrmffpC = false;
      bool RSltONgtms = false;
      bool YrlLXjAjsG = false;
      bool YmbTiGGLGp = false;
      bool xhIYnoOZKC = false;
      bool wExkYNsGqH = false;
      string kKBVpQPrKp;
      string RuzhpBsJQM;
      string AxktkbXrPS;
      string UkicagEgzc;
      string jLQsWolxgL;
      string aErzwnZHkO;
      string rXbrUfLWGI;
      string xMJmcofqWw;
      string oaKEqQrjfm;
      string HwwkkMjYXq;
      string cPpYOOtFWH;
      string HiknZQMXAE;
      string mbqTBAQYCP;
      string FHSeSZklpc;
      string WmNXeYKHKT;
      string AMXTDBXWWN;
      string xVCGCAPFVz;
      string fZhWgAOSob;
      string oINiPsiybR;
      string BNObeBkGVe;
      if(kKBVpQPrKp == cPpYOOtFWH){IFlKmZeAlD = true;}
      else if(cPpYOOtFWH == kKBVpQPrKp){lIrQWnqNRf = true;}
      if(RuzhpBsJQM == HiknZQMXAE){lFhuXoHTqJ = true;}
      else if(HiknZQMXAE == RuzhpBsJQM){kVIJiXXGSo = true;}
      if(AxktkbXrPS == mbqTBAQYCP){QRdEyRKFrf = true;}
      else if(mbqTBAQYCP == AxktkbXrPS){lYbyddOzbF = true;}
      if(UkicagEgzc == FHSeSZklpc){OHwJTjWCuo = true;}
      else if(FHSeSZklpc == UkicagEgzc){HAUYPcyjdy = true;}
      if(jLQsWolxgL == WmNXeYKHKT){OiLYeufTEp = true;}
      else if(WmNXeYKHKT == jLQsWolxgL){GeRPrmffpC = true;}
      if(aErzwnZHkO == AMXTDBXWWN){sQPMNqahMU = true;}
      else if(AMXTDBXWWN == aErzwnZHkO){RSltONgtms = true;}
      if(rXbrUfLWGI == xVCGCAPFVz){OYIGndIXam = true;}
      else if(xVCGCAPFVz == rXbrUfLWGI){YrlLXjAjsG = true;}
      if(xMJmcofqWw == fZhWgAOSob){SEYBuhFFYC = true;}
      if(oaKEqQrjfm == oINiPsiybR){lqBBmyrjwc = true;}
      if(HwwkkMjYXq == BNObeBkGVe){JopZZoZFjA = true;}
      while(fZhWgAOSob == xMJmcofqWw){YmbTiGGLGp = true;}
      while(oINiPsiybR == oINiPsiybR){xhIYnoOZKC = true;}
      while(BNObeBkGVe == BNObeBkGVe){wExkYNsGqH = true;}
      if(IFlKmZeAlD == true){IFlKmZeAlD = false;}
      if(lFhuXoHTqJ == true){lFhuXoHTqJ = false;}
      if(QRdEyRKFrf == true){QRdEyRKFrf = false;}
      if(OHwJTjWCuo == true){OHwJTjWCuo = false;}
      if(OiLYeufTEp == true){OiLYeufTEp = false;}
      if(sQPMNqahMU == true){sQPMNqahMU = false;}
      if(OYIGndIXam == true){OYIGndIXam = false;}
      if(SEYBuhFFYC == true){SEYBuhFFYC = false;}
      if(lqBBmyrjwc == true){lqBBmyrjwc = false;}
      if(JopZZoZFjA == true){JopZZoZFjA = false;}
      if(lIrQWnqNRf == true){lIrQWnqNRf = false;}
      if(kVIJiXXGSo == true){kVIJiXXGSo = false;}
      if(lYbyddOzbF == true){lYbyddOzbF = false;}
      if(HAUYPcyjdy == true){HAUYPcyjdy = false;}
      if(GeRPrmffpC == true){GeRPrmffpC = false;}
      if(RSltONgtms == true){RSltONgtms = false;}
      if(YrlLXjAjsG == true){YrlLXjAjsG = false;}
      if(YmbTiGGLGp == true){YmbTiGGLGp = false;}
      if(xhIYnoOZKC == true){xhIYnoOZKC = false;}
      if(wExkYNsGqH == true){wExkYNsGqH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NUIOBGDNJL
{ 
  void FiPscnhXdF()
  { 
      bool GylQJGtIwV = false;
      bool kutpRlYebx = false;
      bool SNzxWIZgAF = false;
      bool NhPMmLhZTW = false;
      bool fsQyRfLmVR = false;
      bool tOKZysyosA = false;
      bool gMHqIDegCG = false;
      bool DzKERZwAeq = false;
      bool wlLhKzXpNt = false;
      bool MsfSpTkZpO = false;
      bool AejPOuDFHY = false;
      bool wyKCDtBYfJ = false;
      bool enSIsKSrOy = false;
      bool oVKPpRBuTO = false;
      bool uShoxOicOw = false;
      bool RLsgjLMbWE = false;
      bool cKpJiZmtMl = false;
      bool rFFRNMGcLd = false;
      bool bocSfdccfd = false;
      bool FZYPljbXFW = false;
      string rjlfTUABgT;
      string OxMqlwleIm;
      string HNKmtkCHqq;
      string DtySBRihDk;
      string VNTwFSKffT;
      string RxhLIdZzlh;
      string RsKoPUzsoT;
      string NDaWQttOhb;
      string aWaWYGMlKW;
      string rjwVTcDdfj;
      string SRqMGOVKtO;
      string jKQJHuRmPJ;
      string IMiRbcHFCn;
      string pPixJJeOQK;
      string jBrumhSmOY;
      string KPNVbFhYjc;
      string GQIFXUaTAx;
      string PDVFYGUmet;
      string KUqcdZBNUD;
      string aGdnETslXR;
      if(rjlfTUABgT == SRqMGOVKtO){GylQJGtIwV = true;}
      else if(SRqMGOVKtO == rjlfTUABgT){AejPOuDFHY = true;}
      if(OxMqlwleIm == jKQJHuRmPJ){kutpRlYebx = true;}
      else if(jKQJHuRmPJ == OxMqlwleIm){wyKCDtBYfJ = true;}
      if(HNKmtkCHqq == IMiRbcHFCn){SNzxWIZgAF = true;}
      else if(IMiRbcHFCn == HNKmtkCHqq){enSIsKSrOy = true;}
      if(DtySBRihDk == pPixJJeOQK){NhPMmLhZTW = true;}
      else if(pPixJJeOQK == DtySBRihDk){oVKPpRBuTO = true;}
      if(VNTwFSKffT == jBrumhSmOY){fsQyRfLmVR = true;}
      else if(jBrumhSmOY == VNTwFSKffT){uShoxOicOw = true;}
      if(RxhLIdZzlh == KPNVbFhYjc){tOKZysyosA = true;}
      else if(KPNVbFhYjc == RxhLIdZzlh){RLsgjLMbWE = true;}
      if(RsKoPUzsoT == GQIFXUaTAx){gMHqIDegCG = true;}
      else if(GQIFXUaTAx == RsKoPUzsoT){cKpJiZmtMl = true;}
      if(NDaWQttOhb == PDVFYGUmet){DzKERZwAeq = true;}
      if(aWaWYGMlKW == KUqcdZBNUD){wlLhKzXpNt = true;}
      if(rjwVTcDdfj == aGdnETslXR){MsfSpTkZpO = true;}
      while(PDVFYGUmet == NDaWQttOhb){rFFRNMGcLd = true;}
      while(KUqcdZBNUD == KUqcdZBNUD){bocSfdccfd = true;}
      while(aGdnETslXR == aGdnETslXR){FZYPljbXFW = true;}
      if(GylQJGtIwV == true){GylQJGtIwV = false;}
      if(kutpRlYebx == true){kutpRlYebx = false;}
      if(SNzxWIZgAF == true){SNzxWIZgAF = false;}
      if(NhPMmLhZTW == true){NhPMmLhZTW = false;}
      if(fsQyRfLmVR == true){fsQyRfLmVR = false;}
      if(tOKZysyosA == true){tOKZysyosA = false;}
      if(gMHqIDegCG == true){gMHqIDegCG = false;}
      if(DzKERZwAeq == true){DzKERZwAeq = false;}
      if(wlLhKzXpNt == true){wlLhKzXpNt = false;}
      if(MsfSpTkZpO == true){MsfSpTkZpO = false;}
      if(AejPOuDFHY == true){AejPOuDFHY = false;}
      if(wyKCDtBYfJ == true){wyKCDtBYfJ = false;}
      if(enSIsKSrOy == true){enSIsKSrOy = false;}
      if(oVKPpRBuTO == true){oVKPpRBuTO = false;}
      if(uShoxOicOw == true){uShoxOicOw = false;}
      if(RLsgjLMbWE == true){RLsgjLMbWE = false;}
      if(cKpJiZmtMl == true){cKpJiZmtMl = false;}
      if(rFFRNMGcLd == true){rFFRNMGcLd = false;}
      if(bocSfdccfd == true){bocSfdccfd = false;}
      if(FZYPljbXFW == true){FZYPljbXFW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EOLUUFRXML
{ 
  void UdwaNbwclO()
  { 
      bool CuRyIKtrRP = false;
      bool OmbsIDpwYA = false;
      bool DZtZqrIYcL = false;
      bool yDlzllTElk = false;
      bool LMLTZjAFHa = false;
      bool rlspHbBqGQ = false;
      bool CVPGRKAbHV = false;
      bool ilJnoqNZAH = false;
      bool qDQCTLKwqJ = false;
      bool kbxVhoxFBP = false;
      bool iYxkqFcEAQ = false;
      bool NaqzZzEMlG = false;
      bool zEjyjGnnFz = false;
      bool sIYjXRFeKN = false;
      bool iFuZuKkywi = false;
      bool jjSuQenzBj = false;
      bool RnzBXFBGaH = false;
      bool sYCYWsJKCZ = false;
      bool VprVOIpcTs = false;
      bool dFdautGtCp = false;
      string tjZESlQmZk;
      string pEhnHNRXVQ;
      string CDRhunRXnY;
      string atXNYPZcsh;
      string xfZszbKiRj;
      string wnDBTpRqIe;
      string TszBJwgUOq;
      string nnemSWcYhT;
      string ciFDblpWth;
      string yhUONEfYiC;
      string upTZwIJQiw;
      string NsJnBjmwZW;
      string GJZfsGSPYN;
      string pEpfYmPfGS;
      string bZmxUFYgMd;
      string RjyMwkPmgp;
      string otqUGJDcOO;
      string UGoGtfWcLn;
      string hlDuuGFcin;
      string WcyQdhhSpL;
      if(tjZESlQmZk == upTZwIJQiw){CuRyIKtrRP = true;}
      else if(upTZwIJQiw == tjZESlQmZk){iYxkqFcEAQ = true;}
      if(pEhnHNRXVQ == NsJnBjmwZW){OmbsIDpwYA = true;}
      else if(NsJnBjmwZW == pEhnHNRXVQ){NaqzZzEMlG = true;}
      if(CDRhunRXnY == GJZfsGSPYN){DZtZqrIYcL = true;}
      else if(GJZfsGSPYN == CDRhunRXnY){zEjyjGnnFz = true;}
      if(atXNYPZcsh == pEpfYmPfGS){yDlzllTElk = true;}
      else if(pEpfYmPfGS == atXNYPZcsh){sIYjXRFeKN = true;}
      if(xfZszbKiRj == bZmxUFYgMd){LMLTZjAFHa = true;}
      else if(bZmxUFYgMd == xfZszbKiRj){iFuZuKkywi = true;}
      if(wnDBTpRqIe == RjyMwkPmgp){rlspHbBqGQ = true;}
      else if(RjyMwkPmgp == wnDBTpRqIe){jjSuQenzBj = true;}
      if(TszBJwgUOq == otqUGJDcOO){CVPGRKAbHV = true;}
      else if(otqUGJDcOO == TszBJwgUOq){RnzBXFBGaH = true;}
      if(nnemSWcYhT == UGoGtfWcLn){ilJnoqNZAH = true;}
      if(ciFDblpWth == hlDuuGFcin){qDQCTLKwqJ = true;}
      if(yhUONEfYiC == WcyQdhhSpL){kbxVhoxFBP = true;}
      while(UGoGtfWcLn == nnemSWcYhT){sYCYWsJKCZ = true;}
      while(hlDuuGFcin == hlDuuGFcin){VprVOIpcTs = true;}
      while(WcyQdhhSpL == WcyQdhhSpL){dFdautGtCp = true;}
      if(CuRyIKtrRP == true){CuRyIKtrRP = false;}
      if(OmbsIDpwYA == true){OmbsIDpwYA = false;}
      if(DZtZqrIYcL == true){DZtZqrIYcL = false;}
      if(yDlzllTElk == true){yDlzllTElk = false;}
      if(LMLTZjAFHa == true){LMLTZjAFHa = false;}
      if(rlspHbBqGQ == true){rlspHbBqGQ = false;}
      if(CVPGRKAbHV == true){CVPGRKAbHV = false;}
      if(ilJnoqNZAH == true){ilJnoqNZAH = false;}
      if(qDQCTLKwqJ == true){qDQCTLKwqJ = false;}
      if(kbxVhoxFBP == true){kbxVhoxFBP = false;}
      if(iYxkqFcEAQ == true){iYxkqFcEAQ = false;}
      if(NaqzZzEMlG == true){NaqzZzEMlG = false;}
      if(zEjyjGnnFz == true){zEjyjGnnFz = false;}
      if(sIYjXRFeKN == true){sIYjXRFeKN = false;}
      if(iFuZuKkywi == true){iFuZuKkywi = false;}
      if(jjSuQenzBj == true){jjSuQenzBj = false;}
      if(RnzBXFBGaH == true){RnzBXFBGaH = false;}
      if(sYCYWsJKCZ == true){sYCYWsJKCZ = false;}
      if(VprVOIpcTs == true){VprVOIpcTs = false;}
      if(dFdautGtCp == true){dFdautGtCp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZACULDCZAW
{ 
  void dLAeiyBGWJ()
  { 
      bool SLGkXqPets = false;
      bool cNGNLeoWZO = false;
      bool msteMpwhOO = false;
      bool OjmHxycTmD = false;
      bool mNIQUorNMB = false;
      bool UZFsuYQaXh = false;
      bool tgQfesayPN = false;
      bool BUjVaZkdJX = false;
      bool yiVNsndtMY = false;
      bool gBwEIFxckb = false;
      bool OsxyzzpiRU = false;
      bool nmRzjLLClq = false;
      bool OflqgAYeMU = false;
      bool cHrhJEkWNs = false;
      bool xtbqktjwUx = false;
      bool ttptMhGGRz = false;
      bool aLWxrftipe = false;
      bool ZnorsTDuFl = false;
      bool PbJPZiRyUa = false;
      bool xeFOSlXeyF = false;
      string lNSYOMasrO;
      string uIhMSgscMn;
      string JHjkFxYhBc;
      string kRMArJTXtm;
      string kNbVYEJYSK;
      string ChfgkddgTQ;
      string mrqOccuhUJ;
      string NViYCufNLA;
      string nAOqaCleON;
      string elDcArWNsw;
      string JbDIwgzGep;
      string yQUTbldAna;
      string qQSGeaSFYJ;
      string YRUPqLwFts;
      string DeAXPOQiAN;
      string OVYRFsIxdV;
      string NshUQfwFcP;
      string oXGtXLPtqP;
      string JiEKtCrCKy;
      string DzaXfJxfHi;
      if(lNSYOMasrO == JbDIwgzGep){SLGkXqPets = true;}
      else if(JbDIwgzGep == lNSYOMasrO){OsxyzzpiRU = true;}
      if(uIhMSgscMn == yQUTbldAna){cNGNLeoWZO = true;}
      else if(yQUTbldAna == uIhMSgscMn){nmRzjLLClq = true;}
      if(JHjkFxYhBc == qQSGeaSFYJ){msteMpwhOO = true;}
      else if(qQSGeaSFYJ == JHjkFxYhBc){OflqgAYeMU = true;}
      if(kRMArJTXtm == YRUPqLwFts){OjmHxycTmD = true;}
      else if(YRUPqLwFts == kRMArJTXtm){cHrhJEkWNs = true;}
      if(kNbVYEJYSK == DeAXPOQiAN){mNIQUorNMB = true;}
      else if(DeAXPOQiAN == kNbVYEJYSK){xtbqktjwUx = true;}
      if(ChfgkddgTQ == OVYRFsIxdV){UZFsuYQaXh = true;}
      else if(OVYRFsIxdV == ChfgkddgTQ){ttptMhGGRz = true;}
      if(mrqOccuhUJ == NshUQfwFcP){tgQfesayPN = true;}
      else if(NshUQfwFcP == mrqOccuhUJ){aLWxrftipe = true;}
      if(NViYCufNLA == oXGtXLPtqP){BUjVaZkdJX = true;}
      if(nAOqaCleON == JiEKtCrCKy){yiVNsndtMY = true;}
      if(elDcArWNsw == DzaXfJxfHi){gBwEIFxckb = true;}
      while(oXGtXLPtqP == NViYCufNLA){ZnorsTDuFl = true;}
      while(JiEKtCrCKy == JiEKtCrCKy){PbJPZiRyUa = true;}
      while(DzaXfJxfHi == DzaXfJxfHi){xeFOSlXeyF = true;}
      if(SLGkXqPets == true){SLGkXqPets = false;}
      if(cNGNLeoWZO == true){cNGNLeoWZO = false;}
      if(msteMpwhOO == true){msteMpwhOO = false;}
      if(OjmHxycTmD == true){OjmHxycTmD = false;}
      if(mNIQUorNMB == true){mNIQUorNMB = false;}
      if(UZFsuYQaXh == true){UZFsuYQaXh = false;}
      if(tgQfesayPN == true){tgQfesayPN = false;}
      if(BUjVaZkdJX == true){BUjVaZkdJX = false;}
      if(yiVNsndtMY == true){yiVNsndtMY = false;}
      if(gBwEIFxckb == true){gBwEIFxckb = false;}
      if(OsxyzzpiRU == true){OsxyzzpiRU = false;}
      if(nmRzjLLClq == true){nmRzjLLClq = false;}
      if(OflqgAYeMU == true){OflqgAYeMU = false;}
      if(cHrhJEkWNs == true){cHrhJEkWNs = false;}
      if(xtbqktjwUx == true){xtbqktjwUx = false;}
      if(ttptMhGGRz == true){ttptMhGGRz = false;}
      if(aLWxrftipe == true){aLWxrftipe = false;}
      if(ZnorsTDuFl == true){ZnorsTDuFl = false;}
      if(PbJPZiRyUa == true){PbJPZiRyUa = false;}
      if(xeFOSlXeyF == true){xeFOSlXeyF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WEBFWPVGDT
{ 
  void fSVJSzzygl()
  { 
      bool bGDREtRIOR = false;
      bool QxsFBrIFfh = false;
      bool GNtBqpEUOW = false;
      bool BhjGkcmzLM = false;
      bool NmTZBofgUb = false;
      bool aqJlXOLCZN = false;
      bool pwtrQhMlTX = false;
      bool EJtTUTsTzC = false;
      bool KWAluJYyiW = false;
      bool RkYxVRraJT = false;
      bool bsNwXRxpRD = false;
      bool UqDXCTuHwG = false;
      bool IOCxGTjwxC = false;
      bool aSKeZRJEOd = false;
      bool MifeCZhBuC = false;
      bool VjeCLNpQpE = false;
      bool hArOcCfXxk = false;
      bool JqsRtYhXtg = false;
      bool kiAtgpmISM = false;
      bool asNKwLpRCA = false;
      string cptLwFcWob;
      string lZKLawamfT;
      string UZwIqykVDF;
      string LzQjXRbQMI;
      string pZLDTwRjMh;
      string GNcIyCskUy;
      string UGSjPmIZmI;
      string TKaXcuNrot;
      string fAJUyyWIlU;
      string XpwNniGbnf;
      string nqxDOwmEfC;
      string nAwZSTxxkR;
      string PznRkdNMjs;
      string nlEIGoDFGC;
      string KRbigXtWuT;
      string lIqVQnCeSk;
      string iaUmNCumTc;
      string PqqhGyXFkM;
      string jqRPGfuhrR;
      string lYmVTjwoUd;
      if(cptLwFcWob == nqxDOwmEfC){bGDREtRIOR = true;}
      else if(nqxDOwmEfC == cptLwFcWob){bsNwXRxpRD = true;}
      if(lZKLawamfT == nAwZSTxxkR){QxsFBrIFfh = true;}
      else if(nAwZSTxxkR == lZKLawamfT){UqDXCTuHwG = true;}
      if(UZwIqykVDF == PznRkdNMjs){GNtBqpEUOW = true;}
      else if(PznRkdNMjs == UZwIqykVDF){IOCxGTjwxC = true;}
      if(LzQjXRbQMI == nlEIGoDFGC){BhjGkcmzLM = true;}
      else if(nlEIGoDFGC == LzQjXRbQMI){aSKeZRJEOd = true;}
      if(pZLDTwRjMh == KRbigXtWuT){NmTZBofgUb = true;}
      else if(KRbigXtWuT == pZLDTwRjMh){MifeCZhBuC = true;}
      if(GNcIyCskUy == lIqVQnCeSk){aqJlXOLCZN = true;}
      else if(lIqVQnCeSk == GNcIyCskUy){VjeCLNpQpE = true;}
      if(UGSjPmIZmI == iaUmNCumTc){pwtrQhMlTX = true;}
      else if(iaUmNCumTc == UGSjPmIZmI){hArOcCfXxk = true;}
      if(TKaXcuNrot == PqqhGyXFkM){EJtTUTsTzC = true;}
      if(fAJUyyWIlU == jqRPGfuhrR){KWAluJYyiW = true;}
      if(XpwNniGbnf == lYmVTjwoUd){RkYxVRraJT = true;}
      while(PqqhGyXFkM == TKaXcuNrot){JqsRtYhXtg = true;}
      while(jqRPGfuhrR == jqRPGfuhrR){kiAtgpmISM = true;}
      while(lYmVTjwoUd == lYmVTjwoUd){asNKwLpRCA = true;}
      if(bGDREtRIOR == true){bGDREtRIOR = false;}
      if(QxsFBrIFfh == true){QxsFBrIFfh = false;}
      if(GNtBqpEUOW == true){GNtBqpEUOW = false;}
      if(BhjGkcmzLM == true){BhjGkcmzLM = false;}
      if(NmTZBofgUb == true){NmTZBofgUb = false;}
      if(aqJlXOLCZN == true){aqJlXOLCZN = false;}
      if(pwtrQhMlTX == true){pwtrQhMlTX = false;}
      if(EJtTUTsTzC == true){EJtTUTsTzC = false;}
      if(KWAluJYyiW == true){KWAluJYyiW = false;}
      if(RkYxVRraJT == true){RkYxVRraJT = false;}
      if(bsNwXRxpRD == true){bsNwXRxpRD = false;}
      if(UqDXCTuHwG == true){UqDXCTuHwG = false;}
      if(IOCxGTjwxC == true){IOCxGTjwxC = false;}
      if(aSKeZRJEOd == true){aSKeZRJEOd = false;}
      if(MifeCZhBuC == true){MifeCZhBuC = false;}
      if(VjeCLNpQpE == true){VjeCLNpQpE = false;}
      if(hArOcCfXxk == true){hArOcCfXxk = false;}
      if(JqsRtYhXtg == true){JqsRtYhXtg = false;}
      if(kiAtgpmISM == true){kiAtgpmISM = false;}
      if(asNKwLpRCA == true){asNKwLpRCA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJVDPSXQZQ
{ 
  void FuVPcPEYuy()
  { 
      bool tcVSemUQfx = false;
      bool wNSmcpihGx = false;
      bool FcwpYWrdKf = false;
      bool jLTZDaFJKs = false;
      bool glbCBMjkby = false;
      bool clDMzRfesH = false;
      bool tqFAMjssjC = false;
      bool kZXNQSAsoL = false;
      bool mHBMDyIGZk = false;
      bool taPCyogbpQ = false;
      bool TpAYNDOowg = false;
      bool QmphUmpswN = false;
      bool blTzIKKVOa = false;
      bool kYCYqwGbzz = false;
      bool jSJrTHkggL = false;
      bool znecohWBQD = false;
      bool ssaVurkQpY = false;
      bool fNsxdIbaeB = false;
      bool ZcnCaxsZiJ = false;
      bool YFKwGqqnwa = false;
      string soAdEjSUVu;
      string CzKsQTPbVx;
      string XaACZmRRDH;
      string GxKEJnURAx;
      string gqjdCYmZrH;
      string zfoomSoyEQ;
      string RAQNoEnGjc;
      string yybYQgpVzA;
      string zqYuHZIVQp;
      string zWNiefZVny;
      string kgpPIBDQYG;
      string cSyDRaaVFO;
      string wSosdbjssk;
      string GThBPSAJlF;
      string WqxKNfYJRE;
      string EEQYBRrxkg;
      string RKWmzIkwnz;
      string ZQizrEVeex;
      string DabofCDIzx;
      string ZCYFnLTJKF;
      if(soAdEjSUVu == kgpPIBDQYG){tcVSemUQfx = true;}
      else if(kgpPIBDQYG == soAdEjSUVu){TpAYNDOowg = true;}
      if(CzKsQTPbVx == cSyDRaaVFO){wNSmcpihGx = true;}
      else if(cSyDRaaVFO == CzKsQTPbVx){QmphUmpswN = true;}
      if(XaACZmRRDH == wSosdbjssk){FcwpYWrdKf = true;}
      else if(wSosdbjssk == XaACZmRRDH){blTzIKKVOa = true;}
      if(GxKEJnURAx == GThBPSAJlF){jLTZDaFJKs = true;}
      else if(GThBPSAJlF == GxKEJnURAx){kYCYqwGbzz = true;}
      if(gqjdCYmZrH == WqxKNfYJRE){glbCBMjkby = true;}
      else if(WqxKNfYJRE == gqjdCYmZrH){jSJrTHkggL = true;}
      if(zfoomSoyEQ == EEQYBRrxkg){clDMzRfesH = true;}
      else if(EEQYBRrxkg == zfoomSoyEQ){znecohWBQD = true;}
      if(RAQNoEnGjc == RKWmzIkwnz){tqFAMjssjC = true;}
      else if(RKWmzIkwnz == RAQNoEnGjc){ssaVurkQpY = true;}
      if(yybYQgpVzA == ZQizrEVeex){kZXNQSAsoL = true;}
      if(zqYuHZIVQp == DabofCDIzx){mHBMDyIGZk = true;}
      if(zWNiefZVny == ZCYFnLTJKF){taPCyogbpQ = true;}
      while(ZQizrEVeex == yybYQgpVzA){fNsxdIbaeB = true;}
      while(DabofCDIzx == DabofCDIzx){ZcnCaxsZiJ = true;}
      while(ZCYFnLTJKF == ZCYFnLTJKF){YFKwGqqnwa = true;}
      if(tcVSemUQfx == true){tcVSemUQfx = false;}
      if(wNSmcpihGx == true){wNSmcpihGx = false;}
      if(FcwpYWrdKf == true){FcwpYWrdKf = false;}
      if(jLTZDaFJKs == true){jLTZDaFJKs = false;}
      if(glbCBMjkby == true){glbCBMjkby = false;}
      if(clDMzRfesH == true){clDMzRfesH = false;}
      if(tqFAMjssjC == true){tqFAMjssjC = false;}
      if(kZXNQSAsoL == true){kZXNQSAsoL = false;}
      if(mHBMDyIGZk == true){mHBMDyIGZk = false;}
      if(taPCyogbpQ == true){taPCyogbpQ = false;}
      if(TpAYNDOowg == true){TpAYNDOowg = false;}
      if(QmphUmpswN == true){QmphUmpswN = false;}
      if(blTzIKKVOa == true){blTzIKKVOa = false;}
      if(kYCYqwGbzz == true){kYCYqwGbzz = false;}
      if(jSJrTHkggL == true){jSJrTHkggL = false;}
      if(znecohWBQD == true){znecohWBQD = false;}
      if(ssaVurkQpY == true){ssaVurkQpY = false;}
      if(fNsxdIbaeB == true){fNsxdIbaeB = false;}
      if(ZcnCaxsZiJ == true){ZcnCaxsZiJ = false;}
      if(YFKwGqqnwa == true){YFKwGqqnwa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TRAPDCVPQY
{ 
  void LqDppolNkP()
  { 
      bool jMdLGwbzbs = false;
      bool XEzpmtoXcr = false;
      bool hUYOJQXApM = false;
      bool QSZckaUWtR = false;
      bool qVogVFppFZ = false;
      bool fYGVIPmPCp = false;
      bool YaJObFdVEM = false;
      bool ZRcKAMerrD = false;
      bool ZgtQgrMEUU = false;
      bool nEUEsQMaEQ = false;
      bool aTlszNuuUu = false;
      bool ktXyPqfrgj = false;
      bool rYBiXUxYRj = false;
      bool zDmacGuAQS = false;
      bool wQiYjsgVnB = false;
      bool jTsUXBSCVe = false;
      bool QWdkwgGxVJ = false;
      bool uebOmbobze = false;
      bool najPzfJSCa = false;
      bool msekCZmycC = false;
      string IjPGmbbYru;
      string jZqVprbBZI;
      string TLIJzGUgOa;
      string loJCbMzYji;
      string stytkWuciT;
      string iFeXbxbFGg;
      string GuJQItQotd;
      string sDRpPZNNYb;
      string KrxurgKkae;
      string ksRCbyjhlq;
      string GGiFaemnIB;
      string jNgeWOxOXb;
      string jeNOszlOOQ;
      string ofbgVDIrTN;
      string sVbZuWMmfM;
      string BVJJGasTLa;
      string sXZrLElzIT;
      string FEtKhNCnTV;
      string myiBOTVRZt;
      string KofsTUwjNp;
      if(IjPGmbbYru == GGiFaemnIB){jMdLGwbzbs = true;}
      else if(GGiFaemnIB == IjPGmbbYru){aTlszNuuUu = true;}
      if(jZqVprbBZI == jNgeWOxOXb){XEzpmtoXcr = true;}
      else if(jNgeWOxOXb == jZqVprbBZI){ktXyPqfrgj = true;}
      if(TLIJzGUgOa == jeNOszlOOQ){hUYOJQXApM = true;}
      else if(jeNOszlOOQ == TLIJzGUgOa){rYBiXUxYRj = true;}
      if(loJCbMzYji == ofbgVDIrTN){QSZckaUWtR = true;}
      else if(ofbgVDIrTN == loJCbMzYji){zDmacGuAQS = true;}
      if(stytkWuciT == sVbZuWMmfM){qVogVFppFZ = true;}
      else if(sVbZuWMmfM == stytkWuciT){wQiYjsgVnB = true;}
      if(iFeXbxbFGg == BVJJGasTLa){fYGVIPmPCp = true;}
      else if(BVJJGasTLa == iFeXbxbFGg){jTsUXBSCVe = true;}
      if(GuJQItQotd == sXZrLElzIT){YaJObFdVEM = true;}
      else if(sXZrLElzIT == GuJQItQotd){QWdkwgGxVJ = true;}
      if(sDRpPZNNYb == FEtKhNCnTV){ZRcKAMerrD = true;}
      if(KrxurgKkae == myiBOTVRZt){ZgtQgrMEUU = true;}
      if(ksRCbyjhlq == KofsTUwjNp){nEUEsQMaEQ = true;}
      while(FEtKhNCnTV == sDRpPZNNYb){uebOmbobze = true;}
      while(myiBOTVRZt == myiBOTVRZt){najPzfJSCa = true;}
      while(KofsTUwjNp == KofsTUwjNp){msekCZmycC = true;}
      if(jMdLGwbzbs == true){jMdLGwbzbs = false;}
      if(XEzpmtoXcr == true){XEzpmtoXcr = false;}
      if(hUYOJQXApM == true){hUYOJQXApM = false;}
      if(QSZckaUWtR == true){QSZckaUWtR = false;}
      if(qVogVFppFZ == true){qVogVFppFZ = false;}
      if(fYGVIPmPCp == true){fYGVIPmPCp = false;}
      if(YaJObFdVEM == true){YaJObFdVEM = false;}
      if(ZRcKAMerrD == true){ZRcKAMerrD = false;}
      if(ZgtQgrMEUU == true){ZgtQgrMEUU = false;}
      if(nEUEsQMaEQ == true){nEUEsQMaEQ = false;}
      if(aTlszNuuUu == true){aTlszNuuUu = false;}
      if(ktXyPqfrgj == true){ktXyPqfrgj = false;}
      if(rYBiXUxYRj == true){rYBiXUxYRj = false;}
      if(zDmacGuAQS == true){zDmacGuAQS = false;}
      if(wQiYjsgVnB == true){wQiYjsgVnB = false;}
      if(jTsUXBSCVe == true){jTsUXBSCVe = false;}
      if(QWdkwgGxVJ == true){QWdkwgGxVJ = false;}
      if(uebOmbobze == true){uebOmbobze = false;}
      if(najPzfJSCa == true){najPzfJSCa = false;}
      if(msekCZmycC == true){msekCZmycC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SQNPLUETWH
{ 
  void SNjEgmDCDF()
  { 
      bool YuASDoMHEx = false;
      bool LdsabeorBG = false;
      bool LjfeRzJLER = false;
      bool kVlmLoDDjz = false;
      bool ReURxEygkA = false;
      bool bmHCQnOVBE = false;
      bool fBDlMoqFOl = false;
      bool akHCofPOhM = false;
      bool AcZEoxOiWX = false;
      bool ahCfSPbhFH = false;
      bool MsSzYpeENj = false;
      bool XznnDCayxO = false;
      bool aHipKsibiY = false;
      bool EgJZAHKaey = false;
      bool RJVlzatNbQ = false;
      bool ockpgEJbnf = false;
      bool HDUnfqpNnw = false;
      bool rATywRlwqi = false;
      bool yUzSjawTsu = false;
      bool xhlzqOngGI = false;
      string IkOFHjrKke;
      string JejCPHDPsW;
      string xHBRActFxs;
      string pGPxGpNgDa;
      string fxjouhEuFh;
      string AMfdBBjwEe;
      string plMroDPmwZ;
      string sVMSpAWMVR;
      string XzzOscZlwF;
      string GRbXktjqzr;
      string SQzfodANmB;
      string dWZmGqlyzL;
      string ccqpTbtnhw;
      string PeMdyHATZO;
      string cLzuaiqoRt;
      string HkrmOoZILM;
      string jLfpkyJwnz;
      string pRYjiQdwPk;
      string kEWmndmYPI;
      string hqIMeQfIJb;
      if(IkOFHjrKke == SQzfodANmB){YuASDoMHEx = true;}
      else if(SQzfodANmB == IkOFHjrKke){MsSzYpeENj = true;}
      if(JejCPHDPsW == dWZmGqlyzL){LdsabeorBG = true;}
      else if(dWZmGqlyzL == JejCPHDPsW){XznnDCayxO = true;}
      if(xHBRActFxs == ccqpTbtnhw){LjfeRzJLER = true;}
      else if(ccqpTbtnhw == xHBRActFxs){aHipKsibiY = true;}
      if(pGPxGpNgDa == PeMdyHATZO){kVlmLoDDjz = true;}
      else if(PeMdyHATZO == pGPxGpNgDa){EgJZAHKaey = true;}
      if(fxjouhEuFh == cLzuaiqoRt){ReURxEygkA = true;}
      else if(cLzuaiqoRt == fxjouhEuFh){RJVlzatNbQ = true;}
      if(AMfdBBjwEe == HkrmOoZILM){bmHCQnOVBE = true;}
      else if(HkrmOoZILM == AMfdBBjwEe){ockpgEJbnf = true;}
      if(plMroDPmwZ == jLfpkyJwnz){fBDlMoqFOl = true;}
      else if(jLfpkyJwnz == plMroDPmwZ){HDUnfqpNnw = true;}
      if(sVMSpAWMVR == pRYjiQdwPk){akHCofPOhM = true;}
      if(XzzOscZlwF == kEWmndmYPI){AcZEoxOiWX = true;}
      if(GRbXktjqzr == hqIMeQfIJb){ahCfSPbhFH = true;}
      while(pRYjiQdwPk == sVMSpAWMVR){rATywRlwqi = true;}
      while(kEWmndmYPI == kEWmndmYPI){yUzSjawTsu = true;}
      while(hqIMeQfIJb == hqIMeQfIJb){xhlzqOngGI = true;}
      if(YuASDoMHEx == true){YuASDoMHEx = false;}
      if(LdsabeorBG == true){LdsabeorBG = false;}
      if(LjfeRzJLER == true){LjfeRzJLER = false;}
      if(kVlmLoDDjz == true){kVlmLoDDjz = false;}
      if(ReURxEygkA == true){ReURxEygkA = false;}
      if(bmHCQnOVBE == true){bmHCQnOVBE = false;}
      if(fBDlMoqFOl == true){fBDlMoqFOl = false;}
      if(akHCofPOhM == true){akHCofPOhM = false;}
      if(AcZEoxOiWX == true){AcZEoxOiWX = false;}
      if(ahCfSPbhFH == true){ahCfSPbhFH = false;}
      if(MsSzYpeENj == true){MsSzYpeENj = false;}
      if(XznnDCayxO == true){XznnDCayxO = false;}
      if(aHipKsibiY == true){aHipKsibiY = false;}
      if(EgJZAHKaey == true){EgJZAHKaey = false;}
      if(RJVlzatNbQ == true){RJVlzatNbQ = false;}
      if(ockpgEJbnf == true){ockpgEJbnf = false;}
      if(HDUnfqpNnw == true){HDUnfqpNnw = false;}
      if(rATywRlwqi == true){rATywRlwqi = false;}
      if(yUzSjawTsu == true){yUzSjawTsu = false;}
      if(xhlzqOngGI == true){xhlzqOngGI = false;}
    } 
}; 
