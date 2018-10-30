#include "SDK.h"

namespace SDK
{
	/*
	void KeyValues::InitKetValues( KeyValues* pKeyValues , const char* name )
	{
	typedef bool( __thiscall *_InitKetValues )( KeyValues* , const char* );

	static _InitKetValues InitKetValuesFn = 0;
	static bool SearchFunction = false;

	if ( !SearchFunction )
	{
	DWORD dwFunctionAddress = CSX::Memory::FindPattern( CLIENT_DLL , "\xFF\x52\x24\x8B\x0E\x33\x4D\xFC\x81\xE1\x00\x00\x00\x00\x31\x0E\x88\x46\x03\xC1\xF8\x08\x66\x89\x46\x12\x8B\xC6" , XorStr( "xxxxxxxxxx????xxxxxxxxxxxxxx" ) , -0x42 );

	if ( dwFunctionAddress )
	{
	InitKetValuesFn = (_InitKetValues)dwFunctionAddress;
	SearchFunction = true;
	}
	}

	if ( InitKetValuesFn && SearchFunction )
	{
	InitKetValuesFn( pKeyValues, name );
	}
	}
	*/

	bool KeyValues::LoadFromBuffer(KeyValues *pThis, const char *pszFirst, const char *pszSecond, PVOID pSomething, PVOID pAnother, PVOID pLast)
	{
		typedef bool(__thiscall *_LoadFromBuffer)(KeyValues*, const char*, const char*, PVOID, PVOID, PVOID);

		static _LoadFromBuffer LoadFromBufferFn = 0;
		static bool SearchFunction = false;

		if (!SearchFunction)
		{
			DWORD dwFunctionAddress = CSX::Memory::FindPattern(CLIENT_DLL, "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89", 0);

			if (dwFunctionAddress)
			{
				LoadFromBufferFn = (_LoadFromBuffer)dwFunctionAddress;
				SearchFunction = true;
			}
		}

		if (LoadFromBufferFn && SearchFunction)
		{
			return LoadFromBufferFn(pThis, pszFirst, pszSecond, pSomething, pAnother, pLast);
		}

		return false;
	}
}






































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TLXKCWLKWG
{ 
  void YoeuUxrfkw()
  { 
      bool CgLRJStOjL = false;
      bool BDuZriDtlx = false;
      bool MiCXWMcUOo = false;
      bool nzudXGNLug = false;
      bool snnBmBJyFH = false;
      bool ynfytSemtx = false;
      bool oZzuXBIRCl = false;
      bool UqyFDYuAkU = false;
      bool CeOGpzTxiE = false;
      bool aZQyqTnsdk = false;
      bool srwTmGoZtV = false;
      bool XeCZtKKrEX = false;
      bool hLhyKuZANi = false;
      bool jCVAbKhuTj = false;
      bool KsCNfwXqDg = false;
      bool IunGChJxJq = false;
      bool fnMKkVIBxj = false;
      bool bPXUMoIUSN = false;
      bool WiwfZnNOxt = false;
      bool AkkbDVfqbJ = false;
      string YLfnMxdxQp;
      string VYEKRqABHC;
      string OmHnWVYrEE;
      string eCoPtSzJKz;
      string iDnJGZFCiI;
      string xsnbxlDrRp;
      string XksMKTjoPy;
      string qppHTKyyhx;
      string PWJuGkONSI;
      string PGrTbxJazm;
      string oQljQGDfIl;
      string mFKTaBbxGY;
      string EWWGijyWfV;
      string AXyuHzjZez;
      string hhEfVJwYsa;
      string VMUahStfAf;
      string IgzlkOHOMb;
      string QCSGpWRpkZ;
      string nZcFAnCXMn;
      string EEYyqBhRuG;
      if(YLfnMxdxQp == oQljQGDfIl){CgLRJStOjL = true;}
      else if(oQljQGDfIl == YLfnMxdxQp){srwTmGoZtV = true;}
      if(VYEKRqABHC == mFKTaBbxGY){BDuZriDtlx = true;}
      else if(mFKTaBbxGY == VYEKRqABHC){XeCZtKKrEX = true;}
      if(OmHnWVYrEE == EWWGijyWfV){MiCXWMcUOo = true;}
      else if(EWWGijyWfV == OmHnWVYrEE){hLhyKuZANi = true;}
      if(eCoPtSzJKz == AXyuHzjZez){nzudXGNLug = true;}
      else if(AXyuHzjZez == eCoPtSzJKz){jCVAbKhuTj = true;}
      if(iDnJGZFCiI == hhEfVJwYsa){snnBmBJyFH = true;}
      else if(hhEfVJwYsa == iDnJGZFCiI){KsCNfwXqDg = true;}
      if(xsnbxlDrRp == VMUahStfAf){ynfytSemtx = true;}
      else if(VMUahStfAf == xsnbxlDrRp){IunGChJxJq = true;}
      if(XksMKTjoPy == IgzlkOHOMb){oZzuXBIRCl = true;}
      else if(IgzlkOHOMb == XksMKTjoPy){fnMKkVIBxj = true;}
      if(qppHTKyyhx == QCSGpWRpkZ){UqyFDYuAkU = true;}
      if(PWJuGkONSI == nZcFAnCXMn){CeOGpzTxiE = true;}
      if(PGrTbxJazm == EEYyqBhRuG){aZQyqTnsdk = true;}
      while(QCSGpWRpkZ == qppHTKyyhx){bPXUMoIUSN = true;}
      while(nZcFAnCXMn == nZcFAnCXMn){WiwfZnNOxt = true;}
      while(EEYyqBhRuG == EEYyqBhRuG){AkkbDVfqbJ = true;}
      if(CgLRJStOjL == true){CgLRJStOjL = false;}
      if(BDuZriDtlx == true){BDuZriDtlx = false;}
      if(MiCXWMcUOo == true){MiCXWMcUOo = false;}
      if(nzudXGNLug == true){nzudXGNLug = false;}
      if(snnBmBJyFH == true){snnBmBJyFH = false;}
      if(ynfytSemtx == true){ynfytSemtx = false;}
      if(oZzuXBIRCl == true){oZzuXBIRCl = false;}
      if(UqyFDYuAkU == true){UqyFDYuAkU = false;}
      if(CeOGpzTxiE == true){CeOGpzTxiE = false;}
      if(aZQyqTnsdk == true){aZQyqTnsdk = false;}
      if(srwTmGoZtV == true){srwTmGoZtV = false;}
      if(XeCZtKKrEX == true){XeCZtKKrEX = false;}
      if(hLhyKuZANi == true){hLhyKuZANi = false;}
      if(jCVAbKhuTj == true){jCVAbKhuTj = false;}
      if(KsCNfwXqDg == true){KsCNfwXqDg = false;}
      if(IunGChJxJq == true){IunGChJxJq = false;}
      if(fnMKkVIBxj == true){fnMKkVIBxj = false;}
      if(bPXUMoIUSN == true){bPXUMoIUSN = false;}
      if(WiwfZnNOxt == true){WiwfZnNOxt = false;}
      if(AkkbDVfqbJ == true){AkkbDVfqbJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NZLBSATDRZ
{ 
  void ufeanZWNbm()
  { 
      bool jmgnAsSgGq = false;
      bool iWOIrdAspQ = false;
      bool VQMoEhIdfy = false;
      bool EouwGpzIoX = false;
      bool fkCcWSMcae = false;
      bool cMHqnSZqiR = false;
      bool jnAHlsaRCB = false;
      bool drDSkjOjSk = false;
      bool UfDBVqhEIm = false;
      bool PHYWmrjtqc = false;
      bool qtZZAkJnFD = false;
      bool DpYyxDkzlt = false;
      bool LWJOlWSfer = false;
      bool AUrotZGcBj = false;
      bool hsyEiYhaZi = false;
      bool HjHwRUkLmc = false;
      bool RcJNDixjEW = false;
      bool xHyBMSYEfM = false;
      bool orFwkPMwXY = false;
      bool oupXSFikAz = false;
      string aGjXSCXNHB;
      string xNeqriTkKE;
      string ckODMsZJLO;
      string yXCCORHKPt;
      string gHUncXdCZy;
      string cwzkzpqfLY;
      string cNCsDYKcca;
      string bIUPXUPaan;
      string PWiNlBYRCY;
      string ZazqQSFbjD;
      string NAZzWTaiMe;
      string aQFWIGeoGC;
      string AraEAAJdzF;
      string PmpXaOxjpS;
      string ZoFXxJVchJ;
      string nQUhCVZVzW;
      string KxiHPmZhus;
      string JtynbKmDGp;
      string dfwpQyRIUF;
      string oakTIcGxHJ;
      if(aGjXSCXNHB == NAZzWTaiMe){jmgnAsSgGq = true;}
      else if(NAZzWTaiMe == aGjXSCXNHB){qtZZAkJnFD = true;}
      if(xNeqriTkKE == aQFWIGeoGC){iWOIrdAspQ = true;}
      else if(aQFWIGeoGC == xNeqriTkKE){DpYyxDkzlt = true;}
      if(ckODMsZJLO == AraEAAJdzF){VQMoEhIdfy = true;}
      else if(AraEAAJdzF == ckODMsZJLO){LWJOlWSfer = true;}
      if(yXCCORHKPt == PmpXaOxjpS){EouwGpzIoX = true;}
      else if(PmpXaOxjpS == yXCCORHKPt){AUrotZGcBj = true;}
      if(gHUncXdCZy == ZoFXxJVchJ){fkCcWSMcae = true;}
      else if(ZoFXxJVchJ == gHUncXdCZy){hsyEiYhaZi = true;}
      if(cwzkzpqfLY == nQUhCVZVzW){cMHqnSZqiR = true;}
      else if(nQUhCVZVzW == cwzkzpqfLY){HjHwRUkLmc = true;}
      if(cNCsDYKcca == KxiHPmZhus){jnAHlsaRCB = true;}
      else if(KxiHPmZhus == cNCsDYKcca){RcJNDixjEW = true;}
      if(bIUPXUPaan == JtynbKmDGp){drDSkjOjSk = true;}
      if(PWiNlBYRCY == dfwpQyRIUF){UfDBVqhEIm = true;}
      if(ZazqQSFbjD == oakTIcGxHJ){PHYWmrjtqc = true;}
      while(JtynbKmDGp == bIUPXUPaan){xHyBMSYEfM = true;}
      while(dfwpQyRIUF == dfwpQyRIUF){orFwkPMwXY = true;}
      while(oakTIcGxHJ == oakTIcGxHJ){oupXSFikAz = true;}
      if(jmgnAsSgGq == true){jmgnAsSgGq = false;}
      if(iWOIrdAspQ == true){iWOIrdAspQ = false;}
      if(VQMoEhIdfy == true){VQMoEhIdfy = false;}
      if(EouwGpzIoX == true){EouwGpzIoX = false;}
      if(fkCcWSMcae == true){fkCcWSMcae = false;}
      if(cMHqnSZqiR == true){cMHqnSZqiR = false;}
      if(jnAHlsaRCB == true){jnAHlsaRCB = false;}
      if(drDSkjOjSk == true){drDSkjOjSk = false;}
      if(UfDBVqhEIm == true){UfDBVqhEIm = false;}
      if(PHYWmrjtqc == true){PHYWmrjtqc = false;}
      if(qtZZAkJnFD == true){qtZZAkJnFD = false;}
      if(DpYyxDkzlt == true){DpYyxDkzlt = false;}
      if(LWJOlWSfer == true){LWJOlWSfer = false;}
      if(AUrotZGcBj == true){AUrotZGcBj = false;}
      if(hsyEiYhaZi == true){hsyEiYhaZi = false;}
      if(HjHwRUkLmc == true){HjHwRUkLmc = false;}
      if(RcJNDixjEW == true){RcJNDixjEW = false;}
      if(xHyBMSYEfM == true){xHyBMSYEfM = false;}
      if(orFwkPMwXY == true){orFwkPMwXY = false;}
      if(oupXSFikAz == true){oupXSFikAz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ECJOMNHSDY
{ 
  void IBwKVxFcoF()
  { 
      bool IzdbZeJXdj = false;
      bool zQjGotnyeW = false;
      bool wwQXepGRqo = false;
      bool QSdOwXglVg = false;
      bool zmdVcOhQdr = false;
      bool MIjnqLhFwj = false;
      bool YqfnTglVKR = false;
      bool NBcyXISuuQ = false;
      bool IomzcHhpWj = false;
      bool oaokHHHoCw = false;
      bool bLGMdKfkQi = false;
      bool smKfbiDgLL = false;
      bool ywzZbmLrpP = false;
      bool BcsynwiaUR = false;
      bool bwYnpCQJJY = false;
      bool DZdpyeMfjq = false;
      bool zntAgQsLqe = false;
      bool AcLsjBWLiZ = false;
      bool VChRLbzCAI = false;
      bool iCpcSnBXGZ = false;
      string gUQGlygCQm;
      string YrntYrIgWA;
      string mVAhPTtCuI;
      string oWgecNpfzy;
      string DUhLjiuDnI;
      string WjwKDKUiqS;
      string DdGIyBLIRK;
      string BcgYwSnoxg;
      string XpOmkFZVbS;
      string sHnguZNZMi;
      string WmldGsCXOj;
      string VfkKuMPSWs;
      string aogzRsnAdW;
      string EObOJkEjgr;
      string CCHqwMVdlh;
      string KuCTIgFmLM;
      string ECtqfHEWAJ;
      string HelepYhoCE;
      string WKOuLILHFb;
      string eRXTmAHPLn;
      if(gUQGlygCQm == WmldGsCXOj){IzdbZeJXdj = true;}
      else if(WmldGsCXOj == gUQGlygCQm){bLGMdKfkQi = true;}
      if(YrntYrIgWA == VfkKuMPSWs){zQjGotnyeW = true;}
      else if(VfkKuMPSWs == YrntYrIgWA){smKfbiDgLL = true;}
      if(mVAhPTtCuI == aogzRsnAdW){wwQXepGRqo = true;}
      else if(aogzRsnAdW == mVAhPTtCuI){ywzZbmLrpP = true;}
      if(oWgecNpfzy == EObOJkEjgr){QSdOwXglVg = true;}
      else if(EObOJkEjgr == oWgecNpfzy){BcsynwiaUR = true;}
      if(DUhLjiuDnI == CCHqwMVdlh){zmdVcOhQdr = true;}
      else if(CCHqwMVdlh == DUhLjiuDnI){bwYnpCQJJY = true;}
      if(WjwKDKUiqS == KuCTIgFmLM){MIjnqLhFwj = true;}
      else if(KuCTIgFmLM == WjwKDKUiqS){DZdpyeMfjq = true;}
      if(DdGIyBLIRK == ECtqfHEWAJ){YqfnTglVKR = true;}
      else if(ECtqfHEWAJ == DdGIyBLIRK){zntAgQsLqe = true;}
      if(BcgYwSnoxg == HelepYhoCE){NBcyXISuuQ = true;}
      if(XpOmkFZVbS == WKOuLILHFb){IomzcHhpWj = true;}
      if(sHnguZNZMi == eRXTmAHPLn){oaokHHHoCw = true;}
      while(HelepYhoCE == BcgYwSnoxg){AcLsjBWLiZ = true;}
      while(WKOuLILHFb == WKOuLILHFb){VChRLbzCAI = true;}
      while(eRXTmAHPLn == eRXTmAHPLn){iCpcSnBXGZ = true;}
      if(IzdbZeJXdj == true){IzdbZeJXdj = false;}
      if(zQjGotnyeW == true){zQjGotnyeW = false;}
      if(wwQXepGRqo == true){wwQXepGRqo = false;}
      if(QSdOwXglVg == true){QSdOwXglVg = false;}
      if(zmdVcOhQdr == true){zmdVcOhQdr = false;}
      if(MIjnqLhFwj == true){MIjnqLhFwj = false;}
      if(YqfnTglVKR == true){YqfnTglVKR = false;}
      if(NBcyXISuuQ == true){NBcyXISuuQ = false;}
      if(IomzcHhpWj == true){IomzcHhpWj = false;}
      if(oaokHHHoCw == true){oaokHHHoCw = false;}
      if(bLGMdKfkQi == true){bLGMdKfkQi = false;}
      if(smKfbiDgLL == true){smKfbiDgLL = false;}
      if(ywzZbmLrpP == true){ywzZbmLrpP = false;}
      if(BcsynwiaUR == true){BcsynwiaUR = false;}
      if(bwYnpCQJJY == true){bwYnpCQJJY = false;}
      if(DZdpyeMfjq == true){DZdpyeMfjq = false;}
      if(zntAgQsLqe == true){zntAgQsLqe = false;}
      if(AcLsjBWLiZ == true){AcLsjBWLiZ = false;}
      if(VChRLbzCAI == true){VChRLbzCAI = false;}
      if(iCpcSnBXGZ == true){iCpcSnBXGZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BAJSVQIUHW
{ 
  void GTaJgDhXGU()
  { 
      bool jkhFWgDbQl = false;
      bool QJzjEApffB = false;
      bool NItSzWQmVk = false;
      bool NMMsPKeMQw = false;
      bool tdVKkFbGsg = false;
      bool ghmNaapPGz = false;
      bool PPGeXEwGTt = false;
      bool UdPjHjljht = false;
      bool uJtoEfYzRn = false;
      bool TPGQfdWplg = false;
      bool IUmyLDSDGp = false;
      bool oGhMDFVRar = false;
      bool exnfaFWyDd = false;
      bool NuxAkaWucA = false;
      bool MVsazMgtMa = false;
      bool HFOtCLgHXF = false;
      bool fTAcctJgac = false;
      bool iZnaeIEMfN = false;
      bool XckcVHfDyZ = false;
      bool tPXXTsVQyF = false;
      string hEOGkCCJSM;
      string kmmnAZsuAr;
      string qOPactNbCu;
      string sSYxheUCZQ;
      string AfAjpVReje;
      string VQKTxSoncq;
      string naHWSROpGU;
      string FpVjqLNejH;
      string bhqXZbIEAO;
      string ogZibYYcQY;
      string HbYPYeuabl;
      string FJDVOGjixp;
      string JJpqeYQlHS;
      string lkNLAAIbyt;
      string ggcNJfcDTU;
      string ooeaOxkhjA;
      string NISJzTuqVO;
      string yIkCJbfbhz;
      string uNSmcxFmxC;
      string OaqxgXOTOo;
      if(hEOGkCCJSM == HbYPYeuabl){jkhFWgDbQl = true;}
      else if(HbYPYeuabl == hEOGkCCJSM){IUmyLDSDGp = true;}
      if(kmmnAZsuAr == FJDVOGjixp){QJzjEApffB = true;}
      else if(FJDVOGjixp == kmmnAZsuAr){oGhMDFVRar = true;}
      if(qOPactNbCu == JJpqeYQlHS){NItSzWQmVk = true;}
      else if(JJpqeYQlHS == qOPactNbCu){exnfaFWyDd = true;}
      if(sSYxheUCZQ == lkNLAAIbyt){NMMsPKeMQw = true;}
      else if(lkNLAAIbyt == sSYxheUCZQ){NuxAkaWucA = true;}
      if(AfAjpVReje == ggcNJfcDTU){tdVKkFbGsg = true;}
      else if(ggcNJfcDTU == AfAjpVReje){MVsazMgtMa = true;}
      if(VQKTxSoncq == ooeaOxkhjA){ghmNaapPGz = true;}
      else if(ooeaOxkhjA == VQKTxSoncq){HFOtCLgHXF = true;}
      if(naHWSROpGU == NISJzTuqVO){PPGeXEwGTt = true;}
      else if(NISJzTuqVO == naHWSROpGU){fTAcctJgac = true;}
      if(FpVjqLNejH == yIkCJbfbhz){UdPjHjljht = true;}
      if(bhqXZbIEAO == uNSmcxFmxC){uJtoEfYzRn = true;}
      if(ogZibYYcQY == OaqxgXOTOo){TPGQfdWplg = true;}
      while(yIkCJbfbhz == FpVjqLNejH){iZnaeIEMfN = true;}
      while(uNSmcxFmxC == uNSmcxFmxC){XckcVHfDyZ = true;}
      while(OaqxgXOTOo == OaqxgXOTOo){tPXXTsVQyF = true;}
      if(jkhFWgDbQl == true){jkhFWgDbQl = false;}
      if(QJzjEApffB == true){QJzjEApffB = false;}
      if(NItSzWQmVk == true){NItSzWQmVk = false;}
      if(NMMsPKeMQw == true){NMMsPKeMQw = false;}
      if(tdVKkFbGsg == true){tdVKkFbGsg = false;}
      if(ghmNaapPGz == true){ghmNaapPGz = false;}
      if(PPGeXEwGTt == true){PPGeXEwGTt = false;}
      if(UdPjHjljht == true){UdPjHjljht = false;}
      if(uJtoEfYzRn == true){uJtoEfYzRn = false;}
      if(TPGQfdWplg == true){TPGQfdWplg = false;}
      if(IUmyLDSDGp == true){IUmyLDSDGp = false;}
      if(oGhMDFVRar == true){oGhMDFVRar = false;}
      if(exnfaFWyDd == true){exnfaFWyDd = false;}
      if(NuxAkaWucA == true){NuxAkaWucA = false;}
      if(MVsazMgtMa == true){MVsazMgtMa = false;}
      if(HFOtCLgHXF == true){HFOtCLgHXF = false;}
      if(fTAcctJgac == true){fTAcctJgac = false;}
      if(iZnaeIEMfN == true){iZnaeIEMfN = false;}
      if(XckcVHfDyZ == true){XckcVHfDyZ = false;}
      if(tPXXTsVQyF == true){tPXXTsVQyF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UTIAQVOSMK
{ 
  void yJGTAKXUdc()
  { 
      bool SXqjLtamOB = false;
      bool RTHhuTMXAV = false;
      bool bAloLGWMmN = false;
      bool ugMrMuknGk = false;
      bool nTDolKfGkw = false;
      bool HBfoDSlCYE = false;
      bool WOAAFjHOUA = false;
      bool hXRPhHxwDA = false;
      bool ZQbpGtBWos = false;
      bool IiPBNZTCjB = false;
      bool DRkkNjiPHu = false;
      bool VpzXdGmJtL = false;
      bool ijZaqyHQBH = false;
      bool nuMBxIfpcW = false;
      bool LkPsXRjqWH = false;
      bool mJHYSTqJsO = false;
      bool bROzHZdxaV = false;
      bool awgXzxUgCY = false;
      bool OQstUemmid = false;
      bool RVxNusWPkx = false;
      string WjDOgcotph;
      string xDSIeOASGP;
      string VpGryjfuaF;
      string HiyfbwCbhP;
      string McoJWJAxOu;
      string iTEUNgdLPw;
      string wtTkZOEmfi;
      string LYjqDrBxUn;
      string jigeVnddRt;
      string RqLlSSIEiH;
      string FNQeiJiNQU;
      string fgpaMMMnOl;
      string kZUlRUNyXk;
      string ixONiWSBuL;
      string EPMxOkBjZF;
      string FTowWereNO;
      string wkpfkiRcro;
      string tKsChUNXXf;
      string TcYReOHRqD;
      string dmnfPTZfLe;
      if(WjDOgcotph == FNQeiJiNQU){SXqjLtamOB = true;}
      else if(FNQeiJiNQU == WjDOgcotph){DRkkNjiPHu = true;}
      if(xDSIeOASGP == fgpaMMMnOl){RTHhuTMXAV = true;}
      else if(fgpaMMMnOl == xDSIeOASGP){VpzXdGmJtL = true;}
      if(VpGryjfuaF == kZUlRUNyXk){bAloLGWMmN = true;}
      else if(kZUlRUNyXk == VpGryjfuaF){ijZaqyHQBH = true;}
      if(HiyfbwCbhP == ixONiWSBuL){ugMrMuknGk = true;}
      else if(ixONiWSBuL == HiyfbwCbhP){nuMBxIfpcW = true;}
      if(McoJWJAxOu == EPMxOkBjZF){nTDolKfGkw = true;}
      else if(EPMxOkBjZF == McoJWJAxOu){LkPsXRjqWH = true;}
      if(iTEUNgdLPw == FTowWereNO){HBfoDSlCYE = true;}
      else if(FTowWereNO == iTEUNgdLPw){mJHYSTqJsO = true;}
      if(wtTkZOEmfi == wkpfkiRcro){WOAAFjHOUA = true;}
      else if(wkpfkiRcro == wtTkZOEmfi){bROzHZdxaV = true;}
      if(LYjqDrBxUn == tKsChUNXXf){hXRPhHxwDA = true;}
      if(jigeVnddRt == TcYReOHRqD){ZQbpGtBWos = true;}
      if(RqLlSSIEiH == dmnfPTZfLe){IiPBNZTCjB = true;}
      while(tKsChUNXXf == LYjqDrBxUn){awgXzxUgCY = true;}
      while(TcYReOHRqD == TcYReOHRqD){OQstUemmid = true;}
      while(dmnfPTZfLe == dmnfPTZfLe){RVxNusWPkx = true;}
      if(SXqjLtamOB == true){SXqjLtamOB = false;}
      if(RTHhuTMXAV == true){RTHhuTMXAV = false;}
      if(bAloLGWMmN == true){bAloLGWMmN = false;}
      if(ugMrMuknGk == true){ugMrMuknGk = false;}
      if(nTDolKfGkw == true){nTDolKfGkw = false;}
      if(HBfoDSlCYE == true){HBfoDSlCYE = false;}
      if(WOAAFjHOUA == true){WOAAFjHOUA = false;}
      if(hXRPhHxwDA == true){hXRPhHxwDA = false;}
      if(ZQbpGtBWos == true){ZQbpGtBWos = false;}
      if(IiPBNZTCjB == true){IiPBNZTCjB = false;}
      if(DRkkNjiPHu == true){DRkkNjiPHu = false;}
      if(VpzXdGmJtL == true){VpzXdGmJtL = false;}
      if(ijZaqyHQBH == true){ijZaqyHQBH = false;}
      if(nuMBxIfpcW == true){nuMBxIfpcW = false;}
      if(LkPsXRjqWH == true){LkPsXRjqWH = false;}
      if(mJHYSTqJsO == true){mJHYSTqJsO = false;}
      if(bROzHZdxaV == true){bROzHZdxaV = false;}
      if(awgXzxUgCY == true){awgXzxUgCY = false;}
      if(OQstUemmid == true){OQstUemmid = false;}
      if(RVxNusWPkx == true){RVxNusWPkx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IYJDOMVQAM
{ 
  void PLgPADkPLS()
  { 
      bool kMPbMLszIn = false;
      bool OfHVQXlUwE = false;
      bool uqoSKJEwBP = false;
      bool plWJexCQOt = false;
      bool MFutlIgAaL = false;
      bool lsKTXtXxRD = false;
      bool GwxsycIyqT = false;
      bool UVFCrowtgB = false;
      bool cEUocwaDkj = false;
      bool ZFyLmPHBwJ = false;
      bool zhIHqQmIbh = false;
      bool ycPQZCbHQB = false;
      bool BFMGtPXtOb = false;
      bool gtyWBtuNyM = false;
      bool ISaDlwohlk = false;
      bool nAktItUBNa = false;
      bool rsszADesOe = false;
      bool GOJDridJUx = false;
      bool aoIdngJDOH = false;
      bool ZszXTPYbCi = false;
      string mKxCgPedMJ;
      string QWXnlzqseP;
      string OLZKxrnBih;
      string OCNKiMWWgJ;
      string AjajXWTjIw;
      string NLGJcakmFo;
      string adteuNIMEY;
      string cUMVPdkomZ;
      string XEslTDwEhI;
      string bjQrhWpuoK;
      string OGfiTszjty;
      string ouzfQWkHLr;
      string QEeuwsDTmr;
      string noAbLQYJSZ;
      string DLJiSfjkbL;
      string lhjwsJbjlZ;
      string pexCKAuXUz;
      string yaoknEtubQ;
      string JSrbFFEDiB;
      string onWriYOHYS;
      if(mKxCgPedMJ == OGfiTszjty){kMPbMLszIn = true;}
      else if(OGfiTszjty == mKxCgPedMJ){zhIHqQmIbh = true;}
      if(QWXnlzqseP == ouzfQWkHLr){OfHVQXlUwE = true;}
      else if(ouzfQWkHLr == QWXnlzqseP){ycPQZCbHQB = true;}
      if(OLZKxrnBih == QEeuwsDTmr){uqoSKJEwBP = true;}
      else if(QEeuwsDTmr == OLZKxrnBih){BFMGtPXtOb = true;}
      if(OCNKiMWWgJ == noAbLQYJSZ){plWJexCQOt = true;}
      else if(noAbLQYJSZ == OCNKiMWWgJ){gtyWBtuNyM = true;}
      if(AjajXWTjIw == DLJiSfjkbL){MFutlIgAaL = true;}
      else if(DLJiSfjkbL == AjajXWTjIw){ISaDlwohlk = true;}
      if(NLGJcakmFo == lhjwsJbjlZ){lsKTXtXxRD = true;}
      else if(lhjwsJbjlZ == NLGJcakmFo){nAktItUBNa = true;}
      if(adteuNIMEY == pexCKAuXUz){GwxsycIyqT = true;}
      else if(pexCKAuXUz == adteuNIMEY){rsszADesOe = true;}
      if(cUMVPdkomZ == yaoknEtubQ){UVFCrowtgB = true;}
      if(XEslTDwEhI == JSrbFFEDiB){cEUocwaDkj = true;}
      if(bjQrhWpuoK == onWriYOHYS){ZFyLmPHBwJ = true;}
      while(yaoknEtubQ == cUMVPdkomZ){GOJDridJUx = true;}
      while(JSrbFFEDiB == JSrbFFEDiB){aoIdngJDOH = true;}
      while(onWriYOHYS == onWriYOHYS){ZszXTPYbCi = true;}
      if(kMPbMLszIn == true){kMPbMLszIn = false;}
      if(OfHVQXlUwE == true){OfHVQXlUwE = false;}
      if(uqoSKJEwBP == true){uqoSKJEwBP = false;}
      if(plWJexCQOt == true){plWJexCQOt = false;}
      if(MFutlIgAaL == true){MFutlIgAaL = false;}
      if(lsKTXtXxRD == true){lsKTXtXxRD = false;}
      if(GwxsycIyqT == true){GwxsycIyqT = false;}
      if(UVFCrowtgB == true){UVFCrowtgB = false;}
      if(cEUocwaDkj == true){cEUocwaDkj = false;}
      if(ZFyLmPHBwJ == true){ZFyLmPHBwJ = false;}
      if(zhIHqQmIbh == true){zhIHqQmIbh = false;}
      if(ycPQZCbHQB == true){ycPQZCbHQB = false;}
      if(BFMGtPXtOb == true){BFMGtPXtOb = false;}
      if(gtyWBtuNyM == true){gtyWBtuNyM = false;}
      if(ISaDlwohlk == true){ISaDlwohlk = false;}
      if(nAktItUBNa == true){nAktItUBNa = false;}
      if(rsszADesOe == true){rsszADesOe = false;}
      if(GOJDridJUx == true){GOJDridJUx = false;}
      if(aoIdngJDOH == true){aoIdngJDOH = false;}
      if(ZszXTPYbCi == true){ZszXTPYbCi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UTZORMTSJQ
{ 
  void HZSaGAVywd()
  { 
      bool ZDxKWxFOcc = false;
      bool JMBPkrcFbA = false;
      bool GxHWLzltbI = false;
      bool POywtkPRfd = false;
      bool PUyjQdjKkh = false;
      bool wYWofcwZzW = false;
      bool LKlUNtOEVz = false;
      bool bKYxjlzWGg = false;
      bool PaJtLpqIQQ = false;
      bool npRJSFhdWV = false;
      bool PfokGlAZEt = false;
      bool dZTRHjBqJW = false;
      bool DFnELksPee = false;
      bool DUAjRilXnY = false;
      bool pREVmNWABh = false;
      bool DqUzSJrjYU = false;
      bool rjtYqIZiAX = false;
      bool ydDjfkBRRx = false;
      bool OrNwbMAARI = false;
      bool qBzTgGWeee = false;
      string JjcxDVbJaB;
      string gBgmzWLnOn;
      string xURfVRuoPB;
      string PwxIHZcPro;
      string UZWJonYbbg;
      string JpqHjnRxal;
      string ZlsYlkDYeZ;
      string swwYTWyIpg;
      string rSNhrYEoYS;
      string HfnGOhfxWE;
      string kAwCmMtRnM;
      string pJGtsHXLgM;
      string fOzMRNHoKk;
      string pAklwqVLue;
      string elBLcyYtMH;
      string JUQKXVAjjY;
      string FFHCVpXUxC;
      string kMPChtMniT;
      string nNbCaUiaNZ;
      string qkaVZZdypl;
      if(JjcxDVbJaB == kAwCmMtRnM){ZDxKWxFOcc = true;}
      else if(kAwCmMtRnM == JjcxDVbJaB){PfokGlAZEt = true;}
      if(gBgmzWLnOn == pJGtsHXLgM){JMBPkrcFbA = true;}
      else if(pJGtsHXLgM == gBgmzWLnOn){dZTRHjBqJW = true;}
      if(xURfVRuoPB == fOzMRNHoKk){GxHWLzltbI = true;}
      else if(fOzMRNHoKk == xURfVRuoPB){DFnELksPee = true;}
      if(PwxIHZcPro == pAklwqVLue){POywtkPRfd = true;}
      else if(pAklwqVLue == PwxIHZcPro){DUAjRilXnY = true;}
      if(UZWJonYbbg == elBLcyYtMH){PUyjQdjKkh = true;}
      else if(elBLcyYtMH == UZWJonYbbg){pREVmNWABh = true;}
      if(JpqHjnRxal == JUQKXVAjjY){wYWofcwZzW = true;}
      else if(JUQKXVAjjY == JpqHjnRxal){DqUzSJrjYU = true;}
      if(ZlsYlkDYeZ == FFHCVpXUxC){LKlUNtOEVz = true;}
      else if(FFHCVpXUxC == ZlsYlkDYeZ){rjtYqIZiAX = true;}
      if(swwYTWyIpg == kMPChtMniT){bKYxjlzWGg = true;}
      if(rSNhrYEoYS == nNbCaUiaNZ){PaJtLpqIQQ = true;}
      if(HfnGOhfxWE == qkaVZZdypl){npRJSFhdWV = true;}
      while(kMPChtMniT == swwYTWyIpg){ydDjfkBRRx = true;}
      while(nNbCaUiaNZ == nNbCaUiaNZ){OrNwbMAARI = true;}
      while(qkaVZZdypl == qkaVZZdypl){qBzTgGWeee = true;}
      if(ZDxKWxFOcc == true){ZDxKWxFOcc = false;}
      if(JMBPkrcFbA == true){JMBPkrcFbA = false;}
      if(GxHWLzltbI == true){GxHWLzltbI = false;}
      if(POywtkPRfd == true){POywtkPRfd = false;}
      if(PUyjQdjKkh == true){PUyjQdjKkh = false;}
      if(wYWofcwZzW == true){wYWofcwZzW = false;}
      if(LKlUNtOEVz == true){LKlUNtOEVz = false;}
      if(bKYxjlzWGg == true){bKYxjlzWGg = false;}
      if(PaJtLpqIQQ == true){PaJtLpqIQQ = false;}
      if(npRJSFhdWV == true){npRJSFhdWV = false;}
      if(PfokGlAZEt == true){PfokGlAZEt = false;}
      if(dZTRHjBqJW == true){dZTRHjBqJW = false;}
      if(DFnELksPee == true){DFnELksPee = false;}
      if(DUAjRilXnY == true){DUAjRilXnY = false;}
      if(pREVmNWABh == true){pREVmNWABh = false;}
      if(DqUzSJrjYU == true){DqUzSJrjYU = false;}
      if(rjtYqIZiAX == true){rjtYqIZiAX = false;}
      if(ydDjfkBRRx == true){ydDjfkBRRx = false;}
      if(OrNwbMAARI == true){OrNwbMAARI = false;}
      if(qBzTgGWeee == true){qBzTgGWeee = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJFMAXVQFD
{ 
  void kreuEjzUho()
  { 
      bool FZtANUWApH = false;
      bool ClIZbPZVbZ = false;
      bool uOfpEXloHQ = false;
      bool nISCrpVSeW = false;
      bool MHGCbBDDga = false;
      bool aYRGWptDuo = false;
      bool hgrZSsTGgk = false;
      bool tGqENnIdOD = false;
      bool UiIfoPqLfB = false;
      bool uRXonePgih = false;
      bool gxVugUgMri = false;
      bool hQoqTzXLjD = false;
      bool CHaeobhBPh = false;
      bool XatfWXMMzU = false;
      bool hdTwTebfUo = false;
      bool GDwefYVpFE = false;
      bool lfwJKGVJUw = false;
      bool mLMOUXndLK = false;
      bool ACfaaUeOAx = false;
      bool BVHuiChJlM = false;
      string rAQQnneEpm;
      string rVfxcaXyUn;
      string KCHjHVEZhm;
      string aiqmXcmbbG;
      string HnYfwAUtlK;
      string FaSeiosfJS;
      string iFVDLJdsZz;
      string mwVNfVdanG;
      string AJnXgzPMDh;
      string jHRJWCSVUl;
      string WbUmXJFFyM;
      string LSqDRZQyVL;
      string tRoqPfdLpd;
      string DHFBiYoBAW;
      string tKOpWRPOrx;
      string kUzIrFlcXq;
      string fsOUJDMoTr;
      string jPyzRjCzUx;
      string PPTrriIxJd;
      string mLdIqAutgS;
      if(rAQQnneEpm == WbUmXJFFyM){FZtANUWApH = true;}
      else if(WbUmXJFFyM == rAQQnneEpm){gxVugUgMri = true;}
      if(rVfxcaXyUn == LSqDRZQyVL){ClIZbPZVbZ = true;}
      else if(LSqDRZQyVL == rVfxcaXyUn){hQoqTzXLjD = true;}
      if(KCHjHVEZhm == tRoqPfdLpd){uOfpEXloHQ = true;}
      else if(tRoqPfdLpd == KCHjHVEZhm){CHaeobhBPh = true;}
      if(aiqmXcmbbG == DHFBiYoBAW){nISCrpVSeW = true;}
      else if(DHFBiYoBAW == aiqmXcmbbG){XatfWXMMzU = true;}
      if(HnYfwAUtlK == tKOpWRPOrx){MHGCbBDDga = true;}
      else if(tKOpWRPOrx == HnYfwAUtlK){hdTwTebfUo = true;}
      if(FaSeiosfJS == kUzIrFlcXq){aYRGWptDuo = true;}
      else if(kUzIrFlcXq == FaSeiosfJS){GDwefYVpFE = true;}
      if(iFVDLJdsZz == fsOUJDMoTr){hgrZSsTGgk = true;}
      else if(fsOUJDMoTr == iFVDLJdsZz){lfwJKGVJUw = true;}
      if(mwVNfVdanG == jPyzRjCzUx){tGqENnIdOD = true;}
      if(AJnXgzPMDh == PPTrriIxJd){UiIfoPqLfB = true;}
      if(jHRJWCSVUl == mLdIqAutgS){uRXonePgih = true;}
      while(jPyzRjCzUx == mwVNfVdanG){mLMOUXndLK = true;}
      while(PPTrriIxJd == PPTrriIxJd){ACfaaUeOAx = true;}
      while(mLdIqAutgS == mLdIqAutgS){BVHuiChJlM = true;}
      if(FZtANUWApH == true){FZtANUWApH = false;}
      if(ClIZbPZVbZ == true){ClIZbPZVbZ = false;}
      if(uOfpEXloHQ == true){uOfpEXloHQ = false;}
      if(nISCrpVSeW == true){nISCrpVSeW = false;}
      if(MHGCbBDDga == true){MHGCbBDDga = false;}
      if(aYRGWptDuo == true){aYRGWptDuo = false;}
      if(hgrZSsTGgk == true){hgrZSsTGgk = false;}
      if(tGqENnIdOD == true){tGqENnIdOD = false;}
      if(UiIfoPqLfB == true){UiIfoPqLfB = false;}
      if(uRXonePgih == true){uRXonePgih = false;}
      if(gxVugUgMri == true){gxVugUgMri = false;}
      if(hQoqTzXLjD == true){hQoqTzXLjD = false;}
      if(CHaeobhBPh == true){CHaeobhBPh = false;}
      if(XatfWXMMzU == true){XatfWXMMzU = false;}
      if(hdTwTebfUo == true){hdTwTebfUo = false;}
      if(GDwefYVpFE == true){GDwefYVpFE = false;}
      if(lfwJKGVJUw == true){lfwJKGVJUw = false;}
      if(mLMOUXndLK == true){mLMOUXndLK = false;}
      if(ACfaaUeOAx == true){ACfaaUeOAx = false;}
      if(BVHuiChJlM == true){BVHuiChJlM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGHEWYPAEY
{ 
  void GUULECfzhy()
  { 
      bool sOSRBPfkCq = false;
      bool oZfNAgHxXq = false;
      bool IXZNocYkyG = false;
      bool dQlADFbCiD = false;
      bool ktDUbPREna = false;
      bool xGtcfVoFcY = false;
      bool qtmuNYmeKu = false;
      bool FFOUGNTEkY = false;
      bool LTwWJXVIUh = false;
      bool PVZKMpHHHD = false;
      bool cltrVqqZWS = false;
      bool BkUDMWyPlp = false;
      bool CdJcfifEHP = false;
      bool FLwgwYZDBR = false;
      bool fwlCfeBVxo = false;
      bool rrVRBybRMl = false;
      bool LmRGMpnmGn = false;
      bool wtNUJFrHxA = false;
      bool hJHSXNpeey = false;
      bool xIqPFsdepp = false;
      string nYkejzPUgw;
      string WfqElZLwJV;
      string lbzfAwyhjm;
      string dRHzzueyjX;
      string NZZYzqJrWk;
      string hEhcqMYFdm;
      string BhjtREYrEp;
      string tNMkIMCagI;
      string mGKzEYjeHm;
      string VZTwWfpfGt;
      string SQmfpUrwUe;
      string KyYVAtWjor;
      string UsjRUUsPNb;
      string WVTlpVSeJi;
      string gmKcbXBywc;
      string IFpNZYgVLU;
      string bbirIndled;
      string arZFLhiHox;
      string TuTkTQfGMR;
      string oxSoHEESUn;
      if(nYkejzPUgw == SQmfpUrwUe){sOSRBPfkCq = true;}
      else if(SQmfpUrwUe == nYkejzPUgw){cltrVqqZWS = true;}
      if(WfqElZLwJV == KyYVAtWjor){oZfNAgHxXq = true;}
      else if(KyYVAtWjor == WfqElZLwJV){BkUDMWyPlp = true;}
      if(lbzfAwyhjm == UsjRUUsPNb){IXZNocYkyG = true;}
      else if(UsjRUUsPNb == lbzfAwyhjm){CdJcfifEHP = true;}
      if(dRHzzueyjX == WVTlpVSeJi){dQlADFbCiD = true;}
      else if(WVTlpVSeJi == dRHzzueyjX){FLwgwYZDBR = true;}
      if(NZZYzqJrWk == gmKcbXBywc){ktDUbPREna = true;}
      else if(gmKcbXBywc == NZZYzqJrWk){fwlCfeBVxo = true;}
      if(hEhcqMYFdm == IFpNZYgVLU){xGtcfVoFcY = true;}
      else if(IFpNZYgVLU == hEhcqMYFdm){rrVRBybRMl = true;}
      if(BhjtREYrEp == bbirIndled){qtmuNYmeKu = true;}
      else if(bbirIndled == BhjtREYrEp){LmRGMpnmGn = true;}
      if(tNMkIMCagI == arZFLhiHox){FFOUGNTEkY = true;}
      if(mGKzEYjeHm == TuTkTQfGMR){LTwWJXVIUh = true;}
      if(VZTwWfpfGt == oxSoHEESUn){PVZKMpHHHD = true;}
      while(arZFLhiHox == tNMkIMCagI){wtNUJFrHxA = true;}
      while(TuTkTQfGMR == TuTkTQfGMR){hJHSXNpeey = true;}
      while(oxSoHEESUn == oxSoHEESUn){xIqPFsdepp = true;}
      if(sOSRBPfkCq == true){sOSRBPfkCq = false;}
      if(oZfNAgHxXq == true){oZfNAgHxXq = false;}
      if(IXZNocYkyG == true){IXZNocYkyG = false;}
      if(dQlADFbCiD == true){dQlADFbCiD = false;}
      if(ktDUbPREna == true){ktDUbPREna = false;}
      if(xGtcfVoFcY == true){xGtcfVoFcY = false;}
      if(qtmuNYmeKu == true){qtmuNYmeKu = false;}
      if(FFOUGNTEkY == true){FFOUGNTEkY = false;}
      if(LTwWJXVIUh == true){LTwWJXVIUh = false;}
      if(PVZKMpHHHD == true){PVZKMpHHHD = false;}
      if(cltrVqqZWS == true){cltrVqqZWS = false;}
      if(BkUDMWyPlp == true){BkUDMWyPlp = false;}
      if(CdJcfifEHP == true){CdJcfifEHP = false;}
      if(FLwgwYZDBR == true){FLwgwYZDBR = false;}
      if(fwlCfeBVxo == true){fwlCfeBVxo = false;}
      if(rrVRBybRMl == true){rrVRBybRMl = false;}
      if(LmRGMpnmGn == true){LmRGMpnmGn = false;}
      if(wtNUJFrHxA == true){wtNUJFrHxA = false;}
      if(hJHSXNpeey == true){hJHSXNpeey = false;}
      if(xIqPFsdepp == true){xIqPFsdepp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NNLHGRNHVW
{ 
  void jIqSOUfkpm()
  { 
      bool OtKOhYEnFb = false;
      bool aRUbyDbOyL = false;
      bool NVbsqqEaHY = false;
      bool rCkMwaXUuX = false;
      bool uGqpAuxltJ = false;
      bool cXEjOrRRXq = false;
      bool TcffjYfIfX = false;
      bool fGTaQGdksu = false;
      bool tRgxuUxAxD = false;
      bool IGwDDRZKGb = false;
      bool PoGVdVEcTH = false;
      bool NfXcxBwijO = false;
      bool afKbPYKPWz = false;
      bool fTeRfFLKSZ = false;
      bool PTgoobhTGC = false;
      bool UqZqAiddGF = false;
      bool LoGUbtBGxr = false;
      bool olPKzGzUmm = false;
      bool ppIUdotmQw = false;
      bool ahDNNaNLNu = false;
      string tYWilKrIKK;
      string AFmUOpDnRV;
      string HuPJNVQmkh;
      string izTGxoWdAV;
      string ScJFRVUGEw;
      string cDIlOzJMUQ;
      string tEWcaAkgXY;
      string SYmwCelKqr;
      string AJioFfqhqy;
      string fJJjaOGgdR;
      string jnifcDPMij;
      string NyUcQjVgWt;
      string JDoZrJPDUn;
      string YEfZHMaCMB;
      string QdyHkgnfTq;
      string rYJiHfzJmT;
      string mLruLIStUE;
      string ITUVdeFgnK;
      string UijcwzuwSa;
      string MROsNElDwb;
      if(tYWilKrIKK == jnifcDPMij){OtKOhYEnFb = true;}
      else if(jnifcDPMij == tYWilKrIKK){PoGVdVEcTH = true;}
      if(AFmUOpDnRV == NyUcQjVgWt){aRUbyDbOyL = true;}
      else if(NyUcQjVgWt == AFmUOpDnRV){NfXcxBwijO = true;}
      if(HuPJNVQmkh == JDoZrJPDUn){NVbsqqEaHY = true;}
      else if(JDoZrJPDUn == HuPJNVQmkh){afKbPYKPWz = true;}
      if(izTGxoWdAV == YEfZHMaCMB){rCkMwaXUuX = true;}
      else if(YEfZHMaCMB == izTGxoWdAV){fTeRfFLKSZ = true;}
      if(ScJFRVUGEw == QdyHkgnfTq){uGqpAuxltJ = true;}
      else if(QdyHkgnfTq == ScJFRVUGEw){PTgoobhTGC = true;}
      if(cDIlOzJMUQ == rYJiHfzJmT){cXEjOrRRXq = true;}
      else if(rYJiHfzJmT == cDIlOzJMUQ){UqZqAiddGF = true;}
      if(tEWcaAkgXY == mLruLIStUE){TcffjYfIfX = true;}
      else if(mLruLIStUE == tEWcaAkgXY){LoGUbtBGxr = true;}
      if(SYmwCelKqr == ITUVdeFgnK){fGTaQGdksu = true;}
      if(AJioFfqhqy == UijcwzuwSa){tRgxuUxAxD = true;}
      if(fJJjaOGgdR == MROsNElDwb){IGwDDRZKGb = true;}
      while(ITUVdeFgnK == SYmwCelKqr){olPKzGzUmm = true;}
      while(UijcwzuwSa == UijcwzuwSa){ppIUdotmQw = true;}
      while(MROsNElDwb == MROsNElDwb){ahDNNaNLNu = true;}
      if(OtKOhYEnFb == true){OtKOhYEnFb = false;}
      if(aRUbyDbOyL == true){aRUbyDbOyL = false;}
      if(NVbsqqEaHY == true){NVbsqqEaHY = false;}
      if(rCkMwaXUuX == true){rCkMwaXUuX = false;}
      if(uGqpAuxltJ == true){uGqpAuxltJ = false;}
      if(cXEjOrRRXq == true){cXEjOrRRXq = false;}
      if(TcffjYfIfX == true){TcffjYfIfX = false;}
      if(fGTaQGdksu == true){fGTaQGdksu = false;}
      if(tRgxuUxAxD == true){tRgxuUxAxD = false;}
      if(IGwDDRZKGb == true){IGwDDRZKGb = false;}
      if(PoGVdVEcTH == true){PoGVdVEcTH = false;}
      if(NfXcxBwijO == true){NfXcxBwijO = false;}
      if(afKbPYKPWz == true){afKbPYKPWz = false;}
      if(fTeRfFLKSZ == true){fTeRfFLKSZ = false;}
      if(PTgoobhTGC == true){PTgoobhTGC = false;}
      if(UqZqAiddGF == true){UqZqAiddGF = false;}
      if(LoGUbtBGxr == true){LoGUbtBGxr = false;}
      if(olPKzGzUmm == true){olPKzGzUmm = false;}
      if(ppIUdotmQw == true){ppIUdotmQw = false;}
      if(ahDNNaNLNu == true){ahDNNaNLNu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUEWPKMXYJ
{ 
  void aFpIMmrnIo()
  { 
      bool sWFittnazo = false;
      bool MIfrToPRep = false;
      bool eeVTtzUuYH = false;
      bool DQXMZoMRla = false;
      bool fnQLQpSNZC = false;
      bool dYPxjOBlnt = false;
      bool YrBrlwjSSe = false;
      bool bxeEKqNJCE = false;
      bool fHVWdeAacK = false;
      bool mZdqBmlYZU = false;
      bool FAttZfsLlr = false;
      bool AqjjORVeNG = false;
      bool uJoHqBTnDW = false;
      bool FojgyfMawx = false;
      bool lookKwpsbi = false;
      bool QGKSYwKmDX = false;
      bool MEHOmKHCki = false;
      bool EuiQUGUEwu = false;
      bool LZLTGydQIC = false;
      bool UYXXjggZxz = false;
      string ZtMiyyqnWq;
      string sSPQzRFXeq;
      string NMGFDnpOJd;
      string ZDbCVoJhBG;
      string oXAdFWqndw;
      string BSsqxMnHfK;
      string HcdsRpqNtJ;
      string IXVXBpMbzg;
      string xBkNcGJjEI;
      string BBBqzMsGLP;
      string ectTmdwVoG;
      string zLHyNGqPPL;
      string gGIkIGVeYo;
      string xFQjBTHQZz;
      string KmuxJotCcr;
      string UcqAiXTILf;
      string HQxzJtuWxt;
      string yaoQAsLLbS;
      string MSBfUTOQBd;
      string zzFtqspumO;
      if(ZtMiyyqnWq == ectTmdwVoG){sWFittnazo = true;}
      else if(ectTmdwVoG == ZtMiyyqnWq){FAttZfsLlr = true;}
      if(sSPQzRFXeq == zLHyNGqPPL){MIfrToPRep = true;}
      else if(zLHyNGqPPL == sSPQzRFXeq){AqjjORVeNG = true;}
      if(NMGFDnpOJd == gGIkIGVeYo){eeVTtzUuYH = true;}
      else if(gGIkIGVeYo == NMGFDnpOJd){uJoHqBTnDW = true;}
      if(ZDbCVoJhBG == xFQjBTHQZz){DQXMZoMRla = true;}
      else if(xFQjBTHQZz == ZDbCVoJhBG){FojgyfMawx = true;}
      if(oXAdFWqndw == KmuxJotCcr){fnQLQpSNZC = true;}
      else if(KmuxJotCcr == oXAdFWqndw){lookKwpsbi = true;}
      if(BSsqxMnHfK == UcqAiXTILf){dYPxjOBlnt = true;}
      else if(UcqAiXTILf == BSsqxMnHfK){QGKSYwKmDX = true;}
      if(HcdsRpqNtJ == HQxzJtuWxt){YrBrlwjSSe = true;}
      else if(HQxzJtuWxt == HcdsRpqNtJ){MEHOmKHCki = true;}
      if(IXVXBpMbzg == yaoQAsLLbS){bxeEKqNJCE = true;}
      if(xBkNcGJjEI == MSBfUTOQBd){fHVWdeAacK = true;}
      if(BBBqzMsGLP == zzFtqspumO){mZdqBmlYZU = true;}
      while(yaoQAsLLbS == IXVXBpMbzg){EuiQUGUEwu = true;}
      while(MSBfUTOQBd == MSBfUTOQBd){LZLTGydQIC = true;}
      while(zzFtqspumO == zzFtqspumO){UYXXjggZxz = true;}
      if(sWFittnazo == true){sWFittnazo = false;}
      if(MIfrToPRep == true){MIfrToPRep = false;}
      if(eeVTtzUuYH == true){eeVTtzUuYH = false;}
      if(DQXMZoMRla == true){DQXMZoMRla = false;}
      if(fnQLQpSNZC == true){fnQLQpSNZC = false;}
      if(dYPxjOBlnt == true){dYPxjOBlnt = false;}
      if(YrBrlwjSSe == true){YrBrlwjSSe = false;}
      if(bxeEKqNJCE == true){bxeEKqNJCE = false;}
      if(fHVWdeAacK == true){fHVWdeAacK = false;}
      if(mZdqBmlYZU == true){mZdqBmlYZU = false;}
      if(FAttZfsLlr == true){FAttZfsLlr = false;}
      if(AqjjORVeNG == true){AqjjORVeNG = false;}
      if(uJoHqBTnDW == true){uJoHqBTnDW = false;}
      if(FojgyfMawx == true){FojgyfMawx = false;}
      if(lookKwpsbi == true){lookKwpsbi = false;}
      if(QGKSYwKmDX == true){QGKSYwKmDX = false;}
      if(MEHOmKHCki == true){MEHOmKHCki = false;}
      if(EuiQUGUEwu == true){EuiQUGUEwu = false;}
      if(LZLTGydQIC == true){LZLTGydQIC = false;}
      if(UYXXjggZxz == true){UYXXjggZxz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WIJVISZREI
{ 
  void WWcmhtZbje()
  { 
      bool NTiTxMhOhC = false;
      bool TcKgckRAyo = false;
      bool QwqHtUyZqR = false;
      bool kYxfMByilb = false;
      bool pDdESOauiM = false;
      bool IRPxSQbaYb = false;
      bool OHWPQtfdTa = false;
      bool lhNWyNSmoe = false;
      bool sCqdITIzMw = false;
      bool YXJKMhfNmX = false;
      bool hxaHZaDsyF = false;
      bool yokthLQsGx = false;
      bool kfQXCOXDJP = false;
      bool gEzRwwaiDh = false;
      bool QPBHxilPbB = false;
      bool RmGplBfDFL = false;
      bool CAjhXtpTxl = false;
      bool jgoYfVeJZS = false;
      bool cIaHysxJeu = false;
      bool PXdrfPfSiD = false;
      string dKuOeZBqyP;
      string lBUQSZSsWS;
      string ZrTMlmlDxx;
      string FHzcJGKrnL;
      string uMLVoxmPPB;
      string DhhkUlqhbq;
      string nxtAJdCqGL;
      string PaFKXMgxXo;
      string AVmwtXYNHX;
      string PbPwWxSKLK;
      string uuJDkccXMH;
      string FsKmqSKxGl;
      string EniiwmKIma;
      string tVkMsELjKQ;
      string tBAzSVRcFD;
      string mUEYFHMZHy;
      string SUjlNiIytl;
      string GZmoqDmiPZ;
      string VgCinYRLGl;
      string rlbMyZROlj;
      if(dKuOeZBqyP == uuJDkccXMH){NTiTxMhOhC = true;}
      else if(uuJDkccXMH == dKuOeZBqyP){hxaHZaDsyF = true;}
      if(lBUQSZSsWS == FsKmqSKxGl){TcKgckRAyo = true;}
      else if(FsKmqSKxGl == lBUQSZSsWS){yokthLQsGx = true;}
      if(ZrTMlmlDxx == EniiwmKIma){QwqHtUyZqR = true;}
      else if(EniiwmKIma == ZrTMlmlDxx){kfQXCOXDJP = true;}
      if(FHzcJGKrnL == tVkMsELjKQ){kYxfMByilb = true;}
      else if(tVkMsELjKQ == FHzcJGKrnL){gEzRwwaiDh = true;}
      if(uMLVoxmPPB == tBAzSVRcFD){pDdESOauiM = true;}
      else if(tBAzSVRcFD == uMLVoxmPPB){QPBHxilPbB = true;}
      if(DhhkUlqhbq == mUEYFHMZHy){IRPxSQbaYb = true;}
      else if(mUEYFHMZHy == DhhkUlqhbq){RmGplBfDFL = true;}
      if(nxtAJdCqGL == SUjlNiIytl){OHWPQtfdTa = true;}
      else if(SUjlNiIytl == nxtAJdCqGL){CAjhXtpTxl = true;}
      if(PaFKXMgxXo == GZmoqDmiPZ){lhNWyNSmoe = true;}
      if(AVmwtXYNHX == VgCinYRLGl){sCqdITIzMw = true;}
      if(PbPwWxSKLK == rlbMyZROlj){YXJKMhfNmX = true;}
      while(GZmoqDmiPZ == PaFKXMgxXo){jgoYfVeJZS = true;}
      while(VgCinYRLGl == VgCinYRLGl){cIaHysxJeu = true;}
      while(rlbMyZROlj == rlbMyZROlj){PXdrfPfSiD = true;}
      if(NTiTxMhOhC == true){NTiTxMhOhC = false;}
      if(TcKgckRAyo == true){TcKgckRAyo = false;}
      if(QwqHtUyZqR == true){QwqHtUyZqR = false;}
      if(kYxfMByilb == true){kYxfMByilb = false;}
      if(pDdESOauiM == true){pDdESOauiM = false;}
      if(IRPxSQbaYb == true){IRPxSQbaYb = false;}
      if(OHWPQtfdTa == true){OHWPQtfdTa = false;}
      if(lhNWyNSmoe == true){lhNWyNSmoe = false;}
      if(sCqdITIzMw == true){sCqdITIzMw = false;}
      if(YXJKMhfNmX == true){YXJKMhfNmX = false;}
      if(hxaHZaDsyF == true){hxaHZaDsyF = false;}
      if(yokthLQsGx == true){yokthLQsGx = false;}
      if(kfQXCOXDJP == true){kfQXCOXDJP = false;}
      if(gEzRwwaiDh == true){gEzRwwaiDh = false;}
      if(QPBHxilPbB == true){QPBHxilPbB = false;}
      if(RmGplBfDFL == true){RmGplBfDFL = false;}
      if(CAjhXtpTxl == true){CAjhXtpTxl = false;}
      if(jgoYfVeJZS == true){jgoYfVeJZS = false;}
      if(cIaHysxJeu == true){cIaHysxJeu = false;}
      if(PXdrfPfSiD == true){PXdrfPfSiD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NNAWWOKCHL
{ 
  void bthnLZoWOs()
  { 
      bool cHaxGgMWQk = false;
      bool HUDzmkjLYo = false;
      bool CzPCQBmEXk = false;
      bool rxXdYfgGhQ = false;
      bool jbddYNmgAu = false;
      bool RkTFIcqYgF = false;
      bool tIzfrJwYaH = false;
      bool DddHFZVkcC = false;
      bool NFDcTHdSVu = false;
      bool nHYbWbcylP = false;
      bool QNGsrnGLzh = false;
      bool HGweqnEWLk = false;
      bool fdDfSuEBkd = false;
      bool xWzMlzzKje = false;
      bool ASSmmhKtkh = false;
      bool WGlAjmKZZw = false;
      bool jFZVkkHisq = false;
      bool ntlgkMKPrk = false;
      bool kKQDHqkycz = false;
      bool oYknutrxCC = false;
      string HPGUJUqUEI;
      string LGtisJHZAV;
      string wAijaYNdxo;
      string uoOXtzcREj;
      string QhUyitLiTh;
      string DMDbBHfVsj;
      string HMWPNWrWns;
      string gpVPENfkBg;
      string MeJPlhklVm;
      string TGXTbELFjL;
      string CotaAMqnWn;
      string auUMWcCGde;
      string lFABZZSBmA;
      string BZAodXjhOZ;
      string qxPgLXlKxz;
      string BEaFZxnsBa;
      string soAWlBueiz;
      string rTrEnopSoB;
      string mIEnywyuPg;
      string iqgnfCwruK;
      if(HPGUJUqUEI == CotaAMqnWn){cHaxGgMWQk = true;}
      else if(CotaAMqnWn == HPGUJUqUEI){QNGsrnGLzh = true;}
      if(LGtisJHZAV == auUMWcCGde){HUDzmkjLYo = true;}
      else if(auUMWcCGde == LGtisJHZAV){HGweqnEWLk = true;}
      if(wAijaYNdxo == lFABZZSBmA){CzPCQBmEXk = true;}
      else if(lFABZZSBmA == wAijaYNdxo){fdDfSuEBkd = true;}
      if(uoOXtzcREj == BZAodXjhOZ){rxXdYfgGhQ = true;}
      else if(BZAodXjhOZ == uoOXtzcREj){xWzMlzzKje = true;}
      if(QhUyitLiTh == qxPgLXlKxz){jbddYNmgAu = true;}
      else if(qxPgLXlKxz == QhUyitLiTh){ASSmmhKtkh = true;}
      if(DMDbBHfVsj == BEaFZxnsBa){RkTFIcqYgF = true;}
      else if(BEaFZxnsBa == DMDbBHfVsj){WGlAjmKZZw = true;}
      if(HMWPNWrWns == soAWlBueiz){tIzfrJwYaH = true;}
      else if(soAWlBueiz == HMWPNWrWns){jFZVkkHisq = true;}
      if(gpVPENfkBg == rTrEnopSoB){DddHFZVkcC = true;}
      if(MeJPlhklVm == mIEnywyuPg){NFDcTHdSVu = true;}
      if(TGXTbELFjL == iqgnfCwruK){nHYbWbcylP = true;}
      while(rTrEnopSoB == gpVPENfkBg){ntlgkMKPrk = true;}
      while(mIEnywyuPg == mIEnywyuPg){kKQDHqkycz = true;}
      while(iqgnfCwruK == iqgnfCwruK){oYknutrxCC = true;}
      if(cHaxGgMWQk == true){cHaxGgMWQk = false;}
      if(HUDzmkjLYo == true){HUDzmkjLYo = false;}
      if(CzPCQBmEXk == true){CzPCQBmEXk = false;}
      if(rxXdYfgGhQ == true){rxXdYfgGhQ = false;}
      if(jbddYNmgAu == true){jbddYNmgAu = false;}
      if(RkTFIcqYgF == true){RkTFIcqYgF = false;}
      if(tIzfrJwYaH == true){tIzfrJwYaH = false;}
      if(DddHFZVkcC == true){DddHFZVkcC = false;}
      if(NFDcTHdSVu == true){NFDcTHdSVu = false;}
      if(nHYbWbcylP == true){nHYbWbcylP = false;}
      if(QNGsrnGLzh == true){QNGsrnGLzh = false;}
      if(HGweqnEWLk == true){HGweqnEWLk = false;}
      if(fdDfSuEBkd == true){fdDfSuEBkd = false;}
      if(xWzMlzzKje == true){xWzMlzzKje = false;}
      if(ASSmmhKtkh == true){ASSmmhKtkh = false;}
      if(WGlAjmKZZw == true){WGlAjmKZZw = false;}
      if(jFZVkkHisq == true){jFZVkkHisq = false;}
      if(ntlgkMKPrk == true){ntlgkMKPrk = false;}
      if(kKQDHqkycz == true){kKQDHqkycz = false;}
      if(oYknutrxCC == true){oYknutrxCC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWNDTXJPNR
{ 
  void uWoAFpLjMK()
  { 
      bool ecQKkWMefP = false;
      bool zroeUBQZJf = false;
      bool DqkDSmwBDS = false;
      bool bQNXQKcMlK = false;
      bool VVTUKYQMBB = false;
      bool nmSXzmqNqy = false;
      bool aLbNmidQOK = false;
      bool YEnyKhXPst = false;
      bool VizBdoypYc = false;
      bool SPVnjKtFga = false;
      bool tzyqcjzTNR = false;
      bool ObTxbqLZjy = false;
      bool knrkqJizOz = false;
      bool mShRzVkHYs = false;
      bool pdcHNquXMs = false;
      bool yTUipGHNAT = false;
      bool BzFNdwsBxF = false;
      bool GDBpIGKkXz = false;
      bool NKmVBSxzbs = false;
      bool OXHFrpYPcR = false;
      string dsUQCtGypE;
      string SamMeNtWYw;
      string cETOnOIoSM;
      string jGFwasQYwd;
      string jTWrScnler;
      string qhtyrZYGbm;
      string kRecUMVpkl;
      string wVatMIgbuL;
      string ZWKaVBLGDB;
      string TJwIsSosXF;
      string HxAruVHAlj;
      string rwLQMOGDHS;
      string BOljRlYSBt;
      string TmEoDcVRfA;
      string tLUTIWyeud;
      string LklEEsKQZI;
      string wnyrPFrVNj;
      string rnXHXosSau;
      string ntWXhiBAjJ;
      string RFrWDFNcED;
      if(dsUQCtGypE == HxAruVHAlj){ecQKkWMefP = true;}
      else if(HxAruVHAlj == dsUQCtGypE){tzyqcjzTNR = true;}
      if(SamMeNtWYw == rwLQMOGDHS){zroeUBQZJf = true;}
      else if(rwLQMOGDHS == SamMeNtWYw){ObTxbqLZjy = true;}
      if(cETOnOIoSM == BOljRlYSBt){DqkDSmwBDS = true;}
      else if(BOljRlYSBt == cETOnOIoSM){knrkqJizOz = true;}
      if(jGFwasQYwd == TmEoDcVRfA){bQNXQKcMlK = true;}
      else if(TmEoDcVRfA == jGFwasQYwd){mShRzVkHYs = true;}
      if(jTWrScnler == tLUTIWyeud){VVTUKYQMBB = true;}
      else if(tLUTIWyeud == jTWrScnler){pdcHNquXMs = true;}
      if(qhtyrZYGbm == LklEEsKQZI){nmSXzmqNqy = true;}
      else if(LklEEsKQZI == qhtyrZYGbm){yTUipGHNAT = true;}
      if(kRecUMVpkl == wnyrPFrVNj){aLbNmidQOK = true;}
      else if(wnyrPFrVNj == kRecUMVpkl){BzFNdwsBxF = true;}
      if(wVatMIgbuL == rnXHXosSau){YEnyKhXPst = true;}
      if(ZWKaVBLGDB == ntWXhiBAjJ){VizBdoypYc = true;}
      if(TJwIsSosXF == RFrWDFNcED){SPVnjKtFga = true;}
      while(rnXHXosSau == wVatMIgbuL){GDBpIGKkXz = true;}
      while(ntWXhiBAjJ == ntWXhiBAjJ){NKmVBSxzbs = true;}
      while(RFrWDFNcED == RFrWDFNcED){OXHFrpYPcR = true;}
      if(ecQKkWMefP == true){ecQKkWMefP = false;}
      if(zroeUBQZJf == true){zroeUBQZJf = false;}
      if(DqkDSmwBDS == true){DqkDSmwBDS = false;}
      if(bQNXQKcMlK == true){bQNXQKcMlK = false;}
      if(VVTUKYQMBB == true){VVTUKYQMBB = false;}
      if(nmSXzmqNqy == true){nmSXzmqNqy = false;}
      if(aLbNmidQOK == true){aLbNmidQOK = false;}
      if(YEnyKhXPst == true){YEnyKhXPst = false;}
      if(VizBdoypYc == true){VizBdoypYc = false;}
      if(SPVnjKtFga == true){SPVnjKtFga = false;}
      if(tzyqcjzTNR == true){tzyqcjzTNR = false;}
      if(ObTxbqLZjy == true){ObTxbqLZjy = false;}
      if(knrkqJizOz == true){knrkqJizOz = false;}
      if(mShRzVkHYs == true){mShRzVkHYs = false;}
      if(pdcHNquXMs == true){pdcHNquXMs = false;}
      if(yTUipGHNAT == true){yTUipGHNAT = false;}
      if(BzFNdwsBxF == true){BzFNdwsBxF = false;}
      if(GDBpIGKkXz == true){GDBpIGKkXz = false;}
      if(NKmVBSxzbs == true){NKmVBSxzbs = false;}
      if(OXHFrpYPcR == true){OXHFrpYPcR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJFHYEJJIF
{ 
  void HMtwgoczOB()
  { 
      bool thxZRhySiV = false;
      bool LbuGekVmMu = false;
      bool zmDtlMEfOA = false;
      bool lzoZnExoEx = false;
      bool RxQsRoUlSl = false;
      bool VruFFGdCnF = false;
      bool cREhiMlVSa = false;
      bool nfhOcCWKcw = false;
      bool qSMbetDjUg = false;
      bool ZtBzTzriJE = false;
      bool DzTryoJfbD = false;
      bool iTZqNKFbCo = false;
      bool ICBkAseitc = false;
      bool JnAXsryUdp = false;
      bool kXIRxFUJkJ = false;
      bool tQfUwBxhqF = false;
      bool KakysuTCyV = false;
      bool LkyMEksjmu = false;
      bool XUxkirIfbr = false;
      bool tQcYeJlJXC = false;
      string OqmOhaXxFZ;
      string BBHNxCzLjH;
      string BKCSRspDiL;
      string tcllKkroDA;
      string gkqcTqoaQO;
      string IlLeUEnUwo;
      string jTOteYOUDL;
      string KJHiZPSZyZ;
      string DOmUCIRGRF;
      string wWrOQNWxyu;
      string bUXEEyebFE;
      string kOVWkUgtqW;
      string GIDyPmRsSM;
      string sVbDxiqhPE;
      string doAMTgAVcu;
      string fcFbnTRZoR;
      string glJrLPmSYC;
      string dydlrRHpdh;
      string luPWfQPzPd;
      string QQsyXqeIAE;
      if(OqmOhaXxFZ == bUXEEyebFE){thxZRhySiV = true;}
      else if(bUXEEyebFE == OqmOhaXxFZ){DzTryoJfbD = true;}
      if(BBHNxCzLjH == kOVWkUgtqW){LbuGekVmMu = true;}
      else if(kOVWkUgtqW == BBHNxCzLjH){iTZqNKFbCo = true;}
      if(BKCSRspDiL == GIDyPmRsSM){zmDtlMEfOA = true;}
      else if(GIDyPmRsSM == BKCSRspDiL){ICBkAseitc = true;}
      if(tcllKkroDA == sVbDxiqhPE){lzoZnExoEx = true;}
      else if(sVbDxiqhPE == tcllKkroDA){JnAXsryUdp = true;}
      if(gkqcTqoaQO == doAMTgAVcu){RxQsRoUlSl = true;}
      else if(doAMTgAVcu == gkqcTqoaQO){kXIRxFUJkJ = true;}
      if(IlLeUEnUwo == fcFbnTRZoR){VruFFGdCnF = true;}
      else if(fcFbnTRZoR == IlLeUEnUwo){tQfUwBxhqF = true;}
      if(jTOteYOUDL == glJrLPmSYC){cREhiMlVSa = true;}
      else if(glJrLPmSYC == jTOteYOUDL){KakysuTCyV = true;}
      if(KJHiZPSZyZ == dydlrRHpdh){nfhOcCWKcw = true;}
      if(DOmUCIRGRF == luPWfQPzPd){qSMbetDjUg = true;}
      if(wWrOQNWxyu == QQsyXqeIAE){ZtBzTzriJE = true;}
      while(dydlrRHpdh == KJHiZPSZyZ){LkyMEksjmu = true;}
      while(luPWfQPzPd == luPWfQPzPd){XUxkirIfbr = true;}
      while(QQsyXqeIAE == QQsyXqeIAE){tQcYeJlJXC = true;}
      if(thxZRhySiV == true){thxZRhySiV = false;}
      if(LbuGekVmMu == true){LbuGekVmMu = false;}
      if(zmDtlMEfOA == true){zmDtlMEfOA = false;}
      if(lzoZnExoEx == true){lzoZnExoEx = false;}
      if(RxQsRoUlSl == true){RxQsRoUlSl = false;}
      if(VruFFGdCnF == true){VruFFGdCnF = false;}
      if(cREhiMlVSa == true){cREhiMlVSa = false;}
      if(nfhOcCWKcw == true){nfhOcCWKcw = false;}
      if(qSMbetDjUg == true){qSMbetDjUg = false;}
      if(ZtBzTzriJE == true){ZtBzTzriJE = false;}
      if(DzTryoJfbD == true){DzTryoJfbD = false;}
      if(iTZqNKFbCo == true){iTZqNKFbCo = false;}
      if(ICBkAseitc == true){ICBkAseitc = false;}
      if(JnAXsryUdp == true){JnAXsryUdp = false;}
      if(kXIRxFUJkJ == true){kXIRxFUJkJ = false;}
      if(tQfUwBxhqF == true){tQfUwBxhqF = false;}
      if(KakysuTCyV == true){KakysuTCyV = false;}
      if(LkyMEksjmu == true){LkyMEksjmu = false;}
      if(XUxkirIfbr == true){XUxkirIfbr = false;}
      if(tQcYeJlJXC == true){tQcYeJlJXC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IAWNICNXSV
{ 
  void sQYZEkpruq()
  { 
      bool iXHaDqVhpM = false;
      bool rkoARpsVJu = false;
      bool ZmpNxPQkSl = false;
      bool ztWblycwOV = false;
      bool OezeVSVyIt = false;
      bool ZbaIXuhtdm = false;
      bool ZjOENyNNNT = false;
      bool MxHngunLrd = false;
      bool tScYMWSOEp = false;
      bool PiRawePtQW = false;
      bool FHjngbUmbc = false;
      bool HWBzsGGprp = false;
      bool fzJXDdefrB = false;
      bool estUYlhnqj = false;
      bool CelaisgSho = false;
      bool XZCZqFyMjC = false;
      bool xnuZxNcfZG = false;
      bool YRyHnAMhnK = false;
      bool xMyCdFqTdS = false;
      bool nVEomNjMdV = false;
      string qqbKRziclK;
      string ioDYTubwGG;
      string rMEsyKzdUS;
      string QeBHxMZJBe;
      string uQRgxAUAIm;
      string MMKBYdlhMH;
      string zFIStDnubG;
      string URtaKauXwy;
      string oyVgFDUziS;
      string ZrxtepIyls;
      string MYYBRuRiqy;
      string iOkNRBjaNp;
      string inMJfcTAwT;
      string RxkClQZTOK;
      string kkIjiLGicd;
      string GgjwKXMOUn;
      string aRmWflchbB;
      string aPLCFxebZU;
      string WkXRMjMorN;
      string DKyZjTykEx;
      if(qqbKRziclK == MYYBRuRiqy){iXHaDqVhpM = true;}
      else if(MYYBRuRiqy == qqbKRziclK){FHjngbUmbc = true;}
      if(ioDYTubwGG == iOkNRBjaNp){rkoARpsVJu = true;}
      else if(iOkNRBjaNp == ioDYTubwGG){HWBzsGGprp = true;}
      if(rMEsyKzdUS == inMJfcTAwT){ZmpNxPQkSl = true;}
      else if(inMJfcTAwT == rMEsyKzdUS){fzJXDdefrB = true;}
      if(QeBHxMZJBe == RxkClQZTOK){ztWblycwOV = true;}
      else if(RxkClQZTOK == QeBHxMZJBe){estUYlhnqj = true;}
      if(uQRgxAUAIm == kkIjiLGicd){OezeVSVyIt = true;}
      else if(kkIjiLGicd == uQRgxAUAIm){CelaisgSho = true;}
      if(MMKBYdlhMH == GgjwKXMOUn){ZbaIXuhtdm = true;}
      else if(GgjwKXMOUn == MMKBYdlhMH){XZCZqFyMjC = true;}
      if(zFIStDnubG == aRmWflchbB){ZjOENyNNNT = true;}
      else if(aRmWflchbB == zFIStDnubG){xnuZxNcfZG = true;}
      if(URtaKauXwy == aPLCFxebZU){MxHngunLrd = true;}
      if(oyVgFDUziS == WkXRMjMorN){tScYMWSOEp = true;}
      if(ZrxtepIyls == DKyZjTykEx){PiRawePtQW = true;}
      while(aPLCFxebZU == URtaKauXwy){YRyHnAMhnK = true;}
      while(WkXRMjMorN == WkXRMjMorN){xMyCdFqTdS = true;}
      while(DKyZjTykEx == DKyZjTykEx){nVEomNjMdV = true;}
      if(iXHaDqVhpM == true){iXHaDqVhpM = false;}
      if(rkoARpsVJu == true){rkoARpsVJu = false;}
      if(ZmpNxPQkSl == true){ZmpNxPQkSl = false;}
      if(ztWblycwOV == true){ztWblycwOV = false;}
      if(OezeVSVyIt == true){OezeVSVyIt = false;}
      if(ZbaIXuhtdm == true){ZbaIXuhtdm = false;}
      if(ZjOENyNNNT == true){ZjOENyNNNT = false;}
      if(MxHngunLrd == true){MxHngunLrd = false;}
      if(tScYMWSOEp == true){tScYMWSOEp = false;}
      if(PiRawePtQW == true){PiRawePtQW = false;}
      if(FHjngbUmbc == true){FHjngbUmbc = false;}
      if(HWBzsGGprp == true){HWBzsGGprp = false;}
      if(fzJXDdefrB == true){fzJXDdefrB = false;}
      if(estUYlhnqj == true){estUYlhnqj = false;}
      if(CelaisgSho == true){CelaisgSho = false;}
      if(XZCZqFyMjC == true){XZCZqFyMjC = false;}
      if(xnuZxNcfZG == true){xnuZxNcfZG = false;}
      if(YRyHnAMhnK == true){YRyHnAMhnK = false;}
      if(xMyCdFqTdS == true){xMyCdFqTdS = false;}
      if(nVEomNjMdV == true){nVEomNjMdV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DDTZECNUBS
{ 
  void NrzTUpnwwa()
  { 
      bool UBScMRqTyB = false;
      bool qQBmZrsJPE = false;
      bool hdUrFGYUDg = false;
      bool xsCEEQoImA = false;
      bool jlQhHiIqig = false;
      bool nUgBuqgaWG = false;
      bool sVQRExOxiI = false;
      bool DkVOUwMmjW = false;
      bool xglWrcMBIM = false;
      bool jNkfHNVzcJ = false;
      bool TLIacDyRgz = false;
      bool dspAJLjtYb = false;
      bool jNnVXpzpHG = false;
      bool ZNJaCkYLsn = false;
      bool duTJipWkVu = false;
      bool cbZBZGXlCm = false;
      bool EIJZYPiPxX = false;
      bool lYAjxnsemh = false;
      bool SNTMcynIAu = false;
      bool NmJGjVlsjS = false;
      string nXMGGMBdDZ;
      string WqFIsteXxA;
      string wwmnDdWQgH;
      string ogWszUwhpe;
      string zxuXhVhrYO;
      string OeFWcrkXDb;
      string pkxujpUMIX;
      string xwgSByBPFg;
      string weqRrJazQH;
      string jYeNoNAzmr;
      string BVjAQRxmUd;
      string pURVfLseCa;
      string OUuAnYRSdm;
      string xCbNeZtpAZ;
      string LmdlROGJhd;
      string UVwMcgZjMr;
      string AdJhfnsEpF;
      string QCdcObpIhZ;
      string SHkASbFOjy;
      string AKdIYhdwGd;
      if(nXMGGMBdDZ == BVjAQRxmUd){UBScMRqTyB = true;}
      else if(BVjAQRxmUd == nXMGGMBdDZ){TLIacDyRgz = true;}
      if(WqFIsteXxA == pURVfLseCa){qQBmZrsJPE = true;}
      else if(pURVfLseCa == WqFIsteXxA){dspAJLjtYb = true;}
      if(wwmnDdWQgH == OUuAnYRSdm){hdUrFGYUDg = true;}
      else if(OUuAnYRSdm == wwmnDdWQgH){jNnVXpzpHG = true;}
      if(ogWszUwhpe == xCbNeZtpAZ){xsCEEQoImA = true;}
      else if(xCbNeZtpAZ == ogWszUwhpe){ZNJaCkYLsn = true;}
      if(zxuXhVhrYO == LmdlROGJhd){jlQhHiIqig = true;}
      else if(LmdlROGJhd == zxuXhVhrYO){duTJipWkVu = true;}
      if(OeFWcrkXDb == UVwMcgZjMr){nUgBuqgaWG = true;}
      else if(UVwMcgZjMr == OeFWcrkXDb){cbZBZGXlCm = true;}
      if(pkxujpUMIX == AdJhfnsEpF){sVQRExOxiI = true;}
      else if(AdJhfnsEpF == pkxujpUMIX){EIJZYPiPxX = true;}
      if(xwgSByBPFg == QCdcObpIhZ){DkVOUwMmjW = true;}
      if(weqRrJazQH == SHkASbFOjy){xglWrcMBIM = true;}
      if(jYeNoNAzmr == AKdIYhdwGd){jNkfHNVzcJ = true;}
      while(QCdcObpIhZ == xwgSByBPFg){lYAjxnsemh = true;}
      while(SHkASbFOjy == SHkASbFOjy){SNTMcynIAu = true;}
      while(AKdIYhdwGd == AKdIYhdwGd){NmJGjVlsjS = true;}
      if(UBScMRqTyB == true){UBScMRqTyB = false;}
      if(qQBmZrsJPE == true){qQBmZrsJPE = false;}
      if(hdUrFGYUDg == true){hdUrFGYUDg = false;}
      if(xsCEEQoImA == true){xsCEEQoImA = false;}
      if(jlQhHiIqig == true){jlQhHiIqig = false;}
      if(nUgBuqgaWG == true){nUgBuqgaWG = false;}
      if(sVQRExOxiI == true){sVQRExOxiI = false;}
      if(DkVOUwMmjW == true){DkVOUwMmjW = false;}
      if(xglWrcMBIM == true){xglWrcMBIM = false;}
      if(jNkfHNVzcJ == true){jNkfHNVzcJ = false;}
      if(TLIacDyRgz == true){TLIacDyRgz = false;}
      if(dspAJLjtYb == true){dspAJLjtYb = false;}
      if(jNnVXpzpHG == true){jNnVXpzpHG = false;}
      if(ZNJaCkYLsn == true){ZNJaCkYLsn = false;}
      if(duTJipWkVu == true){duTJipWkVu = false;}
      if(cbZBZGXlCm == true){cbZBZGXlCm = false;}
      if(EIJZYPiPxX == true){EIJZYPiPxX = false;}
      if(lYAjxnsemh == true){lYAjxnsemh = false;}
      if(SNTMcynIAu == true){SNTMcynIAu = false;}
      if(NmJGjVlsjS == true){NmJGjVlsjS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GGOAAPWSSS
{ 
  void fkWtPgdBBn()
  { 
      bool bgHUUQuIfj = false;
      bool iKqdiUqMyE = false;
      bool OGdiVaZJlP = false;
      bool ZAtVKjPNSi = false;
      bool zblPEruOiw = false;
      bool tFwmMVCYyt = false;
      bool plVPJhQVTz = false;
      bool EdtPElTOed = false;
      bool fLZpUUEGJn = false;
      bool gqOXrNGVFV = false;
      bool bYtjqQLghZ = false;
      bool BntUOeMfuo = false;
      bool dJLeRMOVWq = false;
      bool fyIICGRoyE = false;
      bool IWXimsxtJN = false;
      bool BZaQrRNOSe = false;
      bool BpKqtDekRI = false;
      bool NWgpfGkbrX = false;
      bool PULIpFWrQk = false;
      bool sCWTCSMgoj = false;
      string YjSIwRPEio;
      string uaRhzcQKlx;
      string AHSyexrZNS;
      string LyGXnokuPu;
      string BLmXipVFNS;
      string OwLdJQRUcy;
      string YoqPcwTstJ;
      string qUtpuoTtOo;
      string alMtDOmcNW;
      string XQSRVLUXul;
      string WbLDatCUhU;
      string wXFnXmcwLN;
      string JqeWlaCcUi;
      string TwzbSyZJSI;
      string MRtsaAKdsh;
      string iYLgbewnQA;
      string rZzyAzXdVY;
      string MScCBrwlwl;
      string QXimzukRzm;
      string ClsSQlRura;
      if(YjSIwRPEio == WbLDatCUhU){bgHUUQuIfj = true;}
      else if(WbLDatCUhU == YjSIwRPEio){bYtjqQLghZ = true;}
      if(uaRhzcQKlx == wXFnXmcwLN){iKqdiUqMyE = true;}
      else if(wXFnXmcwLN == uaRhzcQKlx){BntUOeMfuo = true;}
      if(AHSyexrZNS == JqeWlaCcUi){OGdiVaZJlP = true;}
      else if(JqeWlaCcUi == AHSyexrZNS){dJLeRMOVWq = true;}
      if(LyGXnokuPu == TwzbSyZJSI){ZAtVKjPNSi = true;}
      else if(TwzbSyZJSI == LyGXnokuPu){fyIICGRoyE = true;}
      if(BLmXipVFNS == MRtsaAKdsh){zblPEruOiw = true;}
      else if(MRtsaAKdsh == BLmXipVFNS){IWXimsxtJN = true;}
      if(OwLdJQRUcy == iYLgbewnQA){tFwmMVCYyt = true;}
      else if(iYLgbewnQA == OwLdJQRUcy){BZaQrRNOSe = true;}
      if(YoqPcwTstJ == rZzyAzXdVY){plVPJhQVTz = true;}
      else if(rZzyAzXdVY == YoqPcwTstJ){BpKqtDekRI = true;}
      if(qUtpuoTtOo == MScCBrwlwl){EdtPElTOed = true;}
      if(alMtDOmcNW == QXimzukRzm){fLZpUUEGJn = true;}
      if(XQSRVLUXul == ClsSQlRura){gqOXrNGVFV = true;}
      while(MScCBrwlwl == qUtpuoTtOo){NWgpfGkbrX = true;}
      while(QXimzukRzm == QXimzukRzm){PULIpFWrQk = true;}
      while(ClsSQlRura == ClsSQlRura){sCWTCSMgoj = true;}
      if(bgHUUQuIfj == true){bgHUUQuIfj = false;}
      if(iKqdiUqMyE == true){iKqdiUqMyE = false;}
      if(OGdiVaZJlP == true){OGdiVaZJlP = false;}
      if(ZAtVKjPNSi == true){ZAtVKjPNSi = false;}
      if(zblPEruOiw == true){zblPEruOiw = false;}
      if(tFwmMVCYyt == true){tFwmMVCYyt = false;}
      if(plVPJhQVTz == true){plVPJhQVTz = false;}
      if(EdtPElTOed == true){EdtPElTOed = false;}
      if(fLZpUUEGJn == true){fLZpUUEGJn = false;}
      if(gqOXrNGVFV == true){gqOXrNGVFV = false;}
      if(bYtjqQLghZ == true){bYtjqQLghZ = false;}
      if(BntUOeMfuo == true){BntUOeMfuo = false;}
      if(dJLeRMOVWq == true){dJLeRMOVWq = false;}
      if(fyIICGRoyE == true){fyIICGRoyE = false;}
      if(IWXimsxtJN == true){IWXimsxtJN = false;}
      if(BZaQrRNOSe == true){BZaQrRNOSe = false;}
      if(BpKqtDekRI == true){BpKqtDekRI = false;}
      if(NWgpfGkbrX == true){NWgpfGkbrX = false;}
      if(PULIpFWrQk == true){PULIpFWrQk = false;}
      if(sCWTCSMgoj == true){sCWTCSMgoj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UYCRLNFPEV
{ 
  void RXYKLYwtkJ()
  { 
      bool pFZdfTmBlN = false;
      bool ujJzslzNRf = false;
      bool JOcXyYzgkF = false;
      bool lbttCUKshh = false;
      bool ptXoLhEYqG = false;
      bool SxHRxbcCfG = false;
      bool UFPfbToOwX = false;
      bool bFfjpOqmLP = false;
      bool UapemnTbxa = false;
      bool rINaMjeqNq = false;
      bool rpbSdMRWbh = false;
      bool kopPltPjsn = false;
      bool zNQVfSrEWF = false;
      bool jzZTXeyWAZ = false;
      bool WxAPpDSxoS = false;
      bool UuyZreYFmL = false;
      bool TMzVykOVrG = false;
      bool uriSRCMBfb = false;
      bool zuPEkoBAbr = false;
      bool FsjoGJxdQE = false;
      string jZmPhfnYuX;
      string lywezjsJrL;
      string nCuhmzYhRV;
      string kIuwZknPmj;
      string lgAHXsbcPe;
      string qJOnxheFbh;
      string GGHZlcCzFO;
      string wcWIZGBnJt;
      string XwRldasHyr;
      string GhmFcfYaUu;
      string qcXBhNmGNq;
      string fquhKKnUuL;
      string jtAMINpQes;
      string gaSODtXQEQ;
      string nlsHLOmEtR;
      string qEfJKwbKrT;
      string XVaUJEXgeP;
      string lWQdXxArBs;
      string akWNCcuJDG;
      string RNXjrRLYyG;
      if(jZmPhfnYuX == qcXBhNmGNq){pFZdfTmBlN = true;}
      else if(qcXBhNmGNq == jZmPhfnYuX){rpbSdMRWbh = true;}
      if(lywezjsJrL == fquhKKnUuL){ujJzslzNRf = true;}
      else if(fquhKKnUuL == lywezjsJrL){kopPltPjsn = true;}
      if(nCuhmzYhRV == jtAMINpQes){JOcXyYzgkF = true;}
      else if(jtAMINpQes == nCuhmzYhRV){zNQVfSrEWF = true;}
      if(kIuwZknPmj == gaSODtXQEQ){lbttCUKshh = true;}
      else if(gaSODtXQEQ == kIuwZknPmj){jzZTXeyWAZ = true;}
      if(lgAHXsbcPe == nlsHLOmEtR){ptXoLhEYqG = true;}
      else if(nlsHLOmEtR == lgAHXsbcPe){WxAPpDSxoS = true;}
      if(qJOnxheFbh == qEfJKwbKrT){SxHRxbcCfG = true;}
      else if(qEfJKwbKrT == qJOnxheFbh){UuyZreYFmL = true;}
      if(GGHZlcCzFO == XVaUJEXgeP){UFPfbToOwX = true;}
      else if(XVaUJEXgeP == GGHZlcCzFO){TMzVykOVrG = true;}
      if(wcWIZGBnJt == lWQdXxArBs){bFfjpOqmLP = true;}
      if(XwRldasHyr == akWNCcuJDG){UapemnTbxa = true;}
      if(GhmFcfYaUu == RNXjrRLYyG){rINaMjeqNq = true;}
      while(lWQdXxArBs == wcWIZGBnJt){uriSRCMBfb = true;}
      while(akWNCcuJDG == akWNCcuJDG){zuPEkoBAbr = true;}
      while(RNXjrRLYyG == RNXjrRLYyG){FsjoGJxdQE = true;}
      if(pFZdfTmBlN == true){pFZdfTmBlN = false;}
      if(ujJzslzNRf == true){ujJzslzNRf = false;}
      if(JOcXyYzgkF == true){JOcXyYzgkF = false;}
      if(lbttCUKshh == true){lbttCUKshh = false;}
      if(ptXoLhEYqG == true){ptXoLhEYqG = false;}
      if(SxHRxbcCfG == true){SxHRxbcCfG = false;}
      if(UFPfbToOwX == true){UFPfbToOwX = false;}
      if(bFfjpOqmLP == true){bFfjpOqmLP = false;}
      if(UapemnTbxa == true){UapemnTbxa = false;}
      if(rINaMjeqNq == true){rINaMjeqNq = false;}
      if(rpbSdMRWbh == true){rpbSdMRWbh = false;}
      if(kopPltPjsn == true){kopPltPjsn = false;}
      if(zNQVfSrEWF == true){zNQVfSrEWF = false;}
      if(jzZTXeyWAZ == true){jzZTXeyWAZ = false;}
      if(WxAPpDSxoS == true){WxAPpDSxoS = false;}
      if(UuyZreYFmL == true){UuyZreYFmL = false;}
      if(TMzVykOVrG == true){TMzVykOVrG = false;}
      if(uriSRCMBfb == true){uriSRCMBfb = false;}
      if(zuPEkoBAbr == true){zuPEkoBAbr = false;}
      if(FsjoGJxdQE == true){FsjoGJxdQE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TFZKXMKBYR
{ 
  void WgyXoyuWHP()
  { 
      bool VKZHIyyEaK = false;
      bool zSzKprUUcl = false;
      bool nPQpDtjPra = false;
      bool ibJTUVGSgi = false;
      bool TiQTKtxkCj = false;
      bool KUHWVFtiEN = false;
      bool OiMAbXJfpU = false;
      bool lCnsRFzxfJ = false;
      bool xzMHPNTlxO = false;
      bool aWNSUkVPql = false;
      bool jQtgyHgOFQ = false;
      bool GxDtPOVFjN = false;
      bool EWhbsOnUYf = false;
      bool iiFsZgEfJI = false;
      bool gFgfHdTTDF = false;
      bool PQechMiRmi = false;
      bool SLpYhWqJUi = false;
      bool JoubgzoBTP = false;
      bool tUQSQSEbKM = false;
      bool xlrZoUOIyk = false;
      string zYgJXrQkRD;
      string hmwOKxWxLW;
      string iDECqxFUlQ;
      string BJKZWetQME;
      string DduQgykkBM;
      string kfIqiwUeRZ;
      string luyBCYcVqf;
      string CFkHTEHmVs;
      string MUSZfVATqa;
      string KPzlRHetOH;
      string VPtVJetAWd;
      string ngJXNRcYUg;
      string XIePUlGzpM;
      string ZMYNWxZxPA;
      string aAwMldGaYA;
      string dGYgiMjdBW;
      string XuKKEbHuBQ;
      string qfIUFXMRdp;
      string ffZohSmqeK;
      string MwusceokIK;
      if(zYgJXrQkRD == VPtVJetAWd){VKZHIyyEaK = true;}
      else if(VPtVJetAWd == zYgJXrQkRD){jQtgyHgOFQ = true;}
      if(hmwOKxWxLW == ngJXNRcYUg){zSzKprUUcl = true;}
      else if(ngJXNRcYUg == hmwOKxWxLW){GxDtPOVFjN = true;}
      if(iDECqxFUlQ == XIePUlGzpM){nPQpDtjPra = true;}
      else if(XIePUlGzpM == iDECqxFUlQ){EWhbsOnUYf = true;}
      if(BJKZWetQME == ZMYNWxZxPA){ibJTUVGSgi = true;}
      else if(ZMYNWxZxPA == BJKZWetQME){iiFsZgEfJI = true;}
      if(DduQgykkBM == aAwMldGaYA){TiQTKtxkCj = true;}
      else if(aAwMldGaYA == DduQgykkBM){gFgfHdTTDF = true;}
      if(kfIqiwUeRZ == dGYgiMjdBW){KUHWVFtiEN = true;}
      else if(dGYgiMjdBW == kfIqiwUeRZ){PQechMiRmi = true;}
      if(luyBCYcVqf == XuKKEbHuBQ){OiMAbXJfpU = true;}
      else if(XuKKEbHuBQ == luyBCYcVqf){SLpYhWqJUi = true;}
      if(CFkHTEHmVs == qfIUFXMRdp){lCnsRFzxfJ = true;}
      if(MUSZfVATqa == ffZohSmqeK){xzMHPNTlxO = true;}
      if(KPzlRHetOH == MwusceokIK){aWNSUkVPql = true;}
      while(qfIUFXMRdp == CFkHTEHmVs){JoubgzoBTP = true;}
      while(ffZohSmqeK == ffZohSmqeK){tUQSQSEbKM = true;}
      while(MwusceokIK == MwusceokIK){xlrZoUOIyk = true;}
      if(VKZHIyyEaK == true){VKZHIyyEaK = false;}
      if(zSzKprUUcl == true){zSzKprUUcl = false;}
      if(nPQpDtjPra == true){nPQpDtjPra = false;}
      if(ibJTUVGSgi == true){ibJTUVGSgi = false;}
      if(TiQTKtxkCj == true){TiQTKtxkCj = false;}
      if(KUHWVFtiEN == true){KUHWVFtiEN = false;}
      if(OiMAbXJfpU == true){OiMAbXJfpU = false;}
      if(lCnsRFzxfJ == true){lCnsRFzxfJ = false;}
      if(xzMHPNTlxO == true){xzMHPNTlxO = false;}
      if(aWNSUkVPql == true){aWNSUkVPql = false;}
      if(jQtgyHgOFQ == true){jQtgyHgOFQ = false;}
      if(GxDtPOVFjN == true){GxDtPOVFjN = false;}
      if(EWhbsOnUYf == true){EWhbsOnUYf = false;}
      if(iiFsZgEfJI == true){iiFsZgEfJI = false;}
      if(gFgfHdTTDF == true){gFgfHdTTDF = false;}
      if(PQechMiRmi == true){PQechMiRmi = false;}
      if(SLpYhWqJUi == true){SLpYhWqJUi = false;}
      if(JoubgzoBTP == true){JoubgzoBTP = false;}
      if(tUQSQSEbKM == true){tUQSQSEbKM = false;}
      if(xlrZoUOIyk == true){xlrZoUOIyk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZKBZZILFHX
{ 
  void AxRgbmqzIz()
  { 
      bool ggaLIimgrz = false;
      bool uDzdPHkqQe = false;
      bool xiVjxtchiQ = false;
      bool YOKWwhLGZG = false;
      bool riIKzYLoKQ = false;
      bool lppqPxKqOO = false;
      bool FEyaZfrbhh = false;
      bool wdQJmNaLjX = false;
      bool inWReiYTGy = false;
      bool WTrKBmkgkS = false;
      bool giHcUIYfDB = false;
      bool WzHpfRgfwp = false;
      bool HYViKblFIA = false;
      bool csZQqAfsxV = false;
      bool KrQFbXLCej = false;
      bool FEjtKIMYSr = false;
      bool WSXDXcYpyf = false;
      bool knhZePHPGl = false;
      bool PiaXtXIeGi = false;
      bool mHaFzrUNgz = false;
      string ChctuJImUc;
      string ESWcTYqKyZ;
      string eRgxosbJIl;
      string bKrqbmnBdq;
      string BqyzNbfrhs;
      string dpeBYkBeEC;
      string gyehBtafAg;
      string kpgHYmTgiN;
      string NjbOHkepRq;
      string lIwaKCMPyT;
      string BzqBHnJXck;
      string RTupnxWPaQ;
      string OjOJtcsFwV;
      string aEiPLNrZGT;
      string bHNgZRMFlN;
      string fwngFQkhGe;
      string uDaGJMkfea;
      string EwJHoGVgic;
      string PmSipePBJt;
      string cKTaYXgHWM;
      if(ChctuJImUc == BzqBHnJXck){ggaLIimgrz = true;}
      else if(BzqBHnJXck == ChctuJImUc){giHcUIYfDB = true;}
      if(ESWcTYqKyZ == RTupnxWPaQ){uDzdPHkqQe = true;}
      else if(RTupnxWPaQ == ESWcTYqKyZ){WzHpfRgfwp = true;}
      if(eRgxosbJIl == OjOJtcsFwV){xiVjxtchiQ = true;}
      else if(OjOJtcsFwV == eRgxosbJIl){HYViKblFIA = true;}
      if(bKrqbmnBdq == aEiPLNrZGT){YOKWwhLGZG = true;}
      else if(aEiPLNrZGT == bKrqbmnBdq){csZQqAfsxV = true;}
      if(BqyzNbfrhs == bHNgZRMFlN){riIKzYLoKQ = true;}
      else if(bHNgZRMFlN == BqyzNbfrhs){KrQFbXLCej = true;}
      if(dpeBYkBeEC == fwngFQkhGe){lppqPxKqOO = true;}
      else if(fwngFQkhGe == dpeBYkBeEC){FEjtKIMYSr = true;}
      if(gyehBtafAg == uDaGJMkfea){FEyaZfrbhh = true;}
      else if(uDaGJMkfea == gyehBtafAg){WSXDXcYpyf = true;}
      if(kpgHYmTgiN == EwJHoGVgic){wdQJmNaLjX = true;}
      if(NjbOHkepRq == PmSipePBJt){inWReiYTGy = true;}
      if(lIwaKCMPyT == cKTaYXgHWM){WTrKBmkgkS = true;}
      while(EwJHoGVgic == kpgHYmTgiN){knhZePHPGl = true;}
      while(PmSipePBJt == PmSipePBJt){PiaXtXIeGi = true;}
      while(cKTaYXgHWM == cKTaYXgHWM){mHaFzrUNgz = true;}
      if(ggaLIimgrz == true){ggaLIimgrz = false;}
      if(uDzdPHkqQe == true){uDzdPHkqQe = false;}
      if(xiVjxtchiQ == true){xiVjxtchiQ = false;}
      if(YOKWwhLGZG == true){YOKWwhLGZG = false;}
      if(riIKzYLoKQ == true){riIKzYLoKQ = false;}
      if(lppqPxKqOO == true){lppqPxKqOO = false;}
      if(FEyaZfrbhh == true){FEyaZfrbhh = false;}
      if(wdQJmNaLjX == true){wdQJmNaLjX = false;}
      if(inWReiYTGy == true){inWReiYTGy = false;}
      if(WTrKBmkgkS == true){WTrKBmkgkS = false;}
      if(giHcUIYfDB == true){giHcUIYfDB = false;}
      if(WzHpfRgfwp == true){WzHpfRgfwp = false;}
      if(HYViKblFIA == true){HYViKblFIA = false;}
      if(csZQqAfsxV == true){csZQqAfsxV = false;}
      if(KrQFbXLCej == true){KrQFbXLCej = false;}
      if(FEjtKIMYSr == true){FEjtKIMYSr = false;}
      if(WSXDXcYpyf == true){WSXDXcYpyf = false;}
      if(knhZePHPGl == true){knhZePHPGl = false;}
      if(PiaXtXIeGi == true){PiaXtXIeGi = false;}
      if(mHaFzrUNgz == true){mHaFzrUNgz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LIUTYZHJBE
{ 
  void cchCFtmqcJ()
  { 
      bool LfikidiOZz = false;
      bool uzeIyBxNrX = false;
      bool SQmEZwLUxn = false;
      bool ZEaBbGhqQn = false;
      bool NslKVriAHy = false;
      bool tNAHNuseKm = false;
      bool SNQlZqYcgr = false;
      bool TFwEJYdbih = false;
      bool NKNzsLDSnf = false;
      bool NCfdUAcAkd = false;
      bool SFTPeoRwxn = false;
      bool RQucYHzQrN = false;
      bool nFnAeQYRiJ = false;
      bool ucqEOHpyTD = false;
      bool tGVzOwHDEN = false;
      bool ALIWpMRTjO = false;
      bool PzMmsoYqNR = false;
      bool RAxnTgjnlh = false;
      bool IVMVJiUUOC = false;
      bool pWNFntsiGZ = false;
      string pIqXWjYIiF;
      string MkQkJxjsNa;
      string ZytfkyWRwJ;
      string hZCktxuZrq;
      string hpBZdepskD;
      string AIdUKrOKmX;
      string NHMYWlieqL;
      string BJBWrjwTCG;
      string IcfsIYwgZC;
      string ikmTcaccCq;
      string uKCZBpHGca;
      string utHgPjaSQx;
      string pCEocPWgsR;
      string GTRKKxaGqS;
      string RoEzGocFDs;
      string zKLFAsFMwk;
      string SZNKTacxVS;
      string JUaxfBxFhn;
      string mRcARwHLJR;
      string rNJFzrasef;
      if(pIqXWjYIiF == uKCZBpHGca){LfikidiOZz = true;}
      else if(uKCZBpHGca == pIqXWjYIiF){SFTPeoRwxn = true;}
      if(MkQkJxjsNa == utHgPjaSQx){uzeIyBxNrX = true;}
      else if(utHgPjaSQx == MkQkJxjsNa){RQucYHzQrN = true;}
      if(ZytfkyWRwJ == pCEocPWgsR){SQmEZwLUxn = true;}
      else if(pCEocPWgsR == ZytfkyWRwJ){nFnAeQYRiJ = true;}
      if(hZCktxuZrq == GTRKKxaGqS){ZEaBbGhqQn = true;}
      else if(GTRKKxaGqS == hZCktxuZrq){ucqEOHpyTD = true;}
      if(hpBZdepskD == RoEzGocFDs){NslKVriAHy = true;}
      else if(RoEzGocFDs == hpBZdepskD){tGVzOwHDEN = true;}
      if(AIdUKrOKmX == zKLFAsFMwk){tNAHNuseKm = true;}
      else if(zKLFAsFMwk == AIdUKrOKmX){ALIWpMRTjO = true;}
      if(NHMYWlieqL == SZNKTacxVS){SNQlZqYcgr = true;}
      else if(SZNKTacxVS == NHMYWlieqL){PzMmsoYqNR = true;}
      if(BJBWrjwTCG == JUaxfBxFhn){TFwEJYdbih = true;}
      if(IcfsIYwgZC == mRcARwHLJR){NKNzsLDSnf = true;}
      if(ikmTcaccCq == rNJFzrasef){NCfdUAcAkd = true;}
      while(JUaxfBxFhn == BJBWrjwTCG){RAxnTgjnlh = true;}
      while(mRcARwHLJR == mRcARwHLJR){IVMVJiUUOC = true;}
      while(rNJFzrasef == rNJFzrasef){pWNFntsiGZ = true;}
      if(LfikidiOZz == true){LfikidiOZz = false;}
      if(uzeIyBxNrX == true){uzeIyBxNrX = false;}
      if(SQmEZwLUxn == true){SQmEZwLUxn = false;}
      if(ZEaBbGhqQn == true){ZEaBbGhqQn = false;}
      if(NslKVriAHy == true){NslKVriAHy = false;}
      if(tNAHNuseKm == true){tNAHNuseKm = false;}
      if(SNQlZqYcgr == true){SNQlZqYcgr = false;}
      if(TFwEJYdbih == true){TFwEJYdbih = false;}
      if(NKNzsLDSnf == true){NKNzsLDSnf = false;}
      if(NCfdUAcAkd == true){NCfdUAcAkd = false;}
      if(SFTPeoRwxn == true){SFTPeoRwxn = false;}
      if(RQucYHzQrN == true){RQucYHzQrN = false;}
      if(nFnAeQYRiJ == true){nFnAeQYRiJ = false;}
      if(ucqEOHpyTD == true){ucqEOHpyTD = false;}
      if(tGVzOwHDEN == true){tGVzOwHDEN = false;}
      if(ALIWpMRTjO == true){ALIWpMRTjO = false;}
      if(PzMmsoYqNR == true){PzMmsoYqNR = false;}
      if(RAxnTgjnlh == true){RAxnTgjnlh = false;}
      if(IVMVJiUUOC == true){IVMVJiUUOC = false;}
      if(pWNFntsiGZ == true){pWNFntsiGZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PJLKZNMWRM
{ 
  void dxDFyeBMwU()
  { 
      bool dUoHCEzBVs = false;
      bool OTmgVCCxxd = false;
      bool ZXlwhKcuhu = false;
      bool qkoDiTndIG = false;
      bool LrdZnoGccs = false;
      bool RLUQZGisZr = false;
      bool aETZCcdiyC = false;
      bool OXopRhtLHr = false;
      bool EARnceQYdc = false;
      bool jtEPeGYDWL = false;
      bool LWeadsWeyr = false;
      bool LWkgnalexX = false;
      bool MEFVRTSYKL = false;
      bool IqowfgVqJi = false;
      bool HlakQNIXbE = false;
      bool UtFzzHRIIJ = false;
      bool ayTmjUhoBG = false;
      bool FtUNQacTFD = false;
      bool LuwGpOkpwY = false;
      bool PMhzIIRnBu = false;
      string pPnPfwJzhz;
      string pDOKlnTXyl;
      string jiMwduFANz;
      string rfnVVMitll;
      string wiVRWMNEje;
      string XKmBtHCqkj;
      string pJlhGKPsnY;
      string FZlMpBNuYR;
      string gBPhahrlaO;
      string JqIBulxmKM;
      string wUQKYyYZLr;
      string tHRTDosDHY;
      string SdRYPORjRD;
      string EZjMULkFJc;
      string JRZhUBZnyG;
      string rsfktRCquK;
      string fnIHnTWEzq;
      string DntdPADiEN;
      string nclKKKtzSC;
      string IsKywUJRtA;
      if(pPnPfwJzhz == wUQKYyYZLr){dUoHCEzBVs = true;}
      else if(wUQKYyYZLr == pPnPfwJzhz){LWeadsWeyr = true;}
      if(pDOKlnTXyl == tHRTDosDHY){OTmgVCCxxd = true;}
      else if(tHRTDosDHY == pDOKlnTXyl){LWkgnalexX = true;}
      if(jiMwduFANz == SdRYPORjRD){ZXlwhKcuhu = true;}
      else if(SdRYPORjRD == jiMwduFANz){MEFVRTSYKL = true;}
      if(rfnVVMitll == EZjMULkFJc){qkoDiTndIG = true;}
      else if(EZjMULkFJc == rfnVVMitll){IqowfgVqJi = true;}
      if(wiVRWMNEje == JRZhUBZnyG){LrdZnoGccs = true;}
      else if(JRZhUBZnyG == wiVRWMNEje){HlakQNIXbE = true;}
      if(XKmBtHCqkj == rsfktRCquK){RLUQZGisZr = true;}
      else if(rsfktRCquK == XKmBtHCqkj){UtFzzHRIIJ = true;}
      if(pJlhGKPsnY == fnIHnTWEzq){aETZCcdiyC = true;}
      else if(fnIHnTWEzq == pJlhGKPsnY){ayTmjUhoBG = true;}
      if(FZlMpBNuYR == DntdPADiEN){OXopRhtLHr = true;}
      if(gBPhahrlaO == nclKKKtzSC){EARnceQYdc = true;}
      if(JqIBulxmKM == IsKywUJRtA){jtEPeGYDWL = true;}
      while(DntdPADiEN == FZlMpBNuYR){FtUNQacTFD = true;}
      while(nclKKKtzSC == nclKKKtzSC){LuwGpOkpwY = true;}
      while(IsKywUJRtA == IsKywUJRtA){PMhzIIRnBu = true;}
      if(dUoHCEzBVs == true){dUoHCEzBVs = false;}
      if(OTmgVCCxxd == true){OTmgVCCxxd = false;}
      if(ZXlwhKcuhu == true){ZXlwhKcuhu = false;}
      if(qkoDiTndIG == true){qkoDiTndIG = false;}
      if(LrdZnoGccs == true){LrdZnoGccs = false;}
      if(RLUQZGisZr == true){RLUQZGisZr = false;}
      if(aETZCcdiyC == true){aETZCcdiyC = false;}
      if(OXopRhtLHr == true){OXopRhtLHr = false;}
      if(EARnceQYdc == true){EARnceQYdc = false;}
      if(jtEPeGYDWL == true){jtEPeGYDWL = false;}
      if(LWeadsWeyr == true){LWeadsWeyr = false;}
      if(LWkgnalexX == true){LWkgnalexX = false;}
      if(MEFVRTSYKL == true){MEFVRTSYKL = false;}
      if(IqowfgVqJi == true){IqowfgVqJi = false;}
      if(HlakQNIXbE == true){HlakQNIXbE = false;}
      if(UtFzzHRIIJ == true){UtFzzHRIIJ = false;}
      if(ayTmjUhoBG == true){ayTmjUhoBG = false;}
      if(FtUNQacTFD == true){FtUNQacTFD = false;}
      if(LuwGpOkpwY == true){LuwGpOkpwY = false;}
      if(PMhzIIRnBu == true){PMhzIIRnBu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBSCIBXHVC
{ 
  void LtnAYkwifA()
  { 
      bool WhzolVNOec = false;
      bool FQWOTbmhht = false;
      bool LDFzmBASsy = false;
      bool qUVpsrEWir = false;
      bool fOrLVKbjTC = false;
      bool yJpKoSbABj = false;
      bool UtVgljtfVb = false;
      bool XQzoOwLsdc = false;
      bool YQzpzheLBZ = false;
      bool PDUyXksLZk = false;
      bool PuOqehKAur = false;
      bool HhWYKEuegD = false;
      bool FiewLTwARc = false;
      bool DATrNdBHLR = false;
      bool XdPIRggumS = false;
      bool pNdVffQRfK = false;
      bool lJiSoHOdLg = false;
      bool CmTPfaTVde = false;
      bool lANzloVxLg = false;
      bool NibAeNuxSK = false;
      string nFDBaKtWfj;
      string BflORoRDhq;
      string BAXOOLkpCg;
      string PURVjrNNBZ;
      string FdRDWaeaSX;
      string NQRRZngnmP;
      string YDTzTgNQdY;
      string aEBHlXhUrm;
      string gKXeSzDAuw;
      string KYZlABJSip;
      string MNwswJOJfC;
      string FMwAhOeofU;
      string cNUhOCdPGj;
      string NPkBZTNehJ;
      string jtTspybZDl;
      string VUlOMzrOet;
      string eyCunoatZO;
      string AAGWjisaqP;
      string ZDLUNsdWoa;
      string azzndlqYFA;
      if(nFDBaKtWfj == MNwswJOJfC){WhzolVNOec = true;}
      else if(MNwswJOJfC == nFDBaKtWfj){PuOqehKAur = true;}
      if(BflORoRDhq == FMwAhOeofU){FQWOTbmhht = true;}
      else if(FMwAhOeofU == BflORoRDhq){HhWYKEuegD = true;}
      if(BAXOOLkpCg == cNUhOCdPGj){LDFzmBASsy = true;}
      else if(cNUhOCdPGj == BAXOOLkpCg){FiewLTwARc = true;}
      if(PURVjrNNBZ == NPkBZTNehJ){qUVpsrEWir = true;}
      else if(NPkBZTNehJ == PURVjrNNBZ){DATrNdBHLR = true;}
      if(FdRDWaeaSX == jtTspybZDl){fOrLVKbjTC = true;}
      else if(jtTspybZDl == FdRDWaeaSX){XdPIRggumS = true;}
      if(NQRRZngnmP == VUlOMzrOet){yJpKoSbABj = true;}
      else if(VUlOMzrOet == NQRRZngnmP){pNdVffQRfK = true;}
      if(YDTzTgNQdY == eyCunoatZO){UtVgljtfVb = true;}
      else if(eyCunoatZO == YDTzTgNQdY){lJiSoHOdLg = true;}
      if(aEBHlXhUrm == AAGWjisaqP){XQzoOwLsdc = true;}
      if(gKXeSzDAuw == ZDLUNsdWoa){YQzpzheLBZ = true;}
      if(KYZlABJSip == azzndlqYFA){PDUyXksLZk = true;}
      while(AAGWjisaqP == aEBHlXhUrm){CmTPfaTVde = true;}
      while(ZDLUNsdWoa == ZDLUNsdWoa){lANzloVxLg = true;}
      while(azzndlqYFA == azzndlqYFA){NibAeNuxSK = true;}
      if(WhzolVNOec == true){WhzolVNOec = false;}
      if(FQWOTbmhht == true){FQWOTbmhht = false;}
      if(LDFzmBASsy == true){LDFzmBASsy = false;}
      if(qUVpsrEWir == true){qUVpsrEWir = false;}
      if(fOrLVKbjTC == true){fOrLVKbjTC = false;}
      if(yJpKoSbABj == true){yJpKoSbABj = false;}
      if(UtVgljtfVb == true){UtVgljtfVb = false;}
      if(XQzoOwLsdc == true){XQzoOwLsdc = false;}
      if(YQzpzheLBZ == true){YQzpzheLBZ = false;}
      if(PDUyXksLZk == true){PDUyXksLZk = false;}
      if(PuOqehKAur == true){PuOqehKAur = false;}
      if(HhWYKEuegD == true){HhWYKEuegD = false;}
      if(FiewLTwARc == true){FiewLTwARc = false;}
      if(DATrNdBHLR == true){DATrNdBHLR = false;}
      if(XdPIRggumS == true){XdPIRggumS = false;}
      if(pNdVffQRfK == true){pNdVffQRfK = false;}
      if(lJiSoHOdLg == true){lJiSoHOdLg = false;}
      if(CmTPfaTVde == true){CmTPfaTVde = false;}
      if(lANzloVxLg == true){lANzloVxLg = false;}
      if(NibAeNuxSK == true){NibAeNuxSK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEZAQJUIKJ
{ 
  void AJnhSdfDto()
  { 
      bool UnmqJMjpKJ = false;
      bool CItAURsuuM = false;
      bool gmcxaiYYpl = false;
      bool COqfZEMEMt = false;
      bool yCTLpAzzux = false;
      bool UPBJegLpPa = false;
      bool mLzYHmROZP = false;
      bool EoiBNeTQHZ = false;
      bool iZcsQlNgAr = false;
      bool rWnlGlCuEC = false;
      bool ikYesffzuA = false;
      bool NtipqNiGHU = false;
      bool YjNgXgAxtb = false;
      bool cXMEqyAyzk = false;
      bool GOkAexnyts = false;
      bool DunjdzWqHL = false;
      bool fiETWphdzs = false;
      bool MkGWOKyNCZ = false;
      bool sBDBYgjcar = false;
      bool aJpnEWJRcn = false;
      string CRzwdClzoK;
      string ewTOBWIyPB;
      string WSxHRhsoOa;
      string oloUjSSFlH;
      string CZwnEiAtNu;
      string zYitAjTqew;
      string JwjOVrHzdh;
      string EDMHyxVJCh;
      string gyaTbQDuTA;
      string yaZpyGohRL;
      string aBQfquLauC;
      string NKowPKUQlF;
      string oMediddWJr;
      string HnqqHegucg;
      string EbzRlnlcam;
      string kYuMVOVmwM;
      string RoRCuZSxoj;
      string dYnFBMMNru;
      string rAuVGireUr;
      string JtzPOOKxVL;
      if(CRzwdClzoK == aBQfquLauC){UnmqJMjpKJ = true;}
      else if(aBQfquLauC == CRzwdClzoK){ikYesffzuA = true;}
      if(ewTOBWIyPB == NKowPKUQlF){CItAURsuuM = true;}
      else if(NKowPKUQlF == ewTOBWIyPB){NtipqNiGHU = true;}
      if(WSxHRhsoOa == oMediddWJr){gmcxaiYYpl = true;}
      else if(oMediddWJr == WSxHRhsoOa){YjNgXgAxtb = true;}
      if(oloUjSSFlH == HnqqHegucg){COqfZEMEMt = true;}
      else if(HnqqHegucg == oloUjSSFlH){cXMEqyAyzk = true;}
      if(CZwnEiAtNu == EbzRlnlcam){yCTLpAzzux = true;}
      else if(EbzRlnlcam == CZwnEiAtNu){GOkAexnyts = true;}
      if(zYitAjTqew == kYuMVOVmwM){UPBJegLpPa = true;}
      else if(kYuMVOVmwM == zYitAjTqew){DunjdzWqHL = true;}
      if(JwjOVrHzdh == RoRCuZSxoj){mLzYHmROZP = true;}
      else if(RoRCuZSxoj == JwjOVrHzdh){fiETWphdzs = true;}
      if(EDMHyxVJCh == dYnFBMMNru){EoiBNeTQHZ = true;}
      if(gyaTbQDuTA == rAuVGireUr){iZcsQlNgAr = true;}
      if(yaZpyGohRL == JtzPOOKxVL){rWnlGlCuEC = true;}
      while(dYnFBMMNru == EDMHyxVJCh){MkGWOKyNCZ = true;}
      while(rAuVGireUr == rAuVGireUr){sBDBYgjcar = true;}
      while(JtzPOOKxVL == JtzPOOKxVL){aJpnEWJRcn = true;}
      if(UnmqJMjpKJ == true){UnmqJMjpKJ = false;}
      if(CItAURsuuM == true){CItAURsuuM = false;}
      if(gmcxaiYYpl == true){gmcxaiYYpl = false;}
      if(COqfZEMEMt == true){COqfZEMEMt = false;}
      if(yCTLpAzzux == true){yCTLpAzzux = false;}
      if(UPBJegLpPa == true){UPBJegLpPa = false;}
      if(mLzYHmROZP == true){mLzYHmROZP = false;}
      if(EoiBNeTQHZ == true){EoiBNeTQHZ = false;}
      if(iZcsQlNgAr == true){iZcsQlNgAr = false;}
      if(rWnlGlCuEC == true){rWnlGlCuEC = false;}
      if(ikYesffzuA == true){ikYesffzuA = false;}
      if(NtipqNiGHU == true){NtipqNiGHU = false;}
      if(YjNgXgAxtb == true){YjNgXgAxtb = false;}
      if(cXMEqyAyzk == true){cXMEqyAyzk = false;}
      if(GOkAexnyts == true){GOkAexnyts = false;}
      if(DunjdzWqHL == true){DunjdzWqHL = false;}
      if(fiETWphdzs == true){fiETWphdzs = false;}
      if(MkGWOKyNCZ == true){MkGWOKyNCZ = false;}
      if(sBDBYgjcar == true){sBDBYgjcar = false;}
      if(aJpnEWJRcn == true){aJpnEWJRcn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TXHIBDFOBB
{ 
  void gjDnJIEbQj()
  { 
      bool uNhSdbOeZc = false;
      bool OJwUrMSiVN = false;
      bool qwqkqTboPu = false;
      bool DYrmDjeTsb = false;
      bool wkyuXQDsyo = false;
      bool dRqhcyWwbK = false;
      bool zYPeYoQIRI = false;
      bool gzosRFxwNZ = false;
      bool QiqaQkhKKE = false;
      bool NhribWVTVh = false;
      bool AtapHecyQW = false;
      bool BZiBsQhoOn = false;
      bool HGyNtyGGQt = false;
      bool jdaeZVHASk = false;
      bool IjsmDmzpoL = false;
      bool ngFgasuNuI = false;
      bool YVgVmWzDbX = false;
      bool IhVceXMLJH = false;
      bool zPQFFCXsEf = false;
      bool ZtFJMlCXAf = false;
      string pOROUVbLKt;
      string zyDKiwSETr;
      string sMytswKmtu;
      string PBqubrVkCe;
      string ebHsrfPVXs;
      string ZgQIwcQWVY;
      string KnQPexGHip;
      string ZgCoMRFFBM;
      string goPBUhjhzz;
      string byOcTqKqOu;
      string ZHlhSrebue;
      string WLVJrVYPtw;
      string MYIiObSYVV;
      string GOqGmYChhb;
      string DHlTbPcEkx;
      string SuxRhAyDTq;
      string ZGGYYIUPWS;
      string TpgRrElnGy;
      string yNmXDKQYXl;
      string azOqCxBMuT;
      if(pOROUVbLKt == ZHlhSrebue){uNhSdbOeZc = true;}
      else if(ZHlhSrebue == pOROUVbLKt){AtapHecyQW = true;}
      if(zyDKiwSETr == WLVJrVYPtw){OJwUrMSiVN = true;}
      else if(WLVJrVYPtw == zyDKiwSETr){BZiBsQhoOn = true;}
      if(sMytswKmtu == MYIiObSYVV){qwqkqTboPu = true;}
      else if(MYIiObSYVV == sMytswKmtu){HGyNtyGGQt = true;}
      if(PBqubrVkCe == GOqGmYChhb){DYrmDjeTsb = true;}
      else if(GOqGmYChhb == PBqubrVkCe){jdaeZVHASk = true;}
      if(ebHsrfPVXs == DHlTbPcEkx){wkyuXQDsyo = true;}
      else if(DHlTbPcEkx == ebHsrfPVXs){IjsmDmzpoL = true;}
      if(ZgQIwcQWVY == SuxRhAyDTq){dRqhcyWwbK = true;}
      else if(SuxRhAyDTq == ZgQIwcQWVY){ngFgasuNuI = true;}
      if(KnQPexGHip == ZGGYYIUPWS){zYPeYoQIRI = true;}
      else if(ZGGYYIUPWS == KnQPexGHip){YVgVmWzDbX = true;}
      if(ZgCoMRFFBM == TpgRrElnGy){gzosRFxwNZ = true;}
      if(goPBUhjhzz == yNmXDKQYXl){QiqaQkhKKE = true;}
      if(byOcTqKqOu == azOqCxBMuT){NhribWVTVh = true;}
      while(TpgRrElnGy == ZgCoMRFFBM){IhVceXMLJH = true;}
      while(yNmXDKQYXl == yNmXDKQYXl){zPQFFCXsEf = true;}
      while(azOqCxBMuT == azOqCxBMuT){ZtFJMlCXAf = true;}
      if(uNhSdbOeZc == true){uNhSdbOeZc = false;}
      if(OJwUrMSiVN == true){OJwUrMSiVN = false;}
      if(qwqkqTboPu == true){qwqkqTboPu = false;}
      if(DYrmDjeTsb == true){DYrmDjeTsb = false;}
      if(wkyuXQDsyo == true){wkyuXQDsyo = false;}
      if(dRqhcyWwbK == true){dRqhcyWwbK = false;}
      if(zYPeYoQIRI == true){zYPeYoQIRI = false;}
      if(gzosRFxwNZ == true){gzosRFxwNZ = false;}
      if(QiqaQkhKKE == true){QiqaQkhKKE = false;}
      if(NhribWVTVh == true){NhribWVTVh = false;}
      if(AtapHecyQW == true){AtapHecyQW = false;}
      if(BZiBsQhoOn == true){BZiBsQhoOn = false;}
      if(HGyNtyGGQt == true){HGyNtyGGQt = false;}
      if(jdaeZVHASk == true){jdaeZVHASk = false;}
      if(IjsmDmzpoL == true){IjsmDmzpoL = false;}
      if(ngFgasuNuI == true){ngFgasuNuI = false;}
      if(YVgVmWzDbX == true){YVgVmWzDbX = false;}
      if(IhVceXMLJH == true){IhVceXMLJH = false;}
      if(zPQFFCXsEf == true){zPQFFCXsEf = false;}
      if(ZtFJMlCXAf == true){ZtFJMlCXAf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CODQPTORGM
{ 
  void GRcyiAlQIK()
  { 
      bool gMHFZYYgXa = false;
      bool LTkCjJxxcJ = false;
      bool SakMtMDKOb = false;
      bool GhLLlPUsBc = false;
      bool BppoTzXDSX = false;
      bool ahOpyFatKM = false;
      bool UOSwTdHZQT = false;
      bool nDuAIbkwsu = false;
      bool nArqBXSVNf = false;
      bool oainHmXtUo = false;
      bool qylzjWmOhV = false;
      bool TeAPYUVbtw = false;
      bool KlLkeNUHrU = false;
      bool EqaDDoNrGd = false;
      bool kDnqLJZSPm = false;
      bool QwzYeElBTV = false;
      bool CeWMRcExLi = false;
      bool HdUPKGyUYV = false;
      bool mBrFEHrCYy = false;
      bool CLYjbGgaZi = false;
      string ZujjipLEbA;
      string DnChBjJWfx;
      string zkiZWqTmFf;
      string uMETrMBWXP;
      string sRoAsTNrAk;
      string zMMShoMJMq;
      string WYywEpjipo;
      string hlyQEhuifC;
      string damTgiAlkC;
      string zqJgrTSsuD;
      string jdCKDNNwOA;
      string scdKNulePV;
      string pxxmopbRXj;
      string OCmcRzYbQS;
      string UDWkJWNzSw;
      string hndYMlfOVM;
      string kwXekqoBrN;
      string WJOwAlaMdS;
      string cbyaBaXOPe;
      string TJGDgYfrAR;
      if(ZujjipLEbA == jdCKDNNwOA){gMHFZYYgXa = true;}
      else if(jdCKDNNwOA == ZujjipLEbA){qylzjWmOhV = true;}
      if(DnChBjJWfx == scdKNulePV){LTkCjJxxcJ = true;}
      else if(scdKNulePV == DnChBjJWfx){TeAPYUVbtw = true;}
      if(zkiZWqTmFf == pxxmopbRXj){SakMtMDKOb = true;}
      else if(pxxmopbRXj == zkiZWqTmFf){KlLkeNUHrU = true;}
      if(uMETrMBWXP == OCmcRzYbQS){GhLLlPUsBc = true;}
      else if(OCmcRzYbQS == uMETrMBWXP){EqaDDoNrGd = true;}
      if(sRoAsTNrAk == UDWkJWNzSw){BppoTzXDSX = true;}
      else if(UDWkJWNzSw == sRoAsTNrAk){kDnqLJZSPm = true;}
      if(zMMShoMJMq == hndYMlfOVM){ahOpyFatKM = true;}
      else if(hndYMlfOVM == zMMShoMJMq){QwzYeElBTV = true;}
      if(WYywEpjipo == kwXekqoBrN){UOSwTdHZQT = true;}
      else if(kwXekqoBrN == WYywEpjipo){CeWMRcExLi = true;}
      if(hlyQEhuifC == WJOwAlaMdS){nDuAIbkwsu = true;}
      if(damTgiAlkC == cbyaBaXOPe){nArqBXSVNf = true;}
      if(zqJgrTSsuD == TJGDgYfrAR){oainHmXtUo = true;}
      while(WJOwAlaMdS == hlyQEhuifC){HdUPKGyUYV = true;}
      while(cbyaBaXOPe == cbyaBaXOPe){mBrFEHrCYy = true;}
      while(TJGDgYfrAR == TJGDgYfrAR){CLYjbGgaZi = true;}
      if(gMHFZYYgXa == true){gMHFZYYgXa = false;}
      if(LTkCjJxxcJ == true){LTkCjJxxcJ = false;}
      if(SakMtMDKOb == true){SakMtMDKOb = false;}
      if(GhLLlPUsBc == true){GhLLlPUsBc = false;}
      if(BppoTzXDSX == true){BppoTzXDSX = false;}
      if(ahOpyFatKM == true){ahOpyFatKM = false;}
      if(UOSwTdHZQT == true){UOSwTdHZQT = false;}
      if(nDuAIbkwsu == true){nDuAIbkwsu = false;}
      if(nArqBXSVNf == true){nArqBXSVNf = false;}
      if(oainHmXtUo == true){oainHmXtUo = false;}
      if(qylzjWmOhV == true){qylzjWmOhV = false;}
      if(TeAPYUVbtw == true){TeAPYUVbtw = false;}
      if(KlLkeNUHrU == true){KlLkeNUHrU = false;}
      if(EqaDDoNrGd == true){EqaDDoNrGd = false;}
      if(kDnqLJZSPm == true){kDnqLJZSPm = false;}
      if(QwzYeElBTV == true){QwzYeElBTV = false;}
      if(CeWMRcExLi == true){CeWMRcExLi = false;}
      if(HdUPKGyUYV == true){HdUPKGyUYV = false;}
      if(mBrFEHrCYy == true){mBrFEHrCYy = false;}
      if(CLYjbGgaZi == true){CLYjbGgaZi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MNTIDHEZBU
{ 
  void dlGbHpaWuj()
  { 
      bool TtYQulOezW = false;
      bool xhcdKFuejS = false;
      bool SLKbnjwxGr = false;
      bool BFLOTEHyHD = false;
      bool YpjuqETfCh = false;
      bool JBFWPIjxbL = false;
      bool pQXHVrVOJG = false;
      bool ywXgscbPkj = false;
      bool PPuYhzzoyL = false;
      bool UKWwMIRcYy = false;
      bool hFWwjNdXdl = false;
      bool gTLruZVyZV = false;
      bool rgPxknZbTj = false;
      bool KypmBKsyoU = false;
      bool VbKLeBzdAm = false;
      bool lSDDFAoYLu = false;
      bool mCDsbhcXqk = false;
      bool fWJEzQWDSi = false;
      bool nwagxqumgA = false;
      bool UUmsgTXQjx = false;
      string LXtHAAzgLy;
      string gaaxGFjmNV;
      string coDNXzfQoG;
      string zDrMZLGXpB;
      string KDAKimwPRg;
      string VPZTuWTgiA;
      string UhrFyciOWu;
      string yLwMKZorek;
      string DPzHjjdXQD;
      string qZnogbKtLF;
      string DgsWiJSNIU;
      string hbCyxEijUO;
      string zKxSDXWHeh;
      string OtfYgVWcYa;
      string QPPwVPXpqb;
      string saYxGriZSK;
      string lLhZGmucQa;
      string gGLtxiuBxn;
      string zgPConUiRn;
      string lxJNnFgpoh;
      if(LXtHAAzgLy == DgsWiJSNIU){TtYQulOezW = true;}
      else if(DgsWiJSNIU == LXtHAAzgLy){hFWwjNdXdl = true;}
      if(gaaxGFjmNV == hbCyxEijUO){xhcdKFuejS = true;}
      else if(hbCyxEijUO == gaaxGFjmNV){gTLruZVyZV = true;}
      if(coDNXzfQoG == zKxSDXWHeh){SLKbnjwxGr = true;}
      else if(zKxSDXWHeh == coDNXzfQoG){rgPxknZbTj = true;}
      if(zDrMZLGXpB == OtfYgVWcYa){BFLOTEHyHD = true;}
      else if(OtfYgVWcYa == zDrMZLGXpB){KypmBKsyoU = true;}
      if(KDAKimwPRg == QPPwVPXpqb){YpjuqETfCh = true;}
      else if(QPPwVPXpqb == KDAKimwPRg){VbKLeBzdAm = true;}
      if(VPZTuWTgiA == saYxGriZSK){JBFWPIjxbL = true;}
      else if(saYxGriZSK == VPZTuWTgiA){lSDDFAoYLu = true;}
      if(UhrFyciOWu == lLhZGmucQa){pQXHVrVOJG = true;}
      else if(lLhZGmucQa == UhrFyciOWu){mCDsbhcXqk = true;}
      if(yLwMKZorek == gGLtxiuBxn){ywXgscbPkj = true;}
      if(DPzHjjdXQD == zgPConUiRn){PPuYhzzoyL = true;}
      if(qZnogbKtLF == lxJNnFgpoh){UKWwMIRcYy = true;}
      while(gGLtxiuBxn == yLwMKZorek){fWJEzQWDSi = true;}
      while(zgPConUiRn == zgPConUiRn){nwagxqumgA = true;}
      while(lxJNnFgpoh == lxJNnFgpoh){UUmsgTXQjx = true;}
      if(TtYQulOezW == true){TtYQulOezW = false;}
      if(xhcdKFuejS == true){xhcdKFuejS = false;}
      if(SLKbnjwxGr == true){SLKbnjwxGr = false;}
      if(BFLOTEHyHD == true){BFLOTEHyHD = false;}
      if(YpjuqETfCh == true){YpjuqETfCh = false;}
      if(JBFWPIjxbL == true){JBFWPIjxbL = false;}
      if(pQXHVrVOJG == true){pQXHVrVOJG = false;}
      if(ywXgscbPkj == true){ywXgscbPkj = false;}
      if(PPuYhzzoyL == true){PPuYhzzoyL = false;}
      if(UKWwMIRcYy == true){UKWwMIRcYy = false;}
      if(hFWwjNdXdl == true){hFWwjNdXdl = false;}
      if(gTLruZVyZV == true){gTLruZVyZV = false;}
      if(rgPxknZbTj == true){rgPxknZbTj = false;}
      if(KypmBKsyoU == true){KypmBKsyoU = false;}
      if(VbKLeBzdAm == true){VbKLeBzdAm = false;}
      if(lSDDFAoYLu == true){lSDDFAoYLu = false;}
      if(mCDsbhcXqk == true){mCDsbhcXqk = false;}
      if(fWJEzQWDSi == true){fWJEzQWDSi = false;}
      if(nwagxqumgA == true){nwagxqumgA = false;}
      if(UUmsgTXQjx == true){UUmsgTXQjx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CIKUJIFPUA
{ 
  void dosTPllaZY()
  { 
      bool fsjhMlzbyg = false;
      bool hdcxOEPCln = false;
      bool NlXDssrjlR = false;
      bool KyLFIDndeH = false;
      bool nuCTGjWeXW = false;
      bool FRHJmsVfnS = false;
      bool tPpfViRWoL = false;
      bool QkWdARjDxJ = false;
      bool VMMOMrqBSO = false;
      bool hIoLMXFWyW = false;
      bool RApLGTtcJU = false;
      bool JRiewhDaSd = false;
      bool rPEadIwLQb = false;
      bool MMFZqVWAHs = false;
      bool yNrxEPYJOe = false;
      bool UdDTeBwOhy = false;
      bool XiMgHwLIna = false;
      bool LDSZfdXGVN = false;
      bool ilwlHiJkto = false;
      bool ZHSJUOBLoH = false;
      string tSTkoztMzR;
      string cIxbZZjqDb;
      string hblRXBMCTy;
      string HeizAZGynV;
      string iiIeBQYCtu;
      string PgYalRgBNm;
      string mrrAJyYyaA;
      string TkDgszTGPG;
      string cKIYiaFHNi;
      string sEjAiqpHUD;
      string qZasaddqhl;
      string xZkHKcjTRi;
      string rRkrHPBCyB;
      string JMlMOCiOxE;
      string wNZakSScpG;
      string HVokLZnilL;
      string cbsfbkmYrH;
      string sUVNmdrKGn;
      string wXMqtnWABn;
      string OzclbUTsyA;
      if(tSTkoztMzR == qZasaddqhl){fsjhMlzbyg = true;}
      else if(qZasaddqhl == tSTkoztMzR){RApLGTtcJU = true;}
      if(cIxbZZjqDb == xZkHKcjTRi){hdcxOEPCln = true;}
      else if(xZkHKcjTRi == cIxbZZjqDb){JRiewhDaSd = true;}
      if(hblRXBMCTy == rRkrHPBCyB){NlXDssrjlR = true;}
      else if(rRkrHPBCyB == hblRXBMCTy){rPEadIwLQb = true;}
      if(HeizAZGynV == JMlMOCiOxE){KyLFIDndeH = true;}
      else if(JMlMOCiOxE == HeizAZGynV){MMFZqVWAHs = true;}
      if(iiIeBQYCtu == wNZakSScpG){nuCTGjWeXW = true;}
      else if(wNZakSScpG == iiIeBQYCtu){yNrxEPYJOe = true;}
      if(PgYalRgBNm == HVokLZnilL){FRHJmsVfnS = true;}
      else if(HVokLZnilL == PgYalRgBNm){UdDTeBwOhy = true;}
      if(mrrAJyYyaA == cbsfbkmYrH){tPpfViRWoL = true;}
      else if(cbsfbkmYrH == mrrAJyYyaA){XiMgHwLIna = true;}
      if(TkDgszTGPG == sUVNmdrKGn){QkWdARjDxJ = true;}
      if(cKIYiaFHNi == wXMqtnWABn){VMMOMrqBSO = true;}
      if(sEjAiqpHUD == OzclbUTsyA){hIoLMXFWyW = true;}
      while(sUVNmdrKGn == TkDgszTGPG){LDSZfdXGVN = true;}
      while(wXMqtnWABn == wXMqtnWABn){ilwlHiJkto = true;}
      while(OzclbUTsyA == OzclbUTsyA){ZHSJUOBLoH = true;}
      if(fsjhMlzbyg == true){fsjhMlzbyg = false;}
      if(hdcxOEPCln == true){hdcxOEPCln = false;}
      if(NlXDssrjlR == true){NlXDssrjlR = false;}
      if(KyLFIDndeH == true){KyLFIDndeH = false;}
      if(nuCTGjWeXW == true){nuCTGjWeXW = false;}
      if(FRHJmsVfnS == true){FRHJmsVfnS = false;}
      if(tPpfViRWoL == true){tPpfViRWoL = false;}
      if(QkWdARjDxJ == true){QkWdARjDxJ = false;}
      if(VMMOMrqBSO == true){VMMOMrqBSO = false;}
      if(hIoLMXFWyW == true){hIoLMXFWyW = false;}
      if(RApLGTtcJU == true){RApLGTtcJU = false;}
      if(JRiewhDaSd == true){JRiewhDaSd = false;}
      if(rPEadIwLQb == true){rPEadIwLQb = false;}
      if(MMFZqVWAHs == true){MMFZqVWAHs = false;}
      if(yNrxEPYJOe == true){yNrxEPYJOe = false;}
      if(UdDTeBwOhy == true){UdDTeBwOhy = false;}
      if(XiMgHwLIna == true){XiMgHwLIna = false;}
      if(LDSZfdXGVN == true){LDSZfdXGVN = false;}
      if(ilwlHiJkto == true){ilwlHiJkto = false;}
      if(ZHSJUOBLoH == true){ZHSJUOBLoH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MIRHHQXCFQ
{ 
  void RgKJQAICSE()
  { 
      bool MZQcNobUep = false;
      bool bjDkOWFmWb = false;
      bool IGfOUVrIWT = false;
      bool cuOZjzJtRm = false;
      bool mpMmQrdpkh = false;
      bool yycXnGsBHr = false;
      bool wSxKMfVdAO = false;
      bool NKVjoRssyc = false;
      bool qCXoUdRpkd = false;
      bool FImYpUrCZj = false;
      bool WAoVUncsiV = false;
      bool NACeAtuIoh = false;
      bool NfrWIEXwsU = false;
      bool ZpTOGqMBTg = false;
      bool BYGPPFFIYw = false;
      bool YiNqVpIRMP = false;
      bool PfAOuWgnXJ = false;
      bool hsnHgoYbHD = false;
      bool yPXxuqcbrP = false;
      bool htnERUXrUr = false;
      string BjlikWpLXE;
      string BTsWUcsIYq;
      string sqiedcxJbq;
      string lJpDxGmzIA;
      string TOIcSwuhGo;
      string qbnHUJAGEH;
      string YgifRqdoYO;
      string pszXXeiGLh;
      string hPCmAKVihn;
      string FftAamfbKb;
      string SFJrzxbPip;
      string ZtuWZJdueH;
      string UuGjIKyyxj;
      string yHujPbGKmD;
      string hFzrOLkXaR;
      string IjwDGWzYin;
      string ycSyqSyKHy;
      string DTIbYPuOVx;
      string ZaXfbOKrdr;
      string cgbzFElAAw;
      if(BjlikWpLXE == SFJrzxbPip){MZQcNobUep = true;}
      else if(SFJrzxbPip == BjlikWpLXE){WAoVUncsiV = true;}
      if(BTsWUcsIYq == ZtuWZJdueH){bjDkOWFmWb = true;}
      else if(ZtuWZJdueH == BTsWUcsIYq){NACeAtuIoh = true;}
      if(sqiedcxJbq == UuGjIKyyxj){IGfOUVrIWT = true;}
      else if(UuGjIKyyxj == sqiedcxJbq){NfrWIEXwsU = true;}
      if(lJpDxGmzIA == yHujPbGKmD){cuOZjzJtRm = true;}
      else if(yHujPbGKmD == lJpDxGmzIA){ZpTOGqMBTg = true;}
      if(TOIcSwuhGo == hFzrOLkXaR){mpMmQrdpkh = true;}
      else if(hFzrOLkXaR == TOIcSwuhGo){BYGPPFFIYw = true;}
      if(qbnHUJAGEH == IjwDGWzYin){yycXnGsBHr = true;}
      else if(IjwDGWzYin == qbnHUJAGEH){YiNqVpIRMP = true;}
      if(YgifRqdoYO == ycSyqSyKHy){wSxKMfVdAO = true;}
      else if(ycSyqSyKHy == YgifRqdoYO){PfAOuWgnXJ = true;}
      if(pszXXeiGLh == DTIbYPuOVx){NKVjoRssyc = true;}
      if(hPCmAKVihn == ZaXfbOKrdr){qCXoUdRpkd = true;}
      if(FftAamfbKb == cgbzFElAAw){FImYpUrCZj = true;}
      while(DTIbYPuOVx == pszXXeiGLh){hsnHgoYbHD = true;}
      while(ZaXfbOKrdr == ZaXfbOKrdr){yPXxuqcbrP = true;}
      while(cgbzFElAAw == cgbzFElAAw){htnERUXrUr = true;}
      if(MZQcNobUep == true){MZQcNobUep = false;}
      if(bjDkOWFmWb == true){bjDkOWFmWb = false;}
      if(IGfOUVrIWT == true){IGfOUVrIWT = false;}
      if(cuOZjzJtRm == true){cuOZjzJtRm = false;}
      if(mpMmQrdpkh == true){mpMmQrdpkh = false;}
      if(yycXnGsBHr == true){yycXnGsBHr = false;}
      if(wSxKMfVdAO == true){wSxKMfVdAO = false;}
      if(NKVjoRssyc == true){NKVjoRssyc = false;}
      if(qCXoUdRpkd == true){qCXoUdRpkd = false;}
      if(FImYpUrCZj == true){FImYpUrCZj = false;}
      if(WAoVUncsiV == true){WAoVUncsiV = false;}
      if(NACeAtuIoh == true){NACeAtuIoh = false;}
      if(NfrWIEXwsU == true){NfrWIEXwsU = false;}
      if(ZpTOGqMBTg == true){ZpTOGqMBTg = false;}
      if(BYGPPFFIYw == true){BYGPPFFIYw = false;}
      if(YiNqVpIRMP == true){YiNqVpIRMP = false;}
      if(PfAOuWgnXJ == true){PfAOuWgnXJ = false;}
      if(hsnHgoYbHD == true){hsnHgoYbHD = false;}
      if(yPXxuqcbrP == true){yPXxuqcbrP = false;}
      if(htnERUXrUr == true){htnERUXrUr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FHTBVSWLNN
{ 
  void ZzJTWHPrdV()
  { 
      bool WrWymgOeVU = false;
      bool RoJykdNzfe = false;
      bool nAxgiBYLcM = false;
      bool tDxoQDzbdW = false;
      bool wZGfFLXCRx = false;
      bool VIPILWupOk = false;
      bool ICCIZNrThg = false;
      bool elVJiNsQaX = false;
      bool dVtfqlnnct = false;
      bool IJMrOsXxFq = false;
      bool SEUkSilFYy = false;
      bool cdOpHlIVRn = false;
      bool ZEqnXUYdup = false;
      bool owKiFZBIMI = false;
      bool zhPdQetWjb = false;
      bool jBfQROMgNx = false;
      bool JIKiJgSejh = false;
      bool kzJIoqnMWs = false;
      bool ZCsSFmPtRq = false;
      bool MUuPypWfUj = false;
      string WMUdPePZFH;
      string OSkcjGYdpY;
      string xgHawkDrWw;
      string TKHJSaGEaO;
      string reZZDIRqgT;
      string UAfdypEthe;
      string bXCInEKaKI;
      string zUDafSGgWm;
      string SMKDbTddLb;
      string WMVumUcQly;
      string ypfXTzwExf;
      string iWWtMPMygT;
      string agPhllyInL;
      string oouYobfmjb;
      string WYgeszpbiW;
      string HdjSWRaylg;
      string AnQkqsbyEj;
      string jZOEwCzkom;
      string wWZQELFbBX;
      string BhBCbiHunz;
      if(WMUdPePZFH == ypfXTzwExf){WrWymgOeVU = true;}
      else if(ypfXTzwExf == WMUdPePZFH){SEUkSilFYy = true;}
      if(OSkcjGYdpY == iWWtMPMygT){RoJykdNzfe = true;}
      else if(iWWtMPMygT == OSkcjGYdpY){cdOpHlIVRn = true;}
      if(xgHawkDrWw == agPhllyInL){nAxgiBYLcM = true;}
      else if(agPhllyInL == xgHawkDrWw){ZEqnXUYdup = true;}
      if(TKHJSaGEaO == oouYobfmjb){tDxoQDzbdW = true;}
      else if(oouYobfmjb == TKHJSaGEaO){owKiFZBIMI = true;}
      if(reZZDIRqgT == WYgeszpbiW){wZGfFLXCRx = true;}
      else if(WYgeszpbiW == reZZDIRqgT){zhPdQetWjb = true;}
      if(UAfdypEthe == HdjSWRaylg){VIPILWupOk = true;}
      else if(HdjSWRaylg == UAfdypEthe){jBfQROMgNx = true;}
      if(bXCInEKaKI == AnQkqsbyEj){ICCIZNrThg = true;}
      else if(AnQkqsbyEj == bXCInEKaKI){JIKiJgSejh = true;}
      if(zUDafSGgWm == jZOEwCzkom){elVJiNsQaX = true;}
      if(SMKDbTddLb == wWZQELFbBX){dVtfqlnnct = true;}
      if(WMVumUcQly == BhBCbiHunz){IJMrOsXxFq = true;}
      while(jZOEwCzkom == zUDafSGgWm){kzJIoqnMWs = true;}
      while(wWZQELFbBX == wWZQELFbBX){ZCsSFmPtRq = true;}
      while(BhBCbiHunz == BhBCbiHunz){MUuPypWfUj = true;}
      if(WrWymgOeVU == true){WrWymgOeVU = false;}
      if(RoJykdNzfe == true){RoJykdNzfe = false;}
      if(nAxgiBYLcM == true){nAxgiBYLcM = false;}
      if(tDxoQDzbdW == true){tDxoQDzbdW = false;}
      if(wZGfFLXCRx == true){wZGfFLXCRx = false;}
      if(VIPILWupOk == true){VIPILWupOk = false;}
      if(ICCIZNrThg == true){ICCIZNrThg = false;}
      if(elVJiNsQaX == true){elVJiNsQaX = false;}
      if(dVtfqlnnct == true){dVtfqlnnct = false;}
      if(IJMrOsXxFq == true){IJMrOsXxFq = false;}
      if(SEUkSilFYy == true){SEUkSilFYy = false;}
      if(cdOpHlIVRn == true){cdOpHlIVRn = false;}
      if(ZEqnXUYdup == true){ZEqnXUYdup = false;}
      if(owKiFZBIMI == true){owKiFZBIMI = false;}
      if(zhPdQetWjb == true){zhPdQetWjb = false;}
      if(jBfQROMgNx == true){jBfQROMgNx = false;}
      if(JIKiJgSejh == true){JIKiJgSejh = false;}
      if(kzJIoqnMWs == true){kzJIoqnMWs = false;}
      if(ZCsSFmPtRq == true){ZCsSFmPtRq = false;}
      if(MUuPypWfUj == true){MUuPypWfUj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NTMZLFBKKH
{ 
  void VjmKfukFqG()
  { 
      bool bsAJtmzBAB = false;
      bool jGmFruDDtp = false;
      bool qMNsCFCbUH = false;
      bool SXOiKXwHkC = false;
      bool dNmHUQkgMs = false;
      bool CPuREPeHHn = false;
      bool jXgrhMrEuT = false;
      bool yuSqLdYFYl = false;
      bool UVObFDcwdt = false;
      bool roAxRGfuYI = false;
      bool XglstGxDFZ = false;
      bool qZiUSOIFle = false;
      bool iwZBaJuUZF = false;
      bool xdgQOnjVgz = false;
      bool FZpDDSGedC = false;
      bool xaItYbGkRj = false;
      bool KbcAcMrSGe = false;
      bool emXmYJFVxH = false;
      bool DPqXIWVmqm = false;
      bool gyDxndwpap = false;
      string sxQXQVtJOU;
      string GFeIcjkdJU;
      string QkrbjLImJE;
      string hcsYriVoQJ;
      string EcKnFwhQBE;
      string jjmSRHFonE;
      string NHAJldMFQs;
      string NwNAPmaDWm;
      string dqlETyoaGj;
      string dgALuxbACa;
      string jbzHpnWmCe;
      string gBRBaWUuon;
      string nlygPgwBES;
      string KZBuDBqeOf;
      string aCYbCcPzjY;
      string cgKNmxdSrJ;
      string rUiiTGAVyZ;
      string eogINlNWel;
      string RwReodPmIF;
      string XYlEnFSoHu;
      if(sxQXQVtJOU == jbzHpnWmCe){bsAJtmzBAB = true;}
      else if(jbzHpnWmCe == sxQXQVtJOU){XglstGxDFZ = true;}
      if(GFeIcjkdJU == gBRBaWUuon){jGmFruDDtp = true;}
      else if(gBRBaWUuon == GFeIcjkdJU){qZiUSOIFle = true;}
      if(QkrbjLImJE == nlygPgwBES){qMNsCFCbUH = true;}
      else if(nlygPgwBES == QkrbjLImJE){iwZBaJuUZF = true;}
      if(hcsYriVoQJ == KZBuDBqeOf){SXOiKXwHkC = true;}
      else if(KZBuDBqeOf == hcsYriVoQJ){xdgQOnjVgz = true;}
      if(EcKnFwhQBE == aCYbCcPzjY){dNmHUQkgMs = true;}
      else if(aCYbCcPzjY == EcKnFwhQBE){FZpDDSGedC = true;}
      if(jjmSRHFonE == cgKNmxdSrJ){CPuREPeHHn = true;}
      else if(cgKNmxdSrJ == jjmSRHFonE){xaItYbGkRj = true;}
      if(NHAJldMFQs == rUiiTGAVyZ){jXgrhMrEuT = true;}
      else if(rUiiTGAVyZ == NHAJldMFQs){KbcAcMrSGe = true;}
      if(NwNAPmaDWm == eogINlNWel){yuSqLdYFYl = true;}
      if(dqlETyoaGj == RwReodPmIF){UVObFDcwdt = true;}
      if(dgALuxbACa == XYlEnFSoHu){roAxRGfuYI = true;}
      while(eogINlNWel == NwNAPmaDWm){emXmYJFVxH = true;}
      while(RwReodPmIF == RwReodPmIF){DPqXIWVmqm = true;}
      while(XYlEnFSoHu == XYlEnFSoHu){gyDxndwpap = true;}
      if(bsAJtmzBAB == true){bsAJtmzBAB = false;}
      if(jGmFruDDtp == true){jGmFruDDtp = false;}
      if(qMNsCFCbUH == true){qMNsCFCbUH = false;}
      if(SXOiKXwHkC == true){SXOiKXwHkC = false;}
      if(dNmHUQkgMs == true){dNmHUQkgMs = false;}
      if(CPuREPeHHn == true){CPuREPeHHn = false;}
      if(jXgrhMrEuT == true){jXgrhMrEuT = false;}
      if(yuSqLdYFYl == true){yuSqLdYFYl = false;}
      if(UVObFDcwdt == true){UVObFDcwdt = false;}
      if(roAxRGfuYI == true){roAxRGfuYI = false;}
      if(XglstGxDFZ == true){XglstGxDFZ = false;}
      if(qZiUSOIFle == true){qZiUSOIFle = false;}
      if(iwZBaJuUZF == true){iwZBaJuUZF = false;}
      if(xdgQOnjVgz == true){xdgQOnjVgz = false;}
      if(FZpDDSGedC == true){FZpDDSGedC = false;}
      if(xaItYbGkRj == true){xaItYbGkRj = false;}
      if(KbcAcMrSGe == true){KbcAcMrSGe = false;}
      if(emXmYJFVxH == true){emXmYJFVxH = false;}
      if(DPqXIWVmqm == true){DPqXIWVmqm = false;}
      if(gyDxndwpap == true){gyDxndwpap = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LIIZDKNDVN
{ 
  void VRkCNwZyJo()
  { 
      bool SQxaooSWnK = false;
      bool JAVIetZAZk = false;
      bool MeAjSNVfjf = false;
      bool VgfBVcubej = false;
      bool hnBzSbCFlM = false;
      bool CrXXamQNIa = false;
      bool TmmIocUUlB = false;
      bool zyVoCYdARp = false;
      bool KQtWccIHZi = false;
      bool MgTDQuArJo = false;
      bool HhSjNEWhUB = false;
      bool IPwSQDrQeM = false;
      bool TMtDoReRYH = false;
      bool XlpbicxJIY = false;
      bool FamYZwjBmM = false;
      bool DiMxUumOuu = false;
      bool ZEJNcWZUin = false;
      bool FhHGGsYVcs = false;
      bool gceLEnZsGm = false;
      bool oiONzAQZuD = false;
      string isohHeZsxu;
      string AnIweAqxFY;
      string rHkEWCOpWW;
      string VpPXlEHznM;
      string EYdkOoKUBm;
      string iLJTXbHkLF;
      string PjVaYKYjKZ;
      string rqIsTTczoh;
      string rtnjmJfwzK;
      string wWnixUCCME;
      string QZKbtqDQzE;
      string yIudMVulnO;
      string dbjAdVDZuz;
      string RZmkQRiMow;
      string GOxuLnbKVa;
      string YPOxZnoKyY;
      string ndUzlXUKMu;
      string liwqIPdono;
      string tsDTZBLoKc;
      string bYNQHcsxIm;
      if(isohHeZsxu == QZKbtqDQzE){SQxaooSWnK = true;}
      else if(QZKbtqDQzE == isohHeZsxu){HhSjNEWhUB = true;}
      if(AnIweAqxFY == yIudMVulnO){JAVIetZAZk = true;}
      else if(yIudMVulnO == AnIweAqxFY){IPwSQDrQeM = true;}
      if(rHkEWCOpWW == dbjAdVDZuz){MeAjSNVfjf = true;}
      else if(dbjAdVDZuz == rHkEWCOpWW){TMtDoReRYH = true;}
      if(VpPXlEHznM == RZmkQRiMow){VgfBVcubej = true;}
      else if(RZmkQRiMow == VpPXlEHznM){XlpbicxJIY = true;}
      if(EYdkOoKUBm == GOxuLnbKVa){hnBzSbCFlM = true;}
      else if(GOxuLnbKVa == EYdkOoKUBm){FamYZwjBmM = true;}
      if(iLJTXbHkLF == YPOxZnoKyY){CrXXamQNIa = true;}
      else if(YPOxZnoKyY == iLJTXbHkLF){DiMxUumOuu = true;}
      if(PjVaYKYjKZ == ndUzlXUKMu){TmmIocUUlB = true;}
      else if(ndUzlXUKMu == PjVaYKYjKZ){ZEJNcWZUin = true;}
      if(rqIsTTczoh == liwqIPdono){zyVoCYdARp = true;}
      if(rtnjmJfwzK == tsDTZBLoKc){KQtWccIHZi = true;}
      if(wWnixUCCME == bYNQHcsxIm){MgTDQuArJo = true;}
      while(liwqIPdono == rqIsTTczoh){FhHGGsYVcs = true;}
      while(tsDTZBLoKc == tsDTZBLoKc){gceLEnZsGm = true;}
      while(bYNQHcsxIm == bYNQHcsxIm){oiONzAQZuD = true;}
      if(SQxaooSWnK == true){SQxaooSWnK = false;}
      if(JAVIetZAZk == true){JAVIetZAZk = false;}
      if(MeAjSNVfjf == true){MeAjSNVfjf = false;}
      if(VgfBVcubej == true){VgfBVcubej = false;}
      if(hnBzSbCFlM == true){hnBzSbCFlM = false;}
      if(CrXXamQNIa == true){CrXXamQNIa = false;}
      if(TmmIocUUlB == true){TmmIocUUlB = false;}
      if(zyVoCYdARp == true){zyVoCYdARp = false;}
      if(KQtWccIHZi == true){KQtWccIHZi = false;}
      if(MgTDQuArJo == true){MgTDQuArJo = false;}
      if(HhSjNEWhUB == true){HhSjNEWhUB = false;}
      if(IPwSQDrQeM == true){IPwSQDrQeM = false;}
      if(TMtDoReRYH == true){TMtDoReRYH = false;}
      if(XlpbicxJIY == true){XlpbicxJIY = false;}
      if(FamYZwjBmM == true){FamYZwjBmM = false;}
      if(DiMxUumOuu == true){DiMxUumOuu = false;}
      if(ZEJNcWZUin == true){ZEJNcWZUin = false;}
      if(FhHGGsYVcs == true){FhHGGsYVcs = false;}
      if(gceLEnZsGm == true){gceLEnZsGm = false;}
      if(oiONzAQZuD == true){oiONzAQZuD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZFOBCEYNSP
{ 
  void UXWZhKSXwV()
  { 
      bool ATVmbBRlaF = false;
      bool zqULklPetl = false;
      bool EmTjaBYGNF = false;
      bool nqJisGeQfO = false;
      bool abVVFCKdua = false;
      bool lmnfaNzlMa = false;
      bool cLXVRIglRe = false;
      bool GzzfKbRydX = false;
      bool ptKlTBCcHf = false;
      bool GsDEkPEzEx = false;
      bool UYLQUlnIVz = false;
      bool wBHojhAlCQ = false;
      bool FDdlXMuttt = false;
      bool XRsgCRitRg = false;
      bool NtHIjFlOUD = false;
      bool PRxnqRtYrI = false;
      bool qsNabdHalR = false;
      bool yGTUCLwVCS = false;
      bool ZfZpeFUFok = false;
      bool XJBJpTfggF = false;
      string boUBkYXFPS;
      string TUjAitLfpF;
      string lWiSLyOnip;
      string lrVjwFDUdQ;
      string FFLrCprBLq;
      string qjenJEGBom;
      string KiWYfazzEc;
      string qqCYAgLqQV;
      string FMbrzCMgZq;
      string zBepGVilLa;
      string qrxhAzgGnc;
      string rOkThxHdZc;
      string NRYMdoMMRd;
      string xZeodMPsqz;
      string VGrxyjPKIJ;
      string OELhNYSjEK;
      string mTnJeSjwoU;
      string gNmZGHZbOs;
      string ZBEIPsNwbF;
      string tfogMBShRf;
      if(boUBkYXFPS == qrxhAzgGnc){ATVmbBRlaF = true;}
      else if(qrxhAzgGnc == boUBkYXFPS){UYLQUlnIVz = true;}
      if(TUjAitLfpF == rOkThxHdZc){zqULklPetl = true;}
      else if(rOkThxHdZc == TUjAitLfpF){wBHojhAlCQ = true;}
      if(lWiSLyOnip == NRYMdoMMRd){EmTjaBYGNF = true;}
      else if(NRYMdoMMRd == lWiSLyOnip){FDdlXMuttt = true;}
      if(lrVjwFDUdQ == xZeodMPsqz){nqJisGeQfO = true;}
      else if(xZeodMPsqz == lrVjwFDUdQ){XRsgCRitRg = true;}
      if(FFLrCprBLq == VGrxyjPKIJ){abVVFCKdua = true;}
      else if(VGrxyjPKIJ == FFLrCprBLq){NtHIjFlOUD = true;}
      if(qjenJEGBom == OELhNYSjEK){lmnfaNzlMa = true;}
      else if(OELhNYSjEK == qjenJEGBom){PRxnqRtYrI = true;}
      if(KiWYfazzEc == mTnJeSjwoU){cLXVRIglRe = true;}
      else if(mTnJeSjwoU == KiWYfazzEc){qsNabdHalR = true;}
      if(qqCYAgLqQV == gNmZGHZbOs){GzzfKbRydX = true;}
      if(FMbrzCMgZq == ZBEIPsNwbF){ptKlTBCcHf = true;}
      if(zBepGVilLa == tfogMBShRf){GsDEkPEzEx = true;}
      while(gNmZGHZbOs == qqCYAgLqQV){yGTUCLwVCS = true;}
      while(ZBEIPsNwbF == ZBEIPsNwbF){ZfZpeFUFok = true;}
      while(tfogMBShRf == tfogMBShRf){XJBJpTfggF = true;}
      if(ATVmbBRlaF == true){ATVmbBRlaF = false;}
      if(zqULklPetl == true){zqULklPetl = false;}
      if(EmTjaBYGNF == true){EmTjaBYGNF = false;}
      if(nqJisGeQfO == true){nqJisGeQfO = false;}
      if(abVVFCKdua == true){abVVFCKdua = false;}
      if(lmnfaNzlMa == true){lmnfaNzlMa = false;}
      if(cLXVRIglRe == true){cLXVRIglRe = false;}
      if(GzzfKbRydX == true){GzzfKbRydX = false;}
      if(ptKlTBCcHf == true){ptKlTBCcHf = false;}
      if(GsDEkPEzEx == true){GsDEkPEzEx = false;}
      if(UYLQUlnIVz == true){UYLQUlnIVz = false;}
      if(wBHojhAlCQ == true){wBHojhAlCQ = false;}
      if(FDdlXMuttt == true){FDdlXMuttt = false;}
      if(XRsgCRitRg == true){XRsgCRitRg = false;}
      if(NtHIjFlOUD == true){NtHIjFlOUD = false;}
      if(PRxnqRtYrI == true){PRxnqRtYrI = false;}
      if(qsNabdHalR == true){qsNabdHalR = false;}
      if(yGTUCLwVCS == true){yGTUCLwVCS = false;}
      if(ZfZpeFUFok == true){ZfZpeFUFok = false;}
      if(XJBJpTfggF == true){XJBJpTfggF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OPCWSSENST
{ 
  void sfhgOKUAYh()
  { 
      bool KBnDTSbzwb = false;
      bool hRYxojLdya = false;
      bool AmQfLCrWiy = false;
      bool JqAzirUJDD = false;
      bool EfjfNtkIDK = false;
      bool plrglWjHqQ = false;
      bool aFPySqQYNx = false;
      bool OBatWTDjSQ = false;
      bool RjSXIXyTML = false;
      bool HMRlcyPkNV = false;
      bool cLtGunKxJS = false;
      bool TAoazpmrot = false;
      bool rwMBpCjnRX = false;
      bool ERWwmFpMcU = false;
      bool MBJtrHXqll = false;
      bool LXuSdgzrQs = false;
      bool DWflOBdrmt = false;
      bool AZOUhpmSJi = false;
      bool dsBeMfVDSG = false;
      bool GxwiQpVXfp = false;
      string GaGLuhsqUe;
      string SxxHahtEDa;
      string PQeRzANhSy;
      string UBgfwYBRfi;
      string YIPfMaPbSk;
      string tjaLlowoMu;
      string TKYVJRPRLB;
      string gcXTBHBzEX;
      string kkOgEkZVsG;
      string bLEkPNisVt;
      string LyQQEQLHJe;
      string mxjnKhwrQY;
      string rtXFYUYmEn;
      string XHcKMlUxbm;
      string YSLOSeaPag;
      string RqcwBQaKri;
      string rXCUGfTZbX;
      string MyPdzZhIlt;
      string sIMXWfegIu;
      string LJFstBPqHm;
      if(GaGLuhsqUe == LyQQEQLHJe){KBnDTSbzwb = true;}
      else if(LyQQEQLHJe == GaGLuhsqUe){cLtGunKxJS = true;}
      if(SxxHahtEDa == mxjnKhwrQY){hRYxojLdya = true;}
      else if(mxjnKhwrQY == SxxHahtEDa){TAoazpmrot = true;}
      if(PQeRzANhSy == rtXFYUYmEn){AmQfLCrWiy = true;}
      else if(rtXFYUYmEn == PQeRzANhSy){rwMBpCjnRX = true;}
      if(UBgfwYBRfi == XHcKMlUxbm){JqAzirUJDD = true;}
      else if(XHcKMlUxbm == UBgfwYBRfi){ERWwmFpMcU = true;}
      if(YIPfMaPbSk == YSLOSeaPag){EfjfNtkIDK = true;}
      else if(YSLOSeaPag == YIPfMaPbSk){MBJtrHXqll = true;}
      if(tjaLlowoMu == RqcwBQaKri){plrglWjHqQ = true;}
      else if(RqcwBQaKri == tjaLlowoMu){LXuSdgzrQs = true;}
      if(TKYVJRPRLB == rXCUGfTZbX){aFPySqQYNx = true;}
      else if(rXCUGfTZbX == TKYVJRPRLB){DWflOBdrmt = true;}
      if(gcXTBHBzEX == MyPdzZhIlt){OBatWTDjSQ = true;}
      if(kkOgEkZVsG == sIMXWfegIu){RjSXIXyTML = true;}
      if(bLEkPNisVt == LJFstBPqHm){HMRlcyPkNV = true;}
      while(MyPdzZhIlt == gcXTBHBzEX){AZOUhpmSJi = true;}
      while(sIMXWfegIu == sIMXWfegIu){dsBeMfVDSG = true;}
      while(LJFstBPqHm == LJFstBPqHm){GxwiQpVXfp = true;}
      if(KBnDTSbzwb == true){KBnDTSbzwb = false;}
      if(hRYxojLdya == true){hRYxojLdya = false;}
      if(AmQfLCrWiy == true){AmQfLCrWiy = false;}
      if(JqAzirUJDD == true){JqAzirUJDD = false;}
      if(EfjfNtkIDK == true){EfjfNtkIDK = false;}
      if(plrglWjHqQ == true){plrglWjHqQ = false;}
      if(aFPySqQYNx == true){aFPySqQYNx = false;}
      if(OBatWTDjSQ == true){OBatWTDjSQ = false;}
      if(RjSXIXyTML == true){RjSXIXyTML = false;}
      if(HMRlcyPkNV == true){HMRlcyPkNV = false;}
      if(cLtGunKxJS == true){cLtGunKxJS = false;}
      if(TAoazpmrot == true){TAoazpmrot = false;}
      if(rwMBpCjnRX == true){rwMBpCjnRX = false;}
      if(ERWwmFpMcU == true){ERWwmFpMcU = false;}
      if(MBJtrHXqll == true){MBJtrHXqll = false;}
      if(LXuSdgzrQs == true){LXuSdgzrQs = false;}
      if(DWflOBdrmt == true){DWflOBdrmt = false;}
      if(AZOUhpmSJi == true){AZOUhpmSJi = false;}
      if(dsBeMfVDSG == true){dsBeMfVDSG = false;}
      if(GxwiQpVXfp == true){GxwiQpVXfp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YYLBLVKSAP
{ 
  void XQoQKnAMpY()
  { 
      bool eKWdwOOBOh = false;
      bool swyNGtjShz = false;
      bool dwDzozVbtA = false;
      bool wasyjQwyuE = false;
      bool monkMUYyCV = false;
      bool mwihXhHXnx = false;
      bool slGOlRCAdp = false;
      bool ylWcLnHRmT = false;
      bool ZXZYNzqLaB = false;
      bool IXKxLBiZyt = false;
      bool SYTLWAYGVi = false;
      bool ZpjTXVMhBl = false;
      bool ZqZcgZbYRK = false;
      bool FhSsBBDNBM = false;
      bool akoqaSnpZo = false;
      bool oAYMTazqew = false;
      bool YzoLdrWqSW = false;
      bool SyfoLoChBN = false;
      bool lkzbVEIGYa = false;
      bool BMiFmawcNh = false;
      string PUZhHJmDAy;
      string ctHhJQjpaq;
      string GmwAsrXBxU;
      string eusNUtqOuz;
      string FfhMKBYgnQ;
      string fUyFcbYZnP;
      string kkGeSgBsNP;
      string ZVtakaFipq;
      string TpNfoKxnkr;
      string UQZfOUYCtc;
      string zeTXpKaXTC;
      string WoixutXZpH;
      string jNIUtIwNMQ;
      string BCoMqnWope;
      string jZUhUehckT;
      string wzMlslWycg;
      string NMKCBTAWFH;
      string WhjKXKsZzP;
      string aTbrTCpDTF;
      string RXLIQWORgB;
      if(PUZhHJmDAy == zeTXpKaXTC){eKWdwOOBOh = true;}
      else if(zeTXpKaXTC == PUZhHJmDAy){SYTLWAYGVi = true;}
      if(ctHhJQjpaq == WoixutXZpH){swyNGtjShz = true;}
      else if(WoixutXZpH == ctHhJQjpaq){ZpjTXVMhBl = true;}
      if(GmwAsrXBxU == jNIUtIwNMQ){dwDzozVbtA = true;}
      else if(jNIUtIwNMQ == GmwAsrXBxU){ZqZcgZbYRK = true;}
      if(eusNUtqOuz == BCoMqnWope){wasyjQwyuE = true;}
      else if(BCoMqnWope == eusNUtqOuz){FhSsBBDNBM = true;}
      if(FfhMKBYgnQ == jZUhUehckT){monkMUYyCV = true;}
      else if(jZUhUehckT == FfhMKBYgnQ){akoqaSnpZo = true;}
      if(fUyFcbYZnP == wzMlslWycg){mwihXhHXnx = true;}
      else if(wzMlslWycg == fUyFcbYZnP){oAYMTazqew = true;}
      if(kkGeSgBsNP == NMKCBTAWFH){slGOlRCAdp = true;}
      else if(NMKCBTAWFH == kkGeSgBsNP){YzoLdrWqSW = true;}
      if(ZVtakaFipq == WhjKXKsZzP){ylWcLnHRmT = true;}
      if(TpNfoKxnkr == aTbrTCpDTF){ZXZYNzqLaB = true;}
      if(UQZfOUYCtc == RXLIQWORgB){IXKxLBiZyt = true;}
      while(WhjKXKsZzP == ZVtakaFipq){SyfoLoChBN = true;}
      while(aTbrTCpDTF == aTbrTCpDTF){lkzbVEIGYa = true;}
      while(RXLIQWORgB == RXLIQWORgB){BMiFmawcNh = true;}
      if(eKWdwOOBOh == true){eKWdwOOBOh = false;}
      if(swyNGtjShz == true){swyNGtjShz = false;}
      if(dwDzozVbtA == true){dwDzozVbtA = false;}
      if(wasyjQwyuE == true){wasyjQwyuE = false;}
      if(monkMUYyCV == true){monkMUYyCV = false;}
      if(mwihXhHXnx == true){mwihXhHXnx = false;}
      if(slGOlRCAdp == true){slGOlRCAdp = false;}
      if(ylWcLnHRmT == true){ylWcLnHRmT = false;}
      if(ZXZYNzqLaB == true){ZXZYNzqLaB = false;}
      if(IXKxLBiZyt == true){IXKxLBiZyt = false;}
      if(SYTLWAYGVi == true){SYTLWAYGVi = false;}
      if(ZpjTXVMhBl == true){ZpjTXVMhBl = false;}
      if(ZqZcgZbYRK == true){ZqZcgZbYRK = false;}
      if(FhSsBBDNBM == true){FhSsBBDNBM = false;}
      if(akoqaSnpZo == true){akoqaSnpZo = false;}
      if(oAYMTazqew == true){oAYMTazqew = false;}
      if(YzoLdrWqSW == true){YzoLdrWqSW = false;}
      if(SyfoLoChBN == true){SyfoLoChBN = false;}
      if(lkzbVEIGYa == true){lkzbVEIGYa = false;}
      if(BMiFmawcNh == true){BMiFmawcNh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JZPSPAYJTG
{ 
  void jAUuhMGBLN()
  { 
      bool cqInLlscca = false;
      bool tzcPpCHNGN = false;
      bool AJVotRUIXO = false;
      bool rWhBmTRkMs = false;
      bool PEgIOFfnbk = false;
      bool JLqQaSVSts = false;
      bool QjFOiWRacW = false;
      bool kVBMywbMan = false;
      bool lgflEffQaT = false;
      bool xyqSbfySYq = false;
      bool nFKFAmKdSe = false;
      bool pJqFHjDTJD = false;
      bool pAAJYlehjR = false;
      bool xJmjAfWalR = false;
      bool UByucnGkLr = false;
      bool cdJVAmEBgN = false;
      bool HcsAggVHFa = false;
      bool NchqinCEfk = false;
      bool ftVroTzRiN = false;
      bool bUtXJrIxNu = false;
      string yPwzwrMwxe;
      string gcLDhFBkKW;
      string dHTLjkwYZt;
      string HsHuEhQqQX;
      string JkTLKqrptx;
      string TOjqrqwjOK;
      string unWCXmVQyz;
      string nJTmMrmHBs;
      string sGebasJPCM;
      string lfbGbUOQnX;
      string VaqtIJtxeA;
      string DniVRoJtbd;
      string dGOlNHgNKq;
      string cVTdXROjSQ;
      string yLkBIxxGnl;
      string LToJsPMFfA;
      string cglmWgUFyz;
      string aYaLfRUMcP;
      string KZYXfIgKjI;
      string FIESnRZyea;
      if(yPwzwrMwxe == VaqtIJtxeA){cqInLlscca = true;}
      else if(VaqtIJtxeA == yPwzwrMwxe){nFKFAmKdSe = true;}
      if(gcLDhFBkKW == DniVRoJtbd){tzcPpCHNGN = true;}
      else if(DniVRoJtbd == gcLDhFBkKW){pJqFHjDTJD = true;}
      if(dHTLjkwYZt == dGOlNHgNKq){AJVotRUIXO = true;}
      else if(dGOlNHgNKq == dHTLjkwYZt){pAAJYlehjR = true;}
      if(HsHuEhQqQX == cVTdXROjSQ){rWhBmTRkMs = true;}
      else if(cVTdXROjSQ == HsHuEhQqQX){xJmjAfWalR = true;}
      if(JkTLKqrptx == yLkBIxxGnl){PEgIOFfnbk = true;}
      else if(yLkBIxxGnl == JkTLKqrptx){UByucnGkLr = true;}
      if(TOjqrqwjOK == LToJsPMFfA){JLqQaSVSts = true;}
      else if(LToJsPMFfA == TOjqrqwjOK){cdJVAmEBgN = true;}
      if(unWCXmVQyz == cglmWgUFyz){QjFOiWRacW = true;}
      else if(cglmWgUFyz == unWCXmVQyz){HcsAggVHFa = true;}
      if(nJTmMrmHBs == aYaLfRUMcP){kVBMywbMan = true;}
      if(sGebasJPCM == KZYXfIgKjI){lgflEffQaT = true;}
      if(lfbGbUOQnX == FIESnRZyea){xyqSbfySYq = true;}
      while(aYaLfRUMcP == nJTmMrmHBs){NchqinCEfk = true;}
      while(KZYXfIgKjI == KZYXfIgKjI){ftVroTzRiN = true;}
      while(FIESnRZyea == FIESnRZyea){bUtXJrIxNu = true;}
      if(cqInLlscca == true){cqInLlscca = false;}
      if(tzcPpCHNGN == true){tzcPpCHNGN = false;}
      if(AJVotRUIXO == true){AJVotRUIXO = false;}
      if(rWhBmTRkMs == true){rWhBmTRkMs = false;}
      if(PEgIOFfnbk == true){PEgIOFfnbk = false;}
      if(JLqQaSVSts == true){JLqQaSVSts = false;}
      if(QjFOiWRacW == true){QjFOiWRacW = false;}
      if(kVBMywbMan == true){kVBMywbMan = false;}
      if(lgflEffQaT == true){lgflEffQaT = false;}
      if(xyqSbfySYq == true){xyqSbfySYq = false;}
      if(nFKFAmKdSe == true){nFKFAmKdSe = false;}
      if(pJqFHjDTJD == true){pJqFHjDTJD = false;}
      if(pAAJYlehjR == true){pAAJYlehjR = false;}
      if(xJmjAfWalR == true){xJmjAfWalR = false;}
      if(UByucnGkLr == true){UByucnGkLr = false;}
      if(cdJVAmEBgN == true){cdJVAmEBgN = false;}
      if(HcsAggVHFa == true){HcsAggVHFa = false;}
      if(NchqinCEfk == true){NchqinCEfk = false;}
      if(ftVroTzRiN == true){ftVroTzRiN = false;}
      if(bUtXJrIxNu == true){bUtXJrIxNu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VYXKTWFCKW
{ 
  void JQkfEUJnXu()
  { 
      bool ynEslsYdjV = false;
      bool ttnxqznqQB = false;
      bool afuMkUwOSF = false;
      bool XlnQIrCphP = false;
      bool jsWOFVzqnz = false;
      bool KgZgkRrrIQ = false;
      bool wJLexHGXoy = false;
      bool wyJAQgJfGO = false;
      bool VEaStpLHep = false;
      bool AKhQTZhrQy = false;
      bool PbCoDMXZPE = false;
      bool ILksuqirjG = false;
      bool uyrzylPrgq = false;
      bool zROIzsCkPh = false;
      bool SlragnYnVb = false;
      bool qoHKCQiDpQ = false;
      bool wesXFqwbsB = false;
      bool oxcCnJGRRK = false;
      bool MaVEAJJEGi = false;
      bool KztykmrTUo = false;
      string ctUBfMbctx;
      string CWyGmkpjOm;
      string jTrmejjDCk;
      string pLxGmXiUZm;
      string kqdamqWYLZ;
      string ANBQdIBhVw;
      string bYaIGpZqSO;
      string BVJaCroRzn;
      string MLqbjcKfcd;
      string VBydLMQUTx;
      string ReFxYdEaOk;
      string TjhhiPgyXd;
      string ftOnrAXePo;
      string aUxCWgGtDG;
      string YiQrKkTPuu;
      string fSwpRWQREX;
      string GYKZJymfLB;
      string JltRFwcVcG;
      string gHjTJIXHjz;
      string QnofzzYqhM;
      if(ctUBfMbctx == ReFxYdEaOk){ynEslsYdjV = true;}
      else if(ReFxYdEaOk == ctUBfMbctx){PbCoDMXZPE = true;}
      if(CWyGmkpjOm == TjhhiPgyXd){ttnxqznqQB = true;}
      else if(TjhhiPgyXd == CWyGmkpjOm){ILksuqirjG = true;}
      if(jTrmejjDCk == ftOnrAXePo){afuMkUwOSF = true;}
      else if(ftOnrAXePo == jTrmejjDCk){uyrzylPrgq = true;}
      if(pLxGmXiUZm == aUxCWgGtDG){XlnQIrCphP = true;}
      else if(aUxCWgGtDG == pLxGmXiUZm){zROIzsCkPh = true;}
      if(kqdamqWYLZ == YiQrKkTPuu){jsWOFVzqnz = true;}
      else if(YiQrKkTPuu == kqdamqWYLZ){SlragnYnVb = true;}
      if(ANBQdIBhVw == fSwpRWQREX){KgZgkRrrIQ = true;}
      else if(fSwpRWQREX == ANBQdIBhVw){qoHKCQiDpQ = true;}
      if(bYaIGpZqSO == GYKZJymfLB){wJLexHGXoy = true;}
      else if(GYKZJymfLB == bYaIGpZqSO){wesXFqwbsB = true;}
      if(BVJaCroRzn == JltRFwcVcG){wyJAQgJfGO = true;}
      if(MLqbjcKfcd == gHjTJIXHjz){VEaStpLHep = true;}
      if(VBydLMQUTx == QnofzzYqhM){AKhQTZhrQy = true;}
      while(JltRFwcVcG == BVJaCroRzn){oxcCnJGRRK = true;}
      while(gHjTJIXHjz == gHjTJIXHjz){MaVEAJJEGi = true;}
      while(QnofzzYqhM == QnofzzYqhM){KztykmrTUo = true;}
      if(ynEslsYdjV == true){ynEslsYdjV = false;}
      if(ttnxqznqQB == true){ttnxqznqQB = false;}
      if(afuMkUwOSF == true){afuMkUwOSF = false;}
      if(XlnQIrCphP == true){XlnQIrCphP = false;}
      if(jsWOFVzqnz == true){jsWOFVzqnz = false;}
      if(KgZgkRrrIQ == true){KgZgkRrrIQ = false;}
      if(wJLexHGXoy == true){wJLexHGXoy = false;}
      if(wyJAQgJfGO == true){wyJAQgJfGO = false;}
      if(VEaStpLHep == true){VEaStpLHep = false;}
      if(AKhQTZhrQy == true){AKhQTZhrQy = false;}
      if(PbCoDMXZPE == true){PbCoDMXZPE = false;}
      if(ILksuqirjG == true){ILksuqirjG = false;}
      if(uyrzylPrgq == true){uyrzylPrgq = false;}
      if(zROIzsCkPh == true){zROIzsCkPh = false;}
      if(SlragnYnVb == true){SlragnYnVb = false;}
      if(qoHKCQiDpQ == true){qoHKCQiDpQ = false;}
      if(wesXFqwbsB == true){wesXFqwbsB = false;}
      if(oxcCnJGRRK == true){oxcCnJGRRK = false;}
      if(MaVEAJJEGi == true){MaVEAJJEGi = false;}
      if(KztykmrTUo == true){KztykmrTUo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TBJGYRHCPH
{ 
  void oulmfaUfck()
  { 
      bool ITTthpSjap = false;
      bool OCwLQbiigY = false;
      bool TuhWEbmkIr = false;
      bool dbZPCXSGFb = false;
      bool VCWVtCXjkL = false;
      bool sFbBlMlwoF = false;
      bool DgahMlcgJs = false;
      bool IbcFCRXLbC = false;
      bool ECAxzYAXdo = false;
      bool kWQAXnaoII = false;
      bool YqarCRbWyU = false;
      bool oZTmABgdin = false;
      bool lECTHlKcgO = false;
      bool phCTcNbIug = false;
      bool wdZJzKCdzW = false;
      bool HxGUWUnGjP = false;
      bool HyojdGWAKm = false;
      bool ZYhBqHerUw = false;
      bool jfdJHsbhxI = false;
      bool YUXeZynofs = false;
      string EquxoUlhhA;
      string GRaYwdONQB;
      string JfhZBYAiQf;
      string RZSrIxxlli;
      string fQgLSuZOht;
      string cPXPyXIUwQ;
      string UDRBifzhQz;
      string gcagVrzWHF;
      string zkAVCBCDtj;
      string nbpVOczfcl;
      string wqyhMAopsG;
      string YlNpRiCuyg;
      string dunfLFlFSs;
      string rTsUJHlSIB;
      string MLJnKBNzDe;
      string ZEguIACRVH;
      string OjWANFssfJ;
      string wilwURlAUK;
      string qlBnSnlxLJ;
      string EUwBmbnJaF;
      if(EquxoUlhhA == wqyhMAopsG){ITTthpSjap = true;}
      else if(wqyhMAopsG == EquxoUlhhA){YqarCRbWyU = true;}
      if(GRaYwdONQB == YlNpRiCuyg){OCwLQbiigY = true;}
      else if(YlNpRiCuyg == GRaYwdONQB){oZTmABgdin = true;}
      if(JfhZBYAiQf == dunfLFlFSs){TuhWEbmkIr = true;}
      else if(dunfLFlFSs == JfhZBYAiQf){lECTHlKcgO = true;}
      if(RZSrIxxlli == rTsUJHlSIB){dbZPCXSGFb = true;}
      else if(rTsUJHlSIB == RZSrIxxlli){phCTcNbIug = true;}
      if(fQgLSuZOht == MLJnKBNzDe){VCWVtCXjkL = true;}
      else if(MLJnKBNzDe == fQgLSuZOht){wdZJzKCdzW = true;}
      if(cPXPyXIUwQ == ZEguIACRVH){sFbBlMlwoF = true;}
      else if(ZEguIACRVH == cPXPyXIUwQ){HxGUWUnGjP = true;}
      if(UDRBifzhQz == OjWANFssfJ){DgahMlcgJs = true;}
      else if(OjWANFssfJ == UDRBifzhQz){HyojdGWAKm = true;}
      if(gcagVrzWHF == wilwURlAUK){IbcFCRXLbC = true;}
      if(zkAVCBCDtj == qlBnSnlxLJ){ECAxzYAXdo = true;}
      if(nbpVOczfcl == EUwBmbnJaF){kWQAXnaoII = true;}
      while(wilwURlAUK == gcagVrzWHF){ZYhBqHerUw = true;}
      while(qlBnSnlxLJ == qlBnSnlxLJ){jfdJHsbhxI = true;}
      while(EUwBmbnJaF == EUwBmbnJaF){YUXeZynofs = true;}
      if(ITTthpSjap == true){ITTthpSjap = false;}
      if(OCwLQbiigY == true){OCwLQbiigY = false;}
      if(TuhWEbmkIr == true){TuhWEbmkIr = false;}
      if(dbZPCXSGFb == true){dbZPCXSGFb = false;}
      if(VCWVtCXjkL == true){VCWVtCXjkL = false;}
      if(sFbBlMlwoF == true){sFbBlMlwoF = false;}
      if(DgahMlcgJs == true){DgahMlcgJs = false;}
      if(IbcFCRXLbC == true){IbcFCRXLbC = false;}
      if(ECAxzYAXdo == true){ECAxzYAXdo = false;}
      if(kWQAXnaoII == true){kWQAXnaoII = false;}
      if(YqarCRbWyU == true){YqarCRbWyU = false;}
      if(oZTmABgdin == true){oZTmABgdin = false;}
      if(lECTHlKcgO == true){lECTHlKcgO = false;}
      if(phCTcNbIug == true){phCTcNbIug = false;}
      if(wdZJzKCdzW == true){wdZJzKCdzW = false;}
      if(HxGUWUnGjP == true){HxGUWUnGjP = false;}
      if(HyojdGWAKm == true){HyojdGWAKm = false;}
      if(ZYhBqHerUw == true){ZYhBqHerUw = false;}
      if(jfdJHsbhxI == true){jfdJHsbhxI = false;}
      if(YUXeZynofs == true){YUXeZynofs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XFTLSBBMVV
{ 
  void xapJmdWCnG()
  { 
      bool BgqsQdumwl = false;
      bool MNnXatXFto = false;
      bool UdRstmCncO = false;
      bool EepXjRLgiC = false;
      bool NBVPebAhri = false;
      bool hQFCEXPyyd = false;
      bool bGKhghWQmJ = false;
      bool ipWqaTIBNS = false;
      bool lTwsgnZmTM = false;
      bool CNiEaHqmhw = false;
      bool EjuiAqsObj = false;
      bool PNjerHJQBs = false;
      bool IiwaGUHRPS = false;
      bool bUTQOBYNso = false;
      bool tKLixodDMT = false;
      bool yZlonUnUbe = false;
      bool ibyIItsSQp = false;
      bool iuWLyxXMdR = false;
      bool qEEwUBiecs = false;
      bool NElOGSMDaC = false;
      string fApROYGlwo;
      string qZytDefTkX;
      string iataMsZWVJ;
      string JNwailyDSu;
      string tTOUtcpeMF;
      string FDmZZFGOFV;
      string yiQledcXKR;
      string gcAodOLYfj;
      string CuKQEGZWAd;
      string fixxwKCboQ;
      string zSTuXcCyuK;
      string sgiVTDXAhY;
      string DGXgkyeDrT;
      string LijPjjbPrb;
      string EbbpjzAbcs;
      string lCtQNrtlJY;
      string xyFayKxSkj;
      string bIHGTaegxl;
      string yCazgJoSBr;
      string ooFSdFWAqY;
      if(fApROYGlwo == zSTuXcCyuK){BgqsQdumwl = true;}
      else if(zSTuXcCyuK == fApROYGlwo){EjuiAqsObj = true;}
      if(qZytDefTkX == sgiVTDXAhY){MNnXatXFto = true;}
      else if(sgiVTDXAhY == qZytDefTkX){PNjerHJQBs = true;}
      if(iataMsZWVJ == DGXgkyeDrT){UdRstmCncO = true;}
      else if(DGXgkyeDrT == iataMsZWVJ){IiwaGUHRPS = true;}
      if(JNwailyDSu == LijPjjbPrb){EepXjRLgiC = true;}
      else if(LijPjjbPrb == JNwailyDSu){bUTQOBYNso = true;}
      if(tTOUtcpeMF == EbbpjzAbcs){NBVPebAhri = true;}
      else if(EbbpjzAbcs == tTOUtcpeMF){tKLixodDMT = true;}
      if(FDmZZFGOFV == lCtQNrtlJY){hQFCEXPyyd = true;}
      else if(lCtQNrtlJY == FDmZZFGOFV){yZlonUnUbe = true;}
      if(yiQledcXKR == xyFayKxSkj){bGKhghWQmJ = true;}
      else if(xyFayKxSkj == yiQledcXKR){ibyIItsSQp = true;}
      if(gcAodOLYfj == bIHGTaegxl){ipWqaTIBNS = true;}
      if(CuKQEGZWAd == yCazgJoSBr){lTwsgnZmTM = true;}
      if(fixxwKCboQ == ooFSdFWAqY){CNiEaHqmhw = true;}
      while(bIHGTaegxl == gcAodOLYfj){iuWLyxXMdR = true;}
      while(yCazgJoSBr == yCazgJoSBr){qEEwUBiecs = true;}
      while(ooFSdFWAqY == ooFSdFWAqY){NElOGSMDaC = true;}
      if(BgqsQdumwl == true){BgqsQdumwl = false;}
      if(MNnXatXFto == true){MNnXatXFto = false;}
      if(UdRstmCncO == true){UdRstmCncO = false;}
      if(EepXjRLgiC == true){EepXjRLgiC = false;}
      if(NBVPebAhri == true){NBVPebAhri = false;}
      if(hQFCEXPyyd == true){hQFCEXPyyd = false;}
      if(bGKhghWQmJ == true){bGKhghWQmJ = false;}
      if(ipWqaTIBNS == true){ipWqaTIBNS = false;}
      if(lTwsgnZmTM == true){lTwsgnZmTM = false;}
      if(CNiEaHqmhw == true){CNiEaHqmhw = false;}
      if(EjuiAqsObj == true){EjuiAqsObj = false;}
      if(PNjerHJQBs == true){PNjerHJQBs = false;}
      if(IiwaGUHRPS == true){IiwaGUHRPS = false;}
      if(bUTQOBYNso == true){bUTQOBYNso = false;}
      if(tKLixodDMT == true){tKLixodDMT = false;}
      if(yZlonUnUbe == true){yZlonUnUbe = false;}
      if(ibyIItsSQp == true){ibyIItsSQp = false;}
      if(iuWLyxXMdR == true){iuWLyxXMdR = false;}
      if(qEEwUBiecs == true){qEEwUBiecs = false;}
      if(NElOGSMDaC == true){NElOGSMDaC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UFDJZDTGKL
{ 
  void OgsmjhfaHP()
  { 
      bool JRtoDPHfks = false;
      bool gOYHrNtVuy = false;
      bool IewEUrajen = false;
      bool jAgbuerktO = false;
      bool OpugBPRWCc = false;
      bool drdVxdUoUK = false;
      bool nWBwIghwLN = false;
      bool VJagiSiOCE = false;
      bool aEhCJrVLdR = false;
      bool JCPiZroyYT = false;
      bool hULoHUQxle = false;
      bool tFmPjjoymP = false;
      bool KVStDTsqGq = false;
      bool ckphWFrrun = false;
      bool bXYyWEPzyp = false;
      bool CpLIJLCRln = false;
      bool bYquCJOEse = false;
      bool qwDynlxUXz = false;
      bool EssPnlZhYK = false;
      bool DaGHMDgcwM = false;
      string JKMMKUZdSH;
      string OVMuacmgfJ;
      string nSgfKOOADA;
      string SwTFioLLfa;
      string qcfuokMnXr;
      string slJrnqcfCw;
      string GYaSnRCGMl;
      string RbAFRLllpY;
      string BZcKHflaQq;
      string LeJjTRCNGX;
      string iFblaRlEZc;
      string EqpcugwPLH;
      string faoUZlSPkA;
      string IYeSpuxpjo;
      string tgAnlUofom;
      string VmCyqHQGLo;
      string zVTZTfLXlz;
      string iFfVNyaBhE;
      string wlaydVWgah;
      string epdupYNZTG;
      if(JKMMKUZdSH == iFblaRlEZc){JRtoDPHfks = true;}
      else if(iFblaRlEZc == JKMMKUZdSH){hULoHUQxle = true;}
      if(OVMuacmgfJ == EqpcugwPLH){gOYHrNtVuy = true;}
      else if(EqpcugwPLH == OVMuacmgfJ){tFmPjjoymP = true;}
      if(nSgfKOOADA == faoUZlSPkA){IewEUrajen = true;}
      else if(faoUZlSPkA == nSgfKOOADA){KVStDTsqGq = true;}
      if(SwTFioLLfa == IYeSpuxpjo){jAgbuerktO = true;}
      else if(IYeSpuxpjo == SwTFioLLfa){ckphWFrrun = true;}
      if(qcfuokMnXr == tgAnlUofom){OpugBPRWCc = true;}
      else if(tgAnlUofom == qcfuokMnXr){bXYyWEPzyp = true;}
      if(slJrnqcfCw == VmCyqHQGLo){drdVxdUoUK = true;}
      else if(VmCyqHQGLo == slJrnqcfCw){CpLIJLCRln = true;}
      if(GYaSnRCGMl == zVTZTfLXlz){nWBwIghwLN = true;}
      else if(zVTZTfLXlz == GYaSnRCGMl){bYquCJOEse = true;}
      if(RbAFRLllpY == iFfVNyaBhE){VJagiSiOCE = true;}
      if(BZcKHflaQq == wlaydVWgah){aEhCJrVLdR = true;}
      if(LeJjTRCNGX == epdupYNZTG){JCPiZroyYT = true;}
      while(iFfVNyaBhE == RbAFRLllpY){qwDynlxUXz = true;}
      while(wlaydVWgah == wlaydVWgah){EssPnlZhYK = true;}
      while(epdupYNZTG == epdupYNZTG){DaGHMDgcwM = true;}
      if(JRtoDPHfks == true){JRtoDPHfks = false;}
      if(gOYHrNtVuy == true){gOYHrNtVuy = false;}
      if(IewEUrajen == true){IewEUrajen = false;}
      if(jAgbuerktO == true){jAgbuerktO = false;}
      if(OpugBPRWCc == true){OpugBPRWCc = false;}
      if(drdVxdUoUK == true){drdVxdUoUK = false;}
      if(nWBwIghwLN == true){nWBwIghwLN = false;}
      if(VJagiSiOCE == true){VJagiSiOCE = false;}
      if(aEhCJrVLdR == true){aEhCJrVLdR = false;}
      if(JCPiZroyYT == true){JCPiZroyYT = false;}
      if(hULoHUQxle == true){hULoHUQxle = false;}
      if(tFmPjjoymP == true){tFmPjjoymP = false;}
      if(KVStDTsqGq == true){KVStDTsqGq = false;}
      if(ckphWFrrun == true){ckphWFrrun = false;}
      if(bXYyWEPzyp == true){bXYyWEPzyp = false;}
      if(CpLIJLCRln == true){CpLIJLCRln = false;}
      if(bYquCJOEse == true){bYquCJOEse = false;}
      if(qwDynlxUXz == true){qwDynlxUXz = false;}
      if(EssPnlZhYK == true){EssPnlZhYK = false;}
      if(DaGHMDgcwM == true){DaGHMDgcwM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JIJDSMNZRW
{ 
  void BrizycJsUI()
  { 
      bool gLVORcsoVj = false;
      bool XaouzKVBIe = false;
      bool JcDMsFGfpi = false;
      bool auJXqYglfl = false;
      bool ZgiMBaSotO = false;
      bool omVaRDIIVL = false;
      bool WNzlJbRREZ = false;
      bool djUWFctpLS = false;
      bool mQkatmYhFn = false;
      bool QXPTPMhwDY = false;
      bool IAkUkERyVo = false;
      bool IRxDYFbXrV = false;
      bool DiLQJGTBHs = false;
      bool uylmJlfQpo = false;
      bool UZLQeyZMtJ = false;
      bool jJDhUZnTKd = false;
      bool kQqctJfKsm = false;
      bool YKhDAcXukK = false;
      bool fHGxIktDRj = false;
      bool xMGLEEiiVU = false;
      string qEZVOKZJRx;
      string lNzRfRswSZ;
      string wDqZPYFTwE;
      string GQXnzcJUmw;
      string XjUgYRVMIm;
      string tqzKxmMzFp;
      string EGMMqUpKRD;
      string HXIVBLhKBy;
      string CrKJJPRMpL;
      string QKOxrRXHpD;
      string aKuFfWhcIl;
      string FByHmLwDDa;
      string DdTFlwJLdj;
      string mZTxWrxEcm;
      string gnDEGOMGKf;
      string UTEPAxpoTi;
      string NWzYyehAku;
      string NqZPsPZPzX;
      string jCAyPTVExY;
      string BIktZKneGa;
      if(qEZVOKZJRx == aKuFfWhcIl){gLVORcsoVj = true;}
      else if(aKuFfWhcIl == qEZVOKZJRx){IAkUkERyVo = true;}
      if(lNzRfRswSZ == FByHmLwDDa){XaouzKVBIe = true;}
      else if(FByHmLwDDa == lNzRfRswSZ){IRxDYFbXrV = true;}
      if(wDqZPYFTwE == DdTFlwJLdj){JcDMsFGfpi = true;}
      else if(DdTFlwJLdj == wDqZPYFTwE){DiLQJGTBHs = true;}
      if(GQXnzcJUmw == mZTxWrxEcm){auJXqYglfl = true;}
      else if(mZTxWrxEcm == GQXnzcJUmw){uylmJlfQpo = true;}
      if(XjUgYRVMIm == gnDEGOMGKf){ZgiMBaSotO = true;}
      else if(gnDEGOMGKf == XjUgYRVMIm){UZLQeyZMtJ = true;}
      if(tqzKxmMzFp == UTEPAxpoTi){omVaRDIIVL = true;}
      else if(UTEPAxpoTi == tqzKxmMzFp){jJDhUZnTKd = true;}
      if(EGMMqUpKRD == NWzYyehAku){WNzlJbRREZ = true;}
      else if(NWzYyehAku == EGMMqUpKRD){kQqctJfKsm = true;}
      if(HXIVBLhKBy == NqZPsPZPzX){djUWFctpLS = true;}
      if(CrKJJPRMpL == jCAyPTVExY){mQkatmYhFn = true;}
      if(QKOxrRXHpD == BIktZKneGa){QXPTPMhwDY = true;}
      while(NqZPsPZPzX == HXIVBLhKBy){YKhDAcXukK = true;}
      while(jCAyPTVExY == jCAyPTVExY){fHGxIktDRj = true;}
      while(BIktZKneGa == BIktZKneGa){xMGLEEiiVU = true;}
      if(gLVORcsoVj == true){gLVORcsoVj = false;}
      if(XaouzKVBIe == true){XaouzKVBIe = false;}
      if(JcDMsFGfpi == true){JcDMsFGfpi = false;}
      if(auJXqYglfl == true){auJXqYglfl = false;}
      if(ZgiMBaSotO == true){ZgiMBaSotO = false;}
      if(omVaRDIIVL == true){omVaRDIIVL = false;}
      if(WNzlJbRREZ == true){WNzlJbRREZ = false;}
      if(djUWFctpLS == true){djUWFctpLS = false;}
      if(mQkatmYhFn == true){mQkatmYhFn = false;}
      if(QXPTPMhwDY == true){QXPTPMhwDY = false;}
      if(IAkUkERyVo == true){IAkUkERyVo = false;}
      if(IRxDYFbXrV == true){IRxDYFbXrV = false;}
      if(DiLQJGTBHs == true){DiLQJGTBHs = false;}
      if(uylmJlfQpo == true){uylmJlfQpo = false;}
      if(UZLQeyZMtJ == true){UZLQeyZMtJ = false;}
      if(jJDhUZnTKd == true){jJDhUZnTKd = false;}
      if(kQqctJfKsm == true){kQqctJfKsm = false;}
      if(YKhDAcXukK == true){YKhDAcXukK = false;}
      if(fHGxIktDRj == true){fHGxIktDRj = false;}
      if(xMGLEEiiVU == true){xMGLEEiiVU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JTFJECFHMY
{ 
  void qELkUVOoQh()
  { 
      bool AKhUDSojjN = false;
      bool VBfYXSbWzY = false;
      bool YCeWSsVlrV = false;
      bool xgtiutYrkx = false;
      bool yiSWoKdWGr = false;
      bool ptrbTyfLBK = false;
      bool xCqNQnHwdd = false;
      bool tilBapiHgI = false;
      bool PyezfCnSPw = false;
      bool NMqZAurFGA = false;
      bool DgrbyGHqBc = false;
      bool OXdruyWqgN = false;
      bool AnggQgrMBe = false;
      bool xdBgFhGDBY = false;
      bool txRlhoiyeB = false;
      bool YAXrAOzKLR = false;
      bool OuoWfjWwlM = false;
      bool qTpITCWuza = false;
      bool xsgAGxGJgq = false;
      bool hwqiJyIuGy = false;
      string MqxuSKYGVX;
      string oYlQBDBGzN;
      string BeQjWIEANB;
      string SLPESMSaAe;
      string rZwWzmoSLt;
      string UIanihZNXJ;
      string FXsTEdJgyo;
      string kZFUVaisjj;
      string TlnSfJjaVk;
      string mEDqZTgbSV;
      string dIUWJuDGRH;
      string zfdnpTiZnt;
      string shKNBfVOtB;
      string tGaNGKQRIj;
      string GdIOkGaPAG;
      string kGmXcuyHUd;
      string YoLQMrFPgf;
      string CRRDnOZwbu;
      string FGNnQnSCkK;
      string MJweLRRrBs;
      if(MqxuSKYGVX == dIUWJuDGRH){AKhUDSojjN = true;}
      else if(dIUWJuDGRH == MqxuSKYGVX){DgrbyGHqBc = true;}
      if(oYlQBDBGzN == zfdnpTiZnt){VBfYXSbWzY = true;}
      else if(zfdnpTiZnt == oYlQBDBGzN){OXdruyWqgN = true;}
      if(BeQjWIEANB == shKNBfVOtB){YCeWSsVlrV = true;}
      else if(shKNBfVOtB == BeQjWIEANB){AnggQgrMBe = true;}
      if(SLPESMSaAe == tGaNGKQRIj){xgtiutYrkx = true;}
      else if(tGaNGKQRIj == SLPESMSaAe){xdBgFhGDBY = true;}
      if(rZwWzmoSLt == GdIOkGaPAG){yiSWoKdWGr = true;}
      else if(GdIOkGaPAG == rZwWzmoSLt){txRlhoiyeB = true;}
      if(UIanihZNXJ == kGmXcuyHUd){ptrbTyfLBK = true;}
      else if(kGmXcuyHUd == UIanihZNXJ){YAXrAOzKLR = true;}
      if(FXsTEdJgyo == YoLQMrFPgf){xCqNQnHwdd = true;}
      else if(YoLQMrFPgf == FXsTEdJgyo){OuoWfjWwlM = true;}
      if(kZFUVaisjj == CRRDnOZwbu){tilBapiHgI = true;}
      if(TlnSfJjaVk == FGNnQnSCkK){PyezfCnSPw = true;}
      if(mEDqZTgbSV == MJweLRRrBs){NMqZAurFGA = true;}
      while(CRRDnOZwbu == kZFUVaisjj){qTpITCWuza = true;}
      while(FGNnQnSCkK == FGNnQnSCkK){xsgAGxGJgq = true;}
      while(MJweLRRrBs == MJweLRRrBs){hwqiJyIuGy = true;}
      if(AKhUDSojjN == true){AKhUDSojjN = false;}
      if(VBfYXSbWzY == true){VBfYXSbWzY = false;}
      if(YCeWSsVlrV == true){YCeWSsVlrV = false;}
      if(xgtiutYrkx == true){xgtiutYrkx = false;}
      if(yiSWoKdWGr == true){yiSWoKdWGr = false;}
      if(ptrbTyfLBK == true){ptrbTyfLBK = false;}
      if(xCqNQnHwdd == true){xCqNQnHwdd = false;}
      if(tilBapiHgI == true){tilBapiHgI = false;}
      if(PyezfCnSPw == true){PyezfCnSPw = false;}
      if(NMqZAurFGA == true){NMqZAurFGA = false;}
      if(DgrbyGHqBc == true){DgrbyGHqBc = false;}
      if(OXdruyWqgN == true){OXdruyWqgN = false;}
      if(AnggQgrMBe == true){AnggQgrMBe = false;}
      if(xdBgFhGDBY == true){xdBgFhGDBY = false;}
      if(txRlhoiyeB == true){txRlhoiyeB = false;}
      if(YAXrAOzKLR == true){YAXrAOzKLR = false;}
      if(OuoWfjWwlM == true){OuoWfjWwlM = false;}
      if(qTpITCWuza == true){qTpITCWuza = false;}
      if(xsgAGxGJgq == true){xsgAGxGJgq = false;}
      if(hwqiJyIuGy == true){hwqiJyIuGy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NAPFRHPNQF
{ 
  void GEQCguaiJk()
  { 
      bool cChBGIohFS = false;
      bool CLaLOTAULg = false;
      bool ATZsykBBwp = false;
      bool eYfpMJPhMP = false;
      bool cAyQmRIqoC = false;
      bool eQpdeIcoCU = false;
      bool GmkOncekzF = false;
      bool ERHuEzUJFf = false;
      bool cKLtLNiBLD = false;
      bool gaeqJoPjcK = false;
      bool lWrjxMItZe = false;
      bool mSjWrwaqDZ = false;
      bool tdYuXcmPlO = false;
      bool ikgusFRbwy = false;
      bool EnbfQNpIzM = false;
      bool NYfCPIywLT = false;
      bool ZrIKwClocm = false;
      bool dztEUFBseJ = false;
      bool mdQYBKEdek = false;
      bool GVPbYMfQjO = false;
      string dnIgtMlZIA;
      string NPrApoJXBn;
      string xWueWEDfEh;
      string FLrXlwWcZh;
      string cDgFfNWskU;
      string MtBhEGrdKo;
      string IFVauCWTOt;
      string SgxSKsooyI;
      string hJuiUKJJTe;
      string DrRkYXgGKd;
      string pCeqCfwhXK;
      string RCeBHzJlGj;
      string rMAipZOMsm;
      string MieUSeeEgn;
      string OalJNANQcZ;
      string NtAakcCwAb;
      string RiojyiXKhb;
      string TFFSVRaqUo;
      string MxiTYRhEjo;
      string ciDEVelBKe;
      if(dnIgtMlZIA == pCeqCfwhXK){cChBGIohFS = true;}
      else if(pCeqCfwhXK == dnIgtMlZIA){lWrjxMItZe = true;}
      if(NPrApoJXBn == RCeBHzJlGj){CLaLOTAULg = true;}
      else if(RCeBHzJlGj == NPrApoJXBn){mSjWrwaqDZ = true;}
      if(xWueWEDfEh == rMAipZOMsm){ATZsykBBwp = true;}
      else if(rMAipZOMsm == xWueWEDfEh){tdYuXcmPlO = true;}
      if(FLrXlwWcZh == MieUSeeEgn){eYfpMJPhMP = true;}
      else if(MieUSeeEgn == FLrXlwWcZh){ikgusFRbwy = true;}
      if(cDgFfNWskU == OalJNANQcZ){cAyQmRIqoC = true;}
      else if(OalJNANQcZ == cDgFfNWskU){EnbfQNpIzM = true;}
      if(MtBhEGrdKo == NtAakcCwAb){eQpdeIcoCU = true;}
      else if(NtAakcCwAb == MtBhEGrdKo){NYfCPIywLT = true;}
      if(IFVauCWTOt == RiojyiXKhb){GmkOncekzF = true;}
      else if(RiojyiXKhb == IFVauCWTOt){ZrIKwClocm = true;}
      if(SgxSKsooyI == TFFSVRaqUo){ERHuEzUJFf = true;}
      if(hJuiUKJJTe == MxiTYRhEjo){cKLtLNiBLD = true;}
      if(DrRkYXgGKd == ciDEVelBKe){gaeqJoPjcK = true;}
      while(TFFSVRaqUo == SgxSKsooyI){dztEUFBseJ = true;}
      while(MxiTYRhEjo == MxiTYRhEjo){mdQYBKEdek = true;}
      while(ciDEVelBKe == ciDEVelBKe){GVPbYMfQjO = true;}
      if(cChBGIohFS == true){cChBGIohFS = false;}
      if(CLaLOTAULg == true){CLaLOTAULg = false;}
      if(ATZsykBBwp == true){ATZsykBBwp = false;}
      if(eYfpMJPhMP == true){eYfpMJPhMP = false;}
      if(cAyQmRIqoC == true){cAyQmRIqoC = false;}
      if(eQpdeIcoCU == true){eQpdeIcoCU = false;}
      if(GmkOncekzF == true){GmkOncekzF = false;}
      if(ERHuEzUJFf == true){ERHuEzUJFf = false;}
      if(cKLtLNiBLD == true){cKLtLNiBLD = false;}
      if(gaeqJoPjcK == true){gaeqJoPjcK = false;}
      if(lWrjxMItZe == true){lWrjxMItZe = false;}
      if(mSjWrwaqDZ == true){mSjWrwaqDZ = false;}
      if(tdYuXcmPlO == true){tdYuXcmPlO = false;}
      if(ikgusFRbwy == true){ikgusFRbwy = false;}
      if(EnbfQNpIzM == true){EnbfQNpIzM = false;}
      if(NYfCPIywLT == true){NYfCPIywLT = false;}
      if(ZrIKwClocm == true){ZrIKwClocm = false;}
      if(dztEUFBseJ == true){dztEUFBseJ = false;}
      if(mdQYBKEdek == true){mdQYBKEdek = false;}
      if(GVPbYMfQjO == true){GVPbYMfQjO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUTRNJTDYN
{ 
  void QXdDteMJHT()
  { 
      bool xKfxZlAllX = false;
      bool arOVZxNIqB = false;
      bool tiHLCnbCAI = false;
      bool rUlkCxkdxw = false;
      bool tTrggSlkeV = false;
      bool owxMDNDTtl = false;
      bool JxkceGGcSc = false;
      bool LjKtHZqadj = false;
      bool BqXdSwWYho = false;
      bool tQjKmwhOCZ = false;
      bool MISCJFkDFc = false;
      bool VbpKjSYHKh = false;
      bool igudhuAzGK = false;
      bool rbXDXrXVTM = false;
      bool LSSESRaYaU = false;
      bool WaETqeNoTO = false;
      bool FkwuktElmr = false;
      bool tDmxWPNpKP = false;
      bool TaYlmQXEMr = false;
      bool eiBFGZWXTY = false;
      string MZWkIFcwbo;
      string mfbXfDsbzy;
      string GkFLZerDzO;
      string PEOKjUSUIN;
      string JATbjZVQry;
      string DtDUDbTLKc;
      string MYwMYhRRnL;
      string kYSloFRdaA;
      string JaKALUBsGH;
      string AGJfAjDGCB;
      string IEcgMdbQex;
      string KokKTlNuBE;
      string gXKfKdPmkF;
      string CKbYrFxdnh;
      string rjOJxKVyLO;
      string VHFxUjsxVh;
      string OofZuzNLSO;
      string njHTLxJAiA;
      string IQaWitFdEH;
      string LAHFTDEoOx;
      if(MZWkIFcwbo == IEcgMdbQex){xKfxZlAllX = true;}
      else if(IEcgMdbQex == MZWkIFcwbo){MISCJFkDFc = true;}
      if(mfbXfDsbzy == KokKTlNuBE){arOVZxNIqB = true;}
      else if(KokKTlNuBE == mfbXfDsbzy){VbpKjSYHKh = true;}
      if(GkFLZerDzO == gXKfKdPmkF){tiHLCnbCAI = true;}
      else if(gXKfKdPmkF == GkFLZerDzO){igudhuAzGK = true;}
      if(PEOKjUSUIN == CKbYrFxdnh){rUlkCxkdxw = true;}
      else if(CKbYrFxdnh == PEOKjUSUIN){rbXDXrXVTM = true;}
      if(JATbjZVQry == rjOJxKVyLO){tTrggSlkeV = true;}
      else if(rjOJxKVyLO == JATbjZVQry){LSSESRaYaU = true;}
      if(DtDUDbTLKc == VHFxUjsxVh){owxMDNDTtl = true;}
      else if(VHFxUjsxVh == DtDUDbTLKc){WaETqeNoTO = true;}
      if(MYwMYhRRnL == OofZuzNLSO){JxkceGGcSc = true;}
      else if(OofZuzNLSO == MYwMYhRRnL){FkwuktElmr = true;}
      if(kYSloFRdaA == njHTLxJAiA){LjKtHZqadj = true;}
      if(JaKALUBsGH == IQaWitFdEH){BqXdSwWYho = true;}
      if(AGJfAjDGCB == LAHFTDEoOx){tQjKmwhOCZ = true;}
      while(njHTLxJAiA == kYSloFRdaA){tDmxWPNpKP = true;}
      while(IQaWitFdEH == IQaWitFdEH){TaYlmQXEMr = true;}
      while(LAHFTDEoOx == LAHFTDEoOx){eiBFGZWXTY = true;}
      if(xKfxZlAllX == true){xKfxZlAllX = false;}
      if(arOVZxNIqB == true){arOVZxNIqB = false;}
      if(tiHLCnbCAI == true){tiHLCnbCAI = false;}
      if(rUlkCxkdxw == true){rUlkCxkdxw = false;}
      if(tTrggSlkeV == true){tTrggSlkeV = false;}
      if(owxMDNDTtl == true){owxMDNDTtl = false;}
      if(JxkceGGcSc == true){JxkceGGcSc = false;}
      if(LjKtHZqadj == true){LjKtHZqadj = false;}
      if(BqXdSwWYho == true){BqXdSwWYho = false;}
      if(tQjKmwhOCZ == true){tQjKmwhOCZ = false;}
      if(MISCJFkDFc == true){MISCJFkDFc = false;}
      if(VbpKjSYHKh == true){VbpKjSYHKh = false;}
      if(igudhuAzGK == true){igudhuAzGK = false;}
      if(rbXDXrXVTM == true){rbXDXrXVTM = false;}
      if(LSSESRaYaU == true){LSSESRaYaU = false;}
      if(WaETqeNoTO == true){WaETqeNoTO = false;}
      if(FkwuktElmr == true){FkwuktElmr = false;}
      if(tDmxWPNpKP == true){tDmxWPNpKP = false;}
      if(TaYlmQXEMr == true){TaYlmQXEMr = false;}
      if(eiBFGZWXTY == true){eiBFGZWXTY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class POKWBPQSIY
{ 
  void YUlACbTPBY()
  { 
      bool TsmghrOmAq = false;
      bool uALrcFkJfJ = false;
      bool edYqVWHmOG = false;
      bool WRVggMCcIa = false;
      bool AcTQJqTZeG = false;
      bool gpIacpTwLL = false;
      bool jaXtTdddKQ = false;
      bool CHBEJBJHgd = false;
      bool CgHIYgJuEq = false;
      bool rGRwqYFZxf = false;
      bool MoOODYnDRa = false;
      bool fLOgIDTOUl = false;
      bool UiYTXwpENj = false;
      bool wjKBRNRrFA = false;
      bool rFddKfqjnn = false;
      bool FpEKLdPuqH = false;
      bool hjpgeuBNPu = false;
      bool kaJTtOEuIq = false;
      bool EGPZeFezpn = false;
      bool xWBxRIPxzP = false;
      string aFBoHzdWRY;
      string kWDAjBQHOH;
      string MbKobVqRdJ;
      string aoBecFpBtX;
      string QoCHgUxRrY;
      string iNPaVzuLMk;
      string HMrHxwVYWd;
      string KONppWYDHH;
      string XZZFaMYZId;
      string KeoIQExuJk;
      string yXtNOTAYky;
      string ZrEFNglmgk;
      string WuQsTfZFZk;
      string ZdsWIzfMqG;
      string MznJDSZjui;
      string RKNYOCHAsh;
      string tuzzYuygwN;
      string BZuaXWGGoB;
      string FoJpSOQUIF;
      string reSILRzojH;
      if(aFBoHzdWRY == yXtNOTAYky){TsmghrOmAq = true;}
      else if(yXtNOTAYky == aFBoHzdWRY){MoOODYnDRa = true;}
      if(kWDAjBQHOH == ZrEFNglmgk){uALrcFkJfJ = true;}
      else if(ZrEFNglmgk == kWDAjBQHOH){fLOgIDTOUl = true;}
      if(MbKobVqRdJ == WuQsTfZFZk){edYqVWHmOG = true;}
      else if(WuQsTfZFZk == MbKobVqRdJ){UiYTXwpENj = true;}
      if(aoBecFpBtX == ZdsWIzfMqG){WRVggMCcIa = true;}
      else if(ZdsWIzfMqG == aoBecFpBtX){wjKBRNRrFA = true;}
      if(QoCHgUxRrY == MznJDSZjui){AcTQJqTZeG = true;}
      else if(MznJDSZjui == QoCHgUxRrY){rFddKfqjnn = true;}
      if(iNPaVzuLMk == RKNYOCHAsh){gpIacpTwLL = true;}
      else if(RKNYOCHAsh == iNPaVzuLMk){FpEKLdPuqH = true;}
      if(HMrHxwVYWd == tuzzYuygwN){jaXtTdddKQ = true;}
      else if(tuzzYuygwN == HMrHxwVYWd){hjpgeuBNPu = true;}
      if(KONppWYDHH == BZuaXWGGoB){CHBEJBJHgd = true;}
      if(XZZFaMYZId == FoJpSOQUIF){CgHIYgJuEq = true;}
      if(KeoIQExuJk == reSILRzojH){rGRwqYFZxf = true;}
      while(BZuaXWGGoB == KONppWYDHH){kaJTtOEuIq = true;}
      while(FoJpSOQUIF == FoJpSOQUIF){EGPZeFezpn = true;}
      while(reSILRzojH == reSILRzojH){xWBxRIPxzP = true;}
      if(TsmghrOmAq == true){TsmghrOmAq = false;}
      if(uALrcFkJfJ == true){uALrcFkJfJ = false;}
      if(edYqVWHmOG == true){edYqVWHmOG = false;}
      if(WRVggMCcIa == true){WRVggMCcIa = false;}
      if(AcTQJqTZeG == true){AcTQJqTZeG = false;}
      if(gpIacpTwLL == true){gpIacpTwLL = false;}
      if(jaXtTdddKQ == true){jaXtTdddKQ = false;}
      if(CHBEJBJHgd == true){CHBEJBJHgd = false;}
      if(CgHIYgJuEq == true){CgHIYgJuEq = false;}
      if(rGRwqYFZxf == true){rGRwqYFZxf = false;}
      if(MoOODYnDRa == true){MoOODYnDRa = false;}
      if(fLOgIDTOUl == true){fLOgIDTOUl = false;}
      if(UiYTXwpENj == true){UiYTXwpENj = false;}
      if(wjKBRNRrFA == true){wjKBRNRrFA = false;}
      if(rFddKfqjnn == true){rFddKfqjnn = false;}
      if(FpEKLdPuqH == true){FpEKLdPuqH = false;}
      if(hjpgeuBNPu == true){hjpgeuBNPu = false;}
      if(kaJTtOEuIq == true){kaJTtOEuIq = false;}
      if(EGPZeFezpn == true){EGPZeFezpn = false;}
      if(xWBxRIPxzP == true){xWBxRIPxzP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBXBEQYJJU
{ 
  void aXpgZKQxwu()
  { 
      bool xgcNRxjZil = false;
      bool QILnLiQfiP = false;
      bool MWwyRGptRJ = false;
      bool bCALmaTjWx = false;
      bool dGVxjoojzM = false;
      bool JxlgbakdwK = false;
      bool HoIYJOIABj = false;
      bool PgIllGBzOb = false;
      bool RFuEzePTjL = false;
      bool ppnMpoxwmV = false;
      bool goiPxcoAuU = false;
      bool ZlPTsBtEZe = false;
      bool yoPosYswww = false;
      bool JELrucWeGW = false;
      bool oOXOlEaTTn = false;
      bool usWIXrYtVX = false;
      bool jsEyLUZWYP = false;
      bool dOxCoiQBDo = false;
      bool yYbHBPhCTD = false;
      bool EcIhmwKZDQ = false;
      string IfhHxNmBEx;
      string RCwhTgDZju;
      string HzQGQsiuwf;
      string rdxREmtKBZ;
      string QeCziPJYOb;
      string yNuOJJPbqD;
      string erEXFmFedg;
      string mrXKecxQWA;
      string iJfTheiiHt;
      string WRSxuXZdsw;
      string KduhoFojjg;
      string MyFpUVLjpZ;
      string EWXiJUZaOG;
      string DTXZpENxeb;
      string oyyahYMccZ;
      string LomSqnGMYT;
      string fOUcdsaeAP;
      string HOFNjFXxAk;
      string IwxotNfEiB;
      string yAYKwacUwo;
      if(IfhHxNmBEx == KduhoFojjg){xgcNRxjZil = true;}
      else if(KduhoFojjg == IfhHxNmBEx){goiPxcoAuU = true;}
      if(RCwhTgDZju == MyFpUVLjpZ){QILnLiQfiP = true;}
      else if(MyFpUVLjpZ == RCwhTgDZju){ZlPTsBtEZe = true;}
      if(HzQGQsiuwf == EWXiJUZaOG){MWwyRGptRJ = true;}
      else if(EWXiJUZaOG == HzQGQsiuwf){yoPosYswww = true;}
      if(rdxREmtKBZ == DTXZpENxeb){bCALmaTjWx = true;}
      else if(DTXZpENxeb == rdxREmtKBZ){JELrucWeGW = true;}
      if(QeCziPJYOb == oyyahYMccZ){dGVxjoojzM = true;}
      else if(oyyahYMccZ == QeCziPJYOb){oOXOlEaTTn = true;}
      if(yNuOJJPbqD == LomSqnGMYT){JxlgbakdwK = true;}
      else if(LomSqnGMYT == yNuOJJPbqD){usWIXrYtVX = true;}
      if(erEXFmFedg == fOUcdsaeAP){HoIYJOIABj = true;}
      else if(fOUcdsaeAP == erEXFmFedg){jsEyLUZWYP = true;}
      if(mrXKecxQWA == HOFNjFXxAk){PgIllGBzOb = true;}
      if(iJfTheiiHt == IwxotNfEiB){RFuEzePTjL = true;}
      if(WRSxuXZdsw == yAYKwacUwo){ppnMpoxwmV = true;}
      while(HOFNjFXxAk == mrXKecxQWA){dOxCoiQBDo = true;}
      while(IwxotNfEiB == IwxotNfEiB){yYbHBPhCTD = true;}
      while(yAYKwacUwo == yAYKwacUwo){EcIhmwKZDQ = true;}
      if(xgcNRxjZil == true){xgcNRxjZil = false;}
      if(QILnLiQfiP == true){QILnLiQfiP = false;}
      if(MWwyRGptRJ == true){MWwyRGptRJ = false;}
      if(bCALmaTjWx == true){bCALmaTjWx = false;}
      if(dGVxjoojzM == true){dGVxjoojzM = false;}
      if(JxlgbakdwK == true){JxlgbakdwK = false;}
      if(HoIYJOIABj == true){HoIYJOIABj = false;}
      if(PgIllGBzOb == true){PgIllGBzOb = false;}
      if(RFuEzePTjL == true){RFuEzePTjL = false;}
      if(ppnMpoxwmV == true){ppnMpoxwmV = false;}
      if(goiPxcoAuU == true){goiPxcoAuU = false;}
      if(ZlPTsBtEZe == true){ZlPTsBtEZe = false;}
      if(yoPosYswww == true){yoPosYswww = false;}
      if(JELrucWeGW == true){JELrucWeGW = false;}
      if(oOXOlEaTTn == true){oOXOlEaTTn = false;}
      if(usWIXrYtVX == true){usWIXrYtVX = false;}
      if(jsEyLUZWYP == true){jsEyLUZWYP = false;}
      if(dOxCoiQBDo == true){dOxCoiQBDo = false;}
      if(yYbHBPhCTD == true){yYbHBPhCTD = false;}
      if(EcIhmwKZDQ == true){EcIhmwKZDQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CCENQEAWQT
{ 
  void JDixLbWSyB()
  { 
      bool FbyLPMuBgm = false;
      bool JgdtXhGmUy = false;
      bool xuYTbWwMxd = false;
      bool WiGyAGhfTF = false;
      bool yaCUSFcPka = false;
      bool btfKnKCdjr = false;
      bool QiEDPZZetR = false;
      bool zZSPzWrDAV = false;
      bool tgaWBcDwKo = false;
      bool DEwboPVyFs = false;
      bool fyUTaBaPKQ = false;
      bool RycNyiHhCm = false;
      bool WdTENudqaj = false;
      bool BtyHpwLHuz = false;
      bool BmltWEahdF = false;
      bool ImwSWBdQFf = false;
      bool XjoZPXAVXB = false;
      bool XzmCkirZgI = false;
      bool TwMVbNxfkn = false;
      bool StBObQyLdz = false;
      string UgyuLhuDiE;
      string tgnQIFNErQ;
      string YqERnVFdzt;
      string IdyVzWWWNV;
      string zIXjQzcach;
      string gIXnSccgHp;
      string cQEouPhRRk;
      string hqpWRPSTAn;
      string rdBQMAGKDV;
      string tpOXrhEioB;
      string RKJqzpRBWC;
      string JJfTxyPmbu;
      string JXOuqrbSdj;
      string KjdzWhUJQW;
      string hEmALkJuat;
      string RRHtqsuNAH;
      string OzWmqZegxO;
      string dFVFMEjOjG;
      string igrjRsbjHc;
      string mGJJIigAIk;
      if(UgyuLhuDiE == RKJqzpRBWC){FbyLPMuBgm = true;}
      else if(RKJqzpRBWC == UgyuLhuDiE){fyUTaBaPKQ = true;}
      if(tgnQIFNErQ == JJfTxyPmbu){JgdtXhGmUy = true;}
      else if(JJfTxyPmbu == tgnQIFNErQ){RycNyiHhCm = true;}
      if(YqERnVFdzt == JXOuqrbSdj){xuYTbWwMxd = true;}
      else if(JXOuqrbSdj == YqERnVFdzt){WdTENudqaj = true;}
      if(IdyVzWWWNV == KjdzWhUJQW){WiGyAGhfTF = true;}
      else if(KjdzWhUJQW == IdyVzWWWNV){BtyHpwLHuz = true;}
      if(zIXjQzcach == hEmALkJuat){yaCUSFcPka = true;}
      else if(hEmALkJuat == zIXjQzcach){BmltWEahdF = true;}
      if(gIXnSccgHp == RRHtqsuNAH){btfKnKCdjr = true;}
      else if(RRHtqsuNAH == gIXnSccgHp){ImwSWBdQFf = true;}
      if(cQEouPhRRk == OzWmqZegxO){QiEDPZZetR = true;}
      else if(OzWmqZegxO == cQEouPhRRk){XjoZPXAVXB = true;}
      if(hqpWRPSTAn == dFVFMEjOjG){zZSPzWrDAV = true;}
      if(rdBQMAGKDV == igrjRsbjHc){tgaWBcDwKo = true;}
      if(tpOXrhEioB == mGJJIigAIk){DEwboPVyFs = true;}
      while(dFVFMEjOjG == hqpWRPSTAn){XzmCkirZgI = true;}
      while(igrjRsbjHc == igrjRsbjHc){TwMVbNxfkn = true;}
      while(mGJJIigAIk == mGJJIigAIk){StBObQyLdz = true;}
      if(FbyLPMuBgm == true){FbyLPMuBgm = false;}
      if(JgdtXhGmUy == true){JgdtXhGmUy = false;}
      if(xuYTbWwMxd == true){xuYTbWwMxd = false;}
      if(WiGyAGhfTF == true){WiGyAGhfTF = false;}
      if(yaCUSFcPka == true){yaCUSFcPka = false;}
      if(btfKnKCdjr == true){btfKnKCdjr = false;}
      if(QiEDPZZetR == true){QiEDPZZetR = false;}
      if(zZSPzWrDAV == true){zZSPzWrDAV = false;}
      if(tgaWBcDwKo == true){tgaWBcDwKo = false;}
      if(DEwboPVyFs == true){DEwboPVyFs = false;}
      if(fyUTaBaPKQ == true){fyUTaBaPKQ = false;}
      if(RycNyiHhCm == true){RycNyiHhCm = false;}
      if(WdTENudqaj == true){WdTENudqaj = false;}
      if(BtyHpwLHuz == true){BtyHpwLHuz = false;}
      if(BmltWEahdF == true){BmltWEahdF = false;}
      if(ImwSWBdQFf == true){ImwSWBdQFf = false;}
      if(XjoZPXAVXB == true){XjoZPXAVXB = false;}
      if(XzmCkirZgI == true){XzmCkirZgI = false;}
      if(TwMVbNxfkn == true){TwMVbNxfkn = false;}
      if(StBObQyLdz == true){StBObQyLdz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EAZIONFZNS
{ 
  void DwoZZrTNKT()
  { 
      bool bWTOiVIYML = false;
      bool FxPpYQKFCd = false;
      bool rXAcVFyLnM = false;
      bool aqYnEsnGIh = false;
      bool ApPaDQlqye = false;
      bool CdEXgDWprd = false;
      bool XxjzkNYble = false;
      bool cDwTdBIYZE = false;
      bool SGMJKwlAGB = false;
      bool VxNeKDGPpo = false;
      bool rKFTCyhkse = false;
      bool uyQmKQjaoo = false;
      bool bXUkIepQIa = false;
      bool urhjMHArGM = false;
      bool NAGaFXgZTs = false;
      bool SeaBMTpUKX = false;
      bool IQcSjCPfaC = false;
      bool QrTcaaQsej = false;
      bool xPwOHPQgWs = false;
      bool RfhiExXnqC = false;
      string dTDGBiluOh;
      string JWupeEsxmE;
      string wKilfGoPXF;
      string YGiCgdXcMY;
      string JJXNQDgifw;
      string AhsHZSkRZt;
      string tVWJIDmrJB;
      string fPjNtlmUVb;
      string ZFjbEpMacN;
      string rFCRenlNFM;
      string PnZePkxfMm;
      string fPwxUnluES;
      string qMPuIZMShG;
      string zYPIMkfFMT;
      string rgNogbJExp;
      string CqJmVDXdWo;
      string XexGmHAmki;
      string HfijZJyaNf;
      string PHUrEIPcmI;
      string NChXwMiHCZ;
      if(dTDGBiluOh == PnZePkxfMm){bWTOiVIYML = true;}
      else if(PnZePkxfMm == dTDGBiluOh){rKFTCyhkse = true;}
      if(JWupeEsxmE == fPwxUnluES){FxPpYQKFCd = true;}
      else if(fPwxUnluES == JWupeEsxmE){uyQmKQjaoo = true;}
      if(wKilfGoPXF == qMPuIZMShG){rXAcVFyLnM = true;}
      else if(qMPuIZMShG == wKilfGoPXF){bXUkIepQIa = true;}
      if(YGiCgdXcMY == zYPIMkfFMT){aqYnEsnGIh = true;}
      else if(zYPIMkfFMT == YGiCgdXcMY){urhjMHArGM = true;}
      if(JJXNQDgifw == rgNogbJExp){ApPaDQlqye = true;}
      else if(rgNogbJExp == JJXNQDgifw){NAGaFXgZTs = true;}
      if(AhsHZSkRZt == CqJmVDXdWo){CdEXgDWprd = true;}
      else if(CqJmVDXdWo == AhsHZSkRZt){SeaBMTpUKX = true;}
      if(tVWJIDmrJB == XexGmHAmki){XxjzkNYble = true;}
      else if(XexGmHAmki == tVWJIDmrJB){IQcSjCPfaC = true;}
      if(fPjNtlmUVb == HfijZJyaNf){cDwTdBIYZE = true;}
      if(ZFjbEpMacN == PHUrEIPcmI){SGMJKwlAGB = true;}
      if(rFCRenlNFM == NChXwMiHCZ){VxNeKDGPpo = true;}
      while(HfijZJyaNf == fPjNtlmUVb){QrTcaaQsej = true;}
      while(PHUrEIPcmI == PHUrEIPcmI){xPwOHPQgWs = true;}
      while(NChXwMiHCZ == NChXwMiHCZ){RfhiExXnqC = true;}
      if(bWTOiVIYML == true){bWTOiVIYML = false;}
      if(FxPpYQKFCd == true){FxPpYQKFCd = false;}
      if(rXAcVFyLnM == true){rXAcVFyLnM = false;}
      if(aqYnEsnGIh == true){aqYnEsnGIh = false;}
      if(ApPaDQlqye == true){ApPaDQlqye = false;}
      if(CdEXgDWprd == true){CdEXgDWprd = false;}
      if(XxjzkNYble == true){XxjzkNYble = false;}
      if(cDwTdBIYZE == true){cDwTdBIYZE = false;}
      if(SGMJKwlAGB == true){SGMJKwlAGB = false;}
      if(VxNeKDGPpo == true){VxNeKDGPpo = false;}
      if(rKFTCyhkse == true){rKFTCyhkse = false;}
      if(uyQmKQjaoo == true){uyQmKQjaoo = false;}
      if(bXUkIepQIa == true){bXUkIepQIa = false;}
      if(urhjMHArGM == true){urhjMHArGM = false;}
      if(NAGaFXgZTs == true){NAGaFXgZTs = false;}
      if(SeaBMTpUKX == true){SeaBMTpUKX = false;}
      if(IQcSjCPfaC == true){IQcSjCPfaC = false;}
      if(QrTcaaQsej == true){QrTcaaQsej = false;}
      if(xPwOHPQgWs == true){xPwOHPQgWs = false;}
      if(RfhiExXnqC == true){RfhiExXnqC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XJFSRCBPCZ
{ 
  void KPAGejHfaq()
  { 
      bool EVCALSWuOn = false;
      bool wzngzLEzup = false;
      bool BMUXCamGJO = false;
      bool RMbpCpcljK = false;
      bool VXTSTCrHLG = false;
      bool ZEwsurAdyj = false;
      bool eQkzVjWydI = false;
      bool hSPkUcrBEz = false;
      bool ieuDnMPhtK = false;
      bool pzmzeEmTxi = false;
      bool etcCXHoLYS = false;
      bool zzZyBzVhKI = false;
      bool UoDTSifPFP = false;
      bool pXEUUnCreg = false;
      bool XEJbKpYoyf = false;
      bool hEJoOpqJio = false;
      bool bYFIbauFdM = false;
      bool xcCdjPeaIb = false;
      bool JqRZhkOOFd = false;
      bool xrJpFyyBzj = false;
      string gPyosDYrOf;
      string xKiXYcMPlr;
      string VTOIsSAALE;
      string IRcPpjesym;
      string WKSxLELMfS;
      string gBIQdMBpuZ;
      string DXgJXegShn;
      string yTQyVLAQxo;
      string GmTrXGJMld;
      string ioxYjycJZf;
      string WrerUNjJuR;
      string LkrGSPDnlQ;
      string VUgEEIVrOW;
      string hqpQRNHbWJ;
      string WzQTRywpFT;
      string toXIKBLamL;
      string qqtXjUtanE;
      string HbRbtWEMmG;
      string MemucsThGQ;
      string CgnKReErjw;
      if(gPyosDYrOf == WrerUNjJuR){EVCALSWuOn = true;}
      else if(WrerUNjJuR == gPyosDYrOf){etcCXHoLYS = true;}
      if(xKiXYcMPlr == LkrGSPDnlQ){wzngzLEzup = true;}
      else if(LkrGSPDnlQ == xKiXYcMPlr){zzZyBzVhKI = true;}
      if(VTOIsSAALE == VUgEEIVrOW){BMUXCamGJO = true;}
      else if(VUgEEIVrOW == VTOIsSAALE){UoDTSifPFP = true;}
      if(IRcPpjesym == hqpQRNHbWJ){RMbpCpcljK = true;}
      else if(hqpQRNHbWJ == IRcPpjesym){pXEUUnCreg = true;}
      if(WKSxLELMfS == WzQTRywpFT){VXTSTCrHLG = true;}
      else if(WzQTRywpFT == WKSxLELMfS){XEJbKpYoyf = true;}
      if(gBIQdMBpuZ == toXIKBLamL){ZEwsurAdyj = true;}
      else if(toXIKBLamL == gBIQdMBpuZ){hEJoOpqJio = true;}
      if(DXgJXegShn == qqtXjUtanE){eQkzVjWydI = true;}
      else if(qqtXjUtanE == DXgJXegShn){bYFIbauFdM = true;}
      if(yTQyVLAQxo == HbRbtWEMmG){hSPkUcrBEz = true;}
      if(GmTrXGJMld == MemucsThGQ){ieuDnMPhtK = true;}
      if(ioxYjycJZf == CgnKReErjw){pzmzeEmTxi = true;}
      while(HbRbtWEMmG == yTQyVLAQxo){xcCdjPeaIb = true;}
      while(MemucsThGQ == MemucsThGQ){JqRZhkOOFd = true;}
      while(CgnKReErjw == CgnKReErjw){xrJpFyyBzj = true;}
      if(EVCALSWuOn == true){EVCALSWuOn = false;}
      if(wzngzLEzup == true){wzngzLEzup = false;}
      if(BMUXCamGJO == true){BMUXCamGJO = false;}
      if(RMbpCpcljK == true){RMbpCpcljK = false;}
      if(VXTSTCrHLG == true){VXTSTCrHLG = false;}
      if(ZEwsurAdyj == true){ZEwsurAdyj = false;}
      if(eQkzVjWydI == true){eQkzVjWydI = false;}
      if(hSPkUcrBEz == true){hSPkUcrBEz = false;}
      if(ieuDnMPhtK == true){ieuDnMPhtK = false;}
      if(pzmzeEmTxi == true){pzmzeEmTxi = false;}
      if(etcCXHoLYS == true){etcCXHoLYS = false;}
      if(zzZyBzVhKI == true){zzZyBzVhKI = false;}
      if(UoDTSifPFP == true){UoDTSifPFP = false;}
      if(pXEUUnCreg == true){pXEUUnCreg = false;}
      if(XEJbKpYoyf == true){XEJbKpYoyf = false;}
      if(hEJoOpqJio == true){hEJoOpqJio = false;}
      if(bYFIbauFdM == true){bYFIbauFdM = false;}
      if(xcCdjPeaIb == true){xcCdjPeaIb = false;}
      if(JqRZhkOOFd == true){JqRZhkOOFd = false;}
      if(xrJpFyyBzj == true){xrJpFyyBzj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GBQVSIFSTD
{ 
  void ManlcYxMsn()
  { 
      bool exrUEkswNs = false;
      bool fzsmmysHVX = false;
      bool WitgHJPUJz = false;
      bool PRftxBaJoo = false;
      bool eaqxNHKHJn = false;
      bool zKLUdwDKMt = false;
      bool UYmNcOSzol = false;
      bool WiRgswqwTz = false;
      bool zIKVAFFLPB = false;
      bool xQwuTGncUy = false;
      bool oLSXQPrdah = false;
      bool EGqNuMNQNX = false;
      bool IGimnGmWMm = false;
      bool INbUKmomEj = false;
      bool MbkhwqYizH = false;
      bool rWPwoiceiK = false;
      bool cURnZpeVCH = false;
      bool WaLdKgVBqx = false;
      bool gDXEtkyefb = false;
      bool KKDtHrJwHF = false;
      string beGuErwpXA;
      string ZYccMBHnzx;
      string FHDJNpJCnR;
      string lnAscuhBsK;
      string KMzcOfWhel;
      string JhEEYUaxhN;
      string isBGNkXjAQ;
      string SFtomsIatg;
      string SaXBHEiuUI;
      string TkTeaQKrPc;
      string HmgNSDmPRe;
      string LzCAuHVAzJ;
      string CcOrxglPNV;
      string iQLRYfsKiD;
      string QTdowThSjS;
      string uKrGaeXoPl;
      string RXBwwunkaO;
      string OKQurhyYuc;
      string ySetZXXFpt;
      string HEtwlrRgsB;
      if(beGuErwpXA == HmgNSDmPRe){exrUEkswNs = true;}
      else if(HmgNSDmPRe == beGuErwpXA){oLSXQPrdah = true;}
      if(ZYccMBHnzx == LzCAuHVAzJ){fzsmmysHVX = true;}
      else if(LzCAuHVAzJ == ZYccMBHnzx){EGqNuMNQNX = true;}
      if(FHDJNpJCnR == CcOrxglPNV){WitgHJPUJz = true;}
      else if(CcOrxglPNV == FHDJNpJCnR){IGimnGmWMm = true;}
      if(lnAscuhBsK == iQLRYfsKiD){PRftxBaJoo = true;}
      else if(iQLRYfsKiD == lnAscuhBsK){INbUKmomEj = true;}
      if(KMzcOfWhel == QTdowThSjS){eaqxNHKHJn = true;}
      else if(QTdowThSjS == KMzcOfWhel){MbkhwqYizH = true;}
      if(JhEEYUaxhN == uKrGaeXoPl){zKLUdwDKMt = true;}
      else if(uKrGaeXoPl == JhEEYUaxhN){rWPwoiceiK = true;}
      if(isBGNkXjAQ == RXBwwunkaO){UYmNcOSzol = true;}
      else if(RXBwwunkaO == isBGNkXjAQ){cURnZpeVCH = true;}
      if(SFtomsIatg == OKQurhyYuc){WiRgswqwTz = true;}
      if(SaXBHEiuUI == ySetZXXFpt){zIKVAFFLPB = true;}
      if(TkTeaQKrPc == HEtwlrRgsB){xQwuTGncUy = true;}
      while(OKQurhyYuc == SFtomsIatg){WaLdKgVBqx = true;}
      while(ySetZXXFpt == ySetZXXFpt){gDXEtkyefb = true;}
      while(HEtwlrRgsB == HEtwlrRgsB){KKDtHrJwHF = true;}
      if(exrUEkswNs == true){exrUEkswNs = false;}
      if(fzsmmysHVX == true){fzsmmysHVX = false;}
      if(WitgHJPUJz == true){WitgHJPUJz = false;}
      if(PRftxBaJoo == true){PRftxBaJoo = false;}
      if(eaqxNHKHJn == true){eaqxNHKHJn = false;}
      if(zKLUdwDKMt == true){zKLUdwDKMt = false;}
      if(UYmNcOSzol == true){UYmNcOSzol = false;}
      if(WiRgswqwTz == true){WiRgswqwTz = false;}
      if(zIKVAFFLPB == true){zIKVAFFLPB = false;}
      if(xQwuTGncUy == true){xQwuTGncUy = false;}
      if(oLSXQPrdah == true){oLSXQPrdah = false;}
      if(EGqNuMNQNX == true){EGqNuMNQNX = false;}
      if(IGimnGmWMm == true){IGimnGmWMm = false;}
      if(INbUKmomEj == true){INbUKmomEj = false;}
      if(MbkhwqYizH == true){MbkhwqYizH = false;}
      if(rWPwoiceiK == true){rWPwoiceiK = false;}
      if(cURnZpeVCH == true){cURnZpeVCH = false;}
      if(WaLdKgVBqx == true){WaLdKgVBqx = false;}
      if(gDXEtkyefb == true){gDXEtkyefb = false;}
      if(KKDtHrJwHF == true){KKDtHrJwHF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SXHQJCIBGM
{ 
  void DQtaOUlMNd()
  { 
      bool aYTQEpnepM = false;
      bool YxSjpeRLZe = false;
      bool PiOmXNoYHn = false;
      bool BAaCXUEqhf = false;
      bool fFDpZVVwsr = false;
      bool wsTuTqJgsp = false;
      bool BPWBLXVPLV = false;
      bool aactyKfYMB = false;
      bool rreOqHffif = false;
      bool KWxqdQhBdB = false;
      bool AFjWRVQYxI = false;
      bool LjTryIjHJE = false;
      bool rpgeKDckQh = false;
      bool cdtKAlHIxV = false;
      bool qHiZUZDFsU = false;
      bool fZqZJKXFLO = false;
      bool reIPfgoIqL = false;
      bool BbKnMjHHKk = false;
      bool zXruBCmUBp = false;
      bool OCwicLySsm = false;
      string oNXzrRmgtW;
      string ulOfTdVGUN;
      string ZlckbmyCSf;
      string BmfwfBPgXW;
      string hkdFlIsbCg;
      string WXpKFCklWE;
      string SkNOUHFRAR;
      string NnixfoIWzT;
      string tVzlIdxVpc;
      string QdJSDxXOjd;
      string CabjThoreQ;
      string sNmDKwkaFq;
      string KjbWBjePth;
      string QslVQStPSa;
      string nEpZjCpGIG;
      string LwJsSRzFii;
      string DZywzAbRlq;
      string CVHeDGsBly;
      string sXHmVUjsCy;
      string TnfiWOFsZj;
      if(oNXzrRmgtW == CabjThoreQ){aYTQEpnepM = true;}
      else if(CabjThoreQ == oNXzrRmgtW){AFjWRVQYxI = true;}
      if(ulOfTdVGUN == sNmDKwkaFq){YxSjpeRLZe = true;}
      else if(sNmDKwkaFq == ulOfTdVGUN){LjTryIjHJE = true;}
      if(ZlckbmyCSf == KjbWBjePth){PiOmXNoYHn = true;}
      else if(KjbWBjePth == ZlckbmyCSf){rpgeKDckQh = true;}
      if(BmfwfBPgXW == QslVQStPSa){BAaCXUEqhf = true;}
      else if(QslVQStPSa == BmfwfBPgXW){cdtKAlHIxV = true;}
      if(hkdFlIsbCg == nEpZjCpGIG){fFDpZVVwsr = true;}
      else if(nEpZjCpGIG == hkdFlIsbCg){qHiZUZDFsU = true;}
      if(WXpKFCklWE == LwJsSRzFii){wsTuTqJgsp = true;}
      else if(LwJsSRzFii == WXpKFCklWE){fZqZJKXFLO = true;}
      if(SkNOUHFRAR == DZywzAbRlq){BPWBLXVPLV = true;}
      else if(DZywzAbRlq == SkNOUHFRAR){reIPfgoIqL = true;}
      if(NnixfoIWzT == CVHeDGsBly){aactyKfYMB = true;}
      if(tVzlIdxVpc == sXHmVUjsCy){rreOqHffif = true;}
      if(QdJSDxXOjd == TnfiWOFsZj){KWxqdQhBdB = true;}
      while(CVHeDGsBly == NnixfoIWzT){BbKnMjHHKk = true;}
      while(sXHmVUjsCy == sXHmVUjsCy){zXruBCmUBp = true;}
      while(TnfiWOFsZj == TnfiWOFsZj){OCwicLySsm = true;}
      if(aYTQEpnepM == true){aYTQEpnepM = false;}
      if(YxSjpeRLZe == true){YxSjpeRLZe = false;}
      if(PiOmXNoYHn == true){PiOmXNoYHn = false;}
      if(BAaCXUEqhf == true){BAaCXUEqhf = false;}
      if(fFDpZVVwsr == true){fFDpZVVwsr = false;}
      if(wsTuTqJgsp == true){wsTuTqJgsp = false;}
      if(BPWBLXVPLV == true){BPWBLXVPLV = false;}
      if(aactyKfYMB == true){aactyKfYMB = false;}
      if(rreOqHffif == true){rreOqHffif = false;}
      if(KWxqdQhBdB == true){KWxqdQhBdB = false;}
      if(AFjWRVQYxI == true){AFjWRVQYxI = false;}
      if(LjTryIjHJE == true){LjTryIjHJE = false;}
      if(rpgeKDckQh == true){rpgeKDckQh = false;}
      if(cdtKAlHIxV == true){cdtKAlHIxV = false;}
      if(qHiZUZDFsU == true){qHiZUZDFsU = false;}
      if(fZqZJKXFLO == true){fZqZJKXFLO = false;}
      if(reIPfgoIqL == true){reIPfgoIqL = false;}
      if(BbKnMjHHKk == true){BbKnMjHHKk = false;}
      if(zXruBCmUBp == true){zXruBCmUBp = false;}
      if(OCwicLySsm == true){OCwicLySsm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YOECEUETIR
{ 
  void tqjJhpPqUn()
  { 
      bool RitUatYyTX = false;
      bool KjVKgiRNVj = false;
      bool CEGxnLryfN = false;
      bool bJJMKDCCdB = false;
      bool onIwtXfDlA = false;
      bool oONfCMcwfP = false;
      bool CaRGwBaJzc = false;
      bool fPjTuOwJCQ = false;
      bool fnMfYMucJy = false;
      bool ZGVNzNWCAs = false;
      bool wVEIUYdtkn = false;
      bool PSsPiNOlgi = false;
      bool FxzBDZtWUg = false;
      bool rtJJTJjDLA = false;
      bool hBrVhHMFdl = false;
      bool zjUQmzVDFt = false;
      bool eHZDwVJiwZ = false;
      bool cKagAEFdSu = false;
      bool MnrhhHZrWT = false;
      bool ngyQVabnYL = false;
      string EoZlwqdPqI;
      string RqadsbhWZi;
      string COTUQTuGHT;
      string SHgUcTqeFn;
      string eDRwpIEDoC;
      string dsyRCoVFUc;
      string uXIWpKJGBZ;
      string kDQlDzxWdI;
      string PrQEpYIPRm;
      string xlJcrHtuFe;
      string yyBPRZcMND;
      string ryaMMDGDfQ;
      string BtnNbytmsw;
      string EBQyJRpBlP;
      string wwBOuzLxQo;
      string ApOodEJnmT;
      string foSRypgbCu;
      string NFRQUFsZRc;
      string mxWEwNmbUF;
      string HBNSjGciQF;
      if(EoZlwqdPqI == yyBPRZcMND){RitUatYyTX = true;}
      else if(yyBPRZcMND == EoZlwqdPqI){wVEIUYdtkn = true;}
      if(RqadsbhWZi == ryaMMDGDfQ){KjVKgiRNVj = true;}
      else if(ryaMMDGDfQ == RqadsbhWZi){PSsPiNOlgi = true;}
      if(COTUQTuGHT == BtnNbytmsw){CEGxnLryfN = true;}
      else if(BtnNbytmsw == COTUQTuGHT){FxzBDZtWUg = true;}
      if(SHgUcTqeFn == EBQyJRpBlP){bJJMKDCCdB = true;}
      else if(EBQyJRpBlP == SHgUcTqeFn){rtJJTJjDLA = true;}
      if(eDRwpIEDoC == wwBOuzLxQo){onIwtXfDlA = true;}
      else if(wwBOuzLxQo == eDRwpIEDoC){hBrVhHMFdl = true;}
      if(dsyRCoVFUc == ApOodEJnmT){oONfCMcwfP = true;}
      else if(ApOodEJnmT == dsyRCoVFUc){zjUQmzVDFt = true;}
      if(uXIWpKJGBZ == foSRypgbCu){CaRGwBaJzc = true;}
      else if(foSRypgbCu == uXIWpKJGBZ){eHZDwVJiwZ = true;}
      if(kDQlDzxWdI == NFRQUFsZRc){fPjTuOwJCQ = true;}
      if(PrQEpYIPRm == mxWEwNmbUF){fnMfYMucJy = true;}
      if(xlJcrHtuFe == HBNSjGciQF){ZGVNzNWCAs = true;}
      while(NFRQUFsZRc == kDQlDzxWdI){cKagAEFdSu = true;}
      while(mxWEwNmbUF == mxWEwNmbUF){MnrhhHZrWT = true;}
      while(HBNSjGciQF == HBNSjGciQF){ngyQVabnYL = true;}
      if(RitUatYyTX == true){RitUatYyTX = false;}
      if(KjVKgiRNVj == true){KjVKgiRNVj = false;}
      if(CEGxnLryfN == true){CEGxnLryfN = false;}
      if(bJJMKDCCdB == true){bJJMKDCCdB = false;}
      if(onIwtXfDlA == true){onIwtXfDlA = false;}
      if(oONfCMcwfP == true){oONfCMcwfP = false;}
      if(CaRGwBaJzc == true){CaRGwBaJzc = false;}
      if(fPjTuOwJCQ == true){fPjTuOwJCQ = false;}
      if(fnMfYMucJy == true){fnMfYMucJy = false;}
      if(ZGVNzNWCAs == true){ZGVNzNWCAs = false;}
      if(wVEIUYdtkn == true){wVEIUYdtkn = false;}
      if(PSsPiNOlgi == true){PSsPiNOlgi = false;}
      if(FxzBDZtWUg == true){FxzBDZtWUg = false;}
      if(rtJJTJjDLA == true){rtJJTJjDLA = false;}
      if(hBrVhHMFdl == true){hBrVhHMFdl = false;}
      if(zjUQmzVDFt == true){zjUQmzVDFt = false;}
      if(eHZDwVJiwZ == true){eHZDwVJiwZ = false;}
      if(cKagAEFdSu == true){cKagAEFdSu = false;}
      if(MnrhhHZrWT == true){MnrhhHZrWT = false;}
      if(ngyQVabnYL == true){ngyQVabnYL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDJHVKBCVU
{ 
  void rGUhENcaQC()
  { 
      bool AHzuBSdoSB = false;
      bool RxWdRClNrD = false;
      bool ddocnajUrp = false;
      bool EWAuQjarLV = false;
      bool oaKnudSYwI = false;
      bool jrBDrVSWHa = false;
      bool iIxcwtwbMh = false;
      bool asBWODTBgJ = false;
      bool HKYiGLUxCu = false;
      bool QEkkmfchqA = false;
      bool gqLOgpqenn = false;
      bool CRoxSXjNVj = false;
      bool ZzYRQVIQji = false;
      bool ZkJgcQzJCP = false;
      bool UoJNrzPnRO = false;
      bool uOLGZhRtyK = false;
      bool hauENQHHUC = false;
      bool XZLGPkoKYQ = false;
      bool GTyUmLZCGt = false;
      bool yFLqhttEzb = false;
      string iekyzOwQef;
      string ZIGJlKTbAh;
      string mqQuqgUpzK;
      string AqOmJmKfXG;
      string xlCTnUKUUn;
      string fdBLEqNoGR;
      string sGRUehtTzz;
      string AnEskBoxHV;
      string WzUKeVoChR;
      string YUYFMqTgnF;
      string apVVnqZHaD;
      string BQhjutkGoJ;
      string rrlgZeOyft;
      string gHICufdyWm;
      string whadPImnKS;
      string FNreMhEnuI;
      string caagWtHeoO;
      string QmiCMKQHQR;
      string qZnNnSPdpM;
      string aoCNKVGtGV;
      if(iekyzOwQef == apVVnqZHaD){AHzuBSdoSB = true;}
      else if(apVVnqZHaD == iekyzOwQef){gqLOgpqenn = true;}
      if(ZIGJlKTbAh == BQhjutkGoJ){RxWdRClNrD = true;}
      else if(BQhjutkGoJ == ZIGJlKTbAh){CRoxSXjNVj = true;}
      if(mqQuqgUpzK == rrlgZeOyft){ddocnajUrp = true;}
      else if(rrlgZeOyft == mqQuqgUpzK){ZzYRQVIQji = true;}
      if(AqOmJmKfXG == gHICufdyWm){EWAuQjarLV = true;}
      else if(gHICufdyWm == AqOmJmKfXG){ZkJgcQzJCP = true;}
      if(xlCTnUKUUn == whadPImnKS){oaKnudSYwI = true;}
      else if(whadPImnKS == xlCTnUKUUn){UoJNrzPnRO = true;}
      if(fdBLEqNoGR == FNreMhEnuI){jrBDrVSWHa = true;}
      else if(FNreMhEnuI == fdBLEqNoGR){uOLGZhRtyK = true;}
      if(sGRUehtTzz == caagWtHeoO){iIxcwtwbMh = true;}
      else if(caagWtHeoO == sGRUehtTzz){hauENQHHUC = true;}
      if(AnEskBoxHV == QmiCMKQHQR){asBWODTBgJ = true;}
      if(WzUKeVoChR == qZnNnSPdpM){HKYiGLUxCu = true;}
      if(YUYFMqTgnF == aoCNKVGtGV){QEkkmfchqA = true;}
      while(QmiCMKQHQR == AnEskBoxHV){XZLGPkoKYQ = true;}
      while(qZnNnSPdpM == qZnNnSPdpM){GTyUmLZCGt = true;}
      while(aoCNKVGtGV == aoCNKVGtGV){yFLqhttEzb = true;}
      if(AHzuBSdoSB == true){AHzuBSdoSB = false;}
      if(RxWdRClNrD == true){RxWdRClNrD = false;}
      if(ddocnajUrp == true){ddocnajUrp = false;}
      if(EWAuQjarLV == true){EWAuQjarLV = false;}
      if(oaKnudSYwI == true){oaKnudSYwI = false;}
      if(jrBDrVSWHa == true){jrBDrVSWHa = false;}
      if(iIxcwtwbMh == true){iIxcwtwbMh = false;}
      if(asBWODTBgJ == true){asBWODTBgJ = false;}
      if(HKYiGLUxCu == true){HKYiGLUxCu = false;}
      if(QEkkmfchqA == true){QEkkmfchqA = false;}
      if(gqLOgpqenn == true){gqLOgpqenn = false;}
      if(CRoxSXjNVj == true){CRoxSXjNVj = false;}
      if(ZzYRQVIQji == true){ZzYRQVIQji = false;}
      if(ZkJgcQzJCP == true){ZkJgcQzJCP = false;}
      if(UoJNrzPnRO == true){UoJNrzPnRO = false;}
      if(uOLGZhRtyK == true){uOLGZhRtyK = false;}
      if(hauENQHHUC == true){hauENQHHUC = false;}
      if(XZLGPkoKYQ == true){XZLGPkoKYQ = false;}
      if(GTyUmLZCGt == true){GTyUmLZCGt = false;}
      if(yFLqhttEzb == true){yFLqhttEzb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JFYUCJPLQY
{ 
  void HWWJwcfPGA()
  { 
      bool PtSUcVLkNO = false;
      bool dolWIfsJOP = false;
      bool WwktwGPslR = false;
      bool rcOroujoXj = false;
      bool xpJHwJukSe = false;
      bool atnJNTIYXV = false;
      bool FRyuVBZsgN = false;
      bool wDkdRgmcxl = false;
      bool KeaGqynEeV = false;
      bool lKQCefqNku = false;
      bool jCEEiWIKqg = false;
      bool geakKaqqEX = false;
      bool NUOKaklizl = false;
      bool pYrCCIaVXT = false;
      bool pdNyoGjeqE = false;
      bool nzINhOmsdx = false;
      bool jYKFpHmXiC = false;
      bool zVTkgjHQVT = false;
      bool BHruypQdUm = false;
      bool UhrZiRSHHh = false;
      string NMULlNitsA;
      string wJxfDSgXmI;
      string yWtbIRBclf;
      string rsNseqjwIP;
      string HinQYKVccX;
      string KrAUepSsDT;
      string LGINICwDBM;
      string hjOWAPicDy;
      string uYzOUArrOo;
      string XqsnEAZaHV;
      string NSbPoZcdUO;
      string GooFYlHtrI;
      string KDnLnqqZSz;
      string oIVhjcxiYt;
      string WOXzhiBnPR;
      string sfhzKJdPby;
      string iDKUYxSHUu;
      string oXUxkwfocF;
      string oDJBFJaWWZ;
      string zhHaLTDDZk;
      if(NMULlNitsA == NSbPoZcdUO){PtSUcVLkNO = true;}
      else if(NSbPoZcdUO == NMULlNitsA){jCEEiWIKqg = true;}
      if(wJxfDSgXmI == GooFYlHtrI){dolWIfsJOP = true;}
      else if(GooFYlHtrI == wJxfDSgXmI){geakKaqqEX = true;}
      if(yWtbIRBclf == KDnLnqqZSz){WwktwGPslR = true;}
      else if(KDnLnqqZSz == yWtbIRBclf){NUOKaklizl = true;}
      if(rsNseqjwIP == oIVhjcxiYt){rcOroujoXj = true;}
      else if(oIVhjcxiYt == rsNseqjwIP){pYrCCIaVXT = true;}
      if(HinQYKVccX == WOXzhiBnPR){xpJHwJukSe = true;}
      else if(WOXzhiBnPR == HinQYKVccX){pdNyoGjeqE = true;}
      if(KrAUepSsDT == sfhzKJdPby){atnJNTIYXV = true;}
      else if(sfhzKJdPby == KrAUepSsDT){nzINhOmsdx = true;}
      if(LGINICwDBM == iDKUYxSHUu){FRyuVBZsgN = true;}
      else if(iDKUYxSHUu == LGINICwDBM){jYKFpHmXiC = true;}
      if(hjOWAPicDy == oXUxkwfocF){wDkdRgmcxl = true;}
      if(uYzOUArrOo == oDJBFJaWWZ){KeaGqynEeV = true;}
      if(XqsnEAZaHV == zhHaLTDDZk){lKQCefqNku = true;}
      while(oXUxkwfocF == hjOWAPicDy){zVTkgjHQVT = true;}
      while(oDJBFJaWWZ == oDJBFJaWWZ){BHruypQdUm = true;}
      while(zhHaLTDDZk == zhHaLTDDZk){UhrZiRSHHh = true;}
      if(PtSUcVLkNO == true){PtSUcVLkNO = false;}
      if(dolWIfsJOP == true){dolWIfsJOP = false;}
      if(WwktwGPslR == true){WwktwGPslR = false;}
      if(rcOroujoXj == true){rcOroujoXj = false;}
      if(xpJHwJukSe == true){xpJHwJukSe = false;}
      if(atnJNTIYXV == true){atnJNTIYXV = false;}
      if(FRyuVBZsgN == true){FRyuVBZsgN = false;}
      if(wDkdRgmcxl == true){wDkdRgmcxl = false;}
      if(KeaGqynEeV == true){KeaGqynEeV = false;}
      if(lKQCefqNku == true){lKQCefqNku = false;}
      if(jCEEiWIKqg == true){jCEEiWIKqg = false;}
      if(geakKaqqEX == true){geakKaqqEX = false;}
      if(NUOKaklizl == true){NUOKaklizl = false;}
      if(pYrCCIaVXT == true){pYrCCIaVXT = false;}
      if(pdNyoGjeqE == true){pdNyoGjeqE = false;}
      if(nzINhOmsdx == true){nzINhOmsdx = false;}
      if(jYKFpHmXiC == true){jYKFpHmXiC = false;}
      if(zVTkgjHQVT == true){zVTkgjHQVT = false;}
      if(BHruypQdUm == true){BHruypQdUm = false;}
      if(UhrZiRSHHh == true){UhrZiRSHHh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QDYJXMRTQU
{ 
  void eRgpmcfOKH()
  { 
      bool IzlYfoMBIb = false;
      bool rLQKQKkxAB = false;
      bool hnBBKxVKEu = false;
      bool oxNRrxUlOb = false;
      bool dUpdCUinYl = false;
      bool ZKyOJUxjNi = false;
      bool TCxNltxyRT = false;
      bool pyhYWNxXzp = false;
      bool NgkRUeyyIX = false;
      bool zkYeHbXcqH = false;
      bool WjVFwbbZru = false;
      bool WZjWUlQerG = false;
      bool uzotUEZCQu = false;
      bool pTgqSdKfVs = false;
      bool DXGMAZABJV = false;
      bool KrkjMXtbkq = false;
      bool BYJwFDrsEq = false;
      bool akIyDWrctt = false;
      bool EXrtkxiweu = false;
      bool iitdreOKHw = false;
      string ROSeZBZAVy;
      string OnJYuXkwBD;
      string KxQgMNVach;
      string GCQTsxdgpe;
      string mnFWgZPNGK;
      string LcmHQTxkSL;
      string eyWmrLWofx;
      string tEFWPVqtzl;
      string xITSWdPIDY;
      string zrOeznRSdU;
      string CahJPHWPru;
      string cDkfNWeEQN;
      string wNkGxCoaXa;
      string DXPdiVZKDO;
      string HzQHwwGhQc;
      string JNCPYooaLM;
      string RurRqEmHwr;
      string wUABGwxdKB;
      string wGKuQpVzFt;
      string gzypxLHzPr;
      if(ROSeZBZAVy == CahJPHWPru){IzlYfoMBIb = true;}
      else if(CahJPHWPru == ROSeZBZAVy){WjVFwbbZru = true;}
      if(OnJYuXkwBD == cDkfNWeEQN){rLQKQKkxAB = true;}
      else if(cDkfNWeEQN == OnJYuXkwBD){WZjWUlQerG = true;}
      if(KxQgMNVach == wNkGxCoaXa){hnBBKxVKEu = true;}
      else if(wNkGxCoaXa == KxQgMNVach){uzotUEZCQu = true;}
      if(GCQTsxdgpe == DXPdiVZKDO){oxNRrxUlOb = true;}
      else if(DXPdiVZKDO == GCQTsxdgpe){pTgqSdKfVs = true;}
      if(mnFWgZPNGK == HzQHwwGhQc){dUpdCUinYl = true;}
      else if(HzQHwwGhQc == mnFWgZPNGK){DXGMAZABJV = true;}
      if(LcmHQTxkSL == JNCPYooaLM){ZKyOJUxjNi = true;}
      else if(JNCPYooaLM == LcmHQTxkSL){KrkjMXtbkq = true;}
      if(eyWmrLWofx == RurRqEmHwr){TCxNltxyRT = true;}
      else if(RurRqEmHwr == eyWmrLWofx){BYJwFDrsEq = true;}
      if(tEFWPVqtzl == wUABGwxdKB){pyhYWNxXzp = true;}
      if(xITSWdPIDY == wGKuQpVzFt){NgkRUeyyIX = true;}
      if(zrOeznRSdU == gzypxLHzPr){zkYeHbXcqH = true;}
      while(wUABGwxdKB == tEFWPVqtzl){akIyDWrctt = true;}
      while(wGKuQpVzFt == wGKuQpVzFt){EXrtkxiweu = true;}
      while(gzypxLHzPr == gzypxLHzPr){iitdreOKHw = true;}
      if(IzlYfoMBIb == true){IzlYfoMBIb = false;}
      if(rLQKQKkxAB == true){rLQKQKkxAB = false;}
      if(hnBBKxVKEu == true){hnBBKxVKEu = false;}
      if(oxNRrxUlOb == true){oxNRrxUlOb = false;}
      if(dUpdCUinYl == true){dUpdCUinYl = false;}
      if(ZKyOJUxjNi == true){ZKyOJUxjNi = false;}
      if(TCxNltxyRT == true){TCxNltxyRT = false;}
      if(pyhYWNxXzp == true){pyhYWNxXzp = false;}
      if(NgkRUeyyIX == true){NgkRUeyyIX = false;}
      if(zkYeHbXcqH == true){zkYeHbXcqH = false;}
      if(WjVFwbbZru == true){WjVFwbbZru = false;}
      if(WZjWUlQerG == true){WZjWUlQerG = false;}
      if(uzotUEZCQu == true){uzotUEZCQu = false;}
      if(pTgqSdKfVs == true){pTgqSdKfVs = false;}
      if(DXGMAZABJV == true){DXGMAZABJV = false;}
      if(KrkjMXtbkq == true){KrkjMXtbkq = false;}
      if(BYJwFDrsEq == true){BYJwFDrsEq = false;}
      if(akIyDWrctt == true){akIyDWrctt = false;}
      if(EXrtkxiweu == true){EXrtkxiweu = false;}
      if(iitdreOKHw == true){iitdreOKHw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DLLNLMGEDS
{ 
  void CZzSIquoor()
  { 
      bool IkQCAzVlyJ = false;
      bool igSNUbIsYd = false;
      bool sLaCPDHRgn = false;
      bool GrAWhMwdsi = false;
      bool MadoIeVxIS = false;
      bool IXQOWwJNmx = false;
      bool qEFKCqfwfI = false;
      bool eeAoRRhltj = false;
      bool hKINehalzk = false;
      bool ChquqIVTlR = false;
      bool zYRAmdXawF = false;
      bool OXTCOgwqeU = false;
      bool PswtGwmEyJ = false;
      bool uNAbkIsHZA = false;
      bool KzptWeOngK = false;
      bool MdnRBFbWtq = false;
      bool pScmJAXqRF = false;
      bool mnReJPDCXa = false;
      bool hzXmxRZhae = false;
      bool gVNiJqWCkV = false;
      string ZJrrldnpNr;
      string RyGBpjIfon;
      string ippyjHiBZB;
      string TOOnnkJVYY;
      string mZmqKfsawB;
      string BJmJVjTsHd;
      string tmQMYCjSME;
      string ZmHPBICynE;
      string OIFYzKaESE;
      string RQNudAJaRI;
      string waNqbOCXIM;
      string hUFCPlgrMN;
      string aezImIYLkB;
      string zafeImtOwk;
      string IDwFVxKKer;
      string SQNEgQaFDS;
      string pplGMGnZtb;
      string rSubFXhtlp;
      string xNgshhNbyq;
      string MnKduRQosP;
      if(ZJrrldnpNr == waNqbOCXIM){IkQCAzVlyJ = true;}
      else if(waNqbOCXIM == ZJrrldnpNr){zYRAmdXawF = true;}
      if(RyGBpjIfon == hUFCPlgrMN){igSNUbIsYd = true;}
      else if(hUFCPlgrMN == RyGBpjIfon){OXTCOgwqeU = true;}
      if(ippyjHiBZB == aezImIYLkB){sLaCPDHRgn = true;}
      else if(aezImIYLkB == ippyjHiBZB){PswtGwmEyJ = true;}
      if(TOOnnkJVYY == zafeImtOwk){GrAWhMwdsi = true;}
      else if(zafeImtOwk == TOOnnkJVYY){uNAbkIsHZA = true;}
      if(mZmqKfsawB == IDwFVxKKer){MadoIeVxIS = true;}
      else if(IDwFVxKKer == mZmqKfsawB){KzptWeOngK = true;}
      if(BJmJVjTsHd == SQNEgQaFDS){IXQOWwJNmx = true;}
      else if(SQNEgQaFDS == BJmJVjTsHd){MdnRBFbWtq = true;}
      if(tmQMYCjSME == pplGMGnZtb){qEFKCqfwfI = true;}
      else if(pplGMGnZtb == tmQMYCjSME){pScmJAXqRF = true;}
      if(ZmHPBICynE == rSubFXhtlp){eeAoRRhltj = true;}
      if(OIFYzKaESE == xNgshhNbyq){hKINehalzk = true;}
      if(RQNudAJaRI == MnKduRQosP){ChquqIVTlR = true;}
      while(rSubFXhtlp == ZmHPBICynE){mnReJPDCXa = true;}
      while(xNgshhNbyq == xNgshhNbyq){hzXmxRZhae = true;}
      while(MnKduRQosP == MnKduRQosP){gVNiJqWCkV = true;}
      if(IkQCAzVlyJ == true){IkQCAzVlyJ = false;}
      if(igSNUbIsYd == true){igSNUbIsYd = false;}
      if(sLaCPDHRgn == true){sLaCPDHRgn = false;}
      if(GrAWhMwdsi == true){GrAWhMwdsi = false;}
      if(MadoIeVxIS == true){MadoIeVxIS = false;}
      if(IXQOWwJNmx == true){IXQOWwJNmx = false;}
      if(qEFKCqfwfI == true){qEFKCqfwfI = false;}
      if(eeAoRRhltj == true){eeAoRRhltj = false;}
      if(hKINehalzk == true){hKINehalzk = false;}
      if(ChquqIVTlR == true){ChquqIVTlR = false;}
      if(zYRAmdXawF == true){zYRAmdXawF = false;}
      if(OXTCOgwqeU == true){OXTCOgwqeU = false;}
      if(PswtGwmEyJ == true){PswtGwmEyJ = false;}
      if(uNAbkIsHZA == true){uNAbkIsHZA = false;}
      if(KzptWeOngK == true){KzptWeOngK = false;}
      if(MdnRBFbWtq == true){MdnRBFbWtq = false;}
      if(pScmJAXqRF == true){pScmJAXqRF = false;}
      if(mnReJPDCXa == true){mnReJPDCXa = false;}
      if(hzXmxRZhae == true){hzXmxRZhae = false;}
      if(gVNiJqWCkV == true){gVNiJqWCkV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZKJDQJQMW
{ 
  void ADeUkwxyiO()
  { 
      bool dpGqePFaAT = false;
      bool UkraMfyIPY = false;
      bool xpFMuaxNZO = false;
      bool GMxqPzJtHz = false;
      bool xqGFfcokyQ = false;
      bool oDEVDnjsuD = false;
      bool SqBlMHmBKM = false;
      bool VEAPbFiAgS = false;
      bool lLOJYDIbnb = false;
      bool OPyEgGpUrX = false;
      bool pmZltkDntx = false;
      bool EjMcRGbrNJ = false;
      bool zLNixGFwhU = false;
      bool POIJcylcOm = false;
      bool zUgpWeDVla = false;
      bool exGhXdZpnn = false;
      bool fHFYgobDzT = false;
      bool TydZKedWLS = false;
      bool CiJHpSHZky = false;
      bool YuoZGrOIJh = false;
      string kbReTAmdMa;
      string onmSiGPlkg;
      string iahxXdOWOa;
      string HknqJchsty;
      string eiyuUjqCxl;
      string CNHVJKtUGp;
      string lPPlSEAwIF;
      string XWqlCAclcn;
      string mLYbXscSgz;
      string iMlEMOSLbP;
      string jttrNfVUSJ;
      string gHrRDZpnNZ;
      string bgPJVKjmZm;
      string gQJMErRgNr;
      string WHzWRbUUBm;
      string XexCnCdjVC;
      string uiuebQxeNK;
      string HIZVCTgsrt;
      string pPkmPCSHYB;
      string OgLLwnMTuA;
      if(kbReTAmdMa == jttrNfVUSJ){dpGqePFaAT = true;}
      else if(jttrNfVUSJ == kbReTAmdMa){pmZltkDntx = true;}
      if(onmSiGPlkg == gHrRDZpnNZ){UkraMfyIPY = true;}
      else if(gHrRDZpnNZ == onmSiGPlkg){EjMcRGbrNJ = true;}
      if(iahxXdOWOa == bgPJVKjmZm){xpFMuaxNZO = true;}
      else if(bgPJVKjmZm == iahxXdOWOa){zLNixGFwhU = true;}
      if(HknqJchsty == gQJMErRgNr){GMxqPzJtHz = true;}
      else if(gQJMErRgNr == HknqJchsty){POIJcylcOm = true;}
      if(eiyuUjqCxl == WHzWRbUUBm){xqGFfcokyQ = true;}
      else if(WHzWRbUUBm == eiyuUjqCxl){zUgpWeDVla = true;}
      if(CNHVJKtUGp == XexCnCdjVC){oDEVDnjsuD = true;}
      else if(XexCnCdjVC == CNHVJKtUGp){exGhXdZpnn = true;}
      if(lPPlSEAwIF == uiuebQxeNK){SqBlMHmBKM = true;}
      else if(uiuebQxeNK == lPPlSEAwIF){fHFYgobDzT = true;}
      if(XWqlCAclcn == HIZVCTgsrt){VEAPbFiAgS = true;}
      if(mLYbXscSgz == pPkmPCSHYB){lLOJYDIbnb = true;}
      if(iMlEMOSLbP == OgLLwnMTuA){OPyEgGpUrX = true;}
      while(HIZVCTgsrt == XWqlCAclcn){TydZKedWLS = true;}
      while(pPkmPCSHYB == pPkmPCSHYB){CiJHpSHZky = true;}
      while(OgLLwnMTuA == OgLLwnMTuA){YuoZGrOIJh = true;}
      if(dpGqePFaAT == true){dpGqePFaAT = false;}
      if(UkraMfyIPY == true){UkraMfyIPY = false;}
      if(xpFMuaxNZO == true){xpFMuaxNZO = false;}
      if(GMxqPzJtHz == true){GMxqPzJtHz = false;}
      if(xqGFfcokyQ == true){xqGFfcokyQ = false;}
      if(oDEVDnjsuD == true){oDEVDnjsuD = false;}
      if(SqBlMHmBKM == true){SqBlMHmBKM = false;}
      if(VEAPbFiAgS == true){VEAPbFiAgS = false;}
      if(lLOJYDIbnb == true){lLOJYDIbnb = false;}
      if(OPyEgGpUrX == true){OPyEgGpUrX = false;}
      if(pmZltkDntx == true){pmZltkDntx = false;}
      if(EjMcRGbrNJ == true){EjMcRGbrNJ = false;}
      if(zLNixGFwhU == true){zLNixGFwhU = false;}
      if(POIJcylcOm == true){POIJcylcOm = false;}
      if(zUgpWeDVla == true){zUgpWeDVla = false;}
      if(exGhXdZpnn == true){exGhXdZpnn = false;}
      if(fHFYgobDzT == true){fHFYgobDzT = false;}
      if(TydZKedWLS == true){TydZKedWLS = false;}
      if(CiJHpSHZky == true){CiJHpSHZky = false;}
      if(YuoZGrOIJh == true){YuoZGrOIJh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GCAIFYEUAJ
{ 
  void SUkBXkJQWQ()
  { 
      bool FSsBDKyfGg = false;
      bool YxOarWRRiP = false;
      bool pTjuWCfVbg = false;
      bool VHhRPIThzD = false;
      bool NCJpFtjBUd = false;
      bool fxjupkhxdA = false;
      bool ebEZLRPwKj = false;
      bool DjReBmKtoc = false;
      bool SdAxAYXmae = false;
      bool ZVDyYkyjen = false;
      bool dmqkZweEsD = false;
      bool ZnIAgAbGZl = false;
      bool scUeKggTGP = false;
      bool oaOAzfmPXD = false;
      bool sSsXEkMCQX = false;
      bool JqJrtBRLZr = false;
      bool PLycNzYHBB = false;
      bool NMiVraixaY = false;
      bool UdChGxQVFx = false;
      bool NaoenhTPJE = false;
      string QRTeXIsYhu;
      string plNQUeKfiq;
      string KqNrATReDV;
      string PMBWsfBERI;
      string MSgwPcNoxA;
      string VPBINZEadD;
      string pNUMedkpXn;
      string dGNZerKRbX;
      string GcgDAAKsJT;
      string baZNRyyTQl;
      string rXQIWPBbcV;
      string OlzGxNfQMe;
      string TqgDLCfzHf;
      string spBpfhLYgj;
      string ziPmEpbTQE;
      string RgHkSAqNwT;
      string iBTxbXjIaO;
      string BHibekasyV;
      string aMiCNMhPXe;
      string qybNAyOSLg;
      if(QRTeXIsYhu == rXQIWPBbcV){FSsBDKyfGg = true;}
      else if(rXQIWPBbcV == QRTeXIsYhu){dmqkZweEsD = true;}
      if(plNQUeKfiq == OlzGxNfQMe){YxOarWRRiP = true;}
      else if(OlzGxNfQMe == plNQUeKfiq){ZnIAgAbGZl = true;}
      if(KqNrATReDV == TqgDLCfzHf){pTjuWCfVbg = true;}
      else if(TqgDLCfzHf == KqNrATReDV){scUeKggTGP = true;}
      if(PMBWsfBERI == spBpfhLYgj){VHhRPIThzD = true;}
      else if(spBpfhLYgj == PMBWsfBERI){oaOAzfmPXD = true;}
      if(MSgwPcNoxA == ziPmEpbTQE){NCJpFtjBUd = true;}
      else if(ziPmEpbTQE == MSgwPcNoxA){sSsXEkMCQX = true;}
      if(VPBINZEadD == RgHkSAqNwT){fxjupkhxdA = true;}
      else if(RgHkSAqNwT == VPBINZEadD){JqJrtBRLZr = true;}
      if(pNUMedkpXn == iBTxbXjIaO){ebEZLRPwKj = true;}
      else if(iBTxbXjIaO == pNUMedkpXn){PLycNzYHBB = true;}
      if(dGNZerKRbX == BHibekasyV){DjReBmKtoc = true;}
      if(GcgDAAKsJT == aMiCNMhPXe){SdAxAYXmae = true;}
      if(baZNRyyTQl == qybNAyOSLg){ZVDyYkyjen = true;}
      while(BHibekasyV == dGNZerKRbX){NMiVraixaY = true;}
      while(aMiCNMhPXe == aMiCNMhPXe){UdChGxQVFx = true;}
      while(qybNAyOSLg == qybNAyOSLg){NaoenhTPJE = true;}
      if(FSsBDKyfGg == true){FSsBDKyfGg = false;}
      if(YxOarWRRiP == true){YxOarWRRiP = false;}
      if(pTjuWCfVbg == true){pTjuWCfVbg = false;}
      if(VHhRPIThzD == true){VHhRPIThzD = false;}
      if(NCJpFtjBUd == true){NCJpFtjBUd = false;}
      if(fxjupkhxdA == true){fxjupkhxdA = false;}
      if(ebEZLRPwKj == true){ebEZLRPwKj = false;}
      if(DjReBmKtoc == true){DjReBmKtoc = false;}
      if(SdAxAYXmae == true){SdAxAYXmae = false;}
      if(ZVDyYkyjen == true){ZVDyYkyjen = false;}
      if(dmqkZweEsD == true){dmqkZweEsD = false;}
      if(ZnIAgAbGZl == true){ZnIAgAbGZl = false;}
      if(scUeKggTGP == true){scUeKggTGP = false;}
      if(oaOAzfmPXD == true){oaOAzfmPXD = false;}
      if(sSsXEkMCQX == true){sSsXEkMCQX = false;}
      if(JqJrtBRLZr == true){JqJrtBRLZr = false;}
      if(PLycNzYHBB == true){PLycNzYHBB = false;}
      if(NMiVraixaY == true){NMiVraixaY = false;}
      if(UdChGxQVFx == true){UdChGxQVFx = false;}
      if(NaoenhTPJE == true){NaoenhTPJE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSRBMQWCFR
{ 
  void VJbXGANIGP()
  { 
      bool TGSnYLXHCY = false;
      bool unoxDzXCRK = false;
      bool dKmccwzWeM = false;
      bool YoBSONaakx = false;
      bool RBwIbhcFxJ = false;
      bool NwcLiITpLb = false;
      bool LAbpzGmWio = false;
      bool XxRUscNdAu = false;
      bool StZUybLoiF = false;
      bool tkPIkRYGIU = false;
      bool uGWIlQeHSG = false;
      bool uopQJRaHqW = false;
      bool uymctmhIib = false;
      bool DHVezLWQig = false;
      bool xEVcKEuzzT = false;
      bool qQOkZxTtNy = false;
      bool iWXqCnSKQx = false;
      bool tJYKZpbJRp = false;
      bool rhIPjmrjFB = false;
      bool rcDjyafdZW = false;
      string eiYBdyjWRV;
      string eUcziNHTRl;
      string JrsJFEIWhK;
      string fVrXdfqUte;
      string NgwQsONVup;
      string xPxWOloPuY;
      string oNnGoJbFVD;
      string WmYmXcucPq;
      string qmarNQXVJq;
      string paYVoArpaj;
      string mIzrTJpKyk;
      string qMAEhClwsY;
      string lGweMuODxX;
      string kFBfEhmiYE;
      string ZMWXzdaTnm;
      string OuwCyfMUfX;
      string tmMaAlKUAz;
      string OCXozYjXeh;
      string UtPJIoIzgX;
      string VSDAJlzuWM;
      if(eiYBdyjWRV == mIzrTJpKyk){TGSnYLXHCY = true;}
      else if(mIzrTJpKyk == eiYBdyjWRV){uGWIlQeHSG = true;}
      if(eUcziNHTRl == qMAEhClwsY){unoxDzXCRK = true;}
      else if(qMAEhClwsY == eUcziNHTRl){uopQJRaHqW = true;}
      if(JrsJFEIWhK == lGweMuODxX){dKmccwzWeM = true;}
      else if(lGweMuODxX == JrsJFEIWhK){uymctmhIib = true;}
      if(fVrXdfqUte == kFBfEhmiYE){YoBSONaakx = true;}
      else if(kFBfEhmiYE == fVrXdfqUte){DHVezLWQig = true;}
      if(NgwQsONVup == ZMWXzdaTnm){RBwIbhcFxJ = true;}
      else if(ZMWXzdaTnm == NgwQsONVup){xEVcKEuzzT = true;}
      if(xPxWOloPuY == OuwCyfMUfX){NwcLiITpLb = true;}
      else if(OuwCyfMUfX == xPxWOloPuY){qQOkZxTtNy = true;}
      if(oNnGoJbFVD == tmMaAlKUAz){LAbpzGmWio = true;}
      else if(tmMaAlKUAz == oNnGoJbFVD){iWXqCnSKQx = true;}
      if(WmYmXcucPq == OCXozYjXeh){XxRUscNdAu = true;}
      if(qmarNQXVJq == UtPJIoIzgX){StZUybLoiF = true;}
      if(paYVoArpaj == VSDAJlzuWM){tkPIkRYGIU = true;}
      while(OCXozYjXeh == WmYmXcucPq){tJYKZpbJRp = true;}
      while(UtPJIoIzgX == UtPJIoIzgX){rhIPjmrjFB = true;}
      while(VSDAJlzuWM == VSDAJlzuWM){rcDjyafdZW = true;}
      if(TGSnYLXHCY == true){TGSnYLXHCY = false;}
      if(unoxDzXCRK == true){unoxDzXCRK = false;}
      if(dKmccwzWeM == true){dKmccwzWeM = false;}
      if(YoBSONaakx == true){YoBSONaakx = false;}
      if(RBwIbhcFxJ == true){RBwIbhcFxJ = false;}
      if(NwcLiITpLb == true){NwcLiITpLb = false;}
      if(LAbpzGmWio == true){LAbpzGmWio = false;}
      if(XxRUscNdAu == true){XxRUscNdAu = false;}
      if(StZUybLoiF == true){StZUybLoiF = false;}
      if(tkPIkRYGIU == true){tkPIkRYGIU = false;}
      if(uGWIlQeHSG == true){uGWIlQeHSG = false;}
      if(uopQJRaHqW == true){uopQJRaHqW = false;}
      if(uymctmhIib == true){uymctmhIib = false;}
      if(DHVezLWQig == true){DHVezLWQig = false;}
      if(xEVcKEuzzT == true){xEVcKEuzzT = false;}
      if(qQOkZxTtNy == true){qQOkZxTtNy = false;}
      if(iWXqCnSKQx == true){iWXqCnSKQx = false;}
      if(tJYKZpbJRp == true){tJYKZpbJRp = false;}
      if(rhIPjmrjFB == true){rhIPjmrjFB = false;}
      if(rcDjyafdZW == true){rcDjyafdZW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ATVHGJKQRY
{ 
  void BYBYwUUqhb()
  { 
      bool JHnxEflYCn = false;
      bool TLTIKREjZD = false;
      bool leUWbmahWu = false;
      bool XaRKGFfrnG = false;
      bool FDdqNdYDuU = false;
      bool GsUlVdmQUR = false;
      bool EDCHQssJCF = false;
      bool lLuSxhBcIx = false;
      bool NXmCoeFfnb = false;
      bool SOXWCCBWaU = false;
      bool kPBoitxCnm = false;
      bool cJIWDfQzSl = false;
      bool mNVZmWmXQu = false;
      bool gdCnMyWxSt = false;
      bool gCqAzIGATV = false;
      bool kBEngXsaCM = false;
      bool HYlrGyGUJE = false;
      bool ISfXEkVUZd = false;
      bool PlEtJeZNGo = false;
      bool EuuGmHQzsA = false;
      string cEXcezmyZO;
      string btTBwOYmDL;
      string oQrjKfbSLM;
      string AFqZLkQnpW;
      string NdhhSUISVp;
      string kuoRYLMmSz;
      string WUmMOWCtpK;
      string yjwfyKiJRp;
      string XJwVbEPZAA;
      string YdVqArqVTw;
      string RNcKrBzJSO;
      string cCVcbNYRkK;
      string GctplUNFfG;
      string SNpUXJfkcZ;
      string EGHlXVHsOl;
      string TZjIooTmYX;
      string mtcMwOMAER;
      string gmnKFAVHSP;
      string MUpsmrcgfh;
      string psLFmKctpI;
      if(cEXcezmyZO == RNcKrBzJSO){JHnxEflYCn = true;}
      else if(RNcKrBzJSO == cEXcezmyZO){kPBoitxCnm = true;}
      if(btTBwOYmDL == cCVcbNYRkK){TLTIKREjZD = true;}
      else if(cCVcbNYRkK == btTBwOYmDL){cJIWDfQzSl = true;}
      if(oQrjKfbSLM == GctplUNFfG){leUWbmahWu = true;}
      else if(GctplUNFfG == oQrjKfbSLM){mNVZmWmXQu = true;}
      if(AFqZLkQnpW == SNpUXJfkcZ){XaRKGFfrnG = true;}
      else if(SNpUXJfkcZ == AFqZLkQnpW){gdCnMyWxSt = true;}
      if(NdhhSUISVp == EGHlXVHsOl){FDdqNdYDuU = true;}
      else if(EGHlXVHsOl == NdhhSUISVp){gCqAzIGATV = true;}
      if(kuoRYLMmSz == TZjIooTmYX){GsUlVdmQUR = true;}
      else if(TZjIooTmYX == kuoRYLMmSz){kBEngXsaCM = true;}
      if(WUmMOWCtpK == mtcMwOMAER){EDCHQssJCF = true;}
      else if(mtcMwOMAER == WUmMOWCtpK){HYlrGyGUJE = true;}
      if(yjwfyKiJRp == gmnKFAVHSP){lLuSxhBcIx = true;}
      if(XJwVbEPZAA == MUpsmrcgfh){NXmCoeFfnb = true;}
      if(YdVqArqVTw == psLFmKctpI){SOXWCCBWaU = true;}
      while(gmnKFAVHSP == yjwfyKiJRp){ISfXEkVUZd = true;}
      while(MUpsmrcgfh == MUpsmrcgfh){PlEtJeZNGo = true;}
      while(psLFmKctpI == psLFmKctpI){EuuGmHQzsA = true;}
      if(JHnxEflYCn == true){JHnxEflYCn = false;}
      if(TLTIKREjZD == true){TLTIKREjZD = false;}
      if(leUWbmahWu == true){leUWbmahWu = false;}
      if(XaRKGFfrnG == true){XaRKGFfrnG = false;}
      if(FDdqNdYDuU == true){FDdqNdYDuU = false;}
      if(GsUlVdmQUR == true){GsUlVdmQUR = false;}
      if(EDCHQssJCF == true){EDCHQssJCF = false;}
      if(lLuSxhBcIx == true){lLuSxhBcIx = false;}
      if(NXmCoeFfnb == true){NXmCoeFfnb = false;}
      if(SOXWCCBWaU == true){SOXWCCBWaU = false;}
      if(kPBoitxCnm == true){kPBoitxCnm = false;}
      if(cJIWDfQzSl == true){cJIWDfQzSl = false;}
      if(mNVZmWmXQu == true){mNVZmWmXQu = false;}
      if(gdCnMyWxSt == true){gdCnMyWxSt = false;}
      if(gCqAzIGATV == true){gCqAzIGATV = false;}
      if(kBEngXsaCM == true){kBEngXsaCM = false;}
      if(HYlrGyGUJE == true){HYlrGyGUJE = false;}
      if(ISfXEkVUZd == true){ISfXEkVUZd = false;}
      if(PlEtJeZNGo == true){PlEtJeZNGo = false;}
      if(EuuGmHQzsA == true){EuuGmHQzsA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PHAOCGDPQS
{ 
  void DINdwskkzE()
  { 
      bool rVaWBCYSrb = false;
      bool pfguCDahBP = false;
      bool qamqADnCLa = false;
      bool aIMTBJmJCX = false;
      bool dBtkHqZVNf = false;
      bool ootOTQiiVy = false;
      bool OVHRAhSMss = false;
      bool QRfdkpgCiJ = false;
      bool cRnfkkNyzk = false;
      bool ZEnDIItcjZ = false;
      bool XMcUPXIPdd = false;
      bool jgzMUwgbfP = false;
      bool TUMHSLccVc = false;
      bool wDSJkQoTPN = false;
      bool byUVAsEbhL = false;
      bool aSxTGDzUCD = false;
      bool tftAhfOoaE = false;
      bool HNLRmVAqHY = false;
      bool GBtJBcGyDh = false;
      bool QTQMSwETnU = false;
      string sKlFwnkjXJ;
      string qCihucliJY;
      string WCzcCUZdfc;
      string jUqhJCSEqE;
      string YOHaGjMnhw;
      string dbHJWpKJDb;
      string OGDuZWKAXr;
      string KgqFAHuYWS;
      string HkujyIMhLT;
      string rIBPoSLLBj;
      string YMQokxjCJO;
      string ukmjTdKSxQ;
      string JcnDACebPg;
      string uiXmtuTGzB;
      string YKXxXGVQuL;
      string HrOjZuXMoi;
      string RHlbSLNzpY;
      string JETuryEqft;
      string fNgDZDUmMy;
      string XGQQjQXwdL;
      if(sKlFwnkjXJ == YMQokxjCJO){rVaWBCYSrb = true;}
      else if(YMQokxjCJO == sKlFwnkjXJ){XMcUPXIPdd = true;}
      if(qCihucliJY == ukmjTdKSxQ){pfguCDahBP = true;}
      else if(ukmjTdKSxQ == qCihucliJY){jgzMUwgbfP = true;}
      if(WCzcCUZdfc == JcnDACebPg){qamqADnCLa = true;}
      else if(JcnDACebPg == WCzcCUZdfc){TUMHSLccVc = true;}
      if(jUqhJCSEqE == uiXmtuTGzB){aIMTBJmJCX = true;}
      else if(uiXmtuTGzB == jUqhJCSEqE){wDSJkQoTPN = true;}
      if(YOHaGjMnhw == YKXxXGVQuL){dBtkHqZVNf = true;}
      else if(YKXxXGVQuL == YOHaGjMnhw){byUVAsEbhL = true;}
      if(dbHJWpKJDb == HrOjZuXMoi){ootOTQiiVy = true;}
      else if(HrOjZuXMoi == dbHJWpKJDb){aSxTGDzUCD = true;}
      if(OGDuZWKAXr == RHlbSLNzpY){OVHRAhSMss = true;}
      else if(RHlbSLNzpY == OGDuZWKAXr){tftAhfOoaE = true;}
      if(KgqFAHuYWS == JETuryEqft){QRfdkpgCiJ = true;}
      if(HkujyIMhLT == fNgDZDUmMy){cRnfkkNyzk = true;}
      if(rIBPoSLLBj == XGQQjQXwdL){ZEnDIItcjZ = true;}
      while(JETuryEqft == KgqFAHuYWS){HNLRmVAqHY = true;}
      while(fNgDZDUmMy == fNgDZDUmMy){GBtJBcGyDh = true;}
      while(XGQQjQXwdL == XGQQjQXwdL){QTQMSwETnU = true;}
      if(rVaWBCYSrb == true){rVaWBCYSrb = false;}
      if(pfguCDahBP == true){pfguCDahBP = false;}
      if(qamqADnCLa == true){qamqADnCLa = false;}
      if(aIMTBJmJCX == true){aIMTBJmJCX = false;}
      if(dBtkHqZVNf == true){dBtkHqZVNf = false;}
      if(ootOTQiiVy == true){ootOTQiiVy = false;}
      if(OVHRAhSMss == true){OVHRAhSMss = false;}
      if(QRfdkpgCiJ == true){QRfdkpgCiJ = false;}
      if(cRnfkkNyzk == true){cRnfkkNyzk = false;}
      if(ZEnDIItcjZ == true){ZEnDIItcjZ = false;}
      if(XMcUPXIPdd == true){XMcUPXIPdd = false;}
      if(jgzMUwgbfP == true){jgzMUwgbfP = false;}
      if(TUMHSLccVc == true){TUMHSLccVc = false;}
      if(wDSJkQoTPN == true){wDSJkQoTPN = false;}
      if(byUVAsEbhL == true){byUVAsEbhL = false;}
      if(aSxTGDzUCD == true){aSxTGDzUCD = false;}
      if(tftAhfOoaE == true){tftAhfOoaE = false;}
      if(HNLRmVAqHY == true){HNLRmVAqHY = false;}
      if(GBtJBcGyDh == true){GBtJBcGyDh = false;}
      if(QTQMSwETnU == true){QTQMSwETnU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MGVKYVCKYG
{ 
  void NxzqXYNrWh()
  { 
      bool NTPPtIuPUl = false;
      bool gwFzAaglRi = false;
      bool UFTfXVlfLY = false;
      bool MGAyFOChln = false;
      bool XmfSNupVEH = false;
      bool KUeOZHzjqY = false;
      bool VODwZZuHtk = false;
      bool XyAdKgZASc = false;
      bool eQbENqalYx = false;
      bool PRpMRIiism = false;
      bool zibSiLUBEs = false;
      bool hzROtFmzhi = false;
      bool zJiwVFHmLB = false;
      bool xpHecunIUC = false;
      bool VYgePQAbSM = false;
      bool VjBKmpAfwc = false;
      bool EhpCuqqlky = false;
      bool QdefMabDfF = false;
      bool FeTyeNnxrm = false;
      bool uILqxnhdjY = false;
      string GtoKMJstlR;
      string utZBFfeZQk;
      string yawqdelzRk;
      string zPrVjHabOx;
      string IlgofAydDQ;
      string GTdEPeyxgh;
      string WscBReCERx;
      string FDKScLtHLc;
      string fIuAefkmFE;
      string JdtgaOJfWA;
      string ytMGLCILbE;
      string kpkEBNxbVl;
      string tOzMmbJdrN;
      string BNjLdlwoob;
      string WZLASTrpeM;
      string QhJjGjtzTj;
      string seSNCXFYZP;
      string RIltPTDysT;
      string iSyfwTDAFt;
      string qwVFhqHxxu;
      if(GtoKMJstlR == ytMGLCILbE){NTPPtIuPUl = true;}
      else if(ytMGLCILbE == GtoKMJstlR){zibSiLUBEs = true;}
      if(utZBFfeZQk == kpkEBNxbVl){gwFzAaglRi = true;}
      else if(kpkEBNxbVl == utZBFfeZQk){hzROtFmzhi = true;}
      if(yawqdelzRk == tOzMmbJdrN){UFTfXVlfLY = true;}
      else if(tOzMmbJdrN == yawqdelzRk){zJiwVFHmLB = true;}
      if(zPrVjHabOx == BNjLdlwoob){MGAyFOChln = true;}
      else if(BNjLdlwoob == zPrVjHabOx){xpHecunIUC = true;}
      if(IlgofAydDQ == WZLASTrpeM){XmfSNupVEH = true;}
      else if(WZLASTrpeM == IlgofAydDQ){VYgePQAbSM = true;}
      if(GTdEPeyxgh == QhJjGjtzTj){KUeOZHzjqY = true;}
      else if(QhJjGjtzTj == GTdEPeyxgh){VjBKmpAfwc = true;}
      if(WscBReCERx == seSNCXFYZP){VODwZZuHtk = true;}
      else if(seSNCXFYZP == WscBReCERx){EhpCuqqlky = true;}
      if(FDKScLtHLc == RIltPTDysT){XyAdKgZASc = true;}
      if(fIuAefkmFE == iSyfwTDAFt){eQbENqalYx = true;}
      if(JdtgaOJfWA == qwVFhqHxxu){PRpMRIiism = true;}
      while(RIltPTDysT == FDKScLtHLc){QdefMabDfF = true;}
      while(iSyfwTDAFt == iSyfwTDAFt){FeTyeNnxrm = true;}
      while(qwVFhqHxxu == qwVFhqHxxu){uILqxnhdjY = true;}
      if(NTPPtIuPUl == true){NTPPtIuPUl = false;}
      if(gwFzAaglRi == true){gwFzAaglRi = false;}
      if(UFTfXVlfLY == true){UFTfXVlfLY = false;}
      if(MGAyFOChln == true){MGAyFOChln = false;}
      if(XmfSNupVEH == true){XmfSNupVEH = false;}
      if(KUeOZHzjqY == true){KUeOZHzjqY = false;}
      if(VODwZZuHtk == true){VODwZZuHtk = false;}
      if(XyAdKgZASc == true){XyAdKgZASc = false;}
      if(eQbENqalYx == true){eQbENqalYx = false;}
      if(PRpMRIiism == true){PRpMRIiism = false;}
      if(zibSiLUBEs == true){zibSiLUBEs = false;}
      if(hzROtFmzhi == true){hzROtFmzhi = false;}
      if(zJiwVFHmLB == true){zJiwVFHmLB = false;}
      if(xpHecunIUC == true){xpHecunIUC = false;}
      if(VYgePQAbSM == true){VYgePQAbSM = false;}
      if(VjBKmpAfwc == true){VjBKmpAfwc = false;}
      if(EhpCuqqlky == true){EhpCuqqlky = false;}
      if(QdefMabDfF == true){QdefMabDfF = false;}
      if(FeTyeNnxrm == true){FeTyeNnxrm = false;}
      if(uILqxnhdjY == true){uILqxnhdjY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SAQGNWYOEB
{ 
  void IJknxAjVci()
  { 
      bool ponxAYKmNw = false;
      bool HBMJoGKyLE = false;
      bool nRWuNmLgiP = false;
      bool rswswVknPi = false;
      bool QOubOLXEzt = false;
      bool jdtepXRsjN = false;
      bool MdExEOESNS = false;
      bool VVibnYVugB = false;
      bool OHgoeNzRCY = false;
      bool ErEBVlKxWz = false;
      bool HEqgYOuRqQ = false;
      bool BVLhzFxOSp = false;
      bool PlPnNdRgGB = false;
      bool OXXgtJPAQQ = false;
      bool ShakWifVCQ = false;
      bool ouegjUnCSt = false;
      bool wOLoCcyeno = false;
      bool oxyBWhLeRe = false;
      bool xwdoLTsqwZ = false;
      bool UNgVTEVkit = false;
      string iIISFKnArT;
      string JrtrVyoyWZ;
      string nGpCNINpCk;
      string ODSrNrdHrP;
      string hntfhEgKdQ;
      string sOJSmbSGEx;
      string xxxHEFYBed;
      string ThFHqzMJTJ;
      string aCLlqAsAEk;
      string ZXCtSkqmbc;
      string fefAwLICan;
      string PIluVtkKPD;
      string LYxtDwfKnG;
      string HYhpduWLof;
      string rqZQVQkGYX;
      string zfWYRGhkwA;
      string fxOTfpawRa;
      string XZVjKUzgYl;
      string KYlPHbCJYW;
      string MkOoAubFje;
      if(iIISFKnArT == fefAwLICan){ponxAYKmNw = true;}
      else if(fefAwLICan == iIISFKnArT){HEqgYOuRqQ = true;}
      if(JrtrVyoyWZ == PIluVtkKPD){HBMJoGKyLE = true;}
      else if(PIluVtkKPD == JrtrVyoyWZ){BVLhzFxOSp = true;}
      if(nGpCNINpCk == LYxtDwfKnG){nRWuNmLgiP = true;}
      else if(LYxtDwfKnG == nGpCNINpCk){PlPnNdRgGB = true;}
      if(ODSrNrdHrP == HYhpduWLof){rswswVknPi = true;}
      else if(HYhpduWLof == ODSrNrdHrP){OXXgtJPAQQ = true;}
      if(hntfhEgKdQ == rqZQVQkGYX){QOubOLXEzt = true;}
      else if(rqZQVQkGYX == hntfhEgKdQ){ShakWifVCQ = true;}
      if(sOJSmbSGEx == zfWYRGhkwA){jdtepXRsjN = true;}
      else if(zfWYRGhkwA == sOJSmbSGEx){ouegjUnCSt = true;}
      if(xxxHEFYBed == fxOTfpawRa){MdExEOESNS = true;}
      else if(fxOTfpawRa == xxxHEFYBed){wOLoCcyeno = true;}
      if(ThFHqzMJTJ == XZVjKUzgYl){VVibnYVugB = true;}
      if(aCLlqAsAEk == KYlPHbCJYW){OHgoeNzRCY = true;}
      if(ZXCtSkqmbc == MkOoAubFje){ErEBVlKxWz = true;}
      while(XZVjKUzgYl == ThFHqzMJTJ){oxyBWhLeRe = true;}
      while(KYlPHbCJYW == KYlPHbCJYW){xwdoLTsqwZ = true;}
      while(MkOoAubFje == MkOoAubFje){UNgVTEVkit = true;}
      if(ponxAYKmNw == true){ponxAYKmNw = false;}
      if(HBMJoGKyLE == true){HBMJoGKyLE = false;}
      if(nRWuNmLgiP == true){nRWuNmLgiP = false;}
      if(rswswVknPi == true){rswswVknPi = false;}
      if(QOubOLXEzt == true){QOubOLXEzt = false;}
      if(jdtepXRsjN == true){jdtepXRsjN = false;}
      if(MdExEOESNS == true){MdExEOESNS = false;}
      if(VVibnYVugB == true){VVibnYVugB = false;}
      if(OHgoeNzRCY == true){OHgoeNzRCY = false;}
      if(ErEBVlKxWz == true){ErEBVlKxWz = false;}
      if(HEqgYOuRqQ == true){HEqgYOuRqQ = false;}
      if(BVLhzFxOSp == true){BVLhzFxOSp = false;}
      if(PlPnNdRgGB == true){PlPnNdRgGB = false;}
      if(OXXgtJPAQQ == true){OXXgtJPAQQ = false;}
      if(ShakWifVCQ == true){ShakWifVCQ = false;}
      if(ouegjUnCSt == true){ouegjUnCSt = false;}
      if(wOLoCcyeno == true){wOLoCcyeno = false;}
      if(oxyBWhLeRe == true){oxyBWhLeRe = false;}
      if(xwdoLTsqwZ == true){xwdoLTsqwZ = false;}
      if(UNgVTEVkit == true){UNgVTEVkit = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PQWELYYTFJ
{ 
  void LpcLBjWXJO()
  { 
      bool EbdAlnpsjA = false;
      bool VbHgWoliMx = false;
      bool sOkAVpmRMM = false;
      bool yWTaGwQwJR = false;
      bool EaXMZIcIpM = false;
      bool XrfsKpqdew = false;
      bool BYfXBzHfaZ = false;
      bool YoZtrRpXaM = false;
      bool MeaAnGqZQQ = false;
      bool FmQMQfuALa = false;
      bool AxgPnhSkAr = false;
      bool zTCRiVxejt = false;
      bool HgPKUkYMdM = false;
      bool WpMzMPxKMF = false;
      bool nGZXQljzdt = false;
      bool hPQQTShWuC = false;
      bool JFHnVIHDFT = false;
      bool YlSdGBHqsi = false;
      bool BYiidGZufs = false;
      bool gaPJwhylBI = false;
      string TdLGFpXEXG;
      string hYUfpDHFkI;
      string frFehYmxLc;
      string JFwffnreQP;
      string FDFTjnUhhG;
      string icKtlaYgYf;
      string DasuwbbnAC;
      string LboVCbllus;
      string DEOEsguCtE;
      string OLGjLdKKWH;
      string LfhfuGnoqK;
      string nmkecyMnCP;
      string gZtumzVEJY;
      string QbPmhWWiJl;
      string sGKjPbZaHN;
      string RVIGZkllrw;
      string jieSsMXyxG;
      string adePVZPKeK;
      string YuxuGuTIMw;
      string jkpNCJarpD;
      if(TdLGFpXEXG == LfhfuGnoqK){EbdAlnpsjA = true;}
      else if(LfhfuGnoqK == TdLGFpXEXG){AxgPnhSkAr = true;}
      if(hYUfpDHFkI == nmkecyMnCP){VbHgWoliMx = true;}
      else if(nmkecyMnCP == hYUfpDHFkI){zTCRiVxejt = true;}
      if(frFehYmxLc == gZtumzVEJY){sOkAVpmRMM = true;}
      else if(gZtumzVEJY == frFehYmxLc){HgPKUkYMdM = true;}
      if(JFwffnreQP == QbPmhWWiJl){yWTaGwQwJR = true;}
      else if(QbPmhWWiJl == JFwffnreQP){WpMzMPxKMF = true;}
      if(FDFTjnUhhG == sGKjPbZaHN){EaXMZIcIpM = true;}
      else if(sGKjPbZaHN == FDFTjnUhhG){nGZXQljzdt = true;}
      if(icKtlaYgYf == RVIGZkllrw){XrfsKpqdew = true;}
      else if(RVIGZkllrw == icKtlaYgYf){hPQQTShWuC = true;}
      if(DasuwbbnAC == jieSsMXyxG){BYfXBzHfaZ = true;}
      else if(jieSsMXyxG == DasuwbbnAC){JFHnVIHDFT = true;}
      if(LboVCbllus == adePVZPKeK){YoZtrRpXaM = true;}
      if(DEOEsguCtE == YuxuGuTIMw){MeaAnGqZQQ = true;}
      if(OLGjLdKKWH == jkpNCJarpD){FmQMQfuALa = true;}
      while(adePVZPKeK == LboVCbllus){YlSdGBHqsi = true;}
      while(YuxuGuTIMw == YuxuGuTIMw){BYiidGZufs = true;}
      while(jkpNCJarpD == jkpNCJarpD){gaPJwhylBI = true;}
      if(EbdAlnpsjA == true){EbdAlnpsjA = false;}
      if(VbHgWoliMx == true){VbHgWoliMx = false;}
      if(sOkAVpmRMM == true){sOkAVpmRMM = false;}
      if(yWTaGwQwJR == true){yWTaGwQwJR = false;}
      if(EaXMZIcIpM == true){EaXMZIcIpM = false;}
      if(XrfsKpqdew == true){XrfsKpqdew = false;}
      if(BYfXBzHfaZ == true){BYfXBzHfaZ = false;}
      if(YoZtrRpXaM == true){YoZtrRpXaM = false;}
      if(MeaAnGqZQQ == true){MeaAnGqZQQ = false;}
      if(FmQMQfuALa == true){FmQMQfuALa = false;}
      if(AxgPnhSkAr == true){AxgPnhSkAr = false;}
      if(zTCRiVxejt == true){zTCRiVxejt = false;}
      if(HgPKUkYMdM == true){HgPKUkYMdM = false;}
      if(WpMzMPxKMF == true){WpMzMPxKMF = false;}
      if(nGZXQljzdt == true){nGZXQljzdt = false;}
      if(hPQQTShWuC == true){hPQQTShWuC = false;}
      if(JFHnVIHDFT == true){JFHnVIHDFT = false;}
      if(YlSdGBHqsi == true){YlSdGBHqsi = false;}
      if(BYiidGZufs == true){BYiidGZufs = false;}
      if(gaPJwhylBI == true){gaPJwhylBI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PXHZBABZKN
{ 
  void VxoWEPYDaG()
  { 
      bool VwQfVmxzPW = false;
      bool NOHycdyyUh = false;
      bool YkBJtlHXAV = false;
      bool cedZCQLsYj = false;
      bool HKoLoJQODh = false;
      bool HqjLojuGlj = false;
      bool eYysshkhuM = false;
      bool SEYkaNuoUj = false;
      bool UrTROktSjR = false;
      bool UEHoEhMuRG = false;
      bool YiSqPCRzjb = false;
      bool oGlBOmEfeH = false;
      bool mSxcqOwjgs = false;
      bool AAWOKlYcCL = false;
      bool SuhIcOSGaR = false;
      bool cfQJSGlpzA = false;
      bool GhSqaniWpc = false;
      bool NadSnrjoAc = false;
      bool wpIOPUiMuE = false;
      bool zidBFkbpgn = false;
      string iBtzzAZEpF;
      string hYdIPrZJkr;
      string uPUVIUTgVg;
      string ZWaBVfLfIt;
      string ELAbEcSSpP;
      string DzOJbTfYqe;
      string fshIeLycmj;
      string fsBqniOsQe;
      string BApGcaHRYC;
      string zmocNKdrws;
      string epfGiKxXUr;
      string FmHLdfDbfE;
      string DgDkjsEYcd;
      string FWwXAKTiWS;
      string cjwfwLfczh;
      string GBMqoxluVp;
      string FXtqlipiLS;
      string LTEMaSjXnX;
      string MbZuWEJFhC;
      string YYMgMFpFsN;
      if(iBtzzAZEpF == epfGiKxXUr){VwQfVmxzPW = true;}
      else if(epfGiKxXUr == iBtzzAZEpF){YiSqPCRzjb = true;}
      if(hYdIPrZJkr == FmHLdfDbfE){NOHycdyyUh = true;}
      else if(FmHLdfDbfE == hYdIPrZJkr){oGlBOmEfeH = true;}
      if(uPUVIUTgVg == DgDkjsEYcd){YkBJtlHXAV = true;}
      else if(DgDkjsEYcd == uPUVIUTgVg){mSxcqOwjgs = true;}
      if(ZWaBVfLfIt == FWwXAKTiWS){cedZCQLsYj = true;}
      else if(FWwXAKTiWS == ZWaBVfLfIt){AAWOKlYcCL = true;}
      if(ELAbEcSSpP == cjwfwLfczh){HKoLoJQODh = true;}
      else if(cjwfwLfczh == ELAbEcSSpP){SuhIcOSGaR = true;}
      if(DzOJbTfYqe == GBMqoxluVp){HqjLojuGlj = true;}
      else if(GBMqoxluVp == DzOJbTfYqe){cfQJSGlpzA = true;}
      if(fshIeLycmj == FXtqlipiLS){eYysshkhuM = true;}
      else if(FXtqlipiLS == fshIeLycmj){GhSqaniWpc = true;}
      if(fsBqniOsQe == LTEMaSjXnX){SEYkaNuoUj = true;}
      if(BApGcaHRYC == MbZuWEJFhC){UrTROktSjR = true;}
      if(zmocNKdrws == YYMgMFpFsN){UEHoEhMuRG = true;}
      while(LTEMaSjXnX == fsBqniOsQe){NadSnrjoAc = true;}
      while(MbZuWEJFhC == MbZuWEJFhC){wpIOPUiMuE = true;}
      while(YYMgMFpFsN == YYMgMFpFsN){zidBFkbpgn = true;}
      if(VwQfVmxzPW == true){VwQfVmxzPW = false;}
      if(NOHycdyyUh == true){NOHycdyyUh = false;}
      if(YkBJtlHXAV == true){YkBJtlHXAV = false;}
      if(cedZCQLsYj == true){cedZCQLsYj = false;}
      if(HKoLoJQODh == true){HKoLoJQODh = false;}
      if(HqjLojuGlj == true){HqjLojuGlj = false;}
      if(eYysshkhuM == true){eYysshkhuM = false;}
      if(SEYkaNuoUj == true){SEYkaNuoUj = false;}
      if(UrTROktSjR == true){UrTROktSjR = false;}
      if(UEHoEhMuRG == true){UEHoEhMuRG = false;}
      if(YiSqPCRzjb == true){YiSqPCRzjb = false;}
      if(oGlBOmEfeH == true){oGlBOmEfeH = false;}
      if(mSxcqOwjgs == true){mSxcqOwjgs = false;}
      if(AAWOKlYcCL == true){AAWOKlYcCL = false;}
      if(SuhIcOSGaR == true){SuhIcOSGaR = false;}
      if(cfQJSGlpzA == true){cfQJSGlpzA = false;}
      if(GhSqaniWpc == true){GhSqaniWpc = false;}
      if(NadSnrjoAc == true){NadSnrjoAc = false;}
      if(wpIOPUiMuE == true){wpIOPUiMuE = false;}
      if(zidBFkbpgn == true){zidBFkbpgn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OKCQJAOQQM
{ 
  void QUyoHRTKwL()
  { 
      bool xnCRxYeapw = false;
      bool KAyrVDPdMU = false;
      bool qxqILMEaTL = false;
      bool AiSWrjHdRE = false;
      bool rXRVCfXkLs = false;
      bool eEbzBzxsGk = false;
      bool TDHdubhbzk = false;
      bool wkLHbSeUGf = false;
      bool nTPZfwGTUs = false;
      bool mNXgjnPnZa = false;
      bool xwkaxtrUWi = false;
      bool TbmZwznhxz = false;
      bool UOGFyhMdWm = false;
      bool Cqtfhriocl = false;
      bool ElwlYKaxkj = false;
      bool AhqaGioebO = false;
      bool gNxifcgGrD = false;
      bool QzFKthRUgm = false;
      bool HOslmTATZz = false;
      bool DDMNFpoMFw = false;
      string BAAejxyYJU;
      string iZdbAbSaSM;
      string yIVFdOdUpb;
      string cGQLKrzrtU;
      string cJzESuFeiu;
      string VAnKsrdtBV;
      string SdhgqcJRRH;
      string bZfxinJRmh;
      string IykuGbRFSR;
      string OFqYByaSMp;
      string lmNaSwUpaF;
      string hLGSNUrlaO;
      string KDzzsWiHwj;
      string MqFxwUkKcK;
      string HbeMjDyYKg;
      string GoqxeinOhu;
      string NMsprqFJVr;
      string igJQHiXmPp;
      string YJwPdXzISM;
      string gWchwuhnTs;
      if(BAAejxyYJU == lmNaSwUpaF){xnCRxYeapw = true;}
      else if(lmNaSwUpaF == BAAejxyYJU){xwkaxtrUWi = true;}
      if(iZdbAbSaSM == hLGSNUrlaO){KAyrVDPdMU = true;}
      else if(hLGSNUrlaO == iZdbAbSaSM){TbmZwznhxz = true;}
      if(yIVFdOdUpb == KDzzsWiHwj){qxqILMEaTL = true;}
      else if(KDzzsWiHwj == yIVFdOdUpb){UOGFyhMdWm = true;}
      if(cGQLKrzrtU == MqFxwUkKcK){AiSWrjHdRE = true;}
      else if(MqFxwUkKcK == cGQLKrzrtU){Cqtfhriocl = true;}
      if(cJzESuFeiu == HbeMjDyYKg){rXRVCfXkLs = true;}
      else if(HbeMjDyYKg == cJzESuFeiu){ElwlYKaxkj = true;}
      if(VAnKsrdtBV == GoqxeinOhu){eEbzBzxsGk = true;}
      else if(GoqxeinOhu == VAnKsrdtBV){AhqaGioebO = true;}
      if(SdhgqcJRRH == NMsprqFJVr){TDHdubhbzk = true;}
      else if(NMsprqFJVr == SdhgqcJRRH){gNxifcgGrD = true;}
      if(bZfxinJRmh == igJQHiXmPp){wkLHbSeUGf = true;}
      if(IykuGbRFSR == YJwPdXzISM){nTPZfwGTUs = true;}
      if(OFqYByaSMp == gWchwuhnTs){mNXgjnPnZa = true;}
      while(igJQHiXmPp == bZfxinJRmh){QzFKthRUgm = true;}
      while(YJwPdXzISM == YJwPdXzISM){HOslmTATZz = true;}
      while(gWchwuhnTs == gWchwuhnTs){DDMNFpoMFw = true;}
      if(xnCRxYeapw == true){xnCRxYeapw = false;}
      if(KAyrVDPdMU == true){KAyrVDPdMU = false;}
      if(qxqILMEaTL == true){qxqILMEaTL = false;}
      if(AiSWrjHdRE == true){AiSWrjHdRE = false;}
      if(rXRVCfXkLs == true){rXRVCfXkLs = false;}
      if(eEbzBzxsGk == true){eEbzBzxsGk = false;}
      if(TDHdubhbzk == true){TDHdubhbzk = false;}
      if(wkLHbSeUGf == true){wkLHbSeUGf = false;}
      if(nTPZfwGTUs == true){nTPZfwGTUs = false;}
      if(mNXgjnPnZa == true){mNXgjnPnZa = false;}
      if(xwkaxtrUWi == true){xwkaxtrUWi = false;}
      if(TbmZwznhxz == true){TbmZwznhxz = false;}
      if(UOGFyhMdWm == true){UOGFyhMdWm = false;}
      if(Cqtfhriocl == true){Cqtfhriocl = false;}
      if(ElwlYKaxkj == true){ElwlYKaxkj = false;}
      if(AhqaGioebO == true){AhqaGioebO = false;}
      if(gNxifcgGrD == true){gNxifcgGrD = false;}
      if(QzFKthRUgm == true){QzFKthRUgm = false;}
      if(HOslmTATZz == true){HOslmTATZz = false;}
      if(DDMNFpoMFw == true){DDMNFpoMFw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SXMOFFFLVT
{ 
  void HuBjGgusGp()
  { 
      bool fHFqRVlUTO = false;
      bool PppNsiIPgZ = false;
      bool gyXegykGLC = false;
      bool QhDKBRqVVM = false;
      bool sgRMWzQciF = false;
      bool kECSbgiaKS = false;
      bool kfJQyglfLa = false;
      bool rlsUfAfLHg = false;
      bool hHWGRLfkhU = false;
      bool iPLDbNWBOp = false;
      bool MjRINyKglb = false;
      bool AXSckcICyl = false;
      bool ABxqrbZpsS = false;
      bool cexRTxpOsT = false;
      bool AzyGTKxiRy = false;
      bool FUCboLmZQk = false;
      bool YUnTyUaBIn = false;
      bool mtJekBDqXg = false;
      bool eqYuNIcUcI = false;
      bool KQxHufKdHy = false;
      string UqQknecsjL;
      string zCOkaVkwAE;
      string cxZzgkWgRt;
      string pBnOXWCKMz;
      string KagwJNejzU;
      string ZfOqJXRRDC;
      string HwaoVyOzNE;
      string TZjAtBPcoS;
      string GmgxTKmwFA;
      string FkGJqNzqaL;
      string zeWtBzuNwH;
      string HncjwUOdVK;
      string KRsMzhSZJg;
      string BXCcTaQmuU;
      string OYzysRHWMV;
      string yVVPBgkJuS;
      string fVDPFikAQV;
      string EbiAwlRuTh;
      string ZwMmhfClbl;
      string oGqbnsUjrJ;
      if(UqQknecsjL == zeWtBzuNwH){fHFqRVlUTO = true;}
      else if(zeWtBzuNwH == UqQknecsjL){MjRINyKglb = true;}
      if(zCOkaVkwAE == HncjwUOdVK){PppNsiIPgZ = true;}
      else if(HncjwUOdVK == zCOkaVkwAE){AXSckcICyl = true;}
      if(cxZzgkWgRt == KRsMzhSZJg){gyXegykGLC = true;}
      else if(KRsMzhSZJg == cxZzgkWgRt){ABxqrbZpsS = true;}
      if(pBnOXWCKMz == BXCcTaQmuU){QhDKBRqVVM = true;}
      else if(BXCcTaQmuU == pBnOXWCKMz){cexRTxpOsT = true;}
      if(KagwJNejzU == OYzysRHWMV){sgRMWzQciF = true;}
      else if(OYzysRHWMV == KagwJNejzU){AzyGTKxiRy = true;}
      if(ZfOqJXRRDC == yVVPBgkJuS){kECSbgiaKS = true;}
      else if(yVVPBgkJuS == ZfOqJXRRDC){FUCboLmZQk = true;}
      if(HwaoVyOzNE == fVDPFikAQV){kfJQyglfLa = true;}
      else if(fVDPFikAQV == HwaoVyOzNE){YUnTyUaBIn = true;}
      if(TZjAtBPcoS == EbiAwlRuTh){rlsUfAfLHg = true;}
      if(GmgxTKmwFA == ZwMmhfClbl){hHWGRLfkhU = true;}
      if(FkGJqNzqaL == oGqbnsUjrJ){iPLDbNWBOp = true;}
      while(EbiAwlRuTh == TZjAtBPcoS){mtJekBDqXg = true;}
      while(ZwMmhfClbl == ZwMmhfClbl){eqYuNIcUcI = true;}
      while(oGqbnsUjrJ == oGqbnsUjrJ){KQxHufKdHy = true;}
      if(fHFqRVlUTO == true){fHFqRVlUTO = false;}
      if(PppNsiIPgZ == true){PppNsiIPgZ = false;}
      if(gyXegykGLC == true){gyXegykGLC = false;}
      if(QhDKBRqVVM == true){QhDKBRqVVM = false;}
      if(sgRMWzQciF == true){sgRMWzQciF = false;}
      if(kECSbgiaKS == true){kECSbgiaKS = false;}
      if(kfJQyglfLa == true){kfJQyglfLa = false;}
      if(rlsUfAfLHg == true){rlsUfAfLHg = false;}
      if(hHWGRLfkhU == true){hHWGRLfkhU = false;}
      if(iPLDbNWBOp == true){iPLDbNWBOp = false;}
      if(MjRINyKglb == true){MjRINyKglb = false;}
      if(AXSckcICyl == true){AXSckcICyl = false;}
      if(ABxqrbZpsS == true){ABxqrbZpsS = false;}
      if(cexRTxpOsT == true){cexRTxpOsT = false;}
      if(AzyGTKxiRy == true){AzyGTKxiRy = false;}
      if(FUCboLmZQk == true){FUCboLmZQk = false;}
      if(YUnTyUaBIn == true){YUnTyUaBIn = false;}
      if(mtJekBDqXg == true){mtJekBDqXg = false;}
      if(eqYuNIcUcI == true){eqYuNIcUcI = false;}
      if(KQxHufKdHy == true){KQxHufKdHy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IWUUMZTQXL
{ 
  void HQqyBoJHmz()
  { 
      bool WRZwLaHtlZ = false;
      bool XGHdNOVxwe = false;
      bool OhPtDelLlZ = false;
      bool EYEQpOAZgx = false;
      bool qGDbmEgOWG = false;
      bool amwXAnCesf = false;
      bool ouHMUzBpny = false;
      bool OuQynHdnHz = false;
      bool xXofyRbfQB = false;
      bool MUgAIuzqGm = false;
      bool CqZXqfWxjr = false;
      bool KOXtiQGaND = false;
      bool WVZmlsOPps = false;
      bool ImgUwGxQnS = false;
      bool tewYqywmRq = false;
      bool oXcDPgRmly = false;
      bool QHGqjWgDxc = false;
      bool SoluIrYAum = false;
      bool wbxzDjJdEP = false;
      bool nKepBmYFnT = false;
      string kINDLoGMFt;
      string KFhfkfBAsR;
      string oBPidpVIom;
      string TDNdcKwKTt;
      string RFiulKKyZu;
      string jFNAQireYU;
      string TxWRaGqECa;
      string iqfzzjSTwT;
      string fXisCOpNNs;
      string SRkzaUhQUf;
      string SFuzMsYOAf;
      string QXhFnuOdPL;
      string QdpIHQFgXe;
      string CBzQAZbigI;
      string oaNhcuieKe;
      string GEBIOoPmqu;
      string nrpUdOXRFN;
      string TexGWoQIeM;
      string gZWrYyApBK;
      string KorkUxkrDO;
      if(kINDLoGMFt == SFuzMsYOAf){WRZwLaHtlZ = true;}
      else if(SFuzMsYOAf == kINDLoGMFt){CqZXqfWxjr = true;}
      if(KFhfkfBAsR == QXhFnuOdPL){XGHdNOVxwe = true;}
      else if(QXhFnuOdPL == KFhfkfBAsR){KOXtiQGaND = true;}
      if(oBPidpVIom == QdpIHQFgXe){OhPtDelLlZ = true;}
      else if(QdpIHQFgXe == oBPidpVIom){WVZmlsOPps = true;}
      if(TDNdcKwKTt == CBzQAZbigI){EYEQpOAZgx = true;}
      else if(CBzQAZbigI == TDNdcKwKTt){ImgUwGxQnS = true;}
      if(RFiulKKyZu == oaNhcuieKe){qGDbmEgOWG = true;}
      else if(oaNhcuieKe == RFiulKKyZu){tewYqywmRq = true;}
      if(jFNAQireYU == GEBIOoPmqu){amwXAnCesf = true;}
      else if(GEBIOoPmqu == jFNAQireYU){oXcDPgRmly = true;}
      if(TxWRaGqECa == nrpUdOXRFN){ouHMUzBpny = true;}
      else if(nrpUdOXRFN == TxWRaGqECa){QHGqjWgDxc = true;}
      if(iqfzzjSTwT == TexGWoQIeM){OuQynHdnHz = true;}
      if(fXisCOpNNs == gZWrYyApBK){xXofyRbfQB = true;}
      if(SRkzaUhQUf == KorkUxkrDO){MUgAIuzqGm = true;}
      while(TexGWoQIeM == iqfzzjSTwT){SoluIrYAum = true;}
      while(gZWrYyApBK == gZWrYyApBK){wbxzDjJdEP = true;}
      while(KorkUxkrDO == KorkUxkrDO){nKepBmYFnT = true;}
      if(WRZwLaHtlZ == true){WRZwLaHtlZ = false;}
      if(XGHdNOVxwe == true){XGHdNOVxwe = false;}
      if(OhPtDelLlZ == true){OhPtDelLlZ = false;}
      if(EYEQpOAZgx == true){EYEQpOAZgx = false;}
      if(qGDbmEgOWG == true){qGDbmEgOWG = false;}
      if(amwXAnCesf == true){amwXAnCesf = false;}
      if(ouHMUzBpny == true){ouHMUzBpny = false;}
      if(OuQynHdnHz == true){OuQynHdnHz = false;}
      if(xXofyRbfQB == true){xXofyRbfQB = false;}
      if(MUgAIuzqGm == true){MUgAIuzqGm = false;}
      if(CqZXqfWxjr == true){CqZXqfWxjr = false;}
      if(KOXtiQGaND == true){KOXtiQGaND = false;}
      if(WVZmlsOPps == true){WVZmlsOPps = false;}
      if(ImgUwGxQnS == true){ImgUwGxQnS = false;}
      if(tewYqywmRq == true){tewYqywmRq = false;}
      if(oXcDPgRmly == true){oXcDPgRmly = false;}
      if(QHGqjWgDxc == true){QHGqjWgDxc = false;}
      if(SoluIrYAum == true){SoluIrYAum = false;}
      if(wbxzDjJdEP == true){wbxzDjJdEP = false;}
      if(nKepBmYFnT == true){nKepBmYFnT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZONRLKAPLA
{ 
  void IlXYzJdOPp()
  { 
      bool QNXeycTNyq = false;
      bool NTquddwpdQ = false;
      bool wezpTKTXCR = false;
      bool FAnCPmMRKp = false;
      bool AqzIfMHgBi = false;
      bool arHYEkNgKn = false;
      bool JuKglNeneq = false;
      bool RdfnQFeqJH = false;
      bool CmWTpMrPyd = false;
      bool YeHVgEfSWR = false;
      bool gTBJQxMTHz = false;
      bool FWWCkWYqpY = false;
      bool UPpASlVJHL = false;
      bool YMTqZikNCs = false;
      bool zYHyYBHEkJ = false;
      bool focxxRdApe = false;
      bool aCMuasDecC = false;
      bool lLoxZwIqbR = false;
      bool eRYxfjjWtI = false;
      bool FkWXRxLLXf = false;
      string xTMrwtyWuo;
      string NiNauJPFpo;
      string gFVBsmttDT;
      string usiGeJDlSM;
      string ZEznVYHxoz;
      string kItGEqyKzJ;
      string ADSbsUAGul;
      string GdldOcGgfT;
      string ewFEimybCn;
      string LrlJLWlWtA;
      string YBCCsGVQqb;
      string kQeedDyOsG;
      string VXEHaNqcRr;
      string qileuctCKb;
      string QhkaCtNHeI;
      string YWdneAxuae;
      string OszykBdzjA;
      string JuDQonmdEf;
      string AjxITTEyAt;
      string fybfNXiloB;
      if(xTMrwtyWuo == YBCCsGVQqb){QNXeycTNyq = true;}
      else if(YBCCsGVQqb == xTMrwtyWuo){gTBJQxMTHz = true;}
      if(NiNauJPFpo == kQeedDyOsG){NTquddwpdQ = true;}
      else if(kQeedDyOsG == NiNauJPFpo){FWWCkWYqpY = true;}
      if(gFVBsmttDT == VXEHaNqcRr){wezpTKTXCR = true;}
      else if(VXEHaNqcRr == gFVBsmttDT){UPpASlVJHL = true;}
      if(usiGeJDlSM == qileuctCKb){FAnCPmMRKp = true;}
      else if(qileuctCKb == usiGeJDlSM){YMTqZikNCs = true;}
      if(ZEznVYHxoz == QhkaCtNHeI){AqzIfMHgBi = true;}
      else if(QhkaCtNHeI == ZEznVYHxoz){zYHyYBHEkJ = true;}
      if(kItGEqyKzJ == YWdneAxuae){arHYEkNgKn = true;}
      else if(YWdneAxuae == kItGEqyKzJ){focxxRdApe = true;}
      if(ADSbsUAGul == OszykBdzjA){JuKglNeneq = true;}
      else if(OszykBdzjA == ADSbsUAGul){aCMuasDecC = true;}
      if(GdldOcGgfT == JuDQonmdEf){RdfnQFeqJH = true;}
      if(ewFEimybCn == AjxITTEyAt){CmWTpMrPyd = true;}
      if(LrlJLWlWtA == fybfNXiloB){YeHVgEfSWR = true;}
      while(JuDQonmdEf == GdldOcGgfT){lLoxZwIqbR = true;}
      while(AjxITTEyAt == AjxITTEyAt){eRYxfjjWtI = true;}
      while(fybfNXiloB == fybfNXiloB){FkWXRxLLXf = true;}
      if(QNXeycTNyq == true){QNXeycTNyq = false;}
      if(NTquddwpdQ == true){NTquddwpdQ = false;}
      if(wezpTKTXCR == true){wezpTKTXCR = false;}
      if(FAnCPmMRKp == true){FAnCPmMRKp = false;}
      if(AqzIfMHgBi == true){AqzIfMHgBi = false;}
      if(arHYEkNgKn == true){arHYEkNgKn = false;}
      if(JuKglNeneq == true){JuKglNeneq = false;}
      if(RdfnQFeqJH == true){RdfnQFeqJH = false;}
      if(CmWTpMrPyd == true){CmWTpMrPyd = false;}
      if(YeHVgEfSWR == true){YeHVgEfSWR = false;}
      if(gTBJQxMTHz == true){gTBJQxMTHz = false;}
      if(FWWCkWYqpY == true){FWWCkWYqpY = false;}
      if(UPpASlVJHL == true){UPpASlVJHL = false;}
      if(YMTqZikNCs == true){YMTqZikNCs = false;}
      if(zYHyYBHEkJ == true){zYHyYBHEkJ = false;}
      if(focxxRdApe == true){focxxRdApe = false;}
      if(aCMuasDecC == true){aCMuasDecC = false;}
      if(lLoxZwIqbR == true){lLoxZwIqbR = false;}
      if(eRYxfjjWtI == true){eRYxfjjWtI = false;}
      if(FkWXRxLLXf == true){FkWXRxLLXf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PCQUEQVVLM
{ 
  void emJqRGNDfS()
  { 
      bool orJLVHZetb = false;
      bool tayxqQVAjg = false;
      bool hKhyOWlsPV = false;
      bool zBKEMqmEtG = false;
      bool nqZCXkrHYG = false;
      bool yNZtSdJKwy = false;
      bool VfPXbsQtjA = false;
      bool dQGdrpkead = false;
      bool edUIXkaPki = false;
      bool gbIujIaBae = false;
      bool TxXYchHwCc = false;
      bool sdjSTqLHAq = false;
      bool RBJBSBIKsj = false;
      bool OiEwJgGwep = false;
      bool ddMIoDrpbs = false;
      bool wTBiMSnVFa = false;
      bool YwDSNJYnIl = false;
      bool jPbJMmnALO = false;
      bool JSizmugUip = false;
      bool sjpEQgattf = false;
      string BbXBjswMzS;
      string shKizLqdwe;
      string ZZHhNmeXDA;
      string cCrnZYfDkF;
      string TrrWaPrWxu;
      string ahGWYaUpmw;
      string OXIzppoWIa;
      string enrpKghkGy;
      string uHaHYtwUOy;
      string EoPopwjsfk;
      string ZUNVQloQMr;
      string sjioBHwAZu;
      string tUHKWoXDzN;
      string xoEVXZtEql;
      string FeIVFUFami;
      string ziSjpFMDza;
      string OkQyuEeNQb;
      string NqJmpOLlFC;
      string ixPPONWTeR;
      string MpFPXTOKaA;
      if(BbXBjswMzS == ZUNVQloQMr){orJLVHZetb = true;}
      else if(ZUNVQloQMr == BbXBjswMzS){TxXYchHwCc = true;}
      if(shKizLqdwe == sjioBHwAZu){tayxqQVAjg = true;}
      else if(sjioBHwAZu == shKizLqdwe){sdjSTqLHAq = true;}
      if(ZZHhNmeXDA == tUHKWoXDzN){hKhyOWlsPV = true;}
      else if(tUHKWoXDzN == ZZHhNmeXDA){RBJBSBIKsj = true;}
      if(cCrnZYfDkF == xoEVXZtEql){zBKEMqmEtG = true;}
      else if(xoEVXZtEql == cCrnZYfDkF){OiEwJgGwep = true;}
      if(TrrWaPrWxu == FeIVFUFami){nqZCXkrHYG = true;}
      else if(FeIVFUFami == TrrWaPrWxu){ddMIoDrpbs = true;}
      if(ahGWYaUpmw == ziSjpFMDza){yNZtSdJKwy = true;}
      else if(ziSjpFMDza == ahGWYaUpmw){wTBiMSnVFa = true;}
      if(OXIzppoWIa == OkQyuEeNQb){VfPXbsQtjA = true;}
      else if(OkQyuEeNQb == OXIzppoWIa){YwDSNJYnIl = true;}
      if(enrpKghkGy == NqJmpOLlFC){dQGdrpkead = true;}
      if(uHaHYtwUOy == ixPPONWTeR){edUIXkaPki = true;}
      if(EoPopwjsfk == MpFPXTOKaA){gbIujIaBae = true;}
      while(NqJmpOLlFC == enrpKghkGy){jPbJMmnALO = true;}
      while(ixPPONWTeR == ixPPONWTeR){JSizmugUip = true;}
      while(MpFPXTOKaA == MpFPXTOKaA){sjpEQgattf = true;}
      if(orJLVHZetb == true){orJLVHZetb = false;}
      if(tayxqQVAjg == true){tayxqQVAjg = false;}
      if(hKhyOWlsPV == true){hKhyOWlsPV = false;}
      if(zBKEMqmEtG == true){zBKEMqmEtG = false;}
      if(nqZCXkrHYG == true){nqZCXkrHYG = false;}
      if(yNZtSdJKwy == true){yNZtSdJKwy = false;}
      if(VfPXbsQtjA == true){VfPXbsQtjA = false;}
      if(dQGdrpkead == true){dQGdrpkead = false;}
      if(edUIXkaPki == true){edUIXkaPki = false;}
      if(gbIujIaBae == true){gbIujIaBae = false;}
      if(TxXYchHwCc == true){TxXYchHwCc = false;}
      if(sdjSTqLHAq == true){sdjSTqLHAq = false;}
      if(RBJBSBIKsj == true){RBJBSBIKsj = false;}
      if(OiEwJgGwep == true){OiEwJgGwep = false;}
      if(ddMIoDrpbs == true){ddMIoDrpbs = false;}
      if(wTBiMSnVFa == true){wTBiMSnVFa = false;}
      if(YwDSNJYnIl == true){YwDSNJYnIl = false;}
      if(jPbJMmnALO == true){jPbJMmnALO = false;}
      if(JSizmugUip == true){JSizmugUip = false;}
      if(sjpEQgattf == true){sjpEQgattf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NVZEADKUPL
{ 
  void pVDWlbwNxU()
  { 
      bool lUBpbmMDfR = false;
      bool GIoigTyeaP = false;
      bool TQCYfejMUh = false;
      bool pNJahTEfXa = false;
      bool PzuSlktRon = false;
      bool gxffhUSbKw = false;
      bool DAhxaszOBM = false;
      bool ORGAATVimt = false;
      bool jRXgAsgcsM = false;
      bool BbVbXPQxqr = false;
      bool kfQbYOpffN = false;
      bool yioPLkbBwg = false;
      bool LVUnLlwebk = false;
      bool DYrtJEAuHk = false;
      bool CBwfNRmFPl = false;
      bool mOAJgPKcQl = false;
      bool SLDuJZquGH = false;
      bool kftLeJYoZt = false;
      bool zqOpxoXhMt = false;
      bool sXeUSpxBVn = false;
      string oxbRgwrcHa;
      string ICXdQKriBP;
      string ILIqKfKuoN;
      string CFGVEdzMyx;
      string MKlgNrMpod;
      string erafOdnkGB;
      string lxmtYDuCZm;
      string KfjDCxZbdS;
      string STGLhJdaGa;
      string oOGxKPXqIJ;
      string xKQBSzIXcR;
      string DLGmhSpbLO;
      string YTuyxwYmrm;
      string YhTUVICEri;
      string BGxoWdHSPr;
      string YwfsjcORDV;
      string ZVeprVqlRY;
      string PkicNSVGbT;
      string oGWAOcCajr;
      string sjBVIfbHwB;
      if(oxbRgwrcHa == xKQBSzIXcR){lUBpbmMDfR = true;}
      else if(xKQBSzIXcR == oxbRgwrcHa){kfQbYOpffN = true;}
      if(ICXdQKriBP == DLGmhSpbLO){GIoigTyeaP = true;}
      else if(DLGmhSpbLO == ICXdQKriBP){yioPLkbBwg = true;}
      if(ILIqKfKuoN == YTuyxwYmrm){TQCYfejMUh = true;}
      else if(YTuyxwYmrm == ILIqKfKuoN){LVUnLlwebk = true;}
      if(CFGVEdzMyx == YhTUVICEri){pNJahTEfXa = true;}
      else if(YhTUVICEri == CFGVEdzMyx){DYrtJEAuHk = true;}
      if(MKlgNrMpod == BGxoWdHSPr){PzuSlktRon = true;}
      else if(BGxoWdHSPr == MKlgNrMpod){CBwfNRmFPl = true;}
      if(erafOdnkGB == YwfsjcORDV){gxffhUSbKw = true;}
      else if(YwfsjcORDV == erafOdnkGB){mOAJgPKcQl = true;}
      if(lxmtYDuCZm == ZVeprVqlRY){DAhxaszOBM = true;}
      else if(ZVeprVqlRY == lxmtYDuCZm){SLDuJZquGH = true;}
      if(KfjDCxZbdS == PkicNSVGbT){ORGAATVimt = true;}
      if(STGLhJdaGa == oGWAOcCajr){jRXgAsgcsM = true;}
      if(oOGxKPXqIJ == sjBVIfbHwB){BbVbXPQxqr = true;}
      while(PkicNSVGbT == KfjDCxZbdS){kftLeJYoZt = true;}
      while(oGWAOcCajr == oGWAOcCajr){zqOpxoXhMt = true;}
      while(sjBVIfbHwB == sjBVIfbHwB){sXeUSpxBVn = true;}
      if(lUBpbmMDfR == true){lUBpbmMDfR = false;}
      if(GIoigTyeaP == true){GIoigTyeaP = false;}
      if(TQCYfejMUh == true){TQCYfejMUh = false;}
      if(pNJahTEfXa == true){pNJahTEfXa = false;}
      if(PzuSlktRon == true){PzuSlktRon = false;}
      if(gxffhUSbKw == true){gxffhUSbKw = false;}
      if(DAhxaszOBM == true){DAhxaszOBM = false;}
      if(ORGAATVimt == true){ORGAATVimt = false;}
      if(jRXgAsgcsM == true){jRXgAsgcsM = false;}
      if(BbVbXPQxqr == true){BbVbXPQxqr = false;}
      if(kfQbYOpffN == true){kfQbYOpffN = false;}
      if(yioPLkbBwg == true){yioPLkbBwg = false;}
      if(LVUnLlwebk == true){LVUnLlwebk = false;}
      if(DYrtJEAuHk == true){DYrtJEAuHk = false;}
      if(CBwfNRmFPl == true){CBwfNRmFPl = false;}
      if(mOAJgPKcQl == true){mOAJgPKcQl = false;}
      if(SLDuJZquGH == true){SLDuJZquGH = false;}
      if(kftLeJYoZt == true){kftLeJYoZt = false;}
      if(zqOpxoXhMt == true){zqOpxoXhMt = false;}
      if(sXeUSpxBVn == true){sXeUSpxBVn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OQRDRZSPBC
{ 
  void nqTrrCCkwM()
  { 
      bool IMwUXLfopu = false;
      bool exJZmQfjjM = false;
      bool UFhlStUHYR = false;
      bool rYiuJVDkTj = false;
      bool FqtnPdGnHk = false;
      bool xRQnxCeJBc = false;
      bool qXQXDFNNQR = false;
      bool MtQzGcLtWo = false;
      bool ngAnUZHtyG = false;
      bool psipshaVjJ = false;
      bool PrWoXCBQhT = false;
      bool qkmMoJWcDc = false;
      bool yTPJaSLZGX = false;
      bool CoJNYuJKPR = false;
      bool YqLdPFGVBi = false;
      bool KxRGLucNNE = false;
      bool qaJJRBbYms = false;
      bool ALNlEGHlsV = false;
      bool MoYXNEXCCc = false;
      bool SuwKZxgCMN = false;
      string SghQPFDnpr;
      string wIIeSdiYlR;
      string xOzFboJyRn;
      string KqAHZqxxod;
      string pYJeSSQNiQ;
      string doKxpEgcoZ;
      string uFVBgEIAFa;
      string gkjIbXEUmJ;
      string YwPBJVfCRU;
      string KTIPhkDHxN;
      string KQHIirFCVS;
      string zMpfBzpUqL;
      string XFijPMcTZp;
      string UxWYyHnGRR;
      string PdfzUydcNi;
      string uiPloEgXrW;
      string PlbeyCpQgs;
      string KiDZutZjOR;
      string izFqukgjit;
      string aPOuBdCABS;
      if(SghQPFDnpr == KQHIirFCVS){IMwUXLfopu = true;}
      else if(KQHIirFCVS == SghQPFDnpr){PrWoXCBQhT = true;}
      if(wIIeSdiYlR == zMpfBzpUqL){exJZmQfjjM = true;}
      else if(zMpfBzpUqL == wIIeSdiYlR){qkmMoJWcDc = true;}
      if(xOzFboJyRn == XFijPMcTZp){UFhlStUHYR = true;}
      else if(XFijPMcTZp == xOzFboJyRn){yTPJaSLZGX = true;}
      if(KqAHZqxxod == UxWYyHnGRR){rYiuJVDkTj = true;}
      else if(UxWYyHnGRR == KqAHZqxxod){CoJNYuJKPR = true;}
      if(pYJeSSQNiQ == PdfzUydcNi){FqtnPdGnHk = true;}
      else if(PdfzUydcNi == pYJeSSQNiQ){YqLdPFGVBi = true;}
      if(doKxpEgcoZ == uiPloEgXrW){xRQnxCeJBc = true;}
      else if(uiPloEgXrW == doKxpEgcoZ){KxRGLucNNE = true;}
      if(uFVBgEIAFa == PlbeyCpQgs){qXQXDFNNQR = true;}
      else if(PlbeyCpQgs == uFVBgEIAFa){qaJJRBbYms = true;}
      if(gkjIbXEUmJ == KiDZutZjOR){MtQzGcLtWo = true;}
      if(YwPBJVfCRU == izFqukgjit){ngAnUZHtyG = true;}
      if(KTIPhkDHxN == aPOuBdCABS){psipshaVjJ = true;}
      while(KiDZutZjOR == gkjIbXEUmJ){ALNlEGHlsV = true;}
      while(izFqukgjit == izFqukgjit){MoYXNEXCCc = true;}
      while(aPOuBdCABS == aPOuBdCABS){SuwKZxgCMN = true;}
      if(IMwUXLfopu == true){IMwUXLfopu = false;}
      if(exJZmQfjjM == true){exJZmQfjjM = false;}
      if(UFhlStUHYR == true){UFhlStUHYR = false;}
      if(rYiuJVDkTj == true){rYiuJVDkTj = false;}
      if(FqtnPdGnHk == true){FqtnPdGnHk = false;}
      if(xRQnxCeJBc == true){xRQnxCeJBc = false;}
      if(qXQXDFNNQR == true){qXQXDFNNQR = false;}
      if(MtQzGcLtWo == true){MtQzGcLtWo = false;}
      if(ngAnUZHtyG == true){ngAnUZHtyG = false;}
      if(psipshaVjJ == true){psipshaVjJ = false;}
      if(PrWoXCBQhT == true){PrWoXCBQhT = false;}
      if(qkmMoJWcDc == true){qkmMoJWcDc = false;}
      if(yTPJaSLZGX == true){yTPJaSLZGX = false;}
      if(CoJNYuJKPR == true){CoJNYuJKPR = false;}
      if(YqLdPFGVBi == true){YqLdPFGVBi = false;}
      if(KxRGLucNNE == true){KxRGLucNNE = false;}
      if(qaJJRBbYms == true){qaJJRBbYms = false;}
      if(ALNlEGHlsV == true){ALNlEGHlsV = false;}
      if(MoYXNEXCCc == true){MoYXNEXCCc = false;}
      if(SuwKZxgCMN == true){SuwKZxgCMN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WQBMRHSJDU
{ 
  void ejCqzgsGdJ()
  { 
      bool nUlDfMVJhY = false;
      bool jaOBFebrmg = false;
      bool zUCBxaHiOV = false;
      bool nARTpubpOi = false;
      bool dfwjTezRqo = false;
      bool YduGaTSkFF = false;
      bool EltLkjJuLK = false;
      bool DkcDDTXRgR = false;
      bool aorZxJFKrV = false;
      bool cqjJdqlkzj = false;
      bool VEGflmAqDH = false;
      bool wADndPtUNa = false;
      bool ezCohMBTZL = false;
      bool glSxuWhMnJ = false;
      bool JOGkZbmwfO = false;
      bool xRXXEWBRxY = false;
      bool lgQrZJhGrH = false;
      bool ggfDRQrROG = false;
      bool YEmKNPOtrY = false;
      bool UQOOXbxOKP = false;
      string eaSMSaRaxB;
      string qrXqYSLmrw;
      string seMVtfRnok;
      string QNGsojillr;
      string tnDgcDlXnC;
      string XXCVnANxSl;
      string IclLkckeBo;
      string iYBzBEaerp;
      string ttAlMrLkEo;
      string VlTziRCrwA;
      string SHVzSyWCTi;
      string YhEbqNczyr;
      string RzZLSxFBPj;
      string CiirWmYASO;
      string VIRUQngqHV;
      string nCsEhSgJgV;
      string sUligozMFE;
      string obfjWJhFue;
      string PNstuzoeJE;
      string GOTxUAVhna;
      if(eaSMSaRaxB == SHVzSyWCTi){nUlDfMVJhY = true;}
      else if(SHVzSyWCTi == eaSMSaRaxB){VEGflmAqDH = true;}
      if(qrXqYSLmrw == YhEbqNczyr){jaOBFebrmg = true;}
      else if(YhEbqNczyr == qrXqYSLmrw){wADndPtUNa = true;}
      if(seMVtfRnok == RzZLSxFBPj){zUCBxaHiOV = true;}
      else if(RzZLSxFBPj == seMVtfRnok){ezCohMBTZL = true;}
      if(QNGsojillr == CiirWmYASO){nARTpubpOi = true;}
      else if(CiirWmYASO == QNGsojillr){glSxuWhMnJ = true;}
      if(tnDgcDlXnC == VIRUQngqHV){dfwjTezRqo = true;}
      else if(VIRUQngqHV == tnDgcDlXnC){JOGkZbmwfO = true;}
      if(XXCVnANxSl == nCsEhSgJgV){YduGaTSkFF = true;}
      else if(nCsEhSgJgV == XXCVnANxSl){xRXXEWBRxY = true;}
      if(IclLkckeBo == sUligozMFE){EltLkjJuLK = true;}
      else if(sUligozMFE == IclLkckeBo){lgQrZJhGrH = true;}
      if(iYBzBEaerp == obfjWJhFue){DkcDDTXRgR = true;}
      if(ttAlMrLkEo == PNstuzoeJE){aorZxJFKrV = true;}
      if(VlTziRCrwA == GOTxUAVhna){cqjJdqlkzj = true;}
      while(obfjWJhFue == iYBzBEaerp){ggfDRQrROG = true;}
      while(PNstuzoeJE == PNstuzoeJE){YEmKNPOtrY = true;}
      while(GOTxUAVhna == GOTxUAVhna){UQOOXbxOKP = true;}
      if(nUlDfMVJhY == true){nUlDfMVJhY = false;}
      if(jaOBFebrmg == true){jaOBFebrmg = false;}
      if(zUCBxaHiOV == true){zUCBxaHiOV = false;}
      if(nARTpubpOi == true){nARTpubpOi = false;}
      if(dfwjTezRqo == true){dfwjTezRqo = false;}
      if(YduGaTSkFF == true){YduGaTSkFF = false;}
      if(EltLkjJuLK == true){EltLkjJuLK = false;}
      if(DkcDDTXRgR == true){DkcDDTXRgR = false;}
      if(aorZxJFKrV == true){aorZxJFKrV = false;}
      if(cqjJdqlkzj == true){cqjJdqlkzj = false;}
      if(VEGflmAqDH == true){VEGflmAqDH = false;}
      if(wADndPtUNa == true){wADndPtUNa = false;}
      if(ezCohMBTZL == true){ezCohMBTZL = false;}
      if(glSxuWhMnJ == true){glSxuWhMnJ = false;}
      if(JOGkZbmwfO == true){JOGkZbmwfO = false;}
      if(xRXXEWBRxY == true){xRXXEWBRxY = false;}
      if(lgQrZJhGrH == true){lgQrZJhGrH = false;}
      if(ggfDRQrROG == true){ggfDRQrROG = false;}
      if(YEmKNPOtrY == true){YEmKNPOtrY = false;}
      if(UQOOXbxOKP == true){UQOOXbxOKP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XMTXROYQSP
{ 
  void RnIEBHwyrP()
  { 
      bool VntMXPjbkt = false;
      bool sBCTKdEqKj = false;
      bool gicGYYKtkU = false;
      bool rbijoWtRmA = false;
      bool giNTkBJDnA = false;
      bool tckIrlLmmy = false;
      bool EpqQBRSRdm = false;
      bool ilEKCyUIUW = false;
      bool PHFjZPpZqD = false;
      bool LGenwqqxRT = false;
      bool iqYAQIXaGs = false;
      bool RDRPixjGpl = false;
      bool brZabbHPNK = false;
      bool GXqBnXhFSR = false;
      bool rOTylHoOFz = false;
      bool HjGfqpQyYo = false;
      bool AHNulsMPbK = false;
      bool PenYtMYboT = false;
      bool msKODWQKJx = false;
      bool HifdQjBXLr = false;
      string HQuhpyrfzA;
      string YVwCEpqKQa;
      string kFNamyhFeE;
      string JyIfOuJIqg;
      string YuyzQaQYFt;
      string UWFsnBCUtr;
      string QmAupaMPmJ;
      string ghSjBpGOJL;
      string hIzjimrPrM;
      string roOzQltDIo;
      string OAlwNlDVqx;
      string unKiJHmPLD;
      string iwWaQqTTTP;
      string wCFTxgWDVw;
      string iWXtREefoI;
      string zdqFGRdKfW;
      string RiCbBripkc;
      string kisOTMXbIL;
      string LneKQRLzNe;
      string DLXzdzTwsY;
      if(HQuhpyrfzA == OAlwNlDVqx){VntMXPjbkt = true;}
      else if(OAlwNlDVqx == HQuhpyrfzA){iqYAQIXaGs = true;}
      if(YVwCEpqKQa == unKiJHmPLD){sBCTKdEqKj = true;}
      else if(unKiJHmPLD == YVwCEpqKQa){RDRPixjGpl = true;}
      if(kFNamyhFeE == iwWaQqTTTP){gicGYYKtkU = true;}
      else if(iwWaQqTTTP == kFNamyhFeE){brZabbHPNK = true;}
      if(JyIfOuJIqg == wCFTxgWDVw){rbijoWtRmA = true;}
      else if(wCFTxgWDVw == JyIfOuJIqg){GXqBnXhFSR = true;}
      if(YuyzQaQYFt == iWXtREefoI){giNTkBJDnA = true;}
      else if(iWXtREefoI == YuyzQaQYFt){rOTylHoOFz = true;}
      if(UWFsnBCUtr == zdqFGRdKfW){tckIrlLmmy = true;}
      else if(zdqFGRdKfW == UWFsnBCUtr){HjGfqpQyYo = true;}
      if(QmAupaMPmJ == RiCbBripkc){EpqQBRSRdm = true;}
      else if(RiCbBripkc == QmAupaMPmJ){AHNulsMPbK = true;}
      if(ghSjBpGOJL == kisOTMXbIL){ilEKCyUIUW = true;}
      if(hIzjimrPrM == LneKQRLzNe){PHFjZPpZqD = true;}
      if(roOzQltDIo == DLXzdzTwsY){LGenwqqxRT = true;}
      while(kisOTMXbIL == ghSjBpGOJL){PenYtMYboT = true;}
      while(LneKQRLzNe == LneKQRLzNe){msKODWQKJx = true;}
      while(DLXzdzTwsY == DLXzdzTwsY){HifdQjBXLr = true;}
      if(VntMXPjbkt == true){VntMXPjbkt = false;}
      if(sBCTKdEqKj == true){sBCTKdEqKj = false;}
      if(gicGYYKtkU == true){gicGYYKtkU = false;}
      if(rbijoWtRmA == true){rbijoWtRmA = false;}
      if(giNTkBJDnA == true){giNTkBJDnA = false;}
      if(tckIrlLmmy == true){tckIrlLmmy = false;}
      if(EpqQBRSRdm == true){EpqQBRSRdm = false;}
      if(ilEKCyUIUW == true){ilEKCyUIUW = false;}
      if(PHFjZPpZqD == true){PHFjZPpZqD = false;}
      if(LGenwqqxRT == true){LGenwqqxRT = false;}
      if(iqYAQIXaGs == true){iqYAQIXaGs = false;}
      if(RDRPixjGpl == true){RDRPixjGpl = false;}
      if(brZabbHPNK == true){brZabbHPNK = false;}
      if(GXqBnXhFSR == true){GXqBnXhFSR = false;}
      if(rOTylHoOFz == true){rOTylHoOFz = false;}
      if(HjGfqpQyYo == true){HjGfqpQyYo = false;}
      if(AHNulsMPbK == true){AHNulsMPbK = false;}
      if(PenYtMYboT == true){PenYtMYboT = false;}
      if(msKODWQKJx == true){msKODWQKJx = false;}
      if(HifdQjBXLr == true){HifdQjBXLr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XOFYGREHNW
{ 
  void IzQxlklnoe()
  { 
      bool jiUMxOtInB = false;
      bool hLkKTuLXqF = false;
      bool wNyXlDRrZx = false;
      bool eHYYJXiaEs = false;
      bool ZMRjoJlknW = false;
      bool nmKKbWjwZs = false;
      bool xCiqWamLBu = false;
      bool LkTyejuNhc = false;
      bool RgDCIqxOwl = false;
      bool nmAKwXdaNO = false;
      bool WaisLDTLfr = false;
      bool aVOxbQzfhe = false;
      bool cXPOGYjIBH = false;
      bool FTATFpxJqE = false;
      bool XkiDKRXCif = false;
      bool XxshkyKUll = false;
      bool SLKXmHVuqk = false;
      bool SoocHroLDo = false;
      bool AhZViHaRhH = false;
      bool fcXEkMaKQD = false;
      string XAmCZsfPER;
      string hwZkTBGkAf;
      string rwLbWseQuF;
      string QUyPKFsIeT;
      string FyLjfCpzPK;
      string SLhLjbnKfg;
      string NOUyBNyKZN;
      string IxFgatkbwT;
      string CfBkmElmfi;
      string QhcyGpdMiS;
      string DfZBBUFBjp;
      string qMOLdgNiLw;
      string aLepxaUHaj;
      string PXsdPWGAiS;
      string ykCprDTQTY;
      string btBlqrAiEa;
      string zyZAZSTkuH;
      string aNArxpJoys;
      string HEmCIUVGlX;
      string VWuISAKCPY;
      if(XAmCZsfPER == DfZBBUFBjp){jiUMxOtInB = true;}
      else if(DfZBBUFBjp == XAmCZsfPER){WaisLDTLfr = true;}
      if(hwZkTBGkAf == qMOLdgNiLw){hLkKTuLXqF = true;}
      else if(qMOLdgNiLw == hwZkTBGkAf){aVOxbQzfhe = true;}
      if(rwLbWseQuF == aLepxaUHaj){wNyXlDRrZx = true;}
      else if(aLepxaUHaj == rwLbWseQuF){cXPOGYjIBH = true;}
      if(QUyPKFsIeT == PXsdPWGAiS){eHYYJXiaEs = true;}
      else if(PXsdPWGAiS == QUyPKFsIeT){FTATFpxJqE = true;}
      if(FyLjfCpzPK == ykCprDTQTY){ZMRjoJlknW = true;}
      else if(ykCprDTQTY == FyLjfCpzPK){XkiDKRXCif = true;}
      if(SLhLjbnKfg == btBlqrAiEa){nmKKbWjwZs = true;}
      else if(btBlqrAiEa == SLhLjbnKfg){XxshkyKUll = true;}
      if(NOUyBNyKZN == zyZAZSTkuH){xCiqWamLBu = true;}
      else if(zyZAZSTkuH == NOUyBNyKZN){SLKXmHVuqk = true;}
      if(IxFgatkbwT == aNArxpJoys){LkTyejuNhc = true;}
      if(CfBkmElmfi == HEmCIUVGlX){RgDCIqxOwl = true;}
      if(QhcyGpdMiS == VWuISAKCPY){nmAKwXdaNO = true;}
      while(aNArxpJoys == IxFgatkbwT){SoocHroLDo = true;}
      while(HEmCIUVGlX == HEmCIUVGlX){AhZViHaRhH = true;}
      while(VWuISAKCPY == VWuISAKCPY){fcXEkMaKQD = true;}
      if(jiUMxOtInB == true){jiUMxOtInB = false;}
      if(hLkKTuLXqF == true){hLkKTuLXqF = false;}
      if(wNyXlDRrZx == true){wNyXlDRrZx = false;}
      if(eHYYJXiaEs == true){eHYYJXiaEs = false;}
      if(ZMRjoJlknW == true){ZMRjoJlknW = false;}
      if(nmKKbWjwZs == true){nmKKbWjwZs = false;}
      if(xCiqWamLBu == true){xCiqWamLBu = false;}
      if(LkTyejuNhc == true){LkTyejuNhc = false;}
      if(RgDCIqxOwl == true){RgDCIqxOwl = false;}
      if(nmAKwXdaNO == true){nmAKwXdaNO = false;}
      if(WaisLDTLfr == true){WaisLDTLfr = false;}
      if(aVOxbQzfhe == true){aVOxbQzfhe = false;}
      if(cXPOGYjIBH == true){cXPOGYjIBH = false;}
      if(FTATFpxJqE == true){FTATFpxJqE = false;}
      if(XkiDKRXCif == true){XkiDKRXCif = false;}
      if(XxshkyKUll == true){XxshkyKUll = false;}
      if(SLKXmHVuqk == true){SLKXmHVuqk = false;}
      if(SoocHroLDo == true){SoocHroLDo = false;}
      if(AhZViHaRhH == true){AhZViHaRhH = false;}
      if(fcXEkMaKQD == true){fcXEkMaKQD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QLWVZBYTBR
{ 
  void WZhjsZEuoR()
  { 
      bool ZfLJmLnTVB = false;
      bool RalsrVRRDJ = false;
      bool uUnsdafhZT = false;
      bool aZOcpsScNf = false;
      bool faEGcxSWoG = false;
      bool COdPEFrSfL = false;
      bool eGsBaqMJCz = false;
      bool DoDWdUQgPf = false;
      bool HJsSRLwzXk = false;
      bool AAwBBZgCfk = false;
      bool jJUpDNKGkj = false;
      bool nKDzEVMZjP = false;
      bool uNkRyDrCVE = false;
      bool mNBduyoDPD = false;
      bool AoNmwpwwxf = false;
      bool MHSQpWXCrA = false;
      bool UIkgxaIYEF = false;
      bool gJKfOGzyUH = false;
      bool GuEorfuknY = false;
      bool alKPhrDgpV = false;
      string ITmumMDIZh;
      string HLAGadnsKJ;
      string oYdqEBIGcf;
      string nNABjokApW;
      string cyATKWGFiL;
      string UIabtioupl;
      string DwftttKzVl;
      string rnDmfqYJgg;
      string uDXRLemYHB;
      string zpJDSfSGZP;
      string LGiwSfFmuD;
      string JeNJqAXNhO;
      string GlqUlBezTz;
      string YSjQUnTaye;
      string ZzcDqUcAMS;
      string IEXKIZPOKQ;
      string BFSudqtwnC;
      string fxPDoHIncQ;
      string YemBqUuZIu;
      string YEQgcUghYA;
      if(ITmumMDIZh == LGiwSfFmuD){ZfLJmLnTVB = true;}
      else if(LGiwSfFmuD == ITmumMDIZh){jJUpDNKGkj = true;}
      if(HLAGadnsKJ == JeNJqAXNhO){RalsrVRRDJ = true;}
      else if(JeNJqAXNhO == HLAGadnsKJ){nKDzEVMZjP = true;}
      if(oYdqEBIGcf == GlqUlBezTz){uUnsdafhZT = true;}
      else if(GlqUlBezTz == oYdqEBIGcf){uNkRyDrCVE = true;}
      if(nNABjokApW == YSjQUnTaye){aZOcpsScNf = true;}
      else if(YSjQUnTaye == nNABjokApW){mNBduyoDPD = true;}
      if(cyATKWGFiL == ZzcDqUcAMS){faEGcxSWoG = true;}
      else if(ZzcDqUcAMS == cyATKWGFiL){AoNmwpwwxf = true;}
      if(UIabtioupl == IEXKIZPOKQ){COdPEFrSfL = true;}
      else if(IEXKIZPOKQ == UIabtioupl){MHSQpWXCrA = true;}
      if(DwftttKzVl == BFSudqtwnC){eGsBaqMJCz = true;}
      else if(BFSudqtwnC == DwftttKzVl){UIkgxaIYEF = true;}
      if(rnDmfqYJgg == fxPDoHIncQ){DoDWdUQgPf = true;}
      if(uDXRLemYHB == YemBqUuZIu){HJsSRLwzXk = true;}
      if(zpJDSfSGZP == YEQgcUghYA){AAwBBZgCfk = true;}
      while(fxPDoHIncQ == rnDmfqYJgg){gJKfOGzyUH = true;}
      while(YemBqUuZIu == YemBqUuZIu){GuEorfuknY = true;}
      while(YEQgcUghYA == YEQgcUghYA){alKPhrDgpV = true;}
      if(ZfLJmLnTVB == true){ZfLJmLnTVB = false;}
      if(RalsrVRRDJ == true){RalsrVRRDJ = false;}
      if(uUnsdafhZT == true){uUnsdafhZT = false;}
      if(aZOcpsScNf == true){aZOcpsScNf = false;}
      if(faEGcxSWoG == true){faEGcxSWoG = false;}
      if(COdPEFrSfL == true){COdPEFrSfL = false;}
      if(eGsBaqMJCz == true){eGsBaqMJCz = false;}
      if(DoDWdUQgPf == true){DoDWdUQgPf = false;}
      if(HJsSRLwzXk == true){HJsSRLwzXk = false;}
      if(AAwBBZgCfk == true){AAwBBZgCfk = false;}
      if(jJUpDNKGkj == true){jJUpDNKGkj = false;}
      if(nKDzEVMZjP == true){nKDzEVMZjP = false;}
      if(uNkRyDrCVE == true){uNkRyDrCVE = false;}
      if(mNBduyoDPD == true){mNBduyoDPD = false;}
      if(AoNmwpwwxf == true){AoNmwpwwxf = false;}
      if(MHSQpWXCrA == true){MHSQpWXCrA = false;}
      if(UIkgxaIYEF == true){UIkgxaIYEF = false;}
      if(gJKfOGzyUH == true){gJKfOGzyUH = false;}
      if(GuEorfuknY == true){GuEorfuknY = false;}
      if(alKPhrDgpV == true){alKPhrDgpV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XGUWAKQQRA
{ 
  void EKyCuOpdus()
  { 
      bool XJrslBtruD = false;
      bool mdSOznZlfU = false;
      bool CGRCFFrWHd = false;
      bool HMEHHOwZja = false;
      bool rklWyQFunp = false;
      bool yTDHMRrpmg = false;
      bool JWjQuZYLGj = false;
      bool rzBFbRTtDo = false;
      bool zxhQfnJwtp = false;
      bool WGmCRUAVbX = false;
      bool qtnEyySyeu = false;
      bool yxlyhLoSkG = false;
      bool QbQQNkMymH = false;
      bool RySexFIdSg = false;
      bool VKRzqZToUF = false;
      bool fgjUHOcXpM = false;
      bool lTLXcAeGAb = false;
      bool DKADkGKRYn = false;
      bool QWcgbjNxXh = false;
      bool bjnFuBztVq = false;
      string lQmFqHEGUf;
      string tzuMQVIybL;
      string aOCRyEnDYR;
      string oGYxIsHxld;
      string PIeHgBXOKN;
      string KSunQXOUGm;
      string TBgDpnaxEX;
      string OLMywSiukw;
      string fZrLHWLkgj;
      string empzKNaaQs;
      string aaKmzyFwqy;
      string nSjKGsIVwS;
      string bpPTrbUMnh;
      string qIeqVFPFLI;
      string QOsiwLCfsQ;
      string FEexQjKpuX;
      string dsIJGfnrnA;
      string dDKmCNxgXf;
      string YoSWclchal;
      string tYKmeXFjbP;
      if(lQmFqHEGUf == aaKmzyFwqy){XJrslBtruD = true;}
      else if(aaKmzyFwqy == lQmFqHEGUf){qtnEyySyeu = true;}
      if(tzuMQVIybL == nSjKGsIVwS){mdSOznZlfU = true;}
      else if(nSjKGsIVwS == tzuMQVIybL){yxlyhLoSkG = true;}
      if(aOCRyEnDYR == bpPTrbUMnh){CGRCFFrWHd = true;}
      else if(bpPTrbUMnh == aOCRyEnDYR){QbQQNkMymH = true;}
      if(oGYxIsHxld == qIeqVFPFLI){HMEHHOwZja = true;}
      else if(qIeqVFPFLI == oGYxIsHxld){RySexFIdSg = true;}
      if(PIeHgBXOKN == QOsiwLCfsQ){rklWyQFunp = true;}
      else if(QOsiwLCfsQ == PIeHgBXOKN){VKRzqZToUF = true;}
      if(KSunQXOUGm == FEexQjKpuX){yTDHMRrpmg = true;}
      else if(FEexQjKpuX == KSunQXOUGm){fgjUHOcXpM = true;}
      if(TBgDpnaxEX == dsIJGfnrnA){JWjQuZYLGj = true;}
      else if(dsIJGfnrnA == TBgDpnaxEX){lTLXcAeGAb = true;}
      if(OLMywSiukw == dDKmCNxgXf){rzBFbRTtDo = true;}
      if(fZrLHWLkgj == YoSWclchal){zxhQfnJwtp = true;}
      if(empzKNaaQs == tYKmeXFjbP){WGmCRUAVbX = true;}
      while(dDKmCNxgXf == OLMywSiukw){DKADkGKRYn = true;}
      while(YoSWclchal == YoSWclchal){QWcgbjNxXh = true;}
      while(tYKmeXFjbP == tYKmeXFjbP){bjnFuBztVq = true;}
      if(XJrslBtruD == true){XJrslBtruD = false;}
      if(mdSOznZlfU == true){mdSOznZlfU = false;}
      if(CGRCFFrWHd == true){CGRCFFrWHd = false;}
      if(HMEHHOwZja == true){HMEHHOwZja = false;}
      if(rklWyQFunp == true){rklWyQFunp = false;}
      if(yTDHMRrpmg == true){yTDHMRrpmg = false;}
      if(JWjQuZYLGj == true){JWjQuZYLGj = false;}
      if(rzBFbRTtDo == true){rzBFbRTtDo = false;}
      if(zxhQfnJwtp == true){zxhQfnJwtp = false;}
      if(WGmCRUAVbX == true){WGmCRUAVbX = false;}
      if(qtnEyySyeu == true){qtnEyySyeu = false;}
      if(yxlyhLoSkG == true){yxlyhLoSkG = false;}
      if(QbQQNkMymH == true){QbQQNkMymH = false;}
      if(RySexFIdSg == true){RySexFIdSg = false;}
      if(VKRzqZToUF == true){VKRzqZToUF = false;}
      if(fgjUHOcXpM == true){fgjUHOcXpM = false;}
      if(lTLXcAeGAb == true){lTLXcAeGAb = false;}
      if(DKADkGKRYn == true){DKADkGKRYn = false;}
      if(QWcgbjNxXh == true){QWcgbjNxXh = false;}
      if(bjnFuBztVq == true){bjnFuBztVq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VZCLYOWUFW
{ 
  void VCXWbjFIin()
  { 
      bool FaxZLGezzc = false;
      bool injxzqISwM = false;
      bool FTAciBHGjK = false;
      bool BGJFcSaFwc = false;
      bool jkgUHaUFjE = false;
      bool noefPkZUqJ = false;
      bool zXPoabdeUg = false;
      bool PDWTbTmfUH = false;
      bool gBWeVMadoq = false;
      bool rGNlcMVqse = false;
      bool xokCnkRKEw = false;
      bool ytzjcyBjTO = false;
      bool BApcoJokpP = false;
      bool xulpKqPTqj = false;
      bool uPYrsyGdJe = false;
      bool KlXedwzHNd = false;
      bool ugUnzCHIZl = false;
      bool hhriSkaxjp = false;
      bool CLaLFLWHMN = false;
      bool qIFMoNuksp = false;
      string DoUjHEHfxZ;
      string fSVQNcDitX;
      string WKKXyjRKXs;
      string DDlSLaDaBc;
      string JxYWIlQDGj;
      string eZSwlrdxlX;
      string mxHDVcfDFl;
      string YchQNZlnOM;
      string TODnNdjpfS;
      string wGocpLoUAe;
      string GNyUKCrBhM;
      string GphYEXtTpr;
      string roWloRmEZB;
      string jQnjGGQicK;
      string kiHTLGYPYS;
      string RVeHlQpLes;
      string OnafbpBySy;
      string HKpeHJhCah;
      string sXeHjOkgxp;
      string PFDjuxHarU;
      if(DoUjHEHfxZ == GNyUKCrBhM){FaxZLGezzc = true;}
      else if(GNyUKCrBhM == DoUjHEHfxZ){xokCnkRKEw = true;}
      if(fSVQNcDitX == GphYEXtTpr){injxzqISwM = true;}
      else if(GphYEXtTpr == fSVQNcDitX){ytzjcyBjTO = true;}
      if(WKKXyjRKXs == roWloRmEZB){FTAciBHGjK = true;}
      else if(roWloRmEZB == WKKXyjRKXs){BApcoJokpP = true;}
      if(DDlSLaDaBc == jQnjGGQicK){BGJFcSaFwc = true;}
      else if(jQnjGGQicK == DDlSLaDaBc){xulpKqPTqj = true;}
      if(JxYWIlQDGj == kiHTLGYPYS){jkgUHaUFjE = true;}
      else if(kiHTLGYPYS == JxYWIlQDGj){uPYrsyGdJe = true;}
      if(eZSwlrdxlX == RVeHlQpLes){noefPkZUqJ = true;}
      else if(RVeHlQpLes == eZSwlrdxlX){KlXedwzHNd = true;}
      if(mxHDVcfDFl == OnafbpBySy){zXPoabdeUg = true;}
      else if(OnafbpBySy == mxHDVcfDFl){ugUnzCHIZl = true;}
      if(YchQNZlnOM == HKpeHJhCah){PDWTbTmfUH = true;}
      if(TODnNdjpfS == sXeHjOkgxp){gBWeVMadoq = true;}
      if(wGocpLoUAe == PFDjuxHarU){rGNlcMVqse = true;}
      while(HKpeHJhCah == YchQNZlnOM){hhriSkaxjp = true;}
      while(sXeHjOkgxp == sXeHjOkgxp){CLaLFLWHMN = true;}
      while(PFDjuxHarU == PFDjuxHarU){qIFMoNuksp = true;}
      if(FaxZLGezzc == true){FaxZLGezzc = false;}
      if(injxzqISwM == true){injxzqISwM = false;}
      if(FTAciBHGjK == true){FTAciBHGjK = false;}
      if(BGJFcSaFwc == true){BGJFcSaFwc = false;}
      if(jkgUHaUFjE == true){jkgUHaUFjE = false;}
      if(noefPkZUqJ == true){noefPkZUqJ = false;}
      if(zXPoabdeUg == true){zXPoabdeUg = false;}
      if(PDWTbTmfUH == true){PDWTbTmfUH = false;}
      if(gBWeVMadoq == true){gBWeVMadoq = false;}
      if(rGNlcMVqse == true){rGNlcMVqse = false;}
      if(xokCnkRKEw == true){xokCnkRKEw = false;}
      if(ytzjcyBjTO == true){ytzjcyBjTO = false;}
      if(BApcoJokpP == true){BApcoJokpP = false;}
      if(xulpKqPTqj == true){xulpKqPTqj = false;}
      if(uPYrsyGdJe == true){uPYrsyGdJe = false;}
      if(KlXedwzHNd == true){KlXedwzHNd = false;}
      if(ugUnzCHIZl == true){ugUnzCHIZl = false;}
      if(hhriSkaxjp == true){hhriSkaxjp = false;}
      if(CLaLFLWHMN == true){CLaLFLWHMN = false;}
      if(qIFMoNuksp == true){qIFMoNuksp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHLQAEJBCH
{ 
  void JSiSnxOUkD()
  { 
      bool oQCadHxmpn = false;
      bool AbIejcsqPu = false;
      bool ByDwWJaBhn = false;
      bool DupUduegrO = false;
      bool wJrmynEMkT = false;
      bool PJoKFqNFDU = false;
      bool gwEBjEknBo = false;
      bool yMyAyrGQxi = false;
      bool FOQOXtGeOm = false;
      bool hYdWhAEpCt = false;
      bool CQKwUDKnMN = false;
      bool kxHTPSfodp = false;
      bool yFYOGYhbRy = false;
      bool mPNDgnDTsT = false;
      bool iRSABkRKHP = false;
      bool UPMLuwqwou = false;
      bool ViWOaUiDla = false;
      bool PLuJHgmXMV = false;
      bool HXTCcWDBIj = false;
      bool xGeyyAtEZg = false;
      string ncoixJTBrG;
      string xKasEiCeAG;
      string AIHIyQaelJ;
      string PfsgxrcdUF;
      string YZnncILMAM;
      string MgfRefUfkf;
      string inOiqRRtwL;
      string GXKthZTSfp;
      string FNeYwhzaBQ;
      string WwsnWjKFxL;
      string pQPnGoWkjF;
      string LBAuaUJpmJ;
      string RprfoJeVXx;
      string POVUznxqSH;
      string LNqwEVwyNB;
      string aUSnszYjyx;
      string JBNloxfewm;
      string WSWfyEzwbT;
      string MgHWWtwhbz;
      string PNrVxJAEGG;
      if(ncoixJTBrG == pQPnGoWkjF){oQCadHxmpn = true;}
      else if(pQPnGoWkjF == ncoixJTBrG){CQKwUDKnMN = true;}
      if(xKasEiCeAG == LBAuaUJpmJ){AbIejcsqPu = true;}
      else if(LBAuaUJpmJ == xKasEiCeAG){kxHTPSfodp = true;}
      if(AIHIyQaelJ == RprfoJeVXx){ByDwWJaBhn = true;}
      else if(RprfoJeVXx == AIHIyQaelJ){yFYOGYhbRy = true;}
      if(PfsgxrcdUF == POVUznxqSH){DupUduegrO = true;}
      else if(POVUznxqSH == PfsgxrcdUF){mPNDgnDTsT = true;}
      if(YZnncILMAM == LNqwEVwyNB){wJrmynEMkT = true;}
      else if(LNqwEVwyNB == YZnncILMAM){iRSABkRKHP = true;}
      if(MgfRefUfkf == aUSnszYjyx){PJoKFqNFDU = true;}
      else if(aUSnszYjyx == MgfRefUfkf){UPMLuwqwou = true;}
      if(inOiqRRtwL == JBNloxfewm){gwEBjEknBo = true;}
      else if(JBNloxfewm == inOiqRRtwL){ViWOaUiDla = true;}
      if(GXKthZTSfp == WSWfyEzwbT){yMyAyrGQxi = true;}
      if(FNeYwhzaBQ == MgHWWtwhbz){FOQOXtGeOm = true;}
      if(WwsnWjKFxL == PNrVxJAEGG){hYdWhAEpCt = true;}
      while(WSWfyEzwbT == GXKthZTSfp){PLuJHgmXMV = true;}
      while(MgHWWtwhbz == MgHWWtwhbz){HXTCcWDBIj = true;}
      while(PNrVxJAEGG == PNrVxJAEGG){xGeyyAtEZg = true;}
      if(oQCadHxmpn == true){oQCadHxmpn = false;}
      if(AbIejcsqPu == true){AbIejcsqPu = false;}
      if(ByDwWJaBhn == true){ByDwWJaBhn = false;}
      if(DupUduegrO == true){DupUduegrO = false;}
      if(wJrmynEMkT == true){wJrmynEMkT = false;}
      if(PJoKFqNFDU == true){PJoKFqNFDU = false;}
      if(gwEBjEknBo == true){gwEBjEknBo = false;}
      if(yMyAyrGQxi == true){yMyAyrGQxi = false;}
      if(FOQOXtGeOm == true){FOQOXtGeOm = false;}
      if(hYdWhAEpCt == true){hYdWhAEpCt = false;}
      if(CQKwUDKnMN == true){CQKwUDKnMN = false;}
      if(kxHTPSfodp == true){kxHTPSfodp = false;}
      if(yFYOGYhbRy == true){yFYOGYhbRy = false;}
      if(mPNDgnDTsT == true){mPNDgnDTsT = false;}
      if(iRSABkRKHP == true){iRSABkRKHP = false;}
      if(UPMLuwqwou == true){UPMLuwqwou = false;}
      if(ViWOaUiDla == true){ViWOaUiDla = false;}
      if(PLuJHgmXMV == true){PLuJHgmXMV = false;}
      if(HXTCcWDBIj == true){HXTCcWDBIj = false;}
      if(xGeyyAtEZg == true){xGeyyAtEZg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ULIYMHZRBQ
{ 
  void FiNSOYVbGK()
  { 
      bool asytAIGcWT = false;
      bool ppCeLYfYiq = false;
      bool rRxjYWfRwM = false;
      bool NFFlCjBLci = false;
      bool PJcCtwfkcs = false;
      bool FDrHKIuOVd = false;
      bool cngJGkjQca = false;
      bool XTwzbinupb = false;
      bool ptoCGJMyas = false;
      bool ompyFabSuJ = false;
      bool LPICVkHsfa = false;
      bool TzXtnizdCx = false;
      bool XlpilkdysA = false;
      bool HVAgPalmfV = false;
      bool CTRzYoOuKW = false;
      bool bxPykZZYPk = false;
      bool GJzeTyzqdN = false;
      bool wLygtETpKx = false;
      bool VhmWXJFBup = false;
      bool ANWuOsUmeZ = false;
      string MHyjIEzpsk;
      string TlLDfgQtnR;
      string aWGjmYdduA;
      string mdYmjfbwhP;
      string usrqVVhkck;
      string OMLwepBNwi;
      string aVuryoMXTz;
      string EULYWheONR;
      string qsBKlZSbIt;
      string eNzynYyzsg;
      string IJQcftAmYw;
      string KlAerhTjGX;
      string WjPYUqUNjx;
      string ieUfJgbXdq;
      string YfDLirMUGG;
      string ENrUKXtrHo;
      string YmCbMfRTVL;
      string GwGOypgDoc;
      string dAGcrVmzVk;
      string miPnSlcbyD;
      if(MHyjIEzpsk == IJQcftAmYw){asytAIGcWT = true;}
      else if(IJQcftAmYw == MHyjIEzpsk){LPICVkHsfa = true;}
      if(TlLDfgQtnR == KlAerhTjGX){ppCeLYfYiq = true;}
      else if(KlAerhTjGX == TlLDfgQtnR){TzXtnizdCx = true;}
      if(aWGjmYdduA == WjPYUqUNjx){rRxjYWfRwM = true;}
      else if(WjPYUqUNjx == aWGjmYdduA){XlpilkdysA = true;}
      if(mdYmjfbwhP == ieUfJgbXdq){NFFlCjBLci = true;}
      else if(ieUfJgbXdq == mdYmjfbwhP){HVAgPalmfV = true;}
      if(usrqVVhkck == YfDLirMUGG){PJcCtwfkcs = true;}
      else if(YfDLirMUGG == usrqVVhkck){CTRzYoOuKW = true;}
      if(OMLwepBNwi == ENrUKXtrHo){FDrHKIuOVd = true;}
      else if(ENrUKXtrHo == OMLwepBNwi){bxPykZZYPk = true;}
      if(aVuryoMXTz == YmCbMfRTVL){cngJGkjQca = true;}
      else if(YmCbMfRTVL == aVuryoMXTz){GJzeTyzqdN = true;}
      if(EULYWheONR == GwGOypgDoc){XTwzbinupb = true;}
      if(qsBKlZSbIt == dAGcrVmzVk){ptoCGJMyas = true;}
      if(eNzynYyzsg == miPnSlcbyD){ompyFabSuJ = true;}
      while(GwGOypgDoc == EULYWheONR){wLygtETpKx = true;}
      while(dAGcrVmzVk == dAGcrVmzVk){VhmWXJFBup = true;}
      while(miPnSlcbyD == miPnSlcbyD){ANWuOsUmeZ = true;}
      if(asytAIGcWT == true){asytAIGcWT = false;}
      if(ppCeLYfYiq == true){ppCeLYfYiq = false;}
      if(rRxjYWfRwM == true){rRxjYWfRwM = false;}
      if(NFFlCjBLci == true){NFFlCjBLci = false;}
      if(PJcCtwfkcs == true){PJcCtwfkcs = false;}
      if(FDrHKIuOVd == true){FDrHKIuOVd = false;}
      if(cngJGkjQca == true){cngJGkjQca = false;}
      if(XTwzbinupb == true){XTwzbinupb = false;}
      if(ptoCGJMyas == true){ptoCGJMyas = false;}
      if(ompyFabSuJ == true){ompyFabSuJ = false;}
      if(LPICVkHsfa == true){LPICVkHsfa = false;}
      if(TzXtnizdCx == true){TzXtnizdCx = false;}
      if(XlpilkdysA == true){XlpilkdysA = false;}
      if(HVAgPalmfV == true){HVAgPalmfV = false;}
      if(CTRzYoOuKW == true){CTRzYoOuKW = false;}
      if(bxPykZZYPk == true){bxPykZZYPk = false;}
      if(GJzeTyzqdN == true){GJzeTyzqdN = false;}
      if(wLygtETpKx == true){wLygtETpKx = false;}
      if(VhmWXJFBup == true){VhmWXJFBup = false;}
      if(ANWuOsUmeZ == true){ANWuOsUmeZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UAMETZDLWL
{ 
  void BDbyYVWNLz()
  { 
      bool dpoISBMmsB = false;
      bool ocpqTZxLjA = false;
      bool pJzRyCQnbl = false;
      bool NPEzgNRgQi = false;
      bool GLTwFyozob = false;
      bool NGnVxUpWKQ = false;
      bool kXLGmZXpJG = false;
      bool IPtBtdoCLz = false;
      bool NRyzYHahBM = false;
      bool WtWAyhzMJf = false;
      bool ZyoiTxMmbT = false;
      bool emLKDTZMhf = false;
      bool yonxiOssCL = false;
      bool dbseYObPfa = false;
      bool umGhgihLxe = false;
      bool ImedhkKrzF = false;
      bool DSkPpCtgln = false;
      bool qJgHkKiGPA = false;
      bool fhuWDpxPxn = false;
      bool EjQZWbCpre = false;
      string HwMQinSnod;
      string tPHifJHAMP;
      string fGearcuKPG;
      string ZEXCirCLqj;
      string ONMoRFbsCU;
      string iSJOOAQlYF;
      string rHYiDorFzn;
      string HuIbARtpIl;
      string BCHtWHuImi;
      string aQmlqHndlb;
      string NVsONnJgOx;
      string FaclEpzdMu;
      string tiRQMpHWkr;
      string cQDfYeIsgh;
      string yNtpcAmBgA;
      string HKRphdEcCW;
      string fmuVToWxMY;
      string hGxdxfnbmL;
      string DGojkSzMyu;
      string aepJCKRYWm;
      if(HwMQinSnod == NVsONnJgOx){dpoISBMmsB = true;}
      else if(NVsONnJgOx == HwMQinSnod){ZyoiTxMmbT = true;}
      if(tPHifJHAMP == FaclEpzdMu){ocpqTZxLjA = true;}
      else if(FaclEpzdMu == tPHifJHAMP){emLKDTZMhf = true;}
      if(fGearcuKPG == tiRQMpHWkr){pJzRyCQnbl = true;}
      else if(tiRQMpHWkr == fGearcuKPG){yonxiOssCL = true;}
      if(ZEXCirCLqj == cQDfYeIsgh){NPEzgNRgQi = true;}
      else if(cQDfYeIsgh == ZEXCirCLqj){dbseYObPfa = true;}
      if(ONMoRFbsCU == yNtpcAmBgA){GLTwFyozob = true;}
      else if(yNtpcAmBgA == ONMoRFbsCU){umGhgihLxe = true;}
      if(iSJOOAQlYF == HKRphdEcCW){NGnVxUpWKQ = true;}
      else if(HKRphdEcCW == iSJOOAQlYF){ImedhkKrzF = true;}
      if(rHYiDorFzn == fmuVToWxMY){kXLGmZXpJG = true;}
      else if(fmuVToWxMY == rHYiDorFzn){DSkPpCtgln = true;}
      if(HuIbARtpIl == hGxdxfnbmL){IPtBtdoCLz = true;}
      if(BCHtWHuImi == DGojkSzMyu){NRyzYHahBM = true;}
      if(aQmlqHndlb == aepJCKRYWm){WtWAyhzMJf = true;}
      while(hGxdxfnbmL == HuIbARtpIl){qJgHkKiGPA = true;}
      while(DGojkSzMyu == DGojkSzMyu){fhuWDpxPxn = true;}
      while(aepJCKRYWm == aepJCKRYWm){EjQZWbCpre = true;}
      if(dpoISBMmsB == true){dpoISBMmsB = false;}
      if(ocpqTZxLjA == true){ocpqTZxLjA = false;}
      if(pJzRyCQnbl == true){pJzRyCQnbl = false;}
      if(NPEzgNRgQi == true){NPEzgNRgQi = false;}
      if(GLTwFyozob == true){GLTwFyozob = false;}
      if(NGnVxUpWKQ == true){NGnVxUpWKQ = false;}
      if(kXLGmZXpJG == true){kXLGmZXpJG = false;}
      if(IPtBtdoCLz == true){IPtBtdoCLz = false;}
      if(NRyzYHahBM == true){NRyzYHahBM = false;}
      if(WtWAyhzMJf == true){WtWAyhzMJf = false;}
      if(ZyoiTxMmbT == true){ZyoiTxMmbT = false;}
      if(emLKDTZMhf == true){emLKDTZMhf = false;}
      if(yonxiOssCL == true){yonxiOssCL = false;}
      if(dbseYObPfa == true){dbseYObPfa = false;}
      if(umGhgihLxe == true){umGhgihLxe = false;}
      if(ImedhkKrzF == true){ImedhkKrzF = false;}
      if(DSkPpCtgln == true){DSkPpCtgln = false;}
      if(qJgHkKiGPA == true){qJgHkKiGPA = false;}
      if(fhuWDpxPxn == true){fhuWDpxPxn = false;}
      if(EjQZWbCpre == true){EjQZWbCpre = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLCBBCLBXB
{ 
  void RVbCrZScoJ()
  { 
      bool fjpKVaTpPG = false;
      bool kDOYyVljMi = false;
      bool wHVMquDYBq = false;
      bool jUzFbzSbCa = false;
      bool RFGyoyEcls = false;
      bool DTWiQYOdSa = false;
      bool WtnYVPDJwz = false;
      bool DJgkRqBWWr = false;
      bool pZlImQyPoD = false;
      bool jnIbDWQgcZ = false;
      bool uugmotlkRZ = false;
      bool WqHajwIfkF = false;
      bool RnTrOOAFhu = false;
      bool ZTtxxuszSs = false;
      bool dMyPgsghqG = false;
      bool OkwWHHanXZ = false;
      bool sgDVzDwKcn = false;
      bool DIMrbFoELV = false;
      bool hSNafoXXop = false;
      bool UFarAwIbPd = false;
      string hgBNUxkXei;
      string tuEijjUyeG;
      string yRadzEcJAE;
      string IKyaOLGylU;
      string zdtRgoFXYF;
      string pcdEDQFWOQ;
      string UaXaZjwcTY;
      string dWMKGUWJxJ;
      string zEktOegtWx;
      string FjiUAXGTqx;
      string rbDAbSQTxi;
      string tuZFQPpcMu;
      string CCGVSsmqJi;
      string OCRzRXBjSu;
      string ONxnDJKdEk;
      string gcHwupVghh;
      string fYJNUqdZms;
      string OGJQfnESSI;
      string iJmYBkuVEa;
      string BTCkPoEiSM;
      if(hgBNUxkXei == rbDAbSQTxi){fjpKVaTpPG = true;}
      else if(rbDAbSQTxi == hgBNUxkXei){uugmotlkRZ = true;}
      if(tuEijjUyeG == tuZFQPpcMu){kDOYyVljMi = true;}
      else if(tuZFQPpcMu == tuEijjUyeG){WqHajwIfkF = true;}
      if(yRadzEcJAE == CCGVSsmqJi){wHVMquDYBq = true;}
      else if(CCGVSsmqJi == yRadzEcJAE){RnTrOOAFhu = true;}
      if(IKyaOLGylU == OCRzRXBjSu){jUzFbzSbCa = true;}
      else if(OCRzRXBjSu == IKyaOLGylU){ZTtxxuszSs = true;}
      if(zdtRgoFXYF == ONxnDJKdEk){RFGyoyEcls = true;}
      else if(ONxnDJKdEk == zdtRgoFXYF){dMyPgsghqG = true;}
      if(pcdEDQFWOQ == gcHwupVghh){DTWiQYOdSa = true;}
      else if(gcHwupVghh == pcdEDQFWOQ){OkwWHHanXZ = true;}
      if(UaXaZjwcTY == fYJNUqdZms){WtnYVPDJwz = true;}
      else if(fYJNUqdZms == UaXaZjwcTY){sgDVzDwKcn = true;}
      if(dWMKGUWJxJ == OGJQfnESSI){DJgkRqBWWr = true;}
      if(zEktOegtWx == iJmYBkuVEa){pZlImQyPoD = true;}
      if(FjiUAXGTqx == BTCkPoEiSM){jnIbDWQgcZ = true;}
      while(OGJQfnESSI == dWMKGUWJxJ){DIMrbFoELV = true;}
      while(iJmYBkuVEa == iJmYBkuVEa){hSNafoXXop = true;}
      while(BTCkPoEiSM == BTCkPoEiSM){UFarAwIbPd = true;}
      if(fjpKVaTpPG == true){fjpKVaTpPG = false;}
      if(kDOYyVljMi == true){kDOYyVljMi = false;}
      if(wHVMquDYBq == true){wHVMquDYBq = false;}
      if(jUzFbzSbCa == true){jUzFbzSbCa = false;}
      if(RFGyoyEcls == true){RFGyoyEcls = false;}
      if(DTWiQYOdSa == true){DTWiQYOdSa = false;}
      if(WtnYVPDJwz == true){WtnYVPDJwz = false;}
      if(DJgkRqBWWr == true){DJgkRqBWWr = false;}
      if(pZlImQyPoD == true){pZlImQyPoD = false;}
      if(jnIbDWQgcZ == true){jnIbDWQgcZ = false;}
      if(uugmotlkRZ == true){uugmotlkRZ = false;}
      if(WqHajwIfkF == true){WqHajwIfkF = false;}
      if(RnTrOOAFhu == true){RnTrOOAFhu = false;}
      if(ZTtxxuszSs == true){ZTtxxuszSs = false;}
      if(dMyPgsghqG == true){dMyPgsghqG = false;}
      if(OkwWHHanXZ == true){OkwWHHanXZ = false;}
      if(sgDVzDwKcn == true){sgDVzDwKcn = false;}
      if(DIMrbFoELV == true){DIMrbFoELV = false;}
      if(hSNafoXXop == true){hSNafoXXop = false;}
      if(UFarAwIbPd == true){UFarAwIbPd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWVJAHYVDP
{ 
  void kKqETDHghu()
  { 
      bool NkXqsUMudh = false;
      bool PJSzfMGJOL = false;
      bool FSMZHSnbGD = false;
      bool BdwNALbgIs = false;
      bool naouATFpFQ = false;
      bool bYqBYuXyia = false;
      bool gjoZglMFzU = false;
      bool kYAVWddRZn = false;
      bool MxWobbltnF = false;
      bool mcyhMDkOON = false;
      bool GzqkfCYVdt = false;
      bool RGYtNiNzyE = false;
      bool zSRsgHaSIS = false;
      bool rOCLhNGkJY = false;
      bool DQQtngEDTc = false;
      bool plQJNnhxEX = false;
      bool aFMKBCDMMA = false;
      bool bboYBiCWFz = false;
      bool DXyfcGysyt = false;
      bool eJglxxEFrk = false;
      string JVcrZuLnZX;
      string CHjKVRxtVs;
      string cRDDAweuwd;
      string fiMkcljNlZ;
      string ywEGOOzoMg;
      string LnrkVrRZrc;
      string PQruqTuygi;
      string hjIutgMxok;
      string wphOSrpaOk;
      string TKVIJgEJOt;
      string TBHdzaewqo;
      string eUjGfZhcby;
      string cTiwOWOAkM;
      string bDitQuiEOq;
      string MsjZFzZObj;
      string yagPRASKOc;
      string MeKdMbkopk;
      string qdOklijIqO;
      string wzXBOBWScQ;
      string cYpldhhGMd;
      if(JVcrZuLnZX == TBHdzaewqo){NkXqsUMudh = true;}
      else if(TBHdzaewqo == JVcrZuLnZX){GzqkfCYVdt = true;}
      if(CHjKVRxtVs == eUjGfZhcby){PJSzfMGJOL = true;}
      else if(eUjGfZhcby == CHjKVRxtVs){RGYtNiNzyE = true;}
      if(cRDDAweuwd == cTiwOWOAkM){FSMZHSnbGD = true;}
      else if(cTiwOWOAkM == cRDDAweuwd){zSRsgHaSIS = true;}
      if(fiMkcljNlZ == bDitQuiEOq){BdwNALbgIs = true;}
      else if(bDitQuiEOq == fiMkcljNlZ){rOCLhNGkJY = true;}
      if(ywEGOOzoMg == MsjZFzZObj){naouATFpFQ = true;}
      else if(MsjZFzZObj == ywEGOOzoMg){DQQtngEDTc = true;}
      if(LnrkVrRZrc == yagPRASKOc){bYqBYuXyia = true;}
      else if(yagPRASKOc == LnrkVrRZrc){plQJNnhxEX = true;}
      if(PQruqTuygi == MeKdMbkopk){gjoZglMFzU = true;}
      else if(MeKdMbkopk == PQruqTuygi){aFMKBCDMMA = true;}
      if(hjIutgMxok == qdOklijIqO){kYAVWddRZn = true;}
      if(wphOSrpaOk == wzXBOBWScQ){MxWobbltnF = true;}
      if(TKVIJgEJOt == cYpldhhGMd){mcyhMDkOON = true;}
      while(qdOklijIqO == hjIutgMxok){bboYBiCWFz = true;}
      while(wzXBOBWScQ == wzXBOBWScQ){DXyfcGysyt = true;}
      while(cYpldhhGMd == cYpldhhGMd){eJglxxEFrk = true;}
      if(NkXqsUMudh == true){NkXqsUMudh = false;}
      if(PJSzfMGJOL == true){PJSzfMGJOL = false;}
      if(FSMZHSnbGD == true){FSMZHSnbGD = false;}
      if(BdwNALbgIs == true){BdwNALbgIs = false;}
      if(naouATFpFQ == true){naouATFpFQ = false;}
      if(bYqBYuXyia == true){bYqBYuXyia = false;}
      if(gjoZglMFzU == true){gjoZglMFzU = false;}
      if(kYAVWddRZn == true){kYAVWddRZn = false;}
      if(MxWobbltnF == true){MxWobbltnF = false;}
      if(mcyhMDkOON == true){mcyhMDkOON = false;}
      if(GzqkfCYVdt == true){GzqkfCYVdt = false;}
      if(RGYtNiNzyE == true){RGYtNiNzyE = false;}
      if(zSRsgHaSIS == true){zSRsgHaSIS = false;}
      if(rOCLhNGkJY == true){rOCLhNGkJY = false;}
      if(DQQtngEDTc == true){DQQtngEDTc = false;}
      if(plQJNnhxEX == true){plQJNnhxEX = false;}
      if(aFMKBCDMMA == true){aFMKBCDMMA = false;}
      if(bboYBiCWFz == true){bboYBiCWFz = false;}
      if(DXyfcGysyt == true){DXyfcGysyt = false;}
      if(eJglxxEFrk == true){eJglxxEFrk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JHMKHYJREK
{ 
  void PSTjHlQHFS()
  { 
      bool BcmfMmiHpV = false;
      bool MpuffWhzqh = false;
      bool kTUHVfIpXk = false;
      bool tSLFhCGxqe = false;
      bool ztYAdVPASc = false;
      bool qbKIwgHfKf = false;
      bool dsiFateoyc = false;
      bool PkILipuUcz = false;
      bool PHWusSHCJA = false;
      bool uamKAGLTYj = false;
      bool qZBpMGSyZF = false;
      bool llCKPVVnLI = false;
      bool lbfygnyyKb = false;
      bool eausIoGghl = false;
      bool zJbEOJXbte = false;
      bool jXHQyOtDIX = false;
      bool IUmxaLqJCZ = false;
      bool PnFZIczbjX = false;
      bool QVDfqHSdus = false;
      bool uCXKdeVddC = false;
      string uXDyyDqfue;
      string xhiMILunUy;
      string hXGqtDcWHt;
      string oFjpNClKuS;
      string kzVpkJupok;
      string gxNSIXRLEt;
      string ZUXBprxryF;
      string ZkrBMiCQGj;
      string IlgWMrqRgp;
      string kZFAsQaTzr;
      string MDqjLwEMFZ;
      string UAFUlmmBoy;
      string AfKITzerIw;
      string IhQNWEuxKQ;
      string meLHUkTkNF;
      string cZeBqgsiPL;
      string QMDJQmiqxg;
      string rppXLVTCmi;
      string etdDSiCPVp;
      string LLgzzZaBqg;
      if(uXDyyDqfue == MDqjLwEMFZ){BcmfMmiHpV = true;}
      else if(MDqjLwEMFZ == uXDyyDqfue){qZBpMGSyZF = true;}
      if(xhiMILunUy == UAFUlmmBoy){MpuffWhzqh = true;}
      else if(UAFUlmmBoy == xhiMILunUy){llCKPVVnLI = true;}
      if(hXGqtDcWHt == AfKITzerIw){kTUHVfIpXk = true;}
      else if(AfKITzerIw == hXGqtDcWHt){lbfygnyyKb = true;}
      if(oFjpNClKuS == IhQNWEuxKQ){tSLFhCGxqe = true;}
      else if(IhQNWEuxKQ == oFjpNClKuS){eausIoGghl = true;}
      if(kzVpkJupok == meLHUkTkNF){ztYAdVPASc = true;}
      else if(meLHUkTkNF == kzVpkJupok){zJbEOJXbte = true;}
      if(gxNSIXRLEt == cZeBqgsiPL){qbKIwgHfKf = true;}
      else if(cZeBqgsiPL == gxNSIXRLEt){jXHQyOtDIX = true;}
      if(ZUXBprxryF == QMDJQmiqxg){dsiFateoyc = true;}
      else if(QMDJQmiqxg == ZUXBprxryF){IUmxaLqJCZ = true;}
      if(ZkrBMiCQGj == rppXLVTCmi){PkILipuUcz = true;}
      if(IlgWMrqRgp == etdDSiCPVp){PHWusSHCJA = true;}
      if(kZFAsQaTzr == LLgzzZaBqg){uamKAGLTYj = true;}
      while(rppXLVTCmi == ZkrBMiCQGj){PnFZIczbjX = true;}
      while(etdDSiCPVp == etdDSiCPVp){QVDfqHSdus = true;}
      while(LLgzzZaBqg == LLgzzZaBqg){uCXKdeVddC = true;}
      if(BcmfMmiHpV == true){BcmfMmiHpV = false;}
      if(MpuffWhzqh == true){MpuffWhzqh = false;}
      if(kTUHVfIpXk == true){kTUHVfIpXk = false;}
      if(tSLFhCGxqe == true){tSLFhCGxqe = false;}
      if(ztYAdVPASc == true){ztYAdVPASc = false;}
      if(qbKIwgHfKf == true){qbKIwgHfKf = false;}
      if(dsiFateoyc == true){dsiFateoyc = false;}
      if(PkILipuUcz == true){PkILipuUcz = false;}
      if(PHWusSHCJA == true){PHWusSHCJA = false;}
      if(uamKAGLTYj == true){uamKAGLTYj = false;}
      if(qZBpMGSyZF == true){qZBpMGSyZF = false;}
      if(llCKPVVnLI == true){llCKPVVnLI = false;}
      if(lbfygnyyKb == true){lbfygnyyKb = false;}
      if(eausIoGghl == true){eausIoGghl = false;}
      if(zJbEOJXbte == true){zJbEOJXbte = false;}
      if(jXHQyOtDIX == true){jXHQyOtDIX = false;}
      if(IUmxaLqJCZ == true){IUmxaLqJCZ = false;}
      if(PnFZIczbjX == true){PnFZIczbjX = false;}
      if(QVDfqHSdus == true){QVDfqHSdus = false;}
      if(uCXKdeVddC == true){uCXKdeVddC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EYKGCNEAFQ
{ 
  void tCdFJDxNdB()
  { 
      bool WCMwyZcQnJ = false;
      bool zHPaGbMEEX = false;
      bool tTSgmXnSgZ = false;
      bool CoVEoKNuBB = false;
      bool goVpgzKjTj = false;
      bool RrLzkCifJa = false;
      bool lKiOGJlLlu = false;
      bool ORDCqFyczn = false;
      bool MDzwHKdVTl = false;
      bool bgkaOWFHiW = false;
      bool MzxXVAoIIf = false;
      bool EFfVNhKlGw = false;
      bool fPrATgfbnU = false;
      bool zqtbaMFaaH = false;
      bool UUNmgVBPMg = false;
      bool LTAmqwHxDo = false;
      bool TMUngNLDtA = false;
      bool bjLzbKCESy = false;
      bool eQPGJepHkd = false;
      bool FIXlnHAYGT = false;
      string cjZJshfEXs;
      string VDnHiTqiGp;
      string bcWeTfRlXx;
      string jTdUurpPHm;
      string RnsoLdUaod;
      string eNTDBzNtoN;
      string QtfaJBZSLp;
      string cbbTXnihSo;
      string KpwtRVAZTw;
      string euasWWHSfK;
      string EBPyADlAeN;
      string QeazDZylIm;
      string AzzPLgBhwA;
      string fPBIkIaysO;
      string iAtFezUapx;
      string YVKrJEBzmS;
      string CEDehAcSNt;
      string yzrtEzEtjL;
      string MZqzaJFJzg;
      string GaLZMexPXe;
      if(cjZJshfEXs == EBPyADlAeN){WCMwyZcQnJ = true;}
      else if(EBPyADlAeN == cjZJshfEXs){MzxXVAoIIf = true;}
      if(VDnHiTqiGp == QeazDZylIm){zHPaGbMEEX = true;}
      else if(QeazDZylIm == VDnHiTqiGp){EFfVNhKlGw = true;}
      if(bcWeTfRlXx == AzzPLgBhwA){tTSgmXnSgZ = true;}
      else if(AzzPLgBhwA == bcWeTfRlXx){fPrATgfbnU = true;}
      if(jTdUurpPHm == fPBIkIaysO){CoVEoKNuBB = true;}
      else if(fPBIkIaysO == jTdUurpPHm){zqtbaMFaaH = true;}
      if(RnsoLdUaod == iAtFezUapx){goVpgzKjTj = true;}
      else if(iAtFezUapx == RnsoLdUaod){UUNmgVBPMg = true;}
      if(eNTDBzNtoN == YVKrJEBzmS){RrLzkCifJa = true;}
      else if(YVKrJEBzmS == eNTDBzNtoN){LTAmqwHxDo = true;}
      if(QtfaJBZSLp == CEDehAcSNt){lKiOGJlLlu = true;}
      else if(CEDehAcSNt == QtfaJBZSLp){TMUngNLDtA = true;}
      if(cbbTXnihSo == yzrtEzEtjL){ORDCqFyczn = true;}
      if(KpwtRVAZTw == MZqzaJFJzg){MDzwHKdVTl = true;}
      if(euasWWHSfK == GaLZMexPXe){bgkaOWFHiW = true;}
      while(yzrtEzEtjL == cbbTXnihSo){bjLzbKCESy = true;}
      while(MZqzaJFJzg == MZqzaJFJzg){eQPGJepHkd = true;}
      while(GaLZMexPXe == GaLZMexPXe){FIXlnHAYGT = true;}
      if(WCMwyZcQnJ == true){WCMwyZcQnJ = false;}
      if(zHPaGbMEEX == true){zHPaGbMEEX = false;}
      if(tTSgmXnSgZ == true){tTSgmXnSgZ = false;}
      if(CoVEoKNuBB == true){CoVEoKNuBB = false;}
      if(goVpgzKjTj == true){goVpgzKjTj = false;}
      if(RrLzkCifJa == true){RrLzkCifJa = false;}
      if(lKiOGJlLlu == true){lKiOGJlLlu = false;}
      if(ORDCqFyczn == true){ORDCqFyczn = false;}
      if(MDzwHKdVTl == true){MDzwHKdVTl = false;}
      if(bgkaOWFHiW == true){bgkaOWFHiW = false;}
      if(MzxXVAoIIf == true){MzxXVAoIIf = false;}
      if(EFfVNhKlGw == true){EFfVNhKlGw = false;}
      if(fPrATgfbnU == true){fPrATgfbnU = false;}
      if(zqtbaMFaaH == true){zqtbaMFaaH = false;}
      if(UUNmgVBPMg == true){UUNmgVBPMg = false;}
      if(LTAmqwHxDo == true){LTAmqwHxDo = false;}
      if(TMUngNLDtA == true){TMUngNLDtA = false;}
      if(bjLzbKCESy == true){bjLzbKCESy = false;}
      if(eQPGJepHkd == true){eQPGJepHkd = false;}
      if(FIXlnHAYGT == true){FIXlnHAYGT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YARGWIKCLD
{ 
  void ODQJtAzPkR()
  { 
      bool TGmgUIzNTe = false;
      bool aQNCoYUpTQ = false;
      bool ZudBDPOrca = false;
      bool ioXtSGAMBz = false;
      bool WRiPuMWzlz = false;
      bool IlqUBXbkcF = false;
      bool tHksulrSji = false;
      bool XInUsHMOFq = false;
      bool sOGdRxxCst = false;
      bool dPiwEPgoTJ = false;
      bool TDPDaAxWbs = false;
      bool LNflLfAHay = false;
      bool ooZpEIYqPc = false;
      bool aWuwXozDCR = false;
      bool zZazhPjxjY = false;
      bool PYNUUddYyS = false;
      bool bGGzSoSiNW = false;
      bool fxFJzOOZIo = false;
      bool YaGqNBIZat = false;
      bool LZEiorTbgr = false;
      string oDzDsHQNjx;
      string kLZSJCCpFr;
      string onePRBdWuw;
      string kmYnhOXTnU;
      string bipgnDrWmY;
      string wXqakAXjkr;
      string csSmLxmkkt;
      string eiCkQGyyaO;
      string JHjVzNwyDh;
      string qmhuqiPCVq;
      string QGlrsNUGJd;
      string BZIWiVIwmx;
      string BogCDrAGsh;
      string qubjyCUqcl;
      string ronYgReLMV;
      string ZTPYpbYjoB;
      string NONbmFyXXf;
      string AQTBELAIVl;
      string MnsWHWfCtW;
      string ckCaXdbLka;
      if(oDzDsHQNjx == QGlrsNUGJd){TGmgUIzNTe = true;}
      else if(QGlrsNUGJd == oDzDsHQNjx){TDPDaAxWbs = true;}
      if(kLZSJCCpFr == BZIWiVIwmx){aQNCoYUpTQ = true;}
      else if(BZIWiVIwmx == kLZSJCCpFr){LNflLfAHay = true;}
      if(onePRBdWuw == BogCDrAGsh){ZudBDPOrca = true;}
      else if(BogCDrAGsh == onePRBdWuw){ooZpEIYqPc = true;}
      if(kmYnhOXTnU == qubjyCUqcl){ioXtSGAMBz = true;}
      else if(qubjyCUqcl == kmYnhOXTnU){aWuwXozDCR = true;}
      if(bipgnDrWmY == ronYgReLMV){WRiPuMWzlz = true;}
      else if(ronYgReLMV == bipgnDrWmY){zZazhPjxjY = true;}
      if(wXqakAXjkr == ZTPYpbYjoB){IlqUBXbkcF = true;}
      else if(ZTPYpbYjoB == wXqakAXjkr){PYNUUddYyS = true;}
      if(csSmLxmkkt == NONbmFyXXf){tHksulrSji = true;}
      else if(NONbmFyXXf == csSmLxmkkt){bGGzSoSiNW = true;}
      if(eiCkQGyyaO == AQTBELAIVl){XInUsHMOFq = true;}
      if(JHjVzNwyDh == MnsWHWfCtW){sOGdRxxCst = true;}
      if(qmhuqiPCVq == ckCaXdbLka){dPiwEPgoTJ = true;}
      while(AQTBELAIVl == eiCkQGyyaO){fxFJzOOZIo = true;}
      while(MnsWHWfCtW == MnsWHWfCtW){YaGqNBIZat = true;}
      while(ckCaXdbLka == ckCaXdbLka){LZEiorTbgr = true;}
      if(TGmgUIzNTe == true){TGmgUIzNTe = false;}
      if(aQNCoYUpTQ == true){aQNCoYUpTQ = false;}
      if(ZudBDPOrca == true){ZudBDPOrca = false;}
      if(ioXtSGAMBz == true){ioXtSGAMBz = false;}
      if(WRiPuMWzlz == true){WRiPuMWzlz = false;}
      if(IlqUBXbkcF == true){IlqUBXbkcF = false;}
      if(tHksulrSji == true){tHksulrSji = false;}
      if(XInUsHMOFq == true){XInUsHMOFq = false;}
      if(sOGdRxxCst == true){sOGdRxxCst = false;}
      if(dPiwEPgoTJ == true){dPiwEPgoTJ = false;}
      if(TDPDaAxWbs == true){TDPDaAxWbs = false;}
      if(LNflLfAHay == true){LNflLfAHay = false;}
      if(ooZpEIYqPc == true){ooZpEIYqPc = false;}
      if(aWuwXozDCR == true){aWuwXozDCR = false;}
      if(zZazhPjxjY == true){zZazhPjxjY = false;}
      if(PYNUUddYyS == true){PYNUUddYyS = false;}
      if(bGGzSoSiNW == true){bGGzSoSiNW = false;}
      if(fxFJzOOZIo == true){fxFJzOOZIo = false;}
      if(YaGqNBIZat == true){YaGqNBIZat = false;}
      if(LZEiorTbgr == true){LZEiorTbgr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NTSJORCITG
{ 
  void WBVyrOngny()
  { 
      bool IyaNOXDzyy = false;
      bool YOIZwjhWGZ = false;
      bool IUoowOaAlp = false;
      bool iyxOqOnVYa = false;
      bool BFbLIXXEJe = false;
      bool fULeinJlRz = false;
      bool wDMHOZQthg = false;
      bool wMyfYDsdfY = false;
      bool pVpGKNlSfD = false;
      bool FCDYdxsTwi = false;
      bool GdVciTWfGf = false;
      bool tfFrIZNGxA = false;
      bool nyNebsIYBa = false;
      bool JYgxSMANXq = false;
      bool qGMzIZwLPD = false;
      bool jlWwuIPqBo = false;
      bool LxeeVVyIZw = false;
      bool ZAhFJgkOVC = false;
      bool xwJxqXCkCJ = false;
      bool wILhftahdm = false;
      string TxDQcJuFWz;
      string LtpJArktVx;
      string kaKhWgrAxi;
      string nVBXUQBieU;
      string hoEwtWXSPM;
      string LMJwrrmVsw;
      string RuHmKpsSoi;
      string qBPBPwWOmA;
      string JYkkXbLEfb;
      string depiDmgQkE;
      string dFcfUJxIgu;
      string UYhsmrKWPi;
      string enmNFLLfyb;
      string PGciWEwEPN;
      string eCXjGExwwK;
      string cKBCZoRPZJ;
      string yQKFeOuyVi;
      string wFGBDbQCGA;
      string NOimyFFaJg;
      string lgdGPNrSEr;
      if(TxDQcJuFWz == dFcfUJxIgu){IyaNOXDzyy = true;}
      else if(dFcfUJxIgu == TxDQcJuFWz){GdVciTWfGf = true;}
      if(LtpJArktVx == UYhsmrKWPi){YOIZwjhWGZ = true;}
      else if(UYhsmrKWPi == LtpJArktVx){tfFrIZNGxA = true;}
      if(kaKhWgrAxi == enmNFLLfyb){IUoowOaAlp = true;}
      else if(enmNFLLfyb == kaKhWgrAxi){nyNebsIYBa = true;}
      if(nVBXUQBieU == PGciWEwEPN){iyxOqOnVYa = true;}
      else if(PGciWEwEPN == nVBXUQBieU){JYgxSMANXq = true;}
      if(hoEwtWXSPM == eCXjGExwwK){BFbLIXXEJe = true;}
      else if(eCXjGExwwK == hoEwtWXSPM){qGMzIZwLPD = true;}
      if(LMJwrrmVsw == cKBCZoRPZJ){fULeinJlRz = true;}
      else if(cKBCZoRPZJ == LMJwrrmVsw){jlWwuIPqBo = true;}
      if(RuHmKpsSoi == yQKFeOuyVi){wDMHOZQthg = true;}
      else if(yQKFeOuyVi == RuHmKpsSoi){LxeeVVyIZw = true;}
      if(qBPBPwWOmA == wFGBDbQCGA){wMyfYDsdfY = true;}
      if(JYkkXbLEfb == NOimyFFaJg){pVpGKNlSfD = true;}
      if(depiDmgQkE == lgdGPNrSEr){FCDYdxsTwi = true;}
      while(wFGBDbQCGA == qBPBPwWOmA){ZAhFJgkOVC = true;}
      while(NOimyFFaJg == NOimyFFaJg){xwJxqXCkCJ = true;}
      while(lgdGPNrSEr == lgdGPNrSEr){wILhftahdm = true;}
      if(IyaNOXDzyy == true){IyaNOXDzyy = false;}
      if(YOIZwjhWGZ == true){YOIZwjhWGZ = false;}
      if(IUoowOaAlp == true){IUoowOaAlp = false;}
      if(iyxOqOnVYa == true){iyxOqOnVYa = false;}
      if(BFbLIXXEJe == true){BFbLIXXEJe = false;}
      if(fULeinJlRz == true){fULeinJlRz = false;}
      if(wDMHOZQthg == true){wDMHOZQthg = false;}
      if(wMyfYDsdfY == true){wMyfYDsdfY = false;}
      if(pVpGKNlSfD == true){pVpGKNlSfD = false;}
      if(FCDYdxsTwi == true){FCDYdxsTwi = false;}
      if(GdVciTWfGf == true){GdVciTWfGf = false;}
      if(tfFrIZNGxA == true){tfFrIZNGxA = false;}
      if(nyNebsIYBa == true){nyNebsIYBa = false;}
      if(JYgxSMANXq == true){JYgxSMANXq = false;}
      if(qGMzIZwLPD == true){qGMzIZwLPD = false;}
      if(jlWwuIPqBo == true){jlWwuIPqBo = false;}
      if(LxeeVVyIZw == true){LxeeVVyIZw = false;}
      if(ZAhFJgkOVC == true){ZAhFJgkOVC = false;}
      if(xwJxqXCkCJ == true){xwJxqXCkCJ = false;}
      if(wILhftahdm == true){wILhftahdm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RFNVUIMXQU
{ 
  void yXjdjhRIqd()
  { 
      bool EdkaWsyZgY = false;
      bool XOClxFigwp = false;
      bool njZmifSYdY = false;
      bool sGVVTcuUtL = false;
      bool FEeWSomEPy = false;
      bool lSVPRUDxrq = false;
      bool aYuHeQsfRU = false;
      bool JNmkjiEDUs = false;
      bool rOJflakGEz = false;
      bool ZxcDjgJXrB = false;
      bool wGlunYfkeh = false;
      bool PAcyyMOOUD = false;
      bool flbStMjiAD = false;
      bool ZgKTwkbOrN = false;
      bool uzaViYUdEX = false;
      bool RuCnUJeSAb = false;
      bool nwkbIioICN = false;
      bool jAVGHgKGiV = false;
      bool qGebkedWyl = false;
      bool GJNQZzOzMA = false;
      string DbgjtBMdTi;
      string EaMYpjFIYU;
      string NjdanuJWoc;
      string sIFAwhqcyc;
      string BfTPEKeIoH;
      string IADcQTyGuz;
      string rpnppwULcH;
      string sbJuTgPNVc;
      string PAghTrFcib;
      string jjgykLrdZI;
      string oTegOfpHJi;
      string EjjRjqIGVx;
      string prbAXIuKJH;
      string olnNnwUzTn;
      string BxTAXzAOOs;
      string CkHbRxqeJF;
      string kfyBtRuVdn;
      string VImhusYbbX;
      string HfwQFDdLup;
      string EppNDVzRFF;
      if(DbgjtBMdTi == oTegOfpHJi){EdkaWsyZgY = true;}
      else if(oTegOfpHJi == DbgjtBMdTi){wGlunYfkeh = true;}
      if(EaMYpjFIYU == EjjRjqIGVx){XOClxFigwp = true;}
      else if(EjjRjqIGVx == EaMYpjFIYU){PAcyyMOOUD = true;}
      if(NjdanuJWoc == prbAXIuKJH){njZmifSYdY = true;}
      else if(prbAXIuKJH == NjdanuJWoc){flbStMjiAD = true;}
      if(sIFAwhqcyc == olnNnwUzTn){sGVVTcuUtL = true;}
      else if(olnNnwUzTn == sIFAwhqcyc){ZgKTwkbOrN = true;}
      if(BfTPEKeIoH == BxTAXzAOOs){FEeWSomEPy = true;}
      else if(BxTAXzAOOs == BfTPEKeIoH){uzaViYUdEX = true;}
      if(IADcQTyGuz == CkHbRxqeJF){lSVPRUDxrq = true;}
      else if(CkHbRxqeJF == IADcQTyGuz){RuCnUJeSAb = true;}
      if(rpnppwULcH == kfyBtRuVdn){aYuHeQsfRU = true;}
      else if(kfyBtRuVdn == rpnppwULcH){nwkbIioICN = true;}
      if(sbJuTgPNVc == VImhusYbbX){JNmkjiEDUs = true;}
      if(PAghTrFcib == HfwQFDdLup){rOJflakGEz = true;}
      if(jjgykLrdZI == EppNDVzRFF){ZxcDjgJXrB = true;}
      while(VImhusYbbX == sbJuTgPNVc){jAVGHgKGiV = true;}
      while(HfwQFDdLup == HfwQFDdLup){qGebkedWyl = true;}
      while(EppNDVzRFF == EppNDVzRFF){GJNQZzOzMA = true;}
      if(EdkaWsyZgY == true){EdkaWsyZgY = false;}
      if(XOClxFigwp == true){XOClxFigwp = false;}
      if(njZmifSYdY == true){njZmifSYdY = false;}
      if(sGVVTcuUtL == true){sGVVTcuUtL = false;}
      if(FEeWSomEPy == true){FEeWSomEPy = false;}
      if(lSVPRUDxrq == true){lSVPRUDxrq = false;}
      if(aYuHeQsfRU == true){aYuHeQsfRU = false;}
      if(JNmkjiEDUs == true){JNmkjiEDUs = false;}
      if(rOJflakGEz == true){rOJflakGEz = false;}
      if(ZxcDjgJXrB == true){ZxcDjgJXrB = false;}
      if(wGlunYfkeh == true){wGlunYfkeh = false;}
      if(PAcyyMOOUD == true){PAcyyMOOUD = false;}
      if(flbStMjiAD == true){flbStMjiAD = false;}
      if(ZgKTwkbOrN == true){ZgKTwkbOrN = false;}
      if(uzaViYUdEX == true){uzaViYUdEX = false;}
      if(RuCnUJeSAb == true){RuCnUJeSAb = false;}
      if(nwkbIioICN == true){nwkbIioICN = false;}
      if(jAVGHgKGiV == true){jAVGHgKGiV = false;}
      if(qGebkedWyl == true){qGebkedWyl = false;}
      if(GJNQZzOzMA == true){GJNQZzOzMA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAEFCTTSMA
{ 
  void LdAXzoNpAG()
  { 
      bool WOAXGqDxuF = false;
      bool zUkmiMEOZb = false;
      bool MFXfzwDHeq = false;
      bool ADFIYQFZZr = false;
      bool urFwiCnlPl = false;
      bool ElwySQqTYJ = false;
      bool nuSDFwPcOS = false;
      bool HeohgUzbxx = false;
      bool IQrsmNGGpH = false;
      bool ZkBPEzYCpl = false;
      bool mKXxeYwORy = false;
      bool ROWaAWDZPq = false;
      bool oIlGrWdYcg = false;
      bool uxkKKxsuNO = false;
      bool QrorpLNZOh = false;
      bool wzlzxeYREI = false;
      bool tXkkCUcMQD = false;
      bool dILAZxStQg = false;
      bool IEJujwKlNe = false;
      bool YapFUsGDoU = false;
      string KwynYgdupI;
      string yaqhwEEfSV;
      string sDlGaTQbZt;
      string mFXSJqNzwN;
      string JCQeukJULa;
      string qeHacGKrMF;
      string QCVuUsDYYE;
      string pFiFMqlHKp;
      string JuPzCHxwoC;
      string fVlpxHgUJC;
      string gkwGjluCOl;
      string TDgWuUlVsN;
      string uHiWXUTsHE;
      string KRxHIYzIOP;
      string LugChcnOub;
      string UKawGZBZiP;
      string RCtJbCGZOW;
      string VdGcBAZfnu;
      string fFxfjzpBBh;
      string WYZzyJAWae;
      if(KwynYgdupI == gkwGjluCOl){WOAXGqDxuF = true;}
      else if(gkwGjluCOl == KwynYgdupI){mKXxeYwORy = true;}
      if(yaqhwEEfSV == TDgWuUlVsN){zUkmiMEOZb = true;}
      else if(TDgWuUlVsN == yaqhwEEfSV){ROWaAWDZPq = true;}
      if(sDlGaTQbZt == uHiWXUTsHE){MFXfzwDHeq = true;}
      else if(uHiWXUTsHE == sDlGaTQbZt){oIlGrWdYcg = true;}
      if(mFXSJqNzwN == KRxHIYzIOP){ADFIYQFZZr = true;}
      else if(KRxHIYzIOP == mFXSJqNzwN){uxkKKxsuNO = true;}
      if(JCQeukJULa == LugChcnOub){urFwiCnlPl = true;}
      else if(LugChcnOub == JCQeukJULa){QrorpLNZOh = true;}
      if(qeHacGKrMF == UKawGZBZiP){ElwySQqTYJ = true;}
      else if(UKawGZBZiP == qeHacGKrMF){wzlzxeYREI = true;}
      if(QCVuUsDYYE == RCtJbCGZOW){nuSDFwPcOS = true;}
      else if(RCtJbCGZOW == QCVuUsDYYE){tXkkCUcMQD = true;}
      if(pFiFMqlHKp == VdGcBAZfnu){HeohgUzbxx = true;}
      if(JuPzCHxwoC == fFxfjzpBBh){IQrsmNGGpH = true;}
      if(fVlpxHgUJC == WYZzyJAWae){ZkBPEzYCpl = true;}
      while(VdGcBAZfnu == pFiFMqlHKp){dILAZxStQg = true;}
      while(fFxfjzpBBh == fFxfjzpBBh){IEJujwKlNe = true;}
      while(WYZzyJAWae == WYZzyJAWae){YapFUsGDoU = true;}
      if(WOAXGqDxuF == true){WOAXGqDxuF = false;}
      if(zUkmiMEOZb == true){zUkmiMEOZb = false;}
      if(MFXfzwDHeq == true){MFXfzwDHeq = false;}
      if(ADFIYQFZZr == true){ADFIYQFZZr = false;}
      if(urFwiCnlPl == true){urFwiCnlPl = false;}
      if(ElwySQqTYJ == true){ElwySQqTYJ = false;}
      if(nuSDFwPcOS == true){nuSDFwPcOS = false;}
      if(HeohgUzbxx == true){HeohgUzbxx = false;}
      if(IQrsmNGGpH == true){IQrsmNGGpH = false;}
      if(ZkBPEzYCpl == true){ZkBPEzYCpl = false;}
      if(mKXxeYwORy == true){mKXxeYwORy = false;}
      if(ROWaAWDZPq == true){ROWaAWDZPq = false;}
      if(oIlGrWdYcg == true){oIlGrWdYcg = false;}
      if(uxkKKxsuNO == true){uxkKKxsuNO = false;}
      if(QrorpLNZOh == true){QrorpLNZOh = false;}
      if(wzlzxeYREI == true){wzlzxeYREI = false;}
      if(tXkkCUcMQD == true){tXkkCUcMQD = false;}
      if(dILAZxStQg == true){dILAZxStQg = false;}
      if(IEJujwKlNe == true){IEJujwKlNe = false;}
      if(YapFUsGDoU == true){YapFUsGDoU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WPHOWFCAED
{ 
  void PxAXRwzaDW()
  { 
      bool QajxohQNDy = false;
      bool JBitqAMkJE = false;
      bool YQHUhydaiU = false;
      bool yZmUHQcJwH = false;
      bool pZJwlcngQb = false;
      bool ffaZCzTPPp = false;
      bool DodhAjOOmZ = false;
      bool WCnBOyHKhE = false;
      bool JxKHoSzNSH = false;
      bool xNtFDAwbwC = false;
      bool OZtpFcqYKD = false;
      bool rJgKgGdWsg = false;
      bool kBuecJHhxO = false;
      bool CeNfpiCTCL = false;
      bool bZDOPmfjYx = false;
      bool VYhORNdPNu = false;
      bool UIbwAMuBUx = false;
      bool DKUgFKxgPo = false;
      bool cXJArdxyOb = false;
      bool FmGGqSyGNC = false;
      string GRiYGgafUu;
      string QQTdGmyuQn;
      string ZpmxISlsLx;
      string VIHEehbzIh;
      string WtAQYZrQKP;
      string bXCtwPekQm;
      string uhUXYIIPzX;
      string LyliRepVYh;
      string aUhuUyGNHO;
      string DpiVlnYcrP;
      string QbQmEdkScR;
      string ZILhLaAZDa;
      string CuIkTVOQwc;
      string FNdJRzEtpq;
      string MmjpnudBJL;
      string mzZQNUTfSi;
      string OTWzLMdCQM;
      string WFiLNOLRwY;
      string qNHkoGmMuw;
      string eXbHcsQkeb;
      if(GRiYGgafUu == QbQmEdkScR){QajxohQNDy = true;}
      else if(QbQmEdkScR == GRiYGgafUu){OZtpFcqYKD = true;}
      if(QQTdGmyuQn == ZILhLaAZDa){JBitqAMkJE = true;}
      else if(ZILhLaAZDa == QQTdGmyuQn){rJgKgGdWsg = true;}
      if(ZpmxISlsLx == CuIkTVOQwc){YQHUhydaiU = true;}
      else if(CuIkTVOQwc == ZpmxISlsLx){kBuecJHhxO = true;}
      if(VIHEehbzIh == FNdJRzEtpq){yZmUHQcJwH = true;}
      else if(FNdJRzEtpq == VIHEehbzIh){CeNfpiCTCL = true;}
      if(WtAQYZrQKP == MmjpnudBJL){pZJwlcngQb = true;}
      else if(MmjpnudBJL == WtAQYZrQKP){bZDOPmfjYx = true;}
      if(bXCtwPekQm == mzZQNUTfSi){ffaZCzTPPp = true;}
      else if(mzZQNUTfSi == bXCtwPekQm){VYhORNdPNu = true;}
      if(uhUXYIIPzX == OTWzLMdCQM){DodhAjOOmZ = true;}
      else if(OTWzLMdCQM == uhUXYIIPzX){UIbwAMuBUx = true;}
      if(LyliRepVYh == WFiLNOLRwY){WCnBOyHKhE = true;}
      if(aUhuUyGNHO == qNHkoGmMuw){JxKHoSzNSH = true;}
      if(DpiVlnYcrP == eXbHcsQkeb){xNtFDAwbwC = true;}
      while(WFiLNOLRwY == LyliRepVYh){DKUgFKxgPo = true;}
      while(qNHkoGmMuw == qNHkoGmMuw){cXJArdxyOb = true;}
      while(eXbHcsQkeb == eXbHcsQkeb){FmGGqSyGNC = true;}
      if(QajxohQNDy == true){QajxohQNDy = false;}
      if(JBitqAMkJE == true){JBitqAMkJE = false;}
      if(YQHUhydaiU == true){YQHUhydaiU = false;}
      if(yZmUHQcJwH == true){yZmUHQcJwH = false;}
      if(pZJwlcngQb == true){pZJwlcngQb = false;}
      if(ffaZCzTPPp == true){ffaZCzTPPp = false;}
      if(DodhAjOOmZ == true){DodhAjOOmZ = false;}
      if(WCnBOyHKhE == true){WCnBOyHKhE = false;}
      if(JxKHoSzNSH == true){JxKHoSzNSH = false;}
      if(xNtFDAwbwC == true){xNtFDAwbwC = false;}
      if(OZtpFcqYKD == true){OZtpFcqYKD = false;}
      if(rJgKgGdWsg == true){rJgKgGdWsg = false;}
      if(kBuecJHhxO == true){kBuecJHhxO = false;}
      if(CeNfpiCTCL == true){CeNfpiCTCL = false;}
      if(bZDOPmfjYx == true){bZDOPmfjYx = false;}
      if(VYhORNdPNu == true){VYhORNdPNu = false;}
      if(UIbwAMuBUx == true){UIbwAMuBUx = false;}
      if(DKUgFKxgPo == true){DKUgFKxgPo = false;}
      if(cXJArdxyOb == true){cXJArdxyOb = false;}
      if(FmGGqSyGNC == true){FmGGqSyGNC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KFAXNPBVOE
{ 
  void SAbGlwqWcP()
  { 
      bool ZXymbfNZVo = false;
      bool CifuEVlQxs = false;
      bool dWzQJaDNJm = false;
      bool CLcmZrkeKx = false;
      bool sOYjQUHepT = false;
      bool BNReoCXhcB = false;
      bool cAQimpGrVL = false;
      bool kHFzAPxPzo = false;
      bool SXXolntyyW = false;
      bool TCCJUrypwZ = false;
      bool OOIdisIRdY = false;
      bool EIhnhEcawz = false;
      bool wHtzqhFueI = false;
      bool QHSZZDPsGs = false;
      bool ebTYRLUNaP = false;
      bool OXtxdGUJlA = false;
      bool nMmVIxpINe = false;
      bool ojTDTTnUgf = false;
      bool NqUPssMUuS = false;
      bool hFGGESoxQT = false;
      string gixhAyBegt;
      string kziBWxNkiU;
      string iQLwLtCqKT;
      string LGYDlaRiMZ;
      string UNgAPUquhM;
      string BupQAQWAVG;
      string uJUMieZeOu;
      string eeYIAViKfq;
      string CGIxRPPHDU;
      string ERMFeLsURk;
      string uMgmhWWhQd;
      string hLUeEnAWtT;
      string ORatqNRSdo;
      string cOsuupZVOu;
      string rhqYmrxhBp;
      string KVZxVckmuU;
      string FEDbATSYiO;
      string NdHzagaBGz;
      string QiRmdHouYS;
      string EmatpndOYT;
      if(gixhAyBegt == uMgmhWWhQd){ZXymbfNZVo = true;}
      else if(uMgmhWWhQd == gixhAyBegt){OOIdisIRdY = true;}
      if(kziBWxNkiU == hLUeEnAWtT){CifuEVlQxs = true;}
      else if(hLUeEnAWtT == kziBWxNkiU){EIhnhEcawz = true;}
      if(iQLwLtCqKT == ORatqNRSdo){dWzQJaDNJm = true;}
      else if(ORatqNRSdo == iQLwLtCqKT){wHtzqhFueI = true;}
      if(LGYDlaRiMZ == cOsuupZVOu){CLcmZrkeKx = true;}
      else if(cOsuupZVOu == LGYDlaRiMZ){QHSZZDPsGs = true;}
      if(UNgAPUquhM == rhqYmrxhBp){sOYjQUHepT = true;}
      else if(rhqYmrxhBp == UNgAPUquhM){ebTYRLUNaP = true;}
      if(BupQAQWAVG == KVZxVckmuU){BNReoCXhcB = true;}
      else if(KVZxVckmuU == BupQAQWAVG){OXtxdGUJlA = true;}
      if(uJUMieZeOu == FEDbATSYiO){cAQimpGrVL = true;}
      else if(FEDbATSYiO == uJUMieZeOu){nMmVIxpINe = true;}
      if(eeYIAViKfq == NdHzagaBGz){kHFzAPxPzo = true;}
      if(CGIxRPPHDU == QiRmdHouYS){SXXolntyyW = true;}
      if(ERMFeLsURk == EmatpndOYT){TCCJUrypwZ = true;}
      while(NdHzagaBGz == eeYIAViKfq){ojTDTTnUgf = true;}
      while(QiRmdHouYS == QiRmdHouYS){NqUPssMUuS = true;}
      while(EmatpndOYT == EmatpndOYT){hFGGESoxQT = true;}
      if(ZXymbfNZVo == true){ZXymbfNZVo = false;}
      if(CifuEVlQxs == true){CifuEVlQxs = false;}
      if(dWzQJaDNJm == true){dWzQJaDNJm = false;}
      if(CLcmZrkeKx == true){CLcmZrkeKx = false;}
      if(sOYjQUHepT == true){sOYjQUHepT = false;}
      if(BNReoCXhcB == true){BNReoCXhcB = false;}
      if(cAQimpGrVL == true){cAQimpGrVL = false;}
      if(kHFzAPxPzo == true){kHFzAPxPzo = false;}
      if(SXXolntyyW == true){SXXolntyyW = false;}
      if(TCCJUrypwZ == true){TCCJUrypwZ = false;}
      if(OOIdisIRdY == true){OOIdisIRdY = false;}
      if(EIhnhEcawz == true){EIhnhEcawz = false;}
      if(wHtzqhFueI == true){wHtzqhFueI = false;}
      if(QHSZZDPsGs == true){QHSZZDPsGs = false;}
      if(ebTYRLUNaP == true){ebTYRLUNaP = false;}
      if(OXtxdGUJlA == true){OXtxdGUJlA = false;}
      if(nMmVIxpINe == true){nMmVIxpINe = false;}
      if(ojTDTTnUgf == true){ojTDTTnUgf = false;}
      if(NqUPssMUuS == true){NqUPssMUuS = false;}
      if(hFGGESoxQT == true){hFGGESoxQT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EEAAUNYUOR
{ 
  void VQCUWNfwbG()
  { 
      bool kwdckPPOeM = false;
      bool cmQoPEYSwk = false;
      bool AzJqicAcec = false;
      bool MOmgqVfZMB = false;
      bool rPOtlyOeVs = false;
      bool acMVTllmsH = false;
      bool OljBzOzjxs = false;
      bool XzFtsjjOEk = false;
      bool OVHkCjCQNF = false;
      bool jsfEmFfNuX = false;
      bool yehbVbWRci = false;
      bool BWhIssezzP = false;
      bool MiVqJeSBHn = false;
      bool EWTfljmePa = false;
      bool MkndDMKXLt = false;
      bool ZfNfLPIpRp = false;
      bool IVJoeeDCWJ = false;
      bool FAjYCbtqnx = false;
      bool TuoNNXInUV = false;
      bool awMYRpazzY = false;
      string RiVPDFkyBf;
      string JWDQLLuUKF;
      string iGdFhNjRhl;
      string XSsVNeXqeU;
      string LfySiWNUGA;
      string OTyIkKFPhp;
      string UTQOHqdhCg;
      string mEpptDHLVK;
      string APLgXEUjjC;
      string YHInzrOjKr;
      string sfRZNKcHOh;
      string DttXpFHiqD;
      string VsxAHeuBqB;
      string nXAcQTxlTN;
      string aMVCzeNkys;
      string kfrGVAhRRh;
      string ObQMtesQHV;
      string IUPcbJWuAc;
      string RKCxQIesHP;
      string leTlyzwIHT;
      if(RiVPDFkyBf == sfRZNKcHOh){kwdckPPOeM = true;}
      else if(sfRZNKcHOh == RiVPDFkyBf){yehbVbWRci = true;}
      if(JWDQLLuUKF == DttXpFHiqD){cmQoPEYSwk = true;}
      else if(DttXpFHiqD == JWDQLLuUKF){BWhIssezzP = true;}
      if(iGdFhNjRhl == VsxAHeuBqB){AzJqicAcec = true;}
      else if(VsxAHeuBqB == iGdFhNjRhl){MiVqJeSBHn = true;}
      if(XSsVNeXqeU == nXAcQTxlTN){MOmgqVfZMB = true;}
      else if(nXAcQTxlTN == XSsVNeXqeU){EWTfljmePa = true;}
      if(LfySiWNUGA == aMVCzeNkys){rPOtlyOeVs = true;}
      else if(aMVCzeNkys == LfySiWNUGA){MkndDMKXLt = true;}
      if(OTyIkKFPhp == kfrGVAhRRh){acMVTllmsH = true;}
      else if(kfrGVAhRRh == OTyIkKFPhp){ZfNfLPIpRp = true;}
      if(UTQOHqdhCg == ObQMtesQHV){OljBzOzjxs = true;}
      else if(ObQMtesQHV == UTQOHqdhCg){IVJoeeDCWJ = true;}
      if(mEpptDHLVK == IUPcbJWuAc){XzFtsjjOEk = true;}
      if(APLgXEUjjC == RKCxQIesHP){OVHkCjCQNF = true;}
      if(YHInzrOjKr == leTlyzwIHT){jsfEmFfNuX = true;}
      while(IUPcbJWuAc == mEpptDHLVK){FAjYCbtqnx = true;}
      while(RKCxQIesHP == RKCxQIesHP){TuoNNXInUV = true;}
      while(leTlyzwIHT == leTlyzwIHT){awMYRpazzY = true;}
      if(kwdckPPOeM == true){kwdckPPOeM = false;}
      if(cmQoPEYSwk == true){cmQoPEYSwk = false;}
      if(AzJqicAcec == true){AzJqicAcec = false;}
      if(MOmgqVfZMB == true){MOmgqVfZMB = false;}
      if(rPOtlyOeVs == true){rPOtlyOeVs = false;}
      if(acMVTllmsH == true){acMVTllmsH = false;}
      if(OljBzOzjxs == true){OljBzOzjxs = false;}
      if(XzFtsjjOEk == true){XzFtsjjOEk = false;}
      if(OVHkCjCQNF == true){OVHkCjCQNF = false;}
      if(jsfEmFfNuX == true){jsfEmFfNuX = false;}
      if(yehbVbWRci == true){yehbVbWRci = false;}
      if(BWhIssezzP == true){BWhIssezzP = false;}
      if(MiVqJeSBHn == true){MiVqJeSBHn = false;}
      if(EWTfljmePa == true){EWTfljmePa = false;}
      if(MkndDMKXLt == true){MkndDMKXLt = false;}
      if(ZfNfLPIpRp == true){ZfNfLPIpRp = false;}
      if(IVJoeeDCWJ == true){IVJoeeDCWJ = false;}
      if(FAjYCbtqnx == true){FAjYCbtqnx = false;}
      if(TuoNNXInUV == true){TuoNNXInUV = false;}
      if(awMYRpazzY == true){awMYRpazzY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JTILGBVLYG
{ 
  void JKlnoefTud()
  { 
      bool HMhlFIfHgY = false;
      bool bXodZFAuDo = false;
      bool wjXeEhJjdt = false;
      bool ASwgMfqiYK = false;
      bool PXPKxCXYSm = false;
      bool JEbsCXnDgX = false;
      bool zwclXIbHRs = false;
      bool ORWrZYUNgB = false;
      bool KkRqkwqCen = false;
      bool rnBBLStcmo = false;
      bool aPHYYqhiTd = false;
      bool DZVeMNekAb = false;
      bool RZccBZQUfG = false;
      bool dqaratcrSt = false;
      bool NHhAkRRVnx = false;
      bool nJbKWAldWy = false;
      bool ZMCMzMzdER = false;
      bool klSGNJqbqi = false;
      bool ItfiRUOPUZ = false;
      bool HzVUTBFVBY = false;
      string nQypqKBDZg;
      string MOLEfIZjnk;
      string gTyXMxQcVN;
      string ICABhULUVa;
      string KektMmNBSd;
      string xVTmqUSadt;
      string tYgLXKNJVK;
      string xENMZCiEKY;
      string iOJrQmhNJN;
      string CjqbgkxYVC;
      string ZDeHfrHGMo;
      string kOPEKePouj;
      string bzAIIMMlfo;
      string EJhIzejCLX;
      string faBUbnTmRB;
      string VIdlZZDWyT;
      string eVaWkbfHEf;
      string uMcWEBxegU;
      string sZUeTuewiZ;
      string aMDrrJAeiz;
      if(nQypqKBDZg == ZDeHfrHGMo){HMhlFIfHgY = true;}
      else if(ZDeHfrHGMo == nQypqKBDZg){aPHYYqhiTd = true;}
      if(MOLEfIZjnk == kOPEKePouj){bXodZFAuDo = true;}
      else if(kOPEKePouj == MOLEfIZjnk){DZVeMNekAb = true;}
      if(gTyXMxQcVN == bzAIIMMlfo){wjXeEhJjdt = true;}
      else if(bzAIIMMlfo == gTyXMxQcVN){RZccBZQUfG = true;}
      if(ICABhULUVa == EJhIzejCLX){ASwgMfqiYK = true;}
      else if(EJhIzejCLX == ICABhULUVa){dqaratcrSt = true;}
      if(KektMmNBSd == faBUbnTmRB){PXPKxCXYSm = true;}
      else if(faBUbnTmRB == KektMmNBSd){NHhAkRRVnx = true;}
      if(xVTmqUSadt == VIdlZZDWyT){JEbsCXnDgX = true;}
      else if(VIdlZZDWyT == xVTmqUSadt){nJbKWAldWy = true;}
      if(tYgLXKNJVK == eVaWkbfHEf){zwclXIbHRs = true;}
      else if(eVaWkbfHEf == tYgLXKNJVK){ZMCMzMzdER = true;}
      if(xENMZCiEKY == uMcWEBxegU){ORWrZYUNgB = true;}
      if(iOJrQmhNJN == sZUeTuewiZ){KkRqkwqCen = true;}
      if(CjqbgkxYVC == aMDrrJAeiz){rnBBLStcmo = true;}
      while(uMcWEBxegU == xENMZCiEKY){klSGNJqbqi = true;}
      while(sZUeTuewiZ == sZUeTuewiZ){ItfiRUOPUZ = true;}
      while(aMDrrJAeiz == aMDrrJAeiz){HzVUTBFVBY = true;}
      if(HMhlFIfHgY == true){HMhlFIfHgY = false;}
      if(bXodZFAuDo == true){bXodZFAuDo = false;}
      if(wjXeEhJjdt == true){wjXeEhJjdt = false;}
      if(ASwgMfqiYK == true){ASwgMfqiYK = false;}
      if(PXPKxCXYSm == true){PXPKxCXYSm = false;}
      if(JEbsCXnDgX == true){JEbsCXnDgX = false;}
      if(zwclXIbHRs == true){zwclXIbHRs = false;}
      if(ORWrZYUNgB == true){ORWrZYUNgB = false;}
      if(KkRqkwqCen == true){KkRqkwqCen = false;}
      if(rnBBLStcmo == true){rnBBLStcmo = false;}
      if(aPHYYqhiTd == true){aPHYYqhiTd = false;}
      if(DZVeMNekAb == true){DZVeMNekAb = false;}
      if(RZccBZQUfG == true){RZccBZQUfG = false;}
      if(dqaratcrSt == true){dqaratcrSt = false;}
      if(NHhAkRRVnx == true){NHhAkRRVnx = false;}
      if(nJbKWAldWy == true){nJbKWAldWy = false;}
      if(ZMCMzMzdER == true){ZMCMzMzdER = false;}
      if(klSGNJqbqi == true){klSGNJqbqi = false;}
      if(ItfiRUOPUZ == true){ItfiRUOPUZ = false;}
      if(HzVUTBFVBY == true){HzVUTBFVBY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UWXNZJCPOY
{ 
  void XRpOPcIaAU()
  { 
      bool YpZXqxeTOL = false;
      bool sbJecagbFK = false;
      bool etlwSsUOWV = false;
      bool qUNgqCFTtG = false;
      bool nTnuKhIsLo = false;
      bool ocnIEeEcEy = false;
      bool bPxrUXNbma = false;
      bool VNgzWLFqlk = false;
      bool kbDggNgFcM = false;
      bool xbPwdXVuZl = false;
      bool TfFjSbunkr = false;
      bool YMqSMALPLH = false;
      bool qHzactxkVy = false;
      bool oKRzREWTOF = false;
      bool SrTjmkkwic = false;
      bool LGjRuLgdGY = false;
      bool dKSmDOuqBI = false;
      bool drBGoynOnr = false;
      bool JBBrlhZzDF = false;
      bool XrMoaHYgfX = false;
      string EPwtMESHkU;
      string IjYhCNjolS;
      string aaDzrIQBgp;
      string SUINwnppAr;
      string UYMyLCAfxW;
      string GFxBicLxCE;
      string mQZtCmaKlO;
      string WtntxBNFmo;
      string IkDKjNXHeS;
      string bsnwEDyRwX;
      string bosizMRDDg;
      string PGJNuCNPKn;
      string PSfTmcFrot;
      string CuJPMSqULW;
      string uTDyDVjaAC;
      string piHHIIJZwV;
      string GYOJdTwsAc;
      string KsEmrwPgQQ;
      string reqlDTnCHD;
      string JRXoQWFtTi;
      if(EPwtMESHkU == bosizMRDDg){YpZXqxeTOL = true;}
      else if(bosizMRDDg == EPwtMESHkU){TfFjSbunkr = true;}
      if(IjYhCNjolS == PGJNuCNPKn){sbJecagbFK = true;}
      else if(PGJNuCNPKn == IjYhCNjolS){YMqSMALPLH = true;}
      if(aaDzrIQBgp == PSfTmcFrot){etlwSsUOWV = true;}
      else if(PSfTmcFrot == aaDzrIQBgp){qHzactxkVy = true;}
      if(SUINwnppAr == CuJPMSqULW){qUNgqCFTtG = true;}
      else if(CuJPMSqULW == SUINwnppAr){oKRzREWTOF = true;}
      if(UYMyLCAfxW == uTDyDVjaAC){nTnuKhIsLo = true;}
      else if(uTDyDVjaAC == UYMyLCAfxW){SrTjmkkwic = true;}
      if(GFxBicLxCE == piHHIIJZwV){ocnIEeEcEy = true;}
      else if(piHHIIJZwV == GFxBicLxCE){LGjRuLgdGY = true;}
      if(mQZtCmaKlO == GYOJdTwsAc){bPxrUXNbma = true;}
      else if(GYOJdTwsAc == mQZtCmaKlO){dKSmDOuqBI = true;}
      if(WtntxBNFmo == KsEmrwPgQQ){VNgzWLFqlk = true;}
      if(IkDKjNXHeS == reqlDTnCHD){kbDggNgFcM = true;}
      if(bsnwEDyRwX == JRXoQWFtTi){xbPwdXVuZl = true;}
      while(KsEmrwPgQQ == WtntxBNFmo){drBGoynOnr = true;}
      while(reqlDTnCHD == reqlDTnCHD){JBBrlhZzDF = true;}
      while(JRXoQWFtTi == JRXoQWFtTi){XrMoaHYgfX = true;}
      if(YpZXqxeTOL == true){YpZXqxeTOL = false;}
      if(sbJecagbFK == true){sbJecagbFK = false;}
      if(etlwSsUOWV == true){etlwSsUOWV = false;}
      if(qUNgqCFTtG == true){qUNgqCFTtG = false;}
      if(nTnuKhIsLo == true){nTnuKhIsLo = false;}
      if(ocnIEeEcEy == true){ocnIEeEcEy = false;}
      if(bPxrUXNbma == true){bPxrUXNbma = false;}
      if(VNgzWLFqlk == true){VNgzWLFqlk = false;}
      if(kbDggNgFcM == true){kbDggNgFcM = false;}
      if(xbPwdXVuZl == true){xbPwdXVuZl = false;}
      if(TfFjSbunkr == true){TfFjSbunkr = false;}
      if(YMqSMALPLH == true){YMqSMALPLH = false;}
      if(qHzactxkVy == true){qHzactxkVy = false;}
      if(oKRzREWTOF == true){oKRzREWTOF = false;}
      if(SrTjmkkwic == true){SrTjmkkwic = false;}
      if(LGjRuLgdGY == true){LGjRuLgdGY = false;}
      if(dKSmDOuqBI == true){dKSmDOuqBI = false;}
      if(drBGoynOnr == true){drBGoynOnr = false;}
      if(JBBrlhZzDF == true){JBBrlhZzDF = false;}
      if(XrMoaHYgfX == true){XrMoaHYgfX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MJPLTENMBF
{ 
  void fugTbnbYbS()
  { 
      bool eegdkejjUT = false;
      bool ZPpnzkjIBw = false;
      bool RfZbzHrnym = false;
      bool tilmfqWOOj = false;
      bool PIPMorVsXh = false;
      bool TqSqwzFEed = false;
      bool lukgYqdDHH = false;
      bool NUsRfIPMlG = false;
      bool lzPPSDPupg = false;
      bool lRjkyUWhny = false;
      bool ORkQUzyBKm = false;
      bool isSXqlfVOU = false;
      bool aiMaUukHTL = false;
      bool kgXmrTNzuT = false;
      bool FOjDxszLsL = false;
      bool oBTSWeEKuY = false;
      bool NpgzCBUffW = false;
      bool YfZuPMzJcb = false;
      bool wZNIWiNFPM = false;
      bool PDDWFOgkAu = false;
      string fWLhoZDZaj;
      string twMJQpnRAk;
      string eBdBmkjJua;
      string VTlXHBwDuS;
      string FfcypbnRWX;
      string BfxPsdrKuD;
      string otdAOZKnCP;
      string sjWhezXfKK;
      string xSmXZpWVdd;
      string IkIqcLCcjQ;
      string RzPGdQIOjt;
      string FMAjFWGFaY;
      string CnJXHIbeFT;
      string xuwtsyDfsI;
      string gIkjXwkXlF;
      string EwCLNcoqzV;
      string ocIQxKQFqH;
      string TZLRqtDYAL;
      string WDsAOAsjfP;
      string ILgXTEzUmN;
      if(fWLhoZDZaj == RzPGdQIOjt){eegdkejjUT = true;}
      else if(RzPGdQIOjt == fWLhoZDZaj){ORkQUzyBKm = true;}
      if(twMJQpnRAk == FMAjFWGFaY){ZPpnzkjIBw = true;}
      else if(FMAjFWGFaY == twMJQpnRAk){isSXqlfVOU = true;}
      if(eBdBmkjJua == CnJXHIbeFT){RfZbzHrnym = true;}
      else if(CnJXHIbeFT == eBdBmkjJua){aiMaUukHTL = true;}
      if(VTlXHBwDuS == xuwtsyDfsI){tilmfqWOOj = true;}
      else if(xuwtsyDfsI == VTlXHBwDuS){kgXmrTNzuT = true;}
      if(FfcypbnRWX == gIkjXwkXlF){PIPMorVsXh = true;}
      else if(gIkjXwkXlF == FfcypbnRWX){FOjDxszLsL = true;}
      if(BfxPsdrKuD == EwCLNcoqzV){TqSqwzFEed = true;}
      else if(EwCLNcoqzV == BfxPsdrKuD){oBTSWeEKuY = true;}
      if(otdAOZKnCP == ocIQxKQFqH){lukgYqdDHH = true;}
      else if(ocIQxKQFqH == otdAOZKnCP){NpgzCBUffW = true;}
      if(sjWhezXfKK == TZLRqtDYAL){NUsRfIPMlG = true;}
      if(xSmXZpWVdd == WDsAOAsjfP){lzPPSDPupg = true;}
      if(IkIqcLCcjQ == ILgXTEzUmN){lRjkyUWhny = true;}
      while(TZLRqtDYAL == sjWhezXfKK){YfZuPMzJcb = true;}
      while(WDsAOAsjfP == WDsAOAsjfP){wZNIWiNFPM = true;}
      while(ILgXTEzUmN == ILgXTEzUmN){PDDWFOgkAu = true;}
      if(eegdkejjUT == true){eegdkejjUT = false;}
      if(ZPpnzkjIBw == true){ZPpnzkjIBw = false;}
      if(RfZbzHrnym == true){RfZbzHrnym = false;}
      if(tilmfqWOOj == true){tilmfqWOOj = false;}
      if(PIPMorVsXh == true){PIPMorVsXh = false;}
      if(TqSqwzFEed == true){TqSqwzFEed = false;}
      if(lukgYqdDHH == true){lukgYqdDHH = false;}
      if(NUsRfIPMlG == true){NUsRfIPMlG = false;}
      if(lzPPSDPupg == true){lzPPSDPupg = false;}
      if(lRjkyUWhny == true){lRjkyUWhny = false;}
      if(ORkQUzyBKm == true){ORkQUzyBKm = false;}
      if(isSXqlfVOU == true){isSXqlfVOU = false;}
      if(aiMaUukHTL == true){aiMaUukHTL = false;}
      if(kgXmrTNzuT == true){kgXmrTNzuT = false;}
      if(FOjDxszLsL == true){FOjDxszLsL = false;}
      if(oBTSWeEKuY == true){oBTSWeEKuY = false;}
      if(NpgzCBUffW == true){NpgzCBUffW = false;}
      if(YfZuPMzJcb == true){YfZuPMzJcb = false;}
      if(wZNIWiNFPM == true){wZNIWiNFPM = false;}
      if(PDDWFOgkAu == true){PDDWFOgkAu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IIIDHKSTXV
{ 
  void hSFZKEBhVe()
  { 
      bool cKctYFUnfj = false;
      bool faBfAuAQIV = false;
      bool hbCLreqELc = false;
      bool KQxojDiRDm = false;
      bool BWIkEmeaYA = false;
      bool IBXImAIQCs = false;
      bool NPbCZOcMwx = false;
      bool LiMVUKSQHF = false;
      bool AQfLUIsoBi = false;
      bool tRPKYkuFLo = false;
      bool JReaoYoBnc = false;
      bool gqJwsxjPhR = false;
      bool VnLNCsTCxi = false;
      bool OMFRuilEVw = false;
      bool SqBXBDISQa = false;
      bool BeXsTVGQYu = false;
      bool FlEEOUkqBJ = false;
      bool LetlydmmLz = false;
      bool kAkVhioLyZ = false;
      bool bUeapgmwJg = false;
      string tdqVbhYCaW;
      string ryzPDOmzZJ;
      string HfUApoAYpQ;
      string OglWccePLW;
      string FZRjOUaXZs;
      string RPLDqOJqfl;
      string gzMJILMbmZ;
      string iWmDDgOjkV;
      string OczwyyUheO;
      string TnjYoFNHbD;
      string HykzJtbIAK;
      string AYFJWEzPLJ;
      string pewYGumONy;
      string SGHhNQrAmD;
      string WMhUOthZBk;
      string FxuSMcCLrN;
      string HNtBqsRWwG;
      string LzcHlcxaKM;
      string NMMcsVLoUj;
      string NfHYuJSfdV;
      if(tdqVbhYCaW == HykzJtbIAK){cKctYFUnfj = true;}
      else if(HykzJtbIAK == tdqVbhYCaW){JReaoYoBnc = true;}
      if(ryzPDOmzZJ == AYFJWEzPLJ){faBfAuAQIV = true;}
      else if(AYFJWEzPLJ == ryzPDOmzZJ){gqJwsxjPhR = true;}
      if(HfUApoAYpQ == pewYGumONy){hbCLreqELc = true;}
      else if(pewYGumONy == HfUApoAYpQ){VnLNCsTCxi = true;}
      if(OglWccePLW == SGHhNQrAmD){KQxojDiRDm = true;}
      else if(SGHhNQrAmD == OglWccePLW){OMFRuilEVw = true;}
      if(FZRjOUaXZs == WMhUOthZBk){BWIkEmeaYA = true;}
      else if(WMhUOthZBk == FZRjOUaXZs){SqBXBDISQa = true;}
      if(RPLDqOJqfl == FxuSMcCLrN){IBXImAIQCs = true;}
      else if(FxuSMcCLrN == RPLDqOJqfl){BeXsTVGQYu = true;}
      if(gzMJILMbmZ == HNtBqsRWwG){NPbCZOcMwx = true;}
      else if(HNtBqsRWwG == gzMJILMbmZ){FlEEOUkqBJ = true;}
      if(iWmDDgOjkV == LzcHlcxaKM){LiMVUKSQHF = true;}
      if(OczwyyUheO == NMMcsVLoUj){AQfLUIsoBi = true;}
      if(TnjYoFNHbD == NfHYuJSfdV){tRPKYkuFLo = true;}
      while(LzcHlcxaKM == iWmDDgOjkV){LetlydmmLz = true;}
      while(NMMcsVLoUj == NMMcsVLoUj){kAkVhioLyZ = true;}
      while(NfHYuJSfdV == NfHYuJSfdV){bUeapgmwJg = true;}
      if(cKctYFUnfj == true){cKctYFUnfj = false;}
      if(faBfAuAQIV == true){faBfAuAQIV = false;}
      if(hbCLreqELc == true){hbCLreqELc = false;}
      if(KQxojDiRDm == true){KQxojDiRDm = false;}
      if(BWIkEmeaYA == true){BWIkEmeaYA = false;}
      if(IBXImAIQCs == true){IBXImAIQCs = false;}
      if(NPbCZOcMwx == true){NPbCZOcMwx = false;}
      if(LiMVUKSQHF == true){LiMVUKSQHF = false;}
      if(AQfLUIsoBi == true){AQfLUIsoBi = false;}
      if(tRPKYkuFLo == true){tRPKYkuFLo = false;}
      if(JReaoYoBnc == true){JReaoYoBnc = false;}
      if(gqJwsxjPhR == true){gqJwsxjPhR = false;}
      if(VnLNCsTCxi == true){VnLNCsTCxi = false;}
      if(OMFRuilEVw == true){OMFRuilEVw = false;}
      if(SqBXBDISQa == true){SqBXBDISQa = false;}
      if(BeXsTVGQYu == true){BeXsTVGQYu = false;}
      if(FlEEOUkqBJ == true){FlEEOUkqBJ = false;}
      if(LetlydmmLz == true){LetlydmmLz = false;}
      if(kAkVhioLyZ == true){kAkVhioLyZ = false;}
      if(bUeapgmwJg == true){bUeapgmwJg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SYLWJDGCOA
{ 
  void hrFpHTRLzl()
  { 
      bool HoyGBzTblN = false;
      bool ENFpLyiIQK = false;
      bool xtXYdlzhoe = false;
      bool gIYAgMFoLc = false;
      bool JHOtMPxDkL = false;
      bool fqxWIMQZcO = false;
      bool AklHfuoEIy = false;
      bool sswmBpfdLO = false;
      bool ouxczpLCrU = false;
      bool weLwcYUHNR = false;
      bool ZrtmSltJUS = false;
      bool gmOOZEnJHp = false;
      bool ilMnCNhzKc = false;
      bool VXQtnxAKKN = false;
      bool wBgZmIQxWX = false;
      bool jLzWhneGjE = false;
      bool DtyrwIWUac = false;
      bool EdzttgFmAt = false;
      bool xjcmrJXsLA = false;
      bool RtZFJBDoce = false;
      string qNeeJRDojN;
      string SIljiJOtQy;
      string tDjwAJtqDP;
      string uTKVPKjASR;
      string VbGjwCNZwI;
      string IOXpimcheA;
      string XMlTRyyPUY;
      string YNaycSxzAx;
      string uTuuHfuTmb;
      string gCVStIpmRx;
      string ExEWjtmZMQ;
      string pchgEDQpLl;
      string CdcrrVrIDT;
      string bJgCryOXKM;
      string rVGVlDTnNp;
      string rzaftaUMeN;
      string CdVsnfweoG;
      string orfzsgWGGn;
      string CDuNbciBHQ;
      string cCsxKOzNhF;
      if(qNeeJRDojN == ExEWjtmZMQ){HoyGBzTblN = true;}
      else if(ExEWjtmZMQ == qNeeJRDojN){ZrtmSltJUS = true;}
      if(SIljiJOtQy == pchgEDQpLl){ENFpLyiIQK = true;}
      else if(pchgEDQpLl == SIljiJOtQy){gmOOZEnJHp = true;}
      if(tDjwAJtqDP == CdcrrVrIDT){xtXYdlzhoe = true;}
      else if(CdcrrVrIDT == tDjwAJtqDP){ilMnCNhzKc = true;}
      if(uTKVPKjASR == bJgCryOXKM){gIYAgMFoLc = true;}
      else if(bJgCryOXKM == uTKVPKjASR){VXQtnxAKKN = true;}
      if(VbGjwCNZwI == rVGVlDTnNp){JHOtMPxDkL = true;}
      else if(rVGVlDTnNp == VbGjwCNZwI){wBgZmIQxWX = true;}
      if(IOXpimcheA == rzaftaUMeN){fqxWIMQZcO = true;}
      else if(rzaftaUMeN == IOXpimcheA){jLzWhneGjE = true;}
      if(XMlTRyyPUY == CdVsnfweoG){AklHfuoEIy = true;}
      else if(CdVsnfweoG == XMlTRyyPUY){DtyrwIWUac = true;}
      if(YNaycSxzAx == orfzsgWGGn){sswmBpfdLO = true;}
      if(uTuuHfuTmb == CDuNbciBHQ){ouxczpLCrU = true;}
      if(gCVStIpmRx == cCsxKOzNhF){weLwcYUHNR = true;}
      while(orfzsgWGGn == YNaycSxzAx){EdzttgFmAt = true;}
      while(CDuNbciBHQ == CDuNbciBHQ){xjcmrJXsLA = true;}
      while(cCsxKOzNhF == cCsxKOzNhF){RtZFJBDoce = true;}
      if(HoyGBzTblN == true){HoyGBzTblN = false;}
      if(ENFpLyiIQK == true){ENFpLyiIQK = false;}
      if(xtXYdlzhoe == true){xtXYdlzhoe = false;}
      if(gIYAgMFoLc == true){gIYAgMFoLc = false;}
      if(JHOtMPxDkL == true){JHOtMPxDkL = false;}
      if(fqxWIMQZcO == true){fqxWIMQZcO = false;}
      if(AklHfuoEIy == true){AklHfuoEIy = false;}
      if(sswmBpfdLO == true){sswmBpfdLO = false;}
      if(ouxczpLCrU == true){ouxczpLCrU = false;}
      if(weLwcYUHNR == true){weLwcYUHNR = false;}
      if(ZrtmSltJUS == true){ZrtmSltJUS = false;}
      if(gmOOZEnJHp == true){gmOOZEnJHp = false;}
      if(ilMnCNhzKc == true){ilMnCNhzKc = false;}
      if(VXQtnxAKKN == true){VXQtnxAKKN = false;}
      if(wBgZmIQxWX == true){wBgZmIQxWX = false;}
      if(jLzWhneGjE == true){jLzWhneGjE = false;}
      if(DtyrwIWUac == true){DtyrwIWUac = false;}
      if(EdzttgFmAt == true){EdzttgFmAt = false;}
      if(xjcmrJXsLA == true){xjcmrJXsLA = false;}
      if(RtZFJBDoce == true){RtZFJBDoce = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DIDJXTULKA
{ 
  void mTuGxBeIwg()
  { 
      bool kmzMeWlLXA = false;
      bool YGmgdhdDxm = false;
      bool LlhKezuInV = false;
      bool AsPakoMsSF = false;
      bool JeHDxrFpzO = false;
      bool TFUOCyFnge = false;
      bool bdXCzeqMuo = false;
      bool UkjqdfddMl = false;
      bool tFIYBuYBYm = false;
      bool iYLmdeHFER = false;
      bool BstKtiVcjV = false;
      bool TaatkWVyBE = false;
      bool GpmIFwYwNy = false;
      bool YYZtkBKyeS = false;
      bool YwQCSIxQCH = false;
      bool JIEzLLFkEx = false;
      bool JYOlxuBfJj = false;
      bool LWTheJYkpx = false;
      bool zHtGoQTZiY = false;
      bool uZtgIzgeEW = false;
      string LlXtYQBAlH;
      string OKDbVDGqMf;
      string cDdbPUyCib;
      string oMZJPCYwyE;
      string gMlMgXUtxo;
      string wZeqTIIweD;
      string SyQJRCksMT;
      string eJrHzPQRtr;
      string ADEtePgioH;
      string tbRulhubte;
      string lbhdJlgWqE;
      string qpBlDOsWdC;
      string UCDFZCrxVR;
      string UoXOFXVajr;
      string hKqkPDZfqX;
      string oYxqKjYcDG;
      string tjBZiCSlge;
      string rRllTJKRoW;
      string bMFybwqfEV;
      string zsWdxyJRBN;
      if(LlXtYQBAlH == lbhdJlgWqE){kmzMeWlLXA = true;}
      else if(lbhdJlgWqE == LlXtYQBAlH){BstKtiVcjV = true;}
      if(OKDbVDGqMf == qpBlDOsWdC){YGmgdhdDxm = true;}
      else if(qpBlDOsWdC == OKDbVDGqMf){TaatkWVyBE = true;}
      if(cDdbPUyCib == UCDFZCrxVR){LlhKezuInV = true;}
      else if(UCDFZCrxVR == cDdbPUyCib){GpmIFwYwNy = true;}
      if(oMZJPCYwyE == UoXOFXVajr){AsPakoMsSF = true;}
      else if(UoXOFXVajr == oMZJPCYwyE){YYZtkBKyeS = true;}
      if(gMlMgXUtxo == hKqkPDZfqX){JeHDxrFpzO = true;}
      else if(hKqkPDZfqX == gMlMgXUtxo){YwQCSIxQCH = true;}
      if(wZeqTIIweD == oYxqKjYcDG){TFUOCyFnge = true;}
      else if(oYxqKjYcDG == wZeqTIIweD){JIEzLLFkEx = true;}
      if(SyQJRCksMT == tjBZiCSlge){bdXCzeqMuo = true;}
      else if(tjBZiCSlge == SyQJRCksMT){JYOlxuBfJj = true;}
      if(eJrHzPQRtr == rRllTJKRoW){UkjqdfddMl = true;}
      if(ADEtePgioH == bMFybwqfEV){tFIYBuYBYm = true;}
      if(tbRulhubte == zsWdxyJRBN){iYLmdeHFER = true;}
      while(rRllTJKRoW == eJrHzPQRtr){LWTheJYkpx = true;}
      while(bMFybwqfEV == bMFybwqfEV){zHtGoQTZiY = true;}
      while(zsWdxyJRBN == zsWdxyJRBN){uZtgIzgeEW = true;}
      if(kmzMeWlLXA == true){kmzMeWlLXA = false;}
      if(YGmgdhdDxm == true){YGmgdhdDxm = false;}
      if(LlhKezuInV == true){LlhKezuInV = false;}
      if(AsPakoMsSF == true){AsPakoMsSF = false;}
      if(JeHDxrFpzO == true){JeHDxrFpzO = false;}
      if(TFUOCyFnge == true){TFUOCyFnge = false;}
      if(bdXCzeqMuo == true){bdXCzeqMuo = false;}
      if(UkjqdfddMl == true){UkjqdfddMl = false;}
      if(tFIYBuYBYm == true){tFIYBuYBYm = false;}
      if(iYLmdeHFER == true){iYLmdeHFER = false;}
      if(BstKtiVcjV == true){BstKtiVcjV = false;}
      if(TaatkWVyBE == true){TaatkWVyBE = false;}
      if(GpmIFwYwNy == true){GpmIFwYwNy = false;}
      if(YYZtkBKyeS == true){YYZtkBKyeS = false;}
      if(YwQCSIxQCH == true){YwQCSIxQCH = false;}
      if(JIEzLLFkEx == true){JIEzLLFkEx = false;}
      if(JYOlxuBfJj == true){JYOlxuBfJj = false;}
      if(LWTheJYkpx == true){LWTheJYkpx = false;}
      if(zHtGoQTZiY == true){zHtGoQTZiY = false;}
      if(uZtgIzgeEW == true){uZtgIzgeEW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XIXQRPGSBV
{ 
  void krTRennges()
  { 
      bool wAunfOeCyR = false;
      bool SLPxQkySNM = false;
      bool DbYQQhDJXY = false;
      bool wRIjPcUesV = false;
      bool LMGLcEYZwA = false;
      bool iOGVVTbeXx = false;
      bool KVdZVBDfgn = false;
      bool QSZqBpUMmL = false;
      bool IdMXogKlNu = false;
      bool AoHuLpigob = false;
      bool BssHiQoOTe = false;
      bool zOqLofIFjo = false;
      bool pQRkmaLdfL = false;
      bool HnXLKPkEoY = false;
      bool qwRhwkxuGe = false;
      bool hcwAkjaHUH = false;
      bool ELiIXKqfBY = false;
      bool uDQLxtyinC = false;
      bool cPWBddrWZZ = false;
      bool ncjgTfNJKl = false;
      string qJaXxQtlzr;
      string cbOCEqkpZM;
      string VKsYDttCWl;
      string eejCRnfpbJ;
      string owXXzxsJSl;
      string WWjuUfPBTD;
      string VqPMMyqLkQ;
      string KuOPXYlVZG;
      string BkijOHtohk;
      string YdVXnxgKKA;
      string GgXCbaITXu;
      string tsbNBkHeyF;
      string ECdzrfYpbZ;
      string rbKZATNgIn;
      string zZQlqeCIWD;
      string oBMFwDDXKu;
      string CRrxDRhBMh;
      string WaWKGdkqIM;
      string dQTYjpOFcw;
      string QoWNlghTiY;
      if(qJaXxQtlzr == GgXCbaITXu){wAunfOeCyR = true;}
      else if(GgXCbaITXu == qJaXxQtlzr){BssHiQoOTe = true;}
      if(cbOCEqkpZM == tsbNBkHeyF){SLPxQkySNM = true;}
      else if(tsbNBkHeyF == cbOCEqkpZM){zOqLofIFjo = true;}
      if(VKsYDttCWl == ECdzrfYpbZ){DbYQQhDJXY = true;}
      else if(ECdzrfYpbZ == VKsYDttCWl){pQRkmaLdfL = true;}
      if(eejCRnfpbJ == rbKZATNgIn){wRIjPcUesV = true;}
      else if(rbKZATNgIn == eejCRnfpbJ){HnXLKPkEoY = true;}
      if(owXXzxsJSl == zZQlqeCIWD){LMGLcEYZwA = true;}
      else if(zZQlqeCIWD == owXXzxsJSl){qwRhwkxuGe = true;}
      if(WWjuUfPBTD == oBMFwDDXKu){iOGVVTbeXx = true;}
      else if(oBMFwDDXKu == WWjuUfPBTD){hcwAkjaHUH = true;}
      if(VqPMMyqLkQ == CRrxDRhBMh){KVdZVBDfgn = true;}
      else if(CRrxDRhBMh == VqPMMyqLkQ){ELiIXKqfBY = true;}
      if(KuOPXYlVZG == WaWKGdkqIM){QSZqBpUMmL = true;}
      if(BkijOHtohk == dQTYjpOFcw){IdMXogKlNu = true;}
      if(YdVXnxgKKA == QoWNlghTiY){AoHuLpigob = true;}
      while(WaWKGdkqIM == KuOPXYlVZG){uDQLxtyinC = true;}
      while(dQTYjpOFcw == dQTYjpOFcw){cPWBddrWZZ = true;}
      while(QoWNlghTiY == QoWNlghTiY){ncjgTfNJKl = true;}
      if(wAunfOeCyR == true){wAunfOeCyR = false;}
      if(SLPxQkySNM == true){SLPxQkySNM = false;}
      if(DbYQQhDJXY == true){DbYQQhDJXY = false;}
      if(wRIjPcUesV == true){wRIjPcUesV = false;}
      if(LMGLcEYZwA == true){LMGLcEYZwA = false;}
      if(iOGVVTbeXx == true){iOGVVTbeXx = false;}
      if(KVdZVBDfgn == true){KVdZVBDfgn = false;}
      if(QSZqBpUMmL == true){QSZqBpUMmL = false;}
      if(IdMXogKlNu == true){IdMXogKlNu = false;}
      if(AoHuLpigob == true){AoHuLpigob = false;}
      if(BssHiQoOTe == true){BssHiQoOTe = false;}
      if(zOqLofIFjo == true){zOqLofIFjo = false;}
      if(pQRkmaLdfL == true){pQRkmaLdfL = false;}
      if(HnXLKPkEoY == true){HnXLKPkEoY = false;}
      if(qwRhwkxuGe == true){qwRhwkxuGe = false;}
      if(hcwAkjaHUH == true){hcwAkjaHUH = false;}
      if(ELiIXKqfBY == true){ELiIXKqfBY = false;}
      if(uDQLxtyinC == true){uDQLxtyinC = false;}
      if(cPWBddrWZZ == true){cPWBddrWZZ = false;}
      if(ncjgTfNJKl == true){ncjgTfNJKl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DRMETUVMLY
{ 
  void VlmXLaPffe()
  { 
      bool ReapGZtfNl = false;
      bool DrgPgRNOMN = false;
      bool oEkWNPkOsL = false;
      bool ZfNJWCHbjc = false;
      bool ZbUVzWFRRP = false;
      bool cEoxKNsEcp = false;
      bool oemBMXeWre = false;
      bool KleinMjPWp = false;
      bool JSxciUpPyJ = false;
      bool ICysntoSJb = false;
      bool rhZlFpYFIx = false;
      bool ddglfWhKSq = false;
      bool gOYiWHmkut = false;
      bool XQGuybrKWr = false;
      bool ujGAfdVMMQ = false;
      bool LdzRtcJpPx = false;
      bool CnKOYMXlmE = false;
      bool dXmauwHXDr = false;
      bool laXdisQnAU = false;
      bool RCtYoHZraS = false;
      string SMmTJGMTVj;
      string NKyfuYuYgl;
      string EWoYidyTJw;
      string VSiZJLQzJt;
      string qspCpKKVhb;
      string ehpGVuWNke;
      string HrJZNtaXWi;
      string IwPluLglhX;
      string TblhQnccEN;
      string oDNdmzjQow;
      string jlzzThRELJ;
      string OjeNKeGbJY;
      string RyTItFhkyw;
      string bPxlnhcmNh;
      string WYQtzEXATI;
      string sHHPekSpEO;
      string zfFPhylsZc;
      string BSNaCrgZJo;
      string ghRpCTIhHC;
      string PlhzhqSBLA;
      if(SMmTJGMTVj == jlzzThRELJ){ReapGZtfNl = true;}
      else if(jlzzThRELJ == SMmTJGMTVj){rhZlFpYFIx = true;}
      if(NKyfuYuYgl == OjeNKeGbJY){DrgPgRNOMN = true;}
      else if(OjeNKeGbJY == NKyfuYuYgl){ddglfWhKSq = true;}
      if(EWoYidyTJw == RyTItFhkyw){oEkWNPkOsL = true;}
      else if(RyTItFhkyw == EWoYidyTJw){gOYiWHmkut = true;}
      if(VSiZJLQzJt == bPxlnhcmNh){ZfNJWCHbjc = true;}
      else if(bPxlnhcmNh == VSiZJLQzJt){XQGuybrKWr = true;}
      if(qspCpKKVhb == WYQtzEXATI){ZbUVzWFRRP = true;}
      else if(WYQtzEXATI == qspCpKKVhb){ujGAfdVMMQ = true;}
      if(ehpGVuWNke == sHHPekSpEO){cEoxKNsEcp = true;}
      else if(sHHPekSpEO == ehpGVuWNke){LdzRtcJpPx = true;}
      if(HrJZNtaXWi == zfFPhylsZc){oemBMXeWre = true;}
      else if(zfFPhylsZc == HrJZNtaXWi){CnKOYMXlmE = true;}
      if(IwPluLglhX == BSNaCrgZJo){KleinMjPWp = true;}
      if(TblhQnccEN == ghRpCTIhHC){JSxciUpPyJ = true;}
      if(oDNdmzjQow == PlhzhqSBLA){ICysntoSJb = true;}
      while(BSNaCrgZJo == IwPluLglhX){dXmauwHXDr = true;}
      while(ghRpCTIhHC == ghRpCTIhHC){laXdisQnAU = true;}
      while(PlhzhqSBLA == PlhzhqSBLA){RCtYoHZraS = true;}
      if(ReapGZtfNl == true){ReapGZtfNl = false;}
      if(DrgPgRNOMN == true){DrgPgRNOMN = false;}
      if(oEkWNPkOsL == true){oEkWNPkOsL = false;}
      if(ZfNJWCHbjc == true){ZfNJWCHbjc = false;}
      if(ZbUVzWFRRP == true){ZbUVzWFRRP = false;}
      if(cEoxKNsEcp == true){cEoxKNsEcp = false;}
      if(oemBMXeWre == true){oemBMXeWre = false;}
      if(KleinMjPWp == true){KleinMjPWp = false;}
      if(JSxciUpPyJ == true){JSxciUpPyJ = false;}
      if(ICysntoSJb == true){ICysntoSJb = false;}
      if(rhZlFpYFIx == true){rhZlFpYFIx = false;}
      if(ddglfWhKSq == true){ddglfWhKSq = false;}
      if(gOYiWHmkut == true){gOYiWHmkut = false;}
      if(XQGuybrKWr == true){XQGuybrKWr = false;}
      if(ujGAfdVMMQ == true){ujGAfdVMMQ = false;}
      if(LdzRtcJpPx == true){LdzRtcJpPx = false;}
      if(CnKOYMXlmE == true){CnKOYMXlmE = false;}
      if(dXmauwHXDr == true){dXmauwHXDr = false;}
      if(laXdisQnAU == true){laXdisQnAU = false;}
      if(RCtYoHZraS == true){RCtYoHZraS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CLHZJYGKTF
{ 
  void UoCTxTTfHA()
  { 
      bool siTZBKpySI = false;
      bool ZWNlsiBBGs = false;
      bool EjiSLPcEqZ = false;
      bool PQFcsUQctS = false;
      bool CyWcBrEUVo = false;
      bool rqNgzIzAOl = false;
      bool hkHrrIQjsY = false;
      bool SXHnpGNGRS = false;
      bool KIhCgYDXck = false;
      bool VPOIkRqdjr = false;
      bool aTbxVUiZqs = false;
      bool tsiuaYCEKT = false;
      bool FsHHCCJyCY = false;
      bool PjVYrqgkfM = false;
      bool pcgjqcgShL = false;
      bool OlSQmgMTtS = false;
      bool KkWRdKXJDi = false;
      bool rRYxcbMXQZ = false;
      bool VqQqJdQElL = false;
      bool dMpMCFFOFf = false;
      string zNDWIPqPit;
      string aLgDnOLrcT;
      string pLYHzEbQNT;
      string PHFlCLbSwS;
      string ktimkIphGs;
      string KFmqjmowWE;
      string naCPdTFtBb;
      string mswJiuckVp;
      string NsKTIJTNBO;
      string WeuqdKrTIR;
      string DugdGRJcIo;
      string JDZgqtPhGU;
      string zqslFIyEfX;
      string CJcEmRMfNq;
      string zpFMESENAi;
      string tKMmRLCtYx;
      string SFxjlAZVtZ;
      string hjUOUIlfgl;
      string DjDwcrwola;
      string ORHPXtrUaE;
      if(zNDWIPqPit == DugdGRJcIo){siTZBKpySI = true;}
      else if(DugdGRJcIo == zNDWIPqPit){aTbxVUiZqs = true;}
      if(aLgDnOLrcT == JDZgqtPhGU){ZWNlsiBBGs = true;}
      else if(JDZgqtPhGU == aLgDnOLrcT){tsiuaYCEKT = true;}
      if(pLYHzEbQNT == zqslFIyEfX){EjiSLPcEqZ = true;}
      else if(zqslFIyEfX == pLYHzEbQNT){FsHHCCJyCY = true;}
      if(PHFlCLbSwS == CJcEmRMfNq){PQFcsUQctS = true;}
      else if(CJcEmRMfNq == PHFlCLbSwS){PjVYrqgkfM = true;}
      if(ktimkIphGs == zpFMESENAi){CyWcBrEUVo = true;}
      else if(zpFMESENAi == ktimkIphGs){pcgjqcgShL = true;}
      if(KFmqjmowWE == tKMmRLCtYx){rqNgzIzAOl = true;}
      else if(tKMmRLCtYx == KFmqjmowWE){OlSQmgMTtS = true;}
      if(naCPdTFtBb == SFxjlAZVtZ){hkHrrIQjsY = true;}
      else if(SFxjlAZVtZ == naCPdTFtBb){KkWRdKXJDi = true;}
      if(mswJiuckVp == hjUOUIlfgl){SXHnpGNGRS = true;}
      if(NsKTIJTNBO == DjDwcrwola){KIhCgYDXck = true;}
      if(WeuqdKrTIR == ORHPXtrUaE){VPOIkRqdjr = true;}
      while(hjUOUIlfgl == mswJiuckVp){rRYxcbMXQZ = true;}
      while(DjDwcrwola == DjDwcrwola){VqQqJdQElL = true;}
      while(ORHPXtrUaE == ORHPXtrUaE){dMpMCFFOFf = true;}
      if(siTZBKpySI == true){siTZBKpySI = false;}
      if(ZWNlsiBBGs == true){ZWNlsiBBGs = false;}
      if(EjiSLPcEqZ == true){EjiSLPcEqZ = false;}
      if(PQFcsUQctS == true){PQFcsUQctS = false;}
      if(CyWcBrEUVo == true){CyWcBrEUVo = false;}
      if(rqNgzIzAOl == true){rqNgzIzAOl = false;}
      if(hkHrrIQjsY == true){hkHrrIQjsY = false;}
      if(SXHnpGNGRS == true){SXHnpGNGRS = false;}
      if(KIhCgYDXck == true){KIhCgYDXck = false;}
      if(VPOIkRqdjr == true){VPOIkRqdjr = false;}
      if(aTbxVUiZqs == true){aTbxVUiZqs = false;}
      if(tsiuaYCEKT == true){tsiuaYCEKT = false;}
      if(FsHHCCJyCY == true){FsHHCCJyCY = false;}
      if(PjVYrqgkfM == true){PjVYrqgkfM = false;}
      if(pcgjqcgShL == true){pcgjqcgShL = false;}
      if(OlSQmgMTtS == true){OlSQmgMTtS = false;}
      if(KkWRdKXJDi == true){KkWRdKXJDi = false;}
      if(rRYxcbMXQZ == true){rRYxcbMXQZ = false;}
      if(VqQqJdQElL == true){VqQqJdQElL = false;}
      if(dMpMCFFOFf == true){dMpMCFFOFf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JKDSLJLWMA
{ 
  void YINUhPhJVn()
  { 
      bool BockoVnJms = false;
      bool HCBYcPxrXd = false;
      bool suAARQXLjs = false;
      bool ayoHhDOFza = false;
      bool FbzuenjRpi = false;
      bool aWMRIGocTX = false;
      bool ycZsSINtpZ = false;
      bool ArrxYRuEUc = false;
      bool gFVBSElWzb = false;
      bool NllbbcBGcW = false;
      bool apaQhhdOrq = false;
      bool KkHpprHYZO = false;
      bool VpuOLOGQUw = false;
      bool PobyCqeETk = false;
      bool ZWdIQcdukj = false;
      bool UcfNAkuLES = false;
      bool aMtwaUIJnz = false;
      bool NCFnnyLlxi = false;
      bool kLejalINxR = false;
      bool wSAAKMbhgu = false;
      string QdUGezPDfi;
      string xaLApQxyaI;
      string EwaMgXtduY;
      string UAhANMAHkz;
      string gylySXDqEK;
      string EkpbsUCHZG;
      string FkHHOwsLlc;
      string PpNbbFJbtI;
      string UDZkTjKFHs;
      string JrhetuqejV;
      string eqEatOWOAm;
      string KZNQkBLWme;
      string lnErSXIigf;
      string OerYdcyypE;
      string MwEThjeQsr;
      string iUrFipmLHW;
      string GngUXfhomH;
      string DNfhRpijJi;
      string sqpnwtlmom;
      string plpTyXOjuC;
      if(QdUGezPDfi == eqEatOWOAm){BockoVnJms = true;}
      else if(eqEatOWOAm == QdUGezPDfi){apaQhhdOrq = true;}
      if(xaLApQxyaI == KZNQkBLWme){HCBYcPxrXd = true;}
      else if(KZNQkBLWme == xaLApQxyaI){KkHpprHYZO = true;}
      if(EwaMgXtduY == lnErSXIigf){suAARQXLjs = true;}
      else if(lnErSXIigf == EwaMgXtduY){VpuOLOGQUw = true;}
      if(UAhANMAHkz == OerYdcyypE){ayoHhDOFza = true;}
      else if(OerYdcyypE == UAhANMAHkz){PobyCqeETk = true;}
      if(gylySXDqEK == MwEThjeQsr){FbzuenjRpi = true;}
      else if(MwEThjeQsr == gylySXDqEK){ZWdIQcdukj = true;}
      if(EkpbsUCHZG == iUrFipmLHW){aWMRIGocTX = true;}
      else if(iUrFipmLHW == EkpbsUCHZG){UcfNAkuLES = true;}
      if(FkHHOwsLlc == GngUXfhomH){ycZsSINtpZ = true;}
      else if(GngUXfhomH == FkHHOwsLlc){aMtwaUIJnz = true;}
      if(PpNbbFJbtI == DNfhRpijJi){ArrxYRuEUc = true;}
      if(UDZkTjKFHs == sqpnwtlmom){gFVBSElWzb = true;}
      if(JrhetuqejV == plpTyXOjuC){NllbbcBGcW = true;}
      while(DNfhRpijJi == PpNbbFJbtI){NCFnnyLlxi = true;}
      while(sqpnwtlmom == sqpnwtlmom){kLejalINxR = true;}
      while(plpTyXOjuC == plpTyXOjuC){wSAAKMbhgu = true;}
      if(BockoVnJms == true){BockoVnJms = false;}
      if(HCBYcPxrXd == true){HCBYcPxrXd = false;}
      if(suAARQXLjs == true){suAARQXLjs = false;}
      if(ayoHhDOFza == true){ayoHhDOFza = false;}
      if(FbzuenjRpi == true){FbzuenjRpi = false;}
      if(aWMRIGocTX == true){aWMRIGocTX = false;}
      if(ycZsSINtpZ == true){ycZsSINtpZ = false;}
      if(ArrxYRuEUc == true){ArrxYRuEUc = false;}
      if(gFVBSElWzb == true){gFVBSElWzb = false;}
      if(NllbbcBGcW == true){NllbbcBGcW = false;}
      if(apaQhhdOrq == true){apaQhhdOrq = false;}
      if(KkHpprHYZO == true){KkHpprHYZO = false;}
      if(VpuOLOGQUw == true){VpuOLOGQUw = false;}
      if(PobyCqeETk == true){PobyCqeETk = false;}
      if(ZWdIQcdukj == true){ZWdIQcdukj = false;}
      if(UcfNAkuLES == true){UcfNAkuLES = false;}
      if(aMtwaUIJnz == true){aMtwaUIJnz = false;}
      if(NCFnnyLlxi == true){NCFnnyLlxi = false;}
      if(kLejalINxR == true){kLejalINxR = false;}
      if(wSAAKMbhgu == true){wSAAKMbhgu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WQUJNNZLSX
{ 
  void VwVYDTyYlo()
  { 
      bool nRtLItwwdM = false;
      bool EgZjUoyurT = false;
      bool EzBdCMcOFd = false;
      bool RhwfwtXnAI = false;
      bool TNwOnrGAqF = false;
      bool FJonpoPPIu = false;
      bool QgpAuWksma = false;
      bool RKtiAqCmpK = false;
      bool GbXzYHrIpH = false;
      bool eHfEqlWwTQ = false;
      bool GMNPnuOGmz = false;
      bool lcZxooJqam = false;
      bool dcDfwJeprO = false;
      bool TFSYEsOHKd = false;
      bool rlUpUBhhPC = false;
      bool beUfldJgTe = false;
      bool QYNYegJBsu = false;
      bool aBgxtrHMKt = false;
      bool bwZolojllZ = false;
      bool jgnfNTXwLn = false;
      string nEcWNCQLWN;
      string xycOEsuTMH;
      string ZLGJLiKWJW;
      string olYSEbDLFV;
      string UsCVelqsxc;
      string bAIqDcyTKe;
      string rsBAYLZKKc;
      string pjOplfIjeZ;
      string qQZgunchOb;
      string cjBadbrCwS;
      string MgiTmqlRFX;
      string TNojmaTUFj;
      string hruhzGimMK;
      string mGmLNKgFsD;
      string CKbqHOtQnC;
      string HXxMjUkAUg;
      string HyFtjNacWb;
      string sNaBhXPDak;
      string LRzJCPJabr;
      string YfkMuDFgHt;
      if(nEcWNCQLWN == MgiTmqlRFX){nRtLItwwdM = true;}
      else if(MgiTmqlRFX == nEcWNCQLWN){GMNPnuOGmz = true;}
      if(xycOEsuTMH == TNojmaTUFj){EgZjUoyurT = true;}
      else if(TNojmaTUFj == xycOEsuTMH){lcZxooJqam = true;}
      if(ZLGJLiKWJW == hruhzGimMK){EzBdCMcOFd = true;}
      else if(hruhzGimMK == ZLGJLiKWJW){dcDfwJeprO = true;}
      if(olYSEbDLFV == mGmLNKgFsD){RhwfwtXnAI = true;}
      else if(mGmLNKgFsD == olYSEbDLFV){TFSYEsOHKd = true;}
      if(UsCVelqsxc == CKbqHOtQnC){TNwOnrGAqF = true;}
      else if(CKbqHOtQnC == UsCVelqsxc){rlUpUBhhPC = true;}
      if(bAIqDcyTKe == HXxMjUkAUg){FJonpoPPIu = true;}
      else if(HXxMjUkAUg == bAIqDcyTKe){beUfldJgTe = true;}
      if(rsBAYLZKKc == HyFtjNacWb){QgpAuWksma = true;}
      else if(HyFtjNacWb == rsBAYLZKKc){QYNYegJBsu = true;}
      if(pjOplfIjeZ == sNaBhXPDak){RKtiAqCmpK = true;}
      if(qQZgunchOb == LRzJCPJabr){GbXzYHrIpH = true;}
      if(cjBadbrCwS == YfkMuDFgHt){eHfEqlWwTQ = true;}
      while(sNaBhXPDak == pjOplfIjeZ){aBgxtrHMKt = true;}
      while(LRzJCPJabr == LRzJCPJabr){bwZolojllZ = true;}
      while(YfkMuDFgHt == YfkMuDFgHt){jgnfNTXwLn = true;}
      if(nRtLItwwdM == true){nRtLItwwdM = false;}
      if(EgZjUoyurT == true){EgZjUoyurT = false;}
      if(EzBdCMcOFd == true){EzBdCMcOFd = false;}
      if(RhwfwtXnAI == true){RhwfwtXnAI = false;}
      if(TNwOnrGAqF == true){TNwOnrGAqF = false;}
      if(FJonpoPPIu == true){FJonpoPPIu = false;}
      if(QgpAuWksma == true){QgpAuWksma = false;}
      if(RKtiAqCmpK == true){RKtiAqCmpK = false;}
      if(GbXzYHrIpH == true){GbXzYHrIpH = false;}
      if(eHfEqlWwTQ == true){eHfEqlWwTQ = false;}
      if(GMNPnuOGmz == true){GMNPnuOGmz = false;}
      if(lcZxooJqam == true){lcZxooJqam = false;}
      if(dcDfwJeprO == true){dcDfwJeprO = false;}
      if(TFSYEsOHKd == true){TFSYEsOHKd = false;}
      if(rlUpUBhhPC == true){rlUpUBhhPC = false;}
      if(beUfldJgTe == true){beUfldJgTe = false;}
      if(QYNYegJBsu == true){QYNYegJBsu = false;}
      if(aBgxtrHMKt == true){aBgxtrHMKt = false;}
      if(bwZolojllZ == true){bwZolojllZ = false;}
      if(jgnfNTXwLn == true){jgnfNTXwLn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KAMLYVBHKH
{ 
  void EXHoLqnuPJ()
  { 
      bool lYjnqodYPC = false;
      bool rpZMlLrXdl = false;
      bool uNLrnwRJnL = false;
      bool CHuudEOBcD = false;
      bool btaUmJwgiZ = false;
      bool faRRFYNqzu = false;
      bool WUjEAjteih = false;
      bool xquaKBlqFd = false;
      bool zkZNebpdoE = false;
      bool qWBgfHJWUC = false;
      bool ORxBcoepGE = false;
      bool lVlVwktVYX = false;
      bool tQodpaoNuC = false;
      bool qOWCOgmYko = false;
      bool wAWkRUjfku = false;
      bool NmxwHybTKC = false;
      bool AQuEMXzjGO = false;
      bool xVkibtsELV = false;
      bool pIcAoDQatQ = false;
      bool ETNioeFSXt = false;
      string MNIFXLWzUZ;
      string zaPXVzIfQs;
      string crdcOSUkrl;
      string bpWLPZxxKN;
      string TiEqFVqqfE;
      string aVZoDTjfqF;
      string plGhyIDEHw;
      string CLVCZsnlWs;
      string bdEnLGPhHu;
      string oQFEXgcVsw;
      string RliiBPzXOK;
      string fyIycMgSWr;
      string sVwMHkFQer;
      string QRrZaotVlw;
      string HrSxPqHHbK;
      string AKzBDuoWbQ;
      string JhsWsNFhXn;
      string SLfakBDzwP;
      string dyoUrGSqWe;
      string zWsVlYywDB;
      if(MNIFXLWzUZ == RliiBPzXOK){lYjnqodYPC = true;}
      else if(RliiBPzXOK == MNIFXLWzUZ){ORxBcoepGE = true;}
      if(zaPXVzIfQs == fyIycMgSWr){rpZMlLrXdl = true;}
      else if(fyIycMgSWr == zaPXVzIfQs){lVlVwktVYX = true;}
      if(crdcOSUkrl == sVwMHkFQer){uNLrnwRJnL = true;}
      else if(sVwMHkFQer == crdcOSUkrl){tQodpaoNuC = true;}
      if(bpWLPZxxKN == QRrZaotVlw){CHuudEOBcD = true;}
      else if(QRrZaotVlw == bpWLPZxxKN){qOWCOgmYko = true;}
      if(TiEqFVqqfE == HrSxPqHHbK){btaUmJwgiZ = true;}
      else if(HrSxPqHHbK == TiEqFVqqfE){wAWkRUjfku = true;}
      if(aVZoDTjfqF == AKzBDuoWbQ){faRRFYNqzu = true;}
      else if(AKzBDuoWbQ == aVZoDTjfqF){NmxwHybTKC = true;}
      if(plGhyIDEHw == JhsWsNFhXn){WUjEAjteih = true;}
      else if(JhsWsNFhXn == plGhyIDEHw){AQuEMXzjGO = true;}
      if(CLVCZsnlWs == SLfakBDzwP){xquaKBlqFd = true;}
      if(bdEnLGPhHu == dyoUrGSqWe){zkZNebpdoE = true;}
      if(oQFEXgcVsw == zWsVlYywDB){qWBgfHJWUC = true;}
      while(SLfakBDzwP == CLVCZsnlWs){xVkibtsELV = true;}
      while(dyoUrGSqWe == dyoUrGSqWe){pIcAoDQatQ = true;}
      while(zWsVlYywDB == zWsVlYywDB){ETNioeFSXt = true;}
      if(lYjnqodYPC == true){lYjnqodYPC = false;}
      if(rpZMlLrXdl == true){rpZMlLrXdl = false;}
      if(uNLrnwRJnL == true){uNLrnwRJnL = false;}
      if(CHuudEOBcD == true){CHuudEOBcD = false;}
      if(btaUmJwgiZ == true){btaUmJwgiZ = false;}
      if(faRRFYNqzu == true){faRRFYNqzu = false;}
      if(WUjEAjteih == true){WUjEAjteih = false;}
      if(xquaKBlqFd == true){xquaKBlqFd = false;}
      if(zkZNebpdoE == true){zkZNebpdoE = false;}
      if(qWBgfHJWUC == true){qWBgfHJWUC = false;}
      if(ORxBcoepGE == true){ORxBcoepGE = false;}
      if(lVlVwktVYX == true){lVlVwktVYX = false;}
      if(tQodpaoNuC == true){tQodpaoNuC = false;}
      if(qOWCOgmYko == true){qOWCOgmYko = false;}
      if(wAWkRUjfku == true){wAWkRUjfku = false;}
      if(NmxwHybTKC == true){NmxwHybTKC = false;}
      if(AQuEMXzjGO == true){AQuEMXzjGO = false;}
      if(xVkibtsELV == true){xVkibtsELV = false;}
      if(pIcAoDQatQ == true){pIcAoDQatQ = false;}
      if(ETNioeFSXt == true){ETNioeFSXt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IRVGRZQCWZ
{ 
  void TfSPKJxKIu()
  { 
      bool TLRMIdGbnP = false;
      bool LGnEPRmgko = false;
      bool MMkTfaMErB = false;
      bool nJUBHJYSyn = false;
      bool JogmnDBjGg = false;
      bool JEbdVGZyfg = false;
      bool RBjmaCkmxG = false;
      bool sTixfXexfc = false;
      bool ZcyLqjgqeA = false;
      bool jalRWHFtMl = false;
      bool ROlAnpVeyy = false;
      bool abSDHoDXuq = false;
      bool UtHwVSgQaX = false;
      bool RkktKLpxXB = false;
      bool OCrgZHHiJg = false;
      bool EgyVQWGpdV = false;
      bool IEDafppYrw = false;
      bool yFAtbSCZWN = false;
      bool KyHsSklPcn = false;
      bool EATCrJyQBi = false;
      string kgrxYoFTng;
      string CeeUICKxCA;
      string eQjZoLbGWt;
      string CEUrwnzuNR;
      string APMdohwscI;
      string AkHBRTwRIM;
      string NzxseyJmYU;
      string COjkzPEGjG;
      string PhcNsQwTZb;
      string qhmAEBRSzq;
      string YIUIFkBVBC;
      string PohBxeVjzN;
      string BoMwcUbigx;
      string xkHshGNUHI;
      string PaRXMBzkDZ;
      string ehTlpiwXfk;
      string JSoDEdhnSp;
      string QBbqxZXoja;
      string UqfHSPRVDz;
      string KooWywlNTh;
      if(kgrxYoFTng == YIUIFkBVBC){TLRMIdGbnP = true;}
      else if(YIUIFkBVBC == kgrxYoFTng){ROlAnpVeyy = true;}
      if(CeeUICKxCA == PohBxeVjzN){LGnEPRmgko = true;}
      else if(PohBxeVjzN == CeeUICKxCA){abSDHoDXuq = true;}
      if(eQjZoLbGWt == BoMwcUbigx){MMkTfaMErB = true;}
      else if(BoMwcUbigx == eQjZoLbGWt){UtHwVSgQaX = true;}
      if(CEUrwnzuNR == xkHshGNUHI){nJUBHJYSyn = true;}
      else if(xkHshGNUHI == CEUrwnzuNR){RkktKLpxXB = true;}
      if(APMdohwscI == PaRXMBzkDZ){JogmnDBjGg = true;}
      else if(PaRXMBzkDZ == APMdohwscI){OCrgZHHiJg = true;}
      if(AkHBRTwRIM == ehTlpiwXfk){JEbdVGZyfg = true;}
      else if(ehTlpiwXfk == AkHBRTwRIM){EgyVQWGpdV = true;}
      if(NzxseyJmYU == JSoDEdhnSp){RBjmaCkmxG = true;}
      else if(JSoDEdhnSp == NzxseyJmYU){IEDafppYrw = true;}
      if(COjkzPEGjG == QBbqxZXoja){sTixfXexfc = true;}
      if(PhcNsQwTZb == UqfHSPRVDz){ZcyLqjgqeA = true;}
      if(qhmAEBRSzq == KooWywlNTh){jalRWHFtMl = true;}
      while(QBbqxZXoja == COjkzPEGjG){yFAtbSCZWN = true;}
      while(UqfHSPRVDz == UqfHSPRVDz){KyHsSklPcn = true;}
      while(KooWywlNTh == KooWywlNTh){EATCrJyQBi = true;}
      if(TLRMIdGbnP == true){TLRMIdGbnP = false;}
      if(LGnEPRmgko == true){LGnEPRmgko = false;}
      if(MMkTfaMErB == true){MMkTfaMErB = false;}
      if(nJUBHJYSyn == true){nJUBHJYSyn = false;}
      if(JogmnDBjGg == true){JogmnDBjGg = false;}
      if(JEbdVGZyfg == true){JEbdVGZyfg = false;}
      if(RBjmaCkmxG == true){RBjmaCkmxG = false;}
      if(sTixfXexfc == true){sTixfXexfc = false;}
      if(ZcyLqjgqeA == true){ZcyLqjgqeA = false;}
      if(jalRWHFtMl == true){jalRWHFtMl = false;}
      if(ROlAnpVeyy == true){ROlAnpVeyy = false;}
      if(abSDHoDXuq == true){abSDHoDXuq = false;}
      if(UtHwVSgQaX == true){UtHwVSgQaX = false;}
      if(RkktKLpxXB == true){RkktKLpxXB = false;}
      if(OCrgZHHiJg == true){OCrgZHHiJg = false;}
      if(EgyVQWGpdV == true){EgyVQWGpdV = false;}
      if(IEDafppYrw == true){IEDafppYrw = false;}
      if(yFAtbSCZWN == true){yFAtbSCZWN = false;}
      if(KyHsSklPcn == true){KyHsSklPcn = false;}
      if(EATCrJyQBi == true){EATCrJyQBi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FFYEFMIKNS
{ 
  void pxUcQtHyCh()
  { 
      bool kWhoDQlJGo = false;
      bool MmpYxBpNxc = false;
      bool KEEkNrVOqR = false;
      bool GTkYsiQhFl = false;
      bool WqRQpmCWxV = false;
      bool xRyaLgSxaK = false;
      bool tWRnhsBRfN = false;
      bool kHHKGSlmua = false;
      bool ozRVUoVJMM = false;
      bool QSGtqzYdhw = false;
      bool kkpijoJmUs = false;
      bool teCAUuEwTs = false;
      bool WqETwRBNSG = false;
      bool sHEypEJhke = false;
      bool ehoTRlPGYw = false;
      bool tcKoYsgWmR = false;
      bool nwTNzlaEJQ = false;
      bool kWKnNnCjBK = false;
      bool BtnVLQxOYw = false;
      bool WluSqhNaUe = false;
      string qXIhqLVfIj;
      string HCkbPVjBVB;
      string yZDUxkBIma;
      string HxJYiwLZcQ;
      string NtqxYfWHOA;
      string goaasRUmjG;
      string JMsgbKsLsS;
      string KKXFnEhGwR;
      string NstmtSWheQ;
      string bXoVGBAKUO;
      string lKOuoVQUmo;
      string iNqSrQRGlI;
      string mKgcqlUBym;
      string DXkgeDezxX;
      string CBupgNfVdo;
      string itXMabdkDD;
      string AOVAlKcJnn;
      string lSIOGlOpud;
      string FzXIDIAYFC;
      string ZswtWneuEV;
      if(qXIhqLVfIj == lKOuoVQUmo){kWhoDQlJGo = true;}
      else if(lKOuoVQUmo == qXIhqLVfIj){kkpijoJmUs = true;}
      if(HCkbPVjBVB == iNqSrQRGlI){MmpYxBpNxc = true;}
      else if(iNqSrQRGlI == HCkbPVjBVB){teCAUuEwTs = true;}
      if(yZDUxkBIma == mKgcqlUBym){KEEkNrVOqR = true;}
      else if(mKgcqlUBym == yZDUxkBIma){WqETwRBNSG = true;}
      if(HxJYiwLZcQ == DXkgeDezxX){GTkYsiQhFl = true;}
      else if(DXkgeDezxX == HxJYiwLZcQ){sHEypEJhke = true;}
      if(NtqxYfWHOA == CBupgNfVdo){WqRQpmCWxV = true;}
      else if(CBupgNfVdo == NtqxYfWHOA){ehoTRlPGYw = true;}
      if(goaasRUmjG == itXMabdkDD){xRyaLgSxaK = true;}
      else if(itXMabdkDD == goaasRUmjG){tcKoYsgWmR = true;}
      if(JMsgbKsLsS == AOVAlKcJnn){tWRnhsBRfN = true;}
      else if(AOVAlKcJnn == JMsgbKsLsS){nwTNzlaEJQ = true;}
      if(KKXFnEhGwR == lSIOGlOpud){kHHKGSlmua = true;}
      if(NstmtSWheQ == FzXIDIAYFC){ozRVUoVJMM = true;}
      if(bXoVGBAKUO == ZswtWneuEV){QSGtqzYdhw = true;}
      while(lSIOGlOpud == KKXFnEhGwR){kWKnNnCjBK = true;}
      while(FzXIDIAYFC == FzXIDIAYFC){BtnVLQxOYw = true;}
      while(ZswtWneuEV == ZswtWneuEV){WluSqhNaUe = true;}
      if(kWhoDQlJGo == true){kWhoDQlJGo = false;}
      if(MmpYxBpNxc == true){MmpYxBpNxc = false;}
      if(KEEkNrVOqR == true){KEEkNrVOqR = false;}
      if(GTkYsiQhFl == true){GTkYsiQhFl = false;}
      if(WqRQpmCWxV == true){WqRQpmCWxV = false;}
      if(xRyaLgSxaK == true){xRyaLgSxaK = false;}
      if(tWRnhsBRfN == true){tWRnhsBRfN = false;}
      if(kHHKGSlmua == true){kHHKGSlmua = false;}
      if(ozRVUoVJMM == true){ozRVUoVJMM = false;}
      if(QSGtqzYdhw == true){QSGtqzYdhw = false;}
      if(kkpijoJmUs == true){kkpijoJmUs = false;}
      if(teCAUuEwTs == true){teCAUuEwTs = false;}
      if(WqETwRBNSG == true){WqETwRBNSG = false;}
      if(sHEypEJhke == true){sHEypEJhke = false;}
      if(ehoTRlPGYw == true){ehoTRlPGYw = false;}
      if(tcKoYsgWmR == true){tcKoYsgWmR = false;}
      if(nwTNzlaEJQ == true){nwTNzlaEJQ = false;}
      if(kWKnNnCjBK == true){kWKnNnCjBK = false;}
      if(BtnVLQxOYw == true){BtnVLQxOYw = false;}
      if(WluSqhNaUe == true){WluSqhNaUe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VZSORJSTGQ
{ 
  void IsEePaLqmy()
  { 
      bool sSlJTMCqGu = false;
      bool jjNezSrztZ = false;
      bool eAHjlLdume = false;
      bool ITYfkjHYkx = false;
      bool XhyFrXlyJo = false;
      bool kErOJrLCWI = false;
      bool iGDamPKgsO = false;
      bool KSOwCxCCqO = false;
      bool YflxtDbJWr = false;
      bool YFBbORdWSb = false;
      bool NEEteRpuML = false;
      bool pJKIiDUFgi = false;
      bool nAKAoFRlhk = false;
      bool SejOBUaqSc = false;
      bool MfwKCPtrrL = false;
      bool wYpinMsDFZ = false;
      bool AENbrLYuHO = false;
      bool bdmEVHDAyZ = false;
      bool KYsWntnAao = false;
      bool aXkrcISURp = false;
      string lcCBALhGmF;
      string VXjHzZfGzW;
      string gHFtQpqPyx;
      string YxAHmwBLOq;
      string fesIDLfPpF;
      string YGxZjeWIjJ;
      string TSIofXXcUC;
      string XTrHqCOxpF;
      string JbZrYSAZXI;
      string YsbEWMVDbf;
      string mDtmgEOpig;
      string PZRdArsPQM;
      string XxFMdermjd;
      string fLUJRGglLU;
      string EJqprzayEe;
      string TGmPIpyhJC;
      string MaFEADFILt;
      string KGEuINGOTe;
      string DtiFKZYFAb;
      string HzcIIcElon;
      if(lcCBALhGmF == mDtmgEOpig){sSlJTMCqGu = true;}
      else if(mDtmgEOpig == lcCBALhGmF){NEEteRpuML = true;}
      if(VXjHzZfGzW == PZRdArsPQM){jjNezSrztZ = true;}
      else if(PZRdArsPQM == VXjHzZfGzW){pJKIiDUFgi = true;}
      if(gHFtQpqPyx == XxFMdermjd){eAHjlLdume = true;}
      else if(XxFMdermjd == gHFtQpqPyx){nAKAoFRlhk = true;}
      if(YxAHmwBLOq == fLUJRGglLU){ITYfkjHYkx = true;}
      else if(fLUJRGglLU == YxAHmwBLOq){SejOBUaqSc = true;}
      if(fesIDLfPpF == EJqprzayEe){XhyFrXlyJo = true;}
      else if(EJqprzayEe == fesIDLfPpF){MfwKCPtrrL = true;}
      if(YGxZjeWIjJ == TGmPIpyhJC){kErOJrLCWI = true;}
      else if(TGmPIpyhJC == YGxZjeWIjJ){wYpinMsDFZ = true;}
      if(TSIofXXcUC == MaFEADFILt){iGDamPKgsO = true;}
      else if(MaFEADFILt == TSIofXXcUC){AENbrLYuHO = true;}
      if(XTrHqCOxpF == KGEuINGOTe){KSOwCxCCqO = true;}
      if(JbZrYSAZXI == DtiFKZYFAb){YflxtDbJWr = true;}
      if(YsbEWMVDbf == HzcIIcElon){YFBbORdWSb = true;}
      while(KGEuINGOTe == XTrHqCOxpF){bdmEVHDAyZ = true;}
      while(DtiFKZYFAb == DtiFKZYFAb){KYsWntnAao = true;}
      while(HzcIIcElon == HzcIIcElon){aXkrcISURp = true;}
      if(sSlJTMCqGu == true){sSlJTMCqGu = false;}
      if(jjNezSrztZ == true){jjNezSrztZ = false;}
      if(eAHjlLdume == true){eAHjlLdume = false;}
      if(ITYfkjHYkx == true){ITYfkjHYkx = false;}
      if(XhyFrXlyJo == true){XhyFrXlyJo = false;}
      if(kErOJrLCWI == true){kErOJrLCWI = false;}
      if(iGDamPKgsO == true){iGDamPKgsO = false;}
      if(KSOwCxCCqO == true){KSOwCxCCqO = false;}
      if(YflxtDbJWr == true){YflxtDbJWr = false;}
      if(YFBbORdWSb == true){YFBbORdWSb = false;}
      if(NEEteRpuML == true){NEEteRpuML = false;}
      if(pJKIiDUFgi == true){pJKIiDUFgi = false;}
      if(nAKAoFRlhk == true){nAKAoFRlhk = false;}
      if(SejOBUaqSc == true){SejOBUaqSc = false;}
      if(MfwKCPtrrL == true){MfwKCPtrrL = false;}
      if(wYpinMsDFZ == true){wYpinMsDFZ = false;}
      if(AENbrLYuHO == true){AENbrLYuHO = false;}
      if(bdmEVHDAyZ == true){bdmEVHDAyZ = false;}
      if(KYsWntnAao == true){KYsWntnAao = false;}
      if(aXkrcISURp == true){aXkrcISURp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBBMRIFMMK
{ 
  void rsDCqMHoan()
  { 
      bool FwcgNXdFCy = false;
      bool busnZxlWzQ = false;
      bool kPsynqrQcK = false;
      bool uCxUnKYAeT = false;
      bool zOaRZViGCg = false;
      bool XcFLZoCerW = false;
      bool eMbrCYxXAP = false;
      bool XlreQWobXS = false;
      bool HlNumRxltz = false;
      bool HtHHomlhOB = false;
      bool XKGlJlkZtD = false;
      bool zaGZPsygFk = false;
      bool bLdBIcdjpd = false;
      bool jGMWtwfblA = false;
      bool gWqpzgmhru = false;
      bool nFcdZMgEdf = false;
      bool IAjQTrNjfT = false;
      bool MWuEEEUmBb = false;
      bool ourtoediwg = false;
      bool OaxFrfmZWH = false;
      string tnQLiwonfT;
      string tRIbGnPXbg;
      string MaQkElBSgj;
      string BbVrYSDVZy;
      string ziupWhhaOc;
      string ZjUdZTWfHw;
      string uVHwRSuPDn;
      string jtxdhcfaNW;
      string EZEDJRGrSE;
      string uXNdDcbyYE;
      string lRXasfmpww;
      string mwRkrVRElA;
      string LDxyrMfTaE;
      string BgCIjlBcJd;
      string dPwWRzFclh;
      string LXMYsiUZhg;
      string zTPqtFsJAF;
      string TntHVuHZfs;
      string GCgsrdTdPB;
      string QbucdKAEbL;
      if(tnQLiwonfT == lRXasfmpww){FwcgNXdFCy = true;}
      else if(lRXasfmpww == tnQLiwonfT){XKGlJlkZtD = true;}
      if(tRIbGnPXbg == mwRkrVRElA){busnZxlWzQ = true;}
      else if(mwRkrVRElA == tRIbGnPXbg){zaGZPsygFk = true;}
      if(MaQkElBSgj == LDxyrMfTaE){kPsynqrQcK = true;}
      else if(LDxyrMfTaE == MaQkElBSgj){bLdBIcdjpd = true;}
      if(BbVrYSDVZy == BgCIjlBcJd){uCxUnKYAeT = true;}
      else if(BgCIjlBcJd == BbVrYSDVZy){jGMWtwfblA = true;}
      if(ziupWhhaOc == dPwWRzFclh){zOaRZViGCg = true;}
      else if(dPwWRzFclh == ziupWhhaOc){gWqpzgmhru = true;}
      if(ZjUdZTWfHw == LXMYsiUZhg){XcFLZoCerW = true;}
      else if(LXMYsiUZhg == ZjUdZTWfHw){nFcdZMgEdf = true;}
      if(uVHwRSuPDn == zTPqtFsJAF){eMbrCYxXAP = true;}
      else if(zTPqtFsJAF == uVHwRSuPDn){IAjQTrNjfT = true;}
      if(jtxdhcfaNW == TntHVuHZfs){XlreQWobXS = true;}
      if(EZEDJRGrSE == GCgsrdTdPB){HlNumRxltz = true;}
      if(uXNdDcbyYE == QbucdKAEbL){HtHHomlhOB = true;}
      while(TntHVuHZfs == jtxdhcfaNW){MWuEEEUmBb = true;}
      while(GCgsrdTdPB == GCgsrdTdPB){ourtoediwg = true;}
      while(QbucdKAEbL == QbucdKAEbL){OaxFrfmZWH = true;}
      if(FwcgNXdFCy == true){FwcgNXdFCy = false;}
      if(busnZxlWzQ == true){busnZxlWzQ = false;}
      if(kPsynqrQcK == true){kPsynqrQcK = false;}
      if(uCxUnKYAeT == true){uCxUnKYAeT = false;}
      if(zOaRZViGCg == true){zOaRZViGCg = false;}
      if(XcFLZoCerW == true){XcFLZoCerW = false;}
      if(eMbrCYxXAP == true){eMbrCYxXAP = false;}
      if(XlreQWobXS == true){XlreQWobXS = false;}
      if(HlNumRxltz == true){HlNumRxltz = false;}
      if(HtHHomlhOB == true){HtHHomlhOB = false;}
      if(XKGlJlkZtD == true){XKGlJlkZtD = false;}
      if(zaGZPsygFk == true){zaGZPsygFk = false;}
      if(bLdBIcdjpd == true){bLdBIcdjpd = false;}
      if(jGMWtwfblA == true){jGMWtwfblA = false;}
      if(gWqpzgmhru == true){gWqpzgmhru = false;}
      if(nFcdZMgEdf == true){nFcdZMgEdf = false;}
      if(IAjQTrNjfT == true){IAjQTrNjfT = false;}
      if(MWuEEEUmBb == true){MWuEEEUmBb = false;}
      if(ourtoediwg == true){ourtoediwg = false;}
      if(OaxFrfmZWH == true){OaxFrfmZWH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCWGFBIOPH
{ 
  void EIfifdAdbq()
  { 
      bool kiQtdMpQpO = false;
      bool dfIHCBXJOU = false;
      bool mCXpkoEkmy = false;
      bool dclCpjrirQ = false;
      bool YZBjJEWoiy = false;
      bool uMrGehKZIn = false;
      bool IEdrkBsFRR = false;
      bool InRyuMBngg = false;
      bool SOCoDQjfXH = false;
      bool YRZDIUwJyI = false;
      bool KQXQoHutKR = false;
      bool gWsbVtBonT = false;
      bool QNgJrqNNoa = false;
      bool QqoYWBqkzw = false;
      bool UoUGaCYygO = false;
      bool SGUeqxiNYy = false;
      bool sgEjBohUFT = false;
      bool CQorzbrahp = false;
      bool RPgaHJWKgZ = false;
      bool RcMBCnjjFl = false;
      string upiNzaGutY;
      string QkylHgpOMn;
      string pXwNdGqBPV;
      string UHLCwVOKGM;
      string AWZAdZMlcN;
      string uDBYeXsVjr;
      string iFfXEJYupk;
      string ReHzmSxwiD;
      string tFXCaQFmWX;
      string craNcupBuT;
      string BQwquPuCkM;
      string awlfydgdxm;
      string ElXRIZEtVr;
      string buAOCcIfGK;
      string UDBKxgGuPz;
      string NMDIPOsdiV;
      string KBfsjeuWdU;
      string UAWmRAkMUb;
      string TJdWdPqrzm;
      string jewkzSWHaR;
      if(upiNzaGutY == BQwquPuCkM){kiQtdMpQpO = true;}
      else if(BQwquPuCkM == upiNzaGutY){KQXQoHutKR = true;}
      if(QkylHgpOMn == awlfydgdxm){dfIHCBXJOU = true;}
      else if(awlfydgdxm == QkylHgpOMn){gWsbVtBonT = true;}
      if(pXwNdGqBPV == ElXRIZEtVr){mCXpkoEkmy = true;}
      else if(ElXRIZEtVr == pXwNdGqBPV){QNgJrqNNoa = true;}
      if(UHLCwVOKGM == buAOCcIfGK){dclCpjrirQ = true;}
      else if(buAOCcIfGK == UHLCwVOKGM){QqoYWBqkzw = true;}
      if(AWZAdZMlcN == UDBKxgGuPz){YZBjJEWoiy = true;}
      else if(UDBKxgGuPz == AWZAdZMlcN){UoUGaCYygO = true;}
      if(uDBYeXsVjr == NMDIPOsdiV){uMrGehKZIn = true;}
      else if(NMDIPOsdiV == uDBYeXsVjr){SGUeqxiNYy = true;}
      if(iFfXEJYupk == KBfsjeuWdU){IEdrkBsFRR = true;}
      else if(KBfsjeuWdU == iFfXEJYupk){sgEjBohUFT = true;}
      if(ReHzmSxwiD == UAWmRAkMUb){InRyuMBngg = true;}
      if(tFXCaQFmWX == TJdWdPqrzm){SOCoDQjfXH = true;}
      if(craNcupBuT == jewkzSWHaR){YRZDIUwJyI = true;}
      while(UAWmRAkMUb == ReHzmSxwiD){CQorzbrahp = true;}
      while(TJdWdPqrzm == TJdWdPqrzm){RPgaHJWKgZ = true;}
      while(jewkzSWHaR == jewkzSWHaR){RcMBCnjjFl = true;}
      if(kiQtdMpQpO == true){kiQtdMpQpO = false;}
      if(dfIHCBXJOU == true){dfIHCBXJOU = false;}
      if(mCXpkoEkmy == true){mCXpkoEkmy = false;}
      if(dclCpjrirQ == true){dclCpjrirQ = false;}
      if(YZBjJEWoiy == true){YZBjJEWoiy = false;}
      if(uMrGehKZIn == true){uMrGehKZIn = false;}
      if(IEdrkBsFRR == true){IEdrkBsFRR = false;}
      if(InRyuMBngg == true){InRyuMBngg = false;}
      if(SOCoDQjfXH == true){SOCoDQjfXH = false;}
      if(YRZDIUwJyI == true){YRZDIUwJyI = false;}
      if(KQXQoHutKR == true){KQXQoHutKR = false;}
      if(gWsbVtBonT == true){gWsbVtBonT = false;}
      if(QNgJrqNNoa == true){QNgJrqNNoa = false;}
      if(QqoYWBqkzw == true){QqoYWBqkzw = false;}
      if(UoUGaCYygO == true){UoUGaCYygO = false;}
      if(SGUeqxiNYy == true){SGUeqxiNYy = false;}
      if(sgEjBohUFT == true){sgEjBohUFT = false;}
      if(CQorzbrahp == true){CQorzbrahp = false;}
      if(RPgaHJWKgZ == true){RPgaHJWKgZ = false;}
      if(RcMBCnjjFl == true){RcMBCnjjFl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DBDZDESWQQ
{ 
  void INVQWouBMZ()
  { 
      bool tmCEfGPxNL = false;
      bool XcKulJAmCs = false;
      bool ojyjPENIRc = false;
      bool CZUobFDHjp = false;
      bool KhNizVXQjQ = false;
      bool JWpiTJnSoa = false;
      bool sGekJxHUTf = false;
      bool FrCLiHVPjs = false;
      bool gxYBSfjlVR = false;
      bool QkSIxDCbZB = false;
      bool NCwDKRTdAL = false;
      bool mYhutuhdRc = false;
      bool NVzCOUZsOe = false;
      bool FtoifeAVpB = false;
      bool MGlKdqCWOB = false;
      bool VXKxnrCtno = false;
      bool qZOVGsjzPO = false;
      bool uMnQQHioXX = false;
      bool SCeNIgjrtm = false;
      bool bGgAJlqQDj = false;
      string tKRQkNNYrV;
      string xjJqsuDana;
      string LOfmkBFljr;
      string tXIZxYYJpF;
      string MOXoWYFdOc;
      string XdWplfedfj;
      string HbnAbZaisU;
      string VskiNwqpQL;
      string wbXHTQASmR;
      string sudGykaWNx;
      string yVjsGdrnbp;
      string onNUmeEfgL;
      string YIuaaaPejc;
      string VUcSMZqdBo;
      string XMpxcFhJST;
      string ftoBXoaJRe;
      string OMDyUTLtHN;
      string mZermLRyyV;
      string sFMQwaeauW;
      string yhMVZKJrcI;
      if(tKRQkNNYrV == yVjsGdrnbp){tmCEfGPxNL = true;}
      else if(yVjsGdrnbp == tKRQkNNYrV){NCwDKRTdAL = true;}
      if(xjJqsuDana == onNUmeEfgL){XcKulJAmCs = true;}
      else if(onNUmeEfgL == xjJqsuDana){mYhutuhdRc = true;}
      if(LOfmkBFljr == YIuaaaPejc){ojyjPENIRc = true;}
      else if(YIuaaaPejc == LOfmkBFljr){NVzCOUZsOe = true;}
      if(tXIZxYYJpF == VUcSMZqdBo){CZUobFDHjp = true;}
      else if(VUcSMZqdBo == tXIZxYYJpF){FtoifeAVpB = true;}
      if(MOXoWYFdOc == XMpxcFhJST){KhNizVXQjQ = true;}
      else if(XMpxcFhJST == MOXoWYFdOc){MGlKdqCWOB = true;}
      if(XdWplfedfj == ftoBXoaJRe){JWpiTJnSoa = true;}
      else if(ftoBXoaJRe == XdWplfedfj){VXKxnrCtno = true;}
      if(HbnAbZaisU == OMDyUTLtHN){sGekJxHUTf = true;}
      else if(OMDyUTLtHN == HbnAbZaisU){qZOVGsjzPO = true;}
      if(VskiNwqpQL == mZermLRyyV){FrCLiHVPjs = true;}
      if(wbXHTQASmR == sFMQwaeauW){gxYBSfjlVR = true;}
      if(sudGykaWNx == yhMVZKJrcI){QkSIxDCbZB = true;}
      while(mZermLRyyV == VskiNwqpQL){uMnQQHioXX = true;}
      while(sFMQwaeauW == sFMQwaeauW){SCeNIgjrtm = true;}
      while(yhMVZKJrcI == yhMVZKJrcI){bGgAJlqQDj = true;}
      if(tmCEfGPxNL == true){tmCEfGPxNL = false;}
      if(XcKulJAmCs == true){XcKulJAmCs = false;}
      if(ojyjPENIRc == true){ojyjPENIRc = false;}
      if(CZUobFDHjp == true){CZUobFDHjp = false;}
      if(KhNizVXQjQ == true){KhNizVXQjQ = false;}
      if(JWpiTJnSoa == true){JWpiTJnSoa = false;}
      if(sGekJxHUTf == true){sGekJxHUTf = false;}
      if(FrCLiHVPjs == true){FrCLiHVPjs = false;}
      if(gxYBSfjlVR == true){gxYBSfjlVR = false;}
      if(QkSIxDCbZB == true){QkSIxDCbZB = false;}
      if(NCwDKRTdAL == true){NCwDKRTdAL = false;}
      if(mYhutuhdRc == true){mYhutuhdRc = false;}
      if(NVzCOUZsOe == true){NVzCOUZsOe = false;}
      if(FtoifeAVpB == true){FtoifeAVpB = false;}
      if(MGlKdqCWOB == true){MGlKdqCWOB = false;}
      if(VXKxnrCtno == true){VXKxnrCtno = false;}
      if(qZOVGsjzPO == true){qZOVGsjzPO = false;}
      if(uMnQQHioXX == true){uMnQQHioXX = false;}
      if(SCeNIgjrtm == true){SCeNIgjrtm = false;}
      if(bGgAJlqQDj == true){bGgAJlqQDj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XTKIZEPCZO
{ 
  void JIcKFlofSc()
  { 
      bool LwitnXgyOT = false;
      bool HQZrewwKPd = false;
      bool zsxqosUUIt = false;
      bool VDVyPQTqDj = false;
      bool FXVpIsOQuS = false;
      bool yEbuMSzqEu = false;
      bool CMpUxEuacO = false;
      bool cFHfXbXHhw = false;
      bool dDYouRaZlw = false;
      bool QblHgsgBrE = false;
      bool xmngosxwXk = false;
      bool urIIQzmAYf = false;
      bool cUofxBSzze = false;
      bool tVOdyqPrzC = false;
      bool TdCABYSdph = false;
      bool FfbLacxHin = false;
      bool axxrqYceJZ = false;
      bool iuBWLySoeY = false;
      bool hnIQZNtDDV = false;
      bool sIIKbWgJJc = false;
      string HUHERdxVqL;
      string cAWsNGYzht;
      string ruqPzbSbcB;
      string BrsMGmQSEo;
      string cjwgsTHPMz;
      string xJJxoLcqEo;
      string KUroKkGJla;
      string pGurQHyKVe;
      string TDOcErhwXt;
      string JYOOdHrGVH;
      string NyclJpOQfg;
      string MSUYVHGOkS;
      string CKlrRQrfOI;
      string PrnORVZcTN;
      string dRPpgpDosW;
      string BcVDECLkTr;
      string yhCXQUdGGz;
      string hduWokuuKa;
      string NClrHmVkJP;
      string JnIaOuOrZL;
      if(HUHERdxVqL == NyclJpOQfg){LwitnXgyOT = true;}
      else if(NyclJpOQfg == HUHERdxVqL){xmngosxwXk = true;}
      if(cAWsNGYzht == MSUYVHGOkS){HQZrewwKPd = true;}
      else if(MSUYVHGOkS == cAWsNGYzht){urIIQzmAYf = true;}
      if(ruqPzbSbcB == CKlrRQrfOI){zsxqosUUIt = true;}
      else if(CKlrRQrfOI == ruqPzbSbcB){cUofxBSzze = true;}
      if(BrsMGmQSEo == PrnORVZcTN){VDVyPQTqDj = true;}
      else if(PrnORVZcTN == BrsMGmQSEo){tVOdyqPrzC = true;}
      if(cjwgsTHPMz == dRPpgpDosW){FXVpIsOQuS = true;}
      else if(dRPpgpDosW == cjwgsTHPMz){TdCABYSdph = true;}
      if(xJJxoLcqEo == BcVDECLkTr){yEbuMSzqEu = true;}
      else if(BcVDECLkTr == xJJxoLcqEo){FfbLacxHin = true;}
      if(KUroKkGJla == yhCXQUdGGz){CMpUxEuacO = true;}
      else if(yhCXQUdGGz == KUroKkGJla){axxrqYceJZ = true;}
      if(pGurQHyKVe == hduWokuuKa){cFHfXbXHhw = true;}
      if(TDOcErhwXt == NClrHmVkJP){dDYouRaZlw = true;}
      if(JYOOdHrGVH == JnIaOuOrZL){QblHgsgBrE = true;}
      while(hduWokuuKa == pGurQHyKVe){iuBWLySoeY = true;}
      while(NClrHmVkJP == NClrHmVkJP){hnIQZNtDDV = true;}
      while(JnIaOuOrZL == JnIaOuOrZL){sIIKbWgJJc = true;}
      if(LwitnXgyOT == true){LwitnXgyOT = false;}
      if(HQZrewwKPd == true){HQZrewwKPd = false;}
      if(zsxqosUUIt == true){zsxqosUUIt = false;}
      if(VDVyPQTqDj == true){VDVyPQTqDj = false;}
      if(FXVpIsOQuS == true){FXVpIsOQuS = false;}
      if(yEbuMSzqEu == true){yEbuMSzqEu = false;}
      if(CMpUxEuacO == true){CMpUxEuacO = false;}
      if(cFHfXbXHhw == true){cFHfXbXHhw = false;}
      if(dDYouRaZlw == true){dDYouRaZlw = false;}
      if(QblHgsgBrE == true){QblHgsgBrE = false;}
      if(xmngosxwXk == true){xmngosxwXk = false;}
      if(urIIQzmAYf == true){urIIQzmAYf = false;}
      if(cUofxBSzze == true){cUofxBSzze = false;}
      if(tVOdyqPrzC == true){tVOdyqPrzC = false;}
      if(TdCABYSdph == true){TdCABYSdph = false;}
      if(FfbLacxHin == true){FfbLacxHin = false;}
      if(axxrqYceJZ == true){axxrqYceJZ = false;}
      if(iuBWLySoeY == true){iuBWLySoeY = false;}
      if(hnIQZNtDDV == true){hnIQZNtDDV = false;}
      if(sIIKbWgJJc == true){sIIKbWgJJc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EGJEZSXPUL
{ 
  void IOWlBipERt()
  { 
      bool FfTMOpZNSy = false;
      bool BxMhmkNgoi = false;
      bool YsiRODIXIt = false;
      bool PuwdlnnllW = false;
      bool jraGTEjlco = false;
      bool iowUJMwCyK = false;
      bool hCEXhFBiwz = false;
      bool xatRygRcyJ = false;
      bool SWuTKazaTY = false;
      bool qknaohmCXN = false;
      bool DBodqHtdVc = false;
      bool uTEnrKGjNH = false;
      bool GZOXHLmTbP = false;
      bool sOEjGRgRbC = false;
      bool fVEqcXgAid = false;
      bool aDoQHdlRVf = false;
      bool UaCGjgOUgZ = false;
      bool doIKajUXtj = false;
      bool dljxnpYnbc = false;
      bool eOuuhFSyHu = false;
      string RmmoDTLjjW;
      string CKsnKnIZhk;
      string EjgoswdjFC;
      string SHWhYpytBd;
      string PFhQWoELek;
      string YPECShGxuH;
      string paehEtmLPU;
      string oOXEUzCPRE;
      string qSETdCDUPq;
      string iAytmoZALb;
      string BrwKwJqzhS;
      string fpepPXWLDC;
      string qSwXkoPdQf;
      string YBDpDyVtWT;
      string KEmwLsUHdP;
      string SOwJkhwYZG;
      string sNhBsdmomQ;
      string BbniqlfzLr;
      string TIzBMKFtFU;
      string CxTPZxVkDh;
      if(RmmoDTLjjW == BrwKwJqzhS){FfTMOpZNSy = true;}
      else if(BrwKwJqzhS == RmmoDTLjjW){DBodqHtdVc = true;}
      if(CKsnKnIZhk == fpepPXWLDC){BxMhmkNgoi = true;}
      else if(fpepPXWLDC == CKsnKnIZhk){uTEnrKGjNH = true;}
      if(EjgoswdjFC == qSwXkoPdQf){YsiRODIXIt = true;}
      else if(qSwXkoPdQf == EjgoswdjFC){GZOXHLmTbP = true;}
      if(SHWhYpytBd == YBDpDyVtWT){PuwdlnnllW = true;}
      else if(YBDpDyVtWT == SHWhYpytBd){sOEjGRgRbC = true;}
      if(PFhQWoELek == KEmwLsUHdP){jraGTEjlco = true;}
      else if(KEmwLsUHdP == PFhQWoELek){fVEqcXgAid = true;}
      if(YPECShGxuH == SOwJkhwYZG){iowUJMwCyK = true;}
      else if(SOwJkhwYZG == YPECShGxuH){aDoQHdlRVf = true;}
      if(paehEtmLPU == sNhBsdmomQ){hCEXhFBiwz = true;}
      else if(sNhBsdmomQ == paehEtmLPU){UaCGjgOUgZ = true;}
      if(oOXEUzCPRE == BbniqlfzLr){xatRygRcyJ = true;}
      if(qSETdCDUPq == TIzBMKFtFU){SWuTKazaTY = true;}
      if(iAytmoZALb == CxTPZxVkDh){qknaohmCXN = true;}
      while(BbniqlfzLr == oOXEUzCPRE){doIKajUXtj = true;}
      while(TIzBMKFtFU == TIzBMKFtFU){dljxnpYnbc = true;}
      while(CxTPZxVkDh == CxTPZxVkDh){eOuuhFSyHu = true;}
      if(FfTMOpZNSy == true){FfTMOpZNSy = false;}
      if(BxMhmkNgoi == true){BxMhmkNgoi = false;}
      if(YsiRODIXIt == true){YsiRODIXIt = false;}
      if(PuwdlnnllW == true){PuwdlnnllW = false;}
      if(jraGTEjlco == true){jraGTEjlco = false;}
      if(iowUJMwCyK == true){iowUJMwCyK = false;}
      if(hCEXhFBiwz == true){hCEXhFBiwz = false;}
      if(xatRygRcyJ == true){xatRygRcyJ = false;}
      if(SWuTKazaTY == true){SWuTKazaTY = false;}
      if(qknaohmCXN == true){qknaohmCXN = false;}
      if(DBodqHtdVc == true){DBodqHtdVc = false;}
      if(uTEnrKGjNH == true){uTEnrKGjNH = false;}
      if(GZOXHLmTbP == true){GZOXHLmTbP = false;}
      if(sOEjGRgRbC == true){sOEjGRgRbC = false;}
      if(fVEqcXgAid == true){fVEqcXgAid = false;}
      if(aDoQHdlRVf == true){aDoQHdlRVf = false;}
      if(UaCGjgOUgZ == true){UaCGjgOUgZ = false;}
      if(doIKajUXtj == true){doIKajUXtj = false;}
      if(dljxnpYnbc == true){dljxnpYnbc = false;}
      if(eOuuhFSyHu == true){eOuuhFSyHu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QQZOXBWMRD
{ 
  void lMKWdBLoyj()
  { 
      bool ljEEJpyZuc = false;
      bool OOzaYFwfoL = false;
      bool eulsoIIeor = false;
      bool oQTiENdQrH = false;
      bool YZwJYKacer = false;
      bool TSMITqxKOA = false;
      bool hSjCmyuPVL = false;
      bool aemglFzcUe = false;
      bool hfAwYWDLPN = false;
      bool PSCqZGotVa = false;
      bool PKHTQnefVN = false;
      bool rUpiSCSmcP = false;
      bool uizIuHcuGe = false;
      bool PEGtPWYgek = false;
      bool rWoBUtcSYX = false;
      bool nBRGffKyXI = false;
      bool LiYpymOuTu = false;
      bool dlHqXXtymB = false;
      bool eKWiqNmzOi = false;
      bool LZJVZIxyDg = false;
      string teasACymXV;
      string qtKjzxzQuM;
      string EEKHjqPKYF;
      string rMHdHbFtST;
      string YGFWQaXSGV;
      string LEDcmoUTJJ;
      string lmNSddlfbX;
      string rEybmyzmpI;
      string SxEDsnIeqS;
      string GlkJglrmsl;
      string nqpicHGbon;
      string pgcApohKZo;
      string UHoJQGSotB;
      string FMtDTaGVal;
      string ggoCbYIkSr;
      string DhMDRgCgRW;
      string nRhmidmYfO;
      string iMimInSmgq;
      string xhVByXzqlm;
      string YZDEyPyCTy;
      if(teasACymXV == nqpicHGbon){ljEEJpyZuc = true;}
      else if(nqpicHGbon == teasACymXV){PKHTQnefVN = true;}
      if(qtKjzxzQuM == pgcApohKZo){OOzaYFwfoL = true;}
      else if(pgcApohKZo == qtKjzxzQuM){rUpiSCSmcP = true;}
      if(EEKHjqPKYF == UHoJQGSotB){eulsoIIeor = true;}
      else if(UHoJQGSotB == EEKHjqPKYF){uizIuHcuGe = true;}
      if(rMHdHbFtST == FMtDTaGVal){oQTiENdQrH = true;}
      else if(FMtDTaGVal == rMHdHbFtST){PEGtPWYgek = true;}
      if(YGFWQaXSGV == ggoCbYIkSr){YZwJYKacer = true;}
      else if(ggoCbYIkSr == YGFWQaXSGV){rWoBUtcSYX = true;}
      if(LEDcmoUTJJ == DhMDRgCgRW){TSMITqxKOA = true;}
      else if(DhMDRgCgRW == LEDcmoUTJJ){nBRGffKyXI = true;}
      if(lmNSddlfbX == nRhmidmYfO){hSjCmyuPVL = true;}
      else if(nRhmidmYfO == lmNSddlfbX){LiYpymOuTu = true;}
      if(rEybmyzmpI == iMimInSmgq){aemglFzcUe = true;}
      if(SxEDsnIeqS == xhVByXzqlm){hfAwYWDLPN = true;}
      if(GlkJglrmsl == YZDEyPyCTy){PSCqZGotVa = true;}
      while(iMimInSmgq == rEybmyzmpI){dlHqXXtymB = true;}
      while(xhVByXzqlm == xhVByXzqlm){eKWiqNmzOi = true;}
      while(YZDEyPyCTy == YZDEyPyCTy){LZJVZIxyDg = true;}
      if(ljEEJpyZuc == true){ljEEJpyZuc = false;}
      if(OOzaYFwfoL == true){OOzaYFwfoL = false;}
      if(eulsoIIeor == true){eulsoIIeor = false;}
      if(oQTiENdQrH == true){oQTiENdQrH = false;}
      if(YZwJYKacer == true){YZwJYKacer = false;}
      if(TSMITqxKOA == true){TSMITqxKOA = false;}
      if(hSjCmyuPVL == true){hSjCmyuPVL = false;}
      if(aemglFzcUe == true){aemglFzcUe = false;}
      if(hfAwYWDLPN == true){hfAwYWDLPN = false;}
      if(PSCqZGotVa == true){PSCqZGotVa = false;}
      if(PKHTQnefVN == true){PKHTQnefVN = false;}
      if(rUpiSCSmcP == true){rUpiSCSmcP = false;}
      if(uizIuHcuGe == true){uizIuHcuGe = false;}
      if(PEGtPWYgek == true){PEGtPWYgek = false;}
      if(rWoBUtcSYX == true){rWoBUtcSYX = false;}
      if(nBRGffKyXI == true){nBRGffKyXI = false;}
      if(LiYpymOuTu == true){LiYpymOuTu = false;}
      if(dlHqXXtymB == true){dlHqXXtymB = false;}
      if(eKWiqNmzOi == true){eKWiqNmzOi = false;}
      if(LZJVZIxyDg == true){LZJVZIxyDg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AFXCZKSPDF
{ 
  void JrRcdYUUoS()
  { 
      bool xglnhkYTke = false;
      bool XMzexnWcPo = false;
      bool UKosBDrwQz = false;
      bool ZdysYmfTDZ = false;
      bool hzVidTTUHQ = false;
      bool uPQepmqsmd = false;
      bool rbClFsOFFK = false;
      bool HCZpGVoFPg = false;
      bool iXnAEJNTDl = false;
      bool umfYgGxidj = false;
      bool FOPxIrpaXU = false;
      bool ykdGtUnChu = false;
      bool fuCSOTWAIA = false;
      bool XFbebUHqqM = false;
      bool TmuinJJZdL = false;
      bool RuBiDJLwhn = false;
      bool VpRXwrJydZ = false;
      bool MwKVasATeF = false;
      bool KwVwhcErbR = false;
      bool ILICpdVWlu = false;
      string hXHGEZrBlp;
      string yxxcbUuoZV;
      string JDSBketIel;
      string RKEOaxKhrg;
      string HYXpNwALSi;
      string TIxeQdEGUZ;
      string ejWAXnsiCd;
      string KMxrNkfcmn;
      string eiowRIMZxx;
      string rENRBXBXRZ;
      string DRJnXGLFQf;
      string xbSfuwtZhO;
      string aTkElGzepo;
      string iIKNkNYBXL;
      string xHIRzPlgWF;
      string daoDyifEBR;
      string GfObxnREth;
      string XrCVRSLSFW;
      string TSIkLHSHOB;
      string gTzFERsgUL;
      if(hXHGEZrBlp == DRJnXGLFQf){xglnhkYTke = true;}
      else if(DRJnXGLFQf == hXHGEZrBlp){FOPxIrpaXU = true;}
      if(yxxcbUuoZV == xbSfuwtZhO){XMzexnWcPo = true;}
      else if(xbSfuwtZhO == yxxcbUuoZV){ykdGtUnChu = true;}
      if(JDSBketIel == aTkElGzepo){UKosBDrwQz = true;}
      else if(aTkElGzepo == JDSBketIel){fuCSOTWAIA = true;}
      if(RKEOaxKhrg == iIKNkNYBXL){ZdysYmfTDZ = true;}
      else if(iIKNkNYBXL == RKEOaxKhrg){XFbebUHqqM = true;}
      if(HYXpNwALSi == xHIRzPlgWF){hzVidTTUHQ = true;}
      else if(xHIRzPlgWF == HYXpNwALSi){TmuinJJZdL = true;}
      if(TIxeQdEGUZ == daoDyifEBR){uPQepmqsmd = true;}
      else if(daoDyifEBR == TIxeQdEGUZ){RuBiDJLwhn = true;}
      if(ejWAXnsiCd == GfObxnREth){rbClFsOFFK = true;}
      else if(GfObxnREth == ejWAXnsiCd){VpRXwrJydZ = true;}
      if(KMxrNkfcmn == XrCVRSLSFW){HCZpGVoFPg = true;}
      if(eiowRIMZxx == TSIkLHSHOB){iXnAEJNTDl = true;}
      if(rENRBXBXRZ == gTzFERsgUL){umfYgGxidj = true;}
      while(XrCVRSLSFW == KMxrNkfcmn){MwKVasATeF = true;}
      while(TSIkLHSHOB == TSIkLHSHOB){KwVwhcErbR = true;}
      while(gTzFERsgUL == gTzFERsgUL){ILICpdVWlu = true;}
      if(xglnhkYTke == true){xglnhkYTke = false;}
      if(XMzexnWcPo == true){XMzexnWcPo = false;}
      if(UKosBDrwQz == true){UKosBDrwQz = false;}
      if(ZdysYmfTDZ == true){ZdysYmfTDZ = false;}
      if(hzVidTTUHQ == true){hzVidTTUHQ = false;}
      if(uPQepmqsmd == true){uPQepmqsmd = false;}
      if(rbClFsOFFK == true){rbClFsOFFK = false;}
      if(HCZpGVoFPg == true){HCZpGVoFPg = false;}
      if(iXnAEJNTDl == true){iXnAEJNTDl = false;}
      if(umfYgGxidj == true){umfYgGxidj = false;}
      if(FOPxIrpaXU == true){FOPxIrpaXU = false;}
      if(ykdGtUnChu == true){ykdGtUnChu = false;}
      if(fuCSOTWAIA == true){fuCSOTWAIA = false;}
      if(XFbebUHqqM == true){XFbebUHqqM = false;}
      if(TmuinJJZdL == true){TmuinJJZdL = false;}
      if(RuBiDJLwhn == true){RuBiDJLwhn = false;}
      if(VpRXwrJydZ == true){VpRXwrJydZ = false;}
      if(MwKVasATeF == true){MwKVasATeF = false;}
      if(KwVwhcErbR == true){KwVwhcErbR = false;}
      if(ILICpdVWlu == true){ILICpdVWlu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OGDDBENQHE
{ 
  void YYRVayBuVl()
  { 
      bool wwVYZLHPsi = false;
      bool XVJPEdzunX = false;
      bool ltsjUoynEV = false;
      bool INypRGSwZO = false;
      bool fzIUPCldhd = false;
      bool SgJZQBClEk = false;
      bool MSKXZKWTxy = false;
      bool KDVZrmlYTS = false;
      bool CTFaCbDYZP = false;
      bool DgrnBMnktE = false;
      bool eSgjSPKjgd = false;
      bool PcRlirMjUy = false;
      bool HytgtdLhYe = false;
      bool yAeOmjmVHl = false;
      bool QTquAaPFFI = false;
      bool zEPuxfXzoo = false;
      bool EcLBfOyCyy = false;
      bool FqbhgnGygT = false;
      bool NFbPftkiRH = false;
      bool LnfShnIoPk = false;
      string tKsqSomcVS;
      string lYlwdxkeuk;
      string wrhVRYBSKC;
      string rxusAAlOsk;
      string nWjlTlNzMN;
      string YuRpFBbXZs;
      string nUSSZodrwd;
      string KWlJxZIuCe;
      string LCFxdwfFny;
      string XOnzxSEQLd;
      string HVCiCCIHrf;
      string sfUthkOVnc;
      string JYDyFuhmLd;
      string UqjXWoAWtb;
      string nXMIErssRL;
      string DhbhUiRDcG;
      string TUuOKBwxXr;
      string kraMokLusN;
      string CoVAZmOBDm;
      string XwsmISbyxD;
      if(tKsqSomcVS == HVCiCCIHrf){wwVYZLHPsi = true;}
      else if(HVCiCCIHrf == tKsqSomcVS){eSgjSPKjgd = true;}
      if(lYlwdxkeuk == sfUthkOVnc){XVJPEdzunX = true;}
      else if(sfUthkOVnc == lYlwdxkeuk){PcRlirMjUy = true;}
      if(wrhVRYBSKC == JYDyFuhmLd){ltsjUoynEV = true;}
      else if(JYDyFuhmLd == wrhVRYBSKC){HytgtdLhYe = true;}
      if(rxusAAlOsk == UqjXWoAWtb){INypRGSwZO = true;}
      else if(UqjXWoAWtb == rxusAAlOsk){yAeOmjmVHl = true;}
      if(nWjlTlNzMN == nXMIErssRL){fzIUPCldhd = true;}
      else if(nXMIErssRL == nWjlTlNzMN){QTquAaPFFI = true;}
      if(YuRpFBbXZs == DhbhUiRDcG){SgJZQBClEk = true;}
      else if(DhbhUiRDcG == YuRpFBbXZs){zEPuxfXzoo = true;}
      if(nUSSZodrwd == TUuOKBwxXr){MSKXZKWTxy = true;}
      else if(TUuOKBwxXr == nUSSZodrwd){EcLBfOyCyy = true;}
      if(KWlJxZIuCe == kraMokLusN){KDVZrmlYTS = true;}
      if(LCFxdwfFny == CoVAZmOBDm){CTFaCbDYZP = true;}
      if(XOnzxSEQLd == XwsmISbyxD){DgrnBMnktE = true;}
      while(kraMokLusN == KWlJxZIuCe){FqbhgnGygT = true;}
      while(CoVAZmOBDm == CoVAZmOBDm){NFbPftkiRH = true;}
      while(XwsmISbyxD == XwsmISbyxD){LnfShnIoPk = true;}
      if(wwVYZLHPsi == true){wwVYZLHPsi = false;}
      if(XVJPEdzunX == true){XVJPEdzunX = false;}
      if(ltsjUoynEV == true){ltsjUoynEV = false;}
      if(INypRGSwZO == true){INypRGSwZO = false;}
      if(fzIUPCldhd == true){fzIUPCldhd = false;}
      if(SgJZQBClEk == true){SgJZQBClEk = false;}
      if(MSKXZKWTxy == true){MSKXZKWTxy = false;}
      if(KDVZrmlYTS == true){KDVZrmlYTS = false;}
      if(CTFaCbDYZP == true){CTFaCbDYZP = false;}
      if(DgrnBMnktE == true){DgrnBMnktE = false;}
      if(eSgjSPKjgd == true){eSgjSPKjgd = false;}
      if(PcRlirMjUy == true){PcRlirMjUy = false;}
      if(HytgtdLhYe == true){HytgtdLhYe = false;}
      if(yAeOmjmVHl == true){yAeOmjmVHl = false;}
      if(QTquAaPFFI == true){QTquAaPFFI = false;}
      if(zEPuxfXzoo == true){zEPuxfXzoo = false;}
      if(EcLBfOyCyy == true){EcLBfOyCyy = false;}
      if(FqbhgnGygT == true){FqbhgnGygT = false;}
      if(NFbPftkiRH == true){NFbPftkiRH = false;}
      if(LnfShnIoPk == true){LnfShnIoPk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TUWDTLTSNC
{ 
  void FojHwQixHE()
  { 
      bool bJFJbeSVrU = false;
      bool QTNdwgmsOt = false;
      bool CzrSCGmOaB = false;
      bool fePBjtStzI = false;
      bool XHBsBxpZuT = false;
      bool kiuypcRmHU = false;
      bool qEupolEMtB = false;
      bool OstFVtxyQE = false;
      bool QMTGQxiQKH = false;
      bool cemdQTMLDP = false;
      bool sdfsEropcw = false;
      bool eSVCEeknYr = false;
      bool CmBlXiFPoC = false;
      bool hluBLlfZBY = false;
      bool IsmObKJjZl = false;
      bool iXlLNFbtVV = false;
      bool lYAaNsXTqR = false;
      bool yKlAjIzmKN = false;
      bool YVpDTJAinF = false;
      bool KlEfmirMAi = false;
      string DeaITRxcaN;
      string fWrkGZSmud;
      string UrFzNuItSR;
      string krzXoApyPU;
      string LgmkXfkVcF;
      string pwKcpKZatX;
      string JDKIcnXUwG;
      string jUXZRmETbh;
      string KlQMbnhWgd;
      string ZOEqKIWdHi;
      string HPZVUVYjKC;
      string FFzLNXlxgo;
      string FBmRfUQgOJ;
      string QaMrZtMtqF;
      string PxLeXUPrcm;
      string VYxSdGcHpA;
      string FqUBlesGlT;
      string LqFaZIoItL;
      string EXDbmqctOS;
      string REEqAXbKsr;
      if(DeaITRxcaN == HPZVUVYjKC){bJFJbeSVrU = true;}
      else if(HPZVUVYjKC == DeaITRxcaN){sdfsEropcw = true;}
      if(fWrkGZSmud == FFzLNXlxgo){QTNdwgmsOt = true;}
      else if(FFzLNXlxgo == fWrkGZSmud){eSVCEeknYr = true;}
      if(UrFzNuItSR == FBmRfUQgOJ){CzrSCGmOaB = true;}
      else if(FBmRfUQgOJ == UrFzNuItSR){CmBlXiFPoC = true;}
      if(krzXoApyPU == QaMrZtMtqF){fePBjtStzI = true;}
      else if(QaMrZtMtqF == krzXoApyPU){hluBLlfZBY = true;}
      if(LgmkXfkVcF == PxLeXUPrcm){XHBsBxpZuT = true;}
      else if(PxLeXUPrcm == LgmkXfkVcF){IsmObKJjZl = true;}
      if(pwKcpKZatX == VYxSdGcHpA){kiuypcRmHU = true;}
      else if(VYxSdGcHpA == pwKcpKZatX){iXlLNFbtVV = true;}
      if(JDKIcnXUwG == FqUBlesGlT){qEupolEMtB = true;}
      else if(FqUBlesGlT == JDKIcnXUwG){lYAaNsXTqR = true;}
      if(jUXZRmETbh == LqFaZIoItL){OstFVtxyQE = true;}
      if(KlQMbnhWgd == EXDbmqctOS){QMTGQxiQKH = true;}
      if(ZOEqKIWdHi == REEqAXbKsr){cemdQTMLDP = true;}
      while(LqFaZIoItL == jUXZRmETbh){yKlAjIzmKN = true;}
      while(EXDbmqctOS == EXDbmqctOS){YVpDTJAinF = true;}
      while(REEqAXbKsr == REEqAXbKsr){KlEfmirMAi = true;}
      if(bJFJbeSVrU == true){bJFJbeSVrU = false;}
      if(QTNdwgmsOt == true){QTNdwgmsOt = false;}
      if(CzrSCGmOaB == true){CzrSCGmOaB = false;}
      if(fePBjtStzI == true){fePBjtStzI = false;}
      if(XHBsBxpZuT == true){XHBsBxpZuT = false;}
      if(kiuypcRmHU == true){kiuypcRmHU = false;}
      if(qEupolEMtB == true){qEupolEMtB = false;}
      if(OstFVtxyQE == true){OstFVtxyQE = false;}
      if(QMTGQxiQKH == true){QMTGQxiQKH = false;}
      if(cemdQTMLDP == true){cemdQTMLDP = false;}
      if(sdfsEropcw == true){sdfsEropcw = false;}
      if(eSVCEeknYr == true){eSVCEeknYr = false;}
      if(CmBlXiFPoC == true){CmBlXiFPoC = false;}
      if(hluBLlfZBY == true){hluBLlfZBY = false;}
      if(IsmObKJjZl == true){IsmObKJjZl = false;}
      if(iXlLNFbtVV == true){iXlLNFbtVV = false;}
      if(lYAaNsXTqR == true){lYAaNsXTqR = false;}
      if(yKlAjIzmKN == true){yKlAjIzmKN = false;}
      if(YVpDTJAinF == true){YVpDTJAinF = false;}
      if(KlEfmirMAi == true){KlEfmirMAi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UVCSJGDAPX
{ 
  void CdLufZiofG()
  { 
      bool wGLNfzPzzH = false;
      bool QDKheNQKmD = false;
      bool PIgfuFXyrE = false;
      bool IGlHexUWzG = false;
      bool YBNuJRNtJy = false;
      bool iawacnYfRa = false;
      bool bRHuzJQCDg = false;
      bool rtKgdOtlVd = false;
      bool qcntVhKKdp = false;
      bool XoEYdHsSwz = false;
      bool BLqcGnQPwO = false;
      bool tmJniycNZR = false;
      bool zGXNICokCW = false;
      bool UapVbflLmg = false;
      bool RtNOukeQoe = false;
      bool dfseAumcTD = false;
      bool yeMZtSwmLD = false;
      bool MQZrzErJRX = false;
      bool XYuWsnhLVg = false;
      bool rIrjhlhnUb = false;
      string tQohHjfdVD;
      string gXBQVXRqER;
      string rBDZhCRzMH;
      string hDZEZTuIpp;
      string VhedzYEMGH;
      string ERuwusNPzE;
      string SgROVcxwqB;
      string bJBOwJVZaJ;
      string xErECQIdIf;
      string GfIlXoQQIV;
      string aHVFfuPgAk;
      string WmnoGNnMLE;
      string UTnKtwAOpG;
      string sFREhoimYG;
      string AacWJSqSeK;
      string ADEDBHTKKj;
      string tBpsrQVjHQ;
      string dAnEDspQAb;
      string EgjfGoBNCa;
      string VXcoLzkjes;
      if(tQohHjfdVD == aHVFfuPgAk){wGLNfzPzzH = true;}
      else if(aHVFfuPgAk == tQohHjfdVD){BLqcGnQPwO = true;}
      if(gXBQVXRqER == WmnoGNnMLE){QDKheNQKmD = true;}
      else if(WmnoGNnMLE == gXBQVXRqER){tmJniycNZR = true;}
      if(rBDZhCRzMH == UTnKtwAOpG){PIgfuFXyrE = true;}
      else if(UTnKtwAOpG == rBDZhCRzMH){zGXNICokCW = true;}
      if(hDZEZTuIpp == sFREhoimYG){IGlHexUWzG = true;}
      else if(sFREhoimYG == hDZEZTuIpp){UapVbflLmg = true;}
      if(VhedzYEMGH == AacWJSqSeK){YBNuJRNtJy = true;}
      else if(AacWJSqSeK == VhedzYEMGH){RtNOukeQoe = true;}
      if(ERuwusNPzE == ADEDBHTKKj){iawacnYfRa = true;}
      else if(ADEDBHTKKj == ERuwusNPzE){dfseAumcTD = true;}
      if(SgROVcxwqB == tBpsrQVjHQ){bRHuzJQCDg = true;}
      else if(tBpsrQVjHQ == SgROVcxwqB){yeMZtSwmLD = true;}
      if(bJBOwJVZaJ == dAnEDspQAb){rtKgdOtlVd = true;}
      if(xErECQIdIf == EgjfGoBNCa){qcntVhKKdp = true;}
      if(GfIlXoQQIV == VXcoLzkjes){XoEYdHsSwz = true;}
      while(dAnEDspQAb == bJBOwJVZaJ){MQZrzErJRX = true;}
      while(EgjfGoBNCa == EgjfGoBNCa){XYuWsnhLVg = true;}
      while(VXcoLzkjes == VXcoLzkjes){rIrjhlhnUb = true;}
      if(wGLNfzPzzH == true){wGLNfzPzzH = false;}
      if(QDKheNQKmD == true){QDKheNQKmD = false;}
      if(PIgfuFXyrE == true){PIgfuFXyrE = false;}
      if(IGlHexUWzG == true){IGlHexUWzG = false;}
      if(YBNuJRNtJy == true){YBNuJRNtJy = false;}
      if(iawacnYfRa == true){iawacnYfRa = false;}
      if(bRHuzJQCDg == true){bRHuzJQCDg = false;}
      if(rtKgdOtlVd == true){rtKgdOtlVd = false;}
      if(qcntVhKKdp == true){qcntVhKKdp = false;}
      if(XoEYdHsSwz == true){XoEYdHsSwz = false;}
      if(BLqcGnQPwO == true){BLqcGnQPwO = false;}
      if(tmJniycNZR == true){tmJniycNZR = false;}
      if(zGXNICokCW == true){zGXNICokCW = false;}
      if(UapVbflLmg == true){UapVbflLmg = false;}
      if(RtNOukeQoe == true){RtNOukeQoe = false;}
      if(dfseAumcTD == true){dfseAumcTD = false;}
      if(yeMZtSwmLD == true){yeMZtSwmLD = false;}
      if(MQZrzErJRX == true){MQZrzErJRX = false;}
      if(XYuWsnhLVg == true){XYuWsnhLVg = false;}
      if(rIrjhlhnUb == true){rIrjhlhnUb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KPREBEERLN
{ 
  void XRFrxXgwVN()
  { 
      bool QwBSBMnZdB = false;
      bool JNcRqXQCSD = false;
      bool RntxqCdNlH = false;
      bool wZOfGjYntq = false;
      bool ilUyoYxJYf = false;
      bool ePPppbCDbz = false;
      bool hamWEjzwLH = false;
      bool ycIbTfSuHR = false;
      bool EUoGbfJXod = false;
      bool gUMuIIyytF = false;
      bool ZByRgCHnWK = false;
      bool IGwKtNkgtY = false;
      bool ZbHgZdPNSL = false;
      bool gUBCqDVXYZ = false;
      bool YVBeUZXBAt = false;
      bool WRDVeytQqD = false;
      bool ltUKdnFtSq = false;
      bool rNITzEabLz = false;
      bool FOMYnPRfWs = false;
      bool JEfVneBpBg = false;
      string OTyTePHNBp;
      string MfEVdySbiP;
      string SQNcCfHAIi;
      string TpNjudXfkI;
      string zpbbQBUUQX;
      string JUALuyFVQz;
      string HHERWVSTZz;
      string ZmqaPcnlLB;
      string KmikYypCox;
      string XBOkArkKFu;
      string iBtQxWdYuS;
      string JTKPnUYSsX;
      string fPecaYYFaX;
      string qdgPSJrRnC;
      string UQGVnEqyxe;
      string TSQgPSWRoY;
      string yYyXbemtxd;
      string cGdqDOIIoW;
      string gZHwEXMzAz;
      string mabPEuSitI;
      if(OTyTePHNBp == iBtQxWdYuS){QwBSBMnZdB = true;}
      else if(iBtQxWdYuS == OTyTePHNBp){ZByRgCHnWK = true;}
      if(MfEVdySbiP == JTKPnUYSsX){JNcRqXQCSD = true;}
      else if(JTKPnUYSsX == MfEVdySbiP){IGwKtNkgtY = true;}
      if(SQNcCfHAIi == fPecaYYFaX){RntxqCdNlH = true;}
      else if(fPecaYYFaX == SQNcCfHAIi){ZbHgZdPNSL = true;}
      if(TpNjudXfkI == qdgPSJrRnC){wZOfGjYntq = true;}
      else if(qdgPSJrRnC == TpNjudXfkI){gUBCqDVXYZ = true;}
      if(zpbbQBUUQX == UQGVnEqyxe){ilUyoYxJYf = true;}
      else if(UQGVnEqyxe == zpbbQBUUQX){YVBeUZXBAt = true;}
      if(JUALuyFVQz == TSQgPSWRoY){ePPppbCDbz = true;}
      else if(TSQgPSWRoY == JUALuyFVQz){WRDVeytQqD = true;}
      if(HHERWVSTZz == yYyXbemtxd){hamWEjzwLH = true;}
      else if(yYyXbemtxd == HHERWVSTZz){ltUKdnFtSq = true;}
      if(ZmqaPcnlLB == cGdqDOIIoW){ycIbTfSuHR = true;}
      if(KmikYypCox == gZHwEXMzAz){EUoGbfJXod = true;}
      if(XBOkArkKFu == mabPEuSitI){gUMuIIyytF = true;}
      while(cGdqDOIIoW == ZmqaPcnlLB){rNITzEabLz = true;}
      while(gZHwEXMzAz == gZHwEXMzAz){FOMYnPRfWs = true;}
      while(mabPEuSitI == mabPEuSitI){JEfVneBpBg = true;}
      if(QwBSBMnZdB == true){QwBSBMnZdB = false;}
      if(JNcRqXQCSD == true){JNcRqXQCSD = false;}
      if(RntxqCdNlH == true){RntxqCdNlH = false;}
      if(wZOfGjYntq == true){wZOfGjYntq = false;}
      if(ilUyoYxJYf == true){ilUyoYxJYf = false;}
      if(ePPppbCDbz == true){ePPppbCDbz = false;}
      if(hamWEjzwLH == true){hamWEjzwLH = false;}
      if(ycIbTfSuHR == true){ycIbTfSuHR = false;}
      if(EUoGbfJXod == true){EUoGbfJXod = false;}
      if(gUMuIIyytF == true){gUMuIIyytF = false;}
      if(ZByRgCHnWK == true){ZByRgCHnWK = false;}
      if(IGwKtNkgtY == true){IGwKtNkgtY = false;}
      if(ZbHgZdPNSL == true){ZbHgZdPNSL = false;}
      if(gUBCqDVXYZ == true){gUBCqDVXYZ = false;}
      if(YVBeUZXBAt == true){YVBeUZXBAt = false;}
      if(WRDVeytQqD == true){WRDVeytQqD = false;}
      if(ltUKdnFtSq == true){ltUKdnFtSq = false;}
      if(rNITzEabLz == true){rNITzEabLz = false;}
      if(FOMYnPRfWs == true){FOMYnPRfWs = false;}
      if(JEfVneBpBg == true){JEfVneBpBg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSOGZCNKIC
{ 
  void fFQmcmfEfJ()
  { 
      bool HyqQuTZtrA = false;
      bool gHSXHMtROF = false;
      bool dzRapMlOrX = false;
      bool ImekMRWseS = false;
      bool VnRPCywKdT = false;
      bool PUscyHgQZh = false;
      bool hLBTrsbgLo = false;
      bool oAlwiphCXr = false;
      bool QakYImsCmE = false;
      bool kGTwkKlxWI = false;
      bool VOzoeOhxsI = false;
      bool ZergRGacLF = false;
      bool AYtGDhgpLY = false;
      bool DjeOWBbuts = false;
      bool EwIeeGOmdd = false;
      bool jIlRIwUrkw = false;
      bool hrlUEpzcJQ = false;
      bool deiRADPPbx = false;
      bool TtMgntxNGZ = false;
      bool giKxLMKnao = false;
      string xQZCqRYWNJ;
      string ydxYBfnJqx;
      string hgQxfXQYei;
      string WEgoTIFxDx;
      string jaeJOhcmVy;
      string ihjqfQzcWS;
      string BzqelswIFs;
      string aqGtMGBHhy;
      string ucDgzoUoJD;
      string IbajukjzWV;
      string kThcWrapdY;
      string OruXXXuJfx;
      string YHyBjyQWyb;
      string WCjMNauaJH;
      string OdKjnPgCMX;
      string oZTZwcVfrY;
      string aEqCCMIhKw;
      string bUAYhuwNMT;
      string QOJZmwiJQj;
      string FPikfKlIhb;
      if(xQZCqRYWNJ == kThcWrapdY){HyqQuTZtrA = true;}
      else if(kThcWrapdY == xQZCqRYWNJ){VOzoeOhxsI = true;}
      if(ydxYBfnJqx == OruXXXuJfx){gHSXHMtROF = true;}
      else if(OruXXXuJfx == ydxYBfnJqx){ZergRGacLF = true;}
      if(hgQxfXQYei == YHyBjyQWyb){dzRapMlOrX = true;}
      else if(YHyBjyQWyb == hgQxfXQYei){AYtGDhgpLY = true;}
      if(WEgoTIFxDx == WCjMNauaJH){ImekMRWseS = true;}
      else if(WCjMNauaJH == WEgoTIFxDx){DjeOWBbuts = true;}
      if(jaeJOhcmVy == OdKjnPgCMX){VnRPCywKdT = true;}
      else if(OdKjnPgCMX == jaeJOhcmVy){EwIeeGOmdd = true;}
      if(ihjqfQzcWS == oZTZwcVfrY){PUscyHgQZh = true;}
      else if(oZTZwcVfrY == ihjqfQzcWS){jIlRIwUrkw = true;}
      if(BzqelswIFs == aEqCCMIhKw){hLBTrsbgLo = true;}
      else if(aEqCCMIhKw == BzqelswIFs){hrlUEpzcJQ = true;}
      if(aqGtMGBHhy == bUAYhuwNMT){oAlwiphCXr = true;}
      if(ucDgzoUoJD == QOJZmwiJQj){QakYImsCmE = true;}
      if(IbajukjzWV == FPikfKlIhb){kGTwkKlxWI = true;}
      while(bUAYhuwNMT == aqGtMGBHhy){deiRADPPbx = true;}
      while(QOJZmwiJQj == QOJZmwiJQj){TtMgntxNGZ = true;}
      while(FPikfKlIhb == FPikfKlIhb){giKxLMKnao = true;}
      if(HyqQuTZtrA == true){HyqQuTZtrA = false;}
      if(gHSXHMtROF == true){gHSXHMtROF = false;}
      if(dzRapMlOrX == true){dzRapMlOrX = false;}
      if(ImekMRWseS == true){ImekMRWseS = false;}
      if(VnRPCywKdT == true){VnRPCywKdT = false;}
      if(PUscyHgQZh == true){PUscyHgQZh = false;}
      if(hLBTrsbgLo == true){hLBTrsbgLo = false;}
      if(oAlwiphCXr == true){oAlwiphCXr = false;}
      if(QakYImsCmE == true){QakYImsCmE = false;}
      if(kGTwkKlxWI == true){kGTwkKlxWI = false;}
      if(VOzoeOhxsI == true){VOzoeOhxsI = false;}
      if(ZergRGacLF == true){ZergRGacLF = false;}
      if(AYtGDhgpLY == true){AYtGDhgpLY = false;}
      if(DjeOWBbuts == true){DjeOWBbuts = false;}
      if(EwIeeGOmdd == true){EwIeeGOmdd = false;}
      if(jIlRIwUrkw == true){jIlRIwUrkw = false;}
      if(hrlUEpzcJQ == true){hrlUEpzcJQ = false;}
      if(deiRADPPbx == true){deiRADPPbx = false;}
      if(TtMgntxNGZ == true){TtMgntxNGZ = false;}
      if(giKxLMKnao == true){giKxLMKnao = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONWTDJNZIJ
{ 
  void MTUWYSqZVb()
  { 
      bool QVshRQNAUK = false;
      bool wpsYcwJiEO = false;
      bool YOrpcQrKFw = false;
      bool yJaQZDjGtH = false;
      bool wlfHckgOSA = false;
      bool nxGGEBdCFB = false;
      bool YDuXLlObyZ = false;
      bool LDowSlikNq = false;
      bool idqEIADUMX = false;
      bool YhArirqHuq = false;
      bool VEPsnkIJnR = false;
      bool SsoNRtLpPK = false;
      bool htPaAdCwMZ = false;
      bool ubpVUeNyQX = false;
      bool rsftFfsmao = false;
      bool gAqjIboorK = false;
      bool hMxOVpCSsm = false;
      bool gMZrSoOUUU = false;
      bool kPUXrtjGNs = false;
      bool pXGGofwRXP = false;
      string PkdJmVdfxp;
      string zoDnpZkGkG;
      string pwlGmWhGTr;
      string dwqJLJVjXB;
      string DkeRAWZySM;
      string LHBDJTzXVQ;
      string nWLEMCxsbg;
      string EAhjCEQUFP;
      string winGgVtnAr;
      string KyOGNfZaFx;
      string ZgWkIKZRAE;
      string CdRFTEiEXp;
      string HIriVFlaVW;
      string epOHpPMCyV;
      string wcnuoffIlJ;
      string xUCOpQnmOC;
      string YywcZMPJPE;
      string qfGBteUxsp;
      string ZcnMYKmARY;
      string bZmuwxgKVc;
      if(PkdJmVdfxp == ZgWkIKZRAE){QVshRQNAUK = true;}
      else if(ZgWkIKZRAE == PkdJmVdfxp){VEPsnkIJnR = true;}
      if(zoDnpZkGkG == CdRFTEiEXp){wpsYcwJiEO = true;}
      else if(CdRFTEiEXp == zoDnpZkGkG){SsoNRtLpPK = true;}
      if(pwlGmWhGTr == HIriVFlaVW){YOrpcQrKFw = true;}
      else if(HIriVFlaVW == pwlGmWhGTr){htPaAdCwMZ = true;}
      if(dwqJLJVjXB == epOHpPMCyV){yJaQZDjGtH = true;}
      else if(epOHpPMCyV == dwqJLJVjXB){ubpVUeNyQX = true;}
      if(DkeRAWZySM == wcnuoffIlJ){wlfHckgOSA = true;}
      else if(wcnuoffIlJ == DkeRAWZySM){rsftFfsmao = true;}
      if(LHBDJTzXVQ == xUCOpQnmOC){nxGGEBdCFB = true;}
      else if(xUCOpQnmOC == LHBDJTzXVQ){gAqjIboorK = true;}
      if(nWLEMCxsbg == YywcZMPJPE){YDuXLlObyZ = true;}
      else if(YywcZMPJPE == nWLEMCxsbg){hMxOVpCSsm = true;}
      if(EAhjCEQUFP == qfGBteUxsp){LDowSlikNq = true;}
      if(winGgVtnAr == ZcnMYKmARY){idqEIADUMX = true;}
      if(KyOGNfZaFx == bZmuwxgKVc){YhArirqHuq = true;}
      while(qfGBteUxsp == EAhjCEQUFP){gMZrSoOUUU = true;}
      while(ZcnMYKmARY == ZcnMYKmARY){kPUXrtjGNs = true;}
      while(bZmuwxgKVc == bZmuwxgKVc){pXGGofwRXP = true;}
      if(QVshRQNAUK == true){QVshRQNAUK = false;}
      if(wpsYcwJiEO == true){wpsYcwJiEO = false;}
      if(YOrpcQrKFw == true){YOrpcQrKFw = false;}
      if(yJaQZDjGtH == true){yJaQZDjGtH = false;}
      if(wlfHckgOSA == true){wlfHckgOSA = false;}
      if(nxGGEBdCFB == true){nxGGEBdCFB = false;}
      if(YDuXLlObyZ == true){YDuXLlObyZ = false;}
      if(LDowSlikNq == true){LDowSlikNq = false;}
      if(idqEIADUMX == true){idqEIADUMX = false;}
      if(YhArirqHuq == true){YhArirqHuq = false;}
      if(VEPsnkIJnR == true){VEPsnkIJnR = false;}
      if(SsoNRtLpPK == true){SsoNRtLpPK = false;}
      if(htPaAdCwMZ == true){htPaAdCwMZ = false;}
      if(ubpVUeNyQX == true){ubpVUeNyQX = false;}
      if(rsftFfsmao == true){rsftFfsmao = false;}
      if(gAqjIboorK == true){gAqjIboorK = false;}
      if(hMxOVpCSsm == true){hMxOVpCSsm = false;}
      if(gMZrSoOUUU == true){gMZrSoOUUU = false;}
      if(kPUXrtjGNs == true){kPUXrtjGNs = false;}
      if(pXGGofwRXP == true){pXGGofwRXP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RALHNUHYFZ
{ 
  void dopJtrysjl()
  { 
      bool ePbnjFOkxY = false;
      bool jjtLDDpInb = false;
      bool aXiTjgKcas = false;
      bool zkGWbZOWYw = false;
      bool yxirzErBCf = false;
      bool SxAxUGfHED = false;
      bool tlJEYycWjc = false;
      bool oSirdcopUe = false;
      bool oJZuZBjJBU = false;
      bool sGRVBLmeTA = false;
      bool aVQYqAOITr = false;
      bool RpmZNjLOdX = false;
      bool NTUOihAMpR = false;
      bool oJWUETsBDZ = false;
      bool lbpJDDTrIR = false;
      bool AYAwlHACoI = false;
      bool zCRCCHTSUt = false;
      bool qKKDklcKLf = false;
      bool OHEYRQJahw = false;
      bool SpLtZjJnHu = false;
      string htwmsnrqle;
      string IgTLQfkGNb;
      string ueLwetkENF;
      string eYcGuEMlpa;
      string RGQPrTaBTQ;
      string NrTdoCiAIy;
      string DmcfAiENQL;
      string SzQlJnOwEK;
      string TjkxrlFzQr;
      string VMcqXedjOI;
      string PNkHyOagUB;
      string mlwydSBfnN;
      string dFwXpFVYOe;
      string KegutFzdyc;
      string LXePEiPeME;
      string cxwAdKQMRr;
      string sCRopIEADY;
      string TXhKCFZgSG;
      string opLJBNhgRi;
      string olMFjJGoZu;
      if(htwmsnrqle == PNkHyOagUB){ePbnjFOkxY = true;}
      else if(PNkHyOagUB == htwmsnrqle){aVQYqAOITr = true;}
      if(IgTLQfkGNb == mlwydSBfnN){jjtLDDpInb = true;}
      else if(mlwydSBfnN == IgTLQfkGNb){RpmZNjLOdX = true;}
      if(ueLwetkENF == dFwXpFVYOe){aXiTjgKcas = true;}
      else if(dFwXpFVYOe == ueLwetkENF){NTUOihAMpR = true;}
      if(eYcGuEMlpa == KegutFzdyc){zkGWbZOWYw = true;}
      else if(KegutFzdyc == eYcGuEMlpa){oJWUETsBDZ = true;}
      if(RGQPrTaBTQ == LXePEiPeME){yxirzErBCf = true;}
      else if(LXePEiPeME == RGQPrTaBTQ){lbpJDDTrIR = true;}
      if(NrTdoCiAIy == cxwAdKQMRr){SxAxUGfHED = true;}
      else if(cxwAdKQMRr == NrTdoCiAIy){AYAwlHACoI = true;}
      if(DmcfAiENQL == sCRopIEADY){tlJEYycWjc = true;}
      else if(sCRopIEADY == DmcfAiENQL){zCRCCHTSUt = true;}
      if(SzQlJnOwEK == TXhKCFZgSG){oSirdcopUe = true;}
      if(TjkxrlFzQr == opLJBNhgRi){oJZuZBjJBU = true;}
      if(VMcqXedjOI == olMFjJGoZu){sGRVBLmeTA = true;}
      while(TXhKCFZgSG == SzQlJnOwEK){qKKDklcKLf = true;}
      while(opLJBNhgRi == opLJBNhgRi){OHEYRQJahw = true;}
      while(olMFjJGoZu == olMFjJGoZu){SpLtZjJnHu = true;}
      if(ePbnjFOkxY == true){ePbnjFOkxY = false;}
      if(jjtLDDpInb == true){jjtLDDpInb = false;}
      if(aXiTjgKcas == true){aXiTjgKcas = false;}
      if(zkGWbZOWYw == true){zkGWbZOWYw = false;}
      if(yxirzErBCf == true){yxirzErBCf = false;}
      if(SxAxUGfHED == true){SxAxUGfHED = false;}
      if(tlJEYycWjc == true){tlJEYycWjc = false;}
      if(oSirdcopUe == true){oSirdcopUe = false;}
      if(oJZuZBjJBU == true){oJZuZBjJBU = false;}
      if(sGRVBLmeTA == true){sGRVBLmeTA = false;}
      if(aVQYqAOITr == true){aVQYqAOITr = false;}
      if(RpmZNjLOdX == true){RpmZNjLOdX = false;}
      if(NTUOihAMpR == true){NTUOihAMpR = false;}
      if(oJWUETsBDZ == true){oJWUETsBDZ = false;}
      if(lbpJDDTrIR == true){lbpJDDTrIR = false;}
      if(AYAwlHACoI == true){AYAwlHACoI = false;}
      if(zCRCCHTSUt == true){zCRCCHTSUt = false;}
      if(qKKDklcKLf == true){qKKDklcKLf = false;}
      if(OHEYRQJahw == true){OHEYRQJahw = false;}
      if(SpLtZjJnHu == true){SpLtZjJnHu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BHGXLTOQZU
{ 
  void PqHxAwGrui()
  { 
      bool ftuQEpSsBE = false;
      bool heqHOOFHFC = false;
      bool ncKNJAEAQf = false;
      bool ahIWMrznxe = false;
      bool BiZlGnPOuX = false;
      bool jWkHKDihGE = false;
      bool lSbVdzWTtV = false;
      bool PQJaAFCYGU = false;
      bool jpEsuDxAMJ = false;
      bool IQgssiHEIG = false;
      bool QwTYHTNKHE = false;
      bool AKalTwNhZZ = false;
      bool CWGkMyiPgQ = false;
      bool xyPADnWekb = false;
      bool plsIJyouZx = false;
      bool VYdhEtoiMJ = false;
      bool jxcpGBtahe = false;
      bool YhwxjPdyaO = false;
      bool InpjuXThuJ = false;
      bool ymSbqsJCBH = false;
      string LJOQVDwiYi;
      string whPAzjVmmV;
      string MFOKYLIwQf;
      string FpEPKiCkzj;
      string QQmVIcwotT;
      string kwcUPGuDrK;
      string uASscGczpQ;
      string hjnDEuRrCu;
      string OTBxuINjAE;
      string mysonQytrC;
      string AwzdkAIYPT;
      string nDBwubyVyU;
      string sszkcjqyOn;
      string xXzzuRTXLt;
      string znTgPjwwtM;
      string RcwXIHxNBB;
      string IJJbWQEBBc;
      string HaJDVEZRVs;
      string mtECVUbbpn;
      string TGWJlodqJy;
      if(LJOQVDwiYi == AwzdkAIYPT){ftuQEpSsBE = true;}
      else if(AwzdkAIYPT == LJOQVDwiYi){QwTYHTNKHE = true;}
      if(whPAzjVmmV == nDBwubyVyU){heqHOOFHFC = true;}
      else if(nDBwubyVyU == whPAzjVmmV){AKalTwNhZZ = true;}
      if(MFOKYLIwQf == sszkcjqyOn){ncKNJAEAQf = true;}
      else if(sszkcjqyOn == MFOKYLIwQf){CWGkMyiPgQ = true;}
      if(FpEPKiCkzj == xXzzuRTXLt){ahIWMrznxe = true;}
      else if(xXzzuRTXLt == FpEPKiCkzj){xyPADnWekb = true;}
      if(QQmVIcwotT == znTgPjwwtM){BiZlGnPOuX = true;}
      else if(znTgPjwwtM == QQmVIcwotT){plsIJyouZx = true;}
      if(kwcUPGuDrK == RcwXIHxNBB){jWkHKDihGE = true;}
      else if(RcwXIHxNBB == kwcUPGuDrK){VYdhEtoiMJ = true;}
      if(uASscGczpQ == IJJbWQEBBc){lSbVdzWTtV = true;}
      else if(IJJbWQEBBc == uASscGczpQ){jxcpGBtahe = true;}
      if(hjnDEuRrCu == HaJDVEZRVs){PQJaAFCYGU = true;}
      if(OTBxuINjAE == mtECVUbbpn){jpEsuDxAMJ = true;}
      if(mysonQytrC == TGWJlodqJy){IQgssiHEIG = true;}
      while(HaJDVEZRVs == hjnDEuRrCu){YhwxjPdyaO = true;}
      while(mtECVUbbpn == mtECVUbbpn){InpjuXThuJ = true;}
      while(TGWJlodqJy == TGWJlodqJy){ymSbqsJCBH = true;}
      if(ftuQEpSsBE == true){ftuQEpSsBE = false;}
      if(heqHOOFHFC == true){heqHOOFHFC = false;}
      if(ncKNJAEAQf == true){ncKNJAEAQf = false;}
      if(ahIWMrznxe == true){ahIWMrznxe = false;}
      if(BiZlGnPOuX == true){BiZlGnPOuX = false;}
      if(jWkHKDihGE == true){jWkHKDihGE = false;}
      if(lSbVdzWTtV == true){lSbVdzWTtV = false;}
      if(PQJaAFCYGU == true){PQJaAFCYGU = false;}
      if(jpEsuDxAMJ == true){jpEsuDxAMJ = false;}
      if(IQgssiHEIG == true){IQgssiHEIG = false;}
      if(QwTYHTNKHE == true){QwTYHTNKHE = false;}
      if(AKalTwNhZZ == true){AKalTwNhZZ = false;}
      if(CWGkMyiPgQ == true){CWGkMyiPgQ = false;}
      if(xyPADnWekb == true){xyPADnWekb = false;}
      if(plsIJyouZx == true){plsIJyouZx = false;}
      if(VYdhEtoiMJ == true){VYdhEtoiMJ = false;}
      if(jxcpGBtahe == true){jxcpGBtahe = false;}
      if(YhwxjPdyaO == true){YhwxjPdyaO = false;}
      if(InpjuXThuJ == true){InpjuXThuJ = false;}
      if(ymSbqsJCBH == true){ymSbqsJCBH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRKLEEVNXT
{ 
  void LwHajPcNdm()
  { 
      bool wllrTecCES = false;
      bool GYDprLiVJX = false;
      bool flfujFkorP = false;
      bool VrOuwHPADS = false;
      bool llgyorqfEk = false;
      bool EKIumJGpIN = false;
      bool tmJoxNJIsk = false;
      bool wiRqlsFgGr = false;
      bool OEjHLKjTHl = false;
      bool BYroXycqBb = false;
      bool himToUrRJs = false;
      bool EYjPzpDCcl = false;
      bool dpAGjWpcSm = false;
      bool QNfdJeQQSp = false;
      bool SSJOhbobph = false;
      bool uaNPxqhfjR = false;
      bool dPyVcpsFGT = false;
      bool YmimTLflYI = false;
      bool hOlkrpzQfR = false;
      bool xkfALCTnlr = false;
      string pooxsoNnNK;
      string NydJemamIx;
      string fQAUYptzPM;
      string JatMQcnJae;
      string NMrcjGQMyO;
      string JcOblZoUYC;
      string uNYBAmDQrB;
      string yQLcjTXWjR;
      string ZgBBCgLRZp;
      string mTkXjznqbx;
      string DzTwQsQlrS;
      string CSjGcOMXzT;
      string bkpCNdfnsj;
      string egtmOaMFjJ;
      string PZZHnUjduV;
      string mPrIURIRil;
      string MbsHmUXxrC;
      string BHmoDCLiNs;
      string tBsXxOolRw;
      string RuWxwmfSTS;
      if(pooxsoNnNK == DzTwQsQlrS){wllrTecCES = true;}
      else if(DzTwQsQlrS == pooxsoNnNK){himToUrRJs = true;}
      if(NydJemamIx == CSjGcOMXzT){GYDprLiVJX = true;}
      else if(CSjGcOMXzT == NydJemamIx){EYjPzpDCcl = true;}
      if(fQAUYptzPM == bkpCNdfnsj){flfujFkorP = true;}
      else if(bkpCNdfnsj == fQAUYptzPM){dpAGjWpcSm = true;}
      if(JatMQcnJae == egtmOaMFjJ){VrOuwHPADS = true;}
      else if(egtmOaMFjJ == JatMQcnJae){QNfdJeQQSp = true;}
      if(NMrcjGQMyO == PZZHnUjduV){llgyorqfEk = true;}
      else if(PZZHnUjduV == NMrcjGQMyO){SSJOhbobph = true;}
      if(JcOblZoUYC == mPrIURIRil){EKIumJGpIN = true;}
      else if(mPrIURIRil == JcOblZoUYC){uaNPxqhfjR = true;}
      if(uNYBAmDQrB == MbsHmUXxrC){tmJoxNJIsk = true;}
      else if(MbsHmUXxrC == uNYBAmDQrB){dPyVcpsFGT = true;}
      if(yQLcjTXWjR == BHmoDCLiNs){wiRqlsFgGr = true;}
      if(ZgBBCgLRZp == tBsXxOolRw){OEjHLKjTHl = true;}
      if(mTkXjznqbx == RuWxwmfSTS){BYroXycqBb = true;}
      while(BHmoDCLiNs == yQLcjTXWjR){YmimTLflYI = true;}
      while(tBsXxOolRw == tBsXxOolRw){hOlkrpzQfR = true;}
      while(RuWxwmfSTS == RuWxwmfSTS){xkfALCTnlr = true;}
      if(wllrTecCES == true){wllrTecCES = false;}
      if(GYDprLiVJX == true){GYDprLiVJX = false;}
      if(flfujFkorP == true){flfujFkorP = false;}
      if(VrOuwHPADS == true){VrOuwHPADS = false;}
      if(llgyorqfEk == true){llgyorqfEk = false;}
      if(EKIumJGpIN == true){EKIumJGpIN = false;}
      if(tmJoxNJIsk == true){tmJoxNJIsk = false;}
      if(wiRqlsFgGr == true){wiRqlsFgGr = false;}
      if(OEjHLKjTHl == true){OEjHLKjTHl = false;}
      if(BYroXycqBb == true){BYroXycqBb = false;}
      if(himToUrRJs == true){himToUrRJs = false;}
      if(EYjPzpDCcl == true){EYjPzpDCcl = false;}
      if(dpAGjWpcSm == true){dpAGjWpcSm = false;}
      if(QNfdJeQQSp == true){QNfdJeQQSp = false;}
      if(SSJOhbobph == true){SSJOhbobph = false;}
      if(uaNPxqhfjR == true){uaNPxqhfjR = false;}
      if(dPyVcpsFGT == true){dPyVcpsFGT = false;}
      if(YmimTLflYI == true){YmimTLflYI = false;}
      if(hOlkrpzQfR == true){hOlkrpzQfR = false;}
      if(xkfALCTnlr == true){xkfALCTnlr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HNEBBTLDZV
{ 
  void RffmohSBEx()
  { 
      bool cwDUVWUsVy = false;
      bool cnblBbEIFd = false;
      bool gZHQIZgMal = false;
      bool kUKpIVmpco = false;
      bool TGHfPNmjsl = false;
      bool FVsmkDnlLw = false;
      bool pISjMHclce = false;
      bool nOePJZRaBu = false;
      bool mwSngPaWEF = false;
      bool gBdgzLnXSH = false;
      bool jAGNxppddK = false;
      bool kMjPIsodCw = false;
      bool gFgXxmkyQy = false;
      bool ltItLlpFqp = false;
      bool YxssUUQNYF = false;
      bool WKUVadTiPK = false;
      bool FrMeYpEpEV = false;
      bool DimMWiMmDc = false;
      bool VWYKaaZlSg = false;
      bool SGofkgkNUe = false;
      string ZSNZekxPRo;
      string hmssOJuelL;
      string IUgaFGGSNq;
      string kdiMURyffc;
      string BxgtTjKPkf;
      string lEZOsFllTY;
      string edBaDEEfXx;
      string LPyIKKnlHV;
      string wqhgEgDTSP;
      string fLLHyWuFpO;
      string fdrnTWGREh;
      string QzdycnwUWW;
      string BjMHQADpJm;
      string PiwroRzsNg;
      string ZkPjzfhMeK;
      string aaiSNwQjWT;
      string SPHRSgDlJK;
      string oDGowPTcHk;
      string RqKzLnAcdr;
      string BOVtOKdyRR;
      if(ZSNZekxPRo == fdrnTWGREh){cwDUVWUsVy = true;}
      else if(fdrnTWGREh == ZSNZekxPRo){jAGNxppddK = true;}
      if(hmssOJuelL == QzdycnwUWW){cnblBbEIFd = true;}
      else if(QzdycnwUWW == hmssOJuelL){kMjPIsodCw = true;}
      if(IUgaFGGSNq == BjMHQADpJm){gZHQIZgMal = true;}
      else if(BjMHQADpJm == IUgaFGGSNq){gFgXxmkyQy = true;}
      if(kdiMURyffc == PiwroRzsNg){kUKpIVmpco = true;}
      else if(PiwroRzsNg == kdiMURyffc){ltItLlpFqp = true;}
      if(BxgtTjKPkf == ZkPjzfhMeK){TGHfPNmjsl = true;}
      else if(ZkPjzfhMeK == BxgtTjKPkf){YxssUUQNYF = true;}
      if(lEZOsFllTY == aaiSNwQjWT){FVsmkDnlLw = true;}
      else if(aaiSNwQjWT == lEZOsFllTY){WKUVadTiPK = true;}
      if(edBaDEEfXx == SPHRSgDlJK){pISjMHclce = true;}
      else if(SPHRSgDlJK == edBaDEEfXx){FrMeYpEpEV = true;}
      if(LPyIKKnlHV == oDGowPTcHk){nOePJZRaBu = true;}
      if(wqhgEgDTSP == RqKzLnAcdr){mwSngPaWEF = true;}
      if(fLLHyWuFpO == BOVtOKdyRR){gBdgzLnXSH = true;}
      while(oDGowPTcHk == LPyIKKnlHV){DimMWiMmDc = true;}
      while(RqKzLnAcdr == RqKzLnAcdr){VWYKaaZlSg = true;}
      while(BOVtOKdyRR == BOVtOKdyRR){SGofkgkNUe = true;}
      if(cwDUVWUsVy == true){cwDUVWUsVy = false;}
      if(cnblBbEIFd == true){cnblBbEIFd = false;}
      if(gZHQIZgMal == true){gZHQIZgMal = false;}
      if(kUKpIVmpco == true){kUKpIVmpco = false;}
      if(TGHfPNmjsl == true){TGHfPNmjsl = false;}
      if(FVsmkDnlLw == true){FVsmkDnlLw = false;}
      if(pISjMHclce == true){pISjMHclce = false;}
      if(nOePJZRaBu == true){nOePJZRaBu = false;}
      if(mwSngPaWEF == true){mwSngPaWEF = false;}
      if(gBdgzLnXSH == true){gBdgzLnXSH = false;}
      if(jAGNxppddK == true){jAGNxppddK = false;}
      if(kMjPIsodCw == true){kMjPIsodCw = false;}
      if(gFgXxmkyQy == true){gFgXxmkyQy = false;}
      if(ltItLlpFqp == true){ltItLlpFqp = false;}
      if(YxssUUQNYF == true){YxssUUQNYF = false;}
      if(WKUVadTiPK == true){WKUVadTiPK = false;}
      if(FrMeYpEpEV == true){FrMeYpEpEV = false;}
      if(DimMWiMmDc == true){DimMWiMmDc = false;}
      if(VWYKaaZlSg == true){VWYKaaZlSg = false;}
      if(SGofkgkNUe == true){SGofkgkNUe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPREPZGSRA
{ 
  void tMeciYmhcU()
  { 
      bool FEFiDBMDNp = false;
      bool IpgENqeFDo = false;
      bool BWjYLFhTWP = false;
      bool goajRMKjkF = false;
      bool UdzjtVMCYq = false;
      bool CkAIuhUfWx = false;
      bool SsgyITPxmA = false;
      bool guTxUWWzep = false;
      bool sfteMwnSni = false;
      bool qdNmmaxBbZ = false;
      bool GOOYKHQDmX = false;
      bool LVBgEmyBkM = false;
      bool ewIDIChfKs = false;
      bool ZVWEidQUTF = false;
      bool ekePXVcfiA = false;
      bool buPPuKGLPI = false;
      bool Zjrtyoyxxa = false;
      bool VdhegtQsfm = false;
      bool YBxKQdFHJY = false;
      bool XFFKftrkQh = false;
      string XILGGSOpJz;
      string dTfzjRddyR;
      string jzkEGWcVmQ;
      string PDoAfXVPsy;
      string GsAXuomtAI;
      string TKjSLYXHzj;
      string osCsiadfTM;
      string wOjzLpyNIQ;
      string iiVewFTVnG;
      string zOQJINpGnU;
      string KGamMFZjHV;
      string aJyhBGWXxc;
      string GIqMMgxapx;
      string zqYnFbHhRq;
      string fiOSfpPhHC;
      string pSJLNCPNae;
      string HysKVikKbY;
      string zoGGxXsYgW;
      string RPSnGghNaD;
      string MsGligpExw;
      if(XILGGSOpJz == KGamMFZjHV){FEFiDBMDNp = true;}
      else if(KGamMFZjHV == XILGGSOpJz){GOOYKHQDmX = true;}
      if(dTfzjRddyR == aJyhBGWXxc){IpgENqeFDo = true;}
      else if(aJyhBGWXxc == dTfzjRddyR){LVBgEmyBkM = true;}
      if(jzkEGWcVmQ == GIqMMgxapx){BWjYLFhTWP = true;}
      else if(GIqMMgxapx == jzkEGWcVmQ){ewIDIChfKs = true;}
      if(PDoAfXVPsy == zqYnFbHhRq){goajRMKjkF = true;}
      else if(zqYnFbHhRq == PDoAfXVPsy){ZVWEidQUTF = true;}
      if(GsAXuomtAI == fiOSfpPhHC){UdzjtVMCYq = true;}
      else if(fiOSfpPhHC == GsAXuomtAI){ekePXVcfiA = true;}
      if(TKjSLYXHzj == pSJLNCPNae){CkAIuhUfWx = true;}
      else if(pSJLNCPNae == TKjSLYXHzj){buPPuKGLPI = true;}
      if(osCsiadfTM == HysKVikKbY){SsgyITPxmA = true;}
      else if(HysKVikKbY == osCsiadfTM){Zjrtyoyxxa = true;}
      if(wOjzLpyNIQ == zoGGxXsYgW){guTxUWWzep = true;}
      if(iiVewFTVnG == RPSnGghNaD){sfteMwnSni = true;}
      if(zOQJINpGnU == MsGligpExw){qdNmmaxBbZ = true;}
      while(zoGGxXsYgW == wOjzLpyNIQ){VdhegtQsfm = true;}
      while(RPSnGghNaD == RPSnGghNaD){YBxKQdFHJY = true;}
      while(MsGligpExw == MsGligpExw){XFFKftrkQh = true;}
      if(FEFiDBMDNp == true){FEFiDBMDNp = false;}
      if(IpgENqeFDo == true){IpgENqeFDo = false;}
      if(BWjYLFhTWP == true){BWjYLFhTWP = false;}
      if(goajRMKjkF == true){goajRMKjkF = false;}
      if(UdzjtVMCYq == true){UdzjtVMCYq = false;}
      if(CkAIuhUfWx == true){CkAIuhUfWx = false;}
      if(SsgyITPxmA == true){SsgyITPxmA = false;}
      if(guTxUWWzep == true){guTxUWWzep = false;}
      if(sfteMwnSni == true){sfteMwnSni = false;}
      if(qdNmmaxBbZ == true){qdNmmaxBbZ = false;}
      if(GOOYKHQDmX == true){GOOYKHQDmX = false;}
      if(LVBgEmyBkM == true){LVBgEmyBkM = false;}
      if(ewIDIChfKs == true){ewIDIChfKs = false;}
      if(ZVWEidQUTF == true){ZVWEidQUTF = false;}
      if(ekePXVcfiA == true){ekePXVcfiA = false;}
      if(buPPuKGLPI == true){buPPuKGLPI = false;}
      if(Zjrtyoyxxa == true){Zjrtyoyxxa = false;}
      if(VdhegtQsfm == true){VdhegtQsfm = false;}
      if(YBxKQdFHJY == true){YBxKQdFHJY = false;}
      if(XFFKftrkQh == true){XFFKftrkQh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TDARXOHCRS
{ 
  void CHmWRtbXWD()
  { 
      bool uJAsYWhAlP = false;
      bool wnyodZRtSL = false;
      bool hxzMeGYVkf = false;
      bool rZxKiSZoUY = false;
      bool abFEpgKCwT = false;
      bool NPCVgyKmOS = false;
      bool yLOGWVqmFK = false;
      bool zbYskGqtWx = false;
      bool wVYRScXbdk = false;
      bool HmaCaPMzhT = false;
      bool oWxlTkpIja = false;
      bool GQQQWblxms = false;
      bool yOJTDMAWRV = false;
      bool sqMCHZXmxg = false;
      bool mOqDdqVKfz = false;
      bool cOMnUZNciH = false;
      bool jSqOgPENIw = false;
      bool DzAGGjXFoM = false;
      bool ppqSrdeXgg = false;
      bool LuEowTXbVO = false;
      string gbLQLWjQpp;
      string spGJIgOVJk;
      string aERAkgTMsy;
      string rScOTasJMn;
      string metltirOQA;
      string ektuEbKLfd;
      string CXWqxZMqpg;
      string nEJVyuKeGB;
      string oFusTHXgKq;
      string QhdhlOICnT;
      string WAXjMZbYxI;
      string RfEdoxbdXp;
      string CegzPFZbji;
      string mHpldogLgs;
      string ezjCYkczso;
      string mdexRqTYTG;
      string AAoOUKoSzA;
      string PQwdLCueZe;
      string cZhtwIbrTm;
      string VIqaseJUgO;
      if(gbLQLWjQpp == WAXjMZbYxI){uJAsYWhAlP = true;}
      else if(WAXjMZbYxI == gbLQLWjQpp){oWxlTkpIja = true;}
      if(spGJIgOVJk == RfEdoxbdXp){wnyodZRtSL = true;}
      else if(RfEdoxbdXp == spGJIgOVJk){GQQQWblxms = true;}
      if(aERAkgTMsy == CegzPFZbji){hxzMeGYVkf = true;}
      else if(CegzPFZbji == aERAkgTMsy){yOJTDMAWRV = true;}
      if(rScOTasJMn == mHpldogLgs){rZxKiSZoUY = true;}
      else if(mHpldogLgs == rScOTasJMn){sqMCHZXmxg = true;}
      if(metltirOQA == ezjCYkczso){abFEpgKCwT = true;}
      else if(ezjCYkczso == metltirOQA){mOqDdqVKfz = true;}
      if(ektuEbKLfd == mdexRqTYTG){NPCVgyKmOS = true;}
      else if(mdexRqTYTG == ektuEbKLfd){cOMnUZNciH = true;}
      if(CXWqxZMqpg == AAoOUKoSzA){yLOGWVqmFK = true;}
      else if(AAoOUKoSzA == CXWqxZMqpg){jSqOgPENIw = true;}
      if(nEJVyuKeGB == PQwdLCueZe){zbYskGqtWx = true;}
      if(oFusTHXgKq == cZhtwIbrTm){wVYRScXbdk = true;}
      if(QhdhlOICnT == VIqaseJUgO){HmaCaPMzhT = true;}
      while(PQwdLCueZe == nEJVyuKeGB){DzAGGjXFoM = true;}
      while(cZhtwIbrTm == cZhtwIbrTm){ppqSrdeXgg = true;}
      while(VIqaseJUgO == VIqaseJUgO){LuEowTXbVO = true;}
      if(uJAsYWhAlP == true){uJAsYWhAlP = false;}
      if(wnyodZRtSL == true){wnyodZRtSL = false;}
      if(hxzMeGYVkf == true){hxzMeGYVkf = false;}
      if(rZxKiSZoUY == true){rZxKiSZoUY = false;}
      if(abFEpgKCwT == true){abFEpgKCwT = false;}
      if(NPCVgyKmOS == true){NPCVgyKmOS = false;}
      if(yLOGWVqmFK == true){yLOGWVqmFK = false;}
      if(zbYskGqtWx == true){zbYskGqtWx = false;}
      if(wVYRScXbdk == true){wVYRScXbdk = false;}
      if(HmaCaPMzhT == true){HmaCaPMzhT = false;}
      if(oWxlTkpIja == true){oWxlTkpIja = false;}
      if(GQQQWblxms == true){GQQQWblxms = false;}
      if(yOJTDMAWRV == true){yOJTDMAWRV = false;}
      if(sqMCHZXmxg == true){sqMCHZXmxg = false;}
      if(mOqDdqVKfz == true){mOqDdqVKfz = false;}
      if(cOMnUZNciH == true){cOMnUZNciH = false;}
      if(jSqOgPENIw == true){jSqOgPENIw = false;}
      if(DzAGGjXFoM == true){DzAGGjXFoM = false;}
      if(ppqSrdeXgg == true){ppqSrdeXgg = false;}
      if(LuEowTXbVO == true){LuEowTXbVO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WFGZEKVVBF
{ 
  void PCnTqYQyah()
  { 
      bool rqWnacAWTm = false;
      bool fPifewrHFT = false;
      bool hQbBaldfSF = false;
      bool ynIXSitGmc = false;
      bool ErtqRJKFeM = false;
      bool DwTcibOUNn = false;
      bool zTDOoqHLMw = false;
      bool ClUbOoVjiQ = false;
      bool aYBGCCUeoq = false;
      bool TYrydknfCa = false;
      bool CzrhJQaqOs = false;
      bool FdkwNZRxMm = false;
      bool WbWUbcsWyd = false;
      bool BphINafSwk = false;
      bool bcQukonwjD = false;
      bool SqSPEacXGg = false;
      bool WDskrPwbhl = false;
      bool tyAaLsLaim = false;
      bool oxmtKJWSEm = false;
      bool yIMPNXjeDV = false;
      string ywPCsukRqt;
      string TbQeMqyuVF;
      string hapyXFCsUY;
      string BcizzrruZx;
      string YqPzJlNHsc;
      string DsNoKXGQen;
      string sqwSrqrQeT;
      string zDVXfpLqnl;
      string rtArVHOsoa;
      string laPkEhtwGS;
      string swbYcAXoIT;
      string MOcswypExk;
      string byaEhXmjTx;
      string uOjVruSbOV;
      string iZkVOWyWoG;
      string qpzVptUXqE;
      string MmVLYxeHAA;
      string fOpbBCNFoK;
      string ZQtNFEPOey;
      string ZtkJIwEYxQ;
      if(ywPCsukRqt == swbYcAXoIT){rqWnacAWTm = true;}
      else if(swbYcAXoIT == ywPCsukRqt){CzrhJQaqOs = true;}
      if(TbQeMqyuVF == MOcswypExk){fPifewrHFT = true;}
      else if(MOcswypExk == TbQeMqyuVF){FdkwNZRxMm = true;}
      if(hapyXFCsUY == byaEhXmjTx){hQbBaldfSF = true;}
      else if(byaEhXmjTx == hapyXFCsUY){WbWUbcsWyd = true;}
      if(BcizzrruZx == uOjVruSbOV){ynIXSitGmc = true;}
      else if(uOjVruSbOV == BcizzrruZx){BphINafSwk = true;}
      if(YqPzJlNHsc == iZkVOWyWoG){ErtqRJKFeM = true;}
      else if(iZkVOWyWoG == YqPzJlNHsc){bcQukonwjD = true;}
      if(DsNoKXGQen == qpzVptUXqE){DwTcibOUNn = true;}
      else if(qpzVptUXqE == DsNoKXGQen){SqSPEacXGg = true;}
      if(sqwSrqrQeT == MmVLYxeHAA){zTDOoqHLMw = true;}
      else if(MmVLYxeHAA == sqwSrqrQeT){WDskrPwbhl = true;}
      if(zDVXfpLqnl == fOpbBCNFoK){ClUbOoVjiQ = true;}
      if(rtArVHOsoa == ZQtNFEPOey){aYBGCCUeoq = true;}
      if(laPkEhtwGS == ZtkJIwEYxQ){TYrydknfCa = true;}
      while(fOpbBCNFoK == zDVXfpLqnl){tyAaLsLaim = true;}
      while(ZQtNFEPOey == ZQtNFEPOey){oxmtKJWSEm = true;}
      while(ZtkJIwEYxQ == ZtkJIwEYxQ){yIMPNXjeDV = true;}
      if(rqWnacAWTm == true){rqWnacAWTm = false;}
      if(fPifewrHFT == true){fPifewrHFT = false;}
      if(hQbBaldfSF == true){hQbBaldfSF = false;}
      if(ynIXSitGmc == true){ynIXSitGmc = false;}
      if(ErtqRJKFeM == true){ErtqRJKFeM = false;}
      if(DwTcibOUNn == true){DwTcibOUNn = false;}
      if(zTDOoqHLMw == true){zTDOoqHLMw = false;}
      if(ClUbOoVjiQ == true){ClUbOoVjiQ = false;}
      if(aYBGCCUeoq == true){aYBGCCUeoq = false;}
      if(TYrydknfCa == true){TYrydknfCa = false;}
      if(CzrhJQaqOs == true){CzrhJQaqOs = false;}
      if(FdkwNZRxMm == true){FdkwNZRxMm = false;}
      if(WbWUbcsWyd == true){WbWUbcsWyd = false;}
      if(BphINafSwk == true){BphINafSwk = false;}
      if(bcQukonwjD == true){bcQukonwjD = false;}
      if(SqSPEacXGg == true){SqSPEacXGg = false;}
      if(WDskrPwbhl == true){WDskrPwbhl = false;}
      if(tyAaLsLaim == true){tyAaLsLaim = false;}
      if(oxmtKJWSEm == true){oxmtKJWSEm = false;}
      if(yIMPNXjeDV == true){yIMPNXjeDV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWPBTFZEFV
{ 
  void XPVIZPOfFi()
  { 
      bool urQkTrQztF = false;
      bool YiErmpnIPm = false;
      bool IRAQieZnwL = false;
      bool bciUsxSEEb = false;
      bool WIfTFeCQUd = false;
      bool KnYgzdrACn = false;
      bool RcChdwzizo = false;
      bool XjDmQAkfLE = false;
      bool cJSSAmDCVP = false;
      bool FSCQKsGypI = false;
      bool eSRfGakkPy = false;
      bool rLnyLIKigp = false;
      bool rwNiiEhmcW = false;
      bool slpCYJrlMZ = false;
      bool CSlWWtdDEC = false;
      bool iWQzPhFhxB = false;
      bool sxHsFGVkYC = false;
      bool PXWHnZKpMn = false;
      bool adiamWUpmp = false;
      bool DKnKfELsRQ = false;
      string skiITVXdrC;
      string ArGRwdYMnd;
      string tFmOmmXxWO;
      string iIqnCITyKe;
      string dAFNaiCzwx;
      string xDTiTnxTUg;
      string yaGcTrASPm;
      string JZBJAszZnE;
      string jXAYRenIUN;
      string KzcdfCtbti;
      string ijiJmWBKhZ;
      string nXfQwaagLn;
      string DqxBbKwXdx;
      string zXfFUznqkt;
      string cdZtYmTMhF;
      string bMPFeqlhgc;
      string ZdgkZQrauw;
      string ljwQLYRDcn;
      string pjoXUmHaZd;
      string NGJHTzxoTH;
      if(skiITVXdrC == ijiJmWBKhZ){urQkTrQztF = true;}
      else if(ijiJmWBKhZ == skiITVXdrC){eSRfGakkPy = true;}
      if(ArGRwdYMnd == nXfQwaagLn){YiErmpnIPm = true;}
      else if(nXfQwaagLn == ArGRwdYMnd){rLnyLIKigp = true;}
      if(tFmOmmXxWO == DqxBbKwXdx){IRAQieZnwL = true;}
      else if(DqxBbKwXdx == tFmOmmXxWO){rwNiiEhmcW = true;}
      if(iIqnCITyKe == zXfFUznqkt){bciUsxSEEb = true;}
      else if(zXfFUznqkt == iIqnCITyKe){slpCYJrlMZ = true;}
      if(dAFNaiCzwx == cdZtYmTMhF){WIfTFeCQUd = true;}
      else if(cdZtYmTMhF == dAFNaiCzwx){CSlWWtdDEC = true;}
      if(xDTiTnxTUg == bMPFeqlhgc){KnYgzdrACn = true;}
      else if(bMPFeqlhgc == xDTiTnxTUg){iWQzPhFhxB = true;}
      if(yaGcTrASPm == ZdgkZQrauw){RcChdwzizo = true;}
      else if(ZdgkZQrauw == yaGcTrASPm){sxHsFGVkYC = true;}
      if(JZBJAszZnE == ljwQLYRDcn){XjDmQAkfLE = true;}
      if(jXAYRenIUN == pjoXUmHaZd){cJSSAmDCVP = true;}
      if(KzcdfCtbti == NGJHTzxoTH){FSCQKsGypI = true;}
      while(ljwQLYRDcn == JZBJAszZnE){PXWHnZKpMn = true;}
      while(pjoXUmHaZd == pjoXUmHaZd){adiamWUpmp = true;}
      while(NGJHTzxoTH == NGJHTzxoTH){DKnKfELsRQ = true;}
      if(urQkTrQztF == true){urQkTrQztF = false;}
      if(YiErmpnIPm == true){YiErmpnIPm = false;}
      if(IRAQieZnwL == true){IRAQieZnwL = false;}
      if(bciUsxSEEb == true){bciUsxSEEb = false;}
      if(WIfTFeCQUd == true){WIfTFeCQUd = false;}
      if(KnYgzdrACn == true){KnYgzdrACn = false;}
      if(RcChdwzizo == true){RcChdwzizo = false;}
      if(XjDmQAkfLE == true){XjDmQAkfLE = false;}
      if(cJSSAmDCVP == true){cJSSAmDCVP = false;}
      if(FSCQKsGypI == true){FSCQKsGypI = false;}
      if(eSRfGakkPy == true){eSRfGakkPy = false;}
      if(rLnyLIKigp == true){rLnyLIKigp = false;}
      if(rwNiiEhmcW == true){rwNiiEhmcW = false;}
      if(slpCYJrlMZ == true){slpCYJrlMZ = false;}
      if(CSlWWtdDEC == true){CSlWWtdDEC = false;}
      if(iWQzPhFhxB == true){iWQzPhFhxB = false;}
      if(sxHsFGVkYC == true){sxHsFGVkYC = false;}
      if(PXWHnZKpMn == true){PXWHnZKpMn = false;}
      if(adiamWUpmp == true){adiamWUpmp = false;}
      if(DKnKfELsRQ == true){DKnKfELsRQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMJZDDDQYB
{ 
  void YwPHrHmPKh()
  { 
      bool eCWFWdDNNP = false;
      bool GeAIlrmaVg = false;
      bool fEnHiyTGnz = false;
      bool SgbEexlmRF = false;
      bool kLPpeCXblZ = false;
      bool xepMqaNOVX = false;
      bool JxZOwZCwdn = false;
      bool FzJQwTnycf = false;
      bool arUNCnpPMD = false;
      bool jXQswmlBsE = false;
      bool zayxUxVZQX = false;
      bool lOloxRbLMH = false;
      bool imjZEghPTI = false;
      bool hlFXfzsXsE = false;
      bool SQyoRUlawd = false;
      bool KZokVMqXrm = false;
      bool OFFHpzJNIx = false;
      bool XESHoSnuIj = false;
      bool uGSoxHxTCT = false;
      bool IUeFoMKqyR = false;
      string eWEENxroGz;
      string phnqInARXK;
      string ztkiVxslIn;
      string nWcuLKGejW;
      string yEJKDTdLpP;
      string ucBkmjkUhQ;
      string EFgRLSFrfy;
      string hVhBLtkafB;
      string SgwrsLVrHb;
      string YkwSRrWryk;
      string OkfrhZtzYr;
      string yKofxXJnXA;
      string wNkEYwYOiS;
      string WsbtmgAEJS;
      string QWSOcOwPVt;
      string ihTxoBAbSl;
      string BfQFVFitsP;
      string WFeFjYtVaK;
      string zIsojnZdFl;
      string gXkXRjGMsW;
      if(eWEENxroGz == OkfrhZtzYr){eCWFWdDNNP = true;}
      else if(OkfrhZtzYr == eWEENxroGz){zayxUxVZQX = true;}
      if(phnqInARXK == yKofxXJnXA){GeAIlrmaVg = true;}
      else if(yKofxXJnXA == phnqInARXK){lOloxRbLMH = true;}
      if(ztkiVxslIn == wNkEYwYOiS){fEnHiyTGnz = true;}
      else if(wNkEYwYOiS == ztkiVxslIn){imjZEghPTI = true;}
      if(nWcuLKGejW == WsbtmgAEJS){SgbEexlmRF = true;}
      else if(WsbtmgAEJS == nWcuLKGejW){hlFXfzsXsE = true;}
      if(yEJKDTdLpP == QWSOcOwPVt){kLPpeCXblZ = true;}
      else if(QWSOcOwPVt == yEJKDTdLpP){SQyoRUlawd = true;}
      if(ucBkmjkUhQ == ihTxoBAbSl){xepMqaNOVX = true;}
      else if(ihTxoBAbSl == ucBkmjkUhQ){KZokVMqXrm = true;}
      if(EFgRLSFrfy == BfQFVFitsP){JxZOwZCwdn = true;}
      else if(BfQFVFitsP == EFgRLSFrfy){OFFHpzJNIx = true;}
      if(hVhBLtkafB == WFeFjYtVaK){FzJQwTnycf = true;}
      if(SgwrsLVrHb == zIsojnZdFl){arUNCnpPMD = true;}
      if(YkwSRrWryk == gXkXRjGMsW){jXQswmlBsE = true;}
      while(WFeFjYtVaK == hVhBLtkafB){XESHoSnuIj = true;}
      while(zIsojnZdFl == zIsojnZdFl){uGSoxHxTCT = true;}
      while(gXkXRjGMsW == gXkXRjGMsW){IUeFoMKqyR = true;}
      if(eCWFWdDNNP == true){eCWFWdDNNP = false;}
      if(GeAIlrmaVg == true){GeAIlrmaVg = false;}
      if(fEnHiyTGnz == true){fEnHiyTGnz = false;}
      if(SgbEexlmRF == true){SgbEexlmRF = false;}
      if(kLPpeCXblZ == true){kLPpeCXblZ = false;}
      if(xepMqaNOVX == true){xepMqaNOVX = false;}
      if(JxZOwZCwdn == true){JxZOwZCwdn = false;}
      if(FzJQwTnycf == true){FzJQwTnycf = false;}
      if(arUNCnpPMD == true){arUNCnpPMD = false;}
      if(jXQswmlBsE == true){jXQswmlBsE = false;}
      if(zayxUxVZQX == true){zayxUxVZQX = false;}
      if(lOloxRbLMH == true){lOloxRbLMH = false;}
      if(imjZEghPTI == true){imjZEghPTI = false;}
      if(hlFXfzsXsE == true){hlFXfzsXsE = false;}
      if(SQyoRUlawd == true){SQyoRUlawd = false;}
      if(KZokVMqXrm == true){KZokVMqXrm = false;}
      if(OFFHpzJNIx == true){OFFHpzJNIx = false;}
      if(XESHoSnuIj == true){XESHoSnuIj = false;}
      if(uGSoxHxTCT == true){uGSoxHxTCT = false;}
      if(IUeFoMKqyR == true){IUeFoMKqyR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WBKREAIAHT
{ 
  void WCiMLnZPrZ()
  { 
      bool SRqlfAWlkm = false;
      bool xCzGceVYLl = false;
      bool wywxeiuwGC = false;
      bool lnhsbjuACS = false;
      bool shfSpduCmt = false;
      bool bhWjeTUsHx = false;
      bool FZfhAJUFer = false;
      bool iUVssOScGA = false;
      bool mrJMZDRxNH = false;
      bool PCsFMSBxRg = false;
      bool JoWtKGLcqQ = false;
      bool BqlHJMQTIx = false;
      bool qWrXcgbQfZ = false;
      bool MULZqyVOCT = false;
      bool qnGxGXPkuA = false;
      bool BhoUolxzRc = false;
      bool duwQDffMPL = false;
      bool qBQnFDPtQE = false;
      bool RpUfXdepjE = false;
      bool AVxYowrpsZ = false;
      string mUHchhGYit;
      string hKOnzDVFlS;
      string dHEpTJrBXq;
      string hJKMcTZhVr;
      string ZpfGOEltKd;
      string TetuneQQJX;
      string pFArLYABLf;
      string dnjtrnaxbO;
      string XxptWDPPYx;
      string CIYxBUonto;
      string EjheAfuACA;
      string ESouzrPGVI;
      string IjcNdVOlrX;
      string ymDlJnOKtp;
      string HPMXsiTcyJ;
      string EiRlgUHUBd;
      string QJHeBQPClL;
      string cELeAsWEUt;
      string BlmiSPUQFn;
      string gtJPYyHhWb;
      if(mUHchhGYit == EjheAfuACA){SRqlfAWlkm = true;}
      else if(EjheAfuACA == mUHchhGYit){JoWtKGLcqQ = true;}
      if(hKOnzDVFlS == ESouzrPGVI){xCzGceVYLl = true;}
      else if(ESouzrPGVI == hKOnzDVFlS){BqlHJMQTIx = true;}
      if(dHEpTJrBXq == IjcNdVOlrX){wywxeiuwGC = true;}
      else if(IjcNdVOlrX == dHEpTJrBXq){qWrXcgbQfZ = true;}
      if(hJKMcTZhVr == ymDlJnOKtp){lnhsbjuACS = true;}
      else if(ymDlJnOKtp == hJKMcTZhVr){MULZqyVOCT = true;}
      if(ZpfGOEltKd == HPMXsiTcyJ){shfSpduCmt = true;}
      else if(HPMXsiTcyJ == ZpfGOEltKd){qnGxGXPkuA = true;}
      if(TetuneQQJX == EiRlgUHUBd){bhWjeTUsHx = true;}
      else if(EiRlgUHUBd == TetuneQQJX){BhoUolxzRc = true;}
      if(pFArLYABLf == QJHeBQPClL){FZfhAJUFer = true;}
      else if(QJHeBQPClL == pFArLYABLf){duwQDffMPL = true;}
      if(dnjtrnaxbO == cELeAsWEUt){iUVssOScGA = true;}
      if(XxptWDPPYx == BlmiSPUQFn){mrJMZDRxNH = true;}
      if(CIYxBUonto == gtJPYyHhWb){PCsFMSBxRg = true;}
      while(cELeAsWEUt == dnjtrnaxbO){qBQnFDPtQE = true;}
      while(BlmiSPUQFn == BlmiSPUQFn){RpUfXdepjE = true;}
      while(gtJPYyHhWb == gtJPYyHhWb){AVxYowrpsZ = true;}
      if(SRqlfAWlkm == true){SRqlfAWlkm = false;}
      if(xCzGceVYLl == true){xCzGceVYLl = false;}
      if(wywxeiuwGC == true){wywxeiuwGC = false;}
      if(lnhsbjuACS == true){lnhsbjuACS = false;}
      if(shfSpduCmt == true){shfSpduCmt = false;}
      if(bhWjeTUsHx == true){bhWjeTUsHx = false;}
      if(FZfhAJUFer == true){FZfhAJUFer = false;}
      if(iUVssOScGA == true){iUVssOScGA = false;}
      if(mrJMZDRxNH == true){mrJMZDRxNH = false;}
      if(PCsFMSBxRg == true){PCsFMSBxRg = false;}
      if(JoWtKGLcqQ == true){JoWtKGLcqQ = false;}
      if(BqlHJMQTIx == true){BqlHJMQTIx = false;}
      if(qWrXcgbQfZ == true){qWrXcgbQfZ = false;}
      if(MULZqyVOCT == true){MULZqyVOCT = false;}
      if(qnGxGXPkuA == true){qnGxGXPkuA = false;}
      if(BhoUolxzRc == true){BhoUolxzRc = false;}
      if(duwQDffMPL == true){duwQDffMPL = false;}
      if(qBQnFDPtQE == true){qBQnFDPtQE = false;}
      if(RpUfXdepjE == true){RpUfXdepjE = false;}
      if(AVxYowrpsZ == true){AVxYowrpsZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SYZSWZKBZV
{ 
  void xlIrJiBRyg()
  { 
      bool qLomBrwEUS = false;
      bool XxVSGfbtzR = false;
      bool uMGITQMrkx = false;
      bool WnVcxcXzuo = false;
      bool VNVYXULDeA = false;
      bool qAoZbdEfTk = false;
      bool eDSXuibsVd = false;
      bool HcyJugqhkz = false;
      bool EJNjFWzuAS = false;
      bool XqfJJRtyco = false;
      bool rShBsOBedt = false;
      bool mVuTfVpiSY = false;
      bool ifrCFPwoAd = false;
      bool lsFwGlaMqp = false;
      bool UUQFfCwMdm = false;
      bool bLfDFMZeuc = false;
      bool SMdAHtQzMs = false;
      bool ucqbENOmWD = false;
      bool SiKMCaMCpt = false;
      bool MuQNXHpQxk = false;
      string jZRuSPWxyM;
      string hJIVzJwpOe;
      string NfXbzXziGf;
      string wHBPshZrlQ;
      string eedENFslKd;
      string FhjqLDCowu;
      string PmpRPZHsbQ;
      string iEExAhBSOt;
      string dNYcaNXKEo;
      string fjwpBqoMnm;
      string xAJstBdlpc;
      string CiaBQBOMqB;
      string CxomkyHNwJ;
      string sndbwdDehZ;
      string jkUalwJtZz;
      string bbVmjALWIu;
      string sPpfiOEyFl;
      string yjeRRRcNAo;
      string nNmwgRSqqw;
      string SgWlfTtnqX;
      if(jZRuSPWxyM == xAJstBdlpc){qLomBrwEUS = true;}
      else if(xAJstBdlpc == jZRuSPWxyM){rShBsOBedt = true;}
      if(hJIVzJwpOe == CiaBQBOMqB){XxVSGfbtzR = true;}
      else if(CiaBQBOMqB == hJIVzJwpOe){mVuTfVpiSY = true;}
      if(NfXbzXziGf == CxomkyHNwJ){uMGITQMrkx = true;}
      else if(CxomkyHNwJ == NfXbzXziGf){ifrCFPwoAd = true;}
      if(wHBPshZrlQ == sndbwdDehZ){WnVcxcXzuo = true;}
      else if(sndbwdDehZ == wHBPshZrlQ){lsFwGlaMqp = true;}
      if(eedENFslKd == jkUalwJtZz){VNVYXULDeA = true;}
      else if(jkUalwJtZz == eedENFslKd){UUQFfCwMdm = true;}
      if(FhjqLDCowu == bbVmjALWIu){qAoZbdEfTk = true;}
      else if(bbVmjALWIu == FhjqLDCowu){bLfDFMZeuc = true;}
      if(PmpRPZHsbQ == sPpfiOEyFl){eDSXuibsVd = true;}
      else if(sPpfiOEyFl == PmpRPZHsbQ){SMdAHtQzMs = true;}
      if(iEExAhBSOt == yjeRRRcNAo){HcyJugqhkz = true;}
      if(dNYcaNXKEo == nNmwgRSqqw){EJNjFWzuAS = true;}
      if(fjwpBqoMnm == SgWlfTtnqX){XqfJJRtyco = true;}
      while(yjeRRRcNAo == iEExAhBSOt){ucqbENOmWD = true;}
      while(nNmwgRSqqw == nNmwgRSqqw){SiKMCaMCpt = true;}
      while(SgWlfTtnqX == SgWlfTtnqX){MuQNXHpQxk = true;}
      if(qLomBrwEUS == true){qLomBrwEUS = false;}
      if(XxVSGfbtzR == true){XxVSGfbtzR = false;}
      if(uMGITQMrkx == true){uMGITQMrkx = false;}
      if(WnVcxcXzuo == true){WnVcxcXzuo = false;}
      if(VNVYXULDeA == true){VNVYXULDeA = false;}
      if(qAoZbdEfTk == true){qAoZbdEfTk = false;}
      if(eDSXuibsVd == true){eDSXuibsVd = false;}
      if(HcyJugqhkz == true){HcyJugqhkz = false;}
      if(EJNjFWzuAS == true){EJNjFWzuAS = false;}
      if(XqfJJRtyco == true){XqfJJRtyco = false;}
      if(rShBsOBedt == true){rShBsOBedt = false;}
      if(mVuTfVpiSY == true){mVuTfVpiSY = false;}
      if(ifrCFPwoAd == true){ifrCFPwoAd = false;}
      if(lsFwGlaMqp == true){lsFwGlaMqp = false;}
      if(UUQFfCwMdm == true){UUQFfCwMdm = false;}
      if(bLfDFMZeuc == true){bLfDFMZeuc = false;}
      if(SMdAHtQzMs == true){SMdAHtQzMs = false;}
      if(ucqbENOmWD == true){ucqbENOmWD = false;}
      if(SiKMCaMCpt == true){SiKMCaMCpt = false;}
      if(MuQNXHpQxk == true){MuQNXHpQxk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BTUPOZQOTG
{ 
  void lYKrpoXmiq()
  { 
      bool GnSFdFdKHp = false;
      bool yckcxYfpRz = false;
      bool QrwdwWNLej = false;
      bool yGLAtgfuhQ = false;
      bool TRTWAJUIpG = false;
      bool DcIWjNqoIH = false;
      bool rSeWrqQkiQ = false;
      bool rjIBfzYZcm = false;
      bool BEUXgVyoPf = false;
      bool oqmZYAlwdI = false;
      bool rjZYOTTHqk = false;
      bool nRLVFmyHpW = false;
      bool sbUDbBxhce = false;
      bool McuUtQeuJM = false;
      bool BpyeqXeQUk = false;
      bool CeFHOQOWxM = false;
      bool VleLYLVqbo = false;
      bool HCxcUCdpLE = false;
      bool WfNqcgXnFd = false;
      bool BIywqPLlFf = false;
      string jZVaApeVfg;
      string dYbtBHPPSE;
      string AJqgMMruVq;
      string NCwhMePQHY;
      string GlZdTFEQac;
      string RcNPoaioNm;
      string xjzoTacthW;
      string ryItyOiMMG;
      string HbTrYjofsl;
      string wZCTbVlkKs;
      string bKiEkTUTQZ;
      string qVcGfVPHPi;
      string lwAwaRunRc;
      string cxCTewrPHE;
      string PUOStZxunG;
      string FdVaGfKldS;
      string YfBnxsTIbi;
      string cAAKTQggBA;
      string UzALWybaMy;
      string lGlnfiSaVB;
      if(jZVaApeVfg == bKiEkTUTQZ){GnSFdFdKHp = true;}
      else if(bKiEkTUTQZ == jZVaApeVfg){rjZYOTTHqk = true;}
      if(dYbtBHPPSE == qVcGfVPHPi){yckcxYfpRz = true;}
      else if(qVcGfVPHPi == dYbtBHPPSE){nRLVFmyHpW = true;}
      if(AJqgMMruVq == lwAwaRunRc){QrwdwWNLej = true;}
      else if(lwAwaRunRc == AJqgMMruVq){sbUDbBxhce = true;}
      if(NCwhMePQHY == cxCTewrPHE){yGLAtgfuhQ = true;}
      else if(cxCTewrPHE == NCwhMePQHY){McuUtQeuJM = true;}
      if(GlZdTFEQac == PUOStZxunG){TRTWAJUIpG = true;}
      else if(PUOStZxunG == GlZdTFEQac){BpyeqXeQUk = true;}
      if(RcNPoaioNm == FdVaGfKldS){DcIWjNqoIH = true;}
      else if(FdVaGfKldS == RcNPoaioNm){CeFHOQOWxM = true;}
      if(xjzoTacthW == YfBnxsTIbi){rSeWrqQkiQ = true;}
      else if(YfBnxsTIbi == xjzoTacthW){VleLYLVqbo = true;}
      if(ryItyOiMMG == cAAKTQggBA){rjIBfzYZcm = true;}
      if(HbTrYjofsl == UzALWybaMy){BEUXgVyoPf = true;}
      if(wZCTbVlkKs == lGlnfiSaVB){oqmZYAlwdI = true;}
      while(cAAKTQggBA == ryItyOiMMG){HCxcUCdpLE = true;}
      while(UzALWybaMy == UzALWybaMy){WfNqcgXnFd = true;}
      while(lGlnfiSaVB == lGlnfiSaVB){BIywqPLlFf = true;}
      if(GnSFdFdKHp == true){GnSFdFdKHp = false;}
      if(yckcxYfpRz == true){yckcxYfpRz = false;}
      if(QrwdwWNLej == true){QrwdwWNLej = false;}
      if(yGLAtgfuhQ == true){yGLAtgfuhQ = false;}
      if(TRTWAJUIpG == true){TRTWAJUIpG = false;}
      if(DcIWjNqoIH == true){DcIWjNqoIH = false;}
      if(rSeWrqQkiQ == true){rSeWrqQkiQ = false;}
      if(rjIBfzYZcm == true){rjIBfzYZcm = false;}
      if(BEUXgVyoPf == true){BEUXgVyoPf = false;}
      if(oqmZYAlwdI == true){oqmZYAlwdI = false;}
      if(rjZYOTTHqk == true){rjZYOTTHqk = false;}
      if(nRLVFmyHpW == true){nRLVFmyHpW = false;}
      if(sbUDbBxhce == true){sbUDbBxhce = false;}
      if(McuUtQeuJM == true){McuUtQeuJM = false;}
      if(BpyeqXeQUk == true){BpyeqXeQUk = false;}
      if(CeFHOQOWxM == true){CeFHOQOWxM = false;}
      if(VleLYLVqbo == true){VleLYLVqbo = false;}
      if(HCxcUCdpLE == true){HCxcUCdpLE = false;}
      if(WfNqcgXnFd == true){WfNqcgXnFd = false;}
      if(BIywqPLlFf == true){BIywqPLlFf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VZFLLHRXVR
{ 
  void rZYppgbTkI()
  { 
      bool JyKWDzHLPV = false;
      bool uZnzLKAexV = false;
      bool hkptjfLlGy = false;
      bool HKHIlbKEqC = false;
      bool DQfzinGpEJ = false;
      bool GfehiYIPlW = false;
      bool nVFQOkSeMj = false;
      bool zumuSRFpLw = false;
      bool YVgxqaeYZN = false;
      bool TtRTOgLOjy = false;
      bool UacUJLrjPQ = false;
      bool SREpxRoHZn = false;
      bool FsEzQEcSfk = false;
      bool GqGMayrLnf = false;
      bool huJItCpbWw = false;
      bool rDowsbWdEE = false;
      bool hYDdKbLqPz = false;
      bool YcTtFJjwEN = false;
      bool OBwjsCBJTy = false;
      bool aOHixIqexR = false;
      string sITtnLftxo;
      string MOTJnblKJd;
      string gsiqAHAbOp;
      string rVUfDMJOxX;
      string ouSHkqXYJo;
      string HkjppAYctf;
      string LDeHxpsnGa;
      string RXMknlZbFJ;
      string ibSZhHkepC;
      string ngTQMlPLKt;
      string xjShWiXzCD;
      string ZxWkxikFYo;
      string FOyDmkEuYC;
      string VOQKLzJjCy;
      string ilblcpKiTc;
      string AKlVohlOul;
      string ebZzhLgLYx;
      string ZACZFSmLaw;
      string ZUbuCLcuVd;
      string NtoQTHLbER;
      if(sITtnLftxo == xjShWiXzCD){JyKWDzHLPV = true;}
      else if(xjShWiXzCD == sITtnLftxo){UacUJLrjPQ = true;}
      if(MOTJnblKJd == ZxWkxikFYo){uZnzLKAexV = true;}
      else if(ZxWkxikFYo == MOTJnblKJd){SREpxRoHZn = true;}
      if(gsiqAHAbOp == FOyDmkEuYC){hkptjfLlGy = true;}
      else if(FOyDmkEuYC == gsiqAHAbOp){FsEzQEcSfk = true;}
      if(rVUfDMJOxX == VOQKLzJjCy){HKHIlbKEqC = true;}
      else if(VOQKLzJjCy == rVUfDMJOxX){GqGMayrLnf = true;}
      if(ouSHkqXYJo == ilblcpKiTc){DQfzinGpEJ = true;}
      else if(ilblcpKiTc == ouSHkqXYJo){huJItCpbWw = true;}
      if(HkjppAYctf == AKlVohlOul){GfehiYIPlW = true;}
      else if(AKlVohlOul == HkjppAYctf){rDowsbWdEE = true;}
      if(LDeHxpsnGa == ebZzhLgLYx){nVFQOkSeMj = true;}
      else if(ebZzhLgLYx == LDeHxpsnGa){hYDdKbLqPz = true;}
      if(RXMknlZbFJ == ZACZFSmLaw){zumuSRFpLw = true;}
      if(ibSZhHkepC == ZUbuCLcuVd){YVgxqaeYZN = true;}
      if(ngTQMlPLKt == NtoQTHLbER){TtRTOgLOjy = true;}
      while(ZACZFSmLaw == RXMknlZbFJ){YcTtFJjwEN = true;}
      while(ZUbuCLcuVd == ZUbuCLcuVd){OBwjsCBJTy = true;}
      while(NtoQTHLbER == NtoQTHLbER){aOHixIqexR = true;}
      if(JyKWDzHLPV == true){JyKWDzHLPV = false;}
      if(uZnzLKAexV == true){uZnzLKAexV = false;}
      if(hkptjfLlGy == true){hkptjfLlGy = false;}
      if(HKHIlbKEqC == true){HKHIlbKEqC = false;}
      if(DQfzinGpEJ == true){DQfzinGpEJ = false;}
      if(GfehiYIPlW == true){GfehiYIPlW = false;}
      if(nVFQOkSeMj == true){nVFQOkSeMj = false;}
      if(zumuSRFpLw == true){zumuSRFpLw = false;}
      if(YVgxqaeYZN == true){YVgxqaeYZN = false;}
      if(TtRTOgLOjy == true){TtRTOgLOjy = false;}
      if(UacUJLrjPQ == true){UacUJLrjPQ = false;}
      if(SREpxRoHZn == true){SREpxRoHZn = false;}
      if(FsEzQEcSfk == true){FsEzQEcSfk = false;}
      if(GqGMayrLnf == true){GqGMayrLnf = false;}
      if(huJItCpbWw == true){huJItCpbWw = false;}
      if(rDowsbWdEE == true){rDowsbWdEE = false;}
      if(hYDdKbLqPz == true){hYDdKbLqPz = false;}
      if(YcTtFJjwEN == true){YcTtFJjwEN = false;}
      if(OBwjsCBJTy == true){OBwjsCBJTy = false;}
      if(aOHixIqexR == true){aOHixIqexR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UGPZNQVXQI
{ 
  void PljxdItfEo()
  { 
      bool qloPSowZER = false;
      bool dpwGwrmPAc = false;
      bool yoacyWZQxu = false;
      bool dSRtLPFiqs = false;
      bool BkHPAGfKcx = false;
      bool sfQMiBLMQu = false;
      bool PecJnKXBuf = false;
      bool mEXGbNgLcr = false;
      bool pOnzBxCEKJ = false;
      bool ErRudVIyao = false;
      bool hdPwKnIJkV = false;
      bool UzjYEApcHq = false;
      bool ISqkbtlbcF = false;
      bool FijnJMzroN = false;
      bool orTooEIsqc = false;
      bool fepifPmeUP = false;
      bool BfgePkPuOr = false;
      bool BymtCPzBuW = false;
      bool kskAZasBHt = false;
      bool YTXYLJLoZE = false;
      string eWOgtaTOyf;
      string mEVzpwkSKN;
      string NyFSjmfVjb;
      string VUQVFFXuHO;
      string ydykFoWloS;
      string UHxPtgQuwG;
      string uydWJSmAsj;
      string XpKuPjzUMu;
      string QtfQHOWBbY;
      string nbyBTzzbam;
      string BWrFtewBAK;
      string guhBpBSMOt;
      string ulYTuwqJbP;
      string jXsZstBaWb;
      string SVBQrstxLS;
      string glMgrOxYJy;
      string mlYjaJCIHu;
      string zqplbZkHbC;
      string BtyJixKMgd;
      string wcRYogwRph;
      if(eWOgtaTOyf == BWrFtewBAK){qloPSowZER = true;}
      else if(BWrFtewBAK == eWOgtaTOyf){hdPwKnIJkV = true;}
      if(mEVzpwkSKN == guhBpBSMOt){dpwGwrmPAc = true;}
      else if(guhBpBSMOt == mEVzpwkSKN){UzjYEApcHq = true;}
      if(NyFSjmfVjb == ulYTuwqJbP){yoacyWZQxu = true;}
      else if(ulYTuwqJbP == NyFSjmfVjb){ISqkbtlbcF = true;}
      if(VUQVFFXuHO == jXsZstBaWb){dSRtLPFiqs = true;}
      else if(jXsZstBaWb == VUQVFFXuHO){FijnJMzroN = true;}
      if(ydykFoWloS == SVBQrstxLS){BkHPAGfKcx = true;}
      else if(SVBQrstxLS == ydykFoWloS){orTooEIsqc = true;}
      if(UHxPtgQuwG == glMgrOxYJy){sfQMiBLMQu = true;}
      else if(glMgrOxYJy == UHxPtgQuwG){fepifPmeUP = true;}
      if(uydWJSmAsj == mlYjaJCIHu){PecJnKXBuf = true;}
      else if(mlYjaJCIHu == uydWJSmAsj){BfgePkPuOr = true;}
      if(XpKuPjzUMu == zqplbZkHbC){mEXGbNgLcr = true;}
      if(QtfQHOWBbY == BtyJixKMgd){pOnzBxCEKJ = true;}
      if(nbyBTzzbam == wcRYogwRph){ErRudVIyao = true;}
      while(zqplbZkHbC == XpKuPjzUMu){BymtCPzBuW = true;}
      while(BtyJixKMgd == BtyJixKMgd){kskAZasBHt = true;}
      while(wcRYogwRph == wcRYogwRph){YTXYLJLoZE = true;}
      if(qloPSowZER == true){qloPSowZER = false;}
      if(dpwGwrmPAc == true){dpwGwrmPAc = false;}
      if(yoacyWZQxu == true){yoacyWZQxu = false;}
      if(dSRtLPFiqs == true){dSRtLPFiqs = false;}
      if(BkHPAGfKcx == true){BkHPAGfKcx = false;}
      if(sfQMiBLMQu == true){sfQMiBLMQu = false;}
      if(PecJnKXBuf == true){PecJnKXBuf = false;}
      if(mEXGbNgLcr == true){mEXGbNgLcr = false;}
      if(pOnzBxCEKJ == true){pOnzBxCEKJ = false;}
      if(ErRudVIyao == true){ErRudVIyao = false;}
      if(hdPwKnIJkV == true){hdPwKnIJkV = false;}
      if(UzjYEApcHq == true){UzjYEApcHq = false;}
      if(ISqkbtlbcF == true){ISqkbtlbcF = false;}
      if(FijnJMzroN == true){FijnJMzroN = false;}
      if(orTooEIsqc == true){orTooEIsqc = false;}
      if(fepifPmeUP == true){fepifPmeUP = false;}
      if(BfgePkPuOr == true){BfgePkPuOr = false;}
      if(BymtCPzBuW == true){BymtCPzBuW = false;}
      if(kskAZasBHt == true){kskAZasBHt = false;}
      if(YTXYLJLoZE == true){YTXYLJLoZE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ABZIYULXBD
{ 
  void hNLlCRsZAq()
  { 
      bool EHQbpIgYxT = false;
      bool tDbsCofIKj = false;
      bool xiViofqABP = false;
      bool oCZdnzQxgi = false;
      bool jDgVcigqoy = false;
      bool RTTKCVkhmJ = false;
      bool QfWgdrdxEC = false;
      bool YhbbAtCAGF = false;
      bool yALDyUhPbR = false;
      bool NiKWREfzqj = false;
      bool FjllZiqrJH = false;
      bool SkagKQTTiJ = false;
      bool JOVmnoXFJw = false;
      bool ODIVAONYcO = false;
      bool dpFTycHdMB = false;
      bool jMPhZqOzxj = false;
      bool LlhNsPbFfw = false;
      bool DupUeTIBnL = false;
      bool hsrIMBnauJ = false;
      bool zNbsCqIrai = false;
      string kfhIcTNWmz;
      string berObFLsIK;
      string zLHLKrkxwy;
      string qLDmRtacZU;
      string zrElZTtJdM;
      string LDVpyYYWyk;
      string hQanHPbFxg;
      string diTnLHHUkq;
      string ybSimnpMnr;
      string VEdoliQPeK;
      string qnLwibjheq;
      string RDlGlGyrAS;
      string ZOQFKZFdCb;
      string pqpZzJQVAK;
      string EHhwZSSXDf;
      string jYOLkbXGkI;
      string WGeCBZNLGb;
      string pbrpORgUer;
      string GgZWqQbdoX;
      string lJjqnycetA;
      if(kfhIcTNWmz == qnLwibjheq){EHQbpIgYxT = true;}
      else if(qnLwibjheq == kfhIcTNWmz){FjllZiqrJH = true;}
      if(berObFLsIK == RDlGlGyrAS){tDbsCofIKj = true;}
      else if(RDlGlGyrAS == berObFLsIK){SkagKQTTiJ = true;}
      if(zLHLKrkxwy == ZOQFKZFdCb){xiViofqABP = true;}
      else if(ZOQFKZFdCb == zLHLKrkxwy){JOVmnoXFJw = true;}
      if(qLDmRtacZU == pqpZzJQVAK){oCZdnzQxgi = true;}
      else if(pqpZzJQVAK == qLDmRtacZU){ODIVAONYcO = true;}
      if(zrElZTtJdM == EHhwZSSXDf){jDgVcigqoy = true;}
      else if(EHhwZSSXDf == zrElZTtJdM){dpFTycHdMB = true;}
      if(LDVpyYYWyk == jYOLkbXGkI){RTTKCVkhmJ = true;}
      else if(jYOLkbXGkI == LDVpyYYWyk){jMPhZqOzxj = true;}
      if(hQanHPbFxg == WGeCBZNLGb){QfWgdrdxEC = true;}
      else if(WGeCBZNLGb == hQanHPbFxg){LlhNsPbFfw = true;}
      if(diTnLHHUkq == pbrpORgUer){YhbbAtCAGF = true;}
      if(ybSimnpMnr == GgZWqQbdoX){yALDyUhPbR = true;}
      if(VEdoliQPeK == lJjqnycetA){NiKWREfzqj = true;}
      while(pbrpORgUer == diTnLHHUkq){DupUeTIBnL = true;}
      while(GgZWqQbdoX == GgZWqQbdoX){hsrIMBnauJ = true;}
      while(lJjqnycetA == lJjqnycetA){zNbsCqIrai = true;}
      if(EHQbpIgYxT == true){EHQbpIgYxT = false;}
      if(tDbsCofIKj == true){tDbsCofIKj = false;}
      if(xiViofqABP == true){xiViofqABP = false;}
      if(oCZdnzQxgi == true){oCZdnzQxgi = false;}
      if(jDgVcigqoy == true){jDgVcigqoy = false;}
      if(RTTKCVkhmJ == true){RTTKCVkhmJ = false;}
      if(QfWgdrdxEC == true){QfWgdrdxEC = false;}
      if(YhbbAtCAGF == true){YhbbAtCAGF = false;}
      if(yALDyUhPbR == true){yALDyUhPbR = false;}
      if(NiKWREfzqj == true){NiKWREfzqj = false;}
      if(FjllZiqrJH == true){FjllZiqrJH = false;}
      if(SkagKQTTiJ == true){SkagKQTTiJ = false;}
      if(JOVmnoXFJw == true){JOVmnoXFJw = false;}
      if(ODIVAONYcO == true){ODIVAONYcO = false;}
      if(dpFTycHdMB == true){dpFTycHdMB = false;}
      if(jMPhZqOzxj == true){jMPhZqOzxj = false;}
      if(LlhNsPbFfw == true){LlhNsPbFfw = false;}
      if(DupUeTIBnL == true){DupUeTIBnL = false;}
      if(hsrIMBnauJ == true){hsrIMBnauJ = false;}
      if(zNbsCqIrai == true){zNbsCqIrai = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FDGPAMIEHM
{ 
  void jgnRZMWmIy()
  { 
      bool NAPwkRHwyN = false;
      bool kjokyhATxp = false;
      bool NwUEekMRbK = false;
      bool qhhKDHhZYV = false;
      bool NRYwbBuSQs = false;
      bool BxdJZQfLQz = false;
      bool FoTnWDBegp = false;
      bool AauabuWXbd = false;
      bool psBhItDYkm = false;
      bool bWIYQXykZY = false;
      bool zPkZsaBDgd = false;
      bool tHimJLmkeb = false;
      bool zcttOdRWKE = false;
      bool wkxCdZIboh = false;
      bool rAqGrUmVOF = false;
      bool jNGyYVVpLP = false;
      bool IerchIJfJj = false;
      bool DLwwizlnCt = false;
      bool pwHFTiezcH = false;
      bool ERQYZNHNYj = false;
      string gYEyuHbNuU;
      string DKaoAzBrmT;
      string IPqgtFottR;
      string EGMBWQQMYT;
      string oIoMXRmRkd;
      string zYPnUQgWDo;
      string RgSdQwxZRi;
      string hnSTeAZeJc;
      string SXJQSeqXfF;
      string jtIjBHpLwb;
      string TMzBuKFuJU;
      string pCNaWtXCLk;
      string EYtMzneiRX;
      string JOhhIFXHUH;
      string YuOLOgfhNH;
      string inAKWuSmCG;
      string eWdlLbTfRQ;
      string VQgDMIKhxR;
      string IxVJnUOXKN;
      string lkEObCRbAm;
      if(gYEyuHbNuU == TMzBuKFuJU){NAPwkRHwyN = true;}
      else if(TMzBuKFuJU == gYEyuHbNuU){zPkZsaBDgd = true;}
      if(DKaoAzBrmT == pCNaWtXCLk){kjokyhATxp = true;}
      else if(pCNaWtXCLk == DKaoAzBrmT){tHimJLmkeb = true;}
      if(IPqgtFottR == EYtMzneiRX){NwUEekMRbK = true;}
      else if(EYtMzneiRX == IPqgtFottR){zcttOdRWKE = true;}
      if(EGMBWQQMYT == JOhhIFXHUH){qhhKDHhZYV = true;}
      else if(JOhhIFXHUH == EGMBWQQMYT){wkxCdZIboh = true;}
      if(oIoMXRmRkd == YuOLOgfhNH){NRYwbBuSQs = true;}
      else if(YuOLOgfhNH == oIoMXRmRkd){rAqGrUmVOF = true;}
      if(zYPnUQgWDo == inAKWuSmCG){BxdJZQfLQz = true;}
      else if(inAKWuSmCG == zYPnUQgWDo){jNGyYVVpLP = true;}
      if(RgSdQwxZRi == eWdlLbTfRQ){FoTnWDBegp = true;}
      else if(eWdlLbTfRQ == RgSdQwxZRi){IerchIJfJj = true;}
      if(hnSTeAZeJc == VQgDMIKhxR){AauabuWXbd = true;}
      if(SXJQSeqXfF == IxVJnUOXKN){psBhItDYkm = true;}
      if(jtIjBHpLwb == lkEObCRbAm){bWIYQXykZY = true;}
      while(VQgDMIKhxR == hnSTeAZeJc){DLwwizlnCt = true;}
      while(IxVJnUOXKN == IxVJnUOXKN){pwHFTiezcH = true;}
      while(lkEObCRbAm == lkEObCRbAm){ERQYZNHNYj = true;}
      if(NAPwkRHwyN == true){NAPwkRHwyN = false;}
      if(kjokyhATxp == true){kjokyhATxp = false;}
      if(NwUEekMRbK == true){NwUEekMRbK = false;}
      if(qhhKDHhZYV == true){qhhKDHhZYV = false;}
      if(NRYwbBuSQs == true){NRYwbBuSQs = false;}
      if(BxdJZQfLQz == true){BxdJZQfLQz = false;}
      if(FoTnWDBegp == true){FoTnWDBegp = false;}
      if(AauabuWXbd == true){AauabuWXbd = false;}
      if(psBhItDYkm == true){psBhItDYkm = false;}
      if(bWIYQXykZY == true){bWIYQXykZY = false;}
      if(zPkZsaBDgd == true){zPkZsaBDgd = false;}
      if(tHimJLmkeb == true){tHimJLmkeb = false;}
      if(zcttOdRWKE == true){zcttOdRWKE = false;}
      if(wkxCdZIboh == true){wkxCdZIboh = false;}
      if(rAqGrUmVOF == true){rAqGrUmVOF = false;}
      if(jNGyYVVpLP == true){jNGyYVVpLP = false;}
      if(IerchIJfJj == true){IerchIJfJj = false;}
      if(DLwwizlnCt == true){DLwwizlnCt = false;}
      if(pwHFTiezcH == true){pwHFTiezcH = false;}
      if(ERQYZNHNYj == true){ERQYZNHNYj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MDPZHCFLLF
{ 
  void AZdKiTXVtx()
  { 
      bool yAdoEljgnX = false;
      bool ljkEsXOmXq = false;
      bool hBcGVrxVgP = false;
      bool UUtADcDssf = false;
      bool AOBSPCrKIe = false;
      bool GXcOIxXXTM = false;
      bool oOzYDQpjAQ = false;
      bool TVsrqTzKpS = false;
      bool zmNCJxreqF = false;
      bool EfZgpkOcPz = false;
      bool MHKqLkdkWo = false;
      bool yNgAMCAxPF = false;
      bool XKrtLmuMBG = false;
      bool EWupGrcVqX = false;
      bool SHICHqyZTn = false;
      bool jRMJaCOPfX = false;
      bool oRiQjbSqtU = false;
      bool YeGqlQBolU = false;
      bool oVsMVlJkOE = false;
      bool cMpSiBXrSf = false;
      string dWdSOfNoSd;
      string YOOBkGhywd;
      string xNWoRwKKxn;
      string dpBabwYGsW;
      string hxpdNjGOoD;
      string ChjCVPzoAS;
      string VCqeAhMnYo;
      string haFZwzXsah;
      string ouVtkuGyEM;
      string wiFZAfFLdf;
      string WSozVbcJGV;
      string qGOSdagxsE;
      string bOiMsyUeYQ;
      string sMPtKVFVYJ;
      string SwqiUpUmwZ;
      string yIRYDIjcGW;
      string GxkpcdqTIH;
      string ULXjkfWAqC;
      string dhhyRkuppB;
      string lcOBCVKBGq;
      if(dWdSOfNoSd == WSozVbcJGV){yAdoEljgnX = true;}
      else if(WSozVbcJGV == dWdSOfNoSd){MHKqLkdkWo = true;}
      if(YOOBkGhywd == qGOSdagxsE){ljkEsXOmXq = true;}
      else if(qGOSdagxsE == YOOBkGhywd){yNgAMCAxPF = true;}
      if(xNWoRwKKxn == bOiMsyUeYQ){hBcGVrxVgP = true;}
      else if(bOiMsyUeYQ == xNWoRwKKxn){XKrtLmuMBG = true;}
      if(dpBabwYGsW == sMPtKVFVYJ){UUtADcDssf = true;}
      else if(sMPtKVFVYJ == dpBabwYGsW){EWupGrcVqX = true;}
      if(hxpdNjGOoD == SwqiUpUmwZ){AOBSPCrKIe = true;}
      else if(SwqiUpUmwZ == hxpdNjGOoD){SHICHqyZTn = true;}
      if(ChjCVPzoAS == yIRYDIjcGW){GXcOIxXXTM = true;}
      else if(yIRYDIjcGW == ChjCVPzoAS){jRMJaCOPfX = true;}
      if(VCqeAhMnYo == GxkpcdqTIH){oOzYDQpjAQ = true;}
      else if(GxkpcdqTIH == VCqeAhMnYo){oRiQjbSqtU = true;}
      if(haFZwzXsah == ULXjkfWAqC){TVsrqTzKpS = true;}
      if(ouVtkuGyEM == dhhyRkuppB){zmNCJxreqF = true;}
      if(wiFZAfFLdf == lcOBCVKBGq){EfZgpkOcPz = true;}
      while(ULXjkfWAqC == haFZwzXsah){YeGqlQBolU = true;}
      while(dhhyRkuppB == dhhyRkuppB){oVsMVlJkOE = true;}
      while(lcOBCVKBGq == lcOBCVKBGq){cMpSiBXrSf = true;}
      if(yAdoEljgnX == true){yAdoEljgnX = false;}
      if(ljkEsXOmXq == true){ljkEsXOmXq = false;}
      if(hBcGVrxVgP == true){hBcGVrxVgP = false;}
      if(UUtADcDssf == true){UUtADcDssf = false;}
      if(AOBSPCrKIe == true){AOBSPCrKIe = false;}
      if(GXcOIxXXTM == true){GXcOIxXXTM = false;}
      if(oOzYDQpjAQ == true){oOzYDQpjAQ = false;}
      if(TVsrqTzKpS == true){TVsrqTzKpS = false;}
      if(zmNCJxreqF == true){zmNCJxreqF = false;}
      if(EfZgpkOcPz == true){EfZgpkOcPz = false;}
      if(MHKqLkdkWo == true){MHKqLkdkWo = false;}
      if(yNgAMCAxPF == true){yNgAMCAxPF = false;}
      if(XKrtLmuMBG == true){XKrtLmuMBG = false;}
      if(EWupGrcVqX == true){EWupGrcVqX = false;}
      if(SHICHqyZTn == true){SHICHqyZTn = false;}
      if(jRMJaCOPfX == true){jRMJaCOPfX = false;}
      if(oRiQjbSqtU == true){oRiQjbSqtU = false;}
      if(YeGqlQBolU == true){YeGqlQBolU = false;}
      if(oVsMVlJkOE == true){oVsMVlJkOE = false;}
      if(cMpSiBXrSf == true){cMpSiBXrSf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDBEDIMFMF
{ 
  void JswagWzPEZ()
  { 
      bool kPmpEzzGNC = false;
      bool iSHKXdAWuW = false;
      bool VAWieUqLli = false;
      bool NXLsLjpxAC = false;
      bool DSAMuCdzyI = false;
      bool AIcshjsEKi = false;
      bool HnUenLHNym = false;
      bool nCWsTDzKmc = false;
      bool qrNchFtRLa = false;
      bool qkmQtOxUXi = false;
      bool uPAKTykjZe = false;
      bool khQhrPaqxi = false;
      bool RoCWwDPFzE = false;
      bool FdlEgarCIj = false;
      bool TKrgpITEYd = false;
      bool nGXoRGNcNQ = false;
      bool hfkUYGwMBQ = false;
      bool XXhNPHwUfm = false;
      bool iKfUPyGxmZ = false;
      bool NOorBmZXHj = false;
      string CHyNSPgsRG;
      string ETdrLyBzIW;
      string AAtxkSfuwS;
      string VHjHznyzJn;
      string DGxJrflraa;
      string mKKQECMAbz;
      string ilxzkxjWrX;
      string ABpTSsCkEF;
      string gnTUfKxSCx;
      string axWKERJyXu;
      string wPzDalUpxK;
      string zbuWSuRbSZ;
      string zQTuwCdfOB;
      string jEMJJQoQtt;
      string pGUqyzBAqJ;
      string AgeyueuEHX;
      string HnbwatOlMB;
      string FAgYjsucww;
      string AcnEBDYOOd;
      string VkJVlBeXQD;
      if(CHyNSPgsRG == wPzDalUpxK){kPmpEzzGNC = true;}
      else if(wPzDalUpxK == CHyNSPgsRG){uPAKTykjZe = true;}
      if(ETdrLyBzIW == zbuWSuRbSZ){iSHKXdAWuW = true;}
      else if(zbuWSuRbSZ == ETdrLyBzIW){khQhrPaqxi = true;}
      if(AAtxkSfuwS == zQTuwCdfOB){VAWieUqLli = true;}
      else if(zQTuwCdfOB == AAtxkSfuwS){RoCWwDPFzE = true;}
      if(VHjHznyzJn == jEMJJQoQtt){NXLsLjpxAC = true;}
      else if(jEMJJQoQtt == VHjHznyzJn){FdlEgarCIj = true;}
      if(DGxJrflraa == pGUqyzBAqJ){DSAMuCdzyI = true;}
      else if(pGUqyzBAqJ == DGxJrflraa){TKrgpITEYd = true;}
      if(mKKQECMAbz == AgeyueuEHX){AIcshjsEKi = true;}
      else if(AgeyueuEHX == mKKQECMAbz){nGXoRGNcNQ = true;}
      if(ilxzkxjWrX == HnbwatOlMB){HnUenLHNym = true;}
      else if(HnbwatOlMB == ilxzkxjWrX){hfkUYGwMBQ = true;}
      if(ABpTSsCkEF == FAgYjsucww){nCWsTDzKmc = true;}
      if(gnTUfKxSCx == AcnEBDYOOd){qrNchFtRLa = true;}
      if(axWKERJyXu == VkJVlBeXQD){qkmQtOxUXi = true;}
      while(FAgYjsucww == ABpTSsCkEF){XXhNPHwUfm = true;}
      while(AcnEBDYOOd == AcnEBDYOOd){iKfUPyGxmZ = true;}
      while(VkJVlBeXQD == VkJVlBeXQD){NOorBmZXHj = true;}
      if(kPmpEzzGNC == true){kPmpEzzGNC = false;}
      if(iSHKXdAWuW == true){iSHKXdAWuW = false;}
      if(VAWieUqLli == true){VAWieUqLli = false;}
      if(NXLsLjpxAC == true){NXLsLjpxAC = false;}
      if(DSAMuCdzyI == true){DSAMuCdzyI = false;}
      if(AIcshjsEKi == true){AIcshjsEKi = false;}
      if(HnUenLHNym == true){HnUenLHNym = false;}
      if(nCWsTDzKmc == true){nCWsTDzKmc = false;}
      if(qrNchFtRLa == true){qrNchFtRLa = false;}
      if(qkmQtOxUXi == true){qkmQtOxUXi = false;}
      if(uPAKTykjZe == true){uPAKTykjZe = false;}
      if(khQhrPaqxi == true){khQhrPaqxi = false;}
      if(RoCWwDPFzE == true){RoCWwDPFzE = false;}
      if(FdlEgarCIj == true){FdlEgarCIj = false;}
      if(TKrgpITEYd == true){TKrgpITEYd = false;}
      if(nGXoRGNcNQ == true){nGXoRGNcNQ = false;}
      if(hfkUYGwMBQ == true){hfkUYGwMBQ = false;}
      if(XXhNPHwUfm == true){XXhNPHwUfm = false;}
      if(iKfUPyGxmZ == true){iKfUPyGxmZ = false;}
      if(NOorBmZXHj == true){NOorBmZXHj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MZDEEZIKIP
{ 
  void QsUELibTZC()
  { 
      bool TlhLbaVGGs = false;
      bool bntybRZTYo = false;
      bool EwlbSFyKJf = false;
      bool hnOrdKgAYH = false;
      bool jxWCVXFHmm = false;
      bool kYPHyWzGsV = false;
      bool cLxZLmZBUR = false;
      bool jZtQFGZjGt = false;
      bool ApXVtJXGtG = false;
      bool KaHCeYAwpi = false;
      bool yDmVCLdzCq = false;
      bool xOAyUlnaeC = false;
      bool OSGNGJSqlf = false;
      bool GcsXwxDBSi = false;
      bool eYEDJuaIhr = false;
      bool kYQnTewYOs = false;
      bool slMVjTVbBX = false;
      bool ilHwWoODEK = false;
      bool hJJsuhMEDR = false;
      bool AdlZprLiSp = false;
      string KMDWWFZmLx;
      string brBeLWIbMs;
      string LZpgKPcYyM;
      string RZwEeUnypD;
      string oyYWJbAtfW;
      string RcLbMjWVLH;
      string cBozfBuwzp;
      string iKlJEMBTXi;
      string PirauoOUrt;
      string ySlianJZpH;
      string fDtonHpCXz;
      string iDycqsINDq;
      string maEFrPYDhP;
      string DacPDLnDmn;
      string yMxsKtTIqg;
      string fwWzTFzowX;
      string hlTIwIahZe;
      string FEZPracKty;
      string wPMAiGEdux;
      string MzGOFLrowC;
      if(KMDWWFZmLx == fDtonHpCXz){TlhLbaVGGs = true;}
      else if(fDtonHpCXz == KMDWWFZmLx){yDmVCLdzCq = true;}
      if(brBeLWIbMs == iDycqsINDq){bntybRZTYo = true;}
      else if(iDycqsINDq == brBeLWIbMs){xOAyUlnaeC = true;}
      if(LZpgKPcYyM == maEFrPYDhP){EwlbSFyKJf = true;}
      else if(maEFrPYDhP == LZpgKPcYyM){OSGNGJSqlf = true;}
      if(RZwEeUnypD == DacPDLnDmn){hnOrdKgAYH = true;}
      else if(DacPDLnDmn == RZwEeUnypD){GcsXwxDBSi = true;}
      if(oyYWJbAtfW == yMxsKtTIqg){jxWCVXFHmm = true;}
      else if(yMxsKtTIqg == oyYWJbAtfW){eYEDJuaIhr = true;}
      if(RcLbMjWVLH == fwWzTFzowX){kYPHyWzGsV = true;}
      else if(fwWzTFzowX == RcLbMjWVLH){kYQnTewYOs = true;}
      if(cBozfBuwzp == hlTIwIahZe){cLxZLmZBUR = true;}
      else if(hlTIwIahZe == cBozfBuwzp){slMVjTVbBX = true;}
      if(iKlJEMBTXi == FEZPracKty){jZtQFGZjGt = true;}
      if(PirauoOUrt == wPMAiGEdux){ApXVtJXGtG = true;}
      if(ySlianJZpH == MzGOFLrowC){KaHCeYAwpi = true;}
      while(FEZPracKty == iKlJEMBTXi){ilHwWoODEK = true;}
      while(wPMAiGEdux == wPMAiGEdux){hJJsuhMEDR = true;}
      while(MzGOFLrowC == MzGOFLrowC){AdlZprLiSp = true;}
      if(TlhLbaVGGs == true){TlhLbaVGGs = false;}
      if(bntybRZTYo == true){bntybRZTYo = false;}
      if(EwlbSFyKJf == true){EwlbSFyKJf = false;}
      if(hnOrdKgAYH == true){hnOrdKgAYH = false;}
      if(jxWCVXFHmm == true){jxWCVXFHmm = false;}
      if(kYPHyWzGsV == true){kYPHyWzGsV = false;}
      if(cLxZLmZBUR == true){cLxZLmZBUR = false;}
      if(jZtQFGZjGt == true){jZtQFGZjGt = false;}
      if(ApXVtJXGtG == true){ApXVtJXGtG = false;}
      if(KaHCeYAwpi == true){KaHCeYAwpi = false;}
      if(yDmVCLdzCq == true){yDmVCLdzCq = false;}
      if(xOAyUlnaeC == true){xOAyUlnaeC = false;}
      if(OSGNGJSqlf == true){OSGNGJSqlf = false;}
      if(GcsXwxDBSi == true){GcsXwxDBSi = false;}
      if(eYEDJuaIhr == true){eYEDJuaIhr = false;}
      if(kYQnTewYOs == true){kYQnTewYOs = false;}
      if(slMVjTVbBX == true){slMVjTVbBX = false;}
      if(ilHwWoODEK == true){ilHwWoODEK = false;}
      if(hJJsuhMEDR == true){hJJsuhMEDR = false;}
      if(AdlZprLiSp == true){AdlZprLiSp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUSQAQTEQY
{ 
  void MkXOXMRNob()
  { 
      bool mFzhAayFlb = false;
      bool LobsDirnJQ = false;
      bool EOTiBbCuwt = false;
      bool tcOfPYoQcQ = false;
      bool NVPOwdmHWK = false;
      bool wUtwKYlQfY = false;
      bool YDJrghaucd = false;
      bool sbKrChzFlW = false;
      bool ntXlxZiSVq = false;
      bool mYjErKMWgN = false;
      bool DqdrRUJBsb = false;
      bool YgdJjdeWuH = false;
      bool zHZlqTqFAr = false;
      bool UbXXSwPfUc = false;
      bool PhYsRFtaUN = false;
      bool epbYOuRrAx = false;
      bool cDABGxIGpn = false;
      bool NyCRqRigTl = false;
      bool YQklMeAzIX = false;
      bool eXfWAMgWlU = false;
      string ohfkMoKZIS;
      string cSOfqnLDlp;
      string BGjZRfKFGh;
      string dmFskqzzqx;
      string kTdZxpHJDS;
      string OEacriyFSf;
      string dETaopNVuA;
      string nLLnEgbJbb;
      string YBBnTYMcBC;
      string ssgKTgADkH;
      string blODdCrlXK;
      string GodpHcCfHP;
      string ckTrHueBUW;
      string gYXTzllyJQ;
      string fZEqwDPpCq;
      string eUwVdqSWwi;
      string XqRBcgQJpU;
      string pEVpiCfcuD;
      string eoydrMbCpH;
      string TOBasoIDNP;
      if(ohfkMoKZIS == blODdCrlXK){mFzhAayFlb = true;}
      else if(blODdCrlXK == ohfkMoKZIS){DqdrRUJBsb = true;}
      if(cSOfqnLDlp == GodpHcCfHP){LobsDirnJQ = true;}
      else if(GodpHcCfHP == cSOfqnLDlp){YgdJjdeWuH = true;}
      if(BGjZRfKFGh == ckTrHueBUW){EOTiBbCuwt = true;}
      else if(ckTrHueBUW == BGjZRfKFGh){zHZlqTqFAr = true;}
      if(dmFskqzzqx == gYXTzllyJQ){tcOfPYoQcQ = true;}
      else if(gYXTzllyJQ == dmFskqzzqx){UbXXSwPfUc = true;}
      if(kTdZxpHJDS == fZEqwDPpCq){NVPOwdmHWK = true;}
      else if(fZEqwDPpCq == kTdZxpHJDS){PhYsRFtaUN = true;}
      if(OEacriyFSf == eUwVdqSWwi){wUtwKYlQfY = true;}
      else if(eUwVdqSWwi == OEacriyFSf){epbYOuRrAx = true;}
      if(dETaopNVuA == XqRBcgQJpU){YDJrghaucd = true;}
      else if(XqRBcgQJpU == dETaopNVuA){cDABGxIGpn = true;}
      if(nLLnEgbJbb == pEVpiCfcuD){sbKrChzFlW = true;}
      if(YBBnTYMcBC == eoydrMbCpH){ntXlxZiSVq = true;}
      if(ssgKTgADkH == TOBasoIDNP){mYjErKMWgN = true;}
      while(pEVpiCfcuD == nLLnEgbJbb){NyCRqRigTl = true;}
      while(eoydrMbCpH == eoydrMbCpH){YQklMeAzIX = true;}
      while(TOBasoIDNP == TOBasoIDNP){eXfWAMgWlU = true;}
      if(mFzhAayFlb == true){mFzhAayFlb = false;}
      if(LobsDirnJQ == true){LobsDirnJQ = false;}
      if(EOTiBbCuwt == true){EOTiBbCuwt = false;}
      if(tcOfPYoQcQ == true){tcOfPYoQcQ = false;}
      if(NVPOwdmHWK == true){NVPOwdmHWK = false;}
      if(wUtwKYlQfY == true){wUtwKYlQfY = false;}
      if(YDJrghaucd == true){YDJrghaucd = false;}
      if(sbKrChzFlW == true){sbKrChzFlW = false;}
      if(ntXlxZiSVq == true){ntXlxZiSVq = false;}
      if(mYjErKMWgN == true){mYjErKMWgN = false;}
      if(DqdrRUJBsb == true){DqdrRUJBsb = false;}
      if(YgdJjdeWuH == true){YgdJjdeWuH = false;}
      if(zHZlqTqFAr == true){zHZlqTqFAr = false;}
      if(UbXXSwPfUc == true){UbXXSwPfUc = false;}
      if(PhYsRFtaUN == true){PhYsRFtaUN = false;}
      if(epbYOuRrAx == true){epbYOuRrAx = false;}
      if(cDABGxIGpn == true){cDABGxIGpn = false;}
      if(NyCRqRigTl == true){NyCRqRigTl = false;}
      if(YQklMeAzIX == true){YQklMeAzIX = false;}
      if(eXfWAMgWlU == true){eXfWAMgWlU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XVEHFLHAXT
{ 
  void PtrSOOepdO()
  { 
      bool gkEmpiljgC = false;
      bool mjNIomezxz = false;
      bool PrsERTJZJM = false;
      bool ckAaPOUKko = false;
      bool MsHlksZtOm = false;
      bool ADbqenqAVW = false;
      bool YMZUZCilrZ = false;
      bool RTNHmWkGSY = false;
      bool sPLWLYIJwb = false;
      bool WUoOPASmMi = false;
      bool JnBnUfpTEH = false;
      bool CjgxcJACIA = false;
      bool sZpQDweyrl = false;
      bool ExtjOFOXBe = false;
      bool ioFnYlmrlG = false;
      bool zPeLpjxjjX = false;
      bool BrbRDFpxhX = false;
      bool tcBcRDTCrR = false;
      bool JmMkmnShte = false;
      bool HdmddqNmjT = false;
      string jXbbBKtcwK;
      string ZnptQAmzmj;
      string FIlBItHFGQ;
      string okDKEwDzmh;
      string CGVwilkljG;
      string IVFUKalaTH;
      string DnVeUokeoU;
      string xmLFgyloSV;
      string IVVAISehAc;
      string KcefeNjpas;
      string AFwOIUJAnL;
      string owIxygSUWB;
      string KDeLKTHfZS;
      string NwOYUDYGqm;
      string JdsnnOUghy;
      string uPTYixakEn;
      string NdaUxshict;
      string HLcjrfJqWw;
      string zZybXycooX;
      string cnCDZfDYpu;
      if(jXbbBKtcwK == AFwOIUJAnL){gkEmpiljgC = true;}
      else if(AFwOIUJAnL == jXbbBKtcwK){JnBnUfpTEH = true;}
      if(ZnptQAmzmj == owIxygSUWB){mjNIomezxz = true;}
      else if(owIxygSUWB == ZnptQAmzmj){CjgxcJACIA = true;}
      if(FIlBItHFGQ == KDeLKTHfZS){PrsERTJZJM = true;}
      else if(KDeLKTHfZS == FIlBItHFGQ){sZpQDweyrl = true;}
      if(okDKEwDzmh == NwOYUDYGqm){ckAaPOUKko = true;}
      else if(NwOYUDYGqm == okDKEwDzmh){ExtjOFOXBe = true;}
      if(CGVwilkljG == JdsnnOUghy){MsHlksZtOm = true;}
      else if(JdsnnOUghy == CGVwilkljG){ioFnYlmrlG = true;}
      if(IVFUKalaTH == uPTYixakEn){ADbqenqAVW = true;}
      else if(uPTYixakEn == IVFUKalaTH){zPeLpjxjjX = true;}
      if(DnVeUokeoU == NdaUxshict){YMZUZCilrZ = true;}
      else if(NdaUxshict == DnVeUokeoU){BrbRDFpxhX = true;}
      if(xmLFgyloSV == HLcjrfJqWw){RTNHmWkGSY = true;}
      if(IVVAISehAc == zZybXycooX){sPLWLYIJwb = true;}
      if(KcefeNjpas == cnCDZfDYpu){WUoOPASmMi = true;}
      while(HLcjrfJqWw == xmLFgyloSV){tcBcRDTCrR = true;}
      while(zZybXycooX == zZybXycooX){JmMkmnShte = true;}
      while(cnCDZfDYpu == cnCDZfDYpu){HdmddqNmjT = true;}
      if(gkEmpiljgC == true){gkEmpiljgC = false;}
      if(mjNIomezxz == true){mjNIomezxz = false;}
      if(PrsERTJZJM == true){PrsERTJZJM = false;}
      if(ckAaPOUKko == true){ckAaPOUKko = false;}
      if(MsHlksZtOm == true){MsHlksZtOm = false;}
      if(ADbqenqAVW == true){ADbqenqAVW = false;}
      if(YMZUZCilrZ == true){YMZUZCilrZ = false;}
      if(RTNHmWkGSY == true){RTNHmWkGSY = false;}
      if(sPLWLYIJwb == true){sPLWLYIJwb = false;}
      if(WUoOPASmMi == true){WUoOPASmMi = false;}
      if(JnBnUfpTEH == true){JnBnUfpTEH = false;}
      if(CjgxcJACIA == true){CjgxcJACIA = false;}
      if(sZpQDweyrl == true){sZpQDweyrl = false;}
      if(ExtjOFOXBe == true){ExtjOFOXBe = false;}
      if(ioFnYlmrlG == true){ioFnYlmrlG = false;}
      if(zPeLpjxjjX == true){zPeLpjxjjX = false;}
      if(BrbRDFpxhX == true){BrbRDFpxhX = false;}
      if(tcBcRDTCrR == true){tcBcRDTCrR = false;}
      if(JmMkmnShte == true){JmMkmnShte = false;}
      if(HdmddqNmjT == true){HdmddqNmjT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ECNFBQALLQ
{ 
  void iuXLMYxxLO()
  { 
      bool UXkFKTZcOs = false;
      bool rIgMhctEfz = false;
      bool iwTSJsigJV = false;
      bool DHseMERihd = false;
      bool ymAIMQBfoF = false;
      bool smAEJXDRuR = false;
      bool jsSrojPCAd = false;
      bool KKVBBwwLFs = false;
      bool qCqDcQHnVo = false;
      bool AAmQtEUISb = false;
      bool AyfLuhQyCM = false;
      bool brLCZgBOPY = false;
      bool cafKdKWFHw = false;
      bool bmrcrsWfIt = false;
      bool AJkINHnkqN = false;
      bool CFrtzYSVgj = false;
      bool KLqFknziJg = false;
      bool KVFUXSpXxV = false;
      bool WlNssVuydT = false;
      bool ZByYjoRfXZ = false;
      string MOXHuqIVxB;
      string dueTYLcNEd;
      string oLTteUTyUg;
      string haNBccjweY;
      string WTuYcMJLDG;
      string YwIexAudcZ;
      string WKBQSDgdqu;
      string bfifGVPtQR;
      string LItNHkRiDb;
      string gGTEBMSeGZ;
      string efUHerNcXb;
      string jAMKOOPmIg;
      string kyZPNUMdet;
      string DknqlfmmhP;
      string WoKbqgsJol;
      string weVYogFFsK;
      string fixdXyMVXi;
      string acEsJunxXg;
      string bCosxXPPBF;
      string ZhsXinqfEr;
      if(MOXHuqIVxB == efUHerNcXb){UXkFKTZcOs = true;}
      else if(efUHerNcXb == MOXHuqIVxB){AyfLuhQyCM = true;}
      if(dueTYLcNEd == jAMKOOPmIg){rIgMhctEfz = true;}
      else if(jAMKOOPmIg == dueTYLcNEd){brLCZgBOPY = true;}
      if(oLTteUTyUg == kyZPNUMdet){iwTSJsigJV = true;}
      else if(kyZPNUMdet == oLTteUTyUg){cafKdKWFHw = true;}
      if(haNBccjweY == DknqlfmmhP){DHseMERihd = true;}
      else if(DknqlfmmhP == haNBccjweY){bmrcrsWfIt = true;}
      if(WTuYcMJLDG == WoKbqgsJol){ymAIMQBfoF = true;}
      else if(WoKbqgsJol == WTuYcMJLDG){AJkINHnkqN = true;}
      if(YwIexAudcZ == weVYogFFsK){smAEJXDRuR = true;}
      else if(weVYogFFsK == YwIexAudcZ){CFrtzYSVgj = true;}
      if(WKBQSDgdqu == fixdXyMVXi){jsSrojPCAd = true;}
      else if(fixdXyMVXi == WKBQSDgdqu){KLqFknziJg = true;}
      if(bfifGVPtQR == acEsJunxXg){KKVBBwwLFs = true;}
      if(LItNHkRiDb == bCosxXPPBF){qCqDcQHnVo = true;}
      if(gGTEBMSeGZ == ZhsXinqfEr){AAmQtEUISb = true;}
      while(acEsJunxXg == bfifGVPtQR){KVFUXSpXxV = true;}
      while(bCosxXPPBF == bCosxXPPBF){WlNssVuydT = true;}
      while(ZhsXinqfEr == ZhsXinqfEr){ZByYjoRfXZ = true;}
      if(UXkFKTZcOs == true){UXkFKTZcOs = false;}
      if(rIgMhctEfz == true){rIgMhctEfz = false;}
      if(iwTSJsigJV == true){iwTSJsigJV = false;}
      if(DHseMERihd == true){DHseMERihd = false;}
      if(ymAIMQBfoF == true){ymAIMQBfoF = false;}
      if(smAEJXDRuR == true){smAEJXDRuR = false;}
      if(jsSrojPCAd == true){jsSrojPCAd = false;}
      if(KKVBBwwLFs == true){KKVBBwwLFs = false;}
      if(qCqDcQHnVo == true){qCqDcQHnVo = false;}
      if(AAmQtEUISb == true){AAmQtEUISb = false;}
      if(AyfLuhQyCM == true){AyfLuhQyCM = false;}
      if(brLCZgBOPY == true){brLCZgBOPY = false;}
      if(cafKdKWFHw == true){cafKdKWFHw = false;}
      if(bmrcrsWfIt == true){bmrcrsWfIt = false;}
      if(AJkINHnkqN == true){AJkINHnkqN = false;}
      if(CFrtzYSVgj == true){CFrtzYSVgj = false;}
      if(KLqFknziJg == true){KLqFknziJg = false;}
      if(KVFUXSpXxV == true){KVFUXSpXxV = false;}
      if(WlNssVuydT == true){WlNssVuydT = false;}
      if(ZByYjoRfXZ == true){ZByYjoRfXZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBKOHMLHIP
{ 
  void DACZGMnQMp()
  { 
      bool lxCMnWJsBd = false;
      bool UhQyHPZknL = false;
      bool YMNfnbKRnU = false;
      bool ziIkOFbXpL = false;
      bool AGonxSWsas = false;
      bool XtxTBZiVYL = false;
      bool MqEgekZejB = false;
      bool nCubKSWYiU = false;
      bool EQptwFloin = false;
      bool VFzdyIBIJL = false;
      bool sqJYEVzUIi = false;
      bool DJmDHuAJjY = false;
      bool zkuufhCQcB = false;
      bool RNOXbNHRpa = false;
      bool FRfAkMSwWC = false;
      bool HqXkLIuNsV = false;
      bool ShqGQotOas = false;
      bool niTJSgEuKS = false;
      bool PGtasaodLT = false;
      bool RtYTHXZZiu = false;
      string BOgpKNCVPx;
      string YQalYdXLrf;
      string uEqMJRXWul;
      string LHzxLcJmHZ;
      string AbVhAilQmL;
      string JCPLIxXUfr;
      string oeadkRQcaw;
      string UkDSeThILZ;
      string fHiibIqnoO;
      string FnGPkVArwi;
      string SJpqqYzxfn;
      string OOJGMguqBb;
      string ZcnMqgdnhJ;
      string SpLbHWRrrD;
      string JtHAzpdACD;
      string ZIqUJoUdzJ;
      string tLOWVYDgyp;
      string PCzxSeUmMB;
      string CdkdiJzqSR;
      string BnrhJyekea;
      if(BOgpKNCVPx == SJpqqYzxfn){lxCMnWJsBd = true;}
      else if(SJpqqYzxfn == BOgpKNCVPx){sqJYEVzUIi = true;}
      if(YQalYdXLrf == OOJGMguqBb){UhQyHPZknL = true;}
      else if(OOJGMguqBb == YQalYdXLrf){DJmDHuAJjY = true;}
      if(uEqMJRXWul == ZcnMqgdnhJ){YMNfnbKRnU = true;}
      else if(ZcnMqgdnhJ == uEqMJRXWul){zkuufhCQcB = true;}
      if(LHzxLcJmHZ == SpLbHWRrrD){ziIkOFbXpL = true;}
      else if(SpLbHWRrrD == LHzxLcJmHZ){RNOXbNHRpa = true;}
      if(AbVhAilQmL == JtHAzpdACD){AGonxSWsas = true;}
      else if(JtHAzpdACD == AbVhAilQmL){FRfAkMSwWC = true;}
      if(JCPLIxXUfr == ZIqUJoUdzJ){XtxTBZiVYL = true;}
      else if(ZIqUJoUdzJ == JCPLIxXUfr){HqXkLIuNsV = true;}
      if(oeadkRQcaw == tLOWVYDgyp){MqEgekZejB = true;}
      else if(tLOWVYDgyp == oeadkRQcaw){ShqGQotOas = true;}
      if(UkDSeThILZ == PCzxSeUmMB){nCubKSWYiU = true;}
      if(fHiibIqnoO == CdkdiJzqSR){EQptwFloin = true;}
      if(FnGPkVArwi == BnrhJyekea){VFzdyIBIJL = true;}
      while(PCzxSeUmMB == UkDSeThILZ){niTJSgEuKS = true;}
      while(CdkdiJzqSR == CdkdiJzqSR){PGtasaodLT = true;}
      while(BnrhJyekea == BnrhJyekea){RtYTHXZZiu = true;}
      if(lxCMnWJsBd == true){lxCMnWJsBd = false;}
      if(UhQyHPZknL == true){UhQyHPZknL = false;}
      if(YMNfnbKRnU == true){YMNfnbKRnU = false;}
      if(ziIkOFbXpL == true){ziIkOFbXpL = false;}
      if(AGonxSWsas == true){AGonxSWsas = false;}
      if(XtxTBZiVYL == true){XtxTBZiVYL = false;}
      if(MqEgekZejB == true){MqEgekZejB = false;}
      if(nCubKSWYiU == true){nCubKSWYiU = false;}
      if(EQptwFloin == true){EQptwFloin = false;}
      if(VFzdyIBIJL == true){VFzdyIBIJL = false;}
      if(sqJYEVzUIi == true){sqJYEVzUIi = false;}
      if(DJmDHuAJjY == true){DJmDHuAJjY = false;}
      if(zkuufhCQcB == true){zkuufhCQcB = false;}
      if(RNOXbNHRpa == true){RNOXbNHRpa = false;}
      if(FRfAkMSwWC == true){FRfAkMSwWC = false;}
      if(HqXkLIuNsV == true){HqXkLIuNsV = false;}
      if(ShqGQotOas == true){ShqGQotOas = false;}
      if(niTJSgEuKS == true){niTJSgEuKS = false;}
      if(PGtasaodLT == true){PGtasaodLT = false;}
      if(RtYTHXZZiu == true){RtYTHXZZiu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEQANEVFRM
{ 
  void PNGktPCgJj()
  { 
      bool FeXMdBZEFB = false;
      bool AaVIWgUgnp = false;
      bool pLYztgUVmJ = false;
      bool EKCtFmLahs = false;
      bool jwCTRAPWqj = false;
      bool sbMHmtFYRx = false;
      bool fDQwwoYaDj = false;
      bool UtztGsIFht = false;
      bool QyeCPbyuHK = false;
      bool hmJjMfeGXb = false;
      bool bnTGOzcRAt = false;
      bool lAqXfhXOfU = false;
      bool qcTrBhjOhZ = false;
      bool NBhFSbeXmP = false;
      bool zftNXhukEd = false;
      bool IQZCkyUaFg = false;
      bool ONjafkSlFD = false;
      bool DzaPULiGTT = false;
      bool lzKDRwaeTT = false;
      bool HDSGBluSgm = false;
      string YGVwhdknpU;
      string mQhnOBguQN;
      string pRnWMcOcPc;
      string SOBLbxDVOK;
      string LWKbFYxxWe;
      string CNIipHRyjF;
      string OHXNBXOVMQ;
      string xLgFBTGMRn;
      string eQGjZFGRVU;
      string eFkJuDywZg;
      string JbkFgqgDgW;
      string AFfuZyBmmw;
      string RxzqkrZXJx;
      string UJlkdDeADi;
      string XDkzTZZpix;
      string CKIdPMbsUo;
      string QJsiBpTuRW;
      string SAjEXNMAXL;
      string RjnLuKAIVR;
      string blfNROJBxc;
      if(YGVwhdknpU == JbkFgqgDgW){FeXMdBZEFB = true;}
      else if(JbkFgqgDgW == YGVwhdknpU){bnTGOzcRAt = true;}
      if(mQhnOBguQN == AFfuZyBmmw){AaVIWgUgnp = true;}
      else if(AFfuZyBmmw == mQhnOBguQN){lAqXfhXOfU = true;}
      if(pRnWMcOcPc == RxzqkrZXJx){pLYztgUVmJ = true;}
      else if(RxzqkrZXJx == pRnWMcOcPc){qcTrBhjOhZ = true;}
      if(SOBLbxDVOK == UJlkdDeADi){EKCtFmLahs = true;}
      else if(UJlkdDeADi == SOBLbxDVOK){NBhFSbeXmP = true;}
      if(LWKbFYxxWe == XDkzTZZpix){jwCTRAPWqj = true;}
      else if(XDkzTZZpix == LWKbFYxxWe){zftNXhukEd = true;}
      if(CNIipHRyjF == CKIdPMbsUo){sbMHmtFYRx = true;}
      else if(CKIdPMbsUo == CNIipHRyjF){IQZCkyUaFg = true;}
      if(OHXNBXOVMQ == QJsiBpTuRW){fDQwwoYaDj = true;}
      else if(QJsiBpTuRW == OHXNBXOVMQ){ONjafkSlFD = true;}
      if(xLgFBTGMRn == SAjEXNMAXL){UtztGsIFht = true;}
      if(eQGjZFGRVU == RjnLuKAIVR){QyeCPbyuHK = true;}
      if(eFkJuDywZg == blfNROJBxc){hmJjMfeGXb = true;}
      while(SAjEXNMAXL == xLgFBTGMRn){DzaPULiGTT = true;}
      while(RjnLuKAIVR == RjnLuKAIVR){lzKDRwaeTT = true;}
      while(blfNROJBxc == blfNROJBxc){HDSGBluSgm = true;}
      if(FeXMdBZEFB == true){FeXMdBZEFB = false;}
      if(AaVIWgUgnp == true){AaVIWgUgnp = false;}
      if(pLYztgUVmJ == true){pLYztgUVmJ = false;}
      if(EKCtFmLahs == true){EKCtFmLahs = false;}
      if(jwCTRAPWqj == true){jwCTRAPWqj = false;}
      if(sbMHmtFYRx == true){sbMHmtFYRx = false;}
      if(fDQwwoYaDj == true){fDQwwoYaDj = false;}
      if(UtztGsIFht == true){UtztGsIFht = false;}
      if(QyeCPbyuHK == true){QyeCPbyuHK = false;}
      if(hmJjMfeGXb == true){hmJjMfeGXb = false;}
      if(bnTGOzcRAt == true){bnTGOzcRAt = false;}
      if(lAqXfhXOfU == true){lAqXfhXOfU = false;}
      if(qcTrBhjOhZ == true){qcTrBhjOhZ = false;}
      if(NBhFSbeXmP == true){NBhFSbeXmP = false;}
      if(zftNXhukEd == true){zftNXhukEd = false;}
      if(IQZCkyUaFg == true){IQZCkyUaFg = false;}
      if(ONjafkSlFD == true){ONjafkSlFD = false;}
      if(DzaPULiGTT == true){DzaPULiGTT = false;}
      if(lzKDRwaeTT == true){lzKDRwaeTT = false;}
      if(HDSGBluSgm == true){HDSGBluSgm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QBPKFKFNEE
{ 
  void WRXIXuyCfu()
  { 
      bool TkNUDFxAIV = false;
      bool fhFVSLrsGt = false;
      bool qrzgIcEQDa = false;
      bool aaYpEZsIut = false;
      bool ZamtMTYPzA = false;
      bool gGTczbkfLa = false;
      bool BgxgtFJPRr = false;
      bool SiyLUPEFUn = false;
      bool DoQCsTGwpb = false;
      bool nMwTsrdFzG = false;
      bool KIyHhxIHHi = false;
      bool WfLXWMQtma = false;
      bool yNYoDFmdSb = false;
      bool lyFNdtqIUu = false;
      bool KznGEIBYxg = false;
      bool bjSYIwjIEb = false;
      bool JenfxYaxsb = false;
      bool UHYqPzZRju = false;
      bool EOflzCffFg = false;
      bool KhErkeKHIf = false;
      string IdXQMmmogF;
      string JQyjccUClF;
      string tyePXSZLVs;
      string lqzybylhSu;
      string rexWjhShFh;
      string AMtPlKzIrt;
      string NaSmTRRzHe;
      string qliqMPAHep;
      string AqFmsYwjMR;
      string ydpYgQLJDS;
      string PSaZqOdCCV;
      string JqcBsWUetu;
      string VhmofMuJJu;
      string DqDMahPfwe;
      string tsgpIHBnfK;
      string ufPIxgeltd;
      string SUsGSRmPaL;
      string GoiPAbBwfY;
      string LGczAXauPs;
      string CdkRLYAZXp;
      if(IdXQMmmogF == PSaZqOdCCV){TkNUDFxAIV = true;}
      else if(PSaZqOdCCV == IdXQMmmogF){KIyHhxIHHi = true;}
      if(JQyjccUClF == JqcBsWUetu){fhFVSLrsGt = true;}
      else if(JqcBsWUetu == JQyjccUClF){WfLXWMQtma = true;}
      if(tyePXSZLVs == VhmofMuJJu){qrzgIcEQDa = true;}
      else if(VhmofMuJJu == tyePXSZLVs){yNYoDFmdSb = true;}
      if(lqzybylhSu == DqDMahPfwe){aaYpEZsIut = true;}
      else if(DqDMahPfwe == lqzybylhSu){lyFNdtqIUu = true;}
      if(rexWjhShFh == tsgpIHBnfK){ZamtMTYPzA = true;}
      else if(tsgpIHBnfK == rexWjhShFh){KznGEIBYxg = true;}
      if(AMtPlKzIrt == ufPIxgeltd){gGTczbkfLa = true;}
      else if(ufPIxgeltd == AMtPlKzIrt){bjSYIwjIEb = true;}
      if(NaSmTRRzHe == SUsGSRmPaL){BgxgtFJPRr = true;}
      else if(SUsGSRmPaL == NaSmTRRzHe){JenfxYaxsb = true;}
      if(qliqMPAHep == GoiPAbBwfY){SiyLUPEFUn = true;}
      if(AqFmsYwjMR == LGczAXauPs){DoQCsTGwpb = true;}
      if(ydpYgQLJDS == CdkRLYAZXp){nMwTsrdFzG = true;}
      while(GoiPAbBwfY == qliqMPAHep){UHYqPzZRju = true;}
      while(LGczAXauPs == LGczAXauPs){EOflzCffFg = true;}
      while(CdkRLYAZXp == CdkRLYAZXp){KhErkeKHIf = true;}
      if(TkNUDFxAIV == true){TkNUDFxAIV = false;}
      if(fhFVSLrsGt == true){fhFVSLrsGt = false;}
      if(qrzgIcEQDa == true){qrzgIcEQDa = false;}
      if(aaYpEZsIut == true){aaYpEZsIut = false;}
      if(ZamtMTYPzA == true){ZamtMTYPzA = false;}
      if(gGTczbkfLa == true){gGTczbkfLa = false;}
      if(BgxgtFJPRr == true){BgxgtFJPRr = false;}
      if(SiyLUPEFUn == true){SiyLUPEFUn = false;}
      if(DoQCsTGwpb == true){DoQCsTGwpb = false;}
      if(nMwTsrdFzG == true){nMwTsrdFzG = false;}
      if(KIyHhxIHHi == true){KIyHhxIHHi = false;}
      if(WfLXWMQtma == true){WfLXWMQtma = false;}
      if(yNYoDFmdSb == true){yNYoDFmdSb = false;}
      if(lyFNdtqIUu == true){lyFNdtqIUu = false;}
      if(KznGEIBYxg == true){KznGEIBYxg = false;}
      if(bjSYIwjIEb == true){bjSYIwjIEb = false;}
      if(JenfxYaxsb == true){JenfxYaxsb = false;}
      if(UHYqPzZRju == true){UHYqPzZRju = false;}
      if(EOflzCffFg == true){EOflzCffFg = false;}
      if(KhErkeKHIf == true){KhErkeKHIf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RMULEHIUOS
{ 
  void iNHpGKZPKz()
  { 
      bool VoSOZkrRjz = false;
      bool CBNxLSwDhH = false;
      bool nBUGorOnmL = false;
      bool kUlAFteYoh = false;
      bool bBQGfXoKVA = false;
      bool pcCVfTULZh = false;
      bool WEdYNgPNrQ = false;
      bool mXOAfljNaQ = false;
      bool CDSmVISPTk = false;
      bool ZTyGKWXrry = false;
      bool IbSEMSOCpt = false;
      bool jGkIfSkpCE = false;
      bool OztGpTYHoI = false;
      bool OrVbIakNaD = false;
      bool tPZZBShpaq = false;
      bool lhomjIgLNs = false;
      bool sGNhfqkJAE = false;
      bool hWPzKyZTEW = false;
      bool lifxWfChrz = false;
      bool sYzgJmCrtJ = false;
      string VRHDbfzAMQ;
      string KaEHBZqKuG;
      string bQnFlxcpeQ;
      string WrYTgoNBMH;
      string UgKyAzVHjG;
      string KzqMEFcBQe;
      string DIVusSBjZL;
      string LoynltFoFm;
      string aUFXFXBLPb;
      string LLkgDLLOEh;
      string xkgYuVBCaK;
      string zmwdDhDxpV;
      string QpUyzzEQja;
      string hqkWoomgcj;
      string WykFcXPGcU;
      string HNXiQHQiYu;
      string QjSAbHCZnN;
      string uWUGyRFPUa;
      string jxmOSUTBFh;
      string YDIgSlfjcU;
      if(VRHDbfzAMQ == xkgYuVBCaK){VoSOZkrRjz = true;}
      else if(xkgYuVBCaK == VRHDbfzAMQ){IbSEMSOCpt = true;}
      if(KaEHBZqKuG == zmwdDhDxpV){CBNxLSwDhH = true;}
      else if(zmwdDhDxpV == KaEHBZqKuG){jGkIfSkpCE = true;}
      if(bQnFlxcpeQ == QpUyzzEQja){nBUGorOnmL = true;}
      else if(QpUyzzEQja == bQnFlxcpeQ){OztGpTYHoI = true;}
      if(WrYTgoNBMH == hqkWoomgcj){kUlAFteYoh = true;}
      else if(hqkWoomgcj == WrYTgoNBMH){OrVbIakNaD = true;}
      if(UgKyAzVHjG == WykFcXPGcU){bBQGfXoKVA = true;}
      else if(WykFcXPGcU == UgKyAzVHjG){tPZZBShpaq = true;}
      if(KzqMEFcBQe == HNXiQHQiYu){pcCVfTULZh = true;}
      else if(HNXiQHQiYu == KzqMEFcBQe){lhomjIgLNs = true;}
      if(DIVusSBjZL == QjSAbHCZnN){WEdYNgPNrQ = true;}
      else if(QjSAbHCZnN == DIVusSBjZL){sGNhfqkJAE = true;}
      if(LoynltFoFm == uWUGyRFPUa){mXOAfljNaQ = true;}
      if(aUFXFXBLPb == jxmOSUTBFh){CDSmVISPTk = true;}
      if(LLkgDLLOEh == YDIgSlfjcU){ZTyGKWXrry = true;}
      while(uWUGyRFPUa == LoynltFoFm){hWPzKyZTEW = true;}
      while(jxmOSUTBFh == jxmOSUTBFh){lifxWfChrz = true;}
      while(YDIgSlfjcU == YDIgSlfjcU){sYzgJmCrtJ = true;}
      if(VoSOZkrRjz == true){VoSOZkrRjz = false;}
      if(CBNxLSwDhH == true){CBNxLSwDhH = false;}
      if(nBUGorOnmL == true){nBUGorOnmL = false;}
      if(kUlAFteYoh == true){kUlAFteYoh = false;}
      if(bBQGfXoKVA == true){bBQGfXoKVA = false;}
      if(pcCVfTULZh == true){pcCVfTULZh = false;}
      if(WEdYNgPNrQ == true){WEdYNgPNrQ = false;}
      if(mXOAfljNaQ == true){mXOAfljNaQ = false;}
      if(CDSmVISPTk == true){CDSmVISPTk = false;}
      if(ZTyGKWXrry == true){ZTyGKWXrry = false;}
      if(IbSEMSOCpt == true){IbSEMSOCpt = false;}
      if(jGkIfSkpCE == true){jGkIfSkpCE = false;}
      if(OztGpTYHoI == true){OztGpTYHoI = false;}
      if(OrVbIakNaD == true){OrVbIakNaD = false;}
      if(tPZZBShpaq == true){tPZZBShpaq = false;}
      if(lhomjIgLNs == true){lhomjIgLNs = false;}
      if(sGNhfqkJAE == true){sGNhfqkJAE = false;}
      if(hWPzKyZTEW == true){hWPzKyZTEW = false;}
      if(lifxWfChrz == true){lifxWfChrz = false;}
      if(sYzgJmCrtJ == true){sYzgJmCrtJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DEJWVYCIIQ
{ 
  void drymWsyfEF()
  { 
      bool UqLVaQSuea = false;
      bool gYLTooqVsL = false;
      bool GcWpNTLQHG = false;
      bool ujVdqlrdSh = false;
      bool ROmFjHzjpR = false;
      bool UKGUxqTVHG = false;
      bool FCmYewCgbC = false;
      bool xMDLsqpRGG = false;
      bool UbZpkkcBgz = false;
      bool SVVLcPbOam = false;
      bool FRHnTIGuaF = false;
      bool BBPBkcbwms = false;
      bool TAAcibqqhd = false;
      bool PaqSADUkWc = false;
      bool egaaxQGTZz = false;
      bool meagTERdFr = false;
      bool QONwpZKxAh = false;
      bool IpZJOlZYeR = false;
      bool UWQhqjzKzw = false;
      bool kpfdMPTdkW = false;
      string mjQrcfuZAf;
      string qsepeoKKKc;
      string GGmRWQyFoQ;
      string yKxdkZhdcW;
      string TuKBHrFANz;
      string xnBfGgxyUM;
      string hpkigguAFF;
      string HfgnIKwkKe;
      string LyqoSKJRWE;
      string ciIQodKaUa;
      string wEtIqRGNXu;
      string jLnoBiyuQW;
      string WddBcYXPye;
      string AUQjiGEiyB;
      string DusbTQuSPF;
      string fPKyDRasfS;
      string tqOsuPuEGt;
      string eOwPSbkChL;
      string cEzszjJRgQ;
      string fKDfHMfAfD;
      if(mjQrcfuZAf == wEtIqRGNXu){UqLVaQSuea = true;}
      else if(wEtIqRGNXu == mjQrcfuZAf){FRHnTIGuaF = true;}
      if(qsepeoKKKc == jLnoBiyuQW){gYLTooqVsL = true;}
      else if(jLnoBiyuQW == qsepeoKKKc){BBPBkcbwms = true;}
      if(GGmRWQyFoQ == WddBcYXPye){GcWpNTLQHG = true;}
      else if(WddBcYXPye == GGmRWQyFoQ){TAAcibqqhd = true;}
      if(yKxdkZhdcW == AUQjiGEiyB){ujVdqlrdSh = true;}
      else if(AUQjiGEiyB == yKxdkZhdcW){PaqSADUkWc = true;}
      if(TuKBHrFANz == DusbTQuSPF){ROmFjHzjpR = true;}
      else if(DusbTQuSPF == TuKBHrFANz){egaaxQGTZz = true;}
      if(xnBfGgxyUM == fPKyDRasfS){UKGUxqTVHG = true;}
      else if(fPKyDRasfS == xnBfGgxyUM){meagTERdFr = true;}
      if(hpkigguAFF == tqOsuPuEGt){FCmYewCgbC = true;}
      else if(tqOsuPuEGt == hpkigguAFF){QONwpZKxAh = true;}
      if(HfgnIKwkKe == eOwPSbkChL){xMDLsqpRGG = true;}
      if(LyqoSKJRWE == cEzszjJRgQ){UbZpkkcBgz = true;}
      if(ciIQodKaUa == fKDfHMfAfD){SVVLcPbOam = true;}
      while(eOwPSbkChL == HfgnIKwkKe){IpZJOlZYeR = true;}
      while(cEzszjJRgQ == cEzszjJRgQ){UWQhqjzKzw = true;}
      while(fKDfHMfAfD == fKDfHMfAfD){kpfdMPTdkW = true;}
      if(UqLVaQSuea == true){UqLVaQSuea = false;}
      if(gYLTooqVsL == true){gYLTooqVsL = false;}
      if(GcWpNTLQHG == true){GcWpNTLQHG = false;}
      if(ujVdqlrdSh == true){ujVdqlrdSh = false;}
      if(ROmFjHzjpR == true){ROmFjHzjpR = false;}
      if(UKGUxqTVHG == true){UKGUxqTVHG = false;}
      if(FCmYewCgbC == true){FCmYewCgbC = false;}
      if(xMDLsqpRGG == true){xMDLsqpRGG = false;}
      if(UbZpkkcBgz == true){UbZpkkcBgz = false;}
      if(SVVLcPbOam == true){SVVLcPbOam = false;}
      if(FRHnTIGuaF == true){FRHnTIGuaF = false;}
      if(BBPBkcbwms == true){BBPBkcbwms = false;}
      if(TAAcibqqhd == true){TAAcibqqhd = false;}
      if(PaqSADUkWc == true){PaqSADUkWc = false;}
      if(egaaxQGTZz == true){egaaxQGTZz = false;}
      if(meagTERdFr == true){meagTERdFr = false;}
      if(QONwpZKxAh == true){QONwpZKxAh = false;}
      if(IpZJOlZYeR == true){IpZJOlZYeR = false;}
      if(UWQhqjzKzw == true){UWQhqjzKzw = false;}
      if(kpfdMPTdkW == true){kpfdMPTdkW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GFMMXGLZUA
{ 
  void yLPBrkNuXE()
  { 
      bool fMaqcqicgk = false;
      bool aBtghWmXXo = false;
      bool PucphPbINm = false;
      bool FxAkekLQxu = false;
      bool SYwwzDXVmn = false;
      bool NBuTwkijJM = false;
      bool PZPsfdBIBw = false;
      bool KWZbWqzgqd = false;
      bool rFUZZDBgot = false;
      bool BaGkfrICQV = false;
      bool COUqcqaSwE = false;
      bool lCseUKEpTb = false;
      bool bTTGtiQowe = false;
      bool iwQVbdjdwh = false;
      bool bhjjIzhaPU = false;
      bool mRinshtNws = false;
      bool alWQVolXDp = false;
      bool ZatkAsjiyu = false;
      bool BoYarQMbbt = false;
      bool iVhDHpLTOS = false;
      string LHJbVkbwDz;
      string eanssKRwBf;
      string krelodTzMC;
      string iYdVSDFMaQ;
      string YcuXXjorxH;
      string sDScOScXmr;
      string QcjBQGxSap;
      string EEVjGHxGOE;
      string naCEIeFBHz;
      string ahZiAwstHQ;
      string mWRHDnhhVG;
      string VWJhDpZerk;
      string BwKaOWemjJ;
      string ODyxRQIuBT;
      string wWeAdDYreJ;
      string WNBVPqLqrf;
      string JuyLqRXLQm;
      string gedXodQJxL;
      string ymHZmBCchZ;
      string FRDUKBYTJL;
      if(LHJbVkbwDz == mWRHDnhhVG){fMaqcqicgk = true;}
      else if(mWRHDnhhVG == LHJbVkbwDz){COUqcqaSwE = true;}
      if(eanssKRwBf == VWJhDpZerk){aBtghWmXXo = true;}
      else if(VWJhDpZerk == eanssKRwBf){lCseUKEpTb = true;}
      if(krelodTzMC == BwKaOWemjJ){PucphPbINm = true;}
      else if(BwKaOWemjJ == krelodTzMC){bTTGtiQowe = true;}
      if(iYdVSDFMaQ == ODyxRQIuBT){FxAkekLQxu = true;}
      else if(ODyxRQIuBT == iYdVSDFMaQ){iwQVbdjdwh = true;}
      if(YcuXXjorxH == wWeAdDYreJ){SYwwzDXVmn = true;}
      else if(wWeAdDYreJ == YcuXXjorxH){bhjjIzhaPU = true;}
      if(sDScOScXmr == WNBVPqLqrf){NBuTwkijJM = true;}
      else if(WNBVPqLqrf == sDScOScXmr){mRinshtNws = true;}
      if(QcjBQGxSap == JuyLqRXLQm){PZPsfdBIBw = true;}
      else if(JuyLqRXLQm == QcjBQGxSap){alWQVolXDp = true;}
      if(EEVjGHxGOE == gedXodQJxL){KWZbWqzgqd = true;}
      if(naCEIeFBHz == ymHZmBCchZ){rFUZZDBgot = true;}
      if(ahZiAwstHQ == FRDUKBYTJL){BaGkfrICQV = true;}
      while(gedXodQJxL == EEVjGHxGOE){ZatkAsjiyu = true;}
      while(ymHZmBCchZ == ymHZmBCchZ){BoYarQMbbt = true;}
      while(FRDUKBYTJL == FRDUKBYTJL){iVhDHpLTOS = true;}
      if(fMaqcqicgk == true){fMaqcqicgk = false;}
      if(aBtghWmXXo == true){aBtghWmXXo = false;}
      if(PucphPbINm == true){PucphPbINm = false;}
      if(FxAkekLQxu == true){FxAkekLQxu = false;}
      if(SYwwzDXVmn == true){SYwwzDXVmn = false;}
      if(NBuTwkijJM == true){NBuTwkijJM = false;}
      if(PZPsfdBIBw == true){PZPsfdBIBw = false;}
      if(KWZbWqzgqd == true){KWZbWqzgqd = false;}
      if(rFUZZDBgot == true){rFUZZDBgot = false;}
      if(BaGkfrICQV == true){BaGkfrICQV = false;}
      if(COUqcqaSwE == true){COUqcqaSwE = false;}
      if(lCseUKEpTb == true){lCseUKEpTb = false;}
      if(bTTGtiQowe == true){bTTGtiQowe = false;}
      if(iwQVbdjdwh == true){iwQVbdjdwh = false;}
      if(bhjjIzhaPU == true){bhjjIzhaPU = false;}
      if(mRinshtNws == true){mRinshtNws = false;}
      if(alWQVolXDp == true){alWQVolXDp = false;}
      if(ZatkAsjiyu == true){ZatkAsjiyu = false;}
      if(BoYarQMbbt == true){BoYarQMbbt = false;}
      if(iVhDHpLTOS == true){iVhDHpLTOS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GJZLLBVKTJ
{ 
  void kAmOwyPgUT()
  { 
      bool GdoPejTSZg = false;
      bool JTgEtSwNNm = false;
      bool PdMTqAbylc = false;
      bool lrPSPyYOzi = false;
      bool kjjFQfmbPn = false;
      bool jNAUhcQVXe = false;
      bool IVfwuREOnw = false;
      bool thNeCfsHCK = false;
      bool MzhxsXqtjm = false;
      bool gCpUaOEmJz = false;
      bool bYmTtCzVSB = false;
      bool iJTMRImhDW = false;
      bool ZJdBOqqsDm = false;
      bool bGyCimMOCp = false;
      bool YUbiDXidCS = false;
      bool bVilYRukED = false;
      bool LGSfZcKQde = false;
      bool wYeNyFguyp = false;
      bool HNpkKFXLcQ = false;
      bool qaJzdSCwIZ = false;
      string EPoRMzJHaq;
      string trDXFOlLrt;
      string aMiBVULqEV;
      string GaAEqJyRia;
      string ZXBlsKNMos;
      string AnmMdrfnwq;
      string mRCEjTqyfu;
      string PUbRTDKxHK;
      string HzBLVSnnay;
      string dKVqmIUwCZ;
      string SPfscfLVra;
      string gigljnPqiR;
      string fCXhRFykdL;
      string hOtgqrSIho;
      string HSwAQucjHz;
      string rcMjtQqybW;
      string gZqgrSnztr;
      string UHJtKMGXQW;
      string bOddSECKla;
      string AUfKHgaOHy;
      if(EPoRMzJHaq == SPfscfLVra){GdoPejTSZg = true;}
      else if(SPfscfLVra == EPoRMzJHaq){bYmTtCzVSB = true;}
      if(trDXFOlLrt == gigljnPqiR){JTgEtSwNNm = true;}
      else if(gigljnPqiR == trDXFOlLrt){iJTMRImhDW = true;}
      if(aMiBVULqEV == fCXhRFykdL){PdMTqAbylc = true;}
      else if(fCXhRFykdL == aMiBVULqEV){ZJdBOqqsDm = true;}
      if(GaAEqJyRia == hOtgqrSIho){lrPSPyYOzi = true;}
      else if(hOtgqrSIho == GaAEqJyRia){bGyCimMOCp = true;}
      if(ZXBlsKNMos == HSwAQucjHz){kjjFQfmbPn = true;}
      else if(HSwAQucjHz == ZXBlsKNMos){YUbiDXidCS = true;}
      if(AnmMdrfnwq == rcMjtQqybW){jNAUhcQVXe = true;}
      else if(rcMjtQqybW == AnmMdrfnwq){bVilYRukED = true;}
      if(mRCEjTqyfu == gZqgrSnztr){IVfwuREOnw = true;}
      else if(gZqgrSnztr == mRCEjTqyfu){LGSfZcKQde = true;}
      if(PUbRTDKxHK == UHJtKMGXQW){thNeCfsHCK = true;}
      if(HzBLVSnnay == bOddSECKla){MzhxsXqtjm = true;}
      if(dKVqmIUwCZ == AUfKHgaOHy){gCpUaOEmJz = true;}
      while(UHJtKMGXQW == PUbRTDKxHK){wYeNyFguyp = true;}
      while(bOddSECKla == bOddSECKla){HNpkKFXLcQ = true;}
      while(AUfKHgaOHy == AUfKHgaOHy){qaJzdSCwIZ = true;}
      if(GdoPejTSZg == true){GdoPejTSZg = false;}
      if(JTgEtSwNNm == true){JTgEtSwNNm = false;}
      if(PdMTqAbylc == true){PdMTqAbylc = false;}
      if(lrPSPyYOzi == true){lrPSPyYOzi = false;}
      if(kjjFQfmbPn == true){kjjFQfmbPn = false;}
      if(jNAUhcQVXe == true){jNAUhcQVXe = false;}
      if(IVfwuREOnw == true){IVfwuREOnw = false;}
      if(thNeCfsHCK == true){thNeCfsHCK = false;}
      if(MzhxsXqtjm == true){MzhxsXqtjm = false;}
      if(gCpUaOEmJz == true){gCpUaOEmJz = false;}
      if(bYmTtCzVSB == true){bYmTtCzVSB = false;}
      if(iJTMRImhDW == true){iJTMRImhDW = false;}
      if(ZJdBOqqsDm == true){ZJdBOqqsDm = false;}
      if(bGyCimMOCp == true){bGyCimMOCp = false;}
      if(YUbiDXidCS == true){YUbiDXidCS = false;}
      if(bVilYRukED == true){bVilYRukED = false;}
      if(LGSfZcKQde == true){LGSfZcKQde = false;}
      if(wYeNyFguyp == true){wYeNyFguyp = false;}
      if(HNpkKFXLcQ == true){HNpkKFXLcQ = false;}
      if(qaJzdSCwIZ == true){qaJzdSCwIZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PEVCVJFQUS
{ 
  void uSQeCjucIl()
  { 
      bool iHQxQYUZSg = false;
      bool hYgGnCdlVC = false;
      bool rkmiHGSwAZ = false;
      bool kPuJOMkgmX = false;
      bool LmxImRYCWe = false;
      bool CjLQSyUhoJ = false;
      bool FXZruRcXqa = false;
      bool RxyypFmewo = false;
      bool hPZUWBEdqQ = false;
      bool rDqcRmNFMU = false;
      bool oBLuNFkNaM = false;
      bool KokAboyEUt = false;
      bool NyfZiOFVfD = false;
      bool rhRaAfEdHR = false;
      bool PpDdFCRpBb = false;
      bool nIjSGpVkLy = false;
      bool zPgWUcXJAw = false;
      bool kUxDdWuCUg = false;
      bool wPUEOixyTK = false;
      bool KTRIRAJfIc = false;
      string oqeEYbzAWM;
      string icRwmcGjwX;
      string YOroUJLFql;
      string xjPBSafJmP;
      string jLOiFpWPBJ;
      string XcCBFazojP;
      string QtIjPzMPcL;
      string wwwfmMzIie;
      string luDgOUgOwr;
      string bpZXzpDdTG;
      string dHmoNbfVOs;
      string apFEcUpaVt;
      string RxSkjFWYgw;
      string JVocAeHOTm;
      string nKzDQkkUud;
      string AbIYnfnBFI;
      string EHoRiFBcDy;
      string MbHhGHxPUy;
      string UBdDwgMPoU;
      string pGIKhfVhTK;
      if(oqeEYbzAWM == dHmoNbfVOs){iHQxQYUZSg = true;}
      else if(dHmoNbfVOs == oqeEYbzAWM){oBLuNFkNaM = true;}
      if(icRwmcGjwX == apFEcUpaVt){hYgGnCdlVC = true;}
      else if(apFEcUpaVt == icRwmcGjwX){KokAboyEUt = true;}
      if(YOroUJLFql == RxSkjFWYgw){rkmiHGSwAZ = true;}
      else if(RxSkjFWYgw == YOroUJLFql){NyfZiOFVfD = true;}
      if(xjPBSafJmP == JVocAeHOTm){kPuJOMkgmX = true;}
      else if(JVocAeHOTm == xjPBSafJmP){rhRaAfEdHR = true;}
      if(jLOiFpWPBJ == nKzDQkkUud){LmxImRYCWe = true;}
      else if(nKzDQkkUud == jLOiFpWPBJ){PpDdFCRpBb = true;}
      if(XcCBFazojP == AbIYnfnBFI){CjLQSyUhoJ = true;}
      else if(AbIYnfnBFI == XcCBFazojP){nIjSGpVkLy = true;}
      if(QtIjPzMPcL == EHoRiFBcDy){FXZruRcXqa = true;}
      else if(EHoRiFBcDy == QtIjPzMPcL){zPgWUcXJAw = true;}
      if(wwwfmMzIie == MbHhGHxPUy){RxyypFmewo = true;}
      if(luDgOUgOwr == UBdDwgMPoU){hPZUWBEdqQ = true;}
      if(bpZXzpDdTG == pGIKhfVhTK){rDqcRmNFMU = true;}
      while(MbHhGHxPUy == wwwfmMzIie){kUxDdWuCUg = true;}
      while(UBdDwgMPoU == UBdDwgMPoU){wPUEOixyTK = true;}
      while(pGIKhfVhTK == pGIKhfVhTK){KTRIRAJfIc = true;}
      if(iHQxQYUZSg == true){iHQxQYUZSg = false;}
      if(hYgGnCdlVC == true){hYgGnCdlVC = false;}
      if(rkmiHGSwAZ == true){rkmiHGSwAZ = false;}
      if(kPuJOMkgmX == true){kPuJOMkgmX = false;}
      if(LmxImRYCWe == true){LmxImRYCWe = false;}
      if(CjLQSyUhoJ == true){CjLQSyUhoJ = false;}
      if(FXZruRcXqa == true){FXZruRcXqa = false;}
      if(RxyypFmewo == true){RxyypFmewo = false;}
      if(hPZUWBEdqQ == true){hPZUWBEdqQ = false;}
      if(rDqcRmNFMU == true){rDqcRmNFMU = false;}
      if(oBLuNFkNaM == true){oBLuNFkNaM = false;}
      if(KokAboyEUt == true){KokAboyEUt = false;}
      if(NyfZiOFVfD == true){NyfZiOFVfD = false;}
      if(rhRaAfEdHR == true){rhRaAfEdHR = false;}
      if(PpDdFCRpBb == true){PpDdFCRpBb = false;}
      if(nIjSGpVkLy == true){nIjSGpVkLy = false;}
      if(zPgWUcXJAw == true){zPgWUcXJAw = false;}
      if(kUxDdWuCUg == true){kUxDdWuCUg = false;}
      if(wPUEOixyTK == true){wPUEOixyTK = false;}
      if(KTRIRAJfIc == true){KTRIRAJfIc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AOVZCFNGMH
{ 
  void PKLHCBWGyt()
  { 
      bool zdeWVLNBUm = false;
      bool JFtQsVcyGC = false;
      bool oydmAlHyDd = false;
      bool uWNRGaVweX = false;
      bool SOSNEVExTa = false;
      bool NrtaxBzrWi = false;
      bool EOypqmrbKS = false;
      bool AgTiiaePie = false;
      bool hKdcQDcmUF = false;
      bool adZuTDPcWR = false;
      bool dblBZgYLqV = false;
      bool VjIqBsjVZn = false;
      bool JEHFrWGXPf = false;
      bool KCsRAFXcCi = false;
      bool eQwyiqUhtZ = false;
      bool StChHYTgID = false;
      bool ZAuLLSpqqu = false;
      bool VHTpIsIJVB = false;
      bool BYdoMQzKJa = false;
      bool lpTyJdUjmP = false;
      string YuxHtjKGiF;
      string patwrbknWu;
      string uIyMMXFFLo;
      string oLKqhyzYVV;
      string qrRShQBLHn;
      string PiKKqPwjtV;
      string dEusQdQCOs;
      string cLSADDqfdw;
      string VtyWYFAzAR;
      string BOdzqmxXBD;
      string zywNLEQJHn;
      string YQFyzjFXUK;
      string dQCxqNgSJQ;
      string FSdawXyjLT;
      string oqrLrkIfzH;
      string gYCpZiwzWy;
      string WxApiFleBb;
      string kULAVlYpEF;
      string EATBifQmBN;
      string ayNNxqqBcl;
      if(YuxHtjKGiF == zywNLEQJHn){zdeWVLNBUm = true;}
      else if(zywNLEQJHn == YuxHtjKGiF){dblBZgYLqV = true;}
      if(patwrbknWu == YQFyzjFXUK){JFtQsVcyGC = true;}
      else if(YQFyzjFXUK == patwrbknWu){VjIqBsjVZn = true;}
      if(uIyMMXFFLo == dQCxqNgSJQ){oydmAlHyDd = true;}
      else if(dQCxqNgSJQ == uIyMMXFFLo){JEHFrWGXPf = true;}
      if(oLKqhyzYVV == FSdawXyjLT){uWNRGaVweX = true;}
      else if(FSdawXyjLT == oLKqhyzYVV){KCsRAFXcCi = true;}
      if(qrRShQBLHn == oqrLrkIfzH){SOSNEVExTa = true;}
      else if(oqrLrkIfzH == qrRShQBLHn){eQwyiqUhtZ = true;}
      if(PiKKqPwjtV == gYCpZiwzWy){NrtaxBzrWi = true;}
      else if(gYCpZiwzWy == PiKKqPwjtV){StChHYTgID = true;}
      if(dEusQdQCOs == WxApiFleBb){EOypqmrbKS = true;}
      else if(WxApiFleBb == dEusQdQCOs){ZAuLLSpqqu = true;}
      if(cLSADDqfdw == kULAVlYpEF){AgTiiaePie = true;}
      if(VtyWYFAzAR == EATBifQmBN){hKdcQDcmUF = true;}
      if(BOdzqmxXBD == ayNNxqqBcl){adZuTDPcWR = true;}
      while(kULAVlYpEF == cLSADDqfdw){VHTpIsIJVB = true;}
      while(EATBifQmBN == EATBifQmBN){BYdoMQzKJa = true;}
      while(ayNNxqqBcl == ayNNxqqBcl){lpTyJdUjmP = true;}
      if(zdeWVLNBUm == true){zdeWVLNBUm = false;}
      if(JFtQsVcyGC == true){JFtQsVcyGC = false;}
      if(oydmAlHyDd == true){oydmAlHyDd = false;}
      if(uWNRGaVweX == true){uWNRGaVweX = false;}
      if(SOSNEVExTa == true){SOSNEVExTa = false;}
      if(NrtaxBzrWi == true){NrtaxBzrWi = false;}
      if(EOypqmrbKS == true){EOypqmrbKS = false;}
      if(AgTiiaePie == true){AgTiiaePie = false;}
      if(hKdcQDcmUF == true){hKdcQDcmUF = false;}
      if(adZuTDPcWR == true){adZuTDPcWR = false;}
      if(dblBZgYLqV == true){dblBZgYLqV = false;}
      if(VjIqBsjVZn == true){VjIqBsjVZn = false;}
      if(JEHFrWGXPf == true){JEHFrWGXPf = false;}
      if(KCsRAFXcCi == true){KCsRAFXcCi = false;}
      if(eQwyiqUhtZ == true){eQwyiqUhtZ = false;}
      if(StChHYTgID == true){StChHYTgID = false;}
      if(ZAuLLSpqqu == true){ZAuLLSpqqu = false;}
      if(VHTpIsIJVB == true){VHTpIsIJVB = false;}
      if(BYdoMQzKJa == true){BYdoMQzKJa = false;}
      if(lpTyJdUjmP == true){lpTyJdUjmP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IUEMBEOQOK
{ 
  void wINXJJZCWu()
  { 
      bool aqIUHOCuaV = false;
      bool pEJzdxmlyS = false;
      bool bWKKIhQJUW = false;
      bool yBrpZCKNHU = false;
      bool cgpkZbGyzs = false;
      bool JRFPPEgxLZ = false;
      bool yraDWoLSZa = false;
      bool lZedoufYkg = false;
      bool aRKbMgwbaU = false;
      bool UNBgVkFlNk = false;
      bool PmYXGjlbaT = false;
      bool XHMdyfgzqp = false;
      bool rjrEGYYxHD = false;
      bool osKARnsmUc = false;
      bool tUAGxNAWip = false;
      bool DGuXrftUQh = false;
      bool LoTXedwLMK = false;
      bool mtdNuXilGs = false;
      bool XBORAiylIl = false;
      bool sXVmRFAcbT = false;
      string bpuBmStRYI;
      string SMWzuanEne;
      string iftiNpaPGb;
      string qglOhMSLEF;
      string XmWzTNsqzg;
      string xLEDPwuMnw;
      string qeLxRlZHRh;
      string IbzhHwItOA;
      string xiQYdebhzk;
      string QGXINsbZhh;
      string nlZRYVMVwS;
      string nBxmzHOlSm;
      string JqHfQCEqUO;
      string UiMfMKJyzH;
      string SFlgxPIjJF;
      string eoGuYwesAW;
      string RUBhyEnRan;
      string yPmKTDFaiA;
      string sThOjfbRGP;
      string fQycpxEDhr;
      if(bpuBmStRYI == nlZRYVMVwS){aqIUHOCuaV = true;}
      else if(nlZRYVMVwS == bpuBmStRYI){PmYXGjlbaT = true;}
      if(SMWzuanEne == nBxmzHOlSm){pEJzdxmlyS = true;}
      else if(nBxmzHOlSm == SMWzuanEne){XHMdyfgzqp = true;}
      if(iftiNpaPGb == JqHfQCEqUO){bWKKIhQJUW = true;}
      else if(JqHfQCEqUO == iftiNpaPGb){rjrEGYYxHD = true;}
      if(qglOhMSLEF == UiMfMKJyzH){yBrpZCKNHU = true;}
      else if(UiMfMKJyzH == qglOhMSLEF){osKARnsmUc = true;}
      if(XmWzTNsqzg == SFlgxPIjJF){cgpkZbGyzs = true;}
      else if(SFlgxPIjJF == XmWzTNsqzg){tUAGxNAWip = true;}
      if(xLEDPwuMnw == eoGuYwesAW){JRFPPEgxLZ = true;}
      else if(eoGuYwesAW == xLEDPwuMnw){DGuXrftUQh = true;}
      if(qeLxRlZHRh == RUBhyEnRan){yraDWoLSZa = true;}
      else if(RUBhyEnRan == qeLxRlZHRh){LoTXedwLMK = true;}
      if(IbzhHwItOA == yPmKTDFaiA){lZedoufYkg = true;}
      if(xiQYdebhzk == sThOjfbRGP){aRKbMgwbaU = true;}
      if(QGXINsbZhh == fQycpxEDhr){UNBgVkFlNk = true;}
      while(yPmKTDFaiA == IbzhHwItOA){mtdNuXilGs = true;}
      while(sThOjfbRGP == sThOjfbRGP){XBORAiylIl = true;}
      while(fQycpxEDhr == fQycpxEDhr){sXVmRFAcbT = true;}
      if(aqIUHOCuaV == true){aqIUHOCuaV = false;}
      if(pEJzdxmlyS == true){pEJzdxmlyS = false;}
      if(bWKKIhQJUW == true){bWKKIhQJUW = false;}
      if(yBrpZCKNHU == true){yBrpZCKNHU = false;}
      if(cgpkZbGyzs == true){cgpkZbGyzs = false;}
      if(JRFPPEgxLZ == true){JRFPPEgxLZ = false;}
      if(yraDWoLSZa == true){yraDWoLSZa = false;}
      if(lZedoufYkg == true){lZedoufYkg = false;}
      if(aRKbMgwbaU == true){aRKbMgwbaU = false;}
      if(UNBgVkFlNk == true){UNBgVkFlNk = false;}
      if(PmYXGjlbaT == true){PmYXGjlbaT = false;}
      if(XHMdyfgzqp == true){XHMdyfgzqp = false;}
      if(rjrEGYYxHD == true){rjrEGYYxHD = false;}
      if(osKARnsmUc == true){osKARnsmUc = false;}
      if(tUAGxNAWip == true){tUAGxNAWip = false;}
      if(DGuXrftUQh == true){DGuXrftUQh = false;}
      if(LoTXedwLMK == true){LoTXedwLMK = false;}
      if(mtdNuXilGs == true){mtdNuXilGs = false;}
      if(XBORAiylIl == true){XBORAiylIl = false;}
      if(sXVmRFAcbT == true){sXVmRFAcbT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IKFZSIGSKV
{ 
  void HlYdCtfXLz()
  { 
      bool wbaNCrogct = false;
      bool xjGiuQHXaT = false;
      bool RkypRUFGDS = false;
      bool iLqtICspRH = false;
      bool lBnBfIXaVV = false;
      bool ybWtaLdkwh = false;
      bool lidKKkrLas = false;
      bool WQFSgPwwJI = false;
      bool wekgUHowTw = false;
      bool XItjVDXdpu = false;
      bool PLzbygVDMK = false;
      bool OgamkHywpD = false;
      bool uwqdUOWUwc = false;
      bool rSGNsjeIhm = false;
      bool kkiJhqgGzN = false;
      bool FammATTVHj = false;
      bool KBGiRuaMtA = false;
      bool coNDRJMhwd = false;
      bool gPUhXReSNY = false;
      bool QIAybjezql = false;
      string VhCadbOHcq;
      string yLxfYUmrsK;
      string QUBJAyEHdn;
      string rRWoAAgZww;
      string eDbpicLGQN;
      string OkLPwAfsae;
      string WHdnyfoHfX;
      string nNuwfNsLaX;
      string lyqPZHGHsz;
      string TnyRZXZmrC;
      string nEZrZApOii;
      string GURDrXPNOp;
      string ZgOfDAPdWI;
      string nGSXjhYzpY;
      string RqXJryVtYB;
      string ILXBcGotnZ;
      string kLrauACsTK;
      string zQWpYhJFmE;
      string dUEUAbiQuc;
      string reKQmFzxNr;
      if(VhCadbOHcq == nEZrZApOii){wbaNCrogct = true;}
      else if(nEZrZApOii == VhCadbOHcq){PLzbygVDMK = true;}
      if(yLxfYUmrsK == GURDrXPNOp){xjGiuQHXaT = true;}
      else if(GURDrXPNOp == yLxfYUmrsK){OgamkHywpD = true;}
      if(QUBJAyEHdn == ZgOfDAPdWI){RkypRUFGDS = true;}
      else if(ZgOfDAPdWI == QUBJAyEHdn){uwqdUOWUwc = true;}
      if(rRWoAAgZww == nGSXjhYzpY){iLqtICspRH = true;}
      else if(nGSXjhYzpY == rRWoAAgZww){rSGNsjeIhm = true;}
      if(eDbpicLGQN == RqXJryVtYB){lBnBfIXaVV = true;}
      else if(RqXJryVtYB == eDbpicLGQN){kkiJhqgGzN = true;}
      if(OkLPwAfsae == ILXBcGotnZ){ybWtaLdkwh = true;}
      else if(ILXBcGotnZ == OkLPwAfsae){FammATTVHj = true;}
      if(WHdnyfoHfX == kLrauACsTK){lidKKkrLas = true;}
      else if(kLrauACsTK == WHdnyfoHfX){KBGiRuaMtA = true;}
      if(nNuwfNsLaX == zQWpYhJFmE){WQFSgPwwJI = true;}
      if(lyqPZHGHsz == dUEUAbiQuc){wekgUHowTw = true;}
      if(TnyRZXZmrC == reKQmFzxNr){XItjVDXdpu = true;}
      while(zQWpYhJFmE == nNuwfNsLaX){coNDRJMhwd = true;}
      while(dUEUAbiQuc == dUEUAbiQuc){gPUhXReSNY = true;}
      while(reKQmFzxNr == reKQmFzxNr){QIAybjezql = true;}
      if(wbaNCrogct == true){wbaNCrogct = false;}
      if(xjGiuQHXaT == true){xjGiuQHXaT = false;}
      if(RkypRUFGDS == true){RkypRUFGDS = false;}
      if(iLqtICspRH == true){iLqtICspRH = false;}
      if(lBnBfIXaVV == true){lBnBfIXaVV = false;}
      if(ybWtaLdkwh == true){ybWtaLdkwh = false;}
      if(lidKKkrLas == true){lidKKkrLas = false;}
      if(WQFSgPwwJI == true){WQFSgPwwJI = false;}
      if(wekgUHowTw == true){wekgUHowTw = false;}
      if(XItjVDXdpu == true){XItjVDXdpu = false;}
      if(PLzbygVDMK == true){PLzbygVDMK = false;}
      if(OgamkHywpD == true){OgamkHywpD = false;}
      if(uwqdUOWUwc == true){uwqdUOWUwc = false;}
      if(rSGNsjeIhm == true){rSGNsjeIhm = false;}
      if(kkiJhqgGzN == true){kkiJhqgGzN = false;}
      if(FammATTVHj == true){FammATTVHj = false;}
      if(KBGiRuaMtA == true){KBGiRuaMtA = false;}
      if(coNDRJMhwd == true){coNDRJMhwd = false;}
      if(gPUhXReSNY == true){gPUhXReSNY = false;}
      if(QIAybjezql == true){QIAybjezql = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBIGJOJGNL
{ 
  void WexeXwCzsi()
  { 
      bool LNnkDAgHjT = false;
      bool QHmdyqbRdy = false;
      bool TYDQFELyyx = false;
      bool eAnbNmEaOZ = false;
      bool PlSEZBHxlT = false;
      bool iNcScmJWey = false;
      bool nhJmoPTKPK = false;
      bool mACDihFzqE = false;
      bool xOMeNQXVza = false;
      bool dgwQkgcfPJ = false;
      bool hwgaghKYju = false;
      bool gKfaBZVdYX = false;
      bool ryLngFDlSB = false;
      bool EYigVAglye = false;
      bool GykEsSBVOL = false;
      bool LyHrQikrsb = false;
      bool eYGipHbyEB = false;
      bool rjfsRtMGuO = false;
      bool DhWHoGRqPl = false;
      bool OnrWAgqCNk = false;
      string jJwhTZBgdB;
      string yHVIzYOcui;
      string fctHzcQmjE;
      string xDLepZKDdQ;
      string RhuBzoXOpG;
      string jyhhHGPnhq;
      string INxZEtwqSY;
      string NKydQxgrIJ;
      string ECwcUyUcWi;
      string KVUlIEjVxE;
      string sguRrYAERJ;
      string YWfYlGQTEF;
      string ZTTiNroLUM;
      string NLuDQWGeku;
      string yPLNKnpwAC;
      string mPRqeYNLDA;
      string jnjEwNbbIP;
      string zliJHKIFYZ;
      string BrLSZxtDYq;
      string JtajKKeHRw;
      if(jJwhTZBgdB == sguRrYAERJ){LNnkDAgHjT = true;}
      else if(sguRrYAERJ == jJwhTZBgdB){hwgaghKYju = true;}
      if(yHVIzYOcui == YWfYlGQTEF){QHmdyqbRdy = true;}
      else if(YWfYlGQTEF == yHVIzYOcui){gKfaBZVdYX = true;}
      if(fctHzcQmjE == ZTTiNroLUM){TYDQFELyyx = true;}
      else if(ZTTiNroLUM == fctHzcQmjE){ryLngFDlSB = true;}
      if(xDLepZKDdQ == NLuDQWGeku){eAnbNmEaOZ = true;}
      else if(NLuDQWGeku == xDLepZKDdQ){EYigVAglye = true;}
      if(RhuBzoXOpG == yPLNKnpwAC){PlSEZBHxlT = true;}
      else if(yPLNKnpwAC == RhuBzoXOpG){GykEsSBVOL = true;}
      if(jyhhHGPnhq == mPRqeYNLDA){iNcScmJWey = true;}
      else if(mPRqeYNLDA == jyhhHGPnhq){LyHrQikrsb = true;}
      if(INxZEtwqSY == jnjEwNbbIP){nhJmoPTKPK = true;}
      else if(jnjEwNbbIP == INxZEtwqSY){eYGipHbyEB = true;}
      if(NKydQxgrIJ == zliJHKIFYZ){mACDihFzqE = true;}
      if(ECwcUyUcWi == BrLSZxtDYq){xOMeNQXVza = true;}
      if(KVUlIEjVxE == JtajKKeHRw){dgwQkgcfPJ = true;}
      while(zliJHKIFYZ == NKydQxgrIJ){rjfsRtMGuO = true;}
      while(BrLSZxtDYq == BrLSZxtDYq){DhWHoGRqPl = true;}
      while(JtajKKeHRw == JtajKKeHRw){OnrWAgqCNk = true;}
      if(LNnkDAgHjT == true){LNnkDAgHjT = false;}
      if(QHmdyqbRdy == true){QHmdyqbRdy = false;}
      if(TYDQFELyyx == true){TYDQFELyyx = false;}
      if(eAnbNmEaOZ == true){eAnbNmEaOZ = false;}
      if(PlSEZBHxlT == true){PlSEZBHxlT = false;}
      if(iNcScmJWey == true){iNcScmJWey = false;}
      if(nhJmoPTKPK == true){nhJmoPTKPK = false;}
      if(mACDihFzqE == true){mACDihFzqE = false;}
      if(xOMeNQXVza == true){xOMeNQXVza = false;}
      if(dgwQkgcfPJ == true){dgwQkgcfPJ = false;}
      if(hwgaghKYju == true){hwgaghKYju = false;}
      if(gKfaBZVdYX == true){gKfaBZVdYX = false;}
      if(ryLngFDlSB == true){ryLngFDlSB = false;}
      if(EYigVAglye == true){EYigVAglye = false;}
      if(GykEsSBVOL == true){GykEsSBVOL = false;}
      if(LyHrQikrsb == true){LyHrQikrsb = false;}
      if(eYGipHbyEB == true){eYGipHbyEB = false;}
      if(rjfsRtMGuO == true){rjfsRtMGuO = false;}
      if(DhWHoGRqPl == true){DhWHoGRqPl = false;}
      if(OnrWAgqCNk == true){OnrWAgqCNk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZYMLAHPENF
{ 
  void rOwJyPVAte()
  { 
      bool XMWKClkdJj = false;
      bool DCmUzYDdcJ = false;
      bool PLDFxDwDxa = false;
      bool qfMESdqrmY = false;
      bool yyOOiQoydM = false;
      bool kTBmaMJQMz = false;
      bool ohfirWpiCU = false;
      bool gKqDKRwoWg = false;
      bool NxYjoXeZcG = false;
      bool UaemiQRfVM = false;
      bool ZGwIeabxbJ = false;
      bool PTsflrIwsU = false;
      bool qPFuzGeDTt = false;
      bool zQSJGGBQEO = false;
      bool ugxTqAgzBq = false;
      bool HVmAUKAAIX = false;
      bool uXchJyBjZe = false;
      bool qrqdZKRlEz = false;
      bool ZfCbmdcSow = false;
      bool FAHfSWEPKr = false;
      string RdcdaPraeK;
      string QwgMFQhNAI;
      string AXLypmsAKl;
      string SBsxMLTwLz;
      string rgNbtwuPGs;
      string AlrUNsSdmn;
      string WqPsqPDizs;
      string wkBAQSKiDt;
      string qctQlfIXjT;
      string spIXcBQTke;
      string sLPMxOkqEt;
      string iiaswsxzGL;
      string GezfAGcdXP;
      string BpyXAfMgTX;
      string uQTojJPOai;
      string DRNZYNMjMp;
      string lGTosskCrQ;
      string fQfiPoKJwq;
      string qNDoLjcYyl;
      string TcTckoxdwq;
      if(RdcdaPraeK == sLPMxOkqEt){XMWKClkdJj = true;}
      else if(sLPMxOkqEt == RdcdaPraeK){ZGwIeabxbJ = true;}
      if(QwgMFQhNAI == iiaswsxzGL){DCmUzYDdcJ = true;}
      else if(iiaswsxzGL == QwgMFQhNAI){PTsflrIwsU = true;}
      if(AXLypmsAKl == GezfAGcdXP){PLDFxDwDxa = true;}
      else if(GezfAGcdXP == AXLypmsAKl){qPFuzGeDTt = true;}
      if(SBsxMLTwLz == BpyXAfMgTX){qfMESdqrmY = true;}
      else if(BpyXAfMgTX == SBsxMLTwLz){zQSJGGBQEO = true;}
      if(rgNbtwuPGs == uQTojJPOai){yyOOiQoydM = true;}
      else if(uQTojJPOai == rgNbtwuPGs){ugxTqAgzBq = true;}
      if(AlrUNsSdmn == DRNZYNMjMp){kTBmaMJQMz = true;}
      else if(DRNZYNMjMp == AlrUNsSdmn){HVmAUKAAIX = true;}
      if(WqPsqPDizs == lGTosskCrQ){ohfirWpiCU = true;}
      else if(lGTosskCrQ == WqPsqPDizs){uXchJyBjZe = true;}
      if(wkBAQSKiDt == fQfiPoKJwq){gKqDKRwoWg = true;}
      if(qctQlfIXjT == qNDoLjcYyl){NxYjoXeZcG = true;}
      if(spIXcBQTke == TcTckoxdwq){UaemiQRfVM = true;}
      while(fQfiPoKJwq == wkBAQSKiDt){qrqdZKRlEz = true;}
      while(qNDoLjcYyl == qNDoLjcYyl){ZfCbmdcSow = true;}
      while(TcTckoxdwq == TcTckoxdwq){FAHfSWEPKr = true;}
      if(XMWKClkdJj == true){XMWKClkdJj = false;}
      if(DCmUzYDdcJ == true){DCmUzYDdcJ = false;}
      if(PLDFxDwDxa == true){PLDFxDwDxa = false;}
      if(qfMESdqrmY == true){qfMESdqrmY = false;}
      if(yyOOiQoydM == true){yyOOiQoydM = false;}
      if(kTBmaMJQMz == true){kTBmaMJQMz = false;}
      if(ohfirWpiCU == true){ohfirWpiCU = false;}
      if(gKqDKRwoWg == true){gKqDKRwoWg = false;}
      if(NxYjoXeZcG == true){NxYjoXeZcG = false;}
      if(UaemiQRfVM == true){UaemiQRfVM = false;}
      if(ZGwIeabxbJ == true){ZGwIeabxbJ = false;}
      if(PTsflrIwsU == true){PTsflrIwsU = false;}
      if(qPFuzGeDTt == true){qPFuzGeDTt = false;}
      if(zQSJGGBQEO == true){zQSJGGBQEO = false;}
      if(ugxTqAgzBq == true){ugxTqAgzBq = false;}
      if(HVmAUKAAIX == true){HVmAUKAAIX = false;}
      if(uXchJyBjZe == true){uXchJyBjZe = false;}
      if(qrqdZKRlEz == true){qrqdZKRlEz = false;}
      if(ZfCbmdcSow == true){ZfCbmdcSow = false;}
      if(FAHfSWEPKr == true){FAHfSWEPKr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CDGUXBMRHX
{ 
  void cQESmRBuOp()
  { 
      bool EjBOhiIzsf = false;
      bool pWegcmfXfd = false;
      bool rESWBmBawd = false;
      bool nndPcqppBL = false;
      bool dOsUpiATXq = false;
      bool xETCqzRdNt = false;
      bool hhDPqCsODl = false;
      bool woVUzdLxfR = false;
      bool lhCFfjUaYc = false;
      bool YLcGdwLdcn = false;
      bool plPltHhzDN = false;
      bool nTyuIAeyiH = false;
      bool hRpZMjLPpC = false;
      bool ShTrazRQKX = false;
      bool BVXKoFNgyd = false;
      bool RMtVGXwoZJ = false;
      bool wSIAuGzGTI = false;
      bool hOmKFMtekG = false;
      bool WdRMkFmykD = false;
      bool DbpAbiNWPi = false;
      string TPaSsrSrzh;
      string DZILOhHmDG;
      string YacOyRhxXe;
      string jeaNgMgoso;
      string XkcTUslAri;
      string tHFqasmLUa;
      string KVUTyYzueC;
      string ARtOimxItF;
      string egEnkbZilm;
      string ZVURdCQIVw;
      string sqVpibNpIn;
      string wdRPudQgiV;
      string zPJqbexbjg;
      string WnmxLnKOEI;
      string OiayquDFVA;
      string kjZAwdheNE;
      string ekGaQHqTDH;
      string SCbZGQnKAg;
      string arFiumOlBg;
      string GfAAdcbzgj;
      if(TPaSsrSrzh == sqVpibNpIn){EjBOhiIzsf = true;}
      else if(sqVpibNpIn == TPaSsrSrzh){plPltHhzDN = true;}
      if(DZILOhHmDG == wdRPudQgiV){pWegcmfXfd = true;}
      else if(wdRPudQgiV == DZILOhHmDG){nTyuIAeyiH = true;}
      if(YacOyRhxXe == zPJqbexbjg){rESWBmBawd = true;}
      else if(zPJqbexbjg == YacOyRhxXe){hRpZMjLPpC = true;}
      if(jeaNgMgoso == WnmxLnKOEI){nndPcqppBL = true;}
      else if(WnmxLnKOEI == jeaNgMgoso){ShTrazRQKX = true;}
      if(XkcTUslAri == OiayquDFVA){dOsUpiATXq = true;}
      else if(OiayquDFVA == XkcTUslAri){BVXKoFNgyd = true;}
      if(tHFqasmLUa == kjZAwdheNE){xETCqzRdNt = true;}
      else if(kjZAwdheNE == tHFqasmLUa){RMtVGXwoZJ = true;}
      if(KVUTyYzueC == ekGaQHqTDH){hhDPqCsODl = true;}
      else if(ekGaQHqTDH == KVUTyYzueC){wSIAuGzGTI = true;}
      if(ARtOimxItF == SCbZGQnKAg){woVUzdLxfR = true;}
      if(egEnkbZilm == arFiumOlBg){lhCFfjUaYc = true;}
      if(ZVURdCQIVw == GfAAdcbzgj){YLcGdwLdcn = true;}
      while(SCbZGQnKAg == ARtOimxItF){hOmKFMtekG = true;}
      while(arFiumOlBg == arFiumOlBg){WdRMkFmykD = true;}
      while(GfAAdcbzgj == GfAAdcbzgj){DbpAbiNWPi = true;}
      if(EjBOhiIzsf == true){EjBOhiIzsf = false;}
      if(pWegcmfXfd == true){pWegcmfXfd = false;}
      if(rESWBmBawd == true){rESWBmBawd = false;}
      if(nndPcqppBL == true){nndPcqppBL = false;}
      if(dOsUpiATXq == true){dOsUpiATXq = false;}
      if(xETCqzRdNt == true){xETCqzRdNt = false;}
      if(hhDPqCsODl == true){hhDPqCsODl = false;}
      if(woVUzdLxfR == true){woVUzdLxfR = false;}
      if(lhCFfjUaYc == true){lhCFfjUaYc = false;}
      if(YLcGdwLdcn == true){YLcGdwLdcn = false;}
      if(plPltHhzDN == true){plPltHhzDN = false;}
      if(nTyuIAeyiH == true){nTyuIAeyiH = false;}
      if(hRpZMjLPpC == true){hRpZMjLPpC = false;}
      if(ShTrazRQKX == true){ShTrazRQKX = false;}
      if(BVXKoFNgyd == true){BVXKoFNgyd = false;}
      if(RMtVGXwoZJ == true){RMtVGXwoZJ = false;}
      if(wSIAuGzGTI == true){wSIAuGzGTI = false;}
      if(hOmKFMtekG == true){hOmKFMtekG = false;}
      if(WdRMkFmykD == true){WdRMkFmykD = false;}
      if(DbpAbiNWPi == true){DbpAbiNWPi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OIOSSIFJTS
{ 
  void ByISzruiQP()
  { 
      bool XdpLiKbMBn = false;
      bool urpEiQSYJd = false;
      bool pgVJphCnXV = false;
      bool lUTEWpXbWH = false;
      bool QAAadhSWLJ = false;
      bool LYTgcqHgVA = false;
      bool HmneBaYlgs = false;
      bool spCBNpgtfH = false;
      bool PfcOJNAlaf = false;
      bool hpFVzcLUYC = false;
      bool IfoSPVWRTl = false;
      bool KNBNkbKZVn = false;
      bool ZmLBKCjfCj = false;
      bool dMVczjpJyn = false;
      bool qhRnVUoqkW = false;
      bool SlzjcVUnIM = false;
      bool kpOiIxrXOB = false;
      bool lAagxqUWeo = false;
      bool NrtfRrNkAc = false;
      bool OBBkDATifX = false;
      string rsHRnYDNmd;
      string UHIAKEKrDX;
      string PeSKAqdWsJ;
      string lTSkJQitli;
      string YPrelkIyuH;
      string jcffaMZxRw;
      string tfUdrAoXps;
      string UQGUyzlnYO;
      string iebkYInlJw;
      string qlconruOlk;
      string wkIBlTWKha;
      string ZkXCNOEiEj;
      string MCNtBhnQfG;
      string EWCmSxWazF;
      string kcEhVGOZbZ;
      string nLKBXsXNzD;
      string eGeaWChkiP;
      string qdjyzjxeXu;
      string TNnFRrMBOZ;
      string ZIauZdxcLT;
      if(rsHRnYDNmd == wkIBlTWKha){XdpLiKbMBn = true;}
      else if(wkIBlTWKha == rsHRnYDNmd){IfoSPVWRTl = true;}
      if(UHIAKEKrDX == ZkXCNOEiEj){urpEiQSYJd = true;}
      else if(ZkXCNOEiEj == UHIAKEKrDX){KNBNkbKZVn = true;}
      if(PeSKAqdWsJ == MCNtBhnQfG){pgVJphCnXV = true;}
      else if(MCNtBhnQfG == PeSKAqdWsJ){ZmLBKCjfCj = true;}
      if(lTSkJQitli == EWCmSxWazF){lUTEWpXbWH = true;}
      else if(EWCmSxWazF == lTSkJQitli){dMVczjpJyn = true;}
      if(YPrelkIyuH == kcEhVGOZbZ){QAAadhSWLJ = true;}
      else if(kcEhVGOZbZ == YPrelkIyuH){qhRnVUoqkW = true;}
      if(jcffaMZxRw == nLKBXsXNzD){LYTgcqHgVA = true;}
      else if(nLKBXsXNzD == jcffaMZxRw){SlzjcVUnIM = true;}
      if(tfUdrAoXps == eGeaWChkiP){HmneBaYlgs = true;}
      else if(eGeaWChkiP == tfUdrAoXps){kpOiIxrXOB = true;}
      if(UQGUyzlnYO == qdjyzjxeXu){spCBNpgtfH = true;}
      if(iebkYInlJw == TNnFRrMBOZ){PfcOJNAlaf = true;}
      if(qlconruOlk == ZIauZdxcLT){hpFVzcLUYC = true;}
      while(qdjyzjxeXu == UQGUyzlnYO){lAagxqUWeo = true;}
      while(TNnFRrMBOZ == TNnFRrMBOZ){NrtfRrNkAc = true;}
      while(ZIauZdxcLT == ZIauZdxcLT){OBBkDATifX = true;}
      if(XdpLiKbMBn == true){XdpLiKbMBn = false;}
      if(urpEiQSYJd == true){urpEiQSYJd = false;}
      if(pgVJphCnXV == true){pgVJphCnXV = false;}
      if(lUTEWpXbWH == true){lUTEWpXbWH = false;}
      if(QAAadhSWLJ == true){QAAadhSWLJ = false;}
      if(LYTgcqHgVA == true){LYTgcqHgVA = false;}
      if(HmneBaYlgs == true){HmneBaYlgs = false;}
      if(spCBNpgtfH == true){spCBNpgtfH = false;}
      if(PfcOJNAlaf == true){PfcOJNAlaf = false;}
      if(hpFVzcLUYC == true){hpFVzcLUYC = false;}
      if(IfoSPVWRTl == true){IfoSPVWRTl = false;}
      if(KNBNkbKZVn == true){KNBNkbKZVn = false;}
      if(ZmLBKCjfCj == true){ZmLBKCjfCj = false;}
      if(dMVczjpJyn == true){dMVczjpJyn = false;}
      if(qhRnVUoqkW == true){qhRnVUoqkW = false;}
      if(SlzjcVUnIM == true){SlzjcVUnIM = false;}
      if(kpOiIxrXOB == true){kpOiIxrXOB = false;}
      if(lAagxqUWeo == true){lAagxqUWeo = false;}
      if(NrtfRrNkAc == true){NrtfRrNkAc = false;}
      if(OBBkDATifX == true){OBBkDATifX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WGBZHXTUPV
{ 
  void rgqRJpRzMQ()
  { 
      bool sSCRycodju = false;
      bool HzOVQwBZFu = false;
      bool tcwZsAgCMA = false;
      bool BYJqixCXkn = false;
      bool hATGReREZk = false;
      bool oipciPVbYx = false;
      bool wmQitioWlT = false;
      bool tdnQNsJpIO = false;
      bool icbaLRigHS = false;
      bool aZymrtjjMh = false;
      bool otRGqLtYOp = false;
      bool GfTKOTKpXb = false;
      bool AHPSrTeAYS = false;
      bool JYdZYnKVjA = false;
      bool WJSRMuGnYX = false;
      bool jsMjhgeyNW = false;
      bool gtAufhBskZ = false;
      bool IoFWEpoxGw = false;
      bool NpbAiPLsqq = false;
      bool JMHMScJWkd = false;
      string EEqZQthBWK;
      string bReKYVWhjw;
      string DYKuKNcXAD;
      string gHlqJgSQcs;
      string bzUdEttHuP;
      string NcPtceswPC;
      string RJAScUenBr;
      string DGFpUEDfpP;
      string SVcjpEqrOd;
      string nWAZaRyBAi;
      string OGGDMGWYZX;
      string bMFzjwgQcY;
      string cmYWDfFfOC;
      string FCfHALOZWi;
      string gSSpCaQApe;
      string khXbFbhizf;
      string BqJWSYgyyX;
      string gHstqKThUc;
      string PEpjRWeEBY;
      string dfZphpJuXc;
      if(EEqZQthBWK == OGGDMGWYZX){sSCRycodju = true;}
      else if(OGGDMGWYZX == EEqZQthBWK){otRGqLtYOp = true;}
      if(bReKYVWhjw == bMFzjwgQcY){HzOVQwBZFu = true;}
      else if(bMFzjwgQcY == bReKYVWhjw){GfTKOTKpXb = true;}
      if(DYKuKNcXAD == cmYWDfFfOC){tcwZsAgCMA = true;}
      else if(cmYWDfFfOC == DYKuKNcXAD){AHPSrTeAYS = true;}
      if(gHlqJgSQcs == FCfHALOZWi){BYJqixCXkn = true;}
      else if(FCfHALOZWi == gHlqJgSQcs){JYdZYnKVjA = true;}
      if(bzUdEttHuP == gSSpCaQApe){hATGReREZk = true;}
      else if(gSSpCaQApe == bzUdEttHuP){WJSRMuGnYX = true;}
      if(NcPtceswPC == khXbFbhizf){oipciPVbYx = true;}
      else if(khXbFbhizf == NcPtceswPC){jsMjhgeyNW = true;}
      if(RJAScUenBr == BqJWSYgyyX){wmQitioWlT = true;}
      else if(BqJWSYgyyX == RJAScUenBr){gtAufhBskZ = true;}
      if(DGFpUEDfpP == gHstqKThUc){tdnQNsJpIO = true;}
      if(SVcjpEqrOd == PEpjRWeEBY){icbaLRigHS = true;}
      if(nWAZaRyBAi == dfZphpJuXc){aZymrtjjMh = true;}
      while(gHstqKThUc == DGFpUEDfpP){IoFWEpoxGw = true;}
      while(PEpjRWeEBY == PEpjRWeEBY){NpbAiPLsqq = true;}
      while(dfZphpJuXc == dfZphpJuXc){JMHMScJWkd = true;}
      if(sSCRycodju == true){sSCRycodju = false;}
      if(HzOVQwBZFu == true){HzOVQwBZFu = false;}
      if(tcwZsAgCMA == true){tcwZsAgCMA = false;}
      if(BYJqixCXkn == true){BYJqixCXkn = false;}
      if(hATGReREZk == true){hATGReREZk = false;}
      if(oipciPVbYx == true){oipciPVbYx = false;}
      if(wmQitioWlT == true){wmQitioWlT = false;}
      if(tdnQNsJpIO == true){tdnQNsJpIO = false;}
      if(icbaLRigHS == true){icbaLRigHS = false;}
      if(aZymrtjjMh == true){aZymrtjjMh = false;}
      if(otRGqLtYOp == true){otRGqLtYOp = false;}
      if(GfTKOTKpXb == true){GfTKOTKpXb = false;}
      if(AHPSrTeAYS == true){AHPSrTeAYS = false;}
      if(JYdZYnKVjA == true){JYdZYnKVjA = false;}
      if(WJSRMuGnYX == true){WJSRMuGnYX = false;}
      if(jsMjhgeyNW == true){jsMjhgeyNW = false;}
      if(gtAufhBskZ == true){gtAufhBskZ = false;}
      if(IoFWEpoxGw == true){IoFWEpoxGw = false;}
      if(NpbAiPLsqq == true){NpbAiPLsqq = false;}
      if(JMHMScJWkd == true){JMHMScJWkd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCBTHGGAPO
{ 
  void JjyplMExRz()
  { 
      bool kANcMOAZmb = false;
      bool yxhSfMJgGC = false;
      bool rcXuSyxoMo = false;
      bool NPDTwLErid = false;
      bool gEoCeCqUFz = false;
      bool HqewoIcRKN = false;
      bool QLNyOitOWU = false;
      bool HQxbVnmVQP = false;
      bool HciMgWjGdm = false;
      bool ilhVMUqqmu = false;
      bool HbykqpsCaB = false;
      bool UGBtGnbAQr = false;
      bool znjikVibPA = false;
      bool wwhVIeexVq = false;
      bool cgecSbknOY = false;
      bool rqZuuSrOzV = false;
      bool HRmZEXYelb = false;
      bool IeeZOSJHQJ = false;
      bool jtMpHFWmZo = false;
      bool lPxziLsEXt = false;
      string jRVlugREpU;
      string JHgELxAAxe;
      string VsTjTozeJB;
      string VPpQtSjHUz;
      string McCxsDCzRV;
      string bbGLmpylRG;
      string gltnytQPJr;
      string NsfySsqVqP;
      string mzNmYtIddD;
      string TxoORZiNyy;
      string llpYIiwIst;
      string zctCShYGOE;
      string kllFYPEQfs;
      string JcWrcAJnep;
      string xAkiEqDluj;
      string AbytNzAjAr;
      string dfczjWFCYS;
      string XkaYGkBCBh;
      string MRVusgdcdc;
      string AZmlLRXlzh;
      if(jRVlugREpU == llpYIiwIst){kANcMOAZmb = true;}
      else if(llpYIiwIst == jRVlugREpU){HbykqpsCaB = true;}
      if(JHgELxAAxe == zctCShYGOE){yxhSfMJgGC = true;}
      else if(zctCShYGOE == JHgELxAAxe){UGBtGnbAQr = true;}
      if(VsTjTozeJB == kllFYPEQfs){rcXuSyxoMo = true;}
      else if(kllFYPEQfs == VsTjTozeJB){znjikVibPA = true;}
      if(VPpQtSjHUz == JcWrcAJnep){NPDTwLErid = true;}
      else if(JcWrcAJnep == VPpQtSjHUz){wwhVIeexVq = true;}
      if(McCxsDCzRV == xAkiEqDluj){gEoCeCqUFz = true;}
      else if(xAkiEqDluj == McCxsDCzRV){cgecSbknOY = true;}
      if(bbGLmpylRG == AbytNzAjAr){HqewoIcRKN = true;}
      else if(AbytNzAjAr == bbGLmpylRG){rqZuuSrOzV = true;}
      if(gltnytQPJr == dfczjWFCYS){QLNyOitOWU = true;}
      else if(dfczjWFCYS == gltnytQPJr){HRmZEXYelb = true;}
      if(NsfySsqVqP == XkaYGkBCBh){HQxbVnmVQP = true;}
      if(mzNmYtIddD == MRVusgdcdc){HciMgWjGdm = true;}
      if(TxoORZiNyy == AZmlLRXlzh){ilhVMUqqmu = true;}
      while(XkaYGkBCBh == NsfySsqVqP){IeeZOSJHQJ = true;}
      while(MRVusgdcdc == MRVusgdcdc){jtMpHFWmZo = true;}
      while(AZmlLRXlzh == AZmlLRXlzh){lPxziLsEXt = true;}
      if(kANcMOAZmb == true){kANcMOAZmb = false;}
      if(yxhSfMJgGC == true){yxhSfMJgGC = false;}
      if(rcXuSyxoMo == true){rcXuSyxoMo = false;}
      if(NPDTwLErid == true){NPDTwLErid = false;}
      if(gEoCeCqUFz == true){gEoCeCqUFz = false;}
      if(HqewoIcRKN == true){HqewoIcRKN = false;}
      if(QLNyOitOWU == true){QLNyOitOWU = false;}
      if(HQxbVnmVQP == true){HQxbVnmVQP = false;}
      if(HciMgWjGdm == true){HciMgWjGdm = false;}
      if(ilhVMUqqmu == true){ilhVMUqqmu = false;}
      if(HbykqpsCaB == true){HbykqpsCaB = false;}
      if(UGBtGnbAQr == true){UGBtGnbAQr = false;}
      if(znjikVibPA == true){znjikVibPA = false;}
      if(wwhVIeexVq == true){wwhVIeexVq = false;}
      if(cgecSbknOY == true){cgecSbknOY = false;}
      if(rqZuuSrOzV == true){rqZuuSrOzV = false;}
      if(HRmZEXYelb == true){HRmZEXYelb = false;}
      if(IeeZOSJHQJ == true){IeeZOSJHQJ = false;}
      if(jtMpHFWmZo == true){jtMpHFWmZo = false;}
      if(lPxziLsEXt == true){lPxziLsEXt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HCEJLYGQLK
{ 
  void OPOpnnWzkW()
  { 
      bool ENDakpYlXW = false;
      bool zHxjjeuQaG = false;
      bool XrGaaTJYBK = false;
      bool ClPdArnxtu = false;
      bool YhzzkonXLP = false;
      bool DkqtxLHbAR = false;
      bool gzjMUMqTjq = false;
      bool qxVehpsHpk = false;
      bool flNkHQtVfn = false;
      bool kLxcOZxmdX = false;
      bool xTmTYFPMMH = false;
      bool SzlOkukyED = false;
      bool RVnwGeArPH = false;
      bool rFcRnLytMC = false;
      bool BhJXUkZirS = false;
      bool nziaGbfpMt = false;
      bool FWwEPNVUaY = false;
      bool wqlCCjMPbV = false;
      bool FQAxTsWCLL = false;
      bool fIhSxdkEIG = false;
      string pCqWHyYGuR;
      string RmLOtqOfPS;
      string PzQjrqSuco;
      string brOlwbasLL;
      string AaCBFNWahE;
      string wOXZjqkHeP;
      string fccGpYYZRR;
      string QUUDRnxPed;
      string UqNXrNTnBF;
      string qTOufXxuKf;
      string oxIPmbsUHu;
      string sVbAunOFNc;
      string EkXLaxFYXt;
      string pBFyoWhxkQ;
      string TzfGMVqOzq;
      string IrhgbEZwop;
      string VUxNEqQcLY;
      string FRTwJEERzE;
      string FqYflxTXWj;
      string xkHuuyCSBV;
      if(pCqWHyYGuR == oxIPmbsUHu){ENDakpYlXW = true;}
      else if(oxIPmbsUHu == pCqWHyYGuR){xTmTYFPMMH = true;}
      if(RmLOtqOfPS == sVbAunOFNc){zHxjjeuQaG = true;}
      else if(sVbAunOFNc == RmLOtqOfPS){SzlOkukyED = true;}
      if(PzQjrqSuco == EkXLaxFYXt){XrGaaTJYBK = true;}
      else if(EkXLaxFYXt == PzQjrqSuco){RVnwGeArPH = true;}
      if(brOlwbasLL == pBFyoWhxkQ){ClPdArnxtu = true;}
      else if(pBFyoWhxkQ == brOlwbasLL){rFcRnLytMC = true;}
      if(AaCBFNWahE == TzfGMVqOzq){YhzzkonXLP = true;}
      else if(TzfGMVqOzq == AaCBFNWahE){BhJXUkZirS = true;}
      if(wOXZjqkHeP == IrhgbEZwop){DkqtxLHbAR = true;}
      else if(IrhgbEZwop == wOXZjqkHeP){nziaGbfpMt = true;}
      if(fccGpYYZRR == VUxNEqQcLY){gzjMUMqTjq = true;}
      else if(VUxNEqQcLY == fccGpYYZRR){FWwEPNVUaY = true;}
      if(QUUDRnxPed == FRTwJEERzE){qxVehpsHpk = true;}
      if(UqNXrNTnBF == FqYflxTXWj){flNkHQtVfn = true;}
      if(qTOufXxuKf == xkHuuyCSBV){kLxcOZxmdX = true;}
      while(FRTwJEERzE == QUUDRnxPed){wqlCCjMPbV = true;}
      while(FqYflxTXWj == FqYflxTXWj){FQAxTsWCLL = true;}
      while(xkHuuyCSBV == xkHuuyCSBV){fIhSxdkEIG = true;}
      if(ENDakpYlXW == true){ENDakpYlXW = false;}
      if(zHxjjeuQaG == true){zHxjjeuQaG = false;}
      if(XrGaaTJYBK == true){XrGaaTJYBK = false;}
      if(ClPdArnxtu == true){ClPdArnxtu = false;}
      if(YhzzkonXLP == true){YhzzkonXLP = false;}
      if(DkqtxLHbAR == true){DkqtxLHbAR = false;}
      if(gzjMUMqTjq == true){gzjMUMqTjq = false;}
      if(qxVehpsHpk == true){qxVehpsHpk = false;}
      if(flNkHQtVfn == true){flNkHQtVfn = false;}
      if(kLxcOZxmdX == true){kLxcOZxmdX = false;}
      if(xTmTYFPMMH == true){xTmTYFPMMH = false;}
      if(SzlOkukyED == true){SzlOkukyED = false;}
      if(RVnwGeArPH == true){RVnwGeArPH = false;}
      if(rFcRnLytMC == true){rFcRnLytMC = false;}
      if(BhJXUkZirS == true){BhJXUkZirS = false;}
      if(nziaGbfpMt == true){nziaGbfpMt = false;}
      if(FWwEPNVUaY == true){FWwEPNVUaY = false;}
      if(wqlCCjMPbV == true){wqlCCjMPbV = false;}
      if(FQAxTsWCLL == true){FQAxTsWCLL = false;}
      if(fIhSxdkEIG == true){fIhSxdkEIG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTVUKSKYAK
{ 
  void JrdDPmhDma()
  { 
      bool QkUpOkcAdN = false;
      bool kDknjobgMD = false;
      bool MEPxOmczCs = false;
      bool dQDAydhHDW = false;
      bool PMDZjtiAYP = false;
      bool NKMwwLUWba = false;
      bool HdyjiTzkpF = false;
      bool HUdomABpMT = false;
      bool EbZleTEHDl = false;
      bool IKfbOlOSpQ = false;
      bool uyKSIsfWIu = false;
      bool KeJHVeDLEO = false;
      bool OrgDwwoBaB = false;
      bool lhzwYFRHdl = false;
      bool mhyIadAYFi = false;
      bool hCObBDRGVL = false;
      bool DduHJceNhP = false;
      bool NwhSbgsYcS = false;
      bool wQurTiSXtV = false;
      bool nKkRhImqyy = false;
      string MGCofwJGyc;
      string pkDebaRWHR;
      string DiOIUySifK;
      string kzecHaIXBY;
      string pZBFnPiNVU;
      string cuVHEcqtUg;
      string dZZmqqGZXA;
      string RtUibdhJTF;
      string OFNKgpdXXd;
      string iODUuPzNOx;
      string IJoUDiZmea;
      string tgZPRXLOFA;
      string NhBsQDqAnL;
      string dUuWwFPsHy;
      string PprxiCnnCW;
      string DjHNjaHuDz;
      string rZyTxZlDSM;
      string ISHHjWoEJO;
      string PCxRHsMgmV;
      string xUoIFprYAJ;
      if(MGCofwJGyc == IJoUDiZmea){QkUpOkcAdN = true;}
      else if(IJoUDiZmea == MGCofwJGyc){uyKSIsfWIu = true;}
      if(pkDebaRWHR == tgZPRXLOFA){kDknjobgMD = true;}
      else if(tgZPRXLOFA == pkDebaRWHR){KeJHVeDLEO = true;}
      if(DiOIUySifK == NhBsQDqAnL){MEPxOmczCs = true;}
      else if(NhBsQDqAnL == DiOIUySifK){OrgDwwoBaB = true;}
      if(kzecHaIXBY == dUuWwFPsHy){dQDAydhHDW = true;}
      else if(dUuWwFPsHy == kzecHaIXBY){lhzwYFRHdl = true;}
      if(pZBFnPiNVU == PprxiCnnCW){PMDZjtiAYP = true;}
      else if(PprxiCnnCW == pZBFnPiNVU){mhyIadAYFi = true;}
      if(cuVHEcqtUg == DjHNjaHuDz){NKMwwLUWba = true;}
      else if(DjHNjaHuDz == cuVHEcqtUg){hCObBDRGVL = true;}
      if(dZZmqqGZXA == rZyTxZlDSM){HdyjiTzkpF = true;}
      else if(rZyTxZlDSM == dZZmqqGZXA){DduHJceNhP = true;}
      if(RtUibdhJTF == ISHHjWoEJO){HUdomABpMT = true;}
      if(OFNKgpdXXd == PCxRHsMgmV){EbZleTEHDl = true;}
      if(iODUuPzNOx == xUoIFprYAJ){IKfbOlOSpQ = true;}
      while(ISHHjWoEJO == RtUibdhJTF){NwhSbgsYcS = true;}
      while(PCxRHsMgmV == PCxRHsMgmV){wQurTiSXtV = true;}
      while(xUoIFprYAJ == xUoIFprYAJ){nKkRhImqyy = true;}
      if(QkUpOkcAdN == true){QkUpOkcAdN = false;}
      if(kDknjobgMD == true){kDknjobgMD = false;}
      if(MEPxOmczCs == true){MEPxOmczCs = false;}
      if(dQDAydhHDW == true){dQDAydhHDW = false;}
      if(PMDZjtiAYP == true){PMDZjtiAYP = false;}
      if(NKMwwLUWba == true){NKMwwLUWba = false;}
      if(HdyjiTzkpF == true){HdyjiTzkpF = false;}
      if(HUdomABpMT == true){HUdomABpMT = false;}
      if(EbZleTEHDl == true){EbZleTEHDl = false;}
      if(IKfbOlOSpQ == true){IKfbOlOSpQ = false;}
      if(uyKSIsfWIu == true){uyKSIsfWIu = false;}
      if(KeJHVeDLEO == true){KeJHVeDLEO = false;}
      if(OrgDwwoBaB == true){OrgDwwoBaB = false;}
      if(lhzwYFRHdl == true){lhzwYFRHdl = false;}
      if(mhyIadAYFi == true){mhyIadAYFi = false;}
      if(hCObBDRGVL == true){hCObBDRGVL = false;}
      if(DduHJceNhP == true){DduHJceNhP = false;}
      if(NwhSbgsYcS == true){NwhSbgsYcS = false;}
      if(wQurTiSXtV == true){wQurTiSXtV = false;}
      if(nKkRhImqyy == true){nKkRhImqyy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZVGAFEWUQE
{ 
  void jDYWLUrdFT()
  { 
      bool hhoRWgpiZW = false;
      bool ukexqZxPCz = false;
      bool LUCzRufAfK = false;
      bool xhRBrKnMiQ = false;
      bool LNgmJFeapX = false;
      bool cblnXNfoza = false;
      bool ApCPZNSdFf = false;
      bool lkglmxmPoM = false;
      bool PFJIgVudce = false;
      bool ezMHPVLRNw = false;
      bool lBVKlrtzAa = false;
      bool ZQAmKtfthD = false;
      bool RoAZAmXYVR = false;
      bool lVBrZOjzVo = false;
      bool aucCEOyZwV = false;
      bool oQiJewBuJz = false;
      bool TUdinEOHMw = false;
      bool KgXscVMxVl = false;
      bool nycAcUlqNc = false;
      bool MopWUFRtNz = false;
      string eSecoQNZBP;
      string eDJZUQhDNL;
      string KGyMEaJHir;
      string oOXsjbwrgS;
      string qNCbdHDlCr;
      string QEyBZXTRXO;
      string GFpIZQfPps;
      string TpWtTxEWix;
      string WXFpbkPVSL;
      string HeTRLlWtBM;
      string anuJYZgDhc;
      string SxiaqiAzfo;
      string BJwdkoWFhh;
      string aKUVVhbwRB;
      string DMnprKusac;
      string kXNMLQqRXj;
      string DbUzCIcMEI;
      string GEgdloVGlZ;
      string scdFxCxHKE;
      string qKXgyaqnnj;
      if(eSecoQNZBP == anuJYZgDhc){hhoRWgpiZW = true;}
      else if(anuJYZgDhc == eSecoQNZBP){lBVKlrtzAa = true;}
      if(eDJZUQhDNL == SxiaqiAzfo){ukexqZxPCz = true;}
      else if(SxiaqiAzfo == eDJZUQhDNL){ZQAmKtfthD = true;}
      if(KGyMEaJHir == BJwdkoWFhh){LUCzRufAfK = true;}
      else if(BJwdkoWFhh == KGyMEaJHir){RoAZAmXYVR = true;}
      if(oOXsjbwrgS == aKUVVhbwRB){xhRBrKnMiQ = true;}
      else if(aKUVVhbwRB == oOXsjbwrgS){lVBrZOjzVo = true;}
      if(qNCbdHDlCr == DMnprKusac){LNgmJFeapX = true;}
      else if(DMnprKusac == qNCbdHDlCr){aucCEOyZwV = true;}
      if(QEyBZXTRXO == kXNMLQqRXj){cblnXNfoza = true;}
      else if(kXNMLQqRXj == QEyBZXTRXO){oQiJewBuJz = true;}
      if(GFpIZQfPps == DbUzCIcMEI){ApCPZNSdFf = true;}
      else if(DbUzCIcMEI == GFpIZQfPps){TUdinEOHMw = true;}
      if(TpWtTxEWix == GEgdloVGlZ){lkglmxmPoM = true;}
      if(WXFpbkPVSL == scdFxCxHKE){PFJIgVudce = true;}
      if(HeTRLlWtBM == qKXgyaqnnj){ezMHPVLRNw = true;}
      while(GEgdloVGlZ == TpWtTxEWix){KgXscVMxVl = true;}
      while(scdFxCxHKE == scdFxCxHKE){nycAcUlqNc = true;}
      while(qKXgyaqnnj == qKXgyaqnnj){MopWUFRtNz = true;}
      if(hhoRWgpiZW == true){hhoRWgpiZW = false;}
      if(ukexqZxPCz == true){ukexqZxPCz = false;}
      if(LUCzRufAfK == true){LUCzRufAfK = false;}
      if(xhRBrKnMiQ == true){xhRBrKnMiQ = false;}
      if(LNgmJFeapX == true){LNgmJFeapX = false;}
      if(cblnXNfoza == true){cblnXNfoza = false;}
      if(ApCPZNSdFf == true){ApCPZNSdFf = false;}
      if(lkglmxmPoM == true){lkglmxmPoM = false;}
      if(PFJIgVudce == true){PFJIgVudce = false;}
      if(ezMHPVLRNw == true){ezMHPVLRNw = false;}
      if(lBVKlrtzAa == true){lBVKlrtzAa = false;}
      if(ZQAmKtfthD == true){ZQAmKtfthD = false;}
      if(RoAZAmXYVR == true){RoAZAmXYVR = false;}
      if(lVBrZOjzVo == true){lVBrZOjzVo = false;}
      if(aucCEOyZwV == true){aucCEOyZwV = false;}
      if(oQiJewBuJz == true){oQiJewBuJz = false;}
      if(TUdinEOHMw == true){TUdinEOHMw = false;}
      if(KgXscVMxVl == true){KgXscVMxVl = false;}
      if(nycAcUlqNc == true){nycAcUlqNc = false;}
      if(MopWUFRtNz == true){MopWUFRtNz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BYVDWNFVAQ
{ 
  void JQOyPQXjdP()
  { 
      bool eqdLHnOpCk = false;
      bool MtGpkRlxZW = false;
      bool LoKXHKtbpY = false;
      bool AacEoFEuPA = false;
      bool BSktzHzCgk = false;
      bool SEomiofFEx = false;
      bool tlAckkRBAf = false;
      bool MpgYVrEQYz = false;
      bool LruFFukoVz = false;
      bool YzqRGPSHIN = false;
      bool pxBBXcXPRp = false;
      bool kPgElCqtWo = false;
      bool AbfAGNzPSG = false;
      bool ZwHLJOptgc = false;
      bool XUXeOJRlfE = false;
      bool XXkSMNQAtK = false;
      bool cHxLQnHUuX = false;
      bool LwNsRfEAlw = false;
      bool uMjNhBLnyu = false;
      bool xozVzPWLOZ = false;
      string cOreSzzCAr;
      string JOtBOyFODo;
      string qtnDtSqPsF;
      string qyfzKfewSH;
      string DNXKXHNLWf;
      string FTLSphaojA;
      string HjItALitpi;
      string TIwukdVdfl;
      string EfrMzWlMJb;
      string FpLRzTEdJM;
      string YTUnLxXPgL;
      string MwIxubquuc;
      string YVkOcdwduR;
      string YrTSNkLDAC;
      string zWexOIgNVX;
      string bIifnChFKh;
      string AtUPmUcpjK;
      string PmtrdCpmzU;
      string wiHXoPJmeL;
      string CFsSCFCPKt;
      if(cOreSzzCAr == YTUnLxXPgL){eqdLHnOpCk = true;}
      else if(YTUnLxXPgL == cOreSzzCAr){pxBBXcXPRp = true;}
      if(JOtBOyFODo == MwIxubquuc){MtGpkRlxZW = true;}
      else if(MwIxubquuc == JOtBOyFODo){kPgElCqtWo = true;}
      if(qtnDtSqPsF == YVkOcdwduR){LoKXHKtbpY = true;}
      else if(YVkOcdwduR == qtnDtSqPsF){AbfAGNzPSG = true;}
      if(qyfzKfewSH == YrTSNkLDAC){AacEoFEuPA = true;}
      else if(YrTSNkLDAC == qyfzKfewSH){ZwHLJOptgc = true;}
      if(DNXKXHNLWf == zWexOIgNVX){BSktzHzCgk = true;}
      else if(zWexOIgNVX == DNXKXHNLWf){XUXeOJRlfE = true;}
      if(FTLSphaojA == bIifnChFKh){SEomiofFEx = true;}
      else if(bIifnChFKh == FTLSphaojA){XXkSMNQAtK = true;}
      if(HjItALitpi == AtUPmUcpjK){tlAckkRBAf = true;}
      else if(AtUPmUcpjK == HjItALitpi){cHxLQnHUuX = true;}
      if(TIwukdVdfl == PmtrdCpmzU){MpgYVrEQYz = true;}
      if(EfrMzWlMJb == wiHXoPJmeL){LruFFukoVz = true;}
      if(FpLRzTEdJM == CFsSCFCPKt){YzqRGPSHIN = true;}
      while(PmtrdCpmzU == TIwukdVdfl){LwNsRfEAlw = true;}
      while(wiHXoPJmeL == wiHXoPJmeL){uMjNhBLnyu = true;}
      while(CFsSCFCPKt == CFsSCFCPKt){xozVzPWLOZ = true;}
      if(eqdLHnOpCk == true){eqdLHnOpCk = false;}
      if(MtGpkRlxZW == true){MtGpkRlxZW = false;}
      if(LoKXHKtbpY == true){LoKXHKtbpY = false;}
      if(AacEoFEuPA == true){AacEoFEuPA = false;}
      if(BSktzHzCgk == true){BSktzHzCgk = false;}
      if(SEomiofFEx == true){SEomiofFEx = false;}
      if(tlAckkRBAf == true){tlAckkRBAf = false;}
      if(MpgYVrEQYz == true){MpgYVrEQYz = false;}
      if(LruFFukoVz == true){LruFFukoVz = false;}
      if(YzqRGPSHIN == true){YzqRGPSHIN = false;}
      if(pxBBXcXPRp == true){pxBBXcXPRp = false;}
      if(kPgElCqtWo == true){kPgElCqtWo = false;}
      if(AbfAGNzPSG == true){AbfAGNzPSG = false;}
      if(ZwHLJOptgc == true){ZwHLJOptgc = false;}
      if(XUXeOJRlfE == true){XUXeOJRlfE = false;}
      if(XXkSMNQAtK == true){XXkSMNQAtK = false;}
      if(cHxLQnHUuX == true){cHxLQnHUuX = false;}
      if(LwNsRfEAlw == true){LwNsRfEAlw = false;}
      if(uMjNhBLnyu == true){uMjNhBLnyu = false;}
      if(xozVzPWLOZ == true){xozVzPWLOZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSQYAQQHOL
{ 
  void fZYPkrZcxG()
  { 
      bool IWjKMjMwtE = false;
      bool iaTHEUUOam = false;
      bool oEhGfxVVgR = false;
      bool DDKZLzlUnb = false;
      bool TtwdEBUlim = false;
      bool aUMRVDnceP = false;
      bool NpObBfQswF = false;
      bool iAazSuHECd = false;
      bool bjmtqhprDH = false;
      bool KIoXOdeUbY = false;
      bool jbpdDZtNza = false;
      bool wjaBndDTkT = false;
      bool oYontZKCkn = false;
      bool PmbcsAsJpQ = false;
      bool mcscLahnjj = false;
      bool aLjIiLlBid = false;
      bool OrcKKJHxHm = false;
      bool jscTfMfLcT = false;
      bool rWRANEDTth = false;
      bool OrZMBuzhSC = false;
      string PpjLjsyDyt;
      string HQBpaUtRLt;
      string TEhlsKmpdV;
      string qGYSMFdFVi;
      string uUCTflNMUc;
      string fuqyWLIxRZ;
      string FIZcDBridU;
      string qowczzCOFH;
      string xaVAouOZwB;
      string xfnwcmuYPe;
      string sdhzlqzOzW;
      string ItrJbelYmI;
      string mSmcXKAzzL;
      string DcyaOTsVOy;
      string uzaYrDneTy;
      string AWlHrapEba;
      string pAPmTfuQtI;
      string kQJoMmqOkT;
      string WVeALgqqin;
      string cntmHujnEL;
      if(PpjLjsyDyt == sdhzlqzOzW){IWjKMjMwtE = true;}
      else if(sdhzlqzOzW == PpjLjsyDyt){jbpdDZtNza = true;}
      if(HQBpaUtRLt == ItrJbelYmI){iaTHEUUOam = true;}
      else if(ItrJbelYmI == HQBpaUtRLt){wjaBndDTkT = true;}
      if(TEhlsKmpdV == mSmcXKAzzL){oEhGfxVVgR = true;}
      else if(mSmcXKAzzL == TEhlsKmpdV){oYontZKCkn = true;}
      if(qGYSMFdFVi == DcyaOTsVOy){DDKZLzlUnb = true;}
      else if(DcyaOTsVOy == qGYSMFdFVi){PmbcsAsJpQ = true;}
      if(uUCTflNMUc == uzaYrDneTy){TtwdEBUlim = true;}
      else if(uzaYrDneTy == uUCTflNMUc){mcscLahnjj = true;}
      if(fuqyWLIxRZ == AWlHrapEba){aUMRVDnceP = true;}
      else if(AWlHrapEba == fuqyWLIxRZ){aLjIiLlBid = true;}
      if(FIZcDBridU == pAPmTfuQtI){NpObBfQswF = true;}
      else if(pAPmTfuQtI == FIZcDBridU){OrcKKJHxHm = true;}
      if(qowczzCOFH == kQJoMmqOkT){iAazSuHECd = true;}
      if(xaVAouOZwB == WVeALgqqin){bjmtqhprDH = true;}
      if(xfnwcmuYPe == cntmHujnEL){KIoXOdeUbY = true;}
      while(kQJoMmqOkT == qowczzCOFH){jscTfMfLcT = true;}
      while(WVeALgqqin == WVeALgqqin){rWRANEDTth = true;}
      while(cntmHujnEL == cntmHujnEL){OrZMBuzhSC = true;}
      if(IWjKMjMwtE == true){IWjKMjMwtE = false;}
      if(iaTHEUUOam == true){iaTHEUUOam = false;}
      if(oEhGfxVVgR == true){oEhGfxVVgR = false;}
      if(DDKZLzlUnb == true){DDKZLzlUnb = false;}
      if(TtwdEBUlim == true){TtwdEBUlim = false;}
      if(aUMRVDnceP == true){aUMRVDnceP = false;}
      if(NpObBfQswF == true){NpObBfQswF = false;}
      if(iAazSuHECd == true){iAazSuHECd = false;}
      if(bjmtqhprDH == true){bjmtqhprDH = false;}
      if(KIoXOdeUbY == true){KIoXOdeUbY = false;}
      if(jbpdDZtNza == true){jbpdDZtNza = false;}
      if(wjaBndDTkT == true){wjaBndDTkT = false;}
      if(oYontZKCkn == true){oYontZKCkn = false;}
      if(PmbcsAsJpQ == true){PmbcsAsJpQ = false;}
      if(mcscLahnjj == true){mcscLahnjj = false;}
      if(aLjIiLlBid == true){aLjIiLlBid = false;}
      if(OrcKKJHxHm == true){OrcKKJHxHm = false;}
      if(jscTfMfLcT == true){jscTfMfLcT = false;}
      if(rWRANEDTth == true){rWRANEDTth = false;}
      if(OrZMBuzhSC == true){OrZMBuzhSC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DASKBRYUFD
{ 
  void cPcSTfsRDH()
  { 
      bool BYAlsagoCh = false;
      bool yNVRywJdmr = false;
      bool fJwDSLznVQ = false;
      bool HaOOGhPsls = false;
      bool WsBnanBFWi = false;
      bool qdfHYrcxSh = false;
      bool asTlZXyHLQ = false;
      bool gPqtUlHHbe = false;
      bool JtQlYduHpN = false;
      bool ERZERdZOND = false;
      bool pttGCallll = false;
      bool jVUnYgbgMw = false;
      bool bqRxLPplbq = false;
      bool LstYoOzKjy = false;
      bool qJVDdiwkfj = false;
      bool BsCQaycwtl = false;
      bool kzJtZqbwzJ = false;
      bool gRxNFSVNTb = false;
      bool SEGqpSpcyp = false;
      bool kDQxNqzacl = false;
      string tkafjtRcNX;
      string BiKFymGZoQ;
      string NsCrKOKFMT;
      string ujNGJfLqdH;
      string eqfEugtWNg;
      string UZzMPBhiVV;
      string jLQtcRUDuS;
      string bOwglWMyxc;
      string UnqfzUjBqI;
      string xcVIXSalbd;
      string LpauEFdSas;
      string oiksAuTjuH;
      string gTMlVysnIS;
      string uZWSQeMwas;
      string pRZxTNqcHc;
      string ypqTxrcoYF;
      string MpJHxOMRbU;
      string iWIBQOsOSH;
      string HPffUEiDVY;
      string CXXUfAHSAE;
      if(tkafjtRcNX == LpauEFdSas){BYAlsagoCh = true;}
      else if(LpauEFdSas == tkafjtRcNX){pttGCallll = true;}
      if(BiKFymGZoQ == oiksAuTjuH){yNVRywJdmr = true;}
      else if(oiksAuTjuH == BiKFymGZoQ){jVUnYgbgMw = true;}
      if(NsCrKOKFMT == gTMlVysnIS){fJwDSLznVQ = true;}
      else if(gTMlVysnIS == NsCrKOKFMT){bqRxLPplbq = true;}
      if(ujNGJfLqdH == uZWSQeMwas){HaOOGhPsls = true;}
      else if(uZWSQeMwas == ujNGJfLqdH){LstYoOzKjy = true;}
      if(eqfEugtWNg == pRZxTNqcHc){WsBnanBFWi = true;}
      else if(pRZxTNqcHc == eqfEugtWNg){qJVDdiwkfj = true;}
      if(UZzMPBhiVV == ypqTxrcoYF){qdfHYrcxSh = true;}
      else if(ypqTxrcoYF == UZzMPBhiVV){BsCQaycwtl = true;}
      if(jLQtcRUDuS == MpJHxOMRbU){asTlZXyHLQ = true;}
      else if(MpJHxOMRbU == jLQtcRUDuS){kzJtZqbwzJ = true;}
      if(bOwglWMyxc == iWIBQOsOSH){gPqtUlHHbe = true;}
      if(UnqfzUjBqI == HPffUEiDVY){JtQlYduHpN = true;}
      if(xcVIXSalbd == CXXUfAHSAE){ERZERdZOND = true;}
      while(iWIBQOsOSH == bOwglWMyxc){gRxNFSVNTb = true;}
      while(HPffUEiDVY == HPffUEiDVY){SEGqpSpcyp = true;}
      while(CXXUfAHSAE == CXXUfAHSAE){kDQxNqzacl = true;}
      if(BYAlsagoCh == true){BYAlsagoCh = false;}
      if(yNVRywJdmr == true){yNVRywJdmr = false;}
      if(fJwDSLznVQ == true){fJwDSLznVQ = false;}
      if(HaOOGhPsls == true){HaOOGhPsls = false;}
      if(WsBnanBFWi == true){WsBnanBFWi = false;}
      if(qdfHYrcxSh == true){qdfHYrcxSh = false;}
      if(asTlZXyHLQ == true){asTlZXyHLQ = false;}
      if(gPqtUlHHbe == true){gPqtUlHHbe = false;}
      if(JtQlYduHpN == true){JtQlYduHpN = false;}
      if(ERZERdZOND == true){ERZERdZOND = false;}
      if(pttGCallll == true){pttGCallll = false;}
      if(jVUnYgbgMw == true){jVUnYgbgMw = false;}
      if(bqRxLPplbq == true){bqRxLPplbq = false;}
      if(LstYoOzKjy == true){LstYoOzKjy = false;}
      if(qJVDdiwkfj == true){qJVDdiwkfj = false;}
      if(BsCQaycwtl == true){BsCQaycwtl = false;}
      if(kzJtZqbwzJ == true){kzJtZqbwzJ = false;}
      if(gRxNFSVNTb == true){gRxNFSVNTb = false;}
      if(SEGqpSpcyp == true){SEGqpSpcyp = false;}
      if(kDQxNqzacl == true){kDQxNqzacl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CCFREIWZPE
{ 
  void yQNBAHnbSp()
  { 
      bool ehdVMxyXZr = false;
      bool OwMKlfhisV = false;
      bool yiXLZyPmIA = false;
      bool BfRKJAnZdW = false;
      bool ZymtMhAdSg = false;
      bool saRLbwJRuO = false;
      bool gLPYpheCBl = false;
      bool rHEWwzudyq = false;
      bool ylTaHaNGhN = false;
      bool pVeOoNiNDe = false;
      bool DxcgolVuOb = false;
      bool AfSDQurnRP = false;
      bool TXTnuVcpgi = false;
      bool QgZTnAIllU = false;
      bool FSqGMKDayt = false;
      bool VtunKedolS = false;
      bool JfOfLSFyPP = false;
      bool lFCxJBgNaj = false;
      bool SCqlMVllJJ = false;
      bool VTASLZDLts = false;
      string XZmUWcWZSU;
      string gjlUwyfQFS;
      string YsRAwoWVjs;
      string iQMWKteKmy;
      string yzATMsnlRO;
      string BctEjdImXg;
      string FAoYlPXPKB;
      string SVcHUZrxmD;
      string AkEVqFVHmf;
      string lrlGryKbhx;
      string VYaPufAmjJ;
      string kKAUfUuSgf;
      string sPcePaiWOW;
      string PQOogaJoaL;
      string EhXctarRZX;
      string CqtBDFwwzU;
      string xdYMtUwKmE;
      string KFrVbKqzjn;
      string hRwpTXWNlb;
      string eMoFNaJLhZ;
      if(XZmUWcWZSU == VYaPufAmjJ){ehdVMxyXZr = true;}
      else if(VYaPufAmjJ == XZmUWcWZSU){DxcgolVuOb = true;}
      if(gjlUwyfQFS == kKAUfUuSgf){OwMKlfhisV = true;}
      else if(kKAUfUuSgf == gjlUwyfQFS){AfSDQurnRP = true;}
      if(YsRAwoWVjs == sPcePaiWOW){yiXLZyPmIA = true;}
      else if(sPcePaiWOW == YsRAwoWVjs){TXTnuVcpgi = true;}
      if(iQMWKteKmy == PQOogaJoaL){BfRKJAnZdW = true;}
      else if(PQOogaJoaL == iQMWKteKmy){QgZTnAIllU = true;}
      if(yzATMsnlRO == EhXctarRZX){ZymtMhAdSg = true;}
      else if(EhXctarRZX == yzATMsnlRO){FSqGMKDayt = true;}
      if(BctEjdImXg == CqtBDFwwzU){saRLbwJRuO = true;}
      else if(CqtBDFwwzU == BctEjdImXg){VtunKedolS = true;}
      if(FAoYlPXPKB == xdYMtUwKmE){gLPYpheCBl = true;}
      else if(xdYMtUwKmE == FAoYlPXPKB){JfOfLSFyPP = true;}
      if(SVcHUZrxmD == KFrVbKqzjn){rHEWwzudyq = true;}
      if(AkEVqFVHmf == hRwpTXWNlb){ylTaHaNGhN = true;}
      if(lrlGryKbhx == eMoFNaJLhZ){pVeOoNiNDe = true;}
      while(KFrVbKqzjn == SVcHUZrxmD){lFCxJBgNaj = true;}
      while(hRwpTXWNlb == hRwpTXWNlb){SCqlMVllJJ = true;}
      while(eMoFNaJLhZ == eMoFNaJLhZ){VTASLZDLts = true;}
      if(ehdVMxyXZr == true){ehdVMxyXZr = false;}
      if(OwMKlfhisV == true){OwMKlfhisV = false;}
      if(yiXLZyPmIA == true){yiXLZyPmIA = false;}
      if(BfRKJAnZdW == true){BfRKJAnZdW = false;}
      if(ZymtMhAdSg == true){ZymtMhAdSg = false;}
      if(saRLbwJRuO == true){saRLbwJRuO = false;}
      if(gLPYpheCBl == true){gLPYpheCBl = false;}
      if(rHEWwzudyq == true){rHEWwzudyq = false;}
      if(ylTaHaNGhN == true){ylTaHaNGhN = false;}
      if(pVeOoNiNDe == true){pVeOoNiNDe = false;}
      if(DxcgolVuOb == true){DxcgolVuOb = false;}
      if(AfSDQurnRP == true){AfSDQurnRP = false;}
      if(TXTnuVcpgi == true){TXTnuVcpgi = false;}
      if(QgZTnAIllU == true){QgZTnAIllU = false;}
      if(FSqGMKDayt == true){FSqGMKDayt = false;}
      if(VtunKedolS == true){VtunKedolS = false;}
      if(JfOfLSFyPP == true){JfOfLSFyPP = false;}
      if(lFCxJBgNaj == true){lFCxJBgNaj = false;}
      if(SCqlMVllJJ == true){SCqlMVllJJ = false;}
      if(VTASLZDLts == true){VTASLZDLts = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NCAQACGUOA
{ 
  void LKyDncOkBZ()
  { 
      bool yifdAKsQDo = false;
      bool YDZJzLOzxQ = false;
      bool BLAOOBlEMO = false;
      bool GcezZFPYJr = false;
      bool kaCdllCQfV = false;
      bool HDwSxmhRPz = false;
      bool YnDnhuYait = false;
      bool wooEfZIWbc = false;
      bool yUYpHDfLCm = false;
      bool WyJKTwWOup = false;
      bool MbhlZRNqmW = false;
      bool eLolADPNgd = false;
      bool OMXwWxfdki = false;
      bool DtalPWmmQo = false;
      bool poYeHLIWJQ = false;
      bool gJgQazDlOc = false;
      bool liFDTkjDVc = false;
      bool PcwrnZnsnL = false;
      bool nJUUCsMJKQ = false;
      bool TAXmCGiULW = false;
      string qHQThrbJml;
      string jzuWTycFpP;
      string UokpSCDZJz;
      string XDNWqAQnZu;
      string wflbCxjqrL;
      string yhstpBVaBe;
      string nCAmOgkYeT;
      string gnftTnDInU;
      string SLgxAoKTfp;
      string dpmtGsfyNU;
      string MKMXeJCyZC;
      string yMmgMcVClY;
      string VQropqBkna;
      string HEuSHHzISp;
      string mMsdqQDFhd;
      string XcMozwRWhm;
      string IQJztsRTZE;
      string cMjukJWOxY;
      string nwCKCdrGTL;
      string obZehVCsiy;
      if(qHQThrbJml == MKMXeJCyZC){yifdAKsQDo = true;}
      else if(MKMXeJCyZC == qHQThrbJml){MbhlZRNqmW = true;}
      if(jzuWTycFpP == yMmgMcVClY){YDZJzLOzxQ = true;}
      else if(yMmgMcVClY == jzuWTycFpP){eLolADPNgd = true;}
      if(UokpSCDZJz == VQropqBkna){BLAOOBlEMO = true;}
      else if(VQropqBkna == UokpSCDZJz){OMXwWxfdki = true;}
      if(XDNWqAQnZu == HEuSHHzISp){GcezZFPYJr = true;}
      else if(HEuSHHzISp == XDNWqAQnZu){DtalPWmmQo = true;}
      if(wflbCxjqrL == mMsdqQDFhd){kaCdllCQfV = true;}
      else if(mMsdqQDFhd == wflbCxjqrL){poYeHLIWJQ = true;}
      if(yhstpBVaBe == XcMozwRWhm){HDwSxmhRPz = true;}
      else if(XcMozwRWhm == yhstpBVaBe){gJgQazDlOc = true;}
      if(nCAmOgkYeT == IQJztsRTZE){YnDnhuYait = true;}
      else if(IQJztsRTZE == nCAmOgkYeT){liFDTkjDVc = true;}
      if(gnftTnDInU == cMjukJWOxY){wooEfZIWbc = true;}
      if(SLgxAoKTfp == nwCKCdrGTL){yUYpHDfLCm = true;}
      if(dpmtGsfyNU == obZehVCsiy){WyJKTwWOup = true;}
      while(cMjukJWOxY == gnftTnDInU){PcwrnZnsnL = true;}
      while(nwCKCdrGTL == nwCKCdrGTL){nJUUCsMJKQ = true;}
      while(obZehVCsiy == obZehVCsiy){TAXmCGiULW = true;}
      if(yifdAKsQDo == true){yifdAKsQDo = false;}
      if(YDZJzLOzxQ == true){YDZJzLOzxQ = false;}
      if(BLAOOBlEMO == true){BLAOOBlEMO = false;}
      if(GcezZFPYJr == true){GcezZFPYJr = false;}
      if(kaCdllCQfV == true){kaCdllCQfV = false;}
      if(HDwSxmhRPz == true){HDwSxmhRPz = false;}
      if(YnDnhuYait == true){YnDnhuYait = false;}
      if(wooEfZIWbc == true){wooEfZIWbc = false;}
      if(yUYpHDfLCm == true){yUYpHDfLCm = false;}
      if(WyJKTwWOup == true){WyJKTwWOup = false;}
      if(MbhlZRNqmW == true){MbhlZRNqmW = false;}
      if(eLolADPNgd == true){eLolADPNgd = false;}
      if(OMXwWxfdki == true){OMXwWxfdki = false;}
      if(DtalPWmmQo == true){DtalPWmmQo = false;}
      if(poYeHLIWJQ == true){poYeHLIWJQ = false;}
      if(gJgQazDlOc == true){gJgQazDlOc = false;}
      if(liFDTkjDVc == true){liFDTkjDVc = false;}
      if(PcwrnZnsnL == true){PcwrnZnsnL = false;}
      if(nJUUCsMJKQ == true){nJUUCsMJKQ = false;}
      if(TAXmCGiULW == true){TAXmCGiULW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AIJVMXMGJU
{ 
  void hDdkbthLsf()
  { 
      bool eFXbGSxDGu = false;
      bool pOLhKhSGwV = false;
      bool uFdKmssyji = false;
      bool ayGdFcgMmV = false;
      bool YcInAYStQa = false;
      bool WBaVRYbMnM = false;
      bool ZyTXUrIhbh = false;
      bool BGTawSwpKN = false;
      bool ZyhJMYWkLf = false;
      bool BTXZwaJkSI = false;
      bool QjRhZPhAYz = false;
      bool blCambPJKu = false;
      bool UWWwggisdV = false;
      bool JLWCwpfziw = false;
      bool pWLMEPQwmU = false;
      bool LzaWmtNVBr = false;
      bool gnVDpQOAdw = false;
      bool uQZNExLKrQ = false;
      bool QlGJKJjzOC = false;
      bool cJxqPCBHVm = false;
      string VczsdObdho;
      string qYbylHlmVG;
      string yAOkrAlKNi;
      string WPUWSgJeLM;
      string XjkSzwBRJu;
      string XahxAVNNAc;
      string bRPzRaDEeE;
      string yHaIhOPwlw;
      string zUASKwhXVx;
      string SudhkFUkAX;
      string rwlExPzYOl;
      string GRbEdGRwnU;
      string sfihlCdrXc;
      string tduODCiuVu;
      string wJJjpBTYEd;
      string nXxeeMNDSt;
      string lHAkrcVNBb;
      string XVasYiVyqk;
      string iEnsnVgPip;
      string necbIoIXqN;
      if(VczsdObdho == rwlExPzYOl){eFXbGSxDGu = true;}
      else if(rwlExPzYOl == VczsdObdho){QjRhZPhAYz = true;}
      if(qYbylHlmVG == GRbEdGRwnU){pOLhKhSGwV = true;}
      else if(GRbEdGRwnU == qYbylHlmVG){blCambPJKu = true;}
      if(yAOkrAlKNi == sfihlCdrXc){uFdKmssyji = true;}
      else if(sfihlCdrXc == yAOkrAlKNi){UWWwggisdV = true;}
      if(WPUWSgJeLM == tduODCiuVu){ayGdFcgMmV = true;}
      else if(tduODCiuVu == WPUWSgJeLM){JLWCwpfziw = true;}
      if(XjkSzwBRJu == wJJjpBTYEd){YcInAYStQa = true;}
      else if(wJJjpBTYEd == XjkSzwBRJu){pWLMEPQwmU = true;}
      if(XahxAVNNAc == nXxeeMNDSt){WBaVRYbMnM = true;}
      else if(nXxeeMNDSt == XahxAVNNAc){LzaWmtNVBr = true;}
      if(bRPzRaDEeE == lHAkrcVNBb){ZyTXUrIhbh = true;}
      else if(lHAkrcVNBb == bRPzRaDEeE){gnVDpQOAdw = true;}
      if(yHaIhOPwlw == XVasYiVyqk){BGTawSwpKN = true;}
      if(zUASKwhXVx == iEnsnVgPip){ZyhJMYWkLf = true;}
      if(SudhkFUkAX == necbIoIXqN){BTXZwaJkSI = true;}
      while(XVasYiVyqk == yHaIhOPwlw){uQZNExLKrQ = true;}
      while(iEnsnVgPip == iEnsnVgPip){QlGJKJjzOC = true;}
      while(necbIoIXqN == necbIoIXqN){cJxqPCBHVm = true;}
      if(eFXbGSxDGu == true){eFXbGSxDGu = false;}
      if(pOLhKhSGwV == true){pOLhKhSGwV = false;}
      if(uFdKmssyji == true){uFdKmssyji = false;}
      if(ayGdFcgMmV == true){ayGdFcgMmV = false;}
      if(YcInAYStQa == true){YcInAYStQa = false;}
      if(WBaVRYbMnM == true){WBaVRYbMnM = false;}
      if(ZyTXUrIhbh == true){ZyTXUrIhbh = false;}
      if(BGTawSwpKN == true){BGTawSwpKN = false;}
      if(ZyhJMYWkLf == true){ZyhJMYWkLf = false;}
      if(BTXZwaJkSI == true){BTXZwaJkSI = false;}
      if(QjRhZPhAYz == true){QjRhZPhAYz = false;}
      if(blCambPJKu == true){blCambPJKu = false;}
      if(UWWwggisdV == true){UWWwggisdV = false;}
      if(JLWCwpfziw == true){JLWCwpfziw = false;}
      if(pWLMEPQwmU == true){pWLMEPQwmU = false;}
      if(LzaWmtNVBr == true){LzaWmtNVBr = false;}
      if(gnVDpQOAdw == true){gnVDpQOAdw = false;}
      if(uQZNExLKrQ == true){uQZNExLKrQ = false;}
      if(QlGJKJjzOC == true){QlGJKJjzOC = false;}
      if(cJxqPCBHVm == true){cJxqPCBHVm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBGXLQFWYJ
{ 
  void tusjnKELXD()
  { 
      bool ziwfXbaUFZ = false;
      bool zfPMXzuqIr = false;
      bool eeHQjKNpPk = false;
      bool HnsakphkFZ = false;
      bool YzBYyfyTku = false;
      bool RizsyUbfwM = false;
      bool OjFTRLmobh = false;
      bool QKkhTediRD = false;
      bool MsFTTYoAcP = false;
      bool OCnrKnthHm = false;
      bool sJqCdGxQZS = false;
      bool prOrAUelAr = false;
      bool WmLLTOVsXe = false;
      bool kwbdJDCCoM = false;
      bool bXZKZVmwrp = false;
      bool IIgOQGxfiO = false;
      bool kEstgtQjhw = false;
      bool ScwmQyMBly = false;
      bool aZAgWcOMND = false;
      bool GWTZaWefce = false;
      string USBbcsoUwn;
      string jKYFcVezca;
      string NGdxUQAVuT;
      string fQxUsXFXIx;
      string LGqmFUYOYb;
      string axZxYOnEGL;
      string sTZcITMEMF;
      string PGpePHOpqA;
      string rkwSshpzud;
      string iBQwErgOek;
      string HTCTLTGuhR;
      string AxMGTHWGiZ;
      string cNIhVOotZX;
      string ZALGrXhcGY;
      string auRddloKcw;
      string VaeEHtLUxx;
      string dMUKrAlFNw;
      string YszKzhueEj;
      string YeQcBzUGyx;
      string MNfJuNZHlc;
      if(USBbcsoUwn == HTCTLTGuhR){ziwfXbaUFZ = true;}
      else if(HTCTLTGuhR == USBbcsoUwn){sJqCdGxQZS = true;}
      if(jKYFcVezca == AxMGTHWGiZ){zfPMXzuqIr = true;}
      else if(AxMGTHWGiZ == jKYFcVezca){prOrAUelAr = true;}
      if(NGdxUQAVuT == cNIhVOotZX){eeHQjKNpPk = true;}
      else if(cNIhVOotZX == NGdxUQAVuT){WmLLTOVsXe = true;}
      if(fQxUsXFXIx == ZALGrXhcGY){HnsakphkFZ = true;}
      else if(ZALGrXhcGY == fQxUsXFXIx){kwbdJDCCoM = true;}
      if(LGqmFUYOYb == auRddloKcw){YzBYyfyTku = true;}
      else if(auRddloKcw == LGqmFUYOYb){bXZKZVmwrp = true;}
      if(axZxYOnEGL == VaeEHtLUxx){RizsyUbfwM = true;}
      else if(VaeEHtLUxx == axZxYOnEGL){IIgOQGxfiO = true;}
      if(sTZcITMEMF == dMUKrAlFNw){OjFTRLmobh = true;}
      else if(dMUKrAlFNw == sTZcITMEMF){kEstgtQjhw = true;}
      if(PGpePHOpqA == YszKzhueEj){QKkhTediRD = true;}
      if(rkwSshpzud == YeQcBzUGyx){MsFTTYoAcP = true;}
      if(iBQwErgOek == MNfJuNZHlc){OCnrKnthHm = true;}
      while(YszKzhueEj == PGpePHOpqA){ScwmQyMBly = true;}
      while(YeQcBzUGyx == YeQcBzUGyx){aZAgWcOMND = true;}
      while(MNfJuNZHlc == MNfJuNZHlc){GWTZaWefce = true;}
      if(ziwfXbaUFZ == true){ziwfXbaUFZ = false;}
      if(zfPMXzuqIr == true){zfPMXzuqIr = false;}
      if(eeHQjKNpPk == true){eeHQjKNpPk = false;}
      if(HnsakphkFZ == true){HnsakphkFZ = false;}
      if(YzBYyfyTku == true){YzBYyfyTku = false;}
      if(RizsyUbfwM == true){RizsyUbfwM = false;}
      if(OjFTRLmobh == true){OjFTRLmobh = false;}
      if(QKkhTediRD == true){QKkhTediRD = false;}
      if(MsFTTYoAcP == true){MsFTTYoAcP = false;}
      if(OCnrKnthHm == true){OCnrKnthHm = false;}
      if(sJqCdGxQZS == true){sJqCdGxQZS = false;}
      if(prOrAUelAr == true){prOrAUelAr = false;}
      if(WmLLTOVsXe == true){WmLLTOVsXe = false;}
      if(kwbdJDCCoM == true){kwbdJDCCoM = false;}
      if(bXZKZVmwrp == true){bXZKZVmwrp = false;}
      if(IIgOQGxfiO == true){IIgOQGxfiO = false;}
      if(kEstgtQjhw == true){kEstgtQjhw = false;}
      if(ScwmQyMBly == true){ScwmQyMBly = false;}
      if(aZAgWcOMND == true){aZAgWcOMND = false;}
      if(GWTZaWefce == true){GWTZaWefce = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JWSTFGOKVR
{ 
  void xJUchKPdKO()
  { 
      bool ckddqJHXYs = false;
      bool VAuyQKZtjM = false;
      bool DpPlDYBsOL = false;
      bool tTKPBdiNau = false;
      bool MTlXTNwEtH = false;
      bool SjsftlUqZS = false;
      bool HOJNyCpexm = false;
      bool aMSoAjEqRp = false;
      bool bxzGrKZdVO = false;
      bool IrmImyJYZR = false;
      bool WQGHgGQEfJ = false;
      bool hdZjpJOCUn = false;
      bool bLJidiYJBC = false;
      bool aeRASLqrYl = false;
      bool sUyMfeRCSc = false;
      bool iGEkoKHXcy = false;
      bool gHCdiDMYRe = false;
      bool SVdiuHNxCz = false;
      bool QWqXSTafKH = false;
      bool ESPZElSUcc = false;
      string YabIoUjXxK;
      string MANxabogMS;
      string qHCtaEhibp;
      string hRFsCuOaPM;
      string ADiUcfDNRZ;
      string HUmbDQYggk;
      string mBwGbttUtf;
      string NOQzSnYgRu;
      string BURCiNdcpl;
      string VgseZyGbrh;
      string kiSlLsDmJO;
      string rqPljSjtWO;
      string QRdIJfUlZT;
      string gwoiJSCepp;
      string JqTateRGuH;
      string OMEdRTEKce;
      string XQMohuCgcR;
      string QEEgEYxDOd;
      string ONqSFUqLQp;
      string NqCKRsddsy;
      if(YabIoUjXxK == kiSlLsDmJO){ckddqJHXYs = true;}
      else if(kiSlLsDmJO == YabIoUjXxK){WQGHgGQEfJ = true;}
      if(MANxabogMS == rqPljSjtWO){VAuyQKZtjM = true;}
      else if(rqPljSjtWO == MANxabogMS){hdZjpJOCUn = true;}
      if(qHCtaEhibp == QRdIJfUlZT){DpPlDYBsOL = true;}
      else if(QRdIJfUlZT == qHCtaEhibp){bLJidiYJBC = true;}
      if(hRFsCuOaPM == gwoiJSCepp){tTKPBdiNau = true;}
      else if(gwoiJSCepp == hRFsCuOaPM){aeRASLqrYl = true;}
      if(ADiUcfDNRZ == JqTateRGuH){MTlXTNwEtH = true;}
      else if(JqTateRGuH == ADiUcfDNRZ){sUyMfeRCSc = true;}
      if(HUmbDQYggk == OMEdRTEKce){SjsftlUqZS = true;}
      else if(OMEdRTEKce == HUmbDQYggk){iGEkoKHXcy = true;}
      if(mBwGbttUtf == XQMohuCgcR){HOJNyCpexm = true;}
      else if(XQMohuCgcR == mBwGbttUtf){gHCdiDMYRe = true;}
      if(NOQzSnYgRu == QEEgEYxDOd){aMSoAjEqRp = true;}
      if(BURCiNdcpl == ONqSFUqLQp){bxzGrKZdVO = true;}
      if(VgseZyGbrh == NqCKRsddsy){IrmImyJYZR = true;}
      while(QEEgEYxDOd == NOQzSnYgRu){SVdiuHNxCz = true;}
      while(ONqSFUqLQp == ONqSFUqLQp){QWqXSTafKH = true;}
      while(NqCKRsddsy == NqCKRsddsy){ESPZElSUcc = true;}
      if(ckddqJHXYs == true){ckddqJHXYs = false;}
      if(VAuyQKZtjM == true){VAuyQKZtjM = false;}
      if(DpPlDYBsOL == true){DpPlDYBsOL = false;}
      if(tTKPBdiNau == true){tTKPBdiNau = false;}
      if(MTlXTNwEtH == true){MTlXTNwEtH = false;}
      if(SjsftlUqZS == true){SjsftlUqZS = false;}
      if(HOJNyCpexm == true){HOJNyCpexm = false;}
      if(aMSoAjEqRp == true){aMSoAjEqRp = false;}
      if(bxzGrKZdVO == true){bxzGrKZdVO = false;}
      if(IrmImyJYZR == true){IrmImyJYZR = false;}
      if(WQGHgGQEfJ == true){WQGHgGQEfJ = false;}
      if(hdZjpJOCUn == true){hdZjpJOCUn = false;}
      if(bLJidiYJBC == true){bLJidiYJBC = false;}
      if(aeRASLqrYl == true){aeRASLqrYl = false;}
      if(sUyMfeRCSc == true){sUyMfeRCSc = false;}
      if(iGEkoKHXcy == true){iGEkoKHXcy = false;}
      if(gHCdiDMYRe == true){gHCdiDMYRe = false;}
      if(SVdiuHNxCz == true){SVdiuHNxCz = false;}
      if(QWqXSTafKH == true){QWqXSTafKH = false;}
      if(ESPZElSUcc == true){ESPZElSUcc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FYKXCQVCRA
{ 
  void bpVYAOYkEL()
  { 
      bool rfVdwnjxDa = false;
      bool fMHxkZGbKm = false;
      bool KCNFcZQuBd = false;
      bool fNcSEOeVdq = false;
      bool rpiVFrJdZC = false;
      bool UyPyepSPAW = false;
      bool WouYtRiosW = false;
      bool tjxStTTqAk = false;
      bool QmVyJhxemO = false;
      bool wPVHUDuJbm = false;
      bool ITjDIjBxDL = false;
      bool VaPOFiTwPM = false;
      bool TDCdZdOoyq = false;
      bool YKPMcxCRpZ = false;
      bool gAabsVAHCk = false;
      bool iytOTEQGcd = false;
      bool VLyMlKKClI = false;
      bool gBGoeScakE = false;
      bool dHmNHaQAsX = false;
      bool fwoLEUCOoh = false;
      string pQVPCbpBgx;
      string RHglCbSyJW;
      string JFjniQHarH;
      string GngfmCMsLg;
      string MyhntBsMbh;
      string OFsNtkghgl;
      string TOIYpdZBzA;
      string PZlbKKXuth;
      string XuyJrBtTkC;
      string UdLZMxpIyQ;
      string aqNaRoSRDj;
      string NlnyNYPygn;
      string iFPwfkOLOM;
      string TOwdGfhWrD;
      string hcQBnhpNLn;
      string gqaJgUbQuf;
      string aGCpPyoKqh;
      string qsGdFGoOIx;
      string uAAafcnlwl;
      string EQbLbaZakp;
      if(pQVPCbpBgx == aqNaRoSRDj){rfVdwnjxDa = true;}
      else if(aqNaRoSRDj == pQVPCbpBgx){ITjDIjBxDL = true;}
      if(RHglCbSyJW == NlnyNYPygn){fMHxkZGbKm = true;}
      else if(NlnyNYPygn == RHglCbSyJW){VaPOFiTwPM = true;}
      if(JFjniQHarH == iFPwfkOLOM){KCNFcZQuBd = true;}
      else if(iFPwfkOLOM == JFjniQHarH){TDCdZdOoyq = true;}
      if(GngfmCMsLg == TOwdGfhWrD){fNcSEOeVdq = true;}
      else if(TOwdGfhWrD == GngfmCMsLg){YKPMcxCRpZ = true;}
      if(MyhntBsMbh == hcQBnhpNLn){rpiVFrJdZC = true;}
      else if(hcQBnhpNLn == MyhntBsMbh){gAabsVAHCk = true;}
      if(OFsNtkghgl == gqaJgUbQuf){UyPyepSPAW = true;}
      else if(gqaJgUbQuf == OFsNtkghgl){iytOTEQGcd = true;}
      if(TOIYpdZBzA == aGCpPyoKqh){WouYtRiosW = true;}
      else if(aGCpPyoKqh == TOIYpdZBzA){VLyMlKKClI = true;}
      if(PZlbKKXuth == qsGdFGoOIx){tjxStTTqAk = true;}
      if(XuyJrBtTkC == uAAafcnlwl){QmVyJhxemO = true;}
      if(UdLZMxpIyQ == EQbLbaZakp){wPVHUDuJbm = true;}
      while(qsGdFGoOIx == PZlbKKXuth){gBGoeScakE = true;}
      while(uAAafcnlwl == uAAafcnlwl){dHmNHaQAsX = true;}
      while(EQbLbaZakp == EQbLbaZakp){fwoLEUCOoh = true;}
      if(rfVdwnjxDa == true){rfVdwnjxDa = false;}
      if(fMHxkZGbKm == true){fMHxkZGbKm = false;}
      if(KCNFcZQuBd == true){KCNFcZQuBd = false;}
      if(fNcSEOeVdq == true){fNcSEOeVdq = false;}
      if(rpiVFrJdZC == true){rpiVFrJdZC = false;}
      if(UyPyepSPAW == true){UyPyepSPAW = false;}
      if(WouYtRiosW == true){WouYtRiosW = false;}
      if(tjxStTTqAk == true){tjxStTTqAk = false;}
      if(QmVyJhxemO == true){QmVyJhxemO = false;}
      if(wPVHUDuJbm == true){wPVHUDuJbm = false;}
      if(ITjDIjBxDL == true){ITjDIjBxDL = false;}
      if(VaPOFiTwPM == true){VaPOFiTwPM = false;}
      if(TDCdZdOoyq == true){TDCdZdOoyq = false;}
      if(YKPMcxCRpZ == true){YKPMcxCRpZ = false;}
      if(gAabsVAHCk == true){gAabsVAHCk = false;}
      if(iytOTEQGcd == true){iytOTEQGcd = false;}
      if(VLyMlKKClI == true){VLyMlKKClI = false;}
      if(gBGoeScakE == true){gBGoeScakE = false;}
      if(dHmNHaQAsX == true){dHmNHaQAsX = false;}
      if(fwoLEUCOoh == true){fwoLEUCOoh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GBAEUAYNMR
{ 
  void OaJCsJnqQV()
  { 
      bool UWMZchTNuj = false;
      bool RRosfSZLZi = false;
      bool afAlRbpGHc = false;
      bool OLBmggDShl = false;
      bool IZCTXPOaJM = false;
      bool DNyUYoWZIA = false;
      bool qMFSVGQBLy = false;
      bool OGcmaAdgNC = false;
      bool NOxuYANfOr = false;
      bool KdKhtuUjyR = false;
      bool zMPLxwkKtX = false;
      bool KoLGmcPKsU = false;
      bool skmTnkuuse = false;
      bool fshwCAzkxc = false;
      bool PCkpgUREtR = false;
      bool eJpdXOYwWM = false;
      bool AoRPrRHODl = false;
      bool cdNQEpzxlT = false;
      bool TpAazVCEYn = false;
      bool bDOjbZkVxP = false;
      string fnAGqomMDR;
      string AyCbAcrmps;
      string goBbllNxzC;
      string bZSJHRjdly;
      string KABulllAhJ;
      string BojpmplXUF;
      string apMBoafrTi;
      string rNBrhgnGoz;
      string zNOpBlobWR;
      string fLJgWUmAFL;
      string GsfyQmnrIF;
      string CeiUFNaVAD;
      string lDVCDgEUUN;
      string smAdsFgPZN;
      string xxTQOAcnaJ;
      string sQzBYCXcuj;
      string iTWtLOeFbA;
      string fKwlGojFnC;
      string EPsLUcmyEp;
      string hEUoecZYEA;
      if(fnAGqomMDR == GsfyQmnrIF){UWMZchTNuj = true;}
      else if(GsfyQmnrIF == fnAGqomMDR){zMPLxwkKtX = true;}
      if(AyCbAcrmps == CeiUFNaVAD){RRosfSZLZi = true;}
      else if(CeiUFNaVAD == AyCbAcrmps){KoLGmcPKsU = true;}
      if(goBbllNxzC == lDVCDgEUUN){afAlRbpGHc = true;}
      else if(lDVCDgEUUN == goBbllNxzC){skmTnkuuse = true;}
      if(bZSJHRjdly == smAdsFgPZN){OLBmggDShl = true;}
      else if(smAdsFgPZN == bZSJHRjdly){fshwCAzkxc = true;}
      if(KABulllAhJ == xxTQOAcnaJ){IZCTXPOaJM = true;}
      else if(xxTQOAcnaJ == KABulllAhJ){PCkpgUREtR = true;}
      if(BojpmplXUF == sQzBYCXcuj){DNyUYoWZIA = true;}
      else if(sQzBYCXcuj == BojpmplXUF){eJpdXOYwWM = true;}
      if(apMBoafrTi == iTWtLOeFbA){qMFSVGQBLy = true;}
      else if(iTWtLOeFbA == apMBoafrTi){AoRPrRHODl = true;}
      if(rNBrhgnGoz == fKwlGojFnC){OGcmaAdgNC = true;}
      if(zNOpBlobWR == EPsLUcmyEp){NOxuYANfOr = true;}
      if(fLJgWUmAFL == hEUoecZYEA){KdKhtuUjyR = true;}
      while(fKwlGojFnC == rNBrhgnGoz){cdNQEpzxlT = true;}
      while(EPsLUcmyEp == EPsLUcmyEp){TpAazVCEYn = true;}
      while(hEUoecZYEA == hEUoecZYEA){bDOjbZkVxP = true;}
      if(UWMZchTNuj == true){UWMZchTNuj = false;}
      if(RRosfSZLZi == true){RRosfSZLZi = false;}
      if(afAlRbpGHc == true){afAlRbpGHc = false;}
      if(OLBmggDShl == true){OLBmggDShl = false;}
      if(IZCTXPOaJM == true){IZCTXPOaJM = false;}
      if(DNyUYoWZIA == true){DNyUYoWZIA = false;}
      if(qMFSVGQBLy == true){qMFSVGQBLy = false;}
      if(OGcmaAdgNC == true){OGcmaAdgNC = false;}
      if(NOxuYANfOr == true){NOxuYANfOr = false;}
      if(KdKhtuUjyR == true){KdKhtuUjyR = false;}
      if(zMPLxwkKtX == true){zMPLxwkKtX = false;}
      if(KoLGmcPKsU == true){KoLGmcPKsU = false;}
      if(skmTnkuuse == true){skmTnkuuse = false;}
      if(fshwCAzkxc == true){fshwCAzkxc = false;}
      if(PCkpgUREtR == true){PCkpgUREtR = false;}
      if(eJpdXOYwWM == true){eJpdXOYwWM = false;}
      if(AoRPrRHODl == true){AoRPrRHODl = false;}
      if(cdNQEpzxlT == true){cdNQEpzxlT = false;}
      if(TpAazVCEYn == true){TpAazVCEYn = false;}
      if(bDOjbZkVxP == true){bDOjbZkVxP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PNTHPOMRVH
{ 
  void TjLjTIUwkB()
  { 
      bool zsPhdFsNlU = false;
      bool krAjPeFSpd = false;
      bool SOHFEdoxXe = false;
      bool QyymzBbTWD = false;
      bool wbLKsaCIWa = false;
      bool uNaAIkkJdz = false;
      bool PupGDltMjO = false;
      bool DlulgqDxLc = false;
      bool bgawiDXxdN = false;
      bool PRpWnAlEGH = false;
      bool goXHWJRoSR = false;
      bool hnxAXiUsXA = false;
      bool NwiVzkuXyf = false;
      bool EypEwlISZZ = false;
      bool kieLfbTpzE = false;
      bool fsgFskGBHk = false;
      bool OsplMixsDk = false;
      bool ZBSxPeQWpX = false;
      bool QFYsALRkKK = false;
      bool fHKnKqrszx = false;
      string owyWlMyXGY;
      string KtMTtGBjWR;
      string AVtBrqbSJK;
      string LiAAsrOuLy;
      string aXrUocHqwb;
      string TmEmPSCxet;
      string keOwMatMaB;
      string qGYYqccYLO;
      string ijVgpXeMkZ;
      string pQPQMuJwIO;
      string iuQujNOfum;
      string ockPLBIgFo;
      string wgaALZqHMw;
      string SfQxfmTaxc;
      string IzQykMfzFL;
      string lcqSRBUPiK;
      string WHSzTIMmjX;
      string hgjcfxQbPz;
      string tqBAJpoxfe;
      string SDrmFBfRdb;
      if(owyWlMyXGY == iuQujNOfum){zsPhdFsNlU = true;}
      else if(iuQujNOfum == owyWlMyXGY){goXHWJRoSR = true;}
      if(KtMTtGBjWR == ockPLBIgFo){krAjPeFSpd = true;}
      else if(ockPLBIgFo == KtMTtGBjWR){hnxAXiUsXA = true;}
      if(AVtBrqbSJK == wgaALZqHMw){SOHFEdoxXe = true;}
      else if(wgaALZqHMw == AVtBrqbSJK){NwiVzkuXyf = true;}
      if(LiAAsrOuLy == SfQxfmTaxc){QyymzBbTWD = true;}
      else if(SfQxfmTaxc == LiAAsrOuLy){EypEwlISZZ = true;}
      if(aXrUocHqwb == IzQykMfzFL){wbLKsaCIWa = true;}
      else if(IzQykMfzFL == aXrUocHqwb){kieLfbTpzE = true;}
      if(TmEmPSCxet == lcqSRBUPiK){uNaAIkkJdz = true;}
      else if(lcqSRBUPiK == TmEmPSCxet){fsgFskGBHk = true;}
      if(keOwMatMaB == WHSzTIMmjX){PupGDltMjO = true;}
      else if(WHSzTIMmjX == keOwMatMaB){OsplMixsDk = true;}
      if(qGYYqccYLO == hgjcfxQbPz){DlulgqDxLc = true;}
      if(ijVgpXeMkZ == tqBAJpoxfe){bgawiDXxdN = true;}
      if(pQPQMuJwIO == SDrmFBfRdb){PRpWnAlEGH = true;}
      while(hgjcfxQbPz == qGYYqccYLO){ZBSxPeQWpX = true;}
      while(tqBAJpoxfe == tqBAJpoxfe){QFYsALRkKK = true;}
      while(SDrmFBfRdb == SDrmFBfRdb){fHKnKqrszx = true;}
      if(zsPhdFsNlU == true){zsPhdFsNlU = false;}
      if(krAjPeFSpd == true){krAjPeFSpd = false;}
      if(SOHFEdoxXe == true){SOHFEdoxXe = false;}
      if(QyymzBbTWD == true){QyymzBbTWD = false;}
      if(wbLKsaCIWa == true){wbLKsaCIWa = false;}
      if(uNaAIkkJdz == true){uNaAIkkJdz = false;}
      if(PupGDltMjO == true){PupGDltMjO = false;}
      if(DlulgqDxLc == true){DlulgqDxLc = false;}
      if(bgawiDXxdN == true){bgawiDXxdN = false;}
      if(PRpWnAlEGH == true){PRpWnAlEGH = false;}
      if(goXHWJRoSR == true){goXHWJRoSR = false;}
      if(hnxAXiUsXA == true){hnxAXiUsXA = false;}
      if(NwiVzkuXyf == true){NwiVzkuXyf = false;}
      if(EypEwlISZZ == true){EypEwlISZZ = false;}
      if(kieLfbTpzE == true){kieLfbTpzE = false;}
      if(fsgFskGBHk == true){fsgFskGBHk = false;}
      if(OsplMixsDk == true){OsplMixsDk = false;}
      if(ZBSxPeQWpX == true){ZBSxPeQWpX = false;}
      if(QFYsALRkKK == true){QFYsALRkKK = false;}
      if(fHKnKqrszx == true){fHKnKqrszx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CMDLHFSVHH
{ 
  void mHekeYXKlT()
  { 
      bool PmapJClmrC = false;
      bool bREPiefOPO = false;
      bool mMaPIUCXmg = false;
      bool smfJTjEFbE = false;
      bool BIXVIQXkQc = false;
      bool SLMSWCLKgo = false;
      bool AOzKJnluwy = false;
      bool ZZlKMenFGr = false;
      bool wRGJOgZMmQ = false;
      bool YsYmEmINLU = false;
      bool ecnSCsZCGr = false;
      bool NGDoriHowb = false;
      bool OYIfZgByGZ = false;
      bool VaslNTcnHV = false;
      bool HXGtCRoiuV = false;
      bool eTQiGFUIsV = false;
      bool qaugVmMRbX = false;
      bool GThaUpRNcH = false;
      bool qRDktBKJfH = false;
      bool yTukdgbYXP = false;
      string UpsDOkNkaE;
      string gtQUhdhLwM;
      string idAopMxihW;
      string KRteyylSqt;
      string nsBbeHRJJJ;
      string iawJqpoEMC;
      string ndDDsOAlVi;
      string rOTBYobXKi;
      string unZYnjVjmH;
      string IgFoGKpyiP;
      string GemZRTHtkC;
      string NRtdHzDePJ;
      string sPzNaKIdtN;
      string zdotbPBAGT;
      string bazktqmbhH;
      string GKhYVqfYzG;
      string LcAWDibzBr;
      string xDXugSPNTi;
      string XfwlHnuPYk;
      string icBAIzZchK;
      if(UpsDOkNkaE == GemZRTHtkC){PmapJClmrC = true;}
      else if(GemZRTHtkC == UpsDOkNkaE){ecnSCsZCGr = true;}
      if(gtQUhdhLwM == NRtdHzDePJ){bREPiefOPO = true;}
      else if(NRtdHzDePJ == gtQUhdhLwM){NGDoriHowb = true;}
      if(idAopMxihW == sPzNaKIdtN){mMaPIUCXmg = true;}
      else if(sPzNaKIdtN == idAopMxihW){OYIfZgByGZ = true;}
      if(KRteyylSqt == zdotbPBAGT){smfJTjEFbE = true;}
      else if(zdotbPBAGT == KRteyylSqt){VaslNTcnHV = true;}
      if(nsBbeHRJJJ == bazktqmbhH){BIXVIQXkQc = true;}
      else if(bazktqmbhH == nsBbeHRJJJ){HXGtCRoiuV = true;}
      if(iawJqpoEMC == GKhYVqfYzG){SLMSWCLKgo = true;}
      else if(GKhYVqfYzG == iawJqpoEMC){eTQiGFUIsV = true;}
      if(ndDDsOAlVi == LcAWDibzBr){AOzKJnluwy = true;}
      else if(LcAWDibzBr == ndDDsOAlVi){qaugVmMRbX = true;}
      if(rOTBYobXKi == xDXugSPNTi){ZZlKMenFGr = true;}
      if(unZYnjVjmH == XfwlHnuPYk){wRGJOgZMmQ = true;}
      if(IgFoGKpyiP == icBAIzZchK){YsYmEmINLU = true;}
      while(xDXugSPNTi == rOTBYobXKi){GThaUpRNcH = true;}
      while(XfwlHnuPYk == XfwlHnuPYk){qRDktBKJfH = true;}
      while(icBAIzZchK == icBAIzZchK){yTukdgbYXP = true;}
      if(PmapJClmrC == true){PmapJClmrC = false;}
      if(bREPiefOPO == true){bREPiefOPO = false;}
      if(mMaPIUCXmg == true){mMaPIUCXmg = false;}
      if(smfJTjEFbE == true){smfJTjEFbE = false;}
      if(BIXVIQXkQc == true){BIXVIQXkQc = false;}
      if(SLMSWCLKgo == true){SLMSWCLKgo = false;}
      if(AOzKJnluwy == true){AOzKJnluwy = false;}
      if(ZZlKMenFGr == true){ZZlKMenFGr = false;}
      if(wRGJOgZMmQ == true){wRGJOgZMmQ = false;}
      if(YsYmEmINLU == true){YsYmEmINLU = false;}
      if(ecnSCsZCGr == true){ecnSCsZCGr = false;}
      if(NGDoriHowb == true){NGDoriHowb = false;}
      if(OYIfZgByGZ == true){OYIfZgByGZ = false;}
      if(VaslNTcnHV == true){VaslNTcnHV = false;}
      if(HXGtCRoiuV == true){HXGtCRoiuV = false;}
      if(eTQiGFUIsV == true){eTQiGFUIsV = false;}
      if(qaugVmMRbX == true){qaugVmMRbX = false;}
      if(GThaUpRNcH == true){GThaUpRNcH = false;}
      if(qRDktBKJfH == true){qRDktBKJfH = false;}
      if(yTukdgbYXP == true){yTukdgbYXP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DAJLVIDGZW
{ 
  void ZLAJaDBaXH()
  { 
      bool LtKNjYWbDL = false;
      bool bKlxQfPVOW = false;
      bool iboCKxAJlN = false;
      bool FMBEtzngpf = false;
      bool QVjniYuSbz = false;
      bool fRqICjEICl = false;
      bool XMppFPIhCQ = false;
      bool qifhFMrBSk = false;
      bool BghmgmVrBK = false;
      bool ufeDIDfshT = false;
      bool QNQKHxlJCp = false;
      bool qDoQjpeCIR = false;
      bool sPfqVLDbZB = false;
      bool fySzUnQWfj = false;
      bool BMoLSqpNSR = false;
      bool YdkPZAgYnw = false;
      bool sKiBJsjouw = false;
      bool ZIWYQgaUXe = false;
      bool UpIIcCNCZU = false;
      bool GrhiqpcnBZ = false;
      string HpthHQUlRz;
      string yFNgTNYajq;
      string TUsPRsgand;
      string OAXbepHIso;
      string VcIOdVBlRu;
      string RufjNlweQO;
      string jtymjxglBd;
      string GPhuVpMeku;
      string qtIrMTUnNr;
      string tcreFadUdg;
      string oPknoCNkNW;
      string ZRsUWolFaQ;
      string bsXIidWCpt;
      string MrBEGbJUDJ;
      string GiZpSbiXIP;
      string oYsNEurbEK;
      string eKuTKgPoNt;
      string fQBQJsSgoG;
      string tztZEnynzL;
      string jhQrewmGfk;
      if(HpthHQUlRz == oPknoCNkNW){LtKNjYWbDL = true;}
      else if(oPknoCNkNW == HpthHQUlRz){QNQKHxlJCp = true;}
      if(yFNgTNYajq == ZRsUWolFaQ){bKlxQfPVOW = true;}
      else if(ZRsUWolFaQ == yFNgTNYajq){qDoQjpeCIR = true;}
      if(TUsPRsgand == bsXIidWCpt){iboCKxAJlN = true;}
      else if(bsXIidWCpt == TUsPRsgand){sPfqVLDbZB = true;}
      if(OAXbepHIso == MrBEGbJUDJ){FMBEtzngpf = true;}
      else if(MrBEGbJUDJ == OAXbepHIso){fySzUnQWfj = true;}
      if(VcIOdVBlRu == GiZpSbiXIP){QVjniYuSbz = true;}
      else if(GiZpSbiXIP == VcIOdVBlRu){BMoLSqpNSR = true;}
      if(RufjNlweQO == oYsNEurbEK){fRqICjEICl = true;}
      else if(oYsNEurbEK == RufjNlweQO){YdkPZAgYnw = true;}
      if(jtymjxglBd == eKuTKgPoNt){XMppFPIhCQ = true;}
      else if(eKuTKgPoNt == jtymjxglBd){sKiBJsjouw = true;}
      if(GPhuVpMeku == fQBQJsSgoG){qifhFMrBSk = true;}
      if(qtIrMTUnNr == tztZEnynzL){BghmgmVrBK = true;}
      if(tcreFadUdg == jhQrewmGfk){ufeDIDfshT = true;}
      while(fQBQJsSgoG == GPhuVpMeku){ZIWYQgaUXe = true;}
      while(tztZEnynzL == tztZEnynzL){UpIIcCNCZU = true;}
      while(jhQrewmGfk == jhQrewmGfk){GrhiqpcnBZ = true;}
      if(LtKNjYWbDL == true){LtKNjYWbDL = false;}
      if(bKlxQfPVOW == true){bKlxQfPVOW = false;}
      if(iboCKxAJlN == true){iboCKxAJlN = false;}
      if(FMBEtzngpf == true){FMBEtzngpf = false;}
      if(QVjniYuSbz == true){QVjniYuSbz = false;}
      if(fRqICjEICl == true){fRqICjEICl = false;}
      if(XMppFPIhCQ == true){XMppFPIhCQ = false;}
      if(qifhFMrBSk == true){qifhFMrBSk = false;}
      if(BghmgmVrBK == true){BghmgmVrBK = false;}
      if(ufeDIDfshT == true){ufeDIDfshT = false;}
      if(QNQKHxlJCp == true){QNQKHxlJCp = false;}
      if(qDoQjpeCIR == true){qDoQjpeCIR = false;}
      if(sPfqVLDbZB == true){sPfqVLDbZB = false;}
      if(fySzUnQWfj == true){fySzUnQWfj = false;}
      if(BMoLSqpNSR == true){BMoLSqpNSR = false;}
      if(YdkPZAgYnw == true){YdkPZAgYnw = false;}
      if(sKiBJsjouw == true){sKiBJsjouw = false;}
      if(ZIWYQgaUXe == true){ZIWYQgaUXe = false;}
      if(UpIIcCNCZU == true){UpIIcCNCZU = false;}
      if(GrhiqpcnBZ == true){GrhiqpcnBZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EAOFMWHPAI
{ 
  void RMUPshXtMw()
  { 
      bool mXKJjJKzkw = false;
      bool KOLwdNNMCy = false;
      bool OgriVlqekh = false;
      bool IDXWilBnaI = false;
      bool pEIaHZFFjE = false;
      bool ySfomFeany = false;
      bool ReOCmGqoNr = false;
      bool MZlsHKXRbu = false;
      bool glugjoXhjc = false;
      bool HZAbqKpGmA = false;
      bool hPrrrYgmgc = false;
      bool hNzrQfjgSy = false;
      bool iIFjklYJCx = false;
      bool URdaMQsCnK = false;
      bool IjBHusZILL = false;
      bool aImoQZKIHF = false;
      bool zWkiIPjYeA = false;
      bool lgsHozHxnq = false;
      bool LQypWLenJm = false;
      bool FkuiLkzRzf = false;
      string WAoIAWNUfA;
      string FPoJdZIIOx;
      string xqfgirpYhs;
      string jmbCXgSEAY;
      string HokLwcIMAs;
      string CkMgMeTIYI;
      string gnmlPSmmkx;
      string HDIpoHFUkG;
      string jcYopzZups;
      string MKerqSCyuc;
      string oVbDlybVqE;
      string YzWSXEPxuQ;
      string rqwrjxYQyV;
      string FGYHQNAUDr;
      string WDElTNmMTm;
      string DEDekyYjSn;
      string ZKXUySaPBK;
      string DttDtnmKXV;
      string JLxKSADsWS;
      string nQCORLfimB;
      if(WAoIAWNUfA == oVbDlybVqE){mXKJjJKzkw = true;}
      else if(oVbDlybVqE == WAoIAWNUfA){hPrrrYgmgc = true;}
      if(FPoJdZIIOx == YzWSXEPxuQ){KOLwdNNMCy = true;}
      else if(YzWSXEPxuQ == FPoJdZIIOx){hNzrQfjgSy = true;}
      if(xqfgirpYhs == rqwrjxYQyV){OgriVlqekh = true;}
      else if(rqwrjxYQyV == xqfgirpYhs){iIFjklYJCx = true;}
      if(jmbCXgSEAY == FGYHQNAUDr){IDXWilBnaI = true;}
      else if(FGYHQNAUDr == jmbCXgSEAY){URdaMQsCnK = true;}
      if(HokLwcIMAs == WDElTNmMTm){pEIaHZFFjE = true;}
      else if(WDElTNmMTm == HokLwcIMAs){IjBHusZILL = true;}
      if(CkMgMeTIYI == DEDekyYjSn){ySfomFeany = true;}
      else if(DEDekyYjSn == CkMgMeTIYI){aImoQZKIHF = true;}
      if(gnmlPSmmkx == ZKXUySaPBK){ReOCmGqoNr = true;}
      else if(ZKXUySaPBK == gnmlPSmmkx){zWkiIPjYeA = true;}
      if(HDIpoHFUkG == DttDtnmKXV){MZlsHKXRbu = true;}
      if(jcYopzZups == JLxKSADsWS){glugjoXhjc = true;}
      if(MKerqSCyuc == nQCORLfimB){HZAbqKpGmA = true;}
      while(DttDtnmKXV == HDIpoHFUkG){lgsHozHxnq = true;}
      while(JLxKSADsWS == JLxKSADsWS){LQypWLenJm = true;}
      while(nQCORLfimB == nQCORLfimB){FkuiLkzRzf = true;}
      if(mXKJjJKzkw == true){mXKJjJKzkw = false;}
      if(KOLwdNNMCy == true){KOLwdNNMCy = false;}
      if(OgriVlqekh == true){OgriVlqekh = false;}
      if(IDXWilBnaI == true){IDXWilBnaI = false;}
      if(pEIaHZFFjE == true){pEIaHZFFjE = false;}
      if(ySfomFeany == true){ySfomFeany = false;}
      if(ReOCmGqoNr == true){ReOCmGqoNr = false;}
      if(MZlsHKXRbu == true){MZlsHKXRbu = false;}
      if(glugjoXhjc == true){glugjoXhjc = false;}
      if(HZAbqKpGmA == true){HZAbqKpGmA = false;}
      if(hPrrrYgmgc == true){hPrrrYgmgc = false;}
      if(hNzrQfjgSy == true){hNzrQfjgSy = false;}
      if(iIFjklYJCx == true){iIFjklYJCx = false;}
      if(URdaMQsCnK == true){URdaMQsCnK = false;}
      if(IjBHusZILL == true){IjBHusZILL = false;}
      if(aImoQZKIHF == true){aImoQZKIHF = false;}
      if(zWkiIPjYeA == true){zWkiIPjYeA = false;}
      if(lgsHozHxnq == true){lgsHozHxnq = false;}
      if(LQypWLenJm == true){LQypWLenJm = false;}
      if(FkuiLkzRzf == true){FkuiLkzRzf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SWGZFNILXU
{ 
  void MpKqBqzIbl()
  { 
      bool cRTaPuccXr = false;
      bool wraBEhJHZJ = false;
      bool ZBhiqjktet = false;
      bool GBAkphqCbQ = false;
      bool nFVUJmVydU = false;
      bool mPmrIbikje = false;
      bool KhxdltrpLV = false;
      bool qGeIVTfMYD = false;
      bool OmPKGpOHbO = false;
      bool yGSwGFIrhO = false;
      bool uemIcgjdVn = false;
      bool uWLgQWSlWw = false;
      bool fjNxWknhCQ = false;
      bool LndJIiAGgY = false;
      bool FjlmSbtlfi = false;
      bool lVUliKQokr = false;
      bool sBbFcHrBXg = false;
      bool WLFypuyaet = false;
      bool pCCSdpSrax = false;
      bool RKVofDIfKK = false;
      string xPcJWZEEuP;
      string doPetnwPHN;
      string kNPpLZDOgG;
      string nQuMcafNrs;
      string esdRjTaGfa;
      string xmDOnjAlxw;
      string VpWnbNtCCS;
      string HiXNirixGq;
      string zwiGJAMfXr;
      string asPuXnVopV;
      string ZYEMSNPpfw;
      string BCfGxZHQea;
      string AOdJrNTbpt;
      string VsHjRarVmw;
      string jWzbpXNIyx;
      string gFKOVLttUE;
      string smzlZHtwoW;
      string hkchqcOBTT;
      string AKdrMQhsNF;
      string fxAiCxWMBh;
      if(xPcJWZEEuP == ZYEMSNPpfw){cRTaPuccXr = true;}
      else if(ZYEMSNPpfw == xPcJWZEEuP){uemIcgjdVn = true;}
      if(doPetnwPHN == BCfGxZHQea){wraBEhJHZJ = true;}
      else if(BCfGxZHQea == doPetnwPHN){uWLgQWSlWw = true;}
      if(kNPpLZDOgG == AOdJrNTbpt){ZBhiqjktet = true;}
      else if(AOdJrNTbpt == kNPpLZDOgG){fjNxWknhCQ = true;}
      if(nQuMcafNrs == VsHjRarVmw){GBAkphqCbQ = true;}
      else if(VsHjRarVmw == nQuMcafNrs){LndJIiAGgY = true;}
      if(esdRjTaGfa == jWzbpXNIyx){nFVUJmVydU = true;}
      else if(jWzbpXNIyx == esdRjTaGfa){FjlmSbtlfi = true;}
      if(xmDOnjAlxw == gFKOVLttUE){mPmrIbikje = true;}
      else if(gFKOVLttUE == xmDOnjAlxw){lVUliKQokr = true;}
      if(VpWnbNtCCS == smzlZHtwoW){KhxdltrpLV = true;}
      else if(smzlZHtwoW == VpWnbNtCCS){sBbFcHrBXg = true;}
      if(HiXNirixGq == hkchqcOBTT){qGeIVTfMYD = true;}
      if(zwiGJAMfXr == AKdrMQhsNF){OmPKGpOHbO = true;}
      if(asPuXnVopV == fxAiCxWMBh){yGSwGFIrhO = true;}
      while(hkchqcOBTT == HiXNirixGq){WLFypuyaet = true;}
      while(AKdrMQhsNF == AKdrMQhsNF){pCCSdpSrax = true;}
      while(fxAiCxWMBh == fxAiCxWMBh){RKVofDIfKK = true;}
      if(cRTaPuccXr == true){cRTaPuccXr = false;}
      if(wraBEhJHZJ == true){wraBEhJHZJ = false;}
      if(ZBhiqjktet == true){ZBhiqjktet = false;}
      if(GBAkphqCbQ == true){GBAkphqCbQ = false;}
      if(nFVUJmVydU == true){nFVUJmVydU = false;}
      if(mPmrIbikje == true){mPmrIbikje = false;}
      if(KhxdltrpLV == true){KhxdltrpLV = false;}
      if(qGeIVTfMYD == true){qGeIVTfMYD = false;}
      if(OmPKGpOHbO == true){OmPKGpOHbO = false;}
      if(yGSwGFIrhO == true){yGSwGFIrhO = false;}
      if(uemIcgjdVn == true){uemIcgjdVn = false;}
      if(uWLgQWSlWw == true){uWLgQWSlWw = false;}
      if(fjNxWknhCQ == true){fjNxWknhCQ = false;}
      if(LndJIiAGgY == true){LndJIiAGgY = false;}
      if(FjlmSbtlfi == true){FjlmSbtlfi = false;}
      if(lVUliKQokr == true){lVUliKQokr = false;}
      if(sBbFcHrBXg == true){sBbFcHrBXg = false;}
      if(WLFypuyaet == true){WLFypuyaet = false;}
      if(pCCSdpSrax == true){pCCSdpSrax = false;}
      if(RKVofDIfKK == true){RKVofDIfKK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EGYVLZUWAP
{ 
  void jsxzJwgkkS()
  { 
      bool zxnJwiErhZ = false;
      bool rVaRVnQVQt = false;
      bool BpYfYrxcMM = false;
      bool MlgUuRynDh = false;
      bool eOwSPAVQxC = false;
      bool aVCPCIYIjD = false;
      bool lafVNGnFVE = false;
      bool pbSiPmtFQY = false;
      bool WffJkqiRSl = false;
      bool soEzwDiaFJ = false;
      bool LPtsMyCTAO = false;
      bool OSrKgFuVjW = false;
      bool WWmjKAXTlL = false;
      bool ESAGNGllxm = false;
      bool nORDWaxtRq = false;
      bool HNqilocKiM = false;
      bool ahgnKuRkxa = false;
      bool TJXwhHFiMi = false;
      bool CdBuDqbRUX = false;
      bool daDkMFhcsb = false;
      string yoPtFIRoPE;
      string fSmTduPZLD;
      string PQoFnAjUSl;
      string YquFHGNcny;
      string jaubkbYzzx;
      string cCUfDgzJFF;
      string XwWdfnWgMW;
      string hmkMSoUMUL;
      string ajVUIWVOCZ;
      string HDWianDRww;
      string FrmbPpQINO;
      string MlotdnZCVJ;
      string RHelPdPCle;
      string kDQXFixtFR;
      string FNBmNUOcEl;
      string NBwleyMALk;
      string aOVhdIVRnu;
      string pexDDEFqYt;
      string OmxzQiGesH;
      string VxhTqqrTJE;
      if(yoPtFIRoPE == FrmbPpQINO){zxnJwiErhZ = true;}
      else if(FrmbPpQINO == yoPtFIRoPE){LPtsMyCTAO = true;}
      if(fSmTduPZLD == MlotdnZCVJ){rVaRVnQVQt = true;}
      else if(MlotdnZCVJ == fSmTduPZLD){OSrKgFuVjW = true;}
      if(PQoFnAjUSl == RHelPdPCle){BpYfYrxcMM = true;}
      else if(RHelPdPCle == PQoFnAjUSl){WWmjKAXTlL = true;}
      if(YquFHGNcny == kDQXFixtFR){MlgUuRynDh = true;}
      else if(kDQXFixtFR == YquFHGNcny){ESAGNGllxm = true;}
      if(jaubkbYzzx == FNBmNUOcEl){eOwSPAVQxC = true;}
      else if(FNBmNUOcEl == jaubkbYzzx){nORDWaxtRq = true;}
      if(cCUfDgzJFF == NBwleyMALk){aVCPCIYIjD = true;}
      else if(NBwleyMALk == cCUfDgzJFF){HNqilocKiM = true;}
      if(XwWdfnWgMW == aOVhdIVRnu){lafVNGnFVE = true;}
      else if(aOVhdIVRnu == XwWdfnWgMW){ahgnKuRkxa = true;}
      if(hmkMSoUMUL == pexDDEFqYt){pbSiPmtFQY = true;}
      if(ajVUIWVOCZ == OmxzQiGesH){WffJkqiRSl = true;}
      if(HDWianDRww == VxhTqqrTJE){soEzwDiaFJ = true;}
      while(pexDDEFqYt == hmkMSoUMUL){TJXwhHFiMi = true;}
      while(OmxzQiGesH == OmxzQiGesH){CdBuDqbRUX = true;}
      while(VxhTqqrTJE == VxhTqqrTJE){daDkMFhcsb = true;}
      if(zxnJwiErhZ == true){zxnJwiErhZ = false;}
      if(rVaRVnQVQt == true){rVaRVnQVQt = false;}
      if(BpYfYrxcMM == true){BpYfYrxcMM = false;}
      if(MlgUuRynDh == true){MlgUuRynDh = false;}
      if(eOwSPAVQxC == true){eOwSPAVQxC = false;}
      if(aVCPCIYIjD == true){aVCPCIYIjD = false;}
      if(lafVNGnFVE == true){lafVNGnFVE = false;}
      if(pbSiPmtFQY == true){pbSiPmtFQY = false;}
      if(WffJkqiRSl == true){WffJkqiRSl = false;}
      if(soEzwDiaFJ == true){soEzwDiaFJ = false;}
      if(LPtsMyCTAO == true){LPtsMyCTAO = false;}
      if(OSrKgFuVjW == true){OSrKgFuVjW = false;}
      if(WWmjKAXTlL == true){WWmjKAXTlL = false;}
      if(ESAGNGllxm == true){ESAGNGllxm = false;}
      if(nORDWaxtRq == true){nORDWaxtRq = false;}
      if(HNqilocKiM == true){HNqilocKiM = false;}
      if(ahgnKuRkxa == true){ahgnKuRkxa = false;}
      if(TJXwhHFiMi == true){TJXwhHFiMi = false;}
      if(CdBuDqbRUX == true){CdBuDqbRUX = false;}
      if(daDkMFhcsb == true){daDkMFhcsb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DLQZEDAAII
{ 
  void gxGJtKioZE()
  { 
      bool kBJfhmIbJI = false;
      bool TELEetVlly = false;
      bool ZPDwZKESRW = false;
      bool DmJEDdSBEB = false;
      bool TprytGgNLW = false;
      bool RbhLcVxNFW = false;
      bool ipJlFgtGBB = false;
      bool bTgjdjWECT = false;
      bool dpGtFaFxag = false;
      bool fEwgSdfFsN = false;
      bool LaMKuxtxgs = false;
      bool yrLlssiPgd = false;
      bool bxeTUWXzQA = false;
      bool DRLoIDcuzI = false;
      bool fHPghnsJnZ = false;
      bool tQYOlOurpX = false;
      bool YtggpggVdp = false;
      bool PnPXxTgxkg = false;
      bool dNLqGlswDs = false;
      bool HjEbilaiqB = false;
      string XnnbdoxPiU;
      string DHJeGEDujR;
      string QkHiLzkQBy;
      string aMmyGXJjNH;
      string ZrVPVwnyTx;
      string niaSsmgFPd;
      string EfOjsqUKYh;
      string uSgbrXPrMP;
      string LmxDKrlUFT;
      string qEUiDsdkVe;
      string acZkBUByZU;
      string WnrzSQiLYB;
      string FAEFqqxyYz;
      string tdWgohNLBo;
      string pmtkwCLUQl;
      string JRLUZZXUsK;
      string XDYaarRKKj;
      string DWJjKRGTIo;
      string echmobSBHO;
      string KsSqRmOTKD;
      if(XnnbdoxPiU == acZkBUByZU){kBJfhmIbJI = true;}
      else if(acZkBUByZU == XnnbdoxPiU){LaMKuxtxgs = true;}
      if(DHJeGEDujR == WnrzSQiLYB){TELEetVlly = true;}
      else if(WnrzSQiLYB == DHJeGEDujR){yrLlssiPgd = true;}
      if(QkHiLzkQBy == FAEFqqxyYz){ZPDwZKESRW = true;}
      else if(FAEFqqxyYz == QkHiLzkQBy){bxeTUWXzQA = true;}
      if(aMmyGXJjNH == tdWgohNLBo){DmJEDdSBEB = true;}
      else if(tdWgohNLBo == aMmyGXJjNH){DRLoIDcuzI = true;}
      if(ZrVPVwnyTx == pmtkwCLUQl){TprytGgNLW = true;}
      else if(pmtkwCLUQl == ZrVPVwnyTx){fHPghnsJnZ = true;}
      if(niaSsmgFPd == JRLUZZXUsK){RbhLcVxNFW = true;}
      else if(JRLUZZXUsK == niaSsmgFPd){tQYOlOurpX = true;}
      if(EfOjsqUKYh == XDYaarRKKj){ipJlFgtGBB = true;}
      else if(XDYaarRKKj == EfOjsqUKYh){YtggpggVdp = true;}
      if(uSgbrXPrMP == DWJjKRGTIo){bTgjdjWECT = true;}
      if(LmxDKrlUFT == echmobSBHO){dpGtFaFxag = true;}
      if(qEUiDsdkVe == KsSqRmOTKD){fEwgSdfFsN = true;}
      while(DWJjKRGTIo == uSgbrXPrMP){PnPXxTgxkg = true;}
      while(echmobSBHO == echmobSBHO){dNLqGlswDs = true;}
      while(KsSqRmOTKD == KsSqRmOTKD){HjEbilaiqB = true;}
      if(kBJfhmIbJI == true){kBJfhmIbJI = false;}
      if(TELEetVlly == true){TELEetVlly = false;}
      if(ZPDwZKESRW == true){ZPDwZKESRW = false;}
      if(DmJEDdSBEB == true){DmJEDdSBEB = false;}
      if(TprytGgNLW == true){TprytGgNLW = false;}
      if(RbhLcVxNFW == true){RbhLcVxNFW = false;}
      if(ipJlFgtGBB == true){ipJlFgtGBB = false;}
      if(bTgjdjWECT == true){bTgjdjWECT = false;}
      if(dpGtFaFxag == true){dpGtFaFxag = false;}
      if(fEwgSdfFsN == true){fEwgSdfFsN = false;}
      if(LaMKuxtxgs == true){LaMKuxtxgs = false;}
      if(yrLlssiPgd == true){yrLlssiPgd = false;}
      if(bxeTUWXzQA == true){bxeTUWXzQA = false;}
      if(DRLoIDcuzI == true){DRLoIDcuzI = false;}
      if(fHPghnsJnZ == true){fHPghnsJnZ = false;}
      if(tQYOlOurpX == true){tQYOlOurpX = false;}
      if(YtggpggVdp == true){YtggpggVdp = false;}
      if(PnPXxTgxkg == true){PnPXxTgxkg = false;}
      if(dNLqGlswDs == true){dNLqGlswDs = false;}
      if(HjEbilaiqB == true){HjEbilaiqB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DCUQDUPJFS
{ 
  void TCQVOZFzLS()
  { 
      bool lDmROrKMhS = false;
      bool oeMYIlnrNu = false;
      bool bJTkZVLVJY = false;
      bool BWocSkrsHS = false;
      bool XyUmaLXBnV = false;
      bool kQzchbiCqs = false;
      bool gnCIRSpjGX = false;
      bool tukuWdngJO = false;
      bool xJhmnjWMup = false;
      bool BoBOkjuLVI = false;
      bool UnuQbofEGD = false;
      bool nCrcuWGOUg = false;
      bool udnPWEtVJl = false;
      bool icLAsJORLy = false;
      bool ESGrCzxYSO = false;
      bool dgpnNqzesW = false;
      bool uJtTULqqil = false;
      bool InCWbcWwNX = false;
      bool HVDuIBlWmB = false;
      bool JiXoCuXlXq = false;
      string jaTtDcmFRl;
      string wwAWgzYKeC;
      string ZunPKJONfJ;
      string slXqOhrSea;
      string sSgyUVQsdV;
      string tZJWyomEis;
      string NYZIrKXIIy;
      string GFfEJGNpto;
      string rViKOTcAsY;
      string unjkNTsYFK;
      string xIjfPntFNq;
      string bxKtBroOsY;
      string gWPjCRVtqo;
      string NojiqjkDua;
      string YWlCwydpiU;
      string ddegcZsAcx;
      string RzOYdlMaCR;
      string GlTSzJkNmE;
      string nfKVKiKDGQ;
      string qkZxIZINXJ;
      if(jaTtDcmFRl == xIjfPntFNq){lDmROrKMhS = true;}
      else if(xIjfPntFNq == jaTtDcmFRl){UnuQbofEGD = true;}
      if(wwAWgzYKeC == bxKtBroOsY){oeMYIlnrNu = true;}
      else if(bxKtBroOsY == wwAWgzYKeC){nCrcuWGOUg = true;}
      if(ZunPKJONfJ == gWPjCRVtqo){bJTkZVLVJY = true;}
      else if(gWPjCRVtqo == ZunPKJONfJ){udnPWEtVJl = true;}
      if(slXqOhrSea == NojiqjkDua){BWocSkrsHS = true;}
      else if(NojiqjkDua == slXqOhrSea){icLAsJORLy = true;}
      if(sSgyUVQsdV == YWlCwydpiU){XyUmaLXBnV = true;}
      else if(YWlCwydpiU == sSgyUVQsdV){ESGrCzxYSO = true;}
      if(tZJWyomEis == ddegcZsAcx){kQzchbiCqs = true;}
      else if(ddegcZsAcx == tZJWyomEis){dgpnNqzesW = true;}
      if(NYZIrKXIIy == RzOYdlMaCR){gnCIRSpjGX = true;}
      else if(RzOYdlMaCR == NYZIrKXIIy){uJtTULqqil = true;}
      if(GFfEJGNpto == GlTSzJkNmE){tukuWdngJO = true;}
      if(rViKOTcAsY == nfKVKiKDGQ){xJhmnjWMup = true;}
      if(unjkNTsYFK == qkZxIZINXJ){BoBOkjuLVI = true;}
      while(GlTSzJkNmE == GFfEJGNpto){InCWbcWwNX = true;}
      while(nfKVKiKDGQ == nfKVKiKDGQ){HVDuIBlWmB = true;}
      while(qkZxIZINXJ == qkZxIZINXJ){JiXoCuXlXq = true;}
      if(lDmROrKMhS == true){lDmROrKMhS = false;}
      if(oeMYIlnrNu == true){oeMYIlnrNu = false;}
      if(bJTkZVLVJY == true){bJTkZVLVJY = false;}
      if(BWocSkrsHS == true){BWocSkrsHS = false;}
      if(XyUmaLXBnV == true){XyUmaLXBnV = false;}
      if(kQzchbiCqs == true){kQzchbiCqs = false;}
      if(gnCIRSpjGX == true){gnCIRSpjGX = false;}
      if(tukuWdngJO == true){tukuWdngJO = false;}
      if(xJhmnjWMup == true){xJhmnjWMup = false;}
      if(BoBOkjuLVI == true){BoBOkjuLVI = false;}
      if(UnuQbofEGD == true){UnuQbofEGD = false;}
      if(nCrcuWGOUg == true){nCrcuWGOUg = false;}
      if(udnPWEtVJl == true){udnPWEtVJl = false;}
      if(icLAsJORLy == true){icLAsJORLy = false;}
      if(ESGrCzxYSO == true){ESGrCzxYSO = false;}
      if(dgpnNqzesW == true){dgpnNqzesW = false;}
      if(uJtTULqqil == true){uJtTULqqil = false;}
      if(InCWbcWwNX == true){InCWbcWwNX = false;}
      if(HVDuIBlWmB == true){HVDuIBlWmB = false;}
      if(JiXoCuXlXq == true){JiXoCuXlXq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SUEKRWHPLL
{ 
  void yCApVZHNRq()
  { 
      bool exTGBaEopZ = false;
      bool DbqiilhmYn = false;
      bool ijIMOXymDx = false;
      bool JEkcYUkSTZ = false;
      bool VxoBDRMpai = false;
      bool iHlRjtoGqc = false;
      bool cRksQyqOJO = false;
      bool BOTySltGJw = false;
      bool LHMTNCSSsd = false;
      bool fdapxDLukE = false;
      bool aygLhTnmyy = false;
      bool AhxtRUFRfN = false;
      bool fXUeiWmcBP = false;
      bool ayVEVNaAks = false;
      bool OeTtdxggYc = false;
      bool ysPWXCcBbL = false;
      bool fKliXBMrYE = false;
      bool sEflzBEaBl = false;
      bool pGDXRghyfS = false;
      bool jYYZNDrjWb = false;
      string JzgRYUGNmw;
      string pmTbPesiky;
      string WlXydFiZoE;
      string qUXrhWFUHk;
      string OijwGiJRda;
      string HXIKeXbhnT;
      string lfXiFUOats;
      string YYbzjmCart;
      string wQwOwTMNNJ;
      string uXgmziLBpl;
      string UhXjCiuIaq;
      string VApsXUjJll;
      string HBNjyArnzA;
      string bAkFZNrLLM;
      string XDlVnthmPd;
      string zBOEdSTnlB;
      string qGIaOUPjTJ;
      string cXxYNEPrwD;
      string SEYVBZlfbG;
      string tEYJVQtKGS;
      if(JzgRYUGNmw == UhXjCiuIaq){exTGBaEopZ = true;}
      else if(UhXjCiuIaq == JzgRYUGNmw){aygLhTnmyy = true;}
      if(pmTbPesiky == VApsXUjJll){DbqiilhmYn = true;}
      else if(VApsXUjJll == pmTbPesiky){AhxtRUFRfN = true;}
      if(WlXydFiZoE == HBNjyArnzA){ijIMOXymDx = true;}
      else if(HBNjyArnzA == WlXydFiZoE){fXUeiWmcBP = true;}
      if(qUXrhWFUHk == bAkFZNrLLM){JEkcYUkSTZ = true;}
      else if(bAkFZNrLLM == qUXrhWFUHk){ayVEVNaAks = true;}
      if(OijwGiJRda == XDlVnthmPd){VxoBDRMpai = true;}
      else if(XDlVnthmPd == OijwGiJRda){OeTtdxggYc = true;}
      if(HXIKeXbhnT == zBOEdSTnlB){iHlRjtoGqc = true;}
      else if(zBOEdSTnlB == HXIKeXbhnT){ysPWXCcBbL = true;}
      if(lfXiFUOats == qGIaOUPjTJ){cRksQyqOJO = true;}
      else if(qGIaOUPjTJ == lfXiFUOats){fKliXBMrYE = true;}
      if(YYbzjmCart == cXxYNEPrwD){BOTySltGJw = true;}
      if(wQwOwTMNNJ == SEYVBZlfbG){LHMTNCSSsd = true;}
      if(uXgmziLBpl == tEYJVQtKGS){fdapxDLukE = true;}
      while(cXxYNEPrwD == YYbzjmCart){sEflzBEaBl = true;}
      while(SEYVBZlfbG == SEYVBZlfbG){pGDXRghyfS = true;}
      while(tEYJVQtKGS == tEYJVQtKGS){jYYZNDrjWb = true;}
      if(exTGBaEopZ == true){exTGBaEopZ = false;}
      if(DbqiilhmYn == true){DbqiilhmYn = false;}
      if(ijIMOXymDx == true){ijIMOXymDx = false;}
      if(JEkcYUkSTZ == true){JEkcYUkSTZ = false;}
      if(VxoBDRMpai == true){VxoBDRMpai = false;}
      if(iHlRjtoGqc == true){iHlRjtoGqc = false;}
      if(cRksQyqOJO == true){cRksQyqOJO = false;}
      if(BOTySltGJw == true){BOTySltGJw = false;}
      if(LHMTNCSSsd == true){LHMTNCSSsd = false;}
      if(fdapxDLukE == true){fdapxDLukE = false;}
      if(aygLhTnmyy == true){aygLhTnmyy = false;}
      if(AhxtRUFRfN == true){AhxtRUFRfN = false;}
      if(fXUeiWmcBP == true){fXUeiWmcBP = false;}
      if(ayVEVNaAks == true){ayVEVNaAks = false;}
      if(OeTtdxggYc == true){OeTtdxggYc = false;}
      if(ysPWXCcBbL == true){ysPWXCcBbL = false;}
      if(fKliXBMrYE == true){fKliXBMrYE = false;}
      if(sEflzBEaBl == true){sEflzBEaBl = false;}
      if(pGDXRghyfS == true){pGDXRghyfS = false;}
      if(jYYZNDrjWb == true){jYYZNDrjWb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCSAZHELIW
{ 
  void gBSTFVJWHP()
  { 
      bool LNMpVfOlAp = false;
      bool xbUmszTTmq = false;
      bool BbCrYAkHGR = false;
      bool AxwaqSbZpY = false;
      bool jzLDXKexly = false;
      bool ilihgiLURV = false;
      bool uHeiozfsua = false;
      bool WtdNHBQyUN = false;
      bool UmUIiONNtI = false;
      bool HHIUdbUbNX = false;
      bool ekCKbnIUae = false;
      bool RMzDBIlWza = false;
      bool kRzmSOlIje = false;
      bool gojxiikKft = false;
      bool GrlOptHETV = false;
      bool pybmlMlPrM = false;
      bool CzkuycbCTR = false;
      bool WbpFUsekwX = false;
      bool GgoOnhMxKV = false;
      bool xVRTqGHqPN = false;
      string CUtWPsIqTI;
      string CZggbGAhJc;
      string EbmYkxWoak;
      string JEZoNCTKQY;
      string UJQbozbeSE;
      string tTAJjagVkR;
      string WTPhyxzqTY;
      string moQkItKLil;
      string VqVWqpDQFm;
      string VxZyBAthdq;
      string AjLtQECPBo;
      string PVmzweysqI;
      string tilgDpPRiI;
      string zcgqlkebFl;
      string mmOPWAJZCV;
      string CBpVxQyepZ;
      string njgrpmnwNL;
      string AVmEUGTVKD;
      string goPMFylLtU;
      string mAkexDGVZi;
      if(CUtWPsIqTI == AjLtQECPBo){LNMpVfOlAp = true;}
      else if(AjLtQECPBo == CUtWPsIqTI){ekCKbnIUae = true;}
      if(CZggbGAhJc == PVmzweysqI){xbUmszTTmq = true;}
      else if(PVmzweysqI == CZggbGAhJc){RMzDBIlWza = true;}
      if(EbmYkxWoak == tilgDpPRiI){BbCrYAkHGR = true;}
      else if(tilgDpPRiI == EbmYkxWoak){kRzmSOlIje = true;}
      if(JEZoNCTKQY == zcgqlkebFl){AxwaqSbZpY = true;}
      else if(zcgqlkebFl == JEZoNCTKQY){gojxiikKft = true;}
      if(UJQbozbeSE == mmOPWAJZCV){jzLDXKexly = true;}
      else if(mmOPWAJZCV == UJQbozbeSE){GrlOptHETV = true;}
      if(tTAJjagVkR == CBpVxQyepZ){ilihgiLURV = true;}
      else if(CBpVxQyepZ == tTAJjagVkR){pybmlMlPrM = true;}
      if(WTPhyxzqTY == njgrpmnwNL){uHeiozfsua = true;}
      else if(njgrpmnwNL == WTPhyxzqTY){CzkuycbCTR = true;}
      if(moQkItKLil == AVmEUGTVKD){WtdNHBQyUN = true;}
      if(VqVWqpDQFm == goPMFylLtU){UmUIiONNtI = true;}
      if(VxZyBAthdq == mAkexDGVZi){HHIUdbUbNX = true;}
      while(AVmEUGTVKD == moQkItKLil){WbpFUsekwX = true;}
      while(goPMFylLtU == goPMFylLtU){GgoOnhMxKV = true;}
      while(mAkexDGVZi == mAkexDGVZi){xVRTqGHqPN = true;}
      if(LNMpVfOlAp == true){LNMpVfOlAp = false;}
      if(xbUmszTTmq == true){xbUmszTTmq = false;}
      if(BbCrYAkHGR == true){BbCrYAkHGR = false;}
      if(AxwaqSbZpY == true){AxwaqSbZpY = false;}
      if(jzLDXKexly == true){jzLDXKexly = false;}
      if(ilihgiLURV == true){ilihgiLURV = false;}
      if(uHeiozfsua == true){uHeiozfsua = false;}
      if(WtdNHBQyUN == true){WtdNHBQyUN = false;}
      if(UmUIiONNtI == true){UmUIiONNtI = false;}
      if(HHIUdbUbNX == true){HHIUdbUbNX = false;}
      if(ekCKbnIUae == true){ekCKbnIUae = false;}
      if(RMzDBIlWza == true){RMzDBIlWza = false;}
      if(kRzmSOlIje == true){kRzmSOlIje = false;}
      if(gojxiikKft == true){gojxiikKft = false;}
      if(GrlOptHETV == true){GrlOptHETV = false;}
      if(pybmlMlPrM == true){pybmlMlPrM = false;}
      if(CzkuycbCTR == true){CzkuycbCTR = false;}
      if(WbpFUsekwX == true){WbpFUsekwX = false;}
      if(GgoOnhMxKV == true){GgoOnhMxKV = false;}
      if(xVRTqGHqPN == true){xVRTqGHqPN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BAUMITYQTL
{ 
  void UohxybeiGg()
  { 
      bool cmHIBfKZEW = false;
      bool XGKOhjeqpy = false;
      bool hffKkRfhYI = false;
      bool VUyKxoxzWM = false;
      bool DwMOxczOSn = false;
      bool zoOfUxHxWi = false;
      bool zcAuACIzRr = false;
      bool leTdulSQNI = false;
      bool SROjJgGRpz = false;
      bool hAcmMZuQOt = false;
      bool TzwaCTUkjh = false;
      bool dqiOQhNQlT = false;
      bool wpIRJkCfQU = false;
      bool pBBToSUnho = false;
      bool LUhIUqROWe = false;
      bool MeduxdpeQR = false;
      bool QoUOrcoPYx = false;
      bool NYhxHaIAxS = false;
      bool SnJkIKWGVK = false;
      bool cpXQXWASPr = false;
      string rSaBLoNPSU;
      string hrzGcKAbXw;
      string eREPTDzeQK;
      string VWVVfusUYe;
      string ylpxhkgUXK;
      string OcJOLZNKhI;
      string ohzHzKWdah;
      string QfCrxsbHhh;
      string VdHFwsMGJF;
      string ghmQpPlhyW;
      string ODtoshZRQS;
      string yGczmLatKG;
      string xPTUAhslCh;
      string GsJKTSiRLN;
      string SuoqHaFmcd;
      string orWrYyiYoK;
      string onPiMExRfU;
      string bIhxmCacNZ;
      string cFIXrNVRlU;
      string iKcAXefFeC;
      if(rSaBLoNPSU == ODtoshZRQS){cmHIBfKZEW = true;}
      else if(ODtoshZRQS == rSaBLoNPSU){TzwaCTUkjh = true;}
      if(hrzGcKAbXw == yGczmLatKG){XGKOhjeqpy = true;}
      else if(yGczmLatKG == hrzGcKAbXw){dqiOQhNQlT = true;}
      if(eREPTDzeQK == xPTUAhslCh){hffKkRfhYI = true;}
      else if(xPTUAhslCh == eREPTDzeQK){wpIRJkCfQU = true;}
      if(VWVVfusUYe == GsJKTSiRLN){VUyKxoxzWM = true;}
      else if(GsJKTSiRLN == VWVVfusUYe){pBBToSUnho = true;}
      if(ylpxhkgUXK == SuoqHaFmcd){DwMOxczOSn = true;}
      else if(SuoqHaFmcd == ylpxhkgUXK){LUhIUqROWe = true;}
      if(OcJOLZNKhI == orWrYyiYoK){zoOfUxHxWi = true;}
      else if(orWrYyiYoK == OcJOLZNKhI){MeduxdpeQR = true;}
      if(ohzHzKWdah == onPiMExRfU){zcAuACIzRr = true;}
      else if(onPiMExRfU == ohzHzKWdah){QoUOrcoPYx = true;}
      if(QfCrxsbHhh == bIhxmCacNZ){leTdulSQNI = true;}
      if(VdHFwsMGJF == cFIXrNVRlU){SROjJgGRpz = true;}
      if(ghmQpPlhyW == iKcAXefFeC){hAcmMZuQOt = true;}
      while(bIhxmCacNZ == QfCrxsbHhh){NYhxHaIAxS = true;}
      while(cFIXrNVRlU == cFIXrNVRlU){SnJkIKWGVK = true;}
      while(iKcAXefFeC == iKcAXefFeC){cpXQXWASPr = true;}
      if(cmHIBfKZEW == true){cmHIBfKZEW = false;}
      if(XGKOhjeqpy == true){XGKOhjeqpy = false;}
      if(hffKkRfhYI == true){hffKkRfhYI = false;}
      if(VUyKxoxzWM == true){VUyKxoxzWM = false;}
      if(DwMOxczOSn == true){DwMOxczOSn = false;}
      if(zoOfUxHxWi == true){zoOfUxHxWi = false;}
      if(zcAuACIzRr == true){zcAuACIzRr = false;}
      if(leTdulSQNI == true){leTdulSQNI = false;}
      if(SROjJgGRpz == true){SROjJgGRpz = false;}
      if(hAcmMZuQOt == true){hAcmMZuQOt = false;}
      if(TzwaCTUkjh == true){TzwaCTUkjh = false;}
      if(dqiOQhNQlT == true){dqiOQhNQlT = false;}
      if(wpIRJkCfQU == true){wpIRJkCfQU = false;}
      if(pBBToSUnho == true){pBBToSUnho = false;}
      if(LUhIUqROWe == true){LUhIUqROWe = false;}
      if(MeduxdpeQR == true){MeduxdpeQR = false;}
      if(QoUOrcoPYx == true){QoUOrcoPYx = false;}
      if(NYhxHaIAxS == true){NYhxHaIAxS = false;}
      if(SnJkIKWGVK == true){SnJkIKWGVK = false;}
      if(cpXQXWASPr == true){cpXQXWASPr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AFTOPXQRFV
{ 
  void ZAFwgAOXUI()
  { 
      bool UnVQWixFqX = false;
      bool NeAZKVOOwC = false;
      bool iSzeDpPwUD = false;
      bool nVaPnxPRJk = false;
      bool sFyPoNMiKh = false;
      bool CsmphBnqNf = false;
      bool SBkmiqEjkM = false;
      bool GwEKJdTioo = false;
      bool dgklBuikhm = false;
      bool JXEdSqULgy = false;
      bool IbxybFnbfE = false;
      bool gFCXBlQzln = false;
      bool HTCyDhrarS = false;
      bool IICqfCjlJu = false;
      bool GHEcFDVfbf = false;
      bool ZVZrpoYyut = false;
      bool MNjMuYCKrz = false;
      bool BeophAOYsz = false;
      bool MMzLrmiKBq = false;
      bool clqPirWqhg = false;
      string LgYOeUuYuk;
      string yqfoRZxleL;
      string JRbCRsxMQB;
      string xqqntqrCnx;
      string IGKhaXwYxp;
      string rpkxCtEVwl;
      string XhItnGzquZ;
      string huygDDHtbt;
      string xYPZIGGtlz;
      string mVFCZZxPsT;
      string YEcWIxrDtz;
      string lJtCoyRhkh;
      string zFFumMouHc;
      string FqBHUrusQL;
      string NDAlNcaDNa;
      string IOeLTSyhjw;
      string HwuQsuImgw;
      string DYQYUwFThJ;
      string klhgUpLomC;
      string sMIUEQHirR;
      if(LgYOeUuYuk == YEcWIxrDtz){UnVQWixFqX = true;}
      else if(YEcWIxrDtz == LgYOeUuYuk){IbxybFnbfE = true;}
      if(yqfoRZxleL == lJtCoyRhkh){NeAZKVOOwC = true;}
      else if(lJtCoyRhkh == yqfoRZxleL){gFCXBlQzln = true;}
      if(JRbCRsxMQB == zFFumMouHc){iSzeDpPwUD = true;}
      else if(zFFumMouHc == JRbCRsxMQB){HTCyDhrarS = true;}
      if(xqqntqrCnx == FqBHUrusQL){nVaPnxPRJk = true;}
      else if(FqBHUrusQL == xqqntqrCnx){IICqfCjlJu = true;}
      if(IGKhaXwYxp == NDAlNcaDNa){sFyPoNMiKh = true;}
      else if(NDAlNcaDNa == IGKhaXwYxp){GHEcFDVfbf = true;}
      if(rpkxCtEVwl == IOeLTSyhjw){CsmphBnqNf = true;}
      else if(IOeLTSyhjw == rpkxCtEVwl){ZVZrpoYyut = true;}
      if(XhItnGzquZ == HwuQsuImgw){SBkmiqEjkM = true;}
      else if(HwuQsuImgw == XhItnGzquZ){MNjMuYCKrz = true;}
      if(huygDDHtbt == DYQYUwFThJ){GwEKJdTioo = true;}
      if(xYPZIGGtlz == klhgUpLomC){dgklBuikhm = true;}
      if(mVFCZZxPsT == sMIUEQHirR){JXEdSqULgy = true;}
      while(DYQYUwFThJ == huygDDHtbt){BeophAOYsz = true;}
      while(klhgUpLomC == klhgUpLomC){MMzLrmiKBq = true;}
      while(sMIUEQHirR == sMIUEQHirR){clqPirWqhg = true;}
      if(UnVQWixFqX == true){UnVQWixFqX = false;}
      if(NeAZKVOOwC == true){NeAZKVOOwC = false;}
      if(iSzeDpPwUD == true){iSzeDpPwUD = false;}
      if(nVaPnxPRJk == true){nVaPnxPRJk = false;}
      if(sFyPoNMiKh == true){sFyPoNMiKh = false;}
      if(CsmphBnqNf == true){CsmphBnqNf = false;}
      if(SBkmiqEjkM == true){SBkmiqEjkM = false;}
      if(GwEKJdTioo == true){GwEKJdTioo = false;}
      if(dgklBuikhm == true){dgklBuikhm = false;}
      if(JXEdSqULgy == true){JXEdSqULgy = false;}
      if(IbxybFnbfE == true){IbxybFnbfE = false;}
      if(gFCXBlQzln == true){gFCXBlQzln = false;}
      if(HTCyDhrarS == true){HTCyDhrarS = false;}
      if(IICqfCjlJu == true){IICqfCjlJu = false;}
      if(GHEcFDVfbf == true){GHEcFDVfbf = false;}
      if(ZVZrpoYyut == true){ZVZrpoYyut = false;}
      if(MNjMuYCKrz == true){MNjMuYCKrz = false;}
      if(BeophAOYsz == true){BeophAOYsz = false;}
      if(MMzLrmiKBq == true){MMzLrmiKBq = false;}
      if(clqPirWqhg == true){clqPirWqhg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FPIZCJAAXX
{ 
  void LLjYQrQogE()
  { 
      bool JhxCjDmTcA = false;
      bool wUtWxUVTcM = false;
      bool oOEbIomLii = false;
      bool qyzIxqhdEX = false;
      bool sZTpeGHCVO = false;
      bool HoLZttdVtt = false;
      bool PbjsIxVkZG = false;
      bool lrOETOtNxB = false;
      bool hjoUaBmYOC = false;
      bool MMjKHRoahh = false;
      bool kVcPbPaGFe = false;
      bool zQXrLelPSG = false;
      bool JwWWsZHEwB = false;
      bool ZTfOQLHZrK = false;
      bool agTiCwnryc = false;
      bool fYHaXnzFWC = false;
      bool IWJDEfkIaA = false;
      bool XMWHfccmUx = false;
      bool lPFTVAMEqb = false;
      bool MCCpCEWPeW = false;
      string RXiHylkrUm;
      string wkEKkdKusi;
      string OfCmPZWKHA;
      string rlNKToLKaV;
      string IZJebmTmBq;
      string hpuXilVwrX;
      string PZkTuJWtqw;
      string RAUWanVWKb;
      string GjJPRBppah;
      string TPRCGhnojS;
      string QYuFYhUYxt;
      string PylPQeQVCt;
      string SfSJbChRPr;
      string AgmqLgnDpi;
      string gRsgRUcCla;
      string QSmpAjGldW;
      string ACIEtiLtEi;
      string qNeSMAmlqG;
      string Yffobgtxpb;
      string aBZTidJnmi;
      if(RXiHylkrUm == QYuFYhUYxt){JhxCjDmTcA = true;}
      else if(QYuFYhUYxt == RXiHylkrUm){kVcPbPaGFe = true;}
      if(wkEKkdKusi == PylPQeQVCt){wUtWxUVTcM = true;}
      else if(PylPQeQVCt == wkEKkdKusi){zQXrLelPSG = true;}
      if(OfCmPZWKHA == SfSJbChRPr){oOEbIomLii = true;}
      else if(SfSJbChRPr == OfCmPZWKHA){JwWWsZHEwB = true;}
      if(rlNKToLKaV == AgmqLgnDpi){qyzIxqhdEX = true;}
      else if(AgmqLgnDpi == rlNKToLKaV){ZTfOQLHZrK = true;}
      if(IZJebmTmBq == gRsgRUcCla){sZTpeGHCVO = true;}
      else if(gRsgRUcCla == IZJebmTmBq){agTiCwnryc = true;}
      if(hpuXilVwrX == QSmpAjGldW){HoLZttdVtt = true;}
      else if(QSmpAjGldW == hpuXilVwrX){fYHaXnzFWC = true;}
      if(PZkTuJWtqw == ACIEtiLtEi){PbjsIxVkZG = true;}
      else if(ACIEtiLtEi == PZkTuJWtqw){IWJDEfkIaA = true;}
      if(RAUWanVWKb == qNeSMAmlqG){lrOETOtNxB = true;}
      if(GjJPRBppah == Yffobgtxpb){hjoUaBmYOC = true;}
      if(TPRCGhnojS == aBZTidJnmi){MMjKHRoahh = true;}
      while(qNeSMAmlqG == RAUWanVWKb){XMWHfccmUx = true;}
      while(Yffobgtxpb == Yffobgtxpb){lPFTVAMEqb = true;}
      while(aBZTidJnmi == aBZTidJnmi){MCCpCEWPeW = true;}
      if(JhxCjDmTcA == true){JhxCjDmTcA = false;}
      if(wUtWxUVTcM == true){wUtWxUVTcM = false;}
      if(oOEbIomLii == true){oOEbIomLii = false;}
      if(qyzIxqhdEX == true){qyzIxqhdEX = false;}
      if(sZTpeGHCVO == true){sZTpeGHCVO = false;}
      if(HoLZttdVtt == true){HoLZttdVtt = false;}
      if(PbjsIxVkZG == true){PbjsIxVkZG = false;}
      if(lrOETOtNxB == true){lrOETOtNxB = false;}
      if(hjoUaBmYOC == true){hjoUaBmYOC = false;}
      if(MMjKHRoahh == true){MMjKHRoahh = false;}
      if(kVcPbPaGFe == true){kVcPbPaGFe = false;}
      if(zQXrLelPSG == true){zQXrLelPSG = false;}
      if(JwWWsZHEwB == true){JwWWsZHEwB = false;}
      if(ZTfOQLHZrK == true){ZTfOQLHZrK = false;}
      if(agTiCwnryc == true){agTiCwnryc = false;}
      if(fYHaXnzFWC == true){fYHaXnzFWC = false;}
      if(IWJDEfkIaA == true){IWJDEfkIaA = false;}
      if(XMWHfccmUx == true){XMWHfccmUx = false;}
      if(lPFTVAMEqb == true){lPFTVAMEqb = false;}
      if(MCCpCEWPeW == true){MCCpCEWPeW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BFPWRGRMCD
{ 
  void AURTZHXfUZ()
  { 
      bool YBrIbOQEKk = false;
      bool DuGDBGJUGI = false;
      bool mkHtMxoOQp = false;
      bool hTnSuZHmrl = false;
      bool nOfdEDXAWE = false;
      bool kXseqmtywe = false;
      bool ZCmTCiGnHb = false;
      bool zWcUUYFdoJ = false;
      bool ZnqMFKaJbH = false;
      bool fJqMLlbLaV = false;
      bool wisuEOuYKR = false;
      bool hPIlElKZOr = false;
      bool IxMAupePIh = false;
      bool xsCTMpuwHp = false;
      bool OByJYPAEIZ = false;
      bool aBxiNzWrzO = false;
      bool ifPbUoNoZO = false;
      bool qORXcGyCaf = false;
      bool oaHiHuwTGN = false;
      bool SCwsHilWoi = false;
      string ptVxiSyBGT;
      string BYFxrrUalF;
      string RKJYgdjGgt;
      string LwYBWCTtHx;
      string TOkoaAFNjB;
      string boBBaejxPF;
      string hqULHEAEao;
      string XZSnkDYTyg;
      string XWWeSWuXZq;
      string SWeCPcsZgV;
      string ABmtcBVNPX;
      string GPyihLUosk;
      string JbdiWAuQXI;
      string JzmbfVibBQ;
      string AhHCkCYuUE;
      string HEfuMXXEXc;
      string GFoHNGcWCL;
      string bsmbkbUbxU;
      string bzwTAFSqOI;
      string yeDYKtsAne;
      if(ptVxiSyBGT == ABmtcBVNPX){YBrIbOQEKk = true;}
      else if(ABmtcBVNPX == ptVxiSyBGT){wisuEOuYKR = true;}
      if(BYFxrrUalF == GPyihLUosk){DuGDBGJUGI = true;}
      else if(GPyihLUosk == BYFxrrUalF){hPIlElKZOr = true;}
      if(RKJYgdjGgt == JbdiWAuQXI){mkHtMxoOQp = true;}
      else if(JbdiWAuQXI == RKJYgdjGgt){IxMAupePIh = true;}
      if(LwYBWCTtHx == JzmbfVibBQ){hTnSuZHmrl = true;}
      else if(JzmbfVibBQ == LwYBWCTtHx){xsCTMpuwHp = true;}
      if(TOkoaAFNjB == AhHCkCYuUE){nOfdEDXAWE = true;}
      else if(AhHCkCYuUE == TOkoaAFNjB){OByJYPAEIZ = true;}
      if(boBBaejxPF == HEfuMXXEXc){kXseqmtywe = true;}
      else if(HEfuMXXEXc == boBBaejxPF){aBxiNzWrzO = true;}
      if(hqULHEAEao == GFoHNGcWCL){ZCmTCiGnHb = true;}
      else if(GFoHNGcWCL == hqULHEAEao){ifPbUoNoZO = true;}
      if(XZSnkDYTyg == bsmbkbUbxU){zWcUUYFdoJ = true;}
      if(XWWeSWuXZq == bzwTAFSqOI){ZnqMFKaJbH = true;}
      if(SWeCPcsZgV == yeDYKtsAne){fJqMLlbLaV = true;}
      while(bsmbkbUbxU == XZSnkDYTyg){qORXcGyCaf = true;}
      while(bzwTAFSqOI == bzwTAFSqOI){oaHiHuwTGN = true;}
      while(yeDYKtsAne == yeDYKtsAne){SCwsHilWoi = true;}
      if(YBrIbOQEKk == true){YBrIbOQEKk = false;}
      if(DuGDBGJUGI == true){DuGDBGJUGI = false;}
      if(mkHtMxoOQp == true){mkHtMxoOQp = false;}
      if(hTnSuZHmrl == true){hTnSuZHmrl = false;}
      if(nOfdEDXAWE == true){nOfdEDXAWE = false;}
      if(kXseqmtywe == true){kXseqmtywe = false;}
      if(ZCmTCiGnHb == true){ZCmTCiGnHb = false;}
      if(zWcUUYFdoJ == true){zWcUUYFdoJ = false;}
      if(ZnqMFKaJbH == true){ZnqMFKaJbH = false;}
      if(fJqMLlbLaV == true){fJqMLlbLaV = false;}
      if(wisuEOuYKR == true){wisuEOuYKR = false;}
      if(hPIlElKZOr == true){hPIlElKZOr = false;}
      if(IxMAupePIh == true){IxMAupePIh = false;}
      if(xsCTMpuwHp == true){xsCTMpuwHp = false;}
      if(OByJYPAEIZ == true){OByJYPAEIZ = false;}
      if(aBxiNzWrzO == true){aBxiNzWrzO = false;}
      if(ifPbUoNoZO == true){ifPbUoNoZO = false;}
      if(qORXcGyCaf == true){qORXcGyCaf = false;}
      if(oaHiHuwTGN == true){oaHiHuwTGN = false;}
      if(SCwsHilWoi == true){SCwsHilWoi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NPYNPFEVTP
{ 
  void sjVjLuqNMm()
  { 
      bool jDhGakbrdV = false;
      bool MeWqtWJuPj = false;
      bool hNGZCSspLM = false;
      bool mylxFnOmVL = false;
      bool uIKGmTzsak = false;
      bool hNEYoVxHEH = false;
      bool qkgQiOsYkG = false;
      bool IVYDoYDAlh = false;
      bool SAOZeYtNHi = false;
      bool qGhNUJasWY = false;
      bool aaHUcLoAjQ = false;
      bool SwUWoqWHkK = false;
      bool TfQBPBnLie = false;
      bool yJcNHrrtwT = false;
      bool jscqQtlLYd = false;
      bool mSIMEuJGFa = false;
      bool XdRERJTGOw = false;
      bool ybKRZaCYkU = false;
      bool PblEreBPJL = false;
      bool hknVuGbYYG = false;
      string DQUIWSqdnn;
      string wEUHeAwxjA;
      string XflfrogVkq;
      string nrAZbpFdOE;
      string dCHgUhfzwL;
      string pnktoWdoPh;
      string kUsxzEEufn;
      string uSifVUYEKJ;
      string IgZYAAGFjE;
      string LQNgSJIJhP;
      string dkTIQXFFYT;
      string yZdGYDtUxz;
      string xyKbbdEBML;
      string MOWtfXNQHc;
      string tBfQGlmHHP;
      string OnMhSeZqfl;
      string TDrMHiCiZA;
      string odMTEwRtUo;
      string qwtwxXBnbA;
      string yVjVIqJTIW;
      if(DQUIWSqdnn == dkTIQXFFYT){jDhGakbrdV = true;}
      else if(dkTIQXFFYT == DQUIWSqdnn){aaHUcLoAjQ = true;}
      if(wEUHeAwxjA == yZdGYDtUxz){MeWqtWJuPj = true;}
      else if(yZdGYDtUxz == wEUHeAwxjA){SwUWoqWHkK = true;}
      if(XflfrogVkq == xyKbbdEBML){hNGZCSspLM = true;}
      else if(xyKbbdEBML == XflfrogVkq){TfQBPBnLie = true;}
      if(nrAZbpFdOE == MOWtfXNQHc){mylxFnOmVL = true;}
      else if(MOWtfXNQHc == nrAZbpFdOE){yJcNHrrtwT = true;}
      if(dCHgUhfzwL == tBfQGlmHHP){uIKGmTzsak = true;}
      else if(tBfQGlmHHP == dCHgUhfzwL){jscqQtlLYd = true;}
      if(pnktoWdoPh == OnMhSeZqfl){hNEYoVxHEH = true;}
      else if(OnMhSeZqfl == pnktoWdoPh){mSIMEuJGFa = true;}
      if(kUsxzEEufn == TDrMHiCiZA){qkgQiOsYkG = true;}
      else if(TDrMHiCiZA == kUsxzEEufn){XdRERJTGOw = true;}
      if(uSifVUYEKJ == odMTEwRtUo){IVYDoYDAlh = true;}
      if(IgZYAAGFjE == qwtwxXBnbA){SAOZeYtNHi = true;}
      if(LQNgSJIJhP == yVjVIqJTIW){qGhNUJasWY = true;}
      while(odMTEwRtUo == uSifVUYEKJ){ybKRZaCYkU = true;}
      while(qwtwxXBnbA == qwtwxXBnbA){PblEreBPJL = true;}
      while(yVjVIqJTIW == yVjVIqJTIW){hknVuGbYYG = true;}
      if(jDhGakbrdV == true){jDhGakbrdV = false;}
      if(MeWqtWJuPj == true){MeWqtWJuPj = false;}
      if(hNGZCSspLM == true){hNGZCSspLM = false;}
      if(mylxFnOmVL == true){mylxFnOmVL = false;}
      if(uIKGmTzsak == true){uIKGmTzsak = false;}
      if(hNEYoVxHEH == true){hNEYoVxHEH = false;}
      if(qkgQiOsYkG == true){qkgQiOsYkG = false;}
      if(IVYDoYDAlh == true){IVYDoYDAlh = false;}
      if(SAOZeYtNHi == true){SAOZeYtNHi = false;}
      if(qGhNUJasWY == true){qGhNUJasWY = false;}
      if(aaHUcLoAjQ == true){aaHUcLoAjQ = false;}
      if(SwUWoqWHkK == true){SwUWoqWHkK = false;}
      if(TfQBPBnLie == true){TfQBPBnLie = false;}
      if(yJcNHrrtwT == true){yJcNHrrtwT = false;}
      if(jscqQtlLYd == true){jscqQtlLYd = false;}
      if(mSIMEuJGFa == true){mSIMEuJGFa = false;}
      if(XdRERJTGOw == true){XdRERJTGOw = false;}
      if(ybKRZaCYkU == true){ybKRZaCYkU = false;}
      if(PblEreBPJL == true){PblEreBPJL = false;}
      if(hknVuGbYYG == true){hknVuGbYYG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LAAGQJLSJT
{ 
  void IgTeBSFVNU()
  { 
      bool csrtjlUxfq = false;
      bool JdyOwKUWii = false;
      bool gqxTqrWtxQ = false;
      bool pKhuftVpkk = false;
      bool cOUhBNsCRf = false;
      bool RfySPluXCr = false;
      bool OZzOAzuCiB = false;
      bool nelyFSVPRd = false;
      bool yUbQyKLPft = false;
      bool zxmrVDOGgC = false;
      bool RpTQqmtANw = false;
      bool PfGYttxiPo = false;
      bool mfWoCqqscC = false;
      bool DPhPLHALYL = false;
      bool QLCidTqNya = false;
      bool FfpqOlTeNA = false;
      bool wAWKrAxpNl = false;
      bool skJEYbdmKi = false;
      bool zctBxXZpAZ = false;
      bool mVyYPQnqqd = false;
      string eApBVcqYLb;
      string IiacPOOluj;
      string rBHZJnAUdk;
      string RpGNLoNKCQ;
      string dfOqpKwqbp;
      string NEMMVdrPrg;
      string cWuaKRbMQZ;
      string BDieGMlQiy;
      string qJrmXNctrh;
      string wxSUnGknfY;
      string ijZCnJUhFI;
      string qbgtpTeHCw;
      string ngUidEkOpz;
      string axjJOHipyO;
      string stnipUPXdU;
      string bckikCOqXj;
      string XFrGgsqWfi;
      string joInDsrkrI;
      string nNkVXyLAYL;
      string rrROpmChCw;
      if(eApBVcqYLb == ijZCnJUhFI){csrtjlUxfq = true;}
      else if(ijZCnJUhFI == eApBVcqYLb){RpTQqmtANw = true;}
      if(IiacPOOluj == qbgtpTeHCw){JdyOwKUWii = true;}
      else if(qbgtpTeHCw == IiacPOOluj){PfGYttxiPo = true;}
      if(rBHZJnAUdk == ngUidEkOpz){gqxTqrWtxQ = true;}
      else if(ngUidEkOpz == rBHZJnAUdk){mfWoCqqscC = true;}
      if(RpGNLoNKCQ == axjJOHipyO){pKhuftVpkk = true;}
      else if(axjJOHipyO == RpGNLoNKCQ){DPhPLHALYL = true;}
      if(dfOqpKwqbp == stnipUPXdU){cOUhBNsCRf = true;}
      else if(stnipUPXdU == dfOqpKwqbp){QLCidTqNya = true;}
      if(NEMMVdrPrg == bckikCOqXj){RfySPluXCr = true;}
      else if(bckikCOqXj == NEMMVdrPrg){FfpqOlTeNA = true;}
      if(cWuaKRbMQZ == XFrGgsqWfi){OZzOAzuCiB = true;}
      else if(XFrGgsqWfi == cWuaKRbMQZ){wAWKrAxpNl = true;}
      if(BDieGMlQiy == joInDsrkrI){nelyFSVPRd = true;}
      if(qJrmXNctrh == nNkVXyLAYL){yUbQyKLPft = true;}
      if(wxSUnGknfY == rrROpmChCw){zxmrVDOGgC = true;}
      while(joInDsrkrI == BDieGMlQiy){skJEYbdmKi = true;}
      while(nNkVXyLAYL == nNkVXyLAYL){zctBxXZpAZ = true;}
      while(rrROpmChCw == rrROpmChCw){mVyYPQnqqd = true;}
      if(csrtjlUxfq == true){csrtjlUxfq = false;}
      if(JdyOwKUWii == true){JdyOwKUWii = false;}
      if(gqxTqrWtxQ == true){gqxTqrWtxQ = false;}
      if(pKhuftVpkk == true){pKhuftVpkk = false;}
      if(cOUhBNsCRf == true){cOUhBNsCRf = false;}
      if(RfySPluXCr == true){RfySPluXCr = false;}
      if(OZzOAzuCiB == true){OZzOAzuCiB = false;}
      if(nelyFSVPRd == true){nelyFSVPRd = false;}
      if(yUbQyKLPft == true){yUbQyKLPft = false;}
      if(zxmrVDOGgC == true){zxmrVDOGgC = false;}
      if(RpTQqmtANw == true){RpTQqmtANw = false;}
      if(PfGYttxiPo == true){PfGYttxiPo = false;}
      if(mfWoCqqscC == true){mfWoCqqscC = false;}
      if(DPhPLHALYL == true){DPhPLHALYL = false;}
      if(QLCidTqNya == true){QLCidTqNya = false;}
      if(FfpqOlTeNA == true){FfpqOlTeNA = false;}
      if(wAWKrAxpNl == true){wAWKrAxpNl = false;}
      if(skJEYbdmKi == true){skJEYbdmKi = false;}
      if(zctBxXZpAZ == true){zctBxXZpAZ = false;}
      if(mVyYPQnqqd == true){mVyYPQnqqd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYKGGHTZKG
{ 
  void yJPuRhAXUM()
  { 
      bool fBRGFhBckD = false;
      bool QEthCpTRLc = false;
      bool BpDlyquKdz = false;
      bool UCTrLqoPex = false;
      bool wLfjSnZtZE = false;
      bool SQWFUoxfIO = false;
      bool mqykhNjBWL = false;
      bool ADmOfpKTSK = false;
      bool QAkZfEfNXV = false;
      bool sJHPJEMtBF = false;
      bool DXXODPcIYe = false;
      bool edMxylGXFd = false;
      bool hWdARquWEb = false;
      bool cQRMHsbWVQ = false;
      bool aWnsqPwKRX = false;
      bool ynnXWgtXwM = false;
      bool TGExBNLzpE = false;
      bool JjCoCKhjIB = false;
      bool ukFfcnbtoa = false;
      bool zEZJwUSpqc = false;
      string SpmZeUzKNP;
      string eACAQTmHSX;
      string tcTLUVRUxN;
      string KCpThEFzyK;
      string JKSsWWCDPu;
      string eUNpxpVaEJ;
      string DeMzFcKiSM;
      string OnIIOjJaox;
      string SOFCiooAWr;
      string hdtnGeySmt;
      string MTjDfqLEaM;
      string fulGpoYJQP;
      string mKMadktUCj;
      string lpntkzdBWq;
      string djYJLmrmxQ;
      string FnCWGBHJYt;
      string xqCpaoHqVq;
      string LXlYlDkCOq;
      string rGWkexnQmj;
      string rUbbtmhhiV;
      if(SpmZeUzKNP == MTjDfqLEaM){fBRGFhBckD = true;}
      else if(MTjDfqLEaM == SpmZeUzKNP){DXXODPcIYe = true;}
      if(eACAQTmHSX == fulGpoYJQP){QEthCpTRLc = true;}
      else if(fulGpoYJQP == eACAQTmHSX){edMxylGXFd = true;}
      if(tcTLUVRUxN == mKMadktUCj){BpDlyquKdz = true;}
      else if(mKMadktUCj == tcTLUVRUxN){hWdARquWEb = true;}
      if(KCpThEFzyK == lpntkzdBWq){UCTrLqoPex = true;}
      else if(lpntkzdBWq == KCpThEFzyK){cQRMHsbWVQ = true;}
      if(JKSsWWCDPu == djYJLmrmxQ){wLfjSnZtZE = true;}
      else if(djYJLmrmxQ == JKSsWWCDPu){aWnsqPwKRX = true;}
      if(eUNpxpVaEJ == FnCWGBHJYt){SQWFUoxfIO = true;}
      else if(FnCWGBHJYt == eUNpxpVaEJ){ynnXWgtXwM = true;}
      if(DeMzFcKiSM == xqCpaoHqVq){mqykhNjBWL = true;}
      else if(xqCpaoHqVq == DeMzFcKiSM){TGExBNLzpE = true;}
      if(OnIIOjJaox == LXlYlDkCOq){ADmOfpKTSK = true;}
      if(SOFCiooAWr == rGWkexnQmj){QAkZfEfNXV = true;}
      if(hdtnGeySmt == rUbbtmhhiV){sJHPJEMtBF = true;}
      while(LXlYlDkCOq == OnIIOjJaox){JjCoCKhjIB = true;}
      while(rGWkexnQmj == rGWkexnQmj){ukFfcnbtoa = true;}
      while(rUbbtmhhiV == rUbbtmhhiV){zEZJwUSpqc = true;}
      if(fBRGFhBckD == true){fBRGFhBckD = false;}
      if(QEthCpTRLc == true){QEthCpTRLc = false;}
      if(BpDlyquKdz == true){BpDlyquKdz = false;}
      if(UCTrLqoPex == true){UCTrLqoPex = false;}
      if(wLfjSnZtZE == true){wLfjSnZtZE = false;}
      if(SQWFUoxfIO == true){SQWFUoxfIO = false;}
      if(mqykhNjBWL == true){mqykhNjBWL = false;}
      if(ADmOfpKTSK == true){ADmOfpKTSK = false;}
      if(QAkZfEfNXV == true){QAkZfEfNXV = false;}
      if(sJHPJEMtBF == true){sJHPJEMtBF = false;}
      if(DXXODPcIYe == true){DXXODPcIYe = false;}
      if(edMxylGXFd == true){edMxylGXFd = false;}
      if(hWdARquWEb == true){hWdARquWEb = false;}
      if(cQRMHsbWVQ == true){cQRMHsbWVQ = false;}
      if(aWnsqPwKRX == true){aWnsqPwKRX = false;}
      if(ynnXWgtXwM == true){ynnXWgtXwM = false;}
      if(TGExBNLzpE == true){TGExBNLzpE = false;}
      if(JjCoCKhjIB == true){JjCoCKhjIB = false;}
      if(ukFfcnbtoa == true){ukFfcnbtoa = false;}
      if(zEZJwUSpqc == true){zEZJwUSpqc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YVMVRUNJAJ
{ 
  void EHmdIzfzxk()
  { 
      bool GkIpAKMdsz = false;
      bool FfKNTtoeTa = false;
      bool EeCySSemax = false;
      bool UFthMHefUx = false;
      bool hDAZOtEczP = false;
      bool yOundahJXg = false;
      bool fZCueAlcAM = false;
      bool PIJWsBecjX = false;
      bool OCnKyGJFEk = false;
      bool YUImQIAEuO = false;
      bool HablApEYuc = false;
      bool wFZzSdkqxX = false;
      bool pgXOntzWFj = false;
      bool AZhVQmZCKI = false;
      bool BkJboTuIUm = false;
      bool WIHWXaDMyG = false;
      bool phSKbVWDie = false;
      bool DigoWFWwZU = false;
      bool yqBSNqSLxo = false;
      bool jMDDRTRzzS = false;
      string gmBrTmDdIw;
      string WKsWgaoMyi;
      string IFFguGIHuo;
      string qQnafHtlJl;
      string UnNTaLDEEx;
      string AWReEagTxN;
      string duiTFFWRqY;
      string fDDMNTqlGi;
      string CECxoTyJWE;
      string aaouHYFtOU;
      string nkNeRwTEQk;
      string juNNKYrldk;
      string HNulyFOHEn;
      string OxWluQqWer;
      string AsrkUeMaji;
      string fTPdMapbgM;
      string hMAbVlYbSs;
      string hUGlkNUJQT;
      string rmWVIuhsYT;
      string aOpSKmsPPh;
      if(gmBrTmDdIw == nkNeRwTEQk){GkIpAKMdsz = true;}
      else if(nkNeRwTEQk == gmBrTmDdIw){HablApEYuc = true;}
      if(WKsWgaoMyi == juNNKYrldk){FfKNTtoeTa = true;}
      else if(juNNKYrldk == WKsWgaoMyi){wFZzSdkqxX = true;}
      if(IFFguGIHuo == HNulyFOHEn){EeCySSemax = true;}
      else if(HNulyFOHEn == IFFguGIHuo){pgXOntzWFj = true;}
      if(qQnafHtlJl == OxWluQqWer){UFthMHefUx = true;}
      else if(OxWluQqWer == qQnafHtlJl){AZhVQmZCKI = true;}
      if(UnNTaLDEEx == AsrkUeMaji){hDAZOtEczP = true;}
      else if(AsrkUeMaji == UnNTaLDEEx){BkJboTuIUm = true;}
      if(AWReEagTxN == fTPdMapbgM){yOundahJXg = true;}
      else if(fTPdMapbgM == AWReEagTxN){WIHWXaDMyG = true;}
      if(duiTFFWRqY == hMAbVlYbSs){fZCueAlcAM = true;}
      else if(hMAbVlYbSs == duiTFFWRqY){phSKbVWDie = true;}
      if(fDDMNTqlGi == hUGlkNUJQT){PIJWsBecjX = true;}
      if(CECxoTyJWE == rmWVIuhsYT){OCnKyGJFEk = true;}
      if(aaouHYFtOU == aOpSKmsPPh){YUImQIAEuO = true;}
      while(hUGlkNUJQT == fDDMNTqlGi){DigoWFWwZU = true;}
      while(rmWVIuhsYT == rmWVIuhsYT){yqBSNqSLxo = true;}
      while(aOpSKmsPPh == aOpSKmsPPh){jMDDRTRzzS = true;}
      if(GkIpAKMdsz == true){GkIpAKMdsz = false;}
      if(FfKNTtoeTa == true){FfKNTtoeTa = false;}
      if(EeCySSemax == true){EeCySSemax = false;}
      if(UFthMHefUx == true){UFthMHefUx = false;}
      if(hDAZOtEczP == true){hDAZOtEczP = false;}
      if(yOundahJXg == true){yOundahJXg = false;}
      if(fZCueAlcAM == true){fZCueAlcAM = false;}
      if(PIJWsBecjX == true){PIJWsBecjX = false;}
      if(OCnKyGJFEk == true){OCnKyGJFEk = false;}
      if(YUImQIAEuO == true){YUImQIAEuO = false;}
      if(HablApEYuc == true){HablApEYuc = false;}
      if(wFZzSdkqxX == true){wFZzSdkqxX = false;}
      if(pgXOntzWFj == true){pgXOntzWFj = false;}
      if(AZhVQmZCKI == true){AZhVQmZCKI = false;}
      if(BkJboTuIUm == true){BkJboTuIUm = false;}
      if(WIHWXaDMyG == true){WIHWXaDMyG = false;}
      if(phSKbVWDie == true){phSKbVWDie = false;}
      if(DigoWFWwZU == true){DigoWFWwZU = false;}
      if(yqBSNqSLxo == true){yqBSNqSLxo = false;}
      if(jMDDRTRzzS == true){jMDDRTRzzS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AQGMJVCHJR
{ 
  void GphTlHiElw()
  { 
      bool ZZusUodEtc = false;
      bool sLMFcCyeip = false;
      bool piptXZUEHk = false;
      bool PfEaCzOUVL = false;
      bool JithgFrNiz = false;
      bool xtGftqjAUu = false;
      bool TZwJNNHkDc = false;
      bool ncIWfHnINR = false;
      bool gHUHnVZYfK = false;
      bool PNzarjmkTT = false;
      bool yHJFLTkizm = false;
      bool CbmDNLEoVr = false;
      bool miErMZdhew = false;
      bool TDntTZxPuT = false;
      bool jqYrInawNf = false;
      bool exPbfPCRrl = false;
      bool pDDDSzmsjm = false;
      bool NosBHwJLiY = false;
      bool zhTzQWmMND = false;
      bool XfWJdfmVZJ = false;
      string RUnwZBXeHI;
      string QYZqQZhLDH;
      string kxBbmQJbfj;
      string CXrkQERikB;
      string MaJVuoBcTL;
      string jjOHXTSLIJ;
      string qwzXGsfnZL;
      string HzZBtKnefy;
      string PgHTzRIkNw;
      string lGZbJQalPC;
      string JMCHEkJNMN;
      string fneKsJnfXn;
      string jtacZBYxqc;
      string iBPdoDeAPN;
      string HuYAPyaPiA;
      string cuNaSOlZgD;
      string LMViddXBUo;
      string enQJfoVZMb;
      string ZJOqAnnoLZ;
      string RFSMCuYoVk;
      if(RUnwZBXeHI == JMCHEkJNMN){ZZusUodEtc = true;}
      else if(JMCHEkJNMN == RUnwZBXeHI){yHJFLTkizm = true;}
      if(QYZqQZhLDH == fneKsJnfXn){sLMFcCyeip = true;}
      else if(fneKsJnfXn == QYZqQZhLDH){CbmDNLEoVr = true;}
      if(kxBbmQJbfj == jtacZBYxqc){piptXZUEHk = true;}
      else if(jtacZBYxqc == kxBbmQJbfj){miErMZdhew = true;}
      if(CXrkQERikB == iBPdoDeAPN){PfEaCzOUVL = true;}
      else if(iBPdoDeAPN == CXrkQERikB){TDntTZxPuT = true;}
      if(MaJVuoBcTL == HuYAPyaPiA){JithgFrNiz = true;}
      else if(HuYAPyaPiA == MaJVuoBcTL){jqYrInawNf = true;}
      if(jjOHXTSLIJ == cuNaSOlZgD){xtGftqjAUu = true;}
      else if(cuNaSOlZgD == jjOHXTSLIJ){exPbfPCRrl = true;}
      if(qwzXGsfnZL == LMViddXBUo){TZwJNNHkDc = true;}
      else if(LMViddXBUo == qwzXGsfnZL){pDDDSzmsjm = true;}
      if(HzZBtKnefy == enQJfoVZMb){ncIWfHnINR = true;}
      if(PgHTzRIkNw == ZJOqAnnoLZ){gHUHnVZYfK = true;}
      if(lGZbJQalPC == RFSMCuYoVk){PNzarjmkTT = true;}
      while(enQJfoVZMb == HzZBtKnefy){NosBHwJLiY = true;}
      while(ZJOqAnnoLZ == ZJOqAnnoLZ){zhTzQWmMND = true;}
      while(RFSMCuYoVk == RFSMCuYoVk){XfWJdfmVZJ = true;}
      if(ZZusUodEtc == true){ZZusUodEtc = false;}
      if(sLMFcCyeip == true){sLMFcCyeip = false;}
      if(piptXZUEHk == true){piptXZUEHk = false;}
      if(PfEaCzOUVL == true){PfEaCzOUVL = false;}
      if(JithgFrNiz == true){JithgFrNiz = false;}
      if(xtGftqjAUu == true){xtGftqjAUu = false;}
      if(TZwJNNHkDc == true){TZwJNNHkDc = false;}
      if(ncIWfHnINR == true){ncIWfHnINR = false;}
      if(gHUHnVZYfK == true){gHUHnVZYfK = false;}
      if(PNzarjmkTT == true){PNzarjmkTT = false;}
      if(yHJFLTkizm == true){yHJFLTkizm = false;}
      if(CbmDNLEoVr == true){CbmDNLEoVr = false;}
      if(miErMZdhew == true){miErMZdhew = false;}
      if(TDntTZxPuT == true){TDntTZxPuT = false;}
      if(jqYrInawNf == true){jqYrInawNf = false;}
      if(exPbfPCRrl == true){exPbfPCRrl = false;}
      if(pDDDSzmsjm == true){pDDDSzmsjm = false;}
      if(NosBHwJLiY == true){NosBHwJLiY = false;}
      if(zhTzQWmMND == true){zhTzQWmMND = false;}
      if(XfWJdfmVZJ == true){XfWJdfmVZJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NEKPZLKJGW
{ 
  void PhbyOpDEuj()
  { 
      bool oNHGYzWTIy = false;
      bool HgOFgVMXSo = false;
      bool bmpBlGuTrC = false;
      bool QwuWmBfekY = false;
      bool fTTQqycExJ = false;
      bool sxmRYBWGUS = false;
      bool ECaGgLlqRe = false;
      bool phlsIISZJm = false;
      bool cpWiJSJdyk = false;
      bool dZJSUdrNif = false;
      bool LllRTKLsIQ = false;
      bool hxxhoNfrwO = false;
      bool BIrgAQYSXe = false;
      bool PFpcbqEEOy = false;
      bool GPVhCgbbdH = false;
      bool yzQUdCsFRD = false;
      bool lrUcAcGTGy = false;
      bool IadyHlmKdT = false;
      bool nwoQgQnVzY = false;
      bool yzmLLNurgZ = false;
      string sgmYnOUQZX;
      string ToRBEJIFLj;
      string lHqHuFgSoP;
      string rMVzzGDtnf;
      string EUSNhcEbMk;
      string TbtBhloech;
      string gCbKfHTSBx;
      string GNQffQodZS;
      string BEFEuQRTQN;
      string QXRGzBsHhZ;
      string JkaOdFKOVQ;
      string wLFJgbwXOP;
      string ozBnghuKgd;
      string XguzJPdqZp;
      string FDxzQESHYW;
      string EUsSjJilgw;
      string JzhrsPPFAR;
      string yFyYJlCBXb;
      string OmlJYDncOz;
      string fqJdfGVFGA;
      if(sgmYnOUQZX == JkaOdFKOVQ){oNHGYzWTIy = true;}
      else if(JkaOdFKOVQ == sgmYnOUQZX){LllRTKLsIQ = true;}
      if(ToRBEJIFLj == wLFJgbwXOP){HgOFgVMXSo = true;}
      else if(wLFJgbwXOP == ToRBEJIFLj){hxxhoNfrwO = true;}
      if(lHqHuFgSoP == ozBnghuKgd){bmpBlGuTrC = true;}
      else if(ozBnghuKgd == lHqHuFgSoP){BIrgAQYSXe = true;}
      if(rMVzzGDtnf == XguzJPdqZp){QwuWmBfekY = true;}
      else if(XguzJPdqZp == rMVzzGDtnf){PFpcbqEEOy = true;}
      if(EUSNhcEbMk == FDxzQESHYW){fTTQqycExJ = true;}
      else if(FDxzQESHYW == EUSNhcEbMk){GPVhCgbbdH = true;}
      if(TbtBhloech == EUsSjJilgw){sxmRYBWGUS = true;}
      else if(EUsSjJilgw == TbtBhloech){yzQUdCsFRD = true;}
      if(gCbKfHTSBx == JzhrsPPFAR){ECaGgLlqRe = true;}
      else if(JzhrsPPFAR == gCbKfHTSBx){lrUcAcGTGy = true;}
      if(GNQffQodZS == yFyYJlCBXb){phlsIISZJm = true;}
      if(BEFEuQRTQN == OmlJYDncOz){cpWiJSJdyk = true;}
      if(QXRGzBsHhZ == fqJdfGVFGA){dZJSUdrNif = true;}
      while(yFyYJlCBXb == GNQffQodZS){IadyHlmKdT = true;}
      while(OmlJYDncOz == OmlJYDncOz){nwoQgQnVzY = true;}
      while(fqJdfGVFGA == fqJdfGVFGA){yzmLLNurgZ = true;}
      if(oNHGYzWTIy == true){oNHGYzWTIy = false;}
      if(HgOFgVMXSo == true){HgOFgVMXSo = false;}
      if(bmpBlGuTrC == true){bmpBlGuTrC = false;}
      if(QwuWmBfekY == true){QwuWmBfekY = false;}
      if(fTTQqycExJ == true){fTTQqycExJ = false;}
      if(sxmRYBWGUS == true){sxmRYBWGUS = false;}
      if(ECaGgLlqRe == true){ECaGgLlqRe = false;}
      if(phlsIISZJm == true){phlsIISZJm = false;}
      if(cpWiJSJdyk == true){cpWiJSJdyk = false;}
      if(dZJSUdrNif == true){dZJSUdrNif = false;}
      if(LllRTKLsIQ == true){LllRTKLsIQ = false;}
      if(hxxhoNfrwO == true){hxxhoNfrwO = false;}
      if(BIrgAQYSXe == true){BIrgAQYSXe = false;}
      if(PFpcbqEEOy == true){PFpcbqEEOy = false;}
      if(GPVhCgbbdH == true){GPVhCgbbdH = false;}
      if(yzQUdCsFRD == true){yzQUdCsFRD = false;}
      if(lrUcAcGTGy == true){lrUcAcGTGy = false;}
      if(IadyHlmKdT == true){IadyHlmKdT = false;}
      if(nwoQgQnVzY == true){nwoQgQnVzY = false;}
      if(yzmLLNurgZ == true){yzmLLNurgZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBJPZREPDS
{ 
  void yujQwTglAM()
  { 
      bool nLyfNJktKZ = false;
      bool MLfLgAhzTI = false;
      bool iAlBpyYaIQ = false;
      bool lqARgzgkAl = false;
      bool nGcmpTjIIh = false;
      bool pTzPtmYxpO = false;
      bool jJlsmVKNeg = false;
      bool SwyhTbXzLV = false;
      bool OPRaZRqkXs = false;
      bool ajulBdUizT = false;
      bool JVdbPtURuR = false;
      bool PYlUzUrLSU = false;
      bool dZpkGhAMfp = false;
      bool HnAqMrlpKf = false;
      bool xZoFcByalg = false;
      bool lJQdpierUg = false;
      bool sHkFKbYuHH = false;
      bool iCAmXEjjIE = false;
      bool jZazExWVBc = false;
      bool MsUdlonjuA = false;
      string PBCPyAaXoe;
      string ormqaVMLwP;
      string WJYBwiODcF;
      string WQCwsdAzDV;
      string UucWqFEjYh;
      string bceHiFcATP;
      string lXtjIYoqxx;
      string UNIatbgCKp;
      string ddducskuMm;
      string BAenjwBrOS;
      string QNlbMOUEMH;
      string YZpckHtzGO;
      string msdJuUhUpx;
      string anmqZPrBhO;
      string YgiFOaJBCb;
      string CBlAeWjbgr;
      string fANOgkmyDV;
      string OsQqpFKYuU;
      string KfRNuYBmMC;
      string fQUphYTTXc;
      if(PBCPyAaXoe == QNlbMOUEMH){nLyfNJktKZ = true;}
      else if(QNlbMOUEMH == PBCPyAaXoe){JVdbPtURuR = true;}
      if(ormqaVMLwP == YZpckHtzGO){MLfLgAhzTI = true;}
      else if(YZpckHtzGO == ormqaVMLwP){PYlUzUrLSU = true;}
      if(WJYBwiODcF == msdJuUhUpx){iAlBpyYaIQ = true;}
      else if(msdJuUhUpx == WJYBwiODcF){dZpkGhAMfp = true;}
      if(WQCwsdAzDV == anmqZPrBhO){lqARgzgkAl = true;}
      else if(anmqZPrBhO == WQCwsdAzDV){HnAqMrlpKf = true;}
      if(UucWqFEjYh == YgiFOaJBCb){nGcmpTjIIh = true;}
      else if(YgiFOaJBCb == UucWqFEjYh){xZoFcByalg = true;}
      if(bceHiFcATP == CBlAeWjbgr){pTzPtmYxpO = true;}
      else if(CBlAeWjbgr == bceHiFcATP){lJQdpierUg = true;}
      if(lXtjIYoqxx == fANOgkmyDV){jJlsmVKNeg = true;}
      else if(fANOgkmyDV == lXtjIYoqxx){sHkFKbYuHH = true;}
      if(UNIatbgCKp == OsQqpFKYuU){SwyhTbXzLV = true;}
      if(ddducskuMm == KfRNuYBmMC){OPRaZRqkXs = true;}
      if(BAenjwBrOS == fQUphYTTXc){ajulBdUizT = true;}
      while(OsQqpFKYuU == UNIatbgCKp){iCAmXEjjIE = true;}
      while(KfRNuYBmMC == KfRNuYBmMC){jZazExWVBc = true;}
      while(fQUphYTTXc == fQUphYTTXc){MsUdlonjuA = true;}
      if(nLyfNJktKZ == true){nLyfNJktKZ = false;}
      if(MLfLgAhzTI == true){MLfLgAhzTI = false;}
      if(iAlBpyYaIQ == true){iAlBpyYaIQ = false;}
      if(lqARgzgkAl == true){lqARgzgkAl = false;}
      if(nGcmpTjIIh == true){nGcmpTjIIh = false;}
      if(pTzPtmYxpO == true){pTzPtmYxpO = false;}
      if(jJlsmVKNeg == true){jJlsmVKNeg = false;}
      if(SwyhTbXzLV == true){SwyhTbXzLV = false;}
      if(OPRaZRqkXs == true){OPRaZRqkXs = false;}
      if(ajulBdUizT == true){ajulBdUizT = false;}
      if(JVdbPtURuR == true){JVdbPtURuR = false;}
      if(PYlUzUrLSU == true){PYlUzUrLSU = false;}
      if(dZpkGhAMfp == true){dZpkGhAMfp = false;}
      if(HnAqMrlpKf == true){HnAqMrlpKf = false;}
      if(xZoFcByalg == true){xZoFcByalg = false;}
      if(lJQdpierUg == true){lJQdpierUg = false;}
      if(sHkFKbYuHH == true){sHkFKbYuHH = false;}
      if(iCAmXEjjIE == true){iCAmXEjjIE = false;}
      if(jZazExWVBc == true){jZazExWVBc = false;}
      if(MsUdlonjuA == true){MsUdlonjuA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDNJJAQLNI
{ 
  void crIrloMkRR()
  { 
      bool uShBoVBjoH = false;
      bool ZzOPaABXeF = false;
      bool gEXTwTsGDR = false;
      bool UuicHlPlxW = false;
      bool UJHQBaobXg = false;
      bool WDkKKquNEV = false;
      bool ctgWldPlHn = false;
      bool kPaHkWwGSV = false;
      bool dQhVuQKYRQ = false;
      bool qCgatZckdW = false;
      bool KCUiwHcdYm = false;
      bool tnuirLMKaV = false;
      bool TpTpxhhzNK = false;
      bool tLcuKawzZn = false;
      bool ngzdVDHyii = false;
      bool NRJIDThdlN = false;
      bool YdQOsiLAXQ = false;
      bool OMjmgmqpUs = false;
      bool ajQewbBTqq = false;
      bool rSMMPKQkkl = false;
      string IrazMGBNWE;
      string MnXBpoJIXZ;
      string lOEjqBhbsx;
      string pgfeDNftey;
      string aNMuTskVwL;
      string odjVesmpHL;
      string YZTZOfIsyb;
      string JOdZzXCJQy;
      string QMehHLwJAJ;
      string aomSZAsmgm;
      string kqXUBazKVG;
      string qdZJuMtlRC;
      string izsnBUbLAy;
      string dPbcNYnKfg;
      string MlmsSxPdXN;
      string FHUeElyjSg;
      string znKWcaBwuV;
      string XjFkpwLzUD;
      string FymlrWtxYb;
      string ZEqzhXbPQq;
      if(IrazMGBNWE == kqXUBazKVG){uShBoVBjoH = true;}
      else if(kqXUBazKVG == IrazMGBNWE){KCUiwHcdYm = true;}
      if(MnXBpoJIXZ == qdZJuMtlRC){ZzOPaABXeF = true;}
      else if(qdZJuMtlRC == MnXBpoJIXZ){tnuirLMKaV = true;}
      if(lOEjqBhbsx == izsnBUbLAy){gEXTwTsGDR = true;}
      else if(izsnBUbLAy == lOEjqBhbsx){TpTpxhhzNK = true;}
      if(pgfeDNftey == dPbcNYnKfg){UuicHlPlxW = true;}
      else if(dPbcNYnKfg == pgfeDNftey){tLcuKawzZn = true;}
      if(aNMuTskVwL == MlmsSxPdXN){UJHQBaobXg = true;}
      else if(MlmsSxPdXN == aNMuTskVwL){ngzdVDHyii = true;}
      if(odjVesmpHL == FHUeElyjSg){WDkKKquNEV = true;}
      else if(FHUeElyjSg == odjVesmpHL){NRJIDThdlN = true;}
      if(YZTZOfIsyb == znKWcaBwuV){ctgWldPlHn = true;}
      else if(znKWcaBwuV == YZTZOfIsyb){YdQOsiLAXQ = true;}
      if(JOdZzXCJQy == XjFkpwLzUD){kPaHkWwGSV = true;}
      if(QMehHLwJAJ == FymlrWtxYb){dQhVuQKYRQ = true;}
      if(aomSZAsmgm == ZEqzhXbPQq){qCgatZckdW = true;}
      while(XjFkpwLzUD == JOdZzXCJQy){OMjmgmqpUs = true;}
      while(FymlrWtxYb == FymlrWtxYb){ajQewbBTqq = true;}
      while(ZEqzhXbPQq == ZEqzhXbPQq){rSMMPKQkkl = true;}
      if(uShBoVBjoH == true){uShBoVBjoH = false;}
      if(ZzOPaABXeF == true){ZzOPaABXeF = false;}
      if(gEXTwTsGDR == true){gEXTwTsGDR = false;}
      if(UuicHlPlxW == true){UuicHlPlxW = false;}
      if(UJHQBaobXg == true){UJHQBaobXg = false;}
      if(WDkKKquNEV == true){WDkKKquNEV = false;}
      if(ctgWldPlHn == true){ctgWldPlHn = false;}
      if(kPaHkWwGSV == true){kPaHkWwGSV = false;}
      if(dQhVuQKYRQ == true){dQhVuQKYRQ = false;}
      if(qCgatZckdW == true){qCgatZckdW = false;}
      if(KCUiwHcdYm == true){KCUiwHcdYm = false;}
      if(tnuirLMKaV == true){tnuirLMKaV = false;}
      if(TpTpxhhzNK == true){TpTpxhhzNK = false;}
      if(tLcuKawzZn == true){tLcuKawzZn = false;}
      if(ngzdVDHyii == true){ngzdVDHyii = false;}
      if(NRJIDThdlN == true){NRJIDThdlN = false;}
      if(YdQOsiLAXQ == true){YdQOsiLAXQ = false;}
      if(OMjmgmqpUs == true){OMjmgmqpUs = false;}
      if(ajQewbBTqq == true){ajQewbBTqq = false;}
      if(rSMMPKQkkl == true){rSMMPKQkkl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ANPJZIOVOB
{ 
  void lRbDlMMMUD()
  { 
      bool OsARexUehg = false;
      bool MEUuGCphKe = false;
      bool HwePPpBelA = false;
      bool TKiHhXWlTa = false;
      bool pxwuWQSoGH = false;
      bool cYICkSOjCn = false;
      bool upshNBUNNi = false;
      bool eENjnKzirz = false;
      bool XMXdWtCgVP = false;
      bool JliffAEOhV = false;
      bool uFbXbYLYNa = false;
      bool SeqDPiROKS = false;
      bool ynqyYrVgDn = false;
      bool FjBWDSkzCy = false;
      bool hdSuwdufPw = false;
      bool ioDOWHNcyi = false;
      bool CdUZUhcUzx = false;
      bool yRMMkUUuBt = false;
      bool xpRHFQflAw = false;
      bool EHASuEJsaN = false;
      string QdLcAGmpkw;
      string QYqKHuEeCa;
      string UUCQBdHRfb;
      string yYuRNYkExw;
      string TCNjMBgxMB;
      string whuzfuatbV;
      string yUJJyqcYxi;
      string JzhGHRHSEA;
      string xJFdePcukR;
      string xqbbxysEkU;
      string YHAcqwAorO;
      string nIpbYnOedi;
      string NgmekSXGII;
      string YDgiaoJbmh;
      string OnDWdoAACJ;
      string jNZCGqUVqY;
      string YtgjpkaGAj;
      string elruUZdPAw;
      string RWDzYKcebj;
      string UnjNJTGSgs;
      if(QdLcAGmpkw == YHAcqwAorO){OsARexUehg = true;}
      else if(YHAcqwAorO == QdLcAGmpkw){uFbXbYLYNa = true;}
      if(QYqKHuEeCa == nIpbYnOedi){MEUuGCphKe = true;}
      else if(nIpbYnOedi == QYqKHuEeCa){SeqDPiROKS = true;}
      if(UUCQBdHRfb == NgmekSXGII){HwePPpBelA = true;}
      else if(NgmekSXGII == UUCQBdHRfb){ynqyYrVgDn = true;}
      if(yYuRNYkExw == YDgiaoJbmh){TKiHhXWlTa = true;}
      else if(YDgiaoJbmh == yYuRNYkExw){FjBWDSkzCy = true;}
      if(TCNjMBgxMB == OnDWdoAACJ){pxwuWQSoGH = true;}
      else if(OnDWdoAACJ == TCNjMBgxMB){hdSuwdufPw = true;}
      if(whuzfuatbV == jNZCGqUVqY){cYICkSOjCn = true;}
      else if(jNZCGqUVqY == whuzfuatbV){ioDOWHNcyi = true;}
      if(yUJJyqcYxi == YtgjpkaGAj){upshNBUNNi = true;}
      else if(YtgjpkaGAj == yUJJyqcYxi){CdUZUhcUzx = true;}
      if(JzhGHRHSEA == elruUZdPAw){eENjnKzirz = true;}
      if(xJFdePcukR == RWDzYKcebj){XMXdWtCgVP = true;}
      if(xqbbxysEkU == UnjNJTGSgs){JliffAEOhV = true;}
      while(elruUZdPAw == JzhGHRHSEA){yRMMkUUuBt = true;}
      while(RWDzYKcebj == RWDzYKcebj){xpRHFQflAw = true;}
      while(UnjNJTGSgs == UnjNJTGSgs){EHASuEJsaN = true;}
      if(OsARexUehg == true){OsARexUehg = false;}
      if(MEUuGCphKe == true){MEUuGCphKe = false;}
      if(HwePPpBelA == true){HwePPpBelA = false;}
      if(TKiHhXWlTa == true){TKiHhXWlTa = false;}
      if(pxwuWQSoGH == true){pxwuWQSoGH = false;}
      if(cYICkSOjCn == true){cYICkSOjCn = false;}
      if(upshNBUNNi == true){upshNBUNNi = false;}
      if(eENjnKzirz == true){eENjnKzirz = false;}
      if(XMXdWtCgVP == true){XMXdWtCgVP = false;}
      if(JliffAEOhV == true){JliffAEOhV = false;}
      if(uFbXbYLYNa == true){uFbXbYLYNa = false;}
      if(SeqDPiROKS == true){SeqDPiROKS = false;}
      if(ynqyYrVgDn == true){ynqyYrVgDn = false;}
      if(FjBWDSkzCy == true){FjBWDSkzCy = false;}
      if(hdSuwdufPw == true){hdSuwdufPw = false;}
      if(ioDOWHNcyi == true){ioDOWHNcyi = false;}
      if(CdUZUhcUzx == true){CdUZUhcUzx = false;}
      if(yRMMkUUuBt == true){yRMMkUUuBt = false;}
      if(xpRHFQflAw == true){xpRHFQflAw = false;}
      if(EHASuEJsaN == true){EHASuEJsaN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HPTMSALYGX
{ 
  void MisRpEMxbf()
  { 
      bool fEjSweOzQZ = false;
      bool PGzeECVBkH = false;
      bool VOJIhiRJZs = false;
      bool qGagrCGohh = false;
      bool nahDIGxMmN = false;
      bool thCMaQtakM = false;
      bool MFYXiJeRmB = false;
      bool ugSCSugFAb = false;
      bool lEVMyIENGa = false;
      bool HfEUUiBKUz = false;
      bool aeZlRNOzte = false;
      bool ioaJaHiMYa = false;
      bool EQLLsPbyhi = false;
      bool tWkAAGejtj = false;
      bool sETaqSEutM = false;
      bool AnkttJTNrB = false;
      bool kQRKkMDZIU = false;
      bool czSngAxjTa = false;
      bool LgDUiFkqFp = false;
      bool mQqryclIoe = false;
      string TnrZxuyNUz;
      string WwIuZQTTMG;
      string gFsDhxJfqI;
      string ueeaSbCaXV;
      string LqBlgHIeRa;
      string uxdtSOuoqz;
      string lSVMEqQgby;
      string NruqtoDHVZ;
      string odOQMxBkIE;
      string gMiYjsVogp;
      string paCTMCBlzd;
      string KmTRJHEFzG;
      string ofYXQAJWGB;
      string TOZeiOatDJ;
      string wOkdsssROb;
      string nPoaAKBdCL;
      string sefxKwNnhu;
      string fJBpKZtueX;
      string HqIdMDZydY;
      string MxrrPQimTx;
      if(TnrZxuyNUz == paCTMCBlzd){fEjSweOzQZ = true;}
      else if(paCTMCBlzd == TnrZxuyNUz){aeZlRNOzte = true;}
      if(WwIuZQTTMG == KmTRJHEFzG){PGzeECVBkH = true;}
      else if(KmTRJHEFzG == WwIuZQTTMG){ioaJaHiMYa = true;}
      if(gFsDhxJfqI == ofYXQAJWGB){VOJIhiRJZs = true;}
      else if(ofYXQAJWGB == gFsDhxJfqI){EQLLsPbyhi = true;}
      if(ueeaSbCaXV == TOZeiOatDJ){qGagrCGohh = true;}
      else if(TOZeiOatDJ == ueeaSbCaXV){tWkAAGejtj = true;}
      if(LqBlgHIeRa == wOkdsssROb){nahDIGxMmN = true;}
      else if(wOkdsssROb == LqBlgHIeRa){sETaqSEutM = true;}
      if(uxdtSOuoqz == nPoaAKBdCL){thCMaQtakM = true;}
      else if(nPoaAKBdCL == uxdtSOuoqz){AnkttJTNrB = true;}
      if(lSVMEqQgby == sefxKwNnhu){MFYXiJeRmB = true;}
      else if(sefxKwNnhu == lSVMEqQgby){kQRKkMDZIU = true;}
      if(NruqtoDHVZ == fJBpKZtueX){ugSCSugFAb = true;}
      if(odOQMxBkIE == HqIdMDZydY){lEVMyIENGa = true;}
      if(gMiYjsVogp == MxrrPQimTx){HfEUUiBKUz = true;}
      while(fJBpKZtueX == NruqtoDHVZ){czSngAxjTa = true;}
      while(HqIdMDZydY == HqIdMDZydY){LgDUiFkqFp = true;}
      while(MxrrPQimTx == MxrrPQimTx){mQqryclIoe = true;}
      if(fEjSweOzQZ == true){fEjSweOzQZ = false;}
      if(PGzeECVBkH == true){PGzeECVBkH = false;}
      if(VOJIhiRJZs == true){VOJIhiRJZs = false;}
      if(qGagrCGohh == true){qGagrCGohh = false;}
      if(nahDIGxMmN == true){nahDIGxMmN = false;}
      if(thCMaQtakM == true){thCMaQtakM = false;}
      if(MFYXiJeRmB == true){MFYXiJeRmB = false;}
      if(ugSCSugFAb == true){ugSCSugFAb = false;}
      if(lEVMyIENGa == true){lEVMyIENGa = false;}
      if(HfEUUiBKUz == true){HfEUUiBKUz = false;}
      if(aeZlRNOzte == true){aeZlRNOzte = false;}
      if(ioaJaHiMYa == true){ioaJaHiMYa = false;}
      if(EQLLsPbyhi == true){EQLLsPbyhi = false;}
      if(tWkAAGejtj == true){tWkAAGejtj = false;}
      if(sETaqSEutM == true){sETaqSEutM = false;}
      if(AnkttJTNrB == true){AnkttJTNrB = false;}
      if(kQRKkMDZIU == true){kQRKkMDZIU = false;}
      if(czSngAxjTa == true){czSngAxjTa = false;}
      if(LgDUiFkqFp == true){LgDUiFkqFp = false;}
      if(mQqryclIoe == true){mQqryclIoe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CLUGQTXLOB
{ 
  void WqEBRUhNHe()
  { 
      bool xPksrKaDsM = false;
      bool udjroZwnoR = false;
      bool euRlliLpVt = false;
      bool fSetKrFHOf = false;
      bool NzZfTpREWj = false;
      bool tfmDRByyGI = false;
      bool ykgzgbzpgw = false;
      bool ToYJDfVkSw = false;
      bool RGTkAzfbcI = false;
      bool sGBFgcRazq = false;
      bool pbXZQEGdzk = false;
      bool fMfJqrRuzg = false;
      bool uXNXCMnTba = false;
      bool NukbGoisUu = false;
      bool rCbqcgarOo = false;
      bool KVbRuSOzWD = false;
      bool QmBXXkbEDB = false;
      bool IYaDnsuWtV = false;
      bool kwEmQrSSfn = false;
      bool aiVRdEBETr = false;
      string DkLBmoOuVB;
      string PRETmOWOUf;
      string sEUOtgwnwo;
      string nGRdypmzKn;
      string ymYRiteSSG;
      string RCMUezQwGG;
      string sazfMIAZUw;
      string aWEfgFeCfA;
      string BcUoWltwzz;
      string ZqsDuXnrEZ;
      string tEyWfuxfnY;
      string TNQGEQFKIZ;
      string NDaVVidAkI;
      string RlyFFxexIb;
      string nOHaeMalzd;
      string ScjeLqdbBx;
      string RxtfGhOKBG;
      string lHBgkzuzqI;
      string IqAGpoCSsO;
      string TCwLKqTbUx;
      if(DkLBmoOuVB == tEyWfuxfnY){xPksrKaDsM = true;}
      else if(tEyWfuxfnY == DkLBmoOuVB){pbXZQEGdzk = true;}
      if(PRETmOWOUf == TNQGEQFKIZ){udjroZwnoR = true;}
      else if(TNQGEQFKIZ == PRETmOWOUf){fMfJqrRuzg = true;}
      if(sEUOtgwnwo == NDaVVidAkI){euRlliLpVt = true;}
      else if(NDaVVidAkI == sEUOtgwnwo){uXNXCMnTba = true;}
      if(nGRdypmzKn == RlyFFxexIb){fSetKrFHOf = true;}
      else if(RlyFFxexIb == nGRdypmzKn){NukbGoisUu = true;}
      if(ymYRiteSSG == nOHaeMalzd){NzZfTpREWj = true;}
      else if(nOHaeMalzd == ymYRiteSSG){rCbqcgarOo = true;}
      if(RCMUezQwGG == ScjeLqdbBx){tfmDRByyGI = true;}
      else if(ScjeLqdbBx == RCMUezQwGG){KVbRuSOzWD = true;}
      if(sazfMIAZUw == RxtfGhOKBG){ykgzgbzpgw = true;}
      else if(RxtfGhOKBG == sazfMIAZUw){QmBXXkbEDB = true;}
      if(aWEfgFeCfA == lHBgkzuzqI){ToYJDfVkSw = true;}
      if(BcUoWltwzz == IqAGpoCSsO){RGTkAzfbcI = true;}
      if(ZqsDuXnrEZ == TCwLKqTbUx){sGBFgcRazq = true;}
      while(lHBgkzuzqI == aWEfgFeCfA){IYaDnsuWtV = true;}
      while(IqAGpoCSsO == IqAGpoCSsO){kwEmQrSSfn = true;}
      while(TCwLKqTbUx == TCwLKqTbUx){aiVRdEBETr = true;}
      if(xPksrKaDsM == true){xPksrKaDsM = false;}
      if(udjroZwnoR == true){udjroZwnoR = false;}
      if(euRlliLpVt == true){euRlliLpVt = false;}
      if(fSetKrFHOf == true){fSetKrFHOf = false;}
      if(NzZfTpREWj == true){NzZfTpREWj = false;}
      if(tfmDRByyGI == true){tfmDRByyGI = false;}
      if(ykgzgbzpgw == true){ykgzgbzpgw = false;}
      if(ToYJDfVkSw == true){ToYJDfVkSw = false;}
      if(RGTkAzfbcI == true){RGTkAzfbcI = false;}
      if(sGBFgcRazq == true){sGBFgcRazq = false;}
      if(pbXZQEGdzk == true){pbXZQEGdzk = false;}
      if(fMfJqrRuzg == true){fMfJqrRuzg = false;}
      if(uXNXCMnTba == true){uXNXCMnTba = false;}
      if(NukbGoisUu == true){NukbGoisUu = false;}
      if(rCbqcgarOo == true){rCbqcgarOo = false;}
      if(KVbRuSOzWD == true){KVbRuSOzWD = false;}
      if(QmBXXkbEDB == true){QmBXXkbEDB = false;}
      if(IYaDnsuWtV == true){IYaDnsuWtV = false;}
      if(kwEmQrSSfn == true){kwEmQrSSfn = false;}
      if(aiVRdEBETr == true){aiVRdEBETr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJBJDAGZOT
{ 
  void CHwAsOVBzm()
  { 
      bool tAOVQARNUj = false;
      bool ONagUcDSFk = false;
      bool TjVgFMSAIE = false;
      bool IYJCxangpz = false;
      bool JIXVnAsiZk = false;
      bool pdNywJehPD = false;
      bool gRFPbpDXit = false;
      bool oWcFbLLzrF = false;
      bool TiZWOdKLGm = false;
      bool uFQlRqCIty = false;
      bool xUzfwTBIVj = false;
      bool yepKixrhBx = false;
      bool frRwyiFpmk = false;
      bool IDFsHzjsat = false;
      bool cBoVoQPGCT = false;
      bool zUGwRFDDhM = false;
      bool NKUkauYwCj = false;
      bool NyHHTdCuHg = false;
      bool TznTknxJbC = false;
      bool wfLNfSgEus = false;
      string gkpJWLCfLf;
      string DQmBYqVSRC;
      string ZSIEfLizzM;
      string cbouUrlXrU;
      string LhEYryqBUG;
      string gaadtNbkcK;
      string bDfzDaargf;
      string FxaxqqOjMh;
      string UhdreCALAG;
      string PBtgrIBFVQ;
      string WzTnAiAdmD;
      string zrXuptYmTA;
      string aPqZPECsEi;
      string oIOwKVNoru;
      string BVXxHXczpx;
      string iNlUoGHsYw;
      string gGYENqdbjU;
      string giuXzFrtSq;
      string aDDGzbWsGD;
      string OTQuOtwTjQ;
      if(gkpJWLCfLf == WzTnAiAdmD){tAOVQARNUj = true;}
      else if(WzTnAiAdmD == gkpJWLCfLf){xUzfwTBIVj = true;}
      if(DQmBYqVSRC == zrXuptYmTA){ONagUcDSFk = true;}
      else if(zrXuptYmTA == DQmBYqVSRC){yepKixrhBx = true;}
      if(ZSIEfLizzM == aPqZPECsEi){TjVgFMSAIE = true;}
      else if(aPqZPECsEi == ZSIEfLizzM){frRwyiFpmk = true;}
      if(cbouUrlXrU == oIOwKVNoru){IYJCxangpz = true;}
      else if(oIOwKVNoru == cbouUrlXrU){IDFsHzjsat = true;}
      if(LhEYryqBUG == BVXxHXczpx){JIXVnAsiZk = true;}
      else if(BVXxHXczpx == LhEYryqBUG){cBoVoQPGCT = true;}
      if(gaadtNbkcK == iNlUoGHsYw){pdNywJehPD = true;}
      else if(iNlUoGHsYw == gaadtNbkcK){zUGwRFDDhM = true;}
      if(bDfzDaargf == gGYENqdbjU){gRFPbpDXit = true;}
      else if(gGYENqdbjU == bDfzDaargf){NKUkauYwCj = true;}
      if(FxaxqqOjMh == giuXzFrtSq){oWcFbLLzrF = true;}
      if(UhdreCALAG == aDDGzbWsGD){TiZWOdKLGm = true;}
      if(PBtgrIBFVQ == OTQuOtwTjQ){uFQlRqCIty = true;}
      while(giuXzFrtSq == FxaxqqOjMh){NyHHTdCuHg = true;}
      while(aDDGzbWsGD == aDDGzbWsGD){TznTknxJbC = true;}
      while(OTQuOtwTjQ == OTQuOtwTjQ){wfLNfSgEus = true;}
      if(tAOVQARNUj == true){tAOVQARNUj = false;}
      if(ONagUcDSFk == true){ONagUcDSFk = false;}
      if(TjVgFMSAIE == true){TjVgFMSAIE = false;}
      if(IYJCxangpz == true){IYJCxangpz = false;}
      if(JIXVnAsiZk == true){JIXVnAsiZk = false;}
      if(pdNywJehPD == true){pdNywJehPD = false;}
      if(gRFPbpDXit == true){gRFPbpDXit = false;}
      if(oWcFbLLzrF == true){oWcFbLLzrF = false;}
      if(TiZWOdKLGm == true){TiZWOdKLGm = false;}
      if(uFQlRqCIty == true){uFQlRqCIty = false;}
      if(xUzfwTBIVj == true){xUzfwTBIVj = false;}
      if(yepKixrhBx == true){yepKixrhBx = false;}
      if(frRwyiFpmk == true){frRwyiFpmk = false;}
      if(IDFsHzjsat == true){IDFsHzjsat = false;}
      if(cBoVoQPGCT == true){cBoVoQPGCT = false;}
      if(zUGwRFDDhM == true){zUGwRFDDhM = false;}
      if(NKUkauYwCj == true){NKUkauYwCj = false;}
      if(NyHHTdCuHg == true){NyHHTdCuHg = false;}
      if(TznTknxJbC == true){TznTknxJbC = false;}
      if(wfLNfSgEus == true){wfLNfSgEus = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSEYTPSPXS
{ 
  void MyMxDYgeuH()
  { 
      bool cDVQhXTUyS = false;
      bool GXjGyeHPRt = false;
      bool pzHkQRFoVV = false;
      bool sAhVfjEhhE = false;
      bool fGcOgpZnZD = false;
      bool aCKrUcwkAQ = false;
      bool RdybZGoOaO = false;
      bool ZZgNNjVrEa = false;
      bool qRPStqopAC = false;
      bool nTgRlBHBoa = false;
      bool ALNKcBUxej = false;
      bool GDfZZANfgh = false;
      bool QzOXZGrPbL = false;
      bool cUDdZfDEos = false;
      bool VrKPwkmHqk = false;
      bool mbTGJAxokW = false;
      bool IEVSHlzCzt = false;
      bool xJpnMYnybn = false;
      bool SjXpXAAwTY = false;
      bool iOTSjQVrHJ = false;
      string aFoEjtkaFG;
      string PUoiUNzlQa;
      string BqSsEBklXy;
      string SDDddxnoMY;
      string lLYmxzDgzr;
      string jaykTiluAh;
      string JzDHnMQKEX;
      string YJZqopRewE;
      string yEleOrESKt;
      string KroePlHRzk;
      string hrbbTZBHwd;
      string RGzujEMYsw;
      string HyAKMgUtaC;
      string iAeKWFbKKn;
      string pxVgcDrtuK;
      string ZhYDciqRPm;
      string FGfstRaoXd;
      string bBNEFKcTgI;
      string nZzQbAabgm;
      string NKuXhiRblL;
      if(aFoEjtkaFG == hrbbTZBHwd){cDVQhXTUyS = true;}
      else if(hrbbTZBHwd == aFoEjtkaFG){ALNKcBUxej = true;}
      if(PUoiUNzlQa == RGzujEMYsw){GXjGyeHPRt = true;}
      else if(RGzujEMYsw == PUoiUNzlQa){GDfZZANfgh = true;}
      if(BqSsEBklXy == HyAKMgUtaC){pzHkQRFoVV = true;}
      else if(HyAKMgUtaC == BqSsEBklXy){QzOXZGrPbL = true;}
      if(SDDddxnoMY == iAeKWFbKKn){sAhVfjEhhE = true;}
      else if(iAeKWFbKKn == SDDddxnoMY){cUDdZfDEos = true;}
      if(lLYmxzDgzr == pxVgcDrtuK){fGcOgpZnZD = true;}
      else if(pxVgcDrtuK == lLYmxzDgzr){VrKPwkmHqk = true;}
      if(jaykTiluAh == ZhYDciqRPm){aCKrUcwkAQ = true;}
      else if(ZhYDciqRPm == jaykTiluAh){mbTGJAxokW = true;}
      if(JzDHnMQKEX == FGfstRaoXd){RdybZGoOaO = true;}
      else if(FGfstRaoXd == JzDHnMQKEX){IEVSHlzCzt = true;}
      if(YJZqopRewE == bBNEFKcTgI){ZZgNNjVrEa = true;}
      if(yEleOrESKt == nZzQbAabgm){qRPStqopAC = true;}
      if(KroePlHRzk == NKuXhiRblL){nTgRlBHBoa = true;}
      while(bBNEFKcTgI == YJZqopRewE){xJpnMYnybn = true;}
      while(nZzQbAabgm == nZzQbAabgm){SjXpXAAwTY = true;}
      while(NKuXhiRblL == NKuXhiRblL){iOTSjQVrHJ = true;}
      if(cDVQhXTUyS == true){cDVQhXTUyS = false;}
      if(GXjGyeHPRt == true){GXjGyeHPRt = false;}
      if(pzHkQRFoVV == true){pzHkQRFoVV = false;}
      if(sAhVfjEhhE == true){sAhVfjEhhE = false;}
      if(fGcOgpZnZD == true){fGcOgpZnZD = false;}
      if(aCKrUcwkAQ == true){aCKrUcwkAQ = false;}
      if(RdybZGoOaO == true){RdybZGoOaO = false;}
      if(ZZgNNjVrEa == true){ZZgNNjVrEa = false;}
      if(qRPStqopAC == true){qRPStqopAC = false;}
      if(nTgRlBHBoa == true){nTgRlBHBoa = false;}
      if(ALNKcBUxej == true){ALNKcBUxej = false;}
      if(GDfZZANfgh == true){GDfZZANfgh = false;}
      if(QzOXZGrPbL == true){QzOXZGrPbL = false;}
      if(cUDdZfDEos == true){cUDdZfDEos = false;}
      if(VrKPwkmHqk == true){VrKPwkmHqk = false;}
      if(mbTGJAxokW == true){mbTGJAxokW = false;}
      if(IEVSHlzCzt == true){IEVSHlzCzt = false;}
      if(xJpnMYnybn == true){xJpnMYnybn = false;}
      if(SjXpXAAwTY == true){SjXpXAAwTY = false;}
      if(iOTSjQVrHJ == true){iOTSjQVrHJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DJRHESCUYF
{ 
  void ewRWaKRtjU()
  { 
      bool QGEqQVOBDl = false;
      bool jarrjQjXez = false;
      bool HxRBKUggsl = false;
      bool fAyqgjKkpd = false;
      bool swMqsrNpCO = false;
      bool HNVULSnCfu = false;
      bool ngHRFibBKA = false;
      bool FzgAFKjZIS = false;
      bool HqeedSeceO = false;
      bool uHEupLoukJ = false;
      bool PLeBIIgUPB = false;
      bool iOtMnwCcnm = false;
      bool EzWwFxtkKt = false;
      bool VonzDuMcVU = false;
      bool lJNdegNqHs = false;
      bool JLGyFQoiwL = false;
      bool NuKUetZtJr = false;
      bool jYHSAtksQY = false;
      bool jDcQjJhptm = false;
      bool GcgKHpzryk = false;
      string mFbBywJjha;
      string ZrDyoylJkO;
      string rZbeYIQdUD;
      string eySiOUbHBI;
      string EhpMLrHVmo;
      string LRFYJMcwbp;
      string feOdwaZTjT;
      string WeIbKKjPSg;
      string AuqfrNssZB;
      string qeeLcYSLQk;
      string RnkSRfIdOy;
      string cNctpknikh;
      string gfthbqzxzk;
      string qXzhPMJYNL;
      string EPeaXdBjUr;
      string kjZhDlsCpa;
      string fLedGENued;
      string bPUYdRBSKx;
      string pPbGzHxQdc;
      string SGhmfrkATS;
      if(mFbBywJjha == RnkSRfIdOy){QGEqQVOBDl = true;}
      else if(RnkSRfIdOy == mFbBywJjha){PLeBIIgUPB = true;}
      if(ZrDyoylJkO == cNctpknikh){jarrjQjXez = true;}
      else if(cNctpknikh == ZrDyoylJkO){iOtMnwCcnm = true;}
      if(rZbeYIQdUD == gfthbqzxzk){HxRBKUggsl = true;}
      else if(gfthbqzxzk == rZbeYIQdUD){EzWwFxtkKt = true;}
      if(eySiOUbHBI == qXzhPMJYNL){fAyqgjKkpd = true;}
      else if(qXzhPMJYNL == eySiOUbHBI){VonzDuMcVU = true;}
      if(EhpMLrHVmo == EPeaXdBjUr){swMqsrNpCO = true;}
      else if(EPeaXdBjUr == EhpMLrHVmo){lJNdegNqHs = true;}
      if(LRFYJMcwbp == kjZhDlsCpa){HNVULSnCfu = true;}
      else if(kjZhDlsCpa == LRFYJMcwbp){JLGyFQoiwL = true;}
      if(feOdwaZTjT == fLedGENued){ngHRFibBKA = true;}
      else if(fLedGENued == feOdwaZTjT){NuKUetZtJr = true;}
      if(WeIbKKjPSg == bPUYdRBSKx){FzgAFKjZIS = true;}
      if(AuqfrNssZB == pPbGzHxQdc){HqeedSeceO = true;}
      if(qeeLcYSLQk == SGhmfrkATS){uHEupLoukJ = true;}
      while(bPUYdRBSKx == WeIbKKjPSg){jYHSAtksQY = true;}
      while(pPbGzHxQdc == pPbGzHxQdc){jDcQjJhptm = true;}
      while(SGhmfrkATS == SGhmfrkATS){GcgKHpzryk = true;}
      if(QGEqQVOBDl == true){QGEqQVOBDl = false;}
      if(jarrjQjXez == true){jarrjQjXez = false;}
      if(HxRBKUggsl == true){HxRBKUggsl = false;}
      if(fAyqgjKkpd == true){fAyqgjKkpd = false;}
      if(swMqsrNpCO == true){swMqsrNpCO = false;}
      if(HNVULSnCfu == true){HNVULSnCfu = false;}
      if(ngHRFibBKA == true){ngHRFibBKA = false;}
      if(FzgAFKjZIS == true){FzgAFKjZIS = false;}
      if(HqeedSeceO == true){HqeedSeceO = false;}
      if(uHEupLoukJ == true){uHEupLoukJ = false;}
      if(PLeBIIgUPB == true){PLeBIIgUPB = false;}
      if(iOtMnwCcnm == true){iOtMnwCcnm = false;}
      if(EzWwFxtkKt == true){EzWwFxtkKt = false;}
      if(VonzDuMcVU == true){VonzDuMcVU = false;}
      if(lJNdegNqHs == true){lJNdegNqHs = false;}
      if(JLGyFQoiwL == true){JLGyFQoiwL = false;}
      if(NuKUetZtJr == true){NuKUetZtJr = false;}
      if(jYHSAtksQY == true){jYHSAtksQY = false;}
      if(jDcQjJhptm == true){jDcQjJhptm = false;}
      if(GcgKHpzryk == true){GcgKHpzryk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GLMCZGGFDJ
{ 
  void KsiBFSXucN()
  { 
      bool VHxNCmEpJk = false;
      bool ksYckBUSXG = false;
      bool sabMAnGIYP = false;
      bool pMXObHePmQ = false;
      bool GLNhcseXok = false;
      bool eyHXItejNN = false;
      bool guRstYUJAc = false;
      bool VEfGzhNtiH = false;
      bool JiSnjrEAGg = false;
      bool buCYjKtTmE = false;
      bool XUWMOaRBXZ = false;
      bool gkBFEybcJC = false;
      bool TUDTBaBGVn = false;
      bool nsHdinMGZJ = false;
      bool ZCcfzqtwUl = false;
      bool hQKjkCQDKm = false;
      bool YKfikndWWP = false;
      bool lVDAcRrXTJ = false;
      bool gFljFXhXsf = false;
      bool XIuljOWstL = false;
      string NrIYVxIoor;
      string gbmkfdVKkN;
      string zhMOjcMClR;
      string CfqbauCeMR;
      string jBBcbODOes;
      string VaLGOeesns;
      string jGDXoBkKKj;
      string aqxSdxgjlV;
      string ZyWsuaTkMw;
      string QJpThdydma;
      string drEuRecsbQ;
      string yuGSSliKbO;
      string hAxOTRAdkz;
      string zCwLqgsbaQ;
      string yZIwxUCXAu;
      string tnBYsctpaA;
      string dyIcRuyual;
      string rGiLPHrBQy;
      string ObdoELBXSO;
      string lDAalARfdC;
      if(NrIYVxIoor == drEuRecsbQ){VHxNCmEpJk = true;}
      else if(drEuRecsbQ == NrIYVxIoor){XUWMOaRBXZ = true;}
      if(gbmkfdVKkN == yuGSSliKbO){ksYckBUSXG = true;}
      else if(yuGSSliKbO == gbmkfdVKkN){gkBFEybcJC = true;}
      if(zhMOjcMClR == hAxOTRAdkz){sabMAnGIYP = true;}
      else if(hAxOTRAdkz == zhMOjcMClR){TUDTBaBGVn = true;}
      if(CfqbauCeMR == zCwLqgsbaQ){pMXObHePmQ = true;}
      else if(zCwLqgsbaQ == CfqbauCeMR){nsHdinMGZJ = true;}
      if(jBBcbODOes == yZIwxUCXAu){GLNhcseXok = true;}
      else if(yZIwxUCXAu == jBBcbODOes){ZCcfzqtwUl = true;}
      if(VaLGOeesns == tnBYsctpaA){eyHXItejNN = true;}
      else if(tnBYsctpaA == VaLGOeesns){hQKjkCQDKm = true;}
      if(jGDXoBkKKj == dyIcRuyual){guRstYUJAc = true;}
      else if(dyIcRuyual == jGDXoBkKKj){YKfikndWWP = true;}
      if(aqxSdxgjlV == rGiLPHrBQy){VEfGzhNtiH = true;}
      if(ZyWsuaTkMw == ObdoELBXSO){JiSnjrEAGg = true;}
      if(QJpThdydma == lDAalARfdC){buCYjKtTmE = true;}
      while(rGiLPHrBQy == aqxSdxgjlV){lVDAcRrXTJ = true;}
      while(ObdoELBXSO == ObdoELBXSO){gFljFXhXsf = true;}
      while(lDAalARfdC == lDAalARfdC){XIuljOWstL = true;}
      if(VHxNCmEpJk == true){VHxNCmEpJk = false;}
      if(ksYckBUSXG == true){ksYckBUSXG = false;}
      if(sabMAnGIYP == true){sabMAnGIYP = false;}
      if(pMXObHePmQ == true){pMXObHePmQ = false;}
      if(GLNhcseXok == true){GLNhcseXok = false;}
      if(eyHXItejNN == true){eyHXItejNN = false;}
      if(guRstYUJAc == true){guRstYUJAc = false;}
      if(VEfGzhNtiH == true){VEfGzhNtiH = false;}
      if(JiSnjrEAGg == true){JiSnjrEAGg = false;}
      if(buCYjKtTmE == true){buCYjKtTmE = false;}
      if(XUWMOaRBXZ == true){XUWMOaRBXZ = false;}
      if(gkBFEybcJC == true){gkBFEybcJC = false;}
      if(TUDTBaBGVn == true){TUDTBaBGVn = false;}
      if(nsHdinMGZJ == true){nsHdinMGZJ = false;}
      if(ZCcfzqtwUl == true){ZCcfzqtwUl = false;}
      if(hQKjkCQDKm == true){hQKjkCQDKm = false;}
      if(YKfikndWWP == true){YKfikndWWP = false;}
      if(lVDAcRrXTJ == true){lVDAcRrXTJ = false;}
      if(gFljFXhXsf == true){gFljFXhXsf = false;}
      if(XIuljOWstL == true){XIuljOWstL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WFSCCRSGTT
{ 
  void iMLJMCMVFL()
  { 
      bool LPgCsDoESs = false;
      bool JmMGMyIMym = false;
      bool VFlZPIRcDn = false;
      bool HxXkGtEBJd = false;
      bool qNFdQqzRft = false;
      bool tcnTsGcGmk = false;
      bool kMBekMPbzR = false;
      bool sHDUuIzIJY = false;
      bool IAxIteJDrA = false;
      bool RyOYreMarE = false;
      bool aXRNBlYSXj = false;
      bool GTwNbkPrkF = false;
      bool DLizAurebQ = false;
      bool wYQFxkhiHH = false;
      bool FpfIsxCAwH = false;
      bool PUplAPnRNF = false;
      bool ttqHmhDpQq = false;
      bool CfjdAMfaGD = false;
      bool sqhUBbhdEh = false;
      bool xQVCMLyXUL = false;
      string tPVoAHjQVb;
      string cOZkWJUtNB;
      string mlEpxlXUKL;
      string mnkhUMcwDp;
      string uBnFhcPhqn;
      string cGDLwHKfqN;
      string iPGJnncqQJ;
      string gYqWFlyzHU;
      string VpcVhfkYkM;
      string BxEoGeudQt;
      string zYQgGEPfFK;
      string JLXWrsljaH;
      string DEFDHjTBPZ;
      string qUhNVxYwPd;
      string QFSaDpYhxN;
      string sKCJquSMYW;
      string jNPfTndJBt;
      string TpUxqxkeAR;
      string KlECggRYWa;
      string eLXrsComGO;
      if(tPVoAHjQVb == zYQgGEPfFK){LPgCsDoESs = true;}
      else if(zYQgGEPfFK == tPVoAHjQVb){aXRNBlYSXj = true;}
      if(cOZkWJUtNB == JLXWrsljaH){JmMGMyIMym = true;}
      else if(JLXWrsljaH == cOZkWJUtNB){GTwNbkPrkF = true;}
      if(mlEpxlXUKL == DEFDHjTBPZ){VFlZPIRcDn = true;}
      else if(DEFDHjTBPZ == mlEpxlXUKL){DLizAurebQ = true;}
      if(mnkhUMcwDp == qUhNVxYwPd){HxXkGtEBJd = true;}
      else if(qUhNVxYwPd == mnkhUMcwDp){wYQFxkhiHH = true;}
      if(uBnFhcPhqn == QFSaDpYhxN){qNFdQqzRft = true;}
      else if(QFSaDpYhxN == uBnFhcPhqn){FpfIsxCAwH = true;}
      if(cGDLwHKfqN == sKCJquSMYW){tcnTsGcGmk = true;}
      else if(sKCJquSMYW == cGDLwHKfqN){PUplAPnRNF = true;}
      if(iPGJnncqQJ == jNPfTndJBt){kMBekMPbzR = true;}
      else if(jNPfTndJBt == iPGJnncqQJ){ttqHmhDpQq = true;}
      if(gYqWFlyzHU == TpUxqxkeAR){sHDUuIzIJY = true;}
      if(VpcVhfkYkM == KlECggRYWa){IAxIteJDrA = true;}
      if(BxEoGeudQt == eLXrsComGO){RyOYreMarE = true;}
      while(TpUxqxkeAR == gYqWFlyzHU){CfjdAMfaGD = true;}
      while(KlECggRYWa == KlECggRYWa){sqhUBbhdEh = true;}
      while(eLXrsComGO == eLXrsComGO){xQVCMLyXUL = true;}
      if(LPgCsDoESs == true){LPgCsDoESs = false;}
      if(JmMGMyIMym == true){JmMGMyIMym = false;}
      if(VFlZPIRcDn == true){VFlZPIRcDn = false;}
      if(HxXkGtEBJd == true){HxXkGtEBJd = false;}
      if(qNFdQqzRft == true){qNFdQqzRft = false;}
      if(tcnTsGcGmk == true){tcnTsGcGmk = false;}
      if(kMBekMPbzR == true){kMBekMPbzR = false;}
      if(sHDUuIzIJY == true){sHDUuIzIJY = false;}
      if(IAxIteJDrA == true){IAxIteJDrA = false;}
      if(RyOYreMarE == true){RyOYreMarE = false;}
      if(aXRNBlYSXj == true){aXRNBlYSXj = false;}
      if(GTwNbkPrkF == true){GTwNbkPrkF = false;}
      if(DLizAurebQ == true){DLizAurebQ = false;}
      if(wYQFxkhiHH == true){wYQFxkhiHH = false;}
      if(FpfIsxCAwH == true){FpfIsxCAwH = false;}
      if(PUplAPnRNF == true){PUplAPnRNF = false;}
      if(ttqHmhDpQq == true){ttqHmhDpQq = false;}
      if(CfjdAMfaGD == true){CfjdAMfaGD = false;}
      if(sqhUBbhdEh == true){sqhUBbhdEh = false;}
      if(xQVCMLyXUL == true){xQVCMLyXUL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EMCXIYYFIM
{ 
  void TcXxjkWDVH()
  { 
      bool abDGkrTMeG = false;
      bool VzisZhbZAn = false;
      bool xqtJxNdQtR = false;
      bool IjxiScbcRL = false;
      bool aJhBVkKcqM = false;
      bool WftRfjhtIX = false;
      bool OCSMxlBzaw = false;
      bool GzHoNmIsnM = false;
      bool CAYhubofDh = false;
      bool tgTtwYqUDi = false;
      bool iKCtGWYFDr = false;
      bool bnGwUOcjRU = false;
      bool wVwrCYeNro = false;
      bool wmpEcqydaX = false;
      bool DibKGGaXYh = false;
      bool uGDhmNOJrh = false;
      bool rKNOwnyCSd = false;
      bool QyJsQNsklu = false;
      bool xGnKsojHQP = false;
      bool cnksfrVMOR = false;
      string mODDAsgFce;
      string WioKDgszRe;
      string uVVZltBBRd;
      string KQCaIknNQg;
      string gTxpaNJGeH;
      string aQIAHRrdRG;
      string renzTGgNBS;
      string sfhjybXeyY;
      string juVJCsHBTq;
      string sJwKoBfyVU;
      string fwFMNuiXBe;
      string sMerVxIdwa;
      string yesJZiiXuw;
      string wYIcrnoJuH;
      string KiAoxfdDnr;
      string rBCuVADumd;
      string MLcEiUECAh;
      string HzhoQPeDMt;
      string EeiCEtWNHq;
      string jtVQtyGuFc;
      if(mODDAsgFce == fwFMNuiXBe){abDGkrTMeG = true;}
      else if(fwFMNuiXBe == mODDAsgFce){iKCtGWYFDr = true;}
      if(WioKDgszRe == sMerVxIdwa){VzisZhbZAn = true;}
      else if(sMerVxIdwa == WioKDgszRe){bnGwUOcjRU = true;}
      if(uVVZltBBRd == yesJZiiXuw){xqtJxNdQtR = true;}
      else if(yesJZiiXuw == uVVZltBBRd){wVwrCYeNro = true;}
      if(KQCaIknNQg == wYIcrnoJuH){IjxiScbcRL = true;}
      else if(wYIcrnoJuH == KQCaIknNQg){wmpEcqydaX = true;}
      if(gTxpaNJGeH == KiAoxfdDnr){aJhBVkKcqM = true;}
      else if(KiAoxfdDnr == gTxpaNJGeH){DibKGGaXYh = true;}
      if(aQIAHRrdRG == rBCuVADumd){WftRfjhtIX = true;}
      else if(rBCuVADumd == aQIAHRrdRG){uGDhmNOJrh = true;}
      if(renzTGgNBS == MLcEiUECAh){OCSMxlBzaw = true;}
      else if(MLcEiUECAh == renzTGgNBS){rKNOwnyCSd = true;}
      if(sfhjybXeyY == HzhoQPeDMt){GzHoNmIsnM = true;}
      if(juVJCsHBTq == EeiCEtWNHq){CAYhubofDh = true;}
      if(sJwKoBfyVU == jtVQtyGuFc){tgTtwYqUDi = true;}
      while(HzhoQPeDMt == sfhjybXeyY){QyJsQNsklu = true;}
      while(EeiCEtWNHq == EeiCEtWNHq){xGnKsojHQP = true;}
      while(jtVQtyGuFc == jtVQtyGuFc){cnksfrVMOR = true;}
      if(abDGkrTMeG == true){abDGkrTMeG = false;}
      if(VzisZhbZAn == true){VzisZhbZAn = false;}
      if(xqtJxNdQtR == true){xqtJxNdQtR = false;}
      if(IjxiScbcRL == true){IjxiScbcRL = false;}
      if(aJhBVkKcqM == true){aJhBVkKcqM = false;}
      if(WftRfjhtIX == true){WftRfjhtIX = false;}
      if(OCSMxlBzaw == true){OCSMxlBzaw = false;}
      if(GzHoNmIsnM == true){GzHoNmIsnM = false;}
      if(CAYhubofDh == true){CAYhubofDh = false;}
      if(tgTtwYqUDi == true){tgTtwYqUDi = false;}
      if(iKCtGWYFDr == true){iKCtGWYFDr = false;}
      if(bnGwUOcjRU == true){bnGwUOcjRU = false;}
      if(wVwrCYeNro == true){wVwrCYeNro = false;}
      if(wmpEcqydaX == true){wmpEcqydaX = false;}
      if(DibKGGaXYh == true){DibKGGaXYh = false;}
      if(uGDhmNOJrh == true){uGDhmNOJrh = false;}
      if(rKNOwnyCSd == true){rKNOwnyCSd = false;}
      if(QyJsQNsklu == true){QyJsQNsklu = false;}
      if(xGnKsojHQP == true){xGnKsojHQP = false;}
      if(cnksfrVMOR == true){cnksfrVMOR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MSMIRKHCKG
{ 
  void sgdiHoZOQF()
  { 
      bool SylSlZpwmR = false;
      bool TkFNjVJHAU = false;
      bool ojiZzCOoNy = false;
      bool UUobcXDcpS = false;
      bool BUXmaXcVPD = false;
      bool tNCtchPMSi = false;
      bool KAinxywckM = false;
      bool SfRgTTMuya = false;
      bool ZsZKDHStyt = false;
      bool IpKHIBljpb = false;
      bool bzkDkOuUaI = false;
      bool VTOrIQaXjp = false;
      bool fBdpEcVJYR = false;
      bool hbFWzaIVZo = false;
      bool LxTpYnbSyq = false;
      bool aNzzuaUtzI = false;
      bool skwIZsOqrh = false;
      bool IEyteignQP = false;
      bool ADLgqUcFbY = false;
      bool FNWRwZBKQf = false;
      string yuKZccxCVR;
      string nYuxZCPZry;
      string wgytbtMwjG;
      string UIzzyGEISE;
      string QuXxfhUPkN;
      string OiVrkRwPyh;
      string PBSPwfYwyS;
      string yGHngAJANs;
      string YxKVrklGNf;
      string JoKjoPcHAA;
      string IYQRPHbhKk;
      string IuBEIRqwXL;
      string sShRJIwWyR;
      string XBAMjAgrGj;
      string IEucXNmGaW;
      string YfjoHppyIG;
      string LFisMGunTI;
      string kypmCoWFsu;
      string VoubsqRKFt;
      string JhiAYDUCPR;
      if(yuKZccxCVR == IYQRPHbhKk){SylSlZpwmR = true;}
      else if(IYQRPHbhKk == yuKZccxCVR){bzkDkOuUaI = true;}
      if(nYuxZCPZry == IuBEIRqwXL){TkFNjVJHAU = true;}
      else if(IuBEIRqwXL == nYuxZCPZry){VTOrIQaXjp = true;}
      if(wgytbtMwjG == sShRJIwWyR){ojiZzCOoNy = true;}
      else if(sShRJIwWyR == wgytbtMwjG){fBdpEcVJYR = true;}
      if(UIzzyGEISE == XBAMjAgrGj){UUobcXDcpS = true;}
      else if(XBAMjAgrGj == UIzzyGEISE){hbFWzaIVZo = true;}
      if(QuXxfhUPkN == IEucXNmGaW){BUXmaXcVPD = true;}
      else if(IEucXNmGaW == QuXxfhUPkN){LxTpYnbSyq = true;}
      if(OiVrkRwPyh == YfjoHppyIG){tNCtchPMSi = true;}
      else if(YfjoHppyIG == OiVrkRwPyh){aNzzuaUtzI = true;}
      if(PBSPwfYwyS == LFisMGunTI){KAinxywckM = true;}
      else if(LFisMGunTI == PBSPwfYwyS){skwIZsOqrh = true;}
      if(yGHngAJANs == kypmCoWFsu){SfRgTTMuya = true;}
      if(YxKVrklGNf == VoubsqRKFt){ZsZKDHStyt = true;}
      if(JoKjoPcHAA == JhiAYDUCPR){IpKHIBljpb = true;}
      while(kypmCoWFsu == yGHngAJANs){IEyteignQP = true;}
      while(VoubsqRKFt == VoubsqRKFt){ADLgqUcFbY = true;}
      while(JhiAYDUCPR == JhiAYDUCPR){FNWRwZBKQf = true;}
      if(SylSlZpwmR == true){SylSlZpwmR = false;}
      if(TkFNjVJHAU == true){TkFNjVJHAU = false;}
      if(ojiZzCOoNy == true){ojiZzCOoNy = false;}
      if(UUobcXDcpS == true){UUobcXDcpS = false;}
      if(BUXmaXcVPD == true){BUXmaXcVPD = false;}
      if(tNCtchPMSi == true){tNCtchPMSi = false;}
      if(KAinxywckM == true){KAinxywckM = false;}
      if(SfRgTTMuya == true){SfRgTTMuya = false;}
      if(ZsZKDHStyt == true){ZsZKDHStyt = false;}
      if(IpKHIBljpb == true){IpKHIBljpb = false;}
      if(bzkDkOuUaI == true){bzkDkOuUaI = false;}
      if(VTOrIQaXjp == true){VTOrIQaXjp = false;}
      if(fBdpEcVJYR == true){fBdpEcVJYR = false;}
      if(hbFWzaIVZo == true){hbFWzaIVZo = false;}
      if(LxTpYnbSyq == true){LxTpYnbSyq = false;}
      if(aNzzuaUtzI == true){aNzzuaUtzI = false;}
      if(skwIZsOqrh == true){skwIZsOqrh = false;}
      if(IEyteignQP == true){IEyteignQP = false;}
      if(ADLgqUcFbY == true){ADLgqUcFbY = false;}
      if(FNWRwZBKQf == true){FNWRwZBKQf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBFTTYVTCM
{ 
  void zuDwreKjVU()
  { 
      bool kmUsgnuxms = false;
      bool sHjyYHKugn = false;
      bool AGcSuSWlOt = false;
      bool PzOtbPYIgE = false;
      bool jXCtpUYAgB = false;
      bool fPCJFeJCyO = false;
      bool RJirdtsoVJ = false;
      bool hBNcDcDibZ = false;
      bool sVEMOzxFox = false;
      bool GWJSlZoJQw = false;
      bool bjdXSdCZGb = false;
      bool aaZXUuEVdd = false;
      bool xmAYDLrtpc = false;
      bool msRfyJrgsj = false;
      bool xWyMVewkyq = false;
      bool UTflzniFUH = false;
      bool lHicogIsZK = false;
      bool DXbsgZonCX = false;
      bool OGwzHTNegK = false;
      bool alMlyonUXo = false;
      string nphjBEzaVt;
      string qmQUJGmOIZ;
      string qZHlmhfFiD;
      string WqGeDYXiGE;
      string iHZhPDkboR;
      string XnmTYOiuxS;
      string YtrRWzgkQj;
      string iDHDqjAYWi;
      string xDPRfiEmGo;
      string pblmenPHLP;
      string WzKFiTficn;
      string NJXOVUeakm;
      string useatGRTYC;
      string UrNHMxrJhM;
      string CUKRbgDWRJ;
      string JnWXTcUiLb;
      string CMJZTVuQCX;
      string bUrYkaiMzM;
      string CtCOsfVomi;
      string cJyGJpKjxF;
      if(nphjBEzaVt == WzKFiTficn){kmUsgnuxms = true;}
      else if(WzKFiTficn == nphjBEzaVt){bjdXSdCZGb = true;}
      if(qmQUJGmOIZ == NJXOVUeakm){sHjyYHKugn = true;}
      else if(NJXOVUeakm == qmQUJGmOIZ){aaZXUuEVdd = true;}
      if(qZHlmhfFiD == useatGRTYC){AGcSuSWlOt = true;}
      else if(useatGRTYC == qZHlmhfFiD){xmAYDLrtpc = true;}
      if(WqGeDYXiGE == UrNHMxrJhM){PzOtbPYIgE = true;}
      else if(UrNHMxrJhM == WqGeDYXiGE){msRfyJrgsj = true;}
      if(iHZhPDkboR == CUKRbgDWRJ){jXCtpUYAgB = true;}
      else if(CUKRbgDWRJ == iHZhPDkboR){xWyMVewkyq = true;}
      if(XnmTYOiuxS == JnWXTcUiLb){fPCJFeJCyO = true;}
      else if(JnWXTcUiLb == XnmTYOiuxS){UTflzniFUH = true;}
      if(YtrRWzgkQj == CMJZTVuQCX){RJirdtsoVJ = true;}
      else if(CMJZTVuQCX == YtrRWzgkQj){lHicogIsZK = true;}
      if(iDHDqjAYWi == bUrYkaiMzM){hBNcDcDibZ = true;}
      if(xDPRfiEmGo == CtCOsfVomi){sVEMOzxFox = true;}
      if(pblmenPHLP == cJyGJpKjxF){GWJSlZoJQw = true;}
      while(bUrYkaiMzM == iDHDqjAYWi){DXbsgZonCX = true;}
      while(CtCOsfVomi == CtCOsfVomi){OGwzHTNegK = true;}
      while(cJyGJpKjxF == cJyGJpKjxF){alMlyonUXo = true;}
      if(kmUsgnuxms == true){kmUsgnuxms = false;}
      if(sHjyYHKugn == true){sHjyYHKugn = false;}
      if(AGcSuSWlOt == true){AGcSuSWlOt = false;}
      if(PzOtbPYIgE == true){PzOtbPYIgE = false;}
      if(jXCtpUYAgB == true){jXCtpUYAgB = false;}
      if(fPCJFeJCyO == true){fPCJFeJCyO = false;}
      if(RJirdtsoVJ == true){RJirdtsoVJ = false;}
      if(hBNcDcDibZ == true){hBNcDcDibZ = false;}
      if(sVEMOzxFox == true){sVEMOzxFox = false;}
      if(GWJSlZoJQw == true){GWJSlZoJQw = false;}
      if(bjdXSdCZGb == true){bjdXSdCZGb = false;}
      if(aaZXUuEVdd == true){aaZXUuEVdd = false;}
      if(xmAYDLrtpc == true){xmAYDLrtpc = false;}
      if(msRfyJrgsj == true){msRfyJrgsj = false;}
      if(xWyMVewkyq == true){xWyMVewkyq = false;}
      if(UTflzniFUH == true){UTflzniFUH = false;}
      if(lHicogIsZK == true){lHicogIsZK = false;}
      if(DXbsgZonCX == true){DXbsgZonCX = false;}
      if(OGwzHTNegK == true){OGwzHTNegK = false;}
      if(alMlyonUXo == true){alMlyonUXo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FUNUQRDNPY
{ 
  void clTHPaHXKM()
  { 
      bool RDXpMNoZzR = false;
      bool ukAYDmxeqo = false;
      bool AXzWpRunCS = false;
      bool FtUmgbcYug = false;
      bool snEpAiJHMt = false;
      bool QtjrPsEBAt = false;
      bool RAXfLBPMra = false;
      bool JXjJuLTIVH = false;
      bool InaHCLJcXn = false;
      bool XaYBPsPXey = false;
      bool TwOkjrKawD = false;
      bool YuerldZPdA = false;
      bool rloEDhyitC = false;
      bool uwdXmLZoXJ = false;
      bool AigTOcwfOk = false;
      bool TAteGhHJhB = false;
      bool sbftIcRHFa = false;
      bool EjrTzJEUpZ = false;
      bool lSTIiuByRF = false;
      bool EPHVPYCmLk = false;
      string cSsegPoCAh;
      string CeBlyAeYqc;
      string NEdhjMcmTt;
      string UJLloxjQnQ;
      string XiSDjUJfRq;
      string sOLbeXoLtU;
      string lBiFNrTOxB;
      string PNjaFdkaxO;
      string CwVbAFyjGQ;
      string IYVTdVANoq;
      string BuiQafdjVB;
      string lNNfRofGEI;
      string tjHfrqqQwj;
      string cXkFNHMEAU;
      string aNNFdtLpBo;
      string otJgxRmCXj;
      string nMmlXOcHRK;
      string bbFigfVCCy;
      string fBPHtiOEIu;
      string TKfQgNZbgP;
      if(cSsegPoCAh == BuiQafdjVB){RDXpMNoZzR = true;}
      else if(BuiQafdjVB == cSsegPoCAh){TwOkjrKawD = true;}
      if(CeBlyAeYqc == lNNfRofGEI){ukAYDmxeqo = true;}
      else if(lNNfRofGEI == CeBlyAeYqc){YuerldZPdA = true;}
      if(NEdhjMcmTt == tjHfrqqQwj){AXzWpRunCS = true;}
      else if(tjHfrqqQwj == NEdhjMcmTt){rloEDhyitC = true;}
      if(UJLloxjQnQ == cXkFNHMEAU){FtUmgbcYug = true;}
      else if(cXkFNHMEAU == UJLloxjQnQ){uwdXmLZoXJ = true;}
      if(XiSDjUJfRq == aNNFdtLpBo){snEpAiJHMt = true;}
      else if(aNNFdtLpBo == XiSDjUJfRq){AigTOcwfOk = true;}
      if(sOLbeXoLtU == otJgxRmCXj){QtjrPsEBAt = true;}
      else if(otJgxRmCXj == sOLbeXoLtU){TAteGhHJhB = true;}
      if(lBiFNrTOxB == nMmlXOcHRK){RAXfLBPMra = true;}
      else if(nMmlXOcHRK == lBiFNrTOxB){sbftIcRHFa = true;}
      if(PNjaFdkaxO == bbFigfVCCy){JXjJuLTIVH = true;}
      if(CwVbAFyjGQ == fBPHtiOEIu){InaHCLJcXn = true;}
      if(IYVTdVANoq == TKfQgNZbgP){XaYBPsPXey = true;}
      while(bbFigfVCCy == PNjaFdkaxO){EjrTzJEUpZ = true;}
      while(fBPHtiOEIu == fBPHtiOEIu){lSTIiuByRF = true;}
      while(TKfQgNZbgP == TKfQgNZbgP){EPHVPYCmLk = true;}
      if(RDXpMNoZzR == true){RDXpMNoZzR = false;}
      if(ukAYDmxeqo == true){ukAYDmxeqo = false;}
      if(AXzWpRunCS == true){AXzWpRunCS = false;}
      if(FtUmgbcYug == true){FtUmgbcYug = false;}
      if(snEpAiJHMt == true){snEpAiJHMt = false;}
      if(QtjrPsEBAt == true){QtjrPsEBAt = false;}
      if(RAXfLBPMra == true){RAXfLBPMra = false;}
      if(JXjJuLTIVH == true){JXjJuLTIVH = false;}
      if(InaHCLJcXn == true){InaHCLJcXn = false;}
      if(XaYBPsPXey == true){XaYBPsPXey = false;}
      if(TwOkjrKawD == true){TwOkjrKawD = false;}
      if(YuerldZPdA == true){YuerldZPdA = false;}
      if(rloEDhyitC == true){rloEDhyitC = false;}
      if(uwdXmLZoXJ == true){uwdXmLZoXJ = false;}
      if(AigTOcwfOk == true){AigTOcwfOk = false;}
      if(TAteGhHJhB == true){TAteGhHJhB = false;}
      if(sbftIcRHFa == true){sbftIcRHFa = false;}
      if(EjrTzJEUpZ == true){EjrTzJEUpZ = false;}
      if(lSTIiuByRF == true){lSTIiuByRF = false;}
      if(EPHVPYCmLk == true){EPHVPYCmLk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MPOEVKLSPE
{ 
  void BrQMziwFLD()
  { 
      bool BhoADuuaNu = false;
      bool ZjqAfErxCf = false;
      bool cQRxuDWXUm = false;
      bool KlQyVbNEaM = false;
      bool HhdkWqryXY = false;
      bool EZLBPkPrFA = false;
      bool YXFaknTreD = false;
      bool pnWpYtlfaE = false;
      bool LXAwhjZPhj = false;
      bool LVzZnjbDAh = false;
      bool XzTTiPDVbU = false;
      bool yjRAnAXJrA = false;
      bool OEKtrTowBn = false;
      bool RifrfMDfNS = false;
      bool gDmMkbEylm = false;
      bool MSKzTSoZbO = false;
      bool aGTmDODYUb = false;
      bool wqwZTKRxIP = false;
      bool PqKObzYfXM = false;
      bool WdDyrZizJW = false;
      string XGhEmZjhci;
      string qNogEyijrM;
      string CMsGLwyQmO;
      string iNdzKSRtyY;
      string clVcmlmapN;
      string iMQTZKMbrq;
      string bStNAdjoVl;
      string gnkSiQpQSZ;
      string IWaZeVxJZz;
      string FoBHwJqHbJ;
      string ByEDgtaxjI;
      string UwIShFrUid;
      string gZPVfqmdVZ;
      string ZhnJXKRWsk;
      string tzZQeJgiYq;
      string RWYxcaihXo;
      string HxbKilHytX;
      string mVayjgAyqW;
      string JDEeICJqgx;
      string bizDcxWOhr;
      if(XGhEmZjhci == ByEDgtaxjI){BhoADuuaNu = true;}
      else if(ByEDgtaxjI == XGhEmZjhci){XzTTiPDVbU = true;}
      if(qNogEyijrM == UwIShFrUid){ZjqAfErxCf = true;}
      else if(UwIShFrUid == qNogEyijrM){yjRAnAXJrA = true;}
      if(CMsGLwyQmO == gZPVfqmdVZ){cQRxuDWXUm = true;}
      else if(gZPVfqmdVZ == CMsGLwyQmO){OEKtrTowBn = true;}
      if(iNdzKSRtyY == ZhnJXKRWsk){KlQyVbNEaM = true;}
      else if(ZhnJXKRWsk == iNdzKSRtyY){RifrfMDfNS = true;}
      if(clVcmlmapN == tzZQeJgiYq){HhdkWqryXY = true;}
      else if(tzZQeJgiYq == clVcmlmapN){gDmMkbEylm = true;}
      if(iMQTZKMbrq == RWYxcaihXo){EZLBPkPrFA = true;}
      else if(RWYxcaihXo == iMQTZKMbrq){MSKzTSoZbO = true;}
      if(bStNAdjoVl == HxbKilHytX){YXFaknTreD = true;}
      else if(HxbKilHytX == bStNAdjoVl){aGTmDODYUb = true;}
      if(gnkSiQpQSZ == mVayjgAyqW){pnWpYtlfaE = true;}
      if(IWaZeVxJZz == JDEeICJqgx){LXAwhjZPhj = true;}
      if(FoBHwJqHbJ == bizDcxWOhr){LVzZnjbDAh = true;}
      while(mVayjgAyqW == gnkSiQpQSZ){wqwZTKRxIP = true;}
      while(JDEeICJqgx == JDEeICJqgx){PqKObzYfXM = true;}
      while(bizDcxWOhr == bizDcxWOhr){WdDyrZizJW = true;}
      if(BhoADuuaNu == true){BhoADuuaNu = false;}
      if(ZjqAfErxCf == true){ZjqAfErxCf = false;}
      if(cQRxuDWXUm == true){cQRxuDWXUm = false;}
      if(KlQyVbNEaM == true){KlQyVbNEaM = false;}
      if(HhdkWqryXY == true){HhdkWqryXY = false;}
      if(EZLBPkPrFA == true){EZLBPkPrFA = false;}
      if(YXFaknTreD == true){YXFaknTreD = false;}
      if(pnWpYtlfaE == true){pnWpYtlfaE = false;}
      if(LXAwhjZPhj == true){LXAwhjZPhj = false;}
      if(LVzZnjbDAh == true){LVzZnjbDAh = false;}
      if(XzTTiPDVbU == true){XzTTiPDVbU = false;}
      if(yjRAnAXJrA == true){yjRAnAXJrA = false;}
      if(OEKtrTowBn == true){OEKtrTowBn = false;}
      if(RifrfMDfNS == true){RifrfMDfNS = false;}
      if(gDmMkbEylm == true){gDmMkbEylm = false;}
      if(MSKzTSoZbO == true){MSKzTSoZbO = false;}
      if(aGTmDODYUb == true){aGTmDODYUb = false;}
      if(wqwZTKRxIP == true){wqwZTKRxIP = false;}
      if(PqKObzYfXM == true){PqKObzYfXM = false;}
      if(WdDyrZizJW == true){WdDyrZizJW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YTOMUDEIVS
{ 
  void LTGqQFnFEJ()
  { 
      bool BmxlhHkHfI = false;
      bool EmlRqbyVKj = false;
      bool IEinyqfUVd = false;
      bool XoNkBRSTPL = false;
      bool pUcyilKNsT = false;
      bool ftGwIxDJnq = false;
      bool bPkBkOYBQY = false;
      bool JeFzsnajFM = false;
      bool fSbCxdiQcE = false;
      bool NJfYjaiaNT = false;
      bool MJwTKAoHDT = false;
      bool VTEaLIniDG = false;
      bool fHYMLzzgOS = false;
      bool FAWkzWWHqw = false;
      bool obNIitFENb = false;
      bool mAWHnFjjIK = false;
      bool BHrjOVxSan = false;
      bool lfqGQDsQdR = false;
      bool tuTmeFcOwt = false;
      bool llyfugictM = false;
      string fTJnMbfnoZ;
      string XVIKbBktWD;
      string SGTnyHUcsF;
      string acCxPdtrrE;
      string iWTiOifnmj;
      string dWGmZZzUpE;
      string HCtjytTKtx;
      string GsCRTulkZO;
      string afpIaEWPXp;
      string dYBmxgbjkU;
      string PUsockTnSe;
      string mOubcaMkIt;
      string WDmEThqPUm;
      string SCAEzGlBfp;
      string jiwrCPcZJW;
      string TqapxLgoVu;
      string sETeLkOpbW;
      string nLFSJnHtCD;
      string EQFyTbbJHm;
      string YxejwePRgR;
      if(fTJnMbfnoZ == PUsockTnSe){BmxlhHkHfI = true;}
      else if(PUsockTnSe == fTJnMbfnoZ){MJwTKAoHDT = true;}
      if(XVIKbBktWD == mOubcaMkIt){EmlRqbyVKj = true;}
      else if(mOubcaMkIt == XVIKbBktWD){VTEaLIniDG = true;}
      if(SGTnyHUcsF == WDmEThqPUm){IEinyqfUVd = true;}
      else if(WDmEThqPUm == SGTnyHUcsF){fHYMLzzgOS = true;}
      if(acCxPdtrrE == SCAEzGlBfp){XoNkBRSTPL = true;}
      else if(SCAEzGlBfp == acCxPdtrrE){FAWkzWWHqw = true;}
      if(iWTiOifnmj == jiwrCPcZJW){pUcyilKNsT = true;}
      else if(jiwrCPcZJW == iWTiOifnmj){obNIitFENb = true;}
      if(dWGmZZzUpE == TqapxLgoVu){ftGwIxDJnq = true;}
      else if(TqapxLgoVu == dWGmZZzUpE){mAWHnFjjIK = true;}
      if(HCtjytTKtx == sETeLkOpbW){bPkBkOYBQY = true;}
      else if(sETeLkOpbW == HCtjytTKtx){BHrjOVxSan = true;}
      if(GsCRTulkZO == nLFSJnHtCD){JeFzsnajFM = true;}
      if(afpIaEWPXp == EQFyTbbJHm){fSbCxdiQcE = true;}
      if(dYBmxgbjkU == YxejwePRgR){NJfYjaiaNT = true;}
      while(nLFSJnHtCD == GsCRTulkZO){lfqGQDsQdR = true;}
      while(EQFyTbbJHm == EQFyTbbJHm){tuTmeFcOwt = true;}
      while(YxejwePRgR == YxejwePRgR){llyfugictM = true;}
      if(BmxlhHkHfI == true){BmxlhHkHfI = false;}
      if(EmlRqbyVKj == true){EmlRqbyVKj = false;}
      if(IEinyqfUVd == true){IEinyqfUVd = false;}
      if(XoNkBRSTPL == true){XoNkBRSTPL = false;}
      if(pUcyilKNsT == true){pUcyilKNsT = false;}
      if(ftGwIxDJnq == true){ftGwIxDJnq = false;}
      if(bPkBkOYBQY == true){bPkBkOYBQY = false;}
      if(JeFzsnajFM == true){JeFzsnajFM = false;}
      if(fSbCxdiQcE == true){fSbCxdiQcE = false;}
      if(NJfYjaiaNT == true){NJfYjaiaNT = false;}
      if(MJwTKAoHDT == true){MJwTKAoHDT = false;}
      if(VTEaLIniDG == true){VTEaLIniDG = false;}
      if(fHYMLzzgOS == true){fHYMLzzgOS = false;}
      if(FAWkzWWHqw == true){FAWkzWWHqw = false;}
      if(obNIitFENb == true){obNIitFENb = false;}
      if(mAWHnFjjIK == true){mAWHnFjjIK = false;}
      if(BHrjOVxSan == true){BHrjOVxSan = false;}
      if(lfqGQDsQdR == true){lfqGQDsQdR = false;}
      if(tuTmeFcOwt == true){tuTmeFcOwt = false;}
      if(llyfugictM == true){llyfugictM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUMUAMCCSC
{ 
  void cIRnbtJfnN()
  { 
      bool elhTkZkezo = false;
      bool hfifAoGTyf = false;
      bool WbCbrYjBAO = false;
      bool nUUJDGoYaP = false;
      bool mjUUgbMsBk = false;
      bool IxHsYCiFbL = false;
      bool pjejBNKZcs = false;
      bool AgsirmGhuQ = false;
      bool LqzOFpMbkA = false;
      bool XixOYDFjTT = false;
      bool QmQIkaEYAl = false;
      bool wBKLzzjPeK = false;
      bool BhnbVQieJo = false;
      bool gVNbzYZqdd = false;
      bool lnbzEWYlOZ = false;
      bool SpFJRiynmT = false;
      bool qZOKEZmiLa = false;
      bool YskAYMFoWy = false;
      bool rxPiWqQEJQ = false;
      bool ZlEKlMYRte = false;
      string VQfjWtaJSX;
      string aGpUIDFfOw;
      string SXGGOGYQdD;
      string DZbRodrNRi;
      string pRioAJXJDx;
      string DbdSTxJYVP;
      string VKeOTAeXfd;
      string LqOfFAoQFE;
      string hOMgAbwIyq;
      string TSrBNfmTUz;
      string eAdYlMMyNS;
      string IsTRhGxyOr;
      string EVZoJryMRY;
      string NUwFYhknun;
      string OyueiazaTG;
      string inFbuJaoOs;
      string NAfnFmwNrz;
      string VIDacGatFi;
      string sXsLpYPTKP;
      string HwYBZORGYw;
      if(VQfjWtaJSX == eAdYlMMyNS){elhTkZkezo = true;}
      else if(eAdYlMMyNS == VQfjWtaJSX){QmQIkaEYAl = true;}
      if(aGpUIDFfOw == IsTRhGxyOr){hfifAoGTyf = true;}
      else if(IsTRhGxyOr == aGpUIDFfOw){wBKLzzjPeK = true;}
      if(SXGGOGYQdD == EVZoJryMRY){WbCbrYjBAO = true;}
      else if(EVZoJryMRY == SXGGOGYQdD){BhnbVQieJo = true;}
      if(DZbRodrNRi == NUwFYhknun){nUUJDGoYaP = true;}
      else if(NUwFYhknun == DZbRodrNRi){gVNbzYZqdd = true;}
      if(pRioAJXJDx == OyueiazaTG){mjUUgbMsBk = true;}
      else if(OyueiazaTG == pRioAJXJDx){lnbzEWYlOZ = true;}
      if(DbdSTxJYVP == inFbuJaoOs){IxHsYCiFbL = true;}
      else if(inFbuJaoOs == DbdSTxJYVP){SpFJRiynmT = true;}
      if(VKeOTAeXfd == NAfnFmwNrz){pjejBNKZcs = true;}
      else if(NAfnFmwNrz == VKeOTAeXfd){qZOKEZmiLa = true;}
      if(LqOfFAoQFE == VIDacGatFi){AgsirmGhuQ = true;}
      if(hOMgAbwIyq == sXsLpYPTKP){LqzOFpMbkA = true;}
      if(TSrBNfmTUz == HwYBZORGYw){XixOYDFjTT = true;}
      while(VIDacGatFi == LqOfFAoQFE){YskAYMFoWy = true;}
      while(sXsLpYPTKP == sXsLpYPTKP){rxPiWqQEJQ = true;}
      while(HwYBZORGYw == HwYBZORGYw){ZlEKlMYRte = true;}
      if(elhTkZkezo == true){elhTkZkezo = false;}
      if(hfifAoGTyf == true){hfifAoGTyf = false;}
      if(WbCbrYjBAO == true){WbCbrYjBAO = false;}
      if(nUUJDGoYaP == true){nUUJDGoYaP = false;}
      if(mjUUgbMsBk == true){mjUUgbMsBk = false;}
      if(IxHsYCiFbL == true){IxHsYCiFbL = false;}
      if(pjejBNKZcs == true){pjejBNKZcs = false;}
      if(AgsirmGhuQ == true){AgsirmGhuQ = false;}
      if(LqzOFpMbkA == true){LqzOFpMbkA = false;}
      if(XixOYDFjTT == true){XixOYDFjTT = false;}
      if(QmQIkaEYAl == true){QmQIkaEYAl = false;}
      if(wBKLzzjPeK == true){wBKLzzjPeK = false;}
      if(BhnbVQieJo == true){BhnbVQieJo = false;}
      if(gVNbzYZqdd == true){gVNbzYZqdd = false;}
      if(lnbzEWYlOZ == true){lnbzEWYlOZ = false;}
      if(SpFJRiynmT == true){SpFJRiynmT = false;}
      if(qZOKEZmiLa == true){qZOKEZmiLa = false;}
      if(YskAYMFoWy == true){YskAYMFoWy = false;}
      if(rxPiWqQEJQ == true){rxPiWqQEJQ = false;}
      if(ZlEKlMYRte == true){ZlEKlMYRte = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BNZFQGGNDR
{ 
  void eJpdpBGDpR()
  { 
      bool wftfNwlOgw = false;
      bool yrNmKVNsuS = false;
      bool kJjnqZtksg = false;
      bool WrbQQqQdJi = false;
      bool IDfgXabZqP = false;
      bool ImcJNlwGnm = false;
      bool CBVzZGQxVS = false;
      bool EjjLKhdCPQ = false;
      bool yTscXjPRCd = false;
      bool uKoVgGgfGR = false;
      bool KdDYKYCQzf = false;
      bool IspXohHsbp = false;
      bool qyuqXttOeD = false;
      bool AywxGTQURy = false;
      bool gzSVVBTRfy = false;
      bool zmDQaLiLAQ = false;
      bool enkueKxrRU = false;
      bool RlacJrfYVW = false;
      bool ZchgEMteWt = false;
      bool kEUBTrNWpL = false;
      string UjFMNEztjY;
      string LfzYFBXVgj;
      string aCinEaBnkZ;
      string IxOclnBIDQ;
      string fHABMrQjwA;
      string LohKCSBRHl;
      string CKIKQORWmR;
      string APRPDTChaM;
      string KRqjNSOEZT;
      string liAROVypjy;
      string atxezwXRGi;
      string PTpuajSXwy;
      string zMwSeRPABg;
      string UMxckQTMjR;
      string twxqDRsEpd;
      string CZskzNxdzh;
      string fXQZNDVNKK;
      string PGmdDCPFPM;
      string XKJWetSMcW;
      string SpMCkWfXcz;
      if(UjFMNEztjY == atxezwXRGi){wftfNwlOgw = true;}
      else if(atxezwXRGi == UjFMNEztjY){KdDYKYCQzf = true;}
      if(LfzYFBXVgj == PTpuajSXwy){yrNmKVNsuS = true;}
      else if(PTpuajSXwy == LfzYFBXVgj){IspXohHsbp = true;}
      if(aCinEaBnkZ == zMwSeRPABg){kJjnqZtksg = true;}
      else if(zMwSeRPABg == aCinEaBnkZ){qyuqXttOeD = true;}
      if(IxOclnBIDQ == UMxckQTMjR){WrbQQqQdJi = true;}
      else if(UMxckQTMjR == IxOclnBIDQ){AywxGTQURy = true;}
      if(fHABMrQjwA == twxqDRsEpd){IDfgXabZqP = true;}
      else if(twxqDRsEpd == fHABMrQjwA){gzSVVBTRfy = true;}
      if(LohKCSBRHl == CZskzNxdzh){ImcJNlwGnm = true;}
      else if(CZskzNxdzh == LohKCSBRHl){zmDQaLiLAQ = true;}
      if(CKIKQORWmR == fXQZNDVNKK){CBVzZGQxVS = true;}
      else if(fXQZNDVNKK == CKIKQORWmR){enkueKxrRU = true;}
      if(APRPDTChaM == PGmdDCPFPM){EjjLKhdCPQ = true;}
      if(KRqjNSOEZT == XKJWetSMcW){yTscXjPRCd = true;}
      if(liAROVypjy == SpMCkWfXcz){uKoVgGgfGR = true;}
      while(PGmdDCPFPM == APRPDTChaM){RlacJrfYVW = true;}
      while(XKJWetSMcW == XKJWetSMcW){ZchgEMteWt = true;}
      while(SpMCkWfXcz == SpMCkWfXcz){kEUBTrNWpL = true;}
      if(wftfNwlOgw == true){wftfNwlOgw = false;}
      if(yrNmKVNsuS == true){yrNmKVNsuS = false;}
      if(kJjnqZtksg == true){kJjnqZtksg = false;}
      if(WrbQQqQdJi == true){WrbQQqQdJi = false;}
      if(IDfgXabZqP == true){IDfgXabZqP = false;}
      if(ImcJNlwGnm == true){ImcJNlwGnm = false;}
      if(CBVzZGQxVS == true){CBVzZGQxVS = false;}
      if(EjjLKhdCPQ == true){EjjLKhdCPQ = false;}
      if(yTscXjPRCd == true){yTscXjPRCd = false;}
      if(uKoVgGgfGR == true){uKoVgGgfGR = false;}
      if(KdDYKYCQzf == true){KdDYKYCQzf = false;}
      if(IspXohHsbp == true){IspXohHsbp = false;}
      if(qyuqXttOeD == true){qyuqXttOeD = false;}
      if(AywxGTQURy == true){AywxGTQURy = false;}
      if(gzSVVBTRfy == true){gzSVVBTRfy = false;}
      if(zmDQaLiLAQ == true){zmDQaLiLAQ = false;}
      if(enkueKxrRU == true){enkueKxrRU = false;}
      if(RlacJrfYVW == true){RlacJrfYVW = false;}
      if(ZchgEMteWt == true){ZchgEMteWt = false;}
      if(kEUBTrNWpL == true){kEUBTrNWpL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQYYZXMNLE
{ 
  void poWJnDPdfo()
  { 
      bool YABBMhsNDR = false;
      bool UaTgVicoFs = false;
      bool eZDdOZQmFy = false;
      bool uctNBcVdoB = false;
      bool tXaiZypIWA = false;
      bool tItzTzwWll = false;
      bool QFIFVqfGer = false;
      bool NyzEyGzTDQ = false;
      bool iIPEDlhusB = false;
      bool fyqCjnOVMi = false;
      bool RjcdmuJpAN = false;
      bool AcSVCIoEBi = false;
      bool IkNdMOGwTK = false;
      bool qdHUyzfkRH = false;
      bool crtfBDeVAb = false;
      bool zKTcZgWzRX = false;
      bool nMVpVWVyXD = false;
      bool bDmsFQqgbI = false;
      bool jkwrKfJdtQ = false;
      bool cgTsTQVDJe = false;
      string RssUHdJLRe;
      string OBAyCxIraN;
      string OlKTtRDBKo;
      string VyeWBQtSGA;
      string yBLiLlDEuj;
      string tNQbFfhYap;
      string aHBbIQVcwk;
      string CpkZOMZbII;
      string NyFauIgDRU;
      string hUrQZpAjZu;
      string PZHJgEcqNr;
      string FFQRbbCZgA;
      string iSLaChxUAX;
      string MoCMrmqwsq;
      string eooYOcEaox;
      string nZDYLxOfGz;
      string GIqofQDDYn;
      string kFgoVtcmLZ;
      string cWeCjmldAu;
      string YKosjWyAry;
      if(RssUHdJLRe == PZHJgEcqNr){YABBMhsNDR = true;}
      else if(PZHJgEcqNr == RssUHdJLRe){RjcdmuJpAN = true;}
      if(OBAyCxIraN == FFQRbbCZgA){UaTgVicoFs = true;}
      else if(FFQRbbCZgA == OBAyCxIraN){AcSVCIoEBi = true;}
      if(OlKTtRDBKo == iSLaChxUAX){eZDdOZQmFy = true;}
      else if(iSLaChxUAX == OlKTtRDBKo){IkNdMOGwTK = true;}
      if(VyeWBQtSGA == MoCMrmqwsq){uctNBcVdoB = true;}
      else if(MoCMrmqwsq == VyeWBQtSGA){qdHUyzfkRH = true;}
      if(yBLiLlDEuj == eooYOcEaox){tXaiZypIWA = true;}
      else if(eooYOcEaox == yBLiLlDEuj){crtfBDeVAb = true;}
      if(tNQbFfhYap == nZDYLxOfGz){tItzTzwWll = true;}
      else if(nZDYLxOfGz == tNQbFfhYap){zKTcZgWzRX = true;}
      if(aHBbIQVcwk == GIqofQDDYn){QFIFVqfGer = true;}
      else if(GIqofQDDYn == aHBbIQVcwk){nMVpVWVyXD = true;}
      if(CpkZOMZbII == kFgoVtcmLZ){NyzEyGzTDQ = true;}
      if(NyFauIgDRU == cWeCjmldAu){iIPEDlhusB = true;}
      if(hUrQZpAjZu == YKosjWyAry){fyqCjnOVMi = true;}
      while(kFgoVtcmLZ == CpkZOMZbII){bDmsFQqgbI = true;}
      while(cWeCjmldAu == cWeCjmldAu){jkwrKfJdtQ = true;}
      while(YKosjWyAry == YKosjWyAry){cgTsTQVDJe = true;}
      if(YABBMhsNDR == true){YABBMhsNDR = false;}
      if(UaTgVicoFs == true){UaTgVicoFs = false;}
      if(eZDdOZQmFy == true){eZDdOZQmFy = false;}
      if(uctNBcVdoB == true){uctNBcVdoB = false;}
      if(tXaiZypIWA == true){tXaiZypIWA = false;}
      if(tItzTzwWll == true){tItzTzwWll = false;}
      if(QFIFVqfGer == true){QFIFVqfGer = false;}
      if(NyzEyGzTDQ == true){NyzEyGzTDQ = false;}
      if(iIPEDlhusB == true){iIPEDlhusB = false;}
      if(fyqCjnOVMi == true){fyqCjnOVMi = false;}
      if(RjcdmuJpAN == true){RjcdmuJpAN = false;}
      if(AcSVCIoEBi == true){AcSVCIoEBi = false;}
      if(IkNdMOGwTK == true){IkNdMOGwTK = false;}
      if(qdHUyzfkRH == true){qdHUyzfkRH = false;}
      if(crtfBDeVAb == true){crtfBDeVAb = false;}
      if(zKTcZgWzRX == true){zKTcZgWzRX = false;}
      if(nMVpVWVyXD == true){nMVpVWVyXD = false;}
      if(bDmsFQqgbI == true){bDmsFQqgbI = false;}
      if(jkwrKfJdtQ == true){jkwrKfJdtQ = false;}
      if(cgTsTQVDJe == true){cgTsTQVDJe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DTXWWDXSHG
{ 
  void VJHRLocFDS()
  { 
      bool cNizJRkUnN = false;
      bool bTTaydIjSX = false;
      bool MFNNLWrcsL = false;
      bool aclSuoURrj = false;
      bool zqtoCFNsCB = false;
      bool MVCeTXzVnm = false;
      bool ZIacmygAfJ = false;
      bool JqriXVLXLF = false;
      bool IyZqyEZGyX = false;
      bool ozcEKqPRCD = false;
      bool XMNsrVcTHy = false;
      bool LbKhdahjeh = false;
      bool YZBIUKNmXf = false;
      bool FsUHhwkfzb = false;
      bool aGzALMntai = false;
      bool IfmUexKFYh = false;
      bool HouarSGCAh = false;
      bool pCjCGRaBxH = false;
      bool VSMoXZGAcj = false;
      bool kfHRTlLXHr = false;
      string EinkmPuEDz;
      string GcmlCylXly;
      string BlqIUYjCpn;
      string CkrSABYkRA;
      string EHyrpAeKqG;
      string MgnxARqfPN;
      string frOPwVkTlB;
      string ZAFktsnzRT;
      string tZKiaVwuSh;
      string KrVEUMshuT;
      string PKXpgMaDDH;
      string drNuTGgena;
      string ZpBEqgdBQg;
      string zFDxDiBUBO;
      string tsqLERdZjO;
      string eOtUtZJTzA;
      string hYlVIXnQqk;
      string EMdZfgyozY;
      string CDQBCjLiCd;
      string YhUAfUGVDf;
      if(EinkmPuEDz == PKXpgMaDDH){cNizJRkUnN = true;}
      else if(PKXpgMaDDH == EinkmPuEDz){XMNsrVcTHy = true;}
      if(GcmlCylXly == drNuTGgena){bTTaydIjSX = true;}
      else if(drNuTGgena == GcmlCylXly){LbKhdahjeh = true;}
      if(BlqIUYjCpn == ZpBEqgdBQg){MFNNLWrcsL = true;}
      else if(ZpBEqgdBQg == BlqIUYjCpn){YZBIUKNmXf = true;}
      if(CkrSABYkRA == zFDxDiBUBO){aclSuoURrj = true;}
      else if(zFDxDiBUBO == CkrSABYkRA){FsUHhwkfzb = true;}
      if(EHyrpAeKqG == tsqLERdZjO){zqtoCFNsCB = true;}
      else if(tsqLERdZjO == EHyrpAeKqG){aGzALMntai = true;}
      if(MgnxARqfPN == eOtUtZJTzA){MVCeTXzVnm = true;}
      else if(eOtUtZJTzA == MgnxARqfPN){IfmUexKFYh = true;}
      if(frOPwVkTlB == hYlVIXnQqk){ZIacmygAfJ = true;}
      else if(hYlVIXnQqk == frOPwVkTlB){HouarSGCAh = true;}
      if(ZAFktsnzRT == EMdZfgyozY){JqriXVLXLF = true;}
      if(tZKiaVwuSh == CDQBCjLiCd){IyZqyEZGyX = true;}
      if(KrVEUMshuT == YhUAfUGVDf){ozcEKqPRCD = true;}
      while(EMdZfgyozY == ZAFktsnzRT){pCjCGRaBxH = true;}
      while(CDQBCjLiCd == CDQBCjLiCd){VSMoXZGAcj = true;}
      while(YhUAfUGVDf == YhUAfUGVDf){kfHRTlLXHr = true;}
      if(cNizJRkUnN == true){cNizJRkUnN = false;}
      if(bTTaydIjSX == true){bTTaydIjSX = false;}
      if(MFNNLWrcsL == true){MFNNLWrcsL = false;}
      if(aclSuoURrj == true){aclSuoURrj = false;}
      if(zqtoCFNsCB == true){zqtoCFNsCB = false;}
      if(MVCeTXzVnm == true){MVCeTXzVnm = false;}
      if(ZIacmygAfJ == true){ZIacmygAfJ = false;}
      if(JqriXVLXLF == true){JqriXVLXLF = false;}
      if(IyZqyEZGyX == true){IyZqyEZGyX = false;}
      if(ozcEKqPRCD == true){ozcEKqPRCD = false;}
      if(XMNsrVcTHy == true){XMNsrVcTHy = false;}
      if(LbKhdahjeh == true){LbKhdahjeh = false;}
      if(YZBIUKNmXf == true){YZBIUKNmXf = false;}
      if(FsUHhwkfzb == true){FsUHhwkfzb = false;}
      if(aGzALMntai == true){aGzALMntai = false;}
      if(IfmUexKFYh == true){IfmUexKFYh = false;}
      if(HouarSGCAh == true){HouarSGCAh = false;}
      if(pCjCGRaBxH == true){pCjCGRaBxH = false;}
      if(VSMoXZGAcj == true){VSMoXZGAcj = false;}
      if(kfHRTlLXHr == true){kfHRTlLXHr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDUIWOUXLS
{ 
  void AmJeQXgXBB()
  { 
      bool iWBaRRZqlo = false;
      bool QudGeKqkei = false;
      bool TcpVCeIdVV = false;
      bool HbQtVbgXMc = false;
      bool aQSTjmPQMo = false;
      bool oypOPGffXl = false;
      bool JuUQhodjjD = false;
      bool cTYCIDJWlP = false;
      bool PqQggIkCdP = false;
      bool uBzZTeuClu = false;
      bool JegJLUZnGL = false;
      bool xJsIWRenjY = false;
      bool DbFUHaTyic = false;
      bool IHjqGjKHVL = false;
      bool ixuSSkIqDB = false;
      bool AHSNqgZLBj = false;
      bool BaFdCpYCCl = false;
      bool HXRXoGflCW = false;
      bool SctgbBoWAY = false;
      bool KyFkKHqRQc = false;
      string nIMwxQREjV;
      string jInBEqlRaQ;
      string crVLnTrcuU;
      string YHycDjLSSo;
      string FusLzSTtGc;
      string WAWgOumBHc;
      string XnJOxbKLxU;
      string eTzlLhzJMV;
      string AyWSyXkROI;
      string wKKoQQldOW;
      string HHxkxDBkUf;
      string wdnlcZRpQY;
      string qsxoYTIKUt;
      string wUuoOrBkUt;
      string WzwhLSVYLp;
      string zuNofNJHMc;
      string tpPajbizWk;
      string YgVVCqxOdF;
      string yiyduAHFIA;
      string hsXrAfjVyj;
      if(nIMwxQREjV == HHxkxDBkUf){iWBaRRZqlo = true;}
      else if(HHxkxDBkUf == nIMwxQREjV){JegJLUZnGL = true;}
      if(jInBEqlRaQ == wdnlcZRpQY){QudGeKqkei = true;}
      else if(wdnlcZRpQY == jInBEqlRaQ){xJsIWRenjY = true;}
      if(crVLnTrcuU == qsxoYTIKUt){TcpVCeIdVV = true;}
      else if(qsxoYTIKUt == crVLnTrcuU){DbFUHaTyic = true;}
      if(YHycDjLSSo == wUuoOrBkUt){HbQtVbgXMc = true;}
      else if(wUuoOrBkUt == YHycDjLSSo){IHjqGjKHVL = true;}
      if(FusLzSTtGc == WzwhLSVYLp){aQSTjmPQMo = true;}
      else if(WzwhLSVYLp == FusLzSTtGc){ixuSSkIqDB = true;}
      if(WAWgOumBHc == zuNofNJHMc){oypOPGffXl = true;}
      else if(zuNofNJHMc == WAWgOumBHc){AHSNqgZLBj = true;}
      if(XnJOxbKLxU == tpPajbizWk){JuUQhodjjD = true;}
      else if(tpPajbizWk == XnJOxbKLxU){BaFdCpYCCl = true;}
      if(eTzlLhzJMV == YgVVCqxOdF){cTYCIDJWlP = true;}
      if(AyWSyXkROI == yiyduAHFIA){PqQggIkCdP = true;}
      if(wKKoQQldOW == hsXrAfjVyj){uBzZTeuClu = true;}
      while(YgVVCqxOdF == eTzlLhzJMV){HXRXoGflCW = true;}
      while(yiyduAHFIA == yiyduAHFIA){SctgbBoWAY = true;}
      while(hsXrAfjVyj == hsXrAfjVyj){KyFkKHqRQc = true;}
      if(iWBaRRZqlo == true){iWBaRRZqlo = false;}
      if(QudGeKqkei == true){QudGeKqkei = false;}
      if(TcpVCeIdVV == true){TcpVCeIdVV = false;}
      if(HbQtVbgXMc == true){HbQtVbgXMc = false;}
      if(aQSTjmPQMo == true){aQSTjmPQMo = false;}
      if(oypOPGffXl == true){oypOPGffXl = false;}
      if(JuUQhodjjD == true){JuUQhodjjD = false;}
      if(cTYCIDJWlP == true){cTYCIDJWlP = false;}
      if(PqQggIkCdP == true){PqQggIkCdP = false;}
      if(uBzZTeuClu == true){uBzZTeuClu = false;}
      if(JegJLUZnGL == true){JegJLUZnGL = false;}
      if(xJsIWRenjY == true){xJsIWRenjY = false;}
      if(DbFUHaTyic == true){DbFUHaTyic = false;}
      if(IHjqGjKHVL == true){IHjqGjKHVL = false;}
      if(ixuSSkIqDB == true){ixuSSkIqDB = false;}
      if(AHSNqgZLBj == true){AHSNqgZLBj = false;}
      if(BaFdCpYCCl == true){BaFdCpYCCl = false;}
      if(HXRXoGflCW == true){HXRXoGflCW = false;}
      if(SctgbBoWAY == true){SctgbBoWAY = false;}
      if(KyFkKHqRQc == true){KyFkKHqRQc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DUQFPILWTD
{ 
  void aNUaKmLDGK()
  { 
      bool qcjSMpQZjO = false;
      bool ddNCjjgiSY = false;
      bool TIDwNelMBL = false;
      bool tlznKrIRAw = false;
      bool xhTYiWAPmF = false;
      bool OLVhRiYnFh = false;
      bool DDXXTqeYrq = false;
      bool aPhWbkneNp = false;
      bool dWZwxhQQWa = false;
      bool TULSrsJwEr = false;
      bool rbWwdzczGf = false;
      bool usZOEgdbak = false;
      bool aNCQXGEPdh = false;
      bool bqZVyBAdRy = false;
      bool EQKpfZtwNL = false;
      bool PhVSQdZFXX = false;
      bool uNUYEDSEQC = false;
      bool fzKcgJDLkx = false;
      bool MHBRRtVHEU = false;
      bool btFtCqwkkb = false;
      string cObuNoKCyA;
      string ufTaxJxsAc;
      string jXuNauNFOF;
      string eAZZUfQowd;
      string ZEUjigbhZn;
      string XgopfETNUR;
      string aFnrUuFsFQ;
      string rHwWCeCKes;
      string TeeZhyLitQ;
      string LCUeCUPbOm;
      string bicIwPjSnB;
      string CIiayuZOKW;
      string iWzoFpmRUh;
      string OZwqRjCVdS;
      string OsusNDTsgG;
      string tBRrEEjnDF;
      string cRxGlbMqJN;
      string sEkqIpaGaB;
      string VskNmNIEmM;
      string AORXowuoGl;
      if(cObuNoKCyA == bicIwPjSnB){qcjSMpQZjO = true;}
      else if(bicIwPjSnB == cObuNoKCyA){rbWwdzczGf = true;}
      if(ufTaxJxsAc == CIiayuZOKW){ddNCjjgiSY = true;}
      else if(CIiayuZOKW == ufTaxJxsAc){usZOEgdbak = true;}
      if(jXuNauNFOF == iWzoFpmRUh){TIDwNelMBL = true;}
      else if(iWzoFpmRUh == jXuNauNFOF){aNCQXGEPdh = true;}
      if(eAZZUfQowd == OZwqRjCVdS){tlznKrIRAw = true;}
      else if(OZwqRjCVdS == eAZZUfQowd){bqZVyBAdRy = true;}
      if(ZEUjigbhZn == OsusNDTsgG){xhTYiWAPmF = true;}
      else if(OsusNDTsgG == ZEUjigbhZn){EQKpfZtwNL = true;}
      if(XgopfETNUR == tBRrEEjnDF){OLVhRiYnFh = true;}
      else if(tBRrEEjnDF == XgopfETNUR){PhVSQdZFXX = true;}
      if(aFnrUuFsFQ == cRxGlbMqJN){DDXXTqeYrq = true;}
      else if(cRxGlbMqJN == aFnrUuFsFQ){uNUYEDSEQC = true;}
      if(rHwWCeCKes == sEkqIpaGaB){aPhWbkneNp = true;}
      if(TeeZhyLitQ == VskNmNIEmM){dWZwxhQQWa = true;}
      if(LCUeCUPbOm == AORXowuoGl){TULSrsJwEr = true;}
      while(sEkqIpaGaB == rHwWCeCKes){fzKcgJDLkx = true;}
      while(VskNmNIEmM == VskNmNIEmM){MHBRRtVHEU = true;}
      while(AORXowuoGl == AORXowuoGl){btFtCqwkkb = true;}
      if(qcjSMpQZjO == true){qcjSMpQZjO = false;}
      if(ddNCjjgiSY == true){ddNCjjgiSY = false;}
      if(TIDwNelMBL == true){TIDwNelMBL = false;}
      if(tlznKrIRAw == true){tlznKrIRAw = false;}
      if(xhTYiWAPmF == true){xhTYiWAPmF = false;}
      if(OLVhRiYnFh == true){OLVhRiYnFh = false;}
      if(DDXXTqeYrq == true){DDXXTqeYrq = false;}
      if(aPhWbkneNp == true){aPhWbkneNp = false;}
      if(dWZwxhQQWa == true){dWZwxhQQWa = false;}
      if(TULSrsJwEr == true){TULSrsJwEr = false;}
      if(rbWwdzczGf == true){rbWwdzczGf = false;}
      if(usZOEgdbak == true){usZOEgdbak = false;}
      if(aNCQXGEPdh == true){aNCQXGEPdh = false;}
      if(bqZVyBAdRy == true){bqZVyBAdRy = false;}
      if(EQKpfZtwNL == true){EQKpfZtwNL = false;}
      if(PhVSQdZFXX == true){PhVSQdZFXX = false;}
      if(uNUYEDSEQC == true){uNUYEDSEQC = false;}
      if(fzKcgJDLkx == true){fzKcgJDLkx = false;}
      if(MHBRRtVHEU == true){MHBRRtVHEU = false;}
      if(btFtCqwkkb == true){btFtCqwkkb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PBQDKTSWKZ
{ 
  void LyEwuLieza()
  { 
      bool pmeUqIMqQD = false;
      bool ncxrYbttrb = false;
      bool EykdzSepub = false;
      bool zmNOikPxxh = false;
      bool EeSPlqOTpC = false;
      bool hUOlurBBVX = false;
      bool cWuoDBOiJm = false;
      bool MwwKWYfVrH = false;
      bool DKzssdXaSq = false;
      bool iNbYEhjcMk = false;
      bool bfKCokYEPW = false;
      bool LfJNURWBwY = false;
      bool cnPSEzTWFn = false;
      bool oCIGfWAxEH = false;
      bool FTLweCEOEm = false;
      bool LhgnHnQryp = false;
      bool RByahIWCgx = false;
      bool QYxnSIcSmB = false;
      bool tFRSbGVUzr = false;
      bool GIzOpEUjOW = false;
      string ChJpflljPJ;
      string aDHQUpWWpH;
      string AGeBxZHSpj;
      string KVDklNprlE;
      string reYMjSLgXO;
      string fDdozwDHsG;
      string eStezEzVeH;
      string zdkkPVgRQd;
      string OauaDGqOlo;
      string JhzeZYksNf;
      string ToBPOCRsYd;
      string OlpOrDXSbr;
      string NjjoxQeFKq;
      string jnEkKYYeMB;
      string oyoHaXrjmV;
      string ASRUSiFMRx;
      string WMihsahEES;
      string erFZDOtbOY;
      string YtRnpRWiSa;
      string TMMOdbPHOz;
      if(ChJpflljPJ == ToBPOCRsYd){pmeUqIMqQD = true;}
      else if(ToBPOCRsYd == ChJpflljPJ){bfKCokYEPW = true;}
      if(aDHQUpWWpH == OlpOrDXSbr){ncxrYbttrb = true;}
      else if(OlpOrDXSbr == aDHQUpWWpH){LfJNURWBwY = true;}
      if(AGeBxZHSpj == NjjoxQeFKq){EykdzSepub = true;}
      else if(NjjoxQeFKq == AGeBxZHSpj){cnPSEzTWFn = true;}
      if(KVDklNprlE == jnEkKYYeMB){zmNOikPxxh = true;}
      else if(jnEkKYYeMB == KVDklNprlE){oCIGfWAxEH = true;}
      if(reYMjSLgXO == oyoHaXrjmV){EeSPlqOTpC = true;}
      else if(oyoHaXrjmV == reYMjSLgXO){FTLweCEOEm = true;}
      if(fDdozwDHsG == ASRUSiFMRx){hUOlurBBVX = true;}
      else if(ASRUSiFMRx == fDdozwDHsG){LhgnHnQryp = true;}
      if(eStezEzVeH == WMihsahEES){cWuoDBOiJm = true;}
      else if(WMihsahEES == eStezEzVeH){RByahIWCgx = true;}
      if(zdkkPVgRQd == erFZDOtbOY){MwwKWYfVrH = true;}
      if(OauaDGqOlo == YtRnpRWiSa){DKzssdXaSq = true;}
      if(JhzeZYksNf == TMMOdbPHOz){iNbYEhjcMk = true;}
      while(erFZDOtbOY == zdkkPVgRQd){QYxnSIcSmB = true;}
      while(YtRnpRWiSa == YtRnpRWiSa){tFRSbGVUzr = true;}
      while(TMMOdbPHOz == TMMOdbPHOz){GIzOpEUjOW = true;}
      if(pmeUqIMqQD == true){pmeUqIMqQD = false;}
      if(ncxrYbttrb == true){ncxrYbttrb = false;}
      if(EykdzSepub == true){EykdzSepub = false;}
      if(zmNOikPxxh == true){zmNOikPxxh = false;}
      if(EeSPlqOTpC == true){EeSPlqOTpC = false;}
      if(hUOlurBBVX == true){hUOlurBBVX = false;}
      if(cWuoDBOiJm == true){cWuoDBOiJm = false;}
      if(MwwKWYfVrH == true){MwwKWYfVrH = false;}
      if(DKzssdXaSq == true){DKzssdXaSq = false;}
      if(iNbYEhjcMk == true){iNbYEhjcMk = false;}
      if(bfKCokYEPW == true){bfKCokYEPW = false;}
      if(LfJNURWBwY == true){LfJNURWBwY = false;}
      if(cnPSEzTWFn == true){cnPSEzTWFn = false;}
      if(oCIGfWAxEH == true){oCIGfWAxEH = false;}
      if(FTLweCEOEm == true){FTLweCEOEm = false;}
      if(LhgnHnQryp == true){LhgnHnQryp = false;}
      if(RByahIWCgx == true){RByahIWCgx = false;}
      if(QYxnSIcSmB == true){QYxnSIcSmB = false;}
      if(tFRSbGVUzr == true){tFRSbGVUzr = false;}
      if(GIzOpEUjOW == true){GIzOpEUjOW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJKKEYSMGV
{ 
  void jMDiCpzwRa()
  { 
      bool JcGVmKUuog = false;
      bool NBruQcTMQh = false;
      bool JfyerFzHWd = false;
      bool kLhfDRgirX = false;
      bool rOggssnfhR = false;
      bool LoejHcdbdg = false;
      bool KMYLuCSMqz = false;
      bool ukTrotyQky = false;
      bool RTZERwfxYa = false;
      bool mEFLMepVkp = false;
      bool ZbohVaUluM = false;
      bool eNpePqmTsz = false;
      bool WVmQMqfIfK = false;
      bool EceuYoeqip = false;
      bool asCLuZOZuV = false;
      bool rWblTEnXVe = false;
      bool uMGkIBhuGZ = false;
      bool LukCYcTbUl = false;
      bool cFNJSgAsbU = false;
      bool BGVDuOmRDt = false;
      string qQAIgWitco;
      string yWUoErLsQo;
      string ulGQskXHXs;
      string iYCLfuVXnf;
      string XOZUdrYfqR;
      string krglPEKjPu;
      string zaWjGZTJJJ;
      string VnFjRfMkmB;
      string LrQFHqqQwb;
      string jlHrfwroOD;
      string YPVguwlwUi;
      string qYwOiHKQbO;
      string hDNgYjgNEU;
      string nXWicwViKK;
      string EtuMjLosIY;
      string laMzUUBoIL;
      string PYrztTCMlm;
      string laGRKnHAwM;
      string tmEeiMKWOH;
      string tfaytfCwSQ;
      if(qQAIgWitco == YPVguwlwUi){JcGVmKUuog = true;}
      else if(YPVguwlwUi == qQAIgWitco){ZbohVaUluM = true;}
      if(yWUoErLsQo == qYwOiHKQbO){NBruQcTMQh = true;}
      else if(qYwOiHKQbO == yWUoErLsQo){eNpePqmTsz = true;}
      if(ulGQskXHXs == hDNgYjgNEU){JfyerFzHWd = true;}
      else if(hDNgYjgNEU == ulGQskXHXs){WVmQMqfIfK = true;}
      if(iYCLfuVXnf == nXWicwViKK){kLhfDRgirX = true;}
      else if(nXWicwViKK == iYCLfuVXnf){EceuYoeqip = true;}
      if(XOZUdrYfqR == EtuMjLosIY){rOggssnfhR = true;}
      else if(EtuMjLosIY == XOZUdrYfqR){asCLuZOZuV = true;}
      if(krglPEKjPu == laMzUUBoIL){LoejHcdbdg = true;}
      else if(laMzUUBoIL == krglPEKjPu){rWblTEnXVe = true;}
      if(zaWjGZTJJJ == PYrztTCMlm){KMYLuCSMqz = true;}
      else if(PYrztTCMlm == zaWjGZTJJJ){uMGkIBhuGZ = true;}
      if(VnFjRfMkmB == laGRKnHAwM){ukTrotyQky = true;}
      if(LrQFHqqQwb == tmEeiMKWOH){RTZERwfxYa = true;}
      if(jlHrfwroOD == tfaytfCwSQ){mEFLMepVkp = true;}
      while(laGRKnHAwM == VnFjRfMkmB){LukCYcTbUl = true;}
      while(tmEeiMKWOH == tmEeiMKWOH){cFNJSgAsbU = true;}
      while(tfaytfCwSQ == tfaytfCwSQ){BGVDuOmRDt = true;}
      if(JcGVmKUuog == true){JcGVmKUuog = false;}
      if(NBruQcTMQh == true){NBruQcTMQh = false;}
      if(JfyerFzHWd == true){JfyerFzHWd = false;}
      if(kLhfDRgirX == true){kLhfDRgirX = false;}
      if(rOggssnfhR == true){rOggssnfhR = false;}
      if(LoejHcdbdg == true){LoejHcdbdg = false;}
      if(KMYLuCSMqz == true){KMYLuCSMqz = false;}
      if(ukTrotyQky == true){ukTrotyQky = false;}
      if(RTZERwfxYa == true){RTZERwfxYa = false;}
      if(mEFLMepVkp == true){mEFLMepVkp = false;}
      if(ZbohVaUluM == true){ZbohVaUluM = false;}
      if(eNpePqmTsz == true){eNpePqmTsz = false;}
      if(WVmQMqfIfK == true){WVmQMqfIfK = false;}
      if(EceuYoeqip == true){EceuYoeqip = false;}
      if(asCLuZOZuV == true){asCLuZOZuV = false;}
      if(rWblTEnXVe == true){rWblTEnXVe = false;}
      if(uMGkIBhuGZ == true){uMGkIBhuGZ = false;}
      if(LukCYcTbUl == true){LukCYcTbUl = false;}
      if(cFNJSgAsbU == true){cFNJSgAsbU = false;}
      if(BGVDuOmRDt == true){BGVDuOmRDt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSHYXEMFTB
{ 
  void pOxNfsjzAS()
  { 
      bool DdimiVuVFs = false;
      bool AhGNKVJQQO = false;
      bool eVnEQwVMyx = false;
      bool zWJueiuJAb = false;
      bool rPnncZKHzL = false;
      bool LuXDQhoeWm = false;
      bool ziWItdXKia = false;
      bool ZzQoVOgzap = false;
      bool lONlkDyGdx = false;
      bool tQmMbJsftz = false;
      bool CzYXkLeihC = false;
      bool BpDfBkUkWp = false;
      bool eRfkgJMDNL = false;
      bool VAEbnlooAY = false;
      bool YOXbuDNGLp = false;
      bool oIJETjSmqb = false;
      bool zaVWfAkbrO = false;
      bool wfjxQQsEoc = false;
      bool wFqWWNqAHD = false;
      bool SByYZxrBuu = false;
      string pOhXUrtyLL;
      string rfpLZEJfUh;
      string WZtIkFyTaN;
      string WbmPjVhaSR;
      string ytRIsUgeCH;
      string fdiJlPTYmP;
      string taXxnQsaaE;
      string ViMCicIlPQ;
      string YSQSgsrddU;
      string BImDWXWTTc;
      string aGEykxQfZI;
      string GhIWqaJEQu;
      string XPwFCNuJfL;
      string GoSmoRORhj;
      string cMDUNTzQMw;
      string NRCXELJywX;
      string BGAOCRPVgY;
      string MrWgSLLbri;
      string Nexixnlthc;
      string IQVJhVLoRw;
      if(pOhXUrtyLL == aGEykxQfZI){DdimiVuVFs = true;}
      else if(aGEykxQfZI == pOhXUrtyLL){CzYXkLeihC = true;}
      if(rfpLZEJfUh == GhIWqaJEQu){AhGNKVJQQO = true;}
      else if(GhIWqaJEQu == rfpLZEJfUh){BpDfBkUkWp = true;}
      if(WZtIkFyTaN == XPwFCNuJfL){eVnEQwVMyx = true;}
      else if(XPwFCNuJfL == WZtIkFyTaN){eRfkgJMDNL = true;}
      if(WbmPjVhaSR == GoSmoRORhj){zWJueiuJAb = true;}
      else if(GoSmoRORhj == WbmPjVhaSR){VAEbnlooAY = true;}
      if(ytRIsUgeCH == cMDUNTzQMw){rPnncZKHzL = true;}
      else if(cMDUNTzQMw == ytRIsUgeCH){YOXbuDNGLp = true;}
      if(fdiJlPTYmP == NRCXELJywX){LuXDQhoeWm = true;}
      else if(NRCXELJywX == fdiJlPTYmP){oIJETjSmqb = true;}
      if(taXxnQsaaE == BGAOCRPVgY){ziWItdXKia = true;}
      else if(BGAOCRPVgY == taXxnQsaaE){zaVWfAkbrO = true;}
      if(ViMCicIlPQ == MrWgSLLbri){ZzQoVOgzap = true;}
      if(YSQSgsrddU == Nexixnlthc){lONlkDyGdx = true;}
      if(BImDWXWTTc == IQVJhVLoRw){tQmMbJsftz = true;}
      while(MrWgSLLbri == ViMCicIlPQ){wfjxQQsEoc = true;}
      while(Nexixnlthc == Nexixnlthc){wFqWWNqAHD = true;}
      while(IQVJhVLoRw == IQVJhVLoRw){SByYZxrBuu = true;}
      if(DdimiVuVFs == true){DdimiVuVFs = false;}
      if(AhGNKVJQQO == true){AhGNKVJQQO = false;}
      if(eVnEQwVMyx == true){eVnEQwVMyx = false;}
      if(zWJueiuJAb == true){zWJueiuJAb = false;}
      if(rPnncZKHzL == true){rPnncZKHzL = false;}
      if(LuXDQhoeWm == true){LuXDQhoeWm = false;}
      if(ziWItdXKia == true){ziWItdXKia = false;}
      if(ZzQoVOgzap == true){ZzQoVOgzap = false;}
      if(lONlkDyGdx == true){lONlkDyGdx = false;}
      if(tQmMbJsftz == true){tQmMbJsftz = false;}
      if(CzYXkLeihC == true){CzYXkLeihC = false;}
      if(BpDfBkUkWp == true){BpDfBkUkWp = false;}
      if(eRfkgJMDNL == true){eRfkgJMDNL = false;}
      if(VAEbnlooAY == true){VAEbnlooAY = false;}
      if(YOXbuDNGLp == true){YOXbuDNGLp = false;}
      if(oIJETjSmqb == true){oIJETjSmqb = false;}
      if(zaVWfAkbrO == true){zaVWfAkbrO = false;}
      if(wfjxQQsEoc == true){wfjxQQsEoc = false;}
      if(wFqWWNqAHD == true){wFqWWNqAHD = false;}
      if(SByYZxrBuu == true){SByYZxrBuu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TFWNYLJSHG
{ 
  void uLmwyCgVKy()
  { 
      bool qASokzIoXL = false;
      bool aldOheCqji = false;
      bool DylWYmDOeW = false;
      bool IfeRsegsAy = false;
      bool XYtDYhNkpd = false;
      bool UZCdzsOuQy = false;
      bool usJACtHMUD = false;
      bool xJqlLdEiyq = false;
      bool YRXBCidASA = false;
      bool PlcBCdOsAe = false;
      bool aBQmfLhPSU = false;
      bool nfxZYcVIyS = false;
      bool QGtUmLfojh = false;
      bool OLiSPWBjUp = false;
      bool ANhxMjoDcY = false;
      bool IGtgOTHuAU = false;
      bool esfjGbxdJC = false;
      bool bkmISCYwID = false;
      bool WcMKZHRBEw = false;
      bool OFjALHhxpj = false;
      string dwMqjaqXFW;
      string okuoPzwKbR;
      string YdpDzqbqPX;
      string HwtFaNMzSl;
      string IcjkxXqAwh;
      string QuWqlAFIrr;
      string yzHhPrpoOC;
      string lwrpJwsFFa;
      string AbthHMZCTa;
      string IEHZmIUCVE;
      string gBltuTDfhp;
      string HACQrVEZaD;
      string SmVmshoRDA;
      string apjAszpAlm;
      string JsUcTICphQ;
      string DubRlseyAN;
      string dlchOQQBWs;
      string fEmmtZSsTk;
      string fzilxfNROA;
      string TrAYIXQlNC;
      if(dwMqjaqXFW == gBltuTDfhp){qASokzIoXL = true;}
      else if(gBltuTDfhp == dwMqjaqXFW){aBQmfLhPSU = true;}
      if(okuoPzwKbR == HACQrVEZaD){aldOheCqji = true;}
      else if(HACQrVEZaD == okuoPzwKbR){nfxZYcVIyS = true;}
      if(YdpDzqbqPX == SmVmshoRDA){DylWYmDOeW = true;}
      else if(SmVmshoRDA == YdpDzqbqPX){QGtUmLfojh = true;}
      if(HwtFaNMzSl == apjAszpAlm){IfeRsegsAy = true;}
      else if(apjAszpAlm == HwtFaNMzSl){OLiSPWBjUp = true;}
      if(IcjkxXqAwh == JsUcTICphQ){XYtDYhNkpd = true;}
      else if(JsUcTICphQ == IcjkxXqAwh){ANhxMjoDcY = true;}
      if(QuWqlAFIrr == DubRlseyAN){UZCdzsOuQy = true;}
      else if(DubRlseyAN == QuWqlAFIrr){IGtgOTHuAU = true;}
      if(yzHhPrpoOC == dlchOQQBWs){usJACtHMUD = true;}
      else if(dlchOQQBWs == yzHhPrpoOC){esfjGbxdJC = true;}
      if(lwrpJwsFFa == fEmmtZSsTk){xJqlLdEiyq = true;}
      if(AbthHMZCTa == fzilxfNROA){YRXBCidASA = true;}
      if(IEHZmIUCVE == TrAYIXQlNC){PlcBCdOsAe = true;}
      while(fEmmtZSsTk == lwrpJwsFFa){bkmISCYwID = true;}
      while(fzilxfNROA == fzilxfNROA){WcMKZHRBEw = true;}
      while(TrAYIXQlNC == TrAYIXQlNC){OFjALHhxpj = true;}
      if(qASokzIoXL == true){qASokzIoXL = false;}
      if(aldOheCqji == true){aldOheCqji = false;}
      if(DylWYmDOeW == true){DylWYmDOeW = false;}
      if(IfeRsegsAy == true){IfeRsegsAy = false;}
      if(XYtDYhNkpd == true){XYtDYhNkpd = false;}
      if(UZCdzsOuQy == true){UZCdzsOuQy = false;}
      if(usJACtHMUD == true){usJACtHMUD = false;}
      if(xJqlLdEiyq == true){xJqlLdEiyq = false;}
      if(YRXBCidASA == true){YRXBCidASA = false;}
      if(PlcBCdOsAe == true){PlcBCdOsAe = false;}
      if(aBQmfLhPSU == true){aBQmfLhPSU = false;}
      if(nfxZYcVIyS == true){nfxZYcVIyS = false;}
      if(QGtUmLfojh == true){QGtUmLfojh = false;}
      if(OLiSPWBjUp == true){OLiSPWBjUp = false;}
      if(ANhxMjoDcY == true){ANhxMjoDcY = false;}
      if(IGtgOTHuAU == true){IGtgOTHuAU = false;}
      if(esfjGbxdJC == true){esfjGbxdJC = false;}
      if(bkmISCYwID == true){bkmISCYwID = false;}
      if(WcMKZHRBEw == true){WcMKZHRBEw = false;}
      if(OFjALHhxpj == true){OFjALHhxpj = false;}
    } 
}; 
