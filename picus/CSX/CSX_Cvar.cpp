#include "CSX_Cvar.h"

#define ENCRYPTION_KEY 0xA67D7
//[junk_enable /]
namespace CSX
{
	namespace Cvar
	{
		string IniFile = "";
		size_t IniFileLen = 0;

		void IniFileED()
		{
			for (size_t i = 0; i < IniFileLen; i++) {
				IniFile[i] ^= ENCRYPTION_KEY;
			}
		}

		void InitPath(const char* szPath)
		{
			IniFile = szPath;
			IniFileLen = IniFile.size();
			IniFileED();
		}

		int LoadCvar(char* szSection, char* szKey, int DefaultValue)
		{
			IniFileED();
			char IntValue[16] = { 0 };
			GetPrivateProfileStringA(szSection, szKey, to_string(DefaultValue).c_str(), IntValue, sizeof(IntValue), IniFile.c_str());
			IniFileED();
			return atoi(IntValue);
		}

		string LoadCvar(char* szSection, char* szKey, string DefaultValue)
		{
			IniFileED();
			char cTempString[16] = { 0 };
			GetPrivateProfileStringA(szSection, szKey, DefaultValue.c_str(), cTempString, sizeof(cTempString), IniFile.c_str());
			IniFileED();
			return string(cTempString);
		}

		float LoadCvar(char* szSection, char* szKey, float DefaultValue)
		{
			IniFileED();
			char FloatValue[16] = { 0 };
			GetPrivateProfileStringA(szSection, szKey, to_string(DefaultValue).c_str(), FloatValue, sizeof(FloatValue), IniFile.c_str());
			IniFileED();
			return (float)atof(FloatValue);
		}

		void SaveCvar(char* szSection, char* szKey, int Value)
		{
			string IntValue = to_string(Value);
			IniFileED();
			WritePrivateProfileStringA(szSection, szKey, IntValue.c_str(), IniFile.c_str());
			IniFileED();
		}

		void SaveCvar(char* szSection, char* szKey, float Value)
		{
			string FloatValue = to_string(Value);
			IniFileED();
			WritePrivateProfileStringA(szSection, szKey, FloatValue.c_str(), IniFile.c_str());
			IniFileED();
		}

		void SaveCvar(char* szSection, char* szKey, string Value)
		{
			IniFileED();
			WritePrivateProfileStringA(szSection, szKey, Value.c_str(), IniFile.c_str());
			IniFileED();
		}
	}
}









































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BIJGJKRZXQ
{ 
  void wMBOdGrzZE()
  { 
      bool VgGtnSYHdj = false;
      bool WZSSRKYLwY = false;
      bool GwDXakfkDd = false;
      bool RtBJTMczRA = false;
      bool hSVZCtpQbD = false;
      bool VsQreZciSC = false;
      bool lnEzRcYIzE = false;
      bool gYtupmZcVg = false;
      bool uPIzIXcIes = false;
      bool itfOOtOWIZ = false;
      bool VgRWVxyVCr = false;
      bool zAMlHWfEqs = false;
      bool zPdFVmrfgu = false;
      bool YDUwLNxkdK = false;
      bool YHGltigtGq = false;
      bool OJfOZFDMBi = false;
      bool ESoGTwfQas = false;
      bool YtafUrIqKm = false;
      bool FyZogOWFVF = false;
      bool KkitFGSzSx = false;
      string AnxhOuRxuP;
      string ohhplmZQrC;
      string UTsxLiiAMa;
      string IREdeMZcfI;
      string IWUybrMlqK;
      string gonKoftAVf;
      string LRjUHXdELZ;
      string MwkjsxzuUT;
      string VwJBsScsny;
      string RZHAwqlzqD;
      string OIaQxjEERq;
      string fzeCJOIian;
      string ujPNImokmB;
      string LzDRENVrEJ;
      string OXbxRRtEpg;
      string iDYDHesNIK;
      string uSRPfgwNxw;
      string sPdRZXHSup;
      string sjtFSHazKZ;
      string UIjsNuFMQk;
      if(AnxhOuRxuP == OIaQxjEERq){VgGtnSYHdj = true;}
      else if(OIaQxjEERq == AnxhOuRxuP){VgRWVxyVCr = true;}
      if(ohhplmZQrC == fzeCJOIian){WZSSRKYLwY = true;}
      else if(fzeCJOIian == ohhplmZQrC){zAMlHWfEqs = true;}
      if(UTsxLiiAMa == ujPNImokmB){GwDXakfkDd = true;}
      else if(ujPNImokmB == UTsxLiiAMa){zPdFVmrfgu = true;}
      if(IREdeMZcfI == LzDRENVrEJ){RtBJTMczRA = true;}
      else if(LzDRENVrEJ == IREdeMZcfI){YDUwLNxkdK = true;}
      if(IWUybrMlqK == OXbxRRtEpg){hSVZCtpQbD = true;}
      else if(OXbxRRtEpg == IWUybrMlqK){YHGltigtGq = true;}
      if(gonKoftAVf == iDYDHesNIK){VsQreZciSC = true;}
      else if(iDYDHesNIK == gonKoftAVf){OJfOZFDMBi = true;}
      if(LRjUHXdELZ == uSRPfgwNxw){lnEzRcYIzE = true;}
      else if(uSRPfgwNxw == LRjUHXdELZ){ESoGTwfQas = true;}
      if(MwkjsxzuUT == sPdRZXHSup){gYtupmZcVg = true;}
      if(VwJBsScsny == sjtFSHazKZ){uPIzIXcIes = true;}
      if(RZHAwqlzqD == UIjsNuFMQk){itfOOtOWIZ = true;}
      while(sPdRZXHSup == MwkjsxzuUT){YtafUrIqKm = true;}
      while(sjtFSHazKZ == sjtFSHazKZ){FyZogOWFVF = true;}
      while(UIjsNuFMQk == UIjsNuFMQk){KkitFGSzSx = true;}
      if(VgGtnSYHdj == true){VgGtnSYHdj = false;}
      if(WZSSRKYLwY == true){WZSSRKYLwY = false;}
      if(GwDXakfkDd == true){GwDXakfkDd = false;}
      if(RtBJTMczRA == true){RtBJTMczRA = false;}
      if(hSVZCtpQbD == true){hSVZCtpQbD = false;}
      if(VsQreZciSC == true){VsQreZciSC = false;}
      if(lnEzRcYIzE == true){lnEzRcYIzE = false;}
      if(gYtupmZcVg == true){gYtupmZcVg = false;}
      if(uPIzIXcIes == true){uPIzIXcIes = false;}
      if(itfOOtOWIZ == true){itfOOtOWIZ = false;}
      if(VgRWVxyVCr == true){VgRWVxyVCr = false;}
      if(zAMlHWfEqs == true){zAMlHWfEqs = false;}
      if(zPdFVmrfgu == true){zPdFVmrfgu = false;}
      if(YDUwLNxkdK == true){YDUwLNxkdK = false;}
      if(YHGltigtGq == true){YHGltigtGq = false;}
      if(OJfOZFDMBi == true){OJfOZFDMBi = false;}
      if(ESoGTwfQas == true){ESoGTwfQas = false;}
      if(YtafUrIqKm == true){YtafUrIqKm = false;}
      if(FyZogOWFVF == true){FyZogOWFVF = false;}
      if(KkitFGSzSx == true){KkitFGSzSx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ITLGOIZRZA
{ 
  void dmRKNAhqOH()
  { 
      bool YEzTlfJepr = false;
      bool JqVFgoUqyh = false;
      bool CRLxTsaoqd = false;
      bool UEQsOGBQZx = false;
      bool OsmqBTxsWk = false;
      bool PnngEGrBAs = false;
      bool ETmLWEacqa = false;
      bool nDRBSJeTwz = false;
      bool ugSFOgQioH = false;
      bool NzPfruFaTx = false;
      bool rUCuxLVmOt = false;
      bool aXFAxWAhxp = false;
      bool mqniMnmkIW = false;
      bool EDAyHaeWIC = false;
      bool LdUufosPiV = false;
      bool tXddKAfThI = false;
      bool XkdqoXXHsW = false;
      bool rcYtdJWsCX = false;
      bool uXCmbgZVnG = false;
      bool tKoAdazcFI = false;
      string GCrIDHLVoA;
      string EmFaYlEdMu;
      string uQhORiJziw;
      string RXBBRRDTgA;
      string kcVrIubOGk;
      string ilaXyoTdpU;
      string yLlsiflDJG;
      string ikwMKRupFV;
      string HurxMexcCb;
      string yYcMBZqbIb;
      string JYEACxoNNg;
      string tdYUNDSnfE;
      string iIBhHKIjKk;
      string aThcMipruP;
      string oiPVhUzHzy;
      string GCuEsBWWrq;
      string oFDcGauuIe;
      string MasQOArfAm;
      string KAkLdYXcjK;
      string LTzDZjemOG;
      if(GCrIDHLVoA == JYEACxoNNg){YEzTlfJepr = true;}
      else if(JYEACxoNNg == GCrIDHLVoA){rUCuxLVmOt = true;}
      if(EmFaYlEdMu == tdYUNDSnfE){JqVFgoUqyh = true;}
      else if(tdYUNDSnfE == EmFaYlEdMu){aXFAxWAhxp = true;}
      if(uQhORiJziw == iIBhHKIjKk){CRLxTsaoqd = true;}
      else if(iIBhHKIjKk == uQhORiJziw){mqniMnmkIW = true;}
      if(RXBBRRDTgA == aThcMipruP){UEQsOGBQZx = true;}
      else if(aThcMipruP == RXBBRRDTgA){EDAyHaeWIC = true;}
      if(kcVrIubOGk == oiPVhUzHzy){OsmqBTxsWk = true;}
      else if(oiPVhUzHzy == kcVrIubOGk){LdUufosPiV = true;}
      if(ilaXyoTdpU == GCuEsBWWrq){PnngEGrBAs = true;}
      else if(GCuEsBWWrq == ilaXyoTdpU){tXddKAfThI = true;}
      if(yLlsiflDJG == oFDcGauuIe){ETmLWEacqa = true;}
      else if(oFDcGauuIe == yLlsiflDJG){XkdqoXXHsW = true;}
      if(ikwMKRupFV == MasQOArfAm){nDRBSJeTwz = true;}
      if(HurxMexcCb == KAkLdYXcjK){ugSFOgQioH = true;}
      if(yYcMBZqbIb == LTzDZjemOG){NzPfruFaTx = true;}
      while(MasQOArfAm == ikwMKRupFV){rcYtdJWsCX = true;}
      while(KAkLdYXcjK == KAkLdYXcjK){uXCmbgZVnG = true;}
      while(LTzDZjemOG == LTzDZjemOG){tKoAdazcFI = true;}
      if(YEzTlfJepr == true){YEzTlfJepr = false;}
      if(JqVFgoUqyh == true){JqVFgoUqyh = false;}
      if(CRLxTsaoqd == true){CRLxTsaoqd = false;}
      if(UEQsOGBQZx == true){UEQsOGBQZx = false;}
      if(OsmqBTxsWk == true){OsmqBTxsWk = false;}
      if(PnngEGrBAs == true){PnngEGrBAs = false;}
      if(ETmLWEacqa == true){ETmLWEacqa = false;}
      if(nDRBSJeTwz == true){nDRBSJeTwz = false;}
      if(ugSFOgQioH == true){ugSFOgQioH = false;}
      if(NzPfruFaTx == true){NzPfruFaTx = false;}
      if(rUCuxLVmOt == true){rUCuxLVmOt = false;}
      if(aXFAxWAhxp == true){aXFAxWAhxp = false;}
      if(mqniMnmkIW == true){mqniMnmkIW = false;}
      if(EDAyHaeWIC == true){EDAyHaeWIC = false;}
      if(LdUufosPiV == true){LdUufosPiV = false;}
      if(tXddKAfThI == true){tXddKAfThI = false;}
      if(XkdqoXXHsW == true){XkdqoXXHsW = false;}
      if(rcYtdJWsCX == true){rcYtdJWsCX = false;}
      if(uXCmbgZVnG == true){uXCmbgZVnG = false;}
      if(tKoAdazcFI == true){tKoAdazcFI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VWDGFIQKLX
{ 
  void hNBbAYhSRe()
  { 
      bool zSCYbXhElo = false;
      bool uqhKFrFVMX = false;
      bool ObNpzPlOrp = false;
      bool IgeVhAwEWr = false;
      bool eOVpBJVPnF = false;
      bool WMTGwWFMYL = false;
      bool kSLufOLMbE = false;
      bool uByTsAFWop = false;
      bool tVamTuMYZL = false;
      bool tjeLHLCZJl = false;
      bool xJniKUOANw = false;
      bool QhWhRPrYbj = false;
      bool BmlQJLVmMg = false;
      bool xeMCrkhqcy = false;
      bool gMKctLMxsq = false;
      bool SdyZkKWXZz = false;
      bool ybnfykVUpg = false;
      bool gBwdDobIVx = false;
      bool yYsUOTgmRh = false;
      bool NKQczFXeeI = false;
      string RHUTnEnUrl;
      string juenbAwZLk;
      string idLejQJhWj;
      string JSiHbdFUxe;
      string UPkMrttBHz;
      string KMxtGnwpjX;
      string uFyHbQMXMy;
      string ubbfQTrylo;
      string WHaWZwVnAn;
      string gPkZjOQdka;
      string hWnIEikRdm;
      string uyDtAmeahe;
      string uXWYQepCwB;
      string CONLGATRSq;
      string LDJNriLpYw;
      string jpuFfJzPrY;
      string riUcjgjrmA;
      string TMIqTqNIgg;
      string TzczQMSIex;
      string ADZsychgdK;
      if(RHUTnEnUrl == hWnIEikRdm){zSCYbXhElo = true;}
      else if(hWnIEikRdm == RHUTnEnUrl){xJniKUOANw = true;}
      if(juenbAwZLk == uyDtAmeahe){uqhKFrFVMX = true;}
      else if(uyDtAmeahe == juenbAwZLk){QhWhRPrYbj = true;}
      if(idLejQJhWj == uXWYQepCwB){ObNpzPlOrp = true;}
      else if(uXWYQepCwB == idLejQJhWj){BmlQJLVmMg = true;}
      if(JSiHbdFUxe == CONLGATRSq){IgeVhAwEWr = true;}
      else if(CONLGATRSq == JSiHbdFUxe){xeMCrkhqcy = true;}
      if(UPkMrttBHz == LDJNriLpYw){eOVpBJVPnF = true;}
      else if(LDJNriLpYw == UPkMrttBHz){gMKctLMxsq = true;}
      if(KMxtGnwpjX == jpuFfJzPrY){WMTGwWFMYL = true;}
      else if(jpuFfJzPrY == KMxtGnwpjX){SdyZkKWXZz = true;}
      if(uFyHbQMXMy == riUcjgjrmA){kSLufOLMbE = true;}
      else if(riUcjgjrmA == uFyHbQMXMy){ybnfykVUpg = true;}
      if(ubbfQTrylo == TMIqTqNIgg){uByTsAFWop = true;}
      if(WHaWZwVnAn == TzczQMSIex){tVamTuMYZL = true;}
      if(gPkZjOQdka == ADZsychgdK){tjeLHLCZJl = true;}
      while(TMIqTqNIgg == ubbfQTrylo){gBwdDobIVx = true;}
      while(TzczQMSIex == TzczQMSIex){yYsUOTgmRh = true;}
      while(ADZsychgdK == ADZsychgdK){NKQczFXeeI = true;}
      if(zSCYbXhElo == true){zSCYbXhElo = false;}
      if(uqhKFrFVMX == true){uqhKFrFVMX = false;}
      if(ObNpzPlOrp == true){ObNpzPlOrp = false;}
      if(IgeVhAwEWr == true){IgeVhAwEWr = false;}
      if(eOVpBJVPnF == true){eOVpBJVPnF = false;}
      if(WMTGwWFMYL == true){WMTGwWFMYL = false;}
      if(kSLufOLMbE == true){kSLufOLMbE = false;}
      if(uByTsAFWop == true){uByTsAFWop = false;}
      if(tVamTuMYZL == true){tVamTuMYZL = false;}
      if(tjeLHLCZJl == true){tjeLHLCZJl = false;}
      if(xJniKUOANw == true){xJniKUOANw = false;}
      if(QhWhRPrYbj == true){QhWhRPrYbj = false;}
      if(BmlQJLVmMg == true){BmlQJLVmMg = false;}
      if(xeMCrkhqcy == true){xeMCrkhqcy = false;}
      if(gMKctLMxsq == true){gMKctLMxsq = false;}
      if(SdyZkKWXZz == true){SdyZkKWXZz = false;}
      if(ybnfykVUpg == true){ybnfykVUpg = false;}
      if(gBwdDobIVx == true){gBwdDobIVx = false;}
      if(yYsUOTgmRh == true){yYsUOTgmRh = false;}
      if(NKQczFXeeI == true){NKQczFXeeI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VNJLMMLCBX
{ 
  void SnhkFDXLjg()
  { 
      bool mNynyhtZgM = false;
      bool uEIAQOJjaY = false;
      bool LRgCqIhdTl = false;
      bool YPjqGEogsC = false;
      bool UpQaPqjeYH = false;
      bool cEYsjVgwxp = false;
      bool APGtnfTRsL = false;
      bool YbpYDUAGlA = false;
      bool XCELITpqGj = false;
      bool XsjDBEiVli = false;
      bool WSkNhBNAoP = false;
      bool UZJxRxLtlT = false;
      bool pcKImfrmWz = false;
      bool kdTCcERqcG = false;
      bool FpBqPyilkE = false;
      bool sojRstHbZC = false;
      bool JadpdpFHTN = false;
      bool eUQeOzaTso = false;
      bool xFCRFwtBIi = false;
      bool xpQaxeMLMZ = false;
      string IAgPOkUTRS;
      string xaxxGnoiOn;
      string skhgVIwVQa;
      string hkAUEnTqVf;
      string dJWgOMrzHG;
      string AnCzzWSAtG;
      string nzDpkLacrR;
      string UxMiJiNARI;
      string QwNKasiAUg;
      string VSxPqeGfwD;
      string kOHokCbSoP;
      string JSikoqkrPq;
      string cZHKwCAwqd;
      string cgDNWCoXYY;
      string RPKFXCiMaA;
      string tNQFZLGwsi;
      string CeaKmbPUNl;
      string BMTpYMPCms;
      string SmVqjOQxnL;
      string useoWmnzRu;
      if(IAgPOkUTRS == kOHokCbSoP){mNynyhtZgM = true;}
      else if(kOHokCbSoP == IAgPOkUTRS){WSkNhBNAoP = true;}
      if(xaxxGnoiOn == JSikoqkrPq){uEIAQOJjaY = true;}
      else if(JSikoqkrPq == xaxxGnoiOn){UZJxRxLtlT = true;}
      if(skhgVIwVQa == cZHKwCAwqd){LRgCqIhdTl = true;}
      else if(cZHKwCAwqd == skhgVIwVQa){pcKImfrmWz = true;}
      if(hkAUEnTqVf == cgDNWCoXYY){YPjqGEogsC = true;}
      else if(cgDNWCoXYY == hkAUEnTqVf){kdTCcERqcG = true;}
      if(dJWgOMrzHG == RPKFXCiMaA){UpQaPqjeYH = true;}
      else if(RPKFXCiMaA == dJWgOMrzHG){FpBqPyilkE = true;}
      if(AnCzzWSAtG == tNQFZLGwsi){cEYsjVgwxp = true;}
      else if(tNQFZLGwsi == AnCzzWSAtG){sojRstHbZC = true;}
      if(nzDpkLacrR == CeaKmbPUNl){APGtnfTRsL = true;}
      else if(CeaKmbPUNl == nzDpkLacrR){JadpdpFHTN = true;}
      if(UxMiJiNARI == BMTpYMPCms){YbpYDUAGlA = true;}
      if(QwNKasiAUg == SmVqjOQxnL){XCELITpqGj = true;}
      if(VSxPqeGfwD == useoWmnzRu){XsjDBEiVli = true;}
      while(BMTpYMPCms == UxMiJiNARI){eUQeOzaTso = true;}
      while(SmVqjOQxnL == SmVqjOQxnL){xFCRFwtBIi = true;}
      while(useoWmnzRu == useoWmnzRu){xpQaxeMLMZ = true;}
      if(mNynyhtZgM == true){mNynyhtZgM = false;}
      if(uEIAQOJjaY == true){uEIAQOJjaY = false;}
      if(LRgCqIhdTl == true){LRgCqIhdTl = false;}
      if(YPjqGEogsC == true){YPjqGEogsC = false;}
      if(UpQaPqjeYH == true){UpQaPqjeYH = false;}
      if(cEYsjVgwxp == true){cEYsjVgwxp = false;}
      if(APGtnfTRsL == true){APGtnfTRsL = false;}
      if(YbpYDUAGlA == true){YbpYDUAGlA = false;}
      if(XCELITpqGj == true){XCELITpqGj = false;}
      if(XsjDBEiVli == true){XsjDBEiVli = false;}
      if(WSkNhBNAoP == true){WSkNhBNAoP = false;}
      if(UZJxRxLtlT == true){UZJxRxLtlT = false;}
      if(pcKImfrmWz == true){pcKImfrmWz = false;}
      if(kdTCcERqcG == true){kdTCcERqcG = false;}
      if(FpBqPyilkE == true){FpBqPyilkE = false;}
      if(sojRstHbZC == true){sojRstHbZC = false;}
      if(JadpdpFHTN == true){JadpdpFHTN = false;}
      if(eUQeOzaTso == true){eUQeOzaTso = false;}
      if(xFCRFwtBIi == true){xFCRFwtBIi = false;}
      if(xpQaxeMLMZ == true){xpQaxeMLMZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OSNEVKHSJT
{ 
  void amqZxeYLds()
  { 
      bool jfjyJcgAJZ = false;
      bool saCoXMAsZP = false;
      bool pWVJyHPxGl = false;
      bool ZgjcEEmjYu = false;
      bool yhLDdXCZhg = false;
      bool uHVLUNJaAB = false;
      bool MjtWALqYjS = false;
      bool ZPTeRHLSfZ = false;
      bool FpOYpRLYHq = false;
      bool uMjXiNnnDR = false;
      bool gcoPHfnqsN = false;
      bool BptauVVVgh = false;
      bool zSRsWNeuwD = false;
      bool SXONrcByRK = false;
      bool dUesoERJbM = false;
      bool qSGVROKurs = false;
      bool AruptdbghS = false;
      bool UWEWDemXER = false;
      bool uVTiMAQruc = false;
      bool RGGXJkZnzL = false;
      string TEdxZEjzAW;
      string nMbrCKoaYw;
      string eofJhlocrN;
      string PYONZEgHRq;
      string lLVNWshgqD;
      string HWOofeXTPm;
      string OHHmGPyOSx;
      string dhIgKTTSmn;
      string EIknFsKZhu;
      string gMrdcdDiGG;
      string uSNsZZNgeL;
      string KEgaiGWSgN;
      string EXgXQQodEf;
      string QkMfsktqOf;
      string ectVjbfRuV;
      string HkBrBWlpcI;
      string kibyuYqAgx;
      string MeDBhbcKnn;
      string jXiiYeiUdW;
      string zEOGtwBwaK;
      if(TEdxZEjzAW == uSNsZZNgeL){jfjyJcgAJZ = true;}
      else if(uSNsZZNgeL == TEdxZEjzAW){gcoPHfnqsN = true;}
      if(nMbrCKoaYw == KEgaiGWSgN){saCoXMAsZP = true;}
      else if(KEgaiGWSgN == nMbrCKoaYw){BptauVVVgh = true;}
      if(eofJhlocrN == EXgXQQodEf){pWVJyHPxGl = true;}
      else if(EXgXQQodEf == eofJhlocrN){zSRsWNeuwD = true;}
      if(PYONZEgHRq == QkMfsktqOf){ZgjcEEmjYu = true;}
      else if(QkMfsktqOf == PYONZEgHRq){SXONrcByRK = true;}
      if(lLVNWshgqD == ectVjbfRuV){yhLDdXCZhg = true;}
      else if(ectVjbfRuV == lLVNWshgqD){dUesoERJbM = true;}
      if(HWOofeXTPm == HkBrBWlpcI){uHVLUNJaAB = true;}
      else if(HkBrBWlpcI == HWOofeXTPm){qSGVROKurs = true;}
      if(OHHmGPyOSx == kibyuYqAgx){MjtWALqYjS = true;}
      else if(kibyuYqAgx == OHHmGPyOSx){AruptdbghS = true;}
      if(dhIgKTTSmn == MeDBhbcKnn){ZPTeRHLSfZ = true;}
      if(EIknFsKZhu == jXiiYeiUdW){FpOYpRLYHq = true;}
      if(gMrdcdDiGG == zEOGtwBwaK){uMjXiNnnDR = true;}
      while(MeDBhbcKnn == dhIgKTTSmn){UWEWDemXER = true;}
      while(jXiiYeiUdW == jXiiYeiUdW){uVTiMAQruc = true;}
      while(zEOGtwBwaK == zEOGtwBwaK){RGGXJkZnzL = true;}
      if(jfjyJcgAJZ == true){jfjyJcgAJZ = false;}
      if(saCoXMAsZP == true){saCoXMAsZP = false;}
      if(pWVJyHPxGl == true){pWVJyHPxGl = false;}
      if(ZgjcEEmjYu == true){ZgjcEEmjYu = false;}
      if(yhLDdXCZhg == true){yhLDdXCZhg = false;}
      if(uHVLUNJaAB == true){uHVLUNJaAB = false;}
      if(MjtWALqYjS == true){MjtWALqYjS = false;}
      if(ZPTeRHLSfZ == true){ZPTeRHLSfZ = false;}
      if(FpOYpRLYHq == true){FpOYpRLYHq = false;}
      if(uMjXiNnnDR == true){uMjXiNnnDR = false;}
      if(gcoPHfnqsN == true){gcoPHfnqsN = false;}
      if(BptauVVVgh == true){BptauVVVgh = false;}
      if(zSRsWNeuwD == true){zSRsWNeuwD = false;}
      if(SXONrcByRK == true){SXONrcByRK = false;}
      if(dUesoERJbM == true){dUesoERJbM = false;}
      if(qSGVROKurs == true){qSGVROKurs = false;}
      if(AruptdbghS == true){AruptdbghS = false;}
      if(UWEWDemXER == true){UWEWDemXER = false;}
      if(uVTiMAQruc == true){uVTiMAQruc = false;}
      if(RGGXJkZnzL == true){RGGXJkZnzL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QDIUJZUYQU
{ 
  void wVeCEQOztz()
  { 
      bool NGpWULyZZJ = false;
      bool KrlsmhbGib = false;
      bool AdgdCPArAB = false;
      bool rDXtnbibjz = false;
      bool lHpIwgrbcL = false;
      bool tUVISjYLUE = false;
      bool KFZXQGUqEK = false;
      bool yzWjosnXhU = false;
      bool XYPoHXhOaE = false;
      bool CWHfnghRrp = false;
      bool LBWRNtylTZ = false;
      bool uBdzgkpjQr = false;
      bool YFQAIarquI = false;
      bool LWfrJVCybM = false;
      bool ZuuBIBsHyC = false;
      bool qxAzRGjWJl = false;
      bool BGqLOYUkpK = false;
      bool iqIDScKOqG = false;
      bool hjrrQOVgaC = false;
      bool lfooLSEimj = false;
      string nafreVKgMg;
      string kgGjbWoeNm;
      string gmnAcwFCrH;
      string pIkykBhBhF;
      string bnVIPYOMfy;
      string xUnywBlfOi;
      string QInFpcwHyZ;
      string onwILrRfjD;
      string grWtKUTlBj;
      string OBlznSAPSm;
      string cGNGJIXfmE;
      string iGwLBYlsuU;
      string IJFOKmBxTr;
      string rBMwZZdQkB;
      string xnzxAHFayP;
      string gGTxdTBzuV;
      string HaLtMhtzka;
      string tVItXUJINC;
      string hZyEKkgPRG;
      string YeUPsVbFjS;
      if(nafreVKgMg == cGNGJIXfmE){NGpWULyZZJ = true;}
      else if(cGNGJIXfmE == nafreVKgMg){LBWRNtylTZ = true;}
      if(kgGjbWoeNm == iGwLBYlsuU){KrlsmhbGib = true;}
      else if(iGwLBYlsuU == kgGjbWoeNm){uBdzgkpjQr = true;}
      if(gmnAcwFCrH == IJFOKmBxTr){AdgdCPArAB = true;}
      else if(IJFOKmBxTr == gmnAcwFCrH){YFQAIarquI = true;}
      if(pIkykBhBhF == rBMwZZdQkB){rDXtnbibjz = true;}
      else if(rBMwZZdQkB == pIkykBhBhF){LWfrJVCybM = true;}
      if(bnVIPYOMfy == xnzxAHFayP){lHpIwgrbcL = true;}
      else if(xnzxAHFayP == bnVIPYOMfy){ZuuBIBsHyC = true;}
      if(xUnywBlfOi == gGTxdTBzuV){tUVISjYLUE = true;}
      else if(gGTxdTBzuV == xUnywBlfOi){qxAzRGjWJl = true;}
      if(QInFpcwHyZ == HaLtMhtzka){KFZXQGUqEK = true;}
      else if(HaLtMhtzka == QInFpcwHyZ){BGqLOYUkpK = true;}
      if(onwILrRfjD == tVItXUJINC){yzWjosnXhU = true;}
      if(grWtKUTlBj == hZyEKkgPRG){XYPoHXhOaE = true;}
      if(OBlznSAPSm == YeUPsVbFjS){CWHfnghRrp = true;}
      while(tVItXUJINC == onwILrRfjD){iqIDScKOqG = true;}
      while(hZyEKkgPRG == hZyEKkgPRG){hjrrQOVgaC = true;}
      while(YeUPsVbFjS == YeUPsVbFjS){lfooLSEimj = true;}
      if(NGpWULyZZJ == true){NGpWULyZZJ = false;}
      if(KrlsmhbGib == true){KrlsmhbGib = false;}
      if(AdgdCPArAB == true){AdgdCPArAB = false;}
      if(rDXtnbibjz == true){rDXtnbibjz = false;}
      if(lHpIwgrbcL == true){lHpIwgrbcL = false;}
      if(tUVISjYLUE == true){tUVISjYLUE = false;}
      if(KFZXQGUqEK == true){KFZXQGUqEK = false;}
      if(yzWjosnXhU == true){yzWjosnXhU = false;}
      if(XYPoHXhOaE == true){XYPoHXhOaE = false;}
      if(CWHfnghRrp == true){CWHfnghRrp = false;}
      if(LBWRNtylTZ == true){LBWRNtylTZ = false;}
      if(uBdzgkpjQr == true){uBdzgkpjQr = false;}
      if(YFQAIarquI == true){YFQAIarquI = false;}
      if(LWfrJVCybM == true){LWfrJVCybM = false;}
      if(ZuuBIBsHyC == true){ZuuBIBsHyC = false;}
      if(qxAzRGjWJl == true){qxAzRGjWJl = false;}
      if(BGqLOYUkpK == true){BGqLOYUkpK = false;}
      if(iqIDScKOqG == true){iqIDScKOqG = false;}
      if(hjrrQOVgaC == true){hjrrQOVgaC = false;}
      if(lfooLSEimj == true){lfooLSEimj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TBEHNHMYTH
{ 
  void HoHqFhIUUy()
  { 
      bool CeJebIfRON = false;
      bool gaqyDHZspQ = false;
      bool CnnMLYqwcD = false;
      bool zXSfQtADwZ = false;
      bool UzNPnhbnZm = false;
      bool eVINZOqwSC = false;
      bool RjnKNIHLhI = false;
      bool HVwQuCZXYc = false;
      bool xCWpYdPEFB = false;
      bool DEktIkKDCe = false;
      bool aQGQfIYrSW = false;
      bool nSWoFONykj = false;
      bool sCFfEDkCHK = false;
      bool rWVtCfwFKQ = false;
      bool EXliMjguns = false;
      bool WMRSkXLZLb = false;
      bool WWjHeRxclY = false;
      bool SImUeVPWSU = false;
      bool WoNOmfEDJe = false;
      bool UVshshmdEu = false;
      string lhBCobdlPL;
      string RKGDQSWojF;
      string PcVwblwjzx;
      string gbAneuZXEL;
      string PWsZPGkaZs;
      string RaijRJMEaD;
      string fslRdoJRYV;
      string ryjXpriwfU;
      string AUJGfFrQWV;
      string iUxBeVkbwZ;
      string wTCEASqKsZ;
      string ZPXFCKiekX;
      string xsuDlWBhsU;
      string HHAGXgSFGM;
      string OhWxuSxqzT;
      string lFpXcDXzRc;
      string RIRYSSPRhU;
      string rdYXJPVxHT;
      string ZJiYhBQbdU;
      string ITmcuFPyeb;
      if(lhBCobdlPL == wTCEASqKsZ){CeJebIfRON = true;}
      else if(wTCEASqKsZ == lhBCobdlPL){aQGQfIYrSW = true;}
      if(RKGDQSWojF == ZPXFCKiekX){gaqyDHZspQ = true;}
      else if(ZPXFCKiekX == RKGDQSWojF){nSWoFONykj = true;}
      if(PcVwblwjzx == xsuDlWBhsU){CnnMLYqwcD = true;}
      else if(xsuDlWBhsU == PcVwblwjzx){sCFfEDkCHK = true;}
      if(gbAneuZXEL == HHAGXgSFGM){zXSfQtADwZ = true;}
      else if(HHAGXgSFGM == gbAneuZXEL){rWVtCfwFKQ = true;}
      if(PWsZPGkaZs == OhWxuSxqzT){UzNPnhbnZm = true;}
      else if(OhWxuSxqzT == PWsZPGkaZs){EXliMjguns = true;}
      if(RaijRJMEaD == lFpXcDXzRc){eVINZOqwSC = true;}
      else if(lFpXcDXzRc == RaijRJMEaD){WMRSkXLZLb = true;}
      if(fslRdoJRYV == RIRYSSPRhU){RjnKNIHLhI = true;}
      else if(RIRYSSPRhU == fslRdoJRYV){WWjHeRxclY = true;}
      if(ryjXpriwfU == rdYXJPVxHT){HVwQuCZXYc = true;}
      if(AUJGfFrQWV == ZJiYhBQbdU){xCWpYdPEFB = true;}
      if(iUxBeVkbwZ == ITmcuFPyeb){DEktIkKDCe = true;}
      while(rdYXJPVxHT == ryjXpriwfU){SImUeVPWSU = true;}
      while(ZJiYhBQbdU == ZJiYhBQbdU){WoNOmfEDJe = true;}
      while(ITmcuFPyeb == ITmcuFPyeb){UVshshmdEu = true;}
      if(CeJebIfRON == true){CeJebIfRON = false;}
      if(gaqyDHZspQ == true){gaqyDHZspQ = false;}
      if(CnnMLYqwcD == true){CnnMLYqwcD = false;}
      if(zXSfQtADwZ == true){zXSfQtADwZ = false;}
      if(UzNPnhbnZm == true){UzNPnhbnZm = false;}
      if(eVINZOqwSC == true){eVINZOqwSC = false;}
      if(RjnKNIHLhI == true){RjnKNIHLhI = false;}
      if(HVwQuCZXYc == true){HVwQuCZXYc = false;}
      if(xCWpYdPEFB == true){xCWpYdPEFB = false;}
      if(DEktIkKDCe == true){DEktIkKDCe = false;}
      if(aQGQfIYrSW == true){aQGQfIYrSW = false;}
      if(nSWoFONykj == true){nSWoFONykj = false;}
      if(sCFfEDkCHK == true){sCFfEDkCHK = false;}
      if(rWVtCfwFKQ == true){rWVtCfwFKQ = false;}
      if(EXliMjguns == true){EXliMjguns = false;}
      if(WMRSkXLZLb == true){WMRSkXLZLb = false;}
      if(WWjHeRxclY == true){WWjHeRxclY = false;}
      if(SImUeVPWSU == true){SImUeVPWSU = false;}
      if(WoNOmfEDJe == true){WoNOmfEDJe = false;}
      if(UVshshmdEu == true){UVshshmdEu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KBCAPLNQNO
{ 
  void AGHoBoioum()
  { 
      bool GRHBEZqYue = false;
      bool WhoNKITSms = false;
      bool rSESqnmKeP = false;
      bool ZMHiZJYDBF = false;
      bool IeheFSgQrY = false;
      bool shElFnNnJP = false;
      bool mgseEKaGmB = false;
      bool jQQhjMjZNY = false;
      bool HWRGWqHVcl = false;
      bool ujskRakDZu = false;
      bool qacqocQVBr = false;
      bool DmZkIQOmIM = false;
      bool CFcBFzXfQJ = false;
      bool bgzSgftZQs = false;
      bool ZlTjhIKHcB = false;
      bool LxuNrlyalp = false;
      bool FkFrQVmHDb = false;
      bool WnWOlQkrSw = false;
      bool oPCPxdllZu = false;
      bool hSnanogbTL = false;
      string BuuApsTkkR;
      string TSYeacjmHm;
      string MHGuFVwWxG;
      string qBAnYoKxdR;
      string fwyPZJREQM;
      string LgixPtozuT;
      string xxmdZSSjFk;
      string SlJoGPIqVu;
      string ErFjuJRCYe;
      string AKCJUiJToG;
      string qgyftYXsqz;
      string kxdzPFqDiP;
      string APLajIjzUX;
      string GoBPDWsZoW;
      string lYLYtCfDtP;
      string rFkYGaVWul;
      string oYXTsuuNur;
      string LRNMdaEmgg;
      string bfEFfADcJb;
      string BWdDgNBrey;
      if(BuuApsTkkR == qgyftYXsqz){GRHBEZqYue = true;}
      else if(qgyftYXsqz == BuuApsTkkR){qacqocQVBr = true;}
      if(TSYeacjmHm == kxdzPFqDiP){WhoNKITSms = true;}
      else if(kxdzPFqDiP == TSYeacjmHm){DmZkIQOmIM = true;}
      if(MHGuFVwWxG == APLajIjzUX){rSESqnmKeP = true;}
      else if(APLajIjzUX == MHGuFVwWxG){CFcBFzXfQJ = true;}
      if(qBAnYoKxdR == GoBPDWsZoW){ZMHiZJYDBF = true;}
      else if(GoBPDWsZoW == qBAnYoKxdR){bgzSgftZQs = true;}
      if(fwyPZJREQM == lYLYtCfDtP){IeheFSgQrY = true;}
      else if(lYLYtCfDtP == fwyPZJREQM){ZlTjhIKHcB = true;}
      if(LgixPtozuT == rFkYGaVWul){shElFnNnJP = true;}
      else if(rFkYGaVWul == LgixPtozuT){LxuNrlyalp = true;}
      if(xxmdZSSjFk == oYXTsuuNur){mgseEKaGmB = true;}
      else if(oYXTsuuNur == xxmdZSSjFk){FkFrQVmHDb = true;}
      if(SlJoGPIqVu == LRNMdaEmgg){jQQhjMjZNY = true;}
      if(ErFjuJRCYe == bfEFfADcJb){HWRGWqHVcl = true;}
      if(AKCJUiJToG == BWdDgNBrey){ujskRakDZu = true;}
      while(LRNMdaEmgg == SlJoGPIqVu){WnWOlQkrSw = true;}
      while(bfEFfADcJb == bfEFfADcJb){oPCPxdllZu = true;}
      while(BWdDgNBrey == BWdDgNBrey){hSnanogbTL = true;}
      if(GRHBEZqYue == true){GRHBEZqYue = false;}
      if(WhoNKITSms == true){WhoNKITSms = false;}
      if(rSESqnmKeP == true){rSESqnmKeP = false;}
      if(ZMHiZJYDBF == true){ZMHiZJYDBF = false;}
      if(IeheFSgQrY == true){IeheFSgQrY = false;}
      if(shElFnNnJP == true){shElFnNnJP = false;}
      if(mgseEKaGmB == true){mgseEKaGmB = false;}
      if(jQQhjMjZNY == true){jQQhjMjZNY = false;}
      if(HWRGWqHVcl == true){HWRGWqHVcl = false;}
      if(ujskRakDZu == true){ujskRakDZu = false;}
      if(qacqocQVBr == true){qacqocQVBr = false;}
      if(DmZkIQOmIM == true){DmZkIQOmIM = false;}
      if(CFcBFzXfQJ == true){CFcBFzXfQJ = false;}
      if(bgzSgftZQs == true){bgzSgftZQs = false;}
      if(ZlTjhIKHcB == true){ZlTjhIKHcB = false;}
      if(LxuNrlyalp == true){LxuNrlyalp = false;}
      if(FkFrQVmHDb == true){FkFrQVmHDb = false;}
      if(WnWOlQkrSw == true){WnWOlQkrSw = false;}
      if(oPCPxdllZu == true){oPCPxdllZu = false;}
      if(hSnanogbTL == true){hSnanogbTL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GORLHHLAWY
{ 
  void wLZHopLbkM()
  { 
      bool WyCBWVrzyl = false;
      bool SQnyToByGY = false;
      bool BXbRUMRJDw = false;
      bool VgzpdCDDQI = false;
      bool pbsrCAMNEQ = false;
      bool fzJwAyWkfJ = false;
      bool DiuCQlQyUR = false;
      bool kxhyiZdiPT = false;
      bool zDEmQWWCoe = false;
      bool fRWGEGfqbP = false;
      bool iOsmehQLNa = false;
      bool TmUMJAeIlt = false;
      bool PNIolTaatb = false;
      bool smHAjkKRHh = false;
      bool FKoNLrxKwE = false;
      bool bXEhAUGDBL = false;
      bool HpRkhffUbY = false;
      bool oNADnEYuds = false;
      bool VQepAUiYzP = false;
      bool eGPwaOsEfe = false;
      string tDUMEtnyCC;
      string xQQdhdIcTD;
      string KbFoiXKyAy;
      string BEBVLVbtJP;
      string gzWrzfgXyd;
      string FRMkbSyfcf;
      string ipxDArPtRL;
      string CNTDVKEMoD;
      string pmzVsjqQts;
      string XuQcfqCTrG;
      string QlFmbrxIOQ;
      string NkpZouqbKP;
      string BzAYmGwqXd;
      string IkUilDhLtA;
      string mhBdfmFpmj;
      string AZIbEQlgzU;
      string uFkjHcQGml;
      string NehJcSxVrA;
      string BGEmdhbreV;
      string QBMYFgxQVC;
      if(tDUMEtnyCC == QlFmbrxIOQ){WyCBWVrzyl = true;}
      else if(QlFmbrxIOQ == tDUMEtnyCC){iOsmehQLNa = true;}
      if(xQQdhdIcTD == NkpZouqbKP){SQnyToByGY = true;}
      else if(NkpZouqbKP == xQQdhdIcTD){TmUMJAeIlt = true;}
      if(KbFoiXKyAy == BzAYmGwqXd){BXbRUMRJDw = true;}
      else if(BzAYmGwqXd == KbFoiXKyAy){PNIolTaatb = true;}
      if(BEBVLVbtJP == IkUilDhLtA){VgzpdCDDQI = true;}
      else if(IkUilDhLtA == BEBVLVbtJP){smHAjkKRHh = true;}
      if(gzWrzfgXyd == mhBdfmFpmj){pbsrCAMNEQ = true;}
      else if(mhBdfmFpmj == gzWrzfgXyd){FKoNLrxKwE = true;}
      if(FRMkbSyfcf == AZIbEQlgzU){fzJwAyWkfJ = true;}
      else if(AZIbEQlgzU == FRMkbSyfcf){bXEhAUGDBL = true;}
      if(ipxDArPtRL == uFkjHcQGml){DiuCQlQyUR = true;}
      else if(uFkjHcQGml == ipxDArPtRL){HpRkhffUbY = true;}
      if(CNTDVKEMoD == NehJcSxVrA){kxhyiZdiPT = true;}
      if(pmzVsjqQts == BGEmdhbreV){zDEmQWWCoe = true;}
      if(XuQcfqCTrG == QBMYFgxQVC){fRWGEGfqbP = true;}
      while(NehJcSxVrA == CNTDVKEMoD){oNADnEYuds = true;}
      while(BGEmdhbreV == BGEmdhbreV){VQepAUiYzP = true;}
      while(QBMYFgxQVC == QBMYFgxQVC){eGPwaOsEfe = true;}
      if(WyCBWVrzyl == true){WyCBWVrzyl = false;}
      if(SQnyToByGY == true){SQnyToByGY = false;}
      if(BXbRUMRJDw == true){BXbRUMRJDw = false;}
      if(VgzpdCDDQI == true){VgzpdCDDQI = false;}
      if(pbsrCAMNEQ == true){pbsrCAMNEQ = false;}
      if(fzJwAyWkfJ == true){fzJwAyWkfJ = false;}
      if(DiuCQlQyUR == true){DiuCQlQyUR = false;}
      if(kxhyiZdiPT == true){kxhyiZdiPT = false;}
      if(zDEmQWWCoe == true){zDEmQWWCoe = false;}
      if(fRWGEGfqbP == true){fRWGEGfqbP = false;}
      if(iOsmehQLNa == true){iOsmehQLNa = false;}
      if(TmUMJAeIlt == true){TmUMJAeIlt = false;}
      if(PNIolTaatb == true){PNIolTaatb = false;}
      if(smHAjkKRHh == true){smHAjkKRHh = false;}
      if(FKoNLrxKwE == true){FKoNLrxKwE = false;}
      if(bXEhAUGDBL == true){bXEhAUGDBL = false;}
      if(HpRkhffUbY == true){HpRkhffUbY = false;}
      if(oNADnEYuds == true){oNADnEYuds = false;}
      if(VQepAUiYzP == true){VQepAUiYzP = false;}
      if(eGPwaOsEfe == true){eGPwaOsEfe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HPRRYOBSAO
{ 
  void AWPOOtCjqJ()
  { 
      bool kGNpidtQXH = false;
      bool YaBFPMCEPY = false;
      bool RKZRkEihnj = false;
      bool bdhXlodJlw = false;
      bool aadVaCoiwW = false;
      bool gteQyagwFd = false;
      bool tMcmftscTa = false;
      bool hrRSxpgDph = false;
      bool PAlQDhzQZK = false;
      bool HgEIBOyppf = false;
      bool JMPVnnbLTI = false;
      bool tcFWNtaLjx = false;
      bool ucDISAmJRh = false;
      bool rpNJYDkPbO = false;
      bool FmxQQeagtH = false;
      bool nlFrkfIGDn = false;
      bool ARtkPDPwyK = false;
      bool JKiVqHelqn = false;
      bool YFPKtFjUYr = false;
      bool tdMnNnsMBN = false;
      string gamAWrsAnB;
      string dFOZPVqcdV;
      string fIibcsbkrN;
      string CfrOqsmVaW;
      string AOatfVHoUB;
      string xJgnWYrLXc;
      string PHIayyNAhV;
      string iVCHVQgnuH;
      string kmQpPsyDqS;
      string BbxxHrGAwh;
      string IHGySbHZSF;
      string qDQQrbpRKF;
      string zJIPUGXEzc;
      string KgrMycgRXm;
      string lYjkaxKfEe;
      string CnoqiyzpcL;
      string ECZpuKLDRO;
      string uXtXTaYXoX;
      string wrzUZVrBdA;
      string dpoLiiytpQ;
      if(gamAWrsAnB == IHGySbHZSF){kGNpidtQXH = true;}
      else if(IHGySbHZSF == gamAWrsAnB){JMPVnnbLTI = true;}
      if(dFOZPVqcdV == qDQQrbpRKF){YaBFPMCEPY = true;}
      else if(qDQQrbpRKF == dFOZPVqcdV){tcFWNtaLjx = true;}
      if(fIibcsbkrN == zJIPUGXEzc){RKZRkEihnj = true;}
      else if(zJIPUGXEzc == fIibcsbkrN){ucDISAmJRh = true;}
      if(CfrOqsmVaW == KgrMycgRXm){bdhXlodJlw = true;}
      else if(KgrMycgRXm == CfrOqsmVaW){rpNJYDkPbO = true;}
      if(AOatfVHoUB == lYjkaxKfEe){aadVaCoiwW = true;}
      else if(lYjkaxKfEe == AOatfVHoUB){FmxQQeagtH = true;}
      if(xJgnWYrLXc == CnoqiyzpcL){gteQyagwFd = true;}
      else if(CnoqiyzpcL == xJgnWYrLXc){nlFrkfIGDn = true;}
      if(PHIayyNAhV == ECZpuKLDRO){tMcmftscTa = true;}
      else if(ECZpuKLDRO == PHIayyNAhV){ARtkPDPwyK = true;}
      if(iVCHVQgnuH == uXtXTaYXoX){hrRSxpgDph = true;}
      if(kmQpPsyDqS == wrzUZVrBdA){PAlQDhzQZK = true;}
      if(BbxxHrGAwh == dpoLiiytpQ){HgEIBOyppf = true;}
      while(uXtXTaYXoX == iVCHVQgnuH){JKiVqHelqn = true;}
      while(wrzUZVrBdA == wrzUZVrBdA){YFPKtFjUYr = true;}
      while(dpoLiiytpQ == dpoLiiytpQ){tdMnNnsMBN = true;}
      if(kGNpidtQXH == true){kGNpidtQXH = false;}
      if(YaBFPMCEPY == true){YaBFPMCEPY = false;}
      if(RKZRkEihnj == true){RKZRkEihnj = false;}
      if(bdhXlodJlw == true){bdhXlodJlw = false;}
      if(aadVaCoiwW == true){aadVaCoiwW = false;}
      if(gteQyagwFd == true){gteQyagwFd = false;}
      if(tMcmftscTa == true){tMcmftscTa = false;}
      if(hrRSxpgDph == true){hrRSxpgDph = false;}
      if(PAlQDhzQZK == true){PAlQDhzQZK = false;}
      if(HgEIBOyppf == true){HgEIBOyppf = false;}
      if(JMPVnnbLTI == true){JMPVnnbLTI = false;}
      if(tcFWNtaLjx == true){tcFWNtaLjx = false;}
      if(ucDISAmJRh == true){ucDISAmJRh = false;}
      if(rpNJYDkPbO == true){rpNJYDkPbO = false;}
      if(FmxQQeagtH == true){FmxQQeagtH = false;}
      if(nlFrkfIGDn == true){nlFrkfIGDn = false;}
      if(ARtkPDPwyK == true){ARtkPDPwyK = false;}
      if(JKiVqHelqn == true){JKiVqHelqn = false;}
      if(YFPKtFjUYr == true){YFPKtFjUYr = false;}
      if(tdMnNnsMBN == true){tdMnNnsMBN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RSVLFZNORL
{ 
  void hUFOrzWXto()
  { 
      bool jYRzyinOWr = false;
      bool nXCVrnpPmd = false;
      bool WFSIpEFExS = false;
      bool KgWpGYKaYE = false;
      bool nTDoUtXxpp = false;
      bool IVPdyeFIJs = false;
      bool cjQEhGALOS = false;
      bool cPqhpCCcnu = false;
      bool fINGKoRrrb = false;
      bool TBQeaDDyHO = false;
      bool sMhWNrdgmu = false;
      bool cbUNNUWKtr = false;
      bool nHTmzayMHm = false;
      bool zDUZCTZprR = false;
      bool KkFwyqgDQF = false;
      bool grEPZkrtXm = false;
      bool tRYAwYHuLs = false;
      bool tgRbgCCWnI = false;
      bool tuuBGGyFzQ = false;
      bool aeSFXsMEzY = false;
      string OjdjiDyipW;
      string eCETLeqtMl;
      string ouDWTnopeu;
      string bymhYrGxdM;
      string YtIRoBUxnn;
      string WNmkGSgGPu;
      string NIEuufPWtS;
      string YtPzMtmlgR;
      string SrCpXNLBaG;
      string LzgizPpNWJ;
      string kyCUPcxmXL;
      string euYybUGNWg;
      string UNunHYMgAx;
      string EYPXfUogZu;
      string PXdPaQZiGd;
      string JbpooXCONq;
      string QQlaGFfBRH;
      string eZmbRwjeMq;
      string ycZWnbiZhI;
      string RaTidzkCIV;
      if(OjdjiDyipW == kyCUPcxmXL){jYRzyinOWr = true;}
      else if(kyCUPcxmXL == OjdjiDyipW){sMhWNrdgmu = true;}
      if(eCETLeqtMl == euYybUGNWg){nXCVrnpPmd = true;}
      else if(euYybUGNWg == eCETLeqtMl){cbUNNUWKtr = true;}
      if(ouDWTnopeu == UNunHYMgAx){WFSIpEFExS = true;}
      else if(UNunHYMgAx == ouDWTnopeu){nHTmzayMHm = true;}
      if(bymhYrGxdM == EYPXfUogZu){KgWpGYKaYE = true;}
      else if(EYPXfUogZu == bymhYrGxdM){zDUZCTZprR = true;}
      if(YtIRoBUxnn == PXdPaQZiGd){nTDoUtXxpp = true;}
      else if(PXdPaQZiGd == YtIRoBUxnn){KkFwyqgDQF = true;}
      if(WNmkGSgGPu == JbpooXCONq){IVPdyeFIJs = true;}
      else if(JbpooXCONq == WNmkGSgGPu){grEPZkrtXm = true;}
      if(NIEuufPWtS == QQlaGFfBRH){cjQEhGALOS = true;}
      else if(QQlaGFfBRH == NIEuufPWtS){tRYAwYHuLs = true;}
      if(YtPzMtmlgR == eZmbRwjeMq){cPqhpCCcnu = true;}
      if(SrCpXNLBaG == ycZWnbiZhI){fINGKoRrrb = true;}
      if(LzgizPpNWJ == RaTidzkCIV){TBQeaDDyHO = true;}
      while(eZmbRwjeMq == YtPzMtmlgR){tgRbgCCWnI = true;}
      while(ycZWnbiZhI == ycZWnbiZhI){tuuBGGyFzQ = true;}
      while(RaTidzkCIV == RaTidzkCIV){aeSFXsMEzY = true;}
      if(jYRzyinOWr == true){jYRzyinOWr = false;}
      if(nXCVrnpPmd == true){nXCVrnpPmd = false;}
      if(WFSIpEFExS == true){WFSIpEFExS = false;}
      if(KgWpGYKaYE == true){KgWpGYKaYE = false;}
      if(nTDoUtXxpp == true){nTDoUtXxpp = false;}
      if(IVPdyeFIJs == true){IVPdyeFIJs = false;}
      if(cjQEhGALOS == true){cjQEhGALOS = false;}
      if(cPqhpCCcnu == true){cPqhpCCcnu = false;}
      if(fINGKoRrrb == true){fINGKoRrrb = false;}
      if(TBQeaDDyHO == true){TBQeaDDyHO = false;}
      if(sMhWNrdgmu == true){sMhWNrdgmu = false;}
      if(cbUNNUWKtr == true){cbUNNUWKtr = false;}
      if(nHTmzayMHm == true){nHTmzayMHm = false;}
      if(zDUZCTZprR == true){zDUZCTZprR = false;}
      if(KkFwyqgDQF == true){KkFwyqgDQF = false;}
      if(grEPZkrtXm == true){grEPZkrtXm = false;}
      if(tRYAwYHuLs == true){tRYAwYHuLs = false;}
      if(tgRbgCCWnI == true){tgRbgCCWnI = false;}
      if(tuuBGGyFzQ == true){tuuBGGyFzQ = false;}
      if(aeSFXsMEzY == true){aeSFXsMEzY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ALABPDUWGE
{ 
  void LIuZbLQzGU()
  { 
      bool IzOOeLIdKH = false;
      bool IaxGNWEnKP = false;
      bool qksuYKcTsQ = false;
      bool ieFDtBfgON = false;
      bool hcsjrZguTa = false;
      bool xuwNDXFSpU = false;
      bool hnksXdUtLM = false;
      bool pXYwhOrJDy = false;
      bool dhzRTnirzW = false;
      bool uNqtfsqzMO = false;
      bool EmiHjZVzfo = false;
      bool ewOqqAoSZi = false;
      bool uctoQcgdPn = false;
      bool Wrxnspyrhs = false;
      bool SiMJqzyzDf = false;
      bool EYYcTbrsqG = false;
      bool sqiqSlzZyA = false;
      bool BxkfQLQjyQ = false;
      bool egajjxTTUR = false;
      bool xEBaAazVqE = false;
      string CtSXCiNePl;
      string MDRFutgGKm;
      string TXomJcHCdW;
      string dMkHwYTTyL;
      string qKUHKpnufd;
      string jqxuQdEeNZ;
      string aLAsHASKJV;
      string aMHzuJDgbT;
      string oLVAllPppS;
      string UnGYjfJbzK;
      string WdlKCXiyzG;
      string ZWCtkOpzGV;
      string jbTpBmGiOP;
      string AbhRwLZKyO;
      string CRpjrykLnU;
      string pJVdZuKuJP;
      string QAijGxokxZ;
      string oeBqSSliyD;
      string BtutYpGDqB;
      string AdBhxCiGdt;
      if(CtSXCiNePl == WdlKCXiyzG){IzOOeLIdKH = true;}
      else if(WdlKCXiyzG == CtSXCiNePl){EmiHjZVzfo = true;}
      if(MDRFutgGKm == ZWCtkOpzGV){IaxGNWEnKP = true;}
      else if(ZWCtkOpzGV == MDRFutgGKm){ewOqqAoSZi = true;}
      if(TXomJcHCdW == jbTpBmGiOP){qksuYKcTsQ = true;}
      else if(jbTpBmGiOP == TXomJcHCdW){uctoQcgdPn = true;}
      if(dMkHwYTTyL == AbhRwLZKyO){ieFDtBfgON = true;}
      else if(AbhRwLZKyO == dMkHwYTTyL){Wrxnspyrhs = true;}
      if(qKUHKpnufd == CRpjrykLnU){hcsjrZguTa = true;}
      else if(CRpjrykLnU == qKUHKpnufd){SiMJqzyzDf = true;}
      if(jqxuQdEeNZ == pJVdZuKuJP){xuwNDXFSpU = true;}
      else if(pJVdZuKuJP == jqxuQdEeNZ){EYYcTbrsqG = true;}
      if(aLAsHASKJV == QAijGxokxZ){hnksXdUtLM = true;}
      else if(QAijGxokxZ == aLAsHASKJV){sqiqSlzZyA = true;}
      if(aMHzuJDgbT == oeBqSSliyD){pXYwhOrJDy = true;}
      if(oLVAllPppS == BtutYpGDqB){dhzRTnirzW = true;}
      if(UnGYjfJbzK == AdBhxCiGdt){uNqtfsqzMO = true;}
      while(oeBqSSliyD == aMHzuJDgbT){BxkfQLQjyQ = true;}
      while(BtutYpGDqB == BtutYpGDqB){egajjxTTUR = true;}
      while(AdBhxCiGdt == AdBhxCiGdt){xEBaAazVqE = true;}
      if(IzOOeLIdKH == true){IzOOeLIdKH = false;}
      if(IaxGNWEnKP == true){IaxGNWEnKP = false;}
      if(qksuYKcTsQ == true){qksuYKcTsQ = false;}
      if(ieFDtBfgON == true){ieFDtBfgON = false;}
      if(hcsjrZguTa == true){hcsjrZguTa = false;}
      if(xuwNDXFSpU == true){xuwNDXFSpU = false;}
      if(hnksXdUtLM == true){hnksXdUtLM = false;}
      if(pXYwhOrJDy == true){pXYwhOrJDy = false;}
      if(dhzRTnirzW == true){dhzRTnirzW = false;}
      if(uNqtfsqzMO == true){uNqtfsqzMO = false;}
      if(EmiHjZVzfo == true){EmiHjZVzfo = false;}
      if(ewOqqAoSZi == true){ewOqqAoSZi = false;}
      if(uctoQcgdPn == true){uctoQcgdPn = false;}
      if(Wrxnspyrhs == true){Wrxnspyrhs = false;}
      if(SiMJqzyzDf == true){SiMJqzyzDf = false;}
      if(EYYcTbrsqG == true){EYYcTbrsqG = false;}
      if(sqiqSlzZyA == true){sqiqSlzZyA = false;}
      if(BxkfQLQjyQ == true){BxkfQLQjyQ = false;}
      if(egajjxTTUR == true){egajjxTTUR = false;}
      if(xEBaAazVqE == true){xEBaAazVqE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DRHDPNUPZD
{ 
  void GNIphfpKBV()
  { 
      bool XlLxpTOAkR = false;
      bool ZgmRHZXUzq = false;
      bool ZExsMkoSCA = false;
      bool oiywEfsHVx = false;
      bool tCCHtcLCoP = false;
      bool JXEPiSnSjF = false;
      bool ewxjcpiqNa = false;
      bool fPzCwWCpzj = false;
      bool YlcmqQdhMl = false;
      bool raXPSyEReD = false;
      bool tUoOisYCTL = false;
      bool QyTzgrSJsL = false;
      bool LAdaiEriiy = false;
      bool SjKupEwOEy = false;
      bool qbNBVsHXiZ = false;
      bool etYSrsqNee = false;
      bool ApTUsfmXJb = false;
      bool wEFtTjmcFo = false;
      bool wUzITXLqDw = false;
      bool NhiYxBHrHo = false;
      string cnrcVMXVoY;
      string SlxkhfcPwc;
      string cBaGYFKwLu;
      string XKsnkbtaDF;
      string eZzKTRJism;
      string ONMKqaNkEP;
      string CbJsBIrJAG;
      string kCMpyDCPlH;
      string waCXgKxhwJ;
      string NIWmCDPFJL;
      string YzimCLBVMn;
      string YyzwTbYkMq;
      string KKNprbfYnu;
      string mwFaiwqPVU;
      string JbVHkPJZTa;
      string ddsSAOlrtZ;
      string fbhQAcrXNW;
      string jJOrginFEb;
      string SFEMRJDmZT;
      string JzUwogsEHI;
      if(cnrcVMXVoY == YzimCLBVMn){XlLxpTOAkR = true;}
      else if(YzimCLBVMn == cnrcVMXVoY){tUoOisYCTL = true;}
      if(SlxkhfcPwc == YyzwTbYkMq){ZgmRHZXUzq = true;}
      else if(YyzwTbYkMq == SlxkhfcPwc){QyTzgrSJsL = true;}
      if(cBaGYFKwLu == KKNprbfYnu){ZExsMkoSCA = true;}
      else if(KKNprbfYnu == cBaGYFKwLu){LAdaiEriiy = true;}
      if(XKsnkbtaDF == mwFaiwqPVU){oiywEfsHVx = true;}
      else if(mwFaiwqPVU == XKsnkbtaDF){SjKupEwOEy = true;}
      if(eZzKTRJism == JbVHkPJZTa){tCCHtcLCoP = true;}
      else if(JbVHkPJZTa == eZzKTRJism){qbNBVsHXiZ = true;}
      if(ONMKqaNkEP == ddsSAOlrtZ){JXEPiSnSjF = true;}
      else if(ddsSAOlrtZ == ONMKqaNkEP){etYSrsqNee = true;}
      if(CbJsBIrJAG == fbhQAcrXNW){ewxjcpiqNa = true;}
      else if(fbhQAcrXNW == CbJsBIrJAG){ApTUsfmXJb = true;}
      if(kCMpyDCPlH == jJOrginFEb){fPzCwWCpzj = true;}
      if(waCXgKxhwJ == SFEMRJDmZT){YlcmqQdhMl = true;}
      if(NIWmCDPFJL == JzUwogsEHI){raXPSyEReD = true;}
      while(jJOrginFEb == kCMpyDCPlH){wEFtTjmcFo = true;}
      while(SFEMRJDmZT == SFEMRJDmZT){wUzITXLqDw = true;}
      while(JzUwogsEHI == JzUwogsEHI){NhiYxBHrHo = true;}
      if(XlLxpTOAkR == true){XlLxpTOAkR = false;}
      if(ZgmRHZXUzq == true){ZgmRHZXUzq = false;}
      if(ZExsMkoSCA == true){ZExsMkoSCA = false;}
      if(oiywEfsHVx == true){oiywEfsHVx = false;}
      if(tCCHtcLCoP == true){tCCHtcLCoP = false;}
      if(JXEPiSnSjF == true){JXEPiSnSjF = false;}
      if(ewxjcpiqNa == true){ewxjcpiqNa = false;}
      if(fPzCwWCpzj == true){fPzCwWCpzj = false;}
      if(YlcmqQdhMl == true){YlcmqQdhMl = false;}
      if(raXPSyEReD == true){raXPSyEReD = false;}
      if(tUoOisYCTL == true){tUoOisYCTL = false;}
      if(QyTzgrSJsL == true){QyTzgrSJsL = false;}
      if(LAdaiEriiy == true){LAdaiEriiy = false;}
      if(SjKupEwOEy == true){SjKupEwOEy = false;}
      if(qbNBVsHXiZ == true){qbNBVsHXiZ = false;}
      if(etYSrsqNee == true){etYSrsqNee = false;}
      if(ApTUsfmXJb == true){ApTUsfmXJb = false;}
      if(wEFtTjmcFo == true){wEFtTjmcFo = false;}
      if(wUzITXLqDw == true){wUzITXLqDw = false;}
      if(NhiYxBHrHo == true){NhiYxBHrHo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YDKHHLSKGE
{ 
  void ZfrGTfpVAg()
  { 
      bool gMMGQcXbqC = false;
      bool GYHChybdsH = false;
      bool QKTYtDngVV = false;
      bool frtKRFQIoB = false;
      bool lbjbgQlGDe = false;
      bool hVNowVsnMM = false;
      bool npFVVOdwkc = false;
      bool gToqVnarqd = false;
      bool RhcqmKeEOu = false;
      bool McwcNuWOFS = false;
      bool loUaxOgVTI = false;
      bool tBxitFMOhL = false;
      bool jYhoPEXLdZ = false;
      bool RMlXqbMCsX = false;
      bool dIkFBLeNhH = false;
      bool hHftiNHfKs = false;
      bool qUqsqhOYqS = false;
      bool rKVJgambnE = false;
      bool YKdVrKfrod = false;
      bool TgqzgJQrOS = false;
      string VmqsscGHHR;
      string AMdBQtKdYI;
      string JzwREesToK;
      string hwYrHtuWsU;
      string UNgpEYFgoa;
      string VhIQMVpYnN;
      string ilSxiEmksV;
      string ymjEmuRFNf;
      string ZMdNoAnIfl;
      string EVhekiujGz;
      string kUmTbhxDcR;
      string DkLInWIEHi;
      string QeFHRbEFTE;
      string AhyNuEYKlH;
      string CjeNiSKZpN;
      string ZpcXiGPfBA;
      string cqjXQVlxMi;
      string xxSAffzqXy;
      string RdPFdJEadn;
      string osIkdKzHwN;
      if(VmqsscGHHR == kUmTbhxDcR){gMMGQcXbqC = true;}
      else if(kUmTbhxDcR == VmqsscGHHR){loUaxOgVTI = true;}
      if(AMdBQtKdYI == DkLInWIEHi){GYHChybdsH = true;}
      else if(DkLInWIEHi == AMdBQtKdYI){tBxitFMOhL = true;}
      if(JzwREesToK == QeFHRbEFTE){QKTYtDngVV = true;}
      else if(QeFHRbEFTE == JzwREesToK){jYhoPEXLdZ = true;}
      if(hwYrHtuWsU == AhyNuEYKlH){frtKRFQIoB = true;}
      else if(AhyNuEYKlH == hwYrHtuWsU){RMlXqbMCsX = true;}
      if(UNgpEYFgoa == CjeNiSKZpN){lbjbgQlGDe = true;}
      else if(CjeNiSKZpN == UNgpEYFgoa){dIkFBLeNhH = true;}
      if(VhIQMVpYnN == ZpcXiGPfBA){hVNowVsnMM = true;}
      else if(ZpcXiGPfBA == VhIQMVpYnN){hHftiNHfKs = true;}
      if(ilSxiEmksV == cqjXQVlxMi){npFVVOdwkc = true;}
      else if(cqjXQVlxMi == ilSxiEmksV){qUqsqhOYqS = true;}
      if(ymjEmuRFNf == xxSAffzqXy){gToqVnarqd = true;}
      if(ZMdNoAnIfl == RdPFdJEadn){RhcqmKeEOu = true;}
      if(EVhekiujGz == osIkdKzHwN){McwcNuWOFS = true;}
      while(xxSAffzqXy == ymjEmuRFNf){rKVJgambnE = true;}
      while(RdPFdJEadn == RdPFdJEadn){YKdVrKfrod = true;}
      while(osIkdKzHwN == osIkdKzHwN){TgqzgJQrOS = true;}
      if(gMMGQcXbqC == true){gMMGQcXbqC = false;}
      if(GYHChybdsH == true){GYHChybdsH = false;}
      if(QKTYtDngVV == true){QKTYtDngVV = false;}
      if(frtKRFQIoB == true){frtKRFQIoB = false;}
      if(lbjbgQlGDe == true){lbjbgQlGDe = false;}
      if(hVNowVsnMM == true){hVNowVsnMM = false;}
      if(npFVVOdwkc == true){npFVVOdwkc = false;}
      if(gToqVnarqd == true){gToqVnarqd = false;}
      if(RhcqmKeEOu == true){RhcqmKeEOu = false;}
      if(McwcNuWOFS == true){McwcNuWOFS = false;}
      if(loUaxOgVTI == true){loUaxOgVTI = false;}
      if(tBxitFMOhL == true){tBxitFMOhL = false;}
      if(jYhoPEXLdZ == true){jYhoPEXLdZ = false;}
      if(RMlXqbMCsX == true){RMlXqbMCsX = false;}
      if(dIkFBLeNhH == true){dIkFBLeNhH = false;}
      if(hHftiNHfKs == true){hHftiNHfKs = false;}
      if(qUqsqhOYqS == true){qUqsqhOYqS = false;}
      if(rKVJgambnE == true){rKVJgambnE = false;}
      if(YKdVrKfrod == true){YKdVrKfrod = false;}
      if(TgqzgJQrOS == true){TgqzgJQrOS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JJKUVCZOHC
{ 
  void nejYCcGSXG()
  { 
      bool pcSkghRMeS = false;
      bool iLaeyhNAcN = false;
      bool mRSxqZwynP = false;
      bool jeMggVAaTR = false;
      bool BkPDQYgaPE = false;
      bool SgZwQYJVtH = false;
      bool lSXPhDztxc = false;
      bool hlgLMCCPfR = false;
      bool sUhjwDEPPI = false;
      bool MdgLfhMzVM = false;
      bool ZlcmVgAOjN = false;
      bool WsobOQknTd = false;
      bool yidoQEEUed = false;
      bool pCtTrGrtNP = false;
      bool DpfCkSoFxP = false;
      bool wYfqNqHnWR = false;
      bool beiFXTzVjH = false;
      bool YpZDaICbDx = false;
      bool PzXPhQWDGB = false;
      bool zEXwnXGZeR = false;
      string ASfDItVSJt;
      string HofSgjEEIQ;
      string GkjooujaSU;
      string lBgydUFrWb;
      string nEsksodbpr;
      string wgzoePiqNN;
      string JtAnHFHgoM;
      string dMhgcBqzuz;
      string QHkZYFCrTN;
      string lNdIRsEEcn;
      string gwmcNjzRLc;
      string XiwOwCJZPB;
      string DPNaaQhYPi;
      string xlVGRTUHMn;
      string GjfppDRPMO;
      string ienakRiMCx;
      string BZBcfkMowb;
      string hBMbuSiWkX;
      string ySMBzSxuVz;
      string kHFOmfhDJE;
      if(ASfDItVSJt == gwmcNjzRLc){pcSkghRMeS = true;}
      else if(gwmcNjzRLc == ASfDItVSJt){ZlcmVgAOjN = true;}
      if(HofSgjEEIQ == XiwOwCJZPB){iLaeyhNAcN = true;}
      else if(XiwOwCJZPB == HofSgjEEIQ){WsobOQknTd = true;}
      if(GkjooujaSU == DPNaaQhYPi){mRSxqZwynP = true;}
      else if(DPNaaQhYPi == GkjooujaSU){yidoQEEUed = true;}
      if(lBgydUFrWb == xlVGRTUHMn){jeMggVAaTR = true;}
      else if(xlVGRTUHMn == lBgydUFrWb){pCtTrGrtNP = true;}
      if(nEsksodbpr == GjfppDRPMO){BkPDQYgaPE = true;}
      else if(GjfppDRPMO == nEsksodbpr){DpfCkSoFxP = true;}
      if(wgzoePiqNN == ienakRiMCx){SgZwQYJVtH = true;}
      else if(ienakRiMCx == wgzoePiqNN){wYfqNqHnWR = true;}
      if(JtAnHFHgoM == BZBcfkMowb){lSXPhDztxc = true;}
      else if(BZBcfkMowb == JtAnHFHgoM){beiFXTzVjH = true;}
      if(dMhgcBqzuz == hBMbuSiWkX){hlgLMCCPfR = true;}
      if(QHkZYFCrTN == ySMBzSxuVz){sUhjwDEPPI = true;}
      if(lNdIRsEEcn == kHFOmfhDJE){MdgLfhMzVM = true;}
      while(hBMbuSiWkX == dMhgcBqzuz){YpZDaICbDx = true;}
      while(ySMBzSxuVz == ySMBzSxuVz){PzXPhQWDGB = true;}
      while(kHFOmfhDJE == kHFOmfhDJE){zEXwnXGZeR = true;}
      if(pcSkghRMeS == true){pcSkghRMeS = false;}
      if(iLaeyhNAcN == true){iLaeyhNAcN = false;}
      if(mRSxqZwynP == true){mRSxqZwynP = false;}
      if(jeMggVAaTR == true){jeMggVAaTR = false;}
      if(BkPDQYgaPE == true){BkPDQYgaPE = false;}
      if(SgZwQYJVtH == true){SgZwQYJVtH = false;}
      if(lSXPhDztxc == true){lSXPhDztxc = false;}
      if(hlgLMCCPfR == true){hlgLMCCPfR = false;}
      if(sUhjwDEPPI == true){sUhjwDEPPI = false;}
      if(MdgLfhMzVM == true){MdgLfhMzVM = false;}
      if(ZlcmVgAOjN == true){ZlcmVgAOjN = false;}
      if(WsobOQknTd == true){WsobOQknTd = false;}
      if(yidoQEEUed == true){yidoQEEUed = false;}
      if(pCtTrGrtNP == true){pCtTrGrtNP = false;}
      if(DpfCkSoFxP == true){DpfCkSoFxP = false;}
      if(wYfqNqHnWR == true){wYfqNqHnWR = false;}
      if(beiFXTzVjH == true){beiFXTzVjH = false;}
      if(YpZDaICbDx == true){YpZDaICbDx = false;}
      if(PzXPhQWDGB == true){PzXPhQWDGB = false;}
      if(zEXwnXGZeR == true){zEXwnXGZeR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KWPYFQOEFE
{ 
  void xJLWLrpgMQ()
  { 
      bool UitixNtYbt = false;
      bool xbaZayyInA = false;
      bool CpTHZSihie = false;
      bool pbOYlKRAyu = false;
      bool TkZBnUeUee = false;
      bool PDkoMePlId = false;
      bool eLoxDVNCmP = false;
      bool fxJsfQPRSE = false;
      bool mNDDOmpZLG = false;
      bool ufqTPIwbyS = false;
      bool HchOzRsqIu = false;
      bool OxSEqRHkhP = false;
      bool emqgUAGpdX = false;
      bool UnTAxKfoEw = false;
      bool szRPqyMmcx = false;
      bool AKthnTkAtz = false;
      bool LDNjaacSHf = false;
      bool lSgkWeVboW = false;
      bool mSMfXKtkLc = false;
      bool ZeuEkplgnP = false;
      string HOxIpuLSTE;
      string BLqgceQVJc;
      string DQMeYYrcKV;
      string qwRVceaAYW;
      string eHiaVRHmzT;
      string YVJuHpCSjR;
      string ChHxMFtUEy;
      string DPxmxwglIG;
      string QFcqxVmVOl;
      string cIQHTwzlNP;
      string WmhBPJXWyK;
      string IPJcBxFQAq;
      string SYGRUtzpSA;
      string xuXsjdWbbm;
      string xPWDcMzmGW;
      string qikVxyfPgV;
      string JhDxNNrPsW;
      string ZcnMtCBDnH;
      string tLjuINKBwk;
      string xGtFcOLZoP;
      if(HOxIpuLSTE == WmhBPJXWyK){UitixNtYbt = true;}
      else if(WmhBPJXWyK == HOxIpuLSTE){HchOzRsqIu = true;}
      if(BLqgceQVJc == IPJcBxFQAq){xbaZayyInA = true;}
      else if(IPJcBxFQAq == BLqgceQVJc){OxSEqRHkhP = true;}
      if(DQMeYYrcKV == SYGRUtzpSA){CpTHZSihie = true;}
      else if(SYGRUtzpSA == DQMeYYrcKV){emqgUAGpdX = true;}
      if(qwRVceaAYW == xuXsjdWbbm){pbOYlKRAyu = true;}
      else if(xuXsjdWbbm == qwRVceaAYW){UnTAxKfoEw = true;}
      if(eHiaVRHmzT == xPWDcMzmGW){TkZBnUeUee = true;}
      else if(xPWDcMzmGW == eHiaVRHmzT){szRPqyMmcx = true;}
      if(YVJuHpCSjR == qikVxyfPgV){PDkoMePlId = true;}
      else if(qikVxyfPgV == YVJuHpCSjR){AKthnTkAtz = true;}
      if(ChHxMFtUEy == JhDxNNrPsW){eLoxDVNCmP = true;}
      else if(JhDxNNrPsW == ChHxMFtUEy){LDNjaacSHf = true;}
      if(DPxmxwglIG == ZcnMtCBDnH){fxJsfQPRSE = true;}
      if(QFcqxVmVOl == tLjuINKBwk){mNDDOmpZLG = true;}
      if(cIQHTwzlNP == xGtFcOLZoP){ufqTPIwbyS = true;}
      while(ZcnMtCBDnH == DPxmxwglIG){lSgkWeVboW = true;}
      while(tLjuINKBwk == tLjuINKBwk){mSMfXKtkLc = true;}
      while(xGtFcOLZoP == xGtFcOLZoP){ZeuEkplgnP = true;}
      if(UitixNtYbt == true){UitixNtYbt = false;}
      if(xbaZayyInA == true){xbaZayyInA = false;}
      if(CpTHZSihie == true){CpTHZSihie = false;}
      if(pbOYlKRAyu == true){pbOYlKRAyu = false;}
      if(TkZBnUeUee == true){TkZBnUeUee = false;}
      if(PDkoMePlId == true){PDkoMePlId = false;}
      if(eLoxDVNCmP == true){eLoxDVNCmP = false;}
      if(fxJsfQPRSE == true){fxJsfQPRSE = false;}
      if(mNDDOmpZLG == true){mNDDOmpZLG = false;}
      if(ufqTPIwbyS == true){ufqTPIwbyS = false;}
      if(HchOzRsqIu == true){HchOzRsqIu = false;}
      if(OxSEqRHkhP == true){OxSEqRHkhP = false;}
      if(emqgUAGpdX == true){emqgUAGpdX = false;}
      if(UnTAxKfoEw == true){UnTAxKfoEw = false;}
      if(szRPqyMmcx == true){szRPqyMmcx = false;}
      if(AKthnTkAtz == true){AKthnTkAtz = false;}
      if(LDNjaacSHf == true){LDNjaacSHf = false;}
      if(lSgkWeVboW == true){lSgkWeVboW = false;}
      if(mSMfXKtkLc == true){mSMfXKtkLc = false;}
      if(ZeuEkplgnP == true){ZeuEkplgnP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BUUJKUCUVX
{ 
  void kOctlpGXjd()
  { 
      bool gnjupEhggn = false;
      bool AwDyYYggmd = false;
      bool pTLuizcMYj = false;
      bool ODCPaePlCT = false;
      bool UNFnWnzGZD = false;
      bool TyEwlNboMp = false;
      bool bVIwYwsnWt = false;
      bool JtdTJcOXXt = false;
      bool zVmUQPzFdM = false;
      bool CaZLrzEIOa = false;
      bool tLietYUkmI = false;
      bool yERRpFhmfJ = false;
      bool wnJJqiURaJ = false;
      bool XFJxzmmHar = false;
      bool uNSVOyJHVm = false;
      bool QRcFdGCYnL = false;
      bool DCKdjruTRD = false;
      bool RaLmNiUmus = false;
      bool ZNwmsGcDTs = false;
      bool kNTPnrDokV = false;
      string aqiyPFRWiC;
      string YUhBYrhrpa;
      string VqLptKwLpy;
      string cKpIOdUqzG;
      string kcYpxclqxL;
      string TDtNWifrDE;
      string JGgjYOdYlu;
      string XpriprSUsR;
      string YFNeeZPcle;
      string ybnuxewnQh;
      string yMECncLKXd;
      string QKzkfErCEz;
      string zBlHwuCxlK;
      string weEKTLAKqC;
      string OEFIOncCPs;
      string lsiRiwawGr;
      string ZOYMglGnRT;
      string DgLBjtwdrI;
      string SAgrYCulbW;
      string kDEycAerac;
      if(aqiyPFRWiC == yMECncLKXd){gnjupEhggn = true;}
      else if(yMECncLKXd == aqiyPFRWiC){tLietYUkmI = true;}
      if(YUhBYrhrpa == QKzkfErCEz){AwDyYYggmd = true;}
      else if(QKzkfErCEz == YUhBYrhrpa){yERRpFhmfJ = true;}
      if(VqLptKwLpy == zBlHwuCxlK){pTLuizcMYj = true;}
      else if(zBlHwuCxlK == VqLptKwLpy){wnJJqiURaJ = true;}
      if(cKpIOdUqzG == weEKTLAKqC){ODCPaePlCT = true;}
      else if(weEKTLAKqC == cKpIOdUqzG){XFJxzmmHar = true;}
      if(kcYpxclqxL == OEFIOncCPs){UNFnWnzGZD = true;}
      else if(OEFIOncCPs == kcYpxclqxL){uNSVOyJHVm = true;}
      if(TDtNWifrDE == lsiRiwawGr){TyEwlNboMp = true;}
      else if(lsiRiwawGr == TDtNWifrDE){QRcFdGCYnL = true;}
      if(JGgjYOdYlu == ZOYMglGnRT){bVIwYwsnWt = true;}
      else if(ZOYMglGnRT == JGgjYOdYlu){DCKdjruTRD = true;}
      if(XpriprSUsR == DgLBjtwdrI){JtdTJcOXXt = true;}
      if(YFNeeZPcle == SAgrYCulbW){zVmUQPzFdM = true;}
      if(ybnuxewnQh == kDEycAerac){CaZLrzEIOa = true;}
      while(DgLBjtwdrI == XpriprSUsR){RaLmNiUmus = true;}
      while(SAgrYCulbW == SAgrYCulbW){ZNwmsGcDTs = true;}
      while(kDEycAerac == kDEycAerac){kNTPnrDokV = true;}
      if(gnjupEhggn == true){gnjupEhggn = false;}
      if(AwDyYYggmd == true){AwDyYYggmd = false;}
      if(pTLuizcMYj == true){pTLuizcMYj = false;}
      if(ODCPaePlCT == true){ODCPaePlCT = false;}
      if(UNFnWnzGZD == true){UNFnWnzGZD = false;}
      if(TyEwlNboMp == true){TyEwlNboMp = false;}
      if(bVIwYwsnWt == true){bVIwYwsnWt = false;}
      if(JtdTJcOXXt == true){JtdTJcOXXt = false;}
      if(zVmUQPzFdM == true){zVmUQPzFdM = false;}
      if(CaZLrzEIOa == true){CaZLrzEIOa = false;}
      if(tLietYUkmI == true){tLietYUkmI = false;}
      if(yERRpFhmfJ == true){yERRpFhmfJ = false;}
      if(wnJJqiURaJ == true){wnJJqiURaJ = false;}
      if(XFJxzmmHar == true){XFJxzmmHar = false;}
      if(uNSVOyJHVm == true){uNSVOyJHVm = false;}
      if(QRcFdGCYnL == true){QRcFdGCYnL = false;}
      if(DCKdjruTRD == true){DCKdjruTRD = false;}
      if(RaLmNiUmus == true){RaLmNiUmus = false;}
      if(ZNwmsGcDTs == true){ZNwmsGcDTs = false;}
      if(kNTPnrDokV == true){kNTPnrDokV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WVYBQBPHUX
{ 
  void QVTIuiCfiW()
  { 
      bool NAdaElzwRb = false;
      bool fIiGfWASYV = false;
      bool NCblAQzKBw = false;
      bool tDiKyqNSKs = false;
      bool CxHkhrQAAy = false;
      bool ayzfFLXram = false;
      bool mouVgbZXIn = false;
      bool IhIfTPtqDI = false;
      bool zyJCVwDDFl = false;
      bool TVqWFNClDF = false;
      bool RrrLoroSMo = false;
      bool QgnSmoerAk = false;
      bool XVSVUmqkaF = false;
      bool NHmxpGGyNc = false;
      bool GkqPUmgYjP = false;
      bool iJlShwZVpB = false;
      bool BErGbJspbf = false;
      bool ifeWdmeDBh = false;
      bool FRBLWEUTPt = false;
      bool gkHLaCrjnL = false;
      string lIcfBMintc;
      string rDlIMyiOpG;
      string XeQfUFDEhW;
      string wPmlEagMUH;
      string FrtQcgFWHX;
      string FKzeuGrwLw;
      string JeFWfbPAEk;
      string RVthAekADn;
      string AfwJRlQIpy;
      string ijBXyalXjA;
      string QESVFiPQdQ;
      string VrsWwchuEt;
      string LHKGChUViY;
      string rNPCWuMaEi;
      string VzdZbppdbU;
      string sqSpoJtMSX;
      string NthEXIbpAB;
      string QGqVXMckdL;
      string qqsOfBtZNN;
      string AzHgUbRYBT;
      if(lIcfBMintc == QESVFiPQdQ){NAdaElzwRb = true;}
      else if(QESVFiPQdQ == lIcfBMintc){RrrLoroSMo = true;}
      if(rDlIMyiOpG == VrsWwchuEt){fIiGfWASYV = true;}
      else if(VrsWwchuEt == rDlIMyiOpG){QgnSmoerAk = true;}
      if(XeQfUFDEhW == LHKGChUViY){NCblAQzKBw = true;}
      else if(LHKGChUViY == XeQfUFDEhW){XVSVUmqkaF = true;}
      if(wPmlEagMUH == rNPCWuMaEi){tDiKyqNSKs = true;}
      else if(rNPCWuMaEi == wPmlEagMUH){NHmxpGGyNc = true;}
      if(FrtQcgFWHX == VzdZbppdbU){CxHkhrQAAy = true;}
      else if(VzdZbppdbU == FrtQcgFWHX){GkqPUmgYjP = true;}
      if(FKzeuGrwLw == sqSpoJtMSX){ayzfFLXram = true;}
      else if(sqSpoJtMSX == FKzeuGrwLw){iJlShwZVpB = true;}
      if(JeFWfbPAEk == NthEXIbpAB){mouVgbZXIn = true;}
      else if(NthEXIbpAB == JeFWfbPAEk){BErGbJspbf = true;}
      if(RVthAekADn == QGqVXMckdL){IhIfTPtqDI = true;}
      if(AfwJRlQIpy == qqsOfBtZNN){zyJCVwDDFl = true;}
      if(ijBXyalXjA == AzHgUbRYBT){TVqWFNClDF = true;}
      while(QGqVXMckdL == RVthAekADn){ifeWdmeDBh = true;}
      while(qqsOfBtZNN == qqsOfBtZNN){FRBLWEUTPt = true;}
      while(AzHgUbRYBT == AzHgUbRYBT){gkHLaCrjnL = true;}
      if(NAdaElzwRb == true){NAdaElzwRb = false;}
      if(fIiGfWASYV == true){fIiGfWASYV = false;}
      if(NCblAQzKBw == true){NCblAQzKBw = false;}
      if(tDiKyqNSKs == true){tDiKyqNSKs = false;}
      if(CxHkhrQAAy == true){CxHkhrQAAy = false;}
      if(ayzfFLXram == true){ayzfFLXram = false;}
      if(mouVgbZXIn == true){mouVgbZXIn = false;}
      if(IhIfTPtqDI == true){IhIfTPtqDI = false;}
      if(zyJCVwDDFl == true){zyJCVwDDFl = false;}
      if(TVqWFNClDF == true){TVqWFNClDF = false;}
      if(RrrLoroSMo == true){RrrLoroSMo = false;}
      if(QgnSmoerAk == true){QgnSmoerAk = false;}
      if(XVSVUmqkaF == true){XVSVUmqkaF = false;}
      if(NHmxpGGyNc == true){NHmxpGGyNc = false;}
      if(GkqPUmgYjP == true){GkqPUmgYjP = false;}
      if(iJlShwZVpB == true){iJlShwZVpB = false;}
      if(BErGbJspbf == true){BErGbJspbf = false;}
      if(ifeWdmeDBh == true){ifeWdmeDBh = false;}
      if(FRBLWEUTPt == true){FRBLWEUTPt = false;}
      if(gkHLaCrjnL == true){gkHLaCrjnL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GMIQJGJHYZ
{ 
  void RYgIuULtrB()
  { 
      bool oiPdftJqfW = false;
      bool shXBoaxexH = false;
      bool bDdDDeBwKj = false;
      bool bfIKsNlpRw = false;
      bool DbmFZVwCrW = false;
      bool kQhnEkELZA = false;
      bool sMfwuMZMHb = false;
      bool oGMADAQYcg = false;
      bool iyEnyLxTGH = false;
      bool JZQRCqwqJN = false;
      bool uitPgdDgjE = false;
      bool UehrRtIqxj = false;
      bool OGGzSOpuyM = false;
      bool DYOPlzEnGT = false;
      bool HPiCmdqXzI = false;
      bool hEsZyoctxS = false;
      bool nHiWAuPSGR = false;
      bool oTkdbzXEMn = false;
      bool WSuoezfoQx = false;
      bool VKqnfAgLBq = false;
      string UdScUWGNBk;
      string CjAQbRLdNh;
      string KGBbWTQuXc;
      string pcHrFeLnlU;
      string BaFOONSwce;
      string mPzJFObqFA;
      string FKpXuYcILx;
      string GWqsfjAlMJ;
      string BUSrpZdxlq;
      string CTikPqjgTo;
      string kJjeYPYFcU;
      string OpdwzjrxhU;
      string ufVUulnGco;
      string ASSWYqjmTZ;
      string BXTRcMplke;
      string ymzztFmPjl;
      string bScnUuWGWH;
      string zEdISWLEri;
      string wBUxpMSTcT;
      string ETDgxiufwg;
      if(UdScUWGNBk == kJjeYPYFcU){oiPdftJqfW = true;}
      else if(kJjeYPYFcU == UdScUWGNBk){uitPgdDgjE = true;}
      if(CjAQbRLdNh == OpdwzjrxhU){shXBoaxexH = true;}
      else if(OpdwzjrxhU == CjAQbRLdNh){UehrRtIqxj = true;}
      if(KGBbWTQuXc == ufVUulnGco){bDdDDeBwKj = true;}
      else if(ufVUulnGco == KGBbWTQuXc){OGGzSOpuyM = true;}
      if(pcHrFeLnlU == ASSWYqjmTZ){bfIKsNlpRw = true;}
      else if(ASSWYqjmTZ == pcHrFeLnlU){DYOPlzEnGT = true;}
      if(BaFOONSwce == BXTRcMplke){DbmFZVwCrW = true;}
      else if(BXTRcMplke == BaFOONSwce){HPiCmdqXzI = true;}
      if(mPzJFObqFA == ymzztFmPjl){kQhnEkELZA = true;}
      else if(ymzztFmPjl == mPzJFObqFA){hEsZyoctxS = true;}
      if(FKpXuYcILx == bScnUuWGWH){sMfwuMZMHb = true;}
      else if(bScnUuWGWH == FKpXuYcILx){nHiWAuPSGR = true;}
      if(GWqsfjAlMJ == zEdISWLEri){oGMADAQYcg = true;}
      if(BUSrpZdxlq == wBUxpMSTcT){iyEnyLxTGH = true;}
      if(CTikPqjgTo == ETDgxiufwg){JZQRCqwqJN = true;}
      while(zEdISWLEri == GWqsfjAlMJ){oTkdbzXEMn = true;}
      while(wBUxpMSTcT == wBUxpMSTcT){WSuoezfoQx = true;}
      while(ETDgxiufwg == ETDgxiufwg){VKqnfAgLBq = true;}
      if(oiPdftJqfW == true){oiPdftJqfW = false;}
      if(shXBoaxexH == true){shXBoaxexH = false;}
      if(bDdDDeBwKj == true){bDdDDeBwKj = false;}
      if(bfIKsNlpRw == true){bfIKsNlpRw = false;}
      if(DbmFZVwCrW == true){DbmFZVwCrW = false;}
      if(kQhnEkELZA == true){kQhnEkELZA = false;}
      if(sMfwuMZMHb == true){sMfwuMZMHb = false;}
      if(oGMADAQYcg == true){oGMADAQYcg = false;}
      if(iyEnyLxTGH == true){iyEnyLxTGH = false;}
      if(JZQRCqwqJN == true){JZQRCqwqJN = false;}
      if(uitPgdDgjE == true){uitPgdDgjE = false;}
      if(UehrRtIqxj == true){UehrRtIqxj = false;}
      if(OGGzSOpuyM == true){OGGzSOpuyM = false;}
      if(DYOPlzEnGT == true){DYOPlzEnGT = false;}
      if(HPiCmdqXzI == true){HPiCmdqXzI = false;}
      if(hEsZyoctxS == true){hEsZyoctxS = false;}
      if(nHiWAuPSGR == true){nHiWAuPSGR = false;}
      if(oTkdbzXEMn == true){oTkdbzXEMn = false;}
      if(WSuoezfoQx == true){WSuoezfoQx = false;}
      if(VKqnfAgLBq == true){VKqnfAgLBq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SPIVKDJQAO
{ 
  void XmiQJyKjWb()
  { 
      bool NPGYXhcfXx = false;
      bool YyZyJXIbRH = false;
      bool yeildzlguM = false;
      bool ZEmdNYTGld = false;
      bool tPaSBardIH = false;
      bool NCqmjhfUtX = false;
      bool wukKXTKujj = false;
      bool DConNhDQjD = false;
      bool GIYmzWMAte = false;
      bool rzLOgyePth = false;
      bool PxsXEKMDYB = false;
      bool dPkqQnVxLB = false;
      bool GJBFrEpaGO = false;
      bool DnWCmJPBin = false;
      bool JJbrAcOUys = false;
      bool bgEsaGunfz = false;
      bool TlxJypsiDG = false;
      bool YUOXqxhIEO = false;
      bool pVbMmVjcag = false;
      bool NaUiTWLRtJ = false;
      string IBFsHnwjXB;
      string hMqEQcFmku;
      string OxJtRBfkDy;
      string AGkblTrTrW;
      string YXjCBQFwol;
      string crBJWLqKaF;
      string ILfYBbbORw;
      string kltOWqNGrB;
      string wjuQUHEaFa;
      string cgrlOMqKAZ;
      string npdsBqxmme;
      string xjRZJXPOEs;
      string WBJqTDsIAJ;
      string zCGSNFFBPc;
      string KRmZcrOScp;
      string wbGGCmgmZx;
      string ynldetdzMD;
      string SOzaiFNiNa;
      string nZfJMWwzPa;
      string YSbReVeJui;
      if(IBFsHnwjXB == npdsBqxmme){NPGYXhcfXx = true;}
      else if(npdsBqxmme == IBFsHnwjXB){PxsXEKMDYB = true;}
      if(hMqEQcFmku == xjRZJXPOEs){YyZyJXIbRH = true;}
      else if(xjRZJXPOEs == hMqEQcFmku){dPkqQnVxLB = true;}
      if(OxJtRBfkDy == WBJqTDsIAJ){yeildzlguM = true;}
      else if(WBJqTDsIAJ == OxJtRBfkDy){GJBFrEpaGO = true;}
      if(AGkblTrTrW == zCGSNFFBPc){ZEmdNYTGld = true;}
      else if(zCGSNFFBPc == AGkblTrTrW){DnWCmJPBin = true;}
      if(YXjCBQFwol == KRmZcrOScp){tPaSBardIH = true;}
      else if(KRmZcrOScp == YXjCBQFwol){JJbrAcOUys = true;}
      if(crBJWLqKaF == wbGGCmgmZx){NCqmjhfUtX = true;}
      else if(wbGGCmgmZx == crBJWLqKaF){bgEsaGunfz = true;}
      if(ILfYBbbORw == ynldetdzMD){wukKXTKujj = true;}
      else if(ynldetdzMD == ILfYBbbORw){TlxJypsiDG = true;}
      if(kltOWqNGrB == SOzaiFNiNa){DConNhDQjD = true;}
      if(wjuQUHEaFa == nZfJMWwzPa){GIYmzWMAte = true;}
      if(cgrlOMqKAZ == YSbReVeJui){rzLOgyePth = true;}
      while(SOzaiFNiNa == kltOWqNGrB){YUOXqxhIEO = true;}
      while(nZfJMWwzPa == nZfJMWwzPa){pVbMmVjcag = true;}
      while(YSbReVeJui == YSbReVeJui){NaUiTWLRtJ = true;}
      if(NPGYXhcfXx == true){NPGYXhcfXx = false;}
      if(YyZyJXIbRH == true){YyZyJXIbRH = false;}
      if(yeildzlguM == true){yeildzlguM = false;}
      if(ZEmdNYTGld == true){ZEmdNYTGld = false;}
      if(tPaSBardIH == true){tPaSBardIH = false;}
      if(NCqmjhfUtX == true){NCqmjhfUtX = false;}
      if(wukKXTKujj == true){wukKXTKujj = false;}
      if(DConNhDQjD == true){DConNhDQjD = false;}
      if(GIYmzWMAte == true){GIYmzWMAte = false;}
      if(rzLOgyePth == true){rzLOgyePth = false;}
      if(PxsXEKMDYB == true){PxsXEKMDYB = false;}
      if(dPkqQnVxLB == true){dPkqQnVxLB = false;}
      if(GJBFrEpaGO == true){GJBFrEpaGO = false;}
      if(DnWCmJPBin == true){DnWCmJPBin = false;}
      if(JJbrAcOUys == true){JJbrAcOUys = false;}
      if(bgEsaGunfz == true){bgEsaGunfz = false;}
      if(TlxJypsiDG == true){TlxJypsiDG = false;}
      if(YUOXqxhIEO == true){YUOXqxhIEO = false;}
      if(pVbMmVjcag == true){pVbMmVjcag = false;}
      if(NaUiTWLRtJ == true){NaUiTWLRtJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FHHGVCSOPB
{ 
  void fYuLmlCRsa()
  { 
      bool EUdgGkxpCS = false;
      bool oHopcgtXWF = false;
      bool WgYIOqyEDL = false;
      bool JPxsxHwyXc = false;
      bool eQJKFIwDUd = false;
      bool wtSQRXuUSP = false;
      bool mrlqJYKusU = false;
      bool jwzsZFWODF = false;
      bool uujZOOxfaZ = false;
      bool MbfIpldRBg = false;
      bool yAJztAuYpM = false;
      bool AgRMUrIMbt = false;
      bool adUTIIQpDm = false;
      bool aEMVHtkjeO = false;
      bool SXpOYeJTny = false;
      bool dRpGFTeppl = false;
      bool iFVCkuUuEZ = false;
      bool GYgMaDnGtd = false;
      bool yxCEJJOFQm = false;
      bool OussfNBmdc = false;
      string rVlsheqhqY;
      string aYwIVmQPVS;
      string LCSthXNgOc;
      string WokKzMojql;
      string RaCadQjgCD;
      string uoBeupDqKJ;
      string QJSOBknlJJ;
      string xgXjAkzqQR;
      string nfeKghmGOI;
      string JxZgUIHmZr;
      string cxXrGOQRdK;
      string pLarVkeHhT;
      string xhWAzzHqOr;
      string cMRXopIlES;
      string QVbDSxWgLi;
      string dAFFuuaWrG;
      string HZClhdsCDe;
      string crDPCbFShC;
      string cZeeObGMct;
      string PksyLqSpVo;
      if(rVlsheqhqY == cxXrGOQRdK){EUdgGkxpCS = true;}
      else if(cxXrGOQRdK == rVlsheqhqY){yAJztAuYpM = true;}
      if(aYwIVmQPVS == pLarVkeHhT){oHopcgtXWF = true;}
      else if(pLarVkeHhT == aYwIVmQPVS){AgRMUrIMbt = true;}
      if(LCSthXNgOc == xhWAzzHqOr){WgYIOqyEDL = true;}
      else if(xhWAzzHqOr == LCSthXNgOc){adUTIIQpDm = true;}
      if(WokKzMojql == cMRXopIlES){JPxsxHwyXc = true;}
      else if(cMRXopIlES == WokKzMojql){aEMVHtkjeO = true;}
      if(RaCadQjgCD == QVbDSxWgLi){eQJKFIwDUd = true;}
      else if(QVbDSxWgLi == RaCadQjgCD){SXpOYeJTny = true;}
      if(uoBeupDqKJ == dAFFuuaWrG){wtSQRXuUSP = true;}
      else if(dAFFuuaWrG == uoBeupDqKJ){dRpGFTeppl = true;}
      if(QJSOBknlJJ == HZClhdsCDe){mrlqJYKusU = true;}
      else if(HZClhdsCDe == QJSOBknlJJ){iFVCkuUuEZ = true;}
      if(xgXjAkzqQR == crDPCbFShC){jwzsZFWODF = true;}
      if(nfeKghmGOI == cZeeObGMct){uujZOOxfaZ = true;}
      if(JxZgUIHmZr == PksyLqSpVo){MbfIpldRBg = true;}
      while(crDPCbFShC == xgXjAkzqQR){GYgMaDnGtd = true;}
      while(cZeeObGMct == cZeeObGMct){yxCEJJOFQm = true;}
      while(PksyLqSpVo == PksyLqSpVo){OussfNBmdc = true;}
      if(EUdgGkxpCS == true){EUdgGkxpCS = false;}
      if(oHopcgtXWF == true){oHopcgtXWF = false;}
      if(WgYIOqyEDL == true){WgYIOqyEDL = false;}
      if(JPxsxHwyXc == true){JPxsxHwyXc = false;}
      if(eQJKFIwDUd == true){eQJKFIwDUd = false;}
      if(wtSQRXuUSP == true){wtSQRXuUSP = false;}
      if(mrlqJYKusU == true){mrlqJYKusU = false;}
      if(jwzsZFWODF == true){jwzsZFWODF = false;}
      if(uujZOOxfaZ == true){uujZOOxfaZ = false;}
      if(MbfIpldRBg == true){MbfIpldRBg = false;}
      if(yAJztAuYpM == true){yAJztAuYpM = false;}
      if(AgRMUrIMbt == true){AgRMUrIMbt = false;}
      if(adUTIIQpDm == true){adUTIIQpDm = false;}
      if(aEMVHtkjeO == true){aEMVHtkjeO = false;}
      if(SXpOYeJTny == true){SXpOYeJTny = false;}
      if(dRpGFTeppl == true){dRpGFTeppl = false;}
      if(iFVCkuUuEZ == true){iFVCkuUuEZ = false;}
      if(GYgMaDnGtd == true){GYgMaDnGtd = false;}
      if(yxCEJJOFQm == true){yxCEJJOFQm = false;}
      if(OussfNBmdc == true){OussfNBmdc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PPLQWKOPNC
{ 
  void hJWyhhagri()
  { 
      bool SuERjaqmma = false;
      bool SPzSfAnYeK = false;
      bool yyKYwGRsqg = false;
      bool NMJSVxPEdD = false;
      bool KzRORqptCM = false;
      bool yUOQkTjfUc = false;
      bool JyuGNGGgwi = false;
      bool kitaAygwGF = false;
      bool PWqehrxrhB = false;
      bool MiiAtLDKAL = false;
      bool kJySaPamQl = false;
      bool mnYPNmHPYV = false;
      bool IOyuWBAsgn = false;
      bool uVutUGYXER = false;
      bool QKawNXKSmH = false;
      bool EnkeCVLDwY = false;
      bool PgGbpQsduH = false;
      bool OiLGEymBgy = false;
      bool qgGYjHjQry = false;
      bool tUbeCjDzFx = false;
      string jayqTskqaB;
      string UohJiyIRoe;
      string eLZbfRoAnD;
      string jOhgGlprmY;
      string oFCpdndZOU;
      string SiyjHXAVKB;
      string DkDXRFGACw;
      string IPePoYJjxq;
      string mOlTkBPyYh;
      string lThkUECeXY;
      string gdWRMCDhti;
      string OPYTOozilQ;
      string oIbUKnhstk;
      string VdMYJJrTHh;
      string xhDpSVuOWf;
      string FTrHiYBBGY;
      string UKmJNjDAJE;
      string webETHFlBn;
      string rTWOeClFok;
      string HpNhMltsbi;
      if(jayqTskqaB == gdWRMCDhti){SuERjaqmma = true;}
      else if(gdWRMCDhti == jayqTskqaB){kJySaPamQl = true;}
      if(UohJiyIRoe == OPYTOozilQ){SPzSfAnYeK = true;}
      else if(OPYTOozilQ == UohJiyIRoe){mnYPNmHPYV = true;}
      if(eLZbfRoAnD == oIbUKnhstk){yyKYwGRsqg = true;}
      else if(oIbUKnhstk == eLZbfRoAnD){IOyuWBAsgn = true;}
      if(jOhgGlprmY == VdMYJJrTHh){NMJSVxPEdD = true;}
      else if(VdMYJJrTHh == jOhgGlprmY){uVutUGYXER = true;}
      if(oFCpdndZOU == xhDpSVuOWf){KzRORqptCM = true;}
      else if(xhDpSVuOWf == oFCpdndZOU){QKawNXKSmH = true;}
      if(SiyjHXAVKB == FTrHiYBBGY){yUOQkTjfUc = true;}
      else if(FTrHiYBBGY == SiyjHXAVKB){EnkeCVLDwY = true;}
      if(DkDXRFGACw == UKmJNjDAJE){JyuGNGGgwi = true;}
      else if(UKmJNjDAJE == DkDXRFGACw){PgGbpQsduH = true;}
      if(IPePoYJjxq == webETHFlBn){kitaAygwGF = true;}
      if(mOlTkBPyYh == rTWOeClFok){PWqehrxrhB = true;}
      if(lThkUECeXY == HpNhMltsbi){MiiAtLDKAL = true;}
      while(webETHFlBn == IPePoYJjxq){OiLGEymBgy = true;}
      while(rTWOeClFok == rTWOeClFok){qgGYjHjQry = true;}
      while(HpNhMltsbi == HpNhMltsbi){tUbeCjDzFx = true;}
      if(SuERjaqmma == true){SuERjaqmma = false;}
      if(SPzSfAnYeK == true){SPzSfAnYeK = false;}
      if(yyKYwGRsqg == true){yyKYwGRsqg = false;}
      if(NMJSVxPEdD == true){NMJSVxPEdD = false;}
      if(KzRORqptCM == true){KzRORqptCM = false;}
      if(yUOQkTjfUc == true){yUOQkTjfUc = false;}
      if(JyuGNGGgwi == true){JyuGNGGgwi = false;}
      if(kitaAygwGF == true){kitaAygwGF = false;}
      if(PWqehrxrhB == true){PWqehrxrhB = false;}
      if(MiiAtLDKAL == true){MiiAtLDKAL = false;}
      if(kJySaPamQl == true){kJySaPamQl = false;}
      if(mnYPNmHPYV == true){mnYPNmHPYV = false;}
      if(IOyuWBAsgn == true){IOyuWBAsgn = false;}
      if(uVutUGYXER == true){uVutUGYXER = false;}
      if(QKawNXKSmH == true){QKawNXKSmH = false;}
      if(EnkeCVLDwY == true){EnkeCVLDwY = false;}
      if(PgGbpQsduH == true){PgGbpQsduH = false;}
      if(OiLGEymBgy == true){OiLGEymBgy = false;}
      if(qgGYjHjQry == true){qgGYjHjQry = false;}
      if(tUbeCjDzFx == true){tUbeCjDzFx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWZDPJYBIE
{ 
  void UsdYdhCJZn()
  { 
      bool yQBrJiLtdN = false;
      bool WzEKJEYGVC = false;
      bool MAcBkqgzic = false;
      bool TMQrVOsmaq = false;
      bool MnNAqDNknS = false;
      bool UKerWxmzGS = false;
      bool BLKAtJiMnt = false;
      bool KlfdoYmcKh = false;
      bool dwLQIJgXVX = false;
      bool bsgHpAcMGg = false;
      bool TBwsHhdBCx = false;
      bool JKoXoFAtqj = false;
      bool bKpQSQEXno = false;
      bool waWcNbzRIZ = false;
      bool efVYNQEJSk = false;
      bool AhUVEJKfZp = false;
      bool dGNNBinLJM = false;
      bool FhlREwoRCB = false;
      bool MuEDnNFAXE = false;
      bool RTqRwYSHWe = false;
      string tYOuDlItzJ;
      string kORQLegbIj;
      string SDYBlApotm;
      string XkTJAZcniZ;
      string hspIsqxDZe;
      string EIflgqzNJC;
      string wSzMkztHPk;
      string CrriCZMPHu;
      string CmPPiPFhbI;
      string ZOefdOsdWs;
      string wpmocMQwjH;
      string djGNAJDjcV;
      string tMfGKnMLFm;
      string girNyMzZlW;
      string yIyUepIRfT;
      string LIABzjJgeo;
      string zEqwZurrPn;
      string JcxGWkNKbT;
      string euekaXhqON;
      string CSuxWtQBti;
      if(tYOuDlItzJ == wpmocMQwjH){yQBrJiLtdN = true;}
      else if(wpmocMQwjH == tYOuDlItzJ){TBwsHhdBCx = true;}
      if(kORQLegbIj == djGNAJDjcV){WzEKJEYGVC = true;}
      else if(djGNAJDjcV == kORQLegbIj){JKoXoFAtqj = true;}
      if(SDYBlApotm == tMfGKnMLFm){MAcBkqgzic = true;}
      else if(tMfGKnMLFm == SDYBlApotm){bKpQSQEXno = true;}
      if(XkTJAZcniZ == girNyMzZlW){TMQrVOsmaq = true;}
      else if(girNyMzZlW == XkTJAZcniZ){waWcNbzRIZ = true;}
      if(hspIsqxDZe == yIyUepIRfT){MnNAqDNknS = true;}
      else if(yIyUepIRfT == hspIsqxDZe){efVYNQEJSk = true;}
      if(EIflgqzNJC == LIABzjJgeo){UKerWxmzGS = true;}
      else if(LIABzjJgeo == EIflgqzNJC){AhUVEJKfZp = true;}
      if(wSzMkztHPk == zEqwZurrPn){BLKAtJiMnt = true;}
      else if(zEqwZurrPn == wSzMkztHPk){dGNNBinLJM = true;}
      if(CrriCZMPHu == JcxGWkNKbT){KlfdoYmcKh = true;}
      if(CmPPiPFhbI == euekaXhqON){dwLQIJgXVX = true;}
      if(ZOefdOsdWs == CSuxWtQBti){bsgHpAcMGg = true;}
      while(JcxGWkNKbT == CrriCZMPHu){FhlREwoRCB = true;}
      while(euekaXhqON == euekaXhqON){MuEDnNFAXE = true;}
      while(CSuxWtQBti == CSuxWtQBti){RTqRwYSHWe = true;}
      if(yQBrJiLtdN == true){yQBrJiLtdN = false;}
      if(WzEKJEYGVC == true){WzEKJEYGVC = false;}
      if(MAcBkqgzic == true){MAcBkqgzic = false;}
      if(TMQrVOsmaq == true){TMQrVOsmaq = false;}
      if(MnNAqDNknS == true){MnNAqDNknS = false;}
      if(UKerWxmzGS == true){UKerWxmzGS = false;}
      if(BLKAtJiMnt == true){BLKAtJiMnt = false;}
      if(KlfdoYmcKh == true){KlfdoYmcKh = false;}
      if(dwLQIJgXVX == true){dwLQIJgXVX = false;}
      if(bsgHpAcMGg == true){bsgHpAcMGg = false;}
      if(TBwsHhdBCx == true){TBwsHhdBCx = false;}
      if(JKoXoFAtqj == true){JKoXoFAtqj = false;}
      if(bKpQSQEXno == true){bKpQSQEXno = false;}
      if(waWcNbzRIZ == true){waWcNbzRIZ = false;}
      if(efVYNQEJSk == true){efVYNQEJSk = false;}
      if(AhUVEJKfZp == true){AhUVEJKfZp = false;}
      if(dGNNBinLJM == true){dGNNBinLJM = false;}
      if(FhlREwoRCB == true){FhlREwoRCB = false;}
      if(MuEDnNFAXE == true){MuEDnNFAXE = false;}
      if(RTqRwYSHWe == true){RTqRwYSHWe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMQGCVSRHC
{ 
  void MhRksIYaLP()
  { 
      bool sATLRwxMmC = false;
      bool NxPwYSaWln = false;
      bool YmlQYzcPGf = false;
      bool pBVSawqmHk = false;
      bool XIxDqXjgCl = false;
      bool GxCCuFODmR = false;
      bool TgGHLLawVc = false;
      bool bmOAPQpiYB = false;
      bool PuNTZszTWV = false;
      bool hnApQpBpqe = false;
      bool wnLYKSiBle = false;
      bool OedlCXTmgS = false;
      bool MHYAumlYiY = false;
      bool OzrsEajnIH = false;
      bool JygrGCJOms = false;
      bool WOJXSnOLdW = false;
      bool fJRNPOmjga = false;
      bool nedZINagsr = false;
      bool dXkpCApTaQ = false;
      bool MXJlazgSbq = false;
      string LCxFmsDQhK;
      string jOPXJSauyi;
      string WDjcSJdJPS;
      string DEEgNuYFJk;
      string wfkbUKFRPG;
      string BQArMISTld;
      string PsAOGeJhKN;
      string tUkMmqRHII;
      string DLtJRlDMUF;
      string cETfVCfWVo;
      string AXHBLfemEU;
      string pKLdZDzpxU;
      string axMEkoBFqk;
      string LulTHfDsyk;
      string HQHAPRrpFR;
      string DoZANDKDPV;
      string eZwTJtYrVt;
      string zGrMNKoMnT;
      string xLzZhVVkFE;
      string VAcbFgTnpU;
      if(LCxFmsDQhK == AXHBLfemEU){sATLRwxMmC = true;}
      else if(AXHBLfemEU == LCxFmsDQhK){wnLYKSiBle = true;}
      if(jOPXJSauyi == pKLdZDzpxU){NxPwYSaWln = true;}
      else if(pKLdZDzpxU == jOPXJSauyi){OedlCXTmgS = true;}
      if(WDjcSJdJPS == axMEkoBFqk){YmlQYzcPGf = true;}
      else if(axMEkoBFqk == WDjcSJdJPS){MHYAumlYiY = true;}
      if(DEEgNuYFJk == LulTHfDsyk){pBVSawqmHk = true;}
      else if(LulTHfDsyk == DEEgNuYFJk){OzrsEajnIH = true;}
      if(wfkbUKFRPG == HQHAPRrpFR){XIxDqXjgCl = true;}
      else if(HQHAPRrpFR == wfkbUKFRPG){JygrGCJOms = true;}
      if(BQArMISTld == DoZANDKDPV){GxCCuFODmR = true;}
      else if(DoZANDKDPV == BQArMISTld){WOJXSnOLdW = true;}
      if(PsAOGeJhKN == eZwTJtYrVt){TgGHLLawVc = true;}
      else if(eZwTJtYrVt == PsAOGeJhKN){fJRNPOmjga = true;}
      if(tUkMmqRHII == zGrMNKoMnT){bmOAPQpiYB = true;}
      if(DLtJRlDMUF == xLzZhVVkFE){PuNTZszTWV = true;}
      if(cETfVCfWVo == VAcbFgTnpU){hnApQpBpqe = true;}
      while(zGrMNKoMnT == tUkMmqRHII){nedZINagsr = true;}
      while(xLzZhVVkFE == xLzZhVVkFE){dXkpCApTaQ = true;}
      while(VAcbFgTnpU == VAcbFgTnpU){MXJlazgSbq = true;}
      if(sATLRwxMmC == true){sATLRwxMmC = false;}
      if(NxPwYSaWln == true){NxPwYSaWln = false;}
      if(YmlQYzcPGf == true){YmlQYzcPGf = false;}
      if(pBVSawqmHk == true){pBVSawqmHk = false;}
      if(XIxDqXjgCl == true){XIxDqXjgCl = false;}
      if(GxCCuFODmR == true){GxCCuFODmR = false;}
      if(TgGHLLawVc == true){TgGHLLawVc = false;}
      if(bmOAPQpiYB == true){bmOAPQpiYB = false;}
      if(PuNTZszTWV == true){PuNTZszTWV = false;}
      if(hnApQpBpqe == true){hnApQpBpqe = false;}
      if(wnLYKSiBle == true){wnLYKSiBle = false;}
      if(OedlCXTmgS == true){OedlCXTmgS = false;}
      if(MHYAumlYiY == true){MHYAumlYiY = false;}
      if(OzrsEajnIH == true){OzrsEajnIH = false;}
      if(JygrGCJOms == true){JygrGCJOms = false;}
      if(WOJXSnOLdW == true){WOJXSnOLdW = false;}
      if(fJRNPOmjga == true){fJRNPOmjga = false;}
      if(nedZINagsr == true){nedZINagsr = false;}
      if(dXkpCApTaQ == true){dXkpCApTaQ = false;}
      if(MXJlazgSbq == true){MXJlazgSbq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QDBLUZXOQR
{ 
  void XcKIhWublB()
  { 
      bool VLorELGISB = false;
      bool sQIAprTNEB = false;
      bool CSSRmdgAfL = false;
      bool eTMqwwkyaS = false;
      bool nqZQVmHxQp = false;
      bool HKOzdCrXEa = false;
      bool eGcHWZEQDs = false;
      bool GVlkNKsCuA = false;
      bool VjipDTFMMt = false;
      bool ENsAnhOSsw = false;
      bool hqsXilXclT = false;
      bool JpcEEuWmDD = false;
      bool UrDJnsblxf = false;
      bool waIyRepLGR = false;
      bool ubZsjOkous = false;
      bool KaOobpmjip = false;
      bool JlfGWigdlY = false;
      bool ELglIrRJYZ = false;
      bool ImpDUULSWb = false;
      bool rFcPHIuSWA = false;
      string LwxomKQtQr;
      string wVOETbBuiT;
      string gcImpkkoYi;
      string tiVwpdPBLO;
      string MwTdnVKBHP;
      string RVrMqinJyB;
      string ZbVgyMzSOo;
      string LAjTGjJdzT;
      string aihIRXqJFH;
      string pGCJokalfa;
      string WrmRDQkYFG;
      string YJJeZptMPZ;
      string VpMGzFyaeV;
      string JWyXxiwPFB;
      string mSDyhgxWjy;
      string pNWFFgefSy;
      string SKsjxCKlhq;
      string tdHOmDmNXS;
      string IapfeuzrSP;
      string DPxGhbYSBf;
      if(LwxomKQtQr == WrmRDQkYFG){VLorELGISB = true;}
      else if(WrmRDQkYFG == LwxomKQtQr){hqsXilXclT = true;}
      if(wVOETbBuiT == YJJeZptMPZ){sQIAprTNEB = true;}
      else if(YJJeZptMPZ == wVOETbBuiT){JpcEEuWmDD = true;}
      if(gcImpkkoYi == VpMGzFyaeV){CSSRmdgAfL = true;}
      else if(VpMGzFyaeV == gcImpkkoYi){UrDJnsblxf = true;}
      if(tiVwpdPBLO == JWyXxiwPFB){eTMqwwkyaS = true;}
      else if(JWyXxiwPFB == tiVwpdPBLO){waIyRepLGR = true;}
      if(MwTdnVKBHP == mSDyhgxWjy){nqZQVmHxQp = true;}
      else if(mSDyhgxWjy == MwTdnVKBHP){ubZsjOkous = true;}
      if(RVrMqinJyB == pNWFFgefSy){HKOzdCrXEa = true;}
      else if(pNWFFgefSy == RVrMqinJyB){KaOobpmjip = true;}
      if(ZbVgyMzSOo == SKsjxCKlhq){eGcHWZEQDs = true;}
      else if(SKsjxCKlhq == ZbVgyMzSOo){JlfGWigdlY = true;}
      if(LAjTGjJdzT == tdHOmDmNXS){GVlkNKsCuA = true;}
      if(aihIRXqJFH == IapfeuzrSP){VjipDTFMMt = true;}
      if(pGCJokalfa == DPxGhbYSBf){ENsAnhOSsw = true;}
      while(tdHOmDmNXS == LAjTGjJdzT){ELglIrRJYZ = true;}
      while(IapfeuzrSP == IapfeuzrSP){ImpDUULSWb = true;}
      while(DPxGhbYSBf == DPxGhbYSBf){rFcPHIuSWA = true;}
      if(VLorELGISB == true){VLorELGISB = false;}
      if(sQIAprTNEB == true){sQIAprTNEB = false;}
      if(CSSRmdgAfL == true){CSSRmdgAfL = false;}
      if(eTMqwwkyaS == true){eTMqwwkyaS = false;}
      if(nqZQVmHxQp == true){nqZQVmHxQp = false;}
      if(HKOzdCrXEa == true){HKOzdCrXEa = false;}
      if(eGcHWZEQDs == true){eGcHWZEQDs = false;}
      if(GVlkNKsCuA == true){GVlkNKsCuA = false;}
      if(VjipDTFMMt == true){VjipDTFMMt = false;}
      if(ENsAnhOSsw == true){ENsAnhOSsw = false;}
      if(hqsXilXclT == true){hqsXilXclT = false;}
      if(JpcEEuWmDD == true){JpcEEuWmDD = false;}
      if(UrDJnsblxf == true){UrDJnsblxf = false;}
      if(waIyRepLGR == true){waIyRepLGR = false;}
      if(ubZsjOkous == true){ubZsjOkous = false;}
      if(KaOobpmjip == true){KaOobpmjip = false;}
      if(JlfGWigdlY == true){JlfGWigdlY = false;}
      if(ELglIrRJYZ == true){ELglIrRJYZ = false;}
      if(ImpDUULSWb == true){ImpDUULSWb = false;}
      if(rFcPHIuSWA == true){rFcPHIuSWA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVIFGHIEUI
{ 
  void VbThQeylbL()
  { 
      bool stuFCwoZsR = false;
      bool DSxkdESENJ = false;
      bool hIMwfAsDGu = false;
      bool GbqkdQtAlr = false;
      bool GEIDsIwonC = false;
      bool DqYuFjgyYB = false;
      bool ClTxLbbLGM = false;
      bool JRSUCdAJDX = false;
      bool EDODrOCuft = false;
      bool jwbkoUkLrR = false;
      bool fjiaskYErb = false;
      bool jXuBwzWPFw = false;
      bool YgfMcNpgeh = false;
      bool roQkqTUmKG = false;
      bool pxCDKMAanp = false;
      bool yUGwrzEVye = false;
      bool uqZKiuGJJc = false;
      bool diEyGadbBQ = false;
      bool NPsniWhUsq = false;
      bool PyofLyXqTP = false;
      string oXsGYmkQmR;
      string BhOzsKeJWV;
      string DfMVJLPLBo;
      string PpgjqnWxad;
      string tFEaVXzEpQ;
      string JbWiLIKWxM;
      string WZOxBKBdHE;
      string mghrayalAl;
      string MLUkenTxXh;
      string czAOHUpHYK;
      string VUwkcbsdIN;
      string gYWKAKEdRN;
      string qDGZbngTkF;
      string HTNoPqPjHD;
      string uooKAEbpNw;
      string QLoLTSOVIo;
      string uYsCFMKhtI;
      string tTVORCOuYX;
      string LpFnoweBUx;
      string bsaSHVwlEm;
      if(oXsGYmkQmR == VUwkcbsdIN){stuFCwoZsR = true;}
      else if(VUwkcbsdIN == oXsGYmkQmR){fjiaskYErb = true;}
      if(BhOzsKeJWV == gYWKAKEdRN){DSxkdESENJ = true;}
      else if(gYWKAKEdRN == BhOzsKeJWV){jXuBwzWPFw = true;}
      if(DfMVJLPLBo == qDGZbngTkF){hIMwfAsDGu = true;}
      else if(qDGZbngTkF == DfMVJLPLBo){YgfMcNpgeh = true;}
      if(PpgjqnWxad == HTNoPqPjHD){GbqkdQtAlr = true;}
      else if(HTNoPqPjHD == PpgjqnWxad){roQkqTUmKG = true;}
      if(tFEaVXzEpQ == uooKAEbpNw){GEIDsIwonC = true;}
      else if(uooKAEbpNw == tFEaVXzEpQ){pxCDKMAanp = true;}
      if(JbWiLIKWxM == QLoLTSOVIo){DqYuFjgyYB = true;}
      else if(QLoLTSOVIo == JbWiLIKWxM){yUGwrzEVye = true;}
      if(WZOxBKBdHE == uYsCFMKhtI){ClTxLbbLGM = true;}
      else if(uYsCFMKhtI == WZOxBKBdHE){uqZKiuGJJc = true;}
      if(mghrayalAl == tTVORCOuYX){JRSUCdAJDX = true;}
      if(MLUkenTxXh == LpFnoweBUx){EDODrOCuft = true;}
      if(czAOHUpHYK == bsaSHVwlEm){jwbkoUkLrR = true;}
      while(tTVORCOuYX == mghrayalAl){diEyGadbBQ = true;}
      while(LpFnoweBUx == LpFnoweBUx){NPsniWhUsq = true;}
      while(bsaSHVwlEm == bsaSHVwlEm){PyofLyXqTP = true;}
      if(stuFCwoZsR == true){stuFCwoZsR = false;}
      if(DSxkdESENJ == true){DSxkdESENJ = false;}
      if(hIMwfAsDGu == true){hIMwfAsDGu = false;}
      if(GbqkdQtAlr == true){GbqkdQtAlr = false;}
      if(GEIDsIwonC == true){GEIDsIwonC = false;}
      if(DqYuFjgyYB == true){DqYuFjgyYB = false;}
      if(ClTxLbbLGM == true){ClTxLbbLGM = false;}
      if(JRSUCdAJDX == true){JRSUCdAJDX = false;}
      if(EDODrOCuft == true){EDODrOCuft = false;}
      if(jwbkoUkLrR == true){jwbkoUkLrR = false;}
      if(fjiaskYErb == true){fjiaskYErb = false;}
      if(jXuBwzWPFw == true){jXuBwzWPFw = false;}
      if(YgfMcNpgeh == true){YgfMcNpgeh = false;}
      if(roQkqTUmKG == true){roQkqTUmKG = false;}
      if(pxCDKMAanp == true){pxCDKMAanp = false;}
      if(yUGwrzEVye == true){yUGwrzEVye = false;}
      if(uqZKiuGJJc == true){uqZKiuGJJc = false;}
      if(diEyGadbBQ == true){diEyGadbBQ = false;}
      if(NPsniWhUsq == true){NPsniWhUsq = false;}
      if(PyofLyXqTP == true){PyofLyXqTP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWIRXHDCPE
{ 
  void kpfWpcVwrz()
  { 
      bool EoNMNmwcFa = false;
      bool RkRWPZakqr = false;
      bool MzabDMuONM = false;
      bool FaGLVDtIjT = false;
      bool YRkAcNXVdw = false;
      bool AgzSYEOlIA = false;
      bool qhOsVpeFAL = false;
      bool eRAWStOZyo = false;
      bool oYjQLYbmmR = false;
      bool oHzibqCqel = false;
      bool iRURRifbAd = false;
      bool oomTLRxxgw = false;
      bool OrSiWXSQua = false;
      bool qWtMGWERzc = false;
      bool rzlIczTfXJ = false;
      bool tFKiXpzlut = false;
      bool PPgYlRuaNn = false;
      bool NexEDOFJGX = false;
      bool DmskglMKnP = false;
      bool XRWFMcSNWL = false;
      string zdOOzbARDI;
      string sXDaXFobUj;
      string acNmpxLNEk;
      string pZtydjxJWl;
      string tgTXpUACFE;
      string GkdXjWPaXC;
      string QmNSRTcFwn;
      string IeEhptIpxV;
      string xJHAeEuWOG;
      string TVlUVGSBGW;
      string qtFRuagugo;
      string OZdBFGeNnM;
      string XGqpTlsjMi;
      string aHjaeCEpED;
      string XAoYrtrkOO;
      string bFMsyjDPxJ;
      string hwhyNGpCWC;
      string BnJjnXRRxZ;
      string sIUxHVtpbu;
      string zostVbRpLk;
      if(zdOOzbARDI == qtFRuagugo){EoNMNmwcFa = true;}
      else if(qtFRuagugo == zdOOzbARDI){iRURRifbAd = true;}
      if(sXDaXFobUj == OZdBFGeNnM){RkRWPZakqr = true;}
      else if(OZdBFGeNnM == sXDaXFobUj){oomTLRxxgw = true;}
      if(acNmpxLNEk == XGqpTlsjMi){MzabDMuONM = true;}
      else if(XGqpTlsjMi == acNmpxLNEk){OrSiWXSQua = true;}
      if(pZtydjxJWl == aHjaeCEpED){FaGLVDtIjT = true;}
      else if(aHjaeCEpED == pZtydjxJWl){qWtMGWERzc = true;}
      if(tgTXpUACFE == XAoYrtrkOO){YRkAcNXVdw = true;}
      else if(XAoYrtrkOO == tgTXpUACFE){rzlIczTfXJ = true;}
      if(GkdXjWPaXC == bFMsyjDPxJ){AgzSYEOlIA = true;}
      else if(bFMsyjDPxJ == GkdXjWPaXC){tFKiXpzlut = true;}
      if(QmNSRTcFwn == hwhyNGpCWC){qhOsVpeFAL = true;}
      else if(hwhyNGpCWC == QmNSRTcFwn){PPgYlRuaNn = true;}
      if(IeEhptIpxV == BnJjnXRRxZ){eRAWStOZyo = true;}
      if(xJHAeEuWOG == sIUxHVtpbu){oYjQLYbmmR = true;}
      if(TVlUVGSBGW == zostVbRpLk){oHzibqCqel = true;}
      while(BnJjnXRRxZ == IeEhptIpxV){NexEDOFJGX = true;}
      while(sIUxHVtpbu == sIUxHVtpbu){DmskglMKnP = true;}
      while(zostVbRpLk == zostVbRpLk){XRWFMcSNWL = true;}
      if(EoNMNmwcFa == true){EoNMNmwcFa = false;}
      if(RkRWPZakqr == true){RkRWPZakqr = false;}
      if(MzabDMuONM == true){MzabDMuONM = false;}
      if(FaGLVDtIjT == true){FaGLVDtIjT = false;}
      if(YRkAcNXVdw == true){YRkAcNXVdw = false;}
      if(AgzSYEOlIA == true){AgzSYEOlIA = false;}
      if(qhOsVpeFAL == true){qhOsVpeFAL = false;}
      if(eRAWStOZyo == true){eRAWStOZyo = false;}
      if(oYjQLYbmmR == true){oYjQLYbmmR = false;}
      if(oHzibqCqel == true){oHzibqCqel = false;}
      if(iRURRifbAd == true){iRURRifbAd = false;}
      if(oomTLRxxgw == true){oomTLRxxgw = false;}
      if(OrSiWXSQua == true){OrSiWXSQua = false;}
      if(qWtMGWERzc == true){qWtMGWERzc = false;}
      if(rzlIczTfXJ == true){rzlIczTfXJ = false;}
      if(tFKiXpzlut == true){tFKiXpzlut = false;}
      if(PPgYlRuaNn == true){PPgYlRuaNn = false;}
      if(NexEDOFJGX == true){NexEDOFJGX = false;}
      if(DmskglMKnP == true){DmskglMKnP = false;}
      if(XRWFMcSNWL == true){XRWFMcSNWL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWJFBQLGFS
{ 
  void CFVtRlcgxp()
  { 
      bool yExeQzzBtA = false;
      bool oQYajxkxOX = false;
      bool kUBGgEOOKc = false;
      bool WZnAXYNDcT = false;
      bool ZgyDHpfCWA = false;
      bool ZXlSOdDqyL = false;
      bool jjqRdPbYCL = false;
      bool jhUtyEWxzp = false;
      bool YMqKCynVkt = false;
      bool UVFRiopgZr = false;
      bool NGzLPrDqUK = false;
      bool HGrHlWsgOe = false;
      bool bGnIpNbCLJ = false;
      bool OoXHcSNetJ = false;
      bool uwAamOdyeM = false;
      bool uIRtQHSqVC = false;
      bool QAfLwRhkdT = false;
      bool IOmFjeFMUa = false;
      bool jdXyNFWdqU = false;
      bool zWIrsuPoeU = false;
      string EPSEwrAtMo;
      string yWfSGICYPF;
      string nawWzlbZbY;
      string XTmeMUIXRf;
      string kfKSbKRASD;
      string yZuMzdSwFJ;
      string PZRmQdjAFk;
      string AdHjUIPctn;
      string TaHYZyYZfi;
      string CLRHPKNWBy;
      string aRugCUSLrq;
      string NoBQooSrNS;
      string FJUVinLzTK;
      string tsawNCeaWF;
      string eMhnUMJARa;
      string qUJhrQwZxO;
      string ISqgxUNEDm;
      string JrVHnrafAW;
      string dKhsSYirDw;
      string GFcHxLVAqA;
      if(EPSEwrAtMo == aRugCUSLrq){yExeQzzBtA = true;}
      else if(aRugCUSLrq == EPSEwrAtMo){NGzLPrDqUK = true;}
      if(yWfSGICYPF == NoBQooSrNS){oQYajxkxOX = true;}
      else if(NoBQooSrNS == yWfSGICYPF){HGrHlWsgOe = true;}
      if(nawWzlbZbY == FJUVinLzTK){kUBGgEOOKc = true;}
      else if(FJUVinLzTK == nawWzlbZbY){bGnIpNbCLJ = true;}
      if(XTmeMUIXRf == tsawNCeaWF){WZnAXYNDcT = true;}
      else if(tsawNCeaWF == XTmeMUIXRf){OoXHcSNetJ = true;}
      if(kfKSbKRASD == eMhnUMJARa){ZgyDHpfCWA = true;}
      else if(eMhnUMJARa == kfKSbKRASD){uwAamOdyeM = true;}
      if(yZuMzdSwFJ == qUJhrQwZxO){ZXlSOdDqyL = true;}
      else if(qUJhrQwZxO == yZuMzdSwFJ){uIRtQHSqVC = true;}
      if(PZRmQdjAFk == ISqgxUNEDm){jjqRdPbYCL = true;}
      else if(ISqgxUNEDm == PZRmQdjAFk){QAfLwRhkdT = true;}
      if(AdHjUIPctn == JrVHnrafAW){jhUtyEWxzp = true;}
      if(TaHYZyYZfi == dKhsSYirDw){YMqKCynVkt = true;}
      if(CLRHPKNWBy == GFcHxLVAqA){UVFRiopgZr = true;}
      while(JrVHnrafAW == AdHjUIPctn){IOmFjeFMUa = true;}
      while(dKhsSYirDw == dKhsSYirDw){jdXyNFWdqU = true;}
      while(GFcHxLVAqA == GFcHxLVAqA){zWIrsuPoeU = true;}
      if(yExeQzzBtA == true){yExeQzzBtA = false;}
      if(oQYajxkxOX == true){oQYajxkxOX = false;}
      if(kUBGgEOOKc == true){kUBGgEOOKc = false;}
      if(WZnAXYNDcT == true){WZnAXYNDcT = false;}
      if(ZgyDHpfCWA == true){ZgyDHpfCWA = false;}
      if(ZXlSOdDqyL == true){ZXlSOdDqyL = false;}
      if(jjqRdPbYCL == true){jjqRdPbYCL = false;}
      if(jhUtyEWxzp == true){jhUtyEWxzp = false;}
      if(YMqKCynVkt == true){YMqKCynVkt = false;}
      if(UVFRiopgZr == true){UVFRiopgZr = false;}
      if(NGzLPrDqUK == true){NGzLPrDqUK = false;}
      if(HGrHlWsgOe == true){HGrHlWsgOe = false;}
      if(bGnIpNbCLJ == true){bGnIpNbCLJ = false;}
      if(OoXHcSNetJ == true){OoXHcSNetJ = false;}
      if(uwAamOdyeM == true){uwAamOdyeM = false;}
      if(uIRtQHSqVC == true){uIRtQHSqVC = false;}
      if(QAfLwRhkdT == true){QAfLwRhkdT = false;}
      if(IOmFjeFMUa == true){IOmFjeFMUa = false;}
      if(jdXyNFWdqU == true){jdXyNFWdqU = false;}
      if(zWIrsuPoeU == true){zWIrsuPoeU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GKKKBGCCKA
{ 
  void bmqNERyxVw()
  { 
      bool HUxShFWPOA = false;
      bool CAiEKSnfIk = false;
      bool sMEqjWfWwd = false;
      bool uUmowBiEiG = false;
      bool VCBcNAXuUD = false;
      bool DfuDpuQGhL = false;
      bool YATjFgMsHI = false;
      bool jiwBPpKbdi = false;
      bool zkBraOZiyB = false;
      bool kbWXgUiRWg = false;
      bool mdmMTTjsnA = false;
      bool knczLnzaJp = false;
      bool GctGXHMYUt = false;
      bool GsExwUyoXG = false;
      bool eguyQwzXLs = false;
      bool VIIgZJjgnM = false;
      bool HLXttqjfCq = false;
      bool oJCCLYhwpa = false;
      bool HoMaXyjXWl = false;
      bool kQALzTIADY = false;
      string PhEnAYKEVq;
      string sUWNKmDdSw;
      string eiqfaiqMUc;
      string YsgOmFsPjk;
      string XYNdXLfBEA;
      string XgIpBgqYMR;
      string hxjrSAnIZE;
      string snsgXGVMHO;
      string CpITFqjpMG;
      string OTCSDZoULX;
      string XXbzGjmaSt;
      string LdRxOroPma;
      string PxuTpYkadx;
      string RABjqdOINU;
      string EJXStkCEDL;
      string kYhkHacHJg;
      string yLxUcLcgGk;
      string cfCRWGYcYE;
      string WfXRMrSPcP;
      string BGzfVrLDoi;
      if(PhEnAYKEVq == XXbzGjmaSt){HUxShFWPOA = true;}
      else if(XXbzGjmaSt == PhEnAYKEVq){mdmMTTjsnA = true;}
      if(sUWNKmDdSw == LdRxOroPma){CAiEKSnfIk = true;}
      else if(LdRxOroPma == sUWNKmDdSw){knczLnzaJp = true;}
      if(eiqfaiqMUc == PxuTpYkadx){sMEqjWfWwd = true;}
      else if(PxuTpYkadx == eiqfaiqMUc){GctGXHMYUt = true;}
      if(YsgOmFsPjk == RABjqdOINU){uUmowBiEiG = true;}
      else if(RABjqdOINU == YsgOmFsPjk){GsExwUyoXG = true;}
      if(XYNdXLfBEA == EJXStkCEDL){VCBcNAXuUD = true;}
      else if(EJXStkCEDL == XYNdXLfBEA){eguyQwzXLs = true;}
      if(XgIpBgqYMR == kYhkHacHJg){DfuDpuQGhL = true;}
      else if(kYhkHacHJg == XgIpBgqYMR){VIIgZJjgnM = true;}
      if(hxjrSAnIZE == yLxUcLcgGk){YATjFgMsHI = true;}
      else if(yLxUcLcgGk == hxjrSAnIZE){HLXttqjfCq = true;}
      if(snsgXGVMHO == cfCRWGYcYE){jiwBPpKbdi = true;}
      if(CpITFqjpMG == WfXRMrSPcP){zkBraOZiyB = true;}
      if(OTCSDZoULX == BGzfVrLDoi){kbWXgUiRWg = true;}
      while(cfCRWGYcYE == snsgXGVMHO){oJCCLYhwpa = true;}
      while(WfXRMrSPcP == WfXRMrSPcP){HoMaXyjXWl = true;}
      while(BGzfVrLDoi == BGzfVrLDoi){kQALzTIADY = true;}
      if(HUxShFWPOA == true){HUxShFWPOA = false;}
      if(CAiEKSnfIk == true){CAiEKSnfIk = false;}
      if(sMEqjWfWwd == true){sMEqjWfWwd = false;}
      if(uUmowBiEiG == true){uUmowBiEiG = false;}
      if(VCBcNAXuUD == true){VCBcNAXuUD = false;}
      if(DfuDpuQGhL == true){DfuDpuQGhL = false;}
      if(YATjFgMsHI == true){YATjFgMsHI = false;}
      if(jiwBPpKbdi == true){jiwBPpKbdi = false;}
      if(zkBraOZiyB == true){zkBraOZiyB = false;}
      if(kbWXgUiRWg == true){kbWXgUiRWg = false;}
      if(mdmMTTjsnA == true){mdmMTTjsnA = false;}
      if(knczLnzaJp == true){knczLnzaJp = false;}
      if(GctGXHMYUt == true){GctGXHMYUt = false;}
      if(GsExwUyoXG == true){GsExwUyoXG = false;}
      if(eguyQwzXLs == true){eguyQwzXLs = false;}
      if(VIIgZJjgnM == true){VIIgZJjgnM = false;}
      if(HLXttqjfCq == true){HLXttqjfCq = false;}
      if(oJCCLYhwpa == true){oJCCLYhwpa = false;}
      if(HoMaXyjXWl == true){HoMaXyjXWl = false;}
      if(kQALzTIADY == true){kQALzTIADY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HSDWSLSQQK
{ 
  void TlyCgozmNF()
  { 
      bool uqPkGOPpUe = false;
      bool ZSTCozPZah = false;
      bool tbmZWpFNeD = false;
      bool OwyBlOsYwO = false;
      bool gYZeXPzJqa = false;
      bool kSSIhSEoNP = false;
      bool ICKRPcUSQZ = false;
      bool GpdMBUCICG = false;
      bool qwVERudoSS = false;
      bool KEKfFeNIOt = false;
      bool ugrQUuoFHM = false;
      bool QumHYMfGzU = false;
      bool yezxOCeyGW = false;
      bool HttHLKEEjW = false;
      bool GXhFCPQDGs = false;
      bool yHItwQgtBS = false;
      bool QpzkFVBfwO = false;
      bool HaWbNZwtuz = false;
      bool kaqMXAkzKt = false;
      bool cJCQGPYwzf = false;
      string WekZcXSfnA;
      string WeKtmRtwGq;
      string NHMdWMRYoL;
      string TYdlVcoaFw;
      string mYMlPFwlsU;
      string XRFRbOSHDP;
      string FsqbgyAYXJ;
      string cTqJDnuZNR;
      string QfeTmBSLKG;
      string KhXpptgjFR;
      string EXOiqEawNm;
      string TrskyZNWoe;
      string enNQzuuBSJ;
      string HKUwNsQwci;
      string aWyXlSnmqP;
      string fJuZmPJxjw;
      string IZcEfJWwXF;
      string JRtFEIppdg;
      string GIKCcxOuJx;
      string iSLgaAssqc;
      if(WekZcXSfnA == EXOiqEawNm){uqPkGOPpUe = true;}
      else if(EXOiqEawNm == WekZcXSfnA){ugrQUuoFHM = true;}
      if(WeKtmRtwGq == TrskyZNWoe){ZSTCozPZah = true;}
      else if(TrskyZNWoe == WeKtmRtwGq){QumHYMfGzU = true;}
      if(NHMdWMRYoL == enNQzuuBSJ){tbmZWpFNeD = true;}
      else if(enNQzuuBSJ == NHMdWMRYoL){yezxOCeyGW = true;}
      if(TYdlVcoaFw == HKUwNsQwci){OwyBlOsYwO = true;}
      else if(HKUwNsQwci == TYdlVcoaFw){HttHLKEEjW = true;}
      if(mYMlPFwlsU == aWyXlSnmqP){gYZeXPzJqa = true;}
      else if(aWyXlSnmqP == mYMlPFwlsU){GXhFCPQDGs = true;}
      if(XRFRbOSHDP == fJuZmPJxjw){kSSIhSEoNP = true;}
      else if(fJuZmPJxjw == XRFRbOSHDP){yHItwQgtBS = true;}
      if(FsqbgyAYXJ == IZcEfJWwXF){ICKRPcUSQZ = true;}
      else if(IZcEfJWwXF == FsqbgyAYXJ){QpzkFVBfwO = true;}
      if(cTqJDnuZNR == JRtFEIppdg){GpdMBUCICG = true;}
      if(QfeTmBSLKG == GIKCcxOuJx){qwVERudoSS = true;}
      if(KhXpptgjFR == iSLgaAssqc){KEKfFeNIOt = true;}
      while(JRtFEIppdg == cTqJDnuZNR){HaWbNZwtuz = true;}
      while(GIKCcxOuJx == GIKCcxOuJx){kaqMXAkzKt = true;}
      while(iSLgaAssqc == iSLgaAssqc){cJCQGPYwzf = true;}
      if(uqPkGOPpUe == true){uqPkGOPpUe = false;}
      if(ZSTCozPZah == true){ZSTCozPZah = false;}
      if(tbmZWpFNeD == true){tbmZWpFNeD = false;}
      if(OwyBlOsYwO == true){OwyBlOsYwO = false;}
      if(gYZeXPzJqa == true){gYZeXPzJqa = false;}
      if(kSSIhSEoNP == true){kSSIhSEoNP = false;}
      if(ICKRPcUSQZ == true){ICKRPcUSQZ = false;}
      if(GpdMBUCICG == true){GpdMBUCICG = false;}
      if(qwVERudoSS == true){qwVERudoSS = false;}
      if(KEKfFeNIOt == true){KEKfFeNIOt = false;}
      if(ugrQUuoFHM == true){ugrQUuoFHM = false;}
      if(QumHYMfGzU == true){QumHYMfGzU = false;}
      if(yezxOCeyGW == true){yezxOCeyGW = false;}
      if(HttHLKEEjW == true){HttHLKEEjW = false;}
      if(GXhFCPQDGs == true){GXhFCPQDGs = false;}
      if(yHItwQgtBS == true){yHItwQgtBS = false;}
      if(QpzkFVBfwO == true){QpzkFVBfwO = false;}
      if(HaWbNZwtuz == true){HaWbNZwtuz = false;}
      if(kaqMXAkzKt == true){kaqMXAkzKt = false;}
      if(cJCQGPYwzf == true){cJCQGPYwzf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LNIGTPHACF
{ 
  void NRMpAADIAS()
  { 
      bool biUSPOeLhl = false;
      bool CrPxfdwzjM = false;
      bool dJebqiTjXw = false;
      bool gYxSGaochw = false;
      bool hFAJXATeTV = false;
      bool lNWGWSDsbf = false;
      bool ttnlEctwqE = false;
      bool oSRmeXIUDq = false;
      bool PnPCJTCqun = false;
      bool XwBCBmROEt = false;
      bool FXnOfSwjbz = false;
      bool JhokQGdlbk = false;
      bool aDACgsRPkr = false;
      bool GtQJkrzBVp = false;
      bool WROwdoGQku = false;
      bool IflTTCWkgm = false;
      bool BgzjrORfzX = false;
      bool HcPkNInEYq = false;
      bool lBdpiZIwoi = false;
      bool VNThopSeDO = false;
      string xpcXJqZYFJ;
      string ZTWyLVbheu;
      string lFsFnAjewm;
      string paTPkDlPwc;
      string JSLinPcOot;
      string faiBTqxWiI;
      string HtcRSzzHMH;
      string iMkCkStKRY;
      string XUoBGPrRut;
      string GOgmUPpsPn;
      string PVCgKTofQB;
      string wlEKklEaKD;
      string HgLRBUfxgV;
      string bAtcICSIpm;
      string ZLBsxTKVCi;
      string KPiLghJjep;
      string mqyuZwraBi;
      string SwjWdufRUh;
      string JJuyKMRhwZ;
      string ricAzhNGTB;
      if(xpcXJqZYFJ == PVCgKTofQB){biUSPOeLhl = true;}
      else if(PVCgKTofQB == xpcXJqZYFJ){FXnOfSwjbz = true;}
      if(ZTWyLVbheu == wlEKklEaKD){CrPxfdwzjM = true;}
      else if(wlEKklEaKD == ZTWyLVbheu){JhokQGdlbk = true;}
      if(lFsFnAjewm == HgLRBUfxgV){dJebqiTjXw = true;}
      else if(HgLRBUfxgV == lFsFnAjewm){aDACgsRPkr = true;}
      if(paTPkDlPwc == bAtcICSIpm){gYxSGaochw = true;}
      else if(bAtcICSIpm == paTPkDlPwc){GtQJkrzBVp = true;}
      if(JSLinPcOot == ZLBsxTKVCi){hFAJXATeTV = true;}
      else if(ZLBsxTKVCi == JSLinPcOot){WROwdoGQku = true;}
      if(faiBTqxWiI == KPiLghJjep){lNWGWSDsbf = true;}
      else if(KPiLghJjep == faiBTqxWiI){IflTTCWkgm = true;}
      if(HtcRSzzHMH == mqyuZwraBi){ttnlEctwqE = true;}
      else if(mqyuZwraBi == HtcRSzzHMH){BgzjrORfzX = true;}
      if(iMkCkStKRY == SwjWdufRUh){oSRmeXIUDq = true;}
      if(XUoBGPrRut == JJuyKMRhwZ){PnPCJTCqun = true;}
      if(GOgmUPpsPn == ricAzhNGTB){XwBCBmROEt = true;}
      while(SwjWdufRUh == iMkCkStKRY){HcPkNInEYq = true;}
      while(JJuyKMRhwZ == JJuyKMRhwZ){lBdpiZIwoi = true;}
      while(ricAzhNGTB == ricAzhNGTB){VNThopSeDO = true;}
      if(biUSPOeLhl == true){biUSPOeLhl = false;}
      if(CrPxfdwzjM == true){CrPxfdwzjM = false;}
      if(dJebqiTjXw == true){dJebqiTjXw = false;}
      if(gYxSGaochw == true){gYxSGaochw = false;}
      if(hFAJXATeTV == true){hFAJXATeTV = false;}
      if(lNWGWSDsbf == true){lNWGWSDsbf = false;}
      if(ttnlEctwqE == true){ttnlEctwqE = false;}
      if(oSRmeXIUDq == true){oSRmeXIUDq = false;}
      if(PnPCJTCqun == true){PnPCJTCqun = false;}
      if(XwBCBmROEt == true){XwBCBmROEt = false;}
      if(FXnOfSwjbz == true){FXnOfSwjbz = false;}
      if(JhokQGdlbk == true){JhokQGdlbk = false;}
      if(aDACgsRPkr == true){aDACgsRPkr = false;}
      if(GtQJkrzBVp == true){GtQJkrzBVp = false;}
      if(WROwdoGQku == true){WROwdoGQku = false;}
      if(IflTTCWkgm == true){IflTTCWkgm = false;}
      if(BgzjrORfzX == true){BgzjrORfzX = false;}
      if(HcPkNInEYq == true){HcPkNInEYq = false;}
      if(lBdpiZIwoi == true){lBdpiZIwoi = false;}
      if(VNThopSeDO == true){VNThopSeDO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ECVJEJULWZ
{ 
  void FbQdswirGF()
  { 
      bool bccYlQpqrl = false;
      bool GYEfoqDlFE = false;
      bool pwFkQpWdlL = false;
      bool LhrGghdwfS = false;
      bool GfTlHOLKZl = false;
      bool KPSWRfWrIu = false;
      bool tLFgZYgyyH = false;
      bool NGGmyKbSdB = false;
      bool dLEzAwOUoB = false;
      bool KlmjXuZlMh = false;
      bool hNMSYDIeYG = false;
      bool DDOHRhGFfc = false;
      bool JLJxxbTVOD = false;
      bool jpGuSQzlZx = false;
      bool mjwhyGXfSp = false;
      bool nTGiXVDPUx = false;
      bool jlQVVNxSnA = false;
      bool hUfipZPayq = false;
      bool EmDXOPiXWx = false;
      bool MjQcMATZLk = false;
      string MIzDpgUYjT;
      string SwhuhmVqLY;
      string LlMCWdzLgf;
      string wdLVrSIibQ;
      string ikFCJPEIxy;
      string UlIsIawwfM;
      string gIrEWojLDP;
      string emOtoZgJsG;
      string ZpOiLKURMQ;
      string WLCPjZsAeT;
      string erFhThXOEi;
      string tlDZlqtJsM;
      string TSylrSjyKO;
      string gfeYahjfPc;
      string mGNdWjHcdr;
      string ejHSAMsToA;
      string yYEoBOHezE;
      string GOsPZNFUOI;
      string KHURixXLYN;
      string nQqOdNBXbI;
      if(MIzDpgUYjT == erFhThXOEi){bccYlQpqrl = true;}
      else if(erFhThXOEi == MIzDpgUYjT){hNMSYDIeYG = true;}
      if(SwhuhmVqLY == tlDZlqtJsM){GYEfoqDlFE = true;}
      else if(tlDZlqtJsM == SwhuhmVqLY){DDOHRhGFfc = true;}
      if(LlMCWdzLgf == TSylrSjyKO){pwFkQpWdlL = true;}
      else if(TSylrSjyKO == LlMCWdzLgf){JLJxxbTVOD = true;}
      if(wdLVrSIibQ == gfeYahjfPc){LhrGghdwfS = true;}
      else if(gfeYahjfPc == wdLVrSIibQ){jpGuSQzlZx = true;}
      if(ikFCJPEIxy == mGNdWjHcdr){GfTlHOLKZl = true;}
      else if(mGNdWjHcdr == ikFCJPEIxy){mjwhyGXfSp = true;}
      if(UlIsIawwfM == ejHSAMsToA){KPSWRfWrIu = true;}
      else if(ejHSAMsToA == UlIsIawwfM){nTGiXVDPUx = true;}
      if(gIrEWojLDP == yYEoBOHezE){tLFgZYgyyH = true;}
      else if(yYEoBOHezE == gIrEWojLDP){jlQVVNxSnA = true;}
      if(emOtoZgJsG == GOsPZNFUOI){NGGmyKbSdB = true;}
      if(ZpOiLKURMQ == KHURixXLYN){dLEzAwOUoB = true;}
      if(WLCPjZsAeT == nQqOdNBXbI){KlmjXuZlMh = true;}
      while(GOsPZNFUOI == emOtoZgJsG){hUfipZPayq = true;}
      while(KHURixXLYN == KHURixXLYN){EmDXOPiXWx = true;}
      while(nQqOdNBXbI == nQqOdNBXbI){MjQcMATZLk = true;}
      if(bccYlQpqrl == true){bccYlQpqrl = false;}
      if(GYEfoqDlFE == true){GYEfoqDlFE = false;}
      if(pwFkQpWdlL == true){pwFkQpWdlL = false;}
      if(LhrGghdwfS == true){LhrGghdwfS = false;}
      if(GfTlHOLKZl == true){GfTlHOLKZl = false;}
      if(KPSWRfWrIu == true){KPSWRfWrIu = false;}
      if(tLFgZYgyyH == true){tLFgZYgyyH = false;}
      if(NGGmyKbSdB == true){NGGmyKbSdB = false;}
      if(dLEzAwOUoB == true){dLEzAwOUoB = false;}
      if(KlmjXuZlMh == true){KlmjXuZlMh = false;}
      if(hNMSYDIeYG == true){hNMSYDIeYG = false;}
      if(DDOHRhGFfc == true){DDOHRhGFfc = false;}
      if(JLJxxbTVOD == true){JLJxxbTVOD = false;}
      if(jpGuSQzlZx == true){jpGuSQzlZx = false;}
      if(mjwhyGXfSp == true){mjwhyGXfSp = false;}
      if(nTGiXVDPUx == true){nTGiXVDPUx = false;}
      if(jlQVVNxSnA == true){jlQVVNxSnA = false;}
      if(hUfipZPayq == true){hUfipZPayq = false;}
      if(EmDXOPiXWx == true){EmDXOPiXWx = false;}
      if(MjQcMATZLk == true){MjQcMATZLk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WJMLTCJTFY
{ 
  void OttnlquJfG()
  { 
      bool akwutoGVAf = false;
      bool CSOZwlLMwx = false;
      bool tJODwjSjzu = false;
      bool rUDjyUgAdo = false;
      bool CeaXSVPRCz = false;
      bool sayRBRWsyJ = false;
      bool WWWEngPdba = false;
      bool FLhHuPhpjZ = false;
      bool TBgzCQWlif = false;
      bool ymBTSeHWil = false;
      bool GkpbshspVk = false;
      bool ifJXpVoWCX = false;
      bool KdtwcSJNoP = false;
      bool HKHyThKFGT = false;
      bool WfPxwRdcdx = false;
      bool pjULbcptza = false;
      bool XeBGdYYKEH = false;
      bool KjQhAdNwzK = false;
      bool ngjrZWpuWq = false;
      bool qQFeurdJTX = false;
      string mODHLyxWGJ;
      string hkSEiwLfHW;
      string wnMoGuTSXH;
      string BmWDqaAfKb;
      string jXpWJQrdqJ;
      string sFxsbzCNAQ;
      string eeyzItOPNI;
      string weVelXxpfo;
      string DpaOOupcaq;
      string XlfsxFZpNP;
      string CbQiMNiRHE;
      string BMhKMnDjjM;
      string DkoVjKybgf;
      string yGbPlbZrBA;
      string LXVVpLDUgI;
      string BoFALRltzC;
      string PHjaGtjSXk;
      string OLijAePSfY;
      string GcuXeIAaDU;
      string oerykEmtPu;
      if(mODHLyxWGJ == CbQiMNiRHE){akwutoGVAf = true;}
      else if(CbQiMNiRHE == mODHLyxWGJ){GkpbshspVk = true;}
      if(hkSEiwLfHW == BMhKMnDjjM){CSOZwlLMwx = true;}
      else if(BMhKMnDjjM == hkSEiwLfHW){ifJXpVoWCX = true;}
      if(wnMoGuTSXH == DkoVjKybgf){tJODwjSjzu = true;}
      else if(DkoVjKybgf == wnMoGuTSXH){KdtwcSJNoP = true;}
      if(BmWDqaAfKb == yGbPlbZrBA){rUDjyUgAdo = true;}
      else if(yGbPlbZrBA == BmWDqaAfKb){HKHyThKFGT = true;}
      if(jXpWJQrdqJ == LXVVpLDUgI){CeaXSVPRCz = true;}
      else if(LXVVpLDUgI == jXpWJQrdqJ){WfPxwRdcdx = true;}
      if(sFxsbzCNAQ == BoFALRltzC){sayRBRWsyJ = true;}
      else if(BoFALRltzC == sFxsbzCNAQ){pjULbcptza = true;}
      if(eeyzItOPNI == PHjaGtjSXk){WWWEngPdba = true;}
      else if(PHjaGtjSXk == eeyzItOPNI){XeBGdYYKEH = true;}
      if(weVelXxpfo == OLijAePSfY){FLhHuPhpjZ = true;}
      if(DpaOOupcaq == GcuXeIAaDU){TBgzCQWlif = true;}
      if(XlfsxFZpNP == oerykEmtPu){ymBTSeHWil = true;}
      while(OLijAePSfY == weVelXxpfo){KjQhAdNwzK = true;}
      while(GcuXeIAaDU == GcuXeIAaDU){ngjrZWpuWq = true;}
      while(oerykEmtPu == oerykEmtPu){qQFeurdJTX = true;}
      if(akwutoGVAf == true){akwutoGVAf = false;}
      if(CSOZwlLMwx == true){CSOZwlLMwx = false;}
      if(tJODwjSjzu == true){tJODwjSjzu = false;}
      if(rUDjyUgAdo == true){rUDjyUgAdo = false;}
      if(CeaXSVPRCz == true){CeaXSVPRCz = false;}
      if(sayRBRWsyJ == true){sayRBRWsyJ = false;}
      if(WWWEngPdba == true){WWWEngPdba = false;}
      if(FLhHuPhpjZ == true){FLhHuPhpjZ = false;}
      if(TBgzCQWlif == true){TBgzCQWlif = false;}
      if(ymBTSeHWil == true){ymBTSeHWil = false;}
      if(GkpbshspVk == true){GkpbshspVk = false;}
      if(ifJXpVoWCX == true){ifJXpVoWCX = false;}
      if(KdtwcSJNoP == true){KdtwcSJNoP = false;}
      if(HKHyThKFGT == true){HKHyThKFGT = false;}
      if(WfPxwRdcdx == true){WfPxwRdcdx = false;}
      if(pjULbcptza == true){pjULbcptza = false;}
      if(XeBGdYYKEH == true){XeBGdYYKEH = false;}
      if(KjQhAdNwzK == true){KjQhAdNwzK = false;}
      if(ngjrZWpuWq == true){ngjrZWpuWq = false;}
      if(qQFeurdJTX == true){qQFeurdJTX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LGISKEAYGQ
{ 
  void uDRgwjwzax()
  { 
      bool LasxDpDKis = false;
      bool WaLMJBZqVP = false;
      bool uJCzkWNOTZ = false;
      bool bxsdPjpICL = false;
      bool AILqeyFXjM = false;
      bool TNTztCYtMf = false;
      bool copIQZhhxZ = false;
      bool KQnKPmxLUl = false;
      bool QodGFOdsjN = false;
      bool LwwVhKRCZF = false;
      bool PXaKCDYJjG = false;
      bool FMZaPnKjDB = false;
      bool woyiNNURbE = false;
      bool UtkOVsOTDB = false;
      bool pTJcIyWVGt = false;
      bool AhzXJaYrwn = false;
      bool iHgekLbKEV = false;
      bool ZqfCLbfVZP = false;
      bool qzKhDmtNFu = false;
      bool UVWPShldqx = false;
      string RJRLWtYdRg;
      string CiHoVKnZyA;
      string VHMDVSFtsU;
      string NWBAnNYzgT;
      string tVWQlthEng;
      string FoZWiKwNoE;
      string nekwTegHBH;
      string kordGAkuQa;
      string jBGLPXxeQd;
      string QLJceOkZxH;
      string NZDfuPwuQh;
      string ZBwOTmYYgu;
      string hCqXqZePyr;
      string PKxJNJxZPz;
      string aBOhEPOuIr;
      string oLrCZKifoV;
      string kgxXSOEmBK;
      string oyIhTfnITb;
      string LjGGCDStjC;
      string ZRktNtEpPo;
      if(RJRLWtYdRg == NZDfuPwuQh){LasxDpDKis = true;}
      else if(NZDfuPwuQh == RJRLWtYdRg){PXaKCDYJjG = true;}
      if(CiHoVKnZyA == ZBwOTmYYgu){WaLMJBZqVP = true;}
      else if(ZBwOTmYYgu == CiHoVKnZyA){FMZaPnKjDB = true;}
      if(VHMDVSFtsU == hCqXqZePyr){uJCzkWNOTZ = true;}
      else if(hCqXqZePyr == VHMDVSFtsU){woyiNNURbE = true;}
      if(NWBAnNYzgT == PKxJNJxZPz){bxsdPjpICL = true;}
      else if(PKxJNJxZPz == NWBAnNYzgT){UtkOVsOTDB = true;}
      if(tVWQlthEng == aBOhEPOuIr){AILqeyFXjM = true;}
      else if(aBOhEPOuIr == tVWQlthEng){pTJcIyWVGt = true;}
      if(FoZWiKwNoE == oLrCZKifoV){TNTztCYtMf = true;}
      else if(oLrCZKifoV == FoZWiKwNoE){AhzXJaYrwn = true;}
      if(nekwTegHBH == kgxXSOEmBK){copIQZhhxZ = true;}
      else if(kgxXSOEmBK == nekwTegHBH){iHgekLbKEV = true;}
      if(kordGAkuQa == oyIhTfnITb){KQnKPmxLUl = true;}
      if(jBGLPXxeQd == LjGGCDStjC){QodGFOdsjN = true;}
      if(QLJceOkZxH == ZRktNtEpPo){LwwVhKRCZF = true;}
      while(oyIhTfnITb == kordGAkuQa){ZqfCLbfVZP = true;}
      while(LjGGCDStjC == LjGGCDStjC){qzKhDmtNFu = true;}
      while(ZRktNtEpPo == ZRktNtEpPo){UVWPShldqx = true;}
      if(LasxDpDKis == true){LasxDpDKis = false;}
      if(WaLMJBZqVP == true){WaLMJBZqVP = false;}
      if(uJCzkWNOTZ == true){uJCzkWNOTZ = false;}
      if(bxsdPjpICL == true){bxsdPjpICL = false;}
      if(AILqeyFXjM == true){AILqeyFXjM = false;}
      if(TNTztCYtMf == true){TNTztCYtMf = false;}
      if(copIQZhhxZ == true){copIQZhhxZ = false;}
      if(KQnKPmxLUl == true){KQnKPmxLUl = false;}
      if(QodGFOdsjN == true){QodGFOdsjN = false;}
      if(LwwVhKRCZF == true){LwwVhKRCZF = false;}
      if(PXaKCDYJjG == true){PXaKCDYJjG = false;}
      if(FMZaPnKjDB == true){FMZaPnKjDB = false;}
      if(woyiNNURbE == true){woyiNNURbE = false;}
      if(UtkOVsOTDB == true){UtkOVsOTDB = false;}
      if(pTJcIyWVGt == true){pTJcIyWVGt = false;}
      if(AhzXJaYrwn == true){AhzXJaYrwn = false;}
      if(iHgekLbKEV == true){iHgekLbKEV = false;}
      if(ZqfCLbfVZP == true){ZqfCLbfVZP = false;}
      if(qzKhDmtNFu == true){qzKhDmtNFu = false;}
      if(UVWPShldqx == true){UVWPShldqx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RFOSMKKDNX
{ 
  void mwhHPyEHbq()
  { 
      bool zFHGsoFnKJ = false;
      bool QNoxfUYhLT = false;
      bool AulCuyjnVu = false;
      bool sYPEhRLkIq = false;
      bool gcuawQesLU = false;
      bool SORcpDSFKt = false;
      bool FQROQqykPO = false;
      bool InZTlWALGe = false;
      bool SqcBcdHlNd = false;
      bool yGZNlQLfJE = false;
      bool RtcxLeoyqS = false;
      bool CHyeaNmQll = false;
      bool jMWkPCNLgV = false;
      bool LTBBNYOfoy = false;
      bool oJutbpHtlY = false;
      bool cttWUFXqgJ = false;
      bool QcQUHhGxRC = false;
      bool zHamxaRbJZ = false;
      bool tSYIrQZdfI = false;
      bool BWzfgMrZms = false;
      string hcBVOoLQzE;
      string ftybzqzYww;
      string ZsaiAlZipB;
      string QbJzgJEnoy;
      string nmmeabphCq;
      string qWwyQoBRUb;
      string ObZymDjyto;
      string mLjxIlFuIY;
      string wrgzJsfLiq;
      string HlTMiLMnqW;
      string rqmMDfmyoe;
      string iGIwfWuaos;
      string WYPDhAqXNx;
      string YREkfFEUud;
      string GgVDIBcXfL;
      string PlzxATajdD;
      string nPjrGRCXPZ;
      string SafLmpCMtg;
      string WTqBgmRGkM;
      string eTpqoqxcxp;
      if(hcBVOoLQzE == rqmMDfmyoe){zFHGsoFnKJ = true;}
      else if(rqmMDfmyoe == hcBVOoLQzE){RtcxLeoyqS = true;}
      if(ftybzqzYww == iGIwfWuaos){QNoxfUYhLT = true;}
      else if(iGIwfWuaos == ftybzqzYww){CHyeaNmQll = true;}
      if(ZsaiAlZipB == WYPDhAqXNx){AulCuyjnVu = true;}
      else if(WYPDhAqXNx == ZsaiAlZipB){jMWkPCNLgV = true;}
      if(QbJzgJEnoy == YREkfFEUud){sYPEhRLkIq = true;}
      else if(YREkfFEUud == QbJzgJEnoy){LTBBNYOfoy = true;}
      if(nmmeabphCq == GgVDIBcXfL){gcuawQesLU = true;}
      else if(GgVDIBcXfL == nmmeabphCq){oJutbpHtlY = true;}
      if(qWwyQoBRUb == PlzxATajdD){SORcpDSFKt = true;}
      else if(PlzxATajdD == qWwyQoBRUb){cttWUFXqgJ = true;}
      if(ObZymDjyto == nPjrGRCXPZ){FQROQqykPO = true;}
      else if(nPjrGRCXPZ == ObZymDjyto){QcQUHhGxRC = true;}
      if(mLjxIlFuIY == SafLmpCMtg){InZTlWALGe = true;}
      if(wrgzJsfLiq == WTqBgmRGkM){SqcBcdHlNd = true;}
      if(HlTMiLMnqW == eTpqoqxcxp){yGZNlQLfJE = true;}
      while(SafLmpCMtg == mLjxIlFuIY){zHamxaRbJZ = true;}
      while(WTqBgmRGkM == WTqBgmRGkM){tSYIrQZdfI = true;}
      while(eTpqoqxcxp == eTpqoqxcxp){BWzfgMrZms = true;}
      if(zFHGsoFnKJ == true){zFHGsoFnKJ = false;}
      if(QNoxfUYhLT == true){QNoxfUYhLT = false;}
      if(AulCuyjnVu == true){AulCuyjnVu = false;}
      if(sYPEhRLkIq == true){sYPEhRLkIq = false;}
      if(gcuawQesLU == true){gcuawQesLU = false;}
      if(SORcpDSFKt == true){SORcpDSFKt = false;}
      if(FQROQqykPO == true){FQROQqykPO = false;}
      if(InZTlWALGe == true){InZTlWALGe = false;}
      if(SqcBcdHlNd == true){SqcBcdHlNd = false;}
      if(yGZNlQLfJE == true){yGZNlQLfJE = false;}
      if(RtcxLeoyqS == true){RtcxLeoyqS = false;}
      if(CHyeaNmQll == true){CHyeaNmQll = false;}
      if(jMWkPCNLgV == true){jMWkPCNLgV = false;}
      if(LTBBNYOfoy == true){LTBBNYOfoy = false;}
      if(oJutbpHtlY == true){oJutbpHtlY = false;}
      if(cttWUFXqgJ == true){cttWUFXqgJ = false;}
      if(QcQUHhGxRC == true){QcQUHhGxRC = false;}
      if(zHamxaRbJZ == true){zHamxaRbJZ = false;}
      if(tSYIrQZdfI == true){tSYIrQZdfI = false;}
      if(BWzfgMrZms == true){BWzfgMrZms = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RSUIMZHDAB
{ 
  void PkJpPMdfrc()
  { 
      bool YmePBDghlm = false;
      bool SBgUSWMJQs = false;
      bool RpIJGBuHkE = false;
      bool sxWVQPjxfw = false;
      bool WeYcwIijrr = false;
      bool zBXXpheVIz = false;
      bool IZwhsVdLDD = false;
      bool lOcUVlRfNy = false;
      bool SLOrErYyei = false;
      bool kOngnxiqiZ = false;
      bool dWgoGjXCCE = false;
      bool QzIKfwLDcB = false;
      bool wefTSXawgX = false;
      bool DawmUweYlU = false;
      bool UWwaRkFdAq = false;
      bool leNhcypMWh = false;
      bool JaVdApCUpj = false;
      bool RlQHfZiFCg = false;
      bool RwwolXMNJV = false;
      bool FSCELtASZb = false;
      string jJghNPhqlW;
      string payGbnYqYs;
      string iadwYGQbSd;
      string OtMcYVdGCL;
      string YasMrJOLiw;
      string WIDnKJfkIH;
      string yGXIHwOVhG;
      string JRoMUHgQEP;
      string rFrVGFqXRP;
      string osxuMRCkEw;
      string usccmFTpSC;
      string bOgsOsOCBC;
      string EpDRRPTsAC;
      string FwMHTybPiB;
      string lAEOnaMEfS;
      string CAiCqEoLKW;
      string lZpQxeBYYP;
      string RzTAPEkndp;
      string DPNgzENKPP;
      string JPELOLKnRI;
      if(jJghNPhqlW == usccmFTpSC){YmePBDghlm = true;}
      else if(usccmFTpSC == jJghNPhqlW){dWgoGjXCCE = true;}
      if(payGbnYqYs == bOgsOsOCBC){SBgUSWMJQs = true;}
      else if(bOgsOsOCBC == payGbnYqYs){QzIKfwLDcB = true;}
      if(iadwYGQbSd == EpDRRPTsAC){RpIJGBuHkE = true;}
      else if(EpDRRPTsAC == iadwYGQbSd){wefTSXawgX = true;}
      if(OtMcYVdGCL == FwMHTybPiB){sxWVQPjxfw = true;}
      else if(FwMHTybPiB == OtMcYVdGCL){DawmUweYlU = true;}
      if(YasMrJOLiw == lAEOnaMEfS){WeYcwIijrr = true;}
      else if(lAEOnaMEfS == YasMrJOLiw){UWwaRkFdAq = true;}
      if(WIDnKJfkIH == CAiCqEoLKW){zBXXpheVIz = true;}
      else if(CAiCqEoLKW == WIDnKJfkIH){leNhcypMWh = true;}
      if(yGXIHwOVhG == lZpQxeBYYP){IZwhsVdLDD = true;}
      else if(lZpQxeBYYP == yGXIHwOVhG){JaVdApCUpj = true;}
      if(JRoMUHgQEP == RzTAPEkndp){lOcUVlRfNy = true;}
      if(rFrVGFqXRP == DPNgzENKPP){SLOrErYyei = true;}
      if(osxuMRCkEw == JPELOLKnRI){kOngnxiqiZ = true;}
      while(RzTAPEkndp == JRoMUHgQEP){RlQHfZiFCg = true;}
      while(DPNgzENKPP == DPNgzENKPP){RwwolXMNJV = true;}
      while(JPELOLKnRI == JPELOLKnRI){FSCELtASZb = true;}
      if(YmePBDghlm == true){YmePBDghlm = false;}
      if(SBgUSWMJQs == true){SBgUSWMJQs = false;}
      if(RpIJGBuHkE == true){RpIJGBuHkE = false;}
      if(sxWVQPjxfw == true){sxWVQPjxfw = false;}
      if(WeYcwIijrr == true){WeYcwIijrr = false;}
      if(zBXXpheVIz == true){zBXXpheVIz = false;}
      if(IZwhsVdLDD == true){IZwhsVdLDD = false;}
      if(lOcUVlRfNy == true){lOcUVlRfNy = false;}
      if(SLOrErYyei == true){SLOrErYyei = false;}
      if(kOngnxiqiZ == true){kOngnxiqiZ = false;}
      if(dWgoGjXCCE == true){dWgoGjXCCE = false;}
      if(QzIKfwLDcB == true){QzIKfwLDcB = false;}
      if(wefTSXawgX == true){wefTSXawgX = false;}
      if(DawmUweYlU == true){DawmUweYlU = false;}
      if(UWwaRkFdAq == true){UWwaRkFdAq = false;}
      if(leNhcypMWh == true){leNhcypMWh = false;}
      if(JaVdApCUpj == true){JaVdApCUpj = false;}
      if(RlQHfZiFCg == true){RlQHfZiFCg = false;}
      if(RwwolXMNJV == true){RwwolXMNJV = false;}
      if(FSCELtASZb == true){FSCELtASZb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JNBUEWSCAD
{ 
  void gRmemWbUEk()
  { 
      bool PgCTxWxTZf = false;
      bool YyqnMueTIy = false;
      bool qshekeagSH = false;
      bool EAWAPxQMXT = false;
      bool OwybIXPGVy = false;
      bool HBrQSWzXiR = false;
      bool wPBRbXapXO = false;
      bool eRwniutFVM = false;
      bool OULUzDHGhs = false;
      bool ysdFXyufAj = false;
      bool xYhHSoFEgW = false;
      bool csBVCaEfSY = false;
      bool PUIeQlnpPk = false;
      bool ANFkPpmECJ = false;
      bool xDYKQFqICw = false;
      bool sONaTcQCpg = false;
      bool BOnwWOmQFM = false;
      bool nAdIaMuyOK = false;
      bool temSrkzeQm = false;
      bool YjNUHhOcnB = false;
      string nOGLmKFFCM;
      string lQwfTWOJHN;
      string shssDVXdtY;
      string trdZeOptIT;
      string COgilPShkZ;
      string RXjtPGVMIR;
      string mbKcStlVBF;
      string fTAmKeBJHm;
      string DpsTGWIjKX;
      string rdkqgaEDQr;
      string dwfftyWwik;
      string FLFVOwhpVu;
      string kCLdMCiJGj;
      string ZxsOJGJNZI;
      string ALAZSgXObj;
      string rNgUGajCSq;
      string PMpzKHRpMH;
      string mUPMuZBlKe;
      string eTgVqMQYIh;
      string VHtismVBOK;
      if(nOGLmKFFCM == dwfftyWwik){PgCTxWxTZf = true;}
      else if(dwfftyWwik == nOGLmKFFCM){xYhHSoFEgW = true;}
      if(lQwfTWOJHN == FLFVOwhpVu){YyqnMueTIy = true;}
      else if(FLFVOwhpVu == lQwfTWOJHN){csBVCaEfSY = true;}
      if(shssDVXdtY == kCLdMCiJGj){qshekeagSH = true;}
      else if(kCLdMCiJGj == shssDVXdtY){PUIeQlnpPk = true;}
      if(trdZeOptIT == ZxsOJGJNZI){EAWAPxQMXT = true;}
      else if(ZxsOJGJNZI == trdZeOptIT){ANFkPpmECJ = true;}
      if(COgilPShkZ == ALAZSgXObj){OwybIXPGVy = true;}
      else if(ALAZSgXObj == COgilPShkZ){xDYKQFqICw = true;}
      if(RXjtPGVMIR == rNgUGajCSq){HBrQSWzXiR = true;}
      else if(rNgUGajCSq == RXjtPGVMIR){sONaTcQCpg = true;}
      if(mbKcStlVBF == PMpzKHRpMH){wPBRbXapXO = true;}
      else if(PMpzKHRpMH == mbKcStlVBF){BOnwWOmQFM = true;}
      if(fTAmKeBJHm == mUPMuZBlKe){eRwniutFVM = true;}
      if(DpsTGWIjKX == eTgVqMQYIh){OULUzDHGhs = true;}
      if(rdkqgaEDQr == VHtismVBOK){ysdFXyufAj = true;}
      while(mUPMuZBlKe == fTAmKeBJHm){nAdIaMuyOK = true;}
      while(eTgVqMQYIh == eTgVqMQYIh){temSrkzeQm = true;}
      while(VHtismVBOK == VHtismVBOK){YjNUHhOcnB = true;}
      if(PgCTxWxTZf == true){PgCTxWxTZf = false;}
      if(YyqnMueTIy == true){YyqnMueTIy = false;}
      if(qshekeagSH == true){qshekeagSH = false;}
      if(EAWAPxQMXT == true){EAWAPxQMXT = false;}
      if(OwybIXPGVy == true){OwybIXPGVy = false;}
      if(HBrQSWzXiR == true){HBrQSWzXiR = false;}
      if(wPBRbXapXO == true){wPBRbXapXO = false;}
      if(eRwniutFVM == true){eRwniutFVM = false;}
      if(OULUzDHGhs == true){OULUzDHGhs = false;}
      if(ysdFXyufAj == true){ysdFXyufAj = false;}
      if(xYhHSoFEgW == true){xYhHSoFEgW = false;}
      if(csBVCaEfSY == true){csBVCaEfSY = false;}
      if(PUIeQlnpPk == true){PUIeQlnpPk = false;}
      if(ANFkPpmECJ == true){ANFkPpmECJ = false;}
      if(xDYKQFqICw == true){xDYKQFqICw = false;}
      if(sONaTcQCpg == true){sONaTcQCpg = false;}
      if(BOnwWOmQFM == true){BOnwWOmQFM = false;}
      if(nAdIaMuyOK == true){nAdIaMuyOK = false;}
      if(temSrkzeQm == true){temSrkzeQm = false;}
      if(YjNUHhOcnB == true){YjNUHhOcnB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWANBFBWVP
{ 
  void xSQTSfGrtG()
  { 
      bool znixnNiQEF = false;
      bool ghrMmbZHsQ = false;
      bool pnquCtOItJ = false;
      bool JTphuhoghf = false;
      bool aFPzhldweC = false;
      bool bsUFqKxntt = false;
      bool zZVtuNrJRE = false;
      bool mrZNokYqNQ = false;
      bool PRdrhQyjqk = false;
      bool kBmngBiUDT = false;
      bool tTeaPiSHQF = false;
      bool kFaddhwdMe = false;
      bool PHSgSkFkgn = false;
      bool BEmtWulCby = false;
      bool xqTkzeaIJz = false;
      bool EEHYDlByHd = false;
      bool chZcEgSfHi = false;
      bool usBOgXnhhn = false;
      bool KwbhixwNpj = false;
      bool tnuyUPQqgR = false;
      string siGFTsLKco;
      string BIQgPBGObF;
      string mLXNlRxrPW;
      string PXARCLsDIx;
      string wGCGkGAyOX;
      string WHkdahKsTC;
      string uTtFYdHyeE;
      string HCFdJfIRbe;
      string QzcrAHmWpT;
      string BAiGCcMwgH;
      string zBTKPTCGUt;
      string ZsQolwpCFQ;
      string qjHKCGSybf;
      string TMjUeOfRbf;
      string FfCwtHjtUF;
      string lJpPPPtIHJ;
      string BDenZMIuKX;
      string QYaZLKhLPt;
      string WYdWtJVTEP;
      string UWJReBBOVh;
      if(siGFTsLKco == zBTKPTCGUt){znixnNiQEF = true;}
      else if(zBTKPTCGUt == siGFTsLKco){tTeaPiSHQF = true;}
      if(BIQgPBGObF == ZsQolwpCFQ){ghrMmbZHsQ = true;}
      else if(ZsQolwpCFQ == BIQgPBGObF){kFaddhwdMe = true;}
      if(mLXNlRxrPW == qjHKCGSybf){pnquCtOItJ = true;}
      else if(qjHKCGSybf == mLXNlRxrPW){PHSgSkFkgn = true;}
      if(PXARCLsDIx == TMjUeOfRbf){JTphuhoghf = true;}
      else if(TMjUeOfRbf == PXARCLsDIx){BEmtWulCby = true;}
      if(wGCGkGAyOX == FfCwtHjtUF){aFPzhldweC = true;}
      else if(FfCwtHjtUF == wGCGkGAyOX){xqTkzeaIJz = true;}
      if(WHkdahKsTC == lJpPPPtIHJ){bsUFqKxntt = true;}
      else if(lJpPPPtIHJ == WHkdahKsTC){EEHYDlByHd = true;}
      if(uTtFYdHyeE == BDenZMIuKX){zZVtuNrJRE = true;}
      else if(BDenZMIuKX == uTtFYdHyeE){chZcEgSfHi = true;}
      if(HCFdJfIRbe == QYaZLKhLPt){mrZNokYqNQ = true;}
      if(QzcrAHmWpT == WYdWtJVTEP){PRdrhQyjqk = true;}
      if(BAiGCcMwgH == UWJReBBOVh){kBmngBiUDT = true;}
      while(QYaZLKhLPt == HCFdJfIRbe){usBOgXnhhn = true;}
      while(WYdWtJVTEP == WYdWtJVTEP){KwbhixwNpj = true;}
      while(UWJReBBOVh == UWJReBBOVh){tnuyUPQqgR = true;}
      if(znixnNiQEF == true){znixnNiQEF = false;}
      if(ghrMmbZHsQ == true){ghrMmbZHsQ = false;}
      if(pnquCtOItJ == true){pnquCtOItJ = false;}
      if(JTphuhoghf == true){JTphuhoghf = false;}
      if(aFPzhldweC == true){aFPzhldweC = false;}
      if(bsUFqKxntt == true){bsUFqKxntt = false;}
      if(zZVtuNrJRE == true){zZVtuNrJRE = false;}
      if(mrZNokYqNQ == true){mrZNokYqNQ = false;}
      if(PRdrhQyjqk == true){PRdrhQyjqk = false;}
      if(kBmngBiUDT == true){kBmngBiUDT = false;}
      if(tTeaPiSHQF == true){tTeaPiSHQF = false;}
      if(kFaddhwdMe == true){kFaddhwdMe = false;}
      if(PHSgSkFkgn == true){PHSgSkFkgn = false;}
      if(BEmtWulCby == true){BEmtWulCby = false;}
      if(xqTkzeaIJz == true){xqTkzeaIJz = false;}
      if(EEHYDlByHd == true){EEHYDlByHd = false;}
      if(chZcEgSfHi == true){chZcEgSfHi = false;}
      if(usBOgXnhhn == true){usBOgXnhhn = false;}
      if(KwbhixwNpj == true){KwbhixwNpj = false;}
      if(tnuyUPQqgR == true){tnuyUPQqgR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ROMZXUXROL
{ 
  void njWLnqfUkY()
  { 
      bool YaAHbMTMKI = false;
      bool UqqUmKmYGl = false;
      bool edWelusyGj = false;
      bool ZhwfJQTlMN = false;
      bool AnAeNAEaDV = false;
      bool lJTmRtEVVf = false;
      bool SVGahluLKW = false;
      bool pBLslpdrQk = false;
      bool pStjyPOJNP = false;
      bool LyPgtdhZwb = false;
      bool EsPgfjyZAb = false;
      bool QMEkoAbVcR = false;
      bool WlxuKrlezI = false;
      bool HDuofxCNEN = false;
      bool RoIlyzsdqs = false;
      bool CMxdESuTVm = false;
      bool yTaqTMQPEr = false;
      bool yNQOAhdKxK = false;
      bool zHmFGuGQjN = false;
      bool BhqQOyNQSk = false;
      string OJGIGdUFpQ;
      string zcLKoXpbOF;
      string yddRdCedSO;
      string hcwtuMqSZb;
      string iEbRrYgodo;
      string mOJfdjfodE;
      string ypmbiWfRPc;
      string fXBmVtCMZE;
      string UpAdbTSQPK;
      string fCnVcsRAhU;
      string rPYAIPMWJi;
      string hSPZiIpIzP;
      string DPBEwdifJc;
      string cBdELFQAUM;
      string GuGfcNlOlT;
      string CIASQcNTDe;
      string fgNgGfoKNd;
      string rpnmIIIVbi;
      string qUtoZTBKni;
      string rwwpgYhZYw;
      if(OJGIGdUFpQ == rPYAIPMWJi){YaAHbMTMKI = true;}
      else if(rPYAIPMWJi == OJGIGdUFpQ){EsPgfjyZAb = true;}
      if(zcLKoXpbOF == hSPZiIpIzP){UqqUmKmYGl = true;}
      else if(hSPZiIpIzP == zcLKoXpbOF){QMEkoAbVcR = true;}
      if(yddRdCedSO == DPBEwdifJc){edWelusyGj = true;}
      else if(DPBEwdifJc == yddRdCedSO){WlxuKrlezI = true;}
      if(hcwtuMqSZb == cBdELFQAUM){ZhwfJQTlMN = true;}
      else if(cBdELFQAUM == hcwtuMqSZb){HDuofxCNEN = true;}
      if(iEbRrYgodo == GuGfcNlOlT){AnAeNAEaDV = true;}
      else if(GuGfcNlOlT == iEbRrYgodo){RoIlyzsdqs = true;}
      if(mOJfdjfodE == CIASQcNTDe){lJTmRtEVVf = true;}
      else if(CIASQcNTDe == mOJfdjfodE){CMxdESuTVm = true;}
      if(ypmbiWfRPc == fgNgGfoKNd){SVGahluLKW = true;}
      else if(fgNgGfoKNd == ypmbiWfRPc){yTaqTMQPEr = true;}
      if(fXBmVtCMZE == rpnmIIIVbi){pBLslpdrQk = true;}
      if(UpAdbTSQPK == qUtoZTBKni){pStjyPOJNP = true;}
      if(fCnVcsRAhU == rwwpgYhZYw){LyPgtdhZwb = true;}
      while(rpnmIIIVbi == fXBmVtCMZE){yNQOAhdKxK = true;}
      while(qUtoZTBKni == qUtoZTBKni){zHmFGuGQjN = true;}
      while(rwwpgYhZYw == rwwpgYhZYw){BhqQOyNQSk = true;}
      if(YaAHbMTMKI == true){YaAHbMTMKI = false;}
      if(UqqUmKmYGl == true){UqqUmKmYGl = false;}
      if(edWelusyGj == true){edWelusyGj = false;}
      if(ZhwfJQTlMN == true){ZhwfJQTlMN = false;}
      if(AnAeNAEaDV == true){AnAeNAEaDV = false;}
      if(lJTmRtEVVf == true){lJTmRtEVVf = false;}
      if(SVGahluLKW == true){SVGahluLKW = false;}
      if(pBLslpdrQk == true){pBLslpdrQk = false;}
      if(pStjyPOJNP == true){pStjyPOJNP = false;}
      if(LyPgtdhZwb == true){LyPgtdhZwb = false;}
      if(EsPgfjyZAb == true){EsPgfjyZAb = false;}
      if(QMEkoAbVcR == true){QMEkoAbVcR = false;}
      if(WlxuKrlezI == true){WlxuKrlezI = false;}
      if(HDuofxCNEN == true){HDuofxCNEN = false;}
      if(RoIlyzsdqs == true){RoIlyzsdqs = false;}
      if(CMxdESuTVm == true){CMxdESuTVm = false;}
      if(yTaqTMQPEr == true){yTaqTMQPEr = false;}
      if(yNQOAhdKxK == true){yNQOAhdKxK = false;}
      if(zHmFGuGQjN == true){zHmFGuGQjN = false;}
      if(BhqQOyNQSk == true){BhqQOyNQSk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKPGJTMWCD
{ 
  void cVfSNPHKnH()
  { 
      bool McXHOlGnEi = false;
      bool gatToNQkwJ = false;
      bool shXfooIzHU = false;
      bool ZNjXDdhclt = false;
      bool EZKqzOkIBo = false;
      bool piuSxdFqRY = false;
      bool cHfiISpVPK = false;
      bool enyCETWgga = false;
      bool EAySdqSQaZ = false;
      bool YqKNQxsaig = false;
      bool YOspKCkrOd = false;
      bool HXKqUcJNER = false;
      bool AYuplnckkG = false;
      bool auyzBoGHHb = false;
      bool FZCxSAfTrn = false;
      bool neWQfzTDEV = false;
      bool ZAHHDLZKoe = false;
      bool VBFcLZWxXk = false;
      bool HJrxSuYgSC = false;
      bool VDDlCFSttH = false;
      string CtdeEVlBJi;
      string HigMnTmzjS;
      string GmosSRFPFx;
      string UcHrhIKdgH;
      string rWrdKmnyqm;
      string RozGOPEjMl;
      string PWwLOeaode;
      string IIRbZjtLie;
      string cHYReecBcS;
      string DaRuqVafPe;
      string LzTLdJXWge;
      string UsAgIIydgi;
      string BZLLagpWjE;
      string INuDTdmMmV;
      string HGTyxKZkli;
      string XxzfdlnIjw;
      string SAlcVHxxNe;
      string UkpKbuFNNQ;
      string HFjBfLNPZg;
      string oebqCGUqcp;
      if(CtdeEVlBJi == LzTLdJXWge){McXHOlGnEi = true;}
      else if(LzTLdJXWge == CtdeEVlBJi){YOspKCkrOd = true;}
      if(HigMnTmzjS == UsAgIIydgi){gatToNQkwJ = true;}
      else if(UsAgIIydgi == HigMnTmzjS){HXKqUcJNER = true;}
      if(GmosSRFPFx == BZLLagpWjE){shXfooIzHU = true;}
      else if(BZLLagpWjE == GmosSRFPFx){AYuplnckkG = true;}
      if(UcHrhIKdgH == INuDTdmMmV){ZNjXDdhclt = true;}
      else if(INuDTdmMmV == UcHrhIKdgH){auyzBoGHHb = true;}
      if(rWrdKmnyqm == HGTyxKZkli){EZKqzOkIBo = true;}
      else if(HGTyxKZkli == rWrdKmnyqm){FZCxSAfTrn = true;}
      if(RozGOPEjMl == XxzfdlnIjw){piuSxdFqRY = true;}
      else if(XxzfdlnIjw == RozGOPEjMl){neWQfzTDEV = true;}
      if(PWwLOeaode == SAlcVHxxNe){cHfiISpVPK = true;}
      else if(SAlcVHxxNe == PWwLOeaode){ZAHHDLZKoe = true;}
      if(IIRbZjtLie == UkpKbuFNNQ){enyCETWgga = true;}
      if(cHYReecBcS == HFjBfLNPZg){EAySdqSQaZ = true;}
      if(DaRuqVafPe == oebqCGUqcp){YqKNQxsaig = true;}
      while(UkpKbuFNNQ == IIRbZjtLie){VBFcLZWxXk = true;}
      while(HFjBfLNPZg == HFjBfLNPZg){HJrxSuYgSC = true;}
      while(oebqCGUqcp == oebqCGUqcp){VDDlCFSttH = true;}
      if(McXHOlGnEi == true){McXHOlGnEi = false;}
      if(gatToNQkwJ == true){gatToNQkwJ = false;}
      if(shXfooIzHU == true){shXfooIzHU = false;}
      if(ZNjXDdhclt == true){ZNjXDdhclt = false;}
      if(EZKqzOkIBo == true){EZKqzOkIBo = false;}
      if(piuSxdFqRY == true){piuSxdFqRY = false;}
      if(cHfiISpVPK == true){cHfiISpVPK = false;}
      if(enyCETWgga == true){enyCETWgga = false;}
      if(EAySdqSQaZ == true){EAySdqSQaZ = false;}
      if(YqKNQxsaig == true){YqKNQxsaig = false;}
      if(YOspKCkrOd == true){YOspKCkrOd = false;}
      if(HXKqUcJNER == true){HXKqUcJNER = false;}
      if(AYuplnckkG == true){AYuplnckkG = false;}
      if(auyzBoGHHb == true){auyzBoGHHb = false;}
      if(FZCxSAfTrn == true){FZCxSAfTrn = false;}
      if(neWQfzTDEV == true){neWQfzTDEV = false;}
      if(ZAHHDLZKoe == true){ZAHHDLZKoe = false;}
      if(VBFcLZWxXk == true){VBFcLZWxXk = false;}
      if(HJrxSuYgSC == true){HJrxSuYgSC = false;}
      if(VDDlCFSttH == true){VDDlCFSttH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UCBDLKRFTR
{ 
  void CpZiukmdXe()
  { 
      bool bXbqOZPRiF = false;
      bool lCftJcTwzN = false;
      bool mUfPIJUzhy = false;
      bool OPnyZdwMTV = false;
      bool qLuzsyBQaa = false;
      bool ubRyIHqLiF = false;
      bool EQjjqWNhUf = false;
      bool gHbdVbZfWJ = false;
      bool HEYGDmxpoR = false;
      bool ljdNQabKIW = false;
      bool kTwutnzncg = false;
      bool hKoYxAqcgE = false;
      bool YXsCswdOMt = false;
      bool AOXAYnHdMO = false;
      bool mJMIjatEPP = false;
      bool iycDxMasBx = false;
      bool KkahgSloAJ = false;
      bool sNPRQOKkSR = false;
      bool CYyxKBkUCL = false;
      bool NObOECidbR = false;
      string yqqyYxyjEk;
      string ESWLYImmBM;
      string QVsbnUBenK;
      string QqJcpxGaSD;
      string ObqTwYeGzW;
      string IySwRcyOKD;
      string uTwtTNIsVa;
      string BLTxxndZfP;
      string ptfQBRXMLM;
      string zqQOHufwzh;
      string PkkXUwdUzd;
      string yYitNBnfrC;
      string ouhJbJtFoC;
      string HhaxzEJHuF;
      string nDNhNZIWBG;
      string GAEwrTDbwK;
      string BYewVQykuJ;
      string qfjlNlhAuB;
      string BXEiwHcdFe;
      string BhLjEPXRMw;
      if(yqqyYxyjEk == PkkXUwdUzd){bXbqOZPRiF = true;}
      else if(PkkXUwdUzd == yqqyYxyjEk){kTwutnzncg = true;}
      if(ESWLYImmBM == yYitNBnfrC){lCftJcTwzN = true;}
      else if(yYitNBnfrC == ESWLYImmBM){hKoYxAqcgE = true;}
      if(QVsbnUBenK == ouhJbJtFoC){mUfPIJUzhy = true;}
      else if(ouhJbJtFoC == QVsbnUBenK){YXsCswdOMt = true;}
      if(QqJcpxGaSD == HhaxzEJHuF){OPnyZdwMTV = true;}
      else if(HhaxzEJHuF == QqJcpxGaSD){AOXAYnHdMO = true;}
      if(ObqTwYeGzW == nDNhNZIWBG){qLuzsyBQaa = true;}
      else if(nDNhNZIWBG == ObqTwYeGzW){mJMIjatEPP = true;}
      if(IySwRcyOKD == GAEwrTDbwK){ubRyIHqLiF = true;}
      else if(GAEwrTDbwK == IySwRcyOKD){iycDxMasBx = true;}
      if(uTwtTNIsVa == BYewVQykuJ){EQjjqWNhUf = true;}
      else if(BYewVQykuJ == uTwtTNIsVa){KkahgSloAJ = true;}
      if(BLTxxndZfP == qfjlNlhAuB){gHbdVbZfWJ = true;}
      if(ptfQBRXMLM == BXEiwHcdFe){HEYGDmxpoR = true;}
      if(zqQOHufwzh == BhLjEPXRMw){ljdNQabKIW = true;}
      while(qfjlNlhAuB == BLTxxndZfP){sNPRQOKkSR = true;}
      while(BXEiwHcdFe == BXEiwHcdFe){CYyxKBkUCL = true;}
      while(BhLjEPXRMw == BhLjEPXRMw){NObOECidbR = true;}
      if(bXbqOZPRiF == true){bXbqOZPRiF = false;}
      if(lCftJcTwzN == true){lCftJcTwzN = false;}
      if(mUfPIJUzhy == true){mUfPIJUzhy = false;}
      if(OPnyZdwMTV == true){OPnyZdwMTV = false;}
      if(qLuzsyBQaa == true){qLuzsyBQaa = false;}
      if(ubRyIHqLiF == true){ubRyIHqLiF = false;}
      if(EQjjqWNhUf == true){EQjjqWNhUf = false;}
      if(gHbdVbZfWJ == true){gHbdVbZfWJ = false;}
      if(HEYGDmxpoR == true){HEYGDmxpoR = false;}
      if(ljdNQabKIW == true){ljdNQabKIW = false;}
      if(kTwutnzncg == true){kTwutnzncg = false;}
      if(hKoYxAqcgE == true){hKoYxAqcgE = false;}
      if(YXsCswdOMt == true){YXsCswdOMt = false;}
      if(AOXAYnHdMO == true){AOXAYnHdMO = false;}
      if(mJMIjatEPP == true){mJMIjatEPP = false;}
      if(iycDxMasBx == true){iycDxMasBx = false;}
      if(KkahgSloAJ == true){KkahgSloAJ = false;}
      if(sNPRQOKkSR == true){sNPRQOKkSR = false;}
      if(CYyxKBkUCL == true){CYyxKBkUCL = false;}
      if(NObOECidbR == true){NObOECidbR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DVPJLTZHJP
{ 
  void MKTfTasiIJ()
  { 
      bool wCjxTNOXrh = false;
      bool LGLPpywVQC = false;
      bool glLspuyOcG = false;
      bool OknaIllmUe = false;
      bool qdYbUtNqNj = false;
      bool TzBNTKqqHY = false;
      bool PztkSaSkGE = false;
      bool MIBkKCMiYw = false;
      bool gHBrlPjZHy = false;
      bool uufwPqimIs = false;
      bool acjJXLyQCQ = false;
      bool xHRLqHyCzD = false;
      bool qsdIIQbFUT = false;
      bool TYaeUEWrTa = false;
      bool QTXpAndUEH = false;
      bool sgnFChybAH = false;
      bool isuiwXglpl = false;
      bool kFhYlXUmHU = false;
      bool mHAMZmkUcm = false;
      bool GurMqXXntb = false;
      string YYAUcMAXHI;
      string EBhVXNKLWp;
      string hRZnJcSRwe;
      string hPamJigtrS;
      string gKdKZTfIPX;
      string UbseTGzLLA;
      string shabanatLo;
      string gQTEJXmPNo;
      string wKCYKGWwTC;
      string iUhrYyiBik;
      string skwapEIoUw;
      string TixWDifBRU;
      string RdaJFLhaeL;
      string nkfcwLNaiF;
      string xgaXiAWLop;
      string RhjOSOKmUe;
      string VgKJIhDUaq;
      string VESMWkCDaF;
      string nWknsGBQJg;
      string BZGDiPVRPA;
      if(YYAUcMAXHI == skwapEIoUw){wCjxTNOXrh = true;}
      else if(skwapEIoUw == YYAUcMAXHI){acjJXLyQCQ = true;}
      if(EBhVXNKLWp == TixWDifBRU){LGLPpywVQC = true;}
      else if(TixWDifBRU == EBhVXNKLWp){xHRLqHyCzD = true;}
      if(hRZnJcSRwe == RdaJFLhaeL){glLspuyOcG = true;}
      else if(RdaJFLhaeL == hRZnJcSRwe){qsdIIQbFUT = true;}
      if(hPamJigtrS == nkfcwLNaiF){OknaIllmUe = true;}
      else if(nkfcwLNaiF == hPamJigtrS){TYaeUEWrTa = true;}
      if(gKdKZTfIPX == xgaXiAWLop){qdYbUtNqNj = true;}
      else if(xgaXiAWLop == gKdKZTfIPX){QTXpAndUEH = true;}
      if(UbseTGzLLA == RhjOSOKmUe){TzBNTKqqHY = true;}
      else if(RhjOSOKmUe == UbseTGzLLA){sgnFChybAH = true;}
      if(shabanatLo == VgKJIhDUaq){PztkSaSkGE = true;}
      else if(VgKJIhDUaq == shabanatLo){isuiwXglpl = true;}
      if(gQTEJXmPNo == VESMWkCDaF){MIBkKCMiYw = true;}
      if(wKCYKGWwTC == nWknsGBQJg){gHBrlPjZHy = true;}
      if(iUhrYyiBik == BZGDiPVRPA){uufwPqimIs = true;}
      while(VESMWkCDaF == gQTEJXmPNo){kFhYlXUmHU = true;}
      while(nWknsGBQJg == nWknsGBQJg){mHAMZmkUcm = true;}
      while(BZGDiPVRPA == BZGDiPVRPA){GurMqXXntb = true;}
      if(wCjxTNOXrh == true){wCjxTNOXrh = false;}
      if(LGLPpywVQC == true){LGLPpywVQC = false;}
      if(glLspuyOcG == true){glLspuyOcG = false;}
      if(OknaIllmUe == true){OknaIllmUe = false;}
      if(qdYbUtNqNj == true){qdYbUtNqNj = false;}
      if(TzBNTKqqHY == true){TzBNTKqqHY = false;}
      if(PztkSaSkGE == true){PztkSaSkGE = false;}
      if(MIBkKCMiYw == true){MIBkKCMiYw = false;}
      if(gHBrlPjZHy == true){gHBrlPjZHy = false;}
      if(uufwPqimIs == true){uufwPqimIs = false;}
      if(acjJXLyQCQ == true){acjJXLyQCQ = false;}
      if(xHRLqHyCzD == true){xHRLqHyCzD = false;}
      if(qsdIIQbFUT == true){qsdIIQbFUT = false;}
      if(TYaeUEWrTa == true){TYaeUEWrTa = false;}
      if(QTXpAndUEH == true){QTXpAndUEH = false;}
      if(sgnFChybAH == true){sgnFChybAH = false;}
      if(isuiwXglpl == true){isuiwXglpl = false;}
      if(kFhYlXUmHU == true){kFhYlXUmHU = false;}
      if(mHAMZmkUcm == true){mHAMZmkUcm = false;}
      if(GurMqXXntb == true){GurMqXXntb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TLGHHARQFV
{ 
  void EBUxAaJpXw()
  { 
      bool WWEgZdMcTJ = false;
      bool OWIVxWIdtm = false;
      bool JPzdqhRuDz = false;
      bool BNPUgbtNjj = false;
      bool CzbHwcHgbV = false;
      bool UfZVqHXaor = false;
      bool LRYTHBGmnU = false;
      bool cusKkJmrhO = false;
      bool ZkThdVmtdZ = false;
      bool ETXrYkZIzt = false;
      bool VUsGrZlPkg = false;
      bool UeraRZypol = false;
      bool NMIOQJXBlz = false;
      bool jesmrFrMpE = false;
      bool jXIxEYaway = false;
      bool miSMgIMeoi = false;
      bool CjdkwpkEiL = false;
      bool hkAkCpEKJq = false;
      bool haamMALgGi = false;
      bool sNXGCztWAO = false;
      string kWmmbeVLRH;
      string TbgnTjpyqr;
      string kJSVaLFgRe;
      string uqWgDrHEYq;
      string jQWSGLhXpM;
      string BtWaTaEQMP;
      string ZotmLcFzka;
      string clZzHTlzOO;
      string dgqEcBTuMb;
      string mprIQuWjGc;
      string GhmOiPTWTA;
      string oECxlrxoKK;
      string IJlInmsQiL;
      string xCrkHutcUN;
      string gxbMmintWY;
      string ygZwUwwdZw;
      string VDnHDlLQop;
      string yUTwcKhZVE;
      string zytJNPcwQL;
      string zPCYrdJTJA;
      if(kWmmbeVLRH == GhmOiPTWTA){WWEgZdMcTJ = true;}
      else if(GhmOiPTWTA == kWmmbeVLRH){VUsGrZlPkg = true;}
      if(TbgnTjpyqr == oECxlrxoKK){OWIVxWIdtm = true;}
      else if(oECxlrxoKK == TbgnTjpyqr){UeraRZypol = true;}
      if(kJSVaLFgRe == IJlInmsQiL){JPzdqhRuDz = true;}
      else if(IJlInmsQiL == kJSVaLFgRe){NMIOQJXBlz = true;}
      if(uqWgDrHEYq == xCrkHutcUN){BNPUgbtNjj = true;}
      else if(xCrkHutcUN == uqWgDrHEYq){jesmrFrMpE = true;}
      if(jQWSGLhXpM == gxbMmintWY){CzbHwcHgbV = true;}
      else if(gxbMmintWY == jQWSGLhXpM){jXIxEYaway = true;}
      if(BtWaTaEQMP == ygZwUwwdZw){UfZVqHXaor = true;}
      else if(ygZwUwwdZw == BtWaTaEQMP){miSMgIMeoi = true;}
      if(ZotmLcFzka == VDnHDlLQop){LRYTHBGmnU = true;}
      else if(VDnHDlLQop == ZotmLcFzka){CjdkwpkEiL = true;}
      if(clZzHTlzOO == yUTwcKhZVE){cusKkJmrhO = true;}
      if(dgqEcBTuMb == zytJNPcwQL){ZkThdVmtdZ = true;}
      if(mprIQuWjGc == zPCYrdJTJA){ETXrYkZIzt = true;}
      while(yUTwcKhZVE == clZzHTlzOO){hkAkCpEKJq = true;}
      while(zytJNPcwQL == zytJNPcwQL){haamMALgGi = true;}
      while(zPCYrdJTJA == zPCYrdJTJA){sNXGCztWAO = true;}
      if(WWEgZdMcTJ == true){WWEgZdMcTJ = false;}
      if(OWIVxWIdtm == true){OWIVxWIdtm = false;}
      if(JPzdqhRuDz == true){JPzdqhRuDz = false;}
      if(BNPUgbtNjj == true){BNPUgbtNjj = false;}
      if(CzbHwcHgbV == true){CzbHwcHgbV = false;}
      if(UfZVqHXaor == true){UfZVqHXaor = false;}
      if(LRYTHBGmnU == true){LRYTHBGmnU = false;}
      if(cusKkJmrhO == true){cusKkJmrhO = false;}
      if(ZkThdVmtdZ == true){ZkThdVmtdZ = false;}
      if(ETXrYkZIzt == true){ETXrYkZIzt = false;}
      if(VUsGrZlPkg == true){VUsGrZlPkg = false;}
      if(UeraRZypol == true){UeraRZypol = false;}
      if(NMIOQJXBlz == true){NMIOQJXBlz = false;}
      if(jesmrFrMpE == true){jesmrFrMpE = false;}
      if(jXIxEYaway == true){jXIxEYaway = false;}
      if(miSMgIMeoi == true){miSMgIMeoi = false;}
      if(CjdkwpkEiL == true){CjdkwpkEiL = false;}
      if(hkAkCpEKJq == true){hkAkCpEKJq = false;}
      if(haamMALgGi == true){haamMALgGi = false;}
      if(sNXGCztWAO == true){sNXGCztWAO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEDIGCLMNS
{ 
  void gzULepnrbL()
  { 
      bool cTzYtIktzY = false;
      bool uSHrtbSkIO = false;
      bool kCalyNuzfI = false;
      bool NsEWCRlPLC = false;
      bool SJCcOKsgUU = false;
      bool WinYHasMag = false;
      bool MkOpKCNjoc = false;
      bool pDZGuaAyXn = false;
      bool TNdLleEfOb = false;
      bool YYneohtLSL = false;
      bool wIrrdSJhcg = false;
      bool ZtolMzHCDf = false;
      bool yhVMEROtQN = false;
      bool fnfMrKVlgT = false;
      bool UVChCdjBSp = false;
      bool arIlMNmemM = false;
      bool DPRPAkObtB = false;
      bool cUViKcfmKa = false;
      bool gNbZmnfszd = false;
      bool XqyTQFDmhQ = false;
      string JYiGIoZWYj;
      string FHwEfFwnmm;
      string CBbhWqJVxb;
      string unWSHgkYhb;
      string BkKiUfpQkj;
      string TBTunIwAjR;
      string fEYxoQjdwy;
      string TWFLlQpsNq;
      string ArkMHsUbdz;
      string kjoQwxMNsD;
      string uLTlPwwHJW;
      string RDmrQmTLou;
      string wIAxNihnPo;
      string EczJwoXywL;
      string xMRHhgxwAI;
      string dAYxHlLWYg;
      string NHrUSoEcwa;
      string OUPdyipsPf;
      string llnGLDEBBJ;
      string cBZPxoUxnr;
      if(JYiGIoZWYj == uLTlPwwHJW){cTzYtIktzY = true;}
      else if(uLTlPwwHJW == JYiGIoZWYj){wIrrdSJhcg = true;}
      if(FHwEfFwnmm == RDmrQmTLou){uSHrtbSkIO = true;}
      else if(RDmrQmTLou == FHwEfFwnmm){ZtolMzHCDf = true;}
      if(CBbhWqJVxb == wIAxNihnPo){kCalyNuzfI = true;}
      else if(wIAxNihnPo == CBbhWqJVxb){yhVMEROtQN = true;}
      if(unWSHgkYhb == EczJwoXywL){NsEWCRlPLC = true;}
      else if(EczJwoXywL == unWSHgkYhb){fnfMrKVlgT = true;}
      if(BkKiUfpQkj == xMRHhgxwAI){SJCcOKsgUU = true;}
      else if(xMRHhgxwAI == BkKiUfpQkj){UVChCdjBSp = true;}
      if(TBTunIwAjR == dAYxHlLWYg){WinYHasMag = true;}
      else if(dAYxHlLWYg == TBTunIwAjR){arIlMNmemM = true;}
      if(fEYxoQjdwy == NHrUSoEcwa){MkOpKCNjoc = true;}
      else if(NHrUSoEcwa == fEYxoQjdwy){DPRPAkObtB = true;}
      if(TWFLlQpsNq == OUPdyipsPf){pDZGuaAyXn = true;}
      if(ArkMHsUbdz == llnGLDEBBJ){TNdLleEfOb = true;}
      if(kjoQwxMNsD == cBZPxoUxnr){YYneohtLSL = true;}
      while(OUPdyipsPf == TWFLlQpsNq){cUViKcfmKa = true;}
      while(llnGLDEBBJ == llnGLDEBBJ){gNbZmnfszd = true;}
      while(cBZPxoUxnr == cBZPxoUxnr){XqyTQFDmhQ = true;}
      if(cTzYtIktzY == true){cTzYtIktzY = false;}
      if(uSHrtbSkIO == true){uSHrtbSkIO = false;}
      if(kCalyNuzfI == true){kCalyNuzfI = false;}
      if(NsEWCRlPLC == true){NsEWCRlPLC = false;}
      if(SJCcOKsgUU == true){SJCcOKsgUU = false;}
      if(WinYHasMag == true){WinYHasMag = false;}
      if(MkOpKCNjoc == true){MkOpKCNjoc = false;}
      if(pDZGuaAyXn == true){pDZGuaAyXn = false;}
      if(TNdLleEfOb == true){TNdLleEfOb = false;}
      if(YYneohtLSL == true){YYneohtLSL = false;}
      if(wIrrdSJhcg == true){wIrrdSJhcg = false;}
      if(ZtolMzHCDf == true){ZtolMzHCDf = false;}
      if(yhVMEROtQN == true){yhVMEROtQN = false;}
      if(fnfMrKVlgT == true){fnfMrKVlgT = false;}
      if(UVChCdjBSp == true){UVChCdjBSp = false;}
      if(arIlMNmemM == true){arIlMNmemM = false;}
      if(DPRPAkObtB == true){DPRPAkObtB = false;}
      if(cUViKcfmKa == true){cUViKcfmKa = false;}
      if(gNbZmnfszd == true){gNbZmnfszd = false;}
      if(XqyTQFDmhQ == true){XqyTQFDmhQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WIOQKTKVUY
{ 
  void iiLJeFjeoA()
  { 
      bool tNuAVRUDMJ = false;
      bool xGGUUDnjVx = false;
      bool IUGzGAsyZt = false;
      bool tJaaKaSGNy = false;
      bool mxlzNXAZga = false;
      bool bsZVEYGutU = false;
      bool YVcSOnfeKs = false;
      bool jgWWJLhHlh = false;
      bool ATRySBiEWk = false;
      bool TXMrZRTTjY = false;
      bool rVOmqtVDMr = false;
      bool pzJLUEEdAN = false;
      bool EaHYYMUdxr = false;
      bool qOXModEdHX = false;
      bool ffrdtUNAWV = false;
      bool MpTWURNoNd = false;
      bool ZqGUBbaxWp = false;
      bool zZVbgYhddE = false;
      bool zTGaeAtBqW = false;
      bool QOQcynZXcS = false;
      string CjHNRWGXGD;
      string RWeVptLWCb;
      string uQbDgxHiVU;
      string jOpDYOoMYB;
      string nixLHYuBUg;
      string kkhxukHDgU;
      string OXBlTCgaxa;
      string EzxAmLTPwH;
      string BFOniyfrHm;
      string HkeEmPhLrE;
      string rUEsclnhJi;
      string RrHZSIJMCU;
      string VnSJTSTsNX;
      string dIWqOgBULx;
      string KyhYVOdFld;
      string GVIWhDBtZJ;
      string RtUlFIUPKl;
      string HnAFKXFtnE;
      string oOGjQIAzJL;
      string eGuBePcwSM;
      if(CjHNRWGXGD == rUEsclnhJi){tNuAVRUDMJ = true;}
      else if(rUEsclnhJi == CjHNRWGXGD){rVOmqtVDMr = true;}
      if(RWeVptLWCb == RrHZSIJMCU){xGGUUDnjVx = true;}
      else if(RrHZSIJMCU == RWeVptLWCb){pzJLUEEdAN = true;}
      if(uQbDgxHiVU == VnSJTSTsNX){IUGzGAsyZt = true;}
      else if(VnSJTSTsNX == uQbDgxHiVU){EaHYYMUdxr = true;}
      if(jOpDYOoMYB == dIWqOgBULx){tJaaKaSGNy = true;}
      else if(dIWqOgBULx == jOpDYOoMYB){qOXModEdHX = true;}
      if(nixLHYuBUg == KyhYVOdFld){mxlzNXAZga = true;}
      else if(KyhYVOdFld == nixLHYuBUg){ffrdtUNAWV = true;}
      if(kkhxukHDgU == GVIWhDBtZJ){bsZVEYGutU = true;}
      else if(GVIWhDBtZJ == kkhxukHDgU){MpTWURNoNd = true;}
      if(OXBlTCgaxa == RtUlFIUPKl){YVcSOnfeKs = true;}
      else if(RtUlFIUPKl == OXBlTCgaxa){ZqGUBbaxWp = true;}
      if(EzxAmLTPwH == HnAFKXFtnE){jgWWJLhHlh = true;}
      if(BFOniyfrHm == oOGjQIAzJL){ATRySBiEWk = true;}
      if(HkeEmPhLrE == eGuBePcwSM){TXMrZRTTjY = true;}
      while(HnAFKXFtnE == EzxAmLTPwH){zZVbgYhddE = true;}
      while(oOGjQIAzJL == oOGjQIAzJL){zTGaeAtBqW = true;}
      while(eGuBePcwSM == eGuBePcwSM){QOQcynZXcS = true;}
      if(tNuAVRUDMJ == true){tNuAVRUDMJ = false;}
      if(xGGUUDnjVx == true){xGGUUDnjVx = false;}
      if(IUGzGAsyZt == true){IUGzGAsyZt = false;}
      if(tJaaKaSGNy == true){tJaaKaSGNy = false;}
      if(mxlzNXAZga == true){mxlzNXAZga = false;}
      if(bsZVEYGutU == true){bsZVEYGutU = false;}
      if(YVcSOnfeKs == true){YVcSOnfeKs = false;}
      if(jgWWJLhHlh == true){jgWWJLhHlh = false;}
      if(ATRySBiEWk == true){ATRySBiEWk = false;}
      if(TXMrZRTTjY == true){TXMrZRTTjY = false;}
      if(rVOmqtVDMr == true){rVOmqtVDMr = false;}
      if(pzJLUEEdAN == true){pzJLUEEdAN = false;}
      if(EaHYYMUdxr == true){EaHYYMUdxr = false;}
      if(qOXModEdHX == true){qOXModEdHX = false;}
      if(ffrdtUNAWV == true){ffrdtUNAWV = false;}
      if(MpTWURNoNd == true){MpTWURNoNd = false;}
      if(ZqGUBbaxWp == true){ZqGUBbaxWp = false;}
      if(zZVbgYhddE == true){zZVbgYhddE = false;}
      if(zTGaeAtBqW == true){zTGaeAtBqW = false;}
      if(QOQcynZXcS == true){QOQcynZXcS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FTHDALTCCU
{ 
  void ybTWgZIDWL()
  { 
      bool llCcighlpZ = false;
      bool tKKBbixQlr = false;
      bool CbeYyfnCgl = false;
      bool zQLUuPbwHh = false;
      bool fxTNAJffWL = false;
      bool PVgCmJGddD = false;
      bool seFEadyoGM = false;
      bool GAIDLFIRXn = false;
      bool zHeUVciJhk = false;
      bool IyREoBqPlW = false;
      bool LpZKEPNcqg = false;
      bool AoFpDkzjhy = false;
      bool toHUDIhDOK = false;
      bool OseAcJhUQG = false;
      bool OGRAkTrbBD = false;
      bool BGgncViEGw = false;
      bool gKOfSHJEMt = false;
      bool CeTbimWHjj = false;
      bool PGBKIHLqXH = false;
      bool ZdOTZErkgc = false;
      string gdXrPmFWKI;
      string NWpurNjpau;
      string YAPMoziMcD;
      string tjYbsaiSRr;
      string jJEnUgnLGO;
      string fQlgUfOKCQ;
      string EstGNcxOBR;
      string eRXiLOuaqI;
      string LWFNWdxqGN;
      string LXPBmqPxZq;
      string iYKnjOsDVF;
      string jmSsFhmfjj;
      string fFHnFGBVwT;
      string yxAzYlLQcI;
      string jtVBcYFWwE;
      string DjNpLdQVid;
      string NWHCGlmSTS;
      string VVCazkjGLg;
      string BeZqPOjKnu;
      string UphztNlStp;
      if(gdXrPmFWKI == iYKnjOsDVF){llCcighlpZ = true;}
      else if(iYKnjOsDVF == gdXrPmFWKI){LpZKEPNcqg = true;}
      if(NWpurNjpau == jmSsFhmfjj){tKKBbixQlr = true;}
      else if(jmSsFhmfjj == NWpurNjpau){AoFpDkzjhy = true;}
      if(YAPMoziMcD == fFHnFGBVwT){CbeYyfnCgl = true;}
      else if(fFHnFGBVwT == YAPMoziMcD){toHUDIhDOK = true;}
      if(tjYbsaiSRr == yxAzYlLQcI){zQLUuPbwHh = true;}
      else if(yxAzYlLQcI == tjYbsaiSRr){OseAcJhUQG = true;}
      if(jJEnUgnLGO == jtVBcYFWwE){fxTNAJffWL = true;}
      else if(jtVBcYFWwE == jJEnUgnLGO){OGRAkTrbBD = true;}
      if(fQlgUfOKCQ == DjNpLdQVid){PVgCmJGddD = true;}
      else if(DjNpLdQVid == fQlgUfOKCQ){BGgncViEGw = true;}
      if(EstGNcxOBR == NWHCGlmSTS){seFEadyoGM = true;}
      else if(NWHCGlmSTS == EstGNcxOBR){gKOfSHJEMt = true;}
      if(eRXiLOuaqI == VVCazkjGLg){GAIDLFIRXn = true;}
      if(LWFNWdxqGN == BeZqPOjKnu){zHeUVciJhk = true;}
      if(LXPBmqPxZq == UphztNlStp){IyREoBqPlW = true;}
      while(VVCazkjGLg == eRXiLOuaqI){CeTbimWHjj = true;}
      while(BeZqPOjKnu == BeZqPOjKnu){PGBKIHLqXH = true;}
      while(UphztNlStp == UphztNlStp){ZdOTZErkgc = true;}
      if(llCcighlpZ == true){llCcighlpZ = false;}
      if(tKKBbixQlr == true){tKKBbixQlr = false;}
      if(CbeYyfnCgl == true){CbeYyfnCgl = false;}
      if(zQLUuPbwHh == true){zQLUuPbwHh = false;}
      if(fxTNAJffWL == true){fxTNAJffWL = false;}
      if(PVgCmJGddD == true){PVgCmJGddD = false;}
      if(seFEadyoGM == true){seFEadyoGM = false;}
      if(GAIDLFIRXn == true){GAIDLFIRXn = false;}
      if(zHeUVciJhk == true){zHeUVciJhk = false;}
      if(IyREoBqPlW == true){IyREoBqPlW = false;}
      if(LpZKEPNcqg == true){LpZKEPNcqg = false;}
      if(AoFpDkzjhy == true){AoFpDkzjhy = false;}
      if(toHUDIhDOK == true){toHUDIhDOK = false;}
      if(OseAcJhUQG == true){OseAcJhUQG = false;}
      if(OGRAkTrbBD == true){OGRAkTrbBD = false;}
      if(BGgncViEGw == true){BGgncViEGw = false;}
      if(gKOfSHJEMt == true){gKOfSHJEMt = false;}
      if(CeTbimWHjj == true){CeTbimWHjj = false;}
      if(PGBKIHLqXH == true){PGBKIHLqXH = false;}
      if(ZdOTZErkgc == true){ZdOTZErkgc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XCBYCMLZSO
{ 
  void QssEmBOwWL()
  { 
      bool VOUinBrOJh = false;
      bool zDUdpQoUdO = false;
      bool xIrWEaHrGz = false;
      bool YmOOxpqeFk = false;
      bool OHkESLmZea = false;
      bool RHORPMVxdN = false;
      bool tzIJIMoFfz = false;
      bool ZKOsApWmDs = false;
      bool mgMfhQXwzj = false;
      bool TsAqqOybuF = false;
      bool VgsfAGrVQZ = false;
      bool pisjaMlcbq = false;
      bool orGwffKWBk = false;
      bool qtryXFmgea = false;
      bool YBeYskzPQd = false;
      bool cUADPdawzT = false;
      bool wUTfhupuMU = false;
      bool YEyASmMgDt = false;
      bool gtGXIWtnhs = false;
      bool ephKdDhzqx = false;
      string BimZsRFeVy;
      string poFEafakky;
      string ZgZoOwRFpj;
      string BbUUHwpHhK;
      string YaReqriERg;
      string RWFqhUIyKw;
      string AznkwOUjxd;
      string oSCaZzPtyW;
      string NMnISeVclm;
      string mrxlKYlfib;
      string XyHmryTeRi;
      string EOznimLeSR;
      string rqyKqxVQQA;
      string NjLVyOEAQU;
      string KqKChYrJDW;
      string NGMQifzxwu;
      string cDORVUDdoT;
      string hLOxHBfubS;
      string ELNsmGWulS;
      string OHDVqHbsgN;
      if(BimZsRFeVy == XyHmryTeRi){VOUinBrOJh = true;}
      else if(XyHmryTeRi == BimZsRFeVy){VgsfAGrVQZ = true;}
      if(poFEafakky == EOznimLeSR){zDUdpQoUdO = true;}
      else if(EOznimLeSR == poFEafakky){pisjaMlcbq = true;}
      if(ZgZoOwRFpj == rqyKqxVQQA){xIrWEaHrGz = true;}
      else if(rqyKqxVQQA == ZgZoOwRFpj){orGwffKWBk = true;}
      if(BbUUHwpHhK == NjLVyOEAQU){YmOOxpqeFk = true;}
      else if(NjLVyOEAQU == BbUUHwpHhK){qtryXFmgea = true;}
      if(YaReqriERg == KqKChYrJDW){OHkESLmZea = true;}
      else if(KqKChYrJDW == YaReqriERg){YBeYskzPQd = true;}
      if(RWFqhUIyKw == NGMQifzxwu){RHORPMVxdN = true;}
      else if(NGMQifzxwu == RWFqhUIyKw){cUADPdawzT = true;}
      if(AznkwOUjxd == cDORVUDdoT){tzIJIMoFfz = true;}
      else if(cDORVUDdoT == AznkwOUjxd){wUTfhupuMU = true;}
      if(oSCaZzPtyW == hLOxHBfubS){ZKOsApWmDs = true;}
      if(NMnISeVclm == ELNsmGWulS){mgMfhQXwzj = true;}
      if(mrxlKYlfib == OHDVqHbsgN){TsAqqOybuF = true;}
      while(hLOxHBfubS == oSCaZzPtyW){YEyASmMgDt = true;}
      while(ELNsmGWulS == ELNsmGWulS){gtGXIWtnhs = true;}
      while(OHDVqHbsgN == OHDVqHbsgN){ephKdDhzqx = true;}
      if(VOUinBrOJh == true){VOUinBrOJh = false;}
      if(zDUdpQoUdO == true){zDUdpQoUdO = false;}
      if(xIrWEaHrGz == true){xIrWEaHrGz = false;}
      if(YmOOxpqeFk == true){YmOOxpqeFk = false;}
      if(OHkESLmZea == true){OHkESLmZea = false;}
      if(RHORPMVxdN == true){RHORPMVxdN = false;}
      if(tzIJIMoFfz == true){tzIJIMoFfz = false;}
      if(ZKOsApWmDs == true){ZKOsApWmDs = false;}
      if(mgMfhQXwzj == true){mgMfhQXwzj = false;}
      if(TsAqqOybuF == true){TsAqqOybuF = false;}
      if(VgsfAGrVQZ == true){VgsfAGrVQZ = false;}
      if(pisjaMlcbq == true){pisjaMlcbq = false;}
      if(orGwffKWBk == true){orGwffKWBk = false;}
      if(qtryXFmgea == true){qtryXFmgea = false;}
      if(YBeYskzPQd == true){YBeYskzPQd = false;}
      if(cUADPdawzT == true){cUADPdawzT = false;}
      if(wUTfhupuMU == true){wUTfhupuMU = false;}
      if(YEyASmMgDt == true){YEyASmMgDt = false;}
      if(gtGXIWtnhs == true){gtGXIWtnhs = false;}
      if(ephKdDhzqx == true){ephKdDhzqx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSPXHTUCRG
{ 
  void oCyhmUdtIB()
  { 
      bool CsyghiCxbV = false;
      bool gdrZDoqkmc = false;
      bool IiLkTZAclw = false;
      bool rkMyjVicVZ = false;
      bool THWNpHFasM = false;
      bool UWPqESgNNH = false;
      bool hYLeduQtog = false;
      bool GNONJALyuL = false;
      bool TZjYaVVVtQ = false;
      bool nVONqturjt = false;
      bool qLkMGGHCgD = false;
      bool HiSCmIolDH = false;
      bool ZuAXrkzBVO = false;
      bool FTOAUInWSU = false;
      bool OSnpJFCMZi = false;
      bool FInbTuLMUV = false;
      bool HFgRxnURhe = false;
      bool TRTisGGJOl = false;
      bool hmblJwflfY = false;
      bool waCxMIlVrU = false;
      string knOrCMOprc;
      string lsJskRIiry;
      string QoemnrwFLs;
      string trRmbLTLyy;
      string HyynMkiGJW;
      string IiteSwIbEK;
      string QJeyhtaVRZ;
      string xwjspSppZD;
      string JpwnkLxmTf;
      string CrHmhxSzGS;
      string JMniYLyAnz;
      string FRCBBZNpNV;
      string wnBkWFnwLr;
      string zqjGswBMPZ;
      string NwyUajoGlH;
      string jcljVVKDMS;
      string WBouANhwHE;
      string YBZnIzogKl;
      string PhKEIWFzjW;
      string kyAwCLHDUM;
      if(knOrCMOprc == JMniYLyAnz){CsyghiCxbV = true;}
      else if(JMniYLyAnz == knOrCMOprc){qLkMGGHCgD = true;}
      if(lsJskRIiry == FRCBBZNpNV){gdrZDoqkmc = true;}
      else if(FRCBBZNpNV == lsJskRIiry){HiSCmIolDH = true;}
      if(QoemnrwFLs == wnBkWFnwLr){IiLkTZAclw = true;}
      else if(wnBkWFnwLr == QoemnrwFLs){ZuAXrkzBVO = true;}
      if(trRmbLTLyy == zqjGswBMPZ){rkMyjVicVZ = true;}
      else if(zqjGswBMPZ == trRmbLTLyy){FTOAUInWSU = true;}
      if(HyynMkiGJW == NwyUajoGlH){THWNpHFasM = true;}
      else if(NwyUajoGlH == HyynMkiGJW){OSnpJFCMZi = true;}
      if(IiteSwIbEK == jcljVVKDMS){UWPqESgNNH = true;}
      else if(jcljVVKDMS == IiteSwIbEK){FInbTuLMUV = true;}
      if(QJeyhtaVRZ == WBouANhwHE){hYLeduQtog = true;}
      else if(WBouANhwHE == QJeyhtaVRZ){HFgRxnURhe = true;}
      if(xwjspSppZD == YBZnIzogKl){GNONJALyuL = true;}
      if(JpwnkLxmTf == PhKEIWFzjW){TZjYaVVVtQ = true;}
      if(CrHmhxSzGS == kyAwCLHDUM){nVONqturjt = true;}
      while(YBZnIzogKl == xwjspSppZD){TRTisGGJOl = true;}
      while(PhKEIWFzjW == PhKEIWFzjW){hmblJwflfY = true;}
      while(kyAwCLHDUM == kyAwCLHDUM){waCxMIlVrU = true;}
      if(CsyghiCxbV == true){CsyghiCxbV = false;}
      if(gdrZDoqkmc == true){gdrZDoqkmc = false;}
      if(IiLkTZAclw == true){IiLkTZAclw = false;}
      if(rkMyjVicVZ == true){rkMyjVicVZ = false;}
      if(THWNpHFasM == true){THWNpHFasM = false;}
      if(UWPqESgNNH == true){UWPqESgNNH = false;}
      if(hYLeduQtog == true){hYLeduQtog = false;}
      if(GNONJALyuL == true){GNONJALyuL = false;}
      if(TZjYaVVVtQ == true){TZjYaVVVtQ = false;}
      if(nVONqturjt == true){nVONqturjt = false;}
      if(qLkMGGHCgD == true){qLkMGGHCgD = false;}
      if(HiSCmIolDH == true){HiSCmIolDH = false;}
      if(ZuAXrkzBVO == true){ZuAXrkzBVO = false;}
      if(FTOAUInWSU == true){FTOAUInWSU = false;}
      if(OSnpJFCMZi == true){OSnpJFCMZi = false;}
      if(FInbTuLMUV == true){FInbTuLMUV = false;}
      if(HFgRxnURhe == true){HFgRxnURhe = false;}
      if(TRTisGGJOl == true){TRTisGGJOl = false;}
      if(hmblJwflfY == true){hmblJwflfY = false;}
      if(waCxMIlVrU == true){waCxMIlVrU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ULXNWGRSPT
{ 
  void tLstpfUVgB()
  { 
      bool YdmainOFyf = false;
      bool mXUZuqGPHX = false;
      bool jNKGLFkQCf = false;
      bool rjSxUfFAmw = false;
      bool sYamPYqBAT = false;
      bool VlwNqKTgPc = false;
      bool DyCSnCEXFO = false;
      bool kFbLdLmWpl = false;
      bool OjQiJFnFFK = false;
      bool LYjJruVHzM = false;
      bool UTukhPJkie = false;
      bool WxpcOTgTIh = false;
      bool OyRuCMVRTh = false;
      bool peWdRtnfAt = false;
      bool uCVamOhHuX = false;
      bool OCzRyVCAhU = false;
      bool tqRAoqZMLU = false;
      bool fBTNlLbpHn = false;
      bool eNWuTmfFfu = false;
      bool rnxeADkUlw = false;
      string TTXCacCiAw;
      string sIcHhHwuKb;
      string AgxwTXpawV;
      string ZJwYozHUTM;
      string iaGtsZBaHX;
      string BVJWplVahC;
      string maldViLERi;
      string zbbysYZDDs;
      string VOTYUDAZhC;
      string dflQZHncXJ;
      string NxIYXZsLcQ;
      string MRXogXHMJR;
      string ilVPESpLYk;
      string jxeteXFuAu;
      string KowRpLIxjB;
      string AbTGZbbsTF;
      string jhmrfOmdJI;
      string RMMNHtoEYs;
      string KrbWjIdYTC;
      string wMauKbCEkb;
      if(TTXCacCiAw == NxIYXZsLcQ){YdmainOFyf = true;}
      else if(NxIYXZsLcQ == TTXCacCiAw){UTukhPJkie = true;}
      if(sIcHhHwuKb == MRXogXHMJR){mXUZuqGPHX = true;}
      else if(MRXogXHMJR == sIcHhHwuKb){WxpcOTgTIh = true;}
      if(AgxwTXpawV == ilVPESpLYk){jNKGLFkQCf = true;}
      else if(ilVPESpLYk == AgxwTXpawV){OyRuCMVRTh = true;}
      if(ZJwYozHUTM == jxeteXFuAu){rjSxUfFAmw = true;}
      else if(jxeteXFuAu == ZJwYozHUTM){peWdRtnfAt = true;}
      if(iaGtsZBaHX == KowRpLIxjB){sYamPYqBAT = true;}
      else if(KowRpLIxjB == iaGtsZBaHX){uCVamOhHuX = true;}
      if(BVJWplVahC == AbTGZbbsTF){VlwNqKTgPc = true;}
      else if(AbTGZbbsTF == BVJWplVahC){OCzRyVCAhU = true;}
      if(maldViLERi == jhmrfOmdJI){DyCSnCEXFO = true;}
      else if(jhmrfOmdJI == maldViLERi){tqRAoqZMLU = true;}
      if(zbbysYZDDs == RMMNHtoEYs){kFbLdLmWpl = true;}
      if(VOTYUDAZhC == KrbWjIdYTC){OjQiJFnFFK = true;}
      if(dflQZHncXJ == wMauKbCEkb){LYjJruVHzM = true;}
      while(RMMNHtoEYs == zbbysYZDDs){fBTNlLbpHn = true;}
      while(KrbWjIdYTC == KrbWjIdYTC){eNWuTmfFfu = true;}
      while(wMauKbCEkb == wMauKbCEkb){rnxeADkUlw = true;}
      if(YdmainOFyf == true){YdmainOFyf = false;}
      if(mXUZuqGPHX == true){mXUZuqGPHX = false;}
      if(jNKGLFkQCf == true){jNKGLFkQCf = false;}
      if(rjSxUfFAmw == true){rjSxUfFAmw = false;}
      if(sYamPYqBAT == true){sYamPYqBAT = false;}
      if(VlwNqKTgPc == true){VlwNqKTgPc = false;}
      if(DyCSnCEXFO == true){DyCSnCEXFO = false;}
      if(kFbLdLmWpl == true){kFbLdLmWpl = false;}
      if(OjQiJFnFFK == true){OjQiJFnFFK = false;}
      if(LYjJruVHzM == true){LYjJruVHzM = false;}
      if(UTukhPJkie == true){UTukhPJkie = false;}
      if(WxpcOTgTIh == true){WxpcOTgTIh = false;}
      if(OyRuCMVRTh == true){OyRuCMVRTh = false;}
      if(peWdRtnfAt == true){peWdRtnfAt = false;}
      if(uCVamOhHuX == true){uCVamOhHuX = false;}
      if(OCzRyVCAhU == true){OCzRyVCAhU = false;}
      if(tqRAoqZMLU == true){tqRAoqZMLU = false;}
      if(fBTNlLbpHn == true){fBTNlLbpHn = false;}
      if(eNWuTmfFfu == true){eNWuTmfFfu = false;}
      if(rnxeADkUlw == true){rnxeADkUlw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZJXKLDEZIP
{ 
  void kpIBhkYIZd()
  { 
      bool pMsERUquPq = false;
      bool ENmUogchYx = false;
      bool UHbLlddCuZ = false;
      bool fLZUdBePfY = false;
      bool lfuIkqANnC = false;
      bool DOpsNhkgRn = false;
      bool qoApKsnSpn = false;
      bool CMCALoLSau = false;
      bool dPNrWRVfGu = false;
      bool PxxrgwfEyr = false;
      bool DhXAApMohY = false;
      bool WSGWJabHSs = false;
      bool WHMtXEPKTO = false;
      bool JHUhqwqMrg = false;
      bool FgygYxqahF = false;
      bool UYkEVuUdbw = false;
      bool ZBVTOOxYeN = false;
      bool iOOlmpJeUa = false;
      bool NncNskVPMw = false;
      bool aNjwGDKeSJ = false;
      string luafXuOfTS;
      string WCpuaYywth;
      string VkLdrtupgg;
      string uVPKfqjIEf;
      string ojkaddtpBt;
      string PFclPAixmd;
      string AXzmXBmePj;
      string ooqNrlAjzN;
      string AEolQpscuf;
      string HlUafQkxDc;
      string qOaRFZNOtc;
      string zzxZduiMVh;
      string HKjjcCTQha;
      string BCgVWkdWgp;
      string bdhSfInuxj;
      string gXaVUgepoC;
      string FwgSawSbCr;
      string RMffFdbQDT;
      string NYTysdaKAp;
      string FmhdjfxPqi;
      if(luafXuOfTS == qOaRFZNOtc){pMsERUquPq = true;}
      else if(qOaRFZNOtc == luafXuOfTS){DhXAApMohY = true;}
      if(WCpuaYywth == zzxZduiMVh){ENmUogchYx = true;}
      else if(zzxZduiMVh == WCpuaYywth){WSGWJabHSs = true;}
      if(VkLdrtupgg == HKjjcCTQha){UHbLlddCuZ = true;}
      else if(HKjjcCTQha == VkLdrtupgg){WHMtXEPKTO = true;}
      if(uVPKfqjIEf == BCgVWkdWgp){fLZUdBePfY = true;}
      else if(BCgVWkdWgp == uVPKfqjIEf){JHUhqwqMrg = true;}
      if(ojkaddtpBt == bdhSfInuxj){lfuIkqANnC = true;}
      else if(bdhSfInuxj == ojkaddtpBt){FgygYxqahF = true;}
      if(PFclPAixmd == gXaVUgepoC){DOpsNhkgRn = true;}
      else if(gXaVUgepoC == PFclPAixmd){UYkEVuUdbw = true;}
      if(AXzmXBmePj == FwgSawSbCr){qoApKsnSpn = true;}
      else if(FwgSawSbCr == AXzmXBmePj){ZBVTOOxYeN = true;}
      if(ooqNrlAjzN == RMffFdbQDT){CMCALoLSau = true;}
      if(AEolQpscuf == NYTysdaKAp){dPNrWRVfGu = true;}
      if(HlUafQkxDc == FmhdjfxPqi){PxxrgwfEyr = true;}
      while(RMffFdbQDT == ooqNrlAjzN){iOOlmpJeUa = true;}
      while(NYTysdaKAp == NYTysdaKAp){NncNskVPMw = true;}
      while(FmhdjfxPqi == FmhdjfxPqi){aNjwGDKeSJ = true;}
      if(pMsERUquPq == true){pMsERUquPq = false;}
      if(ENmUogchYx == true){ENmUogchYx = false;}
      if(UHbLlddCuZ == true){UHbLlddCuZ = false;}
      if(fLZUdBePfY == true){fLZUdBePfY = false;}
      if(lfuIkqANnC == true){lfuIkqANnC = false;}
      if(DOpsNhkgRn == true){DOpsNhkgRn = false;}
      if(qoApKsnSpn == true){qoApKsnSpn = false;}
      if(CMCALoLSau == true){CMCALoLSau = false;}
      if(dPNrWRVfGu == true){dPNrWRVfGu = false;}
      if(PxxrgwfEyr == true){PxxrgwfEyr = false;}
      if(DhXAApMohY == true){DhXAApMohY = false;}
      if(WSGWJabHSs == true){WSGWJabHSs = false;}
      if(WHMtXEPKTO == true){WHMtXEPKTO = false;}
      if(JHUhqwqMrg == true){JHUhqwqMrg = false;}
      if(FgygYxqahF == true){FgygYxqahF = false;}
      if(UYkEVuUdbw == true){UYkEVuUdbw = false;}
      if(ZBVTOOxYeN == true){ZBVTOOxYeN = false;}
      if(iOOlmpJeUa == true){iOOlmpJeUa = false;}
      if(NncNskVPMw == true){NncNskVPMw = false;}
      if(aNjwGDKeSJ == true){aNjwGDKeSJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EYXBUUNPTC
{ 
  void iFMdZcRRAM()
  { 
      bool dOjAlSpVdZ = false;
      bool jedKRoffyM = false;
      bool IFKsnaPBZM = false;
      bool cMxoguOrEO = false;
      bool AhRMlOuLeS = false;
      bool pyhWSYEqML = false;
      bool CouQwXhndW = false;
      bool ZnajMamxHY = false;
      bool eEWHVddaWI = false;
      bool pXfrLKlAPN = false;
      bool gHgHrCWyKq = false;
      bool kHjmgxSmuS = false;
      bool tGQVfCIiXB = false;
      bool nlgsqXXOPT = false;
      bool HePfXimrLO = false;
      bool ryFxTZpKao = false;
      bool tnaJCyZqwI = false;
      bool ZDXaKOqkyx = false;
      bool PQWJIpgiZQ = false;
      bool gMmZZSEGcY = false;
      string DhfSkKkNDW;
      string qTgcjBgCWw;
      string uqVGPHZzUm;
      string uhcsSDCSCo;
      string WEATycTIty;
      string CAhtYLMYDd;
      string jksPaIpnKg;
      string zOAhZpqBIm;
      string mRFWkuAhUG;
      string pcPYElKjro;
      string lfyMynzzUh;
      string TKQPpSfWee;
      string IHTDpWyacn;
      string eHJTAHSrXx;
      string uBNlmfMzil;
      string FnENgdMtVb;
      string oYWgCLBxOh;
      string zmyhiGsgQK;
      string JzrqhpDulV;
      string tYWwHWdgia;
      if(DhfSkKkNDW == lfyMynzzUh){dOjAlSpVdZ = true;}
      else if(lfyMynzzUh == DhfSkKkNDW){gHgHrCWyKq = true;}
      if(qTgcjBgCWw == TKQPpSfWee){jedKRoffyM = true;}
      else if(TKQPpSfWee == qTgcjBgCWw){kHjmgxSmuS = true;}
      if(uqVGPHZzUm == IHTDpWyacn){IFKsnaPBZM = true;}
      else if(IHTDpWyacn == uqVGPHZzUm){tGQVfCIiXB = true;}
      if(uhcsSDCSCo == eHJTAHSrXx){cMxoguOrEO = true;}
      else if(eHJTAHSrXx == uhcsSDCSCo){nlgsqXXOPT = true;}
      if(WEATycTIty == uBNlmfMzil){AhRMlOuLeS = true;}
      else if(uBNlmfMzil == WEATycTIty){HePfXimrLO = true;}
      if(CAhtYLMYDd == FnENgdMtVb){pyhWSYEqML = true;}
      else if(FnENgdMtVb == CAhtYLMYDd){ryFxTZpKao = true;}
      if(jksPaIpnKg == oYWgCLBxOh){CouQwXhndW = true;}
      else if(oYWgCLBxOh == jksPaIpnKg){tnaJCyZqwI = true;}
      if(zOAhZpqBIm == zmyhiGsgQK){ZnajMamxHY = true;}
      if(mRFWkuAhUG == JzrqhpDulV){eEWHVddaWI = true;}
      if(pcPYElKjro == tYWwHWdgia){pXfrLKlAPN = true;}
      while(zmyhiGsgQK == zOAhZpqBIm){ZDXaKOqkyx = true;}
      while(JzrqhpDulV == JzrqhpDulV){PQWJIpgiZQ = true;}
      while(tYWwHWdgia == tYWwHWdgia){gMmZZSEGcY = true;}
      if(dOjAlSpVdZ == true){dOjAlSpVdZ = false;}
      if(jedKRoffyM == true){jedKRoffyM = false;}
      if(IFKsnaPBZM == true){IFKsnaPBZM = false;}
      if(cMxoguOrEO == true){cMxoguOrEO = false;}
      if(AhRMlOuLeS == true){AhRMlOuLeS = false;}
      if(pyhWSYEqML == true){pyhWSYEqML = false;}
      if(CouQwXhndW == true){CouQwXhndW = false;}
      if(ZnajMamxHY == true){ZnajMamxHY = false;}
      if(eEWHVddaWI == true){eEWHVddaWI = false;}
      if(pXfrLKlAPN == true){pXfrLKlAPN = false;}
      if(gHgHrCWyKq == true){gHgHrCWyKq = false;}
      if(kHjmgxSmuS == true){kHjmgxSmuS = false;}
      if(tGQVfCIiXB == true){tGQVfCIiXB = false;}
      if(nlgsqXXOPT == true){nlgsqXXOPT = false;}
      if(HePfXimrLO == true){HePfXimrLO = false;}
      if(ryFxTZpKao == true){ryFxTZpKao = false;}
      if(tnaJCyZqwI == true){tnaJCyZqwI = false;}
      if(ZDXaKOqkyx == true){ZDXaKOqkyx = false;}
      if(PQWJIpgiZQ == true){PQWJIpgiZQ = false;}
      if(gMmZZSEGcY == true){gMmZZSEGcY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NJXVAYRHBY
{ 
  void hiNsHOfKrK()
  { 
      bool rGLjHyhdzh = false;
      bool RUsyAPfdDA = false;
      bool NXVnhRDIdh = false;
      bool fzXAxhxOwB = false;
      bool FECElBTfTF = false;
      bool AFWXETjWCp = false;
      bool uZAQBRwrBR = false;
      bool SRhCuJUQCf = false;
      bool xWnXgZbzwc = false;
      bool yZMFGfDkDT = false;
      bool EaeBmiXUct = false;
      bool zSUVrXkbjb = false;
      bool oxwXTrFbwP = false;
      bool FiNiaWqlkx = false;
      bool CHWBdeFpMh = false;
      bool taBbdHdHht = false;
      bool duYNoPFluV = false;
      bool fyqlYhZusn = false;
      bool mOPNUdglES = false;
      bool rjEpTGhJMN = false;
      string kxloMerFHV;
      string VfkYWkeQkP;
      string koAZIBMaNc;
      string RuNdTFWYtG;
      string ApDtHPjxLI;
      string tnDzfuxMgL;
      string RQreEZSHEQ;
      string OGVePulGRr;
      string RPOEidqNxX;
      string IJrinixYog;
      string xbrutnRYjk;
      string JqtntCCmua;
      string iEJgHENmpf;
      string xMQkuoXTKu;
      string LSdMORPEnl;
      string gKdOyrSKno;
      string ZehDmwZJrE;
      string dhczOQaxRo;
      string oJyEzmiCmD;
      string WMeUVgjaYR;
      if(kxloMerFHV == xbrutnRYjk){rGLjHyhdzh = true;}
      else if(xbrutnRYjk == kxloMerFHV){EaeBmiXUct = true;}
      if(VfkYWkeQkP == JqtntCCmua){RUsyAPfdDA = true;}
      else if(JqtntCCmua == VfkYWkeQkP){zSUVrXkbjb = true;}
      if(koAZIBMaNc == iEJgHENmpf){NXVnhRDIdh = true;}
      else if(iEJgHENmpf == koAZIBMaNc){oxwXTrFbwP = true;}
      if(RuNdTFWYtG == xMQkuoXTKu){fzXAxhxOwB = true;}
      else if(xMQkuoXTKu == RuNdTFWYtG){FiNiaWqlkx = true;}
      if(ApDtHPjxLI == LSdMORPEnl){FECElBTfTF = true;}
      else if(LSdMORPEnl == ApDtHPjxLI){CHWBdeFpMh = true;}
      if(tnDzfuxMgL == gKdOyrSKno){AFWXETjWCp = true;}
      else if(gKdOyrSKno == tnDzfuxMgL){taBbdHdHht = true;}
      if(RQreEZSHEQ == ZehDmwZJrE){uZAQBRwrBR = true;}
      else if(ZehDmwZJrE == RQreEZSHEQ){duYNoPFluV = true;}
      if(OGVePulGRr == dhczOQaxRo){SRhCuJUQCf = true;}
      if(RPOEidqNxX == oJyEzmiCmD){xWnXgZbzwc = true;}
      if(IJrinixYog == WMeUVgjaYR){yZMFGfDkDT = true;}
      while(dhczOQaxRo == OGVePulGRr){fyqlYhZusn = true;}
      while(oJyEzmiCmD == oJyEzmiCmD){mOPNUdglES = true;}
      while(WMeUVgjaYR == WMeUVgjaYR){rjEpTGhJMN = true;}
      if(rGLjHyhdzh == true){rGLjHyhdzh = false;}
      if(RUsyAPfdDA == true){RUsyAPfdDA = false;}
      if(NXVnhRDIdh == true){NXVnhRDIdh = false;}
      if(fzXAxhxOwB == true){fzXAxhxOwB = false;}
      if(FECElBTfTF == true){FECElBTfTF = false;}
      if(AFWXETjWCp == true){AFWXETjWCp = false;}
      if(uZAQBRwrBR == true){uZAQBRwrBR = false;}
      if(SRhCuJUQCf == true){SRhCuJUQCf = false;}
      if(xWnXgZbzwc == true){xWnXgZbzwc = false;}
      if(yZMFGfDkDT == true){yZMFGfDkDT = false;}
      if(EaeBmiXUct == true){EaeBmiXUct = false;}
      if(zSUVrXkbjb == true){zSUVrXkbjb = false;}
      if(oxwXTrFbwP == true){oxwXTrFbwP = false;}
      if(FiNiaWqlkx == true){FiNiaWqlkx = false;}
      if(CHWBdeFpMh == true){CHWBdeFpMh = false;}
      if(taBbdHdHht == true){taBbdHdHht = false;}
      if(duYNoPFluV == true){duYNoPFluV = false;}
      if(fyqlYhZusn == true){fyqlYhZusn = false;}
      if(mOPNUdglES == true){mOPNUdglES = false;}
      if(rjEpTGhJMN == true){rjEpTGhJMN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NXPYBEXFJC
{ 
  void apFnxlkDDU()
  { 
      bool oPMdVTkRyi = false;
      bool ozlFcrcowz = false;
      bool lwptmpkffB = false;
      bool VsnFajdSYR = false;
      bool wekfoxJZCT = false;
      bool kANOmrYSpe = false;
      bool iFlxMwKfds = false;
      bool NKQdDGLKFp = false;
      bool fKdLPUeYSh = false;
      bool KKbsiqrnSr = false;
      bool ldwIFajiLf = false;
      bool gONAzXaahr = false;
      bool QlMuhChWuM = false;
      bool OXrMEBOUFn = false;
      bool kuNlBwxbtK = false;
      bool PRFaazQAZD = false;
      bool rNnzRJVBwx = false;
      bool IGVsGVXatl = false;
      bool FGbjwxRRlE = false;
      bool kOtCuWHNUr = false;
      string JKVowhXfgu;
      string DMcqhntmhz;
      string pIOSkMPzFg;
      string QGWTBwlkfY;
      string arAxcbLurz;
      string WqtbJAwDEj;
      string SYazdxoIol;
      string CJGIXxIRoI;
      string BTHFKYLuJA;
      string AhfwGCRASf;
      string lCGGwNjlDM;
      string qeNuizRUoE;
      string ktznkTcKCV;
      string eIyIWyMAIx;
      string oZqwIVUkNH;
      string jxKOtrCRUc;
      string jZjggifEXj;
      string lQLrPLCDfP;
      string zqwtkhxjOd;
      string wuefMOpJOZ;
      if(JKVowhXfgu == lCGGwNjlDM){oPMdVTkRyi = true;}
      else if(lCGGwNjlDM == JKVowhXfgu){ldwIFajiLf = true;}
      if(DMcqhntmhz == qeNuizRUoE){ozlFcrcowz = true;}
      else if(qeNuizRUoE == DMcqhntmhz){gONAzXaahr = true;}
      if(pIOSkMPzFg == ktznkTcKCV){lwptmpkffB = true;}
      else if(ktznkTcKCV == pIOSkMPzFg){QlMuhChWuM = true;}
      if(QGWTBwlkfY == eIyIWyMAIx){VsnFajdSYR = true;}
      else if(eIyIWyMAIx == QGWTBwlkfY){OXrMEBOUFn = true;}
      if(arAxcbLurz == oZqwIVUkNH){wekfoxJZCT = true;}
      else if(oZqwIVUkNH == arAxcbLurz){kuNlBwxbtK = true;}
      if(WqtbJAwDEj == jxKOtrCRUc){kANOmrYSpe = true;}
      else if(jxKOtrCRUc == WqtbJAwDEj){PRFaazQAZD = true;}
      if(SYazdxoIol == jZjggifEXj){iFlxMwKfds = true;}
      else if(jZjggifEXj == SYazdxoIol){rNnzRJVBwx = true;}
      if(CJGIXxIRoI == lQLrPLCDfP){NKQdDGLKFp = true;}
      if(BTHFKYLuJA == zqwtkhxjOd){fKdLPUeYSh = true;}
      if(AhfwGCRASf == wuefMOpJOZ){KKbsiqrnSr = true;}
      while(lQLrPLCDfP == CJGIXxIRoI){IGVsGVXatl = true;}
      while(zqwtkhxjOd == zqwtkhxjOd){FGbjwxRRlE = true;}
      while(wuefMOpJOZ == wuefMOpJOZ){kOtCuWHNUr = true;}
      if(oPMdVTkRyi == true){oPMdVTkRyi = false;}
      if(ozlFcrcowz == true){ozlFcrcowz = false;}
      if(lwptmpkffB == true){lwptmpkffB = false;}
      if(VsnFajdSYR == true){VsnFajdSYR = false;}
      if(wekfoxJZCT == true){wekfoxJZCT = false;}
      if(kANOmrYSpe == true){kANOmrYSpe = false;}
      if(iFlxMwKfds == true){iFlxMwKfds = false;}
      if(NKQdDGLKFp == true){NKQdDGLKFp = false;}
      if(fKdLPUeYSh == true){fKdLPUeYSh = false;}
      if(KKbsiqrnSr == true){KKbsiqrnSr = false;}
      if(ldwIFajiLf == true){ldwIFajiLf = false;}
      if(gONAzXaahr == true){gONAzXaahr = false;}
      if(QlMuhChWuM == true){QlMuhChWuM = false;}
      if(OXrMEBOUFn == true){OXrMEBOUFn = false;}
      if(kuNlBwxbtK == true){kuNlBwxbtK = false;}
      if(PRFaazQAZD == true){PRFaazQAZD = false;}
      if(rNnzRJVBwx == true){rNnzRJVBwx = false;}
      if(IGVsGVXatl == true){IGVsGVXatl = false;}
      if(FGbjwxRRlE == true){FGbjwxRRlE = false;}
      if(kOtCuWHNUr == true){kOtCuWHNUr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OHYESEDAYC
{ 
  void RYQOkVgMbI()
  { 
      bool AbXRjUiTHg = false;
      bool MDljuSokOM = false;
      bool MGodsQXptf = false;
      bool QKShSMwFkJ = false;
      bool qLkBinGRou = false;
      bool wnbjftltXS = false;
      bool wrZaQCkDQh = false;
      bool WjAEUBUmtF = false;
      bool KFAyjchiCY = false;
      bool ZBgRNykKkg = false;
      bool CDBGYMmXOe = false;
      bool ZzzSIprbqn = false;
      bool TCBrIUChqW = false;
      bool PJCNCHEtZW = false;
      bool oKTXyZCNJW = false;
      bool GJTwNzBJxE = false;
      bool JFfqOPwlQB = false;
      bool lyBTyIhcsi = false;
      bool SnXTPGpFzC = false;
      bool FuwVMjecIi = false;
      string khnpcnCKbB;
      string OHaWkUdAZm;
      string ZrELwDuqaM;
      string zsUTbxEcZB;
      string mlAtNlZSMl;
      string GNrSLrdbtZ;
      string rLiOCUmHun;
      string PBaXAmrKyJ;
      string cceoGkABHj;
      string TcizJaDkqr;
      string zSXYVFmURX;
      string zSdjwPfsIQ;
      string UkzKUmSaOY;
      string jHTFKKFGSA;
      string yejjjAzyDs;
      string tJbZWNSMDi;
      string mMGsmrzXZk;
      string JZaHSoBOaT;
      string nTWUdaesiw;
      string rrCjNlYpwr;
      if(khnpcnCKbB == zSXYVFmURX){AbXRjUiTHg = true;}
      else if(zSXYVFmURX == khnpcnCKbB){CDBGYMmXOe = true;}
      if(OHaWkUdAZm == zSdjwPfsIQ){MDljuSokOM = true;}
      else if(zSdjwPfsIQ == OHaWkUdAZm){ZzzSIprbqn = true;}
      if(ZrELwDuqaM == UkzKUmSaOY){MGodsQXptf = true;}
      else if(UkzKUmSaOY == ZrELwDuqaM){TCBrIUChqW = true;}
      if(zsUTbxEcZB == jHTFKKFGSA){QKShSMwFkJ = true;}
      else if(jHTFKKFGSA == zsUTbxEcZB){PJCNCHEtZW = true;}
      if(mlAtNlZSMl == yejjjAzyDs){qLkBinGRou = true;}
      else if(yejjjAzyDs == mlAtNlZSMl){oKTXyZCNJW = true;}
      if(GNrSLrdbtZ == tJbZWNSMDi){wnbjftltXS = true;}
      else if(tJbZWNSMDi == GNrSLrdbtZ){GJTwNzBJxE = true;}
      if(rLiOCUmHun == mMGsmrzXZk){wrZaQCkDQh = true;}
      else if(mMGsmrzXZk == rLiOCUmHun){JFfqOPwlQB = true;}
      if(PBaXAmrKyJ == JZaHSoBOaT){WjAEUBUmtF = true;}
      if(cceoGkABHj == nTWUdaesiw){KFAyjchiCY = true;}
      if(TcizJaDkqr == rrCjNlYpwr){ZBgRNykKkg = true;}
      while(JZaHSoBOaT == PBaXAmrKyJ){lyBTyIhcsi = true;}
      while(nTWUdaesiw == nTWUdaesiw){SnXTPGpFzC = true;}
      while(rrCjNlYpwr == rrCjNlYpwr){FuwVMjecIi = true;}
      if(AbXRjUiTHg == true){AbXRjUiTHg = false;}
      if(MDljuSokOM == true){MDljuSokOM = false;}
      if(MGodsQXptf == true){MGodsQXptf = false;}
      if(QKShSMwFkJ == true){QKShSMwFkJ = false;}
      if(qLkBinGRou == true){qLkBinGRou = false;}
      if(wnbjftltXS == true){wnbjftltXS = false;}
      if(wrZaQCkDQh == true){wrZaQCkDQh = false;}
      if(WjAEUBUmtF == true){WjAEUBUmtF = false;}
      if(KFAyjchiCY == true){KFAyjchiCY = false;}
      if(ZBgRNykKkg == true){ZBgRNykKkg = false;}
      if(CDBGYMmXOe == true){CDBGYMmXOe = false;}
      if(ZzzSIprbqn == true){ZzzSIprbqn = false;}
      if(TCBrIUChqW == true){TCBrIUChqW = false;}
      if(PJCNCHEtZW == true){PJCNCHEtZW = false;}
      if(oKTXyZCNJW == true){oKTXyZCNJW = false;}
      if(GJTwNzBJxE == true){GJTwNzBJxE = false;}
      if(JFfqOPwlQB == true){JFfqOPwlQB = false;}
      if(lyBTyIhcsi == true){lyBTyIhcsi = false;}
      if(SnXTPGpFzC == true){SnXTPGpFzC = false;}
      if(FuwVMjecIi == true){FuwVMjecIi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRRYZFIDZN
{ 
  void IcWIwbPIen()
  { 
      bool rMYimXpyth = false;
      bool qulabzgBRW = false;
      bool OhNcmaoSbN = false;
      bool rlnkQFONpQ = false;
      bool sFAzHDjLkX = false;
      bool neTreJywuM = false;
      bool iWVgoFGAKW = false;
      bool jSKBdJhOUj = false;
      bool qchEYMRwFG = false;
      bool HSSdhViSJC = false;
      bool wiAOmUTSNV = false;
      bool biaLUFoRIb = false;
      bool mKtEORAgSH = false;
      bool ZPFSmIcTQD = false;
      bool syhjdYrHJb = false;
      bool gRKgOknwzV = false;
      bool UmzFwMdIXM = false;
      bool cVAEincKZp = false;
      bool YsXpaIEXDB = false;
      bool TfTuiFzbmR = false;
      string rSZTEKXcrA;
      string cdWiHRFflM;
      string tOfNiAdrLt;
      string SkWNKICaIB;
      string acFtinfhKi;
      string HUegeclMjD;
      string geRxgqHIYy;
      string OeXjkRJket;
      string UwhbmxGoig;
      string VopEUwLHMq;
      string gXJLTbxtwM;
      string TBhoijxoKi;
      string kRYrcZnSOn;
      string GBYmNwmVIK;
      string ALsVMUHAVk;
      string zWxdGOyQit;
      string mefHGScubl;
      string xafziYXDeI;
      string RnxdoiDtgy;
      string yVlNWVflPt;
      if(rSZTEKXcrA == gXJLTbxtwM){rMYimXpyth = true;}
      else if(gXJLTbxtwM == rSZTEKXcrA){wiAOmUTSNV = true;}
      if(cdWiHRFflM == TBhoijxoKi){qulabzgBRW = true;}
      else if(TBhoijxoKi == cdWiHRFflM){biaLUFoRIb = true;}
      if(tOfNiAdrLt == kRYrcZnSOn){OhNcmaoSbN = true;}
      else if(kRYrcZnSOn == tOfNiAdrLt){mKtEORAgSH = true;}
      if(SkWNKICaIB == GBYmNwmVIK){rlnkQFONpQ = true;}
      else if(GBYmNwmVIK == SkWNKICaIB){ZPFSmIcTQD = true;}
      if(acFtinfhKi == ALsVMUHAVk){sFAzHDjLkX = true;}
      else if(ALsVMUHAVk == acFtinfhKi){syhjdYrHJb = true;}
      if(HUegeclMjD == zWxdGOyQit){neTreJywuM = true;}
      else if(zWxdGOyQit == HUegeclMjD){gRKgOknwzV = true;}
      if(geRxgqHIYy == mefHGScubl){iWVgoFGAKW = true;}
      else if(mefHGScubl == geRxgqHIYy){UmzFwMdIXM = true;}
      if(OeXjkRJket == xafziYXDeI){jSKBdJhOUj = true;}
      if(UwhbmxGoig == RnxdoiDtgy){qchEYMRwFG = true;}
      if(VopEUwLHMq == yVlNWVflPt){HSSdhViSJC = true;}
      while(xafziYXDeI == OeXjkRJket){cVAEincKZp = true;}
      while(RnxdoiDtgy == RnxdoiDtgy){YsXpaIEXDB = true;}
      while(yVlNWVflPt == yVlNWVflPt){TfTuiFzbmR = true;}
      if(rMYimXpyth == true){rMYimXpyth = false;}
      if(qulabzgBRW == true){qulabzgBRW = false;}
      if(OhNcmaoSbN == true){OhNcmaoSbN = false;}
      if(rlnkQFONpQ == true){rlnkQFONpQ = false;}
      if(sFAzHDjLkX == true){sFAzHDjLkX = false;}
      if(neTreJywuM == true){neTreJywuM = false;}
      if(iWVgoFGAKW == true){iWVgoFGAKW = false;}
      if(jSKBdJhOUj == true){jSKBdJhOUj = false;}
      if(qchEYMRwFG == true){qchEYMRwFG = false;}
      if(HSSdhViSJC == true){HSSdhViSJC = false;}
      if(wiAOmUTSNV == true){wiAOmUTSNV = false;}
      if(biaLUFoRIb == true){biaLUFoRIb = false;}
      if(mKtEORAgSH == true){mKtEORAgSH = false;}
      if(ZPFSmIcTQD == true){ZPFSmIcTQD = false;}
      if(syhjdYrHJb == true){syhjdYrHJb = false;}
      if(gRKgOknwzV == true){gRKgOknwzV = false;}
      if(UmzFwMdIXM == true){UmzFwMdIXM = false;}
      if(cVAEincKZp == true){cVAEincKZp = false;}
      if(YsXpaIEXDB == true){YsXpaIEXDB = false;}
      if(TfTuiFzbmR == true){TfTuiFzbmR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUMIKXZRYU
{ 
  void QeIFfLssbN()
  { 
      bool dwaMsjMRmX = false;
      bool NbPKBPWuQp = false;
      bool VMVsCyhowC = false;
      bool YQxDDEpbPJ = false;
      bool IyZkunfxCN = false;
      bool wyFDmRZhKt = false;
      bool BXVkywdLGx = false;
      bool ZueGgXlkxN = false;
      bool SkliFZLtQl = false;
      bool dIQVIkbomy = false;
      bool KTpEnBSyVP = false;
      bool eojxbQkleX = false;
      bool kiuUTQdJyw = false;
      bool uxyzCythuE = false;
      bool GMYBHnYTsq = false;
      bool zoJONbYVkW = false;
      bool WJAZTgqjtc = false;
      bool VDqZRXKtMe = false;
      bool qKQGxFnila = false;
      bool YYxXgxLzgZ = false;
      string WuUPBXOrUL;
      string TAFZVdJhhP;
      string dnNhaCwuDw;
      string uCVQYhtbfg;
      string huBcZyElQP;
      string JhCLWhgmnz;
      string bSnXPRdoAm;
      string jhBBhiljHc;
      string xJdmmNzKsq;
      string BHngEOGdMI;
      string TOldfbgAdn;
      string uxeKBRoAkC;
      string RTwJlctUwS;
      string bIWzJiXzHK;
      string fyfFuDbcem;
      string YGrJpAScrC;
      string gMEKLlZeBS;
      string tosZWSmqNh;
      string ARoJtVQNII;
      string PuHEcTtVsJ;
      if(WuUPBXOrUL == TOldfbgAdn){dwaMsjMRmX = true;}
      else if(TOldfbgAdn == WuUPBXOrUL){KTpEnBSyVP = true;}
      if(TAFZVdJhhP == uxeKBRoAkC){NbPKBPWuQp = true;}
      else if(uxeKBRoAkC == TAFZVdJhhP){eojxbQkleX = true;}
      if(dnNhaCwuDw == RTwJlctUwS){VMVsCyhowC = true;}
      else if(RTwJlctUwS == dnNhaCwuDw){kiuUTQdJyw = true;}
      if(uCVQYhtbfg == bIWzJiXzHK){YQxDDEpbPJ = true;}
      else if(bIWzJiXzHK == uCVQYhtbfg){uxyzCythuE = true;}
      if(huBcZyElQP == fyfFuDbcem){IyZkunfxCN = true;}
      else if(fyfFuDbcem == huBcZyElQP){GMYBHnYTsq = true;}
      if(JhCLWhgmnz == YGrJpAScrC){wyFDmRZhKt = true;}
      else if(YGrJpAScrC == JhCLWhgmnz){zoJONbYVkW = true;}
      if(bSnXPRdoAm == gMEKLlZeBS){BXVkywdLGx = true;}
      else if(gMEKLlZeBS == bSnXPRdoAm){WJAZTgqjtc = true;}
      if(jhBBhiljHc == tosZWSmqNh){ZueGgXlkxN = true;}
      if(xJdmmNzKsq == ARoJtVQNII){SkliFZLtQl = true;}
      if(BHngEOGdMI == PuHEcTtVsJ){dIQVIkbomy = true;}
      while(tosZWSmqNh == jhBBhiljHc){VDqZRXKtMe = true;}
      while(ARoJtVQNII == ARoJtVQNII){qKQGxFnila = true;}
      while(PuHEcTtVsJ == PuHEcTtVsJ){YYxXgxLzgZ = true;}
      if(dwaMsjMRmX == true){dwaMsjMRmX = false;}
      if(NbPKBPWuQp == true){NbPKBPWuQp = false;}
      if(VMVsCyhowC == true){VMVsCyhowC = false;}
      if(YQxDDEpbPJ == true){YQxDDEpbPJ = false;}
      if(IyZkunfxCN == true){IyZkunfxCN = false;}
      if(wyFDmRZhKt == true){wyFDmRZhKt = false;}
      if(BXVkywdLGx == true){BXVkywdLGx = false;}
      if(ZueGgXlkxN == true){ZueGgXlkxN = false;}
      if(SkliFZLtQl == true){SkliFZLtQl = false;}
      if(dIQVIkbomy == true){dIQVIkbomy = false;}
      if(KTpEnBSyVP == true){KTpEnBSyVP = false;}
      if(eojxbQkleX == true){eojxbQkleX = false;}
      if(kiuUTQdJyw == true){kiuUTQdJyw = false;}
      if(uxyzCythuE == true){uxyzCythuE = false;}
      if(GMYBHnYTsq == true){GMYBHnYTsq = false;}
      if(zoJONbYVkW == true){zoJONbYVkW = false;}
      if(WJAZTgqjtc == true){WJAZTgqjtc = false;}
      if(VDqZRXKtMe == true){VDqZRXKtMe = false;}
      if(qKQGxFnila == true){qKQGxFnila = false;}
      if(YYxXgxLzgZ == true){YYxXgxLzgZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KODTAZWUCF
{ 
  void pORqSTbahV()
  { 
      bool EHqhijuLfP = false;
      bool urslsVNhEk = false;
      bool almbjYtsfH = false;
      bool lIawBdfoXd = false;
      bool AlbkgbggWJ = false;
      bool CeQZbSTOxJ = false;
      bool oCeYclQwjP = false;
      bool pXJajnJCuH = false;
      bool rNVWEHrAUh = false;
      bool KQqOnyGCIu = false;
      bool LjwHSdUoom = false;
      bool IRTpRbfITU = false;
      bool sPbCEYfuml = false;
      bool hHsAwHQNDa = false;
      bool mDLgYsxBxM = false;
      bool RyhmBuItDt = false;
      bool yZBDFBXTsJ = false;
      bool KSFshpEtcL = false;
      bool bdyaUiYGyA = false;
      bool yWKIbNBHbX = false;
      string aXIWdOuWrH;
      string gPfmHOVzyj;
      string tGeaWUGOEU;
      string oAdZpxgBzI;
      string CeerwcNSGt;
      string htULyUrhzJ;
      string HfRWRgkFxJ;
      string gUAphObles;
      string GnHKltfSaU;
      string EzBpBVMHaP;
      string rIUwNNtddi;
      string sFDFDSYHjW;
      string ASdbEhTJoL;
      string CTLOByTKxY;
      string ABnrbyuumh;
      string xFWDOYdsrf;
      string sjoSgYtnEE;
      string zNKLWzdlzF;
      string lXWGNwxIAb;
      string UZSQePMVKD;
      if(aXIWdOuWrH == rIUwNNtddi){EHqhijuLfP = true;}
      else if(rIUwNNtddi == aXIWdOuWrH){LjwHSdUoom = true;}
      if(gPfmHOVzyj == sFDFDSYHjW){urslsVNhEk = true;}
      else if(sFDFDSYHjW == gPfmHOVzyj){IRTpRbfITU = true;}
      if(tGeaWUGOEU == ASdbEhTJoL){almbjYtsfH = true;}
      else if(ASdbEhTJoL == tGeaWUGOEU){sPbCEYfuml = true;}
      if(oAdZpxgBzI == CTLOByTKxY){lIawBdfoXd = true;}
      else if(CTLOByTKxY == oAdZpxgBzI){hHsAwHQNDa = true;}
      if(CeerwcNSGt == ABnrbyuumh){AlbkgbggWJ = true;}
      else if(ABnrbyuumh == CeerwcNSGt){mDLgYsxBxM = true;}
      if(htULyUrhzJ == xFWDOYdsrf){CeQZbSTOxJ = true;}
      else if(xFWDOYdsrf == htULyUrhzJ){RyhmBuItDt = true;}
      if(HfRWRgkFxJ == sjoSgYtnEE){oCeYclQwjP = true;}
      else if(sjoSgYtnEE == HfRWRgkFxJ){yZBDFBXTsJ = true;}
      if(gUAphObles == zNKLWzdlzF){pXJajnJCuH = true;}
      if(GnHKltfSaU == lXWGNwxIAb){rNVWEHrAUh = true;}
      if(EzBpBVMHaP == UZSQePMVKD){KQqOnyGCIu = true;}
      while(zNKLWzdlzF == gUAphObles){KSFshpEtcL = true;}
      while(lXWGNwxIAb == lXWGNwxIAb){bdyaUiYGyA = true;}
      while(UZSQePMVKD == UZSQePMVKD){yWKIbNBHbX = true;}
      if(EHqhijuLfP == true){EHqhijuLfP = false;}
      if(urslsVNhEk == true){urslsVNhEk = false;}
      if(almbjYtsfH == true){almbjYtsfH = false;}
      if(lIawBdfoXd == true){lIawBdfoXd = false;}
      if(AlbkgbggWJ == true){AlbkgbggWJ = false;}
      if(CeQZbSTOxJ == true){CeQZbSTOxJ = false;}
      if(oCeYclQwjP == true){oCeYclQwjP = false;}
      if(pXJajnJCuH == true){pXJajnJCuH = false;}
      if(rNVWEHrAUh == true){rNVWEHrAUh = false;}
      if(KQqOnyGCIu == true){KQqOnyGCIu = false;}
      if(LjwHSdUoom == true){LjwHSdUoom = false;}
      if(IRTpRbfITU == true){IRTpRbfITU = false;}
      if(sPbCEYfuml == true){sPbCEYfuml = false;}
      if(hHsAwHQNDa == true){hHsAwHQNDa = false;}
      if(mDLgYsxBxM == true){mDLgYsxBxM = false;}
      if(RyhmBuItDt == true){RyhmBuItDt = false;}
      if(yZBDFBXTsJ == true){yZBDFBXTsJ = false;}
      if(KSFshpEtcL == true){KSFshpEtcL = false;}
      if(bdyaUiYGyA == true){bdyaUiYGyA = false;}
      if(yWKIbNBHbX == true){yWKIbNBHbX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WPXWYBLTPC
{ 
  void rXtupRrHJz()
  { 
      bool yIrbVZtZlQ = false;
      bool bpVjTRGHlg = false;
      bool KoOLPoFMkx = false;
      bool bPVnstqpCF = false;
      bool XtRZDtqCVK = false;
      bool SdKDnJtfMg = false;
      bool ThnnnLTgqY = false;
      bool aQFgIPWnIV = false;
      bool yDqadyERAj = false;
      bool AKdUkpGdkr = false;
      bool ZJLwiCYduX = false;
      bool lFXphQqNJp = false;
      bool GBgGXQljuS = false;
      bool IsCQwortqb = false;
      bool YaWbxumnmU = false;
      bool zsTukXcEXS = false;
      bool PohbPsCHss = false;
      bool XwVgQfeEJc = false;
      bool cyxaSPYHeX = false;
      bool LnWXMjrtME = false;
      string mSYsIGBYPo;
      string nLkUfJySCZ;
      string KLSQzErUEa;
      string wOJrqyAmNJ;
      string FhVYjQhAtz;
      string daUirbzIsD;
      string OgUosYBrdh;
      string JLFrUcosgi;
      string WqZEwVtaAO;
      string yqsJuXNgfK;
      string OoWLpSVcNP;
      string lGbKgWGQrW;
      string earOjSRuww;
      string PIMVTgUONd;
      string zQNkbrOicY;
      string RwnIenxHbX;
      string AZfQzdsFqA;
      string CrCOWNMHlr;
      string DiSXeSTDqe;
      string jMlpcZkwky;
      if(mSYsIGBYPo == OoWLpSVcNP){yIrbVZtZlQ = true;}
      else if(OoWLpSVcNP == mSYsIGBYPo){ZJLwiCYduX = true;}
      if(nLkUfJySCZ == lGbKgWGQrW){bpVjTRGHlg = true;}
      else if(lGbKgWGQrW == nLkUfJySCZ){lFXphQqNJp = true;}
      if(KLSQzErUEa == earOjSRuww){KoOLPoFMkx = true;}
      else if(earOjSRuww == KLSQzErUEa){GBgGXQljuS = true;}
      if(wOJrqyAmNJ == PIMVTgUONd){bPVnstqpCF = true;}
      else if(PIMVTgUONd == wOJrqyAmNJ){IsCQwortqb = true;}
      if(FhVYjQhAtz == zQNkbrOicY){XtRZDtqCVK = true;}
      else if(zQNkbrOicY == FhVYjQhAtz){YaWbxumnmU = true;}
      if(daUirbzIsD == RwnIenxHbX){SdKDnJtfMg = true;}
      else if(RwnIenxHbX == daUirbzIsD){zsTukXcEXS = true;}
      if(OgUosYBrdh == AZfQzdsFqA){ThnnnLTgqY = true;}
      else if(AZfQzdsFqA == OgUosYBrdh){PohbPsCHss = true;}
      if(JLFrUcosgi == CrCOWNMHlr){aQFgIPWnIV = true;}
      if(WqZEwVtaAO == DiSXeSTDqe){yDqadyERAj = true;}
      if(yqsJuXNgfK == jMlpcZkwky){AKdUkpGdkr = true;}
      while(CrCOWNMHlr == JLFrUcosgi){XwVgQfeEJc = true;}
      while(DiSXeSTDqe == DiSXeSTDqe){cyxaSPYHeX = true;}
      while(jMlpcZkwky == jMlpcZkwky){LnWXMjrtME = true;}
      if(yIrbVZtZlQ == true){yIrbVZtZlQ = false;}
      if(bpVjTRGHlg == true){bpVjTRGHlg = false;}
      if(KoOLPoFMkx == true){KoOLPoFMkx = false;}
      if(bPVnstqpCF == true){bPVnstqpCF = false;}
      if(XtRZDtqCVK == true){XtRZDtqCVK = false;}
      if(SdKDnJtfMg == true){SdKDnJtfMg = false;}
      if(ThnnnLTgqY == true){ThnnnLTgqY = false;}
      if(aQFgIPWnIV == true){aQFgIPWnIV = false;}
      if(yDqadyERAj == true){yDqadyERAj = false;}
      if(AKdUkpGdkr == true){AKdUkpGdkr = false;}
      if(ZJLwiCYduX == true){ZJLwiCYduX = false;}
      if(lFXphQqNJp == true){lFXphQqNJp = false;}
      if(GBgGXQljuS == true){GBgGXQljuS = false;}
      if(IsCQwortqb == true){IsCQwortqb = false;}
      if(YaWbxumnmU == true){YaWbxumnmU = false;}
      if(zsTukXcEXS == true){zsTukXcEXS = false;}
      if(PohbPsCHss == true){PohbPsCHss = false;}
      if(XwVgQfeEJc == true){XwVgQfeEJc = false;}
      if(cyxaSPYHeX == true){cyxaSPYHeX = false;}
      if(LnWXMjrtME == true){LnWXMjrtME = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYGSBOTESB
{ 
  void csTWUnsxbT()
  { 
      bool DNBlCVXZsu = false;
      bool tBbjtSSpQU = false;
      bool tfYGcnAZGs = false;
      bool ghTtJOqzwm = false;
      bool zZBRKfRZUF = false;
      bool lUZhhXntJN = false;
      bool UyTzOLhgZf = false;
      bool aStcVUdGuw = false;
      bool VaEAHLIkMl = false;
      bool ZxohRAFCDz = false;
      bool yjAoeSawMN = false;
      bool sgyMqtsTqC = false;
      bool DxUmFddLLV = false;
      bool PbCwylZPUo = false;
      bool kLYzssycpX = false;
      bool GkKBuBPNiA = false;
      bool oPkpxRdBOF = false;
      bool TcyCQqXVsL = false;
      bool eAVmOdQBBx = false;
      bool WMgUAVZhBb = false;
      string onAcIKmKmo;
      string DzWMddPjVw;
      string UNocLouYAU;
      string kodbwsMNja;
      string KxmDtdnIbQ;
      string SnSzBazWQT;
      string OOJREOUtPk;
      string RCAukXalhg;
      string AlxjBwWeZV;
      string sowQMwmVyf;
      string JsspyQnWOd;
      string zNojSbQZPH;
      string rpTsrbFiin;
      string jFmBXHsGkk;
      string IzQwWeAMxj;
      string eMFqnSYzxV;
      string LEnZstamLL;
      string hJneyrYWWN;
      string brlyIXzuNE;
      string htJOYEKqDb;
      if(onAcIKmKmo == JsspyQnWOd){DNBlCVXZsu = true;}
      else if(JsspyQnWOd == onAcIKmKmo){yjAoeSawMN = true;}
      if(DzWMddPjVw == zNojSbQZPH){tBbjtSSpQU = true;}
      else if(zNojSbQZPH == DzWMddPjVw){sgyMqtsTqC = true;}
      if(UNocLouYAU == rpTsrbFiin){tfYGcnAZGs = true;}
      else if(rpTsrbFiin == UNocLouYAU){DxUmFddLLV = true;}
      if(kodbwsMNja == jFmBXHsGkk){ghTtJOqzwm = true;}
      else if(jFmBXHsGkk == kodbwsMNja){PbCwylZPUo = true;}
      if(KxmDtdnIbQ == IzQwWeAMxj){zZBRKfRZUF = true;}
      else if(IzQwWeAMxj == KxmDtdnIbQ){kLYzssycpX = true;}
      if(SnSzBazWQT == eMFqnSYzxV){lUZhhXntJN = true;}
      else if(eMFqnSYzxV == SnSzBazWQT){GkKBuBPNiA = true;}
      if(OOJREOUtPk == LEnZstamLL){UyTzOLhgZf = true;}
      else if(LEnZstamLL == OOJREOUtPk){oPkpxRdBOF = true;}
      if(RCAukXalhg == hJneyrYWWN){aStcVUdGuw = true;}
      if(AlxjBwWeZV == brlyIXzuNE){VaEAHLIkMl = true;}
      if(sowQMwmVyf == htJOYEKqDb){ZxohRAFCDz = true;}
      while(hJneyrYWWN == RCAukXalhg){TcyCQqXVsL = true;}
      while(brlyIXzuNE == brlyIXzuNE){eAVmOdQBBx = true;}
      while(htJOYEKqDb == htJOYEKqDb){WMgUAVZhBb = true;}
      if(DNBlCVXZsu == true){DNBlCVXZsu = false;}
      if(tBbjtSSpQU == true){tBbjtSSpQU = false;}
      if(tfYGcnAZGs == true){tfYGcnAZGs = false;}
      if(ghTtJOqzwm == true){ghTtJOqzwm = false;}
      if(zZBRKfRZUF == true){zZBRKfRZUF = false;}
      if(lUZhhXntJN == true){lUZhhXntJN = false;}
      if(UyTzOLhgZf == true){UyTzOLhgZf = false;}
      if(aStcVUdGuw == true){aStcVUdGuw = false;}
      if(VaEAHLIkMl == true){VaEAHLIkMl = false;}
      if(ZxohRAFCDz == true){ZxohRAFCDz = false;}
      if(yjAoeSawMN == true){yjAoeSawMN = false;}
      if(sgyMqtsTqC == true){sgyMqtsTqC = false;}
      if(DxUmFddLLV == true){DxUmFddLLV = false;}
      if(PbCwylZPUo == true){PbCwylZPUo = false;}
      if(kLYzssycpX == true){kLYzssycpX = false;}
      if(GkKBuBPNiA == true){GkKBuBPNiA = false;}
      if(oPkpxRdBOF == true){oPkpxRdBOF = false;}
      if(TcyCQqXVsL == true){TcyCQqXVsL = false;}
      if(eAVmOdQBBx == true){eAVmOdQBBx = false;}
      if(WMgUAVZhBb == true){WMgUAVZhBb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELOVJYHCSW
{ 
  void gyLfeOZSNb()
  { 
      bool JihtIWCVWt = false;
      bool JyRIJQaBBo = false;
      bool YcSyDkAMTl = false;
      bool rAVXooKpXL = false;
      bool DZTLjHqNWr = false;
      bool OgAkhfPjpW = false;
      bool VpBjBJcsST = false;
      bool GjcplzJHNw = false;
      bool tmobXLzkpI = false;
      bool ZaABoMXiJa = false;
      bool eytDldDKzh = false;
      bool VHVtchBZLp = false;
      bool KrDKtfjaAY = false;
      bool bZymRuslpt = false;
      bool HnlHmREFYH = false;
      bool LxWTPmtiIG = false;
      bool scKZGuJhcg = false;
      bool nPiRhWGuXc = false;
      bool aeCrMdDdXe = false;
      bool BJcjAecLBq = false;
      string sKIBnhXIXp;
      string SMLCihgsLX;
      string okfWtOTMaa;
      string IsbYBStjoU;
      string DjsLklAGzA;
      string bFJeDIelHZ;
      string OLgwhZkmBQ;
      string nxEpTFrUlH;
      string OMMZyDixUs;
      string nHbOFrCwdK;
      string AMFiMeASKy;
      string QKAAKCzGxe;
      string pnRIbfUoka;
      string CupaGBGcNT;
      string CPlVcdHbED;
      string swzzUMuxGg;
      string KLhiuUTYsJ;
      string uWsccZCwfy;
      string XskghGupFt;
      string GJVgJphCZH;
      if(sKIBnhXIXp == AMFiMeASKy){JihtIWCVWt = true;}
      else if(AMFiMeASKy == sKIBnhXIXp){eytDldDKzh = true;}
      if(SMLCihgsLX == QKAAKCzGxe){JyRIJQaBBo = true;}
      else if(QKAAKCzGxe == SMLCihgsLX){VHVtchBZLp = true;}
      if(okfWtOTMaa == pnRIbfUoka){YcSyDkAMTl = true;}
      else if(pnRIbfUoka == okfWtOTMaa){KrDKtfjaAY = true;}
      if(IsbYBStjoU == CupaGBGcNT){rAVXooKpXL = true;}
      else if(CupaGBGcNT == IsbYBStjoU){bZymRuslpt = true;}
      if(DjsLklAGzA == CPlVcdHbED){DZTLjHqNWr = true;}
      else if(CPlVcdHbED == DjsLklAGzA){HnlHmREFYH = true;}
      if(bFJeDIelHZ == swzzUMuxGg){OgAkhfPjpW = true;}
      else if(swzzUMuxGg == bFJeDIelHZ){LxWTPmtiIG = true;}
      if(OLgwhZkmBQ == KLhiuUTYsJ){VpBjBJcsST = true;}
      else if(KLhiuUTYsJ == OLgwhZkmBQ){scKZGuJhcg = true;}
      if(nxEpTFrUlH == uWsccZCwfy){GjcplzJHNw = true;}
      if(OMMZyDixUs == XskghGupFt){tmobXLzkpI = true;}
      if(nHbOFrCwdK == GJVgJphCZH){ZaABoMXiJa = true;}
      while(uWsccZCwfy == nxEpTFrUlH){nPiRhWGuXc = true;}
      while(XskghGupFt == XskghGupFt){aeCrMdDdXe = true;}
      while(GJVgJphCZH == GJVgJphCZH){BJcjAecLBq = true;}
      if(JihtIWCVWt == true){JihtIWCVWt = false;}
      if(JyRIJQaBBo == true){JyRIJQaBBo = false;}
      if(YcSyDkAMTl == true){YcSyDkAMTl = false;}
      if(rAVXooKpXL == true){rAVXooKpXL = false;}
      if(DZTLjHqNWr == true){DZTLjHqNWr = false;}
      if(OgAkhfPjpW == true){OgAkhfPjpW = false;}
      if(VpBjBJcsST == true){VpBjBJcsST = false;}
      if(GjcplzJHNw == true){GjcplzJHNw = false;}
      if(tmobXLzkpI == true){tmobXLzkpI = false;}
      if(ZaABoMXiJa == true){ZaABoMXiJa = false;}
      if(eytDldDKzh == true){eytDldDKzh = false;}
      if(VHVtchBZLp == true){VHVtchBZLp = false;}
      if(KrDKtfjaAY == true){KrDKtfjaAY = false;}
      if(bZymRuslpt == true){bZymRuslpt = false;}
      if(HnlHmREFYH == true){HnlHmREFYH = false;}
      if(LxWTPmtiIG == true){LxWTPmtiIG = false;}
      if(scKZGuJhcg == true){scKZGuJhcg = false;}
      if(nPiRhWGuXc == true){nPiRhWGuXc = false;}
      if(aeCrMdDdXe == true){aeCrMdDdXe = false;}
      if(BJcjAecLBq == true){BJcjAecLBq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GRKWTXUQXT
{ 
  void yoSiaxLeQd()
  { 
      bool TkCUdrKHSQ = false;
      bool lVaEbtZdDo = false;
      bool yOJwmnACwF = false;
      bool XXOqoyhUOu = false;
      bool zSlgifmlDY = false;
      bool WWVYmEbGhp = false;
      bool qILMrNGjPd = false;
      bool LEOHpfccNH = false;
      bool BNyWhACpEj = false;
      bool WbmYEqHYnU = false;
      bool YCWZMRINhG = false;
      bool bzrZodJndr = false;
      bool KQffHjQpDz = false;
      bool XDnrhypXKQ = false;
      bool roHxHWiMjZ = false;
      bool gStuJIWqSb = false;
      bool BRJiiYKArp = false;
      bool mkdNzVJhXj = false;
      bool BDGdREIriZ = false;
      bool azFhOZfXOi = false;
      string GfJYIzPyIo;
      string RunBHaPfDz;
      string zGfmyeVCoO;
      string xuAjgeKSdd;
      string tcbZKtqMmG;
      string gTXTWAzWac;
      string cMJsrVuDUc;
      string QxBZEVeGbE;
      string nJPhgdWfNg;
      string fmqAAgThhn;
      string ynrKojRyOA;
      string VrtWoTxaLN;
      string yOonwcFBZX;
      string CwYmFARFrx;
      string MYQMKmrUKf;
      string jrVTpjyDNM;
      string ePXqyYTHRo;
      string BrhOBYxccI;
      string jkpsmJZExU;
      string BNqfSwBYNl;
      if(GfJYIzPyIo == ynrKojRyOA){TkCUdrKHSQ = true;}
      else if(ynrKojRyOA == GfJYIzPyIo){YCWZMRINhG = true;}
      if(RunBHaPfDz == VrtWoTxaLN){lVaEbtZdDo = true;}
      else if(VrtWoTxaLN == RunBHaPfDz){bzrZodJndr = true;}
      if(zGfmyeVCoO == yOonwcFBZX){yOJwmnACwF = true;}
      else if(yOonwcFBZX == zGfmyeVCoO){KQffHjQpDz = true;}
      if(xuAjgeKSdd == CwYmFARFrx){XXOqoyhUOu = true;}
      else if(CwYmFARFrx == xuAjgeKSdd){XDnrhypXKQ = true;}
      if(tcbZKtqMmG == MYQMKmrUKf){zSlgifmlDY = true;}
      else if(MYQMKmrUKf == tcbZKtqMmG){roHxHWiMjZ = true;}
      if(gTXTWAzWac == jrVTpjyDNM){WWVYmEbGhp = true;}
      else if(jrVTpjyDNM == gTXTWAzWac){gStuJIWqSb = true;}
      if(cMJsrVuDUc == ePXqyYTHRo){qILMrNGjPd = true;}
      else if(ePXqyYTHRo == cMJsrVuDUc){BRJiiYKArp = true;}
      if(QxBZEVeGbE == BrhOBYxccI){LEOHpfccNH = true;}
      if(nJPhgdWfNg == jkpsmJZExU){BNyWhACpEj = true;}
      if(fmqAAgThhn == BNqfSwBYNl){WbmYEqHYnU = true;}
      while(BrhOBYxccI == QxBZEVeGbE){mkdNzVJhXj = true;}
      while(jkpsmJZExU == jkpsmJZExU){BDGdREIriZ = true;}
      while(BNqfSwBYNl == BNqfSwBYNl){azFhOZfXOi = true;}
      if(TkCUdrKHSQ == true){TkCUdrKHSQ = false;}
      if(lVaEbtZdDo == true){lVaEbtZdDo = false;}
      if(yOJwmnACwF == true){yOJwmnACwF = false;}
      if(XXOqoyhUOu == true){XXOqoyhUOu = false;}
      if(zSlgifmlDY == true){zSlgifmlDY = false;}
      if(WWVYmEbGhp == true){WWVYmEbGhp = false;}
      if(qILMrNGjPd == true){qILMrNGjPd = false;}
      if(LEOHpfccNH == true){LEOHpfccNH = false;}
      if(BNyWhACpEj == true){BNyWhACpEj = false;}
      if(WbmYEqHYnU == true){WbmYEqHYnU = false;}
      if(YCWZMRINhG == true){YCWZMRINhG = false;}
      if(bzrZodJndr == true){bzrZodJndr = false;}
      if(KQffHjQpDz == true){KQffHjQpDz = false;}
      if(XDnrhypXKQ == true){XDnrhypXKQ = false;}
      if(roHxHWiMjZ == true){roHxHWiMjZ = false;}
      if(gStuJIWqSb == true){gStuJIWqSb = false;}
      if(BRJiiYKArp == true){BRJiiYKArp = false;}
      if(mkdNzVJhXj == true){mkdNzVJhXj = false;}
      if(BDGdREIriZ == true){BDGdREIriZ = false;}
      if(azFhOZfXOi == true){azFhOZfXOi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CTDFNRAWFG
{ 
  void bdUMwiSEwh()
  { 
      bool CcwwIYzTQZ = false;
      bool ohelJQyqPI = false;
      bool BRorCISUSF = false;
      bool ebujWOzqdH = false;
      bool tGMcjLjisF = false;
      bool OwssrkmEtA = false;
      bool GeBLuNltOu = false;
      bool QGNHNuFMHp = false;
      bool YjaNpiiCrl = false;
      bool buxdBPEAhW = false;
      bool YoTynHikfx = false;
      bool eawDaVEnUL = false;
      bool djCcTUJiGx = false;
      bool pEdjQiQbYh = false;
      bool AyWtGAytCe = false;
      bool LQfVsolqeS = false;
      bool yzehHawMlr = false;
      bool FbPlLfNIVS = false;
      bool WPgalZXIqb = false;
      bool wZwFjBSnme = false;
      string olQLnDBMxe;
      string DCqgGELnDk;
      string WSLAZMXVMV;
      string nFNPBecTpH;
      string LBFtaGHoIq;
      string PSqQpWZQla;
      string efzbpxnaeb;
      string arxuZUMRZS;
      string FiMVFVNxZe;
      string FMgOcfCdEc;
      string RfJgPWUwqV;
      string JIpSVwSdVT;
      string jqBAVNKhSs;
      string ShNxAYYeFh;
      string AQFEVxVOsf;
      string MXHjsaeJKB;
      string MmdxCbtsRw;
      string XmYnSSkxdY;
      string qwnlgtZcDZ;
      string tOUDVNmIBt;
      if(olQLnDBMxe == RfJgPWUwqV){CcwwIYzTQZ = true;}
      else if(RfJgPWUwqV == olQLnDBMxe){YoTynHikfx = true;}
      if(DCqgGELnDk == JIpSVwSdVT){ohelJQyqPI = true;}
      else if(JIpSVwSdVT == DCqgGELnDk){eawDaVEnUL = true;}
      if(WSLAZMXVMV == jqBAVNKhSs){BRorCISUSF = true;}
      else if(jqBAVNKhSs == WSLAZMXVMV){djCcTUJiGx = true;}
      if(nFNPBecTpH == ShNxAYYeFh){ebujWOzqdH = true;}
      else if(ShNxAYYeFh == nFNPBecTpH){pEdjQiQbYh = true;}
      if(LBFtaGHoIq == AQFEVxVOsf){tGMcjLjisF = true;}
      else if(AQFEVxVOsf == LBFtaGHoIq){AyWtGAytCe = true;}
      if(PSqQpWZQla == MXHjsaeJKB){OwssrkmEtA = true;}
      else if(MXHjsaeJKB == PSqQpWZQla){LQfVsolqeS = true;}
      if(efzbpxnaeb == MmdxCbtsRw){GeBLuNltOu = true;}
      else if(MmdxCbtsRw == efzbpxnaeb){yzehHawMlr = true;}
      if(arxuZUMRZS == XmYnSSkxdY){QGNHNuFMHp = true;}
      if(FiMVFVNxZe == qwnlgtZcDZ){YjaNpiiCrl = true;}
      if(FMgOcfCdEc == tOUDVNmIBt){buxdBPEAhW = true;}
      while(XmYnSSkxdY == arxuZUMRZS){FbPlLfNIVS = true;}
      while(qwnlgtZcDZ == qwnlgtZcDZ){WPgalZXIqb = true;}
      while(tOUDVNmIBt == tOUDVNmIBt){wZwFjBSnme = true;}
      if(CcwwIYzTQZ == true){CcwwIYzTQZ = false;}
      if(ohelJQyqPI == true){ohelJQyqPI = false;}
      if(BRorCISUSF == true){BRorCISUSF = false;}
      if(ebujWOzqdH == true){ebujWOzqdH = false;}
      if(tGMcjLjisF == true){tGMcjLjisF = false;}
      if(OwssrkmEtA == true){OwssrkmEtA = false;}
      if(GeBLuNltOu == true){GeBLuNltOu = false;}
      if(QGNHNuFMHp == true){QGNHNuFMHp = false;}
      if(YjaNpiiCrl == true){YjaNpiiCrl = false;}
      if(buxdBPEAhW == true){buxdBPEAhW = false;}
      if(YoTynHikfx == true){YoTynHikfx = false;}
      if(eawDaVEnUL == true){eawDaVEnUL = false;}
      if(djCcTUJiGx == true){djCcTUJiGx = false;}
      if(pEdjQiQbYh == true){pEdjQiQbYh = false;}
      if(AyWtGAytCe == true){AyWtGAytCe = false;}
      if(LQfVsolqeS == true){LQfVsolqeS = false;}
      if(yzehHawMlr == true){yzehHawMlr = false;}
      if(FbPlLfNIVS == true){FbPlLfNIVS = false;}
      if(WPgalZXIqb == true){WPgalZXIqb = false;}
      if(wZwFjBSnme == true){wZwFjBSnme = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ROUDCFUKAB
{ 
  void BjKiejHnpG()
  { 
      bool bMgjhaFiNh = false;
      bool OYeXwWclJK = false;
      bool MWtxHoWInr = false;
      bool CBAcTapCqO = false;
      bool dVSaDUseRx = false;
      bool XwCsGFRjbs = false;
      bool DxuUfNYBDU = false;
      bool gZutfpDSsm = false;
      bool urppUFzGVO = false;
      bool IGZxKgaxup = false;
      bool uqaxQxBHNQ = false;
      bool BzpnxLGFzZ = false;
      bool OSfoLazxiy = false;
      bool PFXDrEQrYW = false;
      bool EqrENJPkAz = false;
      bool ZUxVabLlkp = false;
      bool yDXOBuamws = false;
      bool tNgcUXaabC = false;
      bool LNwjYtHBbQ = false;
      bool reHiYASdDR = false;
      string NTcSWTLpZr;
      string woYOCCqbMo;
      string OidZNryBgW;
      string epURfJANpf;
      string FGUbCTnqlr;
      string rZOXNepDFd;
      string VKJDNFUGhs;
      string CckfjIOBXt;
      string EHOneEbxDB;
      string SxILKuxQOw;
      string ygIspOohmF;
      string PofLZNuUYI;
      string dWCgZFUYVo;
      string LxlbuXzVyP;
      string PsJykdQxlw;
      string zbrGRbdaSj;
      string tPLytRCEPB;
      string NYWIsjMEwu;
      string nWmZoiFfJS;
      string tYCOUAhLET;
      if(NTcSWTLpZr == ygIspOohmF){bMgjhaFiNh = true;}
      else if(ygIspOohmF == NTcSWTLpZr){uqaxQxBHNQ = true;}
      if(woYOCCqbMo == PofLZNuUYI){OYeXwWclJK = true;}
      else if(PofLZNuUYI == woYOCCqbMo){BzpnxLGFzZ = true;}
      if(OidZNryBgW == dWCgZFUYVo){MWtxHoWInr = true;}
      else if(dWCgZFUYVo == OidZNryBgW){OSfoLazxiy = true;}
      if(epURfJANpf == LxlbuXzVyP){CBAcTapCqO = true;}
      else if(LxlbuXzVyP == epURfJANpf){PFXDrEQrYW = true;}
      if(FGUbCTnqlr == PsJykdQxlw){dVSaDUseRx = true;}
      else if(PsJykdQxlw == FGUbCTnqlr){EqrENJPkAz = true;}
      if(rZOXNepDFd == zbrGRbdaSj){XwCsGFRjbs = true;}
      else if(zbrGRbdaSj == rZOXNepDFd){ZUxVabLlkp = true;}
      if(VKJDNFUGhs == tPLytRCEPB){DxuUfNYBDU = true;}
      else if(tPLytRCEPB == VKJDNFUGhs){yDXOBuamws = true;}
      if(CckfjIOBXt == NYWIsjMEwu){gZutfpDSsm = true;}
      if(EHOneEbxDB == nWmZoiFfJS){urppUFzGVO = true;}
      if(SxILKuxQOw == tYCOUAhLET){IGZxKgaxup = true;}
      while(NYWIsjMEwu == CckfjIOBXt){tNgcUXaabC = true;}
      while(nWmZoiFfJS == nWmZoiFfJS){LNwjYtHBbQ = true;}
      while(tYCOUAhLET == tYCOUAhLET){reHiYASdDR = true;}
      if(bMgjhaFiNh == true){bMgjhaFiNh = false;}
      if(OYeXwWclJK == true){OYeXwWclJK = false;}
      if(MWtxHoWInr == true){MWtxHoWInr = false;}
      if(CBAcTapCqO == true){CBAcTapCqO = false;}
      if(dVSaDUseRx == true){dVSaDUseRx = false;}
      if(XwCsGFRjbs == true){XwCsGFRjbs = false;}
      if(DxuUfNYBDU == true){DxuUfNYBDU = false;}
      if(gZutfpDSsm == true){gZutfpDSsm = false;}
      if(urppUFzGVO == true){urppUFzGVO = false;}
      if(IGZxKgaxup == true){IGZxKgaxup = false;}
      if(uqaxQxBHNQ == true){uqaxQxBHNQ = false;}
      if(BzpnxLGFzZ == true){BzpnxLGFzZ = false;}
      if(OSfoLazxiy == true){OSfoLazxiy = false;}
      if(PFXDrEQrYW == true){PFXDrEQrYW = false;}
      if(EqrENJPkAz == true){EqrENJPkAz = false;}
      if(ZUxVabLlkp == true){ZUxVabLlkp = false;}
      if(yDXOBuamws == true){yDXOBuamws = false;}
      if(tNgcUXaabC == true){tNgcUXaabC = false;}
      if(LNwjYtHBbQ == true){LNwjYtHBbQ = false;}
      if(reHiYASdDR == true){reHiYASdDR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUZBURNJOR
{ 
  void ZNkDOiXStH()
  { 
      bool qBmJZHjmqz = false;
      bool ZMVgNORBJm = false;
      bool HLrujZVOmR = false;
      bool aOUDMEDhxn = false;
      bool neMRhbJgXt = false;
      bool aaUVHfIqYz = false;
      bool kVzZXKrSUI = false;
      bool LiEVzczaMI = false;
      bool PoprpAszug = false;
      bool wLIxCRemtX = false;
      bool iqLOirWyVe = false;
      bool fheQiueGiX = false;
      bool RsWmMAZGTg = false;
      bool xMfoYYcbJy = false;
      bool dtcQAOfrNH = false;
      bool mXDWGpTYCh = false;
      bool RPengTBprK = false;
      bool RDwjsWQGmy = false;
      bool ThrLtYIJhh = false;
      bool EEZagNOnjf = false;
      string dfjladUfyo;
      string ApzNSIadHT;
      string kElZgAlnjl;
      string nPhKoZAZOy;
      string GlHPtGeUqs;
      string lAlFTYsJFZ;
      string qfwLAjHoYs;
      string HBPJNzxVeZ;
      string VQxpAmdcpQ;
      string fpUnGapuOJ;
      string yowykkkbrU;
      string aXeeEaiFLM;
      string GeyHMRfaDm;
      string IBGUbfUzFO;
      string CBkUoILpif;
      string qjjCDTpnkT;
      string FJYFLZQJDY;
      string FjAxKEtdSE;
      string FprWuYRERH;
      string ofNkJrceIP;
      if(dfjladUfyo == yowykkkbrU){qBmJZHjmqz = true;}
      else if(yowykkkbrU == dfjladUfyo){iqLOirWyVe = true;}
      if(ApzNSIadHT == aXeeEaiFLM){ZMVgNORBJm = true;}
      else if(aXeeEaiFLM == ApzNSIadHT){fheQiueGiX = true;}
      if(kElZgAlnjl == GeyHMRfaDm){HLrujZVOmR = true;}
      else if(GeyHMRfaDm == kElZgAlnjl){RsWmMAZGTg = true;}
      if(nPhKoZAZOy == IBGUbfUzFO){aOUDMEDhxn = true;}
      else if(IBGUbfUzFO == nPhKoZAZOy){xMfoYYcbJy = true;}
      if(GlHPtGeUqs == CBkUoILpif){neMRhbJgXt = true;}
      else if(CBkUoILpif == GlHPtGeUqs){dtcQAOfrNH = true;}
      if(lAlFTYsJFZ == qjjCDTpnkT){aaUVHfIqYz = true;}
      else if(qjjCDTpnkT == lAlFTYsJFZ){mXDWGpTYCh = true;}
      if(qfwLAjHoYs == FJYFLZQJDY){kVzZXKrSUI = true;}
      else if(FJYFLZQJDY == qfwLAjHoYs){RPengTBprK = true;}
      if(HBPJNzxVeZ == FjAxKEtdSE){LiEVzczaMI = true;}
      if(VQxpAmdcpQ == FprWuYRERH){PoprpAszug = true;}
      if(fpUnGapuOJ == ofNkJrceIP){wLIxCRemtX = true;}
      while(FjAxKEtdSE == HBPJNzxVeZ){RDwjsWQGmy = true;}
      while(FprWuYRERH == FprWuYRERH){ThrLtYIJhh = true;}
      while(ofNkJrceIP == ofNkJrceIP){EEZagNOnjf = true;}
      if(qBmJZHjmqz == true){qBmJZHjmqz = false;}
      if(ZMVgNORBJm == true){ZMVgNORBJm = false;}
      if(HLrujZVOmR == true){HLrujZVOmR = false;}
      if(aOUDMEDhxn == true){aOUDMEDhxn = false;}
      if(neMRhbJgXt == true){neMRhbJgXt = false;}
      if(aaUVHfIqYz == true){aaUVHfIqYz = false;}
      if(kVzZXKrSUI == true){kVzZXKrSUI = false;}
      if(LiEVzczaMI == true){LiEVzczaMI = false;}
      if(PoprpAszug == true){PoprpAszug = false;}
      if(wLIxCRemtX == true){wLIxCRemtX = false;}
      if(iqLOirWyVe == true){iqLOirWyVe = false;}
      if(fheQiueGiX == true){fheQiueGiX = false;}
      if(RsWmMAZGTg == true){RsWmMAZGTg = false;}
      if(xMfoYYcbJy == true){xMfoYYcbJy = false;}
      if(dtcQAOfrNH == true){dtcQAOfrNH = false;}
      if(mXDWGpTYCh == true){mXDWGpTYCh = false;}
      if(RPengTBprK == true){RPengTBprK = false;}
      if(RDwjsWQGmy == true){RDwjsWQGmy = false;}
      if(ThrLtYIJhh == true){ThrLtYIJhh = false;}
      if(EEZagNOnjf == true){EEZagNOnjf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IMAIPUFQKI
{ 
  void GWUKMdYttS()
  { 
      bool OLddRmgsGX = false;
      bool dwVSOEuCAd = false;
      bool OLpmsMhOgd = false;
      bool ifEyXFjVPP = false;
      bool iIrWzWLdku = false;
      bool JFRZSDUqkE = false;
      bool ESLcnxrXtJ = false;
      bool UYljuFSSnW = false;
      bool AEdlTcNeeU = false;
      bool jskLLPxPiB = false;
      bool dniaZjSgdM = false;
      bool jBCODAoYIL = false;
      bool iMrZZbnaYe = false;
      bool IDjlrMUCLj = false;
      bool JgBSjhpVHL = false;
      bool aXGWSRwJBy = false;
      bool wrIyDgQQVq = false;
      bool elNYBCLZoq = false;
      bool lRTNEkwNTZ = false;
      bool PKBNmRYDOD = false;
      string fTOCnZjCyR;
      string qSiPZGSWfh;
      string UgHKZPZdeA;
      string ulxUqmxsCs;
      string JOatCUbGGD;
      string DIQzNzMDbY;
      string AGWyVEUOXm;
      string IZUmYFFMHF;
      string mTWaxmVyGr;
      string ZsQcsCrcXy;
      string zNhTucmdaH;
      string sAwVlfiuBi;
      string iWHeNOJqtW;
      string McoJFYkDfT;
      string ArWyyZxtqM;
      string SwaoOcFCGf;
      string TuiEuQKlPM;
      string ufOhhqzIgm;
      string QOAgDQBzuc;
      string ThxAAEISDh;
      if(fTOCnZjCyR == zNhTucmdaH){OLddRmgsGX = true;}
      else if(zNhTucmdaH == fTOCnZjCyR){dniaZjSgdM = true;}
      if(qSiPZGSWfh == sAwVlfiuBi){dwVSOEuCAd = true;}
      else if(sAwVlfiuBi == qSiPZGSWfh){jBCODAoYIL = true;}
      if(UgHKZPZdeA == iWHeNOJqtW){OLpmsMhOgd = true;}
      else if(iWHeNOJqtW == UgHKZPZdeA){iMrZZbnaYe = true;}
      if(ulxUqmxsCs == McoJFYkDfT){ifEyXFjVPP = true;}
      else if(McoJFYkDfT == ulxUqmxsCs){IDjlrMUCLj = true;}
      if(JOatCUbGGD == ArWyyZxtqM){iIrWzWLdku = true;}
      else if(ArWyyZxtqM == JOatCUbGGD){JgBSjhpVHL = true;}
      if(DIQzNzMDbY == SwaoOcFCGf){JFRZSDUqkE = true;}
      else if(SwaoOcFCGf == DIQzNzMDbY){aXGWSRwJBy = true;}
      if(AGWyVEUOXm == TuiEuQKlPM){ESLcnxrXtJ = true;}
      else if(TuiEuQKlPM == AGWyVEUOXm){wrIyDgQQVq = true;}
      if(IZUmYFFMHF == ufOhhqzIgm){UYljuFSSnW = true;}
      if(mTWaxmVyGr == QOAgDQBzuc){AEdlTcNeeU = true;}
      if(ZsQcsCrcXy == ThxAAEISDh){jskLLPxPiB = true;}
      while(ufOhhqzIgm == IZUmYFFMHF){elNYBCLZoq = true;}
      while(QOAgDQBzuc == QOAgDQBzuc){lRTNEkwNTZ = true;}
      while(ThxAAEISDh == ThxAAEISDh){PKBNmRYDOD = true;}
      if(OLddRmgsGX == true){OLddRmgsGX = false;}
      if(dwVSOEuCAd == true){dwVSOEuCAd = false;}
      if(OLpmsMhOgd == true){OLpmsMhOgd = false;}
      if(ifEyXFjVPP == true){ifEyXFjVPP = false;}
      if(iIrWzWLdku == true){iIrWzWLdku = false;}
      if(JFRZSDUqkE == true){JFRZSDUqkE = false;}
      if(ESLcnxrXtJ == true){ESLcnxrXtJ = false;}
      if(UYljuFSSnW == true){UYljuFSSnW = false;}
      if(AEdlTcNeeU == true){AEdlTcNeeU = false;}
      if(jskLLPxPiB == true){jskLLPxPiB = false;}
      if(dniaZjSgdM == true){dniaZjSgdM = false;}
      if(jBCODAoYIL == true){jBCODAoYIL = false;}
      if(iMrZZbnaYe == true){iMrZZbnaYe = false;}
      if(IDjlrMUCLj == true){IDjlrMUCLj = false;}
      if(JgBSjhpVHL == true){JgBSjhpVHL = false;}
      if(aXGWSRwJBy == true){aXGWSRwJBy = false;}
      if(wrIyDgQQVq == true){wrIyDgQQVq = false;}
      if(elNYBCLZoq == true){elNYBCLZoq = false;}
      if(lRTNEkwNTZ == true){lRTNEkwNTZ = false;}
      if(PKBNmRYDOD == true){PKBNmRYDOD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PLDCTXDHDJ
{ 
  void xiMMZZsneH()
  { 
      bool fEdUjTGdOG = false;
      bool PGMMKGJcPk = false;
      bool DkVuYCLEFx = false;
      bool DFrMFHCCwo = false;
      bool LFFLgKaRTA = false;
      bool KxgtTuhhwh = false;
      bool HCXQCKNAGC = false;
      bool EHfaZxeKON = false;
      bool bskFmGYysK = false;
      bool ZTGOhJhoJW = false;
      bool xZKQuDQGTW = false;
      bool PXThFOQSdu = false;
      bool kOGwcjAQrQ = false;
      bool OpAqQBhTJi = false;
      bool oSdWtCzXIS = false;
      bool rPKNkhSOmL = false;
      bool CANDHZWcQE = false;
      bool fwIuGSkjBa = false;
      bool kbHYYzemFi = false;
      bool hTgyfoFaPU = false;
      string CyxDtjULBr;
      string ksteZMgtHD;
      string ZOmImZiuwK;
      string IXGpMFXxQA;
      string EqokJeqIrQ;
      string ZrXqtnKoQU;
      string AYPqjMmDST;
      string nidGziYCyH;
      string iaDejPAOuY;
      string tifwAfayAw;
      string qmpYcpOQrL;
      string OHpJkZVkGT;
      string MYIsYFDhGS;
      string HaBBQujeCt;
      string BiVjJlrWKZ;
      string KpqgjSewzX;
      string mgJYDmFnso;
      string ppiMScCYil;
      string MfWgIRjURx;
      string QmeeGUZwfW;
      if(CyxDtjULBr == qmpYcpOQrL){fEdUjTGdOG = true;}
      else if(qmpYcpOQrL == CyxDtjULBr){xZKQuDQGTW = true;}
      if(ksteZMgtHD == OHpJkZVkGT){PGMMKGJcPk = true;}
      else if(OHpJkZVkGT == ksteZMgtHD){PXThFOQSdu = true;}
      if(ZOmImZiuwK == MYIsYFDhGS){DkVuYCLEFx = true;}
      else if(MYIsYFDhGS == ZOmImZiuwK){kOGwcjAQrQ = true;}
      if(IXGpMFXxQA == HaBBQujeCt){DFrMFHCCwo = true;}
      else if(HaBBQujeCt == IXGpMFXxQA){OpAqQBhTJi = true;}
      if(EqokJeqIrQ == BiVjJlrWKZ){LFFLgKaRTA = true;}
      else if(BiVjJlrWKZ == EqokJeqIrQ){oSdWtCzXIS = true;}
      if(ZrXqtnKoQU == KpqgjSewzX){KxgtTuhhwh = true;}
      else if(KpqgjSewzX == ZrXqtnKoQU){rPKNkhSOmL = true;}
      if(AYPqjMmDST == mgJYDmFnso){HCXQCKNAGC = true;}
      else if(mgJYDmFnso == AYPqjMmDST){CANDHZWcQE = true;}
      if(nidGziYCyH == ppiMScCYil){EHfaZxeKON = true;}
      if(iaDejPAOuY == MfWgIRjURx){bskFmGYysK = true;}
      if(tifwAfayAw == QmeeGUZwfW){ZTGOhJhoJW = true;}
      while(ppiMScCYil == nidGziYCyH){fwIuGSkjBa = true;}
      while(MfWgIRjURx == MfWgIRjURx){kbHYYzemFi = true;}
      while(QmeeGUZwfW == QmeeGUZwfW){hTgyfoFaPU = true;}
      if(fEdUjTGdOG == true){fEdUjTGdOG = false;}
      if(PGMMKGJcPk == true){PGMMKGJcPk = false;}
      if(DkVuYCLEFx == true){DkVuYCLEFx = false;}
      if(DFrMFHCCwo == true){DFrMFHCCwo = false;}
      if(LFFLgKaRTA == true){LFFLgKaRTA = false;}
      if(KxgtTuhhwh == true){KxgtTuhhwh = false;}
      if(HCXQCKNAGC == true){HCXQCKNAGC = false;}
      if(EHfaZxeKON == true){EHfaZxeKON = false;}
      if(bskFmGYysK == true){bskFmGYysK = false;}
      if(ZTGOhJhoJW == true){ZTGOhJhoJW = false;}
      if(xZKQuDQGTW == true){xZKQuDQGTW = false;}
      if(PXThFOQSdu == true){PXThFOQSdu = false;}
      if(kOGwcjAQrQ == true){kOGwcjAQrQ = false;}
      if(OpAqQBhTJi == true){OpAqQBhTJi = false;}
      if(oSdWtCzXIS == true){oSdWtCzXIS = false;}
      if(rPKNkhSOmL == true){rPKNkhSOmL = false;}
      if(CANDHZWcQE == true){CANDHZWcQE = false;}
      if(fwIuGSkjBa == true){fwIuGSkjBa = false;}
      if(kbHYYzemFi == true){kbHYYzemFi = false;}
      if(hTgyfoFaPU == true){hTgyfoFaPU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WVCLYDWGHS
{ 
  void ZABDuWXVoR()
  { 
      bool hfkoObPMSV = false;
      bool JYQWPydnor = false;
      bool dKYSVmfNZb = false;
      bool VLHTeiyKQb = false;
      bool fmVyogGsxo = false;
      bool iRbXpXGRTb = false;
      bool wBlpAxQxrg = false;
      bool ASXMLqnadn = false;
      bool glPkrDjjcG = false;
      bool bgqofdAeyq = false;
      bool QIAQoPtOLz = false;
      bool ifnetJkByw = false;
      bool NgTkESbhgh = false;
      bool pIblXXlzuc = false;
      bool JUXdXwrLtV = false;
      bool rzgBdioOLV = false;
      bool mLgdIZDCHW = false;
      bool XlFUlrIoNI = false;
      bool aPnLopbaHn = false;
      bool hWnZoxntUx = false;
      string bbwidINnia;
      string gbMxhuSbau;
      string jewQQREjJF;
      string DhDCDJSZLM;
      string ynpLyBllDw;
      string NOkUVwffSM;
      string DcecWyYJtX;
      string bsQNxuokSO;
      string fSfMqoxifG;
      string cmGyJUIMnz;
      string cbqeTUxXWa;
      string HuMDgkwSkg;
      string BodmuolSDc;
      string lbwSlEaArW;
      string rZLFzhZCRY;
      string XpbHymxEje;
      string heTtneztRb;
      string JwaOobdYnN;
      string OjAeEwAnUy;
      string GWPMnNFRQU;
      if(bbwidINnia == cbqeTUxXWa){hfkoObPMSV = true;}
      else if(cbqeTUxXWa == bbwidINnia){QIAQoPtOLz = true;}
      if(gbMxhuSbau == HuMDgkwSkg){JYQWPydnor = true;}
      else if(HuMDgkwSkg == gbMxhuSbau){ifnetJkByw = true;}
      if(jewQQREjJF == BodmuolSDc){dKYSVmfNZb = true;}
      else if(BodmuolSDc == jewQQREjJF){NgTkESbhgh = true;}
      if(DhDCDJSZLM == lbwSlEaArW){VLHTeiyKQb = true;}
      else if(lbwSlEaArW == DhDCDJSZLM){pIblXXlzuc = true;}
      if(ynpLyBllDw == rZLFzhZCRY){fmVyogGsxo = true;}
      else if(rZLFzhZCRY == ynpLyBllDw){JUXdXwrLtV = true;}
      if(NOkUVwffSM == XpbHymxEje){iRbXpXGRTb = true;}
      else if(XpbHymxEje == NOkUVwffSM){rzgBdioOLV = true;}
      if(DcecWyYJtX == heTtneztRb){wBlpAxQxrg = true;}
      else if(heTtneztRb == DcecWyYJtX){mLgdIZDCHW = true;}
      if(bsQNxuokSO == JwaOobdYnN){ASXMLqnadn = true;}
      if(fSfMqoxifG == OjAeEwAnUy){glPkrDjjcG = true;}
      if(cmGyJUIMnz == GWPMnNFRQU){bgqofdAeyq = true;}
      while(JwaOobdYnN == bsQNxuokSO){XlFUlrIoNI = true;}
      while(OjAeEwAnUy == OjAeEwAnUy){aPnLopbaHn = true;}
      while(GWPMnNFRQU == GWPMnNFRQU){hWnZoxntUx = true;}
      if(hfkoObPMSV == true){hfkoObPMSV = false;}
      if(JYQWPydnor == true){JYQWPydnor = false;}
      if(dKYSVmfNZb == true){dKYSVmfNZb = false;}
      if(VLHTeiyKQb == true){VLHTeiyKQb = false;}
      if(fmVyogGsxo == true){fmVyogGsxo = false;}
      if(iRbXpXGRTb == true){iRbXpXGRTb = false;}
      if(wBlpAxQxrg == true){wBlpAxQxrg = false;}
      if(ASXMLqnadn == true){ASXMLqnadn = false;}
      if(glPkrDjjcG == true){glPkrDjjcG = false;}
      if(bgqofdAeyq == true){bgqofdAeyq = false;}
      if(QIAQoPtOLz == true){QIAQoPtOLz = false;}
      if(ifnetJkByw == true){ifnetJkByw = false;}
      if(NgTkESbhgh == true){NgTkESbhgh = false;}
      if(pIblXXlzuc == true){pIblXXlzuc = false;}
      if(JUXdXwrLtV == true){JUXdXwrLtV = false;}
      if(rzgBdioOLV == true){rzgBdioOLV = false;}
      if(mLgdIZDCHW == true){mLgdIZDCHW = false;}
      if(XlFUlrIoNI == true){XlFUlrIoNI = false;}
      if(aPnLopbaHn == true){aPnLopbaHn = false;}
      if(hWnZoxntUx == true){hWnZoxntUx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DTOEBJTTCN
{ 
  void iEGkPqVUjE()
  { 
      bool dbfKPNTMGp = false;
      bool YOJtXtmTwJ = false;
      bool inPVHAAGWw = false;
      bool xmJhsAcwal = false;
      bool lafMPKmYsM = false;
      bool kQMcCoLKCO = false;
      bool NMpJrlEbAW = false;
      bool QqrJWIIDFx = false;
      bool NaNKKgZfeE = false;
      bool nStLYZkVTd = false;
      bool FLYWwtYDFt = false;
      bool fIEEBlzezL = false;
      bool MXwuhxwfjx = false;
      bool WmibqBCqNP = false;
      bool IWakYeOoJm = false;
      bool ZFVIRgOcny = false;
      bool yrSHWrZbMA = false;
      bool jHRiDoxKWC = false;
      bool iGWxXRQaKK = false;
      bool lYCORQDSOf = false;
      string IPwJeTdBdK;
      string zjWNjbcbUt;
      string ptuWDSUtXb;
      string KLqIZNPRUh;
      string WKhQqSYqPi;
      string OzBDrOTZFL;
      string zjdBAnrOmV;
      string MLHmWeLeek;
      string tcdnNLJnPL;
      string toLIimgfQD;
      string ZJEsWDrOgN;
      string CotURVFonn;
      string dEybbWzyDi;
      string xfNbKjYkQK;
      string SuHCIEtpqM;
      string hrqbYVLbRA;
      string DtKxPWaSKg;
      string xTXdVhwwSW;
      string bJGqAFnlCn;
      string YwTQGYjJmk;
      if(IPwJeTdBdK == ZJEsWDrOgN){dbfKPNTMGp = true;}
      else if(ZJEsWDrOgN == IPwJeTdBdK){FLYWwtYDFt = true;}
      if(zjWNjbcbUt == CotURVFonn){YOJtXtmTwJ = true;}
      else if(CotURVFonn == zjWNjbcbUt){fIEEBlzezL = true;}
      if(ptuWDSUtXb == dEybbWzyDi){inPVHAAGWw = true;}
      else if(dEybbWzyDi == ptuWDSUtXb){MXwuhxwfjx = true;}
      if(KLqIZNPRUh == xfNbKjYkQK){xmJhsAcwal = true;}
      else if(xfNbKjYkQK == KLqIZNPRUh){WmibqBCqNP = true;}
      if(WKhQqSYqPi == SuHCIEtpqM){lafMPKmYsM = true;}
      else if(SuHCIEtpqM == WKhQqSYqPi){IWakYeOoJm = true;}
      if(OzBDrOTZFL == hrqbYVLbRA){kQMcCoLKCO = true;}
      else if(hrqbYVLbRA == OzBDrOTZFL){ZFVIRgOcny = true;}
      if(zjdBAnrOmV == DtKxPWaSKg){NMpJrlEbAW = true;}
      else if(DtKxPWaSKg == zjdBAnrOmV){yrSHWrZbMA = true;}
      if(MLHmWeLeek == xTXdVhwwSW){QqrJWIIDFx = true;}
      if(tcdnNLJnPL == bJGqAFnlCn){NaNKKgZfeE = true;}
      if(toLIimgfQD == YwTQGYjJmk){nStLYZkVTd = true;}
      while(xTXdVhwwSW == MLHmWeLeek){jHRiDoxKWC = true;}
      while(bJGqAFnlCn == bJGqAFnlCn){iGWxXRQaKK = true;}
      while(YwTQGYjJmk == YwTQGYjJmk){lYCORQDSOf = true;}
      if(dbfKPNTMGp == true){dbfKPNTMGp = false;}
      if(YOJtXtmTwJ == true){YOJtXtmTwJ = false;}
      if(inPVHAAGWw == true){inPVHAAGWw = false;}
      if(xmJhsAcwal == true){xmJhsAcwal = false;}
      if(lafMPKmYsM == true){lafMPKmYsM = false;}
      if(kQMcCoLKCO == true){kQMcCoLKCO = false;}
      if(NMpJrlEbAW == true){NMpJrlEbAW = false;}
      if(QqrJWIIDFx == true){QqrJWIIDFx = false;}
      if(NaNKKgZfeE == true){NaNKKgZfeE = false;}
      if(nStLYZkVTd == true){nStLYZkVTd = false;}
      if(FLYWwtYDFt == true){FLYWwtYDFt = false;}
      if(fIEEBlzezL == true){fIEEBlzezL = false;}
      if(MXwuhxwfjx == true){MXwuhxwfjx = false;}
      if(WmibqBCqNP == true){WmibqBCqNP = false;}
      if(IWakYeOoJm == true){IWakYeOoJm = false;}
      if(ZFVIRgOcny == true){ZFVIRgOcny = false;}
      if(yrSHWrZbMA == true){yrSHWrZbMA = false;}
      if(jHRiDoxKWC == true){jHRiDoxKWC = false;}
      if(iGWxXRQaKK == true){iGWxXRQaKK = false;}
      if(lYCORQDSOf == true){lYCORQDSOf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PUADQAJIWD
{ 
  void yqhUwimWJt()
  { 
      bool YzpDWKcbyd = false;
      bool jDVVPSxpHe = false;
      bool SscLiyqEll = false;
      bool FFMAYWNlUY = false;
      bool IABJzRPbyg = false;
      bool SuNmHeVeTX = false;
      bool SXpLXeqVwr = false;
      bool FLUiWSqTMQ = false;
      bool hPGFTKqYst = false;
      bool AhRxFjJpkT = false;
      bool asfFaGZdQn = false;
      bool mCSCoDRkrN = false;
      bool mRcCrXsXdm = false;
      bool JBhrooiAdM = false;
      bool jNHEGyPOHB = false;
      bool RYxXgJQdND = false;
      bool NCzdekTZNA = false;
      bool UQGfdZKYus = false;
      bool HePcUjEKLf = false;
      bool XEmZzgNcZU = false;
      string wViNydTQRk;
      string RnVXtZllBH;
      string FpPZZpfLYU;
      string nIJaQRyRYZ;
      string PHWFndpBLz;
      string iyIUuGFJmI;
      string yHrwwJdtHb;
      string aUNarxSKku;
      string zdAYloAofK;
      string MndQbHPZId;
      string AwtiYNkgbx;
      string ntXqIUHTKH;
      string JnNxPlpxzj;
      string grBHuDiQAX;
      string ESNiVRPlHH;
      string AwPBTLhxSl;
      string WmhqPusQuE;
      string kpSmDpaeax;
      string VEoqikbzmj;
      string VlyNAQkVSa;
      if(wViNydTQRk == AwtiYNkgbx){YzpDWKcbyd = true;}
      else if(AwtiYNkgbx == wViNydTQRk){asfFaGZdQn = true;}
      if(RnVXtZllBH == ntXqIUHTKH){jDVVPSxpHe = true;}
      else if(ntXqIUHTKH == RnVXtZllBH){mCSCoDRkrN = true;}
      if(FpPZZpfLYU == JnNxPlpxzj){SscLiyqEll = true;}
      else if(JnNxPlpxzj == FpPZZpfLYU){mRcCrXsXdm = true;}
      if(nIJaQRyRYZ == grBHuDiQAX){FFMAYWNlUY = true;}
      else if(grBHuDiQAX == nIJaQRyRYZ){JBhrooiAdM = true;}
      if(PHWFndpBLz == ESNiVRPlHH){IABJzRPbyg = true;}
      else if(ESNiVRPlHH == PHWFndpBLz){jNHEGyPOHB = true;}
      if(iyIUuGFJmI == AwPBTLhxSl){SuNmHeVeTX = true;}
      else if(AwPBTLhxSl == iyIUuGFJmI){RYxXgJQdND = true;}
      if(yHrwwJdtHb == WmhqPusQuE){SXpLXeqVwr = true;}
      else if(WmhqPusQuE == yHrwwJdtHb){NCzdekTZNA = true;}
      if(aUNarxSKku == kpSmDpaeax){FLUiWSqTMQ = true;}
      if(zdAYloAofK == VEoqikbzmj){hPGFTKqYst = true;}
      if(MndQbHPZId == VlyNAQkVSa){AhRxFjJpkT = true;}
      while(kpSmDpaeax == aUNarxSKku){UQGfdZKYus = true;}
      while(VEoqikbzmj == VEoqikbzmj){HePcUjEKLf = true;}
      while(VlyNAQkVSa == VlyNAQkVSa){XEmZzgNcZU = true;}
      if(YzpDWKcbyd == true){YzpDWKcbyd = false;}
      if(jDVVPSxpHe == true){jDVVPSxpHe = false;}
      if(SscLiyqEll == true){SscLiyqEll = false;}
      if(FFMAYWNlUY == true){FFMAYWNlUY = false;}
      if(IABJzRPbyg == true){IABJzRPbyg = false;}
      if(SuNmHeVeTX == true){SuNmHeVeTX = false;}
      if(SXpLXeqVwr == true){SXpLXeqVwr = false;}
      if(FLUiWSqTMQ == true){FLUiWSqTMQ = false;}
      if(hPGFTKqYst == true){hPGFTKqYst = false;}
      if(AhRxFjJpkT == true){AhRxFjJpkT = false;}
      if(asfFaGZdQn == true){asfFaGZdQn = false;}
      if(mCSCoDRkrN == true){mCSCoDRkrN = false;}
      if(mRcCrXsXdm == true){mRcCrXsXdm = false;}
      if(JBhrooiAdM == true){JBhrooiAdM = false;}
      if(jNHEGyPOHB == true){jNHEGyPOHB = false;}
      if(RYxXgJQdND == true){RYxXgJQdND = false;}
      if(NCzdekTZNA == true){NCzdekTZNA = false;}
      if(UQGfdZKYus == true){UQGfdZKYus = false;}
      if(HePcUjEKLf == true){HePcUjEKLf = false;}
      if(XEmZzgNcZU == true){XEmZzgNcZU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TONVSVPIOF
{ 
  void KhXzMThPaq()
  { 
      bool AGEUbteokk = false;
      bool hWNCEzVqzf = false;
      bool mRCpNFIyoc = false;
      bool dpAiwozWcm = false;
      bool RRpBYWEGkC = false;
      bool iafbOhDNHV = false;
      bool kfAIGqWdGO = false;
      bool AyOMOUbBRp = false;
      bool BBNmtCKXUN = false;
      bool lkPGBlRhth = false;
      bool zZAWBkMSNs = false;
      bool GCwQUiSMNE = false;
      bool gzJrcOhHKc = false;
      bool DsGjqaBqlJ = false;
      bool pqJaHiozkR = false;
      bool SFUpAAQHsl = false;
      bool CEIkoMwMYs = false;
      bool hbZDNooijt = false;
      bool ZiVrJyYQip = false;
      bool KsxzGkhYku = false;
      string OomMlXjmDJ;
      string cKPuRQgUQh;
      string cLiVGDnNXp;
      string KFonhpUQqX;
      string FNrTMICrQn;
      string aKrCIDFQFh;
      string jVOMzWVaMa;
      string uQcrbOTPIx;
      string BuxiPzNlfe;
      string jDKInjyeTp;
      string maeosJgAZs;
      string ipHIgnYexA;
      string JiugqrGTEr;
      string QouSKZQHpF;
      string RNMlwtuCbz;
      string KTgTgDfyyA;
      string DNugcttoxH;
      string XQnqhuVIkw;
      string wDrEgwHblG;
      string sRIoBERfIB;
      if(OomMlXjmDJ == maeosJgAZs){AGEUbteokk = true;}
      else if(maeosJgAZs == OomMlXjmDJ){zZAWBkMSNs = true;}
      if(cKPuRQgUQh == ipHIgnYexA){hWNCEzVqzf = true;}
      else if(ipHIgnYexA == cKPuRQgUQh){GCwQUiSMNE = true;}
      if(cLiVGDnNXp == JiugqrGTEr){mRCpNFIyoc = true;}
      else if(JiugqrGTEr == cLiVGDnNXp){gzJrcOhHKc = true;}
      if(KFonhpUQqX == QouSKZQHpF){dpAiwozWcm = true;}
      else if(QouSKZQHpF == KFonhpUQqX){DsGjqaBqlJ = true;}
      if(FNrTMICrQn == RNMlwtuCbz){RRpBYWEGkC = true;}
      else if(RNMlwtuCbz == FNrTMICrQn){pqJaHiozkR = true;}
      if(aKrCIDFQFh == KTgTgDfyyA){iafbOhDNHV = true;}
      else if(KTgTgDfyyA == aKrCIDFQFh){SFUpAAQHsl = true;}
      if(jVOMzWVaMa == DNugcttoxH){kfAIGqWdGO = true;}
      else if(DNugcttoxH == jVOMzWVaMa){CEIkoMwMYs = true;}
      if(uQcrbOTPIx == XQnqhuVIkw){AyOMOUbBRp = true;}
      if(BuxiPzNlfe == wDrEgwHblG){BBNmtCKXUN = true;}
      if(jDKInjyeTp == sRIoBERfIB){lkPGBlRhth = true;}
      while(XQnqhuVIkw == uQcrbOTPIx){hbZDNooijt = true;}
      while(wDrEgwHblG == wDrEgwHblG){ZiVrJyYQip = true;}
      while(sRIoBERfIB == sRIoBERfIB){KsxzGkhYku = true;}
      if(AGEUbteokk == true){AGEUbteokk = false;}
      if(hWNCEzVqzf == true){hWNCEzVqzf = false;}
      if(mRCpNFIyoc == true){mRCpNFIyoc = false;}
      if(dpAiwozWcm == true){dpAiwozWcm = false;}
      if(RRpBYWEGkC == true){RRpBYWEGkC = false;}
      if(iafbOhDNHV == true){iafbOhDNHV = false;}
      if(kfAIGqWdGO == true){kfAIGqWdGO = false;}
      if(AyOMOUbBRp == true){AyOMOUbBRp = false;}
      if(BBNmtCKXUN == true){BBNmtCKXUN = false;}
      if(lkPGBlRhth == true){lkPGBlRhth = false;}
      if(zZAWBkMSNs == true){zZAWBkMSNs = false;}
      if(GCwQUiSMNE == true){GCwQUiSMNE = false;}
      if(gzJrcOhHKc == true){gzJrcOhHKc = false;}
      if(DsGjqaBqlJ == true){DsGjqaBqlJ = false;}
      if(pqJaHiozkR == true){pqJaHiozkR = false;}
      if(SFUpAAQHsl == true){SFUpAAQHsl = false;}
      if(CEIkoMwMYs == true){CEIkoMwMYs = false;}
      if(hbZDNooijt == true){hbZDNooijt = false;}
      if(ZiVrJyYQip == true){ZiVrJyYQip = false;}
      if(KsxzGkhYku == true){KsxzGkhYku = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DXEQHEIRLB
{ 
  void NdVrtYFUgo()
  { 
      bool LkOZkhfMiU = false;
      bool TNZMMDoqXx = false;
      bool SJMjLNhaSZ = false;
      bool AhCImPdIjJ = false;
      bool dRBXIZwetY = false;
      bool LzcnYCYeOX = false;
      bool zEtJTkKQYx = false;
      bool YfHNSAInak = false;
      bool QDfsNAFNjk = false;
      bool qztLKYXqDX = false;
      bool PfFxzerOVX = false;
      bool sjDcHwYAuT = false;
      bool fxgnGZluDt = false;
      bool cQkDVjxhth = false;
      bool HprLqGuQEN = false;
      bool zWwjrSzRqY = false;
      bool swKauczAHW = false;
      bool yqGMLoEUwz = false;
      bool eUqptFUBLD = false;
      bool kepUnKeQPO = false;
      string jJCQdDtABL;
      string QctnpSxDxd;
      string hoQdgNErXw;
      string HJppVnZFfC;
      string psdMPsmmUy;
      string IDzGStsYiP;
      string zCcFDGlESB;
      string sqWtnnKDNn;
      string ZRXZnEJjWa;
      string uBWPDmQYJI;
      string GiTSEQfERd;
      string joKtpheCRz;
      string wCgrGqUHqB;
      string XltEgpxEUX;
      string YFRrpGqbYV;
      string INGJMECaMN;
      string uXNQGytFNz;
      string jZhtaqjnBz;
      string ArhVrJejrc;
      string nWrHbAqBlr;
      if(jJCQdDtABL == GiTSEQfERd){LkOZkhfMiU = true;}
      else if(GiTSEQfERd == jJCQdDtABL){PfFxzerOVX = true;}
      if(QctnpSxDxd == joKtpheCRz){TNZMMDoqXx = true;}
      else if(joKtpheCRz == QctnpSxDxd){sjDcHwYAuT = true;}
      if(hoQdgNErXw == wCgrGqUHqB){SJMjLNhaSZ = true;}
      else if(wCgrGqUHqB == hoQdgNErXw){fxgnGZluDt = true;}
      if(HJppVnZFfC == XltEgpxEUX){AhCImPdIjJ = true;}
      else if(XltEgpxEUX == HJppVnZFfC){cQkDVjxhth = true;}
      if(psdMPsmmUy == YFRrpGqbYV){dRBXIZwetY = true;}
      else if(YFRrpGqbYV == psdMPsmmUy){HprLqGuQEN = true;}
      if(IDzGStsYiP == INGJMECaMN){LzcnYCYeOX = true;}
      else if(INGJMECaMN == IDzGStsYiP){zWwjrSzRqY = true;}
      if(zCcFDGlESB == uXNQGytFNz){zEtJTkKQYx = true;}
      else if(uXNQGytFNz == zCcFDGlESB){swKauczAHW = true;}
      if(sqWtnnKDNn == jZhtaqjnBz){YfHNSAInak = true;}
      if(ZRXZnEJjWa == ArhVrJejrc){QDfsNAFNjk = true;}
      if(uBWPDmQYJI == nWrHbAqBlr){qztLKYXqDX = true;}
      while(jZhtaqjnBz == sqWtnnKDNn){yqGMLoEUwz = true;}
      while(ArhVrJejrc == ArhVrJejrc){eUqptFUBLD = true;}
      while(nWrHbAqBlr == nWrHbAqBlr){kepUnKeQPO = true;}
      if(LkOZkhfMiU == true){LkOZkhfMiU = false;}
      if(TNZMMDoqXx == true){TNZMMDoqXx = false;}
      if(SJMjLNhaSZ == true){SJMjLNhaSZ = false;}
      if(AhCImPdIjJ == true){AhCImPdIjJ = false;}
      if(dRBXIZwetY == true){dRBXIZwetY = false;}
      if(LzcnYCYeOX == true){LzcnYCYeOX = false;}
      if(zEtJTkKQYx == true){zEtJTkKQYx = false;}
      if(YfHNSAInak == true){YfHNSAInak = false;}
      if(QDfsNAFNjk == true){QDfsNAFNjk = false;}
      if(qztLKYXqDX == true){qztLKYXqDX = false;}
      if(PfFxzerOVX == true){PfFxzerOVX = false;}
      if(sjDcHwYAuT == true){sjDcHwYAuT = false;}
      if(fxgnGZluDt == true){fxgnGZluDt = false;}
      if(cQkDVjxhth == true){cQkDVjxhth = false;}
      if(HprLqGuQEN == true){HprLqGuQEN = false;}
      if(zWwjrSzRqY == true){zWwjrSzRqY = false;}
      if(swKauczAHW == true){swKauczAHW = false;}
      if(yqGMLoEUwz == true){yqGMLoEUwz = false;}
      if(eUqptFUBLD == true){eUqptFUBLD = false;}
      if(kepUnKeQPO == true){kepUnKeQPO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EONAHKAQXS
{ 
  void rnfGqfANyS()
  { 
      bool muqlSiyMlS = false;
      bool lIcsomdtOf = false;
      bool PAfeaCVDbp = false;
      bool ifgKGgghZh = false;
      bool kKVOdgZuZJ = false;
      bool SWlZdmPMLP = false;
      bool MtkujGaSmH = false;
      bool FuUgtFeRBt = false;
      bool badRXMsHfT = false;
      bool RUWJUqYZeW = false;
      bool FHHSDWBFeY = false;
      bool HyKRnlQSWX = false;
      bool MTmTokXLMD = false;
      bool fEldnUSKOA = false;
      bool KnbGLTJEUh = false;
      bool ZFDHJkUncR = false;
      bool zprbsDLfcT = false;
      bool TFEVNYrfHV = false;
      bool aSpdcZBeTD = false;
      bool zdhwBTuAMI = false;
      string XYMrkgysuR;
      string LjRMqjCZrH;
      string TCuSpskIHj;
      string RwyUxPUVxK;
      string TCcGpVBgEU;
      string EzlbhUdsBr;
      string uolLzPlwOb;
      string OfcgmQZncU;
      string qEElfRJVmc;
      string lbTEPdQQGZ;
      string jFScFXWEoQ;
      string uoQgBqkzfh;
      string FPJkomLXRJ;
      string AIgCkkkagH;
      string uFgVgwKmCY;
      string rQkYTUwgmR;
      string LymfPmIOuP;
      string FJSXmAhmEs;
      string cYUrQjXHhQ;
      string oDnOwwRBGt;
      if(XYMrkgysuR == jFScFXWEoQ){muqlSiyMlS = true;}
      else if(jFScFXWEoQ == XYMrkgysuR){FHHSDWBFeY = true;}
      if(LjRMqjCZrH == uoQgBqkzfh){lIcsomdtOf = true;}
      else if(uoQgBqkzfh == LjRMqjCZrH){HyKRnlQSWX = true;}
      if(TCuSpskIHj == FPJkomLXRJ){PAfeaCVDbp = true;}
      else if(FPJkomLXRJ == TCuSpskIHj){MTmTokXLMD = true;}
      if(RwyUxPUVxK == AIgCkkkagH){ifgKGgghZh = true;}
      else if(AIgCkkkagH == RwyUxPUVxK){fEldnUSKOA = true;}
      if(TCcGpVBgEU == uFgVgwKmCY){kKVOdgZuZJ = true;}
      else if(uFgVgwKmCY == TCcGpVBgEU){KnbGLTJEUh = true;}
      if(EzlbhUdsBr == rQkYTUwgmR){SWlZdmPMLP = true;}
      else if(rQkYTUwgmR == EzlbhUdsBr){ZFDHJkUncR = true;}
      if(uolLzPlwOb == LymfPmIOuP){MtkujGaSmH = true;}
      else if(LymfPmIOuP == uolLzPlwOb){zprbsDLfcT = true;}
      if(OfcgmQZncU == FJSXmAhmEs){FuUgtFeRBt = true;}
      if(qEElfRJVmc == cYUrQjXHhQ){badRXMsHfT = true;}
      if(lbTEPdQQGZ == oDnOwwRBGt){RUWJUqYZeW = true;}
      while(FJSXmAhmEs == OfcgmQZncU){TFEVNYrfHV = true;}
      while(cYUrQjXHhQ == cYUrQjXHhQ){aSpdcZBeTD = true;}
      while(oDnOwwRBGt == oDnOwwRBGt){zdhwBTuAMI = true;}
      if(muqlSiyMlS == true){muqlSiyMlS = false;}
      if(lIcsomdtOf == true){lIcsomdtOf = false;}
      if(PAfeaCVDbp == true){PAfeaCVDbp = false;}
      if(ifgKGgghZh == true){ifgKGgghZh = false;}
      if(kKVOdgZuZJ == true){kKVOdgZuZJ = false;}
      if(SWlZdmPMLP == true){SWlZdmPMLP = false;}
      if(MtkujGaSmH == true){MtkujGaSmH = false;}
      if(FuUgtFeRBt == true){FuUgtFeRBt = false;}
      if(badRXMsHfT == true){badRXMsHfT = false;}
      if(RUWJUqYZeW == true){RUWJUqYZeW = false;}
      if(FHHSDWBFeY == true){FHHSDWBFeY = false;}
      if(HyKRnlQSWX == true){HyKRnlQSWX = false;}
      if(MTmTokXLMD == true){MTmTokXLMD = false;}
      if(fEldnUSKOA == true){fEldnUSKOA = false;}
      if(KnbGLTJEUh == true){KnbGLTJEUh = false;}
      if(ZFDHJkUncR == true){ZFDHJkUncR = false;}
      if(zprbsDLfcT == true){zprbsDLfcT = false;}
      if(TFEVNYrfHV == true){TFEVNYrfHV = false;}
      if(aSpdcZBeTD == true){aSpdcZBeTD = false;}
      if(zdhwBTuAMI == true){zdhwBTuAMI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HRLRZMWSDQ
{ 
  void rtGywwdSXu()
  { 
      bool bdTbXjfOaE = false;
      bool GYuLHJjGhJ = false;
      bool TRVLUELJdo = false;
      bool DDQRYFFOpr = false;
      bool wxgUJyYzWW = false;
      bool TwrXEKIIGS = false;
      bool XWklACIdlC = false;
      bool EUQpNWkBCW = false;
      bool fMmHVGLsNO = false;
      bool xxHWTZMtTG = false;
      bool otMTSyfBJg = false;
      bool YHFilLjcQs = false;
      bool qPPXFHMsVn = false;
      bool KpgwhkASnW = false;
      bool aJifooqXjI = false;
      bool pidZOZenOL = false;
      bool kmfVWhZIBB = false;
      bool KQosShgjhP = false;
      bool PnIMyaMGhI = false;
      bool GLEclndMIH = false;
      string CXJffFwPXN;
      string AHtChcCDhV;
      string nrBAAFmNiY;
      string XTLUiZOFjt;
      string kKChXxRAYN;
      string CGReOJVJfa;
      string RifzogwZTH;
      string NwTmkcpTcC;
      string mmnVWRCfGY;
      string EFZIbBeDrq;
      string BqfQzFldtk;
      string TBfcnetKbX;
      string ePTtDIVLKi;
      string ymbkBuGXVQ;
      string eXlUECYwUx;
      string GUaTLkXlMq;
      string iaTKmfZubr;
      string YWnLsHdypB;
      string iZqNbcMHYP;
      string WUKdgDDahX;
      if(CXJffFwPXN == BqfQzFldtk){bdTbXjfOaE = true;}
      else if(BqfQzFldtk == CXJffFwPXN){otMTSyfBJg = true;}
      if(AHtChcCDhV == TBfcnetKbX){GYuLHJjGhJ = true;}
      else if(TBfcnetKbX == AHtChcCDhV){YHFilLjcQs = true;}
      if(nrBAAFmNiY == ePTtDIVLKi){TRVLUELJdo = true;}
      else if(ePTtDIVLKi == nrBAAFmNiY){qPPXFHMsVn = true;}
      if(XTLUiZOFjt == ymbkBuGXVQ){DDQRYFFOpr = true;}
      else if(ymbkBuGXVQ == XTLUiZOFjt){KpgwhkASnW = true;}
      if(kKChXxRAYN == eXlUECYwUx){wxgUJyYzWW = true;}
      else if(eXlUECYwUx == kKChXxRAYN){aJifooqXjI = true;}
      if(CGReOJVJfa == GUaTLkXlMq){TwrXEKIIGS = true;}
      else if(GUaTLkXlMq == CGReOJVJfa){pidZOZenOL = true;}
      if(RifzogwZTH == iaTKmfZubr){XWklACIdlC = true;}
      else if(iaTKmfZubr == RifzogwZTH){kmfVWhZIBB = true;}
      if(NwTmkcpTcC == YWnLsHdypB){EUQpNWkBCW = true;}
      if(mmnVWRCfGY == iZqNbcMHYP){fMmHVGLsNO = true;}
      if(EFZIbBeDrq == WUKdgDDahX){xxHWTZMtTG = true;}
      while(YWnLsHdypB == NwTmkcpTcC){KQosShgjhP = true;}
      while(iZqNbcMHYP == iZqNbcMHYP){PnIMyaMGhI = true;}
      while(WUKdgDDahX == WUKdgDDahX){GLEclndMIH = true;}
      if(bdTbXjfOaE == true){bdTbXjfOaE = false;}
      if(GYuLHJjGhJ == true){GYuLHJjGhJ = false;}
      if(TRVLUELJdo == true){TRVLUELJdo = false;}
      if(DDQRYFFOpr == true){DDQRYFFOpr = false;}
      if(wxgUJyYzWW == true){wxgUJyYzWW = false;}
      if(TwrXEKIIGS == true){TwrXEKIIGS = false;}
      if(XWklACIdlC == true){XWklACIdlC = false;}
      if(EUQpNWkBCW == true){EUQpNWkBCW = false;}
      if(fMmHVGLsNO == true){fMmHVGLsNO = false;}
      if(xxHWTZMtTG == true){xxHWTZMtTG = false;}
      if(otMTSyfBJg == true){otMTSyfBJg = false;}
      if(YHFilLjcQs == true){YHFilLjcQs = false;}
      if(qPPXFHMsVn == true){qPPXFHMsVn = false;}
      if(KpgwhkASnW == true){KpgwhkASnW = false;}
      if(aJifooqXjI == true){aJifooqXjI = false;}
      if(pidZOZenOL == true){pidZOZenOL = false;}
      if(kmfVWhZIBB == true){kmfVWhZIBB = false;}
      if(KQosShgjhP == true){KQosShgjhP = false;}
      if(PnIMyaMGhI == true){PnIMyaMGhI = false;}
      if(GLEclndMIH == true){GLEclndMIH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELBJZBDKAK
{ 
  void qJAoPNAzCm()
  { 
      bool HxIuELDbkm = false;
      bool lNPZwQjssY = false;
      bool GfOsUTwwpk = false;
      bool bIGkLEhFzG = false;
      bool qNxLfkbdmN = false;
      bool DnjsubiPak = false;
      bool PHkzKcHdNr = false;
      bool hdtlhshCMj = false;
      bool qSJcgmYMpj = false;
      bool USeNqjbyBC = false;
      bool dxPteYtxLC = false;
      bool sgCqtxxIRW = false;
      bool EtncWPzfux = false;
      bool QjBJFsCOxH = false;
      bool sbBnqnPnTs = false;
      bool lSfdyjJlXP = false;
      bool ZNBNkIfrkA = false;
      bool uiLJccrzli = false;
      bool ALMCKyEWLV = false;
      bool jPphhfZnDi = false;
      string cpHDVYUFXo;
      string xXHQIAHzFe;
      string lGhMFeiotK;
      string QINKBmQWMM;
      string pJQgbLtBGx;
      string EoKfZWIuyp;
      string ofLMYnJwOV;
      string jjmrnboAjt;
      string jhhwGaxgke;
      string eVYVXJyDHn;
      string BymkNTCRqy;
      string gHKDFHxOGx;
      string pcLjqNLQUe;
      string dlrwrluxil;
      string YeplxWLUPQ;
      string LiwJxYmCtz;
      string HkxMTuONLT;
      string LAfUYKlYmT;
      string CqBDStoizS;
      string zrDjdmhcSB;
      if(cpHDVYUFXo == BymkNTCRqy){HxIuELDbkm = true;}
      else if(BymkNTCRqy == cpHDVYUFXo){dxPteYtxLC = true;}
      if(xXHQIAHzFe == gHKDFHxOGx){lNPZwQjssY = true;}
      else if(gHKDFHxOGx == xXHQIAHzFe){sgCqtxxIRW = true;}
      if(lGhMFeiotK == pcLjqNLQUe){GfOsUTwwpk = true;}
      else if(pcLjqNLQUe == lGhMFeiotK){EtncWPzfux = true;}
      if(QINKBmQWMM == dlrwrluxil){bIGkLEhFzG = true;}
      else if(dlrwrluxil == QINKBmQWMM){QjBJFsCOxH = true;}
      if(pJQgbLtBGx == YeplxWLUPQ){qNxLfkbdmN = true;}
      else if(YeplxWLUPQ == pJQgbLtBGx){sbBnqnPnTs = true;}
      if(EoKfZWIuyp == LiwJxYmCtz){DnjsubiPak = true;}
      else if(LiwJxYmCtz == EoKfZWIuyp){lSfdyjJlXP = true;}
      if(ofLMYnJwOV == HkxMTuONLT){PHkzKcHdNr = true;}
      else if(HkxMTuONLT == ofLMYnJwOV){ZNBNkIfrkA = true;}
      if(jjmrnboAjt == LAfUYKlYmT){hdtlhshCMj = true;}
      if(jhhwGaxgke == CqBDStoizS){qSJcgmYMpj = true;}
      if(eVYVXJyDHn == zrDjdmhcSB){USeNqjbyBC = true;}
      while(LAfUYKlYmT == jjmrnboAjt){uiLJccrzli = true;}
      while(CqBDStoizS == CqBDStoizS){ALMCKyEWLV = true;}
      while(zrDjdmhcSB == zrDjdmhcSB){jPphhfZnDi = true;}
      if(HxIuELDbkm == true){HxIuELDbkm = false;}
      if(lNPZwQjssY == true){lNPZwQjssY = false;}
      if(GfOsUTwwpk == true){GfOsUTwwpk = false;}
      if(bIGkLEhFzG == true){bIGkLEhFzG = false;}
      if(qNxLfkbdmN == true){qNxLfkbdmN = false;}
      if(DnjsubiPak == true){DnjsubiPak = false;}
      if(PHkzKcHdNr == true){PHkzKcHdNr = false;}
      if(hdtlhshCMj == true){hdtlhshCMj = false;}
      if(qSJcgmYMpj == true){qSJcgmYMpj = false;}
      if(USeNqjbyBC == true){USeNqjbyBC = false;}
      if(dxPteYtxLC == true){dxPteYtxLC = false;}
      if(sgCqtxxIRW == true){sgCqtxxIRW = false;}
      if(EtncWPzfux == true){EtncWPzfux = false;}
      if(QjBJFsCOxH == true){QjBJFsCOxH = false;}
      if(sbBnqnPnTs == true){sbBnqnPnTs = false;}
      if(lSfdyjJlXP == true){lSfdyjJlXP = false;}
      if(ZNBNkIfrkA == true){ZNBNkIfrkA = false;}
      if(uiLJccrzli == true){uiLJccrzli = false;}
      if(ALMCKyEWLV == true){ALMCKyEWLV = false;}
      if(jPphhfZnDi == true){jPphhfZnDi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GBZPLFUZHW
{ 
  void ODuYCopptj()
  { 
      bool sQkLCrlNNw = false;
      bool uGyyDHolRz = false;
      bool nHbVJJjAtf = false;
      bool diGKYbtKnK = false;
      bool zSnyfIlXCd = false;
      bool EQCpEloPBr = false;
      bool IkTgSMAnYa = false;
      bool NexHzVSdpB = false;
      bool WMyPbMfQFm = false;
      bool mdIuBNyHeT = false;
      bool IyyaQZSupi = false;
      bool SLYAUwmEFF = false;
      bool fihlniVBFk = false;
      bool WLyWrYNWzB = false;
      bool tkZWTaFHaF = false;
      bool atCZmYPMlg = false;
      bool DRoEMHNCHw = false;
      bool hPEDLuJLRN = false;
      bool dOazKbIYiT = false;
      bool JAjRxcuUJM = false;
      string agQNPiKTgV;
      string qkzAhEWxoJ;
      string dGZJUeunbz;
      string VidmcJoANT;
      string OugSxAlpMt;
      string XAlRxUGHsk;
      string nVrgAIGMXY;
      string PViUuhZHMU;
      string rFbhbVwMoH;
      string ChHcfsDzRo;
      string sZRndCQRWP;
      string tztYrhtKFe;
      string LtWPVgOGnB;
      string eZoXaSmnDZ;
      string EepZMDmikx;
      string ystmczDBRx;
      string mKcUkUJWxY;
      string uGGfZfEwDS;
      string seVqCkfBta;
      string PkVGlsCUor;
      if(agQNPiKTgV == sZRndCQRWP){sQkLCrlNNw = true;}
      else if(sZRndCQRWP == agQNPiKTgV){IyyaQZSupi = true;}
      if(qkzAhEWxoJ == tztYrhtKFe){uGyyDHolRz = true;}
      else if(tztYrhtKFe == qkzAhEWxoJ){SLYAUwmEFF = true;}
      if(dGZJUeunbz == LtWPVgOGnB){nHbVJJjAtf = true;}
      else if(LtWPVgOGnB == dGZJUeunbz){fihlniVBFk = true;}
      if(VidmcJoANT == eZoXaSmnDZ){diGKYbtKnK = true;}
      else if(eZoXaSmnDZ == VidmcJoANT){WLyWrYNWzB = true;}
      if(OugSxAlpMt == EepZMDmikx){zSnyfIlXCd = true;}
      else if(EepZMDmikx == OugSxAlpMt){tkZWTaFHaF = true;}
      if(XAlRxUGHsk == ystmczDBRx){EQCpEloPBr = true;}
      else if(ystmczDBRx == XAlRxUGHsk){atCZmYPMlg = true;}
      if(nVrgAIGMXY == mKcUkUJWxY){IkTgSMAnYa = true;}
      else if(mKcUkUJWxY == nVrgAIGMXY){DRoEMHNCHw = true;}
      if(PViUuhZHMU == uGGfZfEwDS){NexHzVSdpB = true;}
      if(rFbhbVwMoH == seVqCkfBta){WMyPbMfQFm = true;}
      if(ChHcfsDzRo == PkVGlsCUor){mdIuBNyHeT = true;}
      while(uGGfZfEwDS == PViUuhZHMU){hPEDLuJLRN = true;}
      while(seVqCkfBta == seVqCkfBta){dOazKbIYiT = true;}
      while(PkVGlsCUor == PkVGlsCUor){JAjRxcuUJM = true;}
      if(sQkLCrlNNw == true){sQkLCrlNNw = false;}
      if(uGyyDHolRz == true){uGyyDHolRz = false;}
      if(nHbVJJjAtf == true){nHbVJJjAtf = false;}
      if(diGKYbtKnK == true){diGKYbtKnK = false;}
      if(zSnyfIlXCd == true){zSnyfIlXCd = false;}
      if(EQCpEloPBr == true){EQCpEloPBr = false;}
      if(IkTgSMAnYa == true){IkTgSMAnYa = false;}
      if(NexHzVSdpB == true){NexHzVSdpB = false;}
      if(WMyPbMfQFm == true){WMyPbMfQFm = false;}
      if(mdIuBNyHeT == true){mdIuBNyHeT = false;}
      if(IyyaQZSupi == true){IyyaQZSupi = false;}
      if(SLYAUwmEFF == true){SLYAUwmEFF = false;}
      if(fihlniVBFk == true){fihlniVBFk = false;}
      if(WLyWrYNWzB == true){WLyWrYNWzB = false;}
      if(tkZWTaFHaF == true){tkZWTaFHaF = false;}
      if(atCZmYPMlg == true){atCZmYPMlg = false;}
      if(DRoEMHNCHw == true){DRoEMHNCHw = false;}
      if(hPEDLuJLRN == true){hPEDLuJLRN = false;}
      if(dOazKbIYiT == true){dOazKbIYiT = false;}
      if(JAjRxcuUJM == true){JAjRxcuUJM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PFOYULDXRK
{ 
  void TFUOZTScfX()
  { 
      bool wSQgFfiwEy = false;
      bool BzIERqodPj = false;
      bool TfJhxFJaZl = false;
      bool iiCmXRmmDZ = false;
      bool PfiOXkkHzw = false;
      bool lPLAFPIhjA = false;
      bool WHWSPRxUfA = false;
      bool DBZpUnxuJL = false;
      bool UCaczSXBhH = false;
      bool JEDDDHIPyF = false;
      bool nQazrkoUfR = false;
      bool SMYYfUfsSw = false;
      bool tumXpzxWmN = false;
      bool egwDWEabjO = false;
      bool dDVPowfdXh = false;
      bool aPxBLscDIs = false;
      bool mRgRmkQUBb = false;
      bool tEIDSqYXht = false;
      bool TSzElPjtrd = false;
      bool aWSqbLVDbE = false;
      string iCpRjreLZO;
      string LGqVDRPKhV;
      string NEMEPFKeCW;
      string kSUEheoUBA;
      string HyKsdHjqjF;
      string REirZdplCd;
      string hAJCdskmmY;
      string ctIgOPtSZI;
      string VTuwFfibeE;
      string nCSXSGoHOk;
      string VwEKcWuBdJ;
      string iXMtHNFMwx;
      string JIIikZbkOH;
      string amEolYOjTi;
      string kgyUVQpXPE;
      string BbKQaMnVYC;
      string uJmWiwTXHh;
      string zUrNMbKnMU;
      string jDUJGybmNZ;
      string ksLRnasbkZ;
      if(iCpRjreLZO == VwEKcWuBdJ){wSQgFfiwEy = true;}
      else if(VwEKcWuBdJ == iCpRjreLZO){nQazrkoUfR = true;}
      if(LGqVDRPKhV == iXMtHNFMwx){BzIERqodPj = true;}
      else if(iXMtHNFMwx == LGqVDRPKhV){SMYYfUfsSw = true;}
      if(NEMEPFKeCW == JIIikZbkOH){TfJhxFJaZl = true;}
      else if(JIIikZbkOH == NEMEPFKeCW){tumXpzxWmN = true;}
      if(kSUEheoUBA == amEolYOjTi){iiCmXRmmDZ = true;}
      else if(amEolYOjTi == kSUEheoUBA){egwDWEabjO = true;}
      if(HyKsdHjqjF == kgyUVQpXPE){PfiOXkkHzw = true;}
      else if(kgyUVQpXPE == HyKsdHjqjF){dDVPowfdXh = true;}
      if(REirZdplCd == BbKQaMnVYC){lPLAFPIhjA = true;}
      else if(BbKQaMnVYC == REirZdplCd){aPxBLscDIs = true;}
      if(hAJCdskmmY == uJmWiwTXHh){WHWSPRxUfA = true;}
      else if(uJmWiwTXHh == hAJCdskmmY){mRgRmkQUBb = true;}
      if(ctIgOPtSZI == zUrNMbKnMU){DBZpUnxuJL = true;}
      if(VTuwFfibeE == jDUJGybmNZ){UCaczSXBhH = true;}
      if(nCSXSGoHOk == ksLRnasbkZ){JEDDDHIPyF = true;}
      while(zUrNMbKnMU == ctIgOPtSZI){tEIDSqYXht = true;}
      while(jDUJGybmNZ == jDUJGybmNZ){TSzElPjtrd = true;}
      while(ksLRnasbkZ == ksLRnasbkZ){aWSqbLVDbE = true;}
      if(wSQgFfiwEy == true){wSQgFfiwEy = false;}
      if(BzIERqodPj == true){BzIERqodPj = false;}
      if(TfJhxFJaZl == true){TfJhxFJaZl = false;}
      if(iiCmXRmmDZ == true){iiCmXRmmDZ = false;}
      if(PfiOXkkHzw == true){PfiOXkkHzw = false;}
      if(lPLAFPIhjA == true){lPLAFPIhjA = false;}
      if(WHWSPRxUfA == true){WHWSPRxUfA = false;}
      if(DBZpUnxuJL == true){DBZpUnxuJL = false;}
      if(UCaczSXBhH == true){UCaczSXBhH = false;}
      if(JEDDDHIPyF == true){JEDDDHIPyF = false;}
      if(nQazrkoUfR == true){nQazrkoUfR = false;}
      if(SMYYfUfsSw == true){SMYYfUfsSw = false;}
      if(tumXpzxWmN == true){tumXpzxWmN = false;}
      if(egwDWEabjO == true){egwDWEabjO = false;}
      if(dDVPowfdXh == true){dDVPowfdXh = false;}
      if(aPxBLscDIs == true){aPxBLscDIs = false;}
      if(mRgRmkQUBb == true){mRgRmkQUBb = false;}
      if(tEIDSqYXht == true){tEIDSqYXht = false;}
      if(TSzElPjtrd == true){TSzElPjtrd = false;}
      if(aWSqbLVDbE == true){aWSqbLVDbE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BOCCYBGITP
{ 
  void pRaxAnGRrY()
  { 
      bool CMKdUyPPsC = false;
      bool XzTbArawPr = false;
      bool KTaKtbxUOM = false;
      bool LBuQLJIUsJ = false;
      bool AuaewmKdqO = false;
      bool booQmikAis = false;
      bool AtBgpWDCPq = false;
      bool iGCFqPswOG = false;
      bool QSdAkWLedc = false;
      bool XIkAIGstoY = false;
      bool iHNzeVmjYX = false;
      bool onkbbhQBwS = false;
      bool KYXmSaUCwk = false;
      bool VzHpXIEdUO = false;
      bool jbFGmjXIXa = false;
      bool oryVNJjafE = false;
      bool AjmnCpguES = false;
      bool dlfgiiTRAi = false;
      bool DMdVucBlbN = false;
      bool YdxQOznRDx = false;
      string IAkCIzyzVr;
      string anGjhfoIUB;
      string JWwRNYGGsq;
      string lgxSTQdJRl;
      string rKCLoCLeNP;
      string CZioAkESoj;
      string sqFdGspmPR;
      string BephJyUjcK;
      string NarcoMyISi;
      string LKUgrAFYEu;
      string MXOwNWiAfB;
      string QTpdWRzbnt;
      string uhUgFqKJoI;
      string suegyoLwOS;
      string cxbQSqUpKa;
      string BckKAdChpW;
      string LZLWIUoIeg;
      string FCNUQyFDOO;
      string VTyOHPKUgT;
      string ldFrGDlEIx;
      if(IAkCIzyzVr == MXOwNWiAfB){CMKdUyPPsC = true;}
      else if(MXOwNWiAfB == IAkCIzyzVr){iHNzeVmjYX = true;}
      if(anGjhfoIUB == QTpdWRzbnt){XzTbArawPr = true;}
      else if(QTpdWRzbnt == anGjhfoIUB){onkbbhQBwS = true;}
      if(JWwRNYGGsq == uhUgFqKJoI){KTaKtbxUOM = true;}
      else if(uhUgFqKJoI == JWwRNYGGsq){KYXmSaUCwk = true;}
      if(lgxSTQdJRl == suegyoLwOS){LBuQLJIUsJ = true;}
      else if(suegyoLwOS == lgxSTQdJRl){VzHpXIEdUO = true;}
      if(rKCLoCLeNP == cxbQSqUpKa){AuaewmKdqO = true;}
      else if(cxbQSqUpKa == rKCLoCLeNP){jbFGmjXIXa = true;}
      if(CZioAkESoj == BckKAdChpW){booQmikAis = true;}
      else if(BckKAdChpW == CZioAkESoj){oryVNJjafE = true;}
      if(sqFdGspmPR == LZLWIUoIeg){AtBgpWDCPq = true;}
      else if(LZLWIUoIeg == sqFdGspmPR){AjmnCpguES = true;}
      if(BephJyUjcK == FCNUQyFDOO){iGCFqPswOG = true;}
      if(NarcoMyISi == VTyOHPKUgT){QSdAkWLedc = true;}
      if(LKUgrAFYEu == ldFrGDlEIx){XIkAIGstoY = true;}
      while(FCNUQyFDOO == BephJyUjcK){dlfgiiTRAi = true;}
      while(VTyOHPKUgT == VTyOHPKUgT){DMdVucBlbN = true;}
      while(ldFrGDlEIx == ldFrGDlEIx){YdxQOznRDx = true;}
      if(CMKdUyPPsC == true){CMKdUyPPsC = false;}
      if(XzTbArawPr == true){XzTbArawPr = false;}
      if(KTaKtbxUOM == true){KTaKtbxUOM = false;}
      if(LBuQLJIUsJ == true){LBuQLJIUsJ = false;}
      if(AuaewmKdqO == true){AuaewmKdqO = false;}
      if(booQmikAis == true){booQmikAis = false;}
      if(AtBgpWDCPq == true){AtBgpWDCPq = false;}
      if(iGCFqPswOG == true){iGCFqPswOG = false;}
      if(QSdAkWLedc == true){QSdAkWLedc = false;}
      if(XIkAIGstoY == true){XIkAIGstoY = false;}
      if(iHNzeVmjYX == true){iHNzeVmjYX = false;}
      if(onkbbhQBwS == true){onkbbhQBwS = false;}
      if(KYXmSaUCwk == true){KYXmSaUCwk = false;}
      if(VzHpXIEdUO == true){VzHpXIEdUO = false;}
      if(jbFGmjXIXa == true){jbFGmjXIXa = false;}
      if(oryVNJjafE == true){oryVNJjafE = false;}
      if(AjmnCpguES == true){AjmnCpguES = false;}
      if(dlfgiiTRAi == true){dlfgiiTRAi = false;}
      if(DMdVucBlbN == true){DMdVucBlbN = false;}
      if(YdxQOznRDx == true){YdxQOznRDx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VKOTDLMKVF
{ 
  void yogtAMBjFI()
  { 
      bool KVEydaCQut = false;
      bool jWErhBswEd = false;
      bool blAKxQzRIf = false;
      bool jsPtbqahRd = false;
      bool bJWmyaMbKP = false;
      bool cmENYXUtAN = false;
      bool ajIOKqHJQq = false;
      bool ZLeZBRPMLW = false;
      bool EWGrCwnBVD = false;
      bool WfgEDrAHcH = false;
      bool SCLTpRHeLG = false;
      bool IHhdIDdPLN = false;
      bool CFnMTsdaWJ = false;
      bool RHjEDBLlCk = false;
      bool oJpOuOxDuz = false;
      bool OkuPENOyzw = false;
      bool mgIBoAXdZH = false;
      bool qqMaYsOZRF = false;
      bool uaeXufLTzp = false;
      bool mNmGxHBoZt = false;
      string ZyRatoxYrk;
      string awXlFQuoud;
      string daNjhKbxTL;
      string mBzNTUPEzY;
      string OVuxgEwOQO;
      string BoXXKykgrj;
      string MAFgyYwKSk;
      string ApoVOIePDd;
      string NNfEJxdbCU;
      string jhMPMOPOzI;
      string HlwfOLzBIC;
      string SUdOVzTBXA;
      string uUHxBRdZJz;
      string sQQuVaQzpy;
      string xbSACOEysM;
      string tNpyMmdzew;
      string gZrJIBEisu;
      string hTLZDSCGul;
      string NffwEeZRhh;
      string xRUsQWiJqA;
      if(ZyRatoxYrk == HlwfOLzBIC){KVEydaCQut = true;}
      else if(HlwfOLzBIC == ZyRatoxYrk){SCLTpRHeLG = true;}
      if(awXlFQuoud == SUdOVzTBXA){jWErhBswEd = true;}
      else if(SUdOVzTBXA == awXlFQuoud){IHhdIDdPLN = true;}
      if(daNjhKbxTL == uUHxBRdZJz){blAKxQzRIf = true;}
      else if(uUHxBRdZJz == daNjhKbxTL){CFnMTsdaWJ = true;}
      if(mBzNTUPEzY == sQQuVaQzpy){jsPtbqahRd = true;}
      else if(sQQuVaQzpy == mBzNTUPEzY){RHjEDBLlCk = true;}
      if(OVuxgEwOQO == xbSACOEysM){bJWmyaMbKP = true;}
      else if(xbSACOEysM == OVuxgEwOQO){oJpOuOxDuz = true;}
      if(BoXXKykgrj == tNpyMmdzew){cmENYXUtAN = true;}
      else if(tNpyMmdzew == BoXXKykgrj){OkuPENOyzw = true;}
      if(MAFgyYwKSk == gZrJIBEisu){ajIOKqHJQq = true;}
      else if(gZrJIBEisu == MAFgyYwKSk){mgIBoAXdZH = true;}
      if(ApoVOIePDd == hTLZDSCGul){ZLeZBRPMLW = true;}
      if(NNfEJxdbCU == NffwEeZRhh){EWGrCwnBVD = true;}
      if(jhMPMOPOzI == xRUsQWiJqA){WfgEDrAHcH = true;}
      while(hTLZDSCGul == ApoVOIePDd){qqMaYsOZRF = true;}
      while(NffwEeZRhh == NffwEeZRhh){uaeXufLTzp = true;}
      while(xRUsQWiJqA == xRUsQWiJqA){mNmGxHBoZt = true;}
      if(KVEydaCQut == true){KVEydaCQut = false;}
      if(jWErhBswEd == true){jWErhBswEd = false;}
      if(blAKxQzRIf == true){blAKxQzRIf = false;}
      if(jsPtbqahRd == true){jsPtbqahRd = false;}
      if(bJWmyaMbKP == true){bJWmyaMbKP = false;}
      if(cmENYXUtAN == true){cmENYXUtAN = false;}
      if(ajIOKqHJQq == true){ajIOKqHJQq = false;}
      if(ZLeZBRPMLW == true){ZLeZBRPMLW = false;}
      if(EWGrCwnBVD == true){EWGrCwnBVD = false;}
      if(WfgEDrAHcH == true){WfgEDrAHcH = false;}
      if(SCLTpRHeLG == true){SCLTpRHeLG = false;}
      if(IHhdIDdPLN == true){IHhdIDdPLN = false;}
      if(CFnMTsdaWJ == true){CFnMTsdaWJ = false;}
      if(RHjEDBLlCk == true){RHjEDBLlCk = false;}
      if(oJpOuOxDuz == true){oJpOuOxDuz = false;}
      if(OkuPENOyzw == true){OkuPENOyzw = false;}
      if(mgIBoAXdZH == true){mgIBoAXdZH = false;}
      if(qqMaYsOZRF == true){qqMaYsOZRF = false;}
      if(uaeXufLTzp == true){uaeXufLTzp = false;}
      if(mNmGxHBoZt == true){mNmGxHBoZt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SVLBUMWRAF
{ 
  void doBKNKfVjP()
  { 
      bool uyBQKYcxiD = false;
      bool DmulTsRcSL = false;
      bool eDYVPMbnnM = false;
      bool CqyOyluCxh = false;
      bool TQGZWdqrtp = false;
      bool OBjRpqYeAy = false;
      bool wnIVBLogng = false;
      bool xPekrNxyyl = false;
      bool UityxAGfXG = false;
      bool MQBzkeIjYL = false;
      bool oKEMrzWzZb = false;
      bool tafOcNtKYA = false;
      bool EIIhUgNfAN = false;
      bool FNZmxKehFx = false;
      bool dHGwMljmVX = false;
      bool kxKXGfBVrK = false;
      bool kpyMWgAsQS = false;
      bool hLEaVwCMUh = false;
      bool xaKcbHCBfQ = false;
      bool IIouMmItYf = false;
      string OxJAzdKZfl;
      string kAaLwfFQnb;
      string GiewgaOSyS;
      string DTmnVPdnlr;
      string pcfXzkPSsq;
      string EhzxPeRMSY;
      string OrbMhRNlof;
      string BRewkdCHww;
      string KwYHNVToXq;
      string yQUMcyAToh;
      string WdcNomCDLl;
      string cKQWOSSUyM;
      string xYOygkwRSl;
      string ciROYgSLRa;
      string SPclOnAyyK;
      string ffUckyOefE;
      string qkkZIsrCxh;
      string zHCXtgubis;
      string jxSIGxOoca;
      string RmeNjgeDdU;
      if(OxJAzdKZfl == WdcNomCDLl){uyBQKYcxiD = true;}
      else if(WdcNomCDLl == OxJAzdKZfl){oKEMrzWzZb = true;}
      if(kAaLwfFQnb == cKQWOSSUyM){DmulTsRcSL = true;}
      else if(cKQWOSSUyM == kAaLwfFQnb){tafOcNtKYA = true;}
      if(GiewgaOSyS == xYOygkwRSl){eDYVPMbnnM = true;}
      else if(xYOygkwRSl == GiewgaOSyS){EIIhUgNfAN = true;}
      if(DTmnVPdnlr == ciROYgSLRa){CqyOyluCxh = true;}
      else if(ciROYgSLRa == DTmnVPdnlr){FNZmxKehFx = true;}
      if(pcfXzkPSsq == SPclOnAyyK){TQGZWdqrtp = true;}
      else if(SPclOnAyyK == pcfXzkPSsq){dHGwMljmVX = true;}
      if(EhzxPeRMSY == ffUckyOefE){OBjRpqYeAy = true;}
      else if(ffUckyOefE == EhzxPeRMSY){kxKXGfBVrK = true;}
      if(OrbMhRNlof == qkkZIsrCxh){wnIVBLogng = true;}
      else if(qkkZIsrCxh == OrbMhRNlof){kpyMWgAsQS = true;}
      if(BRewkdCHww == zHCXtgubis){xPekrNxyyl = true;}
      if(KwYHNVToXq == jxSIGxOoca){UityxAGfXG = true;}
      if(yQUMcyAToh == RmeNjgeDdU){MQBzkeIjYL = true;}
      while(zHCXtgubis == BRewkdCHww){hLEaVwCMUh = true;}
      while(jxSIGxOoca == jxSIGxOoca){xaKcbHCBfQ = true;}
      while(RmeNjgeDdU == RmeNjgeDdU){IIouMmItYf = true;}
      if(uyBQKYcxiD == true){uyBQKYcxiD = false;}
      if(DmulTsRcSL == true){DmulTsRcSL = false;}
      if(eDYVPMbnnM == true){eDYVPMbnnM = false;}
      if(CqyOyluCxh == true){CqyOyluCxh = false;}
      if(TQGZWdqrtp == true){TQGZWdqrtp = false;}
      if(OBjRpqYeAy == true){OBjRpqYeAy = false;}
      if(wnIVBLogng == true){wnIVBLogng = false;}
      if(xPekrNxyyl == true){xPekrNxyyl = false;}
      if(UityxAGfXG == true){UityxAGfXG = false;}
      if(MQBzkeIjYL == true){MQBzkeIjYL = false;}
      if(oKEMrzWzZb == true){oKEMrzWzZb = false;}
      if(tafOcNtKYA == true){tafOcNtKYA = false;}
      if(EIIhUgNfAN == true){EIIhUgNfAN = false;}
      if(FNZmxKehFx == true){FNZmxKehFx = false;}
      if(dHGwMljmVX == true){dHGwMljmVX = false;}
      if(kxKXGfBVrK == true){kxKXGfBVrK = false;}
      if(kpyMWgAsQS == true){kpyMWgAsQS = false;}
      if(hLEaVwCMUh == true){hLEaVwCMUh = false;}
      if(xaKcbHCBfQ == true){xaKcbHCBfQ = false;}
      if(IIouMmItYf == true){IIouMmItYf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CRVHIMLWAR
{ 
  void XKaYWQiVlC()
  { 
      bool fMpiZlgJnQ = false;
      bool OelojlEwCS = false;
      bool iMTFyhNFfD = false;
      bool ncbVdJeHGI = false;
      bool hxICXOHrfK = false;
      bool qfCZNTsjkr = false;
      bool YbdjckCPLa = false;
      bool HwpsjlDRgi = false;
      bool aVZVMHZCIK = false;
      bool QuWNjGTXZm = false;
      bool LqgECtpIoa = false;
      bool PaCBRDBHXU = false;
      bool KAHAKLZbJd = false;
      bool SfrtWinUSR = false;
      bool QQMguorVwg = false;
      bool ELzEbLjftp = false;
      bool UOzLIjiIdh = false;
      bool OfnGEsnZFV = false;
      bool TDfcYGfmSL = false;
      bool zHabwCRAYK = false;
      string jmfFnieVsj;
      string YJVAVgTNZR;
      string AjhpMNyRft;
      string qmuuXnaElO;
      string akUVnuWnhh;
      string bnWSQAFosa;
      string kNpzrkNach;
      string GPbLqOPMCQ;
      string pKixRCPcdW;
      string hkKKcNuUcC;
      string gwKAaMLKaC;
      string jslbkaerho;
      string UjwFzUEQhd;
      string StjziszhVE;
      string pECbmoziZC;
      string iDmmgwzFAG;
      string HubxipJlrq;
      string bwVczQhUSK;
      string VVpfuPHwSm;
      string sshPwubFsw;
      if(jmfFnieVsj == gwKAaMLKaC){fMpiZlgJnQ = true;}
      else if(gwKAaMLKaC == jmfFnieVsj){LqgECtpIoa = true;}
      if(YJVAVgTNZR == jslbkaerho){OelojlEwCS = true;}
      else if(jslbkaerho == YJVAVgTNZR){PaCBRDBHXU = true;}
      if(AjhpMNyRft == UjwFzUEQhd){iMTFyhNFfD = true;}
      else if(UjwFzUEQhd == AjhpMNyRft){KAHAKLZbJd = true;}
      if(qmuuXnaElO == StjziszhVE){ncbVdJeHGI = true;}
      else if(StjziszhVE == qmuuXnaElO){SfrtWinUSR = true;}
      if(akUVnuWnhh == pECbmoziZC){hxICXOHrfK = true;}
      else if(pECbmoziZC == akUVnuWnhh){QQMguorVwg = true;}
      if(bnWSQAFosa == iDmmgwzFAG){qfCZNTsjkr = true;}
      else if(iDmmgwzFAG == bnWSQAFosa){ELzEbLjftp = true;}
      if(kNpzrkNach == HubxipJlrq){YbdjckCPLa = true;}
      else if(HubxipJlrq == kNpzrkNach){UOzLIjiIdh = true;}
      if(GPbLqOPMCQ == bwVczQhUSK){HwpsjlDRgi = true;}
      if(pKixRCPcdW == VVpfuPHwSm){aVZVMHZCIK = true;}
      if(hkKKcNuUcC == sshPwubFsw){QuWNjGTXZm = true;}
      while(bwVczQhUSK == GPbLqOPMCQ){OfnGEsnZFV = true;}
      while(VVpfuPHwSm == VVpfuPHwSm){TDfcYGfmSL = true;}
      while(sshPwubFsw == sshPwubFsw){zHabwCRAYK = true;}
      if(fMpiZlgJnQ == true){fMpiZlgJnQ = false;}
      if(OelojlEwCS == true){OelojlEwCS = false;}
      if(iMTFyhNFfD == true){iMTFyhNFfD = false;}
      if(ncbVdJeHGI == true){ncbVdJeHGI = false;}
      if(hxICXOHrfK == true){hxICXOHrfK = false;}
      if(qfCZNTsjkr == true){qfCZNTsjkr = false;}
      if(YbdjckCPLa == true){YbdjckCPLa = false;}
      if(HwpsjlDRgi == true){HwpsjlDRgi = false;}
      if(aVZVMHZCIK == true){aVZVMHZCIK = false;}
      if(QuWNjGTXZm == true){QuWNjGTXZm = false;}
      if(LqgECtpIoa == true){LqgECtpIoa = false;}
      if(PaCBRDBHXU == true){PaCBRDBHXU = false;}
      if(KAHAKLZbJd == true){KAHAKLZbJd = false;}
      if(SfrtWinUSR == true){SfrtWinUSR = false;}
      if(QQMguorVwg == true){QQMguorVwg = false;}
      if(ELzEbLjftp == true){ELzEbLjftp = false;}
      if(UOzLIjiIdh == true){UOzLIjiIdh = false;}
      if(OfnGEsnZFV == true){OfnGEsnZFV = false;}
      if(TDfcYGfmSL == true){TDfcYGfmSL = false;}
      if(zHabwCRAYK == true){zHabwCRAYK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EVDKJQJPGN
{ 
  void JHIbWDtNiu()
  { 
      bool ilwPbSeMoz = false;
      bool tWorVWJjXI = false;
      bool GnKGROqktV = false;
      bool GtgWaDJhBY = false;
      bool naIweSAdNN = false;
      bool cbjZxtboyN = false;
      bool bsRTrzpRQS = false;
      bool MahzTffNby = false;
      bool NMXgreKGZf = false;
      bool bUjnxuIoDe = false;
      bool biNuABsjFR = false;
      bool ONMzzOVkaN = false;
      bool oirkprqtCY = false;
      bool WqJwWezbgp = false;
      bool kZAIQNHjoh = false;
      bool ZXNoprqbEH = false;
      bool KzhgtXEQcU = false;
      bool OsDjcOiiTc = false;
      bool kGETyycTGd = false;
      bool mWXYflrSNs = false;
      string EoamOiHiNy;
      string VgRDECdNBF;
      string FQPfxlcPcw;
      string actkJZHTky;
      string LVCVFGuhKn;
      string WFbhemZupc;
      string FrFRXslgtd;
      string tKcDsjOsZp;
      string qtEoYVAMFV;
      string AMcIrTQjyL;
      string UNnfsLbYou;
      string XfUAkLmQrB;
      string sYaXdhhUKY;
      string SetOUcGYuN;
      string saXKxTrbWg;
      string gzqxRumPCL;
      string cHOPbskGfH;
      string ENUeHSBPaJ;
      string oGxdqSmxwY;
      string ppWjjlMHiD;
      if(EoamOiHiNy == UNnfsLbYou){ilwPbSeMoz = true;}
      else if(UNnfsLbYou == EoamOiHiNy){biNuABsjFR = true;}
      if(VgRDECdNBF == XfUAkLmQrB){tWorVWJjXI = true;}
      else if(XfUAkLmQrB == VgRDECdNBF){ONMzzOVkaN = true;}
      if(FQPfxlcPcw == sYaXdhhUKY){GnKGROqktV = true;}
      else if(sYaXdhhUKY == FQPfxlcPcw){oirkprqtCY = true;}
      if(actkJZHTky == SetOUcGYuN){GtgWaDJhBY = true;}
      else if(SetOUcGYuN == actkJZHTky){WqJwWezbgp = true;}
      if(LVCVFGuhKn == saXKxTrbWg){naIweSAdNN = true;}
      else if(saXKxTrbWg == LVCVFGuhKn){kZAIQNHjoh = true;}
      if(WFbhemZupc == gzqxRumPCL){cbjZxtboyN = true;}
      else if(gzqxRumPCL == WFbhemZupc){ZXNoprqbEH = true;}
      if(FrFRXslgtd == cHOPbskGfH){bsRTrzpRQS = true;}
      else if(cHOPbskGfH == FrFRXslgtd){KzhgtXEQcU = true;}
      if(tKcDsjOsZp == ENUeHSBPaJ){MahzTffNby = true;}
      if(qtEoYVAMFV == oGxdqSmxwY){NMXgreKGZf = true;}
      if(AMcIrTQjyL == ppWjjlMHiD){bUjnxuIoDe = true;}
      while(ENUeHSBPaJ == tKcDsjOsZp){OsDjcOiiTc = true;}
      while(oGxdqSmxwY == oGxdqSmxwY){kGETyycTGd = true;}
      while(ppWjjlMHiD == ppWjjlMHiD){mWXYflrSNs = true;}
      if(ilwPbSeMoz == true){ilwPbSeMoz = false;}
      if(tWorVWJjXI == true){tWorVWJjXI = false;}
      if(GnKGROqktV == true){GnKGROqktV = false;}
      if(GtgWaDJhBY == true){GtgWaDJhBY = false;}
      if(naIweSAdNN == true){naIweSAdNN = false;}
      if(cbjZxtboyN == true){cbjZxtboyN = false;}
      if(bsRTrzpRQS == true){bsRTrzpRQS = false;}
      if(MahzTffNby == true){MahzTffNby = false;}
      if(NMXgreKGZf == true){NMXgreKGZf = false;}
      if(bUjnxuIoDe == true){bUjnxuIoDe = false;}
      if(biNuABsjFR == true){biNuABsjFR = false;}
      if(ONMzzOVkaN == true){ONMzzOVkaN = false;}
      if(oirkprqtCY == true){oirkprqtCY = false;}
      if(WqJwWezbgp == true){WqJwWezbgp = false;}
      if(kZAIQNHjoh == true){kZAIQNHjoh = false;}
      if(ZXNoprqbEH == true){ZXNoprqbEH = false;}
      if(KzhgtXEQcU == true){KzhgtXEQcU = false;}
      if(OsDjcOiiTc == true){OsDjcOiiTc = false;}
      if(kGETyycTGd == true){kGETyycTGd = false;}
      if(mWXYflrSNs == true){mWXYflrSNs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KEHTVMPPPS
{ 
  void IXBpNmTcrE()
  { 
      bool JTrQljpHKG = false;
      bool gEquRdzNBr = false;
      bool bVtQlgWmNs = false;
      bool BdChpGbQMj = false;
      bool krSAJtCuGr = false;
      bool OcrljmYbdF = false;
      bool MDtQECBIFK = false;
      bool CiAQGiDsGr = false;
      bool dbgUeYlQyC = false;
      bool gzlGXhyBuG = false;
      bool rtouoebbeA = false;
      bool jeUkbjWYkf = false;
      bool QkKDdCwssY = false;
      bool kByzzjmkeA = false;
      bool wKkxRBdBem = false;
      bool KYQPpHjlRm = false;
      bool hhhGPigVlq = false;
      bool xlskjGzMkb = false;
      bool YuOFNLkhJq = false;
      bool zASrRNbehi = false;
      string oMlHMRoLTp;
      string ExcLXaKsGC;
      string VeBXTqLAca;
      string cgHBTNuopZ;
      string lNojTgqLMV;
      string mSEEFKLOnU;
      string GnirNXoaqJ;
      string eUDfQHoQDl;
      string AznGmKbCuJ;
      string CgBVTydxVw;
      string qQTCpROYnx;
      string UtKBUGzbFD;
      string wmehHxThMS;
      string druHujflQU;
      string uDOynIWzBN;
      string yCrSzEkkur;
      string ygMVTbyCGj;
      string aNLjHrXgtz;
      string aTgyTbAcHp;
      string ytpXWOpsdL;
      if(oMlHMRoLTp == qQTCpROYnx){JTrQljpHKG = true;}
      else if(qQTCpROYnx == oMlHMRoLTp){rtouoebbeA = true;}
      if(ExcLXaKsGC == UtKBUGzbFD){gEquRdzNBr = true;}
      else if(UtKBUGzbFD == ExcLXaKsGC){jeUkbjWYkf = true;}
      if(VeBXTqLAca == wmehHxThMS){bVtQlgWmNs = true;}
      else if(wmehHxThMS == VeBXTqLAca){QkKDdCwssY = true;}
      if(cgHBTNuopZ == druHujflQU){BdChpGbQMj = true;}
      else if(druHujflQU == cgHBTNuopZ){kByzzjmkeA = true;}
      if(lNojTgqLMV == uDOynIWzBN){krSAJtCuGr = true;}
      else if(uDOynIWzBN == lNojTgqLMV){wKkxRBdBem = true;}
      if(mSEEFKLOnU == yCrSzEkkur){OcrljmYbdF = true;}
      else if(yCrSzEkkur == mSEEFKLOnU){KYQPpHjlRm = true;}
      if(GnirNXoaqJ == ygMVTbyCGj){MDtQECBIFK = true;}
      else if(ygMVTbyCGj == GnirNXoaqJ){hhhGPigVlq = true;}
      if(eUDfQHoQDl == aNLjHrXgtz){CiAQGiDsGr = true;}
      if(AznGmKbCuJ == aTgyTbAcHp){dbgUeYlQyC = true;}
      if(CgBVTydxVw == ytpXWOpsdL){gzlGXhyBuG = true;}
      while(aNLjHrXgtz == eUDfQHoQDl){xlskjGzMkb = true;}
      while(aTgyTbAcHp == aTgyTbAcHp){YuOFNLkhJq = true;}
      while(ytpXWOpsdL == ytpXWOpsdL){zASrRNbehi = true;}
      if(JTrQljpHKG == true){JTrQljpHKG = false;}
      if(gEquRdzNBr == true){gEquRdzNBr = false;}
      if(bVtQlgWmNs == true){bVtQlgWmNs = false;}
      if(BdChpGbQMj == true){BdChpGbQMj = false;}
      if(krSAJtCuGr == true){krSAJtCuGr = false;}
      if(OcrljmYbdF == true){OcrljmYbdF = false;}
      if(MDtQECBIFK == true){MDtQECBIFK = false;}
      if(CiAQGiDsGr == true){CiAQGiDsGr = false;}
      if(dbgUeYlQyC == true){dbgUeYlQyC = false;}
      if(gzlGXhyBuG == true){gzlGXhyBuG = false;}
      if(rtouoebbeA == true){rtouoebbeA = false;}
      if(jeUkbjWYkf == true){jeUkbjWYkf = false;}
      if(QkKDdCwssY == true){QkKDdCwssY = false;}
      if(kByzzjmkeA == true){kByzzjmkeA = false;}
      if(wKkxRBdBem == true){wKkxRBdBem = false;}
      if(KYQPpHjlRm == true){KYQPpHjlRm = false;}
      if(hhhGPigVlq == true){hhhGPigVlq = false;}
      if(xlskjGzMkb == true){xlskjGzMkb = false;}
      if(YuOFNLkhJq == true){YuOFNLkhJq = false;}
      if(zASrRNbehi == true){zASrRNbehi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IJBLEZISHG
{ 
  void eksDqTnLSy()
  { 
      bool bojOsqzJMd = false;
      bool CcgptlGEis = false;
      bool hGSNexbeYB = false;
      bool fcXVVPGVTq = false;
      bool XHJwioCXIX = false;
      bool IeSVsUVWjw = false;
      bool OUjKxZFKUd = false;
      bool fjkrVaxVdp = false;
      bool tEWBsBJBcB = false;
      bool tilWbDWzzJ = false;
      bool iqDdrYtazR = false;
      bool XArtBJyhRw = false;
      bool PDhTjwyNPS = false;
      bool EyWUGDBrJT = false;
      bool HiCKctqqUR = false;
      bool EngDsfIisu = false;
      bool ZfKfNZcXny = false;
      bool IFYxogAXpp = false;
      bool EGryNPQTaZ = false;
      bool tRzNtaXVxD = false;
      string SwWuVgPxfr;
      string yYWQxizbiJ;
      string XqTYdYXZSV;
      string YWZzKLwVnb;
      string RyVTpeHIda;
      string gcNYwbcyRw;
      string IpdJSbyWGl;
      string ldnGrYUAiz;
      string RPurouIADh;
      string hyDqTbTMAN;
      string fjCrnDoGgW;
      string HcOSestlUX;
      string SyTXDnaxmP;
      string FIzUShMDDl;
      string GCTgaFijLZ;
      string hhrctgPdoA;
      string bqSQQzcszw;
      string fqhiQQemxy;
      string FpkNhWQVal;
      string RiODJOjCPb;
      if(SwWuVgPxfr == fjCrnDoGgW){bojOsqzJMd = true;}
      else if(fjCrnDoGgW == SwWuVgPxfr){iqDdrYtazR = true;}
      if(yYWQxizbiJ == HcOSestlUX){CcgptlGEis = true;}
      else if(HcOSestlUX == yYWQxizbiJ){XArtBJyhRw = true;}
      if(XqTYdYXZSV == SyTXDnaxmP){hGSNexbeYB = true;}
      else if(SyTXDnaxmP == XqTYdYXZSV){PDhTjwyNPS = true;}
      if(YWZzKLwVnb == FIzUShMDDl){fcXVVPGVTq = true;}
      else if(FIzUShMDDl == YWZzKLwVnb){EyWUGDBrJT = true;}
      if(RyVTpeHIda == GCTgaFijLZ){XHJwioCXIX = true;}
      else if(GCTgaFijLZ == RyVTpeHIda){HiCKctqqUR = true;}
      if(gcNYwbcyRw == hhrctgPdoA){IeSVsUVWjw = true;}
      else if(hhrctgPdoA == gcNYwbcyRw){EngDsfIisu = true;}
      if(IpdJSbyWGl == bqSQQzcszw){OUjKxZFKUd = true;}
      else if(bqSQQzcszw == IpdJSbyWGl){ZfKfNZcXny = true;}
      if(ldnGrYUAiz == fqhiQQemxy){fjkrVaxVdp = true;}
      if(RPurouIADh == FpkNhWQVal){tEWBsBJBcB = true;}
      if(hyDqTbTMAN == RiODJOjCPb){tilWbDWzzJ = true;}
      while(fqhiQQemxy == ldnGrYUAiz){IFYxogAXpp = true;}
      while(FpkNhWQVal == FpkNhWQVal){EGryNPQTaZ = true;}
      while(RiODJOjCPb == RiODJOjCPb){tRzNtaXVxD = true;}
      if(bojOsqzJMd == true){bojOsqzJMd = false;}
      if(CcgptlGEis == true){CcgptlGEis = false;}
      if(hGSNexbeYB == true){hGSNexbeYB = false;}
      if(fcXVVPGVTq == true){fcXVVPGVTq = false;}
      if(XHJwioCXIX == true){XHJwioCXIX = false;}
      if(IeSVsUVWjw == true){IeSVsUVWjw = false;}
      if(OUjKxZFKUd == true){OUjKxZFKUd = false;}
      if(fjkrVaxVdp == true){fjkrVaxVdp = false;}
      if(tEWBsBJBcB == true){tEWBsBJBcB = false;}
      if(tilWbDWzzJ == true){tilWbDWzzJ = false;}
      if(iqDdrYtazR == true){iqDdrYtazR = false;}
      if(XArtBJyhRw == true){XArtBJyhRw = false;}
      if(PDhTjwyNPS == true){PDhTjwyNPS = false;}
      if(EyWUGDBrJT == true){EyWUGDBrJT = false;}
      if(HiCKctqqUR == true){HiCKctqqUR = false;}
      if(EngDsfIisu == true){EngDsfIisu = false;}
      if(ZfKfNZcXny == true){ZfKfNZcXny = false;}
      if(IFYxogAXpp == true){IFYxogAXpp = false;}
      if(EGryNPQTaZ == true){EGryNPQTaZ = false;}
      if(tRzNtaXVxD == true){tRzNtaXVxD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONCIOPTQAH
{ 
  void qJVVdCsnUT()
  { 
      bool sijXTDXXKz = false;
      bool cjguwSxtiA = false;
      bool yuxpXamSTn = false;
      bool eFqBZnmaUz = false;
      bool xMSpfIIaRZ = false;
      bool cMzEMyltAr = false;
      bool QEEVTXreVI = false;
      bool eWZjDkcGKP = false;
      bool RLBtLSFmnb = false;
      bool CsZbhsIwVH = false;
      bool PdEJtFlPAa = false;
      bool UejjZFCKKB = false;
      bool RFptFlwxBK = false;
      bool cfkCznGqzF = false;
      bool fplNGXJpCb = false;
      bool pxkUpKmKEH = false;
      bool InNpyotgkk = false;
      bool yLKFUbScnh = false;
      bool cGuYUeuPMn = false;
      bool BwmqwrbuOR = false;
      string URkuAcCIbG;
      string opNQVXGReT;
      string jMXeRfrTsy;
      string LOFRInqnzU;
      string rlJHoNBIgu;
      string QDRetIsFdT;
      string jhPdtZkwHg;
      string fRSJaxCQpD;
      string djlyhIxZXA;
      string ulJekJWfMO;
      string cFAAOykHEw;
      string FcPZoAuRul;
      string bKXHktHnYR;
      string aVDbaYilii;
      string WpVatSWjoj;
      string NFjZlRgsOU;
      string pwimVjYmzQ;
      string QJhMOlnxMS;
      string XXznDUkdpI;
      string roWOraHiFK;
      if(URkuAcCIbG == cFAAOykHEw){sijXTDXXKz = true;}
      else if(cFAAOykHEw == URkuAcCIbG){PdEJtFlPAa = true;}
      if(opNQVXGReT == FcPZoAuRul){cjguwSxtiA = true;}
      else if(FcPZoAuRul == opNQVXGReT){UejjZFCKKB = true;}
      if(jMXeRfrTsy == bKXHktHnYR){yuxpXamSTn = true;}
      else if(bKXHktHnYR == jMXeRfrTsy){RFptFlwxBK = true;}
      if(LOFRInqnzU == aVDbaYilii){eFqBZnmaUz = true;}
      else if(aVDbaYilii == LOFRInqnzU){cfkCznGqzF = true;}
      if(rlJHoNBIgu == WpVatSWjoj){xMSpfIIaRZ = true;}
      else if(WpVatSWjoj == rlJHoNBIgu){fplNGXJpCb = true;}
      if(QDRetIsFdT == NFjZlRgsOU){cMzEMyltAr = true;}
      else if(NFjZlRgsOU == QDRetIsFdT){pxkUpKmKEH = true;}
      if(jhPdtZkwHg == pwimVjYmzQ){QEEVTXreVI = true;}
      else if(pwimVjYmzQ == jhPdtZkwHg){InNpyotgkk = true;}
      if(fRSJaxCQpD == QJhMOlnxMS){eWZjDkcGKP = true;}
      if(djlyhIxZXA == XXznDUkdpI){RLBtLSFmnb = true;}
      if(ulJekJWfMO == roWOraHiFK){CsZbhsIwVH = true;}
      while(QJhMOlnxMS == fRSJaxCQpD){yLKFUbScnh = true;}
      while(XXznDUkdpI == XXznDUkdpI){cGuYUeuPMn = true;}
      while(roWOraHiFK == roWOraHiFK){BwmqwrbuOR = true;}
      if(sijXTDXXKz == true){sijXTDXXKz = false;}
      if(cjguwSxtiA == true){cjguwSxtiA = false;}
      if(yuxpXamSTn == true){yuxpXamSTn = false;}
      if(eFqBZnmaUz == true){eFqBZnmaUz = false;}
      if(xMSpfIIaRZ == true){xMSpfIIaRZ = false;}
      if(cMzEMyltAr == true){cMzEMyltAr = false;}
      if(QEEVTXreVI == true){QEEVTXreVI = false;}
      if(eWZjDkcGKP == true){eWZjDkcGKP = false;}
      if(RLBtLSFmnb == true){RLBtLSFmnb = false;}
      if(CsZbhsIwVH == true){CsZbhsIwVH = false;}
      if(PdEJtFlPAa == true){PdEJtFlPAa = false;}
      if(UejjZFCKKB == true){UejjZFCKKB = false;}
      if(RFptFlwxBK == true){RFptFlwxBK = false;}
      if(cfkCznGqzF == true){cfkCznGqzF = false;}
      if(fplNGXJpCb == true){fplNGXJpCb = false;}
      if(pxkUpKmKEH == true){pxkUpKmKEH = false;}
      if(InNpyotgkk == true){InNpyotgkk = false;}
      if(yLKFUbScnh == true){yLKFUbScnh = false;}
      if(cGuYUeuPMn == true){cGuYUeuPMn = false;}
      if(BwmqwrbuOR == true){BwmqwrbuOR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NRNVMTASNN
{ 
  void NoBTEsUeFH()
  { 
      bool GHyDeUoCZB = false;
      bool blIVqblbbw = false;
      bool TFMTTHqByY = false;
      bool mxDeRzBsSE = false;
      bool HeSjpaDfAW = false;
      bool lXkDbBtejW = false;
      bool cnEANehdEr = false;
      bool asIXnolccr = false;
      bool EKBamPMzDQ = false;
      bool EVJwbTZSWL = false;
      bool sZbHwsONPm = false;
      bool ORCqRRmcNx = false;
      bool RhanmFiLwU = false;
      bool OTFRzdiset = false;
      bool AzjPBlTSdJ = false;
      bool fxEYsLzmUp = false;
      bool JDRtYuLjrn = false;
      bool isxTxSxKlA = false;
      bool kQhmnQOgXm = false;
      bool euXojxhpqG = false;
      string yGfcdcIziU;
      string mVJeXWExtR;
      string EDAhPALsLR;
      string pepqaZcpxg;
      string WGrHHtHJWG;
      string bRikXtGyNc;
      string RPnQdHfSDx;
      string sNAMuyKrZU;
      string rBWEpYuETg;
      string TecTPHSbcA;
      string OoFYNNQWoY;
      string jNXrjPrjaF;
      string LayWdNkgxn;
      string fiPZGDuyqb;
      string IYPtwFGkjz;
      string OhBWnnpiuz;
      string ciZBsByylf;
      string UtsyxmLEZY;
      string HAxxYxgrkS;
      string MMCqzYzNAu;
      if(yGfcdcIziU == OoFYNNQWoY){GHyDeUoCZB = true;}
      else if(OoFYNNQWoY == yGfcdcIziU){sZbHwsONPm = true;}
      if(mVJeXWExtR == jNXrjPrjaF){blIVqblbbw = true;}
      else if(jNXrjPrjaF == mVJeXWExtR){ORCqRRmcNx = true;}
      if(EDAhPALsLR == LayWdNkgxn){TFMTTHqByY = true;}
      else if(LayWdNkgxn == EDAhPALsLR){RhanmFiLwU = true;}
      if(pepqaZcpxg == fiPZGDuyqb){mxDeRzBsSE = true;}
      else if(fiPZGDuyqb == pepqaZcpxg){OTFRzdiset = true;}
      if(WGrHHtHJWG == IYPtwFGkjz){HeSjpaDfAW = true;}
      else if(IYPtwFGkjz == WGrHHtHJWG){AzjPBlTSdJ = true;}
      if(bRikXtGyNc == OhBWnnpiuz){lXkDbBtejW = true;}
      else if(OhBWnnpiuz == bRikXtGyNc){fxEYsLzmUp = true;}
      if(RPnQdHfSDx == ciZBsByylf){cnEANehdEr = true;}
      else if(ciZBsByylf == RPnQdHfSDx){JDRtYuLjrn = true;}
      if(sNAMuyKrZU == UtsyxmLEZY){asIXnolccr = true;}
      if(rBWEpYuETg == HAxxYxgrkS){EKBamPMzDQ = true;}
      if(TecTPHSbcA == MMCqzYzNAu){EVJwbTZSWL = true;}
      while(UtsyxmLEZY == sNAMuyKrZU){isxTxSxKlA = true;}
      while(HAxxYxgrkS == HAxxYxgrkS){kQhmnQOgXm = true;}
      while(MMCqzYzNAu == MMCqzYzNAu){euXojxhpqG = true;}
      if(GHyDeUoCZB == true){GHyDeUoCZB = false;}
      if(blIVqblbbw == true){blIVqblbbw = false;}
      if(TFMTTHqByY == true){TFMTTHqByY = false;}
      if(mxDeRzBsSE == true){mxDeRzBsSE = false;}
      if(HeSjpaDfAW == true){HeSjpaDfAW = false;}
      if(lXkDbBtejW == true){lXkDbBtejW = false;}
      if(cnEANehdEr == true){cnEANehdEr = false;}
      if(asIXnolccr == true){asIXnolccr = false;}
      if(EKBamPMzDQ == true){EKBamPMzDQ = false;}
      if(EVJwbTZSWL == true){EVJwbTZSWL = false;}
      if(sZbHwsONPm == true){sZbHwsONPm = false;}
      if(ORCqRRmcNx == true){ORCqRRmcNx = false;}
      if(RhanmFiLwU == true){RhanmFiLwU = false;}
      if(OTFRzdiset == true){OTFRzdiset = false;}
      if(AzjPBlTSdJ == true){AzjPBlTSdJ = false;}
      if(fxEYsLzmUp == true){fxEYsLzmUp = false;}
      if(JDRtYuLjrn == true){JDRtYuLjrn = false;}
      if(isxTxSxKlA == true){isxTxSxKlA = false;}
      if(kQhmnQOgXm == true){kQhmnQOgXm = false;}
      if(euXojxhpqG == true){euXojxhpqG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PETMSIOQRE
{ 
  void DOFFAbUhrQ()
  { 
      bool OlxMNMyBOM = false;
      bool QqbLsIVnJP = false;
      bool bEiZKNOSxN = false;
      bool DWzyiUjANw = false;
      bool kbGLGGbiBm = false;
      bool tVyarKCWCA = false;
      bool yeEBJsrdcX = false;
      bool YUZNdzxXSD = false;
      bool keQJSgXXFX = false;
      bool SMxNxGXFBN = false;
      bool OxFdOYukwr = false;
      bool NeEzOSNuhb = false;
      bool VTXFFLXMQX = false;
      bool brVFnnZmts = false;
      bool kmbNKnIyyd = false;
      bool rcWZquYAXD = false;
      bool BhTXQUIyKZ = false;
      bool saAophqKtR = false;
      bool CYNlfzUwNs = false;
      bool OZPqrCSExo = false;
      string neQAFUgJDb;
      string zVQYTOtiDQ;
      string xLFBKYRPAQ;
      string eTnzeDNDpz;
      string AeMTrlegNC;
      string KLYNNbZOpg;
      string CQIlxfhRtQ;
      string AprDPSykJX;
      string skCyGStZkC;
      string dzNJwjWaWL;
      string ENlxCTSVyu;
      string cnFRnQNKfd;
      string lHfqmBciGe;
      string uXOxTezEwm;
      string AYbpYosuVf;
      string VLtrZwgtJA;
      string piOSzFZHxI;
      string RJNsdMfpRy;
      string HhNaIicVXX;
      string yEuuwQJIpT;
      if(neQAFUgJDb == ENlxCTSVyu){OlxMNMyBOM = true;}
      else if(ENlxCTSVyu == neQAFUgJDb){OxFdOYukwr = true;}
      if(zVQYTOtiDQ == cnFRnQNKfd){QqbLsIVnJP = true;}
      else if(cnFRnQNKfd == zVQYTOtiDQ){NeEzOSNuhb = true;}
      if(xLFBKYRPAQ == lHfqmBciGe){bEiZKNOSxN = true;}
      else if(lHfqmBciGe == xLFBKYRPAQ){VTXFFLXMQX = true;}
      if(eTnzeDNDpz == uXOxTezEwm){DWzyiUjANw = true;}
      else if(uXOxTezEwm == eTnzeDNDpz){brVFnnZmts = true;}
      if(AeMTrlegNC == AYbpYosuVf){kbGLGGbiBm = true;}
      else if(AYbpYosuVf == AeMTrlegNC){kmbNKnIyyd = true;}
      if(KLYNNbZOpg == VLtrZwgtJA){tVyarKCWCA = true;}
      else if(VLtrZwgtJA == KLYNNbZOpg){rcWZquYAXD = true;}
      if(CQIlxfhRtQ == piOSzFZHxI){yeEBJsrdcX = true;}
      else if(piOSzFZHxI == CQIlxfhRtQ){BhTXQUIyKZ = true;}
      if(AprDPSykJX == RJNsdMfpRy){YUZNdzxXSD = true;}
      if(skCyGStZkC == HhNaIicVXX){keQJSgXXFX = true;}
      if(dzNJwjWaWL == yEuuwQJIpT){SMxNxGXFBN = true;}
      while(RJNsdMfpRy == AprDPSykJX){saAophqKtR = true;}
      while(HhNaIicVXX == HhNaIicVXX){CYNlfzUwNs = true;}
      while(yEuuwQJIpT == yEuuwQJIpT){OZPqrCSExo = true;}
      if(OlxMNMyBOM == true){OlxMNMyBOM = false;}
      if(QqbLsIVnJP == true){QqbLsIVnJP = false;}
      if(bEiZKNOSxN == true){bEiZKNOSxN = false;}
      if(DWzyiUjANw == true){DWzyiUjANw = false;}
      if(kbGLGGbiBm == true){kbGLGGbiBm = false;}
      if(tVyarKCWCA == true){tVyarKCWCA = false;}
      if(yeEBJsrdcX == true){yeEBJsrdcX = false;}
      if(YUZNdzxXSD == true){YUZNdzxXSD = false;}
      if(keQJSgXXFX == true){keQJSgXXFX = false;}
      if(SMxNxGXFBN == true){SMxNxGXFBN = false;}
      if(OxFdOYukwr == true){OxFdOYukwr = false;}
      if(NeEzOSNuhb == true){NeEzOSNuhb = false;}
      if(VTXFFLXMQX == true){VTXFFLXMQX = false;}
      if(brVFnnZmts == true){brVFnnZmts = false;}
      if(kmbNKnIyyd == true){kmbNKnIyyd = false;}
      if(rcWZquYAXD == true){rcWZquYAXD = false;}
      if(BhTXQUIyKZ == true){BhTXQUIyKZ = false;}
      if(saAophqKtR == true){saAophqKtR = false;}
      if(CYNlfzUwNs == true){CYNlfzUwNs = false;}
      if(OZPqrCSExo == true){OZPqrCSExo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XASZRAGAGH
{ 
  void mGIbiQNrno()
  { 
      bool FyVApchSja = false;
      bool xUEYXPdBoJ = false;
      bool CDgpesnLzo = false;
      bool hzgftRpwEg = false;
      bool HfMCqgFgiI = false;
      bool HnXgxBQfVw = false;
      bool oVTtsxnYeG = false;
      bool YgwICWpdyy = false;
      bool nHcphtbAhr = false;
      bool AKaHrkLSJs = false;
      bool sfBbiZqOda = false;
      bool KmgWIgscMz = false;
      bool VnpmGOGnQR = false;
      bool KXUEEHFBGH = false;
      bool CMVHgNcDzK = false;
      bool riFJXFoOVU = false;
      bool TDyMPmRbRB = false;
      bool arVFxJRiGs = false;
      bool kDoFYaRLgz = false;
      bool RqflmyOIrs = false;
      string qfuBpGoOsa;
      string WeRNDtfpjH;
      string mrOWpHxIsZ;
      string TqIXphWowB;
      string cikGmGCmAk;
      string gATMryRXLi;
      string IgVSHfVtWV;
      string XqshdDHHji;
      string EKIIrTWueq;
      string PycNrwNRzH;
      string jIPdNpGlho;
      string qJncdyXNZn;
      string IaOfFZNfoh;
      string opIcywtdtC;
      string MkNpAGJAit;
      string XAqLyJsjXn;
      string cawAzAALdh;
      string DtSXaWMXez;
      string PMxuKoyxdn;
      string CKFGYkoNqz;
      if(qfuBpGoOsa == jIPdNpGlho){FyVApchSja = true;}
      else if(jIPdNpGlho == qfuBpGoOsa){sfBbiZqOda = true;}
      if(WeRNDtfpjH == qJncdyXNZn){xUEYXPdBoJ = true;}
      else if(qJncdyXNZn == WeRNDtfpjH){KmgWIgscMz = true;}
      if(mrOWpHxIsZ == IaOfFZNfoh){CDgpesnLzo = true;}
      else if(IaOfFZNfoh == mrOWpHxIsZ){VnpmGOGnQR = true;}
      if(TqIXphWowB == opIcywtdtC){hzgftRpwEg = true;}
      else if(opIcywtdtC == TqIXphWowB){KXUEEHFBGH = true;}
      if(cikGmGCmAk == MkNpAGJAit){HfMCqgFgiI = true;}
      else if(MkNpAGJAit == cikGmGCmAk){CMVHgNcDzK = true;}
      if(gATMryRXLi == XAqLyJsjXn){HnXgxBQfVw = true;}
      else if(XAqLyJsjXn == gATMryRXLi){riFJXFoOVU = true;}
      if(IgVSHfVtWV == cawAzAALdh){oVTtsxnYeG = true;}
      else if(cawAzAALdh == IgVSHfVtWV){TDyMPmRbRB = true;}
      if(XqshdDHHji == DtSXaWMXez){YgwICWpdyy = true;}
      if(EKIIrTWueq == PMxuKoyxdn){nHcphtbAhr = true;}
      if(PycNrwNRzH == CKFGYkoNqz){AKaHrkLSJs = true;}
      while(DtSXaWMXez == XqshdDHHji){arVFxJRiGs = true;}
      while(PMxuKoyxdn == PMxuKoyxdn){kDoFYaRLgz = true;}
      while(CKFGYkoNqz == CKFGYkoNqz){RqflmyOIrs = true;}
      if(FyVApchSja == true){FyVApchSja = false;}
      if(xUEYXPdBoJ == true){xUEYXPdBoJ = false;}
      if(CDgpesnLzo == true){CDgpesnLzo = false;}
      if(hzgftRpwEg == true){hzgftRpwEg = false;}
      if(HfMCqgFgiI == true){HfMCqgFgiI = false;}
      if(HnXgxBQfVw == true){HnXgxBQfVw = false;}
      if(oVTtsxnYeG == true){oVTtsxnYeG = false;}
      if(YgwICWpdyy == true){YgwICWpdyy = false;}
      if(nHcphtbAhr == true){nHcphtbAhr = false;}
      if(AKaHrkLSJs == true){AKaHrkLSJs = false;}
      if(sfBbiZqOda == true){sfBbiZqOda = false;}
      if(KmgWIgscMz == true){KmgWIgscMz = false;}
      if(VnpmGOGnQR == true){VnpmGOGnQR = false;}
      if(KXUEEHFBGH == true){KXUEEHFBGH = false;}
      if(CMVHgNcDzK == true){CMVHgNcDzK = false;}
      if(riFJXFoOVU == true){riFJXFoOVU = false;}
      if(TDyMPmRbRB == true){TDyMPmRbRB = false;}
      if(arVFxJRiGs == true){arVFxJRiGs = false;}
      if(kDoFYaRLgz == true){kDoFYaRLgz = false;}
      if(RqflmyOIrs == true){RqflmyOIrs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QUTCDUXZLL
{ 
  void bWjwzfTPex()
  { 
      bool oAXEbSmFbo = false;
      bool xgLEKtkhzw = false;
      bool bBMVbjtrzA = false;
      bool dsdZJNpXqj = false;
      bool YSrppIZifP = false;
      bool scnuGmnCcr = false;
      bool XuGbLECktw = false;
      bool DMqPWIIVeS = false;
      bool JKLjGAFhSV = false;
      bool ZntzLdMPel = false;
      bool FnniLglYXy = false;
      bool dRWKhNiVVL = false;
      bool yTSXWOSqDs = false;
      bool urqsMVVbYZ = false;
      bool NgKUqHRjQy = false;
      bool tqtTnlUQMw = false;
      bool NtUdCkacxM = false;
      bool qGwwxRJyfP = false;
      bool xhaFyEyXFa = false;
      bool AFPcLSMfRF = false;
      string JPLhatTpAW;
      string VoIVkGUhFd;
      string fiKMjCAopt;
      string ulYtBPyKDR;
      string CXzFRQmhjp;
      string SqGfAZEzxX;
      string sdAFaiPOTV;
      string HKdnaIiFtT;
      string PSFzbEfssa;
      string KzMeXYXtdi;
      string AXNOhHMREr;
      string pyEdIaYAdW;
      string DVVsKIyzQC;
      string jobLSqFqQT;
      string rNoAjLtiVx;
      string AXPHeeCTDZ;
      string JNBBIBWsKQ;
      string UhjJeogVIz;
      string OOcTCMYUfn;
      string okmqJdLmqi;
      if(JPLhatTpAW == AXNOhHMREr){oAXEbSmFbo = true;}
      else if(AXNOhHMREr == JPLhatTpAW){FnniLglYXy = true;}
      if(VoIVkGUhFd == pyEdIaYAdW){xgLEKtkhzw = true;}
      else if(pyEdIaYAdW == VoIVkGUhFd){dRWKhNiVVL = true;}
      if(fiKMjCAopt == DVVsKIyzQC){bBMVbjtrzA = true;}
      else if(DVVsKIyzQC == fiKMjCAopt){yTSXWOSqDs = true;}
      if(ulYtBPyKDR == jobLSqFqQT){dsdZJNpXqj = true;}
      else if(jobLSqFqQT == ulYtBPyKDR){urqsMVVbYZ = true;}
      if(CXzFRQmhjp == rNoAjLtiVx){YSrppIZifP = true;}
      else if(rNoAjLtiVx == CXzFRQmhjp){NgKUqHRjQy = true;}
      if(SqGfAZEzxX == AXPHeeCTDZ){scnuGmnCcr = true;}
      else if(AXPHeeCTDZ == SqGfAZEzxX){tqtTnlUQMw = true;}
      if(sdAFaiPOTV == JNBBIBWsKQ){XuGbLECktw = true;}
      else if(JNBBIBWsKQ == sdAFaiPOTV){NtUdCkacxM = true;}
      if(HKdnaIiFtT == UhjJeogVIz){DMqPWIIVeS = true;}
      if(PSFzbEfssa == OOcTCMYUfn){JKLjGAFhSV = true;}
      if(KzMeXYXtdi == okmqJdLmqi){ZntzLdMPel = true;}
      while(UhjJeogVIz == HKdnaIiFtT){qGwwxRJyfP = true;}
      while(OOcTCMYUfn == OOcTCMYUfn){xhaFyEyXFa = true;}
      while(okmqJdLmqi == okmqJdLmqi){AFPcLSMfRF = true;}
      if(oAXEbSmFbo == true){oAXEbSmFbo = false;}
      if(xgLEKtkhzw == true){xgLEKtkhzw = false;}
      if(bBMVbjtrzA == true){bBMVbjtrzA = false;}
      if(dsdZJNpXqj == true){dsdZJNpXqj = false;}
      if(YSrppIZifP == true){YSrppIZifP = false;}
      if(scnuGmnCcr == true){scnuGmnCcr = false;}
      if(XuGbLECktw == true){XuGbLECktw = false;}
      if(DMqPWIIVeS == true){DMqPWIIVeS = false;}
      if(JKLjGAFhSV == true){JKLjGAFhSV = false;}
      if(ZntzLdMPel == true){ZntzLdMPel = false;}
      if(FnniLglYXy == true){FnniLglYXy = false;}
      if(dRWKhNiVVL == true){dRWKhNiVVL = false;}
      if(yTSXWOSqDs == true){yTSXWOSqDs = false;}
      if(urqsMVVbYZ == true){urqsMVVbYZ = false;}
      if(NgKUqHRjQy == true){NgKUqHRjQy = false;}
      if(tqtTnlUQMw == true){tqtTnlUQMw = false;}
      if(NtUdCkacxM == true){NtUdCkacxM = false;}
      if(qGwwxRJyfP == true){qGwwxRJyfP = false;}
      if(xhaFyEyXFa == true){xhaFyEyXFa = false;}
      if(AFPcLSMfRF == true){AFPcLSMfRF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWGRWWFYNZ
{ 
  void bwZZfHnNws()
  { 
      bool fomdzIiuMV = false;
      bool UxqDcEqtcu = false;
      bool cagihGWUQe = false;
      bool SoOVMoIXRZ = false;
      bool xdYjiaYgCH = false;
      bool XHEkHFHDwr = false;
      bool kOdgDehUqn = false;
      bool uScDyyCxzH = false;
      bool hoRJHKkdOH = false;
      bool gEbZniAqfE = false;
      bool rDpOLEeBmI = false;
      bool CKDnKwwTZr = false;
      bool tDGjGpqCPO = false;
      bool yKQuOdzCyD = false;
      bool eiqFEWBmOq = false;
      bool mgRnJnxFIU = false;
      bool MblXKrsHZf = false;
      bool xsUVNKMAfi = false;
      bool oEnXbRsclZ = false;
      bool gstcqDxSuM = false;
      string EHAeIiraKE;
      string LpBgrgjoEU;
      string MtAumVljhm;
      string OMUryGPCtG;
      string OTjyYfHcTe;
      string EayQnKHFql;
      string wHrXoyVIik;
      string QgtyGsJBWH;
      string OJQCinODEn;
      string zKKHJHaMIZ;
      string KyshOWfAKt;
      string AFijWmppoB;
      string iREulGWmny;
      string RxswxQPhnL;
      string HOsJnsbajW;
      string QkXGprsywH;
      string AsLLcCMlmG;
      string XIBctUXuHr;
      string ewCQhgYlFE;
      string XQkfLOChfk;
      if(EHAeIiraKE == KyshOWfAKt){fomdzIiuMV = true;}
      else if(KyshOWfAKt == EHAeIiraKE){rDpOLEeBmI = true;}
      if(LpBgrgjoEU == AFijWmppoB){UxqDcEqtcu = true;}
      else if(AFijWmppoB == LpBgrgjoEU){CKDnKwwTZr = true;}
      if(MtAumVljhm == iREulGWmny){cagihGWUQe = true;}
      else if(iREulGWmny == MtAumVljhm){tDGjGpqCPO = true;}
      if(OMUryGPCtG == RxswxQPhnL){SoOVMoIXRZ = true;}
      else if(RxswxQPhnL == OMUryGPCtG){yKQuOdzCyD = true;}
      if(OTjyYfHcTe == HOsJnsbajW){xdYjiaYgCH = true;}
      else if(HOsJnsbajW == OTjyYfHcTe){eiqFEWBmOq = true;}
      if(EayQnKHFql == QkXGprsywH){XHEkHFHDwr = true;}
      else if(QkXGprsywH == EayQnKHFql){mgRnJnxFIU = true;}
      if(wHrXoyVIik == AsLLcCMlmG){kOdgDehUqn = true;}
      else if(AsLLcCMlmG == wHrXoyVIik){MblXKrsHZf = true;}
      if(QgtyGsJBWH == XIBctUXuHr){uScDyyCxzH = true;}
      if(OJQCinODEn == ewCQhgYlFE){hoRJHKkdOH = true;}
      if(zKKHJHaMIZ == XQkfLOChfk){gEbZniAqfE = true;}
      while(XIBctUXuHr == QgtyGsJBWH){xsUVNKMAfi = true;}
      while(ewCQhgYlFE == ewCQhgYlFE){oEnXbRsclZ = true;}
      while(XQkfLOChfk == XQkfLOChfk){gstcqDxSuM = true;}
      if(fomdzIiuMV == true){fomdzIiuMV = false;}
      if(UxqDcEqtcu == true){UxqDcEqtcu = false;}
      if(cagihGWUQe == true){cagihGWUQe = false;}
      if(SoOVMoIXRZ == true){SoOVMoIXRZ = false;}
      if(xdYjiaYgCH == true){xdYjiaYgCH = false;}
      if(XHEkHFHDwr == true){XHEkHFHDwr = false;}
      if(kOdgDehUqn == true){kOdgDehUqn = false;}
      if(uScDyyCxzH == true){uScDyyCxzH = false;}
      if(hoRJHKkdOH == true){hoRJHKkdOH = false;}
      if(gEbZniAqfE == true){gEbZniAqfE = false;}
      if(rDpOLEeBmI == true){rDpOLEeBmI = false;}
      if(CKDnKwwTZr == true){CKDnKwwTZr = false;}
      if(tDGjGpqCPO == true){tDGjGpqCPO = false;}
      if(yKQuOdzCyD == true){yKQuOdzCyD = false;}
      if(eiqFEWBmOq == true){eiqFEWBmOq = false;}
      if(mgRnJnxFIU == true){mgRnJnxFIU = false;}
      if(MblXKrsHZf == true){MblXKrsHZf = false;}
      if(xsUVNKMAfi == true){xsUVNKMAfi = false;}
      if(oEnXbRsclZ == true){oEnXbRsclZ = false;}
      if(gstcqDxSuM == true){gstcqDxSuM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWYIVMVSUA
{ 
  void jRDiHxTMEe()
  { 
      bool EkSAFknJMg = false;
      bool oHiszaaFSM = false;
      bool MsUOdpgKnV = false;
      bool KWsUOyVpVI = false;
      bool NyAhgHYGVq = false;
      bool yzOoJLQEWP = false;
      bool EdVpVSOOeB = false;
      bool EkiKzNrlhW = false;
      bool QZnxXLIDKC = false;
      bool gRTGDicJMO = false;
      bool rKbTlMPDpw = false;
      bool TdWAyeoXSJ = false;
      bool JKDcTmQbHP = false;
      bool khZSdGxTKK = false;
      bool uENOhDuSIX = false;
      bool tEqDEgGyAz = false;
      bool unwZLlEDWq = false;
      bool gUMHNExouQ = false;
      bool qyTiUfpVOw = false;
      bool zzTLOHImCu = false;
      string cqIluwQddX;
      string dlSWDoTldl;
      string DIwEXEVQCz;
      string odSHEjTTuL;
      string MegdxMYcLJ;
      string IsezHTuDNp;
      string azbdhASKST;
      string VzpRZXaRHK;
      string fsErpuzTzj;
      string oQGEkMDDux;
      string tNJrnJDNZi;
      string scuCKgtimm;
      string AzLieEskfM;
      string UXVKQRiMEg;
      string qktQqLVEtD;
      string STPIwtCaMi;
      string PSgMOUGjks;
      string ygeFuPEuqS;
      string ioqbsBINOW;
      string OIAURYEgCW;
      if(cqIluwQddX == tNJrnJDNZi){EkSAFknJMg = true;}
      else if(tNJrnJDNZi == cqIluwQddX){rKbTlMPDpw = true;}
      if(dlSWDoTldl == scuCKgtimm){oHiszaaFSM = true;}
      else if(scuCKgtimm == dlSWDoTldl){TdWAyeoXSJ = true;}
      if(DIwEXEVQCz == AzLieEskfM){MsUOdpgKnV = true;}
      else if(AzLieEskfM == DIwEXEVQCz){JKDcTmQbHP = true;}
      if(odSHEjTTuL == UXVKQRiMEg){KWsUOyVpVI = true;}
      else if(UXVKQRiMEg == odSHEjTTuL){khZSdGxTKK = true;}
      if(MegdxMYcLJ == qktQqLVEtD){NyAhgHYGVq = true;}
      else if(qktQqLVEtD == MegdxMYcLJ){uENOhDuSIX = true;}
      if(IsezHTuDNp == STPIwtCaMi){yzOoJLQEWP = true;}
      else if(STPIwtCaMi == IsezHTuDNp){tEqDEgGyAz = true;}
      if(azbdhASKST == PSgMOUGjks){EdVpVSOOeB = true;}
      else if(PSgMOUGjks == azbdhASKST){unwZLlEDWq = true;}
      if(VzpRZXaRHK == ygeFuPEuqS){EkiKzNrlhW = true;}
      if(fsErpuzTzj == ioqbsBINOW){QZnxXLIDKC = true;}
      if(oQGEkMDDux == OIAURYEgCW){gRTGDicJMO = true;}
      while(ygeFuPEuqS == VzpRZXaRHK){gUMHNExouQ = true;}
      while(ioqbsBINOW == ioqbsBINOW){qyTiUfpVOw = true;}
      while(OIAURYEgCW == OIAURYEgCW){zzTLOHImCu = true;}
      if(EkSAFknJMg == true){EkSAFknJMg = false;}
      if(oHiszaaFSM == true){oHiszaaFSM = false;}
      if(MsUOdpgKnV == true){MsUOdpgKnV = false;}
      if(KWsUOyVpVI == true){KWsUOyVpVI = false;}
      if(NyAhgHYGVq == true){NyAhgHYGVq = false;}
      if(yzOoJLQEWP == true){yzOoJLQEWP = false;}
      if(EdVpVSOOeB == true){EdVpVSOOeB = false;}
      if(EkiKzNrlhW == true){EkiKzNrlhW = false;}
      if(QZnxXLIDKC == true){QZnxXLIDKC = false;}
      if(gRTGDicJMO == true){gRTGDicJMO = false;}
      if(rKbTlMPDpw == true){rKbTlMPDpw = false;}
      if(TdWAyeoXSJ == true){TdWAyeoXSJ = false;}
      if(JKDcTmQbHP == true){JKDcTmQbHP = false;}
      if(khZSdGxTKK == true){khZSdGxTKK = false;}
      if(uENOhDuSIX == true){uENOhDuSIX = false;}
      if(tEqDEgGyAz == true){tEqDEgGyAz = false;}
      if(unwZLlEDWq == true){unwZLlEDWq = false;}
      if(gUMHNExouQ == true){gUMHNExouQ = false;}
      if(qyTiUfpVOw == true){qyTiUfpVOw = false;}
      if(zzTLOHImCu == true){zzTLOHImCu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JATYMOMWMV
{ 
  void lSiHEXVZJB()
  { 
      bool JIZWOEfZWN = false;
      bool XgaTiuYudi = false;
      bool SosTIVXGpy = false;
      bool cRkkhSmVkV = false;
      bool oKmfHDCOrd = false;
      bool SyCHUTOGOs = false;
      bool fZiYkFwokP = false;
      bool ICJHsICNLE = false;
      bool SJNMedPdPO = false;
      bool EgHqoPaOuC = false;
      bool HNdbVPntNM = false;
      bool RBtJZWLWsG = false;
      bool pSYVLbuRSd = false;
      bool hmRJxFekqP = false;
      bool pVPDwClyRR = false;
      bool DEVnMnnHQs = false;
      bool UVajeeijLT = false;
      bool raecQUCVYI = false;
      bool owAAZcQdxI = false;
      bool RWUxtTtfYR = false;
      string cyOcMaNdRR;
      string XZzFalyXYS;
      string uhnZVEBFmo;
      string cPPtRqBiKR;
      string UaRCCOhFxS;
      string KpQnKuJoHH;
      string YIpcnIKFnj;
      string jOMHyUQlXG;
      string VwHUdmyajW;
      string hMaCrLjoNs;
      string EcRNhwcJpo;
      string eXQBlcAVyB;
      string JiURCWmJOl;
      string jaXdBrdtmh;
      string KnktqJuZQO;
      string LOpMjVHALK;
      string ISuEEDAmzs;
      string zGhQpVyaZr;
      string aMsAaVjKtf;
      string kchbZrsfpn;
      if(cyOcMaNdRR == EcRNhwcJpo){JIZWOEfZWN = true;}
      else if(EcRNhwcJpo == cyOcMaNdRR){HNdbVPntNM = true;}
      if(XZzFalyXYS == eXQBlcAVyB){XgaTiuYudi = true;}
      else if(eXQBlcAVyB == XZzFalyXYS){RBtJZWLWsG = true;}
      if(uhnZVEBFmo == JiURCWmJOl){SosTIVXGpy = true;}
      else if(JiURCWmJOl == uhnZVEBFmo){pSYVLbuRSd = true;}
      if(cPPtRqBiKR == jaXdBrdtmh){cRkkhSmVkV = true;}
      else if(jaXdBrdtmh == cPPtRqBiKR){hmRJxFekqP = true;}
      if(UaRCCOhFxS == KnktqJuZQO){oKmfHDCOrd = true;}
      else if(KnktqJuZQO == UaRCCOhFxS){pVPDwClyRR = true;}
      if(KpQnKuJoHH == LOpMjVHALK){SyCHUTOGOs = true;}
      else if(LOpMjVHALK == KpQnKuJoHH){DEVnMnnHQs = true;}
      if(YIpcnIKFnj == ISuEEDAmzs){fZiYkFwokP = true;}
      else if(ISuEEDAmzs == YIpcnIKFnj){UVajeeijLT = true;}
      if(jOMHyUQlXG == zGhQpVyaZr){ICJHsICNLE = true;}
      if(VwHUdmyajW == aMsAaVjKtf){SJNMedPdPO = true;}
      if(hMaCrLjoNs == kchbZrsfpn){EgHqoPaOuC = true;}
      while(zGhQpVyaZr == jOMHyUQlXG){raecQUCVYI = true;}
      while(aMsAaVjKtf == aMsAaVjKtf){owAAZcQdxI = true;}
      while(kchbZrsfpn == kchbZrsfpn){RWUxtTtfYR = true;}
      if(JIZWOEfZWN == true){JIZWOEfZWN = false;}
      if(XgaTiuYudi == true){XgaTiuYudi = false;}
      if(SosTIVXGpy == true){SosTIVXGpy = false;}
      if(cRkkhSmVkV == true){cRkkhSmVkV = false;}
      if(oKmfHDCOrd == true){oKmfHDCOrd = false;}
      if(SyCHUTOGOs == true){SyCHUTOGOs = false;}
      if(fZiYkFwokP == true){fZiYkFwokP = false;}
      if(ICJHsICNLE == true){ICJHsICNLE = false;}
      if(SJNMedPdPO == true){SJNMedPdPO = false;}
      if(EgHqoPaOuC == true){EgHqoPaOuC = false;}
      if(HNdbVPntNM == true){HNdbVPntNM = false;}
      if(RBtJZWLWsG == true){RBtJZWLWsG = false;}
      if(pSYVLbuRSd == true){pSYVLbuRSd = false;}
      if(hmRJxFekqP == true){hmRJxFekqP = false;}
      if(pVPDwClyRR == true){pVPDwClyRR = false;}
      if(DEVnMnnHQs == true){DEVnMnnHQs = false;}
      if(UVajeeijLT == true){UVajeeijLT = false;}
      if(raecQUCVYI == true){raecQUCVYI = false;}
      if(owAAZcQdxI == true){owAAZcQdxI = false;}
      if(RWUxtTtfYR == true){RWUxtTtfYR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XOVSOJTJRB
{ 
  void ldzwkWsegJ()
  { 
      bool BDiTVxdiLd = false;
      bool QBtfCFOUui = false;
      bool mErBfIAned = false;
      bool ktBcKVsNVV = false;
      bool JGHqkYwTRC = false;
      bool hUsRUwKhnN = false;
      bool xoEgsWzRUf = false;
      bool LBzYZfxBPG = false;
      bool LgVcuPAjHN = false;
      bool KLZHYTCaxO = false;
      bool ZeykpgVUro = false;
      bool zJRgBPSakd = false;
      bool VPJGVzbqzF = false;
      bool cWDBgfijlN = false;
      bool sfqSOBtrGJ = false;
      bool AaoSrKVqPq = false;
      bool FdUlLcFQAU = false;
      bool ghoWjoXqrT = false;
      bool FikpECgjIV = false;
      bool KqTuIPKFGl = false;
      string KpDnTGqALu;
      string OldKjABVmA;
      string mQwDsbPicx;
      string YHRkQwFoCi;
      string wQKfrFVsPN;
      string JYdjRstAuq;
      string qIWOVHTrsm;
      string uLSEEVGPLn;
      string GVSPmzchTX;
      string CFtKqmtwJj;
      string kcAbRyFZew;
      string mdnGjVpGaW;
      string ekYUkpQIMQ;
      string aKGaCdVpxo;
      string tDCWjYQmaV;
      string xmUmFzDeqb;
      string hwMOVcXNEG;
      string zzJlbahCkL;
      string YchqTmoSUC;
      string ZqzUHxpnAH;
      if(KpDnTGqALu == kcAbRyFZew){BDiTVxdiLd = true;}
      else if(kcAbRyFZew == KpDnTGqALu){ZeykpgVUro = true;}
      if(OldKjABVmA == mdnGjVpGaW){QBtfCFOUui = true;}
      else if(mdnGjVpGaW == OldKjABVmA){zJRgBPSakd = true;}
      if(mQwDsbPicx == ekYUkpQIMQ){mErBfIAned = true;}
      else if(ekYUkpQIMQ == mQwDsbPicx){VPJGVzbqzF = true;}
      if(YHRkQwFoCi == aKGaCdVpxo){ktBcKVsNVV = true;}
      else if(aKGaCdVpxo == YHRkQwFoCi){cWDBgfijlN = true;}
      if(wQKfrFVsPN == tDCWjYQmaV){JGHqkYwTRC = true;}
      else if(tDCWjYQmaV == wQKfrFVsPN){sfqSOBtrGJ = true;}
      if(JYdjRstAuq == xmUmFzDeqb){hUsRUwKhnN = true;}
      else if(xmUmFzDeqb == JYdjRstAuq){AaoSrKVqPq = true;}
      if(qIWOVHTrsm == hwMOVcXNEG){xoEgsWzRUf = true;}
      else if(hwMOVcXNEG == qIWOVHTrsm){FdUlLcFQAU = true;}
      if(uLSEEVGPLn == zzJlbahCkL){LBzYZfxBPG = true;}
      if(GVSPmzchTX == YchqTmoSUC){LgVcuPAjHN = true;}
      if(CFtKqmtwJj == ZqzUHxpnAH){KLZHYTCaxO = true;}
      while(zzJlbahCkL == uLSEEVGPLn){ghoWjoXqrT = true;}
      while(YchqTmoSUC == YchqTmoSUC){FikpECgjIV = true;}
      while(ZqzUHxpnAH == ZqzUHxpnAH){KqTuIPKFGl = true;}
      if(BDiTVxdiLd == true){BDiTVxdiLd = false;}
      if(QBtfCFOUui == true){QBtfCFOUui = false;}
      if(mErBfIAned == true){mErBfIAned = false;}
      if(ktBcKVsNVV == true){ktBcKVsNVV = false;}
      if(JGHqkYwTRC == true){JGHqkYwTRC = false;}
      if(hUsRUwKhnN == true){hUsRUwKhnN = false;}
      if(xoEgsWzRUf == true){xoEgsWzRUf = false;}
      if(LBzYZfxBPG == true){LBzYZfxBPG = false;}
      if(LgVcuPAjHN == true){LgVcuPAjHN = false;}
      if(KLZHYTCaxO == true){KLZHYTCaxO = false;}
      if(ZeykpgVUro == true){ZeykpgVUro = false;}
      if(zJRgBPSakd == true){zJRgBPSakd = false;}
      if(VPJGVzbqzF == true){VPJGVzbqzF = false;}
      if(cWDBgfijlN == true){cWDBgfijlN = false;}
      if(sfqSOBtrGJ == true){sfqSOBtrGJ = false;}
      if(AaoSrKVqPq == true){AaoSrKVqPq = false;}
      if(FdUlLcFQAU == true){FdUlLcFQAU = false;}
      if(ghoWjoXqrT == true){ghoWjoXqrT = false;}
      if(FikpECgjIV == true){FikpECgjIV = false;}
      if(KqTuIPKFGl == true){KqTuIPKFGl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUNKAFZIBO
{ 
  void BkYLBemmch()
  { 
      bool MpupMYzyYp = false;
      bool nxJNCPsERi = false;
      bool skSpGTkGEC = false;
      bool XhfqLpwcPd = false;
      bool uIqpFiXFjC = false;
      bool IklDkaWEir = false;
      bool mssWSGQSBL = false;
      bool TQommjsckX = false;
      bool ueWCtlwcFj = false;
      bool SqsWpCOUXz = false;
      bool RFEXirwyPA = false;
      bool htTLwHVqcf = false;
      bool KnMQrbWRwj = false;
      bool UYEkFpazSB = false;
      bool pxMFCYWgZh = false;
      bool gXrrocrmeG = false;
      bool UdBfeJohGG = false;
      bool gWXaoMbHNT = false;
      bool FoqNDxfMwb = false;
      bool ynTMgLufZs = false;
      string XcFmlgFPnj;
      string ciPcGhDuJD;
      string nFkubKZLcp;
      string ptxxYEjuml;
      string hsNqWVQicC;
      string lRxWNSqJKb;
      string GsmyshkSEB;
      string xIIXVtqsYF;
      string sqhZDYxaiF;
      string MakLenGPyn;
      string kydbFdJZBS;
      string bxjEhPLNuT;
      string kKiznWWwrg;
      string naujUuMGUY;
      string OWYQdPpfcP;
      string crUdDZOemh;
      string GMgUdACAjm;
      string CErVENlRUY;
      string fqTcDuGQgt;
      string fhTlRCpDld;
      if(XcFmlgFPnj == kydbFdJZBS){MpupMYzyYp = true;}
      else if(kydbFdJZBS == XcFmlgFPnj){RFEXirwyPA = true;}
      if(ciPcGhDuJD == bxjEhPLNuT){nxJNCPsERi = true;}
      else if(bxjEhPLNuT == ciPcGhDuJD){htTLwHVqcf = true;}
      if(nFkubKZLcp == kKiznWWwrg){skSpGTkGEC = true;}
      else if(kKiznWWwrg == nFkubKZLcp){KnMQrbWRwj = true;}
      if(ptxxYEjuml == naujUuMGUY){XhfqLpwcPd = true;}
      else if(naujUuMGUY == ptxxYEjuml){UYEkFpazSB = true;}
      if(hsNqWVQicC == OWYQdPpfcP){uIqpFiXFjC = true;}
      else if(OWYQdPpfcP == hsNqWVQicC){pxMFCYWgZh = true;}
      if(lRxWNSqJKb == crUdDZOemh){IklDkaWEir = true;}
      else if(crUdDZOemh == lRxWNSqJKb){gXrrocrmeG = true;}
      if(GsmyshkSEB == GMgUdACAjm){mssWSGQSBL = true;}
      else if(GMgUdACAjm == GsmyshkSEB){UdBfeJohGG = true;}
      if(xIIXVtqsYF == CErVENlRUY){TQommjsckX = true;}
      if(sqhZDYxaiF == fqTcDuGQgt){ueWCtlwcFj = true;}
      if(MakLenGPyn == fhTlRCpDld){SqsWpCOUXz = true;}
      while(CErVENlRUY == xIIXVtqsYF){gWXaoMbHNT = true;}
      while(fqTcDuGQgt == fqTcDuGQgt){FoqNDxfMwb = true;}
      while(fhTlRCpDld == fhTlRCpDld){ynTMgLufZs = true;}
      if(MpupMYzyYp == true){MpupMYzyYp = false;}
      if(nxJNCPsERi == true){nxJNCPsERi = false;}
      if(skSpGTkGEC == true){skSpGTkGEC = false;}
      if(XhfqLpwcPd == true){XhfqLpwcPd = false;}
      if(uIqpFiXFjC == true){uIqpFiXFjC = false;}
      if(IklDkaWEir == true){IklDkaWEir = false;}
      if(mssWSGQSBL == true){mssWSGQSBL = false;}
      if(TQommjsckX == true){TQommjsckX = false;}
      if(ueWCtlwcFj == true){ueWCtlwcFj = false;}
      if(SqsWpCOUXz == true){SqsWpCOUXz = false;}
      if(RFEXirwyPA == true){RFEXirwyPA = false;}
      if(htTLwHVqcf == true){htTLwHVqcf = false;}
      if(KnMQrbWRwj == true){KnMQrbWRwj = false;}
      if(UYEkFpazSB == true){UYEkFpazSB = false;}
      if(pxMFCYWgZh == true){pxMFCYWgZh = false;}
      if(gXrrocrmeG == true){gXrrocrmeG = false;}
      if(UdBfeJohGG == true){UdBfeJohGG = false;}
      if(gWXaoMbHNT == true){gWXaoMbHNT = false;}
      if(FoqNDxfMwb == true){FoqNDxfMwb = false;}
      if(ynTMgLufZs == true){ynTMgLufZs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MPLMCYGWEQ
{ 
  void fZAOPiLadL()
  { 
      bool msbjPXDMSw = false;
      bool PmRUupGXRJ = false;
      bool dnVIcUgPTe = false;
      bool mEDkIIYAKM = false;
      bool nXsJtTzKcC = false;
      bool TZzqKzXSHt = false;
      bool pmrnJLjgLl = false;
      bool QFMFVFtLOJ = false;
      bool VWmRKNFLZJ = false;
      bool kFsQVAfEAh = false;
      bool jRzqkNMsUE = false;
      bool ELDyXTzZdw = false;
      bool GXGBALMwjV = false;
      bool ZoLgZEXwfw = false;
      bool ALqVEYBurB = false;
      bool AGaDaLKxpZ = false;
      bool BPJzePAWYT = false;
      bool wDsguufkxb = false;
      bool JREhUTNHFN = false;
      bool sZGGujCrqo = false;
      string jtuQOcLXtM;
      string oOCnCNEhzQ;
      string ocYbemDFVW;
      string UfgIitEwbX;
      string AEuoYHqZId;
      string xDFoVGUTlb;
      string YFBXqIgsFI;
      string IHFbQkhjDW;
      string udwqZRarmb;
      string YkKAytCXyP;
      string ayUAVoxcYj;
      string YkPOguJKyZ;
      string hoGciXxFdV;
      string iJknuxIwVj;
      string TxTCDmUuTC;
      string kqZYgkqqQx;
      string qrzCBOAbTi;
      string lMnNFkUEZw;
      string CBkajqjMGK;
      string GQeXsaxQBn;
      if(jtuQOcLXtM == ayUAVoxcYj){msbjPXDMSw = true;}
      else if(ayUAVoxcYj == jtuQOcLXtM){jRzqkNMsUE = true;}
      if(oOCnCNEhzQ == YkPOguJKyZ){PmRUupGXRJ = true;}
      else if(YkPOguJKyZ == oOCnCNEhzQ){ELDyXTzZdw = true;}
      if(ocYbemDFVW == hoGciXxFdV){dnVIcUgPTe = true;}
      else if(hoGciXxFdV == ocYbemDFVW){GXGBALMwjV = true;}
      if(UfgIitEwbX == iJknuxIwVj){mEDkIIYAKM = true;}
      else if(iJknuxIwVj == UfgIitEwbX){ZoLgZEXwfw = true;}
      if(AEuoYHqZId == TxTCDmUuTC){nXsJtTzKcC = true;}
      else if(TxTCDmUuTC == AEuoYHqZId){ALqVEYBurB = true;}
      if(xDFoVGUTlb == kqZYgkqqQx){TZzqKzXSHt = true;}
      else if(kqZYgkqqQx == xDFoVGUTlb){AGaDaLKxpZ = true;}
      if(YFBXqIgsFI == qrzCBOAbTi){pmrnJLjgLl = true;}
      else if(qrzCBOAbTi == YFBXqIgsFI){BPJzePAWYT = true;}
      if(IHFbQkhjDW == lMnNFkUEZw){QFMFVFtLOJ = true;}
      if(udwqZRarmb == CBkajqjMGK){VWmRKNFLZJ = true;}
      if(YkKAytCXyP == GQeXsaxQBn){kFsQVAfEAh = true;}
      while(lMnNFkUEZw == IHFbQkhjDW){wDsguufkxb = true;}
      while(CBkajqjMGK == CBkajqjMGK){JREhUTNHFN = true;}
      while(GQeXsaxQBn == GQeXsaxQBn){sZGGujCrqo = true;}
      if(msbjPXDMSw == true){msbjPXDMSw = false;}
      if(PmRUupGXRJ == true){PmRUupGXRJ = false;}
      if(dnVIcUgPTe == true){dnVIcUgPTe = false;}
      if(mEDkIIYAKM == true){mEDkIIYAKM = false;}
      if(nXsJtTzKcC == true){nXsJtTzKcC = false;}
      if(TZzqKzXSHt == true){TZzqKzXSHt = false;}
      if(pmrnJLjgLl == true){pmrnJLjgLl = false;}
      if(QFMFVFtLOJ == true){QFMFVFtLOJ = false;}
      if(VWmRKNFLZJ == true){VWmRKNFLZJ = false;}
      if(kFsQVAfEAh == true){kFsQVAfEAh = false;}
      if(jRzqkNMsUE == true){jRzqkNMsUE = false;}
      if(ELDyXTzZdw == true){ELDyXTzZdw = false;}
      if(GXGBALMwjV == true){GXGBALMwjV = false;}
      if(ZoLgZEXwfw == true){ZoLgZEXwfw = false;}
      if(ALqVEYBurB == true){ALqVEYBurB = false;}
      if(AGaDaLKxpZ == true){AGaDaLKxpZ = false;}
      if(BPJzePAWYT == true){BPJzePAWYT = false;}
      if(wDsguufkxb == true){wDsguufkxb = false;}
      if(JREhUTNHFN == true){JREhUTNHFN = false;}
      if(sZGGujCrqo == true){sZGGujCrqo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HVMWFFICAD
{ 
  void JscNVxMatP()
  { 
      bool YzbQqHQFTR = false;
      bool ukWLPjkZFK = false;
      bool bXMETddCSk = false;
      bool XpbltKCuuH = false;
      bool gjaRoKWDyk = false;
      bool RIiiGBlXxN = false;
      bool dNlitFJjRF = false;
      bool gpexcrwuOI = false;
      bool HZDgSPGses = false;
      bool YexhdSxrXj = false;
      bool BllsDbclFN = false;
      bool EpIoFDJEPd = false;
      bool yPEYgCswSK = false;
      bool uEXeGVmKdq = false;
      bool lTmQnhVHcZ = false;
      bool JrcskkgNMB = false;
      bool hgTuSASdhj = false;
      bool PzaXrdbnjz = false;
      bool fkTrADbdsU = false;
      bool nZxbJFArym = false;
      string eMZCMqeedI;
      string TaBWREDlEW;
      string eflgbPjEGN;
      string ZCorApwque;
      string PLghtBkkRm;
      string UhpsEzasaw;
      string HaYPiQkIWa;
      string ILqZGSzDla;
      string eylSsrMwmA;
      string PCQyXomQzc;
      string PbNqeJpPll;
      string AWGARInFWp;
      string DoVVLFusCQ;
      string ehEJLCkuni;
      string BwJAArwQgO;
      string BhsIYZGqeY;
      string OxNUHRSxoP;
      string WsRnoHeUUT;
      string JdMmPxoujk;
      string wsPOUDiosi;
      if(eMZCMqeedI == PbNqeJpPll){YzbQqHQFTR = true;}
      else if(PbNqeJpPll == eMZCMqeedI){BllsDbclFN = true;}
      if(TaBWREDlEW == AWGARInFWp){ukWLPjkZFK = true;}
      else if(AWGARInFWp == TaBWREDlEW){EpIoFDJEPd = true;}
      if(eflgbPjEGN == DoVVLFusCQ){bXMETddCSk = true;}
      else if(DoVVLFusCQ == eflgbPjEGN){yPEYgCswSK = true;}
      if(ZCorApwque == ehEJLCkuni){XpbltKCuuH = true;}
      else if(ehEJLCkuni == ZCorApwque){uEXeGVmKdq = true;}
      if(PLghtBkkRm == BwJAArwQgO){gjaRoKWDyk = true;}
      else if(BwJAArwQgO == PLghtBkkRm){lTmQnhVHcZ = true;}
      if(UhpsEzasaw == BhsIYZGqeY){RIiiGBlXxN = true;}
      else if(BhsIYZGqeY == UhpsEzasaw){JrcskkgNMB = true;}
      if(HaYPiQkIWa == OxNUHRSxoP){dNlitFJjRF = true;}
      else if(OxNUHRSxoP == HaYPiQkIWa){hgTuSASdhj = true;}
      if(ILqZGSzDla == WsRnoHeUUT){gpexcrwuOI = true;}
      if(eylSsrMwmA == JdMmPxoujk){HZDgSPGses = true;}
      if(PCQyXomQzc == wsPOUDiosi){YexhdSxrXj = true;}
      while(WsRnoHeUUT == ILqZGSzDla){PzaXrdbnjz = true;}
      while(JdMmPxoujk == JdMmPxoujk){fkTrADbdsU = true;}
      while(wsPOUDiosi == wsPOUDiosi){nZxbJFArym = true;}
      if(YzbQqHQFTR == true){YzbQqHQFTR = false;}
      if(ukWLPjkZFK == true){ukWLPjkZFK = false;}
      if(bXMETddCSk == true){bXMETddCSk = false;}
      if(XpbltKCuuH == true){XpbltKCuuH = false;}
      if(gjaRoKWDyk == true){gjaRoKWDyk = false;}
      if(RIiiGBlXxN == true){RIiiGBlXxN = false;}
      if(dNlitFJjRF == true){dNlitFJjRF = false;}
      if(gpexcrwuOI == true){gpexcrwuOI = false;}
      if(HZDgSPGses == true){HZDgSPGses = false;}
      if(YexhdSxrXj == true){YexhdSxrXj = false;}
      if(BllsDbclFN == true){BllsDbclFN = false;}
      if(EpIoFDJEPd == true){EpIoFDJEPd = false;}
      if(yPEYgCswSK == true){yPEYgCswSK = false;}
      if(uEXeGVmKdq == true){uEXeGVmKdq = false;}
      if(lTmQnhVHcZ == true){lTmQnhVHcZ = false;}
      if(JrcskkgNMB == true){JrcskkgNMB = false;}
      if(hgTuSASdhj == true){hgTuSASdhj = false;}
      if(PzaXrdbnjz == true){PzaXrdbnjz = false;}
      if(fkTrADbdsU == true){fkTrADbdsU = false;}
      if(nZxbJFArym == true){nZxbJFArym = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JNIJZBOFBY
{ 
  void IrktnXofSf()
  { 
      bool RZOiBoSTdm = false;
      bool mWGKIwNqro = false;
      bool FCNZqgKYAU = false;
      bool FKifOTARVV = false;
      bool QdBJnKRowy = false;
      bool rzcprPLoqT = false;
      bool dtSIgcmZun = false;
      bool wuUVXaADkg = false;
      bool PUbBbGhsnz = false;
      bool HLaBqWLscL = false;
      bool WqsICxdGSQ = false;
      bool PIEJEJSQfa = false;
      bool ttkwfjUSdB = false;
      bool PGaYKYaSye = false;
      bool baaXjzGQxh = false;
      bool DtMBQbFxbR = false;
      bool bKbQAIgeze = false;
      bool hzRByTTNMg = false;
      bool dEVwxUtYHh = false;
      bool SdqgCQzJWb = false;
      string NmAoQhIqqK;
      string tDNYbeQPNj;
      string WKewcEsoTk;
      string VuNiXbcYJL;
      string VGaqhLiSYg;
      string jcwbWCHDML;
      string oTXFozoeBA;
      string CrGBNPjnNQ;
      string VaQlArzlLU;
      string TYLxVChUCi;
      string VERXerWtNG;
      string SToupOCkEw;
      string ADSfgcfIeK;
      string gOketRIrHI;
      string UEXECziPHH;
      string zxQFhSkkqB;
      string MOODYEhJBX;
      string FKdwbueOdg;
      string sPBXKjyfwb;
      string gXAFuGpUex;
      if(NmAoQhIqqK == VERXerWtNG){RZOiBoSTdm = true;}
      else if(VERXerWtNG == NmAoQhIqqK){WqsICxdGSQ = true;}
      if(tDNYbeQPNj == SToupOCkEw){mWGKIwNqro = true;}
      else if(SToupOCkEw == tDNYbeQPNj){PIEJEJSQfa = true;}
      if(WKewcEsoTk == ADSfgcfIeK){FCNZqgKYAU = true;}
      else if(ADSfgcfIeK == WKewcEsoTk){ttkwfjUSdB = true;}
      if(VuNiXbcYJL == gOketRIrHI){FKifOTARVV = true;}
      else if(gOketRIrHI == VuNiXbcYJL){PGaYKYaSye = true;}
      if(VGaqhLiSYg == UEXECziPHH){QdBJnKRowy = true;}
      else if(UEXECziPHH == VGaqhLiSYg){baaXjzGQxh = true;}
      if(jcwbWCHDML == zxQFhSkkqB){rzcprPLoqT = true;}
      else if(zxQFhSkkqB == jcwbWCHDML){DtMBQbFxbR = true;}
      if(oTXFozoeBA == MOODYEhJBX){dtSIgcmZun = true;}
      else if(MOODYEhJBX == oTXFozoeBA){bKbQAIgeze = true;}
      if(CrGBNPjnNQ == FKdwbueOdg){wuUVXaADkg = true;}
      if(VaQlArzlLU == sPBXKjyfwb){PUbBbGhsnz = true;}
      if(TYLxVChUCi == gXAFuGpUex){HLaBqWLscL = true;}
      while(FKdwbueOdg == CrGBNPjnNQ){hzRByTTNMg = true;}
      while(sPBXKjyfwb == sPBXKjyfwb){dEVwxUtYHh = true;}
      while(gXAFuGpUex == gXAFuGpUex){SdqgCQzJWb = true;}
      if(RZOiBoSTdm == true){RZOiBoSTdm = false;}
      if(mWGKIwNqro == true){mWGKIwNqro = false;}
      if(FCNZqgKYAU == true){FCNZqgKYAU = false;}
      if(FKifOTARVV == true){FKifOTARVV = false;}
      if(QdBJnKRowy == true){QdBJnKRowy = false;}
      if(rzcprPLoqT == true){rzcprPLoqT = false;}
      if(dtSIgcmZun == true){dtSIgcmZun = false;}
      if(wuUVXaADkg == true){wuUVXaADkg = false;}
      if(PUbBbGhsnz == true){PUbBbGhsnz = false;}
      if(HLaBqWLscL == true){HLaBqWLscL = false;}
      if(WqsICxdGSQ == true){WqsICxdGSQ = false;}
      if(PIEJEJSQfa == true){PIEJEJSQfa = false;}
      if(ttkwfjUSdB == true){ttkwfjUSdB = false;}
      if(PGaYKYaSye == true){PGaYKYaSye = false;}
      if(baaXjzGQxh == true){baaXjzGQxh = false;}
      if(DtMBQbFxbR == true){DtMBQbFxbR = false;}
      if(bKbQAIgeze == true){bKbQAIgeze = false;}
      if(hzRByTTNMg == true){hzRByTTNMg = false;}
      if(dEVwxUtYHh == true){dEVwxUtYHh = false;}
      if(SdqgCQzJWb == true){SdqgCQzJWb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CKOOKMBVRY
{ 
  void WdqGLJtftY()
  { 
      bool mphoNLZiZy = false;
      bool mgbnDyxAGZ = false;
      bool HgIxIDouHJ = false;
      bool hKtbIzYIbL = false;
      bool GgwWEmhsIL = false;
      bool FEZOPFgkgJ = false;
      bool VdbQPclAeD = false;
      bool ZnYuTZkkrV = false;
      bool VuluDdjfMC = false;
      bool SnbRobFfGb = false;
      bool AhNFlReeuo = false;
      bool UwrKnarfMk = false;
      bool rGmckkMGGr = false;
      bool UFeQVnggJl = false;
      bool yFjWhWwQdN = false;
      bool jYSUistkUB = false;
      bool EXXDUPRaoz = false;
      bool sKWammWPtO = false;
      bool oucrIumJgc = false;
      bool tuLIgaggCR = false;
      string WJAIYJoruw;
      string pMoNWeZdTl;
      string YbjloaGIWI;
      string XCMtgdRGec;
      string GPXZIhrBQP;
      string FKzQduYNTx;
      string DgUlYmzufs;
      string NSyqfJDKcG;
      string iFqHDMDwPl;
      string FElgZYukAV;
      string ixUXClMHjU;
      string qNkNOypMiM;
      string iDetmJfQRG;
      string OSKHXljSFQ;
      string zuLuuqTYSa;
      string ihBmleRajs;
      string GupdGXDcpc;
      string NXHRNmrjyw;
      string pHypWfQWUr;
      string TJhLKDFgoW;
      if(WJAIYJoruw == ixUXClMHjU){mphoNLZiZy = true;}
      else if(ixUXClMHjU == WJAIYJoruw){AhNFlReeuo = true;}
      if(pMoNWeZdTl == qNkNOypMiM){mgbnDyxAGZ = true;}
      else if(qNkNOypMiM == pMoNWeZdTl){UwrKnarfMk = true;}
      if(YbjloaGIWI == iDetmJfQRG){HgIxIDouHJ = true;}
      else if(iDetmJfQRG == YbjloaGIWI){rGmckkMGGr = true;}
      if(XCMtgdRGec == OSKHXljSFQ){hKtbIzYIbL = true;}
      else if(OSKHXljSFQ == XCMtgdRGec){UFeQVnggJl = true;}
      if(GPXZIhrBQP == zuLuuqTYSa){GgwWEmhsIL = true;}
      else if(zuLuuqTYSa == GPXZIhrBQP){yFjWhWwQdN = true;}
      if(FKzQduYNTx == ihBmleRajs){FEZOPFgkgJ = true;}
      else if(ihBmleRajs == FKzQduYNTx){jYSUistkUB = true;}
      if(DgUlYmzufs == GupdGXDcpc){VdbQPclAeD = true;}
      else if(GupdGXDcpc == DgUlYmzufs){EXXDUPRaoz = true;}
      if(NSyqfJDKcG == NXHRNmrjyw){ZnYuTZkkrV = true;}
      if(iFqHDMDwPl == pHypWfQWUr){VuluDdjfMC = true;}
      if(FElgZYukAV == TJhLKDFgoW){SnbRobFfGb = true;}
      while(NXHRNmrjyw == NSyqfJDKcG){sKWammWPtO = true;}
      while(pHypWfQWUr == pHypWfQWUr){oucrIumJgc = true;}
      while(TJhLKDFgoW == TJhLKDFgoW){tuLIgaggCR = true;}
      if(mphoNLZiZy == true){mphoNLZiZy = false;}
      if(mgbnDyxAGZ == true){mgbnDyxAGZ = false;}
      if(HgIxIDouHJ == true){HgIxIDouHJ = false;}
      if(hKtbIzYIbL == true){hKtbIzYIbL = false;}
      if(GgwWEmhsIL == true){GgwWEmhsIL = false;}
      if(FEZOPFgkgJ == true){FEZOPFgkgJ = false;}
      if(VdbQPclAeD == true){VdbQPclAeD = false;}
      if(ZnYuTZkkrV == true){ZnYuTZkkrV = false;}
      if(VuluDdjfMC == true){VuluDdjfMC = false;}
      if(SnbRobFfGb == true){SnbRobFfGb = false;}
      if(AhNFlReeuo == true){AhNFlReeuo = false;}
      if(UwrKnarfMk == true){UwrKnarfMk = false;}
      if(rGmckkMGGr == true){rGmckkMGGr = false;}
      if(UFeQVnggJl == true){UFeQVnggJl = false;}
      if(yFjWhWwQdN == true){yFjWhWwQdN = false;}
      if(jYSUistkUB == true){jYSUistkUB = false;}
      if(EXXDUPRaoz == true){EXXDUPRaoz = false;}
      if(sKWammWPtO == true){sKWammWPtO = false;}
      if(oucrIumJgc == true){oucrIumJgc = false;}
      if(tuLIgaggCR == true){tuLIgaggCR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DMSMSLCQEP
{ 
  void VHoYmOhsJQ()
  { 
      bool gISnByZqfL = false;
      bool bQUogjESnd = false;
      bool CYcOaQnZxQ = false;
      bool lfcnQBSmsB = false;
      bool DlABSHkTJD = false;
      bool jnTGeHfDNk = false;
      bool KzsPYwnfYe = false;
      bool RQZlZPXawS = false;
      bool fUQtfxLVJJ = false;
      bool UOYHqDskcW = false;
      bool SEtdlSOhgO = false;
      bool iFHtEoiyia = false;
      bool jSVPKDqRuV = false;
      bool VmxYAaZlIN = false;
      bool idntZPGeCB = false;
      bool UtCBlAieTi = false;
      bool axlKrwHhtd = false;
      bool PxpUrGdapt = false;
      bool wMOsBbjwmz = false;
      bool ruRZllqdBc = false;
      string EfSPfUDmUG;
      string LeZzHVlequ;
      string hndWisfnDi;
      string PtJCPMDcbf;
      string GYJBjWGJTT;
      string qzrajQBufm;
      string oPilpQUXiu;
      string SJDKnJdclM;
      string lWUjqQCiRz;
      string KIwnqqoXKT;
      string BiZXBhugla;
      string lXITBStztZ;
      string OkFijJMOTx;
      string TGRSKCwwhI;
      string UUxqNmzbmX;
      string wpckFPdpmq;
      string UfNoGfGpJy;
      string WxQlEsnNVx;
      string KkbuAcdgNt;
      string XFJpnnHIkg;
      if(EfSPfUDmUG == BiZXBhugla){gISnByZqfL = true;}
      else if(BiZXBhugla == EfSPfUDmUG){SEtdlSOhgO = true;}
      if(LeZzHVlequ == lXITBStztZ){bQUogjESnd = true;}
      else if(lXITBStztZ == LeZzHVlequ){iFHtEoiyia = true;}
      if(hndWisfnDi == OkFijJMOTx){CYcOaQnZxQ = true;}
      else if(OkFijJMOTx == hndWisfnDi){jSVPKDqRuV = true;}
      if(PtJCPMDcbf == TGRSKCwwhI){lfcnQBSmsB = true;}
      else if(TGRSKCwwhI == PtJCPMDcbf){VmxYAaZlIN = true;}
      if(GYJBjWGJTT == UUxqNmzbmX){DlABSHkTJD = true;}
      else if(UUxqNmzbmX == GYJBjWGJTT){idntZPGeCB = true;}
      if(qzrajQBufm == wpckFPdpmq){jnTGeHfDNk = true;}
      else if(wpckFPdpmq == qzrajQBufm){UtCBlAieTi = true;}
      if(oPilpQUXiu == UfNoGfGpJy){KzsPYwnfYe = true;}
      else if(UfNoGfGpJy == oPilpQUXiu){axlKrwHhtd = true;}
      if(SJDKnJdclM == WxQlEsnNVx){RQZlZPXawS = true;}
      if(lWUjqQCiRz == KkbuAcdgNt){fUQtfxLVJJ = true;}
      if(KIwnqqoXKT == XFJpnnHIkg){UOYHqDskcW = true;}
      while(WxQlEsnNVx == SJDKnJdclM){PxpUrGdapt = true;}
      while(KkbuAcdgNt == KkbuAcdgNt){wMOsBbjwmz = true;}
      while(XFJpnnHIkg == XFJpnnHIkg){ruRZllqdBc = true;}
      if(gISnByZqfL == true){gISnByZqfL = false;}
      if(bQUogjESnd == true){bQUogjESnd = false;}
      if(CYcOaQnZxQ == true){CYcOaQnZxQ = false;}
      if(lfcnQBSmsB == true){lfcnQBSmsB = false;}
      if(DlABSHkTJD == true){DlABSHkTJD = false;}
      if(jnTGeHfDNk == true){jnTGeHfDNk = false;}
      if(KzsPYwnfYe == true){KzsPYwnfYe = false;}
      if(RQZlZPXawS == true){RQZlZPXawS = false;}
      if(fUQtfxLVJJ == true){fUQtfxLVJJ = false;}
      if(UOYHqDskcW == true){UOYHqDskcW = false;}
      if(SEtdlSOhgO == true){SEtdlSOhgO = false;}
      if(iFHtEoiyia == true){iFHtEoiyia = false;}
      if(jSVPKDqRuV == true){jSVPKDqRuV = false;}
      if(VmxYAaZlIN == true){VmxYAaZlIN = false;}
      if(idntZPGeCB == true){idntZPGeCB = false;}
      if(UtCBlAieTi == true){UtCBlAieTi = false;}
      if(axlKrwHhtd == true){axlKrwHhtd = false;}
      if(PxpUrGdapt == true){PxpUrGdapt = false;}
      if(wMOsBbjwmz == true){wMOsBbjwmz = false;}
      if(ruRZllqdBc == true){ruRZllqdBc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YXCZGQQUYJ
{ 
  void qjKPChORUP()
  { 
      bool mTYWBRilwS = false;
      bool dBtSTRFoxg = false;
      bool YcIJzpXynq = false;
      bool dOTrnJYaBw = false;
      bool qRGkGwLAoM = false;
      bool bkjBAJLOWK = false;
      bool skxEoPhCeK = false;
      bool rdmBpHVWCD = false;
      bool dXJaPreRqd = false;
      bool yJEqCGTCuq = false;
      bool OJUeUxxiKs = false;
      bool mnMTfVaVow = false;
      bool kPLAMhZwyj = false;
      bool mTbKnUCdGR = false;
      bool uwHxqJxjKf = false;
      bool exMyGyxUSm = false;
      bool XAjZFSMCeL = false;
      bool TxPXBnHNJC = false;
      bool kolRFpHcDo = false;
      bool WhKSttLgqX = false;
      string pHEwGKPhme;
      string EUbIxIBGyK;
      string MezwMHrIDz;
      string OWBRzfdJTg;
      string WmEwajHqGm;
      string YHKXALHIiz;
      string RHemQhTKJR;
      string eqlQmZZDUc;
      string zBCPaGLcQn;
      string XUZUPPHRes;
      string QxhnIgVsjZ;
      string kEnGAQFPMJ;
      string VpsUtKRRBX;
      string SIXaLCTNHs;
      string kRspCSfTTy;
      string JrEUWaEMtx;
      string PDrLHcfMtx;
      string xrISYDwCRa;
      string dyxCOZDCEk;
      string yGTJdgZgiZ;
      if(pHEwGKPhme == QxhnIgVsjZ){mTYWBRilwS = true;}
      else if(QxhnIgVsjZ == pHEwGKPhme){OJUeUxxiKs = true;}
      if(EUbIxIBGyK == kEnGAQFPMJ){dBtSTRFoxg = true;}
      else if(kEnGAQFPMJ == EUbIxIBGyK){mnMTfVaVow = true;}
      if(MezwMHrIDz == VpsUtKRRBX){YcIJzpXynq = true;}
      else if(VpsUtKRRBX == MezwMHrIDz){kPLAMhZwyj = true;}
      if(OWBRzfdJTg == SIXaLCTNHs){dOTrnJYaBw = true;}
      else if(SIXaLCTNHs == OWBRzfdJTg){mTbKnUCdGR = true;}
      if(WmEwajHqGm == kRspCSfTTy){qRGkGwLAoM = true;}
      else if(kRspCSfTTy == WmEwajHqGm){uwHxqJxjKf = true;}
      if(YHKXALHIiz == JrEUWaEMtx){bkjBAJLOWK = true;}
      else if(JrEUWaEMtx == YHKXALHIiz){exMyGyxUSm = true;}
      if(RHemQhTKJR == PDrLHcfMtx){skxEoPhCeK = true;}
      else if(PDrLHcfMtx == RHemQhTKJR){XAjZFSMCeL = true;}
      if(eqlQmZZDUc == xrISYDwCRa){rdmBpHVWCD = true;}
      if(zBCPaGLcQn == dyxCOZDCEk){dXJaPreRqd = true;}
      if(XUZUPPHRes == yGTJdgZgiZ){yJEqCGTCuq = true;}
      while(xrISYDwCRa == eqlQmZZDUc){TxPXBnHNJC = true;}
      while(dyxCOZDCEk == dyxCOZDCEk){kolRFpHcDo = true;}
      while(yGTJdgZgiZ == yGTJdgZgiZ){WhKSttLgqX = true;}
      if(mTYWBRilwS == true){mTYWBRilwS = false;}
      if(dBtSTRFoxg == true){dBtSTRFoxg = false;}
      if(YcIJzpXynq == true){YcIJzpXynq = false;}
      if(dOTrnJYaBw == true){dOTrnJYaBw = false;}
      if(qRGkGwLAoM == true){qRGkGwLAoM = false;}
      if(bkjBAJLOWK == true){bkjBAJLOWK = false;}
      if(skxEoPhCeK == true){skxEoPhCeK = false;}
      if(rdmBpHVWCD == true){rdmBpHVWCD = false;}
      if(dXJaPreRqd == true){dXJaPreRqd = false;}
      if(yJEqCGTCuq == true){yJEqCGTCuq = false;}
      if(OJUeUxxiKs == true){OJUeUxxiKs = false;}
      if(mnMTfVaVow == true){mnMTfVaVow = false;}
      if(kPLAMhZwyj == true){kPLAMhZwyj = false;}
      if(mTbKnUCdGR == true){mTbKnUCdGR = false;}
      if(uwHxqJxjKf == true){uwHxqJxjKf = false;}
      if(exMyGyxUSm == true){exMyGyxUSm = false;}
      if(XAjZFSMCeL == true){XAjZFSMCeL = false;}
      if(TxPXBnHNJC == true){TxPXBnHNJC = false;}
      if(kolRFpHcDo == true){kolRFpHcDo = false;}
      if(WhKSttLgqX == true){WhKSttLgqX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LVCKTXPPOD
{ 
  void cbTrWdILtF()
  { 
      bool BIugUGMpco = false;
      bool PbuMEBfsYD = false;
      bool RjQrUBguhT = false;
      bool qNcuLCibmd = false;
      bool dljApyEErm = false;
      bool kpcuYQqDMS = false;
      bool YRIIxCyABC = false;
      bool SDGtYfAQBV = false;
      bool xcCuiBkgWt = false;
      bool KePTFMdbCm = false;
      bool AEDpTgihVr = false;
      bool QaBpVwONYw = false;
      bool RQcGqmnloM = false;
      bool BXNOVsZMaB = false;
      bool RCLddjdYxI = false;
      bool xQCGViawzf = false;
      bool sxrJqrMmUc = false;
      bool VClXdOFycG = false;
      bool JOnfOkVHrm = false;
      bool RcNuHUKBmk = false;
      string qQiEBOLAjS;
      string IglwHftLQu;
      string TLLlhbptuV;
      string tgugBaaxZf;
      string LOReDrbBRt;
      string zMQjweExWY;
      string YRFNYalEtg;
      string EwlkjFsgip;
      string AobBWgPLjW;
      string VdZAGtIDFb;
      string FWGkoCafzq;
      string kXNgXjoDqr;
      string LaUXLaWkdo;
      string woaGjchqLU;
      string GjLslyPrbW;
      string EFMNQeChZO;
      string foBJtuwHxu;
      string ByrWkaOalM;
      string KdJHkqcMpF;
      string ZAQwnQiByp;
      if(qQiEBOLAjS == FWGkoCafzq){BIugUGMpco = true;}
      else if(FWGkoCafzq == qQiEBOLAjS){AEDpTgihVr = true;}
      if(IglwHftLQu == kXNgXjoDqr){PbuMEBfsYD = true;}
      else if(kXNgXjoDqr == IglwHftLQu){QaBpVwONYw = true;}
      if(TLLlhbptuV == LaUXLaWkdo){RjQrUBguhT = true;}
      else if(LaUXLaWkdo == TLLlhbptuV){RQcGqmnloM = true;}
      if(tgugBaaxZf == woaGjchqLU){qNcuLCibmd = true;}
      else if(woaGjchqLU == tgugBaaxZf){BXNOVsZMaB = true;}
      if(LOReDrbBRt == GjLslyPrbW){dljApyEErm = true;}
      else if(GjLslyPrbW == LOReDrbBRt){RCLddjdYxI = true;}
      if(zMQjweExWY == EFMNQeChZO){kpcuYQqDMS = true;}
      else if(EFMNQeChZO == zMQjweExWY){xQCGViawzf = true;}
      if(YRFNYalEtg == foBJtuwHxu){YRIIxCyABC = true;}
      else if(foBJtuwHxu == YRFNYalEtg){sxrJqrMmUc = true;}
      if(EwlkjFsgip == ByrWkaOalM){SDGtYfAQBV = true;}
      if(AobBWgPLjW == KdJHkqcMpF){xcCuiBkgWt = true;}
      if(VdZAGtIDFb == ZAQwnQiByp){KePTFMdbCm = true;}
      while(ByrWkaOalM == EwlkjFsgip){VClXdOFycG = true;}
      while(KdJHkqcMpF == KdJHkqcMpF){JOnfOkVHrm = true;}
      while(ZAQwnQiByp == ZAQwnQiByp){RcNuHUKBmk = true;}
      if(BIugUGMpco == true){BIugUGMpco = false;}
      if(PbuMEBfsYD == true){PbuMEBfsYD = false;}
      if(RjQrUBguhT == true){RjQrUBguhT = false;}
      if(qNcuLCibmd == true){qNcuLCibmd = false;}
      if(dljApyEErm == true){dljApyEErm = false;}
      if(kpcuYQqDMS == true){kpcuYQqDMS = false;}
      if(YRIIxCyABC == true){YRIIxCyABC = false;}
      if(SDGtYfAQBV == true){SDGtYfAQBV = false;}
      if(xcCuiBkgWt == true){xcCuiBkgWt = false;}
      if(KePTFMdbCm == true){KePTFMdbCm = false;}
      if(AEDpTgihVr == true){AEDpTgihVr = false;}
      if(QaBpVwONYw == true){QaBpVwONYw = false;}
      if(RQcGqmnloM == true){RQcGqmnloM = false;}
      if(BXNOVsZMaB == true){BXNOVsZMaB = false;}
      if(RCLddjdYxI == true){RCLddjdYxI = false;}
      if(xQCGViawzf == true){xQCGViawzf = false;}
      if(sxrJqrMmUc == true){sxrJqrMmUc = false;}
      if(VClXdOFycG == true){VClXdOFycG = false;}
      if(JOnfOkVHrm == true){JOnfOkVHrm = false;}
      if(RcNuHUKBmk == true){RcNuHUKBmk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RVIJVWENWV
{ 
  void KmAtkkGBHq()
  { 
      bool MMVFfJKrYw = false;
      bool cYWZkyFRuI = false;
      bool HppAUybKVI = false;
      bool XAjNWLVLKT = false;
      bool ZScBMJAQiw = false;
      bool ScqDPVWVkg = false;
      bool gAVQYcoJDY = false;
      bool btHahnNnnK = false;
      bool yKaZotJfxA = false;
      bool nAZclZwMbi = false;
      bool UpNJTYUPVb = false;
      bool IigZiWYwad = false;
      bool TJMCjaTdoH = false;
      bool rBMEpHxRFQ = false;
      bool YsJVrFTAtP = false;
      bool AzkxPKdKYs = false;
      bool EqaNiGVcja = false;
      bool YHqKEZzpJe = false;
      bool HTjYGrPOne = false;
      bool dmrMLhSull = false;
      string YDErGRTtWG;
      string TUonDbpnKa;
      string mNFGaYBxYp;
      string hudOlGAayR;
      string UQnJIFxlwL;
      string KnrloKxyRh;
      string PVUfXXpaCx;
      string bOpsGVZuxU;
      string aOANftCrYa;
      string IBJPBzwHkj;
      string OWjzjuxzfS;
      string kCAwHAVHAd;
      string VyBaoZFZqH;
      string ZSJMGDeBcj;
      string wDLFpFBMIA;
      string cnHHOQUIJJ;
      string pWIYsSsnpD;
      string UTdPhRmwki;
      string YrQpdkKCyp;
      string iWqTtYtlMX;
      if(YDErGRTtWG == OWjzjuxzfS){MMVFfJKrYw = true;}
      else if(OWjzjuxzfS == YDErGRTtWG){UpNJTYUPVb = true;}
      if(TUonDbpnKa == kCAwHAVHAd){cYWZkyFRuI = true;}
      else if(kCAwHAVHAd == TUonDbpnKa){IigZiWYwad = true;}
      if(mNFGaYBxYp == VyBaoZFZqH){HppAUybKVI = true;}
      else if(VyBaoZFZqH == mNFGaYBxYp){TJMCjaTdoH = true;}
      if(hudOlGAayR == ZSJMGDeBcj){XAjNWLVLKT = true;}
      else if(ZSJMGDeBcj == hudOlGAayR){rBMEpHxRFQ = true;}
      if(UQnJIFxlwL == wDLFpFBMIA){ZScBMJAQiw = true;}
      else if(wDLFpFBMIA == UQnJIFxlwL){YsJVrFTAtP = true;}
      if(KnrloKxyRh == cnHHOQUIJJ){ScqDPVWVkg = true;}
      else if(cnHHOQUIJJ == KnrloKxyRh){AzkxPKdKYs = true;}
      if(PVUfXXpaCx == pWIYsSsnpD){gAVQYcoJDY = true;}
      else if(pWIYsSsnpD == PVUfXXpaCx){EqaNiGVcja = true;}
      if(bOpsGVZuxU == UTdPhRmwki){btHahnNnnK = true;}
      if(aOANftCrYa == YrQpdkKCyp){yKaZotJfxA = true;}
      if(IBJPBzwHkj == iWqTtYtlMX){nAZclZwMbi = true;}
      while(UTdPhRmwki == bOpsGVZuxU){YHqKEZzpJe = true;}
      while(YrQpdkKCyp == YrQpdkKCyp){HTjYGrPOne = true;}
      while(iWqTtYtlMX == iWqTtYtlMX){dmrMLhSull = true;}
      if(MMVFfJKrYw == true){MMVFfJKrYw = false;}
      if(cYWZkyFRuI == true){cYWZkyFRuI = false;}
      if(HppAUybKVI == true){HppAUybKVI = false;}
      if(XAjNWLVLKT == true){XAjNWLVLKT = false;}
      if(ZScBMJAQiw == true){ZScBMJAQiw = false;}
      if(ScqDPVWVkg == true){ScqDPVWVkg = false;}
      if(gAVQYcoJDY == true){gAVQYcoJDY = false;}
      if(btHahnNnnK == true){btHahnNnnK = false;}
      if(yKaZotJfxA == true){yKaZotJfxA = false;}
      if(nAZclZwMbi == true){nAZclZwMbi = false;}
      if(UpNJTYUPVb == true){UpNJTYUPVb = false;}
      if(IigZiWYwad == true){IigZiWYwad = false;}
      if(TJMCjaTdoH == true){TJMCjaTdoH = false;}
      if(rBMEpHxRFQ == true){rBMEpHxRFQ = false;}
      if(YsJVrFTAtP == true){YsJVrFTAtP = false;}
      if(AzkxPKdKYs == true){AzkxPKdKYs = false;}
      if(EqaNiGVcja == true){EqaNiGVcja = false;}
      if(YHqKEZzpJe == true){YHqKEZzpJe = false;}
      if(HTjYGrPOne == true){HTjYGrPOne = false;}
      if(dmrMLhSull == true){dmrMLhSull = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OUUQKGJYPW
{ 
  void wVMbyOgBEE()
  { 
      bool PNEDhQaXhg = false;
      bool rZIKCJzNsG = false;
      bool EcuPXcXutG = false;
      bool OmZVPPkNEZ = false;
      bool irMXglgkml = false;
      bool WXOjSmRofF = false;
      bool rfcbSEAmtl = false;
      bool XkJSWMPXhk = false;
      bool wmHHipYpCc = false;
      bool yugyhDOkFb = false;
      bool lspAOkNuMG = false;
      bool WsGuJFXUsb = false;
      bool fJjRnbEKkT = false;
      bool xeSGyCxGsy = false;
      bool ccdwGEnlob = false;
      bool esrcucJXMl = false;
      bool gCJsIqaAwH = false;
      bool HRatzDfmLj = false;
      bool mRVInEmoLV = false;
      bool rYtHQZSkmO = false;
      string RihiUgFHEe;
      string cWCnUoFUBO;
      string IqYnzKqAIo;
      string JOgdOeucmC;
      string wROsgOoLBQ;
      string KCndfZKsjK;
      string pEyPUNoXYo;
      string sbgzSqceGj;
      string VeyrdGaDyo;
      string UBrcLqSzYT;
      string YQmLWiUnLo;
      string xemznKGGkN;
      string llZjUqiEma;
      string XdGlLErlUu;
      string llqIqoOsnB;
      string jMNKglqCqe;
      string zPAjRTYBnj;
      string STkpbAtQsf;
      string cpQlqKPuFY;
      string MpupuVkHqW;
      if(RihiUgFHEe == YQmLWiUnLo){PNEDhQaXhg = true;}
      else if(YQmLWiUnLo == RihiUgFHEe){lspAOkNuMG = true;}
      if(cWCnUoFUBO == xemznKGGkN){rZIKCJzNsG = true;}
      else if(xemznKGGkN == cWCnUoFUBO){WsGuJFXUsb = true;}
      if(IqYnzKqAIo == llZjUqiEma){EcuPXcXutG = true;}
      else if(llZjUqiEma == IqYnzKqAIo){fJjRnbEKkT = true;}
      if(JOgdOeucmC == XdGlLErlUu){OmZVPPkNEZ = true;}
      else if(XdGlLErlUu == JOgdOeucmC){xeSGyCxGsy = true;}
      if(wROsgOoLBQ == llqIqoOsnB){irMXglgkml = true;}
      else if(llqIqoOsnB == wROsgOoLBQ){ccdwGEnlob = true;}
      if(KCndfZKsjK == jMNKglqCqe){WXOjSmRofF = true;}
      else if(jMNKglqCqe == KCndfZKsjK){esrcucJXMl = true;}
      if(pEyPUNoXYo == zPAjRTYBnj){rfcbSEAmtl = true;}
      else if(zPAjRTYBnj == pEyPUNoXYo){gCJsIqaAwH = true;}
      if(sbgzSqceGj == STkpbAtQsf){XkJSWMPXhk = true;}
      if(VeyrdGaDyo == cpQlqKPuFY){wmHHipYpCc = true;}
      if(UBrcLqSzYT == MpupuVkHqW){yugyhDOkFb = true;}
      while(STkpbAtQsf == sbgzSqceGj){HRatzDfmLj = true;}
      while(cpQlqKPuFY == cpQlqKPuFY){mRVInEmoLV = true;}
      while(MpupuVkHqW == MpupuVkHqW){rYtHQZSkmO = true;}
      if(PNEDhQaXhg == true){PNEDhQaXhg = false;}
      if(rZIKCJzNsG == true){rZIKCJzNsG = false;}
      if(EcuPXcXutG == true){EcuPXcXutG = false;}
      if(OmZVPPkNEZ == true){OmZVPPkNEZ = false;}
      if(irMXglgkml == true){irMXglgkml = false;}
      if(WXOjSmRofF == true){WXOjSmRofF = false;}
      if(rfcbSEAmtl == true){rfcbSEAmtl = false;}
      if(XkJSWMPXhk == true){XkJSWMPXhk = false;}
      if(wmHHipYpCc == true){wmHHipYpCc = false;}
      if(yugyhDOkFb == true){yugyhDOkFb = false;}
      if(lspAOkNuMG == true){lspAOkNuMG = false;}
      if(WsGuJFXUsb == true){WsGuJFXUsb = false;}
      if(fJjRnbEKkT == true){fJjRnbEKkT = false;}
      if(xeSGyCxGsy == true){xeSGyCxGsy = false;}
      if(ccdwGEnlob == true){ccdwGEnlob = false;}
      if(esrcucJXMl == true){esrcucJXMl = false;}
      if(gCJsIqaAwH == true){gCJsIqaAwH = false;}
      if(HRatzDfmLj == true){HRatzDfmLj = false;}
      if(mRVInEmoLV == true){mRVInEmoLV = false;}
      if(rYtHQZSkmO == true){rYtHQZSkmO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWVICWDXXX
{ 
  void uxYwelZlUn()
  { 
      bool GsHmpYOohN = false;
      bool llNRfnXyhK = false;
      bool AWbQJtkdVO = false;
      bool ldQeaZHqbU = false;
      bool maoalCwZIn = false;
      bool QuEqdiRpdw = false;
      bool njTSbIUhqG = false;
      bool gfVMWYgAdG = false;
      bool xLVgypZZBq = false;
      bool IQMfgDGVzd = false;
      bool gOiBHjYqTE = false;
      bool BQLXybOmUk = false;
      bool hugzyPTpeT = false;
      bool RLBAYibTZO = false;
      bool RhFwoqEogE = false;
      bool nTAOukhiDq = false;
      bool PiMAlpOLyP = false;
      bool AtMGTApjKG = false;
      bool LdIZfyKmFm = false;
      bool ArQiyhVFJy = false;
      string IEFBtWaCNV;
      string lGbqZUYCYf;
      string hOQjURWkfn;
      string UIjgOpfwHf;
      string MKqdOHiIPP;
      string rMUtUtnVfb;
      string ApVZAdWtbi;
      string ncurTXWlUN;
      string iNVPuHmpLU;
      string CKQefVnRdk;
      string jnffbPRcZx;
      string WCASslTGdr;
      string pghHgcMPMx;
      string jFIicuhpmf;
      string pKPOxAKxlt;
      string CgnktDFXyz;
      string DBQcMRtQpy;
      string DcSyCfQSKg;
      string SOdRtCQWoY;
      string oJqncntmCe;
      if(IEFBtWaCNV == jnffbPRcZx){GsHmpYOohN = true;}
      else if(jnffbPRcZx == IEFBtWaCNV){gOiBHjYqTE = true;}
      if(lGbqZUYCYf == WCASslTGdr){llNRfnXyhK = true;}
      else if(WCASslTGdr == lGbqZUYCYf){BQLXybOmUk = true;}
      if(hOQjURWkfn == pghHgcMPMx){AWbQJtkdVO = true;}
      else if(pghHgcMPMx == hOQjURWkfn){hugzyPTpeT = true;}
      if(UIjgOpfwHf == jFIicuhpmf){ldQeaZHqbU = true;}
      else if(jFIicuhpmf == UIjgOpfwHf){RLBAYibTZO = true;}
      if(MKqdOHiIPP == pKPOxAKxlt){maoalCwZIn = true;}
      else if(pKPOxAKxlt == MKqdOHiIPP){RhFwoqEogE = true;}
      if(rMUtUtnVfb == CgnktDFXyz){QuEqdiRpdw = true;}
      else if(CgnktDFXyz == rMUtUtnVfb){nTAOukhiDq = true;}
      if(ApVZAdWtbi == DBQcMRtQpy){njTSbIUhqG = true;}
      else if(DBQcMRtQpy == ApVZAdWtbi){PiMAlpOLyP = true;}
      if(ncurTXWlUN == DcSyCfQSKg){gfVMWYgAdG = true;}
      if(iNVPuHmpLU == SOdRtCQWoY){xLVgypZZBq = true;}
      if(CKQefVnRdk == oJqncntmCe){IQMfgDGVzd = true;}
      while(DcSyCfQSKg == ncurTXWlUN){AtMGTApjKG = true;}
      while(SOdRtCQWoY == SOdRtCQWoY){LdIZfyKmFm = true;}
      while(oJqncntmCe == oJqncntmCe){ArQiyhVFJy = true;}
      if(GsHmpYOohN == true){GsHmpYOohN = false;}
      if(llNRfnXyhK == true){llNRfnXyhK = false;}
      if(AWbQJtkdVO == true){AWbQJtkdVO = false;}
      if(ldQeaZHqbU == true){ldQeaZHqbU = false;}
      if(maoalCwZIn == true){maoalCwZIn = false;}
      if(QuEqdiRpdw == true){QuEqdiRpdw = false;}
      if(njTSbIUhqG == true){njTSbIUhqG = false;}
      if(gfVMWYgAdG == true){gfVMWYgAdG = false;}
      if(xLVgypZZBq == true){xLVgypZZBq = false;}
      if(IQMfgDGVzd == true){IQMfgDGVzd = false;}
      if(gOiBHjYqTE == true){gOiBHjYqTE = false;}
      if(BQLXybOmUk == true){BQLXybOmUk = false;}
      if(hugzyPTpeT == true){hugzyPTpeT = false;}
      if(RLBAYibTZO == true){RLBAYibTZO = false;}
      if(RhFwoqEogE == true){RhFwoqEogE = false;}
      if(nTAOukhiDq == true){nTAOukhiDq = false;}
      if(PiMAlpOLyP == true){PiMAlpOLyP = false;}
      if(AtMGTApjKG == true){AtMGTApjKG = false;}
      if(LdIZfyKmFm == true){LdIZfyKmFm = false;}
      if(ArQiyhVFJy == true){ArQiyhVFJy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRNITTIZJM
{ 
  void sRzzZIyqMn()
  { 
      bool IImOnfEFAH = false;
      bool TYNUxXwOCa = false;
      bool BcDQjoZqGX = false;
      bool oKknpiIYKb = false;
      bool IClAROWtEf = false;
      bool yNfHzeFVdz = false;
      bool FNycRInZdN = false;
      bool OWEaRzqDzV = false;
      bool SflZYbddoK = false;
      bool dltKVtDIhI = false;
      bool ZwPpRaIEoz = false;
      bool nBWHgZbXDp = false;
      bool dKjTicbsEX = false;
      bool uhUpuVPwIy = false;
      bool SZnoVbOmcw = false;
      bool SfEqdPMwGn = false;
      bool yOzREFgfML = false;
      bool KeOFXEVuxH = false;
      bool NoQIEPdcMf = false;
      bool ISpUADZWkQ = false;
      string fGLYfoRGKB;
      string CJgmtlQfTG;
      string McRKWLkYYC;
      string RfoSufMqMe;
      string kQGyAWwtCc;
      string ccPHuDnBBU;
      string DshHjWUNqN;
      string YZSnUuVTJA;
      string PpVwZnQgXq;
      string rLorariyOd;
      string BhCnDDKamA;
      string gUqAFMWkhu;
      string GnpzVMjaMc;
      string LXFfzgmhrW;
      string dosWKXUnmN;
      string UyQSXNrDSp;
      string SiNKnJPLBY;
      string YosKRQtSoy;
      string rumzHNHlHk;
      string njOCDtbihA;
      if(fGLYfoRGKB == BhCnDDKamA){IImOnfEFAH = true;}
      else if(BhCnDDKamA == fGLYfoRGKB){ZwPpRaIEoz = true;}
      if(CJgmtlQfTG == gUqAFMWkhu){TYNUxXwOCa = true;}
      else if(gUqAFMWkhu == CJgmtlQfTG){nBWHgZbXDp = true;}
      if(McRKWLkYYC == GnpzVMjaMc){BcDQjoZqGX = true;}
      else if(GnpzVMjaMc == McRKWLkYYC){dKjTicbsEX = true;}
      if(RfoSufMqMe == LXFfzgmhrW){oKknpiIYKb = true;}
      else if(LXFfzgmhrW == RfoSufMqMe){uhUpuVPwIy = true;}
      if(kQGyAWwtCc == dosWKXUnmN){IClAROWtEf = true;}
      else if(dosWKXUnmN == kQGyAWwtCc){SZnoVbOmcw = true;}
      if(ccPHuDnBBU == UyQSXNrDSp){yNfHzeFVdz = true;}
      else if(UyQSXNrDSp == ccPHuDnBBU){SfEqdPMwGn = true;}
      if(DshHjWUNqN == SiNKnJPLBY){FNycRInZdN = true;}
      else if(SiNKnJPLBY == DshHjWUNqN){yOzREFgfML = true;}
      if(YZSnUuVTJA == YosKRQtSoy){OWEaRzqDzV = true;}
      if(PpVwZnQgXq == rumzHNHlHk){SflZYbddoK = true;}
      if(rLorariyOd == njOCDtbihA){dltKVtDIhI = true;}
      while(YosKRQtSoy == YZSnUuVTJA){KeOFXEVuxH = true;}
      while(rumzHNHlHk == rumzHNHlHk){NoQIEPdcMf = true;}
      while(njOCDtbihA == njOCDtbihA){ISpUADZWkQ = true;}
      if(IImOnfEFAH == true){IImOnfEFAH = false;}
      if(TYNUxXwOCa == true){TYNUxXwOCa = false;}
      if(BcDQjoZqGX == true){BcDQjoZqGX = false;}
      if(oKknpiIYKb == true){oKknpiIYKb = false;}
      if(IClAROWtEf == true){IClAROWtEf = false;}
      if(yNfHzeFVdz == true){yNfHzeFVdz = false;}
      if(FNycRInZdN == true){FNycRInZdN = false;}
      if(OWEaRzqDzV == true){OWEaRzqDzV = false;}
      if(SflZYbddoK == true){SflZYbddoK = false;}
      if(dltKVtDIhI == true){dltKVtDIhI = false;}
      if(ZwPpRaIEoz == true){ZwPpRaIEoz = false;}
      if(nBWHgZbXDp == true){nBWHgZbXDp = false;}
      if(dKjTicbsEX == true){dKjTicbsEX = false;}
      if(uhUpuVPwIy == true){uhUpuVPwIy = false;}
      if(SZnoVbOmcw == true){SZnoVbOmcw = false;}
      if(SfEqdPMwGn == true){SfEqdPMwGn = false;}
      if(yOzREFgfML == true){yOzREFgfML = false;}
      if(KeOFXEVuxH == true){KeOFXEVuxH = false;}
      if(NoQIEPdcMf == true){NoQIEPdcMf = false;}
      if(ISpUADZWkQ == true){ISpUADZWkQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NGEYQPNWIA
{ 
  void yDMwfeLyYt()
  { 
      bool NddmHEsIAP = false;
      bool ugJkyMhNwy = false;
      bool bOoAtDzbNK = false;
      bool rjpaxAmUIe = false;
      bool EbCAAokRBH = false;
      bool VzxipyndrE = false;
      bool FQuoXKphmx = false;
      bool ZMFQszLozF = false;
      bool ShaGormHkz = false;
      bool MJcEZmfNco = false;
      bool yCdDgJtfop = false;
      bool lydmkXpoAe = false;
      bool XixnkQjAqG = false;
      bool TyLKGPDWYf = false;
      bool xGRtMNfoSB = false;
      bool xqNxRPFoSQ = false;
      bool YsniWnlSfV = false;
      bool TSPUgQQCbW = false;
      bool kthpJbkOrq = false;
      bool JOEIGDRiXY = false;
      string FBNxIyZUaO;
      string zcmoAQsfhA;
      string jUYPfgijya;
      string HJYuBsaIXN;
      string zsWfIgyMuf;
      string GKSZEkcyQa;
      string PpVAGoDrmH;
      string pjITBpxrGy;
      string hVnRTxqzqQ;
      string QbrwyJXWZT;
      string dGYnpVCzYN;
      string mjrRrsCDfJ;
      string yEBWqNqLUq;
      string RaSlUbwzby;
      string tracdfjaDE;
      string HUpPVYFCxb;
      string dpdguLRFwQ;
      string xCahPFdXsL;
      string dQIPjxjCQw;
      string VtCzTENsgR;
      if(FBNxIyZUaO == dGYnpVCzYN){NddmHEsIAP = true;}
      else if(dGYnpVCzYN == FBNxIyZUaO){yCdDgJtfop = true;}
      if(zcmoAQsfhA == mjrRrsCDfJ){ugJkyMhNwy = true;}
      else if(mjrRrsCDfJ == zcmoAQsfhA){lydmkXpoAe = true;}
      if(jUYPfgijya == yEBWqNqLUq){bOoAtDzbNK = true;}
      else if(yEBWqNqLUq == jUYPfgijya){XixnkQjAqG = true;}
      if(HJYuBsaIXN == RaSlUbwzby){rjpaxAmUIe = true;}
      else if(RaSlUbwzby == HJYuBsaIXN){TyLKGPDWYf = true;}
      if(zsWfIgyMuf == tracdfjaDE){EbCAAokRBH = true;}
      else if(tracdfjaDE == zsWfIgyMuf){xGRtMNfoSB = true;}
      if(GKSZEkcyQa == HUpPVYFCxb){VzxipyndrE = true;}
      else if(HUpPVYFCxb == GKSZEkcyQa){xqNxRPFoSQ = true;}
      if(PpVAGoDrmH == dpdguLRFwQ){FQuoXKphmx = true;}
      else if(dpdguLRFwQ == PpVAGoDrmH){YsniWnlSfV = true;}
      if(pjITBpxrGy == xCahPFdXsL){ZMFQszLozF = true;}
      if(hVnRTxqzqQ == dQIPjxjCQw){ShaGormHkz = true;}
      if(QbrwyJXWZT == VtCzTENsgR){MJcEZmfNco = true;}
      while(xCahPFdXsL == pjITBpxrGy){TSPUgQQCbW = true;}
      while(dQIPjxjCQw == dQIPjxjCQw){kthpJbkOrq = true;}
      while(VtCzTENsgR == VtCzTENsgR){JOEIGDRiXY = true;}
      if(NddmHEsIAP == true){NddmHEsIAP = false;}
      if(ugJkyMhNwy == true){ugJkyMhNwy = false;}
      if(bOoAtDzbNK == true){bOoAtDzbNK = false;}
      if(rjpaxAmUIe == true){rjpaxAmUIe = false;}
      if(EbCAAokRBH == true){EbCAAokRBH = false;}
      if(VzxipyndrE == true){VzxipyndrE = false;}
      if(FQuoXKphmx == true){FQuoXKphmx = false;}
      if(ZMFQszLozF == true){ZMFQszLozF = false;}
      if(ShaGormHkz == true){ShaGormHkz = false;}
      if(MJcEZmfNco == true){MJcEZmfNco = false;}
      if(yCdDgJtfop == true){yCdDgJtfop = false;}
      if(lydmkXpoAe == true){lydmkXpoAe = false;}
      if(XixnkQjAqG == true){XixnkQjAqG = false;}
      if(TyLKGPDWYf == true){TyLKGPDWYf = false;}
      if(xGRtMNfoSB == true){xGRtMNfoSB = false;}
      if(xqNxRPFoSQ == true){xqNxRPFoSQ = false;}
      if(YsniWnlSfV == true){YsniWnlSfV = false;}
      if(TSPUgQQCbW == true){TSPUgQQCbW = false;}
      if(kthpJbkOrq == true){kthpJbkOrq = false;}
      if(JOEIGDRiXY == true){JOEIGDRiXY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RVBXEXQCQV
{ 
  void twoxTHSRNZ()
  { 
      bool QWAIUcaYyT = false;
      bool VkceqGHeDu = false;
      bool OywkAxBiPF = false;
      bool jTNjahraWa = false;
      bool swQlEGkLVM = false;
      bool ICkwUSaOIX = false;
      bool bqJrjBWrEJ = false;
      bool OfHbCRhKgt = false;
      bool LoNDxgiQOI = false;
      bool GcSzzBmXBC = false;
      bool irHLxbuIsD = false;
      bool jPhNLldFtD = false;
      bool SFduClMIbB = false;
      bool eKIdLShBFV = false;
      bool lZXLYptEnN = false;
      bool WgcyjcOLJL = false;
      bool OmfqXZHECr = false;
      bool DbAYQrhSWL = false;
      bool qHTOdxgKth = false;
      bool EVqtGytfmz = false;
      string OTdDQUYuTi;
      string HDKBDJEnEE;
      string hOqjDJBFHz;
      string VgTkgEMaeY;
      string yPcKiRaFtX;
      string fkcoYzcsAG;
      string TTnUNaiYUz;
      string xdIeFSlfAl;
      string hwKiTjDeMg;
      string bSZXFebIxI;
      string hBjuaCbxiF;
      string NwsOXXIEAc;
      string WELnXdDjZa;
      string pciqDgLPIR;
      string HFwGTeYLAg;
      string VWHTkdowXw;
      string yrXHPjNCKq;
      string MswiVRHETr;
      string ErjrETVOFZ;
      string qOqMSPhnqj;
      if(OTdDQUYuTi == hBjuaCbxiF){QWAIUcaYyT = true;}
      else if(hBjuaCbxiF == OTdDQUYuTi){irHLxbuIsD = true;}
      if(HDKBDJEnEE == NwsOXXIEAc){VkceqGHeDu = true;}
      else if(NwsOXXIEAc == HDKBDJEnEE){jPhNLldFtD = true;}
      if(hOqjDJBFHz == WELnXdDjZa){OywkAxBiPF = true;}
      else if(WELnXdDjZa == hOqjDJBFHz){SFduClMIbB = true;}
      if(VgTkgEMaeY == pciqDgLPIR){jTNjahraWa = true;}
      else if(pciqDgLPIR == VgTkgEMaeY){eKIdLShBFV = true;}
      if(yPcKiRaFtX == HFwGTeYLAg){swQlEGkLVM = true;}
      else if(HFwGTeYLAg == yPcKiRaFtX){lZXLYptEnN = true;}
      if(fkcoYzcsAG == VWHTkdowXw){ICkwUSaOIX = true;}
      else if(VWHTkdowXw == fkcoYzcsAG){WgcyjcOLJL = true;}
      if(TTnUNaiYUz == yrXHPjNCKq){bqJrjBWrEJ = true;}
      else if(yrXHPjNCKq == TTnUNaiYUz){OmfqXZHECr = true;}
      if(xdIeFSlfAl == MswiVRHETr){OfHbCRhKgt = true;}
      if(hwKiTjDeMg == ErjrETVOFZ){LoNDxgiQOI = true;}
      if(bSZXFebIxI == qOqMSPhnqj){GcSzzBmXBC = true;}
      while(MswiVRHETr == xdIeFSlfAl){DbAYQrhSWL = true;}
      while(ErjrETVOFZ == ErjrETVOFZ){qHTOdxgKth = true;}
      while(qOqMSPhnqj == qOqMSPhnqj){EVqtGytfmz = true;}
      if(QWAIUcaYyT == true){QWAIUcaYyT = false;}
      if(VkceqGHeDu == true){VkceqGHeDu = false;}
      if(OywkAxBiPF == true){OywkAxBiPF = false;}
      if(jTNjahraWa == true){jTNjahraWa = false;}
      if(swQlEGkLVM == true){swQlEGkLVM = false;}
      if(ICkwUSaOIX == true){ICkwUSaOIX = false;}
      if(bqJrjBWrEJ == true){bqJrjBWrEJ = false;}
      if(OfHbCRhKgt == true){OfHbCRhKgt = false;}
      if(LoNDxgiQOI == true){LoNDxgiQOI = false;}
      if(GcSzzBmXBC == true){GcSzzBmXBC = false;}
      if(irHLxbuIsD == true){irHLxbuIsD = false;}
      if(jPhNLldFtD == true){jPhNLldFtD = false;}
      if(SFduClMIbB == true){SFduClMIbB = false;}
      if(eKIdLShBFV == true){eKIdLShBFV = false;}
      if(lZXLYptEnN == true){lZXLYptEnN = false;}
      if(WgcyjcOLJL == true){WgcyjcOLJL = false;}
      if(OmfqXZHECr == true){OmfqXZHECr = false;}
      if(DbAYQrhSWL == true){DbAYQrhSWL = false;}
      if(qHTOdxgKth == true){qHTOdxgKth = false;}
      if(EVqtGytfmz == true){EVqtGytfmz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LXMVKLTANL
{ 
  void EDCiAoXkbk()
  { 
      bool OBcFaiyXKL = false;
      bool FJfLwslxOk = false;
      bool EwYVsmdOjr = false;
      bool hhJnfPBysf = false;
      bool mFGcFrLdwl = false;
      bool FdMcYRbHLn = false;
      bool EinRdWAqeg = false;
      bool rnDiyyowQB = false;
      bool bARxmDUfPO = false;
      bool mslFaDQozh = false;
      bool rTyPtQZdeZ = false;
      bool cfpKLERpeZ = false;
      bool BTbQsyByHt = false;
      bool hAwhJIBCDV = false;
      bool cqAokGCatW = false;
      bool lZJYgXqhVu = false;
      bool PbVjrcjIBD = false;
      bool COmJxJSmem = false;
      bool uZEkIHpXAk = false;
      bool QTfIGBUQwI = false;
      string bXEaomPhIs;
      string cGrcVQiRbs;
      string zFbxLhtaRc;
      string BlkfjxuekW;
      string IkiEODFXBQ;
      string PZzhcWwGOG;
      string soPerpVMsX;
      string VEgFkNVWhI;
      string bVYBNamDCN;
      string BnPddSUELX;
      string hsecuLsswP;
      string AYXGdWPOQR;
      string DRKfWgnDbR;
      string rRLKZiqwGC;
      string hsGlMbPJzG;
      string CGmtUPhzGN;
      string WpRdWiNNft;
      string eTHOjJKYSt;
      string QdDUOldRoK;
      string BroseqbbOd;
      if(bXEaomPhIs == hsecuLsswP){OBcFaiyXKL = true;}
      else if(hsecuLsswP == bXEaomPhIs){rTyPtQZdeZ = true;}
      if(cGrcVQiRbs == AYXGdWPOQR){FJfLwslxOk = true;}
      else if(AYXGdWPOQR == cGrcVQiRbs){cfpKLERpeZ = true;}
      if(zFbxLhtaRc == DRKfWgnDbR){EwYVsmdOjr = true;}
      else if(DRKfWgnDbR == zFbxLhtaRc){BTbQsyByHt = true;}
      if(BlkfjxuekW == rRLKZiqwGC){hhJnfPBysf = true;}
      else if(rRLKZiqwGC == BlkfjxuekW){hAwhJIBCDV = true;}
      if(IkiEODFXBQ == hsGlMbPJzG){mFGcFrLdwl = true;}
      else if(hsGlMbPJzG == IkiEODFXBQ){cqAokGCatW = true;}
      if(PZzhcWwGOG == CGmtUPhzGN){FdMcYRbHLn = true;}
      else if(CGmtUPhzGN == PZzhcWwGOG){lZJYgXqhVu = true;}
      if(soPerpVMsX == WpRdWiNNft){EinRdWAqeg = true;}
      else if(WpRdWiNNft == soPerpVMsX){PbVjrcjIBD = true;}
      if(VEgFkNVWhI == eTHOjJKYSt){rnDiyyowQB = true;}
      if(bVYBNamDCN == QdDUOldRoK){bARxmDUfPO = true;}
      if(BnPddSUELX == BroseqbbOd){mslFaDQozh = true;}
      while(eTHOjJKYSt == VEgFkNVWhI){COmJxJSmem = true;}
      while(QdDUOldRoK == QdDUOldRoK){uZEkIHpXAk = true;}
      while(BroseqbbOd == BroseqbbOd){QTfIGBUQwI = true;}
      if(OBcFaiyXKL == true){OBcFaiyXKL = false;}
      if(FJfLwslxOk == true){FJfLwslxOk = false;}
      if(EwYVsmdOjr == true){EwYVsmdOjr = false;}
      if(hhJnfPBysf == true){hhJnfPBysf = false;}
      if(mFGcFrLdwl == true){mFGcFrLdwl = false;}
      if(FdMcYRbHLn == true){FdMcYRbHLn = false;}
      if(EinRdWAqeg == true){EinRdWAqeg = false;}
      if(rnDiyyowQB == true){rnDiyyowQB = false;}
      if(bARxmDUfPO == true){bARxmDUfPO = false;}
      if(mslFaDQozh == true){mslFaDQozh = false;}
      if(rTyPtQZdeZ == true){rTyPtQZdeZ = false;}
      if(cfpKLERpeZ == true){cfpKLERpeZ = false;}
      if(BTbQsyByHt == true){BTbQsyByHt = false;}
      if(hAwhJIBCDV == true){hAwhJIBCDV = false;}
      if(cqAokGCatW == true){cqAokGCatW = false;}
      if(lZJYgXqhVu == true){lZJYgXqhVu = false;}
      if(PbVjrcjIBD == true){PbVjrcjIBD = false;}
      if(COmJxJSmem == true){COmJxJSmem = false;}
      if(uZEkIHpXAk == true){uZEkIHpXAk = false;}
      if(QTfIGBUQwI == true){QTfIGBUQwI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AYXAPEGUSQ
{ 
  void iHSLNsEdDF()
  { 
      bool pxTScijQuW = false;
      bool dQlYToJeUk = false;
      bool fPIcBTwjpM = false;
      bool NpQFCPopjB = false;
      bool HetgKAYFNp = false;
      bool pamyXZoqQI = false;
      bool lAahJnzfWE = false;
      bool zSuTdAVaSB = false;
      bool tqVAWmCRhb = false;
      bool ZyYaOGDLWV = false;
      bool AriJpWeTUW = false;
      bool EOYONueaLW = false;
      bool lgyteBsTEW = false;
      bool xJDwBCHLJz = false;
      bool HhxLXLZJNT = false;
      bool bcAAjStoeo = false;
      bool cLPyZuLbNL = false;
      bool mSQLPDjlVS = false;
      bool ajGktTIDMh = false;
      bool HSgUVuSykc = false;
      string CVwKTgbVDj;
      string JSuxfUamhm;
      string VYgkVBFARh;
      string ZirrSpdKFU;
      string JoGwhOkOxw;
      string KuYdFcoLoR;
      string baDVJaZCdp;
      string qQhMdfSkCG;
      string QpDUXeJOmo;
      string ASUmrhkjlH;
      string nhjGFtNLAY;
      string KEIiBkXhyd;
      string QLPnoXutTu;
      string uhyuRiGwPc;
      string RxNNewKlkH;
      string KClHpcRuRg;
      string ySrFdbGMRS;
      string eaSUMSyBJr;
      string MJJMjrwpEn;
      string QKehezFIjD;
      if(CVwKTgbVDj == nhjGFtNLAY){pxTScijQuW = true;}
      else if(nhjGFtNLAY == CVwKTgbVDj){AriJpWeTUW = true;}
      if(JSuxfUamhm == KEIiBkXhyd){dQlYToJeUk = true;}
      else if(KEIiBkXhyd == JSuxfUamhm){EOYONueaLW = true;}
      if(VYgkVBFARh == QLPnoXutTu){fPIcBTwjpM = true;}
      else if(QLPnoXutTu == VYgkVBFARh){lgyteBsTEW = true;}
      if(ZirrSpdKFU == uhyuRiGwPc){NpQFCPopjB = true;}
      else if(uhyuRiGwPc == ZirrSpdKFU){xJDwBCHLJz = true;}
      if(JoGwhOkOxw == RxNNewKlkH){HetgKAYFNp = true;}
      else if(RxNNewKlkH == JoGwhOkOxw){HhxLXLZJNT = true;}
      if(KuYdFcoLoR == KClHpcRuRg){pamyXZoqQI = true;}
      else if(KClHpcRuRg == KuYdFcoLoR){bcAAjStoeo = true;}
      if(baDVJaZCdp == ySrFdbGMRS){lAahJnzfWE = true;}
      else if(ySrFdbGMRS == baDVJaZCdp){cLPyZuLbNL = true;}
      if(qQhMdfSkCG == eaSUMSyBJr){zSuTdAVaSB = true;}
      if(QpDUXeJOmo == MJJMjrwpEn){tqVAWmCRhb = true;}
      if(ASUmrhkjlH == QKehezFIjD){ZyYaOGDLWV = true;}
      while(eaSUMSyBJr == qQhMdfSkCG){mSQLPDjlVS = true;}
      while(MJJMjrwpEn == MJJMjrwpEn){ajGktTIDMh = true;}
      while(QKehezFIjD == QKehezFIjD){HSgUVuSykc = true;}
      if(pxTScijQuW == true){pxTScijQuW = false;}
      if(dQlYToJeUk == true){dQlYToJeUk = false;}
      if(fPIcBTwjpM == true){fPIcBTwjpM = false;}
      if(NpQFCPopjB == true){NpQFCPopjB = false;}
      if(HetgKAYFNp == true){HetgKAYFNp = false;}
      if(pamyXZoqQI == true){pamyXZoqQI = false;}
      if(lAahJnzfWE == true){lAahJnzfWE = false;}
      if(zSuTdAVaSB == true){zSuTdAVaSB = false;}
      if(tqVAWmCRhb == true){tqVAWmCRhb = false;}
      if(ZyYaOGDLWV == true){ZyYaOGDLWV = false;}
      if(AriJpWeTUW == true){AriJpWeTUW = false;}
      if(EOYONueaLW == true){EOYONueaLW = false;}
      if(lgyteBsTEW == true){lgyteBsTEW = false;}
      if(xJDwBCHLJz == true){xJDwBCHLJz = false;}
      if(HhxLXLZJNT == true){HhxLXLZJNT = false;}
      if(bcAAjStoeo == true){bcAAjStoeo = false;}
      if(cLPyZuLbNL == true){cLPyZuLbNL = false;}
      if(mSQLPDjlVS == true){mSQLPDjlVS = false;}
      if(ajGktTIDMh == true){ajGktTIDMh = false;}
      if(HSgUVuSykc == true){HSgUVuSykc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PEGVTJXZLW
{ 
  void GDlcJDSaNL()
  { 
      bool UGokGyIaIF = false;
      bool kuqirnZlFP = false;
      bool KMkidmWWxB = false;
      bool IRueMTZAxi = false;
      bool TfwufOGaio = false;
      bool nlBxIHVFGS = false;
      bool bkcHwSzMVX = false;
      bool NZoWwdQpDP = false;
      bool funIMVPyVF = false;
      bool yUsdHiDoyM = false;
      bool OtEKbNxeBe = false;
      bool qeBqlfwUtZ = false;
      bool CBqQZrfLPM = false;
      bool abqpBlqcgy = false;
      bool YkwpOSSCra = false;
      bool lhtXKMDnki = false;
      bool hlPnEPnKoA = false;
      bool oTnuBRFACH = false;
      bool ZdTnargTfo = false;
      bool iCrxQmVHly = false;
      string ZhEsnZLcWn;
      string wImFcCdBVu;
      string GdrFHAkxDX;
      string CzrpIYQFPH;
      string zXJzgyQWnX;
      string gHzwJuoylm;
      string nOYykwQwwD;
      string kXlOwhTrYJ;
      string jOJfpuzugM;
      string jSSbSjzKOj;
      string gUZjlIUkza;
      string bwZcDZFrIo;
      string wVPjTSFJuM;
      string iJdnbPnYtg;
      string ZOuFkmrpYr;
      string eGCYmLFpPS;
      string DLomrRSkAn;
      string lfyaPhZJyg;
      string aPkDhbHFAQ;
      string JyJacOYHNT;
      if(ZhEsnZLcWn == gUZjlIUkza){UGokGyIaIF = true;}
      else if(gUZjlIUkza == ZhEsnZLcWn){OtEKbNxeBe = true;}
      if(wImFcCdBVu == bwZcDZFrIo){kuqirnZlFP = true;}
      else if(bwZcDZFrIo == wImFcCdBVu){qeBqlfwUtZ = true;}
      if(GdrFHAkxDX == wVPjTSFJuM){KMkidmWWxB = true;}
      else if(wVPjTSFJuM == GdrFHAkxDX){CBqQZrfLPM = true;}
      if(CzrpIYQFPH == iJdnbPnYtg){IRueMTZAxi = true;}
      else if(iJdnbPnYtg == CzrpIYQFPH){abqpBlqcgy = true;}
      if(zXJzgyQWnX == ZOuFkmrpYr){TfwufOGaio = true;}
      else if(ZOuFkmrpYr == zXJzgyQWnX){YkwpOSSCra = true;}
      if(gHzwJuoylm == eGCYmLFpPS){nlBxIHVFGS = true;}
      else if(eGCYmLFpPS == gHzwJuoylm){lhtXKMDnki = true;}
      if(nOYykwQwwD == DLomrRSkAn){bkcHwSzMVX = true;}
      else if(DLomrRSkAn == nOYykwQwwD){hlPnEPnKoA = true;}
      if(kXlOwhTrYJ == lfyaPhZJyg){NZoWwdQpDP = true;}
      if(jOJfpuzugM == aPkDhbHFAQ){funIMVPyVF = true;}
      if(jSSbSjzKOj == JyJacOYHNT){yUsdHiDoyM = true;}
      while(lfyaPhZJyg == kXlOwhTrYJ){oTnuBRFACH = true;}
      while(aPkDhbHFAQ == aPkDhbHFAQ){ZdTnargTfo = true;}
      while(JyJacOYHNT == JyJacOYHNT){iCrxQmVHly = true;}
      if(UGokGyIaIF == true){UGokGyIaIF = false;}
      if(kuqirnZlFP == true){kuqirnZlFP = false;}
      if(KMkidmWWxB == true){KMkidmWWxB = false;}
      if(IRueMTZAxi == true){IRueMTZAxi = false;}
      if(TfwufOGaio == true){TfwufOGaio = false;}
      if(nlBxIHVFGS == true){nlBxIHVFGS = false;}
      if(bkcHwSzMVX == true){bkcHwSzMVX = false;}
      if(NZoWwdQpDP == true){NZoWwdQpDP = false;}
      if(funIMVPyVF == true){funIMVPyVF = false;}
      if(yUsdHiDoyM == true){yUsdHiDoyM = false;}
      if(OtEKbNxeBe == true){OtEKbNxeBe = false;}
      if(qeBqlfwUtZ == true){qeBqlfwUtZ = false;}
      if(CBqQZrfLPM == true){CBqQZrfLPM = false;}
      if(abqpBlqcgy == true){abqpBlqcgy = false;}
      if(YkwpOSSCra == true){YkwpOSSCra = false;}
      if(lhtXKMDnki == true){lhtXKMDnki = false;}
      if(hlPnEPnKoA == true){hlPnEPnKoA = false;}
      if(oTnuBRFACH == true){oTnuBRFACH = false;}
      if(ZdTnargTfo == true){ZdTnargTfo = false;}
      if(iCrxQmVHly == true){iCrxQmVHly = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WEHEGJQGZU
{ 
  void XCZVwABZEW()
  { 
      bool PywuUxZQnM = false;
      bool PyjpgQymPP = false;
      bool bFhLuKOzCP = false;
      bool JWfupMywUA = false;
      bool suFFPVZtez = false;
      bool rxhPfKQjAK = false;
      bool iZOXDrRnAT = false;
      bool SCROVfzbwY = false;
      bool jTUCXLoPOf = false;
      bool wNwKRTggCX = false;
      bool EltKgpfStz = false;
      bool KonaZOFLAq = false;
      bool CBYUXEFHxC = false;
      bool zSZXUyZJVg = false;
      bool fWVPUHYUkC = false;
      bool OVgKUDMYlb = false;
      bool kXUrArOQGa = false;
      bool ouoSLfeJzQ = false;
      bool fjVtnclPDR = false;
      bool lAWswHBdOc = false;
      string suJulWScQq;
      string xIenufRTzf;
      string qcdoEdQnAx;
      string aQFBBVtlMN;
      string HgzCxVOcpp;
      string ZztiyQRTpI;
      string FdcSQfDclZ;
      string keGlYKdbrh;
      string PnyKWaWWCj;
      string EZwDHcEfkR;
      string RkpQEtsIJn;
      string moaHsRfRuo;
      string JgaCUKiCeu;
      string FxpaPdxgFb;
      string hOMOxOznKo;
      string wljwIkKnws;
      string LpcOiozAqO;
      string UzMSHuUMEF;
      string LurpySMtSe;
      string TJkMQqkxfI;
      if(suJulWScQq == RkpQEtsIJn){PywuUxZQnM = true;}
      else if(RkpQEtsIJn == suJulWScQq){EltKgpfStz = true;}
      if(xIenufRTzf == moaHsRfRuo){PyjpgQymPP = true;}
      else if(moaHsRfRuo == xIenufRTzf){KonaZOFLAq = true;}
      if(qcdoEdQnAx == JgaCUKiCeu){bFhLuKOzCP = true;}
      else if(JgaCUKiCeu == qcdoEdQnAx){CBYUXEFHxC = true;}
      if(aQFBBVtlMN == FxpaPdxgFb){JWfupMywUA = true;}
      else if(FxpaPdxgFb == aQFBBVtlMN){zSZXUyZJVg = true;}
      if(HgzCxVOcpp == hOMOxOznKo){suFFPVZtez = true;}
      else if(hOMOxOznKo == HgzCxVOcpp){fWVPUHYUkC = true;}
      if(ZztiyQRTpI == wljwIkKnws){rxhPfKQjAK = true;}
      else if(wljwIkKnws == ZztiyQRTpI){OVgKUDMYlb = true;}
      if(FdcSQfDclZ == LpcOiozAqO){iZOXDrRnAT = true;}
      else if(LpcOiozAqO == FdcSQfDclZ){kXUrArOQGa = true;}
      if(keGlYKdbrh == UzMSHuUMEF){SCROVfzbwY = true;}
      if(PnyKWaWWCj == LurpySMtSe){jTUCXLoPOf = true;}
      if(EZwDHcEfkR == TJkMQqkxfI){wNwKRTggCX = true;}
      while(UzMSHuUMEF == keGlYKdbrh){ouoSLfeJzQ = true;}
      while(LurpySMtSe == LurpySMtSe){fjVtnclPDR = true;}
      while(TJkMQqkxfI == TJkMQqkxfI){lAWswHBdOc = true;}
      if(PywuUxZQnM == true){PywuUxZQnM = false;}
      if(PyjpgQymPP == true){PyjpgQymPP = false;}
      if(bFhLuKOzCP == true){bFhLuKOzCP = false;}
      if(JWfupMywUA == true){JWfupMywUA = false;}
      if(suFFPVZtez == true){suFFPVZtez = false;}
      if(rxhPfKQjAK == true){rxhPfKQjAK = false;}
      if(iZOXDrRnAT == true){iZOXDrRnAT = false;}
      if(SCROVfzbwY == true){SCROVfzbwY = false;}
      if(jTUCXLoPOf == true){jTUCXLoPOf = false;}
      if(wNwKRTggCX == true){wNwKRTggCX = false;}
      if(EltKgpfStz == true){EltKgpfStz = false;}
      if(KonaZOFLAq == true){KonaZOFLAq = false;}
      if(CBYUXEFHxC == true){CBYUXEFHxC = false;}
      if(zSZXUyZJVg == true){zSZXUyZJVg = false;}
      if(fWVPUHYUkC == true){fWVPUHYUkC = false;}
      if(OVgKUDMYlb == true){OVgKUDMYlb = false;}
      if(kXUrArOQGa == true){kXUrArOQGa = false;}
      if(ouoSLfeJzQ == true){ouoSLfeJzQ = false;}
      if(fjVtnclPDR == true){fjVtnclPDR = false;}
      if(lAWswHBdOc == true){lAWswHBdOc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OIYZNGAGNK
{ 
  void tjtUtckQCH()
  { 
      bool ZbYowBwTpl = false;
      bool GbLToYaqqr = false;
      bool laLQWVPHut = false;
      bool qbYLnauioW = false;
      bool FWcViNtPCp = false;
      bool NwFEbyPHRa = false;
      bool koYwueCAeO = false;
      bool dqBUmPxphI = false;
      bool azFEguVTio = false;
      bool LmQOkPygZD = false;
      bool KtknMVtkRM = false;
      bool BYZIzljTPz = false;
      bool JiQoCpZliX = false;
      bool QQPdygOQqK = false;
      bool AjCWnlNHPy = false;
      bool fdQatbcukW = false;
      bool uHBtujJwKR = false;
      bool XScEyYgsAQ = false;
      bool cSWkqmzoiW = false;
      bool ESfTPsiHbE = false;
      string CfcALVpRYp;
      string rNILSFgcKK;
      string XlJykLFoFD;
      string KrdJFdSXBI;
      string TsSYLzLJGd;
      string CzoeXQWeOz;
      string PBLUfzjzGo;
      string mJaCqeSkll;
      string zwibBKDzko;
      string GnIBrSgysM;
      string PMDQqsYmms;
      string xlrczTRjTU;
      string ujORiyAZJY;
      string yUrYVmrRjI;
      string lQLrqTufBX;
      string AwdXQeylhr;
      string sycOtctTHM;
      string bzzKheYVZO;
      string CTXlXBpTHp;
      string oGjrPnmwxO;
      if(CfcALVpRYp == PMDQqsYmms){ZbYowBwTpl = true;}
      else if(PMDQqsYmms == CfcALVpRYp){KtknMVtkRM = true;}
      if(rNILSFgcKK == xlrczTRjTU){GbLToYaqqr = true;}
      else if(xlrczTRjTU == rNILSFgcKK){BYZIzljTPz = true;}
      if(XlJykLFoFD == ujORiyAZJY){laLQWVPHut = true;}
      else if(ujORiyAZJY == XlJykLFoFD){JiQoCpZliX = true;}
      if(KrdJFdSXBI == yUrYVmrRjI){qbYLnauioW = true;}
      else if(yUrYVmrRjI == KrdJFdSXBI){QQPdygOQqK = true;}
      if(TsSYLzLJGd == lQLrqTufBX){FWcViNtPCp = true;}
      else if(lQLrqTufBX == TsSYLzLJGd){AjCWnlNHPy = true;}
      if(CzoeXQWeOz == AwdXQeylhr){NwFEbyPHRa = true;}
      else if(AwdXQeylhr == CzoeXQWeOz){fdQatbcukW = true;}
      if(PBLUfzjzGo == sycOtctTHM){koYwueCAeO = true;}
      else if(sycOtctTHM == PBLUfzjzGo){uHBtujJwKR = true;}
      if(mJaCqeSkll == bzzKheYVZO){dqBUmPxphI = true;}
      if(zwibBKDzko == CTXlXBpTHp){azFEguVTio = true;}
      if(GnIBrSgysM == oGjrPnmwxO){LmQOkPygZD = true;}
      while(bzzKheYVZO == mJaCqeSkll){XScEyYgsAQ = true;}
      while(CTXlXBpTHp == CTXlXBpTHp){cSWkqmzoiW = true;}
      while(oGjrPnmwxO == oGjrPnmwxO){ESfTPsiHbE = true;}
      if(ZbYowBwTpl == true){ZbYowBwTpl = false;}
      if(GbLToYaqqr == true){GbLToYaqqr = false;}
      if(laLQWVPHut == true){laLQWVPHut = false;}
      if(qbYLnauioW == true){qbYLnauioW = false;}
      if(FWcViNtPCp == true){FWcViNtPCp = false;}
      if(NwFEbyPHRa == true){NwFEbyPHRa = false;}
      if(koYwueCAeO == true){koYwueCAeO = false;}
      if(dqBUmPxphI == true){dqBUmPxphI = false;}
      if(azFEguVTio == true){azFEguVTio = false;}
      if(LmQOkPygZD == true){LmQOkPygZD = false;}
      if(KtknMVtkRM == true){KtknMVtkRM = false;}
      if(BYZIzljTPz == true){BYZIzljTPz = false;}
      if(JiQoCpZliX == true){JiQoCpZliX = false;}
      if(QQPdygOQqK == true){QQPdygOQqK = false;}
      if(AjCWnlNHPy == true){AjCWnlNHPy = false;}
      if(fdQatbcukW == true){fdQatbcukW = false;}
      if(uHBtujJwKR == true){uHBtujJwKR = false;}
      if(XScEyYgsAQ == true){XScEyYgsAQ = false;}
      if(cSWkqmzoiW == true){cSWkqmzoiW = false;}
      if(ESfTPsiHbE == true){ESfTPsiHbE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHUXKXRVQH
{ 
  void QNnaYoZxRa()
  { 
      bool oNENDcpnUb = false;
      bool TryzEceixZ = false;
      bool HLVDonxzBs = false;
      bool UWioHUKjze = false;
      bool AQzmMNKmDL = false;
      bool mGWLIcrBXO = false;
      bool eqlbHxJIqi = false;
      bool StjRZqMipa = false;
      bool dJupFNzWge = false;
      bool cJLkzJdWeP = false;
      bool DBwTsrWEkR = false;
      bool PIKxjVuwVt = false;
      bool xlbLGJiySQ = false;
      bool MpEaWcNbxN = false;
      bool ptlPPUyOBd = false;
      bool NhAkRRZkMi = false;
      bool JXlUFZEjZG = false;
      bool ITzIDDALwl = false;
      bool KTxnCdoSJF = false;
      bool DcONDSHQKp = false;
      string bTSCnutasU;
      string UlfOlVZTar;
      string GsCEIUoeHq;
      string nRWAIRBHpO;
      string sSFRcpQrhp;
      string NLAXriQOsS;
      string FOSCgDPfGT;
      string URcLymmjaS;
      string ExxQdbQyIY;
      string BlOWIdzDkY;
      string akkOVuhoYF;
      string wfmaOIRCYE;
      string lQXhShDFCT;
      string nizBqTLhuh;
      string tbZCbUznIA;
      string MxefmKMDwm;
      string rblEQMfkiu;
      string xiGqKKqUFx;
      string iOxCHqETOf;
      string GIlHoRpUlP;
      if(bTSCnutasU == akkOVuhoYF){oNENDcpnUb = true;}
      else if(akkOVuhoYF == bTSCnutasU){DBwTsrWEkR = true;}
      if(UlfOlVZTar == wfmaOIRCYE){TryzEceixZ = true;}
      else if(wfmaOIRCYE == UlfOlVZTar){PIKxjVuwVt = true;}
      if(GsCEIUoeHq == lQXhShDFCT){HLVDonxzBs = true;}
      else if(lQXhShDFCT == GsCEIUoeHq){xlbLGJiySQ = true;}
      if(nRWAIRBHpO == nizBqTLhuh){UWioHUKjze = true;}
      else if(nizBqTLhuh == nRWAIRBHpO){MpEaWcNbxN = true;}
      if(sSFRcpQrhp == tbZCbUznIA){AQzmMNKmDL = true;}
      else if(tbZCbUznIA == sSFRcpQrhp){ptlPPUyOBd = true;}
      if(NLAXriQOsS == MxefmKMDwm){mGWLIcrBXO = true;}
      else if(MxefmKMDwm == NLAXriQOsS){NhAkRRZkMi = true;}
      if(FOSCgDPfGT == rblEQMfkiu){eqlbHxJIqi = true;}
      else if(rblEQMfkiu == FOSCgDPfGT){JXlUFZEjZG = true;}
      if(URcLymmjaS == xiGqKKqUFx){StjRZqMipa = true;}
      if(ExxQdbQyIY == iOxCHqETOf){dJupFNzWge = true;}
      if(BlOWIdzDkY == GIlHoRpUlP){cJLkzJdWeP = true;}
      while(xiGqKKqUFx == URcLymmjaS){ITzIDDALwl = true;}
      while(iOxCHqETOf == iOxCHqETOf){KTxnCdoSJF = true;}
      while(GIlHoRpUlP == GIlHoRpUlP){DcONDSHQKp = true;}
      if(oNENDcpnUb == true){oNENDcpnUb = false;}
      if(TryzEceixZ == true){TryzEceixZ = false;}
      if(HLVDonxzBs == true){HLVDonxzBs = false;}
      if(UWioHUKjze == true){UWioHUKjze = false;}
      if(AQzmMNKmDL == true){AQzmMNKmDL = false;}
      if(mGWLIcrBXO == true){mGWLIcrBXO = false;}
      if(eqlbHxJIqi == true){eqlbHxJIqi = false;}
      if(StjRZqMipa == true){StjRZqMipa = false;}
      if(dJupFNzWge == true){dJupFNzWge = false;}
      if(cJLkzJdWeP == true){cJLkzJdWeP = false;}
      if(DBwTsrWEkR == true){DBwTsrWEkR = false;}
      if(PIKxjVuwVt == true){PIKxjVuwVt = false;}
      if(xlbLGJiySQ == true){xlbLGJiySQ = false;}
      if(MpEaWcNbxN == true){MpEaWcNbxN = false;}
      if(ptlPPUyOBd == true){ptlPPUyOBd = false;}
      if(NhAkRRZkMi == true){NhAkRRZkMi = false;}
      if(JXlUFZEjZG == true){JXlUFZEjZG = false;}
      if(ITzIDDALwl == true){ITzIDDALwl = false;}
      if(KTxnCdoSJF == true){KTxnCdoSJF = false;}
      if(DcONDSHQKp == true){DcONDSHQKp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TNJRKMOYQP
{ 
  void QXiXENlPQP()
  { 
      bool YuMLLhyrbi = false;
      bool rYJXBTDqID = false;
      bool oEPQEYddiG = false;
      bool CpNycrEMQH = false;
      bool sorxyLBBbA = false;
      bool loipyUeuHl = false;
      bool DTIUfBLLtJ = false;
      bool PqZAKALSSr = false;
      bool XcChUNGWAI = false;
      bool MJFdDYfXRw = false;
      bool ApHSkuOhfx = false;
      bool IMcOOaRZAR = false;
      bool unKlxGluxk = false;
      bool TnAWqgUjxZ = false;
      bool zXqCzzgpPb = false;
      bool HFWzBMfUVd = false;
      bool JSktdULFXg = false;
      bool GhcaSWwHlx = false;
      bool ZufVdNRBVd = false;
      bool BzOSQfmxYe = false;
      string MrdksyzuOc;
      string jwfCcIEjCm;
      string acufzuDTfa;
      string xGIDtMlbEl;
      string UwsQflDBrq;
      string yfKrWjwxkx;
      string ueOmednbHQ;
      string VbeQReidAN;
      string rBancRuPgK;
      string PoqGppgGlB;
      string xasaVVAtZr;
      string ARwWFsDaKN;
      string iXuxBfkYZb;
      string xcrzPQIzSG;
      string QApnKysTAx;
      string lGwXRZfwZo;
      string kbTytWYxHo;
      string kDHDwihGlC;
      string mQXcpqgUgp;
      string kLZdUofqsm;
      if(MrdksyzuOc == xasaVVAtZr){YuMLLhyrbi = true;}
      else if(xasaVVAtZr == MrdksyzuOc){ApHSkuOhfx = true;}
      if(jwfCcIEjCm == ARwWFsDaKN){rYJXBTDqID = true;}
      else if(ARwWFsDaKN == jwfCcIEjCm){IMcOOaRZAR = true;}
      if(acufzuDTfa == iXuxBfkYZb){oEPQEYddiG = true;}
      else if(iXuxBfkYZb == acufzuDTfa){unKlxGluxk = true;}
      if(xGIDtMlbEl == xcrzPQIzSG){CpNycrEMQH = true;}
      else if(xcrzPQIzSG == xGIDtMlbEl){TnAWqgUjxZ = true;}
      if(UwsQflDBrq == QApnKysTAx){sorxyLBBbA = true;}
      else if(QApnKysTAx == UwsQflDBrq){zXqCzzgpPb = true;}
      if(yfKrWjwxkx == lGwXRZfwZo){loipyUeuHl = true;}
      else if(lGwXRZfwZo == yfKrWjwxkx){HFWzBMfUVd = true;}
      if(ueOmednbHQ == kbTytWYxHo){DTIUfBLLtJ = true;}
      else if(kbTytWYxHo == ueOmednbHQ){JSktdULFXg = true;}
      if(VbeQReidAN == kDHDwihGlC){PqZAKALSSr = true;}
      if(rBancRuPgK == mQXcpqgUgp){XcChUNGWAI = true;}
      if(PoqGppgGlB == kLZdUofqsm){MJFdDYfXRw = true;}
      while(kDHDwihGlC == VbeQReidAN){GhcaSWwHlx = true;}
      while(mQXcpqgUgp == mQXcpqgUgp){ZufVdNRBVd = true;}
      while(kLZdUofqsm == kLZdUofqsm){BzOSQfmxYe = true;}
      if(YuMLLhyrbi == true){YuMLLhyrbi = false;}
      if(rYJXBTDqID == true){rYJXBTDqID = false;}
      if(oEPQEYddiG == true){oEPQEYddiG = false;}
      if(CpNycrEMQH == true){CpNycrEMQH = false;}
      if(sorxyLBBbA == true){sorxyLBBbA = false;}
      if(loipyUeuHl == true){loipyUeuHl = false;}
      if(DTIUfBLLtJ == true){DTIUfBLLtJ = false;}
      if(PqZAKALSSr == true){PqZAKALSSr = false;}
      if(XcChUNGWAI == true){XcChUNGWAI = false;}
      if(MJFdDYfXRw == true){MJFdDYfXRw = false;}
      if(ApHSkuOhfx == true){ApHSkuOhfx = false;}
      if(IMcOOaRZAR == true){IMcOOaRZAR = false;}
      if(unKlxGluxk == true){unKlxGluxk = false;}
      if(TnAWqgUjxZ == true){TnAWqgUjxZ = false;}
      if(zXqCzzgpPb == true){zXqCzzgpPb = false;}
      if(HFWzBMfUVd == true){HFWzBMfUVd = false;}
      if(JSktdULFXg == true){JSktdULFXg = false;}
      if(GhcaSWwHlx == true){GhcaSWwHlx = false;}
      if(ZufVdNRBVd == true){ZufVdNRBVd = false;}
      if(BzOSQfmxYe == true){BzOSQfmxYe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWAZRAOKPL
{ 
  void tBpPPkswQC()
  { 
      bool jDkSuRPpAe = false;
      bool EKkjmPKicw = false;
      bool BQPySKLumY = false;
      bool DYydZrBAhF = false;
      bool XeYmFppYzF = false;
      bool nWitGSnmAk = false;
      bool GTCbbeMHJt = false;
      bool NKBWXWrbrb = false;
      bool TlwhjgpDWH = false;
      bool EOzxzEbwLZ = false;
      bool diOErdVMVj = false;
      bool ZLtXQTWUqu = false;
      bool oIjCpyKEXS = false;
      bool tuQSykXqpG = false;
      bool KcgmgrUbff = false;
      bool gHFPjUyMNs = false;
      bool TRnDoetaZf = false;
      bool wfdkjLaxVy = false;
      bool ciXrlmpBid = false;
      bool mLdwlsodyC = false;
      string FgdEShRGJg;
      string NXNxdFkCTd;
      string fPSMEkKNPX;
      string OsADLdtCno;
      string MrQslNWYfc;
      string RzCbIpORzg;
      string WEqlRTXJlA;
      string LiNdRmyZaq;
      string NlhmGPqXuV;
      string PcCGSIBeaS;
      string pNmeRikXKU;
      string qopITkWDfC;
      string czOPkhfGLJ;
      string kTyIAAyCVW;
      string dSNZealsmh;
      string kxyYopzWti;
      string CeMAjWphIT;
      string lThIXJlnkK;
      string wmTcXmUYSJ;
      string BbIlUzGMpH;
      if(FgdEShRGJg == pNmeRikXKU){jDkSuRPpAe = true;}
      else if(pNmeRikXKU == FgdEShRGJg){diOErdVMVj = true;}
      if(NXNxdFkCTd == qopITkWDfC){EKkjmPKicw = true;}
      else if(qopITkWDfC == NXNxdFkCTd){ZLtXQTWUqu = true;}
      if(fPSMEkKNPX == czOPkhfGLJ){BQPySKLumY = true;}
      else if(czOPkhfGLJ == fPSMEkKNPX){oIjCpyKEXS = true;}
      if(OsADLdtCno == kTyIAAyCVW){DYydZrBAhF = true;}
      else if(kTyIAAyCVW == OsADLdtCno){tuQSykXqpG = true;}
      if(MrQslNWYfc == dSNZealsmh){XeYmFppYzF = true;}
      else if(dSNZealsmh == MrQslNWYfc){KcgmgrUbff = true;}
      if(RzCbIpORzg == kxyYopzWti){nWitGSnmAk = true;}
      else if(kxyYopzWti == RzCbIpORzg){gHFPjUyMNs = true;}
      if(WEqlRTXJlA == CeMAjWphIT){GTCbbeMHJt = true;}
      else if(CeMAjWphIT == WEqlRTXJlA){TRnDoetaZf = true;}
      if(LiNdRmyZaq == lThIXJlnkK){NKBWXWrbrb = true;}
      if(NlhmGPqXuV == wmTcXmUYSJ){TlwhjgpDWH = true;}
      if(PcCGSIBeaS == BbIlUzGMpH){EOzxzEbwLZ = true;}
      while(lThIXJlnkK == LiNdRmyZaq){wfdkjLaxVy = true;}
      while(wmTcXmUYSJ == wmTcXmUYSJ){ciXrlmpBid = true;}
      while(BbIlUzGMpH == BbIlUzGMpH){mLdwlsodyC = true;}
      if(jDkSuRPpAe == true){jDkSuRPpAe = false;}
      if(EKkjmPKicw == true){EKkjmPKicw = false;}
      if(BQPySKLumY == true){BQPySKLumY = false;}
      if(DYydZrBAhF == true){DYydZrBAhF = false;}
      if(XeYmFppYzF == true){XeYmFppYzF = false;}
      if(nWitGSnmAk == true){nWitGSnmAk = false;}
      if(GTCbbeMHJt == true){GTCbbeMHJt = false;}
      if(NKBWXWrbrb == true){NKBWXWrbrb = false;}
      if(TlwhjgpDWH == true){TlwhjgpDWH = false;}
      if(EOzxzEbwLZ == true){EOzxzEbwLZ = false;}
      if(diOErdVMVj == true){diOErdVMVj = false;}
      if(ZLtXQTWUqu == true){ZLtXQTWUqu = false;}
      if(oIjCpyKEXS == true){oIjCpyKEXS = false;}
      if(tuQSykXqpG == true){tuQSykXqpG = false;}
      if(KcgmgrUbff == true){KcgmgrUbff = false;}
      if(gHFPjUyMNs == true){gHFPjUyMNs = false;}
      if(TRnDoetaZf == true){TRnDoetaZf = false;}
      if(wfdkjLaxVy == true){wfdkjLaxVy = false;}
      if(ciXrlmpBid == true){ciXrlmpBid = false;}
      if(mLdwlsodyC == true){mLdwlsodyC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RPDVRHYCRT
{ 
  void dWYRrVzMTH()
  { 
      bool nNiqrAlYFq = false;
      bool FXMZjxfJpM = false;
      bool cJkiNfoDph = false;
      bool KRdtuqJcCg = false;
      bool VGepeejRod = false;
      bool bNKycecAdM = false;
      bool KhiXfmtSes = false;
      bool nCGJpWetEi = false;
      bool wXNLGxHeQP = false;
      bool NIzpWmXGKq = false;
      bool jQmwpYGBIG = false;
      bool AhuuPlUXRi = false;
      bool fOCOeeDQlD = false;
      bool zXjMyfkQUg = false;
      bool pGWKPfNDaj = false;
      bool RzoaLVOXQK = false;
      bool VoOEGbxixj = false;
      bool BDCjrZrqyz = false;
      bool RzpCkzhJBb = false;
      bool RMAKLAqRDm = false;
      string rLFJxysAGS;
      string JoehmVOhKN;
      string XOImCTYfOR;
      string gyhpXLamQi;
      string fsPfuZWlCW;
      string NtyUUdCSGc;
      string ZNknkKGoJa;
      string ubQahdybqc;
      string xlcrDlANUt;
      string JIfnJRHbuj;
      string SgbabkdWmp;
      string eaacfmjsjy;
      string KsTORlucRP;
      string WWgHJPJBPR;
      string IcZeOhgCHV;
      string hOqwYZNNJo;
      string pBFXTItTTP;
      string chcRphToAi;
      string FrUugHekhj;
      string CwrZbHWBKG;
      if(rLFJxysAGS == SgbabkdWmp){nNiqrAlYFq = true;}
      else if(SgbabkdWmp == rLFJxysAGS){jQmwpYGBIG = true;}
      if(JoehmVOhKN == eaacfmjsjy){FXMZjxfJpM = true;}
      else if(eaacfmjsjy == JoehmVOhKN){AhuuPlUXRi = true;}
      if(XOImCTYfOR == KsTORlucRP){cJkiNfoDph = true;}
      else if(KsTORlucRP == XOImCTYfOR){fOCOeeDQlD = true;}
      if(gyhpXLamQi == WWgHJPJBPR){KRdtuqJcCg = true;}
      else if(WWgHJPJBPR == gyhpXLamQi){zXjMyfkQUg = true;}
      if(fsPfuZWlCW == IcZeOhgCHV){VGepeejRod = true;}
      else if(IcZeOhgCHV == fsPfuZWlCW){pGWKPfNDaj = true;}
      if(NtyUUdCSGc == hOqwYZNNJo){bNKycecAdM = true;}
      else if(hOqwYZNNJo == NtyUUdCSGc){RzoaLVOXQK = true;}
      if(ZNknkKGoJa == pBFXTItTTP){KhiXfmtSes = true;}
      else if(pBFXTItTTP == ZNknkKGoJa){VoOEGbxixj = true;}
      if(ubQahdybqc == chcRphToAi){nCGJpWetEi = true;}
      if(xlcrDlANUt == FrUugHekhj){wXNLGxHeQP = true;}
      if(JIfnJRHbuj == CwrZbHWBKG){NIzpWmXGKq = true;}
      while(chcRphToAi == ubQahdybqc){BDCjrZrqyz = true;}
      while(FrUugHekhj == FrUugHekhj){RzpCkzhJBb = true;}
      while(CwrZbHWBKG == CwrZbHWBKG){RMAKLAqRDm = true;}
      if(nNiqrAlYFq == true){nNiqrAlYFq = false;}
      if(FXMZjxfJpM == true){FXMZjxfJpM = false;}
      if(cJkiNfoDph == true){cJkiNfoDph = false;}
      if(KRdtuqJcCg == true){KRdtuqJcCg = false;}
      if(VGepeejRod == true){VGepeejRod = false;}
      if(bNKycecAdM == true){bNKycecAdM = false;}
      if(KhiXfmtSes == true){KhiXfmtSes = false;}
      if(nCGJpWetEi == true){nCGJpWetEi = false;}
      if(wXNLGxHeQP == true){wXNLGxHeQP = false;}
      if(NIzpWmXGKq == true){NIzpWmXGKq = false;}
      if(jQmwpYGBIG == true){jQmwpYGBIG = false;}
      if(AhuuPlUXRi == true){AhuuPlUXRi = false;}
      if(fOCOeeDQlD == true){fOCOeeDQlD = false;}
      if(zXjMyfkQUg == true){zXjMyfkQUg = false;}
      if(pGWKPfNDaj == true){pGWKPfNDaj = false;}
      if(RzoaLVOXQK == true){RzoaLVOXQK = false;}
      if(VoOEGbxixj == true){VoOEGbxixj = false;}
      if(BDCjrZrqyz == true){BDCjrZrqyz = false;}
      if(RzpCkzhJBb == true){RzpCkzhJBb = false;}
      if(RMAKLAqRDm == true){RMAKLAqRDm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QBUDARROOU
{ 
  void jmNGHoXGFA()
  { 
      bool BDNDPLIpmL = false;
      bool GYQecPfssy = false;
      bool AbKuXfciIf = false;
      bool SlkDWqrMqB = false;
      bool gODaLWJzdh = false;
      bool dSczUZrRei = false;
      bool hYgHsUmNIl = false;
      bool XSCqQlYijA = false;
      bool VdFZBzIliw = false;
      bool yZgITHguhq = false;
      bool jwpqKKQlii = false;
      bool BJhdNDTGFs = false;
      bool LBeLmxltXI = false;
      bool EcBsQYnNPq = false;
      bool iWDzuorCtQ = false;
      bool napneiRdEM = false;
      bool YWNZdYHoNn = false;
      bool OFqNKoyeQy = false;
      bool FizHUdlMNh = false;
      bool HJJCSMIcVW = false;
      string icRFDQAJSq;
      string ewoElkrpBY;
      string ByyegwidoV;
      string IutEUlNsFc;
      string gpVGSANaxp;
      string ATDeokelYH;
      string gWUwijBjjA;
      string WzkYqKbrLf;
      string hIfyUnrPPj;
      string HaTxuKVYXi;
      string zcqxTBidmd;
      string ImasYYqVbt;
      string rkUAsufmcg;
      string oCTcfERieT;
      string ENclaUAZXW;
      string TzxcpOIpEX;
      string UuAGnFSxMU;
      string HHpHoeIiYY;
      string tFPGMpEqlR;
      string waeHyJMWxV;
      if(icRFDQAJSq == zcqxTBidmd){BDNDPLIpmL = true;}
      else if(zcqxTBidmd == icRFDQAJSq){jwpqKKQlii = true;}
      if(ewoElkrpBY == ImasYYqVbt){GYQecPfssy = true;}
      else if(ImasYYqVbt == ewoElkrpBY){BJhdNDTGFs = true;}
      if(ByyegwidoV == rkUAsufmcg){AbKuXfciIf = true;}
      else if(rkUAsufmcg == ByyegwidoV){LBeLmxltXI = true;}
      if(IutEUlNsFc == oCTcfERieT){SlkDWqrMqB = true;}
      else if(oCTcfERieT == IutEUlNsFc){EcBsQYnNPq = true;}
      if(gpVGSANaxp == ENclaUAZXW){gODaLWJzdh = true;}
      else if(ENclaUAZXW == gpVGSANaxp){iWDzuorCtQ = true;}
      if(ATDeokelYH == TzxcpOIpEX){dSczUZrRei = true;}
      else if(TzxcpOIpEX == ATDeokelYH){napneiRdEM = true;}
      if(gWUwijBjjA == UuAGnFSxMU){hYgHsUmNIl = true;}
      else if(UuAGnFSxMU == gWUwijBjjA){YWNZdYHoNn = true;}
      if(WzkYqKbrLf == HHpHoeIiYY){XSCqQlYijA = true;}
      if(hIfyUnrPPj == tFPGMpEqlR){VdFZBzIliw = true;}
      if(HaTxuKVYXi == waeHyJMWxV){yZgITHguhq = true;}
      while(HHpHoeIiYY == WzkYqKbrLf){OFqNKoyeQy = true;}
      while(tFPGMpEqlR == tFPGMpEqlR){FizHUdlMNh = true;}
      while(waeHyJMWxV == waeHyJMWxV){HJJCSMIcVW = true;}
      if(BDNDPLIpmL == true){BDNDPLIpmL = false;}
      if(GYQecPfssy == true){GYQecPfssy = false;}
      if(AbKuXfciIf == true){AbKuXfciIf = false;}
      if(SlkDWqrMqB == true){SlkDWqrMqB = false;}
      if(gODaLWJzdh == true){gODaLWJzdh = false;}
      if(dSczUZrRei == true){dSczUZrRei = false;}
      if(hYgHsUmNIl == true){hYgHsUmNIl = false;}
      if(XSCqQlYijA == true){XSCqQlYijA = false;}
      if(VdFZBzIliw == true){VdFZBzIliw = false;}
      if(yZgITHguhq == true){yZgITHguhq = false;}
      if(jwpqKKQlii == true){jwpqKKQlii = false;}
      if(BJhdNDTGFs == true){BJhdNDTGFs = false;}
      if(LBeLmxltXI == true){LBeLmxltXI = false;}
      if(EcBsQYnNPq == true){EcBsQYnNPq = false;}
      if(iWDzuorCtQ == true){iWDzuorCtQ = false;}
      if(napneiRdEM == true){napneiRdEM = false;}
      if(YWNZdYHoNn == true){YWNZdYHoNn = false;}
      if(OFqNKoyeQy == true){OFqNKoyeQy = false;}
      if(FizHUdlMNh == true){FizHUdlMNh = false;}
      if(HJJCSMIcVW == true){HJJCSMIcVW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLQQGAXMRA
{ 
  void VAziPGyeOS()
  { 
      bool SZfbxMxyMr = false;
      bool pphzMqOupE = false;
      bool VkpoBJXMuk = false;
      bool cFMwMkOgOp = false;
      bool McMSfahdRJ = false;
      bool mbWzohjpan = false;
      bool njDaOjckla = false;
      bool bhfArsXXJZ = false;
      bool bstkyBhMHe = false;
      bool BXGaBbZkDu = false;
      bool xwrqgFuWHw = false;
      bool JLgAMupRcN = false;
      bool CQdGYDbFzP = false;
      bool SlTNbeBDEs = false;
      bool FKFLUoqFNG = false;
      bool lIIprgRkRc = false;
      bool dpXrcWrTYg = false;
      bool slMjHqLRli = false;
      bool MWqscKddUu = false;
      bool MQkbPPmMix = false;
      string snXhaOWmAf;
      string CufqKWAepR;
      string KZQufUSNjD;
      string QCIRwlGhqB;
      string fhZcVTFDOY;
      string qPgtmTXcBG;
      string wICwPzmNtY;
      string PRnolbzmYL;
      string PPzKMBVNdc;
      string NdfkEWedNV;
      string gqIpJYaqHL;
      string TjDopgJrjN;
      string dYjRKllDjP;
      string xVZCdXGIBn;
      string ZdFSJdZqtX;
      string MmtArIHpfX;
      string mXHrOyKAKR;
      string ZApwmzSQIf;
      string LuIMCJbYKV;
      string QQcdACWNEL;
      if(snXhaOWmAf == gqIpJYaqHL){SZfbxMxyMr = true;}
      else if(gqIpJYaqHL == snXhaOWmAf){xwrqgFuWHw = true;}
      if(CufqKWAepR == TjDopgJrjN){pphzMqOupE = true;}
      else if(TjDopgJrjN == CufqKWAepR){JLgAMupRcN = true;}
      if(KZQufUSNjD == dYjRKllDjP){VkpoBJXMuk = true;}
      else if(dYjRKllDjP == KZQufUSNjD){CQdGYDbFzP = true;}
      if(QCIRwlGhqB == xVZCdXGIBn){cFMwMkOgOp = true;}
      else if(xVZCdXGIBn == QCIRwlGhqB){SlTNbeBDEs = true;}
      if(fhZcVTFDOY == ZdFSJdZqtX){McMSfahdRJ = true;}
      else if(ZdFSJdZqtX == fhZcVTFDOY){FKFLUoqFNG = true;}
      if(qPgtmTXcBG == MmtArIHpfX){mbWzohjpan = true;}
      else if(MmtArIHpfX == qPgtmTXcBG){lIIprgRkRc = true;}
      if(wICwPzmNtY == mXHrOyKAKR){njDaOjckla = true;}
      else if(mXHrOyKAKR == wICwPzmNtY){dpXrcWrTYg = true;}
      if(PRnolbzmYL == ZApwmzSQIf){bhfArsXXJZ = true;}
      if(PPzKMBVNdc == LuIMCJbYKV){bstkyBhMHe = true;}
      if(NdfkEWedNV == QQcdACWNEL){BXGaBbZkDu = true;}
      while(ZApwmzSQIf == PRnolbzmYL){slMjHqLRli = true;}
      while(LuIMCJbYKV == LuIMCJbYKV){MWqscKddUu = true;}
      while(QQcdACWNEL == QQcdACWNEL){MQkbPPmMix = true;}
      if(SZfbxMxyMr == true){SZfbxMxyMr = false;}
      if(pphzMqOupE == true){pphzMqOupE = false;}
      if(VkpoBJXMuk == true){VkpoBJXMuk = false;}
      if(cFMwMkOgOp == true){cFMwMkOgOp = false;}
      if(McMSfahdRJ == true){McMSfahdRJ = false;}
      if(mbWzohjpan == true){mbWzohjpan = false;}
      if(njDaOjckla == true){njDaOjckla = false;}
      if(bhfArsXXJZ == true){bhfArsXXJZ = false;}
      if(bstkyBhMHe == true){bstkyBhMHe = false;}
      if(BXGaBbZkDu == true){BXGaBbZkDu = false;}
      if(xwrqgFuWHw == true){xwrqgFuWHw = false;}
      if(JLgAMupRcN == true){JLgAMupRcN = false;}
      if(CQdGYDbFzP == true){CQdGYDbFzP = false;}
      if(SlTNbeBDEs == true){SlTNbeBDEs = false;}
      if(FKFLUoqFNG == true){FKFLUoqFNG = false;}
      if(lIIprgRkRc == true){lIIprgRkRc = false;}
      if(dpXrcWrTYg == true){dpXrcWrTYg = false;}
      if(slMjHqLRli == true){slMjHqLRli = false;}
      if(MWqscKddUu == true){MWqscKddUu = false;}
      if(MQkbPPmMix == true){MQkbPPmMix = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXETUWLNEH
{ 
  void TPilRpOmDG()
  { 
      bool aVsqNRzZiZ = false;
      bool KJNSaopbFz = false;
      bool mQLjHHSGbs = false;
      bool DlxmkFURrD = false;
      bool mzkrHJVbBV = false;
      bool ycioHJJIjG = false;
      bool yryoWXLagU = false;
      bool UXjBLmfScx = false;
      bool kqFGuZDHeb = false;
      bool uMhkFuBuVi = false;
      bool yttfAasgdT = false;
      bool cpelUGmqtw = false;
      bool UDuFZIpywQ = false;
      bool kkxtzqxYFU = false;
      bool gVdLzEguQy = false;
      bool HJAZNtzoGr = false;
      bool kukMhrskmd = false;
      bool JNlZPzZjFU = false;
      bool atgxJbjXfF = false;
      bool qISMjkkRcG = false;
      string tDqeEdGOfW;
      string fZIClwzNwH;
      string itFgrlsnrB;
      string gGpJGfonaK;
      string lRseCMKeJj;
      string YOcxYAxKlR;
      string jSVdoYjzuG;
      string GLlkURBaef;
      string aOdIbRdrjG;
      string heBJaTwOod;
      string cLjDdNcqbH;
      string zWeFpVnNBX;
      string tqOnXaJcKB;
      string UlkBDPeZeO;
      string olPbHLzuSE;
      string ehMRikwueC;
      string DAgalMkdCa;
      string qNimhIamgM;
      string aNJFVmZTSR;
      string SiubKoEoot;
      if(tDqeEdGOfW == cLjDdNcqbH){aVsqNRzZiZ = true;}
      else if(cLjDdNcqbH == tDqeEdGOfW){yttfAasgdT = true;}
      if(fZIClwzNwH == zWeFpVnNBX){KJNSaopbFz = true;}
      else if(zWeFpVnNBX == fZIClwzNwH){cpelUGmqtw = true;}
      if(itFgrlsnrB == tqOnXaJcKB){mQLjHHSGbs = true;}
      else if(tqOnXaJcKB == itFgrlsnrB){UDuFZIpywQ = true;}
      if(gGpJGfonaK == UlkBDPeZeO){DlxmkFURrD = true;}
      else if(UlkBDPeZeO == gGpJGfonaK){kkxtzqxYFU = true;}
      if(lRseCMKeJj == olPbHLzuSE){mzkrHJVbBV = true;}
      else if(olPbHLzuSE == lRseCMKeJj){gVdLzEguQy = true;}
      if(YOcxYAxKlR == ehMRikwueC){ycioHJJIjG = true;}
      else if(ehMRikwueC == YOcxYAxKlR){HJAZNtzoGr = true;}
      if(jSVdoYjzuG == DAgalMkdCa){yryoWXLagU = true;}
      else if(DAgalMkdCa == jSVdoYjzuG){kukMhrskmd = true;}
      if(GLlkURBaef == qNimhIamgM){UXjBLmfScx = true;}
      if(aOdIbRdrjG == aNJFVmZTSR){kqFGuZDHeb = true;}
      if(heBJaTwOod == SiubKoEoot){uMhkFuBuVi = true;}
      while(qNimhIamgM == GLlkURBaef){JNlZPzZjFU = true;}
      while(aNJFVmZTSR == aNJFVmZTSR){atgxJbjXfF = true;}
      while(SiubKoEoot == SiubKoEoot){qISMjkkRcG = true;}
      if(aVsqNRzZiZ == true){aVsqNRzZiZ = false;}
      if(KJNSaopbFz == true){KJNSaopbFz = false;}
      if(mQLjHHSGbs == true){mQLjHHSGbs = false;}
      if(DlxmkFURrD == true){DlxmkFURrD = false;}
      if(mzkrHJVbBV == true){mzkrHJVbBV = false;}
      if(ycioHJJIjG == true){ycioHJJIjG = false;}
      if(yryoWXLagU == true){yryoWXLagU = false;}
      if(UXjBLmfScx == true){UXjBLmfScx = false;}
      if(kqFGuZDHeb == true){kqFGuZDHeb = false;}
      if(uMhkFuBuVi == true){uMhkFuBuVi = false;}
      if(yttfAasgdT == true){yttfAasgdT = false;}
      if(cpelUGmqtw == true){cpelUGmqtw = false;}
      if(UDuFZIpywQ == true){UDuFZIpywQ = false;}
      if(kkxtzqxYFU == true){kkxtzqxYFU = false;}
      if(gVdLzEguQy == true){gVdLzEguQy = false;}
      if(HJAZNtzoGr == true){HJAZNtzoGr = false;}
      if(kukMhrskmd == true){kukMhrskmd = false;}
      if(JNlZPzZjFU == true){JNlZPzZjFU = false;}
      if(atgxJbjXfF == true){atgxJbjXfF = false;}
      if(qISMjkkRcG == true){qISMjkkRcG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SFWUMFFWLQ
{ 
  void YIDhhynqyR()
  { 
      bool aXEBjrdjRr = false;
      bool UPCmarhkNU = false;
      bool nUFuBAFCNe = false;
      bool bblQzaKCBT = false;
      bool iUmENyxJZE = false;
      bool aZUimGSIzj = false;
      bool laVmPrdkmA = false;
      bool hejtlSgAhD = false;
      bool CubIEBHCds = false;
      bool IBCQgHyAnU = false;
      bool UMWZWupZxT = false;
      bool YRawhpzNhO = false;
      bool kaGtqgbSMd = false;
      bool TgLMhoYBlI = false;
      bool LgFJUqZGiq = false;
      bool IkSZjtFcio = false;
      bool TXNTArFONs = false;
      bool QxaZCDUwYA = false;
      bool GVjVUhOkcn = false;
      bool iwSwomTlJb = false;
      string qOoHicWQBQ;
      string YozoquqXcq;
      string hoafJngGHf;
      string gZjEPbPWya;
      string ZXfYBAgfFf;
      string XfwxmCnJyt;
      string uPIVjzEuZP;
      string eUYCQJIBeI;
      string HABbHBcmQN;
      string nFXDeJOJoB;
      string wlGpADGtfd;
      string slepltOfOh;
      string VRdMbZwUWG;
      string uzMcMVtLbD;
      string tiHmTBZhRk;
      string uhtGfdHtNa;
      string GkWYhsZCcP;
      string ADEKnmJqra;
      string zODlLMFFxh;
      string OAxBxILhEa;
      if(qOoHicWQBQ == wlGpADGtfd){aXEBjrdjRr = true;}
      else if(wlGpADGtfd == qOoHicWQBQ){UMWZWupZxT = true;}
      if(YozoquqXcq == slepltOfOh){UPCmarhkNU = true;}
      else if(slepltOfOh == YozoquqXcq){YRawhpzNhO = true;}
      if(hoafJngGHf == VRdMbZwUWG){nUFuBAFCNe = true;}
      else if(VRdMbZwUWG == hoafJngGHf){kaGtqgbSMd = true;}
      if(gZjEPbPWya == uzMcMVtLbD){bblQzaKCBT = true;}
      else if(uzMcMVtLbD == gZjEPbPWya){TgLMhoYBlI = true;}
      if(ZXfYBAgfFf == tiHmTBZhRk){iUmENyxJZE = true;}
      else if(tiHmTBZhRk == ZXfYBAgfFf){LgFJUqZGiq = true;}
      if(XfwxmCnJyt == uhtGfdHtNa){aZUimGSIzj = true;}
      else if(uhtGfdHtNa == XfwxmCnJyt){IkSZjtFcio = true;}
      if(uPIVjzEuZP == GkWYhsZCcP){laVmPrdkmA = true;}
      else if(GkWYhsZCcP == uPIVjzEuZP){TXNTArFONs = true;}
      if(eUYCQJIBeI == ADEKnmJqra){hejtlSgAhD = true;}
      if(HABbHBcmQN == zODlLMFFxh){CubIEBHCds = true;}
      if(nFXDeJOJoB == OAxBxILhEa){IBCQgHyAnU = true;}
      while(ADEKnmJqra == eUYCQJIBeI){QxaZCDUwYA = true;}
      while(zODlLMFFxh == zODlLMFFxh){GVjVUhOkcn = true;}
      while(OAxBxILhEa == OAxBxILhEa){iwSwomTlJb = true;}
      if(aXEBjrdjRr == true){aXEBjrdjRr = false;}
      if(UPCmarhkNU == true){UPCmarhkNU = false;}
      if(nUFuBAFCNe == true){nUFuBAFCNe = false;}
      if(bblQzaKCBT == true){bblQzaKCBT = false;}
      if(iUmENyxJZE == true){iUmENyxJZE = false;}
      if(aZUimGSIzj == true){aZUimGSIzj = false;}
      if(laVmPrdkmA == true){laVmPrdkmA = false;}
      if(hejtlSgAhD == true){hejtlSgAhD = false;}
      if(CubIEBHCds == true){CubIEBHCds = false;}
      if(IBCQgHyAnU == true){IBCQgHyAnU = false;}
      if(UMWZWupZxT == true){UMWZWupZxT = false;}
      if(YRawhpzNhO == true){YRawhpzNhO = false;}
      if(kaGtqgbSMd == true){kaGtqgbSMd = false;}
      if(TgLMhoYBlI == true){TgLMhoYBlI = false;}
      if(LgFJUqZGiq == true){LgFJUqZGiq = false;}
      if(IkSZjtFcio == true){IkSZjtFcio = false;}
      if(TXNTArFONs == true){TXNTArFONs = false;}
      if(QxaZCDUwYA == true){QxaZCDUwYA = false;}
      if(GVjVUhOkcn == true){GVjVUhOkcn = false;}
      if(iwSwomTlJb == true){iwSwomTlJb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWUJGMPQZA
{ 
  void TgXGVJsIcx()
  { 
      bool bdPipNhZZW = false;
      bool SCDlgyiANB = false;
      bool nWFTeXYJVX = false;
      bool MsdGAhcyVC = false;
      bool hFQigbdtdz = false;
      bool irMxaEYuDS = false;
      bool oXDBJYYxlz = false;
      bool VkdKThGWlC = false;
      bool sdeWoTffeu = false;
      bool IgtDMKBOYH = false;
      bool DgHecyOCdr = false;
      bool xBJBYLsgMo = false;
      bool rrSqpopZxJ = false;
      bool gryeyMWzsq = false;
      bool FdBlxHXseB = false;
      bool RTCiPKNQom = false;
      bool HnEULFDdCL = false;
      bool nsnVjNqgsi = false;
      bool RxturNpOOn = false;
      bool zFKFiRZgar = false;
      string KzEKVoQHyD;
      string BmgXyfEJZG;
      string yqkqGMqlgj;
      string DPqitXuqVH;
      string ACQoXIZHIf;
      string edoVfSOMDI;
      string xeZNzkuyda;
      string kNmSGuauTy;
      string mjcAFZaVCa;
      string IimNJUcCol;
      string MbcguQpVPk;
      string rSrEUNBZIZ;
      string KZuDRCZZIk;
      string SYFglLHwEn;
      string iFFRhophrw;
      string TCsPbmfYOs;
      string pQMeRSNLSJ;
      string FFUTpFTdUb;
      string MrgMQPepFz;
      string ehgLxSrazO;
      if(KzEKVoQHyD == MbcguQpVPk){bdPipNhZZW = true;}
      else if(MbcguQpVPk == KzEKVoQHyD){DgHecyOCdr = true;}
      if(BmgXyfEJZG == rSrEUNBZIZ){SCDlgyiANB = true;}
      else if(rSrEUNBZIZ == BmgXyfEJZG){xBJBYLsgMo = true;}
      if(yqkqGMqlgj == KZuDRCZZIk){nWFTeXYJVX = true;}
      else if(KZuDRCZZIk == yqkqGMqlgj){rrSqpopZxJ = true;}
      if(DPqitXuqVH == SYFglLHwEn){MsdGAhcyVC = true;}
      else if(SYFglLHwEn == DPqitXuqVH){gryeyMWzsq = true;}
      if(ACQoXIZHIf == iFFRhophrw){hFQigbdtdz = true;}
      else if(iFFRhophrw == ACQoXIZHIf){FdBlxHXseB = true;}
      if(edoVfSOMDI == TCsPbmfYOs){irMxaEYuDS = true;}
      else if(TCsPbmfYOs == edoVfSOMDI){RTCiPKNQom = true;}
      if(xeZNzkuyda == pQMeRSNLSJ){oXDBJYYxlz = true;}
      else if(pQMeRSNLSJ == xeZNzkuyda){HnEULFDdCL = true;}
      if(kNmSGuauTy == FFUTpFTdUb){VkdKThGWlC = true;}
      if(mjcAFZaVCa == MrgMQPepFz){sdeWoTffeu = true;}
      if(IimNJUcCol == ehgLxSrazO){IgtDMKBOYH = true;}
      while(FFUTpFTdUb == kNmSGuauTy){nsnVjNqgsi = true;}
      while(MrgMQPepFz == MrgMQPepFz){RxturNpOOn = true;}
      while(ehgLxSrazO == ehgLxSrazO){zFKFiRZgar = true;}
      if(bdPipNhZZW == true){bdPipNhZZW = false;}
      if(SCDlgyiANB == true){SCDlgyiANB = false;}
      if(nWFTeXYJVX == true){nWFTeXYJVX = false;}
      if(MsdGAhcyVC == true){MsdGAhcyVC = false;}
      if(hFQigbdtdz == true){hFQigbdtdz = false;}
      if(irMxaEYuDS == true){irMxaEYuDS = false;}
      if(oXDBJYYxlz == true){oXDBJYYxlz = false;}
      if(VkdKThGWlC == true){VkdKThGWlC = false;}
      if(sdeWoTffeu == true){sdeWoTffeu = false;}
      if(IgtDMKBOYH == true){IgtDMKBOYH = false;}
      if(DgHecyOCdr == true){DgHecyOCdr = false;}
      if(xBJBYLsgMo == true){xBJBYLsgMo = false;}
      if(rrSqpopZxJ == true){rrSqpopZxJ = false;}
      if(gryeyMWzsq == true){gryeyMWzsq = false;}
      if(FdBlxHXseB == true){FdBlxHXseB = false;}
      if(RTCiPKNQom == true){RTCiPKNQom = false;}
      if(HnEULFDdCL == true){HnEULFDdCL = false;}
      if(nsnVjNqgsi == true){nsnVjNqgsi = false;}
      if(RxturNpOOn == true){RxturNpOOn = false;}
      if(zFKFiRZgar == true){zFKFiRZgar = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DZLHXFCKOU
{ 
  void jFywqMGxDG()
  { 
      bool rGOzJHWBJp = false;
      bool YhyKudpLcI = false;
      bool GyAnzKZmNc = false;
      bool JmajIViuJp = false;
      bool SkCIcHkGkM = false;
      bool QCuEPsFZAz = false;
      bool ginggkHOBY = false;
      bool ttBlpVwrLr = false;
      bool ZTBALGrVTP = false;
      bool PJuKIixVar = false;
      bool AVEMSWBIOt = false;
      bool xNOIYNgmUa = false;
      bool skulIkypcG = false;
      bool YZRSqDOoho = false;
      bool EiGZRCtmku = false;
      bool BJAzyOaSDg = false;
      bool XKeIUWuuQV = false;
      bool zrEfVJeUTG = false;
      bool pKEhEOZRUb = false;
      bool bulBQtDyEt = false;
      string XurXdWoriL;
      string cozhqVgDCm;
      string kQymLtUfNO;
      string QNGKISWtap;
      string ZrwStdLCnE;
      string QzQjVGxELj;
      string CJeTtOhoYY;
      string zlbMMrUerh;
      string hSqIxQxWoC;
      string URiqnQMbXe;
      string uWcPEeWDWc;
      string lRMcBjSWWd;
      string RKAWEhDkXw;
      string erGMlLobDS;
      string stzLQDFFoE;
      string ypFtNjVFLW;
      string bleaxsKzpo;
      string tpTEjXLnGA;
      string byuTyolMyC;
      string ojQfpHOXNW;
      if(XurXdWoriL == uWcPEeWDWc){rGOzJHWBJp = true;}
      else if(uWcPEeWDWc == XurXdWoriL){AVEMSWBIOt = true;}
      if(cozhqVgDCm == lRMcBjSWWd){YhyKudpLcI = true;}
      else if(lRMcBjSWWd == cozhqVgDCm){xNOIYNgmUa = true;}
      if(kQymLtUfNO == RKAWEhDkXw){GyAnzKZmNc = true;}
      else if(RKAWEhDkXw == kQymLtUfNO){skulIkypcG = true;}
      if(QNGKISWtap == erGMlLobDS){JmajIViuJp = true;}
      else if(erGMlLobDS == QNGKISWtap){YZRSqDOoho = true;}
      if(ZrwStdLCnE == stzLQDFFoE){SkCIcHkGkM = true;}
      else if(stzLQDFFoE == ZrwStdLCnE){EiGZRCtmku = true;}
      if(QzQjVGxELj == ypFtNjVFLW){QCuEPsFZAz = true;}
      else if(ypFtNjVFLW == QzQjVGxELj){BJAzyOaSDg = true;}
      if(CJeTtOhoYY == bleaxsKzpo){ginggkHOBY = true;}
      else if(bleaxsKzpo == CJeTtOhoYY){XKeIUWuuQV = true;}
      if(zlbMMrUerh == tpTEjXLnGA){ttBlpVwrLr = true;}
      if(hSqIxQxWoC == byuTyolMyC){ZTBALGrVTP = true;}
      if(URiqnQMbXe == ojQfpHOXNW){PJuKIixVar = true;}
      while(tpTEjXLnGA == zlbMMrUerh){zrEfVJeUTG = true;}
      while(byuTyolMyC == byuTyolMyC){pKEhEOZRUb = true;}
      while(ojQfpHOXNW == ojQfpHOXNW){bulBQtDyEt = true;}
      if(rGOzJHWBJp == true){rGOzJHWBJp = false;}
      if(YhyKudpLcI == true){YhyKudpLcI = false;}
      if(GyAnzKZmNc == true){GyAnzKZmNc = false;}
      if(JmajIViuJp == true){JmajIViuJp = false;}
      if(SkCIcHkGkM == true){SkCIcHkGkM = false;}
      if(QCuEPsFZAz == true){QCuEPsFZAz = false;}
      if(ginggkHOBY == true){ginggkHOBY = false;}
      if(ttBlpVwrLr == true){ttBlpVwrLr = false;}
      if(ZTBALGrVTP == true){ZTBALGrVTP = false;}
      if(PJuKIixVar == true){PJuKIixVar = false;}
      if(AVEMSWBIOt == true){AVEMSWBIOt = false;}
      if(xNOIYNgmUa == true){xNOIYNgmUa = false;}
      if(skulIkypcG == true){skulIkypcG = false;}
      if(YZRSqDOoho == true){YZRSqDOoho = false;}
      if(EiGZRCtmku == true){EiGZRCtmku = false;}
      if(BJAzyOaSDg == true){BJAzyOaSDg = false;}
      if(XKeIUWuuQV == true){XKeIUWuuQV = false;}
      if(zrEfVJeUTG == true){zrEfVJeUTG = false;}
      if(pKEhEOZRUb == true){pKEhEOZRUb = false;}
      if(bulBQtDyEt == true){bulBQtDyEt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JLTDJYCVIX
{ 
  void jIpYqFOasV()
  { 
      bool rGMjtDNcpR = false;
      bool eRtctQTcTO = false;
      bool SAUbIMVjXf = false;
      bool AOffqODjKU = false;
      bool BmdDsHOZBY = false;
      bool IOyDVrkjbh = false;
      bool hcFJQPlOlf = false;
      bool MiRyMeVQiA = false;
      bool yuiyWlQbJy = false;
      bool cTIclYgTlc = false;
      bool VAnVLZwzqq = false;
      bool VTBajmtHme = false;
      bool zKEmCsanMn = false;
      bool xBeFexGMlx = false;
      bool oQjRcIRhsz = false;
      bool dZgHdKuBSS = false;
      bool yImDsTowul = false;
      bool fgUophZlKt = false;
      bool astMJXUXbU = false;
      bool CFtTyfcgYI = false;
      string JJHQKYCwsM;
      string UMrybeDqYF;
      string OhffomxjLY;
      string uVQOpdtaNo;
      string kUxoYAmPIS;
      string oDpNfadbaX;
      string bRjUQyucHy;
      string kccjTsjpGo;
      string zgbsiqfDiO;
      string ASzpMSjcXa;
      string EKHKhLaGsl;
      string qmVlXupqkY;
      string RrtrxRdmWB;
      string IHSekoYQLX;
      string QZKwXNxNSQ;
      string csqyJMPPMP;
      string hnirdiUpAh;
      string WYfNIqgyUj;
      string UQUFXPQTVY;
      string ZJDupcqRRo;
      if(JJHQKYCwsM == EKHKhLaGsl){rGMjtDNcpR = true;}
      else if(EKHKhLaGsl == JJHQKYCwsM){VAnVLZwzqq = true;}
      if(UMrybeDqYF == qmVlXupqkY){eRtctQTcTO = true;}
      else if(qmVlXupqkY == UMrybeDqYF){VTBajmtHme = true;}
      if(OhffomxjLY == RrtrxRdmWB){SAUbIMVjXf = true;}
      else if(RrtrxRdmWB == OhffomxjLY){zKEmCsanMn = true;}
      if(uVQOpdtaNo == IHSekoYQLX){AOffqODjKU = true;}
      else if(IHSekoYQLX == uVQOpdtaNo){xBeFexGMlx = true;}
      if(kUxoYAmPIS == QZKwXNxNSQ){BmdDsHOZBY = true;}
      else if(QZKwXNxNSQ == kUxoYAmPIS){oQjRcIRhsz = true;}
      if(oDpNfadbaX == csqyJMPPMP){IOyDVrkjbh = true;}
      else if(csqyJMPPMP == oDpNfadbaX){dZgHdKuBSS = true;}
      if(bRjUQyucHy == hnirdiUpAh){hcFJQPlOlf = true;}
      else if(hnirdiUpAh == bRjUQyucHy){yImDsTowul = true;}
      if(kccjTsjpGo == WYfNIqgyUj){MiRyMeVQiA = true;}
      if(zgbsiqfDiO == UQUFXPQTVY){yuiyWlQbJy = true;}
      if(ASzpMSjcXa == ZJDupcqRRo){cTIclYgTlc = true;}
      while(WYfNIqgyUj == kccjTsjpGo){fgUophZlKt = true;}
      while(UQUFXPQTVY == UQUFXPQTVY){astMJXUXbU = true;}
      while(ZJDupcqRRo == ZJDupcqRRo){CFtTyfcgYI = true;}
      if(rGMjtDNcpR == true){rGMjtDNcpR = false;}
      if(eRtctQTcTO == true){eRtctQTcTO = false;}
      if(SAUbIMVjXf == true){SAUbIMVjXf = false;}
      if(AOffqODjKU == true){AOffqODjKU = false;}
      if(BmdDsHOZBY == true){BmdDsHOZBY = false;}
      if(IOyDVrkjbh == true){IOyDVrkjbh = false;}
      if(hcFJQPlOlf == true){hcFJQPlOlf = false;}
      if(MiRyMeVQiA == true){MiRyMeVQiA = false;}
      if(yuiyWlQbJy == true){yuiyWlQbJy = false;}
      if(cTIclYgTlc == true){cTIclYgTlc = false;}
      if(VAnVLZwzqq == true){VAnVLZwzqq = false;}
      if(VTBajmtHme == true){VTBajmtHme = false;}
      if(zKEmCsanMn == true){zKEmCsanMn = false;}
      if(xBeFexGMlx == true){xBeFexGMlx = false;}
      if(oQjRcIRhsz == true){oQjRcIRhsz = false;}
      if(dZgHdKuBSS == true){dZgHdKuBSS = false;}
      if(yImDsTowul == true){yImDsTowul = false;}
      if(fgUophZlKt == true){fgUophZlKt = false;}
      if(astMJXUXbU == true){astMJXUXbU = false;}
      if(CFtTyfcgYI == true){CFtTyfcgYI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QXWHLWEVRE
{ 
  void sbjbCjEcIo()
  { 
      bool npVTYWVQph = false;
      bool LKCjGTuKms = false;
      bool XIGnXdRDUZ = false;
      bool sZCYNSAEZG = false;
      bool GNkkomkJBl = false;
      bool pZTRZeihuu = false;
      bool FSuPolHdWm = false;
      bool SpkflJXVyk = false;
      bool sHBijTFkyh = false;
      bool iSIeAnSUwD = false;
      bool fGmOTAnmfQ = false;
      bool HNjKByQLfV = false;
      bool fVfoEAgGfx = false;
      bool qCYuFmTmOi = false;
      bool eSFhZViycB = false;
      bool XGnZWJZyKT = false;
      bool ShHhZEnnEO = false;
      bool ddxwpNQyOh = false;
      bool RicdZjNyYw = false;
      bool MVcuPwLWIU = false;
      string KlpLurAAOa;
      string cXifRuoJcu;
      string ryYSoPCSCU;
      string UKSZjCwOMN;
      string IOLZCBbrao;
      string zfPQLLNXVe;
      string phxtFSFJuO;
      string zawOmcmyPn;
      string nKqNVnuBOY;
      string nYrgXZRQTj;
      string uSwLpYiAdh;
      string YPHhqfqiYQ;
      string XDtWZahOqM;
      string LVdfrVNeXx;
      string FtXgAYRKpq;
      string ihrCLqXZkP;
      string pTJQVCkaoV;
      string RLLbLcfNWB;
      string IWYzdcdbTB;
      string xntIGkjGKy;
      if(KlpLurAAOa == uSwLpYiAdh){npVTYWVQph = true;}
      else if(uSwLpYiAdh == KlpLurAAOa){fGmOTAnmfQ = true;}
      if(cXifRuoJcu == YPHhqfqiYQ){LKCjGTuKms = true;}
      else if(YPHhqfqiYQ == cXifRuoJcu){HNjKByQLfV = true;}
      if(ryYSoPCSCU == XDtWZahOqM){XIGnXdRDUZ = true;}
      else if(XDtWZahOqM == ryYSoPCSCU){fVfoEAgGfx = true;}
      if(UKSZjCwOMN == LVdfrVNeXx){sZCYNSAEZG = true;}
      else if(LVdfrVNeXx == UKSZjCwOMN){qCYuFmTmOi = true;}
      if(IOLZCBbrao == FtXgAYRKpq){GNkkomkJBl = true;}
      else if(FtXgAYRKpq == IOLZCBbrao){eSFhZViycB = true;}
      if(zfPQLLNXVe == ihrCLqXZkP){pZTRZeihuu = true;}
      else if(ihrCLqXZkP == zfPQLLNXVe){XGnZWJZyKT = true;}
      if(phxtFSFJuO == pTJQVCkaoV){FSuPolHdWm = true;}
      else if(pTJQVCkaoV == phxtFSFJuO){ShHhZEnnEO = true;}
      if(zawOmcmyPn == RLLbLcfNWB){SpkflJXVyk = true;}
      if(nKqNVnuBOY == IWYzdcdbTB){sHBijTFkyh = true;}
      if(nYrgXZRQTj == xntIGkjGKy){iSIeAnSUwD = true;}
      while(RLLbLcfNWB == zawOmcmyPn){ddxwpNQyOh = true;}
      while(IWYzdcdbTB == IWYzdcdbTB){RicdZjNyYw = true;}
      while(xntIGkjGKy == xntIGkjGKy){MVcuPwLWIU = true;}
      if(npVTYWVQph == true){npVTYWVQph = false;}
      if(LKCjGTuKms == true){LKCjGTuKms = false;}
      if(XIGnXdRDUZ == true){XIGnXdRDUZ = false;}
      if(sZCYNSAEZG == true){sZCYNSAEZG = false;}
      if(GNkkomkJBl == true){GNkkomkJBl = false;}
      if(pZTRZeihuu == true){pZTRZeihuu = false;}
      if(FSuPolHdWm == true){FSuPolHdWm = false;}
      if(SpkflJXVyk == true){SpkflJXVyk = false;}
      if(sHBijTFkyh == true){sHBijTFkyh = false;}
      if(iSIeAnSUwD == true){iSIeAnSUwD = false;}
      if(fGmOTAnmfQ == true){fGmOTAnmfQ = false;}
      if(HNjKByQLfV == true){HNjKByQLfV = false;}
      if(fVfoEAgGfx == true){fVfoEAgGfx = false;}
      if(qCYuFmTmOi == true){qCYuFmTmOi = false;}
      if(eSFhZViycB == true){eSFhZViycB = false;}
      if(XGnZWJZyKT == true){XGnZWJZyKT = false;}
      if(ShHhZEnnEO == true){ShHhZEnnEO = false;}
      if(ddxwpNQyOh == true){ddxwpNQyOh = false;}
      if(RicdZjNyYw == true){RicdZjNyYw = false;}
      if(MVcuPwLWIU == true){MVcuPwLWIU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DAHNATCMPR
{ 
  void BFqaPYuALi()
  { 
      bool uUehghHNye = false;
      bool jdFPUsCCJs = false;
      bool QwUxJVmdqg = false;
      bool ZeDaIOWtPQ = false;
      bool UimfFPmZKC = false;
      bool RYxSZzAhYK = false;
      bool tcWQFEZeGF = false;
      bool WHmrYgJnrs = false;
      bool iMTnPAhjAI = false;
      bool OnUEVqMVZA = false;
      bool oITEfJlEss = false;
      bool pLoebhJhBF = false;
      bool WodxqhmiVh = false;
      bool TmNrEasOIG = false;
      bool OcqGSDzobn = false;
      bool gdTUcAdVNy = false;
      bool VChLYCxxaB = false;
      bool nuZupsyXdm = false;
      bool hxGhApTsOE = false;
      bool xXAKjLuehQ = false;
      string jOtXlbmBsG;
      string gqTsWQgggz;
      string utQQqSopdH;
      string ThGWGsEwsN;
      string slQjLHnfeB;
      string AdMXYoydgT;
      string mxXkmzjwmc;
      string LjmTFIcgEi;
      string dIKbHoUhyQ;
      string uaPZZwOewL;
      string XqsBpPqsSP;
      string LRYxodlwdy;
      string dByVhkTMsJ;
      string tyjsKmPJkq;
      string xbPhEdBRkw;
      string KRAygVsWTF;
      string udzIVNhflC;
      string OcKmAClPRE;
      string jCbwzbxkLo;
      string srofuTbGMq;
      if(jOtXlbmBsG == XqsBpPqsSP){uUehghHNye = true;}
      else if(XqsBpPqsSP == jOtXlbmBsG){oITEfJlEss = true;}
      if(gqTsWQgggz == LRYxodlwdy){jdFPUsCCJs = true;}
      else if(LRYxodlwdy == gqTsWQgggz){pLoebhJhBF = true;}
      if(utQQqSopdH == dByVhkTMsJ){QwUxJVmdqg = true;}
      else if(dByVhkTMsJ == utQQqSopdH){WodxqhmiVh = true;}
      if(ThGWGsEwsN == tyjsKmPJkq){ZeDaIOWtPQ = true;}
      else if(tyjsKmPJkq == ThGWGsEwsN){TmNrEasOIG = true;}
      if(slQjLHnfeB == xbPhEdBRkw){UimfFPmZKC = true;}
      else if(xbPhEdBRkw == slQjLHnfeB){OcqGSDzobn = true;}
      if(AdMXYoydgT == KRAygVsWTF){RYxSZzAhYK = true;}
      else if(KRAygVsWTF == AdMXYoydgT){gdTUcAdVNy = true;}
      if(mxXkmzjwmc == udzIVNhflC){tcWQFEZeGF = true;}
      else if(udzIVNhflC == mxXkmzjwmc){VChLYCxxaB = true;}
      if(LjmTFIcgEi == OcKmAClPRE){WHmrYgJnrs = true;}
      if(dIKbHoUhyQ == jCbwzbxkLo){iMTnPAhjAI = true;}
      if(uaPZZwOewL == srofuTbGMq){OnUEVqMVZA = true;}
      while(OcKmAClPRE == LjmTFIcgEi){nuZupsyXdm = true;}
      while(jCbwzbxkLo == jCbwzbxkLo){hxGhApTsOE = true;}
      while(srofuTbGMq == srofuTbGMq){xXAKjLuehQ = true;}
      if(uUehghHNye == true){uUehghHNye = false;}
      if(jdFPUsCCJs == true){jdFPUsCCJs = false;}
      if(QwUxJVmdqg == true){QwUxJVmdqg = false;}
      if(ZeDaIOWtPQ == true){ZeDaIOWtPQ = false;}
      if(UimfFPmZKC == true){UimfFPmZKC = false;}
      if(RYxSZzAhYK == true){RYxSZzAhYK = false;}
      if(tcWQFEZeGF == true){tcWQFEZeGF = false;}
      if(WHmrYgJnrs == true){WHmrYgJnrs = false;}
      if(iMTnPAhjAI == true){iMTnPAhjAI = false;}
      if(OnUEVqMVZA == true){OnUEVqMVZA = false;}
      if(oITEfJlEss == true){oITEfJlEss = false;}
      if(pLoebhJhBF == true){pLoebhJhBF = false;}
      if(WodxqhmiVh == true){WodxqhmiVh = false;}
      if(TmNrEasOIG == true){TmNrEasOIG = false;}
      if(OcqGSDzobn == true){OcqGSDzobn = false;}
      if(gdTUcAdVNy == true){gdTUcAdVNy = false;}
      if(VChLYCxxaB == true){VChLYCxxaB = false;}
      if(nuZupsyXdm == true){nuZupsyXdm = false;}
      if(hxGhApTsOE == true){hxGhApTsOE = false;}
      if(xXAKjLuehQ == true){xXAKjLuehQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EXAQZZGKDG
{ 
  void NtLCYiiXfx()
  { 
      bool ORImjgHswk = false;
      bool wEnHfypcXA = false;
      bool TzcQmUSRjB = false;
      bool zZYJYPcOrV = false;
      bool lDJcfPPEIi = false;
      bool xMILTOnrzO = false;
      bool OoItkVfehP = false;
      bool UbkCNPpAjX = false;
      bool FOIAEmRNpJ = false;
      bool akOdHwtPqJ = false;
      bool ikWrOUbGxD = false;
      bool YnIbIAgIoy = false;
      bool ESnXniMGtQ = false;
      bool VaJZnUqPki = false;
      bool LLPlkmcmVH = false;
      bool PkarFQwyDe = false;
      bool IULggyehmm = false;
      bool IQXFlsDCmB = false;
      bool GZkmAjAQUX = false;
      bool YsLFaqziEm = false;
      string ydSBcUoQLF;
      string HWkXhFOgQM;
      string XZmkeThpwi;
      string SkHnyHXyWJ;
      string xrXqigcJdm;
      string pzyHgYqhWI;
      string lyTcmWPxYZ;
      string gQKHOfBuBx;
      string pYLJrSlAGZ;
      string QpaNWzXtEM;
      string RfjEFZnprB;
      string WwfYSNlKjT;
      string kOpzIqowkP;
      string HGpofKnHDS;
      string euIFCUJCuI;
      string MNKkaCokuO;
      string kqFbsPFqsH;
      string YeGRooGkwn;
      string hlBbDswFNc;
      string UDLohmpfLm;
      if(ydSBcUoQLF == RfjEFZnprB){ORImjgHswk = true;}
      else if(RfjEFZnprB == ydSBcUoQLF){ikWrOUbGxD = true;}
      if(HWkXhFOgQM == WwfYSNlKjT){wEnHfypcXA = true;}
      else if(WwfYSNlKjT == HWkXhFOgQM){YnIbIAgIoy = true;}
      if(XZmkeThpwi == kOpzIqowkP){TzcQmUSRjB = true;}
      else if(kOpzIqowkP == XZmkeThpwi){ESnXniMGtQ = true;}
      if(SkHnyHXyWJ == HGpofKnHDS){zZYJYPcOrV = true;}
      else if(HGpofKnHDS == SkHnyHXyWJ){VaJZnUqPki = true;}
      if(xrXqigcJdm == euIFCUJCuI){lDJcfPPEIi = true;}
      else if(euIFCUJCuI == xrXqigcJdm){LLPlkmcmVH = true;}
      if(pzyHgYqhWI == MNKkaCokuO){xMILTOnrzO = true;}
      else if(MNKkaCokuO == pzyHgYqhWI){PkarFQwyDe = true;}
      if(lyTcmWPxYZ == kqFbsPFqsH){OoItkVfehP = true;}
      else if(kqFbsPFqsH == lyTcmWPxYZ){IULggyehmm = true;}
      if(gQKHOfBuBx == YeGRooGkwn){UbkCNPpAjX = true;}
      if(pYLJrSlAGZ == hlBbDswFNc){FOIAEmRNpJ = true;}
      if(QpaNWzXtEM == UDLohmpfLm){akOdHwtPqJ = true;}
      while(YeGRooGkwn == gQKHOfBuBx){IQXFlsDCmB = true;}
      while(hlBbDswFNc == hlBbDswFNc){GZkmAjAQUX = true;}
      while(UDLohmpfLm == UDLohmpfLm){YsLFaqziEm = true;}
      if(ORImjgHswk == true){ORImjgHswk = false;}
      if(wEnHfypcXA == true){wEnHfypcXA = false;}
      if(TzcQmUSRjB == true){TzcQmUSRjB = false;}
      if(zZYJYPcOrV == true){zZYJYPcOrV = false;}
      if(lDJcfPPEIi == true){lDJcfPPEIi = false;}
      if(xMILTOnrzO == true){xMILTOnrzO = false;}
      if(OoItkVfehP == true){OoItkVfehP = false;}
      if(UbkCNPpAjX == true){UbkCNPpAjX = false;}
      if(FOIAEmRNpJ == true){FOIAEmRNpJ = false;}
      if(akOdHwtPqJ == true){akOdHwtPqJ = false;}
      if(ikWrOUbGxD == true){ikWrOUbGxD = false;}
      if(YnIbIAgIoy == true){YnIbIAgIoy = false;}
      if(ESnXniMGtQ == true){ESnXniMGtQ = false;}
      if(VaJZnUqPki == true){VaJZnUqPki = false;}
      if(LLPlkmcmVH == true){LLPlkmcmVH = false;}
      if(PkarFQwyDe == true){PkarFQwyDe = false;}
      if(IULggyehmm == true){IULggyehmm = false;}
      if(IQXFlsDCmB == true){IQXFlsDCmB = false;}
      if(GZkmAjAQUX == true){GZkmAjAQUX = false;}
      if(YsLFaqziEm == true){YsLFaqziEm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TSKFIMUDFM
{ 
  void GMlYmEWjxH()
  { 
      bool rVIfaeYECQ = false;
      bool LOahqlzJYB = false;
      bool MSKOXjfFWd = false;
      bool JfncTwMIdg = false;
      bool GDDqeCmFwP = false;
      bool MqlgsZKtIp = false;
      bool zTgYHeaxOu = false;
      bool YpeqtJPTjV = false;
      bool xZJHQRsGjt = false;
      bool kSAmhlWdiz = false;
      bool boqApWLtmj = false;
      bool KqJlrZKZIo = false;
      bool lTNTKGpqJI = false;
      bool lkjktHhIRs = false;
      bool GyTzisJNtI = false;
      bool awVtMHaWoj = false;
      bool fTkexYGXrk = false;
      bool qBIOhmAOkQ = false;
      bool wbwAgoPpXl = false;
      bool gKSgNlNoCK = false;
      string LLrkmjObfJ;
      string HjLoLSnwwe;
      string TCGKEYOBXr;
      string TcEfssWrZS;
      string QMBYdWBSqK;
      string oUVKlIEhfN;
      string UNDmoeffwR;
      string uwWcOGAhgh;
      string XwJMDzGstj;
      string noLLyDIOiy;
      string pVWYPryrwe;
      string HWAxpXEpjp;
      string XmkLdFjKeL;
      string ylyhrBYjxK;
      string AOwObQnNVZ;
      string zSdraCjKuJ;
      string InNkgVXSFo;
      string zTsZpJqVjM;
      string RVoEMfIFHp;
      string QOnnCMALhG;
      if(LLrkmjObfJ == pVWYPryrwe){rVIfaeYECQ = true;}
      else if(pVWYPryrwe == LLrkmjObfJ){boqApWLtmj = true;}
      if(HjLoLSnwwe == HWAxpXEpjp){LOahqlzJYB = true;}
      else if(HWAxpXEpjp == HjLoLSnwwe){KqJlrZKZIo = true;}
      if(TCGKEYOBXr == XmkLdFjKeL){MSKOXjfFWd = true;}
      else if(XmkLdFjKeL == TCGKEYOBXr){lTNTKGpqJI = true;}
      if(TcEfssWrZS == ylyhrBYjxK){JfncTwMIdg = true;}
      else if(ylyhrBYjxK == TcEfssWrZS){lkjktHhIRs = true;}
      if(QMBYdWBSqK == AOwObQnNVZ){GDDqeCmFwP = true;}
      else if(AOwObQnNVZ == QMBYdWBSqK){GyTzisJNtI = true;}
      if(oUVKlIEhfN == zSdraCjKuJ){MqlgsZKtIp = true;}
      else if(zSdraCjKuJ == oUVKlIEhfN){awVtMHaWoj = true;}
      if(UNDmoeffwR == InNkgVXSFo){zTgYHeaxOu = true;}
      else if(InNkgVXSFo == UNDmoeffwR){fTkexYGXrk = true;}
      if(uwWcOGAhgh == zTsZpJqVjM){YpeqtJPTjV = true;}
      if(XwJMDzGstj == RVoEMfIFHp){xZJHQRsGjt = true;}
      if(noLLyDIOiy == QOnnCMALhG){kSAmhlWdiz = true;}
      while(zTsZpJqVjM == uwWcOGAhgh){qBIOhmAOkQ = true;}
      while(RVoEMfIFHp == RVoEMfIFHp){wbwAgoPpXl = true;}
      while(QOnnCMALhG == QOnnCMALhG){gKSgNlNoCK = true;}
      if(rVIfaeYECQ == true){rVIfaeYECQ = false;}
      if(LOahqlzJYB == true){LOahqlzJYB = false;}
      if(MSKOXjfFWd == true){MSKOXjfFWd = false;}
      if(JfncTwMIdg == true){JfncTwMIdg = false;}
      if(GDDqeCmFwP == true){GDDqeCmFwP = false;}
      if(MqlgsZKtIp == true){MqlgsZKtIp = false;}
      if(zTgYHeaxOu == true){zTgYHeaxOu = false;}
      if(YpeqtJPTjV == true){YpeqtJPTjV = false;}
      if(xZJHQRsGjt == true){xZJHQRsGjt = false;}
      if(kSAmhlWdiz == true){kSAmhlWdiz = false;}
      if(boqApWLtmj == true){boqApWLtmj = false;}
      if(KqJlrZKZIo == true){KqJlrZKZIo = false;}
      if(lTNTKGpqJI == true){lTNTKGpqJI = false;}
      if(lkjktHhIRs == true){lkjktHhIRs = false;}
      if(GyTzisJNtI == true){GyTzisJNtI = false;}
      if(awVtMHaWoj == true){awVtMHaWoj = false;}
      if(fTkexYGXrk == true){fTkexYGXrk = false;}
      if(qBIOhmAOkQ == true){qBIOhmAOkQ = false;}
      if(wbwAgoPpXl == true){wbwAgoPpXl = false;}
      if(gKSgNlNoCK == true){gKSgNlNoCK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QZDXCGZGFX
{ 
  void HMbNCQNLKq()
  { 
      bool DKTjPyfUZT = false;
      bool pksJhmlouQ = false;
      bool sqIAzksWhR = false;
      bool usOkuBGigc = false;
      bool ICmqYXDZqf = false;
      bool oZjMELBTje = false;
      bool FIlHYwWHOg = false;
      bool fDHRHqERaa = false;
      bool hSeCcUJCgi = false;
      bool AlyCWzPeSb = false;
      bool AuLKzlSREM = false;
      bool HisIxmdjeE = false;
      bool lUafftEEtH = false;
      bool aZzzamHUCq = false;
      bool BrxTbQsoFj = false;
      bool VfANoeTfdE = false;
      bool gNWwlgjshK = false;
      bool eJgnCtXGDP = false;
      bool BPzKluZkJu = false;
      bool SbpyJnVBht = false;
      string lqHeNPwgwb;
      string TLOyzHZYWW;
      string OhiSRaDUPL;
      string IWFibAcnZT;
      string WHmLmxjzNN;
      string INlacDIoMl;
      string MaQkTxGfWz;
      string dkyDzGtXfU;
      string qDGCDtkdFX;
      string rnanGupCrp;
      string qEcOiWPiaV;
      string IjJruIUOgY;
      string MbazGpJKwD;
      string QrfodmarSf;
      string eBCiOHeiry;
      string abUSdOcdIs;
      string NElXFQETOI;
      string hcwAsKYqjy;
      string LaSxboWMLO;
      string JxiYSaPecy;
      if(lqHeNPwgwb == qEcOiWPiaV){DKTjPyfUZT = true;}
      else if(qEcOiWPiaV == lqHeNPwgwb){AuLKzlSREM = true;}
      if(TLOyzHZYWW == IjJruIUOgY){pksJhmlouQ = true;}
      else if(IjJruIUOgY == TLOyzHZYWW){HisIxmdjeE = true;}
      if(OhiSRaDUPL == MbazGpJKwD){sqIAzksWhR = true;}
      else if(MbazGpJKwD == OhiSRaDUPL){lUafftEEtH = true;}
      if(IWFibAcnZT == QrfodmarSf){usOkuBGigc = true;}
      else if(QrfodmarSf == IWFibAcnZT){aZzzamHUCq = true;}
      if(WHmLmxjzNN == eBCiOHeiry){ICmqYXDZqf = true;}
      else if(eBCiOHeiry == WHmLmxjzNN){BrxTbQsoFj = true;}
      if(INlacDIoMl == abUSdOcdIs){oZjMELBTje = true;}
      else if(abUSdOcdIs == INlacDIoMl){VfANoeTfdE = true;}
      if(MaQkTxGfWz == NElXFQETOI){FIlHYwWHOg = true;}
      else if(NElXFQETOI == MaQkTxGfWz){gNWwlgjshK = true;}
      if(dkyDzGtXfU == hcwAsKYqjy){fDHRHqERaa = true;}
      if(qDGCDtkdFX == LaSxboWMLO){hSeCcUJCgi = true;}
      if(rnanGupCrp == JxiYSaPecy){AlyCWzPeSb = true;}
      while(hcwAsKYqjy == dkyDzGtXfU){eJgnCtXGDP = true;}
      while(LaSxboWMLO == LaSxboWMLO){BPzKluZkJu = true;}
      while(JxiYSaPecy == JxiYSaPecy){SbpyJnVBht = true;}
      if(DKTjPyfUZT == true){DKTjPyfUZT = false;}
      if(pksJhmlouQ == true){pksJhmlouQ = false;}
      if(sqIAzksWhR == true){sqIAzksWhR = false;}
      if(usOkuBGigc == true){usOkuBGigc = false;}
      if(ICmqYXDZqf == true){ICmqYXDZqf = false;}
      if(oZjMELBTje == true){oZjMELBTje = false;}
      if(FIlHYwWHOg == true){FIlHYwWHOg = false;}
      if(fDHRHqERaa == true){fDHRHqERaa = false;}
      if(hSeCcUJCgi == true){hSeCcUJCgi = false;}
      if(AlyCWzPeSb == true){AlyCWzPeSb = false;}
      if(AuLKzlSREM == true){AuLKzlSREM = false;}
      if(HisIxmdjeE == true){HisIxmdjeE = false;}
      if(lUafftEEtH == true){lUafftEEtH = false;}
      if(aZzzamHUCq == true){aZzzamHUCq = false;}
      if(BrxTbQsoFj == true){BrxTbQsoFj = false;}
      if(VfANoeTfdE == true){VfANoeTfdE = false;}
      if(gNWwlgjshK == true){gNWwlgjshK = false;}
      if(eJgnCtXGDP == true){eJgnCtXGDP = false;}
      if(BPzKluZkJu == true){BPzKluZkJu = false;}
      if(SbpyJnVBht == true){SbpyJnVBht = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DHHVVTDBSU
{ 
  void jxxiqEAyAa()
  { 
      bool BrVwKgGbYK = false;
      bool oAnUHzcKxh = false;
      bool hbbkSLFpjP = false;
      bool mStiZQZCbo = false;
      bool yktEudUUtt = false;
      bool wYaXnYPkcy = false;
      bool aPrIXVGFtp = false;
      bool ZZhIjwhXoo = false;
      bool qkuoTNqVuA = false;
      bool BnYcNiskfY = false;
      bool WOaEUVpRnq = false;
      bool qrunHpTCoJ = false;
      bool ejKsokBFuA = false;
      bool DwqQSbJqTx = false;
      bool XZhDJIrjVW = false;
      bool OpwWtlEgOj = false;
      bool UkWmntBeVe = false;
      bool fchrlFCHjf = false;
      bool rQjXlMAUWf = false;
      bool WcbjbmCuOP = false;
      string NIaNASIoLH;
      string ToUhhKJjLI;
      string JIuGuydVCU;
      string zZqpilrtWq;
      string xwPLbNYNQa;
      string xfgeFFMTRB;
      string nmlqIsxezw;
      string RONTKNrjeg;
      string ZQFbXSrMkd;
      string YYbVDKJYDh;
      string QtOTJhSMTq;
      string NbnkbXgKSo;
      string BjsUXsmqQz;
      string DSgwQeCkRo;
      string AessQwjqse;
      string cyFNgfAsuQ;
      string uawTmturUx;
      string UwrdoVqzEa;
      string IwylVFMSPj;
      string dJpBtYiYFV;
      if(NIaNASIoLH == QtOTJhSMTq){BrVwKgGbYK = true;}
      else if(QtOTJhSMTq == NIaNASIoLH){WOaEUVpRnq = true;}
      if(ToUhhKJjLI == NbnkbXgKSo){oAnUHzcKxh = true;}
      else if(NbnkbXgKSo == ToUhhKJjLI){qrunHpTCoJ = true;}
      if(JIuGuydVCU == BjsUXsmqQz){hbbkSLFpjP = true;}
      else if(BjsUXsmqQz == JIuGuydVCU){ejKsokBFuA = true;}
      if(zZqpilrtWq == DSgwQeCkRo){mStiZQZCbo = true;}
      else if(DSgwQeCkRo == zZqpilrtWq){DwqQSbJqTx = true;}
      if(xwPLbNYNQa == AessQwjqse){yktEudUUtt = true;}
      else if(AessQwjqse == xwPLbNYNQa){XZhDJIrjVW = true;}
      if(xfgeFFMTRB == cyFNgfAsuQ){wYaXnYPkcy = true;}
      else if(cyFNgfAsuQ == xfgeFFMTRB){OpwWtlEgOj = true;}
      if(nmlqIsxezw == uawTmturUx){aPrIXVGFtp = true;}
      else if(uawTmturUx == nmlqIsxezw){UkWmntBeVe = true;}
      if(RONTKNrjeg == UwrdoVqzEa){ZZhIjwhXoo = true;}
      if(ZQFbXSrMkd == IwylVFMSPj){qkuoTNqVuA = true;}
      if(YYbVDKJYDh == dJpBtYiYFV){BnYcNiskfY = true;}
      while(UwrdoVqzEa == RONTKNrjeg){fchrlFCHjf = true;}
      while(IwylVFMSPj == IwylVFMSPj){rQjXlMAUWf = true;}
      while(dJpBtYiYFV == dJpBtYiYFV){WcbjbmCuOP = true;}
      if(BrVwKgGbYK == true){BrVwKgGbYK = false;}
      if(oAnUHzcKxh == true){oAnUHzcKxh = false;}
      if(hbbkSLFpjP == true){hbbkSLFpjP = false;}
      if(mStiZQZCbo == true){mStiZQZCbo = false;}
      if(yktEudUUtt == true){yktEudUUtt = false;}
      if(wYaXnYPkcy == true){wYaXnYPkcy = false;}
      if(aPrIXVGFtp == true){aPrIXVGFtp = false;}
      if(ZZhIjwhXoo == true){ZZhIjwhXoo = false;}
      if(qkuoTNqVuA == true){qkuoTNqVuA = false;}
      if(BnYcNiskfY == true){BnYcNiskfY = false;}
      if(WOaEUVpRnq == true){WOaEUVpRnq = false;}
      if(qrunHpTCoJ == true){qrunHpTCoJ = false;}
      if(ejKsokBFuA == true){ejKsokBFuA = false;}
      if(DwqQSbJqTx == true){DwqQSbJqTx = false;}
      if(XZhDJIrjVW == true){XZhDJIrjVW = false;}
      if(OpwWtlEgOj == true){OpwWtlEgOj = false;}
      if(UkWmntBeVe == true){UkWmntBeVe = false;}
      if(fchrlFCHjf == true){fchrlFCHjf = false;}
      if(rQjXlMAUWf == true){rQjXlMAUWf = false;}
      if(WcbjbmCuOP == true){WcbjbmCuOP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SGCXMZKTYM
{ 
  void UGnCJAKuGY()
  { 
      bool CMCUSmMgqs = false;
      bool BJnyfrdcNg = false;
      bool NcOuXDKaKa = false;
      bool zRoyewsgyT = false;
      bool fWSnUtpphd = false;
      bool CxKUlYxGwO = false;
      bool blWPtiUpSj = false;
      bool zwetApKaZd = false;
      bool NTrfYCHTLF = false;
      bool ylkiqtACtl = false;
      bool YzXyeFSQUu = false;
      bool OWgSBHtpqq = false;
      bool aBeMkMLuCG = false;
      bool pHfnENwsBS = false;
      bool jpzPqaERhi = false;
      bool zJLDKXUKMR = false;
      bool tXNNFGqrNm = false;
      bool KBoXGkCOVK = false;
      bool HsMSGfwccg = false;
      bool rlfiYMbkKj = false;
      string jsPrNJcGiY;
      string ndXbTAoTsK;
      string tcRBSGohzf;
      string HNhIJMXYmX;
      string ECGlmahUJl;
      string TNhWMGaNYG;
      string UtGCQZwOSH;
      string cPfVFqWeOr;
      string YTXNMtfKwC;
      string kJAfCKuEVM;
      string dSCCIDgMQU;
      string jwzfhAVspV;
      string skRPWTPASu;
      string uSJBOFRVEJ;
      string NTtbRoKTxB;
      string nCNzTrAlfo;
      string mgsUZRlxRc;
      string iAofIZqpxh;
      string JuCQHsEJhV;
      string EeoOVgZYBz;
      if(jsPrNJcGiY == dSCCIDgMQU){CMCUSmMgqs = true;}
      else if(dSCCIDgMQU == jsPrNJcGiY){YzXyeFSQUu = true;}
      if(ndXbTAoTsK == jwzfhAVspV){BJnyfrdcNg = true;}
      else if(jwzfhAVspV == ndXbTAoTsK){OWgSBHtpqq = true;}
      if(tcRBSGohzf == skRPWTPASu){NcOuXDKaKa = true;}
      else if(skRPWTPASu == tcRBSGohzf){aBeMkMLuCG = true;}
      if(HNhIJMXYmX == uSJBOFRVEJ){zRoyewsgyT = true;}
      else if(uSJBOFRVEJ == HNhIJMXYmX){pHfnENwsBS = true;}
      if(ECGlmahUJl == NTtbRoKTxB){fWSnUtpphd = true;}
      else if(NTtbRoKTxB == ECGlmahUJl){jpzPqaERhi = true;}
      if(TNhWMGaNYG == nCNzTrAlfo){CxKUlYxGwO = true;}
      else if(nCNzTrAlfo == TNhWMGaNYG){zJLDKXUKMR = true;}
      if(UtGCQZwOSH == mgsUZRlxRc){blWPtiUpSj = true;}
      else if(mgsUZRlxRc == UtGCQZwOSH){tXNNFGqrNm = true;}
      if(cPfVFqWeOr == iAofIZqpxh){zwetApKaZd = true;}
      if(YTXNMtfKwC == JuCQHsEJhV){NTrfYCHTLF = true;}
      if(kJAfCKuEVM == EeoOVgZYBz){ylkiqtACtl = true;}
      while(iAofIZqpxh == cPfVFqWeOr){KBoXGkCOVK = true;}
      while(JuCQHsEJhV == JuCQHsEJhV){HsMSGfwccg = true;}
      while(EeoOVgZYBz == EeoOVgZYBz){rlfiYMbkKj = true;}
      if(CMCUSmMgqs == true){CMCUSmMgqs = false;}
      if(BJnyfrdcNg == true){BJnyfrdcNg = false;}
      if(NcOuXDKaKa == true){NcOuXDKaKa = false;}
      if(zRoyewsgyT == true){zRoyewsgyT = false;}
      if(fWSnUtpphd == true){fWSnUtpphd = false;}
      if(CxKUlYxGwO == true){CxKUlYxGwO = false;}
      if(blWPtiUpSj == true){blWPtiUpSj = false;}
      if(zwetApKaZd == true){zwetApKaZd = false;}
      if(NTrfYCHTLF == true){NTrfYCHTLF = false;}
      if(ylkiqtACtl == true){ylkiqtACtl = false;}
      if(YzXyeFSQUu == true){YzXyeFSQUu = false;}
      if(OWgSBHtpqq == true){OWgSBHtpqq = false;}
      if(aBeMkMLuCG == true){aBeMkMLuCG = false;}
      if(pHfnENwsBS == true){pHfnENwsBS = false;}
      if(jpzPqaERhi == true){jpzPqaERhi = false;}
      if(zJLDKXUKMR == true){zJLDKXUKMR = false;}
      if(tXNNFGqrNm == true){tXNNFGqrNm = false;}
      if(KBoXGkCOVK == true){KBoXGkCOVK = false;}
      if(HsMSGfwccg == true){HsMSGfwccg = false;}
      if(rlfiYMbkKj == true){rlfiYMbkKj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWUHRCZKAV
{ 
  void wbczywwHPX()
  { 
      bool qCmcGgJoYE = false;
      bool WGdSjWNtoD = false;
      bool XDEPOqoAEL = false;
      bool wRqJjWxQZV = false;
      bool qLfZWKoCgX = false;
      bool npiolmxWOP = false;
      bool rIjMHFOThN = false;
      bool YwUTLMXerD = false;
      bool BlTfXGhCXw = false;
      bool ZZCKdhaTRR = false;
      bool wUTTzrUPcY = false;
      bool PRdKNFoDnB = false;
      bool WLwlmysKoc = false;
      bool lEMaHfSAgf = false;
      bool lSYygHuqwX = false;
      bool sWeQtjYhfA = false;
      bool yKZzmLFCDg = false;
      bool moWIPDmxEf = false;
      bool CCNRjOYugX = false;
      bool HjTfgasYLU = false;
      string BItCxAhrMc;
      string RXZjZdwURj;
      string xJGzLZLaIV;
      string iqIJmAgDTe;
      string XCfEEjqwrP;
      string gMJBcqBuqW;
      string oHjptZPPxY;
      string wsAlLudCta;
      string iOhroVhHfu;
      string ylLxpQSoKd;
      string UazTSmLWoh;
      string MzAPnZYqAX;
      string rHiBZKgDwu;
      string coqQGIPOYB;
      string JKRyhzlwIP;
      string qanmlMqxsI;
      string GIasFXIjJf;
      string JJRzNgpkTa;
      string YjtfDBAEes;
      string QSUQtBjYsJ;
      if(BItCxAhrMc == UazTSmLWoh){qCmcGgJoYE = true;}
      else if(UazTSmLWoh == BItCxAhrMc){wUTTzrUPcY = true;}
      if(RXZjZdwURj == MzAPnZYqAX){WGdSjWNtoD = true;}
      else if(MzAPnZYqAX == RXZjZdwURj){PRdKNFoDnB = true;}
      if(xJGzLZLaIV == rHiBZKgDwu){XDEPOqoAEL = true;}
      else if(rHiBZKgDwu == xJGzLZLaIV){WLwlmysKoc = true;}
      if(iqIJmAgDTe == coqQGIPOYB){wRqJjWxQZV = true;}
      else if(coqQGIPOYB == iqIJmAgDTe){lEMaHfSAgf = true;}
      if(XCfEEjqwrP == JKRyhzlwIP){qLfZWKoCgX = true;}
      else if(JKRyhzlwIP == XCfEEjqwrP){lSYygHuqwX = true;}
      if(gMJBcqBuqW == qanmlMqxsI){npiolmxWOP = true;}
      else if(qanmlMqxsI == gMJBcqBuqW){sWeQtjYhfA = true;}
      if(oHjptZPPxY == GIasFXIjJf){rIjMHFOThN = true;}
      else if(GIasFXIjJf == oHjptZPPxY){yKZzmLFCDg = true;}
      if(wsAlLudCta == JJRzNgpkTa){YwUTLMXerD = true;}
      if(iOhroVhHfu == YjtfDBAEes){BlTfXGhCXw = true;}
      if(ylLxpQSoKd == QSUQtBjYsJ){ZZCKdhaTRR = true;}
      while(JJRzNgpkTa == wsAlLudCta){moWIPDmxEf = true;}
      while(YjtfDBAEes == YjtfDBAEes){CCNRjOYugX = true;}
      while(QSUQtBjYsJ == QSUQtBjYsJ){HjTfgasYLU = true;}
      if(qCmcGgJoYE == true){qCmcGgJoYE = false;}
      if(WGdSjWNtoD == true){WGdSjWNtoD = false;}
      if(XDEPOqoAEL == true){XDEPOqoAEL = false;}
      if(wRqJjWxQZV == true){wRqJjWxQZV = false;}
      if(qLfZWKoCgX == true){qLfZWKoCgX = false;}
      if(npiolmxWOP == true){npiolmxWOP = false;}
      if(rIjMHFOThN == true){rIjMHFOThN = false;}
      if(YwUTLMXerD == true){YwUTLMXerD = false;}
      if(BlTfXGhCXw == true){BlTfXGhCXw = false;}
      if(ZZCKdhaTRR == true){ZZCKdhaTRR = false;}
      if(wUTTzrUPcY == true){wUTTzrUPcY = false;}
      if(PRdKNFoDnB == true){PRdKNFoDnB = false;}
      if(WLwlmysKoc == true){WLwlmysKoc = false;}
      if(lEMaHfSAgf == true){lEMaHfSAgf = false;}
      if(lSYygHuqwX == true){lSYygHuqwX = false;}
      if(sWeQtjYhfA == true){sWeQtjYhfA = false;}
      if(yKZzmLFCDg == true){yKZzmLFCDg = false;}
      if(moWIPDmxEf == true){moWIPDmxEf = false;}
      if(CCNRjOYugX == true){CCNRjOYugX = false;}
      if(HjTfgasYLU == true){HjTfgasYLU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBBQTCLUQW
{ 
  void kfFBCeFfPG()
  { 
      bool MQwSDzGlHZ = false;
      bool kUuEVieeRP = false;
      bool sZAQjfRMFr = false;
      bool nrMnezBTRp = false;
      bool ScklLgdtVP = false;
      bool kfxnDlQfhX = false;
      bool htfPlsHGYW = false;
      bool hLMbwPnNEC = false;
      bool CWpoHHtXks = false;
      bool hUktHYwVAS = false;
      bool ZXVzhYSVqm = false;
      bool xDbfVKEqHd = false;
      bool yjUfnMZSTX = false;
      bool SSMkcdBpHh = false;
      bool nXfyuesFYx = false;
      bool TFNWToCpKU = false;
      bool zACTTeppCq = false;
      bool JNiZoaEWkJ = false;
      bool SUtVENEpQn = false;
      bool bLelinUMdP = false;
      string EyePctsGeG;
      string aBOWjQyNGr;
      string WJEKzRHQLb;
      string YWkfNDudpG;
      string GpdnnlgfAB;
      string IgeAIttTPL;
      string lctDgDPiJg;
      string UUWzkgfQVM;
      string kbPKSqrkWS;
      string JaNeTduZGk;
      string WxWTfnJfOb;
      string NcyDZKMjjp;
      string LdLpXsHreH;
      string lFJkpmFuee;
      string hLWtFfcJFJ;
      string RLpQYrkfwl;
      string fRAHpITMNl;
      string FREEIzHQkq;
      string PxlVpZOsMx;
      string BYzrzPLPEw;
      if(EyePctsGeG == WxWTfnJfOb){MQwSDzGlHZ = true;}
      else if(WxWTfnJfOb == EyePctsGeG){ZXVzhYSVqm = true;}
      if(aBOWjQyNGr == NcyDZKMjjp){kUuEVieeRP = true;}
      else if(NcyDZKMjjp == aBOWjQyNGr){xDbfVKEqHd = true;}
      if(WJEKzRHQLb == LdLpXsHreH){sZAQjfRMFr = true;}
      else if(LdLpXsHreH == WJEKzRHQLb){yjUfnMZSTX = true;}
      if(YWkfNDudpG == lFJkpmFuee){nrMnezBTRp = true;}
      else if(lFJkpmFuee == YWkfNDudpG){SSMkcdBpHh = true;}
      if(GpdnnlgfAB == hLWtFfcJFJ){ScklLgdtVP = true;}
      else if(hLWtFfcJFJ == GpdnnlgfAB){nXfyuesFYx = true;}
      if(IgeAIttTPL == RLpQYrkfwl){kfxnDlQfhX = true;}
      else if(RLpQYrkfwl == IgeAIttTPL){TFNWToCpKU = true;}
      if(lctDgDPiJg == fRAHpITMNl){htfPlsHGYW = true;}
      else if(fRAHpITMNl == lctDgDPiJg){zACTTeppCq = true;}
      if(UUWzkgfQVM == FREEIzHQkq){hLMbwPnNEC = true;}
      if(kbPKSqrkWS == PxlVpZOsMx){CWpoHHtXks = true;}
      if(JaNeTduZGk == BYzrzPLPEw){hUktHYwVAS = true;}
      while(FREEIzHQkq == UUWzkgfQVM){JNiZoaEWkJ = true;}
      while(PxlVpZOsMx == PxlVpZOsMx){SUtVENEpQn = true;}
      while(BYzrzPLPEw == BYzrzPLPEw){bLelinUMdP = true;}
      if(MQwSDzGlHZ == true){MQwSDzGlHZ = false;}
      if(kUuEVieeRP == true){kUuEVieeRP = false;}
      if(sZAQjfRMFr == true){sZAQjfRMFr = false;}
      if(nrMnezBTRp == true){nrMnezBTRp = false;}
      if(ScklLgdtVP == true){ScklLgdtVP = false;}
      if(kfxnDlQfhX == true){kfxnDlQfhX = false;}
      if(htfPlsHGYW == true){htfPlsHGYW = false;}
      if(hLMbwPnNEC == true){hLMbwPnNEC = false;}
      if(CWpoHHtXks == true){CWpoHHtXks = false;}
      if(hUktHYwVAS == true){hUktHYwVAS = false;}
      if(ZXVzhYSVqm == true){ZXVzhYSVqm = false;}
      if(xDbfVKEqHd == true){xDbfVKEqHd = false;}
      if(yjUfnMZSTX == true){yjUfnMZSTX = false;}
      if(SSMkcdBpHh == true){SSMkcdBpHh = false;}
      if(nXfyuesFYx == true){nXfyuesFYx = false;}
      if(TFNWToCpKU == true){TFNWToCpKU = false;}
      if(zACTTeppCq == true){zACTTeppCq = false;}
      if(JNiZoaEWkJ == true){JNiZoaEWkJ = false;}
      if(SUtVENEpQn == true){SUtVENEpQn = false;}
      if(bLelinUMdP == true){bLelinUMdP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IBYYRMNQHJ
{ 
  void XaRDKsfdIg()
  { 
      bool NTGgVQQrJG = false;
      bool NWLrSshkNE = false;
      bool cmLIyUAaKx = false;
      bool XDbqhMqHPE = false;
      bool TWjjTMlwot = false;
      bool uPxeuZHyiA = false;
      bool PphMhKuTKG = false;
      bool BZVIjFDank = false;
      bool iDlPBHGxuH = false;
      bool EsYPodoXCJ = false;
      bool RRlisVtntp = false;
      bool WgJxQLDSKZ = false;
      bool ExXCBIBFTF = false;
      bool PfYdTQRCWf = false;
      bool NRCFkXiayc = false;
      bool ZWMbFTsjgj = false;
      bool TnUnZqHfcA = false;
      bool tBueMluSRd = false;
      bool YZHpfsSxYA = false;
      bool WhVlLYxNes = false;
      string KNVsZGQNqY;
      string pfuhPQoWGA;
      string dmHxwnioKx;
      string VWQJmOSuCC;
      string zxNOxzDDfz;
      string fuBLIXFXxl;
      string WaDtCTOkuA;
      string xsUEAgYrzw;
      string kfIKRaUFBO;
      string ItyQeYtTMd;
      string kSHfClawLb;
      string yNYBAqSrca;
      string yIjfqCuEZb;
      string mFfVKSYcIe;
      string AYtYQuVxPn;
      string FBpkfbhanz;
      string qWWiorhCph;
      string SojyaYOLPw;
      string fynkVkPtph;
      string jxoIndBKiX;
      if(KNVsZGQNqY == kSHfClawLb){NTGgVQQrJG = true;}
      else if(kSHfClawLb == KNVsZGQNqY){RRlisVtntp = true;}
      if(pfuhPQoWGA == yNYBAqSrca){NWLrSshkNE = true;}
      else if(yNYBAqSrca == pfuhPQoWGA){WgJxQLDSKZ = true;}
      if(dmHxwnioKx == yIjfqCuEZb){cmLIyUAaKx = true;}
      else if(yIjfqCuEZb == dmHxwnioKx){ExXCBIBFTF = true;}
      if(VWQJmOSuCC == mFfVKSYcIe){XDbqhMqHPE = true;}
      else if(mFfVKSYcIe == VWQJmOSuCC){PfYdTQRCWf = true;}
      if(zxNOxzDDfz == AYtYQuVxPn){TWjjTMlwot = true;}
      else if(AYtYQuVxPn == zxNOxzDDfz){NRCFkXiayc = true;}
      if(fuBLIXFXxl == FBpkfbhanz){uPxeuZHyiA = true;}
      else if(FBpkfbhanz == fuBLIXFXxl){ZWMbFTsjgj = true;}
      if(WaDtCTOkuA == qWWiorhCph){PphMhKuTKG = true;}
      else if(qWWiorhCph == WaDtCTOkuA){TnUnZqHfcA = true;}
      if(xsUEAgYrzw == SojyaYOLPw){BZVIjFDank = true;}
      if(kfIKRaUFBO == fynkVkPtph){iDlPBHGxuH = true;}
      if(ItyQeYtTMd == jxoIndBKiX){EsYPodoXCJ = true;}
      while(SojyaYOLPw == xsUEAgYrzw){tBueMluSRd = true;}
      while(fynkVkPtph == fynkVkPtph){YZHpfsSxYA = true;}
      while(jxoIndBKiX == jxoIndBKiX){WhVlLYxNes = true;}
      if(NTGgVQQrJG == true){NTGgVQQrJG = false;}
      if(NWLrSshkNE == true){NWLrSshkNE = false;}
      if(cmLIyUAaKx == true){cmLIyUAaKx = false;}
      if(XDbqhMqHPE == true){XDbqhMqHPE = false;}
      if(TWjjTMlwot == true){TWjjTMlwot = false;}
      if(uPxeuZHyiA == true){uPxeuZHyiA = false;}
      if(PphMhKuTKG == true){PphMhKuTKG = false;}
      if(BZVIjFDank == true){BZVIjFDank = false;}
      if(iDlPBHGxuH == true){iDlPBHGxuH = false;}
      if(EsYPodoXCJ == true){EsYPodoXCJ = false;}
      if(RRlisVtntp == true){RRlisVtntp = false;}
      if(WgJxQLDSKZ == true){WgJxQLDSKZ = false;}
      if(ExXCBIBFTF == true){ExXCBIBFTF = false;}
      if(PfYdTQRCWf == true){PfYdTQRCWf = false;}
      if(NRCFkXiayc == true){NRCFkXiayc = false;}
      if(ZWMbFTsjgj == true){ZWMbFTsjgj = false;}
      if(TnUnZqHfcA == true){TnUnZqHfcA = false;}
      if(tBueMluSRd == true){tBueMluSRd = false;}
      if(YZHpfsSxYA == true){YZHpfsSxYA = false;}
      if(WhVlLYxNes == true){WhVlLYxNes = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MXXPBNRNWI
{ 
  void MjLOipECDi()
  { 
      bool LUIAuUYFoJ = false;
      bool jqfWNIMZIw = false;
      bool RNwrlLKxGp = false;
      bool VRrxkTXNTR = false;
      bool KMrAgjNnkW = false;
      bool yDmXUyXPNi = false;
      bool JayymSyhls = false;
      bool jyGpkEUuKC = false;
      bool xWMjrSdUcl = false;
      bool uHzkIiNtMN = false;
      bool kfBqlzxxlP = false;
      bool ccFLlmOOGU = false;
      bool odEzyczVhB = false;
      bool pahwQQUUyr = false;
      bool UghMJSCnyU = false;
      bool UzmrYHaCsJ = false;
      bool AbPjZCtItU = false;
      bool RtQNAHuqpe = false;
      bool ZKWMgqmpXI = false;
      bool oSanrsRymG = false;
      string PYyiOWzcuJ;
      string CbDnQxZmqJ;
      string POGWpUayIi;
      string fIHBQpdjBL;
      string qoIGXXVtxm;
      string cpjqNARars;
      string wBTMcsUCWa;
      string TokeSaGAzS;
      string zgBUGpYPmQ;
      string XCqIPpUwce;
      string CTWWSmEEXl;
      string tRaZtPzyFm;
      string UEOGCQycPc;
      string FJWUPfJdBT;
      string lTqBWGaROA;
      string pVqpKyEPTC;
      string naoufjtGJN;
      string FVwkBANNjw;
      string ofOOmjSgKR;
      string atKzeKduUl;
      if(PYyiOWzcuJ == CTWWSmEEXl){LUIAuUYFoJ = true;}
      else if(CTWWSmEEXl == PYyiOWzcuJ){kfBqlzxxlP = true;}
      if(CbDnQxZmqJ == tRaZtPzyFm){jqfWNIMZIw = true;}
      else if(tRaZtPzyFm == CbDnQxZmqJ){ccFLlmOOGU = true;}
      if(POGWpUayIi == UEOGCQycPc){RNwrlLKxGp = true;}
      else if(UEOGCQycPc == POGWpUayIi){odEzyczVhB = true;}
      if(fIHBQpdjBL == FJWUPfJdBT){VRrxkTXNTR = true;}
      else if(FJWUPfJdBT == fIHBQpdjBL){pahwQQUUyr = true;}
      if(qoIGXXVtxm == lTqBWGaROA){KMrAgjNnkW = true;}
      else if(lTqBWGaROA == qoIGXXVtxm){UghMJSCnyU = true;}
      if(cpjqNARars == pVqpKyEPTC){yDmXUyXPNi = true;}
      else if(pVqpKyEPTC == cpjqNARars){UzmrYHaCsJ = true;}
      if(wBTMcsUCWa == naoufjtGJN){JayymSyhls = true;}
      else if(naoufjtGJN == wBTMcsUCWa){AbPjZCtItU = true;}
      if(TokeSaGAzS == FVwkBANNjw){jyGpkEUuKC = true;}
      if(zgBUGpYPmQ == ofOOmjSgKR){xWMjrSdUcl = true;}
      if(XCqIPpUwce == atKzeKduUl){uHzkIiNtMN = true;}
      while(FVwkBANNjw == TokeSaGAzS){RtQNAHuqpe = true;}
      while(ofOOmjSgKR == ofOOmjSgKR){ZKWMgqmpXI = true;}
      while(atKzeKduUl == atKzeKduUl){oSanrsRymG = true;}
      if(LUIAuUYFoJ == true){LUIAuUYFoJ = false;}
      if(jqfWNIMZIw == true){jqfWNIMZIw = false;}
      if(RNwrlLKxGp == true){RNwrlLKxGp = false;}
      if(VRrxkTXNTR == true){VRrxkTXNTR = false;}
      if(KMrAgjNnkW == true){KMrAgjNnkW = false;}
      if(yDmXUyXPNi == true){yDmXUyXPNi = false;}
      if(JayymSyhls == true){JayymSyhls = false;}
      if(jyGpkEUuKC == true){jyGpkEUuKC = false;}
      if(xWMjrSdUcl == true){xWMjrSdUcl = false;}
      if(uHzkIiNtMN == true){uHzkIiNtMN = false;}
      if(kfBqlzxxlP == true){kfBqlzxxlP = false;}
      if(ccFLlmOOGU == true){ccFLlmOOGU = false;}
      if(odEzyczVhB == true){odEzyczVhB = false;}
      if(pahwQQUUyr == true){pahwQQUUyr = false;}
      if(UghMJSCnyU == true){UghMJSCnyU = false;}
      if(UzmrYHaCsJ == true){UzmrYHaCsJ = false;}
      if(AbPjZCtItU == true){AbPjZCtItU = false;}
      if(RtQNAHuqpe == true){RtQNAHuqpe = false;}
      if(ZKWMgqmpXI == true){ZKWMgqmpXI = false;}
      if(oSanrsRymG == true){oSanrsRymG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSBQSGOAXD
{ 
  void uJyYaOJIjq()
  { 
      bool rukigeUJrz = false;
      bool CwBauiDnFY = false;
      bool YuHOAaodGr = false;
      bool uPWHXnXrBU = false;
      bool uxbQaQgInj = false;
      bool QtiKWwnVhF = false;
      bool pqCzEmZtDG = false;
      bool KKmjdbTqni = false;
      bool tfpVaAfMka = false;
      bool ABJueEtbLn = false;
      bool qlFgYGHzft = false;
      bool cxhzKJAgXE = false;
      bool GNJbGIAqFZ = false;
      bool hrezrIZIwU = false;
      bool rgfpxDTKjU = false;
      bool DMDHgcccaQ = false;
      bool FQsGMkRiHC = false;
      bool iqjDLZgSeC = false;
      bool opGkVUnWRO = false;
      bool exhfPamZdM = false;
      string sCQLzySnuX;
      string pZHEBiPHTB;
      string BMWxuWfcNQ;
      string IHWPddAWFG;
      string snAfsHYJmQ;
      string YFHSCgfSQc;
      string SpadOhCraW;
      string isCMIMLpDn;
      string xVpxrCAENw;
      string ygFcmDNVQL;
      string EgiPgfDuKo;
      string UoObewzdlL;
      string hyddYBmYYE;
      string zpZrjQmaPL;
      string zEtYaIRdxq;
      string EiiFcGCEqf;
      string reVFoePWrO;
      string JYNZMdDFDP;
      string jJbhAPGTPc;
      string NhijTTiniu;
      if(sCQLzySnuX == EgiPgfDuKo){rukigeUJrz = true;}
      else if(EgiPgfDuKo == sCQLzySnuX){qlFgYGHzft = true;}
      if(pZHEBiPHTB == UoObewzdlL){CwBauiDnFY = true;}
      else if(UoObewzdlL == pZHEBiPHTB){cxhzKJAgXE = true;}
      if(BMWxuWfcNQ == hyddYBmYYE){YuHOAaodGr = true;}
      else if(hyddYBmYYE == BMWxuWfcNQ){GNJbGIAqFZ = true;}
      if(IHWPddAWFG == zpZrjQmaPL){uPWHXnXrBU = true;}
      else if(zpZrjQmaPL == IHWPddAWFG){hrezrIZIwU = true;}
      if(snAfsHYJmQ == zEtYaIRdxq){uxbQaQgInj = true;}
      else if(zEtYaIRdxq == snAfsHYJmQ){rgfpxDTKjU = true;}
      if(YFHSCgfSQc == EiiFcGCEqf){QtiKWwnVhF = true;}
      else if(EiiFcGCEqf == YFHSCgfSQc){DMDHgcccaQ = true;}
      if(SpadOhCraW == reVFoePWrO){pqCzEmZtDG = true;}
      else if(reVFoePWrO == SpadOhCraW){FQsGMkRiHC = true;}
      if(isCMIMLpDn == JYNZMdDFDP){KKmjdbTqni = true;}
      if(xVpxrCAENw == jJbhAPGTPc){tfpVaAfMka = true;}
      if(ygFcmDNVQL == NhijTTiniu){ABJueEtbLn = true;}
      while(JYNZMdDFDP == isCMIMLpDn){iqjDLZgSeC = true;}
      while(jJbhAPGTPc == jJbhAPGTPc){opGkVUnWRO = true;}
      while(NhijTTiniu == NhijTTiniu){exhfPamZdM = true;}
      if(rukigeUJrz == true){rukigeUJrz = false;}
      if(CwBauiDnFY == true){CwBauiDnFY = false;}
      if(YuHOAaodGr == true){YuHOAaodGr = false;}
      if(uPWHXnXrBU == true){uPWHXnXrBU = false;}
      if(uxbQaQgInj == true){uxbQaQgInj = false;}
      if(QtiKWwnVhF == true){QtiKWwnVhF = false;}
      if(pqCzEmZtDG == true){pqCzEmZtDG = false;}
      if(KKmjdbTqni == true){KKmjdbTqni = false;}
      if(tfpVaAfMka == true){tfpVaAfMka = false;}
      if(ABJueEtbLn == true){ABJueEtbLn = false;}
      if(qlFgYGHzft == true){qlFgYGHzft = false;}
      if(cxhzKJAgXE == true){cxhzKJAgXE = false;}
      if(GNJbGIAqFZ == true){GNJbGIAqFZ = false;}
      if(hrezrIZIwU == true){hrezrIZIwU = false;}
      if(rgfpxDTKjU == true){rgfpxDTKjU = false;}
      if(DMDHgcccaQ == true){DMDHgcccaQ = false;}
      if(FQsGMkRiHC == true){FQsGMkRiHC = false;}
      if(iqjDLZgSeC == true){iqjDLZgSeC = false;}
      if(opGkVUnWRO == true){opGkVUnWRO = false;}
      if(exhfPamZdM == true){exhfPamZdM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JZNOUMEJTC
{ 
  void puYIuiHtjw()
  { 
      bool nmhRFhVkNh = false;
      bool IrRrhLMWuM = false;
      bool uQrCmqoDfd = false;
      bool scJYamjEwa = false;
      bool xuPZUjkktK = false;
      bool KrswHWtfdO = false;
      bool rREiofhsRu = false;
      bool aIZTPAARgD = false;
      bool FDJUTAiMQD = false;
      bool rEZhhepgjo = false;
      bool BrTzjBSYgH = false;
      bool WczaInIjPo = false;
      bool wVcNCWirlj = false;
      bool JTgrBNjKkR = false;
      bool gJfIgPFzYs = false;
      bool WGQurfPGwM = false;
      bool SamxyDuGYu = false;
      bool ExyxHmoTgm = false;
      bool RiTrMCClzV = false;
      bool xdOXzGWiJc = false;
      string epZOEfCwPW;
      string sDrcpZAsXO;
      string cTmmpnpJaA;
      string VglmoXZWCf;
      string ynHXABbpVU;
      string ocRerKCmYQ;
      string prVOAMRFmR;
      string AdpqPoMPmn;
      string LznFLsOHtd;
      string UmxlpFSrWn;
      string jWCDUKlaOD;
      string xmzjEpDQDH;
      string xJKIwMfDBK;
      string VUrzEnwkjA;
      string GnrqfhmNhz;
      string BCnOqZLtGH;
      string diYDgctAfP;
      string sSfCBIRTbO;
      string ZSVCITgdId;
      string bCdbWXPnJD;
      if(epZOEfCwPW == jWCDUKlaOD){nmhRFhVkNh = true;}
      else if(jWCDUKlaOD == epZOEfCwPW){BrTzjBSYgH = true;}
      if(sDrcpZAsXO == xmzjEpDQDH){IrRrhLMWuM = true;}
      else if(xmzjEpDQDH == sDrcpZAsXO){WczaInIjPo = true;}
      if(cTmmpnpJaA == xJKIwMfDBK){uQrCmqoDfd = true;}
      else if(xJKIwMfDBK == cTmmpnpJaA){wVcNCWirlj = true;}
      if(VglmoXZWCf == VUrzEnwkjA){scJYamjEwa = true;}
      else if(VUrzEnwkjA == VglmoXZWCf){JTgrBNjKkR = true;}
      if(ynHXABbpVU == GnrqfhmNhz){xuPZUjkktK = true;}
      else if(GnrqfhmNhz == ynHXABbpVU){gJfIgPFzYs = true;}
      if(ocRerKCmYQ == BCnOqZLtGH){KrswHWtfdO = true;}
      else if(BCnOqZLtGH == ocRerKCmYQ){WGQurfPGwM = true;}
      if(prVOAMRFmR == diYDgctAfP){rREiofhsRu = true;}
      else if(diYDgctAfP == prVOAMRFmR){SamxyDuGYu = true;}
      if(AdpqPoMPmn == sSfCBIRTbO){aIZTPAARgD = true;}
      if(LznFLsOHtd == ZSVCITgdId){FDJUTAiMQD = true;}
      if(UmxlpFSrWn == bCdbWXPnJD){rEZhhepgjo = true;}
      while(sSfCBIRTbO == AdpqPoMPmn){ExyxHmoTgm = true;}
      while(ZSVCITgdId == ZSVCITgdId){RiTrMCClzV = true;}
      while(bCdbWXPnJD == bCdbWXPnJD){xdOXzGWiJc = true;}
      if(nmhRFhVkNh == true){nmhRFhVkNh = false;}
      if(IrRrhLMWuM == true){IrRrhLMWuM = false;}
      if(uQrCmqoDfd == true){uQrCmqoDfd = false;}
      if(scJYamjEwa == true){scJYamjEwa = false;}
      if(xuPZUjkktK == true){xuPZUjkktK = false;}
      if(KrswHWtfdO == true){KrswHWtfdO = false;}
      if(rREiofhsRu == true){rREiofhsRu = false;}
      if(aIZTPAARgD == true){aIZTPAARgD = false;}
      if(FDJUTAiMQD == true){FDJUTAiMQD = false;}
      if(rEZhhepgjo == true){rEZhhepgjo = false;}
      if(BrTzjBSYgH == true){BrTzjBSYgH = false;}
      if(WczaInIjPo == true){WczaInIjPo = false;}
      if(wVcNCWirlj == true){wVcNCWirlj = false;}
      if(JTgrBNjKkR == true){JTgrBNjKkR = false;}
      if(gJfIgPFzYs == true){gJfIgPFzYs = false;}
      if(WGQurfPGwM == true){WGQurfPGwM = false;}
      if(SamxyDuGYu == true){SamxyDuGYu = false;}
      if(ExyxHmoTgm == true){ExyxHmoTgm = false;}
      if(RiTrMCClzV == true){RiTrMCClzV = false;}
      if(xdOXzGWiJc == true){xdOXzGWiJc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NIVOIOLQFY
{ 
  void mLMlefTdGg()
  { 
      bool AZFflodHoI = false;
      bool WXaaCVSsjC = false;
      bool nBICbhlWJP = false;
      bool WiKtpwekaM = false;
      bool qfruBTrhQU = false;
      bool dPQiTzRCED = false;
      bool DHyZlmMgjF = false;
      bool qgRWKIINBI = false;
      bool pDGnlHSbZq = false;
      bool ecgXJjhRJN = false;
      bool GKxKdwxsYK = false;
      bool pEAuNzBKmd = false;
      bool UkHsZNAtMa = false;
      bool aqDnBfGuJp = false;
      bool JYDOBackKK = false;
      bool iXeesVDEkQ = false;
      bool uDfxjzALth = false;
      bool rGAxUuhrqz = false;
      bool kPjCqDMYuf = false;
      bool bCJstGrFeC = false;
      string BrDtQndROM;
      string cNFhVXMDkq;
      string xaxXaubmJw;
      string kNdakuWHDy;
      string yHXUxPGNSj;
      string bCsRCateTV;
      string MqHRaPjewZ;
      string BEAlsoCcaL;
      string nNTZUiULXJ;
      string AqnhlGAFsh;
      string fbQrhWCGYN;
      string YREHgyWgxr;
      string tXGmZJQSAl;
      string owirfMxbqx;
      string fOmJkilfAm;
      string jTIBnHUdSY;
      string GjFlXchMaT;
      string BuoALejwCq;
      string WjRMCVngDX;
      string rTJSqwIAlI;
      if(BrDtQndROM == fbQrhWCGYN){AZFflodHoI = true;}
      else if(fbQrhWCGYN == BrDtQndROM){GKxKdwxsYK = true;}
      if(cNFhVXMDkq == YREHgyWgxr){WXaaCVSsjC = true;}
      else if(YREHgyWgxr == cNFhVXMDkq){pEAuNzBKmd = true;}
      if(xaxXaubmJw == tXGmZJQSAl){nBICbhlWJP = true;}
      else if(tXGmZJQSAl == xaxXaubmJw){UkHsZNAtMa = true;}
      if(kNdakuWHDy == owirfMxbqx){WiKtpwekaM = true;}
      else if(owirfMxbqx == kNdakuWHDy){aqDnBfGuJp = true;}
      if(yHXUxPGNSj == fOmJkilfAm){qfruBTrhQU = true;}
      else if(fOmJkilfAm == yHXUxPGNSj){JYDOBackKK = true;}
      if(bCsRCateTV == jTIBnHUdSY){dPQiTzRCED = true;}
      else if(jTIBnHUdSY == bCsRCateTV){iXeesVDEkQ = true;}
      if(MqHRaPjewZ == GjFlXchMaT){DHyZlmMgjF = true;}
      else if(GjFlXchMaT == MqHRaPjewZ){uDfxjzALth = true;}
      if(BEAlsoCcaL == BuoALejwCq){qgRWKIINBI = true;}
      if(nNTZUiULXJ == WjRMCVngDX){pDGnlHSbZq = true;}
      if(AqnhlGAFsh == rTJSqwIAlI){ecgXJjhRJN = true;}
      while(BuoALejwCq == BEAlsoCcaL){rGAxUuhrqz = true;}
      while(WjRMCVngDX == WjRMCVngDX){kPjCqDMYuf = true;}
      while(rTJSqwIAlI == rTJSqwIAlI){bCJstGrFeC = true;}
      if(AZFflodHoI == true){AZFflodHoI = false;}
      if(WXaaCVSsjC == true){WXaaCVSsjC = false;}
      if(nBICbhlWJP == true){nBICbhlWJP = false;}
      if(WiKtpwekaM == true){WiKtpwekaM = false;}
      if(qfruBTrhQU == true){qfruBTrhQU = false;}
      if(dPQiTzRCED == true){dPQiTzRCED = false;}
      if(DHyZlmMgjF == true){DHyZlmMgjF = false;}
      if(qgRWKIINBI == true){qgRWKIINBI = false;}
      if(pDGnlHSbZq == true){pDGnlHSbZq = false;}
      if(ecgXJjhRJN == true){ecgXJjhRJN = false;}
      if(GKxKdwxsYK == true){GKxKdwxsYK = false;}
      if(pEAuNzBKmd == true){pEAuNzBKmd = false;}
      if(UkHsZNAtMa == true){UkHsZNAtMa = false;}
      if(aqDnBfGuJp == true){aqDnBfGuJp = false;}
      if(JYDOBackKK == true){JYDOBackKK = false;}
      if(iXeesVDEkQ == true){iXeesVDEkQ = false;}
      if(uDfxjzALth == true){uDfxjzALth = false;}
      if(rGAxUuhrqz == true){rGAxUuhrqz = false;}
      if(kPjCqDMYuf == true){kPjCqDMYuf = false;}
      if(bCJstGrFeC == true){bCJstGrFeC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCLYZMIQNT
{ 
  void nXSQjybcLM()
  { 
      bool fPGIlEELyw = false;
      bool QEUqYcDBug = false;
      bool yZxsBSSkPA = false;
      bool rxLOxhuMjp = false;
      bool wsxbNQYHqQ = false;
      bool dwEEhGRMHS = false;
      bool lSwxDSrFtp = false;
      bool hpQEjEbUfj = false;
      bool tKtyWwsHfp = false;
      bool PhFREcwAYt = false;
      bool XTNAimeAUc = false;
      bool exgWXbYxaH = false;
      bool ZkYDazkyzG = false;
      bool HawkLawtPi = false;
      bool QrlDLSAhtc = false;
      bool DzYRTmtKYi = false;
      bool CfANUDAuKx = false;
      bool eehrphyVqH = false;
      bool zDEWCIBeRY = false;
      bool flUffkrXhH = false;
      string sWOwLMGfer;
      string WYNAVGgemr;
      string UqebkclzAQ;
      string aykqMqEGGw;
      string QXPjVpnheH;
      string ixjkkCrmLh;
      string aHfNQYmWnd;
      string BZYqbxatGu;
      string oDUrgdNzGJ;
      string zRuXVJqBSw;
      string CRtAGJYsJm;
      string axfQsWlmgm;
      string KnPdeieAUS;
      string FYbJsWJUlX;
      string FUpSiBldey;
      string WEUfkOBPUW;
      string dXXpgCVVXV;
      string MRAJhoxxuc;
      string xBUVuAEwXd;
      string UszPsgxzkf;
      if(sWOwLMGfer == CRtAGJYsJm){fPGIlEELyw = true;}
      else if(CRtAGJYsJm == sWOwLMGfer){XTNAimeAUc = true;}
      if(WYNAVGgemr == axfQsWlmgm){QEUqYcDBug = true;}
      else if(axfQsWlmgm == WYNAVGgemr){exgWXbYxaH = true;}
      if(UqebkclzAQ == KnPdeieAUS){yZxsBSSkPA = true;}
      else if(KnPdeieAUS == UqebkclzAQ){ZkYDazkyzG = true;}
      if(aykqMqEGGw == FYbJsWJUlX){rxLOxhuMjp = true;}
      else if(FYbJsWJUlX == aykqMqEGGw){HawkLawtPi = true;}
      if(QXPjVpnheH == FUpSiBldey){wsxbNQYHqQ = true;}
      else if(FUpSiBldey == QXPjVpnheH){QrlDLSAhtc = true;}
      if(ixjkkCrmLh == WEUfkOBPUW){dwEEhGRMHS = true;}
      else if(WEUfkOBPUW == ixjkkCrmLh){DzYRTmtKYi = true;}
      if(aHfNQYmWnd == dXXpgCVVXV){lSwxDSrFtp = true;}
      else if(dXXpgCVVXV == aHfNQYmWnd){CfANUDAuKx = true;}
      if(BZYqbxatGu == MRAJhoxxuc){hpQEjEbUfj = true;}
      if(oDUrgdNzGJ == xBUVuAEwXd){tKtyWwsHfp = true;}
      if(zRuXVJqBSw == UszPsgxzkf){PhFREcwAYt = true;}
      while(MRAJhoxxuc == BZYqbxatGu){eehrphyVqH = true;}
      while(xBUVuAEwXd == xBUVuAEwXd){zDEWCIBeRY = true;}
      while(UszPsgxzkf == UszPsgxzkf){flUffkrXhH = true;}
      if(fPGIlEELyw == true){fPGIlEELyw = false;}
      if(QEUqYcDBug == true){QEUqYcDBug = false;}
      if(yZxsBSSkPA == true){yZxsBSSkPA = false;}
      if(rxLOxhuMjp == true){rxLOxhuMjp = false;}
      if(wsxbNQYHqQ == true){wsxbNQYHqQ = false;}
      if(dwEEhGRMHS == true){dwEEhGRMHS = false;}
      if(lSwxDSrFtp == true){lSwxDSrFtp = false;}
      if(hpQEjEbUfj == true){hpQEjEbUfj = false;}
      if(tKtyWwsHfp == true){tKtyWwsHfp = false;}
      if(PhFREcwAYt == true){PhFREcwAYt = false;}
      if(XTNAimeAUc == true){XTNAimeAUc = false;}
      if(exgWXbYxaH == true){exgWXbYxaH = false;}
      if(ZkYDazkyzG == true){ZkYDazkyzG = false;}
      if(HawkLawtPi == true){HawkLawtPi = false;}
      if(QrlDLSAhtc == true){QrlDLSAhtc = false;}
      if(DzYRTmtKYi == true){DzYRTmtKYi = false;}
      if(CfANUDAuKx == true){CfANUDAuKx = false;}
      if(eehrphyVqH == true){eehrphyVqH = false;}
      if(zDEWCIBeRY == true){zDEWCIBeRY = false;}
      if(flUffkrXhH == true){flUffkrXhH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUMHNWHJGT
{ 
  void seINIhkSXg()
  { 
      bool CemEHGDhnd = false;
      bool ZxGAaWqrVx = false;
      bool IbGyMIhzqt = false;
      bool cMgqOxeGmQ = false;
      bool SUlAgnqnym = false;
      bool OSlStaYory = false;
      bool XDqsBNPPkd = false;
      bool rjFFdmoFQX = false;
      bool QtBEfJZNwm = false;
      bool XpOnrOdszT = false;
      bool XbCTtdMfoH = false;
      bool lSXTgdClNq = false;
      bool mCSyFBURNO = false;
      bool IwGwzoqgJB = false;
      bool wsYoBERtGN = false;
      bool MreHgVIEOs = false;
      bool JuSZypMbUr = false;
      bool mUcLtscdwA = false;
      bool jaKzBQQzOc = false;
      bool flSQrBazqL = false;
      string cKMnTyyuKM;
      string rWmFoTqYHo;
      string rGigJalaPK;
      string iOBBixcebf;
      string fMjYgnPdfn;
      string LMVEyVafdr;
      string MXfzddUkVr;
      string pLwbJfWJzV;
      string LHtbzWrxDN;
      string VwBiTHgjuD;
      string SdInxAPtuS;
      string yQgIfFdDAG;
      string kXhIVsKNHB;
      string zmOwChyGdz;
      string HxCjOEPrCN;
      string dcinRuuARE;
      string oBlsTLCjFy;
      string GWZBznUysQ;
      string cRKtWVDadH;
      string lyoZJFLIQC;
      if(cKMnTyyuKM == SdInxAPtuS){CemEHGDhnd = true;}
      else if(SdInxAPtuS == cKMnTyyuKM){XbCTtdMfoH = true;}
      if(rWmFoTqYHo == yQgIfFdDAG){ZxGAaWqrVx = true;}
      else if(yQgIfFdDAG == rWmFoTqYHo){lSXTgdClNq = true;}
      if(rGigJalaPK == kXhIVsKNHB){IbGyMIhzqt = true;}
      else if(kXhIVsKNHB == rGigJalaPK){mCSyFBURNO = true;}
      if(iOBBixcebf == zmOwChyGdz){cMgqOxeGmQ = true;}
      else if(zmOwChyGdz == iOBBixcebf){IwGwzoqgJB = true;}
      if(fMjYgnPdfn == HxCjOEPrCN){SUlAgnqnym = true;}
      else if(HxCjOEPrCN == fMjYgnPdfn){wsYoBERtGN = true;}
      if(LMVEyVafdr == dcinRuuARE){OSlStaYory = true;}
      else if(dcinRuuARE == LMVEyVafdr){MreHgVIEOs = true;}
      if(MXfzddUkVr == oBlsTLCjFy){XDqsBNPPkd = true;}
      else if(oBlsTLCjFy == MXfzddUkVr){JuSZypMbUr = true;}
      if(pLwbJfWJzV == GWZBznUysQ){rjFFdmoFQX = true;}
      if(LHtbzWrxDN == cRKtWVDadH){QtBEfJZNwm = true;}
      if(VwBiTHgjuD == lyoZJFLIQC){XpOnrOdszT = true;}
      while(GWZBznUysQ == pLwbJfWJzV){mUcLtscdwA = true;}
      while(cRKtWVDadH == cRKtWVDadH){jaKzBQQzOc = true;}
      while(lyoZJFLIQC == lyoZJFLIQC){flSQrBazqL = true;}
      if(CemEHGDhnd == true){CemEHGDhnd = false;}
      if(ZxGAaWqrVx == true){ZxGAaWqrVx = false;}
      if(IbGyMIhzqt == true){IbGyMIhzqt = false;}
      if(cMgqOxeGmQ == true){cMgqOxeGmQ = false;}
      if(SUlAgnqnym == true){SUlAgnqnym = false;}
      if(OSlStaYory == true){OSlStaYory = false;}
      if(XDqsBNPPkd == true){XDqsBNPPkd = false;}
      if(rjFFdmoFQX == true){rjFFdmoFQX = false;}
      if(QtBEfJZNwm == true){QtBEfJZNwm = false;}
      if(XpOnrOdszT == true){XpOnrOdszT = false;}
      if(XbCTtdMfoH == true){XbCTtdMfoH = false;}
      if(lSXTgdClNq == true){lSXTgdClNq = false;}
      if(mCSyFBURNO == true){mCSyFBURNO = false;}
      if(IwGwzoqgJB == true){IwGwzoqgJB = false;}
      if(wsYoBERtGN == true){wsYoBERtGN = false;}
      if(MreHgVIEOs == true){MreHgVIEOs = false;}
      if(JuSZypMbUr == true){JuSZypMbUr = false;}
      if(mUcLtscdwA == true){mUcLtscdwA = false;}
      if(jaKzBQQzOc == true){jaKzBQQzOc = false;}
      if(flSQrBazqL == true){flSQrBazqL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PSBKAZSKLH
{ 
  void lTBmGFoZtt()
  { 
      bool QUCQWnAIxq = false;
      bool AABRVshKeb = false;
      bool iWakXNPXRM = false;
      bool dzpGYIgjqT = false;
      bool jXkJauTwJH = false;
      bool lNeKLssRrJ = false;
      bool XbpkNBKtrN = false;
      bool MxSLqLkQJc = false;
      bool sSOKaPUete = false;
      bool POrguHgAwZ = false;
      bool kYDwtntSSA = false;
      bool HcHPPFNfJx = false;
      bool fezMyxFlQi = false;
      bool dkUjqTPRPl = false;
      bool UCLtXmHbRo = false;
      bool tBqysFYpyx = false;
      bool iIBjWWIWYu = false;
      bool ouPWbdTFoL = false;
      bool pdTaocsVqk = false;
      bool tYTSDMAbXB = false;
      string VCoikmyRyc;
      string AQDluicYhl;
      string ENDYgMuMct;
      string RLDbqplPFD;
      string zcdZidgJYW;
      string npWwbHyPCY;
      string qkoDKnNbuF;
      string xMTelbicpD;
      string elnFFaoGzi;
      string rVNfLNmZOt;
      string QFOTZbWrKA;
      string YUYytFxixj;
      string zGbLMaymTX;
      string nINwlZXUfd;
      string DxwzKWxOkF;
      string QDbetKcCGz;
      string cjYlMPGcMU;
      string hcDTgCJcBo;
      string ciBNHjfiBb;
      string wUNfBTYJmt;
      if(VCoikmyRyc == QFOTZbWrKA){QUCQWnAIxq = true;}
      else if(QFOTZbWrKA == VCoikmyRyc){kYDwtntSSA = true;}
      if(AQDluicYhl == YUYytFxixj){AABRVshKeb = true;}
      else if(YUYytFxixj == AQDluicYhl){HcHPPFNfJx = true;}
      if(ENDYgMuMct == zGbLMaymTX){iWakXNPXRM = true;}
      else if(zGbLMaymTX == ENDYgMuMct){fezMyxFlQi = true;}
      if(RLDbqplPFD == nINwlZXUfd){dzpGYIgjqT = true;}
      else if(nINwlZXUfd == RLDbqplPFD){dkUjqTPRPl = true;}
      if(zcdZidgJYW == DxwzKWxOkF){jXkJauTwJH = true;}
      else if(DxwzKWxOkF == zcdZidgJYW){UCLtXmHbRo = true;}
      if(npWwbHyPCY == QDbetKcCGz){lNeKLssRrJ = true;}
      else if(QDbetKcCGz == npWwbHyPCY){tBqysFYpyx = true;}
      if(qkoDKnNbuF == cjYlMPGcMU){XbpkNBKtrN = true;}
      else if(cjYlMPGcMU == qkoDKnNbuF){iIBjWWIWYu = true;}
      if(xMTelbicpD == hcDTgCJcBo){MxSLqLkQJc = true;}
      if(elnFFaoGzi == ciBNHjfiBb){sSOKaPUete = true;}
      if(rVNfLNmZOt == wUNfBTYJmt){POrguHgAwZ = true;}
      while(hcDTgCJcBo == xMTelbicpD){ouPWbdTFoL = true;}
      while(ciBNHjfiBb == ciBNHjfiBb){pdTaocsVqk = true;}
      while(wUNfBTYJmt == wUNfBTYJmt){tYTSDMAbXB = true;}
      if(QUCQWnAIxq == true){QUCQWnAIxq = false;}
      if(AABRVshKeb == true){AABRVshKeb = false;}
      if(iWakXNPXRM == true){iWakXNPXRM = false;}
      if(dzpGYIgjqT == true){dzpGYIgjqT = false;}
      if(jXkJauTwJH == true){jXkJauTwJH = false;}
      if(lNeKLssRrJ == true){lNeKLssRrJ = false;}
      if(XbpkNBKtrN == true){XbpkNBKtrN = false;}
      if(MxSLqLkQJc == true){MxSLqLkQJc = false;}
      if(sSOKaPUete == true){sSOKaPUete = false;}
      if(POrguHgAwZ == true){POrguHgAwZ = false;}
      if(kYDwtntSSA == true){kYDwtntSSA = false;}
      if(HcHPPFNfJx == true){HcHPPFNfJx = false;}
      if(fezMyxFlQi == true){fezMyxFlQi = false;}
      if(dkUjqTPRPl == true){dkUjqTPRPl = false;}
      if(UCLtXmHbRo == true){UCLtXmHbRo = false;}
      if(tBqysFYpyx == true){tBqysFYpyx = false;}
      if(iIBjWWIWYu == true){iIBjWWIWYu = false;}
      if(ouPWbdTFoL == true){ouPWbdTFoL = false;}
      if(pdTaocsVqk == true){pdTaocsVqk = false;}
      if(tYTSDMAbXB == true){tYTSDMAbXB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFCTZFKOWL
{ 
  void tBeJMbpkEX()
  { 
      bool euNayUXkXL = false;
      bool DCgegluTsB = false;
      bool GqXDJjkQMw = false;
      bool RbfkDVKdMD = false;
      bool sgNaBSIVSA = false;
      bool PDRcmmWKRO = false;
      bool jGXasbWuaK = false;
      bool bQGoIZdxBp = false;
      bool bOxLfOJDxP = false;
      bool zAMyTlIlgZ = false;
      bool wMtHYzwbTM = false;
      bool JZIamUIMud = false;
      bool RSyLLbEIUV = false;
      bool RqPbtOTpmg = false;
      bool SgikGYqlLy = false;
      bool cuqDHcOiwx = false;
      bool tmGxtRJfgX = false;
      bool ASZOLjiNEl = false;
      bool jSxVsWAMUQ = false;
      bool AktpleZkpn = false;
      string QWIAYuXIWO;
      string YFqnCNsSVI;
      string FKMexGJIWY;
      string TQNKyLjalk;
      string VrduzxBzsA;
      string WszkmGKdCR;
      string kPlxuHqfpq;
      string dSfjlMgQeA;
      string EKPVBZQbXr;
      string BFXTzGFfAq;
      string FVJCWEMPyZ;
      string YszCNazQwU;
      string pPIxoXtLjf;
      string GBQmtiBNzx;
      string MBcxSHGVGY;
      string GoieApMLMy;
      string KBeSSXcLHe;
      string ZlRyHolKeh;
      string RXFLYRRkmE;
      string VoAAlLWKdt;
      if(QWIAYuXIWO == FVJCWEMPyZ){euNayUXkXL = true;}
      else if(FVJCWEMPyZ == QWIAYuXIWO){wMtHYzwbTM = true;}
      if(YFqnCNsSVI == YszCNazQwU){DCgegluTsB = true;}
      else if(YszCNazQwU == YFqnCNsSVI){JZIamUIMud = true;}
      if(FKMexGJIWY == pPIxoXtLjf){GqXDJjkQMw = true;}
      else if(pPIxoXtLjf == FKMexGJIWY){RSyLLbEIUV = true;}
      if(TQNKyLjalk == GBQmtiBNzx){RbfkDVKdMD = true;}
      else if(GBQmtiBNzx == TQNKyLjalk){RqPbtOTpmg = true;}
      if(VrduzxBzsA == MBcxSHGVGY){sgNaBSIVSA = true;}
      else if(MBcxSHGVGY == VrduzxBzsA){SgikGYqlLy = true;}
      if(WszkmGKdCR == GoieApMLMy){PDRcmmWKRO = true;}
      else if(GoieApMLMy == WszkmGKdCR){cuqDHcOiwx = true;}
      if(kPlxuHqfpq == KBeSSXcLHe){jGXasbWuaK = true;}
      else if(KBeSSXcLHe == kPlxuHqfpq){tmGxtRJfgX = true;}
      if(dSfjlMgQeA == ZlRyHolKeh){bQGoIZdxBp = true;}
      if(EKPVBZQbXr == RXFLYRRkmE){bOxLfOJDxP = true;}
      if(BFXTzGFfAq == VoAAlLWKdt){zAMyTlIlgZ = true;}
      while(ZlRyHolKeh == dSfjlMgQeA){ASZOLjiNEl = true;}
      while(RXFLYRRkmE == RXFLYRRkmE){jSxVsWAMUQ = true;}
      while(VoAAlLWKdt == VoAAlLWKdt){AktpleZkpn = true;}
      if(euNayUXkXL == true){euNayUXkXL = false;}
      if(DCgegluTsB == true){DCgegluTsB = false;}
      if(GqXDJjkQMw == true){GqXDJjkQMw = false;}
      if(RbfkDVKdMD == true){RbfkDVKdMD = false;}
      if(sgNaBSIVSA == true){sgNaBSIVSA = false;}
      if(PDRcmmWKRO == true){PDRcmmWKRO = false;}
      if(jGXasbWuaK == true){jGXasbWuaK = false;}
      if(bQGoIZdxBp == true){bQGoIZdxBp = false;}
      if(bOxLfOJDxP == true){bOxLfOJDxP = false;}
      if(zAMyTlIlgZ == true){zAMyTlIlgZ = false;}
      if(wMtHYzwbTM == true){wMtHYzwbTM = false;}
      if(JZIamUIMud == true){JZIamUIMud = false;}
      if(RSyLLbEIUV == true){RSyLLbEIUV = false;}
      if(RqPbtOTpmg == true){RqPbtOTpmg = false;}
      if(SgikGYqlLy == true){SgikGYqlLy = false;}
      if(cuqDHcOiwx == true){cuqDHcOiwx = false;}
      if(tmGxtRJfgX == true){tmGxtRJfgX = false;}
      if(ASZOLjiNEl == true){ASZOLjiNEl = false;}
      if(jSxVsWAMUQ == true){jSxVsWAMUQ = false;}
      if(AktpleZkpn == true){AktpleZkpn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQYLDRBSSV
{ 
  void pkWlxONuuJ()
  { 
      bool MLKDjeqYtR = false;
      bool dRHYoDxTMn = false;
      bool AratJTfYEd = false;
      bool mnksVBxTpp = false;
      bool gouFLAYuOy = false;
      bool IswgxUjPsP = false;
      bool yRTPdpgOCm = false;
      bool FcdVHLxViJ = false;
      bool ujKFVsqDwB = false;
      bool QgZZqOUeaV = false;
      bool SKsbsePZYk = false;
      bool WOgjUNHOsj = false;
      bool ycRAVXDDdr = false;
      bool qRtNpkqiLq = false;
      bool dRdKeCApFd = false;
      bool HFlpWorrFU = false;
      bool bLugtETTsi = false;
      bool WYCCGgzGVT = false;
      bool XMyAkkfDpA = false;
      bool rycqPSVxPZ = false;
      string iHcjUVWqoe;
      string RaTjcgdbLM;
      string OlATDwFccr;
      string YuPpODJcYh;
      string CRutzYqWNx;
      string PahrCxHJfY;
      string PsOwGWKcUZ;
      string XADcJwqGTe;
      string EiPecxMXnR;
      string uAxASJDymc;
      string NNCmZOXEhF;
      string GAoBTgdiTJ;
      string JmoCdXDDKA;
      string srSqQqfcFN;
      string ZHphLuKufk;
      string fUedTaYzIB;
      string LTtgMNhyjc;
      string BAcGjBwGqi;
      string MIWZUXNoXp;
      string SgUDCFNIVx;
      if(iHcjUVWqoe == NNCmZOXEhF){MLKDjeqYtR = true;}
      else if(NNCmZOXEhF == iHcjUVWqoe){SKsbsePZYk = true;}
      if(RaTjcgdbLM == GAoBTgdiTJ){dRHYoDxTMn = true;}
      else if(GAoBTgdiTJ == RaTjcgdbLM){WOgjUNHOsj = true;}
      if(OlATDwFccr == JmoCdXDDKA){AratJTfYEd = true;}
      else if(JmoCdXDDKA == OlATDwFccr){ycRAVXDDdr = true;}
      if(YuPpODJcYh == srSqQqfcFN){mnksVBxTpp = true;}
      else if(srSqQqfcFN == YuPpODJcYh){qRtNpkqiLq = true;}
      if(CRutzYqWNx == ZHphLuKufk){gouFLAYuOy = true;}
      else if(ZHphLuKufk == CRutzYqWNx){dRdKeCApFd = true;}
      if(PahrCxHJfY == fUedTaYzIB){IswgxUjPsP = true;}
      else if(fUedTaYzIB == PahrCxHJfY){HFlpWorrFU = true;}
      if(PsOwGWKcUZ == LTtgMNhyjc){yRTPdpgOCm = true;}
      else if(LTtgMNhyjc == PsOwGWKcUZ){bLugtETTsi = true;}
      if(XADcJwqGTe == BAcGjBwGqi){FcdVHLxViJ = true;}
      if(EiPecxMXnR == MIWZUXNoXp){ujKFVsqDwB = true;}
      if(uAxASJDymc == SgUDCFNIVx){QgZZqOUeaV = true;}
      while(BAcGjBwGqi == XADcJwqGTe){WYCCGgzGVT = true;}
      while(MIWZUXNoXp == MIWZUXNoXp){XMyAkkfDpA = true;}
      while(SgUDCFNIVx == SgUDCFNIVx){rycqPSVxPZ = true;}
      if(MLKDjeqYtR == true){MLKDjeqYtR = false;}
      if(dRHYoDxTMn == true){dRHYoDxTMn = false;}
      if(AratJTfYEd == true){AratJTfYEd = false;}
      if(mnksVBxTpp == true){mnksVBxTpp = false;}
      if(gouFLAYuOy == true){gouFLAYuOy = false;}
      if(IswgxUjPsP == true){IswgxUjPsP = false;}
      if(yRTPdpgOCm == true){yRTPdpgOCm = false;}
      if(FcdVHLxViJ == true){FcdVHLxViJ = false;}
      if(ujKFVsqDwB == true){ujKFVsqDwB = false;}
      if(QgZZqOUeaV == true){QgZZqOUeaV = false;}
      if(SKsbsePZYk == true){SKsbsePZYk = false;}
      if(WOgjUNHOsj == true){WOgjUNHOsj = false;}
      if(ycRAVXDDdr == true){ycRAVXDDdr = false;}
      if(qRtNpkqiLq == true){qRtNpkqiLq = false;}
      if(dRdKeCApFd == true){dRdKeCApFd = false;}
      if(HFlpWorrFU == true){HFlpWorrFU = false;}
      if(bLugtETTsi == true){bLugtETTsi = false;}
      if(WYCCGgzGVT == true){WYCCGgzGVT = false;}
      if(XMyAkkfDpA == true){XMyAkkfDpA = false;}
      if(rycqPSVxPZ == true){rycqPSVxPZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SOTSLYUETF
{ 
  void lCOQeEOHXY()
  { 
      bool tRkBjYqfVa = false;
      bool fQBYowbOij = false;
      bool YMuOLbSdtL = false;
      bool sgYIZRfKRm = false;
      bool tKJiUghMFc = false;
      bool GsAgKgWWpI = false;
      bool GMkJhyrrzW = false;
      bool QQwuoNCLtd = false;
      bool tFYQFzfqyr = false;
      bool uJUIghYABV = false;
      bool noNhMowErw = false;
      bool eKcLOAnUDh = false;
      bool SAtGaHwnOH = false;
      bool nCKXpErpEQ = false;
      bool CazBNkfItf = false;
      bool tEwSDmuHGF = false;
      bool rIpkHbAEVJ = false;
      bool IxPmeqBrrp = false;
      bool anshNiFqUC = false;
      bool JkiyXtkNsk = false;
      string kgitNzlxry;
      string tVZMdUjXPn;
      string GeOCtLyTFU;
      string ugInNtwJaj;
      string hzekOFWjkE;
      string DKtqdGSfzC;
      string BSrXCMNlzi;
      string XZxfFHzdnn;
      string nNhAQkmQJH;
      string bPJYiOGHhB;
      string rjkBgcNOlW;
      string HnrKNmkqHR;
      string ZwcrHHPXxp;
      string AqulwEbfTm;
      string XYemzmXzKu;
      string dOAPbwGstY;
      string NoQuVPrFOI;
      string KEXTtAQprU;
      string jQMCMkqfKA;
      string xiltZhHjRi;
      if(kgitNzlxry == rjkBgcNOlW){tRkBjYqfVa = true;}
      else if(rjkBgcNOlW == kgitNzlxry){noNhMowErw = true;}
      if(tVZMdUjXPn == HnrKNmkqHR){fQBYowbOij = true;}
      else if(HnrKNmkqHR == tVZMdUjXPn){eKcLOAnUDh = true;}
      if(GeOCtLyTFU == ZwcrHHPXxp){YMuOLbSdtL = true;}
      else if(ZwcrHHPXxp == GeOCtLyTFU){SAtGaHwnOH = true;}
      if(ugInNtwJaj == AqulwEbfTm){sgYIZRfKRm = true;}
      else if(AqulwEbfTm == ugInNtwJaj){nCKXpErpEQ = true;}
      if(hzekOFWjkE == XYemzmXzKu){tKJiUghMFc = true;}
      else if(XYemzmXzKu == hzekOFWjkE){CazBNkfItf = true;}
      if(DKtqdGSfzC == dOAPbwGstY){GsAgKgWWpI = true;}
      else if(dOAPbwGstY == DKtqdGSfzC){tEwSDmuHGF = true;}
      if(BSrXCMNlzi == NoQuVPrFOI){GMkJhyrrzW = true;}
      else if(NoQuVPrFOI == BSrXCMNlzi){rIpkHbAEVJ = true;}
      if(XZxfFHzdnn == KEXTtAQprU){QQwuoNCLtd = true;}
      if(nNhAQkmQJH == jQMCMkqfKA){tFYQFzfqyr = true;}
      if(bPJYiOGHhB == xiltZhHjRi){uJUIghYABV = true;}
      while(KEXTtAQprU == XZxfFHzdnn){IxPmeqBrrp = true;}
      while(jQMCMkqfKA == jQMCMkqfKA){anshNiFqUC = true;}
      while(xiltZhHjRi == xiltZhHjRi){JkiyXtkNsk = true;}
      if(tRkBjYqfVa == true){tRkBjYqfVa = false;}
      if(fQBYowbOij == true){fQBYowbOij = false;}
      if(YMuOLbSdtL == true){YMuOLbSdtL = false;}
      if(sgYIZRfKRm == true){sgYIZRfKRm = false;}
      if(tKJiUghMFc == true){tKJiUghMFc = false;}
      if(GsAgKgWWpI == true){GsAgKgWWpI = false;}
      if(GMkJhyrrzW == true){GMkJhyrrzW = false;}
      if(QQwuoNCLtd == true){QQwuoNCLtd = false;}
      if(tFYQFzfqyr == true){tFYQFzfqyr = false;}
      if(uJUIghYABV == true){uJUIghYABV = false;}
      if(noNhMowErw == true){noNhMowErw = false;}
      if(eKcLOAnUDh == true){eKcLOAnUDh = false;}
      if(SAtGaHwnOH == true){SAtGaHwnOH = false;}
      if(nCKXpErpEQ == true){nCKXpErpEQ = false;}
      if(CazBNkfItf == true){CazBNkfItf = false;}
      if(tEwSDmuHGF == true){tEwSDmuHGF = false;}
      if(rIpkHbAEVJ == true){rIpkHbAEVJ = false;}
      if(IxPmeqBrrp == true){IxPmeqBrrp = false;}
      if(anshNiFqUC == true){anshNiFqUC = false;}
      if(JkiyXtkNsk == true){JkiyXtkNsk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IKIKNBJNED
{ 
  void JkKQIBuyWj()
  { 
      bool tnKfuRJfIs = false;
      bool WfamNApHtB = false;
      bool WILleoLbAk = false;
      bool RJyGKWKSlg = false;
      bool DitVLrjmsQ = false;
      bool gNoHlkcXAF = false;
      bool FhfXbMgUbq = false;
      bool pWVNymOpam = false;
      bool EYhiDDTpUZ = false;
      bool tlRgaUDVty = false;
      bool KPKCaJrbJy = false;
      bool VmxNAgzwUX = false;
      bool rqACwDFnld = false;
      bool jrubboNfIs = false;
      bool KrgWDHoDft = false;
      bool UGBWGTOIFW = false;
      bool EDofNcqUlL = false;
      bool SSnaMAKdyo = false;
      bool OCIqIcqYVH = false;
      bool ZFakoGCBIZ = false;
      string IjkhZTxtEt;
      string IeHWZzJdlr;
      string VowladLXwl;
      string pdgfPakHuH;
      string hGWpKmxIBO;
      string ZGyGkSmyHw;
      string HZxSEdybHy;
      string NBheKOSGbm;
      string gDVhLjeZuw;
      string mlzzAHIElf;
      string nUBDAXXTwV;
      string AgWTPDEPGU;
      string zXgKKaBidC;
      string GNUwyLCRgn;
      string LLdYuGPfjw;
      string DsyQgQmprZ;
      string VoosPmMaUD;
      string BliRImtHOE;
      string LVygyNPDOh;
      string XLZHRWVjJI;
      if(IjkhZTxtEt == nUBDAXXTwV){tnKfuRJfIs = true;}
      else if(nUBDAXXTwV == IjkhZTxtEt){KPKCaJrbJy = true;}
      if(IeHWZzJdlr == AgWTPDEPGU){WfamNApHtB = true;}
      else if(AgWTPDEPGU == IeHWZzJdlr){VmxNAgzwUX = true;}
      if(VowladLXwl == zXgKKaBidC){WILleoLbAk = true;}
      else if(zXgKKaBidC == VowladLXwl){rqACwDFnld = true;}
      if(pdgfPakHuH == GNUwyLCRgn){RJyGKWKSlg = true;}
      else if(GNUwyLCRgn == pdgfPakHuH){jrubboNfIs = true;}
      if(hGWpKmxIBO == LLdYuGPfjw){DitVLrjmsQ = true;}
      else if(LLdYuGPfjw == hGWpKmxIBO){KrgWDHoDft = true;}
      if(ZGyGkSmyHw == DsyQgQmprZ){gNoHlkcXAF = true;}
      else if(DsyQgQmprZ == ZGyGkSmyHw){UGBWGTOIFW = true;}
      if(HZxSEdybHy == VoosPmMaUD){FhfXbMgUbq = true;}
      else if(VoosPmMaUD == HZxSEdybHy){EDofNcqUlL = true;}
      if(NBheKOSGbm == BliRImtHOE){pWVNymOpam = true;}
      if(gDVhLjeZuw == LVygyNPDOh){EYhiDDTpUZ = true;}
      if(mlzzAHIElf == XLZHRWVjJI){tlRgaUDVty = true;}
      while(BliRImtHOE == NBheKOSGbm){SSnaMAKdyo = true;}
      while(LVygyNPDOh == LVygyNPDOh){OCIqIcqYVH = true;}
      while(XLZHRWVjJI == XLZHRWVjJI){ZFakoGCBIZ = true;}
      if(tnKfuRJfIs == true){tnKfuRJfIs = false;}
      if(WfamNApHtB == true){WfamNApHtB = false;}
      if(WILleoLbAk == true){WILleoLbAk = false;}
      if(RJyGKWKSlg == true){RJyGKWKSlg = false;}
      if(DitVLrjmsQ == true){DitVLrjmsQ = false;}
      if(gNoHlkcXAF == true){gNoHlkcXAF = false;}
      if(FhfXbMgUbq == true){FhfXbMgUbq = false;}
      if(pWVNymOpam == true){pWVNymOpam = false;}
      if(EYhiDDTpUZ == true){EYhiDDTpUZ = false;}
      if(tlRgaUDVty == true){tlRgaUDVty = false;}
      if(KPKCaJrbJy == true){KPKCaJrbJy = false;}
      if(VmxNAgzwUX == true){VmxNAgzwUX = false;}
      if(rqACwDFnld == true){rqACwDFnld = false;}
      if(jrubboNfIs == true){jrubboNfIs = false;}
      if(KrgWDHoDft == true){KrgWDHoDft = false;}
      if(UGBWGTOIFW == true){UGBWGTOIFW = false;}
      if(EDofNcqUlL == true){EDofNcqUlL = false;}
      if(SSnaMAKdyo == true){SSnaMAKdyo = false;}
      if(OCIqIcqYVH == true){OCIqIcqYVH = false;}
      if(ZFakoGCBIZ == true){ZFakoGCBIZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSUXKYBXKV
{ 
  void PRdmgxskXH()
  { 
      bool czpofbbQTY = false;
      bool mbjIUsUBjq = false;
      bool tneroNuIph = false;
      bool ctEGjMmTRp = false;
      bool xduhHFKIHs = false;
      bool JLqhYoUxzR = false;
      bool gSalusXcXH = false;
      bool GBjtsQswkj = false;
      bool DlAwXRDWhu = false;
      bool qoTAIeDIlO = false;
      bool hgjzmIbwnI = false;
      bool uXMPNtReNd = false;
      bool oAtcQQgjlO = false;
      bool MjJVCWCBJO = false;
      bool pHiZzTcDlN = false;
      bool MYtIYglHiV = false;
      bool aqJYuKNpNq = false;
      bool rQUymhRUcw = false;
      bool ndyYBnpBxU = false;
      bool juRmnyxJen = false;
      string jWUSMitAgc;
      string hcuQDtNoGg;
      string mhZRLpUrPD;
      string AcpmqcygtQ;
      string nrLcZweTpa;
      string MsbCwCxCHW;
      string NBjdbFmHYZ;
      string ugtostWxrO;
      string KACopHAmpo;
      string fwYXCmIgBU;
      string JWtPefzmJB;
      string ezJsLNyumU;
      string EzRjtyIVlG;
      string lowXFmFmJK;
      string HNdnJfleMn;
      string nNtgPJFKVg;
      string WcACPpDlnX;
      string ILkcMqVcZN;
      string MdIyRYuOHu;
      string htQcmdNaYT;
      if(jWUSMitAgc == JWtPefzmJB){czpofbbQTY = true;}
      else if(JWtPefzmJB == jWUSMitAgc){hgjzmIbwnI = true;}
      if(hcuQDtNoGg == ezJsLNyumU){mbjIUsUBjq = true;}
      else if(ezJsLNyumU == hcuQDtNoGg){uXMPNtReNd = true;}
      if(mhZRLpUrPD == EzRjtyIVlG){tneroNuIph = true;}
      else if(EzRjtyIVlG == mhZRLpUrPD){oAtcQQgjlO = true;}
      if(AcpmqcygtQ == lowXFmFmJK){ctEGjMmTRp = true;}
      else if(lowXFmFmJK == AcpmqcygtQ){MjJVCWCBJO = true;}
      if(nrLcZweTpa == HNdnJfleMn){xduhHFKIHs = true;}
      else if(HNdnJfleMn == nrLcZweTpa){pHiZzTcDlN = true;}
      if(MsbCwCxCHW == nNtgPJFKVg){JLqhYoUxzR = true;}
      else if(nNtgPJFKVg == MsbCwCxCHW){MYtIYglHiV = true;}
      if(NBjdbFmHYZ == WcACPpDlnX){gSalusXcXH = true;}
      else if(WcACPpDlnX == NBjdbFmHYZ){aqJYuKNpNq = true;}
      if(ugtostWxrO == ILkcMqVcZN){GBjtsQswkj = true;}
      if(KACopHAmpo == MdIyRYuOHu){DlAwXRDWhu = true;}
      if(fwYXCmIgBU == htQcmdNaYT){qoTAIeDIlO = true;}
      while(ILkcMqVcZN == ugtostWxrO){rQUymhRUcw = true;}
      while(MdIyRYuOHu == MdIyRYuOHu){ndyYBnpBxU = true;}
      while(htQcmdNaYT == htQcmdNaYT){juRmnyxJen = true;}
      if(czpofbbQTY == true){czpofbbQTY = false;}
      if(mbjIUsUBjq == true){mbjIUsUBjq = false;}
      if(tneroNuIph == true){tneroNuIph = false;}
      if(ctEGjMmTRp == true){ctEGjMmTRp = false;}
      if(xduhHFKIHs == true){xduhHFKIHs = false;}
      if(JLqhYoUxzR == true){JLqhYoUxzR = false;}
      if(gSalusXcXH == true){gSalusXcXH = false;}
      if(GBjtsQswkj == true){GBjtsQswkj = false;}
      if(DlAwXRDWhu == true){DlAwXRDWhu = false;}
      if(qoTAIeDIlO == true){qoTAIeDIlO = false;}
      if(hgjzmIbwnI == true){hgjzmIbwnI = false;}
      if(uXMPNtReNd == true){uXMPNtReNd = false;}
      if(oAtcQQgjlO == true){oAtcQQgjlO = false;}
      if(MjJVCWCBJO == true){MjJVCWCBJO = false;}
      if(pHiZzTcDlN == true){pHiZzTcDlN = false;}
      if(MYtIYglHiV == true){MYtIYglHiV = false;}
      if(aqJYuKNpNq == true){aqJYuKNpNq = false;}
      if(rQUymhRUcw == true){rQUymhRUcw = false;}
      if(ndyYBnpBxU == true){ndyYBnpBxU = false;}
      if(juRmnyxJen == true){juRmnyxJen = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VELDIANDHN
{ 
  void aGjyliTjAe()
  { 
      bool eEyInVcnri = false;
      bool MLTZFoYDgm = false;
      bool KohtVdSoKe = false;
      bool CJbjgntRlX = false;
      bool tfHDpTqypy = false;
      bool CQkDdoWDmK = false;
      bool DncNgCjjsR = false;
      bool uGRIseheEB = false;
      bool lTyLckYXFq = false;
      bool RpdaUFCtVm = false;
      bool jHEYDuzbKz = false;
      bool HqzlYjoRjw = false;
      bool dLdCAEbpnm = false;
      bool bmIQQeOZIg = false;
      bool kwNGjZqrBk = false;
      bool PkJZJXdCYz = false;
      bool SInWWTihUt = false;
      bool UPJCKhxWSa = false;
      bool NjnDWqdiHr = false;
      bool AMAJOcIpjP = false;
      string BQYrpuSOKu;
      string ndmFTWxzaP;
      string JwysFVQmbr;
      string EngWJbSXqA;
      string tfcUZFNdJS;
      string xsIEZERfmT;
      string eemRpAxPuq;
      string DYIZVdScSz;
      string HlcIuKfbwE;
      string KljWVOrKdZ;
      string IxiSOXkhiu;
      string loNnLrBdWf;
      string TUTqgRokEH;
      string kHyrpKDKsW;
      string ZxsASUYwKd;
      string MOnyFndrlx;
      string izdaKdpUxB;
      string oqkzFVbSXL;
      string rsaatWTAlC;
      string fLYunaTRpn;
      if(BQYrpuSOKu == IxiSOXkhiu){eEyInVcnri = true;}
      else if(IxiSOXkhiu == BQYrpuSOKu){jHEYDuzbKz = true;}
      if(ndmFTWxzaP == loNnLrBdWf){MLTZFoYDgm = true;}
      else if(loNnLrBdWf == ndmFTWxzaP){HqzlYjoRjw = true;}
      if(JwysFVQmbr == TUTqgRokEH){KohtVdSoKe = true;}
      else if(TUTqgRokEH == JwysFVQmbr){dLdCAEbpnm = true;}
      if(EngWJbSXqA == kHyrpKDKsW){CJbjgntRlX = true;}
      else if(kHyrpKDKsW == EngWJbSXqA){bmIQQeOZIg = true;}
      if(tfcUZFNdJS == ZxsASUYwKd){tfHDpTqypy = true;}
      else if(ZxsASUYwKd == tfcUZFNdJS){kwNGjZqrBk = true;}
      if(xsIEZERfmT == MOnyFndrlx){CQkDdoWDmK = true;}
      else if(MOnyFndrlx == xsIEZERfmT){PkJZJXdCYz = true;}
      if(eemRpAxPuq == izdaKdpUxB){DncNgCjjsR = true;}
      else if(izdaKdpUxB == eemRpAxPuq){SInWWTihUt = true;}
      if(DYIZVdScSz == oqkzFVbSXL){uGRIseheEB = true;}
      if(HlcIuKfbwE == rsaatWTAlC){lTyLckYXFq = true;}
      if(KljWVOrKdZ == fLYunaTRpn){RpdaUFCtVm = true;}
      while(oqkzFVbSXL == DYIZVdScSz){UPJCKhxWSa = true;}
      while(rsaatWTAlC == rsaatWTAlC){NjnDWqdiHr = true;}
      while(fLYunaTRpn == fLYunaTRpn){AMAJOcIpjP = true;}
      if(eEyInVcnri == true){eEyInVcnri = false;}
      if(MLTZFoYDgm == true){MLTZFoYDgm = false;}
      if(KohtVdSoKe == true){KohtVdSoKe = false;}
      if(CJbjgntRlX == true){CJbjgntRlX = false;}
      if(tfHDpTqypy == true){tfHDpTqypy = false;}
      if(CQkDdoWDmK == true){CQkDdoWDmK = false;}
      if(DncNgCjjsR == true){DncNgCjjsR = false;}
      if(uGRIseheEB == true){uGRIseheEB = false;}
      if(lTyLckYXFq == true){lTyLckYXFq = false;}
      if(RpdaUFCtVm == true){RpdaUFCtVm = false;}
      if(jHEYDuzbKz == true){jHEYDuzbKz = false;}
      if(HqzlYjoRjw == true){HqzlYjoRjw = false;}
      if(dLdCAEbpnm == true){dLdCAEbpnm = false;}
      if(bmIQQeOZIg == true){bmIQQeOZIg = false;}
      if(kwNGjZqrBk == true){kwNGjZqrBk = false;}
      if(PkJZJXdCYz == true){PkJZJXdCYz = false;}
      if(SInWWTihUt == true){SInWWTihUt = false;}
      if(UPJCKhxWSa == true){UPJCKhxWSa = false;}
      if(NjnDWqdiHr == true){NjnDWqdiHr = false;}
      if(AMAJOcIpjP == true){AMAJOcIpjP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBXOJMJGAD
{ 
  void LnlmYoUZpj()
  { 
      bool TmcobAoYZk = false;
      bool IHLFmtnHwY = false;
      bool nlcAjNsIgp = false;
      bool rXBGofhorx = false;
      bool qosPwKrCoN = false;
      bool MTNQOgJbFO = false;
      bool GfqjsjGFQG = false;
      bool LyOzgzsNEZ = false;
      bool VqTTcYKjqH = false;
      bool VGjdpLxJVL = false;
      bool DlkhBNEOiO = false;
      bool nuWfrOLXGU = false;
      bool ZVNJjFOjIV = false;
      bool CjqrViFkRP = false;
      bool TuAcSZiEkb = false;
      bool zZDBlgYbxw = false;
      bool zTGNMEEeJJ = false;
      bool IaFpAeVjpK = false;
      bool WJygWbgpGo = false;
      bool KdmVPznmQO = false;
      string DCiPDsDsFC;
      string ywNKHwqRhr;
      string ncEVmgsLAo;
      string ihNUKLMMhj;
      string SmhtqMdjra;
      string cYnRNZyNbW;
      string zrsPTPhsAu;
      string jdiyYBtJeZ;
      string CJTYMJswHk;
      string NzjLjZtRaa;
      string dkjwqzpprM;
      string enhBTpYTDJ;
      string WllOhjsWNy;
      string GciEwRYWhN;
      string TDDuFYQhrs;
      string BZOQEqzUOG;
      string FSbsFCFdFC;
      string RBkppSiqJI;
      string TKeUxfNSAE;
      string SDHbIAaKoD;
      if(DCiPDsDsFC == dkjwqzpprM){TmcobAoYZk = true;}
      else if(dkjwqzpprM == DCiPDsDsFC){DlkhBNEOiO = true;}
      if(ywNKHwqRhr == enhBTpYTDJ){IHLFmtnHwY = true;}
      else if(enhBTpYTDJ == ywNKHwqRhr){nuWfrOLXGU = true;}
      if(ncEVmgsLAo == WllOhjsWNy){nlcAjNsIgp = true;}
      else if(WllOhjsWNy == ncEVmgsLAo){ZVNJjFOjIV = true;}
      if(ihNUKLMMhj == GciEwRYWhN){rXBGofhorx = true;}
      else if(GciEwRYWhN == ihNUKLMMhj){CjqrViFkRP = true;}
      if(SmhtqMdjra == TDDuFYQhrs){qosPwKrCoN = true;}
      else if(TDDuFYQhrs == SmhtqMdjra){TuAcSZiEkb = true;}
      if(cYnRNZyNbW == BZOQEqzUOG){MTNQOgJbFO = true;}
      else if(BZOQEqzUOG == cYnRNZyNbW){zZDBlgYbxw = true;}
      if(zrsPTPhsAu == FSbsFCFdFC){GfqjsjGFQG = true;}
      else if(FSbsFCFdFC == zrsPTPhsAu){zTGNMEEeJJ = true;}
      if(jdiyYBtJeZ == RBkppSiqJI){LyOzgzsNEZ = true;}
      if(CJTYMJswHk == TKeUxfNSAE){VqTTcYKjqH = true;}
      if(NzjLjZtRaa == SDHbIAaKoD){VGjdpLxJVL = true;}
      while(RBkppSiqJI == jdiyYBtJeZ){IaFpAeVjpK = true;}
      while(TKeUxfNSAE == TKeUxfNSAE){WJygWbgpGo = true;}
      while(SDHbIAaKoD == SDHbIAaKoD){KdmVPznmQO = true;}
      if(TmcobAoYZk == true){TmcobAoYZk = false;}
      if(IHLFmtnHwY == true){IHLFmtnHwY = false;}
      if(nlcAjNsIgp == true){nlcAjNsIgp = false;}
      if(rXBGofhorx == true){rXBGofhorx = false;}
      if(qosPwKrCoN == true){qosPwKrCoN = false;}
      if(MTNQOgJbFO == true){MTNQOgJbFO = false;}
      if(GfqjsjGFQG == true){GfqjsjGFQG = false;}
      if(LyOzgzsNEZ == true){LyOzgzsNEZ = false;}
      if(VqTTcYKjqH == true){VqTTcYKjqH = false;}
      if(VGjdpLxJVL == true){VGjdpLxJVL = false;}
      if(DlkhBNEOiO == true){DlkhBNEOiO = false;}
      if(nuWfrOLXGU == true){nuWfrOLXGU = false;}
      if(ZVNJjFOjIV == true){ZVNJjFOjIV = false;}
      if(CjqrViFkRP == true){CjqrViFkRP = false;}
      if(TuAcSZiEkb == true){TuAcSZiEkb = false;}
      if(zZDBlgYbxw == true){zZDBlgYbxw = false;}
      if(zTGNMEEeJJ == true){zTGNMEEeJJ = false;}
      if(IaFpAeVjpK == true){IaFpAeVjpK = false;}
      if(WJygWbgpGo == true){WJygWbgpGo = false;}
      if(KdmVPznmQO == true){KdmVPznmQO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RYXGLNCFID
{ 
  void orgrwprFhE()
  { 
      bool uAHAzuggWY = false;
      bool CKmxexQGhi = false;
      bool xyVZzHFkuP = false;
      bool yekNRdtzYK = false;
      bool MYozYFVEAA = false;
      bool GuCSExdhBq = false;
      bool owkGZXYZfA = false;
      bool CRhXWYJWAs = false;
      bool lBjuJCbSIT = false;
      bool AMxhUPmhYB = false;
      bool fwXzxnNeue = false;
      bool nHgHEmMpwX = false;
      bool uGQLApTzDH = false;
      bool laxzNodkxU = false;
      bool nxWcfseocg = false;
      bool CwlBFYfMzH = false;
      bool UObmsMJhtP = false;
      bool JbrajyjmeG = false;
      bool KdWVFonwsn = false;
      bool JQkpAZVijT = false;
      string IVxfhkkEqG;
      string kRqsYAdRmS;
      string jVkycVXYXo;
      string LBEUeUmJGG;
      string jlUeqXnmhx;
      string fqAfSmjzCM;
      string NLgBuiNVOD;
      string NTKghxAFGF;
      string hjqZJTAXBr;
      string jmHtrYFSjI;
      string JSYdjLgSyV;
      string lerxdcUGqa;
      string hpTVSZMPnJ;
      string rhUyuOLMpx;
      string mhZfGFuJPP;
      string DyaJZTyCKK;
      string zQencDJtBP;
      string QHQsmAQnPN;
      string eCzXFtGLXb;
      string QIBfxWCkCC;
      if(IVxfhkkEqG == JSYdjLgSyV){uAHAzuggWY = true;}
      else if(JSYdjLgSyV == IVxfhkkEqG){fwXzxnNeue = true;}
      if(kRqsYAdRmS == lerxdcUGqa){CKmxexQGhi = true;}
      else if(lerxdcUGqa == kRqsYAdRmS){nHgHEmMpwX = true;}
      if(jVkycVXYXo == hpTVSZMPnJ){xyVZzHFkuP = true;}
      else if(hpTVSZMPnJ == jVkycVXYXo){uGQLApTzDH = true;}
      if(LBEUeUmJGG == rhUyuOLMpx){yekNRdtzYK = true;}
      else if(rhUyuOLMpx == LBEUeUmJGG){laxzNodkxU = true;}
      if(jlUeqXnmhx == mhZfGFuJPP){MYozYFVEAA = true;}
      else if(mhZfGFuJPP == jlUeqXnmhx){nxWcfseocg = true;}
      if(fqAfSmjzCM == DyaJZTyCKK){GuCSExdhBq = true;}
      else if(DyaJZTyCKK == fqAfSmjzCM){CwlBFYfMzH = true;}
      if(NLgBuiNVOD == zQencDJtBP){owkGZXYZfA = true;}
      else if(zQencDJtBP == NLgBuiNVOD){UObmsMJhtP = true;}
      if(NTKghxAFGF == QHQsmAQnPN){CRhXWYJWAs = true;}
      if(hjqZJTAXBr == eCzXFtGLXb){lBjuJCbSIT = true;}
      if(jmHtrYFSjI == QIBfxWCkCC){AMxhUPmhYB = true;}
      while(QHQsmAQnPN == NTKghxAFGF){JbrajyjmeG = true;}
      while(eCzXFtGLXb == eCzXFtGLXb){KdWVFonwsn = true;}
      while(QIBfxWCkCC == QIBfxWCkCC){JQkpAZVijT = true;}
      if(uAHAzuggWY == true){uAHAzuggWY = false;}
      if(CKmxexQGhi == true){CKmxexQGhi = false;}
      if(xyVZzHFkuP == true){xyVZzHFkuP = false;}
      if(yekNRdtzYK == true){yekNRdtzYK = false;}
      if(MYozYFVEAA == true){MYozYFVEAA = false;}
      if(GuCSExdhBq == true){GuCSExdhBq = false;}
      if(owkGZXYZfA == true){owkGZXYZfA = false;}
      if(CRhXWYJWAs == true){CRhXWYJWAs = false;}
      if(lBjuJCbSIT == true){lBjuJCbSIT = false;}
      if(AMxhUPmhYB == true){AMxhUPmhYB = false;}
      if(fwXzxnNeue == true){fwXzxnNeue = false;}
      if(nHgHEmMpwX == true){nHgHEmMpwX = false;}
      if(uGQLApTzDH == true){uGQLApTzDH = false;}
      if(laxzNodkxU == true){laxzNodkxU = false;}
      if(nxWcfseocg == true){nxWcfseocg = false;}
      if(CwlBFYfMzH == true){CwlBFYfMzH = false;}
      if(UObmsMJhtP == true){UObmsMJhtP = false;}
      if(JbrajyjmeG == true){JbrajyjmeG = false;}
      if(KdWVFonwsn == true){KdWVFonwsn = false;}
      if(JQkpAZVijT == true){JQkpAZVijT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKRGIXVLHA
{ 
  void RsQWViCRBS()
  { 
      bool RkmCGdnVEu = false;
      bool FpjmeWKMwb = false;
      bool YiSaAYwePa = false;
      bool OifZXSRsdu = false;
      bool srUNPqaJTV = false;
      bool CtarOhRMBh = false;
      bool hIFcgVKKPM = false;
      bool ERhAhgNELJ = false;
      bool ymLsYTInKo = false;
      bool AFqwNjlrgs = false;
      bool gPtHQkLZJh = false;
      bool TNBriuxLEM = false;
      bool NVzZLzZkmx = false;
      bool tVXRbhrEcn = false;
      bool HhdcVmDyNS = false;
      bool mZmUfKQUuR = false;
      bool KZmMmyoiPB = false;
      bool CsiQEfrWEY = false;
      bool ubXUKUhDkR = false;
      bool RXIKcguQoW = false;
      string BXCokEUKNa;
      string bhtbOZiPbU;
      string BVdbSiUgQA;
      string ORUbjwrirR;
      string eXVMEYobMh;
      string PJkImesaWB;
      string jntNMJMSrS;
      string hAWKodARWs;
      string trThjFgMnE;
      string CQLqhqdHzu;
      string MVjtAPlaTJ;
      string eaDcGqTLcH;
      string cAemQQnfbx;
      string zrRbgYHZhU;
      string SGsdZaMijp;
      string XRerRMqxci;
      string bGyVJlIbuh;
      string jsdInWGAMp;
      string DEukZhNZJU;
      string gKxyrMHXTm;
      if(BXCokEUKNa == MVjtAPlaTJ){RkmCGdnVEu = true;}
      else if(MVjtAPlaTJ == BXCokEUKNa){gPtHQkLZJh = true;}
      if(bhtbOZiPbU == eaDcGqTLcH){FpjmeWKMwb = true;}
      else if(eaDcGqTLcH == bhtbOZiPbU){TNBriuxLEM = true;}
      if(BVdbSiUgQA == cAemQQnfbx){YiSaAYwePa = true;}
      else if(cAemQQnfbx == BVdbSiUgQA){NVzZLzZkmx = true;}
      if(ORUbjwrirR == zrRbgYHZhU){OifZXSRsdu = true;}
      else if(zrRbgYHZhU == ORUbjwrirR){tVXRbhrEcn = true;}
      if(eXVMEYobMh == SGsdZaMijp){srUNPqaJTV = true;}
      else if(SGsdZaMijp == eXVMEYobMh){HhdcVmDyNS = true;}
      if(PJkImesaWB == XRerRMqxci){CtarOhRMBh = true;}
      else if(XRerRMqxci == PJkImesaWB){mZmUfKQUuR = true;}
      if(jntNMJMSrS == bGyVJlIbuh){hIFcgVKKPM = true;}
      else if(bGyVJlIbuh == jntNMJMSrS){KZmMmyoiPB = true;}
      if(hAWKodARWs == jsdInWGAMp){ERhAhgNELJ = true;}
      if(trThjFgMnE == DEukZhNZJU){ymLsYTInKo = true;}
      if(CQLqhqdHzu == gKxyrMHXTm){AFqwNjlrgs = true;}
      while(jsdInWGAMp == hAWKodARWs){CsiQEfrWEY = true;}
      while(DEukZhNZJU == DEukZhNZJU){ubXUKUhDkR = true;}
      while(gKxyrMHXTm == gKxyrMHXTm){RXIKcguQoW = true;}
      if(RkmCGdnVEu == true){RkmCGdnVEu = false;}
      if(FpjmeWKMwb == true){FpjmeWKMwb = false;}
      if(YiSaAYwePa == true){YiSaAYwePa = false;}
      if(OifZXSRsdu == true){OifZXSRsdu = false;}
      if(srUNPqaJTV == true){srUNPqaJTV = false;}
      if(CtarOhRMBh == true){CtarOhRMBh = false;}
      if(hIFcgVKKPM == true){hIFcgVKKPM = false;}
      if(ERhAhgNELJ == true){ERhAhgNELJ = false;}
      if(ymLsYTInKo == true){ymLsYTInKo = false;}
      if(AFqwNjlrgs == true){AFqwNjlrgs = false;}
      if(gPtHQkLZJh == true){gPtHQkLZJh = false;}
      if(TNBriuxLEM == true){TNBriuxLEM = false;}
      if(NVzZLzZkmx == true){NVzZLzZkmx = false;}
      if(tVXRbhrEcn == true){tVXRbhrEcn = false;}
      if(HhdcVmDyNS == true){HhdcVmDyNS = false;}
      if(mZmUfKQUuR == true){mZmUfKQUuR = false;}
      if(KZmMmyoiPB == true){KZmMmyoiPB = false;}
      if(CsiQEfrWEY == true){CsiQEfrWEY = false;}
      if(ubXUKUhDkR == true){ubXUKUhDkR = false;}
      if(RXIKcguQoW == true){RXIKcguQoW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FJLCCHNSUC
{ 
  void SLyYgeJEFR()
  { 
      bool hyuzLjUNxg = false;
      bool nuPWSloomY = false;
      bool lHatFKqRyp = false;
      bool htSaltbgcd = false;
      bool nQMXhFjCxa = false;
      bool ilXlOaXBsB = false;
      bool rDOHyscnjX = false;
      bool KHLJjUtDLz = false;
      bool ZoUXGwWgML = false;
      bool WZmblkCFYn = false;
      bool cuRYPaaOBs = false;
      bool gUotaChqAC = false;
      bool WuaYBjUiWz = false;
      bool SndWWdXuHf = false;
      bool VIfSeBksBj = false;
      bool CKFWRhTsXf = false;
      bool GqqCZrpRWw = false;
      bool emiUgNOHtz = false;
      bool zagmwHiHEo = false;
      bool JeWbYdQdsl = false;
      string GyarmhPqfs;
      string UrTHYxWTmy;
      string GVUFkgABVg;
      string iOuHYQXxtF;
      string yhHeIJIVVJ;
      string RgVQTjcUGG;
      string gOVyKFxLiI;
      string ZYZhzYNpwb;
      string XeeLPBrdnn;
      string mCpmXjMJTD;
      string MxmNjrHnQu;
      string VmYehCiJiI;
      string NSWtUXhlKP;
      string MEVsParRbW;
      string tEMsRzdLFV;
      string BCZLosZrrM;
      string JVdBhQRePG;
      string KQgLOIFdbU;
      string sWfnNJeJEV;
      string BzYPNYaLKA;
      if(GyarmhPqfs == MxmNjrHnQu){hyuzLjUNxg = true;}
      else if(MxmNjrHnQu == GyarmhPqfs){cuRYPaaOBs = true;}
      if(UrTHYxWTmy == VmYehCiJiI){nuPWSloomY = true;}
      else if(VmYehCiJiI == UrTHYxWTmy){gUotaChqAC = true;}
      if(GVUFkgABVg == NSWtUXhlKP){lHatFKqRyp = true;}
      else if(NSWtUXhlKP == GVUFkgABVg){WuaYBjUiWz = true;}
      if(iOuHYQXxtF == MEVsParRbW){htSaltbgcd = true;}
      else if(MEVsParRbW == iOuHYQXxtF){SndWWdXuHf = true;}
      if(yhHeIJIVVJ == tEMsRzdLFV){nQMXhFjCxa = true;}
      else if(tEMsRzdLFV == yhHeIJIVVJ){VIfSeBksBj = true;}
      if(RgVQTjcUGG == BCZLosZrrM){ilXlOaXBsB = true;}
      else if(BCZLosZrrM == RgVQTjcUGG){CKFWRhTsXf = true;}
      if(gOVyKFxLiI == JVdBhQRePG){rDOHyscnjX = true;}
      else if(JVdBhQRePG == gOVyKFxLiI){GqqCZrpRWw = true;}
      if(ZYZhzYNpwb == KQgLOIFdbU){KHLJjUtDLz = true;}
      if(XeeLPBrdnn == sWfnNJeJEV){ZoUXGwWgML = true;}
      if(mCpmXjMJTD == BzYPNYaLKA){WZmblkCFYn = true;}
      while(KQgLOIFdbU == ZYZhzYNpwb){emiUgNOHtz = true;}
      while(sWfnNJeJEV == sWfnNJeJEV){zagmwHiHEo = true;}
      while(BzYPNYaLKA == BzYPNYaLKA){JeWbYdQdsl = true;}
      if(hyuzLjUNxg == true){hyuzLjUNxg = false;}
      if(nuPWSloomY == true){nuPWSloomY = false;}
      if(lHatFKqRyp == true){lHatFKqRyp = false;}
      if(htSaltbgcd == true){htSaltbgcd = false;}
      if(nQMXhFjCxa == true){nQMXhFjCxa = false;}
      if(ilXlOaXBsB == true){ilXlOaXBsB = false;}
      if(rDOHyscnjX == true){rDOHyscnjX = false;}
      if(KHLJjUtDLz == true){KHLJjUtDLz = false;}
      if(ZoUXGwWgML == true){ZoUXGwWgML = false;}
      if(WZmblkCFYn == true){WZmblkCFYn = false;}
      if(cuRYPaaOBs == true){cuRYPaaOBs = false;}
      if(gUotaChqAC == true){gUotaChqAC = false;}
      if(WuaYBjUiWz == true){WuaYBjUiWz = false;}
      if(SndWWdXuHf == true){SndWWdXuHf = false;}
      if(VIfSeBksBj == true){VIfSeBksBj = false;}
      if(CKFWRhTsXf == true){CKFWRhTsXf = false;}
      if(GqqCZrpRWw == true){GqqCZrpRWw = false;}
      if(emiUgNOHtz == true){emiUgNOHtz = false;}
      if(zagmwHiHEo == true){zagmwHiHEo = false;}
      if(JeWbYdQdsl == true){JeWbYdQdsl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WMXBAVNXMH
{ 
  void IeFyqPPVBo()
  { 
      bool ewSlJYxoqs = false;
      bool EoOTYrooTE = false;
      bool xPCgxtFgkU = false;
      bool mzfnAQcoNx = false;
      bool SVEOzUfGIN = false;
      bool aDXqEOsknP = false;
      bool TPEWFEIZTH = false;
      bool PAbWkbKnhc = false;
      bool NzXWsjboil = false;
      bool XrAxcDQhIu = false;
      bool LFmAyabAFb = false;
      bool DFDKBUqgcV = false;
      bool cTqgjXAdth = false;
      bool LcelQHMWYS = false;
      bool IaiHhRnowI = false;
      bool LjFlRrOFQa = false;
      bool ZxGXQaZQtt = false;
      bool HUHJNCjizR = false;
      bool iKhkWbXrUX = false;
      bool rHGyrKTLpG = false;
      string MNCdkVSFen;
      string zkwngtmzqD;
      string czFVVMaPwL;
      string BcIlZidyBh;
      string OFmifyXUTV;
      string cipGVNHgIX;
      string uCJTlWbKOx;
      string PoxInXLWpW;
      string oGwZhSlBPM;
      string bwocmLuTxJ;
      string WMGVFmkgSy;
      string BkpkioGilT;
      string jatBVSzUVb;
      string crZgAbzZTt;
      string gEiRLpFDsy;
      string FLgcYwREzl;
      string nQLpUILJkH;
      string ofOqlfqcpf;
      string MuaWWQLwHE;
      string JuahGQrrwC;
      if(MNCdkVSFen == WMGVFmkgSy){ewSlJYxoqs = true;}
      else if(WMGVFmkgSy == MNCdkVSFen){LFmAyabAFb = true;}
      if(zkwngtmzqD == BkpkioGilT){EoOTYrooTE = true;}
      else if(BkpkioGilT == zkwngtmzqD){DFDKBUqgcV = true;}
      if(czFVVMaPwL == jatBVSzUVb){xPCgxtFgkU = true;}
      else if(jatBVSzUVb == czFVVMaPwL){cTqgjXAdth = true;}
      if(BcIlZidyBh == crZgAbzZTt){mzfnAQcoNx = true;}
      else if(crZgAbzZTt == BcIlZidyBh){LcelQHMWYS = true;}
      if(OFmifyXUTV == gEiRLpFDsy){SVEOzUfGIN = true;}
      else if(gEiRLpFDsy == OFmifyXUTV){IaiHhRnowI = true;}
      if(cipGVNHgIX == FLgcYwREzl){aDXqEOsknP = true;}
      else if(FLgcYwREzl == cipGVNHgIX){LjFlRrOFQa = true;}
      if(uCJTlWbKOx == nQLpUILJkH){TPEWFEIZTH = true;}
      else if(nQLpUILJkH == uCJTlWbKOx){ZxGXQaZQtt = true;}
      if(PoxInXLWpW == ofOqlfqcpf){PAbWkbKnhc = true;}
      if(oGwZhSlBPM == MuaWWQLwHE){NzXWsjboil = true;}
      if(bwocmLuTxJ == JuahGQrrwC){XrAxcDQhIu = true;}
      while(ofOqlfqcpf == PoxInXLWpW){HUHJNCjizR = true;}
      while(MuaWWQLwHE == MuaWWQLwHE){iKhkWbXrUX = true;}
      while(JuahGQrrwC == JuahGQrrwC){rHGyrKTLpG = true;}
      if(ewSlJYxoqs == true){ewSlJYxoqs = false;}
      if(EoOTYrooTE == true){EoOTYrooTE = false;}
      if(xPCgxtFgkU == true){xPCgxtFgkU = false;}
      if(mzfnAQcoNx == true){mzfnAQcoNx = false;}
      if(SVEOzUfGIN == true){SVEOzUfGIN = false;}
      if(aDXqEOsknP == true){aDXqEOsknP = false;}
      if(TPEWFEIZTH == true){TPEWFEIZTH = false;}
      if(PAbWkbKnhc == true){PAbWkbKnhc = false;}
      if(NzXWsjboil == true){NzXWsjboil = false;}
      if(XrAxcDQhIu == true){XrAxcDQhIu = false;}
      if(LFmAyabAFb == true){LFmAyabAFb = false;}
      if(DFDKBUqgcV == true){DFDKBUqgcV = false;}
      if(cTqgjXAdth == true){cTqgjXAdth = false;}
      if(LcelQHMWYS == true){LcelQHMWYS = false;}
      if(IaiHhRnowI == true){IaiHhRnowI = false;}
      if(LjFlRrOFQa == true){LjFlRrOFQa = false;}
      if(ZxGXQaZQtt == true){ZxGXQaZQtt = false;}
      if(HUHJNCjizR == true){HUHJNCjizR = false;}
      if(iKhkWbXrUX == true){iKhkWbXrUX = false;}
      if(rHGyrKTLpG == true){rHGyrKTLpG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LOJKZUCQDZ
{ 
  void nImFTaXWFD()
  { 
      bool InRHMJKVNX = false;
      bool RUaVLKaleg = false;
      bool kCdkyxLsWE = false;
      bool EWtchTIpKO = false;
      bool TdWgjRixNZ = false;
      bool QPJZeFJfIP = false;
      bool yQyIStaynr = false;
      bool CkaQNGfxBg = false;
      bool NNfxnoNUxb = false;
      bool KbguPCfNNp = false;
      bool qkJVXeorLY = false;
      bool ZLebBkkAUd = false;
      bool gFALgZEeAL = false;
      bool ZSiLocDJZI = false;
      bool zVIYBywFte = false;
      bool QerjIkjxox = false;
      bool ZJrAyGbTlY = false;
      bool gbaLdKxbKi = false;
      bool czkUtuZzCE = false;
      bool rGUchpcIZt = false;
      string HlHABEhSgO;
      string GGXbwDVOxB;
      string DHjKPEUsKP;
      string WXpNQfjMks;
      string nBXQezCaPR;
      string brIeYzBwkx;
      string inHQrhQKLQ;
      string SIdEMCjTeP;
      string BtdsnePKoQ;
      string dnbnKzsGXw;
      string irOyySNDRV;
      string PhQUunKOcN;
      string SFUtlegotN;
      string JduhgJeetV;
      string QLsTBuWGrV;
      string oecKddWULT;
      string kYJELkmink;
      string IeTHwGLBsp;
      string HaxXYdAjEC;
      string mKTZjrBnHP;
      if(HlHABEhSgO == irOyySNDRV){InRHMJKVNX = true;}
      else if(irOyySNDRV == HlHABEhSgO){qkJVXeorLY = true;}
      if(GGXbwDVOxB == PhQUunKOcN){RUaVLKaleg = true;}
      else if(PhQUunKOcN == GGXbwDVOxB){ZLebBkkAUd = true;}
      if(DHjKPEUsKP == SFUtlegotN){kCdkyxLsWE = true;}
      else if(SFUtlegotN == DHjKPEUsKP){gFALgZEeAL = true;}
      if(WXpNQfjMks == JduhgJeetV){EWtchTIpKO = true;}
      else if(JduhgJeetV == WXpNQfjMks){ZSiLocDJZI = true;}
      if(nBXQezCaPR == QLsTBuWGrV){TdWgjRixNZ = true;}
      else if(QLsTBuWGrV == nBXQezCaPR){zVIYBywFte = true;}
      if(brIeYzBwkx == oecKddWULT){QPJZeFJfIP = true;}
      else if(oecKddWULT == brIeYzBwkx){QerjIkjxox = true;}
      if(inHQrhQKLQ == kYJELkmink){yQyIStaynr = true;}
      else if(kYJELkmink == inHQrhQKLQ){ZJrAyGbTlY = true;}
      if(SIdEMCjTeP == IeTHwGLBsp){CkaQNGfxBg = true;}
      if(BtdsnePKoQ == HaxXYdAjEC){NNfxnoNUxb = true;}
      if(dnbnKzsGXw == mKTZjrBnHP){KbguPCfNNp = true;}
      while(IeTHwGLBsp == SIdEMCjTeP){gbaLdKxbKi = true;}
      while(HaxXYdAjEC == HaxXYdAjEC){czkUtuZzCE = true;}
      while(mKTZjrBnHP == mKTZjrBnHP){rGUchpcIZt = true;}
      if(InRHMJKVNX == true){InRHMJKVNX = false;}
      if(RUaVLKaleg == true){RUaVLKaleg = false;}
      if(kCdkyxLsWE == true){kCdkyxLsWE = false;}
      if(EWtchTIpKO == true){EWtchTIpKO = false;}
      if(TdWgjRixNZ == true){TdWgjRixNZ = false;}
      if(QPJZeFJfIP == true){QPJZeFJfIP = false;}
      if(yQyIStaynr == true){yQyIStaynr = false;}
      if(CkaQNGfxBg == true){CkaQNGfxBg = false;}
      if(NNfxnoNUxb == true){NNfxnoNUxb = false;}
      if(KbguPCfNNp == true){KbguPCfNNp = false;}
      if(qkJVXeorLY == true){qkJVXeorLY = false;}
      if(ZLebBkkAUd == true){ZLebBkkAUd = false;}
      if(gFALgZEeAL == true){gFALgZEeAL = false;}
      if(ZSiLocDJZI == true){ZSiLocDJZI = false;}
      if(zVIYBywFte == true){zVIYBywFte = false;}
      if(QerjIkjxox == true){QerjIkjxox = false;}
      if(ZJrAyGbTlY == true){ZJrAyGbTlY = false;}
      if(gbaLdKxbKi == true){gbaLdKxbKi = false;}
      if(czkUtuZzCE == true){czkUtuZzCE = false;}
      if(rGUchpcIZt == true){rGUchpcIZt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PUGFJWOEQT
{ 
  void YHCLzaLexf()
  { 
      bool iFATBDVtpX = false;
      bool ojHdUOszOJ = false;
      bool aMOHTVbwui = false;
      bool cesQrTfiTD = false;
      bool KjMAXGGTJu = false;
      bool kzBVpWqsze = false;
      bool aYyHtKqqkB = false;
      bool hJeLypzNiN = false;
      bool PImAxddWZV = false;
      bool cmjnbklFFM = false;
      bool OOhIMbToXA = false;
      bool WcJkPRkyJQ = false;
      bool gUQPXuZpjM = false;
      bool DsIVyAaemV = false;
      bool JnzZzzcyYJ = false;
      bool AnwnftySjR = false;
      bool BdFKwdTmmO = false;
      bool qGKmHrUpPY = false;
      bool RaRZMPxUpD = false;
      bool CIuVTfindV = false;
      string dcaqCkdEzD;
      string sNThCuPZsN;
      string NIyAHozPRn;
      string GEokZDcYCM;
      string VkUriplBff;
      string mAJxuVeajN;
      string lNmLwoYiHz;
      string SpWgqbmFQQ;
      string CxjlBFuqoE;
      string YBooZHyJws;
      string RDsgMwdbFT;
      string hYJTKndBKp;
      string tgtDaRBgHj;
      string ddJWyzEDZE;
      string bSlVVzrUdl;
      string dxzFzkIpFt;
      string twUVpEPlUK;
      string jZbFOauYhb;
      string ZfCVGfdDXN;
      string pNxeJeyPfQ;
      if(dcaqCkdEzD == RDsgMwdbFT){iFATBDVtpX = true;}
      else if(RDsgMwdbFT == dcaqCkdEzD){OOhIMbToXA = true;}
      if(sNThCuPZsN == hYJTKndBKp){ojHdUOszOJ = true;}
      else if(hYJTKndBKp == sNThCuPZsN){WcJkPRkyJQ = true;}
      if(NIyAHozPRn == tgtDaRBgHj){aMOHTVbwui = true;}
      else if(tgtDaRBgHj == NIyAHozPRn){gUQPXuZpjM = true;}
      if(GEokZDcYCM == ddJWyzEDZE){cesQrTfiTD = true;}
      else if(ddJWyzEDZE == GEokZDcYCM){DsIVyAaemV = true;}
      if(VkUriplBff == bSlVVzrUdl){KjMAXGGTJu = true;}
      else if(bSlVVzrUdl == VkUriplBff){JnzZzzcyYJ = true;}
      if(mAJxuVeajN == dxzFzkIpFt){kzBVpWqsze = true;}
      else if(dxzFzkIpFt == mAJxuVeajN){AnwnftySjR = true;}
      if(lNmLwoYiHz == twUVpEPlUK){aYyHtKqqkB = true;}
      else if(twUVpEPlUK == lNmLwoYiHz){BdFKwdTmmO = true;}
      if(SpWgqbmFQQ == jZbFOauYhb){hJeLypzNiN = true;}
      if(CxjlBFuqoE == ZfCVGfdDXN){PImAxddWZV = true;}
      if(YBooZHyJws == pNxeJeyPfQ){cmjnbklFFM = true;}
      while(jZbFOauYhb == SpWgqbmFQQ){qGKmHrUpPY = true;}
      while(ZfCVGfdDXN == ZfCVGfdDXN){RaRZMPxUpD = true;}
      while(pNxeJeyPfQ == pNxeJeyPfQ){CIuVTfindV = true;}
      if(iFATBDVtpX == true){iFATBDVtpX = false;}
      if(ojHdUOszOJ == true){ojHdUOszOJ = false;}
      if(aMOHTVbwui == true){aMOHTVbwui = false;}
      if(cesQrTfiTD == true){cesQrTfiTD = false;}
      if(KjMAXGGTJu == true){KjMAXGGTJu = false;}
      if(kzBVpWqsze == true){kzBVpWqsze = false;}
      if(aYyHtKqqkB == true){aYyHtKqqkB = false;}
      if(hJeLypzNiN == true){hJeLypzNiN = false;}
      if(PImAxddWZV == true){PImAxddWZV = false;}
      if(cmjnbklFFM == true){cmjnbklFFM = false;}
      if(OOhIMbToXA == true){OOhIMbToXA = false;}
      if(WcJkPRkyJQ == true){WcJkPRkyJQ = false;}
      if(gUQPXuZpjM == true){gUQPXuZpjM = false;}
      if(DsIVyAaemV == true){DsIVyAaemV = false;}
      if(JnzZzzcyYJ == true){JnzZzzcyYJ = false;}
      if(AnwnftySjR == true){AnwnftySjR = false;}
      if(BdFKwdTmmO == true){BdFKwdTmmO = false;}
      if(qGKmHrUpPY == true){qGKmHrUpPY = false;}
      if(RaRZMPxUpD == true){RaRZMPxUpD = false;}
      if(CIuVTfindV == true){CIuVTfindV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FBKXOXSMBF
{ 
  void sRbVhwCuOT()
  { 
      bool LtndREhprh = false;
      bool osLBdyiCcz = false;
      bool ClIfLENiRW = false;
      bool dZNsoKOFDI = false;
      bool gGkdklzoPi = false;
      bool LmSCBZlISN = false;
      bool qzYVDPfRLT = false;
      bool jdzTSwBdtZ = false;
      bool EYThLqGKqP = false;
      bool XGmpRhgPZV = false;
      bool GhcwzhnziF = false;
      bool XINrIRepJM = false;
      bool IUawudpIBk = false;
      bool OkDYSWuWic = false;
      bool DHbkqPrtgA = false;
      bool CqFNMlGgAU = false;
      bool qexyqlEoZl = false;
      bool WHGfJBsoEe = false;
      bool lubBiWfpMg = false;
      bool POWOlXJctE = false;
      string RltmVplykw;
      string BxZmhFaYtB;
      string zMyIlIdQIR;
      string ZfnmuVkoPb;
      string ZHuPHdcArZ;
      string jjrngEnkBM;
      string MVoSWVJmqL;
      string UkJRarQhBH;
      string fcYihomAFq;
      string hznDPERbsk;
      string UpJfEyZZMo;
      string nFjsgiwGkg;
      string hJgAdUxGBV;
      string ZnoPloTrdj;
      string ONmQDbPtVg;
      string ILqLCLJICj;
      string BTXpOzQUGq;
      string PDcASUVPxB;
      string FCjUNOxdMa;
      string fKpshupwCE;
      if(RltmVplykw == UpJfEyZZMo){LtndREhprh = true;}
      else if(UpJfEyZZMo == RltmVplykw){GhcwzhnziF = true;}
      if(BxZmhFaYtB == nFjsgiwGkg){osLBdyiCcz = true;}
      else if(nFjsgiwGkg == BxZmhFaYtB){XINrIRepJM = true;}
      if(zMyIlIdQIR == hJgAdUxGBV){ClIfLENiRW = true;}
      else if(hJgAdUxGBV == zMyIlIdQIR){IUawudpIBk = true;}
      if(ZfnmuVkoPb == ZnoPloTrdj){dZNsoKOFDI = true;}
      else if(ZnoPloTrdj == ZfnmuVkoPb){OkDYSWuWic = true;}
      if(ZHuPHdcArZ == ONmQDbPtVg){gGkdklzoPi = true;}
      else if(ONmQDbPtVg == ZHuPHdcArZ){DHbkqPrtgA = true;}
      if(jjrngEnkBM == ILqLCLJICj){LmSCBZlISN = true;}
      else if(ILqLCLJICj == jjrngEnkBM){CqFNMlGgAU = true;}
      if(MVoSWVJmqL == BTXpOzQUGq){qzYVDPfRLT = true;}
      else if(BTXpOzQUGq == MVoSWVJmqL){qexyqlEoZl = true;}
      if(UkJRarQhBH == PDcASUVPxB){jdzTSwBdtZ = true;}
      if(fcYihomAFq == FCjUNOxdMa){EYThLqGKqP = true;}
      if(hznDPERbsk == fKpshupwCE){XGmpRhgPZV = true;}
      while(PDcASUVPxB == UkJRarQhBH){WHGfJBsoEe = true;}
      while(FCjUNOxdMa == FCjUNOxdMa){lubBiWfpMg = true;}
      while(fKpshupwCE == fKpshupwCE){POWOlXJctE = true;}
      if(LtndREhprh == true){LtndREhprh = false;}
      if(osLBdyiCcz == true){osLBdyiCcz = false;}
      if(ClIfLENiRW == true){ClIfLENiRW = false;}
      if(dZNsoKOFDI == true){dZNsoKOFDI = false;}
      if(gGkdklzoPi == true){gGkdklzoPi = false;}
      if(LmSCBZlISN == true){LmSCBZlISN = false;}
      if(qzYVDPfRLT == true){qzYVDPfRLT = false;}
      if(jdzTSwBdtZ == true){jdzTSwBdtZ = false;}
      if(EYThLqGKqP == true){EYThLqGKqP = false;}
      if(XGmpRhgPZV == true){XGmpRhgPZV = false;}
      if(GhcwzhnziF == true){GhcwzhnziF = false;}
      if(XINrIRepJM == true){XINrIRepJM = false;}
      if(IUawudpIBk == true){IUawudpIBk = false;}
      if(OkDYSWuWic == true){OkDYSWuWic = false;}
      if(DHbkqPrtgA == true){DHbkqPrtgA = false;}
      if(CqFNMlGgAU == true){CqFNMlGgAU = false;}
      if(qexyqlEoZl == true){qexyqlEoZl = false;}
      if(WHGfJBsoEe == true){WHGfJBsoEe = false;}
      if(lubBiWfpMg == true){lubBiWfpMg = false;}
      if(POWOlXJctE == true){POWOlXJctE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HCSUGUNOTK
{ 
  void qkhAFNJOyp()
  { 
      bool JMSteJxLMS = false;
      bool brJZnKJwJl = false;
      bool qxfTTUoUsy = false;
      bool QqNmITZOMb = false;
      bool NkZPdWGjFr = false;
      bool KACbTMfzaJ = false;
      bool TbSOCjdVQT = false;
      bool juigYFWQpx = false;
      bool OEPAmQnlTu = false;
      bool nanCHkSKMs = false;
      bool sjSkIPQVCN = false;
      bool oOJduPMRbl = false;
      bool urCVeJGgYn = false;
      bool lLEwDdkdrW = false;
      bool zSiFFZRKGr = false;
      bool XBiaxAhxFy = false;
      bool JjwObdKMZR = false;
      bool dhZFlcJwPF = false;
      bool ruZgPkcdzD = false;
      bool wmXsNPWTdb = false;
      string qMXDbHmCWn;
      string ntcuXqWmsb;
      string TeAAUSVahW;
      string jKoJFLcjEK;
      string WIMrHtatRq;
      string aodteMMWiJ;
      string kLTzDcFSpM;
      string NlhhFKSIsZ;
      string qbIqwufues;
      string yFBuZLnMnd;
      string oIEFcnGwnT;
      string tEdJRJCcDI;
      string xKnwNIkmIt;
      string WFTOjiXCNH;
      string ojGLytbrcQ;
      string ILIffeTHrU;
      string DTmtxnjOYi;
      string kzOwSMDbxS;
      string gsJqkKxmhF;
      string OQKsDUwLOK;
      if(qMXDbHmCWn == oIEFcnGwnT){JMSteJxLMS = true;}
      else if(oIEFcnGwnT == qMXDbHmCWn){sjSkIPQVCN = true;}
      if(ntcuXqWmsb == tEdJRJCcDI){brJZnKJwJl = true;}
      else if(tEdJRJCcDI == ntcuXqWmsb){oOJduPMRbl = true;}
      if(TeAAUSVahW == xKnwNIkmIt){qxfTTUoUsy = true;}
      else if(xKnwNIkmIt == TeAAUSVahW){urCVeJGgYn = true;}
      if(jKoJFLcjEK == WFTOjiXCNH){QqNmITZOMb = true;}
      else if(WFTOjiXCNH == jKoJFLcjEK){lLEwDdkdrW = true;}
      if(WIMrHtatRq == ojGLytbrcQ){NkZPdWGjFr = true;}
      else if(ojGLytbrcQ == WIMrHtatRq){zSiFFZRKGr = true;}
      if(aodteMMWiJ == ILIffeTHrU){KACbTMfzaJ = true;}
      else if(ILIffeTHrU == aodteMMWiJ){XBiaxAhxFy = true;}
      if(kLTzDcFSpM == DTmtxnjOYi){TbSOCjdVQT = true;}
      else if(DTmtxnjOYi == kLTzDcFSpM){JjwObdKMZR = true;}
      if(NlhhFKSIsZ == kzOwSMDbxS){juigYFWQpx = true;}
      if(qbIqwufues == gsJqkKxmhF){OEPAmQnlTu = true;}
      if(yFBuZLnMnd == OQKsDUwLOK){nanCHkSKMs = true;}
      while(kzOwSMDbxS == NlhhFKSIsZ){dhZFlcJwPF = true;}
      while(gsJqkKxmhF == gsJqkKxmhF){ruZgPkcdzD = true;}
      while(OQKsDUwLOK == OQKsDUwLOK){wmXsNPWTdb = true;}
      if(JMSteJxLMS == true){JMSteJxLMS = false;}
      if(brJZnKJwJl == true){brJZnKJwJl = false;}
      if(qxfTTUoUsy == true){qxfTTUoUsy = false;}
      if(QqNmITZOMb == true){QqNmITZOMb = false;}
      if(NkZPdWGjFr == true){NkZPdWGjFr = false;}
      if(KACbTMfzaJ == true){KACbTMfzaJ = false;}
      if(TbSOCjdVQT == true){TbSOCjdVQT = false;}
      if(juigYFWQpx == true){juigYFWQpx = false;}
      if(OEPAmQnlTu == true){OEPAmQnlTu = false;}
      if(nanCHkSKMs == true){nanCHkSKMs = false;}
      if(sjSkIPQVCN == true){sjSkIPQVCN = false;}
      if(oOJduPMRbl == true){oOJduPMRbl = false;}
      if(urCVeJGgYn == true){urCVeJGgYn = false;}
      if(lLEwDdkdrW == true){lLEwDdkdrW = false;}
      if(zSiFFZRKGr == true){zSiFFZRKGr = false;}
      if(XBiaxAhxFy == true){XBiaxAhxFy = false;}
      if(JjwObdKMZR == true){JjwObdKMZR = false;}
      if(dhZFlcJwPF == true){dhZFlcJwPF = false;}
      if(ruZgPkcdzD == true){ruZgPkcdzD = false;}
      if(wmXsNPWTdb == true){wmXsNPWTdb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TVENMMNIJS
{ 
  void YZwGmNuYXf()
  { 
      bool FOmfCLlqYN = false;
      bool tDHQCWcOiM = false;
      bool CKzfszRdIj = false;
      bool OyjpaAgSHq = false;
      bool sRQRCyWgjN = false;
      bool yaRjauOGmC = false;
      bool sHiozwTQpC = false;
      bool pKGrTksgdt = false;
      bool bjttkngzOe = false;
      bool lZeFykhbSG = false;
      bool eFqgXnTYQp = false;
      bool CgcsZIMnDK = false;
      bool OTCLPQfBth = false;
      bool CROWPWsMWx = false;
      bool UHiXcEwkeo = false;
      bool XtXIrKDeRH = false;
      bool HRehnjSFcD = false;
      bool PzRGpGkdiL = false;
      bool TtVFKItFeF = false;
      bool SOuOoCcAjr = false;
      string tClqWCkrmP;
      string AdhAJaFczF;
      string dnxUwqboqI;
      string tCnuzmqgqq;
      string kXlVjXukHL;
      string BnXkfGEQtf;
      string auAdVyplBV;
      string jXlHUFBbkY;
      string wphfGGeDPs;
      string iZmKQpXIAl;
      string gIjkbcCPQZ;
      string EbeVijNUWO;
      string SmWImJkapd;
      string hsbzqnGwDc;
      string DOmonGtQbf;
      string bCkkStkbxR;
      string rbYlrKAfdu;
      string dQQsLEzgTf;
      string OUyKCeIpfx;
      string CeylkboBxd;
      if(tClqWCkrmP == gIjkbcCPQZ){FOmfCLlqYN = true;}
      else if(gIjkbcCPQZ == tClqWCkrmP){eFqgXnTYQp = true;}
      if(AdhAJaFczF == EbeVijNUWO){tDHQCWcOiM = true;}
      else if(EbeVijNUWO == AdhAJaFczF){CgcsZIMnDK = true;}
      if(dnxUwqboqI == SmWImJkapd){CKzfszRdIj = true;}
      else if(SmWImJkapd == dnxUwqboqI){OTCLPQfBth = true;}
      if(tCnuzmqgqq == hsbzqnGwDc){OyjpaAgSHq = true;}
      else if(hsbzqnGwDc == tCnuzmqgqq){CROWPWsMWx = true;}
      if(kXlVjXukHL == DOmonGtQbf){sRQRCyWgjN = true;}
      else if(DOmonGtQbf == kXlVjXukHL){UHiXcEwkeo = true;}
      if(BnXkfGEQtf == bCkkStkbxR){yaRjauOGmC = true;}
      else if(bCkkStkbxR == BnXkfGEQtf){XtXIrKDeRH = true;}
      if(auAdVyplBV == rbYlrKAfdu){sHiozwTQpC = true;}
      else if(rbYlrKAfdu == auAdVyplBV){HRehnjSFcD = true;}
      if(jXlHUFBbkY == dQQsLEzgTf){pKGrTksgdt = true;}
      if(wphfGGeDPs == OUyKCeIpfx){bjttkngzOe = true;}
      if(iZmKQpXIAl == CeylkboBxd){lZeFykhbSG = true;}
      while(dQQsLEzgTf == jXlHUFBbkY){PzRGpGkdiL = true;}
      while(OUyKCeIpfx == OUyKCeIpfx){TtVFKItFeF = true;}
      while(CeylkboBxd == CeylkboBxd){SOuOoCcAjr = true;}
      if(FOmfCLlqYN == true){FOmfCLlqYN = false;}
      if(tDHQCWcOiM == true){tDHQCWcOiM = false;}
      if(CKzfszRdIj == true){CKzfszRdIj = false;}
      if(OyjpaAgSHq == true){OyjpaAgSHq = false;}
      if(sRQRCyWgjN == true){sRQRCyWgjN = false;}
      if(yaRjauOGmC == true){yaRjauOGmC = false;}
      if(sHiozwTQpC == true){sHiozwTQpC = false;}
      if(pKGrTksgdt == true){pKGrTksgdt = false;}
      if(bjttkngzOe == true){bjttkngzOe = false;}
      if(lZeFykhbSG == true){lZeFykhbSG = false;}
      if(eFqgXnTYQp == true){eFqgXnTYQp = false;}
      if(CgcsZIMnDK == true){CgcsZIMnDK = false;}
      if(OTCLPQfBth == true){OTCLPQfBth = false;}
      if(CROWPWsMWx == true){CROWPWsMWx = false;}
      if(UHiXcEwkeo == true){UHiXcEwkeo = false;}
      if(XtXIrKDeRH == true){XtXIrKDeRH = false;}
      if(HRehnjSFcD == true){HRehnjSFcD = false;}
      if(PzRGpGkdiL == true){PzRGpGkdiL = false;}
      if(TtVFKItFeF == true){TtVFKItFeF = false;}
      if(SOuOoCcAjr == true){SOuOoCcAjr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HCBGZRKEOC
{ 
  void FMskHBKFRR()
  { 
      bool kNObsPcWZI = false;
      bool araegrkFGf = false;
      bool IhLFgVhxeG = false;
      bool XhZtqcwrCe = false;
      bool lRQtfqqfCO = false;
      bool qUSNnCBItW = false;
      bool gfqSkrSgnD = false;
      bool urCaspQRYo = false;
      bool dCuQPCOMFn = false;
      bool anxfxGZyJn = false;
      bool YKqySyRrTy = false;
      bool kjjFsejaDh = false;
      bool cFbAbHtWcl = false;
      bool PSHkPTLwxQ = false;
      bool jWrGCqDrlS = false;
      bool VztbKThpVL = false;
      bool DuPhhSbzoY = false;
      bool TmdlxGNVxk = false;
      bool DCjJPQXfZw = false;
      bool lUalMoHKXj = false;
      string QIswbhwsFB;
      string WZWRyyAzOR;
      string DOMVmBRYJF;
      string khKErealgZ;
      string rfHnZflcNN;
      string EkWdsCwWIa;
      string PXizPnOSZT;
      string WOSoYXGXwG;
      string OoLwBzLfKo;
      string hDcFJUxIYk;
      string QTDsppShFV;
      string uXaCMaLmyP;
      string ciHklSlNeE;
      string ZyzLoukSFL;
      string gdaosJcasi;
      string IKJIHhLSHW;
      string DFCBuxYPMQ;
      string osgmizHSqb;
      string pLTwuPoqDG;
      string jSKiHbaYsw;
      if(QIswbhwsFB == QTDsppShFV){kNObsPcWZI = true;}
      else if(QTDsppShFV == QIswbhwsFB){YKqySyRrTy = true;}
      if(WZWRyyAzOR == uXaCMaLmyP){araegrkFGf = true;}
      else if(uXaCMaLmyP == WZWRyyAzOR){kjjFsejaDh = true;}
      if(DOMVmBRYJF == ciHklSlNeE){IhLFgVhxeG = true;}
      else if(ciHklSlNeE == DOMVmBRYJF){cFbAbHtWcl = true;}
      if(khKErealgZ == ZyzLoukSFL){XhZtqcwrCe = true;}
      else if(ZyzLoukSFL == khKErealgZ){PSHkPTLwxQ = true;}
      if(rfHnZflcNN == gdaosJcasi){lRQtfqqfCO = true;}
      else if(gdaosJcasi == rfHnZflcNN){jWrGCqDrlS = true;}
      if(EkWdsCwWIa == IKJIHhLSHW){qUSNnCBItW = true;}
      else if(IKJIHhLSHW == EkWdsCwWIa){VztbKThpVL = true;}
      if(PXizPnOSZT == DFCBuxYPMQ){gfqSkrSgnD = true;}
      else if(DFCBuxYPMQ == PXizPnOSZT){DuPhhSbzoY = true;}
      if(WOSoYXGXwG == osgmizHSqb){urCaspQRYo = true;}
      if(OoLwBzLfKo == pLTwuPoqDG){dCuQPCOMFn = true;}
      if(hDcFJUxIYk == jSKiHbaYsw){anxfxGZyJn = true;}
      while(osgmizHSqb == WOSoYXGXwG){TmdlxGNVxk = true;}
      while(pLTwuPoqDG == pLTwuPoqDG){DCjJPQXfZw = true;}
      while(jSKiHbaYsw == jSKiHbaYsw){lUalMoHKXj = true;}
      if(kNObsPcWZI == true){kNObsPcWZI = false;}
      if(araegrkFGf == true){araegrkFGf = false;}
      if(IhLFgVhxeG == true){IhLFgVhxeG = false;}
      if(XhZtqcwrCe == true){XhZtqcwrCe = false;}
      if(lRQtfqqfCO == true){lRQtfqqfCO = false;}
      if(qUSNnCBItW == true){qUSNnCBItW = false;}
      if(gfqSkrSgnD == true){gfqSkrSgnD = false;}
      if(urCaspQRYo == true){urCaspQRYo = false;}
      if(dCuQPCOMFn == true){dCuQPCOMFn = false;}
      if(anxfxGZyJn == true){anxfxGZyJn = false;}
      if(YKqySyRrTy == true){YKqySyRrTy = false;}
      if(kjjFsejaDh == true){kjjFsejaDh = false;}
      if(cFbAbHtWcl == true){cFbAbHtWcl = false;}
      if(PSHkPTLwxQ == true){PSHkPTLwxQ = false;}
      if(jWrGCqDrlS == true){jWrGCqDrlS = false;}
      if(VztbKThpVL == true){VztbKThpVL = false;}
      if(DuPhhSbzoY == true){DuPhhSbzoY = false;}
      if(TmdlxGNVxk == true){TmdlxGNVxk = false;}
      if(DCjJPQXfZw == true){DCjJPQXfZw = false;}
      if(lUalMoHKXj == true){lUalMoHKXj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FAWYNYUVMT
{ 
  void JwnKEwzJys()
  { 
      bool jSNPYyLRab = false;
      bool SzcDVIiKjb = false;
      bool LtomeaSjSC = false;
      bool xXPTBAnGgG = false;
      bool bJqnFuGyfM = false;
      bool QMgUKocZjy = false;
      bool fayYduiJBU = false;
      bool TbcdACDBhj = false;
      bool TUDGlkpuIL = false;
      bool WOViZAKSJK = false;
      bool LxwLsniDTI = false;
      bool lbrAeLXqms = false;
      bool EnApxFGtDz = false;
      bool qjqXXWXrNy = false;
      bool BmaAYuVUEN = false;
      bool cSfQFXwFNn = false;
      bool gozUQBjUcH = false;
      bool mfdorRNAQC = false;
      bool ikpoWXEaRA = false;
      bool ZSeZQLmGiX = false;
      string jlZcnFwwaB;
      string AyQamTdcYw;
      string rMujDPTZsq;
      string Wsgczxhntj;
      string xeIOOUYuNT;
      string aAwMOWpoZX;
      string lVDidHQmbp;
      string koinzNEgVi;
      string qXMYQWwUOb;
      string GsOWybbYjH;
      string DkTWhkRHNB;
      string SJTpfOIdSH;
      string KwYziraMpX;
      string kfwNeGDoqe;
      string EoHMJxYYpj;
      string SxFcxHLTno;
      string KFRoPlNFKZ;
      string KTlnCUoMpk;
      string TCVGFmaSQX;
      string tjBCUzXRwW;
      if(jlZcnFwwaB == DkTWhkRHNB){jSNPYyLRab = true;}
      else if(DkTWhkRHNB == jlZcnFwwaB){LxwLsniDTI = true;}
      if(AyQamTdcYw == SJTpfOIdSH){SzcDVIiKjb = true;}
      else if(SJTpfOIdSH == AyQamTdcYw){lbrAeLXqms = true;}
      if(rMujDPTZsq == KwYziraMpX){LtomeaSjSC = true;}
      else if(KwYziraMpX == rMujDPTZsq){EnApxFGtDz = true;}
      if(Wsgczxhntj == kfwNeGDoqe){xXPTBAnGgG = true;}
      else if(kfwNeGDoqe == Wsgczxhntj){qjqXXWXrNy = true;}
      if(xeIOOUYuNT == EoHMJxYYpj){bJqnFuGyfM = true;}
      else if(EoHMJxYYpj == xeIOOUYuNT){BmaAYuVUEN = true;}
      if(aAwMOWpoZX == SxFcxHLTno){QMgUKocZjy = true;}
      else if(SxFcxHLTno == aAwMOWpoZX){cSfQFXwFNn = true;}
      if(lVDidHQmbp == KFRoPlNFKZ){fayYduiJBU = true;}
      else if(KFRoPlNFKZ == lVDidHQmbp){gozUQBjUcH = true;}
      if(koinzNEgVi == KTlnCUoMpk){TbcdACDBhj = true;}
      if(qXMYQWwUOb == TCVGFmaSQX){TUDGlkpuIL = true;}
      if(GsOWybbYjH == tjBCUzXRwW){WOViZAKSJK = true;}
      while(KTlnCUoMpk == koinzNEgVi){mfdorRNAQC = true;}
      while(TCVGFmaSQX == TCVGFmaSQX){ikpoWXEaRA = true;}
      while(tjBCUzXRwW == tjBCUzXRwW){ZSeZQLmGiX = true;}
      if(jSNPYyLRab == true){jSNPYyLRab = false;}
      if(SzcDVIiKjb == true){SzcDVIiKjb = false;}
      if(LtomeaSjSC == true){LtomeaSjSC = false;}
      if(xXPTBAnGgG == true){xXPTBAnGgG = false;}
      if(bJqnFuGyfM == true){bJqnFuGyfM = false;}
      if(QMgUKocZjy == true){QMgUKocZjy = false;}
      if(fayYduiJBU == true){fayYduiJBU = false;}
      if(TbcdACDBhj == true){TbcdACDBhj = false;}
      if(TUDGlkpuIL == true){TUDGlkpuIL = false;}
      if(WOViZAKSJK == true){WOViZAKSJK = false;}
      if(LxwLsniDTI == true){LxwLsniDTI = false;}
      if(lbrAeLXqms == true){lbrAeLXqms = false;}
      if(EnApxFGtDz == true){EnApxFGtDz = false;}
      if(qjqXXWXrNy == true){qjqXXWXrNy = false;}
      if(BmaAYuVUEN == true){BmaAYuVUEN = false;}
      if(cSfQFXwFNn == true){cSfQFXwFNn = false;}
      if(gozUQBjUcH == true){gozUQBjUcH = false;}
      if(mfdorRNAQC == true){mfdorRNAQC = false;}
      if(ikpoWXEaRA == true){ikpoWXEaRA = false;}
      if(ZSeZQLmGiX == true){ZSeZQLmGiX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class USRYJTAVSL
{ 
  void KSdDTVyhap()
  { 
      bool OJGyLhwEsI = false;
      bool HepKmLyLQN = false;
      bool ebzexhAwpy = false;
      bool bOPdbIWaLg = false;
      bool TOSRJlWmZI = false;
      bool CRIfSmKbAd = false;
      bool hzOtfsOMhd = false;
      bool nWzjtPIhUL = false;
      bool KMVhuKFiLo = false;
      bool xuZhzTAXkQ = false;
      bool XKEuTeRYlC = false;
      bool dcHoSUcgyV = false;
      bool meAsfsxRja = false;
      bool PjwEmAIaNP = false;
      bool rgxJKUmkPe = false;
      bool pTYPcrJLPZ = false;
      bool hAnLlsfDBR = false;
      bool MCShdGhqhL = false;
      bool GLBFjwLgbu = false;
      bool qwKmhqslWR = false;
      string RacqRRKlIl;
      string zPnnAZaLuo;
      string tMHwaOSWgD;
      string XEkfjNbemh;
      string QnphbUhufF;
      string UkbCGFSgPD;
      string zmEENudIDm;
      string xwXNYFVZUF;
      string gXqbimbiYe;
      string tuOjicjlTg;
      string qYqsIXMOcA;
      string isMKWbwcVa;
      string StiXrChnew;
      string VjFmNHfyTK;
      string aNGYwBiDNG;
      string fGPsNwpSAG;
      string pYigdzmYwO;
      string uyJKAFnKbp;
      string SdZXPPTLZR;
      string RNxNUBdZtx;
      if(RacqRRKlIl == qYqsIXMOcA){OJGyLhwEsI = true;}
      else if(qYqsIXMOcA == RacqRRKlIl){XKEuTeRYlC = true;}
      if(zPnnAZaLuo == isMKWbwcVa){HepKmLyLQN = true;}
      else if(isMKWbwcVa == zPnnAZaLuo){dcHoSUcgyV = true;}
      if(tMHwaOSWgD == StiXrChnew){ebzexhAwpy = true;}
      else if(StiXrChnew == tMHwaOSWgD){meAsfsxRja = true;}
      if(XEkfjNbemh == VjFmNHfyTK){bOPdbIWaLg = true;}
      else if(VjFmNHfyTK == XEkfjNbemh){PjwEmAIaNP = true;}
      if(QnphbUhufF == aNGYwBiDNG){TOSRJlWmZI = true;}
      else if(aNGYwBiDNG == QnphbUhufF){rgxJKUmkPe = true;}
      if(UkbCGFSgPD == fGPsNwpSAG){CRIfSmKbAd = true;}
      else if(fGPsNwpSAG == UkbCGFSgPD){pTYPcrJLPZ = true;}
      if(zmEENudIDm == pYigdzmYwO){hzOtfsOMhd = true;}
      else if(pYigdzmYwO == zmEENudIDm){hAnLlsfDBR = true;}
      if(xwXNYFVZUF == uyJKAFnKbp){nWzjtPIhUL = true;}
      if(gXqbimbiYe == SdZXPPTLZR){KMVhuKFiLo = true;}
      if(tuOjicjlTg == RNxNUBdZtx){xuZhzTAXkQ = true;}
      while(uyJKAFnKbp == xwXNYFVZUF){MCShdGhqhL = true;}
      while(SdZXPPTLZR == SdZXPPTLZR){GLBFjwLgbu = true;}
      while(RNxNUBdZtx == RNxNUBdZtx){qwKmhqslWR = true;}
      if(OJGyLhwEsI == true){OJGyLhwEsI = false;}
      if(HepKmLyLQN == true){HepKmLyLQN = false;}
      if(ebzexhAwpy == true){ebzexhAwpy = false;}
      if(bOPdbIWaLg == true){bOPdbIWaLg = false;}
      if(TOSRJlWmZI == true){TOSRJlWmZI = false;}
      if(CRIfSmKbAd == true){CRIfSmKbAd = false;}
      if(hzOtfsOMhd == true){hzOtfsOMhd = false;}
      if(nWzjtPIhUL == true){nWzjtPIhUL = false;}
      if(KMVhuKFiLo == true){KMVhuKFiLo = false;}
      if(xuZhzTAXkQ == true){xuZhzTAXkQ = false;}
      if(XKEuTeRYlC == true){XKEuTeRYlC = false;}
      if(dcHoSUcgyV == true){dcHoSUcgyV = false;}
      if(meAsfsxRja == true){meAsfsxRja = false;}
      if(PjwEmAIaNP == true){PjwEmAIaNP = false;}
      if(rgxJKUmkPe == true){rgxJKUmkPe = false;}
      if(pTYPcrJLPZ == true){pTYPcrJLPZ = false;}
      if(hAnLlsfDBR == true){hAnLlsfDBR = false;}
      if(MCShdGhqhL == true){MCShdGhqhL = false;}
      if(GLBFjwLgbu == true){GLBFjwLgbu = false;}
      if(qwKmhqslWR == true){qwKmhqslWR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EDZIENZGPZ
{ 
  void msPbotraIG()
  { 
      bool wptgCKmOPg = false;
      bool AWoJGjVXLU = false;
      bool lVfosrHDHi = false;
      bool JUssgYVlML = false;
      bool fbAAMHjkLL = false;
      bool IWhakaJEnK = false;
      bool CjHfXfdubh = false;
      bool NjLAnKUebk = false;
      bool HVrwallSHF = false;
      bool OQxCIwUUcg = false;
      bool dnIdxXLhma = false;
      bool FdcCCfqKEl = false;
      bool sLnVSxlIqq = false;
      bool oACtHTNNzC = false;
      bool ZEffzjnuzb = false;
      bool EJPpnSAlKz = false;
      bool lCpulFbhui = false;
      bool ScKCLneHWi = false;
      bool JqJPmekMGn = false;
      bool TbDAQXOjtt = false;
      string OOpmdpMOWt;
      string bRtJYYhzXf;
      string GAcMYnmBbO;
      string ggiTCzQqJV;
      string FHYXTpMgWy;
      string ECZpQNkcOp;
      string DLmHMtiaHY;
      string IqpCayaFsi;
      string bFdcJeGrCn;
      string NncSRsTQLY;
      string GkZxoNLXPS;
      string mfieOxhJyg;
      string mqYSLTNWjg;
      string dJtTbpffnu;
      string SibjBhFxET;
      string LJSdlOLGlV;
      string AnnhnclOCX;
      string RBVDNEOoRc;
      string OPSPVTqPhN;
      string eYtRudutuX;
      if(OOpmdpMOWt == GkZxoNLXPS){wptgCKmOPg = true;}
      else if(GkZxoNLXPS == OOpmdpMOWt){dnIdxXLhma = true;}
      if(bRtJYYhzXf == mfieOxhJyg){AWoJGjVXLU = true;}
      else if(mfieOxhJyg == bRtJYYhzXf){FdcCCfqKEl = true;}
      if(GAcMYnmBbO == mqYSLTNWjg){lVfosrHDHi = true;}
      else if(mqYSLTNWjg == GAcMYnmBbO){sLnVSxlIqq = true;}
      if(ggiTCzQqJV == dJtTbpffnu){JUssgYVlML = true;}
      else if(dJtTbpffnu == ggiTCzQqJV){oACtHTNNzC = true;}
      if(FHYXTpMgWy == SibjBhFxET){fbAAMHjkLL = true;}
      else if(SibjBhFxET == FHYXTpMgWy){ZEffzjnuzb = true;}
      if(ECZpQNkcOp == LJSdlOLGlV){IWhakaJEnK = true;}
      else if(LJSdlOLGlV == ECZpQNkcOp){EJPpnSAlKz = true;}
      if(DLmHMtiaHY == AnnhnclOCX){CjHfXfdubh = true;}
      else if(AnnhnclOCX == DLmHMtiaHY){lCpulFbhui = true;}
      if(IqpCayaFsi == RBVDNEOoRc){NjLAnKUebk = true;}
      if(bFdcJeGrCn == OPSPVTqPhN){HVrwallSHF = true;}
      if(NncSRsTQLY == eYtRudutuX){OQxCIwUUcg = true;}
      while(RBVDNEOoRc == IqpCayaFsi){ScKCLneHWi = true;}
      while(OPSPVTqPhN == OPSPVTqPhN){JqJPmekMGn = true;}
      while(eYtRudutuX == eYtRudutuX){TbDAQXOjtt = true;}
      if(wptgCKmOPg == true){wptgCKmOPg = false;}
      if(AWoJGjVXLU == true){AWoJGjVXLU = false;}
      if(lVfosrHDHi == true){lVfosrHDHi = false;}
      if(JUssgYVlML == true){JUssgYVlML = false;}
      if(fbAAMHjkLL == true){fbAAMHjkLL = false;}
      if(IWhakaJEnK == true){IWhakaJEnK = false;}
      if(CjHfXfdubh == true){CjHfXfdubh = false;}
      if(NjLAnKUebk == true){NjLAnKUebk = false;}
      if(HVrwallSHF == true){HVrwallSHF = false;}
      if(OQxCIwUUcg == true){OQxCIwUUcg = false;}
      if(dnIdxXLhma == true){dnIdxXLhma = false;}
      if(FdcCCfqKEl == true){FdcCCfqKEl = false;}
      if(sLnVSxlIqq == true){sLnVSxlIqq = false;}
      if(oACtHTNNzC == true){oACtHTNNzC = false;}
      if(ZEffzjnuzb == true){ZEffzjnuzb = false;}
      if(EJPpnSAlKz == true){EJPpnSAlKz = false;}
      if(lCpulFbhui == true){lCpulFbhui = false;}
      if(ScKCLneHWi == true){ScKCLneHWi = false;}
      if(JqJPmekMGn == true){JqJPmekMGn = false;}
      if(TbDAQXOjtt == true){TbDAQXOjtt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MKGLKFNCVK
{ 
  void DhLwIIUtym()
  { 
      bool hWyesFGVsc = false;
      bool yFwGmPmLNw = false;
      bool mmGgBMdrEu = false;
      bool oUaqDZQDWt = false;
      bool lCVpejYVHV = false;
      bool yKMiWtPRcf = false;
      bool bNRynddFCN = false;
      bool yjoSJkRQCQ = false;
      bool mHkhxdHrUI = false;
      bool JzZpSYkXCA = false;
      bool GTSsXOVtYl = false;
      bool czPLsTciAJ = false;
      bool VkjsDzJyzk = false;
      bool AsNBJToqKi = false;
      bool INSifKiNxz = false;
      bool uBWrdVjYoY = false;
      bool EWtnlikNBY = false;
      bool ekYRBIRBNs = false;
      bool PuBAoyWVXn = false;
      bool jPCkdkTexx = false;
      string AAeygEPmTu;
      string pgtLnCkODw;
      string hAxkTzHENp;
      string YMlVTjaVwd;
      string xjwncVKOTF;
      string UqtYZADseh;
      string wLYcWcuXqD;
      string bPSZyxDIIx;
      string orjHVgSNwS;
      string fhpOglLSRz;
      string amWPdEYUZb;
      string wtjgrEaRGp;
      string KhaXXsYDrL;
      string lkqJWBUUdQ;
      string HymUVkxJVc;
      string LsLbosLyrj;
      string eVbNoLDaKq;
      string iGmphLtGBl;
      string wPhPAsYPTc;
      string oVbtklWZeK;
      if(AAeygEPmTu == amWPdEYUZb){hWyesFGVsc = true;}
      else if(amWPdEYUZb == AAeygEPmTu){GTSsXOVtYl = true;}
      if(pgtLnCkODw == wtjgrEaRGp){yFwGmPmLNw = true;}
      else if(wtjgrEaRGp == pgtLnCkODw){czPLsTciAJ = true;}
      if(hAxkTzHENp == KhaXXsYDrL){mmGgBMdrEu = true;}
      else if(KhaXXsYDrL == hAxkTzHENp){VkjsDzJyzk = true;}
      if(YMlVTjaVwd == lkqJWBUUdQ){oUaqDZQDWt = true;}
      else if(lkqJWBUUdQ == YMlVTjaVwd){AsNBJToqKi = true;}
      if(xjwncVKOTF == HymUVkxJVc){lCVpejYVHV = true;}
      else if(HymUVkxJVc == xjwncVKOTF){INSifKiNxz = true;}
      if(UqtYZADseh == LsLbosLyrj){yKMiWtPRcf = true;}
      else if(LsLbosLyrj == UqtYZADseh){uBWrdVjYoY = true;}
      if(wLYcWcuXqD == eVbNoLDaKq){bNRynddFCN = true;}
      else if(eVbNoLDaKq == wLYcWcuXqD){EWtnlikNBY = true;}
      if(bPSZyxDIIx == iGmphLtGBl){yjoSJkRQCQ = true;}
      if(orjHVgSNwS == wPhPAsYPTc){mHkhxdHrUI = true;}
      if(fhpOglLSRz == oVbtklWZeK){JzZpSYkXCA = true;}
      while(iGmphLtGBl == bPSZyxDIIx){ekYRBIRBNs = true;}
      while(wPhPAsYPTc == wPhPAsYPTc){PuBAoyWVXn = true;}
      while(oVbtklWZeK == oVbtklWZeK){jPCkdkTexx = true;}
      if(hWyesFGVsc == true){hWyesFGVsc = false;}
      if(yFwGmPmLNw == true){yFwGmPmLNw = false;}
      if(mmGgBMdrEu == true){mmGgBMdrEu = false;}
      if(oUaqDZQDWt == true){oUaqDZQDWt = false;}
      if(lCVpejYVHV == true){lCVpejYVHV = false;}
      if(yKMiWtPRcf == true){yKMiWtPRcf = false;}
      if(bNRynddFCN == true){bNRynddFCN = false;}
      if(yjoSJkRQCQ == true){yjoSJkRQCQ = false;}
      if(mHkhxdHrUI == true){mHkhxdHrUI = false;}
      if(JzZpSYkXCA == true){JzZpSYkXCA = false;}
      if(GTSsXOVtYl == true){GTSsXOVtYl = false;}
      if(czPLsTciAJ == true){czPLsTciAJ = false;}
      if(VkjsDzJyzk == true){VkjsDzJyzk = false;}
      if(AsNBJToqKi == true){AsNBJToqKi = false;}
      if(INSifKiNxz == true){INSifKiNxz = false;}
      if(uBWrdVjYoY == true){uBWrdVjYoY = false;}
      if(EWtnlikNBY == true){EWtnlikNBY = false;}
      if(ekYRBIRBNs == true){ekYRBIRBNs = false;}
      if(PuBAoyWVXn == true){PuBAoyWVXn = false;}
      if(jPCkdkTexx == true){jPCkdkTexx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BYAXDTLZZQ
{ 
  void qRXDJsVMRk()
  { 
      bool EnjVrwThzg = false;
      bool mQETqTPlba = false;
      bool fUBaIiRFun = false;
      bool TjCcNxErAr = false;
      bool cofMPlCACO = false;
      bool JepbHjlJMI = false;
      bool eNmLMDOaGs = false;
      bool OXlixpooKW = false;
      bool gQDgentaUd = false;
      bool KufqMOCTAM = false;
      bool WasIzksGdR = false;
      bool uxyoaNKGgX = false;
      bool JnGbiTqtWh = false;
      bool nUoyAGWtgs = false;
      bool tmwDiMxqPy = false;
      bool DwmbDiURZf = false;
      bool tzjucZIAoU = false;
      bool qQYmdVrCsV = false;
      bool WAdXdrhMtQ = false;
      bool lFTBzuCAZJ = false;
      string dIUOrGOVmJ;
      string QdNelagyzo;
      string oXrzQdfBeM;
      string QgPPmONmhY;
      string ogHVkrBXiK;
      string HoepyFPVyO;
      string ZMpZrjNxrW;
      string MsPZAIQWNY;
      string cISTFbBZRg;
      string yqoTzbpgdB;
      string dDfLxNYFop;
      string nsHZlRsVUP;
      string hmfKXUEuZX;
      string RjsMtZbHVq;
      string CwjasFjPhh;
      string iTLNSpWVmc;
      string JdeRXEAueM;
      string olzcNlDFRS;
      string koNroxXfsD;
      string DGUshYRSCn;
      if(dIUOrGOVmJ == dDfLxNYFop){EnjVrwThzg = true;}
      else if(dDfLxNYFop == dIUOrGOVmJ){WasIzksGdR = true;}
      if(QdNelagyzo == nsHZlRsVUP){mQETqTPlba = true;}
      else if(nsHZlRsVUP == QdNelagyzo){uxyoaNKGgX = true;}
      if(oXrzQdfBeM == hmfKXUEuZX){fUBaIiRFun = true;}
      else if(hmfKXUEuZX == oXrzQdfBeM){JnGbiTqtWh = true;}
      if(QgPPmONmhY == RjsMtZbHVq){TjCcNxErAr = true;}
      else if(RjsMtZbHVq == QgPPmONmhY){nUoyAGWtgs = true;}
      if(ogHVkrBXiK == CwjasFjPhh){cofMPlCACO = true;}
      else if(CwjasFjPhh == ogHVkrBXiK){tmwDiMxqPy = true;}
      if(HoepyFPVyO == iTLNSpWVmc){JepbHjlJMI = true;}
      else if(iTLNSpWVmc == HoepyFPVyO){DwmbDiURZf = true;}
      if(ZMpZrjNxrW == JdeRXEAueM){eNmLMDOaGs = true;}
      else if(JdeRXEAueM == ZMpZrjNxrW){tzjucZIAoU = true;}
      if(MsPZAIQWNY == olzcNlDFRS){OXlixpooKW = true;}
      if(cISTFbBZRg == koNroxXfsD){gQDgentaUd = true;}
      if(yqoTzbpgdB == DGUshYRSCn){KufqMOCTAM = true;}
      while(olzcNlDFRS == MsPZAIQWNY){qQYmdVrCsV = true;}
      while(koNroxXfsD == koNroxXfsD){WAdXdrhMtQ = true;}
      while(DGUshYRSCn == DGUshYRSCn){lFTBzuCAZJ = true;}
      if(EnjVrwThzg == true){EnjVrwThzg = false;}
      if(mQETqTPlba == true){mQETqTPlba = false;}
      if(fUBaIiRFun == true){fUBaIiRFun = false;}
      if(TjCcNxErAr == true){TjCcNxErAr = false;}
      if(cofMPlCACO == true){cofMPlCACO = false;}
      if(JepbHjlJMI == true){JepbHjlJMI = false;}
      if(eNmLMDOaGs == true){eNmLMDOaGs = false;}
      if(OXlixpooKW == true){OXlixpooKW = false;}
      if(gQDgentaUd == true){gQDgentaUd = false;}
      if(KufqMOCTAM == true){KufqMOCTAM = false;}
      if(WasIzksGdR == true){WasIzksGdR = false;}
      if(uxyoaNKGgX == true){uxyoaNKGgX = false;}
      if(JnGbiTqtWh == true){JnGbiTqtWh = false;}
      if(nUoyAGWtgs == true){nUoyAGWtgs = false;}
      if(tmwDiMxqPy == true){tmwDiMxqPy = false;}
      if(DwmbDiURZf == true){DwmbDiURZf = false;}
      if(tzjucZIAoU == true){tzjucZIAoU = false;}
      if(qQYmdVrCsV == true){qQYmdVrCsV = false;}
      if(WAdXdrhMtQ == true){WAdXdrhMtQ = false;}
      if(lFTBzuCAZJ == true){lFTBzuCAZJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TKSBLWXKQZ
{ 
  void xpDjBDFhsr()
  { 
      bool uEUVqLosMN = false;
      bool ExaXTTTRZI = false;
      bool DYeElWAFFN = false;
      bool EaPTsTeBBz = false;
      bool OUUBNBPswD = false;
      bool CSuMkWZQiU = false;
      bool KinzIchHdz = false;
      bool oRPatiDdqk = false;
      bool GGJBKleDhW = false;
      bool tNRgnefVrj = false;
      bool TIOwOjDURC = false;
      bool TwZyNEZlnW = false;
      bool xdYHFaAhlO = false;
      bool CgkGQyqMmZ = false;
      bool hKkfDynTTj = false;
      bool FthVlpiHqn = false;
      bool jUiCAlKShP = false;
      bool MMyNnmrsDG = false;
      bool lgOBJHzPTa = false;
      bool OjVzpNaifQ = false;
      string UHDkRaCOOo;
      string BHNPeFWnKU;
      string qqwlUMGVPo;
      string KKUmnzZxgP;
      string GnPXfsbcks;
      string kcEnedKRQE;
      string TgzYdqlaaf;
      string eYHtNDaYGa;
      string jdjVEhFgIK;
      string nIgbwZnpsn;
      string GBBFOMUJZa;
      string ClKoUpwcUw;
      string kFSQqVreyn;
      string OjeRTibeHr;
      string MuHgHCxqHF;
      string cKVxDBikNr;
      string UpKkMRGsVl;
      string NRVcjoxkJo;
      string YAWsKDOhOR;
      string zqRPWVkVUo;
      if(UHDkRaCOOo == GBBFOMUJZa){uEUVqLosMN = true;}
      else if(GBBFOMUJZa == UHDkRaCOOo){TIOwOjDURC = true;}
      if(BHNPeFWnKU == ClKoUpwcUw){ExaXTTTRZI = true;}
      else if(ClKoUpwcUw == BHNPeFWnKU){TwZyNEZlnW = true;}
      if(qqwlUMGVPo == kFSQqVreyn){DYeElWAFFN = true;}
      else if(kFSQqVreyn == qqwlUMGVPo){xdYHFaAhlO = true;}
      if(KKUmnzZxgP == OjeRTibeHr){EaPTsTeBBz = true;}
      else if(OjeRTibeHr == KKUmnzZxgP){CgkGQyqMmZ = true;}
      if(GnPXfsbcks == MuHgHCxqHF){OUUBNBPswD = true;}
      else if(MuHgHCxqHF == GnPXfsbcks){hKkfDynTTj = true;}
      if(kcEnedKRQE == cKVxDBikNr){CSuMkWZQiU = true;}
      else if(cKVxDBikNr == kcEnedKRQE){FthVlpiHqn = true;}
      if(TgzYdqlaaf == UpKkMRGsVl){KinzIchHdz = true;}
      else if(UpKkMRGsVl == TgzYdqlaaf){jUiCAlKShP = true;}
      if(eYHtNDaYGa == NRVcjoxkJo){oRPatiDdqk = true;}
      if(jdjVEhFgIK == YAWsKDOhOR){GGJBKleDhW = true;}
      if(nIgbwZnpsn == zqRPWVkVUo){tNRgnefVrj = true;}
      while(NRVcjoxkJo == eYHtNDaYGa){MMyNnmrsDG = true;}
      while(YAWsKDOhOR == YAWsKDOhOR){lgOBJHzPTa = true;}
      while(zqRPWVkVUo == zqRPWVkVUo){OjVzpNaifQ = true;}
      if(uEUVqLosMN == true){uEUVqLosMN = false;}
      if(ExaXTTTRZI == true){ExaXTTTRZI = false;}
      if(DYeElWAFFN == true){DYeElWAFFN = false;}
      if(EaPTsTeBBz == true){EaPTsTeBBz = false;}
      if(OUUBNBPswD == true){OUUBNBPswD = false;}
      if(CSuMkWZQiU == true){CSuMkWZQiU = false;}
      if(KinzIchHdz == true){KinzIchHdz = false;}
      if(oRPatiDdqk == true){oRPatiDdqk = false;}
      if(GGJBKleDhW == true){GGJBKleDhW = false;}
      if(tNRgnefVrj == true){tNRgnefVrj = false;}
      if(TIOwOjDURC == true){TIOwOjDURC = false;}
      if(TwZyNEZlnW == true){TwZyNEZlnW = false;}
      if(xdYHFaAhlO == true){xdYHFaAhlO = false;}
      if(CgkGQyqMmZ == true){CgkGQyqMmZ = false;}
      if(hKkfDynTTj == true){hKkfDynTTj = false;}
      if(FthVlpiHqn == true){FthVlpiHqn = false;}
      if(jUiCAlKShP == true){jUiCAlKShP = false;}
      if(MMyNnmrsDG == true){MMyNnmrsDG = false;}
      if(lgOBJHzPTa == true){lgOBJHzPTa = false;}
      if(OjVzpNaifQ == true){OjVzpNaifQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NPALAAEIZL
{ 
  void LZZczKPtjZ()
  { 
      bool RuXpVDzQfO = false;
      bool SXQAhaWIFq = false;
      bool tnxcKRerzV = false;
      bool DIWsmaYkBc = false;
      bool RCbOBsXBgk = false;
      bool VBNezdytfD = false;
      bool YHRJKJAXMH = false;
      bool ClGbZqLhbR = false;
      bool scKNACuqsJ = false;
      bool cdExDJjSEq = false;
      bool rznZiitkFH = false;
      bool RPSNKuxDJH = false;
      bool OJeCeXhIYQ = false;
      bool HsdkYtnkeQ = false;
      bool IKlkqMLpmH = false;
      bool MgIxbiUltL = false;
      bool BkLnAYlhoQ = false;
      bool HLXryEWtLR = false;
      bool LqVREZjfIp = false;
      bool ZCpTPXyxjR = false;
      string gDNwoqCEZt;
      string EllAuXXiuf;
      string bGAsyEAiNH;
      string BdzypPYbMT;
      string qXnuGLeIDw;
      string jPHqkZDUxj;
      string qSqRsZmmKe;
      string yuWboEREmm;
      string ZqfQXkVHNP;
      string MEebbXfWCf;
      string YqyXynsfCg;
      string IygKJzmZtH;
      string EeZtSsQtzQ;
      string XuCGNhsHSi;
      string rpEfHNWTSb;
      string jGbtbsREFE;
      string WzflINuawb;
      string GfGKONasmF;
      string VwbXgRSHdT;
      string QoBOLsJSWt;
      if(gDNwoqCEZt == YqyXynsfCg){RuXpVDzQfO = true;}
      else if(YqyXynsfCg == gDNwoqCEZt){rznZiitkFH = true;}
      if(EllAuXXiuf == IygKJzmZtH){SXQAhaWIFq = true;}
      else if(IygKJzmZtH == EllAuXXiuf){RPSNKuxDJH = true;}
      if(bGAsyEAiNH == EeZtSsQtzQ){tnxcKRerzV = true;}
      else if(EeZtSsQtzQ == bGAsyEAiNH){OJeCeXhIYQ = true;}
      if(BdzypPYbMT == XuCGNhsHSi){DIWsmaYkBc = true;}
      else if(XuCGNhsHSi == BdzypPYbMT){HsdkYtnkeQ = true;}
      if(qXnuGLeIDw == rpEfHNWTSb){RCbOBsXBgk = true;}
      else if(rpEfHNWTSb == qXnuGLeIDw){IKlkqMLpmH = true;}
      if(jPHqkZDUxj == jGbtbsREFE){VBNezdytfD = true;}
      else if(jGbtbsREFE == jPHqkZDUxj){MgIxbiUltL = true;}
      if(qSqRsZmmKe == WzflINuawb){YHRJKJAXMH = true;}
      else if(WzflINuawb == qSqRsZmmKe){BkLnAYlhoQ = true;}
      if(yuWboEREmm == GfGKONasmF){ClGbZqLhbR = true;}
      if(ZqfQXkVHNP == VwbXgRSHdT){scKNACuqsJ = true;}
      if(MEebbXfWCf == QoBOLsJSWt){cdExDJjSEq = true;}
      while(GfGKONasmF == yuWboEREmm){HLXryEWtLR = true;}
      while(VwbXgRSHdT == VwbXgRSHdT){LqVREZjfIp = true;}
      while(QoBOLsJSWt == QoBOLsJSWt){ZCpTPXyxjR = true;}
      if(RuXpVDzQfO == true){RuXpVDzQfO = false;}
      if(SXQAhaWIFq == true){SXQAhaWIFq = false;}
      if(tnxcKRerzV == true){tnxcKRerzV = false;}
      if(DIWsmaYkBc == true){DIWsmaYkBc = false;}
      if(RCbOBsXBgk == true){RCbOBsXBgk = false;}
      if(VBNezdytfD == true){VBNezdytfD = false;}
      if(YHRJKJAXMH == true){YHRJKJAXMH = false;}
      if(ClGbZqLhbR == true){ClGbZqLhbR = false;}
      if(scKNACuqsJ == true){scKNACuqsJ = false;}
      if(cdExDJjSEq == true){cdExDJjSEq = false;}
      if(rznZiitkFH == true){rznZiitkFH = false;}
      if(RPSNKuxDJH == true){RPSNKuxDJH = false;}
      if(OJeCeXhIYQ == true){OJeCeXhIYQ = false;}
      if(HsdkYtnkeQ == true){HsdkYtnkeQ = false;}
      if(IKlkqMLpmH == true){IKlkqMLpmH = false;}
      if(MgIxbiUltL == true){MgIxbiUltL = false;}
      if(BkLnAYlhoQ == true){BkLnAYlhoQ = false;}
      if(HLXryEWtLR == true){HLXryEWtLR = false;}
      if(LqVREZjfIp == true){LqVREZjfIp = false;}
      if(ZCpTPXyxjR == true){ZCpTPXyxjR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSAOXSKCHJ
{ 
  void uWQEqAmNDd()
  { 
      bool auBKwSTLHF = false;
      bool zDXAVFmdVS = false;
      bool CmjOzLohgs = false;
      bool kcBhYfYhIC = false;
      bool yLCdxmzqXt = false;
      bool xHeCznLlKk = false;
      bool dldOUVCobp = false;
      bool fFVTTqjGQM = false;
      bool LxKlucyzik = false;
      bool TlWWXMgmIb = false;
      bool kJOhNrlLhI = false;
      bool DFUyYfbrSr = false;
      bool XDGpVthyuH = false;
      bool JwxoaCibXD = false;
      bool qlQahOQXyr = false;
      bool joUQDhCYLT = false;
      bool JmQZyGHfXV = false;
      bool xzTPAklfIH = false;
      bool cJzCWUbgls = false;
      bool zJQEsDVpba = false;
      string xSmJwdaCMP;
      string PhcMcmtzsK;
      string skxdyPJiDC;
      string bjIoemDIrO;
      string ROPUyYsFPX;
      string DixFfLVJKg;
      string TryKneZmgp;
      string jkGdseVbeY;
      string WESeysmDIT;
      string RsyLtYPFgT;
      string zFXZnSbSLB;
      string psdkJPZTMu;
      string qVdNYpmujU;
      string PPuLZRgsqe;
      string QUrHcXOMCe;
      string zwrkbcaJBx;
      string efiqlZxSLq;
      string hfbgdWdWkA;
      string bZsEUSWKiw;
      string qWqszklAVC;
      if(xSmJwdaCMP == zFXZnSbSLB){auBKwSTLHF = true;}
      else if(zFXZnSbSLB == xSmJwdaCMP){kJOhNrlLhI = true;}
      if(PhcMcmtzsK == psdkJPZTMu){zDXAVFmdVS = true;}
      else if(psdkJPZTMu == PhcMcmtzsK){DFUyYfbrSr = true;}
      if(skxdyPJiDC == qVdNYpmujU){CmjOzLohgs = true;}
      else if(qVdNYpmujU == skxdyPJiDC){XDGpVthyuH = true;}
      if(bjIoemDIrO == PPuLZRgsqe){kcBhYfYhIC = true;}
      else if(PPuLZRgsqe == bjIoemDIrO){JwxoaCibXD = true;}
      if(ROPUyYsFPX == QUrHcXOMCe){yLCdxmzqXt = true;}
      else if(QUrHcXOMCe == ROPUyYsFPX){qlQahOQXyr = true;}
      if(DixFfLVJKg == zwrkbcaJBx){xHeCznLlKk = true;}
      else if(zwrkbcaJBx == DixFfLVJKg){joUQDhCYLT = true;}
      if(TryKneZmgp == efiqlZxSLq){dldOUVCobp = true;}
      else if(efiqlZxSLq == TryKneZmgp){JmQZyGHfXV = true;}
      if(jkGdseVbeY == hfbgdWdWkA){fFVTTqjGQM = true;}
      if(WESeysmDIT == bZsEUSWKiw){LxKlucyzik = true;}
      if(RsyLtYPFgT == qWqszklAVC){TlWWXMgmIb = true;}
      while(hfbgdWdWkA == jkGdseVbeY){xzTPAklfIH = true;}
      while(bZsEUSWKiw == bZsEUSWKiw){cJzCWUbgls = true;}
      while(qWqszklAVC == qWqszklAVC){zJQEsDVpba = true;}
      if(auBKwSTLHF == true){auBKwSTLHF = false;}
      if(zDXAVFmdVS == true){zDXAVFmdVS = false;}
      if(CmjOzLohgs == true){CmjOzLohgs = false;}
      if(kcBhYfYhIC == true){kcBhYfYhIC = false;}
      if(yLCdxmzqXt == true){yLCdxmzqXt = false;}
      if(xHeCznLlKk == true){xHeCznLlKk = false;}
      if(dldOUVCobp == true){dldOUVCobp = false;}
      if(fFVTTqjGQM == true){fFVTTqjGQM = false;}
      if(LxKlucyzik == true){LxKlucyzik = false;}
      if(TlWWXMgmIb == true){TlWWXMgmIb = false;}
      if(kJOhNrlLhI == true){kJOhNrlLhI = false;}
      if(DFUyYfbrSr == true){DFUyYfbrSr = false;}
      if(XDGpVthyuH == true){XDGpVthyuH = false;}
      if(JwxoaCibXD == true){JwxoaCibXD = false;}
      if(qlQahOQXyr == true){qlQahOQXyr = false;}
      if(joUQDhCYLT == true){joUQDhCYLT = false;}
      if(JmQZyGHfXV == true){JmQZyGHfXV = false;}
      if(xzTPAklfIH == true){xzTPAklfIH = false;}
      if(cJzCWUbgls == true){cJzCWUbgls = false;}
      if(zJQEsDVpba == true){zJQEsDVpba = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TLOGAXZGMG
{ 
  void PJrKquscRw()
  { 
      bool kIJgVWxDmI = false;
      bool TEDoqGNPzT = false;
      bool etgNiRghKI = false;
      bool rmmQrkhRdI = false;
      bool hxTuydZulf = false;
      bool XizouqauxD = false;
      bool oOrePfRmxG = false;
      bool XwkqkhalOF = false;
      bool rludkInxUB = false;
      bool KmTaSSEneR = false;
      bool LlyfIayIEM = false;
      bool QofrKDTNsH = false;
      bool rUSuukcKXS = false;
      bool dlHxsGmOVK = false;
      bool KesHkVGaPP = false;
      bool zpuWYqTCjW = false;
      bool xmkkidgiyD = false;
      bool PErixMaKKZ = false;
      bool eBtHSmpjXB = false;
      bool mkdzMWtHYG = false;
      string xAGAkeSCZV;
      string axJrYyNqZy;
      string dctKEtsKjW;
      string SbGJHhcnrW;
      string SDndDLEbYu;
      string FJhdNUGuwq;
      string kHRCCzqzjq;
      string VYzCeanPHr;
      string oQloRJtbum;
      string bgrBlLllaE;
      string UFrhZfKfym;
      string gpnDBUVbjs;
      string FOExOngxQT;
      string oBoCXjYDPl;
      string yNcHFlsozQ;
      string oJBhzFBuSl;
      string yMOdyeAkfR;
      string uSMytqlwqc;
      string tqyzeeAGDR;
      string idkdmlzyJa;
      if(xAGAkeSCZV == UFrhZfKfym){kIJgVWxDmI = true;}
      else if(UFrhZfKfym == xAGAkeSCZV){LlyfIayIEM = true;}
      if(axJrYyNqZy == gpnDBUVbjs){TEDoqGNPzT = true;}
      else if(gpnDBUVbjs == axJrYyNqZy){QofrKDTNsH = true;}
      if(dctKEtsKjW == FOExOngxQT){etgNiRghKI = true;}
      else if(FOExOngxQT == dctKEtsKjW){rUSuukcKXS = true;}
      if(SbGJHhcnrW == oBoCXjYDPl){rmmQrkhRdI = true;}
      else if(oBoCXjYDPl == SbGJHhcnrW){dlHxsGmOVK = true;}
      if(SDndDLEbYu == yNcHFlsozQ){hxTuydZulf = true;}
      else if(yNcHFlsozQ == SDndDLEbYu){KesHkVGaPP = true;}
      if(FJhdNUGuwq == oJBhzFBuSl){XizouqauxD = true;}
      else if(oJBhzFBuSl == FJhdNUGuwq){zpuWYqTCjW = true;}
      if(kHRCCzqzjq == yMOdyeAkfR){oOrePfRmxG = true;}
      else if(yMOdyeAkfR == kHRCCzqzjq){xmkkidgiyD = true;}
      if(VYzCeanPHr == uSMytqlwqc){XwkqkhalOF = true;}
      if(oQloRJtbum == tqyzeeAGDR){rludkInxUB = true;}
      if(bgrBlLllaE == idkdmlzyJa){KmTaSSEneR = true;}
      while(uSMytqlwqc == VYzCeanPHr){PErixMaKKZ = true;}
      while(tqyzeeAGDR == tqyzeeAGDR){eBtHSmpjXB = true;}
      while(idkdmlzyJa == idkdmlzyJa){mkdzMWtHYG = true;}
      if(kIJgVWxDmI == true){kIJgVWxDmI = false;}
      if(TEDoqGNPzT == true){TEDoqGNPzT = false;}
      if(etgNiRghKI == true){etgNiRghKI = false;}
      if(rmmQrkhRdI == true){rmmQrkhRdI = false;}
      if(hxTuydZulf == true){hxTuydZulf = false;}
      if(XizouqauxD == true){XizouqauxD = false;}
      if(oOrePfRmxG == true){oOrePfRmxG = false;}
      if(XwkqkhalOF == true){XwkqkhalOF = false;}
      if(rludkInxUB == true){rludkInxUB = false;}
      if(KmTaSSEneR == true){KmTaSSEneR = false;}
      if(LlyfIayIEM == true){LlyfIayIEM = false;}
      if(QofrKDTNsH == true){QofrKDTNsH = false;}
      if(rUSuukcKXS == true){rUSuukcKXS = false;}
      if(dlHxsGmOVK == true){dlHxsGmOVK = false;}
      if(KesHkVGaPP == true){KesHkVGaPP = false;}
      if(zpuWYqTCjW == true){zpuWYqTCjW = false;}
      if(xmkkidgiyD == true){xmkkidgiyD = false;}
      if(PErixMaKKZ == true){PErixMaKKZ = false;}
      if(eBtHSmpjXB == true){eBtHSmpjXB = false;}
      if(mkdzMWtHYG == true){mkdzMWtHYG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PGNOJPGKVO
{ 
  void IJuunJiaNF()
  { 
      bool yHHlPMaWdN = false;
      bool mjaKXKdqcy = false;
      bool RaBnlpXiNA = false;
      bool SdRrMkBuPI = false;
      bool weFJpmrXgj = false;
      bool VQKtlXGSzZ = false;
      bool nrIctJSixl = false;
      bool JhaTBmUryz = false;
      bool yABcdCTWFo = false;
      bool eiupUEVcOf = false;
      bool UJZuanoqrz = false;
      bool COTzanpfzr = false;
      bool pucIHalkyw = false;
      bool RrcReoZGCp = false;
      bool MbeGlPOuPg = false;
      bool OodWpYfRmA = false;
      bool BErugKkCUl = false;
      bool NjcIeNPWVq = false;
      bool LqURhbOGbF = false;
      bool JISCoIjiYb = false;
      string PpHNPpsKQD;
      string jEuzTqWijD;
      string IdJRXDLnoa;
      string pTdwIPDPiE;
      string jusDLhSftc;
      string JoJFWkfopL;
      string eFVoMQZzpD;
      string mHAeSMkFGp;
      string ketLQAJXYX;
      string iOZWYdZDqu;
      string HToppBodlJ;
      string AZiAazKKXL;
      string GCZSUYhdGn;
      string mgOKhQoEVO;
      string LfkPWJfYwZ;
      string SPfenEtWVQ;
      string TLXyWSKXRJ;
      string JGnIAaQKuK;
      string sIhfUXBjWc;
      string WShFuAHmrD;
      if(PpHNPpsKQD == HToppBodlJ){yHHlPMaWdN = true;}
      else if(HToppBodlJ == PpHNPpsKQD){UJZuanoqrz = true;}
      if(jEuzTqWijD == AZiAazKKXL){mjaKXKdqcy = true;}
      else if(AZiAazKKXL == jEuzTqWijD){COTzanpfzr = true;}
      if(IdJRXDLnoa == GCZSUYhdGn){RaBnlpXiNA = true;}
      else if(GCZSUYhdGn == IdJRXDLnoa){pucIHalkyw = true;}
      if(pTdwIPDPiE == mgOKhQoEVO){SdRrMkBuPI = true;}
      else if(mgOKhQoEVO == pTdwIPDPiE){RrcReoZGCp = true;}
      if(jusDLhSftc == LfkPWJfYwZ){weFJpmrXgj = true;}
      else if(LfkPWJfYwZ == jusDLhSftc){MbeGlPOuPg = true;}
      if(JoJFWkfopL == SPfenEtWVQ){VQKtlXGSzZ = true;}
      else if(SPfenEtWVQ == JoJFWkfopL){OodWpYfRmA = true;}
      if(eFVoMQZzpD == TLXyWSKXRJ){nrIctJSixl = true;}
      else if(TLXyWSKXRJ == eFVoMQZzpD){BErugKkCUl = true;}
      if(mHAeSMkFGp == JGnIAaQKuK){JhaTBmUryz = true;}
      if(ketLQAJXYX == sIhfUXBjWc){yABcdCTWFo = true;}
      if(iOZWYdZDqu == WShFuAHmrD){eiupUEVcOf = true;}
      while(JGnIAaQKuK == mHAeSMkFGp){NjcIeNPWVq = true;}
      while(sIhfUXBjWc == sIhfUXBjWc){LqURhbOGbF = true;}
      while(WShFuAHmrD == WShFuAHmrD){JISCoIjiYb = true;}
      if(yHHlPMaWdN == true){yHHlPMaWdN = false;}
      if(mjaKXKdqcy == true){mjaKXKdqcy = false;}
      if(RaBnlpXiNA == true){RaBnlpXiNA = false;}
      if(SdRrMkBuPI == true){SdRrMkBuPI = false;}
      if(weFJpmrXgj == true){weFJpmrXgj = false;}
      if(VQKtlXGSzZ == true){VQKtlXGSzZ = false;}
      if(nrIctJSixl == true){nrIctJSixl = false;}
      if(JhaTBmUryz == true){JhaTBmUryz = false;}
      if(yABcdCTWFo == true){yABcdCTWFo = false;}
      if(eiupUEVcOf == true){eiupUEVcOf = false;}
      if(UJZuanoqrz == true){UJZuanoqrz = false;}
      if(COTzanpfzr == true){COTzanpfzr = false;}
      if(pucIHalkyw == true){pucIHalkyw = false;}
      if(RrcReoZGCp == true){RrcReoZGCp = false;}
      if(MbeGlPOuPg == true){MbeGlPOuPg = false;}
      if(OodWpYfRmA == true){OodWpYfRmA = false;}
      if(BErugKkCUl == true){BErugKkCUl = false;}
      if(NjcIeNPWVq == true){NjcIeNPWVq = false;}
      if(LqURhbOGbF == true){LqURhbOGbF = false;}
      if(JISCoIjiYb == true){JISCoIjiYb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HBMEZJJKCH
{ 
  void yNaSVFhPXk()
  { 
      bool cqEqESLpSq = false;
      bool qAIBQgQiRA = false;
      bool iGCxgFkfEM = false;
      bool ZrgdWymkVQ = false;
      bool FKwXoACbBJ = false;
      bool sAoicVnGJz = false;
      bool gflGRySeeS = false;
      bool tfMAtXJdIg = false;
      bool CIetSYDxBA = false;
      bool KfbWiZYpGp = false;
      bool gXxiPNnnnE = false;
      bool MJybwYAqms = false;
      bool uVceINDpRU = false;
      bool zSXRAeLueF = false;
      bool kOIxmAhzZK = false;
      bool YgDMuKtRaB = false;
      bool JxWTEskfaQ = false;
      bool MFMhIfMfqH = false;
      bool eEPGuSPLWp = false;
      bool ksUdumrors = false;
      string QBZatwcqzi;
      string tTWZwsSqHt;
      string FJFVDxcDkX;
      string NtlGXWyITP;
      string BqYkCgyjYC;
      string IQxLJGwDXx;
      string SYGaVzhPBY;
      string uKXrsNjUTV;
      string zrehOwxZxQ;
      string atjWwbkxOC;
      string yhizHysERu;
      string VbjByatYLZ;
      string BHRjyAZAuQ;
      string clFQXQJeZQ;
      string CrHBuzKhYV;
      string hLloAqQyBH;
      string YrIBRiVSdh;
      string QOzuWJzQoz;
      string pqbZiRAPPg;
      string ALdSqJiGiL;
      if(QBZatwcqzi == yhizHysERu){cqEqESLpSq = true;}
      else if(yhizHysERu == QBZatwcqzi){gXxiPNnnnE = true;}
      if(tTWZwsSqHt == VbjByatYLZ){qAIBQgQiRA = true;}
      else if(VbjByatYLZ == tTWZwsSqHt){MJybwYAqms = true;}
      if(FJFVDxcDkX == BHRjyAZAuQ){iGCxgFkfEM = true;}
      else if(BHRjyAZAuQ == FJFVDxcDkX){uVceINDpRU = true;}
      if(NtlGXWyITP == clFQXQJeZQ){ZrgdWymkVQ = true;}
      else if(clFQXQJeZQ == NtlGXWyITP){zSXRAeLueF = true;}
      if(BqYkCgyjYC == CrHBuzKhYV){FKwXoACbBJ = true;}
      else if(CrHBuzKhYV == BqYkCgyjYC){kOIxmAhzZK = true;}
      if(IQxLJGwDXx == hLloAqQyBH){sAoicVnGJz = true;}
      else if(hLloAqQyBH == IQxLJGwDXx){YgDMuKtRaB = true;}
      if(SYGaVzhPBY == YrIBRiVSdh){gflGRySeeS = true;}
      else if(YrIBRiVSdh == SYGaVzhPBY){JxWTEskfaQ = true;}
      if(uKXrsNjUTV == QOzuWJzQoz){tfMAtXJdIg = true;}
      if(zrehOwxZxQ == pqbZiRAPPg){CIetSYDxBA = true;}
      if(atjWwbkxOC == ALdSqJiGiL){KfbWiZYpGp = true;}
      while(QOzuWJzQoz == uKXrsNjUTV){MFMhIfMfqH = true;}
      while(pqbZiRAPPg == pqbZiRAPPg){eEPGuSPLWp = true;}
      while(ALdSqJiGiL == ALdSqJiGiL){ksUdumrors = true;}
      if(cqEqESLpSq == true){cqEqESLpSq = false;}
      if(qAIBQgQiRA == true){qAIBQgQiRA = false;}
      if(iGCxgFkfEM == true){iGCxgFkfEM = false;}
      if(ZrgdWymkVQ == true){ZrgdWymkVQ = false;}
      if(FKwXoACbBJ == true){FKwXoACbBJ = false;}
      if(sAoicVnGJz == true){sAoicVnGJz = false;}
      if(gflGRySeeS == true){gflGRySeeS = false;}
      if(tfMAtXJdIg == true){tfMAtXJdIg = false;}
      if(CIetSYDxBA == true){CIetSYDxBA = false;}
      if(KfbWiZYpGp == true){KfbWiZYpGp = false;}
      if(gXxiPNnnnE == true){gXxiPNnnnE = false;}
      if(MJybwYAqms == true){MJybwYAqms = false;}
      if(uVceINDpRU == true){uVceINDpRU = false;}
      if(zSXRAeLueF == true){zSXRAeLueF = false;}
      if(kOIxmAhzZK == true){kOIxmAhzZK = false;}
      if(YgDMuKtRaB == true){YgDMuKtRaB = false;}
      if(JxWTEskfaQ == true){JxWTEskfaQ = false;}
      if(MFMhIfMfqH == true){MFMhIfMfqH = false;}
      if(eEPGuSPLWp == true){eEPGuSPLWp = false;}
      if(ksUdumrors == true){ksUdumrors = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BGTBNOAPEI
{ 
  void MTwglFYnYg()
  { 
      bool HNsQzcDuoK = false;
      bool ISmRVqpPMb = false;
      bool BMayjBnaAY = false;
      bool xMmpziFAsI = false;
      bool UhbbmNmztu = false;
      bool dksHQumtgy = false;
      bool obtPNuexSm = false;
      bool koWDGTjyLV = false;
      bool OngEuLTeYD = false;
      bool wLTuTsmMOq = false;
      bool hogHJnOpBx = false;
      bool KniKiAtpUB = false;
      bool bAXOqZVajN = false;
      bool fXiTnYHZtG = false;
      bool wddasHbIMS = false;
      bool yxrNPhQRPj = false;
      bool RmFmQlEOVJ = false;
      bool rUuNEyVxUi = false;
      bool yMOQOieVEF = false;
      bool IpJKnJXpKG = false;
      string hiHPfjuXAG;
      string SyUaGTlstq;
      string HiDiYZOnYb;
      string FSzKjuKuZx;
      string nTXCTAHqcz;
      string UYbXHzeYpF;
      string VHzYAAzKpK;
      string JqSwCnKBOY;
      string SWKYHgpaDk;
      string QkETagUzBS;
      string AwASpcFeUS;
      string odJRmyxZQT;
      string JYGEsXlyVV;
      string SKzwXVVqhd;
      string aKFjwlamgb;
      string ithhJbowYS;
      string pGJzAddNtQ;
      string bFqmsyTWIH;
      string wzQslXcRmu;
      string fZRPmTBGjS;
      if(hiHPfjuXAG == AwASpcFeUS){HNsQzcDuoK = true;}
      else if(AwASpcFeUS == hiHPfjuXAG){hogHJnOpBx = true;}
      if(SyUaGTlstq == odJRmyxZQT){ISmRVqpPMb = true;}
      else if(odJRmyxZQT == SyUaGTlstq){KniKiAtpUB = true;}
      if(HiDiYZOnYb == JYGEsXlyVV){BMayjBnaAY = true;}
      else if(JYGEsXlyVV == HiDiYZOnYb){bAXOqZVajN = true;}
      if(FSzKjuKuZx == SKzwXVVqhd){xMmpziFAsI = true;}
      else if(SKzwXVVqhd == FSzKjuKuZx){fXiTnYHZtG = true;}
      if(nTXCTAHqcz == aKFjwlamgb){UhbbmNmztu = true;}
      else if(aKFjwlamgb == nTXCTAHqcz){wddasHbIMS = true;}
      if(UYbXHzeYpF == ithhJbowYS){dksHQumtgy = true;}
      else if(ithhJbowYS == UYbXHzeYpF){yxrNPhQRPj = true;}
      if(VHzYAAzKpK == pGJzAddNtQ){obtPNuexSm = true;}
      else if(pGJzAddNtQ == VHzYAAzKpK){RmFmQlEOVJ = true;}
      if(JqSwCnKBOY == bFqmsyTWIH){koWDGTjyLV = true;}
      if(SWKYHgpaDk == wzQslXcRmu){OngEuLTeYD = true;}
      if(QkETagUzBS == fZRPmTBGjS){wLTuTsmMOq = true;}
      while(bFqmsyTWIH == JqSwCnKBOY){rUuNEyVxUi = true;}
      while(wzQslXcRmu == wzQslXcRmu){yMOQOieVEF = true;}
      while(fZRPmTBGjS == fZRPmTBGjS){IpJKnJXpKG = true;}
      if(HNsQzcDuoK == true){HNsQzcDuoK = false;}
      if(ISmRVqpPMb == true){ISmRVqpPMb = false;}
      if(BMayjBnaAY == true){BMayjBnaAY = false;}
      if(xMmpziFAsI == true){xMmpziFAsI = false;}
      if(UhbbmNmztu == true){UhbbmNmztu = false;}
      if(dksHQumtgy == true){dksHQumtgy = false;}
      if(obtPNuexSm == true){obtPNuexSm = false;}
      if(koWDGTjyLV == true){koWDGTjyLV = false;}
      if(OngEuLTeYD == true){OngEuLTeYD = false;}
      if(wLTuTsmMOq == true){wLTuTsmMOq = false;}
      if(hogHJnOpBx == true){hogHJnOpBx = false;}
      if(KniKiAtpUB == true){KniKiAtpUB = false;}
      if(bAXOqZVajN == true){bAXOqZVajN = false;}
      if(fXiTnYHZtG == true){fXiTnYHZtG = false;}
      if(wddasHbIMS == true){wddasHbIMS = false;}
      if(yxrNPhQRPj == true){yxrNPhQRPj = false;}
      if(RmFmQlEOVJ == true){RmFmQlEOVJ = false;}
      if(rUuNEyVxUi == true){rUuNEyVxUi = false;}
      if(yMOQOieVEF == true){yMOQOieVEF = false;}
      if(IpJKnJXpKG == true){IpJKnJXpKG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XKGNNBSOVW
{ 
  void epLUYszonC()
  { 
      bool iMZcLcmUMx = false;
      bool ouaAsTFMWT = false;
      bool pylJVIJVcj = false;
      bool XbOePNxMLN = false;
      bool lnRSEFzkHI = false;
      bool BTcapkaQHD = false;
      bool SQqbYNfuke = false;
      bool WsAJhCfSEP = false;
      bool IXOUiEymnd = false;
      bool lfFItUwosq = false;
      bool YDAblHSTsm = false;
      bool FIMqtuBWsT = false;
      bool OsGGspnqOM = false;
      bool FpZNqFWlha = false;
      bool kesBYdTNOz = false;
      bool SZuYbewtiu = false;
      bool TbEghOhzAn = false;
      bool XPnSijAFhO = false;
      bool WZbPseuAkL = false;
      bool JcClGJZLSK = false;
      string oHAnuIRmkf;
      string GajkuNQZbH;
      string NXPtIPYnOy;
      string uVraeNoXHX;
      string kbniGoKiri;
      string kEFAMRqGff;
      string jdYmkkhJFh;
      string XrREWligmS;
      string EpwfMpQrNN;
      string WhqamGDAyV;
      string HAdKKrmAda;
      string hKTNathsZt;
      string TpwqKpBpQP;
      string iihRKELkVT;
      string DPNmfLOcAs;
      string YKZDBQElzU;
      string qwjNrzbBCW;
      string hwWFqEbJLz;
      string aXpXpYIdPs;
      string AZlBcGfAug;
      if(oHAnuIRmkf == HAdKKrmAda){iMZcLcmUMx = true;}
      else if(HAdKKrmAda == oHAnuIRmkf){YDAblHSTsm = true;}
      if(GajkuNQZbH == hKTNathsZt){ouaAsTFMWT = true;}
      else if(hKTNathsZt == GajkuNQZbH){FIMqtuBWsT = true;}
      if(NXPtIPYnOy == TpwqKpBpQP){pylJVIJVcj = true;}
      else if(TpwqKpBpQP == NXPtIPYnOy){OsGGspnqOM = true;}
      if(uVraeNoXHX == iihRKELkVT){XbOePNxMLN = true;}
      else if(iihRKELkVT == uVraeNoXHX){FpZNqFWlha = true;}
      if(kbniGoKiri == DPNmfLOcAs){lnRSEFzkHI = true;}
      else if(DPNmfLOcAs == kbniGoKiri){kesBYdTNOz = true;}
      if(kEFAMRqGff == YKZDBQElzU){BTcapkaQHD = true;}
      else if(YKZDBQElzU == kEFAMRqGff){SZuYbewtiu = true;}
      if(jdYmkkhJFh == qwjNrzbBCW){SQqbYNfuke = true;}
      else if(qwjNrzbBCW == jdYmkkhJFh){TbEghOhzAn = true;}
      if(XrREWligmS == hwWFqEbJLz){WsAJhCfSEP = true;}
      if(EpwfMpQrNN == aXpXpYIdPs){IXOUiEymnd = true;}
      if(WhqamGDAyV == AZlBcGfAug){lfFItUwosq = true;}
      while(hwWFqEbJLz == XrREWligmS){XPnSijAFhO = true;}
      while(aXpXpYIdPs == aXpXpYIdPs){WZbPseuAkL = true;}
      while(AZlBcGfAug == AZlBcGfAug){JcClGJZLSK = true;}
      if(iMZcLcmUMx == true){iMZcLcmUMx = false;}
      if(ouaAsTFMWT == true){ouaAsTFMWT = false;}
      if(pylJVIJVcj == true){pylJVIJVcj = false;}
      if(XbOePNxMLN == true){XbOePNxMLN = false;}
      if(lnRSEFzkHI == true){lnRSEFzkHI = false;}
      if(BTcapkaQHD == true){BTcapkaQHD = false;}
      if(SQqbYNfuke == true){SQqbYNfuke = false;}
      if(WsAJhCfSEP == true){WsAJhCfSEP = false;}
      if(IXOUiEymnd == true){IXOUiEymnd = false;}
      if(lfFItUwosq == true){lfFItUwosq = false;}
      if(YDAblHSTsm == true){YDAblHSTsm = false;}
      if(FIMqtuBWsT == true){FIMqtuBWsT = false;}
      if(OsGGspnqOM == true){OsGGspnqOM = false;}
      if(FpZNqFWlha == true){FpZNqFWlha = false;}
      if(kesBYdTNOz == true){kesBYdTNOz = false;}
      if(SZuYbewtiu == true){SZuYbewtiu = false;}
      if(TbEghOhzAn == true){TbEghOhzAn = false;}
      if(XPnSijAFhO == true){XPnSijAFhO = false;}
      if(WZbPseuAkL == true){WZbPseuAkL = false;}
      if(JcClGJZLSK == true){JcClGJZLSK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YDCHNTSYAB
{ 
  void faAtWuaNPh()
  { 
      bool sXhwDDaftr = false;
      bool yLjsluMOxu = false;
      bool qfcBAfwtVq = false;
      bool GzawOnklar = false;
      bool bqPTkusdtA = false;
      bool oRKNXNufuX = false;
      bool GfJClykmdx = false;
      bool JZnFSzQJQF = false;
      bool mRAVCooMXB = false;
      bool sFpDkwgMgl = false;
      bool JFzwpOcFtY = false;
      bool wkOpjnfnAw = false;
      bool JXObEEjjUW = false;
      bool REbeugRDem = false;
      bool LiSzEHpzSw = false;
      bool PsLkckpXqk = false;
      bool eskWGrJjuC = false;
      bool VbINkZFPWx = false;
      bool NjRXHXrqCJ = false;
      bool qtLtHSyurM = false;
      string prhjmohDiZ;
      string SdfxCkNMZG;
      string WKaMzkxXwu;
      string GoFatnQfOl;
      string YMOxYpsnGs;
      string idarNfQUkB;
      string qJHnScXFDN;
      string UhymgKucnI;
      string qJQCLcONMN;
      string WuuMuOFZeu;
      string RnkrXBfmLD;
      string jngbJhrEbp;
      string OKroqZlkrR;
      string EVyrpCYYdK;
      string waBIdiNSDN;
      string WBxnfHwuBy;
      string OttszOookG;
      string JTZRsmIjLI;
      string MSheuDXJLi;
      string GcWfuCgIJO;
      if(prhjmohDiZ == RnkrXBfmLD){sXhwDDaftr = true;}
      else if(RnkrXBfmLD == prhjmohDiZ){JFzwpOcFtY = true;}
      if(SdfxCkNMZG == jngbJhrEbp){yLjsluMOxu = true;}
      else if(jngbJhrEbp == SdfxCkNMZG){wkOpjnfnAw = true;}
      if(WKaMzkxXwu == OKroqZlkrR){qfcBAfwtVq = true;}
      else if(OKroqZlkrR == WKaMzkxXwu){JXObEEjjUW = true;}
      if(GoFatnQfOl == EVyrpCYYdK){GzawOnklar = true;}
      else if(EVyrpCYYdK == GoFatnQfOl){REbeugRDem = true;}
      if(YMOxYpsnGs == waBIdiNSDN){bqPTkusdtA = true;}
      else if(waBIdiNSDN == YMOxYpsnGs){LiSzEHpzSw = true;}
      if(idarNfQUkB == WBxnfHwuBy){oRKNXNufuX = true;}
      else if(WBxnfHwuBy == idarNfQUkB){PsLkckpXqk = true;}
      if(qJHnScXFDN == OttszOookG){GfJClykmdx = true;}
      else if(OttszOookG == qJHnScXFDN){eskWGrJjuC = true;}
      if(UhymgKucnI == JTZRsmIjLI){JZnFSzQJQF = true;}
      if(qJQCLcONMN == MSheuDXJLi){mRAVCooMXB = true;}
      if(WuuMuOFZeu == GcWfuCgIJO){sFpDkwgMgl = true;}
      while(JTZRsmIjLI == UhymgKucnI){VbINkZFPWx = true;}
      while(MSheuDXJLi == MSheuDXJLi){NjRXHXrqCJ = true;}
      while(GcWfuCgIJO == GcWfuCgIJO){qtLtHSyurM = true;}
      if(sXhwDDaftr == true){sXhwDDaftr = false;}
      if(yLjsluMOxu == true){yLjsluMOxu = false;}
      if(qfcBAfwtVq == true){qfcBAfwtVq = false;}
      if(GzawOnklar == true){GzawOnklar = false;}
      if(bqPTkusdtA == true){bqPTkusdtA = false;}
      if(oRKNXNufuX == true){oRKNXNufuX = false;}
      if(GfJClykmdx == true){GfJClykmdx = false;}
      if(JZnFSzQJQF == true){JZnFSzQJQF = false;}
      if(mRAVCooMXB == true){mRAVCooMXB = false;}
      if(sFpDkwgMgl == true){sFpDkwgMgl = false;}
      if(JFzwpOcFtY == true){JFzwpOcFtY = false;}
      if(wkOpjnfnAw == true){wkOpjnfnAw = false;}
      if(JXObEEjjUW == true){JXObEEjjUW = false;}
      if(REbeugRDem == true){REbeugRDem = false;}
      if(LiSzEHpzSw == true){LiSzEHpzSw = false;}
      if(PsLkckpXqk == true){PsLkckpXqk = false;}
      if(eskWGrJjuC == true){eskWGrJjuC = false;}
      if(VbINkZFPWx == true){VbINkZFPWx = false;}
      if(NjRXHXrqCJ == true){NjRXHXrqCJ = false;}
      if(qtLtHSyurM == true){qtLtHSyurM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LISSRULIOK
{ 
  void FJHsidHDxi()
  { 
      bool mUHafhUgYf = false;
      bool hqVMYHWean = false;
      bool aiFXyzGAlc = false;
      bool amhUOPjgrf = false;
      bool LutRVePire = false;
      bool qjeSLEPibg = false;
      bool bTtuFuJAxI = false;
      bool WomubenmCS = false;
      bool iXHGlpHOJK = false;
      bool AAFLEqAzMZ = false;
      bool VPkjHBxjpf = false;
      bool PbfIxDMnJO = false;
      bool ntqlHWjbpk = false;
      bool eoabxTlXyj = false;
      bool sWYcuYUwNA = false;
      bool dMoylbXybk = false;
      bool RVsEBZBDLc = false;
      bool RnoYUQVNqi = false;
      bool BmNpGRzbpV = false;
      bool wmuNSXcTbU = false;
      string McjxqgePXz;
      string tuXbakOOaX;
      string QfDHrVnyaC;
      string kVTwFDbwpO;
      string cTjQFsXxed;
      string qIHiifZbFV;
      string sfoUOXabVW;
      string JRYMuxwlCy;
      string ypSwLcOjMZ;
      string dzqTUweOCg;
      string SuaIUZiunl;
      string jmZHXCMsJk;
      string JpPwsKaEqy;
      string RgjVeCPKak;
      string sSwaopYiwS;
      string jlEQWbfdPJ;
      string yeDoTCCEbV;
      string lBRXqptnHC;
      string kqIYNfbTyD;
      string WluQlOPGGl;
      if(McjxqgePXz == SuaIUZiunl){mUHafhUgYf = true;}
      else if(SuaIUZiunl == McjxqgePXz){VPkjHBxjpf = true;}
      if(tuXbakOOaX == jmZHXCMsJk){hqVMYHWean = true;}
      else if(jmZHXCMsJk == tuXbakOOaX){PbfIxDMnJO = true;}
      if(QfDHrVnyaC == JpPwsKaEqy){aiFXyzGAlc = true;}
      else if(JpPwsKaEqy == QfDHrVnyaC){ntqlHWjbpk = true;}
      if(kVTwFDbwpO == RgjVeCPKak){amhUOPjgrf = true;}
      else if(RgjVeCPKak == kVTwFDbwpO){eoabxTlXyj = true;}
      if(cTjQFsXxed == sSwaopYiwS){LutRVePire = true;}
      else if(sSwaopYiwS == cTjQFsXxed){sWYcuYUwNA = true;}
      if(qIHiifZbFV == jlEQWbfdPJ){qjeSLEPibg = true;}
      else if(jlEQWbfdPJ == qIHiifZbFV){dMoylbXybk = true;}
      if(sfoUOXabVW == yeDoTCCEbV){bTtuFuJAxI = true;}
      else if(yeDoTCCEbV == sfoUOXabVW){RVsEBZBDLc = true;}
      if(JRYMuxwlCy == lBRXqptnHC){WomubenmCS = true;}
      if(ypSwLcOjMZ == kqIYNfbTyD){iXHGlpHOJK = true;}
      if(dzqTUweOCg == WluQlOPGGl){AAFLEqAzMZ = true;}
      while(lBRXqptnHC == JRYMuxwlCy){RnoYUQVNqi = true;}
      while(kqIYNfbTyD == kqIYNfbTyD){BmNpGRzbpV = true;}
      while(WluQlOPGGl == WluQlOPGGl){wmuNSXcTbU = true;}
      if(mUHafhUgYf == true){mUHafhUgYf = false;}
      if(hqVMYHWean == true){hqVMYHWean = false;}
      if(aiFXyzGAlc == true){aiFXyzGAlc = false;}
      if(amhUOPjgrf == true){amhUOPjgrf = false;}
      if(LutRVePire == true){LutRVePire = false;}
      if(qjeSLEPibg == true){qjeSLEPibg = false;}
      if(bTtuFuJAxI == true){bTtuFuJAxI = false;}
      if(WomubenmCS == true){WomubenmCS = false;}
      if(iXHGlpHOJK == true){iXHGlpHOJK = false;}
      if(AAFLEqAzMZ == true){AAFLEqAzMZ = false;}
      if(VPkjHBxjpf == true){VPkjHBxjpf = false;}
      if(PbfIxDMnJO == true){PbfIxDMnJO = false;}
      if(ntqlHWjbpk == true){ntqlHWjbpk = false;}
      if(eoabxTlXyj == true){eoabxTlXyj = false;}
      if(sWYcuYUwNA == true){sWYcuYUwNA = false;}
      if(dMoylbXybk == true){dMoylbXybk = false;}
      if(RVsEBZBDLc == true){RVsEBZBDLc = false;}
      if(RnoYUQVNqi == true){RnoYUQVNqi = false;}
      if(BmNpGRzbpV == true){BmNpGRzbpV = false;}
      if(wmuNSXcTbU == true){wmuNSXcTbU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SJEGEPFOTB
{ 
  void XTeidjbCjr()
  { 
      bool HDENBFBmPh = false;
      bool izmkxFcKDH = false;
      bool WQUQtbxphZ = false;
      bool OhGjZIzGhf = false;
      bool YXMZeqVASM = false;
      bool CzLkYpimTY = false;
      bool IKFpTBrDLo = false;
      bool GVbWizEtlC = false;
      bool GxWUXOWVLi = false;
      bool YMmJXNRWGc = false;
      bool yRndGfWnBY = false;
      bool lnARRLnjRF = false;
      bool dWrcPtiSzV = false;
      bool ghnIDnIsNq = false;
      bool qiTlwkLVqM = false;
      bool ZhEAzbZLNM = false;
      bool xDofrEzrNc = false;
      bool CtVaNuDGfe = false;
      bool hNbmwzdmJb = false;
      bool OxfBtmsmtr = false;
      string gicYnLMGWl;
      string ButXIkIDiK;
      string XjoiXBuYwT;
      string GDddFkSLLO;
      string MzTkhxnsWT;
      string tKjMnwtsBm;
      string PmKCfxQPRX;
      string RxrUyXPDAa;
      string NCCcZwTRpJ;
      string qYJYzYoRFk;
      string fXazCxRPNP;
      string fprZZMkgcj;
      string czZIgrmTVY;
      string hyxPtobDZb;
      string dEDZcAfjyl;
      string mInVHfySRJ;
      string Jysoggscej;
      string khGAFYwzeg;
      string LDUikZKbIO;
      string pIkQSfKOru;
      if(gicYnLMGWl == fXazCxRPNP){HDENBFBmPh = true;}
      else if(fXazCxRPNP == gicYnLMGWl){yRndGfWnBY = true;}
      if(ButXIkIDiK == fprZZMkgcj){izmkxFcKDH = true;}
      else if(fprZZMkgcj == ButXIkIDiK){lnARRLnjRF = true;}
      if(XjoiXBuYwT == czZIgrmTVY){WQUQtbxphZ = true;}
      else if(czZIgrmTVY == XjoiXBuYwT){dWrcPtiSzV = true;}
      if(GDddFkSLLO == hyxPtobDZb){OhGjZIzGhf = true;}
      else if(hyxPtobDZb == GDddFkSLLO){ghnIDnIsNq = true;}
      if(MzTkhxnsWT == dEDZcAfjyl){YXMZeqVASM = true;}
      else if(dEDZcAfjyl == MzTkhxnsWT){qiTlwkLVqM = true;}
      if(tKjMnwtsBm == mInVHfySRJ){CzLkYpimTY = true;}
      else if(mInVHfySRJ == tKjMnwtsBm){ZhEAzbZLNM = true;}
      if(PmKCfxQPRX == Jysoggscej){IKFpTBrDLo = true;}
      else if(Jysoggscej == PmKCfxQPRX){xDofrEzrNc = true;}
      if(RxrUyXPDAa == khGAFYwzeg){GVbWizEtlC = true;}
      if(NCCcZwTRpJ == LDUikZKbIO){GxWUXOWVLi = true;}
      if(qYJYzYoRFk == pIkQSfKOru){YMmJXNRWGc = true;}
      while(khGAFYwzeg == RxrUyXPDAa){CtVaNuDGfe = true;}
      while(LDUikZKbIO == LDUikZKbIO){hNbmwzdmJb = true;}
      while(pIkQSfKOru == pIkQSfKOru){OxfBtmsmtr = true;}
      if(HDENBFBmPh == true){HDENBFBmPh = false;}
      if(izmkxFcKDH == true){izmkxFcKDH = false;}
      if(WQUQtbxphZ == true){WQUQtbxphZ = false;}
      if(OhGjZIzGhf == true){OhGjZIzGhf = false;}
      if(YXMZeqVASM == true){YXMZeqVASM = false;}
      if(CzLkYpimTY == true){CzLkYpimTY = false;}
      if(IKFpTBrDLo == true){IKFpTBrDLo = false;}
      if(GVbWizEtlC == true){GVbWizEtlC = false;}
      if(GxWUXOWVLi == true){GxWUXOWVLi = false;}
      if(YMmJXNRWGc == true){YMmJXNRWGc = false;}
      if(yRndGfWnBY == true){yRndGfWnBY = false;}
      if(lnARRLnjRF == true){lnARRLnjRF = false;}
      if(dWrcPtiSzV == true){dWrcPtiSzV = false;}
      if(ghnIDnIsNq == true){ghnIDnIsNq = false;}
      if(qiTlwkLVqM == true){qiTlwkLVqM = false;}
      if(ZhEAzbZLNM == true){ZhEAzbZLNM = false;}
      if(xDofrEzrNc == true){xDofrEzrNc = false;}
      if(CtVaNuDGfe == true){CtVaNuDGfe = false;}
      if(hNbmwzdmJb == true){hNbmwzdmJb = false;}
      if(OxfBtmsmtr == true){OxfBtmsmtr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKPGRIMHWN
{ 
  void dVBOIWxPdM()
  { 
      bool mjkkVPoKRW = false;
      bool tkaLdMtqdy = false;
      bool TTAWtHepMn = false;
      bool cHlVPEkqYP = false;
      bool pWAsHfyDFR = false;
      bool EebsfTiNpO = false;
      bool jzxdtlyFuZ = false;
      bool aDSOIwSHPO = false;
      bool Ibjuixfspu = false;
      bool UWBJeqZVzU = false;
      bool gsHfpBLMki = false;
      bool AbyaGIOCtw = false;
      bool GFOAEDCIjR = false;
      bool WxHtgOUDEh = false;
      bool lSHGtrYZDV = false;
      bool bWaDObdGam = false;
      bool zCcTMDUEtq = false;
      bool nLxMKmxIFM = false;
      bool ebFNozVEfF = false;
      bool jNbQiionsq = false;
      string zSHlGRMFuw;
      string eRHVqSksHo;
      string TaXpNOVWQO;
      string XfcJLeWOfD;
      string UfllaWPeDF;
      string lHnQMYuRXq;
      string upngYynyJM;
      string uWMETmnkOq;
      string yqTLcPqLwl;
      string iEpnHerFNc;
      string iRUqJPtixZ;
      string kJDgrEVbEI;
      string GbBXcpfXxn;
      string uiXlIgWcCM;
      string VIOWBZBJwD;
      string JPBFVGPxOS;
      string iWlIdBlQXL;
      string gsZqmyMeVC;
      string oWbtefhSPB;
      string QZOjdzVFrz;
      if(zSHlGRMFuw == iRUqJPtixZ){mjkkVPoKRW = true;}
      else if(iRUqJPtixZ == zSHlGRMFuw){gsHfpBLMki = true;}
      if(eRHVqSksHo == kJDgrEVbEI){tkaLdMtqdy = true;}
      else if(kJDgrEVbEI == eRHVqSksHo){AbyaGIOCtw = true;}
      if(TaXpNOVWQO == GbBXcpfXxn){TTAWtHepMn = true;}
      else if(GbBXcpfXxn == TaXpNOVWQO){GFOAEDCIjR = true;}
      if(XfcJLeWOfD == uiXlIgWcCM){cHlVPEkqYP = true;}
      else if(uiXlIgWcCM == XfcJLeWOfD){WxHtgOUDEh = true;}
      if(UfllaWPeDF == VIOWBZBJwD){pWAsHfyDFR = true;}
      else if(VIOWBZBJwD == UfllaWPeDF){lSHGtrYZDV = true;}
      if(lHnQMYuRXq == JPBFVGPxOS){EebsfTiNpO = true;}
      else if(JPBFVGPxOS == lHnQMYuRXq){bWaDObdGam = true;}
      if(upngYynyJM == iWlIdBlQXL){jzxdtlyFuZ = true;}
      else if(iWlIdBlQXL == upngYynyJM){zCcTMDUEtq = true;}
      if(uWMETmnkOq == gsZqmyMeVC){aDSOIwSHPO = true;}
      if(yqTLcPqLwl == oWbtefhSPB){Ibjuixfspu = true;}
      if(iEpnHerFNc == QZOjdzVFrz){UWBJeqZVzU = true;}
      while(gsZqmyMeVC == uWMETmnkOq){nLxMKmxIFM = true;}
      while(oWbtefhSPB == oWbtefhSPB){ebFNozVEfF = true;}
      while(QZOjdzVFrz == QZOjdzVFrz){jNbQiionsq = true;}
      if(mjkkVPoKRW == true){mjkkVPoKRW = false;}
      if(tkaLdMtqdy == true){tkaLdMtqdy = false;}
      if(TTAWtHepMn == true){TTAWtHepMn = false;}
      if(cHlVPEkqYP == true){cHlVPEkqYP = false;}
      if(pWAsHfyDFR == true){pWAsHfyDFR = false;}
      if(EebsfTiNpO == true){EebsfTiNpO = false;}
      if(jzxdtlyFuZ == true){jzxdtlyFuZ = false;}
      if(aDSOIwSHPO == true){aDSOIwSHPO = false;}
      if(Ibjuixfspu == true){Ibjuixfspu = false;}
      if(UWBJeqZVzU == true){UWBJeqZVzU = false;}
      if(gsHfpBLMki == true){gsHfpBLMki = false;}
      if(AbyaGIOCtw == true){AbyaGIOCtw = false;}
      if(GFOAEDCIjR == true){GFOAEDCIjR = false;}
      if(WxHtgOUDEh == true){WxHtgOUDEh = false;}
      if(lSHGtrYZDV == true){lSHGtrYZDV = false;}
      if(bWaDObdGam == true){bWaDObdGam = false;}
      if(zCcTMDUEtq == true){zCcTMDUEtq = false;}
      if(nLxMKmxIFM == true){nLxMKmxIFM = false;}
      if(ebFNozVEfF == true){ebFNozVEfF = false;}
      if(jNbQiionsq == true){jNbQiionsq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUKIWZNQFH
{ 
  void AfoPzgjCNs()
  { 
      bool bzaWGnJBLX = false;
      bool enAFUDEKXn = false;
      bool HIWtTWVIFe = false;
      bool ZkljQuRaeb = false;
      bool JKdqQoyIbA = false;
      bool SyRrfTbfCi = false;
      bool RAufytCPoY = false;
      bool kcfudxdfde = false;
      bool YNfFMbSsDw = false;
      bool TkYuJJPxsV = false;
      bool mhSDOoRWOi = false;
      bool owBXKEToTV = false;
      bool bILrFzEjlU = false;
      bool hglHqptcpW = false;
      bool JweUGWjAkE = false;
      bool oZcWteWayO = false;
      bool khjsBIJtfT = false;
      bool KqywMedqlh = false;
      bool PDygeHDPNM = false;
      bool TSealaLkTy = false;
      string xpwdQmVVkD;
      string JBUFHIawbN;
      string gTzRboOqpY;
      string hGrlaPbJcs;
      string COeIyRtkKd;
      string VnqmIdpdBa;
      string XeeLUCIidr;
      string fRThLRopTK;
      string tdfLDtOEdx;
      string YxIBUWiSnu;
      string JLGRyEUJbp;
      string ozKqgsyTIa;
      string nDFgShISMn;
      string iVCXBiXNNy;
      string YFcmHZmQUb;
      string YPKNHFFZzP;
      string uCwmHSxmpx;
      string VjFJBiaRYs;
      string urykPSLoPu;
      string cyOxDWIofn;
      if(xpwdQmVVkD == JLGRyEUJbp){bzaWGnJBLX = true;}
      else if(JLGRyEUJbp == xpwdQmVVkD){mhSDOoRWOi = true;}
      if(JBUFHIawbN == ozKqgsyTIa){enAFUDEKXn = true;}
      else if(ozKqgsyTIa == JBUFHIawbN){owBXKEToTV = true;}
      if(gTzRboOqpY == nDFgShISMn){HIWtTWVIFe = true;}
      else if(nDFgShISMn == gTzRboOqpY){bILrFzEjlU = true;}
      if(hGrlaPbJcs == iVCXBiXNNy){ZkljQuRaeb = true;}
      else if(iVCXBiXNNy == hGrlaPbJcs){hglHqptcpW = true;}
      if(COeIyRtkKd == YFcmHZmQUb){JKdqQoyIbA = true;}
      else if(YFcmHZmQUb == COeIyRtkKd){JweUGWjAkE = true;}
      if(VnqmIdpdBa == YPKNHFFZzP){SyRrfTbfCi = true;}
      else if(YPKNHFFZzP == VnqmIdpdBa){oZcWteWayO = true;}
      if(XeeLUCIidr == uCwmHSxmpx){RAufytCPoY = true;}
      else if(uCwmHSxmpx == XeeLUCIidr){khjsBIJtfT = true;}
      if(fRThLRopTK == VjFJBiaRYs){kcfudxdfde = true;}
      if(tdfLDtOEdx == urykPSLoPu){YNfFMbSsDw = true;}
      if(YxIBUWiSnu == cyOxDWIofn){TkYuJJPxsV = true;}
      while(VjFJBiaRYs == fRThLRopTK){KqywMedqlh = true;}
      while(urykPSLoPu == urykPSLoPu){PDygeHDPNM = true;}
      while(cyOxDWIofn == cyOxDWIofn){TSealaLkTy = true;}
      if(bzaWGnJBLX == true){bzaWGnJBLX = false;}
      if(enAFUDEKXn == true){enAFUDEKXn = false;}
      if(HIWtTWVIFe == true){HIWtTWVIFe = false;}
      if(ZkljQuRaeb == true){ZkljQuRaeb = false;}
      if(JKdqQoyIbA == true){JKdqQoyIbA = false;}
      if(SyRrfTbfCi == true){SyRrfTbfCi = false;}
      if(RAufytCPoY == true){RAufytCPoY = false;}
      if(kcfudxdfde == true){kcfudxdfde = false;}
      if(YNfFMbSsDw == true){YNfFMbSsDw = false;}
      if(TkYuJJPxsV == true){TkYuJJPxsV = false;}
      if(mhSDOoRWOi == true){mhSDOoRWOi = false;}
      if(owBXKEToTV == true){owBXKEToTV = false;}
      if(bILrFzEjlU == true){bILrFzEjlU = false;}
      if(hglHqptcpW == true){hglHqptcpW = false;}
      if(JweUGWjAkE == true){JweUGWjAkE = false;}
      if(oZcWteWayO == true){oZcWteWayO = false;}
      if(khjsBIJtfT == true){khjsBIJtfT = false;}
      if(KqywMedqlh == true){KqywMedqlh = false;}
      if(PDygeHDPNM == true){PDygeHDPNM = false;}
      if(TSealaLkTy == true){TSealaLkTy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EGQPALHMHM
{ 
  void uMRZtwHVOj()
  { 
      bool QKPqfSYhFK = false;
      bool CufKQXMIXu = false;
      bool QPKENwDefe = false;
      bool pODSuScGdz = false;
      bool wLjcueztgg = false;
      bool hBsDbAzKdj = false;
      bool OtCZTnrNOy = false;
      bool uGeXzFfhIh = false;
      bool xIxyxnVzpu = false;
      bool SRbsjBJJIH = false;
      bool lkfilaWUEV = false;
      bool URCumGwDce = false;
      bool RsWTeceknx = false;
      bool wVYAwLcOMV = false;
      bool RBuTZAOfGd = false;
      bool EFgcosOLDI = false;
      bool wlfGZyrBzb = false;
      bool chqHNQyCsd = false;
      bool NzdKrpowKC = false;
      bool wQLDZeUntb = false;
      string fkRbhFmsnf;
      string SzPhmnyMDj;
      string MSacrfdTyj;
      string DXappHukrg;
      string eReplrqAkZ;
      string mIImjMKoiB;
      string bStDctYYre;
      string sMTWEunjqA;
      string odhYwtPnFc;
      string xGBqFLWaNq;
      string SRHFgankho;
      string YaxiLxkUHh;
      string ekTPhlKcRr;
      string XNVzgXWbrV;
      string GdFQEVIReH;
      string aCTfLhyqWt;
      string QKSoRKFyCm;
      string aIckaBeCLM;
      string crxKRVsomy;
      string ZeFxFuKQzs;
      if(fkRbhFmsnf == SRHFgankho){QKPqfSYhFK = true;}
      else if(SRHFgankho == fkRbhFmsnf){lkfilaWUEV = true;}
      if(SzPhmnyMDj == YaxiLxkUHh){CufKQXMIXu = true;}
      else if(YaxiLxkUHh == SzPhmnyMDj){URCumGwDce = true;}
      if(MSacrfdTyj == ekTPhlKcRr){QPKENwDefe = true;}
      else if(ekTPhlKcRr == MSacrfdTyj){RsWTeceknx = true;}
      if(DXappHukrg == XNVzgXWbrV){pODSuScGdz = true;}
      else if(XNVzgXWbrV == DXappHukrg){wVYAwLcOMV = true;}
      if(eReplrqAkZ == GdFQEVIReH){wLjcueztgg = true;}
      else if(GdFQEVIReH == eReplrqAkZ){RBuTZAOfGd = true;}
      if(mIImjMKoiB == aCTfLhyqWt){hBsDbAzKdj = true;}
      else if(aCTfLhyqWt == mIImjMKoiB){EFgcosOLDI = true;}
      if(bStDctYYre == QKSoRKFyCm){OtCZTnrNOy = true;}
      else if(QKSoRKFyCm == bStDctYYre){wlfGZyrBzb = true;}
      if(sMTWEunjqA == aIckaBeCLM){uGeXzFfhIh = true;}
      if(odhYwtPnFc == crxKRVsomy){xIxyxnVzpu = true;}
      if(xGBqFLWaNq == ZeFxFuKQzs){SRbsjBJJIH = true;}
      while(aIckaBeCLM == sMTWEunjqA){chqHNQyCsd = true;}
      while(crxKRVsomy == crxKRVsomy){NzdKrpowKC = true;}
      while(ZeFxFuKQzs == ZeFxFuKQzs){wQLDZeUntb = true;}
      if(QKPqfSYhFK == true){QKPqfSYhFK = false;}
      if(CufKQXMIXu == true){CufKQXMIXu = false;}
      if(QPKENwDefe == true){QPKENwDefe = false;}
      if(pODSuScGdz == true){pODSuScGdz = false;}
      if(wLjcueztgg == true){wLjcueztgg = false;}
      if(hBsDbAzKdj == true){hBsDbAzKdj = false;}
      if(OtCZTnrNOy == true){OtCZTnrNOy = false;}
      if(uGeXzFfhIh == true){uGeXzFfhIh = false;}
      if(xIxyxnVzpu == true){xIxyxnVzpu = false;}
      if(SRbsjBJJIH == true){SRbsjBJJIH = false;}
      if(lkfilaWUEV == true){lkfilaWUEV = false;}
      if(URCumGwDce == true){URCumGwDce = false;}
      if(RsWTeceknx == true){RsWTeceknx = false;}
      if(wVYAwLcOMV == true){wVYAwLcOMV = false;}
      if(RBuTZAOfGd == true){RBuTZAOfGd = false;}
      if(EFgcosOLDI == true){EFgcosOLDI = false;}
      if(wlfGZyrBzb == true){wlfGZyrBzb = false;}
      if(chqHNQyCsd == true){chqHNQyCsd = false;}
      if(NzdKrpowKC == true){NzdKrpowKC = false;}
      if(wQLDZeUntb == true){wQLDZeUntb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTVQYBKNBU
{ 
  void WbxrZDEhei()
  { 
      bool syGQSFNcel = false;
      bool VxLKczaTxh = false;
      bool FUiUPIOcol = false;
      bool MMKMpKoNab = false;
      bool kGxYDZxDHM = false;
      bool PgYeoXOlAK = false;
      bool qjnsZJlzTR = false;
      bool JNrVwyWKRo = false;
      bool LKVbVfneXR = false;
      bool wDMQjAREzs = false;
      bool nyjpCCnCip = false;
      bool AETLygOLXs = false;
      bool UGbBUFAalu = false;
      bool gSKXBMZeZS = false;
      bool qkwgQriBRD = false;
      bool lGfFXgVhUw = false;
      bool BNQmJhswJk = false;
      bool GilECjKtjb = false;
      bool WyIhIZlEzT = false;
      bool qrJcQdUIXi = false;
      string EXtltEKzaz;
      string BIORlzqHcP;
      string qzQzrkWyEQ;
      string nQaupiuTrP;
      string fFxuMWGjWs;
      string PDIesEGttJ;
      string hMtJLjgTaC;
      string EWPNikCVmU;
      string dlbKAjIwBk;
      string bBZhgTKnib;
      string plJTormtuH;
      string CkHYeukiJa;
      string bjRpZDxhfP;
      string aNlLercHVH;
      string xOBtiqsADl;
      string iaeIzFUSsl;
      string uFNegnyutm;
      string ScNBcNiXGi;
      string JwdtgzicLY;
      string WJOjLqAVMt;
      if(EXtltEKzaz == plJTormtuH){syGQSFNcel = true;}
      else if(plJTormtuH == EXtltEKzaz){nyjpCCnCip = true;}
      if(BIORlzqHcP == CkHYeukiJa){VxLKczaTxh = true;}
      else if(CkHYeukiJa == BIORlzqHcP){AETLygOLXs = true;}
      if(qzQzrkWyEQ == bjRpZDxhfP){FUiUPIOcol = true;}
      else if(bjRpZDxhfP == qzQzrkWyEQ){UGbBUFAalu = true;}
      if(nQaupiuTrP == aNlLercHVH){MMKMpKoNab = true;}
      else if(aNlLercHVH == nQaupiuTrP){gSKXBMZeZS = true;}
      if(fFxuMWGjWs == xOBtiqsADl){kGxYDZxDHM = true;}
      else if(xOBtiqsADl == fFxuMWGjWs){qkwgQriBRD = true;}
      if(PDIesEGttJ == iaeIzFUSsl){PgYeoXOlAK = true;}
      else if(iaeIzFUSsl == PDIesEGttJ){lGfFXgVhUw = true;}
      if(hMtJLjgTaC == uFNegnyutm){qjnsZJlzTR = true;}
      else if(uFNegnyutm == hMtJLjgTaC){BNQmJhswJk = true;}
      if(EWPNikCVmU == ScNBcNiXGi){JNrVwyWKRo = true;}
      if(dlbKAjIwBk == JwdtgzicLY){LKVbVfneXR = true;}
      if(bBZhgTKnib == WJOjLqAVMt){wDMQjAREzs = true;}
      while(ScNBcNiXGi == EWPNikCVmU){GilECjKtjb = true;}
      while(JwdtgzicLY == JwdtgzicLY){WyIhIZlEzT = true;}
      while(WJOjLqAVMt == WJOjLqAVMt){qrJcQdUIXi = true;}
      if(syGQSFNcel == true){syGQSFNcel = false;}
      if(VxLKczaTxh == true){VxLKczaTxh = false;}
      if(FUiUPIOcol == true){FUiUPIOcol = false;}
      if(MMKMpKoNab == true){MMKMpKoNab = false;}
      if(kGxYDZxDHM == true){kGxYDZxDHM = false;}
      if(PgYeoXOlAK == true){PgYeoXOlAK = false;}
      if(qjnsZJlzTR == true){qjnsZJlzTR = false;}
      if(JNrVwyWKRo == true){JNrVwyWKRo = false;}
      if(LKVbVfneXR == true){LKVbVfneXR = false;}
      if(wDMQjAREzs == true){wDMQjAREzs = false;}
      if(nyjpCCnCip == true){nyjpCCnCip = false;}
      if(AETLygOLXs == true){AETLygOLXs = false;}
      if(UGbBUFAalu == true){UGbBUFAalu = false;}
      if(gSKXBMZeZS == true){gSKXBMZeZS = false;}
      if(qkwgQriBRD == true){qkwgQriBRD = false;}
      if(lGfFXgVhUw == true){lGfFXgVhUw = false;}
      if(BNQmJhswJk == true){BNQmJhswJk = false;}
      if(GilECjKtjb == true){GilECjKtjb = false;}
      if(WyIhIZlEzT == true){WyIhIZlEzT = false;}
      if(qrJcQdUIXi == true){qrJcQdUIXi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DPSNUVOKIW
{ 
  void oXjmkykVPO()
  { 
      bool WixnspjLcO = false;
      bool YUqNMMTatn = false;
      bool wtiEINoXat = false;
      bool tkwBhGcWfP = false;
      bool aknrEkKesd = false;
      bool YyIshczsff = false;
      bool BMjiUmXoeF = false;
      bool ixtdMLFpzX = false;
      bool CJexUubCSF = false;
      bool GjpAOOAFXR = false;
      bool MUAmtbDefW = false;
      bool WIsIcqgmNY = false;
      bool KVVZyzGtPy = false;
      bool KAShKhJqCr = false;
      bool rxVwixphWW = false;
      bool gMqyGpyant = false;
      bool VIOhMWpLxu = false;
      bool hpjVgNAZpA = false;
      bool JXXrRxITaU = false;
      bool iiCIViiniM = false;
      string OyHyNWsfHG;
      string kfTIggpcXY;
      string nwBFajdhRj;
      string idHDKVJcwp;
      string cNwukdXaQp;
      string JVRZySwBWc;
      string rKNWWHYPxL;
      string XNfgwZzFUx;
      string LDQaaMLgFr;
      string YHGTyRAYYd;
      string FIcFSupjdY;
      string TqgZRotlwJ;
      string uqKFlPHMid;
      string YZfpqDZLIe;
      string WaDgYhZfBI;
      string XOcPiNyXSC;
      string ndBzzsKqhN;
      string PhdRmTndgE;
      string paKZFKwQHd;
      string FBsFprZDge;
      if(OyHyNWsfHG == FIcFSupjdY){WixnspjLcO = true;}
      else if(FIcFSupjdY == OyHyNWsfHG){MUAmtbDefW = true;}
      if(kfTIggpcXY == TqgZRotlwJ){YUqNMMTatn = true;}
      else if(TqgZRotlwJ == kfTIggpcXY){WIsIcqgmNY = true;}
      if(nwBFajdhRj == uqKFlPHMid){wtiEINoXat = true;}
      else if(uqKFlPHMid == nwBFajdhRj){KVVZyzGtPy = true;}
      if(idHDKVJcwp == YZfpqDZLIe){tkwBhGcWfP = true;}
      else if(YZfpqDZLIe == idHDKVJcwp){KAShKhJqCr = true;}
      if(cNwukdXaQp == WaDgYhZfBI){aknrEkKesd = true;}
      else if(WaDgYhZfBI == cNwukdXaQp){rxVwixphWW = true;}
      if(JVRZySwBWc == XOcPiNyXSC){YyIshczsff = true;}
      else if(XOcPiNyXSC == JVRZySwBWc){gMqyGpyant = true;}
      if(rKNWWHYPxL == ndBzzsKqhN){BMjiUmXoeF = true;}
      else if(ndBzzsKqhN == rKNWWHYPxL){VIOhMWpLxu = true;}
      if(XNfgwZzFUx == PhdRmTndgE){ixtdMLFpzX = true;}
      if(LDQaaMLgFr == paKZFKwQHd){CJexUubCSF = true;}
      if(YHGTyRAYYd == FBsFprZDge){GjpAOOAFXR = true;}
      while(PhdRmTndgE == XNfgwZzFUx){hpjVgNAZpA = true;}
      while(paKZFKwQHd == paKZFKwQHd){JXXrRxITaU = true;}
      while(FBsFprZDge == FBsFprZDge){iiCIViiniM = true;}
      if(WixnspjLcO == true){WixnspjLcO = false;}
      if(YUqNMMTatn == true){YUqNMMTatn = false;}
      if(wtiEINoXat == true){wtiEINoXat = false;}
      if(tkwBhGcWfP == true){tkwBhGcWfP = false;}
      if(aknrEkKesd == true){aknrEkKesd = false;}
      if(YyIshczsff == true){YyIshczsff = false;}
      if(BMjiUmXoeF == true){BMjiUmXoeF = false;}
      if(ixtdMLFpzX == true){ixtdMLFpzX = false;}
      if(CJexUubCSF == true){CJexUubCSF = false;}
      if(GjpAOOAFXR == true){GjpAOOAFXR = false;}
      if(MUAmtbDefW == true){MUAmtbDefW = false;}
      if(WIsIcqgmNY == true){WIsIcqgmNY = false;}
      if(KVVZyzGtPy == true){KVVZyzGtPy = false;}
      if(KAShKhJqCr == true){KAShKhJqCr = false;}
      if(rxVwixphWW == true){rxVwixphWW = false;}
      if(gMqyGpyant == true){gMqyGpyant = false;}
      if(VIOhMWpLxu == true){VIOhMWpLxu = false;}
      if(hpjVgNAZpA == true){hpjVgNAZpA = false;}
      if(JXXrRxITaU == true){JXXrRxITaU = false;}
      if(iiCIViiniM == true){iiCIViiniM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KLMGYZGAIL
{ 
  void UjWEILyMUG()
  { 
      bool JYMBEyNpNn = false;
      bool qbLQeOmops = false;
      bool CobWFHaYsy = false;
      bool WhZxUgIbJZ = false;
      bool QPprKVJiFz = false;
      bool MFglQUwpux = false;
      bool WnxPQIBNwy = false;
      bool FLeQblzjLj = false;
      bool xqTskQBmgz = false;
      bool jSfLCcSZaB = false;
      bool TwmHsBaQKd = false;
      bool VMdKAfUDdA = false;
      bool HNgwNmeTNy = false;
      bool TYIKPBEMAj = false;
      bool pkcCcXoULW = false;
      bool HOuatGOptG = false;
      bool VGCLKxDSuz = false;
      bool aHCtKWkeSo = false;
      bool xJIpqEchQJ = false;
      bool lOStNihQqf = false;
      string SqpkGPyNgJ;
      string PFsmEugRKu;
      string hAroYAUymo;
      string hCLHGKeTuE;
      string ydtBhjcBXq;
      string CUFKdSyBMG;
      string uzarbMslgs;
      string QMWFxEFpGo;
      string WTaumNxAcn;
      string LcHoJyCCZU;
      string pqUdZoxzNZ;
      string MItWjbXeEN;
      string PrJrhnFhwy;
      string BDPlzfywVx;
      string PxlDbChjFh;
      string ZWxLFxhbwk;
      string jPDOXIrIXD;
      string cbJGyRFFQe;
      string GUcNYeGDfB;
      string xVAjNztXeS;
      if(SqpkGPyNgJ == pqUdZoxzNZ){JYMBEyNpNn = true;}
      else if(pqUdZoxzNZ == SqpkGPyNgJ){TwmHsBaQKd = true;}
      if(PFsmEugRKu == MItWjbXeEN){qbLQeOmops = true;}
      else if(MItWjbXeEN == PFsmEugRKu){VMdKAfUDdA = true;}
      if(hAroYAUymo == PrJrhnFhwy){CobWFHaYsy = true;}
      else if(PrJrhnFhwy == hAroYAUymo){HNgwNmeTNy = true;}
      if(hCLHGKeTuE == BDPlzfywVx){WhZxUgIbJZ = true;}
      else if(BDPlzfywVx == hCLHGKeTuE){TYIKPBEMAj = true;}
      if(ydtBhjcBXq == PxlDbChjFh){QPprKVJiFz = true;}
      else if(PxlDbChjFh == ydtBhjcBXq){pkcCcXoULW = true;}
      if(CUFKdSyBMG == ZWxLFxhbwk){MFglQUwpux = true;}
      else if(ZWxLFxhbwk == CUFKdSyBMG){HOuatGOptG = true;}
      if(uzarbMslgs == jPDOXIrIXD){WnxPQIBNwy = true;}
      else if(jPDOXIrIXD == uzarbMslgs){VGCLKxDSuz = true;}
      if(QMWFxEFpGo == cbJGyRFFQe){FLeQblzjLj = true;}
      if(WTaumNxAcn == GUcNYeGDfB){xqTskQBmgz = true;}
      if(LcHoJyCCZU == xVAjNztXeS){jSfLCcSZaB = true;}
      while(cbJGyRFFQe == QMWFxEFpGo){aHCtKWkeSo = true;}
      while(GUcNYeGDfB == GUcNYeGDfB){xJIpqEchQJ = true;}
      while(xVAjNztXeS == xVAjNztXeS){lOStNihQqf = true;}
      if(JYMBEyNpNn == true){JYMBEyNpNn = false;}
      if(qbLQeOmops == true){qbLQeOmops = false;}
      if(CobWFHaYsy == true){CobWFHaYsy = false;}
      if(WhZxUgIbJZ == true){WhZxUgIbJZ = false;}
      if(QPprKVJiFz == true){QPprKVJiFz = false;}
      if(MFglQUwpux == true){MFglQUwpux = false;}
      if(WnxPQIBNwy == true){WnxPQIBNwy = false;}
      if(FLeQblzjLj == true){FLeQblzjLj = false;}
      if(xqTskQBmgz == true){xqTskQBmgz = false;}
      if(jSfLCcSZaB == true){jSfLCcSZaB = false;}
      if(TwmHsBaQKd == true){TwmHsBaQKd = false;}
      if(VMdKAfUDdA == true){VMdKAfUDdA = false;}
      if(HNgwNmeTNy == true){HNgwNmeTNy = false;}
      if(TYIKPBEMAj == true){TYIKPBEMAj = false;}
      if(pkcCcXoULW == true){pkcCcXoULW = false;}
      if(HOuatGOptG == true){HOuatGOptG = false;}
      if(VGCLKxDSuz == true){VGCLKxDSuz = false;}
      if(aHCtKWkeSo == true){aHCtKWkeSo = false;}
      if(xJIpqEchQJ == true){xJIpqEchQJ = false;}
      if(lOStNihQqf == true){lOStNihQqf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CAKWIWHDSY
{ 
  void tfJCHIyjaD()
  { 
      bool dhcHPJZuLM = false;
      bool EjXmsFCran = false;
      bool TCSaiBcGgE = false;
      bool hjeNWaMafh = false;
      bool uFIPmKPFiW = false;
      bool fNVVbbPCXN = false;
      bool gSOGdTFKQS = false;
      bool sbMssOsDmX = false;
      bool kXXJYTOJkt = false;
      bool LKCRBbqBkT = false;
      bool FFoQdEAbbM = false;
      bool hLOzbIuEhJ = false;
      bool EwYVGiYurQ = false;
      bool XrRTSfiGfU = false;
      bool TmgYMzuCor = false;
      bool glTaOJfSJu = false;
      bool eFjLoptugw = false;
      bool ZnYNpROAJH = false;
      bool mVGzjkYpEI = false;
      bool zPxkoOCVjV = false;
      string wcETzxohJQ;
      string NTPiCalscX;
      string MYMSHyGLyT;
      string ksLzPHmGmI;
      string OIdlErwblc;
      string NLJCrWPlLB;
      string pdjofTHPTt;
      string nfGTJDuZNO;
      string BeYUGYjJHs;
      string qBtlRkYnGk;
      string jgIqohForn;
      string bpXxzLEOiG;
      string iyHaCllUBY;
      string eGTcdUVheY;
      string TtQSQBcwlF;
      string fJFzBlYhoC;
      string uknTJUWtSe;
      string pVjKmognJB;
      string JohurUATbr;
      string unscchGxJw;
      if(wcETzxohJQ == jgIqohForn){dhcHPJZuLM = true;}
      else if(jgIqohForn == wcETzxohJQ){FFoQdEAbbM = true;}
      if(NTPiCalscX == bpXxzLEOiG){EjXmsFCran = true;}
      else if(bpXxzLEOiG == NTPiCalscX){hLOzbIuEhJ = true;}
      if(MYMSHyGLyT == iyHaCllUBY){TCSaiBcGgE = true;}
      else if(iyHaCllUBY == MYMSHyGLyT){EwYVGiYurQ = true;}
      if(ksLzPHmGmI == eGTcdUVheY){hjeNWaMafh = true;}
      else if(eGTcdUVheY == ksLzPHmGmI){XrRTSfiGfU = true;}
      if(OIdlErwblc == TtQSQBcwlF){uFIPmKPFiW = true;}
      else if(TtQSQBcwlF == OIdlErwblc){TmgYMzuCor = true;}
      if(NLJCrWPlLB == fJFzBlYhoC){fNVVbbPCXN = true;}
      else if(fJFzBlYhoC == NLJCrWPlLB){glTaOJfSJu = true;}
      if(pdjofTHPTt == uknTJUWtSe){gSOGdTFKQS = true;}
      else if(uknTJUWtSe == pdjofTHPTt){eFjLoptugw = true;}
      if(nfGTJDuZNO == pVjKmognJB){sbMssOsDmX = true;}
      if(BeYUGYjJHs == JohurUATbr){kXXJYTOJkt = true;}
      if(qBtlRkYnGk == unscchGxJw){LKCRBbqBkT = true;}
      while(pVjKmognJB == nfGTJDuZNO){ZnYNpROAJH = true;}
      while(JohurUATbr == JohurUATbr){mVGzjkYpEI = true;}
      while(unscchGxJw == unscchGxJw){zPxkoOCVjV = true;}
      if(dhcHPJZuLM == true){dhcHPJZuLM = false;}
      if(EjXmsFCran == true){EjXmsFCran = false;}
      if(TCSaiBcGgE == true){TCSaiBcGgE = false;}
      if(hjeNWaMafh == true){hjeNWaMafh = false;}
      if(uFIPmKPFiW == true){uFIPmKPFiW = false;}
      if(fNVVbbPCXN == true){fNVVbbPCXN = false;}
      if(gSOGdTFKQS == true){gSOGdTFKQS = false;}
      if(sbMssOsDmX == true){sbMssOsDmX = false;}
      if(kXXJYTOJkt == true){kXXJYTOJkt = false;}
      if(LKCRBbqBkT == true){LKCRBbqBkT = false;}
      if(FFoQdEAbbM == true){FFoQdEAbbM = false;}
      if(hLOzbIuEhJ == true){hLOzbIuEhJ = false;}
      if(EwYVGiYurQ == true){EwYVGiYurQ = false;}
      if(XrRTSfiGfU == true){XrRTSfiGfU = false;}
      if(TmgYMzuCor == true){TmgYMzuCor = false;}
      if(glTaOJfSJu == true){glTaOJfSJu = false;}
      if(eFjLoptugw == true){eFjLoptugw = false;}
      if(ZnYNpROAJH == true){ZnYNpROAJH = false;}
      if(mVGzjkYpEI == true){mVGzjkYpEI = false;}
      if(zPxkoOCVjV == true){zPxkoOCVjV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JWXIMMMTXX
{ 
  void rikSyVgoqX()
  { 
      bool OcnrGgSBEN = false;
      bool RKDhJVssZu = false;
      bool CqsUPcVdlA = false;
      bool jGOneoPGVh = false;
      bool SiJGJeRKJh = false;
      bool lnxFfWjSbc = false;
      bool LnPEcLuPCU = false;
      bool FlWqcShlKj = false;
      bool KKUDNwIJIH = false;
      bool FwdrWeTEdy = false;
      bool jCHobzQGbM = false;
      bool oxHqRASLpg = false;
      bool ClHtOJIeTy = false;
      bool ycIMAICfaN = false;
      bool eCguSHnlZW = false;
      bool LIOwuxuNZS = false;
      bool qlldNLnuqJ = false;
      bool ymjbBAELbG = false;
      bool UVExlpOLRD = false;
      bool NoFIWsPDhH = false;
      string YlonlWpGPs;
      string RJWbCfmBtU;
      string wPuaFaMrfD;
      string ZqEIwOSphL;
      string dkYHarkyey;
      string LKkqsIpNiL;
      string JxaMTZENfm;
      string NwTiqLpmAM;
      string oONgrOFNPm;
      string XEHVBfJMnA;
      string nXRqkOpCAh;
      string RDNVWujsTE;
      string UqxrOIoyhK;
      string BdyAYQwVud;
      string XCMhVUpkyF;
      string uPrjfwaZcb;
      string ZrUognFNxG;
      string zOxpfRdPVt;
      string SDzbPkkNUb;
      string pVsTEfgXBh;
      if(YlonlWpGPs == nXRqkOpCAh){OcnrGgSBEN = true;}
      else if(nXRqkOpCAh == YlonlWpGPs){jCHobzQGbM = true;}
      if(RJWbCfmBtU == RDNVWujsTE){RKDhJVssZu = true;}
      else if(RDNVWujsTE == RJWbCfmBtU){oxHqRASLpg = true;}
      if(wPuaFaMrfD == UqxrOIoyhK){CqsUPcVdlA = true;}
      else if(UqxrOIoyhK == wPuaFaMrfD){ClHtOJIeTy = true;}
      if(ZqEIwOSphL == BdyAYQwVud){jGOneoPGVh = true;}
      else if(BdyAYQwVud == ZqEIwOSphL){ycIMAICfaN = true;}
      if(dkYHarkyey == XCMhVUpkyF){SiJGJeRKJh = true;}
      else if(XCMhVUpkyF == dkYHarkyey){eCguSHnlZW = true;}
      if(LKkqsIpNiL == uPrjfwaZcb){lnxFfWjSbc = true;}
      else if(uPrjfwaZcb == LKkqsIpNiL){LIOwuxuNZS = true;}
      if(JxaMTZENfm == ZrUognFNxG){LnPEcLuPCU = true;}
      else if(ZrUognFNxG == JxaMTZENfm){qlldNLnuqJ = true;}
      if(NwTiqLpmAM == zOxpfRdPVt){FlWqcShlKj = true;}
      if(oONgrOFNPm == SDzbPkkNUb){KKUDNwIJIH = true;}
      if(XEHVBfJMnA == pVsTEfgXBh){FwdrWeTEdy = true;}
      while(zOxpfRdPVt == NwTiqLpmAM){ymjbBAELbG = true;}
      while(SDzbPkkNUb == SDzbPkkNUb){UVExlpOLRD = true;}
      while(pVsTEfgXBh == pVsTEfgXBh){NoFIWsPDhH = true;}
      if(OcnrGgSBEN == true){OcnrGgSBEN = false;}
      if(RKDhJVssZu == true){RKDhJVssZu = false;}
      if(CqsUPcVdlA == true){CqsUPcVdlA = false;}
      if(jGOneoPGVh == true){jGOneoPGVh = false;}
      if(SiJGJeRKJh == true){SiJGJeRKJh = false;}
      if(lnxFfWjSbc == true){lnxFfWjSbc = false;}
      if(LnPEcLuPCU == true){LnPEcLuPCU = false;}
      if(FlWqcShlKj == true){FlWqcShlKj = false;}
      if(KKUDNwIJIH == true){KKUDNwIJIH = false;}
      if(FwdrWeTEdy == true){FwdrWeTEdy = false;}
      if(jCHobzQGbM == true){jCHobzQGbM = false;}
      if(oxHqRASLpg == true){oxHqRASLpg = false;}
      if(ClHtOJIeTy == true){ClHtOJIeTy = false;}
      if(ycIMAICfaN == true){ycIMAICfaN = false;}
      if(eCguSHnlZW == true){eCguSHnlZW = false;}
      if(LIOwuxuNZS == true){LIOwuxuNZS = false;}
      if(qlldNLnuqJ == true){qlldNLnuqJ = false;}
      if(ymjbBAELbG == true){ymjbBAELbG = false;}
      if(UVExlpOLRD == true){UVExlpOLRD = false;}
      if(NoFIWsPDhH == true){NoFIWsPDhH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VQTLYEWTBJ
{ 
  void mtIHNVTHbM()
  { 
      bool IirPqRMzhW = false;
      bool hrMSqAtcew = false;
      bool DhdkbPGfsT = false;
      bool mxwszsqeBZ = false;
      bool SiUPHaDHbQ = false;
      bool dmueNaEHmb = false;
      bool LfGOijuTSy = false;
      bool IPaFdTMOcB = false;
      bool MyEcpACQfX = false;
      bool njqZNlcGfW = false;
      bool ejndHOLpAs = false;
      bool OpdlPMbcXi = false;
      bool hentJYYBqq = false;
      bool pFhFVcJaVa = false;
      bool oMQlJyFEKA = false;
      bool KAixoAusTh = false;
      bool pKyICJHXQl = false;
      bool DBGwtUNBkL = false;
      bool TTpqgpWkQU = false;
      bool gPGnkdOHiA = false;
      string glJjVwhqSU;
      string ihYdzhfwnU;
      string zkJFlPFUaS;
      string ETzafmemxg;
      string uMVxdMohpw;
      string ettmFwcDxG;
      string pNPzPOixyM;
      string CryHYmPLaZ;
      string aWeenJZLVj;
      string KbpqphwVgO;
      string dqjcsmwmNS;
      string fQbWeSikLG;
      string oWbNCaCGQq;
      string pseLwimBlB;
      string NlxDDtzSLX;
      string zLKaZGPWaS;
      string joVWbmkQZw;
      string fgzKrDYXJH;
      string bjtsqeiDlo;
      string TPaSQYPabQ;
      if(glJjVwhqSU == dqjcsmwmNS){IirPqRMzhW = true;}
      else if(dqjcsmwmNS == glJjVwhqSU){ejndHOLpAs = true;}
      if(ihYdzhfwnU == fQbWeSikLG){hrMSqAtcew = true;}
      else if(fQbWeSikLG == ihYdzhfwnU){OpdlPMbcXi = true;}
      if(zkJFlPFUaS == oWbNCaCGQq){DhdkbPGfsT = true;}
      else if(oWbNCaCGQq == zkJFlPFUaS){hentJYYBqq = true;}
      if(ETzafmemxg == pseLwimBlB){mxwszsqeBZ = true;}
      else if(pseLwimBlB == ETzafmemxg){pFhFVcJaVa = true;}
      if(uMVxdMohpw == NlxDDtzSLX){SiUPHaDHbQ = true;}
      else if(NlxDDtzSLX == uMVxdMohpw){oMQlJyFEKA = true;}
      if(ettmFwcDxG == zLKaZGPWaS){dmueNaEHmb = true;}
      else if(zLKaZGPWaS == ettmFwcDxG){KAixoAusTh = true;}
      if(pNPzPOixyM == joVWbmkQZw){LfGOijuTSy = true;}
      else if(joVWbmkQZw == pNPzPOixyM){pKyICJHXQl = true;}
      if(CryHYmPLaZ == fgzKrDYXJH){IPaFdTMOcB = true;}
      if(aWeenJZLVj == bjtsqeiDlo){MyEcpACQfX = true;}
      if(KbpqphwVgO == TPaSQYPabQ){njqZNlcGfW = true;}
      while(fgzKrDYXJH == CryHYmPLaZ){DBGwtUNBkL = true;}
      while(bjtsqeiDlo == bjtsqeiDlo){TTpqgpWkQU = true;}
      while(TPaSQYPabQ == TPaSQYPabQ){gPGnkdOHiA = true;}
      if(IirPqRMzhW == true){IirPqRMzhW = false;}
      if(hrMSqAtcew == true){hrMSqAtcew = false;}
      if(DhdkbPGfsT == true){DhdkbPGfsT = false;}
      if(mxwszsqeBZ == true){mxwszsqeBZ = false;}
      if(SiUPHaDHbQ == true){SiUPHaDHbQ = false;}
      if(dmueNaEHmb == true){dmueNaEHmb = false;}
      if(LfGOijuTSy == true){LfGOijuTSy = false;}
      if(IPaFdTMOcB == true){IPaFdTMOcB = false;}
      if(MyEcpACQfX == true){MyEcpACQfX = false;}
      if(njqZNlcGfW == true){njqZNlcGfW = false;}
      if(ejndHOLpAs == true){ejndHOLpAs = false;}
      if(OpdlPMbcXi == true){OpdlPMbcXi = false;}
      if(hentJYYBqq == true){hentJYYBqq = false;}
      if(pFhFVcJaVa == true){pFhFVcJaVa = false;}
      if(oMQlJyFEKA == true){oMQlJyFEKA = false;}
      if(KAixoAusTh == true){KAixoAusTh = false;}
      if(pKyICJHXQl == true){pKyICJHXQl = false;}
      if(DBGwtUNBkL == true){DBGwtUNBkL = false;}
      if(TTpqgpWkQU == true){TTpqgpWkQU = false;}
      if(gPGnkdOHiA == true){gPGnkdOHiA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FNECDHHGXF
{ 
  void kRLGNEqEIL()
  { 
      bool aWlYpOmVpU = false;
      bool cYjdTUkOXT = false;
      bool aRjNsVBhiX = false;
      bool PAOmDFzPgf = false;
      bool jqlKSaUdEW = false;
      bool bTRxbImXfU = false;
      bool MFmSFbJxZN = false;
      bool UVgriieYuR = false;
      bool BWdMuuhRLu = false;
      bool SbjMSeETFp = false;
      bool RWEqBGlZNr = false;
      bool cNbNSobZWJ = false;
      bool trletslUYE = false;
      bool eLTFAdSmKn = false;
      bool IIDSREzVsd = false;
      bool DdwwwYkYwI = false;
      bool URAJMRtWNo = false;
      bool VnPhAknSMp = false;
      bool tPauABOXIa = false;
      bool stpCTpHsFA = false;
      string BHwuHGGNoO;
      string ClXtzSbnbU;
      string KTAtoHOFHc;
      string WkuNXcCZQP;
      string BZjtGIFceb;
      string pCmDthGCFA;
      string rBGMrRpJVV;
      string PBWLSkiGmg;
      string BlZflTxrTp;
      string VAUQWATXBn;
      string RwGILnfajJ;
      string zAOYyGaZZY;
      string UypfAPgGoS;
      string RKFzOFeQTy;
      string mVHJpVluRQ;
      string YsxbTTFZIw;
      string GZlRrnuPJs;
      string aKFakypgod;
      string cknXtXNceu;
      string AFIXrNipRC;
      if(BHwuHGGNoO == RwGILnfajJ){aWlYpOmVpU = true;}
      else if(RwGILnfajJ == BHwuHGGNoO){RWEqBGlZNr = true;}
      if(ClXtzSbnbU == zAOYyGaZZY){cYjdTUkOXT = true;}
      else if(zAOYyGaZZY == ClXtzSbnbU){cNbNSobZWJ = true;}
      if(KTAtoHOFHc == UypfAPgGoS){aRjNsVBhiX = true;}
      else if(UypfAPgGoS == KTAtoHOFHc){trletslUYE = true;}
      if(WkuNXcCZQP == RKFzOFeQTy){PAOmDFzPgf = true;}
      else if(RKFzOFeQTy == WkuNXcCZQP){eLTFAdSmKn = true;}
      if(BZjtGIFceb == mVHJpVluRQ){jqlKSaUdEW = true;}
      else if(mVHJpVluRQ == BZjtGIFceb){IIDSREzVsd = true;}
      if(pCmDthGCFA == YsxbTTFZIw){bTRxbImXfU = true;}
      else if(YsxbTTFZIw == pCmDthGCFA){DdwwwYkYwI = true;}
      if(rBGMrRpJVV == GZlRrnuPJs){MFmSFbJxZN = true;}
      else if(GZlRrnuPJs == rBGMrRpJVV){URAJMRtWNo = true;}
      if(PBWLSkiGmg == aKFakypgod){UVgriieYuR = true;}
      if(BlZflTxrTp == cknXtXNceu){BWdMuuhRLu = true;}
      if(VAUQWATXBn == AFIXrNipRC){SbjMSeETFp = true;}
      while(aKFakypgod == PBWLSkiGmg){VnPhAknSMp = true;}
      while(cknXtXNceu == cknXtXNceu){tPauABOXIa = true;}
      while(AFIXrNipRC == AFIXrNipRC){stpCTpHsFA = true;}
      if(aWlYpOmVpU == true){aWlYpOmVpU = false;}
      if(cYjdTUkOXT == true){cYjdTUkOXT = false;}
      if(aRjNsVBhiX == true){aRjNsVBhiX = false;}
      if(PAOmDFzPgf == true){PAOmDFzPgf = false;}
      if(jqlKSaUdEW == true){jqlKSaUdEW = false;}
      if(bTRxbImXfU == true){bTRxbImXfU = false;}
      if(MFmSFbJxZN == true){MFmSFbJxZN = false;}
      if(UVgriieYuR == true){UVgriieYuR = false;}
      if(BWdMuuhRLu == true){BWdMuuhRLu = false;}
      if(SbjMSeETFp == true){SbjMSeETFp = false;}
      if(RWEqBGlZNr == true){RWEqBGlZNr = false;}
      if(cNbNSobZWJ == true){cNbNSobZWJ = false;}
      if(trletslUYE == true){trletslUYE = false;}
      if(eLTFAdSmKn == true){eLTFAdSmKn = false;}
      if(IIDSREzVsd == true){IIDSREzVsd = false;}
      if(DdwwwYkYwI == true){DdwwwYkYwI = false;}
      if(URAJMRtWNo == true){URAJMRtWNo = false;}
      if(VnPhAknSMp == true){VnPhAknSMp = false;}
      if(tPauABOXIa == true){tPauABOXIa = false;}
      if(stpCTpHsFA == true){stpCTpHsFA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZYZUZFWYOR
{ 
  void UnTpHxdpkV()
  { 
      bool ytloggaSuu = false;
      bool KYTKhLshED = false;
      bool RIcjAZVSJi = false;
      bool XSRYsDabxA = false;
      bool kGKbEFoyiM = false;
      bool YiaiZoRCnG = false;
      bool LIJMXqGtRd = false;
      bool jQkESLxAeu = false;
      bool kWjxKnqhzE = false;
      bool lYnpnbxyEN = false;
      bool ytgEbIyWPN = false;
      bool qQWsVoYMBi = false;
      bool zXuMqKctPq = false;
      bool OzuRwpoeUB = false;
      bool pUSkMUCuUz = false;
      bool DjwVNazTMQ = false;
      bool eDGYzrVEwe = false;
      bool zsqzreFKAV = false;
      bool IgYQndCZEV = false;
      bool qUSEWmNtkT = false;
      string QKABKemzJP;
      string tkrdWamfsU;
      string JqKbgdUVuG;
      string MlZsahcdmE;
      string VujeNjkoyX;
      string inydCYAXUf;
      string JQDDCILzCo;
      string yJroyOGfOw;
      string sfXWXXmwpB;
      string hEJGtFqgbF;
      string XllJZYuIem;
      string RTJXmdsgfd;
      string UPIAGszkus;
      string WZEIXHtNxy;
      string ceQDjOulTQ;
      string MKAxkIckDf;
      string ZKNkPqPAze;
      string ieihBoyEQr;
      string yNQegLZGXP;
      string dIJQXRRfmr;
      if(QKABKemzJP == XllJZYuIem){ytloggaSuu = true;}
      else if(XllJZYuIem == QKABKemzJP){ytgEbIyWPN = true;}
      if(tkrdWamfsU == RTJXmdsgfd){KYTKhLshED = true;}
      else if(RTJXmdsgfd == tkrdWamfsU){qQWsVoYMBi = true;}
      if(JqKbgdUVuG == UPIAGszkus){RIcjAZVSJi = true;}
      else if(UPIAGszkus == JqKbgdUVuG){zXuMqKctPq = true;}
      if(MlZsahcdmE == WZEIXHtNxy){XSRYsDabxA = true;}
      else if(WZEIXHtNxy == MlZsahcdmE){OzuRwpoeUB = true;}
      if(VujeNjkoyX == ceQDjOulTQ){kGKbEFoyiM = true;}
      else if(ceQDjOulTQ == VujeNjkoyX){pUSkMUCuUz = true;}
      if(inydCYAXUf == MKAxkIckDf){YiaiZoRCnG = true;}
      else if(MKAxkIckDf == inydCYAXUf){DjwVNazTMQ = true;}
      if(JQDDCILzCo == ZKNkPqPAze){LIJMXqGtRd = true;}
      else if(ZKNkPqPAze == JQDDCILzCo){eDGYzrVEwe = true;}
      if(yJroyOGfOw == ieihBoyEQr){jQkESLxAeu = true;}
      if(sfXWXXmwpB == yNQegLZGXP){kWjxKnqhzE = true;}
      if(hEJGtFqgbF == dIJQXRRfmr){lYnpnbxyEN = true;}
      while(ieihBoyEQr == yJroyOGfOw){zsqzreFKAV = true;}
      while(yNQegLZGXP == yNQegLZGXP){IgYQndCZEV = true;}
      while(dIJQXRRfmr == dIJQXRRfmr){qUSEWmNtkT = true;}
      if(ytloggaSuu == true){ytloggaSuu = false;}
      if(KYTKhLshED == true){KYTKhLshED = false;}
      if(RIcjAZVSJi == true){RIcjAZVSJi = false;}
      if(XSRYsDabxA == true){XSRYsDabxA = false;}
      if(kGKbEFoyiM == true){kGKbEFoyiM = false;}
      if(YiaiZoRCnG == true){YiaiZoRCnG = false;}
      if(LIJMXqGtRd == true){LIJMXqGtRd = false;}
      if(jQkESLxAeu == true){jQkESLxAeu = false;}
      if(kWjxKnqhzE == true){kWjxKnqhzE = false;}
      if(lYnpnbxyEN == true){lYnpnbxyEN = false;}
      if(ytgEbIyWPN == true){ytgEbIyWPN = false;}
      if(qQWsVoYMBi == true){qQWsVoYMBi = false;}
      if(zXuMqKctPq == true){zXuMqKctPq = false;}
      if(OzuRwpoeUB == true){OzuRwpoeUB = false;}
      if(pUSkMUCuUz == true){pUSkMUCuUz = false;}
      if(DjwVNazTMQ == true){DjwVNazTMQ = false;}
      if(eDGYzrVEwe == true){eDGYzrVEwe = false;}
      if(zsqzreFKAV == true){zsqzreFKAV = false;}
      if(IgYQndCZEV == true){IgYQndCZEV = false;}
      if(qUSEWmNtkT == true){qUSEWmNtkT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GRATWIYUIA
{ 
  void HTsWgjjltu()
  { 
      bool UDftKduUIc = false;
      bool MOLzoJXBjy = false;
      bool VfgCmBSzpl = false;
      bool ELcfFRPaKs = false;
      bool GyxDaBHcsG = false;
      bool lRkcDnVdGJ = false;
      bool LueWYBkesX = false;
      bool swpqqWhdbl = false;
      bool soGizlZAcR = false;
      bool wkTBgKSadY = false;
      bool PcjUNpatlf = false;
      bool FqCUPWouWl = false;
      bool bkCabHboJf = false;
      bool EHzCWQEkVJ = false;
      bool KfOwMEizlK = false;
      bool VXDrxdZIsF = false;
      bool NlkFbxqAyy = false;
      bool REZNawWGOW = false;
      bool YcCyKgEHEr = false;
      bool quqQwYtJTO = false;
      string LIhrDANHGC;
      string GrOzQHWTCu;
      string IbpogcYHoi;
      string kcBYhaGHMO;
      string cXbXrtqCxy;
      string nTNVQjSsLZ;
      string bGSWRdpoRp;
      string APGnRjzSwl;
      string lVJqtQPfIy;
      string HNwllVEEFO;
      string EBkHxYNYDf;
      string jAwYnFxbcA;
      string NJgThmSTBw;
      string euMhhjkBsV;
      string DpcbNHRWyf;
      string YcbFBtTRYK;
      string FsWHAnmOpD;
      string UuhGwXgFFZ;
      string UwVVWCSGgn;
      string PTchQKSVbY;
      if(LIhrDANHGC == EBkHxYNYDf){UDftKduUIc = true;}
      else if(EBkHxYNYDf == LIhrDANHGC){PcjUNpatlf = true;}
      if(GrOzQHWTCu == jAwYnFxbcA){MOLzoJXBjy = true;}
      else if(jAwYnFxbcA == GrOzQHWTCu){FqCUPWouWl = true;}
      if(IbpogcYHoi == NJgThmSTBw){VfgCmBSzpl = true;}
      else if(NJgThmSTBw == IbpogcYHoi){bkCabHboJf = true;}
      if(kcBYhaGHMO == euMhhjkBsV){ELcfFRPaKs = true;}
      else if(euMhhjkBsV == kcBYhaGHMO){EHzCWQEkVJ = true;}
      if(cXbXrtqCxy == DpcbNHRWyf){GyxDaBHcsG = true;}
      else if(DpcbNHRWyf == cXbXrtqCxy){KfOwMEizlK = true;}
      if(nTNVQjSsLZ == YcbFBtTRYK){lRkcDnVdGJ = true;}
      else if(YcbFBtTRYK == nTNVQjSsLZ){VXDrxdZIsF = true;}
      if(bGSWRdpoRp == FsWHAnmOpD){LueWYBkesX = true;}
      else if(FsWHAnmOpD == bGSWRdpoRp){NlkFbxqAyy = true;}
      if(APGnRjzSwl == UuhGwXgFFZ){swpqqWhdbl = true;}
      if(lVJqtQPfIy == UwVVWCSGgn){soGizlZAcR = true;}
      if(HNwllVEEFO == PTchQKSVbY){wkTBgKSadY = true;}
      while(UuhGwXgFFZ == APGnRjzSwl){REZNawWGOW = true;}
      while(UwVVWCSGgn == UwVVWCSGgn){YcCyKgEHEr = true;}
      while(PTchQKSVbY == PTchQKSVbY){quqQwYtJTO = true;}
      if(UDftKduUIc == true){UDftKduUIc = false;}
      if(MOLzoJXBjy == true){MOLzoJXBjy = false;}
      if(VfgCmBSzpl == true){VfgCmBSzpl = false;}
      if(ELcfFRPaKs == true){ELcfFRPaKs = false;}
      if(GyxDaBHcsG == true){GyxDaBHcsG = false;}
      if(lRkcDnVdGJ == true){lRkcDnVdGJ = false;}
      if(LueWYBkesX == true){LueWYBkesX = false;}
      if(swpqqWhdbl == true){swpqqWhdbl = false;}
      if(soGizlZAcR == true){soGizlZAcR = false;}
      if(wkTBgKSadY == true){wkTBgKSadY = false;}
      if(PcjUNpatlf == true){PcjUNpatlf = false;}
      if(FqCUPWouWl == true){FqCUPWouWl = false;}
      if(bkCabHboJf == true){bkCabHboJf = false;}
      if(EHzCWQEkVJ == true){EHzCWQEkVJ = false;}
      if(KfOwMEizlK == true){KfOwMEizlK = false;}
      if(VXDrxdZIsF == true){VXDrxdZIsF = false;}
      if(NlkFbxqAyy == true){NlkFbxqAyy = false;}
      if(REZNawWGOW == true){REZNawWGOW = false;}
      if(YcCyKgEHEr == true){YcCyKgEHEr = false;}
      if(quqQwYtJTO == true){quqQwYtJTO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SZEXFCBSES
{ 
  void hrEjRdGhqQ()
  { 
      bool nccbfqepbA = false;
      bool OntkxDBPAP = false;
      bool fXZUCYbkOX = false;
      bool sUVSKMSwAs = false;
      bool LTWmMwILdp = false;
      bool ANOsaPCIZH = false;
      bool OtbDHtSaak = false;
      bool jFPGELBmHF = false;
      bool QPGXXeFbru = false;
      bool JKVrdQrSfS = false;
      bool cgksFuyInO = false;
      bool OPATpzmDfb = false;
      bool oqifaZiWbn = false;
      bool ThHobjeNRc = false;
      bool gxmcftKBBe = false;
      bool dnmDclyERf = false;
      bool LafAugIKrG = false;
      bool UYlCtrEFzg = false;
      bool OhUxJetDLp = false;
      bool kZwkRFRlhz = false;
      string lWIyzozJZk;
      string wRCbGTBPOe;
      string gctEPlbQzH;
      string wpuAGMVfUT;
      string GdSqYFRNnR;
      string qIfJsJbEhM;
      string MiJSnGVCUt;
      string yUuuXDJDeK;
      string UObhQnKlGx;
      string jRyHGWTACS;
      string iPrtTWMkkp;
      string zYZXryHbCA;
      string ujuXJgWnnA;
      string iIBLaEWhOs;
      string aYAQxLqZPH;
      string PryBWyTTjm;
      string zYwkGpXOxm;
      string bYMIZVjeZy;
      string owXgjpKznb;
      string kCxbtBcPJG;
      if(lWIyzozJZk == iPrtTWMkkp){nccbfqepbA = true;}
      else if(iPrtTWMkkp == lWIyzozJZk){cgksFuyInO = true;}
      if(wRCbGTBPOe == zYZXryHbCA){OntkxDBPAP = true;}
      else if(zYZXryHbCA == wRCbGTBPOe){OPATpzmDfb = true;}
      if(gctEPlbQzH == ujuXJgWnnA){fXZUCYbkOX = true;}
      else if(ujuXJgWnnA == gctEPlbQzH){oqifaZiWbn = true;}
      if(wpuAGMVfUT == iIBLaEWhOs){sUVSKMSwAs = true;}
      else if(iIBLaEWhOs == wpuAGMVfUT){ThHobjeNRc = true;}
      if(GdSqYFRNnR == aYAQxLqZPH){LTWmMwILdp = true;}
      else if(aYAQxLqZPH == GdSqYFRNnR){gxmcftKBBe = true;}
      if(qIfJsJbEhM == PryBWyTTjm){ANOsaPCIZH = true;}
      else if(PryBWyTTjm == qIfJsJbEhM){dnmDclyERf = true;}
      if(MiJSnGVCUt == zYwkGpXOxm){OtbDHtSaak = true;}
      else if(zYwkGpXOxm == MiJSnGVCUt){LafAugIKrG = true;}
      if(yUuuXDJDeK == bYMIZVjeZy){jFPGELBmHF = true;}
      if(UObhQnKlGx == owXgjpKznb){QPGXXeFbru = true;}
      if(jRyHGWTACS == kCxbtBcPJG){JKVrdQrSfS = true;}
      while(bYMIZVjeZy == yUuuXDJDeK){UYlCtrEFzg = true;}
      while(owXgjpKznb == owXgjpKznb){OhUxJetDLp = true;}
      while(kCxbtBcPJG == kCxbtBcPJG){kZwkRFRlhz = true;}
      if(nccbfqepbA == true){nccbfqepbA = false;}
      if(OntkxDBPAP == true){OntkxDBPAP = false;}
      if(fXZUCYbkOX == true){fXZUCYbkOX = false;}
      if(sUVSKMSwAs == true){sUVSKMSwAs = false;}
      if(LTWmMwILdp == true){LTWmMwILdp = false;}
      if(ANOsaPCIZH == true){ANOsaPCIZH = false;}
      if(OtbDHtSaak == true){OtbDHtSaak = false;}
      if(jFPGELBmHF == true){jFPGELBmHF = false;}
      if(QPGXXeFbru == true){QPGXXeFbru = false;}
      if(JKVrdQrSfS == true){JKVrdQrSfS = false;}
      if(cgksFuyInO == true){cgksFuyInO = false;}
      if(OPATpzmDfb == true){OPATpzmDfb = false;}
      if(oqifaZiWbn == true){oqifaZiWbn = false;}
      if(ThHobjeNRc == true){ThHobjeNRc = false;}
      if(gxmcftKBBe == true){gxmcftKBBe = false;}
      if(dnmDclyERf == true){dnmDclyERf = false;}
      if(LafAugIKrG == true){LafAugIKrG = false;}
      if(UYlCtrEFzg == true){UYlCtrEFzg = false;}
      if(OhUxJetDLp == true){OhUxJetDLp = false;}
      if(kZwkRFRlhz == true){kZwkRFRlhz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZQJLUVXYRY
{ 
  void NIxPIaQXTa()
  { 
      bool wzLCroUGhG = false;
      bool tmYRclknzF = false;
      bool QJVnMzVVFm = false;
      bool sZzkWmAsRp = false;
      bool sMUgjVabBE = false;
      bool kcBACldXor = false;
      bool SzBtNUnnup = false;
      bool lqWILDnnEq = false;
      bool YtTBCPXzhj = false;
      bool IcEYXtLZTO = false;
      bool gmgLRtGsoz = false;
      bool xoSyTYfArx = false;
      bool xoGKgJmxjR = false;
      bool qOUpJlNIiH = false;
      bool JdJhlSJGEz = false;
      bool NLhVQrfVdI = false;
      bool HIIWHiUcnh = false;
      bool LXQjmTeXXN = false;
      bool zfrkDffyZQ = false;
      bool FqdZABUmaC = false;
      string hYtzyHghdm;
      string ryqpKyhGoY;
      string SRTjEDPtgL;
      string VxwiYTgrqO;
      string mQGVmceBCb;
      string fQdBFQEKtu;
      string qlARRuBIQp;
      string RoPZkBKywb;
      string XNqFfETudI;
      string OWyuWAQnEr;
      string aWjMKpBDPE;
      string FGNSWduulM;
      string aGdHauqTDk;
      string jVtEABcetp;
      string DQfYDIIeXs;
      string FVCqQUrckP;
      string zgzeTjMISV;
      string APAwJKZEES;
      string lMwKfOSCme;
      string IAteqVRAFT;
      if(hYtzyHghdm == aWjMKpBDPE){wzLCroUGhG = true;}
      else if(aWjMKpBDPE == hYtzyHghdm){gmgLRtGsoz = true;}
      if(ryqpKyhGoY == FGNSWduulM){tmYRclknzF = true;}
      else if(FGNSWduulM == ryqpKyhGoY){xoSyTYfArx = true;}
      if(SRTjEDPtgL == aGdHauqTDk){QJVnMzVVFm = true;}
      else if(aGdHauqTDk == SRTjEDPtgL){xoGKgJmxjR = true;}
      if(VxwiYTgrqO == jVtEABcetp){sZzkWmAsRp = true;}
      else if(jVtEABcetp == VxwiYTgrqO){qOUpJlNIiH = true;}
      if(mQGVmceBCb == DQfYDIIeXs){sMUgjVabBE = true;}
      else if(DQfYDIIeXs == mQGVmceBCb){JdJhlSJGEz = true;}
      if(fQdBFQEKtu == FVCqQUrckP){kcBACldXor = true;}
      else if(FVCqQUrckP == fQdBFQEKtu){NLhVQrfVdI = true;}
      if(qlARRuBIQp == zgzeTjMISV){SzBtNUnnup = true;}
      else if(zgzeTjMISV == qlARRuBIQp){HIIWHiUcnh = true;}
      if(RoPZkBKywb == APAwJKZEES){lqWILDnnEq = true;}
      if(XNqFfETudI == lMwKfOSCme){YtTBCPXzhj = true;}
      if(OWyuWAQnEr == IAteqVRAFT){IcEYXtLZTO = true;}
      while(APAwJKZEES == RoPZkBKywb){LXQjmTeXXN = true;}
      while(lMwKfOSCme == lMwKfOSCme){zfrkDffyZQ = true;}
      while(IAteqVRAFT == IAteqVRAFT){FqdZABUmaC = true;}
      if(wzLCroUGhG == true){wzLCroUGhG = false;}
      if(tmYRclknzF == true){tmYRclknzF = false;}
      if(QJVnMzVVFm == true){QJVnMzVVFm = false;}
      if(sZzkWmAsRp == true){sZzkWmAsRp = false;}
      if(sMUgjVabBE == true){sMUgjVabBE = false;}
      if(kcBACldXor == true){kcBACldXor = false;}
      if(SzBtNUnnup == true){SzBtNUnnup = false;}
      if(lqWILDnnEq == true){lqWILDnnEq = false;}
      if(YtTBCPXzhj == true){YtTBCPXzhj = false;}
      if(IcEYXtLZTO == true){IcEYXtLZTO = false;}
      if(gmgLRtGsoz == true){gmgLRtGsoz = false;}
      if(xoSyTYfArx == true){xoSyTYfArx = false;}
      if(xoGKgJmxjR == true){xoGKgJmxjR = false;}
      if(qOUpJlNIiH == true){qOUpJlNIiH = false;}
      if(JdJhlSJGEz == true){JdJhlSJGEz = false;}
      if(NLhVQrfVdI == true){NLhVQrfVdI = false;}
      if(HIIWHiUcnh == true){HIIWHiUcnh = false;}
      if(LXQjmTeXXN == true){LXQjmTeXXN = false;}
      if(zfrkDffyZQ == true){zfrkDffyZQ = false;}
      if(FqdZABUmaC == true){FqdZABUmaC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FFIZVAZVTZ
{ 
  void MpioRjEDYw()
  { 
      bool tWMWUFrGyR = false;
      bool aWamrzVVSy = false;
      bool QGKuaVDCWH = false;
      bool snyOCNDrCY = false;
      bool KNQFqxUsfG = false;
      bool BzLAjmMQwz = false;
      bool BpipXlXLke = false;
      bool udTtnCpFDd = false;
      bool AKVQGscydO = false;
      bool BlwDWTdagF = false;
      bool YIIBKWfRLh = false;
      bool xHMRyqTSid = false;
      bool IZhVcJhPWT = false;
      bool XPXyEqBUFj = false;
      bool NLlwRtYdEf = false;
      bool ALqCwzamXB = false;
      bool oPtrJgiONG = false;
      bool ozMzQxmkDi = false;
      bool jEKqSMXUBF = false;
      bool QOwEuxQtmj = false;
      string WJQSqYLZDn;
      string NWwdpWcaTR;
      string YumRmztyXc;
      string ZSdXCAphrU;
      string EBIeEjrRlB;
      string BABgxbWzeq;
      string eMCZNtsYap;
      string gthzMXlIND;
      string HbMWbZQwZa;
      string dqCBoqzhQJ;
      string pSpwTGRCTZ;
      string oNkbiCAeym;
      string cwyAMpqgJV;
      string XErDMnkPCU;
      string IOcAkPFaRl;
      string pUjcftUpid;
      string OksyBkVhOu;
      string RjbceOTxOw;
      string kPOWeDUOWS;
      string TufYFWUeyA;
      if(WJQSqYLZDn == pSpwTGRCTZ){tWMWUFrGyR = true;}
      else if(pSpwTGRCTZ == WJQSqYLZDn){YIIBKWfRLh = true;}
      if(NWwdpWcaTR == oNkbiCAeym){aWamrzVVSy = true;}
      else if(oNkbiCAeym == NWwdpWcaTR){xHMRyqTSid = true;}
      if(YumRmztyXc == cwyAMpqgJV){QGKuaVDCWH = true;}
      else if(cwyAMpqgJV == YumRmztyXc){IZhVcJhPWT = true;}
      if(ZSdXCAphrU == XErDMnkPCU){snyOCNDrCY = true;}
      else if(XErDMnkPCU == ZSdXCAphrU){XPXyEqBUFj = true;}
      if(EBIeEjrRlB == IOcAkPFaRl){KNQFqxUsfG = true;}
      else if(IOcAkPFaRl == EBIeEjrRlB){NLlwRtYdEf = true;}
      if(BABgxbWzeq == pUjcftUpid){BzLAjmMQwz = true;}
      else if(pUjcftUpid == BABgxbWzeq){ALqCwzamXB = true;}
      if(eMCZNtsYap == OksyBkVhOu){BpipXlXLke = true;}
      else if(OksyBkVhOu == eMCZNtsYap){oPtrJgiONG = true;}
      if(gthzMXlIND == RjbceOTxOw){udTtnCpFDd = true;}
      if(HbMWbZQwZa == kPOWeDUOWS){AKVQGscydO = true;}
      if(dqCBoqzhQJ == TufYFWUeyA){BlwDWTdagF = true;}
      while(RjbceOTxOw == gthzMXlIND){ozMzQxmkDi = true;}
      while(kPOWeDUOWS == kPOWeDUOWS){jEKqSMXUBF = true;}
      while(TufYFWUeyA == TufYFWUeyA){QOwEuxQtmj = true;}
      if(tWMWUFrGyR == true){tWMWUFrGyR = false;}
      if(aWamrzVVSy == true){aWamrzVVSy = false;}
      if(QGKuaVDCWH == true){QGKuaVDCWH = false;}
      if(snyOCNDrCY == true){snyOCNDrCY = false;}
      if(KNQFqxUsfG == true){KNQFqxUsfG = false;}
      if(BzLAjmMQwz == true){BzLAjmMQwz = false;}
      if(BpipXlXLke == true){BpipXlXLke = false;}
      if(udTtnCpFDd == true){udTtnCpFDd = false;}
      if(AKVQGscydO == true){AKVQGscydO = false;}
      if(BlwDWTdagF == true){BlwDWTdagF = false;}
      if(YIIBKWfRLh == true){YIIBKWfRLh = false;}
      if(xHMRyqTSid == true){xHMRyqTSid = false;}
      if(IZhVcJhPWT == true){IZhVcJhPWT = false;}
      if(XPXyEqBUFj == true){XPXyEqBUFj = false;}
      if(NLlwRtYdEf == true){NLlwRtYdEf = false;}
      if(ALqCwzamXB == true){ALqCwzamXB = false;}
      if(oPtrJgiONG == true){oPtrJgiONG = false;}
      if(ozMzQxmkDi == true){ozMzQxmkDi = false;}
      if(jEKqSMXUBF == true){jEKqSMXUBF = false;}
      if(QOwEuxQtmj == true){QOwEuxQtmj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BFPRLFCHAG
{ 
  void kXsoIQmrfU()
  { 
      bool VWXDxpTbSy = false;
      bool xVlkqesSyE = false;
      bool nNjBbLDIIo = false;
      bool dhZqWHOlAH = false;
      bool uzARPOjlDH = false;
      bool TCYGKIlVak = false;
      bool lKSdUOutOj = false;
      bool PHRpInNSlN = false;
      bool bQEAUaITgO = false;
      bool UsKPUkgWxA = false;
      bool SoXTrLkixV = false;
      bool tTjNJVFRIs = false;
      bool GbNzPWwCUX = false;
      bool HqVltmrkHI = false;
      bool pZVKTBIxGz = false;
      bool eOODsqaYDV = false;
      bool PiNZNDxySV = false;
      bool cTJzDfFCeO = false;
      bool NywUsscRrD = false;
      bool LThlsHMwwQ = false;
      string YtBhSPjJSo;
      string jMiwcdPXUR;
      string onOsSuzbxX;
      string DSHeNFrcud;
      string EGRFzecRyI;
      string cRlaqjeHPX;
      string PHLukREEiW;
      string llcqNiVJtn;
      string Rhdoulggmc;
      string ZjNWNwuWUh;
      string ZYiaWpotNH;
      string OVMbGhdWzz;
      string kXQFxBYFdQ;
      string nynMNszCRE;
      string wlTeODWkQf;
      string SYWVxBHcdV;
      string RiQwTPgANN;
      string hbEuCyEkps;
      string dmoyyPaSPM;
      string kVXulNUWLz;
      if(YtBhSPjJSo == ZYiaWpotNH){VWXDxpTbSy = true;}
      else if(ZYiaWpotNH == YtBhSPjJSo){SoXTrLkixV = true;}
      if(jMiwcdPXUR == OVMbGhdWzz){xVlkqesSyE = true;}
      else if(OVMbGhdWzz == jMiwcdPXUR){tTjNJVFRIs = true;}
      if(onOsSuzbxX == kXQFxBYFdQ){nNjBbLDIIo = true;}
      else if(kXQFxBYFdQ == onOsSuzbxX){GbNzPWwCUX = true;}
      if(DSHeNFrcud == nynMNszCRE){dhZqWHOlAH = true;}
      else if(nynMNszCRE == DSHeNFrcud){HqVltmrkHI = true;}
      if(EGRFzecRyI == wlTeODWkQf){uzARPOjlDH = true;}
      else if(wlTeODWkQf == EGRFzecRyI){pZVKTBIxGz = true;}
      if(cRlaqjeHPX == SYWVxBHcdV){TCYGKIlVak = true;}
      else if(SYWVxBHcdV == cRlaqjeHPX){eOODsqaYDV = true;}
      if(PHLukREEiW == RiQwTPgANN){lKSdUOutOj = true;}
      else if(RiQwTPgANN == PHLukREEiW){PiNZNDxySV = true;}
      if(llcqNiVJtn == hbEuCyEkps){PHRpInNSlN = true;}
      if(Rhdoulggmc == dmoyyPaSPM){bQEAUaITgO = true;}
      if(ZjNWNwuWUh == kVXulNUWLz){UsKPUkgWxA = true;}
      while(hbEuCyEkps == llcqNiVJtn){cTJzDfFCeO = true;}
      while(dmoyyPaSPM == dmoyyPaSPM){NywUsscRrD = true;}
      while(kVXulNUWLz == kVXulNUWLz){LThlsHMwwQ = true;}
      if(VWXDxpTbSy == true){VWXDxpTbSy = false;}
      if(xVlkqesSyE == true){xVlkqesSyE = false;}
      if(nNjBbLDIIo == true){nNjBbLDIIo = false;}
      if(dhZqWHOlAH == true){dhZqWHOlAH = false;}
      if(uzARPOjlDH == true){uzARPOjlDH = false;}
      if(TCYGKIlVak == true){TCYGKIlVak = false;}
      if(lKSdUOutOj == true){lKSdUOutOj = false;}
      if(PHRpInNSlN == true){PHRpInNSlN = false;}
      if(bQEAUaITgO == true){bQEAUaITgO = false;}
      if(UsKPUkgWxA == true){UsKPUkgWxA = false;}
      if(SoXTrLkixV == true){SoXTrLkixV = false;}
      if(tTjNJVFRIs == true){tTjNJVFRIs = false;}
      if(GbNzPWwCUX == true){GbNzPWwCUX = false;}
      if(HqVltmrkHI == true){HqVltmrkHI = false;}
      if(pZVKTBIxGz == true){pZVKTBIxGz = false;}
      if(eOODsqaYDV == true){eOODsqaYDV = false;}
      if(PiNZNDxySV == true){PiNZNDxySV = false;}
      if(cTJzDfFCeO == true){cTJzDfFCeO = false;}
      if(NywUsscRrD == true){NywUsscRrD = false;}
      if(LThlsHMwwQ == true){LThlsHMwwQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CSGIUEWEWZ
{ 
  void ixjAeJdeAu()
  { 
      bool lDoYdtFqdd = false;
      bool AjsCqTsqKw = false;
      bool tRUqGsjrpU = false;
      bool ySJVXoEuDh = false;
      bool tnrsifjMts = false;
      bool RJdYJUixSj = false;
      bool KNBJfhaXeC = false;
      bool PymbBGZaIZ = false;
      bool JXywDnnjLC = false;
      bool GGbTXgliNB = false;
      bool FLgrdSWCXD = false;
      bool uHnramOFFr = false;
      bool sqLbuIVSDU = false;
      bool UpNHUxpGRk = false;
      bool QlLIHzRjsk = false;
      bool RfcUHOAEwV = false;
      bool wDyDiEsgWc = false;
      bool wImUaHeCUw = false;
      bool plZSCnMrAG = false;
      bool wkJwnMmIYC = false;
      string AwMplbMqmI;
      string BNlOCRWFUS;
      string sAaOrthJxL;
      string ytqseSmepQ;
      string ZbBbKLEJhD;
      string NtMEwAUxxr;
      string sDtbKHVsji;
      string dqOEsRzzEf;
      string pXatxEgmwe;
      string xogyWVhYQD;
      string pKZyYWeHKe;
      string AVsRBVbzdF;
      string ZiwFknJQhW;
      string iZhBpeycVa;
      string ZZbRdauPwA;
      string tiuKcGOUMj;
      string MNYmwZnraW;
      string WzcDfzGeaK;
      string ssUhcAeWXi;
      string PdPkNLBnVE;
      if(AwMplbMqmI == pKZyYWeHKe){lDoYdtFqdd = true;}
      else if(pKZyYWeHKe == AwMplbMqmI){FLgrdSWCXD = true;}
      if(BNlOCRWFUS == AVsRBVbzdF){AjsCqTsqKw = true;}
      else if(AVsRBVbzdF == BNlOCRWFUS){uHnramOFFr = true;}
      if(sAaOrthJxL == ZiwFknJQhW){tRUqGsjrpU = true;}
      else if(ZiwFknJQhW == sAaOrthJxL){sqLbuIVSDU = true;}
      if(ytqseSmepQ == iZhBpeycVa){ySJVXoEuDh = true;}
      else if(iZhBpeycVa == ytqseSmepQ){UpNHUxpGRk = true;}
      if(ZbBbKLEJhD == ZZbRdauPwA){tnrsifjMts = true;}
      else if(ZZbRdauPwA == ZbBbKLEJhD){QlLIHzRjsk = true;}
      if(NtMEwAUxxr == tiuKcGOUMj){RJdYJUixSj = true;}
      else if(tiuKcGOUMj == NtMEwAUxxr){RfcUHOAEwV = true;}
      if(sDtbKHVsji == MNYmwZnraW){KNBJfhaXeC = true;}
      else if(MNYmwZnraW == sDtbKHVsji){wDyDiEsgWc = true;}
      if(dqOEsRzzEf == WzcDfzGeaK){PymbBGZaIZ = true;}
      if(pXatxEgmwe == ssUhcAeWXi){JXywDnnjLC = true;}
      if(xogyWVhYQD == PdPkNLBnVE){GGbTXgliNB = true;}
      while(WzcDfzGeaK == dqOEsRzzEf){wImUaHeCUw = true;}
      while(ssUhcAeWXi == ssUhcAeWXi){plZSCnMrAG = true;}
      while(PdPkNLBnVE == PdPkNLBnVE){wkJwnMmIYC = true;}
      if(lDoYdtFqdd == true){lDoYdtFqdd = false;}
      if(AjsCqTsqKw == true){AjsCqTsqKw = false;}
      if(tRUqGsjrpU == true){tRUqGsjrpU = false;}
      if(ySJVXoEuDh == true){ySJVXoEuDh = false;}
      if(tnrsifjMts == true){tnrsifjMts = false;}
      if(RJdYJUixSj == true){RJdYJUixSj = false;}
      if(KNBJfhaXeC == true){KNBJfhaXeC = false;}
      if(PymbBGZaIZ == true){PymbBGZaIZ = false;}
      if(JXywDnnjLC == true){JXywDnnjLC = false;}
      if(GGbTXgliNB == true){GGbTXgliNB = false;}
      if(FLgrdSWCXD == true){FLgrdSWCXD = false;}
      if(uHnramOFFr == true){uHnramOFFr = false;}
      if(sqLbuIVSDU == true){sqLbuIVSDU = false;}
      if(UpNHUxpGRk == true){UpNHUxpGRk = false;}
      if(QlLIHzRjsk == true){QlLIHzRjsk = false;}
      if(RfcUHOAEwV == true){RfcUHOAEwV = false;}
      if(wDyDiEsgWc == true){wDyDiEsgWc = false;}
      if(wImUaHeCUw == true){wImUaHeCUw = false;}
      if(plZSCnMrAG == true){plZSCnMrAG = false;}
      if(wkJwnMmIYC == true){wkJwnMmIYC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WRCLZTZNRX
{ 
  void fiATxrIiSR()
  { 
      bool PXkyRaojss = false;
      bool oKxZPLKUCL = false;
      bool DPtZJBwICK = false;
      bool bJYZffBHbf = false;
      bool KrxNjlhSKd = false;
      bool NAySezdLnQ = false;
      bool efgiRfkWsi = false;
      bool KCrWBLSgpW = false;
      bool ScyYwaKGug = false;
      bool CpSLAdKOwE = false;
      bool BKZaTKIbQS = false;
      bool gxVRyBgIlp = false;
      bool VebMfUjgVW = false;
      bool BDjkVHDWFk = false;
      bool ShobzFTBNy = false;
      bool wBbFiViNty = false;
      bool abGsRdMjup = false;
      bool yKDAXmpzMa = false;
      bool AhSWazadCz = false;
      bool XocGKqauKV = false;
      string iqIsYIUWKK;
      string tdwkGKGoRU;
      string zbAfboWMzO;
      string YQQfJnDZGE;
      string cZIjFhWFHF;
      string CJVYIHqbQi;
      string kIXukdNQaR;
      string GfhMqZTQas;
      string RQEsLPtrXC;
      string xaIWSTBMyb;
      string UGepzWaIgh;
      string mZBXRTDdiV;
      string iUrXTeXKsX;
      string XGSzYKlOto;
      string nkKoPWZkFz;
      string PXdbrzNGVU;
      string zPPJKfHBzG;
      string goishyKDIw;
      string EmFtHzcqHY;
      string xfrZpXVBdi;
      if(iqIsYIUWKK == UGepzWaIgh){PXkyRaojss = true;}
      else if(UGepzWaIgh == iqIsYIUWKK){BKZaTKIbQS = true;}
      if(tdwkGKGoRU == mZBXRTDdiV){oKxZPLKUCL = true;}
      else if(mZBXRTDdiV == tdwkGKGoRU){gxVRyBgIlp = true;}
      if(zbAfboWMzO == iUrXTeXKsX){DPtZJBwICK = true;}
      else if(iUrXTeXKsX == zbAfboWMzO){VebMfUjgVW = true;}
      if(YQQfJnDZGE == XGSzYKlOto){bJYZffBHbf = true;}
      else if(XGSzYKlOto == YQQfJnDZGE){BDjkVHDWFk = true;}
      if(cZIjFhWFHF == nkKoPWZkFz){KrxNjlhSKd = true;}
      else if(nkKoPWZkFz == cZIjFhWFHF){ShobzFTBNy = true;}
      if(CJVYIHqbQi == PXdbrzNGVU){NAySezdLnQ = true;}
      else if(PXdbrzNGVU == CJVYIHqbQi){wBbFiViNty = true;}
      if(kIXukdNQaR == zPPJKfHBzG){efgiRfkWsi = true;}
      else if(zPPJKfHBzG == kIXukdNQaR){abGsRdMjup = true;}
      if(GfhMqZTQas == goishyKDIw){KCrWBLSgpW = true;}
      if(RQEsLPtrXC == EmFtHzcqHY){ScyYwaKGug = true;}
      if(xaIWSTBMyb == xfrZpXVBdi){CpSLAdKOwE = true;}
      while(goishyKDIw == GfhMqZTQas){yKDAXmpzMa = true;}
      while(EmFtHzcqHY == EmFtHzcqHY){AhSWazadCz = true;}
      while(xfrZpXVBdi == xfrZpXVBdi){XocGKqauKV = true;}
      if(PXkyRaojss == true){PXkyRaojss = false;}
      if(oKxZPLKUCL == true){oKxZPLKUCL = false;}
      if(DPtZJBwICK == true){DPtZJBwICK = false;}
      if(bJYZffBHbf == true){bJYZffBHbf = false;}
      if(KrxNjlhSKd == true){KrxNjlhSKd = false;}
      if(NAySezdLnQ == true){NAySezdLnQ = false;}
      if(efgiRfkWsi == true){efgiRfkWsi = false;}
      if(KCrWBLSgpW == true){KCrWBLSgpW = false;}
      if(ScyYwaKGug == true){ScyYwaKGug = false;}
      if(CpSLAdKOwE == true){CpSLAdKOwE = false;}
      if(BKZaTKIbQS == true){BKZaTKIbQS = false;}
      if(gxVRyBgIlp == true){gxVRyBgIlp = false;}
      if(VebMfUjgVW == true){VebMfUjgVW = false;}
      if(BDjkVHDWFk == true){BDjkVHDWFk = false;}
      if(ShobzFTBNy == true){ShobzFTBNy = false;}
      if(wBbFiViNty == true){wBbFiViNty = false;}
      if(abGsRdMjup == true){abGsRdMjup = false;}
      if(yKDAXmpzMa == true){yKDAXmpzMa = false;}
      if(AhSWazadCz == true){AhSWazadCz = false;}
      if(XocGKqauKV == true){XocGKqauKV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXBLYKMYPS
{ 
  void iyaNiFwOKx()
  { 
      bool cKklmPFMmG = false;
      bool uQZeLFKNTX = false;
      bool TqRhninBqU = false;
      bool kRYJLPCmOl = false;
      bool QkYHGzZYVT = false;
      bool NGrRylrDyE = false;
      bool aDVSUdqPSw = false;
      bool CWzhGhSKbn = false;
      bool JOeWGeZGLZ = false;
      bool WzoKKMPGmc = false;
      bool HJGZRqHJKP = false;
      bool ThbJtLYyLp = false;
      bool EjDsZDhnWt = false;
      bool RMXzgAIFFO = false;
      bool WPwwGnXeQz = false;
      bool nRtxYWFNzO = false;
      bool ITmQyHKbbs = false;
      bool CSrxSnnHlk = false;
      bool eCWXFARaaJ = false;
      bool tuFqGDcfyz = false;
      string FdtmTNcPcM;
      string VFsHkzrOmt;
      string XRLHRuPwnT;
      string FAgCRqkBLF;
      string HTYmaHVBiR;
      string uAXSKnRmUX;
      string yfaJGUXqot;
      string OqCglErXfJ;
      string ZNNWXFcNqd;
      string YxfnHbrPgF;
      string ieMnCExpfG;
      string utGKyjSDkA;
      string rKzKUQKOZK;
      string LcqaatBYTT;
      string HlgkiepVoW;
      string JodfMYeBTl;
      string tiQVtRCfjD;
      string isiRsGcOao;
      string ZnYCBWyLNB;
      string PzEhZYULpR;
      if(FdtmTNcPcM == ieMnCExpfG){cKklmPFMmG = true;}
      else if(ieMnCExpfG == FdtmTNcPcM){HJGZRqHJKP = true;}
      if(VFsHkzrOmt == utGKyjSDkA){uQZeLFKNTX = true;}
      else if(utGKyjSDkA == VFsHkzrOmt){ThbJtLYyLp = true;}
      if(XRLHRuPwnT == rKzKUQKOZK){TqRhninBqU = true;}
      else if(rKzKUQKOZK == XRLHRuPwnT){EjDsZDhnWt = true;}
      if(FAgCRqkBLF == LcqaatBYTT){kRYJLPCmOl = true;}
      else if(LcqaatBYTT == FAgCRqkBLF){RMXzgAIFFO = true;}
      if(HTYmaHVBiR == HlgkiepVoW){QkYHGzZYVT = true;}
      else if(HlgkiepVoW == HTYmaHVBiR){WPwwGnXeQz = true;}
      if(uAXSKnRmUX == JodfMYeBTl){NGrRylrDyE = true;}
      else if(JodfMYeBTl == uAXSKnRmUX){nRtxYWFNzO = true;}
      if(yfaJGUXqot == tiQVtRCfjD){aDVSUdqPSw = true;}
      else if(tiQVtRCfjD == yfaJGUXqot){ITmQyHKbbs = true;}
      if(OqCglErXfJ == isiRsGcOao){CWzhGhSKbn = true;}
      if(ZNNWXFcNqd == ZnYCBWyLNB){JOeWGeZGLZ = true;}
      if(YxfnHbrPgF == PzEhZYULpR){WzoKKMPGmc = true;}
      while(isiRsGcOao == OqCglErXfJ){CSrxSnnHlk = true;}
      while(ZnYCBWyLNB == ZnYCBWyLNB){eCWXFARaaJ = true;}
      while(PzEhZYULpR == PzEhZYULpR){tuFqGDcfyz = true;}
      if(cKklmPFMmG == true){cKklmPFMmG = false;}
      if(uQZeLFKNTX == true){uQZeLFKNTX = false;}
      if(TqRhninBqU == true){TqRhninBqU = false;}
      if(kRYJLPCmOl == true){kRYJLPCmOl = false;}
      if(QkYHGzZYVT == true){QkYHGzZYVT = false;}
      if(NGrRylrDyE == true){NGrRylrDyE = false;}
      if(aDVSUdqPSw == true){aDVSUdqPSw = false;}
      if(CWzhGhSKbn == true){CWzhGhSKbn = false;}
      if(JOeWGeZGLZ == true){JOeWGeZGLZ = false;}
      if(WzoKKMPGmc == true){WzoKKMPGmc = false;}
      if(HJGZRqHJKP == true){HJGZRqHJKP = false;}
      if(ThbJtLYyLp == true){ThbJtLYyLp = false;}
      if(EjDsZDhnWt == true){EjDsZDhnWt = false;}
      if(RMXzgAIFFO == true){RMXzgAIFFO = false;}
      if(WPwwGnXeQz == true){WPwwGnXeQz = false;}
      if(nRtxYWFNzO == true){nRtxYWFNzO = false;}
      if(ITmQyHKbbs == true){ITmQyHKbbs = false;}
      if(CSrxSnnHlk == true){CSrxSnnHlk = false;}
      if(eCWXFARaaJ == true){eCWXFARaaJ = false;}
      if(tuFqGDcfyz == true){tuFqGDcfyz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SHUCPLNNDS
{ 
  void QfrZogLqmS()
  { 
      bool zhCtixXrzO = false;
      bool CmIrJyLLKM = false;
      bool dDsoHBpSqC = false;
      bool TOuKVKFZki = false;
      bool iiqVbVjTYr = false;
      bool eoYzIunNmg = false;
      bool HFBxumqyWy = false;
      bool skZadtLXMk = false;
      bool RVsyXdpwBZ = false;
      bool VrlDbdhtZn = false;
      bool elwZzsOyVN = false;
      bool jQABPkMCYQ = false;
      bool xtwxcAyVzA = false;
      bool MRxXGfYSzd = false;
      bool OqanoFqknp = false;
      bool ReUJqjozxy = false;
      bool uszVASScuj = false;
      bool LsDtBFTIHX = false;
      bool JNgIigwngV = false;
      bool pZUAiVrEmW = false;
      string MRwRzWopwD;
      string dHnNgUfAoK;
      string gqwxKpgNLa;
      string GRgUWtHdnP;
      string CpdEuCClNT;
      string oYFgpVVyHI;
      string padUxMaSpl;
      string MBLZIqMqCH;
      string nuArlhLAeB;
      string XIVfZaLJHi;
      string biuaGmMfYz;
      string IdwzUualhO;
      string AZnoNEefzg;
      string eDjSfEzYkz;
      string VfafrsLWLe;
      string zYarhBuFMC;
      string HffqTFtdTQ;
      string uCBirTyIxU;
      string rIUUgGbqje;
      string IsLiqpAjMl;
      if(MRwRzWopwD == biuaGmMfYz){zhCtixXrzO = true;}
      else if(biuaGmMfYz == MRwRzWopwD){elwZzsOyVN = true;}
      if(dHnNgUfAoK == IdwzUualhO){CmIrJyLLKM = true;}
      else if(IdwzUualhO == dHnNgUfAoK){jQABPkMCYQ = true;}
      if(gqwxKpgNLa == AZnoNEefzg){dDsoHBpSqC = true;}
      else if(AZnoNEefzg == gqwxKpgNLa){xtwxcAyVzA = true;}
      if(GRgUWtHdnP == eDjSfEzYkz){TOuKVKFZki = true;}
      else if(eDjSfEzYkz == GRgUWtHdnP){MRxXGfYSzd = true;}
      if(CpdEuCClNT == VfafrsLWLe){iiqVbVjTYr = true;}
      else if(VfafrsLWLe == CpdEuCClNT){OqanoFqknp = true;}
      if(oYFgpVVyHI == zYarhBuFMC){eoYzIunNmg = true;}
      else if(zYarhBuFMC == oYFgpVVyHI){ReUJqjozxy = true;}
      if(padUxMaSpl == HffqTFtdTQ){HFBxumqyWy = true;}
      else if(HffqTFtdTQ == padUxMaSpl){uszVASScuj = true;}
      if(MBLZIqMqCH == uCBirTyIxU){skZadtLXMk = true;}
      if(nuArlhLAeB == rIUUgGbqje){RVsyXdpwBZ = true;}
      if(XIVfZaLJHi == IsLiqpAjMl){VrlDbdhtZn = true;}
      while(uCBirTyIxU == MBLZIqMqCH){LsDtBFTIHX = true;}
      while(rIUUgGbqje == rIUUgGbqje){JNgIigwngV = true;}
      while(IsLiqpAjMl == IsLiqpAjMl){pZUAiVrEmW = true;}
      if(zhCtixXrzO == true){zhCtixXrzO = false;}
      if(CmIrJyLLKM == true){CmIrJyLLKM = false;}
      if(dDsoHBpSqC == true){dDsoHBpSqC = false;}
      if(TOuKVKFZki == true){TOuKVKFZki = false;}
      if(iiqVbVjTYr == true){iiqVbVjTYr = false;}
      if(eoYzIunNmg == true){eoYzIunNmg = false;}
      if(HFBxumqyWy == true){HFBxumqyWy = false;}
      if(skZadtLXMk == true){skZadtLXMk = false;}
      if(RVsyXdpwBZ == true){RVsyXdpwBZ = false;}
      if(VrlDbdhtZn == true){VrlDbdhtZn = false;}
      if(elwZzsOyVN == true){elwZzsOyVN = false;}
      if(jQABPkMCYQ == true){jQABPkMCYQ = false;}
      if(xtwxcAyVzA == true){xtwxcAyVzA = false;}
      if(MRxXGfYSzd == true){MRxXGfYSzd = false;}
      if(OqanoFqknp == true){OqanoFqknp = false;}
      if(ReUJqjozxy == true){ReUJqjozxy = false;}
      if(uszVASScuj == true){uszVASScuj = false;}
      if(LsDtBFTIHX == true){LsDtBFTIHX = false;}
      if(JNgIigwngV == true){JNgIigwngV = false;}
      if(pZUAiVrEmW == true){pZUAiVrEmW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EQNGNOLMKT
{ 
  void kiLyYaOFnV()
  { 
      bool gCAkcWzxqL = false;
      bool HElaRdwnVk = false;
      bool IfOjPyjNPc = false;
      bool OVhYEjmUwa = false;
      bool hfmAZmncek = false;
      bool wGIIQBmQUd = false;
      bool mlhNwlWNWh = false;
      bool paquCcrOKc = false;
      bool JGidgHMYIC = false;
      bool xWASmwxZEn = false;
      bool PaGwuUONGm = false;
      bool JYGrUfDEfn = false;
      bool ZyFTkTaYHF = false;
      bool eRKVMiAlhM = false;
      bool syRUsXQHxH = false;
      bool sssPORUlLb = false;
      bool spGAHqOjfk = false;
      bool fQVTuafkZM = false;
      bool CSaAMlYtHt = false;
      bool ONaGSCrQMC = false;
      string ymHyACbbki;
      string aNNHqQRVuw;
      string WINcpbLSrP;
      string VHgAtTPiye;
      string XGLrHphGNV;
      string HYHCbpYdIY;
      string pIiUNSfNNX;
      string BhXQYPxVVA;
      string sEFWHwAeYE;
      string tkaYnOWpdn;
      string JUsoUZBpdL;
      string sCIHfkDMNQ;
      string SBnIcPHybJ;
      string rGrgpXLPBh;
      string uJAMLrcSrC;
      string KKcMUIfjLE;
      string SCNUSlKaRH;
      string ZnKeVJBbxk;
      string lnGZyhdeLg;
      string raDxPruetY;
      if(ymHyACbbki == JUsoUZBpdL){gCAkcWzxqL = true;}
      else if(JUsoUZBpdL == ymHyACbbki){PaGwuUONGm = true;}
      if(aNNHqQRVuw == sCIHfkDMNQ){HElaRdwnVk = true;}
      else if(sCIHfkDMNQ == aNNHqQRVuw){JYGrUfDEfn = true;}
      if(WINcpbLSrP == SBnIcPHybJ){IfOjPyjNPc = true;}
      else if(SBnIcPHybJ == WINcpbLSrP){ZyFTkTaYHF = true;}
      if(VHgAtTPiye == rGrgpXLPBh){OVhYEjmUwa = true;}
      else if(rGrgpXLPBh == VHgAtTPiye){eRKVMiAlhM = true;}
      if(XGLrHphGNV == uJAMLrcSrC){hfmAZmncek = true;}
      else if(uJAMLrcSrC == XGLrHphGNV){syRUsXQHxH = true;}
      if(HYHCbpYdIY == KKcMUIfjLE){wGIIQBmQUd = true;}
      else if(KKcMUIfjLE == HYHCbpYdIY){sssPORUlLb = true;}
      if(pIiUNSfNNX == SCNUSlKaRH){mlhNwlWNWh = true;}
      else if(SCNUSlKaRH == pIiUNSfNNX){spGAHqOjfk = true;}
      if(BhXQYPxVVA == ZnKeVJBbxk){paquCcrOKc = true;}
      if(sEFWHwAeYE == lnGZyhdeLg){JGidgHMYIC = true;}
      if(tkaYnOWpdn == raDxPruetY){xWASmwxZEn = true;}
      while(ZnKeVJBbxk == BhXQYPxVVA){fQVTuafkZM = true;}
      while(lnGZyhdeLg == lnGZyhdeLg){CSaAMlYtHt = true;}
      while(raDxPruetY == raDxPruetY){ONaGSCrQMC = true;}
      if(gCAkcWzxqL == true){gCAkcWzxqL = false;}
      if(HElaRdwnVk == true){HElaRdwnVk = false;}
      if(IfOjPyjNPc == true){IfOjPyjNPc = false;}
      if(OVhYEjmUwa == true){OVhYEjmUwa = false;}
      if(hfmAZmncek == true){hfmAZmncek = false;}
      if(wGIIQBmQUd == true){wGIIQBmQUd = false;}
      if(mlhNwlWNWh == true){mlhNwlWNWh = false;}
      if(paquCcrOKc == true){paquCcrOKc = false;}
      if(JGidgHMYIC == true){JGidgHMYIC = false;}
      if(xWASmwxZEn == true){xWASmwxZEn = false;}
      if(PaGwuUONGm == true){PaGwuUONGm = false;}
      if(JYGrUfDEfn == true){JYGrUfDEfn = false;}
      if(ZyFTkTaYHF == true){ZyFTkTaYHF = false;}
      if(eRKVMiAlhM == true){eRKVMiAlhM = false;}
      if(syRUsXQHxH == true){syRUsXQHxH = false;}
      if(sssPORUlLb == true){sssPORUlLb = false;}
      if(spGAHqOjfk == true){spGAHqOjfk = false;}
      if(fQVTuafkZM == true){fQVTuafkZM = false;}
      if(CSaAMlYtHt == true){CSaAMlYtHt = false;}
      if(ONaGSCrQMC == true){ONaGSCrQMC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NLRGHWHVJI
{ 
  void KmhRMBQuGe()
  { 
      bool FptgWKVdWN = false;
      bool WENVSmhaPi = false;
      bool LxgzFuDqrU = false;
      bool YZhfmhGwYp = false;
      bool wrKQxelLsT = false;
      bool DBkxdHIubb = false;
      bool HelBnwVghj = false;
      bool glCZlSmPBZ = false;
      bool IqxXRWojCe = false;
      bool YLUwhRGJbB = false;
      bool IFcIlQyLLL = false;
      bool UrtBSQgNiQ = false;
      bool HldDLVRFqU = false;
      bool MdmARDNokA = false;
      bool XdYqKfRTcR = false;
      bool krZLsWaZxQ = false;
      bool zsTpzpEsjP = false;
      bool DqcircMmre = false;
      bool EybYjTEbGt = false;
      bool bmrTBeJirT = false;
      string FXfYcmyhTD;
      string apLULAQzAS;
      string SwoQaMteLW;
      string nkRmRIUzgo;
      string tzVwGPpgst;
      string VdylMJhOxP;
      string rSVwOoXYCC;
      string eRRLYTZrKK;
      string VNlRAKmeaH;
      string ZFBQxbcYhQ;
      string qRdpPEMlNr;
      string ioEmtdfEuE;
      string CsxtcYPAOw;
      string qAKsSEiuBw;
      string xARhYjBOWS;
      string uYdcOyTiNp;
      string oLXQBieLTp;
      string ukCzGBaPVr;
      string XBcwBRWgdU;
      string jzhLHlcAgo;
      if(FXfYcmyhTD == qRdpPEMlNr){FptgWKVdWN = true;}
      else if(qRdpPEMlNr == FXfYcmyhTD){IFcIlQyLLL = true;}
      if(apLULAQzAS == ioEmtdfEuE){WENVSmhaPi = true;}
      else if(ioEmtdfEuE == apLULAQzAS){UrtBSQgNiQ = true;}
      if(SwoQaMteLW == CsxtcYPAOw){LxgzFuDqrU = true;}
      else if(CsxtcYPAOw == SwoQaMteLW){HldDLVRFqU = true;}
      if(nkRmRIUzgo == qAKsSEiuBw){YZhfmhGwYp = true;}
      else if(qAKsSEiuBw == nkRmRIUzgo){MdmARDNokA = true;}
      if(tzVwGPpgst == xARhYjBOWS){wrKQxelLsT = true;}
      else if(xARhYjBOWS == tzVwGPpgst){XdYqKfRTcR = true;}
      if(VdylMJhOxP == uYdcOyTiNp){DBkxdHIubb = true;}
      else if(uYdcOyTiNp == VdylMJhOxP){krZLsWaZxQ = true;}
      if(rSVwOoXYCC == oLXQBieLTp){HelBnwVghj = true;}
      else if(oLXQBieLTp == rSVwOoXYCC){zsTpzpEsjP = true;}
      if(eRRLYTZrKK == ukCzGBaPVr){glCZlSmPBZ = true;}
      if(VNlRAKmeaH == XBcwBRWgdU){IqxXRWojCe = true;}
      if(ZFBQxbcYhQ == jzhLHlcAgo){YLUwhRGJbB = true;}
      while(ukCzGBaPVr == eRRLYTZrKK){DqcircMmre = true;}
      while(XBcwBRWgdU == XBcwBRWgdU){EybYjTEbGt = true;}
      while(jzhLHlcAgo == jzhLHlcAgo){bmrTBeJirT = true;}
      if(FptgWKVdWN == true){FptgWKVdWN = false;}
      if(WENVSmhaPi == true){WENVSmhaPi = false;}
      if(LxgzFuDqrU == true){LxgzFuDqrU = false;}
      if(YZhfmhGwYp == true){YZhfmhGwYp = false;}
      if(wrKQxelLsT == true){wrKQxelLsT = false;}
      if(DBkxdHIubb == true){DBkxdHIubb = false;}
      if(HelBnwVghj == true){HelBnwVghj = false;}
      if(glCZlSmPBZ == true){glCZlSmPBZ = false;}
      if(IqxXRWojCe == true){IqxXRWojCe = false;}
      if(YLUwhRGJbB == true){YLUwhRGJbB = false;}
      if(IFcIlQyLLL == true){IFcIlQyLLL = false;}
      if(UrtBSQgNiQ == true){UrtBSQgNiQ = false;}
      if(HldDLVRFqU == true){HldDLVRFqU = false;}
      if(MdmARDNokA == true){MdmARDNokA = false;}
      if(XdYqKfRTcR == true){XdYqKfRTcR = false;}
      if(krZLsWaZxQ == true){krZLsWaZxQ = false;}
      if(zsTpzpEsjP == true){zsTpzpEsjP = false;}
      if(DqcircMmre == true){DqcircMmre = false;}
      if(EybYjTEbGt == true){EybYjTEbGt = false;}
      if(bmrTBeJirT == true){bmrTBeJirT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRJSLMJPXU
{ 
  void kCAHGPxCzf()
  { 
      bool aRxSUGobWh = false;
      bool dGKgVLWVlB = false;
      bool eiBGKWxKXb = false;
      bool rrRrbTWtgQ = false;
      bool ZZJueGidLB = false;
      bool nZgUOrQqHx = false;
      bool IdEtolnSEB = false;
      bool oboUaEYGaE = false;
      bool mSyWnSKwcj = false;
      bool DemiHuVPFr = false;
      bool RQYKLLjLsK = false;
      bool SKPDJoegGW = false;
      bool bqpUyJoGNe = false;
      bool iJAimWsnLc = false;
      bool hyDSQrPiYR = false;
      bool QnJiQZaEMB = false;
      bool VdyOaJJgQm = false;
      bool uqVdncnXDF = false;
      bool tGguOtARRN = false;
      bool wobJGDAnqH = false;
      string nrJzaDfsKO;
      string JgBNhuVuiJ;
      string rjzzLVtyfa;
      string tVXbcplOYB;
      string CdbOSkttWz;
      string UKrBaErKnE;
      string IgNjTmJZkr;
      string JHWgHNHkfZ;
      string aAafFjdWAX;
      string xaaTsUPrtf;
      string bTJepMnKtN;
      string xGeNdHFhdj;
      string ImZMthgDml;
      string xPqAyGpwos;
      string wTblapwMol;
      string PhNKWotwkH;
      string fkXIQgPdPW;
      string QJrkmoKmlD;
      string lTNBWPCgcI;
      string MtLhMLwSVt;
      if(nrJzaDfsKO == bTJepMnKtN){aRxSUGobWh = true;}
      else if(bTJepMnKtN == nrJzaDfsKO){RQYKLLjLsK = true;}
      if(JgBNhuVuiJ == xGeNdHFhdj){dGKgVLWVlB = true;}
      else if(xGeNdHFhdj == JgBNhuVuiJ){SKPDJoegGW = true;}
      if(rjzzLVtyfa == ImZMthgDml){eiBGKWxKXb = true;}
      else if(ImZMthgDml == rjzzLVtyfa){bqpUyJoGNe = true;}
      if(tVXbcplOYB == xPqAyGpwos){rrRrbTWtgQ = true;}
      else if(xPqAyGpwos == tVXbcplOYB){iJAimWsnLc = true;}
      if(CdbOSkttWz == wTblapwMol){ZZJueGidLB = true;}
      else if(wTblapwMol == CdbOSkttWz){hyDSQrPiYR = true;}
      if(UKrBaErKnE == PhNKWotwkH){nZgUOrQqHx = true;}
      else if(PhNKWotwkH == UKrBaErKnE){QnJiQZaEMB = true;}
      if(IgNjTmJZkr == fkXIQgPdPW){IdEtolnSEB = true;}
      else if(fkXIQgPdPW == IgNjTmJZkr){VdyOaJJgQm = true;}
      if(JHWgHNHkfZ == QJrkmoKmlD){oboUaEYGaE = true;}
      if(aAafFjdWAX == lTNBWPCgcI){mSyWnSKwcj = true;}
      if(xaaTsUPrtf == MtLhMLwSVt){DemiHuVPFr = true;}
      while(QJrkmoKmlD == JHWgHNHkfZ){uqVdncnXDF = true;}
      while(lTNBWPCgcI == lTNBWPCgcI){tGguOtARRN = true;}
      while(MtLhMLwSVt == MtLhMLwSVt){wobJGDAnqH = true;}
      if(aRxSUGobWh == true){aRxSUGobWh = false;}
      if(dGKgVLWVlB == true){dGKgVLWVlB = false;}
      if(eiBGKWxKXb == true){eiBGKWxKXb = false;}
      if(rrRrbTWtgQ == true){rrRrbTWtgQ = false;}
      if(ZZJueGidLB == true){ZZJueGidLB = false;}
      if(nZgUOrQqHx == true){nZgUOrQqHx = false;}
      if(IdEtolnSEB == true){IdEtolnSEB = false;}
      if(oboUaEYGaE == true){oboUaEYGaE = false;}
      if(mSyWnSKwcj == true){mSyWnSKwcj = false;}
      if(DemiHuVPFr == true){DemiHuVPFr = false;}
      if(RQYKLLjLsK == true){RQYKLLjLsK = false;}
      if(SKPDJoegGW == true){SKPDJoegGW = false;}
      if(bqpUyJoGNe == true){bqpUyJoGNe = false;}
      if(iJAimWsnLc == true){iJAimWsnLc = false;}
      if(hyDSQrPiYR == true){hyDSQrPiYR = false;}
      if(QnJiQZaEMB == true){QnJiQZaEMB = false;}
      if(VdyOaJJgQm == true){VdyOaJJgQm = false;}
      if(uqVdncnXDF == true){uqVdncnXDF = false;}
      if(tGguOtARRN == true){tGguOtARRN = false;}
      if(wobJGDAnqH == true){wobJGDAnqH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KSSNUXUBXK
{ 
  void FuQZONYnCz()
  { 
      bool JMVpAfxAEt = false;
      bool ieTQPVoWKt = false;
      bool ysTLoIoPRR = false;
      bool bWaLeUOCRU = false;
      bool NepzxIlpDY = false;
      bool qjNZFPrKBq = false;
      bool philRLDHku = false;
      bool HlFpgSDUNf = false;
      bool WyMrarJAGP = false;
      bool bDBZefwDgl = false;
      bool FeFHQEeWsm = false;
      bool MXxUUqUpLZ = false;
      bool BDBVSEkeLA = false;
      bool WznaarsEaW = false;
      bool NlGSCEGfEm = false;
      bool KFrHjBcinM = false;
      bool SzLrPMjVtc = false;
      bool yQPoLPwhSO = false;
      bool xFZXpQHfqY = false;
      bool OJPNDNZNDp = false;
      string OjBIKtjFwp;
      string qpmFynBlAV;
      string QUpllGPTnZ;
      string XriqzcXmPy;
      string EuyfHQsoNU;
      string SQYISstOWE;
      string eQRVSyGuFU;
      string QNWBRVVJeU;
      string MZFTGHTaYG;
      string iJPKTmdcNI;
      string JyjrDEsWpx;
      string XkiCqEKyOL;
      string efWzlHyLgd;
      string qswVKOpNPC;
      string NwjaixZNSO;
      string cfNBcdajFw;
      string GhoLFdnMqc;
      string OxhMxiuwQo;
      string gjrSBLftsf;
      string nFHSufGXUE;
      if(OjBIKtjFwp == JyjrDEsWpx){JMVpAfxAEt = true;}
      else if(JyjrDEsWpx == OjBIKtjFwp){FeFHQEeWsm = true;}
      if(qpmFynBlAV == XkiCqEKyOL){ieTQPVoWKt = true;}
      else if(XkiCqEKyOL == qpmFynBlAV){MXxUUqUpLZ = true;}
      if(QUpllGPTnZ == efWzlHyLgd){ysTLoIoPRR = true;}
      else if(efWzlHyLgd == QUpllGPTnZ){BDBVSEkeLA = true;}
      if(XriqzcXmPy == qswVKOpNPC){bWaLeUOCRU = true;}
      else if(qswVKOpNPC == XriqzcXmPy){WznaarsEaW = true;}
      if(EuyfHQsoNU == NwjaixZNSO){NepzxIlpDY = true;}
      else if(NwjaixZNSO == EuyfHQsoNU){NlGSCEGfEm = true;}
      if(SQYISstOWE == cfNBcdajFw){qjNZFPrKBq = true;}
      else if(cfNBcdajFw == SQYISstOWE){KFrHjBcinM = true;}
      if(eQRVSyGuFU == GhoLFdnMqc){philRLDHku = true;}
      else if(GhoLFdnMqc == eQRVSyGuFU){SzLrPMjVtc = true;}
      if(QNWBRVVJeU == OxhMxiuwQo){HlFpgSDUNf = true;}
      if(MZFTGHTaYG == gjrSBLftsf){WyMrarJAGP = true;}
      if(iJPKTmdcNI == nFHSufGXUE){bDBZefwDgl = true;}
      while(OxhMxiuwQo == QNWBRVVJeU){yQPoLPwhSO = true;}
      while(gjrSBLftsf == gjrSBLftsf){xFZXpQHfqY = true;}
      while(nFHSufGXUE == nFHSufGXUE){OJPNDNZNDp = true;}
      if(JMVpAfxAEt == true){JMVpAfxAEt = false;}
      if(ieTQPVoWKt == true){ieTQPVoWKt = false;}
      if(ysTLoIoPRR == true){ysTLoIoPRR = false;}
      if(bWaLeUOCRU == true){bWaLeUOCRU = false;}
      if(NepzxIlpDY == true){NepzxIlpDY = false;}
      if(qjNZFPrKBq == true){qjNZFPrKBq = false;}
      if(philRLDHku == true){philRLDHku = false;}
      if(HlFpgSDUNf == true){HlFpgSDUNf = false;}
      if(WyMrarJAGP == true){WyMrarJAGP = false;}
      if(bDBZefwDgl == true){bDBZefwDgl = false;}
      if(FeFHQEeWsm == true){FeFHQEeWsm = false;}
      if(MXxUUqUpLZ == true){MXxUUqUpLZ = false;}
      if(BDBVSEkeLA == true){BDBVSEkeLA = false;}
      if(WznaarsEaW == true){WznaarsEaW = false;}
      if(NlGSCEGfEm == true){NlGSCEGfEm = false;}
      if(KFrHjBcinM == true){KFrHjBcinM = false;}
      if(SzLrPMjVtc == true){SzLrPMjVtc = false;}
      if(yQPoLPwhSO == true){yQPoLPwhSO = false;}
      if(xFZXpQHfqY == true){xFZXpQHfqY = false;}
      if(OJPNDNZNDp == true){OJPNDNZNDp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PTTKVNLTES
{ 
  void ZYySQqZKit()
  { 
      bool wgHIuQZJQC = false;
      bool MbzuTeFNKe = false;
      bool BDQEFtKqHw = false;
      bool HNtkSZHmYu = false;
      bool escyrWZYRO = false;
      bool JCDIFsPDDA = false;
      bool FiCUuzhObs = false;
      bool XRnOAIZSLh = false;
      bool UlYrlEJkeZ = false;
      bool JDjXoupICs = false;
      bool oLwYqqOnHx = false;
      bool SxqUfTKJhq = false;
      bool owjCiThQYF = false;
      bool RQPRrIoAAt = false;
      bool pVcgGMMPrU = false;
      bool kfaKEsbsoX = false;
      bool JxOCfCgYbW = false;
      bool dKJmBTSCuW = false;
      bool GSXETkpENz = false;
      bool gwKckrGaBE = false;
      string qjWPDpDTra;
      string xcmqkOUAgc;
      string lMlESPrrgp;
      string WNDOIMMSPy;
      string PhAIfYoerj;
      string cuzpxdySxn;
      string yKmBDiYYiX;
      string BCkiMDLcYs;
      string ZMAwNaNNRd;
      string OtVbAFtyFw;
      string zQwUiZKPcs;
      string RUtDNkKqnb;
      string VLGEJHgJiG;
      string INXbsJQfNm;
      string QxjYLszRNO;
      string uDKcanJqLa;
      string sBgVjExRJE;
      string TecALXahrP;
      string HOuTLFCtBF;
      string zYUlsPQNnH;
      if(qjWPDpDTra == zQwUiZKPcs){wgHIuQZJQC = true;}
      else if(zQwUiZKPcs == qjWPDpDTra){oLwYqqOnHx = true;}
      if(xcmqkOUAgc == RUtDNkKqnb){MbzuTeFNKe = true;}
      else if(RUtDNkKqnb == xcmqkOUAgc){SxqUfTKJhq = true;}
      if(lMlESPrrgp == VLGEJHgJiG){BDQEFtKqHw = true;}
      else if(VLGEJHgJiG == lMlESPrrgp){owjCiThQYF = true;}
      if(WNDOIMMSPy == INXbsJQfNm){HNtkSZHmYu = true;}
      else if(INXbsJQfNm == WNDOIMMSPy){RQPRrIoAAt = true;}
      if(PhAIfYoerj == QxjYLszRNO){escyrWZYRO = true;}
      else if(QxjYLszRNO == PhAIfYoerj){pVcgGMMPrU = true;}
      if(cuzpxdySxn == uDKcanJqLa){JCDIFsPDDA = true;}
      else if(uDKcanJqLa == cuzpxdySxn){kfaKEsbsoX = true;}
      if(yKmBDiYYiX == sBgVjExRJE){FiCUuzhObs = true;}
      else if(sBgVjExRJE == yKmBDiYYiX){JxOCfCgYbW = true;}
      if(BCkiMDLcYs == TecALXahrP){XRnOAIZSLh = true;}
      if(ZMAwNaNNRd == HOuTLFCtBF){UlYrlEJkeZ = true;}
      if(OtVbAFtyFw == zYUlsPQNnH){JDjXoupICs = true;}
      while(TecALXahrP == BCkiMDLcYs){dKJmBTSCuW = true;}
      while(HOuTLFCtBF == HOuTLFCtBF){GSXETkpENz = true;}
      while(zYUlsPQNnH == zYUlsPQNnH){gwKckrGaBE = true;}
      if(wgHIuQZJQC == true){wgHIuQZJQC = false;}
      if(MbzuTeFNKe == true){MbzuTeFNKe = false;}
      if(BDQEFtKqHw == true){BDQEFtKqHw = false;}
      if(HNtkSZHmYu == true){HNtkSZHmYu = false;}
      if(escyrWZYRO == true){escyrWZYRO = false;}
      if(JCDIFsPDDA == true){JCDIFsPDDA = false;}
      if(FiCUuzhObs == true){FiCUuzhObs = false;}
      if(XRnOAIZSLh == true){XRnOAIZSLh = false;}
      if(UlYrlEJkeZ == true){UlYrlEJkeZ = false;}
      if(JDjXoupICs == true){JDjXoupICs = false;}
      if(oLwYqqOnHx == true){oLwYqqOnHx = false;}
      if(SxqUfTKJhq == true){SxqUfTKJhq = false;}
      if(owjCiThQYF == true){owjCiThQYF = false;}
      if(RQPRrIoAAt == true){RQPRrIoAAt = false;}
      if(pVcgGMMPrU == true){pVcgGMMPrU = false;}
      if(kfaKEsbsoX == true){kfaKEsbsoX = false;}
      if(JxOCfCgYbW == true){JxOCfCgYbW = false;}
      if(dKJmBTSCuW == true){dKJmBTSCuW = false;}
      if(GSXETkpENz == true){GSXETkpENz = false;}
      if(gwKckrGaBE == true){gwKckrGaBE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DABZRXGFKF
{ 
  void EJhhCjfcMt()
  { 
      bool wJdfosQnAZ = false;
      bool UjlRZWuHwY = false;
      bool fwbXQzgtZS = false;
      bool caGcHCTkKX = false;
      bool XBJscdYCrg = false;
      bool ddwcmAhGOp = false;
      bool LVNhwtcJJX = false;
      bool CJxYAdmhtl = false;
      bool ZeBsnzddoH = false;
      bool TNVULCnbwi = false;
      bool APrUdTfXbI = false;
      bool MzLbPgTUsx = false;
      bool PzTCDnncMy = false;
      bool pLkLlKlgOU = false;
      bool SGBgtTBsEd = false;
      bool hShzTBwpQo = false;
      bool eDLcRBNApF = false;
      bool ulFXeJxlHi = false;
      bool ltXhPWclrj = false;
      bool NwQYoOuXOr = false;
      string DJGrPCXASe;
      string PQGiyeebXw;
      string cujCeGlMdW;
      string gJGmciJWET;
      string yQRQBajZsX;
      string cJKYqIZDMI;
      string PLWwyGJSGP;
      string VIWDyLcSBD;
      string WMTFsWzhuU;
      string IFJwDltUSt;
      string QQTcBUmGZf;
      string eGBIkDrQCa;
      string GbXkGPzazL;
      string RIAGmGspEY;
      string jrHPoCEAKA;
      string tcRqnorhVl;
      string VLHONWFtVe;
      string KBMdqOTIuE;
      string LyQzRnpJSy;
      string NKTRDYksBS;
      if(DJGrPCXASe == QQTcBUmGZf){wJdfosQnAZ = true;}
      else if(QQTcBUmGZf == DJGrPCXASe){APrUdTfXbI = true;}
      if(PQGiyeebXw == eGBIkDrQCa){UjlRZWuHwY = true;}
      else if(eGBIkDrQCa == PQGiyeebXw){MzLbPgTUsx = true;}
      if(cujCeGlMdW == GbXkGPzazL){fwbXQzgtZS = true;}
      else if(GbXkGPzazL == cujCeGlMdW){PzTCDnncMy = true;}
      if(gJGmciJWET == RIAGmGspEY){caGcHCTkKX = true;}
      else if(RIAGmGspEY == gJGmciJWET){pLkLlKlgOU = true;}
      if(yQRQBajZsX == jrHPoCEAKA){XBJscdYCrg = true;}
      else if(jrHPoCEAKA == yQRQBajZsX){SGBgtTBsEd = true;}
      if(cJKYqIZDMI == tcRqnorhVl){ddwcmAhGOp = true;}
      else if(tcRqnorhVl == cJKYqIZDMI){hShzTBwpQo = true;}
      if(PLWwyGJSGP == VLHONWFtVe){LVNhwtcJJX = true;}
      else if(VLHONWFtVe == PLWwyGJSGP){eDLcRBNApF = true;}
      if(VIWDyLcSBD == KBMdqOTIuE){CJxYAdmhtl = true;}
      if(WMTFsWzhuU == LyQzRnpJSy){ZeBsnzddoH = true;}
      if(IFJwDltUSt == NKTRDYksBS){TNVULCnbwi = true;}
      while(KBMdqOTIuE == VIWDyLcSBD){ulFXeJxlHi = true;}
      while(LyQzRnpJSy == LyQzRnpJSy){ltXhPWclrj = true;}
      while(NKTRDYksBS == NKTRDYksBS){NwQYoOuXOr = true;}
      if(wJdfosQnAZ == true){wJdfosQnAZ = false;}
      if(UjlRZWuHwY == true){UjlRZWuHwY = false;}
      if(fwbXQzgtZS == true){fwbXQzgtZS = false;}
      if(caGcHCTkKX == true){caGcHCTkKX = false;}
      if(XBJscdYCrg == true){XBJscdYCrg = false;}
      if(ddwcmAhGOp == true){ddwcmAhGOp = false;}
      if(LVNhwtcJJX == true){LVNhwtcJJX = false;}
      if(CJxYAdmhtl == true){CJxYAdmhtl = false;}
      if(ZeBsnzddoH == true){ZeBsnzddoH = false;}
      if(TNVULCnbwi == true){TNVULCnbwi = false;}
      if(APrUdTfXbI == true){APrUdTfXbI = false;}
      if(MzLbPgTUsx == true){MzLbPgTUsx = false;}
      if(PzTCDnncMy == true){PzTCDnncMy = false;}
      if(pLkLlKlgOU == true){pLkLlKlgOU = false;}
      if(SGBgtTBsEd == true){SGBgtTBsEd = false;}
      if(hShzTBwpQo == true){hShzTBwpQo = false;}
      if(eDLcRBNApF == true){eDLcRBNApF = false;}
      if(ulFXeJxlHi == true){ulFXeJxlHi = false;}
      if(ltXhPWclrj == true){ltXhPWclrj = false;}
      if(NwQYoOuXOr == true){NwQYoOuXOr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BRYODJPOHG
{ 
  void zzHmglVMfO()
  { 
      bool fSLAuGTsCi = false;
      bool DPKqYQmUHD = false;
      bool IlZLEZqQNW = false;
      bool FpceLUPyYL = false;
      bool DMnKhDjpuH = false;
      bool sfZGgsszwV = false;
      bool PCfedNmfeD = false;
      bool AnuuzuxOdB = false;
      bool oAVFcZPWxS = false;
      bool bQCDwBgIgU = false;
      bool QEKqGEjdGl = false;
      bool udVufOfZCE = false;
      bool xPhMbjlrzy = false;
      bool OohIkkodzY = false;
      bool olPLWyuHWg = false;
      bool UGGbXAVyPW = false;
      bool RqeIWGuMKt = false;
      bool ZCacOLAWpc = false;
      bool oeVRcIhFkk = false;
      bool PqNcGyGGnP = false;
      string GrjQrlEMQd;
      string wfKBKZEIfY;
      string OowNluMPXY;
      string elUuWcKzRj;
      string HNXZuRshQC;
      string gBVoFRuVex;
      string YnoryKKPdh;
      string PFqwQBQWST;
      string BdzUqcPeoF;
      string goUTKTYfaj;
      string GdEimbJZXD;
      string AYCLutnTAV;
      string ueZYAZjXkx;
      string ckuiMXZPhP;
      string SoHlEIlJYQ;
      string eFeEoaEeiM;
      string qloZaOcTyX;
      string UYlkCFXnUq;
      string nazUSWGptl;
      string TtgUXfAhKo;
      if(GrjQrlEMQd == GdEimbJZXD){fSLAuGTsCi = true;}
      else if(GdEimbJZXD == GrjQrlEMQd){QEKqGEjdGl = true;}
      if(wfKBKZEIfY == AYCLutnTAV){DPKqYQmUHD = true;}
      else if(AYCLutnTAV == wfKBKZEIfY){udVufOfZCE = true;}
      if(OowNluMPXY == ueZYAZjXkx){IlZLEZqQNW = true;}
      else if(ueZYAZjXkx == OowNluMPXY){xPhMbjlrzy = true;}
      if(elUuWcKzRj == ckuiMXZPhP){FpceLUPyYL = true;}
      else if(ckuiMXZPhP == elUuWcKzRj){OohIkkodzY = true;}
      if(HNXZuRshQC == SoHlEIlJYQ){DMnKhDjpuH = true;}
      else if(SoHlEIlJYQ == HNXZuRshQC){olPLWyuHWg = true;}
      if(gBVoFRuVex == eFeEoaEeiM){sfZGgsszwV = true;}
      else if(eFeEoaEeiM == gBVoFRuVex){UGGbXAVyPW = true;}
      if(YnoryKKPdh == qloZaOcTyX){PCfedNmfeD = true;}
      else if(qloZaOcTyX == YnoryKKPdh){RqeIWGuMKt = true;}
      if(PFqwQBQWST == UYlkCFXnUq){AnuuzuxOdB = true;}
      if(BdzUqcPeoF == nazUSWGptl){oAVFcZPWxS = true;}
      if(goUTKTYfaj == TtgUXfAhKo){bQCDwBgIgU = true;}
      while(UYlkCFXnUq == PFqwQBQWST){ZCacOLAWpc = true;}
      while(nazUSWGptl == nazUSWGptl){oeVRcIhFkk = true;}
      while(TtgUXfAhKo == TtgUXfAhKo){PqNcGyGGnP = true;}
      if(fSLAuGTsCi == true){fSLAuGTsCi = false;}
      if(DPKqYQmUHD == true){DPKqYQmUHD = false;}
      if(IlZLEZqQNW == true){IlZLEZqQNW = false;}
      if(FpceLUPyYL == true){FpceLUPyYL = false;}
      if(DMnKhDjpuH == true){DMnKhDjpuH = false;}
      if(sfZGgsszwV == true){sfZGgsszwV = false;}
      if(PCfedNmfeD == true){PCfedNmfeD = false;}
      if(AnuuzuxOdB == true){AnuuzuxOdB = false;}
      if(oAVFcZPWxS == true){oAVFcZPWxS = false;}
      if(bQCDwBgIgU == true){bQCDwBgIgU = false;}
      if(QEKqGEjdGl == true){QEKqGEjdGl = false;}
      if(udVufOfZCE == true){udVufOfZCE = false;}
      if(xPhMbjlrzy == true){xPhMbjlrzy = false;}
      if(OohIkkodzY == true){OohIkkodzY = false;}
      if(olPLWyuHWg == true){olPLWyuHWg = false;}
      if(UGGbXAVyPW == true){UGGbXAVyPW = false;}
      if(RqeIWGuMKt == true){RqeIWGuMKt = false;}
      if(ZCacOLAWpc == true){ZCacOLAWpc = false;}
      if(oeVRcIhFkk == true){oeVRcIhFkk = false;}
      if(PqNcGyGGnP == true){PqNcGyGGnP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NTQCWDTEXW
{ 
  void EIQWuScPNg()
  { 
      bool ZxxSFdQdnd = false;
      bool ykzWzmJylg = false;
      bool KjarFULDiS = false;
      bool lIdUSiUGty = false;
      bool fHWqVbsWQn = false;
      bool bVSkCoVFMj = false;
      bool SMuVqpGeEQ = false;
      bool SCEnACMjWc = false;
      bool bnmuqPpsSc = false;
      bool NOtJfSMBzf = false;
      bool VNSAVYRejz = false;
      bool ckijIeYzea = false;
      bool zMMaCDItHh = false;
      bool oKkpGNVmZR = false;
      bool yLJSAbfJAB = false;
      bool sNWXfIBqxS = false;
      bool QWWBJRArcu = false;
      bool IlZNcnDsZa = false;
      bool WysGnbnNKy = false;
      bool LdoHAaoHJi = false;
      string exQfOcICsH;
      string qcxhbrKlVX;
      string HzbsIjpDhj;
      string TetALrUbbt;
      string HWqFYeTsNd;
      string REstufVWXd;
      string lFUJnMiwVj;
      string XhJbPjIVTc;
      string QxoDRPkzFf;
      string VxEyIBCgRM;
      string wWWdGjtRdK;
      string XADtMnQQrY;
      string aippNZdLSN;
      string haEGgtZKwg;
      string UTUtIVsKkT;
      string kkorlMggPf;
      string GiyPcwwwMS;
      string NGUKEHNugr;
      string fSZzcwlLUU;
      string NstQakUFRM;
      if(exQfOcICsH == wWWdGjtRdK){ZxxSFdQdnd = true;}
      else if(wWWdGjtRdK == exQfOcICsH){VNSAVYRejz = true;}
      if(qcxhbrKlVX == XADtMnQQrY){ykzWzmJylg = true;}
      else if(XADtMnQQrY == qcxhbrKlVX){ckijIeYzea = true;}
      if(HzbsIjpDhj == aippNZdLSN){KjarFULDiS = true;}
      else if(aippNZdLSN == HzbsIjpDhj){zMMaCDItHh = true;}
      if(TetALrUbbt == haEGgtZKwg){lIdUSiUGty = true;}
      else if(haEGgtZKwg == TetALrUbbt){oKkpGNVmZR = true;}
      if(HWqFYeTsNd == UTUtIVsKkT){fHWqVbsWQn = true;}
      else if(UTUtIVsKkT == HWqFYeTsNd){yLJSAbfJAB = true;}
      if(REstufVWXd == kkorlMggPf){bVSkCoVFMj = true;}
      else if(kkorlMggPf == REstufVWXd){sNWXfIBqxS = true;}
      if(lFUJnMiwVj == GiyPcwwwMS){SMuVqpGeEQ = true;}
      else if(GiyPcwwwMS == lFUJnMiwVj){QWWBJRArcu = true;}
      if(XhJbPjIVTc == NGUKEHNugr){SCEnACMjWc = true;}
      if(QxoDRPkzFf == fSZzcwlLUU){bnmuqPpsSc = true;}
      if(VxEyIBCgRM == NstQakUFRM){NOtJfSMBzf = true;}
      while(NGUKEHNugr == XhJbPjIVTc){IlZNcnDsZa = true;}
      while(fSZzcwlLUU == fSZzcwlLUU){WysGnbnNKy = true;}
      while(NstQakUFRM == NstQakUFRM){LdoHAaoHJi = true;}
      if(ZxxSFdQdnd == true){ZxxSFdQdnd = false;}
      if(ykzWzmJylg == true){ykzWzmJylg = false;}
      if(KjarFULDiS == true){KjarFULDiS = false;}
      if(lIdUSiUGty == true){lIdUSiUGty = false;}
      if(fHWqVbsWQn == true){fHWqVbsWQn = false;}
      if(bVSkCoVFMj == true){bVSkCoVFMj = false;}
      if(SMuVqpGeEQ == true){SMuVqpGeEQ = false;}
      if(SCEnACMjWc == true){SCEnACMjWc = false;}
      if(bnmuqPpsSc == true){bnmuqPpsSc = false;}
      if(NOtJfSMBzf == true){NOtJfSMBzf = false;}
      if(VNSAVYRejz == true){VNSAVYRejz = false;}
      if(ckijIeYzea == true){ckijIeYzea = false;}
      if(zMMaCDItHh == true){zMMaCDItHh = false;}
      if(oKkpGNVmZR == true){oKkpGNVmZR = false;}
      if(yLJSAbfJAB == true){yLJSAbfJAB = false;}
      if(sNWXfIBqxS == true){sNWXfIBqxS = false;}
      if(QWWBJRArcu == true){QWWBJRArcu = false;}
      if(IlZNcnDsZa == true){IlZNcnDsZa = false;}
      if(WysGnbnNKy == true){WysGnbnNKy = false;}
      if(LdoHAaoHJi == true){LdoHAaoHJi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YWSHUPIDRD
{ 
  void djrLgaQlaT()
  { 
      bool iFQqjgqFeh = false;
      bool ELFwqtuekB = false;
      bool sNAYhLUrWo = false;
      bool IOLOGNslWa = false;
      bool FhBTVrpNwV = false;
      bool myZziVEqJY = false;
      bool LyhpZozpod = false;
      bool BIIJwLMfCo = false;
      bool VGwACJoMek = false;
      bool IBcyPGzKtg = false;
      bool szXSUdpPCX = false;
      bool JXoUCECgmP = false;
      bool zlKEVAfKtp = false;
      bool LBlVuVidfX = false;
      bool TYKHbjLIuK = false;
      bool DSWegGnTxU = false;
      bool yfVMMIlTYf = false;
      bool VXBPuabDbk = false;
      bool nWOilrdHno = false;
      bool hOgLZnDxuT = false;
      string rKkwGJKsZn;
      string SqnBUQiTRd;
      string hsRPadTegT;
      string TSqHYxEpUe;
      string UMIBVKQbcx;
      string VfUXozsUVb;
      string peLGTzzfbW;
      string LszlJUjQtQ;
      string NqCixnxTSZ;
      string EjTrooAChW;
      string KkzFlcfiOT;
      string ObaEOyccIe;
      string BfMCSbYHxU;
      string UgiXFcrxxU;
      string HOFzKbIPcp;
      string MXsCUeXxmJ;
      string DYksyhsDzl;
      string GefnXlaMqp;
      string SJdGIxnfCa;
      string EuKmQhdLAc;
      if(rKkwGJKsZn == KkzFlcfiOT){iFQqjgqFeh = true;}
      else if(KkzFlcfiOT == rKkwGJKsZn){szXSUdpPCX = true;}
      if(SqnBUQiTRd == ObaEOyccIe){ELFwqtuekB = true;}
      else if(ObaEOyccIe == SqnBUQiTRd){JXoUCECgmP = true;}
      if(hsRPadTegT == BfMCSbYHxU){sNAYhLUrWo = true;}
      else if(BfMCSbYHxU == hsRPadTegT){zlKEVAfKtp = true;}
      if(TSqHYxEpUe == UgiXFcrxxU){IOLOGNslWa = true;}
      else if(UgiXFcrxxU == TSqHYxEpUe){LBlVuVidfX = true;}
      if(UMIBVKQbcx == HOFzKbIPcp){FhBTVrpNwV = true;}
      else if(HOFzKbIPcp == UMIBVKQbcx){TYKHbjLIuK = true;}
      if(VfUXozsUVb == MXsCUeXxmJ){myZziVEqJY = true;}
      else if(MXsCUeXxmJ == VfUXozsUVb){DSWegGnTxU = true;}
      if(peLGTzzfbW == DYksyhsDzl){LyhpZozpod = true;}
      else if(DYksyhsDzl == peLGTzzfbW){yfVMMIlTYf = true;}
      if(LszlJUjQtQ == GefnXlaMqp){BIIJwLMfCo = true;}
      if(NqCixnxTSZ == SJdGIxnfCa){VGwACJoMek = true;}
      if(EjTrooAChW == EuKmQhdLAc){IBcyPGzKtg = true;}
      while(GefnXlaMqp == LszlJUjQtQ){VXBPuabDbk = true;}
      while(SJdGIxnfCa == SJdGIxnfCa){nWOilrdHno = true;}
      while(EuKmQhdLAc == EuKmQhdLAc){hOgLZnDxuT = true;}
      if(iFQqjgqFeh == true){iFQqjgqFeh = false;}
      if(ELFwqtuekB == true){ELFwqtuekB = false;}
      if(sNAYhLUrWo == true){sNAYhLUrWo = false;}
      if(IOLOGNslWa == true){IOLOGNslWa = false;}
      if(FhBTVrpNwV == true){FhBTVrpNwV = false;}
      if(myZziVEqJY == true){myZziVEqJY = false;}
      if(LyhpZozpod == true){LyhpZozpod = false;}
      if(BIIJwLMfCo == true){BIIJwLMfCo = false;}
      if(VGwACJoMek == true){VGwACJoMek = false;}
      if(IBcyPGzKtg == true){IBcyPGzKtg = false;}
      if(szXSUdpPCX == true){szXSUdpPCX = false;}
      if(JXoUCECgmP == true){JXoUCECgmP = false;}
      if(zlKEVAfKtp == true){zlKEVAfKtp = false;}
      if(LBlVuVidfX == true){LBlVuVidfX = false;}
      if(TYKHbjLIuK == true){TYKHbjLIuK = false;}
      if(DSWegGnTxU == true){DSWegGnTxU = false;}
      if(yfVMMIlTYf == true){yfVMMIlTYf = false;}
      if(VXBPuabDbk == true){VXBPuabDbk = false;}
      if(nWOilrdHno == true){nWOilrdHno = false;}
      if(hOgLZnDxuT == true){hOgLZnDxuT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFPBTTDDJN
{ 
  void pdDrnKyGSj()
  { 
      bool ZQZFAPXCoE = false;
      bool ipnkzrsgeE = false;
      bool mmByqMrRaF = false;
      bool rBidaqMFoW = false;
      bool CbLJApdbPz = false;
      bool OgiiRmPbOn = false;
      bool WFbiLhGKJI = false;
      bool emrIBKbryA = false;
      bool hQCaqLRAMn = false;
      bool akqAAxAbxR = false;
      bool jSSGTanagG = false;
      bool LXcNGFDArA = false;
      bool QGxVhtwrHE = false;
      bool KztfQOywHP = false;
      bool WpSFbCHctt = false;
      bool tzixBcUxXZ = false;
      bool dwTcuLdxxq = false;
      bool HGsbdamqse = false;
      bool lTyNJLPxdm = false;
      bool sBXglZWpKP = false;
      string lDUiTmhsoD;
      string RToPuoBkNQ;
      string UJgEiJwZVA;
      string btPZSahbDq;
      string hgzCbCPbXC;
      string BYPIycVPAK;
      string pHXobXEPwU;
      string GYgWhnKecg;
      string sUCTzCeGbp;
      string ESbsAaIKaE;
      string xAeCwbqsZJ;
      string SqmSQUFEoY;
      string sxnGPnwmVH;
      string eADYjspzWW;
      string LlgRXNfJcf;
      string UEUCLzMXmH;
      string fDWReSmOiX;
      string eFgRNGQViB;
      string ImKplZeANj;
      string gSMOqHOOmE;
      if(lDUiTmhsoD == xAeCwbqsZJ){ZQZFAPXCoE = true;}
      else if(xAeCwbqsZJ == lDUiTmhsoD){jSSGTanagG = true;}
      if(RToPuoBkNQ == SqmSQUFEoY){ipnkzrsgeE = true;}
      else if(SqmSQUFEoY == RToPuoBkNQ){LXcNGFDArA = true;}
      if(UJgEiJwZVA == sxnGPnwmVH){mmByqMrRaF = true;}
      else if(sxnGPnwmVH == UJgEiJwZVA){QGxVhtwrHE = true;}
      if(btPZSahbDq == eADYjspzWW){rBidaqMFoW = true;}
      else if(eADYjspzWW == btPZSahbDq){KztfQOywHP = true;}
      if(hgzCbCPbXC == LlgRXNfJcf){CbLJApdbPz = true;}
      else if(LlgRXNfJcf == hgzCbCPbXC){WpSFbCHctt = true;}
      if(BYPIycVPAK == UEUCLzMXmH){OgiiRmPbOn = true;}
      else if(UEUCLzMXmH == BYPIycVPAK){tzixBcUxXZ = true;}
      if(pHXobXEPwU == fDWReSmOiX){WFbiLhGKJI = true;}
      else if(fDWReSmOiX == pHXobXEPwU){dwTcuLdxxq = true;}
      if(GYgWhnKecg == eFgRNGQViB){emrIBKbryA = true;}
      if(sUCTzCeGbp == ImKplZeANj){hQCaqLRAMn = true;}
      if(ESbsAaIKaE == gSMOqHOOmE){akqAAxAbxR = true;}
      while(eFgRNGQViB == GYgWhnKecg){HGsbdamqse = true;}
      while(ImKplZeANj == ImKplZeANj){lTyNJLPxdm = true;}
      while(gSMOqHOOmE == gSMOqHOOmE){sBXglZWpKP = true;}
      if(ZQZFAPXCoE == true){ZQZFAPXCoE = false;}
      if(ipnkzrsgeE == true){ipnkzrsgeE = false;}
      if(mmByqMrRaF == true){mmByqMrRaF = false;}
      if(rBidaqMFoW == true){rBidaqMFoW = false;}
      if(CbLJApdbPz == true){CbLJApdbPz = false;}
      if(OgiiRmPbOn == true){OgiiRmPbOn = false;}
      if(WFbiLhGKJI == true){WFbiLhGKJI = false;}
      if(emrIBKbryA == true){emrIBKbryA = false;}
      if(hQCaqLRAMn == true){hQCaqLRAMn = false;}
      if(akqAAxAbxR == true){akqAAxAbxR = false;}
      if(jSSGTanagG == true){jSSGTanagG = false;}
      if(LXcNGFDArA == true){LXcNGFDArA = false;}
      if(QGxVhtwrHE == true){QGxVhtwrHE = false;}
      if(KztfQOywHP == true){KztfQOywHP = false;}
      if(WpSFbCHctt == true){WpSFbCHctt = false;}
      if(tzixBcUxXZ == true){tzixBcUxXZ = false;}
      if(dwTcuLdxxq == true){dwTcuLdxxq = false;}
      if(HGsbdamqse == true){HGsbdamqse = false;}
      if(lTyNJLPxdm == true){lTyNJLPxdm = false;}
      if(sBXglZWpKP == true){sBXglZWpKP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QXIHAMERKD
{ 
  void lGsknVRmru()
  { 
      bool SQyVLmCUbT = false;
      bool nhFHYxYCZU = false;
      bool COYHPGHwQd = false;
      bool ufiEkcLdmR = false;
      bool NCLQSiHQBq = false;
      bool RSwBbDqqGF = false;
      bool fFDxYIzBWu = false;
      bool luOIGzCHof = false;
      bool zptYMbigbg = false;
      bool kTWhkHyOrK = false;
      bool jGtGFVEntc = false;
      bool BjCaGpLekx = false;
      bool YRYpKRXgXz = false;
      bool AnPeuswnSp = false;
      bool WumyeARwat = false;
      bool wTcukRgEun = false;
      bool yWQubNUWeN = false;
      bool tXLtZdeZKJ = false;
      bool zbFcCgKTsd = false;
      bool MqrerAeqWQ = false;
      string galusWOcck;
      string JVeutyVeZT;
      string LgVNszYhjA;
      string LPNldNbZkw;
      string OgFFTCsuPG;
      string ZVKIEzEXCs;
      string xfrcYtIsRg;
      string VutcFdaQtq;
      string FdRcapEEgd;
      string IDXqyhncfZ;
      string tAcijdagCZ;
      string YmdKmTOPCi;
      string oDMnXSWCeX;
      string oykUwFAirw;
      string OXBHFUZMDe;
      string SYawjpmnKR;
      string HXCekZCINg;
      string SeWFUQCFiD;
      string sJzzEPXnjG;
      string RMXaopVWVe;
      if(galusWOcck == tAcijdagCZ){SQyVLmCUbT = true;}
      else if(tAcijdagCZ == galusWOcck){jGtGFVEntc = true;}
      if(JVeutyVeZT == YmdKmTOPCi){nhFHYxYCZU = true;}
      else if(YmdKmTOPCi == JVeutyVeZT){BjCaGpLekx = true;}
      if(LgVNszYhjA == oDMnXSWCeX){COYHPGHwQd = true;}
      else if(oDMnXSWCeX == LgVNszYhjA){YRYpKRXgXz = true;}
      if(LPNldNbZkw == oykUwFAirw){ufiEkcLdmR = true;}
      else if(oykUwFAirw == LPNldNbZkw){AnPeuswnSp = true;}
      if(OgFFTCsuPG == OXBHFUZMDe){NCLQSiHQBq = true;}
      else if(OXBHFUZMDe == OgFFTCsuPG){WumyeARwat = true;}
      if(ZVKIEzEXCs == SYawjpmnKR){RSwBbDqqGF = true;}
      else if(SYawjpmnKR == ZVKIEzEXCs){wTcukRgEun = true;}
      if(xfrcYtIsRg == HXCekZCINg){fFDxYIzBWu = true;}
      else if(HXCekZCINg == xfrcYtIsRg){yWQubNUWeN = true;}
      if(VutcFdaQtq == SeWFUQCFiD){luOIGzCHof = true;}
      if(FdRcapEEgd == sJzzEPXnjG){zptYMbigbg = true;}
      if(IDXqyhncfZ == RMXaopVWVe){kTWhkHyOrK = true;}
      while(SeWFUQCFiD == VutcFdaQtq){tXLtZdeZKJ = true;}
      while(sJzzEPXnjG == sJzzEPXnjG){zbFcCgKTsd = true;}
      while(RMXaopVWVe == RMXaopVWVe){MqrerAeqWQ = true;}
      if(SQyVLmCUbT == true){SQyVLmCUbT = false;}
      if(nhFHYxYCZU == true){nhFHYxYCZU = false;}
      if(COYHPGHwQd == true){COYHPGHwQd = false;}
      if(ufiEkcLdmR == true){ufiEkcLdmR = false;}
      if(NCLQSiHQBq == true){NCLQSiHQBq = false;}
      if(RSwBbDqqGF == true){RSwBbDqqGF = false;}
      if(fFDxYIzBWu == true){fFDxYIzBWu = false;}
      if(luOIGzCHof == true){luOIGzCHof = false;}
      if(zptYMbigbg == true){zptYMbigbg = false;}
      if(kTWhkHyOrK == true){kTWhkHyOrK = false;}
      if(jGtGFVEntc == true){jGtGFVEntc = false;}
      if(BjCaGpLekx == true){BjCaGpLekx = false;}
      if(YRYpKRXgXz == true){YRYpKRXgXz = false;}
      if(AnPeuswnSp == true){AnPeuswnSp = false;}
      if(WumyeARwat == true){WumyeARwat = false;}
      if(wTcukRgEun == true){wTcukRgEun = false;}
      if(yWQubNUWeN == true){yWQubNUWeN = false;}
      if(tXLtZdeZKJ == true){tXLtZdeZKJ = false;}
      if(zbFcCgKTsd == true){zbFcCgKTsd = false;}
      if(MqrerAeqWQ == true){MqrerAeqWQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FNPAEEFPXP
{ 
  void BTfiAAQNwP()
  { 
      bool eeLLgremha = false;
      bool SJdzdchLOC = false;
      bool oWqlPaSuUD = false;
      bool ZPJwHwUYFQ = false;
      bool tuAkuaktmZ = false;
      bool AFlOnInZuG = false;
      bool ZjSdADAgqg = false;
      bool IIFyHsVFpo = false;
      bool oXHuCUctIz = false;
      bool ItcypKbVkq = false;
      bool ZDCGQqznGt = false;
      bool liiGRBbXaf = false;
      bool aGYqYNfHHw = false;
      bool RzUzOkUBdL = false;
      bool VonOMZLVgo = false;
      bool iEuEQTdLgC = false;
      bool KqfJblNjqf = false;
      bool fZsPJkRKey = false;
      bool CJaSNMEPhu = false;
      bool GJUaAdIdlZ = false;
      string nXwipWrJRG;
      string DPASRfoHYl;
      string GgLJIsSLhT;
      string GXKmZDEkdi;
      string bGrEFgSWWr;
      string FryxwGMmZw;
      string DfbyAfFMsN;
      string bDdoKznGEa;
      string awooOOYNqS;
      string pQKgewetEY;
      string bFdJQBNImw;
      string RGhzVHqljk;
      string GqUZWKrwKN;
      string TsBeyUReXM;
      string APZtBjhLLW;
      string EsKSSjjDlG;
      string JRyYcXEDAA;
      string oLNWkqRaYm;
      string bfjmJZihMO;
      string jOsRChQBRc;
      if(nXwipWrJRG == bFdJQBNImw){eeLLgremha = true;}
      else if(bFdJQBNImw == nXwipWrJRG){ZDCGQqznGt = true;}
      if(DPASRfoHYl == RGhzVHqljk){SJdzdchLOC = true;}
      else if(RGhzVHqljk == DPASRfoHYl){liiGRBbXaf = true;}
      if(GgLJIsSLhT == GqUZWKrwKN){oWqlPaSuUD = true;}
      else if(GqUZWKrwKN == GgLJIsSLhT){aGYqYNfHHw = true;}
      if(GXKmZDEkdi == TsBeyUReXM){ZPJwHwUYFQ = true;}
      else if(TsBeyUReXM == GXKmZDEkdi){RzUzOkUBdL = true;}
      if(bGrEFgSWWr == APZtBjhLLW){tuAkuaktmZ = true;}
      else if(APZtBjhLLW == bGrEFgSWWr){VonOMZLVgo = true;}
      if(FryxwGMmZw == EsKSSjjDlG){AFlOnInZuG = true;}
      else if(EsKSSjjDlG == FryxwGMmZw){iEuEQTdLgC = true;}
      if(DfbyAfFMsN == JRyYcXEDAA){ZjSdADAgqg = true;}
      else if(JRyYcXEDAA == DfbyAfFMsN){KqfJblNjqf = true;}
      if(bDdoKznGEa == oLNWkqRaYm){IIFyHsVFpo = true;}
      if(awooOOYNqS == bfjmJZihMO){oXHuCUctIz = true;}
      if(pQKgewetEY == jOsRChQBRc){ItcypKbVkq = true;}
      while(oLNWkqRaYm == bDdoKznGEa){fZsPJkRKey = true;}
      while(bfjmJZihMO == bfjmJZihMO){CJaSNMEPhu = true;}
      while(jOsRChQBRc == jOsRChQBRc){GJUaAdIdlZ = true;}
      if(eeLLgremha == true){eeLLgremha = false;}
      if(SJdzdchLOC == true){SJdzdchLOC = false;}
      if(oWqlPaSuUD == true){oWqlPaSuUD = false;}
      if(ZPJwHwUYFQ == true){ZPJwHwUYFQ = false;}
      if(tuAkuaktmZ == true){tuAkuaktmZ = false;}
      if(AFlOnInZuG == true){AFlOnInZuG = false;}
      if(ZjSdADAgqg == true){ZjSdADAgqg = false;}
      if(IIFyHsVFpo == true){IIFyHsVFpo = false;}
      if(oXHuCUctIz == true){oXHuCUctIz = false;}
      if(ItcypKbVkq == true){ItcypKbVkq = false;}
      if(ZDCGQqznGt == true){ZDCGQqznGt = false;}
      if(liiGRBbXaf == true){liiGRBbXaf = false;}
      if(aGYqYNfHHw == true){aGYqYNfHHw = false;}
      if(RzUzOkUBdL == true){RzUzOkUBdL = false;}
      if(VonOMZLVgo == true){VonOMZLVgo = false;}
      if(iEuEQTdLgC == true){iEuEQTdLgC = false;}
      if(KqfJblNjqf == true){KqfJblNjqf = false;}
      if(fZsPJkRKey == true){fZsPJkRKey = false;}
      if(CJaSNMEPhu == true){CJaSNMEPhu = false;}
      if(GJUaAdIdlZ == true){GJUaAdIdlZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLCSMWMXHU
{ 
  void PrNmSFPBwJ()
  { 
      bool LAFAdAmqho = false;
      bool VKQBRhzDgD = false;
      bool GHBWCKYFbr = false;
      bool rtixCTEAYb = false;
      bool hxmGshuyaw = false;
      bool ZoQPYDyiyS = false;
      bool ahPoxbbTzx = false;
      bool cydFVIUtdT = false;
      bool OZdeRDdSXy = false;
      bool UUCFAzgxJR = false;
      bool GbzcSaKLsP = false;
      bool iEFeEAEjWs = false;
      bool xIuAcHwYEW = false;
      bool aWjLMmaBLq = false;
      bool rSYIPQPWBz = false;
      bool uxZQTyfyzK = false;
      bool elGWnLTsRQ = false;
      bool ZCXfBeimjM = false;
      bool rYWFadwTrO = false;
      bool HbBBMFMCTE = false;
      string cbyVFpHoRl;
      string xKsOgRbHrE;
      string sgTrPpKkdX;
      string TCuYDsbPMK;
      string lYTIHabHEt;
      string HtrdAuIGGO;
      string fVLsRuOTLm;
      string oMuhSTNKjo;
      string NCgiQZJRYI;
      string kVJxdPNaqM;
      string LHwQFtzKLf;
      string hxWQBcobcq;
      string kxuCBTCyDC;
      string GmTXdFGPdV;
      string ZzFsZnzrwA;
      string ZkyzaNMsOl;
      string rBGIYucymu;
      string WZxGRkqCbN;
      string TJBCbVoUwP;
      string sMArdYsxTe;
      if(cbyVFpHoRl == LHwQFtzKLf){LAFAdAmqho = true;}
      else if(LHwQFtzKLf == cbyVFpHoRl){GbzcSaKLsP = true;}
      if(xKsOgRbHrE == hxWQBcobcq){VKQBRhzDgD = true;}
      else if(hxWQBcobcq == xKsOgRbHrE){iEFeEAEjWs = true;}
      if(sgTrPpKkdX == kxuCBTCyDC){GHBWCKYFbr = true;}
      else if(kxuCBTCyDC == sgTrPpKkdX){xIuAcHwYEW = true;}
      if(TCuYDsbPMK == GmTXdFGPdV){rtixCTEAYb = true;}
      else if(GmTXdFGPdV == TCuYDsbPMK){aWjLMmaBLq = true;}
      if(lYTIHabHEt == ZzFsZnzrwA){hxmGshuyaw = true;}
      else if(ZzFsZnzrwA == lYTIHabHEt){rSYIPQPWBz = true;}
      if(HtrdAuIGGO == ZkyzaNMsOl){ZoQPYDyiyS = true;}
      else if(ZkyzaNMsOl == HtrdAuIGGO){uxZQTyfyzK = true;}
      if(fVLsRuOTLm == rBGIYucymu){ahPoxbbTzx = true;}
      else if(rBGIYucymu == fVLsRuOTLm){elGWnLTsRQ = true;}
      if(oMuhSTNKjo == WZxGRkqCbN){cydFVIUtdT = true;}
      if(NCgiQZJRYI == TJBCbVoUwP){OZdeRDdSXy = true;}
      if(kVJxdPNaqM == sMArdYsxTe){UUCFAzgxJR = true;}
      while(WZxGRkqCbN == oMuhSTNKjo){ZCXfBeimjM = true;}
      while(TJBCbVoUwP == TJBCbVoUwP){rYWFadwTrO = true;}
      while(sMArdYsxTe == sMArdYsxTe){HbBBMFMCTE = true;}
      if(LAFAdAmqho == true){LAFAdAmqho = false;}
      if(VKQBRhzDgD == true){VKQBRhzDgD = false;}
      if(GHBWCKYFbr == true){GHBWCKYFbr = false;}
      if(rtixCTEAYb == true){rtixCTEAYb = false;}
      if(hxmGshuyaw == true){hxmGshuyaw = false;}
      if(ZoQPYDyiyS == true){ZoQPYDyiyS = false;}
      if(ahPoxbbTzx == true){ahPoxbbTzx = false;}
      if(cydFVIUtdT == true){cydFVIUtdT = false;}
      if(OZdeRDdSXy == true){OZdeRDdSXy = false;}
      if(UUCFAzgxJR == true){UUCFAzgxJR = false;}
      if(GbzcSaKLsP == true){GbzcSaKLsP = false;}
      if(iEFeEAEjWs == true){iEFeEAEjWs = false;}
      if(xIuAcHwYEW == true){xIuAcHwYEW = false;}
      if(aWjLMmaBLq == true){aWjLMmaBLq = false;}
      if(rSYIPQPWBz == true){rSYIPQPWBz = false;}
      if(uxZQTyfyzK == true){uxZQTyfyzK = false;}
      if(elGWnLTsRQ == true){elGWnLTsRQ = false;}
      if(ZCXfBeimjM == true){ZCXfBeimjM = false;}
      if(rYWFadwTrO == true){rYWFadwTrO = false;}
      if(HbBBMFMCTE == true){HbBBMFMCTE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGPOUKQHQN
{ 
  void uoQzMgfExY()
  { 
      bool eNpXsRHSEb = false;
      bool PEOtdREcXB = false;
      bool PkxrlltGWZ = false;
      bool xTJLKOeqBF = false;
      bool uHDHYbqdaL = false;
      bool jnVHusQylG = false;
      bool XBuddwuDiP = false;
      bool mNbSGHhpSK = false;
      bool uQeLoIxCPR = false;
      bool xgEtgsLYcc = false;
      bool fntLXVMCAm = false;
      bool KZebLHVioV = false;
      bool ysmRRGJgkN = false;
      bool uIMpdGVTnS = false;
      bool wuBcGXBchZ = false;
      bool XcjHdmAbsR = false;
      bool MeQmrCNoxE = false;
      bool kCuVZDqKLt = false;
      bool EfzLpSXFLq = false;
      bool GtZVFQdOjD = false;
      string tCqSKOlBDj;
      string HCuNnyfLUB;
      string PdPPWfZIoo;
      string cHIaCgaRqN;
      string lDyxuYYVEz;
      string stLRmPmawd;
      string ocMNGAsUKH;
      string WNTGPMeRUx;
      string HDEowiuqnl;
      string sAVNYIqkpu;
      string fDKxceZFCZ;
      string kUFyWlYXRX;
      string ECfYNWrGgG;
      string VtaZRDrHLQ;
      string IooNBYtWql;
      string jSTSpcXliG;
      string mTXuEptfgS;
      string sRLAOONSWo;
      string bUOuWCaIio;
      string fGXFcoRtJL;
      if(tCqSKOlBDj == fDKxceZFCZ){eNpXsRHSEb = true;}
      else if(fDKxceZFCZ == tCqSKOlBDj){fntLXVMCAm = true;}
      if(HCuNnyfLUB == kUFyWlYXRX){PEOtdREcXB = true;}
      else if(kUFyWlYXRX == HCuNnyfLUB){KZebLHVioV = true;}
      if(PdPPWfZIoo == ECfYNWrGgG){PkxrlltGWZ = true;}
      else if(ECfYNWrGgG == PdPPWfZIoo){ysmRRGJgkN = true;}
      if(cHIaCgaRqN == VtaZRDrHLQ){xTJLKOeqBF = true;}
      else if(VtaZRDrHLQ == cHIaCgaRqN){uIMpdGVTnS = true;}
      if(lDyxuYYVEz == IooNBYtWql){uHDHYbqdaL = true;}
      else if(IooNBYtWql == lDyxuYYVEz){wuBcGXBchZ = true;}
      if(stLRmPmawd == jSTSpcXliG){jnVHusQylG = true;}
      else if(jSTSpcXliG == stLRmPmawd){XcjHdmAbsR = true;}
      if(ocMNGAsUKH == mTXuEptfgS){XBuddwuDiP = true;}
      else if(mTXuEptfgS == ocMNGAsUKH){MeQmrCNoxE = true;}
      if(WNTGPMeRUx == sRLAOONSWo){mNbSGHhpSK = true;}
      if(HDEowiuqnl == bUOuWCaIio){uQeLoIxCPR = true;}
      if(sAVNYIqkpu == fGXFcoRtJL){xgEtgsLYcc = true;}
      while(sRLAOONSWo == WNTGPMeRUx){kCuVZDqKLt = true;}
      while(bUOuWCaIio == bUOuWCaIio){EfzLpSXFLq = true;}
      while(fGXFcoRtJL == fGXFcoRtJL){GtZVFQdOjD = true;}
      if(eNpXsRHSEb == true){eNpXsRHSEb = false;}
      if(PEOtdREcXB == true){PEOtdREcXB = false;}
      if(PkxrlltGWZ == true){PkxrlltGWZ = false;}
      if(xTJLKOeqBF == true){xTJLKOeqBF = false;}
      if(uHDHYbqdaL == true){uHDHYbqdaL = false;}
      if(jnVHusQylG == true){jnVHusQylG = false;}
      if(XBuddwuDiP == true){XBuddwuDiP = false;}
      if(mNbSGHhpSK == true){mNbSGHhpSK = false;}
      if(uQeLoIxCPR == true){uQeLoIxCPR = false;}
      if(xgEtgsLYcc == true){xgEtgsLYcc = false;}
      if(fntLXVMCAm == true){fntLXVMCAm = false;}
      if(KZebLHVioV == true){KZebLHVioV = false;}
      if(ysmRRGJgkN == true){ysmRRGJgkN = false;}
      if(uIMpdGVTnS == true){uIMpdGVTnS = false;}
      if(wuBcGXBchZ == true){wuBcGXBchZ = false;}
      if(XcjHdmAbsR == true){XcjHdmAbsR = false;}
      if(MeQmrCNoxE == true){MeQmrCNoxE = false;}
      if(kCuVZDqKLt == true){kCuVZDqKLt = false;}
      if(EfzLpSXFLq == true){EfzLpSXFLq = false;}
      if(GtZVFQdOjD == true){GtZVFQdOjD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PXECMNBJLF
{ 
  void RfoFVWaOQD()
  { 
      bool VxlAptOLcK = false;
      bool xBahMmBfuy = false;
      bool assZIbqcGU = false;
      bool iySMxbgxVl = false;
      bool kfmjffRCqw = false;
      bool clGIHbEMqO = false;
      bool DlFHazhNjk = false;
      bool GDJJMtGIsc = false;
      bool JnkJrxqKFV = false;
      bool WUGHhzaeJg = false;
      bool xDSGpYbxuM = false;
      bool UwSOEPBuPd = false;
      bool HXIONkxBaN = false;
      bool TbzMeGUdSS = false;
      bool UtPsAaBrCS = false;
      bool yeOeYZuDrF = false;
      bool bZWgrrwGjy = false;
      bool tWcwINHONl = false;
      bool jEzHPoMTmE = false;
      bool KRlNqtXhAH = false;
      string xARtdLQByp;
      string zECILFjwYV;
      string FGBpLKzQkG;
      string rLVSCfKEMG;
      string jlbDKJrVet;
      string xYjPPpzbhT;
      string MzPqxmiiFe;
      string ufiSlSexeC;
      string SclqITbGCL;
      string giVstjVkFX;
      string aIPzzRoQcw;
      string LBwfBiNYhc;
      string LcftyMJpYC;
      string xtrHbJNlqq;
      string dKcGzelpqL;
      string VwCbLxbUBm;
      string HzrazRJnDq;
      string UbgpzBzZtS;
      string ZTyMfAqPud;
      string hrkEjdRBGh;
      if(xARtdLQByp == aIPzzRoQcw){VxlAptOLcK = true;}
      else if(aIPzzRoQcw == xARtdLQByp){xDSGpYbxuM = true;}
      if(zECILFjwYV == LBwfBiNYhc){xBahMmBfuy = true;}
      else if(LBwfBiNYhc == zECILFjwYV){UwSOEPBuPd = true;}
      if(FGBpLKzQkG == LcftyMJpYC){assZIbqcGU = true;}
      else if(LcftyMJpYC == FGBpLKzQkG){HXIONkxBaN = true;}
      if(rLVSCfKEMG == xtrHbJNlqq){iySMxbgxVl = true;}
      else if(xtrHbJNlqq == rLVSCfKEMG){TbzMeGUdSS = true;}
      if(jlbDKJrVet == dKcGzelpqL){kfmjffRCqw = true;}
      else if(dKcGzelpqL == jlbDKJrVet){UtPsAaBrCS = true;}
      if(xYjPPpzbhT == VwCbLxbUBm){clGIHbEMqO = true;}
      else if(VwCbLxbUBm == xYjPPpzbhT){yeOeYZuDrF = true;}
      if(MzPqxmiiFe == HzrazRJnDq){DlFHazhNjk = true;}
      else if(HzrazRJnDq == MzPqxmiiFe){bZWgrrwGjy = true;}
      if(ufiSlSexeC == UbgpzBzZtS){GDJJMtGIsc = true;}
      if(SclqITbGCL == ZTyMfAqPud){JnkJrxqKFV = true;}
      if(giVstjVkFX == hrkEjdRBGh){WUGHhzaeJg = true;}
      while(UbgpzBzZtS == ufiSlSexeC){tWcwINHONl = true;}
      while(ZTyMfAqPud == ZTyMfAqPud){jEzHPoMTmE = true;}
      while(hrkEjdRBGh == hrkEjdRBGh){KRlNqtXhAH = true;}
      if(VxlAptOLcK == true){VxlAptOLcK = false;}
      if(xBahMmBfuy == true){xBahMmBfuy = false;}
      if(assZIbqcGU == true){assZIbqcGU = false;}
      if(iySMxbgxVl == true){iySMxbgxVl = false;}
      if(kfmjffRCqw == true){kfmjffRCqw = false;}
      if(clGIHbEMqO == true){clGIHbEMqO = false;}
      if(DlFHazhNjk == true){DlFHazhNjk = false;}
      if(GDJJMtGIsc == true){GDJJMtGIsc = false;}
      if(JnkJrxqKFV == true){JnkJrxqKFV = false;}
      if(WUGHhzaeJg == true){WUGHhzaeJg = false;}
      if(xDSGpYbxuM == true){xDSGpYbxuM = false;}
      if(UwSOEPBuPd == true){UwSOEPBuPd = false;}
      if(HXIONkxBaN == true){HXIONkxBaN = false;}
      if(TbzMeGUdSS == true){TbzMeGUdSS = false;}
      if(UtPsAaBrCS == true){UtPsAaBrCS = false;}
      if(yeOeYZuDrF == true){yeOeYZuDrF = false;}
      if(bZWgrrwGjy == true){bZWgrrwGjy = false;}
      if(tWcwINHONl == true){tWcwINHONl = false;}
      if(jEzHPoMTmE == true){jEzHPoMTmE = false;}
      if(KRlNqtXhAH == true){KRlNqtXhAH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUADSALLVY
{ 
  void UGUURdQOMe()
  { 
      bool XZIcdtJdSq = false;
      bool iVmuCadbrm = false;
      bool XwWiXSInMM = false;
      bool FHFLFrIbkQ = false;
      bool rfcseZtKBp = false;
      bool UAnRIaCZEL = false;
      bool kVRFkaQapJ = false;
      bool RBpauqTdDy = false;
      bool YymVrFTmCd = false;
      bool piXZfWOWHE = false;
      bool JSUqXSJMWQ = false;
      bool GYWFllhuMf = false;
      bool GcYLTicQuY = false;
      bool cxVzoFduyZ = false;
      bool uHQkWQLRns = false;
      bool nTJbxftIWo = false;
      bool osQxnJDXQf = false;
      bool ImwmkzLmnC = false;
      bool WLcCkJmtCI = false;
      bool LUXJjBpTxN = false;
      string srchESbhaL;
      string qmqCZGWIqL;
      string EccXOqGnTI;
      string BgEAfxFIJD;
      string ogNgkfbIsX;
      string fjZuOPOESN;
      string LmNRKJipWb;
      string BOymVWPwli;
      string OyuwcRGJlP;
      string iAowrBTwWb;
      string xklQWRkmYr;
      string ASRiyMrRnr;
      string CYEGsAYCuU;
      string DSZKlcMdZK;
      string gTktOPhGxe;
      string IBHdZXgeXV;
      string siqEnhrHxU;
      string AOrdLhnKrc;
      string SREPLBKukO;
      string wgFDRybgFg;
      if(srchESbhaL == xklQWRkmYr){XZIcdtJdSq = true;}
      else if(xklQWRkmYr == srchESbhaL){JSUqXSJMWQ = true;}
      if(qmqCZGWIqL == ASRiyMrRnr){iVmuCadbrm = true;}
      else if(ASRiyMrRnr == qmqCZGWIqL){GYWFllhuMf = true;}
      if(EccXOqGnTI == CYEGsAYCuU){XwWiXSInMM = true;}
      else if(CYEGsAYCuU == EccXOqGnTI){GcYLTicQuY = true;}
      if(BgEAfxFIJD == DSZKlcMdZK){FHFLFrIbkQ = true;}
      else if(DSZKlcMdZK == BgEAfxFIJD){cxVzoFduyZ = true;}
      if(ogNgkfbIsX == gTktOPhGxe){rfcseZtKBp = true;}
      else if(gTktOPhGxe == ogNgkfbIsX){uHQkWQLRns = true;}
      if(fjZuOPOESN == IBHdZXgeXV){UAnRIaCZEL = true;}
      else if(IBHdZXgeXV == fjZuOPOESN){nTJbxftIWo = true;}
      if(LmNRKJipWb == siqEnhrHxU){kVRFkaQapJ = true;}
      else if(siqEnhrHxU == LmNRKJipWb){osQxnJDXQf = true;}
      if(BOymVWPwli == AOrdLhnKrc){RBpauqTdDy = true;}
      if(OyuwcRGJlP == SREPLBKukO){YymVrFTmCd = true;}
      if(iAowrBTwWb == wgFDRybgFg){piXZfWOWHE = true;}
      while(AOrdLhnKrc == BOymVWPwli){ImwmkzLmnC = true;}
      while(SREPLBKukO == SREPLBKukO){WLcCkJmtCI = true;}
      while(wgFDRybgFg == wgFDRybgFg){LUXJjBpTxN = true;}
      if(XZIcdtJdSq == true){XZIcdtJdSq = false;}
      if(iVmuCadbrm == true){iVmuCadbrm = false;}
      if(XwWiXSInMM == true){XwWiXSInMM = false;}
      if(FHFLFrIbkQ == true){FHFLFrIbkQ = false;}
      if(rfcseZtKBp == true){rfcseZtKBp = false;}
      if(UAnRIaCZEL == true){UAnRIaCZEL = false;}
      if(kVRFkaQapJ == true){kVRFkaQapJ = false;}
      if(RBpauqTdDy == true){RBpauqTdDy = false;}
      if(YymVrFTmCd == true){YymVrFTmCd = false;}
      if(piXZfWOWHE == true){piXZfWOWHE = false;}
      if(JSUqXSJMWQ == true){JSUqXSJMWQ = false;}
      if(GYWFllhuMf == true){GYWFllhuMf = false;}
      if(GcYLTicQuY == true){GcYLTicQuY = false;}
      if(cxVzoFduyZ == true){cxVzoFduyZ = false;}
      if(uHQkWQLRns == true){uHQkWQLRns = false;}
      if(nTJbxftIWo == true){nTJbxftIWo = false;}
      if(osQxnJDXQf == true){osQxnJDXQf = false;}
      if(ImwmkzLmnC == true){ImwmkzLmnC = false;}
      if(WLcCkJmtCI == true){WLcCkJmtCI = false;}
      if(LUXJjBpTxN == true){LUXJjBpTxN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBQUGAJUBL
{ 
  void cXDqAbFUxm()
  { 
      bool ZVkhFSzlSp = false;
      bool HWMrREQEqj = false;
      bool eHWyXuECom = false;
      bool GnSGyOmgaC = false;
      bool KTykJkAAUy = false;
      bool qHjsJSzlKJ = false;
      bool OwweiSEFsD = false;
      bool RjdoYKJkol = false;
      bool uDhpuzEZwf = false;
      bool PAVQnNWSBp = false;
      bool gtHRgGctTz = false;
      bool JOxXOLOGjj = false;
      bool OdJNmROMBK = false;
      bool npjyFAwQJo = false;
      bool VJFxWBCyCb = false;
      bool zQiRbCktdP = false;
      bool rQsIKSdzRN = false;
      bool OyxtNEYMpl = false;
      bool OPKYLWHRWD = false;
      bool PClswFQwlD = false;
      string FpbGOUQuXm;
      string nyZTDICpEs;
      string XxKfmrsJQP;
      string EtClCfzXrS;
      string gBKgTWbtKR;
      string gGQMRHfuTW;
      string bHeHhsunQW;
      string IdxkMWmcLP;
      string PyyyixcpTu;
      string ADEUqZVDya;
      string bndnICIeAu;
      string UCjDHcIfYj;
      string QEUVWFZctm;
      string AjeknbUKpf;
      string oxoXZxTBNN;
      string QpdNJWTHRD;
      string cfkNtkXyPf;
      string IxpruSPwuY;
      string kXOfVKFQbQ;
      string HMsmDIMbco;
      if(FpbGOUQuXm == bndnICIeAu){ZVkhFSzlSp = true;}
      else if(bndnICIeAu == FpbGOUQuXm){gtHRgGctTz = true;}
      if(nyZTDICpEs == UCjDHcIfYj){HWMrREQEqj = true;}
      else if(UCjDHcIfYj == nyZTDICpEs){JOxXOLOGjj = true;}
      if(XxKfmrsJQP == QEUVWFZctm){eHWyXuECom = true;}
      else if(QEUVWFZctm == XxKfmrsJQP){OdJNmROMBK = true;}
      if(EtClCfzXrS == AjeknbUKpf){GnSGyOmgaC = true;}
      else if(AjeknbUKpf == EtClCfzXrS){npjyFAwQJo = true;}
      if(gBKgTWbtKR == oxoXZxTBNN){KTykJkAAUy = true;}
      else if(oxoXZxTBNN == gBKgTWbtKR){VJFxWBCyCb = true;}
      if(gGQMRHfuTW == QpdNJWTHRD){qHjsJSzlKJ = true;}
      else if(QpdNJWTHRD == gGQMRHfuTW){zQiRbCktdP = true;}
      if(bHeHhsunQW == cfkNtkXyPf){OwweiSEFsD = true;}
      else if(cfkNtkXyPf == bHeHhsunQW){rQsIKSdzRN = true;}
      if(IdxkMWmcLP == IxpruSPwuY){RjdoYKJkol = true;}
      if(PyyyixcpTu == kXOfVKFQbQ){uDhpuzEZwf = true;}
      if(ADEUqZVDya == HMsmDIMbco){PAVQnNWSBp = true;}
      while(IxpruSPwuY == IdxkMWmcLP){OyxtNEYMpl = true;}
      while(kXOfVKFQbQ == kXOfVKFQbQ){OPKYLWHRWD = true;}
      while(HMsmDIMbco == HMsmDIMbco){PClswFQwlD = true;}
      if(ZVkhFSzlSp == true){ZVkhFSzlSp = false;}
      if(HWMrREQEqj == true){HWMrREQEqj = false;}
      if(eHWyXuECom == true){eHWyXuECom = false;}
      if(GnSGyOmgaC == true){GnSGyOmgaC = false;}
      if(KTykJkAAUy == true){KTykJkAAUy = false;}
      if(qHjsJSzlKJ == true){qHjsJSzlKJ = false;}
      if(OwweiSEFsD == true){OwweiSEFsD = false;}
      if(RjdoYKJkol == true){RjdoYKJkol = false;}
      if(uDhpuzEZwf == true){uDhpuzEZwf = false;}
      if(PAVQnNWSBp == true){PAVQnNWSBp = false;}
      if(gtHRgGctTz == true){gtHRgGctTz = false;}
      if(JOxXOLOGjj == true){JOxXOLOGjj = false;}
      if(OdJNmROMBK == true){OdJNmROMBK = false;}
      if(npjyFAwQJo == true){npjyFAwQJo = false;}
      if(VJFxWBCyCb == true){VJFxWBCyCb = false;}
      if(zQiRbCktdP == true){zQiRbCktdP = false;}
      if(rQsIKSdzRN == true){rQsIKSdzRN = false;}
      if(OyxtNEYMpl == true){OyxtNEYMpl = false;}
      if(OPKYLWHRWD == true){OPKYLWHRWD = false;}
      if(PClswFQwlD == true){PClswFQwlD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBBWOAAODX
{ 
  void hfhEEsgQVG()
  { 
      bool XSWmZpzLKP = false;
      bool lFawzLiphR = false;
      bool YkpaSNObEF = false;
      bool YaJRKDISeW = false;
      bool mFLXbnalYY = false;
      bool mgIfxmcwUL = false;
      bool aWHEqLuJlw = false;
      bool DQKLdTZRze = false;
      bool mcCeRrRcUX = false;
      bool aMxSuPxGgP = false;
      bool rRAcVWVxBd = false;
      bool NKwpXyUcly = false;
      bool tSnNUpSrPN = false;
      bool VSkilVcYJu = false;
      bool WTaqKQPHux = false;
      bool uUUiVZclIe = false;
      bool EdhnHtYNDB = false;
      bool UuSqbaqxDD = false;
      bool aLwRRAyCNM = false;
      bool rpQdqskmiP = false;
      string hTOPunZQte;
      string cZVmIdVjIQ;
      string RlQMdBWIeN;
      string eLiSQyeHLp;
      string PiAdoAYmCp;
      string zUGyZuDClt;
      string RQkfAQpCWJ;
      string yOXSAilmXc;
      string biGnNJEksV;
      string ucVRXzxTdX;
      string JWQsrkwnxp;
      string IQeIRhKxSp;
      string LFJANUsGtB;
      string lSJzSFRNwc;
      string NQmCMeyMzp;
      string nABmLEMPeW;
      string rptwEpGeoL;
      string PxAocuRHnh;
      string WfGENlRVnO;
      string sChYkWWqyV;
      if(hTOPunZQte == JWQsrkwnxp){XSWmZpzLKP = true;}
      else if(JWQsrkwnxp == hTOPunZQte){rRAcVWVxBd = true;}
      if(cZVmIdVjIQ == IQeIRhKxSp){lFawzLiphR = true;}
      else if(IQeIRhKxSp == cZVmIdVjIQ){NKwpXyUcly = true;}
      if(RlQMdBWIeN == LFJANUsGtB){YkpaSNObEF = true;}
      else if(LFJANUsGtB == RlQMdBWIeN){tSnNUpSrPN = true;}
      if(eLiSQyeHLp == lSJzSFRNwc){YaJRKDISeW = true;}
      else if(lSJzSFRNwc == eLiSQyeHLp){VSkilVcYJu = true;}
      if(PiAdoAYmCp == NQmCMeyMzp){mFLXbnalYY = true;}
      else if(NQmCMeyMzp == PiAdoAYmCp){WTaqKQPHux = true;}
      if(zUGyZuDClt == nABmLEMPeW){mgIfxmcwUL = true;}
      else if(nABmLEMPeW == zUGyZuDClt){uUUiVZclIe = true;}
      if(RQkfAQpCWJ == rptwEpGeoL){aWHEqLuJlw = true;}
      else if(rptwEpGeoL == RQkfAQpCWJ){EdhnHtYNDB = true;}
      if(yOXSAilmXc == PxAocuRHnh){DQKLdTZRze = true;}
      if(biGnNJEksV == WfGENlRVnO){mcCeRrRcUX = true;}
      if(ucVRXzxTdX == sChYkWWqyV){aMxSuPxGgP = true;}
      while(PxAocuRHnh == yOXSAilmXc){UuSqbaqxDD = true;}
      while(WfGENlRVnO == WfGENlRVnO){aLwRRAyCNM = true;}
      while(sChYkWWqyV == sChYkWWqyV){rpQdqskmiP = true;}
      if(XSWmZpzLKP == true){XSWmZpzLKP = false;}
      if(lFawzLiphR == true){lFawzLiphR = false;}
      if(YkpaSNObEF == true){YkpaSNObEF = false;}
      if(YaJRKDISeW == true){YaJRKDISeW = false;}
      if(mFLXbnalYY == true){mFLXbnalYY = false;}
      if(mgIfxmcwUL == true){mgIfxmcwUL = false;}
      if(aWHEqLuJlw == true){aWHEqLuJlw = false;}
      if(DQKLdTZRze == true){DQKLdTZRze = false;}
      if(mcCeRrRcUX == true){mcCeRrRcUX = false;}
      if(aMxSuPxGgP == true){aMxSuPxGgP = false;}
      if(rRAcVWVxBd == true){rRAcVWVxBd = false;}
      if(NKwpXyUcly == true){NKwpXyUcly = false;}
      if(tSnNUpSrPN == true){tSnNUpSrPN = false;}
      if(VSkilVcYJu == true){VSkilVcYJu = false;}
      if(WTaqKQPHux == true){WTaqKQPHux = false;}
      if(uUUiVZclIe == true){uUUiVZclIe = false;}
      if(EdhnHtYNDB == true){EdhnHtYNDB = false;}
      if(UuSqbaqxDD == true){UuSqbaqxDD = false;}
      if(aLwRRAyCNM == true){aLwRRAyCNM = false;}
      if(rpQdqskmiP == true){rpQdqskmiP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KOGNLHFMVO
{ 
  void EQPtNJKslF()
  { 
      bool MTYAESnkpx = false;
      bool jDNRqfYoPb = false;
      bool wjrlqohkmx = false;
      bool tbbfHFnJaU = false;
      bool INzWdrpzTP = false;
      bool OeaPmcamJO = false;
      bool kDyrDHahJk = false;
      bool rPOtSijVHy = false;
      bool zhRWiPBMrd = false;
      bool dBAMjEPHTV = false;
      bool RHohXzQfwE = false;
      bool sFeKOClaIn = false;
      bool GNoeGpPBJO = false;
      bool TbBlgqsiyj = false;
      bool yUPmkYWoyg = false;
      bool RnyfPDSJbh = false;
      bool jOWhkQDrcW = false;
      bool JDcYolyBtg = false;
      bool TZDcwedVWd = false;
      bool YiGQAjygCT = false;
      string aqEyXpabZn;
      string ayVELGHSyl;
      string OBxJGpNcGc;
      string bijORYWgaz;
      string OaouJcPJgH;
      string GYwgrZstrg;
      string cxUwLrOGlm;
      string iaqzWmLBzc;
      string aDwzWDmDVr;
      string ebnsWRFsjR;
      string NIWtXfgxJF;
      string NruPFZAVYH;
      string ELktHHlxbF;
      string gSRhPSfCap;
      string WotQemgYmx;
      string QjTbMBXclQ;
      string tiUDYuZNzm;
      string syuikPRTPU;
      string ZNJenxypUN;
      string uDQKwmUpqj;
      if(aqEyXpabZn == NIWtXfgxJF){MTYAESnkpx = true;}
      else if(NIWtXfgxJF == aqEyXpabZn){RHohXzQfwE = true;}
      if(ayVELGHSyl == NruPFZAVYH){jDNRqfYoPb = true;}
      else if(NruPFZAVYH == ayVELGHSyl){sFeKOClaIn = true;}
      if(OBxJGpNcGc == ELktHHlxbF){wjrlqohkmx = true;}
      else if(ELktHHlxbF == OBxJGpNcGc){GNoeGpPBJO = true;}
      if(bijORYWgaz == gSRhPSfCap){tbbfHFnJaU = true;}
      else if(gSRhPSfCap == bijORYWgaz){TbBlgqsiyj = true;}
      if(OaouJcPJgH == WotQemgYmx){INzWdrpzTP = true;}
      else if(WotQemgYmx == OaouJcPJgH){yUPmkYWoyg = true;}
      if(GYwgrZstrg == QjTbMBXclQ){OeaPmcamJO = true;}
      else if(QjTbMBXclQ == GYwgrZstrg){RnyfPDSJbh = true;}
      if(cxUwLrOGlm == tiUDYuZNzm){kDyrDHahJk = true;}
      else if(tiUDYuZNzm == cxUwLrOGlm){jOWhkQDrcW = true;}
      if(iaqzWmLBzc == syuikPRTPU){rPOtSijVHy = true;}
      if(aDwzWDmDVr == ZNJenxypUN){zhRWiPBMrd = true;}
      if(ebnsWRFsjR == uDQKwmUpqj){dBAMjEPHTV = true;}
      while(syuikPRTPU == iaqzWmLBzc){JDcYolyBtg = true;}
      while(ZNJenxypUN == ZNJenxypUN){TZDcwedVWd = true;}
      while(uDQKwmUpqj == uDQKwmUpqj){YiGQAjygCT = true;}
      if(MTYAESnkpx == true){MTYAESnkpx = false;}
      if(jDNRqfYoPb == true){jDNRqfYoPb = false;}
      if(wjrlqohkmx == true){wjrlqohkmx = false;}
      if(tbbfHFnJaU == true){tbbfHFnJaU = false;}
      if(INzWdrpzTP == true){INzWdrpzTP = false;}
      if(OeaPmcamJO == true){OeaPmcamJO = false;}
      if(kDyrDHahJk == true){kDyrDHahJk = false;}
      if(rPOtSijVHy == true){rPOtSijVHy = false;}
      if(zhRWiPBMrd == true){zhRWiPBMrd = false;}
      if(dBAMjEPHTV == true){dBAMjEPHTV = false;}
      if(RHohXzQfwE == true){RHohXzQfwE = false;}
      if(sFeKOClaIn == true){sFeKOClaIn = false;}
      if(GNoeGpPBJO == true){GNoeGpPBJO = false;}
      if(TbBlgqsiyj == true){TbBlgqsiyj = false;}
      if(yUPmkYWoyg == true){yUPmkYWoyg = false;}
      if(RnyfPDSJbh == true){RnyfPDSJbh = false;}
      if(jOWhkQDrcW == true){jOWhkQDrcW = false;}
      if(JDcYolyBtg == true){JDcYolyBtg = false;}
      if(TZDcwedVWd == true){TZDcwedVWd = false;}
      if(YiGQAjygCT == true){YiGQAjygCT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OONFPLHZEE
{ 
  void knLNlKeMOX()
  { 
      bool UZWQdQYAfe = false;
      bool EbbXxVhKKx = false;
      bool DMsReRKBTw = false;
      bool ixbJrHJBrR = false;
      bool sJppsCRglr = false;
      bool PCmaXHfFkL = false;
      bool GXfiwGASep = false;
      bool MgSsEsWDYc = false;
      bool AcOagfKBkj = false;
      bool aDQfLUcGsl = false;
      bool CyCufhjtVe = false;
      bool kcgILcIFCP = false;
      bool wyhuPIPlgj = false;
      bool PQJlZBaSuy = false;
      bool wQfFzxWIUh = false;
      bool LXDdoEQGfW = false;
      bool SxMlPTTthJ = false;
      bool CoJETfSbuR = false;
      bool kHRzXqMfxU = false;
      bool kTmXfzDspe = false;
      string gMuEGWgAFN;
      string osfFVBKZye;
      string HwURHNHllU;
      string bHHJhYdtla;
      string fVSFBXmLwX;
      string jhRHckrcwr;
      string PtNjlglVXw;
      string WQmXzkcOQj;
      string ZuoOksozgx;
      string gBytKkIiST;
      string lRnAATttHr;
      string HdLMSTEyzs;
      string rloZPVRsMO;
      string btuxxHHoNQ;
      string yuqnoColap;
      string fJiZbzcNjd;
      string BAgsPNhOOK;
      string MPkitwuAkM;
      string gfRVhRKVVx;
      string etEiOyNxXb;
      if(gMuEGWgAFN == lRnAATttHr){UZWQdQYAfe = true;}
      else if(lRnAATttHr == gMuEGWgAFN){CyCufhjtVe = true;}
      if(osfFVBKZye == HdLMSTEyzs){EbbXxVhKKx = true;}
      else if(HdLMSTEyzs == osfFVBKZye){kcgILcIFCP = true;}
      if(HwURHNHllU == rloZPVRsMO){DMsReRKBTw = true;}
      else if(rloZPVRsMO == HwURHNHllU){wyhuPIPlgj = true;}
      if(bHHJhYdtla == btuxxHHoNQ){ixbJrHJBrR = true;}
      else if(btuxxHHoNQ == bHHJhYdtla){PQJlZBaSuy = true;}
      if(fVSFBXmLwX == yuqnoColap){sJppsCRglr = true;}
      else if(yuqnoColap == fVSFBXmLwX){wQfFzxWIUh = true;}
      if(jhRHckrcwr == fJiZbzcNjd){PCmaXHfFkL = true;}
      else if(fJiZbzcNjd == jhRHckrcwr){LXDdoEQGfW = true;}
      if(PtNjlglVXw == BAgsPNhOOK){GXfiwGASep = true;}
      else if(BAgsPNhOOK == PtNjlglVXw){SxMlPTTthJ = true;}
      if(WQmXzkcOQj == MPkitwuAkM){MgSsEsWDYc = true;}
      if(ZuoOksozgx == gfRVhRKVVx){AcOagfKBkj = true;}
      if(gBytKkIiST == etEiOyNxXb){aDQfLUcGsl = true;}
      while(MPkitwuAkM == WQmXzkcOQj){CoJETfSbuR = true;}
      while(gfRVhRKVVx == gfRVhRKVVx){kHRzXqMfxU = true;}
      while(etEiOyNxXb == etEiOyNxXb){kTmXfzDspe = true;}
      if(UZWQdQYAfe == true){UZWQdQYAfe = false;}
      if(EbbXxVhKKx == true){EbbXxVhKKx = false;}
      if(DMsReRKBTw == true){DMsReRKBTw = false;}
      if(ixbJrHJBrR == true){ixbJrHJBrR = false;}
      if(sJppsCRglr == true){sJppsCRglr = false;}
      if(PCmaXHfFkL == true){PCmaXHfFkL = false;}
      if(GXfiwGASep == true){GXfiwGASep = false;}
      if(MgSsEsWDYc == true){MgSsEsWDYc = false;}
      if(AcOagfKBkj == true){AcOagfKBkj = false;}
      if(aDQfLUcGsl == true){aDQfLUcGsl = false;}
      if(CyCufhjtVe == true){CyCufhjtVe = false;}
      if(kcgILcIFCP == true){kcgILcIFCP = false;}
      if(wyhuPIPlgj == true){wyhuPIPlgj = false;}
      if(PQJlZBaSuy == true){PQJlZBaSuy = false;}
      if(wQfFzxWIUh == true){wQfFzxWIUh = false;}
      if(LXDdoEQGfW == true){LXDdoEQGfW = false;}
      if(SxMlPTTthJ == true){SxMlPTTthJ = false;}
      if(CoJETfSbuR == true){CoJETfSbuR = false;}
      if(kHRzXqMfxU == true){kHRzXqMfxU = false;}
      if(kTmXfzDspe == true){kTmXfzDspe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XEYOTHNIHC
{ 
  void jqrRqtRQJb()
  { 
      bool nOyWGuGHQM = false;
      bool LAgXstlycM = false;
      bool KdXhauZphL = false;
      bool AeoRueCwuC = false;
      bool LTZkFnwawC = false;
      bool QjSwNKpQuK = false;
      bool VPZFLfLPcO = false;
      bool roDZBqDmbm = false;
      bool zytetPLrEj = false;
      bool nkBjgusTYY = false;
      bool bgyhJbgruW = false;
      bool GDoHLWVtLw = false;
      bool TTKrZHmTsF = false;
      bool xjNCKRALVS = false;
      bool hTwgdkwsXK = false;
      bool ZzIcEHVGHC = false;
      bool nNzoZWomwt = false;
      bool WJYrNAXdNo = false;
      bool KsuifxajxD = false;
      bool wsESdTTGHH = false;
      string VaYqJUoqtU;
      string MAUzDBuYuJ;
      string zwNCwbQAni;
      string dfhIkLWuZJ;
      string oyWqtFznsu;
      string tKROjZMWth;
      string DnCLpgSMNr;
      string dAylTAYWHq;
      string bcHsnTOSYL;
      string zzBrFAuKBN;
      string lmaAQtLfui;
      string ApPDFafIXV;
      string RzmCsdyGfS;
      string ENVsEoCHcs;
      string IhXoKIjxme;
      string UlmeumzYHm;
      string uFzbelUVzQ;
      string YYfeNiayqj;
      string sASByRapxR;
      string odzpxCiwJY;
      if(VaYqJUoqtU == lmaAQtLfui){nOyWGuGHQM = true;}
      else if(lmaAQtLfui == VaYqJUoqtU){bgyhJbgruW = true;}
      if(MAUzDBuYuJ == ApPDFafIXV){LAgXstlycM = true;}
      else if(ApPDFafIXV == MAUzDBuYuJ){GDoHLWVtLw = true;}
      if(zwNCwbQAni == RzmCsdyGfS){KdXhauZphL = true;}
      else if(RzmCsdyGfS == zwNCwbQAni){TTKrZHmTsF = true;}
      if(dfhIkLWuZJ == ENVsEoCHcs){AeoRueCwuC = true;}
      else if(ENVsEoCHcs == dfhIkLWuZJ){xjNCKRALVS = true;}
      if(oyWqtFznsu == IhXoKIjxme){LTZkFnwawC = true;}
      else if(IhXoKIjxme == oyWqtFznsu){hTwgdkwsXK = true;}
      if(tKROjZMWth == UlmeumzYHm){QjSwNKpQuK = true;}
      else if(UlmeumzYHm == tKROjZMWth){ZzIcEHVGHC = true;}
      if(DnCLpgSMNr == uFzbelUVzQ){VPZFLfLPcO = true;}
      else if(uFzbelUVzQ == DnCLpgSMNr){nNzoZWomwt = true;}
      if(dAylTAYWHq == YYfeNiayqj){roDZBqDmbm = true;}
      if(bcHsnTOSYL == sASByRapxR){zytetPLrEj = true;}
      if(zzBrFAuKBN == odzpxCiwJY){nkBjgusTYY = true;}
      while(YYfeNiayqj == dAylTAYWHq){WJYrNAXdNo = true;}
      while(sASByRapxR == sASByRapxR){KsuifxajxD = true;}
      while(odzpxCiwJY == odzpxCiwJY){wsESdTTGHH = true;}
      if(nOyWGuGHQM == true){nOyWGuGHQM = false;}
      if(LAgXstlycM == true){LAgXstlycM = false;}
      if(KdXhauZphL == true){KdXhauZphL = false;}
      if(AeoRueCwuC == true){AeoRueCwuC = false;}
      if(LTZkFnwawC == true){LTZkFnwawC = false;}
      if(QjSwNKpQuK == true){QjSwNKpQuK = false;}
      if(VPZFLfLPcO == true){VPZFLfLPcO = false;}
      if(roDZBqDmbm == true){roDZBqDmbm = false;}
      if(zytetPLrEj == true){zytetPLrEj = false;}
      if(nkBjgusTYY == true){nkBjgusTYY = false;}
      if(bgyhJbgruW == true){bgyhJbgruW = false;}
      if(GDoHLWVtLw == true){GDoHLWVtLw = false;}
      if(TTKrZHmTsF == true){TTKrZHmTsF = false;}
      if(xjNCKRALVS == true){xjNCKRALVS = false;}
      if(hTwgdkwsXK == true){hTwgdkwsXK = false;}
      if(ZzIcEHVGHC == true){ZzIcEHVGHC = false;}
      if(nNzoZWomwt == true){nNzoZWomwt = false;}
      if(WJYrNAXdNo == true){WJYrNAXdNo = false;}
      if(KsuifxajxD == true){KsuifxajxD = false;}
      if(wsESdTTGHH == true){wsESdTTGHH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XIOVXRNXHM
{ 
  void BCEzZdWQOh()
  { 
      bool AdQGDrTbtu = false;
      bool kOZttpamax = false;
      bool coMGmGZMei = false;
      bool nxLRnStcpw = false;
      bool QxxFBbVGfR = false;
      bool FwVIFLQKTx = false;
      bool SHwKGnCIFb = false;
      bool wxwegfqHFK = false;
      bool jSfNdraDLc = false;
      bool CjIrcJAlyM = false;
      bool YMAEUHzpbZ = false;
      bool TIFIMAaigO = false;
      bool MzxcYMoEBW = false;
      bool eFJrkXRbrW = false;
      bool sjakJsdzfc = false;
      bool hRFjAZPXeI = false;
      bool SuoEuNzMXo = false;
      bool hzpKUbXMSf = false;
      bool hoXYoNAYqL = false;
      bool ItwjDyuWpw = false;
      string xKNigRgoec;
      string khXnClYAOS;
      string WBJJXVKfmy;
      string CDtzZQaguk;
      string fQwqlWLapp;
      string PhIKiwBDLK;
      string HACgZgnXOk;
      string LqEcmGESXA;
      string KiowhTtiQc;
      string PXVjdeNOQE;
      string imMEeXdeXb;
      string qifKAYLFyG;
      string lEGlVmVTzI;
      string soBSQWWjRK;
      string pOLokgqKjF;
      string THPKRdfaiq;
      string BKfPiCgNsc;
      string CamnPWsRAn;
      string wLisnkYqAm;
      string puBaIfiwGi;
      if(xKNigRgoec == imMEeXdeXb){AdQGDrTbtu = true;}
      else if(imMEeXdeXb == xKNigRgoec){YMAEUHzpbZ = true;}
      if(khXnClYAOS == qifKAYLFyG){kOZttpamax = true;}
      else if(qifKAYLFyG == khXnClYAOS){TIFIMAaigO = true;}
      if(WBJJXVKfmy == lEGlVmVTzI){coMGmGZMei = true;}
      else if(lEGlVmVTzI == WBJJXVKfmy){MzxcYMoEBW = true;}
      if(CDtzZQaguk == soBSQWWjRK){nxLRnStcpw = true;}
      else if(soBSQWWjRK == CDtzZQaguk){eFJrkXRbrW = true;}
      if(fQwqlWLapp == pOLokgqKjF){QxxFBbVGfR = true;}
      else if(pOLokgqKjF == fQwqlWLapp){sjakJsdzfc = true;}
      if(PhIKiwBDLK == THPKRdfaiq){FwVIFLQKTx = true;}
      else if(THPKRdfaiq == PhIKiwBDLK){hRFjAZPXeI = true;}
      if(HACgZgnXOk == BKfPiCgNsc){SHwKGnCIFb = true;}
      else if(BKfPiCgNsc == HACgZgnXOk){SuoEuNzMXo = true;}
      if(LqEcmGESXA == CamnPWsRAn){wxwegfqHFK = true;}
      if(KiowhTtiQc == wLisnkYqAm){jSfNdraDLc = true;}
      if(PXVjdeNOQE == puBaIfiwGi){CjIrcJAlyM = true;}
      while(CamnPWsRAn == LqEcmGESXA){hzpKUbXMSf = true;}
      while(wLisnkYqAm == wLisnkYqAm){hoXYoNAYqL = true;}
      while(puBaIfiwGi == puBaIfiwGi){ItwjDyuWpw = true;}
      if(AdQGDrTbtu == true){AdQGDrTbtu = false;}
      if(kOZttpamax == true){kOZttpamax = false;}
      if(coMGmGZMei == true){coMGmGZMei = false;}
      if(nxLRnStcpw == true){nxLRnStcpw = false;}
      if(QxxFBbVGfR == true){QxxFBbVGfR = false;}
      if(FwVIFLQKTx == true){FwVIFLQKTx = false;}
      if(SHwKGnCIFb == true){SHwKGnCIFb = false;}
      if(wxwegfqHFK == true){wxwegfqHFK = false;}
      if(jSfNdraDLc == true){jSfNdraDLc = false;}
      if(CjIrcJAlyM == true){CjIrcJAlyM = false;}
      if(YMAEUHzpbZ == true){YMAEUHzpbZ = false;}
      if(TIFIMAaigO == true){TIFIMAaigO = false;}
      if(MzxcYMoEBW == true){MzxcYMoEBW = false;}
      if(eFJrkXRbrW == true){eFJrkXRbrW = false;}
      if(sjakJsdzfc == true){sjakJsdzfc = false;}
      if(hRFjAZPXeI == true){hRFjAZPXeI = false;}
      if(SuoEuNzMXo == true){SuoEuNzMXo = false;}
      if(hzpKUbXMSf == true){hzpKUbXMSf = false;}
      if(hoXYoNAYqL == true){hoXYoNAYqL = false;}
      if(ItwjDyuWpw == true){ItwjDyuWpw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TVJRKMWLTS
{ 
  void VBnbGWHWuu()
  { 
      bool plPNmkStOZ = false;
      bool LnEEnRRYnf = false;
      bool KJoSYVlsOO = false;
      bool TFDRSpxMAF = false;
      bool rOqWsIEuSj = false;
      bool rZKHkfxwnR = false;
      bool zZfzFFklkx = false;
      bool TFXhnwSSYP = false;
      bool RpZdWtuugm = false;
      bool sAXiGSiqQm = false;
      bool XSKUPlBbTo = false;
      bool NdXXzIzBbK = false;
      bool KoEyEShnaV = false;
      bool MaCkryeENj = false;
      bool sSbrYOcziy = false;
      bool SgOFciNMQw = false;
      bool EMAyblblfA = false;
      bool ctmrRqMMYo = false;
      bool phEcCfLwIJ = false;
      bool kRnQffScQl = false;
      string PYmhcmubcc;
      string mPHMQrSDfD;
      string auExXAICMT;
      string xcHmajpnLC;
      string QGRuiFVjKU;
      string IsxhnTTpJc;
      string erPIeKHUlg;
      string CdrdmTdJNR;
      string dYrqKDeYyG;
      string QAehXXqIPX;
      string xBxdSdBTuT;
      string pJbqyFAXxb;
      string ehVePBzJGO;
      string cUtoTcaNXg;
      string CLddQGYmiR;
      string XSLnsPfSNQ;
      string erNfpUPlXV;
      string elAQYSEqOJ;
      string cMZnqKJFwE;
      string xIzGCKyynw;
      if(PYmhcmubcc == xBxdSdBTuT){plPNmkStOZ = true;}
      else if(xBxdSdBTuT == PYmhcmubcc){XSKUPlBbTo = true;}
      if(mPHMQrSDfD == pJbqyFAXxb){LnEEnRRYnf = true;}
      else if(pJbqyFAXxb == mPHMQrSDfD){NdXXzIzBbK = true;}
      if(auExXAICMT == ehVePBzJGO){KJoSYVlsOO = true;}
      else if(ehVePBzJGO == auExXAICMT){KoEyEShnaV = true;}
      if(xcHmajpnLC == cUtoTcaNXg){TFDRSpxMAF = true;}
      else if(cUtoTcaNXg == xcHmajpnLC){MaCkryeENj = true;}
      if(QGRuiFVjKU == CLddQGYmiR){rOqWsIEuSj = true;}
      else if(CLddQGYmiR == QGRuiFVjKU){sSbrYOcziy = true;}
      if(IsxhnTTpJc == XSLnsPfSNQ){rZKHkfxwnR = true;}
      else if(XSLnsPfSNQ == IsxhnTTpJc){SgOFciNMQw = true;}
      if(erPIeKHUlg == erNfpUPlXV){zZfzFFklkx = true;}
      else if(erNfpUPlXV == erPIeKHUlg){EMAyblblfA = true;}
      if(CdrdmTdJNR == elAQYSEqOJ){TFXhnwSSYP = true;}
      if(dYrqKDeYyG == cMZnqKJFwE){RpZdWtuugm = true;}
      if(QAehXXqIPX == xIzGCKyynw){sAXiGSiqQm = true;}
      while(elAQYSEqOJ == CdrdmTdJNR){ctmrRqMMYo = true;}
      while(cMZnqKJFwE == cMZnqKJFwE){phEcCfLwIJ = true;}
      while(xIzGCKyynw == xIzGCKyynw){kRnQffScQl = true;}
      if(plPNmkStOZ == true){plPNmkStOZ = false;}
      if(LnEEnRRYnf == true){LnEEnRRYnf = false;}
      if(KJoSYVlsOO == true){KJoSYVlsOO = false;}
      if(TFDRSpxMAF == true){TFDRSpxMAF = false;}
      if(rOqWsIEuSj == true){rOqWsIEuSj = false;}
      if(rZKHkfxwnR == true){rZKHkfxwnR = false;}
      if(zZfzFFklkx == true){zZfzFFklkx = false;}
      if(TFXhnwSSYP == true){TFXhnwSSYP = false;}
      if(RpZdWtuugm == true){RpZdWtuugm = false;}
      if(sAXiGSiqQm == true){sAXiGSiqQm = false;}
      if(XSKUPlBbTo == true){XSKUPlBbTo = false;}
      if(NdXXzIzBbK == true){NdXXzIzBbK = false;}
      if(KoEyEShnaV == true){KoEyEShnaV = false;}
      if(MaCkryeENj == true){MaCkryeENj = false;}
      if(sSbrYOcziy == true){sSbrYOcziy = false;}
      if(SgOFciNMQw == true){SgOFciNMQw = false;}
      if(EMAyblblfA == true){EMAyblblfA = false;}
      if(ctmrRqMMYo == true){ctmrRqMMYo = false;}
      if(phEcCfLwIJ == true){phEcCfLwIJ = false;}
      if(kRnQffScQl == true){kRnQffScQl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UKXJNPQKQU
{ 
  void BtVwuPGnzR()
  { 
      bool ExUacojkJa = false;
      bool VpFPWdJFkz = false;
      bool CXYHIfIDMg = false;
      bool ulHALpplEA = false;
      bool gkatxLKbnb = false;
      bool yPmMRfYMRx = false;
      bool gfXbeihEEg = false;
      bool mXAjRQwdKw = false;
      bool VfPjifzuhe = false;
      bool QcTGTBMzPN = false;
      bool dFXGoZOCuA = false;
      bool juCVbAPnsz = false;
      bool jmWYPKEsQQ = false;
      bool DxNwSPHJuI = false;
      bool QwzguVayeS = false;
      bool kYGPcpizqd = false;
      bool VUlexmgFCL = false;
      bool rGrkhnnoct = false;
      bool iGOxeepxSc = false;
      bool gIRQluKUjI = false;
      string OwOOhuhaZH;
      string wXwAmPWTsT;
      string dSxbwleaeT;
      string jRIopDkpHa;
      string XdYrwGPzrT;
      string bhMCfuylSu;
      string QHuFXePGKi;
      string dfLRwztFep;
      string VehKqBEFJu;
      string FyXLKPiSUR;
      string pIoJowVuGg;
      string BrHbZkZjOV;
      string ZJxOceHzHf;
      string PajNANpYVu;
      string eJzctMqwlY;
      string pyEzqgKZfK;
      string oWnaQZItbL;
      string uAOSpQKUUP;
      string mKMhoQWkVT;
      string CPrKGIUXMU;
      if(OwOOhuhaZH == pIoJowVuGg){ExUacojkJa = true;}
      else if(pIoJowVuGg == OwOOhuhaZH){dFXGoZOCuA = true;}
      if(wXwAmPWTsT == BrHbZkZjOV){VpFPWdJFkz = true;}
      else if(BrHbZkZjOV == wXwAmPWTsT){juCVbAPnsz = true;}
      if(dSxbwleaeT == ZJxOceHzHf){CXYHIfIDMg = true;}
      else if(ZJxOceHzHf == dSxbwleaeT){jmWYPKEsQQ = true;}
      if(jRIopDkpHa == PajNANpYVu){ulHALpplEA = true;}
      else if(PajNANpYVu == jRIopDkpHa){DxNwSPHJuI = true;}
      if(XdYrwGPzrT == eJzctMqwlY){gkatxLKbnb = true;}
      else if(eJzctMqwlY == XdYrwGPzrT){QwzguVayeS = true;}
      if(bhMCfuylSu == pyEzqgKZfK){yPmMRfYMRx = true;}
      else if(pyEzqgKZfK == bhMCfuylSu){kYGPcpizqd = true;}
      if(QHuFXePGKi == oWnaQZItbL){gfXbeihEEg = true;}
      else if(oWnaQZItbL == QHuFXePGKi){VUlexmgFCL = true;}
      if(dfLRwztFep == uAOSpQKUUP){mXAjRQwdKw = true;}
      if(VehKqBEFJu == mKMhoQWkVT){VfPjifzuhe = true;}
      if(FyXLKPiSUR == CPrKGIUXMU){QcTGTBMzPN = true;}
      while(uAOSpQKUUP == dfLRwztFep){rGrkhnnoct = true;}
      while(mKMhoQWkVT == mKMhoQWkVT){iGOxeepxSc = true;}
      while(CPrKGIUXMU == CPrKGIUXMU){gIRQluKUjI = true;}
      if(ExUacojkJa == true){ExUacojkJa = false;}
      if(VpFPWdJFkz == true){VpFPWdJFkz = false;}
      if(CXYHIfIDMg == true){CXYHIfIDMg = false;}
      if(ulHALpplEA == true){ulHALpplEA = false;}
      if(gkatxLKbnb == true){gkatxLKbnb = false;}
      if(yPmMRfYMRx == true){yPmMRfYMRx = false;}
      if(gfXbeihEEg == true){gfXbeihEEg = false;}
      if(mXAjRQwdKw == true){mXAjRQwdKw = false;}
      if(VfPjifzuhe == true){VfPjifzuhe = false;}
      if(QcTGTBMzPN == true){QcTGTBMzPN = false;}
      if(dFXGoZOCuA == true){dFXGoZOCuA = false;}
      if(juCVbAPnsz == true){juCVbAPnsz = false;}
      if(jmWYPKEsQQ == true){jmWYPKEsQQ = false;}
      if(DxNwSPHJuI == true){DxNwSPHJuI = false;}
      if(QwzguVayeS == true){QwzguVayeS = false;}
      if(kYGPcpizqd == true){kYGPcpizqd = false;}
      if(VUlexmgFCL == true){VUlexmgFCL = false;}
      if(rGrkhnnoct == true){rGrkhnnoct = false;}
      if(iGOxeepxSc == true){iGOxeepxSc = false;}
      if(gIRQluKUjI == true){gIRQluKUjI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OSEWDBQOKF
{ 
  void uVtifGEaKS()
  { 
      bool gJbdMaUtuz = false;
      bool JbtSZtnTQb = false;
      bool nbdadFQESc = false;
      bool TYfFjtpHwL = false;
      bool ZCxyRVWadN = false;
      bool TeIiVEeAAH = false;
      bool KQaSejuohe = false;
      bool EfXFClefJI = false;
      bool hoZFIoQxjf = false;
      bool PpHnBIadSh = false;
      bool ZgsyImGCgi = false;
      bool YzpqYUpVKp = false;
      bool SxFCPOYiEs = false;
      bool KBMbhBwbwU = false;
      bool hNQAGQzQPf = false;
      bool RFTcObbpht = false;
      bool OXymXXmOIX = false;
      bool XOYpHEgFwz = false;
      bool OHSXbFgiMG = false;
      bool ZGtBFKOdbh = false;
      string OXEjJQchVi;
      string iQUtmbepCC;
      string zaAggHWErx;
      string LrjQlUESAb;
      string BIpYDOxbVq;
      string TJuelmWXDC;
      string sYpYWpfEHR;
      string WLpaBpjbdR;
      string JuiBcCwFdy;
      string ygPyhbSRBM;
      string isTETISUcu;
      string DutkrypouU;
      string taZJTpwrrY;
      string XSZQiQadgU;
      string iabhtCldFi;
      string lcVgSHSJjd;
      string MacDWkVcCb;
      string WLHakSyqOR;
      string DRlImuwsya;
      string xRtDHIyYKJ;
      if(OXEjJQchVi == isTETISUcu){gJbdMaUtuz = true;}
      else if(isTETISUcu == OXEjJQchVi){ZgsyImGCgi = true;}
      if(iQUtmbepCC == DutkrypouU){JbtSZtnTQb = true;}
      else if(DutkrypouU == iQUtmbepCC){YzpqYUpVKp = true;}
      if(zaAggHWErx == taZJTpwrrY){nbdadFQESc = true;}
      else if(taZJTpwrrY == zaAggHWErx){SxFCPOYiEs = true;}
      if(LrjQlUESAb == XSZQiQadgU){TYfFjtpHwL = true;}
      else if(XSZQiQadgU == LrjQlUESAb){KBMbhBwbwU = true;}
      if(BIpYDOxbVq == iabhtCldFi){ZCxyRVWadN = true;}
      else if(iabhtCldFi == BIpYDOxbVq){hNQAGQzQPf = true;}
      if(TJuelmWXDC == lcVgSHSJjd){TeIiVEeAAH = true;}
      else if(lcVgSHSJjd == TJuelmWXDC){RFTcObbpht = true;}
      if(sYpYWpfEHR == MacDWkVcCb){KQaSejuohe = true;}
      else if(MacDWkVcCb == sYpYWpfEHR){OXymXXmOIX = true;}
      if(WLpaBpjbdR == WLHakSyqOR){EfXFClefJI = true;}
      if(JuiBcCwFdy == DRlImuwsya){hoZFIoQxjf = true;}
      if(ygPyhbSRBM == xRtDHIyYKJ){PpHnBIadSh = true;}
      while(WLHakSyqOR == WLpaBpjbdR){XOYpHEgFwz = true;}
      while(DRlImuwsya == DRlImuwsya){OHSXbFgiMG = true;}
      while(xRtDHIyYKJ == xRtDHIyYKJ){ZGtBFKOdbh = true;}
      if(gJbdMaUtuz == true){gJbdMaUtuz = false;}
      if(JbtSZtnTQb == true){JbtSZtnTQb = false;}
      if(nbdadFQESc == true){nbdadFQESc = false;}
      if(TYfFjtpHwL == true){TYfFjtpHwL = false;}
      if(ZCxyRVWadN == true){ZCxyRVWadN = false;}
      if(TeIiVEeAAH == true){TeIiVEeAAH = false;}
      if(KQaSejuohe == true){KQaSejuohe = false;}
      if(EfXFClefJI == true){EfXFClefJI = false;}
      if(hoZFIoQxjf == true){hoZFIoQxjf = false;}
      if(PpHnBIadSh == true){PpHnBIadSh = false;}
      if(ZgsyImGCgi == true){ZgsyImGCgi = false;}
      if(YzpqYUpVKp == true){YzpqYUpVKp = false;}
      if(SxFCPOYiEs == true){SxFCPOYiEs = false;}
      if(KBMbhBwbwU == true){KBMbhBwbwU = false;}
      if(hNQAGQzQPf == true){hNQAGQzQPf = false;}
      if(RFTcObbpht == true){RFTcObbpht = false;}
      if(OXymXXmOIX == true){OXymXXmOIX = false;}
      if(XOYpHEgFwz == true){XOYpHEgFwz = false;}
      if(OHSXbFgiMG == true){OHSXbFgiMG = false;}
      if(ZGtBFKOdbh == true){ZGtBFKOdbh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFSRPMIGUX
{ 
  void mEcPRYukua()
  { 
      bool ryPqpSrZCj = false;
      bool otnotuxTPx = false;
      bool JhgWQarmQQ = false;
      bool CFCerwqUXk = false;
      bool LCdBNYhaIO = false;
      bool HdBOZJRraO = false;
      bool aFJlhjqJxx = false;
      bool DbwdlGDeJq = false;
      bool rQeBIXDnFh = false;
      bool dztIKGsrTc = false;
      bool gYcKLfhXbS = false;
      bool FmiiVJZIdJ = false;
      bool gDDOSEhmTf = false;
      bool NLKfKSnTob = false;
      bool ofLmcqPKmA = false;
      bool fjOJwdVOqH = false;
      bool xuEwEtcDYC = false;
      bool VGSBTBqQlb = false;
      bool oXzSAcwAjf = false;
      bool xYbhetaPhh = false;
      string yKhgAaCxqm;
      string QndEeGmgWo;
      string CLaDDcitSp;
      string lSrybLkJHF;
      string ixqLORQRkW;
      string cXBGumjdcW;
      string qIeAAxufbS;
      string UcYQGFUPnl;
      string MRIuMOQlDo;
      string aHfkOZSpKR;
      string VkpRCzykAo;
      string RTppKZzinl;
      string gJclqMxnCf;
      string meFWPaaqrM;
      string PflNWHRpan;
      string aiBXjMIDZo;
      string CKhTBmOSZi;
      string yIpaVAWOOj;
      string uHMNEEcglD;
      string SWQCKFyRLj;
      if(yKhgAaCxqm == VkpRCzykAo){ryPqpSrZCj = true;}
      else if(VkpRCzykAo == yKhgAaCxqm){gYcKLfhXbS = true;}
      if(QndEeGmgWo == RTppKZzinl){otnotuxTPx = true;}
      else if(RTppKZzinl == QndEeGmgWo){FmiiVJZIdJ = true;}
      if(CLaDDcitSp == gJclqMxnCf){JhgWQarmQQ = true;}
      else if(gJclqMxnCf == CLaDDcitSp){gDDOSEhmTf = true;}
      if(lSrybLkJHF == meFWPaaqrM){CFCerwqUXk = true;}
      else if(meFWPaaqrM == lSrybLkJHF){NLKfKSnTob = true;}
      if(ixqLORQRkW == PflNWHRpan){LCdBNYhaIO = true;}
      else if(PflNWHRpan == ixqLORQRkW){ofLmcqPKmA = true;}
      if(cXBGumjdcW == aiBXjMIDZo){HdBOZJRraO = true;}
      else if(aiBXjMIDZo == cXBGumjdcW){fjOJwdVOqH = true;}
      if(qIeAAxufbS == CKhTBmOSZi){aFJlhjqJxx = true;}
      else if(CKhTBmOSZi == qIeAAxufbS){xuEwEtcDYC = true;}
      if(UcYQGFUPnl == yIpaVAWOOj){DbwdlGDeJq = true;}
      if(MRIuMOQlDo == uHMNEEcglD){rQeBIXDnFh = true;}
      if(aHfkOZSpKR == SWQCKFyRLj){dztIKGsrTc = true;}
      while(yIpaVAWOOj == UcYQGFUPnl){VGSBTBqQlb = true;}
      while(uHMNEEcglD == uHMNEEcglD){oXzSAcwAjf = true;}
      while(SWQCKFyRLj == SWQCKFyRLj){xYbhetaPhh = true;}
      if(ryPqpSrZCj == true){ryPqpSrZCj = false;}
      if(otnotuxTPx == true){otnotuxTPx = false;}
      if(JhgWQarmQQ == true){JhgWQarmQQ = false;}
      if(CFCerwqUXk == true){CFCerwqUXk = false;}
      if(LCdBNYhaIO == true){LCdBNYhaIO = false;}
      if(HdBOZJRraO == true){HdBOZJRraO = false;}
      if(aFJlhjqJxx == true){aFJlhjqJxx = false;}
      if(DbwdlGDeJq == true){DbwdlGDeJq = false;}
      if(rQeBIXDnFh == true){rQeBIXDnFh = false;}
      if(dztIKGsrTc == true){dztIKGsrTc = false;}
      if(gYcKLfhXbS == true){gYcKLfhXbS = false;}
      if(FmiiVJZIdJ == true){FmiiVJZIdJ = false;}
      if(gDDOSEhmTf == true){gDDOSEhmTf = false;}
      if(NLKfKSnTob == true){NLKfKSnTob = false;}
      if(ofLmcqPKmA == true){ofLmcqPKmA = false;}
      if(fjOJwdVOqH == true){fjOJwdVOqH = false;}
      if(xuEwEtcDYC == true){xuEwEtcDYC = false;}
      if(VGSBTBqQlb == true){VGSBTBqQlb = false;}
      if(oXzSAcwAjf == true){oXzSAcwAjf = false;}
      if(xYbhetaPhh == true){xYbhetaPhh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WOPSJBJVIH
{ 
  void sFHuGYOEaD()
  { 
      bool uaGmgrQTfX = false;
      bool wGfRGoPndo = false;
      bool PQaKkuAZpm = false;
      bool qQJNsaBOQf = false;
      bool AGQkZhGPUR = false;
      bool pspDydAuCl = false;
      bool rpcrffxSYf = false;
      bool nAXyoIzpkC = false;
      bool ojEYxyZFOO = false;
      bool aFMdnJcYEs = false;
      bool kmqncoUrOo = false;
      bool dJJzxHlDuh = false;
      bool FqDJFinsKe = false;
      bool fakrRBsPwH = false;
      bool cgqYjQuMgf = false;
      bool XYdWmsjgis = false;
      bool AbhiJDXRhw = false;
      bool NVHmFXAdZn = false;
      bool mbMdHGxOEY = false;
      bool QLgCGAzHPg = false;
      string XnttVCApLN;
      string nqywrEaGJu;
      string nekFOwpouM;
      string mYMNeyoFIE;
      string EASTHUrGyl;
      string OfEpbsCnfZ;
      string MKuzZPekRt;
      string OVyEpmLQyt;
      string DiqIxGUVll;
      string uBZhrsETsr;
      string pHnEWshzzn;
      string glpkVcTmCS;
      string tIzfyNuPMx;
      string hqXFEwumkE;
      string YUWxEJLnMO;
      string YRRZxhHIFJ;
      string xSlCFpOjgY;
      string hgBxtZkBbn;
      string CHCxXQZxIV;
      string nlgbGGhUrO;
      if(XnttVCApLN == pHnEWshzzn){uaGmgrQTfX = true;}
      else if(pHnEWshzzn == XnttVCApLN){kmqncoUrOo = true;}
      if(nqywrEaGJu == glpkVcTmCS){wGfRGoPndo = true;}
      else if(glpkVcTmCS == nqywrEaGJu){dJJzxHlDuh = true;}
      if(nekFOwpouM == tIzfyNuPMx){PQaKkuAZpm = true;}
      else if(tIzfyNuPMx == nekFOwpouM){FqDJFinsKe = true;}
      if(mYMNeyoFIE == hqXFEwumkE){qQJNsaBOQf = true;}
      else if(hqXFEwumkE == mYMNeyoFIE){fakrRBsPwH = true;}
      if(EASTHUrGyl == YUWxEJLnMO){AGQkZhGPUR = true;}
      else if(YUWxEJLnMO == EASTHUrGyl){cgqYjQuMgf = true;}
      if(OfEpbsCnfZ == YRRZxhHIFJ){pspDydAuCl = true;}
      else if(YRRZxhHIFJ == OfEpbsCnfZ){XYdWmsjgis = true;}
      if(MKuzZPekRt == xSlCFpOjgY){rpcrffxSYf = true;}
      else if(xSlCFpOjgY == MKuzZPekRt){AbhiJDXRhw = true;}
      if(OVyEpmLQyt == hgBxtZkBbn){nAXyoIzpkC = true;}
      if(DiqIxGUVll == CHCxXQZxIV){ojEYxyZFOO = true;}
      if(uBZhrsETsr == nlgbGGhUrO){aFMdnJcYEs = true;}
      while(hgBxtZkBbn == OVyEpmLQyt){NVHmFXAdZn = true;}
      while(CHCxXQZxIV == CHCxXQZxIV){mbMdHGxOEY = true;}
      while(nlgbGGhUrO == nlgbGGhUrO){QLgCGAzHPg = true;}
      if(uaGmgrQTfX == true){uaGmgrQTfX = false;}
      if(wGfRGoPndo == true){wGfRGoPndo = false;}
      if(PQaKkuAZpm == true){PQaKkuAZpm = false;}
      if(qQJNsaBOQf == true){qQJNsaBOQf = false;}
      if(AGQkZhGPUR == true){AGQkZhGPUR = false;}
      if(pspDydAuCl == true){pspDydAuCl = false;}
      if(rpcrffxSYf == true){rpcrffxSYf = false;}
      if(nAXyoIzpkC == true){nAXyoIzpkC = false;}
      if(ojEYxyZFOO == true){ojEYxyZFOO = false;}
      if(aFMdnJcYEs == true){aFMdnJcYEs = false;}
      if(kmqncoUrOo == true){kmqncoUrOo = false;}
      if(dJJzxHlDuh == true){dJJzxHlDuh = false;}
      if(FqDJFinsKe == true){FqDJFinsKe = false;}
      if(fakrRBsPwH == true){fakrRBsPwH = false;}
      if(cgqYjQuMgf == true){cgqYjQuMgf = false;}
      if(XYdWmsjgis == true){XYdWmsjgis = false;}
      if(AbhiJDXRhw == true){AbhiJDXRhw = false;}
      if(NVHmFXAdZn == true){NVHmFXAdZn = false;}
      if(mbMdHGxOEY == true){mbMdHGxOEY = false;}
      if(QLgCGAzHPg == true){QLgCGAzHPg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IUHBWSIJQX
{ 
  void mxBSastMFV()
  { 
      bool YPsqjkkaYd = false;
      bool KdIXzKTxVS = false;
      bool AdqcwYFYSS = false;
      bool rxuZIDhQKC = false;
      bool QkHhkxTYdh = false;
      bool hOCMDtXQuL = false;
      bool fLHFkNhhOu = false;
      bool cCmSBPWJrz = false;
      bool EfukkctiWO = false;
      bool eQVzWFcBwW = false;
      bool OlKhFebiKn = false;
      bool WNYuGAQVTI = false;
      bool TzLAPLfmww = false;
      bool lVNUjRVMfF = false;
      bool AKXhqQrZrW = false;
      bool nGgmDOZJRs = false;
      bool zomNBBADLo = false;
      bool dDpOHIbcIy = false;
      bool SFuZIfnZRV = false;
      bool qLulGLXKgo = false;
      string uWUrzJNUGh;
      string cEphyStTuw;
      string QIZdcjygRE;
      string KlcANOKhfN;
      string ZofLlNWCGO;
      string rjGHnlwqPP;
      string LgCCWpaoUi;
      string HMmhVbbNqO;
      string MuaDLZeVMa;
      string RTSQBsldou;
      string lggWGfxYlL;
      string KizACPFyqw;
      string LFbtQmsVfb;
      string pyYwbfODwe;
      string cFiBPiTRNk;
      string nmlrjgElFS;
      string lasKVLKDXW;
      string BCCLTFVadh;
      string TbHunCLfLu;
      string abxcrBMYfD;
      if(uWUrzJNUGh == lggWGfxYlL){YPsqjkkaYd = true;}
      else if(lggWGfxYlL == uWUrzJNUGh){OlKhFebiKn = true;}
      if(cEphyStTuw == KizACPFyqw){KdIXzKTxVS = true;}
      else if(KizACPFyqw == cEphyStTuw){WNYuGAQVTI = true;}
      if(QIZdcjygRE == LFbtQmsVfb){AdqcwYFYSS = true;}
      else if(LFbtQmsVfb == QIZdcjygRE){TzLAPLfmww = true;}
      if(KlcANOKhfN == pyYwbfODwe){rxuZIDhQKC = true;}
      else if(pyYwbfODwe == KlcANOKhfN){lVNUjRVMfF = true;}
      if(ZofLlNWCGO == cFiBPiTRNk){QkHhkxTYdh = true;}
      else if(cFiBPiTRNk == ZofLlNWCGO){AKXhqQrZrW = true;}
      if(rjGHnlwqPP == nmlrjgElFS){hOCMDtXQuL = true;}
      else if(nmlrjgElFS == rjGHnlwqPP){nGgmDOZJRs = true;}
      if(LgCCWpaoUi == lasKVLKDXW){fLHFkNhhOu = true;}
      else if(lasKVLKDXW == LgCCWpaoUi){zomNBBADLo = true;}
      if(HMmhVbbNqO == BCCLTFVadh){cCmSBPWJrz = true;}
      if(MuaDLZeVMa == TbHunCLfLu){EfukkctiWO = true;}
      if(RTSQBsldou == abxcrBMYfD){eQVzWFcBwW = true;}
      while(BCCLTFVadh == HMmhVbbNqO){dDpOHIbcIy = true;}
      while(TbHunCLfLu == TbHunCLfLu){SFuZIfnZRV = true;}
      while(abxcrBMYfD == abxcrBMYfD){qLulGLXKgo = true;}
      if(YPsqjkkaYd == true){YPsqjkkaYd = false;}
      if(KdIXzKTxVS == true){KdIXzKTxVS = false;}
      if(AdqcwYFYSS == true){AdqcwYFYSS = false;}
      if(rxuZIDhQKC == true){rxuZIDhQKC = false;}
      if(QkHhkxTYdh == true){QkHhkxTYdh = false;}
      if(hOCMDtXQuL == true){hOCMDtXQuL = false;}
      if(fLHFkNhhOu == true){fLHFkNhhOu = false;}
      if(cCmSBPWJrz == true){cCmSBPWJrz = false;}
      if(EfukkctiWO == true){EfukkctiWO = false;}
      if(eQVzWFcBwW == true){eQVzWFcBwW = false;}
      if(OlKhFebiKn == true){OlKhFebiKn = false;}
      if(WNYuGAQVTI == true){WNYuGAQVTI = false;}
      if(TzLAPLfmww == true){TzLAPLfmww = false;}
      if(lVNUjRVMfF == true){lVNUjRVMfF = false;}
      if(AKXhqQrZrW == true){AKXhqQrZrW = false;}
      if(nGgmDOZJRs == true){nGgmDOZJRs = false;}
      if(zomNBBADLo == true){zomNBBADLo = false;}
      if(dDpOHIbcIy == true){dDpOHIbcIy = false;}
      if(SFuZIfnZRV == true){SFuZIfnZRV = false;}
      if(qLulGLXKgo == true){qLulGLXKgo = false;}
    } 
}; 
