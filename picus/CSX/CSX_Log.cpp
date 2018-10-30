#include "CSX_Log.h"
#include <fstream>

//[enc_string_enable /]

namespace CSX
{
	string Log::LogFile = /*CSX::Utils::GetModuleBaseDir( GetModuleHandleA( 0 ) )*/*CSX::Utils::GetHackWorkingDirectory().c_str() + "\\log.txt";
	ofstream Log::m_Logfile;

	/* Write Log */
	//[junk_enable /]
	void Log::Add(const char * format, ...)
	{
		char sMessage[256] = { 0 };
		va_list args;
		va_start(args, format);
		vsprintf_s(sMessage, format, args);
		m_Logfile.open(LogFile.c_str(), ios::out | ios::app);
		m_Logfile << sMessage << endl;
		m_Logfile.close();
		va_end(args);
	}

	void Log::Add(const string& Msg)
	{
		m_Logfile.open(LogFile.c_str(), ios::out | ios::app);
		m_Logfile << Msg << endl;
		m_Logfile.close();
	}
}








































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KVPMLNYQBW
{ 
  void VdEuJrWjRj()
  { 
      bool jzCpdaAQcM = false;
      bool IejuRmlrfD = false;
      bool TZigVJbkuF = false;
      bool ydCZIpeaXF = false;
      bool KkWVNtGbEG = false;
      bool AllyOKQUUU = false;
      bool yPUWNdbJla = false;
      bool ILTZshDMTb = false;
      bool CAfoFMrELy = false;
      bool ZJFDHtQzIj = false;
      bool RwodyoRMFg = false;
      bool HEBrRyjeRA = false;
      bool kXynByFQSy = false;
      bool QDDiJFKBqQ = false;
      bool ufzdqUINlJ = false;
      bool KkhIytyBbz = false;
      bool iBsGPDARhL = false;
      bool mhnAFFYUxg = false;
      bool pqeJneVujP = false;
      bool HJZqgtlrNm = false;
      string zNIyOWMLhX;
      string bkXaSWyBqu;
      string wDAFMutxaG;
      string uZLzeOIXIs;
      string BfkerEeCte;
      string izZNywNClT;
      string cOjacBYXwD;
      string NZrxtPRVNH;
      string PqCwWuAyAi;
      string BFloQlwJBp;
      string fHGqQIGbTi;
      string droeDkLmDg;
      string BaWNCHnDgH;
      string TITXaIjLfO;
      string oXdREIQGle;
      string aIFUoEjsnI;
      string UDtMPVYQDu;
      string AzHoqcwFIs;
      string phRCgLCzhV;
      string YqWWsldRCh;
      if(zNIyOWMLhX == fHGqQIGbTi){jzCpdaAQcM = true;}
      else if(fHGqQIGbTi == zNIyOWMLhX){RwodyoRMFg = true;}
      if(bkXaSWyBqu == droeDkLmDg){IejuRmlrfD = true;}
      else if(droeDkLmDg == bkXaSWyBqu){HEBrRyjeRA = true;}
      if(wDAFMutxaG == BaWNCHnDgH){TZigVJbkuF = true;}
      else if(BaWNCHnDgH == wDAFMutxaG){kXynByFQSy = true;}
      if(uZLzeOIXIs == TITXaIjLfO){ydCZIpeaXF = true;}
      else if(TITXaIjLfO == uZLzeOIXIs){QDDiJFKBqQ = true;}
      if(BfkerEeCte == oXdREIQGle){KkWVNtGbEG = true;}
      else if(oXdREIQGle == BfkerEeCte){ufzdqUINlJ = true;}
      if(izZNywNClT == aIFUoEjsnI){AllyOKQUUU = true;}
      else if(aIFUoEjsnI == izZNywNClT){KkhIytyBbz = true;}
      if(cOjacBYXwD == UDtMPVYQDu){yPUWNdbJla = true;}
      else if(UDtMPVYQDu == cOjacBYXwD){iBsGPDARhL = true;}
      if(NZrxtPRVNH == AzHoqcwFIs){ILTZshDMTb = true;}
      if(PqCwWuAyAi == phRCgLCzhV){CAfoFMrELy = true;}
      if(BFloQlwJBp == YqWWsldRCh){ZJFDHtQzIj = true;}
      while(AzHoqcwFIs == NZrxtPRVNH){mhnAFFYUxg = true;}
      while(phRCgLCzhV == phRCgLCzhV){pqeJneVujP = true;}
      while(YqWWsldRCh == YqWWsldRCh){HJZqgtlrNm = true;}
      if(jzCpdaAQcM == true){jzCpdaAQcM = false;}
      if(IejuRmlrfD == true){IejuRmlrfD = false;}
      if(TZigVJbkuF == true){TZigVJbkuF = false;}
      if(ydCZIpeaXF == true){ydCZIpeaXF = false;}
      if(KkWVNtGbEG == true){KkWVNtGbEG = false;}
      if(AllyOKQUUU == true){AllyOKQUUU = false;}
      if(yPUWNdbJla == true){yPUWNdbJla = false;}
      if(ILTZshDMTb == true){ILTZshDMTb = false;}
      if(CAfoFMrELy == true){CAfoFMrELy = false;}
      if(ZJFDHtQzIj == true){ZJFDHtQzIj = false;}
      if(RwodyoRMFg == true){RwodyoRMFg = false;}
      if(HEBrRyjeRA == true){HEBrRyjeRA = false;}
      if(kXynByFQSy == true){kXynByFQSy = false;}
      if(QDDiJFKBqQ == true){QDDiJFKBqQ = false;}
      if(ufzdqUINlJ == true){ufzdqUINlJ = false;}
      if(KkhIytyBbz == true){KkhIytyBbz = false;}
      if(iBsGPDARhL == true){iBsGPDARhL = false;}
      if(mhnAFFYUxg == true){mhnAFFYUxg = false;}
      if(pqeJneVujP == true){pqeJneVujP = false;}
      if(HJZqgtlrNm == true){HJZqgtlrNm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BGFBOXNHPI
{ 
  void BxSxRfxAnW()
  { 
      bool QrUPXkKQqZ = false;
      bool IYkHwiVNTY = false;
      bool RVgUVsEUqD = false;
      bool kCIwqRSDxP = false;
      bool YkFDrxTFzg = false;
      bool ZsrGsuLAtd = false;
      bool foYnoGPnQd = false;
      bool PRPEzfPccY = false;
      bool YyUKcqKCCw = false;
      bool GSJSiiLROl = false;
      bool hfoVQIdnGN = false;
      bool eiXUEgTOLy = false;
      bool uNkTXxIxUQ = false;
      bool TxOpqsIzsU = false;
      bool NVuoQXunNB = false;
      bool OxGPpTtVxT = false;
      bool AfTpsgUgdL = false;
      bool YTVpkZSwCA = false;
      bool BTiSBWqyzW = false;
      bool zmCYUgCEui = false;
      string iDzwozKDyU;
      string AdHYxowrHl;
      string iufuIrXbPN;
      string gCeaMOPbfu;
      string ifCPyQVsps;
      string XclaUmXEnx;
      string ahnjnyygMi;
      string YTLLDCrPwr;
      string WdlVpDPDFZ;
      string qLniTArSbA;
      string SnfHTDRaXR;
      string tHHwaxwRtk;
      string htbmqNfbrD;
      string JZnwYhydBm;
      string kofmeiDrIW;
      string DaXqSXMsPG;
      string WohTHTSKWr;
      string ySPHzrOnHH;
      string KnTUAiCxdB;
      string VFNuPwHLeL;
      if(iDzwozKDyU == SnfHTDRaXR){QrUPXkKQqZ = true;}
      else if(SnfHTDRaXR == iDzwozKDyU){hfoVQIdnGN = true;}
      if(AdHYxowrHl == tHHwaxwRtk){IYkHwiVNTY = true;}
      else if(tHHwaxwRtk == AdHYxowrHl){eiXUEgTOLy = true;}
      if(iufuIrXbPN == htbmqNfbrD){RVgUVsEUqD = true;}
      else if(htbmqNfbrD == iufuIrXbPN){uNkTXxIxUQ = true;}
      if(gCeaMOPbfu == JZnwYhydBm){kCIwqRSDxP = true;}
      else if(JZnwYhydBm == gCeaMOPbfu){TxOpqsIzsU = true;}
      if(ifCPyQVsps == kofmeiDrIW){YkFDrxTFzg = true;}
      else if(kofmeiDrIW == ifCPyQVsps){NVuoQXunNB = true;}
      if(XclaUmXEnx == DaXqSXMsPG){ZsrGsuLAtd = true;}
      else if(DaXqSXMsPG == XclaUmXEnx){OxGPpTtVxT = true;}
      if(ahnjnyygMi == WohTHTSKWr){foYnoGPnQd = true;}
      else if(WohTHTSKWr == ahnjnyygMi){AfTpsgUgdL = true;}
      if(YTLLDCrPwr == ySPHzrOnHH){PRPEzfPccY = true;}
      if(WdlVpDPDFZ == KnTUAiCxdB){YyUKcqKCCw = true;}
      if(qLniTArSbA == VFNuPwHLeL){GSJSiiLROl = true;}
      while(ySPHzrOnHH == YTLLDCrPwr){YTVpkZSwCA = true;}
      while(KnTUAiCxdB == KnTUAiCxdB){BTiSBWqyzW = true;}
      while(VFNuPwHLeL == VFNuPwHLeL){zmCYUgCEui = true;}
      if(QrUPXkKQqZ == true){QrUPXkKQqZ = false;}
      if(IYkHwiVNTY == true){IYkHwiVNTY = false;}
      if(RVgUVsEUqD == true){RVgUVsEUqD = false;}
      if(kCIwqRSDxP == true){kCIwqRSDxP = false;}
      if(YkFDrxTFzg == true){YkFDrxTFzg = false;}
      if(ZsrGsuLAtd == true){ZsrGsuLAtd = false;}
      if(foYnoGPnQd == true){foYnoGPnQd = false;}
      if(PRPEzfPccY == true){PRPEzfPccY = false;}
      if(YyUKcqKCCw == true){YyUKcqKCCw = false;}
      if(GSJSiiLROl == true){GSJSiiLROl = false;}
      if(hfoVQIdnGN == true){hfoVQIdnGN = false;}
      if(eiXUEgTOLy == true){eiXUEgTOLy = false;}
      if(uNkTXxIxUQ == true){uNkTXxIxUQ = false;}
      if(TxOpqsIzsU == true){TxOpqsIzsU = false;}
      if(NVuoQXunNB == true){NVuoQXunNB = false;}
      if(OxGPpTtVxT == true){OxGPpTtVxT = false;}
      if(AfTpsgUgdL == true){AfTpsgUgdL = false;}
      if(YTVpkZSwCA == true){YTVpkZSwCA = false;}
      if(BTiSBWqyzW == true){BTiSBWqyzW = false;}
      if(zmCYUgCEui == true){zmCYUgCEui = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXTHKJSPVW
{ 
  void STFiLNjsih()
  { 
      bool VtupyKxJiR = false;
      bool WAnLqAZlal = false;
      bool GBTQiVmYIx = false;
      bool kyudnAraUy = false;
      bool cGZZIfyMNM = false;
      bool HPqLVTadHc = false;
      bool WYAkgXFKXp = false;
      bool HyQbJzasIC = false;
      bool WaLupUGjHT = false;
      bool ZOTqbEFosj = false;
      bool amoWEIzOCV = false;
      bool sgVEFwMFuL = false;
      bool RUCEPseZAE = false;
      bool tlAYbjlnpg = false;
      bool VqhlZrrOkf = false;
      bool qAshSFkjGL = false;
      bool dYOxbHgxcV = false;
      bool KYONpZmQdX = false;
      bool APoUNsrRGW = false;
      bool zBgeCwckJS = false;
      string ugiMPOfmMY;
      string WkHspmeihC;
      string ojHdXzwTmW;
      string bnxfZmUtNM;
      string qtpPhwZROH;
      string DlAbIKYEoQ;
      string SMzowhnaTD;
      string RjVULutqwa;
      string ZdFfTpmUXO;
      string NPFxtdtATz;
      string HyyKoSQfQN;
      string QhIOqnHTVF;
      string tTDEoCeXZg;
      string AtWwSaftqA;
      string ZHDKyfGqGG;
      string WadOEnttVl;
      string nrFjMVKLuP;
      string HMcUemQsFJ;
      string unRTJZPIre;
      string glYEMhCSxb;
      if(ugiMPOfmMY == HyyKoSQfQN){VtupyKxJiR = true;}
      else if(HyyKoSQfQN == ugiMPOfmMY){amoWEIzOCV = true;}
      if(WkHspmeihC == QhIOqnHTVF){WAnLqAZlal = true;}
      else if(QhIOqnHTVF == WkHspmeihC){sgVEFwMFuL = true;}
      if(ojHdXzwTmW == tTDEoCeXZg){GBTQiVmYIx = true;}
      else if(tTDEoCeXZg == ojHdXzwTmW){RUCEPseZAE = true;}
      if(bnxfZmUtNM == AtWwSaftqA){kyudnAraUy = true;}
      else if(AtWwSaftqA == bnxfZmUtNM){tlAYbjlnpg = true;}
      if(qtpPhwZROH == ZHDKyfGqGG){cGZZIfyMNM = true;}
      else if(ZHDKyfGqGG == qtpPhwZROH){VqhlZrrOkf = true;}
      if(DlAbIKYEoQ == WadOEnttVl){HPqLVTadHc = true;}
      else if(WadOEnttVl == DlAbIKYEoQ){qAshSFkjGL = true;}
      if(SMzowhnaTD == nrFjMVKLuP){WYAkgXFKXp = true;}
      else if(nrFjMVKLuP == SMzowhnaTD){dYOxbHgxcV = true;}
      if(RjVULutqwa == HMcUemQsFJ){HyQbJzasIC = true;}
      if(ZdFfTpmUXO == unRTJZPIre){WaLupUGjHT = true;}
      if(NPFxtdtATz == glYEMhCSxb){ZOTqbEFosj = true;}
      while(HMcUemQsFJ == RjVULutqwa){KYONpZmQdX = true;}
      while(unRTJZPIre == unRTJZPIre){APoUNsrRGW = true;}
      while(glYEMhCSxb == glYEMhCSxb){zBgeCwckJS = true;}
      if(VtupyKxJiR == true){VtupyKxJiR = false;}
      if(WAnLqAZlal == true){WAnLqAZlal = false;}
      if(GBTQiVmYIx == true){GBTQiVmYIx = false;}
      if(kyudnAraUy == true){kyudnAraUy = false;}
      if(cGZZIfyMNM == true){cGZZIfyMNM = false;}
      if(HPqLVTadHc == true){HPqLVTadHc = false;}
      if(WYAkgXFKXp == true){WYAkgXFKXp = false;}
      if(HyQbJzasIC == true){HyQbJzasIC = false;}
      if(WaLupUGjHT == true){WaLupUGjHT = false;}
      if(ZOTqbEFosj == true){ZOTqbEFosj = false;}
      if(amoWEIzOCV == true){amoWEIzOCV = false;}
      if(sgVEFwMFuL == true){sgVEFwMFuL = false;}
      if(RUCEPseZAE == true){RUCEPseZAE = false;}
      if(tlAYbjlnpg == true){tlAYbjlnpg = false;}
      if(VqhlZrrOkf == true){VqhlZrrOkf = false;}
      if(qAshSFkjGL == true){qAshSFkjGL = false;}
      if(dYOxbHgxcV == true){dYOxbHgxcV = false;}
      if(KYONpZmQdX == true){KYONpZmQdX = false;}
      if(APoUNsrRGW == true){APoUNsrRGW = false;}
      if(zBgeCwckJS == true){zBgeCwckJS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WHSWQDMZNK
{ 
  void ncOKcGMpQX()
  { 
      bool mYooWCUqgc = false;
      bool HbPkFKdNyh = false;
      bool nfisctZTca = false;
      bool EGshRDNEfa = false;
      bool yPxpxASOZV = false;
      bool hxcgpGpwLb = false;
      bool cANGXBihTC = false;
      bool wYgWiXirub = false;
      bool bLtHrGcMqK = false;
      bool NQrDyyCpSu = false;
      bool RktXYJQFxS = false;
      bool XxBiAQGFNQ = false;
      bool YWpIoffdYk = false;
      bool VrZzKpQVii = false;
      bool pWPYlPPJDg = false;
      bool qwcBWutkir = false;
      bool cmgLwfXBYJ = false;
      bool AkWdaBHRWY = false;
      bool PWZqtYOYbP = false;
      bool uelpGDoDbG = false;
      string YBcAHbhrbb;
      string sAIGSsaFAo;
      string XMASgQKjda;
      string JHXZoIABEH;
      string pyCJVGshCd;
      string cNMiQMAKTp;
      string RxOASlciQJ;
      string sYBszZJpwZ;
      string XbhzxutoIc;
      string HohNorjCqj;
      string dKQrkELTjq;
      string CJOtSoPOCW;
      string qnZnCDqnDG;
      string oGzMuNLpNs;
      string jaFRaxantA;
      string cVAUspjcph;
      string NXPcCuKCyF;
      string cZAImPhIME;
      string bDsCdTGeTF;
      string cizffLKbOe;
      if(YBcAHbhrbb == dKQrkELTjq){mYooWCUqgc = true;}
      else if(dKQrkELTjq == YBcAHbhrbb){RktXYJQFxS = true;}
      if(sAIGSsaFAo == CJOtSoPOCW){HbPkFKdNyh = true;}
      else if(CJOtSoPOCW == sAIGSsaFAo){XxBiAQGFNQ = true;}
      if(XMASgQKjda == qnZnCDqnDG){nfisctZTca = true;}
      else if(qnZnCDqnDG == XMASgQKjda){YWpIoffdYk = true;}
      if(JHXZoIABEH == oGzMuNLpNs){EGshRDNEfa = true;}
      else if(oGzMuNLpNs == JHXZoIABEH){VrZzKpQVii = true;}
      if(pyCJVGshCd == jaFRaxantA){yPxpxASOZV = true;}
      else if(jaFRaxantA == pyCJVGshCd){pWPYlPPJDg = true;}
      if(cNMiQMAKTp == cVAUspjcph){hxcgpGpwLb = true;}
      else if(cVAUspjcph == cNMiQMAKTp){qwcBWutkir = true;}
      if(RxOASlciQJ == NXPcCuKCyF){cANGXBihTC = true;}
      else if(NXPcCuKCyF == RxOASlciQJ){cmgLwfXBYJ = true;}
      if(sYBszZJpwZ == cZAImPhIME){wYgWiXirub = true;}
      if(XbhzxutoIc == bDsCdTGeTF){bLtHrGcMqK = true;}
      if(HohNorjCqj == cizffLKbOe){NQrDyyCpSu = true;}
      while(cZAImPhIME == sYBszZJpwZ){AkWdaBHRWY = true;}
      while(bDsCdTGeTF == bDsCdTGeTF){PWZqtYOYbP = true;}
      while(cizffLKbOe == cizffLKbOe){uelpGDoDbG = true;}
      if(mYooWCUqgc == true){mYooWCUqgc = false;}
      if(HbPkFKdNyh == true){HbPkFKdNyh = false;}
      if(nfisctZTca == true){nfisctZTca = false;}
      if(EGshRDNEfa == true){EGshRDNEfa = false;}
      if(yPxpxASOZV == true){yPxpxASOZV = false;}
      if(hxcgpGpwLb == true){hxcgpGpwLb = false;}
      if(cANGXBihTC == true){cANGXBihTC = false;}
      if(wYgWiXirub == true){wYgWiXirub = false;}
      if(bLtHrGcMqK == true){bLtHrGcMqK = false;}
      if(NQrDyyCpSu == true){NQrDyyCpSu = false;}
      if(RktXYJQFxS == true){RktXYJQFxS = false;}
      if(XxBiAQGFNQ == true){XxBiAQGFNQ = false;}
      if(YWpIoffdYk == true){YWpIoffdYk = false;}
      if(VrZzKpQVii == true){VrZzKpQVii = false;}
      if(pWPYlPPJDg == true){pWPYlPPJDg = false;}
      if(qwcBWutkir == true){qwcBWutkir = false;}
      if(cmgLwfXBYJ == true){cmgLwfXBYJ = false;}
      if(AkWdaBHRWY == true){AkWdaBHRWY = false;}
      if(PWZqtYOYbP == true){PWZqtYOYbP = false;}
      if(uelpGDoDbG == true){uelpGDoDbG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HNOUAJDFCF
{ 
  void wOQwOwVWJt()
  { 
      bool MWBxIdGPQZ = false;
      bool MCJmBEwxqD = false;
      bool wtIhDkPGuO = false;
      bool TZlqYitjZX = false;
      bool RMjCMLYxxL = false;
      bool SouEDRNTtW = false;
      bool NzTCFmPSOS = false;
      bool JMXTkiJGVq = false;
      bool MRJjuddhmG = false;
      bool UaoDJSrhwZ = false;
      bool wGidBGRbST = false;
      bool HHyDKuojGb = false;
      bool IgeIxhXTJS = false;
      bool pbJutFheho = false;
      bool LCOSyMckrO = false;
      bool cIaUROaagT = false;
      bool iyRzcfyCJE = false;
      bool MJCQPFRMKj = false;
      bool ElbuphAnde = false;
      bool eHyOGNjPpR = false;
      string mlQSyiXLxe;
      string jExuDbMriu;
      string eGcHqldmSz;
      string kyCWfILqEn;
      string ZSBMrWBdLn;
      string bPmuZgIJaM;
      string FkryskBaOt;
      string QVnuULFPOT;
      string jzaeWULHxz;
      string ACPqinaCTG;
      string UZPRWGarZN;
      string artGbFJNbX;
      string ZtdOsOFxLf;
      string kCwIzKjJHQ;
      string sSgjXIIIPd;
      string eMaufZwAXI;
      string AdfsbYukHR;
      string UAGKdGNtpk;
      string GwhhBYbBbY;
      string OikzPPmmHz;
      if(mlQSyiXLxe == UZPRWGarZN){MWBxIdGPQZ = true;}
      else if(UZPRWGarZN == mlQSyiXLxe){wGidBGRbST = true;}
      if(jExuDbMriu == artGbFJNbX){MCJmBEwxqD = true;}
      else if(artGbFJNbX == jExuDbMriu){HHyDKuojGb = true;}
      if(eGcHqldmSz == ZtdOsOFxLf){wtIhDkPGuO = true;}
      else if(ZtdOsOFxLf == eGcHqldmSz){IgeIxhXTJS = true;}
      if(kyCWfILqEn == kCwIzKjJHQ){TZlqYitjZX = true;}
      else if(kCwIzKjJHQ == kyCWfILqEn){pbJutFheho = true;}
      if(ZSBMrWBdLn == sSgjXIIIPd){RMjCMLYxxL = true;}
      else if(sSgjXIIIPd == ZSBMrWBdLn){LCOSyMckrO = true;}
      if(bPmuZgIJaM == eMaufZwAXI){SouEDRNTtW = true;}
      else if(eMaufZwAXI == bPmuZgIJaM){cIaUROaagT = true;}
      if(FkryskBaOt == AdfsbYukHR){NzTCFmPSOS = true;}
      else if(AdfsbYukHR == FkryskBaOt){iyRzcfyCJE = true;}
      if(QVnuULFPOT == UAGKdGNtpk){JMXTkiJGVq = true;}
      if(jzaeWULHxz == GwhhBYbBbY){MRJjuddhmG = true;}
      if(ACPqinaCTG == OikzPPmmHz){UaoDJSrhwZ = true;}
      while(UAGKdGNtpk == QVnuULFPOT){MJCQPFRMKj = true;}
      while(GwhhBYbBbY == GwhhBYbBbY){ElbuphAnde = true;}
      while(OikzPPmmHz == OikzPPmmHz){eHyOGNjPpR = true;}
      if(MWBxIdGPQZ == true){MWBxIdGPQZ = false;}
      if(MCJmBEwxqD == true){MCJmBEwxqD = false;}
      if(wtIhDkPGuO == true){wtIhDkPGuO = false;}
      if(TZlqYitjZX == true){TZlqYitjZX = false;}
      if(RMjCMLYxxL == true){RMjCMLYxxL = false;}
      if(SouEDRNTtW == true){SouEDRNTtW = false;}
      if(NzTCFmPSOS == true){NzTCFmPSOS = false;}
      if(JMXTkiJGVq == true){JMXTkiJGVq = false;}
      if(MRJjuddhmG == true){MRJjuddhmG = false;}
      if(UaoDJSrhwZ == true){UaoDJSrhwZ = false;}
      if(wGidBGRbST == true){wGidBGRbST = false;}
      if(HHyDKuojGb == true){HHyDKuojGb = false;}
      if(IgeIxhXTJS == true){IgeIxhXTJS = false;}
      if(pbJutFheho == true){pbJutFheho = false;}
      if(LCOSyMckrO == true){LCOSyMckrO = false;}
      if(cIaUROaagT == true){cIaUROaagT = false;}
      if(iyRzcfyCJE == true){iyRzcfyCJE = false;}
      if(MJCQPFRMKj == true){MJCQPFRMKj = false;}
      if(ElbuphAnde == true){ElbuphAnde = false;}
      if(eHyOGNjPpR == true){eHyOGNjPpR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DXINVIGVHT
{ 
  void yTDViPbDFb()
  { 
      bool JxURIACeor = false;
      bool oQaVJXZBzk = false;
      bool WnJrCKNIyt = false;
      bool YJRObBqKge = false;
      bool YafTSCOcBl = false;
      bool njjqAUmbOx = false;
      bool ltftTezLsI = false;
      bool fPUTMwIoZA = false;
      bool wkGMFnZZOG = false;
      bool OOujrdulAm = false;
      bool CCisFYPPeD = false;
      bool MxCNBBmTne = false;
      bool FYwltQUkah = false;
      bool BVolysBMGg = false;
      bool YKtKsQLghq = false;
      bool paxUhcFwzo = false;
      bool DdnxCqIQPH = false;
      bool zaNGFuelrd = false;
      bool FnCjqZXTEU = false;
      bool mFNRdtVxIC = false;
      string lIteiQcidY;
      string WUKheUUYXo;
      string MiiCKHLowR;
      string LPcZYYxdRP;
      string SABmxfgITz;
      string HZxrYDZqTb;
      string FnlMMGqkIF;
      string XqGIVMguFe;
      string aCUwKkSjBV;
      string zFJoKeNoap;
      string ouAOaQToVL;
      string VeloBCSpBb;
      string nGjmGSgQxq;
      string zrUPoeCGUs;
      string RcNoATTUnH;
      string LXmzChLNHI;
      string jCqeMcKWzV;
      string zLUIJKstll;
      string yLboebFVMH;
      string SoyLJOlicX;
      if(lIteiQcidY == ouAOaQToVL){JxURIACeor = true;}
      else if(ouAOaQToVL == lIteiQcidY){CCisFYPPeD = true;}
      if(WUKheUUYXo == VeloBCSpBb){oQaVJXZBzk = true;}
      else if(VeloBCSpBb == WUKheUUYXo){MxCNBBmTne = true;}
      if(MiiCKHLowR == nGjmGSgQxq){WnJrCKNIyt = true;}
      else if(nGjmGSgQxq == MiiCKHLowR){FYwltQUkah = true;}
      if(LPcZYYxdRP == zrUPoeCGUs){YJRObBqKge = true;}
      else if(zrUPoeCGUs == LPcZYYxdRP){BVolysBMGg = true;}
      if(SABmxfgITz == RcNoATTUnH){YafTSCOcBl = true;}
      else if(RcNoATTUnH == SABmxfgITz){YKtKsQLghq = true;}
      if(HZxrYDZqTb == LXmzChLNHI){njjqAUmbOx = true;}
      else if(LXmzChLNHI == HZxrYDZqTb){paxUhcFwzo = true;}
      if(FnlMMGqkIF == jCqeMcKWzV){ltftTezLsI = true;}
      else if(jCqeMcKWzV == FnlMMGqkIF){DdnxCqIQPH = true;}
      if(XqGIVMguFe == zLUIJKstll){fPUTMwIoZA = true;}
      if(aCUwKkSjBV == yLboebFVMH){wkGMFnZZOG = true;}
      if(zFJoKeNoap == SoyLJOlicX){OOujrdulAm = true;}
      while(zLUIJKstll == XqGIVMguFe){zaNGFuelrd = true;}
      while(yLboebFVMH == yLboebFVMH){FnCjqZXTEU = true;}
      while(SoyLJOlicX == SoyLJOlicX){mFNRdtVxIC = true;}
      if(JxURIACeor == true){JxURIACeor = false;}
      if(oQaVJXZBzk == true){oQaVJXZBzk = false;}
      if(WnJrCKNIyt == true){WnJrCKNIyt = false;}
      if(YJRObBqKge == true){YJRObBqKge = false;}
      if(YafTSCOcBl == true){YafTSCOcBl = false;}
      if(njjqAUmbOx == true){njjqAUmbOx = false;}
      if(ltftTezLsI == true){ltftTezLsI = false;}
      if(fPUTMwIoZA == true){fPUTMwIoZA = false;}
      if(wkGMFnZZOG == true){wkGMFnZZOG = false;}
      if(OOujrdulAm == true){OOujrdulAm = false;}
      if(CCisFYPPeD == true){CCisFYPPeD = false;}
      if(MxCNBBmTne == true){MxCNBBmTne = false;}
      if(FYwltQUkah == true){FYwltQUkah = false;}
      if(BVolysBMGg == true){BVolysBMGg = false;}
      if(YKtKsQLghq == true){YKtKsQLghq = false;}
      if(paxUhcFwzo == true){paxUhcFwzo = false;}
      if(DdnxCqIQPH == true){DdnxCqIQPH = false;}
      if(zaNGFuelrd == true){zaNGFuelrd = false;}
      if(FnCjqZXTEU == true){FnCjqZXTEU = false;}
      if(mFNRdtVxIC == true){mFNRdtVxIC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWZGXTFZBH
{ 
  void bMTnNNFJiq()
  { 
      bool qNKslycjjr = false;
      bool sCgMAxuanF = false;
      bool yaeOiyOYRx = false;
      bool sGFJQPVguy = false;
      bool sADjRNVxnQ = false;
      bool YlAREPiwJn = false;
      bool iERmylxWuj = false;
      bool aNfoMyWtwU = false;
      bool bQkAXGGmEA = false;
      bool gZXHPohQle = false;
      bool QzCDpLGLFG = false;
      bool snznLRSQPr = false;
      bool fKRuDBpXYW = false;
      bool PGIREcOhKM = false;
      bool AugyHrZiux = false;
      bool WQBszFgHzn = false;
      bool Uhlipmehii = false;
      bool DjGCqjdTnK = false;
      bool aGcbzzEORz = false;
      bool uHhWqRJxHU = false;
      string ZAKBrGfLWQ;
      string RjsdkIUyim;
      string juxRSpOQiK;
      string cliUDNAsqc;
      string pzDxKJhVFl;
      string WwjDbdDriC;
      string qPbMnfAXaX;
      string IaHGwkrzHI;
      string HrLwmfBfsY;
      string JHJnkaWpJd;
      string JKuhduodGq;
      string lEkZuyDfYI;
      string eUeBNAQSUU;
      string NBoczwxdRr;
      string pWYBmFWjrm;
      string XqQBznftTd;
      string dVJkcjOIZz;
      string BYNgRHucNH;
      string dgahxWkncL;
      string QCJnOUNnXD;
      if(ZAKBrGfLWQ == JKuhduodGq){qNKslycjjr = true;}
      else if(JKuhduodGq == ZAKBrGfLWQ){QzCDpLGLFG = true;}
      if(RjsdkIUyim == lEkZuyDfYI){sCgMAxuanF = true;}
      else if(lEkZuyDfYI == RjsdkIUyim){snznLRSQPr = true;}
      if(juxRSpOQiK == eUeBNAQSUU){yaeOiyOYRx = true;}
      else if(eUeBNAQSUU == juxRSpOQiK){fKRuDBpXYW = true;}
      if(cliUDNAsqc == NBoczwxdRr){sGFJQPVguy = true;}
      else if(NBoczwxdRr == cliUDNAsqc){PGIREcOhKM = true;}
      if(pzDxKJhVFl == pWYBmFWjrm){sADjRNVxnQ = true;}
      else if(pWYBmFWjrm == pzDxKJhVFl){AugyHrZiux = true;}
      if(WwjDbdDriC == XqQBznftTd){YlAREPiwJn = true;}
      else if(XqQBznftTd == WwjDbdDriC){WQBszFgHzn = true;}
      if(qPbMnfAXaX == dVJkcjOIZz){iERmylxWuj = true;}
      else if(dVJkcjOIZz == qPbMnfAXaX){Uhlipmehii = true;}
      if(IaHGwkrzHI == BYNgRHucNH){aNfoMyWtwU = true;}
      if(HrLwmfBfsY == dgahxWkncL){bQkAXGGmEA = true;}
      if(JHJnkaWpJd == QCJnOUNnXD){gZXHPohQle = true;}
      while(BYNgRHucNH == IaHGwkrzHI){DjGCqjdTnK = true;}
      while(dgahxWkncL == dgahxWkncL){aGcbzzEORz = true;}
      while(QCJnOUNnXD == QCJnOUNnXD){uHhWqRJxHU = true;}
      if(qNKslycjjr == true){qNKslycjjr = false;}
      if(sCgMAxuanF == true){sCgMAxuanF = false;}
      if(yaeOiyOYRx == true){yaeOiyOYRx = false;}
      if(sGFJQPVguy == true){sGFJQPVguy = false;}
      if(sADjRNVxnQ == true){sADjRNVxnQ = false;}
      if(YlAREPiwJn == true){YlAREPiwJn = false;}
      if(iERmylxWuj == true){iERmylxWuj = false;}
      if(aNfoMyWtwU == true){aNfoMyWtwU = false;}
      if(bQkAXGGmEA == true){bQkAXGGmEA = false;}
      if(gZXHPohQle == true){gZXHPohQle = false;}
      if(QzCDpLGLFG == true){QzCDpLGLFG = false;}
      if(snznLRSQPr == true){snznLRSQPr = false;}
      if(fKRuDBpXYW == true){fKRuDBpXYW = false;}
      if(PGIREcOhKM == true){PGIREcOhKM = false;}
      if(AugyHrZiux == true){AugyHrZiux = false;}
      if(WQBszFgHzn == true){WQBszFgHzn = false;}
      if(Uhlipmehii == true){Uhlipmehii = false;}
      if(DjGCqjdTnK == true){DjGCqjdTnK = false;}
      if(aGcbzzEORz == true){aGcbzzEORz = false;}
      if(uHhWqRJxHU == true){uHhWqRJxHU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FDRUVJRAEY
{ 
  void CEcxfxZhjJ()
  { 
      bool jVKMQfDdKy = false;
      bool TzESkLTRUk = false;
      bool WoCkwblxNl = false;
      bool KQtNVqFbEe = false;
      bool mKrdujEoJs = false;
      bool smtzHtTZQo = false;
      bool tFPXmCFqxt = false;
      bool FqNoxMwXoM = false;
      bool XwmTsXWuGa = false;
      bool WeLOkgtTqr = false;
      bool dMrPmCZECu = false;
      bool ywjERySweP = false;
      bool fJjVWafyEP = false;
      bool RbgxhKDWgp = false;
      bool yRrLcatGxl = false;
      bool OyoaLUcWsM = false;
      bool WaAlcVPmWH = false;
      bool twOnRNRYsu = false;
      bool fYBRBSmGlN = false;
      bool ggcTTWRGiG = false;
      string rPNRMRUzdP;
      string eJelxjjrmC;
      string xOOiJenHFr;
      string cYTKQiAhVW;
      string OcgTZRqBUx;
      string GOYGidBdHh;
      string dNtklGpTVO;
      string jCVPmUguJr;
      string mllHkOANam;
      string gVamsBhwhT;
      string bXfFNErISO;
      string wFUPtqalzW;
      string GbrhgObiWl;
      string lkNpPOGgtg;
      string WquMpbBKsB;
      string auwKNAexXy;
      string bJlfbLrezf;
      string ktrSAOffrF;
      string NQoULpnCcO;
      string iJIuENEOkd;
      if(rPNRMRUzdP == bXfFNErISO){jVKMQfDdKy = true;}
      else if(bXfFNErISO == rPNRMRUzdP){dMrPmCZECu = true;}
      if(eJelxjjrmC == wFUPtqalzW){TzESkLTRUk = true;}
      else if(wFUPtqalzW == eJelxjjrmC){ywjERySweP = true;}
      if(xOOiJenHFr == GbrhgObiWl){WoCkwblxNl = true;}
      else if(GbrhgObiWl == xOOiJenHFr){fJjVWafyEP = true;}
      if(cYTKQiAhVW == lkNpPOGgtg){KQtNVqFbEe = true;}
      else if(lkNpPOGgtg == cYTKQiAhVW){RbgxhKDWgp = true;}
      if(OcgTZRqBUx == WquMpbBKsB){mKrdujEoJs = true;}
      else if(WquMpbBKsB == OcgTZRqBUx){yRrLcatGxl = true;}
      if(GOYGidBdHh == auwKNAexXy){smtzHtTZQo = true;}
      else if(auwKNAexXy == GOYGidBdHh){OyoaLUcWsM = true;}
      if(dNtklGpTVO == bJlfbLrezf){tFPXmCFqxt = true;}
      else if(bJlfbLrezf == dNtklGpTVO){WaAlcVPmWH = true;}
      if(jCVPmUguJr == ktrSAOffrF){FqNoxMwXoM = true;}
      if(mllHkOANam == NQoULpnCcO){XwmTsXWuGa = true;}
      if(gVamsBhwhT == iJIuENEOkd){WeLOkgtTqr = true;}
      while(ktrSAOffrF == jCVPmUguJr){twOnRNRYsu = true;}
      while(NQoULpnCcO == NQoULpnCcO){fYBRBSmGlN = true;}
      while(iJIuENEOkd == iJIuENEOkd){ggcTTWRGiG = true;}
      if(jVKMQfDdKy == true){jVKMQfDdKy = false;}
      if(TzESkLTRUk == true){TzESkLTRUk = false;}
      if(WoCkwblxNl == true){WoCkwblxNl = false;}
      if(KQtNVqFbEe == true){KQtNVqFbEe = false;}
      if(mKrdujEoJs == true){mKrdujEoJs = false;}
      if(smtzHtTZQo == true){smtzHtTZQo = false;}
      if(tFPXmCFqxt == true){tFPXmCFqxt = false;}
      if(FqNoxMwXoM == true){FqNoxMwXoM = false;}
      if(XwmTsXWuGa == true){XwmTsXWuGa = false;}
      if(WeLOkgtTqr == true){WeLOkgtTqr = false;}
      if(dMrPmCZECu == true){dMrPmCZECu = false;}
      if(ywjERySweP == true){ywjERySweP = false;}
      if(fJjVWafyEP == true){fJjVWafyEP = false;}
      if(RbgxhKDWgp == true){RbgxhKDWgp = false;}
      if(yRrLcatGxl == true){yRrLcatGxl = false;}
      if(OyoaLUcWsM == true){OyoaLUcWsM = false;}
      if(WaAlcVPmWH == true){WaAlcVPmWH = false;}
      if(twOnRNRYsu == true){twOnRNRYsu = false;}
      if(fYBRBSmGlN == true){fYBRBSmGlN = false;}
      if(ggcTTWRGiG == true){ggcTTWRGiG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BRCJIYAZME
{ 
  void OiDfzBQCeJ()
  { 
      bool sJwRgWyrHL = false;
      bool JUklIusSce = false;
      bool KuGQsrmfhN = false;
      bool yGeTSiqOnw = false;
      bool UZMnQoYOuM = false;
      bool lZZmIyDfXo = false;
      bool jSKtMDpRSY = false;
      bool EddgKkhSzD = false;
      bool SXjVaXgqLU = false;
      bool fKpzLBPSaN = false;
      bool zHuWHIwrcX = false;
      bool QjgUVLinSo = false;
      bool WzFyrsndUI = false;
      bool UOqkEKbNNS = false;
      bool bnNmEudVdA = false;
      bool SazlqzCxdO = false;
      bool TRWUDBruQK = false;
      bool jUaAMhkStx = false;
      bool OSAUosOFtE = false;
      bool IejzyKQsjC = false;
      string YIsgXFQUIw;
      string ILfnUxhFsp;
      string FZAFadUGNU;
      string QGewaDMfyL;
      string KeGebGRYlu;
      string PidFbyHmFt;
      string kKHnfBgiNR;
      string jCGheZTVdT;
      string LwURFgcYTb;
      string uZZEZAXRza;
      string ZhKULMbwZB;
      string elJkhoooiy;
      string XHPkVJcCHd;
      string CBVCsdkAFr;
      string FgyRxJQnVk;
      string LhiBCSSZyB;
      string jZnwzcPGqE;
      string DnipsqIxnM;
      string snfVSTSUza;
      string KKBDIerCST;
      if(YIsgXFQUIw == ZhKULMbwZB){sJwRgWyrHL = true;}
      else if(ZhKULMbwZB == YIsgXFQUIw){zHuWHIwrcX = true;}
      if(ILfnUxhFsp == elJkhoooiy){JUklIusSce = true;}
      else if(elJkhoooiy == ILfnUxhFsp){QjgUVLinSo = true;}
      if(FZAFadUGNU == XHPkVJcCHd){KuGQsrmfhN = true;}
      else if(XHPkVJcCHd == FZAFadUGNU){WzFyrsndUI = true;}
      if(QGewaDMfyL == CBVCsdkAFr){yGeTSiqOnw = true;}
      else if(CBVCsdkAFr == QGewaDMfyL){UOqkEKbNNS = true;}
      if(KeGebGRYlu == FgyRxJQnVk){UZMnQoYOuM = true;}
      else if(FgyRxJQnVk == KeGebGRYlu){bnNmEudVdA = true;}
      if(PidFbyHmFt == LhiBCSSZyB){lZZmIyDfXo = true;}
      else if(LhiBCSSZyB == PidFbyHmFt){SazlqzCxdO = true;}
      if(kKHnfBgiNR == jZnwzcPGqE){jSKtMDpRSY = true;}
      else if(jZnwzcPGqE == kKHnfBgiNR){TRWUDBruQK = true;}
      if(jCGheZTVdT == DnipsqIxnM){EddgKkhSzD = true;}
      if(LwURFgcYTb == snfVSTSUza){SXjVaXgqLU = true;}
      if(uZZEZAXRza == KKBDIerCST){fKpzLBPSaN = true;}
      while(DnipsqIxnM == jCGheZTVdT){jUaAMhkStx = true;}
      while(snfVSTSUza == snfVSTSUza){OSAUosOFtE = true;}
      while(KKBDIerCST == KKBDIerCST){IejzyKQsjC = true;}
      if(sJwRgWyrHL == true){sJwRgWyrHL = false;}
      if(JUklIusSce == true){JUklIusSce = false;}
      if(KuGQsrmfhN == true){KuGQsrmfhN = false;}
      if(yGeTSiqOnw == true){yGeTSiqOnw = false;}
      if(UZMnQoYOuM == true){UZMnQoYOuM = false;}
      if(lZZmIyDfXo == true){lZZmIyDfXo = false;}
      if(jSKtMDpRSY == true){jSKtMDpRSY = false;}
      if(EddgKkhSzD == true){EddgKkhSzD = false;}
      if(SXjVaXgqLU == true){SXjVaXgqLU = false;}
      if(fKpzLBPSaN == true){fKpzLBPSaN = false;}
      if(zHuWHIwrcX == true){zHuWHIwrcX = false;}
      if(QjgUVLinSo == true){QjgUVLinSo = false;}
      if(WzFyrsndUI == true){WzFyrsndUI = false;}
      if(UOqkEKbNNS == true){UOqkEKbNNS = false;}
      if(bnNmEudVdA == true){bnNmEudVdA = false;}
      if(SazlqzCxdO == true){SazlqzCxdO = false;}
      if(TRWUDBruQK == true){TRWUDBruQK = false;}
      if(jUaAMhkStx == true){jUaAMhkStx = false;}
      if(OSAUosOFtE == true){OSAUosOFtE = false;}
      if(IejzyKQsjC == true){IejzyKQsjC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XNDXHSSLPA
{ 
  void QaPdqrMeeh()
  { 
      bool ecKWkOVpUL = false;
      bool xrQUryfjlc = false;
      bool PuXBbMwRZP = false;
      bool jgRhymJOkQ = false;
      bool KsPftHJpEG = false;
      bool KsDINiEItY = false;
      bool REQEbPaiVE = false;
      bool nRyUSWfqHT = false;
      bool CGNTEpdITO = false;
      bool iATMzFcKEd = false;
      bool gaTzRsthpp = false;
      bool DNBZWLqwzk = false;
      bool lROHVmxlUM = false;
      bool tUmcmamNBL = false;
      bool wuScLUztpm = false;
      bool OfKTqOMMde = false;
      bool uIMcwhZYmu = false;
      bool YcunnqykwA = false;
      bool nDuhxOKTkX = false;
      bool OaiWPnhpgc = false;
      string pFPPeYlTBu;
      string kfhilgBImj;
      string MLMuEKLZcl;
      string XAdNLtuTwb;
      string xtkMHxQodE;
      string XOMFrdrULU;
      string MLqOWkBUWq;
      string kgMKlSZAmG;
      string sVwXNJmYUh;
      string CaIaPkCVoW;
      string uwRmSqCCSZ;
      string DqgEaqPSBN;
      string xczonKYkuB;
      string PELQKxDIFW;
      string HjGudKsEAX;
      string UjUaYSwcyI;
      string SQHRJzfPsc;
      string mGNdGMVDLd;
      string QUkWffijrq;
      string AaKwEpcold;
      if(pFPPeYlTBu == uwRmSqCCSZ){ecKWkOVpUL = true;}
      else if(uwRmSqCCSZ == pFPPeYlTBu){gaTzRsthpp = true;}
      if(kfhilgBImj == DqgEaqPSBN){xrQUryfjlc = true;}
      else if(DqgEaqPSBN == kfhilgBImj){DNBZWLqwzk = true;}
      if(MLMuEKLZcl == xczonKYkuB){PuXBbMwRZP = true;}
      else if(xczonKYkuB == MLMuEKLZcl){lROHVmxlUM = true;}
      if(XAdNLtuTwb == PELQKxDIFW){jgRhymJOkQ = true;}
      else if(PELQKxDIFW == XAdNLtuTwb){tUmcmamNBL = true;}
      if(xtkMHxQodE == HjGudKsEAX){KsPftHJpEG = true;}
      else if(HjGudKsEAX == xtkMHxQodE){wuScLUztpm = true;}
      if(XOMFrdrULU == UjUaYSwcyI){KsDINiEItY = true;}
      else if(UjUaYSwcyI == XOMFrdrULU){OfKTqOMMde = true;}
      if(MLqOWkBUWq == SQHRJzfPsc){REQEbPaiVE = true;}
      else if(SQHRJzfPsc == MLqOWkBUWq){uIMcwhZYmu = true;}
      if(kgMKlSZAmG == mGNdGMVDLd){nRyUSWfqHT = true;}
      if(sVwXNJmYUh == QUkWffijrq){CGNTEpdITO = true;}
      if(CaIaPkCVoW == AaKwEpcold){iATMzFcKEd = true;}
      while(mGNdGMVDLd == kgMKlSZAmG){YcunnqykwA = true;}
      while(QUkWffijrq == QUkWffijrq){nDuhxOKTkX = true;}
      while(AaKwEpcold == AaKwEpcold){OaiWPnhpgc = true;}
      if(ecKWkOVpUL == true){ecKWkOVpUL = false;}
      if(xrQUryfjlc == true){xrQUryfjlc = false;}
      if(PuXBbMwRZP == true){PuXBbMwRZP = false;}
      if(jgRhymJOkQ == true){jgRhymJOkQ = false;}
      if(KsPftHJpEG == true){KsPftHJpEG = false;}
      if(KsDINiEItY == true){KsDINiEItY = false;}
      if(REQEbPaiVE == true){REQEbPaiVE = false;}
      if(nRyUSWfqHT == true){nRyUSWfqHT = false;}
      if(CGNTEpdITO == true){CGNTEpdITO = false;}
      if(iATMzFcKEd == true){iATMzFcKEd = false;}
      if(gaTzRsthpp == true){gaTzRsthpp = false;}
      if(DNBZWLqwzk == true){DNBZWLqwzk = false;}
      if(lROHVmxlUM == true){lROHVmxlUM = false;}
      if(tUmcmamNBL == true){tUmcmamNBL = false;}
      if(wuScLUztpm == true){wuScLUztpm = false;}
      if(OfKTqOMMde == true){OfKTqOMMde = false;}
      if(uIMcwhZYmu == true){uIMcwhZYmu = false;}
      if(YcunnqykwA == true){YcunnqykwA = false;}
      if(nDuhxOKTkX == true){nDuhxOKTkX = false;}
      if(OaiWPnhpgc == true){OaiWPnhpgc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMYQVKHXQA
{ 
  void lPTnHYlVVE()
  { 
      bool ixfDMuTzbc = false;
      bool VmMWDFBAhJ = false;
      bool rrluDRKTVV = false;
      bool mitiEPkNKY = false;
      bool VWKbgFstko = false;
      bool zgtpdqKkzt = false;
      bool jAcGomrcSm = false;
      bool UnpImUgKNx = false;
      bool YQhgVFoEFM = false;
      bool FzNPoVsElt = false;
      bool MPayTLqlCI = false;
      bool JAWBVTRujj = false;
      bool ynXFhUZZSR = false;
      bool acXSkIojMK = false;
      bool NCBwDEcMtV = false;
      bool DxTCwYqVQz = false;
      bool kRSjhfbEQM = false;
      bool dhiYVumbCc = false;
      bool rMfxOcIVVM = false;
      bool RTTNYwjQOW = false;
      string dypraegKdT;
      string LLIrArVqiy;
      string guIQyxIjaN;
      string ayttSUHJBz;
      string aZMhmoresD;
      string eXNTaipYtc;
      string WwjPsMQOYf;
      string kMoiXHiZdJ;
      string EcpWiCkaTj;
      string diPXcdowoZ;
      string XdGNRSiduS;
      string APtjXsFMgp;
      string bpuoCBwQGs;
      string SlkDkaWcEQ;
      string TGeAjNneAi;
      string XbPyyhhRLQ;
      string VSXCANeqzw;
      string WcHQWVLtEn;
      string NQQWUpVlED;
      string sFRntBhbAV;
      if(dypraegKdT == XdGNRSiduS){ixfDMuTzbc = true;}
      else if(XdGNRSiduS == dypraegKdT){MPayTLqlCI = true;}
      if(LLIrArVqiy == APtjXsFMgp){VmMWDFBAhJ = true;}
      else if(APtjXsFMgp == LLIrArVqiy){JAWBVTRujj = true;}
      if(guIQyxIjaN == bpuoCBwQGs){rrluDRKTVV = true;}
      else if(bpuoCBwQGs == guIQyxIjaN){ynXFhUZZSR = true;}
      if(ayttSUHJBz == SlkDkaWcEQ){mitiEPkNKY = true;}
      else if(SlkDkaWcEQ == ayttSUHJBz){acXSkIojMK = true;}
      if(aZMhmoresD == TGeAjNneAi){VWKbgFstko = true;}
      else if(TGeAjNneAi == aZMhmoresD){NCBwDEcMtV = true;}
      if(eXNTaipYtc == XbPyyhhRLQ){zgtpdqKkzt = true;}
      else if(XbPyyhhRLQ == eXNTaipYtc){DxTCwYqVQz = true;}
      if(WwjPsMQOYf == VSXCANeqzw){jAcGomrcSm = true;}
      else if(VSXCANeqzw == WwjPsMQOYf){kRSjhfbEQM = true;}
      if(kMoiXHiZdJ == WcHQWVLtEn){UnpImUgKNx = true;}
      if(EcpWiCkaTj == NQQWUpVlED){YQhgVFoEFM = true;}
      if(diPXcdowoZ == sFRntBhbAV){FzNPoVsElt = true;}
      while(WcHQWVLtEn == kMoiXHiZdJ){dhiYVumbCc = true;}
      while(NQQWUpVlED == NQQWUpVlED){rMfxOcIVVM = true;}
      while(sFRntBhbAV == sFRntBhbAV){RTTNYwjQOW = true;}
      if(ixfDMuTzbc == true){ixfDMuTzbc = false;}
      if(VmMWDFBAhJ == true){VmMWDFBAhJ = false;}
      if(rrluDRKTVV == true){rrluDRKTVV = false;}
      if(mitiEPkNKY == true){mitiEPkNKY = false;}
      if(VWKbgFstko == true){VWKbgFstko = false;}
      if(zgtpdqKkzt == true){zgtpdqKkzt = false;}
      if(jAcGomrcSm == true){jAcGomrcSm = false;}
      if(UnpImUgKNx == true){UnpImUgKNx = false;}
      if(YQhgVFoEFM == true){YQhgVFoEFM = false;}
      if(FzNPoVsElt == true){FzNPoVsElt = false;}
      if(MPayTLqlCI == true){MPayTLqlCI = false;}
      if(JAWBVTRujj == true){JAWBVTRujj = false;}
      if(ynXFhUZZSR == true){ynXFhUZZSR = false;}
      if(acXSkIojMK == true){acXSkIojMK = false;}
      if(NCBwDEcMtV == true){NCBwDEcMtV = false;}
      if(DxTCwYqVQz == true){DxTCwYqVQz = false;}
      if(kRSjhfbEQM == true){kRSjhfbEQM = false;}
      if(dhiYVumbCc == true){dhiYVumbCc = false;}
      if(rMfxOcIVVM == true){rMfxOcIVVM = false;}
      if(RTTNYwjQOW == true){RTTNYwjQOW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXPEISZPLA
{ 
  void VpGSwoBaCd()
  { 
      bool YmiiqodxIR = false;
      bool pFhUZLIOtq = false;
      bool pfSRStGXMx = false;
      bool OmzyAFQYSm = false;
      bool lVJmsnjQFa = false;
      bool FMZObrTQQw = false;
      bool hGjLCDFiUT = false;
      bool uiuHFUWeXd = false;
      bool KpSlqCMkWH = false;
      bool kAIVEflykp = false;
      bool iAuleVQSJH = false;
      bool VosllqmxTz = false;
      bool qUMMhuaZCY = false;
      bool iYthuKufGU = false;
      bool lsbPlwGVjN = false;
      bool rndkzOmhEj = false;
      bool tqQjYxuLqa = false;
      bool wHpyNxrxak = false;
      bool nFoogtuIif = false;
      bool WMbWaucrpo = false;
      string maUKTfaIuW;
      string tlDcBisnTX;
      string mCrdtMramA;
      string jURLksklVW;
      string GFpwVPZjBT;
      string EliwokhqPG;
      string mzVumZTrrI;
      string xHSxQhLwHe;
      string mIZTwxkVVA;
      string KtVOiHiuJu;
      string wgqsVxTleG;
      string YlikSeZByo;
      string nxVryDkDNJ;
      string yPmLiFRgyy;
      string dypOaXKkwE;
      string hhxTHyLzuS;
      string LPXVIIzXCM;
      string MrDzLoHGQZ;
      string sAHJbQSSEj;
      string tRlelNaUGR;
      if(maUKTfaIuW == wgqsVxTleG){YmiiqodxIR = true;}
      else if(wgqsVxTleG == maUKTfaIuW){iAuleVQSJH = true;}
      if(tlDcBisnTX == YlikSeZByo){pFhUZLIOtq = true;}
      else if(YlikSeZByo == tlDcBisnTX){VosllqmxTz = true;}
      if(mCrdtMramA == nxVryDkDNJ){pfSRStGXMx = true;}
      else if(nxVryDkDNJ == mCrdtMramA){qUMMhuaZCY = true;}
      if(jURLksklVW == yPmLiFRgyy){OmzyAFQYSm = true;}
      else if(yPmLiFRgyy == jURLksklVW){iYthuKufGU = true;}
      if(GFpwVPZjBT == dypOaXKkwE){lVJmsnjQFa = true;}
      else if(dypOaXKkwE == GFpwVPZjBT){lsbPlwGVjN = true;}
      if(EliwokhqPG == hhxTHyLzuS){FMZObrTQQw = true;}
      else if(hhxTHyLzuS == EliwokhqPG){rndkzOmhEj = true;}
      if(mzVumZTrrI == LPXVIIzXCM){hGjLCDFiUT = true;}
      else if(LPXVIIzXCM == mzVumZTrrI){tqQjYxuLqa = true;}
      if(xHSxQhLwHe == MrDzLoHGQZ){uiuHFUWeXd = true;}
      if(mIZTwxkVVA == sAHJbQSSEj){KpSlqCMkWH = true;}
      if(KtVOiHiuJu == tRlelNaUGR){kAIVEflykp = true;}
      while(MrDzLoHGQZ == xHSxQhLwHe){wHpyNxrxak = true;}
      while(sAHJbQSSEj == sAHJbQSSEj){nFoogtuIif = true;}
      while(tRlelNaUGR == tRlelNaUGR){WMbWaucrpo = true;}
      if(YmiiqodxIR == true){YmiiqodxIR = false;}
      if(pFhUZLIOtq == true){pFhUZLIOtq = false;}
      if(pfSRStGXMx == true){pfSRStGXMx = false;}
      if(OmzyAFQYSm == true){OmzyAFQYSm = false;}
      if(lVJmsnjQFa == true){lVJmsnjQFa = false;}
      if(FMZObrTQQw == true){FMZObrTQQw = false;}
      if(hGjLCDFiUT == true){hGjLCDFiUT = false;}
      if(uiuHFUWeXd == true){uiuHFUWeXd = false;}
      if(KpSlqCMkWH == true){KpSlqCMkWH = false;}
      if(kAIVEflykp == true){kAIVEflykp = false;}
      if(iAuleVQSJH == true){iAuleVQSJH = false;}
      if(VosllqmxTz == true){VosllqmxTz = false;}
      if(qUMMhuaZCY == true){qUMMhuaZCY = false;}
      if(iYthuKufGU == true){iYthuKufGU = false;}
      if(lsbPlwGVjN == true){lsbPlwGVjN = false;}
      if(rndkzOmhEj == true){rndkzOmhEj = false;}
      if(tqQjYxuLqa == true){tqQjYxuLqa = false;}
      if(wHpyNxrxak == true){wHpyNxrxak = false;}
      if(nFoogtuIif == true){nFoogtuIif = false;}
      if(WMbWaucrpo == true){WMbWaucrpo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZKVWTICWOR
{ 
  void yxxzGWmFSO()
  { 
      bool BdMVkJeqmS = false;
      bool ibHtehyTzQ = false;
      bool qiASrucdqw = false;
      bool kURUsJKKBT = false;
      bool DzmOsepsLy = false;
      bool NqbduSctdp = false;
      bool fAApgOKmBV = false;
      bool XnReNqwkYM = false;
      bool FjSsitrmYa = false;
      bool fQfLnDzwhe = false;
      bool TDrpaYYwQE = false;
      bool VrUQjwgGGm = false;
      bool VWNZoHIGqJ = false;
      bool qADtrBrcSK = false;
      bool UuWUFnuOaq = false;
      bool VrotIxpRAS = false;
      bool QSFGMUoZXi = false;
      bool EEnwSZzrUB = false;
      bool LseznyKIlu = false;
      bool LZcztBpQHj = false;
      string YmJqGNtqgs;
      string aeDeqkjSNR;
      string wxnFDUuXkx;
      string VVsUnrtwBG;
      string rjMUgRdkwJ;
      string YxfHsazDnk;
      string SVGjXElhqz;
      string pmQGZLjSYl;
      string qJabXXplbM;
      string rqIPnVdbwb;
      string eutxSkfYgg;
      string qfeBtIudLA;
      string NAGdHzeBSE;
      string hHWwGuOdJm;
      string qREtVLLHUe;
      string azQwOenQpS;
      string GeGcziJhty;
      string tQUYIwuMIu;
      string mXfmdhqZhb;
      string GynpgLKatm;
      if(YmJqGNtqgs == eutxSkfYgg){BdMVkJeqmS = true;}
      else if(eutxSkfYgg == YmJqGNtqgs){TDrpaYYwQE = true;}
      if(aeDeqkjSNR == qfeBtIudLA){ibHtehyTzQ = true;}
      else if(qfeBtIudLA == aeDeqkjSNR){VrUQjwgGGm = true;}
      if(wxnFDUuXkx == NAGdHzeBSE){qiASrucdqw = true;}
      else if(NAGdHzeBSE == wxnFDUuXkx){VWNZoHIGqJ = true;}
      if(VVsUnrtwBG == hHWwGuOdJm){kURUsJKKBT = true;}
      else if(hHWwGuOdJm == VVsUnrtwBG){qADtrBrcSK = true;}
      if(rjMUgRdkwJ == qREtVLLHUe){DzmOsepsLy = true;}
      else if(qREtVLLHUe == rjMUgRdkwJ){UuWUFnuOaq = true;}
      if(YxfHsazDnk == azQwOenQpS){NqbduSctdp = true;}
      else if(azQwOenQpS == YxfHsazDnk){VrotIxpRAS = true;}
      if(SVGjXElhqz == GeGcziJhty){fAApgOKmBV = true;}
      else if(GeGcziJhty == SVGjXElhqz){QSFGMUoZXi = true;}
      if(pmQGZLjSYl == tQUYIwuMIu){XnReNqwkYM = true;}
      if(qJabXXplbM == mXfmdhqZhb){FjSsitrmYa = true;}
      if(rqIPnVdbwb == GynpgLKatm){fQfLnDzwhe = true;}
      while(tQUYIwuMIu == pmQGZLjSYl){EEnwSZzrUB = true;}
      while(mXfmdhqZhb == mXfmdhqZhb){LseznyKIlu = true;}
      while(GynpgLKatm == GynpgLKatm){LZcztBpQHj = true;}
      if(BdMVkJeqmS == true){BdMVkJeqmS = false;}
      if(ibHtehyTzQ == true){ibHtehyTzQ = false;}
      if(qiASrucdqw == true){qiASrucdqw = false;}
      if(kURUsJKKBT == true){kURUsJKKBT = false;}
      if(DzmOsepsLy == true){DzmOsepsLy = false;}
      if(NqbduSctdp == true){NqbduSctdp = false;}
      if(fAApgOKmBV == true){fAApgOKmBV = false;}
      if(XnReNqwkYM == true){XnReNqwkYM = false;}
      if(FjSsitrmYa == true){FjSsitrmYa = false;}
      if(fQfLnDzwhe == true){fQfLnDzwhe = false;}
      if(TDrpaYYwQE == true){TDrpaYYwQE = false;}
      if(VrUQjwgGGm == true){VrUQjwgGGm = false;}
      if(VWNZoHIGqJ == true){VWNZoHIGqJ = false;}
      if(qADtrBrcSK == true){qADtrBrcSK = false;}
      if(UuWUFnuOaq == true){UuWUFnuOaq = false;}
      if(VrotIxpRAS == true){VrotIxpRAS = false;}
      if(QSFGMUoZXi == true){QSFGMUoZXi = false;}
      if(EEnwSZzrUB == true){EEnwSZzrUB = false;}
      if(LseznyKIlu == true){LseznyKIlu = false;}
      if(LZcztBpQHj == true){LZcztBpQHj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGHWCMTZIL
{ 
  void AjhVfEeEdN()
  { 
      bool yoXMGfnCcP = false;
      bool EUwryyaJMZ = false;
      bool sdaWegNYTy = false;
      bool fOXCXOECcU = false;
      bool WdHZkGmfpX = false;
      bool WtIxKUOBhY = false;
      bool ROiejowtTj = false;
      bool tXfrDOVAlX = false;
      bool shiwakGaqD = false;
      bool zCUDCHtcou = false;
      bool JsMGcyNPsu = false;
      bool zNPJejemDy = false;
      bool hVCQkrCcow = false;
      bool UrLpNAUcSc = false;
      bool XphuDkmKXS = false;
      bool bHYqNnquVk = false;
      bool wjaxaGCZue = false;
      bool OCTaZqnGNz = false;
      bool EqFVTNTTbZ = false;
      bool JZHhfmPjUw = false;
      string OXyuxtcsio;
      string zjcsJFkdeQ;
      string gKcYVmUOkK;
      string pYDUgijzbz;
      string GOEIElbxag;
      string ZbepPEuYZJ;
      string ZOIYyZfILZ;
      string UlBfKSFUTj;
      string LWnDkOtNFc;
      string nKZRZrGfJe;
      string GTkAMmZyfx;
      string zZFoyCZEmj;
      string eRDikJMiGS;
      string LYKodqlmqx;
      string nuhHcNFjTW;
      string RBrYznPCPC;
      string aprMkZOPLG;
      string QlNpuijuFW;
      string EbPiAKgkoo;
      string biXnVxDUWD;
      if(OXyuxtcsio == GTkAMmZyfx){yoXMGfnCcP = true;}
      else if(GTkAMmZyfx == OXyuxtcsio){JsMGcyNPsu = true;}
      if(zjcsJFkdeQ == zZFoyCZEmj){EUwryyaJMZ = true;}
      else if(zZFoyCZEmj == zjcsJFkdeQ){zNPJejemDy = true;}
      if(gKcYVmUOkK == eRDikJMiGS){sdaWegNYTy = true;}
      else if(eRDikJMiGS == gKcYVmUOkK){hVCQkrCcow = true;}
      if(pYDUgijzbz == LYKodqlmqx){fOXCXOECcU = true;}
      else if(LYKodqlmqx == pYDUgijzbz){UrLpNAUcSc = true;}
      if(GOEIElbxag == nuhHcNFjTW){WdHZkGmfpX = true;}
      else if(nuhHcNFjTW == GOEIElbxag){XphuDkmKXS = true;}
      if(ZbepPEuYZJ == RBrYznPCPC){WtIxKUOBhY = true;}
      else if(RBrYznPCPC == ZbepPEuYZJ){bHYqNnquVk = true;}
      if(ZOIYyZfILZ == aprMkZOPLG){ROiejowtTj = true;}
      else if(aprMkZOPLG == ZOIYyZfILZ){wjaxaGCZue = true;}
      if(UlBfKSFUTj == QlNpuijuFW){tXfrDOVAlX = true;}
      if(LWnDkOtNFc == EbPiAKgkoo){shiwakGaqD = true;}
      if(nKZRZrGfJe == biXnVxDUWD){zCUDCHtcou = true;}
      while(QlNpuijuFW == UlBfKSFUTj){OCTaZqnGNz = true;}
      while(EbPiAKgkoo == EbPiAKgkoo){EqFVTNTTbZ = true;}
      while(biXnVxDUWD == biXnVxDUWD){JZHhfmPjUw = true;}
      if(yoXMGfnCcP == true){yoXMGfnCcP = false;}
      if(EUwryyaJMZ == true){EUwryyaJMZ = false;}
      if(sdaWegNYTy == true){sdaWegNYTy = false;}
      if(fOXCXOECcU == true){fOXCXOECcU = false;}
      if(WdHZkGmfpX == true){WdHZkGmfpX = false;}
      if(WtIxKUOBhY == true){WtIxKUOBhY = false;}
      if(ROiejowtTj == true){ROiejowtTj = false;}
      if(tXfrDOVAlX == true){tXfrDOVAlX = false;}
      if(shiwakGaqD == true){shiwakGaqD = false;}
      if(zCUDCHtcou == true){zCUDCHtcou = false;}
      if(JsMGcyNPsu == true){JsMGcyNPsu = false;}
      if(zNPJejemDy == true){zNPJejemDy = false;}
      if(hVCQkrCcow == true){hVCQkrCcow = false;}
      if(UrLpNAUcSc == true){UrLpNAUcSc = false;}
      if(XphuDkmKXS == true){XphuDkmKXS = false;}
      if(bHYqNnquVk == true){bHYqNnquVk = false;}
      if(wjaxaGCZue == true){wjaxaGCZue = false;}
      if(OCTaZqnGNz == true){OCTaZqnGNz = false;}
      if(EqFVTNTTbZ == true){EqFVTNTTbZ = false;}
      if(JZHhfmPjUw == true){JZHhfmPjUw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SULFVNJOZV
{ 
  void msTgxugunY()
  { 
      bool szgbLDMDcJ = false;
      bool BKQkZTdoqK = false;
      bool nWTNUsGyYm = false;
      bool hQbatMwQOi = false;
      bool eZbEsdRDrd = false;
      bool aNAmKWeSHS = false;
      bool wNdpajipqN = false;
      bool WNZHeOuOTp = false;
      bool aCFuLUPnPX = false;
      bool gcIumQwlcJ = false;
      bool ubLeGMmsHw = false;
      bool aQzQqsIhdG = false;
      bool UtaTgsEeUN = false;
      bool SJkKuzqanz = false;
      bool hWgSwPdrDs = false;
      bool INHWnABryM = false;
      bool HIXtdRfoUr = false;
      bool CgsdYxNHXQ = false;
      bool PMabFEBNVt = false;
      bool yycbrZzmnd = false;
      string rNBSutWicd;
      string bTJwRoljIO;
      string YWzCGgfNdz;
      string fdAPMkXPiE;
      string SDXluKBUPu;
      string mChMrVOyLO;
      string NIEdxyTtjf;
      string RWAEwUyNGw;
      string fLyiLdumWp;
      string WYDUpJzsnx;
      string pHkidQCdQX;
      string XBqOiCKVST;
      string CfXsJrSeOl;
      string VEYJFYZOEu;
      string bRWzSVgoln;
      string zdaUtKiqZk;
      string xWPdBSbhIJ;
      string buQWqkJYan;
      string LcramqdEOu;
      string oioSxECrxz;
      if(rNBSutWicd == pHkidQCdQX){szgbLDMDcJ = true;}
      else if(pHkidQCdQX == rNBSutWicd){ubLeGMmsHw = true;}
      if(bTJwRoljIO == XBqOiCKVST){BKQkZTdoqK = true;}
      else if(XBqOiCKVST == bTJwRoljIO){aQzQqsIhdG = true;}
      if(YWzCGgfNdz == CfXsJrSeOl){nWTNUsGyYm = true;}
      else if(CfXsJrSeOl == YWzCGgfNdz){UtaTgsEeUN = true;}
      if(fdAPMkXPiE == VEYJFYZOEu){hQbatMwQOi = true;}
      else if(VEYJFYZOEu == fdAPMkXPiE){SJkKuzqanz = true;}
      if(SDXluKBUPu == bRWzSVgoln){eZbEsdRDrd = true;}
      else if(bRWzSVgoln == SDXluKBUPu){hWgSwPdrDs = true;}
      if(mChMrVOyLO == zdaUtKiqZk){aNAmKWeSHS = true;}
      else if(zdaUtKiqZk == mChMrVOyLO){INHWnABryM = true;}
      if(NIEdxyTtjf == xWPdBSbhIJ){wNdpajipqN = true;}
      else if(xWPdBSbhIJ == NIEdxyTtjf){HIXtdRfoUr = true;}
      if(RWAEwUyNGw == buQWqkJYan){WNZHeOuOTp = true;}
      if(fLyiLdumWp == LcramqdEOu){aCFuLUPnPX = true;}
      if(WYDUpJzsnx == oioSxECrxz){gcIumQwlcJ = true;}
      while(buQWqkJYan == RWAEwUyNGw){CgsdYxNHXQ = true;}
      while(LcramqdEOu == LcramqdEOu){PMabFEBNVt = true;}
      while(oioSxECrxz == oioSxECrxz){yycbrZzmnd = true;}
      if(szgbLDMDcJ == true){szgbLDMDcJ = false;}
      if(BKQkZTdoqK == true){BKQkZTdoqK = false;}
      if(nWTNUsGyYm == true){nWTNUsGyYm = false;}
      if(hQbatMwQOi == true){hQbatMwQOi = false;}
      if(eZbEsdRDrd == true){eZbEsdRDrd = false;}
      if(aNAmKWeSHS == true){aNAmKWeSHS = false;}
      if(wNdpajipqN == true){wNdpajipqN = false;}
      if(WNZHeOuOTp == true){WNZHeOuOTp = false;}
      if(aCFuLUPnPX == true){aCFuLUPnPX = false;}
      if(gcIumQwlcJ == true){gcIumQwlcJ = false;}
      if(ubLeGMmsHw == true){ubLeGMmsHw = false;}
      if(aQzQqsIhdG == true){aQzQqsIhdG = false;}
      if(UtaTgsEeUN == true){UtaTgsEeUN = false;}
      if(SJkKuzqanz == true){SJkKuzqanz = false;}
      if(hWgSwPdrDs == true){hWgSwPdrDs = false;}
      if(INHWnABryM == true){INHWnABryM = false;}
      if(HIXtdRfoUr == true){HIXtdRfoUr = false;}
      if(CgsdYxNHXQ == true){CgsdYxNHXQ = false;}
      if(PMabFEBNVt == true){PMabFEBNVt = false;}
      if(yycbrZzmnd == true){yycbrZzmnd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YHMTDCSBKJ
{ 
  void othxprLxMo()
  { 
      bool OIENtVpECB = false;
      bool UdWcmsXowt = false;
      bool lTJnpLARbJ = false;
      bool fzCGKhiPHb = false;
      bool BFtxOsfHwG = false;
      bool MjMGKtyQWh = false;
      bool UXcsVVbPSF = false;
      bool JIgTrgZMYx = false;
      bool fsVUxwlwwQ = false;
      bool iSsZGdbBbs = false;
      bool RPopxECsNd = false;
      bool UlqZBbBHwZ = false;
      bool jeTBVqPHMO = false;
      bool EXjfeQDeXr = false;
      bool sshSwxaSXe = false;
      bool bUFCJlumUG = false;
      bool oufzYwBLtk = false;
      bool XWjDfpxBFX = false;
      bool PwihmjShWs = false;
      bool UQKRDxMhsz = false;
      string kUBAsMZitZ;
      string XBTmhYfpRj;
      string GNfBKxNEXF;
      string zjlUFhiCpC;
      string AQeFQGVHIa;
      string aGQiLWnAou;
      string zUKnanPygz;
      string pczOjohajE;
      string bFwxesSCIi;
      string thNtDeFqec;
      string pWaIkxGCzV;
      string nNQkStYNJg;
      string VMoyFHPELE;
      string jquGNEemMg;
      string lPDltfRbbJ;
      string GrgxHdgbCc;
      string gBqtlwRJXN;
      string OkBbtFICEY;
      string pncBxrKxzj;
      string XDkiAkYJAx;
      if(kUBAsMZitZ == pWaIkxGCzV){OIENtVpECB = true;}
      else if(pWaIkxGCzV == kUBAsMZitZ){RPopxECsNd = true;}
      if(XBTmhYfpRj == nNQkStYNJg){UdWcmsXowt = true;}
      else if(nNQkStYNJg == XBTmhYfpRj){UlqZBbBHwZ = true;}
      if(GNfBKxNEXF == VMoyFHPELE){lTJnpLARbJ = true;}
      else if(VMoyFHPELE == GNfBKxNEXF){jeTBVqPHMO = true;}
      if(zjlUFhiCpC == jquGNEemMg){fzCGKhiPHb = true;}
      else if(jquGNEemMg == zjlUFhiCpC){EXjfeQDeXr = true;}
      if(AQeFQGVHIa == lPDltfRbbJ){BFtxOsfHwG = true;}
      else if(lPDltfRbbJ == AQeFQGVHIa){sshSwxaSXe = true;}
      if(aGQiLWnAou == GrgxHdgbCc){MjMGKtyQWh = true;}
      else if(GrgxHdgbCc == aGQiLWnAou){bUFCJlumUG = true;}
      if(zUKnanPygz == gBqtlwRJXN){UXcsVVbPSF = true;}
      else if(gBqtlwRJXN == zUKnanPygz){oufzYwBLtk = true;}
      if(pczOjohajE == OkBbtFICEY){JIgTrgZMYx = true;}
      if(bFwxesSCIi == pncBxrKxzj){fsVUxwlwwQ = true;}
      if(thNtDeFqec == XDkiAkYJAx){iSsZGdbBbs = true;}
      while(OkBbtFICEY == pczOjohajE){XWjDfpxBFX = true;}
      while(pncBxrKxzj == pncBxrKxzj){PwihmjShWs = true;}
      while(XDkiAkYJAx == XDkiAkYJAx){UQKRDxMhsz = true;}
      if(OIENtVpECB == true){OIENtVpECB = false;}
      if(UdWcmsXowt == true){UdWcmsXowt = false;}
      if(lTJnpLARbJ == true){lTJnpLARbJ = false;}
      if(fzCGKhiPHb == true){fzCGKhiPHb = false;}
      if(BFtxOsfHwG == true){BFtxOsfHwG = false;}
      if(MjMGKtyQWh == true){MjMGKtyQWh = false;}
      if(UXcsVVbPSF == true){UXcsVVbPSF = false;}
      if(JIgTrgZMYx == true){JIgTrgZMYx = false;}
      if(fsVUxwlwwQ == true){fsVUxwlwwQ = false;}
      if(iSsZGdbBbs == true){iSsZGdbBbs = false;}
      if(RPopxECsNd == true){RPopxECsNd = false;}
      if(UlqZBbBHwZ == true){UlqZBbBHwZ = false;}
      if(jeTBVqPHMO == true){jeTBVqPHMO = false;}
      if(EXjfeQDeXr == true){EXjfeQDeXr = false;}
      if(sshSwxaSXe == true){sshSwxaSXe = false;}
      if(bUFCJlumUG == true){bUFCJlumUG = false;}
      if(oufzYwBLtk == true){oufzYwBLtk = false;}
      if(XWjDfpxBFX == true){XWjDfpxBFX = false;}
      if(PwihmjShWs == true){PwihmjShWs = false;}
      if(UQKRDxMhsz == true){UQKRDxMhsz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSQYZNBLLU
{ 
  void CwEegaHFMn()
  { 
      bool aAhwGXcFzM = false;
      bool whBPaCVXqP = false;
      bool hHXRbuRinx = false;
      bool tFYQfhuyLF = false;
      bool SNJRClZsNI = false;
      bool kjyGxTcPTL = false;
      bool FsRCSqJkjr = false;
      bool GWMlxUyFPo = false;
      bool UXVfLKHRSM = false;
      bool FfdzzYwHzK = false;
      bool coIVCNXLJb = false;
      bool UWAeqhXkpH = false;
      bool iqRXlasMlY = false;
      bool YqGEMfOzdx = false;
      bool muIqqifzIR = false;
      bool AKQqblWkia = false;
      bool UKZkDdQuSK = false;
      bool SYHrUmiagD = false;
      bool ttDUXOZOba = false;
      bool IdQCcbVXmM = false;
      string IBSwaQLxgK;
      string lDruSslLwG;
      string OKcNzdRyep;
      string HypXHuGDjY;
      string VqnjDKaPtj;
      string qeKhfyXFwx;
      string yNSpDnMUmW;
      string miaWkWWsJn;
      string DCEuzbmHqJ;
      string WAGmZIYxfP;
      string xFbWwIEnxJ;
      string aewHtwIWqb;
      string BFcdzmbnwc;
      string xZNsqxZgyq;
      string XzJhhrDysd;
      string zBFEOrcyWJ;
      string fQqULBQCQw;
      string WbYzECuuwH;
      string idtScwTJey;
      string UbJoLGHoVf;
      if(IBSwaQLxgK == xFbWwIEnxJ){aAhwGXcFzM = true;}
      else if(xFbWwIEnxJ == IBSwaQLxgK){coIVCNXLJb = true;}
      if(lDruSslLwG == aewHtwIWqb){whBPaCVXqP = true;}
      else if(aewHtwIWqb == lDruSslLwG){UWAeqhXkpH = true;}
      if(OKcNzdRyep == BFcdzmbnwc){hHXRbuRinx = true;}
      else if(BFcdzmbnwc == OKcNzdRyep){iqRXlasMlY = true;}
      if(HypXHuGDjY == xZNsqxZgyq){tFYQfhuyLF = true;}
      else if(xZNsqxZgyq == HypXHuGDjY){YqGEMfOzdx = true;}
      if(VqnjDKaPtj == XzJhhrDysd){SNJRClZsNI = true;}
      else if(XzJhhrDysd == VqnjDKaPtj){muIqqifzIR = true;}
      if(qeKhfyXFwx == zBFEOrcyWJ){kjyGxTcPTL = true;}
      else if(zBFEOrcyWJ == qeKhfyXFwx){AKQqblWkia = true;}
      if(yNSpDnMUmW == fQqULBQCQw){FsRCSqJkjr = true;}
      else if(fQqULBQCQw == yNSpDnMUmW){UKZkDdQuSK = true;}
      if(miaWkWWsJn == WbYzECuuwH){GWMlxUyFPo = true;}
      if(DCEuzbmHqJ == idtScwTJey){UXVfLKHRSM = true;}
      if(WAGmZIYxfP == UbJoLGHoVf){FfdzzYwHzK = true;}
      while(WbYzECuuwH == miaWkWWsJn){SYHrUmiagD = true;}
      while(idtScwTJey == idtScwTJey){ttDUXOZOba = true;}
      while(UbJoLGHoVf == UbJoLGHoVf){IdQCcbVXmM = true;}
      if(aAhwGXcFzM == true){aAhwGXcFzM = false;}
      if(whBPaCVXqP == true){whBPaCVXqP = false;}
      if(hHXRbuRinx == true){hHXRbuRinx = false;}
      if(tFYQfhuyLF == true){tFYQfhuyLF = false;}
      if(SNJRClZsNI == true){SNJRClZsNI = false;}
      if(kjyGxTcPTL == true){kjyGxTcPTL = false;}
      if(FsRCSqJkjr == true){FsRCSqJkjr = false;}
      if(GWMlxUyFPo == true){GWMlxUyFPo = false;}
      if(UXVfLKHRSM == true){UXVfLKHRSM = false;}
      if(FfdzzYwHzK == true){FfdzzYwHzK = false;}
      if(coIVCNXLJb == true){coIVCNXLJb = false;}
      if(UWAeqhXkpH == true){UWAeqhXkpH = false;}
      if(iqRXlasMlY == true){iqRXlasMlY = false;}
      if(YqGEMfOzdx == true){YqGEMfOzdx = false;}
      if(muIqqifzIR == true){muIqqifzIR = false;}
      if(AKQqblWkia == true){AKQqblWkia = false;}
      if(UKZkDdQuSK == true){UKZkDdQuSK = false;}
      if(SYHrUmiagD == true){SYHrUmiagD = false;}
      if(ttDUXOZOba == true){ttDUXOZOba = false;}
      if(IdQCcbVXmM == true){IdQCcbVXmM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BMXLERYLEB
{ 
  void CRshbeUSaF()
  { 
      bool UUFyrebPjT = false;
      bool DJPUlYPcoO = false;
      bool ESfpISXrXz = false;
      bool cNpyFUmIlJ = false;
      bool HUTiHJcddA = false;
      bool ktOtxCnPoZ = false;
      bool GiqjpoTROQ = false;
      bool lGqfGjyxhz = false;
      bool ptOXNizuAD = false;
      bool gXSMCXcirR = false;
      bool pKPMOeDhnM = false;
      bool DqgpjLUTWH = false;
      bool pXQKjNnech = false;
      bool HOEPIeeBJi = false;
      bool fQHnzopbbp = false;
      bool DILkbStEcA = false;
      bool qXFFEnlRhE = false;
      bool gTKnbYPcKt = false;
      bool XLClezDTmp = false;
      bool jaYIqHLBiL = false;
      string gDSLleMGPp;
      string VgqgYEPlQz;
      string MxzhZqsnpQ;
      string rSeHMEyZZK;
      string pDzFFXzbgb;
      string HQwceiDkku;
      string lXPyyCCjTT;
      string GoMGIJxtbC;
      string qQHNJaVCcc;
      string BModYSmBGC;
      string VPHNVREpTU;
      string kJIhDUQBnW;
      string gAGqRsAhhp;
      string VwmYgbIsrq;
      string WfhHqqEGaD;
      string BlMiVVIQub;
      string RWHdyoVjBb;
      string LWJxzBRzAa;
      string osGdnjjDDL;
      string SryQYAXDIC;
      if(gDSLleMGPp == VPHNVREpTU){UUFyrebPjT = true;}
      else if(VPHNVREpTU == gDSLleMGPp){pKPMOeDhnM = true;}
      if(VgqgYEPlQz == kJIhDUQBnW){DJPUlYPcoO = true;}
      else if(kJIhDUQBnW == VgqgYEPlQz){DqgpjLUTWH = true;}
      if(MxzhZqsnpQ == gAGqRsAhhp){ESfpISXrXz = true;}
      else if(gAGqRsAhhp == MxzhZqsnpQ){pXQKjNnech = true;}
      if(rSeHMEyZZK == VwmYgbIsrq){cNpyFUmIlJ = true;}
      else if(VwmYgbIsrq == rSeHMEyZZK){HOEPIeeBJi = true;}
      if(pDzFFXzbgb == WfhHqqEGaD){HUTiHJcddA = true;}
      else if(WfhHqqEGaD == pDzFFXzbgb){fQHnzopbbp = true;}
      if(HQwceiDkku == BlMiVVIQub){ktOtxCnPoZ = true;}
      else if(BlMiVVIQub == HQwceiDkku){DILkbStEcA = true;}
      if(lXPyyCCjTT == RWHdyoVjBb){GiqjpoTROQ = true;}
      else if(RWHdyoVjBb == lXPyyCCjTT){qXFFEnlRhE = true;}
      if(GoMGIJxtbC == LWJxzBRzAa){lGqfGjyxhz = true;}
      if(qQHNJaVCcc == osGdnjjDDL){ptOXNizuAD = true;}
      if(BModYSmBGC == SryQYAXDIC){gXSMCXcirR = true;}
      while(LWJxzBRzAa == GoMGIJxtbC){gTKnbYPcKt = true;}
      while(osGdnjjDDL == osGdnjjDDL){XLClezDTmp = true;}
      while(SryQYAXDIC == SryQYAXDIC){jaYIqHLBiL = true;}
      if(UUFyrebPjT == true){UUFyrebPjT = false;}
      if(DJPUlYPcoO == true){DJPUlYPcoO = false;}
      if(ESfpISXrXz == true){ESfpISXrXz = false;}
      if(cNpyFUmIlJ == true){cNpyFUmIlJ = false;}
      if(HUTiHJcddA == true){HUTiHJcddA = false;}
      if(ktOtxCnPoZ == true){ktOtxCnPoZ = false;}
      if(GiqjpoTROQ == true){GiqjpoTROQ = false;}
      if(lGqfGjyxhz == true){lGqfGjyxhz = false;}
      if(ptOXNizuAD == true){ptOXNizuAD = false;}
      if(gXSMCXcirR == true){gXSMCXcirR = false;}
      if(pKPMOeDhnM == true){pKPMOeDhnM = false;}
      if(DqgpjLUTWH == true){DqgpjLUTWH = false;}
      if(pXQKjNnech == true){pXQKjNnech = false;}
      if(HOEPIeeBJi == true){HOEPIeeBJi = false;}
      if(fQHnzopbbp == true){fQHnzopbbp = false;}
      if(DILkbStEcA == true){DILkbStEcA = false;}
      if(qXFFEnlRhE == true){qXFFEnlRhE = false;}
      if(gTKnbYPcKt == true){gTKnbYPcKt = false;}
      if(XLClezDTmp == true){XLClezDTmp = false;}
      if(jaYIqHLBiL == true){jaYIqHLBiL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBVYSMZUDS
{ 
  void bAaydcjkKR()
  { 
      bool KNmiwGaMYL = false;
      bool FHayiHuooy = false;
      bool ZUxqXyZDbP = false;
      bool aFwGoUXkxp = false;
      bool JJbPCXFyKF = false;
      bool pSJxIpQuLx = false;
      bool gWkJjzLTIN = false;
      bool jJqyoQshoz = false;
      bool sasWYIwyyz = false;
      bool EcZzJlXReD = false;
      bool MkpwUgaKHr = false;
      bool wiFLEFdNjb = false;
      bool CNVIJHirnC = false;
      bool raClmHkwBr = false;
      bool glpGDVWOtE = false;
      bool HKhCAyPglN = false;
      bool xhVFzUfTXx = false;
      bool ThLrtPWOFn = false;
      bool jUyjtgsAkn = false;
      bool qEJmtzQkGh = false;
      string yINnLlNDXO;
      string bYAklbjyWP;
      string fhJaGVhRtJ;
      string jLjFQbVjPD;
      string rplGjoRCpt;
      string OJUkhQzlho;
      string EuJOdPouTJ;
      string FziSXpuDpQ;
      string DebAtaqzXz;
      string ciCZzwgWbT;
      string zWifnOZBNr;
      string UwuQkYSIUC;
      string YpWTgWwJTa;
      string IYaWQfuwLe;
      string BpkeefmlnZ;
      string dXCZuJAPzR;
      string SPhmiwVYzE;
      string dWxoAiEroA;
      string iKUsxjWAbH;
      string ffxsMkHywh;
      if(yINnLlNDXO == zWifnOZBNr){KNmiwGaMYL = true;}
      else if(zWifnOZBNr == yINnLlNDXO){MkpwUgaKHr = true;}
      if(bYAklbjyWP == UwuQkYSIUC){FHayiHuooy = true;}
      else if(UwuQkYSIUC == bYAklbjyWP){wiFLEFdNjb = true;}
      if(fhJaGVhRtJ == YpWTgWwJTa){ZUxqXyZDbP = true;}
      else if(YpWTgWwJTa == fhJaGVhRtJ){CNVIJHirnC = true;}
      if(jLjFQbVjPD == IYaWQfuwLe){aFwGoUXkxp = true;}
      else if(IYaWQfuwLe == jLjFQbVjPD){raClmHkwBr = true;}
      if(rplGjoRCpt == BpkeefmlnZ){JJbPCXFyKF = true;}
      else if(BpkeefmlnZ == rplGjoRCpt){glpGDVWOtE = true;}
      if(OJUkhQzlho == dXCZuJAPzR){pSJxIpQuLx = true;}
      else if(dXCZuJAPzR == OJUkhQzlho){HKhCAyPglN = true;}
      if(EuJOdPouTJ == SPhmiwVYzE){gWkJjzLTIN = true;}
      else if(SPhmiwVYzE == EuJOdPouTJ){xhVFzUfTXx = true;}
      if(FziSXpuDpQ == dWxoAiEroA){jJqyoQshoz = true;}
      if(DebAtaqzXz == iKUsxjWAbH){sasWYIwyyz = true;}
      if(ciCZzwgWbT == ffxsMkHywh){EcZzJlXReD = true;}
      while(dWxoAiEroA == FziSXpuDpQ){ThLrtPWOFn = true;}
      while(iKUsxjWAbH == iKUsxjWAbH){jUyjtgsAkn = true;}
      while(ffxsMkHywh == ffxsMkHywh){qEJmtzQkGh = true;}
      if(KNmiwGaMYL == true){KNmiwGaMYL = false;}
      if(FHayiHuooy == true){FHayiHuooy = false;}
      if(ZUxqXyZDbP == true){ZUxqXyZDbP = false;}
      if(aFwGoUXkxp == true){aFwGoUXkxp = false;}
      if(JJbPCXFyKF == true){JJbPCXFyKF = false;}
      if(pSJxIpQuLx == true){pSJxIpQuLx = false;}
      if(gWkJjzLTIN == true){gWkJjzLTIN = false;}
      if(jJqyoQshoz == true){jJqyoQshoz = false;}
      if(sasWYIwyyz == true){sasWYIwyyz = false;}
      if(EcZzJlXReD == true){EcZzJlXReD = false;}
      if(MkpwUgaKHr == true){MkpwUgaKHr = false;}
      if(wiFLEFdNjb == true){wiFLEFdNjb = false;}
      if(CNVIJHirnC == true){CNVIJHirnC = false;}
      if(raClmHkwBr == true){raClmHkwBr = false;}
      if(glpGDVWOtE == true){glpGDVWOtE = false;}
      if(HKhCAyPglN == true){HKhCAyPglN = false;}
      if(xhVFzUfTXx == true){xhVFzUfTXx = false;}
      if(ThLrtPWOFn == true){ThLrtPWOFn = false;}
      if(jUyjtgsAkn == true){jUyjtgsAkn = false;}
      if(qEJmtzQkGh == true){qEJmtzQkGh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IOTSTTDRYX
{ 
  void PKNSbTYHVS()
  { 
      bool sxNUAptFPA = false;
      bool wGjFhXhuDa = false;
      bool flgUcUXTZr = false;
      bool JhaoefDrVM = false;
      bool LpwNqWMqbW = false;
      bool cylogHQsrf = false;
      bool SZfXqNftaB = false;
      bool ToYqOooScF = false;
      bool HgqDOLwlIW = false;
      bool PJzptkKYVc = false;
      bool qRPZCmYtZr = false;
      bool RxPmXkhbIf = false;
      bool RtlDlJpixd = false;
      bool dQxANpQQAb = false;
      bool lBLQERtMSI = false;
      bool DiQpLxfMnr = false;
      bool xowwOBAPZh = false;
      bool UQbgsPhUyU = false;
      bool PdQoZuAGnP = false;
      bool JEcHdxEPCD = false;
      string KiowXqYZlZ;
      string WsFcGnixxp;
      string eEqnehZHUS;
      string YnGPuPIGzl;
      string WdzfCdYLkO;
      string FhTnKFqARp;
      string QQFSBimpgp;
      string fbxLTBFLlA;
      string IOVFNpTREp;
      string YHnIVFXgeS;
      string qhduicjIUJ;
      string AfORgCuAFK;
      string OVkqRXnopN;
      string cXgSJajaVj;
      string GLxuorsWbS;
      string KXaTDUwmdL;
      string ouRGfbyuIG;
      string RTdUDDYpCY;
      string dRMWCFwMOn;
      string dxwKtLspPM;
      if(KiowXqYZlZ == qhduicjIUJ){sxNUAptFPA = true;}
      else if(qhduicjIUJ == KiowXqYZlZ){qRPZCmYtZr = true;}
      if(WsFcGnixxp == AfORgCuAFK){wGjFhXhuDa = true;}
      else if(AfORgCuAFK == WsFcGnixxp){RxPmXkhbIf = true;}
      if(eEqnehZHUS == OVkqRXnopN){flgUcUXTZr = true;}
      else if(OVkqRXnopN == eEqnehZHUS){RtlDlJpixd = true;}
      if(YnGPuPIGzl == cXgSJajaVj){JhaoefDrVM = true;}
      else if(cXgSJajaVj == YnGPuPIGzl){dQxANpQQAb = true;}
      if(WdzfCdYLkO == GLxuorsWbS){LpwNqWMqbW = true;}
      else if(GLxuorsWbS == WdzfCdYLkO){lBLQERtMSI = true;}
      if(FhTnKFqARp == KXaTDUwmdL){cylogHQsrf = true;}
      else if(KXaTDUwmdL == FhTnKFqARp){DiQpLxfMnr = true;}
      if(QQFSBimpgp == ouRGfbyuIG){SZfXqNftaB = true;}
      else if(ouRGfbyuIG == QQFSBimpgp){xowwOBAPZh = true;}
      if(fbxLTBFLlA == RTdUDDYpCY){ToYqOooScF = true;}
      if(IOVFNpTREp == dRMWCFwMOn){HgqDOLwlIW = true;}
      if(YHnIVFXgeS == dxwKtLspPM){PJzptkKYVc = true;}
      while(RTdUDDYpCY == fbxLTBFLlA){UQbgsPhUyU = true;}
      while(dRMWCFwMOn == dRMWCFwMOn){PdQoZuAGnP = true;}
      while(dxwKtLspPM == dxwKtLspPM){JEcHdxEPCD = true;}
      if(sxNUAptFPA == true){sxNUAptFPA = false;}
      if(wGjFhXhuDa == true){wGjFhXhuDa = false;}
      if(flgUcUXTZr == true){flgUcUXTZr = false;}
      if(JhaoefDrVM == true){JhaoefDrVM = false;}
      if(LpwNqWMqbW == true){LpwNqWMqbW = false;}
      if(cylogHQsrf == true){cylogHQsrf = false;}
      if(SZfXqNftaB == true){SZfXqNftaB = false;}
      if(ToYqOooScF == true){ToYqOooScF = false;}
      if(HgqDOLwlIW == true){HgqDOLwlIW = false;}
      if(PJzptkKYVc == true){PJzptkKYVc = false;}
      if(qRPZCmYtZr == true){qRPZCmYtZr = false;}
      if(RxPmXkhbIf == true){RxPmXkhbIf = false;}
      if(RtlDlJpixd == true){RtlDlJpixd = false;}
      if(dQxANpQQAb == true){dQxANpQQAb = false;}
      if(lBLQERtMSI == true){lBLQERtMSI = false;}
      if(DiQpLxfMnr == true){DiQpLxfMnr = false;}
      if(xowwOBAPZh == true){xowwOBAPZh = false;}
      if(UQbgsPhUyU == true){UQbgsPhUyU = false;}
      if(PdQoZuAGnP == true){PdQoZuAGnP = false;}
      if(JEcHdxEPCD == true){JEcHdxEPCD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUVJYNUERH
{ 
  void YHWHqJtKeE()
  { 
      bool FxeOMPZRtO = false;
      bool iFfgOEGZSK = false;
      bool CYQfjDcSnT = false;
      bool necLixyQcd = false;
      bool MRstDeCMWd = false;
      bool olbOOfgydJ = false;
      bool mGcZZDbTyR = false;
      bool GownxkeWcE = false;
      bool APwKeBDOwC = false;
      bool PAmTpGnSTz = false;
      bool DiNEXzomRc = false;
      bool AKUYIWKStY = false;
      bool ANWwBGCcxq = false;
      bool xMDdBRBqme = false;
      bool MQwSBFfNKT = false;
      bool uUYtzoLRDR = false;
      bool xMoafnHpWq = false;
      bool VTfPLjQEuw = false;
      bool ZnRdubmIeL = false;
      bool FjmVhAaVmM = false;
      string SHUlLnYJhh;
      string IbHjRNiFHK;
      string BAtLuTaukR;
      string AAyxjmczpp;
      string DEuoxPrqEM;
      string rQUzLRNJqq;
      string NdYPgHdKzd;
      string kiPQGxFENe;
      string bipXZifykR;
      string ZSIzcZeeHp;
      string lhqZbIBDrO;
      string MIwLPdmAox;
      string beYhERZPng;
      string RZxWssrPwR;
      string hbFWEQWxjy;
      string mepJOHIJVJ;
      string hlPLxmLYRV;
      string lWEXPAYCcn;
      string uceosmjmIl;
      string kitliuLtYR;
      if(SHUlLnYJhh == lhqZbIBDrO){FxeOMPZRtO = true;}
      else if(lhqZbIBDrO == SHUlLnYJhh){DiNEXzomRc = true;}
      if(IbHjRNiFHK == MIwLPdmAox){iFfgOEGZSK = true;}
      else if(MIwLPdmAox == IbHjRNiFHK){AKUYIWKStY = true;}
      if(BAtLuTaukR == beYhERZPng){CYQfjDcSnT = true;}
      else if(beYhERZPng == BAtLuTaukR){ANWwBGCcxq = true;}
      if(AAyxjmczpp == RZxWssrPwR){necLixyQcd = true;}
      else if(RZxWssrPwR == AAyxjmczpp){xMDdBRBqme = true;}
      if(DEuoxPrqEM == hbFWEQWxjy){MRstDeCMWd = true;}
      else if(hbFWEQWxjy == DEuoxPrqEM){MQwSBFfNKT = true;}
      if(rQUzLRNJqq == mepJOHIJVJ){olbOOfgydJ = true;}
      else if(mepJOHIJVJ == rQUzLRNJqq){uUYtzoLRDR = true;}
      if(NdYPgHdKzd == hlPLxmLYRV){mGcZZDbTyR = true;}
      else if(hlPLxmLYRV == NdYPgHdKzd){xMoafnHpWq = true;}
      if(kiPQGxFENe == lWEXPAYCcn){GownxkeWcE = true;}
      if(bipXZifykR == uceosmjmIl){APwKeBDOwC = true;}
      if(ZSIzcZeeHp == kitliuLtYR){PAmTpGnSTz = true;}
      while(lWEXPAYCcn == kiPQGxFENe){VTfPLjQEuw = true;}
      while(uceosmjmIl == uceosmjmIl){ZnRdubmIeL = true;}
      while(kitliuLtYR == kitliuLtYR){FjmVhAaVmM = true;}
      if(FxeOMPZRtO == true){FxeOMPZRtO = false;}
      if(iFfgOEGZSK == true){iFfgOEGZSK = false;}
      if(CYQfjDcSnT == true){CYQfjDcSnT = false;}
      if(necLixyQcd == true){necLixyQcd = false;}
      if(MRstDeCMWd == true){MRstDeCMWd = false;}
      if(olbOOfgydJ == true){olbOOfgydJ = false;}
      if(mGcZZDbTyR == true){mGcZZDbTyR = false;}
      if(GownxkeWcE == true){GownxkeWcE = false;}
      if(APwKeBDOwC == true){APwKeBDOwC = false;}
      if(PAmTpGnSTz == true){PAmTpGnSTz = false;}
      if(DiNEXzomRc == true){DiNEXzomRc = false;}
      if(AKUYIWKStY == true){AKUYIWKStY = false;}
      if(ANWwBGCcxq == true){ANWwBGCcxq = false;}
      if(xMDdBRBqme == true){xMDdBRBqme = false;}
      if(MQwSBFfNKT == true){MQwSBFfNKT = false;}
      if(uUYtzoLRDR == true){uUYtzoLRDR = false;}
      if(xMoafnHpWq == true){xMoafnHpWq = false;}
      if(VTfPLjQEuw == true){VTfPLjQEuw = false;}
      if(ZnRdubmIeL == true){ZnRdubmIeL = false;}
      if(FjmVhAaVmM == true){FjmVhAaVmM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RLHCNWZIQA
{ 
  void thnqNjdGdV()
  { 
      bool MrpexpUYuX = false;
      bool gJOtgzoCzP = false;
      bool KxABPLTtNM = false;
      bool CisNRdADPq = false;
      bool mWRyCmWwbU = false;
      bool SzRaQPqnPk = false;
      bool VZKiVxPAbC = false;
      bool zkmHbmfCyb = false;
      bool oXSrtCQRxC = false;
      bool mLndUNMhcF = false;
      bool XVUYUgMJzc = false;
      bool jopnwyHRoS = false;
      bool fyDZPnxImN = false;
      bool axZrETDsXN = false;
      bool pHRTSxUzhV = false;
      bool FtsJYZRuJg = false;
      bool iDWlClOxjb = false;
      bool uNtbbYfjGR = false;
      bool SyZQHgDPTd = false;
      bool BHjpdljfRf = false;
      string gWZHbKuVeh;
      string KNzXBZcDWH;
      string ORqGCpHcIS;
      string BzujHpDhgi;
      string tyMxJBHqlJ;
      string BVKdTOfSEl;
      string CRMLgKRPPL;
      string VtVnMQEsxB;
      string hQqzRfnQQr;
      string JjdufckBQy;
      string iraanGzWRC;
      string KmVDDlaNsA;
      string VAyXBkQaHj;
      string eDcyRpoPKK;
      string fRzNhWOart;
      string BWHPbhsDYC;
      string pYPhXGJWkM;
      string xKCiTEBjoe;
      string VpiMhIwMVj;
      string xkqIUHBRpa;
      if(gWZHbKuVeh == iraanGzWRC){MrpexpUYuX = true;}
      else if(iraanGzWRC == gWZHbKuVeh){XVUYUgMJzc = true;}
      if(KNzXBZcDWH == KmVDDlaNsA){gJOtgzoCzP = true;}
      else if(KmVDDlaNsA == KNzXBZcDWH){jopnwyHRoS = true;}
      if(ORqGCpHcIS == VAyXBkQaHj){KxABPLTtNM = true;}
      else if(VAyXBkQaHj == ORqGCpHcIS){fyDZPnxImN = true;}
      if(BzujHpDhgi == eDcyRpoPKK){CisNRdADPq = true;}
      else if(eDcyRpoPKK == BzujHpDhgi){axZrETDsXN = true;}
      if(tyMxJBHqlJ == fRzNhWOart){mWRyCmWwbU = true;}
      else if(fRzNhWOart == tyMxJBHqlJ){pHRTSxUzhV = true;}
      if(BVKdTOfSEl == BWHPbhsDYC){SzRaQPqnPk = true;}
      else if(BWHPbhsDYC == BVKdTOfSEl){FtsJYZRuJg = true;}
      if(CRMLgKRPPL == pYPhXGJWkM){VZKiVxPAbC = true;}
      else if(pYPhXGJWkM == CRMLgKRPPL){iDWlClOxjb = true;}
      if(VtVnMQEsxB == xKCiTEBjoe){zkmHbmfCyb = true;}
      if(hQqzRfnQQr == VpiMhIwMVj){oXSrtCQRxC = true;}
      if(JjdufckBQy == xkqIUHBRpa){mLndUNMhcF = true;}
      while(xKCiTEBjoe == VtVnMQEsxB){uNtbbYfjGR = true;}
      while(VpiMhIwMVj == VpiMhIwMVj){SyZQHgDPTd = true;}
      while(xkqIUHBRpa == xkqIUHBRpa){BHjpdljfRf = true;}
      if(MrpexpUYuX == true){MrpexpUYuX = false;}
      if(gJOtgzoCzP == true){gJOtgzoCzP = false;}
      if(KxABPLTtNM == true){KxABPLTtNM = false;}
      if(CisNRdADPq == true){CisNRdADPq = false;}
      if(mWRyCmWwbU == true){mWRyCmWwbU = false;}
      if(SzRaQPqnPk == true){SzRaQPqnPk = false;}
      if(VZKiVxPAbC == true){VZKiVxPAbC = false;}
      if(zkmHbmfCyb == true){zkmHbmfCyb = false;}
      if(oXSrtCQRxC == true){oXSrtCQRxC = false;}
      if(mLndUNMhcF == true){mLndUNMhcF = false;}
      if(XVUYUgMJzc == true){XVUYUgMJzc = false;}
      if(jopnwyHRoS == true){jopnwyHRoS = false;}
      if(fyDZPnxImN == true){fyDZPnxImN = false;}
      if(axZrETDsXN == true){axZrETDsXN = false;}
      if(pHRTSxUzhV == true){pHRTSxUzhV = false;}
      if(FtsJYZRuJg == true){FtsJYZRuJg = false;}
      if(iDWlClOxjb == true){iDWlClOxjb = false;}
      if(uNtbbYfjGR == true){uNtbbYfjGR = false;}
      if(SyZQHgDPTd == true){SyZQHgDPTd = false;}
      if(BHjpdljfRf == true){BHjpdljfRf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DBEIQTJVLO
{ 
  void qZPIRlQBnZ()
  { 
      bool rxVkUryJTX = false;
      bool qliBHhRcmU = false;
      bool tiIQTHUlEq = false;
      bool kiggxgPNfM = false;
      bool HojSmRYUFV = false;
      bool WjdRLInFQN = false;
      bool WLFbmIEBDZ = false;
      bool SDxaMFypcC = false;
      bool hAghTBFOVn = false;
      bool rJwSpwiIfe = false;
      bool MWQeDSmCFF = false;
      bool KycOfVeXIl = false;
      bool CofPhJHdjQ = false;
      bool VpKxoKiBeA = false;
      bool NCJPdtghlT = false;
      bool QLzscWqBxt = false;
      bool LIRnjUneYU = false;
      bool lcrHXzfQln = false;
      bool bYqQAKpQUS = false;
      bool ThEkoFjVeI = false;
      string YNSPBWDWhL;
      string osykneRXYs;
      string EujhXSqaMF;
      string ypwVnyscYJ;
      string RFcxKyRFBz;
      string KVgHcccjrh;
      string ecKbNyxbxp;
      string knyPbyRmXY;
      string AlYMucInsK;
      string UJkqdnuAjL;
      string BpILNWXQfd;
      string LpLThsExgj;
      string pIilUbCHln;
      string DRDMXKdMyX;
      string ErIOzexRIj;
      string ixSzVrGVql;
      string TPeqasmzuX;
      string PqzIfxAUmo;
      string ekyBEGyDpe;
      string DHVMEnMQmF;
      if(YNSPBWDWhL == BpILNWXQfd){rxVkUryJTX = true;}
      else if(BpILNWXQfd == YNSPBWDWhL){MWQeDSmCFF = true;}
      if(osykneRXYs == LpLThsExgj){qliBHhRcmU = true;}
      else if(LpLThsExgj == osykneRXYs){KycOfVeXIl = true;}
      if(EujhXSqaMF == pIilUbCHln){tiIQTHUlEq = true;}
      else if(pIilUbCHln == EujhXSqaMF){CofPhJHdjQ = true;}
      if(ypwVnyscYJ == DRDMXKdMyX){kiggxgPNfM = true;}
      else if(DRDMXKdMyX == ypwVnyscYJ){VpKxoKiBeA = true;}
      if(RFcxKyRFBz == ErIOzexRIj){HojSmRYUFV = true;}
      else if(ErIOzexRIj == RFcxKyRFBz){NCJPdtghlT = true;}
      if(KVgHcccjrh == ixSzVrGVql){WjdRLInFQN = true;}
      else if(ixSzVrGVql == KVgHcccjrh){QLzscWqBxt = true;}
      if(ecKbNyxbxp == TPeqasmzuX){WLFbmIEBDZ = true;}
      else if(TPeqasmzuX == ecKbNyxbxp){LIRnjUneYU = true;}
      if(knyPbyRmXY == PqzIfxAUmo){SDxaMFypcC = true;}
      if(AlYMucInsK == ekyBEGyDpe){hAghTBFOVn = true;}
      if(UJkqdnuAjL == DHVMEnMQmF){rJwSpwiIfe = true;}
      while(PqzIfxAUmo == knyPbyRmXY){lcrHXzfQln = true;}
      while(ekyBEGyDpe == ekyBEGyDpe){bYqQAKpQUS = true;}
      while(DHVMEnMQmF == DHVMEnMQmF){ThEkoFjVeI = true;}
      if(rxVkUryJTX == true){rxVkUryJTX = false;}
      if(qliBHhRcmU == true){qliBHhRcmU = false;}
      if(tiIQTHUlEq == true){tiIQTHUlEq = false;}
      if(kiggxgPNfM == true){kiggxgPNfM = false;}
      if(HojSmRYUFV == true){HojSmRYUFV = false;}
      if(WjdRLInFQN == true){WjdRLInFQN = false;}
      if(WLFbmIEBDZ == true){WLFbmIEBDZ = false;}
      if(SDxaMFypcC == true){SDxaMFypcC = false;}
      if(hAghTBFOVn == true){hAghTBFOVn = false;}
      if(rJwSpwiIfe == true){rJwSpwiIfe = false;}
      if(MWQeDSmCFF == true){MWQeDSmCFF = false;}
      if(KycOfVeXIl == true){KycOfVeXIl = false;}
      if(CofPhJHdjQ == true){CofPhJHdjQ = false;}
      if(VpKxoKiBeA == true){VpKxoKiBeA = false;}
      if(NCJPdtghlT == true){NCJPdtghlT = false;}
      if(QLzscWqBxt == true){QLzscWqBxt = false;}
      if(LIRnjUneYU == true){LIRnjUneYU = false;}
      if(lcrHXzfQln == true){lcrHXzfQln = false;}
      if(bYqQAKpQUS == true){bYqQAKpQUS = false;}
      if(ThEkoFjVeI == true){ThEkoFjVeI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKPZWWEFHS
{ 
  void FjJqxbIAlS()
  { 
      bool DWydPTLXDI = false;
      bool RikMaNuIUJ = false;
      bool YpBrruwhwG = false;
      bool IjDjYUYmpX = false;
      bool xyzPkbeKsJ = false;
      bool SyZBSMVGkT = false;
      bool WcbxzheAnF = false;
      bool nIRxLZqlGQ = false;
      bool PknmmKJCRM = false;
      bool zSBVAUWBQD = false;
      bool wdWnVJgcos = false;
      bool VjAUEknoJo = false;
      bool YbibFVHuwq = false;
      bool DoUCTkOAQd = false;
      bool cfNXpPSfRP = false;
      bool fgraeUuuhA = false;
      bool CkgyofOxBS = false;
      bool VmXfLsOKkp = false;
      bool CacfLVxtXy = false;
      bool pTSQaryPiK = false;
      string lNllFsnBKY;
      string HglETCcxHj;
      string NryMFuxdOV;
      string pHtdqesVEL;
      string goIDIVxpCS;
      string KDquNtOZfK;
      string uKlniAlINn;
      string JHrwCYiuDj;
      string yGbwLlPzQx;
      string PTotPWCUTH;
      string jocNJDLurn;
      string KTVuMohobw;
      string jlqPYpRygf;
      string VOauAIdNmI;
      string aUHcmwxtga;
      string nNrXXxxNoS;
      string kMOLRusZuD;
      string KUCTUPeObb;
      string rXQFqIWCXD;
      string KPXTWOGuKr;
      if(lNllFsnBKY == jocNJDLurn){DWydPTLXDI = true;}
      else if(jocNJDLurn == lNllFsnBKY){wdWnVJgcos = true;}
      if(HglETCcxHj == KTVuMohobw){RikMaNuIUJ = true;}
      else if(KTVuMohobw == HglETCcxHj){VjAUEknoJo = true;}
      if(NryMFuxdOV == jlqPYpRygf){YpBrruwhwG = true;}
      else if(jlqPYpRygf == NryMFuxdOV){YbibFVHuwq = true;}
      if(pHtdqesVEL == VOauAIdNmI){IjDjYUYmpX = true;}
      else if(VOauAIdNmI == pHtdqesVEL){DoUCTkOAQd = true;}
      if(goIDIVxpCS == aUHcmwxtga){xyzPkbeKsJ = true;}
      else if(aUHcmwxtga == goIDIVxpCS){cfNXpPSfRP = true;}
      if(KDquNtOZfK == nNrXXxxNoS){SyZBSMVGkT = true;}
      else if(nNrXXxxNoS == KDquNtOZfK){fgraeUuuhA = true;}
      if(uKlniAlINn == kMOLRusZuD){WcbxzheAnF = true;}
      else if(kMOLRusZuD == uKlniAlINn){CkgyofOxBS = true;}
      if(JHrwCYiuDj == KUCTUPeObb){nIRxLZqlGQ = true;}
      if(yGbwLlPzQx == rXQFqIWCXD){PknmmKJCRM = true;}
      if(PTotPWCUTH == KPXTWOGuKr){zSBVAUWBQD = true;}
      while(KUCTUPeObb == JHrwCYiuDj){VmXfLsOKkp = true;}
      while(rXQFqIWCXD == rXQFqIWCXD){CacfLVxtXy = true;}
      while(KPXTWOGuKr == KPXTWOGuKr){pTSQaryPiK = true;}
      if(DWydPTLXDI == true){DWydPTLXDI = false;}
      if(RikMaNuIUJ == true){RikMaNuIUJ = false;}
      if(YpBrruwhwG == true){YpBrruwhwG = false;}
      if(IjDjYUYmpX == true){IjDjYUYmpX = false;}
      if(xyzPkbeKsJ == true){xyzPkbeKsJ = false;}
      if(SyZBSMVGkT == true){SyZBSMVGkT = false;}
      if(WcbxzheAnF == true){WcbxzheAnF = false;}
      if(nIRxLZqlGQ == true){nIRxLZqlGQ = false;}
      if(PknmmKJCRM == true){PknmmKJCRM = false;}
      if(zSBVAUWBQD == true){zSBVAUWBQD = false;}
      if(wdWnVJgcos == true){wdWnVJgcos = false;}
      if(VjAUEknoJo == true){VjAUEknoJo = false;}
      if(YbibFVHuwq == true){YbibFVHuwq = false;}
      if(DoUCTkOAQd == true){DoUCTkOAQd = false;}
      if(cfNXpPSfRP == true){cfNXpPSfRP = false;}
      if(fgraeUuuhA == true){fgraeUuuhA = false;}
      if(CkgyofOxBS == true){CkgyofOxBS = false;}
      if(VmXfLsOKkp == true){VmXfLsOKkp = false;}
      if(CacfLVxtXy == true){CacfLVxtXy = false;}
      if(pTSQaryPiK == true){pTSQaryPiK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYSRDXDOZN
{ 
  void JRNTqOdkye()
  { 
      bool mDpwYZWgaG = false;
      bool LugQZJKQDL = false;
      bool RlRgAHiiBn = false;
      bool xMlwWGfSXs = false;
      bool YQfkBOzbVm = false;
      bool mzsfpAlIuR = false;
      bool qnelIzJktT = false;
      bool crsJlAGffl = false;
      bool IGNNByTFFV = false;
      bool UWWGCjksbC = false;
      bool ENhCJtFiso = false;
      bool tFcJIjaRkK = false;
      bool eDfXyGVmHC = false;
      bool PMEdguYLEG = false;
      bool rkLPbPtMxR = false;
      bool JTHRWBgJDD = false;
      bool XSaqZgAycN = false;
      bool LPMeRtqPwi = false;
      bool LJooruEmHf = false;
      bool NOHBhYJUot = false;
      string EKXPtUSpVM;
      string zwyducnuim;
      string QfAeJRiouc;
      string hEMRmHZSaE;
      string YHyEHfhDEJ;
      string KOCENYKrFb;
      string kdusetjfpm;
      string CVTdOIguXd;
      string jejlRSCIDO;
      string wgMyTtLFZM;
      string wBMRGotXpE;
      string qPUbrGtJaL;
      string racbqVIUKT;
      string xbVLghRSec;
      string XdSzXgLkGN;
      string ABdOTUYkZj;
      string gZNVHPsItJ;
      string nadxmNIcDJ;
      string JWOxSwxHqM;
      string JfruwyPwqH;
      if(EKXPtUSpVM == wBMRGotXpE){mDpwYZWgaG = true;}
      else if(wBMRGotXpE == EKXPtUSpVM){ENhCJtFiso = true;}
      if(zwyducnuim == qPUbrGtJaL){LugQZJKQDL = true;}
      else if(qPUbrGtJaL == zwyducnuim){tFcJIjaRkK = true;}
      if(QfAeJRiouc == racbqVIUKT){RlRgAHiiBn = true;}
      else if(racbqVIUKT == QfAeJRiouc){eDfXyGVmHC = true;}
      if(hEMRmHZSaE == xbVLghRSec){xMlwWGfSXs = true;}
      else if(xbVLghRSec == hEMRmHZSaE){PMEdguYLEG = true;}
      if(YHyEHfhDEJ == XdSzXgLkGN){YQfkBOzbVm = true;}
      else if(XdSzXgLkGN == YHyEHfhDEJ){rkLPbPtMxR = true;}
      if(KOCENYKrFb == ABdOTUYkZj){mzsfpAlIuR = true;}
      else if(ABdOTUYkZj == KOCENYKrFb){JTHRWBgJDD = true;}
      if(kdusetjfpm == gZNVHPsItJ){qnelIzJktT = true;}
      else if(gZNVHPsItJ == kdusetjfpm){XSaqZgAycN = true;}
      if(CVTdOIguXd == nadxmNIcDJ){crsJlAGffl = true;}
      if(jejlRSCIDO == JWOxSwxHqM){IGNNByTFFV = true;}
      if(wgMyTtLFZM == JfruwyPwqH){UWWGCjksbC = true;}
      while(nadxmNIcDJ == CVTdOIguXd){LPMeRtqPwi = true;}
      while(JWOxSwxHqM == JWOxSwxHqM){LJooruEmHf = true;}
      while(JfruwyPwqH == JfruwyPwqH){NOHBhYJUot = true;}
      if(mDpwYZWgaG == true){mDpwYZWgaG = false;}
      if(LugQZJKQDL == true){LugQZJKQDL = false;}
      if(RlRgAHiiBn == true){RlRgAHiiBn = false;}
      if(xMlwWGfSXs == true){xMlwWGfSXs = false;}
      if(YQfkBOzbVm == true){YQfkBOzbVm = false;}
      if(mzsfpAlIuR == true){mzsfpAlIuR = false;}
      if(qnelIzJktT == true){qnelIzJktT = false;}
      if(crsJlAGffl == true){crsJlAGffl = false;}
      if(IGNNByTFFV == true){IGNNByTFFV = false;}
      if(UWWGCjksbC == true){UWWGCjksbC = false;}
      if(ENhCJtFiso == true){ENhCJtFiso = false;}
      if(tFcJIjaRkK == true){tFcJIjaRkK = false;}
      if(eDfXyGVmHC == true){eDfXyGVmHC = false;}
      if(PMEdguYLEG == true){PMEdguYLEG = false;}
      if(rkLPbPtMxR == true){rkLPbPtMxR = false;}
      if(JTHRWBgJDD == true){JTHRWBgJDD = false;}
      if(XSaqZgAycN == true){XSaqZgAycN = false;}
      if(LPMeRtqPwi == true){LPMeRtqPwi = false;}
      if(LJooruEmHf == true){LJooruEmHf = false;}
      if(NOHBhYJUot == true){NOHBhYJUot = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNQBYORCFO
{ 
  void NYtsKRDnUF()
  { 
      bool equKQobFcF = false;
      bool GLOIDoGlXi = false;
      bool DRAJytNLwn = false;
      bool DGsuFdGdHI = false;
      bool oEGaZsjfSD = false;
      bool HAhAkNpkLW = false;
      bool bPJoBARSDY = false;
      bool iceOszKZjE = false;
      bool JgrrgDYrKr = false;
      bool mURjgYuRYZ = false;
      bool aQbsUdUSHk = false;
      bool CQBHMtXQHx = false;
      bool aYILkOLthT = false;
      bool EsAJdrEzWC = false;
      bool hGkYoWSKWl = false;
      bool BdJayBIQHG = false;
      bool SajmgIPrcU = false;
      bool oYtEOUnjVO = false;
      bool uBWwRaiZKc = false;
      bool jnqQjHVyrf = false;
      string ZkqXYLBwHl;
      string BhXQhYoXUZ;
      string pjPXdbgVFQ;
      string SXLzJSzWJh;
      string IcLJMZctaq;
      string zMganoVTsx;
      string efqqSdVYHO;
      string YSOmQMXFKD;
      string yltNQGqjLT;
      string xfcMDblUqi;
      string EDmLRfxtJa;
      string QPIpyrkcZL;
      string mlNmRsoCio;
      string aDObztyiuk;
      string JwZjCgXmNK;
      string qJteuRoztY;
      string quKUANBfqD;
      string sCgoCpLdkk;
      string VCnYxQJifg;
      string FzoVsNlFjo;
      if(ZkqXYLBwHl == EDmLRfxtJa){equKQobFcF = true;}
      else if(EDmLRfxtJa == ZkqXYLBwHl){aQbsUdUSHk = true;}
      if(BhXQhYoXUZ == QPIpyrkcZL){GLOIDoGlXi = true;}
      else if(QPIpyrkcZL == BhXQhYoXUZ){CQBHMtXQHx = true;}
      if(pjPXdbgVFQ == mlNmRsoCio){DRAJytNLwn = true;}
      else if(mlNmRsoCio == pjPXdbgVFQ){aYILkOLthT = true;}
      if(SXLzJSzWJh == aDObztyiuk){DGsuFdGdHI = true;}
      else if(aDObztyiuk == SXLzJSzWJh){EsAJdrEzWC = true;}
      if(IcLJMZctaq == JwZjCgXmNK){oEGaZsjfSD = true;}
      else if(JwZjCgXmNK == IcLJMZctaq){hGkYoWSKWl = true;}
      if(zMganoVTsx == qJteuRoztY){HAhAkNpkLW = true;}
      else if(qJteuRoztY == zMganoVTsx){BdJayBIQHG = true;}
      if(efqqSdVYHO == quKUANBfqD){bPJoBARSDY = true;}
      else if(quKUANBfqD == efqqSdVYHO){SajmgIPrcU = true;}
      if(YSOmQMXFKD == sCgoCpLdkk){iceOszKZjE = true;}
      if(yltNQGqjLT == VCnYxQJifg){JgrrgDYrKr = true;}
      if(xfcMDblUqi == FzoVsNlFjo){mURjgYuRYZ = true;}
      while(sCgoCpLdkk == YSOmQMXFKD){oYtEOUnjVO = true;}
      while(VCnYxQJifg == VCnYxQJifg){uBWwRaiZKc = true;}
      while(FzoVsNlFjo == FzoVsNlFjo){jnqQjHVyrf = true;}
      if(equKQobFcF == true){equKQobFcF = false;}
      if(GLOIDoGlXi == true){GLOIDoGlXi = false;}
      if(DRAJytNLwn == true){DRAJytNLwn = false;}
      if(DGsuFdGdHI == true){DGsuFdGdHI = false;}
      if(oEGaZsjfSD == true){oEGaZsjfSD = false;}
      if(HAhAkNpkLW == true){HAhAkNpkLW = false;}
      if(bPJoBARSDY == true){bPJoBARSDY = false;}
      if(iceOszKZjE == true){iceOszKZjE = false;}
      if(JgrrgDYrKr == true){JgrrgDYrKr = false;}
      if(mURjgYuRYZ == true){mURjgYuRYZ = false;}
      if(aQbsUdUSHk == true){aQbsUdUSHk = false;}
      if(CQBHMtXQHx == true){CQBHMtXQHx = false;}
      if(aYILkOLthT == true){aYILkOLthT = false;}
      if(EsAJdrEzWC == true){EsAJdrEzWC = false;}
      if(hGkYoWSKWl == true){hGkYoWSKWl = false;}
      if(BdJayBIQHG == true){BdJayBIQHG = false;}
      if(SajmgIPrcU == true){SajmgIPrcU = false;}
      if(oYtEOUnjVO == true){oYtEOUnjVO = false;}
      if(uBWwRaiZKc == true){uBWwRaiZKc = false;}
      if(jnqQjHVyrf == true){jnqQjHVyrf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class INGUCTGEKZ
{ 
  void hYGzChHQmW()
  { 
      bool nVdllryTCr = false;
      bool EJPaLTnZMC = false;
      bool HFzFUOXccK = false;
      bool pxBqpWrQAP = false;
      bool KWIKEqObwy = false;
      bool sUsiuhVYRX = false;
      bool UUqqCHHXjn = false;
      bool aXYwrjxnAc = false;
      bool zwgdQUESwH = false;
      bool ASycupfQIx = false;
      bool jqqIWVuwpK = false;
      bool khXoXXnMag = false;
      bool DobcnHYwBC = false;
      bool DfeDrIFXGt = false;
      bool ZHbkVSuJEW = false;
      bool BTpbtuPNUP = false;
      bool xzumGECUwP = false;
      bool SPFfHuMpGU = false;
      bool MOqdAjpDIx = false;
      bool sqDqxZMndQ = false;
      string dWjozScBQW;
      string bAOhdODROG;
      string jBgAAzuyXD;
      string XxwdgSqPcj;
      string eKeMzrTDBr;
      string rsKXcbpjoA;
      string XecNydDkAL;
      string XnnebYWTAH;
      string fqxfKelXAF;
      string bHZcMAgQOU;
      string ohDoTDEewD;
      string EWigTfhxCT;
      string rfktjQOLSa;
      string rFFfSymHLH;
      string aHbxAFXrIf;
      string SjOtcIxIFD;
      string orMULyQCOV;
      string sZkurjEmse;
      string rVDmIIqKDJ;
      string BdCIRhtGlC;
      if(dWjozScBQW == ohDoTDEewD){nVdllryTCr = true;}
      else if(ohDoTDEewD == dWjozScBQW){jqqIWVuwpK = true;}
      if(bAOhdODROG == EWigTfhxCT){EJPaLTnZMC = true;}
      else if(EWigTfhxCT == bAOhdODROG){khXoXXnMag = true;}
      if(jBgAAzuyXD == rfktjQOLSa){HFzFUOXccK = true;}
      else if(rfktjQOLSa == jBgAAzuyXD){DobcnHYwBC = true;}
      if(XxwdgSqPcj == rFFfSymHLH){pxBqpWrQAP = true;}
      else if(rFFfSymHLH == XxwdgSqPcj){DfeDrIFXGt = true;}
      if(eKeMzrTDBr == aHbxAFXrIf){KWIKEqObwy = true;}
      else if(aHbxAFXrIf == eKeMzrTDBr){ZHbkVSuJEW = true;}
      if(rsKXcbpjoA == SjOtcIxIFD){sUsiuhVYRX = true;}
      else if(SjOtcIxIFD == rsKXcbpjoA){BTpbtuPNUP = true;}
      if(XecNydDkAL == orMULyQCOV){UUqqCHHXjn = true;}
      else if(orMULyQCOV == XecNydDkAL){xzumGECUwP = true;}
      if(XnnebYWTAH == sZkurjEmse){aXYwrjxnAc = true;}
      if(fqxfKelXAF == rVDmIIqKDJ){zwgdQUESwH = true;}
      if(bHZcMAgQOU == BdCIRhtGlC){ASycupfQIx = true;}
      while(sZkurjEmse == XnnebYWTAH){SPFfHuMpGU = true;}
      while(rVDmIIqKDJ == rVDmIIqKDJ){MOqdAjpDIx = true;}
      while(BdCIRhtGlC == BdCIRhtGlC){sqDqxZMndQ = true;}
      if(nVdllryTCr == true){nVdllryTCr = false;}
      if(EJPaLTnZMC == true){EJPaLTnZMC = false;}
      if(HFzFUOXccK == true){HFzFUOXccK = false;}
      if(pxBqpWrQAP == true){pxBqpWrQAP = false;}
      if(KWIKEqObwy == true){KWIKEqObwy = false;}
      if(sUsiuhVYRX == true){sUsiuhVYRX = false;}
      if(UUqqCHHXjn == true){UUqqCHHXjn = false;}
      if(aXYwrjxnAc == true){aXYwrjxnAc = false;}
      if(zwgdQUESwH == true){zwgdQUESwH = false;}
      if(ASycupfQIx == true){ASycupfQIx = false;}
      if(jqqIWVuwpK == true){jqqIWVuwpK = false;}
      if(khXoXXnMag == true){khXoXXnMag = false;}
      if(DobcnHYwBC == true){DobcnHYwBC = false;}
      if(DfeDrIFXGt == true){DfeDrIFXGt = false;}
      if(ZHbkVSuJEW == true){ZHbkVSuJEW = false;}
      if(BTpbtuPNUP == true){BTpbtuPNUP = false;}
      if(xzumGECUwP == true){xzumGECUwP = false;}
      if(SPFfHuMpGU == true){SPFfHuMpGU = false;}
      if(MOqdAjpDIx == true){MOqdAjpDIx = false;}
      if(sqDqxZMndQ == true){sqDqxZMndQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OUZBLTOQLQ
{ 
  void lrsPEegpXj()
  { 
      bool EdMjVUPbWX = false;
      bool jVHONMUmAH = false;
      bool VdmbSlWWAp = false;
      bool RkSMTHiGpS = false;
      bool MMsfREjpQW = false;
      bool AjtoAaqkQj = false;
      bool xrafGyDtuF = false;
      bool dNwhuJjGKO = false;
      bool BfFdohqdLr = false;
      bool QyoGUTkMZS = false;
      bool AouLrmmMsq = false;
      bool qjZChRmxpY = false;
      bool HZhCnfXoMa = false;
      bool XWfqNLjslC = false;
      bool tdjTBfXmYD = false;
      bool fnVBLaGsXM = false;
      bool PxzSTTDinV = false;
      bool gsLnddoOAH = false;
      bool HjQJtiBefl = false;
      bool FqVYlxdQAh = false;
      string ziRNaXJzfK;
      string NShOeVUlnD;
      string EuNPMdShgO;
      string CRqczOhqgQ;
      string xOFkWKkZbu;
      string amigTDVCAx;
      string FbRQIwbEOQ;
      string mdFWGppbrC;
      string rsFlnOiKJw;
      string repiLUwnca;
      string igKLHwhLZc;
      string NsJyFMWfbs;
      string MQuSXHnVLk;
      string sBzRTLisdr;
      string gXjfiyVqdz;
      string yQMiNRkqnz;
      string ILAnjLtqes;
      string ccBjLogOjY;
      string lwqMmboQEC;
      string ZqFeiUXuwW;
      if(ziRNaXJzfK == igKLHwhLZc){EdMjVUPbWX = true;}
      else if(igKLHwhLZc == ziRNaXJzfK){AouLrmmMsq = true;}
      if(NShOeVUlnD == NsJyFMWfbs){jVHONMUmAH = true;}
      else if(NsJyFMWfbs == NShOeVUlnD){qjZChRmxpY = true;}
      if(EuNPMdShgO == MQuSXHnVLk){VdmbSlWWAp = true;}
      else if(MQuSXHnVLk == EuNPMdShgO){HZhCnfXoMa = true;}
      if(CRqczOhqgQ == sBzRTLisdr){RkSMTHiGpS = true;}
      else if(sBzRTLisdr == CRqczOhqgQ){XWfqNLjslC = true;}
      if(xOFkWKkZbu == gXjfiyVqdz){MMsfREjpQW = true;}
      else if(gXjfiyVqdz == xOFkWKkZbu){tdjTBfXmYD = true;}
      if(amigTDVCAx == yQMiNRkqnz){AjtoAaqkQj = true;}
      else if(yQMiNRkqnz == amigTDVCAx){fnVBLaGsXM = true;}
      if(FbRQIwbEOQ == ILAnjLtqes){xrafGyDtuF = true;}
      else if(ILAnjLtqes == FbRQIwbEOQ){PxzSTTDinV = true;}
      if(mdFWGppbrC == ccBjLogOjY){dNwhuJjGKO = true;}
      if(rsFlnOiKJw == lwqMmboQEC){BfFdohqdLr = true;}
      if(repiLUwnca == ZqFeiUXuwW){QyoGUTkMZS = true;}
      while(ccBjLogOjY == mdFWGppbrC){gsLnddoOAH = true;}
      while(lwqMmboQEC == lwqMmboQEC){HjQJtiBefl = true;}
      while(ZqFeiUXuwW == ZqFeiUXuwW){FqVYlxdQAh = true;}
      if(EdMjVUPbWX == true){EdMjVUPbWX = false;}
      if(jVHONMUmAH == true){jVHONMUmAH = false;}
      if(VdmbSlWWAp == true){VdmbSlWWAp = false;}
      if(RkSMTHiGpS == true){RkSMTHiGpS = false;}
      if(MMsfREjpQW == true){MMsfREjpQW = false;}
      if(AjtoAaqkQj == true){AjtoAaqkQj = false;}
      if(xrafGyDtuF == true){xrafGyDtuF = false;}
      if(dNwhuJjGKO == true){dNwhuJjGKO = false;}
      if(BfFdohqdLr == true){BfFdohqdLr = false;}
      if(QyoGUTkMZS == true){QyoGUTkMZS = false;}
      if(AouLrmmMsq == true){AouLrmmMsq = false;}
      if(qjZChRmxpY == true){qjZChRmxpY = false;}
      if(HZhCnfXoMa == true){HZhCnfXoMa = false;}
      if(XWfqNLjslC == true){XWfqNLjslC = false;}
      if(tdjTBfXmYD == true){tdjTBfXmYD = false;}
      if(fnVBLaGsXM == true){fnVBLaGsXM = false;}
      if(PxzSTTDinV == true){PxzSTTDinV = false;}
      if(gsLnddoOAH == true){gsLnddoOAH = false;}
      if(HjQJtiBefl == true){HjQJtiBefl = false;}
      if(FqVYlxdQAh == true){FqVYlxdQAh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KKURXSPUIZ
{ 
  void ugmIigRTQS()
  { 
      bool yIQKqdxrXj = false;
      bool guVhLZDYix = false;
      bool sTCWzpqJyc = false;
      bool rQPGgbMuCV = false;
      bool rzdJynaWNk = false;
      bool yQcNPeGtKA = false;
      bool mnturQfOBi = false;
      bool MIWNFsorYL = false;
      bool PTuMdamCpC = false;
      bool USkBhDFiRg = false;
      bool ILVdYpsPIW = false;
      bool oNUzkSrgQQ = false;
      bool ccYyOtXVeB = false;
      bool nGaqDDyRnm = false;
      bool hXtTNHykQP = false;
      bool LXRADelWPe = false;
      bool SWjGihlcwg = false;
      bool TasciFiEjG = false;
      bool ulFPpPnamX = false;
      bool RaBJUKnmke = false;
      string ptuSaUBNXi;
      string wPBQdzySYJ;
      string BnOQugSABg;
      string TIhUcdskfC;
      string ruSLwSckPs;
      string OwLbNBfdWt;
      string CBLqPmgfmz;
      string GMlVRFVCUc;
      string DgjIRWxGGa;
      string yPOkzqjawI;
      string kwyQmCKoKI;
      string fcJtqVQDYr;
      string pZYLBqyAWa;
      string VtGMqHiTUP;
      string MIwyuUFTtd;
      string afCDRLWlOw;
      string DJSimkWwDj;
      string mwhJfhdaQf;
      string kdFsAorCtf;
      string jwFYLCpMKJ;
      if(ptuSaUBNXi == kwyQmCKoKI){yIQKqdxrXj = true;}
      else if(kwyQmCKoKI == ptuSaUBNXi){ILVdYpsPIW = true;}
      if(wPBQdzySYJ == fcJtqVQDYr){guVhLZDYix = true;}
      else if(fcJtqVQDYr == wPBQdzySYJ){oNUzkSrgQQ = true;}
      if(BnOQugSABg == pZYLBqyAWa){sTCWzpqJyc = true;}
      else if(pZYLBqyAWa == BnOQugSABg){ccYyOtXVeB = true;}
      if(TIhUcdskfC == VtGMqHiTUP){rQPGgbMuCV = true;}
      else if(VtGMqHiTUP == TIhUcdskfC){nGaqDDyRnm = true;}
      if(ruSLwSckPs == MIwyuUFTtd){rzdJynaWNk = true;}
      else if(MIwyuUFTtd == ruSLwSckPs){hXtTNHykQP = true;}
      if(OwLbNBfdWt == afCDRLWlOw){yQcNPeGtKA = true;}
      else if(afCDRLWlOw == OwLbNBfdWt){LXRADelWPe = true;}
      if(CBLqPmgfmz == DJSimkWwDj){mnturQfOBi = true;}
      else if(DJSimkWwDj == CBLqPmgfmz){SWjGihlcwg = true;}
      if(GMlVRFVCUc == mwhJfhdaQf){MIWNFsorYL = true;}
      if(DgjIRWxGGa == kdFsAorCtf){PTuMdamCpC = true;}
      if(yPOkzqjawI == jwFYLCpMKJ){USkBhDFiRg = true;}
      while(mwhJfhdaQf == GMlVRFVCUc){TasciFiEjG = true;}
      while(kdFsAorCtf == kdFsAorCtf){ulFPpPnamX = true;}
      while(jwFYLCpMKJ == jwFYLCpMKJ){RaBJUKnmke = true;}
      if(yIQKqdxrXj == true){yIQKqdxrXj = false;}
      if(guVhLZDYix == true){guVhLZDYix = false;}
      if(sTCWzpqJyc == true){sTCWzpqJyc = false;}
      if(rQPGgbMuCV == true){rQPGgbMuCV = false;}
      if(rzdJynaWNk == true){rzdJynaWNk = false;}
      if(yQcNPeGtKA == true){yQcNPeGtKA = false;}
      if(mnturQfOBi == true){mnturQfOBi = false;}
      if(MIWNFsorYL == true){MIWNFsorYL = false;}
      if(PTuMdamCpC == true){PTuMdamCpC = false;}
      if(USkBhDFiRg == true){USkBhDFiRg = false;}
      if(ILVdYpsPIW == true){ILVdYpsPIW = false;}
      if(oNUzkSrgQQ == true){oNUzkSrgQQ = false;}
      if(ccYyOtXVeB == true){ccYyOtXVeB = false;}
      if(nGaqDDyRnm == true){nGaqDDyRnm = false;}
      if(hXtTNHykQP == true){hXtTNHykQP = false;}
      if(LXRADelWPe == true){LXRADelWPe = false;}
      if(SWjGihlcwg == true){SWjGihlcwg = false;}
      if(TasciFiEjG == true){TasciFiEjG = false;}
      if(ulFPpPnamX == true){ulFPpPnamX = false;}
      if(RaBJUKnmke == true){RaBJUKnmke = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WLWHVWZGOH
{ 
  void YiKjHYqAUa()
  { 
      bool LYThlFaJhg = false;
      bool YNGqQxqECD = false;
      bool nyqCnchqxK = false;
      bool woekbuDFZA = false;
      bool XeLDTUVnFI = false;
      bool YjFrXMhQsJ = false;
      bool XiMXjjhVPV = false;
      bool sldCeJmniT = false;
      bool GtkokLimNO = false;
      bool MmLPbnSmSi = false;
      bool mAXjOlGCMO = false;
      bool ZthZDcyWlX = false;
      bool AtHBJGZNaq = false;
      bool qzUzfGVBZz = false;
      bool FgazoSFlMy = false;
      bool puAuirrWaI = false;
      bool MrbVWaZhsx = false;
      bool HxwmRTTILq = false;
      bool BnAbBuyZQn = false;
      bool NyaRlNFEbO = false;
      string QgrMfpANRS;
      string IMlBZaBMdL;
      string CsCxBEcwYG;
      string dkxbrgZlXs;
      string uBBThAVCPI;
      string WLHypWetLa;
      string NEnLnWOJJs;
      string BOnkQAqhPA;
      string hafQiSdzlU;
      string BfawfqMpeL;
      string kLrVHIWWho;
      string eweKrmXXcV;
      string sOXnrVnqFY;
      string mBDDOVhJJZ;
      string uGRxpEAPEr;
      string ToMISWnEdl;
      string UeRIBcsauV;
      string FNOCZlxaxm;
      string UXmMFyotjr;
      string hceWFPoIuM;
      if(QgrMfpANRS == kLrVHIWWho){LYThlFaJhg = true;}
      else if(kLrVHIWWho == QgrMfpANRS){mAXjOlGCMO = true;}
      if(IMlBZaBMdL == eweKrmXXcV){YNGqQxqECD = true;}
      else if(eweKrmXXcV == IMlBZaBMdL){ZthZDcyWlX = true;}
      if(CsCxBEcwYG == sOXnrVnqFY){nyqCnchqxK = true;}
      else if(sOXnrVnqFY == CsCxBEcwYG){AtHBJGZNaq = true;}
      if(dkxbrgZlXs == mBDDOVhJJZ){woekbuDFZA = true;}
      else if(mBDDOVhJJZ == dkxbrgZlXs){qzUzfGVBZz = true;}
      if(uBBThAVCPI == uGRxpEAPEr){XeLDTUVnFI = true;}
      else if(uGRxpEAPEr == uBBThAVCPI){FgazoSFlMy = true;}
      if(WLHypWetLa == ToMISWnEdl){YjFrXMhQsJ = true;}
      else if(ToMISWnEdl == WLHypWetLa){puAuirrWaI = true;}
      if(NEnLnWOJJs == UeRIBcsauV){XiMXjjhVPV = true;}
      else if(UeRIBcsauV == NEnLnWOJJs){MrbVWaZhsx = true;}
      if(BOnkQAqhPA == FNOCZlxaxm){sldCeJmniT = true;}
      if(hafQiSdzlU == UXmMFyotjr){GtkokLimNO = true;}
      if(BfawfqMpeL == hceWFPoIuM){MmLPbnSmSi = true;}
      while(FNOCZlxaxm == BOnkQAqhPA){HxwmRTTILq = true;}
      while(UXmMFyotjr == UXmMFyotjr){BnAbBuyZQn = true;}
      while(hceWFPoIuM == hceWFPoIuM){NyaRlNFEbO = true;}
      if(LYThlFaJhg == true){LYThlFaJhg = false;}
      if(YNGqQxqECD == true){YNGqQxqECD = false;}
      if(nyqCnchqxK == true){nyqCnchqxK = false;}
      if(woekbuDFZA == true){woekbuDFZA = false;}
      if(XeLDTUVnFI == true){XeLDTUVnFI = false;}
      if(YjFrXMhQsJ == true){YjFrXMhQsJ = false;}
      if(XiMXjjhVPV == true){XiMXjjhVPV = false;}
      if(sldCeJmniT == true){sldCeJmniT = false;}
      if(GtkokLimNO == true){GtkokLimNO = false;}
      if(MmLPbnSmSi == true){MmLPbnSmSi = false;}
      if(mAXjOlGCMO == true){mAXjOlGCMO = false;}
      if(ZthZDcyWlX == true){ZthZDcyWlX = false;}
      if(AtHBJGZNaq == true){AtHBJGZNaq = false;}
      if(qzUzfGVBZz == true){qzUzfGVBZz = false;}
      if(FgazoSFlMy == true){FgazoSFlMy = false;}
      if(puAuirrWaI == true){puAuirrWaI = false;}
      if(MrbVWaZhsx == true){MrbVWaZhsx = false;}
      if(HxwmRTTILq == true){HxwmRTTILq = false;}
      if(BnAbBuyZQn == true){BnAbBuyZQn = false;}
      if(NyaRlNFEbO == true){NyaRlNFEbO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DGOUEGAOUY
{ 
  void qkbcgjBINt()
  { 
      bool nkZOHpbBit = false;
      bool hUkBnHxQMV = false;
      bool GYBQnUqGza = false;
      bool PoXCabrsOM = false;
      bool dMezLZBoVe = false;
      bool CrNBdPiIal = false;
      bool yVBHdrwiZM = false;
      bool PDBzqttBEN = false;
      bool SCjUYWaWXL = false;
      bool riSbNIKWVS = false;
      bool dSOIPzpNJj = false;
      bool VhEMTwkgiG = false;
      bool RZKOUgjYli = false;
      bool iXfljAmaEY = false;
      bool gMMnpJeFIR = false;
      bool WcmOBEHAni = false;
      bool ORbZAxCRcT = false;
      bool IJbJZEMWXK = false;
      bool CdQTMFjRkf = false;
      bool rlmVKOkmmr = false;
      string aagkCGNNsV;
      string FwjFpZZwAI;
      string VPBamrKFfF;
      string YPJSlMskAe;
      string UCambpZinZ;
      string QHtdsLZGyK;
      string uHgmwolRSd;
      string fowVnSoOyw;
      string RbRFnQUfYa;
      string lmlpiNUmpl;
      string EIPJtbLYoZ;
      string VKHCrTpbzf;
      string TGsqqrCGlZ;
      string yBXLqJLILM;
      string FwpyEbfjxP;
      string XrnKRyOXRB;
      string ZFmPbUmuKi;
      string HhQlaXPtmP;
      string MRIWCFNNts;
      string tmpKmzIaWj;
      if(aagkCGNNsV == EIPJtbLYoZ){nkZOHpbBit = true;}
      else if(EIPJtbLYoZ == aagkCGNNsV){dSOIPzpNJj = true;}
      if(FwjFpZZwAI == VKHCrTpbzf){hUkBnHxQMV = true;}
      else if(VKHCrTpbzf == FwjFpZZwAI){VhEMTwkgiG = true;}
      if(VPBamrKFfF == TGsqqrCGlZ){GYBQnUqGza = true;}
      else if(TGsqqrCGlZ == VPBamrKFfF){RZKOUgjYli = true;}
      if(YPJSlMskAe == yBXLqJLILM){PoXCabrsOM = true;}
      else if(yBXLqJLILM == YPJSlMskAe){iXfljAmaEY = true;}
      if(UCambpZinZ == FwpyEbfjxP){dMezLZBoVe = true;}
      else if(FwpyEbfjxP == UCambpZinZ){gMMnpJeFIR = true;}
      if(QHtdsLZGyK == XrnKRyOXRB){CrNBdPiIal = true;}
      else if(XrnKRyOXRB == QHtdsLZGyK){WcmOBEHAni = true;}
      if(uHgmwolRSd == ZFmPbUmuKi){yVBHdrwiZM = true;}
      else if(ZFmPbUmuKi == uHgmwolRSd){ORbZAxCRcT = true;}
      if(fowVnSoOyw == HhQlaXPtmP){PDBzqttBEN = true;}
      if(RbRFnQUfYa == MRIWCFNNts){SCjUYWaWXL = true;}
      if(lmlpiNUmpl == tmpKmzIaWj){riSbNIKWVS = true;}
      while(HhQlaXPtmP == fowVnSoOyw){IJbJZEMWXK = true;}
      while(MRIWCFNNts == MRIWCFNNts){CdQTMFjRkf = true;}
      while(tmpKmzIaWj == tmpKmzIaWj){rlmVKOkmmr = true;}
      if(nkZOHpbBit == true){nkZOHpbBit = false;}
      if(hUkBnHxQMV == true){hUkBnHxQMV = false;}
      if(GYBQnUqGza == true){GYBQnUqGza = false;}
      if(PoXCabrsOM == true){PoXCabrsOM = false;}
      if(dMezLZBoVe == true){dMezLZBoVe = false;}
      if(CrNBdPiIal == true){CrNBdPiIal = false;}
      if(yVBHdrwiZM == true){yVBHdrwiZM = false;}
      if(PDBzqttBEN == true){PDBzqttBEN = false;}
      if(SCjUYWaWXL == true){SCjUYWaWXL = false;}
      if(riSbNIKWVS == true){riSbNIKWVS = false;}
      if(dSOIPzpNJj == true){dSOIPzpNJj = false;}
      if(VhEMTwkgiG == true){VhEMTwkgiG = false;}
      if(RZKOUgjYli == true){RZKOUgjYli = false;}
      if(iXfljAmaEY == true){iXfljAmaEY = false;}
      if(gMMnpJeFIR == true){gMMnpJeFIR = false;}
      if(WcmOBEHAni == true){WcmOBEHAni = false;}
      if(ORbZAxCRcT == true){ORbZAxCRcT = false;}
      if(IJbJZEMWXK == true){IJbJZEMWXK = false;}
      if(CdQTMFjRkf == true){CdQTMFjRkf = false;}
      if(rlmVKOkmmr == true){rlmVKOkmmr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UQSEYZMQVZ
{ 
  void senUdeOXhS()
  { 
      bool TAAxKqsBOF = false;
      bool ZLedCPVqNP = false;
      bool DluyiHcHqH = false;
      bool yVRGCYqYPW = false;
      bool qwrqnkxywX = false;
      bool CAHIShEBND = false;
      bool OkJHGEsXad = false;
      bool YwapXHsEKx = false;
      bool JeKTFyNImT = false;
      bool UoLMHGlkji = false;
      bool qZWSzFYQkL = false;
      bool nzqPtiZpBI = false;
      bool qjkGJikOiR = false;
      bool UHTaGjIrTz = false;
      bool YwXbfUxuSX = false;
      bool fwjarGnPIP = false;
      bool UKhTqgeQJJ = false;
      bool ahWCjtMJan = false;
      bool lpwKkYXshz = false;
      bool urjDdNODjy = false;
      string EVGjDZqFPI;
      string YfflrtrONO;
      string uhhiIGMuFf;
      string GZJIdxAgFc;
      string ZerquZpSgm;
      string XzZazWmXaw;
      string NuzjBzVXIu;
      string tKIknPoqmi;
      string QtOSIGziIG;
      string JcFIOdfIou;
      string DRJlrMqolj;
      string hujrfTggau;
      string AmPBkQFzVK;
      string jfBrezjcZu;
      string PKwYYNrNcu;
      string wzhtuQCHAa;
      string HqSbABsrMf;
      string jEGfepppcW;
      string YqVaNjyHwO;
      string xbbynXqUYW;
      if(EVGjDZqFPI == DRJlrMqolj){TAAxKqsBOF = true;}
      else if(DRJlrMqolj == EVGjDZqFPI){qZWSzFYQkL = true;}
      if(YfflrtrONO == hujrfTggau){ZLedCPVqNP = true;}
      else if(hujrfTggau == YfflrtrONO){nzqPtiZpBI = true;}
      if(uhhiIGMuFf == AmPBkQFzVK){DluyiHcHqH = true;}
      else if(AmPBkQFzVK == uhhiIGMuFf){qjkGJikOiR = true;}
      if(GZJIdxAgFc == jfBrezjcZu){yVRGCYqYPW = true;}
      else if(jfBrezjcZu == GZJIdxAgFc){UHTaGjIrTz = true;}
      if(ZerquZpSgm == PKwYYNrNcu){qwrqnkxywX = true;}
      else if(PKwYYNrNcu == ZerquZpSgm){YwXbfUxuSX = true;}
      if(XzZazWmXaw == wzhtuQCHAa){CAHIShEBND = true;}
      else if(wzhtuQCHAa == XzZazWmXaw){fwjarGnPIP = true;}
      if(NuzjBzVXIu == HqSbABsrMf){OkJHGEsXad = true;}
      else if(HqSbABsrMf == NuzjBzVXIu){UKhTqgeQJJ = true;}
      if(tKIknPoqmi == jEGfepppcW){YwapXHsEKx = true;}
      if(QtOSIGziIG == YqVaNjyHwO){JeKTFyNImT = true;}
      if(JcFIOdfIou == xbbynXqUYW){UoLMHGlkji = true;}
      while(jEGfepppcW == tKIknPoqmi){ahWCjtMJan = true;}
      while(YqVaNjyHwO == YqVaNjyHwO){lpwKkYXshz = true;}
      while(xbbynXqUYW == xbbynXqUYW){urjDdNODjy = true;}
      if(TAAxKqsBOF == true){TAAxKqsBOF = false;}
      if(ZLedCPVqNP == true){ZLedCPVqNP = false;}
      if(DluyiHcHqH == true){DluyiHcHqH = false;}
      if(yVRGCYqYPW == true){yVRGCYqYPW = false;}
      if(qwrqnkxywX == true){qwrqnkxywX = false;}
      if(CAHIShEBND == true){CAHIShEBND = false;}
      if(OkJHGEsXad == true){OkJHGEsXad = false;}
      if(YwapXHsEKx == true){YwapXHsEKx = false;}
      if(JeKTFyNImT == true){JeKTFyNImT = false;}
      if(UoLMHGlkji == true){UoLMHGlkji = false;}
      if(qZWSzFYQkL == true){qZWSzFYQkL = false;}
      if(nzqPtiZpBI == true){nzqPtiZpBI = false;}
      if(qjkGJikOiR == true){qjkGJikOiR = false;}
      if(UHTaGjIrTz == true){UHTaGjIrTz = false;}
      if(YwXbfUxuSX == true){YwXbfUxuSX = false;}
      if(fwjarGnPIP == true){fwjarGnPIP = false;}
      if(UKhTqgeQJJ == true){UKhTqgeQJJ = false;}
      if(ahWCjtMJan == true){ahWCjtMJan = false;}
      if(lpwKkYXshz == true){lpwKkYXshz = false;}
      if(urjDdNODjy == true){urjDdNODjy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TLGZIGXNRU
{ 
  void YIRAXEiLcR()
  { 
      bool TCbNnUVfJm = false;
      bool hylhXRnVIY = false;
      bool ROxbLXlUTb = false;
      bool lFUtCMdcgY = false;
      bool IZrOdSlAdx = false;
      bool PgoJtEEzBQ = false;
      bool hALgAbdrfK = false;
      bool mKnjPrVixr = false;
      bool klqWMFPLAx = false;
      bool IebQpINKNB = false;
      bool osUTKErFsB = false;
      bool hVBIewJoUu = false;
      bool MRqhCHiXtH = false;
      bool dLVwDrRXMH = false;
      bool MKSyOlcSkt = false;
      bool yXoRoXBlQC = false;
      bool UULlXWAFFm = false;
      bool dlcNiBzsTP = false;
      bool dQlzIFVDGe = false;
      bool pfGJlqzfaq = false;
      string ePdTNJyHJn;
      string MERisnTVKZ;
      string qlKQjDxzyG;
      string eoHPSwqpyI;
      string tOjOfpryFC;
      string YiySDrENiJ;
      string LzICJXwBPx;
      string wdWCecBwkt;
      string LzswhupoMZ;
      string rdGowuFhEI;
      string tqhIGuMwma;
      string qHboyMFMUO;
      string gGooFRXhFj;
      string WTqcATQkpl;
      string isCkijCQqj;
      string prNpamCrDn;
      string XeqDDXQzod;
      string uUWhfnEDGV;
      string PGpVtdFBBM;
      string RXhBODCyhL;
      if(ePdTNJyHJn == tqhIGuMwma){TCbNnUVfJm = true;}
      else if(tqhIGuMwma == ePdTNJyHJn){osUTKErFsB = true;}
      if(MERisnTVKZ == qHboyMFMUO){hylhXRnVIY = true;}
      else if(qHboyMFMUO == MERisnTVKZ){hVBIewJoUu = true;}
      if(qlKQjDxzyG == gGooFRXhFj){ROxbLXlUTb = true;}
      else if(gGooFRXhFj == qlKQjDxzyG){MRqhCHiXtH = true;}
      if(eoHPSwqpyI == WTqcATQkpl){lFUtCMdcgY = true;}
      else if(WTqcATQkpl == eoHPSwqpyI){dLVwDrRXMH = true;}
      if(tOjOfpryFC == isCkijCQqj){IZrOdSlAdx = true;}
      else if(isCkijCQqj == tOjOfpryFC){MKSyOlcSkt = true;}
      if(YiySDrENiJ == prNpamCrDn){PgoJtEEzBQ = true;}
      else if(prNpamCrDn == YiySDrENiJ){yXoRoXBlQC = true;}
      if(LzICJXwBPx == XeqDDXQzod){hALgAbdrfK = true;}
      else if(XeqDDXQzod == LzICJXwBPx){UULlXWAFFm = true;}
      if(wdWCecBwkt == uUWhfnEDGV){mKnjPrVixr = true;}
      if(LzswhupoMZ == PGpVtdFBBM){klqWMFPLAx = true;}
      if(rdGowuFhEI == RXhBODCyhL){IebQpINKNB = true;}
      while(uUWhfnEDGV == wdWCecBwkt){dlcNiBzsTP = true;}
      while(PGpVtdFBBM == PGpVtdFBBM){dQlzIFVDGe = true;}
      while(RXhBODCyhL == RXhBODCyhL){pfGJlqzfaq = true;}
      if(TCbNnUVfJm == true){TCbNnUVfJm = false;}
      if(hylhXRnVIY == true){hylhXRnVIY = false;}
      if(ROxbLXlUTb == true){ROxbLXlUTb = false;}
      if(lFUtCMdcgY == true){lFUtCMdcgY = false;}
      if(IZrOdSlAdx == true){IZrOdSlAdx = false;}
      if(PgoJtEEzBQ == true){PgoJtEEzBQ = false;}
      if(hALgAbdrfK == true){hALgAbdrfK = false;}
      if(mKnjPrVixr == true){mKnjPrVixr = false;}
      if(klqWMFPLAx == true){klqWMFPLAx = false;}
      if(IebQpINKNB == true){IebQpINKNB = false;}
      if(osUTKErFsB == true){osUTKErFsB = false;}
      if(hVBIewJoUu == true){hVBIewJoUu = false;}
      if(MRqhCHiXtH == true){MRqhCHiXtH = false;}
      if(dLVwDrRXMH == true){dLVwDrRXMH = false;}
      if(MKSyOlcSkt == true){MKSyOlcSkt = false;}
      if(yXoRoXBlQC == true){yXoRoXBlQC = false;}
      if(UULlXWAFFm == true){UULlXWAFFm = false;}
      if(dlcNiBzsTP == true){dlcNiBzsTP = false;}
      if(dQlzIFVDGe == true){dQlzIFVDGe = false;}
      if(pfGJlqzfaq == true){pfGJlqzfaq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SEBMTKDSDR
{ 
  void EaqQpolTUE()
  { 
      bool ROHeTeCRxl = false;
      bool zTsaFTUxBG = false;
      bool bdtedVGxDk = false;
      bool dpVNYuaNYU = false;
      bool kUkywkzinT = false;
      bool gGXfhmUbAy = false;
      bool XENMIIxeCJ = false;
      bool sHXgUGswis = false;
      bool WXJjDWSpfk = false;
      bool ayMawgHXpm = false;
      bool nTgeaYhqKa = false;
      bool sXsHbAtdIl = false;
      bool pHzQhutxjn = false;
      bool zUFuECqdIe = false;
      bool nbeFrCFFzw = false;
      bool lcOEwgUPwf = false;
      bool ekGWaXRxCY = false;
      bool IQVdxObtYf = false;
      bool ooymBWGByX = false;
      bool gahcADUHdT = false;
      string iIRJeQiULY;
      string thMccBUggc;
      string IdXgAOVemR;
      string oIMOrwPftA;
      string rdlUgdPySG;
      string HGxjFFjjJP;
      string tDhsjlUyjg;
      string knlgkdqDAV;
      string yWMfKiKbIm;
      string LeWeFnwsku;
      string JRNlVTTQzb;
      string NgjnQWqCiA;
      string asoxUFRGax;
      string hySEMgIaJp;
      string OscgZetiOh;
      string wtKjTPbQQP;
      string CMpCtPNfbi;
      string NQrrlgQIXp;
      string KhrrAmmikw;
      string ErJtnBDZlJ;
      if(iIRJeQiULY == JRNlVTTQzb){ROHeTeCRxl = true;}
      else if(JRNlVTTQzb == iIRJeQiULY){nTgeaYhqKa = true;}
      if(thMccBUggc == NgjnQWqCiA){zTsaFTUxBG = true;}
      else if(NgjnQWqCiA == thMccBUggc){sXsHbAtdIl = true;}
      if(IdXgAOVemR == asoxUFRGax){bdtedVGxDk = true;}
      else if(asoxUFRGax == IdXgAOVemR){pHzQhutxjn = true;}
      if(oIMOrwPftA == hySEMgIaJp){dpVNYuaNYU = true;}
      else if(hySEMgIaJp == oIMOrwPftA){zUFuECqdIe = true;}
      if(rdlUgdPySG == OscgZetiOh){kUkywkzinT = true;}
      else if(OscgZetiOh == rdlUgdPySG){nbeFrCFFzw = true;}
      if(HGxjFFjjJP == wtKjTPbQQP){gGXfhmUbAy = true;}
      else if(wtKjTPbQQP == HGxjFFjjJP){lcOEwgUPwf = true;}
      if(tDhsjlUyjg == CMpCtPNfbi){XENMIIxeCJ = true;}
      else if(CMpCtPNfbi == tDhsjlUyjg){ekGWaXRxCY = true;}
      if(knlgkdqDAV == NQrrlgQIXp){sHXgUGswis = true;}
      if(yWMfKiKbIm == KhrrAmmikw){WXJjDWSpfk = true;}
      if(LeWeFnwsku == ErJtnBDZlJ){ayMawgHXpm = true;}
      while(NQrrlgQIXp == knlgkdqDAV){IQVdxObtYf = true;}
      while(KhrrAmmikw == KhrrAmmikw){ooymBWGByX = true;}
      while(ErJtnBDZlJ == ErJtnBDZlJ){gahcADUHdT = true;}
      if(ROHeTeCRxl == true){ROHeTeCRxl = false;}
      if(zTsaFTUxBG == true){zTsaFTUxBG = false;}
      if(bdtedVGxDk == true){bdtedVGxDk = false;}
      if(dpVNYuaNYU == true){dpVNYuaNYU = false;}
      if(kUkywkzinT == true){kUkywkzinT = false;}
      if(gGXfhmUbAy == true){gGXfhmUbAy = false;}
      if(XENMIIxeCJ == true){XENMIIxeCJ = false;}
      if(sHXgUGswis == true){sHXgUGswis = false;}
      if(WXJjDWSpfk == true){WXJjDWSpfk = false;}
      if(ayMawgHXpm == true){ayMawgHXpm = false;}
      if(nTgeaYhqKa == true){nTgeaYhqKa = false;}
      if(sXsHbAtdIl == true){sXsHbAtdIl = false;}
      if(pHzQhutxjn == true){pHzQhutxjn = false;}
      if(zUFuECqdIe == true){zUFuECqdIe = false;}
      if(nbeFrCFFzw == true){nbeFrCFFzw = false;}
      if(lcOEwgUPwf == true){lcOEwgUPwf = false;}
      if(ekGWaXRxCY == true){ekGWaXRxCY = false;}
      if(IQVdxObtYf == true){IQVdxObtYf = false;}
      if(ooymBWGByX == true){ooymBWGByX = false;}
      if(gahcADUHdT == true){gahcADUHdT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XDVRCDTAGN
{ 
  void VUbscGSuIk()
  { 
      bool PEzORawKwT = false;
      bool cRbbDUxoTr = false;
      bool ZfJMhPSqos = false;
      bool XEplUHjzWz = false;
      bool RusmGWRiRZ = false;
      bool PSyeEjtmgC = false;
      bool HEUCwXaoGu = false;
      bool kxSTaemVFK = false;
      bool yjZOcEGKhk = false;
      bool MwSTrMZpqh = false;
      bool ubbVoRAdEZ = false;
      bool wXgVDXeGZq = false;
      bool RPHUhndybO = false;
      bool ExeXOWHDZK = false;
      bool EbGHonPxQU = false;
      bool gTPzQeUHmB = false;
      bool mBCpVzsIGg = false;
      bool PafOloJzft = false;
      bool XghGgjgeGj = false;
      bool BAQYXDZQlp = false;
      string kVHdCDdkrw;
      string QcMYOcorNI;
      string MYfCbQzSHa;
      string cOENDpzfOa;
      string TjtDXHXpIZ;
      string spgQFLpEBk;
      string ELdQTCXzUX;
      string cJdlocdbeU;
      string sIJghlgnHr;
      string AudcWHFdjV;
      string jXVkxiMtbc;
      string gNZgruCwig;
      string UircXgfAPg;
      string WArIjUlXjy;
      string ZmMdKlVwka;
      string FItCBAfsNP;
      string DMduGfVQwW;
      string IdMjGgWNRk;
      string LiOnaNGoHj;
      string osKUtNIRXe;
      if(kVHdCDdkrw == jXVkxiMtbc){PEzORawKwT = true;}
      else if(jXVkxiMtbc == kVHdCDdkrw){ubbVoRAdEZ = true;}
      if(QcMYOcorNI == gNZgruCwig){cRbbDUxoTr = true;}
      else if(gNZgruCwig == QcMYOcorNI){wXgVDXeGZq = true;}
      if(MYfCbQzSHa == UircXgfAPg){ZfJMhPSqos = true;}
      else if(UircXgfAPg == MYfCbQzSHa){RPHUhndybO = true;}
      if(cOENDpzfOa == WArIjUlXjy){XEplUHjzWz = true;}
      else if(WArIjUlXjy == cOENDpzfOa){ExeXOWHDZK = true;}
      if(TjtDXHXpIZ == ZmMdKlVwka){RusmGWRiRZ = true;}
      else if(ZmMdKlVwka == TjtDXHXpIZ){EbGHonPxQU = true;}
      if(spgQFLpEBk == FItCBAfsNP){PSyeEjtmgC = true;}
      else if(FItCBAfsNP == spgQFLpEBk){gTPzQeUHmB = true;}
      if(ELdQTCXzUX == DMduGfVQwW){HEUCwXaoGu = true;}
      else if(DMduGfVQwW == ELdQTCXzUX){mBCpVzsIGg = true;}
      if(cJdlocdbeU == IdMjGgWNRk){kxSTaemVFK = true;}
      if(sIJghlgnHr == LiOnaNGoHj){yjZOcEGKhk = true;}
      if(AudcWHFdjV == osKUtNIRXe){MwSTrMZpqh = true;}
      while(IdMjGgWNRk == cJdlocdbeU){PafOloJzft = true;}
      while(LiOnaNGoHj == LiOnaNGoHj){XghGgjgeGj = true;}
      while(osKUtNIRXe == osKUtNIRXe){BAQYXDZQlp = true;}
      if(PEzORawKwT == true){PEzORawKwT = false;}
      if(cRbbDUxoTr == true){cRbbDUxoTr = false;}
      if(ZfJMhPSqos == true){ZfJMhPSqos = false;}
      if(XEplUHjzWz == true){XEplUHjzWz = false;}
      if(RusmGWRiRZ == true){RusmGWRiRZ = false;}
      if(PSyeEjtmgC == true){PSyeEjtmgC = false;}
      if(HEUCwXaoGu == true){HEUCwXaoGu = false;}
      if(kxSTaemVFK == true){kxSTaemVFK = false;}
      if(yjZOcEGKhk == true){yjZOcEGKhk = false;}
      if(MwSTrMZpqh == true){MwSTrMZpqh = false;}
      if(ubbVoRAdEZ == true){ubbVoRAdEZ = false;}
      if(wXgVDXeGZq == true){wXgVDXeGZq = false;}
      if(RPHUhndybO == true){RPHUhndybO = false;}
      if(ExeXOWHDZK == true){ExeXOWHDZK = false;}
      if(EbGHonPxQU == true){EbGHonPxQU = false;}
      if(gTPzQeUHmB == true){gTPzQeUHmB = false;}
      if(mBCpVzsIGg == true){mBCpVzsIGg = false;}
      if(PafOloJzft == true){PafOloJzft = false;}
      if(XghGgjgeGj == true){XghGgjgeGj = false;}
      if(BAQYXDZQlp == true){BAQYXDZQlp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class REMYTRKMCS
{ 
  void DaiilJCWlj()
  { 
      bool ZDtRJHEMQL = false;
      bool XZAkEKYfKN = false;
      bool aokTKOdZoM = false;
      bool AoyxPLamrq = false;
      bool yuQkVZnTyP = false;
      bool AxFaHkRZHu = false;
      bool ceWEKiaCVr = false;
      bool jlnTOfYzyk = false;
      bool ZJbYLDiXpd = false;
      bool sAewOTXLal = false;
      bool ykyFfOIlLa = false;
      bool LRbWUSDyrH = false;
      bool zDMqyiGqFu = false;
      bool INYLloLVsx = false;
      bool txLOSbYIbu = false;
      bool QZSSmtYHGw = false;
      bool HRgQSysPje = false;
      bool HgFtNBqxXW = false;
      bool KyOJehtGYr = false;
      bool QDPwpbPuwT = false;
      string hEObGrLHsG;
      string slSagsoRLO;
      string hcUhGTRBRC;
      string EAaUqnlQlM;
      string QTqsUWCPGa;
      string jquyOFigVm;
      string aJoqCrKxjr;
      string GYfzxOkbMj;
      string QBtqSNFcFl;
      string EFtykGeAqb;
      string LEfOUKKuBA;
      string THTlVYPyXn;
      string mhrymBdgNp;
      string jjjkXMVfVH;
      string CJaFRxlIbM;
      string qfcCndMgaT;
      string gdgKQiWhNJ;
      string DibPkcGmfp;
      string PVEBzDHgws;
      string znFCaYcQni;
      if(hEObGrLHsG == LEfOUKKuBA){ZDtRJHEMQL = true;}
      else if(LEfOUKKuBA == hEObGrLHsG){ykyFfOIlLa = true;}
      if(slSagsoRLO == THTlVYPyXn){XZAkEKYfKN = true;}
      else if(THTlVYPyXn == slSagsoRLO){LRbWUSDyrH = true;}
      if(hcUhGTRBRC == mhrymBdgNp){aokTKOdZoM = true;}
      else if(mhrymBdgNp == hcUhGTRBRC){zDMqyiGqFu = true;}
      if(EAaUqnlQlM == jjjkXMVfVH){AoyxPLamrq = true;}
      else if(jjjkXMVfVH == EAaUqnlQlM){INYLloLVsx = true;}
      if(QTqsUWCPGa == CJaFRxlIbM){yuQkVZnTyP = true;}
      else if(CJaFRxlIbM == QTqsUWCPGa){txLOSbYIbu = true;}
      if(jquyOFigVm == qfcCndMgaT){AxFaHkRZHu = true;}
      else if(qfcCndMgaT == jquyOFigVm){QZSSmtYHGw = true;}
      if(aJoqCrKxjr == gdgKQiWhNJ){ceWEKiaCVr = true;}
      else if(gdgKQiWhNJ == aJoqCrKxjr){HRgQSysPje = true;}
      if(GYfzxOkbMj == DibPkcGmfp){jlnTOfYzyk = true;}
      if(QBtqSNFcFl == PVEBzDHgws){ZJbYLDiXpd = true;}
      if(EFtykGeAqb == znFCaYcQni){sAewOTXLal = true;}
      while(DibPkcGmfp == GYfzxOkbMj){HgFtNBqxXW = true;}
      while(PVEBzDHgws == PVEBzDHgws){KyOJehtGYr = true;}
      while(znFCaYcQni == znFCaYcQni){QDPwpbPuwT = true;}
      if(ZDtRJHEMQL == true){ZDtRJHEMQL = false;}
      if(XZAkEKYfKN == true){XZAkEKYfKN = false;}
      if(aokTKOdZoM == true){aokTKOdZoM = false;}
      if(AoyxPLamrq == true){AoyxPLamrq = false;}
      if(yuQkVZnTyP == true){yuQkVZnTyP = false;}
      if(AxFaHkRZHu == true){AxFaHkRZHu = false;}
      if(ceWEKiaCVr == true){ceWEKiaCVr = false;}
      if(jlnTOfYzyk == true){jlnTOfYzyk = false;}
      if(ZJbYLDiXpd == true){ZJbYLDiXpd = false;}
      if(sAewOTXLal == true){sAewOTXLal = false;}
      if(ykyFfOIlLa == true){ykyFfOIlLa = false;}
      if(LRbWUSDyrH == true){LRbWUSDyrH = false;}
      if(zDMqyiGqFu == true){zDMqyiGqFu = false;}
      if(INYLloLVsx == true){INYLloLVsx = false;}
      if(txLOSbYIbu == true){txLOSbYIbu = false;}
      if(QZSSmtYHGw == true){QZSSmtYHGw = false;}
      if(HRgQSysPje == true){HRgQSysPje = false;}
      if(HgFtNBqxXW == true){HgFtNBqxXW = false;}
      if(KyOJehtGYr == true){KyOJehtGYr = false;}
      if(QDPwpbPuwT == true){QDPwpbPuwT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OYKOYHTVZE
{ 
  void SiQLNhqOjR()
  { 
      bool LckHubphBZ = false;
      bool JkKWtCLJde = false;
      bool WaPqNzbJqU = false;
      bool jdOLjqzipB = false;
      bool RctPTKFfxY = false;
      bool lQwhNjNstw = false;
      bool AgqfpeWylD = false;
      bool CbScMtfzXC = false;
      bool swMSiShfyA = false;
      bool dGotBklNZo = false;
      bool nGstVJxSUT = false;
      bool DNVqCDTXxX = false;
      bool xpAlYwlYaa = false;
      bool HRZiOmDSxY = false;
      bool UOLdwPkxrx = false;
      bool QNQBqxFGUY = false;
      bool WYrtLlnmbP = false;
      bool ABaYCidWpI = false;
      bool LngcJtBXqQ = false;
      bool gwxXBwWQSK = false;
      string uwbKDfkCLe;
      string sdwfENhadW;
      string rFKBGtwPRi;
      string EAOgDGqWni;
      string dnKKJOBAwp;
      string owmmsokZEI;
      string jUkbZsOOcy;
      string VKmusDuzrq;
      string suTatIMbnN;
      string URSfzICijQ;
      string AlXxTeJqso;
      string tlhMPnBJhR;
      string fmZPdEqGwk;
      string BMOaqGXVHO;
      string zVhzShjGPK;
      string HrBSjNLHSP;
      string mCuImhWGUI;
      string PeCSRKEaww;
      string UkqkdIKwpc;
      string uQCraxaZMk;
      if(uwbKDfkCLe == AlXxTeJqso){LckHubphBZ = true;}
      else if(AlXxTeJqso == uwbKDfkCLe){nGstVJxSUT = true;}
      if(sdwfENhadW == tlhMPnBJhR){JkKWtCLJde = true;}
      else if(tlhMPnBJhR == sdwfENhadW){DNVqCDTXxX = true;}
      if(rFKBGtwPRi == fmZPdEqGwk){WaPqNzbJqU = true;}
      else if(fmZPdEqGwk == rFKBGtwPRi){xpAlYwlYaa = true;}
      if(EAOgDGqWni == BMOaqGXVHO){jdOLjqzipB = true;}
      else if(BMOaqGXVHO == EAOgDGqWni){HRZiOmDSxY = true;}
      if(dnKKJOBAwp == zVhzShjGPK){RctPTKFfxY = true;}
      else if(zVhzShjGPK == dnKKJOBAwp){UOLdwPkxrx = true;}
      if(owmmsokZEI == HrBSjNLHSP){lQwhNjNstw = true;}
      else if(HrBSjNLHSP == owmmsokZEI){QNQBqxFGUY = true;}
      if(jUkbZsOOcy == mCuImhWGUI){AgqfpeWylD = true;}
      else if(mCuImhWGUI == jUkbZsOOcy){WYrtLlnmbP = true;}
      if(VKmusDuzrq == PeCSRKEaww){CbScMtfzXC = true;}
      if(suTatIMbnN == UkqkdIKwpc){swMSiShfyA = true;}
      if(URSfzICijQ == uQCraxaZMk){dGotBklNZo = true;}
      while(PeCSRKEaww == VKmusDuzrq){ABaYCidWpI = true;}
      while(UkqkdIKwpc == UkqkdIKwpc){LngcJtBXqQ = true;}
      while(uQCraxaZMk == uQCraxaZMk){gwxXBwWQSK = true;}
      if(LckHubphBZ == true){LckHubphBZ = false;}
      if(JkKWtCLJde == true){JkKWtCLJde = false;}
      if(WaPqNzbJqU == true){WaPqNzbJqU = false;}
      if(jdOLjqzipB == true){jdOLjqzipB = false;}
      if(RctPTKFfxY == true){RctPTKFfxY = false;}
      if(lQwhNjNstw == true){lQwhNjNstw = false;}
      if(AgqfpeWylD == true){AgqfpeWylD = false;}
      if(CbScMtfzXC == true){CbScMtfzXC = false;}
      if(swMSiShfyA == true){swMSiShfyA = false;}
      if(dGotBklNZo == true){dGotBklNZo = false;}
      if(nGstVJxSUT == true){nGstVJxSUT = false;}
      if(DNVqCDTXxX == true){DNVqCDTXxX = false;}
      if(xpAlYwlYaa == true){xpAlYwlYaa = false;}
      if(HRZiOmDSxY == true){HRZiOmDSxY = false;}
      if(UOLdwPkxrx == true){UOLdwPkxrx = false;}
      if(QNQBqxFGUY == true){QNQBqxFGUY = false;}
      if(WYrtLlnmbP == true){WYrtLlnmbP = false;}
      if(ABaYCidWpI == true){ABaYCidWpI = false;}
      if(LngcJtBXqQ == true){LngcJtBXqQ = false;}
      if(gwxXBwWQSK == true){gwxXBwWQSK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OAMLMVQAZN
{ 
  void FNzRFRlepI()
  { 
      bool DfZsRxExcK = false;
      bool CyuiDCwnRR = false;
      bool hEmQRQgeAu = false;
      bool qasSoxBczn = false;
      bool zNmSYIanuy = false;
      bool lSTJNysJaA = false;
      bool QYxgTaFcsF = false;
      bool BTocSURUqJ = false;
      bool prjCJXHjEq = false;
      bool ErByXZQFyy = false;
      bool CytoxSdpps = false;
      bool fYRRKXotXw = false;
      bool TVXCBIRpFr = false;
      bool DMVsGryuEp = false;
      bool sQsLKeZjnz = false;
      bool kVhBegZqmn = false;
      bool AnkxoTCYLS = false;
      bool ZspgDDbMrV = false;
      bool ihBFHgdTOY = false;
      bool RGHQpFfuVp = false;
      string DursdWReEM;
      string FCMsCtjibB;
      string XHqeESJTdU;
      string WFUqrUPocj;
      string FsPeUyGPan;
      string RNSnlwENoK;
      string MxAipzhVAg;
      string dtGrwdqMJG;
      string LtspCImgEu;
      string QCARWHrfoV;
      string PkOsJXHZrH;
      string FrEhzSEKgg;
      string LBREQbsnUn;
      string lKXmpafzfe;
      string BMnxpXxRRE;
      string ChzHJOSJbh;
      string dSFDVtUQrY;
      string mEdBeyMUOs;
      string daVQlDLPda;
      string HVXyBiHkaw;
      if(DursdWReEM == PkOsJXHZrH){DfZsRxExcK = true;}
      else if(PkOsJXHZrH == DursdWReEM){CytoxSdpps = true;}
      if(FCMsCtjibB == FrEhzSEKgg){CyuiDCwnRR = true;}
      else if(FrEhzSEKgg == FCMsCtjibB){fYRRKXotXw = true;}
      if(XHqeESJTdU == LBREQbsnUn){hEmQRQgeAu = true;}
      else if(LBREQbsnUn == XHqeESJTdU){TVXCBIRpFr = true;}
      if(WFUqrUPocj == lKXmpafzfe){qasSoxBczn = true;}
      else if(lKXmpafzfe == WFUqrUPocj){DMVsGryuEp = true;}
      if(FsPeUyGPan == BMnxpXxRRE){zNmSYIanuy = true;}
      else if(BMnxpXxRRE == FsPeUyGPan){sQsLKeZjnz = true;}
      if(RNSnlwENoK == ChzHJOSJbh){lSTJNysJaA = true;}
      else if(ChzHJOSJbh == RNSnlwENoK){kVhBegZqmn = true;}
      if(MxAipzhVAg == dSFDVtUQrY){QYxgTaFcsF = true;}
      else if(dSFDVtUQrY == MxAipzhVAg){AnkxoTCYLS = true;}
      if(dtGrwdqMJG == mEdBeyMUOs){BTocSURUqJ = true;}
      if(LtspCImgEu == daVQlDLPda){prjCJXHjEq = true;}
      if(QCARWHrfoV == HVXyBiHkaw){ErByXZQFyy = true;}
      while(mEdBeyMUOs == dtGrwdqMJG){ZspgDDbMrV = true;}
      while(daVQlDLPda == daVQlDLPda){ihBFHgdTOY = true;}
      while(HVXyBiHkaw == HVXyBiHkaw){RGHQpFfuVp = true;}
      if(DfZsRxExcK == true){DfZsRxExcK = false;}
      if(CyuiDCwnRR == true){CyuiDCwnRR = false;}
      if(hEmQRQgeAu == true){hEmQRQgeAu = false;}
      if(qasSoxBczn == true){qasSoxBczn = false;}
      if(zNmSYIanuy == true){zNmSYIanuy = false;}
      if(lSTJNysJaA == true){lSTJNysJaA = false;}
      if(QYxgTaFcsF == true){QYxgTaFcsF = false;}
      if(BTocSURUqJ == true){BTocSURUqJ = false;}
      if(prjCJXHjEq == true){prjCJXHjEq = false;}
      if(ErByXZQFyy == true){ErByXZQFyy = false;}
      if(CytoxSdpps == true){CytoxSdpps = false;}
      if(fYRRKXotXw == true){fYRRKXotXw = false;}
      if(TVXCBIRpFr == true){TVXCBIRpFr = false;}
      if(DMVsGryuEp == true){DMVsGryuEp = false;}
      if(sQsLKeZjnz == true){sQsLKeZjnz = false;}
      if(kVhBegZqmn == true){kVhBegZqmn = false;}
      if(AnkxoTCYLS == true){AnkxoTCYLS = false;}
      if(ZspgDDbMrV == true){ZspgDDbMrV = false;}
      if(ihBFHgdTOY == true){ihBFHgdTOY = false;}
      if(RGHQpFfuVp == true){RGHQpFfuVp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UAZJXQGONL
{ 
  void bYktahQMSg()
  { 
      bool uPUykzkjRT = false;
      bool FwPIdFjLar = false;
      bool LytPlEqqUa = false;
      bool tcGnOGwblu = false;
      bool TRzPZkpLzt = false;
      bool VrVVAxVFLg = false;
      bool ItPpZcoasW = false;
      bool IIZfYtzdoB = false;
      bool OfqaFBHknR = false;
      bool jpPFmYBIox = false;
      bool wOSblNSoxF = false;
      bool xrQKScDokY = false;
      bool VDlamRrTsz = false;
      bool rpnrEzNOnr = false;
      bool iRniTrZFmK = false;
      bool UMWQarbqoT = false;
      bool UyuxMHDYGS = false;
      bool OnAsoDPDGt = false;
      bool rmgieeSXQL = false;
      bool WVZUWjVpVM = false;
      string AQhnKhDDKT;
      string cTryuIYhdt;
      string QXYsuthdHp;
      string CxgrYiPRCd;
      string hARMkKxRCK;
      string NiEmYbqorP;
      string zZuUQflAYM;
      string rHfAMPFLHj;
      string wQbwbTssTx;
      string qaYleHExwF;
      string XxsoRFDEaI;
      string VfgHThxzrx;
      string lrfbVQisUE;
      string KHPCLzXmeW;
      string PnSLaLtQSw;
      string KFFySfQQSA;
      string WKjVxOPduU;
      string KKUUgyZUBK;
      string WRZXtFCQjf;
      string hGTdzFExNM;
      if(AQhnKhDDKT == XxsoRFDEaI){uPUykzkjRT = true;}
      else if(XxsoRFDEaI == AQhnKhDDKT){wOSblNSoxF = true;}
      if(cTryuIYhdt == VfgHThxzrx){FwPIdFjLar = true;}
      else if(VfgHThxzrx == cTryuIYhdt){xrQKScDokY = true;}
      if(QXYsuthdHp == lrfbVQisUE){LytPlEqqUa = true;}
      else if(lrfbVQisUE == QXYsuthdHp){VDlamRrTsz = true;}
      if(CxgrYiPRCd == KHPCLzXmeW){tcGnOGwblu = true;}
      else if(KHPCLzXmeW == CxgrYiPRCd){rpnrEzNOnr = true;}
      if(hARMkKxRCK == PnSLaLtQSw){TRzPZkpLzt = true;}
      else if(PnSLaLtQSw == hARMkKxRCK){iRniTrZFmK = true;}
      if(NiEmYbqorP == KFFySfQQSA){VrVVAxVFLg = true;}
      else if(KFFySfQQSA == NiEmYbqorP){UMWQarbqoT = true;}
      if(zZuUQflAYM == WKjVxOPduU){ItPpZcoasW = true;}
      else if(WKjVxOPduU == zZuUQflAYM){UyuxMHDYGS = true;}
      if(rHfAMPFLHj == KKUUgyZUBK){IIZfYtzdoB = true;}
      if(wQbwbTssTx == WRZXtFCQjf){OfqaFBHknR = true;}
      if(qaYleHExwF == hGTdzFExNM){jpPFmYBIox = true;}
      while(KKUUgyZUBK == rHfAMPFLHj){OnAsoDPDGt = true;}
      while(WRZXtFCQjf == WRZXtFCQjf){rmgieeSXQL = true;}
      while(hGTdzFExNM == hGTdzFExNM){WVZUWjVpVM = true;}
      if(uPUykzkjRT == true){uPUykzkjRT = false;}
      if(FwPIdFjLar == true){FwPIdFjLar = false;}
      if(LytPlEqqUa == true){LytPlEqqUa = false;}
      if(tcGnOGwblu == true){tcGnOGwblu = false;}
      if(TRzPZkpLzt == true){TRzPZkpLzt = false;}
      if(VrVVAxVFLg == true){VrVVAxVFLg = false;}
      if(ItPpZcoasW == true){ItPpZcoasW = false;}
      if(IIZfYtzdoB == true){IIZfYtzdoB = false;}
      if(OfqaFBHknR == true){OfqaFBHknR = false;}
      if(jpPFmYBIox == true){jpPFmYBIox = false;}
      if(wOSblNSoxF == true){wOSblNSoxF = false;}
      if(xrQKScDokY == true){xrQKScDokY = false;}
      if(VDlamRrTsz == true){VDlamRrTsz = false;}
      if(rpnrEzNOnr == true){rpnrEzNOnr = false;}
      if(iRniTrZFmK == true){iRniTrZFmK = false;}
      if(UMWQarbqoT == true){UMWQarbqoT = false;}
      if(UyuxMHDYGS == true){UyuxMHDYGS = false;}
      if(OnAsoDPDGt == true){OnAsoDPDGt = false;}
      if(rmgieeSXQL == true){rmgieeSXQL = false;}
      if(WVZUWjVpVM == true){WVZUWjVpVM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZVVGNLYPNN
{ 
  void YBGuNDjAiV()
  { 
      bool VgRiqWKcbZ = false;
      bool fIFgODUGUs = false;
      bool qYEFmtxoxA = false;
      bool BUePBmghDx = false;
      bool OGYKuXGffV = false;
      bool neEIExcLww = false;
      bool YVfaXLdoeb = false;
      bool WlCWekztKO = false;
      bool nRIbMVPVLE = false;
      bool JUlHXraxlj = false;
      bool tQAEyBbhcS = false;
      bool xiBgIHMDOC = false;
      bool uHdaRBAuym = false;
      bool KCHZTWREcK = false;
      bool shsrHaSEyQ = false;
      bool eWijnmmZlw = false;
      bool AgipIuaaNk = false;
      bool oIaDIMOlSp = false;
      bool iwwhHmTXkg = false;
      bool jrRfKMzCiM = false;
      string stAFTJGClO;
      string EXkoRfrHYl;
      string KCKchPtogM;
      string OzJaYpfIwx;
      string ZfWmrwCQza;
      string kPUDRqiWWD;
      string OQVYAFNKQa;
      string AjLaLefXkk;
      string NdoGbyeFIh;
      string HIkriJKxlm;
      string iqAXaAEsqm;
      string KLlkpkbOxC;
      string ZICiTqySrC;
      string UikxCVdQea;
      string slNUWwVACy;
      string huzjNZoQEj;
      string BkAoSaZohT;
      string HKjWImtgLX;
      string UyQtUYiAjb;
      string gMMuYIlYCu;
      if(stAFTJGClO == iqAXaAEsqm){VgRiqWKcbZ = true;}
      else if(iqAXaAEsqm == stAFTJGClO){tQAEyBbhcS = true;}
      if(EXkoRfrHYl == KLlkpkbOxC){fIFgODUGUs = true;}
      else if(KLlkpkbOxC == EXkoRfrHYl){xiBgIHMDOC = true;}
      if(KCKchPtogM == ZICiTqySrC){qYEFmtxoxA = true;}
      else if(ZICiTqySrC == KCKchPtogM){uHdaRBAuym = true;}
      if(OzJaYpfIwx == UikxCVdQea){BUePBmghDx = true;}
      else if(UikxCVdQea == OzJaYpfIwx){KCHZTWREcK = true;}
      if(ZfWmrwCQza == slNUWwVACy){OGYKuXGffV = true;}
      else if(slNUWwVACy == ZfWmrwCQza){shsrHaSEyQ = true;}
      if(kPUDRqiWWD == huzjNZoQEj){neEIExcLww = true;}
      else if(huzjNZoQEj == kPUDRqiWWD){eWijnmmZlw = true;}
      if(OQVYAFNKQa == BkAoSaZohT){YVfaXLdoeb = true;}
      else if(BkAoSaZohT == OQVYAFNKQa){AgipIuaaNk = true;}
      if(AjLaLefXkk == HKjWImtgLX){WlCWekztKO = true;}
      if(NdoGbyeFIh == UyQtUYiAjb){nRIbMVPVLE = true;}
      if(HIkriJKxlm == gMMuYIlYCu){JUlHXraxlj = true;}
      while(HKjWImtgLX == AjLaLefXkk){oIaDIMOlSp = true;}
      while(UyQtUYiAjb == UyQtUYiAjb){iwwhHmTXkg = true;}
      while(gMMuYIlYCu == gMMuYIlYCu){jrRfKMzCiM = true;}
      if(VgRiqWKcbZ == true){VgRiqWKcbZ = false;}
      if(fIFgODUGUs == true){fIFgODUGUs = false;}
      if(qYEFmtxoxA == true){qYEFmtxoxA = false;}
      if(BUePBmghDx == true){BUePBmghDx = false;}
      if(OGYKuXGffV == true){OGYKuXGffV = false;}
      if(neEIExcLww == true){neEIExcLww = false;}
      if(YVfaXLdoeb == true){YVfaXLdoeb = false;}
      if(WlCWekztKO == true){WlCWekztKO = false;}
      if(nRIbMVPVLE == true){nRIbMVPVLE = false;}
      if(JUlHXraxlj == true){JUlHXraxlj = false;}
      if(tQAEyBbhcS == true){tQAEyBbhcS = false;}
      if(xiBgIHMDOC == true){xiBgIHMDOC = false;}
      if(uHdaRBAuym == true){uHdaRBAuym = false;}
      if(KCHZTWREcK == true){KCHZTWREcK = false;}
      if(shsrHaSEyQ == true){shsrHaSEyQ = false;}
      if(eWijnmmZlw == true){eWijnmmZlw = false;}
      if(AgipIuaaNk == true){AgipIuaaNk = false;}
      if(oIaDIMOlSp == true){oIaDIMOlSp = false;}
      if(iwwhHmTXkg == true){iwwhHmTXkg = false;}
      if(jrRfKMzCiM == true){jrRfKMzCiM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NJINGHVVZL
{ 
  void WYhMAztXnH()
  { 
      bool ULkNXDkGIK = false;
      bool zRrVVaJawc = false;
      bool LkIbmrwQlr = false;
      bool pwNxhxcEnR = false;
      bool PWdCdIzdqu = false;
      bool TORfsiCIZe = false;
      bool GTTPTCEtnX = false;
      bool xEldMnHGxe = false;
      bool sSZqYbegEy = false;
      bool uTeJLwCNhb = false;
      bool DEpTyObmTE = false;
      bool bwLukntcqq = false;
      bool XXpoccZcSQ = false;
      bool ksXVaocGrJ = false;
      bool ArNzWyIjXX = false;
      bool CZWpDfOApU = false;
      bool ozTCShXpTw = false;
      bool LmjgqfJpSd = false;
      bool UoEuOLWgRt = false;
      bool ZbPXUBXKfo = false;
      string CtfTpoPQOI;
      string kDLJVnzAZh;
      string RpjApypwhm;
      string CpwXmrnLyb;
      string pRMMuFkNzU;
      string gYFerLKfcq;
      string yShaFtGnWc;
      string zmBxrzdWFk;
      string McwMGdkRea;
      string gIhGcWjkGA;
      string yxpVVtXHls;
      string hnardVWUUb;
      string JoIwwqEuTU;
      string PsQEmPlZqL;
      string GcelsshpbH;
      string AOPdqIntZe;
      string obmRcnXVFO;
      string jwdJVfJVCD;
      string IOSMUAclNd;
      string aqAMWdoNIE;
      if(CtfTpoPQOI == yxpVVtXHls){ULkNXDkGIK = true;}
      else if(yxpVVtXHls == CtfTpoPQOI){DEpTyObmTE = true;}
      if(kDLJVnzAZh == hnardVWUUb){zRrVVaJawc = true;}
      else if(hnardVWUUb == kDLJVnzAZh){bwLukntcqq = true;}
      if(RpjApypwhm == JoIwwqEuTU){LkIbmrwQlr = true;}
      else if(JoIwwqEuTU == RpjApypwhm){XXpoccZcSQ = true;}
      if(CpwXmrnLyb == PsQEmPlZqL){pwNxhxcEnR = true;}
      else if(PsQEmPlZqL == CpwXmrnLyb){ksXVaocGrJ = true;}
      if(pRMMuFkNzU == GcelsshpbH){PWdCdIzdqu = true;}
      else if(GcelsshpbH == pRMMuFkNzU){ArNzWyIjXX = true;}
      if(gYFerLKfcq == AOPdqIntZe){TORfsiCIZe = true;}
      else if(AOPdqIntZe == gYFerLKfcq){CZWpDfOApU = true;}
      if(yShaFtGnWc == obmRcnXVFO){GTTPTCEtnX = true;}
      else if(obmRcnXVFO == yShaFtGnWc){ozTCShXpTw = true;}
      if(zmBxrzdWFk == jwdJVfJVCD){xEldMnHGxe = true;}
      if(McwMGdkRea == IOSMUAclNd){sSZqYbegEy = true;}
      if(gIhGcWjkGA == aqAMWdoNIE){uTeJLwCNhb = true;}
      while(jwdJVfJVCD == zmBxrzdWFk){LmjgqfJpSd = true;}
      while(IOSMUAclNd == IOSMUAclNd){UoEuOLWgRt = true;}
      while(aqAMWdoNIE == aqAMWdoNIE){ZbPXUBXKfo = true;}
      if(ULkNXDkGIK == true){ULkNXDkGIK = false;}
      if(zRrVVaJawc == true){zRrVVaJawc = false;}
      if(LkIbmrwQlr == true){LkIbmrwQlr = false;}
      if(pwNxhxcEnR == true){pwNxhxcEnR = false;}
      if(PWdCdIzdqu == true){PWdCdIzdqu = false;}
      if(TORfsiCIZe == true){TORfsiCIZe = false;}
      if(GTTPTCEtnX == true){GTTPTCEtnX = false;}
      if(xEldMnHGxe == true){xEldMnHGxe = false;}
      if(sSZqYbegEy == true){sSZqYbegEy = false;}
      if(uTeJLwCNhb == true){uTeJLwCNhb = false;}
      if(DEpTyObmTE == true){DEpTyObmTE = false;}
      if(bwLukntcqq == true){bwLukntcqq = false;}
      if(XXpoccZcSQ == true){XXpoccZcSQ = false;}
      if(ksXVaocGrJ == true){ksXVaocGrJ = false;}
      if(ArNzWyIjXX == true){ArNzWyIjXX = false;}
      if(CZWpDfOApU == true){CZWpDfOApU = false;}
      if(ozTCShXpTw == true){ozTCShXpTw = false;}
      if(LmjgqfJpSd == true){LmjgqfJpSd = false;}
      if(UoEuOLWgRt == true){UoEuOLWgRt = false;}
      if(ZbPXUBXKfo == true){ZbPXUBXKfo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LAWHTBHCSB
{ 
  void HYXcJlNOuT()
  { 
      bool prwkOHGIbx = false;
      bool dyuiJmWMqE = false;
      bool wjSPONhjnr = false;
      bool bgkTKHVryX = false;
      bool BiexrjLhjy = false;
      bool GKDltGYfWA = false;
      bool ZVTjVxNbYB = false;
      bool RdOTDNEVXe = false;
      bool BzzpkQdyYE = false;
      bool ioUxxeOtau = false;
      bool WjJifbwjig = false;
      bool BDIrzaVdzF = false;
      bool SOCTSbJQVX = false;
      bool yKucHQpQJJ = false;
      bool TsOrCfgcxW = false;
      bool IjuVbHhoQE = false;
      bool SfNKhqHfji = false;
      bool jFUpkYzJQm = false;
      bool ufSzPOPYAA = false;
      bool hBAEpnfEKL = false;
      string SmymtSjGRu;
      string XBeDraoOTg;
      string minCuVdIDD;
      string FEgjZcHpNF;
      string jXLlOTDWji;
      string GOjGWiyuqX;
      string oaDNpSTudO;
      string SzBNwOWBnb;
      string RGYTxqUaMp;
      string eMyoQJUywu;
      string zIsVPGMWJH;
      string MwGPGhCiPz;
      string yshnjGBMwm;
      string tYFrcJMDEp;
      string dyQFdhFihi;
      string HlhxxGaFkJ;
      string FAZWNmqNlx;
      string UzeZUzbcJB;
      string ARdMfIqHuW;
      string hHRtkcXtqp;
      if(SmymtSjGRu == zIsVPGMWJH){prwkOHGIbx = true;}
      else if(zIsVPGMWJH == SmymtSjGRu){WjJifbwjig = true;}
      if(XBeDraoOTg == MwGPGhCiPz){dyuiJmWMqE = true;}
      else if(MwGPGhCiPz == XBeDraoOTg){BDIrzaVdzF = true;}
      if(minCuVdIDD == yshnjGBMwm){wjSPONhjnr = true;}
      else if(yshnjGBMwm == minCuVdIDD){SOCTSbJQVX = true;}
      if(FEgjZcHpNF == tYFrcJMDEp){bgkTKHVryX = true;}
      else if(tYFrcJMDEp == FEgjZcHpNF){yKucHQpQJJ = true;}
      if(jXLlOTDWji == dyQFdhFihi){BiexrjLhjy = true;}
      else if(dyQFdhFihi == jXLlOTDWji){TsOrCfgcxW = true;}
      if(GOjGWiyuqX == HlhxxGaFkJ){GKDltGYfWA = true;}
      else if(HlhxxGaFkJ == GOjGWiyuqX){IjuVbHhoQE = true;}
      if(oaDNpSTudO == FAZWNmqNlx){ZVTjVxNbYB = true;}
      else if(FAZWNmqNlx == oaDNpSTudO){SfNKhqHfji = true;}
      if(SzBNwOWBnb == UzeZUzbcJB){RdOTDNEVXe = true;}
      if(RGYTxqUaMp == ARdMfIqHuW){BzzpkQdyYE = true;}
      if(eMyoQJUywu == hHRtkcXtqp){ioUxxeOtau = true;}
      while(UzeZUzbcJB == SzBNwOWBnb){jFUpkYzJQm = true;}
      while(ARdMfIqHuW == ARdMfIqHuW){ufSzPOPYAA = true;}
      while(hHRtkcXtqp == hHRtkcXtqp){hBAEpnfEKL = true;}
      if(prwkOHGIbx == true){prwkOHGIbx = false;}
      if(dyuiJmWMqE == true){dyuiJmWMqE = false;}
      if(wjSPONhjnr == true){wjSPONhjnr = false;}
      if(bgkTKHVryX == true){bgkTKHVryX = false;}
      if(BiexrjLhjy == true){BiexrjLhjy = false;}
      if(GKDltGYfWA == true){GKDltGYfWA = false;}
      if(ZVTjVxNbYB == true){ZVTjVxNbYB = false;}
      if(RdOTDNEVXe == true){RdOTDNEVXe = false;}
      if(BzzpkQdyYE == true){BzzpkQdyYE = false;}
      if(ioUxxeOtau == true){ioUxxeOtau = false;}
      if(WjJifbwjig == true){WjJifbwjig = false;}
      if(BDIrzaVdzF == true){BDIrzaVdzF = false;}
      if(SOCTSbJQVX == true){SOCTSbJQVX = false;}
      if(yKucHQpQJJ == true){yKucHQpQJJ = false;}
      if(TsOrCfgcxW == true){TsOrCfgcxW = false;}
      if(IjuVbHhoQE == true){IjuVbHhoQE = false;}
      if(SfNKhqHfji == true){SfNKhqHfji = false;}
      if(jFUpkYzJQm == true){jFUpkYzJQm = false;}
      if(ufSzPOPYAA == true){ufSzPOPYAA = false;}
      if(hBAEpnfEKL == true){hBAEpnfEKL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IMOZLVNUDA
{ 
  void gRwXuKrdff()
  { 
      bool YUTgOHHmlW = false;
      bool gdngrxYiLK = false;
      bool dWrEJPtIrc = false;
      bool TCHBkmWXYz = false;
      bool xgrfZTPEWf = false;
      bool ptbouBbOWz = false;
      bool MztIDdWmwF = false;
      bool ZAJMNxeMeo = false;
      bool AolLmYaSFi = false;
      bool KIBZlxlibu = false;
      bool xbIRFokPby = false;
      bool VOjhzXNiVd = false;
      bool DDhMtRziZP = false;
      bool KwkiqXgTFx = false;
      bool nLqGMuYSZO = false;
      bool jDNxrtsuWn = false;
      bool pBoLmZdApb = false;
      bool qscXprMbzz = false;
      bool sfJLfHimqx = false;
      bool dkwRHlVeSm = false;
      string JTIhYOKpHX;
      string amEIhyMxgy;
      string sBnAomuyRl;
      string UhVSJOqRTo;
      string IpVRKmtNte;
      string HClCDIfHsk;
      string TMYVCsQlzS;
      string HucrpCeWoB;
      string rgDleRuTPA;
      string iiXhUwRAOR;
      string VINaXLYtMA;
      string cJSrslIlpk;
      string xxWyjXWuWs;
      string keHWfjScOS;
      string rAGOXZQfoh;
      string mfKdTXlPqz;
      string odWSPyBuMI;
      string TfXWrxqHaJ;
      string HqFnGFTdCH;
      string yDlOdOcnzZ;
      if(JTIhYOKpHX == VINaXLYtMA){YUTgOHHmlW = true;}
      else if(VINaXLYtMA == JTIhYOKpHX){xbIRFokPby = true;}
      if(amEIhyMxgy == cJSrslIlpk){gdngrxYiLK = true;}
      else if(cJSrslIlpk == amEIhyMxgy){VOjhzXNiVd = true;}
      if(sBnAomuyRl == xxWyjXWuWs){dWrEJPtIrc = true;}
      else if(xxWyjXWuWs == sBnAomuyRl){DDhMtRziZP = true;}
      if(UhVSJOqRTo == keHWfjScOS){TCHBkmWXYz = true;}
      else if(keHWfjScOS == UhVSJOqRTo){KwkiqXgTFx = true;}
      if(IpVRKmtNte == rAGOXZQfoh){xgrfZTPEWf = true;}
      else if(rAGOXZQfoh == IpVRKmtNte){nLqGMuYSZO = true;}
      if(HClCDIfHsk == mfKdTXlPqz){ptbouBbOWz = true;}
      else if(mfKdTXlPqz == HClCDIfHsk){jDNxrtsuWn = true;}
      if(TMYVCsQlzS == odWSPyBuMI){MztIDdWmwF = true;}
      else if(odWSPyBuMI == TMYVCsQlzS){pBoLmZdApb = true;}
      if(HucrpCeWoB == TfXWrxqHaJ){ZAJMNxeMeo = true;}
      if(rgDleRuTPA == HqFnGFTdCH){AolLmYaSFi = true;}
      if(iiXhUwRAOR == yDlOdOcnzZ){KIBZlxlibu = true;}
      while(TfXWrxqHaJ == HucrpCeWoB){qscXprMbzz = true;}
      while(HqFnGFTdCH == HqFnGFTdCH){sfJLfHimqx = true;}
      while(yDlOdOcnzZ == yDlOdOcnzZ){dkwRHlVeSm = true;}
      if(YUTgOHHmlW == true){YUTgOHHmlW = false;}
      if(gdngrxYiLK == true){gdngrxYiLK = false;}
      if(dWrEJPtIrc == true){dWrEJPtIrc = false;}
      if(TCHBkmWXYz == true){TCHBkmWXYz = false;}
      if(xgrfZTPEWf == true){xgrfZTPEWf = false;}
      if(ptbouBbOWz == true){ptbouBbOWz = false;}
      if(MztIDdWmwF == true){MztIDdWmwF = false;}
      if(ZAJMNxeMeo == true){ZAJMNxeMeo = false;}
      if(AolLmYaSFi == true){AolLmYaSFi = false;}
      if(KIBZlxlibu == true){KIBZlxlibu = false;}
      if(xbIRFokPby == true){xbIRFokPby = false;}
      if(VOjhzXNiVd == true){VOjhzXNiVd = false;}
      if(DDhMtRziZP == true){DDhMtRziZP = false;}
      if(KwkiqXgTFx == true){KwkiqXgTFx = false;}
      if(nLqGMuYSZO == true){nLqGMuYSZO = false;}
      if(jDNxrtsuWn == true){jDNxrtsuWn = false;}
      if(pBoLmZdApb == true){pBoLmZdApb = false;}
      if(qscXprMbzz == true){qscXprMbzz = false;}
      if(sfJLfHimqx == true){sfJLfHimqx = false;}
      if(dkwRHlVeSm == true){dkwRHlVeSm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WEGGHRVZZE
{ 
  void gOcQNHtnSm()
  { 
      bool QKcgWpAQDq = false;
      bool edxcmwZGgg = false;
      bool dYdiCyhDYF = false;
      bool oiGyZteYGg = false;
      bool uYpkxNEysL = false;
      bool QamRkrgsdX = false;
      bool IwqxBuWyDr = false;
      bool QAzzkFhrln = false;
      bool siKMnOuoMh = false;
      bool NkthYygrjB = false;
      bool pFuAuQangf = false;
      bool JnGpeYleIm = false;
      bool AhlUdfGRZm = false;
      bool XpIkymnJRX = false;
      bool nHIfXYdEDA = false;
      bool LCixBHTZWO = false;
      bool JINsITfVqq = false;
      bool jcMjyrZFxF = false;
      bool BBNZaUGLjp = false;
      bool TOmDNesOXE = false;
      string YCawuXwlYd;
      string agdhjoGxVc;
      string JgflGdgCpS;
      string bhEMmQDAQe;
      string zmyTtliGMB;
      string GsdEdrWnpR;
      string ptuFBrbQuT;
      string lGfqcWhLrT;
      string uaonLiEAiu;
      string tOJznFqrSB;
      string JRLsPAMmbH;
      string KKwVWPFHsS;
      string nbgzZXwgCX;
      string eospJcOuXL;
      string VRXakiRnbY;
      string ziyzNhjLTr;
      string DejEbURGLt;
      string BJihwWDFOp;
      string FHFdXupscb;
      string rCbfIpgTzP;
      if(YCawuXwlYd == JRLsPAMmbH){QKcgWpAQDq = true;}
      else if(JRLsPAMmbH == YCawuXwlYd){pFuAuQangf = true;}
      if(agdhjoGxVc == KKwVWPFHsS){edxcmwZGgg = true;}
      else if(KKwVWPFHsS == agdhjoGxVc){JnGpeYleIm = true;}
      if(JgflGdgCpS == nbgzZXwgCX){dYdiCyhDYF = true;}
      else if(nbgzZXwgCX == JgflGdgCpS){AhlUdfGRZm = true;}
      if(bhEMmQDAQe == eospJcOuXL){oiGyZteYGg = true;}
      else if(eospJcOuXL == bhEMmQDAQe){XpIkymnJRX = true;}
      if(zmyTtliGMB == VRXakiRnbY){uYpkxNEysL = true;}
      else if(VRXakiRnbY == zmyTtliGMB){nHIfXYdEDA = true;}
      if(GsdEdrWnpR == ziyzNhjLTr){QamRkrgsdX = true;}
      else if(ziyzNhjLTr == GsdEdrWnpR){LCixBHTZWO = true;}
      if(ptuFBrbQuT == DejEbURGLt){IwqxBuWyDr = true;}
      else if(DejEbURGLt == ptuFBrbQuT){JINsITfVqq = true;}
      if(lGfqcWhLrT == BJihwWDFOp){QAzzkFhrln = true;}
      if(uaonLiEAiu == FHFdXupscb){siKMnOuoMh = true;}
      if(tOJznFqrSB == rCbfIpgTzP){NkthYygrjB = true;}
      while(BJihwWDFOp == lGfqcWhLrT){jcMjyrZFxF = true;}
      while(FHFdXupscb == FHFdXupscb){BBNZaUGLjp = true;}
      while(rCbfIpgTzP == rCbfIpgTzP){TOmDNesOXE = true;}
      if(QKcgWpAQDq == true){QKcgWpAQDq = false;}
      if(edxcmwZGgg == true){edxcmwZGgg = false;}
      if(dYdiCyhDYF == true){dYdiCyhDYF = false;}
      if(oiGyZteYGg == true){oiGyZteYGg = false;}
      if(uYpkxNEysL == true){uYpkxNEysL = false;}
      if(QamRkrgsdX == true){QamRkrgsdX = false;}
      if(IwqxBuWyDr == true){IwqxBuWyDr = false;}
      if(QAzzkFhrln == true){QAzzkFhrln = false;}
      if(siKMnOuoMh == true){siKMnOuoMh = false;}
      if(NkthYygrjB == true){NkthYygrjB = false;}
      if(pFuAuQangf == true){pFuAuQangf = false;}
      if(JnGpeYleIm == true){JnGpeYleIm = false;}
      if(AhlUdfGRZm == true){AhlUdfGRZm = false;}
      if(XpIkymnJRX == true){XpIkymnJRX = false;}
      if(nHIfXYdEDA == true){nHIfXYdEDA = false;}
      if(LCixBHTZWO == true){LCixBHTZWO = false;}
      if(JINsITfVqq == true){JINsITfVqq = false;}
      if(jcMjyrZFxF == true){jcMjyrZFxF = false;}
      if(BBNZaUGLjp == true){BBNZaUGLjp = false;}
      if(TOmDNesOXE == true){TOmDNesOXE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QFETIQGMLU
{ 
  void QKCBIxLDjx()
  { 
      bool pJFpzMhqlS = false;
      bool BZHnTfaoNQ = false;
      bool tJAFoiKnQj = false;
      bool jjoifkrnmd = false;
      bool gHBdDtgzEn = false;
      bool CQNgKgIzBQ = false;
      bool BsZChQjXHi = false;
      bool mlCijmIWBt = false;
      bool CLibgTVIYz = false;
      bool csmWbngzum = false;
      bool KJqVBPOexX = false;
      bool YkyGNpJxVO = false;
      bool tbzHFszeGu = false;
      bool FJaOjsTNaQ = false;
      bool FqKAaqtfIl = false;
      bool djcgrhJiPH = false;
      bool QiXBSPKjWU = false;
      bool VwWEJCRygO = false;
      bool zTWURVftVB = false;
      bool ikySAVTIgL = false;
      string eQmNAiweQp;
      string lfKahCFYAg;
      string EYuCKpGebq;
      string ZwBTXusxCJ;
      string XylLTkYmJY;
      string AHcOxGVjCJ;
      string cRDZPoepDl;
      string JIWqIFmjhY;
      string RTVCpSSlWQ;
      string ZItrgGuLwd;
      string GhiWPrjlGq;
      string TkBdrIwAiw;
      string VrTlLBOeKB;
      string KamESikymy;
      string igfexnGPzX;
      string KubzHNOwLO;
      string dFbEgrxxKJ;
      string XxNkNoLnoW;
      string tyelqPynwF;
      string UnmYTcFbyF;
      if(eQmNAiweQp == GhiWPrjlGq){pJFpzMhqlS = true;}
      else if(GhiWPrjlGq == eQmNAiweQp){KJqVBPOexX = true;}
      if(lfKahCFYAg == TkBdrIwAiw){BZHnTfaoNQ = true;}
      else if(TkBdrIwAiw == lfKahCFYAg){YkyGNpJxVO = true;}
      if(EYuCKpGebq == VrTlLBOeKB){tJAFoiKnQj = true;}
      else if(VrTlLBOeKB == EYuCKpGebq){tbzHFszeGu = true;}
      if(ZwBTXusxCJ == KamESikymy){jjoifkrnmd = true;}
      else if(KamESikymy == ZwBTXusxCJ){FJaOjsTNaQ = true;}
      if(XylLTkYmJY == igfexnGPzX){gHBdDtgzEn = true;}
      else if(igfexnGPzX == XylLTkYmJY){FqKAaqtfIl = true;}
      if(AHcOxGVjCJ == KubzHNOwLO){CQNgKgIzBQ = true;}
      else if(KubzHNOwLO == AHcOxGVjCJ){djcgrhJiPH = true;}
      if(cRDZPoepDl == dFbEgrxxKJ){BsZChQjXHi = true;}
      else if(dFbEgrxxKJ == cRDZPoepDl){QiXBSPKjWU = true;}
      if(JIWqIFmjhY == XxNkNoLnoW){mlCijmIWBt = true;}
      if(RTVCpSSlWQ == tyelqPynwF){CLibgTVIYz = true;}
      if(ZItrgGuLwd == UnmYTcFbyF){csmWbngzum = true;}
      while(XxNkNoLnoW == JIWqIFmjhY){VwWEJCRygO = true;}
      while(tyelqPynwF == tyelqPynwF){zTWURVftVB = true;}
      while(UnmYTcFbyF == UnmYTcFbyF){ikySAVTIgL = true;}
      if(pJFpzMhqlS == true){pJFpzMhqlS = false;}
      if(BZHnTfaoNQ == true){BZHnTfaoNQ = false;}
      if(tJAFoiKnQj == true){tJAFoiKnQj = false;}
      if(jjoifkrnmd == true){jjoifkrnmd = false;}
      if(gHBdDtgzEn == true){gHBdDtgzEn = false;}
      if(CQNgKgIzBQ == true){CQNgKgIzBQ = false;}
      if(BsZChQjXHi == true){BsZChQjXHi = false;}
      if(mlCijmIWBt == true){mlCijmIWBt = false;}
      if(CLibgTVIYz == true){CLibgTVIYz = false;}
      if(csmWbngzum == true){csmWbngzum = false;}
      if(KJqVBPOexX == true){KJqVBPOexX = false;}
      if(YkyGNpJxVO == true){YkyGNpJxVO = false;}
      if(tbzHFszeGu == true){tbzHFszeGu = false;}
      if(FJaOjsTNaQ == true){FJaOjsTNaQ = false;}
      if(FqKAaqtfIl == true){FqKAaqtfIl = false;}
      if(djcgrhJiPH == true){djcgrhJiPH = false;}
      if(QiXBSPKjWU == true){QiXBSPKjWU = false;}
      if(VwWEJCRygO == true){VwWEJCRygO = false;}
      if(zTWURVftVB == true){zTWURVftVB = false;}
      if(ikySAVTIgL == true){ikySAVTIgL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HDSKMVLYRZ
{ 
  void azQLWbQeJA()
  { 
      bool oudXUIThWA = false;
      bool qhUrzpieed = false;
      bool TarlLxMXoY = false;
      bool ninZzxEUMj = false;
      bool zoDoJtdZjL = false;
      bool mBIuLNDrLW = false;
      bool uurxMHturB = false;
      bool kNStedXCbR = false;
      bool TlmdllasNl = false;
      bool sLIpnDxGcB = false;
      bool zhhiZYiNQg = false;
      bool pBPtDJIOKZ = false;
      bool gAgGHZFbGa = false;
      bool gRYaRkEEDN = false;
      bool DMcfwrwOle = false;
      bool uhuDTyAbaA = false;
      bool SGHoAYcocR = false;
      bool FDLxVUXBKP = false;
      bool cqpbezVUGS = false;
      bool jccCtxFmfX = false;
      string QcfwAJZcCG;
      string OxVTwCnMNx;
      string yrgtokOlAm;
      string jwGThfIXlf;
      string DoFeAihnbI;
      string nHrwCYulGO;
      string umbPVRpBkP;
      string sQahtIlBsG;
      string DaKrycDKQJ;
      string kVQWjPMpJi;
      string rfCLPXfKBt;
      string msrALTcjRr;
      string NejbeWzExe;
      string wwrKNXYybZ;
      string xsJWWqdQLP;
      string lbYRUMuZfr;
      string YbMWyqBhln;
      string udHqtUVNFn;
      string shrgrTWZpA;
      string byRjBVfmYf;
      if(QcfwAJZcCG == rfCLPXfKBt){oudXUIThWA = true;}
      else if(rfCLPXfKBt == QcfwAJZcCG){zhhiZYiNQg = true;}
      if(OxVTwCnMNx == msrALTcjRr){qhUrzpieed = true;}
      else if(msrALTcjRr == OxVTwCnMNx){pBPtDJIOKZ = true;}
      if(yrgtokOlAm == NejbeWzExe){TarlLxMXoY = true;}
      else if(NejbeWzExe == yrgtokOlAm){gAgGHZFbGa = true;}
      if(jwGThfIXlf == wwrKNXYybZ){ninZzxEUMj = true;}
      else if(wwrKNXYybZ == jwGThfIXlf){gRYaRkEEDN = true;}
      if(DoFeAihnbI == xsJWWqdQLP){zoDoJtdZjL = true;}
      else if(xsJWWqdQLP == DoFeAihnbI){DMcfwrwOle = true;}
      if(nHrwCYulGO == lbYRUMuZfr){mBIuLNDrLW = true;}
      else if(lbYRUMuZfr == nHrwCYulGO){uhuDTyAbaA = true;}
      if(umbPVRpBkP == YbMWyqBhln){uurxMHturB = true;}
      else if(YbMWyqBhln == umbPVRpBkP){SGHoAYcocR = true;}
      if(sQahtIlBsG == udHqtUVNFn){kNStedXCbR = true;}
      if(DaKrycDKQJ == shrgrTWZpA){TlmdllasNl = true;}
      if(kVQWjPMpJi == byRjBVfmYf){sLIpnDxGcB = true;}
      while(udHqtUVNFn == sQahtIlBsG){FDLxVUXBKP = true;}
      while(shrgrTWZpA == shrgrTWZpA){cqpbezVUGS = true;}
      while(byRjBVfmYf == byRjBVfmYf){jccCtxFmfX = true;}
      if(oudXUIThWA == true){oudXUIThWA = false;}
      if(qhUrzpieed == true){qhUrzpieed = false;}
      if(TarlLxMXoY == true){TarlLxMXoY = false;}
      if(ninZzxEUMj == true){ninZzxEUMj = false;}
      if(zoDoJtdZjL == true){zoDoJtdZjL = false;}
      if(mBIuLNDrLW == true){mBIuLNDrLW = false;}
      if(uurxMHturB == true){uurxMHturB = false;}
      if(kNStedXCbR == true){kNStedXCbR = false;}
      if(TlmdllasNl == true){TlmdllasNl = false;}
      if(sLIpnDxGcB == true){sLIpnDxGcB = false;}
      if(zhhiZYiNQg == true){zhhiZYiNQg = false;}
      if(pBPtDJIOKZ == true){pBPtDJIOKZ = false;}
      if(gAgGHZFbGa == true){gAgGHZFbGa = false;}
      if(gRYaRkEEDN == true){gRYaRkEEDN = false;}
      if(DMcfwrwOle == true){DMcfwrwOle = false;}
      if(uhuDTyAbaA == true){uhuDTyAbaA = false;}
      if(SGHoAYcocR == true){SGHoAYcocR = false;}
      if(FDLxVUXBKP == true){FDLxVUXBKP = false;}
      if(cqpbezVUGS == true){cqpbezVUGS = false;}
      if(jccCtxFmfX == true){jccCtxFmfX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WOPGJSWRAH
{ 
  void SZSEdrWJUu()
  { 
      bool LUeJpuTiah = false;
      bool CuQhVSFdai = false;
      bool qFOkDnOQbn = false;
      bool RBtfXUDztu = false;
      bool tdBdOpTwmO = false;
      bool TeUkLFFsGB = false;
      bool fCHmPBAjKB = false;
      bool PFjfnMDjWM = false;
      bool TRdMTmgIUR = false;
      bool OKsrPrWOOM = false;
      bool pilkzOuowz = false;
      bool CVVshNYuSc = false;
      bool UrPrmELqQw = false;
      bool onVKWjerMF = false;
      bool rrMVPrnAKB = false;
      bool SbwkrxTtyt = false;
      bool CDYzJNALVx = false;
      bool ighNjcesbt = false;
      bool QKgOdNrjRY = false;
      bool QksRCnTNMC = false;
      string lYQQHOtAhu;
      string XyijbFTApb;
      string sePjQjaKql;
      string fhYbZDaBGO;
      string PxjGBlyzSa;
      string jSrLCHJgzW;
      string miJwPpZGJX;
      string eRsbMuuIhe;
      string lbrPBNoNYS;
      string ttCjafmnqL;
      string MqpuwRYPyG;
      string LAyUjLqstC;
      string BLgpckPJAf;
      string IHRWRukwTj;
      string nYOSHtugzP;
      string ossnKAJARK;
      string BOPSyEhaCo;
      string ZtZJNbxOii;
      string ohJkqONcMR;
      string kkeIhZJwUC;
      if(lYQQHOtAhu == MqpuwRYPyG){LUeJpuTiah = true;}
      else if(MqpuwRYPyG == lYQQHOtAhu){pilkzOuowz = true;}
      if(XyijbFTApb == LAyUjLqstC){CuQhVSFdai = true;}
      else if(LAyUjLqstC == XyijbFTApb){CVVshNYuSc = true;}
      if(sePjQjaKql == BLgpckPJAf){qFOkDnOQbn = true;}
      else if(BLgpckPJAf == sePjQjaKql){UrPrmELqQw = true;}
      if(fhYbZDaBGO == IHRWRukwTj){RBtfXUDztu = true;}
      else if(IHRWRukwTj == fhYbZDaBGO){onVKWjerMF = true;}
      if(PxjGBlyzSa == nYOSHtugzP){tdBdOpTwmO = true;}
      else if(nYOSHtugzP == PxjGBlyzSa){rrMVPrnAKB = true;}
      if(jSrLCHJgzW == ossnKAJARK){TeUkLFFsGB = true;}
      else if(ossnKAJARK == jSrLCHJgzW){SbwkrxTtyt = true;}
      if(miJwPpZGJX == BOPSyEhaCo){fCHmPBAjKB = true;}
      else if(BOPSyEhaCo == miJwPpZGJX){CDYzJNALVx = true;}
      if(eRsbMuuIhe == ZtZJNbxOii){PFjfnMDjWM = true;}
      if(lbrPBNoNYS == ohJkqONcMR){TRdMTmgIUR = true;}
      if(ttCjafmnqL == kkeIhZJwUC){OKsrPrWOOM = true;}
      while(ZtZJNbxOii == eRsbMuuIhe){ighNjcesbt = true;}
      while(ohJkqONcMR == ohJkqONcMR){QKgOdNrjRY = true;}
      while(kkeIhZJwUC == kkeIhZJwUC){QksRCnTNMC = true;}
      if(LUeJpuTiah == true){LUeJpuTiah = false;}
      if(CuQhVSFdai == true){CuQhVSFdai = false;}
      if(qFOkDnOQbn == true){qFOkDnOQbn = false;}
      if(RBtfXUDztu == true){RBtfXUDztu = false;}
      if(tdBdOpTwmO == true){tdBdOpTwmO = false;}
      if(TeUkLFFsGB == true){TeUkLFFsGB = false;}
      if(fCHmPBAjKB == true){fCHmPBAjKB = false;}
      if(PFjfnMDjWM == true){PFjfnMDjWM = false;}
      if(TRdMTmgIUR == true){TRdMTmgIUR = false;}
      if(OKsrPrWOOM == true){OKsrPrWOOM = false;}
      if(pilkzOuowz == true){pilkzOuowz = false;}
      if(CVVshNYuSc == true){CVVshNYuSc = false;}
      if(UrPrmELqQw == true){UrPrmELqQw = false;}
      if(onVKWjerMF == true){onVKWjerMF = false;}
      if(rrMVPrnAKB == true){rrMVPrnAKB = false;}
      if(SbwkrxTtyt == true){SbwkrxTtyt = false;}
      if(CDYzJNALVx == true){CDYzJNALVx = false;}
      if(ighNjcesbt == true){ighNjcesbt = false;}
      if(QKgOdNrjRY == true){QKgOdNrjRY = false;}
      if(QksRCnTNMC == true){QksRCnTNMC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFHNNCHDIL
{ 
  void QkLzxHgjtK()
  { 
      bool DbsmdOwNhU = false;
      bool rODYAGfSHP = false;
      bool rbEQlfVkwR = false;
      bool AGyelySmdr = false;
      bool lIcFoYgXCs = false;
      bool SFYizbXbBx = false;
      bool rLRPUkPXmC = false;
      bool nsoPdiyyaN = false;
      bool zyiDzthOeK = false;
      bool apkfzZqMkD = false;
      bool IIjzFYPJEQ = false;
      bool cYBmxsbNPZ = false;
      bool DAscayHIPE = false;
      bool qkNWEpNiya = false;
      bool eYJOgCnxiF = false;
      bool ydxLAHPHXG = false;
      bool RHsAYqKdiG = false;
      bool fsOoudpduY = false;
      bool JJZJGNnCWx = false;
      bool aGKqIWeIpo = false;
      string gxwHQlJIKq;
      string aeNojwuzgz;
      string jdUGTfyXyL;
      string VazBHPBpXJ;
      string zNXpRsVkPG;
      string ZVzCmDbpmj;
      string nlKzUzeLhT;
      string uFbWAVGena;
      string KMHqkzaxOE;
      string mKCmUMDXUS;
      string NJDuLTtbCQ;
      string xxCLZaeSNV;
      string XhwdfjCnCn;
      string ShJVNAJLeQ;
      string EztyGpIqNt;
      string gjKztfMZOb;
      string RGZNyPmfyZ;
      string QSnwQYmyWp;
      string aLaHGhWKah;
      string mjwCzyYfzq;
      if(gxwHQlJIKq == NJDuLTtbCQ){DbsmdOwNhU = true;}
      else if(NJDuLTtbCQ == gxwHQlJIKq){IIjzFYPJEQ = true;}
      if(aeNojwuzgz == xxCLZaeSNV){rODYAGfSHP = true;}
      else if(xxCLZaeSNV == aeNojwuzgz){cYBmxsbNPZ = true;}
      if(jdUGTfyXyL == XhwdfjCnCn){rbEQlfVkwR = true;}
      else if(XhwdfjCnCn == jdUGTfyXyL){DAscayHIPE = true;}
      if(VazBHPBpXJ == ShJVNAJLeQ){AGyelySmdr = true;}
      else if(ShJVNAJLeQ == VazBHPBpXJ){qkNWEpNiya = true;}
      if(zNXpRsVkPG == EztyGpIqNt){lIcFoYgXCs = true;}
      else if(EztyGpIqNt == zNXpRsVkPG){eYJOgCnxiF = true;}
      if(ZVzCmDbpmj == gjKztfMZOb){SFYizbXbBx = true;}
      else if(gjKztfMZOb == ZVzCmDbpmj){ydxLAHPHXG = true;}
      if(nlKzUzeLhT == RGZNyPmfyZ){rLRPUkPXmC = true;}
      else if(RGZNyPmfyZ == nlKzUzeLhT){RHsAYqKdiG = true;}
      if(uFbWAVGena == QSnwQYmyWp){nsoPdiyyaN = true;}
      if(KMHqkzaxOE == aLaHGhWKah){zyiDzthOeK = true;}
      if(mKCmUMDXUS == mjwCzyYfzq){apkfzZqMkD = true;}
      while(QSnwQYmyWp == uFbWAVGena){fsOoudpduY = true;}
      while(aLaHGhWKah == aLaHGhWKah){JJZJGNnCWx = true;}
      while(mjwCzyYfzq == mjwCzyYfzq){aGKqIWeIpo = true;}
      if(DbsmdOwNhU == true){DbsmdOwNhU = false;}
      if(rODYAGfSHP == true){rODYAGfSHP = false;}
      if(rbEQlfVkwR == true){rbEQlfVkwR = false;}
      if(AGyelySmdr == true){AGyelySmdr = false;}
      if(lIcFoYgXCs == true){lIcFoYgXCs = false;}
      if(SFYizbXbBx == true){SFYizbXbBx = false;}
      if(rLRPUkPXmC == true){rLRPUkPXmC = false;}
      if(nsoPdiyyaN == true){nsoPdiyyaN = false;}
      if(zyiDzthOeK == true){zyiDzthOeK = false;}
      if(apkfzZqMkD == true){apkfzZqMkD = false;}
      if(IIjzFYPJEQ == true){IIjzFYPJEQ = false;}
      if(cYBmxsbNPZ == true){cYBmxsbNPZ = false;}
      if(DAscayHIPE == true){DAscayHIPE = false;}
      if(qkNWEpNiya == true){qkNWEpNiya = false;}
      if(eYJOgCnxiF == true){eYJOgCnxiF = false;}
      if(ydxLAHPHXG == true){ydxLAHPHXG = false;}
      if(RHsAYqKdiG == true){RHsAYqKdiG = false;}
      if(fsOoudpduY == true){fsOoudpduY = false;}
      if(JJZJGNnCWx == true){JJZJGNnCWx = false;}
      if(aGKqIWeIpo == true){aGKqIWeIpo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LIXLSLDWPN
{ 
  void AMSpRjMtQu()
  { 
      bool VYnnYADWAe = false;
      bool mTLCmWtYmh = false;
      bool PexwUDPieJ = false;
      bool YWQMDlfFOm = false;
      bool VZZIYeKKxs = false;
      bool SkQhUparSU = false;
      bool kUqqFPCyyA = false;
      bool pnJzMoEoXp = false;
      bool sFllpmFhrN = false;
      bool KnlsCAiiDI = false;
      bool bLLwCdbRVe = false;
      bool klTcbeiFAR = false;
      bool KTGkoCBQxL = false;
      bool GVkPNgsoiM = false;
      bool LnMMcYTJRW = false;
      bool RchkxHFaGA = false;
      bool bKTKYOBDOt = false;
      bool ltVnFVHsIQ = false;
      bool hryZtcnzRF = false;
      bool aRhhkATBnN = false;
      string dzTbdkRqqX;
      string bOhtNYIiby;
      string rVBMxAzfoX;
      string JEhzdeFKFn;
      string iZmIqBqRMm;
      string HSkJWIxHdd;
      string llCSNXfiPi;
      string TycnPShrUu;
      string JgSBQpSYbV;
      string gxfbCxWTtS;
      string UICdTJoxsD;
      string ZEmiTESACW;
      string FGGsBVRBkS;
      string wNyBZAeohH;
      string BVeXwbKxHy;
      string dWRWNOCIby;
      string qnLaHLGkIT;
      string ZcSuViahxY;
      string KUsmnZwamL;
      string yVNjPMJEQj;
      if(dzTbdkRqqX == UICdTJoxsD){VYnnYADWAe = true;}
      else if(UICdTJoxsD == dzTbdkRqqX){bLLwCdbRVe = true;}
      if(bOhtNYIiby == ZEmiTESACW){mTLCmWtYmh = true;}
      else if(ZEmiTESACW == bOhtNYIiby){klTcbeiFAR = true;}
      if(rVBMxAzfoX == FGGsBVRBkS){PexwUDPieJ = true;}
      else if(FGGsBVRBkS == rVBMxAzfoX){KTGkoCBQxL = true;}
      if(JEhzdeFKFn == wNyBZAeohH){YWQMDlfFOm = true;}
      else if(wNyBZAeohH == JEhzdeFKFn){GVkPNgsoiM = true;}
      if(iZmIqBqRMm == BVeXwbKxHy){VZZIYeKKxs = true;}
      else if(BVeXwbKxHy == iZmIqBqRMm){LnMMcYTJRW = true;}
      if(HSkJWIxHdd == dWRWNOCIby){SkQhUparSU = true;}
      else if(dWRWNOCIby == HSkJWIxHdd){RchkxHFaGA = true;}
      if(llCSNXfiPi == qnLaHLGkIT){kUqqFPCyyA = true;}
      else if(qnLaHLGkIT == llCSNXfiPi){bKTKYOBDOt = true;}
      if(TycnPShrUu == ZcSuViahxY){pnJzMoEoXp = true;}
      if(JgSBQpSYbV == KUsmnZwamL){sFllpmFhrN = true;}
      if(gxfbCxWTtS == yVNjPMJEQj){KnlsCAiiDI = true;}
      while(ZcSuViahxY == TycnPShrUu){ltVnFVHsIQ = true;}
      while(KUsmnZwamL == KUsmnZwamL){hryZtcnzRF = true;}
      while(yVNjPMJEQj == yVNjPMJEQj){aRhhkATBnN = true;}
      if(VYnnYADWAe == true){VYnnYADWAe = false;}
      if(mTLCmWtYmh == true){mTLCmWtYmh = false;}
      if(PexwUDPieJ == true){PexwUDPieJ = false;}
      if(YWQMDlfFOm == true){YWQMDlfFOm = false;}
      if(VZZIYeKKxs == true){VZZIYeKKxs = false;}
      if(SkQhUparSU == true){SkQhUparSU = false;}
      if(kUqqFPCyyA == true){kUqqFPCyyA = false;}
      if(pnJzMoEoXp == true){pnJzMoEoXp = false;}
      if(sFllpmFhrN == true){sFllpmFhrN = false;}
      if(KnlsCAiiDI == true){KnlsCAiiDI = false;}
      if(bLLwCdbRVe == true){bLLwCdbRVe = false;}
      if(klTcbeiFAR == true){klTcbeiFAR = false;}
      if(KTGkoCBQxL == true){KTGkoCBQxL = false;}
      if(GVkPNgsoiM == true){GVkPNgsoiM = false;}
      if(LnMMcYTJRW == true){LnMMcYTJRW = false;}
      if(RchkxHFaGA == true){RchkxHFaGA = false;}
      if(bKTKYOBDOt == true){bKTKYOBDOt = false;}
      if(ltVnFVHsIQ == true){ltVnFVHsIQ = false;}
      if(hryZtcnzRF == true){hryZtcnzRF = false;}
      if(aRhhkATBnN == true){aRhhkATBnN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VPCLLDUSJR
{ 
  void nqTAFqAwek()
  { 
      bool LxiJSMjafR = false;
      bool EkuWqNLPwL = false;
      bool XEtjYgBkPl = false;
      bool NlxLneFESl = false;
      bool sfSqMAerCp = false;
      bool RazOpGCzkk = false;
      bool KyLsDRmihL = false;
      bool IHwKSrlCWX = false;
      bool CJiZUmmhVg = false;
      bool bGThatTYnt = false;
      bool MuJpgKdowy = false;
      bool UAbMhBPlYP = false;
      bool dFNAiCmOiX = false;
      bool XMObLGzrrJ = false;
      bool JylWLbdHzZ = false;
      bool ehAYPHhIHd = false;
      bool WPGYZIlzBb = false;
      bool CXsOGfTpoG = false;
      bool XfPJsoMpLD = false;
      bool YqkNltrMxD = false;
      string JTowYyHRaK;
      string BeJZxXbezE;
      string GCKLWZOiQT;
      string cDoZgVMOXL;
      string AHdyPEgfMH;
      string mPzZeGJdYy;
      string jXBHgyoisa;
      string LNHmDyYLuS;
      string shWIfMDOuZ;
      string MioYbcGWQQ;
      string OxmkwZIMWf;
      string gxhFFBBraU;
      string uanSOcXhLa;
      string qCteEutkMG;
      string EqrPsOAjTZ;
      string bOuwVmJUWT;
      string CZAuneCDBK;
      string HPeTQEiXZA;
      string bnOkycGyIQ;
      string kZOsEdpwaN;
      if(JTowYyHRaK == OxmkwZIMWf){LxiJSMjafR = true;}
      else if(OxmkwZIMWf == JTowYyHRaK){MuJpgKdowy = true;}
      if(BeJZxXbezE == gxhFFBBraU){EkuWqNLPwL = true;}
      else if(gxhFFBBraU == BeJZxXbezE){UAbMhBPlYP = true;}
      if(GCKLWZOiQT == uanSOcXhLa){XEtjYgBkPl = true;}
      else if(uanSOcXhLa == GCKLWZOiQT){dFNAiCmOiX = true;}
      if(cDoZgVMOXL == qCteEutkMG){NlxLneFESl = true;}
      else if(qCteEutkMG == cDoZgVMOXL){XMObLGzrrJ = true;}
      if(AHdyPEgfMH == EqrPsOAjTZ){sfSqMAerCp = true;}
      else if(EqrPsOAjTZ == AHdyPEgfMH){JylWLbdHzZ = true;}
      if(mPzZeGJdYy == bOuwVmJUWT){RazOpGCzkk = true;}
      else if(bOuwVmJUWT == mPzZeGJdYy){ehAYPHhIHd = true;}
      if(jXBHgyoisa == CZAuneCDBK){KyLsDRmihL = true;}
      else if(CZAuneCDBK == jXBHgyoisa){WPGYZIlzBb = true;}
      if(LNHmDyYLuS == HPeTQEiXZA){IHwKSrlCWX = true;}
      if(shWIfMDOuZ == bnOkycGyIQ){CJiZUmmhVg = true;}
      if(MioYbcGWQQ == kZOsEdpwaN){bGThatTYnt = true;}
      while(HPeTQEiXZA == LNHmDyYLuS){CXsOGfTpoG = true;}
      while(bnOkycGyIQ == bnOkycGyIQ){XfPJsoMpLD = true;}
      while(kZOsEdpwaN == kZOsEdpwaN){YqkNltrMxD = true;}
      if(LxiJSMjafR == true){LxiJSMjafR = false;}
      if(EkuWqNLPwL == true){EkuWqNLPwL = false;}
      if(XEtjYgBkPl == true){XEtjYgBkPl = false;}
      if(NlxLneFESl == true){NlxLneFESl = false;}
      if(sfSqMAerCp == true){sfSqMAerCp = false;}
      if(RazOpGCzkk == true){RazOpGCzkk = false;}
      if(KyLsDRmihL == true){KyLsDRmihL = false;}
      if(IHwKSrlCWX == true){IHwKSrlCWX = false;}
      if(CJiZUmmhVg == true){CJiZUmmhVg = false;}
      if(bGThatTYnt == true){bGThatTYnt = false;}
      if(MuJpgKdowy == true){MuJpgKdowy = false;}
      if(UAbMhBPlYP == true){UAbMhBPlYP = false;}
      if(dFNAiCmOiX == true){dFNAiCmOiX = false;}
      if(XMObLGzrrJ == true){XMObLGzrrJ = false;}
      if(JylWLbdHzZ == true){JylWLbdHzZ = false;}
      if(ehAYPHhIHd == true){ehAYPHhIHd = false;}
      if(WPGYZIlzBb == true){WPGYZIlzBb = false;}
      if(CXsOGfTpoG == true){CXsOGfTpoG = false;}
      if(XfPJsoMpLD == true){XfPJsoMpLD = false;}
      if(YqkNltrMxD == true){YqkNltrMxD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UCFSMUJNOJ
{ 
  void MrYwVFGfRn()
  { 
      bool CYHdnZdLaZ = false;
      bool EzblKgNQii = false;
      bool rDuDWpTwra = false;
      bool caampeKuiT = false;
      bool NYMjhNquzy = false;
      bool utSTCzcEHy = false;
      bool FhTAxcYoue = false;
      bool VShPUSpKVJ = false;
      bool zYxsfhIGjq = false;
      bool BGmkNfFMmE = false;
      bool nBzTcbMCzj = false;
      bool IRiyygjaTP = false;
      bool UREEcOfwBn = false;
      bool MdXQUxYcPD = false;
      bool UFHAhjXolf = false;
      bool uerXiWwupN = false;
      bool wQBKWesRdB = false;
      bool IHKQtPJEVs = false;
      bool qpJVrhkAhx = false;
      bool AdmBHEEwdD = false;
      string xSzsROXHhe;
      string jZQxnOpYbD;
      string yslndKhZJh;
      string agoZXQVUwS;
      string pJlwIXenrp;
      string lDTMqDfLOG;
      string gyxzEDjqYX;
      string sVcINnGpeG;
      string fshTwWMchT;
      string jKFolrMmrF;
      string mnPTwPaLyD;
      string wpfIamPcDg;
      string pGJEnhPmWV;
      string bTyZSqdNWf;
      string wBdeWtexNy;
      string biiKOgdKfN;
      string zmocacqFoj;
      string JBFXjobehs;
      string DSYXsrkmKl;
      string MThJfJLBDt;
      if(xSzsROXHhe == mnPTwPaLyD){CYHdnZdLaZ = true;}
      else if(mnPTwPaLyD == xSzsROXHhe){nBzTcbMCzj = true;}
      if(jZQxnOpYbD == wpfIamPcDg){EzblKgNQii = true;}
      else if(wpfIamPcDg == jZQxnOpYbD){IRiyygjaTP = true;}
      if(yslndKhZJh == pGJEnhPmWV){rDuDWpTwra = true;}
      else if(pGJEnhPmWV == yslndKhZJh){UREEcOfwBn = true;}
      if(agoZXQVUwS == bTyZSqdNWf){caampeKuiT = true;}
      else if(bTyZSqdNWf == agoZXQVUwS){MdXQUxYcPD = true;}
      if(pJlwIXenrp == wBdeWtexNy){NYMjhNquzy = true;}
      else if(wBdeWtexNy == pJlwIXenrp){UFHAhjXolf = true;}
      if(lDTMqDfLOG == biiKOgdKfN){utSTCzcEHy = true;}
      else if(biiKOgdKfN == lDTMqDfLOG){uerXiWwupN = true;}
      if(gyxzEDjqYX == zmocacqFoj){FhTAxcYoue = true;}
      else if(zmocacqFoj == gyxzEDjqYX){wQBKWesRdB = true;}
      if(sVcINnGpeG == JBFXjobehs){VShPUSpKVJ = true;}
      if(fshTwWMchT == DSYXsrkmKl){zYxsfhIGjq = true;}
      if(jKFolrMmrF == MThJfJLBDt){BGmkNfFMmE = true;}
      while(JBFXjobehs == sVcINnGpeG){IHKQtPJEVs = true;}
      while(DSYXsrkmKl == DSYXsrkmKl){qpJVrhkAhx = true;}
      while(MThJfJLBDt == MThJfJLBDt){AdmBHEEwdD = true;}
      if(CYHdnZdLaZ == true){CYHdnZdLaZ = false;}
      if(EzblKgNQii == true){EzblKgNQii = false;}
      if(rDuDWpTwra == true){rDuDWpTwra = false;}
      if(caampeKuiT == true){caampeKuiT = false;}
      if(NYMjhNquzy == true){NYMjhNquzy = false;}
      if(utSTCzcEHy == true){utSTCzcEHy = false;}
      if(FhTAxcYoue == true){FhTAxcYoue = false;}
      if(VShPUSpKVJ == true){VShPUSpKVJ = false;}
      if(zYxsfhIGjq == true){zYxsfhIGjq = false;}
      if(BGmkNfFMmE == true){BGmkNfFMmE = false;}
      if(nBzTcbMCzj == true){nBzTcbMCzj = false;}
      if(IRiyygjaTP == true){IRiyygjaTP = false;}
      if(UREEcOfwBn == true){UREEcOfwBn = false;}
      if(MdXQUxYcPD == true){MdXQUxYcPD = false;}
      if(UFHAhjXolf == true){UFHAhjXolf = false;}
      if(uerXiWwupN == true){uerXiWwupN = false;}
      if(wQBKWesRdB == true){wQBKWesRdB = false;}
      if(IHKQtPJEVs == true){IHKQtPJEVs = false;}
      if(qpJVrhkAhx == true){qpJVrhkAhx = false;}
      if(AdmBHEEwdD == true){AdmBHEEwdD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GFWTRQOPBA
{ 
  void PReEfgfLIu()
  { 
      bool aRZCqVuMSz = false;
      bool aEpTbcQWyB = false;
      bool QWeLILZIHM = false;
      bool IGFOKemMna = false;
      bool LgWwypSxXa = false;
      bool QtGIlEmNse = false;
      bool ulEFpUzbJx = false;
      bool oEiWoiziNS = false;
      bool sckguNzwcF = false;
      bool rZSIeYcQFc = false;
      bool ppmZkMKjSC = false;
      bool EEzalSBXJb = false;
      bool VCzEEPlarQ = false;
      bool GicjbCoKui = false;
      bool CPdZAnZrVL = false;
      bool XFGcHnqiVV = false;
      bool ajqBwVaPyj = false;
      bool cqbaYGXZDQ = false;
      bool psEfsAcAcn = false;
      bool KGoZISXbce = false;
      string PMyiUzXuTh;
      string OUXhTtxCjh;
      string DpVQbkIHaE;
      string JECDOrTPHq;
      string sGsucRVEFn;
      string wuouRYphHi;
      string qQTOXJSTSa;
      string agtsnxwamJ;
      string PDBlIOPHlo;
      string ClIYAcleWS;
      string yBleNOAuGT;
      string bOtxSmOhGJ;
      string tLgdYnYUrL;
      string LRDTLORWYt;
      string NTASMmqLGM;
      string NEXNYlTHFY;
      string pfCuIKLZkD;
      string VqILuZLOQk;
      string wNOexHsouY;
      string uJRzDhRFJC;
      if(PMyiUzXuTh == yBleNOAuGT){aRZCqVuMSz = true;}
      else if(yBleNOAuGT == PMyiUzXuTh){ppmZkMKjSC = true;}
      if(OUXhTtxCjh == bOtxSmOhGJ){aEpTbcQWyB = true;}
      else if(bOtxSmOhGJ == OUXhTtxCjh){EEzalSBXJb = true;}
      if(DpVQbkIHaE == tLgdYnYUrL){QWeLILZIHM = true;}
      else if(tLgdYnYUrL == DpVQbkIHaE){VCzEEPlarQ = true;}
      if(JECDOrTPHq == LRDTLORWYt){IGFOKemMna = true;}
      else if(LRDTLORWYt == JECDOrTPHq){GicjbCoKui = true;}
      if(sGsucRVEFn == NTASMmqLGM){LgWwypSxXa = true;}
      else if(NTASMmqLGM == sGsucRVEFn){CPdZAnZrVL = true;}
      if(wuouRYphHi == NEXNYlTHFY){QtGIlEmNse = true;}
      else if(NEXNYlTHFY == wuouRYphHi){XFGcHnqiVV = true;}
      if(qQTOXJSTSa == pfCuIKLZkD){ulEFpUzbJx = true;}
      else if(pfCuIKLZkD == qQTOXJSTSa){ajqBwVaPyj = true;}
      if(agtsnxwamJ == VqILuZLOQk){oEiWoiziNS = true;}
      if(PDBlIOPHlo == wNOexHsouY){sckguNzwcF = true;}
      if(ClIYAcleWS == uJRzDhRFJC){rZSIeYcQFc = true;}
      while(VqILuZLOQk == agtsnxwamJ){cqbaYGXZDQ = true;}
      while(wNOexHsouY == wNOexHsouY){psEfsAcAcn = true;}
      while(uJRzDhRFJC == uJRzDhRFJC){KGoZISXbce = true;}
      if(aRZCqVuMSz == true){aRZCqVuMSz = false;}
      if(aEpTbcQWyB == true){aEpTbcQWyB = false;}
      if(QWeLILZIHM == true){QWeLILZIHM = false;}
      if(IGFOKemMna == true){IGFOKemMna = false;}
      if(LgWwypSxXa == true){LgWwypSxXa = false;}
      if(QtGIlEmNse == true){QtGIlEmNse = false;}
      if(ulEFpUzbJx == true){ulEFpUzbJx = false;}
      if(oEiWoiziNS == true){oEiWoiziNS = false;}
      if(sckguNzwcF == true){sckguNzwcF = false;}
      if(rZSIeYcQFc == true){rZSIeYcQFc = false;}
      if(ppmZkMKjSC == true){ppmZkMKjSC = false;}
      if(EEzalSBXJb == true){EEzalSBXJb = false;}
      if(VCzEEPlarQ == true){VCzEEPlarQ = false;}
      if(GicjbCoKui == true){GicjbCoKui = false;}
      if(CPdZAnZrVL == true){CPdZAnZrVL = false;}
      if(XFGcHnqiVV == true){XFGcHnqiVV = false;}
      if(ajqBwVaPyj == true){ajqBwVaPyj = false;}
      if(cqbaYGXZDQ == true){cqbaYGXZDQ = false;}
      if(psEfsAcAcn == true){psEfsAcAcn = false;}
      if(KGoZISXbce == true){KGoZISXbce = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWPPXEELFW
{ 
  void tIPQppdDkq()
  { 
      bool hYpMRPHmdn = false;
      bool kQAAbnXejy = false;
      bool WeyDrIgoiS = false;
      bool HYuFUzFxiR = false;
      bool KcTTSOyzYk = false;
      bool XuHVDDalTJ = false;
      bool iSDLfLVuec = false;
      bool hZwSmsKejc = false;
      bool JhQytLQZBR = false;
      bool YScYirYImG = false;
      bool sDTwCxzoiK = false;
      bool swBqzBBFRT = false;
      bool uusNEOwWjt = false;
      bool TBqdiGNUuw = false;
      bool MbqqXcRlYh = false;
      bool qTqSLyJFrn = false;
      bool AbFnpqEXHs = false;
      bool mgKUHTEBpa = false;
      bool xKyBDzKXRk = false;
      bool wIbHwkVCAg = false;
      string dPiFeVrnnH;
      string ICiyYQdXkD;
      string EARGBxgjlf;
      string FFSNqdtSEz;
      string ptXnPOCdNc;
      string qxrKsdybDg;
      string nHCIBDjUGt;
      string WLSkNKcdqm;
      string uCWIoINHTN;
      string fRPXLhrPlL;
      string egXSGfdGxi;
      string AUkQllksSs;
      string obArOFuuZe;
      string RNqeHNeDCJ;
      string dGKkMLfzkY;
      string xywsWCgfDB;
      string jhfRQmcGIY;
      string HgqIOhRPeD;
      string YwKAhSQyHE;
      string fzzBYwarTZ;
      if(dPiFeVrnnH == egXSGfdGxi){hYpMRPHmdn = true;}
      else if(egXSGfdGxi == dPiFeVrnnH){sDTwCxzoiK = true;}
      if(ICiyYQdXkD == AUkQllksSs){kQAAbnXejy = true;}
      else if(AUkQllksSs == ICiyYQdXkD){swBqzBBFRT = true;}
      if(EARGBxgjlf == obArOFuuZe){WeyDrIgoiS = true;}
      else if(obArOFuuZe == EARGBxgjlf){uusNEOwWjt = true;}
      if(FFSNqdtSEz == RNqeHNeDCJ){HYuFUzFxiR = true;}
      else if(RNqeHNeDCJ == FFSNqdtSEz){TBqdiGNUuw = true;}
      if(ptXnPOCdNc == dGKkMLfzkY){KcTTSOyzYk = true;}
      else if(dGKkMLfzkY == ptXnPOCdNc){MbqqXcRlYh = true;}
      if(qxrKsdybDg == xywsWCgfDB){XuHVDDalTJ = true;}
      else if(xywsWCgfDB == qxrKsdybDg){qTqSLyJFrn = true;}
      if(nHCIBDjUGt == jhfRQmcGIY){iSDLfLVuec = true;}
      else if(jhfRQmcGIY == nHCIBDjUGt){AbFnpqEXHs = true;}
      if(WLSkNKcdqm == HgqIOhRPeD){hZwSmsKejc = true;}
      if(uCWIoINHTN == YwKAhSQyHE){JhQytLQZBR = true;}
      if(fRPXLhrPlL == fzzBYwarTZ){YScYirYImG = true;}
      while(HgqIOhRPeD == WLSkNKcdqm){mgKUHTEBpa = true;}
      while(YwKAhSQyHE == YwKAhSQyHE){xKyBDzKXRk = true;}
      while(fzzBYwarTZ == fzzBYwarTZ){wIbHwkVCAg = true;}
      if(hYpMRPHmdn == true){hYpMRPHmdn = false;}
      if(kQAAbnXejy == true){kQAAbnXejy = false;}
      if(WeyDrIgoiS == true){WeyDrIgoiS = false;}
      if(HYuFUzFxiR == true){HYuFUzFxiR = false;}
      if(KcTTSOyzYk == true){KcTTSOyzYk = false;}
      if(XuHVDDalTJ == true){XuHVDDalTJ = false;}
      if(iSDLfLVuec == true){iSDLfLVuec = false;}
      if(hZwSmsKejc == true){hZwSmsKejc = false;}
      if(JhQytLQZBR == true){JhQytLQZBR = false;}
      if(YScYirYImG == true){YScYirYImG = false;}
      if(sDTwCxzoiK == true){sDTwCxzoiK = false;}
      if(swBqzBBFRT == true){swBqzBBFRT = false;}
      if(uusNEOwWjt == true){uusNEOwWjt = false;}
      if(TBqdiGNUuw == true){TBqdiGNUuw = false;}
      if(MbqqXcRlYh == true){MbqqXcRlYh = false;}
      if(qTqSLyJFrn == true){qTqSLyJFrn = false;}
      if(AbFnpqEXHs == true){AbFnpqEXHs = false;}
      if(mgKUHTEBpa == true){mgKUHTEBpa = false;}
      if(xKyBDzKXRk == true){xKyBDzKXRk = false;}
      if(wIbHwkVCAg == true){wIbHwkVCAg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FBIMCATFMD
{ 
  void MVBooFVFqU()
  { 
      bool ZhMtBOQmqc = false;
      bool XEcLWVieAT = false;
      bool yqGzJOxQAM = false;
      bool IfDQQcTNhU = false;
      bool hkwtqRaZgj = false;
      bool aViMihaNkl = false;
      bool RzmeTqBLut = false;
      bool CUwfkMuMHq = false;
      bool nWjPklxqhh = false;
      bool BGcwCiyRaA = false;
      bool QPelhFYDbV = false;
      bool mOFsyuPWsg = false;
      bool tJcMrwrAcB = false;
      bool OclHZXrxhf = false;
      bool MtPMumAjyH = false;
      bool SaXsGGlRtk = false;
      bool NYaZHJcySZ = false;
      bool CRoNTztQQE = false;
      bool uICUhmFrBS = false;
      bool kZDwSnSpEl = false;
      string oLCZOmXTWJ;
      string giRFDjrtwX;
      string UXiqdnfSUk;
      string GYIhKRLorZ;
      string WquqUAGXic;
      string OcpTfRbKuZ;
      string GEylDIZjul;
      string XCBWAcbrWc;
      string hIjqVdinBs;
      string pAtSSSrJnM;
      string ZWcxFMaSTD;
      string ojnRryUHPZ;
      string ZlhBwWIiEh;
      string jSDJDLellJ;
      string CPUyDFMbaU;
      string xksOlnnaBh;
      string DrOkSWfdOf;
      string ShUGWJQiyp;
      string KgIijzYnWO;
      string WEkEGKBjfg;
      if(oLCZOmXTWJ == ZWcxFMaSTD){ZhMtBOQmqc = true;}
      else if(ZWcxFMaSTD == oLCZOmXTWJ){QPelhFYDbV = true;}
      if(giRFDjrtwX == ojnRryUHPZ){XEcLWVieAT = true;}
      else if(ojnRryUHPZ == giRFDjrtwX){mOFsyuPWsg = true;}
      if(UXiqdnfSUk == ZlhBwWIiEh){yqGzJOxQAM = true;}
      else if(ZlhBwWIiEh == UXiqdnfSUk){tJcMrwrAcB = true;}
      if(GYIhKRLorZ == jSDJDLellJ){IfDQQcTNhU = true;}
      else if(jSDJDLellJ == GYIhKRLorZ){OclHZXrxhf = true;}
      if(WquqUAGXic == CPUyDFMbaU){hkwtqRaZgj = true;}
      else if(CPUyDFMbaU == WquqUAGXic){MtPMumAjyH = true;}
      if(OcpTfRbKuZ == xksOlnnaBh){aViMihaNkl = true;}
      else if(xksOlnnaBh == OcpTfRbKuZ){SaXsGGlRtk = true;}
      if(GEylDIZjul == DrOkSWfdOf){RzmeTqBLut = true;}
      else if(DrOkSWfdOf == GEylDIZjul){NYaZHJcySZ = true;}
      if(XCBWAcbrWc == ShUGWJQiyp){CUwfkMuMHq = true;}
      if(hIjqVdinBs == KgIijzYnWO){nWjPklxqhh = true;}
      if(pAtSSSrJnM == WEkEGKBjfg){BGcwCiyRaA = true;}
      while(ShUGWJQiyp == XCBWAcbrWc){CRoNTztQQE = true;}
      while(KgIijzYnWO == KgIijzYnWO){uICUhmFrBS = true;}
      while(WEkEGKBjfg == WEkEGKBjfg){kZDwSnSpEl = true;}
      if(ZhMtBOQmqc == true){ZhMtBOQmqc = false;}
      if(XEcLWVieAT == true){XEcLWVieAT = false;}
      if(yqGzJOxQAM == true){yqGzJOxQAM = false;}
      if(IfDQQcTNhU == true){IfDQQcTNhU = false;}
      if(hkwtqRaZgj == true){hkwtqRaZgj = false;}
      if(aViMihaNkl == true){aViMihaNkl = false;}
      if(RzmeTqBLut == true){RzmeTqBLut = false;}
      if(CUwfkMuMHq == true){CUwfkMuMHq = false;}
      if(nWjPklxqhh == true){nWjPklxqhh = false;}
      if(BGcwCiyRaA == true){BGcwCiyRaA = false;}
      if(QPelhFYDbV == true){QPelhFYDbV = false;}
      if(mOFsyuPWsg == true){mOFsyuPWsg = false;}
      if(tJcMrwrAcB == true){tJcMrwrAcB = false;}
      if(OclHZXrxhf == true){OclHZXrxhf = false;}
      if(MtPMumAjyH == true){MtPMumAjyH = false;}
      if(SaXsGGlRtk == true){SaXsGGlRtk = false;}
      if(NYaZHJcySZ == true){NYaZHJcySZ = false;}
      if(CRoNTztQQE == true){CRoNTztQQE = false;}
      if(uICUhmFrBS == true){uICUhmFrBS = false;}
      if(kZDwSnSpEl == true){kZDwSnSpEl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BVQKIADGYH
{ 
  void pnbOBkfFtD()
  { 
      bool heuXlNykwK = false;
      bool sGDuATGklB = false;
      bool HQcKgMdiky = false;
      bool ASkILkjBLy = false;
      bool UYVfkdMMJP = false;
      bool DUyQLQBjpZ = false;
      bool jPzyJZVtiO = false;
      bool jEZngitxYD = false;
      bool ARYVtfUTwu = false;
      bool iALlOFYXVL = false;
      bool IRdtfyuJic = false;
      bool WEKlYRqdDd = false;
      bool EBymejsnZb = false;
      bool JVaNuhmdou = false;
      bool jLkTYeoYMw = false;
      bool OuUqHGTpOw = false;
      bool FHiHSAcxqq = false;
      bool eMnHtsQeOA = false;
      bool tTadNOBiFn = false;
      bool OwOspcbcAY = false;
      string qMHERlTygl;
      string OjiJBNwbGP;
      string FjXLbJVlae;
      string ziDWaOXeKE;
      string SiKrqQNdnV;
      string gMyICGnwcI;
      string QhXBlfgLim;
      string pRRBxVYeTK;
      string uqyEylktUT;
      string abCCnjKJGL;
      string iBuBeOuwLf;
      string hIbRMYjSDA;
      string ulqOLOPPNM;
      string KPYHbtwxZi;
      string pninlRzkpP;
      string AqFFQwJfoP;
      string zfiyVRjUoR;
      string clsUJGDDct;
      string PeZxLTJSqe;
      string jPHKiKFjST;
      if(qMHERlTygl == iBuBeOuwLf){heuXlNykwK = true;}
      else if(iBuBeOuwLf == qMHERlTygl){IRdtfyuJic = true;}
      if(OjiJBNwbGP == hIbRMYjSDA){sGDuATGklB = true;}
      else if(hIbRMYjSDA == OjiJBNwbGP){WEKlYRqdDd = true;}
      if(FjXLbJVlae == ulqOLOPPNM){HQcKgMdiky = true;}
      else if(ulqOLOPPNM == FjXLbJVlae){EBymejsnZb = true;}
      if(ziDWaOXeKE == KPYHbtwxZi){ASkILkjBLy = true;}
      else if(KPYHbtwxZi == ziDWaOXeKE){JVaNuhmdou = true;}
      if(SiKrqQNdnV == pninlRzkpP){UYVfkdMMJP = true;}
      else if(pninlRzkpP == SiKrqQNdnV){jLkTYeoYMw = true;}
      if(gMyICGnwcI == AqFFQwJfoP){DUyQLQBjpZ = true;}
      else if(AqFFQwJfoP == gMyICGnwcI){OuUqHGTpOw = true;}
      if(QhXBlfgLim == zfiyVRjUoR){jPzyJZVtiO = true;}
      else if(zfiyVRjUoR == QhXBlfgLim){FHiHSAcxqq = true;}
      if(pRRBxVYeTK == clsUJGDDct){jEZngitxYD = true;}
      if(uqyEylktUT == PeZxLTJSqe){ARYVtfUTwu = true;}
      if(abCCnjKJGL == jPHKiKFjST){iALlOFYXVL = true;}
      while(clsUJGDDct == pRRBxVYeTK){eMnHtsQeOA = true;}
      while(PeZxLTJSqe == PeZxLTJSqe){tTadNOBiFn = true;}
      while(jPHKiKFjST == jPHKiKFjST){OwOspcbcAY = true;}
      if(heuXlNykwK == true){heuXlNykwK = false;}
      if(sGDuATGklB == true){sGDuATGklB = false;}
      if(HQcKgMdiky == true){HQcKgMdiky = false;}
      if(ASkILkjBLy == true){ASkILkjBLy = false;}
      if(UYVfkdMMJP == true){UYVfkdMMJP = false;}
      if(DUyQLQBjpZ == true){DUyQLQBjpZ = false;}
      if(jPzyJZVtiO == true){jPzyJZVtiO = false;}
      if(jEZngitxYD == true){jEZngitxYD = false;}
      if(ARYVtfUTwu == true){ARYVtfUTwu = false;}
      if(iALlOFYXVL == true){iALlOFYXVL = false;}
      if(IRdtfyuJic == true){IRdtfyuJic = false;}
      if(WEKlYRqdDd == true){WEKlYRqdDd = false;}
      if(EBymejsnZb == true){EBymejsnZb = false;}
      if(JVaNuhmdou == true){JVaNuhmdou = false;}
      if(jLkTYeoYMw == true){jLkTYeoYMw = false;}
      if(OuUqHGTpOw == true){OuUqHGTpOw = false;}
      if(FHiHSAcxqq == true){FHiHSAcxqq = false;}
      if(eMnHtsQeOA == true){eMnHtsQeOA = false;}
      if(tTadNOBiFn == true){tTadNOBiFn = false;}
      if(OwOspcbcAY == true){OwOspcbcAY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VCTGCJPIPY
{ 
  void rFWhyrQXGd()
  { 
      bool uWEGMieVDi = false;
      bool lCtXaQJalm = false;
      bool uTqVlOyOiL = false;
      bool puaQznurCo = false;
      bool oqusLISaBs = false;
      bool OTGcUafhTx = false;
      bool jPlqspbcYl = false;
      bool UQXwxDYxJc = false;
      bool wXNpxVoxwX = false;
      bool INXFFYFEzU = false;
      bool goBOYxuKeR = false;
      bool ChYpALCwsX = false;
      bool BdgAdHsRpX = false;
      bool yTyowHVyQA = false;
      bool adReVaogFt = false;
      bool WJKbTDHBkQ = false;
      bool EcUHShiitr = false;
      bool oDesxWLCeD = false;
      bool SLMwBnJVUr = false;
      bool zUNzwxJKLm = false;
      string qthqZDCFib;
      string gqLYoXgryD;
      string tpAcMFRuzt;
      string TfhdKNNsdp;
      string CeaLpYpwDy;
      string caBPKAtEeT;
      string kHFnIAIhOb;
      string KmOHAOPomm;
      string OUrBRreRSJ;
      string SIOKEuZlCp;
      string PIganoMsPw;
      string kFRqEPOEWP;
      string VpOFICXEDF;
      string oclxXGnQNb;
      string fkCWXNqXFn;
      string fUPmTZtaSk;
      string QIpKGHSTTy;
      string bxptjjmqgt;
      string KAzOYTMycx;
      string LMybKXtrPP;
      if(qthqZDCFib == PIganoMsPw){uWEGMieVDi = true;}
      else if(PIganoMsPw == qthqZDCFib){goBOYxuKeR = true;}
      if(gqLYoXgryD == kFRqEPOEWP){lCtXaQJalm = true;}
      else if(kFRqEPOEWP == gqLYoXgryD){ChYpALCwsX = true;}
      if(tpAcMFRuzt == VpOFICXEDF){uTqVlOyOiL = true;}
      else if(VpOFICXEDF == tpAcMFRuzt){BdgAdHsRpX = true;}
      if(TfhdKNNsdp == oclxXGnQNb){puaQznurCo = true;}
      else if(oclxXGnQNb == TfhdKNNsdp){yTyowHVyQA = true;}
      if(CeaLpYpwDy == fkCWXNqXFn){oqusLISaBs = true;}
      else if(fkCWXNqXFn == CeaLpYpwDy){adReVaogFt = true;}
      if(caBPKAtEeT == fUPmTZtaSk){OTGcUafhTx = true;}
      else if(fUPmTZtaSk == caBPKAtEeT){WJKbTDHBkQ = true;}
      if(kHFnIAIhOb == QIpKGHSTTy){jPlqspbcYl = true;}
      else if(QIpKGHSTTy == kHFnIAIhOb){EcUHShiitr = true;}
      if(KmOHAOPomm == bxptjjmqgt){UQXwxDYxJc = true;}
      if(OUrBRreRSJ == KAzOYTMycx){wXNpxVoxwX = true;}
      if(SIOKEuZlCp == LMybKXtrPP){INXFFYFEzU = true;}
      while(bxptjjmqgt == KmOHAOPomm){oDesxWLCeD = true;}
      while(KAzOYTMycx == KAzOYTMycx){SLMwBnJVUr = true;}
      while(LMybKXtrPP == LMybKXtrPP){zUNzwxJKLm = true;}
      if(uWEGMieVDi == true){uWEGMieVDi = false;}
      if(lCtXaQJalm == true){lCtXaQJalm = false;}
      if(uTqVlOyOiL == true){uTqVlOyOiL = false;}
      if(puaQznurCo == true){puaQznurCo = false;}
      if(oqusLISaBs == true){oqusLISaBs = false;}
      if(OTGcUafhTx == true){OTGcUafhTx = false;}
      if(jPlqspbcYl == true){jPlqspbcYl = false;}
      if(UQXwxDYxJc == true){UQXwxDYxJc = false;}
      if(wXNpxVoxwX == true){wXNpxVoxwX = false;}
      if(INXFFYFEzU == true){INXFFYFEzU = false;}
      if(goBOYxuKeR == true){goBOYxuKeR = false;}
      if(ChYpALCwsX == true){ChYpALCwsX = false;}
      if(BdgAdHsRpX == true){BdgAdHsRpX = false;}
      if(yTyowHVyQA == true){yTyowHVyQA = false;}
      if(adReVaogFt == true){adReVaogFt = false;}
      if(WJKbTDHBkQ == true){WJKbTDHBkQ = false;}
      if(EcUHShiitr == true){EcUHShiitr = false;}
      if(oDesxWLCeD == true){oDesxWLCeD = false;}
      if(SLMwBnJVUr == true){SLMwBnJVUr = false;}
      if(zUNzwxJKLm == true){zUNzwxJKLm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TXMRUENGMX
{ 
  void VnSnMyThHo()
  { 
      bool ChdbyYIAbX = false;
      bool JjjVUxwuAD = false;
      bool KosNcwoftm = false;
      bool HnWkNoDAgI = false;
      bool nZNVFFUYqn = false;
      bool KwBHtMnPzC = false;
      bool icGnPVMyIe = false;
      bool swOqOkbXIW = false;
      bool bQnFbKmPpB = false;
      bool BmBeZLSYFi = false;
      bool sWQLuOhJrJ = false;
      bool kQHcaRoBME = false;
      bool ixHGdGtiRD = false;
      bool SCRYdEzbKN = false;
      bool ccWgPkeYEH = false;
      bool WRMBAuOJhn = false;
      bool TyroqhyiyV = false;
      bool RMqzbFZZps = false;
      bool bVeJgBpQXh = false;
      bool pptVsdkhph = false;
      string JVTQqoKnGk;
      string tbLazNIVSg;
      string jjSCnqRZzf;
      string bxxGIbsZXF;
      string NnCHpCTaHH;
      string zuUquZCRcA;
      string XkoaIxeFRW;
      string UixNSwhLLl;
      string WpRqffbGKi;
      string YawXgbyazs;
      string XNJjlQyHXy;
      string rqFpcgSxub;
      string UXthxslYfp;
      string yGMROJfhFP;
      string hUhLqgVFuA;
      string JAfWXzSalr;
      string dZbgAkembS;
      string BkrftAoiqP;
      string XgcfgxZosO;
      string pEuMkHrBLF;
      if(JVTQqoKnGk == XNJjlQyHXy){ChdbyYIAbX = true;}
      else if(XNJjlQyHXy == JVTQqoKnGk){sWQLuOhJrJ = true;}
      if(tbLazNIVSg == rqFpcgSxub){JjjVUxwuAD = true;}
      else if(rqFpcgSxub == tbLazNIVSg){kQHcaRoBME = true;}
      if(jjSCnqRZzf == UXthxslYfp){KosNcwoftm = true;}
      else if(UXthxslYfp == jjSCnqRZzf){ixHGdGtiRD = true;}
      if(bxxGIbsZXF == yGMROJfhFP){HnWkNoDAgI = true;}
      else if(yGMROJfhFP == bxxGIbsZXF){SCRYdEzbKN = true;}
      if(NnCHpCTaHH == hUhLqgVFuA){nZNVFFUYqn = true;}
      else if(hUhLqgVFuA == NnCHpCTaHH){ccWgPkeYEH = true;}
      if(zuUquZCRcA == JAfWXzSalr){KwBHtMnPzC = true;}
      else if(JAfWXzSalr == zuUquZCRcA){WRMBAuOJhn = true;}
      if(XkoaIxeFRW == dZbgAkembS){icGnPVMyIe = true;}
      else if(dZbgAkembS == XkoaIxeFRW){TyroqhyiyV = true;}
      if(UixNSwhLLl == BkrftAoiqP){swOqOkbXIW = true;}
      if(WpRqffbGKi == XgcfgxZosO){bQnFbKmPpB = true;}
      if(YawXgbyazs == pEuMkHrBLF){BmBeZLSYFi = true;}
      while(BkrftAoiqP == UixNSwhLLl){RMqzbFZZps = true;}
      while(XgcfgxZosO == XgcfgxZosO){bVeJgBpQXh = true;}
      while(pEuMkHrBLF == pEuMkHrBLF){pptVsdkhph = true;}
      if(ChdbyYIAbX == true){ChdbyYIAbX = false;}
      if(JjjVUxwuAD == true){JjjVUxwuAD = false;}
      if(KosNcwoftm == true){KosNcwoftm = false;}
      if(HnWkNoDAgI == true){HnWkNoDAgI = false;}
      if(nZNVFFUYqn == true){nZNVFFUYqn = false;}
      if(KwBHtMnPzC == true){KwBHtMnPzC = false;}
      if(icGnPVMyIe == true){icGnPVMyIe = false;}
      if(swOqOkbXIW == true){swOqOkbXIW = false;}
      if(bQnFbKmPpB == true){bQnFbKmPpB = false;}
      if(BmBeZLSYFi == true){BmBeZLSYFi = false;}
      if(sWQLuOhJrJ == true){sWQLuOhJrJ = false;}
      if(kQHcaRoBME == true){kQHcaRoBME = false;}
      if(ixHGdGtiRD == true){ixHGdGtiRD = false;}
      if(SCRYdEzbKN == true){SCRYdEzbKN = false;}
      if(ccWgPkeYEH == true){ccWgPkeYEH = false;}
      if(WRMBAuOJhn == true){WRMBAuOJhn = false;}
      if(TyroqhyiyV == true){TyroqhyiyV = false;}
      if(RMqzbFZZps == true){RMqzbFZZps = false;}
      if(bVeJgBpQXh == true){bVeJgBpQXh = false;}
      if(pptVsdkhph == true){pptVsdkhph = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SJLZURMSJM
{ 
  void mymuNSNFUj()
  { 
      bool rpVXXEmhoT = false;
      bool BOfbDDJUhq = false;
      bool VmVmUiOiRo = false;
      bool DBLYXqONsX = false;
      bool TlCsOYWPIA = false;
      bool hEZUcEUiCn = false;
      bool oEQAPADGEL = false;
      bool oubJWjkcXw = false;
      bool MyZQGzapwS = false;
      bool VeKFiPUCcO = false;
      bool VPLwLlcQys = false;
      bool TrKGbpeAsQ = false;
      bool ZMKlpJkVaH = false;
      bool OhzJZwmcEU = false;
      bool WJqCydUDdr = false;
      bool kUJMnIFZGC = false;
      bool AGoqdlrBfe = false;
      bool DBwXtPVHmL = false;
      bool ogriVtYmUR = false;
      bool pMVBTPUAXM = false;
      string WCpyfmLgDR;
      string eHrmPdOdyD;
      string WNIACBSDCA;
      string yPKHPKGAtV;
      string LFVHClGqlO;
      string KxoqGItowd;
      string TIeDSPwjWF;
      string WNibqQrBxQ;
      string uaQmoAZSBH;
      string QQEPBDZSnm;
      string oVUfqxOMzo;
      string QrreirqqNS;
      string pdiPnGJSan;
      string pYMJbZGjwr;
      string lMTLqXYYgJ;
      string LhEUxLlErj;
      string mulKzqehDI;
      string kHuVfcJXYP;
      string gjlQcHUrMQ;
      string mCrLEqZIMz;
      if(WCpyfmLgDR == oVUfqxOMzo){rpVXXEmhoT = true;}
      else if(oVUfqxOMzo == WCpyfmLgDR){VPLwLlcQys = true;}
      if(eHrmPdOdyD == QrreirqqNS){BOfbDDJUhq = true;}
      else if(QrreirqqNS == eHrmPdOdyD){TrKGbpeAsQ = true;}
      if(WNIACBSDCA == pdiPnGJSan){VmVmUiOiRo = true;}
      else if(pdiPnGJSan == WNIACBSDCA){ZMKlpJkVaH = true;}
      if(yPKHPKGAtV == pYMJbZGjwr){DBLYXqONsX = true;}
      else if(pYMJbZGjwr == yPKHPKGAtV){OhzJZwmcEU = true;}
      if(LFVHClGqlO == lMTLqXYYgJ){TlCsOYWPIA = true;}
      else if(lMTLqXYYgJ == LFVHClGqlO){WJqCydUDdr = true;}
      if(KxoqGItowd == LhEUxLlErj){hEZUcEUiCn = true;}
      else if(LhEUxLlErj == KxoqGItowd){kUJMnIFZGC = true;}
      if(TIeDSPwjWF == mulKzqehDI){oEQAPADGEL = true;}
      else if(mulKzqehDI == TIeDSPwjWF){AGoqdlrBfe = true;}
      if(WNibqQrBxQ == kHuVfcJXYP){oubJWjkcXw = true;}
      if(uaQmoAZSBH == gjlQcHUrMQ){MyZQGzapwS = true;}
      if(QQEPBDZSnm == mCrLEqZIMz){VeKFiPUCcO = true;}
      while(kHuVfcJXYP == WNibqQrBxQ){DBwXtPVHmL = true;}
      while(gjlQcHUrMQ == gjlQcHUrMQ){ogriVtYmUR = true;}
      while(mCrLEqZIMz == mCrLEqZIMz){pMVBTPUAXM = true;}
      if(rpVXXEmhoT == true){rpVXXEmhoT = false;}
      if(BOfbDDJUhq == true){BOfbDDJUhq = false;}
      if(VmVmUiOiRo == true){VmVmUiOiRo = false;}
      if(DBLYXqONsX == true){DBLYXqONsX = false;}
      if(TlCsOYWPIA == true){TlCsOYWPIA = false;}
      if(hEZUcEUiCn == true){hEZUcEUiCn = false;}
      if(oEQAPADGEL == true){oEQAPADGEL = false;}
      if(oubJWjkcXw == true){oubJWjkcXw = false;}
      if(MyZQGzapwS == true){MyZQGzapwS = false;}
      if(VeKFiPUCcO == true){VeKFiPUCcO = false;}
      if(VPLwLlcQys == true){VPLwLlcQys = false;}
      if(TrKGbpeAsQ == true){TrKGbpeAsQ = false;}
      if(ZMKlpJkVaH == true){ZMKlpJkVaH = false;}
      if(OhzJZwmcEU == true){OhzJZwmcEU = false;}
      if(WJqCydUDdr == true){WJqCydUDdr = false;}
      if(kUJMnIFZGC == true){kUJMnIFZGC = false;}
      if(AGoqdlrBfe == true){AGoqdlrBfe = false;}
      if(DBwXtPVHmL == true){DBwXtPVHmL = false;}
      if(ogriVtYmUR == true){ogriVtYmUR = false;}
      if(pMVBTPUAXM == true){pMVBTPUAXM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MYMNQKRDND
{ 
  void EzjhAFByxM()
  { 
      bool ZHMsPgxbbi = false;
      bool sFtfySidQQ = false;
      bool yDbaeyHMnM = false;
      bool shLLEPQxOL = false;
      bool FdXFMReAml = false;
      bool LATghVekNQ = false;
      bool ZjnPpLtiai = false;
      bool BkPELTeWNN = false;
      bool TGZBBrOeci = false;
      bool jfixlUpIPB = false;
      bool XuZEkZkOUN = false;
      bool pIWAxSKlOy = false;
      bool wOFqyVBRRq = false;
      bool cWGLpXfUQb = false;
      bool GzKPraIiAT = false;
      bool KEtREIpiFO = false;
      bool XSwdkTBLKY = false;
      bool loUlqxEpyW = false;
      bool NSRyfYboGg = false;
      bool hxOCDmCgdY = false;
      string HrjszptubZ;
      string LsLpbmEiVI;
      string feJKAehERJ;
      string TiKBuAJmIe;
      string qfjQuHAJtt;
      string lmSpSbhZrU;
      string HpcSGchKua;
      string dRapQAtsOr;
      string dYKWWfQUiS;
      string SitmWBCRJS;
      string ZpNSPUMbZR;
      string hnLAqifGwZ;
      string LNabItXmSP;
      string ycjuSmKqHC;
      string TnuRkdXtwn;
      string VwViGLPkKV;
      string wYIKTEEPgD;
      string XnysGXSJqe;
      string WdpesCGAnG;
      string XYglFtejxf;
      if(HrjszptubZ == ZpNSPUMbZR){ZHMsPgxbbi = true;}
      else if(ZpNSPUMbZR == HrjszptubZ){XuZEkZkOUN = true;}
      if(LsLpbmEiVI == hnLAqifGwZ){sFtfySidQQ = true;}
      else if(hnLAqifGwZ == LsLpbmEiVI){pIWAxSKlOy = true;}
      if(feJKAehERJ == LNabItXmSP){yDbaeyHMnM = true;}
      else if(LNabItXmSP == feJKAehERJ){wOFqyVBRRq = true;}
      if(TiKBuAJmIe == ycjuSmKqHC){shLLEPQxOL = true;}
      else if(ycjuSmKqHC == TiKBuAJmIe){cWGLpXfUQb = true;}
      if(qfjQuHAJtt == TnuRkdXtwn){FdXFMReAml = true;}
      else if(TnuRkdXtwn == qfjQuHAJtt){GzKPraIiAT = true;}
      if(lmSpSbhZrU == VwViGLPkKV){LATghVekNQ = true;}
      else if(VwViGLPkKV == lmSpSbhZrU){KEtREIpiFO = true;}
      if(HpcSGchKua == wYIKTEEPgD){ZjnPpLtiai = true;}
      else if(wYIKTEEPgD == HpcSGchKua){XSwdkTBLKY = true;}
      if(dRapQAtsOr == XnysGXSJqe){BkPELTeWNN = true;}
      if(dYKWWfQUiS == WdpesCGAnG){TGZBBrOeci = true;}
      if(SitmWBCRJS == XYglFtejxf){jfixlUpIPB = true;}
      while(XnysGXSJqe == dRapQAtsOr){loUlqxEpyW = true;}
      while(WdpesCGAnG == WdpesCGAnG){NSRyfYboGg = true;}
      while(XYglFtejxf == XYglFtejxf){hxOCDmCgdY = true;}
      if(ZHMsPgxbbi == true){ZHMsPgxbbi = false;}
      if(sFtfySidQQ == true){sFtfySidQQ = false;}
      if(yDbaeyHMnM == true){yDbaeyHMnM = false;}
      if(shLLEPQxOL == true){shLLEPQxOL = false;}
      if(FdXFMReAml == true){FdXFMReAml = false;}
      if(LATghVekNQ == true){LATghVekNQ = false;}
      if(ZjnPpLtiai == true){ZjnPpLtiai = false;}
      if(BkPELTeWNN == true){BkPELTeWNN = false;}
      if(TGZBBrOeci == true){TGZBBrOeci = false;}
      if(jfixlUpIPB == true){jfixlUpIPB = false;}
      if(XuZEkZkOUN == true){XuZEkZkOUN = false;}
      if(pIWAxSKlOy == true){pIWAxSKlOy = false;}
      if(wOFqyVBRRq == true){wOFqyVBRRq = false;}
      if(cWGLpXfUQb == true){cWGLpXfUQb = false;}
      if(GzKPraIiAT == true){GzKPraIiAT = false;}
      if(KEtREIpiFO == true){KEtREIpiFO = false;}
      if(XSwdkTBLKY == true){XSwdkTBLKY = false;}
      if(loUlqxEpyW == true){loUlqxEpyW = false;}
      if(NSRyfYboGg == true){NSRyfYboGg = false;}
      if(hxOCDmCgdY == true){hxOCDmCgdY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QCLFENAMDX
{ 
  void CCqFSMpCFr()
  { 
      bool QLAnxkIalu = false;
      bool QSgerLVWHP = false;
      bool KDGzjlAfYN = false;
      bool CLoPBCtwCD = false;
      bool WFYeKMirLw = false;
      bool keiJWMFADL = false;
      bool jbBYsEcQcp = false;
      bool QYTDsFeboX = false;
      bool CITbbWbfsn = false;
      bool xssqStDAlF = false;
      bool iSOVeLLfQQ = false;
      bool hdLeIbIYwV = false;
      bool cxWnrXfbjy = false;
      bool BdpiojtxwQ = false;
      bool LuOcGThNiq = false;
      bool kdEPckwZdH = false;
      bool eiuRPEmcpX = false;
      bool hKceJgithY = false;
      bool oSssMWZZFD = false;
      bool mTTnlcAwNC = false;
      string JnGCaNiSed;
      string tssBTInLoH;
      string dlxBeTVZtp;
      string gUXWbGDUnp;
      string JOsmBcoaJT;
      string xUXqiXqFWH;
      string rIXowZVWZN;
      string ETWzyPrJAB;
      string euQarMxfnD;
      string OxxgyApEqa;
      string HRAwOcxYsT;
      string ehFUcxrxwj;
      string boiVyHWoBx;
      string YnSYtMtULO;
      string OYmTYfrbEA;
      string IsHGyShdxH;
      string GHWwtqPfaP;
      string CXkgUDCOxS;
      string OukAnefLZa;
      string ePWEIHBqZg;
      if(JnGCaNiSed == HRAwOcxYsT){QLAnxkIalu = true;}
      else if(HRAwOcxYsT == JnGCaNiSed){iSOVeLLfQQ = true;}
      if(tssBTInLoH == ehFUcxrxwj){QSgerLVWHP = true;}
      else if(ehFUcxrxwj == tssBTInLoH){hdLeIbIYwV = true;}
      if(dlxBeTVZtp == boiVyHWoBx){KDGzjlAfYN = true;}
      else if(boiVyHWoBx == dlxBeTVZtp){cxWnrXfbjy = true;}
      if(gUXWbGDUnp == YnSYtMtULO){CLoPBCtwCD = true;}
      else if(YnSYtMtULO == gUXWbGDUnp){BdpiojtxwQ = true;}
      if(JOsmBcoaJT == OYmTYfrbEA){WFYeKMirLw = true;}
      else if(OYmTYfrbEA == JOsmBcoaJT){LuOcGThNiq = true;}
      if(xUXqiXqFWH == IsHGyShdxH){keiJWMFADL = true;}
      else if(IsHGyShdxH == xUXqiXqFWH){kdEPckwZdH = true;}
      if(rIXowZVWZN == GHWwtqPfaP){jbBYsEcQcp = true;}
      else if(GHWwtqPfaP == rIXowZVWZN){eiuRPEmcpX = true;}
      if(ETWzyPrJAB == CXkgUDCOxS){QYTDsFeboX = true;}
      if(euQarMxfnD == OukAnefLZa){CITbbWbfsn = true;}
      if(OxxgyApEqa == ePWEIHBqZg){xssqStDAlF = true;}
      while(CXkgUDCOxS == ETWzyPrJAB){hKceJgithY = true;}
      while(OukAnefLZa == OukAnefLZa){oSssMWZZFD = true;}
      while(ePWEIHBqZg == ePWEIHBqZg){mTTnlcAwNC = true;}
      if(QLAnxkIalu == true){QLAnxkIalu = false;}
      if(QSgerLVWHP == true){QSgerLVWHP = false;}
      if(KDGzjlAfYN == true){KDGzjlAfYN = false;}
      if(CLoPBCtwCD == true){CLoPBCtwCD = false;}
      if(WFYeKMirLw == true){WFYeKMirLw = false;}
      if(keiJWMFADL == true){keiJWMFADL = false;}
      if(jbBYsEcQcp == true){jbBYsEcQcp = false;}
      if(QYTDsFeboX == true){QYTDsFeboX = false;}
      if(CITbbWbfsn == true){CITbbWbfsn = false;}
      if(xssqStDAlF == true){xssqStDAlF = false;}
      if(iSOVeLLfQQ == true){iSOVeLLfQQ = false;}
      if(hdLeIbIYwV == true){hdLeIbIYwV = false;}
      if(cxWnrXfbjy == true){cxWnrXfbjy = false;}
      if(BdpiojtxwQ == true){BdpiojtxwQ = false;}
      if(LuOcGThNiq == true){LuOcGThNiq = false;}
      if(kdEPckwZdH == true){kdEPckwZdH = false;}
      if(eiuRPEmcpX == true){eiuRPEmcpX = false;}
      if(hKceJgithY == true){hKceJgithY = false;}
      if(oSssMWZZFD == true){oSssMWZZFD = false;}
      if(mTTnlcAwNC == true){mTTnlcAwNC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VCLPDJRXJV
{ 
  void afOgWmlWOY()
  { 
      bool QiDjuuPGEb = false;
      bool snqWxqmwjS = false;
      bool nDUlaKFurP = false;
      bool NQbiGXQRmx = false;
      bool RkiQlcKYmQ = false;
      bool jnYlBNORIj = false;
      bool pUNnOcMIPY = false;
      bool ZVIlADTEzy = false;
      bool zfHafZqpgs = false;
      bool JzJCGxXtCJ = false;
      bool PBJNqNflky = false;
      bool sKRKkKMlIn = false;
      bool kWbWPaMFfD = false;
      bool eZBohxVtjR = false;
      bool tEEhzzgyRw = false;
      bool kklNYsZlyQ = false;
      bool BZGhSTIccm = false;
      bool nSCptgStXQ = false;
      bool sNnjStmnQo = false;
      bool XiuTQTyWOe = false;
      string BojahBJLnT;
      string eZPIhEKRZc;
      string ctutdKqBry;
      string mgGAJXUhex;
      string xjRYlzTLjs;
      string cGxzTHspwW;
      string KITpgxTPyK;
      string ibmberbWIe;
      string qeQyUfjGfC;
      string delIloPbrn;
      string fEMZJBTUTb;
      string fVhQeeqUUA;
      string NMjwfEpdpp;
      string bzeTzlSpoT;
      string MOmDWHxUcH;
      string xuHqaSUQtE;
      string LoeczfqNRs;
      string MBfBmyZfYX;
      string HUBhsgqmsf;
      string RCwjIXjJEp;
      if(BojahBJLnT == fEMZJBTUTb){QiDjuuPGEb = true;}
      else if(fEMZJBTUTb == BojahBJLnT){PBJNqNflky = true;}
      if(eZPIhEKRZc == fVhQeeqUUA){snqWxqmwjS = true;}
      else if(fVhQeeqUUA == eZPIhEKRZc){sKRKkKMlIn = true;}
      if(ctutdKqBry == NMjwfEpdpp){nDUlaKFurP = true;}
      else if(NMjwfEpdpp == ctutdKqBry){kWbWPaMFfD = true;}
      if(mgGAJXUhex == bzeTzlSpoT){NQbiGXQRmx = true;}
      else if(bzeTzlSpoT == mgGAJXUhex){eZBohxVtjR = true;}
      if(xjRYlzTLjs == MOmDWHxUcH){RkiQlcKYmQ = true;}
      else if(MOmDWHxUcH == xjRYlzTLjs){tEEhzzgyRw = true;}
      if(cGxzTHspwW == xuHqaSUQtE){jnYlBNORIj = true;}
      else if(xuHqaSUQtE == cGxzTHspwW){kklNYsZlyQ = true;}
      if(KITpgxTPyK == LoeczfqNRs){pUNnOcMIPY = true;}
      else if(LoeczfqNRs == KITpgxTPyK){BZGhSTIccm = true;}
      if(ibmberbWIe == MBfBmyZfYX){ZVIlADTEzy = true;}
      if(qeQyUfjGfC == HUBhsgqmsf){zfHafZqpgs = true;}
      if(delIloPbrn == RCwjIXjJEp){JzJCGxXtCJ = true;}
      while(MBfBmyZfYX == ibmberbWIe){nSCptgStXQ = true;}
      while(HUBhsgqmsf == HUBhsgqmsf){sNnjStmnQo = true;}
      while(RCwjIXjJEp == RCwjIXjJEp){XiuTQTyWOe = true;}
      if(QiDjuuPGEb == true){QiDjuuPGEb = false;}
      if(snqWxqmwjS == true){snqWxqmwjS = false;}
      if(nDUlaKFurP == true){nDUlaKFurP = false;}
      if(NQbiGXQRmx == true){NQbiGXQRmx = false;}
      if(RkiQlcKYmQ == true){RkiQlcKYmQ = false;}
      if(jnYlBNORIj == true){jnYlBNORIj = false;}
      if(pUNnOcMIPY == true){pUNnOcMIPY = false;}
      if(ZVIlADTEzy == true){ZVIlADTEzy = false;}
      if(zfHafZqpgs == true){zfHafZqpgs = false;}
      if(JzJCGxXtCJ == true){JzJCGxXtCJ = false;}
      if(PBJNqNflky == true){PBJNqNflky = false;}
      if(sKRKkKMlIn == true){sKRKkKMlIn = false;}
      if(kWbWPaMFfD == true){kWbWPaMFfD = false;}
      if(eZBohxVtjR == true){eZBohxVtjR = false;}
      if(tEEhzzgyRw == true){tEEhzzgyRw = false;}
      if(kklNYsZlyQ == true){kklNYsZlyQ = false;}
      if(BZGhSTIccm == true){BZGhSTIccm = false;}
      if(nSCptgStXQ == true){nSCptgStXQ = false;}
      if(sNnjStmnQo == true){sNnjStmnQo = false;}
      if(XiuTQTyWOe == true){XiuTQTyWOe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class USAEOOHDUY
{ 
  void LIIarzRdwd()
  { 
      bool nEthauqIPB = false;
      bool NAxeWqrJko = false;
      bool BMuKcOgLyj = false;
      bool tcCmeidtCY = false;
      bool fhaoOnPnVl = false;
      bool ueCMOaJjFM = false;
      bool NeKeHjyKAn = false;
      bool NyGMISlFwn = false;
      bool zspMoPaoXD = false;
      bool ZtnpKAXuhd = false;
      bool pEmhYwXoDu = false;
      bool nDmRMToypr = false;
      bool JIlxNSJQBI = false;
      bool upXSxtFImr = false;
      bool qklcOVGVcp = false;
      bool KZFoUhSpTF = false;
      bool lGntzxfUUS = false;
      bool OgKxAXVJhr = false;
      bool MmnKxVkhxP = false;
      bool bPnhFkxqcR = false;
      string ciBpguOfIi;
      string riSVoZAilq;
      string rZDRBCdTYW;
      string woOEfEoQrK;
      string KOrGxHkCsc;
      string GotBJCeine;
      string RtGkmDUNoj;
      string kiqagchxUt;
      string RaawPGtMuc;
      string ZFcNsPHGTs;
      string mWMIqWyTUg;
      string UhNtMpTKUf;
      string JIRLKfGcgQ;
      string UbdbGtNREs;
      string IaqNIrqhAD;
      string wxkmjdEAyL;
      string PUlEMrDlmR;
      string bBFbXhQEDS;
      string nYccTXqpqb;
      string oNTscmnmBP;
      if(ciBpguOfIi == mWMIqWyTUg){nEthauqIPB = true;}
      else if(mWMIqWyTUg == ciBpguOfIi){pEmhYwXoDu = true;}
      if(riSVoZAilq == UhNtMpTKUf){NAxeWqrJko = true;}
      else if(UhNtMpTKUf == riSVoZAilq){nDmRMToypr = true;}
      if(rZDRBCdTYW == JIRLKfGcgQ){BMuKcOgLyj = true;}
      else if(JIRLKfGcgQ == rZDRBCdTYW){JIlxNSJQBI = true;}
      if(woOEfEoQrK == UbdbGtNREs){tcCmeidtCY = true;}
      else if(UbdbGtNREs == woOEfEoQrK){upXSxtFImr = true;}
      if(KOrGxHkCsc == IaqNIrqhAD){fhaoOnPnVl = true;}
      else if(IaqNIrqhAD == KOrGxHkCsc){qklcOVGVcp = true;}
      if(GotBJCeine == wxkmjdEAyL){ueCMOaJjFM = true;}
      else if(wxkmjdEAyL == GotBJCeine){KZFoUhSpTF = true;}
      if(RtGkmDUNoj == PUlEMrDlmR){NeKeHjyKAn = true;}
      else if(PUlEMrDlmR == RtGkmDUNoj){lGntzxfUUS = true;}
      if(kiqagchxUt == bBFbXhQEDS){NyGMISlFwn = true;}
      if(RaawPGtMuc == nYccTXqpqb){zspMoPaoXD = true;}
      if(ZFcNsPHGTs == oNTscmnmBP){ZtnpKAXuhd = true;}
      while(bBFbXhQEDS == kiqagchxUt){OgKxAXVJhr = true;}
      while(nYccTXqpqb == nYccTXqpqb){MmnKxVkhxP = true;}
      while(oNTscmnmBP == oNTscmnmBP){bPnhFkxqcR = true;}
      if(nEthauqIPB == true){nEthauqIPB = false;}
      if(NAxeWqrJko == true){NAxeWqrJko = false;}
      if(BMuKcOgLyj == true){BMuKcOgLyj = false;}
      if(tcCmeidtCY == true){tcCmeidtCY = false;}
      if(fhaoOnPnVl == true){fhaoOnPnVl = false;}
      if(ueCMOaJjFM == true){ueCMOaJjFM = false;}
      if(NeKeHjyKAn == true){NeKeHjyKAn = false;}
      if(NyGMISlFwn == true){NyGMISlFwn = false;}
      if(zspMoPaoXD == true){zspMoPaoXD = false;}
      if(ZtnpKAXuhd == true){ZtnpKAXuhd = false;}
      if(pEmhYwXoDu == true){pEmhYwXoDu = false;}
      if(nDmRMToypr == true){nDmRMToypr = false;}
      if(JIlxNSJQBI == true){JIlxNSJQBI = false;}
      if(upXSxtFImr == true){upXSxtFImr = false;}
      if(qklcOVGVcp == true){qklcOVGVcp = false;}
      if(KZFoUhSpTF == true){KZFoUhSpTF = false;}
      if(lGntzxfUUS == true){lGntzxfUUS = false;}
      if(OgKxAXVJhr == true){OgKxAXVJhr = false;}
      if(MmnKxVkhxP == true){MmnKxVkhxP = false;}
      if(bPnhFkxqcR == true){bPnhFkxqcR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UEWWKENAFA
{ 
  void mhmzucDUTL()
  { 
      bool wVSVyhFMMC = false;
      bool zoCjwMxguy = false;
      bool DNgDNYHNMm = false;
      bool cZsYBHDwIs = false;
      bool edaEIQzZfZ = false;
      bool eUPWGhoPIY = false;
      bool arzYYZwdho = false;
      bool IBYBSYmctx = false;
      bool ZghmIIKWRT = false;
      bool RnmjSmeCei = false;
      bool TUqpRcwNDg = false;
      bool tMVLysKMQQ = false;
      bool PZLOXUNnif = false;
      bool tjxKcFpqVe = false;
      bool MwSkYESbkY = false;
      bool cSlOStJcSx = false;
      bool PHeWmKOKis = false;
      bool DSqkESGaoS = false;
      bool BlDJDbyiqh = false;
      bool wNYYPERwxO = false;
      string onEsiulMIl;
      string qFjdzfVsgR;
      string SCRiseWJDd;
      string LFJBomGjUL;
      string jxONpyCMol;
      string VuqeilWUAE;
      string XcJeZkwioM;
      string YkXUhUnDsu;
      string bKUQHQNdRC;
      string QkjQmHnjmE;
      string BTXcNkWWxO;
      string ySbFbNIrWJ;
      string WRQlumBHga;
      string fDQnsImqCW;
      string sqgDDyJeoZ;
      string zuMchjCkgZ;
      string iPoWhtBmLS;
      string aQpAQejNhx;
      string dWRHbjqmGI;
      string FBJbmcCKUJ;
      if(onEsiulMIl == BTXcNkWWxO){wVSVyhFMMC = true;}
      else if(BTXcNkWWxO == onEsiulMIl){TUqpRcwNDg = true;}
      if(qFjdzfVsgR == ySbFbNIrWJ){zoCjwMxguy = true;}
      else if(ySbFbNIrWJ == qFjdzfVsgR){tMVLysKMQQ = true;}
      if(SCRiseWJDd == WRQlumBHga){DNgDNYHNMm = true;}
      else if(WRQlumBHga == SCRiseWJDd){PZLOXUNnif = true;}
      if(LFJBomGjUL == fDQnsImqCW){cZsYBHDwIs = true;}
      else if(fDQnsImqCW == LFJBomGjUL){tjxKcFpqVe = true;}
      if(jxONpyCMol == sqgDDyJeoZ){edaEIQzZfZ = true;}
      else if(sqgDDyJeoZ == jxONpyCMol){MwSkYESbkY = true;}
      if(VuqeilWUAE == zuMchjCkgZ){eUPWGhoPIY = true;}
      else if(zuMchjCkgZ == VuqeilWUAE){cSlOStJcSx = true;}
      if(XcJeZkwioM == iPoWhtBmLS){arzYYZwdho = true;}
      else if(iPoWhtBmLS == XcJeZkwioM){PHeWmKOKis = true;}
      if(YkXUhUnDsu == aQpAQejNhx){IBYBSYmctx = true;}
      if(bKUQHQNdRC == dWRHbjqmGI){ZghmIIKWRT = true;}
      if(QkjQmHnjmE == FBJbmcCKUJ){RnmjSmeCei = true;}
      while(aQpAQejNhx == YkXUhUnDsu){DSqkESGaoS = true;}
      while(dWRHbjqmGI == dWRHbjqmGI){BlDJDbyiqh = true;}
      while(FBJbmcCKUJ == FBJbmcCKUJ){wNYYPERwxO = true;}
      if(wVSVyhFMMC == true){wVSVyhFMMC = false;}
      if(zoCjwMxguy == true){zoCjwMxguy = false;}
      if(DNgDNYHNMm == true){DNgDNYHNMm = false;}
      if(cZsYBHDwIs == true){cZsYBHDwIs = false;}
      if(edaEIQzZfZ == true){edaEIQzZfZ = false;}
      if(eUPWGhoPIY == true){eUPWGhoPIY = false;}
      if(arzYYZwdho == true){arzYYZwdho = false;}
      if(IBYBSYmctx == true){IBYBSYmctx = false;}
      if(ZghmIIKWRT == true){ZghmIIKWRT = false;}
      if(RnmjSmeCei == true){RnmjSmeCei = false;}
      if(TUqpRcwNDg == true){TUqpRcwNDg = false;}
      if(tMVLysKMQQ == true){tMVLysKMQQ = false;}
      if(PZLOXUNnif == true){PZLOXUNnif = false;}
      if(tjxKcFpqVe == true){tjxKcFpqVe = false;}
      if(MwSkYESbkY == true){MwSkYESbkY = false;}
      if(cSlOStJcSx == true){cSlOStJcSx = false;}
      if(PHeWmKOKis == true){PHeWmKOKis = false;}
      if(DSqkESGaoS == true){DSqkESGaoS = false;}
      if(BlDJDbyiqh == true){BlDJDbyiqh = false;}
      if(wNYYPERwxO == true){wNYYPERwxO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YNAIAZZYIJ
{ 
  void VkrSitzMjK()
  { 
      bool FYWOjdshhj = false;
      bool sezlXzDuAY = false;
      bool aAYPPougPF = false;
      bool VioNOnPFGK = false;
      bool FKGTsLBqzy = false;
      bool LqincEAGyu = false;
      bool hMRbNKplWj = false;
      bool jxopSQtEWD = false;
      bool mDgRtezAjJ = false;
      bool nIHLbsseFi = false;
      bool VPTPNNCsVL = false;
      bool KujtIefzgh = false;
      bool LoBNubpcOZ = false;
      bool XOzmhWiQEg = false;
      bool cGeXzsXMDw = false;
      bool NsxWWfOGUl = false;
      bool XYdunwwwMk = false;
      bool uOuAFFKcOC = false;
      bool DcZRLdQbQB = false;
      bool IcwRJEbiiC = false;
      string uKPXoopXET;
      string yqppGQfTWi;
      string xGZPNOEXzX;
      string IkqrUNaobU;
      string elZVpGTcPo;
      string oGGkinkzKZ;
      string jRXfKNzyVs;
      string oprBELgDZG;
      string taHJhCdGJf;
      string cadBjMNsLb;
      string GVHWAyOEfW;
      string HgZDfJJOxI;
      string isopPOMpRq;
      string ynqxAXSkJj;
      string mZZlXuBZVa;
      string CyuCsMgRGk;
      string lXmoYTobDH;
      string pYENUJTCRU;
      string MlUqnzroDm;
      string qBdXxOmjNE;
      if(uKPXoopXET == GVHWAyOEfW){FYWOjdshhj = true;}
      else if(GVHWAyOEfW == uKPXoopXET){VPTPNNCsVL = true;}
      if(yqppGQfTWi == HgZDfJJOxI){sezlXzDuAY = true;}
      else if(HgZDfJJOxI == yqppGQfTWi){KujtIefzgh = true;}
      if(xGZPNOEXzX == isopPOMpRq){aAYPPougPF = true;}
      else if(isopPOMpRq == xGZPNOEXzX){LoBNubpcOZ = true;}
      if(IkqrUNaobU == ynqxAXSkJj){VioNOnPFGK = true;}
      else if(ynqxAXSkJj == IkqrUNaobU){XOzmhWiQEg = true;}
      if(elZVpGTcPo == mZZlXuBZVa){FKGTsLBqzy = true;}
      else if(mZZlXuBZVa == elZVpGTcPo){cGeXzsXMDw = true;}
      if(oGGkinkzKZ == CyuCsMgRGk){LqincEAGyu = true;}
      else if(CyuCsMgRGk == oGGkinkzKZ){NsxWWfOGUl = true;}
      if(jRXfKNzyVs == lXmoYTobDH){hMRbNKplWj = true;}
      else if(lXmoYTobDH == jRXfKNzyVs){XYdunwwwMk = true;}
      if(oprBELgDZG == pYENUJTCRU){jxopSQtEWD = true;}
      if(taHJhCdGJf == MlUqnzroDm){mDgRtezAjJ = true;}
      if(cadBjMNsLb == qBdXxOmjNE){nIHLbsseFi = true;}
      while(pYENUJTCRU == oprBELgDZG){uOuAFFKcOC = true;}
      while(MlUqnzroDm == MlUqnzroDm){DcZRLdQbQB = true;}
      while(qBdXxOmjNE == qBdXxOmjNE){IcwRJEbiiC = true;}
      if(FYWOjdshhj == true){FYWOjdshhj = false;}
      if(sezlXzDuAY == true){sezlXzDuAY = false;}
      if(aAYPPougPF == true){aAYPPougPF = false;}
      if(VioNOnPFGK == true){VioNOnPFGK = false;}
      if(FKGTsLBqzy == true){FKGTsLBqzy = false;}
      if(LqincEAGyu == true){LqincEAGyu = false;}
      if(hMRbNKplWj == true){hMRbNKplWj = false;}
      if(jxopSQtEWD == true){jxopSQtEWD = false;}
      if(mDgRtezAjJ == true){mDgRtezAjJ = false;}
      if(nIHLbsseFi == true){nIHLbsseFi = false;}
      if(VPTPNNCsVL == true){VPTPNNCsVL = false;}
      if(KujtIefzgh == true){KujtIefzgh = false;}
      if(LoBNubpcOZ == true){LoBNubpcOZ = false;}
      if(XOzmhWiQEg == true){XOzmhWiQEg = false;}
      if(cGeXzsXMDw == true){cGeXzsXMDw = false;}
      if(NsxWWfOGUl == true){NsxWWfOGUl = false;}
      if(XYdunwwwMk == true){XYdunwwwMk = false;}
      if(uOuAFFKcOC == true){uOuAFFKcOC = false;}
      if(DcZRLdQbQB == true){DcZRLdQbQB = false;}
      if(IcwRJEbiiC == true){IcwRJEbiiC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NYJBCXMVVD
{ 
  void gfRTeeDbIT()
  { 
      bool aBYxJaXIIw = false;
      bool DFXkPUIfjU = false;
      bool GTLBDQxVFY = false;
      bool VGhZVaOoCB = false;
      bool WEowZSQqGX = false;
      bool JFgcrGpXts = false;
      bool cCDiZxXyOn = false;
      bool GTdixBeOak = false;
      bool zFPgOQYEhP = false;
      bool kpuJXUBGVc = false;
      bool uScRQpbyfp = false;
      bool bbwJsXlVTJ = false;
      bool XSPzDPYTKc = false;
      bool AXsyogcyQY = false;
      bool oZYrmJtkPA = false;
      bool ielMEbDdNA = false;
      bool RHmCoDhxTM = false;
      bool umFuUxtXLt = false;
      bool VmDKtVlgsN = false;
      bool cyjQGgmVCj = false;
      string yBOAecbIgb;
      string oqiQcuhMIR;
      string EihUhDKIKe;
      string BCVATcCEnZ;
      string EUIedANjYT;
      string dfDCLOSsRb;
      string STxBZlViwA;
      string rdYiMiaCph;
      string oZipBUzToF;
      string JJmMHkXGEr;
      string denYbzHUob;
      string mPCilrjGzF;
      string mCsppiqMbb;
      string LTxyEKlKOB;
      string NedNRsGDZO;
      string AQGzFakxhr;
      string IurMPTSEeb;
      string FZryqIXfYx;
      string cmlMbuNysc;
      string YobVsSlRyy;
      if(yBOAecbIgb == denYbzHUob){aBYxJaXIIw = true;}
      else if(denYbzHUob == yBOAecbIgb){uScRQpbyfp = true;}
      if(oqiQcuhMIR == mPCilrjGzF){DFXkPUIfjU = true;}
      else if(mPCilrjGzF == oqiQcuhMIR){bbwJsXlVTJ = true;}
      if(EihUhDKIKe == mCsppiqMbb){GTLBDQxVFY = true;}
      else if(mCsppiqMbb == EihUhDKIKe){XSPzDPYTKc = true;}
      if(BCVATcCEnZ == LTxyEKlKOB){VGhZVaOoCB = true;}
      else if(LTxyEKlKOB == BCVATcCEnZ){AXsyogcyQY = true;}
      if(EUIedANjYT == NedNRsGDZO){WEowZSQqGX = true;}
      else if(NedNRsGDZO == EUIedANjYT){oZYrmJtkPA = true;}
      if(dfDCLOSsRb == AQGzFakxhr){JFgcrGpXts = true;}
      else if(AQGzFakxhr == dfDCLOSsRb){ielMEbDdNA = true;}
      if(STxBZlViwA == IurMPTSEeb){cCDiZxXyOn = true;}
      else if(IurMPTSEeb == STxBZlViwA){RHmCoDhxTM = true;}
      if(rdYiMiaCph == FZryqIXfYx){GTdixBeOak = true;}
      if(oZipBUzToF == cmlMbuNysc){zFPgOQYEhP = true;}
      if(JJmMHkXGEr == YobVsSlRyy){kpuJXUBGVc = true;}
      while(FZryqIXfYx == rdYiMiaCph){umFuUxtXLt = true;}
      while(cmlMbuNysc == cmlMbuNysc){VmDKtVlgsN = true;}
      while(YobVsSlRyy == YobVsSlRyy){cyjQGgmVCj = true;}
      if(aBYxJaXIIw == true){aBYxJaXIIw = false;}
      if(DFXkPUIfjU == true){DFXkPUIfjU = false;}
      if(GTLBDQxVFY == true){GTLBDQxVFY = false;}
      if(VGhZVaOoCB == true){VGhZVaOoCB = false;}
      if(WEowZSQqGX == true){WEowZSQqGX = false;}
      if(JFgcrGpXts == true){JFgcrGpXts = false;}
      if(cCDiZxXyOn == true){cCDiZxXyOn = false;}
      if(GTdixBeOak == true){GTdixBeOak = false;}
      if(zFPgOQYEhP == true){zFPgOQYEhP = false;}
      if(kpuJXUBGVc == true){kpuJXUBGVc = false;}
      if(uScRQpbyfp == true){uScRQpbyfp = false;}
      if(bbwJsXlVTJ == true){bbwJsXlVTJ = false;}
      if(XSPzDPYTKc == true){XSPzDPYTKc = false;}
      if(AXsyogcyQY == true){AXsyogcyQY = false;}
      if(oZYrmJtkPA == true){oZYrmJtkPA = false;}
      if(ielMEbDdNA == true){ielMEbDdNA = false;}
      if(RHmCoDhxTM == true){RHmCoDhxTM = false;}
      if(umFuUxtXLt == true){umFuUxtXLt = false;}
      if(VmDKtVlgsN == true){VmDKtVlgsN = false;}
      if(cyjQGgmVCj == true){cyjQGgmVCj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BDZLKTAWTH
{ 
  void dkmNtIlkgm()
  { 
      bool TiSMlMmDgY = false;
      bool hnASHjJOxe = false;
      bool FpxSJPcsOn = false;
      bool wJtSiEqCYL = false;
      bool XfSpPeEawz = false;
      bool DMyPMckACV = false;
      bool jtosbYthiC = false;
      bool sHplHYXHCe = false;
      bool LBwPjiLeGG = false;
      bool SpzCbdqYNq = false;
      bool kWqsFwWLHm = false;
      bool FdxXKhxZJs = false;
      bool NObcjCHnKd = false;
      bool hzsLtoJDJn = false;
      bool MzWSBnsbrs = false;
      bool gRPUcVtOJD = false;
      bool nhBdEFjkdV = false;
      bool XsPVgOrIbu = false;
      bool IfwQwQiYiX = false;
      bool tutGzdxrOu = false;
      string QEkcjyMkbQ;
      string CTfoIbWQpd;
      string febdbFRdKk;
      string OeAhSLZouB;
      string CFRXudDzfg;
      string UziELlcGBd;
      string fiZpCWSxWw;
      string ChVoaaMDix;
      string CSydPOwuWf;
      string iSnQVTfbVX;
      string KFbiemcsdk;
      string ZYXDaMkwZm;
      string aWaqNisETH;
      string tkhLlxqOzc;
      string lCRkGKujpI;
      string ijBhwndkVu;
      string sXZVpopLRc;
      string VVwxBXFojD;
      string nJOKYKizOy;
      string TFsDiNbuuR;
      if(QEkcjyMkbQ == KFbiemcsdk){TiSMlMmDgY = true;}
      else if(KFbiemcsdk == QEkcjyMkbQ){kWqsFwWLHm = true;}
      if(CTfoIbWQpd == ZYXDaMkwZm){hnASHjJOxe = true;}
      else if(ZYXDaMkwZm == CTfoIbWQpd){FdxXKhxZJs = true;}
      if(febdbFRdKk == aWaqNisETH){FpxSJPcsOn = true;}
      else if(aWaqNisETH == febdbFRdKk){NObcjCHnKd = true;}
      if(OeAhSLZouB == tkhLlxqOzc){wJtSiEqCYL = true;}
      else if(tkhLlxqOzc == OeAhSLZouB){hzsLtoJDJn = true;}
      if(CFRXudDzfg == lCRkGKujpI){XfSpPeEawz = true;}
      else if(lCRkGKujpI == CFRXudDzfg){MzWSBnsbrs = true;}
      if(UziELlcGBd == ijBhwndkVu){DMyPMckACV = true;}
      else if(ijBhwndkVu == UziELlcGBd){gRPUcVtOJD = true;}
      if(fiZpCWSxWw == sXZVpopLRc){jtosbYthiC = true;}
      else if(sXZVpopLRc == fiZpCWSxWw){nhBdEFjkdV = true;}
      if(ChVoaaMDix == VVwxBXFojD){sHplHYXHCe = true;}
      if(CSydPOwuWf == nJOKYKizOy){LBwPjiLeGG = true;}
      if(iSnQVTfbVX == TFsDiNbuuR){SpzCbdqYNq = true;}
      while(VVwxBXFojD == ChVoaaMDix){XsPVgOrIbu = true;}
      while(nJOKYKizOy == nJOKYKizOy){IfwQwQiYiX = true;}
      while(TFsDiNbuuR == TFsDiNbuuR){tutGzdxrOu = true;}
      if(TiSMlMmDgY == true){TiSMlMmDgY = false;}
      if(hnASHjJOxe == true){hnASHjJOxe = false;}
      if(FpxSJPcsOn == true){FpxSJPcsOn = false;}
      if(wJtSiEqCYL == true){wJtSiEqCYL = false;}
      if(XfSpPeEawz == true){XfSpPeEawz = false;}
      if(DMyPMckACV == true){DMyPMckACV = false;}
      if(jtosbYthiC == true){jtosbYthiC = false;}
      if(sHplHYXHCe == true){sHplHYXHCe = false;}
      if(LBwPjiLeGG == true){LBwPjiLeGG = false;}
      if(SpzCbdqYNq == true){SpzCbdqYNq = false;}
      if(kWqsFwWLHm == true){kWqsFwWLHm = false;}
      if(FdxXKhxZJs == true){FdxXKhxZJs = false;}
      if(NObcjCHnKd == true){NObcjCHnKd = false;}
      if(hzsLtoJDJn == true){hzsLtoJDJn = false;}
      if(MzWSBnsbrs == true){MzWSBnsbrs = false;}
      if(gRPUcVtOJD == true){gRPUcVtOJD = false;}
      if(nhBdEFjkdV == true){nhBdEFjkdV = false;}
      if(XsPVgOrIbu == true){XsPVgOrIbu = false;}
      if(IfwQwQiYiX == true){IfwQwQiYiX = false;}
      if(tutGzdxrOu == true){tutGzdxrOu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGMOLYJHOX
{ 
  void ZNfBBRKPkZ()
  { 
      bool pPByBIEIpU = false;
      bool LwManrnsMe = false;
      bool EMFRKqyuOR = false;
      bool kmamKHpWcq = false;
      bool aYZKzJRZSF = false;
      bool BmRbGcKjmK = false;
      bool KIsYjXUZQf = false;
      bool BRPUEeltRB = false;
      bool YXcJPxVzgg = false;
      bool xGiSgRfBaa = false;
      bool nrJlDjWwWa = false;
      bool qQRkklfiIl = false;
      bool CVriiuhxnl = false;
      bool zkSpNgOpGf = false;
      bool ZYbFpgnxhu = false;
      bool lwrnYSAZDI = false;
      bool BZIkbGxbXE = false;
      bool WoccLdslsC = false;
      bool GjOszCrdRt = false;
      bool fomxdAPqdj = false;
      string aqReZmHizp;
      string DGpVHGFhgq;
      string KTcolJeCMO;
      string oyiaqafngs;
      string sxAHNKtjcK;
      string YuQULGOcrQ;
      string HEVkBEXPdf;
      string aRBnyNSVab;
      string OuZBoshOPj;
      string MCuQknaPFJ;
      string meFwjHtbWx;
      string nsCQBMdTuH;
      string WJztTXWjDJ;
      string lCPRnjpdRh;
      string zFqRwTAdOX;
      string JGUyldeKbL;
      string kJYMKkcjbQ;
      string WACMHRRhyA;
      string XrUeAfgQeK;
      string FeBGxpgdGK;
      if(aqReZmHizp == meFwjHtbWx){pPByBIEIpU = true;}
      else if(meFwjHtbWx == aqReZmHizp){nrJlDjWwWa = true;}
      if(DGpVHGFhgq == nsCQBMdTuH){LwManrnsMe = true;}
      else if(nsCQBMdTuH == DGpVHGFhgq){qQRkklfiIl = true;}
      if(KTcolJeCMO == WJztTXWjDJ){EMFRKqyuOR = true;}
      else if(WJztTXWjDJ == KTcolJeCMO){CVriiuhxnl = true;}
      if(oyiaqafngs == lCPRnjpdRh){kmamKHpWcq = true;}
      else if(lCPRnjpdRh == oyiaqafngs){zkSpNgOpGf = true;}
      if(sxAHNKtjcK == zFqRwTAdOX){aYZKzJRZSF = true;}
      else if(zFqRwTAdOX == sxAHNKtjcK){ZYbFpgnxhu = true;}
      if(YuQULGOcrQ == JGUyldeKbL){BmRbGcKjmK = true;}
      else if(JGUyldeKbL == YuQULGOcrQ){lwrnYSAZDI = true;}
      if(HEVkBEXPdf == kJYMKkcjbQ){KIsYjXUZQf = true;}
      else if(kJYMKkcjbQ == HEVkBEXPdf){BZIkbGxbXE = true;}
      if(aRBnyNSVab == WACMHRRhyA){BRPUEeltRB = true;}
      if(OuZBoshOPj == XrUeAfgQeK){YXcJPxVzgg = true;}
      if(MCuQknaPFJ == FeBGxpgdGK){xGiSgRfBaa = true;}
      while(WACMHRRhyA == aRBnyNSVab){WoccLdslsC = true;}
      while(XrUeAfgQeK == XrUeAfgQeK){GjOszCrdRt = true;}
      while(FeBGxpgdGK == FeBGxpgdGK){fomxdAPqdj = true;}
      if(pPByBIEIpU == true){pPByBIEIpU = false;}
      if(LwManrnsMe == true){LwManrnsMe = false;}
      if(EMFRKqyuOR == true){EMFRKqyuOR = false;}
      if(kmamKHpWcq == true){kmamKHpWcq = false;}
      if(aYZKzJRZSF == true){aYZKzJRZSF = false;}
      if(BmRbGcKjmK == true){BmRbGcKjmK = false;}
      if(KIsYjXUZQf == true){KIsYjXUZQf = false;}
      if(BRPUEeltRB == true){BRPUEeltRB = false;}
      if(YXcJPxVzgg == true){YXcJPxVzgg = false;}
      if(xGiSgRfBaa == true){xGiSgRfBaa = false;}
      if(nrJlDjWwWa == true){nrJlDjWwWa = false;}
      if(qQRkklfiIl == true){qQRkklfiIl = false;}
      if(CVriiuhxnl == true){CVriiuhxnl = false;}
      if(zkSpNgOpGf == true){zkSpNgOpGf = false;}
      if(ZYbFpgnxhu == true){ZYbFpgnxhu = false;}
      if(lwrnYSAZDI == true){lwrnYSAZDI = false;}
      if(BZIkbGxbXE == true){BZIkbGxbXE = false;}
      if(WoccLdslsC == true){WoccLdslsC = false;}
      if(GjOszCrdRt == true){GjOszCrdRt = false;}
      if(fomxdAPqdj == true){fomxdAPqdj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QJOKKPFPBT
{ 
  void hVrULarCUo()
  { 
      bool ZqHsuuyUWg = false;
      bool rNoVrIhLxG = false;
      bool dRhFFKAyep = false;
      bool HzPaJFuUib = false;
      bool fckFhKAwVz = false;
      bool MGIbrIIBnk = false;
      bool tzofZsxNLl = false;
      bool NMcUaBgcWu = false;
      bool KEbedApniB = false;
      bool wsgxgfmFeo = false;
      bool NlkilzdmBp = false;
      bool afdrapWKCY = false;
      bool CIeJoTfent = false;
      bool OaxhgXTrsd = false;
      bool VDmrZQOnWq = false;
      bool IcCFlEHbtR = false;
      bool TzzGaAiwLC = false;
      bool WdQXDyVliY = false;
      bool FrHwklXqwc = false;
      bool PqyaKVEfQZ = false;
      string EhdzjNkGbl;
      string tuyFKJesLA;
      string PFpfsEYflB;
      string jmglciYxSN;
      string JxmnwroLRi;
      string hJOysyryFe;
      string oEUZCGOLbb;
      string jhaypSRBiB;
      string OMOCTZYhse;
      string qarnXEcNko;
      string cdjpyAiPHZ;
      string fpOEPbpRFc;
      string hfRwkJplZl;
      string oEQtXkcXES;
      string qIaSyALmXu;
      string OLHIHxMmFo;
      string KwpUkbZUfe;
      string zSMmkZEyyj;
      string xCOdXdxHla;
      string YoROIuSFhW;
      if(EhdzjNkGbl == cdjpyAiPHZ){ZqHsuuyUWg = true;}
      else if(cdjpyAiPHZ == EhdzjNkGbl){NlkilzdmBp = true;}
      if(tuyFKJesLA == fpOEPbpRFc){rNoVrIhLxG = true;}
      else if(fpOEPbpRFc == tuyFKJesLA){afdrapWKCY = true;}
      if(PFpfsEYflB == hfRwkJplZl){dRhFFKAyep = true;}
      else if(hfRwkJplZl == PFpfsEYflB){CIeJoTfent = true;}
      if(jmglciYxSN == oEQtXkcXES){HzPaJFuUib = true;}
      else if(oEQtXkcXES == jmglciYxSN){OaxhgXTrsd = true;}
      if(JxmnwroLRi == qIaSyALmXu){fckFhKAwVz = true;}
      else if(qIaSyALmXu == JxmnwroLRi){VDmrZQOnWq = true;}
      if(hJOysyryFe == OLHIHxMmFo){MGIbrIIBnk = true;}
      else if(OLHIHxMmFo == hJOysyryFe){IcCFlEHbtR = true;}
      if(oEUZCGOLbb == KwpUkbZUfe){tzofZsxNLl = true;}
      else if(KwpUkbZUfe == oEUZCGOLbb){TzzGaAiwLC = true;}
      if(jhaypSRBiB == zSMmkZEyyj){NMcUaBgcWu = true;}
      if(OMOCTZYhse == xCOdXdxHla){KEbedApniB = true;}
      if(qarnXEcNko == YoROIuSFhW){wsgxgfmFeo = true;}
      while(zSMmkZEyyj == jhaypSRBiB){WdQXDyVliY = true;}
      while(xCOdXdxHla == xCOdXdxHla){FrHwklXqwc = true;}
      while(YoROIuSFhW == YoROIuSFhW){PqyaKVEfQZ = true;}
      if(ZqHsuuyUWg == true){ZqHsuuyUWg = false;}
      if(rNoVrIhLxG == true){rNoVrIhLxG = false;}
      if(dRhFFKAyep == true){dRhFFKAyep = false;}
      if(HzPaJFuUib == true){HzPaJFuUib = false;}
      if(fckFhKAwVz == true){fckFhKAwVz = false;}
      if(MGIbrIIBnk == true){MGIbrIIBnk = false;}
      if(tzofZsxNLl == true){tzofZsxNLl = false;}
      if(NMcUaBgcWu == true){NMcUaBgcWu = false;}
      if(KEbedApniB == true){KEbedApniB = false;}
      if(wsgxgfmFeo == true){wsgxgfmFeo = false;}
      if(NlkilzdmBp == true){NlkilzdmBp = false;}
      if(afdrapWKCY == true){afdrapWKCY = false;}
      if(CIeJoTfent == true){CIeJoTfent = false;}
      if(OaxhgXTrsd == true){OaxhgXTrsd = false;}
      if(VDmrZQOnWq == true){VDmrZQOnWq = false;}
      if(IcCFlEHbtR == true){IcCFlEHbtR = false;}
      if(TzzGaAiwLC == true){TzzGaAiwLC = false;}
      if(WdQXDyVliY == true){WdQXDyVliY = false;}
      if(FrHwklXqwc == true){FrHwklXqwc = false;}
      if(PqyaKVEfQZ == true){PqyaKVEfQZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HZKERMQSBY
{ 
  void bTWWhzAnsf()
  { 
      bool FRHWJIFPzY = false;
      bool VIHxrXkdUE = false;
      bool QtxHpLPIez = false;
      bool gxMnsJpqfK = false;
      bool WKFEwlHLdy = false;
      bool crHjZLUAfx = false;
      bool swjzqXwTEh = false;
      bool htyJhForLE = false;
      bool DDefVoobNg = false;
      bool ooKhQZZFMX = false;
      bool pnGwQisyCU = false;
      bool WbnbtpRDdC = false;
      bool iTGWsriQrI = false;
      bool eiemNPxiPl = false;
      bool uqZsKMBina = false;
      bool HVbJnVgiDY = false;
      bool zcFtomxBNd = false;
      bool rinqHrsNMf = false;
      bool qAcQAIHUyr = false;
      bool hNepmRkfDW = false;
      string wdqlAYJMgp;
      string tSVuMgLJlJ;
      string YFHeuQpaNs;
      string dQPfLplLkx;
      string uFAAArZlVi;
      string AtgFOqWLqi;
      string hizmLcCpjV;
      string uzYnOTFGdD;
      string pEEdsjiJRU;
      string TaUBOMFMoW;
      string ojBznAVsqt;
      string kPhmrddUtb;
      string tsYOCUeWZC;
      string NsRGNGCFpr;
      string NpSWiDrgIj;
      string hkRMcwLmwT;
      string VzTogryaZl;
      string aYeCNDaCey;
      string bxNoTbaEdR;
      string uPJVWOWcoq;
      if(wdqlAYJMgp == ojBznAVsqt){FRHWJIFPzY = true;}
      else if(ojBznAVsqt == wdqlAYJMgp){pnGwQisyCU = true;}
      if(tSVuMgLJlJ == kPhmrddUtb){VIHxrXkdUE = true;}
      else if(kPhmrddUtb == tSVuMgLJlJ){WbnbtpRDdC = true;}
      if(YFHeuQpaNs == tsYOCUeWZC){QtxHpLPIez = true;}
      else if(tsYOCUeWZC == YFHeuQpaNs){iTGWsriQrI = true;}
      if(dQPfLplLkx == NsRGNGCFpr){gxMnsJpqfK = true;}
      else if(NsRGNGCFpr == dQPfLplLkx){eiemNPxiPl = true;}
      if(uFAAArZlVi == NpSWiDrgIj){WKFEwlHLdy = true;}
      else if(NpSWiDrgIj == uFAAArZlVi){uqZsKMBina = true;}
      if(AtgFOqWLqi == hkRMcwLmwT){crHjZLUAfx = true;}
      else if(hkRMcwLmwT == AtgFOqWLqi){HVbJnVgiDY = true;}
      if(hizmLcCpjV == VzTogryaZl){swjzqXwTEh = true;}
      else if(VzTogryaZl == hizmLcCpjV){zcFtomxBNd = true;}
      if(uzYnOTFGdD == aYeCNDaCey){htyJhForLE = true;}
      if(pEEdsjiJRU == bxNoTbaEdR){DDefVoobNg = true;}
      if(TaUBOMFMoW == uPJVWOWcoq){ooKhQZZFMX = true;}
      while(aYeCNDaCey == uzYnOTFGdD){rinqHrsNMf = true;}
      while(bxNoTbaEdR == bxNoTbaEdR){qAcQAIHUyr = true;}
      while(uPJVWOWcoq == uPJVWOWcoq){hNepmRkfDW = true;}
      if(FRHWJIFPzY == true){FRHWJIFPzY = false;}
      if(VIHxrXkdUE == true){VIHxrXkdUE = false;}
      if(QtxHpLPIez == true){QtxHpLPIez = false;}
      if(gxMnsJpqfK == true){gxMnsJpqfK = false;}
      if(WKFEwlHLdy == true){WKFEwlHLdy = false;}
      if(crHjZLUAfx == true){crHjZLUAfx = false;}
      if(swjzqXwTEh == true){swjzqXwTEh = false;}
      if(htyJhForLE == true){htyJhForLE = false;}
      if(DDefVoobNg == true){DDefVoobNg = false;}
      if(ooKhQZZFMX == true){ooKhQZZFMX = false;}
      if(pnGwQisyCU == true){pnGwQisyCU = false;}
      if(WbnbtpRDdC == true){WbnbtpRDdC = false;}
      if(iTGWsriQrI == true){iTGWsriQrI = false;}
      if(eiemNPxiPl == true){eiemNPxiPl = false;}
      if(uqZsKMBina == true){uqZsKMBina = false;}
      if(HVbJnVgiDY == true){HVbJnVgiDY = false;}
      if(zcFtomxBNd == true){zcFtomxBNd = false;}
      if(rinqHrsNMf == true){rinqHrsNMf = false;}
      if(qAcQAIHUyr == true){qAcQAIHUyr = false;}
      if(hNepmRkfDW == true){hNepmRkfDW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FVNEWAJNDY
{ 
  void sCyRgYSIjF()
  { 
      bool KpMEIDQcVT = false;
      bool cpHUXiFxCb = false;
      bool NcsJmnrnOW = false;
      bool QxnotmUOFS = false;
      bool PqUftAFLhK = false;
      bool naVgwgwCRU = false;
      bool LcOzDeCSZk = false;
      bool OqrjLWHNPl = false;
      bool hgFEioaGrN = false;
      bool qRwkHlcVbO = false;
      bool ylkxwwhkUZ = false;
      bool ZhmeldWJQO = false;
      bool DuaMtwtHcZ = false;
      bool tllAnwuIIl = false;
      bool HplRmIdRyc = false;
      bool OSENLCLXDz = false;
      bool BaIufmwlqp = false;
      bool iOAeGNJIYk = false;
      bool ScIAKagXok = false;
      bool jXFJjfgpkz = false;
      string bDJopjoKjw;
      string rkxFshNVTK;
      string oeCPxFuqlR;
      string RBwUedgobS;
      string FkVBYHcaZP;
      string QVibExAtrk;
      string oxXSeqncaO;
      string AXtAFEIBqo;
      string cTRWBuRTQh;
      string dmwqdHMCWg;
      string SzAKOrbhWz;
      string nzDCHUfBRj;
      string YTMsjNbCWx;
      string qFdJVcTGHJ;
      string SjxQsejtiI;
      string bKkmIzlHaB;
      string QYLYHhUtgd;
      string AYtHQnWwzF;
      string cgTNVfUqAW;
      string qMfGssXYIK;
      if(bDJopjoKjw == SzAKOrbhWz){KpMEIDQcVT = true;}
      else if(SzAKOrbhWz == bDJopjoKjw){ylkxwwhkUZ = true;}
      if(rkxFshNVTK == nzDCHUfBRj){cpHUXiFxCb = true;}
      else if(nzDCHUfBRj == rkxFshNVTK){ZhmeldWJQO = true;}
      if(oeCPxFuqlR == YTMsjNbCWx){NcsJmnrnOW = true;}
      else if(YTMsjNbCWx == oeCPxFuqlR){DuaMtwtHcZ = true;}
      if(RBwUedgobS == qFdJVcTGHJ){QxnotmUOFS = true;}
      else if(qFdJVcTGHJ == RBwUedgobS){tllAnwuIIl = true;}
      if(FkVBYHcaZP == SjxQsejtiI){PqUftAFLhK = true;}
      else if(SjxQsejtiI == FkVBYHcaZP){HplRmIdRyc = true;}
      if(QVibExAtrk == bKkmIzlHaB){naVgwgwCRU = true;}
      else if(bKkmIzlHaB == QVibExAtrk){OSENLCLXDz = true;}
      if(oxXSeqncaO == QYLYHhUtgd){LcOzDeCSZk = true;}
      else if(QYLYHhUtgd == oxXSeqncaO){BaIufmwlqp = true;}
      if(AXtAFEIBqo == AYtHQnWwzF){OqrjLWHNPl = true;}
      if(cTRWBuRTQh == cgTNVfUqAW){hgFEioaGrN = true;}
      if(dmwqdHMCWg == qMfGssXYIK){qRwkHlcVbO = true;}
      while(AYtHQnWwzF == AXtAFEIBqo){iOAeGNJIYk = true;}
      while(cgTNVfUqAW == cgTNVfUqAW){ScIAKagXok = true;}
      while(qMfGssXYIK == qMfGssXYIK){jXFJjfgpkz = true;}
      if(KpMEIDQcVT == true){KpMEIDQcVT = false;}
      if(cpHUXiFxCb == true){cpHUXiFxCb = false;}
      if(NcsJmnrnOW == true){NcsJmnrnOW = false;}
      if(QxnotmUOFS == true){QxnotmUOFS = false;}
      if(PqUftAFLhK == true){PqUftAFLhK = false;}
      if(naVgwgwCRU == true){naVgwgwCRU = false;}
      if(LcOzDeCSZk == true){LcOzDeCSZk = false;}
      if(OqrjLWHNPl == true){OqrjLWHNPl = false;}
      if(hgFEioaGrN == true){hgFEioaGrN = false;}
      if(qRwkHlcVbO == true){qRwkHlcVbO = false;}
      if(ylkxwwhkUZ == true){ylkxwwhkUZ = false;}
      if(ZhmeldWJQO == true){ZhmeldWJQO = false;}
      if(DuaMtwtHcZ == true){DuaMtwtHcZ = false;}
      if(tllAnwuIIl == true){tllAnwuIIl = false;}
      if(HplRmIdRyc == true){HplRmIdRyc = false;}
      if(OSENLCLXDz == true){OSENLCLXDz = false;}
      if(BaIufmwlqp == true){BaIufmwlqp = false;}
      if(iOAeGNJIYk == true){iOAeGNJIYk = false;}
      if(ScIAKagXok == true){ScIAKagXok = false;}
      if(jXFJjfgpkz == true){jXFJjfgpkz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHDMANEFMQ
{ 
  void DzfnlftXAX()
  { 
      bool EaDrbFyXXt = false;
      bool cUkEBkHILd = false;
      bool wUnePmwcGn = false;
      bool mAWpcDYtkp = false;
      bool sypEbMNhir = false;
      bool okhRZjlYcn = false;
      bool JVRiHcxtbx = false;
      bool MMWUkxejDD = false;
      bool ZOsOzBRFPs = false;
      bool RARwgWgHxy = false;
      bool OTGkfbOMgc = false;
      bool FBVYOtbDjF = false;
      bool KqdhfLtamN = false;
      bool QWmEnGIIiW = false;
      bool mEXmnPesgl = false;
      bool udXqmXoYET = false;
      bool gmYTLhOQkI = false;
      bool lSTMSFTpsQ = false;
      bool gBsBSmzuQQ = false;
      bool QjDOozfEbG = false;
      string MywGyTGHTG;
      string ASglaJVuFg;
      string EAjjBplLlT;
      string QnbHyJnFNe;
      string uKkbkHxnau;
      string wDYgRMOMFI;
      string gtUApMpZnQ;
      string VQgZlsPIys;
      string rxjpXNOuol;
      string tbAFyApkkY;
      string RXAJZeVytY;
      string wGNLQiKdcc;
      string xtjCWsQbbl;
      string DeWZbTxZQr;
      string qQBQonOnnO;
      string pLIIaWmymf;
      string OtVHURimjw;
      string ljMjkgsSNh;
      string ecmNwqVNyF;
      string gymjdwtsuW;
      if(MywGyTGHTG == RXAJZeVytY){EaDrbFyXXt = true;}
      else if(RXAJZeVytY == MywGyTGHTG){OTGkfbOMgc = true;}
      if(ASglaJVuFg == wGNLQiKdcc){cUkEBkHILd = true;}
      else if(wGNLQiKdcc == ASglaJVuFg){FBVYOtbDjF = true;}
      if(EAjjBplLlT == xtjCWsQbbl){wUnePmwcGn = true;}
      else if(xtjCWsQbbl == EAjjBplLlT){KqdhfLtamN = true;}
      if(QnbHyJnFNe == DeWZbTxZQr){mAWpcDYtkp = true;}
      else if(DeWZbTxZQr == QnbHyJnFNe){QWmEnGIIiW = true;}
      if(uKkbkHxnau == qQBQonOnnO){sypEbMNhir = true;}
      else if(qQBQonOnnO == uKkbkHxnau){mEXmnPesgl = true;}
      if(wDYgRMOMFI == pLIIaWmymf){okhRZjlYcn = true;}
      else if(pLIIaWmymf == wDYgRMOMFI){udXqmXoYET = true;}
      if(gtUApMpZnQ == OtVHURimjw){JVRiHcxtbx = true;}
      else if(OtVHURimjw == gtUApMpZnQ){gmYTLhOQkI = true;}
      if(VQgZlsPIys == ljMjkgsSNh){MMWUkxejDD = true;}
      if(rxjpXNOuol == ecmNwqVNyF){ZOsOzBRFPs = true;}
      if(tbAFyApkkY == gymjdwtsuW){RARwgWgHxy = true;}
      while(ljMjkgsSNh == VQgZlsPIys){lSTMSFTpsQ = true;}
      while(ecmNwqVNyF == ecmNwqVNyF){gBsBSmzuQQ = true;}
      while(gymjdwtsuW == gymjdwtsuW){QjDOozfEbG = true;}
      if(EaDrbFyXXt == true){EaDrbFyXXt = false;}
      if(cUkEBkHILd == true){cUkEBkHILd = false;}
      if(wUnePmwcGn == true){wUnePmwcGn = false;}
      if(mAWpcDYtkp == true){mAWpcDYtkp = false;}
      if(sypEbMNhir == true){sypEbMNhir = false;}
      if(okhRZjlYcn == true){okhRZjlYcn = false;}
      if(JVRiHcxtbx == true){JVRiHcxtbx = false;}
      if(MMWUkxejDD == true){MMWUkxejDD = false;}
      if(ZOsOzBRFPs == true){ZOsOzBRFPs = false;}
      if(RARwgWgHxy == true){RARwgWgHxy = false;}
      if(OTGkfbOMgc == true){OTGkfbOMgc = false;}
      if(FBVYOtbDjF == true){FBVYOtbDjF = false;}
      if(KqdhfLtamN == true){KqdhfLtamN = false;}
      if(QWmEnGIIiW == true){QWmEnGIIiW = false;}
      if(mEXmnPesgl == true){mEXmnPesgl = false;}
      if(udXqmXoYET == true){udXqmXoYET = false;}
      if(gmYTLhOQkI == true){gmYTLhOQkI = false;}
      if(lSTMSFTpsQ == true){lSTMSFTpsQ = false;}
      if(gBsBSmzuQQ == true){gBsBSmzuQQ = false;}
      if(QjDOozfEbG == true){QjDOozfEbG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OHLKKQNCTB
{ 
  void fsPPEjniRs()
  { 
      bool AdtVceqNuD = false;
      bool YZxFbUWlGd = false;
      bool UFfLmNrcXr = false;
      bool WMMmFizFQY = false;
      bool OqqhIOmRqu = false;
      bool fjilnuyhiO = false;
      bool mNpCfMMKzs = false;
      bool UQVgOcNxDX = false;
      bool ZakbMmcazK = false;
      bool jQVBkABnBu = false;
      bool CbRyZOOBWK = false;
      bool gBeKoMcOps = false;
      bool jlLoIDtTwO = false;
      bool bYuHVxJlBx = false;
      bool YaDncilLMY = false;
      bool XmyHLPQbpW = false;
      bool TtFIhHFXnq = false;
      bool DpMsUJiXMZ = false;
      bool RiGWpoamwG = false;
      bool ggweddUtFV = false;
      string EAqZQMySoP;
      string gVAcDXGPOT;
      string nrSRhSdKHu;
      string tgIrdsThTn;
      string dCPGrrpYTB;
      string TUbyOLgYry;
      string imKtUANHyK;
      string DXuaokcMZo;
      string bEqGaZEJdS;
      string MupUFprUkr;
      string ehZJxwYBJc;
      string iTzDVdwESu;
      string uDdfyIgaUy;
      string sHbhJsehIe;
      string ACAAjrumza;
      string tmCowbEtKo;
      string OyfKjarRsc;
      string yOwntsCdwF;
      string MsbsEFFlkh;
      string okWSQCVpQI;
      if(EAqZQMySoP == ehZJxwYBJc){AdtVceqNuD = true;}
      else if(ehZJxwYBJc == EAqZQMySoP){CbRyZOOBWK = true;}
      if(gVAcDXGPOT == iTzDVdwESu){YZxFbUWlGd = true;}
      else if(iTzDVdwESu == gVAcDXGPOT){gBeKoMcOps = true;}
      if(nrSRhSdKHu == uDdfyIgaUy){UFfLmNrcXr = true;}
      else if(uDdfyIgaUy == nrSRhSdKHu){jlLoIDtTwO = true;}
      if(tgIrdsThTn == sHbhJsehIe){WMMmFizFQY = true;}
      else if(sHbhJsehIe == tgIrdsThTn){bYuHVxJlBx = true;}
      if(dCPGrrpYTB == ACAAjrumza){OqqhIOmRqu = true;}
      else if(ACAAjrumza == dCPGrrpYTB){YaDncilLMY = true;}
      if(TUbyOLgYry == tmCowbEtKo){fjilnuyhiO = true;}
      else if(tmCowbEtKo == TUbyOLgYry){XmyHLPQbpW = true;}
      if(imKtUANHyK == OyfKjarRsc){mNpCfMMKzs = true;}
      else if(OyfKjarRsc == imKtUANHyK){TtFIhHFXnq = true;}
      if(DXuaokcMZo == yOwntsCdwF){UQVgOcNxDX = true;}
      if(bEqGaZEJdS == MsbsEFFlkh){ZakbMmcazK = true;}
      if(MupUFprUkr == okWSQCVpQI){jQVBkABnBu = true;}
      while(yOwntsCdwF == DXuaokcMZo){DpMsUJiXMZ = true;}
      while(MsbsEFFlkh == MsbsEFFlkh){RiGWpoamwG = true;}
      while(okWSQCVpQI == okWSQCVpQI){ggweddUtFV = true;}
      if(AdtVceqNuD == true){AdtVceqNuD = false;}
      if(YZxFbUWlGd == true){YZxFbUWlGd = false;}
      if(UFfLmNrcXr == true){UFfLmNrcXr = false;}
      if(WMMmFizFQY == true){WMMmFizFQY = false;}
      if(OqqhIOmRqu == true){OqqhIOmRqu = false;}
      if(fjilnuyhiO == true){fjilnuyhiO = false;}
      if(mNpCfMMKzs == true){mNpCfMMKzs = false;}
      if(UQVgOcNxDX == true){UQVgOcNxDX = false;}
      if(ZakbMmcazK == true){ZakbMmcazK = false;}
      if(jQVBkABnBu == true){jQVBkABnBu = false;}
      if(CbRyZOOBWK == true){CbRyZOOBWK = false;}
      if(gBeKoMcOps == true){gBeKoMcOps = false;}
      if(jlLoIDtTwO == true){jlLoIDtTwO = false;}
      if(bYuHVxJlBx == true){bYuHVxJlBx = false;}
      if(YaDncilLMY == true){YaDncilLMY = false;}
      if(XmyHLPQbpW == true){XmyHLPQbpW = false;}
      if(TtFIhHFXnq == true){TtFIhHFXnq = false;}
      if(DpMsUJiXMZ == true){DpMsUJiXMZ = false;}
      if(RiGWpoamwG == true){RiGWpoamwG = false;}
      if(ggweddUtFV == true){ggweddUtFV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MZUDONQNSK
{ 
  void DUwYRxdZJK()
  { 
      bool NlajMbXjyq = false;
      bool YfAKLahTJY = false;
      bool MHhCWsCxdW = false;
      bool NrBgDrEZsC = false;
      bool sDpJgKURmp = false;
      bool obANMGDXNS = false;
      bool YaFbcfdTHS = false;
      bool WIaHeJQYVL = false;
      bool XkKmglqmUx = false;
      bool ofLZcRxOgA = false;
      bool fBKUTgAshD = false;
      bool oeBBunQStq = false;
      bool nqyKcpwAdM = false;
      bool LCrVfWZoTA = false;
      bool kyFRHKdJeo = false;
      bool BeUpLoCzqd = false;
      bool jzOUqmlfVX = false;
      bool NaysFpkgCS = false;
      bool LlVoLfgCJq = false;
      bool TayoPkjjZU = false;
      string TRcXNyWqVR;
      string qDtIKYYKlU;
      string LgHOSykbaH;
      string rlcYgwTgii;
      string oUNajEFQRu;
      string NbJETmJOFP;
      string NuPOYFZVbN;
      string FqbDeqSgeN;
      string sTJetPbXFt;
      string lFbTVsEzBd;
      string eioDpVAGYb;
      string TbjqVslkTJ;
      string dCQgaAPHgk;
      string lSfAiJdFoX;
      string PUycZKUjxb;
      string HTfqAcSHbp;
      string GrYmpAwiIM;
      string PfwusJDmGQ;
      string eeKFdRmnAF;
      string pVcyRWuKlZ;
      if(TRcXNyWqVR == eioDpVAGYb){NlajMbXjyq = true;}
      else if(eioDpVAGYb == TRcXNyWqVR){fBKUTgAshD = true;}
      if(qDtIKYYKlU == TbjqVslkTJ){YfAKLahTJY = true;}
      else if(TbjqVslkTJ == qDtIKYYKlU){oeBBunQStq = true;}
      if(LgHOSykbaH == dCQgaAPHgk){MHhCWsCxdW = true;}
      else if(dCQgaAPHgk == LgHOSykbaH){nqyKcpwAdM = true;}
      if(rlcYgwTgii == lSfAiJdFoX){NrBgDrEZsC = true;}
      else if(lSfAiJdFoX == rlcYgwTgii){LCrVfWZoTA = true;}
      if(oUNajEFQRu == PUycZKUjxb){sDpJgKURmp = true;}
      else if(PUycZKUjxb == oUNajEFQRu){kyFRHKdJeo = true;}
      if(NbJETmJOFP == HTfqAcSHbp){obANMGDXNS = true;}
      else if(HTfqAcSHbp == NbJETmJOFP){BeUpLoCzqd = true;}
      if(NuPOYFZVbN == GrYmpAwiIM){YaFbcfdTHS = true;}
      else if(GrYmpAwiIM == NuPOYFZVbN){jzOUqmlfVX = true;}
      if(FqbDeqSgeN == PfwusJDmGQ){WIaHeJQYVL = true;}
      if(sTJetPbXFt == eeKFdRmnAF){XkKmglqmUx = true;}
      if(lFbTVsEzBd == pVcyRWuKlZ){ofLZcRxOgA = true;}
      while(PfwusJDmGQ == FqbDeqSgeN){NaysFpkgCS = true;}
      while(eeKFdRmnAF == eeKFdRmnAF){LlVoLfgCJq = true;}
      while(pVcyRWuKlZ == pVcyRWuKlZ){TayoPkjjZU = true;}
      if(NlajMbXjyq == true){NlajMbXjyq = false;}
      if(YfAKLahTJY == true){YfAKLahTJY = false;}
      if(MHhCWsCxdW == true){MHhCWsCxdW = false;}
      if(NrBgDrEZsC == true){NrBgDrEZsC = false;}
      if(sDpJgKURmp == true){sDpJgKURmp = false;}
      if(obANMGDXNS == true){obANMGDXNS = false;}
      if(YaFbcfdTHS == true){YaFbcfdTHS = false;}
      if(WIaHeJQYVL == true){WIaHeJQYVL = false;}
      if(XkKmglqmUx == true){XkKmglqmUx = false;}
      if(ofLZcRxOgA == true){ofLZcRxOgA = false;}
      if(fBKUTgAshD == true){fBKUTgAshD = false;}
      if(oeBBunQStq == true){oeBBunQStq = false;}
      if(nqyKcpwAdM == true){nqyKcpwAdM = false;}
      if(LCrVfWZoTA == true){LCrVfWZoTA = false;}
      if(kyFRHKdJeo == true){kyFRHKdJeo = false;}
      if(BeUpLoCzqd == true){BeUpLoCzqd = false;}
      if(jzOUqmlfVX == true){jzOUqmlfVX = false;}
      if(NaysFpkgCS == true){NaysFpkgCS = false;}
      if(LlVoLfgCJq == true){LlVoLfgCJq = false;}
      if(TayoPkjjZU == true){TayoPkjjZU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WDSVLHBMUZ
{ 
  void uYlSGanQMd()
  { 
      bool QkiqQkhsqY = false;
      bool bhUpsiyCxj = false;
      bool gzOCUqfnId = false;
      bool eZUPfzrSUi = false;
      bool PxusmjwlUO = false;
      bool NYfhiRWfWY = false;
      bool FsjMsBMFJt = false;
      bool qegNTiDUPj = false;
      bool usTtQGtlfO = false;
      bool cLwwdVMiAk = false;
      bool WqcaWhrRNA = false;
      bool OBQldLZpwm = false;
      bool HZYuQfikjy = false;
      bool VUUdNDQsWh = false;
      bool ObYfAatJRR = false;
      bool uWlMdxRgJq = false;
      bool zGhPdsgmYZ = false;
      bool ugTOYeBsup = false;
      bool kYSRCzhHzQ = false;
      bool liiehHsICG = false;
      string IpcYVndUic;
      string ORqBcitJUc;
      string GjasjDcAEX;
      string CbopcVhDTJ;
      string wtbRpIIrug;
      string clLMaYOioS;
      string KdQKambBXH;
      string BpoKgLIJCb;
      string tkEWuQQbOE;
      string HyOBzSdQpD;
      string fHTnflwAfP;
      string PEgNYZYsPJ;
      string WAlTACbmLN;
      string hrSzulQQqI;
      string TPuznCRBcZ;
      string sjAgffUAnc;
      string KInRgXkgRl;
      string IICHoGEmex;
      string jaKlUxqlSP;
      string RQcNyLadRP;
      if(IpcYVndUic == fHTnflwAfP){QkiqQkhsqY = true;}
      else if(fHTnflwAfP == IpcYVndUic){WqcaWhrRNA = true;}
      if(ORqBcitJUc == PEgNYZYsPJ){bhUpsiyCxj = true;}
      else if(PEgNYZYsPJ == ORqBcitJUc){OBQldLZpwm = true;}
      if(GjasjDcAEX == WAlTACbmLN){gzOCUqfnId = true;}
      else if(WAlTACbmLN == GjasjDcAEX){HZYuQfikjy = true;}
      if(CbopcVhDTJ == hrSzulQQqI){eZUPfzrSUi = true;}
      else if(hrSzulQQqI == CbopcVhDTJ){VUUdNDQsWh = true;}
      if(wtbRpIIrug == TPuznCRBcZ){PxusmjwlUO = true;}
      else if(TPuznCRBcZ == wtbRpIIrug){ObYfAatJRR = true;}
      if(clLMaYOioS == sjAgffUAnc){NYfhiRWfWY = true;}
      else if(sjAgffUAnc == clLMaYOioS){uWlMdxRgJq = true;}
      if(KdQKambBXH == KInRgXkgRl){FsjMsBMFJt = true;}
      else if(KInRgXkgRl == KdQKambBXH){zGhPdsgmYZ = true;}
      if(BpoKgLIJCb == IICHoGEmex){qegNTiDUPj = true;}
      if(tkEWuQQbOE == jaKlUxqlSP){usTtQGtlfO = true;}
      if(HyOBzSdQpD == RQcNyLadRP){cLwwdVMiAk = true;}
      while(IICHoGEmex == BpoKgLIJCb){ugTOYeBsup = true;}
      while(jaKlUxqlSP == jaKlUxqlSP){kYSRCzhHzQ = true;}
      while(RQcNyLadRP == RQcNyLadRP){liiehHsICG = true;}
      if(QkiqQkhsqY == true){QkiqQkhsqY = false;}
      if(bhUpsiyCxj == true){bhUpsiyCxj = false;}
      if(gzOCUqfnId == true){gzOCUqfnId = false;}
      if(eZUPfzrSUi == true){eZUPfzrSUi = false;}
      if(PxusmjwlUO == true){PxusmjwlUO = false;}
      if(NYfhiRWfWY == true){NYfhiRWfWY = false;}
      if(FsjMsBMFJt == true){FsjMsBMFJt = false;}
      if(qegNTiDUPj == true){qegNTiDUPj = false;}
      if(usTtQGtlfO == true){usTtQGtlfO = false;}
      if(cLwwdVMiAk == true){cLwwdVMiAk = false;}
      if(WqcaWhrRNA == true){WqcaWhrRNA = false;}
      if(OBQldLZpwm == true){OBQldLZpwm = false;}
      if(HZYuQfikjy == true){HZYuQfikjy = false;}
      if(VUUdNDQsWh == true){VUUdNDQsWh = false;}
      if(ObYfAatJRR == true){ObYfAatJRR = false;}
      if(uWlMdxRgJq == true){uWlMdxRgJq = false;}
      if(zGhPdsgmYZ == true){zGhPdsgmYZ = false;}
      if(ugTOYeBsup == true){ugTOYeBsup = false;}
      if(kYSRCzhHzQ == true){kYSRCzhHzQ = false;}
      if(liiehHsICG == true){liiehHsICG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OKMMGYVFFT
{ 
  void WmJWdnEYse()
  { 
      bool lUmyMYFfYH = false;
      bool idZNzPJZzC = false;
      bool AqlfZhyASF = false;
      bool hDjTYOcJXi = false;
      bool iEBqdJdubd = false;
      bool mCStTuiGXd = false;
      bool ZFNSYfsGok = false;
      bool lABQTwotCQ = false;
      bool DDXoSfjpzd = false;
      bool eWksIdphSx = false;
      bool PXGqqmACaX = false;
      bool FoDGZWgYAs = false;
      bool uDGKFPOHHo = false;
      bool FHbFAfwgxe = false;
      bool ehObYpSeSl = false;
      bool xRgYBMRula = false;
      bool YstlSxMyFt = false;
      bool ZAaVNNoelO = false;
      bool wjnVrmZCDn = false;
      bool NBtWGlmcIa = false;
      string reCHsdBhOy;
      string AsorciLPjr;
      string pZMWeutrHX;
      string eVdNhqlUWq;
      string fwTNrOLRXV;
      string TenIIRSfbx;
      string iJZpSePbJl;
      string wpsrLtFydQ;
      string jbTkDAhVEQ;
      string XGrZHWWduN;
      string yjIlZdkuwO;
      string LUBLNHonlS;
      string wtXsNoxTko;
      string WbDQRzTgLZ;
      string OlYoEDFgLA;
      string ghrcREMOXj;
      string fRKHqjRksN;
      string mHcLDJUhnK;
      string jQHkHojayN;
      string mEIbsxbRxU;
      if(reCHsdBhOy == yjIlZdkuwO){lUmyMYFfYH = true;}
      else if(yjIlZdkuwO == reCHsdBhOy){PXGqqmACaX = true;}
      if(AsorciLPjr == LUBLNHonlS){idZNzPJZzC = true;}
      else if(LUBLNHonlS == AsorciLPjr){FoDGZWgYAs = true;}
      if(pZMWeutrHX == wtXsNoxTko){AqlfZhyASF = true;}
      else if(wtXsNoxTko == pZMWeutrHX){uDGKFPOHHo = true;}
      if(eVdNhqlUWq == WbDQRzTgLZ){hDjTYOcJXi = true;}
      else if(WbDQRzTgLZ == eVdNhqlUWq){FHbFAfwgxe = true;}
      if(fwTNrOLRXV == OlYoEDFgLA){iEBqdJdubd = true;}
      else if(OlYoEDFgLA == fwTNrOLRXV){ehObYpSeSl = true;}
      if(TenIIRSfbx == ghrcREMOXj){mCStTuiGXd = true;}
      else if(ghrcREMOXj == TenIIRSfbx){xRgYBMRula = true;}
      if(iJZpSePbJl == fRKHqjRksN){ZFNSYfsGok = true;}
      else if(fRKHqjRksN == iJZpSePbJl){YstlSxMyFt = true;}
      if(wpsrLtFydQ == mHcLDJUhnK){lABQTwotCQ = true;}
      if(jbTkDAhVEQ == jQHkHojayN){DDXoSfjpzd = true;}
      if(XGrZHWWduN == mEIbsxbRxU){eWksIdphSx = true;}
      while(mHcLDJUhnK == wpsrLtFydQ){ZAaVNNoelO = true;}
      while(jQHkHojayN == jQHkHojayN){wjnVrmZCDn = true;}
      while(mEIbsxbRxU == mEIbsxbRxU){NBtWGlmcIa = true;}
      if(lUmyMYFfYH == true){lUmyMYFfYH = false;}
      if(idZNzPJZzC == true){idZNzPJZzC = false;}
      if(AqlfZhyASF == true){AqlfZhyASF = false;}
      if(hDjTYOcJXi == true){hDjTYOcJXi = false;}
      if(iEBqdJdubd == true){iEBqdJdubd = false;}
      if(mCStTuiGXd == true){mCStTuiGXd = false;}
      if(ZFNSYfsGok == true){ZFNSYfsGok = false;}
      if(lABQTwotCQ == true){lABQTwotCQ = false;}
      if(DDXoSfjpzd == true){DDXoSfjpzd = false;}
      if(eWksIdphSx == true){eWksIdphSx = false;}
      if(PXGqqmACaX == true){PXGqqmACaX = false;}
      if(FoDGZWgYAs == true){FoDGZWgYAs = false;}
      if(uDGKFPOHHo == true){uDGKFPOHHo = false;}
      if(FHbFAfwgxe == true){FHbFAfwgxe = false;}
      if(ehObYpSeSl == true){ehObYpSeSl = false;}
      if(xRgYBMRula == true){xRgYBMRula = false;}
      if(YstlSxMyFt == true){YstlSxMyFt = false;}
      if(ZAaVNNoelO == true){ZAaVNNoelO = false;}
      if(wjnVrmZCDn == true){wjnVrmZCDn = false;}
      if(NBtWGlmcIa == true){NBtWGlmcIa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DIXQDJMYTA
{ 
  void wGCrztogBY()
  { 
      bool FhXpkmVTxk = false;
      bool ZFBzkMatEl = false;
      bool sidqHIuIXm = false;
      bool iZTNtIwoht = false;
      bool YwRgDAtBRr = false;
      bool KZudcWEfhc = false;
      bool qNuJCAlmEb = false;
      bool QkMJMxQwnG = false;
      bool NtqebIdojX = false;
      bool EPGFDKAIeD = false;
      bool OHwobYNlQf = false;
      bool FHrbOwWPgs = false;
      bool VwCfWAeHFB = false;
      bool wIRkqGxBDD = false;
      bool uqYESwXepG = false;
      bool nkakgSEPSb = false;
      bool tGfOjwoHjI = false;
      bool yUMdyeWyNZ = false;
      bool czQzNKhgEX = false;
      bool BgiaJoKJTV = false;
      string YMzotdEGYM;
      string QiENnhlcna;
      string qdFJAWFDld;
      string PUjQutZgiA;
      string fqGiYKHUyH;
      string yiMwJtGonW;
      string XBUtxwzmSs;
      string HFtmtzXWko;
      string OkEeegImHB;
      string njrLceWLlc;
      string LUCEzsoYBJ;
      string ViEzHmwoOQ;
      string mLfQFWMiKP;
      string cMkHdthAel;
      string qikxfEesDp;
      string igwVoAnlzc;
      string fGOkgJywUN;
      string EwKcYDZikA;
      string qTeTguPPSd;
      string FwACFkUAPW;
      if(YMzotdEGYM == LUCEzsoYBJ){FhXpkmVTxk = true;}
      else if(LUCEzsoYBJ == YMzotdEGYM){OHwobYNlQf = true;}
      if(QiENnhlcna == ViEzHmwoOQ){ZFBzkMatEl = true;}
      else if(ViEzHmwoOQ == QiENnhlcna){FHrbOwWPgs = true;}
      if(qdFJAWFDld == mLfQFWMiKP){sidqHIuIXm = true;}
      else if(mLfQFWMiKP == qdFJAWFDld){VwCfWAeHFB = true;}
      if(PUjQutZgiA == cMkHdthAel){iZTNtIwoht = true;}
      else if(cMkHdthAel == PUjQutZgiA){wIRkqGxBDD = true;}
      if(fqGiYKHUyH == qikxfEesDp){YwRgDAtBRr = true;}
      else if(qikxfEesDp == fqGiYKHUyH){uqYESwXepG = true;}
      if(yiMwJtGonW == igwVoAnlzc){KZudcWEfhc = true;}
      else if(igwVoAnlzc == yiMwJtGonW){nkakgSEPSb = true;}
      if(XBUtxwzmSs == fGOkgJywUN){qNuJCAlmEb = true;}
      else if(fGOkgJywUN == XBUtxwzmSs){tGfOjwoHjI = true;}
      if(HFtmtzXWko == EwKcYDZikA){QkMJMxQwnG = true;}
      if(OkEeegImHB == qTeTguPPSd){NtqebIdojX = true;}
      if(njrLceWLlc == FwACFkUAPW){EPGFDKAIeD = true;}
      while(EwKcYDZikA == HFtmtzXWko){yUMdyeWyNZ = true;}
      while(qTeTguPPSd == qTeTguPPSd){czQzNKhgEX = true;}
      while(FwACFkUAPW == FwACFkUAPW){BgiaJoKJTV = true;}
      if(FhXpkmVTxk == true){FhXpkmVTxk = false;}
      if(ZFBzkMatEl == true){ZFBzkMatEl = false;}
      if(sidqHIuIXm == true){sidqHIuIXm = false;}
      if(iZTNtIwoht == true){iZTNtIwoht = false;}
      if(YwRgDAtBRr == true){YwRgDAtBRr = false;}
      if(KZudcWEfhc == true){KZudcWEfhc = false;}
      if(qNuJCAlmEb == true){qNuJCAlmEb = false;}
      if(QkMJMxQwnG == true){QkMJMxQwnG = false;}
      if(NtqebIdojX == true){NtqebIdojX = false;}
      if(EPGFDKAIeD == true){EPGFDKAIeD = false;}
      if(OHwobYNlQf == true){OHwobYNlQf = false;}
      if(FHrbOwWPgs == true){FHrbOwWPgs = false;}
      if(VwCfWAeHFB == true){VwCfWAeHFB = false;}
      if(wIRkqGxBDD == true){wIRkqGxBDD = false;}
      if(uqYESwXepG == true){uqYESwXepG = false;}
      if(nkakgSEPSb == true){nkakgSEPSb = false;}
      if(tGfOjwoHjI == true){tGfOjwoHjI = false;}
      if(yUMdyeWyNZ == true){yUMdyeWyNZ = false;}
      if(czQzNKhgEX == true){czQzNKhgEX = false;}
      if(BgiaJoKJTV == true){BgiaJoKJTV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WVXAVAXJSP
{ 
  void iVVPZGVyzu()
  { 
      bool exWyMrLmHy = false;
      bool LEhYQFdGkF = false;
      bool rhYiMZpCDX = false;
      bool zNUfYrAPXE = false;
      bool BqRlXujTNb = false;
      bool hJSFlwYmkl = false;
      bool CIijyxjCzX = false;
      bool EOigEBPlKQ = false;
      bool pVoapouOsb = false;
      bool TNdkCrHhna = false;
      bool LgUpXSakBk = false;
      bool glcTwfTHsI = false;
      bool CUJWDqkxeM = false;
      bool tgyjFJByDW = false;
      bool OJNIugjJoV = false;
      bool XzoeXpWxlg = false;
      bool hdGnqznrOm = false;
      bool eVEWtrHBbW = false;
      bool GaIIourSLO = false;
      bool lDMWojCYRu = false;
      string PFozcUOIMc;
      string jFNtmWZdXm;
      string mairZuBQBT;
      string UTHyLiLssa;
      string fTIlEeLlYN;
      string VBdNsnVwYh;
      string SyGrHPyPhD;
      string LfjxGTRwnt;
      string iOrnyTpsEX;
      string MOTKHhMQen;
      string gwDUCoQgGZ;
      string WZIezDGSsm;
      string ZEKKqwMYoY;
      string GARzMlLWkJ;
      string DIldAmGoLE;
      string btWqOckscG;
      string cqqhSVHISN;
      string rihjjQRfKE;
      string pXNjwMdZji;
      string ARsegLQELe;
      if(PFozcUOIMc == gwDUCoQgGZ){exWyMrLmHy = true;}
      else if(gwDUCoQgGZ == PFozcUOIMc){LgUpXSakBk = true;}
      if(jFNtmWZdXm == WZIezDGSsm){LEhYQFdGkF = true;}
      else if(WZIezDGSsm == jFNtmWZdXm){glcTwfTHsI = true;}
      if(mairZuBQBT == ZEKKqwMYoY){rhYiMZpCDX = true;}
      else if(ZEKKqwMYoY == mairZuBQBT){CUJWDqkxeM = true;}
      if(UTHyLiLssa == GARzMlLWkJ){zNUfYrAPXE = true;}
      else if(GARzMlLWkJ == UTHyLiLssa){tgyjFJByDW = true;}
      if(fTIlEeLlYN == DIldAmGoLE){BqRlXujTNb = true;}
      else if(DIldAmGoLE == fTIlEeLlYN){OJNIugjJoV = true;}
      if(VBdNsnVwYh == btWqOckscG){hJSFlwYmkl = true;}
      else if(btWqOckscG == VBdNsnVwYh){XzoeXpWxlg = true;}
      if(SyGrHPyPhD == cqqhSVHISN){CIijyxjCzX = true;}
      else if(cqqhSVHISN == SyGrHPyPhD){hdGnqznrOm = true;}
      if(LfjxGTRwnt == rihjjQRfKE){EOigEBPlKQ = true;}
      if(iOrnyTpsEX == pXNjwMdZji){pVoapouOsb = true;}
      if(MOTKHhMQen == ARsegLQELe){TNdkCrHhna = true;}
      while(rihjjQRfKE == LfjxGTRwnt){eVEWtrHBbW = true;}
      while(pXNjwMdZji == pXNjwMdZji){GaIIourSLO = true;}
      while(ARsegLQELe == ARsegLQELe){lDMWojCYRu = true;}
      if(exWyMrLmHy == true){exWyMrLmHy = false;}
      if(LEhYQFdGkF == true){LEhYQFdGkF = false;}
      if(rhYiMZpCDX == true){rhYiMZpCDX = false;}
      if(zNUfYrAPXE == true){zNUfYrAPXE = false;}
      if(BqRlXujTNb == true){BqRlXujTNb = false;}
      if(hJSFlwYmkl == true){hJSFlwYmkl = false;}
      if(CIijyxjCzX == true){CIijyxjCzX = false;}
      if(EOigEBPlKQ == true){EOigEBPlKQ = false;}
      if(pVoapouOsb == true){pVoapouOsb = false;}
      if(TNdkCrHhna == true){TNdkCrHhna = false;}
      if(LgUpXSakBk == true){LgUpXSakBk = false;}
      if(glcTwfTHsI == true){glcTwfTHsI = false;}
      if(CUJWDqkxeM == true){CUJWDqkxeM = false;}
      if(tgyjFJByDW == true){tgyjFJByDW = false;}
      if(OJNIugjJoV == true){OJNIugjJoV = false;}
      if(XzoeXpWxlg == true){XzoeXpWxlg = false;}
      if(hdGnqznrOm == true){hdGnqznrOm = false;}
      if(eVEWtrHBbW == true){eVEWtrHBbW = false;}
      if(GaIIourSLO == true){GaIIourSLO = false;}
      if(lDMWojCYRu == true){lDMWojCYRu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DIGUQXSXDW
{ 
  void QnaxsktaDK()
  { 
      bool qlcoAkhDqx = false;
      bool TaaCSZMlKg = false;
      bool huMItsKMux = false;
      bool zGnizIcInD = false;
      bool XxicwhmHQS = false;
      bool mskubuYUtH = false;
      bool ZUHtxMlrDK = false;
      bool wDxHJkMiLL = false;
      bool GCwcJGVsGE = false;
      bool iINgcDonej = false;
      bool utEGVjwdlq = false;
      bool hoIiBWYejq = false;
      bool qskzanoQdG = false;
      bool uYDaPLyoGZ = false;
      bool KrHPVszeeG = false;
      bool dJEnrCJEeh = false;
      bool tezeuJkhSp = false;
      bool YiYJgzkUch = false;
      bool nJkXbkUPhN = false;
      bool BsKXferbTM = false;
      string DSyuOpaPxP;
      string IFzLxFJUUj;
      string DbWrXeKzsX;
      string ytOZzuVlgb;
      string HtdMbNBTyP;
      string LnQXibwGXi;
      string eaVYQOpZLC;
      string iWnrbJyKPK;
      string dpAcMKdqpX;
      string yPOxwgXEuN;
      string WbIwgnAXuZ;
      string ckpMFoZsMG;
      string kzinDTIpwu;
      string ksOCnChEwX;
      string JGwQtMYCrH;
      string GernbWsUsM;
      string fKaznjVmYD;
      string GVwnweDRsp;
      string tGxonGBaaQ;
      string JNKirzewcK;
      if(DSyuOpaPxP == WbIwgnAXuZ){qlcoAkhDqx = true;}
      else if(WbIwgnAXuZ == DSyuOpaPxP){utEGVjwdlq = true;}
      if(IFzLxFJUUj == ckpMFoZsMG){TaaCSZMlKg = true;}
      else if(ckpMFoZsMG == IFzLxFJUUj){hoIiBWYejq = true;}
      if(DbWrXeKzsX == kzinDTIpwu){huMItsKMux = true;}
      else if(kzinDTIpwu == DbWrXeKzsX){qskzanoQdG = true;}
      if(ytOZzuVlgb == ksOCnChEwX){zGnizIcInD = true;}
      else if(ksOCnChEwX == ytOZzuVlgb){uYDaPLyoGZ = true;}
      if(HtdMbNBTyP == JGwQtMYCrH){XxicwhmHQS = true;}
      else if(JGwQtMYCrH == HtdMbNBTyP){KrHPVszeeG = true;}
      if(LnQXibwGXi == GernbWsUsM){mskubuYUtH = true;}
      else if(GernbWsUsM == LnQXibwGXi){dJEnrCJEeh = true;}
      if(eaVYQOpZLC == fKaznjVmYD){ZUHtxMlrDK = true;}
      else if(fKaznjVmYD == eaVYQOpZLC){tezeuJkhSp = true;}
      if(iWnrbJyKPK == GVwnweDRsp){wDxHJkMiLL = true;}
      if(dpAcMKdqpX == tGxonGBaaQ){GCwcJGVsGE = true;}
      if(yPOxwgXEuN == JNKirzewcK){iINgcDonej = true;}
      while(GVwnweDRsp == iWnrbJyKPK){YiYJgzkUch = true;}
      while(tGxonGBaaQ == tGxonGBaaQ){nJkXbkUPhN = true;}
      while(JNKirzewcK == JNKirzewcK){BsKXferbTM = true;}
      if(qlcoAkhDqx == true){qlcoAkhDqx = false;}
      if(TaaCSZMlKg == true){TaaCSZMlKg = false;}
      if(huMItsKMux == true){huMItsKMux = false;}
      if(zGnizIcInD == true){zGnizIcInD = false;}
      if(XxicwhmHQS == true){XxicwhmHQS = false;}
      if(mskubuYUtH == true){mskubuYUtH = false;}
      if(ZUHtxMlrDK == true){ZUHtxMlrDK = false;}
      if(wDxHJkMiLL == true){wDxHJkMiLL = false;}
      if(GCwcJGVsGE == true){GCwcJGVsGE = false;}
      if(iINgcDonej == true){iINgcDonej = false;}
      if(utEGVjwdlq == true){utEGVjwdlq = false;}
      if(hoIiBWYejq == true){hoIiBWYejq = false;}
      if(qskzanoQdG == true){qskzanoQdG = false;}
      if(uYDaPLyoGZ == true){uYDaPLyoGZ = false;}
      if(KrHPVszeeG == true){KrHPVszeeG = false;}
      if(dJEnrCJEeh == true){dJEnrCJEeh = false;}
      if(tezeuJkhSp == true){tezeuJkhSp = false;}
      if(YiYJgzkUch == true){YiYJgzkUch = false;}
      if(nJkXbkUPhN == true){nJkXbkUPhN = false;}
      if(BsKXferbTM == true){BsKXferbTM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OLOWQXQLFD
{ 
  void PJiHOSeEGC()
  { 
      bool pqUlgYNCFE = false;
      bool lnzOOFtrEZ = false;
      bool MmJgjPLYJb = false;
      bool eNZQTtZmtQ = false;
      bool GdhrNshTwS = false;
      bool pYcVCDhnBQ = false;
      bool NnsdYYNhuT = false;
      bool eHymSiFRSq = false;
      bool hrbpkFkEOQ = false;
      bool MkkcDSjESo = false;
      bool eAXbmiaoCS = false;
      bool xQVKiULCrT = false;
      bool nISdHtVUjA = false;
      bool yBycLgTADC = false;
      bool euCuSuPath = false;
      bool GgMzBVgtTs = false;
      bool NFFBTwRryB = false;
      bool ALzpnsGXKL = false;
      bool dtaBtRnzbp = false;
      bool zZfKnYoBaW = false;
      string CKntTHFzXw;
      string ZXixyPkTdW;
      string ninGryNpLq;
      string gfUVmVgTgi;
      string nfZyaGjeeR;
      string QhUnTTWgBV;
      string sPngPsCNJb;
      string hQmuiIJoel;
      string NiLtZyKgBT;
      string zzSKoXqrih;
      string DWVCizuZFL;
      string KgCPIKDtHQ;
      string hVMpciybFK;
      string QQGwhqMIKZ;
      string DkapIRxCCe;
      string UwjSAgJfZA;
      string BSTttsaFgQ;
      string xuihMwtVgK;
      string luYapTfnwA;
      string ggiKYkRguP;
      if(CKntTHFzXw == DWVCizuZFL){pqUlgYNCFE = true;}
      else if(DWVCizuZFL == CKntTHFzXw){eAXbmiaoCS = true;}
      if(ZXixyPkTdW == KgCPIKDtHQ){lnzOOFtrEZ = true;}
      else if(KgCPIKDtHQ == ZXixyPkTdW){xQVKiULCrT = true;}
      if(ninGryNpLq == hVMpciybFK){MmJgjPLYJb = true;}
      else if(hVMpciybFK == ninGryNpLq){nISdHtVUjA = true;}
      if(gfUVmVgTgi == QQGwhqMIKZ){eNZQTtZmtQ = true;}
      else if(QQGwhqMIKZ == gfUVmVgTgi){yBycLgTADC = true;}
      if(nfZyaGjeeR == DkapIRxCCe){GdhrNshTwS = true;}
      else if(DkapIRxCCe == nfZyaGjeeR){euCuSuPath = true;}
      if(QhUnTTWgBV == UwjSAgJfZA){pYcVCDhnBQ = true;}
      else if(UwjSAgJfZA == QhUnTTWgBV){GgMzBVgtTs = true;}
      if(sPngPsCNJb == BSTttsaFgQ){NnsdYYNhuT = true;}
      else if(BSTttsaFgQ == sPngPsCNJb){NFFBTwRryB = true;}
      if(hQmuiIJoel == xuihMwtVgK){eHymSiFRSq = true;}
      if(NiLtZyKgBT == luYapTfnwA){hrbpkFkEOQ = true;}
      if(zzSKoXqrih == ggiKYkRguP){MkkcDSjESo = true;}
      while(xuihMwtVgK == hQmuiIJoel){ALzpnsGXKL = true;}
      while(luYapTfnwA == luYapTfnwA){dtaBtRnzbp = true;}
      while(ggiKYkRguP == ggiKYkRguP){zZfKnYoBaW = true;}
      if(pqUlgYNCFE == true){pqUlgYNCFE = false;}
      if(lnzOOFtrEZ == true){lnzOOFtrEZ = false;}
      if(MmJgjPLYJb == true){MmJgjPLYJb = false;}
      if(eNZQTtZmtQ == true){eNZQTtZmtQ = false;}
      if(GdhrNshTwS == true){GdhrNshTwS = false;}
      if(pYcVCDhnBQ == true){pYcVCDhnBQ = false;}
      if(NnsdYYNhuT == true){NnsdYYNhuT = false;}
      if(eHymSiFRSq == true){eHymSiFRSq = false;}
      if(hrbpkFkEOQ == true){hrbpkFkEOQ = false;}
      if(MkkcDSjESo == true){MkkcDSjESo = false;}
      if(eAXbmiaoCS == true){eAXbmiaoCS = false;}
      if(xQVKiULCrT == true){xQVKiULCrT = false;}
      if(nISdHtVUjA == true){nISdHtVUjA = false;}
      if(yBycLgTADC == true){yBycLgTADC = false;}
      if(euCuSuPath == true){euCuSuPath = false;}
      if(GgMzBVgtTs == true){GgMzBVgtTs = false;}
      if(NFFBTwRryB == true){NFFBTwRryB = false;}
      if(ALzpnsGXKL == true){ALzpnsGXKL = false;}
      if(dtaBtRnzbp == true){dtaBtRnzbp = false;}
      if(zZfKnYoBaW == true){zZfKnYoBaW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LSQPYHLJMM
{ 
  void zCFoBihmFC()
  { 
      bool GbedUrFhYz = false;
      bool JcCjPeNUqY = false;
      bool meHkWzkSRX = false;
      bool drCGACcaEG = false;
      bool HPXCIqnHAY = false;
      bool OqYJxaUsGV = false;
      bool GlQBVRawjN = false;
      bool CmQkQXGEcf = false;
      bool KcSrIlSrJY = false;
      bool giThzVzWgq = false;
      bool QrXlWbansY = false;
      bool UQQaKcTXri = false;
      bool yhmKgTShkt = false;
      bool YjWkPSFfVg = false;
      bool LdzjEQRsXV = false;
      bool CadxrhFMFD = false;
      bool IrCyAjsfLr = false;
      bool XmCLXTiCGQ = false;
      bool BZKOryFZrg = false;
      bool MrZSXTaBiT = false;
      string orkjFpoEGn;
      string TDytocwjaM;
      string pdBBcgXNlS;
      string BkZjVVXfQF;
      string KDHJVKgfyP;
      string uLALbKpiHX;
      string SbRmlhcNXT;
      string EPSVCmWrfS;
      string ArOWXokOIK;
      string enYslikTWm;
      string gSHeKesdIn;
      string nxCoXaMuOx;
      string xOFNnQqZjT;
      string CCVrkgjiLr;
      string wGFUVhliUK;
      string VoEYpSNsqt;
      string nStolkbJDp;
      string pdjWApIkqG;
      string dIEYyMywCS;
      string TqrQEcMQhk;
      if(orkjFpoEGn == gSHeKesdIn){GbedUrFhYz = true;}
      else if(gSHeKesdIn == orkjFpoEGn){QrXlWbansY = true;}
      if(TDytocwjaM == nxCoXaMuOx){JcCjPeNUqY = true;}
      else if(nxCoXaMuOx == TDytocwjaM){UQQaKcTXri = true;}
      if(pdBBcgXNlS == xOFNnQqZjT){meHkWzkSRX = true;}
      else if(xOFNnQqZjT == pdBBcgXNlS){yhmKgTShkt = true;}
      if(BkZjVVXfQF == CCVrkgjiLr){drCGACcaEG = true;}
      else if(CCVrkgjiLr == BkZjVVXfQF){YjWkPSFfVg = true;}
      if(KDHJVKgfyP == wGFUVhliUK){HPXCIqnHAY = true;}
      else if(wGFUVhliUK == KDHJVKgfyP){LdzjEQRsXV = true;}
      if(uLALbKpiHX == VoEYpSNsqt){OqYJxaUsGV = true;}
      else if(VoEYpSNsqt == uLALbKpiHX){CadxrhFMFD = true;}
      if(SbRmlhcNXT == nStolkbJDp){GlQBVRawjN = true;}
      else if(nStolkbJDp == SbRmlhcNXT){IrCyAjsfLr = true;}
      if(EPSVCmWrfS == pdjWApIkqG){CmQkQXGEcf = true;}
      if(ArOWXokOIK == dIEYyMywCS){KcSrIlSrJY = true;}
      if(enYslikTWm == TqrQEcMQhk){giThzVzWgq = true;}
      while(pdjWApIkqG == EPSVCmWrfS){XmCLXTiCGQ = true;}
      while(dIEYyMywCS == dIEYyMywCS){BZKOryFZrg = true;}
      while(TqrQEcMQhk == TqrQEcMQhk){MrZSXTaBiT = true;}
      if(GbedUrFhYz == true){GbedUrFhYz = false;}
      if(JcCjPeNUqY == true){JcCjPeNUqY = false;}
      if(meHkWzkSRX == true){meHkWzkSRX = false;}
      if(drCGACcaEG == true){drCGACcaEG = false;}
      if(HPXCIqnHAY == true){HPXCIqnHAY = false;}
      if(OqYJxaUsGV == true){OqYJxaUsGV = false;}
      if(GlQBVRawjN == true){GlQBVRawjN = false;}
      if(CmQkQXGEcf == true){CmQkQXGEcf = false;}
      if(KcSrIlSrJY == true){KcSrIlSrJY = false;}
      if(giThzVzWgq == true){giThzVzWgq = false;}
      if(QrXlWbansY == true){QrXlWbansY = false;}
      if(UQQaKcTXri == true){UQQaKcTXri = false;}
      if(yhmKgTShkt == true){yhmKgTShkt = false;}
      if(YjWkPSFfVg == true){YjWkPSFfVg = false;}
      if(LdzjEQRsXV == true){LdzjEQRsXV = false;}
      if(CadxrhFMFD == true){CadxrhFMFD = false;}
      if(IrCyAjsfLr == true){IrCyAjsfLr = false;}
      if(XmCLXTiCGQ == true){XmCLXTiCGQ = false;}
      if(BZKOryFZrg == true){BZKOryFZrg = false;}
      if(MrZSXTaBiT == true){MrZSXTaBiT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUHAKBOONP
{ 
  void dzfNjwwMnK()
  { 
      bool lOceDVbniO = false;
      bool UZPRoqxtpN = false;
      bool PYFZVjGHWM = false;
      bool rIWdoiUSGP = false;
      bool OMixnLkLHS = false;
      bool BTFXpNJDIS = false;
      bool PTQWWMClcF = false;
      bool WdnZzCoHkK = false;
      bool ztzDKYCzma = false;
      bool ZQKmAtwMaa = false;
      bool IyiBwXefXn = false;
      bool YBSySUUMLx = false;
      bool JDyCfFTBYE = false;
      bool GbgJBBLyHm = false;
      bool tWayBXyLTe = false;
      bool ZiBcQFzfVq = false;
      bool DdGShxTIwR = false;
      bool JWFYDmbAAH = false;
      bool GHgseWaDrw = false;
      bool BebQiPQHQE = false;
      string IZrzjRrZTi;
      string plMdySVlpB;
      string MBBQzFaMfo;
      string BwTrPIHepR;
      string tQejnRCUoc;
      string pabbYHXbAd;
      string qesegsSTOp;
      string KpwYHuVRbh;
      string CGWDzZUrTI;
      string jfeMZOWACt;
      string ziFzRAeCUc;
      string lGzSakIpfH;
      string YazGFdKiyr;
      string XUOhiTAXkz;
      string uRWqWdfMko;
      string GgUuVYizsn;
      string ouEbFQqRiG;
      string kjEgMGDIjb;
      string yxyJlqASMJ;
      string kAdxJzNulG;
      if(IZrzjRrZTi == ziFzRAeCUc){lOceDVbniO = true;}
      else if(ziFzRAeCUc == IZrzjRrZTi){IyiBwXefXn = true;}
      if(plMdySVlpB == lGzSakIpfH){UZPRoqxtpN = true;}
      else if(lGzSakIpfH == plMdySVlpB){YBSySUUMLx = true;}
      if(MBBQzFaMfo == YazGFdKiyr){PYFZVjGHWM = true;}
      else if(YazGFdKiyr == MBBQzFaMfo){JDyCfFTBYE = true;}
      if(BwTrPIHepR == XUOhiTAXkz){rIWdoiUSGP = true;}
      else if(XUOhiTAXkz == BwTrPIHepR){GbgJBBLyHm = true;}
      if(tQejnRCUoc == uRWqWdfMko){OMixnLkLHS = true;}
      else if(uRWqWdfMko == tQejnRCUoc){tWayBXyLTe = true;}
      if(pabbYHXbAd == GgUuVYizsn){BTFXpNJDIS = true;}
      else if(GgUuVYizsn == pabbYHXbAd){ZiBcQFzfVq = true;}
      if(qesegsSTOp == ouEbFQqRiG){PTQWWMClcF = true;}
      else if(ouEbFQqRiG == qesegsSTOp){DdGShxTIwR = true;}
      if(KpwYHuVRbh == kjEgMGDIjb){WdnZzCoHkK = true;}
      if(CGWDzZUrTI == yxyJlqASMJ){ztzDKYCzma = true;}
      if(jfeMZOWACt == kAdxJzNulG){ZQKmAtwMaa = true;}
      while(kjEgMGDIjb == KpwYHuVRbh){JWFYDmbAAH = true;}
      while(yxyJlqASMJ == yxyJlqASMJ){GHgseWaDrw = true;}
      while(kAdxJzNulG == kAdxJzNulG){BebQiPQHQE = true;}
      if(lOceDVbniO == true){lOceDVbniO = false;}
      if(UZPRoqxtpN == true){UZPRoqxtpN = false;}
      if(PYFZVjGHWM == true){PYFZVjGHWM = false;}
      if(rIWdoiUSGP == true){rIWdoiUSGP = false;}
      if(OMixnLkLHS == true){OMixnLkLHS = false;}
      if(BTFXpNJDIS == true){BTFXpNJDIS = false;}
      if(PTQWWMClcF == true){PTQWWMClcF = false;}
      if(WdnZzCoHkK == true){WdnZzCoHkK = false;}
      if(ztzDKYCzma == true){ztzDKYCzma = false;}
      if(ZQKmAtwMaa == true){ZQKmAtwMaa = false;}
      if(IyiBwXefXn == true){IyiBwXefXn = false;}
      if(YBSySUUMLx == true){YBSySUUMLx = false;}
      if(JDyCfFTBYE == true){JDyCfFTBYE = false;}
      if(GbgJBBLyHm == true){GbgJBBLyHm = false;}
      if(tWayBXyLTe == true){tWayBXyLTe = false;}
      if(ZiBcQFzfVq == true){ZiBcQFzfVq = false;}
      if(DdGShxTIwR == true){DdGShxTIwR = false;}
      if(JWFYDmbAAH == true){JWFYDmbAAH = false;}
      if(GHgseWaDrw == true){GHgseWaDrw = false;}
      if(BebQiPQHQE == true){BebQiPQHQE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KZBRRYFNVZ
{ 
  void kVsVKPPlzL()
  { 
      bool qDXAWHglKc = false;
      bool jQCfhwUzsk = false;
      bool ZwTXESGfQI = false;
      bool ZCkrKVAXfT = false;
      bool DRyCmtNFPJ = false;
      bool JkGbMtjAuD = false;
      bool AAVBDgfKVM = false;
      bool uwTZhIyRjK = false;
      bool FBQGynwJfP = false;
      bool lAbcSCuwzF = false;
      bool ODjDOMRgsD = false;
      bool wRPkyzjODO = false;
      bool kWdFZtTpGf = false;
      bool MBRduCQNrk = false;
      bool VPQbTTkqeS = false;
      bool SgsjUqYdcT = false;
      bool rbZMqtzkou = false;
      bool iVWSsUGCkG = false;
      bool IcLnNfIhJE = false;
      bool clkXrtpDjZ = false;
      string aHOuTQEyMx;
      string BrlapsYWlT;
      string HOipSCJpZY;
      string iDEFVhtEZr;
      string cStVjxdioj;
      string idEmFMYXcQ;
      string GOYmOxngFH;
      string zUxtpoUMFU;
      string YaBooEyQzJ;
      string IVbIkNsGHl;
      string JxdgjOgKwQ;
      string rLSHrfNixJ;
      string yWgwycsnIb;
      string uNFSLbxTFa;
      string WnTiQxDTQF;
      string AKJxmmPghH;
      string UrCUVdFzwQ;
      string isdWmKCyeB;
      string ZYXCajEIeX;
      string LPlxFekzNl;
      if(aHOuTQEyMx == JxdgjOgKwQ){qDXAWHglKc = true;}
      else if(JxdgjOgKwQ == aHOuTQEyMx){ODjDOMRgsD = true;}
      if(BrlapsYWlT == rLSHrfNixJ){jQCfhwUzsk = true;}
      else if(rLSHrfNixJ == BrlapsYWlT){wRPkyzjODO = true;}
      if(HOipSCJpZY == yWgwycsnIb){ZwTXESGfQI = true;}
      else if(yWgwycsnIb == HOipSCJpZY){kWdFZtTpGf = true;}
      if(iDEFVhtEZr == uNFSLbxTFa){ZCkrKVAXfT = true;}
      else if(uNFSLbxTFa == iDEFVhtEZr){MBRduCQNrk = true;}
      if(cStVjxdioj == WnTiQxDTQF){DRyCmtNFPJ = true;}
      else if(WnTiQxDTQF == cStVjxdioj){VPQbTTkqeS = true;}
      if(idEmFMYXcQ == AKJxmmPghH){JkGbMtjAuD = true;}
      else if(AKJxmmPghH == idEmFMYXcQ){SgsjUqYdcT = true;}
      if(GOYmOxngFH == UrCUVdFzwQ){AAVBDgfKVM = true;}
      else if(UrCUVdFzwQ == GOYmOxngFH){rbZMqtzkou = true;}
      if(zUxtpoUMFU == isdWmKCyeB){uwTZhIyRjK = true;}
      if(YaBooEyQzJ == ZYXCajEIeX){FBQGynwJfP = true;}
      if(IVbIkNsGHl == LPlxFekzNl){lAbcSCuwzF = true;}
      while(isdWmKCyeB == zUxtpoUMFU){iVWSsUGCkG = true;}
      while(ZYXCajEIeX == ZYXCajEIeX){IcLnNfIhJE = true;}
      while(LPlxFekzNl == LPlxFekzNl){clkXrtpDjZ = true;}
      if(qDXAWHglKc == true){qDXAWHglKc = false;}
      if(jQCfhwUzsk == true){jQCfhwUzsk = false;}
      if(ZwTXESGfQI == true){ZwTXESGfQI = false;}
      if(ZCkrKVAXfT == true){ZCkrKVAXfT = false;}
      if(DRyCmtNFPJ == true){DRyCmtNFPJ = false;}
      if(JkGbMtjAuD == true){JkGbMtjAuD = false;}
      if(AAVBDgfKVM == true){AAVBDgfKVM = false;}
      if(uwTZhIyRjK == true){uwTZhIyRjK = false;}
      if(FBQGynwJfP == true){FBQGynwJfP = false;}
      if(lAbcSCuwzF == true){lAbcSCuwzF = false;}
      if(ODjDOMRgsD == true){ODjDOMRgsD = false;}
      if(wRPkyzjODO == true){wRPkyzjODO = false;}
      if(kWdFZtTpGf == true){kWdFZtTpGf = false;}
      if(MBRduCQNrk == true){MBRduCQNrk = false;}
      if(VPQbTTkqeS == true){VPQbTTkqeS = false;}
      if(SgsjUqYdcT == true){SgsjUqYdcT = false;}
      if(rbZMqtzkou == true){rbZMqtzkou = false;}
      if(iVWSsUGCkG == true){iVWSsUGCkG = false;}
      if(IcLnNfIhJE == true){IcLnNfIhJE = false;}
      if(clkXrtpDjZ == true){clkXrtpDjZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KIISHVSFJM
{ 
  void tmfaRzHlVx()
  { 
      bool fmZnBbFmxN = false;
      bool htuAtNyQjY = false;
      bool dIjWENFPDo = false;
      bool KVFETGTShI = false;
      bool JCXWezDTUR = false;
      bool XCpEUWCDjm = false;
      bool WpiHCLoqfn = false;
      bool tfiaOajNrE = false;
      bool JltkRHfBix = false;
      bool DPhtlTSQTS = false;
      bool KMmgWqTOos = false;
      bool lnLecjuxpt = false;
      bool fmHijexnou = false;
      bool ITtYtxyNOZ = false;
      bool nQLoKOECQB = false;
      bool XUZYmWFEwr = false;
      bool teYskStmkf = false;
      bool lhiPGObRXU = false;
      bool atWmXmsVkW = false;
      bool qsQVfJqREr = false;
      string PTXORYkVXs;
      string uhYFbRJnQw;
      string VakNbqAOpz;
      string dioRlAMWkw;
      string QASLzPmkku;
      string zDSmKnhJla;
      string XVeXOMsHSa;
      string FmDUfVHZNM;
      string DOcuAaPBGy;
      string RDjJXtUuwm;
      string VeSJpLzxGo;
      string fHuZWJsjXm;
      string wqBUJBDsxl;
      string AMdapYwTEn;
      string bSuRRJHJmO;
      string BkWIqddxAn;
      string HFzUnTdUiy;
      string MYejLcwiCz;
      string ttGijPoUjM;
      string tyTPfVSZcy;
      if(PTXORYkVXs == VeSJpLzxGo){fmZnBbFmxN = true;}
      else if(VeSJpLzxGo == PTXORYkVXs){KMmgWqTOos = true;}
      if(uhYFbRJnQw == fHuZWJsjXm){htuAtNyQjY = true;}
      else if(fHuZWJsjXm == uhYFbRJnQw){lnLecjuxpt = true;}
      if(VakNbqAOpz == wqBUJBDsxl){dIjWENFPDo = true;}
      else if(wqBUJBDsxl == VakNbqAOpz){fmHijexnou = true;}
      if(dioRlAMWkw == AMdapYwTEn){KVFETGTShI = true;}
      else if(AMdapYwTEn == dioRlAMWkw){ITtYtxyNOZ = true;}
      if(QASLzPmkku == bSuRRJHJmO){JCXWezDTUR = true;}
      else if(bSuRRJHJmO == QASLzPmkku){nQLoKOECQB = true;}
      if(zDSmKnhJla == BkWIqddxAn){XCpEUWCDjm = true;}
      else if(BkWIqddxAn == zDSmKnhJla){XUZYmWFEwr = true;}
      if(XVeXOMsHSa == HFzUnTdUiy){WpiHCLoqfn = true;}
      else if(HFzUnTdUiy == XVeXOMsHSa){teYskStmkf = true;}
      if(FmDUfVHZNM == MYejLcwiCz){tfiaOajNrE = true;}
      if(DOcuAaPBGy == ttGijPoUjM){JltkRHfBix = true;}
      if(RDjJXtUuwm == tyTPfVSZcy){DPhtlTSQTS = true;}
      while(MYejLcwiCz == FmDUfVHZNM){lhiPGObRXU = true;}
      while(ttGijPoUjM == ttGijPoUjM){atWmXmsVkW = true;}
      while(tyTPfVSZcy == tyTPfVSZcy){qsQVfJqREr = true;}
      if(fmZnBbFmxN == true){fmZnBbFmxN = false;}
      if(htuAtNyQjY == true){htuAtNyQjY = false;}
      if(dIjWENFPDo == true){dIjWENFPDo = false;}
      if(KVFETGTShI == true){KVFETGTShI = false;}
      if(JCXWezDTUR == true){JCXWezDTUR = false;}
      if(XCpEUWCDjm == true){XCpEUWCDjm = false;}
      if(WpiHCLoqfn == true){WpiHCLoqfn = false;}
      if(tfiaOajNrE == true){tfiaOajNrE = false;}
      if(JltkRHfBix == true){JltkRHfBix = false;}
      if(DPhtlTSQTS == true){DPhtlTSQTS = false;}
      if(KMmgWqTOos == true){KMmgWqTOos = false;}
      if(lnLecjuxpt == true){lnLecjuxpt = false;}
      if(fmHijexnou == true){fmHijexnou = false;}
      if(ITtYtxyNOZ == true){ITtYtxyNOZ = false;}
      if(nQLoKOECQB == true){nQLoKOECQB = false;}
      if(XUZYmWFEwr == true){XUZYmWFEwr = false;}
      if(teYskStmkf == true){teYskStmkf = false;}
      if(lhiPGObRXU == true){lhiPGObRXU = false;}
      if(atWmXmsVkW == true){atWmXmsVkW = false;}
      if(qsQVfJqREr == true){qsQVfJqREr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HVFBFKTPLK
{ 
  void ObRxtVPWUi()
  { 
      bool dmBTtSKgQY = false;
      bool jHcBYyFaWb = false;
      bool GSMXHNbAuQ = false;
      bool eBSuUbVsDf = false;
      bool JLzELPHbBT = false;
      bool gpVmEKadMg = false;
      bool pKkAsioggx = false;
      bool cMWqStSILr = false;
      bool GzyaioeeqJ = false;
      bool BqfWozZyKc = false;
      bool ZZtEqUSeUJ = false;
      bool rRRTaqLKQE = false;
      bool EKpXukfACT = false;
      bool UTxiSfFtiO = false;
      bool VAJhRiZMwx = false;
      bool mOhGYOjWIG = false;
      bool oSbBoXUhBt = false;
      bool lRaCiDAIFL = false;
      bool LSDEgFlqKD = false;
      bool whkcZCXIst = false;
      string USKXiSUlpJ;
      string MpJeJhekuL;
      string ywiLQsftxe;
      string RTazTQTWgw;
      string hQJUCCuLEy;
      string YhNUjXizHp;
      string lZoKrsOJLr;
      string OIDzdglOIN;
      string yUpyGiFFOu;
      string gUOqJHbzcJ;
      string mkALiPeOqC;
      string lUpsrRjpEI;
      string mItPLtsLoV;
      string FmkzZNTdPp;
      string EpOMJMdVzq;
      string XkuUVdpjAo;
      string WSYUwyipTe;
      string xFaODwthGy;
      string PXMyyUrQdu;
      string WjdaSlRsPK;
      if(USKXiSUlpJ == mkALiPeOqC){dmBTtSKgQY = true;}
      else if(mkALiPeOqC == USKXiSUlpJ){ZZtEqUSeUJ = true;}
      if(MpJeJhekuL == lUpsrRjpEI){jHcBYyFaWb = true;}
      else if(lUpsrRjpEI == MpJeJhekuL){rRRTaqLKQE = true;}
      if(ywiLQsftxe == mItPLtsLoV){GSMXHNbAuQ = true;}
      else if(mItPLtsLoV == ywiLQsftxe){EKpXukfACT = true;}
      if(RTazTQTWgw == FmkzZNTdPp){eBSuUbVsDf = true;}
      else if(FmkzZNTdPp == RTazTQTWgw){UTxiSfFtiO = true;}
      if(hQJUCCuLEy == EpOMJMdVzq){JLzELPHbBT = true;}
      else if(EpOMJMdVzq == hQJUCCuLEy){VAJhRiZMwx = true;}
      if(YhNUjXizHp == XkuUVdpjAo){gpVmEKadMg = true;}
      else if(XkuUVdpjAo == YhNUjXizHp){mOhGYOjWIG = true;}
      if(lZoKrsOJLr == WSYUwyipTe){pKkAsioggx = true;}
      else if(WSYUwyipTe == lZoKrsOJLr){oSbBoXUhBt = true;}
      if(OIDzdglOIN == xFaODwthGy){cMWqStSILr = true;}
      if(yUpyGiFFOu == PXMyyUrQdu){GzyaioeeqJ = true;}
      if(gUOqJHbzcJ == WjdaSlRsPK){BqfWozZyKc = true;}
      while(xFaODwthGy == OIDzdglOIN){lRaCiDAIFL = true;}
      while(PXMyyUrQdu == PXMyyUrQdu){LSDEgFlqKD = true;}
      while(WjdaSlRsPK == WjdaSlRsPK){whkcZCXIst = true;}
      if(dmBTtSKgQY == true){dmBTtSKgQY = false;}
      if(jHcBYyFaWb == true){jHcBYyFaWb = false;}
      if(GSMXHNbAuQ == true){GSMXHNbAuQ = false;}
      if(eBSuUbVsDf == true){eBSuUbVsDf = false;}
      if(JLzELPHbBT == true){JLzELPHbBT = false;}
      if(gpVmEKadMg == true){gpVmEKadMg = false;}
      if(pKkAsioggx == true){pKkAsioggx = false;}
      if(cMWqStSILr == true){cMWqStSILr = false;}
      if(GzyaioeeqJ == true){GzyaioeeqJ = false;}
      if(BqfWozZyKc == true){BqfWozZyKc = false;}
      if(ZZtEqUSeUJ == true){ZZtEqUSeUJ = false;}
      if(rRRTaqLKQE == true){rRRTaqLKQE = false;}
      if(EKpXukfACT == true){EKpXukfACT = false;}
      if(UTxiSfFtiO == true){UTxiSfFtiO = false;}
      if(VAJhRiZMwx == true){VAJhRiZMwx = false;}
      if(mOhGYOjWIG == true){mOhGYOjWIG = false;}
      if(oSbBoXUhBt == true){oSbBoXUhBt = false;}
      if(lRaCiDAIFL == true){lRaCiDAIFL = false;}
      if(LSDEgFlqKD == true){LSDEgFlqKD = false;}
      if(whkcZCXIst == true){whkcZCXIst = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TSIDYPGMQO
{ 
  void pddeHwFAde()
  { 
      bool ldRnPTSyqZ = false;
      bool BfXZTuofNT = false;
      bool gFOLnPmrdD = false;
      bool ZhBTncMgOD = false;
      bool aRKjbQbDxR = false;
      bool xYMhofPGzA = false;
      bool fZTmzTeDlp = false;
      bool iHQKrPueiX = false;
      bool njuMGBUSdH = false;
      bool NFhOWBxWjH = false;
      bool kXQHhpHCoZ = false;
      bool kjXaLweHgy = false;
      bool yLYecdZCnq = false;
      bool RXtblPSmeQ = false;
      bool sScEWchGCZ = false;
      bool WpplIYyleE = false;
      bool PEOyHNpwou = false;
      bool cqcQEfiUHz = false;
      bool wSzNUbgISM = false;
      bool RgIZAnEdxJ = false;
      string yPmMyKZwHf;
      string CFEfypxYtO;
      string NVQnSAsePe;
      string qYhlynocna;
      string aLxKbBTGel;
      string fooelbzztx;
      string QufcodWSgJ;
      string AUkTmCYGMR;
      string gmzdyBjDzW;
      string npipJfeTUy;
      string dBYVkLEUqj;
      string CsmbQduCdm;
      string sTSKUKktKH;
      string WFkNmeNdrm;
      string wOLPTuDGYf;
      string jcohEKiOAa;
      string ZKKjNxIYnk;
      string PQKqpdICpZ;
      string HeUeWtPCJc;
      string wzdRMlEaBW;
      if(yPmMyKZwHf == dBYVkLEUqj){ldRnPTSyqZ = true;}
      else if(dBYVkLEUqj == yPmMyKZwHf){kXQHhpHCoZ = true;}
      if(CFEfypxYtO == CsmbQduCdm){BfXZTuofNT = true;}
      else if(CsmbQduCdm == CFEfypxYtO){kjXaLweHgy = true;}
      if(NVQnSAsePe == sTSKUKktKH){gFOLnPmrdD = true;}
      else if(sTSKUKktKH == NVQnSAsePe){yLYecdZCnq = true;}
      if(qYhlynocna == WFkNmeNdrm){ZhBTncMgOD = true;}
      else if(WFkNmeNdrm == qYhlynocna){RXtblPSmeQ = true;}
      if(aLxKbBTGel == wOLPTuDGYf){aRKjbQbDxR = true;}
      else if(wOLPTuDGYf == aLxKbBTGel){sScEWchGCZ = true;}
      if(fooelbzztx == jcohEKiOAa){xYMhofPGzA = true;}
      else if(jcohEKiOAa == fooelbzztx){WpplIYyleE = true;}
      if(QufcodWSgJ == ZKKjNxIYnk){fZTmzTeDlp = true;}
      else if(ZKKjNxIYnk == QufcodWSgJ){PEOyHNpwou = true;}
      if(AUkTmCYGMR == PQKqpdICpZ){iHQKrPueiX = true;}
      if(gmzdyBjDzW == HeUeWtPCJc){njuMGBUSdH = true;}
      if(npipJfeTUy == wzdRMlEaBW){NFhOWBxWjH = true;}
      while(PQKqpdICpZ == AUkTmCYGMR){cqcQEfiUHz = true;}
      while(HeUeWtPCJc == HeUeWtPCJc){wSzNUbgISM = true;}
      while(wzdRMlEaBW == wzdRMlEaBW){RgIZAnEdxJ = true;}
      if(ldRnPTSyqZ == true){ldRnPTSyqZ = false;}
      if(BfXZTuofNT == true){BfXZTuofNT = false;}
      if(gFOLnPmrdD == true){gFOLnPmrdD = false;}
      if(ZhBTncMgOD == true){ZhBTncMgOD = false;}
      if(aRKjbQbDxR == true){aRKjbQbDxR = false;}
      if(xYMhofPGzA == true){xYMhofPGzA = false;}
      if(fZTmzTeDlp == true){fZTmzTeDlp = false;}
      if(iHQKrPueiX == true){iHQKrPueiX = false;}
      if(njuMGBUSdH == true){njuMGBUSdH = false;}
      if(NFhOWBxWjH == true){NFhOWBxWjH = false;}
      if(kXQHhpHCoZ == true){kXQHhpHCoZ = false;}
      if(kjXaLweHgy == true){kjXaLweHgy = false;}
      if(yLYecdZCnq == true){yLYecdZCnq = false;}
      if(RXtblPSmeQ == true){RXtblPSmeQ = false;}
      if(sScEWchGCZ == true){sScEWchGCZ = false;}
      if(WpplIYyleE == true){WpplIYyleE = false;}
      if(PEOyHNpwou == true){PEOyHNpwou = false;}
      if(cqcQEfiUHz == true){cqcQEfiUHz = false;}
      if(wSzNUbgISM == true){wSzNUbgISM = false;}
      if(RgIZAnEdxJ == true){RgIZAnEdxJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCOQZCREBP
{ 
  void dksxfsoJOd()
  { 
      bool mFsfAmJTwj = false;
      bool pYiTjotKlM = false;
      bool rFBoLIcyAc = false;
      bool anSanKEyUX = false;
      bool eTHyomyCDp = false;
      bool rJwSKhDDUr = false;
      bool KKTTIBGHfZ = false;
      bool kwpOgYyDzX = false;
      bool JatJjRrzPF = false;
      bool GAccNTAmom = false;
      bool fpVdFwThkl = false;
      bool iADwhiPKiq = false;
      bool JHqZTkSMBN = false;
      bool YKOMrTEQDn = false;
      bool xJNdWGwgud = false;
      bool DoExdYywKU = false;
      bool dGgXMXkqDN = false;
      bool dzGutztNCM = false;
      bool nkRWJiGQhT = false;
      bool UHGiJpcoQy = false;
      string MXlfBWIPWT;
      string BFedEOpLNK;
      string LFpBGBQFrE;
      string YPZZLFXBNd;
      string HyRjMwKtSx;
      string mFYyCHgkYA;
      string FDXRuleESy;
      string qnxiCMmGnK;
      string pVluRTpbXD;
      string YlcNYEZzoa;
      string QFbUFyHpuo;
      string TaxOJiQczb;
      string uDgOYFLiKy;
      string mmQNsktRoS;
      string LAfhjxoNEo;
      string mxAMeNXNuA;
      string mYfxCfJjUX;
      string ozmfPuWyeb;
      string PxdULomEhf;
      string MgVnfmThfD;
      if(MXlfBWIPWT == QFbUFyHpuo){mFsfAmJTwj = true;}
      else if(QFbUFyHpuo == MXlfBWIPWT){fpVdFwThkl = true;}
      if(BFedEOpLNK == TaxOJiQczb){pYiTjotKlM = true;}
      else if(TaxOJiQczb == BFedEOpLNK){iADwhiPKiq = true;}
      if(LFpBGBQFrE == uDgOYFLiKy){rFBoLIcyAc = true;}
      else if(uDgOYFLiKy == LFpBGBQFrE){JHqZTkSMBN = true;}
      if(YPZZLFXBNd == mmQNsktRoS){anSanKEyUX = true;}
      else if(mmQNsktRoS == YPZZLFXBNd){YKOMrTEQDn = true;}
      if(HyRjMwKtSx == LAfhjxoNEo){eTHyomyCDp = true;}
      else if(LAfhjxoNEo == HyRjMwKtSx){xJNdWGwgud = true;}
      if(mFYyCHgkYA == mxAMeNXNuA){rJwSKhDDUr = true;}
      else if(mxAMeNXNuA == mFYyCHgkYA){DoExdYywKU = true;}
      if(FDXRuleESy == mYfxCfJjUX){KKTTIBGHfZ = true;}
      else if(mYfxCfJjUX == FDXRuleESy){dGgXMXkqDN = true;}
      if(qnxiCMmGnK == ozmfPuWyeb){kwpOgYyDzX = true;}
      if(pVluRTpbXD == PxdULomEhf){JatJjRrzPF = true;}
      if(YlcNYEZzoa == MgVnfmThfD){GAccNTAmom = true;}
      while(ozmfPuWyeb == qnxiCMmGnK){dzGutztNCM = true;}
      while(PxdULomEhf == PxdULomEhf){nkRWJiGQhT = true;}
      while(MgVnfmThfD == MgVnfmThfD){UHGiJpcoQy = true;}
      if(mFsfAmJTwj == true){mFsfAmJTwj = false;}
      if(pYiTjotKlM == true){pYiTjotKlM = false;}
      if(rFBoLIcyAc == true){rFBoLIcyAc = false;}
      if(anSanKEyUX == true){anSanKEyUX = false;}
      if(eTHyomyCDp == true){eTHyomyCDp = false;}
      if(rJwSKhDDUr == true){rJwSKhDDUr = false;}
      if(KKTTIBGHfZ == true){KKTTIBGHfZ = false;}
      if(kwpOgYyDzX == true){kwpOgYyDzX = false;}
      if(JatJjRrzPF == true){JatJjRrzPF = false;}
      if(GAccNTAmom == true){GAccNTAmom = false;}
      if(fpVdFwThkl == true){fpVdFwThkl = false;}
      if(iADwhiPKiq == true){iADwhiPKiq = false;}
      if(JHqZTkSMBN == true){JHqZTkSMBN = false;}
      if(YKOMrTEQDn == true){YKOMrTEQDn = false;}
      if(xJNdWGwgud == true){xJNdWGwgud = false;}
      if(DoExdYywKU == true){DoExdYywKU = false;}
      if(dGgXMXkqDN == true){dGgXMXkqDN = false;}
      if(dzGutztNCM == true){dzGutztNCM = false;}
      if(nkRWJiGQhT == true){nkRWJiGQhT = false;}
      if(UHGiJpcoQy == true){UHGiJpcoQy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIHVDOCQFU
{ 
  void cnIwzYcGQC()
  { 
      bool ZfHNsAEUcm = false;
      bool GLfIRcNIVl = false;
      bool gqpQznVUwC = false;
      bool yPrADMfEZk = false;
      bool PGkStDPoMq = false;
      bool yEpRDhoqOF = false;
      bool djYZoqTeFF = false;
      bool xJijWaGXVu = false;
      bool XgIEEsYaxU = false;
      bool WopTGegKdD = false;
      bool jjjHtoUFub = false;
      bool bRUShxaTVu = false;
      bool RshjhHTPdq = false;
      bool sutRKmwAKO = false;
      bool YSeUrFUWlI = false;
      bool ENnhlqBAYl = false;
      bool VFbDhgXCIt = false;
      bool AZIGWyNNqc = false;
      bool mxcUmfGLeT = false;
      bool kwbYsSqalL = false;
      string ixfqYDFMPZ;
      string aGefGqqCCr;
      string RMeWXxyVDs;
      string BKcjlIoxre;
      string JBKXQHJori;
      string ZjuwuWRITa;
      string FiIVYQcuty;
      string CsKWhQBGGP;
      string mIdUSROgnP;
      string pfdQZarnzA;
      string eOusfgZYNd;
      string VLCDnwFnCG;
      string BuGeHVOtwG;
      string XMGFkYMjnl;
      string qpSJsecZbc;
      string VEkrziIQlK;
      string RebGGIFxSO;
      string jUzQPLbwkc;
      string rnRSkTaNGB;
      string PwydUMNMDj;
      if(ixfqYDFMPZ == eOusfgZYNd){ZfHNsAEUcm = true;}
      else if(eOusfgZYNd == ixfqYDFMPZ){jjjHtoUFub = true;}
      if(aGefGqqCCr == VLCDnwFnCG){GLfIRcNIVl = true;}
      else if(VLCDnwFnCG == aGefGqqCCr){bRUShxaTVu = true;}
      if(RMeWXxyVDs == BuGeHVOtwG){gqpQznVUwC = true;}
      else if(BuGeHVOtwG == RMeWXxyVDs){RshjhHTPdq = true;}
      if(BKcjlIoxre == XMGFkYMjnl){yPrADMfEZk = true;}
      else if(XMGFkYMjnl == BKcjlIoxre){sutRKmwAKO = true;}
      if(JBKXQHJori == qpSJsecZbc){PGkStDPoMq = true;}
      else if(qpSJsecZbc == JBKXQHJori){YSeUrFUWlI = true;}
      if(ZjuwuWRITa == VEkrziIQlK){yEpRDhoqOF = true;}
      else if(VEkrziIQlK == ZjuwuWRITa){ENnhlqBAYl = true;}
      if(FiIVYQcuty == RebGGIFxSO){djYZoqTeFF = true;}
      else if(RebGGIFxSO == FiIVYQcuty){VFbDhgXCIt = true;}
      if(CsKWhQBGGP == jUzQPLbwkc){xJijWaGXVu = true;}
      if(mIdUSROgnP == rnRSkTaNGB){XgIEEsYaxU = true;}
      if(pfdQZarnzA == PwydUMNMDj){WopTGegKdD = true;}
      while(jUzQPLbwkc == CsKWhQBGGP){AZIGWyNNqc = true;}
      while(rnRSkTaNGB == rnRSkTaNGB){mxcUmfGLeT = true;}
      while(PwydUMNMDj == PwydUMNMDj){kwbYsSqalL = true;}
      if(ZfHNsAEUcm == true){ZfHNsAEUcm = false;}
      if(GLfIRcNIVl == true){GLfIRcNIVl = false;}
      if(gqpQznVUwC == true){gqpQznVUwC = false;}
      if(yPrADMfEZk == true){yPrADMfEZk = false;}
      if(PGkStDPoMq == true){PGkStDPoMq = false;}
      if(yEpRDhoqOF == true){yEpRDhoqOF = false;}
      if(djYZoqTeFF == true){djYZoqTeFF = false;}
      if(xJijWaGXVu == true){xJijWaGXVu = false;}
      if(XgIEEsYaxU == true){XgIEEsYaxU = false;}
      if(WopTGegKdD == true){WopTGegKdD = false;}
      if(jjjHtoUFub == true){jjjHtoUFub = false;}
      if(bRUShxaTVu == true){bRUShxaTVu = false;}
      if(RshjhHTPdq == true){RshjhHTPdq = false;}
      if(sutRKmwAKO == true){sutRKmwAKO = false;}
      if(YSeUrFUWlI == true){YSeUrFUWlI = false;}
      if(ENnhlqBAYl == true){ENnhlqBAYl = false;}
      if(VFbDhgXCIt == true){VFbDhgXCIt = false;}
      if(AZIGWyNNqc == true){AZIGWyNNqc = false;}
      if(mxcUmfGLeT == true){mxcUmfGLeT = false;}
      if(kwbYsSqalL == true){kwbYsSqalL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUUGBUZYIS
{ 
  void TuhCgQTIGQ()
  { 
      bool gMTqafugxj = false;
      bool qhGWTySTut = false;
      bool gmystFciPr = false;
      bool wfbiRcuaDL = false;
      bool aVMQSJewLf = false;
      bool RJGFTtNZwU = false;
      bool DLQEnLFXEq = false;
      bool DrPiSLahZk = false;
      bool afXjZlYWOX = false;
      bool PUdhIPEHbH = false;
      bool DGqUbZsXmH = false;
      bool SezLtWnfeC = false;
      bool liJgahNgZD = false;
      bool HTGShTnCIA = false;
      bool sBjGEjVSnk = false;
      bool aXbZVTxKst = false;
      bool LMxiAzXgcZ = false;
      bool hkXeIjzCbp = false;
      bool MurnbjqgwN = false;
      bool VdINngEAGE = false;
      string AhhOKpLrRx;
      string eMUiuZVWnc;
      string WpnCxQchkl;
      string uGqMLFBaKB;
      string rXuchRLlqj;
      string trirxKseRs;
      string MdHeCXVHXp;
      string YtMljyuLUe;
      string FqqBrCXyPB;
      string LWIQnOQPaJ;
      string wDNALzfwIy;
      string PhKlnVlFmz;
      string AWrWdBkuxU;
      string hekKiCcppr;
      string VaoQldLWcS;
      string bKbaJYKqWJ;
      string NkymQjwzDl;
      string rwPudYhbjz;
      string oORerWCJBJ;
      string qlTfekcBzB;
      if(AhhOKpLrRx == wDNALzfwIy){gMTqafugxj = true;}
      else if(wDNALzfwIy == AhhOKpLrRx){DGqUbZsXmH = true;}
      if(eMUiuZVWnc == PhKlnVlFmz){qhGWTySTut = true;}
      else if(PhKlnVlFmz == eMUiuZVWnc){SezLtWnfeC = true;}
      if(WpnCxQchkl == AWrWdBkuxU){gmystFciPr = true;}
      else if(AWrWdBkuxU == WpnCxQchkl){liJgahNgZD = true;}
      if(uGqMLFBaKB == hekKiCcppr){wfbiRcuaDL = true;}
      else if(hekKiCcppr == uGqMLFBaKB){HTGShTnCIA = true;}
      if(rXuchRLlqj == VaoQldLWcS){aVMQSJewLf = true;}
      else if(VaoQldLWcS == rXuchRLlqj){sBjGEjVSnk = true;}
      if(trirxKseRs == bKbaJYKqWJ){RJGFTtNZwU = true;}
      else if(bKbaJYKqWJ == trirxKseRs){aXbZVTxKst = true;}
      if(MdHeCXVHXp == NkymQjwzDl){DLQEnLFXEq = true;}
      else if(NkymQjwzDl == MdHeCXVHXp){LMxiAzXgcZ = true;}
      if(YtMljyuLUe == rwPudYhbjz){DrPiSLahZk = true;}
      if(FqqBrCXyPB == oORerWCJBJ){afXjZlYWOX = true;}
      if(LWIQnOQPaJ == qlTfekcBzB){PUdhIPEHbH = true;}
      while(rwPudYhbjz == YtMljyuLUe){hkXeIjzCbp = true;}
      while(oORerWCJBJ == oORerWCJBJ){MurnbjqgwN = true;}
      while(qlTfekcBzB == qlTfekcBzB){VdINngEAGE = true;}
      if(gMTqafugxj == true){gMTqafugxj = false;}
      if(qhGWTySTut == true){qhGWTySTut = false;}
      if(gmystFciPr == true){gmystFciPr = false;}
      if(wfbiRcuaDL == true){wfbiRcuaDL = false;}
      if(aVMQSJewLf == true){aVMQSJewLf = false;}
      if(RJGFTtNZwU == true){RJGFTtNZwU = false;}
      if(DLQEnLFXEq == true){DLQEnLFXEq = false;}
      if(DrPiSLahZk == true){DrPiSLahZk = false;}
      if(afXjZlYWOX == true){afXjZlYWOX = false;}
      if(PUdhIPEHbH == true){PUdhIPEHbH = false;}
      if(DGqUbZsXmH == true){DGqUbZsXmH = false;}
      if(SezLtWnfeC == true){SezLtWnfeC = false;}
      if(liJgahNgZD == true){liJgahNgZD = false;}
      if(HTGShTnCIA == true){HTGShTnCIA = false;}
      if(sBjGEjVSnk == true){sBjGEjVSnk = false;}
      if(aXbZVTxKst == true){aXbZVTxKst = false;}
      if(LMxiAzXgcZ == true){LMxiAzXgcZ = false;}
      if(hkXeIjzCbp == true){hkXeIjzCbp = false;}
      if(MurnbjqgwN == true){MurnbjqgwN = false;}
      if(VdINngEAGE == true){VdINngEAGE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRIEXYFONB
{ 
  void fRXPGUMQDY()
  { 
      bool fzAYyHXRXV = false;
      bool eNzDQeMXUp = false;
      bool JwDTEFLpId = false;
      bool KStAGpLLtD = false;
      bool IrmuZeFapL = false;
      bool qmCCojugTr = false;
      bool ugJtKLSzxZ = false;
      bool SBcQgRJIsY = false;
      bool zkAwmXQqKW = false;
      bool uerBHahsjO = false;
      bool LGdProJkUX = false;
      bool almtrKgMGl = false;
      bool uanaenJbIF = false;
      bool jPXeNsHjEx = false;
      bool OeWmwIqxIx = false;
      bool tUlyTkSDkD = false;
      bool fgbPmKOIgz = false;
      bool CxIJWPEAeV = false;
      bool xLTLLOdZLb = false;
      bool ZEyAQhDHzk = false;
      string pSATiCfBxN;
      string dkDOfhTOlW;
      string SUlZiwRlGC;
      string YnAIisYIxJ;
      string DdtdcxzxCa;
      string oTuIQUgajm;
      string jttunojufl;
      string IKQbSnZHwl;
      string xUifMEsrqN;
      string MyXKYJjzpm;
      string MDQPRdDSob;
      string uYdyoPKNhi;
      string wrDRZKlFCJ;
      string EaRIYsETOh;
      string BaCPSmUZUJ;
      string yWQGqUAyoG;
      string qxPfWTHUYw;
      string LpyzhVomzl;
      string pMjrLgJLRE;
      string rFdHqDKWrz;
      if(pSATiCfBxN == MDQPRdDSob){fzAYyHXRXV = true;}
      else if(MDQPRdDSob == pSATiCfBxN){LGdProJkUX = true;}
      if(dkDOfhTOlW == uYdyoPKNhi){eNzDQeMXUp = true;}
      else if(uYdyoPKNhi == dkDOfhTOlW){almtrKgMGl = true;}
      if(SUlZiwRlGC == wrDRZKlFCJ){JwDTEFLpId = true;}
      else if(wrDRZKlFCJ == SUlZiwRlGC){uanaenJbIF = true;}
      if(YnAIisYIxJ == EaRIYsETOh){KStAGpLLtD = true;}
      else if(EaRIYsETOh == YnAIisYIxJ){jPXeNsHjEx = true;}
      if(DdtdcxzxCa == BaCPSmUZUJ){IrmuZeFapL = true;}
      else if(BaCPSmUZUJ == DdtdcxzxCa){OeWmwIqxIx = true;}
      if(oTuIQUgajm == yWQGqUAyoG){qmCCojugTr = true;}
      else if(yWQGqUAyoG == oTuIQUgajm){tUlyTkSDkD = true;}
      if(jttunojufl == qxPfWTHUYw){ugJtKLSzxZ = true;}
      else if(qxPfWTHUYw == jttunojufl){fgbPmKOIgz = true;}
      if(IKQbSnZHwl == LpyzhVomzl){SBcQgRJIsY = true;}
      if(xUifMEsrqN == pMjrLgJLRE){zkAwmXQqKW = true;}
      if(MyXKYJjzpm == rFdHqDKWrz){uerBHahsjO = true;}
      while(LpyzhVomzl == IKQbSnZHwl){CxIJWPEAeV = true;}
      while(pMjrLgJLRE == pMjrLgJLRE){xLTLLOdZLb = true;}
      while(rFdHqDKWrz == rFdHqDKWrz){ZEyAQhDHzk = true;}
      if(fzAYyHXRXV == true){fzAYyHXRXV = false;}
      if(eNzDQeMXUp == true){eNzDQeMXUp = false;}
      if(JwDTEFLpId == true){JwDTEFLpId = false;}
      if(KStAGpLLtD == true){KStAGpLLtD = false;}
      if(IrmuZeFapL == true){IrmuZeFapL = false;}
      if(qmCCojugTr == true){qmCCojugTr = false;}
      if(ugJtKLSzxZ == true){ugJtKLSzxZ = false;}
      if(SBcQgRJIsY == true){SBcQgRJIsY = false;}
      if(zkAwmXQqKW == true){zkAwmXQqKW = false;}
      if(uerBHahsjO == true){uerBHahsjO = false;}
      if(LGdProJkUX == true){LGdProJkUX = false;}
      if(almtrKgMGl == true){almtrKgMGl = false;}
      if(uanaenJbIF == true){uanaenJbIF = false;}
      if(jPXeNsHjEx == true){jPXeNsHjEx = false;}
      if(OeWmwIqxIx == true){OeWmwIqxIx = false;}
      if(tUlyTkSDkD == true){tUlyTkSDkD = false;}
      if(fgbPmKOIgz == true){fgbPmKOIgz = false;}
      if(CxIJWPEAeV == true){CxIJWPEAeV = false;}
      if(xLTLLOdZLb == true){xLTLLOdZLb = false;}
      if(ZEyAQhDHzk == true){ZEyAQhDHzk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KJIBKZHUXC
{ 
  void CwKzbrmJOd()
  { 
      bool fklFwzlVFs = false;
      bool DpZbAWKIBW = false;
      bool yTEnpfjEDZ = false;
      bool DkEwffdeJS = false;
      bool nNBqltHnfM = false;
      bool HxRIaMgyOQ = false;
      bool PhSeoSkcwT = false;
      bool seyhijSMBw = false;
      bool XwXqSGTwVS = false;
      bool yfPsDFuVCT = false;
      bool IdqLSbyiYp = false;
      bool tTwSrTJbLh = false;
      bool zoGcVNPFdc = false;
      bool owKgmtELXq = false;
      bool IjWfYdiwAj = false;
      bool wSKTUTWOpF = false;
      bool LrEwAxIOfy = false;
      bool OxEUZORaDq = false;
      bool dSEtgVlqMT = false;
      bool WoVRfPfafa = false;
      string iXjjNoiCws;
      string ZAQybsrlDk;
      string GpllLbwUKq;
      string QshcfXARDp;
      string PzaePPbsKC;
      string xsrIDslyXl;
      string rNqFbfRmRE;
      string sahNUGPGVw;
      string zDJHtXAZZm;
      string lBsRyCIUCi;
      string ynaGJVKemw;
      string debbloDjLE;
      string fqNeSqhQPS;
      string ytEmxLcDyX;
      string MVmcIGZQfI;
      string zXJxDHaunR;
      string ntPUxianea;
      string MzkmrJDjVL;
      string RQjGSajGjp;
      string jgPgjRGSeY;
      if(iXjjNoiCws == ynaGJVKemw){fklFwzlVFs = true;}
      else if(ynaGJVKemw == iXjjNoiCws){IdqLSbyiYp = true;}
      if(ZAQybsrlDk == debbloDjLE){DpZbAWKIBW = true;}
      else if(debbloDjLE == ZAQybsrlDk){tTwSrTJbLh = true;}
      if(GpllLbwUKq == fqNeSqhQPS){yTEnpfjEDZ = true;}
      else if(fqNeSqhQPS == GpllLbwUKq){zoGcVNPFdc = true;}
      if(QshcfXARDp == ytEmxLcDyX){DkEwffdeJS = true;}
      else if(ytEmxLcDyX == QshcfXARDp){owKgmtELXq = true;}
      if(PzaePPbsKC == MVmcIGZQfI){nNBqltHnfM = true;}
      else if(MVmcIGZQfI == PzaePPbsKC){IjWfYdiwAj = true;}
      if(xsrIDslyXl == zXJxDHaunR){HxRIaMgyOQ = true;}
      else if(zXJxDHaunR == xsrIDslyXl){wSKTUTWOpF = true;}
      if(rNqFbfRmRE == ntPUxianea){PhSeoSkcwT = true;}
      else if(ntPUxianea == rNqFbfRmRE){LrEwAxIOfy = true;}
      if(sahNUGPGVw == MzkmrJDjVL){seyhijSMBw = true;}
      if(zDJHtXAZZm == RQjGSajGjp){XwXqSGTwVS = true;}
      if(lBsRyCIUCi == jgPgjRGSeY){yfPsDFuVCT = true;}
      while(MzkmrJDjVL == sahNUGPGVw){OxEUZORaDq = true;}
      while(RQjGSajGjp == RQjGSajGjp){dSEtgVlqMT = true;}
      while(jgPgjRGSeY == jgPgjRGSeY){WoVRfPfafa = true;}
      if(fklFwzlVFs == true){fklFwzlVFs = false;}
      if(DpZbAWKIBW == true){DpZbAWKIBW = false;}
      if(yTEnpfjEDZ == true){yTEnpfjEDZ = false;}
      if(DkEwffdeJS == true){DkEwffdeJS = false;}
      if(nNBqltHnfM == true){nNBqltHnfM = false;}
      if(HxRIaMgyOQ == true){HxRIaMgyOQ = false;}
      if(PhSeoSkcwT == true){PhSeoSkcwT = false;}
      if(seyhijSMBw == true){seyhijSMBw = false;}
      if(XwXqSGTwVS == true){XwXqSGTwVS = false;}
      if(yfPsDFuVCT == true){yfPsDFuVCT = false;}
      if(IdqLSbyiYp == true){IdqLSbyiYp = false;}
      if(tTwSrTJbLh == true){tTwSrTJbLh = false;}
      if(zoGcVNPFdc == true){zoGcVNPFdc = false;}
      if(owKgmtELXq == true){owKgmtELXq = false;}
      if(IjWfYdiwAj == true){IjWfYdiwAj = false;}
      if(wSKTUTWOpF == true){wSKTUTWOpF = false;}
      if(LrEwAxIOfy == true){LrEwAxIOfy = false;}
      if(OxEUZORaDq == true){OxEUZORaDq = false;}
      if(dSEtgVlqMT == true){dSEtgVlqMT = false;}
      if(WoVRfPfafa == true){WoVRfPfafa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIROWTHFTG
{ 
  void blqzGWBcoS()
  { 
      bool DyeOBitVcj = false;
      bool ChmwadKyBN = false;
      bool ROhIuYDqVE = false;
      bool SjZpKZUWdE = false;
      bool RQBChTiRLf = false;
      bool SwqJhoQWSc = false;
      bool eDzXRSIwkA = false;
      bool InUxuBNeZa = false;
      bool olepkVrPIU = false;
      bool IyDAYOQcjP = false;
      bool LlfLXebtNf = false;
      bool bkwrmsXJlu = false;
      bool ZrnQqJjTXg = false;
      bool jjuKODGTRG = false;
      bool tyBbsXBLNe = false;
      bool pGpnoSyOTO = false;
      bool uHVfwqpkcj = false;
      bool mDrfBbpLXT = false;
      bool HXGsqcsGVu = false;
      bool EqADLlbUfB = false;
      string BBsugrooTm;
      string OrCpMRLbUC;
      string RxJSapeFqF;
      string HzSyAWzDjD;
      string YokzyRfKLK;
      string MlVGnErZTq;
      string NiyNeOYEop;
      string RIqRccLJUJ;
      string JTtfrVcMJw;
      string eYispoqWUj;
      string raVVsEtEcL;
      string rhFKgsoRUJ;
      string kMurLrZyan;
      string lnokQiyXmn;
      string aXixDwTYMw;
      string AYCLyffcKA;
      string dwcoZDrUsy;
      string tQdfhNcxoO;
      string YAkemMldmk;
      string CVNmJdtsXz;
      if(BBsugrooTm == raVVsEtEcL){DyeOBitVcj = true;}
      else if(raVVsEtEcL == BBsugrooTm){LlfLXebtNf = true;}
      if(OrCpMRLbUC == rhFKgsoRUJ){ChmwadKyBN = true;}
      else if(rhFKgsoRUJ == OrCpMRLbUC){bkwrmsXJlu = true;}
      if(RxJSapeFqF == kMurLrZyan){ROhIuYDqVE = true;}
      else if(kMurLrZyan == RxJSapeFqF){ZrnQqJjTXg = true;}
      if(HzSyAWzDjD == lnokQiyXmn){SjZpKZUWdE = true;}
      else if(lnokQiyXmn == HzSyAWzDjD){jjuKODGTRG = true;}
      if(YokzyRfKLK == aXixDwTYMw){RQBChTiRLf = true;}
      else if(aXixDwTYMw == YokzyRfKLK){tyBbsXBLNe = true;}
      if(MlVGnErZTq == AYCLyffcKA){SwqJhoQWSc = true;}
      else if(AYCLyffcKA == MlVGnErZTq){pGpnoSyOTO = true;}
      if(NiyNeOYEop == dwcoZDrUsy){eDzXRSIwkA = true;}
      else if(dwcoZDrUsy == NiyNeOYEop){uHVfwqpkcj = true;}
      if(RIqRccLJUJ == tQdfhNcxoO){InUxuBNeZa = true;}
      if(JTtfrVcMJw == YAkemMldmk){olepkVrPIU = true;}
      if(eYispoqWUj == CVNmJdtsXz){IyDAYOQcjP = true;}
      while(tQdfhNcxoO == RIqRccLJUJ){mDrfBbpLXT = true;}
      while(YAkemMldmk == YAkemMldmk){HXGsqcsGVu = true;}
      while(CVNmJdtsXz == CVNmJdtsXz){EqADLlbUfB = true;}
      if(DyeOBitVcj == true){DyeOBitVcj = false;}
      if(ChmwadKyBN == true){ChmwadKyBN = false;}
      if(ROhIuYDqVE == true){ROhIuYDqVE = false;}
      if(SjZpKZUWdE == true){SjZpKZUWdE = false;}
      if(RQBChTiRLf == true){RQBChTiRLf = false;}
      if(SwqJhoQWSc == true){SwqJhoQWSc = false;}
      if(eDzXRSIwkA == true){eDzXRSIwkA = false;}
      if(InUxuBNeZa == true){InUxuBNeZa = false;}
      if(olepkVrPIU == true){olepkVrPIU = false;}
      if(IyDAYOQcjP == true){IyDAYOQcjP = false;}
      if(LlfLXebtNf == true){LlfLXebtNf = false;}
      if(bkwrmsXJlu == true){bkwrmsXJlu = false;}
      if(ZrnQqJjTXg == true){ZrnQqJjTXg = false;}
      if(jjuKODGTRG == true){jjuKODGTRG = false;}
      if(tyBbsXBLNe == true){tyBbsXBLNe = false;}
      if(pGpnoSyOTO == true){pGpnoSyOTO = false;}
      if(uHVfwqpkcj == true){uHVfwqpkcj = false;}
      if(mDrfBbpLXT == true){mDrfBbpLXT = false;}
      if(HXGsqcsGVu == true){HXGsqcsGVu = false;}
      if(EqADLlbUfB == true){EqADLlbUfB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XJUDFFIOCD
{ 
  void lELGucZZoO()
  { 
      bool TNKDdIIIuN = false;
      bool aFzobNsNfx = false;
      bool FxpPIQNUwT = false;
      bool MDyObYFANe = false;
      bool ZFLhQCBVdm = false;
      bool aPaqiWXutM = false;
      bool umMbAWGjND = false;
      bool IrzAWzkHyG = false;
      bool PqqJrwbHfE = false;
      bool AJGBjmsjgt = false;
      bool wQIaeiQaTj = false;
      bool kPxmwDwDiD = false;
      bool tyEICylxQj = false;
      bool FAZEKyhQdJ = false;
      bool eBnuTkMSEf = false;
      bool ppBczxMAXf = false;
      bool wSKidjoscx = false;
      bool VeYYYsKInR = false;
      bool kTsjtPzwEN = false;
      bool lhrxNLqERi = false;
      string sjXLDeTKEB;
      string bjwxlYVPIA;
      string sCIIbiqwtl;
      string MZgSnwBlGE;
      string auAceafYuY;
      string ucxPxqbOjU;
      string mWQRoBDdJo;
      string XjJEZyCecA;
      string CSBUpjbRUx;
      string UlBlQDehnd;
      string XCPFALTspz;
      string nwljRUVubE;
      string ZlIMUlhWmV;
      string SUqzcADwTe;
      string QiaVIYzRTu;
      string hjFiDksCkO;
      string dwFTgTElGQ;
      string RYaxnpKmDu;
      string lPDrniOHuq;
      string HALFATdHnn;
      if(sjXLDeTKEB == XCPFALTspz){TNKDdIIIuN = true;}
      else if(XCPFALTspz == sjXLDeTKEB){wQIaeiQaTj = true;}
      if(bjwxlYVPIA == nwljRUVubE){aFzobNsNfx = true;}
      else if(nwljRUVubE == bjwxlYVPIA){kPxmwDwDiD = true;}
      if(sCIIbiqwtl == ZlIMUlhWmV){FxpPIQNUwT = true;}
      else if(ZlIMUlhWmV == sCIIbiqwtl){tyEICylxQj = true;}
      if(MZgSnwBlGE == SUqzcADwTe){MDyObYFANe = true;}
      else if(SUqzcADwTe == MZgSnwBlGE){FAZEKyhQdJ = true;}
      if(auAceafYuY == QiaVIYzRTu){ZFLhQCBVdm = true;}
      else if(QiaVIYzRTu == auAceafYuY){eBnuTkMSEf = true;}
      if(ucxPxqbOjU == hjFiDksCkO){aPaqiWXutM = true;}
      else if(hjFiDksCkO == ucxPxqbOjU){ppBczxMAXf = true;}
      if(mWQRoBDdJo == dwFTgTElGQ){umMbAWGjND = true;}
      else if(dwFTgTElGQ == mWQRoBDdJo){wSKidjoscx = true;}
      if(XjJEZyCecA == RYaxnpKmDu){IrzAWzkHyG = true;}
      if(CSBUpjbRUx == lPDrniOHuq){PqqJrwbHfE = true;}
      if(UlBlQDehnd == HALFATdHnn){AJGBjmsjgt = true;}
      while(RYaxnpKmDu == XjJEZyCecA){VeYYYsKInR = true;}
      while(lPDrniOHuq == lPDrniOHuq){kTsjtPzwEN = true;}
      while(HALFATdHnn == HALFATdHnn){lhrxNLqERi = true;}
      if(TNKDdIIIuN == true){TNKDdIIIuN = false;}
      if(aFzobNsNfx == true){aFzobNsNfx = false;}
      if(FxpPIQNUwT == true){FxpPIQNUwT = false;}
      if(MDyObYFANe == true){MDyObYFANe = false;}
      if(ZFLhQCBVdm == true){ZFLhQCBVdm = false;}
      if(aPaqiWXutM == true){aPaqiWXutM = false;}
      if(umMbAWGjND == true){umMbAWGjND = false;}
      if(IrzAWzkHyG == true){IrzAWzkHyG = false;}
      if(PqqJrwbHfE == true){PqqJrwbHfE = false;}
      if(AJGBjmsjgt == true){AJGBjmsjgt = false;}
      if(wQIaeiQaTj == true){wQIaeiQaTj = false;}
      if(kPxmwDwDiD == true){kPxmwDwDiD = false;}
      if(tyEICylxQj == true){tyEICylxQj = false;}
      if(FAZEKyhQdJ == true){FAZEKyhQdJ = false;}
      if(eBnuTkMSEf == true){eBnuTkMSEf = false;}
      if(ppBczxMAXf == true){ppBczxMAXf = false;}
      if(wSKidjoscx == true){wSKidjoscx = false;}
      if(VeYYYsKInR == true){VeYYYsKInR = false;}
      if(kTsjtPzwEN == true){kTsjtPzwEN = false;}
      if(lhrxNLqERi == true){lhrxNLqERi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YCZCSBQBMJ
{ 
  void LwxAIYumuk()
  { 
      bool kYLsqlSahS = false;
      bool CLlKqGjeeR = false;
      bool QjXRwPdeKJ = false;
      bool FjnFYyfZqJ = false;
      bool gETHPluSZU = false;
      bool IYqChABtwb = false;
      bool HmPXNSWgks = false;
      bool aKnVkMQPBJ = false;
      bool TKFoBfrlWY = false;
      bool xkcOBsnusw = false;
      bool OOhgtxkVRV = false;
      bool ikrmHxhaWh = false;
      bool ZkJMwogYTq = false;
      bool YVVEtFcYtD = false;
      bool tWTBoLrpHE = false;
      bool LNXLWdFUkF = false;
      bool PMCaxNPnrC = false;
      bool TJfTmDRIWj = false;
      bool xqQOeLxJhQ = false;
      bool zInomhUrEa = false;
      string VCBYZnklNg;
      string LuibPCCOuA;
      string YOJrXXwdSq;
      string afZPqmiHEH;
      string INwojikddc;
      string fUaJsGrJAB;
      string rHTWFfUSkb;
      string TtJnqKRUHo;
      string lSAoKGEPVj;
      string tYHCPBtZiE;
      string NSrBIkKlRi;
      string nXCLOYGdLy;
      string aEwAgtmGYp;
      string QrlDbTZyfZ;
      string wRymuWWunp;
      string tQNjcIVqUO;
      string xDNaRwlyjt;
      string yHxlCJGJFJ;
      string WqSiwAeBaS;
      string yhdRbsEWUz;
      if(VCBYZnklNg == NSrBIkKlRi){kYLsqlSahS = true;}
      else if(NSrBIkKlRi == VCBYZnklNg){OOhgtxkVRV = true;}
      if(LuibPCCOuA == nXCLOYGdLy){CLlKqGjeeR = true;}
      else if(nXCLOYGdLy == LuibPCCOuA){ikrmHxhaWh = true;}
      if(YOJrXXwdSq == aEwAgtmGYp){QjXRwPdeKJ = true;}
      else if(aEwAgtmGYp == YOJrXXwdSq){ZkJMwogYTq = true;}
      if(afZPqmiHEH == QrlDbTZyfZ){FjnFYyfZqJ = true;}
      else if(QrlDbTZyfZ == afZPqmiHEH){YVVEtFcYtD = true;}
      if(INwojikddc == wRymuWWunp){gETHPluSZU = true;}
      else if(wRymuWWunp == INwojikddc){tWTBoLrpHE = true;}
      if(fUaJsGrJAB == tQNjcIVqUO){IYqChABtwb = true;}
      else if(tQNjcIVqUO == fUaJsGrJAB){LNXLWdFUkF = true;}
      if(rHTWFfUSkb == xDNaRwlyjt){HmPXNSWgks = true;}
      else if(xDNaRwlyjt == rHTWFfUSkb){PMCaxNPnrC = true;}
      if(TtJnqKRUHo == yHxlCJGJFJ){aKnVkMQPBJ = true;}
      if(lSAoKGEPVj == WqSiwAeBaS){TKFoBfrlWY = true;}
      if(tYHCPBtZiE == yhdRbsEWUz){xkcOBsnusw = true;}
      while(yHxlCJGJFJ == TtJnqKRUHo){TJfTmDRIWj = true;}
      while(WqSiwAeBaS == WqSiwAeBaS){xqQOeLxJhQ = true;}
      while(yhdRbsEWUz == yhdRbsEWUz){zInomhUrEa = true;}
      if(kYLsqlSahS == true){kYLsqlSahS = false;}
      if(CLlKqGjeeR == true){CLlKqGjeeR = false;}
      if(QjXRwPdeKJ == true){QjXRwPdeKJ = false;}
      if(FjnFYyfZqJ == true){FjnFYyfZqJ = false;}
      if(gETHPluSZU == true){gETHPluSZU = false;}
      if(IYqChABtwb == true){IYqChABtwb = false;}
      if(HmPXNSWgks == true){HmPXNSWgks = false;}
      if(aKnVkMQPBJ == true){aKnVkMQPBJ = false;}
      if(TKFoBfrlWY == true){TKFoBfrlWY = false;}
      if(xkcOBsnusw == true){xkcOBsnusw = false;}
      if(OOhgtxkVRV == true){OOhgtxkVRV = false;}
      if(ikrmHxhaWh == true){ikrmHxhaWh = false;}
      if(ZkJMwogYTq == true){ZkJMwogYTq = false;}
      if(YVVEtFcYtD == true){YVVEtFcYtD = false;}
      if(tWTBoLrpHE == true){tWTBoLrpHE = false;}
      if(LNXLWdFUkF == true){LNXLWdFUkF = false;}
      if(PMCaxNPnrC == true){PMCaxNPnrC = false;}
      if(TJfTmDRIWj == true){TJfTmDRIWj = false;}
      if(xqQOeLxJhQ == true){xqQOeLxJhQ = false;}
      if(zInomhUrEa == true){zInomhUrEa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HCXDRQHTQX
{ 
  void TJYeHWszoR()
  { 
      bool RznboMHcCc = false;
      bool XtIKQNWIsS = false;
      bool hgucNqTdeC = false;
      bool XkabMMtEyC = false;
      bool jIHUftNyoc = false;
      bool ynSHEkDLNy = false;
      bool rcxAElTfxD = false;
      bool SSJqhZYawT = false;
      bool cVoCEjRSXb = false;
      bool JhpAJGLGQt = false;
      bool ahBlJedbYd = false;
      bool LbPtUWntwT = false;
      bool TAIVsjbIga = false;
      bool OSJCsuUDrY = false;
      bool FpssPgSwfl = false;
      bool SQKwZZZerY = false;
      bool CVtyPsSNBZ = false;
      bool CkCXNdGPGM = false;
      bool RfbuIyINcS = false;
      bool VoKSVjuucV = false;
      string jzFRaKoRMT;
      string POdjuSbFJt;
      string hqPJySOikS;
      string iVQNDUeuaH;
      string XpBIDkyZFU;
      string ftpijsiuTI;
      string wFgtksyPfa;
      string nfeCWqpHGM;
      string TndPlnfgcJ;
      string kibSKRIGWK;
      string mitegAPmMr;
      string DboGnHbRHw;
      string MRlVoEELqE;
      string hikuZktyhl;
      string YrTkGJsUeC;
      string pqyZxVwXpb;
      string wDwHJTqtgC;
      string NcjVXTxBPe;
      string LignOqkKyE;
      string oWIFpUwLam;
      if(jzFRaKoRMT == mitegAPmMr){RznboMHcCc = true;}
      else if(mitegAPmMr == jzFRaKoRMT){ahBlJedbYd = true;}
      if(POdjuSbFJt == DboGnHbRHw){XtIKQNWIsS = true;}
      else if(DboGnHbRHw == POdjuSbFJt){LbPtUWntwT = true;}
      if(hqPJySOikS == MRlVoEELqE){hgucNqTdeC = true;}
      else if(MRlVoEELqE == hqPJySOikS){TAIVsjbIga = true;}
      if(iVQNDUeuaH == hikuZktyhl){XkabMMtEyC = true;}
      else if(hikuZktyhl == iVQNDUeuaH){OSJCsuUDrY = true;}
      if(XpBIDkyZFU == YrTkGJsUeC){jIHUftNyoc = true;}
      else if(YrTkGJsUeC == XpBIDkyZFU){FpssPgSwfl = true;}
      if(ftpijsiuTI == pqyZxVwXpb){ynSHEkDLNy = true;}
      else if(pqyZxVwXpb == ftpijsiuTI){SQKwZZZerY = true;}
      if(wFgtksyPfa == wDwHJTqtgC){rcxAElTfxD = true;}
      else if(wDwHJTqtgC == wFgtksyPfa){CVtyPsSNBZ = true;}
      if(nfeCWqpHGM == NcjVXTxBPe){SSJqhZYawT = true;}
      if(TndPlnfgcJ == LignOqkKyE){cVoCEjRSXb = true;}
      if(kibSKRIGWK == oWIFpUwLam){JhpAJGLGQt = true;}
      while(NcjVXTxBPe == nfeCWqpHGM){CkCXNdGPGM = true;}
      while(LignOqkKyE == LignOqkKyE){RfbuIyINcS = true;}
      while(oWIFpUwLam == oWIFpUwLam){VoKSVjuucV = true;}
      if(RznboMHcCc == true){RznboMHcCc = false;}
      if(XtIKQNWIsS == true){XtIKQNWIsS = false;}
      if(hgucNqTdeC == true){hgucNqTdeC = false;}
      if(XkabMMtEyC == true){XkabMMtEyC = false;}
      if(jIHUftNyoc == true){jIHUftNyoc = false;}
      if(ynSHEkDLNy == true){ynSHEkDLNy = false;}
      if(rcxAElTfxD == true){rcxAElTfxD = false;}
      if(SSJqhZYawT == true){SSJqhZYawT = false;}
      if(cVoCEjRSXb == true){cVoCEjRSXb = false;}
      if(JhpAJGLGQt == true){JhpAJGLGQt = false;}
      if(ahBlJedbYd == true){ahBlJedbYd = false;}
      if(LbPtUWntwT == true){LbPtUWntwT = false;}
      if(TAIVsjbIga == true){TAIVsjbIga = false;}
      if(OSJCsuUDrY == true){OSJCsuUDrY = false;}
      if(FpssPgSwfl == true){FpssPgSwfl = false;}
      if(SQKwZZZerY == true){SQKwZZZerY = false;}
      if(CVtyPsSNBZ == true){CVtyPsSNBZ = false;}
      if(CkCXNdGPGM == true){CkCXNdGPGM = false;}
      if(RfbuIyINcS == true){RfbuIyINcS = false;}
      if(VoKSVjuucV == true){VoKSVjuucV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ILBNICTRWI
{ 
  void YxaRGpOqrK()
  { 
      bool xGOCwbempN = false;
      bool bREbZTFYlE = false;
      bool IPdhXCMYNU = false;
      bool QywWQmwncj = false;
      bool cdbsnxOFpU = false;
      bool ONugQhbgdt = false;
      bool OGZVxdUgLm = false;
      bool XQwCbemksa = false;
      bool nGhsFDCOFh = false;
      bool KOJhUVEGuK = false;
      bool bgtCxxQsFl = false;
      bool tqmDGIXfPt = false;
      bool aGacbIHOgF = false;
      bool ZgoizGMfwH = false;
      bool lIJSmTaGaM = false;
      bool yXpBiVFQan = false;
      bool pCLAMNCEDA = false;
      bool urjHHRwHpI = false;
      bool hAmUHBqmzd = false;
      bool AuFHRiwIGZ = false;
      string YnkntGcmWp;
      string YhNSmdyKIm;
      string SWVxcwzBde;
      string qKMtkfqrnM;
      string QADkSmBgrq;
      string IykBGCRnKx;
      string GaJryNUTgH;
      string mFWwWSTkdo;
      string uSIlVsZKmi;
      string NChpFopLlF;
      string RgzkDCboen;
      string hgKUBnSWVF;
      string nKgytkXfph;
      string bHyYWOTXiT;
      string QkeyAfqMoR;
      string VTpfRHzBpS;
      string ewyxMahkxm;
      string UtnCoDfhxO;
      string sKpYLIRSHP;
      string OShPnUlhlZ;
      if(YnkntGcmWp == RgzkDCboen){xGOCwbempN = true;}
      else if(RgzkDCboen == YnkntGcmWp){bgtCxxQsFl = true;}
      if(YhNSmdyKIm == hgKUBnSWVF){bREbZTFYlE = true;}
      else if(hgKUBnSWVF == YhNSmdyKIm){tqmDGIXfPt = true;}
      if(SWVxcwzBde == nKgytkXfph){IPdhXCMYNU = true;}
      else if(nKgytkXfph == SWVxcwzBde){aGacbIHOgF = true;}
      if(qKMtkfqrnM == bHyYWOTXiT){QywWQmwncj = true;}
      else if(bHyYWOTXiT == qKMtkfqrnM){ZgoizGMfwH = true;}
      if(QADkSmBgrq == QkeyAfqMoR){cdbsnxOFpU = true;}
      else if(QkeyAfqMoR == QADkSmBgrq){lIJSmTaGaM = true;}
      if(IykBGCRnKx == VTpfRHzBpS){ONugQhbgdt = true;}
      else if(VTpfRHzBpS == IykBGCRnKx){yXpBiVFQan = true;}
      if(GaJryNUTgH == ewyxMahkxm){OGZVxdUgLm = true;}
      else if(ewyxMahkxm == GaJryNUTgH){pCLAMNCEDA = true;}
      if(mFWwWSTkdo == UtnCoDfhxO){XQwCbemksa = true;}
      if(uSIlVsZKmi == sKpYLIRSHP){nGhsFDCOFh = true;}
      if(NChpFopLlF == OShPnUlhlZ){KOJhUVEGuK = true;}
      while(UtnCoDfhxO == mFWwWSTkdo){urjHHRwHpI = true;}
      while(sKpYLIRSHP == sKpYLIRSHP){hAmUHBqmzd = true;}
      while(OShPnUlhlZ == OShPnUlhlZ){AuFHRiwIGZ = true;}
      if(xGOCwbempN == true){xGOCwbempN = false;}
      if(bREbZTFYlE == true){bREbZTFYlE = false;}
      if(IPdhXCMYNU == true){IPdhXCMYNU = false;}
      if(QywWQmwncj == true){QywWQmwncj = false;}
      if(cdbsnxOFpU == true){cdbsnxOFpU = false;}
      if(ONugQhbgdt == true){ONugQhbgdt = false;}
      if(OGZVxdUgLm == true){OGZVxdUgLm = false;}
      if(XQwCbemksa == true){XQwCbemksa = false;}
      if(nGhsFDCOFh == true){nGhsFDCOFh = false;}
      if(KOJhUVEGuK == true){KOJhUVEGuK = false;}
      if(bgtCxxQsFl == true){bgtCxxQsFl = false;}
      if(tqmDGIXfPt == true){tqmDGIXfPt = false;}
      if(aGacbIHOgF == true){aGacbIHOgF = false;}
      if(ZgoizGMfwH == true){ZgoizGMfwH = false;}
      if(lIJSmTaGaM == true){lIJSmTaGaM = false;}
      if(yXpBiVFQan == true){yXpBiVFQan = false;}
      if(pCLAMNCEDA == true){pCLAMNCEDA = false;}
      if(urjHHRwHpI == true){urjHHRwHpI = false;}
      if(hAmUHBqmzd == true){hAmUHBqmzd = false;}
      if(AuFHRiwIGZ == true){AuFHRiwIGZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GRDKPUZBMZ
{ 
  void aFIsqhtdmu()
  { 
      bool qUEcyWWOVg = false;
      bool iChFGRNrwp = false;
      bool nOJDxHJHTY = false;
      bool ADxziBsAOZ = false;
      bool TkyEXYTNpH = false;
      bool WRemQbKBfq = false;
      bool NOuxfeEiVF = false;
      bool XNdWWCQEeX = false;
      bool nuQLCiYKiG = false;
      bool qqTWLEpAXs = false;
      bool UkrkjImHQN = false;
      bool LFWHDRyiux = false;
      bool FsAOOgsGLR = false;
      bool MQglCDDfbs = false;
      bool uRtUukUMTs = false;
      bool GGEZmakcWD = false;
      bool OgwyBtYkEz = false;
      bool ORHBBnzeTc = false;
      bool LglRLFLGzb = false;
      bool SaJYeOVuTA = false;
      string qRMglIsBLN;
      string NncYYnZqxP;
      string xtQmNkqgfI;
      string dsbelLNPgW;
      string patAnbOUxp;
      string nfBQVwAYSB;
      string RMUDiTMxlN;
      string aKKZZWzQzl;
      string WVipTxrLJp;
      string KowfEcFqQU;
      string PQhiPdVbpy;
      string wiZgdwceik;
      string bAmwClNeVw;
      string QIzdVFmAap;
      string bQULsaPPBI;
      string AaIerOdkgc;
      string PqFsgniuKY;
      string JcEsJLfbDa;
      string VycNwpATkH;
      string bBTxZkKbdE;
      if(qRMglIsBLN == PQhiPdVbpy){qUEcyWWOVg = true;}
      else if(PQhiPdVbpy == qRMglIsBLN){UkrkjImHQN = true;}
      if(NncYYnZqxP == wiZgdwceik){iChFGRNrwp = true;}
      else if(wiZgdwceik == NncYYnZqxP){LFWHDRyiux = true;}
      if(xtQmNkqgfI == bAmwClNeVw){nOJDxHJHTY = true;}
      else if(bAmwClNeVw == xtQmNkqgfI){FsAOOgsGLR = true;}
      if(dsbelLNPgW == QIzdVFmAap){ADxziBsAOZ = true;}
      else if(QIzdVFmAap == dsbelLNPgW){MQglCDDfbs = true;}
      if(patAnbOUxp == bQULsaPPBI){TkyEXYTNpH = true;}
      else if(bQULsaPPBI == patAnbOUxp){uRtUukUMTs = true;}
      if(nfBQVwAYSB == AaIerOdkgc){WRemQbKBfq = true;}
      else if(AaIerOdkgc == nfBQVwAYSB){GGEZmakcWD = true;}
      if(RMUDiTMxlN == PqFsgniuKY){NOuxfeEiVF = true;}
      else if(PqFsgniuKY == RMUDiTMxlN){OgwyBtYkEz = true;}
      if(aKKZZWzQzl == JcEsJLfbDa){XNdWWCQEeX = true;}
      if(WVipTxrLJp == VycNwpATkH){nuQLCiYKiG = true;}
      if(KowfEcFqQU == bBTxZkKbdE){qqTWLEpAXs = true;}
      while(JcEsJLfbDa == aKKZZWzQzl){ORHBBnzeTc = true;}
      while(VycNwpATkH == VycNwpATkH){LglRLFLGzb = true;}
      while(bBTxZkKbdE == bBTxZkKbdE){SaJYeOVuTA = true;}
      if(qUEcyWWOVg == true){qUEcyWWOVg = false;}
      if(iChFGRNrwp == true){iChFGRNrwp = false;}
      if(nOJDxHJHTY == true){nOJDxHJHTY = false;}
      if(ADxziBsAOZ == true){ADxziBsAOZ = false;}
      if(TkyEXYTNpH == true){TkyEXYTNpH = false;}
      if(WRemQbKBfq == true){WRemQbKBfq = false;}
      if(NOuxfeEiVF == true){NOuxfeEiVF = false;}
      if(XNdWWCQEeX == true){XNdWWCQEeX = false;}
      if(nuQLCiYKiG == true){nuQLCiYKiG = false;}
      if(qqTWLEpAXs == true){qqTWLEpAXs = false;}
      if(UkrkjImHQN == true){UkrkjImHQN = false;}
      if(LFWHDRyiux == true){LFWHDRyiux = false;}
      if(FsAOOgsGLR == true){FsAOOgsGLR = false;}
      if(MQglCDDfbs == true){MQglCDDfbs = false;}
      if(uRtUukUMTs == true){uRtUukUMTs = false;}
      if(GGEZmakcWD == true){GGEZmakcWD = false;}
      if(OgwyBtYkEz == true){OgwyBtYkEz = false;}
      if(ORHBBnzeTc == true){ORHBBnzeTc = false;}
      if(LglRLFLGzb == true){LglRLFLGzb = false;}
      if(SaJYeOVuTA == true){SaJYeOVuTA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EKNZSRTZIF
{ 
  void uSrPingUhz()
  { 
      bool KSUsBbHyQT = false;
      bool CLRTWZfryE = false;
      bool hhguMWJxfr = false;
      bool yTLpZSdfFC = false;
      bool ShVqolbwaU = false;
      bool uzICObkYfe = false;
      bool RJRXUhAasD = false;
      bool uAlwkAMpGZ = false;
      bool tMWKxzKIbx = false;
      bool gFzajIPxWG = false;
      bool lBCWZuNMQN = false;
      bool PuRFjFmGaU = false;
      bool WqywWoALLc = false;
      bool kPSznsJAkC = false;
      bool lyrOhlmspe = false;
      bool VIWBjtCGAj = false;
      bool tBAnbzbSRp = false;
      bool umVXiYzjNk = false;
      bool BGUfGcsRPs = false;
      bool pDzAHjxDmh = false;
      string dNhZuCinwf;
      string BjoBRNIMIG;
      string xkKHGwjzdC;
      string QAdnXbwkqz;
      string eOMAsujhKU;
      string DChjrrDZTz;
      string RiKsOAFAdo;
      string QXUIbhYJNK;
      string LCoIzORswe;
      string YVQrhuETls;
      string oiDUDfhZIJ;
      string TsMInPtBtA;
      string iLEyQuGcZf;
      string dFXUUcyUFS;
      string frjlLfJHES;
      string BDYkKddEEH;
      string YEzceOUqmK;
      string QZuaTqaSmj;
      string kzYHdaflKq;
      string ysPxtarHGw;
      if(dNhZuCinwf == oiDUDfhZIJ){KSUsBbHyQT = true;}
      else if(oiDUDfhZIJ == dNhZuCinwf){lBCWZuNMQN = true;}
      if(BjoBRNIMIG == TsMInPtBtA){CLRTWZfryE = true;}
      else if(TsMInPtBtA == BjoBRNIMIG){PuRFjFmGaU = true;}
      if(xkKHGwjzdC == iLEyQuGcZf){hhguMWJxfr = true;}
      else if(iLEyQuGcZf == xkKHGwjzdC){WqywWoALLc = true;}
      if(QAdnXbwkqz == dFXUUcyUFS){yTLpZSdfFC = true;}
      else if(dFXUUcyUFS == QAdnXbwkqz){kPSznsJAkC = true;}
      if(eOMAsujhKU == frjlLfJHES){ShVqolbwaU = true;}
      else if(frjlLfJHES == eOMAsujhKU){lyrOhlmspe = true;}
      if(DChjrrDZTz == BDYkKddEEH){uzICObkYfe = true;}
      else if(BDYkKddEEH == DChjrrDZTz){VIWBjtCGAj = true;}
      if(RiKsOAFAdo == YEzceOUqmK){RJRXUhAasD = true;}
      else if(YEzceOUqmK == RiKsOAFAdo){tBAnbzbSRp = true;}
      if(QXUIbhYJNK == QZuaTqaSmj){uAlwkAMpGZ = true;}
      if(LCoIzORswe == kzYHdaflKq){tMWKxzKIbx = true;}
      if(YVQrhuETls == ysPxtarHGw){gFzajIPxWG = true;}
      while(QZuaTqaSmj == QXUIbhYJNK){umVXiYzjNk = true;}
      while(kzYHdaflKq == kzYHdaflKq){BGUfGcsRPs = true;}
      while(ysPxtarHGw == ysPxtarHGw){pDzAHjxDmh = true;}
      if(KSUsBbHyQT == true){KSUsBbHyQT = false;}
      if(CLRTWZfryE == true){CLRTWZfryE = false;}
      if(hhguMWJxfr == true){hhguMWJxfr = false;}
      if(yTLpZSdfFC == true){yTLpZSdfFC = false;}
      if(ShVqolbwaU == true){ShVqolbwaU = false;}
      if(uzICObkYfe == true){uzICObkYfe = false;}
      if(RJRXUhAasD == true){RJRXUhAasD = false;}
      if(uAlwkAMpGZ == true){uAlwkAMpGZ = false;}
      if(tMWKxzKIbx == true){tMWKxzKIbx = false;}
      if(gFzajIPxWG == true){gFzajIPxWG = false;}
      if(lBCWZuNMQN == true){lBCWZuNMQN = false;}
      if(PuRFjFmGaU == true){PuRFjFmGaU = false;}
      if(WqywWoALLc == true){WqywWoALLc = false;}
      if(kPSznsJAkC == true){kPSznsJAkC = false;}
      if(lyrOhlmspe == true){lyrOhlmspe = false;}
      if(VIWBjtCGAj == true){VIWBjtCGAj = false;}
      if(tBAnbzbSRp == true){tBAnbzbSRp = false;}
      if(umVXiYzjNk == true){umVXiYzjNk = false;}
      if(BGUfGcsRPs == true){BGUfGcsRPs = false;}
      if(pDzAHjxDmh == true){pDzAHjxDmh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TXFUVMYLUN
{ 
  void WmMrtsWMmI()
  { 
      bool UsZTgxlEdn = false;
      bool UVYUkIeOph = false;
      bool kwOACnfMDf = false;
      bool ladudPcUzB = false;
      bool iyZuoogXKj = false;
      bool PflhHXeYQr = false;
      bool RZAxCtqdqV = false;
      bool eJOozlVSLM = false;
      bool HHBTPFnwmF = false;
      bool kEDGjIxbsu = false;
      bool yDgoEFQxhV = false;
      bool BLNDkJXghw = false;
      bool FtpkkaFHFp = false;
      bool ntZQOEaMOK = false;
      bool oqNRDYqAVZ = false;
      bool jQtwpDMuEd = false;
      bool zIrrgHlxog = false;
      bool iLSWHNgYhL = false;
      bool jFleFXzcaK = false;
      bool qfIjKfzUku = false;
      string PHxMfuORfq;
      string GTXTnpeMEO;
      string qQuzilegeZ;
      string tsRUYpsKRG;
      string mfJrDAgcir;
      string UmBlfzMydt;
      string QglGxNCDtx;
      string wUuyaKHDuh;
      string ECxmEGreoY;
      string dugXpFtCtp;
      string xdhlwArCLU;
      string rIDuoOjzBp;
      string VXOUSBnXIU;
      string QEIEjaTLpE;
      string OoTTgUrkhb;
      string VuBEUZPNSt;
      string LTtpEnAyLN;
      string tXIwafEtny;
      string JDofzVCDjK;
      string LGrwsttcPs;
      if(PHxMfuORfq == xdhlwArCLU){UsZTgxlEdn = true;}
      else if(xdhlwArCLU == PHxMfuORfq){yDgoEFQxhV = true;}
      if(GTXTnpeMEO == rIDuoOjzBp){UVYUkIeOph = true;}
      else if(rIDuoOjzBp == GTXTnpeMEO){BLNDkJXghw = true;}
      if(qQuzilegeZ == VXOUSBnXIU){kwOACnfMDf = true;}
      else if(VXOUSBnXIU == qQuzilegeZ){FtpkkaFHFp = true;}
      if(tsRUYpsKRG == QEIEjaTLpE){ladudPcUzB = true;}
      else if(QEIEjaTLpE == tsRUYpsKRG){ntZQOEaMOK = true;}
      if(mfJrDAgcir == OoTTgUrkhb){iyZuoogXKj = true;}
      else if(OoTTgUrkhb == mfJrDAgcir){oqNRDYqAVZ = true;}
      if(UmBlfzMydt == VuBEUZPNSt){PflhHXeYQr = true;}
      else if(VuBEUZPNSt == UmBlfzMydt){jQtwpDMuEd = true;}
      if(QglGxNCDtx == LTtpEnAyLN){RZAxCtqdqV = true;}
      else if(LTtpEnAyLN == QglGxNCDtx){zIrrgHlxog = true;}
      if(wUuyaKHDuh == tXIwafEtny){eJOozlVSLM = true;}
      if(ECxmEGreoY == JDofzVCDjK){HHBTPFnwmF = true;}
      if(dugXpFtCtp == LGrwsttcPs){kEDGjIxbsu = true;}
      while(tXIwafEtny == wUuyaKHDuh){iLSWHNgYhL = true;}
      while(JDofzVCDjK == JDofzVCDjK){jFleFXzcaK = true;}
      while(LGrwsttcPs == LGrwsttcPs){qfIjKfzUku = true;}
      if(UsZTgxlEdn == true){UsZTgxlEdn = false;}
      if(UVYUkIeOph == true){UVYUkIeOph = false;}
      if(kwOACnfMDf == true){kwOACnfMDf = false;}
      if(ladudPcUzB == true){ladudPcUzB = false;}
      if(iyZuoogXKj == true){iyZuoogXKj = false;}
      if(PflhHXeYQr == true){PflhHXeYQr = false;}
      if(RZAxCtqdqV == true){RZAxCtqdqV = false;}
      if(eJOozlVSLM == true){eJOozlVSLM = false;}
      if(HHBTPFnwmF == true){HHBTPFnwmF = false;}
      if(kEDGjIxbsu == true){kEDGjIxbsu = false;}
      if(yDgoEFQxhV == true){yDgoEFQxhV = false;}
      if(BLNDkJXghw == true){BLNDkJXghw = false;}
      if(FtpkkaFHFp == true){FtpkkaFHFp = false;}
      if(ntZQOEaMOK == true){ntZQOEaMOK = false;}
      if(oqNRDYqAVZ == true){oqNRDYqAVZ = false;}
      if(jQtwpDMuEd == true){jQtwpDMuEd = false;}
      if(zIrrgHlxog == true){zIrrgHlxog = false;}
      if(iLSWHNgYhL == true){iLSWHNgYhL = false;}
      if(jFleFXzcaK == true){jFleFXzcaK = false;}
      if(qfIjKfzUku == true){qfIjKfzUku = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QXKUHYLGWJ
{ 
  void eoXFQDJJAy()
  { 
      bool DgzaPSriIP = false;
      bool CkaJJuMmfw = false;
      bool qUCEoNGMak = false;
      bool lXodlmlJay = false;
      bool fipaAydjAG = false;
      bool rrkQjhdtlC = false;
      bool LfIXcewxXW = false;
      bool JDMhQIebEq = false;
      bool iVMUstlYsD = false;
      bool IrWXlAZRyV = false;
      bool BfMcwnfDzb = false;
      bool DCouSpTnei = false;
      bool rXEUOQfnuP = false;
      bool hMcioCJiXE = false;
      bool NhYQzGCbFw = false;
      bool glmOcdbrNe = false;
      bool IrIjtpYGGP = false;
      bool gjPZUKymUI = false;
      bool OEhziuZNFK = false;
      bool aQUruUZoWJ = false;
      string eQjbqCUrDd;
      string SUyZxeHTGN;
      string MqKihzrTVj;
      string AcYTLusEmw;
      string OxpUAqDkNJ;
      string bOOeZnGAtq;
      string KAWSdpweNB;
      string lDfKyPBoip;
      string uHFLHkNtsX;
      string orKukOaWqK;
      string uYWMXYhDfK;
      string mRRDuDtKLr;
      string bCkpMtrkYj;
      string ndxYuWksnh;
      string CJNikWZHzh;
      string TPLyhrmfzd;
      string gxdwVITsIY;
      string RBWcpRoCFo;
      string TkkqQYRypD;
      string iEtKBEfRMb;
      if(eQjbqCUrDd == uYWMXYhDfK){DgzaPSriIP = true;}
      else if(uYWMXYhDfK == eQjbqCUrDd){BfMcwnfDzb = true;}
      if(SUyZxeHTGN == mRRDuDtKLr){CkaJJuMmfw = true;}
      else if(mRRDuDtKLr == SUyZxeHTGN){DCouSpTnei = true;}
      if(MqKihzrTVj == bCkpMtrkYj){qUCEoNGMak = true;}
      else if(bCkpMtrkYj == MqKihzrTVj){rXEUOQfnuP = true;}
      if(AcYTLusEmw == ndxYuWksnh){lXodlmlJay = true;}
      else if(ndxYuWksnh == AcYTLusEmw){hMcioCJiXE = true;}
      if(OxpUAqDkNJ == CJNikWZHzh){fipaAydjAG = true;}
      else if(CJNikWZHzh == OxpUAqDkNJ){NhYQzGCbFw = true;}
      if(bOOeZnGAtq == TPLyhrmfzd){rrkQjhdtlC = true;}
      else if(TPLyhrmfzd == bOOeZnGAtq){glmOcdbrNe = true;}
      if(KAWSdpweNB == gxdwVITsIY){LfIXcewxXW = true;}
      else if(gxdwVITsIY == KAWSdpweNB){IrIjtpYGGP = true;}
      if(lDfKyPBoip == RBWcpRoCFo){JDMhQIebEq = true;}
      if(uHFLHkNtsX == TkkqQYRypD){iVMUstlYsD = true;}
      if(orKukOaWqK == iEtKBEfRMb){IrWXlAZRyV = true;}
      while(RBWcpRoCFo == lDfKyPBoip){gjPZUKymUI = true;}
      while(TkkqQYRypD == TkkqQYRypD){OEhziuZNFK = true;}
      while(iEtKBEfRMb == iEtKBEfRMb){aQUruUZoWJ = true;}
      if(DgzaPSriIP == true){DgzaPSriIP = false;}
      if(CkaJJuMmfw == true){CkaJJuMmfw = false;}
      if(qUCEoNGMak == true){qUCEoNGMak = false;}
      if(lXodlmlJay == true){lXodlmlJay = false;}
      if(fipaAydjAG == true){fipaAydjAG = false;}
      if(rrkQjhdtlC == true){rrkQjhdtlC = false;}
      if(LfIXcewxXW == true){LfIXcewxXW = false;}
      if(JDMhQIebEq == true){JDMhQIebEq = false;}
      if(iVMUstlYsD == true){iVMUstlYsD = false;}
      if(IrWXlAZRyV == true){IrWXlAZRyV = false;}
      if(BfMcwnfDzb == true){BfMcwnfDzb = false;}
      if(DCouSpTnei == true){DCouSpTnei = false;}
      if(rXEUOQfnuP == true){rXEUOQfnuP = false;}
      if(hMcioCJiXE == true){hMcioCJiXE = false;}
      if(NhYQzGCbFw == true){NhYQzGCbFw = false;}
      if(glmOcdbrNe == true){glmOcdbrNe = false;}
      if(IrIjtpYGGP == true){IrIjtpYGGP = false;}
      if(gjPZUKymUI == true){gjPZUKymUI = false;}
      if(OEhziuZNFK == true){OEhziuZNFK = false;}
      if(aQUruUZoWJ == true){aQUruUZoWJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HNWOFFRQGQ
{ 
  void zVyqYNHdOY()
  { 
      bool ncOkhdJEIg = false;
      bool KEtFDcPCuu = false;
      bool GfjBBnGSjp = false;
      bool xPWjGVSHcS = false;
      bool NiLdNmXoqN = false;
      bool nHeKzHrMis = false;
      bool WpTSitgJzh = false;
      bool KIYbhXTGnO = false;
      bool PQbVBokMjy = false;
      bool cFXiuWOstS = false;
      bool FOpJDehCcb = false;
      bool mlYUdGOyQt = false;
      bool JUZAEFjpgK = false;
      bool JaLUJBaRRV = false;
      bool GhiHKpfDFo = false;
      bool HPbAJjnoEy = false;
      bool trVRSMaEKc = false;
      bool exfumakRpN = false;
      bool ZgjqCszLLY = false;
      bool NlMTaNMRoy = false;
      string ewGbMFoWjs;
      string CMYHQQkukL;
      string DrpuriPMlZ;
      string spOiBSbYan;
      string FVRJeHYigO;
      string rAIawmFKjc;
      string pckKzMxoGx;
      string nLUwFgZgQj;
      string JfeXhrhnmN;
      string NRoxyckHJR;
      string KjcjZgfLUO;
      string MXsASJxMbG;
      string dJBriWVWyc;
      string wSXyZZDuyB;
      string MWSYBoXodn;
      string fYeCnBhkAC;
      string KIMrStAuZs;
      string GBOatHpcqt;
      string ygrKxWmUKY;
      string qSuuqEJZFG;
      if(ewGbMFoWjs == KjcjZgfLUO){ncOkhdJEIg = true;}
      else if(KjcjZgfLUO == ewGbMFoWjs){FOpJDehCcb = true;}
      if(CMYHQQkukL == MXsASJxMbG){KEtFDcPCuu = true;}
      else if(MXsASJxMbG == CMYHQQkukL){mlYUdGOyQt = true;}
      if(DrpuriPMlZ == dJBriWVWyc){GfjBBnGSjp = true;}
      else if(dJBriWVWyc == DrpuriPMlZ){JUZAEFjpgK = true;}
      if(spOiBSbYan == wSXyZZDuyB){xPWjGVSHcS = true;}
      else if(wSXyZZDuyB == spOiBSbYan){JaLUJBaRRV = true;}
      if(FVRJeHYigO == MWSYBoXodn){NiLdNmXoqN = true;}
      else if(MWSYBoXodn == FVRJeHYigO){GhiHKpfDFo = true;}
      if(rAIawmFKjc == fYeCnBhkAC){nHeKzHrMis = true;}
      else if(fYeCnBhkAC == rAIawmFKjc){HPbAJjnoEy = true;}
      if(pckKzMxoGx == KIMrStAuZs){WpTSitgJzh = true;}
      else if(KIMrStAuZs == pckKzMxoGx){trVRSMaEKc = true;}
      if(nLUwFgZgQj == GBOatHpcqt){KIYbhXTGnO = true;}
      if(JfeXhrhnmN == ygrKxWmUKY){PQbVBokMjy = true;}
      if(NRoxyckHJR == qSuuqEJZFG){cFXiuWOstS = true;}
      while(GBOatHpcqt == nLUwFgZgQj){exfumakRpN = true;}
      while(ygrKxWmUKY == ygrKxWmUKY){ZgjqCszLLY = true;}
      while(qSuuqEJZFG == qSuuqEJZFG){NlMTaNMRoy = true;}
      if(ncOkhdJEIg == true){ncOkhdJEIg = false;}
      if(KEtFDcPCuu == true){KEtFDcPCuu = false;}
      if(GfjBBnGSjp == true){GfjBBnGSjp = false;}
      if(xPWjGVSHcS == true){xPWjGVSHcS = false;}
      if(NiLdNmXoqN == true){NiLdNmXoqN = false;}
      if(nHeKzHrMis == true){nHeKzHrMis = false;}
      if(WpTSitgJzh == true){WpTSitgJzh = false;}
      if(KIYbhXTGnO == true){KIYbhXTGnO = false;}
      if(PQbVBokMjy == true){PQbVBokMjy = false;}
      if(cFXiuWOstS == true){cFXiuWOstS = false;}
      if(FOpJDehCcb == true){FOpJDehCcb = false;}
      if(mlYUdGOyQt == true){mlYUdGOyQt = false;}
      if(JUZAEFjpgK == true){JUZAEFjpgK = false;}
      if(JaLUJBaRRV == true){JaLUJBaRRV = false;}
      if(GhiHKpfDFo == true){GhiHKpfDFo = false;}
      if(HPbAJjnoEy == true){HPbAJjnoEy = false;}
      if(trVRSMaEKc == true){trVRSMaEKc = false;}
      if(exfumakRpN == true){exfumakRpN = false;}
      if(ZgjqCszLLY == true){ZgjqCszLLY = false;}
      if(NlMTaNMRoy == true){NlMTaNMRoy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KBETIVTGEE
{ 
  void SnlKcBxPVW()
  { 
      bool MrbFSnzscg = false;
      bool QEjZqxEiwt = false;
      bool yKIodhYLAX = false;
      bool rGmBzytDMr = false;
      bool uaUKPeNhdc = false;
      bool DwMGMBimaj = false;
      bool OnsFoJRiar = false;
      bool DBWDzWoxZz = false;
      bool UqhWTwtgnx = false;
      bool PHbbdGhPVF = false;
      bool NdHkZBZJGo = false;
      bool LkMbPXGVkr = false;
      bool PjtccuZtZr = false;
      bool oYbUlpiwxR = false;
      bool WjZzkeuzMF = false;
      bool ALedocidId = false;
      bool bejNAmJqpY = false;
      bool nJYSVfKuqx = false;
      bool AZhTrctxeI = false;
      bool HEnSpqALzy = false;
      string QhRbFLiUmB;
      string iGrFpqSpkf;
      string HcwwuLBwQe;
      string lepHaXNOEh;
      string iSyaayISku;
      string tataDmkUfs;
      string JmEHODPjdS;
      string cDlCxneUVw;
      string CiLUkLkOEm;
      string lshKYwOpMX;
      string hYnRRpoqdO;
      string IQzjqaaiVD;
      string RBeqgjUbcB;
      string ZoHyNdtsCu;
      string VtkpeUsySy;
      string UeTJFgtxkh;
      string UNOboTIBVN;
      string fgfagXPoML;
      string pWIeftUyrf;
      string jxIUaIeIBL;
      if(QhRbFLiUmB == hYnRRpoqdO){MrbFSnzscg = true;}
      else if(hYnRRpoqdO == QhRbFLiUmB){NdHkZBZJGo = true;}
      if(iGrFpqSpkf == IQzjqaaiVD){QEjZqxEiwt = true;}
      else if(IQzjqaaiVD == iGrFpqSpkf){LkMbPXGVkr = true;}
      if(HcwwuLBwQe == RBeqgjUbcB){yKIodhYLAX = true;}
      else if(RBeqgjUbcB == HcwwuLBwQe){PjtccuZtZr = true;}
      if(lepHaXNOEh == ZoHyNdtsCu){rGmBzytDMr = true;}
      else if(ZoHyNdtsCu == lepHaXNOEh){oYbUlpiwxR = true;}
      if(iSyaayISku == VtkpeUsySy){uaUKPeNhdc = true;}
      else if(VtkpeUsySy == iSyaayISku){WjZzkeuzMF = true;}
      if(tataDmkUfs == UeTJFgtxkh){DwMGMBimaj = true;}
      else if(UeTJFgtxkh == tataDmkUfs){ALedocidId = true;}
      if(JmEHODPjdS == UNOboTIBVN){OnsFoJRiar = true;}
      else if(UNOboTIBVN == JmEHODPjdS){bejNAmJqpY = true;}
      if(cDlCxneUVw == fgfagXPoML){DBWDzWoxZz = true;}
      if(CiLUkLkOEm == pWIeftUyrf){UqhWTwtgnx = true;}
      if(lshKYwOpMX == jxIUaIeIBL){PHbbdGhPVF = true;}
      while(fgfagXPoML == cDlCxneUVw){nJYSVfKuqx = true;}
      while(pWIeftUyrf == pWIeftUyrf){AZhTrctxeI = true;}
      while(jxIUaIeIBL == jxIUaIeIBL){HEnSpqALzy = true;}
      if(MrbFSnzscg == true){MrbFSnzscg = false;}
      if(QEjZqxEiwt == true){QEjZqxEiwt = false;}
      if(yKIodhYLAX == true){yKIodhYLAX = false;}
      if(rGmBzytDMr == true){rGmBzytDMr = false;}
      if(uaUKPeNhdc == true){uaUKPeNhdc = false;}
      if(DwMGMBimaj == true){DwMGMBimaj = false;}
      if(OnsFoJRiar == true){OnsFoJRiar = false;}
      if(DBWDzWoxZz == true){DBWDzWoxZz = false;}
      if(UqhWTwtgnx == true){UqhWTwtgnx = false;}
      if(PHbbdGhPVF == true){PHbbdGhPVF = false;}
      if(NdHkZBZJGo == true){NdHkZBZJGo = false;}
      if(LkMbPXGVkr == true){LkMbPXGVkr = false;}
      if(PjtccuZtZr == true){PjtccuZtZr = false;}
      if(oYbUlpiwxR == true){oYbUlpiwxR = false;}
      if(WjZzkeuzMF == true){WjZzkeuzMF = false;}
      if(ALedocidId == true){ALedocidId = false;}
      if(bejNAmJqpY == true){bejNAmJqpY = false;}
      if(nJYSVfKuqx == true){nJYSVfKuqx = false;}
      if(AZhTrctxeI == true){AZhTrctxeI = false;}
      if(HEnSpqALzy == true){HEnSpqALzy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NUXXNDGKXZ
{ 
  void uIbbHZXPRa()
  { 
      bool DSmcSJkcjL = false;
      bool hhAQFrsuqo = false;
      bool dlGagewUqb = false;
      bool zSPBrMyqHV = false;
      bool gSguEeieHR = false;
      bool rZuwXRMLwn = false;
      bool NQkIMPRzXs = false;
      bool tCmUHLFKVC = false;
      bool uQMZiYWTca = false;
      bool AmtSIQgYio = false;
      bool MjGOXolanM = false;
      bool LBotrwDLYm = false;
      bool syVxrGHULq = false;
      bool dgbgoLKyBs = false;
      bool mweQPzxAaM = false;
      bool MVzuuONJVQ = false;
      bool hROwidYIEf = false;
      bool lEJeAxSFhs = false;
      bool JHszeHgfka = false;
      bool xAckLVgihk = false;
      string WdsnCzqcAf;
      string anyxiXskDN;
      string OUsHQkXQyC;
      string PsHRiIXOeK;
      string cdUXZkKzqA;
      string wLWqeCkkWQ;
      string aZexPhggNa;
      string AeGrkkzUgf;
      string ZYZyGEVQmg;
      string WlrNjCzWHr;
      string EdkQzRFeFs;
      string DPDppCAfqL;
      string LPtgDOmrIh;
      string lbMobwmIyo;
      string yqKscGhBXh;
      string BSfwgniEMk;
      string dNVXHaCOOt;
      string OrhCMUFBDw;
      string fkTafSwQHm;
      string MiuMKkUmkC;
      if(WdsnCzqcAf == EdkQzRFeFs){DSmcSJkcjL = true;}
      else if(EdkQzRFeFs == WdsnCzqcAf){MjGOXolanM = true;}
      if(anyxiXskDN == DPDppCAfqL){hhAQFrsuqo = true;}
      else if(DPDppCAfqL == anyxiXskDN){LBotrwDLYm = true;}
      if(OUsHQkXQyC == LPtgDOmrIh){dlGagewUqb = true;}
      else if(LPtgDOmrIh == OUsHQkXQyC){syVxrGHULq = true;}
      if(PsHRiIXOeK == lbMobwmIyo){zSPBrMyqHV = true;}
      else if(lbMobwmIyo == PsHRiIXOeK){dgbgoLKyBs = true;}
      if(cdUXZkKzqA == yqKscGhBXh){gSguEeieHR = true;}
      else if(yqKscGhBXh == cdUXZkKzqA){mweQPzxAaM = true;}
      if(wLWqeCkkWQ == BSfwgniEMk){rZuwXRMLwn = true;}
      else if(BSfwgniEMk == wLWqeCkkWQ){MVzuuONJVQ = true;}
      if(aZexPhggNa == dNVXHaCOOt){NQkIMPRzXs = true;}
      else if(dNVXHaCOOt == aZexPhggNa){hROwidYIEf = true;}
      if(AeGrkkzUgf == OrhCMUFBDw){tCmUHLFKVC = true;}
      if(ZYZyGEVQmg == fkTafSwQHm){uQMZiYWTca = true;}
      if(WlrNjCzWHr == MiuMKkUmkC){AmtSIQgYio = true;}
      while(OrhCMUFBDw == AeGrkkzUgf){lEJeAxSFhs = true;}
      while(fkTafSwQHm == fkTafSwQHm){JHszeHgfka = true;}
      while(MiuMKkUmkC == MiuMKkUmkC){xAckLVgihk = true;}
      if(DSmcSJkcjL == true){DSmcSJkcjL = false;}
      if(hhAQFrsuqo == true){hhAQFrsuqo = false;}
      if(dlGagewUqb == true){dlGagewUqb = false;}
      if(zSPBrMyqHV == true){zSPBrMyqHV = false;}
      if(gSguEeieHR == true){gSguEeieHR = false;}
      if(rZuwXRMLwn == true){rZuwXRMLwn = false;}
      if(NQkIMPRzXs == true){NQkIMPRzXs = false;}
      if(tCmUHLFKVC == true){tCmUHLFKVC = false;}
      if(uQMZiYWTca == true){uQMZiYWTca = false;}
      if(AmtSIQgYio == true){AmtSIQgYio = false;}
      if(MjGOXolanM == true){MjGOXolanM = false;}
      if(LBotrwDLYm == true){LBotrwDLYm = false;}
      if(syVxrGHULq == true){syVxrGHULq = false;}
      if(dgbgoLKyBs == true){dgbgoLKyBs = false;}
      if(mweQPzxAaM == true){mweQPzxAaM = false;}
      if(MVzuuONJVQ == true){MVzuuONJVQ = false;}
      if(hROwidYIEf == true){hROwidYIEf = false;}
      if(lEJeAxSFhs == true){lEJeAxSFhs = false;}
      if(JHszeHgfka == true){JHszeHgfka = false;}
      if(xAckLVgihk == true){xAckLVgihk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GYDWIWHGRW
{ 
  void SxrSSBCsmI()
  { 
      bool SDLPLGMDok = false;
      bool dKUrPxxKOu = false;
      bool acdVUMOyhI = false;
      bool kbhXhjhnff = false;
      bool ntQxIhrXTH = false;
      bool KZfWbpYouz = false;
      bool qOVgzCbwJf = false;
      bool OJdiHfLgNl = false;
      bool TqdZxLwKwr = false;
      bool LrrgnYYjxF = false;
      bool GwNnsBwwPu = false;
      bool dqbIfAkuin = false;
      bool GQARTVRxuh = false;
      bool HajHfWcogw = false;
      bool PzuANTQiBn = false;
      bool ncAIzowwTX = false;
      bool jyAgmCHTcI = false;
      bool XuOmYGVzEA = false;
      bool EhwHtdabIq = false;
      bool afVIMQyNMK = false;
      string KqYUmlCzid;
      string lbpLuHHdJR;
      string BfyKOkwHeu;
      string IEoQTriYzJ;
      string UlPDAGCpAh;
      string pOhUHdrNFB;
      string ouTnUglZrD;
      string YiezwOQuJI;
      string hGGxEsWTIo;
      string zUSxUZRahS;
      string TcxxIHihXs;
      string NxDxSinWja;
      string KSQCDEPheW;
      string woNpnFIJnw;
      string JnuPaCQUdl;
      string kuqGIBLusE;
      string qBDAwYiMJN;
      string ZehmQWWBaB;
      string ntDrlByGhm;
      string sNPjEIktSC;
      if(KqYUmlCzid == TcxxIHihXs){SDLPLGMDok = true;}
      else if(TcxxIHihXs == KqYUmlCzid){GwNnsBwwPu = true;}
      if(lbpLuHHdJR == NxDxSinWja){dKUrPxxKOu = true;}
      else if(NxDxSinWja == lbpLuHHdJR){dqbIfAkuin = true;}
      if(BfyKOkwHeu == KSQCDEPheW){acdVUMOyhI = true;}
      else if(KSQCDEPheW == BfyKOkwHeu){GQARTVRxuh = true;}
      if(IEoQTriYzJ == woNpnFIJnw){kbhXhjhnff = true;}
      else if(woNpnFIJnw == IEoQTriYzJ){HajHfWcogw = true;}
      if(UlPDAGCpAh == JnuPaCQUdl){ntQxIhrXTH = true;}
      else if(JnuPaCQUdl == UlPDAGCpAh){PzuANTQiBn = true;}
      if(pOhUHdrNFB == kuqGIBLusE){KZfWbpYouz = true;}
      else if(kuqGIBLusE == pOhUHdrNFB){ncAIzowwTX = true;}
      if(ouTnUglZrD == qBDAwYiMJN){qOVgzCbwJf = true;}
      else if(qBDAwYiMJN == ouTnUglZrD){jyAgmCHTcI = true;}
      if(YiezwOQuJI == ZehmQWWBaB){OJdiHfLgNl = true;}
      if(hGGxEsWTIo == ntDrlByGhm){TqdZxLwKwr = true;}
      if(zUSxUZRahS == sNPjEIktSC){LrrgnYYjxF = true;}
      while(ZehmQWWBaB == YiezwOQuJI){XuOmYGVzEA = true;}
      while(ntDrlByGhm == ntDrlByGhm){EhwHtdabIq = true;}
      while(sNPjEIktSC == sNPjEIktSC){afVIMQyNMK = true;}
      if(SDLPLGMDok == true){SDLPLGMDok = false;}
      if(dKUrPxxKOu == true){dKUrPxxKOu = false;}
      if(acdVUMOyhI == true){acdVUMOyhI = false;}
      if(kbhXhjhnff == true){kbhXhjhnff = false;}
      if(ntQxIhrXTH == true){ntQxIhrXTH = false;}
      if(KZfWbpYouz == true){KZfWbpYouz = false;}
      if(qOVgzCbwJf == true){qOVgzCbwJf = false;}
      if(OJdiHfLgNl == true){OJdiHfLgNl = false;}
      if(TqdZxLwKwr == true){TqdZxLwKwr = false;}
      if(LrrgnYYjxF == true){LrrgnYYjxF = false;}
      if(GwNnsBwwPu == true){GwNnsBwwPu = false;}
      if(dqbIfAkuin == true){dqbIfAkuin = false;}
      if(GQARTVRxuh == true){GQARTVRxuh = false;}
      if(HajHfWcogw == true){HajHfWcogw = false;}
      if(PzuANTQiBn == true){PzuANTQiBn = false;}
      if(ncAIzowwTX == true){ncAIzowwTX = false;}
      if(jyAgmCHTcI == true){jyAgmCHTcI = false;}
      if(XuOmYGVzEA == true){XuOmYGVzEA = false;}
      if(EhwHtdabIq == true){EhwHtdabIq = false;}
      if(afVIMQyNMK == true){afVIMQyNMK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EYNUAYDRQM
{ 
  void yIIGVDTGfs()
  { 
      bool ampNDPSaTd = false;
      bool KyFPuxqyRY = false;
      bool rfLctPANUX = false;
      bool mPBtqjQttI = false;
      bool GtPSPKzWyC = false;
      bool BhoYLubMTm = false;
      bool PFGwquwKYL = false;
      bool fwDJSxQsNi = false;
      bool QdORVFZciw = false;
      bool IDaGsAnSaU = false;
      bool NnxlVEdfFN = false;
      bool ehzjWlpnZk = false;
      bool UTacDbVxQR = false;
      bool JxRrUbfbuQ = false;
      bool bsWVQZEpiG = false;
      bool KzrpztNUit = false;
      bool igPmDhQHOu = false;
      bool FNsIJbwFLc = false;
      bool XeNJHJEbra = false;
      bool NLsBhtciRi = false;
      string QXPdkNKQPK;
      string ZMXcDIpbcX;
      string CxcXEeInAc;
      string ljZiQTqgeG;
      string iJJQiqgfaC;
      string PUoHpTtrZG;
      string FWQmYpmnMi;
      string RIxWornLnM;
      string ybNxMQtRsw;
      string ZzGXBMsWrs;
      string ErTrkHXRSx;
      string eiDMHcISZI;
      string uVuPISBYVb;
      string zRTuIFIVLF;
      string rbywRputPX;
      string DZwjyhxDiS;
      string FzwpyNPIDC;
      string UmGUPTWzyS;
      string WHIyYYVixa;
      string IEmsArfHxD;
      if(QXPdkNKQPK == ErTrkHXRSx){ampNDPSaTd = true;}
      else if(ErTrkHXRSx == QXPdkNKQPK){NnxlVEdfFN = true;}
      if(ZMXcDIpbcX == eiDMHcISZI){KyFPuxqyRY = true;}
      else if(eiDMHcISZI == ZMXcDIpbcX){ehzjWlpnZk = true;}
      if(CxcXEeInAc == uVuPISBYVb){rfLctPANUX = true;}
      else if(uVuPISBYVb == CxcXEeInAc){UTacDbVxQR = true;}
      if(ljZiQTqgeG == zRTuIFIVLF){mPBtqjQttI = true;}
      else if(zRTuIFIVLF == ljZiQTqgeG){JxRrUbfbuQ = true;}
      if(iJJQiqgfaC == rbywRputPX){GtPSPKzWyC = true;}
      else if(rbywRputPX == iJJQiqgfaC){bsWVQZEpiG = true;}
      if(PUoHpTtrZG == DZwjyhxDiS){BhoYLubMTm = true;}
      else if(DZwjyhxDiS == PUoHpTtrZG){KzrpztNUit = true;}
      if(FWQmYpmnMi == FzwpyNPIDC){PFGwquwKYL = true;}
      else if(FzwpyNPIDC == FWQmYpmnMi){igPmDhQHOu = true;}
      if(RIxWornLnM == UmGUPTWzyS){fwDJSxQsNi = true;}
      if(ybNxMQtRsw == WHIyYYVixa){QdORVFZciw = true;}
      if(ZzGXBMsWrs == IEmsArfHxD){IDaGsAnSaU = true;}
      while(UmGUPTWzyS == RIxWornLnM){FNsIJbwFLc = true;}
      while(WHIyYYVixa == WHIyYYVixa){XeNJHJEbra = true;}
      while(IEmsArfHxD == IEmsArfHxD){NLsBhtciRi = true;}
      if(ampNDPSaTd == true){ampNDPSaTd = false;}
      if(KyFPuxqyRY == true){KyFPuxqyRY = false;}
      if(rfLctPANUX == true){rfLctPANUX = false;}
      if(mPBtqjQttI == true){mPBtqjQttI = false;}
      if(GtPSPKzWyC == true){GtPSPKzWyC = false;}
      if(BhoYLubMTm == true){BhoYLubMTm = false;}
      if(PFGwquwKYL == true){PFGwquwKYL = false;}
      if(fwDJSxQsNi == true){fwDJSxQsNi = false;}
      if(QdORVFZciw == true){QdORVFZciw = false;}
      if(IDaGsAnSaU == true){IDaGsAnSaU = false;}
      if(NnxlVEdfFN == true){NnxlVEdfFN = false;}
      if(ehzjWlpnZk == true){ehzjWlpnZk = false;}
      if(UTacDbVxQR == true){UTacDbVxQR = false;}
      if(JxRrUbfbuQ == true){JxRrUbfbuQ = false;}
      if(bsWVQZEpiG == true){bsWVQZEpiG = false;}
      if(KzrpztNUit == true){KzrpztNUit = false;}
      if(igPmDhQHOu == true){igPmDhQHOu = false;}
      if(FNsIJbwFLc == true){FNsIJbwFLc = false;}
      if(XeNJHJEbra == true){XeNJHJEbra = false;}
      if(NLsBhtciRi == true){NLsBhtciRi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DUPPIEMYIR
{ 
  void LqOtxTRkJV()
  { 
      bool VTMUipGzhy = false;
      bool MqdfAQQoVW = false;
      bool CmKbFyiPqd = false;
      bool bslKepiCZd = false;
      bool kBCpjlNYPo = false;
      bool xorbAiIjPj = false;
      bool GpIEVSESAK = false;
      bool gOOrlAkUrS = false;
      bool jKABfmBJKw = false;
      bool hylpWtsxUQ = false;
      bool guYEHiZzoz = false;
      bool ymrwzupGYh = false;
      bool RtHDcibYUq = false;
      bool HmAalolusw = false;
      bool NCUKytGppb = false;
      bool ElYlzlmUbY = false;
      bool GAexqKmQJK = false;
      bool JtMbUPZwFh = false;
      bool blismVONbA = false;
      bool BQSUpMWWTm = false;
      string ReyUXHBKsH;
      string VlZALeZTBz;
      string iDPVfHlMpQ;
      string tZiVWpoQET;
      string uMqhlidpxc;
      string DdOrPOOcnP;
      string VoTcMuCEdV;
      string oJOgDWMgjx;
      string dwONMQKqGI;
      string aMboyFrNVp;
      string fZMbmtOgnr;
      string ChsplZaGQu;
      string jLyUtcgZhy;
      string dyKsREilZS;
      string CdDNGsSkCY;
      string elxaFUaqgK;
      string MnzoODWzYh;
      string pnfxrGHjNB;
      string JuWJTqBjnx;
      string cqEPGOeNyC;
      if(ReyUXHBKsH == fZMbmtOgnr){VTMUipGzhy = true;}
      else if(fZMbmtOgnr == ReyUXHBKsH){guYEHiZzoz = true;}
      if(VlZALeZTBz == ChsplZaGQu){MqdfAQQoVW = true;}
      else if(ChsplZaGQu == VlZALeZTBz){ymrwzupGYh = true;}
      if(iDPVfHlMpQ == jLyUtcgZhy){CmKbFyiPqd = true;}
      else if(jLyUtcgZhy == iDPVfHlMpQ){RtHDcibYUq = true;}
      if(tZiVWpoQET == dyKsREilZS){bslKepiCZd = true;}
      else if(dyKsREilZS == tZiVWpoQET){HmAalolusw = true;}
      if(uMqhlidpxc == CdDNGsSkCY){kBCpjlNYPo = true;}
      else if(CdDNGsSkCY == uMqhlidpxc){NCUKytGppb = true;}
      if(DdOrPOOcnP == elxaFUaqgK){xorbAiIjPj = true;}
      else if(elxaFUaqgK == DdOrPOOcnP){ElYlzlmUbY = true;}
      if(VoTcMuCEdV == MnzoODWzYh){GpIEVSESAK = true;}
      else if(MnzoODWzYh == VoTcMuCEdV){GAexqKmQJK = true;}
      if(oJOgDWMgjx == pnfxrGHjNB){gOOrlAkUrS = true;}
      if(dwONMQKqGI == JuWJTqBjnx){jKABfmBJKw = true;}
      if(aMboyFrNVp == cqEPGOeNyC){hylpWtsxUQ = true;}
      while(pnfxrGHjNB == oJOgDWMgjx){JtMbUPZwFh = true;}
      while(JuWJTqBjnx == JuWJTqBjnx){blismVONbA = true;}
      while(cqEPGOeNyC == cqEPGOeNyC){BQSUpMWWTm = true;}
      if(VTMUipGzhy == true){VTMUipGzhy = false;}
      if(MqdfAQQoVW == true){MqdfAQQoVW = false;}
      if(CmKbFyiPqd == true){CmKbFyiPqd = false;}
      if(bslKepiCZd == true){bslKepiCZd = false;}
      if(kBCpjlNYPo == true){kBCpjlNYPo = false;}
      if(xorbAiIjPj == true){xorbAiIjPj = false;}
      if(GpIEVSESAK == true){GpIEVSESAK = false;}
      if(gOOrlAkUrS == true){gOOrlAkUrS = false;}
      if(jKABfmBJKw == true){jKABfmBJKw = false;}
      if(hylpWtsxUQ == true){hylpWtsxUQ = false;}
      if(guYEHiZzoz == true){guYEHiZzoz = false;}
      if(ymrwzupGYh == true){ymrwzupGYh = false;}
      if(RtHDcibYUq == true){RtHDcibYUq = false;}
      if(HmAalolusw == true){HmAalolusw = false;}
      if(NCUKytGppb == true){NCUKytGppb = false;}
      if(ElYlzlmUbY == true){ElYlzlmUbY = false;}
      if(GAexqKmQJK == true){GAexqKmQJK = false;}
      if(JtMbUPZwFh == true){JtMbUPZwFh = false;}
      if(blismVONbA == true){blismVONbA = false;}
      if(BQSUpMWWTm == true){BQSUpMWWTm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIHQKGNNVF
{ 
  void BoUysqkRwY()
  { 
      bool EbQJKHPttT = false;
      bool CLfTUaYPur = false;
      bool uYVjDPYGUm = false;
      bool mtkLTcczDO = false;
      bool hFVGtmNdBo = false;
      bool ckGHweFfFt = false;
      bool iJZHgIZTAr = false;
      bool yZLfJoDPoP = false;
      bool CtFeJBmdOo = false;
      bool WwsIfYeNYl = false;
      bool NsdIqCYZyH = false;
      bool bpqprnEuxe = false;
      bool UwFKUBgCAk = false;
      bool JopCCIQwmH = false;
      bool cMfGMfFCQr = false;
      bool TjQsRRnSmo = false;
      bool VWZNymAnmi = false;
      bool WIIpCHPyyo = false;
      bool wdlIQZXwkk = false;
      bool UyIxlFmSIZ = false;
      string PhbyLbfJuf;
      string HmRjnUeKoz;
      string EDgpOrlQjb;
      string TxpRcknLex;
      string HsUViHXiNi;
      string ehFHsLAkjT;
      string pPZSMJwzHC;
      string fSeqqKiKGG;
      string UDCAxlriXQ;
      string jCaKHqSBJY;
      string LXaLDLCNQh;
      string cpeczlNZVZ;
      string RNaqScqTjz;
      string rgAhuwcqwk;
      string jdRpntXyLU;
      string dsfjHyxirZ;
      string ThdQpwowhC;
      string JWckomukDY;
      string EsIOVyAQax;
      string zsyWQCABzr;
      if(PhbyLbfJuf == LXaLDLCNQh){EbQJKHPttT = true;}
      else if(LXaLDLCNQh == PhbyLbfJuf){NsdIqCYZyH = true;}
      if(HmRjnUeKoz == cpeczlNZVZ){CLfTUaYPur = true;}
      else if(cpeczlNZVZ == HmRjnUeKoz){bpqprnEuxe = true;}
      if(EDgpOrlQjb == RNaqScqTjz){uYVjDPYGUm = true;}
      else if(RNaqScqTjz == EDgpOrlQjb){UwFKUBgCAk = true;}
      if(TxpRcknLex == rgAhuwcqwk){mtkLTcczDO = true;}
      else if(rgAhuwcqwk == TxpRcknLex){JopCCIQwmH = true;}
      if(HsUViHXiNi == jdRpntXyLU){hFVGtmNdBo = true;}
      else if(jdRpntXyLU == HsUViHXiNi){cMfGMfFCQr = true;}
      if(ehFHsLAkjT == dsfjHyxirZ){ckGHweFfFt = true;}
      else if(dsfjHyxirZ == ehFHsLAkjT){TjQsRRnSmo = true;}
      if(pPZSMJwzHC == ThdQpwowhC){iJZHgIZTAr = true;}
      else if(ThdQpwowhC == pPZSMJwzHC){VWZNymAnmi = true;}
      if(fSeqqKiKGG == JWckomukDY){yZLfJoDPoP = true;}
      if(UDCAxlriXQ == EsIOVyAQax){CtFeJBmdOo = true;}
      if(jCaKHqSBJY == zsyWQCABzr){WwsIfYeNYl = true;}
      while(JWckomukDY == fSeqqKiKGG){WIIpCHPyyo = true;}
      while(EsIOVyAQax == EsIOVyAQax){wdlIQZXwkk = true;}
      while(zsyWQCABzr == zsyWQCABzr){UyIxlFmSIZ = true;}
      if(EbQJKHPttT == true){EbQJKHPttT = false;}
      if(CLfTUaYPur == true){CLfTUaYPur = false;}
      if(uYVjDPYGUm == true){uYVjDPYGUm = false;}
      if(mtkLTcczDO == true){mtkLTcczDO = false;}
      if(hFVGtmNdBo == true){hFVGtmNdBo = false;}
      if(ckGHweFfFt == true){ckGHweFfFt = false;}
      if(iJZHgIZTAr == true){iJZHgIZTAr = false;}
      if(yZLfJoDPoP == true){yZLfJoDPoP = false;}
      if(CtFeJBmdOo == true){CtFeJBmdOo = false;}
      if(WwsIfYeNYl == true){WwsIfYeNYl = false;}
      if(NsdIqCYZyH == true){NsdIqCYZyH = false;}
      if(bpqprnEuxe == true){bpqprnEuxe = false;}
      if(UwFKUBgCAk == true){UwFKUBgCAk = false;}
      if(JopCCIQwmH == true){JopCCIQwmH = false;}
      if(cMfGMfFCQr == true){cMfGMfFCQr = false;}
      if(TjQsRRnSmo == true){TjQsRRnSmo = false;}
      if(VWZNymAnmi == true){VWZNymAnmi = false;}
      if(WIIpCHPyyo == true){WIIpCHPyyo = false;}
      if(wdlIQZXwkk == true){wdlIQZXwkk = false;}
      if(UyIxlFmSIZ == true){UyIxlFmSIZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YIDZYKDITF
{ 
  void YOrebMinel()
  { 
      bool wVDRSBASrP = false;
      bool CNPMuTurSA = false;
      bool hZZxuuBuPE = false;
      bool BBMrYBukSj = false;
      bool jjFAaAcITK = false;
      bool YanTeWwGVX = false;
      bool zFCnOAAXns = false;
      bool XJYhPxTYVt = false;
      bool SsaFfaNrMB = false;
      bool FoPukdhQlZ = false;
      bool AEUZmOBFDg = false;
      bool DXjbFGexIm = false;
      bool lHKmnhtdxl = false;
      bool PClwtNXBSR = false;
      bool ZIofyhFnpd = false;
      bool zjIznrsgkE = false;
      bool TWHRQAkngq = false;
      bool hcdqMcSeoG = false;
      bool cGnTletmHB = false;
      bool TqPNxDBWOy = false;
      string UaEbzxFMih;
      string nzkPQApZzR;
      string dCQDtqJAiC;
      string uxDOPRHXBx;
      string GfisuaCXWw;
      string MAabdSJBgH;
      string nEdflpwWzy;
      string rSXCLxSWHS;
      string olclpuWbkx;
      string HGptJBCDHE;
      string efXYEscXPf;
      string AmsNSCbqpq;
      string TUkCpkbdsK;
      string uPOCnINEhw;
      string SyLExUNcaG;
      string YKMQkKtUhS;
      string RyeEkjXqZJ;
      string nXJtXUIgEV;
      string XyCllkCyQc;
      string OsVOdTSGTM;
      if(UaEbzxFMih == efXYEscXPf){wVDRSBASrP = true;}
      else if(efXYEscXPf == UaEbzxFMih){AEUZmOBFDg = true;}
      if(nzkPQApZzR == AmsNSCbqpq){CNPMuTurSA = true;}
      else if(AmsNSCbqpq == nzkPQApZzR){DXjbFGexIm = true;}
      if(dCQDtqJAiC == TUkCpkbdsK){hZZxuuBuPE = true;}
      else if(TUkCpkbdsK == dCQDtqJAiC){lHKmnhtdxl = true;}
      if(uxDOPRHXBx == uPOCnINEhw){BBMrYBukSj = true;}
      else if(uPOCnINEhw == uxDOPRHXBx){PClwtNXBSR = true;}
      if(GfisuaCXWw == SyLExUNcaG){jjFAaAcITK = true;}
      else if(SyLExUNcaG == GfisuaCXWw){ZIofyhFnpd = true;}
      if(MAabdSJBgH == YKMQkKtUhS){YanTeWwGVX = true;}
      else if(YKMQkKtUhS == MAabdSJBgH){zjIznrsgkE = true;}
      if(nEdflpwWzy == RyeEkjXqZJ){zFCnOAAXns = true;}
      else if(RyeEkjXqZJ == nEdflpwWzy){TWHRQAkngq = true;}
      if(rSXCLxSWHS == nXJtXUIgEV){XJYhPxTYVt = true;}
      if(olclpuWbkx == XyCllkCyQc){SsaFfaNrMB = true;}
      if(HGptJBCDHE == OsVOdTSGTM){FoPukdhQlZ = true;}
      while(nXJtXUIgEV == rSXCLxSWHS){hcdqMcSeoG = true;}
      while(XyCllkCyQc == XyCllkCyQc){cGnTletmHB = true;}
      while(OsVOdTSGTM == OsVOdTSGTM){TqPNxDBWOy = true;}
      if(wVDRSBASrP == true){wVDRSBASrP = false;}
      if(CNPMuTurSA == true){CNPMuTurSA = false;}
      if(hZZxuuBuPE == true){hZZxuuBuPE = false;}
      if(BBMrYBukSj == true){BBMrYBukSj = false;}
      if(jjFAaAcITK == true){jjFAaAcITK = false;}
      if(YanTeWwGVX == true){YanTeWwGVX = false;}
      if(zFCnOAAXns == true){zFCnOAAXns = false;}
      if(XJYhPxTYVt == true){XJYhPxTYVt = false;}
      if(SsaFfaNrMB == true){SsaFfaNrMB = false;}
      if(FoPukdhQlZ == true){FoPukdhQlZ = false;}
      if(AEUZmOBFDg == true){AEUZmOBFDg = false;}
      if(DXjbFGexIm == true){DXjbFGexIm = false;}
      if(lHKmnhtdxl == true){lHKmnhtdxl = false;}
      if(PClwtNXBSR == true){PClwtNXBSR = false;}
      if(ZIofyhFnpd == true){ZIofyhFnpd = false;}
      if(zjIznrsgkE == true){zjIznrsgkE = false;}
      if(TWHRQAkngq == true){TWHRQAkngq = false;}
      if(hcdqMcSeoG == true){hcdqMcSeoG = false;}
      if(cGnTletmHB == true){cGnTletmHB = false;}
      if(TqPNxDBWOy == true){TqPNxDBWOy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IECUUIOBZM
{ 
  void CyAPkbNNfq()
  { 
      bool PXFnrIXfGG = false;
      bool aiHijBrYOW = false;
      bool VIsubohdcF = false;
      bool zlWYwIqDXB = false;
      bool CQdJGnHSDr = false;
      bool tXjiiGeKMC = false;
      bool ZtDAGoMhla = false;
      bool JnANTEeinm = false;
      bool hPZjKbCmpo = false;
      bool dfqUaINcDR = false;
      bool bYgciFWVOd = false;
      bool bwWYUKTSpd = false;
      bool lYrwxdxelL = false;
      bool qBfWLJixBF = false;
      bool EfYLNgJRAQ = false;
      bool numYeCfjfF = false;
      bool HriCmZPANL = false;
      bool aWQjZGzgiP = false;
      bool TfdVWwOHqI = false;
      bool cyRwxLwVXm = false;
      string NXmPRIjzYw;
      string fzyWOMXbJu;
      string tZCIhKRnql;
      string yIwDeHmmbs;
      string UTFIGVkeZF;
      string ONTAnmVdhH;
      string quHlxWDtrH;
      string YkzPaaTsCL;
      string YlOkWjowPq;
      string kJEUBYLSLj;
      string SplRgdODYM;
      string TbbVhEgVPN;
      string gGeBVPfeNB;
      string PAhSsiAxEr;
      string VkWCXJhimx;
      string roDxCLLkuR;
      string yioXxSsJcz;
      string EjRWqujbdM;
      string gxqQJZxjPh;
      string WOBmtlwyFE;
      if(NXmPRIjzYw == SplRgdODYM){PXFnrIXfGG = true;}
      else if(SplRgdODYM == NXmPRIjzYw){bYgciFWVOd = true;}
      if(fzyWOMXbJu == TbbVhEgVPN){aiHijBrYOW = true;}
      else if(TbbVhEgVPN == fzyWOMXbJu){bwWYUKTSpd = true;}
      if(tZCIhKRnql == gGeBVPfeNB){VIsubohdcF = true;}
      else if(gGeBVPfeNB == tZCIhKRnql){lYrwxdxelL = true;}
      if(yIwDeHmmbs == PAhSsiAxEr){zlWYwIqDXB = true;}
      else if(PAhSsiAxEr == yIwDeHmmbs){qBfWLJixBF = true;}
      if(UTFIGVkeZF == VkWCXJhimx){CQdJGnHSDr = true;}
      else if(VkWCXJhimx == UTFIGVkeZF){EfYLNgJRAQ = true;}
      if(ONTAnmVdhH == roDxCLLkuR){tXjiiGeKMC = true;}
      else if(roDxCLLkuR == ONTAnmVdhH){numYeCfjfF = true;}
      if(quHlxWDtrH == yioXxSsJcz){ZtDAGoMhla = true;}
      else if(yioXxSsJcz == quHlxWDtrH){HriCmZPANL = true;}
      if(YkzPaaTsCL == EjRWqujbdM){JnANTEeinm = true;}
      if(YlOkWjowPq == gxqQJZxjPh){hPZjKbCmpo = true;}
      if(kJEUBYLSLj == WOBmtlwyFE){dfqUaINcDR = true;}
      while(EjRWqujbdM == YkzPaaTsCL){aWQjZGzgiP = true;}
      while(gxqQJZxjPh == gxqQJZxjPh){TfdVWwOHqI = true;}
      while(WOBmtlwyFE == WOBmtlwyFE){cyRwxLwVXm = true;}
      if(PXFnrIXfGG == true){PXFnrIXfGG = false;}
      if(aiHijBrYOW == true){aiHijBrYOW = false;}
      if(VIsubohdcF == true){VIsubohdcF = false;}
      if(zlWYwIqDXB == true){zlWYwIqDXB = false;}
      if(CQdJGnHSDr == true){CQdJGnHSDr = false;}
      if(tXjiiGeKMC == true){tXjiiGeKMC = false;}
      if(ZtDAGoMhla == true){ZtDAGoMhla = false;}
      if(JnANTEeinm == true){JnANTEeinm = false;}
      if(hPZjKbCmpo == true){hPZjKbCmpo = false;}
      if(dfqUaINcDR == true){dfqUaINcDR = false;}
      if(bYgciFWVOd == true){bYgciFWVOd = false;}
      if(bwWYUKTSpd == true){bwWYUKTSpd = false;}
      if(lYrwxdxelL == true){lYrwxdxelL = false;}
      if(qBfWLJixBF == true){qBfWLJixBF = false;}
      if(EfYLNgJRAQ == true){EfYLNgJRAQ = false;}
      if(numYeCfjfF == true){numYeCfjfF = false;}
      if(HriCmZPANL == true){HriCmZPANL = false;}
      if(aWQjZGzgiP == true){aWQjZGzgiP = false;}
      if(TfdVWwOHqI == true){TfdVWwOHqI = false;}
      if(cyRwxLwVXm == true){cyRwxLwVXm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TDXORCHLJI
{ 
  void mJsWOgugLf()
  { 
      bool DGaoQPqodw = false;
      bool CeWwTdrNWg = false;
      bool graURGuYHJ = false;
      bool wpmYGYrlrM = false;
      bool psOFJENLmK = false;
      bool QYXyrKfGWK = false;
      bool URgUALqypt = false;
      bool lFUKqmcUKN = false;
      bool silwrXSngu = false;
      bool rlOhqXMtFx = false;
      bool MPVrYKDNHF = false;
      bool hKuJQkfjbc = false;
      bool sDQtCAqmST = false;
      bool ZiPMAdNsXg = false;
      bool TFgbMhpEQF = false;
      bool qbRcEJyapY = false;
      bool TQtnezthJm = false;
      bool XmMuImVohT = false;
      bool JmVMbyQmIq = false;
      bool elCzNCLsxN = false;
      string AqoDLoZFIq;
      string GnXTsYGolF;
      string hTfXEifowH;
      string kNTuHcNnAO;
      string XSYxQloTVa;
      string sYNdhgKRyb;
      string JkIAGrTbMQ;
      string LRoXhOthGR;
      string tMSVOLzoNZ;
      string RuoXFlKYqX;
      string RMGEPajpuS;
      string lcLghwRmkt;
      string reOlyPbQSw;
      string EVphzgFOGn;
      string bJstnojIoI;
      string TXmxfmyUFz;
      string ySXzOPlcgA;
      string qDfxSikTxJ;
      string fTaJcgisCM;
      string ijIHoIltfY;
      if(AqoDLoZFIq == RMGEPajpuS){DGaoQPqodw = true;}
      else if(RMGEPajpuS == AqoDLoZFIq){MPVrYKDNHF = true;}
      if(GnXTsYGolF == lcLghwRmkt){CeWwTdrNWg = true;}
      else if(lcLghwRmkt == GnXTsYGolF){hKuJQkfjbc = true;}
      if(hTfXEifowH == reOlyPbQSw){graURGuYHJ = true;}
      else if(reOlyPbQSw == hTfXEifowH){sDQtCAqmST = true;}
      if(kNTuHcNnAO == EVphzgFOGn){wpmYGYrlrM = true;}
      else if(EVphzgFOGn == kNTuHcNnAO){ZiPMAdNsXg = true;}
      if(XSYxQloTVa == bJstnojIoI){psOFJENLmK = true;}
      else if(bJstnojIoI == XSYxQloTVa){TFgbMhpEQF = true;}
      if(sYNdhgKRyb == TXmxfmyUFz){QYXyrKfGWK = true;}
      else if(TXmxfmyUFz == sYNdhgKRyb){qbRcEJyapY = true;}
      if(JkIAGrTbMQ == ySXzOPlcgA){URgUALqypt = true;}
      else if(ySXzOPlcgA == JkIAGrTbMQ){TQtnezthJm = true;}
      if(LRoXhOthGR == qDfxSikTxJ){lFUKqmcUKN = true;}
      if(tMSVOLzoNZ == fTaJcgisCM){silwrXSngu = true;}
      if(RuoXFlKYqX == ijIHoIltfY){rlOhqXMtFx = true;}
      while(qDfxSikTxJ == LRoXhOthGR){XmMuImVohT = true;}
      while(fTaJcgisCM == fTaJcgisCM){JmVMbyQmIq = true;}
      while(ijIHoIltfY == ijIHoIltfY){elCzNCLsxN = true;}
      if(DGaoQPqodw == true){DGaoQPqodw = false;}
      if(CeWwTdrNWg == true){CeWwTdrNWg = false;}
      if(graURGuYHJ == true){graURGuYHJ = false;}
      if(wpmYGYrlrM == true){wpmYGYrlrM = false;}
      if(psOFJENLmK == true){psOFJENLmK = false;}
      if(QYXyrKfGWK == true){QYXyrKfGWK = false;}
      if(URgUALqypt == true){URgUALqypt = false;}
      if(lFUKqmcUKN == true){lFUKqmcUKN = false;}
      if(silwrXSngu == true){silwrXSngu = false;}
      if(rlOhqXMtFx == true){rlOhqXMtFx = false;}
      if(MPVrYKDNHF == true){MPVrYKDNHF = false;}
      if(hKuJQkfjbc == true){hKuJQkfjbc = false;}
      if(sDQtCAqmST == true){sDQtCAqmST = false;}
      if(ZiPMAdNsXg == true){ZiPMAdNsXg = false;}
      if(TFgbMhpEQF == true){TFgbMhpEQF = false;}
      if(qbRcEJyapY == true){qbRcEJyapY = false;}
      if(TQtnezthJm == true){TQtnezthJm = false;}
      if(XmMuImVohT == true){XmMuImVohT = false;}
      if(JmVMbyQmIq == true){JmVMbyQmIq = false;}
      if(elCzNCLsxN == true){elCzNCLsxN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DCJSKTMTSJ
{ 
  void qfFmSfhLhR()
  { 
      bool QaPDCGnHTi = false;
      bool IRDpmgbyJd = false;
      bool NleApSpJTR = false;
      bool pGjabWnlPN = false;
      bool ktkBLuOhaB = false;
      bool wXNnZewONj = false;
      bool QdnCrBgbNP = false;
      bool soiurSAcot = false;
      bool DIiRVRsuBx = false;
      bool aYYfxGGiIJ = false;
      bool OlTKIGoRwG = false;
      bool dTZSfHuVfa = false;
      bool IkaQoTQDyl = false;
      bool MRTffRnXJP = false;
      bool bazuSGzFzo = false;
      bool KkDhAcLDUn = false;
      bool plTJsMzsmO = false;
      bool TWLQyhlexh = false;
      bool UKDIaaNkeC = false;
      bool FkDVYpHpBF = false;
      string ViPcBKOVkh;
      string UNqKrjEkal;
      string wuYpgsNyZT;
      string BFQMIaKFyH;
      string GdzUMMVoEA;
      string YzrxEZKYuH;
      string wPwRfOxeCR;
      string ZzlSeRuDdU;
      string XYtZtBNSHi;
      string PkKpLphhnx;
      string PqmlZZMYSm;
      string dGuZjWVWWd;
      string BdWTCnnwHn;
      string jNPfFglHzT;
      string nnAUEIpjGn;
      string UKKJwkTSjk;
      string kQRdCQqOUD;
      string kNWCoMcCOs;
      string yEoSTYCFjT;
      string MSXNiXWWRm;
      if(ViPcBKOVkh == PqmlZZMYSm){QaPDCGnHTi = true;}
      else if(PqmlZZMYSm == ViPcBKOVkh){OlTKIGoRwG = true;}
      if(UNqKrjEkal == dGuZjWVWWd){IRDpmgbyJd = true;}
      else if(dGuZjWVWWd == UNqKrjEkal){dTZSfHuVfa = true;}
      if(wuYpgsNyZT == BdWTCnnwHn){NleApSpJTR = true;}
      else if(BdWTCnnwHn == wuYpgsNyZT){IkaQoTQDyl = true;}
      if(BFQMIaKFyH == jNPfFglHzT){pGjabWnlPN = true;}
      else if(jNPfFglHzT == BFQMIaKFyH){MRTffRnXJP = true;}
      if(GdzUMMVoEA == nnAUEIpjGn){ktkBLuOhaB = true;}
      else if(nnAUEIpjGn == GdzUMMVoEA){bazuSGzFzo = true;}
      if(YzrxEZKYuH == UKKJwkTSjk){wXNnZewONj = true;}
      else if(UKKJwkTSjk == YzrxEZKYuH){KkDhAcLDUn = true;}
      if(wPwRfOxeCR == kQRdCQqOUD){QdnCrBgbNP = true;}
      else if(kQRdCQqOUD == wPwRfOxeCR){plTJsMzsmO = true;}
      if(ZzlSeRuDdU == kNWCoMcCOs){soiurSAcot = true;}
      if(XYtZtBNSHi == yEoSTYCFjT){DIiRVRsuBx = true;}
      if(PkKpLphhnx == MSXNiXWWRm){aYYfxGGiIJ = true;}
      while(kNWCoMcCOs == ZzlSeRuDdU){TWLQyhlexh = true;}
      while(yEoSTYCFjT == yEoSTYCFjT){UKDIaaNkeC = true;}
      while(MSXNiXWWRm == MSXNiXWWRm){FkDVYpHpBF = true;}
      if(QaPDCGnHTi == true){QaPDCGnHTi = false;}
      if(IRDpmgbyJd == true){IRDpmgbyJd = false;}
      if(NleApSpJTR == true){NleApSpJTR = false;}
      if(pGjabWnlPN == true){pGjabWnlPN = false;}
      if(ktkBLuOhaB == true){ktkBLuOhaB = false;}
      if(wXNnZewONj == true){wXNnZewONj = false;}
      if(QdnCrBgbNP == true){QdnCrBgbNP = false;}
      if(soiurSAcot == true){soiurSAcot = false;}
      if(DIiRVRsuBx == true){DIiRVRsuBx = false;}
      if(aYYfxGGiIJ == true){aYYfxGGiIJ = false;}
      if(OlTKIGoRwG == true){OlTKIGoRwG = false;}
      if(dTZSfHuVfa == true){dTZSfHuVfa = false;}
      if(IkaQoTQDyl == true){IkaQoTQDyl = false;}
      if(MRTffRnXJP == true){MRTffRnXJP = false;}
      if(bazuSGzFzo == true){bazuSGzFzo = false;}
      if(KkDhAcLDUn == true){KkDhAcLDUn = false;}
      if(plTJsMzsmO == true){plTJsMzsmO = false;}
      if(TWLQyhlexh == true){TWLQyhlexh = false;}
      if(UKDIaaNkeC == true){UKDIaaNkeC = false;}
      if(FkDVYpHpBF == true){FkDVYpHpBF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LONYPZWZLK
{ 
  void PcJitYWopk()
  { 
      bool KqbptkMsgN = false;
      bool PRdgjSXoIL = false;
      bool rKELwdOZwu = false;
      bool ceOqOMAwHm = false;
      bool hAQUYgJZeS = false;
      bool eoohVAlPtP = false;
      bool WmwljjCmRX = false;
      bool RbhVdrtjlO = false;
      bool TnucPmogUO = false;
      bool ZkBqPuDdjo = false;
      bool eWHGBCHTEd = false;
      bool FCceuirTWw = false;
      bool tVRDxgZpFi = false;
      bool nPAxjxfnbM = false;
      bool fVbqIXHWug = false;
      bool DjHmtIEEJT = false;
      bool cROVopBeuy = false;
      bool CDqJQYsatZ = false;
      bool YDtYfEIMCa = false;
      bool saeIjOHGBS = false;
      string UcMXFVIdqN;
      string RkaqPXAWdG;
      string QzTQAUQMGw;
      string HHeIcPSjrJ;
      string kUlyLLGDzd;
      string PMbiAUIwXk;
      string EuWuGKGSNz;
      string FQeUVuMVFn;
      string ONMcfteuHI;
      string GVLHEoxqqB;
      string FmozXzgHNF;
      string HmqiVqhtOL;
      string eLLFsiEWPf;
      string yVdDiaXNEf;
      string NWgBATebkN;
      string GCbfVtbjGo;
      string tJrhHlImAu;
      string SUphyIdJFZ;
      string EblCYutyho;
      string znGPlDeytN;
      if(UcMXFVIdqN == FmozXzgHNF){KqbptkMsgN = true;}
      else if(FmozXzgHNF == UcMXFVIdqN){eWHGBCHTEd = true;}
      if(RkaqPXAWdG == HmqiVqhtOL){PRdgjSXoIL = true;}
      else if(HmqiVqhtOL == RkaqPXAWdG){FCceuirTWw = true;}
      if(QzTQAUQMGw == eLLFsiEWPf){rKELwdOZwu = true;}
      else if(eLLFsiEWPf == QzTQAUQMGw){tVRDxgZpFi = true;}
      if(HHeIcPSjrJ == yVdDiaXNEf){ceOqOMAwHm = true;}
      else if(yVdDiaXNEf == HHeIcPSjrJ){nPAxjxfnbM = true;}
      if(kUlyLLGDzd == NWgBATebkN){hAQUYgJZeS = true;}
      else if(NWgBATebkN == kUlyLLGDzd){fVbqIXHWug = true;}
      if(PMbiAUIwXk == GCbfVtbjGo){eoohVAlPtP = true;}
      else if(GCbfVtbjGo == PMbiAUIwXk){DjHmtIEEJT = true;}
      if(EuWuGKGSNz == tJrhHlImAu){WmwljjCmRX = true;}
      else if(tJrhHlImAu == EuWuGKGSNz){cROVopBeuy = true;}
      if(FQeUVuMVFn == SUphyIdJFZ){RbhVdrtjlO = true;}
      if(ONMcfteuHI == EblCYutyho){TnucPmogUO = true;}
      if(GVLHEoxqqB == znGPlDeytN){ZkBqPuDdjo = true;}
      while(SUphyIdJFZ == FQeUVuMVFn){CDqJQYsatZ = true;}
      while(EblCYutyho == EblCYutyho){YDtYfEIMCa = true;}
      while(znGPlDeytN == znGPlDeytN){saeIjOHGBS = true;}
      if(KqbptkMsgN == true){KqbptkMsgN = false;}
      if(PRdgjSXoIL == true){PRdgjSXoIL = false;}
      if(rKELwdOZwu == true){rKELwdOZwu = false;}
      if(ceOqOMAwHm == true){ceOqOMAwHm = false;}
      if(hAQUYgJZeS == true){hAQUYgJZeS = false;}
      if(eoohVAlPtP == true){eoohVAlPtP = false;}
      if(WmwljjCmRX == true){WmwljjCmRX = false;}
      if(RbhVdrtjlO == true){RbhVdrtjlO = false;}
      if(TnucPmogUO == true){TnucPmogUO = false;}
      if(ZkBqPuDdjo == true){ZkBqPuDdjo = false;}
      if(eWHGBCHTEd == true){eWHGBCHTEd = false;}
      if(FCceuirTWw == true){FCceuirTWw = false;}
      if(tVRDxgZpFi == true){tVRDxgZpFi = false;}
      if(nPAxjxfnbM == true){nPAxjxfnbM = false;}
      if(fVbqIXHWug == true){fVbqIXHWug = false;}
      if(DjHmtIEEJT == true){DjHmtIEEJT = false;}
      if(cROVopBeuy == true){cROVopBeuy = false;}
      if(CDqJQYsatZ == true){CDqJQYsatZ = false;}
      if(YDtYfEIMCa == true){YDtYfEIMCa = false;}
      if(saeIjOHGBS == true){saeIjOHGBS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGAJESBROP
{ 
  void kxoDoGVnSO()
  { 
      bool gMLIlpcdUH = false;
      bool WUrMjQaBRM = false;
      bool tNyONeoGeD = false;
      bool RwYBFGNDAQ = false;
      bool GwLLhByUmK = false;
      bool cQentTOwtH = false;
      bool BWyQoZwqHc = false;
      bool CWABGyBmgM = false;
      bool gTSUaARjGk = false;
      bool rRJsPixuVH = false;
      bool FGNJHGPdhw = false;
      bool RaOhZgDdpn = false;
      bool ILjVkjNGlW = false;
      bool AGQZGZGIMU = false;
      bool jnCKTQCaTh = false;
      bool eTEgytWqXW = false;
      bool rJqKuKKoaz = false;
      bool ZtQVDTIZCU = false;
      bool hlmDrgCiaM = false;
      bool DOjpbawrPI = false;
      string DpcKMpyPUZ;
      string PfkaPbrwOB;
      string wHAJQTjBhk;
      string mfyakVXPqM;
      string OspORNeZHF;
      string XAmgpwpSsr;
      string GxhjligJpt;
      string DbFClCQkrC;
      string nJtcMmrQko;
      string fFWyFQLGbh;
      string gUjMBwuktm;
      string eEapEwDEWz;
      string qPYANyFHwU;
      string pJJJVSZgaQ;
      string qGWyJbdftI;
      string NHjcqQwizD;
      string pnoZwUtQUk;
      string WWdFHjsapl;
      string TZMmHiZgSF;
      string WqgWaDRwBo;
      if(DpcKMpyPUZ == gUjMBwuktm){gMLIlpcdUH = true;}
      else if(gUjMBwuktm == DpcKMpyPUZ){FGNJHGPdhw = true;}
      if(PfkaPbrwOB == eEapEwDEWz){WUrMjQaBRM = true;}
      else if(eEapEwDEWz == PfkaPbrwOB){RaOhZgDdpn = true;}
      if(wHAJQTjBhk == qPYANyFHwU){tNyONeoGeD = true;}
      else if(qPYANyFHwU == wHAJQTjBhk){ILjVkjNGlW = true;}
      if(mfyakVXPqM == pJJJVSZgaQ){RwYBFGNDAQ = true;}
      else if(pJJJVSZgaQ == mfyakVXPqM){AGQZGZGIMU = true;}
      if(OspORNeZHF == qGWyJbdftI){GwLLhByUmK = true;}
      else if(qGWyJbdftI == OspORNeZHF){jnCKTQCaTh = true;}
      if(XAmgpwpSsr == NHjcqQwizD){cQentTOwtH = true;}
      else if(NHjcqQwizD == XAmgpwpSsr){eTEgytWqXW = true;}
      if(GxhjligJpt == pnoZwUtQUk){BWyQoZwqHc = true;}
      else if(pnoZwUtQUk == GxhjligJpt){rJqKuKKoaz = true;}
      if(DbFClCQkrC == WWdFHjsapl){CWABGyBmgM = true;}
      if(nJtcMmrQko == TZMmHiZgSF){gTSUaARjGk = true;}
      if(fFWyFQLGbh == WqgWaDRwBo){rRJsPixuVH = true;}
      while(WWdFHjsapl == DbFClCQkrC){ZtQVDTIZCU = true;}
      while(TZMmHiZgSF == TZMmHiZgSF){hlmDrgCiaM = true;}
      while(WqgWaDRwBo == WqgWaDRwBo){DOjpbawrPI = true;}
      if(gMLIlpcdUH == true){gMLIlpcdUH = false;}
      if(WUrMjQaBRM == true){WUrMjQaBRM = false;}
      if(tNyONeoGeD == true){tNyONeoGeD = false;}
      if(RwYBFGNDAQ == true){RwYBFGNDAQ = false;}
      if(GwLLhByUmK == true){GwLLhByUmK = false;}
      if(cQentTOwtH == true){cQentTOwtH = false;}
      if(BWyQoZwqHc == true){BWyQoZwqHc = false;}
      if(CWABGyBmgM == true){CWABGyBmgM = false;}
      if(gTSUaARjGk == true){gTSUaARjGk = false;}
      if(rRJsPixuVH == true){rRJsPixuVH = false;}
      if(FGNJHGPdhw == true){FGNJHGPdhw = false;}
      if(RaOhZgDdpn == true){RaOhZgDdpn = false;}
      if(ILjVkjNGlW == true){ILjVkjNGlW = false;}
      if(AGQZGZGIMU == true){AGQZGZGIMU = false;}
      if(jnCKTQCaTh == true){jnCKTQCaTh = false;}
      if(eTEgytWqXW == true){eTEgytWqXW = false;}
      if(rJqKuKKoaz == true){rJqKuKKoaz = false;}
      if(ZtQVDTIZCU == true){ZtQVDTIZCU = false;}
      if(hlmDrgCiaM == true){hlmDrgCiaM = false;}
      if(DOjpbawrPI == true){DOjpbawrPI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SCTODLVYCM
{ 
  void INTVQfzJPw()
  { 
      bool yZNhwuTHqs = false;
      bool wLmOnJBsrF = false;
      bool aRGSHQDOuY = false;
      bool JtMUwLeOBs = false;
      bool kRffzrmVRb = false;
      bool jKNlxgTtae = false;
      bool rFLRiByRRb = false;
      bool elqyTIlaTO = false;
      bool dgxToygaWP = false;
      bool rjnWAfGNwx = false;
      bool tUDoxySPRn = false;
      bool tsaLALIrck = false;
      bool UWuCjtxUxm = false;
      bool CYdWUIcHVp = false;
      bool eRIhUzIcVo = false;
      bool XNjLbWZBFC = false;
      bool AyRekVOEpr = false;
      bool hBVlFDNMgj = false;
      bool kUzHPonStx = false;
      bool ibBTpgzdxy = false;
      string nZoYEWjfHF;
      string uVVfZePNLY;
      string hEokrgQQce;
      string iRoEXmVOwp;
      string iuiSqQoIdb;
      string WHwutikEgW;
      string FTCbVcgRIl;
      string JBQVomUVsa;
      string rHlAIaVsJn;
      string CQgYkPrHxN;
      string iXArSVpaGG;
      string OOKFexgCTu;
      string HmHTirTqjY;
      string uNYeqTGsgm;
      string jtmCZnFbtm;
      string ionBGwPgJa;
      string BzphLAoeNL;
      string qmUgKNAEtu;
      string lrxxoFZWYu;
      string DZjGkkDFqY;
      if(nZoYEWjfHF == iXArSVpaGG){yZNhwuTHqs = true;}
      else if(iXArSVpaGG == nZoYEWjfHF){tUDoxySPRn = true;}
      if(uVVfZePNLY == OOKFexgCTu){wLmOnJBsrF = true;}
      else if(OOKFexgCTu == uVVfZePNLY){tsaLALIrck = true;}
      if(hEokrgQQce == HmHTirTqjY){aRGSHQDOuY = true;}
      else if(HmHTirTqjY == hEokrgQQce){UWuCjtxUxm = true;}
      if(iRoEXmVOwp == uNYeqTGsgm){JtMUwLeOBs = true;}
      else if(uNYeqTGsgm == iRoEXmVOwp){CYdWUIcHVp = true;}
      if(iuiSqQoIdb == jtmCZnFbtm){kRffzrmVRb = true;}
      else if(jtmCZnFbtm == iuiSqQoIdb){eRIhUzIcVo = true;}
      if(WHwutikEgW == ionBGwPgJa){jKNlxgTtae = true;}
      else if(ionBGwPgJa == WHwutikEgW){XNjLbWZBFC = true;}
      if(FTCbVcgRIl == BzphLAoeNL){rFLRiByRRb = true;}
      else if(BzphLAoeNL == FTCbVcgRIl){AyRekVOEpr = true;}
      if(JBQVomUVsa == qmUgKNAEtu){elqyTIlaTO = true;}
      if(rHlAIaVsJn == lrxxoFZWYu){dgxToygaWP = true;}
      if(CQgYkPrHxN == DZjGkkDFqY){rjnWAfGNwx = true;}
      while(qmUgKNAEtu == JBQVomUVsa){hBVlFDNMgj = true;}
      while(lrxxoFZWYu == lrxxoFZWYu){kUzHPonStx = true;}
      while(DZjGkkDFqY == DZjGkkDFqY){ibBTpgzdxy = true;}
      if(yZNhwuTHqs == true){yZNhwuTHqs = false;}
      if(wLmOnJBsrF == true){wLmOnJBsrF = false;}
      if(aRGSHQDOuY == true){aRGSHQDOuY = false;}
      if(JtMUwLeOBs == true){JtMUwLeOBs = false;}
      if(kRffzrmVRb == true){kRffzrmVRb = false;}
      if(jKNlxgTtae == true){jKNlxgTtae = false;}
      if(rFLRiByRRb == true){rFLRiByRRb = false;}
      if(elqyTIlaTO == true){elqyTIlaTO = false;}
      if(dgxToygaWP == true){dgxToygaWP = false;}
      if(rjnWAfGNwx == true){rjnWAfGNwx = false;}
      if(tUDoxySPRn == true){tUDoxySPRn = false;}
      if(tsaLALIrck == true){tsaLALIrck = false;}
      if(UWuCjtxUxm == true){UWuCjtxUxm = false;}
      if(CYdWUIcHVp == true){CYdWUIcHVp = false;}
      if(eRIhUzIcVo == true){eRIhUzIcVo = false;}
      if(XNjLbWZBFC == true){XNjLbWZBFC = false;}
      if(AyRekVOEpr == true){AyRekVOEpr = false;}
      if(hBVlFDNMgj == true){hBVlFDNMgj = false;}
      if(kUzHPonStx == true){kUzHPonStx = false;}
      if(ibBTpgzdxy == true){ibBTpgzdxy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MBUHCFDQQB
{ 
  void xjzaZhLznC()
  { 
      bool BxEUKSnklo = false;
      bool MesLJEKsjG = false;
      bool mdspuSVNYS = false;
      bool VFuBGJCJKF = false;
      bool EuufJEDGBt = false;
      bool QjuYJXEOYr = false;
      bool xaLSTHirFA = false;
      bool BBhdCrhNfp = false;
      bool OOLeBkKWqh = false;
      bool FnjSIcibMC = false;
      bool ULBBsPBQWR = false;
      bool pqhhchOgQh = false;
      bool wMAWtMRPVY = false;
      bool IFBdUDNKll = false;
      bool itAZrOGBoZ = false;
      bool OCKdFIKdGf = false;
      bool yltxIjoDMZ = false;
      bool UDueyCLZdf = false;
      bool GPauJFtWYM = false;
      bool rjDFnxzCQI = false;
      string ofomedgYdx;
      string fnIzfHostD;
      string KAxWQGibFB;
      string BjkRMWCSsW;
      string mkUodZDqzp;
      string GRhGfniRVX;
      string tEScuuDqlJ;
      string EVzXPZfIsp;
      string CrcPujCekX;
      string nkxUbiRqsh;
      string WMEpljSJpG;
      string IaYfVCaDhL;
      string rYFNVTYdug;
      string HoOKTpmmdK;
      string QrnePNLQzZ;
      string HOIgoxGqTR;
      string LoOJzSLOMe;
      string OnZXuAjaxI;
      string HHdVYrfhUV;
      string jwSLybdeew;
      if(ofomedgYdx == WMEpljSJpG){BxEUKSnklo = true;}
      else if(WMEpljSJpG == ofomedgYdx){ULBBsPBQWR = true;}
      if(fnIzfHostD == IaYfVCaDhL){MesLJEKsjG = true;}
      else if(IaYfVCaDhL == fnIzfHostD){pqhhchOgQh = true;}
      if(KAxWQGibFB == rYFNVTYdug){mdspuSVNYS = true;}
      else if(rYFNVTYdug == KAxWQGibFB){wMAWtMRPVY = true;}
      if(BjkRMWCSsW == HoOKTpmmdK){VFuBGJCJKF = true;}
      else if(HoOKTpmmdK == BjkRMWCSsW){IFBdUDNKll = true;}
      if(mkUodZDqzp == QrnePNLQzZ){EuufJEDGBt = true;}
      else if(QrnePNLQzZ == mkUodZDqzp){itAZrOGBoZ = true;}
      if(GRhGfniRVX == HOIgoxGqTR){QjuYJXEOYr = true;}
      else if(HOIgoxGqTR == GRhGfniRVX){OCKdFIKdGf = true;}
      if(tEScuuDqlJ == LoOJzSLOMe){xaLSTHirFA = true;}
      else if(LoOJzSLOMe == tEScuuDqlJ){yltxIjoDMZ = true;}
      if(EVzXPZfIsp == OnZXuAjaxI){BBhdCrhNfp = true;}
      if(CrcPujCekX == HHdVYrfhUV){OOLeBkKWqh = true;}
      if(nkxUbiRqsh == jwSLybdeew){FnjSIcibMC = true;}
      while(OnZXuAjaxI == EVzXPZfIsp){UDueyCLZdf = true;}
      while(HHdVYrfhUV == HHdVYrfhUV){GPauJFtWYM = true;}
      while(jwSLybdeew == jwSLybdeew){rjDFnxzCQI = true;}
      if(BxEUKSnklo == true){BxEUKSnklo = false;}
      if(MesLJEKsjG == true){MesLJEKsjG = false;}
      if(mdspuSVNYS == true){mdspuSVNYS = false;}
      if(VFuBGJCJKF == true){VFuBGJCJKF = false;}
      if(EuufJEDGBt == true){EuufJEDGBt = false;}
      if(QjuYJXEOYr == true){QjuYJXEOYr = false;}
      if(xaLSTHirFA == true){xaLSTHirFA = false;}
      if(BBhdCrhNfp == true){BBhdCrhNfp = false;}
      if(OOLeBkKWqh == true){OOLeBkKWqh = false;}
      if(FnjSIcibMC == true){FnjSIcibMC = false;}
      if(ULBBsPBQWR == true){ULBBsPBQWR = false;}
      if(pqhhchOgQh == true){pqhhchOgQh = false;}
      if(wMAWtMRPVY == true){wMAWtMRPVY = false;}
      if(IFBdUDNKll == true){IFBdUDNKll = false;}
      if(itAZrOGBoZ == true){itAZrOGBoZ = false;}
      if(OCKdFIKdGf == true){OCKdFIKdGf = false;}
      if(yltxIjoDMZ == true){yltxIjoDMZ = false;}
      if(UDueyCLZdf == true){UDueyCLZdf = false;}
      if(GPauJFtWYM == true){GPauJFtWYM = false;}
      if(rjDFnxzCQI == true){rjDFnxzCQI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JDGOWLZXET
{ 
  void oSZyVCUEKq()
  { 
      bool TbzGwIbAUQ = false;
      bool zbxwTAbUNa = false;
      bool wdkcocSJta = false;
      bool YkgcEcGIsp = false;
      bool YjouucdGQk = false;
      bool ooyZkoqWQS = false;
      bool oSGtqOtUqq = false;
      bool sTaXCLoohM = false;
      bool zMrIljlGqP = false;
      bool kjqaAGdtDg = false;
      bool hJOZrUNaXZ = false;
      bool ABoETcaxIH = false;
      bool bndbFIcAWw = false;
      bool gtlAdoyRPQ = false;
      bool VLiQOiumHX = false;
      bool efluEtelUi = false;
      bool rNDbrFPnZd = false;
      bool eIhqlQFMMV = false;
      bool NpszQBHquj = false;
      bool KLxfYHHGXJ = false;
      string tBKyxroAmM;
      string gqQQFNnkiq;
      string ybJoTzjVek;
      string xHEbeICTJz;
      string pyGaaGMSxP;
      string GhkpzSrVdx;
      string HSVCOYlokw;
      string LTbiAzUhNN;
      string mRYPdOVOcM;
      string QgoLrXcDMC;
      string UWgAElGBoz;
      string xJHQKpsFXz;
      string CWMYfdePqc;
      string WQVLrPjXLr;
      string HTYdOHYXBB;
      string dWfMzxKIUZ;
      string GqKMbgmwXt;
      string FVteqixiKY;
      string FGOpyAkJLu;
      string EbCkkQJMBh;
      if(tBKyxroAmM == UWgAElGBoz){TbzGwIbAUQ = true;}
      else if(UWgAElGBoz == tBKyxroAmM){hJOZrUNaXZ = true;}
      if(gqQQFNnkiq == xJHQKpsFXz){zbxwTAbUNa = true;}
      else if(xJHQKpsFXz == gqQQFNnkiq){ABoETcaxIH = true;}
      if(ybJoTzjVek == CWMYfdePqc){wdkcocSJta = true;}
      else if(CWMYfdePqc == ybJoTzjVek){bndbFIcAWw = true;}
      if(xHEbeICTJz == WQVLrPjXLr){YkgcEcGIsp = true;}
      else if(WQVLrPjXLr == xHEbeICTJz){gtlAdoyRPQ = true;}
      if(pyGaaGMSxP == HTYdOHYXBB){YjouucdGQk = true;}
      else if(HTYdOHYXBB == pyGaaGMSxP){VLiQOiumHX = true;}
      if(GhkpzSrVdx == dWfMzxKIUZ){ooyZkoqWQS = true;}
      else if(dWfMzxKIUZ == GhkpzSrVdx){efluEtelUi = true;}
      if(HSVCOYlokw == GqKMbgmwXt){oSGtqOtUqq = true;}
      else if(GqKMbgmwXt == HSVCOYlokw){rNDbrFPnZd = true;}
      if(LTbiAzUhNN == FVteqixiKY){sTaXCLoohM = true;}
      if(mRYPdOVOcM == FGOpyAkJLu){zMrIljlGqP = true;}
      if(QgoLrXcDMC == EbCkkQJMBh){kjqaAGdtDg = true;}
      while(FVteqixiKY == LTbiAzUhNN){eIhqlQFMMV = true;}
      while(FGOpyAkJLu == FGOpyAkJLu){NpszQBHquj = true;}
      while(EbCkkQJMBh == EbCkkQJMBh){KLxfYHHGXJ = true;}
      if(TbzGwIbAUQ == true){TbzGwIbAUQ = false;}
      if(zbxwTAbUNa == true){zbxwTAbUNa = false;}
      if(wdkcocSJta == true){wdkcocSJta = false;}
      if(YkgcEcGIsp == true){YkgcEcGIsp = false;}
      if(YjouucdGQk == true){YjouucdGQk = false;}
      if(ooyZkoqWQS == true){ooyZkoqWQS = false;}
      if(oSGtqOtUqq == true){oSGtqOtUqq = false;}
      if(sTaXCLoohM == true){sTaXCLoohM = false;}
      if(zMrIljlGqP == true){zMrIljlGqP = false;}
      if(kjqaAGdtDg == true){kjqaAGdtDg = false;}
      if(hJOZrUNaXZ == true){hJOZrUNaXZ = false;}
      if(ABoETcaxIH == true){ABoETcaxIH = false;}
      if(bndbFIcAWw == true){bndbFIcAWw = false;}
      if(gtlAdoyRPQ == true){gtlAdoyRPQ = false;}
      if(VLiQOiumHX == true){VLiQOiumHX = false;}
      if(efluEtelUi == true){efluEtelUi = false;}
      if(rNDbrFPnZd == true){rNDbrFPnZd = false;}
      if(eIhqlQFMMV == true){eIhqlQFMMV = false;}
      if(NpszQBHquj == true){NpszQBHquj = false;}
      if(KLxfYHHGXJ == true){KLxfYHHGXJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NLUYXVJZCR
{ 
  void QOMhYCxtpj()
  { 
      bool cxwCOKwkDm = false;
      bool hnYhRapbNA = false;
      bool iAabyFlcRU = false;
      bool UxRrbaRxhX = false;
      bool GbbuZPCgid = false;
      bool VKfhHbWTEI = false;
      bool XSShSjVgFp = false;
      bool JrsosGXfBh = false;
      bool DFtnzJRikA = false;
      bool ExsZAmJscp = false;
      bool tVbrTcQpoA = false;
      bool EpSVFRYeiI = false;
      bool RluFlMzToG = false;
      bool xdDKmhdBTW = false;
      bool sbtjuNdXTh = false;
      bool NdKTXIZVGH = false;
      bool dwAhDZmHhW = false;
      bool nXLLPpqLJX = false;
      bool hazGrTSile = false;
      bool IHtMswaMgV = false;
      string bacXXibfAr;
      string yufoFnBamb;
      string xPsBNGKWBF;
      string GAfYQmSISi;
      string TYUHLXjATp;
      string bFVyEMhaJR;
      string YFeulxPHYS;
      string VsHDIXukpp;
      string VJCKcBdgTD;
      string EqzBKOtZUN;
      string IcbAUixRpg;
      string RwkSuOCTRk;
      string ThnUNetGst;
      string cUPbhshBpt;
      string DLpllIGfFu;
      string LZHjtZoGmp;
      string oqYwDwfIjC;
      string gBdWgHqBhF;
      string XNAxhDNfhI;
      string EaOAFLmtip;
      if(bacXXibfAr == IcbAUixRpg){cxwCOKwkDm = true;}
      else if(IcbAUixRpg == bacXXibfAr){tVbrTcQpoA = true;}
      if(yufoFnBamb == RwkSuOCTRk){hnYhRapbNA = true;}
      else if(RwkSuOCTRk == yufoFnBamb){EpSVFRYeiI = true;}
      if(xPsBNGKWBF == ThnUNetGst){iAabyFlcRU = true;}
      else if(ThnUNetGst == xPsBNGKWBF){RluFlMzToG = true;}
      if(GAfYQmSISi == cUPbhshBpt){UxRrbaRxhX = true;}
      else if(cUPbhshBpt == GAfYQmSISi){xdDKmhdBTW = true;}
      if(TYUHLXjATp == DLpllIGfFu){GbbuZPCgid = true;}
      else if(DLpllIGfFu == TYUHLXjATp){sbtjuNdXTh = true;}
      if(bFVyEMhaJR == LZHjtZoGmp){VKfhHbWTEI = true;}
      else if(LZHjtZoGmp == bFVyEMhaJR){NdKTXIZVGH = true;}
      if(YFeulxPHYS == oqYwDwfIjC){XSShSjVgFp = true;}
      else if(oqYwDwfIjC == YFeulxPHYS){dwAhDZmHhW = true;}
      if(VsHDIXukpp == gBdWgHqBhF){JrsosGXfBh = true;}
      if(VJCKcBdgTD == XNAxhDNfhI){DFtnzJRikA = true;}
      if(EqzBKOtZUN == EaOAFLmtip){ExsZAmJscp = true;}
      while(gBdWgHqBhF == VsHDIXukpp){nXLLPpqLJX = true;}
      while(XNAxhDNfhI == XNAxhDNfhI){hazGrTSile = true;}
      while(EaOAFLmtip == EaOAFLmtip){IHtMswaMgV = true;}
      if(cxwCOKwkDm == true){cxwCOKwkDm = false;}
      if(hnYhRapbNA == true){hnYhRapbNA = false;}
      if(iAabyFlcRU == true){iAabyFlcRU = false;}
      if(UxRrbaRxhX == true){UxRrbaRxhX = false;}
      if(GbbuZPCgid == true){GbbuZPCgid = false;}
      if(VKfhHbWTEI == true){VKfhHbWTEI = false;}
      if(XSShSjVgFp == true){XSShSjVgFp = false;}
      if(JrsosGXfBh == true){JrsosGXfBh = false;}
      if(DFtnzJRikA == true){DFtnzJRikA = false;}
      if(ExsZAmJscp == true){ExsZAmJscp = false;}
      if(tVbrTcQpoA == true){tVbrTcQpoA = false;}
      if(EpSVFRYeiI == true){EpSVFRYeiI = false;}
      if(RluFlMzToG == true){RluFlMzToG = false;}
      if(xdDKmhdBTW == true){xdDKmhdBTW = false;}
      if(sbtjuNdXTh == true){sbtjuNdXTh = false;}
      if(NdKTXIZVGH == true){NdKTXIZVGH = false;}
      if(dwAhDZmHhW == true){dwAhDZmHhW = false;}
      if(nXLLPpqLJX == true){nXLLPpqLJX = false;}
      if(hazGrTSile == true){hazGrTSile = false;}
      if(IHtMswaMgV == true){IHtMswaMgV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NAAKVRQZTY
{ 
  void QyzcmtDQiq()
  { 
      bool zsSfWzEuwP = false;
      bool dbWNQgVyay = false;
      bool MhUcNwjJyz = false;
      bool llWruqfCHF = false;
      bool isRwuLhWpd = false;
      bool LtNpjRXpRa = false;
      bool PuwxcrEeSY = false;
      bool BTqVOSPYgC = false;
      bool OMSTnrXgHc = false;
      bool TpjgomwUSD = false;
      bool GCERcqDqaQ = false;
      bool CyIPLDccIk = false;
      bool TXWoELiJga = false;
      bool WuFcuLIBqw = false;
      bool ofFpZUgUUl = false;
      bool KTLhjieOMR = false;
      bool IsKztHseUz = false;
      bool talMunSgOj = false;
      bool dOotQDiWsL = false;
      bool ftoYmwUFwS = false;
      string tYzWcXYyFU;
      string dPePhklXQt;
      string kzAEJsqSGM;
      string zapTlHKPuX;
      string njzPAbnbZm;
      string VuYNwtXtNj;
      string gGqrVDZKdZ;
      string aVbsGBAkEg;
      string FOsTqEBcWq;
      string iPCLpgrGtx;
      string CcyzLzTfGu;
      string tmogdRNXBQ;
      string BxnlqKTPCY;
      string IsqHdcQsHq;
      string kVVbxwaUhX;
      string TUFcuEnLIB;
      string fDcglAwgCB;
      string BTPJfeaMou;
      string jyhdFnnOMZ;
      string nEjGLgsoow;
      if(tYzWcXYyFU == CcyzLzTfGu){zsSfWzEuwP = true;}
      else if(CcyzLzTfGu == tYzWcXYyFU){GCERcqDqaQ = true;}
      if(dPePhklXQt == tmogdRNXBQ){dbWNQgVyay = true;}
      else if(tmogdRNXBQ == dPePhklXQt){CyIPLDccIk = true;}
      if(kzAEJsqSGM == BxnlqKTPCY){MhUcNwjJyz = true;}
      else if(BxnlqKTPCY == kzAEJsqSGM){TXWoELiJga = true;}
      if(zapTlHKPuX == IsqHdcQsHq){llWruqfCHF = true;}
      else if(IsqHdcQsHq == zapTlHKPuX){WuFcuLIBqw = true;}
      if(njzPAbnbZm == kVVbxwaUhX){isRwuLhWpd = true;}
      else if(kVVbxwaUhX == njzPAbnbZm){ofFpZUgUUl = true;}
      if(VuYNwtXtNj == TUFcuEnLIB){LtNpjRXpRa = true;}
      else if(TUFcuEnLIB == VuYNwtXtNj){KTLhjieOMR = true;}
      if(gGqrVDZKdZ == fDcglAwgCB){PuwxcrEeSY = true;}
      else if(fDcglAwgCB == gGqrVDZKdZ){IsKztHseUz = true;}
      if(aVbsGBAkEg == BTPJfeaMou){BTqVOSPYgC = true;}
      if(FOsTqEBcWq == jyhdFnnOMZ){OMSTnrXgHc = true;}
      if(iPCLpgrGtx == nEjGLgsoow){TpjgomwUSD = true;}
      while(BTPJfeaMou == aVbsGBAkEg){talMunSgOj = true;}
      while(jyhdFnnOMZ == jyhdFnnOMZ){dOotQDiWsL = true;}
      while(nEjGLgsoow == nEjGLgsoow){ftoYmwUFwS = true;}
      if(zsSfWzEuwP == true){zsSfWzEuwP = false;}
      if(dbWNQgVyay == true){dbWNQgVyay = false;}
      if(MhUcNwjJyz == true){MhUcNwjJyz = false;}
      if(llWruqfCHF == true){llWruqfCHF = false;}
      if(isRwuLhWpd == true){isRwuLhWpd = false;}
      if(LtNpjRXpRa == true){LtNpjRXpRa = false;}
      if(PuwxcrEeSY == true){PuwxcrEeSY = false;}
      if(BTqVOSPYgC == true){BTqVOSPYgC = false;}
      if(OMSTnrXgHc == true){OMSTnrXgHc = false;}
      if(TpjgomwUSD == true){TpjgomwUSD = false;}
      if(GCERcqDqaQ == true){GCERcqDqaQ = false;}
      if(CyIPLDccIk == true){CyIPLDccIk = false;}
      if(TXWoELiJga == true){TXWoELiJga = false;}
      if(WuFcuLIBqw == true){WuFcuLIBqw = false;}
      if(ofFpZUgUUl == true){ofFpZUgUUl = false;}
      if(KTLhjieOMR == true){KTLhjieOMR = false;}
      if(IsKztHseUz == true){IsKztHseUz = false;}
      if(talMunSgOj == true){talMunSgOj = false;}
      if(dOotQDiWsL == true){dOotQDiWsL = false;}
      if(ftoYmwUFwS == true){ftoYmwUFwS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VCAWWVKOUD
{ 
  void JZSllkJrpc()
  { 
      bool ckNUIMxSWE = false;
      bool uubVNHNbTg = false;
      bool DxszqfYGRI = false;
      bool DezNeqyPim = false;
      bool FTjArzEKHN = false;
      bool JPOTcfrNdb = false;
      bool nqBOAQwOpW = false;
      bool JxrgajMrHq = false;
      bool bNyDzmPfjz = false;
      bool ykkHyORUAb = false;
      bool DpTkELXhrr = false;
      bool SAGlzZryPM = false;
      bool AQdpYYMkhM = false;
      bool RqrfnlsNym = false;
      bool PgmqfydyHY = false;
      bool WTFmamLcLf = false;
      bool ymAfaaHZyN = false;
      bool fezbxTclKZ = false;
      bool tNcIpxlEFA = false;
      bool ZPBSnbgHQF = false;
      string VtrBzsjWyf;
      string YTukKJnOfa;
      string MKUYuwrnSz;
      string YWSHQWIqmi;
      string cThJKZVFID;
      string dPcgHLZTGD;
      string AuEyHBAmUm;
      string AxawxsbLOV;
      string ZlfOVIskAF;
      string wnkjigPiBI;
      string YikUCfngiO;
      string iOEjcNPocz;
      string HPlPpLMqMQ;
      string dsJFxqBKMo;
      string TLBlVhjAGU;
      string RZGCAJwUdp;
      string TxTSkpEyml;
      string MEcmewNAsI;
      string bLjrzDlHFm;
      string uffVVWriBf;
      if(VtrBzsjWyf == YikUCfngiO){ckNUIMxSWE = true;}
      else if(YikUCfngiO == VtrBzsjWyf){DpTkELXhrr = true;}
      if(YTukKJnOfa == iOEjcNPocz){uubVNHNbTg = true;}
      else if(iOEjcNPocz == YTukKJnOfa){SAGlzZryPM = true;}
      if(MKUYuwrnSz == HPlPpLMqMQ){DxszqfYGRI = true;}
      else if(HPlPpLMqMQ == MKUYuwrnSz){AQdpYYMkhM = true;}
      if(YWSHQWIqmi == dsJFxqBKMo){DezNeqyPim = true;}
      else if(dsJFxqBKMo == YWSHQWIqmi){RqrfnlsNym = true;}
      if(cThJKZVFID == TLBlVhjAGU){FTjArzEKHN = true;}
      else if(TLBlVhjAGU == cThJKZVFID){PgmqfydyHY = true;}
      if(dPcgHLZTGD == RZGCAJwUdp){JPOTcfrNdb = true;}
      else if(RZGCAJwUdp == dPcgHLZTGD){WTFmamLcLf = true;}
      if(AuEyHBAmUm == TxTSkpEyml){nqBOAQwOpW = true;}
      else if(TxTSkpEyml == AuEyHBAmUm){ymAfaaHZyN = true;}
      if(AxawxsbLOV == MEcmewNAsI){JxrgajMrHq = true;}
      if(ZlfOVIskAF == bLjrzDlHFm){bNyDzmPfjz = true;}
      if(wnkjigPiBI == uffVVWriBf){ykkHyORUAb = true;}
      while(MEcmewNAsI == AxawxsbLOV){fezbxTclKZ = true;}
      while(bLjrzDlHFm == bLjrzDlHFm){tNcIpxlEFA = true;}
      while(uffVVWriBf == uffVVWriBf){ZPBSnbgHQF = true;}
      if(ckNUIMxSWE == true){ckNUIMxSWE = false;}
      if(uubVNHNbTg == true){uubVNHNbTg = false;}
      if(DxszqfYGRI == true){DxszqfYGRI = false;}
      if(DezNeqyPim == true){DezNeqyPim = false;}
      if(FTjArzEKHN == true){FTjArzEKHN = false;}
      if(JPOTcfrNdb == true){JPOTcfrNdb = false;}
      if(nqBOAQwOpW == true){nqBOAQwOpW = false;}
      if(JxrgajMrHq == true){JxrgajMrHq = false;}
      if(bNyDzmPfjz == true){bNyDzmPfjz = false;}
      if(ykkHyORUAb == true){ykkHyORUAb = false;}
      if(DpTkELXhrr == true){DpTkELXhrr = false;}
      if(SAGlzZryPM == true){SAGlzZryPM = false;}
      if(AQdpYYMkhM == true){AQdpYYMkhM = false;}
      if(RqrfnlsNym == true){RqrfnlsNym = false;}
      if(PgmqfydyHY == true){PgmqfydyHY = false;}
      if(WTFmamLcLf == true){WTFmamLcLf = false;}
      if(ymAfaaHZyN == true){ymAfaaHZyN = false;}
      if(fezbxTclKZ == true){fezbxTclKZ = false;}
      if(tNcIpxlEFA == true){tNcIpxlEFA = false;}
      if(ZPBSnbgHQF == true){ZPBSnbgHQF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VQYVAQUJOH
{ 
  void grbJBmzjDV()
  { 
      bool kSlMAZDaOD = false;
      bool NuwrETJFun = false;
      bool eOybnzeKmf = false;
      bool HKbOCKtGHz = false;
      bool xikmRSyxcR = false;
      bool DYeamVTJYB = false;
      bool usniuDTgot = false;
      bool YDywpudKJU = false;
      bool AhhVcieBbf = false;
      bool pkhGDEuCrO = false;
      bool zQHirAahjq = false;
      bool rIzDANLRFL = false;
      bool XREJDnVqsl = false;
      bool zbSuVjZzcc = false;
      bool IxRknhkeGo = false;
      bool scwfpgMxeE = false;
      bool dinxqPpEgQ = false;
      bool mMocDaATVV = false;
      bool CqjEsVflEo = false;
      bool WcTXyYITsX = false;
      string XJxFqMuTTz;
      string quTXKZnEpO;
      string CCiUHEDSYw;
      string MycgcyHeEX;
      string LzhfQxUNem;
      string iKkroUabxl;
      string IbtWlsRmuL;
      string SIzSCCUCEK;
      string ipnkMBMkqH;
      string XfgROiFKsW;
      string ehRSUaKSom;
      string AXWmDSnIKk;
      string ggunmlahDT;
      string xKIgeBXUQl;
      string qsuEHAItOu;
      string twzIpymceh;
      string AcOUooOpIC;
      string tTrYtmkqgm;
      string dfSIZBKAqf;
      string NuohkNeaOR;
      if(XJxFqMuTTz == ehRSUaKSom){kSlMAZDaOD = true;}
      else if(ehRSUaKSom == XJxFqMuTTz){zQHirAahjq = true;}
      if(quTXKZnEpO == AXWmDSnIKk){NuwrETJFun = true;}
      else if(AXWmDSnIKk == quTXKZnEpO){rIzDANLRFL = true;}
      if(CCiUHEDSYw == ggunmlahDT){eOybnzeKmf = true;}
      else if(ggunmlahDT == CCiUHEDSYw){XREJDnVqsl = true;}
      if(MycgcyHeEX == xKIgeBXUQl){HKbOCKtGHz = true;}
      else if(xKIgeBXUQl == MycgcyHeEX){zbSuVjZzcc = true;}
      if(LzhfQxUNem == qsuEHAItOu){xikmRSyxcR = true;}
      else if(qsuEHAItOu == LzhfQxUNem){IxRknhkeGo = true;}
      if(iKkroUabxl == twzIpymceh){DYeamVTJYB = true;}
      else if(twzIpymceh == iKkroUabxl){scwfpgMxeE = true;}
      if(IbtWlsRmuL == AcOUooOpIC){usniuDTgot = true;}
      else if(AcOUooOpIC == IbtWlsRmuL){dinxqPpEgQ = true;}
      if(SIzSCCUCEK == tTrYtmkqgm){YDywpudKJU = true;}
      if(ipnkMBMkqH == dfSIZBKAqf){AhhVcieBbf = true;}
      if(XfgROiFKsW == NuohkNeaOR){pkhGDEuCrO = true;}
      while(tTrYtmkqgm == SIzSCCUCEK){mMocDaATVV = true;}
      while(dfSIZBKAqf == dfSIZBKAqf){CqjEsVflEo = true;}
      while(NuohkNeaOR == NuohkNeaOR){WcTXyYITsX = true;}
      if(kSlMAZDaOD == true){kSlMAZDaOD = false;}
      if(NuwrETJFun == true){NuwrETJFun = false;}
      if(eOybnzeKmf == true){eOybnzeKmf = false;}
      if(HKbOCKtGHz == true){HKbOCKtGHz = false;}
      if(xikmRSyxcR == true){xikmRSyxcR = false;}
      if(DYeamVTJYB == true){DYeamVTJYB = false;}
      if(usniuDTgot == true){usniuDTgot = false;}
      if(YDywpudKJU == true){YDywpudKJU = false;}
      if(AhhVcieBbf == true){AhhVcieBbf = false;}
      if(pkhGDEuCrO == true){pkhGDEuCrO = false;}
      if(zQHirAahjq == true){zQHirAahjq = false;}
      if(rIzDANLRFL == true){rIzDANLRFL = false;}
      if(XREJDnVqsl == true){XREJDnVqsl = false;}
      if(zbSuVjZzcc == true){zbSuVjZzcc = false;}
      if(IxRknhkeGo == true){IxRknhkeGo = false;}
      if(scwfpgMxeE == true){scwfpgMxeE = false;}
      if(dinxqPpEgQ == true){dinxqPpEgQ = false;}
      if(mMocDaATVV == true){mMocDaATVV = false;}
      if(CqjEsVflEo == true){CqjEsVflEo = false;}
      if(WcTXyYITsX == true){WcTXyYITsX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FYZETCMNGJ
{ 
  void zOAsxzgeyn()
  { 
      bool RtbdKjaCdL = false;
      bool uqMYGOBSac = false;
      bool XpcyYJwkXO = false;
      bool VTxoajStGI = false;
      bool dtRMPYZyHL = false;
      bool LNKuxaRcFA = false;
      bool npePpatWyW = false;
      bool wHLRydYQiz = false;
      bool jycLCHIBqA = false;
      bool RonGUmPCVn = false;
      bool eCzkPEBswT = false;
      bool BAtFPpNSMh = false;
      bool SrfyEGTFwL = false;
      bool NWttUhyruy = false;
      bool GPFXyRuhqe = false;
      bool ZwonVlWAfI = false;
      bool kwwkFdGzjg = false;
      bool qUXNaDmIAm = false;
      bool LkORlRgFYi = false;
      bool LyLmNKSURU = false;
      string bkwEdVNnCS;
      string Deffyzfopg;
      string mYUoOxcDew;
      string wNylPJpwPF;
      string WhptVrhqBU;
      string YqqaSDPGpf;
      string rJIGVogtPo;
      string JjZjJFiaSV;
      string PlBKXFWWSM;
      string siFiMMYjXg;
      string KmbMKnQGQN;
      string UomUQGIyhQ;
      string RKaDuZeqWx;
      string fyClKbJnzj;
      string nPFFrDukSG;
      string EaBGOAMXQk;
      string IZiThVlBJn;
      string wTzycCFULr;
      string dtXQsExuXK;
      string PlXOaNfkXV;
      if(bkwEdVNnCS == KmbMKnQGQN){RtbdKjaCdL = true;}
      else if(KmbMKnQGQN == bkwEdVNnCS){eCzkPEBswT = true;}
      if(Deffyzfopg == UomUQGIyhQ){uqMYGOBSac = true;}
      else if(UomUQGIyhQ == Deffyzfopg){BAtFPpNSMh = true;}
      if(mYUoOxcDew == RKaDuZeqWx){XpcyYJwkXO = true;}
      else if(RKaDuZeqWx == mYUoOxcDew){SrfyEGTFwL = true;}
      if(wNylPJpwPF == fyClKbJnzj){VTxoajStGI = true;}
      else if(fyClKbJnzj == wNylPJpwPF){NWttUhyruy = true;}
      if(WhptVrhqBU == nPFFrDukSG){dtRMPYZyHL = true;}
      else if(nPFFrDukSG == WhptVrhqBU){GPFXyRuhqe = true;}
      if(YqqaSDPGpf == EaBGOAMXQk){LNKuxaRcFA = true;}
      else if(EaBGOAMXQk == YqqaSDPGpf){ZwonVlWAfI = true;}
      if(rJIGVogtPo == IZiThVlBJn){npePpatWyW = true;}
      else if(IZiThVlBJn == rJIGVogtPo){kwwkFdGzjg = true;}
      if(JjZjJFiaSV == wTzycCFULr){wHLRydYQiz = true;}
      if(PlBKXFWWSM == dtXQsExuXK){jycLCHIBqA = true;}
      if(siFiMMYjXg == PlXOaNfkXV){RonGUmPCVn = true;}
      while(wTzycCFULr == JjZjJFiaSV){qUXNaDmIAm = true;}
      while(dtXQsExuXK == dtXQsExuXK){LkORlRgFYi = true;}
      while(PlXOaNfkXV == PlXOaNfkXV){LyLmNKSURU = true;}
      if(RtbdKjaCdL == true){RtbdKjaCdL = false;}
      if(uqMYGOBSac == true){uqMYGOBSac = false;}
      if(XpcyYJwkXO == true){XpcyYJwkXO = false;}
      if(VTxoajStGI == true){VTxoajStGI = false;}
      if(dtRMPYZyHL == true){dtRMPYZyHL = false;}
      if(LNKuxaRcFA == true){LNKuxaRcFA = false;}
      if(npePpatWyW == true){npePpatWyW = false;}
      if(wHLRydYQiz == true){wHLRydYQiz = false;}
      if(jycLCHIBqA == true){jycLCHIBqA = false;}
      if(RonGUmPCVn == true){RonGUmPCVn = false;}
      if(eCzkPEBswT == true){eCzkPEBswT = false;}
      if(BAtFPpNSMh == true){BAtFPpNSMh = false;}
      if(SrfyEGTFwL == true){SrfyEGTFwL = false;}
      if(NWttUhyruy == true){NWttUhyruy = false;}
      if(GPFXyRuhqe == true){GPFXyRuhqe = false;}
      if(ZwonVlWAfI == true){ZwonVlWAfI = false;}
      if(kwwkFdGzjg == true){kwwkFdGzjg = false;}
      if(qUXNaDmIAm == true){qUXNaDmIAm = false;}
      if(LkORlRgFYi == true){LkORlRgFYi = false;}
      if(LyLmNKSURU == true){LyLmNKSURU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CWETWQHBXH
{ 
  void oCQoHnVVDg()
  { 
      bool hTxnwgOtJu = false;
      bool isXMNEVkSP = false;
      bool xVKHqmQDem = false;
      bool IAUXCaSjie = false;
      bool eytCoWVNDC = false;
      bool HrEOVMJpwI = false;
      bool PKPVmhYAKl = false;
      bool kkCmkzaHRU = false;
      bool RDAbfPwGBo = false;
      bool QcnaOThYOG = false;
      bool xVCQRVoQcW = false;
      bool kBXaqLKnpW = false;
      bool lSyUVHxbYQ = false;
      bool RCrKWwBiJJ = false;
      bool afceEOFMiC = false;
      bool IsirUeWguJ = false;
      bool YNrLEiJMEu = false;
      bool KbdfwFpTQG = false;
      bool CjrVIXTApr = false;
      bool YTmAkMnQZV = false;
      string OrwUuksdGM;
      string iFloXqICTt;
      string lbpMrmSOcx;
      string ieKWNQAUVn;
      string TeFtScwrzW;
      string DwHqumBicI;
      string ReAIcDtPbH;
      string pmgfZHVwtP;
      string paPGsmWTbZ;
      string ORrMVndwQO;
      string hgQqgQObQm;
      string QFnNRqPtOp;
      string ganBsXuTJk;
      string cZefgJJXZc;
      string XuCnJIcdud;
      string YjgagHsPxI;
      string VtReJpZIgH;
      string hqUlRlXzqk;
      string uQXfMssEyY;
      string QtZQHddWeT;
      if(OrwUuksdGM == hgQqgQObQm){hTxnwgOtJu = true;}
      else if(hgQqgQObQm == OrwUuksdGM){xVCQRVoQcW = true;}
      if(iFloXqICTt == QFnNRqPtOp){isXMNEVkSP = true;}
      else if(QFnNRqPtOp == iFloXqICTt){kBXaqLKnpW = true;}
      if(lbpMrmSOcx == ganBsXuTJk){xVKHqmQDem = true;}
      else if(ganBsXuTJk == lbpMrmSOcx){lSyUVHxbYQ = true;}
      if(ieKWNQAUVn == cZefgJJXZc){IAUXCaSjie = true;}
      else if(cZefgJJXZc == ieKWNQAUVn){RCrKWwBiJJ = true;}
      if(TeFtScwrzW == XuCnJIcdud){eytCoWVNDC = true;}
      else if(XuCnJIcdud == TeFtScwrzW){afceEOFMiC = true;}
      if(DwHqumBicI == YjgagHsPxI){HrEOVMJpwI = true;}
      else if(YjgagHsPxI == DwHqumBicI){IsirUeWguJ = true;}
      if(ReAIcDtPbH == VtReJpZIgH){PKPVmhYAKl = true;}
      else if(VtReJpZIgH == ReAIcDtPbH){YNrLEiJMEu = true;}
      if(pmgfZHVwtP == hqUlRlXzqk){kkCmkzaHRU = true;}
      if(paPGsmWTbZ == uQXfMssEyY){RDAbfPwGBo = true;}
      if(ORrMVndwQO == QtZQHddWeT){QcnaOThYOG = true;}
      while(hqUlRlXzqk == pmgfZHVwtP){KbdfwFpTQG = true;}
      while(uQXfMssEyY == uQXfMssEyY){CjrVIXTApr = true;}
      while(QtZQHddWeT == QtZQHddWeT){YTmAkMnQZV = true;}
      if(hTxnwgOtJu == true){hTxnwgOtJu = false;}
      if(isXMNEVkSP == true){isXMNEVkSP = false;}
      if(xVKHqmQDem == true){xVKHqmQDem = false;}
      if(IAUXCaSjie == true){IAUXCaSjie = false;}
      if(eytCoWVNDC == true){eytCoWVNDC = false;}
      if(HrEOVMJpwI == true){HrEOVMJpwI = false;}
      if(PKPVmhYAKl == true){PKPVmhYAKl = false;}
      if(kkCmkzaHRU == true){kkCmkzaHRU = false;}
      if(RDAbfPwGBo == true){RDAbfPwGBo = false;}
      if(QcnaOThYOG == true){QcnaOThYOG = false;}
      if(xVCQRVoQcW == true){xVCQRVoQcW = false;}
      if(kBXaqLKnpW == true){kBXaqLKnpW = false;}
      if(lSyUVHxbYQ == true){lSyUVHxbYQ = false;}
      if(RCrKWwBiJJ == true){RCrKWwBiJJ = false;}
      if(afceEOFMiC == true){afceEOFMiC = false;}
      if(IsirUeWguJ == true){IsirUeWguJ = false;}
      if(YNrLEiJMEu == true){YNrLEiJMEu = false;}
      if(KbdfwFpTQG == true){KbdfwFpTQG = false;}
      if(CjrVIXTApr == true){CjrVIXTApr = false;}
      if(YTmAkMnQZV == true){YTmAkMnQZV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBIJXFJYSV
{ 
  void axKUQtTjjp()
  { 
      bool AbVmFXoOgW = false;
      bool SAphHlbytz = false;
      bool qCRYbucxUx = false;
      bool PywWZuwynF = false;
      bool fWGqlJADmr = false;
      bool HWrHhxKwLJ = false;
      bool ursiHUETHM = false;
      bool ocJnTUuZmS = false;
      bool uYKbprFonb = false;
      bool jAmeKncWjR = false;
      bool EfuZCdMDnN = false;
      bool CjIrNVgRsO = false;
      bool OOeebooede = false;
      bool qXpVNOckYL = false;
      bool eCAaZzquQn = false;
      bool GLdUCoBPxN = false;
      bool ohYIVdtmdy = false;
      bool rwrhjLOEFc = false;
      bool xtNoYfsVSX = false;
      bool NMmKWxcqEu = false;
      string GeIBNXYuVn;
      string CCGkbklPkl;
      string KhpaGNnupg;
      string lMEbEZsgbr;
      string YGltxxOUbD;
      string aOVDbYoguA;
      string jcFoBoyefB;
      string rEnsMEwudI;
      string zSTlFXpBzf;
      string kLlbIwBwrH;
      string zjnZLWZcpX;
      string bsClBQISid;
      string zweAQfRMkQ;
      string DzCWIOdtZi;
      string xNLaDqIzZq;
      string mhNOIDEnIf;
      string ENrYUcqfdl;
      string lOrzgkkDxZ;
      string XRlsdUknOE;
      string KplteiVlGZ;
      if(GeIBNXYuVn == zjnZLWZcpX){AbVmFXoOgW = true;}
      else if(zjnZLWZcpX == GeIBNXYuVn){EfuZCdMDnN = true;}
      if(CCGkbklPkl == bsClBQISid){SAphHlbytz = true;}
      else if(bsClBQISid == CCGkbklPkl){CjIrNVgRsO = true;}
      if(KhpaGNnupg == zweAQfRMkQ){qCRYbucxUx = true;}
      else if(zweAQfRMkQ == KhpaGNnupg){OOeebooede = true;}
      if(lMEbEZsgbr == DzCWIOdtZi){PywWZuwynF = true;}
      else if(DzCWIOdtZi == lMEbEZsgbr){qXpVNOckYL = true;}
      if(YGltxxOUbD == xNLaDqIzZq){fWGqlJADmr = true;}
      else if(xNLaDqIzZq == YGltxxOUbD){eCAaZzquQn = true;}
      if(aOVDbYoguA == mhNOIDEnIf){HWrHhxKwLJ = true;}
      else if(mhNOIDEnIf == aOVDbYoguA){GLdUCoBPxN = true;}
      if(jcFoBoyefB == ENrYUcqfdl){ursiHUETHM = true;}
      else if(ENrYUcqfdl == jcFoBoyefB){ohYIVdtmdy = true;}
      if(rEnsMEwudI == lOrzgkkDxZ){ocJnTUuZmS = true;}
      if(zSTlFXpBzf == XRlsdUknOE){uYKbprFonb = true;}
      if(kLlbIwBwrH == KplteiVlGZ){jAmeKncWjR = true;}
      while(lOrzgkkDxZ == rEnsMEwudI){rwrhjLOEFc = true;}
      while(XRlsdUknOE == XRlsdUknOE){xtNoYfsVSX = true;}
      while(KplteiVlGZ == KplteiVlGZ){NMmKWxcqEu = true;}
      if(AbVmFXoOgW == true){AbVmFXoOgW = false;}
      if(SAphHlbytz == true){SAphHlbytz = false;}
      if(qCRYbucxUx == true){qCRYbucxUx = false;}
      if(PywWZuwynF == true){PywWZuwynF = false;}
      if(fWGqlJADmr == true){fWGqlJADmr = false;}
      if(HWrHhxKwLJ == true){HWrHhxKwLJ = false;}
      if(ursiHUETHM == true){ursiHUETHM = false;}
      if(ocJnTUuZmS == true){ocJnTUuZmS = false;}
      if(uYKbprFonb == true){uYKbprFonb = false;}
      if(jAmeKncWjR == true){jAmeKncWjR = false;}
      if(EfuZCdMDnN == true){EfuZCdMDnN = false;}
      if(CjIrNVgRsO == true){CjIrNVgRsO = false;}
      if(OOeebooede == true){OOeebooede = false;}
      if(qXpVNOckYL == true){qXpVNOckYL = false;}
      if(eCAaZzquQn == true){eCAaZzquQn = false;}
      if(GLdUCoBPxN == true){GLdUCoBPxN = false;}
      if(ohYIVdtmdy == true){ohYIVdtmdy = false;}
      if(rwrhjLOEFc == true){rwrhjLOEFc = false;}
      if(xtNoYfsVSX == true){xtNoYfsVSX = false;}
      if(NMmKWxcqEu == true){NMmKWxcqEu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QSJWJXQEOS
{ 
  void HMDysIcrAa()
  { 
      bool ZpbHBCEzIi = false;
      bool DeASlSiruL = false;
      bool KmLNBTstUP = false;
      bool cuLudyoDwg = false;
      bool RtFrcxdCRc = false;
      bool LTepNldNGh = false;
      bool IJerGISEon = false;
      bool cfwNsPhTkE = false;
      bool oqcqEJQVgq = false;
      bool TaxNYHPMkU = false;
      bool dYNczfWQwy = false;
      bool EKcCrQgmnx = false;
      bool qxXyTCihok = false;
      bool zUhPZPdzrY = false;
      bool lAYilJxtVH = false;
      bool acXncfBPJx = false;
      bool woaKyibMbc = false;
      bool mguPKqYnLK = false;
      bool EnMhKWxtmt = false;
      bool NNpubxYNjC = false;
      string UAHIGkkIil;
      string zsCWqEfWBx;
      string qhKFHwYkFj;
      string CUlJfASWrI;
      string XjKFrEjIrf;
      string gVfDPloBBJ;
      string MADzidHrqp;
      string kIdsYGWENC;
      string LPsZDgnits;
      string LRVhwXgLWN;
      string xqRBtXqmeI;
      string PjmzxwGcwC;
      string pYyxeTmwxA;
      string ZKhzEUyqef;
      string pBDkdadVkz;
      string RDPUXYrTVa;
      string jupdiFBntc;
      string yOyQLnUNTD;
      string oQLxiWtNbf;
      string bdUDuuLZCY;
      if(UAHIGkkIil == xqRBtXqmeI){ZpbHBCEzIi = true;}
      else if(xqRBtXqmeI == UAHIGkkIil){dYNczfWQwy = true;}
      if(zsCWqEfWBx == PjmzxwGcwC){DeASlSiruL = true;}
      else if(PjmzxwGcwC == zsCWqEfWBx){EKcCrQgmnx = true;}
      if(qhKFHwYkFj == pYyxeTmwxA){KmLNBTstUP = true;}
      else if(pYyxeTmwxA == qhKFHwYkFj){qxXyTCihok = true;}
      if(CUlJfASWrI == ZKhzEUyqef){cuLudyoDwg = true;}
      else if(ZKhzEUyqef == CUlJfASWrI){zUhPZPdzrY = true;}
      if(XjKFrEjIrf == pBDkdadVkz){RtFrcxdCRc = true;}
      else if(pBDkdadVkz == XjKFrEjIrf){lAYilJxtVH = true;}
      if(gVfDPloBBJ == RDPUXYrTVa){LTepNldNGh = true;}
      else if(RDPUXYrTVa == gVfDPloBBJ){acXncfBPJx = true;}
      if(MADzidHrqp == jupdiFBntc){IJerGISEon = true;}
      else if(jupdiFBntc == MADzidHrqp){woaKyibMbc = true;}
      if(kIdsYGWENC == yOyQLnUNTD){cfwNsPhTkE = true;}
      if(LPsZDgnits == oQLxiWtNbf){oqcqEJQVgq = true;}
      if(LRVhwXgLWN == bdUDuuLZCY){TaxNYHPMkU = true;}
      while(yOyQLnUNTD == kIdsYGWENC){mguPKqYnLK = true;}
      while(oQLxiWtNbf == oQLxiWtNbf){EnMhKWxtmt = true;}
      while(bdUDuuLZCY == bdUDuuLZCY){NNpubxYNjC = true;}
      if(ZpbHBCEzIi == true){ZpbHBCEzIi = false;}
      if(DeASlSiruL == true){DeASlSiruL = false;}
      if(KmLNBTstUP == true){KmLNBTstUP = false;}
      if(cuLudyoDwg == true){cuLudyoDwg = false;}
      if(RtFrcxdCRc == true){RtFrcxdCRc = false;}
      if(LTepNldNGh == true){LTepNldNGh = false;}
      if(IJerGISEon == true){IJerGISEon = false;}
      if(cfwNsPhTkE == true){cfwNsPhTkE = false;}
      if(oqcqEJQVgq == true){oqcqEJQVgq = false;}
      if(TaxNYHPMkU == true){TaxNYHPMkU = false;}
      if(dYNczfWQwy == true){dYNczfWQwy = false;}
      if(EKcCrQgmnx == true){EKcCrQgmnx = false;}
      if(qxXyTCihok == true){qxXyTCihok = false;}
      if(zUhPZPdzrY == true){zUhPZPdzrY = false;}
      if(lAYilJxtVH == true){lAYilJxtVH = false;}
      if(acXncfBPJx == true){acXncfBPJx = false;}
      if(woaKyibMbc == true){woaKyibMbc = false;}
      if(mguPKqYnLK == true){mguPKqYnLK = false;}
      if(EnMhKWxtmt == true){EnMhKWxtmt = false;}
      if(NNpubxYNjC == true){NNpubxYNjC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QBIUUUPZXY
{ 
  void AhiEeYbTyJ()
  { 
      bool WwIfltLEbG = false;
      bool TEbVAdMNHD = false;
      bool lFxVdUuzDr = false;
      bool OrAXNdxDNS = false;
      bool TJPJeFJspr = false;
      bool ZuegDRymCR = false;
      bool zMAiqbEDHW = false;
      bool gJAoibpnpY = false;
      bool LCILSTNSUw = false;
      bool eJBwTHJfRD = false;
      bool BFkTLQuoxa = false;
      bool aKwcGxDoQX = false;
      bool OkiLrWHEVb = false;
      bool SJWmWFQoAB = false;
      bool YXVtUTNXoV = false;
      bool ETOsoPWZbn = false;
      bool IpTVHRnJGA = false;
      bool fOoPzqPnpX = false;
      bool JjOzXytcxH = false;
      bool iqMLrhDzlD = false;
      string eJIFcyfWlq;
      string gMnUHDhFtw;
      string gdpbBpySoc;
      string sEftijAAta;
      string wpWUDRrdjN;
      string BKZlHASgDl;
      string ANhJxbftlW;
      string CgKSApHVXj;
      string yThaaietmi;
      string RSxHZiINWb;
      string kxrMKTzGlR;
      string swITngeGhO;
      string wlHCFjjDrQ;
      string gszuyAaVQH;
      string iXHUoUJdTr;
      string DBeHfypoGZ;
      string jwNUjAxNUm;
      string GJpafYelNk;
      string ZFiAMfNqPz;
      string JkOpWmJlko;
      if(eJIFcyfWlq == kxrMKTzGlR){WwIfltLEbG = true;}
      else if(kxrMKTzGlR == eJIFcyfWlq){BFkTLQuoxa = true;}
      if(gMnUHDhFtw == swITngeGhO){TEbVAdMNHD = true;}
      else if(swITngeGhO == gMnUHDhFtw){aKwcGxDoQX = true;}
      if(gdpbBpySoc == wlHCFjjDrQ){lFxVdUuzDr = true;}
      else if(wlHCFjjDrQ == gdpbBpySoc){OkiLrWHEVb = true;}
      if(sEftijAAta == gszuyAaVQH){OrAXNdxDNS = true;}
      else if(gszuyAaVQH == sEftijAAta){SJWmWFQoAB = true;}
      if(wpWUDRrdjN == iXHUoUJdTr){TJPJeFJspr = true;}
      else if(iXHUoUJdTr == wpWUDRrdjN){YXVtUTNXoV = true;}
      if(BKZlHASgDl == DBeHfypoGZ){ZuegDRymCR = true;}
      else if(DBeHfypoGZ == BKZlHASgDl){ETOsoPWZbn = true;}
      if(ANhJxbftlW == jwNUjAxNUm){zMAiqbEDHW = true;}
      else if(jwNUjAxNUm == ANhJxbftlW){IpTVHRnJGA = true;}
      if(CgKSApHVXj == GJpafYelNk){gJAoibpnpY = true;}
      if(yThaaietmi == ZFiAMfNqPz){LCILSTNSUw = true;}
      if(RSxHZiINWb == JkOpWmJlko){eJBwTHJfRD = true;}
      while(GJpafYelNk == CgKSApHVXj){fOoPzqPnpX = true;}
      while(ZFiAMfNqPz == ZFiAMfNqPz){JjOzXytcxH = true;}
      while(JkOpWmJlko == JkOpWmJlko){iqMLrhDzlD = true;}
      if(WwIfltLEbG == true){WwIfltLEbG = false;}
      if(TEbVAdMNHD == true){TEbVAdMNHD = false;}
      if(lFxVdUuzDr == true){lFxVdUuzDr = false;}
      if(OrAXNdxDNS == true){OrAXNdxDNS = false;}
      if(TJPJeFJspr == true){TJPJeFJspr = false;}
      if(ZuegDRymCR == true){ZuegDRymCR = false;}
      if(zMAiqbEDHW == true){zMAiqbEDHW = false;}
      if(gJAoibpnpY == true){gJAoibpnpY = false;}
      if(LCILSTNSUw == true){LCILSTNSUw = false;}
      if(eJBwTHJfRD == true){eJBwTHJfRD = false;}
      if(BFkTLQuoxa == true){BFkTLQuoxa = false;}
      if(aKwcGxDoQX == true){aKwcGxDoQX = false;}
      if(OkiLrWHEVb == true){OkiLrWHEVb = false;}
      if(SJWmWFQoAB == true){SJWmWFQoAB = false;}
      if(YXVtUTNXoV == true){YXVtUTNXoV = false;}
      if(ETOsoPWZbn == true){ETOsoPWZbn = false;}
      if(IpTVHRnJGA == true){IpTVHRnJGA = false;}
      if(fOoPzqPnpX == true){fOoPzqPnpX = false;}
      if(JjOzXytcxH == true){JjOzXytcxH = false;}
      if(iqMLrhDzlD == true){iqMLrhDzlD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKKTSIVRQW
{ 
  void fxOHwbXtZV()
  { 
      bool hJbTIVwKbe = false;
      bool MEhwWJNDVq = false;
      bool CZwhtFNYzw = false;
      bool GwRhEzkZwO = false;
      bool cUkllNdWWs = false;
      bool ioKVpINtYD = false;
      bool IXKfYQmzrX = false;
      bool YnGGOgoJuf = false;
      bool bqCGMRkurw = false;
      bool kqAsGFKEMV = false;
      bool addyTuhEHI = false;
      bool SDysbRVDTH = false;
      bool eqHwlhmNzI = false;
      bool WjxZFxMDmR = false;
      bool igmichrHRo = false;
      bool jGjFqjVhMl = false;
      bool HTEzlhGXmd = false;
      bool ESQCXxDYSE = false;
      bool ofwKYPAqiV = false;
      bool adpAJPbnwt = false;
      string gihLMUMsIi;
      string MorPSfunag;
      string jWJwuwzkNL;
      string xVtrLRRuOh;
      string KmmGVAwQra;
      string rIfOEJZkQQ;
      string VaewlpuzEA;
      string NAYrVxiCat;
      string AhslSnpemB;
      string rgdxMjHqTe;
      string FwMqMrinrH;
      string ZWJVQmhrcy;
      string APLCIgVael;
      string oriwoDVBZZ;
      string EBlfaVXIgZ;
      string BPNVdpjJif;
      string WHIGRhmNgN;
      string QfSDszcfbl;
      string IMtFjZeNRz;
      string SLSsDxrfNs;
      if(gihLMUMsIi == FwMqMrinrH){hJbTIVwKbe = true;}
      else if(FwMqMrinrH == gihLMUMsIi){addyTuhEHI = true;}
      if(MorPSfunag == ZWJVQmhrcy){MEhwWJNDVq = true;}
      else if(ZWJVQmhrcy == MorPSfunag){SDysbRVDTH = true;}
      if(jWJwuwzkNL == APLCIgVael){CZwhtFNYzw = true;}
      else if(APLCIgVael == jWJwuwzkNL){eqHwlhmNzI = true;}
      if(xVtrLRRuOh == oriwoDVBZZ){GwRhEzkZwO = true;}
      else if(oriwoDVBZZ == xVtrLRRuOh){WjxZFxMDmR = true;}
      if(KmmGVAwQra == EBlfaVXIgZ){cUkllNdWWs = true;}
      else if(EBlfaVXIgZ == KmmGVAwQra){igmichrHRo = true;}
      if(rIfOEJZkQQ == BPNVdpjJif){ioKVpINtYD = true;}
      else if(BPNVdpjJif == rIfOEJZkQQ){jGjFqjVhMl = true;}
      if(VaewlpuzEA == WHIGRhmNgN){IXKfYQmzrX = true;}
      else if(WHIGRhmNgN == VaewlpuzEA){HTEzlhGXmd = true;}
      if(NAYrVxiCat == QfSDszcfbl){YnGGOgoJuf = true;}
      if(AhslSnpemB == IMtFjZeNRz){bqCGMRkurw = true;}
      if(rgdxMjHqTe == SLSsDxrfNs){kqAsGFKEMV = true;}
      while(QfSDszcfbl == NAYrVxiCat){ESQCXxDYSE = true;}
      while(IMtFjZeNRz == IMtFjZeNRz){ofwKYPAqiV = true;}
      while(SLSsDxrfNs == SLSsDxrfNs){adpAJPbnwt = true;}
      if(hJbTIVwKbe == true){hJbTIVwKbe = false;}
      if(MEhwWJNDVq == true){MEhwWJNDVq = false;}
      if(CZwhtFNYzw == true){CZwhtFNYzw = false;}
      if(GwRhEzkZwO == true){GwRhEzkZwO = false;}
      if(cUkllNdWWs == true){cUkllNdWWs = false;}
      if(ioKVpINtYD == true){ioKVpINtYD = false;}
      if(IXKfYQmzrX == true){IXKfYQmzrX = false;}
      if(YnGGOgoJuf == true){YnGGOgoJuf = false;}
      if(bqCGMRkurw == true){bqCGMRkurw = false;}
      if(kqAsGFKEMV == true){kqAsGFKEMV = false;}
      if(addyTuhEHI == true){addyTuhEHI = false;}
      if(SDysbRVDTH == true){SDysbRVDTH = false;}
      if(eqHwlhmNzI == true){eqHwlhmNzI = false;}
      if(WjxZFxMDmR == true){WjxZFxMDmR = false;}
      if(igmichrHRo == true){igmichrHRo = false;}
      if(jGjFqjVhMl == true){jGjFqjVhMl = false;}
      if(HTEzlhGXmd == true){HTEzlhGXmd = false;}
      if(ESQCXxDYSE == true){ESQCXxDYSE = false;}
      if(ofwKYPAqiV == true){ofwKYPAqiV = false;}
      if(adpAJPbnwt == true){adpAJPbnwt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCEXLBZCRA
{ 
  void PjVRbjydYL()
  { 
      bool WDTjJAelJs = false;
      bool JHNgzJgYNu = false;
      bool gqfAjHHwLa = false;
      bool SoHIsEXQwc = false;
      bool FwhiVoFVjK = false;
      bool rAqweeXSAB = false;
      bool shZiaUAEnu = false;
      bool lQckokIxdt = false;
      bool BkMBhRyLdN = false;
      bool gFPtiXVzHB = false;
      bool oBgoXbXFGt = false;
      bool WanGAIVYAJ = false;
      bool VoZaNgAiBR = false;
      bool PJocEAEXcG = false;
      bool trEiqFQJsa = false;
      bool BwyyeAaGaq = false;
      bool anEoeMlLBz = false;
      bool DywsPdjpjI = false;
      bool PpoZPSKqxE = false;
      bool ZywkfFmOEd = false;
      string sRXxmKezpy;
      string LwWOQGZlUM;
      string LJHCAXBADW;
      string fpYEaCDPQU;
      string AfnkETsTgg;
      string FWSsGjJUxO;
      string JduTRUWSnO;
      string DKUzLfUWyf;
      string dgSWQJXexq;
      string shRCLWjUSi;
      string wafSdtBSha;
      string PmWQjbKYCI;
      string xrUxVUrSno;
      string uADOjDBArW;
      string HExWaGLARi;
      string LKRKlEFixI;
      string ChdreOiHgg;
      string ZKffArtyVP;
      string IrBFdjhrbf;
      string xSDjUZZFqM;
      if(sRXxmKezpy == wafSdtBSha){WDTjJAelJs = true;}
      else if(wafSdtBSha == sRXxmKezpy){oBgoXbXFGt = true;}
      if(LwWOQGZlUM == PmWQjbKYCI){JHNgzJgYNu = true;}
      else if(PmWQjbKYCI == LwWOQGZlUM){WanGAIVYAJ = true;}
      if(LJHCAXBADW == xrUxVUrSno){gqfAjHHwLa = true;}
      else if(xrUxVUrSno == LJHCAXBADW){VoZaNgAiBR = true;}
      if(fpYEaCDPQU == uADOjDBArW){SoHIsEXQwc = true;}
      else if(uADOjDBArW == fpYEaCDPQU){PJocEAEXcG = true;}
      if(AfnkETsTgg == HExWaGLARi){FwhiVoFVjK = true;}
      else if(HExWaGLARi == AfnkETsTgg){trEiqFQJsa = true;}
      if(FWSsGjJUxO == LKRKlEFixI){rAqweeXSAB = true;}
      else if(LKRKlEFixI == FWSsGjJUxO){BwyyeAaGaq = true;}
      if(JduTRUWSnO == ChdreOiHgg){shZiaUAEnu = true;}
      else if(ChdreOiHgg == JduTRUWSnO){anEoeMlLBz = true;}
      if(DKUzLfUWyf == ZKffArtyVP){lQckokIxdt = true;}
      if(dgSWQJXexq == IrBFdjhrbf){BkMBhRyLdN = true;}
      if(shRCLWjUSi == xSDjUZZFqM){gFPtiXVzHB = true;}
      while(ZKffArtyVP == DKUzLfUWyf){DywsPdjpjI = true;}
      while(IrBFdjhrbf == IrBFdjhrbf){PpoZPSKqxE = true;}
      while(xSDjUZZFqM == xSDjUZZFqM){ZywkfFmOEd = true;}
      if(WDTjJAelJs == true){WDTjJAelJs = false;}
      if(JHNgzJgYNu == true){JHNgzJgYNu = false;}
      if(gqfAjHHwLa == true){gqfAjHHwLa = false;}
      if(SoHIsEXQwc == true){SoHIsEXQwc = false;}
      if(FwhiVoFVjK == true){FwhiVoFVjK = false;}
      if(rAqweeXSAB == true){rAqweeXSAB = false;}
      if(shZiaUAEnu == true){shZiaUAEnu = false;}
      if(lQckokIxdt == true){lQckokIxdt = false;}
      if(BkMBhRyLdN == true){BkMBhRyLdN = false;}
      if(gFPtiXVzHB == true){gFPtiXVzHB = false;}
      if(oBgoXbXFGt == true){oBgoXbXFGt = false;}
      if(WanGAIVYAJ == true){WanGAIVYAJ = false;}
      if(VoZaNgAiBR == true){VoZaNgAiBR = false;}
      if(PJocEAEXcG == true){PJocEAEXcG = false;}
      if(trEiqFQJsa == true){trEiqFQJsa = false;}
      if(BwyyeAaGaq == true){BwyyeAaGaq = false;}
      if(anEoeMlLBz == true){anEoeMlLBz = false;}
      if(DywsPdjpjI == true){DywsPdjpjI = false;}
      if(PpoZPSKqxE == true){PpoZPSKqxE = false;}
      if(ZywkfFmOEd == true){ZywkfFmOEd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HWRZPPXTLV
{ 
  void iGaKptsdNu()
  { 
      bool RobquYjYiL = false;
      bool tJJZjfphSk = false;
      bool oFjZYFdScg = false;
      bool xQetCQawmr = false;
      bool JILBVOmiAc = false;
      bool BGQPALEBSo = false;
      bool uQwCNddOWS = false;
      bool EstabfthEJ = false;
      bool SuSAfpzPtq = false;
      bool LZcxwrLImq = false;
      bool jXLgXHLpmT = false;
      bool QWwJWAywWW = false;
      bool eOUeGeQwdj = false;
      bool TluMYtikbY = false;
      bool eJbZaocTaw = false;
      bool sPkPMVCfar = false;
      bool pOLDAeajjb = false;
      bool QNTyrUmuEQ = false;
      bool BwVhpEAezD = false;
      bool rDJjhPyXZu = false;
      string uogbnTDIPi;
      string NeuCpcnwkJ;
      string twfdwQubXp;
      string LUatcgtzVO;
      string dzOafUCPqQ;
      string shTsEyJDeX;
      string XajZXrDBZJ;
      string ioZWfthFxb;
      string OfkHwdBhod;
      string WqTxpCOnCn;
      string QBoghEHwNJ;
      string QEFCJrpcdt;
      string pVLwmqUcfc;
      string esDJLNpDZr;
      string VEUeMSkRnx;
      string LlKHxuostp;
      string ieQjdXBwpw;
      string CmCkXlAfiT;
      string GCnhQshuMP;
      string XwIjIqnjBo;
      if(uogbnTDIPi == QBoghEHwNJ){RobquYjYiL = true;}
      else if(QBoghEHwNJ == uogbnTDIPi){jXLgXHLpmT = true;}
      if(NeuCpcnwkJ == QEFCJrpcdt){tJJZjfphSk = true;}
      else if(QEFCJrpcdt == NeuCpcnwkJ){QWwJWAywWW = true;}
      if(twfdwQubXp == pVLwmqUcfc){oFjZYFdScg = true;}
      else if(pVLwmqUcfc == twfdwQubXp){eOUeGeQwdj = true;}
      if(LUatcgtzVO == esDJLNpDZr){xQetCQawmr = true;}
      else if(esDJLNpDZr == LUatcgtzVO){TluMYtikbY = true;}
      if(dzOafUCPqQ == VEUeMSkRnx){JILBVOmiAc = true;}
      else if(VEUeMSkRnx == dzOafUCPqQ){eJbZaocTaw = true;}
      if(shTsEyJDeX == LlKHxuostp){BGQPALEBSo = true;}
      else if(LlKHxuostp == shTsEyJDeX){sPkPMVCfar = true;}
      if(XajZXrDBZJ == ieQjdXBwpw){uQwCNddOWS = true;}
      else if(ieQjdXBwpw == XajZXrDBZJ){pOLDAeajjb = true;}
      if(ioZWfthFxb == CmCkXlAfiT){EstabfthEJ = true;}
      if(OfkHwdBhod == GCnhQshuMP){SuSAfpzPtq = true;}
      if(WqTxpCOnCn == XwIjIqnjBo){LZcxwrLImq = true;}
      while(CmCkXlAfiT == ioZWfthFxb){QNTyrUmuEQ = true;}
      while(GCnhQshuMP == GCnhQshuMP){BwVhpEAezD = true;}
      while(XwIjIqnjBo == XwIjIqnjBo){rDJjhPyXZu = true;}
      if(RobquYjYiL == true){RobquYjYiL = false;}
      if(tJJZjfphSk == true){tJJZjfphSk = false;}
      if(oFjZYFdScg == true){oFjZYFdScg = false;}
      if(xQetCQawmr == true){xQetCQawmr = false;}
      if(JILBVOmiAc == true){JILBVOmiAc = false;}
      if(BGQPALEBSo == true){BGQPALEBSo = false;}
      if(uQwCNddOWS == true){uQwCNddOWS = false;}
      if(EstabfthEJ == true){EstabfthEJ = false;}
      if(SuSAfpzPtq == true){SuSAfpzPtq = false;}
      if(LZcxwrLImq == true){LZcxwrLImq = false;}
      if(jXLgXHLpmT == true){jXLgXHLpmT = false;}
      if(QWwJWAywWW == true){QWwJWAywWW = false;}
      if(eOUeGeQwdj == true){eOUeGeQwdj = false;}
      if(TluMYtikbY == true){TluMYtikbY = false;}
      if(eJbZaocTaw == true){eJbZaocTaw = false;}
      if(sPkPMVCfar == true){sPkPMVCfar = false;}
      if(pOLDAeajjb == true){pOLDAeajjb = false;}
      if(QNTyrUmuEQ == true){QNTyrUmuEQ = false;}
      if(BwVhpEAezD == true){BwVhpEAezD = false;}
      if(rDJjhPyXZu == true){rDJjhPyXZu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZMDJHVZLGW
{ 
  void WeLNgjnaNE()
  { 
      bool fwWANKhdhl = false;
      bool RTmhoELlHp = false;
      bool iTUACkxmPo = false;
      bool SBYgiYByuU = false;
      bool MRfTUmoOqr = false;
      bool BksunMaVyb = false;
      bool NtOsTPtGyP = false;
      bool CMpldRnAfP = false;
      bool whwWmgIcsW = false;
      bool xeASHRClAE = false;
      bool rhQaootGRW = false;
      bool YZphfexrGm = false;
      bool GQMaSXLWdL = false;
      bool OCAaWNRUgy = false;
      bool lBLWxXnRmc = false;
      bool TKeNxbUoIQ = false;
      bool dXcFIWYPLS = false;
      bool MbKIAFEpcu = false;
      bool jsjBqDWmct = false;
      bool rbMPTOYGNa = false;
      string lWfrqEifto;
      string aTdgInAKIi;
      string XGhEfyAXbb;
      string XWQrCiKPxN;
      string EQrZmOzeBg;
      string tgZDnfnbLs;
      string EKERQEDldY;
      string ckMteHNIQR;
      string yVVthqxMDV;
      string tiDDJsLaJh;
      string KNAbEJTeYg;
      string SfKtthnJjY;
      string GphIdsgIjk;
      string umyhGkUtpY;
      string XRnWDOYJJa;
      string EBpjbUerxK;
      string bKumkfhbmI;
      string NtTLBoCLEP;
      string UXzJftwNGl;
      string GcwfwMWAlX;
      if(lWfrqEifto == KNAbEJTeYg){fwWANKhdhl = true;}
      else if(KNAbEJTeYg == lWfrqEifto){rhQaootGRW = true;}
      if(aTdgInAKIi == SfKtthnJjY){RTmhoELlHp = true;}
      else if(SfKtthnJjY == aTdgInAKIi){YZphfexrGm = true;}
      if(XGhEfyAXbb == GphIdsgIjk){iTUACkxmPo = true;}
      else if(GphIdsgIjk == XGhEfyAXbb){GQMaSXLWdL = true;}
      if(XWQrCiKPxN == umyhGkUtpY){SBYgiYByuU = true;}
      else if(umyhGkUtpY == XWQrCiKPxN){OCAaWNRUgy = true;}
      if(EQrZmOzeBg == XRnWDOYJJa){MRfTUmoOqr = true;}
      else if(XRnWDOYJJa == EQrZmOzeBg){lBLWxXnRmc = true;}
      if(tgZDnfnbLs == EBpjbUerxK){BksunMaVyb = true;}
      else if(EBpjbUerxK == tgZDnfnbLs){TKeNxbUoIQ = true;}
      if(EKERQEDldY == bKumkfhbmI){NtOsTPtGyP = true;}
      else if(bKumkfhbmI == EKERQEDldY){dXcFIWYPLS = true;}
      if(ckMteHNIQR == NtTLBoCLEP){CMpldRnAfP = true;}
      if(yVVthqxMDV == UXzJftwNGl){whwWmgIcsW = true;}
      if(tiDDJsLaJh == GcwfwMWAlX){xeASHRClAE = true;}
      while(NtTLBoCLEP == ckMteHNIQR){MbKIAFEpcu = true;}
      while(UXzJftwNGl == UXzJftwNGl){jsjBqDWmct = true;}
      while(GcwfwMWAlX == GcwfwMWAlX){rbMPTOYGNa = true;}
      if(fwWANKhdhl == true){fwWANKhdhl = false;}
      if(RTmhoELlHp == true){RTmhoELlHp = false;}
      if(iTUACkxmPo == true){iTUACkxmPo = false;}
      if(SBYgiYByuU == true){SBYgiYByuU = false;}
      if(MRfTUmoOqr == true){MRfTUmoOqr = false;}
      if(BksunMaVyb == true){BksunMaVyb = false;}
      if(NtOsTPtGyP == true){NtOsTPtGyP = false;}
      if(CMpldRnAfP == true){CMpldRnAfP = false;}
      if(whwWmgIcsW == true){whwWmgIcsW = false;}
      if(xeASHRClAE == true){xeASHRClAE = false;}
      if(rhQaootGRW == true){rhQaootGRW = false;}
      if(YZphfexrGm == true){YZphfexrGm = false;}
      if(GQMaSXLWdL == true){GQMaSXLWdL = false;}
      if(OCAaWNRUgy == true){OCAaWNRUgy = false;}
      if(lBLWxXnRmc == true){lBLWxXnRmc = false;}
      if(TKeNxbUoIQ == true){TKeNxbUoIQ = false;}
      if(dXcFIWYPLS == true){dXcFIWYPLS = false;}
      if(MbKIAFEpcu == true){MbKIAFEpcu = false;}
      if(jsjBqDWmct == true){jsjBqDWmct = false;}
      if(rbMPTOYGNa == true){rbMPTOYGNa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UNVKDCJYYB
{ 
  void PFgeawSLUC()
  { 
      bool LYUOZGuuQI = false;
      bool yCDTfwtzWH = false;
      bool LVDegtejBj = false;
      bool DjTWmmWFPg = false;
      bool qJZlIzeeOX = false;
      bool teoOZpVoge = false;
      bool aKsgENiffr = false;
      bool ZoioQBwQWg = false;
      bool PAVdpXtFxw = false;
      bool RgXjFgQrht = false;
      bool QyyVxEuAxX = false;
      bool tFRzPanOpg = false;
      bool SdiiasQyjj = false;
      bool kDicQQCAgk = false;
      bool ctHYCLPYUe = false;
      bool rBBAblPOtE = false;
      bool nxQMlqWohz = false;
      bool YnhFEXVJgO = false;
      bool crdEriBhAd = false;
      bool BmFcxedtmK = false;
      string uQhSGSxHxa;
      string NVJsyFwIgp;
      string XoZXLbgqcY;
      string PIsfuIQDJM;
      string lUVbwreShP;
      string dfEmIGpKHd;
      string lFdYKEbdyp;
      string osyUECTxbS;
      string xOJMtjDGWn;
      string RFufafqwQq;
      string QAUqakgjiF;
      string msingWwQea;
      string BUHJXixStX;
      string LWgjCwsRlI;
      string CTXQBYWGzD;
      string jZRoousLTq;
      string nOoKtQMylj;
      string cdeWYgxpHz;
      string LqTpnlEquG;
      string ChytUndMWk;
      if(uQhSGSxHxa == QAUqakgjiF){LYUOZGuuQI = true;}
      else if(QAUqakgjiF == uQhSGSxHxa){QyyVxEuAxX = true;}
      if(NVJsyFwIgp == msingWwQea){yCDTfwtzWH = true;}
      else if(msingWwQea == NVJsyFwIgp){tFRzPanOpg = true;}
      if(XoZXLbgqcY == BUHJXixStX){LVDegtejBj = true;}
      else if(BUHJXixStX == XoZXLbgqcY){SdiiasQyjj = true;}
      if(PIsfuIQDJM == LWgjCwsRlI){DjTWmmWFPg = true;}
      else if(LWgjCwsRlI == PIsfuIQDJM){kDicQQCAgk = true;}
      if(lUVbwreShP == CTXQBYWGzD){qJZlIzeeOX = true;}
      else if(CTXQBYWGzD == lUVbwreShP){ctHYCLPYUe = true;}
      if(dfEmIGpKHd == jZRoousLTq){teoOZpVoge = true;}
      else if(jZRoousLTq == dfEmIGpKHd){rBBAblPOtE = true;}
      if(lFdYKEbdyp == nOoKtQMylj){aKsgENiffr = true;}
      else if(nOoKtQMylj == lFdYKEbdyp){nxQMlqWohz = true;}
      if(osyUECTxbS == cdeWYgxpHz){ZoioQBwQWg = true;}
      if(xOJMtjDGWn == LqTpnlEquG){PAVdpXtFxw = true;}
      if(RFufafqwQq == ChytUndMWk){RgXjFgQrht = true;}
      while(cdeWYgxpHz == osyUECTxbS){YnhFEXVJgO = true;}
      while(LqTpnlEquG == LqTpnlEquG){crdEriBhAd = true;}
      while(ChytUndMWk == ChytUndMWk){BmFcxedtmK = true;}
      if(LYUOZGuuQI == true){LYUOZGuuQI = false;}
      if(yCDTfwtzWH == true){yCDTfwtzWH = false;}
      if(LVDegtejBj == true){LVDegtejBj = false;}
      if(DjTWmmWFPg == true){DjTWmmWFPg = false;}
      if(qJZlIzeeOX == true){qJZlIzeeOX = false;}
      if(teoOZpVoge == true){teoOZpVoge = false;}
      if(aKsgENiffr == true){aKsgENiffr = false;}
      if(ZoioQBwQWg == true){ZoioQBwQWg = false;}
      if(PAVdpXtFxw == true){PAVdpXtFxw = false;}
      if(RgXjFgQrht == true){RgXjFgQrht = false;}
      if(QyyVxEuAxX == true){QyyVxEuAxX = false;}
      if(tFRzPanOpg == true){tFRzPanOpg = false;}
      if(SdiiasQyjj == true){SdiiasQyjj = false;}
      if(kDicQQCAgk == true){kDicQQCAgk = false;}
      if(ctHYCLPYUe == true){ctHYCLPYUe = false;}
      if(rBBAblPOtE == true){rBBAblPOtE = false;}
      if(nxQMlqWohz == true){nxQMlqWohz = false;}
      if(YnhFEXVJgO == true){YnhFEXVJgO = false;}
      if(crdEriBhAd == true){crdEriBhAd = false;}
      if(BmFcxedtmK == true){BmFcxedtmK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FKZABKGQDD
{ 
  void JFCLYGjzsa()
  { 
      bool ANUwnDABTg = false;
      bool daETgRGdfw = false;
      bool IMJoOOArcP = false;
      bool VVTtZqCaIm = false;
      bool nZebEtIfpx = false;
      bool cSHhKmEfhZ = false;
      bool CIXDKIGJso = false;
      bool OeVsIhggkU = false;
      bool FUCflCNkil = false;
      bool mWshjeBaQw = false;
      bool mzlAiyxNZc = false;
      bool GWtNThGrQH = false;
      bool tUZHCrkmIc = false;
      bool fFQogGhBwn = false;
      bool FzLGfQbfOC = false;
      bool YJJIBSYeyp = false;
      bool MJFxxAFFgN = false;
      bool zEwcBtJTbl = false;
      bool QFYGDWuHmN = false;
      bool hCDGbwtOJe = false;
      string hOZQwuyEdF;
      string ljMKqZXgXK;
      string wMnynmbewW;
      string uhlsgPiRSo;
      string RzypwGGMGO;
      string MxVJmVabcJ;
      string TTHGKExTca;
      string qGNhswNxBg;
      string fOYhKxMbFL;
      string oGoJVyqqfr;
      string JmjeXGinQp;
      string HcaucFtZwM;
      string rUNRlkQEMt;
      string FWRIWsesKE;
      string NYKPDLfsfP;
      string EQtSAnYRsl;
      string oeaWkkLRXi;
      string aAPrzSJyNZ;
      string FXXwpnbzIi;
      string UMzXOixndS;
      if(hOZQwuyEdF == JmjeXGinQp){ANUwnDABTg = true;}
      else if(JmjeXGinQp == hOZQwuyEdF){mzlAiyxNZc = true;}
      if(ljMKqZXgXK == HcaucFtZwM){daETgRGdfw = true;}
      else if(HcaucFtZwM == ljMKqZXgXK){GWtNThGrQH = true;}
      if(wMnynmbewW == rUNRlkQEMt){IMJoOOArcP = true;}
      else if(rUNRlkQEMt == wMnynmbewW){tUZHCrkmIc = true;}
      if(uhlsgPiRSo == FWRIWsesKE){VVTtZqCaIm = true;}
      else if(FWRIWsesKE == uhlsgPiRSo){fFQogGhBwn = true;}
      if(RzypwGGMGO == NYKPDLfsfP){nZebEtIfpx = true;}
      else if(NYKPDLfsfP == RzypwGGMGO){FzLGfQbfOC = true;}
      if(MxVJmVabcJ == EQtSAnYRsl){cSHhKmEfhZ = true;}
      else if(EQtSAnYRsl == MxVJmVabcJ){YJJIBSYeyp = true;}
      if(TTHGKExTca == oeaWkkLRXi){CIXDKIGJso = true;}
      else if(oeaWkkLRXi == TTHGKExTca){MJFxxAFFgN = true;}
      if(qGNhswNxBg == aAPrzSJyNZ){OeVsIhggkU = true;}
      if(fOYhKxMbFL == FXXwpnbzIi){FUCflCNkil = true;}
      if(oGoJVyqqfr == UMzXOixndS){mWshjeBaQw = true;}
      while(aAPrzSJyNZ == qGNhswNxBg){zEwcBtJTbl = true;}
      while(FXXwpnbzIi == FXXwpnbzIi){QFYGDWuHmN = true;}
      while(UMzXOixndS == UMzXOixndS){hCDGbwtOJe = true;}
      if(ANUwnDABTg == true){ANUwnDABTg = false;}
      if(daETgRGdfw == true){daETgRGdfw = false;}
      if(IMJoOOArcP == true){IMJoOOArcP = false;}
      if(VVTtZqCaIm == true){VVTtZqCaIm = false;}
      if(nZebEtIfpx == true){nZebEtIfpx = false;}
      if(cSHhKmEfhZ == true){cSHhKmEfhZ = false;}
      if(CIXDKIGJso == true){CIXDKIGJso = false;}
      if(OeVsIhggkU == true){OeVsIhggkU = false;}
      if(FUCflCNkil == true){FUCflCNkil = false;}
      if(mWshjeBaQw == true){mWshjeBaQw = false;}
      if(mzlAiyxNZc == true){mzlAiyxNZc = false;}
      if(GWtNThGrQH == true){GWtNThGrQH = false;}
      if(tUZHCrkmIc == true){tUZHCrkmIc = false;}
      if(fFQogGhBwn == true){fFQogGhBwn = false;}
      if(FzLGfQbfOC == true){FzLGfQbfOC = false;}
      if(YJJIBSYeyp == true){YJJIBSYeyp = false;}
      if(MJFxxAFFgN == true){MJFxxAFFgN = false;}
      if(zEwcBtJTbl == true){zEwcBtJTbl = false;}
      if(QFYGDWuHmN == true){QFYGDWuHmN = false;}
      if(hCDGbwtOJe == true){hCDGbwtOJe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CKTXFZSLPC
{ 
  void tQHFHwWHzQ()
  { 
      bool rehygfZToi = false;
      bool fketnEcoIX = false;
      bool BOyBdjtQzu = false;
      bool LIpxKictKz = false;
      bool KVLakholXN = false;
      bool sXYumcffUx = false;
      bool kIUtWXugiF = false;
      bool bhdJMfDXQw = false;
      bool tHslBnitJh = false;
      bool CwZNNBBRDM = false;
      bool lHCRkKsOiH = false;
      bool ZIPYCdPhri = false;
      bool nBWBDeIQuK = false;
      bool elTDJmEbAp = false;
      bool tUKCHsgBKj = false;
      bool lSYTYjkBOG = false;
      bool CcSXcmnLOP = false;
      bool YmhBoSpUsJ = false;
      bool yGFLYMNAeY = false;
      bool BDMtnQBmZU = false;
      string nHdiBmfnPj;
      string AiQtRDwVrI;
      string iJKEKqalgE;
      string SXZEcbneUn;
      string HAwjGqsDyR;
      string tMQbedxYYK;
      string MsGKRcJLRo;
      string PRAEAhMZxT;
      string xWmPKFHxZy;
      string eOFKaNtlSd;
      string ghkICbMLbx;
      string RWbENoGqAL;
      string ULlTKALpdm;
      string naHSlPleNh;
      string suVcfHmAwk;
      string HDkHIVuRxB;
      string PWhnIqPISy;
      string DacRRZoJmD;
      string NKsrekoAKQ;
      string TTgLSWNgTo;
      if(nHdiBmfnPj == ghkICbMLbx){rehygfZToi = true;}
      else if(ghkICbMLbx == nHdiBmfnPj){lHCRkKsOiH = true;}
      if(AiQtRDwVrI == RWbENoGqAL){fketnEcoIX = true;}
      else if(RWbENoGqAL == AiQtRDwVrI){ZIPYCdPhri = true;}
      if(iJKEKqalgE == ULlTKALpdm){BOyBdjtQzu = true;}
      else if(ULlTKALpdm == iJKEKqalgE){nBWBDeIQuK = true;}
      if(SXZEcbneUn == naHSlPleNh){LIpxKictKz = true;}
      else if(naHSlPleNh == SXZEcbneUn){elTDJmEbAp = true;}
      if(HAwjGqsDyR == suVcfHmAwk){KVLakholXN = true;}
      else if(suVcfHmAwk == HAwjGqsDyR){tUKCHsgBKj = true;}
      if(tMQbedxYYK == HDkHIVuRxB){sXYumcffUx = true;}
      else if(HDkHIVuRxB == tMQbedxYYK){lSYTYjkBOG = true;}
      if(MsGKRcJLRo == PWhnIqPISy){kIUtWXugiF = true;}
      else if(PWhnIqPISy == MsGKRcJLRo){CcSXcmnLOP = true;}
      if(PRAEAhMZxT == DacRRZoJmD){bhdJMfDXQw = true;}
      if(xWmPKFHxZy == NKsrekoAKQ){tHslBnitJh = true;}
      if(eOFKaNtlSd == TTgLSWNgTo){CwZNNBBRDM = true;}
      while(DacRRZoJmD == PRAEAhMZxT){YmhBoSpUsJ = true;}
      while(NKsrekoAKQ == NKsrekoAKQ){yGFLYMNAeY = true;}
      while(TTgLSWNgTo == TTgLSWNgTo){BDMtnQBmZU = true;}
      if(rehygfZToi == true){rehygfZToi = false;}
      if(fketnEcoIX == true){fketnEcoIX = false;}
      if(BOyBdjtQzu == true){BOyBdjtQzu = false;}
      if(LIpxKictKz == true){LIpxKictKz = false;}
      if(KVLakholXN == true){KVLakholXN = false;}
      if(sXYumcffUx == true){sXYumcffUx = false;}
      if(kIUtWXugiF == true){kIUtWXugiF = false;}
      if(bhdJMfDXQw == true){bhdJMfDXQw = false;}
      if(tHslBnitJh == true){tHslBnitJh = false;}
      if(CwZNNBBRDM == true){CwZNNBBRDM = false;}
      if(lHCRkKsOiH == true){lHCRkKsOiH = false;}
      if(ZIPYCdPhri == true){ZIPYCdPhri = false;}
      if(nBWBDeIQuK == true){nBWBDeIQuK = false;}
      if(elTDJmEbAp == true){elTDJmEbAp = false;}
      if(tUKCHsgBKj == true){tUKCHsgBKj = false;}
      if(lSYTYjkBOG == true){lSYTYjkBOG = false;}
      if(CcSXcmnLOP == true){CcSXcmnLOP = false;}
      if(YmhBoSpUsJ == true){YmhBoSpUsJ = false;}
      if(yGFLYMNAeY == true){yGFLYMNAeY = false;}
      if(BDMtnQBmZU == true){BDMtnQBmZU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSTFNYVAQN
{ 
  void QAtzOjqLGX()
  { 
      bool mJhQOyjmDJ = false;
      bool IIOKUXJCkq = false;
      bool NGkkyoyAuM = false;
      bool QkVVWFlcoN = false;
      bool mFidJeerNc = false;
      bool ttkDefYxRY = false;
      bool AiqprXmsmO = false;
      bool lfMXDHXGaS = false;
      bool JGlRSVzRpp = false;
      bool gnKQNDNrkl = false;
      bool qlFyqNgNAW = false;
      bool IRVzOswYXW = false;
      bool YVCwgxUwKA = false;
      bool tfVoaXBmaE = false;
      bool nlRShPSLBT = false;
      bool GoUONVjIQs = false;
      bool skCzccugXq = false;
      bool rJyThlEiNR = false;
      bool eJtqsEKHbF = false;
      bool nrVgKDiRoF = false;
      string HQoCPhYuNl;
      string GnTXuEcQoW;
      string jSULiBIPsb;
      string GddfYaruQf;
      string iXMWOEnrfs;
      string hzRyQowdTN;
      string YICkebJnzU;
      string LhzImLFxwe;
      string NQiAtGLfOj;
      string dOaDGZUbrm;
      string tzrLgzzIKE;
      string jygnAIZCqX;
      string QcZOpxHwCM;
      string pcFJjNXXSt;
      string HDUJzfglCy;
      string ASjTWQZdUj;
      string rDGxOGrXEl;
      string jBixQMIQOK;
      string PUsDMWslmS;
      string ntChBDwWus;
      if(HQoCPhYuNl == tzrLgzzIKE){mJhQOyjmDJ = true;}
      else if(tzrLgzzIKE == HQoCPhYuNl){qlFyqNgNAW = true;}
      if(GnTXuEcQoW == jygnAIZCqX){IIOKUXJCkq = true;}
      else if(jygnAIZCqX == GnTXuEcQoW){IRVzOswYXW = true;}
      if(jSULiBIPsb == QcZOpxHwCM){NGkkyoyAuM = true;}
      else if(QcZOpxHwCM == jSULiBIPsb){YVCwgxUwKA = true;}
      if(GddfYaruQf == pcFJjNXXSt){QkVVWFlcoN = true;}
      else if(pcFJjNXXSt == GddfYaruQf){tfVoaXBmaE = true;}
      if(iXMWOEnrfs == HDUJzfglCy){mFidJeerNc = true;}
      else if(HDUJzfglCy == iXMWOEnrfs){nlRShPSLBT = true;}
      if(hzRyQowdTN == ASjTWQZdUj){ttkDefYxRY = true;}
      else if(ASjTWQZdUj == hzRyQowdTN){GoUONVjIQs = true;}
      if(YICkebJnzU == rDGxOGrXEl){AiqprXmsmO = true;}
      else if(rDGxOGrXEl == YICkebJnzU){skCzccugXq = true;}
      if(LhzImLFxwe == jBixQMIQOK){lfMXDHXGaS = true;}
      if(NQiAtGLfOj == PUsDMWslmS){JGlRSVzRpp = true;}
      if(dOaDGZUbrm == ntChBDwWus){gnKQNDNrkl = true;}
      while(jBixQMIQOK == LhzImLFxwe){rJyThlEiNR = true;}
      while(PUsDMWslmS == PUsDMWslmS){eJtqsEKHbF = true;}
      while(ntChBDwWus == ntChBDwWus){nrVgKDiRoF = true;}
      if(mJhQOyjmDJ == true){mJhQOyjmDJ = false;}
      if(IIOKUXJCkq == true){IIOKUXJCkq = false;}
      if(NGkkyoyAuM == true){NGkkyoyAuM = false;}
      if(QkVVWFlcoN == true){QkVVWFlcoN = false;}
      if(mFidJeerNc == true){mFidJeerNc = false;}
      if(ttkDefYxRY == true){ttkDefYxRY = false;}
      if(AiqprXmsmO == true){AiqprXmsmO = false;}
      if(lfMXDHXGaS == true){lfMXDHXGaS = false;}
      if(JGlRSVzRpp == true){JGlRSVzRpp = false;}
      if(gnKQNDNrkl == true){gnKQNDNrkl = false;}
      if(qlFyqNgNAW == true){qlFyqNgNAW = false;}
      if(IRVzOswYXW == true){IRVzOswYXW = false;}
      if(YVCwgxUwKA == true){YVCwgxUwKA = false;}
      if(tfVoaXBmaE == true){tfVoaXBmaE = false;}
      if(nlRShPSLBT == true){nlRShPSLBT = false;}
      if(GoUONVjIQs == true){GoUONVjIQs = false;}
      if(skCzccugXq == true){skCzccugXq = false;}
      if(rJyThlEiNR == true){rJyThlEiNR = false;}
      if(eJtqsEKHbF == true){eJtqsEKHbF = false;}
      if(nrVgKDiRoF == true){nrVgKDiRoF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LRVORYLDJG
{ 
  void EqXXmhllWK()
  { 
      bool AqqnRlrsgZ = false;
      bool pApssxmhfa = false;
      bool PxBfQmVPjK = false;
      bool CHGFrEraND = false;
      bool XhuwNBYIhy = false;
      bool RIMjFDpKXd = false;
      bool QbJWXhskAn = false;
      bool ELUcCgBESO = false;
      bool OMhlsstWzo = false;
      bool OgDilwYYYe = false;
      bool InHssFnjgY = false;
      bool BkrJPDtXce = false;
      bool nWkLZXIkpG = false;
      bool HbemFZEnrm = false;
      bool EKoZmcosSh = false;
      bool BBwsqkCwTV = false;
      bool xDtaQYFFDp = false;
      bool yFepadgLXw = false;
      bool hORHEGflwU = false;
      bool XITVpAPOJO = false;
      string nGZozHBZRT;
      string PUnkSrJDgt;
      string BGMAGGlwDj;
      string SsWZoWDpma;
      string ZLSTpEzACn;
      string MnWnghtYhs;
      string VFVhAWxNuw;
      string oTPGTomsKC;
      string GktPWeWhsH;
      string bdHtFUpkST;
      string GlEFzsXQTq;
      string tBOfmjLGKV;
      string zOTnTKLVBz;
      string zCZpuTgnPd;
      string GGNCMaObGU;
      string JiZxTqRQln;
      string hBOUqqaXjS;
      string DWqfPsARar;
      string ujOfoQbcWE;
      string CPBawEqsKV;
      if(nGZozHBZRT == GlEFzsXQTq){AqqnRlrsgZ = true;}
      else if(GlEFzsXQTq == nGZozHBZRT){InHssFnjgY = true;}
      if(PUnkSrJDgt == tBOfmjLGKV){pApssxmhfa = true;}
      else if(tBOfmjLGKV == PUnkSrJDgt){BkrJPDtXce = true;}
      if(BGMAGGlwDj == zOTnTKLVBz){PxBfQmVPjK = true;}
      else if(zOTnTKLVBz == BGMAGGlwDj){nWkLZXIkpG = true;}
      if(SsWZoWDpma == zCZpuTgnPd){CHGFrEraND = true;}
      else if(zCZpuTgnPd == SsWZoWDpma){HbemFZEnrm = true;}
      if(ZLSTpEzACn == GGNCMaObGU){XhuwNBYIhy = true;}
      else if(GGNCMaObGU == ZLSTpEzACn){EKoZmcosSh = true;}
      if(MnWnghtYhs == JiZxTqRQln){RIMjFDpKXd = true;}
      else if(JiZxTqRQln == MnWnghtYhs){BBwsqkCwTV = true;}
      if(VFVhAWxNuw == hBOUqqaXjS){QbJWXhskAn = true;}
      else if(hBOUqqaXjS == VFVhAWxNuw){xDtaQYFFDp = true;}
      if(oTPGTomsKC == DWqfPsARar){ELUcCgBESO = true;}
      if(GktPWeWhsH == ujOfoQbcWE){OMhlsstWzo = true;}
      if(bdHtFUpkST == CPBawEqsKV){OgDilwYYYe = true;}
      while(DWqfPsARar == oTPGTomsKC){yFepadgLXw = true;}
      while(ujOfoQbcWE == ujOfoQbcWE){hORHEGflwU = true;}
      while(CPBawEqsKV == CPBawEqsKV){XITVpAPOJO = true;}
      if(AqqnRlrsgZ == true){AqqnRlrsgZ = false;}
      if(pApssxmhfa == true){pApssxmhfa = false;}
      if(PxBfQmVPjK == true){PxBfQmVPjK = false;}
      if(CHGFrEraND == true){CHGFrEraND = false;}
      if(XhuwNBYIhy == true){XhuwNBYIhy = false;}
      if(RIMjFDpKXd == true){RIMjFDpKXd = false;}
      if(QbJWXhskAn == true){QbJWXhskAn = false;}
      if(ELUcCgBESO == true){ELUcCgBESO = false;}
      if(OMhlsstWzo == true){OMhlsstWzo = false;}
      if(OgDilwYYYe == true){OgDilwYYYe = false;}
      if(InHssFnjgY == true){InHssFnjgY = false;}
      if(BkrJPDtXce == true){BkrJPDtXce = false;}
      if(nWkLZXIkpG == true){nWkLZXIkpG = false;}
      if(HbemFZEnrm == true){HbemFZEnrm = false;}
      if(EKoZmcosSh == true){EKoZmcosSh = false;}
      if(BBwsqkCwTV == true){BBwsqkCwTV = false;}
      if(xDtaQYFFDp == true){xDtaQYFFDp = false;}
      if(yFepadgLXw == true){yFepadgLXw = false;}
      if(hORHEGflwU == true){hORHEGflwU = false;}
      if(XITVpAPOJO == true){XITVpAPOJO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LUQFLIMXBY
{ 
  void unFAhYtdFn()
  { 
      bool YnYoWcuiKo = false;
      bool jiqzSZCFEs = false;
      bool EjpxOyigAP = false;
      bool iMTRZlQaoF = false;
      bool hKwMCssUzZ = false;
      bool KPSRtoxbaY = false;
      bool sOhtGXPYYg = false;
      bool JbQyLsndtV = false;
      bool EOgaFTtBXk = false;
      bool nnzPMSbBGe = false;
      bool cUuSQhzTGB = false;
      bool ATgFUehGol = false;
      bool cOBmsUbAls = false;
      bool QlWPrjSOKW = false;
      bool UZuVjTHtuh = false;
      bool kVMTBOSIYw = false;
      bool GyhNjOxRMj = false;
      bool LTwSRDTeCY = false;
      bool NgEDIuZDOd = false;
      bool QKoOPVrglV = false;
      string eODtjNTCgZ;
      string YowOqNxVXY;
      string GZoinkWPgl;
      string VIhFcanDMX;
      string HauABUSHgX;
      string IZjTaFZUGz;
      string qEUtEPHqkQ;
      string YtJzRedogS;
      string RPhJduXNdX;
      string ATwNgCGAuk;
      string NaVPyNPjCu;
      string ajmngbVKQI;
      string rtNNPFywSO;
      string YcsuFpsSLP;
      string fmKhwQfIfF;
      string fujmsSNIzr;
      string PSRmWxqrip;
      string hDzAcEieQz;
      string ZpQMicsGBl;
      string bjTSzMUWLy;
      if(eODtjNTCgZ == NaVPyNPjCu){YnYoWcuiKo = true;}
      else if(NaVPyNPjCu == eODtjNTCgZ){cUuSQhzTGB = true;}
      if(YowOqNxVXY == ajmngbVKQI){jiqzSZCFEs = true;}
      else if(ajmngbVKQI == YowOqNxVXY){ATgFUehGol = true;}
      if(GZoinkWPgl == rtNNPFywSO){EjpxOyigAP = true;}
      else if(rtNNPFywSO == GZoinkWPgl){cOBmsUbAls = true;}
      if(VIhFcanDMX == YcsuFpsSLP){iMTRZlQaoF = true;}
      else if(YcsuFpsSLP == VIhFcanDMX){QlWPrjSOKW = true;}
      if(HauABUSHgX == fmKhwQfIfF){hKwMCssUzZ = true;}
      else if(fmKhwQfIfF == HauABUSHgX){UZuVjTHtuh = true;}
      if(IZjTaFZUGz == fujmsSNIzr){KPSRtoxbaY = true;}
      else if(fujmsSNIzr == IZjTaFZUGz){kVMTBOSIYw = true;}
      if(qEUtEPHqkQ == PSRmWxqrip){sOhtGXPYYg = true;}
      else if(PSRmWxqrip == qEUtEPHqkQ){GyhNjOxRMj = true;}
      if(YtJzRedogS == hDzAcEieQz){JbQyLsndtV = true;}
      if(RPhJduXNdX == ZpQMicsGBl){EOgaFTtBXk = true;}
      if(ATwNgCGAuk == bjTSzMUWLy){nnzPMSbBGe = true;}
      while(hDzAcEieQz == YtJzRedogS){LTwSRDTeCY = true;}
      while(ZpQMicsGBl == ZpQMicsGBl){NgEDIuZDOd = true;}
      while(bjTSzMUWLy == bjTSzMUWLy){QKoOPVrglV = true;}
      if(YnYoWcuiKo == true){YnYoWcuiKo = false;}
      if(jiqzSZCFEs == true){jiqzSZCFEs = false;}
      if(EjpxOyigAP == true){EjpxOyigAP = false;}
      if(iMTRZlQaoF == true){iMTRZlQaoF = false;}
      if(hKwMCssUzZ == true){hKwMCssUzZ = false;}
      if(KPSRtoxbaY == true){KPSRtoxbaY = false;}
      if(sOhtGXPYYg == true){sOhtGXPYYg = false;}
      if(JbQyLsndtV == true){JbQyLsndtV = false;}
      if(EOgaFTtBXk == true){EOgaFTtBXk = false;}
      if(nnzPMSbBGe == true){nnzPMSbBGe = false;}
      if(cUuSQhzTGB == true){cUuSQhzTGB = false;}
      if(ATgFUehGol == true){ATgFUehGol = false;}
      if(cOBmsUbAls == true){cOBmsUbAls = false;}
      if(QlWPrjSOKW == true){QlWPrjSOKW = false;}
      if(UZuVjTHtuh == true){UZuVjTHtuh = false;}
      if(kVMTBOSIYw == true){kVMTBOSIYw = false;}
      if(GyhNjOxRMj == true){GyhNjOxRMj = false;}
      if(LTwSRDTeCY == true){LTwSRDTeCY = false;}
      if(NgEDIuZDOd == true){NgEDIuZDOd = false;}
      if(QKoOPVrglV == true){QKoOPVrglV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DWSZRVKMTK
{ 
  void WVnytZtMhL()
  { 
      bool xdpuCMiLRo = false;
      bool qwDeNQXFrt = false;
      bool iDxmSntkPY = false;
      bool ELiCKfPPTZ = false;
      bool ghLbNElyJq = false;
      bool uuNofsgDbN = false;
      bool SxwskeMBTg = false;
      bool AIkSNBrUYO = false;
      bool BwaXcJxsWR = false;
      bool yLnGHjkRqh = false;
      bool qkdcqmJubd = false;
      bool ALdMLVVYQb = false;
      bool gSdChoTeKd = false;
      bool PZdpWQSygo = false;
      bool zBRrQmgatl = false;
      bool NMBPBXGatB = false;
      bool TekyOagnpu = false;
      bool DWrbbfBklu = false;
      bool HsjYPDYOoz = false;
      bool JqEeVUQSdo = false;
      string NfXamZenRB;
      string IkQiKCADns;
      string YqLIpGnDPa;
      string sRnlWVgXeK;
      string yUbPTMJsOt;
      string lgIxXVTOjf;
      string lbYqIqwdLo;
      string UbXctEOwnd;
      string wtoUoLIpOA;
      string CSnyYWwkHc;
      string PfgYZKIfDS;
      string HWZFjqmEBw;
      string hFPLmCnZDW;
      string IdoLOQMPtd;
      string DcmuserhOg;
      string jriKtJPVlW;
      string VibfKdhOqT;
      string eWJWrFSTRH;
      string JFKWmPtdQE;
      string ApcXHTAGjP;
      if(NfXamZenRB == PfgYZKIfDS){xdpuCMiLRo = true;}
      else if(PfgYZKIfDS == NfXamZenRB){qkdcqmJubd = true;}
      if(IkQiKCADns == HWZFjqmEBw){qwDeNQXFrt = true;}
      else if(HWZFjqmEBw == IkQiKCADns){ALdMLVVYQb = true;}
      if(YqLIpGnDPa == hFPLmCnZDW){iDxmSntkPY = true;}
      else if(hFPLmCnZDW == YqLIpGnDPa){gSdChoTeKd = true;}
      if(sRnlWVgXeK == IdoLOQMPtd){ELiCKfPPTZ = true;}
      else if(IdoLOQMPtd == sRnlWVgXeK){PZdpWQSygo = true;}
      if(yUbPTMJsOt == DcmuserhOg){ghLbNElyJq = true;}
      else if(DcmuserhOg == yUbPTMJsOt){zBRrQmgatl = true;}
      if(lgIxXVTOjf == jriKtJPVlW){uuNofsgDbN = true;}
      else if(jriKtJPVlW == lgIxXVTOjf){NMBPBXGatB = true;}
      if(lbYqIqwdLo == VibfKdhOqT){SxwskeMBTg = true;}
      else if(VibfKdhOqT == lbYqIqwdLo){TekyOagnpu = true;}
      if(UbXctEOwnd == eWJWrFSTRH){AIkSNBrUYO = true;}
      if(wtoUoLIpOA == JFKWmPtdQE){BwaXcJxsWR = true;}
      if(CSnyYWwkHc == ApcXHTAGjP){yLnGHjkRqh = true;}
      while(eWJWrFSTRH == UbXctEOwnd){DWrbbfBklu = true;}
      while(JFKWmPtdQE == JFKWmPtdQE){HsjYPDYOoz = true;}
      while(ApcXHTAGjP == ApcXHTAGjP){JqEeVUQSdo = true;}
      if(xdpuCMiLRo == true){xdpuCMiLRo = false;}
      if(qwDeNQXFrt == true){qwDeNQXFrt = false;}
      if(iDxmSntkPY == true){iDxmSntkPY = false;}
      if(ELiCKfPPTZ == true){ELiCKfPPTZ = false;}
      if(ghLbNElyJq == true){ghLbNElyJq = false;}
      if(uuNofsgDbN == true){uuNofsgDbN = false;}
      if(SxwskeMBTg == true){SxwskeMBTg = false;}
      if(AIkSNBrUYO == true){AIkSNBrUYO = false;}
      if(BwaXcJxsWR == true){BwaXcJxsWR = false;}
      if(yLnGHjkRqh == true){yLnGHjkRqh = false;}
      if(qkdcqmJubd == true){qkdcqmJubd = false;}
      if(ALdMLVVYQb == true){ALdMLVVYQb = false;}
      if(gSdChoTeKd == true){gSdChoTeKd = false;}
      if(PZdpWQSygo == true){PZdpWQSygo = false;}
      if(zBRrQmgatl == true){zBRrQmgatl = false;}
      if(NMBPBXGatB == true){NMBPBXGatB = false;}
      if(TekyOagnpu == true){TekyOagnpu = false;}
      if(DWrbbfBklu == true){DWrbbfBklu = false;}
      if(HsjYPDYOoz == true){HsjYPDYOoz = false;}
      if(JqEeVUQSdo == true){JqEeVUQSdo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JISHGEZJGH
{ 
  void mLaajpzcIi()
  { 
      bool rIuepDmWis = false;
      bool ITkZFpfwui = false;
      bool cZONPcXKkU = false;
      bool AiJOqIkFgq = false;
      bool bTykVgixqg = false;
      bool fCJmoSthPM = false;
      bool fbkOsYJWiw = false;
      bool FaODGIacqh = false;
      bool taTEoyYWZY = false;
      bool NCoULziirw = false;
      bool WMOtbFmGff = false;
      bool qQphSFIfZu = false;
      bool AmxKhCktrH = false;
      bool ZqkuLgLYbj = false;
      bool KSpshxMHBG = false;
      bool qCJxwiPDLZ = false;
      bool TrOYFzeuWk = false;
      bool siEpjhwDbk = false;
      bool pcskPWhnyb = false;
      bool RIMCPRERmh = false;
      string VNHWkKPXiD;
      string kziSbEyTTC;
      string hZiJzVCLnw;
      string SSkJXkQaag;
      string fEULbsXejd;
      string MqSGjudyWO;
      string HDjlkROYup;
      string mXrlVcEXgF;
      string yWaJibAeZb;
      string GSELZbUhZK;
      string eyjspoygjG;
      string pGQRPkcZCJ;
      string RizSjTSgMt;
      string IWyWZAlgSs;
      string cSuTlACmun;
      string ztfPrwzRJW;
      string WRUpxTHsqP;
      string yuHIfynefi;
      string RfkXuOphed;
      string AUXwWLyEVR;
      if(VNHWkKPXiD == eyjspoygjG){rIuepDmWis = true;}
      else if(eyjspoygjG == VNHWkKPXiD){WMOtbFmGff = true;}
      if(kziSbEyTTC == pGQRPkcZCJ){ITkZFpfwui = true;}
      else if(pGQRPkcZCJ == kziSbEyTTC){qQphSFIfZu = true;}
      if(hZiJzVCLnw == RizSjTSgMt){cZONPcXKkU = true;}
      else if(RizSjTSgMt == hZiJzVCLnw){AmxKhCktrH = true;}
      if(SSkJXkQaag == IWyWZAlgSs){AiJOqIkFgq = true;}
      else if(IWyWZAlgSs == SSkJXkQaag){ZqkuLgLYbj = true;}
      if(fEULbsXejd == cSuTlACmun){bTykVgixqg = true;}
      else if(cSuTlACmun == fEULbsXejd){KSpshxMHBG = true;}
      if(MqSGjudyWO == ztfPrwzRJW){fCJmoSthPM = true;}
      else if(ztfPrwzRJW == MqSGjudyWO){qCJxwiPDLZ = true;}
      if(HDjlkROYup == WRUpxTHsqP){fbkOsYJWiw = true;}
      else if(WRUpxTHsqP == HDjlkROYup){TrOYFzeuWk = true;}
      if(mXrlVcEXgF == yuHIfynefi){FaODGIacqh = true;}
      if(yWaJibAeZb == RfkXuOphed){taTEoyYWZY = true;}
      if(GSELZbUhZK == AUXwWLyEVR){NCoULziirw = true;}
      while(yuHIfynefi == mXrlVcEXgF){siEpjhwDbk = true;}
      while(RfkXuOphed == RfkXuOphed){pcskPWhnyb = true;}
      while(AUXwWLyEVR == AUXwWLyEVR){RIMCPRERmh = true;}
      if(rIuepDmWis == true){rIuepDmWis = false;}
      if(ITkZFpfwui == true){ITkZFpfwui = false;}
      if(cZONPcXKkU == true){cZONPcXKkU = false;}
      if(AiJOqIkFgq == true){AiJOqIkFgq = false;}
      if(bTykVgixqg == true){bTykVgixqg = false;}
      if(fCJmoSthPM == true){fCJmoSthPM = false;}
      if(fbkOsYJWiw == true){fbkOsYJWiw = false;}
      if(FaODGIacqh == true){FaODGIacqh = false;}
      if(taTEoyYWZY == true){taTEoyYWZY = false;}
      if(NCoULziirw == true){NCoULziirw = false;}
      if(WMOtbFmGff == true){WMOtbFmGff = false;}
      if(qQphSFIfZu == true){qQphSFIfZu = false;}
      if(AmxKhCktrH == true){AmxKhCktrH = false;}
      if(ZqkuLgLYbj == true){ZqkuLgLYbj = false;}
      if(KSpshxMHBG == true){KSpshxMHBG = false;}
      if(qCJxwiPDLZ == true){qCJxwiPDLZ = false;}
      if(TrOYFzeuWk == true){TrOYFzeuWk = false;}
      if(siEpjhwDbk == true){siEpjhwDbk = false;}
      if(pcskPWhnyb == true){pcskPWhnyb = false;}
      if(RIMCPRERmh == true){RIMCPRERmh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFNIIHJOKS
{ 
  void frdYELdxUN()
  { 
      bool wDxwRoPXcA = false;
      bool hYnxzICHpo = false;
      bool mkbMHspMBa = false;
      bool iMuxFaOEma = false;
      bool YWggBDFfbW = false;
      bool sjBWzLbknY = false;
      bool zDVBQVdprX = false;
      bool sxUOQPEtLE = false;
      bool nJjdhzLXyt = false;
      bool zdPNbVAeQf = false;
      bool ZOnEduOlGi = false;
      bool HgYjkpSqTQ = false;
      bool KFryYOhGmt = false;
      bool OYdfdYUfAl = false;
      bool kYROlRFfck = false;
      bool CJLAVTVpfO = false;
      bool NHzMThDsFL = false;
      bool UmpgekncLG = false;
      bool JBdBqFMdKK = false;
      bool DezlYcZEuD = false;
      string OzSIZbjCiw;
      string geqhbmEccP;
      string SqNjglcLbV;
      string lWwcajOmQI;
      string faBgSWtimw;
      string szsQOXlibm;
      string yXaMJKhNGr;
      string XRMUirogQJ;
      string qtYecmdfNC;
      string xeKcJIzoWI;
      string ngbtXbmXgW;
      string hFRRuEyuiW;
      string gCzEtsGiKa;
      string rAJIVKRdHB;
      string AFyqTrNshF;
      string JDFzalgXAe;
      string VDNGdhuJwk;
      string mTnhWaDIjC;
      string eMBFQntJgi;
      string csdbfwrqMl;
      if(OzSIZbjCiw == ngbtXbmXgW){wDxwRoPXcA = true;}
      else if(ngbtXbmXgW == OzSIZbjCiw){ZOnEduOlGi = true;}
      if(geqhbmEccP == hFRRuEyuiW){hYnxzICHpo = true;}
      else if(hFRRuEyuiW == geqhbmEccP){HgYjkpSqTQ = true;}
      if(SqNjglcLbV == gCzEtsGiKa){mkbMHspMBa = true;}
      else if(gCzEtsGiKa == SqNjglcLbV){KFryYOhGmt = true;}
      if(lWwcajOmQI == rAJIVKRdHB){iMuxFaOEma = true;}
      else if(rAJIVKRdHB == lWwcajOmQI){OYdfdYUfAl = true;}
      if(faBgSWtimw == AFyqTrNshF){YWggBDFfbW = true;}
      else if(AFyqTrNshF == faBgSWtimw){kYROlRFfck = true;}
      if(szsQOXlibm == JDFzalgXAe){sjBWzLbknY = true;}
      else if(JDFzalgXAe == szsQOXlibm){CJLAVTVpfO = true;}
      if(yXaMJKhNGr == VDNGdhuJwk){zDVBQVdprX = true;}
      else if(VDNGdhuJwk == yXaMJKhNGr){NHzMThDsFL = true;}
      if(XRMUirogQJ == mTnhWaDIjC){sxUOQPEtLE = true;}
      if(qtYecmdfNC == eMBFQntJgi){nJjdhzLXyt = true;}
      if(xeKcJIzoWI == csdbfwrqMl){zdPNbVAeQf = true;}
      while(mTnhWaDIjC == XRMUirogQJ){UmpgekncLG = true;}
      while(eMBFQntJgi == eMBFQntJgi){JBdBqFMdKK = true;}
      while(csdbfwrqMl == csdbfwrqMl){DezlYcZEuD = true;}
      if(wDxwRoPXcA == true){wDxwRoPXcA = false;}
      if(hYnxzICHpo == true){hYnxzICHpo = false;}
      if(mkbMHspMBa == true){mkbMHspMBa = false;}
      if(iMuxFaOEma == true){iMuxFaOEma = false;}
      if(YWggBDFfbW == true){YWggBDFfbW = false;}
      if(sjBWzLbknY == true){sjBWzLbknY = false;}
      if(zDVBQVdprX == true){zDVBQVdprX = false;}
      if(sxUOQPEtLE == true){sxUOQPEtLE = false;}
      if(nJjdhzLXyt == true){nJjdhzLXyt = false;}
      if(zdPNbVAeQf == true){zdPNbVAeQf = false;}
      if(ZOnEduOlGi == true){ZOnEduOlGi = false;}
      if(HgYjkpSqTQ == true){HgYjkpSqTQ = false;}
      if(KFryYOhGmt == true){KFryYOhGmt = false;}
      if(OYdfdYUfAl == true){OYdfdYUfAl = false;}
      if(kYROlRFfck == true){kYROlRFfck = false;}
      if(CJLAVTVpfO == true){CJLAVTVpfO = false;}
      if(NHzMThDsFL == true){NHzMThDsFL = false;}
      if(UmpgekncLG == true){UmpgekncLG = false;}
      if(JBdBqFMdKK == true){JBdBqFMdKK = false;}
      if(DezlYcZEuD == true){DezlYcZEuD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DZIPTIHQEA
{ 
  void pWquHlNnAu()
  { 
      bool mQCbQOLEMY = false;
      bool TSmRunXZnL = false;
      bool zUOwmzYrSP = false;
      bool sICykunToD = false;
      bool HziBGdYMDV = false;
      bool orhZuRBFoR = false;
      bool oSkxeLQnfz = false;
      bool zDkjEAkMpJ = false;
      bool aLoxZBZbDS = false;
      bool sieXNnNlVu = false;
      bool MkgDVkHxVu = false;
      bool gnPeqcdmWd = false;
      bool knkNGQYMWP = false;
      bool myquxoekbn = false;
      bool tcGIlESzgj = false;
      bool JZOrJXASxF = false;
      bool LtaFIhxUhB = false;
      bool ysLhjIhcbB = false;
      bool xZflFMjykY = false;
      bool oMmVczBAzD = false;
      string OpwfOuoJVT;
      string aOUtXycSXa;
      string ynEiIHXggR;
      string yzmsOqWrIF;
      string ybCTYfoFwC;
      string gniTYalMXG;
      string WHbDUbaaff;
      string bkKRbWkjJc;
      string SSjekKPTUn;
      string FJTBhpzzzx;
      string ENYQZwcQqC;
      string oBCunEXwRJ;
      string LGGraSQIjk;
      string WkkMXEsTFo;
      string gzbRyDGYMc;
      string SChokyHgoG;
      string eTgGfDQpWj;
      string LDqccMdntX;
      string LqwGRTDwaZ;
      string wLeyJMSVlu;
      if(OpwfOuoJVT == ENYQZwcQqC){mQCbQOLEMY = true;}
      else if(ENYQZwcQqC == OpwfOuoJVT){MkgDVkHxVu = true;}
      if(aOUtXycSXa == oBCunEXwRJ){TSmRunXZnL = true;}
      else if(oBCunEXwRJ == aOUtXycSXa){gnPeqcdmWd = true;}
      if(ynEiIHXggR == LGGraSQIjk){zUOwmzYrSP = true;}
      else if(LGGraSQIjk == ynEiIHXggR){knkNGQYMWP = true;}
      if(yzmsOqWrIF == WkkMXEsTFo){sICykunToD = true;}
      else if(WkkMXEsTFo == yzmsOqWrIF){myquxoekbn = true;}
      if(ybCTYfoFwC == gzbRyDGYMc){HziBGdYMDV = true;}
      else if(gzbRyDGYMc == ybCTYfoFwC){tcGIlESzgj = true;}
      if(gniTYalMXG == SChokyHgoG){orhZuRBFoR = true;}
      else if(SChokyHgoG == gniTYalMXG){JZOrJXASxF = true;}
      if(WHbDUbaaff == eTgGfDQpWj){oSkxeLQnfz = true;}
      else if(eTgGfDQpWj == WHbDUbaaff){LtaFIhxUhB = true;}
      if(bkKRbWkjJc == LDqccMdntX){zDkjEAkMpJ = true;}
      if(SSjekKPTUn == LqwGRTDwaZ){aLoxZBZbDS = true;}
      if(FJTBhpzzzx == wLeyJMSVlu){sieXNnNlVu = true;}
      while(LDqccMdntX == bkKRbWkjJc){ysLhjIhcbB = true;}
      while(LqwGRTDwaZ == LqwGRTDwaZ){xZflFMjykY = true;}
      while(wLeyJMSVlu == wLeyJMSVlu){oMmVczBAzD = true;}
      if(mQCbQOLEMY == true){mQCbQOLEMY = false;}
      if(TSmRunXZnL == true){TSmRunXZnL = false;}
      if(zUOwmzYrSP == true){zUOwmzYrSP = false;}
      if(sICykunToD == true){sICykunToD = false;}
      if(HziBGdYMDV == true){HziBGdYMDV = false;}
      if(orhZuRBFoR == true){orhZuRBFoR = false;}
      if(oSkxeLQnfz == true){oSkxeLQnfz = false;}
      if(zDkjEAkMpJ == true){zDkjEAkMpJ = false;}
      if(aLoxZBZbDS == true){aLoxZBZbDS = false;}
      if(sieXNnNlVu == true){sieXNnNlVu = false;}
      if(MkgDVkHxVu == true){MkgDVkHxVu = false;}
      if(gnPeqcdmWd == true){gnPeqcdmWd = false;}
      if(knkNGQYMWP == true){knkNGQYMWP = false;}
      if(myquxoekbn == true){myquxoekbn = false;}
      if(tcGIlESzgj == true){tcGIlESzgj = false;}
      if(JZOrJXASxF == true){JZOrJXASxF = false;}
      if(LtaFIhxUhB == true){LtaFIhxUhB = false;}
      if(ysLhjIhcbB == true){ysLhjIhcbB = false;}
      if(xZflFMjykY == true){xZflFMjykY = false;}
      if(oMmVczBAzD == true){oMmVczBAzD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OGLYQNXIWF
{ 
  void rMJnjPFKNn()
  { 
      bool PtwlrUqeiE = false;
      bool ggxmYITHsk = false;
      bool ZDhjxANAgU = false;
      bool zOfXJkmkGG = false;
      bool ZNjGQwbsQK = false;
      bool SlIBGLMLor = false;
      bool GpyNERAYdm = false;
      bool ViBlKMTaTA = false;
      bool XUiWCMGeRy = false;
      bool YbuOziPWBy = false;
      bool uDPcojkVps = false;
      bool rkroTlHaLq = false;
      bool LVGfOtmmmb = false;
      bool wwZUEUFFgR = false;
      bool bjoXFniGtN = false;
      bool bnKJmZwjOu = false;
      bool wyiNwuLWjy = false;
      bool gBssPagiZa = false;
      bool KgrYAIlPhe = false;
      bool YVqlVdBaaK = false;
      string KhVBZTZzgg;
      string BLzEVwpKhC;
      string oxLRoklUuy;
      string mfoFGoqTHz;
      string IXcXPIAEDc;
      string dfGGRNVDLo;
      string gEEhtUVtyf;
      string FWDitRTnCg;
      string jgQSUHZhms;
      string TmHSRDTtdt;
      string lGGXWHbXLA;
      string sgAdEAnlNm;
      string unGELROkQq;
      string yZKIudasuM;
      string eBWmAlldNR;
      string PhfqyyABME;
      string sqGUBTWrha;
      string YtpBItQSEY;
      string fjXzaQsSKx;
      string dYgpTmtBlg;
      if(KhVBZTZzgg == lGGXWHbXLA){PtwlrUqeiE = true;}
      else if(lGGXWHbXLA == KhVBZTZzgg){uDPcojkVps = true;}
      if(BLzEVwpKhC == sgAdEAnlNm){ggxmYITHsk = true;}
      else if(sgAdEAnlNm == BLzEVwpKhC){rkroTlHaLq = true;}
      if(oxLRoklUuy == unGELROkQq){ZDhjxANAgU = true;}
      else if(unGELROkQq == oxLRoklUuy){LVGfOtmmmb = true;}
      if(mfoFGoqTHz == yZKIudasuM){zOfXJkmkGG = true;}
      else if(yZKIudasuM == mfoFGoqTHz){wwZUEUFFgR = true;}
      if(IXcXPIAEDc == eBWmAlldNR){ZNjGQwbsQK = true;}
      else if(eBWmAlldNR == IXcXPIAEDc){bjoXFniGtN = true;}
      if(dfGGRNVDLo == PhfqyyABME){SlIBGLMLor = true;}
      else if(PhfqyyABME == dfGGRNVDLo){bnKJmZwjOu = true;}
      if(gEEhtUVtyf == sqGUBTWrha){GpyNERAYdm = true;}
      else if(sqGUBTWrha == gEEhtUVtyf){wyiNwuLWjy = true;}
      if(FWDitRTnCg == YtpBItQSEY){ViBlKMTaTA = true;}
      if(jgQSUHZhms == fjXzaQsSKx){XUiWCMGeRy = true;}
      if(TmHSRDTtdt == dYgpTmtBlg){YbuOziPWBy = true;}
      while(YtpBItQSEY == FWDitRTnCg){gBssPagiZa = true;}
      while(fjXzaQsSKx == fjXzaQsSKx){KgrYAIlPhe = true;}
      while(dYgpTmtBlg == dYgpTmtBlg){YVqlVdBaaK = true;}
      if(PtwlrUqeiE == true){PtwlrUqeiE = false;}
      if(ggxmYITHsk == true){ggxmYITHsk = false;}
      if(ZDhjxANAgU == true){ZDhjxANAgU = false;}
      if(zOfXJkmkGG == true){zOfXJkmkGG = false;}
      if(ZNjGQwbsQK == true){ZNjGQwbsQK = false;}
      if(SlIBGLMLor == true){SlIBGLMLor = false;}
      if(GpyNERAYdm == true){GpyNERAYdm = false;}
      if(ViBlKMTaTA == true){ViBlKMTaTA = false;}
      if(XUiWCMGeRy == true){XUiWCMGeRy = false;}
      if(YbuOziPWBy == true){YbuOziPWBy = false;}
      if(uDPcojkVps == true){uDPcojkVps = false;}
      if(rkroTlHaLq == true){rkroTlHaLq = false;}
      if(LVGfOtmmmb == true){LVGfOtmmmb = false;}
      if(wwZUEUFFgR == true){wwZUEUFFgR = false;}
      if(bjoXFniGtN == true){bjoXFniGtN = false;}
      if(bnKJmZwjOu == true){bnKJmZwjOu = false;}
      if(wyiNwuLWjy == true){wyiNwuLWjy = false;}
      if(gBssPagiZa == true){gBssPagiZa = false;}
      if(KgrYAIlPhe == true){KgrYAIlPhe = false;}
      if(YVqlVdBaaK == true){YVqlVdBaaK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HJJHNSQPJH
{ 
  void tWGEtLcMGb()
  { 
      bool NQeBmkieei = false;
      bool einLXDMTUQ = false;
      bool cxfZGxRzTE = false;
      bool AiCnPjkFjb = false;
      bool AURjrlyjMh = false;
      bool hmIFAQkFuo = false;
      bool TjLZhugzwn = false;
      bool SHjsQIewgT = false;
      bool zgllVMZwnz = false;
      bool zeJtHQIrBw = false;
      bool FznYOaDPnr = false;
      bool koXbpmxZDV = false;
      bool VjLxomyokA = false;
      bool zmtjNAsNWu = false;
      bool JJIuNJHgEU = false;
      bool TinfaVmpia = false;
      bool bNdnrxtmNp = false;
      bool siCIMLbPie = false;
      bool fQkQgPzOJr = false;
      bool MCdwSufTDP = false;
      string zruYyMThpa;
      string HBULmUPnHd;
      string gFAkfKGFiM;
      string qTSxPWfhVJ;
      string OOYdizcdqf;
      string tXjKVtrJrm;
      string GOycinhXwQ;
      string nhSxOSfVCf;
      string hbNDRTiIaV;
      string dWohCAPutt;
      string QEhaqMElwD;
      string NVGMEeAuKP;
      string EZwalRrjuN;
      string CjbIOctlLF;
      string PxMXHIPccX;
      string ATjeoqHHoZ;
      string TTphActyxa;
      string jOjFAGMYSc;
      string BPGWNizxSW;
      string UmwkkuGdWd;
      if(zruYyMThpa == QEhaqMElwD){NQeBmkieei = true;}
      else if(QEhaqMElwD == zruYyMThpa){FznYOaDPnr = true;}
      if(HBULmUPnHd == NVGMEeAuKP){einLXDMTUQ = true;}
      else if(NVGMEeAuKP == HBULmUPnHd){koXbpmxZDV = true;}
      if(gFAkfKGFiM == EZwalRrjuN){cxfZGxRzTE = true;}
      else if(EZwalRrjuN == gFAkfKGFiM){VjLxomyokA = true;}
      if(qTSxPWfhVJ == CjbIOctlLF){AiCnPjkFjb = true;}
      else if(CjbIOctlLF == qTSxPWfhVJ){zmtjNAsNWu = true;}
      if(OOYdizcdqf == PxMXHIPccX){AURjrlyjMh = true;}
      else if(PxMXHIPccX == OOYdizcdqf){JJIuNJHgEU = true;}
      if(tXjKVtrJrm == ATjeoqHHoZ){hmIFAQkFuo = true;}
      else if(ATjeoqHHoZ == tXjKVtrJrm){TinfaVmpia = true;}
      if(GOycinhXwQ == TTphActyxa){TjLZhugzwn = true;}
      else if(TTphActyxa == GOycinhXwQ){bNdnrxtmNp = true;}
      if(nhSxOSfVCf == jOjFAGMYSc){SHjsQIewgT = true;}
      if(hbNDRTiIaV == BPGWNizxSW){zgllVMZwnz = true;}
      if(dWohCAPutt == UmwkkuGdWd){zeJtHQIrBw = true;}
      while(jOjFAGMYSc == nhSxOSfVCf){siCIMLbPie = true;}
      while(BPGWNizxSW == BPGWNizxSW){fQkQgPzOJr = true;}
      while(UmwkkuGdWd == UmwkkuGdWd){MCdwSufTDP = true;}
      if(NQeBmkieei == true){NQeBmkieei = false;}
      if(einLXDMTUQ == true){einLXDMTUQ = false;}
      if(cxfZGxRzTE == true){cxfZGxRzTE = false;}
      if(AiCnPjkFjb == true){AiCnPjkFjb = false;}
      if(AURjrlyjMh == true){AURjrlyjMh = false;}
      if(hmIFAQkFuo == true){hmIFAQkFuo = false;}
      if(TjLZhugzwn == true){TjLZhugzwn = false;}
      if(SHjsQIewgT == true){SHjsQIewgT = false;}
      if(zgllVMZwnz == true){zgllVMZwnz = false;}
      if(zeJtHQIrBw == true){zeJtHQIrBw = false;}
      if(FznYOaDPnr == true){FznYOaDPnr = false;}
      if(koXbpmxZDV == true){koXbpmxZDV = false;}
      if(VjLxomyokA == true){VjLxomyokA = false;}
      if(zmtjNAsNWu == true){zmtjNAsNWu = false;}
      if(JJIuNJHgEU == true){JJIuNJHgEU = false;}
      if(TinfaVmpia == true){TinfaVmpia = false;}
      if(bNdnrxtmNp == true){bNdnrxtmNp = false;}
      if(siCIMLbPie == true){siCIMLbPie = false;}
      if(fQkQgPzOJr == true){fQkQgPzOJr = false;}
      if(MCdwSufTDP == true){MCdwSufTDP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HIEUROQABV
{ 
  void smQRYOfJzK()
  { 
      bool CZzJcJTimi = false;
      bool dTbJYXQxRt = false;
      bool BuCwROoEOh = false;
      bool nTDHaMULwV = false;
      bool nXChyXgUkh = false;
      bool WPtmWGXCrO = false;
      bool TOTFuKPThM = false;
      bool CFAwFdsTxt = false;
      bool hTTgKYYQkT = false;
      bool oSThBYDwmn = false;
      bool HMlYeQOyhs = false;
      bool NDEygAumtW = false;
      bool lyiNWjlRuf = false;
      bool ZwgJlUgtBt = false;
      bool JZirGlNVBB = false;
      bool dQCPCIdYCu = false;
      bool ewDBSRVuLM = false;
      bool SAkAMLPqHj = false;
      bool WPQsCIsQHc = false;
      bool pIrGOMVgYn = false;
      string IuMzRsNSAm;
      string XAiPyPQIkm;
      string oGHQxrSJNy;
      string nCrkCKOmxR;
      string QaYDqIWgpu;
      string PmSbHBnwBZ;
      string aDEByUHxNm;
      string AdLTVNhDYo;
      string UkTRiBjQcA;
      string WSkWqNVWFV;
      string BYTCtkazFt;
      string TjXMEojmSw;
      string kqUMQhsnbI;
      string qKyCmuQQWy;
      string ajKigmtYSB;
      string ciDIkKEHlM;
      string rmWxCIkUYI;
      string XTPUVBfkfc;
      string mUVZeIHoRc;
      string qJdKFnMMgX;
      if(IuMzRsNSAm == BYTCtkazFt){CZzJcJTimi = true;}
      else if(BYTCtkazFt == IuMzRsNSAm){HMlYeQOyhs = true;}
      if(XAiPyPQIkm == TjXMEojmSw){dTbJYXQxRt = true;}
      else if(TjXMEojmSw == XAiPyPQIkm){NDEygAumtW = true;}
      if(oGHQxrSJNy == kqUMQhsnbI){BuCwROoEOh = true;}
      else if(kqUMQhsnbI == oGHQxrSJNy){lyiNWjlRuf = true;}
      if(nCrkCKOmxR == qKyCmuQQWy){nTDHaMULwV = true;}
      else if(qKyCmuQQWy == nCrkCKOmxR){ZwgJlUgtBt = true;}
      if(QaYDqIWgpu == ajKigmtYSB){nXChyXgUkh = true;}
      else if(ajKigmtYSB == QaYDqIWgpu){JZirGlNVBB = true;}
      if(PmSbHBnwBZ == ciDIkKEHlM){WPtmWGXCrO = true;}
      else if(ciDIkKEHlM == PmSbHBnwBZ){dQCPCIdYCu = true;}
      if(aDEByUHxNm == rmWxCIkUYI){TOTFuKPThM = true;}
      else if(rmWxCIkUYI == aDEByUHxNm){ewDBSRVuLM = true;}
      if(AdLTVNhDYo == XTPUVBfkfc){CFAwFdsTxt = true;}
      if(UkTRiBjQcA == mUVZeIHoRc){hTTgKYYQkT = true;}
      if(WSkWqNVWFV == qJdKFnMMgX){oSThBYDwmn = true;}
      while(XTPUVBfkfc == AdLTVNhDYo){SAkAMLPqHj = true;}
      while(mUVZeIHoRc == mUVZeIHoRc){WPQsCIsQHc = true;}
      while(qJdKFnMMgX == qJdKFnMMgX){pIrGOMVgYn = true;}
      if(CZzJcJTimi == true){CZzJcJTimi = false;}
      if(dTbJYXQxRt == true){dTbJYXQxRt = false;}
      if(BuCwROoEOh == true){BuCwROoEOh = false;}
      if(nTDHaMULwV == true){nTDHaMULwV = false;}
      if(nXChyXgUkh == true){nXChyXgUkh = false;}
      if(WPtmWGXCrO == true){WPtmWGXCrO = false;}
      if(TOTFuKPThM == true){TOTFuKPThM = false;}
      if(CFAwFdsTxt == true){CFAwFdsTxt = false;}
      if(hTTgKYYQkT == true){hTTgKYYQkT = false;}
      if(oSThBYDwmn == true){oSThBYDwmn = false;}
      if(HMlYeQOyhs == true){HMlYeQOyhs = false;}
      if(NDEygAumtW == true){NDEygAumtW = false;}
      if(lyiNWjlRuf == true){lyiNWjlRuf = false;}
      if(ZwgJlUgtBt == true){ZwgJlUgtBt = false;}
      if(JZirGlNVBB == true){JZirGlNVBB = false;}
      if(dQCPCIdYCu == true){dQCPCIdYCu = false;}
      if(ewDBSRVuLM == true){ewDBSRVuLM = false;}
      if(SAkAMLPqHj == true){SAkAMLPqHj = false;}
      if(WPQsCIsQHc == true){WPQsCIsQHc = false;}
      if(pIrGOMVgYn == true){pIrGOMVgYn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PDZKZKYCKS
{ 
  void OEbarHwtNF()
  { 
      bool TbAInYVzfj = false;
      bool sSYmELFKzE = false;
      bool mbSaRMDJOs = false;
      bool rPuWVlqUrI = false;
      bool yoZsqrUfim = false;
      bool sjCOsqJZpb = false;
      bool VMjlrcWBRS = false;
      bool TkRpGyBYjY = false;
      bool qWZbzHNgcd = false;
      bool bRdQmkEmAN = false;
      bool UTOQTIRLHu = false;
      bool okpRjymHlj = false;
      bool PpXmpBGBDV = false;
      bool sOXVEXIJIq = false;
      bool oBZgnqbMfo = false;
      bool ywAPyeuaZR = false;
      bool BQIkCaMTNM = false;
      bool pdzuuNPpzz = false;
      bool ZtUOXwNHWY = false;
      bool bhiqpYsneN = false;
      string hUVlBjUyQK;
      string FEwhGdEpQr;
      string DdgYWrtlfp;
      string DaEgmBTgRO;
      string xqBEaNGiXR;
      string fWVHZDnwOI;
      string ohSZGdAPuE;
      string KWXBtMbbyI;
      string kLONKgFxGi;
      string NWRJZPXbyw;
      string NqnSGIyTMN;
      string bLyGXdSEOZ;
      string YCILpmEObe;
      string nAdButWwHC;
      string hljsHBYLku;
      string wTMXXKhcbS;
      string DiqhZahwKc;
      string GWxMrmRPDo;
      string OrcghUnFdj;
      string LtTnyytCTg;
      if(hUVlBjUyQK == NqnSGIyTMN){TbAInYVzfj = true;}
      else if(NqnSGIyTMN == hUVlBjUyQK){UTOQTIRLHu = true;}
      if(FEwhGdEpQr == bLyGXdSEOZ){sSYmELFKzE = true;}
      else if(bLyGXdSEOZ == FEwhGdEpQr){okpRjymHlj = true;}
      if(DdgYWrtlfp == YCILpmEObe){mbSaRMDJOs = true;}
      else if(YCILpmEObe == DdgYWrtlfp){PpXmpBGBDV = true;}
      if(DaEgmBTgRO == nAdButWwHC){rPuWVlqUrI = true;}
      else if(nAdButWwHC == DaEgmBTgRO){sOXVEXIJIq = true;}
      if(xqBEaNGiXR == hljsHBYLku){yoZsqrUfim = true;}
      else if(hljsHBYLku == xqBEaNGiXR){oBZgnqbMfo = true;}
      if(fWVHZDnwOI == wTMXXKhcbS){sjCOsqJZpb = true;}
      else if(wTMXXKhcbS == fWVHZDnwOI){ywAPyeuaZR = true;}
      if(ohSZGdAPuE == DiqhZahwKc){VMjlrcWBRS = true;}
      else if(DiqhZahwKc == ohSZGdAPuE){BQIkCaMTNM = true;}
      if(KWXBtMbbyI == GWxMrmRPDo){TkRpGyBYjY = true;}
      if(kLONKgFxGi == OrcghUnFdj){qWZbzHNgcd = true;}
      if(NWRJZPXbyw == LtTnyytCTg){bRdQmkEmAN = true;}
      while(GWxMrmRPDo == KWXBtMbbyI){pdzuuNPpzz = true;}
      while(OrcghUnFdj == OrcghUnFdj){ZtUOXwNHWY = true;}
      while(LtTnyytCTg == LtTnyytCTg){bhiqpYsneN = true;}
      if(TbAInYVzfj == true){TbAInYVzfj = false;}
      if(sSYmELFKzE == true){sSYmELFKzE = false;}
      if(mbSaRMDJOs == true){mbSaRMDJOs = false;}
      if(rPuWVlqUrI == true){rPuWVlqUrI = false;}
      if(yoZsqrUfim == true){yoZsqrUfim = false;}
      if(sjCOsqJZpb == true){sjCOsqJZpb = false;}
      if(VMjlrcWBRS == true){VMjlrcWBRS = false;}
      if(TkRpGyBYjY == true){TkRpGyBYjY = false;}
      if(qWZbzHNgcd == true){qWZbzHNgcd = false;}
      if(bRdQmkEmAN == true){bRdQmkEmAN = false;}
      if(UTOQTIRLHu == true){UTOQTIRLHu = false;}
      if(okpRjymHlj == true){okpRjymHlj = false;}
      if(PpXmpBGBDV == true){PpXmpBGBDV = false;}
      if(sOXVEXIJIq == true){sOXVEXIJIq = false;}
      if(oBZgnqbMfo == true){oBZgnqbMfo = false;}
      if(ywAPyeuaZR == true){ywAPyeuaZR = false;}
      if(BQIkCaMTNM == true){BQIkCaMTNM = false;}
      if(pdzuuNPpzz == true){pdzuuNPpzz = false;}
      if(ZtUOXwNHWY == true){ZtUOXwNHWY = false;}
      if(bhiqpYsneN == true){bhiqpYsneN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FEYCRKSNBK
{ 
  void GTNmJeXwjZ()
  { 
      bool qCzRfdAaez = false;
      bool PPYhlEZEpQ = false;
      bool tiauddegHu = false;
      bool FEaoAjQyiG = false;
      bool UEcqyDklKs = false;
      bool pxlNsIbDnC = false;
      bool zSSitKoihB = false;
      bool naUjupFixa = false;
      bool srVOFHSNur = false;
      bool IMKgHCktxn = false;
      bool NBEIFOcBRD = false;
      bool DrGMJGxEdl = false;
      bool rbmosaQncs = false;
      bool ELlIMqnMIp = false;
      bool eQuroQGxXA = false;
      bool FgPKulOOPd = false;
      bool ynYYyqGxAS = false;
      bool RjunHafuAb = false;
      bool UTQbnXwaMZ = false;
      bool bYxeqqrWtx = false;
      string HXicBGzfuc;
      string qArwjgEqhF;
      string QETfKnyFbL;
      string fjVUDfoyLc;
      string SjnIsOMoHY;
      string zBIbSCDDRM;
      string IsEjxGeWsE;
      string rFeEmfQLlu;
      string bIyDLdbsCA;
      string bkfzUYfEKm;
      string iouCfsWEol;
      string lrQWjAuBXT;
      string elUsbGYfjN;
      string ALAzLmMuWR;
      string HWDPOjTJOT;
      string degqHxTCaY;
      string TpUalZrRKx;
      string mzdFMHhEdr;
      string mPQPjVeIqO;
      string SJUxxQCcdn;
      if(HXicBGzfuc == iouCfsWEol){qCzRfdAaez = true;}
      else if(iouCfsWEol == HXicBGzfuc){NBEIFOcBRD = true;}
      if(qArwjgEqhF == lrQWjAuBXT){PPYhlEZEpQ = true;}
      else if(lrQWjAuBXT == qArwjgEqhF){DrGMJGxEdl = true;}
      if(QETfKnyFbL == elUsbGYfjN){tiauddegHu = true;}
      else if(elUsbGYfjN == QETfKnyFbL){rbmosaQncs = true;}
      if(fjVUDfoyLc == ALAzLmMuWR){FEaoAjQyiG = true;}
      else if(ALAzLmMuWR == fjVUDfoyLc){ELlIMqnMIp = true;}
      if(SjnIsOMoHY == HWDPOjTJOT){UEcqyDklKs = true;}
      else if(HWDPOjTJOT == SjnIsOMoHY){eQuroQGxXA = true;}
      if(zBIbSCDDRM == degqHxTCaY){pxlNsIbDnC = true;}
      else if(degqHxTCaY == zBIbSCDDRM){FgPKulOOPd = true;}
      if(IsEjxGeWsE == TpUalZrRKx){zSSitKoihB = true;}
      else if(TpUalZrRKx == IsEjxGeWsE){ynYYyqGxAS = true;}
      if(rFeEmfQLlu == mzdFMHhEdr){naUjupFixa = true;}
      if(bIyDLdbsCA == mPQPjVeIqO){srVOFHSNur = true;}
      if(bkfzUYfEKm == SJUxxQCcdn){IMKgHCktxn = true;}
      while(mzdFMHhEdr == rFeEmfQLlu){RjunHafuAb = true;}
      while(mPQPjVeIqO == mPQPjVeIqO){UTQbnXwaMZ = true;}
      while(SJUxxQCcdn == SJUxxQCcdn){bYxeqqrWtx = true;}
      if(qCzRfdAaez == true){qCzRfdAaez = false;}
      if(PPYhlEZEpQ == true){PPYhlEZEpQ = false;}
      if(tiauddegHu == true){tiauddegHu = false;}
      if(FEaoAjQyiG == true){FEaoAjQyiG = false;}
      if(UEcqyDklKs == true){UEcqyDklKs = false;}
      if(pxlNsIbDnC == true){pxlNsIbDnC = false;}
      if(zSSitKoihB == true){zSSitKoihB = false;}
      if(naUjupFixa == true){naUjupFixa = false;}
      if(srVOFHSNur == true){srVOFHSNur = false;}
      if(IMKgHCktxn == true){IMKgHCktxn = false;}
      if(NBEIFOcBRD == true){NBEIFOcBRD = false;}
      if(DrGMJGxEdl == true){DrGMJGxEdl = false;}
      if(rbmosaQncs == true){rbmosaQncs = false;}
      if(ELlIMqnMIp == true){ELlIMqnMIp = false;}
      if(eQuroQGxXA == true){eQuroQGxXA = false;}
      if(FgPKulOOPd == true){FgPKulOOPd = false;}
      if(ynYYyqGxAS == true){ynYYyqGxAS = false;}
      if(RjunHafuAb == true){RjunHafuAb = false;}
      if(UTQbnXwaMZ == true){UTQbnXwaMZ = false;}
      if(bYxeqqrWtx == true){bYxeqqrWtx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QEIRBDCHHD
{ 
  void WAbSUfZbNE()
  { 
      bool fIBnkZFENy = false;
      bool jeUcdNNDAw = false;
      bool qSBbDSbKot = false;
      bool JrwQzpJBpq = false;
      bool RacUZgPZKz = false;
      bool aHTgrNHYjR = false;
      bool yuPTnriDdn = false;
      bool DLMIdPofCW = false;
      bool CBzoTCXPYl = false;
      bool hjRXsWLJfh = false;
      bool xMwWuOtLCb = false;
      bool XaWMPxwZzl = false;
      bool TTdqFTtnPH = false;
      bool EezTYoEbsE = false;
      bool HMMxNHMEIw = false;
      bool ZkJtNdhFRb = false;
      bool UFuuXraDnZ = false;
      bool rTgudHGgcy = false;
      bool GofTgSUFFu = false;
      bool HzKRiBQRYU = false;
      string XOcOJYOmMn;
      string tIPiGeGpCA;
      string SdDAUkheuN;
      string UuixLxPaKo;
      string gPtqfTsAnV;
      string DdIIBtKctY;
      string qiqySzYSXI;
      string PffNTCiMUB;
      string qhqYJqlawQ;
      string mlgkxxXwYg;
      string tabeGXyuny;
      string KxIsgJrSnb;
      string MyVGVcztPW;
      string dmnmGQFMSl;
      string rqlxGodnEn;
      string FFHwTwEUJc;
      string YDeRUWJUlQ;
      string DezCiVMYAf;
      string zKpbRXfqTJ;
      string MkDoNnLTci;
      if(XOcOJYOmMn == tabeGXyuny){fIBnkZFENy = true;}
      else if(tabeGXyuny == XOcOJYOmMn){xMwWuOtLCb = true;}
      if(tIPiGeGpCA == KxIsgJrSnb){jeUcdNNDAw = true;}
      else if(KxIsgJrSnb == tIPiGeGpCA){XaWMPxwZzl = true;}
      if(SdDAUkheuN == MyVGVcztPW){qSBbDSbKot = true;}
      else if(MyVGVcztPW == SdDAUkheuN){TTdqFTtnPH = true;}
      if(UuixLxPaKo == dmnmGQFMSl){JrwQzpJBpq = true;}
      else if(dmnmGQFMSl == UuixLxPaKo){EezTYoEbsE = true;}
      if(gPtqfTsAnV == rqlxGodnEn){RacUZgPZKz = true;}
      else if(rqlxGodnEn == gPtqfTsAnV){HMMxNHMEIw = true;}
      if(DdIIBtKctY == FFHwTwEUJc){aHTgrNHYjR = true;}
      else if(FFHwTwEUJc == DdIIBtKctY){ZkJtNdhFRb = true;}
      if(qiqySzYSXI == YDeRUWJUlQ){yuPTnriDdn = true;}
      else if(YDeRUWJUlQ == qiqySzYSXI){UFuuXraDnZ = true;}
      if(PffNTCiMUB == DezCiVMYAf){DLMIdPofCW = true;}
      if(qhqYJqlawQ == zKpbRXfqTJ){CBzoTCXPYl = true;}
      if(mlgkxxXwYg == MkDoNnLTci){hjRXsWLJfh = true;}
      while(DezCiVMYAf == PffNTCiMUB){rTgudHGgcy = true;}
      while(zKpbRXfqTJ == zKpbRXfqTJ){GofTgSUFFu = true;}
      while(MkDoNnLTci == MkDoNnLTci){HzKRiBQRYU = true;}
      if(fIBnkZFENy == true){fIBnkZFENy = false;}
      if(jeUcdNNDAw == true){jeUcdNNDAw = false;}
      if(qSBbDSbKot == true){qSBbDSbKot = false;}
      if(JrwQzpJBpq == true){JrwQzpJBpq = false;}
      if(RacUZgPZKz == true){RacUZgPZKz = false;}
      if(aHTgrNHYjR == true){aHTgrNHYjR = false;}
      if(yuPTnriDdn == true){yuPTnriDdn = false;}
      if(DLMIdPofCW == true){DLMIdPofCW = false;}
      if(CBzoTCXPYl == true){CBzoTCXPYl = false;}
      if(hjRXsWLJfh == true){hjRXsWLJfh = false;}
      if(xMwWuOtLCb == true){xMwWuOtLCb = false;}
      if(XaWMPxwZzl == true){XaWMPxwZzl = false;}
      if(TTdqFTtnPH == true){TTdqFTtnPH = false;}
      if(EezTYoEbsE == true){EezTYoEbsE = false;}
      if(HMMxNHMEIw == true){HMMxNHMEIw = false;}
      if(ZkJtNdhFRb == true){ZkJtNdhFRb = false;}
      if(UFuuXraDnZ == true){UFuuXraDnZ = false;}
      if(rTgudHGgcy == true){rTgudHGgcy = false;}
      if(GofTgSUFFu == true){GofTgSUFFu = false;}
      if(HzKRiBQRYU == true){HzKRiBQRYU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MCPCVLCGXF
{ 
  void ZxeLKpZWDi()
  { 
      bool UKiVKAgWad = false;
      bool dscFMVzbqd = false;
      bool UsXnVzQqGm = false;
      bool ECeSsocuWV = false;
      bool DJiYIkLjOF = false;
      bool feYJzbmuzK = false;
      bool ipPmZbNJMX = false;
      bool sEFUaLKyfk = false;
      bool ngcBGYdVSQ = false;
      bool BhuLmMsuzf = false;
      bool WBXpLbZDhn = false;
      bool RnOOWCNOgB = false;
      bool xrquVKIthO = false;
      bool ROzzNlJloe = false;
      bool zandzNTfoj = false;
      bool zeOxhdJbTB = false;
      bool SfUSWCnOAj = false;
      bool saZBCWEMwI = false;
      bool qbFyPmACQi = false;
      bool bgRmLTFUHw = false;
      string GTGfnFUeah;
      string FrTzQrFbqP;
      string ulxUqadljR;
      string MUXwdAuLZT;
      string JCFhFNExVw;
      string AINArTWloM;
      string aiuIVkTXUP;
      string wtBXGrgPPc;
      string VgQnQEGXDJ;
      string dJWNraHwLU;
      string sgbFzGGosA;
      string mGWLpsSGrR;
      string dwUKlmXnfe;
      string kkDtjoFKnK;
      string xRdCWXmKWy;
      string IAEtqxLQTM;
      string iRJOOBCbaA;
      string nHShTMSSnN;
      string zMRgWjfJDm;
      string dnpaafHPmU;
      if(GTGfnFUeah == sgbFzGGosA){UKiVKAgWad = true;}
      else if(sgbFzGGosA == GTGfnFUeah){WBXpLbZDhn = true;}
      if(FrTzQrFbqP == mGWLpsSGrR){dscFMVzbqd = true;}
      else if(mGWLpsSGrR == FrTzQrFbqP){RnOOWCNOgB = true;}
      if(ulxUqadljR == dwUKlmXnfe){UsXnVzQqGm = true;}
      else if(dwUKlmXnfe == ulxUqadljR){xrquVKIthO = true;}
      if(MUXwdAuLZT == kkDtjoFKnK){ECeSsocuWV = true;}
      else if(kkDtjoFKnK == MUXwdAuLZT){ROzzNlJloe = true;}
      if(JCFhFNExVw == xRdCWXmKWy){DJiYIkLjOF = true;}
      else if(xRdCWXmKWy == JCFhFNExVw){zandzNTfoj = true;}
      if(AINArTWloM == IAEtqxLQTM){feYJzbmuzK = true;}
      else if(IAEtqxLQTM == AINArTWloM){zeOxhdJbTB = true;}
      if(aiuIVkTXUP == iRJOOBCbaA){ipPmZbNJMX = true;}
      else if(iRJOOBCbaA == aiuIVkTXUP){SfUSWCnOAj = true;}
      if(wtBXGrgPPc == nHShTMSSnN){sEFUaLKyfk = true;}
      if(VgQnQEGXDJ == zMRgWjfJDm){ngcBGYdVSQ = true;}
      if(dJWNraHwLU == dnpaafHPmU){BhuLmMsuzf = true;}
      while(nHShTMSSnN == wtBXGrgPPc){saZBCWEMwI = true;}
      while(zMRgWjfJDm == zMRgWjfJDm){qbFyPmACQi = true;}
      while(dnpaafHPmU == dnpaafHPmU){bgRmLTFUHw = true;}
      if(UKiVKAgWad == true){UKiVKAgWad = false;}
      if(dscFMVzbqd == true){dscFMVzbqd = false;}
      if(UsXnVzQqGm == true){UsXnVzQqGm = false;}
      if(ECeSsocuWV == true){ECeSsocuWV = false;}
      if(DJiYIkLjOF == true){DJiYIkLjOF = false;}
      if(feYJzbmuzK == true){feYJzbmuzK = false;}
      if(ipPmZbNJMX == true){ipPmZbNJMX = false;}
      if(sEFUaLKyfk == true){sEFUaLKyfk = false;}
      if(ngcBGYdVSQ == true){ngcBGYdVSQ = false;}
      if(BhuLmMsuzf == true){BhuLmMsuzf = false;}
      if(WBXpLbZDhn == true){WBXpLbZDhn = false;}
      if(RnOOWCNOgB == true){RnOOWCNOgB = false;}
      if(xrquVKIthO == true){xrquVKIthO = false;}
      if(ROzzNlJloe == true){ROzzNlJloe = false;}
      if(zandzNTfoj == true){zandzNTfoj = false;}
      if(zeOxhdJbTB == true){zeOxhdJbTB = false;}
      if(SfUSWCnOAj == true){SfUSWCnOAj = false;}
      if(saZBCWEMwI == true){saZBCWEMwI = false;}
      if(qbFyPmACQi == true){qbFyPmACQi = false;}
      if(bgRmLTFUHw == true){bgRmLTFUHw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XGZQPONLJP
{ 
  void FsIAFuTRYJ()
  { 
      bool TFWEXOhZzV = false;
      bool RciBEXXYpT = false;
      bool qJBFmhjzAl = false;
      bool HwDczruWPI = false;
      bool PeoArDSlZD = false;
      bool LrGxzKERQo = false;
      bool dhYMOUZGBL = false;
      bool bAJgELTANj = false;
      bool PyZxaOpGco = false;
      bool mdFadgGclW = false;
      bool dLjNaKiYrm = false;
      bool pDDgYfIakz = false;
      bool dSdMXxthCW = false;
      bool FqNpGENMVP = false;
      bool eQNoyjZYBx = false;
      bool YfqmsKhWoc = false;
      bool QAVVhzoNaU = false;
      bool SwEUTNFnOn = false;
      bool XUgExYzaxu = false;
      bool VpWrzetqGz = false;
      string SjUnQlMGws;
      string mFXCWWKUyc;
      string VKtMYoeWkl;
      string GsYMBNbjxE;
      string EqGLtsLNMZ;
      string XWDtEIoHOb;
      string GoVJmtgKBI;
      string uaWtYdDhRf;
      string dQKLOioeIr;
      string YTUVxPVwYA;
      string LAMDdwAJVZ;
      string EHpixodKtE;
      string EBCIjbFAwI;
      string IHJRTdEGgS;
      string heIhnQdlYI;
      string kLBUuKxDTC;
      string qzNMRxxXOT;
      string jWdbVYrUTS;
      string ySbnWxFnWJ;
      string fBmdaiRwQq;
      if(SjUnQlMGws == LAMDdwAJVZ){TFWEXOhZzV = true;}
      else if(LAMDdwAJVZ == SjUnQlMGws){dLjNaKiYrm = true;}
      if(mFXCWWKUyc == EHpixodKtE){RciBEXXYpT = true;}
      else if(EHpixodKtE == mFXCWWKUyc){pDDgYfIakz = true;}
      if(VKtMYoeWkl == EBCIjbFAwI){qJBFmhjzAl = true;}
      else if(EBCIjbFAwI == VKtMYoeWkl){dSdMXxthCW = true;}
      if(GsYMBNbjxE == IHJRTdEGgS){HwDczruWPI = true;}
      else if(IHJRTdEGgS == GsYMBNbjxE){FqNpGENMVP = true;}
      if(EqGLtsLNMZ == heIhnQdlYI){PeoArDSlZD = true;}
      else if(heIhnQdlYI == EqGLtsLNMZ){eQNoyjZYBx = true;}
      if(XWDtEIoHOb == kLBUuKxDTC){LrGxzKERQo = true;}
      else if(kLBUuKxDTC == XWDtEIoHOb){YfqmsKhWoc = true;}
      if(GoVJmtgKBI == qzNMRxxXOT){dhYMOUZGBL = true;}
      else if(qzNMRxxXOT == GoVJmtgKBI){QAVVhzoNaU = true;}
      if(uaWtYdDhRf == jWdbVYrUTS){bAJgELTANj = true;}
      if(dQKLOioeIr == ySbnWxFnWJ){PyZxaOpGco = true;}
      if(YTUVxPVwYA == fBmdaiRwQq){mdFadgGclW = true;}
      while(jWdbVYrUTS == uaWtYdDhRf){SwEUTNFnOn = true;}
      while(ySbnWxFnWJ == ySbnWxFnWJ){XUgExYzaxu = true;}
      while(fBmdaiRwQq == fBmdaiRwQq){VpWrzetqGz = true;}
      if(TFWEXOhZzV == true){TFWEXOhZzV = false;}
      if(RciBEXXYpT == true){RciBEXXYpT = false;}
      if(qJBFmhjzAl == true){qJBFmhjzAl = false;}
      if(HwDczruWPI == true){HwDczruWPI = false;}
      if(PeoArDSlZD == true){PeoArDSlZD = false;}
      if(LrGxzKERQo == true){LrGxzKERQo = false;}
      if(dhYMOUZGBL == true){dhYMOUZGBL = false;}
      if(bAJgELTANj == true){bAJgELTANj = false;}
      if(PyZxaOpGco == true){PyZxaOpGco = false;}
      if(mdFadgGclW == true){mdFadgGclW = false;}
      if(dLjNaKiYrm == true){dLjNaKiYrm = false;}
      if(pDDgYfIakz == true){pDDgYfIakz = false;}
      if(dSdMXxthCW == true){dSdMXxthCW = false;}
      if(FqNpGENMVP == true){FqNpGENMVP = false;}
      if(eQNoyjZYBx == true){eQNoyjZYBx = false;}
      if(YfqmsKhWoc == true){YfqmsKhWoc = false;}
      if(QAVVhzoNaU == true){QAVVhzoNaU = false;}
      if(SwEUTNFnOn == true){SwEUTNFnOn = false;}
      if(XUgExYzaxu == true){XUgExYzaxu = false;}
      if(VpWrzetqGz == true){VpWrzetqGz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SUIHRTFCDE
{ 
  void sjeQEuQokg()
  { 
      bool jCrIYeRYup = false;
      bool SSoBJTHpPW = false;
      bool ZghCmaiEOE = false;
      bool PxQAWgxnPQ = false;
      bool iUHpEFsrlk = false;
      bool oHgkzDToVx = false;
      bool wNJqZVCndb = false;
      bool VTaynFYryg = false;
      bool hpRcOIQfAS = false;
      bool MIRRUUKQPi = false;
      bool DENJOVghxt = false;
      bool ebqoPGugbR = false;
      bool EVmLONBJdS = false;
      bool uHbOdcbIOs = false;
      bool ahiGnkRcCO = false;
      bool ZcnydgRCtA = false;
      bool TXEdzXzbLl = false;
      bool dmSipVmgXd = false;
      bool wYHPrRSdjw = false;
      bool LYNNYDdEHP = false;
      string YPnNLhiaHh;
      string bSEhbUfuDI;
      string FGcFzanLAo;
      string HBnhPsAsgl;
      string NfsaWwQDUP;
      string GjUMNRlhOk;
      string sXZRaZeWSi;
      string TmNQuYMBhC;
      string JjpkiXgaTy;
      string GRdwrpGbAx;
      string RtkluSVDRo;
      string EkALaJgoiD;
      string rDCUcCIRXF;
      string RkAkkPzDoP;
      string BdJesURSUi;
      string IRrxENqQJs;
      string KEeMWSjOaL;
      string JczTBOtXaH;
      string jpxowAsDfX;
      string YituFxywHZ;
      if(YPnNLhiaHh == RtkluSVDRo){jCrIYeRYup = true;}
      else if(RtkluSVDRo == YPnNLhiaHh){DENJOVghxt = true;}
      if(bSEhbUfuDI == EkALaJgoiD){SSoBJTHpPW = true;}
      else if(EkALaJgoiD == bSEhbUfuDI){ebqoPGugbR = true;}
      if(FGcFzanLAo == rDCUcCIRXF){ZghCmaiEOE = true;}
      else if(rDCUcCIRXF == FGcFzanLAo){EVmLONBJdS = true;}
      if(HBnhPsAsgl == RkAkkPzDoP){PxQAWgxnPQ = true;}
      else if(RkAkkPzDoP == HBnhPsAsgl){uHbOdcbIOs = true;}
      if(NfsaWwQDUP == BdJesURSUi){iUHpEFsrlk = true;}
      else if(BdJesURSUi == NfsaWwQDUP){ahiGnkRcCO = true;}
      if(GjUMNRlhOk == IRrxENqQJs){oHgkzDToVx = true;}
      else if(IRrxENqQJs == GjUMNRlhOk){ZcnydgRCtA = true;}
      if(sXZRaZeWSi == KEeMWSjOaL){wNJqZVCndb = true;}
      else if(KEeMWSjOaL == sXZRaZeWSi){TXEdzXzbLl = true;}
      if(TmNQuYMBhC == JczTBOtXaH){VTaynFYryg = true;}
      if(JjpkiXgaTy == jpxowAsDfX){hpRcOIQfAS = true;}
      if(GRdwrpGbAx == YituFxywHZ){MIRRUUKQPi = true;}
      while(JczTBOtXaH == TmNQuYMBhC){dmSipVmgXd = true;}
      while(jpxowAsDfX == jpxowAsDfX){wYHPrRSdjw = true;}
      while(YituFxywHZ == YituFxywHZ){LYNNYDdEHP = true;}
      if(jCrIYeRYup == true){jCrIYeRYup = false;}
      if(SSoBJTHpPW == true){SSoBJTHpPW = false;}
      if(ZghCmaiEOE == true){ZghCmaiEOE = false;}
      if(PxQAWgxnPQ == true){PxQAWgxnPQ = false;}
      if(iUHpEFsrlk == true){iUHpEFsrlk = false;}
      if(oHgkzDToVx == true){oHgkzDToVx = false;}
      if(wNJqZVCndb == true){wNJqZVCndb = false;}
      if(VTaynFYryg == true){VTaynFYryg = false;}
      if(hpRcOIQfAS == true){hpRcOIQfAS = false;}
      if(MIRRUUKQPi == true){MIRRUUKQPi = false;}
      if(DENJOVghxt == true){DENJOVghxt = false;}
      if(ebqoPGugbR == true){ebqoPGugbR = false;}
      if(EVmLONBJdS == true){EVmLONBJdS = false;}
      if(uHbOdcbIOs == true){uHbOdcbIOs = false;}
      if(ahiGnkRcCO == true){ahiGnkRcCO = false;}
      if(ZcnydgRCtA == true){ZcnydgRCtA = false;}
      if(TXEdzXzbLl == true){TXEdzXzbLl = false;}
      if(dmSipVmgXd == true){dmSipVmgXd = false;}
      if(wYHPrRSdjw == true){wYHPrRSdjw = false;}
      if(LYNNYDdEHP == true){LYNNYDdEHP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BECPEKYBRZ
{ 
  void egWcbciOOH()
  { 
      bool teyMFsjqNq = false;
      bool ACZgITpBUg = false;
      bool SieofaFoDY = false;
      bool bhRAwxVuAJ = false;
      bool imLmsrJKau = false;
      bool PjaajKzIgd = false;
      bool mumnPRkYkL = false;
      bool ytALyfXrwm = false;
      bool RuNHJqHpQk = false;
      bool xMOVVnzWXa = false;
      bool HjYPxUiOcD = false;
      bool mHMtMqhfeY = false;
      bool KtIzOkfeoJ = false;
      bool gATUehVxKo = false;
      bool HsMNxpATJe = false;
      bool GSryQMbYBM = false;
      bool oEYSVlmrOe = false;
      bool UjVpQQhtCX = false;
      bool jLUKDNIVDR = false;
      bool FwwxzDTsrK = false;
      string ZYhNGrKrrR;
      string CTTkWcrLam;
      string ASEpEUVTab;
      string iUpwtzbzZM;
      string sUxKtEiZnE;
      string hhuIJHUqIk;
      string VqQPihdWqX;
      string BrlOsfVswz;
      string kweWsAZgml;
      string djqnpBDgaM;
      string aMhQCowfOc;
      string latIzYLtWi;
      string HwjEsRBxXr;
      string cnRjYYNOUD;
      string EtSJADohnQ;
      string pJKrEecdWj;
      string nyIWAxIKja;
      string LxYSeNdZDp;
      string bTIGCTdZet;
      string ujqjPFluID;
      if(ZYhNGrKrrR == aMhQCowfOc){teyMFsjqNq = true;}
      else if(aMhQCowfOc == ZYhNGrKrrR){HjYPxUiOcD = true;}
      if(CTTkWcrLam == latIzYLtWi){ACZgITpBUg = true;}
      else if(latIzYLtWi == CTTkWcrLam){mHMtMqhfeY = true;}
      if(ASEpEUVTab == HwjEsRBxXr){SieofaFoDY = true;}
      else if(HwjEsRBxXr == ASEpEUVTab){KtIzOkfeoJ = true;}
      if(iUpwtzbzZM == cnRjYYNOUD){bhRAwxVuAJ = true;}
      else if(cnRjYYNOUD == iUpwtzbzZM){gATUehVxKo = true;}
      if(sUxKtEiZnE == EtSJADohnQ){imLmsrJKau = true;}
      else if(EtSJADohnQ == sUxKtEiZnE){HsMNxpATJe = true;}
      if(hhuIJHUqIk == pJKrEecdWj){PjaajKzIgd = true;}
      else if(pJKrEecdWj == hhuIJHUqIk){GSryQMbYBM = true;}
      if(VqQPihdWqX == nyIWAxIKja){mumnPRkYkL = true;}
      else if(nyIWAxIKja == VqQPihdWqX){oEYSVlmrOe = true;}
      if(BrlOsfVswz == LxYSeNdZDp){ytALyfXrwm = true;}
      if(kweWsAZgml == bTIGCTdZet){RuNHJqHpQk = true;}
      if(djqnpBDgaM == ujqjPFluID){xMOVVnzWXa = true;}
      while(LxYSeNdZDp == BrlOsfVswz){UjVpQQhtCX = true;}
      while(bTIGCTdZet == bTIGCTdZet){jLUKDNIVDR = true;}
      while(ujqjPFluID == ujqjPFluID){FwwxzDTsrK = true;}
      if(teyMFsjqNq == true){teyMFsjqNq = false;}
      if(ACZgITpBUg == true){ACZgITpBUg = false;}
      if(SieofaFoDY == true){SieofaFoDY = false;}
      if(bhRAwxVuAJ == true){bhRAwxVuAJ = false;}
      if(imLmsrJKau == true){imLmsrJKau = false;}
      if(PjaajKzIgd == true){PjaajKzIgd = false;}
      if(mumnPRkYkL == true){mumnPRkYkL = false;}
      if(ytALyfXrwm == true){ytALyfXrwm = false;}
      if(RuNHJqHpQk == true){RuNHJqHpQk = false;}
      if(xMOVVnzWXa == true){xMOVVnzWXa = false;}
      if(HjYPxUiOcD == true){HjYPxUiOcD = false;}
      if(mHMtMqhfeY == true){mHMtMqhfeY = false;}
      if(KtIzOkfeoJ == true){KtIzOkfeoJ = false;}
      if(gATUehVxKo == true){gATUehVxKo = false;}
      if(HsMNxpATJe == true){HsMNxpATJe = false;}
      if(GSryQMbYBM == true){GSryQMbYBM = false;}
      if(oEYSVlmrOe == true){oEYSVlmrOe = false;}
      if(UjVpQQhtCX == true){UjVpQQhtCX = false;}
      if(jLUKDNIVDR == true){jLUKDNIVDR = false;}
      if(FwwxzDTsrK == true){FwwxzDTsrK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGSJLTDTCV
{ 
  void qKQtXMiLpb()
  { 
      bool mkRtoVZXrk = false;
      bool VxrpDlFKQU = false;
      bool rYFaTQtLJc = false;
      bool ncZrbskEbw = false;
      bool mJrGSTJyMW = false;
      bool zomePNfqZY = false;
      bool aOOOxrWAOJ = false;
      bool AAhTghgzIA = false;
      bool HwyldyoucN = false;
      bool NteDUYucJZ = false;
      bool wJjDWyHTxg = false;
      bool ffhYReQbky = false;
      bool CbWAuFVezH = false;
      bool lEphDxMtOe = false;
      bool qVxuggMFkp = false;
      bool ITrLXUljHR = false;
      bool cbUpubpzVT = false;
      bool SVNFGfdaSN = false;
      bool sPsIzSMeKi = false;
      bool LblxCOBHAF = false;
      string MUTdcpoZSt;
      string YbDYiilkBe;
      string ngauGiIBDa;
      string LdLSLJWMAE;
      string XxAzloPmpI;
      string ATzPnetXXt;
      string hnVqiuQkNZ;
      string MZkxHqgaIQ;
      string TUKuZqdudf;
      string OynGWibIQq;
      string YdZQwaiCHx;
      string ySPHaNdZRq;
      string QUGgKNkdaY;
      string OYJRrottyz;
      string IbmggwigfI;
      string FBpZZDXrFh;
      string oEbihZIxPk;
      string SibShnhZzO;
      string eDyRSNhjqn;
      string RCnQJEAEzH;
      if(MUTdcpoZSt == YdZQwaiCHx){mkRtoVZXrk = true;}
      else if(YdZQwaiCHx == MUTdcpoZSt){wJjDWyHTxg = true;}
      if(YbDYiilkBe == ySPHaNdZRq){VxrpDlFKQU = true;}
      else if(ySPHaNdZRq == YbDYiilkBe){ffhYReQbky = true;}
      if(ngauGiIBDa == QUGgKNkdaY){rYFaTQtLJc = true;}
      else if(QUGgKNkdaY == ngauGiIBDa){CbWAuFVezH = true;}
      if(LdLSLJWMAE == OYJRrottyz){ncZrbskEbw = true;}
      else if(OYJRrottyz == LdLSLJWMAE){lEphDxMtOe = true;}
      if(XxAzloPmpI == IbmggwigfI){mJrGSTJyMW = true;}
      else if(IbmggwigfI == XxAzloPmpI){qVxuggMFkp = true;}
      if(ATzPnetXXt == FBpZZDXrFh){zomePNfqZY = true;}
      else if(FBpZZDXrFh == ATzPnetXXt){ITrLXUljHR = true;}
      if(hnVqiuQkNZ == oEbihZIxPk){aOOOxrWAOJ = true;}
      else if(oEbihZIxPk == hnVqiuQkNZ){cbUpubpzVT = true;}
      if(MZkxHqgaIQ == SibShnhZzO){AAhTghgzIA = true;}
      if(TUKuZqdudf == eDyRSNhjqn){HwyldyoucN = true;}
      if(OynGWibIQq == RCnQJEAEzH){NteDUYucJZ = true;}
      while(SibShnhZzO == MZkxHqgaIQ){SVNFGfdaSN = true;}
      while(eDyRSNhjqn == eDyRSNhjqn){sPsIzSMeKi = true;}
      while(RCnQJEAEzH == RCnQJEAEzH){LblxCOBHAF = true;}
      if(mkRtoVZXrk == true){mkRtoVZXrk = false;}
      if(VxrpDlFKQU == true){VxrpDlFKQU = false;}
      if(rYFaTQtLJc == true){rYFaTQtLJc = false;}
      if(ncZrbskEbw == true){ncZrbskEbw = false;}
      if(mJrGSTJyMW == true){mJrGSTJyMW = false;}
      if(zomePNfqZY == true){zomePNfqZY = false;}
      if(aOOOxrWAOJ == true){aOOOxrWAOJ = false;}
      if(AAhTghgzIA == true){AAhTghgzIA = false;}
      if(HwyldyoucN == true){HwyldyoucN = false;}
      if(NteDUYucJZ == true){NteDUYucJZ = false;}
      if(wJjDWyHTxg == true){wJjDWyHTxg = false;}
      if(ffhYReQbky == true){ffhYReQbky = false;}
      if(CbWAuFVezH == true){CbWAuFVezH = false;}
      if(lEphDxMtOe == true){lEphDxMtOe = false;}
      if(qVxuggMFkp == true){qVxuggMFkp = false;}
      if(ITrLXUljHR == true){ITrLXUljHR = false;}
      if(cbUpubpzVT == true){cbUpubpzVT = false;}
      if(SVNFGfdaSN == true){SVNFGfdaSN = false;}
      if(sPsIzSMeKi == true){sPsIzSMeKi = false;}
      if(LblxCOBHAF == true){LblxCOBHAF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWPPRNCJOK
{ 
  void EeDZsrOolp()
  { 
      bool LsyWqTUFBA = false;
      bool rxXwyCiOTR = false;
      bool fabTDaImjo = false;
      bool CIByZXqSfd = false;
      bool HDsdAwNCGA = false;
      bool FZKqIkReTQ = false;
      bool KgVMxjwYVa = false;
      bool KQioKbgxSG = false;
      bool MGgjicxJoo = false;
      bool FMyOSZhgfQ = false;
      bool AofeooqUgg = false;
      bool DULMDEAlcU = false;
      bool lligUyRTWj = false;
      bool sAQCGXZBus = false;
      bool lccIkkBkKN = false;
      bool ZwDLeNFzKp = false;
      bool XWywmDDIGf = false;
      bool eyqjhIJawj = false;
      bool wfIIKxxEWr = false;
      bool SaqEVOefUh = false;
      string xEPCdUNnLx;
      string ICjcceYdkk;
      string AcIFcBmnZm;
      string JxcipblXxu;
      string qmzKWoZODY;
      string wOFlwUwKZb;
      string gZNYmLZBmA;
      string rAfpsNcyhm;
      string aXjBquqplV;
      string fbyVNRYaWL;
      string OXbCfuhPsh;
      string rxblAJoMhq;
      string TjOQUQCJba;
      string nCaVYDwgUu;
      string NbwDdhzLUE;
      string cMrfreIKhP;
      string rXmRtoWFNx;
      string MIrldqmLml;
      string QpoXybJuds;
      string tlzECoodJn;
      if(xEPCdUNnLx == OXbCfuhPsh){LsyWqTUFBA = true;}
      else if(OXbCfuhPsh == xEPCdUNnLx){AofeooqUgg = true;}
      if(ICjcceYdkk == rxblAJoMhq){rxXwyCiOTR = true;}
      else if(rxblAJoMhq == ICjcceYdkk){DULMDEAlcU = true;}
      if(AcIFcBmnZm == TjOQUQCJba){fabTDaImjo = true;}
      else if(TjOQUQCJba == AcIFcBmnZm){lligUyRTWj = true;}
      if(JxcipblXxu == nCaVYDwgUu){CIByZXqSfd = true;}
      else if(nCaVYDwgUu == JxcipblXxu){sAQCGXZBus = true;}
      if(qmzKWoZODY == NbwDdhzLUE){HDsdAwNCGA = true;}
      else if(NbwDdhzLUE == qmzKWoZODY){lccIkkBkKN = true;}
      if(wOFlwUwKZb == cMrfreIKhP){FZKqIkReTQ = true;}
      else if(cMrfreIKhP == wOFlwUwKZb){ZwDLeNFzKp = true;}
      if(gZNYmLZBmA == rXmRtoWFNx){KgVMxjwYVa = true;}
      else if(rXmRtoWFNx == gZNYmLZBmA){XWywmDDIGf = true;}
      if(rAfpsNcyhm == MIrldqmLml){KQioKbgxSG = true;}
      if(aXjBquqplV == QpoXybJuds){MGgjicxJoo = true;}
      if(fbyVNRYaWL == tlzECoodJn){FMyOSZhgfQ = true;}
      while(MIrldqmLml == rAfpsNcyhm){eyqjhIJawj = true;}
      while(QpoXybJuds == QpoXybJuds){wfIIKxxEWr = true;}
      while(tlzECoodJn == tlzECoodJn){SaqEVOefUh = true;}
      if(LsyWqTUFBA == true){LsyWqTUFBA = false;}
      if(rxXwyCiOTR == true){rxXwyCiOTR = false;}
      if(fabTDaImjo == true){fabTDaImjo = false;}
      if(CIByZXqSfd == true){CIByZXqSfd = false;}
      if(HDsdAwNCGA == true){HDsdAwNCGA = false;}
      if(FZKqIkReTQ == true){FZKqIkReTQ = false;}
      if(KgVMxjwYVa == true){KgVMxjwYVa = false;}
      if(KQioKbgxSG == true){KQioKbgxSG = false;}
      if(MGgjicxJoo == true){MGgjicxJoo = false;}
      if(FMyOSZhgfQ == true){FMyOSZhgfQ = false;}
      if(AofeooqUgg == true){AofeooqUgg = false;}
      if(DULMDEAlcU == true){DULMDEAlcU = false;}
      if(lligUyRTWj == true){lligUyRTWj = false;}
      if(sAQCGXZBus == true){sAQCGXZBus = false;}
      if(lccIkkBkKN == true){lccIkkBkKN = false;}
      if(ZwDLeNFzKp == true){ZwDLeNFzKp = false;}
      if(XWywmDDIGf == true){XWywmDDIGf = false;}
      if(eyqjhIJawj == true){eyqjhIJawj = false;}
      if(wfIIKxxEWr == true){wfIIKxxEWr = false;}
      if(SaqEVOefUh == true){SaqEVOefUh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NSEEMSDSUS
{ 
  void NbVQJeFHXu()
  { 
      bool eEcSlOhbTb = false;
      bool rGwphzCHOG = false;
      bool OcleRpFJFE = false;
      bool KVbMbdhCzZ = false;
      bool yzaGQSonfo = false;
      bool bNROOCSxAw = false;
      bool IXWPRVejOD = false;
      bool RzHnHPCfOz = false;
      bool BQdPbwENxZ = false;
      bool LjBDQZcKnt = false;
      bool nEZcXbGdGz = false;
      bool zmiBurtGmU = false;
      bool RQmorgyEXg = false;
      bool mqqTLwqArA = false;
      bool pZHxZXBzIY = false;
      bool fVXScWRjkp = false;
      bool dBFZMIwOpy = false;
      bool AtOmeqJoOT = false;
      bool fyuyBQTXpn = false;
      bool eGPCVnTgjQ = false;
      string LRxCoMhdkz;
      string ZbtePZQtFO;
      string QJKwahnfUF;
      string MVPHLeihkn;
      string OSuZFqwRsQ;
      string UJMpYCGAaG;
      string XBIemDLmTj;
      string qiIRAyNkqi;
      string lWmEkCJZhI;
      string YhHdPMKPmB;
      string fIyJYlBupa;
      string nVJqUBNDsj;
      string tlEKKIadBm;
      string mxxoDcYdez;
      string BOiHUDYQJO;
      string zGVCHtDmyQ;
      string KWsCmpXTnq;
      string bjXtieCxpH;
      string iKUlngathI;
      string YleOodUfUd;
      if(LRxCoMhdkz == fIyJYlBupa){eEcSlOhbTb = true;}
      else if(fIyJYlBupa == LRxCoMhdkz){nEZcXbGdGz = true;}
      if(ZbtePZQtFO == nVJqUBNDsj){rGwphzCHOG = true;}
      else if(nVJqUBNDsj == ZbtePZQtFO){zmiBurtGmU = true;}
      if(QJKwahnfUF == tlEKKIadBm){OcleRpFJFE = true;}
      else if(tlEKKIadBm == QJKwahnfUF){RQmorgyEXg = true;}
      if(MVPHLeihkn == mxxoDcYdez){KVbMbdhCzZ = true;}
      else if(mxxoDcYdez == MVPHLeihkn){mqqTLwqArA = true;}
      if(OSuZFqwRsQ == BOiHUDYQJO){yzaGQSonfo = true;}
      else if(BOiHUDYQJO == OSuZFqwRsQ){pZHxZXBzIY = true;}
      if(UJMpYCGAaG == zGVCHtDmyQ){bNROOCSxAw = true;}
      else if(zGVCHtDmyQ == UJMpYCGAaG){fVXScWRjkp = true;}
      if(XBIemDLmTj == KWsCmpXTnq){IXWPRVejOD = true;}
      else if(KWsCmpXTnq == XBIemDLmTj){dBFZMIwOpy = true;}
      if(qiIRAyNkqi == bjXtieCxpH){RzHnHPCfOz = true;}
      if(lWmEkCJZhI == iKUlngathI){BQdPbwENxZ = true;}
      if(YhHdPMKPmB == YleOodUfUd){LjBDQZcKnt = true;}
      while(bjXtieCxpH == qiIRAyNkqi){AtOmeqJoOT = true;}
      while(iKUlngathI == iKUlngathI){fyuyBQTXpn = true;}
      while(YleOodUfUd == YleOodUfUd){eGPCVnTgjQ = true;}
      if(eEcSlOhbTb == true){eEcSlOhbTb = false;}
      if(rGwphzCHOG == true){rGwphzCHOG = false;}
      if(OcleRpFJFE == true){OcleRpFJFE = false;}
      if(KVbMbdhCzZ == true){KVbMbdhCzZ = false;}
      if(yzaGQSonfo == true){yzaGQSonfo = false;}
      if(bNROOCSxAw == true){bNROOCSxAw = false;}
      if(IXWPRVejOD == true){IXWPRVejOD = false;}
      if(RzHnHPCfOz == true){RzHnHPCfOz = false;}
      if(BQdPbwENxZ == true){BQdPbwENxZ = false;}
      if(LjBDQZcKnt == true){LjBDQZcKnt = false;}
      if(nEZcXbGdGz == true){nEZcXbGdGz = false;}
      if(zmiBurtGmU == true){zmiBurtGmU = false;}
      if(RQmorgyEXg == true){RQmorgyEXg = false;}
      if(mqqTLwqArA == true){mqqTLwqArA = false;}
      if(pZHxZXBzIY == true){pZHxZXBzIY = false;}
      if(fVXScWRjkp == true){fVXScWRjkp = false;}
      if(dBFZMIwOpy == true){dBFZMIwOpy = false;}
      if(AtOmeqJoOT == true){AtOmeqJoOT = false;}
      if(fyuyBQTXpn == true){fyuyBQTXpn = false;}
      if(eGPCVnTgjQ == true){eGPCVnTgjQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WJZNNPHFEP
{ 
  void aEcRaMkeYl()
  { 
      bool hpqeRrFxYR = false;
      bool CrdFwxtUKL = false;
      bool aykHifIulg = false;
      bool cPNakBctUB = false;
      bool uInVdjuEFK = false;
      bool MhjghjFjuk = false;
      bool iJLqnmdCTt = false;
      bool TAzJQSKOcz = false;
      bool kEpbUuefsB = false;
      bool usyjRkxwhq = false;
      bool FskKpMhaQP = false;
      bool ZqGwAeTjWs = false;
      bool HxIRyaBPqe = false;
      bool UNglsrTfkI = false;
      bool MDPdbEmCil = false;
      bool RMYniIjSLO = false;
      bool KRiltLKUDI = false;
      bool LmyOfEgept = false;
      bool nygEMIorCk = false;
      bool IATVxuTdiP = false;
      string KwQNHkanjH;
      string rzNzQlepOw;
      string HaFiLhOEOY;
      string hWfeEVGPAm;
      string hOUCJsukhb;
      string gXsWIjphBY;
      string WWZKYUTiut;
      string fOpaOrGDYS;
      string mdVlrJdIVT;
      string fXOaQKoJcn;
      string YLomwRhSIP;
      string dlJhlsAmSP;
      string qLMaNHAOKD;
      string DwaktanipZ;
      string aLAFptOfoW;
      string JCpNxNzOYn;
      string RTIEMgLXnK;
      string FRxsnfKGkT;
      string rUYmsAFMmg;
      string bYJBHHCusJ;
      if(KwQNHkanjH == YLomwRhSIP){hpqeRrFxYR = true;}
      else if(YLomwRhSIP == KwQNHkanjH){FskKpMhaQP = true;}
      if(rzNzQlepOw == dlJhlsAmSP){CrdFwxtUKL = true;}
      else if(dlJhlsAmSP == rzNzQlepOw){ZqGwAeTjWs = true;}
      if(HaFiLhOEOY == qLMaNHAOKD){aykHifIulg = true;}
      else if(qLMaNHAOKD == HaFiLhOEOY){HxIRyaBPqe = true;}
      if(hWfeEVGPAm == DwaktanipZ){cPNakBctUB = true;}
      else if(DwaktanipZ == hWfeEVGPAm){UNglsrTfkI = true;}
      if(hOUCJsukhb == aLAFptOfoW){uInVdjuEFK = true;}
      else if(aLAFptOfoW == hOUCJsukhb){MDPdbEmCil = true;}
      if(gXsWIjphBY == JCpNxNzOYn){MhjghjFjuk = true;}
      else if(JCpNxNzOYn == gXsWIjphBY){RMYniIjSLO = true;}
      if(WWZKYUTiut == RTIEMgLXnK){iJLqnmdCTt = true;}
      else if(RTIEMgLXnK == WWZKYUTiut){KRiltLKUDI = true;}
      if(fOpaOrGDYS == FRxsnfKGkT){TAzJQSKOcz = true;}
      if(mdVlrJdIVT == rUYmsAFMmg){kEpbUuefsB = true;}
      if(fXOaQKoJcn == bYJBHHCusJ){usyjRkxwhq = true;}
      while(FRxsnfKGkT == fOpaOrGDYS){LmyOfEgept = true;}
      while(rUYmsAFMmg == rUYmsAFMmg){nygEMIorCk = true;}
      while(bYJBHHCusJ == bYJBHHCusJ){IATVxuTdiP = true;}
      if(hpqeRrFxYR == true){hpqeRrFxYR = false;}
      if(CrdFwxtUKL == true){CrdFwxtUKL = false;}
      if(aykHifIulg == true){aykHifIulg = false;}
      if(cPNakBctUB == true){cPNakBctUB = false;}
      if(uInVdjuEFK == true){uInVdjuEFK = false;}
      if(MhjghjFjuk == true){MhjghjFjuk = false;}
      if(iJLqnmdCTt == true){iJLqnmdCTt = false;}
      if(TAzJQSKOcz == true){TAzJQSKOcz = false;}
      if(kEpbUuefsB == true){kEpbUuefsB = false;}
      if(usyjRkxwhq == true){usyjRkxwhq = false;}
      if(FskKpMhaQP == true){FskKpMhaQP = false;}
      if(ZqGwAeTjWs == true){ZqGwAeTjWs = false;}
      if(HxIRyaBPqe == true){HxIRyaBPqe = false;}
      if(UNglsrTfkI == true){UNglsrTfkI = false;}
      if(MDPdbEmCil == true){MDPdbEmCil = false;}
      if(RMYniIjSLO == true){RMYniIjSLO = false;}
      if(KRiltLKUDI == true){KRiltLKUDI = false;}
      if(LmyOfEgept == true){LmyOfEgept = false;}
      if(nygEMIorCk == true){nygEMIorCk = false;}
      if(IATVxuTdiP == true){IATVxuTdiP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQZGJKGYWY
{ 
  void rhKZXuGuTc()
  { 
      bool BatFhCKxCl = false;
      bool gANWxonBdu = false;
      bool xRVgAwhziW = false;
      bool GhKXaPaXlt = false;
      bool GQoXMMXcwS = false;
      bool HTmFRjENFl = false;
      bool TKOfezopuh = false;
      bool NPPjnfcxTm = false;
      bool XFDPOmtFFq = false;
      bool KNRzZuBIsN = false;
      bool WghOFqDDQk = false;
      bool HGsROOHzRr = false;
      bool EijDWAyQJr = false;
      bool eTEGPpWnKW = false;
      bool jqnUjETAkK = false;
      bool nBqAInxdrE = false;
      bool slsXFnBlBX = false;
      bool qTotHMuPTR = false;
      bool gyfyEcbEyb = false;
      bool sswFcxyQOw = false;
      string JAZGSfVMQr;
      string tHKKkpXzZt;
      string foRKLWMyQh;
      string mbOlJPdNAE;
      string rbjFCPKNJx;
      string LMcMnUiPtw;
      string SXuhFSsYBU;
      string LJzVCDFMIu;
      string LynTVZyByo;
      string gOTDkTgBAi;
      string WlMnkCMGJj;
      string OVGykUibLe;
      string TqZLnxpukh;
      string WDMZYYlAhT;
      string MqrNZKHURQ;
      string kEoUOfLAAm;
      string LRVaMLJgZM;
      string hitqRbyLlc;
      string pVcTxROqKs;
      string MlAtIuVQBO;
      if(JAZGSfVMQr == WlMnkCMGJj){BatFhCKxCl = true;}
      else if(WlMnkCMGJj == JAZGSfVMQr){WghOFqDDQk = true;}
      if(tHKKkpXzZt == OVGykUibLe){gANWxonBdu = true;}
      else if(OVGykUibLe == tHKKkpXzZt){HGsROOHzRr = true;}
      if(foRKLWMyQh == TqZLnxpukh){xRVgAwhziW = true;}
      else if(TqZLnxpukh == foRKLWMyQh){EijDWAyQJr = true;}
      if(mbOlJPdNAE == WDMZYYlAhT){GhKXaPaXlt = true;}
      else if(WDMZYYlAhT == mbOlJPdNAE){eTEGPpWnKW = true;}
      if(rbjFCPKNJx == MqrNZKHURQ){GQoXMMXcwS = true;}
      else if(MqrNZKHURQ == rbjFCPKNJx){jqnUjETAkK = true;}
      if(LMcMnUiPtw == kEoUOfLAAm){HTmFRjENFl = true;}
      else if(kEoUOfLAAm == LMcMnUiPtw){nBqAInxdrE = true;}
      if(SXuhFSsYBU == LRVaMLJgZM){TKOfezopuh = true;}
      else if(LRVaMLJgZM == SXuhFSsYBU){slsXFnBlBX = true;}
      if(LJzVCDFMIu == hitqRbyLlc){NPPjnfcxTm = true;}
      if(LynTVZyByo == pVcTxROqKs){XFDPOmtFFq = true;}
      if(gOTDkTgBAi == MlAtIuVQBO){KNRzZuBIsN = true;}
      while(hitqRbyLlc == LJzVCDFMIu){qTotHMuPTR = true;}
      while(pVcTxROqKs == pVcTxROqKs){gyfyEcbEyb = true;}
      while(MlAtIuVQBO == MlAtIuVQBO){sswFcxyQOw = true;}
      if(BatFhCKxCl == true){BatFhCKxCl = false;}
      if(gANWxonBdu == true){gANWxonBdu = false;}
      if(xRVgAwhziW == true){xRVgAwhziW = false;}
      if(GhKXaPaXlt == true){GhKXaPaXlt = false;}
      if(GQoXMMXcwS == true){GQoXMMXcwS = false;}
      if(HTmFRjENFl == true){HTmFRjENFl = false;}
      if(TKOfezopuh == true){TKOfezopuh = false;}
      if(NPPjnfcxTm == true){NPPjnfcxTm = false;}
      if(XFDPOmtFFq == true){XFDPOmtFFq = false;}
      if(KNRzZuBIsN == true){KNRzZuBIsN = false;}
      if(WghOFqDDQk == true){WghOFqDDQk = false;}
      if(HGsROOHzRr == true){HGsROOHzRr = false;}
      if(EijDWAyQJr == true){EijDWAyQJr = false;}
      if(eTEGPpWnKW == true){eTEGPpWnKW = false;}
      if(jqnUjETAkK == true){jqnUjETAkK = false;}
      if(nBqAInxdrE == true){nBqAInxdrE = false;}
      if(slsXFnBlBX == true){slsXFnBlBX = false;}
      if(qTotHMuPTR == true){qTotHMuPTR = false;}
      if(gyfyEcbEyb == true){gyfyEcbEyb = false;}
      if(sswFcxyQOw == true){sswFcxyQOw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YQBPAZWBDY
{ 
  void bVyYxiDXBR()
  { 
      bool RYfSuTcOws = false;
      bool yOlPUaXwhq = false;
      bool AKCIqMhRHp = false;
      bool tLJGKiGbOW = false;
      bool eeFHqfNDWO = false;
      bool mrHtXGVXbh = false;
      bool lKHFzmEeFl = false;
      bool TuhLMUFuQL = false;
      bool zdurCCEOiD = false;
      bool MhzfjTXzIE = false;
      bool ahyktrKwhC = false;
      bool BaGQiHPODw = false;
      bool hpwBYluBar = false;
      bool wFlMjQfKyK = false;
      bool rIgfCkbiwc = false;
      bool EIwLVklwLI = false;
      bool wIUoGuotfR = false;
      bool aEQsEZJPym = false;
      bool KMExnnJZpz = false;
      bool eiypOimqZG = false;
      string UQPjoJPXfl;
      string yrEwXkCaul;
      string DFetnDDzEz;
      string JyaphbjPgq;
      string unpDHgGarR;
      string RMdbKPlVwl;
      string FQTfbzQNOu;
      string AltEpPPalG;
      string wcGmhwUzfS;
      string oNTtkeTJbH;
      string QrMxQeSZkt;
      string ALiopcJgye;
      string eQhwFmRzSL;
      string uFyepEPJVC;
      string duOkRddeEI;
      string UmKxcAKPqd;
      string NSGYztMEyk;
      string MAKwAiBwdb;
      string ImuKqHtBBp;
      string tzSroKnolX;
      if(UQPjoJPXfl == QrMxQeSZkt){RYfSuTcOws = true;}
      else if(QrMxQeSZkt == UQPjoJPXfl){ahyktrKwhC = true;}
      if(yrEwXkCaul == ALiopcJgye){yOlPUaXwhq = true;}
      else if(ALiopcJgye == yrEwXkCaul){BaGQiHPODw = true;}
      if(DFetnDDzEz == eQhwFmRzSL){AKCIqMhRHp = true;}
      else if(eQhwFmRzSL == DFetnDDzEz){hpwBYluBar = true;}
      if(JyaphbjPgq == uFyepEPJVC){tLJGKiGbOW = true;}
      else if(uFyepEPJVC == JyaphbjPgq){wFlMjQfKyK = true;}
      if(unpDHgGarR == duOkRddeEI){eeFHqfNDWO = true;}
      else if(duOkRddeEI == unpDHgGarR){rIgfCkbiwc = true;}
      if(RMdbKPlVwl == UmKxcAKPqd){mrHtXGVXbh = true;}
      else if(UmKxcAKPqd == RMdbKPlVwl){EIwLVklwLI = true;}
      if(FQTfbzQNOu == NSGYztMEyk){lKHFzmEeFl = true;}
      else if(NSGYztMEyk == FQTfbzQNOu){wIUoGuotfR = true;}
      if(AltEpPPalG == MAKwAiBwdb){TuhLMUFuQL = true;}
      if(wcGmhwUzfS == ImuKqHtBBp){zdurCCEOiD = true;}
      if(oNTtkeTJbH == tzSroKnolX){MhzfjTXzIE = true;}
      while(MAKwAiBwdb == AltEpPPalG){aEQsEZJPym = true;}
      while(ImuKqHtBBp == ImuKqHtBBp){KMExnnJZpz = true;}
      while(tzSroKnolX == tzSroKnolX){eiypOimqZG = true;}
      if(RYfSuTcOws == true){RYfSuTcOws = false;}
      if(yOlPUaXwhq == true){yOlPUaXwhq = false;}
      if(AKCIqMhRHp == true){AKCIqMhRHp = false;}
      if(tLJGKiGbOW == true){tLJGKiGbOW = false;}
      if(eeFHqfNDWO == true){eeFHqfNDWO = false;}
      if(mrHtXGVXbh == true){mrHtXGVXbh = false;}
      if(lKHFzmEeFl == true){lKHFzmEeFl = false;}
      if(TuhLMUFuQL == true){TuhLMUFuQL = false;}
      if(zdurCCEOiD == true){zdurCCEOiD = false;}
      if(MhzfjTXzIE == true){MhzfjTXzIE = false;}
      if(ahyktrKwhC == true){ahyktrKwhC = false;}
      if(BaGQiHPODw == true){BaGQiHPODw = false;}
      if(hpwBYluBar == true){hpwBYluBar = false;}
      if(wFlMjQfKyK == true){wFlMjQfKyK = false;}
      if(rIgfCkbiwc == true){rIgfCkbiwc = false;}
      if(EIwLVklwLI == true){EIwLVklwLI = false;}
      if(wIUoGuotfR == true){wIUoGuotfR = false;}
      if(aEQsEZJPym == true){aEQsEZJPym = false;}
      if(KMExnnJZpz == true){KMExnnJZpz = false;}
      if(eiypOimqZG == true){eiypOimqZG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QMVGLEMKZT
{ 
  void zIrBMdWjUR()
  { 
      bool KQGrWCgXuk = false;
      bool CUAVkpUNbE = false;
      bool bUsiFQDCAO = false;
      bool HnKWiYVMUG = false;
      bool xRsVyIEieL = false;
      bool VBBpwoXXmF = false;
      bool ydXfcOKdlL = false;
      bool TIrUGJaWjw = false;
      bool LUWnsGmTZs = false;
      bool ByZOIStNsj = false;
      bool yaxSqMIfjl = false;
      bool NAmptdGimW = false;
      bool bqDrJUicMn = false;
      bool PNdAykWExf = false;
      bool yGjnfBLiUd = false;
      bool LKaVHGXEJV = false;
      bool deSwWAVlrI = false;
      bool GClGXUHOMH = false;
      bool JzHibEmIsq = false;
      bool NStaCTnmRe = false;
      string lxFmCrqryU;
      string JXJjWLrQaX;
      string epgWMyiOGR;
      string aEckVlRYTZ;
      string QtdSFsixPd;
      string HDrLwuPhZD;
      string IblgtEuYNk;
      string sTwBHkMOQT;
      string PkzcJXMQoZ;
      string VjyPQnHxXA;
      string xKjeknGqDL;
      string iBRGnXcJWW;
      string rdimOJUfkT;
      string cPpPVFBUqU;
      string QUNdqUSrbr;
      string KyZBITawPb;
      string TZGjhSKBki;
      string VIRBFWQFut;
      string pcErIdpoHB;
      string dFEPBqOcuY;
      if(lxFmCrqryU == xKjeknGqDL){KQGrWCgXuk = true;}
      else if(xKjeknGqDL == lxFmCrqryU){yaxSqMIfjl = true;}
      if(JXJjWLrQaX == iBRGnXcJWW){CUAVkpUNbE = true;}
      else if(iBRGnXcJWW == JXJjWLrQaX){NAmptdGimW = true;}
      if(epgWMyiOGR == rdimOJUfkT){bUsiFQDCAO = true;}
      else if(rdimOJUfkT == epgWMyiOGR){bqDrJUicMn = true;}
      if(aEckVlRYTZ == cPpPVFBUqU){HnKWiYVMUG = true;}
      else if(cPpPVFBUqU == aEckVlRYTZ){PNdAykWExf = true;}
      if(QtdSFsixPd == QUNdqUSrbr){xRsVyIEieL = true;}
      else if(QUNdqUSrbr == QtdSFsixPd){yGjnfBLiUd = true;}
      if(HDrLwuPhZD == KyZBITawPb){VBBpwoXXmF = true;}
      else if(KyZBITawPb == HDrLwuPhZD){LKaVHGXEJV = true;}
      if(IblgtEuYNk == TZGjhSKBki){ydXfcOKdlL = true;}
      else if(TZGjhSKBki == IblgtEuYNk){deSwWAVlrI = true;}
      if(sTwBHkMOQT == VIRBFWQFut){TIrUGJaWjw = true;}
      if(PkzcJXMQoZ == pcErIdpoHB){LUWnsGmTZs = true;}
      if(VjyPQnHxXA == dFEPBqOcuY){ByZOIStNsj = true;}
      while(VIRBFWQFut == sTwBHkMOQT){GClGXUHOMH = true;}
      while(pcErIdpoHB == pcErIdpoHB){JzHibEmIsq = true;}
      while(dFEPBqOcuY == dFEPBqOcuY){NStaCTnmRe = true;}
      if(KQGrWCgXuk == true){KQGrWCgXuk = false;}
      if(CUAVkpUNbE == true){CUAVkpUNbE = false;}
      if(bUsiFQDCAO == true){bUsiFQDCAO = false;}
      if(HnKWiYVMUG == true){HnKWiYVMUG = false;}
      if(xRsVyIEieL == true){xRsVyIEieL = false;}
      if(VBBpwoXXmF == true){VBBpwoXXmF = false;}
      if(ydXfcOKdlL == true){ydXfcOKdlL = false;}
      if(TIrUGJaWjw == true){TIrUGJaWjw = false;}
      if(LUWnsGmTZs == true){LUWnsGmTZs = false;}
      if(ByZOIStNsj == true){ByZOIStNsj = false;}
      if(yaxSqMIfjl == true){yaxSqMIfjl = false;}
      if(NAmptdGimW == true){NAmptdGimW = false;}
      if(bqDrJUicMn == true){bqDrJUicMn = false;}
      if(PNdAykWExf == true){PNdAykWExf = false;}
      if(yGjnfBLiUd == true){yGjnfBLiUd = false;}
      if(LKaVHGXEJV == true){LKaVHGXEJV = false;}
      if(deSwWAVlrI == true){deSwWAVlrI = false;}
      if(GClGXUHOMH == true){GClGXUHOMH = false;}
      if(JzHibEmIsq == true){JzHibEmIsq = false;}
      if(NStaCTnmRe == true){NStaCTnmRe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YAOIXZHYMR
{ 
  void TdrNKmaZbU()
  { 
      bool NVrMPBQyyU = false;
      bool KSLmkjxiAA = false;
      bool WVgDqHjEZG = false;
      bool WQcXeXodxy = false;
      bool jHSAGOqqGj = false;
      bool HJKSuqnnUI = false;
      bool RLYrxspnIM = false;
      bool tSlCPODfwc = false;
      bool PsxoyNGKcm = false;
      bool iAJogXiaCM = false;
      bool YDitooWICf = false;
      bool nIrrrXOisj = false;
      bool mfKUctJwVr = false;
      bool ecciEMKDzJ = false;
      bool pxHwzaIQxI = false;
      bool JzgSZrrNQu = false;
      bool ealKALeInf = false;
      bool NKjisoXOUC = false;
      bool krzMhfuKJL = false;
      bool TwmDePKxun = false;
      string XboeDyjLOe;
      string hVthiAWwjJ;
      string QXVcZEoXXm;
      string PyDuYXwqIC;
      string CUAdctdwlC;
      string pEUYLAGLEy;
      string JLnbPjSzJL;
      string EfmhHuXqAf;
      string arlUwKcdjX;
      string QklJrpgXOr;
      string admayKRmRP;
      string cPLYWQZSeE;
      string GnPktTscoQ;
      string OzbHExFKWk;
      string spMTuBYMlb;
      string QNrKlmOBfe;
      string QnxABcmDUZ;
      string LOwtLQbups;
      string tgpNABGRVR;
      string hDdqTEsLSR;
      if(XboeDyjLOe == admayKRmRP){NVrMPBQyyU = true;}
      else if(admayKRmRP == XboeDyjLOe){YDitooWICf = true;}
      if(hVthiAWwjJ == cPLYWQZSeE){KSLmkjxiAA = true;}
      else if(cPLYWQZSeE == hVthiAWwjJ){nIrrrXOisj = true;}
      if(QXVcZEoXXm == GnPktTscoQ){WVgDqHjEZG = true;}
      else if(GnPktTscoQ == QXVcZEoXXm){mfKUctJwVr = true;}
      if(PyDuYXwqIC == OzbHExFKWk){WQcXeXodxy = true;}
      else if(OzbHExFKWk == PyDuYXwqIC){ecciEMKDzJ = true;}
      if(CUAdctdwlC == spMTuBYMlb){jHSAGOqqGj = true;}
      else if(spMTuBYMlb == CUAdctdwlC){pxHwzaIQxI = true;}
      if(pEUYLAGLEy == QNrKlmOBfe){HJKSuqnnUI = true;}
      else if(QNrKlmOBfe == pEUYLAGLEy){JzgSZrrNQu = true;}
      if(JLnbPjSzJL == QnxABcmDUZ){RLYrxspnIM = true;}
      else if(QnxABcmDUZ == JLnbPjSzJL){ealKALeInf = true;}
      if(EfmhHuXqAf == LOwtLQbups){tSlCPODfwc = true;}
      if(arlUwKcdjX == tgpNABGRVR){PsxoyNGKcm = true;}
      if(QklJrpgXOr == hDdqTEsLSR){iAJogXiaCM = true;}
      while(LOwtLQbups == EfmhHuXqAf){NKjisoXOUC = true;}
      while(tgpNABGRVR == tgpNABGRVR){krzMhfuKJL = true;}
      while(hDdqTEsLSR == hDdqTEsLSR){TwmDePKxun = true;}
      if(NVrMPBQyyU == true){NVrMPBQyyU = false;}
      if(KSLmkjxiAA == true){KSLmkjxiAA = false;}
      if(WVgDqHjEZG == true){WVgDqHjEZG = false;}
      if(WQcXeXodxy == true){WQcXeXodxy = false;}
      if(jHSAGOqqGj == true){jHSAGOqqGj = false;}
      if(HJKSuqnnUI == true){HJKSuqnnUI = false;}
      if(RLYrxspnIM == true){RLYrxspnIM = false;}
      if(tSlCPODfwc == true){tSlCPODfwc = false;}
      if(PsxoyNGKcm == true){PsxoyNGKcm = false;}
      if(iAJogXiaCM == true){iAJogXiaCM = false;}
      if(YDitooWICf == true){YDitooWICf = false;}
      if(nIrrrXOisj == true){nIrrrXOisj = false;}
      if(mfKUctJwVr == true){mfKUctJwVr = false;}
      if(ecciEMKDzJ == true){ecciEMKDzJ = false;}
      if(pxHwzaIQxI == true){pxHwzaIQxI = false;}
      if(JzgSZrrNQu == true){JzgSZrrNQu = false;}
      if(ealKALeInf == true){ealKALeInf = false;}
      if(NKjisoXOUC == true){NKjisoXOUC = false;}
      if(krzMhfuKJL == true){krzMhfuKJL = false;}
      if(TwmDePKxun == true){TwmDePKxun = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NTAWWPYGUE
{ 
  void aXnpczYGbD()
  { 
      bool rerbSFzVOq = false;
      bool pxTulcMANm = false;
      bool zHHwAqKKDq = false;
      bool wqRMPIGtyD = false;
      bool HiTueYbjeq = false;
      bool tdbWJjWuba = false;
      bool tnRXtzfGed = false;
      bool WRCJfQnMRb = false;
      bool PaeMwSOtDe = false;
      bool kKSWJSQwBf = false;
      bool sUEBUcaRqs = false;
      bool wKdALSIFab = false;
      bool jkDzrLyfAM = false;
      bool ArLkhtWdrT = false;
      bool qxDKiZfSKp = false;
      bool KKUZwIQEII = false;
      bool dtQerDzsRQ = false;
      bool weNHjlgsPS = false;
      bool eeVKCoXkoZ = false;
      bool dRUiowfYRf = false;
      string fKqnucpzwd;
      string keEbJGWfTA;
      string UUewQYplCw;
      string sbsoayTroR;
      string ZqLkAEVbGY;
      string PwpCGKeuWV;
      string lEwAjJkPAK;
      string ldpBZcJtuL;
      string CNedgwkphP;
      string TYUSeUtLAq;
      string SGaumkGncc;
      string BjzKTYZSSn;
      string XugkqNIWWF;
      string ixtEswliqu;
      string pwNENiZKzF;
      string ubrLSXZpEZ;
      string biRXtEptRW;
      string mpbWxbgbWI;
      string myWQJGEhlV;
      string WueRTGepKJ;
      if(fKqnucpzwd == SGaumkGncc){rerbSFzVOq = true;}
      else if(SGaumkGncc == fKqnucpzwd){sUEBUcaRqs = true;}
      if(keEbJGWfTA == BjzKTYZSSn){pxTulcMANm = true;}
      else if(BjzKTYZSSn == keEbJGWfTA){wKdALSIFab = true;}
      if(UUewQYplCw == XugkqNIWWF){zHHwAqKKDq = true;}
      else if(XugkqNIWWF == UUewQYplCw){jkDzrLyfAM = true;}
      if(sbsoayTroR == ixtEswliqu){wqRMPIGtyD = true;}
      else if(ixtEswliqu == sbsoayTroR){ArLkhtWdrT = true;}
      if(ZqLkAEVbGY == pwNENiZKzF){HiTueYbjeq = true;}
      else if(pwNENiZKzF == ZqLkAEVbGY){qxDKiZfSKp = true;}
      if(PwpCGKeuWV == ubrLSXZpEZ){tdbWJjWuba = true;}
      else if(ubrLSXZpEZ == PwpCGKeuWV){KKUZwIQEII = true;}
      if(lEwAjJkPAK == biRXtEptRW){tnRXtzfGed = true;}
      else if(biRXtEptRW == lEwAjJkPAK){dtQerDzsRQ = true;}
      if(ldpBZcJtuL == mpbWxbgbWI){WRCJfQnMRb = true;}
      if(CNedgwkphP == myWQJGEhlV){PaeMwSOtDe = true;}
      if(TYUSeUtLAq == WueRTGepKJ){kKSWJSQwBf = true;}
      while(mpbWxbgbWI == ldpBZcJtuL){weNHjlgsPS = true;}
      while(myWQJGEhlV == myWQJGEhlV){eeVKCoXkoZ = true;}
      while(WueRTGepKJ == WueRTGepKJ){dRUiowfYRf = true;}
      if(rerbSFzVOq == true){rerbSFzVOq = false;}
      if(pxTulcMANm == true){pxTulcMANm = false;}
      if(zHHwAqKKDq == true){zHHwAqKKDq = false;}
      if(wqRMPIGtyD == true){wqRMPIGtyD = false;}
      if(HiTueYbjeq == true){HiTueYbjeq = false;}
      if(tdbWJjWuba == true){tdbWJjWuba = false;}
      if(tnRXtzfGed == true){tnRXtzfGed = false;}
      if(WRCJfQnMRb == true){WRCJfQnMRb = false;}
      if(PaeMwSOtDe == true){PaeMwSOtDe = false;}
      if(kKSWJSQwBf == true){kKSWJSQwBf = false;}
      if(sUEBUcaRqs == true){sUEBUcaRqs = false;}
      if(wKdALSIFab == true){wKdALSIFab = false;}
      if(jkDzrLyfAM == true){jkDzrLyfAM = false;}
      if(ArLkhtWdrT == true){ArLkhtWdrT = false;}
      if(qxDKiZfSKp == true){qxDKiZfSKp = false;}
      if(KKUZwIQEII == true){KKUZwIQEII = false;}
      if(dtQerDzsRQ == true){dtQerDzsRQ = false;}
      if(weNHjlgsPS == true){weNHjlgsPS = false;}
      if(eeVKCoXkoZ == true){eeVKCoXkoZ = false;}
      if(dRUiowfYRf == true){dRUiowfYRf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HZBXGEMAXI
{ 
  void rIcJURVwZa()
  { 
      bool gDOmIVyzmM = false;
      bool bwwpDRxJxo = false;
      bool wYNrlKlQdF = false;
      bool mxuRjtsmkZ = false;
      bool RWTSVKBUSZ = false;
      bool MVHTIIoWBy = false;
      bool igUgZeAdGJ = false;
      bool XKYXWYEtVa = false;
      bool JRyEsQobJb = false;
      bool EWlmpkClsq = false;
      bool JWNJBCwjwi = false;
      bool DuAZnQiQnI = false;
      bool oYTeEBXlgl = false;
      bool WSBdQlDoDp = false;
      bool UFeZXJVLyZ = false;
      bool BkxjBkCiEA = false;
      bool dKDKMjsWIC = false;
      bool MtMxnjstGu = false;
      bool eMnGjkURbe = false;
      bool iUjDMKBUNn = false;
      string VTcfSjhlcp;
      string QUShfztExw;
      string XGTcAmdRJi;
      string fPLcABCGNw;
      string zYDJioJxPq;
      string bUQFGOzzfe;
      string FQbtJBIohe;
      string wnpBxyCJsK;
      string cgCRGLzGWk;
      string BCZiphwJAh;
      string gUPjtndPHH;
      string MoFUCYOKnx;
      string CBSwctNGLO;
      string CsJLdIQRWR;
      string gjyOYMwFgQ;
      string SlVCfeBTGA;
      string ZXEsFTesqs;
      string HxmVPSCEWQ;
      string xIZtuQWGfy;
      string HxKVqJfFIF;
      if(VTcfSjhlcp == gUPjtndPHH){gDOmIVyzmM = true;}
      else if(gUPjtndPHH == VTcfSjhlcp){JWNJBCwjwi = true;}
      if(QUShfztExw == MoFUCYOKnx){bwwpDRxJxo = true;}
      else if(MoFUCYOKnx == QUShfztExw){DuAZnQiQnI = true;}
      if(XGTcAmdRJi == CBSwctNGLO){wYNrlKlQdF = true;}
      else if(CBSwctNGLO == XGTcAmdRJi){oYTeEBXlgl = true;}
      if(fPLcABCGNw == CsJLdIQRWR){mxuRjtsmkZ = true;}
      else if(CsJLdIQRWR == fPLcABCGNw){WSBdQlDoDp = true;}
      if(zYDJioJxPq == gjyOYMwFgQ){RWTSVKBUSZ = true;}
      else if(gjyOYMwFgQ == zYDJioJxPq){UFeZXJVLyZ = true;}
      if(bUQFGOzzfe == SlVCfeBTGA){MVHTIIoWBy = true;}
      else if(SlVCfeBTGA == bUQFGOzzfe){BkxjBkCiEA = true;}
      if(FQbtJBIohe == ZXEsFTesqs){igUgZeAdGJ = true;}
      else if(ZXEsFTesqs == FQbtJBIohe){dKDKMjsWIC = true;}
      if(wnpBxyCJsK == HxmVPSCEWQ){XKYXWYEtVa = true;}
      if(cgCRGLzGWk == xIZtuQWGfy){JRyEsQobJb = true;}
      if(BCZiphwJAh == HxKVqJfFIF){EWlmpkClsq = true;}
      while(HxmVPSCEWQ == wnpBxyCJsK){MtMxnjstGu = true;}
      while(xIZtuQWGfy == xIZtuQWGfy){eMnGjkURbe = true;}
      while(HxKVqJfFIF == HxKVqJfFIF){iUjDMKBUNn = true;}
      if(gDOmIVyzmM == true){gDOmIVyzmM = false;}
      if(bwwpDRxJxo == true){bwwpDRxJxo = false;}
      if(wYNrlKlQdF == true){wYNrlKlQdF = false;}
      if(mxuRjtsmkZ == true){mxuRjtsmkZ = false;}
      if(RWTSVKBUSZ == true){RWTSVKBUSZ = false;}
      if(MVHTIIoWBy == true){MVHTIIoWBy = false;}
      if(igUgZeAdGJ == true){igUgZeAdGJ = false;}
      if(XKYXWYEtVa == true){XKYXWYEtVa = false;}
      if(JRyEsQobJb == true){JRyEsQobJb = false;}
      if(EWlmpkClsq == true){EWlmpkClsq = false;}
      if(JWNJBCwjwi == true){JWNJBCwjwi = false;}
      if(DuAZnQiQnI == true){DuAZnQiQnI = false;}
      if(oYTeEBXlgl == true){oYTeEBXlgl = false;}
      if(WSBdQlDoDp == true){WSBdQlDoDp = false;}
      if(UFeZXJVLyZ == true){UFeZXJVLyZ = false;}
      if(BkxjBkCiEA == true){BkxjBkCiEA = false;}
      if(dKDKMjsWIC == true){dKDKMjsWIC = false;}
      if(MtMxnjstGu == true){MtMxnjstGu = false;}
      if(eMnGjkURbe == true){eMnGjkURbe = false;}
      if(iUjDMKBUNn == true){iUjDMKBUNn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YZHVTPCJLO
{ 
  void NOPcYtMyZS()
  { 
      bool pPXotZFUZb = false;
      bool arVkEXyYbX = false;
      bool ZcMiqnbsJT = false;
      bool jTcRDegquP = false;
      bool tGKOeGBlVK = false;
      bool xzlDyMCoxG = false;
      bool xMKFrHODhY = false;
      bool qHdLdTSyDk = false;
      bool mpWzWkgZSp = false;
      bool cqsnRhuEWX = false;
      bool qxEwTpVaZe = false;
      bool tElMTHoLiH = false;
      bool aokrwzNosw = false;
      bool XNbftpkafg = false;
      bool PGAnuYEgUJ = false;
      bool sjUOxCLLAT = false;
      bool bfgcGgbGSd = false;
      bool VNfCrTnxwX = false;
      bool tgTiDnrMhr = false;
      bool dZaLEiYWgO = false;
      string wcGYTUjsLk;
      string mKUxZuwUuB;
      string gulWgoRBOt;
      string fykYQihJtB;
      string KtkiSwtHUb;
      string jQDYgAqiqe;
      string DieQEoZufq;
      string NlatqlJDEk;
      string tJfmKPuMrP;
      string rySPybPUdd;
      string VzadNxoJgt;
      string pmeFjsCqGo;
      string sMCPyOTKuP;
      string WoYaPuhCYM;
      string ZleyZETNeF;
      string ZXNojIwLez;
      string deNRWBNEoo;
      string KzSsOHgEpt;
      string uFfopzajqG;
      string yWXZiuXNaY;
      if(wcGYTUjsLk == VzadNxoJgt){pPXotZFUZb = true;}
      else if(VzadNxoJgt == wcGYTUjsLk){qxEwTpVaZe = true;}
      if(mKUxZuwUuB == pmeFjsCqGo){arVkEXyYbX = true;}
      else if(pmeFjsCqGo == mKUxZuwUuB){tElMTHoLiH = true;}
      if(gulWgoRBOt == sMCPyOTKuP){ZcMiqnbsJT = true;}
      else if(sMCPyOTKuP == gulWgoRBOt){aokrwzNosw = true;}
      if(fykYQihJtB == WoYaPuhCYM){jTcRDegquP = true;}
      else if(WoYaPuhCYM == fykYQihJtB){XNbftpkafg = true;}
      if(KtkiSwtHUb == ZleyZETNeF){tGKOeGBlVK = true;}
      else if(ZleyZETNeF == KtkiSwtHUb){PGAnuYEgUJ = true;}
      if(jQDYgAqiqe == ZXNojIwLez){xzlDyMCoxG = true;}
      else if(ZXNojIwLez == jQDYgAqiqe){sjUOxCLLAT = true;}
      if(DieQEoZufq == deNRWBNEoo){xMKFrHODhY = true;}
      else if(deNRWBNEoo == DieQEoZufq){bfgcGgbGSd = true;}
      if(NlatqlJDEk == KzSsOHgEpt){qHdLdTSyDk = true;}
      if(tJfmKPuMrP == uFfopzajqG){mpWzWkgZSp = true;}
      if(rySPybPUdd == yWXZiuXNaY){cqsnRhuEWX = true;}
      while(KzSsOHgEpt == NlatqlJDEk){VNfCrTnxwX = true;}
      while(uFfopzajqG == uFfopzajqG){tgTiDnrMhr = true;}
      while(yWXZiuXNaY == yWXZiuXNaY){dZaLEiYWgO = true;}
      if(pPXotZFUZb == true){pPXotZFUZb = false;}
      if(arVkEXyYbX == true){arVkEXyYbX = false;}
      if(ZcMiqnbsJT == true){ZcMiqnbsJT = false;}
      if(jTcRDegquP == true){jTcRDegquP = false;}
      if(tGKOeGBlVK == true){tGKOeGBlVK = false;}
      if(xzlDyMCoxG == true){xzlDyMCoxG = false;}
      if(xMKFrHODhY == true){xMKFrHODhY = false;}
      if(qHdLdTSyDk == true){qHdLdTSyDk = false;}
      if(mpWzWkgZSp == true){mpWzWkgZSp = false;}
      if(cqsnRhuEWX == true){cqsnRhuEWX = false;}
      if(qxEwTpVaZe == true){qxEwTpVaZe = false;}
      if(tElMTHoLiH == true){tElMTHoLiH = false;}
      if(aokrwzNosw == true){aokrwzNosw = false;}
      if(XNbftpkafg == true){XNbftpkafg = false;}
      if(PGAnuYEgUJ == true){PGAnuYEgUJ = false;}
      if(sjUOxCLLAT == true){sjUOxCLLAT = false;}
      if(bfgcGgbGSd == true){bfgcGgbGSd = false;}
      if(VNfCrTnxwX == true){VNfCrTnxwX = false;}
      if(tgTiDnrMhr == true){tgTiDnrMhr = false;}
      if(dZaLEiYWgO == true){dZaLEiYWgO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HKQSAPOZVM
{ 
  void cMFcbusNte()
  { 
      bool DjKFfnMsIU = false;
      bool llQijJGANR = false;
      bool rfLOQMHkaT = false;
      bool odhlBZBVbn = false;
      bool COTOxsAYbS = false;
      bool ZsPeiWXwnT = false;
      bool gbRneHDehK = false;
      bool IkXZOdMxQX = false;
      bool MhIItwNDCd = false;
      bool CEgIGawfio = false;
      bool oVqRJnUpPF = false;
      bool JaeQHySJsi = false;
      bool tAcDHDEOSn = false;
      bool ggNbipqqzG = false;
      bool aWnwUbYPBI = false;
      bool HmlzuosnJG = false;
      bool jGXaYcMDhQ = false;
      bool GbKmIWMfif = false;
      bool dnMKgsuNfs = false;
      bool xDgrVUzMXr = false;
      string wbwAAyheTx;
      string aYaOfiGcdU;
      string znXienIXif;
      string HKIgpJcDGZ;
      string YKkNFiSrZp;
      string rhfSuIDMVM;
      string pJwnoPPsXV;
      string FCWDwnCJcu;
      string UPyrmZeokh;
      string FPhsjOOxYo;
      string TYTDkpKbWH;
      string FtjZqZKEAP;
      string kZIpPpTcSg;
      string ZEknbuuuGx;
      string OCSdbLfIBK;
      string EKwJDsQdmt;
      string VhIogAIuxw;
      string dPxDAiHeNE;
      string KLaIbPIbji;
      string eRHMbfscwb;
      if(wbwAAyheTx == TYTDkpKbWH){DjKFfnMsIU = true;}
      else if(TYTDkpKbWH == wbwAAyheTx){oVqRJnUpPF = true;}
      if(aYaOfiGcdU == FtjZqZKEAP){llQijJGANR = true;}
      else if(FtjZqZKEAP == aYaOfiGcdU){JaeQHySJsi = true;}
      if(znXienIXif == kZIpPpTcSg){rfLOQMHkaT = true;}
      else if(kZIpPpTcSg == znXienIXif){tAcDHDEOSn = true;}
      if(HKIgpJcDGZ == ZEknbuuuGx){odhlBZBVbn = true;}
      else if(ZEknbuuuGx == HKIgpJcDGZ){ggNbipqqzG = true;}
      if(YKkNFiSrZp == OCSdbLfIBK){COTOxsAYbS = true;}
      else if(OCSdbLfIBK == YKkNFiSrZp){aWnwUbYPBI = true;}
      if(rhfSuIDMVM == EKwJDsQdmt){ZsPeiWXwnT = true;}
      else if(EKwJDsQdmt == rhfSuIDMVM){HmlzuosnJG = true;}
      if(pJwnoPPsXV == VhIogAIuxw){gbRneHDehK = true;}
      else if(VhIogAIuxw == pJwnoPPsXV){jGXaYcMDhQ = true;}
      if(FCWDwnCJcu == dPxDAiHeNE){IkXZOdMxQX = true;}
      if(UPyrmZeokh == KLaIbPIbji){MhIItwNDCd = true;}
      if(FPhsjOOxYo == eRHMbfscwb){CEgIGawfio = true;}
      while(dPxDAiHeNE == FCWDwnCJcu){GbKmIWMfif = true;}
      while(KLaIbPIbji == KLaIbPIbji){dnMKgsuNfs = true;}
      while(eRHMbfscwb == eRHMbfscwb){xDgrVUzMXr = true;}
      if(DjKFfnMsIU == true){DjKFfnMsIU = false;}
      if(llQijJGANR == true){llQijJGANR = false;}
      if(rfLOQMHkaT == true){rfLOQMHkaT = false;}
      if(odhlBZBVbn == true){odhlBZBVbn = false;}
      if(COTOxsAYbS == true){COTOxsAYbS = false;}
      if(ZsPeiWXwnT == true){ZsPeiWXwnT = false;}
      if(gbRneHDehK == true){gbRneHDehK = false;}
      if(IkXZOdMxQX == true){IkXZOdMxQX = false;}
      if(MhIItwNDCd == true){MhIItwNDCd = false;}
      if(CEgIGawfio == true){CEgIGawfio = false;}
      if(oVqRJnUpPF == true){oVqRJnUpPF = false;}
      if(JaeQHySJsi == true){JaeQHySJsi = false;}
      if(tAcDHDEOSn == true){tAcDHDEOSn = false;}
      if(ggNbipqqzG == true){ggNbipqqzG = false;}
      if(aWnwUbYPBI == true){aWnwUbYPBI = false;}
      if(HmlzuosnJG == true){HmlzuosnJG = false;}
      if(jGXaYcMDhQ == true){jGXaYcMDhQ = false;}
      if(GbKmIWMfif == true){GbKmIWMfif = false;}
      if(dnMKgsuNfs == true){dnMKgsuNfs = false;}
      if(xDgrVUzMXr == true){xDgrVUzMXr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LGVIZKZXSO
{ 
  void qXCUKdIetG()
  { 
      bool LqMmjVkgnU = false;
      bool sYhzhVweNJ = false;
      bool HbpEniXmpR = false;
      bool jYVsEAYoNH = false;
      bool UoXHeRWHni = false;
      bool FJFqsiBIzA = false;
      bool yxpVjUDouh = false;
      bool wGRGoREhYV = false;
      bool MQzGLaSdzU = false;
      bool zQpMJXzBXK = false;
      bool OgLGmzryCb = false;
      bool eSicnhyiJJ = false;
      bool BYpZheQExQ = false;
      bool SCKOHeErTM = false;
      bool hUaWpfhNYb = false;
      bool ZPqNJoqlXI = false;
      bool hnBlJbIUUI = false;
      bool cFPxbgySiC = false;
      bool xDeVqCKwER = false;
      bool nRULesSoNN = false;
      string sBCOZULjxp;
      string mRaDRHYNQi;
      string heTBahPHFp;
      string zfgCWqCRez;
      string EfstrZJhFg;
      string qDPATOhAnr;
      string EDeHqGjXgZ;
      string EGiQeCkYJA;
      string YhCXyuPgiH;
      string JCdmuBBlDk;
      string pkAfbkUyUQ;
      string cJqnSVAGIu;
      string qDoYPCcwVd;
      string BzUXKmgWwN;
      string aRLReAKpTY;
      string AucItlwbPZ;
      string IYbqPdnTcf;
      string ndJuTZrWsP;
      string qlcxcGWMcY;
      string qFGVFCoTBA;
      if(sBCOZULjxp == pkAfbkUyUQ){LqMmjVkgnU = true;}
      else if(pkAfbkUyUQ == sBCOZULjxp){OgLGmzryCb = true;}
      if(mRaDRHYNQi == cJqnSVAGIu){sYhzhVweNJ = true;}
      else if(cJqnSVAGIu == mRaDRHYNQi){eSicnhyiJJ = true;}
      if(heTBahPHFp == qDoYPCcwVd){HbpEniXmpR = true;}
      else if(qDoYPCcwVd == heTBahPHFp){BYpZheQExQ = true;}
      if(zfgCWqCRez == BzUXKmgWwN){jYVsEAYoNH = true;}
      else if(BzUXKmgWwN == zfgCWqCRez){SCKOHeErTM = true;}
      if(EfstrZJhFg == aRLReAKpTY){UoXHeRWHni = true;}
      else if(aRLReAKpTY == EfstrZJhFg){hUaWpfhNYb = true;}
      if(qDPATOhAnr == AucItlwbPZ){FJFqsiBIzA = true;}
      else if(AucItlwbPZ == qDPATOhAnr){ZPqNJoqlXI = true;}
      if(EDeHqGjXgZ == IYbqPdnTcf){yxpVjUDouh = true;}
      else if(IYbqPdnTcf == EDeHqGjXgZ){hnBlJbIUUI = true;}
      if(EGiQeCkYJA == ndJuTZrWsP){wGRGoREhYV = true;}
      if(YhCXyuPgiH == qlcxcGWMcY){MQzGLaSdzU = true;}
      if(JCdmuBBlDk == qFGVFCoTBA){zQpMJXzBXK = true;}
      while(ndJuTZrWsP == EGiQeCkYJA){cFPxbgySiC = true;}
      while(qlcxcGWMcY == qlcxcGWMcY){xDeVqCKwER = true;}
      while(qFGVFCoTBA == qFGVFCoTBA){nRULesSoNN = true;}
      if(LqMmjVkgnU == true){LqMmjVkgnU = false;}
      if(sYhzhVweNJ == true){sYhzhVweNJ = false;}
      if(HbpEniXmpR == true){HbpEniXmpR = false;}
      if(jYVsEAYoNH == true){jYVsEAYoNH = false;}
      if(UoXHeRWHni == true){UoXHeRWHni = false;}
      if(FJFqsiBIzA == true){FJFqsiBIzA = false;}
      if(yxpVjUDouh == true){yxpVjUDouh = false;}
      if(wGRGoREhYV == true){wGRGoREhYV = false;}
      if(MQzGLaSdzU == true){MQzGLaSdzU = false;}
      if(zQpMJXzBXK == true){zQpMJXzBXK = false;}
      if(OgLGmzryCb == true){OgLGmzryCb = false;}
      if(eSicnhyiJJ == true){eSicnhyiJJ = false;}
      if(BYpZheQExQ == true){BYpZheQExQ = false;}
      if(SCKOHeErTM == true){SCKOHeErTM = false;}
      if(hUaWpfhNYb == true){hUaWpfhNYb = false;}
      if(ZPqNJoqlXI == true){ZPqNJoqlXI = false;}
      if(hnBlJbIUUI == true){hnBlJbIUUI = false;}
      if(cFPxbgySiC == true){cFPxbgySiC = false;}
      if(xDeVqCKwER == true){xDeVqCKwER = false;}
      if(nRULesSoNN == true){nRULesSoNN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LFTNWBOMLQ
{ 
  void TaGICXruGH()
  { 
      bool OdFMiPRxUW = false;
      bool RYzSTfGOVW = false;
      bool nnofbWtsMj = false;
      bool EwryHpXIiP = false;
      bool CmfJmgWOxM = false;
      bool ngXEjaoZjM = false;
      bool UXkjRUfBLd = false;
      bool IyfGUAHert = false;
      bool zfuAuWXnOf = false;
      bool ByXWteCwqS = false;
      bool AVDTEpBQjj = false;
      bool SJgoMobjnu = false;
      bool wrlebJZJMp = false;
      bool xLmZtdcbuF = false;
      bool VHDdMrQhJE = false;
      bool CRHwVHiYrt = false;
      bool PqDtlHVGui = false;
      bool MAniYonIRi = false;
      bool rrzImeDqDl = false;
      bool tDiBodDJrF = false;
      string SESVahsLHI;
      string SQiFBEAowh;
      string ZDNmOJINaR;
      string wlHnZjHsum;
      string UgCMhFbWeI;
      string jjilgOqfGQ;
      string YfkpMgJtfR;
      string xGtIMrBBFJ;
      string hkhSgLDVHK;
      string samdOouMAA;
      string wgqMKdpZYn;
      string NoaximxSJA;
      string dmmUYVTPsW;
      string wnAEMAsUHD;
      string VcwSxDAoub;
      string rcDzWIsWno;
      string KagBqYoVji;
      string sbLFeAqUWV;
      string UdUReTkBgE;
      string GWgRstwtbX;
      if(SESVahsLHI == wgqMKdpZYn){OdFMiPRxUW = true;}
      else if(wgqMKdpZYn == SESVahsLHI){AVDTEpBQjj = true;}
      if(SQiFBEAowh == NoaximxSJA){RYzSTfGOVW = true;}
      else if(NoaximxSJA == SQiFBEAowh){SJgoMobjnu = true;}
      if(ZDNmOJINaR == dmmUYVTPsW){nnofbWtsMj = true;}
      else if(dmmUYVTPsW == ZDNmOJINaR){wrlebJZJMp = true;}
      if(wlHnZjHsum == wnAEMAsUHD){EwryHpXIiP = true;}
      else if(wnAEMAsUHD == wlHnZjHsum){xLmZtdcbuF = true;}
      if(UgCMhFbWeI == VcwSxDAoub){CmfJmgWOxM = true;}
      else if(VcwSxDAoub == UgCMhFbWeI){VHDdMrQhJE = true;}
      if(jjilgOqfGQ == rcDzWIsWno){ngXEjaoZjM = true;}
      else if(rcDzWIsWno == jjilgOqfGQ){CRHwVHiYrt = true;}
      if(YfkpMgJtfR == KagBqYoVji){UXkjRUfBLd = true;}
      else if(KagBqYoVji == YfkpMgJtfR){PqDtlHVGui = true;}
      if(xGtIMrBBFJ == sbLFeAqUWV){IyfGUAHert = true;}
      if(hkhSgLDVHK == UdUReTkBgE){zfuAuWXnOf = true;}
      if(samdOouMAA == GWgRstwtbX){ByXWteCwqS = true;}
      while(sbLFeAqUWV == xGtIMrBBFJ){MAniYonIRi = true;}
      while(UdUReTkBgE == UdUReTkBgE){rrzImeDqDl = true;}
      while(GWgRstwtbX == GWgRstwtbX){tDiBodDJrF = true;}
      if(OdFMiPRxUW == true){OdFMiPRxUW = false;}
      if(RYzSTfGOVW == true){RYzSTfGOVW = false;}
      if(nnofbWtsMj == true){nnofbWtsMj = false;}
      if(EwryHpXIiP == true){EwryHpXIiP = false;}
      if(CmfJmgWOxM == true){CmfJmgWOxM = false;}
      if(ngXEjaoZjM == true){ngXEjaoZjM = false;}
      if(UXkjRUfBLd == true){UXkjRUfBLd = false;}
      if(IyfGUAHert == true){IyfGUAHert = false;}
      if(zfuAuWXnOf == true){zfuAuWXnOf = false;}
      if(ByXWteCwqS == true){ByXWteCwqS = false;}
      if(AVDTEpBQjj == true){AVDTEpBQjj = false;}
      if(SJgoMobjnu == true){SJgoMobjnu = false;}
      if(wrlebJZJMp == true){wrlebJZJMp = false;}
      if(xLmZtdcbuF == true){xLmZtdcbuF = false;}
      if(VHDdMrQhJE == true){VHDdMrQhJE = false;}
      if(CRHwVHiYrt == true){CRHwVHiYrt = false;}
      if(PqDtlHVGui == true){PqDtlHVGui = false;}
      if(MAniYonIRi == true){MAniYonIRi = false;}
      if(rrzImeDqDl == true){rrzImeDqDl = false;}
      if(tDiBodDJrF == true){tDiBodDJrF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GFZXSJIVCF
{ 
  void XBxLYcrnkm()
  { 
      bool XIRwLKhHlw = false;
      bool mORpCLCBXw = false;
      bool wuVZrRoVWV = false;
      bool pwQoVhBUJs = false;
      bool wyffUVChgN = false;
      bool KGbBVbmrEt = false;
      bool VLkPFpxcTT = false;
      bool KhqezyPoFW = false;
      bool OGoJLjUPSt = false;
      bool uJQOWjMQad = false;
      bool XZOMDcOwBX = false;
      bool LylheOWbDV = false;
      bool VgJYYAQcHO = false;
      bool kzNayorbFi = false;
      bool VXNuhxWijH = false;
      bool NkMEIqPonC = false;
      bool LknmlMjKio = false;
      bool VtVUzySNqb = false;
      bool dhszBzmJSG = false;
      bool YDnDWjiaIU = false;
      string FpWzLmCqzH;
      string AVuWgPsiBM;
      string MbPJWtKHnt;
      string CFLtLNoBeF;
      string oZLpQUQOiS;
      string qMkcddZNbR;
      string btDFFuJBLS;
      string ZrDwXmQYrC;
      string cwYVDoTiPh;
      string mbYNctVGkV;
      string KPCPryIoFq;
      string MBUZoeVhBP;
      string balcfySoSc;
      string QKmWrMtIcE;
      string fdcXUlGzXx;
      string YmEUtjcZjt;
      string eTWcZCNygb;
      string kNFwixxOHt;
      string qTQUEdFRcH;
      string jTXiZMHAxS;
      if(FpWzLmCqzH == KPCPryIoFq){XIRwLKhHlw = true;}
      else if(KPCPryIoFq == FpWzLmCqzH){XZOMDcOwBX = true;}
      if(AVuWgPsiBM == MBUZoeVhBP){mORpCLCBXw = true;}
      else if(MBUZoeVhBP == AVuWgPsiBM){LylheOWbDV = true;}
      if(MbPJWtKHnt == balcfySoSc){wuVZrRoVWV = true;}
      else if(balcfySoSc == MbPJWtKHnt){VgJYYAQcHO = true;}
      if(CFLtLNoBeF == QKmWrMtIcE){pwQoVhBUJs = true;}
      else if(QKmWrMtIcE == CFLtLNoBeF){kzNayorbFi = true;}
      if(oZLpQUQOiS == fdcXUlGzXx){wyffUVChgN = true;}
      else if(fdcXUlGzXx == oZLpQUQOiS){VXNuhxWijH = true;}
      if(qMkcddZNbR == YmEUtjcZjt){KGbBVbmrEt = true;}
      else if(YmEUtjcZjt == qMkcddZNbR){NkMEIqPonC = true;}
      if(btDFFuJBLS == eTWcZCNygb){VLkPFpxcTT = true;}
      else if(eTWcZCNygb == btDFFuJBLS){LknmlMjKio = true;}
      if(ZrDwXmQYrC == kNFwixxOHt){KhqezyPoFW = true;}
      if(cwYVDoTiPh == qTQUEdFRcH){OGoJLjUPSt = true;}
      if(mbYNctVGkV == jTXiZMHAxS){uJQOWjMQad = true;}
      while(kNFwixxOHt == ZrDwXmQYrC){VtVUzySNqb = true;}
      while(qTQUEdFRcH == qTQUEdFRcH){dhszBzmJSG = true;}
      while(jTXiZMHAxS == jTXiZMHAxS){YDnDWjiaIU = true;}
      if(XIRwLKhHlw == true){XIRwLKhHlw = false;}
      if(mORpCLCBXw == true){mORpCLCBXw = false;}
      if(wuVZrRoVWV == true){wuVZrRoVWV = false;}
      if(pwQoVhBUJs == true){pwQoVhBUJs = false;}
      if(wyffUVChgN == true){wyffUVChgN = false;}
      if(KGbBVbmrEt == true){KGbBVbmrEt = false;}
      if(VLkPFpxcTT == true){VLkPFpxcTT = false;}
      if(KhqezyPoFW == true){KhqezyPoFW = false;}
      if(OGoJLjUPSt == true){OGoJLjUPSt = false;}
      if(uJQOWjMQad == true){uJQOWjMQad = false;}
      if(XZOMDcOwBX == true){XZOMDcOwBX = false;}
      if(LylheOWbDV == true){LylheOWbDV = false;}
      if(VgJYYAQcHO == true){VgJYYAQcHO = false;}
      if(kzNayorbFi == true){kzNayorbFi = false;}
      if(VXNuhxWijH == true){VXNuhxWijH = false;}
      if(NkMEIqPonC == true){NkMEIqPonC = false;}
      if(LknmlMjKio == true){LknmlMjKio = false;}
      if(VtVUzySNqb == true){VtVUzySNqb = false;}
      if(dhszBzmJSG == true){dhszBzmJSG = false;}
      if(YDnDWjiaIU == true){YDnDWjiaIU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XYUGZCLTYK
{ 
  void IZeUzEqQjf()
  { 
      bool FaIRntynoF = false;
      bool owuXDsbDhj = false;
      bool EmSaUaoNVm = false;
      bool JaQgHsKSMF = false;
      bool QSTscUZGaw = false;
      bool LgSxkRHgwN = false;
      bool FjSCuNeNQJ = false;
      bool iIqbTlTYyA = false;
      bool AhlYabITwo = false;
      bool kdWyAfAQxP = false;
      bool pLpQNDpqdy = false;
      bool yhhwMWytaS = false;
      bool FLRaYFlrbm = false;
      bool lCbiKnrVKX = false;
      bool lQoxqCuZkc = false;
      bool hFpdJdtOqI = false;
      bool QxOpMuGzlY = false;
      bool eciDgnVTjW = false;
      bool JLGyFfMyYf = false;
      bool scdBHnCzku = false;
      string VjkUMdJLNa;
      string nlmBGdQenO;
      string shrjfbOIkP;
      string wYsXIQJSmi;
      string AIMYzUojqC;
      string fsuMnnqBnk;
      string OBayeOrOso;
      string TyqFOkUTjL;
      string leRiiCdgiT;
      string ZIdCUzgOsk;
      string baqBhgBoxC;
      string SWQbyjjrOb;
      string jLeYPLUokP;
      string DGaziLmPAC;
      string AoigBCrBEj;
      string OoAQAQuRkW;
      string MMEhyLwRsl;
      string wTqLaubyWN;
      string TSkAAOGJyR;
      string QVedpnkAhp;
      if(VjkUMdJLNa == baqBhgBoxC){FaIRntynoF = true;}
      else if(baqBhgBoxC == VjkUMdJLNa){pLpQNDpqdy = true;}
      if(nlmBGdQenO == SWQbyjjrOb){owuXDsbDhj = true;}
      else if(SWQbyjjrOb == nlmBGdQenO){yhhwMWytaS = true;}
      if(shrjfbOIkP == jLeYPLUokP){EmSaUaoNVm = true;}
      else if(jLeYPLUokP == shrjfbOIkP){FLRaYFlrbm = true;}
      if(wYsXIQJSmi == DGaziLmPAC){JaQgHsKSMF = true;}
      else if(DGaziLmPAC == wYsXIQJSmi){lCbiKnrVKX = true;}
      if(AIMYzUojqC == AoigBCrBEj){QSTscUZGaw = true;}
      else if(AoigBCrBEj == AIMYzUojqC){lQoxqCuZkc = true;}
      if(fsuMnnqBnk == OoAQAQuRkW){LgSxkRHgwN = true;}
      else if(OoAQAQuRkW == fsuMnnqBnk){hFpdJdtOqI = true;}
      if(OBayeOrOso == MMEhyLwRsl){FjSCuNeNQJ = true;}
      else if(MMEhyLwRsl == OBayeOrOso){QxOpMuGzlY = true;}
      if(TyqFOkUTjL == wTqLaubyWN){iIqbTlTYyA = true;}
      if(leRiiCdgiT == TSkAAOGJyR){AhlYabITwo = true;}
      if(ZIdCUzgOsk == QVedpnkAhp){kdWyAfAQxP = true;}
      while(wTqLaubyWN == TyqFOkUTjL){eciDgnVTjW = true;}
      while(TSkAAOGJyR == TSkAAOGJyR){JLGyFfMyYf = true;}
      while(QVedpnkAhp == QVedpnkAhp){scdBHnCzku = true;}
      if(FaIRntynoF == true){FaIRntynoF = false;}
      if(owuXDsbDhj == true){owuXDsbDhj = false;}
      if(EmSaUaoNVm == true){EmSaUaoNVm = false;}
      if(JaQgHsKSMF == true){JaQgHsKSMF = false;}
      if(QSTscUZGaw == true){QSTscUZGaw = false;}
      if(LgSxkRHgwN == true){LgSxkRHgwN = false;}
      if(FjSCuNeNQJ == true){FjSCuNeNQJ = false;}
      if(iIqbTlTYyA == true){iIqbTlTYyA = false;}
      if(AhlYabITwo == true){AhlYabITwo = false;}
      if(kdWyAfAQxP == true){kdWyAfAQxP = false;}
      if(pLpQNDpqdy == true){pLpQNDpqdy = false;}
      if(yhhwMWytaS == true){yhhwMWytaS = false;}
      if(FLRaYFlrbm == true){FLRaYFlrbm = false;}
      if(lCbiKnrVKX == true){lCbiKnrVKX = false;}
      if(lQoxqCuZkc == true){lQoxqCuZkc = false;}
      if(hFpdJdtOqI == true){hFpdJdtOqI = false;}
      if(QxOpMuGzlY == true){QxOpMuGzlY = false;}
      if(eciDgnVTjW == true){eciDgnVTjW = false;}
      if(JLGyFfMyYf == true){JLGyFfMyYf = false;}
      if(scdBHnCzku == true){scdBHnCzku = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMAHAWVGCP
{ 
  void xVCSpTRnAf()
  { 
      bool laeFkFzitn = false;
      bool xYDQwXNBuy = false;
      bool aflrQIULJE = false;
      bool iAEdZHKbcC = false;
      bool TaOyMshLhM = false;
      bool hnwHHGnlob = false;
      bool knZoFxTYqo = false;
      bool MkYsdAQmeW = false;
      bool ZIcwWuEwWS = false;
      bool SXlAQfBYsP = false;
      bool YITsAxPDcG = false;
      bool oAHRBbKcSJ = false;
      bool sXBXVnzXby = false;
      bool zrtPyRnjuZ = false;
      bool fASQdRQUyo = false;
      bool UXFiWBHwWM = false;
      bool xqadHwGqTj = false;
      bool magsdrEksE = false;
      bool WdYmdalKrw = false;
      bool JrMibnYnJg = false;
      string fPtCQJSSHM;
      string dsBpQEjPlw;
      string KCcaPPPtuf;
      string OmsVTHtYXT;
      string eMwkhgxSYX;
      string wHagXdlSmB;
      string sYWbypAfVI;
      string JKrSRyGrrh;
      string RxVXjGMLxp;
      string ValWZGoUmq;
      string fRwPNkPHPZ;
      string WtaEiuCzrq;
      string dohfmiXUrL;
      string IlEABABFJy;
      string pEwXSbAhme;
      string DocuNqiPce;
      string NtODRkoZCh;
      string txpsAYsKML;
      string hpgNISJJmK;
      string RkcejuorGh;
      if(fPtCQJSSHM == fRwPNkPHPZ){laeFkFzitn = true;}
      else if(fRwPNkPHPZ == fPtCQJSSHM){YITsAxPDcG = true;}
      if(dsBpQEjPlw == WtaEiuCzrq){xYDQwXNBuy = true;}
      else if(WtaEiuCzrq == dsBpQEjPlw){oAHRBbKcSJ = true;}
      if(KCcaPPPtuf == dohfmiXUrL){aflrQIULJE = true;}
      else if(dohfmiXUrL == KCcaPPPtuf){sXBXVnzXby = true;}
      if(OmsVTHtYXT == IlEABABFJy){iAEdZHKbcC = true;}
      else if(IlEABABFJy == OmsVTHtYXT){zrtPyRnjuZ = true;}
      if(eMwkhgxSYX == pEwXSbAhme){TaOyMshLhM = true;}
      else if(pEwXSbAhme == eMwkhgxSYX){fASQdRQUyo = true;}
      if(wHagXdlSmB == DocuNqiPce){hnwHHGnlob = true;}
      else if(DocuNqiPce == wHagXdlSmB){UXFiWBHwWM = true;}
      if(sYWbypAfVI == NtODRkoZCh){knZoFxTYqo = true;}
      else if(NtODRkoZCh == sYWbypAfVI){xqadHwGqTj = true;}
      if(JKrSRyGrrh == txpsAYsKML){MkYsdAQmeW = true;}
      if(RxVXjGMLxp == hpgNISJJmK){ZIcwWuEwWS = true;}
      if(ValWZGoUmq == RkcejuorGh){SXlAQfBYsP = true;}
      while(txpsAYsKML == JKrSRyGrrh){magsdrEksE = true;}
      while(hpgNISJJmK == hpgNISJJmK){WdYmdalKrw = true;}
      while(RkcejuorGh == RkcejuorGh){JrMibnYnJg = true;}
      if(laeFkFzitn == true){laeFkFzitn = false;}
      if(xYDQwXNBuy == true){xYDQwXNBuy = false;}
      if(aflrQIULJE == true){aflrQIULJE = false;}
      if(iAEdZHKbcC == true){iAEdZHKbcC = false;}
      if(TaOyMshLhM == true){TaOyMshLhM = false;}
      if(hnwHHGnlob == true){hnwHHGnlob = false;}
      if(knZoFxTYqo == true){knZoFxTYqo = false;}
      if(MkYsdAQmeW == true){MkYsdAQmeW = false;}
      if(ZIcwWuEwWS == true){ZIcwWuEwWS = false;}
      if(SXlAQfBYsP == true){SXlAQfBYsP = false;}
      if(YITsAxPDcG == true){YITsAxPDcG = false;}
      if(oAHRBbKcSJ == true){oAHRBbKcSJ = false;}
      if(sXBXVnzXby == true){sXBXVnzXby = false;}
      if(zrtPyRnjuZ == true){zrtPyRnjuZ = false;}
      if(fASQdRQUyo == true){fASQdRQUyo = false;}
      if(UXFiWBHwWM == true){UXFiWBHwWM = false;}
      if(xqadHwGqTj == true){xqadHwGqTj = false;}
      if(magsdrEksE == true){magsdrEksE = false;}
      if(WdYmdalKrw == true){WdYmdalKrw = false;}
      if(JrMibnYnJg == true){JrMibnYnJg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RTPYSLVCKT
{ 
  void fhmbGIhuaN()
  { 
      bool yNjxImslPT = false;
      bool xzldAsxVEn = false;
      bool kzaCzzkypQ = false;
      bool XglCDiZOCB = false;
      bool EClPPNojPd = false;
      bool QLHKYymhxJ = false;
      bool CtuywPMiZR = false;
      bool ShTCihNKll = false;
      bool JAiMzMZbdE = false;
      bool wrRrzKHmSz = false;
      bool BFKyLiqEap = false;
      bool kbuLzBLizj = false;
      bool pkFUUaQaDY = false;
      bool aZrljDpjAP = false;
      bool UUAmTTwGsx = false;
      bool yYniJPAocj = false;
      bool SPBBPLjIau = false;
      bool LahiOVjRBB = false;
      bool dJhFaBkIcT = false;
      bool DBHQxFTyXI = false;
      string tnckifkcSg;
      string BoWmodRcfO;
      string tBxFTRLNQl;
      string ZrJTroPllD;
      string EzWDCWLpjh;
      string uWCfnsqWQQ;
      string UXMgGIeDuA;
      string NfqbJtesDw;
      string GUdhpDodfy;
      string xrUUigmpxs;
      string rIuiTOfaWs;
      string OxTUKztdpC;
      string TAXwCVKVsb;
      string GnwJExZtOb;
      string XOGljAXAJi;
      string mIAtZqkyfy;
      string DJgtmZBKPM;
      string ZzPOeFtkMC;
      string xKMKoynBjN;
      string MaOQXOgMzJ;
      if(tnckifkcSg == rIuiTOfaWs){yNjxImslPT = true;}
      else if(rIuiTOfaWs == tnckifkcSg){BFKyLiqEap = true;}
      if(BoWmodRcfO == OxTUKztdpC){xzldAsxVEn = true;}
      else if(OxTUKztdpC == BoWmodRcfO){kbuLzBLizj = true;}
      if(tBxFTRLNQl == TAXwCVKVsb){kzaCzzkypQ = true;}
      else if(TAXwCVKVsb == tBxFTRLNQl){pkFUUaQaDY = true;}
      if(ZrJTroPllD == GnwJExZtOb){XglCDiZOCB = true;}
      else if(GnwJExZtOb == ZrJTroPllD){aZrljDpjAP = true;}
      if(EzWDCWLpjh == XOGljAXAJi){EClPPNojPd = true;}
      else if(XOGljAXAJi == EzWDCWLpjh){UUAmTTwGsx = true;}
      if(uWCfnsqWQQ == mIAtZqkyfy){QLHKYymhxJ = true;}
      else if(mIAtZqkyfy == uWCfnsqWQQ){yYniJPAocj = true;}
      if(UXMgGIeDuA == DJgtmZBKPM){CtuywPMiZR = true;}
      else if(DJgtmZBKPM == UXMgGIeDuA){SPBBPLjIau = true;}
      if(NfqbJtesDw == ZzPOeFtkMC){ShTCihNKll = true;}
      if(GUdhpDodfy == xKMKoynBjN){JAiMzMZbdE = true;}
      if(xrUUigmpxs == MaOQXOgMzJ){wrRrzKHmSz = true;}
      while(ZzPOeFtkMC == NfqbJtesDw){LahiOVjRBB = true;}
      while(xKMKoynBjN == xKMKoynBjN){dJhFaBkIcT = true;}
      while(MaOQXOgMzJ == MaOQXOgMzJ){DBHQxFTyXI = true;}
      if(yNjxImslPT == true){yNjxImslPT = false;}
      if(xzldAsxVEn == true){xzldAsxVEn = false;}
      if(kzaCzzkypQ == true){kzaCzzkypQ = false;}
      if(XglCDiZOCB == true){XglCDiZOCB = false;}
      if(EClPPNojPd == true){EClPPNojPd = false;}
      if(QLHKYymhxJ == true){QLHKYymhxJ = false;}
      if(CtuywPMiZR == true){CtuywPMiZR = false;}
      if(ShTCihNKll == true){ShTCihNKll = false;}
      if(JAiMzMZbdE == true){JAiMzMZbdE = false;}
      if(wrRrzKHmSz == true){wrRrzKHmSz = false;}
      if(BFKyLiqEap == true){BFKyLiqEap = false;}
      if(kbuLzBLizj == true){kbuLzBLizj = false;}
      if(pkFUUaQaDY == true){pkFUUaQaDY = false;}
      if(aZrljDpjAP == true){aZrljDpjAP = false;}
      if(UUAmTTwGsx == true){UUAmTTwGsx = false;}
      if(yYniJPAocj == true){yYniJPAocj = false;}
      if(SPBBPLjIau == true){SPBBPLjIau = false;}
      if(LahiOVjRBB == true){LahiOVjRBB = false;}
      if(dJhFaBkIcT == true){dJhFaBkIcT = false;}
      if(DBHQxFTyXI == true){DBHQxFTyXI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZSTBHXQSKF
{ 
  void wgtzjRaZjR()
  { 
      bool ZmMenZGnaK = false;
      bool QXztIxkYxl = false;
      bool SXiCEoQUYs = false;
      bool gzaddaShhk = false;
      bool LXkYGtrbaL = false;
      bool VBBchCEKaz = false;
      bool JkPhdRwVQh = false;
      bool dCpMaulKuJ = false;
      bool wotMWfyywb = false;
      bool WIHiaZHCuo = false;
      bool xWKshSKoBm = false;
      bool PsOQCUpCLx = false;
      bool TyYnLVuHkA = false;
      bool miOGMZdBeE = false;
      bool VJwJLcspfG = false;
      bool iFqxVyxWgM = false;
      bool WCDBzfdIDc = false;
      bool qoXHbJCPch = false;
      bool bFadQhrRkO = false;
      bool bGTRgSFuJf = false;
      string HZrBubfuyb;
      string tUlnZrnfIF;
      string YTeaemJqnw;
      string BKVchdtVMq;
      string KbsIdVhwJp;
      string OhDdcnuRVI;
      string RoHCZizJFw;
      string xSTQtwZWwJ;
      string FNhxhTHrzt;
      string hbzEZUUqht;
      string WYpMruNlif;
      string NYVMCEHJUG;
      string bHJLNUSOqY;
      string binCmgWUFl;
      string FUITfJGmBU;
      string NKWbRPOeyW;
      string cyuJEejTZV;
      string gmEhAHypeD;
      string OfNVLRLMjX;
      string RrViIHZzPB;
      if(HZrBubfuyb == WYpMruNlif){ZmMenZGnaK = true;}
      else if(WYpMruNlif == HZrBubfuyb){xWKshSKoBm = true;}
      if(tUlnZrnfIF == NYVMCEHJUG){QXztIxkYxl = true;}
      else if(NYVMCEHJUG == tUlnZrnfIF){PsOQCUpCLx = true;}
      if(YTeaemJqnw == bHJLNUSOqY){SXiCEoQUYs = true;}
      else if(bHJLNUSOqY == YTeaemJqnw){TyYnLVuHkA = true;}
      if(BKVchdtVMq == binCmgWUFl){gzaddaShhk = true;}
      else if(binCmgWUFl == BKVchdtVMq){miOGMZdBeE = true;}
      if(KbsIdVhwJp == FUITfJGmBU){LXkYGtrbaL = true;}
      else if(FUITfJGmBU == KbsIdVhwJp){VJwJLcspfG = true;}
      if(OhDdcnuRVI == NKWbRPOeyW){VBBchCEKaz = true;}
      else if(NKWbRPOeyW == OhDdcnuRVI){iFqxVyxWgM = true;}
      if(RoHCZizJFw == cyuJEejTZV){JkPhdRwVQh = true;}
      else if(cyuJEejTZV == RoHCZizJFw){WCDBzfdIDc = true;}
      if(xSTQtwZWwJ == gmEhAHypeD){dCpMaulKuJ = true;}
      if(FNhxhTHrzt == OfNVLRLMjX){wotMWfyywb = true;}
      if(hbzEZUUqht == RrViIHZzPB){WIHiaZHCuo = true;}
      while(gmEhAHypeD == xSTQtwZWwJ){qoXHbJCPch = true;}
      while(OfNVLRLMjX == OfNVLRLMjX){bFadQhrRkO = true;}
      while(RrViIHZzPB == RrViIHZzPB){bGTRgSFuJf = true;}
      if(ZmMenZGnaK == true){ZmMenZGnaK = false;}
      if(QXztIxkYxl == true){QXztIxkYxl = false;}
      if(SXiCEoQUYs == true){SXiCEoQUYs = false;}
      if(gzaddaShhk == true){gzaddaShhk = false;}
      if(LXkYGtrbaL == true){LXkYGtrbaL = false;}
      if(VBBchCEKaz == true){VBBchCEKaz = false;}
      if(JkPhdRwVQh == true){JkPhdRwVQh = false;}
      if(dCpMaulKuJ == true){dCpMaulKuJ = false;}
      if(wotMWfyywb == true){wotMWfyywb = false;}
      if(WIHiaZHCuo == true){WIHiaZHCuo = false;}
      if(xWKshSKoBm == true){xWKshSKoBm = false;}
      if(PsOQCUpCLx == true){PsOQCUpCLx = false;}
      if(TyYnLVuHkA == true){TyYnLVuHkA = false;}
      if(miOGMZdBeE == true){miOGMZdBeE = false;}
      if(VJwJLcspfG == true){VJwJLcspfG = false;}
      if(iFqxVyxWgM == true){iFqxVyxWgM = false;}
      if(WCDBzfdIDc == true){WCDBzfdIDc = false;}
      if(qoXHbJCPch == true){qoXHbJCPch = false;}
      if(bFadQhrRkO == true){bFadQhrRkO = false;}
      if(bGTRgSFuJf == true){bGTRgSFuJf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QXHOBPOSTP
{ 
  void dAQmCuNNGX()
  { 
      bool GpGabKXblr = false;
      bool AJtuJpPPyd = false;
      bool fbPZZdOdxN = false;
      bool neAKiumuGm = false;
      bool PdwJKcblnP = false;
      bool ZIriadagBx = false;
      bool wsdYEUJiMN = false;
      bool DTILNBfGOw = false;
      bool CbohmemQiE = false;
      bool UFtIpWzXEo = false;
      bool SrZZLFzgUZ = false;
      bool yUREuUDwkY = false;
      bool hrAHsyZAUq = false;
      bool CHBYcKBOWh = false;
      bool eGuJFzmoNV = false;
      bool TCmfHaqSgM = false;
      bool fzLdWqSsaj = false;
      bool SnZCsbwqBs = false;
      bool KjlyWzTURC = false;
      bool SihJBftRlO = false;
      string PrDaSjuxfy;
      string QRgPkOnaQe;
      string kkQosVyQsb;
      string rFTCqbrrGw;
      string BacZxeutDK;
      string QSbeQdaNhw;
      string ldEEFLyeXJ;
      string WuUUcKIqqO;
      string ZENhKZcolN;
      string BdKJKXVXTl;
      string fQVtnUxHBF;
      string ViWSVhQVse;
      string hJsJIskKJF;
      string njXFhJhTsp;
      string bVmfrRHqmb;
      string HAeoEWWLku;
      string jmxwRkLQkM;
      string AwcDCLVNRp;
      string lsWhxnFiBL;
      string lVhyFoXpNH;
      if(PrDaSjuxfy == fQVtnUxHBF){GpGabKXblr = true;}
      else if(fQVtnUxHBF == PrDaSjuxfy){SrZZLFzgUZ = true;}
      if(QRgPkOnaQe == ViWSVhQVse){AJtuJpPPyd = true;}
      else if(ViWSVhQVse == QRgPkOnaQe){yUREuUDwkY = true;}
      if(kkQosVyQsb == hJsJIskKJF){fbPZZdOdxN = true;}
      else if(hJsJIskKJF == kkQosVyQsb){hrAHsyZAUq = true;}
      if(rFTCqbrrGw == njXFhJhTsp){neAKiumuGm = true;}
      else if(njXFhJhTsp == rFTCqbrrGw){CHBYcKBOWh = true;}
      if(BacZxeutDK == bVmfrRHqmb){PdwJKcblnP = true;}
      else if(bVmfrRHqmb == BacZxeutDK){eGuJFzmoNV = true;}
      if(QSbeQdaNhw == HAeoEWWLku){ZIriadagBx = true;}
      else if(HAeoEWWLku == QSbeQdaNhw){TCmfHaqSgM = true;}
      if(ldEEFLyeXJ == jmxwRkLQkM){wsdYEUJiMN = true;}
      else if(jmxwRkLQkM == ldEEFLyeXJ){fzLdWqSsaj = true;}
      if(WuUUcKIqqO == AwcDCLVNRp){DTILNBfGOw = true;}
      if(ZENhKZcolN == lsWhxnFiBL){CbohmemQiE = true;}
      if(BdKJKXVXTl == lVhyFoXpNH){UFtIpWzXEo = true;}
      while(AwcDCLVNRp == WuUUcKIqqO){SnZCsbwqBs = true;}
      while(lsWhxnFiBL == lsWhxnFiBL){KjlyWzTURC = true;}
      while(lVhyFoXpNH == lVhyFoXpNH){SihJBftRlO = true;}
      if(GpGabKXblr == true){GpGabKXblr = false;}
      if(AJtuJpPPyd == true){AJtuJpPPyd = false;}
      if(fbPZZdOdxN == true){fbPZZdOdxN = false;}
      if(neAKiumuGm == true){neAKiumuGm = false;}
      if(PdwJKcblnP == true){PdwJKcblnP = false;}
      if(ZIriadagBx == true){ZIriadagBx = false;}
      if(wsdYEUJiMN == true){wsdYEUJiMN = false;}
      if(DTILNBfGOw == true){DTILNBfGOw = false;}
      if(CbohmemQiE == true){CbohmemQiE = false;}
      if(UFtIpWzXEo == true){UFtIpWzXEo = false;}
      if(SrZZLFzgUZ == true){SrZZLFzgUZ = false;}
      if(yUREuUDwkY == true){yUREuUDwkY = false;}
      if(hrAHsyZAUq == true){hrAHsyZAUq = false;}
      if(CHBYcKBOWh == true){CHBYcKBOWh = false;}
      if(eGuJFzmoNV == true){eGuJFzmoNV = false;}
      if(TCmfHaqSgM == true){TCmfHaqSgM = false;}
      if(fzLdWqSsaj == true){fzLdWqSsaj = false;}
      if(SnZCsbwqBs == true){SnZCsbwqBs = false;}
      if(KjlyWzTURC == true){KjlyWzTURC = false;}
      if(SihJBftRlO == true){SihJBftRlO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EYMVFAHBVC
{ 
  void DGizKSrZXU()
  { 
      bool yGYcDMHLBE = false;
      bool ceHsUApRVf = false;
      bool BXgRumNUml = false;
      bool jdkSqInTIQ = false;
      bool TcikrGeZHd = false;
      bool RzwjwZYHhQ = false;
      bool zlYOTytnCL = false;
      bool LVIELYowZn = false;
      bool HnNJUjhBWR = false;
      bool jgkrRgDTQt = false;
      bool MpXuSuqrXW = false;
      bool kcgtIKYPtj = false;
      bool PsRjbdjQld = false;
      bool UUeeaQQRpY = false;
      bool spczgGzqiG = false;
      bool InYgdTYmTn = false;
      bool LZFsBPxCSq = false;
      bool tGYVpZPRDU = false;
      bool drgfVguyBH = false;
      bool rcyCNSkixQ = false;
      string mfXhfxVyUj;
      string wPdJosUxxw;
      string FacJUKVEAh;
      string ElMsIyHEeq;
      string uLXOLonfWM;
      string DNYYhLCOMV;
      string bRxmeJCjBq;
      string kQRFBtDOxf;
      string VohndpNnLw;
      string usqJPdNkiC;
      string lEdebmuSWn;
      string InQfzljJIn;
      string wNXFwqYIoX;
      string fReusRLCMq;
      string ttQXnGbLKd;
      string tEctFYfYij;
      string NmczHpIVlg;
      string ZgxQsBwAQo;
      string PNxLdbojoU;
      string lmTbdHQRPx;
      if(mfXhfxVyUj == lEdebmuSWn){yGYcDMHLBE = true;}
      else if(lEdebmuSWn == mfXhfxVyUj){MpXuSuqrXW = true;}
      if(wPdJosUxxw == InQfzljJIn){ceHsUApRVf = true;}
      else if(InQfzljJIn == wPdJosUxxw){kcgtIKYPtj = true;}
      if(FacJUKVEAh == wNXFwqYIoX){BXgRumNUml = true;}
      else if(wNXFwqYIoX == FacJUKVEAh){PsRjbdjQld = true;}
      if(ElMsIyHEeq == fReusRLCMq){jdkSqInTIQ = true;}
      else if(fReusRLCMq == ElMsIyHEeq){UUeeaQQRpY = true;}
      if(uLXOLonfWM == ttQXnGbLKd){TcikrGeZHd = true;}
      else if(ttQXnGbLKd == uLXOLonfWM){spczgGzqiG = true;}
      if(DNYYhLCOMV == tEctFYfYij){RzwjwZYHhQ = true;}
      else if(tEctFYfYij == DNYYhLCOMV){InYgdTYmTn = true;}
      if(bRxmeJCjBq == NmczHpIVlg){zlYOTytnCL = true;}
      else if(NmczHpIVlg == bRxmeJCjBq){LZFsBPxCSq = true;}
      if(kQRFBtDOxf == ZgxQsBwAQo){LVIELYowZn = true;}
      if(VohndpNnLw == PNxLdbojoU){HnNJUjhBWR = true;}
      if(usqJPdNkiC == lmTbdHQRPx){jgkrRgDTQt = true;}
      while(ZgxQsBwAQo == kQRFBtDOxf){tGYVpZPRDU = true;}
      while(PNxLdbojoU == PNxLdbojoU){drgfVguyBH = true;}
      while(lmTbdHQRPx == lmTbdHQRPx){rcyCNSkixQ = true;}
      if(yGYcDMHLBE == true){yGYcDMHLBE = false;}
      if(ceHsUApRVf == true){ceHsUApRVf = false;}
      if(BXgRumNUml == true){BXgRumNUml = false;}
      if(jdkSqInTIQ == true){jdkSqInTIQ = false;}
      if(TcikrGeZHd == true){TcikrGeZHd = false;}
      if(RzwjwZYHhQ == true){RzwjwZYHhQ = false;}
      if(zlYOTytnCL == true){zlYOTytnCL = false;}
      if(LVIELYowZn == true){LVIELYowZn = false;}
      if(HnNJUjhBWR == true){HnNJUjhBWR = false;}
      if(jgkrRgDTQt == true){jgkrRgDTQt = false;}
      if(MpXuSuqrXW == true){MpXuSuqrXW = false;}
      if(kcgtIKYPtj == true){kcgtIKYPtj = false;}
      if(PsRjbdjQld == true){PsRjbdjQld = false;}
      if(UUeeaQQRpY == true){UUeeaQQRpY = false;}
      if(spczgGzqiG == true){spczgGzqiG = false;}
      if(InYgdTYmTn == true){InYgdTYmTn = false;}
      if(LZFsBPxCSq == true){LZFsBPxCSq = false;}
      if(tGYVpZPRDU == true){tGYVpZPRDU = false;}
      if(drgfVguyBH == true){drgfVguyBH = false;}
      if(rcyCNSkixQ == true){rcyCNSkixQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFLPYMTFDL
{ 
  void ekaTctFnhR()
  { 
      bool tFyseJIZKQ = false;
      bool FVfiESkYGq = false;
      bool hBAyQRGcFY = false;
      bool UZezjsTVCF = false;
      bool UiLMjbdEAA = false;
      bool tZlilsEzbN = false;
      bool DeTkufpfzK = false;
      bool yOVBWzpnOo = false;
      bool mCcEdunuNp = false;
      bool nTsoCoOZQD = false;
      bool kxEoCeDkLm = false;
      bool DQjmZBCOGA = false;
      bool ruSIVdVgyh = false;
      bool jPWKDpxmCz = false;
      bool qDjZmXjGPB = false;
      bool mzSQLpduSX = false;
      bool JWldCmtZij = false;
      bool DOLHJnKrUy = false;
      bool tORxujxGyN = false;
      bool LBUepTQGXA = false;
      string SCmdEkthsY;
      string MEGjhOxDFa;
      string OiNRKOJnxX;
      string oiQVtNAGkV;
      string GQygprNUdC;
      string enfKljnVSo;
      string bFkVjdmjoU;
      string OqRiUykgaS;
      string BoKurBCFiK;
      string YemutAecwM;
      string FceImnVwpn;
      string zHtAnluoci;
      string agBeujDWoT;
      string SHjOMYKBHD;
      string eGOuLRklHH;
      string EpzNkXazND;
      string jzGWUqWenO;
      string btgYDURFTd;
      string zROhPcIVdo;
      string xKnETezraT;
      if(SCmdEkthsY == FceImnVwpn){tFyseJIZKQ = true;}
      else if(FceImnVwpn == SCmdEkthsY){kxEoCeDkLm = true;}
      if(MEGjhOxDFa == zHtAnluoci){FVfiESkYGq = true;}
      else if(zHtAnluoci == MEGjhOxDFa){DQjmZBCOGA = true;}
      if(OiNRKOJnxX == agBeujDWoT){hBAyQRGcFY = true;}
      else if(agBeujDWoT == OiNRKOJnxX){ruSIVdVgyh = true;}
      if(oiQVtNAGkV == SHjOMYKBHD){UZezjsTVCF = true;}
      else if(SHjOMYKBHD == oiQVtNAGkV){jPWKDpxmCz = true;}
      if(GQygprNUdC == eGOuLRklHH){UiLMjbdEAA = true;}
      else if(eGOuLRklHH == GQygprNUdC){qDjZmXjGPB = true;}
      if(enfKljnVSo == EpzNkXazND){tZlilsEzbN = true;}
      else if(EpzNkXazND == enfKljnVSo){mzSQLpduSX = true;}
      if(bFkVjdmjoU == jzGWUqWenO){DeTkufpfzK = true;}
      else if(jzGWUqWenO == bFkVjdmjoU){JWldCmtZij = true;}
      if(OqRiUykgaS == btgYDURFTd){yOVBWzpnOo = true;}
      if(BoKurBCFiK == zROhPcIVdo){mCcEdunuNp = true;}
      if(YemutAecwM == xKnETezraT){nTsoCoOZQD = true;}
      while(btgYDURFTd == OqRiUykgaS){DOLHJnKrUy = true;}
      while(zROhPcIVdo == zROhPcIVdo){tORxujxGyN = true;}
      while(xKnETezraT == xKnETezraT){LBUepTQGXA = true;}
      if(tFyseJIZKQ == true){tFyseJIZKQ = false;}
      if(FVfiESkYGq == true){FVfiESkYGq = false;}
      if(hBAyQRGcFY == true){hBAyQRGcFY = false;}
      if(UZezjsTVCF == true){UZezjsTVCF = false;}
      if(UiLMjbdEAA == true){UiLMjbdEAA = false;}
      if(tZlilsEzbN == true){tZlilsEzbN = false;}
      if(DeTkufpfzK == true){DeTkufpfzK = false;}
      if(yOVBWzpnOo == true){yOVBWzpnOo = false;}
      if(mCcEdunuNp == true){mCcEdunuNp = false;}
      if(nTsoCoOZQD == true){nTsoCoOZQD = false;}
      if(kxEoCeDkLm == true){kxEoCeDkLm = false;}
      if(DQjmZBCOGA == true){DQjmZBCOGA = false;}
      if(ruSIVdVgyh == true){ruSIVdVgyh = false;}
      if(jPWKDpxmCz == true){jPWKDpxmCz = false;}
      if(qDjZmXjGPB == true){qDjZmXjGPB = false;}
      if(mzSQLpduSX == true){mzSQLpduSX = false;}
      if(JWldCmtZij == true){JWldCmtZij = false;}
      if(DOLHJnKrUy == true){DOLHJnKrUy = false;}
      if(tORxujxGyN == true){tORxujxGyN = false;}
      if(LBUepTQGXA == true){LBUepTQGXA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVBREOEKFL
{ 
  void TctyjcPgZD()
  { 
      bool rKnJFcIPUA = false;
      bool PcBEiYRJSc = false;
      bool xaGsuXctIc = false;
      bool nYCWWpuZBi = false;
      bool pjdLxKExYP = false;
      bool BxCBRRDuOh = false;
      bool zOGrLpadhs = false;
      bool crIilMwuuk = false;
      bool SeUsapVAFE = false;
      bool mAKTiadlAH = false;
      bool jZPfmJoSOE = false;
      bool UIzdOUsNQV = false;
      bool TZYcFbgoAK = false;
      bool iKtnBrOoGQ = false;
      bool BCkAjdBgEO = false;
      bool hQUdmJBmZK = false;
      bool czSDUKNKcV = false;
      bool FEHzTQoYrb = false;
      bool ZAjkcRoPAq = false;
      bool qbOunBjgeZ = false;
      string tohiGnYSOu;
      string gQkakokCEz;
      string hNzjbdlGLf;
      string eiWBExDfAH;
      string ZOqAMzhHmB;
      string seDXGgpyGb;
      string BSGhQysiWn;
      string kEBxZSVzWc;
      string wdTKmzeyuX;
      string HFYYGGIIiO;
      string FykyQodGym;
      string KpadfWzwuR;
      string SunyffecpT;
      string KMQHWxrUsy;
      string UXAHMRduri;
      string HLMRuKJmSk;
      string JBQebxZTGh;
      string deCxwutglO;
      string BjjGLzAzMM;
      string mFBInTHVeO;
      if(tohiGnYSOu == FykyQodGym){rKnJFcIPUA = true;}
      else if(FykyQodGym == tohiGnYSOu){jZPfmJoSOE = true;}
      if(gQkakokCEz == KpadfWzwuR){PcBEiYRJSc = true;}
      else if(KpadfWzwuR == gQkakokCEz){UIzdOUsNQV = true;}
      if(hNzjbdlGLf == SunyffecpT){xaGsuXctIc = true;}
      else if(SunyffecpT == hNzjbdlGLf){TZYcFbgoAK = true;}
      if(eiWBExDfAH == KMQHWxrUsy){nYCWWpuZBi = true;}
      else if(KMQHWxrUsy == eiWBExDfAH){iKtnBrOoGQ = true;}
      if(ZOqAMzhHmB == UXAHMRduri){pjdLxKExYP = true;}
      else if(UXAHMRduri == ZOqAMzhHmB){BCkAjdBgEO = true;}
      if(seDXGgpyGb == HLMRuKJmSk){BxCBRRDuOh = true;}
      else if(HLMRuKJmSk == seDXGgpyGb){hQUdmJBmZK = true;}
      if(BSGhQysiWn == JBQebxZTGh){zOGrLpadhs = true;}
      else if(JBQebxZTGh == BSGhQysiWn){czSDUKNKcV = true;}
      if(kEBxZSVzWc == deCxwutglO){crIilMwuuk = true;}
      if(wdTKmzeyuX == BjjGLzAzMM){SeUsapVAFE = true;}
      if(HFYYGGIIiO == mFBInTHVeO){mAKTiadlAH = true;}
      while(deCxwutglO == kEBxZSVzWc){FEHzTQoYrb = true;}
      while(BjjGLzAzMM == BjjGLzAzMM){ZAjkcRoPAq = true;}
      while(mFBInTHVeO == mFBInTHVeO){qbOunBjgeZ = true;}
      if(rKnJFcIPUA == true){rKnJFcIPUA = false;}
      if(PcBEiYRJSc == true){PcBEiYRJSc = false;}
      if(xaGsuXctIc == true){xaGsuXctIc = false;}
      if(nYCWWpuZBi == true){nYCWWpuZBi = false;}
      if(pjdLxKExYP == true){pjdLxKExYP = false;}
      if(BxCBRRDuOh == true){BxCBRRDuOh = false;}
      if(zOGrLpadhs == true){zOGrLpadhs = false;}
      if(crIilMwuuk == true){crIilMwuuk = false;}
      if(SeUsapVAFE == true){SeUsapVAFE = false;}
      if(mAKTiadlAH == true){mAKTiadlAH = false;}
      if(jZPfmJoSOE == true){jZPfmJoSOE = false;}
      if(UIzdOUsNQV == true){UIzdOUsNQV = false;}
      if(TZYcFbgoAK == true){TZYcFbgoAK = false;}
      if(iKtnBrOoGQ == true){iKtnBrOoGQ = false;}
      if(BCkAjdBgEO == true){BCkAjdBgEO = false;}
      if(hQUdmJBmZK == true){hQUdmJBmZK = false;}
      if(czSDUKNKcV == true){czSDUKNKcV = false;}
      if(FEHzTQoYrb == true){FEHzTQoYrb = false;}
      if(ZAjkcRoPAq == true){ZAjkcRoPAq = false;}
      if(qbOunBjgeZ == true){qbOunBjgeZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELEOGMVIGY
{ 
  void VsmYaQiwSE()
  { 
      bool OnPrYzVXMO = false;
      bool uWAdVIQFBU = false;
      bool xFDSkocdbZ = false;
      bool mHbqmJbCSZ = false;
      bool QqZHbTdGdf = false;
      bool JQRzjJkwGj = false;
      bool VqulbmtJqL = false;
      bool fNlbEGeuqR = false;
      bool LWAwQVpbGc = false;
      bool XfuiDYumfn = false;
      bool ZUORAudoud = false;
      bool doFoXzqzVF = false;
      bool wRCNnzSDYe = false;
      bool KqPCqpHhuU = false;
      bool qBgcziZGLE = false;
      bool hwRZrHSBdA = false;
      bool caQPSlYCxg = false;
      bool qIDBNtkYOE = false;
      bool YMrTxOZoKj = false;
      bool XGEuqPkQJM = false;
      string kjObinhKII;
      string cYxAsyuSkE;
      string WaurGsUzRT;
      string JqwAUmEJwj;
      string angxqUpXtW;
      string hxkpdJoVVo;
      string TiroykbxeF;
      string skWBcityBl;
      string DwEukMFGWK;
      string xhnGPqwqyF;
      string rssncxajMt;
      string PqUilWewDl;
      string fVZTIKwPkl;
      string lCzusKDQRn;
      string kVtcuGNEUs;
      string MAmMYWTYfS;
      string ALyaHMqYob;
      string TNdPAKawYB;
      string xrtrYlOlVW;
      string pdjznZWSUh;
      if(kjObinhKII == rssncxajMt){OnPrYzVXMO = true;}
      else if(rssncxajMt == kjObinhKII){ZUORAudoud = true;}
      if(cYxAsyuSkE == PqUilWewDl){uWAdVIQFBU = true;}
      else if(PqUilWewDl == cYxAsyuSkE){doFoXzqzVF = true;}
      if(WaurGsUzRT == fVZTIKwPkl){xFDSkocdbZ = true;}
      else if(fVZTIKwPkl == WaurGsUzRT){wRCNnzSDYe = true;}
      if(JqwAUmEJwj == lCzusKDQRn){mHbqmJbCSZ = true;}
      else if(lCzusKDQRn == JqwAUmEJwj){KqPCqpHhuU = true;}
      if(angxqUpXtW == kVtcuGNEUs){QqZHbTdGdf = true;}
      else if(kVtcuGNEUs == angxqUpXtW){qBgcziZGLE = true;}
      if(hxkpdJoVVo == MAmMYWTYfS){JQRzjJkwGj = true;}
      else if(MAmMYWTYfS == hxkpdJoVVo){hwRZrHSBdA = true;}
      if(TiroykbxeF == ALyaHMqYob){VqulbmtJqL = true;}
      else if(ALyaHMqYob == TiroykbxeF){caQPSlYCxg = true;}
      if(skWBcityBl == TNdPAKawYB){fNlbEGeuqR = true;}
      if(DwEukMFGWK == xrtrYlOlVW){LWAwQVpbGc = true;}
      if(xhnGPqwqyF == pdjznZWSUh){XfuiDYumfn = true;}
      while(TNdPAKawYB == skWBcityBl){qIDBNtkYOE = true;}
      while(xrtrYlOlVW == xrtrYlOlVW){YMrTxOZoKj = true;}
      while(pdjznZWSUh == pdjznZWSUh){XGEuqPkQJM = true;}
      if(OnPrYzVXMO == true){OnPrYzVXMO = false;}
      if(uWAdVIQFBU == true){uWAdVIQFBU = false;}
      if(xFDSkocdbZ == true){xFDSkocdbZ = false;}
      if(mHbqmJbCSZ == true){mHbqmJbCSZ = false;}
      if(QqZHbTdGdf == true){QqZHbTdGdf = false;}
      if(JQRzjJkwGj == true){JQRzjJkwGj = false;}
      if(VqulbmtJqL == true){VqulbmtJqL = false;}
      if(fNlbEGeuqR == true){fNlbEGeuqR = false;}
      if(LWAwQVpbGc == true){LWAwQVpbGc = false;}
      if(XfuiDYumfn == true){XfuiDYumfn = false;}
      if(ZUORAudoud == true){ZUORAudoud = false;}
      if(doFoXzqzVF == true){doFoXzqzVF = false;}
      if(wRCNnzSDYe == true){wRCNnzSDYe = false;}
      if(KqPCqpHhuU == true){KqPCqpHhuU = false;}
      if(qBgcziZGLE == true){qBgcziZGLE = false;}
      if(hwRZrHSBdA == true){hwRZrHSBdA = false;}
      if(caQPSlYCxg == true){caQPSlYCxg = false;}
      if(qIDBNtkYOE == true){qIDBNtkYOE = false;}
      if(YMrTxOZoKj == true){YMrTxOZoKj = false;}
      if(XGEuqPkQJM == true){XGEuqPkQJM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JJPINXVCKK
{ 
  void XJkaRXlhCC()
  { 
      bool GebeenOgcU = false;
      bool MpwxnyrmUb = false;
      bool tSYtyNTSGq = false;
      bool VrtllisYJY = false;
      bool tUmFhykbrT = false;
      bool eggahnFhfQ = false;
      bool TwakzTuKKF = false;
      bool ESdugZeTLA = false;
      bool bramMnKSDy = false;
      bool dLrsFysBGN = false;
      bool CaRlOLDksI = false;
      bool IkVenbUnYK = false;
      bool IbGLbsakpi = false;
      bool fdNxyBZnXA = false;
      bool kYZuprpMEc = false;
      bool cFcuEZTGKV = false;
      bool kSuJbdXXgm = false;
      bool BgPXYjCKUj = false;
      bool DNfMGZARrY = false;
      bool gTcCPSdQSL = false;
      string OuesFeTzrT;
      string hXFSOBcoXZ;
      string hmXHQwAXkq;
      string CIeZDCpjns;
      string mLPqWdALjG;
      string zRUPeaWWbJ;
      string dwNARYseOM;
      string LsAdlVWgjl;
      string womeqjmOuc;
      string eSHePqyOYx;
      string kVwXuFRqdI;
      string EpmpNnIiJh;
      string leilhslVOu;
      string XHHlBZrPik;
      string SwjmXoeQRa;
      string hOFqLGlKpC;
      string TubhjwhAom;
      string wszXOptwNs;
      string NVDnNICPat;
      string nhYgRWUCCb;
      if(OuesFeTzrT == kVwXuFRqdI){GebeenOgcU = true;}
      else if(kVwXuFRqdI == OuesFeTzrT){CaRlOLDksI = true;}
      if(hXFSOBcoXZ == EpmpNnIiJh){MpwxnyrmUb = true;}
      else if(EpmpNnIiJh == hXFSOBcoXZ){IkVenbUnYK = true;}
      if(hmXHQwAXkq == leilhslVOu){tSYtyNTSGq = true;}
      else if(leilhslVOu == hmXHQwAXkq){IbGLbsakpi = true;}
      if(CIeZDCpjns == XHHlBZrPik){VrtllisYJY = true;}
      else if(XHHlBZrPik == CIeZDCpjns){fdNxyBZnXA = true;}
      if(mLPqWdALjG == SwjmXoeQRa){tUmFhykbrT = true;}
      else if(SwjmXoeQRa == mLPqWdALjG){kYZuprpMEc = true;}
      if(zRUPeaWWbJ == hOFqLGlKpC){eggahnFhfQ = true;}
      else if(hOFqLGlKpC == zRUPeaWWbJ){cFcuEZTGKV = true;}
      if(dwNARYseOM == TubhjwhAom){TwakzTuKKF = true;}
      else if(TubhjwhAom == dwNARYseOM){kSuJbdXXgm = true;}
      if(LsAdlVWgjl == wszXOptwNs){ESdugZeTLA = true;}
      if(womeqjmOuc == NVDnNICPat){bramMnKSDy = true;}
      if(eSHePqyOYx == nhYgRWUCCb){dLrsFysBGN = true;}
      while(wszXOptwNs == LsAdlVWgjl){BgPXYjCKUj = true;}
      while(NVDnNICPat == NVDnNICPat){DNfMGZARrY = true;}
      while(nhYgRWUCCb == nhYgRWUCCb){gTcCPSdQSL = true;}
      if(GebeenOgcU == true){GebeenOgcU = false;}
      if(MpwxnyrmUb == true){MpwxnyrmUb = false;}
      if(tSYtyNTSGq == true){tSYtyNTSGq = false;}
      if(VrtllisYJY == true){VrtllisYJY = false;}
      if(tUmFhykbrT == true){tUmFhykbrT = false;}
      if(eggahnFhfQ == true){eggahnFhfQ = false;}
      if(TwakzTuKKF == true){TwakzTuKKF = false;}
      if(ESdugZeTLA == true){ESdugZeTLA = false;}
      if(bramMnKSDy == true){bramMnKSDy = false;}
      if(dLrsFysBGN == true){dLrsFysBGN = false;}
      if(CaRlOLDksI == true){CaRlOLDksI = false;}
      if(IkVenbUnYK == true){IkVenbUnYK = false;}
      if(IbGLbsakpi == true){IbGLbsakpi = false;}
      if(fdNxyBZnXA == true){fdNxyBZnXA = false;}
      if(kYZuprpMEc == true){kYZuprpMEc = false;}
      if(cFcuEZTGKV == true){cFcuEZTGKV = false;}
      if(kSuJbdXXgm == true){kSuJbdXXgm = false;}
      if(BgPXYjCKUj == true){BgPXYjCKUj = false;}
      if(DNfMGZARrY == true){DNfMGZARrY = false;}
      if(gTcCPSdQSL == true){gTcCPSdQSL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NIOLEYRVCT
{ 
  void QpzQCoIBgN()
  { 
      bool FQyfBWDVCA = false;
      bool PNTXztEeKP = false;
      bool oqfzbfdnhT = false;
      bool oPsbxyXSVT = false;
      bool jTNenHSKQk = false;
      bool qsVyZOkzDV = false;
      bool rOmhKATrZB = false;
      bool VlJpeVcAKU = false;
      bool NSXxcwsuBi = false;
      bool NXOAaVfeTn = false;
      bool mZjOOFieTD = false;
      bool kjoiHZppFO = false;
      bool GYqqnxWJPI = false;
      bool pygWgmhIhW = false;
      bool NNaxxcierA = false;
      bool eoZFgOisaQ = false;
      bool hZPKNmDRCU = false;
      bool rhHhAsxssK = false;
      bool OrQOdAXbpS = false;
      bool DogRonxQiK = false;
      string UqTBxyetMC;
      string NwzFYPjpkF;
      string GAnOdWhIWS;
      string IBLISFnqsD;
      string aQjZQZkkIi;
      string hcdEpTDEWZ;
      string PVXstMjqlS;
      string bswgeoPNyE;
      string kxzmkeXHRz;
      string CiTSnFsqfD;
      string otypHofwZA;
      string DoGSoSVjIO;
      string ocYmPrYcsY;
      string wYhtPqyJeu;
      string yagRuMcBdV;
      string iIiROLVLaP;
      string QDCADeHLCx;
      string TMEMPNwHqC;
      string PWyXpnoPfD;
      string VmiPeuXfNP;
      if(UqTBxyetMC == otypHofwZA){FQyfBWDVCA = true;}
      else if(otypHofwZA == UqTBxyetMC){mZjOOFieTD = true;}
      if(NwzFYPjpkF == DoGSoSVjIO){PNTXztEeKP = true;}
      else if(DoGSoSVjIO == NwzFYPjpkF){kjoiHZppFO = true;}
      if(GAnOdWhIWS == ocYmPrYcsY){oqfzbfdnhT = true;}
      else if(ocYmPrYcsY == GAnOdWhIWS){GYqqnxWJPI = true;}
      if(IBLISFnqsD == wYhtPqyJeu){oPsbxyXSVT = true;}
      else if(wYhtPqyJeu == IBLISFnqsD){pygWgmhIhW = true;}
      if(aQjZQZkkIi == yagRuMcBdV){jTNenHSKQk = true;}
      else if(yagRuMcBdV == aQjZQZkkIi){NNaxxcierA = true;}
      if(hcdEpTDEWZ == iIiROLVLaP){qsVyZOkzDV = true;}
      else if(iIiROLVLaP == hcdEpTDEWZ){eoZFgOisaQ = true;}
      if(PVXstMjqlS == QDCADeHLCx){rOmhKATrZB = true;}
      else if(QDCADeHLCx == PVXstMjqlS){hZPKNmDRCU = true;}
      if(bswgeoPNyE == TMEMPNwHqC){VlJpeVcAKU = true;}
      if(kxzmkeXHRz == PWyXpnoPfD){NSXxcwsuBi = true;}
      if(CiTSnFsqfD == VmiPeuXfNP){NXOAaVfeTn = true;}
      while(TMEMPNwHqC == bswgeoPNyE){rhHhAsxssK = true;}
      while(PWyXpnoPfD == PWyXpnoPfD){OrQOdAXbpS = true;}
      while(VmiPeuXfNP == VmiPeuXfNP){DogRonxQiK = true;}
      if(FQyfBWDVCA == true){FQyfBWDVCA = false;}
      if(PNTXztEeKP == true){PNTXztEeKP = false;}
      if(oqfzbfdnhT == true){oqfzbfdnhT = false;}
      if(oPsbxyXSVT == true){oPsbxyXSVT = false;}
      if(jTNenHSKQk == true){jTNenHSKQk = false;}
      if(qsVyZOkzDV == true){qsVyZOkzDV = false;}
      if(rOmhKATrZB == true){rOmhKATrZB = false;}
      if(VlJpeVcAKU == true){VlJpeVcAKU = false;}
      if(NSXxcwsuBi == true){NSXxcwsuBi = false;}
      if(NXOAaVfeTn == true){NXOAaVfeTn = false;}
      if(mZjOOFieTD == true){mZjOOFieTD = false;}
      if(kjoiHZppFO == true){kjoiHZppFO = false;}
      if(GYqqnxWJPI == true){GYqqnxWJPI = false;}
      if(pygWgmhIhW == true){pygWgmhIhW = false;}
      if(NNaxxcierA == true){NNaxxcierA = false;}
      if(eoZFgOisaQ == true){eoZFgOisaQ = false;}
      if(hZPKNmDRCU == true){hZPKNmDRCU = false;}
      if(rhHhAsxssK == true){rhHhAsxssK = false;}
      if(OrQOdAXbpS == true){OrQOdAXbpS = false;}
      if(DogRonxQiK == true){DogRonxQiK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTLHHQEBEI
{ 
  void XYbeokmtFQ()
  { 
      bool AQeyhhcMzE = false;
      bool sQUFpNhTGU = false;
      bool eTTldxXnqO = false;
      bool gePuCCUZEa = false;
      bool RKdKthnNSp = false;
      bool SynCZfxrUj = false;
      bool KnUjWOAYCn = false;
      bool sHOfDUoIru = false;
      bool JKUBwhpNVV = false;
      bool FbETQcotme = false;
      bool hOKewKiIyE = false;
      bool pnAYZATSno = false;
      bool XlDghQCuPa = false;
      bool euVMNuzpFk = false;
      bool zgOQeRafsP = false;
      bool JVFyHuKdwe = false;
      bool HnsWZuRnKe = false;
      bool AcNDppXlBQ = false;
      bool oWBzRIpWFS = false;
      bool jVtZcKnqqj = false;
      string HYiHfekAtH;
      string QWcUFFWdYM;
      string VXBrNQjjmu;
      string YncbYNofWV;
      string oGVUBAgaAr;
      string JMiTBiXptP;
      string uAMzibtBwq;
      string QpHCWPBfqM;
      string iIiukLEIZo;
      string pylHaosWlY;
      string FfdIbSFgxl;
      string hqzgflQRNW;
      string WlbHBREzag;
      string VesRHDeZTR;
      string GXLmHyyEao;
      string YaIPCTEVHJ;
      string NFFPPCyhZc;
      string GpyuPyZnAC;
      string SAXlItWdOm;
      string yJSJEARuXE;
      if(HYiHfekAtH == FfdIbSFgxl){AQeyhhcMzE = true;}
      else if(FfdIbSFgxl == HYiHfekAtH){hOKewKiIyE = true;}
      if(QWcUFFWdYM == hqzgflQRNW){sQUFpNhTGU = true;}
      else if(hqzgflQRNW == QWcUFFWdYM){pnAYZATSno = true;}
      if(VXBrNQjjmu == WlbHBREzag){eTTldxXnqO = true;}
      else if(WlbHBREzag == VXBrNQjjmu){XlDghQCuPa = true;}
      if(YncbYNofWV == VesRHDeZTR){gePuCCUZEa = true;}
      else if(VesRHDeZTR == YncbYNofWV){euVMNuzpFk = true;}
      if(oGVUBAgaAr == GXLmHyyEao){RKdKthnNSp = true;}
      else if(GXLmHyyEao == oGVUBAgaAr){zgOQeRafsP = true;}
      if(JMiTBiXptP == YaIPCTEVHJ){SynCZfxrUj = true;}
      else if(YaIPCTEVHJ == JMiTBiXptP){JVFyHuKdwe = true;}
      if(uAMzibtBwq == NFFPPCyhZc){KnUjWOAYCn = true;}
      else if(NFFPPCyhZc == uAMzibtBwq){HnsWZuRnKe = true;}
      if(QpHCWPBfqM == GpyuPyZnAC){sHOfDUoIru = true;}
      if(iIiukLEIZo == SAXlItWdOm){JKUBwhpNVV = true;}
      if(pylHaosWlY == yJSJEARuXE){FbETQcotme = true;}
      while(GpyuPyZnAC == QpHCWPBfqM){AcNDppXlBQ = true;}
      while(SAXlItWdOm == SAXlItWdOm){oWBzRIpWFS = true;}
      while(yJSJEARuXE == yJSJEARuXE){jVtZcKnqqj = true;}
      if(AQeyhhcMzE == true){AQeyhhcMzE = false;}
      if(sQUFpNhTGU == true){sQUFpNhTGU = false;}
      if(eTTldxXnqO == true){eTTldxXnqO = false;}
      if(gePuCCUZEa == true){gePuCCUZEa = false;}
      if(RKdKthnNSp == true){RKdKthnNSp = false;}
      if(SynCZfxrUj == true){SynCZfxrUj = false;}
      if(KnUjWOAYCn == true){KnUjWOAYCn = false;}
      if(sHOfDUoIru == true){sHOfDUoIru = false;}
      if(JKUBwhpNVV == true){JKUBwhpNVV = false;}
      if(FbETQcotme == true){FbETQcotme = false;}
      if(hOKewKiIyE == true){hOKewKiIyE = false;}
      if(pnAYZATSno == true){pnAYZATSno = false;}
      if(XlDghQCuPa == true){XlDghQCuPa = false;}
      if(euVMNuzpFk == true){euVMNuzpFk = false;}
      if(zgOQeRafsP == true){zgOQeRafsP = false;}
      if(JVFyHuKdwe == true){JVFyHuKdwe = false;}
      if(HnsWZuRnKe == true){HnsWZuRnKe = false;}
      if(AcNDppXlBQ == true){AcNDppXlBQ = false;}
      if(oWBzRIpWFS == true){oWBzRIpWFS = false;}
      if(jVtZcKnqqj == true){jVtZcKnqqj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IJBTVNQIYT
{ 
  void GcJwcFFTgC()
  { 
      bool qDNEJIqqOK = false;
      bool dUdPPzDzbe = false;
      bool jNoaDSzFBJ = false;
      bool MIqfdboQpu = false;
      bool BZhjCNVPfI = false;
      bool dWbgZdNlAp = false;
      bool JkoFxVcykn = false;
      bool JlIfcKeFYp = false;
      bool xiZreofKFA = false;
      bool NDQAlPjclf = false;
      bool jXdrzqOuDP = false;
      bool yHNJsZLxZH = false;
      bool oRrkZFVHtN = false;
      bool ZCTrFYEhrn = false;
      bool akGoBFoGGL = false;
      bool ElCdqRfsRs = false;
      bool VGBppunVDT = false;
      bool VdFlgELCiU = false;
      bool QPBhJmzoAn = false;
      bool sLQyRTiQzF = false;
      string KirxQdynlT;
      string aOALarNnun;
      string EIKkFGwYrh;
      string aXJWfnQprz;
      string KhXAAtoDwn;
      string xgYAeCYHqJ;
      string hZwDsDFdfm;
      string aWuucWkKjL;
      string RsbDjsyIqc;
      string PJziRkkTGx;
      string nKXJMZlcXI;
      string RNWeroxrTz;
      string ExmCXRXMdq;
      string kQDmXGVSqK;
      string HVjiLBmUpc;
      string mrAHsqXUlu;
      string CZzfWAJiHl;
      string TeBJriMDqV;
      string eDVAErQwtf;
      string hAfwHhVELK;
      if(KirxQdynlT == nKXJMZlcXI){qDNEJIqqOK = true;}
      else if(nKXJMZlcXI == KirxQdynlT){jXdrzqOuDP = true;}
      if(aOALarNnun == RNWeroxrTz){dUdPPzDzbe = true;}
      else if(RNWeroxrTz == aOALarNnun){yHNJsZLxZH = true;}
      if(EIKkFGwYrh == ExmCXRXMdq){jNoaDSzFBJ = true;}
      else if(ExmCXRXMdq == EIKkFGwYrh){oRrkZFVHtN = true;}
      if(aXJWfnQprz == kQDmXGVSqK){MIqfdboQpu = true;}
      else if(kQDmXGVSqK == aXJWfnQprz){ZCTrFYEhrn = true;}
      if(KhXAAtoDwn == HVjiLBmUpc){BZhjCNVPfI = true;}
      else if(HVjiLBmUpc == KhXAAtoDwn){akGoBFoGGL = true;}
      if(xgYAeCYHqJ == mrAHsqXUlu){dWbgZdNlAp = true;}
      else if(mrAHsqXUlu == xgYAeCYHqJ){ElCdqRfsRs = true;}
      if(hZwDsDFdfm == CZzfWAJiHl){JkoFxVcykn = true;}
      else if(CZzfWAJiHl == hZwDsDFdfm){VGBppunVDT = true;}
      if(aWuucWkKjL == TeBJriMDqV){JlIfcKeFYp = true;}
      if(RsbDjsyIqc == eDVAErQwtf){xiZreofKFA = true;}
      if(PJziRkkTGx == hAfwHhVELK){NDQAlPjclf = true;}
      while(TeBJriMDqV == aWuucWkKjL){VdFlgELCiU = true;}
      while(eDVAErQwtf == eDVAErQwtf){QPBhJmzoAn = true;}
      while(hAfwHhVELK == hAfwHhVELK){sLQyRTiQzF = true;}
      if(qDNEJIqqOK == true){qDNEJIqqOK = false;}
      if(dUdPPzDzbe == true){dUdPPzDzbe = false;}
      if(jNoaDSzFBJ == true){jNoaDSzFBJ = false;}
      if(MIqfdboQpu == true){MIqfdboQpu = false;}
      if(BZhjCNVPfI == true){BZhjCNVPfI = false;}
      if(dWbgZdNlAp == true){dWbgZdNlAp = false;}
      if(JkoFxVcykn == true){JkoFxVcykn = false;}
      if(JlIfcKeFYp == true){JlIfcKeFYp = false;}
      if(xiZreofKFA == true){xiZreofKFA = false;}
      if(NDQAlPjclf == true){NDQAlPjclf = false;}
      if(jXdrzqOuDP == true){jXdrzqOuDP = false;}
      if(yHNJsZLxZH == true){yHNJsZLxZH = false;}
      if(oRrkZFVHtN == true){oRrkZFVHtN = false;}
      if(ZCTrFYEhrn == true){ZCTrFYEhrn = false;}
      if(akGoBFoGGL == true){akGoBFoGGL = false;}
      if(ElCdqRfsRs == true){ElCdqRfsRs = false;}
      if(VGBppunVDT == true){VGBppunVDT = false;}
      if(VdFlgELCiU == true){VdFlgELCiU = false;}
      if(QPBhJmzoAn == true){QPBhJmzoAn = false;}
      if(sLQyRTiQzF == true){sLQyRTiQzF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XZQXKULXUQ
{ 
  void ogrcJXrhiK()
  { 
      bool iSnoKQuwbZ = false;
      bool WZLWqQmrkI = false;
      bool JNXdVUlmDW = false;
      bool XOKynbGArS = false;
      bool EUsEsXlnFV = false;
      bool JtAfNVuJSp = false;
      bool dHsFCHPMhO = false;
      bool JmASEoTTkx = false;
      bool hyhgMdOdkS = false;
      bool fwgBnwanCk = false;
      bool IYFpLWtgbY = false;
      bool BbYUHfZMrY = false;
      bool rkbOiNFydH = false;
      bool NeQzoIrqVp = false;
      bool igCLQEXMtI = false;
      bool WOwcrWxpHy = false;
      bool RwDTKVKYfz = false;
      bool mipCoLhPyd = false;
      bool osEVjzimGR = false;
      bool LBjWXmdiBt = false;
      string lHheoLjyoZ;
      string niijwIFtLS;
      string cctVfAfquQ;
      string enCBmiBOrF;
      string HAykcMFzAJ;
      string edgcPJMLzn;
      string erDYtzghxN;
      string GqCGLbdJsS;
      string ugqkkBHYkd;
      string VoODaOxZpc;
      string fWBlCmaZRm;
      string eCSgsxBRms;
      string rHxTqQbzew;
      string eDSPmYeEhx;
      string ZgHxyTVhJc;
      string MelwkXZgtl;
      string LbtUIajDsU;
      string SwjoTKAzVX;
      string ttoCizRVeP;
      string yyKwlxlloW;
      if(lHheoLjyoZ == fWBlCmaZRm){iSnoKQuwbZ = true;}
      else if(fWBlCmaZRm == lHheoLjyoZ){IYFpLWtgbY = true;}
      if(niijwIFtLS == eCSgsxBRms){WZLWqQmrkI = true;}
      else if(eCSgsxBRms == niijwIFtLS){BbYUHfZMrY = true;}
      if(cctVfAfquQ == rHxTqQbzew){JNXdVUlmDW = true;}
      else if(rHxTqQbzew == cctVfAfquQ){rkbOiNFydH = true;}
      if(enCBmiBOrF == eDSPmYeEhx){XOKynbGArS = true;}
      else if(eDSPmYeEhx == enCBmiBOrF){NeQzoIrqVp = true;}
      if(HAykcMFzAJ == ZgHxyTVhJc){EUsEsXlnFV = true;}
      else if(ZgHxyTVhJc == HAykcMFzAJ){igCLQEXMtI = true;}
      if(edgcPJMLzn == MelwkXZgtl){JtAfNVuJSp = true;}
      else if(MelwkXZgtl == edgcPJMLzn){WOwcrWxpHy = true;}
      if(erDYtzghxN == LbtUIajDsU){dHsFCHPMhO = true;}
      else if(LbtUIajDsU == erDYtzghxN){RwDTKVKYfz = true;}
      if(GqCGLbdJsS == SwjoTKAzVX){JmASEoTTkx = true;}
      if(ugqkkBHYkd == ttoCizRVeP){hyhgMdOdkS = true;}
      if(VoODaOxZpc == yyKwlxlloW){fwgBnwanCk = true;}
      while(SwjoTKAzVX == GqCGLbdJsS){mipCoLhPyd = true;}
      while(ttoCizRVeP == ttoCizRVeP){osEVjzimGR = true;}
      while(yyKwlxlloW == yyKwlxlloW){LBjWXmdiBt = true;}
      if(iSnoKQuwbZ == true){iSnoKQuwbZ = false;}
      if(WZLWqQmrkI == true){WZLWqQmrkI = false;}
      if(JNXdVUlmDW == true){JNXdVUlmDW = false;}
      if(XOKynbGArS == true){XOKynbGArS = false;}
      if(EUsEsXlnFV == true){EUsEsXlnFV = false;}
      if(JtAfNVuJSp == true){JtAfNVuJSp = false;}
      if(dHsFCHPMhO == true){dHsFCHPMhO = false;}
      if(JmASEoTTkx == true){JmASEoTTkx = false;}
      if(hyhgMdOdkS == true){hyhgMdOdkS = false;}
      if(fwgBnwanCk == true){fwgBnwanCk = false;}
      if(IYFpLWtgbY == true){IYFpLWtgbY = false;}
      if(BbYUHfZMrY == true){BbYUHfZMrY = false;}
      if(rkbOiNFydH == true){rkbOiNFydH = false;}
      if(NeQzoIrqVp == true){NeQzoIrqVp = false;}
      if(igCLQEXMtI == true){igCLQEXMtI = false;}
      if(WOwcrWxpHy == true){WOwcrWxpHy = false;}
      if(RwDTKVKYfz == true){RwDTKVKYfz = false;}
      if(mipCoLhPyd == true){mipCoLhPyd = false;}
      if(osEVjzimGR == true){osEVjzimGR = false;}
      if(LBjWXmdiBt == true){LBjWXmdiBt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TDKHGCEBBX
{ 
  void aYXiMmkTAP()
  { 
      bool VpEHPBsCjk = false;
      bool sPCViYkkKJ = false;
      bool senwXxONJo = false;
      bool XVgKKAGDOw = false;
      bool IwLKjVtTIO = false;
      bool HbZxspBIiS = false;
      bool mfrtMXhqKi = false;
      bool RgVOAxTdLB = false;
      bool CuEuhuwiRT = false;
      bool zyUuJbDRxL = false;
      bool mCIYwZGLww = false;
      bool WWwgQrawLR = false;
      bool azZqiTMZEY = false;
      bool sBgAOzleyI = false;
      bool oklVxbCmeR = false;
      bool BGGfkncRpc = false;
      bool MfGXCVpwSQ = false;
      bool FuyDbpMEsG = false;
      bool QZtmWluBPZ = false;
      bool WUoUuJdOSa = false;
      string OKbKkNxSDF;
      string bdqYuMYDNb;
      string WFUchnwZml;
      string YfWJdcXGLU;
      string XAlTdGqWze;
      string pOyQfJpycw;
      string RWeQfuGhuR;
      string oRqsEVTBzb;
      string xYZHuKhGcT;
      string mYdPDBVUmi;
      string zIahpXWFMK;
      string pozAyrwWUV;
      string NAFaePnboD;
      string AyNQboxrRX;
      string mctRdxYcQK;
      string EyzRUzDADZ;
      string juPJKqaiYJ;
      string tDFxhjGnxg;
      string pKKeyBywuc;
      string kxormrMjGl;
      if(OKbKkNxSDF == zIahpXWFMK){VpEHPBsCjk = true;}
      else if(zIahpXWFMK == OKbKkNxSDF){mCIYwZGLww = true;}
      if(bdqYuMYDNb == pozAyrwWUV){sPCViYkkKJ = true;}
      else if(pozAyrwWUV == bdqYuMYDNb){WWwgQrawLR = true;}
      if(WFUchnwZml == NAFaePnboD){senwXxONJo = true;}
      else if(NAFaePnboD == WFUchnwZml){azZqiTMZEY = true;}
      if(YfWJdcXGLU == AyNQboxrRX){XVgKKAGDOw = true;}
      else if(AyNQboxrRX == YfWJdcXGLU){sBgAOzleyI = true;}
      if(XAlTdGqWze == mctRdxYcQK){IwLKjVtTIO = true;}
      else if(mctRdxYcQK == XAlTdGqWze){oklVxbCmeR = true;}
      if(pOyQfJpycw == EyzRUzDADZ){HbZxspBIiS = true;}
      else if(EyzRUzDADZ == pOyQfJpycw){BGGfkncRpc = true;}
      if(RWeQfuGhuR == juPJKqaiYJ){mfrtMXhqKi = true;}
      else if(juPJKqaiYJ == RWeQfuGhuR){MfGXCVpwSQ = true;}
      if(oRqsEVTBzb == tDFxhjGnxg){RgVOAxTdLB = true;}
      if(xYZHuKhGcT == pKKeyBywuc){CuEuhuwiRT = true;}
      if(mYdPDBVUmi == kxormrMjGl){zyUuJbDRxL = true;}
      while(tDFxhjGnxg == oRqsEVTBzb){FuyDbpMEsG = true;}
      while(pKKeyBywuc == pKKeyBywuc){QZtmWluBPZ = true;}
      while(kxormrMjGl == kxormrMjGl){WUoUuJdOSa = true;}
      if(VpEHPBsCjk == true){VpEHPBsCjk = false;}
      if(sPCViYkkKJ == true){sPCViYkkKJ = false;}
      if(senwXxONJo == true){senwXxONJo = false;}
      if(XVgKKAGDOw == true){XVgKKAGDOw = false;}
      if(IwLKjVtTIO == true){IwLKjVtTIO = false;}
      if(HbZxspBIiS == true){HbZxspBIiS = false;}
      if(mfrtMXhqKi == true){mfrtMXhqKi = false;}
      if(RgVOAxTdLB == true){RgVOAxTdLB = false;}
      if(CuEuhuwiRT == true){CuEuhuwiRT = false;}
      if(zyUuJbDRxL == true){zyUuJbDRxL = false;}
      if(mCIYwZGLww == true){mCIYwZGLww = false;}
      if(WWwgQrawLR == true){WWwgQrawLR = false;}
      if(azZqiTMZEY == true){azZqiTMZEY = false;}
      if(sBgAOzleyI == true){sBgAOzleyI = false;}
      if(oklVxbCmeR == true){oklVxbCmeR = false;}
      if(BGGfkncRpc == true){BGGfkncRpc = false;}
      if(MfGXCVpwSQ == true){MfGXCVpwSQ = false;}
      if(FuyDbpMEsG == true){FuyDbpMEsG = false;}
      if(QZtmWluBPZ == true){QZtmWluBPZ = false;}
      if(WUoUuJdOSa == true){WUoUuJdOSa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IAEXNZBBGI
{ 
  void EcpLjlkRbq()
  { 
      bool nDUEKWYtsN = false;
      bool iQcIKlEhBn = false;
      bool FsLPqdkTQP = false;
      bool fKDLPeSRWT = false;
      bool jFwlfoWIOV = false;
      bool xUbCstrEMg = false;
      bool lFddhXNRrf = false;
      bool TmKhEzwYjC = false;
      bool HbFuRKiARU = false;
      bool lNEpgdbSEH = false;
      bool bFPhCKJtyt = false;
      bool yTUKYJAiLW = false;
      bool oMzXtFhUAZ = false;
      bool XdTbZCMWrH = false;
      bool BnCXWRssQX = false;
      bool dsHhSOFqnx = false;
      bool botYVUAskW = false;
      bool wdpDVAKbBb = false;
      bool MoDbweVkJK = false;
      bool wVhufLtdBC = false;
      string yHIdJjWwaa;
      string ejhqUARVkJ;
      string GcWDopfeZV;
      string JWyozpcIiI;
      string sAgUHTisQO;
      string XjPWdVkEoT;
      string DqWFRIkrre;
      string WIlbQFuCuV;
      string GmNKxYGbLd;
      string FYTOFBdbCy;
      string hqBlqOxmGX;
      string ZhISNPdLHr;
      string CJgOZynXWO;
      string aTzxmPlbSi;
      string bSUmEWPABo;
      string XSTJwXJmLs;
      string aZPqwFiLex;
      string dBsYQinsJD;
      string hnVhpIAoAP;
      string FzQYIBCcpy;
      if(yHIdJjWwaa == hqBlqOxmGX){nDUEKWYtsN = true;}
      else if(hqBlqOxmGX == yHIdJjWwaa){bFPhCKJtyt = true;}
      if(ejhqUARVkJ == ZhISNPdLHr){iQcIKlEhBn = true;}
      else if(ZhISNPdLHr == ejhqUARVkJ){yTUKYJAiLW = true;}
      if(GcWDopfeZV == CJgOZynXWO){FsLPqdkTQP = true;}
      else if(CJgOZynXWO == GcWDopfeZV){oMzXtFhUAZ = true;}
      if(JWyozpcIiI == aTzxmPlbSi){fKDLPeSRWT = true;}
      else if(aTzxmPlbSi == JWyozpcIiI){XdTbZCMWrH = true;}
      if(sAgUHTisQO == bSUmEWPABo){jFwlfoWIOV = true;}
      else if(bSUmEWPABo == sAgUHTisQO){BnCXWRssQX = true;}
      if(XjPWdVkEoT == XSTJwXJmLs){xUbCstrEMg = true;}
      else if(XSTJwXJmLs == XjPWdVkEoT){dsHhSOFqnx = true;}
      if(DqWFRIkrre == aZPqwFiLex){lFddhXNRrf = true;}
      else if(aZPqwFiLex == DqWFRIkrre){botYVUAskW = true;}
      if(WIlbQFuCuV == dBsYQinsJD){TmKhEzwYjC = true;}
      if(GmNKxYGbLd == hnVhpIAoAP){HbFuRKiARU = true;}
      if(FYTOFBdbCy == FzQYIBCcpy){lNEpgdbSEH = true;}
      while(dBsYQinsJD == WIlbQFuCuV){wdpDVAKbBb = true;}
      while(hnVhpIAoAP == hnVhpIAoAP){MoDbweVkJK = true;}
      while(FzQYIBCcpy == FzQYIBCcpy){wVhufLtdBC = true;}
      if(nDUEKWYtsN == true){nDUEKWYtsN = false;}
      if(iQcIKlEhBn == true){iQcIKlEhBn = false;}
      if(FsLPqdkTQP == true){FsLPqdkTQP = false;}
      if(fKDLPeSRWT == true){fKDLPeSRWT = false;}
      if(jFwlfoWIOV == true){jFwlfoWIOV = false;}
      if(xUbCstrEMg == true){xUbCstrEMg = false;}
      if(lFddhXNRrf == true){lFddhXNRrf = false;}
      if(TmKhEzwYjC == true){TmKhEzwYjC = false;}
      if(HbFuRKiARU == true){HbFuRKiARU = false;}
      if(lNEpgdbSEH == true){lNEpgdbSEH = false;}
      if(bFPhCKJtyt == true){bFPhCKJtyt = false;}
      if(yTUKYJAiLW == true){yTUKYJAiLW = false;}
      if(oMzXtFhUAZ == true){oMzXtFhUAZ = false;}
      if(XdTbZCMWrH == true){XdTbZCMWrH = false;}
      if(BnCXWRssQX == true){BnCXWRssQX = false;}
      if(dsHhSOFqnx == true){dsHhSOFqnx = false;}
      if(botYVUAskW == true){botYVUAskW = false;}
      if(wdpDVAKbBb == true){wdpDVAKbBb = false;}
      if(MoDbweVkJK == true){MoDbweVkJK = false;}
      if(wVhufLtdBC == true){wVhufLtdBC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIBOFHAMYN
{ 
  void ujggxUMQVD()
  { 
      bool NFsVySOPdn = false;
      bool FqLNUWgTFf = false;
      bool nnPEfXDGMl = false;
      bool weFagADtYc = false;
      bool cBUiBmGQUz = false;
      bool QKqmIZoopZ = false;
      bool PHCrrakkgU = false;
      bool TltcClSfCs = false;
      bool RmlMUkmRSG = false;
      bool KOEyMUzcqa = false;
      bool BViAfdPNkV = false;
      bool HJlwIcVpWH = false;
      bool mSRZKEhwQg = false;
      bool mooarwDkgp = false;
      bool UZgxyBbHoj = false;
      bool zIGinhDIpa = false;
      bool wTxDhSUKEM = false;
      bool YjIflMlTbI = false;
      bool caGghdiFmJ = false;
      bool rtuGtBbcOf = false;
      string CbzVafHjam;
      string whGdHIIDoy;
      string GtUbZrXufp;
      string RaKWfIqBUq;
      string gcHNedPJDq;
      string dcBOEHHWuh;
      string HMDkUUWiyy;
      string RHixQclGwu;
      string cNroMoZwSX;
      string BTFljUZWsJ;
      string HgKFYVtExa;
      string UAaAFtTNYe;
      string uZQawyCwNw;
      string DPNmnuCmQp;
      string uUyqCBsFfp;
      string ALyNOgQjIa;
      string TxqBXFmmLK;
      string qgxijZbYXu;
      string FxPXurRzXH;
      string dSdpVydxTw;
      if(CbzVafHjam == HgKFYVtExa){NFsVySOPdn = true;}
      else if(HgKFYVtExa == CbzVafHjam){BViAfdPNkV = true;}
      if(whGdHIIDoy == UAaAFtTNYe){FqLNUWgTFf = true;}
      else if(UAaAFtTNYe == whGdHIIDoy){HJlwIcVpWH = true;}
      if(GtUbZrXufp == uZQawyCwNw){nnPEfXDGMl = true;}
      else if(uZQawyCwNw == GtUbZrXufp){mSRZKEhwQg = true;}
      if(RaKWfIqBUq == DPNmnuCmQp){weFagADtYc = true;}
      else if(DPNmnuCmQp == RaKWfIqBUq){mooarwDkgp = true;}
      if(gcHNedPJDq == uUyqCBsFfp){cBUiBmGQUz = true;}
      else if(uUyqCBsFfp == gcHNedPJDq){UZgxyBbHoj = true;}
      if(dcBOEHHWuh == ALyNOgQjIa){QKqmIZoopZ = true;}
      else if(ALyNOgQjIa == dcBOEHHWuh){zIGinhDIpa = true;}
      if(HMDkUUWiyy == TxqBXFmmLK){PHCrrakkgU = true;}
      else if(TxqBXFmmLK == HMDkUUWiyy){wTxDhSUKEM = true;}
      if(RHixQclGwu == qgxijZbYXu){TltcClSfCs = true;}
      if(cNroMoZwSX == FxPXurRzXH){RmlMUkmRSG = true;}
      if(BTFljUZWsJ == dSdpVydxTw){KOEyMUzcqa = true;}
      while(qgxijZbYXu == RHixQclGwu){YjIflMlTbI = true;}
      while(FxPXurRzXH == FxPXurRzXH){caGghdiFmJ = true;}
      while(dSdpVydxTw == dSdpVydxTw){rtuGtBbcOf = true;}
      if(NFsVySOPdn == true){NFsVySOPdn = false;}
      if(FqLNUWgTFf == true){FqLNUWgTFf = false;}
      if(nnPEfXDGMl == true){nnPEfXDGMl = false;}
      if(weFagADtYc == true){weFagADtYc = false;}
      if(cBUiBmGQUz == true){cBUiBmGQUz = false;}
      if(QKqmIZoopZ == true){QKqmIZoopZ = false;}
      if(PHCrrakkgU == true){PHCrrakkgU = false;}
      if(TltcClSfCs == true){TltcClSfCs = false;}
      if(RmlMUkmRSG == true){RmlMUkmRSG = false;}
      if(KOEyMUzcqa == true){KOEyMUzcqa = false;}
      if(BViAfdPNkV == true){BViAfdPNkV = false;}
      if(HJlwIcVpWH == true){HJlwIcVpWH = false;}
      if(mSRZKEhwQg == true){mSRZKEhwQg = false;}
      if(mooarwDkgp == true){mooarwDkgp = false;}
      if(UZgxyBbHoj == true){UZgxyBbHoj = false;}
      if(zIGinhDIpa == true){zIGinhDIpa = false;}
      if(wTxDhSUKEM == true){wTxDhSUKEM = false;}
      if(YjIflMlTbI == true){YjIflMlTbI = false;}
      if(caGghdiFmJ == true){caGghdiFmJ = false;}
      if(rtuGtBbcOf == true){rtuGtBbcOf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MVAISAIOMI
{ 
  void qrPELNRTGy()
  { 
      bool GeyJHXZIGp = false;
      bool SButtuiWDs = false;
      bool TdOOMjRRFC = false;
      bool RcXXaLZdSK = false;
      bool QjqapacUrL = false;
      bool qKtyScQiwX = false;
      bool FICDXpdWTh = false;
      bool UFEsbjlmXk = false;
      bool HxYsLHhZFx = false;
      bool upguEHgnDz = false;
      bool xFAKplGBWh = false;
      bool qcLKPIjJrP = false;
      bool HERVleXJnT = false;
      bool DxjXnCwNDY = false;
      bool BgCWGReWeu = false;
      bool WXwmqsmeYL = false;
      bool OwMCdssmVN = false;
      bool LWFSOaBtOT = false;
      bool AAerwfAwfu = false;
      bool ORorKEUzrM = false;
      string rmMGaQhnRR;
      string uMrzDPWuUq;
      string XzjwZlmeAr;
      string kxuSRuOdYd;
      string cueqTTiuzn;
      string FfemjsCPgn;
      string cCnYfxRZgI;
      string ArWqNcTscF;
      string DqfLmFSHhX;
      string ryxjBaGGKV;
      string CIOqmNImYG;
      string ZJmakkVbla;
      string eJqIPCtlpm;
      string VMhHCtcoXZ;
      string weibyhKWzP;
      string EeUjpsRFak;
      string SVxljMbfXp;
      string HfELdAZPJg;
      string qXmZhqryQJ;
      string cXOmGahxql;
      if(rmMGaQhnRR == CIOqmNImYG){GeyJHXZIGp = true;}
      else if(CIOqmNImYG == rmMGaQhnRR){xFAKplGBWh = true;}
      if(uMrzDPWuUq == ZJmakkVbla){SButtuiWDs = true;}
      else if(ZJmakkVbla == uMrzDPWuUq){qcLKPIjJrP = true;}
      if(XzjwZlmeAr == eJqIPCtlpm){TdOOMjRRFC = true;}
      else if(eJqIPCtlpm == XzjwZlmeAr){HERVleXJnT = true;}
      if(kxuSRuOdYd == VMhHCtcoXZ){RcXXaLZdSK = true;}
      else if(VMhHCtcoXZ == kxuSRuOdYd){DxjXnCwNDY = true;}
      if(cueqTTiuzn == weibyhKWzP){QjqapacUrL = true;}
      else if(weibyhKWzP == cueqTTiuzn){BgCWGReWeu = true;}
      if(FfemjsCPgn == EeUjpsRFak){qKtyScQiwX = true;}
      else if(EeUjpsRFak == FfemjsCPgn){WXwmqsmeYL = true;}
      if(cCnYfxRZgI == SVxljMbfXp){FICDXpdWTh = true;}
      else if(SVxljMbfXp == cCnYfxRZgI){OwMCdssmVN = true;}
      if(ArWqNcTscF == HfELdAZPJg){UFEsbjlmXk = true;}
      if(DqfLmFSHhX == qXmZhqryQJ){HxYsLHhZFx = true;}
      if(ryxjBaGGKV == cXOmGahxql){upguEHgnDz = true;}
      while(HfELdAZPJg == ArWqNcTscF){LWFSOaBtOT = true;}
      while(qXmZhqryQJ == qXmZhqryQJ){AAerwfAwfu = true;}
      while(cXOmGahxql == cXOmGahxql){ORorKEUzrM = true;}
      if(GeyJHXZIGp == true){GeyJHXZIGp = false;}
      if(SButtuiWDs == true){SButtuiWDs = false;}
      if(TdOOMjRRFC == true){TdOOMjRRFC = false;}
      if(RcXXaLZdSK == true){RcXXaLZdSK = false;}
      if(QjqapacUrL == true){QjqapacUrL = false;}
      if(qKtyScQiwX == true){qKtyScQiwX = false;}
      if(FICDXpdWTh == true){FICDXpdWTh = false;}
      if(UFEsbjlmXk == true){UFEsbjlmXk = false;}
      if(HxYsLHhZFx == true){HxYsLHhZFx = false;}
      if(upguEHgnDz == true){upguEHgnDz = false;}
      if(xFAKplGBWh == true){xFAKplGBWh = false;}
      if(qcLKPIjJrP == true){qcLKPIjJrP = false;}
      if(HERVleXJnT == true){HERVleXJnT = false;}
      if(DxjXnCwNDY == true){DxjXnCwNDY = false;}
      if(BgCWGReWeu == true){BgCWGReWeu = false;}
      if(WXwmqsmeYL == true){WXwmqsmeYL = false;}
      if(OwMCdssmVN == true){OwMCdssmVN = false;}
      if(LWFSOaBtOT == true){LWFSOaBtOT = false;}
      if(AAerwfAwfu == true){AAerwfAwfu = false;}
      if(ORorKEUzrM == true){ORorKEUzrM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WQIJKYZITT
{ 
  void MYxfhINrOk()
  { 
      bool QRdtWRSouh = false;
      bool HaKXMjROnZ = false;
      bool uIDgarsMID = false;
      bool rWlsDKkBgU = false;
      bool cdPgxyqhmb = false;
      bool AhWUrHNxSe = false;
      bool XGgqpjnQUB = false;
      bool yQgTwQsVib = false;
      bool ALZfDJzRBu = false;
      bool wnhCwWxXqM = false;
      bool KaMkciADXa = false;
      bool OqOqeMgAmf = false;
      bool kVOYEKheWZ = false;
      bool SUeVRZynCT = false;
      bool JutagEYpXj = false;
      bool pxjKbnMnfS = false;
      bool AVfyHsMsZE = false;
      bool NrxTWobmqA = false;
      bool krHmjVjUsc = false;
      bool NKIjSmPuSn = false;
      string inVkVUQpWt;
      string bwZZERLRdV;
      string aayBzBRZzA;
      string IRLPzULhxG;
      string FVKEluOzfI;
      string IXMuCHoUkU;
      string DqqWlKkKZj;
      string FcTXQFQtOE;
      string lRtqqjFPMr;
      string eqwcCNdnSb;
      string JEYwCfEodw;
      string puFfhlxzeB;
      string EUxhENfpUD;
      string abbltgrxnL;
      string fPlPBjkQuQ;
      string QeIQWoHqro;
      string zNTaVOTTlA;
      string szLTVnhggT;
      string cPuElwSKPE;
      string ZBFzLRwLtm;
      if(inVkVUQpWt == JEYwCfEodw){QRdtWRSouh = true;}
      else if(JEYwCfEodw == inVkVUQpWt){KaMkciADXa = true;}
      if(bwZZERLRdV == puFfhlxzeB){HaKXMjROnZ = true;}
      else if(puFfhlxzeB == bwZZERLRdV){OqOqeMgAmf = true;}
      if(aayBzBRZzA == EUxhENfpUD){uIDgarsMID = true;}
      else if(EUxhENfpUD == aayBzBRZzA){kVOYEKheWZ = true;}
      if(IRLPzULhxG == abbltgrxnL){rWlsDKkBgU = true;}
      else if(abbltgrxnL == IRLPzULhxG){SUeVRZynCT = true;}
      if(FVKEluOzfI == fPlPBjkQuQ){cdPgxyqhmb = true;}
      else if(fPlPBjkQuQ == FVKEluOzfI){JutagEYpXj = true;}
      if(IXMuCHoUkU == QeIQWoHqro){AhWUrHNxSe = true;}
      else if(QeIQWoHqro == IXMuCHoUkU){pxjKbnMnfS = true;}
      if(DqqWlKkKZj == zNTaVOTTlA){XGgqpjnQUB = true;}
      else if(zNTaVOTTlA == DqqWlKkKZj){AVfyHsMsZE = true;}
      if(FcTXQFQtOE == szLTVnhggT){yQgTwQsVib = true;}
      if(lRtqqjFPMr == cPuElwSKPE){ALZfDJzRBu = true;}
      if(eqwcCNdnSb == ZBFzLRwLtm){wnhCwWxXqM = true;}
      while(szLTVnhggT == FcTXQFQtOE){NrxTWobmqA = true;}
      while(cPuElwSKPE == cPuElwSKPE){krHmjVjUsc = true;}
      while(ZBFzLRwLtm == ZBFzLRwLtm){NKIjSmPuSn = true;}
      if(QRdtWRSouh == true){QRdtWRSouh = false;}
      if(HaKXMjROnZ == true){HaKXMjROnZ = false;}
      if(uIDgarsMID == true){uIDgarsMID = false;}
      if(rWlsDKkBgU == true){rWlsDKkBgU = false;}
      if(cdPgxyqhmb == true){cdPgxyqhmb = false;}
      if(AhWUrHNxSe == true){AhWUrHNxSe = false;}
      if(XGgqpjnQUB == true){XGgqpjnQUB = false;}
      if(yQgTwQsVib == true){yQgTwQsVib = false;}
      if(ALZfDJzRBu == true){ALZfDJzRBu = false;}
      if(wnhCwWxXqM == true){wnhCwWxXqM = false;}
      if(KaMkciADXa == true){KaMkciADXa = false;}
      if(OqOqeMgAmf == true){OqOqeMgAmf = false;}
      if(kVOYEKheWZ == true){kVOYEKheWZ = false;}
      if(SUeVRZynCT == true){SUeVRZynCT = false;}
      if(JutagEYpXj == true){JutagEYpXj = false;}
      if(pxjKbnMnfS == true){pxjKbnMnfS = false;}
      if(AVfyHsMsZE == true){AVfyHsMsZE = false;}
      if(NrxTWobmqA == true){NrxTWobmqA = false;}
      if(krHmjVjUsc == true){krHmjVjUsc = false;}
      if(NKIjSmPuSn == true){NKIjSmPuSn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KVRLYSMURE
{ 
  void KgYZVLXzAT()
  { 
      bool EnwSJkdizM = false;
      bool cQuIlCrOSs = false;
      bool AjmPqNCZSE = false;
      bool WDcSrGcrZb = false;
      bool XryjcKunsA = false;
      bool JiLjLUAgbw = false;
      bool hEPtpZncQe = false;
      bool ZzoqVIkDlf = false;
      bool SOfStnqrHW = false;
      bool GwPdsSbDtC = false;
      bool WSXOaKtUNC = false;
      bool ixtucTYxzB = false;
      bool iuUsYdjLxD = false;
      bool ghJjJApQqj = false;
      bool tWeEnICUAZ = false;
      bool seDrTaxepx = false;
      bool aiWKVAnJlc = false;
      bool cHFPHLQPFP = false;
      bool aOKXJBeQPh = false;
      bool CLatJKATim = false;
      string rgiRIwiyLg;
      string ikOJymKVwQ;
      string WtSoIpRpSL;
      string KXDctngOUN;
      string fhGrKloIzF;
      string OCeOVxNtIS;
      string dsezWKhlPJ;
      string GwAhjnnaeV;
      string BJqMxIsoGx;
      string ZmFCjmCHVz;
      string ECrozSBwdg;
      string ImOmQUBSBN;
      string RseSjSqxyx;
      string lgFeRyQCMe;
      string GwKYnmXRlO;
      string kjFHhLWZFg;
      string bEyfubhjVS;
      string EzFWHUhGew;
      string tYLjMBayxG;
      string apwfDCxedL;
      if(rgiRIwiyLg == ECrozSBwdg){EnwSJkdizM = true;}
      else if(ECrozSBwdg == rgiRIwiyLg){WSXOaKtUNC = true;}
      if(ikOJymKVwQ == ImOmQUBSBN){cQuIlCrOSs = true;}
      else if(ImOmQUBSBN == ikOJymKVwQ){ixtucTYxzB = true;}
      if(WtSoIpRpSL == RseSjSqxyx){AjmPqNCZSE = true;}
      else if(RseSjSqxyx == WtSoIpRpSL){iuUsYdjLxD = true;}
      if(KXDctngOUN == lgFeRyQCMe){WDcSrGcrZb = true;}
      else if(lgFeRyQCMe == KXDctngOUN){ghJjJApQqj = true;}
      if(fhGrKloIzF == GwKYnmXRlO){XryjcKunsA = true;}
      else if(GwKYnmXRlO == fhGrKloIzF){tWeEnICUAZ = true;}
      if(OCeOVxNtIS == kjFHhLWZFg){JiLjLUAgbw = true;}
      else if(kjFHhLWZFg == OCeOVxNtIS){seDrTaxepx = true;}
      if(dsezWKhlPJ == bEyfubhjVS){hEPtpZncQe = true;}
      else if(bEyfubhjVS == dsezWKhlPJ){aiWKVAnJlc = true;}
      if(GwAhjnnaeV == EzFWHUhGew){ZzoqVIkDlf = true;}
      if(BJqMxIsoGx == tYLjMBayxG){SOfStnqrHW = true;}
      if(ZmFCjmCHVz == apwfDCxedL){GwPdsSbDtC = true;}
      while(EzFWHUhGew == GwAhjnnaeV){cHFPHLQPFP = true;}
      while(tYLjMBayxG == tYLjMBayxG){aOKXJBeQPh = true;}
      while(apwfDCxedL == apwfDCxedL){CLatJKATim = true;}
      if(EnwSJkdizM == true){EnwSJkdizM = false;}
      if(cQuIlCrOSs == true){cQuIlCrOSs = false;}
      if(AjmPqNCZSE == true){AjmPqNCZSE = false;}
      if(WDcSrGcrZb == true){WDcSrGcrZb = false;}
      if(XryjcKunsA == true){XryjcKunsA = false;}
      if(JiLjLUAgbw == true){JiLjLUAgbw = false;}
      if(hEPtpZncQe == true){hEPtpZncQe = false;}
      if(ZzoqVIkDlf == true){ZzoqVIkDlf = false;}
      if(SOfStnqrHW == true){SOfStnqrHW = false;}
      if(GwPdsSbDtC == true){GwPdsSbDtC = false;}
      if(WSXOaKtUNC == true){WSXOaKtUNC = false;}
      if(ixtucTYxzB == true){ixtucTYxzB = false;}
      if(iuUsYdjLxD == true){iuUsYdjLxD = false;}
      if(ghJjJApQqj == true){ghJjJApQqj = false;}
      if(tWeEnICUAZ == true){tWeEnICUAZ = false;}
      if(seDrTaxepx == true){seDrTaxepx = false;}
      if(aiWKVAnJlc == true){aiWKVAnJlc = false;}
      if(cHFPHLQPFP == true){cHFPHLQPFP = false;}
      if(aOKXJBeQPh == true){aOKXJBeQPh = false;}
      if(CLatJKATim == true){CLatJKATim = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LMQILDUNTP
{ 
  void UPVdgVUOWW()
  { 
      bool KGdRRkkpTQ = false;
      bool imBxLjeyQG = false;
      bool dRlmXAcfMG = false;
      bool xkLqzRsjKf = false;
      bool TxcDbenDJa = false;
      bool gKlZzsUpsR = false;
      bool IEcNSxbKyt = false;
      bool punkmgniKs = false;
      bool MYWlZlzkqG = false;
      bool wDqsXOTPje = false;
      bool CcFPjlWBlS = false;
      bool EleAFjhqng = false;
      bool ypSrxmDtNX = false;
      bool MYyfpiTGBm = false;
      bool PxzXBJXqnm = false;
      bool gcbDfLJMRw = false;
      bool hbnNGfmzJV = false;
      bool PaoAQAqtpn = false;
      bool PMGZqiwuzd = false;
      bool YGoFFmJkRV = false;
      string qWFXOWhUMl;
      string kZRLRGoKKU;
      string LWlDHKSxnw;
      string lAykhJLbBP;
      string lZSAyZwRyO;
      string VAFxoUkCQD;
      string EkfQzkbfdI;
      string tMIuhkDkFh;
      string OByZaltAwM;
      string YJLxLBsCAN;
      string yPnpUIrKOD;
      string RzxhoDlGoN;
      string pajQikAKjf;
      string rAjqiyMIER;
      string tjlruZMcIH;
      string OmMmWXfWHj;
      string HgahLQOFzq;
      string pdBWSGnrUJ;
      string XXBbREmxTL;
      string SpBUKMJDfd;
      if(qWFXOWhUMl == yPnpUIrKOD){KGdRRkkpTQ = true;}
      else if(yPnpUIrKOD == qWFXOWhUMl){CcFPjlWBlS = true;}
      if(kZRLRGoKKU == RzxhoDlGoN){imBxLjeyQG = true;}
      else if(RzxhoDlGoN == kZRLRGoKKU){EleAFjhqng = true;}
      if(LWlDHKSxnw == pajQikAKjf){dRlmXAcfMG = true;}
      else if(pajQikAKjf == LWlDHKSxnw){ypSrxmDtNX = true;}
      if(lAykhJLbBP == rAjqiyMIER){xkLqzRsjKf = true;}
      else if(rAjqiyMIER == lAykhJLbBP){MYyfpiTGBm = true;}
      if(lZSAyZwRyO == tjlruZMcIH){TxcDbenDJa = true;}
      else if(tjlruZMcIH == lZSAyZwRyO){PxzXBJXqnm = true;}
      if(VAFxoUkCQD == OmMmWXfWHj){gKlZzsUpsR = true;}
      else if(OmMmWXfWHj == VAFxoUkCQD){gcbDfLJMRw = true;}
      if(EkfQzkbfdI == HgahLQOFzq){IEcNSxbKyt = true;}
      else if(HgahLQOFzq == EkfQzkbfdI){hbnNGfmzJV = true;}
      if(tMIuhkDkFh == pdBWSGnrUJ){punkmgniKs = true;}
      if(OByZaltAwM == XXBbREmxTL){MYWlZlzkqG = true;}
      if(YJLxLBsCAN == SpBUKMJDfd){wDqsXOTPje = true;}
      while(pdBWSGnrUJ == tMIuhkDkFh){PaoAQAqtpn = true;}
      while(XXBbREmxTL == XXBbREmxTL){PMGZqiwuzd = true;}
      while(SpBUKMJDfd == SpBUKMJDfd){YGoFFmJkRV = true;}
      if(KGdRRkkpTQ == true){KGdRRkkpTQ = false;}
      if(imBxLjeyQG == true){imBxLjeyQG = false;}
      if(dRlmXAcfMG == true){dRlmXAcfMG = false;}
      if(xkLqzRsjKf == true){xkLqzRsjKf = false;}
      if(TxcDbenDJa == true){TxcDbenDJa = false;}
      if(gKlZzsUpsR == true){gKlZzsUpsR = false;}
      if(IEcNSxbKyt == true){IEcNSxbKyt = false;}
      if(punkmgniKs == true){punkmgniKs = false;}
      if(MYWlZlzkqG == true){MYWlZlzkqG = false;}
      if(wDqsXOTPje == true){wDqsXOTPje = false;}
      if(CcFPjlWBlS == true){CcFPjlWBlS = false;}
      if(EleAFjhqng == true){EleAFjhqng = false;}
      if(ypSrxmDtNX == true){ypSrxmDtNX = false;}
      if(MYyfpiTGBm == true){MYyfpiTGBm = false;}
      if(PxzXBJXqnm == true){PxzXBJXqnm = false;}
      if(gcbDfLJMRw == true){gcbDfLJMRw = false;}
      if(hbnNGfmzJV == true){hbnNGfmzJV = false;}
      if(PaoAQAqtpn == true){PaoAQAqtpn = false;}
      if(PMGZqiwuzd == true){PMGZqiwuzd = false;}
      if(YGoFFmJkRV == true){YGoFFmJkRV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DINTYEZVIS
{ 
  void WcaslpjaDu()
  { 
      bool sQdQjBnTwc = false;
      bool rbjKQblcaM = false;
      bool ouOkWozzLY = false;
      bool xTbBsXKbru = false;
      bool IVlVluSaSa = false;
      bool oXRPcxBrst = false;
      bool CoHWfXziRs = false;
      bool QKjeDSIsza = false;
      bool VXfkiZBMYw = false;
      bool VShxrTOOpN = false;
      bool wjJZJemlLJ = false;
      bool nIsSYdIVnG = false;
      bool VmKUWybmlj = false;
      bool DtCkelNGbD = false;
      bool lPAOHNZOYO = false;
      bool LrajqIYoDK = false;
      bool DzzbFtFHnl = false;
      bool QCtjTGlwNJ = false;
      bool YMOXXKSSsV = false;
      bool NYDQAmPYIN = false;
      string zdoGfaIHrY;
      string YZOFXwdsgS;
      string sHhytFDtWq;
      string eGZHqeKDhz;
      string XdRyufdeBK;
      string YrqCrruqMZ;
      string XOjAsRzGNs;
      string lZKgtOojDN;
      string bXrMSmOXPz;
      string iSqIbJtQEc;
      string fXRIXygJHd;
      string CKnyyzVWhG;
      string CbqOKShCFj;
      string TXfZhEGjnT;
      string FFPlwXesKc;
      string mWhxaDfCxE;
      string QdEXJeeNPt;
      string rliOAxLESl;
      string nnrbwxoizd;
      string XDliCbArbR;
      if(zdoGfaIHrY == fXRIXygJHd){sQdQjBnTwc = true;}
      else if(fXRIXygJHd == zdoGfaIHrY){wjJZJemlLJ = true;}
      if(YZOFXwdsgS == CKnyyzVWhG){rbjKQblcaM = true;}
      else if(CKnyyzVWhG == YZOFXwdsgS){nIsSYdIVnG = true;}
      if(sHhytFDtWq == CbqOKShCFj){ouOkWozzLY = true;}
      else if(CbqOKShCFj == sHhytFDtWq){VmKUWybmlj = true;}
      if(eGZHqeKDhz == TXfZhEGjnT){xTbBsXKbru = true;}
      else if(TXfZhEGjnT == eGZHqeKDhz){DtCkelNGbD = true;}
      if(XdRyufdeBK == FFPlwXesKc){IVlVluSaSa = true;}
      else if(FFPlwXesKc == XdRyufdeBK){lPAOHNZOYO = true;}
      if(YrqCrruqMZ == mWhxaDfCxE){oXRPcxBrst = true;}
      else if(mWhxaDfCxE == YrqCrruqMZ){LrajqIYoDK = true;}
      if(XOjAsRzGNs == QdEXJeeNPt){CoHWfXziRs = true;}
      else if(QdEXJeeNPt == XOjAsRzGNs){DzzbFtFHnl = true;}
      if(lZKgtOojDN == rliOAxLESl){QKjeDSIsza = true;}
      if(bXrMSmOXPz == nnrbwxoizd){VXfkiZBMYw = true;}
      if(iSqIbJtQEc == XDliCbArbR){VShxrTOOpN = true;}
      while(rliOAxLESl == lZKgtOojDN){QCtjTGlwNJ = true;}
      while(nnrbwxoizd == nnrbwxoizd){YMOXXKSSsV = true;}
      while(XDliCbArbR == XDliCbArbR){NYDQAmPYIN = true;}
      if(sQdQjBnTwc == true){sQdQjBnTwc = false;}
      if(rbjKQblcaM == true){rbjKQblcaM = false;}
      if(ouOkWozzLY == true){ouOkWozzLY = false;}
      if(xTbBsXKbru == true){xTbBsXKbru = false;}
      if(IVlVluSaSa == true){IVlVluSaSa = false;}
      if(oXRPcxBrst == true){oXRPcxBrst = false;}
      if(CoHWfXziRs == true){CoHWfXziRs = false;}
      if(QKjeDSIsza == true){QKjeDSIsza = false;}
      if(VXfkiZBMYw == true){VXfkiZBMYw = false;}
      if(VShxrTOOpN == true){VShxrTOOpN = false;}
      if(wjJZJemlLJ == true){wjJZJemlLJ = false;}
      if(nIsSYdIVnG == true){nIsSYdIVnG = false;}
      if(VmKUWybmlj == true){VmKUWybmlj = false;}
      if(DtCkelNGbD == true){DtCkelNGbD = false;}
      if(lPAOHNZOYO == true){lPAOHNZOYO = false;}
      if(LrajqIYoDK == true){LrajqIYoDK = false;}
      if(DzzbFtFHnl == true){DzzbFtFHnl = false;}
      if(QCtjTGlwNJ == true){QCtjTGlwNJ = false;}
      if(YMOXXKSSsV == true){YMOXXKSSsV = false;}
      if(NYDQAmPYIN == true){NYDQAmPYIN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FTDQEIMCIT
{ 
  void ejxoxfgVaf()
  { 
      bool orRqDSDKio = false;
      bool xMnIPhesiI = false;
      bool ObgMbnDhXA = false;
      bool REddeuMXgO = false;
      bool QJdSwJuBoe = false;
      bool VlqoTNKFPO = false;
      bool OUlhWriJdT = false;
      bool VGLUqExOPR = false;
      bool sCsseeNoKQ = false;
      bool jHIRzwXwuE = false;
      bool alWUIPZWxO = false;
      bool QwoxVLbrDr = false;
      bool dsyMjOxtUu = false;
      bool gBSKqHfXkP = false;
      bool FqquAnRLun = false;
      bool UfsDZgmJkt = false;
      bool RfCBhOcdFO = false;
      bool fDHmlmCDMu = false;
      bool wlyfaBIPkK = false;
      bool TVlpxYopNl = false;
      string mZBxgQUQsA;
      string giYdwUrXzw;
      string NUIgDRrEny;
      string FdtEihjrQG;
      string zOActkMboI;
      string MIgZnSRUtP;
      string XQbutCnTuN;
      string jzHrwyUflR;
      string EQOfkxxTQP;
      string PPyBhhmEhr;
      string wrfaXMBndo;
      string ylibKHBwJx;
      string FUDeyUBGKN;
      string LPxtVLjmIY;
      string uIpaRdgWpZ;
      string gqujlboBcD;
      string LucPdinoFy;
      string WNmkBxebNT;
      string mdPjgUTMHs;
      string WiKEMAeZxi;
      if(mZBxgQUQsA == wrfaXMBndo){orRqDSDKio = true;}
      else if(wrfaXMBndo == mZBxgQUQsA){alWUIPZWxO = true;}
      if(giYdwUrXzw == ylibKHBwJx){xMnIPhesiI = true;}
      else if(ylibKHBwJx == giYdwUrXzw){QwoxVLbrDr = true;}
      if(NUIgDRrEny == FUDeyUBGKN){ObgMbnDhXA = true;}
      else if(FUDeyUBGKN == NUIgDRrEny){dsyMjOxtUu = true;}
      if(FdtEihjrQG == LPxtVLjmIY){REddeuMXgO = true;}
      else if(LPxtVLjmIY == FdtEihjrQG){gBSKqHfXkP = true;}
      if(zOActkMboI == uIpaRdgWpZ){QJdSwJuBoe = true;}
      else if(uIpaRdgWpZ == zOActkMboI){FqquAnRLun = true;}
      if(MIgZnSRUtP == gqujlboBcD){VlqoTNKFPO = true;}
      else if(gqujlboBcD == MIgZnSRUtP){UfsDZgmJkt = true;}
      if(XQbutCnTuN == LucPdinoFy){OUlhWriJdT = true;}
      else if(LucPdinoFy == XQbutCnTuN){RfCBhOcdFO = true;}
      if(jzHrwyUflR == WNmkBxebNT){VGLUqExOPR = true;}
      if(EQOfkxxTQP == mdPjgUTMHs){sCsseeNoKQ = true;}
      if(PPyBhhmEhr == WiKEMAeZxi){jHIRzwXwuE = true;}
      while(WNmkBxebNT == jzHrwyUflR){fDHmlmCDMu = true;}
      while(mdPjgUTMHs == mdPjgUTMHs){wlyfaBIPkK = true;}
      while(WiKEMAeZxi == WiKEMAeZxi){TVlpxYopNl = true;}
      if(orRqDSDKio == true){orRqDSDKio = false;}
      if(xMnIPhesiI == true){xMnIPhesiI = false;}
      if(ObgMbnDhXA == true){ObgMbnDhXA = false;}
      if(REddeuMXgO == true){REddeuMXgO = false;}
      if(QJdSwJuBoe == true){QJdSwJuBoe = false;}
      if(VlqoTNKFPO == true){VlqoTNKFPO = false;}
      if(OUlhWriJdT == true){OUlhWriJdT = false;}
      if(VGLUqExOPR == true){VGLUqExOPR = false;}
      if(sCsseeNoKQ == true){sCsseeNoKQ = false;}
      if(jHIRzwXwuE == true){jHIRzwXwuE = false;}
      if(alWUIPZWxO == true){alWUIPZWxO = false;}
      if(QwoxVLbrDr == true){QwoxVLbrDr = false;}
      if(dsyMjOxtUu == true){dsyMjOxtUu = false;}
      if(gBSKqHfXkP == true){gBSKqHfXkP = false;}
      if(FqquAnRLun == true){FqquAnRLun = false;}
      if(UfsDZgmJkt == true){UfsDZgmJkt = false;}
      if(RfCBhOcdFO == true){RfCBhOcdFO = false;}
      if(fDHmlmCDMu == true){fDHmlmCDMu = false;}
      if(wlyfaBIPkK == true){wlyfaBIPkK = false;}
      if(TVlpxYopNl == true){TVlpxYopNl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBYOIFJCFU
{ 
  void RsdTqgmPgG()
  { 
      bool ruSldauXXb = false;
      bool EuVzmBMicz = false;
      bool TSzpoINHQV = false;
      bool cdAlnZuWyp = false;
      bool lLJCCLdiXt = false;
      bool zCbfAYwbxV = false;
      bool MnGCzatjKN = false;
      bool GpjlNIIwnc = false;
      bool ddiWVZBTlO = false;
      bool cSYccyFHCa = false;
      bool QtYKnJRoSr = false;
      bool QznTqiFjgZ = false;
      bool YZxwjmQHJP = false;
      bool CBtMLiFXiL = false;
      bool HMBtxdeEkt = false;
      bool sUZcBqxbZA = false;
      bool sKeDoPFbHI = false;
      bool cgBVRMYDyG = false;
      bool ILWPVhaQKU = false;
      bool lcxhSxgxFh = false;
      string UEVNBjLAKe;
      string MKNcwIGAal;
      string LQABERQhpi;
      string PgsYBmqTwp;
      string MMkmfmLhOT;
      string fSKJeEDTJi;
      string SdJbOfRobJ;
      string RmEkYzeNUQ;
      string FhSWDxVjsx;
      string iXJMWiCJXA;
      string VWGFCrNZje;
      string YpysdjKmXR;
      string KhudZtdqOo;
      string xUoUuhbNTK;
      string iwzOXsYQhl;
      string XOkGpmbbeI;
      string OVKthDBdxu;
      string IwSNhNhgGf;
      string UNJbRhjheH;
      string GAiLwMkEfT;
      if(UEVNBjLAKe == VWGFCrNZje){ruSldauXXb = true;}
      else if(VWGFCrNZje == UEVNBjLAKe){QtYKnJRoSr = true;}
      if(MKNcwIGAal == YpysdjKmXR){EuVzmBMicz = true;}
      else if(YpysdjKmXR == MKNcwIGAal){QznTqiFjgZ = true;}
      if(LQABERQhpi == KhudZtdqOo){TSzpoINHQV = true;}
      else if(KhudZtdqOo == LQABERQhpi){YZxwjmQHJP = true;}
      if(PgsYBmqTwp == xUoUuhbNTK){cdAlnZuWyp = true;}
      else if(xUoUuhbNTK == PgsYBmqTwp){CBtMLiFXiL = true;}
      if(MMkmfmLhOT == iwzOXsYQhl){lLJCCLdiXt = true;}
      else if(iwzOXsYQhl == MMkmfmLhOT){HMBtxdeEkt = true;}
      if(fSKJeEDTJi == XOkGpmbbeI){zCbfAYwbxV = true;}
      else if(XOkGpmbbeI == fSKJeEDTJi){sUZcBqxbZA = true;}
      if(SdJbOfRobJ == OVKthDBdxu){MnGCzatjKN = true;}
      else if(OVKthDBdxu == SdJbOfRobJ){sKeDoPFbHI = true;}
      if(RmEkYzeNUQ == IwSNhNhgGf){GpjlNIIwnc = true;}
      if(FhSWDxVjsx == UNJbRhjheH){ddiWVZBTlO = true;}
      if(iXJMWiCJXA == GAiLwMkEfT){cSYccyFHCa = true;}
      while(IwSNhNhgGf == RmEkYzeNUQ){cgBVRMYDyG = true;}
      while(UNJbRhjheH == UNJbRhjheH){ILWPVhaQKU = true;}
      while(GAiLwMkEfT == GAiLwMkEfT){lcxhSxgxFh = true;}
      if(ruSldauXXb == true){ruSldauXXb = false;}
      if(EuVzmBMicz == true){EuVzmBMicz = false;}
      if(TSzpoINHQV == true){TSzpoINHQV = false;}
      if(cdAlnZuWyp == true){cdAlnZuWyp = false;}
      if(lLJCCLdiXt == true){lLJCCLdiXt = false;}
      if(zCbfAYwbxV == true){zCbfAYwbxV = false;}
      if(MnGCzatjKN == true){MnGCzatjKN = false;}
      if(GpjlNIIwnc == true){GpjlNIIwnc = false;}
      if(ddiWVZBTlO == true){ddiWVZBTlO = false;}
      if(cSYccyFHCa == true){cSYccyFHCa = false;}
      if(QtYKnJRoSr == true){QtYKnJRoSr = false;}
      if(QznTqiFjgZ == true){QznTqiFjgZ = false;}
      if(YZxwjmQHJP == true){YZxwjmQHJP = false;}
      if(CBtMLiFXiL == true){CBtMLiFXiL = false;}
      if(HMBtxdeEkt == true){HMBtxdeEkt = false;}
      if(sUZcBqxbZA == true){sUZcBqxbZA = false;}
      if(sKeDoPFbHI == true){sKeDoPFbHI = false;}
      if(cgBVRMYDyG == true){cgBVRMYDyG = false;}
      if(ILWPVhaQKU == true){ILWPVhaQKU = false;}
      if(lcxhSxgxFh == true){lcxhSxgxFh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCMNTWDYBR
{ 
  void hPIMDOZmHZ()
  { 
      bool ZNOZEYyUCh = false;
      bool YHLATlzZDA = false;
      bool BKgKllwLfx = false;
      bool TSREIVOANy = false;
      bool ljwdVoNCQG = false;
      bool UNUmCOgEnR = false;
      bool bloENFoGqx = false;
      bool XzLENQNCnw = false;
      bool YsuZcFydCs = false;
      bool oKLwVAurPP = false;
      bool zGLSiUBPZk = false;
      bool AdPrshqPbI = false;
      bool HLExIMmPhN = false;
      bool VVmYwRhbpH = false;
      bool DhEQrLtTCm = false;
      bool IfQHInCNKV = false;
      bool hlgMPeppua = false;
      bool APYTEYGmEx = false;
      bool SSMtEpFfQH = false;
      bool OURUZRArBN = false;
      string QmPAMtnbEe;
      string lzeYXGosPi;
      string BpGwXOGQMH;
      string JqrMosRKDJ;
      string erUEVKKXeg;
      string oBhYXZfSby;
      string nWOxVuHSie;
      string odpFDIVCaN;
      string DhlfRHISnO;
      string MzhEVIdXia;
      string DrnArKLcUP;
      string EdrOuFkieN;
      string lndTRpwkju;
      string exTzJLskmG;
      string ufxYKiGTJQ;
      string XtrUnONUhC;
      string OarZjGJrEi;
      string LzwXSGpFJh;
      string icaSWjEzLt;
      string xYCjrUmXnE;
      if(QmPAMtnbEe == DrnArKLcUP){ZNOZEYyUCh = true;}
      else if(DrnArKLcUP == QmPAMtnbEe){zGLSiUBPZk = true;}
      if(lzeYXGosPi == EdrOuFkieN){YHLATlzZDA = true;}
      else if(EdrOuFkieN == lzeYXGosPi){AdPrshqPbI = true;}
      if(BpGwXOGQMH == lndTRpwkju){BKgKllwLfx = true;}
      else if(lndTRpwkju == BpGwXOGQMH){HLExIMmPhN = true;}
      if(JqrMosRKDJ == exTzJLskmG){TSREIVOANy = true;}
      else if(exTzJLskmG == JqrMosRKDJ){VVmYwRhbpH = true;}
      if(erUEVKKXeg == ufxYKiGTJQ){ljwdVoNCQG = true;}
      else if(ufxYKiGTJQ == erUEVKKXeg){DhEQrLtTCm = true;}
      if(oBhYXZfSby == XtrUnONUhC){UNUmCOgEnR = true;}
      else if(XtrUnONUhC == oBhYXZfSby){IfQHInCNKV = true;}
      if(nWOxVuHSie == OarZjGJrEi){bloENFoGqx = true;}
      else if(OarZjGJrEi == nWOxVuHSie){hlgMPeppua = true;}
      if(odpFDIVCaN == LzwXSGpFJh){XzLENQNCnw = true;}
      if(DhlfRHISnO == icaSWjEzLt){YsuZcFydCs = true;}
      if(MzhEVIdXia == xYCjrUmXnE){oKLwVAurPP = true;}
      while(LzwXSGpFJh == odpFDIVCaN){APYTEYGmEx = true;}
      while(icaSWjEzLt == icaSWjEzLt){SSMtEpFfQH = true;}
      while(xYCjrUmXnE == xYCjrUmXnE){OURUZRArBN = true;}
      if(ZNOZEYyUCh == true){ZNOZEYyUCh = false;}
      if(YHLATlzZDA == true){YHLATlzZDA = false;}
      if(BKgKllwLfx == true){BKgKllwLfx = false;}
      if(TSREIVOANy == true){TSREIVOANy = false;}
      if(ljwdVoNCQG == true){ljwdVoNCQG = false;}
      if(UNUmCOgEnR == true){UNUmCOgEnR = false;}
      if(bloENFoGqx == true){bloENFoGqx = false;}
      if(XzLENQNCnw == true){XzLENQNCnw = false;}
      if(YsuZcFydCs == true){YsuZcFydCs = false;}
      if(oKLwVAurPP == true){oKLwVAurPP = false;}
      if(zGLSiUBPZk == true){zGLSiUBPZk = false;}
      if(AdPrshqPbI == true){AdPrshqPbI = false;}
      if(HLExIMmPhN == true){HLExIMmPhN = false;}
      if(VVmYwRhbpH == true){VVmYwRhbpH = false;}
      if(DhEQrLtTCm == true){DhEQrLtTCm = false;}
      if(IfQHInCNKV == true){IfQHInCNKV = false;}
      if(hlgMPeppua == true){hlgMPeppua = false;}
      if(APYTEYGmEx == true){APYTEYGmEx = false;}
      if(SSMtEpFfQH == true){SSMtEpFfQH = false;}
      if(OURUZRArBN == true){OURUZRArBN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class URRDEKNRSD
{ 
  void mycNYcVjlw()
  { 
      bool SuDBqiPstk = false;
      bool UrhlYEDBlY = false;
      bool ullMNqNeOE = false;
      bool CeosSQXoOn = false;
      bool JgaXLursHK = false;
      bool lueVFgIpnA = false;
      bool VkeohpDoSH = false;
      bool fOmyONLNBR = false;
      bool yTWDRGzTnl = false;
      bool IhBNRYCkoU = false;
      bool rDZAdXIfGq = false;
      bool UuoVBBNaXb = false;
      bool piAgzyMZgo = false;
      bool KaXfZutWZs = false;
      bool ySNwQMreMQ = false;
      bool LbMNeICsAe = false;
      bool KizQftWJwF = false;
      bool HqBdcXUEPl = false;
      bool GhMPdiNJBQ = false;
      bool sAWthPSxQV = false;
      string aBkewBGNrl;
      string TcWFmppeeg;
      string uOFJtEnWcT;
      string fmSzBlHaOo;
      string IoUaXCeukW;
      string TFLhFMuakr;
      string MijYFgKXDB;
      string hOQpYFsekq;
      string YslGzZaksn;
      string pfpVbYFwUq;
      string rHqinEoVIz;
      string SQosSTwdYf;
      string FYdOKCYtNz;
      string AxJtzRCDSu;
      string kFbsVZpxDI;
      string baWokScbXk;
      string ftHJzVGusB;
      string QsLdtAxjsk;
      string MaqFWZZUIg;
      string nZfgOpxRtA;
      if(aBkewBGNrl == rHqinEoVIz){SuDBqiPstk = true;}
      else if(rHqinEoVIz == aBkewBGNrl){rDZAdXIfGq = true;}
      if(TcWFmppeeg == SQosSTwdYf){UrhlYEDBlY = true;}
      else if(SQosSTwdYf == TcWFmppeeg){UuoVBBNaXb = true;}
      if(uOFJtEnWcT == FYdOKCYtNz){ullMNqNeOE = true;}
      else if(FYdOKCYtNz == uOFJtEnWcT){piAgzyMZgo = true;}
      if(fmSzBlHaOo == AxJtzRCDSu){CeosSQXoOn = true;}
      else if(AxJtzRCDSu == fmSzBlHaOo){KaXfZutWZs = true;}
      if(IoUaXCeukW == kFbsVZpxDI){JgaXLursHK = true;}
      else if(kFbsVZpxDI == IoUaXCeukW){ySNwQMreMQ = true;}
      if(TFLhFMuakr == baWokScbXk){lueVFgIpnA = true;}
      else if(baWokScbXk == TFLhFMuakr){LbMNeICsAe = true;}
      if(MijYFgKXDB == ftHJzVGusB){VkeohpDoSH = true;}
      else if(ftHJzVGusB == MijYFgKXDB){KizQftWJwF = true;}
      if(hOQpYFsekq == QsLdtAxjsk){fOmyONLNBR = true;}
      if(YslGzZaksn == MaqFWZZUIg){yTWDRGzTnl = true;}
      if(pfpVbYFwUq == nZfgOpxRtA){IhBNRYCkoU = true;}
      while(QsLdtAxjsk == hOQpYFsekq){HqBdcXUEPl = true;}
      while(MaqFWZZUIg == MaqFWZZUIg){GhMPdiNJBQ = true;}
      while(nZfgOpxRtA == nZfgOpxRtA){sAWthPSxQV = true;}
      if(SuDBqiPstk == true){SuDBqiPstk = false;}
      if(UrhlYEDBlY == true){UrhlYEDBlY = false;}
      if(ullMNqNeOE == true){ullMNqNeOE = false;}
      if(CeosSQXoOn == true){CeosSQXoOn = false;}
      if(JgaXLursHK == true){JgaXLursHK = false;}
      if(lueVFgIpnA == true){lueVFgIpnA = false;}
      if(VkeohpDoSH == true){VkeohpDoSH = false;}
      if(fOmyONLNBR == true){fOmyONLNBR = false;}
      if(yTWDRGzTnl == true){yTWDRGzTnl = false;}
      if(IhBNRYCkoU == true){IhBNRYCkoU = false;}
      if(rDZAdXIfGq == true){rDZAdXIfGq = false;}
      if(UuoVBBNaXb == true){UuoVBBNaXb = false;}
      if(piAgzyMZgo == true){piAgzyMZgo = false;}
      if(KaXfZutWZs == true){KaXfZutWZs = false;}
      if(ySNwQMreMQ == true){ySNwQMreMQ = false;}
      if(LbMNeICsAe == true){LbMNeICsAe = false;}
      if(KizQftWJwF == true){KizQftWJwF = false;}
      if(HqBdcXUEPl == true){HqBdcXUEPl = false;}
      if(GhMPdiNJBQ == true){GhMPdiNJBQ = false;}
      if(sAWthPSxQV == true){sAWthPSxQV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GPBCMJOTLY
{ 
  void NkBbWtqaat()
  { 
      bool bRRyoidiFU = false;
      bool tDWLarbtaL = false;
      bool kLstUpcLQx = false;
      bool ChxVupoVhG = false;
      bool FprBJloDNP = false;
      bool hYLBaPYWdy = false;
      bool GSSHRLFBPk = false;
      bool CGMTGtSrjh = false;
      bool BYyAOcVute = false;
      bool RRqiAmXkiy = false;
      bool fmncNbMrug = false;
      bool xfmuwgTRro = false;
      bool oJHjSjOdST = false;
      bool WhIlCOkUmm = false;
      bool QdANhkeulT = false;
      bool SGrtIWeDJc = false;
      bool MhZaKPXAsg = false;
      bool uzdFXLItCh = false;
      bool FSqyAPoOde = false;
      bool ihKKZhEYDS = false;
      string ckakKQjrGJ;
      string EWnEoBNXqn;
      string sNWkKKQBWA;
      string JdJyfWAIWN;
      string CZseZBXkKZ;
      string ZaKVdOOoaA;
      string AiVGzaNoYR;
      string BEAclTUrLI;
      string leqwaiSnUR;
      string IKhWNTDmey;
      string niMrYUagjK;
      string sWcRNUqYeQ;
      string HYUGJpWdPS;
      string PhMMTDRyXG;
      string HkDJXlhPIr;
      string beHOqPOFii;
      string yxRQuLJPyJ;
      string CrAYIVUKhX;
      string IGUWpjZyVE;
      string oLPnHKTmNM;
      if(ckakKQjrGJ == niMrYUagjK){bRRyoidiFU = true;}
      else if(niMrYUagjK == ckakKQjrGJ){fmncNbMrug = true;}
      if(EWnEoBNXqn == sWcRNUqYeQ){tDWLarbtaL = true;}
      else if(sWcRNUqYeQ == EWnEoBNXqn){xfmuwgTRro = true;}
      if(sNWkKKQBWA == HYUGJpWdPS){kLstUpcLQx = true;}
      else if(HYUGJpWdPS == sNWkKKQBWA){oJHjSjOdST = true;}
      if(JdJyfWAIWN == PhMMTDRyXG){ChxVupoVhG = true;}
      else if(PhMMTDRyXG == JdJyfWAIWN){WhIlCOkUmm = true;}
      if(CZseZBXkKZ == HkDJXlhPIr){FprBJloDNP = true;}
      else if(HkDJXlhPIr == CZseZBXkKZ){QdANhkeulT = true;}
      if(ZaKVdOOoaA == beHOqPOFii){hYLBaPYWdy = true;}
      else if(beHOqPOFii == ZaKVdOOoaA){SGrtIWeDJc = true;}
      if(AiVGzaNoYR == yxRQuLJPyJ){GSSHRLFBPk = true;}
      else if(yxRQuLJPyJ == AiVGzaNoYR){MhZaKPXAsg = true;}
      if(BEAclTUrLI == CrAYIVUKhX){CGMTGtSrjh = true;}
      if(leqwaiSnUR == IGUWpjZyVE){BYyAOcVute = true;}
      if(IKhWNTDmey == oLPnHKTmNM){RRqiAmXkiy = true;}
      while(CrAYIVUKhX == BEAclTUrLI){uzdFXLItCh = true;}
      while(IGUWpjZyVE == IGUWpjZyVE){FSqyAPoOde = true;}
      while(oLPnHKTmNM == oLPnHKTmNM){ihKKZhEYDS = true;}
      if(bRRyoidiFU == true){bRRyoidiFU = false;}
      if(tDWLarbtaL == true){tDWLarbtaL = false;}
      if(kLstUpcLQx == true){kLstUpcLQx = false;}
      if(ChxVupoVhG == true){ChxVupoVhG = false;}
      if(FprBJloDNP == true){FprBJloDNP = false;}
      if(hYLBaPYWdy == true){hYLBaPYWdy = false;}
      if(GSSHRLFBPk == true){GSSHRLFBPk = false;}
      if(CGMTGtSrjh == true){CGMTGtSrjh = false;}
      if(BYyAOcVute == true){BYyAOcVute = false;}
      if(RRqiAmXkiy == true){RRqiAmXkiy = false;}
      if(fmncNbMrug == true){fmncNbMrug = false;}
      if(xfmuwgTRro == true){xfmuwgTRro = false;}
      if(oJHjSjOdST == true){oJHjSjOdST = false;}
      if(WhIlCOkUmm == true){WhIlCOkUmm = false;}
      if(QdANhkeulT == true){QdANhkeulT = false;}
      if(SGrtIWeDJc == true){SGrtIWeDJc = false;}
      if(MhZaKPXAsg == true){MhZaKPXAsg = false;}
      if(uzdFXLItCh == true){uzdFXLItCh = false;}
      if(FSqyAPoOde == true){FSqyAPoOde = false;}
      if(ihKKZhEYDS == true){ihKKZhEYDS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GHXPZZJUZZ
{ 
  void nBMssHTUGn()
  { 
      bool TgDYZRoiaU = false;
      bool FjqVjFWbEF = false;
      bool omoIrfCUBX = false;
      bool YdisQFBmOM = false;
      bool qwrhAhkIeW = false;
      bool MtaNdfrtfs = false;
      bool OUgDwaBxEe = false;
      bool DjMrNrtHHK = false;
      bool utodLdDUPj = false;
      bool NGGUxVOolY = false;
      bool fmDATbghzk = false;
      bool lkmUyUfDqR = false;
      bool XfhURwcruq = false;
      bool dFUidHqoKi = false;
      bool wVUdycTlWc = false;
      bool pKxTBzFiiW = false;
      bool yomHHfPEpq = false;
      bool dqrIUCLDVo = false;
      bool cqURBSIAge = false;
      bool BHGnjHiMWS = false;
      string QSojYIbxKt;
      string HaIezJRLkY;
      string piuOrHkKEZ;
      string WCcyfFLsQs;
      string gmNhAkGCJi;
      string FYdDwgWZqQ;
      string WRrkXFxKys;
      string yYurrCUNOH;
      string BiAVTxXZBz;
      string ikBzVPucKu;
      string mwDQjgdlLt;
      string LJLiPnQVQa;
      string gXJzKMWuVb;
      string GrCSUEfjlm;
      string SlOGmZZRjh;
      string yZMiOOmDGW;
      string KiPimTGrOK;
      string IgjdHtJCMj;
      string lELndgeTDF;
      string RbdPbjVeTS;
      if(QSojYIbxKt == mwDQjgdlLt){TgDYZRoiaU = true;}
      else if(mwDQjgdlLt == QSojYIbxKt){fmDATbghzk = true;}
      if(HaIezJRLkY == LJLiPnQVQa){FjqVjFWbEF = true;}
      else if(LJLiPnQVQa == HaIezJRLkY){lkmUyUfDqR = true;}
      if(piuOrHkKEZ == gXJzKMWuVb){omoIrfCUBX = true;}
      else if(gXJzKMWuVb == piuOrHkKEZ){XfhURwcruq = true;}
      if(WCcyfFLsQs == GrCSUEfjlm){YdisQFBmOM = true;}
      else if(GrCSUEfjlm == WCcyfFLsQs){dFUidHqoKi = true;}
      if(gmNhAkGCJi == SlOGmZZRjh){qwrhAhkIeW = true;}
      else if(SlOGmZZRjh == gmNhAkGCJi){wVUdycTlWc = true;}
      if(FYdDwgWZqQ == yZMiOOmDGW){MtaNdfrtfs = true;}
      else if(yZMiOOmDGW == FYdDwgWZqQ){pKxTBzFiiW = true;}
      if(WRrkXFxKys == KiPimTGrOK){OUgDwaBxEe = true;}
      else if(KiPimTGrOK == WRrkXFxKys){yomHHfPEpq = true;}
      if(yYurrCUNOH == IgjdHtJCMj){DjMrNrtHHK = true;}
      if(BiAVTxXZBz == lELndgeTDF){utodLdDUPj = true;}
      if(ikBzVPucKu == RbdPbjVeTS){NGGUxVOolY = true;}
      while(IgjdHtJCMj == yYurrCUNOH){dqrIUCLDVo = true;}
      while(lELndgeTDF == lELndgeTDF){cqURBSIAge = true;}
      while(RbdPbjVeTS == RbdPbjVeTS){BHGnjHiMWS = true;}
      if(TgDYZRoiaU == true){TgDYZRoiaU = false;}
      if(FjqVjFWbEF == true){FjqVjFWbEF = false;}
      if(omoIrfCUBX == true){omoIrfCUBX = false;}
      if(YdisQFBmOM == true){YdisQFBmOM = false;}
      if(qwrhAhkIeW == true){qwrhAhkIeW = false;}
      if(MtaNdfrtfs == true){MtaNdfrtfs = false;}
      if(OUgDwaBxEe == true){OUgDwaBxEe = false;}
      if(DjMrNrtHHK == true){DjMrNrtHHK = false;}
      if(utodLdDUPj == true){utodLdDUPj = false;}
      if(NGGUxVOolY == true){NGGUxVOolY = false;}
      if(fmDATbghzk == true){fmDATbghzk = false;}
      if(lkmUyUfDqR == true){lkmUyUfDqR = false;}
      if(XfhURwcruq == true){XfhURwcruq = false;}
      if(dFUidHqoKi == true){dFUidHqoKi = false;}
      if(wVUdycTlWc == true){wVUdycTlWc = false;}
      if(pKxTBzFiiW == true){pKxTBzFiiW = false;}
      if(yomHHfPEpq == true){yomHHfPEpq = false;}
      if(dqrIUCLDVo == true){dqrIUCLDVo = false;}
      if(cqURBSIAge == true){cqURBSIAge = false;}
      if(BHGnjHiMWS == true){BHGnjHiMWS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HLGNAMNPAX
{ 
  void iKJKeuyipx()
  { 
      bool DmPmYBQIXh = false;
      bool MoieJekGWS = false;
      bool QYrAjjuHmZ = false;
      bool EUAbCFlrGq = false;
      bool zbJEpDgisy = false;
      bool ZgPTeetPDn = false;
      bool GIVydqnHbE = false;
      bool rrAfToPnKf = false;
      bool DMNozWEgxX = false;
      bool LWoRjpGKZz = false;
      bool PYGoFhgjAp = false;
      bool OFFWjtugyH = false;
      bool mGKDrVChuc = false;
      bool iEOLQdFYiR = false;
      bool pUgGJGRSgp = false;
      bool uYMSMIODxi = false;
      bool eznWHJqsFG = false;
      bool oVxgQRZDtl = false;
      bool EiAFgJruzH = false;
      bool PBbAlqfJzz = false;
      string UmXkQogsWP;
      string nnZQfglgdx;
      string TxhaJINXGh;
      string NIJOiKJVWa;
      string bgmWWIyLWk;
      string UXtnPWFxaI;
      string aImnCfeKhU;
      string WQKDVmJKEA;
      string JCAUNoOUzL;
      string ELtOzStzUp;
      string dndBNDNpSc;
      string MusZyYHRZM;
      string QJKVQLWwED;
      string rKoNWVXzGJ;
      string bYCWyJSTPZ;
      string KbYIZTcHkC;
      string gQkPjCFfDc;
      string BILPjqHnXG;
      string rCferQkgmC;
      string rQNDcKmmmw;
      if(UmXkQogsWP == dndBNDNpSc){DmPmYBQIXh = true;}
      else if(dndBNDNpSc == UmXkQogsWP){PYGoFhgjAp = true;}
      if(nnZQfglgdx == MusZyYHRZM){MoieJekGWS = true;}
      else if(MusZyYHRZM == nnZQfglgdx){OFFWjtugyH = true;}
      if(TxhaJINXGh == QJKVQLWwED){QYrAjjuHmZ = true;}
      else if(QJKVQLWwED == TxhaJINXGh){mGKDrVChuc = true;}
      if(NIJOiKJVWa == rKoNWVXzGJ){EUAbCFlrGq = true;}
      else if(rKoNWVXzGJ == NIJOiKJVWa){iEOLQdFYiR = true;}
      if(bgmWWIyLWk == bYCWyJSTPZ){zbJEpDgisy = true;}
      else if(bYCWyJSTPZ == bgmWWIyLWk){pUgGJGRSgp = true;}
      if(UXtnPWFxaI == KbYIZTcHkC){ZgPTeetPDn = true;}
      else if(KbYIZTcHkC == UXtnPWFxaI){uYMSMIODxi = true;}
      if(aImnCfeKhU == gQkPjCFfDc){GIVydqnHbE = true;}
      else if(gQkPjCFfDc == aImnCfeKhU){eznWHJqsFG = true;}
      if(WQKDVmJKEA == BILPjqHnXG){rrAfToPnKf = true;}
      if(JCAUNoOUzL == rCferQkgmC){DMNozWEgxX = true;}
      if(ELtOzStzUp == rQNDcKmmmw){LWoRjpGKZz = true;}
      while(BILPjqHnXG == WQKDVmJKEA){oVxgQRZDtl = true;}
      while(rCferQkgmC == rCferQkgmC){EiAFgJruzH = true;}
      while(rQNDcKmmmw == rQNDcKmmmw){PBbAlqfJzz = true;}
      if(DmPmYBQIXh == true){DmPmYBQIXh = false;}
      if(MoieJekGWS == true){MoieJekGWS = false;}
      if(QYrAjjuHmZ == true){QYrAjjuHmZ = false;}
      if(EUAbCFlrGq == true){EUAbCFlrGq = false;}
      if(zbJEpDgisy == true){zbJEpDgisy = false;}
      if(ZgPTeetPDn == true){ZgPTeetPDn = false;}
      if(GIVydqnHbE == true){GIVydqnHbE = false;}
      if(rrAfToPnKf == true){rrAfToPnKf = false;}
      if(DMNozWEgxX == true){DMNozWEgxX = false;}
      if(LWoRjpGKZz == true){LWoRjpGKZz = false;}
      if(PYGoFhgjAp == true){PYGoFhgjAp = false;}
      if(OFFWjtugyH == true){OFFWjtugyH = false;}
      if(mGKDrVChuc == true){mGKDrVChuc = false;}
      if(iEOLQdFYiR == true){iEOLQdFYiR = false;}
      if(pUgGJGRSgp == true){pUgGJGRSgp = false;}
      if(uYMSMIODxi == true){uYMSMIODxi = false;}
      if(eznWHJqsFG == true){eznWHJqsFG = false;}
      if(oVxgQRZDtl == true){oVxgQRZDtl = false;}
      if(EiAFgJruzH == true){EiAFgJruzH = false;}
      if(PBbAlqfJzz == true){PBbAlqfJzz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JOJPSWRTNZ
{ 
  void EkmQzSxQhF()
  { 
      bool anOfmelKyT = false;
      bool hqanhTWirG = false;
      bool VsXSFVToFL = false;
      bool aZHQGuNXHL = false;
      bool HWHKohMIul = false;
      bool WOFzkhQwZR = false;
      bool KwFmsHiJgm = false;
      bool GyafyykNdX = false;
      bool ILtTnMTIeY = false;
      bool dRypAKRUQg = false;
      bool yCbHeXmZAm = false;
      bool wDSBIzCkyg = false;
      bool naeIIoAkem = false;
      bool gQwwYFjlnQ = false;
      bool YtHrbaywgB = false;
      bool IfVirXXSzp = false;
      bool WBtNGfGVcC = false;
      bool PPxhItSlfh = false;
      bool pEEdeAtNDB = false;
      bool hQmysXztlu = false;
      string dyyJLVsYQL;
      string GszVdxkMuX;
      string ncyIDAEQWS;
      string dHmYTjGeeK;
      string HUkKrPyjVj;
      string kVIkSAzoGK;
      string QcBxgzFZBs;
      string qGhkQSrnPm;
      string CUtmhIzBGS;
      string kQYTsdTmcs;
      string KXhcrenWUA;
      string IKZSIwhNPY;
      string AETiHahNrl;
      string zFKWcdmRuD;
      string TbgFKZqFKw;
      string uFWErFEzUR;
      string wZehADzCpe;
      string JQSMFXXNXg;
      string ibDupthGeW;
      string YnwcGsxyFH;
      if(dyyJLVsYQL == KXhcrenWUA){anOfmelKyT = true;}
      else if(KXhcrenWUA == dyyJLVsYQL){yCbHeXmZAm = true;}
      if(GszVdxkMuX == IKZSIwhNPY){hqanhTWirG = true;}
      else if(IKZSIwhNPY == GszVdxkMuX){wDSBIzCkyg = true;}
      if(ncyIDAEQWS == AETiHahNrl){VsXSFVToFL = true;}
      else if(AETiHahNrl == ncyIDAEQWS){naeIIoAkem = true;}
      if(dHmYTjGeeK == zFKWcdmRuD){aZHQGuNXHL = true;}
      else if(zFKWcdmRuD == dHmYTjGeeK){gQwwYFjlnQ = true;}
      if(HUkKrPyjVj == TbgFKZqFKw){HWHKohMIul = true;}
      else if(TbgFKZqFKw == HUkKrPyjVj){YtHrbaywgB = true;}
      if(kVIkSAzoGK == uFWErFEzUR){WOFzkhQwZR = true;}
      else if(uFWErFEzUR == kVIkSAzoGK){IfVirXXSzp = true;}
      if(QcBxgzFZBs == wZehADzCpe){KwFmsHiJgm = true;}
      else if(wZehADzCpe == QcBxgzFZBs){WBtNGfGVcC = true;}
      if(qGhkQSrnPm == JQSMFXXNXg){GyafyykNdX = true;}
      if(CUtmhIzBGS == ibDupthGeW){ILtTnMTIeY = true;}
      if(kQYTsdTmcs == YnwcGsxyFH){dRypAKRUQg = true;}
      while(JQSMFXXNXg == qGhkQSrnPm){PPxhItSlfh = true;}
      while(ibDupthGeW == ibDupthGeW){pEEdeAtNDB = true;}
      while(YnwcGsxyFH == YnwcGsxyFH){hQmysXztlu = true;}
      if(anOfmelKyT == true){anOfmelKyT = false;}
      if(hqanhTWirG == true){hqanhTWirG = false;}
      if(VsXSFVToFL == true){VsXSFVToFL = false;}
      if(aZHQGuNXHL == true){aZHQGuNXHL = false;}
      if(HWHKohMIul == true){HWHKohMIul = false;}
      if(WOFzkhQwZR == true){WOFzkhQwZR = false;}
      if(KwFmsHiJgm == true){KwFmsHiJgm = false;}
      if(GyafyykNdX == true){GyafyykNdX = false;}
      if(ILtTnMTIeY == true){ILtTnMTIeY = false;}
      if(dRypAKRUQg == true){dRypAKRUQg = false;}
      if(yCbHeXmZAm == true){yCbHeXmZAm = false;}
      if(wDSBIzCkyg == true){wDSBIzCkyg = false;}
      if(naeIIoAkem == true){naeIIoAkem = false;}
      if(gQwwYFjlnQ == true){gQwwYFjlnQ = false;}
      if(YtHrbaywgB == true){YtHrbaywgB = false;}
      if(IfVirXXSzp == true){IfVirXXSzp = false;}
      if(WBtNGfGVcC == true){WBtNGfGVcC = false;}
      if(PPxhItSlfh == true){PPxhItSlfh = false;}
      if(pEEdeAtNDB == true){pEEdeAtNDB = false;}
      if(hQmysXztlu == true){hQmysXztlu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IXKIQBWXKV
{ 
  void gtfgHlbeWw()
  { 
      bool kEGrAyqRyG = false;
      bool VhhyqafcyL = false;
      bool siAqtSfWGM = false;
      bool TUYUVNjIhJ = false;
      bool IHDFShWYxK = false;
      bool PtfNiBEOyg = false;
      bool RULklAINbc = false;
      bool qXtnDlftXL = false;
      bool uHYuxZoLkU = false;
      bool JUJArmuRSR = false;
      bool ZJwUTqzqKx = false;
      bool UJpmkKuPnM = false;
      bool LxbHTVNswP = false;
      bool pOaGklKEaF = false;
      bool ZxBnzzdWPg = false;
      bool rfdGFcgnAy = false;
      bool cGttGGhjBz = false;
      bool ApnhlOumIT = false;
      bool qqdOWKkUAH = false;
      bool EVDcbTDGhr = false;
      string zscyoGkIsJ;
      string duIsKPbxwX;
      string XAuZzQiqIw;
      string KFLYyPqYiG;
      string dKGrsmBVdR;
      string xyGKayyDzX;
      string XtzxyXjitu;
      string XCNotMtCfL;
      string PMMqzMzAyA;
      string RnZKijKJsV;
      string DRaistjRQN;
      string DuWnIKgIxl;
      string YijtdjcDGK;
      string BkJJIxlcxE;
      string cgjkwWRlCX;
      string CCLHxTggFJ;
      string RgKGLSkMeK;
      string XEKsIqyzyG;
      string SqAhHzYBMn;
      string QFXnlwWdZc;
      if(zscyoGkIsJ == DRaistjRQN){kEGrAyqRyG = true;}
      else if(DRaistjRQN == zscyoGkIsJ){ZJwUTqzqKx = true;}
      if(duIsKPbxwX == DuWnIKgIxl){VhhyqafcyL = true;}
      else if(DuWnIKgIxl == duIsKPbxwX){UJpmkKuPnM = true;}
      if(XAuZzQiqIw == YijtdjcDGK){siAqtSfWGM = true;}
      else if(YijtdjcDGK == XAuZzQiqIw){LxbHTVNswP = true;}
      if(KFLYyPqYiG == BkJJIxlcxE){TUYUVNjIhJ = true;}
      else if(BkJJIxlcxE == KFLYyPqYiG){pOaGklKEaF = true;}
      if(dKGrsmBVdR == cgjkwWRlCX){IHDFShWYxK = true;}
      else if(cgjkwWRlCX == dKGrsmBVdR){ZxBnzzdWPg = true;}
      if(xyGKayyDzX == CCLHxTggFJ){PtfNiBEOyg = true;}
      else if(CCLHxTggFJ == xyGKayyDzX){rfdGFcgnAy = true;}
      if(XtzxyXjitu == RgKGLSkMeK){RULklAINbc = true;}
      else if(RgKGLSkMeK == XtzxyXjitu){cGttGGhjBz = true;}
      if(XCNotMtCfL == XEKsIqyzyG){qXtnDlftXL = true;}
      if(PMMqzMzAyA == SqAhHzYBMn){uHYuxZoLkU = true;}
      if(RnZKijKJsV == QFXnlwWdZc){JUJArmuRSR = true;}
      while(XEKsIqyzyG == XCNotMtCfL){ApnhlOumIT = true;}
      while(SqAhHzYBMn == SqAhHzYBMn){qqdOWKkUAH = true;}
      while(QFXnlwWdZc == QFXnlwWdZc){EVDcbTDGhr = true;}
      if(kEGrAyqRyG == true){kEGrAyqRyG = false;}
      if(VhhyqafcyL == true){VhhyqafcyL = false;}
      if(siAqtSfWGM == true){siAqtSfWGM = false;}
      if(TUYUVNjIhJ == true){TUYUVNjIhJ = false;}
      if(IHDFShWYxK == true){IHDFShWYxK = false;}
      if(PtfNiBEOyg == true){PtfNiBEOyg = false;}
      if(RULklAINbc == true){RULklAINbc = false;}
      if(qXtnDlftXL == true){qXtnDlftXL = false;}
      if(uHYuxZoLkU == true){uHYuxZoLkU = false;}
      if(JUJArmuRSR == true){JUJArmuRSR = false;}
      if(ZJwUTqzqKx == true){ZJwUTqzqKx = false;}
      if(UJpmkKuPnM == true){UJpmkKuPnM = false;}
      if(LxbHTVNswP == true){LxbHTVNswP = false;}
      if(pOaGklKEaF == true){pOaGklKEaF = false;}
      if(ZxBnzzdWPg == true){ZxBnzzdWPg = false;}
      if(rfdGFcgnAy == true){rfdGFcgnAy = false;}
      if(cGttGGhjBz == true){cGttGGhjBz = false;}
      if(ApnhlOumIT == true){ApnhlOumIT = false;}
      if(qqdOWKkUAH == true){qqdOWKkUAH = false;}
      if(EVDcbTDGhr == true){EVDcbTDGhr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QDFWMSEGJH
{ 
  void lAVCtsFerO()
  { 
      bool VNTHskhTQs = false;
      bool qukKxkuqdK = false;
      bool kdiEZXFezW = false;
      bool rMpIbieqNM = false;
      bool BmiRsCbKoT = false;
      bool omYhqqeOgU = false;
      bool fCUsBdEchN = false;
      bool GEdRIxuRLW = false;
      bool wtofgEnHRj = false;
      bool EQJrfzSoQO = false;
      bool yycbMkJHZs = false;
      bool wMDKYlNnMw = false;
      bool pwKxIpukkJ = false;
      bool eGBwXxQMSw = false;
      bool tfhXnrMyTt = false;
      bool kdcTYBneSW = false;
      bool oXWPOpKGma = false;
      bool UAUPBJOmJQ = false;
      bool cwRqXAdhXW = false;
      bool JltuGWJRJy = false;
      string cYruyOkBMZ;
      string zFNSngSUOn;
      string LCmbSSjsTf;
      string iimZTnuTLd;
      string KeBCgVnZHl;
      string tgVSJZlQce;
      string erggpPRmyA;
      string kzJkdgBjtw;
      string dKlhkCNUPs;
      string BepfzSyUMR;
      string EBaHAuWjnc;
      string YBVgATFyum;
      string BxWFyGJclL;
      string igXbqciegp;
      string edfmUzIJee;
      string MzYYQHeVIt;
      string ktyctrdtoX;
      string kaREIXQijy;
      string xzyGyiHzKj;
      string yMVlFkeDsb;
      if(cYruyOkBMZ == EBaHAuWjnc){VNTHskhTQs = true;}
      else if(EBaHAuWjnc == cYruyOkBMZ){yycbMkJHZs = true;}
      if(zFNSngSUOn == YBVgATFyum){qukKxkuqdK = true;}
      else if(YBVgATFyum == zFNSngSUOn){wMDKYlNnMw = true;}
      if(LCmbSSjsTf == BxWFyGJclL){kdiEZXFezW = true;}
      else if(BxWFyGJclL == LCmbSSjsTf){pwKxIpukkJ = true;}
      if(iimZTnuTLd == igXbqciegp){rMpIbieqNM = true;}
      else if(igXbqciegp == iimZTnuTLd){eGBwXxQMSw = true;}
      if(KeBCgVnZHl == edfmUzIJee){BmiRsCbKoT = true;}
      else if(edfmUzIJee == KeBCgVnZHl){tfhXnrMyTt = true;}
      if(tgVSJZlQce == MzYYQHeVIt){omYhqqeOgU = true;}
      else if(MzYYQHeVIt == tgVSJZlQce){kdcTYBneSW = true;}
      if(erggpPRmyA == ktyctrdtoX){fCUsBdEchN = true;}
      else if(ktyctrdtoX == erggpPRmyA){oXWPOpKGma = true;}
      if(kzJkdgBjtw == kaREIXQijy){GEdRIxuRLW = true;}
      if(dKlhkCNUPs == xzyGyiHzKj){wtofgEnHRj = true;}
      if(BepfzSyUMR == yMVlFkeDsb){EQJrfzSoQO = true;}
      while(kaREIXQijy == kzJkdgBjtw){UAUPBJOmJQ = true;}
      while(xzyGyiHzKj == xzyGyiHzKj){cwRqXAdhXW = true;}
      while(yMVlFkeDsb == yMVlFkeDsb){JltuGWJRJy = true;}
      if(VNTHskhTQs == true){VNTHskhTQs = false;}
      if(qukKxkuqdK == true){qukKxkuqdK = false;}
      if(kdiEZXFezW == true){kdiEZXFezW = false;}
      if(rMpIbieqNM == true){rMpIbieqNM = false;}
      if(BmiRsCbKoT == true){BmiRsCbKoT = false;}
      if(omYhqqeOgU == true){omYhqqeOgU = false;}
      if(fCUsBdEchN == true){fCUsBdEchN = false;}
      if(GEdRIxuRLW == true){GEdRIxuRLW = false;}
      if(wtofgEnHRj == true){wtofgEnHRj = false;}
      if(EQJrfzSoQO == true){EQJrfzSoQO = false;}
      if(yycbMkJHZs == true){yycbMkJHZs = false;}
      if(wMDKYlNnMw == true){wMDKYlNnMw = false;}
      if(pwKxIpukkJ == true){pwKxIpukkJ = false;}
      if(eGBwXxQMSw == true){eGBwXxQMSw = false;}
      if(tfhXnrMyTt == true){tfhXnrMyTt = false;}
      if(kdcTYBneSW == true){kdcTYBneSW = false;}
      if(oXWPOpKGma == true){oXWPOpKGma = false;}
      if(UAUPBJOmJQ == true){UAUPBJOmJQ = false;}
      if(cwRqXAdhXW == true){cwRqXAdhXW = false;}
      if(JltuGWJRJy == true){JltuGWJRJy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XCOFNKDGUV
{ 
  void FEmkJbilwN()
  { 
      bool SGSZSfjpjk = false;
      bool qeKFzPOjwr = false;
      bool rRFzuSxdwy = false;
      bool uKtEymUzdJ = false;
      bool zmhZXnUhbi = false;
      bool fOnBeAASez = false;
      bool iGtkpgjFHL = false;
      bool uOFlsFifbH = false;
      bool yOBNSfWrZx = false;
      bool mBUdarsxjp = false;
      bool EPaPmRIBIZ = false;
      bool QUqWBTEfSJ = false;
      bool JqfJYtsaKA = false;
      bool MlwkChnkZA = false;
      bool WUjAfSKxcH = false;
      bool nMdZfMiQqs = false;
      bool XhpINeXFUS = false;
      bool fSFRloHedF = false;
      bool jwyDLzHVFo = false;
      bool yWtgcoeamB = false;
      string qFGVEKttmN;
      string JTzMYloTKe;
      string GGWAxiYxpP;
      string yLiOOTmVMR;
      string JSGUDpQCwK;
      string pKmQpkiFXU;
      string kwEWPykkxF;
      string zSHsVnzBwH;
      string SVBeYmYSYd;
      string jgyqfNOjFF;
      string FfFqLXDsuB;
      string kgIQCPuYxb;
      string ZSLTURUPMI;
      string ZPwqCmQKTB;
      string ieWWrDXgoQ;
      string RolcfmTkVs;
      string CnfmbVkROO;
      string ykEustuoaQ;
      string tmZwpjdSLO;
      string SenaytyjtW;
      if(qFGVEKttmN == FfFqLXDsuB){SGSZSfjpjk = true;}
      else if(FfFqLXDsuB == qFGVEKttmN){EPaPmRIBIZ = true;}
      if(JTzMYloTKe == kgIQCPuYxb){qeKFzPOjwr = true;}
      else if(kgIQCPuYxb == JTzMYloTKe){QUqWBTEfSJ = true;}
      if(GGWAxiYxpP == ZSLTURUPMI){rRFzuSxdwy = true;}
      else if(ZSLTURUPMI == GGWAxiYxpP){JqfJYtsaKA = true;}
      if(yLiOOTmVMR == ZPwqCmQKTB){uKtEymUzdJ = true;}
      else if(ZPwqCmQKTB == yLiOOTmVMR){MlwkChnkZA = true;}
      if(JSGUDpQCwK == ieWWrDXgoQ){zmhZXnUhbi = true;}
      else if(ieWWrDXgoQ == JSGUDpQCwK){WUjAfSKxcH = true;}
      if(pKmQpkiFXU == RolcfmTkVs){fOnBeAASez = true;}
      else if(RolcfmTkVs == pKmQpkiFXU){nMdZfMiQqs = true;}
      if(kwEWPykkxF == CnfmbVkROO){iGtkpgjFHL = true;}
      else if(CnfmbVkROO == kwEWPykkxF){XhpINeXFUS = true;}
      if(zSHsVnzBwH == ykEustuoaQ){uOFlsFifbH = true;}
      if(SVBeYmYSYd == tmZwpjdSLO){yOBNSfWrZx = true;}
      if(jgyqfNOjFF == SenaytyjtW){mBUdarsxjp = true;}
      while(ykEustuoaQ == zSHsVnzBwH){fSFRloHedF = true;}
      while(tmZwpjdSLO == tmZwpjdSLO){jwyDLzHVFo = true;}
      while(SenaytyjtW == SenaytyjtW){yWtgcoeamB = true;}
      if(SGSZSfjpjk == true){SGSZSfjpjk = false;}
      if(qeKFzPOjwr == true){qeKFzPOjwr = false;}
      if(rRFzuSxdwy == true){rRFzuSxdwy = false;}
      if(uKtEymUzdJ == true){uKtEymUzdJ = false;}
      if(zmhZXnUhbi == true){zmhZXnUhbi = false;}
      if(fOnBeAASez == true){fOnBeAASez = false;}
      if(iGtkpgjFHL == true){iGtkpgjFHL = false;}
      if(uOFlsFifbH == true){uOFlsFifbH = false;}
      if(yOBNSfWrZx == true){yOBNSfWrZx = false;}
      if(mBUdarsxjp == true){mBUdarsxjp = false;}
      if(EPaPmRIBIZ == true){EPaPmRIBIZ = false;}
      if(QUqWBTEfSJ == true){QUqWBTEfSJ = false;}
      if(JqfJYtsaKA == true){JqfJYtsaKA = false;}
      if(MlwkChnkZA == true){MlwkChnkZA = false;}
      if(WUjAfSKxcH == true){WUjAfSKxcH = false;}
      if(nMdZfMiQqs == true){nMdZfMiQqs = false;}
      if(XhpINeXFUS == true){XhpINeXFUS = false;}
      if(fSFRloHedF == true){fSFRloHedF = false;}
      if(jwyDLzHVFo == true){jwyDLzHVFo = false;}
      if(yWtgcoeamB == true){yWtgcoeamB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EVLQIELGFM
{ 
  void urPdcMrmYS()
  { 
      bool nawZMPQlkg = false;
      bool RNNCZsyylO = false;
      bool WpAFcChXXW = false;
      bool rxbCOBJwbp = false;
      bool mGyNTmVpLl = false;
      bool cjsxRyaqxK = false;
      bool hrOOnTkLnX = false;
      bool jCWwaQrlko = false;
      bool gqMlsIDdjP = false;
      bool aRzRHuriZz = false;
      bool BKBmCZNxVA = false;
      bool GnGHcpfbUe = false;
      bool QHaXxRCEnf = false;
      bool YIMkmVoZiT = false;
      bool uFHjJlLqnR = false;
      bool OPOtitjdoj = false;
      bool XIJpbxbUTH = false;
      bool AFrBjKzqNL = false;
      bool GKPWQJtRCr = false;
      bool lLjzwmwRHM = false;
      string CIVzPSRDcz;
      string lteSVCNPJg;
      string KrSMyDyTPU;
      string IoZdPxeKAu;
      string QJiUCTZFwY;
      string wNpIzJpIBM;
      string TymIpwUACY;
      string WDPOQAJxJe;
      string crWpYuyReF;
      string GVJnaRWZeG;
      string yYDXCsxbqy;
      string ArzWibawiu;
      string yDVxRAsbny;
      string djSDfEozme;
      string xWZgFOWmEz;
      string qZpiIuCFGC;
      string zVnsTPZupd;
      string laIEyadoqD;
      string cGWoGEsiuk;
      string BjskfbifMo;
      if(CIVzPSRDcz == yYDXCsxbqy){nawZMPQlkg = true;}
      else if(yYDXCsxbqy == CIVzPSRDcz){BKBmCZNxVA = true;}
      if(lteSVCNPJg == ArzWibawiu){RNNCZsyylO = true;}
      else if(ArzWibawiu == lteSVCNPJg){GnGHcpfbUe = true;}
      if(KrSMyDyTPU == yDVxRAsbny){WpAFcChXXW = true;}
      else if(yDVxRAsbny == KrSMyDyTPU){QHaXxRCEnf = true;}
      if(IoZdPxeKAu == djSDfEozme){rxbCOBJwbp = true;}
      else if(djSDfEozme == IoZdPxeKAu){YIMkmVoZiT = true;}
      if(QJiUCTZFwY == xWZgFOWmEz){mGyNTmVpLl = true;}
      else if(xWZgFOWmEz == QJiUCTZFwY){uFHjJlLqnR = true;}
      if(wNpIzJpIBM == qZpiIuCFGC){cjsxRyaqxK = true;}
      else if(qZpiIuCFGC == wNpIzJpIBM){OPOtitjdoj = true;}
      if(TymIpwUACY == zVnsTPZupd){hrOOnTkLnX = true;}
      else if(zVnsTPZupd == TymIpwUACY){XIJpbxbUTH = true;}
      if(WDPOQAJxJe == laIEyadoqD){jCWwaQrlko = true;}
      if(crWpYuyReF == cGWoGEsiuk){gqMlsIDdjP = true;}
      if(GVJnaRWZeG == BjskfbifMo){aRzRHuriZz = true;}
      while(laIEyadoqD == WDPOQAJxJe){AFrBjKzqNL = true;}
      while(cGWoGEsiuk == cGWoGEsiuk){GKPWQJtRCr = true;}
      while(BjskfbifMo == BjskfbifMo){lLjzwmwRHM = true;}
      if(nawZMPQlkg == true){nawZMPQlkg = false;}
      if(RNNCZsyylO == true){RNNCZsyylO = false;}
      if(WpAFcChXXW == true){WpAFcChXXW = false;}
      if(rxbCOBJwbp == true){rxbCOBJwbp = false;}
      if(mGyNTmVpLl == true){mGyNTmVpLl = false;}
      if(cjsxRyaqxK == true){cjsxRyaqxK = false;}
      if(hrOOnTkLnX == true){hrOOnTkLnX = false;}
      if(jCWwaQrlko == true){jCWwaQrlko = false;}
      if(gqMlsIDdjP == true){gqMlsIDdjP = false;}
      if(aRzRHuriZz == true){aRzRHuriZz = false;}
      if(BKBmCZNxVA == true){BKBmCZNxVA = false;}
      if(GnGHcpfbUe == true){GnGHcpfbUe = false;}
      if(QHaXxRCEnf == true){QHaXxRCEnf = false;}
      if(YIMkmVoZiT == true){YIMkmVoZiT = false;}
      if(uFHjJlLqnR == true){uFHjJlLqnR = false;}
      if(OPOtitjdoj == true){OPOtitjdoj = false;}
      if(XIJpbxbUTH == true){XIJpbxbUTH = false;}
      if(AFrBjKzqNL == true){AFrBjKzqNL = false;}
      if(GKPWQJtRCr == true){GKPWQJtRCr = false;}
      if(lLjzwmwRHM == true){lLjzwmwRHM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NULISVFKDL
{ 
  void KOzrmBWMay()
  { 
      bool cfyraCXeLb = false;
      bool AOYmYcYRdP = false;
      bool SjnOrjOpMX = false;
      bool NyIejDfyma = false;
      bool UHrtUClfSf = false;
      bool nRJLwrrjAq = false;
      bool mhSmOCFtDU = false;
      bool wZeCuKrsso = false;
      bool yiXfjwnwhr = false;
      bool LuywnloFfS = false;
      bool wqcxiOlGQl = false;
      bool zypKsEKmDR = false;
      bool NJMKIAaiOI = false;
      bool UlMasGFZwU = false;
      bool KgfurMFnCi = false;
      bool bCCOEmeRni = false;
      bool mDrHQNlPRl = false;
      bool yjphHgcQRu = false;
      bool ulfefSjyVF = false;
      bool ankNgGoYee = false;
      string FQROaLNEXB;
      string ihtNpSpxUn;
      string jkQWrRYNoz;
      string FlkhiFsygk;
      string nAKGkQgLOH;
      string NWCVpUztVI;
      string mAOXwxwMdj;
      string ZqPjAjZKkb;
      string jMyhliiPqO;
      string GzcYxmllJn;
      string TUhdhVGSUG;
      string toIsXZCglN;
      string NgVOdZOqlN;
      string xnAxIPeTzQ;
      string bQukUQpiAW;
      string jFAwZmzSAH;
      string HPgGIFnKjI;
      string uhgUkxlktM;
      string iepOcrmDWV;
      string QLTqIMinbO;
      if(FQROaLNEXB == TUhdhVGSUG){cfyraCXeLb = true;}
      else if(TUhdhVGSUG == FQROaLNEXB){wqcxiOlGQl = true;}
      if(ihtNpSpxUn == toIsXZCglN){AOYmYcYRdP = true;}
      else if(toIsXZCglN == ihtNpSpxUn){zypKsEKmDR = true;}
      if(jkQWrRYNoz == NgVOdZOqlN){SjnOrjOpMX = true;}
      else if(NgVOdZOqlN == jkQWrRYNoz){NJMKIAaiOI = true;}
      if(FlkhiFsygk == xnAxIPeTzQ){NyIejDfyma = true;}
      else if(xnAxIPeTzQ == FlkhiFsygk){UlMasGFZwU = true;}
      if(nAKGkQgLOH == bQukUQpiAW){UHrtUClfSf = true;}
      else if(bQukUQpiAW == nAKGkQgLOH){KgfurMFnCi = true;}
      if(NWCVpUztVI == jFAwZmzSAH){nRJLwrrjAq = true;}
      else if(jFAwZmzSAH == NWCVpUztVI){bCCOEmeRni = true;}
      if(mAOXwxwMdj == HPgGIFnKjI){mhSmOCFtDU = true;}
      else if(HPgGIFnKjI == mAOXwxwMdj){mDrHQNlPRl = true;}
      if(ZqPjAjZKkb == uhgUkxlktM){wZeCuKrsso = true;}
      if(jMyhliiPqO == iepOcrmDWV){yiXfjwnwhr = true;}
      if(GzcYxmllJn == QLTqIMinbO){LuywnloFfS = true;}
      while(uhgUkxlktM == ZqPjAjZKkb){yjphHgcQRu = true;}
      while(iepOcrmDWV == iepOcrmDWV){ulfefSjyVF = true;}
      while(QLTqIMinbO == QLTqIMinbO){ankNgGoYee = true;}
      if(cfyraCXeLb == true){cfyraCXeLb = false;}
      if(AOYmYcYRdP == true){AOYmYcYRdP = false;}
      if(SjnOrjOpMX == true){SjnOrjOpMX = false;}
      if(NyIejDfyma == true){NyIejDfyma = false;}
      if(UHrtUClfSf == true){UHrtUClfSf = false;}
      if(nRJLwrrjAq == true){nRJLwrrjAq = false;}
      if(mhSmOCFtDU == true){mhSmOCFtDU = false;}
      if(wZeCuKrsso == true){wZeCuKrsso = false;}
      if(yiXfjwnwhr == true){yiXfjwnwhr = false;}
      if(LuywnloFfS == true){LuywnloFfS = false;}
      if(wqcxiOlGQl == true){wqcxiOlGQl = false;}
      if(zypKsEKmDR == true){zypKsEKmDR = false;}
      if(NJMKIAaiOI == true){NJMKIAaiOI = false;}
      if(UlMasGFZwU == true){UlMasGFZwU = false;}
      if(KgfurMFnCi == true){KgfurMFnCi = false;}
      if(bCCOEmeRni == true){bCCOEmeRni = false;}
      if(mDrHQNlPRl == true){mDrHQNlPRl = false;}
      if(yjphHgcQRu == true){yjphHgcQRu = false;}
      if(ulfefSjyVF == true){ulfefSjyVF = false;}
      if(ankNgGoYee == true){ankNgGoYee = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TUKLNPAJVI
{ 
  void qUMiyrjuED()
  { 
      bool yNwutkHbqr = false;
      bool GmQaUMKlqs = false;
      bool dUoMxuxRCi = false;
      bool LQVwLPVgRC = false;
      bool nVzOOGMSXz = false;
      bool iIeVIdXiyz = false;
      bool mpYHfoQTOF = false;
      bool qcToEIUayq = false;
      bool hesDzDlAnh = false;
      bool qliROywqiY = false;
      bool osDSIGnoQA = false;
      bool IxkHRHwVIc = false;
      bool CQfgOFtCZG = false;
      bool LdqZBnbaus = false;
      bool OximYsAaAG = false;
      bool BahFVYNVEC = false;
      bool LlOKoeGKGc = false;
      bool fVaPOFgrIU = false;
      bool ETCTFkukEc = false;
      bool aGWrgbhYys = false;
      string HbgGecCDms;
      string UhtFmatpzX;
      string lFQXLrzrVQ;
      string xzAweoXWgy;
      string JCTbSOMYFq;
      string yLdHmBKItm;
      string cKgWwUgyay;
      string DXIAOikoEx;
      string eameRkVsId;
      string dObsUzUxey;
      string hNxGmaDcsD;
      string PUDxHCXCFK;
      string zmpxTowPeO;
      string OnKGPRdfqp;
      string hrAENJLdlS;
      string bSqTztXAly;
      string dnydoaKxhp;
      string XqKOcGmkiK;
      string cRcMmwxpHU;
      string scssLttVOl;
      if(HbgGecCDms == hNxGmaDcsD){yNwutkHbqr = true;}
      else if(hNxGmaDcsD == HbgGecCDms){osDSIGnoQA = true;}
      if(UhtFmatpzX == PUDxHCXCFK){GmQaUMKlqs = true;}
      else if(PUDxHCXCFK == UhtFmatpzX){IxkHRHwVIc = true;}
      if(lFQXLrzrVQ == zmpxTowPeO){dUoMxuxRCi = true;}
      else if(zmpxTowPeO == lFQXLrzrVQ){CQfgOFtCZG = true;}
      if(xzAweoXWgy == OnKGPRdfqp){LQVwLPVgRC = true;}
      else if(OnKGPRdfqp == xzAweoXWgy){LdqZBnbaus = true;}
      if(JCTbSOMYFq == hrAENJLdlS){nVzOOGMSXz = true;}
      else if(hrAENJLdlS == JCTbSOMYFq){OximYsAaAG = true;}
      if(yLdHmBKItm == bSqTztXAly){iIeVIdXiyz = true;}
      else if(bSqTztXAly == yLdHmBKItm){BahFVYNVEC = true;}
      if(cKgWwUgyay == dnydoaKxhp){mpYHfoQTOF = true;}
      else if(dnydoaKxhp == cKgWwUgyay){LlOKoeGKGc = true;}
      if(DXIAOikoEx == XqKOcGmkiK){qcToEIUayq = true;}
      if(eameRkVsId == cRcMmwxpHU){hesDzDlAnh = true;}
      if(dObsUzUxey == scssLttVOl){qliROywqiY = true;}
      while(XqKOcGmkiK == DXIAOikoEx){fVaPOFgrIU = true;}
      while(cRcMmwxpHU == cRcMmwxpHU){ETCTFkukEc = true;}
      while(scssLttVOl == scssLttVOl){aGWrgbhYys = true;}
      if(yNwutkHbqr == true){yNwutkHbqr = false;}
      if(GmQaUMKlqs == true){GmQaUMKlqs = false;}
      if(dUoMxuxRCi == true){dUoMxuxRCi = false;}
      if(LQVwLPVgRC == true){LQVwLPVgRC = false;}
      if(nVzOOGMSXz == true){nVzOOGMSXz = false;}
      if(iIeVIdXiyz == true){iIeVIdXiyz = false;}
      if(mpYHfoQTOF == true){mpYHfoQTOF = false;}
      if(qcToEIUayq == true){qcToEIUayq = false;}
      if(hesDzDlAnh == true){hesDzDlAnh = false;}
      if(qliROywqiY == true){qliROywqiY = false;}
      if(osDSIGnoQA == true){osDSIGnoQA = false;}
      if(IxkHRHwVIc == true){IxkHRHwVIc = false;}
      if(CQfgOFtCZG == true){CQfgOFtCZG = false;}
      if(LdqZBnbaus == true){LdqZBnbaus = false;}
      if(OximYsAaAG == true){OximYsAaAG = false;}
      if(BahFVYNVEC == true){BahFVYNVEC = false;}
      if(LlOKoeGKGc == true){LlOKoeGKGc = false;}
      if(fVaPOFgrIU == true){fVaPOFgrIU = false;}
      if(ETCTFkukEc == true){ETCTFkukEc = false;}
      if(aGWrgbhYys == true){aGWrgbhYys = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TIUVCZBIBN
{ 
  void LNbNOrumiJ()
  { 
      bool hfbkuhgVPH = false;
      bool cQRJNPDOmg = false;
      bool GzBrffDUaY = false;
      bool UPgsdRfbon = false;
      bool ULgVBlFujV = false;
      bool WkhUlidjFO = false;
      bool eMuqmNjYeu = false;
      bool jbZzLtReqs = false;
      bool aHjFBjgMHu = false;
      bool mwVZJIQoim = false;
      bool CfQoltKhIq = false;
      bool QyrLnWbpoC = false;
      bool fWQiHmFApD = false;
      bool dcwEqtpuTH = false;
      bool YzDPdoEJkl = false;
      bool fZzfGeOggy = false;
      bool nKqFNnCnUt = false;
      bool ggWhdgTBFS = false;
      bool iuOEWDcPxL = false;
      bool eINUSOHyCo = false;
      string TYeLGKHIGD;
      string UdcYprZLTm;
      string FpArWqfhEs;
      string ZXLjRLkDWI;
      string zdSiqyPfrb;
      string ClrJMcYmnO;
      string eYENdxSsHd;
      string HWnLmbWQAY;
      string azocpneBWn;
      string lyOHcZZFEt;
      string eWXNTfxgVk;
      string GHlPmejaWp;
      string RQVTqJHghM;
      string BQLGsEbaIK;
      string qxelhdLzTy;
      string pziObOBEVK;
      string YQyJjowfWi;
      string DIRMzTkjlM;
      string xIMjVChwdd;
      string DWFxlZzVCr;
      if(TYeLGKHIGD == eWXNTfxgVk){hfbkuhgVPH = true;}
      else if(eWXNTfxgVk == TYeLGKHIGD){CfQoltKhIq = true;}
      if(UdcYprZLTm == GHlPmejaWp){cQRJNPDOmg = true;}
      else if(GHlPmejaWp == UdcYprZLTm){QyrLnWbpoC = true;}
      if(FpArWqfhEs == RQVTqJHghM){GzBrffDUaY = true;}
      else if(RQVTqJHghM == FpArWqfhEs){fWQiHmFApD = true;}
      if(ZXLjRLkDWI == BQLGsEbaIK){UPgsdRfbon = true;}
      else if(BQLGsEbaIK == ZXLjRLkDWI){dcwEqtpuTH = true;}
      if(zdSiqyPfrb == qxelhdLzTy){ULgVBlFujV = true;}
      else if(qxelhdLzTy == zdSiqyPfrb){YzDPdoEJkl = true;}
      if(ClrJMcYmnO == pziObOBEVK){WkhUlidjFO = true;}
      else if(pziObOBEVK == ClrJMcYmnO){fZzfGeOggy = true;}
      if(eYENdxSsHd == YQyJjowfWi){eMuqmNjYeu = true;}
      else if(YQyJjowfWi == eYENdxSsHd){nKqFNnCnUt = true;}
      if(HWnLmbWQAY == DIRMzTkjlM){jbZzLtReqs = true;}
      if(azocpneBWn == xIMjVChwdd){aHjFBjgMHu = true;}
      if(lyOHcZZFEt == DWFxlZzVCr){mwVZJIQoim = true;}
      while(DIRMzTkjlM == HWnLmbWQAY){ggWhdgTBFS = true;}
      while(xIMjVChwdd == xIMjVChwdd){iuOEWDcPxL = true;}
      while(DWFxlZzVCr == DWFxlZzVCr){eINUSOHyCo = true;}
      if(hfbkuhgVPH == true){hfbkuhgVPH = false;}
      if(cQRJNPDOmg == true){cQRJNPDOmg = false;}
      if(GzBrffDUaY == true){GzBrffDUaY = false;}
      if(UPgsdRfbon == true){UPgsdRfbon = false;}
      if(ULgVBlFujV == true){ULgVBlFujV = false;}
      if(WkhUlidjFO == true){WkhUlidjFO = false;}
      if(eMuqmNjYeu == true){eMuqmNjYeu = false;}
      if(jbZzLtReqs == true){jbZzLtReqs = false;}
      if(aHjFBjgMHu == true){aHjFBjgMHu = false;}
      if(mwVZJIQoim == true){mwVZJIQoim = false;}
      if(CfQoltKhIq == true){CfQoltKhIq = false;}
      if(QyrLnWbpoC == true){QyrLnWbpoC = false;}
      if(fWQiHmFApD == true){fWQiHmFApD = false;}
      if(dcwEqtpuTH == true){dcwEqtpuTH = false;}
      if(YzDPdoEJkl == true){YzDPdoEJkl = false;}
      if(fZzfGeOggy == true){fZzfGeOggy = false;}
      if(nKqFNnCnUt == true){nKqFNnCnUt = false;}
      if(ggWhdgTBFS == true){ggWhdgTBFS = false;}
      if(iuOEWDcPxL == true){iuOEWDcPxL = false;}
      if(eINUSOHyCo == true){eINUSOHyCo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DFEZUBJMDX
{ 
  void LCHLpnkqOS()
  { 
      bool mbBxVVqYfJ = false;
      bool pcjGnDkaBA = false;
      bool iXLZuCcGkt = false;
      bool oirCqJZJBu = false;
      bool MwuOEFiGml = false;
      bool FLYOtPQaBT = false;
      bool rknlTGjhOd = false;
      bool dbYGmlbwUp = false;
      bool SWSyndJdHb = false;
      bool syIhCbIJuy = false;
      bool UBrIIdlSaH = false;
      bool mTFKAVRoxp = false;
      bool wFZlkeTqDK = false;
      bool dRBWVRdKoK = false;
      bool qqDAnZsxgf = false;
      bool JSMFBObFWc = false;
      bool KuOPcVRioi = false;
      bool qHzmyFCYyL = false;
      bool lVJXBKFwVG = false;
      bool oYmMzubmWS = false;
      string EUOUjjsxBS;
      string VLkgBGsDTW;
      string sIwNBKSCsJ;
      string oNQNGEFHxL;
      string rKoQFzhEAW;
      string MfSaOuYATY;
      string RpErdHtXZx;
      string BkFHehTfHB;
      string cNBWwJupyK;
      string fEnXtBGwly;
      string FJeDVaZKwf;
      string bssRwDohwU;
      string MEYORwxhNc;
      string bWsJwSiyAU;
      string ijsRimLWap;
      string MXARkAjPkY;
      string drxSDFziVd;
      string UpgakbKHfe;
      string kaGWQDVbXu;
      string hSMapqlaOd;
      if(EUOUjjsxBS == FJeDVaZKwf){mbBxVVqYfJ = true;}
      else if(FJeDVaZKwf == EUOUjjsxBS){UBrIIdlSaH = true;}
      if(VLkgBGsDTW == bssRwDohwU){pcjGnDkaBA = true;}
      else if(bssRwDohwU == VLkgBGsDTW){mTFKAVRoxp = true;}
      if(sIwNBKSCsJ == MEYORwxhNc){iXLZuCcGkt = true;}
      else if(MEYORwxhNc == sIwNBKSCsJ){wFZlkeTqDK = true;}
      if(oNQNGEFHxL == bWsJwSiyAU){oirCqJZJBu = true;}
      else if(bWsJwSiyAU == oNQNGEFHxL){dRBWVRdKoK = true;}
      if(rKoQFzhEAW == ijsRimLWap){MwuOEFiGml = true;}
      else if(ijsRimLWap == rKoQFzhEAW){qqDAnZsxgf = true;}
      if(MfSaOuYATY == MXARkAjPkY){FLYOtPQaBT = true;}
      else if(MXARkAjPkY == MfSaOuYATY){JSMFBObFWc = true;}
      if(RpErdHtXZx == drxSDFziVd){rknlTGjhOd = true;}
      else if(drxSDFziVd == RpErdHtXZx){KuOPcVRioi = true;}
      if(BkFHehTfHB == UpgakbKHfe){dbYGmlbwUp = true;}
      if(cNBWwJupyK == kaGWQDVbXu){SWSyndJdHb = true;}
      if(fEnXtBGwly == hSMapqlaOd){syIhCbIJuy = true;}
      while(UpgakbKHfe == BkFHehTfHB){qHzmyFCYyL = true;}
      while(kaGWQDVbXu == kaGWQDVbXu){lVJXBKFwVG = true;}
      while(hSMapqlaOd == hSMapqlaOd){oYmMzubmWS = true;}
      if(mbBxVVqYfJ == true){mbBxVVqYfJ = false;}
      if(pcjGnDkaBA == true){pcjGnDkaBA = false;}
      if(iXLZuCcGkt == true){iXLZuCcGkt = false;}
      if(oirCqJZJBu == true){oirCqJZJBu = false;}
      if(MwuOEFiGml == true){MwuOEFiGml = false;}
      if(FLYOtPQaBT == true){FLYOtPQaBT = false;}
      if(rknlTGjhOd == true){rknlTGjhOd = false;}
      if(dbYGmlbwUp == true){dbYGmlbwUp = false;}
      if(SWSyndJdHb == true){SWSyndJdHb = false;}
      if(syIhCbIJuy == true){syIhCbIJuy = false;}
      if(UBrIIdlSaH == true){UBrIIdlSaH = false;}
      if(mTFKAVRoxp == true){mTFKAVRoxp = false;}
      if(wFZlkeTqDK == true){wFZlkeTqDK = false;}
      if(dRBWVRdKoK == true){dRBWVRdKoK = false;}
      if(qqDAnZsxgf == true){qqDAnZsxgf = false;}
      if(JSMFBObFWc == true){JSMFBObFWc = false;}
      if(KuOPcVRioi == true){KuOPcVRioi = false;}
      if(qHzmyFCYyL == true){qHzmyFCYyL = false;}
      if(lVJXBKFwVG == true){lVJXBKFwVG = false;}
      if(oYmMzubmWS == true){oYmMzubmWS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZMANYHIBKX
{ 
  void ZpceLHkWra()
  { 
      bool fhgPPHGBcz = false;
      bool hIZkDOjrHN = false;
      bool lsdbrJgCIJ = false;
      bool sfrUmLKFGC = false;
      bool pIclaIysoK = false;
      bool gpswHlDEWG = false;
      bool ZErTGCQFyq = false;
      bool DdlFXcQrAj = false;
      bool LnMxcCmwMA = false;
      bool IFhzbkQIeY = false;
      bool qstyHCEmYe = false;
      bool VKElulrtpE = false;
      bool OUryhyulcl = false;
      bool MHNbrRsNpZ = false;
      bool yzXhexBuEp = false;
      bool sVSaJWAwPI = false;
      bool HSJlRNxctc = false;
      bool rdEQFPwJTk = false;
      bool wAgmspolRV = false;
      bool RxxgSeokPQ = false;
      string nFCJluTCME;
      string hRSACfKTPw;
      string lFiNNooilA;
      string idEUOMNXKA;
      string BCLWCaeftH;
      string CKypriVnwx;
      string FkPMUDNykp;
      string RlJPtjsLLl;
      string JInexXfNbf;
      string pZbNtQlzBy;
      string NguEoQBiuH;
      string oJbJmwwkPx;
      string XzVFzqJwUd;
      string ysKMXcNjpg;
      string VwSTpfxRZy;
      string TBjEaOLoEx;
      string GFORJwzPkK;
      string hMtiaagCOT;
      string tqVVJwJFkJ;
      string RYerZQhAJt;
      if(nFCJluTCME == NguEoQBiuH){fhgPPHGBcz = true;}
      else if(NguEoQBiuH == nFCJluTCME){qstyHCEmYe = true;}
      if(hRSACfKTPw == oJbJmwwkPx){hIZkDOjrHN = true;}
      else if(oJbJmwwkPx == hRSACfKTPw){VKElulrtpE = true;}
      if(lFiNNooilA == XzVFzqJwUd){lsdbrJgCIJ = true;}
      else if(XzVFzqJwUd == lFiNNooilA){OUryhyulcl = true;}
      if(idEUOMNXKA == ysKMXcNjpg){sfrUmLKFGC = true;}
      else if(ysKMXcNjpg == idEUOMNXKA){MHNbrRsNpZ = true;}
      if(BCLWCaeftH == VwSTpfxRZy){pIclaIysoK = true;}
      else if(VwSTpfxRZy == BCLWCaeftH){yzXhexBuEp = true;}
      if(CKypriVnwx == TBjEaOLoEx){gpswHlDEWG = true;}
      else if(TBjEaOLoEx == CKypriVnwx){sVSaJWAwPI = true;}
      if(FkPMUDNykp == GFORJwzPkK){ZErTGCQFyq = true;}
      else if(GFORJwzPkK == FkPMUDNykp){HSJlRNxctc = true;}
      if(RlJPtjsLLl == hMtiaagCOT){DdlFXcQrAj = true;}
      if(JInexXfNbf == tqVVJwJFkJ){LnMxcCmwMA = true;}
      if(pZbNtQlzBy == RYerZQhAJt){IFhzbkQIeY = true;}
      while(hMtiaagCOT == RlJPtjsLLl){rdEQFPwJTk = true;}
      while(tqVVJwJFkJ == tqVVJwJFkJ){wAgmspolRV = true;}
      while(RYerZQhAJt == RYerZQhAJt){RxxgSeokPQ = true;}
      if(fhgPPHGBcz == true){fhgPPHGBcz = false;}
      if(hIZkDOjrHN == true){hIZkDOjrHN = false;}
      if(lsdbrJgCIJ == true){lsdbrJgCIJ = false;}
      if(sfrUmLKFGC == true){sfrUmLKFGC = false;}
      if(pIclaIysoK == true){pIclaIysoK = false;}
      if(gpswHlDEWG == true){gpswHlDEWG = false;}
      if(ZErTGCQFyq == true){ZErTGCQFyq = false;}
      if(DdlFXcQrAj == true){DdlFXcQrAj = false;}
      if(LnMxcCmwMA == true){LnMxcCmwMA = false;}
      if(IFhzbkQIeY == true){IFhzbkQIeY = false;}
      if(qstyHCEmYe == true){qstyHCEmYe = false;}
      if(VKElulrtpE == true){VKElulrtpE = false;}
      if(OUryhyulcl == true){OUryhyulcl = false;}
      if(MHNbrRsNpZ == true){MHNbrRsNpZ = false;}
      if(yzXhexBuEp == true){yzXhexBuEp = false;}
      if(sVSaJWAwPI == true){sVSaJWAwPI = false;}
      if(HSJlRNxctc == true){HSJlRNxctc = false;}
      if(rdEQFPwJTk == true){rdEQFPwJTk = false;}
      if(wAgmspolRV == true){wAgmspolRV = false;}
      if(RxxgSeokPQ == true){RxxgSeokPQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBZWWUGQFA
{ 
  void ltyZetIteR()
  { 
      bool GblHPcFrUr = false;
      bool rFwXrHVeNk = false;
      bool iygTwXNYVZ = false;
      bool zNaOfgxtYW = false;
      bool pIzYUVPQjo = false;
      bool JJPeWHtRKq = false;
      bool OfVtsedhrL = false;
      bool KbFquayIza = false;
      bool IwogQoxuqX = false;
      bool leihHJlFfp = false;
      bool qgYYdgDYjw = false;
      bool JlSjhSqndD = false;
      bool ghqTYfsXik = false;
      bool nsbJibXPDi = false;
      bool kYLuOzMyzn = false;
      bool RybcIIpEAy = false;
      bool nfoyHQJIAG = false;
      bool ubkuRHWuFZ = false;
      bool TtXtTpRzAa = false;
      bool kSPFtFiMmx = false;
      string KilxbkSpTm;
      string rJmyiuwijV;
      string VlmQBWTszd;
      string TepNGjqtdf;
      string HdIFpkMQVm;
      string wKMGcXwVuE;
      string QZqoTNSZqz;
      string ECFENqdgZP;
      string KCWLhIRjji;
      string nVzYOhmSlc;
      string SlYWitEIrl;
      string tOuetOCeHK;
      string whpILhCfoe;
      string ELuxxXcAcn;
      string EIqynYZTdA;
      string fHKafjwQKA;
      string qXTNhiSyhW;
      string kCCSGnqqTl;
      string IiBnzwAUQN;
      string aMocxfndQF;
      if(KilxbkSpTm == SlYWitEIrl){GblHPcFrUr = true;}
      else if(SlYWitEIrl == KilxbkSpTm){qgYYdgDYjw = true;}
      if(rJmyiuwijV == tOuetOCeHK){rFwXrHVeNk = true;}
      else if(tOuetOCeHK == rJmyiuwijV){JlSjhSqndD = true;}
      if(VlmQBWTszd == whpILhCfoe){iygTwXNYVZ = true;}
      else if(whpILhCfoe == VlmQBWTszd){ghqTYfsXik = true;}
      if(TepNGjqtdf == ELuxxXcAcn){zNaOfgxtYW = true;}
      else if(ELuxxXcAcn == TepNGjqtdf){nsbJibXPDi = true;}
      if(HdIFpkMQVm == EIqynYZTdA){pIzYUVPQjo = true;}
      else if(EIqynYZTdA == HdIFpkMQVm){kYLuOzMyzn = true;}
      if(wKMGcXwVuE == fHKafjwQKA){JJPeWHtRKq = true;}
      else if(fHKafjwQKA == wKMGcXwVuE){RybcIIpEAy = true;}
      if(QZqoTNSZqz == qXTNhiSyhW){OfVtsedhrL = true;}
      else if(qXTNhiSyhW == QZqoTNSZqz){nfoyHQJIAG = true;}
      if(ECFENqdgZP == kCCSGnqqTl){KbFquayIza = true;}
      if(KCWLhIRjji == IiBnzwAUQN){IwogQoxuqX = true;}
      if(nVzYOhmSlc == aMocxfndQF){leihHJlFfp = true;}
      while(kCCSGnqqTl == ECFENqdgZP){ubkuRHWuFZ = true;}
      while(IiBnzwAUQN == IiBnzwAUQN){TtXtTpRzAa = true;}
      while(aMocxfndQF == aMocxfndQF){kSPFtFiMmx = true;}
      if(GblHPcFrUr == true){GblHPcFrUr = false;}
      if(rFwXrHVeNk == true){rFwXrHVeNk = false;}
      if(iygTwXNYVZ == true){iygTwXNYVZ = false;}
      if(zNaOfgxtYW == true){zNaOfgxtYW = false;}
      if(pIzYUVPQjo == true){pIzYUVPQjo = false;}
      if(JJPeWHtRKq == true){JJPeWHtRKq = false;}
      if(OfVtsedhrL == true){OfVtsedhrL = false;}
      if(KbFquayIza == true){KbFquayIza = false;}
      if(IwogQoxuqX == true){IwogQoxuqX = false;}
      if(leihHJlFfp == true){leihHJlFfp = false;}
      if(qgYYdgDYjw == true){qgYYdgDYjw = false;}
      if(JlSjhSqndD == true){JlSjhSqndD = false;}
      if(ghqTYfsXik == true){ghqTYfsXik = false;}
      if(nsbJibXPDi == true){nsbJibXPDi = false;}
      if(kYLuOzMyzn == true){kYLuOzMyzn = false;}
      if(RybcIIpEAy == true){RybcIIpEAy = false;}
      if(nfoyHQJIAG == true){nfoyHQJIAG = false;}
      if(ubkuRHWuFZ == true){ubkuRHWuFZ = false;}
      if(TtXtTpRzAa == true){TtXtTpRzAa = false;}
      if(kSPFtFiMmx == true){kSPFtFiMmx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RJIYYRSERD
{ 
  void jYUiAUfUIT()
  { 
      bool ZCwRUEgqFD = false;
      bool ipkRKYcBGq = false;
      bool fihKTCGNdo = false;
      bool HbXaXeKeWf = false;
      bool ObZtSXwoYO = false;
      bool WTZhgpTkyS = false;
      bool xSMQuGSJte = false;
      bool OxdZcDImru = false;
      bool FRoPSnCptg = false;
      bool KYfEiuPJzL = false;
      bool EltsAYozEc = false;
      bool ggsCMedxxH = false;
      bool DcPMToQZqg = false;
      bool nzmfpSXuOt = false;
      bool yDkRAcedqD = false;
      bool RSMqIbWgZK = false;
      bool IOIXohsMMs = false;
      bool HhhDJArxMp = false;
      bool KmimOUluXO = false;
      bool wpVDkitMbR = false;
      string JdyDHWEEeP;
      string xSoWbVGCWS;
      string gMDgjYuuyg;
      string EwTJjHLfSZ;
      string LGqTaUaNWQ;
      string UHoBlxaRSh;
      string aJFxKAyfmT;
      string JaixGZViFO;
      string xhYhMxHSWm;
      string gtMkyCBsIZ;
      string WuZCHsXruL;
      string aqLEjrjXkN;
      string sfIAmPOyyD;
      string YbaerBHVaS;
      string YPXLLohIAF;
      string SdItgqmZPq;
      string eZsqlzPfLh;
      string jNxRndIwnx;
      string gGxrkuSfyB;
      string OhGimzVfYM;
      if(JdyDHWEEeP == WuZCHsXruL){ZCwRUEgqFD = true;}
      else if(WuZCHsXruL == JdyDHWEEeP){EltsAYozEc = true;}
      if(xSoWbVGCWS == aqLEjrjXkN){ipkRKYcBGq = true;}
      else if(aqLEjrjXkN == xSoWbVGCWS){ggsCMedxxH = true;}
      if(gMDgjYuuyg == sfIAmPOyyD){fihKTCGNdo = true;}
      else if(sfIAmPOyyD == gMDgjYuuyg){DcPMToQZqg = true;}
      if(EwTJjHLfSZ == YbaerBHVaS){HbXaXeKeWf = true;}
      else if(YbaerBHVaS == EwTJjHLfSZ){nzmfpSXuOt = true;}
      if(LGqTaUaNWQ == YPXLLohIAF){ObZtSXwoYO = true;}
      else if(YPXLLohIAF == LGqTaUaNWQ){yDkRAcedqD = true;}
      if(UHoBlxaRSh == SdItgqmZPq){WTZhgpTkyS = true;}
      else if(SdItgqmZPq == UHoBlxaRSh){RSMqIbWgZK = true;}
      if(aJFxKAyfmT == eZsqlzPfLh){xSMQuGSJte = true;}
      else if(eZsqlzPfLh == aJFxKAyfmT){IOIXohsMMs = true;}
      if(JaixGZViFO == jNxRndIwnx){OxdZcDImru = true;}
      if(xhYhMxHSWm == gGxrkuSfyB){FRoPSnCptg = true;}
      if(gtMkyCBsIZ == OhGimzVfYM){KYfEiuPJzL = true;}
      while(jNxRndIwnx == JaixGZViFO){HhhDJArxMp = true;}
      while(gGxrkuSfyB == gGxrkuSfyB){KmimOUluXO = true;}
      while(OhGimzVfYM == OhGimzVfYM){wpVDkitMbR = true;}
      if(ZCwRUEgqFD == true){ZCwRUEgqFD = false;}
      if(ipkRKYcBGq == true){ipkRKYcBGq = false;}
      if(fihKTCGNdo == true){fihKTCGNdo = false;}
      if(HbXaXeKeWf == true){HbXaXeKeWf = false;}
      if(ObZtSXwoYO == true){ObZtSXwoYO = false;}
      if(WTZhgpTkyS == true){WTZhgpTkyS = false;}
      if(xSMQuGSJte == true){xSMQuGSJte = false;}
      if(OxdZcDImru == true){OxdZcDImru = false;}
      if(FRoPSnCptg == true){FRoPSnCptg = false;}
      if(KYfEiuPJzL == true){KYfEiuPJzL = false;}
      if(EltsAYozEc == true){EltsAYozEc = false;}
      if(ggsCMedxxH == true){ggsCMedxxH = false;}
      if(DcPMToQZqg == true){DcPMToQZqg = false;}
      if(nzmfpSXuOt == true){nzmfpSXuOt = false;}
      if(yDkRAcedqD == true){yDkRAcedqD = false;}
      if(RSMqIbWgZK == true){RSMqIbWgZK = false;}
      if(IOIXohsMMs == true){IOIXohsMMs = false;}
      if(HhhDJArxMp == true){HhhDJArxMp = false;}
      if(KmimOUluXO == true){KmimOUluXO = false;}
      if(wpVDkitMbR == true){wpVDkitMbR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEBSDWTFJB
{ 
  void LDXGcppGgx()
  { 
      bool ySdqfchfAa = false;
      bool jbGqcsxCcU = false;
      bool rGNozNQEVF = false;
      bool SpnirJifgA = false;
      bool eNHgFyNOUf = false;
      bool KcetsrEnqS = false;
      bool LdJuIsnWzS = false;
      bool KQVbpeyfiB = false;
      bool zBiptoLtoA = false;
      bool FtoOoBDMYL = false;
      bool JqPCUtHCDO = false;
      bool tYEoSJtSBT = false;
      bool htgyNQbGmn = false;
      bool akHXrIlgVA = false;
      bool gIpaGgozue = false;
      bool GjLFcPJQnE = false;
      bool SBPPnIQgxK = false;
      bool XNxAlZEGrg = false;
      bool abKIhpZBtb = false;
      bool yUrQhfsamx = false;
      string ufTGIEBszK;
      string xtcgVNQwPp;
      string QOOLhrIPKO;
      string gJezKRBjLq;
      string yanjILIqpi;
      string HsSdVgQIYP;
      string wlijdmPcWE;
      string LfjXrpZdDV;
      string jQZbHmqBcd;
      string AsLwtMrEGU;
      string weUkXaJtlf;
      string GmEDeeLGbq;
      string uNzrDRUnce;
      string yVXhYFwnEf;
      string cxOxWNoIQO;
      string AkbOZiebhF;
      string GUQHhkOWeZ;
      string iXCwNyyCUp;
      string cMXNdMsIIo;
      string ZUGyZIfHOl;
      if(ufTGIEBszK == weUkXaJtlf){ySdqfchfAa = true;}
      else if(weUkXaJtlf == ufTGIEBszK){JqPCUtHCDO = true;}
      if(xtcgVNQwPp == GmEDeeLGbq){jbGqcsxCcU = true;}
      else if(GmEDeeLGbq == xtcgVNQwPp){tYEoSJtSBT = true;}
      if(QOOLhrIPKO == uNzrDRUnce){rGNozNQEVF = true;}
      else if(uNzrDRUnce == QOOLhrIPKO){htgyNQbGmn = true;}
      if(gJezKRBjLq == yVXhYFwnEf){SpnirJifgA = true;}
      else if(yVXhYFwnEf == gJezKRBjLq){akHXrIlgVA = true;}
      if(yanjILIqpi == cxOxWNoIQO){eNHgFyNOUf = true;}
      else if(cxOxWNoIQO == yanjILIqpi){gIpaGgozue = true;}
      if(HsSdVgQIYP == AkbOZiebhF){KcetsrEnqS = true;}
      else if(AkbOZiebhF == HsSdVgQIYP){GjLFcPJQnE = true;}
      if(wlijdmPcWE == GUQHhkOWeZ){LdJuIsnWzS = true;}
      else if(GUQHhkOWeZ == wlijdmPcWE){SBPPnIQgxK = true;}
      if(LfjXrpZdDV == iXCwNyyCUp){KQVbpeyfiB = true;}
      if(jQZbHmqBcd == cMXNdMsIIo){zBiptoLtoA = true;}
      if(AsLwtMrEGU == ZUGyZIfHOl){FtoOoBDMYL = true;}
      while(iXCwNyyCUp == LfjXrpZdDV){XNxAlZEGrg = true;}
      while(cMXNdMsIIo == cMXNdMsIIo){abKIhpZBtb = true;}
      while(ZUGyZIfHOl == ZUGyZIfHOl){yUrQhfsamx = true;}
      if(ySdqfchfAa == true){ySdqfchfAa = false;}
      if(jbGqcsxCcU == true){jbGqcsxCcU = false;}
      if(rGNozNQEVF == true){rGNozNQEVF = false;}
      if(SpnirJifgA == true){SpnirJifgA = false;}
      if(eNHgFyNOUf == true){eNHgFyNOUf = false;}
      if(KcetsrEnqS == true){KcetsrEnqS = false;}
      if(LdJuIsnWzS == true){LdJuIsnWzS = false;}
      if(KQVbpeyfiB == true){KQVbpeyfiB = false;}
      if(zBiptoLtoA == true){zBiptoLtoA = false;}
      if(FtoOoBDMYL == true){FtoOoBDMYL = false;}
      if(JqPCUtHCDO == true){JqPCUtHCDO = false;}
      if(tYEoSJtSBT == true){tYEoSJtSBT = false;}
      if(htgyNQbGmn == true){htgyNQbGmn = false;}
      if(akHXrIlgVA == true){akHXrIlgVA = false;}
      if(gIpaGgozue == true){gIpaGgozue = false;}
      if(GjLFcPJQnE == true){GjLFcPJQnE = false;}
      if(SBPPnIQgxK == true){SBPPnIQgxK = false;}
      if(XNxAlZEGrg == true){XNxAlZEGrg = false;}
      if(abKIhpZBtb == true){abKIhpZBtb = false;}
      if(yUrQhfsamx == true){yUrQhfsamx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RKWIMQSBSH
{ 
  void ZjCUMSOPjd()
  { 
      bool csYWtGPZHN = false;
      bool pRBPoBhxKu = false;
      bool MtBDYKKNNP = false;
      bool nCKOKQMwgS = false;
      bool NITVTVIxjq = false;
      bool fyKWoirVyi = false;
      bool wCLqYmGmFY = false;
      bool nkQqgDafiC = false;
      bool CNdWjprmZa = false;
      bool XqxyWLwbwf = false;
      bool OVrKDthSok = false;
      bool IMlugiXoHi = false;
      bool uSMdAxnRUV = false;
      bool GzjDnfUSSp = false;
      bool IYynSLEBRm = false;
      bool mGUMkuINJF = false;
      bool FPxSdJciHA = false;
      bool NFWQaVUXLo = false;
      bool smAhhzdWSs = false;
      bool WHIMkraeKI = false;
      string oChaQXRGgK;
      string reXlZjQtYr;
      string moddbcQThA;
      string ADIELFAVQU;
      string SnCnrNgGKW;
      string HhSOFAYDzn;
      string HyXgJoWSZT;
      string judEZylpkO;
      string uJILsRjtyL;
      string gwWbNUQVdD;
      string pNgqmLDOoH;
      string NhSjsyoMnr;
      string EcTOmmXCpE;
      string hQMhXgcRYg;
      string OUEqyydliP;
      string eDhkyNtRDz;
      string mBYjYwUjML;
      string VXmHdjXcQn;
      string JlTaZdiaiJ;
      string mKNZsNwURB;
      if(oChaQXRGgK == pNgqmLDOoH){csYWtGPZHN = true;}
      else if(pNgqmLDOoH == oChaQXRGgK){OVrKDthSok = true;}
      if(reXlZjQtYr == NhSjsyoMnr){pRBPoBhxKu = true;}
      else if(NhSjsyoMnr == reXlZjQtYr){IMlugiXoHi = true;}
      if(moddbcQThA == EcTOmmXCpE){MtBDYKKNNP = true;}
      else if(EcTOmmXCpE == moddbcQThA){uSMdAxnRUV = true;}
      if(ADIELFAVQU == hQMhXgcRYg){nCKOKQMwgS = true;}
      else if(hQMhXgcRYg == ADIELFAVQU){GzjDnfUSSp = true;}
      if(SnCnrNgGKW == OUEqyydliP){NITVTVIxjq = true;}
      else if(OUEqyydliP == SnCnrNgGKW){IYynSLEBRm = true;}
      if(HhSOFAYDzn == eDhkyNtRDz){fyKWoirVyi = true;}
      else if(eDhkyNtRDz == HhSOFAYDzn){mGUMkuINJF = true;}
      if(HyXgJoWSZT == mBYjYwUjML){wCLqYmGmFY = true;}
      else if(mBYjYwUjML == HyXgJoWSZT){FPxSdJciHA = true;}
      if(judEZylpkO == VXmHdjXcQn){nkQqgDafiC = true;}
      if(uJILsRjtyL == JlTaZdiaiJ){CNdWjprmZa = true;}
      if(gwWbNUQVdD == mKNZsNwURB){XqxyWLwbwf = true;}
      while(VXmHdjXcQn == judEZylpkO){NFWQaVUXLo = true;}
      while(JlTaZdiaiJ == JlTaZdiaiJ){smAhhzdWSs = true;}
      while(mKNZsNwURB == mKNZsNwURB){WHIMkraeKI = true;}
      if(csYWtGPZHN == true){csYWtGPZHN = false;}
      if(pRBPoBhxKu == true){pRBPoBhxKu = false;}
      if(MtBDYKKNNP == true){MtBDYKKNNP = false;}
      if(nCKOKQMwgS == true){nCKOKQMwgS = false;}
      if(NITVTVIxjq == true){NITVTVIxjq = false;}
      if(fyKWoirVyi == true){fyKWoirVyi = false;}
      if(wCLqYmGmFY == true){wCLqYmGmFY = false;}
      if(nkQqgDafiC == true){nkQqgDafiC = false;}
      if(CNdWjprmZa == true){CNdWjprmZa = false;}
      if(XqxyWLwbwf == true){XqxyWLwbwf = false;}
      if(OVrKDthSok == true){OVrKDthSok = false;}
      if(IMlugiXoHi == true){IMlugiXoHi = false;}
      if(uSMdAxnRUV == true){uSMdAxnRUV = false;}
      if(GzjDnfUSSp == true){GzjDnfUSSp = false;}
      if(IYynSLEBRm == true){IYynSLEBRm = false;}
      if(mGUMkuINJF == true){mGUMkuINJF = false;}
      if(FPxSdJciHA == true){FPxSdJciHA = false;}
      if(NFWQaVUXLo == true){NFWQaVUXLo = false;}
      if(smAhhzdWSs == true){smAhhzdWSs = false;}
      if(WHIMkraeKI == true){WHIMkraeKI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUBOJDWBDD
{ 
  void SeIUmCVnYo()
  { 
      bool QcdaHrBdAL = false;
      bool hsDZQsJiNi = false;
      bool zDRWcyztmb = false;
      bool BaWrWQHLAF = false;
      bool apSYSFaPVs = false;
      bool fgfYNMKGxI = false;
      bool rGpYJHVKDA = false;
      bool kxhIIJkrEX = false;
      bool XiYtwUtxeJ = false;
      bool GBNqNTAtPL = false;
      bool iPMUHhyXQD = false;
      bool aRCYkIhwco = false;
      bool MYfstjjqtn = false;
      bool JqcrnIWDlN = false;
      bool VVgainznFF = false;
      bool lDQayKiSaX = false;
      bool yHdbtjnJkc = false;
      bool kdJOSqqEKF = false;
      bool kukoCFZCsc = false;
      bool YDcNPOrEgz = false;
      string JAGBJxjqxS;
      string bWXFZtKrqT;
      string otpbnMxzhV;
      string xOxhqEZqAA;
      string MTYnNEPLIC;
      string kcZzqPJdMx;
      string AjIbVNZpOU;
      string TSrqHVVCNi;
      string wkqejUoypa;
      string tueDzbLwRA;
      string eYxmiSjhqV;
      string sHPcAPscrB;
      string XbAmZYmoqf;
      string KYjNEXmDwR;
      string jGGUhmeCCi;
      string hhEQcDYJMJ;
      string euqLLUWCXb;
      string bpgZQRUfFm;
      string sklHxbUSjB;
      string ydplloPtIN;
      if(JAGBJxjqxS == eYxmiSjhqV){QcdaHrBdAL = true;}
      else if(eYxmiSjhqV == JAGBJxjqxS){iPMUHhyXQD = true;}
      if(bWXFZtKrqT == sHPcAPscrB){hsDZQsJiNi = true;}
      else if(sHPcAPscrB == bWXFZtKrqT){aRCYkIhwco = true;}
      if(otpbnMxzhV == XbAmZYmoqf){zDRWcyztmb = true;}
      else if(XbAmZYmoqf == otpbnMxzhV){MYfstjjqtn = true;}
      if(xOxhqEZqAA == KYjNEXmDwR){BaWrWQHLAF = true;}
      else if(KYjNEXmDwR == xOxhqEZqAA){JqcrnIWDlN = true;}
      if(MTYnNEPLIC == jGGUhmeCCi){apSYSFaPVs = true;}
      else if(jGGUhmeCCi == MTYnNEPLIC){VVgainznFF = true;}
      if(kcZzqPJdMx == hhEQcDYJMJ){fgfYNMKGxI = true;}
      else if(hhEQcDYJMJ == kcZzqPJdMx){lDQayKiSaX = true;}
      if(AjIbVNZpOU == euqLLUWCXb){rGpYJHVKDA = true;}
      else if(euqLLUWCXb == AjIbVNZpOU){yHdbtjnJkc = true;}
      if(TSrqHVVCNi == bpgZQRUfFm){kxhIIJkrEX = true;}
      if(wkqejUoypa == sklHxbUSjB){XiYtwUtxeJ = true;}
      if(tueDzbLwRA == ydplloPtIN){GBNqNTAtPL = true;}
      while(bpgZQRUfFm == TSrqHVVCNi){kdJOSqqEKF = true;}
      while(sklHxbUSjB == sklHxbUSjB){kukoCFZCsc = true;}
      while(ydplloPtIN == ydplloPtIN){YDcNPOrEgz = true;}
      if(QcdaHrBdAL == true){QcdaHrBdAL = false;}
      if(hsDZQsJiNi == true){hsDZQsJiNi = false;}
      if(zDRWcyztmb == true){zDRWcyztmb = false;}
      if(BaWrWQHLAF == true){BaWrWQHLAF = false;}
      if(apSYSFaPVs == true){apSYSFaPVs = false;}
      if(fgfYNMKGxI == true){fgfYNMKGxI = false;}
      if(rGpYJHVKDA == true){rGpYJHVKDA = false;}
      if(kxhIIJkrEX == true){kxhIIJkrEX = false;}
      if(XiYtwUtxeJ == true){XiYtwUtxeJ = false;}
      if(GBNqNTAtPL == true){GBNqNTAtPL = false;}
      if(iPMUHhyXQD == true){iPMUHhyXQD = false;}
      if(aRCYkIhwco == true){aRCYkIhwco = false;}
      if(MYfstjjqtn == true){MYfstjjqtn = false;}
      if(JqcrnIWDlN == true){JqcrnIWDlN = false;}
      if(VVgainznFF == true){VVgainznFF = false;}
      if(lDQayKiSaX == true){lDQayKiSaX = false;}
      if(yHdbtjnJkc == true){yHdbtjnJkc = false;}
      if(kdJOSqqEKF == true){kdJOSqqEKF = false;}
      if(kukoCFZCsc == true){kukoCFZCsc = false;}
      if(YDcNPOrEgz == true){YDcNPOrEgz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWFWSKHYDW
{ 
  void peUtkkmJhz()
  { 
      bool WuEzOLJIFn = false;
      bool CpouOmoVmY = false;
      bool iDwjrTZrsU = false;
      bool yOaGXIATIT = false;
      bool AxCUjuRrDa = false;
      bool UaWbLTyTGt = false;
      bool lQPjomPhWF = false;
      bool mUMTXlBbzx = false;
      bool BgnRAXryuE = false;
      bool KfMOhjgRew = false;
      bool ejUxnzNDEZ = false;
      bool SWUJsEcyjQ = false;
      bool uRmSuGIykn = false;
      bool EiwCRRMpcA = false;
      bool JntVkmLCUc = false;
      bool GigNBNwCCg = false;
      bool pPRPUiaRqa = false;
      bool rlUiHGWRgH = false;
      bool uFcIgVChBD = false;
      bool UJnwKsWdAC = false;
      string hwUEzgVnmL;
      string KzWhWFissZ;
      string VWXLaefggt;
      string pdtJDIFphQ;
      string FYWAAhsFhX;
      string QRirKKYIdU;
      string AoHrUfEMdN;
      string ArLcUwAWLr;
      string kZyJdYuBzs;
      string jwMNPPRdfT;
      string dgbTWXGFXN;
      string KBwkiZqxOw;
      string kCNkdDfxME;
      string dVqrOEydlG;
      string Rodkihzadp;
      string YUPiiaSqpS;
      string rIrTinKEWd;
      string bMKHduYbBu;
      string EETWfJFHIm;
      string kHmSOJwKBt;
      if(hwUEzgVnmL == dgbTWXGFXN){WuEzOLJIFn = true;}
      else if(dgbTWXGFXN == hwUEzgVnmL){ejUxnzNDEZ = true;}
      if(KzWhWFissZ == KBwkiZqxOw){CpouOmoVmY = true;}
      else if(KBwkiZqxOw == KzWhWFissZ){SWUJsEcyjQ = true;}
      if(VWXLaefggt == kCNkdDfxME){iDwjrTZrsU = true;}
      else if(kCNkdDfxME == VWXLaefggt){uRmSuGIykn = true;}
      if(pdtJDIFphQ == dVqrOEydlG){yOaGXIATIT = true;}
      else if(dVqrOEydlG == pdtJDIFphQ){EiwCRRMpcA = true;}
      if(FYWAAhsFhX == Rodkihzadp){AxCUjuRrDa = true;}
      else if(Rodkihzadp == FYWAAhsFhX){JntVkmLCUc = true;}
      if(QRirKKYIdU == YUPiiaSqpS){UaWbLTyTGt = true;}
      else if(YUPiiaSqpS == QRirKKYIdU){GigNBNwCCg = true;}
      if(AoHrUfEMdN == rIrTinKEWd){lQPjomPhWF = true;}
      else if(rIrTinKEWd == AoHrUfEMdN){pPRPUiaRqa = true;}
      if(ArLcUwAWLr == bMKHduYbBu){mUMTXlBbzx = true;}
      if(kZyJdYuBzs == EETWfJFHIm){BgnRAXryuE = true;}
      if(jwMNPPRdfT == kHmSOJwKBt){KfMOhjgRew = true;}
      while(bMKHduYbBu == ArLcUwAWLr){rlUiHGWRgH = true;}
      while(EETWfJFHIm == EETWfJFHIm){uFcIgVChBD = true;}
      while(kHmSOJwKBt == kHmSOJwKBt){UJnwKsWdAC = true;}
      if(WuEzOLJIFn == true){WuEzOLJIFn = false;}
      if(CpouOmoVmY == true){CpouOmoVmY = false;}
      if(iDwjrTZrsU == true){iDwjrTZrsU = false;}
      if(yOaGXIATIT == true){yOaGXIATIT = false;}
      if(AxCUjuRrDa == true){AxCUjuRrDa = false;}
      if(UaWbLTyTGt == true){UaWbLTyTGt = false;}
      if(lQPjomPhWF == true){lQPjomPhWF = false;}
      if(mUMTXlBbzx == true){mUMTXlBbzx = false;}
      if(BgnRAXryuE == true){BgnRAXryuE = false;}
      if(KfMOhjgRew == true){KfMOhjgRew = false;}
      if(ejUxnzNDEZ == true){ejUxnzNDEZ = false;}
      if(SWUJsEcyjQ == true){SWUJsEcyjQ = false;}
      if(uRmSuGIykn == true){uRmSuGIykn = false;}
      if(EiwCRRMpcA == true){EiwCRRMpcA = false;}
      if(JntVkmLCUc == true){JntVkmLCUc = false;}
      if(GigNBNwCCg == true){GigNBNwCCg = false;}
      if(pPRPUiaRqa == true){pPRPUiaRqa = false;}
      if(rlUiHGWRgH == true){rlUiHGWRgH = false;}
      if(uFcIgVChBD == true){uFcIgVChBD = false;}
      if(UJnwKsWdAC == true){UJnwKsWdAC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YRHHGTSEBF
{ 
  void kFcTfZbUBC()
  { 
      bool opikMQJsSj = false;
      bool MEIjznfLHm = false;
      bool zeIKWjpiqh = false;
      bool azsIkJFOPB = false;
      bool uNszMJrUfG = false;
      bool XlSqzKhXNc = false;
      bool aZCkIMKAyo = false;
      bool hRuGrllIyN = false;
      bool qUCjJogCIa = false;
      bool bhAmaUKHqz = false;
      bool yrVqXGqLyM = false;
      bool YYYAlGWSaS = false;
      bool eIqXNAQHfX = false;
      bool adRyOzyLLD = false;
      bool yUDwCCIABT = false;
      bool yrfXUpAydX = false;
      bool pifaktGZlm = false;
      bool IKGXUJEuVK = false;
      bool qQGLYixtdX = false;
      bool yzhnNOocKH = false;
      string UdncOgwJoS;
      string IoummQALZa;
      string YtcrLYjzAR;
      string JuMIZpOeox;
      string WcOjgnJpOk;
      string HXrIQZBuRp;
      string wxJWINclMw;
      string BVVbEwfsLW;
      string OtjOKlCDqA;
      string oSNzAZSraT;
      string LXcSikCQEU;
      string tIjtbCMtLV;
      string KYuMHiHWbe;
      string cmRrKpQQfY;
      string jlzWFfiSWy;
      string MYfFIlcPLz;
      string dfnZrGqrjk;
      string kuOllYZXHa;
      string AozcREHLiY;
      string NBFfuDxZey;
      if(UdncOgwJoS == LXcSikCQEU){opikMQJsSj = true;}
      else if(LXcSikCQEU == UdncOgwJoS){yrVqXGqLyM = true;}
      if(IoummQALZa == tIjtbCMtLV){MEIjznfLHm = true;}
      else if(tIjtbCMtLV == IoummQALZa){YYYAlGWSaS = true;}
      if(YtcrLYjzAR == KYuMHiHWbe){zeIKWjpiqh = true;}
      else if(KYuMHiHWbe == YtcrLYjzAR){eIqXNAQHfX = true;}
      if(JuMIZpOeox == cmRrKpQQfY){azsIkJFOPB = true;}
      else if(cmRrKpQQfY == JuMIZpOeox){adRyOzyLLD = true;}
      if(WcOjgnJpOk == jlzWFfiSWy){uNszMJrUfG = true;}
      else if(jlzWFfiSWy == WcOjgnJpOk){yUDwCCIABT = true;}
      if(HXrIQZBuRp == MYfFIlcPLz){XlSqzKhXNc = true;}
      else if(MYfFIlcPLz == HXrIQZBuRp){yrfXUpAydX = true;}
      if(wxJWINclMw == dfnZrGqrjk){aZCkIMKAyo = true;}
      else if(dfnZrGqrjk == wxJWINclMw){pifaktGZlm = true;}
      if(BVVbEwfsLW == kuOllYZXHa){hRuGrllIyN = true;}
      if(OtjOKlCDqA == AozcREHLiY){qUCjJogCIa = true;}
      if(oSNzAZSraT == NBFfuDxZey){bhAmaUKHqz = true;}
      while(kuOllYZXHa == BVVbEwfsLW){IKGXUJEuVK = true;}
      while(AozcREHLiY == AozcREHLiY){qQGLYixtdX = true;}
      while(NBFfuDxZey == NBFfuDxZey){yzhnNOocKH = true;}
      if(opikMQJsSj == true){opikMQJsSj = false;}
      if(MEIjznfLHm == true){MEIjznfLHm = false;}
      if(zeIKWjpiqh == true){zeIKWjpiqh = false;}
      if(azsIkJFOPB == true){azsIkJFOPB = false;}
      if(uNszMJrUfG == true){uNszMJrUfG = false;}
      if(XlSqzKhXNc == true){XlSqzKhXNc = false;}
      if(aZCkIMKAyo == true){aZCkIMKAyo = false;}
      if(hRuGrllIyN == true){hRuGrllIyN = false;}
      if(qUCjJogCIa == true){qUCjJogCIa = false;}
      if(bhAmaUKHqz == true){bhAmaUKHqz = false;}
      if(yrVqXGqLyM == true){yrVqXGqLyM = false;}
      if(YYYAlGWSaS == true){YYYAlGWSaS = false;}
      if(eIqXNAQHfX == true){eIqXNAQHfX = false;}
      if(adRyOzyLLD == true){adRyOzyLLD = false;}
      if(yUDwCCIABT == true){yUDwCCIABT = false;}
      if(yrfXUpAydX == true){yrfXUpAydX = false;}
      if(pifaktGZlm == true){pifaktGZlm = false;}
      if(IKGXUJEuVK == true){IKGXUJEuVK = false;}
      if(qQGLYixtdX == true){qQGLYixtdX = false;}
      if(yzhnNOocKH == true){yzhnNOocKH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JDLQBKPKLR
{ 
  void sfCrYaKUZP()
  { 
      bool wIgqEswkXz = false;
      bool UwYtdSdMkC = false;
      bool tVwjZzfwJq = false;
      bool HJiyuTHLcb = false;
      bool fLAyrgBtOj = false;
      bool TBcSRZLxRE = false;
      bool MAbgqLMazK = false;
      bool KRjIWiUxqs = false;
      bool xlgYWFgPfU = false;
      bool HJtXOeiSHg = false;
      bool TZuEYBRUwi = false;
      bool FOGYGaSCJl = false;
      bool exudCBXLsq = false;
      bool zCpKYWqbAV = false;
      bool nMTwPrDVQn = false;
      bool MgJUCWeQCW = false;
      bool cFaEiCYwzj = false;
      bool jpCmxScyNJ = false;
      bool yCuFeSsUIC = false;
      bool rZZcrhkPNM = false;
      string ndEYMFNlXn;
      string xDapasgSpD;
      string nodUdsKUNQ;
      string KAAanWzdtM;
      string FzaKymHAYd;
      string eCjohzzjtT;
      string usYHcwDzCE;
      string tDXdxoNTVq;
      string lJwikIPLso;
      string WPiaRMaTgC;
      string jHyTjbdGqr;
      string kfNDglxoVT;
      string fqFNhdTwMk;
      string NtlTGdLbzJ;
      string eJTADpCete;
      string OlxNVrBjlF;
      string HgtGeqttxC;
      string aVoLoWXFKq;
      string boCgVbwYxN;
      string caosCxONVM;
      if(ndEYMFNlXn == jHyTjbdGqr){wIgqEswkXz = true;}
      else if(jHyTjbdGqr == ndEYMFNlXn){TZuEYBRUwi = true;}
      if(xDapasgSpD == kfNDglxoVT){UwYtdSdMkC = true;}
      else if(kfNDglxoVT == xDapasgSpD){FOGYGaSCJl = true;}
      if(nodUdsKUNQ == fqFNhdTwMk){tVwjZzfwJq = true;}
      else if(fqFNhdTwMk == nodUdsKUNQ){exudCBXLsq = true;}
      if(KAAanWzdtM == NtlTGdLbzJ){HJiyuTHLcb = true;}
      else if(NtlTGdLbzJ == KAAanWzdtM){zCpKYWqbAV = true;}
      if(FzaKymHAYd == eJTADpCete){fLAyrgBtOj = true;}
      else if(eJTADpCete == FzaKymHAYd){nMTwPrDVQn = true;}
      if(eCjohzzjtT == OlxNVrBjlF){TBcSRZLxRE = true;}
      else if(OlxNVrBjlF == eCjohzzjtT){MgJUCWeQCW = true;}
      if(usYHcwDzCE == HgtGeqttxC){MAbgqLMazK = true;}
      else if(HgtGeqttxC == usYHcwDzCE){cFaEiCYwzj = true;}
      if(tDXdxoNTVq == aVoLoWXFKq){KRjIWiUxqs = true;}
      if(lJwikIPLso == boCgVbwYxN){xlgYWFgPfU = true;}
      if(WPiaRMaTgC == caosCxONVM){HJtXOeiSHg = true;}
      while(aVoLoWXFKq == tDXdxoNTVq){jpCmxScyNJ = true;}
      while(boCgVbwYxN == boCgVbwYxN){yCuFeSsUIC = true;}
      while(caosCxONVM == caosCxONVM){rZZcrhkPNM = true;}
      if(wIgqEswkXz == true){wIgqEswkXz = false;}
      if(UwYtdSdMkC == true){UwYtdSdMkC = false;}
      if(tVwjZzfwJq == true){tVwjZzfwJq = false;}
      if(HJiyuTHLcb == true){HJiyuTHLcb = false;}
      if(fLAyrgBtOj == true){fLAyrgBtOj = false;}
      if(TBcSRZLxRE == true){TBcSRZLxRE = false;}
      if(MAbgqLMazK == true){MAbgqLMazK = false;}
      if(KRjIWiUxqs == true){KRjIWiUxqs = false;}
      if(xlgYWFgPfU == true){xlgYWFgPfU = false;}
      if(HJtXOeiSHg == true){HJtXOeiSHg = false;}
      if(TZuEYBRUwi == true){TZuEYBRUwi = false;}
      if(FOGYGaSCJl == true){FOGYGaSCJl = false;}
      if(exudCBXLsq == true){exudCBXLsq = false;}
      if(zCpKYWqbAV == true){zCpKYWqbAV = false;}
      if(nMTwPrDVQn == true){nMTwPrDVQn = false;}
      if(MgJUCWeQCW == true){MgJUCWeQCW = false;}
      if(cFaEiCYwzj == true){cFaEiCYwzj = false;}
      if(jpCmxScyNJ == true){jpCmxScyNJ = false;}
      if(yCuFeSsUIC == true){yCuFeSsUIC = false;}
      if(rZZcrhkPNM == true){rZZcrhkPNM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKPAAHASHK
{ 
  void BlwZNuHcEg()
  { 
      bool MacLsDFrcY = false;
      bool JpVWmLIrOy = false;
      bool UVqCqwGeGg = false;
      bool qjMhKeSePg = false;
      bool zAyHOynrOB = false;
      bool ZYCmaqjZTw = false;
      bool wZkuhYcnLH = false;
      bool sdcgzTWinr = false;
      bool INPFGRhZHT = false;
      bool trLSjYPCZo = false;
      bool VzgHHwuUnG = false;
      bool TBkamhJfnP = false;
      bool pCgrNASJxZ = false;
      bool EUJyWIgIxK = false;
      bool VNkAAsHjfC = false;
      bool PiNJySSnsG = false;
      bool dlXOBzqlEd = false;
      bool AAhdscQfrT = false;
      bool shdtJUGzAD = false;
      bool prOpfjpWyA = false;
      string wIoFTLwCKA;
      string KtEQTkAzBr;
      string pXaghEyagu;
      string iIBiBJtlQc;
      string bjRLJVyCmn;
      string TQhaAYhIXP;
      string MUUPRBrVPJ;
      string pNiYQGGPWM;
      string FwnraRaZhb;
      string bkOAQGOBtH;
      string cbmcxGhIJt;
      string SRlKJQgboA;
      string aRmmhEyhIK;
      string qEUOicJKuU;
      string iRQnJJzDqz;
      string ZlLtgKozur;
      string HzAzCNxXaf;
      string GVgTQIBydX;
      string FupIkEragX;
      string nJPCNiRQku;
      if(wIoFTLwCKA == cbmcxGhIJt){MacLsDFrcY = true;}
      else if(cbmcxGhIJt == wIoFTLwCKA){VzgHHwuUnG = true;}
      if(KtEQTkAzBr == SRlKJQgboA){JpVWmLIrOy = true;}
      else if(SRlKJQgboA == KtEQTkAzBr){TBkamhJfnP = true;}
      if(pXaghEyagu == aRmmhEyhIK){UVqCqwGeGg = true;}
      else if(aRmmhEyhIK == pXaghEyagu){pCgrNASJxZ = true;}
      if(iIBiBJtlQc == qEUOicJKuU){qjMhKeSePg = true;}
      else if(qEUOicJKuU == iIBiBJtlQc){EUJyWIgIxK = true;}
      if(bjRLJVyCmn == iRQnJJzDqz){zAyHOynrOB = true;}
      else if(iRQnJJzDqz == bjRLJVyCmn){VNkAAsHjfC = true;}
      if(TQhaAYhIXP == ZlLtgKozur){ZYCmaqjZTw = true;}
      else if(ZlLtgKozur == TQhaAYhIXP){PiNJySSnsG = true;}
      if(MUUPRBrVPJ == HzAzCNxXaf){wZkuhYcnLH = true;}
      else if(HzAzCNxXaf == MUUPRBrVPJ){dlXOBzqlEd = true;}
      if(pNiYQGGPWM == GVgTQIBydX){sdcgzTWinr = true;}
      if(FwnraRaZhb == FupIkEragX){INPFGRhZHT = true;}
      if(bkOAQGOBtH == nJPCNiRQku){trLSjYPCZo = true;}
      while(GVgTQIBydX == pNiYQGGPWM){AAhdscQfrT = true;}
      while(FupIkEragX == FupIkEragX){shdtJUGzAD = true;}
      while(nJPCNiRQku == nJPCNiRQku){prOpfjpWyA = true;}
      if(MacLsDFrcY == true){MacLsDFrcY = false;}
      if(JpVWmLIrOy == true){JpVWmLIrOy = false;}
      if(UVqCqwGeGg == true){UVqCqwGeGg = false;}
      if(qjMhKeSePg == true){qjMhKeSePg = false;}
      if(zAyHOynrOB == true){zAyHOynrOB = false;}
      if(ZYCmaqjZTw == true){ZYCmaqjZTw = false;}
      if(wZkuhYcnLH == true){wZkuhYcnLH = false;}
      if(sdcgzTWinr == true){sdcgzTWinr = false;}
      if(INPFGRhZHT == true){INPFGRhZHT = false;}
      if(trLSjYPCZo == true){trLSjYPCZo = false;}
      if(VzgHHwuUnG == true){VzgHHwuUnG = false;}
      if(TBkamhJfnP == true){TBkamhJfnP = false;}
      if(pCgrNASJxZ == true){pCgrNASJxZ = false;}
      if(EUJyWIgIxK == true){EUJyWIgIxK = false;}
      if(VNkAAsHjfC == true){VNkAAsHjfC = false;}
      if(PiNJySSnsG == true){PiNJySSnsG = false;}
      if(dlXOBzqlEd == true){dlXOBzqlEd = false;}
      if(AAhdscQfrT == true){AAhdscQfrT = false;}
      if(shdtJUGzAD == true){shdtJUGzAD = false;}
      if(prOpfjpWyA == true){prOpfjpWyA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SUAJMDTAZV
{ 
  void DSuGmkpHnf()
  { 
      bool yItTWYfxiw = false;
      bool fTpSTgwPri = false;
      bool kSxryVWPIs = false;
      bool nIogOIUjwd = false;
      bool grXKtzyqVS = false;
      bool yrrUxeLBUB = false;
      bool CQopIXdJDK = false;
      bool LMTOCrtmyy = false;
      bool WetotuPUii = false;
      bool xTOtaPDhCV = false;
      bool VomKHlYdSF = false;
      bool kYDVeWWzuM = false;
      bool IJZUNrxYml = false;
      bool nMkbchqihI = false;
      bool WkBdxYQsPD = false;
      bool sEloNLOSwO = false;
      bool ozpgQYmarx = false;
      bool emRloWHwWo = false;
      bool bDJirjZuOR = false;
      bool SYmSTWtUNY = false;
      string KAYiRBTfRR;
      string cqrPlDHwSr;
      string IiJkOfQpHw;
      string zIdFIVFAWa;
      string GqeYCNsmhO;
      string dPdqLbpmTl;
      string jdYVSTNmGQ;
      string xHZrlQEkiA;
      string mcHrRjdltg;
      string eSfkpcSIFh;
      string AFgRQWolFt;
      string WFESzHVgDh;
      string oasZleboCJ;
      string yueAAgwoau;
      string trgzJYNMlh;
      string GkFWsZMGfk;
      string uAjuuaaESR;
      string KgFInwssPM;
      string RODTDMpHGZ;
      string ToJoztIkDi;
      if(KAYiRBTfRR == AFgRQWolFt){yItTWYfxiw = true;}
      else if(AFgRQWolFt == KAYiRBTfRR){VomKHlYdSF = true;}
      if(cqrPlDHwSr == WFESzHVgDh){fTpSTgwPri = true;}
      else if(WFESzHVgDh == cqrPlDHwSr){kYDVeWWzuM = true;}
      if(IiJkOfQpHw == oasZleboCJ){kSxryVWPIs = true;}
      else if(oasZleboCJ == IiJkOfQpHw){IJZUNrxYml = true;}
      if(zIdFIVFAWa == yueAAgwoau){nIogOIUjwd = true;}
      else if(yueAAgwoau == zIdFIVFAWa){nMkbchqihI = true;}
      if(GqeYCNsmhO == trgzJYNMlh){grXKtzyqVS = true;}
      else if(trgzJYNMlh == GqeYCNsmhO){WkBdxYQsPD = true;}
      if(dPdqLbpmTl == GkFWsZMGfk){yrrUxeLBUB = true;}
      else if(GkFWsZMGfk == dPdqLbpmTl){sEloNLOSwO = true;}
      if(jdYVSTNmGQ == uAjuuaaESR){CQopIXdJDK = true;}
      else if(uAjuuaaESR == jdYVSTNmGQ){ozpgQYmarx = true;}
      if(xHZrlQEkiA == KgFInwssPM){LMTOCrtmyy = true;}
      if(mcHrRjdltg == RODTDMpHGZ){WetotuPUii = true;}
      if(eSfkpcSIFh == ToJoztIkDi){xTOtaPDhCV = true;}
      while(KgFInwssPM == xHZrlQEkiA){emRloWHwWo = true;}
      while(RODTDMpHGZ == RODTDMpHGZ){bDJirjZuOR = true;}
      while(ToJoztIkDi == ToJoztIkDi){SYmSTWtUNY = true;}
      if(yItTWYfxiw == true){yItTWYfxiw = false;}
      if(fTpSTgwPri == true){fTpSTgwPri = false;}
      if(kSxryVWPIs == true){kSxryVWPIs = false;}
      if(nIogOIUjwd == true){nIogOIUjwd = false;}
      if(grXKtzyqVS == true){grXKtzyqVS = false;}
      if(yrrUxeLBUB == true){yrrUxeLBUB = false;}
      if(CQopIXdJDK == true){CQopIXdJDK = false;}
      if(LMTOCrtmyy == true){LMTOCrtmyy = false;}
      if(WetotuPUii == true){WetotuPUii = false;}
      if(xTOtaPDhCV == true){xTOtaPDhCV = false;}
      if(VomKHlYdSF == true){VomKHlYdSF = false;}
      if(kYDVeWWzuM == true){kYDVeWWzuM = false;}
      if(IJZUNrxYml == true){IJZUNrxYml = false;}
      if(nMkbchqihI == true){nMkbchqihI = false;}
      if(WkBdxYQsPD == true){WkBdxYQsPD = false;}
      if(sEloNLOSwO == true){sEloNLOSwO = false;}
      if(ozpgQYmarx == true){ozpgQYmarx = false;}
      if(emRloWHwWo == true){emRloWHwWo = false;}
      if(bDJirjZuOR == true){bDJirjZuOR = false;}
      if(SYmSTWtUNY == true){SYmSTWtUNY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SFOSEAKZDM
{ 
  void DWqsArzrEg()
  { 
      bool zbzzWoTpaK = false;
      bool lHnlRMQUZd = false;
      bool gOnUfjVZHu = false;
      bool pQKhFxYcKp = false;
      bool PdTVahRStR = false;
      bool AirwukmeTm = false;
      bool SshfUVwFgT = false;
      bool mmKiOCtRsx = false;
      bool RDfptGXOmU = false;
      bool JtIWWVunBF = false;
      bool kMkZeNYJgr = false;
      bool pUkVVPNrkN = false;
      bool xgSMKsdmLr = false;
      bool HGQnMFRGLg = false;
      bool hOhudnImBH = false;
      bool ICCmHDtYPk = false;
      bool ikxnkjEwJP = false;
      bool xGgEfhzWhV = false;
      bool kqlEjEDcgJ = false;
      bool LrpZywRsJt = false;
      string rMyspftMVn;
      string IirRBajBtu;
      string lRaBQjtVFK;
      string PDFbBlBcer;
      string MCphKFhCTn;
      string ANzilZkxcF;
      string kYGLXFcPPO;
      string ZHWBijbrqL;
      string BqBRJBEWpb;
      string BDzYHmueJF;
      string bSmENsqxAC;
      string yrGREtWoCW;
      string AGZnNWHxtu;
      string nwhkiiEwDP;
      string KGWndIxhUM;
      string PFbmEVsyqq;
      string lsCENBJUhU;
      string oallMtikKE;
      string ZYcheiUugN;
      string oFELdQERZb;
      if(rMyspftMVn == bSmENsqxAC){zbzzWoTpaK = true;}
      else if(bSmENsqxAC == rMyspftMVn){kMkZeNYJgr = true;}
      if(IirRBajBtu == yrGREtWoCW){lHnlRMQUZd = true;}
      else if(yrGREtWoCW == IirRBajBtu){pUkVVPNrkN = true;}
      if(lRaBQjtVFK == AGZnNWHxtu){gOnUfjVZHu = true;}
      else if(AGZnNWHxtu == lRaBQjtVFK){xgSMKsdmLr = true;}
      if(PDFbBlBcer == nwhkiiEwDP){pQKhFxYcKp = true;}
      else if(nwhkiiEwDP == PDFbBlBcer){HGQnMFRGLg = true;}
      if(MCphKFhCTn == KGWndIxhUM){PdTVahRStR = true;}
      else if(KGWndIxhUM == MCphKFhCTn){hOhudnImBH = true;}
      if(ANzilZkxcF == PFbmEVsyqq){AirwukmeTm = true;}
      else if(PFbmEVsyqq == ANzilZkxcF){ICCmHDtYPk = true;}
      if(kYGLXFcPPO == lsCENBJUhU){SshfUVwFgT = true;}
      else if(lsCENBJUhU == kYGLXFcPPO){ikxnkjEwJP = true;}
      if(ZHWBijbrqL == oallMtikKE){mmKiOCtRsx = true;}
      if(BqBRJBEWpb == ZYcheiUugN){RDfptGXOmU = true;}
      if(BDzYHmueJF == oFELdQERZb){JtIWWVunBF = true;}
      while(oallMtikKE == ZHWBijbrqL){xGgEfhzWhV = true;}
      while(ZYcheiUugN == ZYcheiUugN){kqlEjEDcgJ = true;}
      while(oFELdQERZb == oFELdQERZb){LrpZywRsJt = true;}
      if(zbzzWoTpaK == true){zbzzWoTpaK = false;}
      if(lHnlRMQUZd == true){lHnlRMQUZd = false;}
      if(gOnUfjVZHu == true){gOnUfjVZHu = false;}
      if(pQKhFxYcKp == true){pQKhFxYcKp = false;}
      if(PdTVahRStR == true){PdTVahRStR = false;}
      if(AirwukmeTm == true){AirwukmeTm = false;}
      if(SshfUVwFgT == true){SshfUVwFgT = false;}
      if(mmKiOCtRsx == true){mmKiOCtRsx = false;}
      if(RDfptGXOmU == true){RDfptGXOmU = false;}
      if(JtIWWVunBF == true){JtIWWVunBF = false;}
      if(kMkZeNYJgr == true){kMkZeNYJgr = false;}
      if(pUkVVPNrkN == true){pUkVVPNrkN = false;}
      if(xgSMKsdmLr == true){xgSMKsdmLr = false;}
      if(HGQnMFRGLg == true){HGQnMFRGLg = false;}
      if(hOhudnImBH == true){hOhudnImBH = false;}
      if(ICCmHDtYPk == true){ICCmHDtYPk = false;}
      if(ikxnkjEwJP == true){ikxnkjEwJP = false;}
      if(xGgEfhzWhV == true){xGgEfhzWhV = false;}
      if(kqlEjEDcgJ == true){kqlEjEDcgJ = false;}
      if(LrpZywRsJt == true){LrpZywRsJt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UKPJILXIGV
{ 
  void CRhLHWeBVP()
  { 
      bool BuCdtkFyDB = false;
      bool URacRdHmIT = false;
      bool txYJnJHkde = false;
      bool QEPFtARuiR = false;
      bool MqdNODbsnX = false;
      bool xAUlQDWspj = false;
      bool dTTYjPCVhR = false;
      bool MMEpGCTLtk = false;
      bool gOwGgQicnp = false;
      bool cYFynrXEcz = false;
      bool BGKWKkueeN = false;
      bool jKyFDOXMqS = false;
      bool gYgqnnHFBO = false;
      bool eOhtiaEZuu = false;
      bool VEyZGRZzuZ = false;
      bool UKMJRcYShW = false;
      bool docPiUbDVb = false;
      bool JyQwxbZGkV = false;
      bool OHKbtTBYcG = false;
      bool BkqYRfbhql = false;
      string VSNOfXUzGj;
      string fyUzSJDlaL;
      string CknTZJPCbN;
      string jNGPlKlOYX;
      string FfEJhPDQIP;
      string BGFlXkdtoV;
      string HRXszRqENI;
      string WnNCGWfdkK;
      string GztMMdHUrA;
      string frZCQmILJP;
      string YzDArMrDeA;
      string FzIePIXLfV;
      string JWMMbeOLlT;
      string OUUUkHutTz;
      string lEoqufiulH;
      string PwemGBlqXN;
      string xfRLljemsI;
      string NdqfjEgUQu;
      string uTYdDRpgOj;
      string UDVGBFmcFL;
      if(VSNOfXUzGj == YzDArMrDeA){BuCdtkFyDB = true;}
      else if(YzDArMrDeA == VSNOfXUzGj){BGKWKkueeN = true;}
      if(fyUzSJDlaL == FzIePIXLfV){URacRdHmIT = true;}
      else if(FzIePIXLfV == fyUzSJDlaL){jKyFDOXMqS = true;}
      if(CknTZJPCbN == JWMMbeOLlT){txYJnJHkde = true;}
      else if(JWMMbeOLlT == CknTZJPCbN){gYgqnnHFBO = true;}
      if(jNGPlKlOYX == OUUUkHutTz){QEPFtARuiR = true;}
      else if(OUUUkHutTz == jNGPlKlOYX){eOhtiaEZuu = true;}
      if(FfEJhPDQIP == lEoqufiulH){MqdNODbsnX = true;}
      else if(lEoqufiulH == FfEJhPDQIP){VEyZGRZzuZ = true;}
      if(BGFlXkdtoV == PwemGBlqXN){xAUlQDWspj = true;}
      else if(PwemGBlqXN == BGFlXkdtoV){UKMJRcYShW = true;}
      if(HRXszRqENI == xfRLljemsI){dTTYjPCVhR = true;}
      else if(xfRLljemsI == HRXszRqENI){docPiUbDVb = true;}
      if(WnNCGWfdkK == NdqfjEgUQu){MMEpGCTLtk = true;}
      if(GztMMdHUrA == uTYdDRpgOj){gOwGgQicnp = true;}
      if(frZCQmILJP == UDVGBFmcFL){cYFynrXEcz = true;}
      while(NdqfjEgUQu == WnNCGWfdkK){JyQwxbZGkV = true;}
      while(uTYdDRpgOj == uTYdDRpgOj){OHKbtTBYcG = true;}
      while(UDVGBFmcFL == UDVGBFmcFL){BkqYRfbhql = true;}
      if(BuCdtkFyDB == true){BuCdtkFyDB = false;}
      if(URacRdHmIT == true){URacRdHmIT = false;}
      if(txYJnJHkde == true){txYJnJHkde = false;}
      if(QEPFtARuiR == true){QEPFtARuiR = false;}
      if(MqdNODbsnX == true){MqdNODbsnX = false;}
      if(xAUlQDWspj == true){xAUlQDWspj = false;}
      if(dTTYjPCVhR == true){dTTYjPCVhR = false;}
      if(MMEpGCTLtk == true){MMEpGCTLtk = false;}
      if(gOwGgQicnp == true){gOwGgQicnp = false;}
      if(cYFynrXEcz == true){cYFynrXEcz = false;}
      if(BGKWKkueeN == true){BGKWKkueeN = false;}
      if(jKyFDOXMqS == true){jKyFDOXMqS = false;}
      if(gYgqnnHFBO == true){gYgqnnHFBO = false;}
      if(eOhtiaEZuu == true){eOhtiaEZuu = false;}
      if(VEyZGRZzuZ == true){VEyZGRZzuZ = false;}
      if(UKMJRcYShW == true){UKMJRcYShW = false;}
      if(docPiUbDVb == true){docPiUbDVb = false;}
      if(JyQwxbZGkV == true){JyQwxbZGkV = false;}
      if(OHKbtTBYcG == true){OHKbtTBYcG = false;}
      if(BkqYRfbhql == true){BkqYRfbhql = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGZNKKYLLE
{ 
  void SMOWfKuWAp()
  { 
      bool muZqhfpNHc = false;
      bool rudiywjRNf = false;
      bool SUbmHQodZc = false;
      bool AgHgNfpptY = false;
      bool cjdajApSGZ = false;
      bool zYHyqSTmjR = false;
      bool pMndcKmwVS = false;
      bool GsXoChpBDH = false;
      bool ZWWzdbZJpt = false;
      bool MCGciQuzyY = false;
      bool MsxnTFASuI = false;
      bool bRjbqSooAB = false;
      bool kdGaFDmuFk = false;
      bool lpDdufYieX = false;
      bool aGNgStSekP = false;
      bool bGyxnhmWhP = false;
      bool SFMKWkOFfK = false;
      bool tFJcZdPZIL = false;
      bool jHJpJfrGpM = false;
      bool sCBOFUtDKg = false;
      string wutJRAkuiW;
      string LcbwKnButU;
      string pWrVQIqsWB;
      string GHEqaJEUmD;
      string sKXBAJgKdN;
      string zFgWWYDYsJ;
      string IrXhQDYjUA;
      string igIpbezqUH;
      string afOJBAahUB;
      string GfaduAmpjw;
      string kxoddSxptq;
      string ZMDlhbcOfP;
      string bpPTtDFdub;
      string rIGXWdpkei;
      string DkncbsbouS;
      string WYKUTthViZ;
      string MStSzQGfOD;
      string kqiwMqClrA;
      string bPhbETylDb;
      string wUBFWjqUdK;
      if(wutJRAkuiW == kxoddSxptq){muZqhfpNHc = true;}
      else if(kxoddSxptq == wutJRAkuiW){MsxnTFASuI = true;}
      if(LcbwKnButU == ZMDlhbcOfP){rudiywjRNf = true;}
      else if(ZMDlhbcOfP == LcbwKnButU){bRjbqSooAB = true;}
      if(pWrVQIqsWB == bpPTtDFdub){SUbmHQodZc = true;}
      else if(bpPTtDFdub == pWrVQIqsWB){kdGaFDmuFk = true;}
      if(GHEqaJEUmD == rIGXWdpkei){AgHgNfpptY = true;}
      else if(rIGXWdpkei == GHEqaJEUmD){lpDdufYieX = true;}
      if(sKXBAJgKdN == DkncbsbouS){cjdajApSGZ = true;}
      else if(DkncbsbouS == sKXBAJgKdN){aGNgStSekP = true;}
      if(zFgWWYDYsJ == WYKUTthViZ){zYHyqSTmjR = true;}
      else if(WYKUTthViZ == zFgWWYDYsJ){bGyxnhmWhP = true;}
      if(IrXhQDYjUA == MStSzQGfOD){pMndcKmwVS = true;}
      else if(MStSzQGfOD == IrXhQDYjUA){SFMKWkOFfK = true;}
      if(igIpbezqUH == kqiwMqClrA){GsXoChpBDH = true;}
      if(afOJBAahUB == bPhbETylDb){ZWWzdbZJpt = true;}
      if(GfaduAmpjw == wUBFWjqUdK){MCGciQuzyY = true;}
      while(kqiwMqClrA == igIpbezqUH){tFJcZdPZIL = true;}
      while(bPhbETylDb == bPhbETylDb){jHJpJfrGpM = true;}
      while(wUBFWjqUdK == wUBFWjqUdK){sCBOFUtDKg = true;}
      if(muZqhfpNHc == true){muZqhfpNHc = false;}
      if(rudiywjRNf == true){rudiywjRNf = false;}
      if(SUbmHQodZc == true){SUbmHQodZc = false;}
      if(AgHgNfpptY == true){AgHgNfpptY = false;}
      if(cjdajApSGZ == true){cjdajApSGZ = false;}
      if(zYHyqSTmjR == true){zYHyqSTmjR = false;}
      if(pMndcKmwVS == true){pMndcKmwVS = false;}
      if(GsXoChpBDH == true){GsXoChpBDH = false;}
      if(ZWWzdbZJpt == true){ZWWzdbZJpt = false;}
      if(MCGciQuzyY == true){MCGciQuzyY = false;}
      if(MsxnTFASuI == true){MsxnTFASuI = false;}
      if(bRjbqSooAB == true){bRjbqSooAB = false;}
      if(kdGaFDmuFk == true){kdGaFDmuFk = false;}
      if(lpDdufYieX == true){lpDdufYieX = false;}
      if(aGNgStSekP == true){aGNgStSekP = false;}
      if(bGyxnhmWhP == true){bGyxnhmWhP = false;}
      if(SFMKWkOFfK == true){SFMKWkOFfK = false;}
      if(tFJcZdPZIL == true){tFJcZdPZIL = false;}
      if(jHJpJfrGpM == true){jHJpJfrGpM = false;}
      if(sCBOFUtDKg == true){sCBOFUtDKg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ARXKGHGXMB
{ 
  void kuWZGlpMIu()
  { 
      bool oamfITuAWF = false;
      bool NkIJizXkOt = false;
      bool JqzCXHWjkp = false;
      bool eLCHPYaKax = false;
      bool pEgezxrnPg = false;
      bool HgXTGyajIB = false;
      bool wKPgaBhAsJ = false;
      bool XNJRDFKUDZ = false;
      bool OhUEixniBR = false;
      bool xqBZBenAEx = false;
      bool OruFJsXGPA = false;
      bool mGgimNpLxc = false;
      bool NyyaLfMjQX = false;
      bool QJPFKWmOuo = false;
      bool ZhTBeqKRlm = false;
      bool ocCajPsTtc = false;
      bool gmpqidpaXQ = false;
      bool aaQICfexwU = false;
      bool VtxdimGnVt = false;
      bool cTURIlqbRA = false;
      string uUFFofEIsj;
      string msxTGaxPeD;
      string yKSHJFVAPK;
      string hsUxAhgnKT;
      string amKLhEKDfn;
      string mwhOHjBxui;
      string KDrhCtXzSX;
      string tJELcLzHZF;
      string tSUbXlKFpP;
      string firbJWucJm;
      string fKjHtdqWlw;
      string ktXpoqiQKP;
      string jSJCrLQcBF;
      string QWymZiiNgs;
      string tmTselKClR;
      string ndRsCMBgPi;
      string NOUffOwjPF;
      string IUiQVxzPXF;
      string ANpjQlEEjM;
      string hByyfeRmNP;
      if(uUFFofEIsj == fKjHtdqWlw){oamfITuAWF = true;}
      else if(fKjHtdqWlw == uUFFofEIsj){OruFJsXGPA = true;}
      if(msxTGaxPeD == ktXpoqiQKP){NkIJizXkOt = true;}
      else if(ktXpoqiQKP == msxTGaxPeD){mGgimNpLxc = true;}
      if(yKSHJFVAPK == jSJCrLQcBF){JqzCXHWjkp = true;}
      else if(jSJCrLQcBF == yKSHJFVAPK){NyyaLfMjQX = true;}
      if(hsUxAhgnKT == QWymZiiNgs){eLCHPYaKax = true;}
      else if(QWymZiiNgs == hsUxAhgnKT){QJPFKWmOuo = true;}
      if(amKLhEKDfn == tmTselKClR){pEgezxrnPg = true;}
      else if(tmTselKClR == amKLhEKDfn){ZhTBeqKRlm = true;}
      if(mwhOHjBxui == ndRsCMBgPi){HgXTGyajIB = true;}
      else if(ndRsCMBgPi == mwhOHjBxui){ocCajPsTtc = true;}
      if(KDrhCtXzSX == NOUffOwjPF){wKPgaBhAsJ = true;}
      else if(NOUffOwjPF == KDrhCtXzSX){gmpqidpaXQ = true;}
      if(tJELcLzHZF == IUiQVxzPXF){XNJRDFKUDZ = true;}
      if(tSUbXlKFpP == ANpjQlEEjM){OhUEixniBR = true;}
      if(firbJWucJm == hByyfeRmNP){xqBZBenAEx = true;}
      while(IUiQVxzPXF == tJELcLzHZF){aaQICfexwU = true;}
      while(ANpjQlEEjM == ANpjQlEEjM){VtxdimGnVt = true;}
      while(hByyfeRmNP == hByyfeRmNP){cTURIlqbRA = true;}
      if(oamfITuAWF == true){oamfITuAWF = false;}
      if(NkIJizXkOt == true){NkIJizXkOt = false;}
      if(JqzCXHWjkp == true){JqzCXHWjkp = false;}
      if(eLCHPYaKax == true){eLCHPYaKax = false;}
      if(pEgezxrnPg == true){pEgezxrnPg = false;}
      if(HgXTGyajIB == true){HgXTGyajIB = false;}
      if(wKPgaBhAsJ == true){wKPgaBhAsJ = false;}
      if(XNJRDFKUDZ == true){XNJRDFKUDZ = false;}
      if(OhUEixniBR == true){OhUEixniBR = false;}
      if(xqBZBenAEx == true){xqBZBenAEx = false;}
      if(OruFJsXGPA == true){OruFJsXGPA = false;}
      if(mGgimNpLxc == true){mGgimNpLxc = false;}
      if(NyyaLfMjQX == true){NyyaLfMjQX = false;}
      if(QJPFKWmOuo == true){QJPFKWmOuo = false;}
      if(ZhTBeqKRlm == true){ZhTBeqKRlm = false;}
      if(ocCajPsTtc == true){ocCajPsTtc = false;}
      if(gmpqidpaXQ == true){gmpqidpaXQ = false;}
      if(aaQICfexwU == true){aaQICfexwU = false;}
      if(VtxdimGnVt == true){VtxdimGnVt = false;}
      if(cTURIlqbRA == true){cTURIlqbRA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NSZCFMYFYM
{ 
  void zNGuyNfwhA()
  { 
      bool iXyPucUczU = false;
      bool ARYhpZwEan = false;
      bool KPEHfVKjUg = false;
      bool ttzwLNeJwj = false;
      bool HBIRmdOGbi = false;
      bool gJenQSTpjZ = false;
      bool RkHSZFScWc = false;
      bool tlIqfJHlUB = false;
      bool GEHkAkOKer = false;
      bool toZWSWspqg = false;
      bool LljzouAnIH = false;
      bool LgVhSNcVRo = false;
      bool qHxehFMlXJ = false;
      bool PQunoUTIwE = false;
      bool jaCWfMSqDE = false;
      bool sWXBpEnFQj = false;
      bool iOPyrukhsy = false;
      bool sTZNFQEZyU = false;
      bool lUhSQrrsxk = false;
      bool fOrMVVKEek = false;
      string RpEcXLuyrB;
      string YWbfjQxLVB;
      string KJIjHAqebN;
      string DzxwzhrxhV;
      string NpaSWVtSgD;
      string ZQtUkIgUUX;
      string TQVdxYYffC;
      string YzcznThoNk;
      string FXxYmmFcKq;
      string AWbKBwTxVx;
      string xOledamtgQ;
      string ZrHiSwSwpK;
      string TwUoCBWRxq;
      string AkTPnpkRtM;
      string zKusQHPsrF;
      string dWGKcAsxcc;
      string DVwoQoYqub;
      string KABdKIAbXt;
      string ldZqNcdIlm;
      string wnoRIdOGbb;
      if(RpEcXLuyrB == xOledamtgQ){iXyPucUczU = true;}
      else if(xOledamtgQ == RpEcXLuyrB){LljzouAnIH = true;}
      if(YWbfjQxLVB == ZrHiSwSwpK){ARYhpZwEan = true;}
      else if(ZrHiSwSwpK == YWbfjQxLVB){LgVhSNcVRo = true;}
      if(KJIjHAqebN == TwUoCBWRxq){KPEHfVKjUg = true;}
      else if(TwUoCBWRxq == KJIjHAqebN){qHxehFMlXJ = true;}
      if(DzxwzhrxhV == AkTPnpkRtM){ttzwLNeJwj = true;}
      else if(AkTPnpkRtM == DzxwzhrxhV){PQunoUTIwE = true;}
      if(NpaSWVtSgD == zKusQHPsrF){HBIRmdOGbi = true;}
      else if(zKusQHPsrF == NpaSWVtSgD){jaCWfMSqDE = true;}
      if(ZQtUkIgUUX == dWGKcAsxcc){gJenQSTpjZ = true;}
      else if(dWGKcAsxcc == ZQtUkIgUUX){sWXBpEnFQj = true;}
      if(TQVdxYYffC == DVwoQoYqub){RkHSZFScWc = true;}
      else if(DVwoQoYqub == TQVdxYYffC){iOPyrukhsy = true;}
      if(YzcznThoNk == KABdKIAbXt){tlIqfJHlUB = true;}
      if(FXxYmmFcKq == ldZqNcdIlm){GEHkAkOKer = true;}
      if(AWbKBwTxVx == wnoRIdOGbb){toZWSWspqg = true;}
      while(KABdKIAbXt == YzcznThoNk){sTZNFQEZyU = true;}
      while(ldZqNcdIlm == ldZqNcdIlm){lUhSQrrsxk = true;}
      while(wnoRIdOGbb == wnoRIdOGbb){fOrMVVKEek = true;}
      if(iXyPucUczU == true){iXyPucUczU = false;}
      if(ARYhpZwEan == true){ARYhpZwEan = false;}
      if(KPEHfVKjUg == true){KPEHfVKjUg = false;}
      if(ttzwLNeJwj == true){ttzwLNeJwj = false;}
      if(HBIRmdOGbi == true){HBIRmdOGbi = false;}
      if(gJenQSTpjZ == true){gJenQSTpjZ = false;}
      if(RkHSZFScWc == true){RkHSZFScWc = false;}
      if(tlIqfJHlUB == true){tlIqfJHlUB = false;}
      if(GEHkAkOKer == true){GEHkAkOKer = false;}
      if(toZWSWspqg == true){toZWSWspqg = false;}
      if(LljzouAnIH == true){LljzouAnIH = false;}
      if(LgVhSNcVRo == true){LgVhSNcVRo = false;}
      if(qHxehFMlXJ == true){qHxehFMlXJ = false;}
      if(PQunoUTIwE == true){PQunoUTIwE = false;}
      if(jaCWfMSqDE == true){jaCWfMSqDE = false;}
      if(sWXBpEnFQj == true){sWXBpEnFQj = false;}
      if(iOPyrukhsy == true){iOPyrukhsy = false;}
      if(sTZNFQEZyU == true){sTZNFQEZyU = false;}
      if(lUhSQrrsxk == true){lUhSQrrsxk = false;}
      if(fOrMVVKEek == true){fOrMVVKEek = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GOSCHXNJQQ
{ 
  void MztdTBWoUF()
  { 
      bool iLPZIEpKfD = false;
      bool abkdcSPNXf = false;
      bool RDNMdUclwV = false;
      bool nqoaBQSUTm = false;
      bool SklDNrrawb = false;
      bool YWjaeeyDum = false;
      bool bDOKOilKcL = false;
      bool zttjMgRKzl = false;
      bool cBpUxQGOuV = false;
      bool SPYfLOVand = false;
      bool FgyjbdcANy = false;
      bool NmDJKZMtNx = false;
      bool bWPGsjVNXx = false;
      bool KpVUfuDFrT = false;
      bool nGBxIeLPUl = false;
      bool CbNpChRqqr = false;
      bool HPbPnWRidP = false;
      bool WGBtJVVRxN = false;
      bool XGrluhceRx = false;
      bool cLOALYekIk = false;
      string KbDbGuUgUP;
      string CZjZtlpomg;
      string hMooAIdwwi;
      string gCiyUVwIKK;
      string MdahcnByaD;
      string jGBPExlNbx;
      string RXjliAqlFX;
      string phebTElHLL;
      string HfVsyZATtW;
      string ihgMsosnyc;
      string xPrCNCbYuz;
      string LeCPplBqmI;
      string AXqinHARie;
      string KxIiOrmTew;
      string yaXuKEeRWG;
      string mCBpbZXJNF;
      string BJpPnNVTBx;
      string yhLpJYzwXj;
      string citbrIwSGn;
      string TdFYtnkHGx;
      if(KbDbGuUgUP == xPrCNCbYuz){iLPZIEpKfD = true;}
      else if(xPrCNCbYuz == KbDbGuUgUP){FgyjbdcANy = true;}
      if(CZjZtlpomg == LeCPplBqmI){abkdcSPNXf = true;}
      else if(LeCPplBqmI == CZjZtlpomg){NmDJKZMtNx = true;}
      if(hMooAIdwwi == AXqinHARie){RDNMdUclwV = true;}
      else if(AXqinHARie == hMooAIdwwi){bWPGsjVNXx = true;}
      if(gCiyUVwIKK == KxIiOrmTew){nqoaBQSUTm = true;}
      else if(KxIiOrmTew == gCiyUVwIKK){KpVUfuDFrT = true;}
      if(MdahcnByaD == yaXuKEeRWG){SklDNrrawb = true;}
      else if(yaXuKEeRWG == MdahcnByaD){nGBxIeLPUl = true;}
      if(jGBPExlNbx == mCBpbZXJNF){YWjaeeyDum = true;}
      else if(mCBpbZXJNF == jGBPExlNbx){CbNpChRqqr = true;}
      if(RXjliAqlFX == BJpPnNVTBx){bDOKOilKcL = true;}
      else if(BJpPnNVTBx == RXjliAqlFX){HPbPnWRidP = true;}
      if(phebTElHLL == yhLpJYzwXj){zttjMgRKzl = true;}
      if(HfVsyZATtW == citbrIwSGn){cBpUxQGOuV = true;}
      if(ihgMsosnyc == TdFYtnkHGx){SPYfLOVand = true;}
      while(yhLpJYzwXj == phebTElHLL){WGBtJVVRxN = true;}
      while(citbrIwSGn == citbrIwSGn){XGrluhceRx = true;}
      while(TdFYtnkHGx == TdFYtnkHGx){cLOALYekIk = true;}
      if(iLPZIEpKfD == true){iLPZIEpKfD = false;}
      if(abkdcSPNXf == true){abkdcSPNXf = false;}
      if(RDNMdUclwV == true){RDNMdUclwV = false;}
      if(nqoaBQSUTm == true){nqoaBQSUTm = false;}
      if(SklDNrrawb == true){SklDNrrawb = false;}
      if(YWjaeeyDum == true){YWjaeeyDum = false;}
      if(bDOKOilKcL == true){bDOKOilKcL = false;}
      if(zttjMgRKzl == true){zttjMgRKzl = false;}
      if(cBpUxQGOuV == true){cBpUxQGOuV = false;}
      if(SPYfLOVand == true){SPYfLOVand = false;}
      if(FgyjbdcANy == true){FgyjbdcANy = false;}
      if(NmDJKZMtNx == true){NmDJKZMtNx = false;}
      if(bWPGsjVNXx == true){bWPGsjVNXx = false;}
      if(KpVUfuDFrT == true){KpVUfuDFrT = false;}
      if(nGBxIeLPUl == true){nGBxIeLPUl = false;}
      if(CbNpChRqqr == true){CbNpChRqqr = false;}
      if(HPbPnWRidP == true){HPbPnWRidP = false;}
      if(WGBtJVVRxN == true){WGBtJVVRxN = false;}
      if(XGrluhceRx == true){XGrluhceRx = false;}
      if(cLOALYekIk == true){cLOALYekIk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UEKAISEYBV
{ 
  void KgdIFTEsET()
  { 
      bool XwjWfUhfAl = false;
      bool aPsiilfWLb = false;
      bool nrUgNTcwOh = false;
      bool XxsFtZzeeW = false;
      bool DNuubZjnoV = false;
      bool YDUAgfaCIM = false;
      bool qlQROcWnoI = false;
      bool lAqnXaxZEn = false;
      bool ioHsIUbrXO = false;
      bool yxWSfRwdgz = false;
      bool CuzfiYLgbF = false;
      bool hBxTcCdXIs = false;
      bool BdQZKodYIF = false;
      bool eTsFlmobJj = false;
      bool IuPRfxADoc = false;
      bool nXUmxYeYVt = false;
      bool tmXWaOIqho = false;
      bool MCOXkGNytN = false;
      bool naieRHyFIM = false;
      bool HQFOpVWsqQ = false;
      string uAPsXIiZCE;
      string KCthXkGhlj;
      string wMemUXNDVx;
      string iWhnSGwmDU;
      string ZFKhdpBOyQ;
      string snocthUcYz;
      string teDFUnUFPR;
      string oSeQJqCwIe;
      string VyFFEugEsj;
      string kTODauBENp;
      string VwzgaZIYSD;
      string fXTtcwYyBZ;
      string GPLefVEbpO;
      string oxiRIZyYdd;
      string lIkpEMzUZd;
      string VDDmjFkUBF;
      string VghENhoCkD;
      string xAUWmyeUaS;
      string WiBLrlswgD;
      string odWXHEZgbV;
      if(uAPsXIiZCE == VwzgaZIYSD){XwjWfUhfAl = true;}
      else if(VwzgaZIYSD == uAPsXIiZCE){CuzfiYLgbF = true;}
      if(KCthXkGhlj == fXTtcwYyBZ){aPsiilfWLb = true;}
      else if(fXTtcwYyBZ == KCthXkGhlj){hBxTcCdXIs = true;}
      if(wMemUXNDVx == GPLefVEbpO){nrUgNTcwOh = true;}
      else if(GPLefVEbpO == wMemUXNDVx){BdQZKodYIF = true;}
      if(iWhnSGwmDU == oxiRIZyYdd){XxsFtZzeeW = true;}
      else if(oxiRIZyYdd == iWhnSGwmDU){eTsFlmobJj = true;}
      if(ZFKhdpBOyQ == lIkpEMzUZd){DNuubZjnoV = true;}
      else if(lIkpEMzUZd == ZFKhdpBOyQ){IuPRfxADoc = true;}
      if(snocthUcYz == VDDmjFkUBF){YDUAgfaCIM = true;}
      else if(VDDmjFkUBF == snocthUcYz){nXUmxYeYVt = true;}
      if(teDFUnUFPR == VghENhoCkD){qlQROcWnoI = true;}
      else if(VghENhoCkD == teDFUnUFPR){tmXWaOIqho = true;}
      if(oSeQJqCwIe == xAUWmyeUaS){lAqnXaxZEn = true;}
      if(VyFFEugEsj == WiBLrlswgD){ioHsIUbrXO = true;}
      if(kTODauBENp == odWXHEZgbV){yxWSfRwdgz = true;}
      while(xAUWmyeUaS == oSeQJqCwIe){MCOXkGNytN = true;}
      while(WiBLrlswgD == WiBLrlswgD){naieRHyFIM = true;}
      while(odWXHEZgbV == odWXHEZgbV){HQFOpVWsqQ = true;}
      if(XwjWfUhfAl == true){XwjWfUhfAl = false;}
      if(aPsiilfWLb == true){aPsiilfWLb = false;}
      if(nrUgNTcwOh == true){nrUgNTcwOh = false;}
      if(XxsFtZzeeW == true){XxsFtZzeeW = false;}
      if(DNuubZjnoV == true){DNuubZjnoV = false;}
      if(YDUAgfaCIM == true){YDUAgfaCIM = false;}
      if(qlQROcWnoI == true){qlQROcWnoI = false;}
      if(lAqnXaxZEn == true){lAqnXaxZEn = false;}
      if(ioHsIUbrXO == true){ioHsIUbrXO = false;}
      if(yxWSfRwdgz == true){yxWSfRwdgz = false;}
      if(CuzfiYLgbF == true){CuzfiYLgbF = false;}
      if(hBxTcCdXIs == true){hBxTcCdXIs = false;}
      if(BdQZKodYIF == true){BdQZKodYIF = false;}
      if(eTsFlmobJj == true){eTsFlmobJj = false;}
      if(IuPRfxADoc == true){IuPRfxADoc = false;}
      if(nXUmxYeYVt == true){nXUmxYeYVt = false;}
      if(tmXWaOIqho == true){tmXWaOIqho = false;}
      if(MCOXkGNytN == true){MCOXkGNytN = false;}
      if(naieRHyFIM == true){naieRHyFIM = false;}
      if(HQFOpVWsqQ == true){HQFOpVWsqQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XWXHDOFXDH
{ 
  void htxCwfbAZn()
  { 
      bool SqwmUGNRXV = false;
      bool aPwpfJkyDn = false;
      bool KRrPTxuAOJ = false;
      bool mkeSjlCyix = false;
      bool sHfAAwTafV = false;
      bool CftLyAzfTW = false;
      bool KNDOhojdFt = false;
      bool HmPFuDkqOW = false;
      bool dUTrGHpTTj = false;
      bool lVeLmfDRRK = false;
      bool LpUlOOQoPu = false;
      bool PHQwsosKHa = false;
      bool zQJVHkIDSO = false;
      bool zSYEKmzhdr = false;
      bool qBDYTeEhSx = false;
      bool mrJqLufzec = false;
      bool GMVBuwiMlF = false;
      bool pKgPjxMkBc = false;
      bool fajVbGIhrP = false;
      bool HADBkdfCdX = false;
      string zGpJWAcZyH;
      string JqwDFabjxW;
      string ywMNyEOJbe;
      string SlWtSdJZYY;
      string JHOOMQYeNL;
      string wjOpUDsbKS;
      string lTySnXUBkb;
      string RBKYMphyAh;
      string eiwPiiWgZO;
      string jgPGlpIwZo;
      string wWtkttZocd;
      string VuacnDWhiF;
      string AmbVrjlDmW;
      string hkYLkHoKVo;
      string JhEwsoGmSi;
      string SZMTnJuYsJ;
      string IVCGwjVOqf;
      string OMMtwSiebD;
      string dykDDHYEWb;
      string MQQMfmexAJ;
      if(zGpJWAcZyH == wWtkttZocd){SqwmUGNRXV = true;}
      else if(wWtkttZocd == zGpJWAcZyH){LpUlOOQoPu = true;}
      if(JqwDFabjxW == VuacnDWhiF){aPwpfJkyDn = true;}
      else if(VuacnDWhiF == JqwDFabjxW){PHQwsosKHa = true;}
      if(ywMNyEOJbe == AmbVrjlDmW){KRrPTxuAOJ = true;}
      else if(AmbVrjlDmW == ywMNyEOJbe){zQJVHkIDSO = true;}
      if(SlWtSdJZYY == hkYLkHoKVo){mkeSjlCyix = true;}
      else if(hkYLkHoKVo == SlWtSdJZYY){zSYEKmzhdr = true;}
      if(JHOOMQYeNL == JhEwsoGmSi){sHfAAwTafV = true;}
      else if(JhEwsoGmSi == JHOOMQYeNL){qBDYTeEhSx = true;}
      if(wjOpUDsbKS == SZMTnJuYsJ){CftLyAzfTW = true;}
      else if(SZMTnJuYsJ == wjOpUDsbKS){mrJqLufzec = true;}
      if(lTySnXUBkb == IVCGwjVOqf){KNDOhojdFt = true;}
      else if(IVCGwjVOqf == lTySnXUBkb){GMVBuwiMlF = true;}
      if(RBKYMphyAh == OMMtwSiebD){HmPFuDkqOW = true;}
      if(eiwPiiWgZO == dykDDHYEWb){dUTrGHpTTj = true;}
      if(jgPGlpIwZo == MQQMfmexAJ){lVeLmfDRRK = true;}
      while(OMMtwSiebD == RBKYMphyAh){pKgPjxMkBc = true;}
      while(dykDDHYEWb == dykDDHYEWb){fajVbGIhrP = true;}
      while(MQQMfmexAJ == MQQMfmexAJ){HADBkdfCdX = true;}
      if(SqwmUGNRXV == true){SqwmUGNRXV = false;}
      if(aPwpfJkyDn == true){aPwpfJkyDn = false;}
      if(KRrPTxuAOJ == true){KRrPTxuAOJ = false;}
      if(mkeSjlCyix == true){mkeSjlCyix = false;}
      if(sHfAAwTafV == true){sHfAAwTafV = false;}
      if(CftLyAzfTW == true){CftLyAzfTW = false;}
      if(KNDOhojdFt == true){KNDOhojdFt = false;}
      if(HmPFuDkqOW == true){HmPFuDkqOW = false;}
      if(dUTrGHpTTj == true){dUTrGHpTTj = false;}
      if(lVeLmfDRRK == true){lVeLmfDRRK = false;}
      if(LpUlOOQoPu == true){LpUlOOQoPu = false;}
      if(PHQwsosKHa == true){PHQwsosKHa = false;}
      if(zQJVHkIDSO == true){zQJVHkIDSO = false;}
      if(zSYEKmzhdr == true){zSYEKmzhdr = false;}
      if(qBDYTeEhSx == true){qBDYTeEhSx = false;}
      if(mrJqLufzec == true){mrJqLufzec = false;}
      if(GMVBuwiMlF == true){GMVBuwiMlF = false;}
      if(pKgPjxMkBc == true){pKgPjxMkBc = false;}
      if(fajVbGIhrP == true){fajVbGIhrP = false;}
      if(HADBkdfCdX == true){HADBkdfCdX = false;}
    } 
}; 
