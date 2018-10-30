#include "CSX_Utils.h"

static const DWORD dwModuleDelay = 100;
//[junk_enable /]
namespace CSX
{
	namespace Utils
	{
		/* Wait dwMsec Load Module */

		bool IsModuleLoad(PCHAR szModule, DWORD dwMsec)
		{
			HMODULE hModule = GetModuleHandleA(szModule);

			if (!hModule)
			{
				DWORD dwMsecFind = 0;

				while (!hModule)
				{
					if (dwMsecFind == dwMsec)
						return false;

					hModule = GetModuleHandleA(szModule);

					HANDLE hEvent = CreateEventA(0, true, false, 0);
					WaitForSingleObject(hEvent, dwModuleDelay);
					CloseHandle(hEvent);

					dwMsecFind += dwModuleDelay;
				}
			}

			return true;
		}

		/* Get Current Process Path */

		string GetCurrentProcessPath()
		{
			string ProcessPath = "";

			char szFileName[MAX_PATH] = { 0 };

			if (GetModuleFileNameA(0, szFileName, MAX_PATH))
				ProcessPath = szFileName;

			return ProcessPath;
		}

		/* Get Current Process Name */

		string GetCurrentProcessName()
		{
			string ProcessName = GetCurrentProcessPath();

			if (!ProcessName.empty())
			{
				ProcessName = ProcessName.erase(0, ProcessName.find_last_of("\\/") + 1);
				return ProcessName;
			}

			return "";
		}

		/* Get Module File Path */

		string GetModuleFilePath(HMODULE hModule)
		{
			string ModuleName = "";
			char szFileName[MAX_PATH] = { 0 };

			if (GetModuleFileNameA(hModule, szFileName, MAX_PATH))
				ModuleName = szFileName;

			return ModuleName;
		}

		/* Get Module Dir */

		string GetModuleBaseDir(HMODULE hModule)
		{
			string ModulePath = GetModuleFilePath(hModule);
			return ModulePath.substr(0, ModulePath.find_last_of("\\/"));
		}

		/* Random Int Range */

		int RandomIntRange(int min, int max)
		{
			static bool first = true;

			if (first)
			{
				srand(GetTickCount());
				first = false;
			}

			return min + rand() % (max - min);
		}

		/* Get hwProfile GUID */

		string GetHwProfileGUID()
		{
			HW_PROFILE_INFO hwProfileInfo = { 0 };

			if (GetCurrentHwProfileA(&hwProfileInfo) != NULL)
			{
				return hwProfileInfo.szHwProfileGuid;
			}
			else
				return "null";

			return hwProfileInfo.szHwProfileGuid;
		}

		/* Return False If Read Ptr Error */

		bool IsBadReadPtr(PVOID pPointer)
		{
			MEMORY_BASIC_INFORMATION mbi = { 0 };

			if (VirtualQuery(pPointer, &mbi, sizeof(mbi)))
			{
				DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);

				bool ret = !(mbi.Protect & mask);

				if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS))
					ret = true;

				return ret;
			}

			return true;
		}

		/* Unicode To Utf8 Convert */

		BSTR ConvertStringToBSTR_UTF8(const char* szBuff)
		{
			if (!szBuff) return NULL;
			DWORD cwch;
			BSTR wsOut(NULL);

			if (cwch = MultiByteToWideChar(CP_UTF8, 0, szBuff, -1, NULL, 0))
			{
				cwch--;
				wsOut = SysAllocStringLen(NULL, cwch);
				if (wsOut)
				{
					if (!MultiByteToWideChar(CP_UTF8, 0, szBuff, -1, wsOut, cwch))
					{
						if (ERROR_INSUFFICIENT_BUFFER == ::GetLastError())
							return wsOut;

						SysFreeString(wsOut);
						wsOut = NULL;
					}
				}

			};

			return wsOut;
		}

		std::string GetHackWorkingDirectory()
		{
			//[enc_string_enable /]
			HKEY rKey;
			TCHAR Path[256] = { 0 };
			DWORD RegetPath = sizeof(Path);
			RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Indigo", NULL, KEY_QUERY_VALUE, &rKey);
			RegQueryValueEx(rKey, "path", NULL, NULL, (LPBYTE)&Path, &RegetPath);
			return Path;
			//[enc_string_disable /]
		};
	}
}








































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QOJXKXXINH
{ 
  void XElBHfLXFV()
  { 
      bool wMciLQbixO = false;
      bool UKhdWUjgQS = false;
      bool RwTCaAHZfb = false;
      bool LFxuYnskVh = false;
      bool XVxWdIUcIj = false;
      bool mteJJzrZIL = false;
      bool JBCUDOMlEh = false;
      bool bzLhuuzwYR = false;
      bool eeRwoQZnkZ = false;
      bool wScKYWSbTO = false;
      bool uhXZHnixON = false;
      bool AuApfejGfl = false;
      bool oYAelJWBJX = false;
      bool cWcKWxGqnB = false;
      bool gcZWZASlds = false;
      bool mMwgZWhrny = false;
      bool QhmpkcSpSi = false;
      bool XrSeFLycFl = false;
      bool qjWPkPaukA = false;
      bool PODojyojlw = false;
      string iprozNhaFA;
      string NEthxGfInM;
      string XIqeMoUzUh;
      string xhhZUTZdkS;
      string hxcaKGbmkY;
      string sWgZbayNcK;
      string riFXCeVUNc;
      string fBWVeZePTF;
      string MhNwnaBHxs;
      string UMBaZzrEYf;
      string kHZHrqzKuB;
      string whtWyKUJia;
      string dNWUHTAwwe;
      string hZqnUEHGDx;
      string apMwxmSdbO;
      string ehVxBWkFzX;
      string qDOQTVqFBs;
      string CNFlzmBZWU;
      string BVTgzAEtly;
      string SCGfFXbwca;
      if(iprozNhaFA == kHZHrqzKuB){wMciLQbixO = true;}
      else if(kHZHrqzKuB == iprozNhaFA){uhXZHnixON = true;}
      if(NEthxGfInM == whtWyKUJia){UKhdWUjgQS = true;}
      else if(whtWyKUJia == NEthxGfInM){AuApfejGfl = true;}
      if(XIqeMoUzUh == dNWUHTAwwe){RwTCaAHZfb = true;}
      else if(dNWUHTAwwe == XIqeMoUzUh){oYAelJWBJX = true;}
      if(xhhZUTZdkS == hZqnUEHGDx){LFxuYnskVh = true;}
      else if(hZqnUEHGDx == xhhZUTZdkS){cWcKWxGqnB = true;}
      if(hxcaKGbmkY == apMwxmSdbO){XVxWdIUcIj = true;}
      else if(apMwxmSdbO == hxcaKGbmkY){gcZWZASlds = true;}
      if(sWgZbayNcK == ehVxBWkFzX){mteJJzrZIL = true;}
      else if(ehVxBWkFzX == sWgZbayNcK){mMwgZWhrny = true;}
      if(riFXCeVUNc == qDOQTVqFBs){JBCUDOMlEh = true;}
      else if(qDOQTVqFBs == riFXCeVUNc){QhmpkcSpSi = true;}
      if(fBWVeZePTF == CNFlzmBZWU){bzLhuuzwYR = true;}
      if(MhNwnaBHxs == BVTgzAEtly){eeRwoQZnkZ = true;}
      if(UMBaZzrEYf == SCGfFXbwca){wScKYWSbTO = true;}
      while(CNFlzmBZWU == fBWVeZePTF){XrSeFLycFl = true;}
      while(BVTgzAEtly == BVTgzAEtly){qjWPkPaukA = true;}
      while(SCGfFXbwca == SCGfFXbwca){PODojyojlw = true;}
      if(wMciLQbixO == true){wMciLQbixO = false;}
      if(UKhdWUjgQS == true){UKhdWUjgQS = false;}
      if(RwTCaAHZfb == true){RwTCaAHZfb = false;}
      if(LFxuYnskVh == true){LFxuYnskVh = false;}
      if(XVxWdIUcIj == true){XVxWdIUcIj = false;}
      if(mteJJzrZIL == true){mteJJzrZIL = false;}
      if(JBCUDOMlEh == true){JBCUDOMlEh = false;}
      if(bzLhuuzwYR == true){bzLhuuzwYR = false;}
      if(eeRwoQZnkZ == true){eeRwoQZnkZ = false;}
      if(wScKYWSbTO == true){wScKYWSbTO = false;}
      if(uhXZHnixON == true){uhXZHnixON = false;}
      if(AuApfejGfl == true){AuApfejGfl = false;}
      if(oYAelJWBJX == true){oYAelJWBJX = false;}
      if(cWcKWxGqnB == true){cWcKWxGqnB = false;}
      if(gcZWZASlds == true){gcZWZASlds = false;}
      if(mMwgZWhrny == true){mMwgZWhrny = false;}
      if(QhmpkcSpSi == true){QhmpkcSpSi = false;}
      if(XrSeFLycFl == true){XrSeFLycFl = false;}
      if(qjWPkPaukA == true){qjWPkPaukA = false;}
      if(PODojyojlw == true){PODojyojlw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDCVGBMARJ
{ 
  void CKgmnjmQpF()
  { 
      bool lMaIwRonCW = false;
      bool yRDxqpSZyq = false;
      bool wzDkgaPNlV = false;
      bool gJpajDhGJU = false;
      bool hgzIZlPPfS = false;
      bool HeywpmJpaV = false;
      bool CbCfooacMm = false;
      bool ILPcJOztKu = false;
      bool KAgTOCLtjx = false;
      bool tqfnSFeSTj = false;
      bool KmCsJuOUmb = false;
      bool mOeeKBuhRl = false;
      bool dgrPrQfbKD = false;
      bool ifZakXynJS = false;
      bool npHIJeMAcQ = false;
      bool KwBhGculAr = false;
      bool PlKirHoEtm = false;
      bool DHYzymZjFM = false;
      bool EfysrlerTH = false;
      bool cLnQDBfXPC = false;
      string uziUVyEQNW;
      string AzWklsydnJ;
      string ygzpJHzkAJ;
      string XMIWpnMhrU;
      string XIpzTkdeaA;
      string IaxGENAsKO;
      string zSQDzmqAtx;
      string fPkSlpqzVX;
      string dUJAAwPCRb;
      string nTWdVEqlAg;
      string tdjcTrodTO;
      string WAXmjeJQDC;
      string XohSJMsHxh;
      string yEzodzjffI;
      string HkhDEmujsq;
      string uaixIFwQTH;
      string zgfkPRBiIk;
      string tckuulGdNV;
      string QIOGmXVBfX;
      string DSMXIZEwnm;
      if(uziUVyEQNW == tdjcTrodTO){lMaIwRonCW = true;}
      else if(tdjcTrodTO == uziUVyEQNW){KmCsJuOUmb = true;}
      if(AzWklsydnJ == WAXmjeJQDC){yRDxqpSZyq = true;}
      else if(WAXmjeJQDC == AzWklsydnJ){mOeeKBuhRl = true;}
      if(ygzpJHzkAJ == XohSJMsHxh){wzDkgaPNlV = true;}
      else if(XohSJMsHxh == ygzpJHzkAJ){dgrPrQfbKD = true;}
      if(XMIWpnMhrU == yEzodzjffI){gJpajDhGJU = true;}
      else if(yEzodzjffI == XMIWpnMhrU){ifZakXynJS = true;}
      if(XIpzTkdeaA == HkhDEmujsq){hgzIZlPPfS = true;}
      else if(HkhDEmujsq == XIpzTkdeaA){npHIJeMAcQ = true;}
      if(IaxGENAsKO == uaixIFwQTH){HeywpmJpaV = true;}
      else if(uaixIFwQTH == IaxGENAsKO){KwBhGculAr = true;}
      if(zSQDzmqAtx == zgfkPRBiIk){CbCfooacMm = true;}
      else if(zgfkPRBiIk == zSQDzmqAtx){PlKirHoEtm = true;}
      if(fPkSlpqzVX == tckuulGdNV){ILPcJOztKu = true;}
      if(dUJAAwPCRb == QIOGmXVBfX){KAgTOCLtjx = true;}
      if(nTWdVEqlAg == DSMXIZEwnm){tqfnSFeSTj = true;}
      while(tckuulGdNV == fPkSlpqzVX){DHYzymZjFM = true;}
      while(QIOGmXVBfX == QIOGmXVBfX){EfysrlerTH = true;}
      while(DSMXIZEwnm == DSMXIZEwnm){cLnQDBfXPC = true;}
      if(lMaIwRonCW == true){lMaIwRonCW = false;}
      if(yRDxqpSZyq == true){yRDxqpSZyq = false;}
      if(wzDkgaPNlV == true){wzDkgaPNlV = false;}
      if(gJpajDhGJU == true){gJpajDhGJU = false;}
      if(hgzIZlPPfS == true){hgzIZlPPfS = false;}
      if(HeywpmJpaV == true){HeywpmJpaV = false;}
      if(CbCfooacMm == true){CbCfooacMm = false;}
      if(ILPcJOztKu == true){ILPcJOztKu = false;}
      if(KAgTOCLtjx == true){KAgTOCLtjx = false;}
      if(tqfnSFeSTj == true){tqfnSFeSTj = false;}
      if(KmCsJuOUmb == true){KmCsJuOUmb = false;}
      if(mOeeKBuhRl == true){mOeeKBuhRl = false;}
      if(dgrPrQfbKD == true){dgrPrQfbKD = false;}
      if(ifZakXynJS == true){ifZakXynJS = false;}
      if(npHIJeMAcQ == true){npHIJeMAcQ = false;}
      if(KwBhGculAr == true){KwBhGculAr = false;}
      if(PlKirHoEtm == true){PlKirHoEtm = false;}
      if(DHYzymZjFM == true){DHYzymZjFM = false;}
      if(EfysrlerTH == true){EfysrlerTH = false;}
      if(cLnQDBfXPC == true){cLnQDBfXPC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CQZPAEMRZA
{ 
  void xaPkmzujiC()
  { 
      bool KHeaFdrqxg = false;
      bool ShWNSUyufL = false;
      bool WsygMliwLx = false;
      bool GtlquNdThp = false;
      bool KzymfQwGnP = false;
      bool iXhktQJxNS = false;
      bool tweAaYueSE = false;
      bool peNoBWtKBw = false;
      bool ocHwNhLBxd = false;
      bool DfGOwNUyLH = false;
      bool VQmiYEJsjW = false;
      bool WywQdRnilr = false;
      bool MthoBKXzsm = false;
      bool CuytaXoYWJ = false;
      bool YSQZGEipkd = false;
      bool YkMTtaiygO = false;
      bool gJzwTazCpF = false;
      bool cPMbTtcIhw = false;
      bool ahOPNRiezz = false;
      bool oqqIcOSTFf = false;
      string PdNHRXTGTm;
      string ptAGLrsSyN;
      string JtEIVMALfy;
      string bcBesoaEUl;
      string iSSuwsihxB;
      string lYshEUYFkF;
      string WHaVKMrVNW;
      string QnxMdpbJLc;
      string cSOdLDjTZY;
      string PUTPOarxjj;
      string BMTZjybgDN;
      string sPtIbDswJH;
      string cYunGwUhxD;
      string ydYbbPyntN;
      string bCPMfAaLmK;
      string humcHbQeTn;
      string ctiAPOpSfM;
      string FECweZJiIF;
      string VIumUDqwTz;
      string zSUGjhTOxR;
      if(PdNHRXTGTm == BMTZjybgDN){KHeaFdrqxg = true;}
      else if(BMTZjybgDN == PdNHRXTGTm){VQmiYEJsjW = true;}
      if(ptAGLrsSyN == sPtIbDswJH){ShWNSUyufL = true;}
      else if(sPtIbDswJH == ptAGLrsSyN){WywQdRnilr = true;}
      if(JtEIVMALfy == cYunGwUhxD){WsygMliwLx = true;}
      else if(cYunGwUhxD == JtEIVMALfy){MthoBKXzsm = true;}
      if(bcBesoaEUl == ydYbbPyntN){GtlquNdThp = true;}
      else if(ydYbbPyntN == bcBesoaEUl){CuytaXoYWJ = true;}
      if(iSSuwsihxB == bCPMfAaLmK){KzymfQwGnP = true;}
      else if(bCPMfAaLmK == iSSuwsihxB){YSQZGEipkd = true;}
      if(lYshEUYFkF == humcHbQeTn){iXhktQJxNS = true;}
      else if(humcHbQeTn == lYshEUYFkF){YkMTtaiygO = true;}
      if(WHaVKMrVNW == ctiAPOpSfM){tweAaYueSE = true;}
      else if(ctiAPOpSfM == WHaVKMrVNW){gJzwTazCpF = true;}
      if(QnxMdpbJLc == FECweZJiIF){peNoBWtKBw = true;}
      if(cSOdLDjTZY == VIumUDqwTz){ocHwNhLBxd = true;}
      if(PUTPOarxjj == zSUGjhTOxR){DfGOwNUyLH = true;}
      while(FECweZJiIF == QnxMdpbJLc){cPMbTtcIhw = true;}
      while(VIumUDqwTz == VIumUDqwTz){ahOPNRiezz = true;}
      while(zSUGjhTOxR == zSUGjhTOxR){oqqIcOSTFf = true;}
      if(KHeaFdrqxg == true){KHeaFdrqxg = false;}
      if(ShWNSUyufL == true){ShWNSUyufL = false;}
      if(WsygMliwLx == true){WsygMliwLx = false;}
      if(GtlquNdThp == true){GtlquNdThp = false;}
      if(KzymfQwGnP == true){KzymfQwGnP = false;}
      if(iXhktQJxNS == true){iXhktQJxNS = false;}
      if(tweAaYueSE == true){tweAaYueSE = false;}
      if(peNoBWtKBw == true){peNoBWtKBw = false;}
      if(ocHwNhLBxd == true){ocHwNhLBxd = false;}
      if(DfGOwNUyLH == true){DfGOwNUyLH = false;}
      if(VQmiYEJsjW == true){VQmiYEJsjW = false;}
      if(WywQdRnilr == true){WywQdRnilr = false;}
      if(MthoBKXzsm == true){MthoBKXzsm = false;}
      if(CuytaXoYWJ == true){CuytaXoYWJ = false;}
      if(YSQZGEipkd == true){YSQZGEipkd = false;}
      if(YkMTtaiygO == true){YkMTtaiygO = false;}
      if(gJzwTazCpF == true){gJzwTazCpF = false;}
      if(cPMbTtcIhw == true){cPMbTtcIhw = false;}
      if(ahOPNRiezz == true){ahOPNRiezz = false;}
      if(oqqIcOSTFf == true){oqqIcOSTFf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JOQUYGEWIU
{ 
  void dKHtUkWWde()
  { 
      bool jKIgSlKrIH = false;
      bool YdOYpgXoty = false;
      bool DVDeIgjaqO = false;
      bool gYMPLKapdX = false;
      bool kYEbMuGuGK = false;
      bool niqeTNHdXl = false;
      bool CjBsaAQyMe = false;
      bool GgKWMdRbRN = false;
      bool anTfZxhhwy = false;
      bool DwSrUAXLAM = false;
      bool dIhaEGYURo = false;
      bool wfLKKOPUSd = false;
      bool RhBObJORBL = false;
      bool GFaFiSFsbT = false;
      bool XMQGCXjIgF = false;
      bool jCrWtwGTyt = false;
      bool qHSFipEGar = false;
      bool IWszFFRuLE = false;
      bool ZGjuaDNDLm = false;
      bool MltgbQtKWM = false;
      string sxzjSLslLY;
      string RnWeGsdYmt;
      string YNDnoPfXTh;
      string BjpNorsHtZ;
      string GfyoMhpZyf;
      string xMStResLtC;
      string eUScXhxJpN;
      string AWdMmrPNaH;
      string ZGZmjoQwwJ;
      string ygMqtlNURd;
      string kgijeahFGY;
      string PfjmbYtesh;
      string QAMgOSJlSB;
      string etwxVsWpIJ;
      string HLpWsSxZPU;
      string qhbiNjTCUL;
      string QulEtVimQi;
      string BEWiaFKonw;
      string VjWxKwRMil;
      string ZUUwrMYkcX;
      if(sxzjSLslLY == kgijeahFGY){jKIgSlKrIH = true;}
      else if(kgijeahFGY == sxzjSLslLY){dIhaEGYURo = true;}
      if(RnWeGsdYmt == PfjmbYtesh){YdOYpgXoty = true;}
      else if(PfjmbYtesh == RnWeGsdYmt){wfLKKOPUSd = true;}
      if(YNDnoPfXTh == QAMgOSJlSB){DVDeIgjaqO = true;}
      else if(QAMgOSJlSB == YNDnoPfXTh){RhBObJORBL = true;}
      if(BjpNorsHtZ == etwxVsWpIJ){gYMPLKapdX = true;}
      else if(etwxVsWpIJ == BjpNorsHtZ){GFaFiSFsbT = true;}
      if(GfyoMhpZyf == HLpWsSxZPU){kYEbMuGuGK = true;}
      else if(HLpWsSxZPU == GfyoMhpZyf){XMQGCXjIgF = true;}
      if(xMStResLtC == qhbiNjTCUL){niqeTNHdXl = true;}
      else if(qhbiNjTCUL == xMStResLtC){jCrWtwGTyt = true;}
      if(eUScXhxJpN == QulEtVimQi){CjBsaAQyMe = true;}
      else if(QulEtVimQi == eUScXhxJpN){qHSFipEGar = true;}
      if(AWdMmrPNaH == BEWiaFKonw){GgKWMdRbRN = true;}
      if(ZGZmjoQwwJ == VjWxKwRMil){anTfZxhhwy = true;}
      if(ygMqtlNURd == ZUUwrMYkcX){DwSrUAXLAM = true;}
      while(BEWiaFKonw == AWdMmrPNaH){IWszFFRuLE = true;}
      while(VjWxKwRMil == VjWxKwRMil){ZGjuaDNDLm = true;}
      while(ZUUwrMYkcX == ZUUwrMYkcX){MltgbQtKWM = true;}
      if(jKIgSlKrIH == true){jKIgSlKrIH = false;}
      if(YdOYpgXoty == true){YdOYpgXoty = false;}
      if(DVDeIgjaqO == true){DVDeIgjaqO = false;}
      if(gYMPLKapdX == true){gYMPLKapdX = false;}
      if(kYEbMuGuGK == true){kYEbMuGuGK = false;}
      if(niqeTNHdXl == true){niqeTNHdXl = false;}
      if(CjBsaAQyMe == true){CjBsaAQyMe = false;}
      if(GgKWMdRbRN == true){GgKWMdRbRN = false;}
      if(anTfZxhhwy == true){anTfZxhhwy = false;}
      if(DwSrUAXLAM == true){DwSrUAXLAM = false;}
      if(dIhaEGYURo == true){dIhaEGYURo = false;}
      if(wfLKKOPUSd == true){wfLKKOPUSd = false;}
      if(RhBObJORBL == true){RhBObJORBL = false;}
      if(GFaFiSFsbT == true){GFaFiSFsbT = false;}
      if(XMQGCXjIgF == true){XMQGCXjIgF = false;}
      if(jCrWtwGTyt == true){jCrWtwGTyt = false;}
      if(qHSFipEGar == true){qHSFipEGar = false;}
      if(IWszFFRuLE == true){IWszFFRuLE = false;}
      if(ZGjuaDNDLm == true){ZGjuaDNDLm = false;}
      if(MltgbQtKWM == true){MltgbQtKWM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PHCOXITVFX
{ 
  void cWtsfeWoum()
  { 
      bool ZjgASuuXue = false;
      bool bnprPswfyJ = false;
      bool xELhzyQdgg = false;
      bool dcZmklVQWl = false;
      bool awnFOShbFO = false;
      bool uwpNqVXzBU = false;
      bool eRpNAzOCHd = false;
      bool XeILiAPGSg = false;
      bool PnXSkglLwP = false;
      bool NWPCHJGZEP = false;
      bool DeUbqPmeep = false;
      bool FRfUEpsXbT = false;
      bool NDGrPAPGDZ = false;
      bool soBDckTuaU = false;
      bool sHgFJwquxQ = false;
      bool PiykBzXcMp = false;
      bool AgaFxPQbqT = false;
      bool WywGZGWBhS = false;
      bool JUJlJKqPBc = false;
      bool MqijUMfaHs = false;
      string uKCYHeRuCW;
      string uSWiWoWOjI;
      string XFSSxacGqw;
      string DlQSuuktlC;
      string CFORCgsmEt;
      string jNiBQoqjbg;
      string BLEGTJBEmb;
      string EccgFSpBPQ;
      string goBxLoCPCF;
      string DASFBqBIys;
      string enzcoGjCux;
      string zpTKzLJGtd;
      string HlChYDKWfO;
      string QhCWkspYHE;
      string EAUEGNgHGo;
      string gtNTlslRDl;
      string wMWffRmxZF;
      string VkzpYGQxbL;
      string VDQphWTikq;
      string GXUVIrcnXn;
      if(uKCYHeRuCW == enzcoGjCux){ZjgASuuXue = true;}
      else if(enzcoGjCux == uKCYHeRuCW){DeUbqPmeep = true;}
      if(uSWiWoWOjI == zpTKzLJGtd){bnprPswfyJ = true;}
      else if(zpTKzLJGtd == uSWiWoWOjI){FRfUEpsXbT = true;}
      if(XFSSxacGqw == HlChYDKWfO){xELhzyQdgg = true;}
      else if(HlChYDKWfO == XFSSxacGqw){NDGrPAPGDZ = true;}
      if(DlQSuuktlC == QhCWkspYHE){dcZmklVQWl = true;}
      else if(QhCWkspYHE == DlQSuuktlC){soBDckTuaU = true;}
      if(CFORCgsmEt == EAUEGNgHGo){awnFOShbFO = true;}
      else if(EAUEGNgHGo == CFORCgsmEt){sHgFJwquxQ = true;}
      if(jNiBQoqjbg == gtNTlslRDl){uwpNqVXzBU = true;}
      else if(gtNTlslRDl == jNiBQoqjbg){PiykBzXcMp = true;}
      if(BLEGTJBEmb == wMWffRmxZF){eRpNAzOCHd = true;}
      else if(wMWffRmxZF == BLEGTJBEmb){AgaFxPQbqT = true;}
      if(EccgFSpBPQ == VkzpYGQxbL){XeILiAPGSg = true;}
      if(goBxLoCPCF == VDQphWTikq){PnXSkglLwP = true;}
      if(DASFBqBIys == GXUVIrcnXn){NWPCHJGZEP = true;}
      while(VkzpYGQxbL == EccgFSpBPQ){WywGZGWBhS = true;}
      while(VDQphWTikq == VDQphWTikq){JUJlJKqPBc = true;}
      while(GXUVIrcnXn == GXUVIrcnXn){MqijUMfaHs = true;}
      if(ZjgASuuXue == true){ZjgASuuXue = false;}
      if(bnprPswfyJ == true){bnprPswfyJ = false;}
      if(xELhzyQdgg == true){xELhzyQdgg = false;}
      if(dcZmklVQWl == true){dcZmklVQWl = false;}
      if(awnFOShbFO == true){awnFOShbFO = false;}
      if(uwpNqVXzBU == true){uwpNqVXzBU = false;}
      if(eRpNAzOCHd == true){eRpNAzOCHd = false;}
      if(XeILiAPGSg == true){XeILiAPGSg = false;}
      if(PnXSkglLwP == true){PnXSkglLwP = false;}
      if(NWPCHJGZEP == true){NWPCHJGZEP = false;}
      if(DeUbqPmeep == true){DeUbqPmeep = false;}
      if(FRfUEpsXbT == true){FRfUEpsXbT = false;}
      if(NDGrPAPGDZ == true){NDGrPAPGDZ = false;}
      if(soBDckTuaU == true){soBDckTuaU = false;}
      if(sHgFJwquxQ == true){sHgFJwquxQ = false;}
      if(PiykBzXcMp == true){PiykBzXcMp = false;}
      if(AgaFxPQbqT == true){AgaFxPQbqT = false;}
      if(WywGZGWBhS == true){WywGZGWBhS = false;}
      if(JUJlJKqPBc == true){JUJlJKqPBc = false;}
      if(MqijUMfaHs == true){MqijUMfaHs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KPWLYGSIEE
{ 
  void fneIjboYJa()
  { 
      bool GssTCtjtEQ = false;
      bool zBHeCNioyf = false;
      bool laRKneLUVK = false;
      bool VNQCieQFBJ = false;
      bool wsYgaFnjGZ = false;
      bool hxVNVfaifX = false;
      bool iOXttlkEuX = false;
      bool wcmnisCkii = false;
      bool paOwbYqDfD = false;
      bool DhZdahVdlo = false;
      bool UinidFKgdc = false;
      bool cpzxgHAbRV = false;
      bool tgYrTNCJNB = false;
      bool XXytNHmfSW = false;
      bool NJYCaNicxS = false;
      bool gsMQtmJwPP = false;
      bool CBTcFErEiY = false;
      bool UTItHkHVQG = false;
      bool eZLtTdLhAZ = false;
      bool xpQDUMpwxV = false;
      string QyjiMrfAjM;
      string fucaFNWIdL;
      string PitEsCeJor;
      string ohmyhdeMne;
      string EoREOwGEzs;
      string VRZkihEeoJ;
      string NVKrXyHesb;
      string hKTyHZQpow;
      string uZJuWWHBOz;
      string ZzWdQhdZfQ;
      string nbLXKLxacI;
      string QNosOnMPVA;
      string pGPsCimogZ;
      string wqJYISNkkL;
      string YgXFhLJdPc;
      string VOEfZhLSVb;
      string XIsDMZEQku;
      string ZadJaJhJKp;
      string YJZEEgmcyZ;
      string HuPJmQmUsI;
      if(QyjiMrfAjM == nbLXKLxacI){GssTCtjtEQ = true;}
      else if(nbLXKLxacI == QyjiMrfAjM){UinidFKgdc = true;}
      if(fucaFNWIdL == QNosOnMPVA){zBHeCNioyf = true;}
      else if(QNosOnMPVA == fucaFNWIdL){cpzxgHAbRV = true;}
      if(PitEsCeJor == pGPsCimogZ){laRKneLUVK = true;}
      else if(pGPsCimogZ == PitEsCeJor){tgYrTNCJNB = true;}
      if(ohmyhdeMne == wqJYISNkkL){VNQCieQFBJ = true;}
      else if(wqJYISNkkL == ohmyhdeMne){XXytNHmfSW = true;}
      if(EoREOwGEzs == YgXFhLJdPc){wsYgaFnjGZ = true;}
      else if(YgXFhLJdPc == EoREOwGEzs){NJYCaNicxS = true;}
      if(VRZkihEeoJ == VOEfZhLSVb){hxVNVfaifX = true;}
      else if(VOEfZhLSVb == VRZkihEeoJ){gsMQtmJwPP = true;}
      if(NVKrXyHesb == XIsDMZEQku){iOXttlkEuX = true;}
      else if(XIsDMZEQku == NVKrXyHesb){CBTcFErEiY = true;}
      if(hKTyHZQpow == ZadJaJhJKp){wcmnisCkii = true;}
      if(uZJuWWHBOz == YJZEEgmcyZ){paOwbYqDfD = true;}
      if(ZzWdQhdZfQ == HuPJmQmUsI){DhZdahVdlo = true;}
      while(ZadJaJhJKp == hKTyHZQpow){UTItHkHVQG = true;}
      while(YJZEEgmcyZ == YJZEEgmcyZ){eZLtTdLhAZ = true;}
      while(HuPJmQmUsI == HuPJmQmUsI){xpQDUMpwxV = true;}
      if(GssTCtjtEQ == true){GssTCtjtEQ = false;}
      if(zBHeCNioyf == true){zBHeCNioyf = false;}
      if(laRKneLUVK == true){laRKneLUVK = false;}
      if(VNQCieQFBJ == true){VNQCieQFBJ = false;}
      if(wsYgaFnjGZ == true){wsYgaFnjGZ = false;}
      if(hxVNVfaifX == true){hxVNVfaifX = false;}
      if(iOXttlkEuX == true){iOXttlkEuX = false;}
      if(wcmnisCkii == true){wcmnisCkii = false;}
      if(paOwbYqDfD == true){paOwbYqDfD = false;}
      if(DhZdahVdlo == true){DhZdahVdlo = false;}
      if(UinidFKgdc == true){UinidFKgdc = false;}
      if(cpzxgHAbRV == true){cpzxgHAbRV = false;}
      if(tgYrTNCJNB == true){tgYrTNCJNB = false;}
      if(XXytNHmfSW == true){XXytNHmfSW = false;}
      if(NJYCaNicxS == true){NJYCaNicxS = false;}
      if(gsMQtmJwPP == true){gsMQtmJwPP = false;}
      if(CBTcFErEiY == true){CBTcFErEiY = false;}
      if(UTItHkHVQG == true){UTItHkHVQG = false;}
      if(eZLtTdLhAZ == true){eZLtTdLhAZ = false;}
      if(xpQDUMpwxV == true){xpQDUMpwxV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AGNIVUKASD
{ 
  void jInVhRIGfZ()
  { 
      bool jzhKEgcGoN = false;
      bool qoCIpLekBn = false;
      bool fGjnxoJzUs = false;
      bool wRehIaOSTz = false;
      bool TDSApOMpOH = false;
      bool SfqOedPsMO = false;
      bool XdluQYKUAP = false;
      bool wMQCUbnjyh = false;
      bool cSkMaQaPCe = false;
      bool LUFEaoRWiQ = false;
      bool ErpzKGOntC = false;
      bool pfuelFrYUA = false;
      bool yuRVEaHMae = false;
      bool KQAhdjblBU = false;
      bool BlVAofZaRU = false;
      bool wrCiRJaUtj = false;
      bool yCMOrYfNAB = false;
      bool cGWAyLYRfY = false;
      bool BgtGhRNQPU = false;
      bool JHqRVzYHHP = false;
      string itItCzwIxC;
      string JYtChljgme;
      string tXPSWyjoQy;
      string sHIPJjbdxk;
      string HDIqPCZjsC;
      string OkrcJKdpXD;
      string OGqzICQdsy;
      string KFjCXqOYCU;
      string XAwOjIOeGy;
      string FkGsVALJhN;
      string luptqIAoFR;
      string wFmDeNKcOA;
      string mkXusYzqfW;
      string fFpohcJBXb;
      string HZZoCzyCNI;
      string pithaBXuBR;
      string IJIhkqPyUC;
      string DIFmrMKhss;
      string awdXgxKINg;
      string EOzFSyQrDK;
      if(itItCzwIxC == luptqIAoFR){jzhKEgcGoN = true;}
      else if(luptqIAoFR == itItCzwIxC){ErpzKGOntC = true;}
      if(JYtChljgme == wFmDeNKcOA){qoCIpLekBn = true;}
      else if(wFmDeNKcOA == JYtChljgme){pfuelFrYUA = true;}
      if(tXPSWyjoQy == mkXusYzqfW){fGjnxoJzUs = true;}
      else if(mkXusYzqfW == tXPSWyjoQy){yuRVEaHMae = true;}
      if(sHIPJjbdxk == fFpohcJBXb){wRehIaOSTz = true;}
      else if(fFpohcJBXb == sHIPJjbdxk){KQAhdjblBU = true;}
      if(HDIqPCZjsC == HZZoCzyCNI){TDSApOMpOH = true;}
      else if(HZZoCzyCNI == HDIqPCZjsC){BlVAofZaRU = true;}
      if(OkrcJKdpXD == pithaBXuBR){SfqOedPsMO = true;}
      else if(pithaBXuBR == OkrcJKdpXD){wrCiRJaUtj = true;}
      if(OGqzICQdsy == IJIhkqPyUC){XdluQYKUAP = true;}
      else if(IJIhkqPyUC == OGqzICQdsy){yCMOrYfNAB = true;}
      if(KFjCXqOYCU == DIFmrMKhss){wMQCUbnjyh = true;}
      if(XAwOjIOeGy == awdXgxKINg){cSkMaQaPCe = true;}
      if(FkGsVALJhN == EOzFSyQrDK){LUFEaoRWiQ = true;}
      while(DIFmrMKhss == KFjCXqOYCU){cGWAyLYRfY = true;}
      while(awdXgxKINg == awdXgxKINg){BgtGhRNQPU = true;}
      while(EOzFSyQrDK == EOzFSyQrDK){JHqRVzYHHP = true;}
      if(jzhKEgcGoN == true){jzhKEgcGoN = false;}
      if(qoCIpLekBn == true){qoCIpLekBn = false;}
      if(fGjnxoJzUs == true){fGjnxoJzUs = false;}
      if(wRehIaOSTz == true){wRehIaOSTz = false;}
      if(TDSApOMpOH == true){TDSApOMpOH = false;}
      if(SfqOedPsMO == true){SfqOedPsMO = false;}
      if(XdluQYKUAP == true){XdluQYKUAP = false;}
      if(wMQCUbnjyh == true){wMQCUbnjyh = false;}
      if(cSkMaQaPCe == true){cSkMaQaPCe = false;}
      if(LUFEaoRWiQ == true){LUFEaoRWiQ = false;}
      if(ErpzKGOntC == true){ErpzKGOntC = false;}
      if(pfuelFrYUA == true){pfuelFrYUA = false;}
      if(yuRVEaHMae == true){yuRVEaHMae = false;}
      if(KQAhdjblBU == true){KQAhdjblBU = false;}
      if(BlVAofZaRU == true){BlVAofZaRU = false;}
      if(wrCiRJaUtj == true){wrCiRJaUtj = false;}
      if(yCMOrYfNAB == true){yCMOrYfNAB = false;}
      if(cGWAyLYRfY == true){cGWAyLYRfY = false;}
      if(BgtGhRNQPU == true){BgtGhRNQPU = false;}
      if(JHqRVzYHHP == true){JHqRVzYHHP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KKHDZREFJN
{ 
  void gDpyLMddal()
  { 
      bool XXPSoZsENL = false;
      bool AMBAZPHtuH = false;
      bool kwhcoawclc = false;
      bool EqkQnglFum = false;
      bool srtzzNdOKE = false;
      bool prVecbomdN = false;
      bool cPSkHIajLs = false;
      bool cByINsCidb = false;
      bool xhRgmLVFnM = false;
      bool qzahJcZIrp = false;
      bool lsCRbntMRj = false;
      bool YGIBPtxkyu = false;
      bool mVwzBcaQyk = false;
      bool SsqmpEeAFy = false;
      bool RJmDmkpZRO = false;
      bool enKwDPwCPy = false;
      bool NcNgQfOVLL = false;
      bool PxezcdhsMQ = false;
      bool mAziFehtiZ = false;
      bool HbkHknuGmG = false;
      string EjxBmrLFel;
      string ObLHgwyxAN;
      string GDxRLOBuLn;
      string SfLkoPCWgG;
      string pdrJsIOcSt;
      string oCEeQBmepY;
      string qQspSiPZRQ;
      string sbPtXcKmXC;
      string zXcQyPagUn;
      string bXfIOYjCqK;
      string roKBBNmJHm;
      string pAGmZTmcqC;
      string HiFcnVuHfy;
      string sHwNJJMbPk;
      string cQZgxbQsiu;
      string lGKnCJjgMe;
      string RfdItiEscP;
      string GLNFZqIXfM;
      string ECYjMlxHKA;
      string ZeOjTxlQmO;
      if(EjxBmrLFel == roKBBNmJHm){XXPSoZsENL = true;}
      else if(roKBBNmJHm == EjxBmrLFel){lsCRbntMRj = true;}
      if(ObLHgwyxAN == pAGmZTmcqC){AMBAZPHtuH = true;}
      else if(pAGmZTmcqC == ObLHgwyxAN){YGIBPtxkyu = true;}
      if(GDxRLOBuLn == HiFcnVuHfy){kwhcoawclc = true;}
      else if(HiFcnVuHfy == GDxRLOBuLn){mVwzBcaQyk = true;}
      if(SfLkoPCWgG == sHwNJJMbPk){EqkQnglFum = true;}
      else if(sHwNJJMbPk == SfLkoPCWgG){SsqmpEeAFy = true;}
      if(pdrJsIOcSt == cQZgxbQsiu){srtzzNdOKE = true;}
      else if(cQZgxbQsiu == pdrJsIOcSt){RJmDmkpZRO = true;}
      if(oCEeQBmepY == lGKnCJjgMe){prVecbomdN = true;}
      else if(lGKnCJjgMe == oCEeQBmepY){enKwDPwCPy = true;}
      if(qQspSiPZRQ == RfdItiEscP){cPSkHIajLs = true;}
      else if(RfdItiEscP == qQspSiPZRQ){NcNgQfOVLL = true;}
      if(sbPtXcKmXC == GLNFZqIXfM){cByINsCidb = true;}
      if(zXcQyPagUn == ECYjMlxHKA){xhRgmLVFnM = true;}
      if(bXfIOYjCqK == ZeOjTxlQmO){qzahJcZIrp = true;}
      while(GLNFZqIXfM == sbPtXcKmXC){PxezcdhsMQ = true;}
      while(ECYjMlxHKA == ECYjMlxHKA){mAziFehtiZ = true;}
      while(ZeOjTxlQmO == ZeOjTxlQmO){HbkHknuGmG = true;}
      if(XXPSoZsENL == true){XXPSoZsENL = false;}
      if(AMBAZPHtuH == true){AMBAZPHtuH = false;}
      if(kwhcoawclc == true){kwhcoawclc = false;}
      if(EqkQnglFum == true){EqkQnglFum = false;}
      if(srtzzNdOKE == true){srtzzNdOKE = false;}
      if(prVecbomdN == true){prVecbomdN = false;}
      if(cPSkHIajLs == true){cPSkHIajLs = false;}
      if(cByINsCidb == true){cByINsCidb = false;}
      if(xhRgmLVFnM == true){xhRgmLVFnM = false;}
      if(qzahJcZIrp == true){qzahJcZIrp = false;}
      if(lsCRbntMRj == true){lsCRbntMRj = false;}
      if(YGIBPtxkyu == true){YGIBPtxkyu = false;}
      if(mVwzBcaQyk == true){mVwzBcaQyk = false;}
      if(SsqmpEeAFy == true){SsqmpEeAFy = false;}
      if(RJmDmkpZRO == true){RJmDmkpZRO = false;}
      if(enKwDPwCPy == true){enKwDPwCPy = false;}
      if(NcNgQfOVLL == true){NcNgQfOVLL = false;}
      if(PxezcdhsMQ == true){PxezcdhsMQ = false;}
      if(mAziFehtiZ == true){mAziFehtiZ = false;}
      if(HbkHknuGmG == true){HbkHknuGmG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPAWBHICGJ
{ 
  void iuxLzONSMf()
  { 
      bool FNXMzQweVN = false;
      bool OOwtTQLUZp = false;
      bool RkzgzBPafy = false;
      bool RFhDSFNKoX = false;
      bool UogNpZAxIr = false;
      bool OYpdCUNqMx = false;
      bool BVyXuJgsbO = false;
      bool CBeBUcEkpY = false;
      bool ASRmjsPDAy = false;
      bool qWxqWzpJSg = false;
      bool sGVspNtnIZ = false;
      bool PcAnwhDLnC = false;
      bool tcscXfDmeV = false;
      bool luSJeswXxW = false;
      bool zauahOVJun = false;
      bool ueVPmQNrVJ = false;
      bool JGJmmUJqIC = false;
      bool kfNRDSgStJ = false;
      bool KtrpZHYCWO = false;
      bool fECmMrRHmN = false;
      string YTHVQRHIJl;
      string GpqfDIgIDM;
      string koDoQXgpdx;
      string otkMSAjtoA;
      string IzfazpXOqS;
      string lZxeLjQSFs;
      string jReLxLFeND;
      string YlTCDlIcoa;
      string zSyKKPxFBh;
      string iRouPqUUcn;
      string jsAmtzGuaZ;
      string ancdtRSTAh;
      string OzcfTHxXlM;
      string RnzBpFSKPL;
      string ICdbHunLBy;
      string XATuZkQUTm;
      string ChIOHloamn;
      string zHDoYLVBXY;
      string SlWnnRTDbF;
      string oxqcIZsPTU;
      if(YTHVQRHIJl == jsAmtzGuaZ){FNXMzQweVN = true;}
      else if(jsAmtzGuaZ == YTHVQRHIJl){sGVspNtnIZ = true;}
      if(GpqfDIgIDM == ancdtRSTAh){OOwtTQLUZp = true;}
      else if(ancdtRSTAh == GpqfDIgIDM){PcAnwhDLnC = true;}
      if(koDoQXgpdx == OzcfTHxXlM){RkzgzBPafy = true;}
      else if(OzcfTHxXlM == koDoQXgpdx){tcscXfDmeV = true;}
      if(otkMSAjtoA == RnzBpFSKPL){RFhDSFNKoX = true;}
      else if(RnzBpFSKPL == otkMSAjtoA){luSJeswXxW = true;}
      if(IzfazpXOqS == ICdbHunLBy){UogNpZAxIr = true;}
      else if(ICdbHunLBy == IzfazpXOqS){zauahOVJun = true;}
      if(lZxeLjQSFs == XATuZkQUTm){OYpdCUNqMx = true;}
      else if(XATuZkQUTm == lZxeLjQSFs){ueVPmQNrVJ = true;}
      if(jReLxLFeND == ChIOHloamn){BVyXuJgsbO = true;}
      else if(ChIOHloamn == jReLxLFeND){JGJmmUJqIC = true;}
      if(YlTCDlIcoa == zHDoYLVBXY){CBeBUcEkpY = true;}
      if(zSyKKPxFBh == SlWnnRTDbF){ASRmjsPDAy = true;}
      if(iRouPqUUcn == oxqcIZsPTU){qWxqWzpJSg = true;}
      while(zHDoYLVBXY == YlTCDlIcoa){kfNRDSgStJ = true;}
      while(SlWnnRTDbF == SlWnnRTDbF){KtrpZHYCWO = true;}
      while(oxqcIZsPTU == oxqcIZsPTU){fECmMrRHmN = true;}
      if(FNXMzQweVN == true){FNXMzQweVN = false;}
      if(OOwtTQLUZp == true){OOwtTQLUZp = false;}
      if(RkzgzBPafy == true){RkzgzBPafy = false;}
      if(RFhDSFNKoX == true){RFhDSFNKoX = false;}
      if(UogNpZAxIr == true){UogNpZAxIr = false;}
      if(OYpdCUNqMx == true){OYpdCUNqMx = false;}
      if(BVyXuJgsbO == true){BVyXuJgsbO = false;}
      if(CBeBUcEkpY == true){CBeBUcEkpY = false;}
      if(ASRmjsPDAy == true){ASRmjsPDAy = false;}
      if(qWxqWzpJSg == true){qWxqWzpJSg = false;}
      if(sGVspNtnIZ == true){sGVspNtnIZ = false;}
      if(PcAnwhDLnC == true){PcAnwhDLnC = false;}
      if(tcscXfDmeV == true){tcscXfDmeV = false;}
      if(luSJeswXxW == true){luSJeswXxW = false;}
      if(zauahOVJun == true){zauahOVJun = false;}
      if(ueVPmQNrVJ == true){ueVPmQNrVJ = false;}
      if(JGJmmUJqIC == true){JGJmmUJqIC = false;}
      if(kfNRDSgStJ == true){kfNRDSgStJ = false;}
      if(KtrpZHYCWO == true){KtrpZHYCWO = false;}
      if(fECmMrRHmN == true){fECmMrRHmN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LMZZSPDEQF
{ 
  void lbnCLdneQI()
  { 
      bool WEGcOOKNpT = false;
      bool YcYXHKhBxf = false;
      bool rIEPUZLrCn = false;
      bool jhgJECkqym = false;
      bool ygUgTgEymt = false;
      bool QoyifOApHo = false;
      bool DRKBipwOSF = false;
      bool ZpCKhKmXun = false;
      bool UMFIXuiydp = false;
      bool CujJifVSxd = false;
      bool koehTZlnAU = false;
      bool abtTUpLBdm = false;
      bool GykcCeGsaC = false;
      bool oTZRCegXox = false;
      bool JuxJOZAQos = false;
      bool TToKWmECeo = false;
      bool TsMyeGCbQo = false;
      bool InMfdLAbNc = false;
      bool dpEhhVePuP = false;
      bool aerzdQizdH = false;
      string cVAyJAfhkr;
      string NPzZlEZDHI;
      string kVDeUihfuD;
      string SfwyUReyAW;
      string EiTsIuZCnF;
      string ljeCyGRVdZ;
      string SzmgYgSAFT;
      string ZbDjECCJVY;
      string JfroRiAsAN;
      string zIUZEEulTa;
      string cYwUfJguyw;
      string DIzFQlGxPp;
      string gYAqTQHdfz;
      string GQotwjiXJH;
      string CFuEKqJPIR;
      string xyVdtDYFAO;
      string CCPzolTEIf;
      string DimHnadwgb;
      string HqUNBItKAs;
      string KcWtEzpwOX;
      if(cVAyJAfhkr == cYwUfJguyw){WEGcOOKNpT = true;}
      else if(cYwUfJguyw == cVAyJAfhkr){koehTZlnAU = true;}
      if(NPzZlEZDHI == DIzFQlGxPp){YcYXHKhBxf = true;}
      else if(DIzFQlGxPp == NPzZlEZDHI){abtTUpLBdm = true;}
      if(kVDeUihfuD == gYAqTQHdfz){rIEPUZLrCn = true;}
      else if(gYAqTQHdfz == kVDeUihfuD){GykcCeGsaC = true;}
      if(SfwyUReyAW == GQotwjiXJH){jhgJECkqym = true;}
      else if(GQotwjiXJH == SfwyUReyAW){oTZRCegXox = true;}
      if(EiTsIuZCnF == CFuEKqJPIR){ygUgTgEymt = true;}
      else if(CFuEKqJPIR == EiTsIuZCnF){JuxJOZAQos = true;}
      if(ljeCyGRVdZ == xyVdtDYFAO){QoyifOApHo = true;}
      else if(xyVdtDYFAO == ljeCyGRVdZ){TToKWmECeo = true;}
      if(SzmgYgSAFT == CCPzolTEIf){DRKBipwOSF = true;}
      else if(CCPzolTEIf == SzmgYgSAFT){TsMyeGCbQo = true;}
      if(ZbDjECCJVY == DimHnadwgb){ZpCKhKmXun = true;}
      if(JfroRiAsAN == HqUNBItKAs){UMFIXuiydp = true;}
      if(zIUZEEulTa == KcWtEzpwOX){CujJifVSxd = true;}
      while(DimHnadwgb == ZbDjECCJVY){InMfdLAbNc = true;}
      while(HqUNBItKAs == HqUNBItKAs){dpEhhVePuP = true;}
      while(KcWtEzpwOX == KcWtEzpwOX){aerzdQizdH = true;}
      if(WEGcOOKNpT == true){WEGcOOKNpT = false;}
      if(YcYXHKhBxf == true){YcYXHKhBxf = false;}
      if(rIEPUZLrCn == true){rIEPUZLrCn = false;}
      if(jhgJECkqym == true){jhgJECkqym = false;}
      if(ygUgTgEymt == true){ygUgTgEymt = false;}
      if(QoyifOApHo == true){QoyifOApHo = false;}
      if(DRKBipwOSF == true){DRKBipwOSF = false;}
      if(ZpCKhKmXun == true){ZpCKhKmXun = false;}
      if(UMFIXuiydp == true){UMFIXuiydp = false;}
      if(CujJifVSxd == true){CujJifVSxd = false;}
      if(koehTZlnAU == true){koehTZlnAU = false;}
      if(abtTUpLBdm == true){abtTUpLBdm = false;}
      if(GykcCeGsaC == true){GykcCeGsaC = false;}
      if(oTZRCegXox == true){oTZRCegXox = false;}
      if(JuxJOZAQos == true){JuxJOZAQos = false;}
      if(TToKWmECeo == true){TToKWmECeo = false;}
      if(TsMyeGCbQo == true){TsMyeGCbQo = false;}
      if(InMfdLAbNc == true){InMfdLAbNc = false;}
      if(dpEhhVePuP == true){dpEhhVePuP = false;}
      if(aerzdQizdH == true){aerzdQizdH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OQTZTFJVEF
{ 
  void iBfVmcMDuF()
  { 
      bool ApcZSgIADm = false;
      bool BXGwzRQMuE = false;
      bool LffoLfqCMA = false;
      bool sJeZwPStwP = false;
      bool fBqLhkphxa = false;
      bool pdBwuUJnOl = false;
      bool oGmDsqsfAj = false;
      bool yWQeYJoTGa = false;
      bool pIEkJOIiea = false;
      bool FefJZYNmRp = false;
      bool rJhNcTNVXk = false;
      bool fogmwgCCse = false;
      bool iJBYdTqHFz = false;
      bool uBCQhfZpIp = false;
      bool BmLsuPxrNs = false;
      bool WLtmHhIJiI = false;
      bool cFPXoemQFP = false;
      bool GMsDcuyHdN = false;
      bool VzsMciGPIA = false;
      bool XQGzMuWmEP = false;
      string UWecSkimRV;
      string IxBgsRnuCo;
      string uWVfTpDtGn;
      string eBXloKUZEm;
      string oouChawfBa;
      string XoyryxAzIb;
      string hofcpGZPrh;
      string wNpOAGaSxs;
      string tWrfQpCfmq;
      string JVQbFAISMa;
      string BgnSdJyjrr;
      string WhBPhKwAMA;
      string DsbBYZwNIA;
      string xIGWqNiYBG;
      string rSmuUbUBtt;
      string DIGLXHEmtE;
      string NjaqtNaeYU;
      string bWzFIkFfgx;
      string FuTOwoCuyi;
      string IwexsHqwBG;
      if(UWecSkimRV == BgnSdJyjrr){ApcZSgIADm = true;}
      else if(BgnSdJyjrr == UWecSkimRV){rJhNcTNVXk = true;}
      if(IxBgsRnuCo == WhBPhKwAMA){BXGwzRQMuE = true;}
      else if(WhBPhKwAMA == IxBgsRnuCo){fogmwgCCse = true;}
      if(uWVfTpDtGn == DsbBYZwNIA){LffoLfqCMA = true;}
      else if(DsbBYZwNIA == uWVfTpDtGn){iJBYdTqHFz = true;}
      if(eBXloKUZEm == xIGWqNiYBG){sJeZwPStwP = true;}
      else if(xIGWqNiYBG == eBXloKUZEm){uBCQhfZpIp = true;}
      if(oouChawfBa == rSmuUbUBtt){fBqLhkphxa = true;}
      else if(rSmuUbUBtt == oouChawfBa){BmLsuPxrNs = true;}
      if(XoyryxAzIb == DIGLXHEmtE){pdBwuUJnOl = true;}
      else if(DIGLXHEmtE == XoyryxAzIb){WLtmHhIJiI = true;}
      if(hofcpGZPrh == NjaqtNaeYU){oGmDsqsfAj = true;}
      else if(NjaqtNaeYU == hofcpGZPrh){cFPXoemQFP = true;}
      if(wNpOAGaSxs == bWzFIkFfgx){yWQeYJoTGa = true;}
      if(tWrfQpCfmq == FuTOwoCuyi){pIEkJOIiea = true;}
      if(JVQbFAISMa == IwexsHqwBG){FefJZYNmRp = true;}
      while(bWzFIkFfgx == wNpOAGaSxs){GMsDcuyHdN = true;}
      while(FuTOwoCuyi == FuTOwoCuyi){VzsMciGPIA = true;}
      while(IwexsHqwBG == IwexsHqwBG){XQGzMuWmEP = true;}
      if(ApcZSgIADm == true){ApcZSgIADm = false;}
      if(BXGwzRQMuE == true){BXGwzRQMuE = false;}
      if(LffoLfqCMA == true){LffoLfqCMA = false;}
      if(sJeZwPStwP == true){sJeZwPStwP = false;}
      if(fBqLhkphxa == true){fBqLhkphxa = false;}
      if(pdBwuUJnOl == true){pdBwuUJnOl = false;}
      if(oGmDsqsfAj == true){oGmDsqsfAj = false;}
      if(yWQeYJoTGa == true){yWQeYJoTGa = false;}
      if(pIEkJOIiea == true){pIEkJOIiea = false;}
      if(FefJZYNmRp == true){FefJZYNmRp = false;}
      if(rJhNcTNVXk == true){rJhNcTNVXk = false;}
      if(fogmwgCCse == true){fogmwgCCse = false;}
      if(iJBYdTqHFz == true){iJBYdTqHFz = false;}
      if(uBCQhfZpIp == true){uBCQhfZpIp = false;}
      if(BmLsuPxrNs == true){BmLsuPxrNs = false;}
      if(WLtmHhIJiI == true){WLtmHhIJiI = false;}
      if(cFPXoemQFP == true){cFPXoemQFP = false;}
      if(GMsDcuyHdN == true){GMsDcuyHdN = false;}
      if(VzsMciGPIA == true){VzsMciGPIA = false;}
      if(XQGzMuWmEP == true){XQGzMuWmEP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WFFWUDLERR
{ 
  void RxuKFYaNwC()
  { 
      bool bTkoZNoEcq = false;
      bool AglpOGSIDS = false;
      bool FwEfYMWRZf = false;
      bool qhXLRqRUPe = false;
      bool luzrMymnwa = false;
      bool xgZBOeOEPM = false;
      bool qWdxzRIaXW = false;
      bool oysXgKxMSa = false;
      bool ZhVziJIWxl = false;
      bool cMEDnOQBru = false;
      bool oLPYkynBUD = false;
      bool hBlolIBeOo = false;
      bool JldltctojS = false;
      bool suTXkNRwOj = false;
      bool VGBsEaZOQe = false;
      bool MlmCkChddI = false;
      bool EzRCKlgODX = false;
      bool pFPdTCjkhT = false;
      bool CeXEFHIRlh = false;
      bool fnRGfWnzhR = false;
      string wzQTVbGoVa;
      string sbbbDiIDbT;
      string BIBNfaiyws;
      string KgORfcJhyi;
      string jZlgHKpTFS;
      string OkrlPnxDmu;
      string sHrbPLNJwa;
      string ZaFriaVUFV;
      string kOsddYobCq;
      string eGuCpcgJQw;
      string xfWesnfACn;
      string RcxRJdOOxp;
      string WkGFuSfCBG;
      string tMDJYEqNkp;
      string soZOZBIcsL;
      string NSMaYLZRiZ;
      string IcywtFZnrE;
      string lAcHxhLres;
      string KCJoraAcjM;
      string eZdLgQpcTT;
      if(wzQTVbGoVa == xfWesnfACn){bTkoZNoEcq = true;}
      else if(xfWesnfACn == wzQTVbGoVa){oLPYkynBUD = true;}
      if(sbbbDiIDbT == RcxRJdOOxp){AglpOGSIDS = true;}
      else if(RcxRJdOOxp == sbbbDiIDbT){hBlolIBeOo = true;}
      if(BIBNfaiyws == WkGFuSfCBG){FwEfYMWRZf = true;}
      else if(WkGFuSfCBG == BIBNfaiyws){JldltctojS = true;}
      if(KgORfcJhyi == tMDJYEqNkp){qhXLRqRUPe = true;}
      else if(tMDJYEqNkp == KgORfcJhyi){suTXkNRwOj = true;}
      if(jZlgHKpTFS == soZOZBIcsL){luzrMymnwa = true;}
      else if(soZOZBIcsL == jZlgHKpTFS){VGBsEaZOQe = true;}
      if(OkrlPnxDmu == NSMaYLZRiZ){xgZBOeOEPM = true;}
      else if(NSMaYLZRiZ == OkrlPnxDmu){MlmCkChddI = true;}
      if(sHrbPLNJwa == IcywtFZnrE){qWdxzRIaXW = true;}
      else if(IcywtFZnrE == sHrbPLNJwa){EzRCKlgODX = true;}
      if(ZaFriaVUFV == lAcHxhLres){oysXgKxMSa = true;}
      if(kOsddYobCq == KCJoraAcjM){ZhVziJIWxl = true;}
      if(eGuCpcgJQw == eZdLgQpcTT){cMEDnOQBru = true;}
      while(lAcHxhLres == ZaFriaVUFV){pFPdTCjkhT = true;}
      while(KCJoraAcjM == KCJoraAcjM){CeXEFHIRlh = true;}
      while(eZdLgQpcTT == eZdLgQpcTT){fnRGfWnzhR = true;}
      if(bTkoZNoEcq == true){bTkoZNoEcq = false;}
      if(AglpOGSIDS == true){AglpOGSIDS = false;}
      if(FwEfYMWRZf == true){FwEfYMWRZf = false;}
      if(qhXLRqRUPe == true){qhXLRqRUPe = false;}
      if(luzrMymnwa == true){luzrMymnwa = false;}
      if(xgZBOeOEPM == true){xgZBOeOEPM = false;}
      if(qWdxzRIaXW == true){qWdxzRIaXW = false;}
      if(oysXgKxMSa == true){oysXgKxMSa = false;}
      if(ZhVziJIWxl == true){ZhVziJIWxl = false;}
      if(cMEDnOQBru == true){cMEDnOQBru = false;}
      if(oLPYkynBUD == true){oLPYkynBUD = false;}
      if(hBlolIBeOo == true){hBlolIBeOo = false;}
      if(JldltctojS == true){JldltctojS = false;}
      if(suTXkNRwOj == true){suTXkNRwOj = false;}
      if(VGBsEaZOQe == true){VGBsEaZOQe = false;}
      if(MlmCkChddI == true){MlmCkChddI = false;}
      if(EzRCKlgODX == true){EzRCKlgODX = false;}
      if(pFPdTCjkhT == true){pFPdTCjkhT = false;}
      if(CeXEFHIRlh == true){CeXEFHIRlh = false;}
      if(fnRGfWnzhR == true){fnRGfWnzhR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SKHHAQRYAX
{ 
  void RRFVhoUcZB()
  { 
      bool pBnGRnyegz = false;
      bool maIEGtSXsD = false;
      bool IdOXeoQXhC = false;
      bool BUEJlQxbJc = false;
      bool LZRbqLTfDM = false;
      bool VZrwpLlPbc = false;
      bool WZwdyRVzRo = false;
      bool xpNPqhLlfT = false;
      bool UjUVgbcISZ = false;
      bool dgAfGlcndZ = false;
      bool oUONPeLcFI = false;
      bool AAjHImFawW = false;
      bool oNgqKPpgJF = false;
      bool EXHGdzUGGC = false;
      bool PADKZdxrXS = false;
      bool fCqHjbnWCz = false;
      bool ndTzDcrcdI = false;
      bool RzUsGnKVRg = false;
      bool RyJpYBfAWC = false;
      bool LyDGOkgDGw = false;
      string SoLcAktEfz;
      string hEsnMUNWAe;
      string PDLWfAqjWD;
      string UdpHQxzRHq;
      string RcbiAKjJqE;
      string GWUdpPcoxA;
      string tKhbdEOkWP;
      string UwOJMlacWU;
      string QgrRxxIMRB;
      string TKTHxGuAEu;
      string wymbiJILQD;
      string nARbiMRPdf;
      string wCSVuKcGLG;
      string paXaYRtQhn;
      string oxuNMSrqXj;
      string ofVXztfRfY;
      string fBzKNNcqDR;
      string RBgpqzGEIb;
      string RkibRKFzbe;
      string lcjJHnxkAz;
      if(SoLcAktEfz == wymbiJILQD){pBnGRnyegz = true;}
      else if(wymbiJILQD == SoLcAktEfz){oUONPeLcFI = true;}
      if(hEsnMUNWAe == nARbiMRPdf){maIEGtSXsD = true;}
      else if(nARbiMRPdf == hEsnMUNWAe){AAjHImFawW = true;}
      if(PDLWfAqjWD == wCSVuKcGLG){IdOXeoQXhC = true;}
      else if(wCSVuKcGLG == PDLWfAqjWD){oNgqKPpgJF = true;}
      if(UdpHQxzRHq == paXaYRtQhn){BUEJlQxbJc = true;}
      else if(paXaYRtQhn == UdpHQxzRHq){EXHGdzUGGC = true;}
      if(RcbiAKjJqE == oxuNMSrqXj){LZRbqLTfDM = true;}
      else if(oxuNMSrqXj == RcbiAKjJqE){PADKZdxrXS = true;}
      if(GWUdpPcoxA == ofVXztfRfY){VZrwpLlPbc = true;}
      else if(ofVXztfRfY == GWUdpPcoxA){fCqHjbnWCz = true;}
      if(tKhbdEOkWP == fBzKNNcqDR){WZwdyRVzRo = true;}
      else if(fBzKNNcqDR == tKhbdEOkWP){ndTzDcrcdI = true;}
      if(UwOJMlacWU == RBgpqzGEIb){xpNPqhLlfT = true;}
      if(QgrRxxIMRB == RkibRKFzbe){UjUVgbcISZ = true;}
      if(TKTHxGuAEu == lcjJHnxkAz){dgAfGlcndZ = true;}
      while(RBgpqzGEIb == UwOJMlacWU){RzUsGnKVRg = true;}
      while(RkibRKFzbe == RkibRKFzbe){RyJpYBfAWC = true;}
      while(lcjJHnxkAz == lcjJHnxkAz){LyDGOkgDGw = true;}
      if(pBnGRnyegz == true){pBnGRnyegz = false;}
      if(maIEGtSXsD == true){maIEGtSXsD = false;}
      if(IdOXeoQXhC == true){IdOXeoQXhC = false;}
      if(BUEJlQxbJc == true){BUEJlQxbJc = false;}
      if(LZRbqLTfDM == true){LZRbqLTfDM = false;}
      if(VZrwpLlPbc == true){VZrwpLlPbc = false;}
      if(WZwdyRVzRo == true){WZwdyRVzRo = false;}
      if(xpNPqhLlfT == true){xpNPqhLlfT = false;}
      if(UjUVgbcISZ == true){UjUVgbcISZ = false;}
      if(dgAfGlcndZ == true){dgAfGlcndZ = false;}
      if(oUONPeLcFI == true){oUONPeLcFI = false;}
      if(AAjHImFawW == true){AAjHImFawW = false;}
      if(oNgqKPpgJF == true){oNgqKPpgJF = false;}
      if(EXHGdzUGGC == true){EXHGdzUGGC = false;}
      if(PADKZdxrXS == true){PADKZdxrXS = false;}
      if(fCqHjbnWCz == true){fCqHjbnWCz = false;}
      if(ndTzDcrcdI == true){ndTzDcrcdI = false;}
      if(RzUsGnKVRg == true){RzUsGnKVRg = false;}
      if(RyJpYBfAWC == true){RyJpYBfAWC = false;}
      if(LyDGOkgDGw == true){LyDGOkgDGw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HPNDNGMEUV
{ 
  void IBlSgmfLpM()
  { 
      bool sjESzjPyom = false;
      bool WxnsynJuKR = false;
      bool UPEfhtKSVH = false;
      bool KxMNejBcMh = false;
      bool jXFrFHltME = false;
      bool NJbQYdeXkF = false;
      bool ZwcgbZjZNN = false;
      bool lfibhwJMaa = false;
      bool HQFRsBUwoA = false;
      bool EdrGImuXPe = false;
      bool XMfyRgZzic = false;
      bool USxKxJpLna = false;
      bool EnkMIInbTt = false;
      bool AlwuDujHzM = false;
      bool aVMLfkfhJz = false;
      bool wjjoZiaSpJ = false;
      bool syfnchVBHC = false;
      bool YiMbziaYgW = false;
      bool bGSUyPBHVT = false;
      bool URRoScoXix = false;
      string sdwdtJFzrm;
      string JFIrskOELc;
      string cSPSsZFALn;
      string phKGmpNoKR;
      string plSYGCoszc;
      string mDhQyaOcjU;
      string EEnDwbtCED;
      string XYstlpzpMq;
      string jLBhBmAtHM;
      string ajFpNlyPce;
      string HmnuFNJndI;
      string bXQrjrDFCI;
      string bAtrcmTDgA;
      string qjNhjxWFcm;
      string dLPzkDSMGU;
      string hrMTCHrwSR;
      string tGHcQqJiIm;
      string UxcOePjuHY;
      string TGwLSzWtec;
      string EamKrXEmhs;
      if(sdwdtJFzrm == HmnuFNJndI){sjESzjPyom = true;}
      else if(HmnuFNJndI == sdwdtJFzrm){XMfyRgZzic = true;}
      if(JFIrskOELc == bXQrjrDFCI){WxnsynJuKR = true;}
      else if(bXQrjrDFCI == JFIrskOELc){USxKxJpLna = true;}
      if(cSPSsZFALn == bAtrcmTDgA){UPEfhtKSVH = true;}
      else if(bAtrcmTDgA == cSPSsZFALn){EnkMIInbTt = true;}
      if(phKGmpNoKR == qjNhjxWFcm){KxMNejBcMh = true;}
      else if(qjNhjxWFcm == phKGmpNoKR){AlwuDujHzM = true;}
      if(plSYGCoszc == dLPzkDSMGU){jXFrFHltME = true;}
      else if(dLPzkDSMGU == plSYGCoszc){aVMLfkfhJz = true;}
      if(mDhQyaOcjU == hrMTCHrwSR){NJbQYdeXkF = true;}
      else if(hrMTCHrwSR == mDhQyaOcjU){wjjoZiaSpJ = true;}
      if(EEnDwbtCED == tGHcQqJiIm){ZwcgbZjZNN = true;}
      else if(tGHcQqJiIm == EEnDwbtCED){syfnchVBHC = true;}
      if(XYstlpzpMq == UxcOePjuHY){lfibhwJMaa = true;}
      if(jLBhBmAtHM == TGwLSzWtec){HQFRsBUwoA = true;}
      if(ajFpNlyPce == EamKrXEmhs){EdrGImuXPe = true;}
      while(UxcOePjuHY == XYstlpzpMq){YiMbziaYgW = true;}
      while(TGwLSzWtec == TGwLSzWtec){bGSUyPBHVT = true;}
      while(EamKrXEmhs == EamKrXEmhs){URRoScoXix = true;}
      if(sjESzjPyom == true){sjESzjPyom = false;}
      if(WxnsynJuKR == true){WxnsynJuKR = false;}
      if(UPEfhtKSVH == true){UPEfhtKSVH = false;}
      if(KxMNejBcMh == true){KxMNejBcMh = false;}
      if(jXFrFHltME == true){jXFrFHltME = false;}
      if(NJbQYdeXkF == true){NJbQYdeXkF = false;}
      if(ZwcgbZjZNN == true){ZwcgbZjZNN = false;}
      if(lfibhwJMaa == true){lfibhwJMaa = false;}
      if(HQFRsBUwoA == true){HQFRsBUwoA = false;}
      if(EdrGImuXPe == true){EdrGImuXPe = false;}
      if(XMfyRgZzic == true){XMfyRgZzic = false;}
      if(USxKxJpLna == true){USxKxJpLna = false;}
      if(EnkMIInbTt == true){EnkMIInbTt = false;}
      if(AlwuDujHzM == true){AlwuDujHzM = false;}
      if(aVMLfkfhJz == true){aVMLfkfhJz = false;}
      if(wjjoZiaSpJ == true){wjjoZiaSpJ = false;}
      if(syfnchVBHC == true){syfnchVBHC = false;}
      if(YiMbziaYgW == true){YiMbziaYgW = false;}
      if(bGSUyPBHVT == true){bGSUyPBHVT = false;}
      if(URRoScoXix == true){URRoScoXix = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RBRHFMSQPK
{ 
  void WmwSBwziuq()
  { 
      bool dKoxgspZQi = false;
      bool SnFsDFDTgJ = false;
      bool ZVkjbBXRzX = false;
      bool phYWoTGwgM = false;
      bool hzDDgMcDfw = false;
      bool qNSkUIYEUf = false;
      bool UYZsskOiDj = false;
      bool zGlUaaShCP = false;
      bool XUlDfcOmBg = false;
      bool tBbBqIYKKw = false;
      bool xtzuxjayKt = false;
      bool pqCFHAmWMQ = false;
      bool VbgWpxekcR = false;
      bool CHXFRcUpFu = false;
      bool BQcHpDzVsq = false;
      bool VBytaVMbFz = false;
      bool FpUrrhTwmd = false;
      bool fwQQOFyZfl = false;
      bool yIqlwAJdew = false;
      bool QrkGpLukOI = false;
      string SMxWAOCJzd;
      string tYigLVzqdk;
      string VmSsMzgOaX;
      string GeIGZIGUMo;
      string csGSHnipEM;
      string zwCOcftEJB;
      string gmhbWOPcGD;
      string PeenIbfzlY;
      string PpKOXKcsdt;
      string OBKLIpLewr;
      string XGjBwURNFA;
      string ztSkkqcSDM;
      string lVyMnNUTfS;
      string QADsBIGIRC;
      string sOndtUiYZR;
      string MrajGBIXMh;
      string AxhmizpYjc;
      string jTBBSWhTRT;
      string dutOFYYTmA;
      string AiwiBugAuu;
      if(SMxWAOCJzd == XGjBwURNFA){dKoxgspZQi = true;}
      else if(XGjBwURNFA == SMxWAOCJzd){xtzuxjayKt = true;}
      if(tYigLVzqdk == ztSkkqcSDM){SnFsDFDTgJ = true;}
      else if(ztSkkqcSDM == tYigLVzqdk){pqCFHAmWMQ = true;}
      if(VmSsMzgOaX == lVyMnNUTfS){ZVkjbBXRzX = true;}
      else if(lVyMnNUTfS == VmSsMzgOaX){VbgWpxekcR = true;}
      if(GeIGZIGUMo == QADsBIGIRC){phYWoTGwgM = true;}
      else if(QADsBIGIRC == GeIGZIGUMo){CHXFRcUpFu = true;}
      if(csGSHnipEM == sOndtUiYZR){hzDDgMcDfw = true;}
      else if(sOndtUiYZR == csGSHnipEM){BQcHpDzVsq = true;}
      if(zwCOcftEJB == MrajGBIXMh){qNSkUIYEUf = true;}
      else if(MrajGBIXMh == zwCOcftEJB){VBytaVMbFz = true;}
      if(gmhbWOPcGD == AxhmizpYjc){UYZsskOiDj = true;}
      else if(AxhmizpYjc == gmhbWOPcGD){FpUrrhTwmd = true;}
      if(PeenIbfzlY == jTBBSWhTRT){zGlUaaShCP = true;}
      if(PpKOXKcsdt == dutOFYYTmA){XUlDfcOmBg = true;}
      if(OBKLIpLewr == AiwiBugAuu){tBbBqIYKKw = true;}
      while(jTBBSWhTRT == PeenIbfzlY){fwQQOFyZfl = true;}
      while(dutOFYYTmA == dutOFYYTmA){yIqlwAJdew = true;}
      while(AiwiBugAuu == AiwiBugAuu){QrkGpLukOI = true;}
      if(dKoxgspZQi == true){dKoxgspZQi = false;}
      if(SnFsDFDTgJ == true){SnFsDFDTgJ = false;}
      if(ZVkjbBXRzX == true){ZVkjbBXRzX = false;}
      if(phYWoTGwgM == true){phYWoTGwgM = false;}
      if(hzDDgMcDfw == true){hzDDgMcDfw = false;}
      if(qNSkUIYEUf == true){qNSkUIYEUf = false;}
      if(UYZsskOiDj == true){UYZsskOiDj = false;}
      if(zGlUaaShCP == true){zGlUaaShCP = false;}
      if(XUlDfcOmBg == true){XUlDfcOmBg = false;}
      if(tBbBqIYKKw == true){tBbBqIYKKw = false;}
      if(xtzuxjayKt == true){xtzuxjayKt = false;}
      if(pqCFHAmWMQ == true){pqCFHAmWMQ = false;}
      if(VbgWpxekcR == true){VbgWpxekcR = false;}
      if(CHXFRcUpFu == true){CHXFRcUpFu = false;}
      if(BQcHpDzVsq == true){BQcHpDzVsq = false;}
      if(VBytaVMbFz == true){VBytaVMbFz = false;}
      if(FpUrrhTwmd == true){FpUrrhTwmd = false;}
      if(fwQQOFyZfl == true){fwQQOFyZfl = false;}
      if(yIqlwAJdew == true){yIqlwAJdew = false;}
      if(QrkGpLukOI == true){QrkGpLukOI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WAHMRGLOCM
{ 
  void SEsqWZNGLL()
  { 
      bool IhGVczlWqG = false;
      bool KPjHqOpDli = false;
      bool gBDafIUUyI = false;
      bool jxTwYlFBnz = false;
      bool WxyJBOesTb = false;
      bool inEuxGeeoU = false;
      bool dQYiWMumhE = false;
      bool IoOlLjCsZR = false;
      bool dbBWYurYzS = false;
      bool HZLTVFXPln = false;
      bool TrKOSsYSiN = false;
      bool DkFXpBPCJa = false;
      bool TVmPxhdtPG = false;
      bool LmHkykQlDf = false;
      bool VZplOVUncT = false;
      bool pVFKTxFuRj = false;
      bool PeCbBPdTYE = false;
      bool kczdFteABa = false;
      bool NoQwQpgwRA = false;
      bool fVUSPqWNky = false;
      string GxLCnRtcal;
      string seESNsDuFD;
      string NWfagMcXZW;
      string KGjxxXEJIm;
      string DUWVIJnlLW;
      string ZEGEJiQkUa;
      string nWDDbmuGUo;
      string otlRArAJSX;
      string YqLCxFAfmO;
      string HTohyfRStU;
      string NgRWgfRnER;
      string iGRwBxLAGV;
      string mPTGhVEDST;
      string ZgOyJqZoVR;
      string nLaVfABrfB;
      string UQMYhyNKnL;
      string aNUjqBrTlK;
      string XVeohanyag;
      string TLXRyIUpPL;
      string dOAKpZqpdd;
      if(GxLCnRtcal == NgRWgfRnER){IhGVczlWqG = true;}
      else if(NgRWgfRnER == GxLCnRtcal){TrKOSsYSiN = true;}
      if(seESNsDuFD == iGRwBxLAGV){KPjHqOpDli = true;}
      else if(iGRwBxLAGV == seESNsDuFD){DkFXpBPCJa = true;}
      if(NWfagMcXZW == mPTGhVEDST){gBDafIUUyI = true;}
      else if(mPTGhVEDST == NWfagMcXZW){TVmPxhdtPG = true;}
      if(KGjxxXEJIm == ZgOyJqZoVR){jxTwYlFBnz = true;}
      else if(ZgOyJqZoVR == KGjxxXEJIm){LmHkykQlDf = true;}
      if(DUWVIJnlLW == nLaVfABrfB){WxyJBOesTb = true;}
      else if(nLaVfABrfB == DUWVIJnlLW){VZplOVUncT = true;}
      if(ZEGEJiQkUa == UQMYhyNKnL){inEuxGeeoU = true;}
      else if(UQMYhyNKnL == ZEGEJiQkUa){pVFKTxFuRj = true;}
      if(nWDDbmuGUo == aNUjqBrTlK){dQYiWMumhE = true;}
      else if(aNUjqBrTlK == nWDDbmuGUo){PeCbBPdTYE = true;}
      if(otlRArAJSX == XVeohanyag){IoOlLjCsZR = true;}
      if(YqLCxFAfmO == TLXRyIUpPL){dbBWYurYzS = true;}
      if(HTohyfRStU == dOAKpZqpdd){HZLTVFXPln = true;}
      while(XVeohanyag == otlRArAJSX){kczdFteABa = true;}
      while(TLXRyIUpPL == TLXRyIUpPL){NoQwQpgwRA = true;}
      while(dOAKpZqpdd == dOAKpZqpdd){fVUSPqWNky = true;}
      if(IhGVczlWqG == true){IhGVczlWqG = false;}
      if(KPjHqOpDli == true){KPjHqOpDli = false;}
      if(gBDafIUUyI == true){gBDafIUUyI = false;}
      if(jxTwYlFBnz == true){jxTwYlFBnz = false;}
      if(WxyJBOesTb == true){WxyJBOesTb = false;}
      if(inEuxGeeoU == true){inEuxGeeoU = false;}
      if(dQYiWMumhE == true){dQYiWMumhE = false;}
      if(IoOlLjCsZR == true){IoOlLjCsZR = false;}
      if(dbBWYurYzS == true){dbBWYurYzS = false;}
      if(HZLTVFXPln == true){HZLTVFXPln = false;}
      if(TrKOSsYSiN == true){TrKOSsYSiN = false;}
      if(DkFXpBPCJa == true){DkFXpBPCJa = false;}
      if(TVmPxhdtPG == true){TVmPxhdtPG = false;}
      if(LmHkykQlDf == true){LmHkykQlDf = false;}
      if(VZplOVUncT == true){VZplOVUncT = false;}
      if(pVFKTxFuRj == true){pVFKTxFuRj = false;}
      if(PeCbBPdTYE == true){PeCbBPdTYE = false;}
      if(kczdFteABa == true){kczdFteABa = false;}
      if(NoQwQpgwRA == true){NoQwQpgwRA = false;}
      if(fVUSPqWNky == true){fVUSPqWNky = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IPFMVJBVIY
{ 
  void ZgTBOEUOnc()
  { 
      bool VXRPumDHcG = false;
      bool lpDOABrfJl = false;
      bool eSPYlHGtSA = false;
      bool OOyYXiWmMk = false;
      bool pRnuBjTCMg = false;
      bool SDAGhCHrdm = false;
      bool gIobqWqdpR = false;
      bool dETYwMeUWB = false;
      bool nEhkhLNqpU = false;
      bool aeJYEgcMDe = false;
      bool roLuDOjbKV = false;
      bool XmVczbaDtf = false;
      bool JAnUpzutTO = false;
      bool iSQrIyrlgT = false;
      bool akgUxnIfZb = false;
      bool GYRWUrBqEE = false;
      bool TpHulFVcUA = false;
      bool jnWaFXSTWC = false;
      bool pOUrHJAtWP = false;
      bool xBhczkdkhr = false;
      string OZTYFBJpJo;
      string SxVQufmyLY;
      string jJVPkfFhnA;
      string mISsJzTdVM;
      string hprIiHaACP;
      string RESHgEDEnY;
      string wbBIBKdcHu;
      string LIcyptRNfc;
      string FEeYhipKLE;
      string wOowQGniHY;
      string dxrGEJbTRl;
      string mpYLTqwcaS;
      string TSQDzxSfgi;
      string FhFGyHMYUY;
      string GVsZRFpdbZ;
      string KLInELgoHH;
      string pumhfEjRMM;
      string eXIBLyYqls;
      string GoDHYtZQBm;
      string aWQNiKiKsM;
      if(OZTYFBJpJo == dxrGEJbTRl){VXRPumDHcG = true;}
      else if(dxrGEJbTRl == OZTYFBJpJo){roLuDOjbKV = true;}
      if(SxVQufmyLY == mpYLTqwcaS){lpDOABrfJl = true;}
      else if(mpYLTqwcaS == SxVQufmyLY){XmVczbaDtf = true;}
      if(jJVPkfFhnA == TSQDzxSfgi){eSPYlHGtSA = true;}
      else if(TSQDzxSfgi == jJVPkfFhnA){JAnUpzutTO = true;}
      if(mISsJzTdVM == FhFGyHMYUY){OOyYXiWmMk = true;}
      else if(FhFGyHMYUY == mISsJzTdVM){iSQrIyrlgT = true;}
      if(hprIiHaACP == GVsZRFpdbZ){pRnuBjTCMg = true;}
      else if(GVsZRFpdbZ == hprIiHaACP){akgUxnIfZb = true;}
      if(RESHgEDEnY == KLInELgoHH){SDAGhCHrdm = true;}
      else if(KLInELgoHH == RESHgEDEnY){GYRWUrBqEE = true;}
      if(wbBIBKdcHu == pumhfEjRMM){gIobqWqdpR = true;}
      else if(pumhfEjRMM == wbBIBKdcHu){TpHulFVcUA = true;}
      if(LIcyptRNfc == eXIBLyYqls){dETYwMeUWB = true;}
      if(FEeYhipKLE == GoDHYtZQBm){nEhkhLNqpU = true;}
      if(wOowQGniHY == aWQNiKiKsM){aeJYEgcMDe = true;}
      while(eXIBLyYqls == LIcyptRNfc){jnWaFXSTWC = true;}
      while(GoDHYtZQBm == GoDHYtZQBm){pOUrHJAtWP = true;}
      while(aWQNiKiKsM == aWQNiKiKsM){xBhczkdkhr = true;}
      if(VXRPumDHcG == true){VXRPumDHcG = false;}
      if(lpDOABrfJl == true){lpDOABrfJl = false;}
      if(eSPYlHGtSA == true){eSPYlHGtSA = false;}
      if(OOyYXiWmMk == true){OOyYXiWmMk = false;}
      if(pRnuBjTCMg == true){pRnuBjTCMg = false;}
      if(SDAGhCHrdm == true){SDAGhCHrdm = false;}
      if(gIobqWqdpR == true){gIobqWqdpR = false;}
      if(dETYwMeUWB == true){dETYwMeUWB = false;}
      if(nEhkhLNqpU == true){nEhkhLNqpU = false;}
      if(aeJYEgcMDe == true){aeJYEgcMDe = false;}
      if(roLuDOjbKV == true){roLuDOjbKV = false;}
      if(XmVczbaDtf == true){XmVczbaDtf = false;}
      if(JAnUpzutTO == true){JAnUpzutTO = false;}
      if(iSQrIyrlgT == true){iSQrIyrlgT = false;}
      if(akgUxnIfZb == true){akgUxnIfZb = false;}
      if(GYRWUrBqEE == true){GYRWUrBqEE = false;}
      if(TpHulFVcUA == true){TpHulFVcUA = false;}
      if(jnWaFXSTWC == true){jnWaFXSTWC = false;}
      if(pOUrHJAtWP == true){pOUrHJAtWP = false;}
      if(xBhczkdkhr == true){xBhczkdkhr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RMABUDXMWD
{ 
  void IOHRTwPAAx()
  { 
      bool xadFEBaNxR = false;
      bool uEGEDiCUlU = false;
      bool VeZcaMKIiC = false;
      bool rOVGbxsbVl = false;
      bool ROLCIMTIWq = false;
      bool ucArISBAer = false;
      bool pSeuZgizbF = false;
      bool oZyzCHTWUN = false;
      bool rClqGOOdyJ = false;
      bool wrxcwziQbb = false;
      bool dTgRCUdAoA = false;
      bool zdfQzngnnK = false;
      bool REBRIxcVDD = false;
      bool YDtsjYUTnk = false;
      bool kOoxKRMgcH = false;
      bool StbRJYSOIF = false;
      bool rHwkbuilfa = false;
      bool SMzCYDPDHp = false;
      bool kurwkdaciL = false;
      bool GFLisdSDVO = false;
      string AeUaMoIqAY;
      string JBRbAKPaen;
      string DnzkhJPMgn;
      string qZoLmJZmzT;
      string kFZNWWFseH;
      string RrWoQLeisC;
      string ZwKMhiMFnp;
      string kcbLCyNlNK;
      string EVgYVyDzta;
      string epswtouNfm;
      string JzEoWoQLmS;
      string ysUhyDPkpi;
      string fNLNLtifQN;
      string DzFaAFQqCg;
      string hqLbckULyq;
      string ZJWxGwnqdb;
      string GjtZOymtgr;
      string lXhJAoBikZ;
      string YXhZmsbITD;
      string RZMZayxlNd;
      if(AeUaMoIqAY == JzEoWoQLmS){xadFEBaNxR = true;}
      else if(JzEoWoQLmS == AeUaMoIqAY){dTgRCUdAoA = true;}
      if(JBRbAKPaen == ysUhyDPkpi){uEGEDiCUlU = true;}
      else if(ysUhyDPkpi == JBRbAKPaen){zdfQzngnnK = true;}
      if(DnzkhJPMgn == fNLNLtifQN){VeZcaMKIiC = true;}
      else if(fNLNLtifQN == DnzkhJPMgn){REBRIxcVDD = true;}
      if(qZoLmJZmzT == DzFaAFQqCg){rOVGbxsbVl = true;}
      else if(DzFaAFQqCg == qZoLmJZmzT){YDtsjYUTnk = true;}
      if(kFZNWWFseH == hqLbckULyq){ROLCIMTIWq = true;}
      else if(hqLbckULyq == kFZNWWFseH){kOoxKRMgcH = true;}
      if(RrWoQLeisC == ZJWxGwnqdb){ucArISBAer = true;}
      else if(ZJWxGwnqdb == RrWoQLeisC){StbRJYSOIF = true;}
      if(ZwKMhiMFnp == GjtZOymtgr){pSeuZgizbF = true;}
      else if(GjtZOymtgr == ZwKMhiMFnp){rHwkbuilfa = true;}
      if(kcbLCyNlNK == lXhJAoBikZ){oZyzCHTWUN = true;}
      if(EVgYVyDzta == YXhZmsbITD){rClqGOOdyJ = true;}
      if(epswtouNfm == RZMZayxlNd){wrxcwziQbb = true;}
      while(lXhJAoBikZ == kcbLCyNlNK){SMzCYDPDHp = true;}
      while(YXhZmsbITD == YXhZmsbITD){kurwkdaciL = true;}
      while(RZMZayxlNd == RZMZayxlNd){GFLisdSDVO = true;}
      if(xadFEBaNxR == true){xadFEBaNxR = false;}
      if(uEGEDiCUlU == true){uEGEDiCUlU = false;}
      if(VeZcaMKIiC == true){VeZcaMKIiC = false;}
      if(rOVGbxsbVl == true){rOVGbxsbVl = false;}
      if(ROLCIMTIWq == true){ROLCIMTIWq = false;}
      if(ucArISBAer == true){ucArISBAer = false;}
      if(pSeuZgizbF == true){pSeuZgizbF = false;}
      if(oZyzCHTWUN == true){oZyzCHTWUN = false;}
      if(rClqGOOdyJ == true){rClqGOOdyJ = false;}
      if(wrxcwziQbb == true){wrxcwziQbb = false;}
      if(dTgRCUdAoA == true){dTgRCUdAoA = false;}
      if(zdfQzngnnK == true){zdfQzngnnK = false;}
      if(REBRIxcVDD == true){REBRIxcVDD = false;}
      if(YDtsjYUTnk == true){YDtsjYUTnk = false;}
      if(kOoxKRMgcH == true){kOoxKRMgcH = false;}
      if(StbRJYSOIF == true){StbRJYSOIF = false;}
      if(rHwkbuilfa == true){rHwkbuilfa = false;}
      if(SMzCYDPDHp == true){SMzCYDPDHp = false;}
      if(kurwkdaciL == true){kurwkdaciL = false;}
      if(GFLisdSDVO == true){GFLisdSDVO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFFVFRPYLX
{ 
  void ZcUiETAXAu()
  { 
      bool QDidOxUOUs = false;
      bool DeYafqMcZS = false;
      bool lDZlyWIGwL = false;
      bool GhOgIHfAPe = false;
      bool nWpOcpbkoX = false;
      bool PQDLUMdweq = false;
      bool oORJlVPrRY = false;
      bool KMNtePNLJI = false;
      bool uXRYupeDLu = false;
      bool ciUXpZEfbH = false;
      bool ZjSPMDDIfF = false;
      bool zRmVwRwsNu = false;
      bool qLfWubqoEE = false;
      bool KgiBhLEBMr = false;
      bool mVWGuKuzbX = false;
      bool cLSfQODuTj = false;
      bool LNEbtRilnj = false;
      bool MtgUIUnZaj = false;
      bool frMfazOCkT = false;
      bool IJhbfYRuLd = false;
      string HKBuOlwzec;
      string WsSAGPPVtr;
      string cEqWekGxHC;
      string krWYSjzglD;
      string ygjHZcSNdF;
      string HAQrgDTePd;
      string ezrcqdWshW;
      string QhipswTjwB;
      string RsSCujberO;
      string PTQIYynHPu;
      string GYfGnYRZyk;
      string jihNLkfpgG;
      string CrBSGwRaRu;
      string HLTAurNMNV;
      string SBfHefkCwm;
      string RyZIsOXMAq;
      string GpHDcXPgSS;
      string XTcLmALsnZ;
      string LPdecJkLHf;
      string UALVObscdH;
      if(HKBuOlwzec == GYfGnYRZyk){QDidOxUOUs = true;}
      else if(GYfGnYRZyk == HKBuOlwzec){ZjSPMDDIfF = true;}
      if(WsSAGPPVtr == jihNLkfpgG){DeYafqMcZS = true;}
      else if(jihNLkfpgG == WsSAGPPVtr){zRmVwRwsNu = true;}
      if(cEqWekGxHC == CrBSGwRaRu){lDZlyWIGwL = true;}
      else if(CrBSGwRaRu == cEqWekGxHC){qLfWubqoEE = true;}
      if(krWYSjzglD == HLTAurNMNV){GhOgIHfAPe = true;}
      else if(HLTAurNMNV == krWYSjzglD){KgiBhLEBMr = true;}
      if(ygjHZcSNdF == SBfHefkCwm){nWpOcpbkoX = true;}
      else if(SBfHefkCwm == ygjHZcSNdF){mVWGuKuzbX = true;}
      if(HAQrgDTePd == RyZIsOXMAq){PQDLUMdweq = true;}
      else if(RyZIsOXMAq == HAQrgDTePd){cLSfQODuTj = true;}
      if(ezrcqdWshW == GpHDcXPgSS){oORJlVPrRY = true;}
      else if(GpHDcXPgSS == ezrcqdWshW){LNEbtRilnj = true;}
      if(QhipswTjwB == XTcLmALsnZ){KMNtePNLJI = true;}
      if(RsSCujberO == LPdecJkLHf){uXRYupeDLu = true;}
      if(PTQIYynHPu == UALVObscdH){ciUXpZEfbH = true;}
      while(XTcLmALsnZ == QhipswTjwB){MtgUIUnZaj = true;}
      while(LPdecJkLHf == LPdecJkLHf){frMfazOCkT = true;}
      while(UALVObscdH == UALVObscdH){IJhbfYRuLd = true;}
      if(QDidOxUOUs == true){QDidOxUOUs = false;}
      if(DeYafqMcZS == true){DeYafqMcZS = false;}
      if(lDZlyWIGwL == true){lDZlyWIGwL = false;}
      if(GhOgIHfAPe == true){GhOgIHfAPe = false;}
      if(nWpOcpbkoX == true){nWpOcpbkoX = false;}
      if(PQDLUMdweq == true){PQDLUMdweq = false;}
      if(oORJlVPrRY == true){oORJlVPrRY = false;}
      if(KMNtePNLJI == true){KMNtePNLJI = false;}
      if(uXRYupeDLu == true){uXRYupeDLu = false;}
      if(ciUXpZEfbH == true){ciUXpZEfbH = false;}
      if(ZjSPMDDIfF == true){ZjSPMDDIfF = false;}
      if(zRmVwRwsNu == true){zRmVwRwsNu = false;}
      if(qLfWubqoEE == true){qLfWubqoEE = false;}
      if(KgiBhLEBMr == true){KgiBhLEBMr = false;}
      if(mVWGuKuzbX == true){mVWGuKuzbX = false;}
      if(cLSfQODuTj == true){cLSfQODuTj = false;}
      if(LNEbtRilnj == true){LNEbtRilnj = false;}
      if(MtgUIUnZaj == true){MtgUIUnZaj = false;}
      if(frMfazOCkT == true){frMfazOCkT = false;}
      if(IJhbfYRuLd == true){IJhbfYRuLd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMOXRXIEZT
{ 
  void BEqzIANRIb()
  { 
      bool VwkmGCpBNR = false;
      bool GLmtTdChgU = false;
      bool yKboTjqoCE = false;
      bool dubDlwBxbP = false;
      bool OUkZeBCVCK = false;
      bool ezpuIKTwTV = false;
      bool KAyInKjjHX = false;
      bool bFFQFdZCKS = false;
      bool hVlrZdFfua = false;
      bool cFdGFOVbkT = false;
      bool RRNehZtZod = false;
      bool kRlAmoNGiK = false;
      bool FDofuWazLq = false;
      bool IxQpAPIHJA = false;
      bool ifqQpKTcSP = false;
      bool BOrZNOcgjL = false;
      bool ytNyVmAuzW = false;
      bool fGxiaZMXpj = false;
      bool CygupsEqcl = false;
      bool maWyBoRruC = false;
      string TPuHEFzzEN;
      string ThYPlaNAxV;
      string MXurpAQVui;
      string manPLJJQYk;
      string KENkgLuoQn;
      string NVtmqwUCRE;
      string ocEUarsIDb;
      string RxaMKIJKLe;
      string EaFHVRgBYP;
      string oHyUwhAsKo;
      string SmlnWPuhch;
      string lJqmzOXxyJ;
      string KqinmJyGQc;
      string IQAVMRnQjG;
      string VzXpceQLUg;
      string JCtAdaEyBM;
      string QnQAZVJUah;
      string ZGMrmLTrKH;
      string rmkiSFWzrk;
      string NoPWohhXQH;
      if(TPuHEFzzEN == SmlnWPuhch){VwkmGCpBNR = true;}
      else if(SmlnWPuhch == TPuHEFzzEN){RRNehZtZod = true;}
      if(ThYPlaNAxV == lJqmzOXxyJ){GLmtTdChgU = true;}
      else if(lJqmzOXxyJ == ThYPlaNAxV){kRlAmoNGiK = true;}
      if(MXurpAQVui == KqinmJyGQc){yKboTjqoCE = true;}
      else if(KqinmJyGQc == MXurpAQVui){FDofuWazLq = true;}
      if(manPLJJQYk == IQAVMRnQjG){dubDlwBxbP = true;}
      else if(IQAVMRnQjG == manPLJJQYk){IxQpAPIHJA = true;}
      if(KENkgLuoQn == VzXpceQLUg){OUkZeBCVCK = true;}
      else if(VzXpceQLUg == KENkgLuoQn){ifqQpKTcSP = true;}
      if(NVtmqwUCRE == JCtAdaEyBM){ezpuIKTwTV = true;}
      else if(JCtAdaEyBM == NVtmqwUCRE){BOrZNOcgjL = true;}
      if(ocEUarsIDb == QnQAZVJUah){KAyInKjjHX = true;}
      else if(QnQAZVJUah == ocEUarsIDb){ytNyVmAuzW = true;}
      if(RxaMKIJKLe == ZGMrmLTrKH){bFFQFdZCKS = true;}
      if(EaFHVRgBYP == rmkiSFWzrk){hVlrZdFfua = true;}
      if(oHyUwhAsKo == NoPWohhXQH){cFdGFOVbkT = true;}
      while(ZGMrmLTrKH == RxaMKIJKLe){fGxiaZMXpj = true;}
      while(rmkiSFWzrk == rmkiSFWzrk){CygupsEqcl = true;}
      while(NoPWohhXQH == NoPWohhXQH){maWyBoRruC = true;}
      if(VwkmGCpBNR == true){VwkmGCpBNR = false;}
      if(GLmtTdChgU == true){GLmtTdChgU = false;}
      if(yKboTjqoCE == true){yKboTjqoCE = false;}
      if(dubDlwBxbP == true){dubDlwBxbP = false;}
      if(OUkZeBCVCK == true){OUkZeBCVCK = false;}
      if(ezpuIKTwTV == true){ezpuIKTwTV = false;}
      if(KAyInKjjHX == true){KAyInKjjHX = false;}
      if(bFFQFdZCKS == true){bFFQFdZCKS = false;}
      if(hVlrZdFfua == true){hVlrZdFfua = false;}
      if(cFdGFOVbkT == true){cFdGFOVbkT = false;}
      if(RRNehZtZod == true){RRNehZtZod = false;}
      if(kRlAmoNGiK == true){kRlAmoNGiK = false;}
      if(FDofuWazLq == true){FDofuWazLq = false;}
      if(IxQpAPIHJA == true){IxQpAPIHJA = false;}
      if(ifqQpKTcSP == true){ifqQpKTcSP = false;}
      if(BOrZNOcgjL == true){BOrZNOcgjL = false;}
      if(ytNyVmAuzW == true){ytNyVmAuzW = false;}
      if(fGxiaZMXpj == true){fGxiaZMXpj = false;}
      if(CygupsEqcl == true){CygupsEqcl = false;}
      if(maWyBoRruC == true){maWyBoRruC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YFJPDXNAUF
{ 
  void iqxLCrLtrD()
  { 
      bool iHXRBPfOCc = false;
      bool ucufIRPaqR = false;
      bool pSpRyWgEMs = false;
      bool FGtpeUibhy = false;
      bool BknFlVUwts = false;
      bool UOeiyPQFSe = false;
      bool iaBJXohEBm = false;
      bool hmssQEdkfc = false;
      bool BjKTYqaKrO = false;
      bool DcICPZiegx = false;
      bool mQuGKgUlSs = false;
      bool leZpdyQhjg = false;
      bool NXLmjFdqdq = false;
      bool UzEhpkoEIq = false;
      bool VorzbYCSYQ = false;
      bool IBtAiPEIWF = false;
      bool DdHaXmarAr = false;
      bool JMZsKYfMKK = false;
      bool CKSNiTEEza = false;
      bool gfgCnrhQao = false;
      string gUafuXzXnM;
      string lZLiIjdoIs;
      string OVOWohWzuu;
      string aHAsSdPVwS;
      string DKmoxDoydN;
      string JMYgXLFEqN;
      string BAbrldYSPe;
      string UHsooDhZYk;
      string sYUgkNiTUH;
      string YLdiRDhtDS;
      string dVhzsCTiqT;
      string cfeGTceuHX;
      string uFxIFIdJXl;
      string UmWGGWpVmi;
      string tAbBdrfXOn;
      string YmmfXYYZsk;
      string XJKFzpJYzx;
      string lIHXctcweN;
      string bGtiNgAphh;
      string yPbCKjoWBn;
      if(gUafuXzXnM == dVhzsCTiqT){iHXRBPfOCc = true;}
      else if(dVhzsCTiqT == gUafuXzXnM){mQuGKgUlSs = true;}
      if(lZLiIjdoIs == cfeGTceuHX){ucufIRPaqR = true;}
      else if(cfeGTceuHX == lZLiIjdoIs){leZpdyQhjg = true;}
      if(OVOWohWzuu == uFxIFIdJXl){pSpRyWgEMs = true;}
      else if(uFxIFIdJXl == OVOWohWzuu){NXLmjFdqdq = true;}
      if(aHAsSdPVwS == UmWGGWpVmi){FGtpeUibhy = true;}
      else if(UmWGGWpVmi == aHAsSdPVwS){UzEhpkoEIq = true;}
      if(DKmoxDoydN == tAbBdrfXOn){BknFlVUwts = true;}
      else if(tAbBdrfXOn == DKmoxDoydN){VorzbYCSYQ = true;}
      if(JMYgXLFEqN == YmmfXYYZsk){UOeiyPQFSe = true;}
      else if(YmmfXYYZsk == JMYgXLFEqN){IBtAiPEIWF = true;}
      if(BAbrldYSPe == XJKFzpJYzx){iaBJXohEBm = true;}
      else if(XJKFzpJYzx == BAbrldYSPe){DdHaXmarAr = true;}
      if(UHsooDhZYk == lIHXctcweN){hmssQEdkfc = true;}
      if(sYUgkNiTUH == bGtiNgAphh){BjKTYqaKrO = true;}
      if(YLdiRDhtDS == yPbCKjoWBn){DcICPZiegx = true;}
      while(lIHXctcweN == UHsooDhZYk){JMZsKYfMKK = true;}
      while(bGtiNgAphh == bGtiNgAphh){CKSNiTEEza = true;}
      while(yPbCKjoWBn == yPbCKjoWBn){gfgCnrhQao = true;}
      if(iHXRBPfOCc == true){iHXRBPfOCc = false;}
      if(ucufIRPaqR == true){ucufIRPaqR = false;}
      if(pSpRyWgEMs == true){pSpRyWgEMs = false;}
      if(FGtpeUibhy == true){FGtpeUibhy = false;}
      if(BknFlVUwts == true){BknFlVUwts = false;}
      if(UOeiyPQFSe == true){UOeiyPQFSe = false;}
      if(iaBJXohEBm == true){iaBJXohEBm = false;}
      if(hmssQEdkfc == true){hmssQEdkfc = false;}
      if(BjKTYqaKrO == true){BjKTYqaKrO = false;}
      if(DcICPZiegx == true){DcICPZiegx = false;}
      if(mQuGKgUlSs == true){mQuGKgUlSs = false;}
      if(leZpdyQhjg == true){leZpdyQhjg = false;}
      if(NXLmjFdqdq == true){NXLmjFdqdq = false;}
      if(UzEhpkoEIq == true){UzEhpkoEIq = false;}
      if(VorzbYCSYQ == true){VorzbYCSYQ = false;}
      if(IBtAiPEIWF == true){IBtAiPEIWF = false;}
      if(DdHaXmarAr == true){DdHaXmarAr = false;}
      if(JMZsKYfMKK == true){JMZsKYfMKK = false;}
      if(CKSNiTEEza == true){CKSNiTEEza = false;}
      if(gfgCnrhQao == true){gfgCnrhQao = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KPHILZIQGO
{ 
  void SoCcBWunGG()
  { 
      bool KYGepCFanb = false;
      bool EqbmxGBDaT = false;
      bool DTAXjCIIlS = false;
      bool QlcKiUiwNB = false;
      bool wNakWcNgcC = false;
      bool XtHsLqYiun = false;
      bool swoVLRNQDb = false;
      bool XFpZXosPBG = false;
      bool nbfiuVeizr = false;
      bool wABYHzYFZE = false;
      bool OwcAeREhVV = false;
      bool yIhnARQFao = false;
      bool leRKeXEQRY = false;
      bool QmpwqryfEc = false;
      bool RwNctnRMYp = false;
      bool iSejSjdSUH = false;
      bool NmQwFKSlxH = false;
      bool SjAxWoQoPq = false;
      bool FqrbpyIFdH = false;
      bool OfLxOdfQXj = false;
      string GieuGUMssN;
      string aDMzpSNFlG;
      string ROhykoHJAq;
      string cDnpEaiOGf;
      string MjbLiZeekI;
      string qmBJsrBfKQ;
      string MCsBjWOWtO;
      string jzzGtglWPL;
      string KcXqzpCdwM;
      string ZCDoSJqZaL;
      string KIjWYrmuPM;
      string FeQzGjdBCt;
      string UjZhoguKmj;
      string pMuDACrBSG;
      string CGOiHtlEii;
      string eoWfpZhChr;
      string xcIfVriNyE;
      string rciurOVpZt;
      string tpaEEBoPMa;
      string TpTZJYyiNO;
      if(GieuGUMssN == KIjWYrmuPM){KYGepCFanb = true;}
      else if(KIjWYrmuPM == GieuGUMssN){OwcAeREhVV = true;}
      if(aDMzpSNFlG == FeQzGjdBCt){EqbmxGBDaT = true;}
      else if(FeQzGjdBCt == aDMzpSNFlG){yIhnARQFao = true;}
      if(ROhykoHJAq == UjZhoguKmj){DTAXjCIIlS = true;}
      else if(UjZhoguKmj == ROhykoHJAq){leRKeXEQRY = true;}
      if(cDnpEaiOGf == pMuDACrBSG){QlcKiUiwNB = true;}
      else if(pMuDACrBSG == cDnpEaiOGf){QmpwqryfEc = true;}
      if(MjbLiZeekI == CGOiHtlEii){wNakWcNgcC = true;}
      else if(CGOiHtlEii == MjbLiZeekI){RwNctnRMYp = true;}
      if(qmBJsrBfKQ == eoWfpZhChr){XtHsLqYiun = true;}
      else if(eoWfpZhChr == qmBJsrBfKQ){iSejSjdSUH = true;}
      if(MCsBjWOWtO == xcIfVriNyE){swoVLRNQDb = true;}
      else if(xcIfVriNyE == MCsBjWOWtO){NmQwFKSlxH = true;}
      if(jzzGtglWPL == rciurOVpZt){XFpZXosPBG = true;}
      if(KcXqzpCdwM == tpaEEBoPMa){nbfiuVeizr = true;}
      if(ZCDoSJqZaL == TpTZJYyiNO){wABYHzYFZE = true;}
      while(rciurOVpZt == jzzGtglWPL){SjAxWoQoPq = true;}
      while(tpaEEBoPMa == tpaEEBoPMa){FqrbpyIFdH = true;}
      while(TpTZJYyiNO == TpTZJYyiNO){OfLxOdfQXj = true;}
      if(KYGepCFanb == true){KYGepCFanb = false;}
      if(EqbmxGBDaT == true){EqbmxGBDaT = false;}
      if(DTAXjCIIlS == true){DTAXjCIIlS = false;}
      if(QlcKiUiwNB == true){QlcKiUiwNB = false;}
      if(wNakWcNgcC == true){wNakWcNgcC = false;}
      if(XtHsLqYiun == true){XtHsLqYiun = false;}
      if(swoVLRNQDb == true){swoVLRNQDb = false;}
      if(XFpZXosPBG == true){XFpZXosPBG = false;}
      if(nbfiuVeizr == true){nbfiuVeizr = false;}
      if(wABYHzYFZE == true){wABYHzYFZE = false;}
      if(OwcAeREhVV == true){OwcAeREhVV = false;}
      if(yIhnARQFao == true){yIhnARQFao = false;}
      if(leRKeXEQRY == true){leRKeXEQRY = false;}
      if(QmpwqryfEc == true){QmpwqryfEc = false;}
      if(RwNctnRMYp == true){RwNctnRMYp = false;}
      if(iSejSjdSUH == true){iSejSjdSUH = false;}
      if(NmQwFKSlxH == true){NmQwFKSlxH = false;}
      if(SjAxWoQoPq == true){SjAxWoQoPq = false;}
      if(FqrbpyIFdH == true){FqrbpyIFdH = false;}
      if(OfLxOdfQXj == true){OfLxOdfQXj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCXSBNXLDF
{ 
  void QwbnySBitZ()
  { 
      bool IbzuBnuJhJ = false;
      bool BCyiIzyUgl = false;
      bool SEghYIalXd = false;
      bool WSUkxBjUzj = false;
      bool BcKXCEePea = false;
      bool KLLVLDuRVs = false;
      bool MIlElhhMlH = false;
      bool OdVxjptIfU = false;
      bool dLHwSLHyZs = false;
      bool FRyGWsqGlT = false;
      bool WRdXMfpNkV = false;
      bool JmlAPBBpkZ = false;
      bool ailrBxePZq = false;
      bool ynWLyLhjim = false;
      bool VsMDiSfxpV = false;
      bool qBULrmekWP = false;
      bool AantWVQZCE = false;
      bool SRGyEgWiIh = false;
      bool QhYEzxSKSK = false;
      bool fxMTluFSfM = false;
      string IVgkGAYluL;
      string BrulFpapFs;
      string sxOHBzOVEX;
      string WetixZXUCB;
      string eDlUrRMFgY;
      string JsPFpKGYjG;
      string kDgWnWxMne;
      string SFmEOoKtPj;
      string mIofOdOorl;
      string SykuPbWPfU;
      string UzRBFEFLqB;
      string AMIATcNAIK;
      string HITCMTUqnl;
      string StOtPmqmZJ;
      string XDxqkGpkbm;
      string NVHUNLfOol;
      string iOWFiGxNkg;
      string kZaymEKcQF;
      string djPBXwmsgD;
      string HcynaJgrIe;
      if(IVgkGAYluL == UzRBFEFLqB){IbzuBnuJhJ = true;}
      else if(UzRBFEFLqB == IVgkGAYluL){WRdXMfpNkV = true;}
      if(BrulFpapFs == AMIATcNAIK){BCyiIzyUgl = true;}
      else if(AMIATcNAIK == BrulFpapFs){JmlAPBBpkZ = true;}
      if(sxOHBzOVEX == HITCMTUqnl){SEghYIalXd = true;}
      else if(HITCMTUqnl == sxOHBzOVEX){ailrBxePZq = true;}
      if(WetixZXUCB == StOtPmqmZJ){WSUkxBjUzj = true;}
      else if(StOtPmqmZJ == WetixZXUCB){ynWLyLhjim = true;}
      if(eDlUrRMFgY == XDxqkGpkbm){BcKXCEePea = true;}
      else if(XDxqkGpkbm == eDlUrRMFgY){VsMDiSfxpV = true;}
      if(JsPFpKGYjG == NVHUNLfOol){KLLVLDuRVs = true;}
      else if(NVHUNLfOol == JsPFpKGYjG){qBULrmekWP = true;}
      if(kDgWnWxMne == iOWFiGxNkg){MIlElhhMlH = true;}
      else if(iOWFiGxNkg == kDgWnWxMne){AantWVQZCE = true;}
      if(SFmEOoKtPj == kZaymEKcQF){OdVxjptIfU = true;}
      if(mIofOdOorl == djPBXwmsgD){dLHwSLHyZs = true;}
      if(SykuPbWPfU == HcynaJgrIe){FRyGWsqGlT = true;}
      while(kZaymEKcQF == SFmEOoKtPj){SRGyEgWiIh = true;}
      while(djPBXwmsgD == djPBXwmsgD){QhYEzxSKSK = true;}
      while(HcynaJgrIe == HcynaJgrIe){fxMTluFSfM = true;}
      if(IbzuBnuJhJ == true){IbzuBnuJhJ = false;}
      if(BCyiIzyUgl == true){BCyiIzyUgl = false;}
      if(SEghYIalXd == true){SEghYIalXd = false;}
      if(WSUkxBjUzj == true){WSUkxBjUzj = false;}
      if(BcKXCEePea == true){BcKXCEePea = false;}
      if(KLLVLDuRVs == true){KLLVLDuRVs = false;}
      if(MIlElhhMlH == true){MIlElhhMlH = false;}
      if(OdVxjptIfU == true){OdVxjptIfU = false;}
      if(dLHwSLHyZs == true){dLHwSLHyZs = false;}
      if(FRyGWsqGlT == true){FRyGWsqGlT = false;}
      if(WRdXMfpNkV == true){WRdXMfpNkV = false;}
      if(JmlAPBBpkZ == true){JmlAPBBpkZ = false;}
      if(ailrBxePZq == true){ailrBxePZq = false;}
      if(ynWLyLhjim == true){ynWLyLhjim = false;}
      if(VsMDiSfxpV == true){VsMDiSfxpV = false;}
      if(qBULrmekWP == true){qBULrmekWP = false;}
      if(AantWVQZCE == true){AantWVQZCE = false;}
      if(SRGyEgWiIh == true){SRGyEgWiIh = false;}
      if(QhYEzxSKSK == true){QhYEzxSKSK = false;}
      if(fxMTluFSfM == true){fxMTluFSfM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JICSSUTYGV
{ 
  void VHuMUhIflD()
  { 
      bool KYOXFnjUur = false;
      bool MiabswJtrY = false;
      bool FScxfEgVWT = false;
      bool efZczHZcgn = false;
      bool LmHMhznmTK = false;
      bool eqLxXruRqB = false;
      bool HOyaNgIxbl = false;
      bool VfNDNRKQOg = false;
      bool QsBLnnUbFH = false;
      bool LIkfgwogzB = false;
      bool ppLhoycHjF = false;
      bool heCKjONlmY = false;
      bool LfqUaMuhWQ = false;
      bool cdQNpZhTWp = false;
      bool KMrAYfFZuR = false;
      bool iCsZoJyqGb = false;
      bool DukScEOoUK = false;
      bool gsPwOznqut = false;
      bool HUlEgZjpXf = false;
      bool aqMtmObYWU = false;
      string nZnBmHdcAy;
      string pBrPzxUadA;
      string TrfmSaPEFC;
      string tzkXGBFcZf;
      string GNROhUqnaF;
      string axpcrusBiM;
      string qZWxEqQUIy;
      string rqAytGaQEx;
      string jbcAbwJHeL;
      string HEtNnfpTKq;
      string EVecNixqil;
      string UbwkbPwVVH;
      string hIpxpnxlKN;
      string QGGNrNwAmr;
      string zRYrqfHIlX;
      string jTyDIwfhlZ;
      string kKfVVNVisN;
      string SuicIQixGK;
      string foAlcwICFu;
      string hOONGnkDWc;
      if(nZnBmHdcAy == EVecNixqil){KYOXFnjUur = true;}
      else if(EVecNixqil == nZnBmHdcAy){ppLhoycHjF = true;}
      if(pBrPzxUadA == UbwkbPwVVH){MiabswJtrY = true;}
      else if(UbwkbPwVVH == pBrPzxUadA){heCKjONlmY = true;}
      if(TrfmSaPEFC == hIpxpnxlKN){FScxfEgVWT = true;}
      else if(hIpxpnxlKN == TrfmSaPEFC){LfqUaMuhWQ = true;}
      if(tzkXGBFcZf == QGGNrNwAmr){efZczHZcgn = true;}
      else if(QGGNrNwAmr == tzkXGBFcZf){cdQNpZhTWp = true;}
      if(GNROhUqnaF == zRYrqfHIlX){LmHMhznmTK = true;}
      else if(zRYrqfHIlX == GNROhUqnaF){KMrAYfFZuR = true;}
      if(axpcrusBiM == jTyDIwfhlZ){eqLxXruRqB = true;}
      else if(jTyDIwfhlZ == axpcrusBiM){iCsZoJyqGb = true;}
      if(qZWxEqQUIy == kKfVVNVisN){HOyaNgIxbl = true;}
      else if(kKfVVNVisN == qZWxEqQUIy){DukScEOoUK = true;}
      if(rqAytGaQEx == SuicIQixGK){VfNDNRKQOg = true;}
      if(jbcAbwJHeL == foAlcwICFu){QsBLnnUbFH = true;}
      if(HEtNnfpTKq == hOONGnkDWc){LIkfgwogzB = true;}
      while(SuicIQixGK == rqAytGaQEx){gsPwOznqut = true;}
      while(foAlcwICFu == foAlcwICFu){HUlEgZjpXf = true;}
      while(hOONGnkDWc == hOONGnkDWc){aqMtmObYWU = true;}
      if(KYOXFnjUur == true){KYOXFnjUur = false;}
      if(MiabswJtrY == true){MiabswJtrY = false;}
      if(FScxfEgVWT == true){FScxfEgVWT = false;}
      if(efZczHZcgn == true){efZczHZcgn = false;}
      if(LmHMhznmTK == true){LmHMhznmTK = false;}
      if(eqLxXruRqB == true){eqLxXruRqB = false;}
      if(HOyaNgIxbl == true){HOyaNgIxbl = false;}
      if(VfNDNRKQOg == true){VfNDNRKQOg = false;}
      if(QsBLnnUbFH == true){QsBLnnUbFH = false;}
      if(LIkfgwogzB == true){LIkfgwogzB = false;}
      if(ppLhoycHjF == true){ppLhoycHjF = false;}
      if(heCKjONlmY == true){heCKjONlmY = false;}
      if(LfqUaMuhWQ == true){LfqUaMuhWQ = false;}
      if(cdQNpZhTWp == true){cdQNpZhTWp = false;}
      if(KMrAYfFZuR == true){KMrAYfFZuR = false;}
      if(iCsZoJyqGb == true){iCsZoJyqGb = false;}
      if(DukScEOoUK == true){DukScEOoUK = false;}
      if(gsPwOznqut == true){gsPwOznqut = false;}
      if(HUlEgZjpXf == true){HUlEgZjpXf = false;}
      if(aqMtmObYWU == true){aqMtmObYWU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class URHRMSRYLO
{ 
  void VIdjeRVBoJ()
  { 
      bool dYNpNaAFbm = false;
      bool VYsVTSgaFN = false;
      bool pMdMHbfqKE = false;
      bool oScpNxWoMo = false;
      bool TFqASYOHMP = false;
      bool VEmXnQuBhk = false;
      bool uJuXxDwDHV = false;
      bool wqNPskUcsi = false;
      bool NXdtikeFCw = false;
      bool BUHatJJTDP = false;
      bool cLzpTdpWdD = false;
      bool wSHzXWfBnM = false;
      bool XqAKUajlVi = false;
      bool aBZcFCYmaF = false;
      bool tHazAiNIDW = false;
      bool dIfprlKnVr = false;
      bool sEBtbtsesU = false;
      bool yrZiSPPBKk = false;
      bool NbhzFSVijT = false;
      bool rjRhLoGfWF = false;
      string lrzLCAgRwm;
      string aIHpstiEjd;
      string xkudFDDYxd;
      string KPtftsaunE;
      string rlwjVXwNQW;
      string pFGHlBxVGz;
      string xHUSbLNbwz;
      string SnQfkKnLHg;
      string GoHZnEIlts;
      string wFnoGjRdHK;
      string JURQDCoaWa;
      string MkOYrIAteX;
      string CbgCDNzbYA;
      string sKEwXlXqWk;
      string PgPSgKqPwy;
      string jXzjIhmPNp;
      string CMBVhBgRBG;
      string jIWsHULNVr;
      string WjeaQULTno;
      string yIcfiCfske;
      if(lrzLCAgRwm == JURQDCoaWa){dYNpNaAFbm = true;}
      else if(JURQDCoaWa == lrzLCAgRwm){cLzpTdpWdD = true;}
      if(aIHpstiEjd == MkOYrIAteX){VYsVTSgaFN = true;}
      else if(MkOYrIAteX == aIHpstiEjd){wSHzXWfBnM = true;}
      if(xkudFDDYxd == CbgCDNzbYA){pMdMHbfqKE = true;}
      else if(CbgCDNzbYA == xkudFDDYxd){XqAKUajlVi = true;}
      if(KPtftsaunE == sKEwXlXqWk){oScpNxWoMo = true;}
      else if(sKEwXlXqWk == KPtftsaunE){aBZcFCYmaF = true;}
      if(rlwjVXwNQW == PgPSgKqPwy){TFqASYOHMP = true;}
      else if(PgPSgKqPwy == rlwjVXwNQW){tHazAiNIDW = true;}
      if(pFGHlBxVGz == jXzjIhmPNp){VEmXnQuBhk = true;}
      else if(jXzjIhmPNp == pFGHlBxVGz){dIfprlKnVr = true;}
      if(xHUSbLNbwz == CMBVhBgRBG){uJuXxDwDHV = true;}
      else if(CMBVhBgRBG == xHUSbLNbwz){sEBtbtsesU = true;}
      if(SnQfkKnLHg == jIWsHULNVr){wqNPskUcsi = true;}
      if(GoHZnEIlts == WjeaQULTno){NXdtikeFCw = true;}
      if(wFnoGjRdHK == yIcfiCfske){BUHatJJTDP = true;}
      while(jIWsHULNVr == SnQfkKnLHg){yrZiSPPBKk = true;}
      while(WjeaQULTno == WjeaQULTno){NbhzFSVijT = true;}
      while(yIcfiCfske == yIcfiCfske){rjRhLoGfWF = true;}
      if(dYNpNaAFbm == true){dYNpNaAFbm = false;}
      if(VYsVTSgaFN == true){VYsVTSgaFN = false;}
      if(pMdMHbfqKE == true){pMdMHbfqKE = false;}
      if(oScpNxWoMo == true){oScpNxWoMo = false;}
      if(TFqASYOHMP == true){TFqASYOHMP = false;}
      if(VEmXnQuBhk == true){VEmXnQuBhk = false;}
      if(uJuXxDwDHV == true){uJuXxDwDHV = false;}
      if(wqNPskUcsi == true){wqNPskUcsi = false;}
      if(NXdtikeFCw == true){NXdtikeFCw = false;}
      if(BUHatJJTDP == true){BUHatJJTDP = false;}
      if(cLzpTdpWdD == true){cLzpTdpWdD = false;}
      if(wSHzXWfBnM == true){wSHzXWfBnM = false;}
      if(XqAKUajlVi == true){XqAKUajlVi = false;}
      if(aBZcFCYmaF == true){aBZcFCYmaF = false;}
      if(tHazAiNIDW == true){tHazAiNIDW = false;}
      if(dIfprlKnVr == true){dIfprlKnVr = false;}
      if(sEBtbtsesU == true){sEBtbtsesU = false;}
      if(yrZiSPPBKk == true){yrZiSPPBKk = false;}
      if(NbhzFSVijT == true){NbhzFSVijT = false;}
      if(rjRhLoGfWF == true){rjRhLoGfWF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EQMBKAYXLH
{ 
  void PjBrStiZph()
  { 
      bool XjycuFxHwH = false;
      bool SPHNAcMbmI = false;
      bool InrCnuVUUH = false;
      bool VbRVHeUDdd = false;
      bool QmXCmszTqy = false;
      bool XuwtKjquoz = false;
      bool ibmnlqxlFU = false;
      bool IIxIqUPoPu = false;
      bool uCdVjaeXLX = false;
      bool mZNdtoAjPw = false;
      bool uNNVpOxnDo = false;
      bool TCftEgyREL = false;
      bool LZZhghtTNC = false;
      bool UfZTzgnHfU = false;
      bool dpTVDksTZN = false;
      bool qheEjUnfoH = false;
      bool UcZBUnbLtW = false;
      bool rpkjhVFDdw = false;
      bool oatALlAUjd = false;
      bool sISXAAPSBP = false;
      string rNrhfdzWFB;
      string QCfqrhqCIW;
      string SOcFMRIrho;
      string CDPREijTeb;
      string rQoJehsuNM;
      string tXFsxcklVO;
      string UGnPzNmOmJ;
      string xXXfdBYSad;
      string XMdUudxVUa;
      string yxxQHkcYJQ;
      string ueIEOWAZPu;
      string ERLqpHcSUV;
      string QRtLLAZGYr;
      string YzIJisEZGY;
      string dXGYWfkGZz;
      string IJEnAdjwrO;
      string wsBWWEIBIw;
      string DDMwrrKUoe;
      string OTgYjOuUJF;
      string IHgqbjWiCS;
      if(rNrhfdzWFB == ueIEOWAZPu){XjycuFxHwH = true;}
      else if(ueIEOWAZPu == rNrhfdzWFB){uNNVpOxnDo = true;}
      if(QCfqrhqCIW == ERLqpHcSUV){SPHNAcMbmI = true;}
      else if(ERLqpHcSUV == QCfqrhqCIW){TCftEgyREL = true;}
      if(SOcFMRIrho == QRtLLAZGYr){InrCnuVUUH = true;}
      else if(QRtLLAZGYr == SOcFMRIrho){LZZhghtTNC = true;}
      if(CDPREijTeb == YzIJisEZGY){VbRVHeUDdd = true;}
      else if(YzIJisEZGY == CDPREijTeb){UfZTzgnHfU = true;}
      if(rQoJehsuNM == dXGYWfkGZz){QmXCmszTqy = true;}
      else if(dXGYWfkGZz == rQoJehsuNM){dpTVDksTZN = true;}
      if(tXFsxcklVO == IJEnAdjwrO){XuwtKjquoz = true;}
      else if(IJEnAdjwrO == tXFsxcklVO){qheEjUnfoH = true;}
      if(UGnPzNmOmJ == wsBWWEIBIw){ibmnlqxlFU = true;}
      else if(wsBWWEIBIw == UGnPzNmOmJ){UcZBUnbLtW = true;}
      if(xXXfdBYSad == DDMwrrKUoe){IIxIqUPoPu = true;}
      if(XMdUudxVUa == OTgYjOuUJF){uCdVjaeXLX = true;}
      if(yxxQHkcYJQ == IHgqbjWiCS){mZNdtoAjPw = true;}
      while(DDMwrrKUoe == xXXfdBYSad){rpkjhVFDdw = true;}
      while(OTgYjOuUJF == OTgYjOuUJF){oatALlAUjd = true;}
      while(IHgqbjWiCS == IHgqbjWiCS){sISXAAPSBP = true;}
      if(XjycuFxHwH == true){XjycuFxHwH = false;}
      if(SPHNAcMbmI == true){SPHNAcMbmI = false;}
      if(InrCnuVUUH == true){InrCnuVUUH = false;}
      if(VbRVHeUDdd == true){VbRVHeUDdd = false;}
      if(QmXCmszTqy == true){QmXCmszTqy = false;}
      if(XuwtKjquoz == true){XuwtKjquoz = false;}
      if(ibmnlqxlFU == true){ibmnlqxlFU = false;}
      if(IIxIqUPoPu == true){IIxIqUPoPu = false;}
      if(uCdVjaeXLX == true){uCdVjaeXLX = false;}
      if(mZNdtoAjPw == true){mZNdtoAjPw = false;}
      if(uNNVpOxnDo == true){uNNVpOxnDo = false;}
      if(TCftEgyREL == true){TCftEgyREL = false;}
      if(LZZhghtTNC == true){LZZhghtTNC = false;}
      if(UfZTzgnHfU == true){UfZTzgnHfU = false;}
      if(dpTVDksTZN == true){dpTVDksTZN = false;}
      if(qheEjUnfoH == true){qheEjUnfoH = false;}
      if(UcZBUnbLtW == true){UcZBUnbLtW = false;}
      if(rpkjhVFDdw == true){rpkjhVFDdw = false;}
      if(oatALlAUjd == true){oatALlAUjd = false;}
      if(sISXAAPSBP == true){sISXAAPSBP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MTTGKYHSFR
{ 
  void sCKpRhKypW()
  { 
      bool aHQKSuCpcr = false;
      bool aQkpaVsink = false;
      bool jycOuGbnlu = false;
      bool IHmHBVuQqs = false;
      bool THntCmKWaE = false;
      bool SMUWSbdCOL = false;
      bool SNEgiSccoF = false;
      bool ZcqtQcKiLI = false;
      bool uENhcwlPnY = false;
      bool qsBeZFCGKi = false;
      bool JghVdpUaGp = false;
      bool RuqGQOAVEm = false;
      bool fNoPNgaMTK = false;
      bool ZDXbyNWrDm = false;
      bool aLJyHwBtOL = false;
      bool FfBXCwrSHw = false;
      bool OIGuQNWOHC = false;
      bool rIRRLTDpHR = false;
      bool efxIFsBAZC = false;
      bool VEjHXSFNhs = false;
      string mXuuuPcByf;
      string dXHoiTBejf;
      string GfdUMymlpO;
      string DZbMZEwGUq;
      string yBHBtsOFRc;
      string APPkbHtZhx;
      string bqKjbDutOd;
      string WtJsgFYbaT;
      string ihUMOmKpkS;
      string JWXXOHpXZp;
      string xUpmFFGWDV;
      string hSzONtWxUo;
      string sEJuTAWkdZ;
      string OACjWOqgHI;
      string gnmOkqWJJU;
      string krCkxrKuSF;
      string iUrcHhQPrz;
      string CopLHERtKc;
      string dMaJoWxRld;
      string DwNCZLuJHC;
      if(mXuuuPcByf == xUpmFFGWDV){aHQKSuCpcr = true;}
      else if(xUpmFFGWDV == mXuuuPcByf){JghVdpUaGp = true;}
      if(dXHoiTBejf == hSzONtWxUo){aQkpaVsink = true;}
      else if(hSzONtWxUo == dXHoiTBejf){RuqGQOAVEm = true;}
      if(GfdUMymlpO == sEJuTAWkdZ){jycOuGbnlu = true;}
      else if(sEJuTAWkdZ == GfdUMymlpO){fNoPNgaMTK = true;}
      if(DZbMZEwGUq == OACjWOqgHI){IHmHBVuQqs = true;}
      else if(OACjWOqgHI == DZbMZEwGUq){ZDXbyNWrDm = true;}
      if(yBHBtsOFRc == gnmOkqWJJU){THntCmKWaE = true;}
      else if(gnmOkqWJJU == yBHBtsOFRc){aLJyHwBtOL = true;}
      if(APPkbHtZhx == krCkxrKuSF){SMUWSbdCOL = true;}
      else if(krCkxrKuSF == APPkbHtZhx){FfBXCwrSHw = true;}
      if(bqKjbDutOd == iUrcHhQPrz){SNEgiSccoF = true;}
      else if(iUrcHhQPrz == bqKjbDutOd){OIGuQNWOHC = true;}
      if(WtJsgFYbaT == CopLHERtKc){ZcqtQcKiLI = true;}
      if(ihUMOmKpkS == dMaJoWxRld){uENhcwlPnY = true;}
      if(JWXXOHpXZp == DwNCZLuJHC){qsBeZFCGKi = true;}
      while(CopLHERtKc == WtJsgFYbaT){rIRRLTDpHR = true;}
      while(dMaJoWxRld == dMaJoWxRld){efxIFsBAZC = true;}
      while(DwNCZLuJHC == DwNCZLuJHC){VEjHXSFNhs = true;}
      if(aHQKSuCpcr == true){aHQKSuCpcr = false;}
      if(aQkpaVsink == true){aQkpaVsink = false;}
      if(jycOuGbnlu == true){jycOuGbnlu = false;}
      if(IHmHBVuQqs == true){IHmHBVuQqs = false;}
      if(THntCmKWaE == true){THntCmKWaE = false;}
      if(SMUWSbdCOL == true){SMUWSbdCOL = false;}
      if(SNEgiSccoF == true){SNEgiSccoF = false;}
      if(ZcqtQcKiLI == true){ZcqtQcKiLI = false;}
      if(uENhcwlPnY == true){uENhcwlPnY = false;}
      if(qsBeZFCGKi == true){qsBeZFCGKi = false;}
      if(JghVdpUaGp == true){JghVdpUaGp = false;}
      if(RuqGQOAVEm == true){RuqGQOAVEm = false;}
      if(fNoPNgaMTK == true){fNoPNgaMTK = false;}
      if(ZDXbyNWrDm == true){ZDXbyNWrDm = false;}
      if(aLJyHwBtOL == true){aLJyHwBtOL = false;}
      if(FfBXCwrSHw == true){FfBXCwrSHw = false;}
      if(OIGuQNWOHC == true){OIGuQNWOHC = false;}
      if(rIRRLTDpHR == true){rIRRLTDpHR = false;}
      if(efxIFsBAZC == true){efxIFsBAZC = false;}
      if(VEjHXSFNhs == true){VEjHXSFNhs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TFVQEWHZXV
{ 
  void PIstfhXFEM()
  { 
      bool ZppBQUroAo = false;
      bool CsZGUpiNaW = false;
      bool zTtykcwKue = false;
      bool QpLOyRrcng = false;
      bool boJzQHimsf = false;
      bool ynaSlGuqPm = false;
      bool XgtUYMhKID = false;
      bool xFYstJJthc = false;
      bool sJROgbOrcq = false;
      bool VAMAIttnaD = false;
      bool ZYeoirOgXb = false;
      bool xBJltOOenw = false;
      bool xohQhxrYkz = false;
      bool PUTdDUdcfn = false;
      bool NhTAtUqaGt = false;
      bool fOzdFkpOHk = false;
      bool zpwYMbgeiZ = false;
      bool jlzAiPUhVM = false;
      bool FRSpTAUoXS = false;
      bool dPUtnWlumS = false;
      string SdDwzJOTbY;
      string krsqZaaSGM;
      string QynZlrLSCE;
      string sCBCxtkxdY;
      string XyryeISjmA;
      string sTHftUpcJH;
      string ywRXehqpsf;
      string pdngoSFoud;
      string YafBKYtUIc;
      string EImWZbgTSw;
      string QcpGKPeZpb;
      string OAheiWPPMG;
      string nVhPbhpRHN;
      string kkWyNwkYpu;
      string tUefODZHnC;
      string LQHMIttaec;
      string YMScpcdjRl;
      string lqYRLSqBAX;
      string HidEBTdKoS;
      string BJtNWgCBok;
      if(SdDwzJOTbY == QcpGKPeZpb){ZppBQUroAo = true;}
      else if(QcpGKPeZpb == SdDwzJOTbY){ZYeoirOgXb = true;}
      if(krsqZaaSGM == OAheiWPPMG){CsZGUpiNaW = true;}
      else if(OAheiWPPMG == krsqZaaSGM){xBJltOOenw = true;}
      if(QynZlrLSCE == nVhPbhpRHN){zTtykcwKue = true;}
      else if(nVhPbhpRHN == QynZlrLSCE){xohQhxrYkz = true;}
      if(sCBCxtkxdY == kkWyNwkYpu){QpLOyRrcng = true;}
      else if(kkWyNwkYpu == sCBCxtkxdY){PUTdDUdcfn = true;}
      if(XyryeISjmA == tUefODZHnC){boJzQHimsf = true;}
      else if(tUefODZHnC == XyryeISjmA){NhTAtUqaGt = true;}
      if(sTHftUpcJH == LQHMIttaec){ynaSlGuqPm = true;}
      else if(LQHMIttaec == sTHftUpcJH){fOzdFkpOHk = true;}
      if(ywRXehqpsf == YMScpcdjRl){XgtUYMhKID = true;}
      else if(YMScpcdjRl == ywRXehqpsf){zpwYMbgeiZ = true;}
      if(pdngoSFoud == lqYRLSqBAX){xFYstJJthc = true;}
      if(YafBKYtUIc == HidEBTdKoS){sJROgbOrcq = true;}
      if(EImWZbgTSw == BJtNWgCBok){VAMAIttnaD = true;}
      while(lqYRLSqBAX == pdngoSFoud){jlzAiPUhVM = true;}
      while(HidEBTdKoS == HidEBTdKoS){FRSpTAUoXS = true;}
      while(BJtNWgCBok == BJtNWgCBok){dPUtnWlumS = true;}
      if(ZppBQUroAo == true){ZppBQUroAo = false;}
      if(CsZGUpiNaW == true){CsZGUpiNaW = false;}
      if(zTtykcwKue == true){zTtykcwKue = false;}
      if(QpLOyRrcng == true){QpLOyRrcng = false;}
      if(boJzQHimsf == true){boJzQHimsf = false;}
      if(ynaSlGuqPm == true){ynaSlGuqPm = false;}
      if(XgtUYMhKID == true){XgtUYMhKID = false;}
      if(xFYstJJthc == true){xFYstJJthc = false;}
      if(sJROgbOrcq == true){sJROgbOrcq = false;}
      if(VAMAIttnaD == true){VAMAIttnaD = false;}
      if(ZYeoirOgXb == true){ZYeoirOgXb = false;}
      if(xBJltOOenw == true){xBJltOOenw = false;}
      if(xohQhxrYkz == true){xohQhxrYkz = false;}
      if(PUTdDUdcfn == true){PUTdDUdcfn = false;}
      if(NhTAtUqaGt == true){NhTAtUqaGt = false;}
      if(fOzdFkpOHk == true){fOzdFkpOHk = false;}
      if(zpwYMbgeiZ == true){zpwYMbgeiZ = false;}
      if(jlzAiPUhVM == true){jlzAiPUhVM = false;}
      if(FRSpTAUoXS == true){FRSpTAUoXS = false;}
      if(dPUtnWlumS == true){dPUtnWlumS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BAQHLJAZLF
{ 
  void wMCApipiKn()
  { 
      bool retIHOOrcD = false;
      bool BmAwXRCwNd = false;
      bool xhbsOOIEUV = false;
      bool anXrIfIiqE = false;
      bool tJXgmglUAn = false;
      bool hdcMpKDAsr = false;
      bool FJXHbMOImq = false;
      bool JTFIinJuGh = false;
      bool bnDfmxKLBy = false;
      bool cHoyzkkQEZ = false;
      bool RcgIeOXUcC = false;
      bool AIsLQRFrUd = false;
      bool CCHnOBdHJy = false;
      bool DspgPyGtAX = false;
      bool ZpizyUNcgh = false;
      bool eswZXPVrtd = false;
      bool jQKdyGRMwR = false;
      bool KKqwELSIpt = false;
      bool mBZbTKwPIz = false;
      bool cNAWmJeFAq = false;
      string AwMQyueQGE;
      string QFHAEHuwPt;
      string ymTsIbCxff;
      string MSmsWaLmRZ;
      string JPwMaCKfFi;
      string GGsZXMcTIV;
      string sgjaqxROdc;
      string uIdokhqGRF;
      string RVrwYGZNUJ;
      string yreugcfVUc;
      string kuBcmybDop;
      string VVBCEWomBk;
      string XEsUdDdhIH;
      string CVkoUVUOJa;
      string dVYencqbqJ;
      string nrTjFgCgyj;
      string TsugnzjLhh;
      string CZdaGBeOfB;
      string LCqyTJBBjn;
      string TmQYGkaqpn;
      if(AwMQyueQGE == kuBcmybDop){retIHOOrcD = true;}
      else if(kuBcmybDop == AwMQyueQGE){RcgIeOXUcC = true;}
      if(QFHAEHuwPt == VVBCEWomBk){BmAwXRCwNd = true;}
      else if(VVBCEWomBk == QFHAEHuwPt){AIsLQRFrUd = true;}
      if(ymTsIbCxff == XEsUdDdhIH){xhbsOOIEUV = true;}
      else if(XEsUdDdhIH == ymTsIbCxff){CCHnOBdHJy = true;}
      if(MSmsWaLmRZ == CVkoUVUOJa){anXrIfIiqE = true;}
      else if(CVkoUVUOJa == MSmsWaLmRZ){DspgPyGtAX = true;}
      if(JPwMaCKfFi == dVYencqbqJ){tJXgmglUAn = true;}
      else if(dVYencqbqJ == JPwMaCKfFi){ZpizyUNcgh = true;}
      if(GGsZXMcTIV == nrTjFgCgyj){hdcMpKDAsr = true;}
      else if(nrTjFgCgyj == GGsZXMcTIV){eswZXPVrtd = true;}
      if(sgjaqxROdc == TsugnzjLhh){FJXHbMOImq = true;}
      else if(TsugnzjLhh == sgjaqxROdc){jQKdyGRMwR = true;}
      if(uIdokhqGRF == CZdaGBeOfB){JTFIinJuGh = true;}
      if(RVrwYGZNUJ == LCqyTJBBjn){bnDfmxKLBy = true;}
      if(yreugcfVUc == TmQYGkaqpn){cHoyzkkQEZ = true;}
      while(CZdaGBeOfB == uIdokhqGRF){KKqwELSIpt = true;}
      while(LCqyTJBBjn == LCqyTJBBjn){mBZbTKwPIz = true;}
      while(TmQYGkaqpn == TmQYGkaqpn){cNAWmJeFAq = true;}
      if(retIHOOrcD == true){retIHOOrcD = false;}
      if(BmAwXRCwNd == true){BmAwXRCwNd = false;}
      if(xhbsOOIEUV == true){xhbsOOIEUV = false;}
      if(anXrIfIiqE == true){anXrIfIiqE = false;}
      if(tJXgmglUAn == true){tJXgmglUAn = false;}
      if(hdcMpKDAsr == true){hdcMpKDAsr = false;}
      if(FJXHbMOImq == true){FJXHbMOImq = false;}
      if(JTFIinJuGh == true){JTFIinJuGh = false;}
      if(bnDfmxKLBy == true){bnDfmxKLBy = false;}
      if(cHoyzkkQEZ == true){cHoyzkkQEZ = false;}
      if(RcgIeOXUcC == true){RcgIeOXUcC = false;}
      if(AIsLQRFrUd == true){AIsLQRFrUd = false;}
      if(CCHnOBdHJy == true){CCHnOBdHJy = false;}
      if(DspgPyGtAX == true){DspgPyGtAX = false;}
      if(ZpizyUNcgh == true){ZpizyUNcgh = false;}
      if(eswZXPVrtd == true){eswZXPVrtd = false;}
      if(jQKdyGRMwR == true){jQKdyGRMwR = false;}
      if(KKqwELSIpt == true){KKqwELSIpt = false;}
      if(mBZbTKwPIz == true){mBZbTKwPIz = false;}
      if(cNAWmJeFAq == true){cNAWmJeFAq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KWAVQDGRMU
{ 
  void aQYioBSdBA()
  { 
      bool IlJhdZmyxR = false;
      bool lRmQoucHNx = false;
      bool TqgSWUlAgX = false;
      bool PWHLhgVmyp = false;
      bool AMALrgExLr = false;
      bool MVmyMREqLI = false;
      bool mlRZCOKbhI = false;
      bool ZoJXxGqUZo = false;
      bool PoooKsjIzQ = false;
      bool beboCOuZJd = false;
      bool WcODRXLPBF = false;
      bool ZiQWryxbOI = false;
      bool eBcQfuNUUi = false;
      bool LQLwSmZlWm = false;
      bool gUHsqsNEwE = false;
      bool RSLAzUAyWW = false;
      bool JqtSsIXUDF = false;
      bool XKFbbKtiYm = false;
      bool gIXQQsFKwx = false;
      bool mbOAcpZnAh = false;
      string wOFCpjrHmW;
      string cDUhzRPpuY;
      string VDwxOTBCPY;
      string IFDmMNFiSG;
      string lrTaoMoAhj;
      string uupGqsSHnV;
      string ipqOOWAgUk;
      string MgWolcjUHB;
      string dBTfdMPxuT;
      string uxtwWwAEMS;
      string MIexWNYBTN;
      string JxAmrhVLkB;
      string HClBoPmZRp;
      string ceIooVVVJP;
      string nNdhKxwHEo;
      string ZoTKLKVdIH;
      string ayjckdoKxV;
      string LACUNsXEqq;
      string SeVbPmKxde;
      string zqNBnodAwf;
      if(wOFCpjrHmW == MIexWNYBTN){IlJhdZmyxR = true;}
      else if(MIexWNYBTN == wOFCpjrHmW){WcODRXLPBF = true;}
      if(cDUhzRPpuY == JxAmrhVLkB){lRmQoucHNx = true;}
      else if(JxAmrhVLkB == cDUhzRPpuY){ZiQWryxbOI = true;}
      if(VDwxOTBCPY == HClBoPmZRp){TqgSWUlAgX = true;}
      else if(HClBoPmZRp == VDwxOTBCPY){eBcQfuNUUi = true;}
      if(IFDmMNFiSG == ceIooVVVJP){PWHLhgVmyp = true;}
      else if(ceIooVVVJP == IFDmMNFiSG){LQLwSmZlWm = true;}
      if(lrTaoMoAhj == nNdhKxwHEo){AMALrgExLr = true;}
      else if(nNdhKxwHEo == lrTaoMoAhj){gUHsqsNEwE = true;}
      if(uupGqsSHnV == ZoTKLKVdIH){MVmyMREqLI = true;}
      else if(ZoTKLKVdIH == uupGqsSHnV){RSLAzUAyWW = true;}
      if(ipqOOWAgUk == ayjckdoKxV){mlRZCOKbhI = true;}
      else if(ayjckdoKxV == ipqOOWAgUk){JqtSsIXUDF = true;}
      if(MgWolcjUHB == LACUNsXEqq){ZoJXxGqUZo = true;}
      if(dBTfdMPxuT == SeVbPmKxde){PoooKsjIzQ = true;}
      if(uxtwWwAEMS == zqNBnodAwf){beboCOuZJd = true;}
      while(LACUNsXEqq == MgWolcjUHB){XKFbbKtiYm = true;}
      while(SeVbPmKxde == SeVbPmKxde){gIXQQsFKwx = true;}
      while(zqNBnodAwf == zqNBnodAwf){mbOAcpZnAh = true;}
      if(IlJhdZmyxR == true){IlJhdZmyxR = false;}
      if(lRmQoucHNx == true){lRmQoucHNx = false;}
      if(TqgSWUlAgX == true){TqgSWUlAgX = false;}
      if(PWHLhgVmyp == true){PWHLhgVmyp = false;}
      if(AMALrgExLr == true){AMALrgExLr = false;}
      if(MVmyMREqLI == true){MVmyMREqLI = false;}
      if(mlRZCOKbhI == true){mlRZCOKbhI = false;}
      if(ZoJXxGqUZo == true){ZoJXxGqUZo = false;}
      if(PoooKsjIzQ == true){PoooKsjIzQ = false;}
      if(beboCOuZJd == true){beboCOuZJd = false;}
      if(WcODRXLPBF == true){WcODRXLPBF = false;}
      if(ZiQWryxbOI == true){ZiQWryxbOI = false;}
      if(eBcQfuNUUi == true){eBcQfuNUUi = false;}
      if(LQLwSmZlWm == true){LQLwSmZlWm = false;}
      if(gUHsqsNEwE == true){gUHsqsNEwE = false;}
      if(RSLAzUAyWW == true){RSLAzUAyWW = false;}
      if(JqtSsIXUDF == true){JqtSsIXUDF = false;}
      if(XKFbbKtiYm == true){XKFbbKtiYm = false;}
      if(gIXQQsFKwx == true){gIXQQsFKwx = false;}
      if(mbOAcpZnAh == true){mbOAcpZnAh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FACIZDOGLC
{ 
  void UnhggMqkPN()
  { 
      bool HudnuQkKBc = false;
      bool ysyijriKoZ = false;
      bool xzwYKHQxTr = false;
      bool YicMmryBQA = false;
      bool pPhhqBYZNE = false;
      bool OpIMLIzFdm = false;
      bool znpIEPQlur = false;
      bool shsoigROgI = false;
      bool iqjPdhZPBd = false;
      bool ssXdACYYdb = false;
      bool jmdVLfwTdd = false;
      bool qjYUDHEaeV = false;
      bool oBjRyzKPnf = false;
      bool HrkEXwNNEx = false;
      bool kGlWmIUCZr = false;
      bool yytHmiCMWL = false;
      bool UgfxWyyTwH = false;
      bool tpWgjhONdo = false;
      bool dIouhIxdQn = false;
      bool sAqrcEZozn = false;
      string mWNgGTNUpb;
      string zpWtaOGWKY;
      string MEgjHemAQB;
      string fXnTmoAEgb;
      string PDwAZTObzd;
      string szqWThpdZa;
      string gMEoubCCHk;
      string OBphJIIfJn;
      string QLBlIgfQzF;
      string zWeFuCzHFx;
      string QLUOPqJIML;
      string YJTlKVLRgN;
      string wkDBkqWjlH;
      string JBaMWEplWQ;
      string WWDnfpDstZ;
      string pgaqBfISdX;
      string UYWFBXhHOG;
      string eZuPpYgOUt;
      string ncoMQbaiKp;
      string uWIywyAylI;
      if(mWNgGTNUpb == QLUOPqJIML){HudnuQkKBc = true;}
      else if(QLUOPqJIML == mWNgGTNUpb){jmdVLfwTdd = true;}
      if(zpWtaOGWKY == YJTlKVLRgN){ysyijriKoZ = true;}
      else if(YJTlKVLRgN == zpWtaOGWKY){qjYUDHEaeV = true;}
      if(MEgjHemAQB == wkDBkqWjlH){xzwYKHQxTr = true;}
      else if(wkDBkqWjlH == MEgjHemAQB){oBjRyzKPnf = true;}
      if(fXnTmoAEgb == JBaMWEplWQ){YicMmryBQA = true;}
      else if(JBaMWEplWQ == fXnTmoAEgb){HrkEXwNNEx = true;}
      if(PDwAZTObzd == WWDnfpDstZ){pPhhqBYZNE = true;}
      else if(WWDnfpDstZ == PDwAZTObzd){kGlWmIUCZr = true;}
      if(szqWThpdZa == pgaqBfISdX){OpIMLIzFdm = true;}
      else if(pgaqBfISdX == szqWThpdZa){yytHmiCMWL = true;}
      if(gMEoubCCHk == UYWFBXhHOG){znpIEPQlur = true;}
      else if(UYWFBXhHOG == gMEoubCCHk){UgfxWyyTwH = true;}
      if(OBphJIIfJn == eZuPpYgOUt){shsoigROgI = true;}
      if(QLBlIgfQzF == ncoMQbaiKp){iqjPdhZPBd = true;}
      if(zWeFuCzHFx == uWIywyAylI){ssXdACYYdb = true;}
      while(eZuPpYgOUt == OBphJIIfJn){tpWgjhONdo = true;}
      while(ncoMQbaiKp == ncoMQbaiKp){dIouhIxdQn = true;}
      while(uWIywyAylI == uWIywyAylI){sAqrcEZozn = true;}
      if(HudnuQkKBc == true){HudnuQkKBc = false;}
      if(ysyijriKoZ == true){ysyijriKoZ = false;}
      if(xzwYKHQxTr == true){xzwYKHQxTr = false;}
      if(YicMmryBQA == true){YicMmryBQA = false;}
      if(pPhhqBYZNE == true){pPhhqBYZNE = false;}
      if(OpIMLIzFdm == true){OpIMLIzFdm = false;}
      if(znpIEPQlur == true){znpIEPQlur = false;}
      if(shsoigROgI == true){shsoigROgI = false;}
      if(iqjPdhZPBd == true){iqjPdhZPBd = false;}
      if(ssXdACYYdb == true){ssXdACYYdb = false;}
      if(jmdVLfwTdd == true){jmdVLfwTdd = false;}
      if(qjYUDHEaeV == true){qjYUDHEaeV = false;}
      if(oBjRyzKPnf == true){oBjRyzKPnf = false;}
      if(HrkEXwNNEx == true){HrkEXwNNEx = false;}
      if(kGlWmIUCZr == true){kGlWmIUCZr = false;}
      if(yytHmiCMWL == true){yytHmiCMWL = false;}
      if(UgfxWyyTwH == true){UgfxWyyTwH = false;}
      if(tpWgjhONdo == true){tpWgjhONdo = false;}
      if(dIouhIxdQn == true){dIouhIxdQn = false;}
      if(sAqrcEZozn == true){sAqrcEZozn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YHVABTJMIJ
{ 
  void RkRmGjRXtw()
  { 
      bool mIhyajUaSN = false;
      bool rfklqeLBsJ = false;
      bool anUYPQjyfx = false;
      bool xtFFXXrbib = false;
      bool RbZWenUYgm = false;
      bool RRemCznJiK = false;
      bool zWuUQxaeNT = false;
      bool mjSRqzNyta = false;
      bool uLQrefPRDX = false;
      bool jhrXbufFFg = false;
      bool NoKNzhyNwD = false;
      bool koPHOmFCok = false;
      bool hIbojFqtow = false;
      bool SIrMNFBDrx = false;
      bool gCVzltRkJn = false;
      bool pdPUzENUct = false;
      bool pDYAkcwCtI = false;
      bool lBJqDfmbDo = false;
      bool mGkAFnrXNI = false;
      bool rfZyGdcUOJ = false;
      string KHRlEhOxSn;
      string NLHwwUqVdq;
      string leOIRhzcNK;
      string jTqnseqcqb;
      string SwFpTbzOsx;
      string ZYUSRerIUV;
      string hljIDtTSDR;
      string dNdBXpZYnp;
      string ikiQjLyXVN;
      string mhIVtgLxlZ;
      string HfKbSLuSub;
      string FSTdmwCTXr;
      string uwxpeuFIHp;
      string ebmOhDZHxY;
      string PectHTOdhx;
      string eqZtdLiTxX;
      string GlLEwdfFuj;
      string VuWybQSCiK;
      string gaZJLmCrjW;
      string TFKYSdSXxc;
      if(KHRlEhOxSn == HfKbSLuSub){mIhyajUaSN = true;}
      else if(HfKbSLuSub == KHRlEhOxSn){NoKNzhyNwD = true;}
      if(NLHwwUqVdq == FSTdmwCTXr){rfklqeLBsJ = true;}
      else if(FSTdmwCTXr == NLHwwUqVdq){koPHOmFCok = true;}
      if(leOIRhzcNK == uwxpeuFIHp){anUYPQjyfx = true;}
      else if(uwxpeuFIHp == leOIRhzcNK){hIbojFqtow = true;}
      if(jTqnseqcqb == ebmOhDZHxY){xtFFXXrbib = true;}
      else if(ebmOhDZHxY == jTqnseqcqb){SIrMNFBDrx = true;}
      if(SwFpTbzOsx == PectHTOdhx){RbZWenUYgm = true;}
      else if(PectHTOdhx == SwFpTbzOsx){gCVzltRkJn = true;}
      if(ZYUSRerIUV == eqZtdLiTxX){RRemCznJiK = true;}
      else if(eqZtdLiTxX == ZYUSRerIUV){pdPUzENUct = true;}
      if(hljIDtTSDR == GlLEwdfFuj){zWuUQxaeNT = true;}
      else if(GlLEwdfFuj == hljIDtTSDR){pDYAkcwCtI = true;}
      if(dNdBXpZYnp == VuWybQSCiK){mjSRqzNyta = true;}
      if(ikiQjLyXVN == gaZJLmCrjW){uLQrefPRDX = true;}
      if(mhIVtgLxlZ == TFKYSdSXxc){jhrXbufFFg = true;}
      while(VuWybQSCiK == dNdBXpZYnp){lBJqDfmbDo = true;}
      while(gaZJLmCrjW == gaZJLmCrjW){mGkAFnrXNI = true;}
      while(TFKYSdSXxc == TFKYSdSXxc){rfZyGdcUOJ = true;}
      if(mIhyajUaSN == true){mIhyajUaSN = false;}
      if(rfklqeLBsJ == true){rfklqeLBsJ = false;}
      if(anUYPQjyfx == true){anUYPQjyfx = false;}
      if(xtFFXXrbib == true){xtFFXXrbib = false;}
      if(RbZWenUYgm == true){RbZWenUYgm = false;}
      if(RRemCznJiK == true){RRemCznJiK = false;}
      if(zWuUQxaeNT == true){zWuUQxaeNT = false;}
      if(mjSRqzNyta == true){mjSRqzNyta = false;}
      if(uLQrefPRDX == true){uLQrefPRDX = false;}
      if(jhrXbufFFg == true){jhrXbufFFg = false;}
      if(NoKNzhyNwD == true){NoKNzhyNwD = false;}
      if(koPHOmFCok == true){koPHOmFCok = false;}
      if(hIbojFqtow == true){hIbojFqtow = false;}
      if(SIrMNFBDrx == true){SIrMNFBDrx = false;}
      if(gCVzltRkJn == true){gCVzltRkJn = false;}
      if(pdPUzENUct == true){pdPUzENUct = false;}
      if(pDYAkcwCtI == true){pDYAkcwCtI = false;}
      if(lBJqDfmbDo == true){lBJqDfmbDo = false;}
      if(mGkAFnrXNI == true){mGkAFnrXNI = false;}
      if(rfZyGdcUOJ == true){rfZyGdcUOJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SUHEDFTDFH
{ 
  void ebYgyjZSIZ()
  { 
      bool ggKnpUIVWg = false;
      bool gFBdqcdGMf = false;
      bool NpYaezdwxj = false;
      bool heJkjFTdcl = false;
      bool GuuRasoWxJ = false;
      bool ujrHypHjIq = false;
      bool qLYlyCuPsl = false;
      bool JzdaYRuHzl = false;
      bool KHzmoylCms = false;
      bool xiUkuuWJTY = false;
      bool xYcLAuFRhf = false;
      bool uAjWgiLkxA = false;
      bool PsbAnZered = false;
      bool ukmZnkemms = false;
      bool rUTGxxyyEL = false;
      bool ikLTJExbXZ = false;
      bool QNlDkJMKiu = false;
      bool EXyEHuZUCp = false;
      bool agmSuKZTQi = false;
      bool nCPNbehPVm = false;
      string NjGnABhgix;
      string BPRndnfnZe;
      string CAMbhluImd;
      string MWGzGWMHJQ;
      string ztqyaiBTJx;
      string DKhGMMWdGO;
      string FYtEjeJSgG;
      string aYeJfIJOBy;
      string jazoZCoAls;
      string ziBuKZzlOw;
      string ZilDVefXaD;
      string CIcHddZEeg;
      string pJfnHrXiyG;
      string JXzEYBouSt;
      string WQYhppFsQf;
      string ztGgGQCyud;
      string HwZTteIXic;
      string odljKYjxxR;
      string mdRSHORSyH;
      string ypAomZqFmL;
      if(NjGnABhgix == ZilDVefXaD){ggKnpUIVWg = true;}
      else if(ZilDVefXaD == NjGnABhgix){xYcLAuFRhf = true;}
      if(BPRndnfnZe == CIcHddZEeg){gFBdqcdGMf = true;}
      else if(CIcHddZEeg == BPRndnfnZe){uAjWgiLkxA = true;}
      if(CAMbhluImd == pJfnHrXiyG){NpYaezdwxj = true;}
      else if(pJfnHrXiyG == CAMbhluImd){PsbAnZered = true;}
      if(MWGzGWMHJQ == JXzEYBouSt){heJkjFTdcl = true;}
      else if(JXzEYBouSt == MWGzGWMHJQ){ukmZnkemms = true;}
      if(ztqyaiBTJx == WQYhppFsQf){GuuRasoWxJ = true;}
      else if(WQYhppFsQf == ztqyaiBTJx){rUTGxxyyEL = true;}
      if(DKhGMMWdGO == ztGgGQCyud){ujrHypHjIq = true;}
      else if(ztGgGQCyud == DKhGMMWdGO){ikLTJExbXZ = true;}
      if(FYtEjeJSgG == HwZTteIXic){qLYlyCuPsl = true;}
      else if(HwZTteIXic == FYtEjeJSgG){QNlDkJMKiu = true;}
      if(aYeJfIJOBy == odljKYjxxR){JzdaYRuHzl = true;}
      if(jazoZCoAls == mdRSHORSyH){KHzmoylCms = true;}
      if(ziBuKZzlOw == ypAomZqFmL){xiUkuuWJTY = true;}
      while(odljKYjxxR == aYeJfIJOBy){EXyEHuZUCp = true;}
      while(mdRSHORSyH == mdRSHORSyH){agmSuKZTQi = true;}
      while(ypAomZqFmL == ypAomZqFmL){nCPNbehPVm = true;}
      if(ggKnpUIVWg == true){ggKnpUIVWg = false;}
      if(gFBdqcdGMf == true){gFBdqcdGMf = false;}
      if(NpYaezdwxj == true){NpYaezdwxj = false;}
      if(heJkjFTdcl == true){heJkjFTdcl = false;}
      if(GuuRasoWxJ == true){GuuRasoWxJ = false;}
      if(ujrHypHjIq == true){ujrHypHjIq = false;}
      if(qLYlyCuPsl == true){qLYlyCuPsl = false;}
      if(JzdaYRuHzl == true){JzdaYRuHzl = false;}
      if(KHzmoylCms == true){KHzmoylCms = false;}
      if(xiUkuuWJTY == true){xiUkuuWJTY = false;}
      if(xYcLAuFRhf == true){xYcLAuFRhf = false;}
      if(uAjWgiLkxA == true){uAjWgiLkxA = false;}
      if(PsbAnZered == true){PsbAnZered = false;}
      if(ukmZnkemms == true){ukmZnkemms = false;}
      if(rUTGxxyyEL == true){rUTGxxyyEL = false;}
      if(ikLTJExbXZ == true){ikLTJExbXZ = false;}
      if(QNlDkJMKiu == true){QNlDkJMKiu = false;}
      if(EXyEHuZUCp == true){EXyEHuZUCp = false;}
      if(agmSuKZTQi == true){agmSuKZTQi = false;}
      if(nCPNbehPVm == true){nCPNbehPVm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BIKTRJSVPV
{ 
  void TMJSsOmDCu()
  { 
      bool AzQfEZGbls = false;
      bool SCdtIJPJtM = false;
      bool zuykoMFbXr = false;
      bool FGfwpMVrVP = false;
      bool XWpxwxsKXU = false;
      bool dndKZEBeqr = false;
      bool TdDtnLWhDu = false;
      bool mXmencEBor = false;
      bool StDCNQbUWk = false;
      bool LqAdutSwIj = false;
      bool ZKHchGAzWw = false;
      bool zAoyYZaBfW = false;
      bool jBLRjuWJit = false;
      bool JIrFRHmaTH = false;
      bool PbyZlKBBEV = false;
      bool TRPlzXzorm = false;
      bool iqQcmqIjgR = false;
      bool lAgYGHDlfY = false;
      bool sUEMaqrFFt = false;
      bool IxhgXYLUmt = false;
      string FlVKplkrJq;
      string XyVFXdYxqi;
      string ZtUYxSJxKG;
      string HCoDLNMqmb;
      string YGJbEwooIm;
      string grRUELQwNX;
      string cngCjVIRtK;
      string QgJPKSjrUA;
      string cTnWZPjTzz;
      string wPdPyjYGrh;
      string mXuyVzhBKk;
      string aXbNtJAJcT;
      string koRtNBDtQZ;
      string scAmMFYoBZ;
      string hiJOXXnQVo;
      string jOdXwyFAjU;
      string wnkjqyXnAo;
      string jKIClCfDVp;
      string MmXaoeybpO;
      string zXEgdtxYWZ;
      if(FlVKplkrJq == mXuyVzhBKk){AzQfEZGbls = true;}
      else if(mXuyVzhBKk == FlVKplkrJq){ZKHchGAzWw = true;}
      if(XyVFXdYxqi == aXbNtJAJcT){SCdtIJPJtM = true;}
      else if(aXbNtJAJcT == XyVFXdYxqi){zAoyYZaBfW = true;}
      if(ZtUYxSJxKG == koRtNBDtQZ){zuykoMFbXr = true;}
      else if(koRtNBDtQZ == ZtUYxSJxKG){jBLRjuWJit = true;}
      if(HCoDLNMqmb == scAmMFYoBZ){FGfwpMVrVP = true;}
      else if(scAmMFYoBZ == HCoDLNMqmb){JIrFRHmaTH = true;}
      if(YGJbEwooIm == hiJOXXnQVo){XWpxwxsKXU = true;}
      else if(hiJOXXnQVo == YGJbEwooIm){PbyZlKBBEV = true;}
      if(grRUELQwNX == jOdXwyFAjU){dndKZEBeqr = true;}
      else if(jOdXwyFAjU == grRUELQwNX){TRPlzXzorm = true;}
      if(cngCjVIRtK == wnkjqyXnAo){TdDtnLWhDu = true;}
      else if(wnkjqyXnAo == cngCjVIRtK){iqQcmqIjgR = true;}
      if(QgJPKSjrUA == jKIClCfDVp){mXmencEBor = true;}
      if(cTnWZPjTzz == MmXaoeybpO){StDCNQbUWk = true;}
      if(wPdPyjYGrh == zXEgdtxYWZ){LqAdutSwIj = true;}
      while(jKIClCfDVp == QgJPKSjrUA){lAgYGHDlfY = true;}
      while(MmXaoeybpO == MmXaoeybpO){sUEMaqrFFt = true;}
      while(zXEgdtxYWZ == zXEgdtxYWZ){IxhgXYLUmt = true;}
      if(AzQfEZGbls == true){AzQfEZGbls = false;}
      if(SCdtIJPJtM == true){SCdtIJPJtM = false;}
      if(zuykoMFbXr == true){zuykoMFbXr = false;}
      if(FGfwpMVrVP == true){FGfwpMVrVP = false;}
      if(XWpxwxsKXU == true){XWpxwxsKXU = false;}
      if(dndKZEBeqr == true){dndKZEBeqr = false;}
      if(TdDtnLWhDu == true){TdDtnLWhDu = false;}
      if(mXmencEBor == true){mXmencEBor = false;}
      if(StDCNQbUWk == true){StDCNQbUWk = false;}
      if(LqAdutSwIj == true){LqAdutSwIj = false;}
      if(ZKHchGAzWw == true){ZKHchGAzWw = false;}
      if(zAoyYZaBfW == true){zAoyYZaBfW = false;}
      if(jBLRjuWJit == true){jBLRjuWJit = false;}
      if(JIrFRHmaTH == true){JIrFRHmaTH = false;}
      if(PbyZlKBBEV == true){PbyZlKBBEV = false;}
      if(TRPlzXzorm == true){TRPlzXzorm = false;}
      if(iqQcmqIjgR == true){iqQcmqIjgR = false;}
      if(lAgYGHDlfY == true){lAgYGHDlfY = false;}
      if(sUEMaqrFFt == true){sUEMaqrFFt = false;}
      if(IxhgXYLUmt == true){IxhgXYLUmt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WEHVADRKYZ
{ 
  void wlORYoFQdL()
  { 
      bool zNjnGcDSyn = false;
      bool XAsXOVrAwW = false;
      bool KSgdxgejrM = false;
      bool uhGdjUysys = false;
      bool tdtGMWzUhE = false;
      bool AdWxiffGqY = false;
      bool xSakspsPms = false;
      bool XzCCbgYaQZ = false;
      bool hKCmLQKItE = false;
      bool orBZwaDIMV = false;
      bool djgogAbUVC = false;
      bool GFoQplQmYb = false;
      bool fjUhDfycGA = false;
      bool cPNuwydMGL = false;
      bool opmryjCjiJ = false;
      bool KPijpsOykB = false;
      bool CzNUYpqsUr = false;
      bool IDgNmpwcjT = false;
      bool cNswpNfcFD = false;
      bool iebFIpbSSH = false;
      string YAECCusbak;
      string weyXRtfMwt;
      string wPQlDqLSkL;
      string ZNNpDDsYpx;
      string yByoFeALQV;
      string tnokxIjRzL;
      string iZpPLhQIUO;
      string AHVzutRafY;
      string qACPRkYbrt;
      string TbYeOYLidW;
      string NqqCVlRopD;
      string qIlZUhXaxZ;
      string InPatYhqjW;
      string iiwJKzIAse;
      string TiloCKpzJf;
      string AjkENZaQHx;
      string EZESUILbOU;
      string ZXgSFZBaXi;
      string iigEVyxruk;
      string XrrwZsdTTt;
      if(YAECCusbak == NqqCVlRopD){zNjnGcDSyn = true;}
      else if(NqqCVlRopD == YAECCusbak){djgogAbUVC = true;}
      if(weyXRtfMwt == qIlZUhXaxZ){XAsXOVrAwW = true;}
      else if(qIlZUhXaxZ == weyXRtfMwt){GFoQplQmYb = true;}
      if(wPQlDqLSkL == InPatYhqjW){KSgdxgejrM = true;}
      else if(InPatYhqjW == wPQlDqLSkL){fjUhDfycGA = true;}
      if(ZNNpDDsYpx == iiwJKzIAse){uhGdjUysys = true;}
      else if(iiwJKzIAse == ZNNpDDsYpx){cPNuwydMGL = true;}
      if(yByoFeALQV == TiloCKpzJf){tdtGMWzUhE = true;}
      else if(TiloCKpzJf == yByoFeALQV){opmryjCjiJ = true;}
      if(tnokxIjRzL == AjkENZaQHx){AdWxiffGqY = true;}
      else if(AjkENZaQHx == tnokxIjRzL){KPijpsOykB = true;}
      if(iZpPLhQIUO == EZESUILbOU){xSakspsPms = true;}
      else if(EZESUILbOU == iZpPLhQIUO){CzNUYpqsUr = true;}
      if(AHVzutRafY == ZXgSFZBaXi){XzCCbgYaQZ = true;}
      if(qACPRkYbrt == iigEVyxruk){hKCmLQKItE = true;}
      if(TbYeOYLidW == XrrwZsdTTt){orBZwaDIMV = true;}
      while(ZXgSFZBaXi == AHVzutRafY){IDgNmpwcjT = true;}
      while(iigEVyxruk == iigEVyxruk){cNswpNfcFD = true;}
      while(XrrwZsdTTt == XrrwZsdTTt){iebFIpbSSH = true;}
      if(zNjnGcDSyn == true){zNjnGcDSyn = false;}
      if(XAsXOVrAwW == true){XAsXOVrAwW = false;}
      if(KSgdxgejrM == true){KSgdxgejrM = false;}
      if(uhGdjUysys == true){uhGdjUysys = false;}
      if(tdtGMWzUhE == true){tdtGMWzUhE = false;}
      if(AdWxiffGqY == true){AdWxiffGqY = false;}
      if(xSakspsPms == true){xSakspsPms = false;}
      if(XzCCbgYaQZ == true){XzCCbgYaQZ = false;}
      if(hKCmLQKItE == true){hKCmLQKItE = false;}
      if(orBZwaDIMV == true){orBZwaDIMV = false;}
      if(djgogAbUVC == true){djgogAbUVC = false;}
      if(GFoQplQmYb == true){GFoQplQmYb = false;}
      if(fjUhDfycGA == true){fjUhDfycGA = false;}
      if(cPNuwydMGL == true){cPNuwydMGL = false;}
      if(opmryjCjiJ == true){opmryjCjiJ = false;}
      if(KPijpsOykB == true){KPijpsOykB = false;}
      if(CzNUYpqsUr == true){CzNUYpqsUr = false;}
      if(IDgNmpwcjT == true){IDgNmpwcjT = false;}
      if(cNswpNfcFD == true){cNswpNfcFD = false;}
      if(iebFIpbSSH == true){iebFIpbSSH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QHRLNYMPMW
{ 
  void YVVZiYmcCD()
  { 
      bool tFRqqdluBL = false;
      bool VqtYnijcJA = false;
      bool NJXTTbtXmC = false;
      bool JAikpaIeuS = false;
      bool uMmEHYrOxM = false;
      bool rVyIZjhxWP = false;
      bool iOIzCVHJhN = false;
      bool ZFgpEAWSMu = false;
      bool jeaZJnCaKG = false;
      bool sKIfjgEnCk = false;
      bool QigjmmnHDZ = false;
      bool NOkbfDmioO = false;
      bool TgzbTOxAFX = false;
      bool wiQadByqlW = false;
      bool ztWkreZfAg = false;
      bool sVynRijFPX = false;
      bool pmCfdexKxd = false;
      bool EwwSOZKNio = false;
      bool oQAYdZjcIu = false;
      bool QrbNgLrqGM = false;
      string iMYZRmlDSF;
      string FsrjAPBOWL;
      string SUWVJSLTmW;
      string AGtGhFWmHC;
      string KbOCqADDhm;
      string PLfQCOpDPy;
      string bRPwEyzlCt;
      string rNGUBpFTdJ;
      string PHlAHoacDS;
      string PSWJarLSxr;
      string AQBntBEKOM;
      string IVZGhTfPoP;
      string XVhieZqxtI;
      string dlWkIyFxGF;
      string jPNqKssPaG;
      string MwdgUehSJU;
      string JHQGhVznyj;
      string OiJieIIqYk;
      string faWmwhIoQd;
      string PlnkwcyHIn;
      if(iMYZRmlDSF == AQBntBEKOM){tFRqqdluBL = true;}
      else if(AQBntBEKOM == iMYZRmlDSF){QigjmmnHDZ = true;}
      if(FsrjAPBOWL == IVZGhTfPoP){VqtYnijcJA = true;}
      else if(IVZGhTfPoP == FsrjAPBOWL){NOkbfDmioO = true;}
      if(SUWVJSLTmW == XVhieZqxtI){NJXTTbtXmC = true;}
      else if(XVhieZqxtI == SUWVJSLTmW){TgzbTOxAFX = true;}
      if(AGtGhFWmHC == dlWkIyFxGF){JAikpaIeuS = true;}
      else if(dlWkIyFxGF == AGtGhFWmHC){wiQadByqlW = true;}
      if(KbOCqADDhm == jPNqKssPaG){uMmEHYrOxM = true;}
      else if(jPNqKssPaG == KbOCqADDhm){ztWkreZfAg = true;}
      if(PLfQCOpDPy == MwdgUehSJU){rVyIZjhxWP = true;}
      else if(MwdgUehSJU == PLfQCOpDPy){sVynRijFPX = true;}
      if(bRPwEyzlCt == JHQGhVznyj){iOIzCVHJhN = true;}
      else if(JHQGhVznyj == bRPwEyzlCt){pmCfdexKxd = true;}
      if(rNGUBpFTdJ == OiJieIIqYk){ZFgpEAWSMu = true;}
      if(PHlAHoacDS == faWmwhIoQd){jeaZJnCaKG = true;}
      if(PSWJarLSxr == PlnkwcyHIn){sKIfjgEnCk = true;}
      while(OiJieIIqYk == rNGUBpFTdJ){EwwSOZKNio = true;}
      while(faWmwhIoQd == faWmwhIoQd){oQAYdZjcIu = true;}
      while(PlnkwcyHIn == PlnkwcyHIn){QrbNgLrqGM = true;}
      if(tFRqqdluBL == true){tFRqqdluBL = false;}
      if(VqtYnijcJA == true){VqtYnijcJA = false;}
      if(NJXTTbtXmC == true){NJXTTbtXmC = false;}
      if(JAikpaIeuS == true){JAikpaIeuS = false;}
      if(uMmEHYrOxM == true){uMmEHYrOxM = false;}
      if(rVyIZjhxWP == true){rVyIZjhxWP = false;}
      if(iOIzCVHJhN == true){iOIzCVHJhN = false;}
      if(ZFgpEAWSMu == true){ZFgpEAWSMu = false;}
      if(jeaZJnCaKG == true){jeaZJnCaKG = false;}
      if(sKIfjgEnCk == true){sKIfjgEnCk = false;}
      if(QigjmmnHDZ == true){QigjmmnHDZ = false;}
      if(NOkbfDmioO == true){NOkbfDmioO = false;}
      if(TgzbTOxAFX == true){TgzbTOxAFX = false;}
      if(wiQadByqlW == true){wiQadByqlW = false;}
      if(ztWkreZfAg == true){ztWkreZfAg = false;}
      if(sVynRijFPX == true){sVynRijFPX = false;}
      if(pmCfdexKxd == true){pmCfdexKxd = false;}
      if(EwwSOZKNio == true){EwwSOZKNio = false;}
      if(oQAYdZjcIu == true){oQAYdZjcIu = false;}
      if(QrbNgLrqGM == true){QrbNgLrqGM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GRAHGWZXOB
{ 
  void RLnyoCfeUF()
  { 
      bool ptnzQdGyTb = false;
      bool QXsLusbwry = false;
      bool knKTJmUQLs = false;
      bool yFmaQKspYn = false;
      bool jYhNRImbOm = false;
      bool tqNQpBjTod = false;
      bool IolZcLjRtj = false;
      bool AkWDOLGxBA = false;
      bool zsCYyGrWjO = false;
      bool aYBtftmHjG = false;
      bool YUgdlJTJCe = false;
      bool umSndPmNaW = false;
      bool SNhfJbjbXT = false;
      bool YyMtbdMXlo = false;
      bool mhTFTmGMQP = false;
      bool HYfNmKmBUK = false;
      bool YqlhFwZXLA = false;
      bool DOaliksbMV = false;
      bool UWLHMzRzHQ = false;
      bool pLDbQuulAW = false;
      string mBWHlQlDop;
      string EQoqETLzHh;
      string FGAtdwCMGh;
      string BIGRqIXidx;
      string aPzbTOFlBu;
      string bQWYBfAbdo;
      string OZwHnwKXAu;
      string ucUJHpHYZP;
      string pQLKGjkhPK;
      string IwFoiBSrmX;
      string EhlFAywMRL;
      string YbBOzyNlAD;
      string KbHomzXeaF;
      string WPkCLHdFKH;
      string mYQElgtqpk;
      string mgqjNbaxRA;
      string aQlLnJpzCq;
      string TIasPkKDDG;
      string FgooSpXBoi;
      string ggmJgWmFPb;
      if(mBWHlQlDop == EhlFAywMRL){ptnzQdGyTb = true;}
      else if(EhlFAywMRL == mBWHlQlDop){YUgdlJTJCe = true;}
      if(EQoqETLzHh == YbBOzyNlAD){QXsLusbwry = true;}
      else if(YbBOzyNlAD == EQoqETLzHh){umSndPmNaW = true;}
      if(FGAtdwCMGh == KbHomzXeaF){knKTJmUQLs = true;}
      else if(KbHomzXeaF == FGAtdwCMGh){SNhfJbjbXT = true;}
      if(BIGRqIXidx == WPkCLHdFKH){yFmaQKspYn = true;}
      else if(WPkCLHdFKH == BIGRqIXidx){YyMtbdMXlo = true;}
      if(aPzbTOFlBu == mYQElgtqpk){jYhNRImbOm = true;}
      else if(mYQElgtqpk == aPzbTOFlBu){mhTFTmGMQP = true;}
      if(bQWYBfAbdo == mgqjNbaxRA){tqNQpBjTod = true;}
      else if(mgqjNbaxRA == bQWYBfAbdo){HYfNmKmBUK = true;}
      if(OZwHnwKXAu == aQlLnJpzCq){IolZcLjRtj = true;}
      else if(aQlLnJpzCq == OZwHnwKXAu){YqlhFwZXLA = true;}
      if(ucUJHpHYZP == TIasPkKDDG){AkWDOLGxBA = true;}
      if(pQLKGjkhPK == FgooSpXBoi){zsCYyGrWjO = true;}
      if(IwFoiBSrmX == ggmJgWmFPb){aYBtftmHjG = true;}
      while(TIasPkKDDG == ucUJHpHYZP){DOaliksbMV = true;}
      while(FgooSpXBoi == FgooSpXBoi){UWLHMzRzHQ = true;}
      while(ggmJgWmFPb == ggmJgWmFPb){pLDbQuulAW = true;}
      if(ptnzQdGyTb == true){ptnzQdGyTb = false;}
      if(QXsLusbwry == true){QXsLusbwry = false;}
      if(knKTJmUQLs == true){knKTJmUQLs = false;}
      if(yFmaQKspYn == true){yFmaQKspYn = false;}
      if(jYhNRImbOm == true){jYhNRImbOm = false;}
      if(tqNQpBjTod == true){tqNQpBjTod = false;}
      if(IolZcLjRtj == true){IolZcLjRtj = false;}
      if(AkWDOLGxBA == true){AkWDOLGxBA = false;}
      if(zsCYyGrWjO == true){zsCYyGrWjO = false;}
      if(aYBtftmHjG == true){aYBtftmHjG = false;}
      if(YUgdlJTJCe == true){YUgdlJTJCe = false;}
      if(umSndPmNaW == true){umSndPmNaW = false;}
      if(SNhfJbjbXT == true){SNhfJbjbXT = false;}
      if(YyMtbdMXlo == true){YyMtbdMXlo = false;}
      if(mhTFTmGMQP == true){mhTFTmGMQP = false;}
      if(HYfNmKmBUK == true){HYfNmKmBUK = false;}
      if(YqlhFwZXLA == true){YqlhFwZXLA = false;}
      if(DOaliksbMV == true){DOaliksbMV = false;}
      if(UWLHMzRzHQ == true){UWLHMzRzHQ = false;}
      if(pLDbQuulAW == true){pLDbQuulAW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZLZHMHWBY
{ 
  void rShxVYoFxV()
  { 
      bool TTKJnwhGfp = false;
      bool AkMhojGzNm = false;
      bool yqyUtmGuzq = false;
      bool AgIFMzKGEu = false;
      bool tyDGeZfZJi = false;
      bool qHxEnbUoPA = false;
      bool olHooTcHUp = false;
      bool YztRrAnroT = false;
      bool GfkQzsjDQk = false;
      bool dUqDGHqOQL = false;
      bool xYETJrMeLn = false;
      bool nbAusJAqow = false;
      bool iYqjLEHqLj = false;
      bool IYbcVhaRGH = false;
      bool fErbxCUwKx = false;
      bool HzZTbYhUHF = false;
      bool jVTaeOzWZL = false;
      bool hhjgPefOlJ = false;
      bool iLfOcJyIBw = false;
      bool AFKBWKkQxi = false;
      string rbwxILOUGH;
      string fRJUGeoEiE;
      string BLEJCRqMYG;
      string XWkZIArbHU;
      string BWPQLfbCxc;
      string yATLyfWmtq;
      string TCuziIgiMG;
      string mNwOCewnxW;
      string onOwIXDYbb;
      string dEhQAzaQgD;
      string zrpqpjDFIT;
      string jhoXBemzqK;
      string FHHjbhefND;
      string DeGtWwyXGX;
      string UyPHruOKOU;
      string LaZVxqkFOH;
      string EWqFPEbuAF;
      string gPsSoHqArf;
      string SUQrrcFjwe;
      string LsIySyGKqm;
      if(rbwxILOUGH == zrpqpjDFIT){TTKJnwhGfp = true;}
      else if(zrpqpjDFIT == rbwxILOUGH){xYETJrMeLn = true;}
      if(fRJUGeoEiE == jhoXBemzqK){AkMhojGzNm = true;}
      else if(jhoXBemzqK == fRJUGeoEiE){nbAusJAqow = true;}
      if(BLEJCRqMYG == FHHjbhefND){yqyUtmGuzq = true;}
      else if(FHHjbhefND == BLEJCRqMYG){iYqjLEHqLj = true;}
      if(XWkZIArbHU == DeGtWwyXGX){AgIFMzKGEu = true;}
      else if(DeGtWwyXGX == XWkZIArbHU){IYbcVhaRGH = true;}
      if(BWPQLfbCxc == UyPHruOKOU){tyDGeZfZJi = true;}
      else if(UyPHruOKOU == BWPQLfbCxc){fErbxCUwKx = true;}
      if(yATLyfWmtq == LaZVxqkFOH){qHxEnbUoPA = true;}
      else if(LaZVxqkFOH == yATLyfWmtq){HzZTbYhUHF = true;}
      if(TCuziIgiMG == EWqFPEbuAF){olHooTcHUp = true;}
      else if(EWqFPEbuAF == TCuziIgiMG){jVTaeOzWZL = true;}
      if(mNwOCewnxW == gPsSoHqArf){YztRrAnroT = true;}
      if(onOwIXDYbb == SUQrrcFjwe){GfkQzsjDQk = true;}
      if(dEhQAzaQgD == LsIySyGKqm){dUqDGHqOQL = true;}
      while(gPsSoHqArf == mNwOCewnxW){hhjgPefOlJ = true;}
      while(SUQrrcFjwe == SUQrrcFjwe){iLfOcJyIBw = true;}
      while(LsIySyGKqm == LsIySyGKqm){AFKBWKkQxi = true;}
      if(TTKJnwhGfp == true){TTKJnwhGfp = false;}
      if(AkMhojGzNm == true){AkMhojGzNm = false;}
      if(yqyUtmGuzq == true){yqyUtmGuzq = false;}
      if(AgIFMzKGEu == true){AgIFMzKGEu = false;}
      if(tyDGeZfZJi == true){tyDGeZfZJi = false;}
      if(qHxEnbUoPA == true){qHxEnbUoPA = false;}
      if(olHooTcHUp == true){olHooTcHUp = false;}
      if(YztRrAnroT == true){YztRrAnroT = false;}
      if(GfkQzsjDQk == true){GfkQzsjDQk = false;}
      if(dUqDGHqOQL == true){dUqDGHqOQL = false;}
      if(xYETJrMeLn == true){xYETJrMeLn = false;}
      if(nbAusJAqow == true){nbAusJAqow = false;}
      if(iYqjLEHqLj == true){iYqjLEHqLj = false;}
      if(IYbcVhaRGH == true){IYbcVhaRGH = false;}
      if(fErbxCUwKx == true){fErbxCUwKx = false;}
      if(HzZTbYhUHF == true){HzZTbYhUHF = false;}
      if(jVTaeOzWZL == true){jVTaeOzWZL = false;}
      if(hhjgPefOlJ == true){hhjgPefOlJ = false;}
      if(iLfOcJyIBw == true){iLfOcJyIBw = false;}
      if(AFKBWKkQxi == true){AFKBWKkQxi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FSGANMJEBL
{ 
  void qMPcUTQtrn()
  { 
      bool iMoDhnRJSp = false;
      bool qfWllRDkdL = false;
      bool RjxRfxOwIK = false;
      bool xocRJcHWiG = false;
      bool UAycaiGgHd = false;
      bool tXKBMzOXXj = false;
      bool YVAIsBDEbI = false;
      bool JgCXpRkUpw = false;
      bool phnePZeaFJ = false;
      bool NjyygzzpiZ = false;
      bool eCEzTNUmKu = false;
      bool OtgbsqgVrS = false;
      bool WbzRuZhEqq = false;
      bool StkQQndoLC = false;
      bool FqQJuTCWEo = false;
      bool RcyQCDClEs = false;
      bool eQwScTIQKE = false;
      bool NrKoNeLoWa = false;
      bool XLzBZowUNN = false;
      bool lqkRWouygb = false;
      string bbLbLpQJzB;
      string cxHJoylUiG;
      string GedzDaxcjs;
      string mXFGBeVUPa;
      string osgZUDVdUV;
      string BIjFExyLXk;
      string rnZFOFqBHK;
      string bREIQNyDeA;
      string FTIOremABE;
      string fJwehBSaKO;
      string MUVJsiDbnq;
      string ytgXfYfLNj;
      string RqzCeRUZZP;
      string tWsPnjxyUJ;
      string aLMJFkcYzJ;
      string VHNaxVUTea;
      string NdCXxaBQju;
      string agpDIGdows;
      string owaQtlJRSS;
      string PdStuxInMd;
      if(bbLbLpQJzB == MUVJsiDbnq){iMoDhnRJSp = true;}
      else if(MUVJsiDbnq == bbLbLpQJzB){eCEzTNUmKu = true;}
      if(cxHJoylUiG == ytgXfYfLNj){qfWllRDkdL = true;}
      else if(ytgXfYfLNj == cxHJoylUiG){OtgbsqgVrS = true;}
      if(GedzDaxcjs == RqzCeRUZZP){RjxRfxOwIK = true;}
      else if(RqzCeRUZZP == GedzDaxcjs){WbzRuZhEqq = true;}
      if(mXFGBeVUPa == tWsPnjxyUJ){xocRJcHWiG = true;}
      else if(tWsPnjxyUJ == mXFGBeVUPa){StkQQndoLC = true;}
      if(osgZUDVdUV == aLMJFkcYzJ){UAycaiGgHd = true;}
      else if(aLMJFkcYzJ == osgZUDVdUV){FqQJuTCWEo = true;}
      if(BIjFExyLXk == VHNaxVUTea){tXKBMzOXXj = true;}
      else if(VHNaxVUTea == BIjFExyLXk){RcyQCDClEs = true;}
      if(rnZFOFqBHK == NdCXxaBQju){YVAIsBDEbI = true;}
      else if(NdCXxaBQju == rnZFOFqBHK){eQwScTIQKE = true;}
      if(bREIQNyDeA == agpDIGdows){JgCXpRkUpw = true;}
      if(FTIOremABE == owaQtlJRSS){phnePZeaFJ = true;}
      if(fJwehBSaKO == PdStuxInMd){NjyygzzpiZ = true;}
      while(agpDIGdows == bREIQNyDeA){NrKoNeLoWa = true;}
      while(owaQtlJRSS == owaQtlJRSS){XLzBZowUNN = true;}
      while(PdStuxInMd == PdStuxInMd){lqkRWouygb = true;}
      if(iMoDhnRJSp == true){iMoDhnRJSp = false;}
      if(qfWllRDkdL == true){qfWllRDkdL = false;}
      if(RjxRfxOwIK == true){RjxRfxOwIK = false;}
      if(xocRJcHWiG == true){xocRJcHWiG = false;}
      if(UAycaiGgHd == true){UAycaiGgHd = false;}
      if(tXKBMzOXXj == true){tXKBMzOXXj = false;}
      if(YVAIsBDEbI == true){YVAIsBDEbI = false;}
      if(JgCXpRkUpw == true){JgCXpRkUpw = false;}
      if(phnePZeaFJ == true){phnePZeaFJ = false;}
      if(NjyygzzpiZ == true){NjyygzzpiZ = false;}
      if(eCEzTNUmKu == true){eCEzTNUmKu = false;}
      if(OtgbsqgVrS == true){OtgbsqgVrS = false;}
      if(WbzRuZhEqq == true){WbzRuZhEqq = false;}
      if(StkQQndoLC == true){StkQQndoLC = false;}
      if(FqQJuTCWEo == true){FqQJuTCWEo = false;}
      if(RcyQCDClEs == true){RcyQCDClEs = false;}
      if(eQwScTIQKE == true){eQwScTIQKE = false;}
      if(NrKoNeLoWa == true){NrKoNeLoWa = false;}
      if(XLzBZowUNN == true){XLzBZowUNN = false;}
      if(lqkRWouygb == true){lqkRWouygb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GGPNGGRXGX
{ 
  void hfKFqXzoHj()
  { 
      bool UrilBWJTkz = false;
      bool GKXwlGuqVW = false;
      bool ffMJAYAJBx = false;
      bool JDgIeIxcuF = false;
      bool ClagxEfZLP = false;
      bool tSfNsofZlb = false;
      bool VASmpCcPRd = false;
      bool JSwQUtEeMw = false;
      bool raxkCqXSOo = false;
      bool bWqSiCTnqt = false;
      bool aQIhGbVOsz = false;
      bool jBNpjuCgjz = false;
      bool eJAbBlbcgS = false;
      bool ZQmRUaSPda = false;
      bool UIZPFaIBin = false;
      bool zlDrPRQffU = false;
      bool zsgaYSNwUI = false;
      bool blCIeVijVZ = false;
      bool catrSnNuCD = false;
      bool KljJbaazql = false;
      string dOcsDCCPFr;
      string wUMIaboqIz;
      string PPiyfqEnHu;
      string ZSrqOWJlTP;
      string wWmhNwktMs;
      string TyHWHOfdMM;
      string yOIKRcbVtE;
      string SCWrCsbBjj;
      string GKaNbbLUiz;
      string qeYHRgNbPj;
      string TOAIaQaOTO;
      string mdscGmnuip;
      string QHltMmcPaV;
      string ezlAPqJRlK;
      string BxAUMMlwBd;
      string sSsZSMbFwn;
      string mKmyimrsMO;
      string cWIYnTGRhz;
      string BgOwbMGLgD;
      string OEVyWpJCkZ;
      if(dOcsDCCPFr == TOAIaQaOTO){UrilBWJTkz = true;}
      else if(TOAIaQaOTO == dOcsDCCPFr){aQIhGbVOsz = true;}
      if(wUMIaboqIz == mdscGmnuip){GKXwlGuqVW = true;}
      else if(mdscGmnuip == wUMIaboqIz){jBNpjuCgjz = true;}
      if(PPiyfqEnHu == QHltMmcPaV){ffMJAYAJBx = true;}
      else if(QHltMmcPaV == PPiyfqEnHu){eJAbBlbcgS = true;}
      if(ZSrqOWJlTP == ezlAPqJRlK){JDgIeIxcuF = true;}
      else if(ezlAPqJRlK == ZSrqOWJlTP){ZQmRUaSPda = true;}
      if(wWmhNwktMs == BxAUMMlwBd){ClagxEfZLP = true;}
      else if(BxAUMMlwBd == wWmhNwktMs){UIZPFaIBin = true;}
      if(TyHWHOfdMM == sSsZSMbFwn){tSfNsofZlb = true;}
      else if(sSsZSMbFwn == TyHWHOfdMM){zlDrPRQffU = true;}
      if(yOIKRcbVtE == mKmyimrsMO){VASmpCcPRd = true;}
      else if(mKmyimrsMO == yOIKRcbVtE){zsgaYSNwUI = true;}
      if(SCWrCsbBjj == cWIYnTGRhz){JSwQUtEeMw = true;}
      if(GKaNbbLUiz == BgOwbMGLgD){raxkCqXSOo = true;}
      if(qeYHRgNbPj == OEVyWpJCkZ){bWqSiCTnqt = true;}
      while(cWIYnTGRhz == SCWrCsbBjj){blCIeVijVZ = true;}
      while(BgOwbMGLgD == BgOwbMGLgD){catrSnNuCD = true;}
      while(OEVyWpJCkZ == OEVyWpJCkZ){KljJbaazql = true;}
      if(UrilBWJTkz == true){UrilBWJTkz = false;}
      if(GKXwlGuqVW == true){GKXwlGuqVW = false;}
      if(ffMJAYAJBx == true){ffMJAYAJBx = false;}
      if(JDgIeIxcuF == true){JDgIeIxcuF = false;}
      if(ClagxEfZLP == true){ClagxEfZLP = false;}
      if(tSfNsofZlb == true){tSfNsofZlb = false;}
      if(VASmpCcPRd == true){VASmpCcPRd = false;}
      if(JSwQUtEeMw == true){JSwQUtEeMw = false;}
      if(raxkCqXSOo == true){raxkCqXSOo = false;}
      if(bWqSiCTnqt == true){bWqSiCTnqt = false;}
      if(aQIhGbVOsz == true){aQIhGbVOsz = false;}
      if(jBNpjuCgjz == true){jBNpjuCgjz = false;}
      if(eJAbBlbcgS == true){eJAbBlbcgS = false;}
      if(ZQmRUaSPda == true){ZQmRUaSPda = false;}
      if(UIZPFaIBin == true){UIZPFaIBin = false;}
      if(zlDrPRQffU == true){zlDrPRQffU = false;}
      if(zsgaYSNwUI == true){zsgaYSNwUI = false;}
      if(blCIeVijVZ == true){blCIeVijVZ = false;}
      if(catrSnNuCD == true){catrSnNuCD = false;}
      if(KljJbaazql == true){KljJbaazql = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUXVVYPSRW
{ 
  void ImednYlfoW()
  { 
      bool ycghXmwgMy = false;
      bool jIpbIemaqk = false;
      bool iseFDjwTAW = false;
      bool leEcFudIHU = false;
      bool leLBUKeRsb = false;
      bool MQSNxEyaem = false;
      bool qcfoLFEMWN = false;
      bool BeSVzEhdjs = false;
      bool FeZXJVLqeA = false;
      bool xCdUdJyVpP = false;
      bool FRtfahxxNs = false;
      bool WTqkhLCIfo = false;
      bool sMhWPzAyqo = false;
      bool FLnTmmjsxa = false;
      bool XOckccLrlR = false;
      bool GopAWrjXQb = false;
      bool gyFXmLfWxu = false;
      bool aJLEQdjwsl = false;
      bool mILYiPUmwt = false;
      bool CMcVsYJEyR = false;
      string VtTRTkePNd;
      string jFtVSAOTyQ;
      string CgceWFCnKS;
      string arLiLHDdSl;
      string kdnlxSsuML;
      string dYcQtoQnuN;
      string hqFtCrsKJL;
      string wkAMeYsqgE;
      string MHazoCOunW;
      string pOiFDsXsiF;
      string YhlBOrYPkU;
      string uZGpAaPFEA;
      string cyWlUgCuIl;
      string AAHbedUZjx;
      string dyJSbQIrEc;
      string cRnibZLzfh;
      string odGzTuReLV;
      string FpVHWdoDJD;
      string YKpfIiLXzF;
      string SUsCHArJyg;
      if(VtTRTkePNd == YhlBOrYPkU){ycghXmwgMy = true;}
      else if(YhlBOrYPkU == VtTRTkePNd){FRtfahxxNs = true;}
      if(jFtVSAOTyQ == uZGpAaPFEA){jIpbIemaqk = true;}
      else if(uZGpAaPFEA == jFtVSAOTyQ){WTqkhLCIfo = true;}
      if(CgceWFCnKS == cyWlUgCuIl){iseFDjwTAW = true;}
      else if(cyWlUgCuIl == CgceWFCnKS){sMhWPzAyqo = true;}
      if(arLiLHDdSl == AAHbedUZjx){leEcFudIHU = true;}
      else if(AAHbedUZjx == arLiLHDdSl){FLnTmmjsxa = true;}
      if(kdnlxSsuML == dyJSbQIrEc){leLBUKeRsb = true;}
      else if(dyJSbQIrEc == kdnlxSsuML){XOckccLrlR = true;}
      if(dYcQtoQnuN == cRnibZLzfh){MQSNxEyaem = true;}
      else if(cRnibZLzfh == dYcQtoQnuN){GopAWrjXQb = true;}
      if(hqFtCrsKJL == odGzTuReLV){qcfoLFEMWN = true;}
      else if(odGzTuReLV == hqFtCrsKJL){gyFXmLfWxu = true;}
      if(wkAMeYsqgE == FpVHWdoDJD){BeSVzEhdjs = true;}
      if(MHazoCOunW == YKpfIiLXzF){FeZXJVLqeA = true;}
      if(pOiFDsXsiF == SUsCHArJyg){xCdUdJyVpP = true;}
      while(FpVHWdoDJD == wkAMeYsqgE){aJLEQdjwsl = true;}
      while(YKpfIiLXzF == YKpfIiLXzF){mILYiPUmwt = true;}
      while(SUsCHArJyg == SUsCHArJyg){CMcVsYJEyR = true;}
      if(ycghXmwgMy == true){ycghXmwgMy = false;}
      if(jIpbIemaqk == true){jIpbIemaqk = false;}
      if(iseFDjwTAW == true){iseFDjwTAW = false;}
      if(leEcFudIHU == true){leEcFudIHU = false;}
      if(leLBUKeRsb == true){leLBUKeRsb = false;}
      if(MQSNxEyaem == true){MQSNxEyaem = false;}
      if(qcfoLFEMWN == true){qcfoLFEMWN = false;}
      if(BeSVzEhdjs == true){BeSVzEhdjs = false;}
      if(FeZXJVLqeA == true){FeZXJVLqeA = false;}
      if(xCdUdJyVpP == true){xCdUdJyVpP = false;}
      if(FRtfahxxNs == true){FRtfahxxNs = false;}
      if(WTqkhLCIfo == true){WTqkhLCIfo = false;}
      if(sMhWPzAyqo == true){sMhWPzAyqo = false;}
      if(FLnTmmjsxa == true){FLnTmmjsxa = false;}
      if(XOckccLrlR == true){XOckccLrlR = false;}
      if(GopAWrjXQb == true){GopAWrjXQb = false;}
      if(gyFXmLfWxu == true){gyFXmLfWxu = false;}
      if(aJLEQdjwsl == true){aJLEQdjwsl = false;}
      if(mILYiPUmwt == true){mILYiPUmwt = false;}
      if(CMcVsYJEyR == true){CMcVsYJEyR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HBLRRVUDFJ
{ 
  void UCyQROytAN()
  { 
      bool IrsTadJiFz = false;
      bool HIHKImpRiT = false;
      bool bgFYYGkpci = false;
      bool jPdZqoyenX = false;
      bool lBhYnGliUe = false;
      bool SaYqIblTtU = false;
      bool rTFWOrehSS = false;
      bool nKcKhZzgkR = false;
      bool UBUyQJplQP = false;
      bool CdjTfSuLJu = false;
      bool bDQBpHxOJi = false;
      bool bFibApyHGF = false;
      bool BrRCQJaJeO = false;
      bool dnWopQkTII = false;
      bool LacgmwuHTo = false;
      bool UnFDsilNkf = false;
      bool gnjtEnhskj = false;
      bool FdzxsaOjPT = false;
      bool OSpptpiTuH = false;
      bool dXibbXqhcy = false;
      string mhYotqXACn;
      string OzZQbHlsTb;
      string xbBQYUrtDe;
      string CJrsjPGYfm;
      string WKrakDtGBs;
      string yHHBbLgIQZ;
      string ycwWkFHggM;
      string BNMgEmjaeV;
      string ZlsKftBpQY;
      string iyIGnsOUof;
      string uNZnrjuawo;
      string bFctzMjkqq;
      string DQQHdCFFrL;
      string YOkzZLLESw;
      string yasaxcVNGb;
      string JcdybexRKo;
      string eohkPMUcUm;
      string AeStrcXoKA;
      string gryPCwkmXu;
      string OttcRJrIKk;
      if(mhYotqXACn == uNZnrjuawo){IrsTadJiFz = true;}
      else if(uNZnrjuawo == mhYotqXACn){bDQBpHxOJi = true;}
      if(OzZQbHlsTb == bFctzMjkqq){HIHKImpRiT = true;}
      else if(bFctzMjkqq == OzZQbHlsTb){bFibApyHGF = true;}
      if(xbBQYUrtDe == DQQHdCFFrL){bgFYYGkpci = true;}
      else if(DQQHdCFFrL == xbBQYUrtDe){BrRCQJaJeO = true;}
      if(CJrsjPGYfm == YOkzZLLESw){jPdZqoyenX = true;}
      else if(YOkzZLLESw == CJrsjPGYfm){dnWopQkTII = true;}
      if(WKrakDtGBs == yasaxcVNGb){lBhYnGliUe = true;}
      else if(yasaxcVNGb == WKrakDtGBs){LacgmwuHTo = true;}
      if(yHHBbLgIQZ == JcdybexRKo){SaYqIblTtU = true;}
      else if(JcdybexRKo == yHHBbLgIQZ){UnFDsilNkf = true;}
      if(ycwWkFHggM == eohkPMUcUm){rTFWOrehSS = true;}
      else if(eohkPMUcUm == ycwWkFHggM){gnjtEnhskj = true;}
      if(BNMgEmjaeV == AeStrcXoKA){nKcKhZzgkR = true;}
      if(ZlsKftBpQY == gryPCwkmXu){UBUyQJplQP = true;}
      if(iyIGnsOUof == OttcRJrIKk){CdjTfSuLJu = true;}
      while(AeStrcXoKA == BNMgEmjaeV){FdzxsaOjPT = true;}
      while(gryPCwkmXu == gryPCwkmXu){OSpptpiTuH = true;}
      while(OttcRJrIKk == OttcRJrIKk){dXibbXqhcy = true;}
      if(IrsTadJiFz == true){IrsTadJiFz = false;}
      if(HIHKImpRiT == true){HIHKImpRiT = false;}
      if(bgFYYGkpci == true){bgFYYGkpci = false;}
      if(jPdZqoyenX == true){jPdZqoyenX = false;}
      if(lBhYnGliUe == true){lBhYnGliUe = false;}
      if(SaYqIblTtU == true){SaYqIblTtU = false;}
      if(rTFWOrehSS == true){rTFWOrehSS = false;}
      if(nKcKhZzgkR == true){nKcKhZzgkR = false;}
      if(UBUyQJplQP == true){UBUyQJplQP = false;}
      if(CdjTfSuLJu == true){CdjTfSuLJu = false;}
      if(bDQBpHxOJi == true){bDQBpHxOJi = false;}
      if(bFibApyHGF == true){bFibApyHGF = false;}
      if(BrRCQJaJeO == true){BrRCQJaJeO = false;}
      if(dnWopQkTII == true){dnWopQkTII = false;}
      if(LacgmwuHTo == true){LacgmwuHTo = false;}
      if(UnFDsilNkf == true){UnFDsilNkf = false;}
      if(gnjtEnhskj == true){gnjtEnhskj = false;}
      if(FdzxsaOjPT == true){FdzxsaOjPT = false;}
      if(OSpptpiTuH == true){OSpptpiTuH = false;}
      if(dXibbXqhcy == true){dXibbXqhcy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QEQTXQJIPO
{ 
  void AtrLlkkXnX()
  { 
      bool SMjNaCpqsx = false;
      bool BjqmMgGysd = false;
      bool NwOhEtKZJC = false;
      bool AEcSrQjzeV = false;
      bool CtghqpOTMm = false;
      bool auBGGVxBJf = false;
      bool qPhqxxHXtw = false;
      bool wGTWaTOgpO = false;
      bool eqNVaFCVMW = false;
      bool SipzdmLpkt = false;
      bool hqYPpUaefm = false;
      bool GQKtAABLPq = false;
      bool tlKXcNPUrn = false;
      bool HYwwfnRyfG = false;
      bool dXpYPCXwyd = false;
      bool kAZszwfAlb = false;
      bool EGlqfhTOOM = false;
      bool hDfJMWulIa = false;
      bool pTVOCHyDwj = false;
      bool HQLDBXkysh = false;
      string YqxazsCqyW;
      string tCtfgSTBRJ;
      string CtwUAAkYiw;
      string IRUJBNEHwV;
      string WNUcMtGPSp;
      string sehxtdubay;
      string HdHBNbhkdT;
      string NMEulnYSIF;
      string tVFrCcjWOX;
      string RbgxNsFTOj;
      string LUkzbgalKG;
      string EbTUElXPyk;
      string rLWGBlfGhs;
      string iFEXsYkFPV;
      string ByLISpILsb;
      string UpUcrAydyp;
      string BTERWyXuae;
      string BSzcjtzNmK;
      string dTNFXskafs;
      string aGHYTgstkT;
      if(YqxazsCqyW == LUkzbgalKG){SMjNaCpqsx = true;}
      else if(LUkzbgalKG == YqxazsCqyW){hqYPpUaefm = true;}
      if(tCtfgSTBRJ == EbTUElXPyk){BjqmMgGysd = true;}
      else if(EbTUElXPyk == tCtfgSTBRJ){GQKtAABLPq = true;}
      if(CtwUAAkYiw == rLWGBlfGhs){NwOhEtKZJC = true;}
      else if(rLWGBlfGhs == CtwUAAkYiw){tlKXcNPUrn = true;}
      if(IRUJBNEHwV == iFEXsYkFPV){AEcSrQjzeV = true;}
      else if(iFEXsYkFPV == IRUJBNEHwV){HYwwfnRyfG = true;}
      if(WNUcMtGPSp == ByLISpILsb){CtghqpOTMm = true;}
      else if(ByLISpILsb == WNUcMtGPSp){dXpYPCXwyd = true;}
      if(sehxtdubay == UpUcrAydyp){auBGGVxBJf = true;}
      else if(UpUcrAydyp == sehxtdubay){kAZszwfAlb = true;}
      if(HdHBNbhkdT == BTERWyXuae){qPhqxxHXtw = true;}
      else if(BTERWyXuae == HdHBNbhkdT){EGlqfhTOOM = true;}
      if(NMEulnYSIF == BSzcjtzNmK){wGTWaTOgpO = true;}
      if(tVFrCcjWOX == dTNFXskafs){eqNVaFCVMW = true;}
      if(RbgxNsFTOj == aGHYTgstkT){SipzdmLpkt = true;}
      while(BSzcjtzNmK == NMEulnYSIF){hDfJMWulIa = true;}
      while(dTNFXskafs == dTNFXskafs){pTVOCHyDwj = true;}
      while(aGHYTgstkT == aGHYTgstkT){HQLDBXkysh = true;}
      if(SMjNaCpqsx == true){SMjNaCpqsx = false;}
      if(BjqmMgGysd == true){BjqmMgGysd = false;}
      if(NwOhEtKZJC == true){NwOhEtKZJC = false;}
      if(AEcSrQjzeV == true){AEcSrQjzeV = false;}
      if(CtghqpOTMm == true){CtghqpOTMm = false;}
      if(auBGGVxBJf == true){auBGGVxBJf = false;}
      if(qPhqxxHXtw == true){qPhqxxHXtw = false;}
      if(wGTWaTOgpO == true){wGTWaTOgpO = false;}
      if(eqNVaFCVMW == true){eqNVaFCVMW = false;}
      if(SipzdmLpkt == true){SipzdmLpkt = false;}
      if(hqYPpUaefm == true){hqYPpUaefm = false;}
      if(GQKtAABLPq == true){GQKtAABLPq = false;}
      if(tlKXcNPUrn == true){tlKXcNPUrn = false;}
      if(HYwwfnRyfG == true){HYwwfnRyfG = false;}
      if(dXpYPCXwyd == true){dXpYPCXwyd = false;}
      if(kAZszwfAlb == true){kAZszwfAlb = false;}
      if(EGlqfhTOOM == true){EGlqfhTOOM = false;}
      if(hDfJMWulIa == true){hDfJMWulIa = false;}
      if(pTVOCHyDwj == true){pTVOCHyDwj = false;}
      if(HQLDBXkysh == true){HQLDBXkysh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NJCOMAXUZR
{ 
  void ZgTEHJpESY()
  { 
      bool rWTnYsRzjL = false;
      bool IcmLHfMoLx = false;
      bool TlERLpYfGh = false;
      bool ObtHfNNJVj = false;
      bool cBXYFKLanQ = false;
      bool ukIyHFRCbh = false;
      bool TksBxgheet = false;
      bool SCTaUSOfLB = false;
      bool dxqpmcSwzZ = false;
      bool uLhnPqIVbY = false;
      bool cgusyrRgco = false;
      bool qlpaDWtCNT = false;
      bool NkeFzGUfLd = false;
      bool KrDlXxCyqt = false;
      bool KkTKiJVHjs = false;
      bool xFIHLqBptr = false;
      bool WlVzdziDCG = false;
      bool TwKTJbRUWp = false;
      bool jNuRgFjuag = false;
      bool wMDzWXOTfi = false;
      string SfeCIUlIRa;
      string zGrZhDOmyI;
      string ETjIXxhlLq;
      string xnVuVJNeFM;
      string nGtPPtsISf;
      string gffqczwWdK;
      string lAwZdKjwDX;
      string ojgkUxYUrc;
      string EZSfJRHeSW;
      string NqAuamJTlE;
      string JxEupxyuVe;
      string ZbdAGLhQQL;
      string CFdgKyilKg;
      string mEhmTGVWoL;
      string TMImxlNAnO;
      string EsDaCESWjr;
      string OLknqUspgz;
      string oLbEqpwpjY;
      string jhyuctAHkO;
      string mzlwxIaTub;
      if(SfeCIUlIRa == JxEupxyuVe){rWTnYsRzjL = true;}
      else if(JxEupxyuVe == SfeCIUlIRa){cgusyrRgco = true;}
      if(zGrZhDOmyI == ZbdAGLhQQL){IcmLHfMoLx = true;}
      else if(ZbdAGLhQQL == zGrZhDOmyI){qlpaDWtCNT = true;}
      if(ETjIXxhlLq == CFdgKyilKg){TlERLpYfGh = true;}
      else if(CFdgKyilKg == ETjIXxhlLq){NkeFzGUfLd = true;}
      if(xnVuVJNeFM == mEhmTGVWoL){ObtHfNNJVj = true;}
      else if(mEhmTGVWoL == xnVuVJNeFM){KrDlXxCyqt = true;}
      if(nGtPPtsISf == TMImxlNAnO){cBXYFKLanQ = true;}
      else if(TMImxlNAnO == nGtPPtsISf){KkTKiJVHjs = true;}
      if(gffqczwWdK == EsDaCESWjr){ukIyHFRCbh = true;}
      else if(EsDaCESWjr == gffqczwWdK){xFIHLqBptr = true;}
      if(lAwZdKjwDX == OLknqUspgz){TksBxgheet = true;}
      else if(OLknqUspgz == lAwZdKjwDX){WlVzdziDCG = true;}
      if(ojgkUxYUrc == oLbEqpwpjY){SCTaUSOfLB = true;}
      if(EZSfJRHeSW == jhyuctAHkO){dxqpmcSwzZ = true;}
      if(NqAuamJTlE == mzlwxIaTub){uLhnPqIVbY = true;}
      while(oLbEqpwpjY == ojgkUxYUrc){TwKTJbRUWp = true;}
      while(jhyuctAHkO == jhyuctAHkO){jNuRgFjuag = true;}
      while(mzlwxIaTub == mzlwxIaTub){wMDzWXOTfi = true;}
      if(rWTnYsRzjL == true){rWTnYsRzjL = false;}
      if(IcmLHfMoLx == true){IcmLHfMoLx = false;}
      if(TlERLpYfGh == true){TlERLpYfGh = false;}
      if(ObtHfNNJVj == true){ObtHfNNJVj = false;}
      if(cBXYFKLanQ == true){cBXYFKLanQ = false;}
      if(ukIyHFRCbh == true){ukIyHFRCbh = false;}
      if(TksBxgheet == true){TksBxgheet = false;}
      if(SCTaUSOfLB == true){SCTaUSOfLB = false;}
      if(dxqpmcSwzZ == true){dxqpmcSwzZ = false;}
      if(uLhnPqIVbY == true){uLhnPqIVbY = false;}
      if(cgusyrRgco == true){cgusyrRgco = false;}
      if(qlpaDWtCNT == true){qlpaDWtCNT = false;}
      if(NkeFzGUfLd == true){NkeFzGUfLd = false;}
      if(KrDlXxCyqt == true){KrDlXxCyqt = false;}
      if(KkTKiJVHjs == true){KkTKiJVHjs = false;}
      if(xFIHLqBptr == true){xFIHLqBptr = false;}
      if(WlVzdziDCG == true){WlVzdziDCG = false;}
      if(TwKTJbRUWp == true){TwKTJbRUWp = false;}
      if(jNuRgFjuag == true){jNuRgFjuag = false;}
      if(wMDzWXOTfi == true){wMDzWXOTfi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKQIYUGNVF
{ 
  void JhmHGXaYyw()
  { 
      bool VjPLUXjXnY = false;
      bool jglBIlDorH = false;
      bool QBOmFroTfc = false;
      bool inROrXuPEj = false;
      bool KaoTmYODdE = false;
      bool nyoelTUbGc = false;
      bool iPrLowOWJj = false;
      bool pnjHwpLuzf = false;
      bool dkoaokymcX = false;
      bool CSJbBthddp = false;
      bool JqtsNzNghw = false;
      bool IYcZyxaRVE = false;
      bool ybtkhXeHGC = false;
      bool HhRIWmqwMp = false;
      bool WQEfPdoicD = false;
      bool TQHYrgwILo = false;
      bool TFafnZHTCL = false;
      bool GdEfhgXOVD = false;
      bool hueChqarPo = false;
      bool qhjWVQoXrp = false;
      string gkAlAnZpYq;
      string mNUuDUmYDK;
      string HafBLYwJQx;
      string zIyyhWkoAD;
      string zXerwXBCKz;
      string dADmWFFzaa;
      string qPZbqdOVNf;
      string jyXAKiwnFm;
      string XtzQSzFKbb;
      string RkNZLiyCAS;
      string JfodOfcDcm;
      string JRtnDxQIIq;
      string XDskNzjxnb;
      string ksmlcrEVCl;
      string WChoSAqZWN;
      string SptJtFlEPP;
      string weOACPeHKL;
      string stGVUVUERN;
      string HKaZItzcrX;
      string FAFlpqmglD;
      if(gkAlAnZpYq == JfodOfcDcm){VjPLUXjXnY = true;}
      else if(JfodOfcDcm == gkAlAnZpYq){JqtsNzNghw = true;}
      if(mNUuDUmYDK == JRtnDxQIIq){jglBIlDorH = true;}
      else if(JRtnDxQIIq == mNUuDUmYDK){IYcZyxaRVE = true;}
      if(HafBLYwJQx == XDskNzjxnb){QBOmFroTfc = true;}
      else if(XDskNzjxnb == HafBLYwJQx){ybtkhXeHGC = true;}
      if(zIyyhWkoAD == ksmlcrEVCl){inROrXuPEj = true;}
      else if(ksmlcrEVCl == zIyyhWkoAD){HhRIWmqwMp = true;}
      if(zXerwXBCKz == WChoSAqZWN){KaoTmYODdE = true;}
      else if(WChoSAqZWN == zXerwXBCKz){WQEfPdoicD = true;}
      if(dADmWFFzaa == SptJtFlEPP){nyoelTUbGc = true;}
      else if(SptJtFlEPP == dADmWFFzaa){TQHYrgwILo = true;}
      if(qPZbqdOVNf == weOACPeHKL){iPrLowOWJj = true;}
      else if(weOACPeHKL == qPZbqdOVNf){TFafnZHTCL = true;}
      if(jyXAKiwnFm == stGVUVUERN){pnjHwpLuzf = true;}
      if(XtzQSzFKbb == HKaZItzcrX){dkoaokymcX = true;}
      if(RkNZLiyCAS == FAFlpqmglD){CSJbBthddp = true;}
      while(stGVUVUERN == jyXAKiwnFm){GdEfhgXOVD = true;}
      while(HKaZItzcrX == HKaZItzcrX){hueChqarPo = true;}
      while(FAFlpqmglD == FAFlpqmglD){qhjWVQoXrp = true;}
      if(VjPLUXjXnY == true){VjPLUXjXnY = false;}
      if(jglBIlDorH == true){jglBIlDorH = false;}
      if(QBOmFroTfc == true){QBOmFroTfc = false;}
      if(inROrXuPEj == true){inROrXuPEj = false;}
      if(KaoTmYODdE == true){KaoTmYODdE = false;}
      if(nyoelTUbGc == true){nyoelTUbGc = false;}
      if(iPrLowOWJj == true){iPrLowOWJj = false;}
      if(pnjHwpLuzf == true){pnjHwpLuzf = false;}
      if(dkoaokymcX == true){dkoaokymcX = false;}
      if(CSJbBthddp == true){CSJbBthddp = false;}
      if(JqtsNzNghw == true){JqtsNzNghw = false;}
      if(IYcZyxaRVE == true){IYcZyxaRVE = false;}
      if(ybtkhXeHGC == true){ybtkhXeHGC = false;}
      if(HhRIWmqwMp == true){HhRIWmqwMp = false;}
      if(WQEfPdoicD == true){WQEfPdoicD = false;}
      if(TQHYrgwILo == true){TQHYrgwILo = false;}
      if(TFafnZHTCL == true){TFafnZHTCL = false;}
      if(GdEfhgXOVD == true){GdEfhgXOVD = false;}
      if(hueChqarPo == true){hueChqarPo = false;}
      if(qhjWVQoXrp == true){qhjWVQoXrp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZBNRIUBEGD
{ 
  void DcAQAqXadf()
  { 
      bool EVogwiLHYy = false;
      bool uoGNQRQgMu = false;
      bool nGHpHRugUE = false;
      bool oxTRArilXf = false;
      bool VAnhNhWMpU = false;
      bool pEwMqyOzYe = false;
      bool mdlUJyVoMX = false;
      bool hdIfYnSYcY = false;
      bool thpANjBGaC = false;
      bool ciNsrrOSXO = false;
      bool MhzSlLuPmD = false;
      bool foWzkFmlGZ = false;
      bool xOOKtzQPng = false;
      bool ZzBNMMhXNC = false;
      bool okTXWmMNIm = false;
      bool EbMyRyTnXm = false;
      bool tfbGdfnImX = false;
      bool WOYEkLtpnH = false;
      bool lDHAbxlDuN = false;
      bool stAZHIJNtp = false;
      string dhnjcIuoIr;
      string UgOPEVZXyz;
      string ykgzUuRwXs;
      string hCJJqnrNNO;
      string PqNxFPfDKg;
      string OazdQrAnOh;
      string qzQOKRWEYQ;
      string cLKjiGWjtE;
      string ONlpeHDesy;
      string nEzeWQZzmn;
      string saetECPPtJ;
      string UPtKSdMajC;
      string OqKabYMeNS;
      string gXxFKmhrlb;
      string qnkjcXKnLr;
      string DzPjYCPERe;
      string ojCbbxSnze;
      string uUnHLaGaxE;
      string OXSUOgIMgI;
      string XdZGlHkIHf;
      if(dhnjcIuoIr == saetECPPtJ){EVogwiLHYy = true;}
      else if(saetECPPtJ == dhnjcIuoIr){MhzSlLuPmD = true;}
      if(UgOPEVZXyz == UPtKSdMajC){uoGNQRQgMu = true;}
      else if(UPtKSdMajC == UgOPEVZXyz){foWzkFmlGZ = true;}
      if(ykgzUuRwXs == OqKabYMeNS){nGHpHRugUE = true;}
      else if(OqKabYMeNS == ykgzUuRwXs){xOOKtzQPng = true;}
      if(hCJJqnrNNO == gXxFKmhrlb){oxTRArilXf = true;}
      else if(gXxFKmhrlb == hCJJqnrNNO){ZzBNMMhXNC = true;}
      if(PqNxFPfDKg == qnkjcXKnLr){VAnhNhWMpU = true;}
      else if(qnkjcXKnLr == PqNxFPfDKg){okTXWmMNIm = true;}
      if(OazdQrAnOh == DzPjYCPERe){pEwMqyOzYe = true;}
      else if(DzPjYCPERe == OazdQrAnOh){EbMyRyTnXm = true;}
      if(qzQOKRWEYQ == ojCbbxSnze){mdlUJyVoMX = true;}
      else if(ojCbbxSnze == qzQOKRWEYQ){tfbGdfnImX = true;}
      if(cLKjiGWjtE == uUnHLaGaxE){hdIfYnSYcY = true;}
      if(ONlpeHDesy == OXSUOgIMgI){thpANjBGaC = true;}
      if(nEzeWQZzmn == XdZGlHkIHf){ciNsrrOSXO = true;}
      while(uUnHLaGaxE == cLKjiGWjtE){WOYEkLtpnH = true;}
      while(OXSUOgIMgI == OXSUOgIMgI){lDHAbxlDuN = true;}
      while(XdZGlHkIHf == XdZGlHkIHf){stAZHIJNtp = true;}
      if(EVogwiLHYy == true){EVogwiLHYy = false;}
      if(uoGNQRQgMu == true){uoGNQRQgMu = false;}
      if(nGHpHRugUE == true){nGHpHRugUE = false;}
      if(oxTRArilXf == true){oxTRArilXf = false;}
      if(VAnhNhWMpU == true){VAnhNhWMpU = false;}
      if(pEwMqyOzYe == true){pEwMqyOzYe = false;}
      if(mdlUJyVoMX == true){mdlUJyVoMX = false;}
      if(hdIfYnSYcY == true){hdIfYnSYcY = false;}
      if(thpANjBGaC == true){thpANjBGaC = false;}
      if(ciNsrrOSXO == true){ciNsrrOSXO = false;}
      if(MhzSlLuPmD == true){MhzSlLuPmD = false;}
      if(foWzkFmlGZ == true){foWzkFmlGZ = false;}
      if(xOOKtzQPng == true){xOOKtzQPng = false;}
      if(ZzBNMMhXNC == true){ZzBNMMhXNC = false;}
      if(okTXWmMNIm == true){okTXWmMNIm = false;}
      if(EbMyRyTnXm == true){EbMyRyTnXm = false;}
      if(tfbGdfnImX == true){tfbGdfnImX = false;}
      if(WOYEkLtpnH == true){WOYEkLtpnH = false;}
      if(lDHAbxlDuN == true){lDHAbxlDuN = false;}
      if(stAZHIJNtp == true){stAZHIJNtp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XPCCTXNIMZ
{ 
  void WnOncXzDoq()
  { 
      bool oSHzLcRxmo = false;
      bool sdCQPProrL = false;
      bool nyymilOAHJ = false;
      bool nRoFqraIZl = false;
      bool npDWsMnfdB = false;
      bool oSfqRqUUQY = false;
      bool NRodBanxYW = false;
      bool niOFXxtbsW = false;
      bool yhVGTUkymA = false;
      bool XGrAXVAYUR = false;
      bool XpHGNGDZSU = false;
      bool wrasafuiKf = false;
      bool ppKXzgqOgB = false;
      bool xUGazHaOrN = false;
      bool QLeSDfeyYr = false;
      bool aQOnbgfiHf = false;
      bool PorQWbkAtT = false;
      bool FfpxPdKrTT = false;
      bool CrpoafGRyR = false;
      bool aqHMxbSOub = false;
      string BJNVihaXIm;
      string qWEochymQI;
      string SwXqxAlOZp;
      string teGjZaHCsT;
      string HYcxcUEXKo;
      string LcwNdFlVXh;
      string wLySrMPTOB;
      string ZuswBsTaNb;
      string wNEjeRhsGU;
      string okdLWwaJEQ;
      string FjIJPPizMk;
      string lKIwlhGOnZ;
      string dVNtLnQhZE;
      string SJVxVMFuTO;
      string ihfVhdchYn;
      string oMVeliVOxa;
      string yAZHRboKZZ;
      string cLtYqwprLg;
      string LiIkPFnqLm;
      string pqxsQhIXDG;
      if(BJNVihaXIm == FjIJPPizMk){oSHzLcRxmo = true;}
      else if(FjIJPPizMk == BJNVihaXIm){XpHGNGDZSU = true;}
      if(qWEochymQI == lKIwlhGOnZ){sdCQPProrL = true;}
      else if(lKIwlhGOnZ == qWEochymQI){wrasafuiKf = true;}
      if(SwXqxAlOZp == dVNtLnQhZE){nyymilOAHJ = true;}
      else if(dVNtLnQhZE == SwXqxAlOZp){ppKXzgqOgB = true;}
      if(teGjZaHCsT == SJVxVMFuTO){nRoFqraIZl = true;}
      else if(SJVxVMFuTO == teGjZaHCsT){xUGazHaOrN = true;}
      if(HYcxcUEXKo == ihfVhdchYn){npDWsMnfdB = true;}
      else if(ihfVhdchYn == HYcxcUEXKo){QLeSDfeyYr = true;}
      if(LcwNdFlVXh == oMVeliVOxa){oSfqRqUUQY = true;}
      else if(oMVeliVOxa == LcwNdFlVXh){aQOnbgfiHf = true;}
      if(wLySrMPTOB == yAZHRboKZZ){NRodBanxYW = true;}
      else if(yAZHRboKZZ == wLySrMPTOB){PorQWbkAtT = true;}
      if(ZuswBsTaNb == cLtYqwprLg){niOFXxtbsW = true;}
      if(wNEjeRhsGU == LiIkPFnqLm){yhVGTUkymA = true;}
      if(okdLWwaJEQ == pqxsQhIXDG){XGrAXVAYUR = true;}
      while(cLtYqwprLg == ZuswBsTaNb){FfpxPdKrTT = true;}
      while(LiIkPFnqLm == LiIkPFnqLm){CrpoafGRyR = true;}
      while(pqxsQhIXDG == pqxsQhIXDG){aqHMxbSOub = true;}
      if(oSHzLcRxmo == true){oSHzLcRxmo = false;}
      if(sdCQPProrL == true){sdCQPProrL = false;}
      if(nyymilOAHJ == true){nyymilOAHJ = false;}
      if(nRoFqraIZl == true){nRoFqraIZl = false;}
      if(npDWsMnfdB == true){npDWsMnfdB = false;}
      if(oSfqRqUUQY == true){oSfqRqUUQY = false;}
      if(NRodBanxYW == true){NRodBanxYW = false;}
      if(niOFXxtbsW == true){niOFXxtbsW = false;}
      if(yhVGTUkymA == true){yhVGTUkymA = false;}
      if(XGrAXVAYUR == true){XGrAXVAYUR = false;}
      if(XpHGNGDZSU == true){XpHGNGDZSU = false;}
      if(wrasafuiKf == true){wrasafuiKf = false;}
      if(ppKXzgqOgB == true){ppKXzgqOgB = false;}
      if(xUGazHaOrN == true){xUGazHaOrN = false;}
      if(QLeSDfeyYr == true){QLeSDfeyYr = false;}
      if(aQOnbgfiHf == true){aQOnbgfiHf = false;}
      if(PorQWbkAtT == true){PorQWbkAtT = false;}
      if(FfpxPdKrTT == true){FfpxPdKrTT = false;}
      if(CrpoafGRyR == true){CrpoafGRyR = false;}
      if(aqHMxbSOub == true){aqHMxbSOub = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IFGYUFUYOI
{ 
  void jLnrniVoOQ()
  { 
      bool btnCddouWt = false;
      bool DwPkKUunuZ = false;
      bool jWfPffSEZo = false;
      bool PGKcuzsAge = false;
      bool NPsDBAfNGR = false;
      bool ckhADFOXWy = false;
      bool LjUhdwkmpL = false;
      bool buGPMUdcNf = false;
      bool AEyILeYKZp = false;
      bool jUciTduLYF = false;
      bool OsXupgdSnh = false;
      bool akJqxGkMVy = false;
      bool WaMzaGRWui = false;
      bool ZSDIQHgDSd = false;
      bool BGWrOzLllN = false;
      bool rhoahnfXTi = false;
      bool OGWEHIhBZo = false;
      bool YgtqxQDUjb = false;
      bool ufkhpqccac = false;
      bool bIiiOtiRjG = false;
      string IwdVEAWuSw;
      string woWhGcrNCc;
      string tSklLylrOk;
      string FoeslPafsY;
      string AgqMGOzcmX;
      string EBwmBoLqKG;
      string NdghpHKdwq;
      string BLUdbMbXfx;
      string zJEpfErrqw;
      string DjVmLVAJWy;
      string EUgwVrgSKo;
      string NnLNHEZpBl;
      string ORmzmRphSF;
      string MSAgrdbHUn;
      string XZhCiPXIeG;
      string wKHkjmggID;
      string ByAEbumdUc;
      string bRVMNojkQX;
      string sgCLJCKPxF;
      string wuzQlYYcZm;
      if(IwdVEAWuSw == EUgwVrgSKo){btnCddouWt = true;}
      else if(EUgwVrgSKo == IwdVEAWuSw){OsXupgdSnh = true;}
      if(woWhGcrNCc == NnLNHEZpBl){DwPkKUunuZ = true;}
      else if(NnLNHEZpBl == woWhGcrNCc){akJqxGkMVy = true;}
      if(tSklLylrOk == ORmzmRphSF){jWfPffSEZo = true;}
      else if(ORmzmRphSF == tSklLylrOk){WaMzaGRWui = true;}
      if(FoeslPafsY == MSAgrdbHUn){PGKcuzsAge = true;}
      else if(MSAgrdbHUn == FoeslPafsY){ZSDIQHgDSd = true;}
      if(AgqMGOzcmX == XZhCiPXIeG){NPsDBAfNGR = true;}
      else if(XZhCiPXIeG == AgqMGOzcmX){BGWrOzLllN = true;}
      if(EBwmBoLqKG == wKHkjmggID){ckhADFOXWy = true;}
      else if(wKHkjmggID == EBwmBoLqKG){rhoahnfXTi = true;}
      if(NdghpHKdwq == ByAEbumdUc){LjUhdwkmpL = true;}
      else if(ByAEbumdUc == NdghpHKdwq){OGWEHIhBZo = true;}
      if(BLUdbMbXfx == bRVMNojkQX){buGPMUdcNf = true;}
      if(zJEpfErrqw == sgCLJCKPxF){AEyILeYKZp = true;}
      if(DjVmLVAJWy == wuzQlYYcZm){jUciTduLYF = true;}
      while(bRVMNojkQX == BLUdbMbXfx){YgtqxQDUjb = true;}
      while(sgCLJCKPxF == sgCLJCKPxF){ufkhpqccac = true;}
      while(wuzQlYYcZm == wuzQlYYcZm){bIiiOtiRjG = true;}
      if(btnCddouWt == true){btnCddouWt = false;}
      if(DwPkKUunuZ == true){DwPkKUunuZ = false;}
      if(jWfPffSEZo == true){jWfPffSEZo = false;}
      if(PGKcuzsAge == true){PGKcuzsAge = false;}
      if(NPsDBAfNGR == true){NPsDBAfNGR = false;}
      if(ckhADFOXWy == true){ckhADFOXWy = false;}
      if(LjUhdwkmpL == true){LjUhdwkmpL = false;}
      if(buGPMUdcNf == true){buGPMUdcNf = false;}
      if(AEyILeYKZp == true){AEyILeYKZp = false;}
      if(jUciTduLYF == true){jUciTduLYF = false;}
      if(OsXupgdSnh == true){OsXupgdSnh = false;}
      if(akJqxGkMVy == true){akJqxGkMVy = false;}
      if(WaMzaGRWui == true){WaMzaGRWui = false;}
      if(ZSDIQHgDSd == true){ZSDIQHgDSd = false;}
      if(BGWrOzLllN == true){BGWrOzLllN = false;}
      if(rhoahnfXTi == true){rhoahnfXTi = false;}
      if(OGWEHIhBZo == true){OGWEHIhBZo = false;}
      if(YgtqxQDUjb == true){YgtqxQDUjb = false;}
      if(ufkhpqccac == true){ufkhpqccac = false;}
      if(bIiiOtiRjG == true){bIiiOtiRjG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WAONAAQVMN
{ 
  void EGaPGLdAEF()
  { 
      bool sFozcZdlSe = false;
      bool IdujYNqcia = false;
      bool fUZYWYBlhs = false;
      bool rMPkaAVhrV = false;
      bool ScjGknJdrt = false;
      bool OHryHXfQbE = false;
      bool XrDZmwOKIY = false;
      bool rIjMHDkSni = false;
      bool PXsndjTQcD = false;
      bool TFFnyaYKSo = false;
      bool ZyUTBFXeqE = false;
      bool mMbsozzPuD = false;
      bool bxhFFlDwOg = false;
      bool daAzIQCZlX = false;
      bool MoZXQGcMyy = false;
      bool aJOPMbQPNP = false;
      bool CaQJZLMcjX = false;
      bool xZcWpmWJny = false;
      bool IpxPFULjlg = false;
      bool AlLWUkYPxE = false;
      string SSSsEJhqIN;
      string pXEZHgBcxZ;
      string toMAyjFqrJ;
      string KUCRxOnNmM;
      string OgyxmOrEit;
      string hkLbQcGRtU;
      string DpyzCUVmcs;
      string snokKNpOMj;
      string qBIybZJZAU;
      string HVSSIXhzuS;
      string sFboBtuaRD;
      string lqFKcChAXc;
      string KwlHkWUWbl;
      string eqTsqlYSwg;
      string diHxiQQIpG;
      string phbRHxSTEe;
      string ZXyfXuWLSp;
      string cPDpzbnoYU;
      string FLgVwxOClt;
      string SENRHFjbYn;
      if(SSSsEJhqIN == sFboBtuaRD){sFozcZdlSe = true;}
      else if(sFboBtuaRD == SSSsEJhqIN){ZyUTBFXeqE = true;}
      if(pXEZHgBcxZ == lqFKcChAXc){IdujYNqcia = true;}
      else if(lqFKcChAXc == pXEZHgBcxZ){mMbsozzPuD = true;}
      if(toMAyjFqrJ == KwlHkWUWbl){fUZYWYBlhs = true;}
      else if(KwlHkWUWbl == toMAyjFqrJ){bxhFFlDwOg = true;}
      if(KUCRxOnNmM == eqTsqlYSwg){rMPkaAVhrV = true;}
      else if(eqTsqlYSwg == KUCRxOnNmM){daAzIQCZlX = true;}
      if(OgyxmOrEit == diHxiQQIpG){ScjGknJdrt = true;}
      else if(diHxiQQIpG == OgyxmOrEit){MoZXQGcMyy = true;}
      if(hkLbQcGRtU == phbRHxSTEe){OHryHXfQbE = true;}
      else if(phbRHxSTEe == hkLbQcGRtU){aJOPMbQPNP = true;}
      if(DpyzCUVmcs == ZXyfXuWLSp){XrDZmwOKIY = true;}
      else if(ZXyfXuWLSp == DpyzCUVmcs){CaQJZLMcjX = true;}
      if(snokKNpOMj == cPDpzbnoYU){rIjMHDkSni = true;}
      if(qBIybZJZAU == FLgVwxOClt){PXsndjTQcD = true;}
      if(HVSSIXhzuS == SENRHFjbYn){TFFnyaYKSo = true;}
      while(cPDpzbnoYU == snokKNpOMj){xZcWpmWJny = true;}
      while(FLgVwxOClt == FLgVwxOClt){IpxPFULjlg = true;}
      while(SENRHFjbYn == SENRHFjbYn){AlLWUkYPxE = true;}
      if(sFozcZdlSe == true){sFozcZdlSe = false;}
      if(IdujYNqcia == true){IdujYNqcia = false;}
      if(fUZYWYBlhs == true){fUZYWYBlhs = false;}
      if(rMPkaAVhrV == true){rMPkaAVhrV = false;}
      if(ScjGknJdrt == true){ScjGknJdrt = false;}
      if(OHryHXfQbE == true){OHryHXfQbE = false;}
      if(XrDZmwOKIY == true){XrDZmwOKIY = false;}
      if(rIjMHDkSni == true){rIjMHDkSni = false;}
      if(PXsndjTQcD == true){PXsndjTQcD = false;}
      if(TFFnyaYKSo == true){TFFnyaYKSo = false;}
      if(ZyUTBFXeqE == true){ZyUTBFXeqE = false;}
      if(mMbsozzPuD == true){mMbsozzPuD = false;}
      if(bxhFFlDwOg == true){bxhFFlDwOg = false;}
      if(daAzIQCZlX == true){daAzIQCZlX = false;}
      if(MoZXQGcMyy == true){MoZXQGcMyy = false;}
      if(aJOPMbQPNP == true){aJOPMbQPNP = false;}
      if(CaQJZLMcjX == true){CaQJZLMcjX = false;}
      if(xZcWpmWJny == true){xZcWpmWJny = false;}
      if(IpxPFULjlg == true){IpxPFULjlg = false;}
      if(AlLWUkYPxE == true){AlLWUkYPxE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WMOHHTOOIR
{ 
  void YgtxubrCPZ()
  { 
      bool MiVEJBJtlf = false;
      bool qCLGRbOxOi = false;
      bool TRrLFNqyTI = false;
      bool YDZLJVBFFZ = false;
      bool CXtJeGYNFZ = false;
      bool cwICFtqKyu = false;
      bool JLadHnbAww = false;
      bool ZIrofuXhfz = false;
      bool ocrtebuXGO = false;
      bool eqHJPqwPCq = false;
      bool eXRJzUESVJ = false;
      bool WIdzFgSgye = false;
      bool rDthQiAhZo = false;
      bool zHeoTRLitJ = false;
      bool XbBxrVNIEi = false;
      bool XPRXyadirQ = false;
      bool TWsgJOcoen = false;
      bool UjlnGPBxou = false;
      bool UrdpRipHps = false;
      bool mbpdpBiUmc = false;
      string tnqwGnnFLi;
      string CHEmQpxBDw;
      string rHEEdrkXyK;
      string BldtQJcsSr;
      string lEmjojPNQH;
      string giwmamjmRN;
      string DQHBhPdKWG;
      string MEhLJnTTOt;
      string bWGpdRppSc;
      string ZpbEnVwlCY;
      string FFpJtbBjcm;
      string SPXWlfJQWP;
      string ZmqtgWbcXm;
      string qgRooWgxuB;
      string PGMfJKRESI;
      string MePlzRNwcX;
      string AXMoukxhhO;
      string yLVUASaLjV;
      string FXJOaMRfpW;
      string IkUXBqtWkY;
      if(tnqwGnnFLi == FFpJtbBjcm){MiVEJBJtlf = true;}
      else if(FFpJtbBjcm == tnqwGnnFLi){eXRJzUESVJ = true;}
      if(CHEmQpxBDw == SPXWlfJQWP){qCLGRbOxOi = true;}
      else if(SPXWlfJQWP == CHEmQpxBDw){WIdzFgSgye = true;}
      if(rHEEdrkXyK == ZmqtgWbcXm){TRrLFNqyTI = true;}
      else if(ZmqtgWbcXm == rHEEdrkXyK){rDthQiAhZo = true;}
      if(BldtQJcsSr == qgRooWgxuB){YDZLJVBFFZ = true;}
      else if(qgRooWgxuB == BldtQJcsSr){zHeoTRLitJ = true;}
      if(lEmjojPNQH == PGMfJKRESI){CXtJeGYNFZ = true;}
      else if(PGMfJKRESI == lEmjojPNQH){XbBxrVNIEi = true;}
      if(giwmamjmRN == MePlzRNwcX){cwICFtqKyu = true;}
      else if(MePlzRNwcX == giwmamjmRN){XPRXyadirQ = true;}
      if(DQHBhPdKWG == AXMoukxhhO){JLadHnbAww = true;}
      else if(AXMoukxhhO == DQHBhPdKWG){TWsgJOcoen = true;}
      if(MEhLJnTTOt == yLVUASaLjV){ZIrofuXhfz = true;}
      if(bWGpdRppSc == FXJOaMRfpW){ocrtebuXGO = true;}
      if(ZpbEnVwlCY == IkUXBqtWkY){eqHJPqwPCq = true;}
      while(yLVUASaLjV == MEhLJnTTOt){UjlnGPBxou = true;}
      while(FXJOaMRfpW == FXJOaMRfpW){UrdpRipHps = true;}
      while(IkUXBqtWkY == IkUXBqtWkY){mbpdpBiUmc = true;}
      if(MiVEJBJtlf == true){MiVEJBJtlf = false;}
      if(qCLGRbOxOi == true){qCLGRbOxOi = false;}
      if(TRrLFNqyTI == true){TRrLFNqyTI = false;}
      if(YDZLJVBFFZ == true){YDZLJVBFFZ = false;}
      if(CXtJeGYNFZ == true){CXtJeGYNFZ = false;}
      if(cwICFtqKyu == true){cwICFtqKyu = false;}
      if(JLadHnbAww == true){JLadHnbAww = false;}
      if(ZIrofuXhfz == true){ZIrofuXhfz = false;}
      if(ocrtebuXGO == true){ocrtebuXGO = false;}
      if(eqHJPqwPCq == true){eqHJPqwPCq = false;}
      if(eXRJzUESVJ == true){eXRJzUESVJ = false;}
      if(WIdzFgSgye == true){WIdzFgSgye = false;}
      if(rDthQiAhZo == true){rDthQiAhZo = false;}
      if(zHeoTRLitJ == true){zHeoTRLitJ = false;}
      if(XbBxrVNIEi == true){XbBxrVNIEi = false;}
      if(XPRXyadirQ == true){XPRXyadirQ = false;}
      if(TWsgJOcoen == true){TWsgJOcoen = false;}
      if(UjlnGPBxou == true){UjlnGPBxou = false;}
      if(UrdpRipHps == true){UrdpRipHps = false;}
      if(mbpdpBiUmc == true){mbpdpBiUmc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WDXJRALESK
{ 
  void KThMakKGAs()
  { 
      bool TZhVDJYWIi = false;
      bool VeeOhNcXmn = false;
      bool nlhGKVqZOR = false;
      bool uNVJDsqrdZ = false;
      bool alBbtNZtLO = false;
      bool NonmRgrbLg = false;
      bool RyHqmHJVKn = false;
      bool WktNMBkFLw = false;
      bool wxOADGYhqW = false;
      bool BOfwIcdJnm = false;
      bool EDjWqcuaZQ = false;
      bool wlPOkTiHmg = false;
      bool haenlHExEi = false;
      bool WaQYrrNqIa = false;
      bool KyHZZOzRKn = false;
      bool sWWHEdYuki = false;
      bool XxWpsUVqWr = false;
      bool GqzMWjSFNX = false;
      bool ImmPpAEJTN = false;
      bool TRGYCMbRfE = false;
      string lyXGgKugdZ;
      string giipZrMJPU;
      string EQqCfCVcgk;
      string YVeawumdaw;
      string WFRIeEuHFw;
      string BMlOeVGUZd;
      string oRzsBLEHtd;
      string FiiTyyyhXa;
      string HNWkiLjPwa;
      string oRDwGEGYHT;
      string AmNbpSdRQf;
      string WXxyWbuOJp;
      string aoLSonemMs;
      string rYaDaTzuuQ;
      string hRzPDQTFYe;
      string JrPQrKatlB;
      string mqEWnxwsWD;
      string bASrIIowPX;
      string TZNgjAJJLQ;
      string rFIscqMbaG;
      if(lyXGgKugdZ == AmNbpSdRQf){TZhVDJYWIi = true;}
      else if(AmNbpSdRQf == lyXGgKugdZ){EDjWqcuaZQ = true;}
      if(giipZrMJPU == WXxyWbuOJp){VeeOhNcXmn = true;}
      else if(WXxyWbuOJp == giipZrMJPU){wlPOkTiHmg = true;}
      if(EQqCfCVcgk == aoLSonemMs){nlhGKVqZOR = true;}
      else if(aoLSonemMs == EQqCfCVcgk){haenlHExEi = true;}
      if(YVeawumdaw == rYaDaTzuuQ){uNVJDsqrdZ = true;}
      else if(rYaDaTzuuQ == YVeawumdaw){WaQYrrNqIa = true;}
      if(WFRIeEuHFw == hRzPDQTFYe){alBbtNZtLO = true;}
      else if(hRzPDQTFYe == WFRIeEuHFw){KyHZZOzRKn = true;}
      if(BMlOeVGUZd == JrPQrKatlB){NonmRgrbLg = true;}
      else if(JrPQrKatlB == BMlOeVGUZd){sWWHEdYuki = true;}
      if(oRzsBLEHtd == mqEWnxwsWD){RyHqmHJVKn = true;}
      else if(mqEWnxwsWD == oRzsBLEHtd){XxWpsUVqWr = true;}
      if(FiiTyyyhXa == bASrIIowPX){WktNMBkFLw = true;}
      if(HNWkiLjPwa == TZNgjAJJLQ){wxOADGYhqW = true;}
      if(oRDwGEGYHT == rFIscqMbaG){BOfwIcdJnm = true;}
      while(bASrIIowPX == FiiTyyyhXa){GqzMWjSFNX = true;}
      while(TZNgjAJJLQ == TZNgjAJJLQ){ImmPpAEJTN = true;}
      while(rFIscqMbaG == rFIscqMbaG){TRGYCMbRfE = true;}
      if(TZhVDJYWIi == true){TZhVDJYWIi = false;}
      if(VeeOhNcXmn == true){VeeOhNcXmn = false;}
      if(nlhGKVqZOR == true){nlhGKVqZOR = false;}
      if(uNVJDsqrdZ == true){uNVJDsqrdZ = false;}
      if(alBbtNZtLO == true){alBbtNZtLO = false;}
      if(NonmRgrbLg == true){NonmRgrbLg = false;}
      if(RyHqmHJVKn == true){RyHqmHJVKn = false;}
      if(WktNMBkFLw == true){WktNMBkFLw = false;}
      if(wxOADGYhqW == true){wxOADGYhqW = false;}
      if(BOfwIcdJnm == true){BOfwIcdJnm = false;}
      if(EDjWqcuaZQ == true){EDjWqcuaZQ = false;}
      if(wlPOkTiHmg == true){wlPOkTiHmg = false;}
      if(haenlHExEi == true){haenlHExEi = false;}
      if(WaQYrrNqIa == true){WaQYrrNqIa = false;}
      if(KyHZZOzRKn == true){KyHZZOzRKn = false;}
      if(sWWHEdYuki == true){sWWHEdYuki = false;}
      if(XxWpsUVqWr == true){XxWpsUVqWr = false;}
      if(GqzMWjSFNX == true){GqzMWjSFNX = false;}
      if(ImmPpAEJTN == true){ImmPpAEJTN = false;}
      if(TRGYCMbRfE == true){TRGYCMbRfE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KGMBSDIDLV
{ 
  void HnwXNHhndu()
  { 
      bool WgDKipxSxH = false;
      bool tuwsLHEJgK = false;
      bool PdIgFSPQCu = false;
      bool FUxBgWuzwG = false;
      bool OJIBVTLmLp = false;
      bool JmXBlrYWEP = false;
      bool agQBBYxtLn = false;
      bool MFMawFVGKl = false;
      bool GcELkRwuOn = false;
      bool yYtffgsHzx = false;
      bool VQaXdEZxFf = false;
      bool WRMSJycEPj = false;
      bool bCfXpnLguP = false;
      bool MNHMPoBggg = false;
      bool qzphRfLaWh = false;
      bool DnqPUTkDgp = false;
      bool rsCoTIKzCT = false;
      bool wwWircLxGJ = false;
      bool bkKNLXWqqw = false;
      bool EyzqnyxAOI = false;
      string TgYyPPKATI;
      string kLlUZZNYNM;
      string MLZVBMdDPB;
      string meEnpLlfTe;
      string RzqQEkuaUH;
      string oHOHiIGCxD;
      string lGjRUFGyeO;
      string mhEitMUJRP;
      string QDhHMfQwFh;
      string EjhQsKOYuy;
      string exwGTGCeNV;
      string mxkhlhYbFn;
      string nJsxJDznpi;
      string yuNSkSHbnF;
      string dliitGzAdK;
      string llSHJUEzwP;
      string GOodWrjRxT;
      string awnAKCaJCD;
      string EzJewMbFIP;
      string OHfXyOxFMB;
      if(TgYyPPKATI == exwGTGCeNV){WgDKipxSxH = true;}
      else if(exwGTGCeNV == TgYyPPKATI){VQaXdEZxFf = true;}
      if(kLlUZZNYNM == mxkhlhYbFn){tuwsLHEJgK = true;}
      else if(mxkhlhYbFn == kLlUZZNYNM){WRMSJycEPj = true;}
      if(MLZVBMdDPB == nJsxJDznpi){PdIgFSPQCu = true;}
      else if(nJsxJDznpi == MLZVBMdDPB){bCfXpnLguP = true;}
      if(meEnpLlfTe == yuNSkSHbnF){FUxBgWuzwG = true;}
      else if(yuNSkSHbnF == meEnpLlfTe){MNHMPoBggg = true;}
      if(RzqQEkuaUH == dliitGzAdK){OJIBVTLmLp = true;}
      else if(dliitGzAdK == RzqQEkuaUH){qzphRfLaWh = true;}
      if(oHOHiIGCxD == llSHJUEzwP){JmXBlrYWEP = true;}
      else if(llSHJUEzwP == oHOHiIGCxD){DnqPUTkDgp = true;}
      if(lGjRUFGyeO == GOodWrjRxT){agQBBYxtLn = true;}
      else if(GOodWrjRxT == lGjRUFGyeO){rsCoTIKzCT = true;}
      if(mhEitMUJRP == awnAKCaJCD){MFMawFVGKl = true;}
      if(QDhHMfQwFh == EzJewMbFIP){GcELkRwuOn = true;}
      if(EjhQsKOYuy == OHfXyOxFMB){yYtffgsHzx = true;}
      while(awnAKCaJCD == mhEitMUJRP){wwWircLxGJ = true;}
      while(EzJewMbFIP == EzJewMbFIP){bkKNLXWqqw = true;}
      while(OHfXyOxFMB == OHfXyOxFMB){EyzqnyxAOI = true;}
      if(WgDKipxSxH == true){WgDKipxSxH = false;}
      if(tuwsLHEJgK == true){tuwsLHEJgK = false;}
      if(PdIgFSPQCu == true){PdIgFSPQCu = false;}
      if(FUxBgWuzwG == true){FUxBgWuzwG = false;}
      if(OJIBVTLmLp == true){OJIBVTLmLp = false;}
      if(JmXBlrYWEP == true){JmXBlrYWEP = false;}
      if(agQBBYxtLn == true){agQBBYxtLn = false;}
      if(MFMawFVGKl == true){MFMawFVGKl = false;}
      if(GcELkRwuOn == true){GcELkRwuOn = false;}
      if(yYtffgsHzx == true){yYtffgsHzx = false;}
      if(VQaXdEZxFf == true){VQaXdEZxFf = false;}
      if(WRMSJycEPj == true){WRMSJycEPj = false;}
      if(bCfXpnLguP == true){bCfXpnLguP = false;}
      if(MNHMPoBggg == true){MNHMPoBggg = false;}
      if(qzphRfLaWh == true){qzphRfLaWh = false;}
      if(DnqPUTkDgp == true){DnqPUTkDgp = false;}
      if(rsCoTIKzCT == true){rsCoTIKzCT = false;}
      if(wwWircLxGJ == true){wwWircLxGJ = false;}
      if(bkKNLXWqqw == true){bkKNLXWqqw = false;}
      if(EyzqnyxAOI == true){EyzqnyxAOI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class URTBSPWJGZ
{ 
  void YRSJPhqsMn()
  { 
      bool XzVTgawxHG = false;
      bool dtSHzDyGkz = false;
      bool MgjZfZRIFK = false;
      bool fStwEubJQG = false;
      bool uORyWzLLHw = false;
      bool tWtpDpOwnG = false;
      bool JnrxaKAWCE = false;
      bool bnodDyPlCf = false;
      bool OFBIQIYDrN = false;
      bool ffVKwHWUXL = false;
      bool znJDUFgPlE = false;
      bool acsHqEmifR = false;
      bool kweoXuSegw = false;
      bool btOpgZwxnK = false;
      bool aJRmmClNTr = false;
      bool UmnFaDJTeY = false;
      bool lChocfODZQ = false;
      bool HotUqbdqBU = false;
      bool IELoboFJPd = false;
      bool QbRPXXabKG = false;
      string BLxkgSnnrm;
      string TWAVLWziyW;
      string KozIfLIJqm;
      string qAQGohnFPL;
      string daPecdoOSM;
      string oUbFeMLoFV;
      string JewFuSGsfc;
      string htSlsiYTeB;
      string VsqexWYKbc;
      string WzAtBzdKiK;
      string XwioduBoMu;
      string mqKDzPmRHY;
      string suQCGisYjt;
      string EOjUcYKCBC;
      string Uixgpeowtl;
      string LMCKQbefit;
      string BcFSqYHoaZ;
      string FkPFDJyjMb;
      string txdyhqLZEB;
      string teSHArdeoQ;
      if(BLxkgSnnrm == XwioduBoMu){XzVTgawxHG = true;}
      else if(XwioduBoMu == BLxkgSnnrm){znJDUFgPlE = true;}
      if(TWAVLWziyW == mqKDzPmRHY){dtSHzDyGkz = true;}
      else if(mqKDzPmRHY == TWAVLWziyW){acsHqEmifR = true;}
      if(KozIfLIJqm == suQCGisYjt){MgjZfZRIFK = true;}
      else if(suQCGisYjt == KozIfLIJqm){kweoXuSegw = true;}
      if(qAQGohnFPL == EOjUcYKCBC){fStwEubJQG = true;}
      else if(EOjUcYKCBC == qAQGohnFPL){btOpgZwxnK = true;}
      if(daPecdoOSM == Uixgpeowtl){uORyWzLLHw = true;}
      else if(Uixgpeowtl == daPecdoOSM){aJRmmClNTr = true;}
      if(oUbFeMLoFV == LMCKQbefit){tWtpDpOwnG = true;}
      else if(LMCKQbefit == oUbFeMLoFV){UmnFaDJTeY = true;}
      if(JewFuSGsfc == BcFSqYHoaZ){JnrxaKAWCE = true;}
      else if(BcFSqYHoaZ == JewFuSGsfc){lChocfODZQ = true;}
      if(htSlsiYTeB == FkPFDJyjMb){bnodDyPlCf = true;}
      if(VsqexWYKbc == txdyhqLZEB){OFBIQIYDrN = true;}
      if(WzAtBzdKiK == teSHArdeoQ){ffVKwHWUXL = true;}
      while(FkPFDJyjMb == htSlsiYTeB){HotUqbdqBU = true;}
      while(txdyhqLZEB == txdyhqLZEB){IELoboFJPd = true;}
      while(teSHArdeoQ == teSHArdeoQ){QbRPXXabKG = true;}
      if(XzVTgawxHG == true){XzVTgawxHG = false;}
      if(dtSHzDyGkz == true){dtSHzDyGkz = false;}
      if(MgjZfZRIFK == true){MgjZfZRIFK = false;}
      if(fStwEubJQG == true){fStwEubJQG = false;}
      if(uORyWzLLHw == true){uORyWzLLHw = false;}
      if(tWtpDpOwnG == true){tWtpDpOwnG = false;}
      if(JnrxaKAWCE == true){JnrxaKAWCE = false;}
      if(bnodDyPlCf == true){bnodDyPlCf = false;}
      if(OFBIQIYDrN == true){OFBIQIYDrN = false;}
      if(ffVKwHWUXL == true){ffVKwHWUXL = false;}
      if(znJDUFgPlE == true){znJDUFgPlE = false;}
      if(acsHqEmifR == true){acsHqEmifR = false;}
      if(kweoXuSegw == true){kweoXuSegw = false;}
      if(btOpgZwxnK == true){btOpgZwxnK = false;}
      if(aJRmmClNTr == true){aJRmmClNTr = false;}
      if(UmnFaDJTeY == true){UmnFaDJTeY = false;}
      if(lChocfODZQ == true){lChocfODZQ = false;}
      if(HotUqbdqBU == true){HotUqbdqBU = false;}
      if(IELoboFJPd == true){IELoboFJPd = false;}
      if(QbRPXXabKG == true){QbRPXXabKG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QFWPIFVVYQ
{ 
  void sIrsGyXcys()
  { 
      bool YDtSCyfFpX = false;
      bool pbifUkRVue = false;
      bool VnHVYjSwec = false;
      bool pPgJqpLZTp = false;
      bool GrqHrdqfpK = false;
      bool jwIedkuYtR = false;
      bool fjZMhauYod = false;
      bool YrBEXcwAdt = false;
      bool slFUrtHCeG = false;
      bool umeBJWRdZR = false;
      bool iRqLkrtDGB = false;
      bool nttzYtdFTn = false;
      bool TrshikMzuA = false;
      bool KSaMLattjA = false;
      bool zDudSAsfcP = false;
      bool sMJkxpXIbz = false;
      bool etIFqUThmx = false;
      bool ziUTnPwPPi = false;
      bool rgWeHxIoOV = false;
      bool DlRkUEuplx = false;
      string AoHTqXGxrP;
      string dahmpSBFeL;
      string KauCQdFAto;
      string GeeyrNtyNG;
      string YTzZuKTQjX;
      string BrwogZtFCM;
      string RFCDIyuiuc;
      string YCqXlpaUGG;
      string JnQWmOhpRR;
      string SouAoTRwQw;
      string OkVGyzAYCp;
      string yYywDcoePt;
      string QFRcJjGphS;
      string YeEKqYSJYn;
      string NImaTspzxM;
      string dlgWfISrwN;
      string rKqjRTUmEd;
      string KeGafHSpJP;
      string sGrVnlygeh;
      string FZMKuCRDJz;
      if(AoHTqXGxrP == OkVGyzAYCp){YDtSCyfFpX = true;}
      else if(OkVGyzAYCp == AoHTqXGxrP){iRqLkrtDGB = true;}
      if(dahmpSBFeL == yYywDcoePt){pbifUkRVue = true;}
      else if(yYywDcoePt == dahmpSBFeL){nttzYtdFTn = true;}
      if(KauCQdFAto == QFRcJjGphS){VnHVYjSwec = true;}
      else if(QFRcJjGphS == KauCQdFAto){TrshikMzuA = true;}
      if(GeeyrNtyNG == YeEKqYSJYn){pPgJqpLZTp = true;}
      else if(YeEKqYSJYn == GeeyrNtyNG){KSaMLattjA = true;}
      if(YTzZuKTQjX == NImaTspzxM){GrqHrdqfpK = true;}
      else if(NImaTspzxM == YTzZuKTQjX){zDudSAsfcP = true;}
      if(BrwogZtFCM == dlgWfISrwN){jwIedkuYtR = true;}
      else if(dlgWfISrwN == BrwogZtFCM){sMJkxpXIbz = true;}
      if(RFCDIyuiuc == rKqjRTUmEd){fjZMhauYod = true;}
      else if(rKqjRTUmEd == RFCDIyuiuc){etIFqUThmx = true;}
      if(YCqXlpaUGG == KeGafHSpJP){YrBEXcwAdt = true;}
      if(JnQWmOhpRR == sGrVnlygeh){slFUrtHCeG = true;}
      if(SouAoTRwQw == FZMKuCRDJz){umeBJWRdZR = true;}
      while(KeGafHSpJP == YCqXlpaUGG){ziUTnPwPPi = true;}
      while(sGrVnlygeh == sGrVnlygeh){rgWeHxIoOV = true;}
      while(FZMKuCRDJz == FZMKuCRDJz){DlRkUEuplx = true;}
      if(YDtSCyfFpX == true){YDtSCyfFpX = false;}
      if(pbifUkRVue == true){pbifUkRVue = false;}
      if(VnHVYjSwec == true){VnHVYjSwec = false;}
      if(pPgJqpLZTp == true){pPgJqpLZTp = false;}
      if(GrqHrdqfpK == true){GrqHrdqfpK = false;}
      if(jwIedkuYtR == true){jwIedkuYtR = false;}
      if(fjZMhauYod == true){fjZMhauYod = false;}
      if(YrBEXcwAdt == true){YrBEXcwAdt = false;}
      if(slFUrtHCeG == true){slFUrtHCeG = false;}
      if(umeBJWRdZR == true){umeBJWRdZR = false;}
      if(iRqLkrtDGB == true){iRqLkrtDGB = false;}
      if(nttzYtdFTn == true){nttzYtdFTn = false;}
      if(TrshikMzuA == true){TrshikMzuA = false;}
      if(KSaMLattjA == true){KSaMLattjA = false;}
      if(zDudSAsfcP == true){zDudSAsfcP = false;}
      if(sMJkxpXIbz == true){sMJkxpXIbz = false;}
      if(etIFqUThmx == true){etIFqUThmx = false;}
      if(ziUTnPwPPi == true){ziUTnPwPPi = false;}
      if(rgWeHxIoOV == true){rgWeHxIoOV = false;}
      if(DlRkUEuplx == true){DlRkUEuplx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HAUOYJKMRI
{ 
  void agwddRkLkL()
  { 
      bool znqbRGekIl = false;
      bool sjyROPsYda = false;
      bool MwHhFfCCnk = false;
      bool ijmsmBNzhs = false;
      bool SZZfXbzRKU = false;
      bool IURVRDfJWk = false;
      bool EbxWDJwFeN = false;
      bool CsqjIlVbJc = false;
      bool gjrSbNSRai = false;
      bool VEcxopcCbO = false;
      bool etmwSOdgNe = false;
      bool gDzsDUiduo = false;
      bool qedwrxQsuR = false;
      bool JTzuxmxuAN = false;
      bool jkEuBRFjsU = false;
      bool HzHmWAPpEV = false;
      bool ykluVNDEuQ = false;
      bool WndgEGZhtZ = false;
      bool qgzZKJMLXx = false;
      bool WGqdOzyIZn = false;
      string ZHxGeHVLXq;
      string lixnfxREAT;
      string bNPtxdqiSS;
      string RzguMcXoqK;
      string GHxfzdZYXf;
      string tDKkxLrCJA;
      string PlsFZlBCbC;
      string YbMpNTPjuT;
      string DRKlYOowyA;
      string kVfqtTOrGN;
      string cXxVHRqUWc;
      string wHHpxyaGgK;
      string xEEaQDwVus;
      string EWdhpfTodG;
      string XTYUDdNpsu;
      string sHLuPYTVEE;
      string VUYdXYdZzR;
      string dlcZmdejXm;
      string oFbzAxLhRR;
      string LxjZkCtuwe;
      if(ZHxGeHVLXq == cXxVHRqUWc){znqbRGekIl = true;}
      else if(cXxVHRqUWc == ZHxGeHVLXq){etmwSOdgNe = true;}
      if(lixnfxREAT == wHHpxyaGgK){sjyROPsYda = true;}
      else if(wHHpxyaGgK == lixnfxREAT){gDzsDUiduo = true;}
      if(bNPtxdqiSS == xEEaQDwVus){MwHhFfCCnk = true;}
      else if(xEEaQDwVus == bNPtxdqiSS){qedwrxQsuR = true;}
      if(RzguMcXoqK == EWdhpfTodG){ijmsmBNzhs = true;}
      else if(EWdhpfTodG == RzguMcXoqK){JTzuxmxuAN = true;}
      if(GHxfzdZYXf == XTYUDdNpsu){SZZfXbzRKU = true;}
      else if(XTYUDdNpsu == GHxfzdZYXf){jkEuBRFjsU = true;}
      if(tDKkxLrCJA == sHLuPYTVEE){IURVRDfJWk = true;}
      else if(sHLuPYTVEE == tDKkxLrCJA){HzHmWAPpEV = true;}
      if(PlsFZlBCbC == VUYdXYdZzR){EbxWDJwFeN = true;}
      else if(VUYdXYdZzR == PlsFZlBCbC){ykluVNDEuQ = true;}
      if(YbMpNTPjuT == dlcZmdejXm){CsqjIlVbJc = true;}
      if(DRKlYOowyA == oFbzAxLhRR){gjrSbNSRai = true;}
      if(kVfqtTOrGN == LxjZkCtuwe){VEcxopcCbO = true;}
      while(dlcZmdejXm == YbMpNTPjuT){WndgEGZhtZ = true;}
      while(oFbzAxLhRR == oFbzAxLhRR){qgzZKJMLXx = true;}
      while(LxjZkCtuwe == LxjZkCtuwe){WGqdOzyIZn = true;}
      if(znqbRGekIl == true){znqbRGekIl = false;}
      if(sjyROPsYda == true){sjyROPsYda = false;}
      if(MwHhFfCCnk == true){MwHhFfCCnk = false;}
      if(ijmsmBNzhs == true){ijmsmBNzhs = false;}
      if(SZZfXbzRKU == true){SZZfXbzRKU = false;}
      if(IURVRDfJWk == true){IURVRDfJWk = false;}
      if(EbxWDJwFeN == true){EbxWDJwFeN = false;}
      if(CsqjIlVbJc == true){CsqjIlVbJc = false;}
      if(gjrSbNSRai == true){gjrSbNSRai = false;}
      if(VEcxopcCbO == true){VEcxopcCbO = false;}
      if(etmwSOdgNe == true){etmwSOdgNe = false;}
      if(gDzsDUiduo == true){gDzsDUiduo = false;}
      if(qedwrxQsuR == true){qedwrxQsuR = false;}
      if(JTzuxmxuAN == true){JTzuxmxuAN = false;}
      if(jkEuBRFjsU == true){jkEuBRFjsU = false;}
      if(HzHmWAPpEV == true){HzHmWAPpEV = false;}
      if(ykluVNDEuQ == true){ykluVNDEuQ = false;}
      if(WndgEGZhtZ == true){WndgEGZhtZ = false;}
      if(qgzZKJMLXx == true){qgzZKJMLXx = false;}
      if(WGqdOzyIZn == true){WGqdOzyIZn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENCXFKJOPK
{ 
  void fzWjNTyhZq()
  { 
      bool WUIxBLQmbq = false;
      bool mwZrKxwNSX = false;
      bool ugJTCHlZIg = false;
      bool SsokjWtXWy = false;
      bool ZHkIZLoHXH = false;
      bool KNSGEpKous = false;
      bool ZqeuXsHoHm = false;
      bool DYqUxnuAsp = false;
      bool SdBAVFZhgs = false;
      bool LEccXicpjf = false;
      bool EAzjDlWyJP = false;
      bool tJuEauodYS = false;
      bool TYINazuNwN = false;
      bool LFQNkSdQxj = false;
      bool hbYQzCIXCc = false;
      bool syQQMfqkJE = false;
      bool pJBuEnshTI = false;
      bool QXfnkrzrOY = false;
      bool pWKTUMozAF = false;
      bool asHssYZdLL = false;
      string DIFCraXbGT;
      string ATZltzAqJf;
      string CBXcyLKObn;
      string jyZofbDFXn;
      string pSlOwGMuqT;
      string nODZPBjcDg;
      string PIASiCtkGR;
      string wtTUoiOJfr;
      string yPXHzUtzYd;
      string raBpYhSTet;
      string ManYXsuhjf;
      string lZwLhzjrSN;
      string HtLcZVrcwH;
      string QueleXbyjF;
      string ZMOsqSdoHY;
      string xZAQlROLzB;
      string ARkcOquJfK;
      string XkIMnteSkH;
      string qDVXJquNAM;
      string IPzhEHbldA;
      if(DIFCraXbGT == ManYXsuhjf){WUIxBLQmbq = true;}
      else if(ManYXsuhjf == DIFCraXbGT){EAzjDlWyJP = true;}
      if(ATZltzAqJf == lZwLhzjrSN){mwZrKxwNSX = true;}
      else if(lZwLhzjrSN == ATZltzAqJf){tJuEauodYS = true;}
      if(CBXcyLKObn == HtLcZVrcwH){ugJTCHlZIg = true;}
      else if(HtLcZVrcwH == CBXcyLKObn){TYINazuNwN = true;}
      if(jyZofbDFXn == QueleXbyjF){SsokjWtXWy = true;}
      else if(QueleXbyjF == jyZofbDFXn){LFQNkSdQxj = true;}
      if(pSlOwGMuqT == ZMOsqSdoHY){ZHkIZLoHXH = true;}
      else if(ZMOsqSdoHY == pSlOwGMuqT){hbYQzCIXCc = true;}
      if(nODZPBjcDg == xZAQlROLzB){KNSGEpKous = true;}
      else if(xZAQlROLzB == nODZPBjcDg){syQQMfqkJE = true;}
      if(PIASiCtkGR == ARkcOquJfK){ZqeuXsHoHm = true;}
      else if(ARkcOquJfK == PIASiCtkGR){pJBuEnshTI = true;}
      if(wtTUoiOJfr == XkIMnteSkH){DYqUxnuAsp = true;}
      if(yPXHzUtzYd == qDVXJquNAM){SdBAVFZhgs = true;}
      if(raBpYhSTet == IPzhEHbldA){LEccXicpjf = true;}
      while(XkIMnteSkH == wtTUoiOJfr){QXfnkrzrOY = true;}
      while(qDVXJquNAM == qDVXJquNAM){pWKTUMozAF = true;}
      while(IPzhEHbldA == IPzhEHbldA){asHssYZdLL = true;}
      if(WUIxBLQmbq == true){WUIxBLQmbq = false;}
      if(mwZrKxwNSX == true){mwZrKxwNSX = false;}
      if(ugJTCHlZIg == true){ugJTCHlZIg = false;}
      if(SsokjWtXWy == true){SsokjWtXWy = false;}
      if(ZHkIZLoHXH == true){ZHkIZLoHXH = false;}
      if(KNSGEpKous == true){KNSGEpKous = false;}
      if(ZqeuXsHoHm == true){ZqeuXsHoHm = false;}
      if(DYqUxnuAsp == true){DYqUxnuAsp = false;}
      if(SdBAVFZhgs == true){SdBAVFZhgs = false;}
      if(LEccXicpjf == true){LEccXicpjf = false;}
      if(EAzjDlWyJP == true){EAzjDlWyJP = false;}
      if(tJuEauodYS == true){tJuEauodYS = false;}
      if(TYINazuNwN == true){TYINazuNwN = false;}
      if(LFQNkSdQxj == true){LFQNkSdQxj = false;}
      if(hbYQzCIXCc == true){hbYQzCIXCc = false;}
      if(syQQMfqkJE == true){syQQMfqkJE = false;}
      if(pJBuEnshTI == true){pJBuEnshTI = false;}
      if(QXfnkrzrOY == true){QXfnkrzrOY = false;}
      if(pWKTUMozAF == true){pWKTUMozAF = false;}
      if(asHssYZdLL == true){asHssYZdLL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FJHJUIFWMY
{ 
  void RjFbdASdEZ()
  { 
      bool BSqRylyEGA = false;
      bool cGBYhiWZbI = false;
      bool uljUwypcIY = false;
      bool aJWoRiPGlf = false;
      bool aYONcNTIge = false;
      bool ctYLWOhVUA = false;
      bool uVwgZTiMHy = false;
      bool SQnugVXWqi = false;
      bool egudwfjLSD = false;
      bool BskljFcgnJ = false;
      bool eGBhMMGcdA = false;
      bool qLdlUNaRks = false;
      bool jWtExYeCKb = false;
      bool sphhDXfNRi = false;
      bool YGgRLoPyQW = false;
      bool dKwtYHMxjn = false;
      bool gESCHBcwhx = false;
      bool hMACUcpbrI = false;
      bool JgknxhtnJw = false;
      bool KhcdBUneKK = false;
      string zSJFAzSGyk;
      string qtCgYJKnUz;
      string iJKUyEOTHB;
      string WYZDMaOuOB;
      string KhAMoMrcUA;
      string fafJAoHnHw;
      string kzzwOSUyUx;
      string uOZTnAJyfl;
      string MlyGVurPDW;
      string TZnSQLiDxV;
      string rsHWFQBMVA;
      string fJIVjyAraS;
      string aEuydUaGCb;
      string QGAJtSebAE;
      string tetDqJRSiR;
      string KpbeumyIsk;
      string ptKsiYIyaQ;
      string TYrWYuJqGT;
      string CHXjRZdVNG;
      string UVhPNzUATR;
      if(zSJFAzSGyk == rsHWFQBMVA){BSqRylyEGA = true;}
      else if(rsHWFQBMVA == zSJFAzSGyk){eGBhMMGcdA = true;}
      if(qtCgYJKnUz == fJIVjyAraS){cGBYhiWZbI = true;}
      else if(fJIVjyAraS == qtCgYJKnUz){qLdlUNaRks = true;}
      if(iJKUyEOTHB == aEuydUaGCb){uljUwypcIY = true;}
      else if(aEuydUaGCb == iJKUyEOTHB){jWtExYeCKb = true;}
      if(WYZDMaOuOB == QGAJtSebAE){aJWoRiPGlf = true;}
      else if(QGAJtSebAE == WYZDMaOuOB){sphhDXfNRi = true;}
      if(KhAMoMrcUA == tetDqJRSiR){aYONcNTIge = true;}
      else if(tetDqJRSiR == KhAMoMrcUA){YGgRLoPyQW = true;}
      if(fafJAoHnHw == KpbeumyIsk){ctYLWOhVUA = true;}
      else if(KpbeumyIsk == fafJAoHnHw){dKwtYHMxjn = true;}
      if(kzzwOSUyUx == ptKsiYIyaQ){uVwgZTiMHy = true;}
      else if(ptKsiYIyaQ == kzzwOSUyUx){gESCHBcwhx = true;}
      if(uOZTnAJyfl == TYrWYuJqGT){SQnugVXWqi = true;}
      if(MlyGVurPDW == CHXjRZdVNG){egudwfjLSD = true;}
      if(TZnSQLiDxV == UVhPNzUATR){BskljFcgnJ = true;}
      while(TYrWYuJqGT == uOZTnAJyfl){hMACUcpbrI = true;}
      while(CHXjRZdVNG == CHXjRZdVNG){JgknxhtnJw = true;}
      while(UVhPNzUATR == UVhPNzUATR){KhcdBUneKK = true;}
      if(BSqRylyEGA == true){BSqRylyEGA = false;}
      if(cGBYhiWZbI == true){cGBYhiWZbI = false;}
      if(uljUwypcIY == true){uljUwypcIY = false;}
      if(aJWoRiPGlf == true){aJWoRiPGlf = false;}
      if(aYONcNTIge == true){aYONcNTIge = false;}
      if(ctYLWOhVUA == true){ctYLWOhVUA = false;}
      if(uVwgZTiMHy == true){uVwgZTiMHy = false;}
      if(SQnugVXWqi == true){SQnugVXWqi = false;}
      if(egudwfjLSD == true){egudwfjLSD = false;}
      if(BskljFcgnJ == true){BskljFcgnJ = false;}
      if(eGBhMMGcdA == true){eGBhMMGcdA = false;}
      if(qLdlUNaRks == true){qLdlUNaRks = false;}
      if(jWtExYeCKb == true){jWtExYeCKb = false;}
      if(sphhDXfNRi == true){sphhDXfNRi = false;}
      if(YGgRLoPyQW == true){YGgRLoPyQW = false;}
      if(dKwtYHMxjn == true){dKwtYHMxjn = false;}
      if(gESCHBcwhx == true){gESCHBcwhx = false;}
      if(hMACUcpbrI == true){hMACUcpbrI = false;}
      if(JgknxhtnJw == true){JgknxhtnJw = false;}
      if(KhcdBUneKK == true){KhcdBUneKK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFEVQRQTIS
{ 
  void fjewroYbnz()
  { 
      bool gUMKUCiTPc = false;
      bool cfflGWYWFt = false;
      bool zdwUoLYjFR = false;
      bool rzdeQhjZMO = false;
      bool YPXoIftxEL = false;
      bool kntATCYrVJ = false;
      bool czNxjcBBUX = false;
      bool mzKqVjGHLI = false;
      bool RbesgEEcKN = false;
      bool JqECkYBZEe = false;
      bool drbgYldDdj = false;
      bool wRfMrBUUQf = false;
      bool XYqHOutHFx = false;
      bool hgCfdYzyUt = false;
      bool ZByZRrKqKi = false;
      bool EgIXHFBUSc = false;
      bool rVxgBPOAiT = false;
      bool CVAWFWZQoV = false;
      bool kCwVrBXeYX = false;
      bool XeeqCEDRYC = false;
      string pFgFoiHbHn;
      string ShThIlkRPg;
      string HVmYQdEcuc;
      string NplJAODdpc;
      string RadRbykQad;
      string pjfOVTSInL;
      string edgdacwJhs;
      string hGbmPgrVwR;
      string rnBQlcJWmf;
      string wupeymtzpz;
      string CbhhwjHszo;
      string bxLVSqbPqy;
      string SYWCxmQxnb;
      string lrexPQFTUC;
      string UPXxDziTLG;
      string KeIrfdEejJ;
      string TKEWCiRNGB;
      string kIuncDAYzy;
      string DwkhQHjmRl;
      string MZiKiKKAuT;
      if(pFgFoiHbHn == CbhhwjHszo){gUMKUCiTPc = true;}
      else if(CbhhwjHszo == pFgFoiHbHn){drbgYldDdj = true;}
      if(ShThIlkRPg == bxLVSqbPqy){cfflGWYWFt = true;}
      else if(bxLVSqbPqy == ShThIlkRPg){wRfMrBUUQf = true;}
      if(HVmYQdEcuc == SYWCxmQxnb){zdwUoLYjFR = true;}
      else if(SYWCxmQxnb == HVmYQdEcuc){XYqHOutHFx = true;}
      if(NplJAODdpc == lrexPQFTUC){rzdeQhjZMO = true;}
      else if(lrexPQFTUC == NplJAODdpc){hgCfdYzyUt = true;}
      if(RadRbykQad == UPXxDziTLG){YPXoIftxEL = true;}
      else if(UPXxDziTLG == RadRbykQad){ZByZRrKqKi = true;}
      if(pjfOVTSInL == KeIrfdEejJ){kntATCYrVJ = true;}
      else if(KeIrfdEejJ == pjfOVTSInL){EgIXHFBUSc = true;}
      if(edgdacwJhs == TKEWCiRNGB){czNxjcBBUX = true;}
      else if(TKEWCiRNGB == edgdacwJhs){rVxgBPOAiT = true;}
      if(hGbmPgrVwR == kIuncDAYzy){mzKqVjGHLI = true;}
      if(rnBQlcJWmf == DwkhQHjmRl){RbesgEEcKN = true;}
      if(wupeymtzpz == MZiKiKKAuT){JqECkYBZEe = true;}
      while(kIuncDAYzy == hGbmPgrVwR){CVAWFWZQoV = true;}
      while(DwkhQHjmRl == DwkhQHjmRl){kCwVrBXeYX = true;}
      while(MZiKiKKAuT == MZiKiKKAuT){XeeqCEDRYC = true;}
      if(gUMKUCiTPc == true){gUMKUCiTPc = false;}
      if(cfflGWYWFt == true){cfflGWYWFt = false;}
      if(zdwUoLYjFR == true){zdwUoLYjFR = false;}
      if(rzdeQhjZMO == true){rzdeQhjZMO = false;}
      if(YPXoIftxEL == true){YPXoIftxEL = false;}
      if(kntATCYrVJ == true){kntATCYrVJ = false;}
      if(czNxjcBBUX == true){czNxjcBBUX = false;}
      if(mzKqVjGHLI == true){mzKqVjGHLI = false;}
      if(RbesgEEcKN == true){RbesgEEcKN = false;}
      if(JqECkYBZEe == true){JqECkYBZEe = false;}
      if(drbgYldDdj == true){drbgYldDdj = false;}
      if(wRfMrBUUQf == true){wRfMrBUUQf = false;}
      if(XYqHOutHFx == true){XYqHOutHFx = false;}
      if(hgCfdYzyUt == true){hgCfdYzyUt = false;}
      if(ZByZRrKqKi == true){ZByZRrKqKi = false;}
      if(EgIXHFBUSc == true){EgIXHFBUSc = false;}
      if(rVxgBPOAiT == true){rVxgBPOAiT = false;}
      if(CVAWFWZQoV == true){CVAWFWZQoV = false;}
      if(kCwVrBXeYX == true){kCwVrBXeYX = false;}
      if(XeeqCEDRYC == true){XeeqCEDRYC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PCLTXUQVHU
{ 
  void qAbqRqHYTI()
  { 
      bool AjBNwFKquQ = false;
      bool YreTmtNxgk = false;
      bool LOgKZXmeqj = false;
      bool QLENHnWHuR = false;
      bool HGCkWufXps = false;
      bool JfYTGkCpnY = false;
      bool SfzLAMnRMz = false;
      bool XFCPdFLumd = false;
      bool rOnyZkmjHV = false;
      bool kfTVzaGqkK = false;
      bool GNLqVDdJpA = false;
      bool YHCJfDrBkO = false;
      bool ZEKpOqkfPC = false;
      bool yUJcWdDxcW = false;
      bool HcsGwcdJou = false;
      bool iFFVkCDUbe = false;
      bool SxsnCExYlC = false;
      bool ztYOHwKDsk = false;
      bool MapUTsOmrT = false;
      bool ZhUxEJjFEr = false;
      string qIjoLGZnlo;
      string diHZHJrWcm;
      string JhczjwPLAr;
      string qodqNIBIuY;
      string wFDMMZkcwJ;
      string kGNEsIfkEP;
      string pNntxnEQLz;
      string HjbDqDeQmJ;
      string LlPpHkbZyF;
      string cQDehhRJOX;
      string VUQxBAeJNo;
      string dOytEDxxmM;
      string MdRGVpgwVI;
      string lUBOnpUSoG;
      string FRLIaNSIad;
      string jTWCLqCKaK;
      string SinFDJNiGN;
      string heIfGtSJeH;
      string XYUqXSxyCw;
      string nKqdnWcGFR;
      if(qIjoLGZnlo == VUQxBAeJNo){AjBNwFKquQ = true;}
      else if(VUQxBAeJNo == qIjoLGZnlo){GNLqVDdJpA = true;}
      if(diHZHJrWcm == dOytEDxxmM){YreTmtNxgk = true;}
      else if(dOytEDxxmM == diHZHJrWcm){YHCJfDrBkO = true;}
      if(JhczjwPLAr == MdRGVpgwVI){LOgKZXmeqj = true;}
      else if(MdRGVpgwVI == JhczjwPLAr){ZEKpOqkfPC = true;}
      if(qodqNIBIuY == lUBOnpUSoG){QLENHnWHuR = true;}
      else if(lUBOnpUSoG == qodqNIBIuY){yUJcWdDxcW = true;}
      if(wFDMMZkcwJ == FRLIaNSIad){HGCkWufXps = true;}
      else if(FRLIaNSIad == wFDMMZkcwJ){HcsGwcdJou = true;}
      if(kGNEsIfkEP == jTWCLqCKaK){JfYTGkCpnY = true;}
      else if(jTWCLqCKaK == kGNEsIfkEP){iFFVkCDUbe = true;}
      if(pNntxnEQLz == SinFDJNiGN){SfzLAMnRMz = true;}
      else if(SinFDJNiGN == pNntxnEQLz){SxsnCExYlC = true;}
      if(HjbDqDeQmJ == heIfGtSJeH){XFCPdFLumd = true;}
      if(LlPpHkbZyF == XYUqXSxyCw){rOnyZkmjHV = true;}
      if(cQDehhRJOX == nKqdnWcGFR){kfTVzaGqkK = true;}
      while(heIfGtSJeH == HjbDqDeQmJ){ztYOHwKDsk = true;}
      while(XYUqXSxyCw == XYUqXSxyCw){MapUTsOmrT = true;}
      while(nKqdnWcGFR == nKqdnWcGFR){ZhUxEJjFEr = true;}
      if(AjBNwFKquQ == true){AjBNwFKquQ = false;}
      if(YreTmtNxgk == true){YreTmtNxgk = false;}
      if(LOgKZXmeqj == true){LOgKZXmeqj = false;}
      if(QLENHnWHuR == true){QLENHnWHuR = false;}
      if(HGCkWufXps == true){HGCkWufXps = false;}
      if(JfYTGkCpnY == true){JfYTGkCpnY = false;}
      if(SfzLAMnRMz == true){SfzLAMnRMz = false;}
      if(XFCPdFLumd == true){XFCPdFLumd = false;}
      if(rOnyZkmjHV == true){rOnyZkmjHV = false;}
      if(kfTVzaGqkK == true){kfTVzaGqkK = false;}
      if(GNLqVDdJpA == true){GNLqVDdJpA = false;}
      if(YHCJfDrBkO == true){YHCJfDrBkO = false;}
      if(ZEKpOqkfPC == true){ZEKpOqkfPC = false;}
      if(yUJcWdDxcW == true){yUJcWdDxcW = false;}
      if(HcsGwcdJou == true){HcsGwcdJou = false;}
      if(iFFVkCDUbe == true){iFFVkCDUbe = false;}
      if(SxsnCExYlC == true){SxsnCExYlC = false;}
      if(ztYOHwKDsk == true){ztYOHwKDsk = false;}
      if(MapUTsOmrT == true){MapUTsOmrT = false;}
      if(ZhUxEJjFEr == true){ZhUxEJjFEr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CEHUAVCLME
{ 
  void NNPCcheeCW()
  { 
      bool okANognqjl = false;
      bool yDJsyOOJzA = false;
      bool UoKpRnSOmV = false;
      bool fwKXdMaLCD = false;
      bool EoyrpaphEF = false;
      bool AAbPdAZJwA = false;
      bool OYENFCrlOk = false;
      bool nCHuwfpSzp = false;
      bool xkKgVfTusd = false;
      bool mQPBoekjlm = false;
      bool hESTRxsgTy = false;
      bool JHJFCcOXrZ = false;
      bool ixrkyXmFGQ = false;
      bool tGfMIsSpOX = false;
      bool mmatTeGKyL = false;
      bool PMqMEjMgVs = false;
      bool KmZCEDaxwJ = false;
      bool KYITlwVyQS = false;
      bool QbHtAgOTHX = false;
      bool glUVNAMYpQ = false;
      string VUpNtDJaAE;
      string QQHUxJufds;
      string hphEKVxuoZ;
      string qeZUObKWjG;
      string XJrVRuBLOT;
      string TRuRRfmkDX;
      string GOlZNlpmGU;
      string yYuWVXyLmO;
      string UkgUGZjHDi;
      string nYSMAIXRIe;
      string ENEsVuWXws;
      string gaynDVhRSm;
      string CijXgYFhWM;
      string zfDIKHfmzK;
      string CLLJBNadJe;
      string aGzUcVcfMw;
      string pnBjsBXpdu;
      string otRHjpXZWS;
      string yaYrksgien;
      string dAaCUOJaPz;
      if(VUpNtDJaAE == ENEsVuWXws){okANognqjl = true;}
      else if(ENEsVuWXws == VUpNtDJaAE){hESTRxsgTy = true;}
      if(QQHUxJufds == gaynDVhRSm){yDJsyOOJzA = true;}
      else if(gaynDVhRSm == QQHUxJufds){JHJFCcOXrZ = true;}
      if(hphEKVxuoZ == CijXgYFhWM){UoKpRnSOmV = true;}
      else if(CijXgYFhWM == hphEKVxuoZ){ixrkyXmFGQ = true;}
      if(qeZUObKWjG == zfDIKHfmzK){fwKXdMaLCD = true;}
      else if(zfDIKHfmzK == qeZUObKWjG){tGfMIsSpOX = true;}
      if(XJrVRuBLOT == CLLJBNadJe){EoyrpaphEF = true;}
      else if(CLLJBNadJe == XJrVRuBLOT){mmatTeGKyL = true;}
      if(TRuRRfmkDX == aGzUcVcfMw){AAbPdAZJwA = true;}
      else if(aGzUcVcfMw == TRuRRfmkDX){PMqMEjMgVs = true;}
      if(GOlZNlpmGU == pnBjsBXpdu){OYENFCrlOk = true;}
      else if(pnBjsBXpdu == GOlZNlpmGU){KmZCEDaxwJ = true;}
      if(yYuWVXyLmO == otRHjpXZWS){nCHuwfpSzp = true;}
      if(UkgUGZjHDi == yaYrksgien){xkKgVfTusd = true;}
      if(nYSMAIXRIe == dAaCUOJaPz){mQPBoekjlm = true;}
      while(otRHjpXZWS == yYuWVXyLmO){KYITlwVyQS = true;}
      while(yaYrksgien == yaYrksgien){QbHtAgOTHX = true;}
      while(dAaCUOJaPz == dAaCUOJaPz){glUVNAMYpQ = true;}
      if(okANognqjl == true){okANognqjl = false;}
      if(yDJsyOOJzA == true){yDJsyOOJzA = false;}
      if(UoKpRnSOmV == true){UoKpRnSOmV = false;}
      if(fwKXdMaLCD == true){fwKXdMaLCD = false;}
      if(EoyrpaphEF == true){EoyrpaphEF = false;}
      if(AAbPdAZJwA == true){AAbPdAZJwA = false;}
      if(OYENFCrlOk == true){OYENFCrlOk = false;}
      if(nCHuwfpSzp == true){nCHuwfpSzp = false;}
      if(xkKgVfTusd == true){xkKgVfTusd = false;}
      if(mQPBoekjlm == true){mQPBoekjlm = false;}
      if(hESTRxsgTy == true){hESTRxsgTy = false;}
      if(JHJFCcOXrZ == true){JHJFCcOXrZ = false;}
      if(ixrkyXmFGQ == true){ixrkyXmFGQ = false;}
      if(tGfMIsSpOX == true){tGfMIsSpOX = false;}
      if(mmatTeGKyL == true){mmatTeGKyL = false;}
      if(PMqMEjMgVs == true){PMqMEjMgVs = false;}
      if(KmZCEDaxwJ == true){KmZCEDaxwJ = false;}
      if(KYITlwVyQS == true){KYITlwVyQS = false;}
      if(QbHtAgOTHX == true){QbHtAgOTHX = false;}
      if(glUVNAMYpQ == true){glUVNAMYpQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AFNMLHNKIH
{ 
  void AgHhsGbHOd()
  { 
      bool RZzWoehOhA = false;
      bool qEtcgmsXuR = false;
      bool HmtqMgdZjf = false;
      bool nHyTEarCpO = false;
      bool jkeTEXdYUr = false;
      bool WcJhMdfHKH = false;
      bool BHdCMjGaXF = false;
      bool tphfhWHZlo = false;
      bool CEFqIKxQHZ = false;
      bool ukriMbGcHU = false;
      bool QDAOyfudzp = false;
      bool WGVUExBlsC = false;
      bool mpTyKJyySF = false;
      bool PdSRYzDqsc = false;
      bool OTQQDoPWdP = false;
      bool ZTjEhZjCDn = false;
      bool gwKtZsnDwF = false;
      bool sKrPmTZCuV = false;
      bool taUDewtNjy = false;
      bool PBmFuRIVpJ = false;
      string OGsVdutWjd;
      string igrKrAjsMN;
      string yqSSUncYwl;
      string NBjKjuqcYc;
      string OyEWUIUXjj;
      string QZPtMXmZAp;
      string SVZxQgxgaw;
      string IGUjyAlwyL;
      string TEnMVmkpxM;
      string IQbiJrXHGm;
      string LmxmaKEeuM;
      string kpaoVNgNbc;
      string wHiOnqelaF;
      string bepLAfHBkL;
      string hGtkaRpmMu;
      string LKecqEDhzi;
      string eSEojGAPno;
      string GfbQupMynV;
      string BrZftRzNUw;
      string cYCBfPBFAT;
      if(OGsVdutWjd == LmxmaKEeuM){RZzWoehOhA = true;}
      else if(LmxmaKEeuM == OGsVdutWjd){QDAOyfudzp = true;}
      if(igrKrAjsMN == kpaoVNgNbc){qEtcgmsXuR = true;}
      else if(kpaoVNgNbc == igrKrAjsMN){WGVUExBlsC = true;}
      if(yqSSUncYwl == wHiOnqelaF){HmtqMgdZjf = true;}
      else if(wHiOnqelaF == yqSSUncYwl){mpTyKJyySF = true;}
      if(NBjKjuqcYc == bepLAfHBkL){nHyTEarCpO = true;}
      else if(bepLAfHBkL == NBjKjuqcYc){PdSRYzDqsc = true;}
      if(OyEWUIUXjj == hGtkaRpmMu){jkeTEXdYUr = true;}
      else if(hGtkaRpmMu == OyEWUIUXjj){OTQQDoPWdP = true;}
      if(QZPtMXmZAp == LKecqEDhzi){WcJhMdfHKH = true;}
      else if(LKecqEDhzi == QZPtMXmZAp){ZTjEhZjCDn = true;}
      if(SVZxQgxgaw == eSEojGAPno){BHdCMjGaXF = true;}
      else if(eSEojGAPno == SVZxQgxgaw){gwKtZsnDwF = true;}
      if(IGUjyAlwyL == GfbQupMynV){tphfhWHZlo = true;}
      if(TEnMVmkpxM == BrZftRzNUw){CEFqIKxQHZ = true;}
      if(IQbiJrXHGm == cYCBfPBFAT){ukriMbGcHU = true;}
      while(GfbQupMynV == IGUjyAlwyL){sKrPmTZCuV = true;}
      while(BrZftRzNUw == BrZftRzNUw){taUDewtNjy = true;}
      while(cYCBfPBFAT == cYCBfPBFAT){PBmFuRIVpJ = true;}
      if(RZzWoehOhA == true){RZzWoehOhA = false;}
      if(qEtcgmsXuR == true){qEtcgmsXuR = false;}
      if(HmtqMgdZjf == true){HmtqMgdZjf = false;}
      if(nHyTEarCpO == true){nHyTEarCpO = false;}
      if(jkeTEXdYUr == true){jkeTEXdYUr = false;}
      if(WcJhMdfHKH == true){WcJhMdfHKH = false;}
      if(BHdCMjGaXF == true){BHdCMjGaXF = false;}
      if(tphfhWHZlo == true){tphfhWHZlo = false;}
      if(CEFqIKxQHZ == true){CEFqIKxQHZ = false;}
      if(ukriMbGcHU == true){ukriMbGcHU = false;}
      if(QDAOyfudzp == true){QDAOyfudzp = false;}
      if(WGVUExBlsC == true){WGVUExBlsC = false;}
      if(mpTyKJyySF == true){mpTyKJyySF = false;}
      if(PdSRYzDqsc == true){PdSRYzDqsc = false;}
      if(OTQQDoPWdP == true){OTQQDoPWdP = false;}
      if(ZTjEhZjCDn == true){ZTjEhZjCDn = false;}
      if(gwKtZsnDwF == true){gwKtZsnDwF = false;}
      if(sKrPmTZCuV == true){sKrPmTZCuV = false;}
      if(taUDewtNjy == true){taUDewtNjy = false;}
      if(PBmFuRIVpJ == true){PBmFuRIVpJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JZZVLKKNSJ
{ 
  void OnTDAljfJU()
  { 
      bool WOSlWeVEuS = false;
      bool nJHbkUurhB = false;
      bool akrZEFCtxO = false;
      bool XJqjlMopuZ = false;
      bool QUEzdtkqfz = false;
      bool tkaKKlWrgQ = false;
      bool caHgueRWoX = false;
      bool fExHkGgruK = false;
      bool UKNxTlhgZA = false;
      bool pwJdxoMWEz = false;
      bool bNBITpnTYE = false;
      bool EewWwRMKMI = false;
      bool xkxohiuSJu = false;
      bool sJmwiGIFcd = false;
      bool xOIUwKzmge = false;
      bool bCKuCqQMZj = false;
      bool tVJcLtqAmp = false;
      bool JHgiKhcbsW = false;
      bool jIkdTpzqtq = false;
      bool owesibEeJB = false;
      string RUneYgRYDY;
      string wWWSOBqUEB;
      string AiPoSPzdnr;
      string wRSJUAYrdZ;
      string QIyuoXflSs;
      string wlddAiFyMJ;
      string hmkLcdDNxN;
      string czqejqjTzt;
      string iMKuuJmoJl;
      string uZeTqdXmSL;
      string URoEPxuysI;
      string ylzSZVbpPS;
      string pNEKSCTWnG;
      string TxAnZQWFey;
      string OnuAnIaLtV;
      string BgWAUGNdlN;
      string cXKmnBkLsI;
      string yVLREBRDWJ;
      string bHcSFlZASS;
      string DrTQUpdIMl;
      if(RUneYgRYDY == URoEPxuysI){WOSlWeVEuS = true;}
      else if(URoEPxuysI == RUneYgRYDY){bNBITpnTYE = true;}
      if(wWWSOBqUEB == ylzSZVbpPS){nJHbkUurhB = true;}
      else if(ylzSZVbpPS == wWWSOBqUEB){EewWwRMKMI = true;}
      if(AiPoSPzdnr == pNEKSCTWnG){akrZEFCtxO = true;}
      else if(pNEKSCTWnG == AiPoSPzdnr){xkxohiuSJu = true;}
      if(wRSJUAYrdZ == TxAnZQWFey){XJqjlMopuZ = true;}
      else if(TxAnZQWFey == wRSJUAYrdZ){sJmwiGIFcd = true;}
      if(QIyuoXflSs == OnuAnIaLtV){QUEzdtkqfz = true;}
      else if(OnuAnIaLtV == QIyuoXflSs){xOIUwKzmge = true;}
      if(wlddAiFyMJ == BgWAUGNdlN){tkaKKlWrgQ = true;}
      else if(BgWAUGNdlN == wlddAiFyMJ){bCKuCqQMZj = true;}
      if(hmkLcdDNxN == cXKmnBkLsI){caHgueRWoX = true;}
      else if(cXKmnBkLsI == hmkLcdDNxN){tVJcLtqAmp = true;}
      if(czqejqjTzt == yVLREBRDWJ){fExHkGgruK = true;}
      if(iMKuuJmoJl == bHcSFlZASS){UKNxTlhgZA = true;}
      if(uZeTqdXmSL == DrTQUpdIMl){pwJdxoMWEz = true;}
      while(yVLREBRDWJ == czqejqjTzt){JHgiKhcbsW = true;}
      while(bHcSFlZASS == bHcSFlZASS){jIkdTpzqtq = true;}
      while(DrTQUpdIMl == DrTQUpdIMl){owesibEeJB = true;}
      if(WOSlWeVEuS == true){WOSlWeVEuS = false;}
      if(nJHbkUurhB == true){nJHbkUurhB = false;}
      if(akrZEFCtxO == true){akrZEFCtxO = false;}
      if(XJqjlMopuZ == true){XJqjlMopuZ = false;}
      if(QUEzdtkqfz == true){QUEzdtkqfz = false;}
      if(tkaKKlWrgQ == true){tkaKKlWrgQ = false;}
      if(caHgueRWoX == true){caHgueRWoX = false;}
      if(fExHkGgruK == true){fExHkGgruK = false;}
      if(UKNxTlhgZA == true){UKNxTlhgZA = false;}
      if(pwJdxoMWEz == true){pwJdxoMWEz = false;}
      if(bNBITpnTYE == true){bNBITpnTYE = false;}
      if(EewWwRMKMI == true){EewWwRMKMI = false;}
      if(xkxohiuSJu == true){xkxohiuSJu = false;}
      if(sJmwiGIFcd == true){sJmwiGIFcd = false;}
      if(xOIUwKzmge == true){xOIUwKzmge = false;}
      if(bCKuCqQMZj == true){bCKuCqQMZj = false;}
      if(tVJcLtqAmp == true){tVJcLtqAmp = false;}
      if(JHgiKhcbsW == true){JHgiKhcbsW = false;}
      if(jIkdTpzqtq == true){jIkdTpzqtq = false;}
      if(owesibEeJB == true){owesibEeJB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVMKRGSAEW
{ 
  void xQATqTRsKa()
  { 
      bool pbzJYdTShc = false;
      bool yJxojiArNc = false;
      bool nnPqjSLqWs = false;
      bool kkMXaOIFtT = false;
      bool gCBphOVgIR = false;
      bool ODNaJBLHZG = false;
      bool SbwoqNxZOU = false;
      bool atxtulmZIU = false;
      bool wdiEdhXkOZ = false;
      bool CAfnAEGMzU = false;
      bool RwSnpUFSfX = false;
      bool OlyEJnsqKJ = false;
      bool pMLnRaNJsp = false;
      bool eaanCzKuNJ = false;
      bool bEEpKQBaeM = false;
      bool LOCpdFkdVP = false;
      bool GwZornLKBJ = false;
      bool dycAgkHUdB = false;
      bool YldgeQXkJx = false;
      bool OfYyDedPyW = false;
      string cyQcBeVzZx;
      string DIoNGnXPCf;
      string YswYLTbtyz;
      string hKFUKOOFHm;
      string zJdstKtwdB;
      string nFIAAjBqQg;
      string CaAZPrCTCr;
      string YSHPgPPDeA;
      string YePwLbBFTa;
      string MWnZjXIEdB;
      string IZslcUxrTk;
      string UyMQHXLENm;
      string qxzbeBehfI;
      string GKZcrzkcTq;
      string eIkiGOKXRL;
      string LEppKKZRGa;
      string pPMKeJXiYI;
      string lhjWIhLQUQ;
      string qHPTxBUiSg;
      string YTWrAOwaEx;
      if(cyQcBeVzZx == IZslcUxrTk){pbzJYdTShc = true;}
      else if(IZslcUxrTk == cyQcBeVzZx){RwSnpUFSfX = true;}
      if(DIoNGnXPCf == UyMQHXLENm){yJxojiArNc = true;}
      else if(UyMQHXLENm == DIoNGnXPCf){OlyEJnsqKJ = true;}
      if(YswYLTbtyz == qxzbeBehfI){nnPqjSLqWs = true;}
      else if(qxzbeBehfI == YswYLTbtyz){pMLnRaNJsp = true;}
      if(hKFUKOOFHm == GKZcrzkcTq){kkMXaOIFtT = true;}
      else if(GKZcrzkcTq == hKFUKOOFHm){eaanCzKuNJ = true;}
      if(zJdstKtwdB == eIkiGOKXRL){gCBphOVgIR = true;}
      else if(eIkiGOKXRL == zJdstKtwdB){bEEpKQBaeM = true;}
      if(nFIAAjBqQg == LEppKKZRGa){ODNaJBLHZG = true;}
      else if(LEppKKZRGa == nFIAAjBqQg){LOCpdFkdVP = true;}
      if(CaAZPrCTCr == pPMKeJXiYI){SbwoqNxZOU = true;}
      else if(pPMKeJXiYI == CaAZPrCTCr){GwZornLKBJ = true;}
      if(YSHPgPPDeA == lhjWIhLQUQ){atxtulmZIU = true;}
      if(YePwLbBFTa == qHPTxBUiSg){wdiEdhXkOZ = true;}
      if(MWnZjXIEdB == YTWrAOwaEx){CAfnAEGMzU = true;}
      while(lhjWIhLQUQ == YSHPgPPDeA){dycAgkHUdB = true;}
      while(qHPTxBUiSg == qHPTxBUiSg){YldgeQXkJx = true;}
      while(YTWrAOwaEx == YTWrAOwaEx){OfYyDedPyW = true;}
      if(pbzJYdTShc == true){pbzJYdTShc = false;}
      if(yJxojiArNc == true){yJxojiArNc = false;}
      if(nnPqjSLqWs == true){nnPqjSLqWs = false;}
      if(kkMXaOIFtT == true){kkMXaOIFtT = false;}
      if(gCBphOVgIR == true){gCBphOVgIR = false;}
      if(ODNaJBLHZG == true){ODNaJBLHZG = false;}
      if(SbwoqNxZOU == true){SbwoqNxZOU = false;}
      if(atxtulmZIU == true){atxtulmZIU = false;}
      if(wdiEdhXkOZ == true){wdiEdhXkOZ = false;}
      if(CAfnAEGMzU == true){CAfnAEGMzU = false;}
      if(RwSnpUFSfX == true){RwSnpUFSfX = false;}
      if(OlyEJnsqKJ == true){OlyEJnsqKJ = false;}
      if(pMLnRaNJsp == true){pMLnRaNJsp = false;}
      if(eaanCzKuNJ == true){eaanCzKuNJ = false;}
      if(bEEpKQBaeM == true){bEEpKQBaeM = false;}
      if(LOCpdFkdVP == true){LOCpdFkdVP = false;}
      if(GwZornLKBJ == true){GwZornLKBJ = false;}
      if(dycAgkHUdB == true){dycAgkHUdB = false;}
      if(YldgeQXkJx == true){YldgeQXkJx = false;}
      if(OfYyDedPyW == true){OfYyDedPyW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YEYYNWRNGS
{ 
  void pjSOhuzfeR()
  { 
      bool UYrkAHfLJu = false;
      bool TlhonYKizm = false;
      bool XNDqHsAesC = false;
      bool hpqfyiCWRD = false;
      bool YfAzyOVNEy = false;
      bool MCzfcHUAdH = false;
      bool GBSHNcuCqE = false;
      bool VmQwNrMDrs = false;
      bool XmZtoepKCq = false;
      bool NBsKwWNslV = false;
      bool SSVAcZkDRk = false;
      bool tRIkiTbXRi = false;
      bool lkAAqTsGzp = false;
      bool dTRWZEQYRP = false;
      bool smrRxwsIac = false;
      bool uobCihSVJI = false;
      bool feDaGZzkKd = false;
      bool CCGBpzriCt = false;
      bool ZkeWunqOnr = false;
      bool ltPJjNiRKW = false;
      string CdKKeqYebA;
      string VMRqzlrPwQ;
      string PLRSnLscDJ;
      string aHUkrYYJQO;
      string UqEXkCxMwn;
      string ARAcZqMqWS;
      string yuaSYOrfzZ;
      string MiyhuYGshk;
      string NggPJJGqLB;
      string MglxPZPlzW;
      string JQNVaQTSgA;
      string jSJkEROLJP;
      string HAUyNewARV;
      string IUtKbxTKnr;
      string pmKKQtXBry;
      string KDciPJwPIu;
      string TSBKrPYyJH;
      string xDWQZTpJgT;
      string HuHSKFqKuR;
      string AECrXWlzSB;
      if(CdKKeqYebA == JQNVaQTSgA){UYrkAHfLJu = true;}
      else if(JQNVaQTSgA == CdKKeqYebA){SSVAcZkDRk = true;}
      if(VMRqzlrPwQ == jSJkEROLJP){TlhonYKizm = true;}
      else if(jSJkEROLJP == VMRqzlrPwQ){tRIkiTbXRi = true;}
      if(PLRSnLscDJ == HAUyNewARV){XNDqHsAesC = true;}
      else if(HAUyNewARV == PLRSnLscDJ){lkAAqTsGzp = true;}
      if(aHUkrYYJQO == IUtKbxTKnr){hpqfyiCWRD = true;}
      else if(IUtKbxTKnr == aHUkrYYJQO){dTRWZEQYRP = true;}
      if(UqEXkCxMwn == pmKKQtXBry){YfAzyOVNEy = true;}
      else if(pmKKQtXBry == UqEXkCxMwn){smrRxwsIac = true;}
      if(ARAcZqMqWS == KDciPJwPIu){MCzfcHUAdH = true;}
      else if(KDciPJwPIu == ARAcZqMqWS){uobCihSVJI = true;}
      if(yuaSYOrfzZ == TSBKrPYyJH){GBSHNcuCqE = true;}
      else if(TSBKrPYyJH == yuaSYOrfzZ){feDaGZzkKd = true;}
      if(MiyhuYGshk == xDWQZTpJgT){VmQwNrMDrs = true;}
      if(NggPJJGqLB == HuHSKFqKuR){XmZtoepKCq = true;}
      if(MglxPZPlzW == AECrXWlzSB){NBsKwWNslV = true;}
      while(xDWQZTpJgT == MiyhuYGshk){CCGBpzriCt = true;}
      while(HuHSKFqKuR == HuHSKFqKuR){ZkeWunqOnr = true;}
      while(AECrXWlzSB == AECrXWlzSB){ltPJjNiRKW = true;}
      if(UYrkAHfLJu == true){UYrkAHfLJu = false;}
      if(TlhonYKizm == true){TlhonYKizm = false;}
      if(XNDqHsAesC == true){XNDqHsAesC = false;}
      if(hpqfyiCWRD == true){hpqfyiCWRD = false;}
      if(YfAzyOVNEy == true){YfAzyOVNEy = false;}
      if(MCzfcHUAdH == true){MCzfcHUAdH = false;}
      if(GBSHNcuCqE == true){GBSHNcuCqE = false;}
      if(VmQwNrMDrs == true){VmQwNrMDrs = false;}
      if(XmZtoepKCq == true){XmZtoepKCq = false;}
      if(NBsKwWNslV == true){NBsKwWNslV = false;}
      if(SSVAcZkDRk == true){SSVAcZkDRk = false;}
      if(tRIkiTbXRi == true){tRIkiTbXRi = false;}
      if(lkAAqTsGzp == true){lkAAqTsGzp = false;}
      if(dTRWZEQYRP == true){dTRWZEQYRP = false;}
      if(smrRxwsIac == true){smrRxwsIac = false;}
      if(uobCihSVJI == true){uobCihSVJI = false;}
      if(feDaGZzkKd == true){feDaGZzkKd = false;}
      if(CCGBpzriCt == true){CCGBpzriCt = false;}
      if(ZkeWunqOnr == true){ZkeWunqOnr = false;}
      if(ltPJjNiRKW == true){ltPJjNiRKW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XLIBPJNJAF
{ 
  void CrhtKIYabo()
  { 
      bool fHTfAfWmpN = false;
      bool KxXKucFxdn = false;
      bool ieyiozEWjT = false;
      bool igLVGTSinG = false;
      bool FVnSEZhpUB = false;
      bool UWUHoBJkpB = false;
      bool bzCWeckCDa = false;
      bool KVIXhMpedP = false;
      bool QNBiyLMDfE = false;
      bool KgrmdFTQna = false;
      bool nfltpzNwYb = false;
      bool KdGajNxSYS = false;
      bool QhVzQcdVsb = false;
      bool sYqDakaHrz = false;
      bool yPdDsgaRCQ = false;
      bool IArVKGJmcN = false;
      bool UrDwillDzz = false;
      bool lpZZUADRFi = false;
      bool CLTcTsfVrU = false;
      bool amdedFMhUH = false;
      string rmleDfHtsz;
      string oBjcTozNjW;
      string SOYofMFjpQ;
      string ntCxycLVXI;
      string LqojTlLGOP;
      string zRHyfcNxyp;
      string aXDbKuzleq;
      string ccpbKaYnVs;
      string ByUaRWlDRU;
      string OOWhgmmNYY;
      string mYbXlVbfnE;
      string EYbEobCcKn;
      string IwUKbOFHtW;
      string mLPwGbWxnu;
      string tFPMQomSsF;
      string kKCjPqERwX;
      string QTlQQrJeyM;
      string EFnPtCgHsl;
      string bmOolcJefO;
      string WFAQeZTzwX;
      if(rmleDfHtsz == mYbXlVbfnE){fHTfAfWmpN = true;}
      else if(mYbXlVbfnE == rmleDfHtsz){nfltpzNwYb = true;}
      if(oBjcTozNjW == EYbEobCcKn){KxXKucFxdn = true;}
      else if(EYbEobCcKn == oBjcTozNjW){KdGajNxSYS = true;}
      if(SOYofMFjpQ == IwUKbOFHtW){ieyiozEWjT = true;}
      else if(IwUKbOFHtW == SOYofMFjpQ){QhVzQcdVsb = true;}
      if(ntCxycLVXI == mLPwGbWxnu){igLVGTSinG = true;}
      else if(mLPwGbWxnu == ntCxycLVXI){sYqDakaHrz = true;}
      if(LqojTlLGOP == tFPMQomSsF){FVnSEZhpUB = true;}
      else if(tFPMQomSsF == LqojTlLGOP){yPdDsgaRCQ = true;}
      if(zRHyfcNxyp == kKCjPqERwX){UWUHoBJkpB = true;}
      else if(kKCjPqERwX == zRHyfcNxyp){IArVKGJmcN = true;}
      if(aXDbKuzleq == QTlQQrJeyM){bzCWeckCDa = true;}
      else if(QTlQQrJeyM == aXDbKuzleq){UrDwillDzz = true;}
      if(ccpbKaYnVs == EFnPtCgHsl){KVIXhMpedP = true;}
      if(ByUaRWlDRU == bmOolcJefO){QNBiyLMDfE = true;}
      if(OOWhgmmNYY == WFAQeZTzwX){KgrmdFTQna = true;}
      while(EFnPtCgHsl == ccpbKaYnVs){lpZZUADRFi = true;}
      while(bmOolcJefO == bmOolcJefO){CLTcTsfVrU = true;}
      while(WFAQeZTzwX == WFAQeZTzwX){amdedFMhUH = true;}
      if(fHTfAfWmpN == true){fHTfAfWmpN = false;}
      if(KxXKucFxdn == true){KxXKucFxdn = false;}
      if(ieyiozEWjT == true){ieyiozEWjT = false;}
      if(igLVGTSinG == true){igLVGTSinG = false;}
      if(FVnSEZhpUB == true){FVnSEZhpUB = false;}
      if(UWUHoBJkpB == true){UWUHoBJkpB = false;}
      if(bzCWeckCDa == true){bzCWeckCDa = false;}
      if(KVIXhMpedP == true){KVIXhMpedP = false;}
      if(QNBiyLMDfE == true){QNBiyLMDfE = false;}
      if(KgrmdFTQna == true){KgrmdFTQna = false;}
      if(nfltpzNwYb == true){nfltpzNwYb = false;}
      if(KdGajNxSYS == true){KdGajNxSYS = false;}
      if(QhVzQcdVsb == true){QhVzQcdVsb = false;}
      if(sYqDakaHrz == true){sYqDakaHrz = false;}
      if(yPdDsgaRCQ == true){yPdDsgaRCQ = false;}
      if(IArVKGJmcN == true){IArVKGJmcN = false;}
      if(UrDwillDzz == true){UrDwillDzz = false;}
      if(lpZZUADRFi == true){lpZZUADRFi = false;}
      if(CLTcTsfVrU == true){CLTcTsfVrU = false;}
      if(amdedFMhUH == true){amdedFMhUH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UNLCOASTJG
{ 
  void YqDRKFzKgq()
  { 
      bool crBcYNJPHE = false;
      bool CyyGibjYBe = false;
      bool zBgCqZXLUe = false;
      bool iazGhMgKCr = false;
      bool alznkBRiwe = false;
      bool zuguIbLzky = false;
      bool pxubUbzqYV = false;
      bool tYWIEMBrQo = false;
      bool InPofmsDyF = false;
      bool BhZDBcqXSI = false;
      bool CZKZjZYXpu = false;
      bool aShupBhFug = false;
      bool husSUMzSGb = false;
      bool UcYImhdoFG = false;
      bool OUNCehAeMA = false;
      bool tlckaGgqEW = false;
      bool ZFROZxsZHI = false;
      bool XrAoSMhpml = false;
      bool MUGGgiAmgf = false;
      bool AlkhfIDzbg = false;
      string fUuHkQupmQ;
      string DemJwHsLpR;
      string rGPqEFgEBs;
      string KWzhebtkQR;
      string mycwLrsQhX;
      string rZNTsYEECe;
      string iqnsFgfEeT;
      string MHtXdtcTeM;
      string MPVdBkIfoF;
      string WphlhwJipe;
      string LnlOKjeooz;
      string ukYpRTUJrU;
      string XzPYwVZHoh;
      string jscAAYcHTQ;
      string GTppJkQqUO;
      string aAqVHMXNRn;
      string KWzHOCIYpr;
      string pNpaODJZOK;
      string FhmaGjCHrn;
      string APoeGiThaH;
      if(fUuHkQupmQ == LnlOKjeooz){crBcYNJPHE = true;}
      else if(LnlOKjeooz == fUuHkQupmQ){CZKZjZYXpu = true;}
      if(DemJwHsLpR == ukYpRTUJrU){CyyGibjYBe = true;}
      else if(ukYpRTUJrU == DemJwHsLpR){aShupBhFug = true;}
      if(rGPqEFgEBs == XzPYwVZHoh){zBgCqZXLUe = true;}
      else if(XzPYwVZHoh == rGPqEFgEBs){husSUMzSGb = true;}
      if(KWzhebtkQR == jscAAYcHTQ){iazGhMgKCr = true;}
      else if(jscAAYcHTQ == KWzhebtkQR){UcYImhdoFG = true;}
      if(mycwLrsQhX == GTppJkQqUO){alznkBRiwe = true;}
      else if(GTppJkQqUO == mycwLrsQhX){OUNCehAeMA = true;}
      if(rZNTsYEECe == aAqVHMXNRn){zuguIbLzky = true;}
      else if(aAqVHMXNRn == rZNTsYEECe){tlckaGgqEW = true;}
      if(iqnsFgfEeT == KWzHOCIYpr){pxubUbzqYV = true;}
      else if(KWzHOCIYpr == iqnsFgfEeT){ZFROZxsZHI = true;}
      if(MHtXdtcTeM == pNpaODJZOK){tYWIEMBrQo = true;}
      if(MPVdBkIfoF == FhmaGjCHrn){InPofmsDyF = true;}
      if(WphlhwJipe == APoeGiThaH){BhZDBcqXSI = true;}
      while(pNpaODJZOK == MHtXdtcTeM){XrAoSMhpml = true;}
      while(FhmaGjCHrn == FhmaGjCHrn){MUGGgiAmgf = true;}
      while(APoeGiThaH == APoeGiThaH){AlkhfIDzbg = true;}
      if(crBcYNJPHE == true){crBcYNJPHE = false;}
      if(CyyGibjYBe == true){CyyGibjYBe = false;}
      if(zBgCqZXLUe == true){zBgCqZXLUe = false;}
      if(iazGhMgKCr == true){iazGhMgKCr = false;}
      if(alznkBRiwe == true){alznkBRiwe = false;}
      if(zuguIbLzky == true){zuguIbLzky = false;}
      if(pxubUbzqYV == true){pxubUbzqYV = false;}
      if(tYWIEMBrQo == true){tYWIEMBrQo = false;}
      if(InPofmsDyF == true){InPofmsDyF = false;}
      if(BhZDBcqXSI == true){BhZDBcqXSI = false;}
      if(CZKZjZYXpu == true){CZKZjZYXpu = false;}
      if(aShupBhFug == true){aShupBhFug = false;}
      if(husSUMzSGb == true){husSUMzSGb = false;}
      if(UcYImhdoFG == true){UcYImhdoFG = false;}
      if(OUNCehAeMA == true){OUNCehAeMA = false;}
      if(tlckaGgqEW == true){tlckaGgqEW = false;}
      if(ZFROZxsZHI == true){ZFROZxsZHI = false;}
      if(XrAoSMhpml == true){XrAoSMhpml = false;}
      if(MUGGgiAmgf == true){MUGGgiAmgf = false;}
      if(AlkhfIDzbg == true){AlkhfIDzbg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUTNCTYFIN
{ 
  void hkCDXNBtrU()
  { 
      bool zANbUkisxj = false;
      bool GMwfzYplMT = false;
      bool VSIyQMirLC = false;
      bool QyPKBaIbVH = false;
      bool EARbGmLHlN = false;
      bool kROfRfrPLH = false;
      bool BphtTHwldY = false;
      bool PNQEPVAfqc = false;
      bool AbGxRziisU = false;
      bool hsQNGNRXIz = false;
      bool pZdNxXAKQu = false;
      bool eLXhHZjjcT = false;
      bool YNsIpWwCyB = false;
      bool DcXrmaxsAs = false;
      bool yYSxpWUhGf = false;
      bool dgtnZcgVWZ = false;
      bool axLOqCmfuf = false;
      bool bqjiVzuuSS = false;
      bool BNwRWVhjRK = false;
      bool tbVZSAMDGm = false;
      string xBTClbalEu;
      string coQUwOwlfe;
      string kmHNORDwKw;
      string jotcODMTFl;
      string dfenrhnDKZ;
      string VWBHMJtGmU;
      string YdbHLmtnGs;
      string CcgsAFITUg;
      string cAljaMmmPE;
      string JGfjNzEXbE;
      string mAwQWrpHGH;
      string BakFrYqqfz;
      string AGXBjwwweA;
      string AkqQtbDUMh;
      string VfgHDhUZro;
      string HMqbEfctga;
      string utbFHPiULP;
      string UWdxdTZPyB;
      string aWEpsmsPLN;
      string zImllaDbAm;
      if(xBTClbalEu == mAwQWrpHGH){zANbUkisxj = true;}
      else if(mAwQWrpHGH == xBTClbalEu){pZdNxXAKQu = true;}
      if(coQUwOwlfe == BakFrYqqfz){GMwfzYplMT = true;}
      else if(BakFrYqqfz == coQUwOwlfe){eLXhHZjjcT = true;}
      if(kmHNORDwKw == AGXBjwwweA){VSIyQMirLC = true;}
      else if(AGXBjwwweA == kmHNORDwKw){YNsIpWwCyB = true;}
      if(jotcODMTFl == AkqQtbDUMh){QyPKBaIbVH = true;}
      else if(AkqQtbDUMh == jotcODMTFl){DcXrmaxsAs = true;}
      if(dfenrhnDKZ == VfgHDhUZro){EARbGmLHlN = true;}
      else if(VfgHDhUZro == dfenrhnDKZ){yYSxpWUhGf = true;}
      if(VWBHMJtGmU == HMqbEfctga){kROfRfrPLH = true;}
      else if(HMqbEfctga == VWBHMJtGmU){dgtnZcgVWZ = true;}
      if(YdbHLmtnGs == utbFHPiULP){BphtTHwldY = true;}
      else if(utbFHPiULP == YdbHLmtnGs){axLOqCmfuf = true;}
      if(CcgsAFITUg == UWdxdTZPyB){PNQEPVAfqc = true;}
      if(cAljaMmmPE == aWEpsmsPLN){AbGxRziisU = true;}
      if(JGfjNzEXbE == zImllaDbAm){hsQNGNRXIz = true;}
      while(UWdxdTZPyB == CcgsAFITUg){bqjiVzuuSS = true;}
      while(aWEpsmsPLN == aWEpsmsPLN){BNwRWVhjRK = true;}
      while(zImllaDbAm == zImllaDbAm){tbVZSAMDGm = true;}
      if(zANbUkisxj == true){zANbUkisxj = false;}
      if(GMwfzYplMT == true){GMwfzYplMT = false;}
      if(VSIyQMirLC == true){VSIyQMirLC = false;}
      if(QyPKBaIbVH == true){QyPKBaIbVH = false;}
      if(EARbGmLHlN == true){EARbGmLHlN = false;}
      if(kROfRfrPLH == true){kROfRfrPLH = false;}
      if(BphtTHwldY == true){BphtTHwldY = false;}
      if(PNQEPVAfqc == true){PNQEPVAfqc = false;}
      if(AbGxRziisU == true){AbGxRziisU = false;}
      if(hsQNGNRXIz == true){hsQNGNRXIz = false;}
      if(pZdNxXAKQu == true){pZdNxXAKQu = false;}
      if(eLXhHZjjcT == true){eLXhHZjjcT = false;}
      if(YNsIpWwCyB == true){YNsIpWwCyB = false;}
      if(DcXrmaxsAs == true){DcXrmaxsAs = false;}
      if(yYSxpWUhGf == true){yYSxpWUhGf = false;}
      if(dgtnZcgVWZ == true){dgtnZcgVWZ = false;}
      if(axLOqCmfuf == true){axLOqCmfuf = false;}
      if(bqjiVzuuSS == true){bqjiVzuuSS = false;}
      if(BNwRWVhjRK == true){BNwRWVhjRK = false;}
      if(tbVZSAMDGm == true){tbVZSAMDGm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JGYPOHEHOH
{ 
  void yyHAjOlQOX()
  { 
      bool oHAMrOOCBO = false;
      bool NeIVSLQVfI = false;
      bool iWxEXwrCpM = false;
      bool izGLJlYNnj = false;
      bool StRQZXbhnc = false;
      bool sgcQoSJuow = false;
      bool WMMnfOXxMf = false;
      bool lDgwpnFgdA = false;
      bool UJNNSBVpVq = false;
      bool ccXrNFhckL = false;
      bool zeVHpozgaB = false;
      bool NcRnaMyyVe = false;
      bool rhaVDIeohj = false;
      bool GbwSBonGXc = false;
      bool BoPUdzLjQA = false;
      bool HjHGSQDzEg = false;
      bool KKyptkgzml = false;
      bool XrarcDSFrD = false;
      bool xuYgbWTozj = false;
      bool lnBpSppYZr = false;
      string WuCPoWOXZe;
      string LxbEgDpYsZ;
      string GpUTggBRfr;
      string zHRUxncdjF;
      string euVduANorS;
      string OsukIfZhiI;
      string VwqhfDeHGs;
      string ZMontKTqXf;
      string TLYMcGMgMR;
      string OutbiiDnyr;
      string UFhzrCEHqx;
      string MiJCnJWeFY;
      string qyuodeRNEL;
      string GfrfKNdZUZ;
      string BFoOEfkrmY;
      string LYhYAWKsUM;
      string kqCfpfpcra;
      string fxJeXlIfjy;
      string tYZfzhxTen;
      string CjEHnKDJYY;
      if(WuCPoWOXZe == UFhzrCEHqx){oHAMrOOCBO = true;}
      else if(UFhzrCEHqx == WuCPoWOXZe){zeVHpozgaB = true;}
      if(LxbEgDpYsZ == MiJCnJWeFY){NeIVSLQVfI = true;}
      else if(MiJCnJWeFY == LxbEgDpYsZ){NcRnaMyyVe = true;}
      if(GpUTggBRfr == qyuodeRNEL){iWxEXwrCpM = true;}
      else if(qyuodeRNEL == GpUTggBRfr){rhaVDIeohj = true;}
      if(zHRUxncdjF == GfrfKNdZUZ){izGLJlYNnj = true;}
      else if(GfrfKNdZUZ == zHRUxncdjF){GbwSBonGXc = true;}
      if(euVduANorS == BFoOEfkrmY){StRQZXbhnc = true;}
      else if(BFoOEfkrmY == euVduANorS){BoPUdzLjQA = true;}
      if(OsukIfZhiI == LYhYAWKsUM){sgcQoSJuow = true;}
      else if(LYhYAWKsUM == OsukIfZhiI){HjHGSQDzEg = true;}
      if(VwqhfDeHGs == kqCfpfpcra){WMMnfOXxMf = true;}
      else if(kqCfpfpcra == VwqhfDeHGs){KKyptkgzml = true;}
      if(ZMontKTqXf == fxJeXlIfjy){lDgwpnFgdA = true;}
      if(TLYMcGMgMR == tYZfzhxTen){UJNNSBVpVq = true;}
      if(OutbiiDnyr == CjEHnKDJYY){ccXrNFhckL = true;}
      while(fxJeXlIfjy == ZMontKTqXf){XrarcDSFrD = true;}
      while(tYZfzhxTen == tYZfzhxTen){xuYgbWTozj = true;}
      while(CjEHnKDJYY == CjEHnKDJYY){lnBpSppYZr = true;}
      if(oHAMrOOCBO == true){oHAMrOOCBO = false;}
      if(NeIVSLQVfI == true){NeIVSLQVfI = false;}
      if(iWxEXwrCpM == true){iWxEXwrCpM = false;}
      if(izGLJlYNnj == true){izGLJlYNnj = false;}
      if(StRQZXbhnc == true){StRQZXbhnc = false;}
      if(sgcQoSJuow == true){sgcQoSJuow = false;}
      if(WMMnfOXxMf == true){WMMnfOXxMf = false;}
      if(lDgwpnFgdA == true){lDgwpnFgdA = false;}
      if(UJNNSBVpVq == true){UJNNSBVpVq = false;}
      if(ccXrNFhckL == true){ccXrNFhckL = false;}
      if(zeVHpozgaB == true){zeVHpozgaB = false;}
      if(NcRnaMyyVe == true){NcRnaMyyVe = false;}
      if(rhaVDIeohj == true){rhaVDIeohj = false;}
      if(GbwSBonGXc == true){GbwSBonGXc = false;}
      if(BoPUdzLjQA == true){BoPUdzLjQA = false;}
      if(HjHGSQDzEg == true){HjHGSQDzEg = false;}
      if(KKyptkgzml == true){KKyptkgzml = false;}
      if(XrarcDSFrD == true){XrarcDSFrD = false;}
      if(xuYgbWTozj == true){xuYgbWTozj = false;}
      if(lnBpSppYZr == true){lnBpSppYZr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TMIELPIJQR
{ 
  void WGUFSGxQGc()
  { 
      bool PzOsdYhMzq = false;
      bool NsjNaVpdjo = false;
      bool uOzIrRmYiN = false;
      bool hFSitgIufH = false;
      bool BTsNMgkbCI = false;
      bool AMMgnAzFBL = false;
      bool lJckJIZBTs = false;
      bool MtxcnbUluK = false;
      bool gLVaMUslus = false;
      bool hCtUVrpHEE = false;
      bool GjHIuFOjsM = false;
      bool eNKqeamCXn = false;
      bool PnFaLKAcGu = false;
      bool kNhqDxDNeH = false;
      bool FIsiNTqCpu = false;
      bool EnjPoSdgxk = false;
      bool EkcxaRfTmg = false;
      bool WZWQhGuWMq = false;
      bool SxmLpxdRBk = false;
      bool TVPsCUfuHu = false;
      string EKbwkjmCPF;
      string KcxXIMYpAh;
      string bChKsbPcls;
      string bMuWyCwdzw;
      string ElhHSQuIKI;
      string IXSehCcRDJ;
      string TJPVdyhZZG;
      string PuqDdoTZqb;
      string fHSdkDtPnu;
      string ZeZoctVMdU;
      string iVhErNgOBr;
      string iCabcLqlka;
      string ERlefkUBaj;
      string SHuVrKYNkW;
      string VeOuLWEyMQ;
      string CiaDQQiDXH;
      string renRYbHEiS;
      string mcBNEYDpSJ;
      string gWoJgifrFa;
      string aUpcdpqxWj;
      if(EKbwkjmCPF == iVhErNgOBr){PzOsdYhMzq = true;}
      else if(iVhErNgOBr == EKbwkjmCPF){GjHIuFOjsM = true;}
      if(KcxXIMYpAh == iCabcLqlka){NsjNaVpdjo = true;}
      else if(iCabcLqlka == KcxXIMYpAh){eNKqeamCXn = true;}
      if(bChKsbPcls == ERlefkUBaj){uOzIrRmYiN = true;}
      else if(ERlefkUBaj == bChKsbPcls){PnFaLKAcGu = true;}
      if(bMuWyCwdzw == SHuVrKYNkW){hFSitgIufH = true;}
      else if(SHuVrKYNkW == bMuWyCwdzw){kNhqDxDNeH = true;}
      if(ElhHSQuIKI == VeOuLWEyMQ){BTsNMgkbCI = true;}
      else if(VeOuLWEyMQ == ElhHSQuIKI){FIsiNTqCpu = true;}
      if(IXSehCcRDJ == CiaDQQiDXH){AMMgnAzFBL = true;}
      else if(CiaDQQiDXH == IXSehCcRDJ){EnjPoSdgxk = true;}
      if(TJPVdyhZZG == renRYbHEiS){lJckJIZBTs = true;}
      else if(renRYbHEiS == TJPVdyhZZG){EkcxaRfTmg = true;}
      if(PuqDdoTZqb == mcBNEYDpSJ){MtxcnbUluK = true;}
      if(fHSdkDtPnu == gWoJgifrFa){gLVaMUslus = true;}
      if(ZeZoctVMdU == aUpcdpqxWj){hCtUVrpHEE = true;}
      while(mcBNEYDpSJ == PuqDdoTZqb){WZWQhGuWMq = true;}
      while(gWoJgifrFa == gWoJgifrFa){SxmLpxdRBk = true;}
      while(aUpcdpqxWj == aUpcdpqxWj){TVPsCUfuHu = true;}
      if(PzOsdYhMzq == true){PzOsdYhMzq = false;}
      if(NsjNaVpdjo == true){NsjNaVpdjo = false;}
      if(uOzIrRmYiN == true){uOzIrRmYiN = false;}
      if(hFSitgIufH == true){hFSitgIufH = false;}
      if(BTsNMgkbCI == true){BTsNMgkbCI = false;}
      if(AMMgnAzFBL == true){AMMgnAzFBL = false;}
      if(lJckJIZBTs == true){lJckJIZBTs = false;}
      if(MtxcnbUluK == true){MtxcnbUluK = false;}
      if(gLVaMUslus == true){gLVaMUslus = false;}
      if(hCtUVrpHEE == true){hCtUVrpHEE = false;}
      if(GjHIuFOjsM == true){GjHIuFOjsM = false;}
      if(eNKqeamCXn == true){eNKqeamCXn = false;}
      if(PnFaLKAcGu == true){PnFaLKAcGu = false;}
      if(kNhqDxDNeH == true){kNhqDxDNeH = false;}
      if(FIsiNTqCpu == true){FIsiNTqCpu = false;}
      if(EnjPoSdgxk == true){EnjPoSdgxk = false;}
      if(EkcxaRfTmg == true){EkcxaRfTmg = false;}
      if(WZWQhGuWMq == true){WZWQhGuWMq = false;}
      if(SxmLpxdRBk == true){SxmLpxdRBk = false;}
      if(TVPsCUfuHu == true){TVPsCUfuHu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UAQEPUTJWW
{ 
  void lQNnVmsBQz()
  { 
      bool DicQfmkjNE = false;
      bool ALUIMPcUrC = false;
      bool spqocGPpSI = false;
      bool ZQXXUOPzFa = false;
      bool irHmAfxoIo = false;
      bool gLrQPNrnnY = false;
      bool XtRFejnxny = false;
      bool zcPRTBhDnw = false;
      bool IZhdbOYGIG = false;
      bool VbLfCnaCIQ = false;
      bool qABJoDwZxO = false;
      bool fnzrQyLmdQ = false;
      bool KhngbXRiOe = false;
      bool aeuXEIXXnX = false;
      bool SyJsagbTPE = false;
      bool bmXqFJLThR = false;
      bool lMLSmAsamH = false;
      bool ZnzGyLXtGt = false;
      bool wySKCmGDSu = false;
      bool xDpWlFmqGZ = false;
      string iCntUalOBc;
      string AFmXTZhESA;
      string EugrBZxqKf;
      string EWxbZACGyc;
      string ouPaiCtNoA;
      string wDlhxmUwsu;
      string dtEUXdHKyT;
      string XaGoKIfFIy;
      string ejBKiBjOdl;
      string eGNCztqtDF;
      string uiOVcVxxWn;
      string HOmtQtsslW;
      string srgLnRMDpP;
      string RkCDDuUegN;
      string DmqpePSTlE;
      string BxIgLCCCgL;
      string ItGHWVLipU;
      string YNMXSGBpgY;
      string ysQkOTcVrB;
      string rSyVEJfjSI;
      if(iCntUalOBc == uiOVcVxxWn){DicQfmkjNE = true;}
      else if(uiOVcVxxWn == iCntUalOBc){qABJoDwZxO = true;}
      if(AFmXTZhESA == HOmtQtsslW){ALUIMPcUrC = true;}
      else if(HOmtQtsslW == AFmXTZhESA){fnzrQyLmdQ = true;}
      if(EugrBZxqKf == srgLnRMDpP){spqocGPpSI = true;}
      else if(srgLnRMDpP == EugrBZxqKf){KhngbXRiOe = true;}
      if(EWxbZACGyc == RkCDDuUegN){ZQXXUOPzFa = true;}
      else if(RkCDDuUegN == EWxbZACGyc){aeuXEIXXnX = true;}
      if(ouPaiCtNoA == DmqpePSTlE){irHmAfxoIo = true;}
      else if(DmqpePSTlE == ouPaiCtNoA){SyJsagbTPE = true;}
      if(wDlhxmUwsu == BxIgLCCCgL){gLrQPNrnnY = true;}
      else if(BxIgLCCCgL == wDlhxmUwsu){bmXqFJLThR = true;}
      if(dtEUXdHKyT == ItGHWVLipU){XtRFejnxny = true;}
      else if(ItGHWVLipU == dtEUXdHKyT){lMLSmAsamH = true;}
      if(XaGoKIfFIy == YNMXSGBpgY){zcPRTBhDnw = true;}
      if(ejBKiBjOdl == ysQkOTcVrB){IZhdbOYGIG = true;}
      if(eGNCztqtDF == rSyVEJfjSI){VbLfCnaCIQ = true;}
      while(YNMXSGBpgY == XaGoKIfFIy){ZnzGyLXtGt = true;}
      while(ysQkOTcVrB == ysQkOTcVrB){wySKCmGDSu = true;}
      while(rSyVEJfjSI == rSyVEJfjSI){xDpWlFmqGZ = true;}
      if(DicQfmkjNE == true){DicQfmkjNE = false;}
      if(ALUIMPcUrC == true){ALUIMPcUrC = false;}
      if(spqocGPpSI == true){spqocGPpSI = false;}
      if(ZQXXUOPzFa == true){ZQXXUOPzFa = false;}
      if(irHmAfxoIo == true){irHmAfxoIo = false;}
      if(gLrQPNrnnY == true){gLrQPNrnnY = false;}
      if(XtRFejnxny == true){XtRFejnxny = false;}
      if(zcPRTBhDnw == true){zcPRTBhDnw = false;}
      if(IZhdbOYGIG == true){IZhdbOYGIG = false;}
      if(VbLfCnaCIQ == true){VbLfCnaCIQ = false;}
      if(qABJoDwZxO == true){qABJoDwZxO = false;}
      if(fnzrQyLmdQ == true){fnzrQyLmdQ = false;}
      if(KhngbXRiOe == true){KhngbXRiOe = false;}
      if(aeuXEIXXnX == true){aeuXEIXXnX = false;}
      if(SyJsagbTPE == true){SyJsagbTPE = false;}
      if(bmXqFJLThR == true){bmXqFJLThR = false;}
      if(lMLSmAsamH == true){lMLSmAsamH = false;}
      if(ZnzGyLXtGt == true){ZnzGyLXtGt = false;}
      if(wySKCmGDSu == true){wySKCmGDSu = false;}
      if(xDpWlFmqGZ == true){xDpWlFmqGZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NXPFKPPZRJ
{ 
  void fyouMBugwL()
  { 
      bool QXPgBmkdEE = false;
      bool xTtugEgPWn = false;
      bool lyBHKscqdU = false;
      bool bkGVeheJtU = false;
      bool PoiTYPqEtr = false;
      bool dAtwtSVIVH = false;
      bool KtAicMNYQy = false;
      bool YWUBXwOhiu = false;
      bool CXxkqaqJaM = false;
      bool MWnlKVoAqM = false;
      bool CRnuSHerYy = false;
      bool DnYaFlwOrB = false;
      bool VDyDlCihqB = false;
      bool GOpWsjjBRi = false;
      bool uykcIYxMgX = false;
      bool ZaHopyTjIQ = false;
      bool XxAXqoxChU = false;
      bool CtwIGWSVuN = false;
      bool EVBSbfGBft = false;
      bool QzsBLyyMkT = false;
      string aGNluwfhaq;
      string MQtEJQALEx;
      string TsTiRiMerO;
      string AcRIzyVPbf;
      string lapszxMqzl;
      string aZMPmhldUL;
      string jAoMqizkFK;
      string ukiYKrCajT;
      string VUfGmZPBUR;
      string MquQwkldCP;
      string xbknqppnEu;
      string eKtAoOUhYQ;
      string TyQnxDpScZ;
      string FYYUVtiqPx;
      string jbwZlCxtag;
      string QEFkwzKxqm;
      string AXLeoFlZdt;
      string fcSagrBqCu;
      string GuquIBTmXW;
      string jlAbxLQQjf;
      if(aGNluwfhaq == xbknqppnEu){QXPgBmkdEE = true;}
      else if(xbknqppnEu == aGNluwfhaq){CRnuSHerYy = true;}
      if(MQtEJQALEx == eKtAoOUhYQ){xTtugEgPWn = true;}
      else if(eKtAoOUhYQ == MQtEJQALEx){DnYaFlwOrB = true;}
      if(TsTiRiMerO == TyQnxDpScZ){lyBHKscqdU = true;}
      else if(TyQnxDpScZ == TsTiRiMerO){VDyDlCihqB = true;}
      if(AcRIzyVPbf == FYYUVtiqPx){bkGVeheJtU = true;}
      else if(FYYUVtiqPx == AcRIzyVPbf){GOpWsjjBRi = true;}
      if(lapszxMqzl == jbwZlCxtag){PoiTYPqEtr = true;}
      else if(jbwZlCxtag == lapszxMqzl){uykcIYxMgX = true;}
      if(aZMPmhldUL == QEFkwzKxqm){dAtwtSVIVH = true;}
      else if(QEFkwzKxqm == aZMPmhldUL){ZaHopyTjIQ = true;}
      if(jAoMqizkFK == AXLeoFlZdt){KtAicMNYQy = true;}
      else if(AXLeoFlZdt == jAoMqizkFK){XxAXqoxChU = true;}
      if(ukiYKrCajT == fcSagrBqCu){YWUBXwOhiu = true;}
      if(VUfGmZPBUR == GuquIBTmXW){CXxkqaqJaM = true;}
      if(MquQwkldCP == jlAbxLQQjf){MWnlKVoAqM = true;}
      while(fcSagrBqCu == ukiYKrCajT){CtwIGWSVuN = true;}
      while(GuquIBTmXW == GuquIBTmXW){EVBSbfGBft = true;}
      while(jlAbxLQQjf == jlAbxLQQjf){QzsBLyyMkT = true;}
      if(QXPgBmkdEE == true){QXPgBmkdEE = false;}
      if(xTtugEgPWn == true){xTtugEgPWn = false;}
      if(lyBHKscqdU == true){lyBHKscqdU = false;}
      if(bkGVeheJtU == true){bkGVeheJtU = false;}
      if(PoiTYPqEtr == true){PoiTYPqEtr = false;}
      if(dAtwtSVIVH == true){dAtwtSVIVH = false;}
      if(KtAicMNYQy == true){KtAicMNYQy = false;}
      if(YWUBXwOhiu == true){YWUBXwOhiu = false;}
      if(CXxkqaqJaM == true){CXxkqaqJaM = false;}
      if(MWnlKVoAqM == true){MWnlKVoAqM = false;}
      if(CRnuSHerYy == true){CRnuSHerYy = false;}
      if(DnYaFlwOrB == true){DnYaFlwOrB = false;}
      if(VDyDlCihqB == true){VDyDlCihqB = false;}
      if(GOpWsjjBRi == true){GOpWsjjBRi = false;}
      if(uykcIYxMgX == true){uykcIYxMgX = false;}
      if(ZaHopyTjIQ == true){ZaHopyTjIQ = false;}
      if(XxAXqoxChU == true){XxAXqoxChU = false;}
      if(CtwIGWSVuN == true){CtwIGWSVuN = false;}
      if(EVBSbfGBft == true){EVBSbfGBft = false;}
      if(QzsBLyyMkT == true){QzsBLyyMkT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFXPMUOIGO
{ 
  void PamPaJhCFh()
  { 
      bool juYGHTHsRp = false;
      bool KrjHcTUORc = false;
      bool WymYqZeWWQ = false;
      bool eExBmfcQTx = false;
      bool rzYXLmmDbE = false;
      bool aCzdVkHzOg = false;
      bool okVBLGtiUw = false;
      bool qEuTjXZPME = false;
      bool latSobFTeB = false;
      bool YcBlIHcXMF = false;
      bool rEifMWHesy = false;
      bool LrlJtNpDMj = false;
      bool BaESXOCILc = false;
      bool uCCHMhrOFS = false;
      bool TZZfpfprqt = false;
      bool RYLcDQzPHy = false;
      bool TzTQDJpewM = false;
      bool VbxsPbBYcq = false;
      bool XKQQLVqYEw = false;
      bool hbGHyTFJbg = false;
      string mYErOPjMtd;
      string PYFghSJXcO;
      string uYLLnwdhoR;
      string yjrPVysVuq;
      string tqJKUidsNC;
      string eTHfQNMsDR;
      string kCXcefgoKj;
      string YnclTDPBpE;
      string RkUllebLyH;
      string lAScFrTgeo;
      string BnhccqqVLN;
      string yLCyAAhkqA;
      string DVqDxYVzfb;
      string iiVACcCqJt;
      string nGAkIZxTcF;
      string KipelfxeeE;
      string VqoidPpCuW;
      string ypbwMwUFtX;
      string bBWaRAsqOW;
      string eXLEYwRQHs;
      if(mYErOPjMtd == BnhccqqVLN){juYGHTHsRp = true;}
      else if(BnhccqqVLN == mYErOPjMtd){rEifMWHesy = true;}
      if(PYFghSJXcO == yLCyAAhkqA){KrjHcTUORc = true;}
      else if(yLCyAAhkqA == PYFghSJXcO){LrlJtNpDMj = true;}
      if(uYLLnwdhoR == DVqDxYVzfb){WymYqZeWWQ = true;}
      else if(DVqDxYVzfb == uYLLnwdhoR){BaESXOCILc = true;}
      if(yjrPVysVuq == iiVACcCqJt){eExBmfcQTx = true;}
      else if(iiVACcCqJt == yjrPVysVuq){uCCHMhrOFS = true;}
      if(tqJKUidsNC == nGAkIZxTcF){rzYXLmmDbE = true;}
      else if(nGAkIZxTcF == tqJKUidsNC){TZZfpfprqt = true;}
      if(eTHfQNMsDR == KipelfxeeE){aCzdVkHzOg = true;}
      else if(KipelfxeeE == eTHfQNMsDR){RYLcDQzPHy = true;}
      if(kCXcefgoKj == VqoidPpCuW){okVBLGtiUw = true;}
      else if(VqoidPpCuW == kCXcefgoKj){TzTQDJpewM = true;}
      if(YnclTDPBpE == ypbwMwUFtX){qEuTjXZPME = true;}
      if(RkUllebLyH == bBWaRAsqOW){latSobFTeB = true;}
      if(lAScFrTgeo == eXLEYwRQHs){YcBlIHcXMF = true;}
      while(ypbwMwUFtX == YnclTDPBpE){VbxsPbBYcq = true;}
      while(bBWaRAsqOW == bBWaRAsqOW){XKQQLVqYEw = true;}
      while(eXLEYwRQHs == eXLEYwRQHs){hbGHyTFJbg = true;}
      if(juYGHTHsRp == true){juYGHTHsRp = false;}
      if(KrjHcTUORc == true){KrjHcTUORc = false;}
      if(WymYqZeWWQ == true){WymYqZeWWQ = false;}
      if(eExBmfcQTx == true){eExBmfcQTx = false;}
      if(rzYXLmmDbE == true){rzYXLmmDbE = false;}
      if(aCzdVkHzOg == true){aCzdVkHzOg = false;}
      if(okVBLGtiUw == true){okVBLGtiUw = false;}
      if(qEuTjXZPME == true){qEuTjXZPME = false;}
      if(latSobFTeB == true){latSobFTeB = false;}
      if(YcBlIHcXMF == true){YcBlIHcXMF = false;}
      if(rEifMWHesy == true){rEifMWHesy = false;}
      if(LrlJtNpDMj == true){LrlJtNpDMj = false;}
      if(BaESXOCILc == true){BaESXOCILc = false;}
      if(uCCHMhrOFS == true){uCCHMhrOFS = false;}
      if(TZZfpfprqt == true){TZZfpfprqt = false;}
      if(RYLcDQzPHy == true){RYLcDQzPHy = false;}
      if(TzTQDJpewM == true){TzTQDJpewM = false;}
      if(VbxsPbBYcq == true){VbxsPbBYcq = false;}
      if(XKQQLVqYEw == true){XKQQLVqYEw = false;}
      if(hbGHyTFJbg == true){hbGHyTFJbg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YSHKWGAYLC
{ 
  void sGbEgerIug()
  { 
      bool dEZtMuxzsA = false;
      bool KhMbVnhyOA = false;
      bool rqacLAwaWS = false;
      bool KXnEWTSXte = false;
      bool wBxbdWyjMZ = false;
      bool jRDpSmcwiM = false;
      bool yVcZomtHFB = false;
      bool UKDjEqszzo = false;
      bool BMOwirTxki = false;
      bool qWogfZXXlp = false;
      bool bqdKEZNTlb = false;
      bool tdxsLkHgqw = false;
      bool SxWVJyUVDd = false;
      bool SUMIMKhDqI = false;
      bool dALJoNZuVu = false;
      bool RqfpXeTIBG = false;
      bool ErQHIYQnfA = false;
      bool CEphRSkMgw = false;
      bool YYAHLboWkh = false;
      bool pZCkEljDAP = false;
      string OqiGBjjMYx;
      string CxQjxrmuRS;
      string YakBIWwCYY;
      string xyaTaUwzXM;
      string kfThaUaIUV;
      string HAqAmnFgxe;
      string mgnzADWxIc;
      string unWFhrGCZn;
      string wmhCQwHZfm;
      string OOBsYDrThW;
      string ydzrZTdlSt;
      string gCGIiAzkhD;
      string wwQVNflcfd;
      string AmUDpRnpbx;
      string SVGkFMHrKY;
      string EGkdaBNcdt;
      string hAFntthDSQ;
      string LIJkkapeQB;
      string XsSHZsBqbo;
      string ELMhORPRqL;
      if(OqiGBjjMYx == ydzrZTdlSt){dEZtMuxzsA = true;}
      else if(ydzrZTdlSt == OqiGBjjMYx){bqdKEZNTlb = true;}
      if(CxQjxrmuRS == gCGIiAzkhD){KhMbVnhyOA = true;}
      else if(gCGIiAzkhD == CxQjxrmuRS){tdxsLkHgqw = true;}
      if(YakBIWwCYY == wwQVNflcfd){rqacLAwaWS = true;}
      else if(wwQVNflcfd == YakBIWwCYY){SxWVJyUVDd = true;}
      if(xyaTaUwzXM == AmUDpRnpbx){KXnEWTSXte = true;}
      else if(AmUDpRnpbx == xyaTaUwzXM){SUMIMKhDqI = true;}
      if(kfThaUaIUV == SVGkFMHrKY){wBxbdWyjMZ = true;}
      else if(SVGkFMHrKY == kfThaUaIUV){dALJoNZuVu = true;}
      if(HAqAmnFgxe == EGkdaBNcdt){jRDpSmcwiM = true;}
      else if(EGkdaBNcdt == HAqAmnFgxe){RqfpXeTIBG = true;}
      if(mgnzADWxIc == hAFntthDSQ){yVcZomtHFB = true;}
      else if(hAFntthDSQ == mgnzADWxIc){ErQHIYQnfA = true;}
      if(unWFhrGCZn == LIJkkapeQB){UKDjEqszzo = true;}
      if(wmhCQwHZfm == XsSHZsBqbo){BMOwirTxki = true;}
      if(OOBsYDrThW == ELMhORPRqL){qWogfZXXlp = true;}
      while(LIJkkapeQB == unWFhrGCZn){CEphRSkMgw = true;}
      while(XsSHZsBqbo == XsSHZsBqbo){YYAHLboWkh = true;}
      while(ELMhORPRqL == ELMhORPRqL){pZCkEljDAP = true;}
      if(dEZtMuxzsA == true){dEZtMuxzsA = false;}
      if(KhMbVnhyOA == true){KhMbVnhyOA = false;}
      if(rqacLAwaWS == true){rqacLAwaWS = false;}
      if(KXnEWTSXte == true){KXnEWTSXte = false;}
      if(wBxbdWyjMZ == true){wBxbdWyjMZ = false;}
      if(jRDpSmcwiM == true){jRDpSmcwiM = false;}
      if(yVcZomtHFB == true){yVcZomtHFB = false;}
      if(UKDjEqszzo == true){UKDjEqszzo = false;}
      if(BMOwirTxki == true){BMOwirTxki = false;}
      if(qWogfZXXlp == true){qWogfZXXlp = false;}
      if(bqdKEZNTlb == true){bqdKEZNTlb = false;}
      if(tdxsLkHgqw == true){tdxsLkHgqw = false;}
      if(SxWVJyUVDd == true){SxWVJyUVDd = false;}
      if(SUMIMKhDqI == true){SUMIMKhDqI = false;}
      if(dALJoNZuVu == true){dALJoNZuVu = false;}
      if(RqfpXeTIBG == true){RqfpXeTIBG = false;}
      if(ErQHIYQnfA == true){ErQHIYQnfA = false;}
      if(CEphRSkMgw == true){CEphRSkMgw = false;}
      if(YYAHLboWkh == true){YYAHLboWkh = false;}
      if(pZCkEljDAP == true){pZCkEljDAP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IKZHPBDLVQ
{ 
  void SymhVcgBXU()
  { 
      bool sUxAtTbtmj = false;
      bool WBVhIBrNpX = false;
      bool cZQKmaGDWc = false;
      bool UbhLUFJBTy = false;
      bool DzWxaLJoWh = false;
      bool YRVoLSElNT = false;
      bool NYXJOtSJNC = false;
      bool qqtrUdDSia = false;
      bool RQfoDDGsAB = false;
      bool BWnAjdaNhf = false;
      bool rzbUphWdTh = false;
      bool PkDlBwsiFL = false;
      bool nZJMBTDtHp = false;
      bool CokDiRoKyV = false;
      bool fbYRkPTBym = false;
      bool krHWrSpOTV = false;
      bool ecVdeZzzDj = false;
      bool HhjjeLArak = false;
      bool ABwTFKhOLP = false;
      bool bZqcqDGulK = false;
      string BCkBTSCjSq;
      string VlVdQnzzkQ;
      string ttrJFsTuwL;
      string XQhBlRKRkK;
      string DwDJyabdmE;
      string BMRmqHKbwa;
      string zGnGTFEUry;
      string cgNaNyphKe;
      string QoIqKLytJd;
      string GiVKLwHwpr;
      string VHlnbTyqYs;
      string RcQQJJyxwH;
      string HJKOrsLDPQ;
      string ptrSJJDTOq;
      string MGUPMdSEBB;
      string yKAhkLwXwi;
      string HubIDWjyHA;
      string GdiFuAouBN;
      string aGCNRetKgx;
      string MeXeiReMMo;
      if(BCkBTSCjSq == VHlnbTyqYs){sUxAtTbtmj = true;}
      else if(VHlnbTyqYs == BCkBTSCjSq){rzbUphWdTh = true;}
      if(VlVdQnzzkQ == RcQQJJyxwH){WBVhIBrNpX = true;}
      else if(RcQQJJyxwH == VlVdQnzzkQ){PkDlBwsiFL = true;}
      if(ttrJFsTuwL == HJKOrsLDPQ){cZQKmaGDWc = true;}
      else if(HJKOrsLDPQ == ttrJFsTuwL){nZJMBTDtHp = true;}
      if(XQhBlRKRkK == ptrSJJDTOq){UbhLUFJBTy = true;}
      else if(ptrSJJDTOq == XQhBlRKRkK){CokDiRoKyV = true;}
      if(DwDJyabdmE == MGUPMdSEBB){DzWxaLJoWh = true;}
      else if(MGUPMdSEBB == DwDJyabdmE){fbYRkPTBym = true;}
      if(BMRmqHKbwa == yKAhkLwXwi){YRVoLSElNT = true;}
      else if(yKAhkLwXwi == BMRmqHKbwa){krHWrSpOTV = true;}
      if(zGnGTFEUry == HubIDWjyHA){NYXJOtSJNC = true;}
      else if(HubIDWjyHA == zGnGTFEUry){ecVdeZzzDj = true;}
      if(cgNaNyphKe == GdiFuAouBN){qqtrUdDSia = true;}
      if(QoIqKLytJd == aGCNRetKgx){RQfoDDGsAB = true;}
      if(GiVKLwHwpr == MeXeiReMMo){BWnAjdaNhf = true;}
      while(GdiFuAouBN == cgNaNyphKe){HhjjeLArak = true;}
      while(aGCNRetKgx == aGCNRetKgx){ABwTFKhOLP = true;}
      while(MeXeiReMMo == MeXeiReMMo){bZqcqDGulK = true;}
      if(sUxAtTbtmj == true){sUxAtTbtmj = false;}
      if(WBVhIBrNpX == true){WBVhIBrNpX = false;}
      if(cZQKmaGDWc == true){cZQKmaGDWc = false;}
      if(UbhLUFJBTy == true){UbhLUFJBTy = false;}
      if(DzWxaLJoWh == true){DzWxaLJoWh = false;}
      if(YRVoLSElNT == true){YRVoLSElNT = false;}
      if(NYXJOtSJNC == true){NYXJOtSJNC = false;}
      if(qqtrUdDSia == true){qqtrUdDSia = false;}
      if(RQfoDDGsAB == true){RQfoDDGsAB = false;}
      if(BWnAjdaNhf == true){BWnAjdaNhf = false;}
      if(rzbUphWdTh == true){rzbUphWdTh = false;}
      if(PkDlBwsiFL == true){PkDlBwsiFL = false;}
      if(nZJMBTDtHp == true){nZJMBTDtHp = false;}
      if(CokDiRoKyV == true){CokDiRoKyV = false;}
      if(fbYRkPTBym == true){fbYRkPTBym = false;}
      if(krHWrSpOTV == true){krHWrSpOTV = false;}
      if(ecVdeZzzDj == true){ecVdeZzzDj = false;}
      if(HhjjeLArak == true){HhjjeLArak = false;}
      if(ABwTFKhOLP == true){ABwTFKhOLP = false;}
      if(bZqcqDGulK == true){bZqcqDGulK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JUUEEKXBPJ
{ 
  void wwmWAKEHNO()
  { 
      bool mxWEYTEqsn = false;
      bool rrYebqjcFR = false;
      bool kYCSGuCUuc = false;
      bool HxXwweiUQN = false;
      bool uDtEUgxXHp = false;
      bool KDlQkNtExc = false;
      bool RjwQfuUbix = false;
      bool HPMrVheyxZ = false;
      bool ydMERDKGLh = false;
      bool jeWnuLGdXY = false;
      bool MUoJhuqttC = false;
      bool iwGWdmWqyc = false;
      bool kNQANcrYxK = false;
      bool bBaYNcoDWV = false;
      bool MQLIznXzJH = false;
      bool nPeunyEnwF = false;
      bool DSxjahUhJA = false;
      bool yTUbPUCIBY = false;
      bool EsOoVMVfkO = false;
      bool YBHQSsSbgR = false;
      string oKyPwVCSek;
      string oPsxoqqShk;
      string LIqsqPMQPj;
      string mAWLdlNCTe;
      string hDUrGtmiBC;
      string xQBxigSEXf;
      string JlDtynrhTD;
      string doyCDInzmw;
      string bcOMmWzYbw;
      string TJdnVwzZsR;
      string BEOxYISzta;
      string sSQaDfWqGb;
      string oTGWiUKJfH;
      string INFVuWNQme;
      string DAeACArDkp;
      string ZISRchyrOE;
      string yISmRfNuff;
      string RFDbXnoGTi;
      string bGYogAtnrN;
      string YVCigugqhW;
      if(oKyPwVCSek == BEOxYISzta){mxWEYTEqsn = true;}
      else if(BEOxYISzta == oKyPwVCSek){MUoJhuqttC = true;}
      if(oPsxoqqShk == sSQaDfWqGb){rrYebqjcFR = true;}
      else if(sSQaDfWqGb == oPsxoqqShk){iwGWdmWqyc = true;}
      if(LIqsqPMQPj == oTGWiUKJfH){kYCSGuCUuc = true;}
      else if(oTGWiUKJfH == LIqsqPMQPj){kNQANcrYxK = true;}
      if(mAWLdlNCTe == INFVuWNQme){HxXwweiUQN = true;}
      else if(INFVuWNQme == mAWLdlNCTe){bBaYNcoDWV = true;}
      if(hDUrGtmiBC == DAeACArDkp){uDtEUgxXHp = true;}
      else if(DAeACArDkp == hDUrGtmiBC){MQLIznXzJH = true;}
      if(xQBxigSEXf == ZISRchyrOE){KDlQkNtExc = true;}
      else if(ZISRchyrOE == xQBxigSEXf){nPeunyEnwF = true;}
      if(JlDtynrhTD == yISmRfNuff){RjwQfuUbix = true;}
      else if(yISmRfNuff == JlDtynrhTD){DSxjahUhJA = true;}
      if(doyCDInzmw == RFDbXnoGTi){HPMrVheyxZ = true;}
      if(bcOMmWzYbw == bGYogAtnrN){ydMERDKGLh = true;}
      if(TJdnVwzZsR == YVCigugqhW){jeWnuLGdXY = true;}
      while(RFDbXnoGTi == doyCDInzmw){yTUbPUCIBY = true;}
      while(bGYogAtnrN == bGYogAtnrN){EsOoVMVfkO = true;}
      while(YVCigugqhW == YVCigugqhW){YBHQSsSbgR = true;}
      if(mxWEYTEqsn == true){mxWEYTEqsn = false;}
      if(rrYebqjcFR == true){rrYebqjcFR = false;}
      if(kYCSGuCUuc == true){kYCSGuCUuc = false;}
      if(HxXwweiUQN == true){HxXwweiUQN = false;}
      if(uDtEUgxXHp == true){uDtEUgxXHp = false;}
      if(KDlQkNtExc == true){KDlQkNtExc = false;}
      if(RjwQfuUbix == true){RjwQfuUbix = false;}
      if(HPMrVheyxZ == true){HPMrVheyxZ = false;}
      if(ydMERDKGLh == true){ydMERDKGLh = false;}
      if(jeWnuLGdXY == true){jeWnuLGdXY = false;}
      if(MUoJhuqttC == true){MUoJhuqttC = false;}
      if(iwGWdmWqyc == true){iwGWdmWqyc = false;}
      if(kNQANcrYxK == true){kNQANcrYxK = false;}
      if(bBaYNcoDWV == true){bBaYNcoDWV = false;}
      if(MQLIznXzJH == true){MQLIznXzJH = false;}
      if(nPeunyEnwF == true){nPeunyEnwF = false;}
      if(DSxjahUhJA == true){DSxjahUhJA = false;}
      if(yTUbPUCIBY == true){yTUbPUCIBY = false;}
      if(EsOoVMVfkO == true){EsOoVMVfkO = false;}
      if(YBHQSsSbgR == true){YBHQSsSbgR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PSZIYADGYA
{ 
  void KXcCkhOTMl()
  { 
      bool EDxJVrXyEG = false;
      bool CjDwcxZryY = false;
      bool yuhqfxgCBn = false;
      bool ijfxBBWDnw = false;
      bool FlDhpRNCGQ = false;
      bool hSynUIVFcX = false;
      bool KUxQXSEFua = false;
      bool ZVECTMqzAO = false;
      bool jewjGPlqcr = false;
      bool fQaPkjnmKX = false;
      bool NIHfpLOwUI = false;
      bool RVENmfYNKH = false;
      bool fMbCtIunQi = false;
      bool XDocAbWPst = false;
      bool BpWTaKMMbF = false;
      bool KacDqAfElh = false;
      bool PaekjOfbNL = false;
      bool JJUPGpoHbi = false;
      bool whLLXxalkA = false;
      bool wRcLeaKljM = false;
      string rapWwsRGFT;
      string EJNZLbjArd;
      string DFQbfQRPTN;
      string rmHzWdElnM;
      string IAzRaCzqxm;
      string PFcWsmKOpf;
      string aBlqbRCODg;
      string WxMfUCFyAc;
      string QZSgxlJkGi;
      string TpuHkHOHpJ;
      string AknPPSrwBp;
      string gLONOAiEtp;
      string HQHTNgBFtN;
      string nyIqcflCRe;
      string tNjPCHahrk;
      string YKNABicUCh;
      string QmBmCiDXki;
      string OglOutgrRF;
      string FTMJndjIos;
      string CQziNHLwMT;
      if(rapWwsRGFT == AknPPSrwBp){EDxJVrXyEG = true;}
      else if(AknPPSrwBp == rapWwsRGFT){NIHfpLOwUI = true;}
      if(EJNZLbjArd == gLONOAiEtp){CjDwcxZryY = true;}
      else if(gLONOAiEtp == EJNZLbjArd){RVENmfYNKH = true;}
      if(DFQbfQRPTN == HQHTNgBFtN){yuhqfxgCBn = true;}
      else if(HQHTNgBFtN == DFQbfQRPTN){fMbCtIunQi = true;}
      if(rmHzWdElnM == nyIqcflCRe){ijfxBBWDnw = true;}
      else if(nyIqcflCRe == rmHzWdElnM){XDocAbWPst = true;}
      if(IAzRaCzqxm == tNjPCHahrk){FlDhpRNCGQ = true;}
      else if(tNjPCHahrk == IAzRaCzqxm){BpWTaKMMbF = true;}
      if(PFcWsmKOpf == YKNABicUCh){hSynUIVFcX = true;}
      else if(YKNABicUCh == PFcWsmKOpf){KacDqAfElh = true;}
      if(aBlqbRCODg == QmBmCiDXki){KUxQXSEFua = true;}
      else if(QmBmCiDXki == aBlqbRCODg){PaekjOfbNL = true;}
      if(WxMfUCFyAc == OglOutgrRF){ZVECTMqzAO = true;}
      if(QZSgxlJkGi == FTMJndjIos){jewjGPlqcr = true;}
      if(TpuHkHOHpJ == CQziNHLwMT){fQaPkjnmKX = true;}
      while(OglOutgrRF == WxMfUCFyAc){JJUPGpoHbi = true;}
      while(FTMJndjIos == FTMJndjIos){whLLXxalkA = true;}
      while(CQziNHLwMT == CQziNHLwMT){wRcLeaKljM = true;}
      if(EDxJVrXyEG == true){EDxJVrXyEG = false;}
      if(CjDwcxZryY == true){CjDwcxZryY = false;}
      if(yuhqfxgCBn == true){yuhqfxgCBn = false;}
      if(ijfxBBWDnw == true){ijfxBBWDnw = false;}
      if(FlDhpRNCGQ == true){FlDhpRNCGQ = false;}
      if(hSynUIVFcX == true){hSynUIVFcX = false;}
      if(KUxQXSEFua == true){KUxQXSEFua = false;}
      if(ZVECTMqzAO == true){ZVECTMqzAO = false;}
      if(jewjGPlqcr == true){jewjGPlqcr = false;}
      if(fQaPkjnmKX == true){fQaPkjnmKX = false;}
      if(NIHfpLOwUI == true){NIHfpLOwUI = false;}
      if(RVENmfYNKH == true){RVENmfYNKH = false;}
      if(fMbCtIunQi == true){fMbCtIunQi = false;}
      if(XDocAbWPst == true){XDocAbWPst = false;}
      if(BpWTaKMMbF == true){BpWTaKMMbF = false;}
      if(KacDqAfElh == true){KacDqAfElh = false;}
      if(PaekjOfbNL == true){PaekjOfbNL = false;}
      if(JJUPGpoHbi == true){JJUPGpoHbi = false;}
      if(whLLXxalkA == true){whLLXxalkA = false;}
      if(wRcLeaKljM == true){wRcLeaKljM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZZLCJIPXAE
{ 
  void YJTCjoVVIl()
  { 
      bool RtxHXSsQYH = false;
      bool BLiWdxjCuQ = false;
      bool GekBuTyGtt = false;
      bool KccYijhcqX = false;
      bool CRopsxXuWF = false;
      bool YxrFzmIuME = false;
      bool UlWdwXhJnt = false;
      bool PGKWOnptIy = false;
      bool wDioUNjWZu = false;
      bool alQmDQuKsU = false;
      bool OOGcpSlVqK = false;
      bool xOmOIQCgIi = false;
      bool mKjrScpXSy = false;
      bool seAmigwFyC = false;
      bool aOeOyLzCel = false;
      bool NNCKhEeNJN = false;
      bool cOCsRSNAfa = false;
      bool TwhGIYeUtG = false;
      bool cmrfjecpFd = false;
      bool CiwkZLLlwf = false;
      string UUPtfYBPRa;
      string ZAqbinKKNr;
      string RqmwNpQSaI;
      string xsUOOczibD;
      string ZEBmepYEqD;
      string bArfVdhTgp;
      string IinJdffcMG;
      string naiJSMozQW;
      string QMaXgwBnrk;
      string tfCkuqQqJy;
      string KwqkPARhNI;
      string niCJYwHPcg;
      string eqjbMHXxOa;
      string wxpSMUUpIf;
      string dSajwLdsMz;
      string jAObTSLOXH;
      string cUSlMpsjwE;
      string aQHxDLQAfB;
      string dekPquiNyt;
      string IGRACJAnWG;
      if(UUPtfYBPRa == KwqkPARhNI){RtxHXSsQYH = true;}
      else if(KwqkPARhNI == UUPtfYBPRa){OOGcpSlVqK = true;}
      if(ZAqbinKKNr == niCJYwHPcg){BLiWdxjCuQ = true;}
      else if(niCJYwHPcg == ZAqbinKKNr){xOmOIQCgIi = true;}
      if(RqmwNpQSaI == eqjbMHXxOa){GekBuTyGtt = true;}
      else if(eqjbMHXxOa == RqmwNpQSaI){mKjrScpXSy = true;}
      if(xsUOOczibD == wxpSMUUpIf){KccYijhcqX = true;}
      else if(wxpSMUUpIf == xsUOOczibD){seAmigwFyC = true;}
      if(ZEBmepYEqD == dSajwLdsMz){CRopsxXuWF = true;}
      else if(dSajwLdsMz == ZEBmepYEqD){aOeOyLzCel = true;}
      if(bArfVdhTgp == jAObTSLOXH){YxrFzmIuME = true;}
      else if(jAObTSLOXH == bArfVdhTgp){NNCKhEeNJN = true;}
      if(IinJdffcMG == cUSlMpsjwE){UlWdwXhJnt = true;}
      else if(cUSlMpsjwE == IinJdffcMG){cOCsRSNAfa = true;}
      if(naiJSMozQW == aQHxDLQAfB){PGKWOnptIy = true;}
      if(QMaXgwBnrk == dekPquiNyt){wDioUNjWZu = true;}
      if(tfCkuqQqJy == IGRACJAnWG){alQmDQuKsU = true;}
      while(aQHxDLQAfB == naiJSMozQW){TwhGIYeUtG = true;}
      while(dekPquiNyt == dekPquiNyt){cmrfjecpFd = true;}
      while(IGRACJAnWG == IGRACJAnWG){CiwkZLLlwf = true;}
      if(RtxHXSsQYH == true){RtxHXSsQYH = false;}
      if(BLiWdxjCuQ == true){BLiWdxjCuQ = false;}
      if(GekBuTyGtt == true){GekBuTyGtt = false;}
      if(KccYijhcqX == true){KccYijhcqX = false;}
      if(CRopsxXuWF == true){CRopsxXuWF = false;}
      if(YxrFzmIuME == true){YxrFzmIuME = false;}
      if(UlWdwXhJnt == true){UlWdwXhJnt = false;}
      if(PGKWOnptIy == true){PGKWOnptIy = false;}
      if(wDioUNjWZu == true){wDioUNjWZu = false;}
      if(alQmDQuKsU == true){alQmDQuKsU = false;}
      if(OOGcpSlVqK == true){OOGcpSlVqK = false;}
      if(xOmOIQCgIi == true){xOmOIQCgIi = false;}
      if(mKjrScpXSy == true){mKjrScpXSy = false;}
      if(seAmigwFyC == true){seAmigwFyC = false;}
      if(aOeOyLzCel == true){aOeOyLzCel = false;}
      if(NNCKhEeNJN == true){NNCKhEeNJN = false;}
      if(cOCsRSNAfa == true){cOCsRSNAfa = false;}
      if(TwhGIYeUtG == true){TwhGIYeUtG = false;}
      if(cmrfjecpFd == true){cmrfjecpFd = false;}
      if(CiwkZLLlwf == true){CiwkZLLlwf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JUERBLPMMI
{ 
  void sZKdkBEutu()
  { 
      bool siCxnSoNMp = false;
      bool VSeIaULLPY = false;
      bool tYFPSmnIeR = false;
      bool CcGAfPpdtK = false;
      bool CjPdHlYPFs = false;
      bool xRaYSTdleB = false;
      bool eghtmrMdbL = false;
      bool egRFVKJbIg = false;
      bool NXCkTkCggL = false;
      bool kDzrfVBUpP = false;
      bool ZuntOQzUDI = false;
      bool KCdynGdwZB = false;
      bool oewPZahZZA = false;
      bool InksHSjIWD = false;
      bool lgdXBiYBEY = false;
      bool rEuoZtyXUm = false;
      bool hZuCzVQkqU = false;
      bool VUZVPIAXNp = false;
      bool BfUAIEsuSM = false;
      bool UMnjULlaYf = false;
      string jeJXBqNlYn;
      string HlCBdkaHwb;
      string DHoczfsnCZ;
      string iVtheAEfoP;
      string WIaPLlLjfO;
      string wCoHgcogYU;
      string xZiyEkqUVd;
      string fuRgFufZQM;
      string UJHncggmAC;
      string KXHUSxYbKa;
      string tqNBhBjICl;
      string wPPLAmRuUX;
      string EETTTHnwNI;
      string VEOpScwFGb;
      string wXjOFtIuUe;
      string edGmVoXshZ;
      string NmtsQrBYsW;
      string pLosafTEOZ;
      string zrbicqxbTc;
      string EDXfOIcqyN;
      if(jeJXBqNlYn == tqNBhBjICl){siCxnSoNMp = true;}
      else if(tqNBhBjICl == jeJXBqNlYn){ZuntOQzUDI = true;}
      if(HlCBdkaHwb == wPPLAmRuUX){VSeIaULLPY = true;}
      else if(wPPLAmRuUX == HlCBdkaHwb){KCdynGdwZB = true;}
      if(DHoczfsnCZ == EETTTHnwNI){tYFPSmnIeR = true;}
      else if(EETTTHnwNI == DHoczfsnCZ){oewPZahZZA = true;}
      if(iVtheAEfoP == VEOpScwFGb){CcGAfPpdtK = true;}
      else if(VEOpScwFGb == iVtheAEfoP){InksHSjIWD = true;}
      if(WIaPLlLjfO == wXjOFtIuUe){CjPdHlYPFs = true;}
      else if(wXjOFtIuUe == WIaPLlLjfO){lgdXBiYBEY = true;}
      if(wCoHgcogYU == edGmVoXshZ){xRaYSTdleB = true;}
      else if(edGmVoXshZ == wCoHgcogYU){rEuoZtyXUm = true;}
      if(xZiyEkqUVd == NmtsQrBYsW){eghtmrMdbL = true;}
      else if(NmtsQrBYsW == xZiyEkqUVd){hZuCzVQkqU = true;}
      if(fuRgFufZQM == pLosafTEOZ){egRFVKJbIg = true;}
      if(UJHncggmAC == zrbicqxbTc){NXCkTkCggL = true;}
      if(KXHUSxYbKa == EDXfOIcqyN){kDzrfVBUpP = true;}
      while(pLosafTEOZ == fuRgFufZQM){VUZVPIAXNp = true;}
      while(zrbicqxbTc == zrbicqxbTc){BfUAIEsuSM = true;}
      while(EDXfOIcqyN == EDXfOIcqyN){UMnjULlaYf = true;}
      if(siCxnSoNMp == true){siCxnSoNMp = false;}
      if(VSeIaULLPY == true){VSeIaULLPY = false;}
      if(tYFPSmnIeR == true){tYFPSmnIeR = false;}
      if(CcGAfPpdtK == true){CcGAfPpdtK = false;}
      if(CjPdHlYPFs == true){CjPdHlYPFs = false;}
      if(xRaYSTdleB == true){xRaYSTdleB = false;}
      if(eghtmrMdbL == true){eghtmrMdbL = false;}
      if(egRFVKJbIg == true){egRFVKJbIg = false;}
      if(NXCkTkCggL == true){NXCkTkCggL = false;}
      if(kDzrfVBUpP == true){kDzrfVBUpP = false;}
      if(ZuntOQzUDI == true){ZuntOQzUDI = false;}
      if(KCdynGdwZB == true){KCdynGdwZB = false;}
      if(oewPZahZZA == true){oewPZahZZA = false;}
      if(InksHSjIWD == true){InksHSjIWD = false;}
      if(lgdXBiYBEY == true){lgdXBiYBEY = false;}
      if(rEuoZtyXUm == true){rEuoZtyXUm = false;}
      if(hZuCzVQkqU == true){hZuCzVQkqU = false;}
      if(VUZVPIAXNp == true){VUZVPIAXNp = false;}
      if(BfUAIEsuSM == true){BfUAIEsuSM = false;}
      if(UMnjULlaYf == true){UMnjULlaYf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUSNCDPSXQ
{ 
  void RTDFCcHsed()
  { 
      bool yTfGmrHQiD = false;
      bool ROTJNEQZRi = false;
      bool PxLuCLakdw = false;
      bool otwWPfAzXd = false;
      bool spreQgylPX = false;
      bool ZpxkUAIkDb = false;
      bool QWlmOXRwsh = false;
      bool DRCmoYFgdU = false;
      bool MoUGVzxLBP = false;
      bool WPuwMWDEPs = false;
      bool PCrhTImJuw = false;
      bool ubGhPbBeQP = false;
      bool ZGtdLmVGaS = false;
      bool UAQkFJwmlN = false;
      bool LmPFTtJMfk = false;
      bool UXnzSIINVg = false;
      bool lgicatKVcF = false;
      bool fOsCEmqnKQ = false;
      bool dJZoxwMRRx = false;
      bool BhQFbdEmeZ = false;
      string uRiNCBsnVJ;
      string RrzyNEYUMY;
      string JYdqcDtVLJ;
      string QuAUcgqidu;
      string eHDMkfdLpp;
      string SWfVJVmqkz;
      string GWcLrVqeVf;
      string NopRtCVQGx;
      string ZieUqsPeKG;
      string szyenHdqTO;
      string nyoKccgOaH;
      string AVkmZWrHUy;
      string GMTOlOqKcl;
      string XdxqJasUrN;
      string MBDDGXOKFR;
      string PWWVIaeaXN;
      string kVknjVYtdy;
      string dXOGlEJPHO;
      string AgFLWAGahh;
      string wRwdbpPOTj;
      if(uRiNCBsnVJ == nyoKccgOaH){yTfGmrHQiD = true;}
      else if(nyoKccgOaH == uRiNCBsnVJ){PCrhTImJuw = true;}
      if(RrzyNEYUMY == AVkmZWrHUy){ROTJNEQZRi = true;}
      else if(AVkmZWrHUy == RrzyNEYUMY){ubGhPbBeQP = true;}
      if(JYdqcDtVLJ == GMTOlOqKcl){PxLuCLakdw = true;}
      else if(GMTOlOqKcl == JYdqcDtVLJ){ZGtdLmVGaS = true;}
      if(QuAUcgqidu == XdxqJasUrN){otwWPfAzXd = true;}
      else if(XdxqJasUrN == QuAUcgqidu){UAQkFJwmlN = true;}
      if(eHDMkfdLpp == MBDDGXOKFR){spreQgylPX = true;}
      else if(MBDDGXOKFR == eHDMkfdLpp){LmPFTtJMfk = true;}
      if(SWfVJVmqkz == PWWVIaeaXN){ZpxkUAIkDb = true;}
      else if(PWWVIaeaXN == SWfVJVmqkz){UXnzSIINVg = true;}
      if(GWcLrVqeVf == kVknjVYtdy){QWlmOXRwsh = true;}
      else if(kVknjVYtdy == GWcLrVqeVf){lgicatKVcF = true;}
      if(NopRtCVQGx == dXOGlEJPHO){DRCmoYFgdU = true;}
      if(ZieUqsPeKG == AgFLWAGahh){MoUGVzxLBP = true;}
      if(szyenHdqTO == wRwdbpPOTj){WPuwMWDEPs = true;}
      while(dXOGlEJPHO == NopRtCVQGx){fOsCEmqnKQ = true;}
      while(AgFLWAGahh == AgFLWAGahh){dJZoxwMRRx = true;}
      while(wRwdbpPOTj == wRwdbpPOTj){BhQFbdEmeZ = true;}
      if(yTfGmrHQiD == true){yTfGmrHQiD = false;}
      if(ROTJNEQZRi == true){ROTJNEQZRi = false;}
      if(PxLuCLakdw == true){PxLuCLakdw = false;}
      if(otwWPfAzXd == true){otwWPfAzXd = false;}
      if(spreQgylPX == true){spreQgylPX = false;}
      if(ZpxkUAIkDb == true){ZpxkUAIkDb = false;}
      if(QWlmOXRwsh == true){QWlmOXRwsh = false;}
      if(DRCmoYFgdU == true){DRCmoYFgdU = false;}
      if(MoUGVzxLBP == true){MoUGVzxLBP = false;}
      if(WPuwMWDEPs == true){WPuwMWDEPs = false;}
      if(PCrhTImJuw == true){PCrhTImJuw = false;}
      if(ubGhPbBeQP == true){ubGhPbBeQP = false;}
      if(ZGtdLmVGaS == true){ZGtdLmVGaS = false;}
      if(UAQkFJwmlN == true){UAQkFJwmlN = false;}
      if(LmPFTtJMfk == true){LmPFTtJMfk = false;}
      if(UXnzSIINVg == true){UXnzSIINVg = false;}
      if(lgicatKVcF == true){lgicatKVcF = false;}
      if(fOsCEmqnKQ == true){fOsCEmqnKQ = false;}
      if(dJZoxwMRRx == true){dJZoxwMRRx = false;}
      if(BhQFbdEmeZ == true){BhQFbdEmeZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JANAPUNNLQ
{ 
  void rwclizbFID()
  { 
      bool OfQEFfrxZo = false;
      bool pKyAijhJdu = false;
      bool wbNsbRYjmE = false;
      bool AAzzeLiXgt = false;
      bool DCmSJbpKro = false;
      bool RnkKXlRWbn = false;
      bool GHKVopLyVW = false;
      bool BJbiqtouiA = false;
      bool aOrxlLPnbr = false;
      bool tLusmwrQcT = false;
      bool PrnUnHMBSc = false;
      bool wWmbNrOMic = false;
      bool aWWccoNhuu = false;
      bool CYROjhaWId = false;
      bool zNVywXYSfu = false;
      bool gegAssUKqz = false;
      bool tdFXaXEXre = false;
      bool QrEFdMAXgF = false;
      bool QuCAOWqRVp = false;
      bool MPeJjVHyWX = false;
      string rWeSTyIBjc;
      string pEnjibTBUo;
      string dsGmafZWLM;
      string yIHyYBMAWx;
      string rKCWMiJOZk;
      string LiSsKzQrqm;
      string XlpWdgwpLh;
      string OSdXxTqjar;
      string VKwZBPoOmZ;
      string kTJiYFTfre;
      string lSDqVrFuup;
      string HfRzQNoPVO;
      string qhCkxtJtyq;
      string zKquFDGFDI;
      string KtSwRECKRL;
      string QEKdmEQRtb;
      string iKwEpxoVtN;
      string GjMMDxOFTs;
      string rzbmauAMIA;
      string loKbZzxOGU;
      if(rWeSTyIBjc == lSDqVrFuup){OfQEFfrxZo = true;}
      else if(lSDqVrFuup == rWeSTyIBjc){PrnUnHMBSc = true;}
      if(pEnjibTBUo == HfRzQNoPVO){pKyAijhJdu = true;}
      else if(HfRzQNoPVO == pEnjibTBUo){wWmbNrOMic = true;}
      if(dsGmafZWLM == qhCkxtJtyq){wbNsbRYjmE = true;}
      else if(qhCkxtJtyq == dsGmafZWLM){aWWccoNhuu = true;}
      if(yIHyYBMAWx == zKquFDGFDI){AAzzeLiXgt = true;}
      else if(zKquFDGFDI == yIHyYBMAWx){CYROjhaWId = true;}
      if(rKCWMiJOZk == KtSwRECKRL){DCmSJbpKro = true;}
      else if(KtSwRECKRL == rKCWMiJOZk){zNVywXYSfu = true;}
      if(LiSsKzQrqm == QEKdmEQRtb){RnkKXlRWbn = true;}
      else if(QEKdmEQRtb == LiSsKzQrqm){gegAssUKqz = true;}
      if(XlpWdgwpLh == iKwEpxoVtN){GHKVopLyVW = true;}
      else if(iKwEpxoVtN == XlpWdgwpLh){tdFXaXEXre = true;}
      if(OSdXxTqjar == GjMMDxOFTs){BJbiqtouiA = true;}
      if(VKwZBPoOmZ == rzbmauAMIA){aOrxlLPnbr = true;}
      if(kTJiYFTfre == loKbZzxOGU){tLusmwrQcT = true;}
      while(GjMMDxOFTs == OSdXxTqjar){QrEFdMAXgF = true;}
      while(rzbmauAMIA == rzbmauAMIA){QuCAOWqRVp = true;}
      while(loKbZzxOGU == loKbZzxOGU){MPeJjVHyWX = true;}
      if(OfQEFfrxZo == true){OfQEFfrxZo = false;}
      if(pKyAijhJdu == true){pKyAijhJdu = false;}
      if(wbNsbRYjmE == true){wbNsbRYjmE = false;}
      if(AAzzeLiXgt == true){AAzzeLiXgt = false;}
      if(DCmSJbpKro == true){DCmSJbpKro = false;}
      if(RnkKXlRWbn == true){RnkKXlRWbn = false;}
      if(GHKVopLyVW == true){GHKVopLyVW = false;}
      if(BJbiqtouiA == true){BJbiqtouiA = false;}
      if(aOrxlLPnbr == true){aOrxlLPnbr = false;}
      if(tLusmwrQcT == true){tLusmwrQcT = false;}
      if(PrnUnHMBSc == true){PrnUnHMBSc = false;}
      if(wWmbNrOMic == true){wWmbNrOMic = false;}
      if(aWWccoNhuu == true){aWWccoNhuu = false;}
      if(CYROjhaWId == true){CYROjhaWId = false;}
      if(zNVywXYSfu == true){zNVywXYSfu = false;}
      if(gegAssUKqz == true){gegAssUKqz = false;}
      if(tdFXaXEXre == true){tdFXaXEXre = false;}
      if(QrEFdMAXgF == true){QrEFdMAXgF = false;}
      if(QuCAOWqRVp == true){QuCAOWqRVp = false;}
      if(MPeJjVHyWX == true){MPeJjVHyWX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WIBAMNQYPS
{ 
  void IeUmBwwQPa()
  { 
      bool DwWUVQCXcm = false;
      bool QSlYRlegRR = false;
      bool CudunatixH = false;
      bool RisxRSfqbs = false;
      bool AKXtBIbyRn = false;
      bool gPySPHSbgu = false;
      bool WSZUVgZoGy = false;
      bool FmFYQrXjte = false;
      bool zwQJaCjagJ = false;
      bool AEKfWhjCYT = false;
      bool ilqShsJYCX = false;
      bool jigBwaBPsS = false;
      bool wzIxyBcYCi = false;
      bool IULawMExah = false;
      bool rLXJYQWIju = false;
      bool fUIFWjdsUf = false;
      bool QkWTOPWGFj = false;
      bool VEnLakazYg = false;
      bool eToGDmMFDL = false;
      bool hKcuRHnEtJ = false;
      string zXHdSpcMRa;
      string rsEecHdwmo;
      string pZIhwVxNFm;
      string IipVrLeLXL;
      string fMNnDJOJgi;
      string uOQcXZPZgw;
      string sOGeSJDhlQ;
      string cRYbIdLUdm;
      string GmfWrtRMyR;
      string uEdaRQFhVt;
      string GgWPFcpoTs;
      string NuwtpFhjmX;
      string qqiTVXmyJr;
      string YcyjgZQQQO;
      string EcrFEAIjkL;
      string hVuxCOxCtg;
      string orebUkwLMP;
      string oRSXTOydPU;
      string PDMyJDhBhR;
      string bNWjZLxPjS;
      if(zXHdSpcMRa == GgWPFcpoTs){DwWUVQCXcm = true;}
      else if(GgWPFcpoTs == zXHdSpcMRa){ilqShsJYCX = true;}
      if(rsEecHdwmo == NuwtpFhjmX){QSlYRlegRR = true;}
      else if(NuwtpFhjmX == rsEecHdwmo){jigBwaBPsS = true;}
      if(pZIhwVxNFm == qqiTVXmyJr){CudunatixH = true;}
      else if(qqiTVXmyJr == pZIhwVxNFm){wzIxyBcYCi = true;}
      if(IipVrLeLXL == YcyjgZQQQO){RisxRSfqbs = true;}
      else if(YcyjgZQQQO == IipVrLeLXL){IULawMExah = true;}
      if(fMNnDJOJgi == EcrFEAIjkL){AKXtBIbyRn = true;}
      else if(EcrFEAIjkL == fMNnDJOJgi){rLXJYQWIju = true;}
      if(uOQcXZPZgw == hVuxCOxCtg){gPySPHSbgu = true;}
      else if(hVuxCOxCtg == uOQcXZPZgw){fUIFWjdsUf = true;}
      if(sOGeSJDhlQ == orebUkwLMP){WSZUVgZoGy = true;}
      else if(orebUkwLMP == sOGeSJDhlQ){QkWTOPWGFj = true;}
      if(cRYbIdLUdm == oRSXTOydPU){FmFYQrXjte = true;}
      if(GmfWrtRMyR == PDMyJDhBhR){zwQJaCjagJ = true;}
      if(uEdaRQFhVt == bNWjZLxPjS){AEKfWhjCYT = true;}
      while(oRSXTOydPU == cRYbIdLUdm){VEnLakazYg = true;}
      while(PDMyJDhBhR == PDMyJDhBhR){eToGDmMFDL = true;}
      while(bNWjZLxPjS == bNWjZLxPjS){hKcuRHnEtJ = true;}
      if(DwWUVQCXcm == true){DwWUVQCXcm = false;}
      if(QSlYRlegRR == true){QSlYRlegRR = false;}
      if(CudunatixH == true){CudunatixH = false;}
      if(RisxRSfqbs == true){RisxRSfqbs = false;}
      if(AKXtBIbyRn == true){AKXtBIbyRn = false;}
      if(gPySPHSbgu == true){gPySPHSbgu = false;}
      if(WSZUVgZoGy == true){WSZUVgZoGy = false;}
      if(FmFYQrXjte == true){FmFYQrXjte = false;}
      if(zwQJaCjagJ == true){zwQJaCjagJ = false;}
      if(AEKfWhjCYT == true){AEKfWhjCYT = false;}
      if(ilqShsJYCX == true){ilqShsJYCX = false;}
      if(jigBwaBPsS == true){jigBwaBPsS = false;}
      if(wzIxyBcYCi == true){wzIxyBcYCi = false;}
      if(IULawMExah == true){IULawMExah = false;}
      if(rLXJYQWIju == true){rLXJYQWIju = false;}
      if(fUIFWjdsUf == true){fUIFWjdsUf = false;}
      if(QkWTOPWGFj == true){QkWTOPWGFj = false;}
      if(VEnLakazYg == true){VEnLakazYg = false;}
      if(eToGDmMFDL == true){eToGDmMFDL = false;}
      if(hKcuRHnEtJ == true){hKcuRHnEtJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BGXYSZKICK
{ 
  void umbyShLbPQ()
  { 
      bool otUmrJpfwi = false;
      bool KXPilLkpXj = false;
      bool rYLyJkCVMW = false;
      bool fAjUiIyZEN = false;
      bool SIQYTPJdAU = false;
      bool NKUShPhWcH = false;
      bool GUTZDKnuzc = false;
      bool NLlKQjImds = false;
      bool aYVrIVeQmS = false;
      bool abwxGynqVJ = false;
      bool bOdWHBXKBx = false;
      bool HtrjfhybQg = false;
      bool eXIgCkPoDS = false;
      bool wRRURLtyjH = false;
      bool xUOoKfiMQY = false;
      bool zLZndEGxUV = false;
      bool liGiApcWRT = false;
      bool mzqJjKISVV = false;
      bool CDXeSjqcpN = false;
      bool FxdOVNNfnU = false;
      string QkCuZUhuje;
      string OimyIqMKAY;
      string IdIwPeXWVZ;
      string URXBqSPndy;
      string TLmtjuhWwj;
      string TbotAmcGeu;
      string xKYJKxKlHo;
      string bYgBEwqNLT;
      string wAalGrbdAE;
      string pJIiAImcjl;
      string kwOGIuunpD;
      string uOtLyxjmDS;
      string VgkDzSQxAu;
      string JNdZiAkTcK;
      string xnmxIaOxkD;
      string YAYRQELLHp;
      string exmtshkUcy;
      string LPJrVgsmuY;
      string DSMwWJoMId;
      string nZMmfzAsDa;
      if(QkCuZUhuje == kwOGIuunpD){otUmrJpfwi = true;}
      else if(kwOGIuunpD == QkCuZUhuje){bOdWHBXKBx = true;}
      if(OimyIqMKAY == uOtLyxjmDS){KXPilLkpXj = true;}
      else if(uOtLyxjmDS == OimyIqMKAY){HtrjfhybQg = true;}
      if(IdIwPeXWVZ == VgkDzSQxAu){rYLyJkCVMW = true;}
      else if(VgkDzSQxAu == IdIwPeXWVZ){eXIgCkPoDS = true;}
      if(URXBqSPndy == JNdZiAkTcK){fAjUiIyZEN = true;}
      else if(JNdZiAkTcK == URXBqSPndy){wRRURLtyjH = true;}
      if(TLmtjuhWwj == xnmxIaOxkD){SIQYTPJdAU = true;}
      else if(xnmxIaOxkD == TLmtjuhWwj){xUOoKfiMQY = true;}
      if(TbotAmcGeu == YAYRQELLHp){NKUShPhWcH = true;}
      else if(YAYRQELLHp == TbotAmcGeu){zLZndEGxUV = true;}
      if(xKYJKxKlHo == exmtshkUcy){GUTZDKnuzc = true;}
      else if(exmtshkUcy == xKYJKxKlHo){liGiApcWRT = true;}
      if(bYgBEwqNLT == LPJrVgsmuY){NLlKQjImds = true;}
      if(wAalGrbdAE == DSMwWJoMId){aYVrIVeQmS = true;}
      if(pJIiAImcjl == nZMmfzAsDa){abwxGynqVJ = true;}
      while(LPJrVgsmuY == bYgBEwqNLT){mzqJjKISVV = true;}
      while(DSMwWJoMId == DSMwWJoMId){CDXeSjqcpN = true;}
      while(nZMmfzAsDa == nZMmfzAsDa){FxdOVNNfnU = true;}
      if(otUmrJpfwi == true){otUmrJpfwi = false;}
      if(KXPilLkpXj == true){KXPilLkpXj = false;}
      if(rYLyJkCVMW == true){rYLyJkCVMW = false;}
      if(fAjUiIyZEN == true){fAjUiIyZEN = false;}
      if(SIQYTPJdAU == true){SIQYTPJdAU = false;}
      if(NKUShPhWcH == true){NKUShPhWcH = false;}
      if(GUTZDKnuzc == true){GUTZDKnuzc = false;}
      if(NLlKQjImds == true){NLlKQjImds = false;}
      if(aYVrIVeQmS == true){aYVrIVeQmS = false;}
      if(abwxGynqVJ == true){abwxGynqVJ = false;}
      if(bOdWHBXKBx == true){bOdWHBXKBx = false;}
      if(HtrjfhybQg == true){HtrjfhybQg = false;}
      if(eXIgCkPoDS == true){eXIgCkPoDS = false;}
      if(wRRURLtyjH == true){wRRURLtyjH = false;}
      if(xUOoKfiMQY == true){xUOoKfiMQY = false;}
      if(zLZndEGxUV == true){zLZndEGxUV = false;}
      if(liGiApcWRT == true){liGiApcWRT = false;}
      if(mzqJjKISVV == true){mzqJjKISVV = false;}
      if(CDXeSjqcpN == true){CDXeSjqcpN = false;}
      if(FxdOVNNfnU == true){FxdOVNNfnU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RLHGEJKSIU
{ 
  void YIhELqjVIN()
  { 
      bool pIChyCoRmO = false;
      bool QRDWhsIcGi = false;
      bool mmTChhJGjW = false;
      bool YqEXzmkbzg = false;
      bool iSowyGRLId = false;
      bool ZPUooCoAzP = false;
      bool shgQpZMeWt = false;
      bool IfcYATyXEa = false;
      bool PxyFwJVOix = false;
      bool yjcjnBkXGX = false;
      bool tmnNUtlwoU = false;
      bool DQwXzuiaUf = false;
      bool ExwZuYDsjz = false;
      bool iZRfgcJkkC = false;
      bool WYZNsgnFjs = false;
      bool RKDZTwpNRw = false;
      bool psLplczQpW = false;
      bool kypRJeXhfN = false;
      bool jyIpgXWqLj = false;
      bool mwSnLcMjbQ = false;
      string QrdlBKqmZS;
      string bjrjlhCmOf;
      string OnmAGwGBnU;
      string wyOfHxnNWj;
      string WBrTsoTexH;
      string bfFcfbFdfF;
      string EpyFVcVLcn;
      string snPeJNwTHQ;
      string caDgrQskAe;
      string rJhRefDlxP;
      string THCINmPaTS;
      string flVObclQMF;
      string jjLywjGyAc;
      string KJVqxUYuTE;
      string ASRgyGmSoC;
      string slZrfiwDMd;
      string gRZpHWQeQH;
      string DqxIEQSdzo;
      string wmJxjXjcKO;
      string YVhpXhrbYb;
      if(QrdlBKqmZS == THCINmPaTS){pIChyCoRmO = true;}
      else if(THCINmPaTS == QrdlBKqmZS){tmnNUtlwoU = true;}
      if(bjrjlhCmOf == flVObclQMF){QRDWhsIcGi = true;}
      else if(flVObclQMF == bjrjlhCmOf){DQwXzuiaUf = true;}
      if(OnmAGwGBnU == jjLywjGyAc){mmTChhJGjW = true;}
      else if(jjLywjGyAc == OnmAGwGBnU){ExwZuYDsjz = true;}
      if(wyOfHxnNWj == KJVqxUYuTE){YqEXzmkbzg = true;}
      else if(KJVqxUYuTE == wyOfHxnNWj){iZRfgcJkkC = true;}
      if(WBrTsoTexH == ASRgyGmSoC){iSowyGRLId = true;}
      else if(ASRgyGmSoC == WBrTsoTexH){WYZNsgnFjs = true;}
      if(bfFcfbFdfF == slZrfiwDMd){ZPUooCoAzP = true;}
      else if(slZrfiwDMd == bfFcfbFdfF){RKDZTwpNRw = true;}
      if(EpyFVcVLcn == gRZpHWQeQH){shgQpZMeWt = true;}
      else if(gRZpHWQeQH == EpyFVcVLcn){psLplczQpW = true;}
      if(snPeJNwTHQ == DqxIEQSdzo){IfcYATyXEa = true;}
      if(caDgrQskAe == wmJxjXjcKO){PxyFwJVOix = true;}
      if(rJhRefDlxP == YVhpXhrbYb){yjcjnBkXGX = true;}
      while(DqxIEQSdzo == snPeJNwTHQ){kypRJeXhfN = true;}
      while(wmJxjXjcKO == wmJxjXjcKO){jyIpgXWqLj = true;}
      while(YVhpXhrbYb == YVhpXhrbYb){mwSnLcMjbQ = true;}
      if(pIChyCoRmO == true){pIChyCoRmO = false;}
      if(QRDWhsIcGi == true){QRDWhsIcGi = false;}
      if(mmTChhJGjW == true){mmTChhJGjW = false;}
      if(YqEXzmkbzg == true){YqEXzmkbzg = false;}
      if(iSowyGRLId == true){iSowyGRLId = false;}
      if(ZPUooCoAzP == true){ZPUooCoAzP = false;}
      if(shgQpZMeWt == true){shgQpZMeWt = false;}
      if(IfcYATyXEa == true){IfcYATyXEa = false;}
      if(PxyFwJVOix == true){PxyFwJVOix = false;}
      if(yjcjnBkXGX == true){yjcjnBkXGX = false;}
      if(tmnNUtlwoU == true){tmnNUtlwoU = false;}
      if(DQwXzuiaUf == true){DQwXzuiaUf = false;}
      if(ExwZuYDsjz == true){ExwZuYDsjz = false;}
      if(iZRfgcJkkC == true){iZRfgcJkkC = false;}
      if(WYZNsgnFjs == true){WYZNsgnFjs = false;}
      if(RKDZTwpNRw == true){RKDZTwpNRw = false;}
      if(psLplczQpW == true){psLplczQpW = false;}
      if(kypRJeXhfN == true){kypRJeXhfN = false;}
      if(jyIpgXWqLj == true){jyIpgXWqLj = false;}
      if(mwSnLcMjbQ == true){mwSnLcMjbQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UMRVCHBOQJ
{ 
  void ZlxwyDqbYR()
  { 
      bool jTgswkQZyO = false;
      bool FsJYLpmDJo = false;
      bool YTBRqMUzxS = false;
      bool YBwLrPSBpm = false;
      bool VlLQBIuUYE = false;
      bool hZlNiQSOBi = false;
      bool PRbfoExxgu = false;
      bool XlMVTmIjPh = false;
      bool RAZsjzOiba = false;
      bool xDzGXDJeax = false;
      bool LxndguNPsw = false;
      bool IhySRPriup = false;
      bool oNVFyTlFyP = false;
      bool ccISWTLuLn = false;
      bool kzofSOEfoI = false;
      bool LaikIxbifM = false;
      bool JHRcTeYfwx = false;
      bool EwWGEpXoli = false;
      bool OGQoECsWKY = false;
      bool rbPyecgMMm = false;
      string UJVlVOMYWE;
      string xjlbQGtuzu;
      string qcKGUNpMBP;
      string tPZMClsDjk;
      string LnClUkwQXq;
      string kaFpSqyOQH;
      string XzXHJgJYYe;
      string NqKNjDZYkj;
      string RYnJeTKjtK;
      string ndlcMLPucn;
      string aWqrdtQqGP;
      string QZdgozLOcp;
      string WZdNqiEhAY;
      string mewxIuhuej;
      string DTcetNAFmN;
      string AASlRBrcBt;
      string ohphbldgYt;
      string RPjrmCwzTc;
      string iztmXlMJfG;
      string CEtktUcuCI;
      if(UJVlVOMYWE == aWqrdtQqGP){jTgswkQZyO = true;}
      else if(aWqrdtQqGP == UJVlVOMYWE){LxndguNPsw = true;}
      if(xjlbQGtuzu == QZdgozLOcp){FsJYLpmDJo = true;}
      else if(QZdgozLOcp == xjlbQGtuzu){IhySRPriup = true;}
      if(qcKGUNpMBP == WZdNqiEhAY){YTBRqMUzxS = true;}
      else if(WZdNqiEhAY == qcKGUNpMBP){oNVFyTlFyP = true;}
      if(tPZMClsDjk == mewxIuhuej){YBwLrPSBpm = true;}
      else if(mewxIuhuej == tPZMClsDjk){ccISWTLuLn = true;}
      if(LnClUkwQXq == DTcetNAFmN){VlLQBIuUYE = true;}
      else if(DTcetNAFmN == LnClUkwQXq){kzofSOEfoI = true;}
      if(kaFpSqyOQH == AASlRBrcBt){hZlNiQSOBi = true;}
      else if(AASlRBrcBt == kaFpSqyOQH){LaikIxbifM = true;}
      if(XzXHJgJYYe == ohphbldgYt){PRbfoExxgu = true;}
      else if(ohphbldgYt == XzXHJgJYYe){JHRcTeYfwx = true;}
      if(NqKNjDZYkj == RPjrmCwzTc){XlMVTmIjPh = true;}
      if(RYnJeTKjtK == iztmXlMJfG){RAZsjzOiba = true;}
      if(ndlcMLPucn == CEtktUcuCI){xDzGXDJeax = true;}
      while(RPjrmCwzTc == NqKNjDZYkj){EwWGEpXoli = true;}
      while(iztmXlMJfG == iztmXlMJfG){OGQoECsWKY = true;}
      while(CEtktUcuCI == CEtktUcuCI){rbPyecgMMm = true;}
      if(jTgswkQZyO == true){jTgswkQZyO = false;}
      if(FsJYLpmDJo == true){FsJYLpmDJo = false;}
      if(YTBRqMUzxS == true){YTBRqMUzxS = false;}
      if(YBwLrPSBpm == true){YBwLrPSBpm = false;}
      if(VlLQBIuUYE == true){VlLQBIuUYE = false;}
      if(hZlNiQSOBi == true){hZlNiQSOBi = false;}
      if(PRbfoExxgu == true){PRbfoExxgu = false;}
      if(XlMVTmIjPh == true){XlMVTmIjPh = false;}
      if(RAZsjzOiba == true){RAZsjzOiba = false;}
      if(xDzGXDJeax == true){xDzGXDJeax = false;}
      if(LxndguNPsw == true){LxndguNPsw = false;}
      if(IhySRPriup == true){IhySRPriup = false;}
      if(oNVFyTlFyP == true){oNVFyTlFyP = false;}
      if(ccISWTLuLn == true){ccISWTLuLn = false;}
      if(kzofSOEfoI == true){kzofSOEfoI = false;}
      if(LaikIxbifM == true){LaikIxbifM = false;}
      if(JHRcTeYfwx == true){JHRcTeYfwx = false;}
      if(EwWGEpXoli == true){EwWGEpXoli = false;}
      if(OGQoECsWKY == true){OGQoECsWKY = false;}
      if(rbPyecgMMm == true){rbPyecgMMm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OIHTXNWYFM
{ 
  void lsxrIxBZDI()
  { 
      bool VGkqfhhbpi = false;
      bool cOgrFARZTR = false;
      bool ipytrCzKHf = false;
      bool SfnmTExpum = false;
      bool fDcQJhsReH = false;
      bool qLEfPeIqyd = false;
      bool hWTKPxatYA = false;
      bool DbegleNhjJ = false;
      bool IheAnHbHXo = false;
      bool wFqRFIiRAM = false;
      bool HzreDPfXsj = false;
      bool RZGoUzqTVI = false;
      bool VSWiExjNbc = false;
      bool uugXBJoAwX = false;
      bool bDOmXVzCwF = false;
      bool RPwrqobJZG = false;
      bool eSwPnVshmK = false;
      bool KpWyfRDiLh = false;
      bool yhQVLfzogM = false;
      bool gfZprIHyzB = false;
      string JOhatTKwZk;
      string GCEHmFWDpA;
      string WCaZBsgLRo;
      string RkWnHczwUU;
      string sEhxDfeTOk;
      string LwIHnGmIYA;
      string lzdjTVfPAK;
      string FZiUGRUdVV;
      string NNwgcVbOAA;
      string opWTitaxdh;
      string zPSDelNnBW;
      string lJlDmYCxGx;
      string sRPzVOCOlM;
      string qWznVxtrBq;
      string InMcNfETgK;
      string qdqfnhAThQ;
      string izCoeOJxho;
      string dJwPoFEllo;
      string KigbUNfTzm;
      string xaKkHJlXyy;
      if(JOhatTKwZk == zPSDelNnBW){VGkqfhhbpi = true;}
      else if(zPSDelNnBW == JOhatTKwZk){HzreDPfXsj = true;}
      if(GCEHmFWDpA == lJlDmYCxGx){cOgrFARZTR = true;}
      else if(lJlDmYCxGx == GCEHmFWDpA){RZGoUzqTVI = true;}
      if(WCaZBsgLRo == sRPzVOCOlM){ipytrCzKHf = true;}
      else if(sRPzVOCOlM == WCaZBsgLRo){VSWiExjNbc = true;}
      if(RkWnHczwUU == qWznVxtrBq){SfnmTExpum = true;}
      else if(qWznVxtrBq == RkWnHczwUU){uugXBJoAwX = true;}
      if(sEhxDfeTOk == InMcNfETgK){fDcQJhsReH = true;}
      else if(InMcNfETgK == sEhxDfeTOk){bDOmXVzCwF = true;}
      if(LwIHnGmIYA == qdqfnhAThQ){qLEfPeIqyd = true;}
      else if(qdqfnhAThQ == LwIHnGmIYA){RPwrqobJZG = true;}
      if(lzdjTVfPAK == izCoeOJxho){hWTKPxatYA = true;}
      else if(izCoeOJxho == lzdjTVfPAK){eSwPnVshmK = true;}
      if(FZiUGRUdVV == dJwPoFEllo){DbegleNhjJ = true;}
      if(NNwgcVbOAA == KigbUNfTzm){IheAnHbHXo = true;}
      if(opWTitaxdh == xaKkHJlXyy){wFqRFIiRAM = true;}
      while(dJwPoFEllo == FZiUGRUdVV){KpWyfRDiLh = true;}
      while(KigbUNfTzm == KigbUNfTzm){yhQVLfzogM = true;}
      while(xaKkHJlXyy == xaKkHJlXyy){gfZprIHyzB = true;}
      if(VGkqfhhbpi == true){VGkqfhhbpi = false;}
      if(cOgrFARZTR == true){cOgrFARZTR = false;}
      if(ipytrCzKHf == true){ipytrCzKHf = false;}
      if(SfnmTExpum == true){SfnmTExpum = false;}
      if(fDcQJhsReH == true){fDcQJhsReH = false;}
      if(qLEfPeIqyd == true){qLEfPeIqyd = false;}
      if(hWTKPxatYA == true){hWTKPxatYA = false;}
      if(DbegleNhjJ == true){DbegleNhjJ = false;}
      if(IheAnHbHXo == true){IheAnHbHXo = false;}
      if(wFqRFIiRAM == true){wFqRFIiRAM = false;}
      if(HzreDPfXsj == true){HzreDPfXsj = false;}
      if(RZGoUzqTVI == true){RZGoUzqTVI = false;}
      if(VSWiExjNbc == true){VSWiExjNbc = false;}
      if(uugXBJoAwX == true){uugXBJoAwX = false;}
      if(bDOmXVzCwF == true){bDOmXVzCwF = false;}
      if(RPwrqobJZG == true){RPwrqobJZG = false;}
      if(eSwPnVshmK == true){eSwPnVshmK = false;}
      if(KpWyfRDiLh == true){KpWyfRDiLh = false;}
      if(yhQVLfzogM == true){yhQVLfzogM = false;}
      if(gfZprIHyzB == true){gfZprIHyzB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBLTGZXYAA
{ 
  void QtCHORgInn()
  { 
      bool UbiQzGEWAB = false;
      bool IxQtBfCycz = false;
      bool oAlAsdpJLC = false;
      bool yDdSNhQnSM = false;
      bool QLrirXmbTh = false;
      bool RLNfHUohXV = false;
      bool PuLyDFSyfS = false;
      bool OOfPidICIU = false;
      bool pNodjlpyKs = false;
      bool riPxxVzsfm = false;
      bool FowBSDfyxd = false;
      bool MlZDfBFhOR = false;
      bool OUnmZfyhSM = false;
      bool dOWUOARnKg = false;
      bool FrAfgGILRu = false;
      bool QReNXkBIal = false;
      bool EyejAxOFoe = false;
      bool iRWgMWTHGT = false;
      bool XmQWwLjJwd = false;
      bool zJMYbHMQfi = false;
      string rgfYnHFRhw;
      string sXqpmJTSWj;
      string LpiTbBkSCE;
      string YMVDcTfpJW;
      string RKtublFgsA;
      string tCRAbBxLxm;
      string WlOdWfCmNT;
      string ddIARBwnro;
      string uDZCKWtUba;
      string WTrWzfuQXw;
      string jSSZVQsRha;
      string EITHqSMLSA;
      string kgLlwKkkAl;
      string FfPwFckzgs;
      string cclBWNzkfg;
      string SixXKDHgcL;
      string fIRwVYrXCO;
      string hMeZWItJPi;
      string KzFSSVirkB;
      string VDWUNUKpfx;
      if(rgfYnHFRhw == jSSZVQsRha){UbiQzGEWAB = true;}
      else if(jSSZVQsRha == rgfYnHFRhw){FowBSDfyxd = true;}
      if(sXqpmJTSWj == EITHqSMLSA){IxQtBfCycz = true;}
      else if(EITHqSMLSA == sXqpmJTSWj){MlZDfBFhOR = true;}
      if(LpiTbBkSCE == kgLlwKkkAl){oAlAsdpJLC = true;}
      else if(kgLlwKkkAl == LpiTbBkSCE){OUnmZfyhSM = true;}
      if(YMVDcTfpJW == FfPwFckzgs){yDdSNhQnSM = true;}
      else if(FfPwFckzgs == YMVDcTfpJW){dOWUOARnKg = true;}
      if(RKtublFgsA == cclBWNzkfg){QLrirXmbTh = true;}
      else if(cclBWNzkfg == RKtublFgsA){FrAfgGILRu = true;}
      if(tCRAbBxLxm == SixXKDHgcL){RLNfHUohXV = true;}
      else if(SixXKDHgcL == tCRAbBxLxm){QReNXkBIal = true;}
      if(WlOdWfCmNT == fIRwVYrXCO){PuLyDFSyfS = true;}
      else if(fIRwVYrXCO == WlOdWfCmNT){EyejAxOFoe = true;}
      if(ddIARBwnro == hMeZWItJPi){OOfPidICIU = true;}
      if(uDZCKWtUba == KzFSSVirkB){pNodjlpyKs = true;}
      if(WTrWzfuQXw == VDWUNUKpfx){riPxxVzsfm = true;}
      while(hMeZWItJPi == ddIARBwnro){iRWgMWTHGT = true;}
      while(KzFSSVirkB == KzFSSVirkB){XmQWwLjJwd = true;}
      while(VDWUNUKpfx == VDWUNUKpfx){zJMYbHMQfi = true;}
      if(UbiQzGEWAB == true){UbiQzGEWAB = false;}
      if(IxQtBfCycz == true){IxQtBfCycz = false;}
      if(oAlAsdpJLC == true){oAlAsdpJLC = false;}
      if(yDdSNhQnSM == true){yDdSNhQnSM = false;}
      if(QLrirXmbTh == true){QLrirXmbTh = false;}
      if(RLNfHUohXV == true){RLNfHUohXV = false;}
      if(PuLyDFSyfS == true){PuLyDFSyfS = false;}
      if(OOfPidICIU == true){OOfPidICIU = false;}
      if(pNodjlpyKs == true){pNodjlpyKs = false;}
      if(riPxxVzsfm == true){riPxxVzsfm = false;}
      if(FowBSDfyxd == true){FowBSDfyxd = false;}
      if(MlZDfBFhOR == true){MlZDfBFhOR = false;}
      if(OUnmZfyhSM == true){OUnmZfyhSM = false;}
      if(dOWUOARnKg == true){dOWUOARnKg = false;}
      if(FrAfgGILRu == true){FrAfgGILRu = false;}
      if(QReNXkBIal == true){QReNXkBIal = false;}
      if(EyejAxOFoe == true){EyejAxOFoe = false;}
      if(iRWgMWTHGT == true){iRWgMWTHGT = false;}
      if(XmQWwLjJwd == true){XmQWwLjJwd = false;}
      if(zJMYbHMQfi == true){zJMYbHMQfi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NUFYKWLCZR
{ 
  void zJaMOdXJGn()
  { 
      bool EzTJFFceze = false;
      bool xrNHHuAnse = false;
      bool TDdQfKOlEB = false;
      bool TkmVkIlBHP = false;
      bool dgCELnkjrn = false;
      bool nDhxnAVDcu = false;
      bool pqZxKLEqVz = false;
      bool IyfdBlAYEr = false;
      bool YetPMPDphj = false;
      bool miYLYlGEtA = false;
      bool itNsepWDuB = false;
      bool AwzkWLxKkt = false;
      bool IOIkLZZUEO = false;
      bool eueDIdRBjW = false;
      bool rztgjqjnoN = false;
      bool owTzqUlbgF = false;
      bool PCzgWEQubr = false;
      bool swZNBJUbBU = false;
      bool plepZhbfMn = false;
      bool roTeGpzNJf = false;
      string JPKNBPSzla;
      string YPdqfbBBDd;
      string DbszlXSkAZ;
      string otYWdbJOzM;
      string oPETbEuUAB;
      string nuVkxgVKbc;
      string xgzMldpGME;
      string SmCqomWZXh;
      string cxkylsXmZw;
      string FymVOHQrhx;
      string NnHwiBrdwJ;
      string KwmsAzuBZr;
      string GDfPyTzgcg;
      string WeqZTnpoOk;
      string BtpPlILsVO;
      string LPSpqKIqxP;
      string BLBOmeEMZL;
      string JGlnpMMQdo;
      string HFLNUHLBiJ;
      string fzqzjorbcH;
      if(JPKNBPSzla == NnHwiBrdwJ){EzTJFFceze = true;}
      else if(NnHwiBrdwJ == JPKNBPSzla){itNsepWDuB = true;}
      if(YPdqfbBBDd == KwmsAzuBZr){xrNHHuAnse = true;}
      else if(KwmsAzuBZr == YPdqfbBBDd){AwzkWLxKkt = true;}
      if(DbszlXSkAZ == GDfPyTzgcg){TDdQfKOlEB = true;}
      else if(GDfPyTzgcg == DbszlXSkAZ){IOIkLZZUEO = true;}
      if(otYWdbJOzM == WeqZTnpoOk){TkmVkIlBHP = true;}
      else if(WeqZTnpoOk == otYWdbJOzM){eueDIdRBjW = true;}
      if(oPETbEuUAB == BtpPlILsVO){dgCELnkjrn = true;}
      else if(BtpPlILsVO == oPETbEuUAB){rztgjqjnoN = true;}
      if(nuVkxgVKbc == LPSpqKIqxP){nDhxnAVDcu = true;}
      else if(LPSpqKIqxP == nuVkxgVKbc){owTzqUlbgF = true;}
      if(xgzMldpGME == BLBOmeEMZL){pqZxKLEqVz = true;}
      else if(BLBOmeEMZL == xgzMldpGME){PCzgWEQubr = true;}
      if(SmCqomWZXh == JGlnpMMQdo){IyfdBlAYEr = true;}
      if(cxkylsXmZw == HFLNUHLBiJ){YetPMPDphj = true;}
      if(FymVOHQrhx == fzqzjorbcH){miYLYlGEtA = true;}
      while(JGlnpMMQdo == SmCqomWZXh){swZNBJUbBU = true;}
      while(HFLNUHLBiJ == HFLNUHLBiJ){plepZhbfMn = true;}
      while(fzqzjorbcH == fzqzjorbcH){roTeGpzNJf = true;}
      if(EzTJFFceze == true){EzTJFFceze = false;}
      if(xrNHHuAnse == true){xrNHHuAnse = false;}
      if(TDdQfKOlEB == true){TDdQfKOlEB = false;}
      if(TkmVkIlBHP == true){TkmVkIlBHP = false;}
      if(dgCELnkjrn == true){dgCELnkjrn = false;}
      if(nDhxnAVDcu == true){nDhxnAVDcu = false;}
      if(pqZxKLEqVz == true){pqZxKLEqVz = false;}
      if(IyfdBlAYEr == true){IyfdBlAYEr = false;}
      if(YetPMPDphj == true){YetPMPDphj = false;}
      if(miYLYlGEtA == true){miYLYlGEtA = false;}
      if(itNsepWDuB == true){itNsepWDuB = false;}
      if(AwzkWLxKkt == true){AwzkWLxKkt = false;}
      if(IOIkLZZUEO == true){IOIkLZZUEO = false;}
      if(eueDIdRBjW == true){eueDIdRBjW = false;}
      if(rztgjqjnoN == true){rztgjqjnoN = false;}
      if(owTzqUlbgF == true){owTzqUlbgF = false;}
      if(PCzgWEQubr == true){PCzgWEQubr = false;}
      if(swZNBJUbBU == true){swZNBJUbBU = false;}
      if(plepZhbfMn == true){plepZhbfMn = false;}
      if(roTeGpzNJf == true){roTeGpzNJf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQIBCDEBFS
{ 
  void GmtBKeMJkD()
  { 
      bool DelpqWNkkT = false;
      bool LxEjxCinTC = false;
      bool DQyJNeSLhd = false;
      bool QoAKqXcPMP = false;
      bool QAHCQAOlpO = false;
      bool ioJkHlgbbM = false;
      bool DBDHDWwsrZ = false;
      bool YSbElDJusM = false;
      bool PgVTtbePCF = false;
      bool pAmALOwAyt = false;
      bool EVsQoQMFyE = false;
      bool ckiPwWfiNb = false;
      bool qgpmiXebrX = false;
      bool GJwzItmEdc = false;
      bool OZQybERXDn = false;
      bool hMlWCWeFgQ = false;
      bool lkMaxTnjGB = false;
      bool jbEjMQQqKe = false;
      bool GGXDosWZwk = false;
      bool PgXNqcMoBI = false;
      string gDrKHTFgdZ;
      string iuLBukMjme;
      string VfIUYehcDF;
      string OMyIOqcEaQ;
      string deqxCgympL;
      string OHGGPAuWlb;
      string kcdYLWwCmD;
      string IHIWAqoLRr;
      string ftmqpHFrsN;
      string wFSzeBASkf;
      string juAlDHziGX;
      string LiFtwqpmhE;
      string QEJYHCnJqy;
      string qVZkHjtAni;
      string HVkUBMzYCn;
      string LMjgOelaeA;
      string SorHgpJTlL;
      string xozywuSoWt;
      string DPGDmdlrVb;
      string ySVmQSddnL;
      if(gDrKHTFgdZ == juAlDHziGX){DelpqWNkkT = true;}
      else if(juAlDHziGX == gDrKHTFgdZ){EVsQoQMFyE = true;}
      if(iuLBukMjme == LiFtwqpmhE){LxEjxCinTC = true;}
      else if(LiFtwqpmhE == iuLBukMjme){ckiPwWfiNb = true;}
      if(VfIUYehcDF == QEJYHCnJqy){DQyJNeSLhd = true;}
      else if(QEJYHCnJqy == VfIUYehcDF){qgpmiXebrX = true;}
      if(OMyIOqcEaQ == qVZkHjtAni){QoAKqXcPMP = true;}
      else if(qVZkHjtAni == OMyIOqcEaQ){GJwzItmEdc = true;}
      if(deqxCgympL == HVkUBMzYCn){QAHCQAOlpO = true;}
      else if(HVkUBMzYCn == deqxCgympL){OZQybERXDn = true;}
      if(OHGGPAuWlb == LMjgOelaeA){ioJkHlgbbM = true;}
      else if(LMjgOelaeA == OHGGPAuWlb){hMlWCWeFgQ = true;}
      if(kcdYLWwCmD == SorHgpJTlL){DBDHDWwsrZ = true;}
      else if(SorHgpJTlL == kcdYLWwCmD){lkMaxTnjGB = true;}
      if(IHIWAqoLRr == xozywuSoWt){YSbElDJusM = true;}
      if(ftmqpHFrsN == DPGDmdlrVb){PgVTtbePCF = true;}
      if(wFSzeBASkf == ySVmQSddnL){pAmALOwAyt = true;}
      while(xozywuSoWt == IHIWAqoLRr){jbEjMQQqKe = true;}
      while(DPGDmdlrVb == DPGDmdlrVb){GGXDosWZwk = true;}
      while(ySVmQSddnL == ySVmQSddnL){PgXNqcMoBI = true;}
      if(DelpqWNkkT == true){DelpqWNkkT = false;}
      if(LxEjxCinTC == true){LxEjxCinTC = false;}
      if(DQyJNeSLhd == true){DQyJNeSLhd = false;}
      if(QoAKqXcPMP == true){QoAKqXcPMP = false;}
      if(QAHCQAOlpO == true){QAHCQAOlpO = false;}
      if(ioJkHlgbbM == true){ioJkHlgbbM = false;}
      if(DBDHDWwsrZ == true){DBDHDWwsrZ = false;}
      if(YSbElDJusM == true){YSbElDJusM = false;}
      if(PgVTtbePCF == true){PgVTtbePCF = false;}
      if(pAmALOwAyt == true){pAmALOwAyt = false;}
      if(EVsQoQMFyE == true){EVsQoQMFyE = false;}
      if(ckiPwWfiNb == true){ckiPwWfiNb = false;}
      if(qgpmiXebrX == true){qgpmiXebrX = false;}
      if(GJwzItmEdc == true){GJwzItmEdc = false;}
      if(OZQybERXDn == true){OZQybERXDn = false;}
      if(hMlWCWeFgQ == true){hMlWCWeFgQ = false;}
      if(lkMaxTnjGB == true){lkMaxTnjGB = false;}
      if(jbEjMQQqKe == true){jbEjMQQqKe = false;}
      if(GGXDosWZwk == true){GGXDosWZwk = false;}
      if(PgXNqcMoBI == true){PgXNqcMoBI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SZNCAZUBUF
{ 
  void OgGPfoyXQW()
  { 
      bool BjATICFENn = false;
      bool eQjJKUejOr = false;
      bool FQUiZEVHkt = false;
      bool mWNEMdbDoQ = false;
      bool DlKDjrRwPx = false;
      bool DqQZGkOQtD = false;
      bool fyTSAHCexg = false;
      bool satyoTGRzg = false;
      bool mZqmquFnxb = false;
      bool OKJkkFSqCb = false;
      bool olziEbxSkm = false;
      bool exRMQFGfbF = false;
      bool BOhUShRJMi = false;
      bool BOPWrBaIiO = false;
      bool ymCKxRswUe = false;
      bool ylOwZaEdQV = false;
      bool JmFBlPgtUO = false;
      bool dywMHOLWXA = false;
      bool oUnhkOzSxR = false;
      bool xwqNEKgBYg = false;
      string hYxocfzLry;
      string KMWDJwENFn;
      string UMDUzenhni;
      string SjFxYNfjqS;
      string DwlkAEYGZB;
      string sBgOaVUbpx;
      string rQWJfZGYdw;
      string PUVmjYaSUu;
      string GgIloQCqWD;
      string rEstZmZbEZ;
      string xzcckYetdB;
      string tCGupKHjTO;
      string XPBaELabMx;
      string zyNtxHEeBQ;
      string lIMUIpxyDP;
      string eoHpChxCYZ;
      string xDggCwnMyi;
      string GciDcOCgRO;
      string ObXxSJpXqO;
      string JBGaShafSM;
      if(hYxocfzLry == xzcckYetdB){BjATICFENn = true;}
      else if(xzcckYetdB == hYxocfzLry){olziEbxSkm = true;}
      if(KMWDJwENFn == tCGupKHjTO){eQjJKUejOr = true;}
      else if(tCGupKHjTO == KMWDJwENFn){exRMQFGfbF = true;}
      if(UMDUzenhni == XPBaELabMx){FQUiZEVHkt = true;}
      else if(XPBaELabMx == UMDUzenhni){BOhUShRJMi = true;}
      if(SjFxYNfjqS == zyNtxHEeBQ){mWNEMdbDoQ = true;}
      else if(zyNtxHEeBQ == SjFxYNfjqS){BOPWrBaIiO = true;}
      if(DwlkAEYGZB == lIMUIpxyDP){DlKDjrRwPx = true;}
      else if(lIMUIpxyDP == DwlkAEYGZB){ymCKxRswUe = true;}
      if(sBgOaVUbpx == eoHpChxCYZ){DqQZGkOQtD = true;}
      else if(eoHpChxCYZ == sBgOaVUbpx){ylOwZaEdQV = true;}
      if(rQWJfZGYdw == xDggCwnMyi){fyTSAHCexg = true;}
      else if(xDggCwnMyi == rQWJfZGYdw){JmFBlPgtUO = true;}
      if(PUVmjYaSUu == GciDcOCgRO){satyoTGRzg = true;}
      if(GgIloQCqWD == ObXxSJpXqO){mZqmquFnxb = true;}
      if(rEstZmZbEZ == JBGaShafSM){OKJkkFSqCb = true;}
      while(GciDcOCgRO == PUVmjYaSUu){dywMHOLWXA = true;}
      while(ObXxSJpXqO == ObXxSJpXqO){oUnhkOzSxR = true;}
      while(JBGaShafSM == JBGaShafSM){xwqNEKgBYg = true;}
      if(BjATICFENn == true){BjATICFENn = false;}
      if(eQjJKUejOr == true){eQjJKUejOr = false;}
      if(FQUiZEVHkt == true){FQUiZEVHkt = false;}
      if(mWNEMdbDoQ == true){mWNEMdbDoQ = false;}
      if(DlKDjrRwPx == true){DlKDjrRwPx = false;}
      if(DqQZGkOQtD == true){DqQZGkOQtD = false;}
      if(fyTSAHCexg == true){fyTSAHCexg = false;}
      if(satyoTGRzg == true){satyoTGRzg = false;}
      if(mZqmquFnxb == true){mZqmquFnxb = false;}
      if(OKJkkFSqCb == true){OKJkkFSqCb = false;}
      if(olziEbxSkm == true){olziEbxSkm = false;}
      if(exRMQFGfbF == true){exRMQFGfbF = false;}
      if(BOhUShRJMi == true){BOhUShRJMi = false;}
      if(BOPWrBaIiO == true){BOPWrBaIiO = false;}
      if(ymCKxRswUe == true){ymCKxRswUe = false;}
      if(ylOwZaEdQV == true){ylOwZaEdQV = false;}
      if(JmFBlPgtUO == true){JmFBlPgtUO = false;}
      if(dywMHOLWXA == true){dywMHOLWXA = false;}
      if(oUnhkOzSxR == true){oUnhkOzSxR = false;}
      if(xwqNEKgBYg == true){xwqNEKgBYg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NNAWBVQNZC
{ 
  void fwZrrBSJDB()
  { 
      bool jdXTdnYtnW = false;
      bool hnpopZcHyY = false;
      bool jFXoZMYxpE = false;
      bool TumoaPRkFm = false;
      bool inwyzTAsVG = false;
      bool rLHxDdFhtQ = false;
      bool PaDjDlABNZ = false;
      bool IrCKouIYpG = false;
      bool MebiLHmokx = false;
      bool JiqnXIjMuM = false;
      bool TyeuyAJxIH = false;
      bool UgrnEjzTXw = false;
      bool zKPQPYANmg = false;
      bool LudclNAfkK = false;
      bool xpgdbcqDjm = false;
      bool IPoyNIhNeZ = false;
      bool zwKawYCOBp = false;
      bool jSiNzJclnm = false;
      bool hxdAXuGePd = false;
      bool elAKKAfFgC = false;
      string szWnaiYKdL;
      string yxThFWbuZG;
      string SnOJPUNMJN;
      string kikdcBJIwP;
      string xnBUWeCEqN;
      string SoRGBFjMYG;
      string VLBPaOMpFD;
      string NSyKIdlsmj;
      string SIVwuuRdbX;
      string RwiptkmltH;
      string SMzmAzpHxX;
      string SpZnnMpETe;
      string xhNglQjHQX;
      string pAzfRFIiuw;
      string EKfDFaWtCg;
      string uhROKjySAj;
      string PipZgRqsWh;
      string DGJXZmBKbL;
      string soFibIhkVh;
      string HphLgVTGWm;
      if(szWnaiYKdL == SMzmAzpHxX){jdXTdnYtnW = true;}
      else if(SMzmAzpHxX == szWnaiYKdL){TyeuyAJxIH = true;}
      if(yxThFWbuZG == SpZnnMpETe){hnpopZcHyY = true;}
      else if(SpZnnMpETe == yxThFWbuZG){UgrnEjzTXw = true;}
      if(SnOJPUNMJN == xhNglQjHQX){jFXoZMYxpE = true;}
      else if(xhNglQjHQX == SnOJPUNMJN){zKPQPYANmg = true;}
      if(kikdcBJIwP == pAzfRFIiuw){TumoaPRkFm = true;}
      else if(pAzfRFIiuw == kikdcBJIwP){LudclNAfkK = true;}
      if(xnBUWeCEqN == EKfDFaWtCg){inwyzTAsVG = true;}
      else if(EKfDFaWtCg == xnBUWeCEqN){xpgdbcqDjm = true;}
      if(SoRGBFjMYG == uhROKjySAj){rLHxDdFhtQ = true;}
      else if(uhROKjySAj == SoRGBFjMYG){IPoyNIhNeZ = true;}
      if(VLBPaOMpFD == PipZgRqsWh){PaDjDlABNZ = true;}
      else if(PipZgRqsWh == VLBPaOMpFD){zwKawYCOBp = true;}
      if(NSyKIdlsmj == DGJXZmBKbL){IrCKouIYpG = true;}
      if(SIVwuuRdbX == soFibIhkVh){MebiLHmokx = true;}
      if(RwiptkmltH == HphLgVTGWm){JiqnXIjMuM = true;}
      while(DGJXZmBKbL == NSyKIdlsmj){jSiNzJclnm = true;}
      while(soFibIhkVh == soFibIhkVh){hxdAXuGePd = true;}
      while(HphLgVTGWm == HphLgVTGWm){elAKKAfFgC = true;}
      if(jdXTdnYtnW == true){jdXTdnYtnW = false;}
      if(hnpopZcHyY == true){hnpopZcHyY = false;}
      if(jFXoZMYxpE == true){jFXoZMYxpE = false;}
      if(TumoaPRkFm == true){TumoaPRkFm = false;}
      if(inwyzTAsVG == true){inwyzTAsVG = false;}
      if(rLHxDdFhtQ == true){rLHxDdFhtQ = false;}
      if(PaDjDlABNZ == true){PaDjDlABNZ = false;}
      if(IrCKouIYpG == true){IrCKouIYpG = false;}
      if(MebiLHmokx == true){MebiLHmokx = false;}
      if(JiqnXIjMuM == true){JiqnXIjMuM = false;}
      if(TyeuyAJxIH == true){TyeuyAJxIH = false;}
      if(UgrnEjzTXw == true){UgrnEjzTXw = false;}
      if(zKPQPYANmg == true){zKPQPYANmg = false;}
      if(LudclNAfkK == true){LudclNAfkK = false;}
      if(xpgdbcqDjm == true){xpgdbcqDjm = false;}
      if(IPoyNIhNeZ == true){IPoyNIhNeZ = false;}
      if(zwKawYCOBp == true){zwKawYCOBp = false;}
      if(jSiNzJclnm == true){jSiNzJclnm = false;}
      if(hxdAXuGePd == true){hxdAXuGePd = false;}
      if(elAKKAfFgC == true){elAKKAfFgC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZLKVDCEWWR
{ 
  void DDeQjJuzmq()
  { 
      bool MUNEPUDFWz = false;
      bool tQMXykhNZS = false;
      bool xaNpFXiMUO = false;
      bool IOoJgQXnXH = false;
      bool slVtWQTwUX = false;
      bool kLoGLkGWzr = false;
      bool kqkHpebCpg = false;
      bool MtoSZLETTo = false;
      bool DmqwdxZixu = false;
      bool KAnfVBANDq = false;
      bool nQFnKqVVgA = false;
      bool gmDKnyznds = false;
      bool FsFtWLFJxX = false;
      bool KpPbAmgDlm = false;
      bool aDCwOWxdrW = false;
      bool BMjKltLKQy = false;
      bool kMYIopXaJA = false;
      bool QwCqRCqIfz = false;
      bool OaQZVyGFpF = false;
      bool aVlmBOdsHX = false;
      string PLBrCWMAgn;
      string iwIjdbsPGo;
      string xfICoItuRN;
      string AnhYACHUkN;
      string cALYkgPiSR;
      string DqDNqjCyDs;
      string bQiTntOiia;
      string UYdsLxTjRH;
      string sLczKJkThP;
      string AIRrkLRrjq;
      string SfzrwdNJCt;
      string QSgwAQniJe;
      string JuBSaMHkIz;
      string eazanMMkDf;
      string uaRmzgaVrT;
      string XiiFgXefRj;
      string WbBCOoTGHm;
      string ECecihdNTs;
      string klsnbwqssQ;
      string hfTSITYOYJ;
      if(PLBrCWMAgn == SfzrwdNJCt){MUNEPUDFWz = true;}
      else if(SfzrwdNJCt == PLBrCWMAgn){nQFnKqVVgA = true;}
      if(iwIjdbsPGo == QSgwAQniJe){tQMXykhNZS = true;}
      else if(QSgwAQniJe == iwIjdbsPGo){gmDKnyznds = true;}
      if(xfICoItuRN == JuBSaMHkIz){xaNpFXiMUO = true;}
      else if(JuBSaMHkIz == xfICoItuRN){FsFtWLFJxX = true;}
      if(AnhYACHUkN == eazanMMkDf){IOoJgQXnXH = true;}
      else if(eazanMMkDf == AnhYACHUkN){KpPbAmgDlm = true;}
      if(cALYkgPiSR == uaRmzgaVrT){slVtWQTwUX = true;}
      else if(uaRmzgaVrT == cALYkgPiSR){aDCwOWxdrW = true;}
      if(DqDNqjCyDs == XiiFgXefRj){kLoGLkGWzr = true;}
      else if(XiiFgXefRj == DqDNqjCyDs){BMjKltLKQy = true;}
      if(bQiTntOiia == WbBCOoTGHm){kqkHpebCpg = true;}
      else if(WbBCOoTGHm == bQiTntOiia){kMYIopXaJA = true;}
      if(UYdsLxTjRH == ECecihdNTs){MtoSZLETTo = true;}
      if(sLczKJkThP == klsnbwqssQ){DmqwdxZixu = true;}
      if(AIRrkLRrjq == hfTSITYOYJ){KAnfVBANDq = true;}
      while(ECecihdNTs == UYdsLxTjRH){QwCqRCqIfz = true;}
      while(klsnbwqssQ == klsnbwqssQ){OaQZVyGFpF = true;}
      while(hfTSITYOYJ == hfTSITYOYJ){aVlmBOdsHX = true;}
      if(MUNEPUDFWz == true){MUNEPUDFWz = false;}
      if(tQMXykhNZS == true){tQMXykhNZS = false;}
      if(xaNpFXiMUO == true){xaNpFXiMUO = false;}
      if(IOoJgQXnXH == true){IOoJgQXnXH = false;}
      if(slVtWQTwUX == true){slVtWQTwUX = false;}
      if(kLoGLkGWzr == true){kLoGLkGWzr = false;}
      if(kqkHpebCpg == true){kqkHpebCpg = false;}
      if(MtoSZLETTo == true){MtoSZLETTo = false;}
      if(DmqwdxZixu == true){DmqwdxZixu = false;}
      if(KAnfVBANDq == true){KAnfVBANDq = false;}
      if(nQFnKqVVgA == true){nQFnKqVVgA = false;}
      if(gmDKnyznds == true){gmDKnyznds = false;}
      if(FsFtWLFJxX == true){FsFtWLFJxX = false;}
      if(KpPbAmgDlm == true){KpPbAmgDlm = false;}
      if(aDCwOWxdrW == true){aDCwOWxdrW = false;}
      if(BMjKltLKQy == true){BMjKltLKQy = false;}
      if(kMYIopXaJA == true){kMYIopXaJA = false;}
      if(QwCqRCqIfz == true){QwCqRCqIfz = false;}
      if(OaQZVyGFpF == true){OaQZVyGFpF = false;}
      if(aVlmBOdsHX == true){aVlmBOdsHX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ITCTLVMGMR
{ 
  void etpYJYUVYk()
  { 
      bool FmnHzNsRVT = false;
      bool NtNlOPzeIE = false;
      bool YXMgGsKxku = false;
      bool hXgoYNplzT = false;
      bool YYBLRoAUjW = false;
      bool pnFMahZHBF = false;
      bool DufZlpMYNA = false;
      bool YMeoeAVBPQ = false;
      bool soMOEsSUNp = false;
      bool niktQdrbZb = false;
      bool cbHixdIQga = false;
      bool MYrjMNhRUr = false;
      bool XrKXMobkXB = false;
      bool HsbmnQgdQa = false;
      bool kBmmcOqAhC = false;
      bool uZGgEjRjWH = false;
      bool BXrfSSxEwu = false;
      bool fEBtHVFWty = false;
      bool ybCVGgmtiD = false;
      bool zxGIZMJHUK = false;
      string MFyanwqmkG;
      string nqPBPBrMOX;
      string coXeJFybQT;
      string QEtFiItNBc;
      string mWNQFmrZFE;
      string HwVnlXgTQh;
      string xOWRoiwJRH;
      string HdLkkGbGYW;
      string NYWLLTiGTL;
      string aZwSeXzubW;
      string piHxxckjCe;
      string uZttUYrKGU;
      string ApoFfghrFM;
      string HfeCfdQZOh;
      string iyDoPBfCyG;
      string fooHVAtCRP;
      string usdoWPurNp;
      string HSwXkClzoe;
      string BeszgSpXff;
      string jNHympTNRA;
      if(MFyanwqmkG == piHxxckjCe){FmnHzNsRVT = true;}
      else if(piHxxckjCe == MFyanwqmkG){cbHixdIQga = true;}
      if(nqPBPBrMOX == uZttUYrKGU){NtNlOPzeIE = true;}
      else if(uZttUYrKGU == nqPBPBrMOX){MYrjMNhRUr = true;}
      if(coXeJFybQT == ApoFfghrFM){YXMgGsKxku = true;}
      else if(ApoFfghrFM == coXeJFybQT){XrKXMobkXB = true;}
      if(QEtFiItNBc == HfeCfdQZOh){hXgoYNplzT = true;}
      else if(HfeCfdQZOh == QEtFiItNBc){HsbmnQgdQa = true;}
      if(mWNQFmrZFE == iyDoPBfCyG){YYBLRoAUjW = true;}
      else if(iyDoPBfCyG == mWNQFmrZFE){kBmmcOqAhC = true;}
      if(HwVnlXgTQh == fooHVAtCRP){pnFMahZHBF = true;}
      else if(fooHVAtCRP == HwVnlXgTQh){uZGgEjRjWH = true;}
      if(xOWRoiwJRH == usdoWPurNp){DufZlpMYNA = true;}
      else if(usdoWPurNp == xOWRoiwJRH){BXrfSSxEwu = true;}
      if(HdLkkGbGYW == HSwXkClzoe){YMeoeAVBPQ = true;}
      if(NYWLLTiGTL == BeszgSpXff){soMOEsSUNp = true;}
      if(aZwSeXzubW == jNHympTNRA){niktQdrbZb = true;}
      while(HSwXkClzoe == HdLkkGbGYW){fEBtHVFWty = true;}
      while(BeszgSpXff == BeszgSpXff){ybCVGgmtiD = true;}
      while(jNHympTNRA == jNHympTNRA){zxGIZMJHUK = true;}
      if(FmnHzNsRVT == true){FmnHzNsRVT = false;}
      if(NtNlOPzeIE == true){NtNlOPzeIE = false;}
      if(YXMgGsKxku == true){YXMgGsKxku = false;}
      if(hXgoYNplzT == true){hXgoYNplzT = false;}
      if(YYBLRoAUjW == true){YYBLRoAUjW = false;}
      if(pnFMahZHBF == true){pnFMahZHBF = false;}
      if(DufZlpMYNA == true){DufZlpMYNA = false;}
      if(YMeoeAVBPQ == true){YMeoeAVBPQ = false;}
      if(soMOEsSUNp == true){soMOEsSUNp = false;}
      if(niktQdrbZb == true){niktQdrbZb = false;}
      if(cbHixdIQga == true){cbHixdIQga = false;}
      if(MYrjMNhRUr == true){MYrjMNhRUr = false;}
      if(XrKXMobkXB == true){XrKXMobkXB = false;}
      if(HsbmnQgdQa == true){HsbmnQgdQa = false;}
      if(kBmmcOqAhC == true){kBmmcOqAhC = false;}
      if(uZGgEjRjWH == true){uZGgEjRjWH = false;}
      if(BXrfSSxEwu == true){BXrfSSxEwu = false;}
      if(fEBtHVFWty == true){fEBtHVFWty = false;}
      if(ybCVGgmtiD == true){ybCVGgmtiD = false;}
      if(zxGIZMJHUK == true){zxGIZMJHUK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCSDPTJGEO
{ 
  void zfjAsHjwJw()
  { 
      bool fJwoFoDAxO = false;
      bool SGodudKCcm = false;
      bool FokZIkEzXx = false;
      bool wtdqsmPjGd = false;
      bool TzyOlBlkgh = false;
      bool BjeFkqXVfU = false;
      bool jEczRYcxkH = false;
      bool NawzSGqWmG = false;
      bool zTSpwMOXFB = false;
      bool OtDksPWywN = false;
      bool YnAYTanele = false;
      bool ABhZUQklDF = false;
      bool JFqirTXKFD = false;
      bool irZZhKStVV = false;
      bool XikaBNLcQc = false;
      bool djtpDTwQfA = false;
      bool CdYiuHaHrJ = false;
      bool xqQhgZTQge = false;
      bool HtscYzyiWO = false;
      bool OCOVStJCet = false;
      string wLdUsoByxh;
      string dGJGNBIwCP;
      string bxBbNwaDZe;
      string PxWMlPRnGs;
      string syohPLDXqu;
      string yECtryJCHw;
      string OyYSSfixTx;
      string iUoJWcHTLB;
      string sCMefLucUn;
      string GOgJduZWPj;
      string bGDsLdOsXP;
      string poqFDLltlG;
      string kGbfpTmeeb;
      string DkEbZlzSSC;
      string wBEFxQXaGS;
      string IejIyUdXDq;
      string pjOwLFkOeQ;
      string MTajKiCWiY;
      string wMYLSXAwcF;
      string IaObLMmIsq;
      if(wLdUsoByxh == bGDsLdOsXP){fJwoFoDAxO = true;}
      else if(bGDsLdOsXP == wLdUsoByxh){YnAYTanele = true;}
      if(dGJGNBIwCP == poqFDLltlG){SGodudKCcm = true;}
      else if(poqFDLltlG == dGJGNBIwCP){ABhZUQklDF = true;}
      if(bxBbNwaDZe == kGbfpTmeeb){FokZIkEzXx = true;}
      else if(kGbfpTmeeb == bxBbNwaDZe){JFqirTXKFD = true;}
      if(PxWMlPRnGs == DkEbZlzSSC){wtdqsmPjGd = true;}
      else if(DkEbZlzSSC == PxWMlPRnGs){irZZhKStVV = true;}
      if(syohPLDXqu == wBEFxQXaGS){TzyOlBlkgh = true;}
      else if(wBEFxQXaGS == syohPLDXqu){XikaBNLcQc = true;}
      if(yECtryJCHw == IejIyUdXDq){BjeFkqXVfU = true;}
      else if(IejIyUdXDq == yECtryJCHw){djtpDTwQfA = true;}
      if(OyYSSfixTx == pjOwLFkOeQ){jEczRYcxkH = true;}
      else if(pjOwLFkOeQ == OyYSSfixTx){CdYiuHaHrJ = true;}
      if(iUoJWcHTLB == MTajKiCWiY){NawzSGqWmG = true;}
      if(sCMefLucUn == wMYLSXAwcF){zTSpwMOXFB = true;}
      if(GOgJduZWPj == IaObLMmIsq){OtDksPWywN = true;}
      while(MTajKiCWiY == iUoJWcHTLB){xqQhgZTQge = true;}
      while(wMYLSXAwcF == wMYLSXAwcF){HtscYzyiWO = true;}
      while(IaObLMmIsq == IaObLMmIsq){OCOVStJCet = true;}
      if(fJwoFoDAxO == true){fJwoFoDAxO = false;}
      if(SGodudKCcm == true){SGodudKCcm = false;}
      if(FokZIkEzXx == true){FokZIkEzXx = false;}
      if(wtdqsmPjGd == true){wtdqsmPjGd = false;}
      if(TzyOlBlkgh == true){TzyOlBlkgh = false;}
      if(BjeFkqXVfU == true){BjeFkqXVfU = false;}
      if(jEczRYcxkH == true){jEczRYcxkH = false;}
      if(NawzSGqWmG == true){NawzSGqWmG = false;}
      if(zTSpwMOXFB == true){zTSpwMOXFB = false;}
      if(OtDksPWywN == true){OtDksPWywN = false;}
      if(YnAYTanele == true){YnAYTanele = false;}
      if(ABhZUQklDF == true){ABhZUQklDF = false;}
      if(JFqirTXKFD == true){JFqirTXKFD = false;}
      if(irZZhKStVV == true){irZZhKStVV = false;}
      if(XikaBNLcQc == true){XikaBNLcQc = false;}
      if(djtpDTwQfA == true){djtpDTwQfA = false;}
      if(CdYiuHaHrJ == true){CdYiuHaHrJ = false;}
      if(xqQhgZTQge == true){xqQhgZTQge = false;}
      if(HtscYzyiWO == true){HtscYzyiWO = false;}
      if(OCOVStJCet == true){OCOVStJCet = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PMULGKAVGB
{ 
  void ruwuRhUYrX()
  { 
      bool ONsuGAtRMX = false;
      bool qKAekksssG = false;
      bool SmnCKZfKsg = false;
      bool YEaTEbEqMW = false;
      bool SNnXZoZSVm = false;
      bool nEkCmaYqkg = false;
      bool TjYezmjfZJ = false;
      bool gCfWnEyQbU = false;
      bool zNoFsUSXgc = false;
      bool DMFfCioIYm = false;
      bool FsrLGlXOOh = false;
      bool cIOPgFuSle = false;
      bool TLyxFTwATE = false;
      bool PoqoPFVcyH = false;
      bool wDJzAuypyx = false;
      bool nVWtTsttFm = false;
      bool oWuJRmQZAa = false;
      bool jSUehPBzxK = false;
      bool UGCWQtSwVV = false;
      bool KaWLRYIAhN = false;
      string eAYCDKKZzX;
      string DWkpMpUSFr;
      string qyzarwCYcc;
      string KYgAxVZjQS;
      string oHcRGuswKf;
      string dZZUcgAxKG;
      string IlwWNepksq;
      string QkBlDiUhTx;
      string CFNxzkyLWP;
      string UbZJKCKGEb;
      string EIDSOsXnQs;
      string MRcMECXzXb;
      string gdNcVnKraB;
      string YOcrrtBthG;
      string NJtdDDyNFH;
      string dLibuataxa;
      string hfMPUynkTJ;
      string BdQQOWijZS;
      string oxlTWNeBwR;
      string zaxGXhxeJF;
      if(eAYCDKKZzX == EIDSOsXnQs){ONsuGAtRMX = true;}
      else if(EIDSOsXnQs == eAYCDKKZzX){FsrLGlXOOh = true;}
      if(DWkpMpUSFr == MRcMECXzXb){qKAekksssG = true;}
      else if(MRcMECXzXb == DWkpMpUSFr){cIOPgFuSle = true;}
      if(qyzarwCYcc == gdNcVnKraB){SmnCKZfKsg = true;}
      else if(gdNcVnKraB == qyzarwCYcc){TLyxFTwATE = true;}
      if(KYgAxVZjQS == YOcrrtBthG){YEaTEbEqMW = true;}
      else if(YOcrrtBthG == KYgAxVZjQS){PoqoPFVcyH = true;}
      if(oHcRGuswKf == NJtdDDyNFH){SNnXZoZSVm = true;}
      else if(NJtdDDyNFH == oHcRGuswKf){wDJzAuypyx = true;}
      if(dZZUcgAxKG == dLibuataxa){nEkCmaYqkg = true;}
      else if(dLibuataxa == dZZUcgAxKG){nVWtTsttFm = true;}
      if(IlwWNepksq == hfMPUynkTJ){TjYezmjfZJ = true;}
      else if(hfMPUynkTJ == IlwWNepksq){oWuJRmQZAa = true;}
      if(QkBlDiUhTx == BdQQOWijZS){gCfWnEyQbU = true;}
      if(CFNxzkyLWP == oxlTWNeBwR){zNoFsUSXgc = true;}
      if(UbZJKCKGEb == zaxGXhxeJF){DMFfCioIYm = true;}
      while(BdQQOWijZS == QkBlDiUhTx){jSUehPBzxK = true;}
      while(oxlTWNeBwR == oxlTWNeBwR){UGCWQtSwVV = true;}
      while(zaxGXhxeJF == zaxGXhxeJF){KaWLRYIAhN = true;}
      if(ONsuGAtRMX == true){ONsuGAtRMX = false;}
      if(qKAekksssG == true){qKAekksssG = false;}
      if(SmnCKZfKsg == true){SmnCKZfKsg = false;}
      if(YEaTEbEqMW == true){YEaTEbEqMW = false;}
      if(SNnXZoZSVm == true){SNnXZoZSVm = false;}
      if(nEkCmaYqkg == true){nEkCmaYqkg = false;}
      if(TjYezmjfZJ == true){TjYezmjfZJ = false;}
      if(gCfWnEyQbU == true){gCfWnEyQbU = false;}
      if(zNoFsUSXgc == true){zNoFsUSXgc = false;}
      if(DMFfCioIYm == true){DMFfCioIYm = false;}
      if(FsrLGlXOOh == true){FsrLGlXOOh = false;}
      if(cIOPgFuSle == true){cIOPgFuSle = false;}
      if(TLyxFTwATE == true){TLyxFTwATE = false;}
      if(PoqoPFVcyH == true){PoqoPFVcyH = false;}
      if(wDJzAuypyx == true){wDJzAuypyx = false;}
      if(nVWtTsttFm == true){nVWtTsttFm = false;}
      if(oWuJRmQZAa == true){oWuJRmQZAa = false;}
      if(jSUehPBzxK == true){jSUehPBzxK = false;}
      if(UGCWQtSwVV == true){UGCWQtSwVV = false;}
      if(KaWLRYIAhN == true){KaWLRYIAhN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PPMSAAKDMH
{ 
  void UmGfGSuMsr()
  { 
      bool oIReZkHKxo = false;
      bool CwVydgTfye = false;
      bool mzklbZGtlH = false;
      bool pyLDHiYWMr = false;
      bool iOxLRNFPeK = false;
      bool wsjQmpWfDz = false;
      bool eNXpzEkRpu = false;
      bool HxSGuXCZTN = false;
      bool UpObKwNtQR = false;
      bool LsSMMVpGLM = false;
      bool cmYjCzacVO = false;
      bool mxLoenzweD = false;
      bool qpBXiOdGtZ = false;
      bool huOHkhRdYL = false;
      bool VkYCeOgchX = false;
      bool WsbHVlkAAn = false;
      bool UTiwfqiDEx = false;
      bool WUXThFRysU = false;
      bool gBYWDnTGlz = false;
      bool wQckpBCcVm = false;
      string yWNHQCSsei;
      string tPcOkUThnX;
      string OaNESeizVj;
      string xRCNkFuWAW;
      string DQcQnnqrJh;
      string iWufWXIIol;
      string TTWtkbNPce;
      string ZwhQTxxwQd;
      string nponBaVWqM;
      string wmhODjthfL;
      string aaPeIloeLY;
      string aLqKxcdisK;
      string GqYPhmOSMi;
      string DOQFDMaKeO;
      string lqKRlkuXQa;
      string FLoVEiCzwV;
      string WVRbVMulGk;
      string BTDdXPfGcx;
      string rpCldqZuAU;
      string JaNJqQZhuZ;
      if(yWNHQCSsei == aaPeIloeLY){oIReZkHKxo = true;}
      else if(aaPeIloeLY == yWNHQCSsei){cmYjCzacVO = true;}
      if(tPcOkUThnX == aLqKxcdisK){CwVydgTfye = true;}
      else if(aLqKxcdisK == tPcOkUThnX){mxLoenzweD = true;}
      if(OaNESeizVj == GqYPhmOSMi){mzklbZGtlH = true;}
      else if(GqYPhmOSMi == OaNESeizVj){qpBXiOdGtZ = true;}
      if(xRCNkFuWAW == DOQFDMaKeO){pyLDHiYWMr = true;}
      else if(DOQFDMaKeO == xRCNkFuWAW){huOHkhRdYL = true;}
      if(DQcQnnqrJh == lqKRlkuXQa){iOxLRNFPeK = true;}
      else if(lqKRlkuXQa == DQcQnnqrJh){VkYCeOgchX = true;}
      if(iWufWXIIol == FLoVEiCzwV){wsjQmpWfDz = true;}
      else if(FLoVEiCzwV == iWufWXIIol){WsbHVlkAAn = true;}
      if(TTWtkbNPce == WVRbVMulGk){eNXpzEkRpu = true;}
      else if(WVRbVMulGk == TTWtkbNPce){UTiwfqiDEx = true;}
      if(ZwhQTxxwQd == BTDdXPfGcx){HxSGuXCZTN = true;}
      if(nponBaVWqM == rpCldqZuAU){UpObKwNtQR = true;}
      if(wmhODjthfL == JaNJqQZhuZ){LsSMMVpGLM = true;}
      while(BTDdXPfGcx == ZwhQTxxwQd){WUXThFRysU = true;}
      while(rpCldqZuAU == rpCldqZuAU){gBYWDnTGlz = true;}
      while(JaNJqQZhuZ == JaNJqQZhuZ){wQckpBCcVm = true;}
      if(oIReZkHKxo == true){oIReZkHKxo = false;}
      if(CwVydgTfye == true){CwVydgTfye = false;}
      if(mzklbZGtlH == true){mzklbZGtlH = false;}
      if(pyLDHiYWMr == true){pyLDHiYWMr = false;}
      if(iOxLRNFPeK == true){iOxLRNFPeK = false;}
      if(wsjQmpWfDz == true){wsjQmpWfDz = false;}
      if(eNXpzEkRpu == true){eNXpzEkRpu = false;}
      if(HxSGuXCZTN == true){HxSGuXCZTN = false;}
      if(UpObKwNtQR == true){UpObKwNtQR = false;}
      if(LsSMMVpGLM == true){LsSMMVpGLM = false;}
      if(cmYjCzacVO == true){cmYjCzacVO = false;}
      if(mxLoenzweD == true){mxLoenzweD = false;}
      if(qpBXiOdGtZ == true){qpBXiOdGtZ = false;}
      if(huOHkhRdYL == true){huOHkhRdYL = false;}
      if(VkYCeOgchX == true){VkYCeOgchX = false;}
      if(WsbHVlkAAn == true){WsbHVlkAAn = false;}
      if(UTiwfqiDEx == true){UTiwfqiDEx = false;}
      if(WUXThFRysU == true){WUXThFRysU = false;}
      if(gBYWDnTGlz == true){gBYWDnTGlz = false;}
      if(wQckpBCcVm == true){wQckpBCcVm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HXAMAKNAVM
{ 
  void exefMWgpua()
  { 
      bool HDwisiJogM = false;
      bool bJoHCPKGxN = false;
      bool AkgVxHoioR = false;
      bool tbCfsHXyfP = false;
      bool pmAkpxspkr = false;
      bool EzVtHWVakl = false;
      bool tZAPSzHINu = false;
      bool qMZgXMjwfA = false;
      bool NyywMtGIYW = false;
      bool kxMsVPlkRq = false;
      bool pkbpArYnVt = false;
      bool lZukYubDCY = false;
      bool ryiqKtzfLH = false;
      bool azenJbVIwU = false;
      bool VSlekKBbUZ = false;
      bool nhisyqBkfF = false;
      bool srbOSmuGaw = false;
      bool ZTHhDZMEFz = false;
      bool rWLlTrPkpS = false;
      bool akbpacpWLx = false;
      string PlPJRkzSEf;
      string VoeLlthKBz;
      string RhRQGOSHll;
      string WKrmJNZQWF;
      string KisOIgpDLc;
      string GBkIagTzCD;
      string RqfSJKxqBX;
      string URnwnhoCIZ;
      string XOwIeUZjMc;
      string sZNSmSDZEx;
      string jyCnInNnTr;
      string rRpceDuWmo;
      string kMeYdtEUJV;
      string eOxKoZMIAq;
      string HkQUjbijnj;
      string WflPMXTcJN;
      string irexMcTfnE;
      string pmWwhzuJnB;
      string KTgYzzchyR;
      string GiymHPFTHH;
      if(PlPJRkzSEf == jyCnInNnTr){HDwisiJogM = true;}
      else if(jyCnInNnTr == PlPJRkzSEf){pkbpArYnVt = true;}
      if(VoeLlthKBz == rRpceDuWmo){bJoHCPKGxN = true;}
      else if(rRpceDuWmo == VoeLlthKBz){lZukYubDCY = true;}
      if(RhRQGOSHll == kMeYdtEUJV){AkgVxHoioR = true;}
      else if(kMeYdtEUJV == RhRQGOSHll){ryiqKtzfLH = true;}
      if(WKrmJNZQWF == eOxKoZMIAq){tbCfsHXyfP = true;}
      else if(eOxKoZMIAq == WKrmJNZQWF){azenJbVIwU = true;}
      if(KisOIgpDLc == HkQUjbijnj){pmAkpxspkr = true;}
      else if(HkQUjbijnj == KisOIgpDLc){VSlekKBbUZ = true;}
      if(GBkIagTzCD == WflPMXTcJN){EzVtHWVakl = true;}
      else if(WflPMXTcJN == GBkIagTzCD){nhisyqBkfF = true;}
      if(RqfSJKxqBX == irexMcTfnE){tZAPSzHINu = true;}
      else if(irexMcTfnE == RqfSJKxqBX){srbOSmuGaw = true;}
      if(URnwnhoCIZ == pmWwhzuJnB){qMZgXMjwfA = true;}
      if(XOwIeUZjMc == KTgYzzchyR){NyywMtGIYW = true;}
      if(sZNSmSDZEx == GiymHPFTHH){kxMsVPlkRq = true;}
      while(pmWwhzuJnB == URnwnhoCIZ){ZTHhDZMEFz = true;}
      while(KTgYzzchyR == KTgYzzchyR){rWLlTrPkpS = true;}
      while(GiymHPFTHH == GiymHPFTHH){akbpacpWLx = true;}
      if(HDwisiJogM == true){HDwisiJogM = false;}
      if(bJoHCPKGxN == true){bJoHCPKGxN = false;}
      if(AkgVxHoioR == true){AkgVxHoioR = false;}
      if(tbCfsHXyfP == true){tbCfsHXyfP = false;}
      if(pmAkpxspkr == true){pmAkpxspkr = false;}
      if(EzVtHWVakl == true){EzVtHWVakl = false;}
      if(tZAPSzHINu == true){tZAPSzHINu = false;}
      if(qMZgXMjwfA == true){qMZgXMjwfA = false;}
      if(NyywMtGIYW == true){NyywMtGIYW = false;}
      if(kxMsVPlkRq == true){kxMsVPlkRq = false;}
      if(pkbpArYnVt == true){pkbpArYnVt = false;}
      if(lZukYubDCY == true){lZukYubDCY = false;}
      if(ryiqKtzfLH == true){ryiqKtzfLH = false;}
      if(azenJbVIwU == true){azenJbVIwU = false;}
      if(VSlekKBbUZ == true){VSlekKBbUZ = false;}
      if(nhisyqBkfF == true){nhisyqBkfF = false;}
      if(srbOSmuGaw == true){srbOSmuGaw = false;}
      if(ZTHhDZMEFz == true){ZTHhDZMEFz = false;}
      if(rWLlTrPkpS == true){rWLlTrPkpS = false;}
      if(akbpacpWLx == true){akbpacpWLx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HOJRDFSIFL
{ 
  void wrpdlGmFiS()
  { 
      bool RtLmaPXxlp = false;
      bool qJFUpsbOhe = false;
      bool OtoeiOZXxH = false;
      bool ckFjAXzPkJ = false;
      bool TtCTSLHtLk = false;
      bool iIbufWEgDM = false;
      bool ozAdMGDVUS = false;
      bool sLdXKTrULX = false;
      bool GfLLYUIKDc = false;
      bool SSMXTTtXGM = false;
      bool HkZsqWeDjL = false;
      bool eiUeFJnnFr = false;
      bool xrRqzayFDp = false;
      bool ZTOzQVGSUC = false;
      bool pFaqyixhSK = false;
      bool fFSOOOSisP = false;
      bool XYzslKUVOj = false;
      bool DUTCCrRarP = false;
      bool dQlsKTBAkB = false;
      bool CXYEdQFgFn = false;
      string TbrwZWPSZM;
      string xdaGQkYCDT;
      string QtqGMgjPEQ;
      string pONoAQeXAO;
      string turjUPDVGZ;
      string RadKgZkljs;
      string mzOJWhPkGz;
      string FABoYVBHlw;
      string cNIezOkDIa;
      string fsnHbugiMl;
      string zSPGUQYnlL;
      string YdzmPYpjJH;
      string wMcfTLMtNd;
      string oRtzxKxBKh;
      string oxRwBBtBqC;
      string ExYEolojmI;
      string EeZHWGjzoE;
      string bnZaSztfdR;
      string RKCLZqroJK;
      string UNOBdKWJZt;
      if(TbrwZWPSZM == zSPGUQYnlL){RtLmaPXxlp = true;}
      else if(zSPGUQYnlL == TbrwZWPSZM){HkZsqWeDjL = true;}
      if(xdaGQkYCDT == YdzmPYpjJH){qJFUpsbOhe = true;}
      else if(YdzmPYpjJH == xdaGQkYCDT){eiUeFJnnFr = true;}
      if(QtqGMgjPEQ == wMcfTLMtNd){OtoeiOZXxH = true;}
      else if(wMcfTLMtNd == QtqGMgjPEQ){xrRqzayFDp = true;}
      if(pONoAQeXAO == oRtzxKxBKh){ckFjAXzPkJ = true;}
      else if(oRtzxKxBKh == pONoAQeXAO){ZTOzQVGSUC = true;}
      if(turjUPDVGZ == oxRwBBtBqC){TtCTSLHtLk = true;}
      else if(oxRwBBtBqC == turjUPDVGZ){pFaqyixhSK = true;}
      if(RadKgZkljs == ExYEolojmI){iIbufWEgDM = true;}
      else if(ExYEolojmI == RadKgZkljs){fFSOOOSisP = true;}
      if(mzOJWhPkGz == EeZHWGjzoE){ozAdMGDVUS = true;}
      else if(EeZHWGjzoE == mzOJWhPkGz){XYzslKUVOj = true;}
      if(FABoYVBHlw == bnZaSztfdR){sLdXKTrULX = true;}
      if(cNIezOkDIa == RKCLZqroJK){GfLLYUIKDc = true;}
      if(fsnHbugiMl == UNOBdKWJZt){SSMXTTtXGM = true;}
      while(bnZaSztfdR == FABoYVBHlw){DUTCCrRarP = true;}
      while(RKCLZqroJK == RKCLZqroJK){dQlsKTBAkB = true;}
      while(UNOBdKWJZt == UNOBdKWJZt){CXYEdQFgFn = true;}
      if(RtLmaPXxlp == true){RtLmaPXxlp = false;}
      if(qJFUpsbOhe == true){qJFUpsbOhe = false;}
      if(OtoeiOZXxH == true){OtoeiOZXxH = false;}
      if(ckFjAXzPkJ == true){ckFjAXzPkJ = false;}
      if(TtCTSLHtLk == true){TtCTSLHtLk = false;}
      if(iIbufWEgDM == true){iIbufWEgDM = false;}
      if(ozAdMGDVUS == true){ozAdMGDVUS = false;}
      if(sLdXKTrULX == true){sLdXKTrULX = false;}
      if(GfLLYUIKDc == true){GfLLYUIKDc = false;}
      if(SSMXTTtXGM == true){SSMXTTtXGM = false;}
      if(HkZsqWeDjL == true){HkZsqWeDjL = false;}
      if(eiUeFJnnFr == true){eiUeFJnnFr = false;}
      if(xrRqzayFDp == true){xrRqzayFDp = false;}
      if(ZTOzQVGSUC == true){ZTOzQVGSUC = false;}
      if(pFaqyixhSK == true){pFaqyixhSK = false;}
      if(fFSOOOSisP == true){fFSOOOSisP = false;}
      if(XYzslKUVOj == true){XYzslKUVOj = false;}
      if(DUTCCrRarP == true){DUTCCrRarP = false;}
      if(dQlsKTBAkB == true){dQlsKTBAkB = false;}
      if(CXYEdQFgFn == true){CXYEdQFgFn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAVPPDEMYP
{ 
  void QJbAXeEbRY()
  { 
      bool iCZXSlyPtG = false;
      bool xZxasbFxpU = false;
      bool ZKoyfVttyt = false;
      bool ramsPgSjUq = false;
      bool OeDlnletkt = false;
      bool IaRthXMarw = false;
      bool qDQANWmEKM = false;
      bool JUczFuHDJt = false;
      bool qzJElQIsKr = false;
      bool UqrXzLNCXR = false;
      bool zZjYjnxSom = false;
      bool PJQxFrtMNx = false;
      bool NstRrSbFzt = false;
      bool hEfrtQPjTy = false;
      bool SpEXbLZuRH = false;
      bool QAoaDFfRgR = false;
      bool LrTtFLdYDn = false;
      bool bJrPdXoWpg = false;
      bool sgmqcgPEoo = false;
      bool kxDClaWJRQ = false;
      string dTJRObqsYa;
      string TPqRoytaWc;
      string jAXtzNtUFy;
      string bpYaHxweBY;
      string isWkdltnIz;
      string kMntJdwORB;
      string gWnZydqQJr;
      string BOZxspcmQN;
      string SGLFNOBdQd;
      string BhNzrMFxlA;
      string tceQxVmqAS;
      string AJyDiaKhMi;
      string bMAeqTBZFf;
      string kfAPTpbuIq;
      string aKcxdqjJQR;
      string CXkCXgczZd;
      string UNkUhUIhjs;
      string yPYUHRjCBz;
      string jrImdNtxrl;
      string MbUeWNYIOI;
      if(dTJRObqsYa == tceQxVmqAS){iCZXSlyPtG = true;}
      else if(tceQxVmqAS == dTJRObqsYa){zZjYjnxSom = true;}
      if(TPqRoytaWc == AJyDiaKhMi){xZxasbFxpU = true;}
      else if(AJyDiaKhMi == TPqRoytaWc){PJQxFrtMNx = true;}
      if(jAXtzNtUFy == bMAeqTBZFf){ZKoyfVttyt = true;}
      else if(bMAeqTBZFf == jAXtzNtUFy){NstRrSbFzt = true;}
      if(bpYaHxweBY == kfAPTpbuIq){ramsPgSjUq = true;}
      else if(kfAPTpbuIq == bpYaHxweBY){hEfrtQPjTy = true;}
      if(isWkdltnIz == aKcxdqjJQR){OeDlnletkt = true;}
      else if(aKcxdqjJQR == isWkdltnIz){SpEXbLZuRH = true;}
      if(kMntJdwORB == CXkCXgczZd){IaRthXMarw = true;}
      else if(CXkCXgczZd == kMntJdwORB){QAoaDFfRgR = true;}
      if(gWnZydqQJr == UNkUhUIhjs){qDQANWmEKM = true;}
      else if(UNkUhUIhjs == gWnZydqQJr){LrTtFLdYDn = true;}
      if(BOZxspcmQN == yPYUHRjCBz){JUczFuHDJt = true;}
      if(SGLFNOBdQd == jrImdNtxrl){qzJElQIsKr = true;}
      if(BhNzrMFxlA == MbUeWNYIOI){UqrXzLNCXR = true;}
      while(yPYUHRjCBz == BOZxspcmQN){bJrPdXoWpg = true;}
      while(jrImdNtxrl == jrImdNtxrl){sgmqcgPEoo = true;}
      while(MbUeWNYIOI == MbUeWNYIOI){kxDClaWJRQ = true;}
      if(iCZXSlyPtG == true){iCZXSlyPtG = false;}
      if(xZxasbFxpU == true){xZxasbFxpU = false;}
      if(ZKoyfVttyt == true){ZKoyfVttyt = false;}
      if(ramsPgSjUq == true){ramsPgSjUq = false;}
      if(OeDlnletkt == true){OeDlnletkt = false;}
      if(IaRthXMarw == true){IaRthXMarw = false;}
      if(qDQANWmEKM == true){qDQANWmEKM = false;}
      if(JUczFuHDJt == true){JUczFuHDJt = false;}
      if(qzJElQIsKr == true){qzJElQIsKr = false;}
      if(UqrXzLNCXR == true){UqrXzLNCXR = false;}
      if(zZjYjnxSom == true){zZjYjnxSom = false;}
      if(PJQxFrtMNx == true){PJQxFrtMNx = false;}
      if(NstRrSbFzt == true){NstRrSbFzt = false;}
      if(hEfrtQPjTy == true){hEfrtQPjTy = false;}
      if(SpEXbLZuRH == true){SpEXbLZuRH = false;}
      if(QAoaDFfRgR == true){QAoaDFfRgR = false;}
      if(LrTtFLdYDn == true){LrTtFLdYDn = false;}
      if(bJrPdXoWpg == true){bJrPdXoWpg = false;}
      if(sgmqcgPEoo == true){sgmqcgPEoo = false;}
      if(kxDClaWJRQ == true){kxDClaWJRQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IXUGPYHJMX
{ 
  void IenPtrDkIk()
  { 
      bool hQrrLjpAfI = false;
      bool dRZDItmtyi = false;
      bool EACTcIhozX = false;
      bool YuYqiWpwux = false;
      bool NRGARxVhQa = false;
      bool FkCNahOXPC = false;
      bool BBAIjhriUl = false;
      bool EpyAUmsBCf = false;
      bool mzXYRmrLQB = false;
      bool HRgruLQxQi = false;
      bool ElNeWOlBsm = false;
      bool nNVjPBdbpw = false;
      bool ogSSdlJFFJ = false;
      bool VwkSaAlsBD = false;
      bool AqScNtwxct = false;
      bool hoGTsXTtAj = false;
      bool EgwiRqbCIP = false;
      bool PjZmuyOoFj = false;
      bool pMcKafoQZD = false;
      bool fqrRyTtiKV = false;
      string ztRJWjkwJf;
      string ICQmHrpZNm;
      string NJGMzdWwZW;
      string ZQddBeQFWb;
      string UMdopagHio;
      string EEKhxonEKr;
      string NoVmGqXmkc;
      string bkDlRAeRVY;
      string xPNjSVFwgM;
      string qLteOfqqhz;
      string CtVGNTAYQw;
      string KViltybkUk;
      string kbGYlQpYWk;
      string JniWVCsGWz;
      string UgfjBUcIjP;
      string EFVwNZnxUw;
      string cbBemVmLPq;
      string EUOVQEwVWQ;
      string nhnHgERlJu;
      string OwlZVseAwe;
      if(ztRJWjkwJf == CtVGNTAYQw){hQrrLjpAfI = true;}
      else if(CtVGNTAYQw == ztRJWjkwJf){ElNeWOlBsm = true;}
      if(ICQmHrpZNm == KViltybkUk){dRZDItmtyi = true;}
      else if(KViltybkUk == ICQmHrpZNm){nNVjPBdbpw = true;}
      if(NJGMzdWwZW == kbGYlQpYWk){EACTcIhozX = true;}
      else if(kbGYlQpYWk == NJGMzdWwZW){ogSSdlJFFJ = true;}
      if(ZQddBeQFWb == JniWVCsGWz){YuYqiWpwux = true;}
      else if(JniWVCsGWz == ZQddBeQFWb){VwkSaAlsBD = true;}
      if(UMdopagHio == UgfjBUcIjP){NRGARxVhQa = true;}
      else if(UgfjBUcIjP == UMdopagHio){AqScNtwxct = true;}
      if(EEKhxonEKr == EFVwNZnxUw){FkCNahOXPC = true;}
      else if(EFVwNZnxUw == EEKhxonEKr){hoGTsXTtAj = true;}
      if(NoVmGqXmkc == cbBemVmLPq){BBAIjhriUl = true;}
      else if(cbBemVmLPq == NoVmGqXmkc){EgwiRqbCIP = true;}
      if(bkDlRAeRVY == EUOVQEwVWQ){EpyAUmsBCf = true;}
      if(xPNjSVFwgM == nhnHgERlJu){mzXYRmrLQB = true;}
      if(qLteOfqqhz == OwlZVseAwe){HRgruLQxQi = true;}
      while(EUOVQEwVWQ == bkDlRAeRVY){PjZmuyOoFj = true;}
      while(nhnHgERlJu == nhnHgERlJu){pMcKafoQZD = true;}
      while(OwlZVseAwe == OwlZVseAwe){fqrRyTtiKV = true;}
      if(hQrrLjpAfI == true){hQrrLjpAfI = false;}
      if(dRZDItmtyi == true){dRZDItmtyi = false;}
      if(EACTcIhozX == true){EACTcIhozX = false;}
      if(YuYqiWpwux == true){YuYqiWpwux = false;}
      if(NRGARxVhQa == true){NRGARxVhQa = false;}
      if(FkCNahOXPC == true){FkCNahOXPC = false;}
      if(BBAIjhriUl == true){BBAIjhriUl = false;}
      if(EpyAUmsBCf == true){EpyAUmsBCf = false;}
      if(mzXYRmrLQB == true){mzXYRmrLQB = false;}
      if(HRgruLQxQi == true){HRgruLQxQi = false;}
      if(ElNeWOlBsm == true){ElNeWOlBsm = false;}
      if(nNVjPBdbpw == true){nNVjPBdbpw = false;}
      if(ogSSdlJFFJ == true){ogSSdlJFFJ = false;}
      if(VwkSaAlsBD == true){VwkSaAlsBD = false;}
      if(AqScNtwxct == true){AqScNtwxct = false;}
      if(hoGTsXTtAj == true){hoGTsXTtAj = false;}
      if(EgwiRqbCIP == true){EgwiRqbCIP = false;}
      if(PjZmuyOoFj == true){PjZmuyOoFj = false;}
      if(pMcKafoQZD == true){pMcKafoQZD = false;}
      if(fqrRyTtiKV == true){fqrRyTtiKV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YEMFFOZFTP
{ 
  void hJrWbEUFyq()
  { 
      bool SPOBuUGZbx = false;
      bool iacLbynkdn = false;
      bool ZUbCJAkFgK = false;
      bool dujWkrjqpA = false;
      bool MqVHIbaEhS = false;
      bool JmuaYynMqt = false;
      bool iBsRSmpGZj = false;
      bool NxudbhyTsg = false;
      bool ZfWOAqAJxm = false;
      bool EXzwQLyEoV = false;
      bool lUexEMqRzq = false;
      bool zTSKUDddQa = false;
      bool mgImfpyzMQ = false;
      bool iteWuEBZKn = false;
      bool AiKGmkEnbN = false;
      bool gTmNiELqRN = false;
      bool NrEhHFnuOP = false;
      bool BETcaDWCzu = false;
      bool lJXziPGRnp = false;
      bool sJHwZHdbzg = false;
      string DzrpoYkNUS;
      string HMiPbPueVO;
      string ztnCEVETRl;
      string MFBogyZkWb;
      string TcTfzJssif;
      string QuCkTIKpkS;
      string TRwhGBKsid;
      string pJIstWaICt;
      string cLjkVRDQVX;
      string njADHCgkZx;
      string yzJFpGlIqx;
      string gCmppHgKMn;
      string xtXLpFIFlq;
      string opiFwdCeuO;
      string euYXplxJMA;
      string VVXkAEayPj;
      string xgWzHqSgtL;
      string FBPyICUAUE;
      string IzrkUSRyFr;
      string CEPKQyXZPy;
      if(DzrpoYkNUS == yzJFpGlIqx){SPOBuUGZbx = true;}
      else if(yzJFpGlIqx == DzrpoYkNUS){lUexEMqRzq = true;}
      if(HMiPbPueVO == gCmppHgKMn){iacLbynkdn = true;}
      else if(gCmppHgKMn == HMiPbPueVO){zTSKUDddQa = true;}
      if(ztnCEVETRl == xtXLpFIFlq){ZUbCJAkFgK = true;}
      else if(xtXLpFIFlq == ztnCEVETRl){mgImfpyzMQ = true;}
      if(MFBogyZkWb == opiFwdCeuO){dujWkrjqpA = true;}
      else if(opiFwdCeuO == MFBogyZkWb){iteWuEBZKn = true;}
      if(TcTfzJssif == euYXplxJMA){MqVHIbaEhS = true;}
      else if(euYXplxJMA == TcTfzJssif){AiKGmkEnbN = true;}
      if(QuCkTIKpkS == VVXkAEayPj){JmuaYynMqt = true;}
      else if(VVXkAEayPj == QuCkTIKpkS){gTmNiELqRN = true;}
      if(TRwhGBKsid == xgWzHqSgtL){iBsRSmpGZj = true;}
      else if(xgWzHqSgtL == TRwhGBKsid){NrEhHFnuOP = true;}
      if(pJIstWaICt == FBPyICUAUE){NxudbhyTsg = true;}
      if(cLjkVRDQVX == IzrkUSRyFr){ZfWOAqAJxm = true;}
      if(njADHCgkZx == CEPKQyXZPy){EXzwQLyEoV = true;}
      while(FBPyICUAUE == pJIstWaICt){BETcaDWCzu = true;}
      while(IzrkUSRyFr == IzrkUSRyFr){lJXziPGRnp = true;}
      while(CEPKQyXZPy == CEPKQyXZPy){sJHwZHdbzg = true;}
      if(SPOBuUGZbx == true){SPOBuUGZbx = false;}
      if(iacLbynkdn == true){iacLbynkdn = false;}
      if(ZUbCJAkFgK == true){ZUbCJAkFgK = false;}
      if(dujWkrjqpA == true){dujWkrjqpA = false;}
      if(MqVHIbaEhS == true){MqVHIbaEhS = false;}
      if(JmuaYynMqt == true){JmuaYynMqt = false;}
      if(iBsRSmpGZj == true){iBsRSmpGZj = false;}
      if(NxudbhyTsg == true){NxudbhyTsg = false;}
      if(ZfWOAqAJxm == true){ZfWOAqAJxm = false;}
      if(EXzwQLyEoV == true){EXzwQLyEoV = false;}
      if(lUexEMqRzq == true){lUexEMqRzq = false;}
      if(zTSKUDddQa == true){zTSKUDddQa = false;}
      if(mgImfpyzMQ == true){mgImfpyzMQ = false;}
      if(iteWuEBZKn == true){iteWuEBZKn = false;}
      if(AiKGmkEnbN == true){AiKGmkEnbN = false;}
      if(gTmNiELqRN == true){gTmNiELqRN = false;}
      if(NrEhHFnuOP == true){NrEhHFnuOP = false;}
      if(BETcaDWCzu == true){BETcaDWCzu = false;}
      if(lJXziPGRnp == true){lJXziPGRnp = false;}
      if(sJHwZHdbzg == true){sJHwZHdbzg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DTPRDFBYQZ
{ 
  void MGLtFacJMo()
  { 
      bool uytjXHoQKn = false;
      bool sHoSwJBLFU = false;
      bool BXqjeDLcRm = false;
      bool eRmcSWMaJf = false;
      bool LmhgUKWFSj = false;
      bool aDRphXHJET = false;
      bool uLzXJbTLzY = false;
      bool xaCZJOoJPU = false;
      bool fGJhLaAwuu = false;
      bool PCVojznJXs = false;
      bool qLGtlzAqgT = false;
      bool hxsjnnCQMh = false;
      bool aWQDItFMoJ = false;
      bool aflWdUzPwL = false;
      bool ZIObMSJlBw = false;
      bool xWxoRTuCkq = false;
      bool tnCXrCKWGT = false;
      bool nmUAISHopp = false;
      bool kTLsLDixEJ = false;
      bool YxeFRlFqiK = false;
      string sOLmyuyxXr;
      string CLuWFrEeBy;
      string DadEJRztpb;
      string saVdsgiQjN;
      string lOteObFgfI;
      string CzCjrSjGcg;
      string wDHuybpRcX;
      string JmumMofzph;
      string LRNgZtYlka;
      string xbnCRhGzfl;
      string lmDIzPEOWD;
      string lkQuVdpZVE;
      string DDgBagzrUe;
      string hgTDwXOFhJ;
      string oJOgoMLrgm;
      string qgcahhGBgR;
      string QMsrVFQMyx;
      string PjrLPtnzMO;
      string VGKgmADsUN;
      string RMXPscPWLi;
      if(sOLmyuyxXr == lmDIzPEOWD){uytjXHoQKn = true;}
      else if(lmDIzPEOWD == sOLmyuyxXr){qLGtlzAqgT = true;}
      if(CLuWFrEeBy == lkQuVdpZVE){sHoSwJBLFU = true;}
      else if(lkQuVdpZVE == CLuWFrEeBy){hxsjnnCQMh = true;}
      if(DadEJRztpb == DDgBagzrUe){BXqjeDLcRm = true;}
      else if(DDgBagzrUe == DadEJRztpb){aWQDItFMoJ = true;}
      if(saVdsgiQjN == hgTDwXOFhJ){eRmcSWMaJf = true;}
      else if(hgTDwXOFhJ == saVdsgiQjN){aflWdUzPwL = true;}
      if(lOteObFgfI == oJOgoMLrgm){LmhgUKWFSj = true;}
      else if(oJOgoMLrgm == lOteObFgfI){ZIObMSJlBw = true;}
      if(CzCjrSjGcg == qgcahhGBgR){aDRphXHJET = true;}
      else if(qgcahhGBgR == CzCjrSjGcg){xWxoRTuCkq = true;}
      if(wDHuybpRcX == QMsrVFQMyx){uLzXJbTLzY = true;}
      else if(QMsrVFQMyx == wDHuybpRcX){tnCXrCKWGT = true;}
      if(JmumMofzph == PjrLPtnzMO){xaCZJOoJPU = true;}
      if(LRNgZtYlka == VGKgmADsUN){fGJhLaAwuu = true;}
      if(xbnCRhGzfl == RMXPscPWLi){PCVojznJXs = true;}
      while(PjrLPtnzMO == JmumMofzph){nmUAISHopp = true;}
      while(VGKgmADsUN == VGKgmADsUN){kTLsLDixEJ = true;}
      while(RMXPscPWLi == RMXPscPWLi){YxeFRlFqiK = true;}
      if(uytjXHoQKn == true){uytjXHoQKn = false;}
      if(sHoSwJBLFU == true){sHoSwJBLFU = false;}
      if(BXqjeDLcRm == true){BXqjeDLcRm = false;}
      if(eRmcSWMaJf == true){eRmcSWMaJf = false;}
      if(LmhgUKWFSj == true){LmhgUKWFSj = false;}
      if(aDRphXHJET == true){aDRphXHJET = false;}
      if(uLzXJbTLzY == true){uLzXJbTLzY = false;}
      if(xaCZJOoJPU == true){xaCZJOoJPU = false;}
      if(fGJhLaAwuu == true){fGJhLaAwuu = false;}
      if(PCVojznJXs == true){PCVojznJXs = false;}
      if(qLGtlzAqgT == true){qLGtlzAqgT = false;}
      if(hxsjnnCQMh == true){hxsjnnCQMh = false;}
      if(aWQDItFMoJ == true){aWQDItFMoJ = false;}
      if(aflWdUzPwL == true){aflWdUzPwL = false;}
      if(ZIObMSJlBw == true){ZIObMSJlBw = false;}
      if(xWxoRTuCkq == true){xWxoRTuCkq = false;}
      if(tnCXrCKWGT == true){tnCXrCKWGT = false;}
      if(nmUAISHopp == true){nmUAISHopp = false;}
      if(kTLsLDixEJ == true){kTLsLDixEJ = false;}
      if(YxeFRlFqiK == true){YxeFRlFqiK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WDKNBJIAZZ
{ 
  void sUoAzkDenQ()
  { 
      bool AiVKOHyodt = false;
      bool zAKBMqPBLQ = false;
      bool BKufOOdNGj = false;
      bool GeYFTRGopR = false;
      bool wQKVxmdkOO = false;
      bool BVgCLonpuz = false;
      bool djhtmTaFgu = false;
      bool kaKsUjzYhb = false;
      bool krzrhjyWte = false;
      bool dQsqnLiQhd = false;
      bool MYETdaLmga = false;
      bool oOHTNlkpLD = false;
      bool UDKCQTgSFJ = false;
      bool BhqEOMneNG = false;
      bool XKoSoPJYcB = false;
      bool ZrFdIINCCJ = false;
      bool sshXZGWCFB = false;
      bool yGbEfKOrMB = false;
      bool KHoDjIcNwG = false;
      bool ykbENecRsh = false;
      string LAaLrdyPom;
      string MGXXPqxgHO;
      string ywtLZMXbng;
      string syrYAaGdZt;
      string SuxJsjPodr;
      string MipeyOFPke;
      string FVaHsONyXo;
      string kSHMuDykRp;
      string xixwTJHMak;
      string UqstoxTpPe;
      string WQQoHtbdju;
      string QUxuhWYemj;
      string HAXmTtZMXy;
      string iIUmSfSHoZ;
      string hdceUzsxMS;
      string YnCfXWrcUN;
      string TPGkLHzKbC;
      string DQpNCcWrST;
      string AbzFZtGoPw;
      string molbGRWrTM;
      if(LAaLrdyPom == WQQoHtbdju){AiVKOHyodt = true;}
      else if(WQQoHtbdju == LAaLrdyPom){MYETdaLmga = true;}
      if(MGXXPqxgHO == QUxuhWYemj){zAKBMqPBLQ = true;}
      else if(QUxuhWYemj == MGXXPqxgHO){oOHTNlkpLD = true;}
      if(ywtLZMXbng == HAXmTtZMXy){BKufOOdNGj = true;}
      else if(HAXmTtZMXy == ywtLZMXbng){UDKCQTgSFJ = true;}
      if(syrYAaGdZt == iIUmSfSHoZ){GeYFTRGopR = true;}
      else if(iIUmSfSHoZ == syrYAaGdZt){BhqEOMneNG = true;}
      if(SuxJsjPodr == hdceUzsxMS){wQKVxmdkOO = true;}
      else if(hdceUzsxMS == SuxJsjPodr){XKoSoPJYcB = true;}
      if(MipeyOFPke == YnCfXWrcUN){BVgCLonpuz = true;}
      else if(YnCfXWrcUN == MipeyOFPke){ZrFdIINCCJ = true;}
      if(FVaHsONyXo == TPGkLHzKbC){djhtmTaFgu = true;}
      else if(TPGkLHzKbC == FVaHsONyXo){sshXZGWCFB = true;}
      if(kSHMuDykRp == DQpNCcWrST){kaKsUjzYhb = true;}
      if(xixwTJHMak == AbzFZtGoPw){krzrhjyWte = true;}
      if(UqstoxTpPe == molbGRWrTM){dQsqnLiQhd = true;}
      while(DQpNCcWrST == kSHMuDykRp){yGbEfKOrMB = true;}
      while(AbzFZtGoPw == AbzFZtGoPw){KHoDjIcNwG = true;}
      while(molbGRWrTM == molbGRWrTM){ykbENecRsh = true;}
      if(AiVKOHyodt == true){AiVKOHyodt = false;}
      if(zAKBMqPBLQ == true){zAKBMqPBLQ = false;}
      if(BKufOOdNGj == true){BKufOOdNGj = false;}
      if(GeYFTRGopR == true){GeYFTRGopR = false;}
      if(wQKVxmdkOO == true){wQKVxmdkOO = false;}
      if(BVgCLonpuz == true){BVgCLonpuz = false;}
      if(djhtmTaFgu == true){djhtmTaFgu = false;}
      if(kaKsUjzYhb == true){kaKsUjzYhb = false;}
      if(krzrhjyWte == true){krzrhjyWte = false;}
      if(dQsqnLiQhd == true){dQsqnLiQhd = false;}
      if(MYETdaLmga == true){MYETdaLmga = false;}
      if(oOHTNlkpLD == true){oOHTNlkpLD = false;}
      if(UDKCQTgSFJ == true){UDKCQTgSFJ = false;}
      if(BhqEOMneNG == true){BhqEOMneNG = false;}
      if(XKoSoPJYcB == true){XKoSoPJYcB = false;}
      if(ZrFdIINCCJ == true){ZrFdIINCCJ = false;}
      if(sshXZGWCFB == true){sshXZGWCFB = false;}
      if(yGbEfKOrMB == true){yGbEfKOrMB = false;}
      if(KHoDjIcNwG == true){KHoDjIcNwG = false;}
      if(ykbENecRsh == true){ykbENecRsh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GERRSJTBUT
{ 
  void xtVOAmqqRK()
  { 
      bool NgIWCFtShz = false;
      bool AHtsCQrJLj = false;
      bool CRJwlRVGLk = false;
      bool SkjfPpzdGY = false;
      bool JoqeCrwTnI = false;
      bool rARAEwXMjj = false;
      bool inHwgOXNcM = false;
      bool RODmZNadts = false;
      bool VBRDsRTibT = false;
      bool SlsVoVhtxm = false;
      bool Uhqbqcwdaq = false;
      bool UsSqNgWDDO = false;
      bool uolJseVgxE = false;
      bool eggGYnKoMQ = false;
      bool VpHjyZTBIH = false;
      bool zdphqeugiL = false;
      bool GPfWLnLLRY = false;
      bool VgqmsFgBLT = false;
      bool LTYoEApyOs = false;
      bool rdGBJGJkYJ = false;
      string kQbDzoQHiC;
      string iVJOgGufux;
      string MKPrVgwEIO;
      string WNMDRZzGtj;
      string UHIiDGekNY;
      string coykqZAigS;
      string rLzUfUJGxH;
      string HnkLcFBfoP;
      string BLqikgPbLq;
      string YPYaqJHnDh;
      string xXmFRnDmIl;
      string YTtRQfUPiz;
      string FhuFirPKTS;
      string xNcGSdXkRx;
      string ccSZSEUHJK;
      string orEDbPchWZ;
      string YsSooLqnzm;
      string IjxkVcOUmd;
      string WHAIdEIYdC;
      string ApNqYjJckH;
      if(kQbDzoQHiC == xXmFRnDmIl){NgIWCFtShz = true;}
      else if(xXmFRnDmIl == kQbDzoQHiC){Uhqbqcwdaq = true;}
      if(iVJOgGufux == YTtRQfUPiz){AHtsCQrJLj = true;}
      else if(YTtRQfUPiz == iVJOgGufux){UsSqNgWDDO = true;}
      if(MKPrVgwEIO == FhuFirPKTS){CRJwlRVGLk = true;}
      else if(FhuFirPKTS == MKPrVgwEIO){uolJseVgxE = true;}
      if(WNMDRZzGtj == xNcGSdXkRx){SkjfPpzdGY = true;}
      else if(xNcGSdXkRx == WNMDRZzGtj){eggGYnKoMQ = true;}
      if(UHIiDGekNY == ccSZSEUHJK){JoqeCrwTnI = true;}
      else if(ccSZSEUHJK == UHIiDGekNY){VpHjyZTBIH = true;}
      if(coykqZAigS == orEDbPchWZ){rARAEwXMjj = true;}
      else if(orEDbPchWZ == coykqZAigS){zdphqeugiL = true;}
      if(rLzUfUJGxH == YsSooLqnzm){inHwgOXNcM = true;}
      else if(YsSooLqnzm == rLzUfUJGxH){GPfWLnLLRY = true;}
      if(HnkLcFBfoP == IjxkVcOUmd){RODmZNadts = true;}
      if(BLqikgPbLq == WHAIdEIYdC){VBRDsRTibT = true;}
      if(YPYaqJHnDh == ApNqYjJckH){SlsVoVhtxm = true;}
      while(IjxkVcOUmd == HnkLcFBfoP){VgqmsFgBLT = true;}
      while(WHAIdEIYdC == WHAIdEIYdC){LTYoEApyOs = true;}
      while(ApNqYjJckH == ApNqYjJckH){rdGBJGJkYJ = true;}
      if(NgIWCFtShz == true){NgIWCFtShz = false;}
      if(AHtsCQrJLj == true){AHtsCQrJLj = false;}
      if(CRJwlRVGLk == true){CRJwlRVGLk = false;}
      if(SkjfPpzdGY == true){SkjfPpzdGY = false;}
      if(JoqeCrwTnI == true){JoqeCrwTnI = false;}
      if(rARAEwXMjj == true){rARAEwXMjj = false;}
      if(inHwgOXNcM == true){inHwgOXNcM = false;}
      if(RODmZNadts == true){RODmZNadts = false;}
      if(VBRDsRTibT == true){VBRDsRTibT = false;}
      if(SlsVoVhtxm == true){SlsVoVhtxm = false;}
      if(Uhqbqcwdaq == true){Uhqbqcwdaq = false;}
      if(UsSqNgWDDO == true){UsSqNgWDDO = false;}
      if(uolJseVgxE == true){uolJseVgxE = false;}
      if(eggGYnKoMQ == true){eggGYnKoMQ = false;}
      if(VpHjyZTBIH == true){VpHjyZTBIH = false;}
      if(zdphqeugiL == true){zdphqeugiL = false;}
      if(GPfWLnLLRY == true){GPfWLnLLRY = false;}
      if(VgqmsFgBLT == true){VgqmsFgBLT = false;}
      if(LTYoEApyOs == true){LTYoEApyOs = false;}
      if(rdGBJGJkYJ == true){rdGBJGJkYJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TYUNLUJEIV
{ 
  void zqZXHnjVbC()
  { 
      bool lEzFeNDyVj = false;
      bool LEkmccrtoL = false;
      bool VRwDallVcQ = false;
      bool paumSqYBPw = false;
      bool JAJdVOeGSB = false;
      bool TujgTUHwer = false;
      bool bgVEskJyUk = false;
      bool EqerCUHSgL = false;
      bool HfDaxupOSx = false;
      bool icVWUbeEjj = false;
      bool FfkgxcPrey = false;
      bool NoOTkwdtHy = false;
      bool uteXBbUIXZ = false;
      bool pChxFatVdT = false;
      bool exjUjtOCkY = false;
      bool xjxkoKBNfU = false;
      bool HGUEIKGQNJ = false;
      bool BIQmTxKKmH = false;
      bool NSWzbGFxIu = false;
      bool ZfpIMXceLY = false;
      string wPGiyPnGIA;
      string SCthKgFkRP;
      string nWSDViEBNd;
      string qHzRJILdWa;
      string yzXyqoZYhG;
      string lWJVtYwDMP;
      string LlseJLDbXB;
      string UaOqQnyTLg;
      string JeTGqTydWk;
      string MIRGOMGsoe;
      string lxBglKHREG;
      string ZcrfGgSlmo;
      string NZEmnMJHcE;
      string gFeftLdlUf;
      string MfYQKjPkAh;
      string tUFzRMrNrY;
      string BzozYUxLkt;
      string CfQHcgAmcE;
      string wXHtKMzfOh;
      string TPtueMpZro;
      if(wPGiyPnGIA == lxBglKHREG){lEzFeNDyVj = true;}
      else if(lxBglKHREG == wPGiyPnGIA){FfkgxcPrey = true;}
      if(SCthKgFkRP == ZcrfGgSlmo){LEkmccrtoL = true;}
      else if(ZcrfGgSlmo == SCthKgFkRP){NoOTkwdtHy = true;}
      if(nWSDViEBNd == NZEmnMJHcE){VRwDallVcQ = true;}
      else if(NZEmnMJHcE == nWSDViEBNd){uteXBbUIXZ = true;}
      if(qHzRJILdWa == gFeftLdlUf){paumSqYBPw = true;}
      else if(gFeftLdlUf == qHzRJILdWa){pChxFatVdT = true;}
      if(yzXyqoZYhG == MfYQKjPkAh){JAJdVOeGSB = true;}
      else if(MfYQKjPkAh == yzXyqoZYhG){exjUjtOCkY = true;}
      if(lWJVtYwDMP == tUFzRMrNrY){TujgTUHwer = true;}
      else if(tUFzRMrNrY == lWJVtYwDMP){xjxkoKBNfU = true;}
      if(LlseJLDbXB == BzozYUxLkt){bgVEskJyUk = true;}
      else if(BzozYUxLkt == LlseJLDbXB){HGUEIKGQNJ = true;}
      if(UaOqQnyTLg == CfQHcgAmcE){EqerCUHSgL = true;}
      if(JeTGqTydWk == wXHtKMzfOh){HfDaxupOSx = true;}
      if(MIRGOMGsoe == TPtueMpZro){icVWUbeEjj = true;}
      while(CfQHcgAmcE == UaOqQnyTLg){BIQmTxKKmH = true;}
      while(wXHtKMzfOh == wXHtKMzfOh){NSWzbGFxIu = true;}
      while(TPtueMpZro == TPtueMpZro){ZfpIMXceLY = true;}
      if(lEzFeNDyVj == true){lEzFeNDyVj = false;}
      if(LEkmccrtoL == true){LEkmccrtoL = false;}
      if(VRwDallVcQ == true){VRwDallVcQ = false;}
      if(paumSqYBPw == true){paumSqYBPw = false;}
      if(JAJdVOeGSB == true){JAJdVOeGSB = false;}
      if(TujgTUHwer == true){TujgTUHwer = false;}
      if(bgVEskJyUk == true){bgVEskJyUk = false;}
      if(EqerCUHSgL == true){EqerCUHSgL = false;}
      if(HfDaxupOSx == true){HfDaxupOSx = false;}
      if(icVWUbeEjj == true){icVWUbeEjj = false;}
      if(FfkgxcPrey == true){FfkgxcPrey = false;}
      if(NoOTkwdtHy == true){NoOTkwdtHy = false;}
      if(uteXBbUIXZ == true){uteXBbUIXZ = false;}
      if(pChxFatVdT == true){pChxFatVdT = false;}
      if(exjUjtOCkY == true){exjUjtOCkY = false;}
      if(xjxkoKBNfU == true){xjxkoKBNfU = false;}
      if(HGUEIKGQNJ == true){HGUEIKGQNJ = false;}
      if(BIQmTxKKmH == true){BIQmTxKKmH = false;}
      if(NSWzbGFxIu == true){NSWzbGFxIu = false;}
      if(ZfpIMXceLY == true){ZfpIMXceLY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFGBUETQIO
{ 
  void IVZlePhAJF()
  { 
      bool hSEqdgstqM = false;
      bool jUxaUGnLKF = false;
      bool LiWMcFFBsR = false;
      bool ljBggBNCFc = false;
      bool gVsgQacSdn = false;
      bool TBgkLzuqNY = false;
      bool brAYZzSQtS = false;
      bool rlFgYoppwC = false;
      bool bmWEyjDQUh = false;
      bool GWngBnUTHR = false;
      bool HMYLuhuzLV = false;
      bool IFuLwnVwao = false;
      bool wBuLMVxYfj = false;
      bool UWiduOOLJP = false;
      bool oDEzZAacjM = false;
      bool SYrRVFRMyZ = false;
      bool kWSbBlWQPg = false;
      bool YJlLArwwlL = false;
      bool tUnSRueQIo = false;
      bool xCMjeRkcxm = false;
      string ccDTfCcEJd;
      string JLRKbQRbWK;
      string CQTEcJLxjW;
      string fBybjjFkUJ;
      string zAcgcOUeCD;
      string qyDYCMJypW;
      string pfTmxHNpZr;
      string KgHNLBnlbO;
      string ngtfegyZYX;
      string ZGuyTSgpiU;
      string AeEJsKqoMB;
      string YWWbhIkmHQ;
      string InQCSDkJtr;
      string UxDGNJckmT;
      string pIMXyCjSPK;
      string hshSMMNBqo;
      string YhuUgaTQOY;
      string fAznazbsEP;
      string TSsjKaPksB;
      string uatytINqqW;
      if(ccDTfCcEJd == AeEJsKqoMB){hSEqdgstqM = true;}
      else if(AeEJsKqoMB == ccDTfCcEJd){HMYLuhuzLV = true;}
      if(JLRKbQRbWK == YWWbhIkmHQ){jUxaUGnLKF = true;}
      else if(YWWbhIkmHQ == JLRKbQRbWK){IFuLwnVwao = true;}
      if(CQTEcJLxjW == InQCSDkJtr){LiWMcFFBsR = true;}
      else if(InQCSDkJtr == CQTEcJLxjW){wBuLMVxYfj = true;}
      if(fBybjjFkUJ == UxDGNJckmT){ljBggBNCFc = true;}
      else if(UxDGNJckmT == fBybjjFkUJ){UWiduOOLJP = true;}
      if(zAcgcOUeCD == pIMXyCjSPK){gVsgQacSdn = true;}
      else if(pIMXyCjSPK == zAcgcOUeCD){oDEzZAacjM = true;}
      if(qyDYCMJypW == hshSMMNBqo){TBgkLzuqNY = true;}
      else if(hshSMMNBqo == qyDYCMJypW){SYrRVFRMyZ = true;}
      if(pfTmxHNpZr == YhuUgaTQOY){brAYZzSQtS = true;}
      else if(YhuUgaTQOY == pfTmxHNpZr){kWSbBlWQPg = true;}
      if(KgHNLBnlbO == fAznazbsEP){rlFgYoppwC = true;}
      if(ngtfegyZYX == TSsjKaPksB){bmWEyjDQUh = true;}
      if(ZGuyTSgpiU == uatytINqqW){GWngBnUTHR = true;}
      while(fAznazbsEP == KgHNLBnlbO){YJlLArwwlL = true;}
      while(TSsjKaPksB == TSsjKaPksB){tUnSRueQIo = true;}
      while(uatytINqqW == uatytINqqW){xCMjeRkcxm = true;}
      if(hSEqdgstqM == true){hSEqdgstqM = false;}
      if(jUxaUGnLKF == true){jUxaUGnLKF = false;}
      if(LiWMcFFBsR == true){LiWMcFFBsR = false;}
      if(ljBggBNCFc == true){ljBggBNCFc = false;}
      if(gVsgQacSdn == true){gVsgQacSdn = false;}
      if(TBgkLzuqNY == true){TBgkLzuqNY = false;}
      if(brAYZzSQtS == true){brAYZzSQtS = false;}
      if(rlFgYoppwC == true){rlFgYoppwC = false;}
      if(bmWEyjDQUh == true){bmWEyjDQUh = false;}
      if(GWngBnUTHR == true){GWngBnUTHR = false;}
      if(HMYLuhuzLV == true){HMYLuhuzLV = false;}
      if(IFuLwnVwao == true){IFuLwnVwao = false;}
      if(wBuLMVxYfj == true){wBuLMVxYfj = false;}
      if(UWiduOOLJP == true){UWiduOOLJP = false;}
      if(oDEzZAacjM == true){oDEzZAacjM = false;}
      if(SYrRVFRMyZ == true){SYrRVFRMyZ = false;}
      if(kWSbBlWQPg == true){kWSbBlWQPg = false;}
      if(YJlLArwwlL == true){YJlLArwwlL = false;}
      if(tUnSRueQIo == true){tUnSRueQIo = false;}
      if(xCMjeRkcxm == true){xCMjeRkcxm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NGHLCZHILX
{ 
  void IJgsbYkcKz()
  { 
      bool glTVNMeOkH = false;
      bool VoYoABaMBB = false;
      bool fnqWCCJnul = false;
      bool QIpsOSAFlh = false;
      bool QqqRGXRsxC = false;
      bool OLdsWsuxSL = false;
      bool CqSzqNyeZh = false;
      bool AUZTjowYQe = false;
      bool jQpsWEdwWU = false;
      bool WDlafYXrar = false;
      bool YlSOBskKIh = false;
      bool xWgnalAZbl = false;
      bool iCIFLxiznL = false;
      bool QExXFyxbqc = false;
      bool TTmoXAVxzt = false;
      bool YyPoJWcNDD = false;
      bool KkWxRrYIhc = false;
      bool nYiyRPOTgK = false;
      bool akAtlSoINi = false;
      bool UjXmSiwpXf = false;
      string OHXwHjlmuH;
      string fiHpaPIhIr;
      string jBgtpRJadn;
      string dyoeIdRNem;
      string bPtKDXdobL;
      string ETqOdMacFp;
      string ZKIHdgscgw;
      string xuDUQTGVqS;
      string mUySiJHaAu;
      string CoHnMQHmgV;
      string dBHeOJQVxJ;
      string GElmCFLpYT;
      string ZSbltInOHA;
      string MToUnlMTEY;
      string rkcqoxDTlH;
      string EQNMuLYVkF;
      string VCNxwlPQzP;
      string srlzbnojww;
      string EUbAuuFbZc;
      string MqhyDoXftC;
      if(OHXwHjlmuH == dBHeOJQVxJ){glTVNMeOkH = true;}
      else if(dBHeOJQVxJ == OHXwHjlmuH){YlSOBskKIh = true;}
      if(fiHpaPIhIr == GElmCFLpYT){VoYoABaMBB = true;}
      else if(GElmCFLpYT == fiHpaPIhIr){xWgnalAZbl = true;}
      if(jBgtpRJadn == ZSbltInOHA){fnqWCCJnul = true;}
      else if(ZSbltInOHA == jBgtpRJadn){iCIFLxiznL = true;}
      if(dyoeIdRNem == MToUnlMTEY){QIpsOSAFlh = true;}
      else if(MToUnlMTEY == dyoeIdRNem){QExXFyxbqc = true;}
      if(bPtKDXdobL == rkcqoxDTlH){QqqRGXRsxC = true;}
      else if(rkcqoxDTlH == bPtKDXdobL){TTmoXAVxzt = true;}
      if(ETqOdMacFp == EQNMuLYVkF){OLdsWsuxSL = true;}
      else if(EQNMuLYVkF == ETqOdMacFp){YyPoJWcNDD = true;}
      if(ZKIHdgscgw == VCNxwlPQzP){CqSzqNyeZh = true;}
      else if(VCNxwlPQzP == ZKIHdgscgw){KkWxRrYIhc = true;}
      if(xuDUQTGVqS == srlzbnojww){AUZTjowYQe = true;}
      if(mUySiJHaAu == EUbAuuFbZc){jQpsWEdwWU = true;}
      if(CoHnMQHmgV == MqhyDoXftC){WDlafYXrar = true;}
      while(srlzbnojww == xuDUQTGVqS){nYiyRPOTgK = true;}
      while(EUbAuuFbZc == EUbAuuFbZc){akAtlSoINi = true;}
      while(MqhyDoXftC == MqhyDoXftC){UjXmSiwpXf = true;}
      if(glTVNMeOkH == true){glTVNMeOkH = false;}
      if(VoYoABaMBB == true){VoYoABaMBB = false;}
      if(fnqWCCJnul == true){fnqWCCJnul = false;}
      if(QIpsOSAFlh == true){QIpsOSAFlh = false;}
      if(QqqRGXRsxC == true){QqqRGXRsxC = false;}
      if(OLdsWsuxSL == true){OLdsWsuxSL = false;}
      if(CqSzqNyeZh == true){CqSzqNyeZh = false;}
      if(AUZTjowYQe == true){AUZTjowYQe = false;}
      if(jQpsWEdwWU == true){jQpsWEdwWU = false;}
      if(WDlafYXrar == true){WDlafYXrar = false;}
      if(YlSOBskKIh == true){YlSOBskKIh = false;}
      if(xWgnalAZbl == true){xWgnalAZbl = false;}
      if(iCIFLxiznL == true){iCIFLxiznL = false;}
      if(QExXFyxbqc == true){QExXFyxbqc = false;}
      if(TTmoXAVxzt == true){TTmoXAVxzt = false;}
      if(YyPoJWcNDD == true){YyPoJWcNDD = false;}
      if(KkWxRrYIhc == true){KkWxRrYIhc = false;}
      if(nYiyRPOTgK == true){nYiyRPOTgK = false;}
      if(akAtlSoINi == true){akAtlSoINi = false;}
      if(UjXmSiwpXf == true){UjXmSiwpXf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SGOIBXRETJ
{ 
  void OcZSXeSrkq()
  { 
      bool xoNhMjnGMG = false;
      bool DHaLukGgQo = false;
      bool cnqHbHMExM = false;
      bool oDSSUQqDDR = false;
      bool DNlHHHASMK = false;
      bool eEldqIxGGF = false;
      bool WiIzQAoHpd = false;
      bool tCczlOBjzU = false;
      bool HsqmhkQoaM = false;
      bool TjxytTEmpH = false;
      bool SrciQbalrc = false;
      bool HNHlydqVRf = false;
      bool iAgdKKEeFR = false;
      bool KOsqCOQIWF = false;
      bool JdwyEFbLAQ = false;
      bool ciUKXRLyXF = false;
      bool XwgZSrTPii = false;
      bool MizLWFDhYF = false;
      bool hrdooasiTj = false;
      bool DRkQhMxVfL = false;
      string lrcmqDyzop;
      string kKsnOhYLgX;
      string iVxlpuUHMw;
      string dgQazclRXC;
      string SNXzxgBKRy;
      string isnzxPupxu;
      string ipmsMDtRok;
      string wGneEVyxoI;
      string sKpNNjrQdi;
      string huUbSbaems;
      string miUgCbFJub;
      string QxBnBXAYeb;
      string KcnFCAlMLc;
      string tTJwVKpIKl;
      string diVBRjtgZu;
      string aCzKhKtOdC;
      string psxShxmFSq;
      string hqNsybGmnR;
      string GFlQBrTzNL;
      string PaeIuklDTU;
      if(lrcmqDyzop == miUgCbFJub){xoNhMjnGMG = true;}
      else if(miUgCbFJub == lrcmqDyzop){SrciQbalrc = true;}
      if(kKsnOhYLgX == QxBnBXAYeb){DHaLukGgQo = true;}
      else if(QxBnBXAYeb == kKsnOhYLgX){HNHlydqVRf = true;}
      if(iVxlpuUHMw == KcnFCAlMLc){cnqHbHMExM = true;}
      else if(KcnFCAlMLc == iVxlpuUHMw){iAgdKKEeFR = true;}
      if(dgQazclRXC == tTJwVKpIKl){oDSSUQqDDR = true;}
      else if(tTJwVKpIKl == dgQazclRXC){KOsqCOQIWF = true;}
      if(SNXzxgBKRy == diVBRjtgZu){DNlHHHASMK = true;}
      else if(diVBRjtgZu == SNXzxgBKRy){JdwyEFbLAQ = true;}
      if(isnzxPupxu == aCzKhKtOdC){eEldqIxGGF = true;}
      else if(aCzKhKtOdC == isnzxPupxu){ciUKXRLyXF = true;}
      if(ipmsMDtRok == psxShxmFSq){WiIzQAoHpd = true;}
      else if(psxShxmFSq == ipmsMDtRok){XwgZSrTPii = true;}
      if(wGneEVyxoI == hqNsybGmnR){tCczlOBjzU = true;}
      if(sKpNNjrQdi == GFlQBrTzNL){HsqmhkQoaM = true;}
      if(huUbSbaems == PaeIuklDTU){TjxytTEmpH = true;}
      while(hqNsybGmnR == wGneEVyxoI){MizLWFDhYF = true;}
      while(GFlQBrTzNL == GFlQBrTzNL){hrdooasiTj = true;}
      while(PaeIuklDTU == PaeIuklDTU){DRkQhMxVfL = true;}
      if(xoNhMjnGMG == true){xoNhMjnGMG = false;}
      if(DHaLukGgQo == true){DHaLukGgQo = false;}
      if(cnqHbHMExM == true){cnqHbHMExM = false;}
      if(oDSSUQqDDR == true){oDSSUQqDDR = false;}
      if(DNlHHHASMK == true){DNlHHHASMK = false;}
      if(eEldqIxGGF == true){eEldqIxGGF = false;}
      if(WiIzQAoHpd == true){WiIzQAoHpd = false;}
      if(tCczlOBjzU == true){tCczlOBjzU = false;}
      if(HsqmhkQoaM == true){HsqmhkQoaM = false;}
      if(TjxytTEmpH == true){TjxytTEmpH = false;}
      if(SrciQbalrc == true){SrciQbalrc = false;}
      if(HNHlydqVRf == true){HNHlydqVRf = false;}
      if(iAgdKKEeFR == true){iAgdKKEeFR = false;}
      if(KOsqCOQIWF == true){KOsqCOQIWF = false;}
      if(JdwyEFbLAQ == true){JdwyEFbLAQ = false;}
      if(ciUKXRLyXF == true){ciUKXRLyXF = false;}
      if(XwgZSrTPii == true){XwgZSrTPii = false;}
      if(MizLWFDhYF == true){MizLWFDhYF = false;}
      if(hrdooasiTj == true){hrdooasiTj = false;}
      if(DRkQhMxVfL == true){DRkQhMxVfL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJSULOEUQE
{ 
  void IfSUriwImF()
  { 
      bool DbkqXNlLLl = false;
      bool MoNtSHGLbr = false;
      bool VFINlXqUpn = false;
      bool LilGjxRFsA = false;
      bool eNDNmrHmVa = false;
      bool pCSyJyTXEA = false;
      bool VQVWZcDGKV = false;
      bool oARbMIBtat = false;
      bool QEzOxJQmxk = false;
      bool dtBsdOrgmJ = false;
      bool oAcAkpjqlA = false;
      bool xYwKjRRGYQ = false;
      bool MQIYruzYxy = false;
      bool QTHRFPbydH = false;
      bool ZZBxnEyqJM = false;
      bool xlHWwXqDIp = false;
      bool qKsnjcReFT = false;
      bool oSbRpmPLjm = false;
      bool xIOjAeMjUg = false;
      bool XXonPOfMNK = false;
      string LwyFGnRgIH;
      string DBsqtXNnqG;
      string WtWpCopTBe;
      string LfEtydKGyc;
      string aUfcBEsHJP;
      string VAaYYRZHCR;
      string xyecuWwysP;
      string MHoNeCNsoy;
      string uiJlJKEfVf;
      string ECDgecoDgd;
      string HuNsDOKMsV;
      string EfSEVOosSk;
      string RQcNLJDIiC;
      string NJLKpAVPht;
      string zrlzaXjzLQ;
      string mwjwLqSAhs;
      string LCdqIuUHNU;
      string sYKYkZdclm;
      string ZDwROQYPzz;
      string hUgoiwOupe;
      if(LwyFGnRgIH == HuNsDOKMsV){DbkqXNlLLl = true;}
      else if(HuNsDOKMsV == LwyFGnRgIH){oAcAkpjqlA = true;}
      if(DBsqtXNnqG == EfSEVOosSk){MoNtSHGLbr = true;}
      else if(EfSEVOosSk == DBsqtXNnqG){xYwKjRRGYQ = true;}
      if(WtWpCopTBe == RQcNLJDIiC){VFINlXqUpn = true;}
      else if(RQcNLJDIiC == WtWpCopTBe){MQIYruzYxy = true;}
      if(LfEtydKGyc == NJLKpAVPht){LilGjxRFsA = true;}
      else if(NJLKpAVPht == LfEtydKGyc){QTHRFPbydH = true;}
      if(aUfcBEsHJP == zrlzaXjzLQ){eNDNmrHmVa = true;}
      else if(zrlzaXjzLQ == aUfcBEsHJP){ZZBxnEyqJM = true;}
      if(VAaYYRZHCR == mwjwLqSAhs){pCSyJyTXEA = true;}
      else if(mwjwLqSAhs == VAaYYRZHCR){xlHWwXqDIp = true;}
      if(xyecuWwysP == LCdqIuUHNU){VQVWZcDGKV = true;}
      else if(LCdqIuUHNU == xyecuWwysP){qKsnjcReFT = true;}
      if(MHoNeCNsoy == sYKYkZdclm){oARbMIBtat = true;}
      if(uiJlJKEfVf == ZDwROQYPzz){QEzOxJQmxk = true;}
      if(ECDgecoDgd == hUgoiwOupe){dtBsdOrgmJ = true;}
      while(sYKYkZdclm == MHoNeCNsoy){oSbRpmPLjm = true;}
      while(ZDwROQYPzz == ZDwROQYPzz){xIOjAeMjUg = true;}
      while(hUgoiwOupe == hUgoiwOupe){XXonPOfMNK = true;}
      if(DbkqXNlLLl == true){DbkqXNlLLl = false;}
      if(MoNtSHGLbr == true){MoNtSHGLbr = false;}
      if(VFINlXqUpn == true){VFINlXqUpn = false;}
      if(LilGjxRFsA == true){LilGjxRFsA = false;}
      if(eNDNmrHmVa == true){eNDNmrHmVa = false;}
      if(pCSyJyTXEA == true){pCSyJyTXEA = false;}
      if(VQVWZcDGKV == true){VQVWZcDGKV = false;}
      if(oARbMIBtat == true){oARbMIBtat = false;}
      if(QEzOxJQmxk == true){QEzOxJQmxk = false;}
      if(dtBsdOrgmJ == true){dtBsdOrgmJ = false;}
      if(oAcAkpjqlA == true){oAcAkpjqlA = false;}
      if(xYwKjRRGYQ == true){xYwKjRRGYQ = false;}
      if(MQIYruzYxy == true){MQIYruzYxy = false;}
      if(QTHRFPbydH == true){QTHRFPbydH = false;}
      if(ZZBxnEyqJM == true){ZZBxnEyqJM = false;}
      if(xlHWwXqDIp == true){xlHWwXqDIp = false;}
      if(qKsnjcReFT == true){qKsnjcReFT = false;}
      if(oSbRpmPLjm == true){oSbRpmPLjm = false;}
      if(xIOjAeMjUg == true){xIOjAeMjUg = false;}
      if(XXonPOfMNK == true){XXonPOfMNK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TYJHQRLPMY
{ 
  void TFlQyRPKMr()
  { 
      bool xESokaTfQa = false;
      bool ISMBCiICPe = false;
      bool fwUROakWYj = false;
      bool HWVmdRwGDb = false;
      bool rfDaimPaRl = false;
      bool idtflBjAaK = false;
      bool oxHgTlxZWk = false;
      bool lCynmzrsha = false;
      bool KJFmAdboAc = false;
      bool gwesltYWHx = false;
      bool opEfzfeGsm = false;
      bool IpRzzfrTfp = false;
      bool KIYsDpWEBr = false;
      bool ZVlklUFYmT = false;
      bool yUuNUqdftG = false;
      bool CEpQmgQKcJ = false;
      bool IaFBMlDgNe = false;
      bool aSgLqoMLYM = false;
      bool LqKtoUeUyE = false;
      bool DtucLXPtAh = false;
      string znrLonVrsw;
      string gsxEnxNBcw;
      string PqdQiWOcsT;
      string PduyyDnyGL;
      string zuOybzgmEe;
      string HGlHhIJabR;
      string ZrzZgDyyFj;
      string JPuQxTbeoi;
      string obYOLIrmPp;
      string sMVnlGwoRY;
      string BigTUrLUJO;
      string felrbxSjOY;
      string KKhPpwsHdp;
      string XmNPhGtFsT;
      string wWdBKOacLo;
      string nLasNpARcY;
      string yEqSprQVKV;
      string DNqtbmggFb;
      string VPuoCLMUBr;
      string GcbUUrfKKR;
      if(znrLonVrsw == BigTUrLUJO){xESokaTfQa = true;}
      else if(BigTUrLUJO == znrLonVrsw){opEfzfeGsm = true;}
      if(gsxEnxNBcw == felrbxSjOY){ISMBCiICPe = true;}
      else if(felrbxSjOY == gsxEnxNBcw){IpRzzfrTfp = true;}
      if(PqdQiWOcsT == KKhPpwsHdp){fwUROakWYj = true;}
      else if(KKhPpwsHdp == PqdQiWOcsT){KIYsDpWEBr = true;}
      if(PduyyDnyGL == XmNPhGtFsT){HWVmdRwGDb = true;}
      else if(XmNPhGtFsT == PduyyDnyGL){ZVlklUFYmT = true;}
      if(zuOybzgmEe == wWdBKOacLo){rfDaimPaRl = true;}
      else if(wWdBKOacLo == zuOybzgmEe){yUuNUqdftG = true;}
      if(HGlHhIJabR == nLasNpARcY){idtflBjAaK = true;}
      else if(nLasNpARcY == HGlHhIJabR){CEpQmgQKcJ = true;}
      if(ZrzZgDyyFj == yEqSprQVKV){oxHgTlxZWk = true;}
      else if(yEqSprQVKV == ZrzZgDyyFj){IaFBMlDgNe = true;}
      if(JPuQxTbeoi == DNqtbmggFb){lCynmzrsha = true;}
      if(obYOLIrmPp == VPuoCLMUBr){KJFmAdboAc = true;}
      if(sMVnlGwoRY == GcbUUrfKKR){gwesltYWHx = true;}
      while(DNqtbmggFb == JPuQxTbeoi){aSgLqoMLYM = true;}
      while(VPuoCLMUBr == VPuoCLMUBr){LqKtoUeUyE = true;}
      while(GcbUUrfKKR == GcbUUrfKKR){DtucLXPtAh = true;}
      if(xESokaTfQa == true){xESokaTfQa = false;}
      if(ISMBCiICPe == true){ISMBCiICPe = false;}
      if(fwUROakWYj == true){fwUROakWYj = false;}
      if(HWVmdRwGDb == true){HWVmdRwGDb = false;}
      if(rfDaimPaRl == true){rfDaimPaRl = false;}
      if(idtflBjAaK == true){idtflBjAaK = false;}
      if(oxHgTlxZWk == true){oxHgTlxZWk = false;}
      if(lCynmzrsha == true){lCynmzrsha = false;}
      if(KJFmAdboAc == true){KJFmAdboAc = false;}
      if(gwesltYWHx == true){gwesltYWHx = false;}
      if(opEfzfeGsm == true){opEfzfeGsm = false;}
      if(IpRzzfrTfp == true){IpRzzfrTfp = false;}
      if(KIYsDpWEBr == true){KIYsDpWEBr = false;}
      if(ZVlklUFYmT == true){ZVlklUFYmT = false;}
      if(yUuNUqdftG == true){yUuNUqdftG = false;}
      if(CEpQmgQKcJ == true){CEpQmgQKcJ = false;}
      if(IaFBMlDgNe == true){IaFBMlDgNe = false;}
      if(aSgLqoMLYM == true){aSgLqoMLYM = false;}
      if(LqKtoUeUyE == true){LqKtoUeUyE = false;}
      if(DtucLXPtAh == true){DtucLXPtAh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FCQZALGCZF
{ 
  void DLhegKBqzW()
  { 
      bool hiNOFrrZMB = false;
      bool PQeZtcKRYu = false;
      bool GMMkecSSfC = false;
      bool sWmcDKFPPO = false;
      bool laMgFYdQIL = false;
      bool hWXCtUVbjc = false;
      bool YYtKIrcBVi = false;
      bool XtBJJfAefF = false;
      bool yBKTUVzkii = false;
      bool ncfmoNgCYM = false;
      bool ucuYnmVNsO = false;
      bool UqwddXNZpm = false;
      bool srSmutOOTw = false;
      bool zxFTJVGkfh = false;
      bool zkrTNwgBIR = false;
      bool zGMlTDJHds = false;
      bool XHswPWkcTI = false;
      bool QbsImHAyZy = false;
      bool MNFCxrkTAG = false;
      bool LyHlJrruEp = false;
      string elPTogZrGC;
      string SmXORmuaWZ;
      string BcEnYUMneb;
      string shbXNVUaQO;
      string BkfpcoNxQd;
      string FLHMhBgauU;
      string TlMdIjKAAw;
      string RTJHXPxNLi;
      string GPXBWhaPoM;
      string nsfwuPYBhr;
      string eNxTLkBznR;
      string DSOLNENLGa;
      string IuKmHXnMMI;
      string qufSEsSDol;
      string fabXIUeUiq;
      string BNuGiiDJMm;
      string wnmeZHlwGU;
      string kJVUthTlel;
      string sTdVGdAZiU;
      string pIqCornwyB;
      if(elPTogZrGC == eNxTLkBznR){hiNOFrrZMB = true;}
      else if(eNxTLkBznR == elPTogZrGC){ucuYnmVNsO = true;}
      if(SmXORmuaWZ == DSOLNENLGa){PQeZtcKRYu = true;}
      else if(DSOLNENLGa == SmXORmuaWZ){UqwddXNZpm = true;}
      if(BcEnYUMneb == IuKmHXnMMI){GMMkecSSfC = true;}
      else if(IuKmHXnMMI == BcEnYUMneb){srSmutOOTw = true;}
      if(shbXNVUaQO == qufSEsSDol){sWmcDKFPPO = true;}
      else if(qufSEsSDol == shbXNVUaQO){zxFTJVGkfh = true;}
      if(BkfpcoNxQd == fabXIUeUiq){laMgFYdQIL = true;}
      else if(fabXIUeUiq == BkfpcoNxQd){zkrTNwgBIR = true;}
      if(FLHMhBgauU == BNuGiiDJMm){hWXCtUVbjc = true;}
      else if(BNuGiiDJMm == FLHMhBgauU){zGMlTDJHds = true;}
      if(TlMdIjKAAw == wnmeZHlwGU){YYtKIrcBVi = true;}
      else if(wnmeZHlwGU == TlMdIjKAAw){XHswPWkcTI = true;}
      if(RTJHXPxNLi == kJVUthTlel){XtBJJfAefF = true;}
      if(GPXBWhaPoM == sTdVGdAZiU){yBKTUVzkii = true;}
      if(nsfwuPYBhr == pIqCornwyB){ncfmoNgCYM = true;}
      while(kJVUthTlel == RTJHXPxNLi){QbsImHAyZy = true;}
      while(sTdVGdAZiU == sTdVGdAZiU){MNFCxrkTAG = true;}
      while(pIqCornwyB == pIqCornwyB){LyHlJrruEp = true;}
      if(hiNOFrrZMB == true){hiNOFrrZMB = false;}
      if(PQeZtcKRYu == true){PQeZtcKRYu = false;}
      if(GMMkecSSfC == true){GMMkecSSfC = false;}
      if(sWmcDKFPPO == true){sWmcDKFPPO = false;}
      if(laMgFYdQIL == true){laMgFYdQIL = false;}
      if(hWXCtUVbjc == true){hWXCtUVbjc = false;}
      if(YYtKIrcBVi == true){YYtKIrcBVi = false;}
      if(XtBJJfAefF == true){XtBJJfAefF = false;}
      if(yBKTUVzkii == true){yBKTUVzkii = false;}
      if(ncfmoNgCYM == true){ncfmoNgCYM = false;}
      if(ucuYnmVNsO == true){ucuYnmVNsO = false;}
      if(UqwddXNZpm == true){UqwddXNZpm = false;}
      if(srSmutOOTw == true){srSmutOOTw = false;}
      if(zxFTJVGkfh == true){zxFTJVGkfh = false;}
      if(zkrTNwgBIR == true){zkrTNwgBIR = false;}
      if(zGMlTDJHds == true){zGMlTDJHds = false;}
      if(XHswPWkcTI == true){XHswPWkcTI = false;}
      if(QbsImHAyZy == true){QbsImHAyZy = false;}
      if(MNFCxrkTAG == true){MNFCxrkTAG = false;}
      if(LyHlJrruEp == true){LyHlJrruEp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GZWBQFXGXU
{ 
  void VFZUoskrAS()
  { 
      bool EWxmLwtAxV = false;
      bool BatGOQsfsq = false;
      bool ONnKirHIwq = false;
      bool frNWxQBndd = false;
      bool BUsCgydDNE = false;
      bool XUCSQphmET = false;
      bool nlEFpIMXJy = false;
      bool PECOotTkcj = false;
      bool NEtrSKpuFG = false;
      bool hNjJoOPmMX = false;
      bool lGtPnTSmcW = false;
      bool VwJTGiqLme = false;
      bool SQRCPBUrZZ = false;
      bool dgYEyGKeDz = false;
      bool rCShjkDPDF = false;
      bool XEAgEUnqzm = false;
      bool yZMDroXFVz = false;
      bool XMInmPyiRe = false;
      bool xFoTCZfqzc = false;
      bool RTfPARpPpu = false;
      string IWfHMUsplA;
      string yqYcawiDJI;
      string dZYHcnCXZr;
      string ZgSsWHylBe;
      string UJPaYOxTlW;
      string BtTwihyYeX;
      string SVQsaQXeFT;
      string xwBenTKxiN;
      string qhkCpeMWKn;
      string JZHcMzsVAH;
      string pSNSYFsoHO;
      string XAoQgjjNDu;
      string EBTRKXoXSo;
      string anwbXXTSdk;
      string lXOwPIjpwb;
      string OeSFCoywIB;
      string PUWSmjENsI;
      string PRjRIgmXCB;
      string mybpZwUpYi;
      string ZXJbURBuJf;
      if(IWfHMUsplA == pSNSYFsoHO){EWxmLwtAxV = true;}
      else if(pSNSYFsoHO == IWfHMUsplA){lGtPnTSmcW = true;}
      if(yqYcawiDJI == XAoQgjjNDu){BatGOQsfsq = true;}
      else if(XAoQgjjNDu == yqYcawiDJI){VwJTGiqLme = true;}
      if(dZYHcnCXZr == EBTRKXoXSo){ONnKirHIwq = true;}
      else if(EBTRKXoXSo == dZYHcnCXZr){SQRCPBUrZZ = true;}
      if(ZgSsWHylBe == anwbXXTSdk){frNWxQBndd = true;}
      else if(anwbXXTSdk == ZgSsWHylBe){dgYEyGKeDz = true;}
      if(UJPaYOxTlW == lXOwPIjpwb){BUsCgydDNE = true;}
      else if(lXOwPIjpwb == UJPaYOxTlW){rCShjkDPDF = true;}
      if(BtTwihyYeX == OeSFCoywIB){XUCSQphmET = true;}
      else if(OeSFCoywIB == BtTwihyYeX){XEAgEUnqzm = true;}
      if(SVQsaQXeFT == PUWSmjENsI){nlEFpIMXJy = true;}
      else if(PUWSmjENsI == SVQsaQXeFT){yZMDroXFVz = true;}
      if(xwBenTKxiN == PRjRIgmXCB){PECOotTkcj = true;}
      if(qhkCpeMWKn == mybpZwUpYi){NEtrSKpuFG = true;}
      if(JZHcMzsVAH == ZXJbURBuJf){hNjJoOPmMX = true;}
      while(PRjRIgmXCB == xwBenTKxiN){XMInmPyiRe = true;}
      while(mybpZwUpYi == mybpZwUpYi){xFoTCZfqzc = true;}
      while(ZXJbURBuJf == ZXJbURBuJf){RTfPARpPpu = true;}
      if(EWxmLwtAxV == true){EWxmLwtAxV = false;}
      if(BatGOQsfsq == true){BatGOQsfsq = false;}
      if(ONnKirHIwq == true){ONnKirHIwq = false;}
      if(frNWxQBndd == true){frNWxQBndd = false;}
      if(BUsCgydDNE == true){BUsCgydDNE = false;}
      if(XUCSQphmET == true){XUCSQphmET = false;}
      if(nlEFpIMXJy == true){nlEFpIMXJy = false;}
      if(PECOotTkcj == true){PECOotTkcj = false;}
      if(NEtrSKpuFG == true){NEtrSKpuFG = false;}
      if(hNjJoOPmMX == true){hNjJoOPmMX = false;}
      if(lGtPnTSmcW == true){lGtPnTSmcW = false;}
      if(VwJTGiqLme == true){VwJTGiqLme = false;}
      if(SQRCPBUrZZ == true){SQRCPBUrZZ = false;}
      if(dgYEyGKeDz == true){dgYEyGKeDz = false;}
      if(rCShjkDPDF == true){rCShjkDPDF = false;}
      if(XEAgEUnqzm == true){XEAgEUnqzm = false;}
      if(yZMDroXFVz == true){yZMDroXFVz = false;}
      if(XMInmPyiRe == true){XMInmPyiRe = false;}
      if(xFoTCZfqzc == true){xFoTCZfqzc = false;}
      if(RTfPARpPpu == true){RTfPARpPpu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UAIGXRKZEN
{ 
  void sCbBUgGeoL()
  { 
      bool NMFnwCnqng = false;
      bool gXepiDFLwe = false;
      bool TIMhEPmhor = false;
      bool GGLhYdGZaF = false;
      bool dlNMOVDYhU = false;
      bool uuegjEAXif = false;
      bool OGBwZaLxQE = false;
      bool xejpBhuzSi = false;
      bool MOAUwLadxU = false;
      bool chqtpXjRln = false;
      bool JGIcWQKofC = false;
      bool IBFzTAFgzO = false;
      bool zgzwbPmpzd = false;
      bool xdNdYGFWyf = false;
      bool AlytLbbqap = false;
      bool RDRWnbGMBH = false;
      bool cUoBFdmaaN = false;
      bool thiSONiEjz = false;
      bool mwOJMtMppx = false;
      bool zsVpCexwog = false;
      string dGJdOCgurp;
      string tEyhaTkSRx;
      string YFebsBrCgm;
      string mBmAIuuMoF;
      string gqNzpzdhUH;
      string kxMklYagkM;
      string KdOEDrRxZe;
      string XXcMQhqflt;
      string WJhZBooBOj;
      string TNbbuCbIwx;
      string gfIoiMUzTD;
      string gutqoAwoCN;
      string CQipLJwARO;
      string FijnMqBspo;
      string UogKCYSjlt;
      string FmFhtQwScZ;
      string PThFxxKGdy;
      string yDyNsNiYmm;
      string pMNWISdBsw;
      string tiPQYBGbME;
      if(dGJdOCgurp == gfIoiMUzTD){NMFnwCnqng = true;}
      else if(gfIoiMUzTD == dGJdOCgurp){JGIcWQKofC = true;}
      if(tEyhaTkSRx == gutqoAwoCN){gXepiDFLwe = true;}
      else if(gutqoAwoCN == tEyhaTkSRx){IBFzTAFgzO = true;}
      if(YFebsBrCgm == CQipLJwARO){TIMhEPmhor = true;}
      else if(CQipLJwARO == YFebsBrCgm){zgzwbPmpzd = true;}
      if(mBmAIuuMoF == FijnMqBspo){GGLhYdGZaF = true;}
      else if(FijnMqBspo == mBmAIuuMoF){xdNdYGFWyf = true;}
      if(gqNzpzdhUH == UogKCYSjlt){dlNMOVDYhU = true;}
      else if(UogKCYSjlt == gqNzpzdhUH){AlytLbbqap = true;}
      if(kxMklYagkM == FmFhtQwScZ){uuegjEAXif = true;}
      else if(FmFhtQwScZ == kxMklYagkM){RDRWnbGMBH = true;}
      if(KdOEDrRxZe == PThFxxKGdy){OGBwZaLxQE = true;}
      else if(PThFxxKGdy == KdOEDrRxZe){cUoBFdmaaN = true;}
      if(XXcMQhqflt == yDyNsNiYmm){xejpBhuzSi = true;}
      if(WJhZBooBOj == pMNWISdBsw){MOAUwLadxU = true;}
      if(TNbbuCbIwx == tiPQYBGbME){chqtpXjRln = true;}
      while(yDyNsNiYmm == XXcMQhqflt){thiSONiEjz = true;}
      while(pMNWISdBsw == pMNWISdBsw){mwOJMtMppx = true;}
      while(tiPQYBGbME == tiPQYBGbME){zsVpCexwog = true;}
      if(NMFnwCnqng == true){NMFnwCnqng = false;}
      if(gXepiDFLwe == true){gXepiDFLwe = false;}
      if(TIMhEPmhor == true){TIMhEPmhor = false;}
      if(GGLhYdGZaF == true){GGLhYdGZaF = false;}
      if(dlNMOVDYhU == true){dlNMOVDYhU = false;}
      if(uuegjEAXif == true){uuegjEAXif = false;}
      if(OGBwZaLxQE == true){OGBwZaLxQE = false;}
      if(xejpBhuzSi == true){xejpBhuzSi = false;}
      if(MOAUwLadxU == true){MOAUwLadxU = false;}
      if(chqtpXjRln == true){chqtpXjRln = false;}
      if(JGIcWQKofC == true){JGIcWQKofC = false;}
      if(IBFzTAFgzO == true){IBFzTAFgzO = false;}
      if(zgzwbPmpzd == true){zgzwbPmpzd = false;}
      if(xdNdYGFWyf == true){xdNdYGFWyf = false;}
      if(AlytLbbqap == true){AlytLbbqap = false;}
      if(RDRWnbGMBH == true){RDRWnbGMBH = false;}
      if(cUoBFdmaaN == true){cUoBFdmaaN = false;}
      if(thiSONiEjz == true){thiSONiEjz = false;}
      if(mwOJMtMppx == true){mwOJMtMppx = false;}
      if(zsVpCexwog == true){zsVpCexwog = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OYNLIBLQSG
{ 
  void DcMUDFUBRP()
  { 
      bool TyNXQgLqQO = false;
      bool ZZhSalhrEP = false;
      bool BsoMwGrsDQ = false;
      bool eoFcEgHejG = false;
      bool OQquhwBpwq = false;
      bool bahATaJAaK = false;
      bool oRnAijUFOs = false;
      bool dCHxBkCteA = false;
      bool EBxLnDGFId = false;
      bool XGDYQwbpLx = false;
      bool bubCMZSkzh = false;
      bool XOVaGmUbLf = false;
      bool dOwjVWyifE = false;
      bool JLhgYJZuyO = false;
      bool jVGaFIkcSd = false;
      bool bzefTMyqgp = false;
      bool ajEtYLfoBw = false;
      bool NZdwuHIVeM = false;
      bool lUPCcJgCMM = false;
      bool KiNInARLBt = false;
      string hnIihNmEnU;
      string KVxdIhjfOl;
      string EWXqhAguwb;
      string ZkSSfokQJr;
      string deCJwMFHGh;
      string eAWXRKQQBg;
      string frIMuYCeyT;
      string xTVVIYUOtU;
      string tZoOwYNtAU;
      string XTPcMlWoNX;
      string KaJmjLdBPs;
      string pCVflFCtQV;
      string KHdcudEsIW;
      string CfAWKTPBdj;
      string uMeHeVxipH;
      string ibXrMCxfrG;
      string HksrpJBzVS;
      string pBQfaybWyY;
      string fUCBnZHIJI;
      string VjJWcJSmQV;
      if(hnIihNmEnU == KaJmjLdBPs){TyNXQgLqQO = true;}
      else if(KaJmjLdBPs == hnIihNmEnU){bubCMZSkzh = true;}
      if(KVxdIhjfOl == pCVflFCtQV){ZZhSalhrEP = true;}
      else if(pCVflFCtQV == KVxdIhjfOl){XOVaGmUbLf = true;}
      if(EWXqhAguwb == KHdcudEsIW){BsoMwGrsDQ = true;}
      else if(KHdcudEsIW == EWXqhAguwb){dOwjVWyifE = true;}
      if(ZkSSfokQJr == CfAWKTPBdj){eoFcEgHejG = true;}
      else if(CfAWKTPBdj == ZkSSfokQJr){JLhgYJZuyO = true;}
      if(deCJwMFHGh == uMeHeVxipH){OQquhwBpwq = true;}
      else if(uMeHeVxipH == deCJwMFHGh){jVGaFIkcSd = true;}
      if(eAWXRKQQBg == ibXrMCxfrG){bahATaJAaK = true;}
      else if(ibXrMCxfrG == eAWXRKQQBg){bzefTMyqgp = true;}
      if(frIMuYCeyT == HksrpJBzVS){oRnAijUFOs = true;}
      else if(HksrpJBzVS == frIMuYCeyT){ajEtYLfoBw = true;}
      if(xTVVIYUOtU == pBQfaybWyY){dCHxBkCteA = true;}
      if(tZoOwYNtAU == fUCBnZHIJI){EBxLnDGFId = true;}
      if(XTPcMlWoNX == VjJWcJSmQV){XGDYQwbpLx = true;}
      while(pBQfaybWyY == xTVVIYUOtU){NZdwuHIVeM = true;}
      while(fUCBnZHIJI == fUCBnZHIJI){lUPCcJgCMM = true;}
      while(VjJWcJSmQV == VjJWcJSmQV){KiNInARLBt = true;}
      if(TyNXQgLqQO == true){TyNXQgLqQO = false;}
      if(ZZhSalhrEP == true){ZZhSalhrEP = false;}
      if(BsoMwGrsDQ == true){BsoMwGrsDQ = false;}
      if(eoFcEgHejG == true){eoFcEgHejG = false;}
      if(OQquhwBpwq == true){OQquhwBpwq = false;}
      if(bahATaJAaK == true){bahATaJAaK = false;}
      if(oRnAijUFOs == true){oRnAijUFOs = false;}
      if(dCHxBkCteA == true){dCHxBkCteA = false;}
      if(EBxLnDGFId == true){EBxLnDGFId = false;}
      if(XGDYQwbpLx == true){XGDYQwbpLx = false;}
      if(bubCMZSkzh == true){bubCMZSkzh = false;}
      if(XOVaGmUbLf == true){XOVaGmUbLf = false;}
      if(dOwjVWyifE == true){dOwjVWyifE = false;}
      if(JLhgYJZuyO == true){JLhgYJZuyO = false;}
      if(jVGaFIkcSd == true){jVGaFIkcSd = false;}
      if(bzefTMyqgp == true){bzefTMyqgp = false;}
      if(ajEtYLfoBw == true){ajEtYLfoBw = false;}
      if(NZdwuHIVeM == true){NZdwuHIVeM = false;}
      if(lUPCcJgCMM == true){lUPCcJgCMM = false;}
      if(KiNInARLBt == true){KiNInARLBt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDOEHPUDJM
{ 
  void DzeyuTTGIT()
  { 
      bool rfsfMNQZQR = false;
      bool JiobuUJzur = false;
      bool auFLzIenKI = false;
      bool kdIIVDkAUg = false;
      bool HtdDlaoDNs = false;
      bool wtFaZwagfD = false;
      bool ibPHgfagFq = false;
      bool iJeNkgRCYY = false;
      bool TbZQMqYghY = false;
      bool cDTQyedVWG = false;
      bool AHyWJlOrps = false;
      bool eXHHiGByuo = false;
      bool GtyfOeoNOF = false;
      bool CufSXLdDHa = false;
      bool bfqnsEwMgq = false;
      bool cfagzGJRHd = false;
      bool wAckqjroiX = false;
      bool cyqUNZCJlJ = false;
      bool icgWbWTyTR = false;
      bool CLucdaCGxJ = false;
      string iHZamOnVWh;
      string mOeBfHIlMV;
      string jQaLjONxZs;
      string OunefgOjtQ;
      string uwMKrmWcmO;
      string CFIkqSgNqX;
      string ApwcTqZzUy;
      string rXrwZmDQTx;
      string rkKKqIlDnM;
      string ABsVPEAjpB;
      string MWHnVdMMLD;
      string PQssfPflkK;
      string EWLHyqeWfU;
      string mSZSkVcVnN;
      string wZqjxiHApz;
      string YOyewoKzpe;
      string zpfqQwpaHK;
      string mKxXOeebKO;
      string jdfguXUtVw;
      string KdeJNFsATB;
      if(iHZamOnVWh == MWHnVdMMLD){rfsfMNQZQR = true;}
      else if(MWHnVdMMLD == iHZamOnVWh){AHyWJlOrps = true;}
      if(mOeBfHIlMV == PQssfPflkK){JiobuUJzur = true;}
      else if(PQssfPflkK == mOeBfHIlMV){eXHHiGByuo = true;}
      if(jQaLjONxZs == EWLHyqeWfU){auFLzIenKI = true;}
      else if(EWLHyqeWfU == jQaLjONxZs){GtyfOeoNOF = true;}
      if(OunefgOjtQ == mSZSkVcVnN){kdIIVDkAUg = true;}
      else if(mSZSkVcVnN == OunefgOjtQ){CufSXLdDHa = true;}
      if(uwMKrmWcmO == wZqjxiHApz){HtdDlaoDNs = true;}
      else if(wZqjxiHApz == uwMKrmWcmO){bfqnsEwMgq = true;}
      if(CFIkqSgNqX == YOyewoKzpe){wtFaZwagfD = true;}
      else if(YOyewoKzpe == CFIkqSgNqX){cfagzGJRHd = true;}
      if(ApwcTqZzUy == zpfqQwpaHK){ibPHgfagFq = true;}
      else if(zpfqQwpaHK == ApwcTqZzUy){wAckqjroiX = true;}
      if(rXrwZmDQTx == mKxXOeebKO){iJeNkgRCYY = true;}
      if(rkKKqIlDnM == jdfguXUtVw){TbZQMqYghY = true;}
      if(ABsVPEAjpB == KdeJNFsATB){cDTQyedVWG = true;}
      while(mKxXOeebKO == rXrwZmDQTx){cyqUNZCJlJ = true;}
      while(jdfguXUtVw == jdfguXUtVw){icgWbWTyTR = true;}
      while(KdeJNFsATB == KdeJNFsATB){CLucdaCGxJ = true;}
      if(rfsfMNQZQR == true){rfsfMNQZQR = false;}
      if(JiobuUJzur == true){JiobuUJzur = false;}
      if(auFLzIenKI == true){auFLzIenKI = false;}
      if(kdIIVDkAUg == true){kdIIVDkAUg = false;}
      if(HtdDlaoDNs == true){HtdDlaoDNs = false;}
      if(wtFaZwagfD == true){wtFaZwagfD = false;}
      if(ibPHgfagFq == true){ibPHgfagFq = false;}
      if(iJeNkgRCYY == true){iJeNkgRCYY = false;}
      if(TbZQMqYghY == true){TbZQMqYghY = false;}
      if(cDTQyedVWG == true){cDTQyedVWG = false;}
      if(AHyWJlOrps == true){AHyWJlOrps = false;}
      if(eXHHiGByuo == true){eXHHiGByuo = false;}
      if(GtyfOeoNOF == true){GtyfOeoNOF = false;}
      if(CufSXLdDHa == true){CufSXLdDHa = false;}
      if(bfqnsEwMgq == true){bfqnsEwMgq = false;}
      if(cfagzGJRHd == true){cfagzGJRHd = false;}
      if(wAckqjroiX == true){wAckqjroiX = false;}
      if(cyqUNZCJlJ == true){cyqUNZCJlJ = false;}
      if(icgWbWTyTR == true){icgWbWTyTR = false;}
      if(CLucdaCGxJ == true){CLucdaCGxJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELEQQRBLDY
{ 
  void BwEzdZMMAa()
  { 
      bool ipYlnXtxAG = false;
      bool bauHYgBHdT = false;
      bool YtfpypaZfO = false;
      bool aQlCLLEucJ = false;
      bool ECVlqaEpAe = false;
      bool jXuhBoKhnx = false;
      bool wURkfLosuN = false;
      bool bFeUOWYszW = false;
      bool kkZBeCVEAW = false;
      bool BWHeMjkjFf = false;
      bool lLtmCesaSd = false;
      bool PQiQMLtPGd = false;
      bool okrYLFxzHd = false;
      bool lnnSjZpmyz = false;
      bool IukVGkmpSB = false;
      bool pUdbqBSVaw = false;
      bool gsSnrbcQfl = false;
      bool UHRHVtzVRa = false;
      bool RHgGnRKLai = false;
      bool HULCRObwde = false;
      string DqwKWAQwNr;
      string VciFIPFpZJ;
      string kzImeLMlzI;
      string zkYoRWDMQh;
      string EsHOIyTnjE;
      string PcMxFEhJeK;
      string mdwFrjDsnk;
      string LsZqFqqtdg;
      string rXBtrWYbjM;
      string otgFtZxCVX;
      string tZzzsWCUqN;
      string NnexSPbBNU;
      string KaJbwRMTwf;
      string tnXGmSYCBV;
      string TEkVzAOile;
      string yuoBNSPXDb;
      string JiYLTYQYKA;
      string qZAqAGpnbu;
      string CcgQgzzVsT;
      string CAyZLkfYBZ;
      if(DqwKWAQwNr == tZzzsWCUqN){ipYlnXtxAG = true;}
      else if(tZzzsWCUqN == DqwKWAQwNr){lLtmCesaSd = true;}
      if(VciFIPFpZJ == NnexSPbBNU){bauHYgBHdT = true;}
      else if(NnexSPbBNU == VciFIPFpZJ){PQiQMLtPGd = true;}
      if(kzImeLMlzI == KaJbwRMTwf){YtfpypaZfO = true;}
      else if(KaJbwRMTwf == kzImeLMlzI){okrYLFxzHd = true;}
      if(zkYoRWDMQh == tnXGmSYCBV){aQlCLLEucJ = true;}
      else if(tnXGmSYCBV == zkYoRWDMQh){lnnSjZpmyz = true;}
      if(EsHOIyTnjE == TEkVzAOile){ECVlqaEpAe = true;}
      else if(TEkVzAOile == EsHOIyTnjE){IukVGkmpSB = true;}
      if(PcMxFEhJeK == yuoBNSPXDb){jXuhBoKhnx = true;}
      else if(yuoBNSPXDb == PcMxFEhJeK){pUdbqBSVaw = true;}
      if(mdwFrjDsnk == JiYLTYQYKA){wURkfLosuN = true;}
      else if(JiYLTYQYKA == mdwFrjDsnk){gsSnrbcQfl = true;}
      if(LsZqFqqtdg == qZAqAGpnbu){bFeUOWYszW = true;}
      if(rXBtrWYbjM == CcgQgzzVsT){kkZBeCVEAW = true;}
      if(otgFtZxCVX == CAyZLkfYBZ){BWHeMjkjFf = true;}
      while(qZAqAGpnbu == LsZqFqqtdg){UHRHVtzVRa = true;}
      while(CcgQgzzVsT == CcgQgzzVsT){RHgGnRKLai = true;}
      while(CAyZLkfYBZ == CAyZLkfYBZ){HULCRObwde = true;}
      if(ipYlnXtxAG == true){ipYlnXtxAG = false;}
      if(bauHYgBHdT == true){bauHYgBHdT = false;}
      if(YtfpypaZfO == true){YtfpypaZfO = false;}
      if(aQlCLLEucJ == true){aQlCLLEucJ = false;}
      if(ECVlqaEpAe == true){ECVlqaEpAe = false;}
      if(jXuhBoKhnx == true){jXuhBoKhnx = false;}
      if(wURkfLosuN == true){wURkfLosuN = false;}
      if(bFeUOWYszW == true){bFeUOWYszW = false;}
      if(kkZBeCVEAW == true){kkZBeCVEAW = false;}
      if(BWHeMjkjFf == true){BWHeMjkjFf = false;}
      if(lLtmCesaSd == true){lLtmCesaSd = false;}
      if(PQiQMLtPGd == true){PQiQMLtPGd = false;}
      if(okrYLFxzHd == true){okrYLFxzHd = false;}
      if(lnnSjZpmyz == true){lnnSjZpmyz = false;}
      if(IukVGkmpSB == true){IukVGkmpSB = false;}
      if(pUdbqBSVaw == true){pUdbqBSVaw = false;}
      if(gsSnrbcQfl == true){gsSnrbcQfl = false;}
      if(UHRHVtzVRa == true){UHRHVtzVRa = false;}
      if(RHgGnRKLai == true){RHgGnRKLai = false;}
      if(HULCRObwde == true){HULCRObwde = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PTSFGKQSYP
{ 
  void ubKKiCQESJ()
  { 
      bool QGzmigKHBs = false;
      bool mRSBphhsVd = false;
      bool CghohdIuNM = false;
      bool LyuXkIlPEf = false;
      bool CIRjHiPXaT = false;
      bool ecliEiXJFF = false;
      bool XPtnhnWtQg = false;
      bool wSoobtPygy = false;
      bool NkTsghMLTB = false;
      bool jbKzIlNcCT = false;
      bool MUHtWMnwHK = false;
      bool TZbGqluBGz = false;
      bool bKaOwTHpgo = false;
      bool fluNlsdZVU = false;
      bool tPEJgJAEIV = false;
      bool pMWCqBtrxD = false;
      bool FyPRdhdNTx = false;
      bool IVelFLGRgl = false;
      bool TChKzTPsWk = false;
      bool zkcSPwAmez = false;
      string EicVSABTUa;
      string NRtSfxkSpl;
      string uBpoTsWsXZ;
      string kHRBhDaJIR;
      string hDErTpemwL;
      string PXnPUCrnCZ;
      string cHuuoFzsjb;
      string WbKXDrwyUd;
      string NjwMJNTCge;
      string KmHioaHJDO;
      string plCTonNPLb;
      string FtSXLsKila;
      string lxMERiTaic;
      string kmtGnbgbWV;
      string ADqEYPTiXu;
      string PXXbbsZyCF;
      string TlgiqSzMjj;
      string MiMPahFHeB;
      string PkDmMNPSdt;
      string BhZQCNWHMG;
      if(EicVSABTUa == plCTonNPLb){QGzmigKHBs = true;}
      else if(plCTonNPLb == EicVSABTUa){MUHtWMnwHK = true;}
      if(NRtSfxkSpl == FtSXLsKila){mRSBphhsVd = true;}
      else if(FtSXLsKila == NRtSfxkSpl){TZbGqluBGz = true;}
      if(uBpoTsWsXZ == lxMERiTaic){CghohdIuNM = true;}
      else if(lxMERiTaic == uBpoTsWsXZ){bKaOwTHpgo = true;}
      if(kHRBhDaJIR == kmtGnbgbWV){LyuXkIlPEf = true;}
      else if(kmtGnbgbWV == kHRBhDaJIR){fluNlsdZVU = true;}
      if(hDErTpemwL == ADqEYPTiXu){CIRjHiPXaT = true;}
      else if(ADqEYPTiXu == hDErTpemwL){tPEJgJAEIV = true;}
      if(PXnPUCrnCZ == PXXbbsZyCF){ecliEiXJFF = true;}
      else if(PXXbbsZyCF == PXnPUCrnCZ){pMWCqBtrxD = true;}
      if(cHuuoFzsjb == TlgiqSzMjj){XPtnhnWtQg = true;}
      else if(TlgiqSzMjj == cHuuoFzsjb){FyPRdhdNTx = true;}
      if(WbKXDrwyUd == MiMPahFHeB){wSoobtPygy = true;}
      if(NjwMJNTCge == PkDmMNPSdt){NkTsghMLTB = true;}
      if(KmHioaHJDO == BhZQCNWHMG){jbKzIlNcCT = true;}
      while(MiMPahFHeB == WbKXDrwyUd){IVelFLGRgl = true;}
      while(PkDmMNPSdt == PkDmMNPSdt){TChKzTPsWk = true;}
      while(BhZQCNWHMG == BhZQCNWHMG){zkcSPwAmez = true;}
      if(QGzmigKHBs == true){QGzmigKHBs = false;}
      if(mRSBphhsVd == true){mRSBphhsVd = false;}
      if(CghohdIuNM == true){CghohdIuNM = false;}
      if(LyuXkIlPEf == true){LyuXkIlPEf = false;}
      if(CIRjHiPXaT == true){CIRjHiPXaT = false;}
      if(ecliEiXJFF == true){ecliEiXJFF = false;}
      if(XPtnhnWtQg == true){XPtnhnWtQg = false;}
      if(wSoobtPygy == true){wSoobtPygy = false;}
      if(NkTsghMLTB == true){NkTsghMLTB = false;}
      if(jbKzIlNcCT == true){jbKzIlNcCT = false;}
      if(MUHtWMnwHK == true){MUHtWMnwHK = false;}
      if(TZbGqluBGz == true){TZbGqluBGz = false;}
      if(bKaOwTHpgo == true){bKaOwTHpgo = false;}
      if(fluNlsdZVU == true){fluNlsdZVU = false;}
      if(tPEJgJAEIV == true){tPEJgJAEIV = false;}
      if(pMWCqBtrxD == true){pMWCqBtrxD = false;}
      if(FyPRdhdNTx == true){FyPRdhdNTx = false;}
      if(IVelFLGRgl == true){IVelFLGRgl = false;}
      if(TChKzTPsWk == true){TChKzTPsWk = false;}
      if(zkcSPwAmez == true){zkcSPwAmez = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UEUDEBGBVG
{ 
  void lzKLJIShNR()
  { 
      bool KLEQPTnwhx = false;
      bool dFhHkVZDFu = false;
      bool DdyRtxZGkm = false;
      bool ffRmExkVbW = false;
      bool dYzgPjaCWG = false;
      bool hPWZwfNmVS = false;
      bool shKtQxntDm = false;
      bool jDaiReeQBJ = false;
      bool WXjeFQJqqX = false;
      bool iyzJcuNEQS = false;
      bool wfziVdomIR = false;
      bool BxlMwVxenA = false;
      bool mwDeElERGV = false;
      bool QZAhNpXBJa = false;
      bool aWiYWlMmMH = false;
      bool yhQQezcTdi = false;
      bool ZWglAaxDyF = false;
      bool xwVNYQNdIR = false;
      bool ZQEyXhJiDN = false;
      bool MEWZBDoxYu = false;
      string AKZFjoZkoR;
      string mPjQsXNDXn;
      string RGjjNMqVaj;
      string fATrYRhzsE;
      string YcQfxOKbih;
      string eKcFXtZpqW;
      string yDJFllurrb;
      string oNJTPnpElz;
      string COmsEUXOTd;
      string qrHVFUSKtL;
      string SRjGrRAJpi;
      string EVDrUjQPAQ;
      string OgXNkxFnNt;
      string VeKafjdfBm;
      string UOXjZVnPBV;
      string EDJcwltVVt;
      string LMuwNYKbLj;
      string FjONuzInnO;
      string JplrpSUgdt;
      string pIJHbISbVA;
      if(AKZFjoZkoR == SRjGrRAJpi){KLEQPTnwhx = true;}
      else if(SRjGrRAJpi == AKZFjoZkoR){wfziVdomIR = true;}
      if(mPjQsXNDXn == EVDrUjQPAQ){dFhHkVZDFu = true;}
      else if(EVDrUjQPAQ == mPjQsXNDXn){BxlMwVxenA = true;}
      if(RGjjNMqVaj == OgXNkxFnNt){DdyRtxZGkm = true;}
      else if(OgXNkxFnNt == RGjjNMqVaj){mwDeElERGV = true;}
      if(fATrYRhzsE == VeKafjdfBm){ffRmExkVbW = true;}
      else if(VeKafjdfBm == fATrYRhzsE){QZAhNpXBJa = true;}
      if(YcQfxOKbih == UOXjZVnPBV){dYzgPjaCWG = true;}
      else if(UOXjZVnPBV == YcQfxOKbih){aWiYWlMmMH = true;}
      if(eKcFXtZpqW == EDJcwltVVt){hPWZwfNmVS = true;}
      else if(EDJcwltVVt == eKcFXtZpqW){yhQQezcTdi = true;}
      if(yDJFllurrb == LMuwNYKbLj){shKtQxntDm = true;}
      else if(LMuwNYKbLj == yDJFllurrb){ZWglAaxDyF = true;}
      if(oNJTPnpElz == FjONuzInnO){jDaiReeQBJ = true;}
      if(COmsEUXOTd == JplrpSUgdt){WXjeFQJqqX = true;}
      if(qrHVFUSKtL == pIJHbISbVA){iyzJcuNEQS = true;}
      while(FjONuzInnO == oNJTPnpElz){xwVNYQNdIR = true;}
      while(JplrpSUgdt == JplrpSUgdt){ZQEyXhJiDN = true;}
      while(pIJHbISbVA == pIJHbISbVA){MEWZBDoxYu = true;}
      if(KLEQPTnwhx == true){KLEQPTnwhx = false;}
      if(dFhHkVZDFu == true){dFhHkVZDFu = false;}
      if(DdyRtxZGkm == true){DdyRtxZGkm = false;}
      if(ffRmExkVbW == true){ffRmExkVbW = false;}
      if(dYzgPjaCWG == true){dYzgPjaCWG = false;}
      if(hPWZwfNmVS == true){hPWZwfNmVS = false;}
      if(shKtQxntDm == true){shKtQxntDm = false;}
      if(jDaiReeQBJ == true){jDaiReeQBJ = false;}
      if(WXjeFQJqqX == true){WXjeFQJqqX = false;}
      if(iyzJcuNEQS == true){iyzJcuNEQS = false;}
      if(wfziVdomIR == true){wfziVdomIR = false;}
      if(BxlMwVxenA == true){BxlMwVxenA = false;}
      if(mwDeElERGV == true){mwDeElERGV = false;}
      if(QZAhNpXBJa == true){QZAhNpXBJa = false;}
      if(aWiYWlMmMH == true){aWiYWlMmMH = false;}
      if(yhQQezcTdi == true){yhQQezcTdi = false;}
      if(ZWglAaxDyF == true){ZWglAaxDyF = false;}
      if(xwVNYQNdIR == true){xwVNYQNdIR = false;}
      if(ZQEyXhJiDN == true){ZQEyXhJiDN = false;}
      if(MEWZBDoxYu == true){MEWZBDoxYu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QNYOUHOYUX
{ 
  void JgIyEhSnFF()
  { 
      bool bpJxyfAOEk = false;
      bool REdBqBUjBj = false;
      bool rkqokjAnKX = false;
      bool ObMKQFTLrL = false;
      bool DhsSLGLqOo = false;
      bool uzqKcqyTMO = false;
      bool fMDfVpqSkk = false;
      bool gJrpfKqXcd = false;
      bool XIZVcPjCgY = false;
      bool GAzdfqeMwV = false;
      bool PrGcHkHBeS = false;
      bool zZphpWmhDG = false;
      bool FnlLefKNKo = false;
      bool eebHNeCxNq = false;
      bool HiWNZfJQmI = false;
      bool ExIoQaFtxa = false;
      bool asppmUyiTK = false;
      bool TpTLzVRYlz = false;
      bool WsZBjhVlqm = false;
      bool ZHzlQNsgZE = false;
      string FxBPpecYpa;
      string EczNQnjTdf;
      string BIEjPuFRdN;
      string SwXkJcmOGU;
      string NYMkBBSFjT;
      string HrxbPxsRzu;
      string YLtbIHFODm;
      string BVMJRcwShO;
      string bAhJGZywVM;
      string jUOLuCdjbs;
      string wEBwSlenJl;
      string BZjkSXdjVi;
      string JIrqCfGBNP;
      string yLqnRWzkqU;
      string tKmiLKkcrW;
      string XsOsjnMJsl;
      string edZsnohuTu;
      string YrsAnyVIfr;
      string udIpqEwxEd;
      string KorFpQjsuV;
      if(FxBPpecYpa == wEBwSlenJl){bpJxyfAOEk = true;}
      else if(wEBwSlenJl == FxBPpecYpa){PrGcHkHBeS = true;}
      if(EczNQnjTdf == BZjkSXdjVi){REdBqBUjBj = true;}
      else if(BZjkSXdjVi == EczNQnjTdf){zZphpWmhDG = true;}
      if(BIEjPuFRdN == JIrqCfGBNP){rkqokjAnKX = true;}
      else if(JIrqCfGBNP == BIEjPuFRdN){FnlLefKNKo = true;}
      if(SwXkJcmOGU == yLqnRWzkqU){ObMKQFTLrL = true;}
      else if(yLqnRWzkqU == SwXkJcmOGU){eebHNeCxNq = true;}
      if(NYMkBBSFjT == tKmiLKkcrW){DhsSLGLqOo = true;}
      else if(tKmiLKkcrW == NYMkBBSFjT){HiWNZfJQmI = true;}
      if(HrxbPxsRzu == XsOsjnMJsl){uzqKcqyTMO = true;}
      else if(XsOsjnMJsl == HrxbPxsRzu){ExIoQaFtxa = true;}
      if(YLtbIHFODm == edZsnohuTu){fMDfVpqSkk = true;}
      else if(edZsnohuTu == YLtbIHFODm){asppmUyiTK = true;}
      if(BVMJRcwShO == YrsAnyVIfr){gJrpfKqXcd = true;}
      if(bAhJGZywVM == udIpqEwxEd){XIZVcPjCgY = true;}
      if(jUOLuCdjbs == KorFpQjsuV){GAzdfqeMwV = true;}
      while(YrsAnyVIfr == BVMJRcwShO){TpTLzVRYlz = true;}
      while(udIpqEwxEd == udIpqEwxEd){WsZBjhVlqm = true;}
      while(KorFpQjsuV == KorFpQjsuV){ZHzlQNsgZE = true;}
      if(bpJxyfAOEk == true){bpJxyfAOEk = false;}
      if(REdBqBUjBj == true){REdBqBUjBj = false;}
      if(rkqokjAnKX == true){rkqokjAnKX = false;}
      if(ObMKQFTLrL == true){ObMKQFTLrL = false;}
      if(DhsSLGLqOo == true){DhsSLGLqOo = false;}
      if(uzqKcqyTMO == true){uzqKcqyTMO = false;}
      if(fMDfVpqSkk == true){fMDfVpqSkk = false;}
      if(gJrpfKqXcd == true){gJrpfKqXcd = false;}
      if(XIZVcPjCgY == true){XIZVcPjCgY = false;}
      if(GAzdfqeMwV == true){GAzdfqeMwV = false;}
      if(PrGcHkHBeS == true){PrGcHkHBeS = false;}
      if(zZphpWmhDG == true){zZphpWmhDG = false;}
      if(FnlLefKNKo == true){FnlLefKNKo = false;}
      if(eebHNeCxNq == true){eebHNeCxNq = false;}
      if(HiWNZfJQmI == true){HiWNZfJQmI = false;}
      if(ExIoQaFtxa == true){ExIoQaFtxa = false;}
      if(asppmUyiTK == true){asppmUyiTK = false;}
      if(TpTLzVRYlz == true){TpTLzVRYlz = false;}
      if(WsZBjhVlqm == true){WsZBjhVlqm = false;}
      if(ZHzlQNsgZE == true){ZHzlQNsgZE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ARIWWRLNFA
{ 
  void dAYCYcCRTk()
  { 
      bool hTQeRufubM = false;
      bool KFwoizJgwS = false;
      bool PuSVTYEPaC = false;
      bool XplamlQEUt = false;
      bool lAptUhWLNI = false;
      bool mzIKnmAtLr = false;
      bool pPTZnUSUBx = false;
      bool iFMBfPEYAl = false;
      bool BsCSOYgbmA = false;
      bool kVsbEWfQFA = false;
      bool OCJPYhmGdY = false;
      bool hbtZqxNBKP = false;
      bool mqgBLNMkxJ = false;
      bool inSAWziltf = false;
      bool kaxNSJbTkG = false;
      bool IeFpMXUHEL = false;
      bool VCIUptIsCq = false;
      bool NaHdeLtTiB = false;
      bool lszqAEhcmy = false;
      bool eahiKiRcXX = false;
      string noflLsypAs;
      string hFuOtmZAog;
      string WZWjWpnqOG;
      string xQBIQWqUYz;
      string YTwMntjVBl;
      string kqDjyORwPV;
      string EGbswRDmyX;
      string uEaoHCcKwb;
      string FSocVGMRJB;
      string EuFDuRrCQW;
      string qxXdpfPNbu;
      string lHAmPlRzXo;
      string EkcwSAzWtp;
      string KZsZkItLlo;
      string pzpNPwtRmI;
      string ArdaRFUbKo;
      string gsSkkLOaBH;
      string qFMizEtOfV;
      string FgiloRuSHf;
      string nSAxHxgEcE;
      if(noflLsypAs == qxXdpfPNbu){hTQeRufubM = true;}
      else if(qxXdpfPNbu == noflLsypAs){OCJPYhmGdY = true;}
      if(hFuOtmZAog == lHAmPlRzXo){KFwoizJgwS = true;}
      else if(lHAmPlRzXo == hFuOtmZAog){hbtZqxNBKP = true;}
      if(WZWjWpnqOG == EkcwSAzWtp){PuSVTYEPaC = true;}
      else if(EkcwSAzWtp == WZWjWpnqOG){mqgBLNMkxJ = true;}
      if(xQBIQWqUYz == KZsZkItLlo){XplamlQEUt = true;}
      else if(KZsZkItLlo == xQBIQWqUYz){inSAWziltf = true;}
      if(YTwMntjVBl == pzpNPwtRmI){lAptUhWLNI = true;}
      else if(pzpNPwtRmI == YTwMntjVBl){kaxNSJbTkG = true;}
      if(kqDjyORwPV == ArdaRFUbKo){mzIKnmAtLr = true;}
      else if(ArdaRFUbKo == kqDjyORwPV){IeFpMXUHEL = true;}
      if(EGbswRDmyX == gsSkkLOaBH){pPTZnUSUBx = true;}
      else if(gsSkkLOaBH == EGbswRDmyX){VCIUptIsCq = true;}
      if(uEaoHCcKwb == qFMizEtOfV){iFMBfPEYAl = true;}
      if(FSocVGMRJB == FgiloRuSHf){BsCSOYgbmA = true;}
      if(EuFDuRrCQW == nSAxHxgEcE){kVsbEWfQFA = true;}
      while(qFMizEtOfV == uEaoHCcKwb){NaHdeLtTiB = true;}
      while(FgiloRuSHf == FgiloRuSHf){lszqAEhcmy = true;}
      while(nSAxHxgEcE == nSAxHxgEcE){eahiKiRcXX = true;}
      if(hTQeRufubM == true){hTQeRufubM = false;}
      if(KFwoizJgwS == true){KFwoizJgwS = false;}
      if(PuSVTYEPaC == true){PuSVTYEPaC = false;}
      if(XplamlQEUt == true){XplamlQEUt = false;}
      if(lAptUhWLNI == true){lAptUhWLNI = false;}
      if(mzIKnmAtLr == true){mzIKnmAtLr = false;}
      if(pPTZnUSUBx == true){pPTZnUSUBx = false;}
      if(iFMBfPEYAl == true){iFMBfPEYAl = false;}
      if(BsCSOYgbmA == true){BsCSOYgbmA = false;}
      if(kVsbEWfQFA == true){kVsbEWfQFA = false;}
      if(OCJPYhmGdY == true){OCJPYhmGdY = false;}
      if(hbtZqxNBKP == true){hbtZqxNBKP = false;}
      if(mqgBLNMkxJ == true){mqgBLNMkxJ = false;}
      if(inSAWziltf == true){inSAWziltf = false;}
      if(kaxNSJbTkG == true){kaxNSJbTkG = false;}
      if(IeFpMXUHEL == true){IeFpMXUHEL = false;}
      if(VCIUptIsCq == true){VCIUptIsCq = false;}
      if(NaHdeLtTiB == true){NaHdeLtTiB = false;}
      if(lszqAEhcmy == true){lszqAEhcmy = false;}
      if(eahiKiRcXX == true){eahiKiRcXX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WIKURMGAIO
{ 
  void FVZXnFtrVG()
  { 
      bool VMgzHOMntz = false;
      bool OwMGloVjRc = false;
      bool MCKpSkwFQb = false;
      bool CBdBwyMbZt = false;
      bool QzcgOIKNTY = false;
      bool aKTzrSBqgV = false;
      bool SGWRwNSLJm = false;
      bool ctKXMMZcaJ = false;
      bool ahkqBqhdIc = false;
      bool xVuDaJbLjB = false;
      bool pyDfwfAwme = false;
      bool sXPWukUePF = false;
      bool enDgpGzGwC = false;
      bool kOsYSbdEuU = false;
      bool qlqcjYGXIp = false;
      bool nwueWCuWpo = false;
      bool gszjteepDS = false;
      bool GPjuNswZxR = false;
      bool AayGOnTOCQ = false;
      bool fGOGnylGhF = false;
      string PWmDRpkDUx;
      string ACfoiPrsBN;
      string XHahQgUtSM;
      string nKYxTIcqpk;
      string hcEwxgcANA;
      string hyfwEIuFlk;
      string UqjIJociVa;
      string mBDPfuCdkj;
      string DUfSeodcrK;
      string MXEEQprwmH;
      string DtdmMfuQPJ;
      string FQTCgzKRcT;
      string KApKNOwyyo;
      string DFqcgJpsFy;
      string tNMiEuDCWQ;
      string fZSTwCDSYy;
      string jxRaGzZqUX;
      string JQMeZxmHGR;
      string LtahIcmWfd;
      string FXUGOxulcF;
      if(PWmDRpkDUx == DtdmMfuQPJ){VMgzHOMntz = true;}
      else if(DtdmMfuQPJ == PWmDRpkDUx){pyDfwfAwme = true;}
      if(ACfoiPrsBN == FQTCgzKRcT){OwMGloVjRc = true;}
      else if(FQTCgzKRcT == ACfoiPrsBN){sXPWukUePF = true;}
      if(XHahQgUtSM == KApKNOwyyo){MCKpSkwFQb = true;}
      else if(KApKNOwyyo == XHahQgUtSM){enDgpGzGwC = true;}
      if(nKYxTIcqpk == DFqcgJpsFy){CBdBwyMbZt = true;}
      else if(DFqcgJpsFy == nKYxTIcqpk){kOsYSbdEuU = true;}
      if(hcEwxgcANA == tNMiEuDCWQ){QzcgOIKNTY = true;}
      else if(tNMiEuDCWQ == hcEwxgcANA){qlqcjYGXIp = true;}
      if(hyfwEIuFlk == fZSTwCDSYy){aKTzrSBqgV = true;}
      else if(fZSTwCDSYy == hyfwEIuFlk){nwueWCuWpo = true;}
      if(UqjIJociVa == jxRaGzZqUX){SGWRwNSLJm = true;}
      else if(jxRaGzZqUX == UqjIJociVa){gszjteepDS = true;}
      if(mBDPfuCdkj == JQMeZxmHGR){ctKXMMZcaJ = true;}
      if(DUfSeodcrK == LtahIcmWfd){ahkqBqhdIc = true;}
      if(MXEEQprwmH == FXUGOxulcF){xVuDaJbLjB = true;}
      while(JQMeZxmHGR == mBDPfuCdkj){GPjuNswZxR = true;}
      while(LtahIcmWfd == LtahIcmWfd){AayGOnTOCQ = true;}
      while(FXUGOxulcF == FXUGOxulcF){fGOGnylGhF = true;}
      if(VMgzHOMntz == true){VMgzHOMntz = false;}
      if(OwMGloVjRc == true){OwMGloVjRc = false;}
      if(MCKpSkwFQb == true){MCKpSkwFQb = false;}
      if(CBdBwyMbZt == true){CBdBwyMbZt = false;}
      if(QzcgOIKNTY == true){QzcgOIKNTY = false;}
      if(aKTzrSBqgV == true){aKTzrSBqgV = false;}
      if(SGWRwNSLJm == true){SGWRwNSLJm = false;}
      if(ctKXMMZcaJ == true){ctKXMMZcaJ = false;}
      if(ahkqBqhdIc == true){ahkqBqhdIc = false;}
      if(xVuDaJbLjB == true){xVuDaJbLjB = false;}
      if(pyDfwfAwme == true){pyDfwfAwme = false;}
      if(sXPWukUePF == true){sXPWukUePF = false;}
      if(enDgpGzGwC == true){enDgpGzGwC = false;}
      if(kOsYSbdEuU == true){kOsYSbdEuU = false;}
      if(qlqcjYGXIp == true){qlqcjYGXIp = false;}
      if(nwueWCuWpo == true){nwueWCuWpo = false;}
      if(gszjteepDS == true){gszjteepDS = false;}
      if(GPjuNswZxR == true){GPjuNswZxR = false;}
      if(AayGOnTOCQ == true){AayGOnTOCQ = false;}
      if(fGOGnylGhF == true){fGOGnylGhF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MEPGBBIJXH
{ 
  void ghNlASwLrS()
  { 
      bool PNMnStFdOj = false;
      bool RwDdSzzQmh = false;
      bool GSrKeglWez = false;
      bool fdXePmtnNJ = false;
      bool PsJuMYCoBs = false;
      bool OizPmxUCIl = false;
      bool HizODnXYNf = false;
      bool ELCdRNIwyG = false;
      bool dxUljxeIqS = false;
      bool RqeaCfturX = false;
      bool AdaVnDfVxZ = false;
      bool oYECHKONdG = false;
      bool JOguNNfbak = false;
      bool TNEZFAVzxg = false;
      bool QIKRcrmbTr = false;
      bool RfQkOkxfHa = false;
      bool WEtMGbTdxH = false;
      bool oOPwpAEORU = false;
      bool ZEHiTmwSKT = false;
      bool DoqWKLOyLB = false;
      string zSHgVjWTOy;
      string meiEFLEbOi;
      string uywwoJHKth;
      string NcJodURtlC;
      string uBCQFzhAiz;
      string XgwiRAWLqM;
      string bLYfkKUtak;
      string sKoMntwfqp;
      string aHbtKggZXc;
      string xGCZZjbWet;
      string dnZxGNqiuW;
      string EqUBlUjeUD;
      string duWxmmHPlD;
      string SZAwMlhdnx;
      string pxdBYGlBmF;
      string zxBbQhRbKT;
      string FbxqDepXnz;
      string lFqWNfQVYf;
      string AGbfDVXXfd;
      string UFTTrOAmxt;
      if(zSHgVjWTOy == dnZxGNqiuW){PNMnStFdOj = true;}
      else if(dnZxGNqiuW == zSHgVjWTOy){AdaVnDfVxZ = true;}
      if(meiEFLEbOi == EqUBlUjeUD){RwDdSzzQmh = true;}
      else if(EqUBlUjeUD == meiEFLEbOi){oYECHKONdG = true;}
      if(uywwoJHKth == duWxmmHPlD){GSrKeglWez = true;}
      else if(duWxmmHPlD == uywwoJHKth){JOguNNfbak = true;}
      if(NcJodURtlC == SZAwMlhdnx){fdXePmtnNJ = true;}
      else if(SZAwMlhdnx == NcJodURtlC){TNEZFAVzxg = true;}
      if(uBCQFzhAiz == pxdBYGlBmF){PsJuMYCoBs = true;}
      else if(pxdBYGlBmF == uBCQFzhAiz){QIKRcrmbTr = true;}
      if(XgwiRAWLqM == zxBbQhRbKT){OizPmxUCIl = true;}
      else if(zxBbQhRbKT == XgwiRAWLqM){RfQkOkxfHa = true;}
      if(bLYfkKUtak == FbxqDepXnz){HizODnXYNf = true;}
      else if(FbxqDepXnz == bLYfkKUtak){WEtMGbTdxH = true;}
      if(sKoMntwfqp == lFqWNfQVYf){ELCdRNIwyG = true;}
      if(aHbtKggZXc == AGbfDVXXfd){dxUljxeIqS = true;}
      if(xGCZZjbWet == UFTTrOAmxt){RqeaCfturX = true;}
      while(lFqWNfQVYf == sKoMntwfqp){oOPwpAEORU = true;}
      while(AGbfDVXXfd == AGbfDVXXfd){ZEHiTmwSKT = true;}
      while(UFTTrOAmxt == UFTTrOAmxt){DoqWKLOyLB = true;}
      if(PNMnStFdOj == true){PNMnStFdOj = false;}
      if(RwDdSzzQmh == true){RwDdSzzQmh = false;}
      if(GSrKeglWez == true){GSrKeglWez = false;}
      if(fdXePmtnNJ == true){fdXePmtnNJ = false;}
      if(PsJuMYCoBs == true){PsJuMYCoBs = false;}
      if(OizPmxUCIl == true){OizPmxUCIl = false;}
      if(HizODnXYNf == true){HizODnXYNf = false;}
      if(ELCdRNIwyG == true){ELCdRNIwyG = false;}
      if(dxUljxeIqS == true){dxUljxeIqS = false;}
      if(RqeaCfturX == true){RqeaCfturX = false;}
      if(AdaVnDfVxZ == true){AdaVnDfVxZ = false;}
      if(oYECHKONdG == true){oYECHKONdG = false;}
      if(JOguNNfbak == true){JOguNNfbak = false;}
      if(TNEZFAVzxg == true){TNEZFAVzxg = false;}
      if(QIKRcrmbTr == true){QIKRcrmbTr = false;}
      if(RfQkOkxfHa == true){RfQkOkxfHa = false;}
      if(WEtMGbTdxH == true){WEtMGbTdxH = false;}
      if(oOPwpAEORU == true){oOPwpAEORU = false;}
      if(ZEHiTmwSKT == true){ZEHiTmwSKT = false;}
      if(DoqWKLOyLB == true){DoqWKLOyLB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UMMLQRTDNW
{ 
  void LLqklLVfKx()
  { 
      bool hLgSENpNaV = false;
      bool VqWEBUsLOG = false;
      bool YUGGAzUaNj = false;
      bool dikiikddyV = false;
      bool fTLluplxZQ = false;
      bool ZUuyENEaRF = false;
      bool rOzprmFnUQ = false;
      bool pOMrZEIUKK = false;
      bool MWBxKImleU = false;
      bool fDMsdRUVsI = false;
      bool jxcIZLICYz = false;
      bool FjPHrVNCfi = false;
      bool zSIAjmCTOI = false;
      bool jmaCZOtrXy = false;
      bool AkNfPwmFAH = false;
      bool DRoKIQobYl = false;
      bool InmPOSINgc = false;
      bool aUegiOFckm = false;
      bool AxSHERxQtI = false;
      bool ZRTkpLxxQw = false;
      string AFXAHSAqJt;
      string UUDsdKqUYY;
      string abRttipETh;
      string imqCKEIQXr;
      string aqEFSuKPDX;
      string VkLQaYmdFX;
      string cwXbLgcBiY;
      string BaxfyiWMaz;
      string YaBuLxaaal;
      string RdKzPdTcsl;
      string RIgdVunfRr;
      string BaDFyCtbPN;
      string FCZwHXPxQT;
      string OtSnhQsXZQ;
      string JuIijpaEAN;
      string jrMefPijVy;
      string epOycGHOXh;
      string IWCzEKsqMR;
      string wKwDiWhmHR;
      string gJBakTfKFc;
      if(AFXAHSAqJt == RIgdVunfRr){hLgSENpNaV = true;}
      else if(RIgdVunfRr == AFXAHSAqJt){jxcIZLICYz = true;}
      if(UUDsdKqUYY == BaDFyCtbPN){VqWEBUsLOG = true;}
      else if(BaDFyCtbPN == UUDsdKqUYY){FjPHrVNCfi = true;}
      if(abRttipETh == FCZwHXPxQT){YUGGAzUaNj = true;}
      else if(FCZwHXPxQT == abRttipETh){zSIAjmCTOI = true;}
      if(imqCKEIQXr == OtSnhQsXZQ){dikiikddyV = true;}
      else if(OtSnhQsXZQ == imqCKEIQXr){jmaCZOtrXy = true;}
      if(aqEFSuKPDX == JuIijpaEAN){fTLluplxZQ = true;}
      else if(JuIijpaEAN == aqEFSuKPDX){AkNfPwmFAH = true;}
      if(VkLQaYmdFX == jrMefPijVy){ZUuyENEaRF = true;}
      else if(jrMefPijVy == VkLQaYmdFX){DRoKIQobYl = true;}
      if(cwXbLgcBiY == epOycGHOXh){rOzprmFnUQ = true;}
      else if(epOycGHOXh == cwXbLgcBiY){InmPOSINgc = true;}
      if(BaxfyiWMaz == IWCzEKsqMR){pOMrZEIUKK = true;}
      if(YaBuLxaaal == wKwDiWhmHR){MWBxKImleU = true;}
      if(RdKzPdTcsl == gJBakTfKFc){fDMsdRUVsI = true;}
      while(IWCzEKsqMR == BaxfyiWMaz){aUegiOFckm = true;}
      while(wKwDiWhmHR == wKwDiWhmHR){AxSHERxQtI = true;}
      while(gJBakTfKFc == gJBakTfKFc){ZRTkpLxxQw = true;}
      if(hLgSENpNaV == true){hLgSENpNaV = false;}
      if(VqWEBUsLOG == true){VqWEBUsLOG = false;}
      if(YUGGAzUaNj == true){YUGGAzUaNj = false;}
      if(dikiikddyV == true){dikiikddyV = false;}
      if(fTLluplxZQ == true){fTLluplxZQ = false;}
      if(ZUuyENEaRF == true){ZUuyENEaRF = false;}
      if(rOzprmFnUQ == true){rOzprmFnUQ = false;}
      if(pOMrZEIUKK == true){pOMrZEIUKK = false;}
      if(MWBxKImleU == true){MWBxKImleU = false;}
      if(fDMsdRUVsI == true){fDMsdRUVsI = false;}
      if(jxcIZLICYz == true){jxcIZLICYz = false;}
      if(FjPHrVNCfi == true){FjPHrVNCfi = false;}
      if(zSIAjmCTOI == true){zSIAjmCTOI = false;}
      if(jmaCZOtrXy == true){jmaCZOtrXy = false;}
      if(AkNfPwmFAH == true){AkNfPwmFAH = false;}
      if(DRoKIQobYl == true){DRoKIQobYl = false;}
      if(InmPOSINgc == true){InmPOSINgc = false;}
      if(aUegiOFckm == true){aUegiOFckm = false;}
      if(AxSHERxQtI == true){AxSHERxQtI = false;}
      if(ZRTkpLxxQw == true){ZRTkpLxxQw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UQTOEGWQQG
{ 
  void lRpVdMQUOO()
  { 
      bool koGVANaAJK = false;
      bool quOdTjnHJU = false;
      bool lowegJjqiI = false;
      bool IpDAeAVSIG = false;
      bool xRJSYzmDTK = false;
      bool sbwFMwsbnp = false;
      bool djQABAqOzS = false;
      bool OUyDXTecFg = false;
      bool WfXYPgtymi = false;
      bool HsdScNAJRY = false;
      bool IYEAwXcshr = false;
      bool QPWHTxLrjU = false;
      bool GsaPLUpfaK = false;
      bool SVLgXxaXbr = false;
      bool EBPtRrWWze = false;
      bool BIYxSOynoa = false;
      bool gxRXYuDoiV = false;
      bool WnPrQFcfyS = false;
      bool xTfwIKwOOJ = false;
      bool zmhAKGirUW = false;
      string quhZuTEnOC;
      string QPMnAaNUGi;
      string eWyBxEKXBa;
      string ZjSYbSAflw;
      string HTGdaULcno;
      string ZywEhTwfcp;
      string IfmncfxnLg;
      string ZghJaKQUZc;
      string sgjLAamOpH;
      string VUCunbgSBt;
      string XXRGOrPmcW;
      string DbFAxbwamB;
      string rhxDLFelVz;
      string dySeFUPdwI;
      string KAkTEtPCxL;
      string fFezCoZNuJ;
      string NcQdsFIZub;
      string LRdeprxdzQ;
      string pcoJTXSScQ;
      string uBhmugiGZz;
      if(quhZuTEnOC == XXRGOrPmcW){koGVANaAJK = true;}
      else if(XXRGOrPmcW == quhZuTEnOC){IYEAwXcshr = true;}
      if(QPMnAaNUGi == DbFAxbwamB){quOdTjnHJU = true;}
      else if(DbFAxbwamB == QPMnAaNUGi){QPWHTxLrjU = true;}
      if(eWyBxEKXBa == rhxDLFelVz){lowegJjqiI = true;}
      else if(rhxDLFelVz == eWyBxEKXBa){GsaPLUpfaK = true;}
      if(ZjSYbSAflw == dySeFUPdwI){IpDAeAVSIG = true;}
      else if(dySeFUPdwI == ZjSYbSAflw){SVLgXxaXbr = true;}
      if(HTGdaULcno == KAkTEtPCxL){xRJSYzmDTK = true;}
      else if(KAkTEtPCxL == HTGdaULcno){EBPtRrWWze = true;}
      if(ZywEhTwfcp == fFezCoZNuJ){sbwFMwsbnp = true;}
      else if(fFezCoZNuJ == ZywEhTwfcp){BIYxSOynoa = true;}
      if(IfmncfxnLg == NcQdsFIZub){djQABAqOzS = true;}
      else if(NcQdsFIZub == IfmncfxnLg){gxRXYuDoiV = true;}
      if(ZghJaKQUZc == LRdeprxdzQ){OUyDXTecFg = true;}
      if(sgjLAamOpH == pcoJTXSScQ){WfXYPgtymi = true;}
      if(VUCunbgSBt == uBhmugiGZz){HsdScNAJRY = true;}
      while(LRdeprxdzQ == ZghJaKQUZc){WnPrQFcfyS = true;}
      while(pcoJTXSScQ == pcoJTXSScQ){xTfwIKwOOJ = true;}
      while(uBhmugiGZz == uBhmugiGZz){zmhAKGirUW = true;}
      if(koGVANaAJK == true){koGVANaAJK = false;}
      if(quOdTjnHJU == true){quOdTjnHJU = false;}
      if(lowegJjqiI == true){lowegJjqiI = false;}
      if(IpDAeAVSIG == true){IpDAeAVSIG = false;}
      if(xRJSYzmDTK == true){xRJSYzmDTK = false;}
      if(sbwFMwsbnp == true){sbwFMwsbnp = false;}
      if(djQABAqOzS == true){djQABAqOzS = false;}
      if(OUyDXTecFg == true){OUyDXTecFg = false;}
      if(WfXYPgtymi == true){WfXYPgtymi = false;}
      if(HsdScNAJRY == true){HsdScNAJRY = false;}
      if(IYEAwXcshr == true){IYEAwXcshr = false;}
      if(QPWHTxLrjU == true){QPWHTxLrjU = false;}
      if(GsaPLUpfaK == true){GsaPLUpfaK = false;}
      if(SVLgXxaXbr == true){SVLgXxaXbr = false;}
      if(EBPtRrWWze == true){EBPtRrWWze = false;}
      if(BIYxSOynoa == true){BIYxSOynoa = false;}
      if(gxRXYuDoiV == true){gxRXYuDoiV = false;}
      if(WnPrQFcfyS == true){WnPrQFcfyS = false;}
      if(xTfwIKwOOJ == true){xTfwIKwOOJ = false;}
      if(zmhAKGirUW == true){zmhAKGirUW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WDPALMELKN
{ 
  void iddlIhsqtz()
  { 
      bool cMSpFixWyM = false;
      bool CbwjRdYOVN = false;
      bool aIaJJVDeAe = false;
      bool aWywjwtdfr = false;
      bool eJVbSdXKDS = false;
      bool UpXwZTlIfi = false;
      bool eRVSkfczzU = false;
      bool itichQlyqf = false;
      bool ysbhKkyBVQ = false;
      bool KlywMNmDpm = false;
      bool AXKhiaGuNI = false;
      bool gmRzklpnIA = false;
      bool gbdhJxulPU = false;
      bool diHDfZhsyj = false;
      bool dCmNjXUyLa = false;
      bool WyupFXtbXl = false;
      bool eTesdxeNTK = false;
      bool DxoXVenPyl = false;
      bool cxanyenRxH = false;
      bool fGUMEJWtim = false;
      string IbeYIwWmzg;
      string YeiIXuftpA;
      string VqdTpOhWgX;
      string OzdFjajBHL;
      string VBhBFaaWNX;
      string gHLilRyLit;
      string NzGbSZBdXw;
      string KdmdeUIbNO;
      string mLJJpGmtSS;
      string cYSMxWtGif;
      string ZwyQMCTgEQ;
      string JVxTGCpxkL;
      string lGLFTkLagH;
      string ZBrhnqMrwn;
      string mFpBIGbyFu;
      string gxUXsSksxa;
      string qsAwqHdPfP;
      string pyAxYfQJxM;
      string JMUkacgUnV;
      string FTtUwsFsKA;
      if(IbeYIwWmzg == ZwyQMCTgEQ){cMSpFixWyM = true;}
      else if(ZwyQMCTgEQ == IbeYIwWmzg){AXKhiaGuNI = true;}
      if(YeiIXuftpA == JVxTGCpxkL){CbwjRdYOVN = true;}
      else if(JVxTGCpxkL == YeiIXuftpA){gmRzklpnIA = true;}
      if(VqdTpOhWgX == lGLFTkLagH){aIaJJVDeAe = true;}
      else if(lGLFTkLagH == VqdTpOhWgX){gbdhJxulPU = true;}
      if(OzdFjajBHL == ZBrhnqMrwn){aWywjwtdfr = true;}
      else if(ZBrhnqMrwn == OzdFjajBHL){diHDfZhsyj = true;}
      if(VBhBFaaWNX == mFpBIGbyFu){eJVbSdXKDS = true;}
      else if(mFpBIGbyFu == VBhBFaaWNX){dCmNjXUyLa = true;}
      if(gHLilRyLit == gxUXsSksxa){UpXwZTlIfi = true;}
      else if(gxUXsSksxa == gHLilRyLit){WyupFXtbXl = true;}
      if(NzGbSZBdXw == qsAwqHdPfP){eRVSkfczzU = true;}
      else if(qsAwqHdPfP == NzGbSZBdXw){eTesdxeNTK = true;}
      if(KdmdeUIbNO == pyAxYfQJxM){itichQlyqf = true;}
      if(mLJJpGmtSS == JMUkacgUnV){ysbhKkyBVQ = true;}
      if(cYSMxWtGif == FTtUwsFsKA){KlywMNmDpm = true;}
      while(pyAxYfQJxM == KdmdeUIbNO){DxoXVenPyl = true;}
      while(JMUkacgUnV == JMUkacgUnV){cxanyenRxH = true;}
      while(FTtUwsFsKA == FTtUwsFsKA){fGUMEJWtim = true;}
      if(cMSpFixWyM == true){cMSpFixWyM = false;}
      if(CbwjRdYOVN == true){CbwjRdYOVN = false;}
      if(aIaJJVDeAe == true){aIaJJVDeAe = false;}
      if(aWywjwtdfr == true){aWywjwtdfr = false;}
      if(eJVbSdXKDS == true){eJVbSdXKDS = false;}
      if(UpXwZTlIfi == true){UpXwZTlIfi = false;}
      if(eRVSkfczzU == true){eRVSkfczzU = false;}
      if(itichQlyqf == true){itichQlyqf = false;}
      if(ysbhKkyBVQ == true){ysbhKkyBVQ = false;}
      if(KlywMNmDpm == true){KlywMNmDpm = false;}
      if(AXKhiaGuNI == true){AXKhiaGuNI = false;}
      if(gmRzklpnIA == true){gmRzklpnIA = false;}
      if(gbdhJxulPU == true){gbdhJxulPU = false;}
      if(diHDfZhsyj == true){diHDfZhsyj = false;}
      if(dCmNjXUyLa == true){dCmNjXUyLa = false;}
      if(WyupFXtbXl == true){WyupFXtbXl = false;}
      if(eTesdxeNTK == true){eTesdxeNTK = false;}
      if(DxoXVenPyl == true){DxoXVenPyl = false;}
      if(cxanyenRxH == true){cxanyenRxH = false;}
      if(fGUMEJWtim == true){fGUMEJWtim = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TRKKSQRJNO
{ 
  void rmTeTFjbPJ()
  { 
      bool XapTmKOyzh = false;
      bool bKrImuXqaI = false;
      bool exxUuqrjCL = false;
      bool YddmYpqwlx = false;
      bool pgaFOGbfSf = false;
      bool AHbsVZcUXw = false;
      bool SdunIxfFjw = false;
      bool EbEcRyVrGo = false;
      bool OMQWKQCkQy = false;
      bool MVXpeMkmwQ = false;
      bool ZVwWbYDybW = false;
      bool EkOigFMYcq = false;
      bool uunkihENyF = false;
      bool MiuoOrQttl = false;
      bool NDJttbHoJZ = false;
      bool zMJEVehKmt = false;
      bool ToAVJUoYTn = false;
      bool oSdqdrltqH = false;
      bool ZOEYGzYpTj = false;
      bool KFHARYCmjY = false;
      string csdtbpYylY;
      string VUTzWWGHuD;
      string anTQCPtHzh;
      string cebiUBCGLJ;
      string jGRchWWLRE;
      string NfaEtoYMrM;
      string wQyEuprkeU;
      string UzulTTVqie;
      string shpuTxEXoe;
      string cpOzMSINgq;
      string elgwjOjokZ;
      string SgcMTNaCjx;
      string lUuzrejwYB;
      string LIJrAGBsLF;
      string NOmPLuMCfz;
      string rFciEJpgEF;
      string dnQiNKXkLM;
      string LgqejWhfnw;
      string RhPZIFeZmp;
      string QUnGbYyDBB;
      if(csdtbpYylY == elgwjOjokZ){XapTmKOyzh = true;}
      else if(elgwjOjokZ == csdtbpYylY){ZVwWbYDybW = true;}
      if(VUTzWWGHuD == SgcMTNaCjx){bKrImuXqaI = true;}
      else if(SgcMTNaCjx == VUTzWWGHuD){EkOigFMYcq = true;}
      if(anTQCPtHzh == lUuzrejwYB){exxUuqrjCL = true;}
      else if(lUuzrejwYB == anTQCPtHzh){uunkihENyF = true;}
      if(cebiUBCGLJ == LIJrAGBsLF){YddmYpqwlx = true;}
      else if(LIJrAGBsLF == cebiUBCGLJ){MiuoOrQttl = true;}
      if(jGRchWWLRE == NOmPLuMCfz){pgaFOGbfSf = true;}
      else if(NOmPLuMCfz == jGRchWWLRE){NDJttbHoJZ = true;}
      if(NfaEtoYMrM == rFciEJpgEF){AHbsVZcUXw = true;}
      else if(rFciEJpgEF == NfaEtoYMrM){zMJEVehKmt = true;}
      if(wQyEuprkeU == dnQiNKXkLM){SdunIxfFjw = true;}
      else if(dnQiNKXkLM == wQyEuprkeU){ToAVJUoYTn = true;}
      if(UzulTTVqie == LgqejWhfnw){EbEcRyVrGo = true;}
      if(shpuTxEXoe == RhPZIFeZmp){OMQWKQCkQy = true;}
      if(cpOzMSINgq == QUnGbYyDBB){MVXpeMkmwQ = true;}
      while(LgqejWhfnw == UzulTTVqie){oSdqdrltqH = true;}
      while(RhPZIFeZmp == RhPZIFeZmp){ZOEYGzYpTj = true;}
      while(QUnGbYyDBB == QUnGbYyDBB){KFHARYCmjY = true;}
      if(XapTmKOyzh == true){XapTmKOyzh = false;}
      if(bKrImuXqaI == true){bKrImuXqaI = false;}
      if(exxUuqrjCL == true){exxUuqrjCL = false;}
      if(YddmYpqwlx == true){YddmYpqwlx = false;}
      if(pgaFOGbfSf == true){pgaFOGbfSf = false;}
      if(AHbsVZcUXw == true){AHbsVZcUXw = false;}
      if(SdunIxfFjw == true){SdunIxfFjw = false;}
      if(EbEcRyVrGo == true){EbEcRyVrGo = false;}
      if(OMQWKQCkQy == true){OMQWKQCkQy = false;}
      if(MVXpeMkmwQ == true){MVXpeMkmwQ = false;}
      if(ZVwWbYDybW == true){ZVwWbYDybW = false;}
      if(EkOigFMYcq == true){EkOigFMYcq = false;}
      if(uunkihENyF == true){uunkihENyF = false;}
      if(MiuoOrQttl == true){MiuoOrQttl = false;}
      if(NDJttbHoJZ == true){NDJttbHoJZ = false;}
      if(zMJEVehKmt == true){zMJEVehKmt = false;}
      if(ToAVJUoYTn == true){ToAVJUoYTn = false;}
      if(oSdqdrltqH == true){oSdqdrltqH = false;}
      if(ZOEYGzYpTj == true){ZOEYGzYpTj = false;}
      if(KFHARYCmjY == true){KFHARYCmjY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQHXSUNEHM
{ 
  void nkDOgqkULZ()
  { 
      bool gpTPpOltUz = false;
      bool uzWpnVNSQT = false;
      bool RjDiGDgSqQ = false;
      bool JbyXljVjlZ = false;
      bool iNKeNDXXzm = false;
      bool EnnXCwmjIl = false;
      bool hTCDoSBzEE = false;
      bool zcgpjDYYVC = false;
      bool fITDMVmaUo = false;
      bool xkazrPKGpu = false;
      bool CXStnaHymz = false;
      bool XOOGGYAzqT = false;
      bool eadPHOCgyU = false;
      bool rShaAHpYPk = false;
      bool NonVQhVUsS = false;
      bool OLOVPatCmY = false;
      bool YZzRGEfnFy = false;
      bool iajFFpmIyY = false;
      bool rgneFgDMKY = false;
      bool NmkpMnoVOM = false;
      string iFHISBsHzl;
      string btAcKNShnR;
      string nnCyZNcehs;
      string FsqyRzLYgX;
      string qZVzSVLOiR;
      string InddQtCIhE;
      string XOZFfiDCKK;
      string CtBQaNSDeD;
      string COuQjRPMhW;
      string wCqbzcAPSj;
      string SJDXOOlMDC;
      string bzcdCJSIVO;
      string TpUmOzDYRy;
      string NCjukrKXCU;
      string eCJetwYMZo;
      string JrtEQboPJO;
      string LNuEnZPhrJ;
      string yuFAiQgorS;
      string apzbnUIfeJ;
      string DtOmJRHEqU;
      if(iFHISBsHzl == SJDXOOlMDC){gpTPpOltUz = true;}
      else if(SJDXOOlMDC == iFHISBsHzl){CXStnaHymz = true;}
      if(btAcKNShnR == bzcdCJSIVO){uzWpnVNSQT = true;}
      else if(bzcdCJSIVO == btAcKNShnR){XOOGGYAzqT = true;}
      if(nnCyZNcehs == TpUmOzDYRy){RjDiGDgSqQ = true;}
      else if(TpUmOzDYRy == nnCyZNcehs){eadPHOCgyU = true;}
      if(FsqyRzLYgX == NCjukrKXCU){JbyXljVjlZ = true;}
      else if(NCjukrKXCU == FsqyRzLYgX){rShaAHpYPk = true;}
      if(qZVzSVLOiR == eCJetwYMZo){iNKeNDXXzm = true;}
      else if(eCJetwYMZo == qZVzSVLOiR){NonVQhVUsS = true;}
      if(InddQtCIhE == JrtEQboPJO){EnnXCwmjIl = true;}
      else if(JrtEQboPJO == InddQtCIhE){OLOVPatCmY = true;}
      if(XOZFfiDCKK == LNuEnZPhrJ){hTCDoSBzEE = true;}
      else if(LNuEnZPhrJ == XOZFfiDCKK){YZzRGEfnFy = true;}
      if(CtBQaNSDeD == yuFAiQgorS){zcgpjDYYVC = true;}
      if(COuQjRPMhW == apzbnUIfeJ){fITDMVmaUo = true;}
      if(wCqbzcAPSj == DtOmJRHEqU){xkazrPKGpu = true;}
      while(yuFAiQgorS == CtBQaNSDeD){iajFFpmIyY = true;}
      while(apzbnUIfeJ == apzbnUIfeJ){rgneFgDMKY = true;}
      while(DtOmJRHEqU == DtOmJRHEqU){NmkpMnoVOM = true;}
      if(gpTPpOltUz == true){gpTPpOltUz = false;}
      if(uzWpnVNSQT == true){uzWpnVNSQT = false;}
      if(RjDiGDgSqQ == true){RjDiGDgSqQ = false;}
      if(JbyXljVjlZ == true){JbyXljVjlZ = false;}
      if(iNKeNDXXzm == true){iNKeNDXXzm = false;}
      if(EnnXCwmjIl == true){EnnXCwmjIl = false;}
      if(hTCDoSBzEE == true){hTCDoSBzEE = false;}
      if(zcgpjDYYVC == true){zcgpjDYYVC = false;}
      if(fITDMVmaUo == true){fITDMVmaUo = false;}
      if(xkazrPKGpu == true){xkazrPKGpu = false;}
      if(CXStnaHymz == true){CXStnaHymz = false;}
      if(XOOGGYAzqT == true){XOOGGYAzqT = false;}
      if(eadPHOCgyU == true){eadPHOCgyU = false;}
      if(rShaAHpYPk == true){rShaAHpYPk = false;}
      if(NonVQhVUsS == true){NonVQhVUsS = false;}
      if(OLOVPatCmY == true){OLOVPatCmY = false;}
      if(YZzRGEfnFy == true){YZzRGEfnFy = false;}
      if(iajFFpmIyY == true){iajFFpmIyY = false;}
      if(rgneFgDMKY == true){rgneFgDMKY = false;}
      if(NmkpMnoVOM == true){NmkpMnoVOM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ERGBGQTIJQ
{ 
  void eZVkkHtaLz()
  { 
      bool efJOEJqGfF = false;
      bool EEXnezKJZH = false;
      bool QUTMkIgGbk = false;
      bool DkFKJOtUUR = false;
      bool yeaUfGQYkX = false;
      bool FyCNeJLxdw = false;
      bool ckduCSzNdP = false;
      bool EpoIIltzfd = false;
      bool qHUEeEhqez = false;
      bool CxpXoNBfSM = false;
      bool HDtUSPJtEs = false;
      bool PMQzEUPZPx = false;
      bool jHhdMHzQTu = false;
      bool jNfSWmNzkP = false;
      bool unlljpgpTT = false;
      bool xaQUczVPIL = false;
      bool PrZJIBfxcQ = false;
      bool HQozBwUutW = false;
      bool aIxzyJxKpW = false;
      bool RxqYzDNcch = false;
      string BBDuQQYJrC;
      string UYYSBEmuqT;
      string AdyxgMrSNY;
      string lLRFRcUVBt;
      string wVCMfStlzd;
      string giIEhWDFOE;
      string YFuTQIGTAX;
      string jRsxWdbkRO;
      string RFTjqCDMXt;
      string ZOGxUqZiwX;
      string LakbtPpKhD;
      string uRnzlSlLbN;
      string FsuGxULubf;
      string ErosCpUqob;
      string LreUzHZGKC;
      string ENGhSSeedY;
      string DuiByCctxw;
      string ytVABMOaGo;
      string tEjYbplHaj;
      string KoNPXQIcVw;
      if(BBDuQQYJrC == LakbtPpKhD){efJOEJqGfF = true;}
      else if(LakbtPpKhD == BBDuQQYJrC){HDtUSPJtEs = true;}
      if(UYYSBEmuqT == uRnzlSlLbN){EEXnezKJZH = true;}
      else if(uRnzlSlLbN == UYYSBEmuqT){PMQzEUPZPx = true;}
      if(AdyxgMrSNY == FsuGxULubf){QUTMkIgGbk = true;}
      else if(FsuGxULubf == AdyxgMrSNY){jHhdMHzQTu = true;}
      if(lLRFRcUVBt == ErosCpUqob){DkFKJOtUUR = true;}
      else if(ErosCpUqob == lLRFRcUVBt){jNfSWmNzkP = true;}
      if(wVCMfStlzd == LreUzHZGKC){yeaUfGQYkX = true;}
      else if(LreUzHZGKC == wVCMfStlzd){unlljpgpTT = true;}
      if(giIEhWDFOE == ENGhSSeedY){FyCNeJLxdw = true;}
      else if(ENGhSSeedY == giIEhWDFOE){xaQUczVPIL = true;}
      if(YFuTQIGTAX == DuiByCctxw){ckduCSzNdP = true;}
      else if(DuiByCctxw == YFuTQIGTAX){PrZJIBfxcQ = true;}
      if(jRsxWdbkRO == ytVABMOaGo){EpoIIltzfd = true;}
      if(RFTjqCDMXt == tEjYbplHaj){qHUEeEhqez = true;}
      if(ZOGxUqZiwX == KoNPXQIcVw){CxpXoNBfSM = true;}
      while(ytVABMOaGo == jRsxWdbkRO){HQozBwUutW = true;}
      while(tEjYbplHaj == tEjYbplHaj){aIxzyJxKpW = true;}
      while(KoNPXQIcVw == KoNPXQIcVw){RxqYzDNcch = true;}
      if(efJOEJqGfF == true){efJOEJqGfF = false;}
      if(EEXnezKJZH == true){EEXnezKJZH = false;}
      if(QUTMkIgGbk == true){QUTMkIgGbk = false;}
      if(DkFKJOtUUR == true){DkFKJOtUUR = false;}
      if(yeaUfGQYkX == true){yeaUfGQYkX = false;}
      if(FyCNeJLxdw == true){FyCNeJLxdw = false;}
      if(ckduCSzNdP == true){ckduCSzNdP = false;}
      if(EpoIIltzfd == true){EpoIIltzfd = false;}
      if(qHUEeEhqez == true){qHUEeEhqez = false;}
      if(CxpXoNBfSM == true){CxpXoNBfSM = false;}
      if(HDtUSPJtEs == true){HDtUSPJtEs = false;}
      if(PMQzEUPZPx == true){PMQzEUPZPx = false;}
      if(jHhdMHzQTu == true){jHhdMHzQTu = false;}
      if(jNfSWmNzkP == true){jNfSWmNzkP = false;}
      if(unlljpgpTT == true){unlljpgpTT = false;}
      if(xaQUczVPIL == true){xaQUczVPIL = false;}
      if(PrZJIBfxcQ == true){PrZJIBfxcQ = false;}
      if(HQozBwUutW == true){HQozBwUutW = false;}
      if(aIxzyJxKpW == true){aIxzyJxKpW = false;}
      if(RxqYzDNcch == true){RxqYzDNcch = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DHUKAGJTKO
{ 
  void TpiDPtuEqT()
  { 
      bool bcCNIlyRsQ = false;
      bool HxFJEHuYMQ = false;
      bool AoJJkTwwNk = false;
      bool OBpeduZZsO = false;
      bool ccWbqRxPor = false;
      bool WsmVxlTscn = false;
      bool pBDICFHaeJ = false;
      bool hUfxnWSgST = false;
      bool VfGVNVOTgr = false;
      bool agxEXbYOZk = false;
      bool JWjfKBMohZ = false;
      bool TmZJRJthtg = false;
      bool qnsmhAXbYL = false;
      bool yDGhJzuaKL = false;
      bool IYlGYnGnmO = false;
      bool gpUstVcxxJ = false;
      bool djPVbPfrzS = false;
      bool OTXhXRBmNt = false;
      bool sjoKdHiNmn = false;
      bool VxcBhXJPeI = false;
      string UEaCWjuhJf;
      string KnLbeQnbPC;
      string jtSQFGhpQA;
      string ihlOpnkXUr;
      string YRnAAZfquM;
      string osfAZalKwP;
      string BFQJwbBwkp;
      string fPGXcRFRPf;
      string ZqtDKoBknO;
      string CabEpTBeEY;
      string YiFEgYlIXI;
      string VTtPpJLMzG;
      string ZPIWnEnChJ;
      string PaNqHploWk;
      string CsNeshfLNf;
      string InfxyIaiPc;
      string kjaNruGCIA;
      string XVpNDgBccG;
      string XcnBBatQsy;
      string PDYsASSzmy;
      if(UEaCWjuhJf == YiFEgYlIXI){bcCNIlyRsQ = true;}
      else if(YiFEgYlIXI == UEaCWjuhJf){JWjfKBMohZ = true;}
      if(KnLbeQnbPC == VTtPpJLMzG){HxFJEHuYMQ = true;}
      else if(VTtPpJLMzG == KnLbeQnbPC){TmZJRJthtg = true;}
      if(jtSQFGhpQA == ZPIWnEnChJ){AoJJkTwwNk = true;}
      else if(ZPIWnEnChJ == jtSQFGhpQA){qnsmhAXbYL = true;}
      if(ihlOpnkXUr == PaNqHploWk){OBpeduZZsO = true;}
      else if(PaNqHploWk == ihlOpnkXUr){yDGhJzuaKL = true;}
      if(YRnAAZfquM == CsNeshfLNf){ccWbqRxPor = true;}
      else if(CsNeshfLNf == YRnAAZfquM){IYlGYnGnmO = true;}
      if(osfAZalKwP == InfxyIaiPc){WsmVxlTscn = true;}
      else if(InfxyIaiPc == osfAZalKwP){gpUstVcxxJ = true;}
      if(BFQJwbBwkp == kjaNruGCIA){pBDICFHaeJ = true;}
      else if(kjaNruGCIA == BFQJwbBwkp){djPVbPfrzS = true;}
      if(fPGXcRFRPf == XVpNDgBccG){hUfxnWSgST = true;}
      if(ZqtDKoBknO == XcnBBatQsy){VfGVNVOTgr = true;}
      if(CabEpTBeEY == PDYsASSzmy){agxEXbYOZk = true;}
      while(XVpNDgBccG == fPGXcRFRPf){OTXhXRBmNt = true;}
      while(XcnBBatQsy == XcnBBatQsy){sjoKdHiNmn = true;}
      while(PDYsASSzmy == PDYsASSzmy){VxcBhXJPeI = true;}
      if(bcCNIlyRsQ == true){bcCNIlyRsQ = false;}
      if(HxFJEHuYMQ == true){HxFJEHuYMQ = false;}
      if(AoJJkTwwNk == true){AoJJkTwwNk = false;}
      if(OBpeduZZsO == true){OBpeduZZsO = false;}
      if(ccWbqRxPor == true){ccWbqRxPor = false;}
      if(WsmVxlTscn == true){WsmVxlTscn = false;}
      if(pBDICFHaeJ == true){pBDICFHaeJ = false;}
      if(hUfxnWSgST == true){hUfxnWSgST = false;}
      if(VfGVNVOTgr == true){VfGVNVOTgr = false;}
      if(agxEXbYOZk == true){agxEXbYOZk = false;}
      if(JWjfKBMohZ == true){JWjfKBMohZ = false;}
      if(TmZJRJthtg == true){TmZJRJthtg = false;}
      if(qnsmhAXbYL == true){qnsmhAXbYL = false;}
      if(yDGhJzuaKL == true){yDGhJzuaKL = false;}
      if(IYlGYnGnmO == true){IYlGYnGnmO = false;}
      if(gpUstVcxxJ == true){gpUstVcxxJ = false;}
      if(djPVbPfrzS == true){djPVbPfrzS = false;}
      if(OTXhXRBmNt == true){OTXhXRBmNt = false;}
      if(sjoKdHiNmn == true){sjoKdHiNmn = false;}
      if(VxcBhXJPeI == true){VxcBhXJPeI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CTHEJXRCHJ
{ 
  void sydLwxOEul()
  { 
      bool sjfEXiSZJR = false;
      bool wxIEzxgfnP = false;
      bool pdTwJlzPjc = false;
      bool gtupZPxclI = false;
      bool eZTOzBkqbs = false;
      bool ChwffPPjul = false;
      bool iCpfjCCRdj = false;
      bool zEtejQJExH = false;
      bool AInqayxPKK = false;
      bool zNgzZbimdw = false;
      bool zTMqsynQwP = false;
      bool FKmmkaOzFl = false;
      bool EmHTjlWtFH = false;
      bool gWZAIguwxc = false;
      bool JfTtEnZsOy = false;
      bool NjhrrMLrHH = false;
      bool atLniijleE = false;
      bool eRBccYSNOu = false;
      bool LceGswnhIw = false;
      bool VDooBOUeLV = false;
      string NLbqYtHkxk;
      string oCUVWshpYi;
      string paZciylgIK;
      string UelnqtdtjI;
      string TEfuWnUZUy;
      string QOURHllzIZ;
      string HabmPJQfdc;
      string OmFPPkteFt;
      string cLLKtGJTfE;
      string IelKAsbseM;
      string XourjcIFCW;
      string qHtNwwORrJ;
      string AwAZUjBuOV;
      string IBzsWnPTaR;
      string xERJMBkXNE;
      string dKBVManVXz;
      string aNpfNpHAqI;
      string fuqaMueqMT;
      string zdgKryAdfu;
      string ztuapiOkuW;
      if(NLbqYtHkxk == XourjcIFCW){sjfEXiSZJR = true;}
      else if(XourjcIFCW == NLbqYtHkxk){zTMqsynQwP = true;}
      if(oCUVWshpYi == qHtNwwORrJ){wxIEzxgfnP = true;}
      else if(qHtNwwORrJ == oCUVWshpYi){FKmmkaOzFl = true;}
      if(paZciylgIK == AwAZUjBuOV){pdTwJlzPjc = true;}
      else if(AwAZUjBuOV == paZciylgIK){EmHTjlWtFH = true;}
      if(UelnqtdtjI == IBzsWnPTaR){gtupZPxclI = true;}
      else if(IBzsWnPTaR == UelnqtdtjI){gWZAIguwxc = true;}
      if(TEfuWnUZUy == xERJMBkXNE){eZTOzBkqbs = true;}
      else if(xERJMBkXNE == TEfuWnUZUy){JfTtEnZsOy = true;}
      if(QOURHllzIZ == dKBVManVXz){ChwffPPjul = true;}
      else if(dKBVManVXz == QOURHllzIZ){NjhrrMLrHH = true;}
      if(HabmPJQfdc == aNpfNpHAqI){iCpfjCCRdj = true;}
      else if(aNpfNpHAqI == HabmPJQfdc){atLniijleE = true;}
      if(OmFPPkteFt == fuqaMueqMT){zEtejQJExH = true;}
      if(cLLKtGJTfE == zdgKryAdfu){AInqayxPKK = true;}
      if(IelKAsbseM == ztuapiOkuW){zNgzZbimdw = true;}
      while(fuqaMueqMT == OmFPPkteFt){eRBccYSNOu = true;}
      while(zdgKryAdfu == zdgKryAdfu){LceGswnhIw = true;}
      while(ztuapiOkuW == ztuapiOkuW){VDooBOUeLV = true;}
      if(sjfEXiSZJR == true){sjfEXiSZJR = false;}
      if(wxIEzxgfnP == true){wxIEzxgfnP = false;}
      if(pdTwJlzPjc == true){pdTwJlzPjc = false;}
      if(gtupZPxclI == true){gtupZPxclI = false;}
      if(eZTOzBkqbs == true){eZTOzBkqbs = false;}
      if(ChwffPPjul == true){ChwffPPjul = false;}
      if(iCpfjCCRdj == true){iCpfjCCRdj = false;}
      if(zEtejQJExH == true){zEtejQJExH = false;}
      if(AInqayxPKK == true){AInqayxPKK = false;}
      if(zNgzZbimdw == true){zNgzZbimdw = false;}
      if(zTMqsynQwP == true){zTMqsynQwP = false;}
      if(FKmmkaOzFl == true){FKmmkaOzFl = false;}
      if(EmHTjlWtFH == true){EmHTjlWtFH = false;}
      if(gWZAIguwxc == true){gWZAIguwxc = false;}
      if(JfTtEnZsOy == true){JfTtEnZsOy = false;}
      if(NjhrrMLrHH == true){NjhrrMLrHH = false;}
      if(atLniijleE == true){atLniijleE = false;}
      if(eRBccYSNOu == true){eRBccYSNOu = false;}
      if(LceGswnhIw == true){LceGswnhIw = false;}
      if(VDooBOUeLV == true){VDooBOUeLV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GEGZPYDDBW
{ 
  void GeWIMwPckB()
  { 
      bool ZsXkyIjwfH = false;
      bool CKKlihXBTH = false;
      bool KudXZetHeC = false;
      bool WnBtjUxerM = false;
      bool DzNuTrzGPR = false;
      bool rCbEqePzKS = false;
      bool ObQckNJQBN = false;
      bool jrIGELghEg = false;
      bool fmqMJTMwCF = false;
      bool FyUZyahjKF = false;
      bool iiFCgAtUAe = false;
      bool xhtclajDTQ = false;
      bool BMNuIlXiHc = false;
      bool dwWzyxhofJ = false;
      bool ZqwXHXEqmW = false;
      bool qdQtDWUJsu = false;
      bool cLNWAAKteo = false;
      bool stXJqKPpmj = false;
      bool hgujlzfcub = false;
      bool bXukfOdZWG = false;
      string leADdKplcf;
      string ICbmQhuhyy;
      string EagpkJdDAw;
      string kPocxtBmlZ;
      string JfrRzUqBrS;
      string zNuwxLxJRU;
      string gllftrNzpW;
      string gIuXnXhPqP;
      string RbKhwWUrek;
      string wrUQsWtLWG;
      string HqLVlqSXHY;
      string chRCDFbDjX;
      string XUTEZnmdeR;
      string dWskIZQowE;
      string ExkGIOZRNm;
      string upbzhlXGwx;
      string EnrptGogtc;
      string olGeSajMwK;
      string OVQqVmutDV;
      string CJrzAQEuLC;
      if(leADdKplcf == HqLVlqSXHY){ZsXkyIjwfH = true;}
      else if(HqLVlqSXHY == leADdKplcf){iiFCgAtUAe = true;}
      if(ICbmQhuhyy == chRCDFbDjX){CKKlihXBTH = true;}
      else if(chRCDFbDjX == ICbmQhuhyy){xhtclajDTQ = true;}
      if(EagpkJdDAw == XUTEZnmdeR){KudXZetHeC = true;}
      else if(XUTEZnmdeR == EagpkJdDAw){BMNuIlXiHc = true;}
      if(kPocxtBmlZ == dWskIZQowE){WnBtjUxerM = true;}
      else if(dWskIZQowE == kPocxtBmlZ){dwWzyxhofJ = true;}
      if(JfrRzUqBrS == ExkGIOZRNm){DzNuTrzGPR = true;}
      else if(ExkGIOZRNm == JfrRzUqBrS){ZqwXHXEqmW = true;}
      if(zNuwxLxJRU == upbzhlXGwx){rCbEqePzKS = true;}
      else if(upbzhlXGwx == zNuwxLxJRU){qdQtDWUJsu = true;}
      if(gllftrNzpW == EnrptGogtc){ObQckNJQBN = true;}
      else if(EnrptGogtc == gllftrNzpW){cLNWAAKteo = true;}
      if(gIuXnXhPqP == olGeSajMwK){jrIGELghEg = true;}
      if(RbKhwWUrek == OVQqVmutDV){fmqMJTMwCF = true;}
      if(wrUQsWtLWG == CJrzAQEuLC){FyUZyahjKF = true;}
      while(olGeSajMwK == gIuXnXhPqP){stXJqKPpmj = true;}
      while(OVQqVmutDV == OVQqVmutDV){hgujlzfcub = true;}
      while(CJrzAQEuLC == CJrzAQEuLC){bXukfOdZWG = true;}
      if(ZsXkyIjwfH == true){ZsXkyIjwfH = false;}
      if(CKKlihXBTH == true){CKKlihXBTH = false;}
      if(KudXZetHeC == true){KudXZetHeC = false;}
      if(WnBtjUxerM == true){WnBtjUxerM = false;}
      if(DzNuTrzGPR == true){DzNuTrzGPR = false;}
      if(rCbEqePzKS == true){rCbEqePzKS = false;}
      if(ObQckNJQBN == true){ObQckNJQBN = false;}
      if(jrIGELghEg == true){jrIGELghEg = false;}
      if(fmqMJTMwCF == true){fmqMJTMwCF = false;}
      if(FyUZyahjKF == true){FyUZyahjKF = false;}
      if(iiFCgAtUAe == true){iiFCgAtUAe = false;}
      if(xhtclajDTQ == true){xhtclajDTQ = false;}
      if(BMNuIlXiHc == true){BMNuIlXiHc = false;}
      if(dwWzyxhofJ == true){dwWzyxhofJ = false;}
      if(ZqwXHXEqmW == true){ZqwXHXEqmW = false;}
      if(qdQtDWUJsu == true){qdQtDWUJsu = false;}
      if(cLNWAAKteo == true){cLNWAAKteo = false;}
      if(stXJqKPpmj == true){stXJqKPpmj = false;}
      if(hgujlzfcub == true){hgujlzfcub = false;}
      if(bXukfOdZWG == true){bXukfOdZWG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QYEKITLPMA
{ 
  void gEaXlKRooq()
  { 
      bool CAqSeDrUhw = false;
      bool kjAjpgjLLw = false;
      bool pKOlCUOhTH = false;
      bool NRqzWwWOqW = false;
      bool mxfuJcNkpx = false;
      bool QhXzMrkFPJ = false;
      bool oJBahTrAMs = false;
      bool KUUoJsdSbZ = false;
      bool GdqWpetqme = false;
      bool LQyghcwFMo = false;
      bool jNXwluNhpT = false;
      bool NScpCKRejC = false;
      bool ZBNghsWmHf = false;
      bool xYFmpsFujt = false;
      bool RLASQrnIeW = false;
      bool KQUJPhzqNr = false;
      bool YZZKWnMpzJ = false;
      bool EWupkNAuPp = false;
      bool FNIkVfEwWH = false;
      bool sOgqUrkpub = false;
      string XTeCFOIDuM;
      string nhRAIyTuGU;
      string MATwwpZFJP;
      string iLmXeDosxF;
      string FjWwOEZoPz;
      string HgSQnXAhGP;
      string nDtfdbtsVE;
      string JZyBPbcWhq;
      string PkoKHBsWiG;
      string DGmhQBpqSl;
      string JgSKphhRAM;
      string tcAOzCNiXb;
      string iWJOAClQjN;
      string klEugiSeUZ;
      string SaVWLaFYiO;
      string mGTpDlWDJm;
      string uRglaIXFgP;
      string jiOyIHBmDZ;
      string wNhVaeSNqu;
      string MOUgdBtiwD;
      if(XTeCFOIDuM == JgSKphhRAM){CAqSeDrUhw = true;}
      else if(JgSKphhRAM == XTeCFOIDuM){jNXwluNhpT = true;}
      if(nhRAIyTuGU == tcAOzCNiXb){kjAjpgjLLw = true;}
      else if(tcAOzCNiXb == nhRAIyTuGU){NScpCKRejC = true;}
      if(MATwwpZFJP == iWJOAClQjN){pKOlCUOhTH = true;}
      else if(iWJOAClQjN == MATwwpZFJP){ZBNghsWmHf = true;}
      if(iLmXeDosxF == klEugiSeUZ){NRqzWwWOqW = true;}
      else if(klEugiSeUZ == iLmXeDosxF){xYFmpsFujt = true;}
      if(FjWwOEZoPz == SaVWLaFYiO){mxfuJcNkpx = true;}
      else if(SaVWLaFYiO == FjWwOEZoPz){RLASQrnIeW = true;}
      if(HgSQnXAhGP == mGTpDlWDJm){QhXzMrkFPJ = true;}
      else if(mGTpDlWDJm == HgSQnXAhGP){KQUJPhzqNr = true;}
      if(nDtfdbtsVE == uRglaIXFgP){oJBahTrAMs = true;}
      else if(uRglaIXFgP == nDtfdbtsVE){YZZKWnMpzJ = true;}
      if(JZyBPbcWhq == jiOyIHBmDZ){KUUoJsdSbZ = true;}
      if(PkoKHBsWiG == wNhVaeSNqu){GdqWpetqme = true;}
      if(DGmhQBpqSl == MOUgdBtiwD){LQyghcwFMo = true;}
      while(jiOyIHBmDZ == JZyBPbcWhq){EWupkNAuPp = true;}
      while(wNhVaeSNqu == wNhVaeSNqu){FNIkVfEwWH = true;}
      while(MOUgdBtiwD == MOUgdBtiwD){sOgqUrkpub = true;}
      if(CAqSeDrUhw == true){CAqSeDrUhw = false;}
      if(kjAjpgjLLw == true){kjAjpgjLLw = false;}
      if(pKOlCUOhTH == true){pKOlCUOhTH = false;}
      if(NRqzWwWOqW == true){NRqzWwWOqW = false;}
      if(mxfuJcNkpx == true){mxfuJcNkpx = false;}
      if(QhXzMrkFPJ == true){QhXzMrkFPJ = false;}
      if(oJBahTrAMs == true){oJBahTrAMs = false;}
      if(KUUoJsdSbZ == true){KUUoJsdSbZ = false;}
      if(GdqWpetqme == true){GdqWpetqme = false;}
      if(LQyghcwFMo == true){LQyghcwFMo = false;}
      if(jNXwluNhpT == true){jNXwluNhpT = false;}
      if(NScpCKRejC == true){NScpCKRejC = false;}
      if(ZBNghsWmHf == true){ZBNghsWmHf = false;}
      if(xYFmpsFujt == true){xYFmpsFujt = false;}
      if(RLASQrnIeW == true){RLASQrnIeW = false;}
      if(KQUJPhzqNr == true){KQUJPhzqNr = false;}
      if(YZZKWnMpzJ == true){YZZKWnMpzJ = false;}
      if(EWupkNAuPp == true){EWupkNAuPp = false;}
      if(FNIkVfEwWH == true){FNIkVfEwWH = false;}
      if(sOgqUrkpub == true){sOgqUrkpub = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWYYKRSIPO
{ 
  void VSaAIuRjtE()
  { 
      bool EfScQPToRQ = false;
      bool IfSzAjJAcX = false;
      bool kiEXWBDuPX = false;
      bool CXDkQpUAma = false;
      bool UUnjmHVQpf = false;
      bool eVTdGVbtGO = false;
      bool LXYsNjchhJ = false;
      bool OJMBCQtUkP = false;
      bool flFjrfEYdu = false;
      bool OatXPxuuWC = false;
      bool emigQVIRbo = false;
      bool aGIpiYSoAg = false;
      bool fDEmtmOolF = false;
      bool VzyijrDYSW = false;
      bool WlxnTISDnp = false;
      bool dGtoVbiulc = false;
      bool GTfVTbIYGp = false;
      bool VtVdJsFPTl = false;
      bool ULBubPEJMI = false;
      bool JHloPDGbUq = false;
      string BUhpsSMLrA;
      string nSSkdyZgEc;
      string wIrHEcqlRo;
      string dzUbGuHRoK;
      string OxpocOxrRX;
      string ExJJFrcZkQ;
      string aZsCVoxqeh;
      string qHqtOyRDdp;
      string fzUtjgoLWN;
      string SggYinEmSn;
      string QFNjgxFOtH;
      string ZYutkbEySn;
      string zlUQOJZRKZ;
      string tejpZZkkNm;
      string bZQOnslmnH;
      string iFUdodkwUW;
      string WmDTMuoFTK;
      string pTkfMYUFcV;
      string WmdDqoJFAu;
      string noQpPoVxBr;
      if(BUhpsSMLrA == QFNjgxFOtH){EfScQPToRQ = true;}
      else if(QFNjgxFOtH == BUhpsSMLrA){emigQVIRbo = true;}
      if(nSSkdyZgEc == ZYutkbEySn){IfSzAjJAcX = true;}
      else if(ZYutkbEySn == nSSkdyZgEc){aGIpiYSoAg = true;}
      if(wIrHEcqlRo == zlUQOJZRKZ){kiEXWBDuPX = true;}
      else if(zlUQOJZRKZ == wIrHEcqlRo){fDEmtmOolF = true;}
      if(dzUbGuHRoK == tejpZZkkNm){CXDkQpUAma = true;}
      else if(tejpZZkkNm == dzUbGuHRoK){VzyijrDYSW = true;}
      if(OxpocOxrRX == bZQOnslmnH){UUnjmHVQpf = true;}
      else if(bZQOnslmnH == OxpocOxrRX){WlxnTISDnp = true;}
      if(ExJJFrcZkQ == iFUdodkwUW){eVTdGVbtGO = true;}
      else if(iFUdodkwUW == ExJJFrcZkQ){dGtoVbiulc = true;}
      if(aZsCVoxqeh == WmDTMuoFTK){LXYsNjchhJ = true;}
      else if(WmDTMuoFTK == aZsCVoxqeh){GTfVTbIYGp = true;}
      if(qHqtOyRDdp == pTkfMYUFcV){OJMBCQtUkP = true;}
      if(fzUtjgoLWN == WmdDqoJFAu){flFjrfEYdu = true;}
      if(SggYinEmSn == noQpPoVxBr){OatXPxuuWC = true;}
      while(pTkfMYUFcV == qHqtOyRDdp){VtVdJsFPTl = true;}
      while(WmdDqoJFAu == WmdDqoJFAu){ULBubPEJMI = true;}
      while(noQpPoVxBr == noQpPoVxBr){JHloPDGbUq = true;}
      if(EfScQPToRQ == true){EfScQPToRQ = false;}
      if(IfSzAjJAcX == true){IfSzAjJAcX = false;}
      if(kiEXWBDuPX == true){kiEXWBDuPX = false;}
      if(CXDkQpUAma == true){CXDkQpUAma = false;}
      if(UUnjmHVQpf == true){UUnjmHVQpf = false;}
      if(eVTdGVbtGO == true){eVTdGVbtGO = false;}
      if(LXYsNjchhJ == true){LXYsNjchhJ = false;}
      if(OJMBCQtUkP == true){OJMBCQtUkP = false;}
      if(flFjrfEYdu == true){flFjrfEYdu = false;}
      if(OatXPxuuWC == true){OatXPxuuWC = false;}
      if(emigQVIRbo == true){emigQVIRbo = false;}
      if(aGIpiYSoAg == true){aGIpiYSoAg = false;}
      if(fDEmtmOolF == true){fDEmtmOolF = false;}
      if(VzyijrDYSW == true){VzyijrDYSW = false;}
      if(WlxnTISDnp == true){WlxnTISDnp = false;}
      if(dGtoVbiulc == true){dGtoVbiulc = false;}
      if(GTfVTbIYGp == true){GTfVTbIYGp = false;}
      if(VtVdJsFPTl == true){VtVdJsFPTl = false;}
      if(ULBubPEJMI == true){ULBubPEJMI = false;}
      if(JHloPDGbUq == true){JHloPDGbUq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TGIDXGIWRJ
{ 
  void lLGgQEVOlC()
  { 
      bool aKeRIXclZE = false;
      bool YDDcltUyUN = false;
      bool IiGRGsYgai = false;
      bool UmYurBfKxd = false;
      bool JKqnqPiLkm = false;
      bool IceEVrENLP = false;
      bool yuLqjkdHjk = false;
      bool NKApDxrSZq = false;
      bool KMwmZrHUYA = false;
      bool wSzhfOzzEG = false;
      bool laazZxboBX = false;
      bool zlmTFkzXQr = false;
      bool cJhjntLRJo = false;
      bool yrOTFilwNb = false;
      bool PSTAAKfect = false;
      bool OahLcbspKe = false;
      bool kKeLZHXSOV = false;
      bool zCKocKogjd = false;
      bool NgoPZWJCqc = false;
      bool oukhpEmHas = false;
      string VeOSaeXFQw;
      string QBiAxohlNd;
      string FqrBJUfxlz;
      string MKLlKTPili;
      string IbILhLCcUt;
      string eSeeyelMJG;
      string yZSQiGpxoc;
      string YzAeVdigTy;
      string SDbqTtefmf;
      string gCYfjhIqba;
      string VEmrUfSAJU;
      string wFrLmuxawo;
      string aJJJuWZUum;
      string UqEscNPjWn;
      string beWSibKNrn;
      string khtmALtdwy;
      string GxEWAEAzhZ;
      string eMEIMumqZT;
      string LLbGCmwRsQ;
      string SlnXhdazRe;
      if(VeOSaeXFQw == VEmrUfSAJU){aKeRIXclZE = true;}
      else if(VEmrUfSAJU == VeOSaeXFQw){laazZxboBX = true;}
      if(QBiAxohlNd == wFrLmuxawo){YDDcltUyUN = true;}
      else if(wFrLmuxawo == QBiAxohlNd){zlmTFkzXQr = true;}
      if(FqrBJUfxlz == aJJJuWZUum){IiGRGsYgai = true;}
      else if(aJJJuWZUum == FqrBJUfxlz){cJhjntLRJo = true;}
      if(MKLlKTPili == UqEscNPjWn){UmYurBfKxd = true;}
      else if(UqEscNPjWn == MKLlKTPili){yrOTFilwNb = true;}
      if(IbILhLCcUt == beWSibKNrn){JKqnqPiLkm = true;}
      else if(beWSibKNrn == IbILhLCcUt){PSTAAKfect = true;}
      if(eSeeyelMJG == khtmALtdwy){IceEVrENLP = true;}
      else if(khtmALtdwy == eSeeyelMJG){OahLcbspKe = true;}
      if(yZSQiGpxoc == GxEWAEAzhZ){yuLqjkdHjk = true;}
      else if(GxEWAEAzhZ == yZSQiGpxoc){kKeLZHXSOV = true;}
      if(YzAeVdigTy == eMEIMumqZT){NKApDxrSZq = true;}
      if(SDbqTtefmf == LLbGCmwRsQ){KMwmZrHUYA = true;}
      if(gCYfjhIqba == SlnXhdazRe){wSzhfOzzEG = true;}
      while(eMEIMumqZT == YzAeVdigTy){zCKocKogjd = true;}
      while(LLbGCmwRsQ == LLbGCmwRsQ){NgoPZWJCqc = true;}
      while(SlnXhdazRe == SlnXhdazRe){oukhpEmHas = true;}
      if(aKeRIXclZE == true){aKeRIXclZE = false;}
      if(YDDcltUyUN == true){YDDcltUyUN = false;}
      if(IiGRGsYgai == true){IiGRGsYgai = false;}
      if(UmYurBfKxd == true){UmYurBfKxd = false;}
      if(JKqnqPiLkm == true){JKqnqPiLkm = false;}
      if(IceEVrENLP == true){IceEVrENLP = false;}
      if(yuLqjkdHjk == true){yuLqjkdHjk = false;}
      if(NKApDxrSZq == true){NKApDxrSZq = false;}
      if(KMwmZrHUYA == true){KMwmZrHUYA = false;}
      if(wSzhfOzzEG == true){wSzhfOzzEG = false;}
      if(laazZxboBX == true){laazZxboBX = false;}
      if(zlmTFkzXQr == true){zlmTFkzXQr = false;}
      if(cJhjntLRJo == true){cJhjntLRJo = false;}
      if(yrOTFilwNb == true){yrOTFilwNb = false;}
      if(PSTAAKfect == true){PSTAAKfect = false;}
      if(OahLcbspKe == true){OahLcbspKe = false;}
      if(kKeLZHXSOV == true){kKeLZHXSOV = false;}
      if(zCKocKogjd == true){zCKocKogjd = false;}
      if(NgoPZWJCqc == true){NgoPZWJCqc = false;}
      if(oukhpEmHas == true){oukhpEmHas = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQUIXTUTIZ
{ 
  void DFBGDGsKJk()
  { 
      bool uansFmefDh = false;
      bool MZBcwwznaR = false;
      bool MVndpJDbJa = false;
      bool lqZLhVLjon = false;
      bool CwNPBBOXpn = false;
      bool VFMXJYlKDu = false;
      bool jDWcuVzotZ = false;
      bool jPylPQHYbn = false;
      bool uelUEgdCBJ = false;
      bool jBftEzZkTe = false;
      bool CYdPDGHaHs = false;
      bool QMhOAFQBXO = false;
      bool rwmjpiiDhQ = false;
      bool pWFxlVAVRx = false;
      bool ZDtIrWSRtz = false;
      bool hYMFmFksZU = false;
      bool XDsqCsHkcd = false;
      bool EuianoBerS = false;
      bool QRJhhRKAJf = false;
      bool jHwxZWJCFy = false;
      string kjgnSUalja;
      string WqUzFSJWwI;
      string apRyUYMpJz;
      string PcGBzFuynO;
      string lOlFPzNfRa;
      string nAqrmuRhTt;
      string HjbkKsjTAz;
      string XLihVMDMiV;
      string KgYiKPkNOE;
      string nMetGClBuV;
      string OtfRDcRJWZ;
      string rFzyiaKsat;
      string HWEuLKgoaT;
      string ZCRMGQAGeg;
      string ybqoMhNfLf;
      string qsZAOrojFs;
      string wciDzommrR;
      string ZENtwfePic;
      string wAcubgbRyO;
      string aPAljVsnoW;
      if(kjgnSUalja == OtfRDcRJWZ){uansFmefDh = true;}
      else if(OtfRDcRJWZ == kjgnSUalja){CYdPDGHaHs = true;}
      if(WqUzFSJWwI == rFzyiaKsat){MZBcwwznaR = true;}
      else if(rFzyiaKsat == WqUzFSJWwI){QMhOAFQBXO = true;}
      if(apRyUYMpJz == HWEuLKgoaT){MVndpJDbJa = true;}
      else if(HWEuLKgoaT == apRyUYMpJz){rwmjpiiDhQ = true;}
      if(PcGBzFuynO == ZCRMGQAGeg){lqZLhVLjon = true;}
      else if(ZCRMGQAGeg == PcGBzFuynO){pWFxlVAVRx = true;}
      if(lOlFPzNfRa == ybqoMhNfLf){CwNPBBOXpn = true;}
      else if(ybqoMhNfLf == lOlFPzNfRa){ZDtIrWSRtz = true;}
      if(nAqrmuRhTt == qsZAOrojFs){VFMXJYlKDu = true;}
      else if(qsZAOrojFs == nAqrmuRhTt){hYMFmFksZU = true;}
      if(HjbkKsjTAz == wciDzommrR){jDWcuVzotZ = true;}
      else if(wciDzommrR == HjbkKsjTAz){XDsqCsHkcd = true;}
      if(XLihVMDMiV == ZENtwfePic){jPylPQHYbn = true;}
      if(KgYiKPkNOE == wAcubgbRyO){uelUEgdCBJ = true;}
      if(nMetGClBuV == aPAljVsnoW){jBftEzZkTe = true;}
      while(ZENtwfePic == XLihVMDMiV){EuianoBerS = true;}
      while(wAcubgbRyO == wAcubgbRyO){QRJhhRKAJf = true;}
      while(aPAljVsnoW == aPAljVsnoW){jHwxZWJCFy = true;}
      if(uansFmefDh == true){uansFmefDh = false;}
      if(MZBcwwznaR == true){MZBcwwznaR = false;}
      if(MVndpJDbJa == true){MVndpJDbJa = false;}
      if(lqZLhVLjon == true){lqZLhVLjon = false;}
      if(CwNPBBOXpn == true){CwNPBBOXpn = false;}
      if(VFMXJYlKDu == true){VFMXJYlKDu = false;}
      if(jDWcuVzotZ == true){jDWcuVzotZ = false;}
      if(jPylPQHYbn == true){jPylPQHYbn = false;}
      if(uelUEgdCBJ == true){uelUEgdCBJ = false;}
      if(jBftEzZkTe == true){jBftEzZkTe = false;}
      if(CYdPDGHaHs == true){CYdPDGHaHs = false;}
      if(QMhOAFQBXO == true){QMhOAFQBXO = false;}
      if(rwmjpiiDhQ == true){rwmjpiiDhQ = false;}
      if(pWFxlVAVRx == true){pWFxlVAVRx = false;}
      if(ZDtIrWSRtz == true){ZDtIrWSRtz = false;}
      if(hYMFmFksZU == true){hYMFmFksZU = false;}
      if(XDsqCsHkcd == true){XDsqCsHkcd = false;}
      if(EuianoBerS == true){EuianoBerS = false;}
      if(QRJhhRKAJf == true){QRJhhRKAJf = false;}
      if(jHwxZWJCFy == true){jHwxZWJCFy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHWDUAYIDI
{ 
  void hotRUGaMAc()
  { 
      bool VohxtzLDhF = false;
      bool ZEjXcysIoX = false;
      bool jRrVfAqrTb = false;
      bool CCTDbnKTTl = false;
      bool XhWJLNRYVs = false;
      bool YWWhyExMRs = false;
      bool HSjFCWkgwn = false;
      bool nZnCABuiJR = false;
      bool iRWZDeflEX = false;
      bool qxBadFyRGn = false;
      bool cjcgFziTgw = false;
      bool INCzJpwKBX = false;
      bool qzbXwpXMXu = false;
      bool DcbVoyooTD = false;
      bool uLEIOcuCRn = false;
      bool ImPiwcIEkP = false;
      bool bVwlsflgJK = false;
      bool AHpxbfuTJS = false;
      bool tUuilPNrYM = false;
      bool pkEDbZPROi = false;
      string FfxYnxYohs;
      string RrbkSZLIbH;
      string NVxOibdiFg;
      string YzHgNepKDr;
      string lfKSoXMnBR;
      string ZaQUajhipL;
      string SpiBTSktWm;
      string iBEjVhLeYK;
      string PphnGyhlGd;
      string wHTrYwwJyW;
      string lRQNiXVgzs;
      string XDJewcIutV;
      string jzmsqbgMKY;
      string kBgCXxZTEi;
      string bBlNFsxoww;
      string mBPbmmdXWG;
      string pJVaHWWHGy;
      string CnpLthNZmy;
      string drQNkilEOk;
      string SCxyrRfLFi;
      if(FfxYnxYohs == lRQNiXVgzs){VohxtzLDhF = true;}
      else if(lRQNiXVgzs == FfxYnxYohs){cjcgFziTgw = true;}
      if(RrbkSZLIbH == XDJewcIutV){ZEjXcysIoX = true;}
      else if(XDJewcIutV == RrbkSZLIbH){INCzJpwKBX = true;}
      if(NVxOibdiFg == jzmsqbgMKY){jRrVfAqrTb = true;}
      else if(jzmsqbgMKY == NVxOibdiFg){qzbXwpXMXu = true;}
      if(YzHgNepKDr == kBgCXxZTEi){CCTDbnKTTl = true;}
      else if(kBgCXxZTEi == YzHgNepKDr){DcbVoyooTD = true;}
      if(lfKSoXMnBR == bBlNFsxoww){XhWJLNRYVs = true;}
      else if(bBlNFsxoww == lfKSoXMnBR){uLEIOcuCRn = true;}
      if(ZaQUajhipL == mBPbmmdXWG){YWWhyExMRs = true;}
      else if(mBPbmmdXWG == ZaQUajhipL){ImPiwcIEkP = true;}
      if(SpiBTSktWm == pJVaHWWHGy){HSjFCWkgwn = true;}
      else if(pJVaHWWHGy == SpiBTSktWm){bVwlsflgJK = true;}
      if(iBEjVhLeYK == CnpLthNZmy){nZnCABuiJR = true;}
      if(PphnGyhlGd == drQNkilEOk){iRWZDeflEX = true;}
      if(wHTrYwwJyW == SCxyrRfLFi){qxBadFyRGn = true;}
      while(CnpLthNZmy == iBEjVhLeYK){AHpxbfuTJS = true;}
      while(drQNkilEOk == drQNkilEOk){tUuilPNrYM = true;}
      while(SCxyrRfLFi == SCxyrRfLFi){pkEDbZPROi = true;}
      if(VohxtzLDhF == true){VohxtzLDhF = false;}
      if(ZEjXcysIoX == true){ZEjXcysIoX = false;}
      if(jRrVfAqrTb == true){jRrVfAqrTb = false;}
      if(CCTDbnKTTl == true){CCTDbnKTTl = false;}
      if(XhWJLNRYVs == true){XhWJLNRYVs = false;}
      if(YWWhyExMRs == true){YWWhyExMRs = false;}
      if(HSjFCWkgwn == true){HSjFCWkgwn = false;}
      if(nZnCABuiJR == true){nZnCABuiJR = false;}
      if(iRWZDeflEX == true){iRWZDeflEX = false;}
      if(qxBadFyRGn == true){qxBadFyRGn = false;}
      if(cjcgFziTgw == true){cjcgFziTgw = false;}
      if(INCzJpwKBX == true){INCzJpwKBX = false;}
      if(qzbXwpXMXu == true){qzbXwpXMXu = false;}
      if(DcbVoyooTD == true){DcbVoyooTD = false;}
      if(uLEIOcuCRn == true){uLEIOcuCRn = false;}
      if(ImPiwcIEkP == true){ImPiwcIEkP = false;}
      if(bVwlsflgJK == true){bVwlsflgJK = false;}
      if(AHpxbfuTJS == true){AHpxbfuTJS = false;}
      if(tUuilPNrYM == true){tUuilPNrYM = false;}
      if(pkEDbZPROi == true){pkEDbZPROi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ILOFCYGGSG
{ 
  void XqCXqVwbje()
  { 
      bool HyLXDQCIpN = false;
      bool KUQbQRAdAQ = false;
      bool hBbkcMlqPd = false;
      bool AYLdWiobKK = false;
      bool XBBMhOlVmH = false;
      bool cOTlmGVatq = false;
      bool dKsMNkImEg = false;
      bool cXTpsfAOCO = false;
      bool ZQDHBkFZpQ = false;
      bool MOgSfMHnzw = false;
      bool GzQFeEucrG = false;
      bool FGYfQMGkLb = false;
      bool fhwmTOqAJg = false;
      bool YMPFIazycw = false;
      bool pbhjLGpABS = false;
      bool FVcWQXDdkP = false;
      bool MtSLhrpSXp = false;
      bool NIIOkEALaN = false;
      bool YqyqaCjsoj = false;
      bool XVMMjuIWCS = false;
      string sNrtLWhKFH;
      string BNBVKJoQNn;
      string oFGocStAgT;
      string GPVlyrohLe;
      string WXRhWkHyHz;
      string QqGUemGDRr;
      string chdkAlqPWS;
      string TGEhQRnXSq;
      string LusgDPIAGL;
      string klPSBotfhj;
      string trbnfJlYEN;
      string zikaghnwhj;
      string cpILghplgb;
      string WHohxTSEBs;
      string cjwsMBBolS;
      string AxxxGDjPHx;
      string SAqbpqsCdN;
      string PjuoGssOze;
      string gBANaZJqas;
      string jDxDZcrUCU;
      if(sNrtLWhKFH == trbnfJlYEN){HyLXDQCIpN = true;}
      else if(trbnfJlYEN == sNrtLWhKFH){GzQFeEucrG = true;}
      if(BNBVKJoQNn == zikaghnwhj){KUQbQRAdAQ = true;}
      else if(zikaghnwhj == BNBVKJoQNn){FGYfQMGkLb = true;}
      if(oFGocStAgT == cpILghplgb){hBbkcMlqPd = true;}
      else if(cpILghplgb == oFGocStAgT){fhwmTOqAJg = true;}
      if(GPVlyrohLe == WHohxTSEBs){AYLdWiobKK = true;}
      else if(WHohxTSEBs == GPVlyrohLe){YMPFIazycw = true;}
      if(WXRhWkHyHz == cjwsMBBolS){XBBMhOlVmH = true;}
      else if(cjwsMBBolS == WXRhWkHyHz){pbhjLGpABS = true;}
      if(QqGUemGDRr == AxxxGDjPHx){cOTlmGVatq = true;}
      else if(AxxxGDjPHx == QqGUemGDRr){FVcWQXDdkP = true;}
      if(chdkAlqPWS == SAqbpqsCdN){dKsMNkImEg = true;}
      else if(SAqbpqsCdN == chdkAlqPWS){MtSLhrpSXp = true;}
      if(TGEhQRnXSq == PjuoGssOze){cXTpsfAOCO = true;}
      if(LusgDPIAGL == gBANaZJqas){ZQDHBkFZpQ = true;}
      if(klPSBotfhj == jDxDZcrUCU){MOgSfMHnzw = true;}
      while(PjuoGssOze == TGEhQRnXSq){NIIOkEALaN = true;}
      while(gBANaZJqas == gBANaZJqas){YqyqaCjsoj = true;}
      while(jDxDZcrUCU == jDxDZcrUCU){XVMMjuIWCS = true;}
      if(HyLXDQCIpN == true){HyLXDQCIpN = false;}
      if(KUQbQRAdAQ == true){KUQbQRAdAQ = false;}
      if(hBbkcMlqPd == true){hBbkcMlqPd = false;}
      if(AYLdWiobKK == true){AYLdWiobKK = false;}
      if(XBBMhOlVmH == true){XBBMhOlVmH = false;}
      if(cOTlmGVatq == true){cOTlmGVatq = false;}
      if(dKsMNkImEg == true){dKsMNkImEg = false;}
      if(cXTpsfAOCO == true){cXTpsfAOCO = false;}
      if(ZQDHBkFZpQ == true){ZQDHBkFZpQ = false;}
      if(MOgSfMHnzw == true){MOgSfMHnzw = false;}
      if(GzQFeEucrG == true){GzQFeEucrG = false;}
      if(FGYfQMGkLb == true){FGYfQMGkLb = false;}
      if(fhwmTOqAJg == true){fhwmTOqAJg = false;}
      if(YMPFIazycw == true){YMPFIazycw = false;}
      if(pbhjLGpABS == true){pbhjLGpABS = false;}
      if(FVcWQXDdkP == true){FVcWQXDdkP = false;}
      if(MtSLhrpSXp == true){MtSLhrpSXp = false;}
      if(NIIOkEALaN == true){NIIOkEALaN = false;}
      if(YqyqaCjsoj == true){YqyqaCjsoj = false;}
      if(XVMMjuIWCS == true){XVMMjuIWCS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LOMYKGOPYY
{ 
  void HUOhnUzRcO()
  { 
      bool WOMQGBqgTO = false;
      bool QSelekadVC = false;
      bool AYgDNAgddV = false;
      bool SyiRUNGnxL = false;
      bool qpEiUIYYYE = false;
      bool VugbHxgICG = false;
      bool UMCxuRjMRR = false;
      bool dmfJKJUyiF = false;
      bool bIFYAWRGKX = false;
      bool fylqqemGmD = false;
      bool YLGHahPWRx = false;
      bool ciZweLHdxY = false;
      bool AcCskeBnSf = false;
      bool WNKefPBxxR = false;
      bool GtoMuwYoMe = false;
      bool WJJODuJMVu = false;
      bool gbEkaOYtQO = false;
      bool KJfeRGnoyn = false;
      bool GLbmIMDubk = false;
      bool FnbCkeoDlf = false;
      string WKZkWhaJzs;
      string wQGojhQhjT;
      string bnBagIFOYO;
      string apAXJpdzSy;
      string lCACNWqoii;
      string sGjXRiJyDO;
      string cMjkRGQies;
      string DRPkgZmyMK;
      string QQepVUGcGZ;
      string gfuEVZSPkH;
      string GIJpeaqypq;
      string uLksxLgsOx;
      string AnbEMXVKPG;
      string HXMFDHHoLt;
      string cHlOeUuCGK;
      string sYAnHRfEdH;
      string EfhijWyfop;
      string DrhTTrBNZq;
      string cTEENhWYyk;
      string bDKDpxZDdH;
      if(WKZkWhaJzs == GIJpeaqypq){WOMQGBqgTO = true;}
      else if(GIJpeaqypq == WKZkWhaJzs){YLGHahPWRx = true;}
      if(wQGojhQhjT == uLksxLgsOx){QSelekadVC = true;}
      else if(uLksxLgsOx == wQGojhQhjT){ciZweLHdxY = true;}
      if(bnBagIFOYO == AnbEMXVKPG){AYgDNAgddV = true;}
      else if(AnbEMXVKPG == bnBagIFOYO){AcCskeBnSf = true;}
      if(apAXJpdzSy == HXMFDHHoLt){SyiRUNGnxL = true;}
      else if(HXMFDHHoLt == apAXJpdzSy){WNKefPBxxR = true;}
      if(lCACNWqoii == cHlOeUuCGK){qpEiUIYYYE = true;}
      else if(cHlOeUuCGK == lCACNWqoii){GtoMuwYoMe = true;}
      if(sGjXRiJyDO == sYAnHRfEdH){VugbHxgICG = true;}
      else if(sYAnHRfEdH == sGjXRiJyDO){WJJODuJMVu = true;}
      if(cMjkRGQies == EfhijWyfop){UMCxuRjMRR = true;}
      else if(EfhijWyfop == cMjkRGQies){gbEkaOYtQO = true;}
      if(DRPkgZmyMK == DrhTTrBNZq){dmfJKJUyiF = true;}
      if(QQepVUGcGZ == cTEENhWYyk){bIFYAWRGKX = true;}
      if(gfuEVZSPkH == bDKDpxZDdH){fylqqemGmD = true;}
      while(DrhTTrBNZq == DRPkgZmyMK){KJfeRGnoyn = true;}
      while(cTEENhWYyk == cTEENhWYyk){GLbmIMDubk = true;}
      while(bDKDpxZDdH == bDKDpxZDdH){FnbCkeoDlf = true;}
      if(WOMQGBqgTO == true){WOMQGBqgTO = false;}
      if(QSelekadVC == true){QSelekadVC = false;}
      if(AYgDNAgddV == true){AYgDNAgddV = false;}
      if(SyiRUNGnxL == true){SyiRUNGnxL = false;}
      if(qpEiUIYYYE == true){qpEiUIYYYE = false;}
      if(VugbHxgICG == true){VugbHxgICG = false;}
      if(UMCxuRjMRR == true){UMCxuRjMRR = false;}
      if(dmfJKJUyiF == true){dmfJKJUyiF = false;}
      if(bIFYAWRGKX == true){bIFYAWRGKX = false;}
      if(fylqqemGmD == true){fylqqemGmD = false;}
      if(YLGHahPWRx == true){YLGHahPWRx = false;}
      if(ciZweLHdxY == true){ciZweLHdxY = false;}
      if(AcCskeBnSf == true){AcCskeBnSf = false;}
      if(WNKefPBxxR == true){WNKefPBxxR = false;}
      if(GtoMuwYoMe == true){GtoMuwYoMe = false;}
      if(WJJODuJMVu == true){WJJODuJMVu = false;}
      if(gbEkaOYtQO == true){gbEkaOYtQO = false;}
      if(KJfeRGnoyn == true){KJfeRGnoyn = false;}
      if(GLbmIMDubk == true){GLbmIMDubk = false;}
      if(FnbCkeoDlf == true){FnbCkeoDlf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WPEDFRWGNI
{ 
  void wRlZOyHzVw()
  { 
      bool QCaweBokxt = false;
      bool lyVYtTnPCN = false;
      bool StWPdRdFBo = false;
      bool DxoTgNGshG = false;
      bool ssOVUTKbAd = false;
      bool KDFiEWfKSN = false;
      bool WjiIpoJCrf = false;
      bool MthuUZeBuJ = false;
      bool HBEXdzqGOJ = false;
      bool huaTiJJGee = false;
      bool KIjTQQVJOe = false;
      bool rePIGUeLdq = false;
      bool xCmhyQSNML = false;
      bool PYVPzyRjGN = false;
      bool dgqjRCfSNN = false;
      bool dxcnhHUCVz = false;
      bool yHxDOSIzJH = false;
      bool DtFPMPKDPu = false;
      bool kzzygSwhhq = false;
      bool cPOGPWjnUy = false;
      string UJonrQYjjp;
      string nUlqYWqpGa;
      string kJHxJYyFHH;
      string iBjutcDuMq;
      string DULIayGZnk;
      string brjUiKCrdS;
      string STbcHmkpxw;
      string SwdPWPyyWK;
      string SXQWeqROLi;
      string aLQsXisiBn;
      string MPcrRfOTxS;
      string MDVTAtDEyQ;
      string UVeNUGejqn;
      string WOxixDuXFy;
      string cxRrVWpxsd;
      string fnjkSqjOWK;
      string BdcJwxGmVw;
      string yezzmXElry;
      string QhpMHhdMPG;
      string SgBtxyTHwX;
      if(UJonrQYjjp == MPcrRfOTxS){QCaweBokxt = true;}
      else if(MPcrRfOTxS == UJonrQYjjp){KIjTQQVJOe = true;}
      if(nUlqYWqpGa == MDVTAtDEyQ){lyVYtTnPCN = true;}
      else if(MDVTAtDEyQ == nUlqYWqpGa){rePIGUeLdq = true;}
      if(kJHxJYyFHH == UVeNUGejqn){StWPdRdFBo = true;}
      else if(UVeNUGejqn == kJHxJYyFHH){xCmhyQSNML = true;}
      if(iBjutcDuMq == WOxixDuXFy){DxoTgNGshG = true;}
      else if(WOxixDuXFy == iBjutcDuMq){PYVPzyRjGN = true;}
      if(DULIayGZnk == cxRrVWpxsd){ssOVUTKbAd = true;}
      else if(cxRrVWpxsd == DULIayGZnk){dgqjRCfSNN = true;}
      if(brjUiKCrdS == fnjkSqjOWK){KDFiEWfKSN = true;}
      else if(fnjkSqjOWK == brjUiKCrdS){dxcnhHUCVz = true;}
      if(STbcHmkpxw == BdcJwxGmVw){WjiIpoJCrf = true;}
      else if(BdcJwxGmVw == STbcHmkpxw){yHxDOSIzJH = true;}
      if(SwdPWPyyWK == yezzmXElry){MthuUZeBuJ = true;}
      if(SXQWeqROLi == QhpMHhdMPG){HBEXdzqGOJ = true;}
      if(aLQsXisiBn == SgBtxyTHwX){huaTiJJGee = true;}
      while(yezzmXElry == SwdPWPyyWK){DtFPMPKDPu = true;}
      while(QhpMHhdMPG == QhpMHhdMPG){kzzygSwhhq = true;}
      while(SgBtxyTHwX == SgBtxyTHwX){cPOGPWjnUy = true;}
      if(QCaweBokxt == true){QCaweBokxt = false;}
      if(lyVYtTnPCN == true){lyVYtTnPCN = false;}
      if(StWPdRdFBo == true){StWPdRdFBo = false;}
      if(DxoTgNGshG == true){DxoTgNGshG = false;}
      if(ssOVUTKbAd == true){ssOVUTKbAd = false;}
      if(KDFiEWfKSN == true){KDFiEWfKSN = false;}
      if(WjiIpoJCrf == true){WjiIpoJCrf = false;}
      if(MthuUZeBuJ == true){MthuUZeBuJ = false;}
      if(HBEXdzqGOJ == true){HBEXdzqGOJ = false;}
      if(huaTiJJGee == true){huaTiJJGee = false;}
      if(KIjTQQVJOe == true){KIjTQQVJOe = false;}
      if(rePIGUeLdq == true){rePIGUeLdq = false;}
      if(xCmhyQSNML == true){xCmhyQSNML = false;}
      if(PYVPzyRjGN == true){PYVPzyRjGN = false;}
      if(dgqjRCfSNN == true){dgqjRCfSNN = false;}
      if(dxcnhHUCVz == true){dxcnhHUCVz = false;}
      if(yHxDOSIzJH == true){yHxDOSIzJH = false;}
      if(DtFPMPKDPu == true){DtFPMPKDPu = false;}
      if(kzzygSwhhq == true){kzzygSwhhq = false;}
      if(cPOGPWjnUy == true){cPOGPWjnUy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWTYRQERUI
{ 
  void XZHAzwuQAu()
  { 
      bool QiWSpKUWFL = false;
      bool femoyRUmWN = false;
      bool qhRYrMAKeH = false;
      bool JSAlyYCrUI = false;
      bool LlwzNWSiBO = false;
      bool eNGDAiRxZd = false;
      bool KKqyBNdBqY = false;
      bool PbSNCEkRLV = false;
      bool sQJQcwLwkP = false;
      bool HFRqyBtyxA = false;
      bool rRrbzCtrBw = false;
      bool xzkEjsBaUF = false;
      bool BgPaRJJbPA = false;
      bool JmULcaXgQZ = false;
      bool CStoRHTNGE = false;
      bool ATcryKBQKo = false;
      bool rRbBlJeZaI = false;
      bool UTJtDhlaJJ = false;
      bool pwVLApKbMS = false;
      bool ZHWagjpsDH = false;
      string EupoXHuCAn;
      string XcnzcjfDRm;
      string IyhTkEGoBi;
      string SyzmqLsjYA;
      string uykUFVcumS;
      string DihlRGMWET;
      string BGBQVZcAHQ;
      string pudRrKMNNO;
      string aKBifjPNUk;
      string zVfFyoxTyf;
      string rcmWbHEQsH;
      string syJorpERkl;
      string JPeVQUPYSD;
      string MrOgVyXeHY;
      string ezTMrBLpMI;
      string jfiMVbxQFH;
      string qfypuAjbSt;
      string SZKMGKwSdP;
      string IZLKSgJBKs;
      string BGYzgzBdRr;
      if(EupoXHuCAn == rcmWbHEQsH){QiWSpKUWFL = true;}
      else if(rcmWbHEQsH == EupoXHuCAn){rRrbzCtrBw = true;}
      if(XcnzcjfDRm == syJorpERkl){femoyRUmWN = true;}
      else if(syJorpERkl == XcnzcjfDRm){xzkEjsBaUF = true;}
      if(IyhTkEGoBi == JPeVQUPYSD){qhRYrMAKeH = true;}
      else if(JPeVQUPYSD == IyhTkEGoBi){BgPaRJJbPA = true;}
      if(SyzmqLsjYA == MrOgVyXeHY){JSAlyYCrUI = true;}
      else if(MrOgVyXeHY == SyzmqLsjYA){JmULcaXgQZ = true;}
      if(uykUFVcumS == ezTMrBLpMI){LlwzNWSiBO = true;}
      else if(ezTMrBLpMI == uykUFVcumS){CStoRHTNGE = true;}
      if(DihlRGMWET == jfiMVbxQFH){eNGDAiRxZd = true;}
      else if(jfiMVbxQFH == DihlRGMWET){ATcryKBQKo = true;}
      if(BGBQVZcAHQ == qfypuAjbSt){KKqyBNdBqY = true;}
      else if(qfypuAjbSt == BGBQVZcAHQ){rRbBlJeZaI = true;}
      if(pudRrKMNNO == SZKMGKwSdP){PbSNCEkRLV = true;}
      if(aKBifjPNUk == IZLKSgJBKs){sQJQcwLwkP = true;}
      if(zVfFyoxTyf == BGYzgzBdRr){HFRqyBtyxA = true;}
      while(SZKMGKwSdP == pudRrKMNNO){UTJtDhlaJJ = true;}
      while(IZLKSgJBKs == IZLKSgJBKs){pwVLApKbMS = true;}
      while(BGYzgzBdRr == BGYzgzBdRr){ZHWagjpsDH = true;}
      if(QiWSpKUWFL == true){QiWSpKUWFL = false;}
      if(femoyRUmWN == true){femoyRUmWN = false;}
      if(qhRYrMAKeH == true){qhRYrMAKeH = false;}
      if(JSAlyYCrUI == true){JSAlyYCrUI = false;}
      if(LlwzNWSiBO == true){LlwzNWSiBO = false;}
      if(eNGDAiRxZd == true){eNGDAiRxZd = false;}
      if(KKqyBNdBqY == true){KKqyBNdBqY = false;}
      if(PbSNCEkRLV == true){PbSNCEkRLV = false;}
      if(sQJQcwLwkP == true){sQJQcwLwkP = false;}
      if(HFRqyBtyxA == true){HFRqyBtyxA = false;}
      if(rRrbzCtrBw == true){rRrbzCtrBw = false;}
      if(xzkEjsBaUF == true){xzkEjsBaUF = false;}
      if(BgPaRJJbPA == true){BgPaRJJbPA = false;}
      if(JmULcaXgQZ == true){JmULcaXgQZ = false;}
      if(CStoRHTNGE == true){CStoRHTNGE = false;}
      if(ATcryKBQKo == true){ATcryKBQKo = false;}
      if(rRbBlJeZaI == true){rRbBlJeZaI = false;}
      if(UTJtDhlaJJ == true){UTJtDhlaJJ = false;}
      if(pwVLApKbMS == true){pwVLApKbMS = false;}
      if(ZHWagjpsDH == true){ZHWagjpsDH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RLDDSOLNQZ
{ 
  void ZqKCGzCqNN()
  { 
      bool yFKytpRbyo = false;
      bool JbebRMcZBn = false;
      bool GaoBdQmVNb = false;
      bool dPNZKWlnBH = false;
      bool PUFrVFcxoe = false;
      bool IxVnhWQJTd = false;
      bool CwNWKsNFQt = false;
      bool aoYsXkVxeX = false;
      bool noghSgtZqm = false;
      bool FbTWETGhgc = false;
      bool rXgtESXbQw = false;
      bool BTdwpNPfDd = false;
      bool ynNdnyVBnD = false;
      bool emQCfPIlcz = false;
      bool ISJtllyXgq = false;
      bool EZeCdEKCFG = false;
      bool xWnMRNDaPZ = false;
      bool FcDDVfdSrC = false;
      bool AyTwzEINXb = false;
      bool FFgVCkdxcX = false;
      string KmoBUtUKqS;
      string FXcwXKZFaC;
      string BMyfNAWQfk;
      string obtrUMgloQ;
      string cCtFRhrYid;
      string kbuYwynJmT;
      string XEeGccdkbL;
      string dmQJZyRrNf;
      string HxgBzNgUwW;
      string YXzUsYWncn;
      string EHxWAxLlzx;
      string fuuHLZWcGP;
      string wIoElFnuPA;
      string adPYaAAJBB;
      string BtVyqcbqJT;
      string CsgMqwSrkt;
      string JPVzVCeWfL;
      string YMbFNCmpNI;
      string cxlwxhwDge;
      string hHYGrlXWbn;
      if(KmoBUtUKqS == EHxWAxLlzx){yFKytpRbyo = true;}
      else if(EHxWAxLlzx == KmoBUtUKqS){rXgtESXbQw = true;}
      if(FXcwXKZFaC == fuuHLZWcGP){JbebRMcZBn = true;}
      else if(fuuHLZWcGP == FXcwXKZFaC){BTdwpNPfDd = true;}
      if(BMyfNAWQfk == wIoElFnuPA){GaoBdQmVNb = true;}
      else if(wIoElFnuPA == BMyfNAWQfk){ynNdnyVBnD = true;}
      if(obtrUMgloQ == adPYaAAJBB){dPNZKWlnBH = true;}
      else if(adPYaAAJBB == obtrUMgloQ){emQCfPIlcz = true;}
      if(cCtFRhrYid == BtVyqcbqJT){PUFrVFcxoe = true;}
      else if(BtVyqcbqJT == cCtFRhrYid){ISJtllyXgq = true;}
      if(kbuYwynJmT == CsgMqwSrkt){IxVnhWQJTd = true;}
      else if(CsgMqwSrkt == kbuYwynJmT){EZeCdEKCFG = true;}
      if(XEeGccdkbL == JPVzVCeWfL){CwNWKsNFQt = true;}
      else if(JPVzVCeWfL == XEeGccdkbL){xWnMRNDaPZ = true;}
      if(dmQJZyRrNf == YMbFNCmpNI){aoYsXkVxeX = true;}
      if(HxgBzNgUwW == cxlwxhwDge){noghSgtZqm = true;}
      if(YXzUsYWncn == hHYGrlXWbn){FbTWETGhgc = true;}
      while(YMbFNCmpNI == dmQJZyRrNf){FcDDVfdSrC = true;}
      while(cxlwxhwDge == cxlwxhwDge){AyTwzEINXb = true;}
      while(hHYGrlXWbn == hHYGrlXWbn){FFgVCkdxcX = true;}
      if(yFKytpRbyo == true){yFKytpRbyo = false;}
      if(JbebRMcZBn == true){JbebRMcZBn = false;}
      if(GaoBdQmVNb == true){GaoBdQmVNb = false;}
      if(dPNZKWlnBH == true){dPNZKWlnBH = false;}
      if(PUFrVFcxoe == true){PUFrVFcxoe = false;}
      if(IxVnhWQJTd == true){IxVnhWQJTd = false;}
      if(CwNWKsNFQt == true){CwNWKsNFQt = false;}
      if(aoYsXkVxeX == true){aoYsXkVxeX = false;}
      if(noghSgtZqm == true){noghSgtZqm = false;}
      if(FbTWETGhgc == true){FbTWETGhgc = false;}
      if(rXgtESXbQw == true){rXgtESXbQw = false;}
      if(BTdwpNPfDd == true){BTdwpNPfDd = false;}
      if(ynNdnyVBnD == true){ynNdnyVBnD = false;}
      if(emQCfPIlcz == true){emQCfPIlcz = false;}
      if(ISJtllyXgq == true){ISJtllyXgq = false;}
      if(EZeCdEKCFG == true){EZeCdEKCFG = false;}
      if(xWnMRNDaPZ == true){xWnMRNDaPZ = false;}
      if(FcDDVfdSrC == true){FcDDVfdSrC = false;}
      if(AyTwzEINXb == true){AyTwzEINXb = false;}
      if(FFgVCkdxcX == true){FFgVCkdxcX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKGUTHBFMP
{ 
  void uyBxiqCeig()
  { 
      bool ulxbPKjyWo = false;
      bool iMqUoRcqeb = false;
      bool QChWOOwLOd = false;
      bool NbqEuGFjFg = false;
      bool hMVRtzKddc = false;
      bool DwSbDsEaMB = false;
      bool NXirbHVmYh = false;
      bool LskysDfPbO = false;
      bool DRhlaQIOAC = false;
      bool CeWESJccpm = false;
      bool dWFwRKKUiA = false;
      bool MozxxupxRL = false;
      bool yGmWfgVgfi = false;
      bool ZCYnkgMlUQ = false;
      bool FneAoNeYGW = false;
      bool TfLeoWjhPk = false;
      bool ndnzZKPKMQ = false;
      bool iDbAFJalgS = false;
      bool BwaJPsqtzN = false;
      bool wdVjbbzfZe = false;
      string rKtTEgAbMn;
      string YGDANjMVRg;
      string KtCLkpxprA;
      string kCUhoUzWKz;
      string WfsORqVuln;
      string MNieGxIiiO;
      string jJjLCWkULs;
      string koKSKdBmtt;
      string TBDDmXSoaq;
      string LQmwPMugMu;
      string FBisCWCQUc;
      string uVnothGfYe;
      string DusTgUCNDy;
      string hTZznSRKBP;
      string UBUyupbyCg;
      string GPIgqJHPLh;
      string UnNWtbuoAa;
      string QueJKBauXq;
      string sDLVqSLsHd;
      string LCyStfnyET;
      if(rKtTEgAbMn == FBisCWCQUc){ulxbPKjyWo = true;}
      else if(FBisCWCQUc == rKtTEgAbMn){dWFwRKKUiA = true;}
      if(YGDANjMVRg == uVnothGfYe){iMqUoRcqeb = true;}
      else if(uVnothGfYe == YGDANjMVRg){MozxxupxRL = true;}
      if(KtCLkpxprA == DusTgUCNDy){QChWOOwLOd = true;}
      else if(DusTgUCNDy == KtCLkpxprA){yGmWfgVgfi = true;}
      if(kCUhoUzWKz == hTZznSRKBP){NbqEuGFjFg = true;}
      else if(hTZznSRKBP == kCUhoUzWKz){ZCYnkgMlUQ = true;}
      if(WfsORqVuln == UBUyupbyCg){hMVRtzKddc = true;}
      else if(UBUyupbyCg == WfsORqVuln){FneAoNeYGW = true;}
      if(MNieGxIiiO == GPIgqJHPLh){DwSbDsEaMB = true;}
      else if(GPIgqJHPLh == MNieGxIiiO){TfLeoWjhPk = true;}
      if(jJjLCWkULs == UnNWtbuoAa){NXirbHVmYh = true;}
      else if(UnNWtbuoAa == jJjLCWkULs){ndnzZKPKMQ = true;}
      if(koKSKdBmtt == QueJKBauXq){LskysDfPbO = true;}
      if(TBDDmXSoaq == sDLVqSLsHd){DRhlaQIOAC = true;}
      if(LQmwPMugMu == LCyStfnyET){CeWESJccpm = true;}
      while(QueJKBauXq == koKSKdBmtt){iDbAFJalgS = true;}
      while(sDLVqSLsHd == sDLVqSLsHd){BwaJPsqtzN = true;}
      while(LCyStfnyET == LCyStfnyET){wdVjbbzfZe = true;}
      if(ulxbPKjyWo == true){ulxbPKjyWo = false;}
      if(iMqUoRcqeb == true){iMqUoRcqeb = false;}
      if(QChWOOwLOd == true){QChWOOwLOd = false;}
      if(NbqEuGFjFg == true){NbqEuGFjFg = false;}
      if(hMVRtzKddc == true){hMVRtzKddc = false;}
      if(DwSbDsEaMB == true){DwSbDsEaMB = false;}
      if(NXirbHVmYh == true){NXirbHVmYh = false;}
      if(LskysDfPbO == true){LskysDfPbO = false;}
      if(DRhlaQIOAC == true){DRhlaQIOAC = false;}
      if(CeWESJccpm == true){CeWESJccpm = false;}
      if(dWFwRKKUiA == true){dWFwRKKUiA = false;}
      if(MozxxupxRL == true){MozxxupxRL = false;}
      if(yGmWfgVgfi == true){yGmWfgVgfi = false;}
      if(ZCYnkgMlUQ == true){ZCYnkgMlUQ = false;}
      if(FneAoNeYGW == true){FneAoNeYGW = false;}
      if(TfLeoWjhPk == true){TfLeoWjhPk = false;}
      if(ndnzZKPKMQ == true){ndnzZKPKMQ = false;}
      if(iDbAFJalgS == true){iDbAFJalgS = false;}
      if(BwaJPsqtzN == true){BwaJPsqtzN = false;}
      if(wdVjbbzfZe == true){wdVjbbzfZe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HBGKAXSKAG
{ 
  void HxWOWnjYny()
  { 
      bool xZRQDWUaUp = false;
      bool eOkZPRMDYw = false;
      bool gSKISfjHlr = false;
      bool lEnBtxKWTt = false;
      bool bSmehMoRIU = false;
      bool acJPbdPJxW = false;
      bool mMncDaajfS = false;
      bool GoidTOfeaG = false;
      bool qSyQRJuXYP = false;
      bool gBYwHOdJaH = false;
      bool lFkpOksewM = false;
      bool xkhqfTNXKt = false;
      bool eCKPlFPmWE = false;
      bool jVDSUkgICf = false;
      bool PPaMRuShPm = false;
      bool BFzfbiuUEI = false;
      bool VGIqcbhPVt = false;
      bool mFUeePayyp = false;
      bool lgWiDdWWpl = false;
      bool pLEsKIHjip = false;
      string XJRAfZaINr;
      string mhiRpmNqoL;
      string GFAqkiqznN;
      string lungVRrFtU;
      string LOFZbZWiHL;
      string TxdHjSJZOx;
      string ibUzGrtCuY;
      string uIxUzrzaOL;
      string LHqbsnQgwC;
      string HRqxlitGSj;
      string fUmhQLAJHq;
      string TiKCkajrGS;
      string aMFsQdQzhQ;
      string ysHefpUILg;
      string mHZFiYGnLK;
      string yBzAJSOtRm;
      string tAaqsZafVt;
      string GagYeSmAJr;
      string WcnXRxsHVN;
      string aZqYmmfiMI;
      if(XJRAfZaINr == fUmhQLAJHq){xZRQDWUaUp = true;}
      else if(fUmhQLAJHq == XJRAfZaINr){lFkpOksewM = true;}
      if(mhiRpmNqoL == TiKCkajrGS){eOkZPRMDYw = true;}
      else if(TiKCkajrGS == mhiRpmNqoL){xkhqfTNXKt = true;}
      if(GFAqkiqznN == aMFsQdQzhQ){gSKISfjHlr = true;}
      else if(aMFsQdQzhQ == GFAqkiqznN){eCKPlFPmWE = true;}
      if(lungVRrFtU == ysHefpUILg){lEnBtxKWTt = true;}
      else if(ysHefpUILg == lungVRrFtU){jVDSUkgICf = true;}
      if(LOFZbZWiHL == mHZFiYGnLK){bSmehMoRIU = true;}
      else if(mHZFiYGnLK == LOFZbZWiHL){PPaMRuShPm = true;}
      if(TxdHjSJZOx == yBzAJSOtRm){acJPbdPJxW = true;}
      else if(yBzAJSOtRm == TxdHjSJZOx){BFzfbiuUEI = true;}
      if(ibUzGrtCuY == tAaqsZafVt){mMncDaajfS = true;}
      else if(tAaqsZafVt == ibUzGrtCuY){VGIqcbhPVt = true;}
      if(uIxUzrzaOL == GagYeSmAJr){GoidTOfeaG = true;}
      if(LHqbsnQgwC == WcnXRxsHVN){qSyQRJuXYP = true;}
      if(HRqxlitGSj == aZqYmmfiMI){gBYwHOdJaH = true;}
      while(GagYeSmAJr == uIxUzrzaOL){mFUeePayyp = true;}
      while(WcnXRxsHVN == WcnXRxsHVN){lgWiDdWWpl = true;}
      while(aZqYmmfiMI == aZqYmmfiMI){pLEsKIHjip = true;}
      if(xZRQDWUaUp == true){xZRQDWUaUp = false;}
      if(eOkZPRMDYw == true){eOkZPRMDYw = false;}
      if(gSKISfjHlr == true){gSKISfjHlr = false;}
      if(lEnBtxKWTt == true){lEnBtxKWTt = false;}
      if(bSmehMoRIU == true){bSmehMoRIU = false;}
      if(acJPbdPJxW == true){acJPbdPJxW = false;}
      if(mMncDaajfS == true){mMncDaajfS = false;}
      if(GoidTOfeaG == true){GoidTOfeaG = false;}
      if(qSyQRJuXYP == true){qSyQRJuXYP = false;}
      if(gBYwHOdJaH == true){gBYwHOdJaH = false;}
      if(lFkpOksewM == true){lFkpOksewM = false;}
      if(xkhqfTNXKt == true){xkhqfTNXKt = false;}
      if(eCKPlFPmWE == true){eCKPlFPmWE = false;}
      if(jVDSUkgICf == true){jVDSUkgICf = false;}
      if(PPaMRuShPm == true){PPaMRuShPm = false;}
      if(BFzfbiuUEI == true){BFzfbiuUEI = false;}
      if(VGIqcbhPVt == true){VGIqcbhPVt = false;}
      if(mFUeePayyp == true){mFUeePayyp = false;}
      if(lgWiDdWWpl == true){lgWiDdWWpl = false;}
      if(pLEsKIHjip == true){pLEsKIHjip = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKGNXORTJF
{ 
  void eQBAsElsrn()
  { 
      bool ACTLKWCyqI = false;
      bool xrnPfxRIMC = false;
      bool xIwCJFtGTu = false;
      bool OLfQnBKznj = false;
      bool VTbFHrKFNy = false;
      bool BDmNMrFRBE = false;
      bool budutkLXbe = false;
      bool lSUbfcgqtR = false;
      bool uorVsKYSDu = false;
      bool wsxiIZofKW = false;
      bool fldiLihKgj = false;
      bool LNXjIlDHCi = false;
      bool MsUfhsVkTF = false;
      bool nAfXkJLIKK = false;
      bool bNkTjhVMZV = false;
      bool WgdaJmRxAR = false;
      bool MxqauLhzzz = false;
      bool atxqHyHBwA = false;
      bool XIKxiGVFNx = false;
      bool qNIrxeWKXX = false;
      string PCetbNAqrd;
      string xmlXLAgifn;
      string HiLrQIPMbw;
      string bMVFBSKbrg;
      string QxzUPJHlPs;
      string nkUlMfpldS;
      string ymOwCkRfVs;
      string pEpyXJjqcG;
      string AdxiHqqisV;
      string bXyYiciDRd;
      string raPVDitWOC;
      string wzJWSTpfnL;
      string thmAQSGQOt;
      string agYyOYOaeX;
      string wTUqYbNbGP;
      string mCOGiJnPFk;
      string ccHUaOaLHt;
      string EPAPOaMwao;
      string EeKzHXRSOF;
      string jzUtuTLAPK;
      if(PCetbNAqrd == raPVDitWOC){ACTLKWCyqI = true;}
      else if(raPVDitWOC == PCetbNAqrd){fldiLihKgj = true;}
      if(xmlXLAgifn == wzJWSTpfnL){xrnPfxRIMC = true;}
      else if(wzJWSTpfnL == xmlXLAgifn){LNXjIlDHCi = true;}
      if(HiLrQIPMbw == thmAQSGQOt){xIwCJFtGTu = true;}
      else if(thmAQSGQOt == HiLrQIPMbw){MsUfhsVkTF = true;}
      if(bMVFBSKbrg == agYyOYOaeX){OLfQnBKznj = true;}
      else if(agYyOYOaeX == bMVFBSKbrg){nAfXkJLIKK = true;}
      if(QxzUPJHlPs == wTUqYbNbGP){VTbFHrKFNy = true;}
      else if(wTUqYbNbGP == QxzUPJHlPs){bNkTjhVMZV = true;}
      if(nkUlMfpldS == mCOGiJnPFk){BDmNMrFRBE = true;}
      else if(mCOGiJnPFk == nkUlMfpldS){WgdaJmRxAR = true;}
      if(ymOwCkRfVs == ccHUaOaLHt){budutkLXbe = true;}
      else if(ccHUaOaLHt == ymOwCkRfVs){MxqauLhzzz = true;}
      if(pEpyXJjqcG == EPAPOaMwao){lSUbfcgqtR = true;}
      if(AdxiHqqisV == EeKzHXRSOF){uorVsKYSDu = true;}
      if(bXyYiciDRd == jzUtuTLAPK){wsxiIZofKW = true;}
      while(EPAPOaMwao == pEpyXJjqcG){atxqHyHBwA = true;}
      while(EeKzHXRSOF == EeKzHXRSOF){XIKxiGVFNx = true;}
      while(jzUtuTLAPK == jzUtuTLAPK){qNIrxeWKXX = true;}
      if(ACTLKWCyqI == true){ACTLKWCyqI = false;}
      if(xrnPfxRIMC == true){xrnPfxRIMC = false;}
      if(xIwCJFtGTu == true){xIwCJFtGTu = false;}
      if(OLfQnBKznj == true){OLfQnBKznj = false;}
      if(VTbFHrKFNy == true){VTbFHrKFNy = false;}
      if(BDmNMrFRBE == true){BDmNMrFRBE = false;}
      if(budutkLXbe == true){budutkLXbe = false;}
      if(lSUbfcgqtR == true){lSUbfcgqtR = false;}
      if(uorVsKYSDu == true){uorVsKYSDu = false;}
      if(wsxiIZofKW == true){wsxiIZofKW = false;}
      if(fldiLihKgj == true){fldiLihKgj = false;}
      if(LNXjIlDHCi == true){LNXjIlDHCi = false;}
      if(MsUfhsVkTF == true){MsUfhsVkTF = false;}
      if(nAfXkJLIKK == true){nAfXkJLIKK = false;}
      if(bNkTjhVMZV == true){bNkTjhVMZV = false;}
      if(WgdaJmRxAR == true){WgdaJmRxAR = false;}
      if(MxqauLhzzz == true){MxqauLhzzz = false;}
      if(atxqHyHBwA == true){atxqHyHBwA = false;}
      if(XIKxiGVFNx == true){XIKxiGVFNx = false;}
      if(qNIrxeWKXX == true){qNIrxeWKXX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YGYITIXXDI
{ 
  void CyDardVmDU()
  { 
      bool sLqSGLeCWX = false;
      bool GihIPRkGLL = false;
      bool PsbDrzGkrH = false;
      bool BIplmhAUCh = false;
      bool kcPihFCRTZ = false;
      bool cEHeQzjmZH = false;
      bool EsJPWxruUg = false;
      bool RPDdZldsVm = false;
      bool xnQSdwBKVn = false;
      bool yMtucqTAMj = false;
      bool MHxlHMBcFe = false;
      bool VpRlKPbqkZ = false;
      bool uhZfiFVIBh = false;
      bool ScfkaoqeKR = false;
      bool uYFpSHtHkM = false;
      bool ObOlodhRCC = false;
      bool qrbWLrKgLU = false;
      bool YxgTeWbiNb = false;
      bool KNWnTpNtww = false;
      bool HZbHZCwheZ = false;
      string uZFYAUFANg;
      string uwjfXQkOYU;
      string pphQFtQzxo;
      string cQfbtdHPqO;
      string uPxCCzYhnG;
      string EgZQRFrnTG;
      string DGDXDePIks;
      string IVWKZareOF;
      string UhKpkwqPJo;
      string lTwkKnLZzX;
      string iPxuyiKPqq;
      string NMYNkUwMmG;
      string nAzuGnYlzk;
      string PRfpWEkOrB;
      string laXSbZthzp;
      string rzmrjhQBoJ;
      string JXPFbugiqg;
      string igTkUMbgTg;
      string tqmJsPemGn;
      string njZirNLSqg;
      if(uZFYAUFANg == iPxuyiKPqq){sLqSGLeCWX = true;}
      else if(iPxuyiKPqq == uZFYAUFANg){MHxlHMBcFe = true;}
      if(uwjfXQkOYU == NMYNkUwMmG){GihIPRkGLL = true;}
      else if(NMYNkUwMmG == uwjfXQkOYU){VpRlKPbqkZ = true;}
      if(pphQFtQzxo == nAzuGnYlzk){PsbDrzGkrH = true;}
      else if(nAzuGnYlzk == pphQFtQzxo){uhZfiFVIBh = true;}
      if(cQfbtdHPqO == PRfpWEkOrB){BIplmhAUCh = true;}
      else if(PRfpWEkOrB == cQfbtdHPqO){ScfkaoqeKR = true;}
      if(uPxCCzYhnG == laXSbZthzp){kcPihFCRTZ = true;}
      else if(laXSbZthzp == uPxCCzYhnG){uYFpSHtHkM = true;}
      if(EgZQRFrnTG == rzmrjhQBoJ){cEHeQzjmZH = true;}
      else if(rzmrjhQBoJ == EgZQRFrnTG){ObOlodhRCC = true;}
      if(DGDXDePIks == JXPFbugiqg){EsJPWxruUg = true;}
      else if(JXPFbugiqg == DGDXDePIks){qrbWLrKgLU = true;}
      if(IVWKZareOF == igTkUMbgTg){RPDdZldsVm = true;}
      if(UhKpkwqPJo == tqmJsPemGn){xnQSdwBKVn = true;}
      if(lTwkKnLZzX == njZirNLSqg){yMtucqTAMj = true;}
      while(igTkUMbgTg == IVWKZareOF){YxgTeWbiNb = true;}
      while(tqmJsPemGn == tqmJsPemGn){KNWnTpNtww = true;}
      while(njZirNLSqg == njZirNLSqg){HZbHZCwheZ = true;}
      if(sLqSGLeCWX == true){sLqSGLeCWX = false;}
      if(GihIPRkGLL == true){GihIPRkGLL = false;}
      if(PsbDrzGkrH == true){PsbDrzGkrH = false;}
      if(BIplmhAUCh == true){BIplmhAUCh = false;}
      if(kcPihFCRTZ == true){kcPihFCRTZ = false;}
      if(cEHeQzjmZH == true){cEHeQzjmZH = false;}
      if(EsJPWxruUg == true){EsJPWxruUg = false;}
      if(RPDdZldsVm == true){RPDdZldsVm = false;}
      if(xnQSdwBKVn == true){xnQSdwBKVn = false;}
      if(yMtucqTAMj == true){yMtucqTAMj = false;}
      if(MHxlHMBcFe == true){MHxlHMBcFe = false;}
      if(VpRlKPbqkZ == true){VpRlKPbqkZ = false;}
      if(uhZfiFVIBh == true){uhZfiFVIBh = false;}
      if(ScfkaoqeKR == true){ScfkaoqeKR = false;}
      if(uYFpSHtHkM == true){uYFpSHtHkM = false;}
      if(ObOlodhRCC == true){ObOlodhRCC = false;}
      if(qrbWLrKgLU == true){qrbWLrKgLU = false;}
      if(YxgTeWbiNb == true){YxgTeWbiNb = false;}
      if(KNWnTpNtww == true){KNWnTpNtww = false;}
      if(HZbHZCwheZ == true){HZbHZCwheZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEGCWGWUXO
{ 
  void UxEglcSmrg()
  { 
      bool AsHxGymAJq = false;
      bool CiLLbDODQc = false;
      bool bLLGmUnzCo = false;
      bool iCWWOTSkKF = false;
      bool qRAAgqyySS = false;
      bool zsFxOngAKl = false;
      bool KmyTIALoxI = false;
      bool kcsKlJLLZu = false;
      bool VogjooxZHZ = false;
      bool lRaXtDTfrg = false;
      bool eJBKhWAtLF = false;
      bool cVaOPUGOeS = false;
      bool DlgWWSCUPh = false;
      bool oeTrPMnVBS = false;
      bool oCNBxQpLIZ = false;
      bool xFBYcscdmO = false;
      bool TedcPxBhyD = false;
      bool fjMLcAXeYF = false;
      bool bqMpkidtPW = false;
      bool iKimzJYkkA = false;
      string xgMSTTqbIc;
      string IoyZFDgwWw;
      string LSoDPbAJKg;
      string NSOIDFaFXT;
      string OgapOOEtLa;
      string dNbDBeqJDr;
      string ThQbOpZoWz;
      string baXDhdqyoA;
      string WFxjCApLHX;
      string ORCezgPybX;
      string oPWLzCoXVW;
      string mrUCUNjgYO;
      string zNhykJYrDA;
      string OrWQLHikkz;
      string KSpjkVxzKl;
      string wiZNYagYao;
      string cwUUItVDqM;
      string eyuYDgXyNO;
      string MZhQEeSJrj;
      string ZJKuVNxVap;
      if(xgMSTTqbIc == oPWLzCoXVW){AsHxGymAJq = true;}
      else if(oPWLzCoXVW == xgMSTTqbIc){eJBKhWAtLF = true;}
      if(IoyZFDgwWw == mrUCUNjgYO){CiLLbDODQc = true;}
      else if(mrUCUNjgYO == IoyZFDgwWw){cVaOPUGOeS = true;}
      if(LSoDPbAJKg == zNhykJYrDA){bLLGmUnzCo = true;}
      else if(zNhykJYrDA == LSoDPbAJKg){DlgWWSCUPh = true;}
      if(NSOIDFaFXT == OrWQLHikkz){iCWWOTSkKF = true;}
      else if(OrWQLHikkz == NSOIDFaFXT){oeTrPMnVBS = true;}
      if(OgapOOEtLa == KSpjkVxzKl){qRAAgqyySS = true;}
      else if(KSpjkVxzKl == OgapOOEtLa){oCNBxQpLIZ = true;}
      if(dNbDBeqJDr == wiZNYagYao){zsFxOngAKl = true;}
      else if(wiZNYagYao == dNbDBeqJDr){xFBYcscdmO = true;}
      if(ThQbOpZoWz == cwUUItVDqM){KmyTIALoxI = true;}
      else if(cwUUItVDqM == ThQbOpZoWz){TedcPxBhyD = true;}
      if(baXDhdqyoA == eyuYDgXyNO){kcsKlJLLZu = true;}
      if(WFxjCApLHX == MZhQEeSJrj){VogjooxZHZ = true;}
      if(ORCezgPybX == ZJKuVNxVap){lRaXtDTfrg = true;}
      while(eyuYDgXyNO == baXDhdqyoA){fjMLcAXeYF = true;}
      while(MZhQEeSJrj == MZhQEeSJrj){bqMpkidtPW = true;}
      while(ZJKuVNxVap == ZJKuVNxVap){iKimzJYkkA = true;}
      if(AsHxGymAJq == true){AsHxGymAJq = false;}
      if(CiLLbDODQc == true){CiLLbDODQc = false;}
      if(bLLGmUnzCo == true){bLLGmUnzCo = false;}
      if(iCWWOTSkKF == true){iCWWOTSkKF = false;}
      if(qRAAgqyySS == true){qRAAgqyySS = false;}
      if(zsFxOngAKl == true){zsFxOngAKl = false;}
      if(KmyTIALoxI == true){KmyTIALoxI = false;}
      if(kcsKlJLLZu == true){kcsKlJLLZu = false;}
      if(VogjooxZHZ == true){VogjooxZHZ = false;}
      if(lRaXtDTfrg == true){lRaXtDTfrg = false;}
      if(eJBKhWAtLF == true){eJBKhWAtLF = false;}
      if(cVaOPUGOeS == true){cVaOPUGOeS = false;}
      if(DlgWWSCUPh == true){DlgWWSCUPh = false;}
      if(oeTrPMnVBS == true){oeTrPMnVBS = false;}
      if(oCNBxQpLIZ == true){oCNBxQpLIZ = false;}
      if(xFBYcscdmO == true){xFBYcscdmO = false;}
      if(TedcPxBhyD == true){TedcPxBhyD = false;}
      if(fjMLcAXeYF == true){fjMLcAXeYF = false;}
      if(bqMpkidtPW == true){bqMpkidtPW = false;}
      if(iKimzJYkkA == true){iKimzJYkkA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCRBVPWOIM
{ 
  void kAIoUbCttB()
  { 
      bool GEkGKYBoXj = false;
      bool hbsrFpBhfQ = false;
      bool RwqSNPTkLb = false;
      bool ChgnPKEZFL = false;
      bool NUXlmMEJkD = false;
      bool EohWnJMRrt = false;
      bool EPcuhAuEct = false;
      bool kbcUCxXFeB = false;
      bool KJAIXNzKAG = false;
      bool ymgKGxqcEm = false;
      bool QzgpRbLMTp = false;
      bool kGmqiuOUXT = false;
      bool AkEVwyuSOE = false;
      bool FuBrjLbKqu = false;
      bool BlpJUqApbK = false;
      bool iWFjlfuKsS = false;
      bool gsyPjpFuGX = false;
      bool SEcbRNutBE = false;
      bool yEpDVipRFE = false;
      bool PRQXNInZYd = false;
      string VYYIrwjKBJ;
      string FhLNljstdg;
      string gJwsMjzxIz;
      string YCgfZWqMGT;
      string TUcOHFPByt;
      string cLuHmMcfwI;
      string wlCCjCAfmO;
      string rfnJMMfglG;
      string UyzNWMGZsM;
      string tLQxWhSadF;
      string FiNiCwXkuZ;
      string futpnymnfX;
      string uamZUgPpme;
      string tECfBkkQLZ;
      string nVdSgyRZJX;
      string tduGJewmOU;
      string fhyPfarNoC;
      string NVbFiZwTsV;
      string OpfPjPJwVV;
      string oxCpsGWNmF;
      if(VYYIrwjKBJ == FiNiCwXkuZ){GEkGKYBoXj = true;}
      else if(FiNiCwXkuZ == VYYIrwjKBJ){QzgpRbLMTp = true;}
      if(FhLNljstdg == futpnymnfX){hbsrFpBhfQ = true;}
      else if(futpnymnfX == FhLNljstdg){kGmqiuOUXT = true;}
      if(gJwsMjzxIz == uamZUgPpme){RwqSNPTkLb = true;}
      else if(uamZUgPpme == gJwsMjzxIz){AkEVwyuSOE = true;}
      if(YCgfZWqMGT == tECfBkkQLZ){ChgnPKEZFL = true;}
      else if(tECfBkkQLZ == YCgfZWqMGT){FuBrjLbKqu = true;}
      if(TUcOHFPByt == nVdSgyRZJX){NUXlmMEJkD = true;}
      else if(nVdSgyRZJX == TUcOHFPByt){BlpJUqApbK = true;}
      if(cLuHmMcfwI == tduGJewmOU){EohWnJMRrt = true;}
      else if(tduGJewmOU == cLuHmMcfwI){iWFjlfuKsS = true;}
      if(wlCCjCAfmO == fhyPfarNoC){EPcuhAuEct = true;}
      else if(fhyPfarNoC == wlCCjCAfmO){gsyPjpFuGX = true;}
      if(rfnJMMfglG == NVbFiZwTsV){kbcUCxXFeB = true;}
      if(UyzNWMGZsM == OpfPjPJwVV){KJAIXNzKAG = true;}
      if(tLQxWhSadF == oxCpsGWNmF){ymgKGxqcEm = true;}
      while(NVbFiZwTsV == rfnJMMfglG){SEcbRNutBE = true;}
      while(OpfPjPJwVV == OpfPjPJwVV){yEpDVipRFE = true;}
      while(oxCpsGWNmF == oxCpsGWNmF){PRQXNInZYd = true;}
      if(GEkGKYBoXj == true){GEkGKYBoXj = false;}
      if(hbsrFpBhfQ == true){hbsrFpBhfQ = false;}
      if(RwqSNPTkLb == true){RwqSNPTkLb = false;}
      if(ChgnPKEZFL == true){ChgnPKEZFL = false;}
      if(NUXlmMEJkD == true){NUXlmMEJkD = false;}
      if(EohWnJMRrt == true){EohWnJMRrt = false;}
      if(EPcuhAuEct == true){EPcuhAuEct = false;}
      if(kbcUCxXFeB == true){kbcUCxXFeB = false;}
      if(KJAIXNzKAG == true){KJAIXNzKAG = false;}
      if(ymgKGxqcEm == true){ymgKGxqcEm = false;}
      if(QzgpRbLMTp == true){QzgpRbLMTp = false;}
      if(kGmqiuOUXT == true){kGmqiuOUXT = false;}
      if(AkEVwyuSOE == true){AkEVwyuSOE = false;}
      if(FuBrjLbKqu == true){FuBrjLbKqu = false;}
      if(BlpJUqApbK == true){BlpJUqApbK = false;}
      if(iWFjlfuKsS == true){iWFjlfuKsS = false;}
      if(gsyPjpFuGX == true){gsyPjpFuGX = false;}
      if(SEcbRNutBE == true){SEcbRNutBE = false;}
      if(yEpDVipRFE == true){yEpDVipRFE = false;}
      if(PRQXNInZYd == true){PRQXNInZYd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZFWYBCRKVH
{ 
  void tsfFEhxmlP()
  { 
      bool MYzZjBJygd = false;
      bool hFzAxUyiYo = false;
      bool cdsxzNZRQc = false;
      bool zmlrjHVkCi = false;
      bool saWgXiwyNY = false;
      bool uIfKchfBZW = false;
      bool argEdtSHQo = false;
      bool zMgowBHMYP = false;
      bool RbErgqGbPB = false;
      bool bTLeIBtRCc = false;
      bool PnhXYhbqNa = false;
      bool aTbJFznoXm = false;
      bool nqrONfBBgt = false;
      bool HpJwActfSy = false;
      bool OONnaIqCZI = false;
      bool NEtOnYwSKs = false;
      bool gZKSSjJfJc = false;
      bool FHVYXYdDmF = false;
      bool nzbXgDwtHa = false;
      bool faUZRoDtVq = false;
      string DzmgDNWlHj;
      string REPWuToLbP;
      string zfXAkgKLoQ;
      string ZwNHTOygEz;
      string HDsluXdKXJ;
      string UofceXbmwW;
      string DKxpJVpHDf;
      string UIGcIwlkEM;
      string CAnewkQjcu;
      string mLkhwwFDcZ;
      string gWGqoMhCUi;
      string lqhiTCVStY;
      string EGeIsJWYfL;
      string piIeffsxpi;
      string CNOsJucCNs;
      string amIDUZqyye;
      string oIVJsDiDDn;
      string IYcKVqrlyx;
      string gUKmkDZEKF;
      string nuyKssqEAG;
      if(DzmgDNWlHj == gWGqoMhCUi){MYzZjBJygd = true;}
      else if(gWGqoMhCUi == DzmgDNWlHj){PnhXYhbqNa = true;}
      if(REPWuToLbP == lqhiTCVStY){hFzAxUyiYo = true;}
      else if(lqhiTCVStY == REPWuToLbP){aTbJFznoXm = true;}
      if(zfXAkgKLoQ == EGeIsJWYfL){cdsxzNZRQc = true;}
      else if(EGeIsJWYfL == zfXAkgKLoQ){nqrONfBBgt = true;}
      if(ZwNHTOygEz == piIeffsxpi){zmlrjHVkCi = true;}
      else if(piIeffsxpi == ZwNHTOygEz){HpJwActfSy = true;}
      if(HDsluXdKXJ == CNOsJucCNs){saWgXiwyNY = true;}
      else if(CNOsJucCNs == HDsluXdKXJ){OONnaIqCZI = true;}
      if(UofceXbmwW == amIDUZqyye){uIfKchfBZW = true;}
      else if(amIDUZqyye == UofceXbmwW){NEtOnYwSKs = true;}
      if(DKxpJVpHDf == oIVJsDiDDn){argEdtSHQo = true;}
      else if(oIVJsDiDDn == DKxpJVpHDf){gZKSSjJfJc = true;}
      if(UIGcIwlkEM == IYcKVqrlyx){zMgowBHMYP = true;}
      if(CAnewkQjcu == gUKmkDZEKF){RbErgqGbPB = true;}
      if(mLkhwwFDcZ == nuyKssqEAG){bTLeIBtRCc = true;}
      while(IYcKVqrlyx == UIGcIwlkEM){FHVYXYdDmF = true;}
      while(gUKmkDZEKF == gUKmkDZEKF){nzbXgDwtHa = true;}
      while(nuyKssqEAG == nuyKssqEAG){faUZRoDtVq = true;}
      if(MYzZjBJygd == true){MYzZjBJygd = false;}
      if(hFzAxUyiYo == true){hFzAxUyiYo = false;}
      if(cdsxzNZRQc == true){cdsxzNZRQc = false;}
      if(zmlrjHVkCi == true){zmlrjHVkCi = false;}
      if(saWgXiwyNY == true){saWgXiwyNY = false;}
      if(uIfKchfBZW == true){uIfKchfBZW = false;}
      if(argEdtSHQo == true){argEdtSHQo = false;}
      if(zMgowBHMYP == true){zMgowBHMYP = false;}
      if(RbErgqGbPB == true){RbErgqGbPB = false;}
      if(bTLeIBtRCc == true){bTLeIBtRCc = false;}
      if(PnhXYhbqNa == true){PnhXYhbqNa = false;}
      if(aTbJFznoXm == true){aTbJFznoXm = false;}
      if(nqrONfBBgt == true){nqrONfBBgt = false;}
      if(HpJwActfSy == true){HpJwActfSy = false;}
      if(OONnaIqCZI == true){OONnaIqCZI = false;}
      if(NEtOnYwSKs == true){NEtOnYwSKs = false;}
      if(gZKSSjJfJc == true){gZKSSjJfJc = false;}
      if(FHVYXYdDmF == true){FHVYXYdDmF = false;}
      if(nzbXgDwtHa == true){nzbXgDwtHa = false;}
      if(faUZRoDtVq == true){faUZRoDtVq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BXABXZNMXQ
{ 
  void kGbIfCUFXF()
  { 
      bool zuAHURcnrs = false;
      bool BKeKyeZZKP = false;
      bool TFDTtabGYk = false;
      bool dIDmIfesqq = false;
      bool YkYgWLsBLW = false;
      bool epbOBsrgMt = false;
      bool pWOGOrGqCR = false;
      bool AfhTphgWwh = false;
      bool gZtBGngokO = false;
      bool nygxACVRRd = false;
      bool FBztWzHHYT = false;
      bool MUjdMPbMAa = false;
      bool LRGmcBzkTn = false;
      bool LOFRcfZAeG = false;
      bool fZPRCTNCjk = false;
      bool aJRpSmuMRU = false;
      bool zVnkHxPSBg = false;
      bool obhstlBnjJ = false;
      bool nxBhMCxOyo = false;
      bool jNiKHJkeJF = false;
      string QEpCccqTBZ;
      string HBGuxeaLRH;
      string xmYyPFywHN;
      string SsJPaZKtdI;
      string TGrPzrPdUw;
      string QiaUEdfrlW;
      string euMmHOqpUX;
      string TggJmptIzX;
      string oUbLxiSnKx;
      string sSHGdYtFHj;
      string AYJwbjBQhO;
      string iXrOhJSAoY;
      string wCeWdBYZfN;
      string woAOWQKejN;
      string gBGwOVZsYT;
      string FsPinxsmSZ;
      string KbkTRsWdrR;
      string ynQbqtwiHH;
      string bfBLICZQZY;
      string WXMJCFPmeU;
      if(QEpCccqTBZ == AYJwbjBQhO){zuAHURcnrs = true;}
      else if(AYJwbjBQhO == QEpCccqTBZ){FBztWzHHYT = true;}
      if(HBGuxeaLRH == iXrOhJSAoY){BKeKyeZZKP = true;}
      else if(iXrOhJSAoY == HBGuxeaLRH){MUjdMPbMAa = true;}
      if(xmYyPFywHN == wCeWdBYZfN){TFDTtabGYk = true;}
      else if(wCeWdBYZfN == xmYyPFywHN){LRGmcBzkTn = true;}
      if(SsJPaZKtdI == woAOWQKejN){dIDmIfesqq = true;}
      else if(woAOWQKejN == SsJPaZKtdI){LOFRcfZAeG = true;}
      if(TGrPzrPdUw == gBGwOVZsYT){YkYgWLsBLW = true;}
      else if(gBGwOVZsYT == TGrPzrPdUw){fZPRCTNCjk = true;}
      if(QiaUEdfrlW == FsPinxsmSZ){epbOBsrgMt = true;}
      else if(FsPinxsmSZ == QiaUEdfrlW){aJRpSmuMRU = true;}
      if(euMmHOqpUX == KbkTRsWdrR){pWOGOrGqCR = true;}
      else if(KbkTRsWdrR == euMmHOqpUX){zVnkHxPSBg = true;}
      if(TggJmptIzX == ynQbqtwiHH){AfhTphgWwh = true;}
      if(oUbLxiSnKx == bfBLICZQZY){gZtBGngokO = true;}
      if(sSHGdYtFHj == WXMJCFPmeU){nygxACVRRd = true;}
      while(ynQbqtwiHH == TggJmptIzX){obhstlBnjJ = true;}
      while(bfBLICZQZY == bfBLICZQZY){nxBhMCxOyo = true;}
      while(WXMJCFPmeU == WXMJCFPmeU){jNiKHJkeJF = true;}
      if(zuAHURcnrs == true){zuAHURcnrs = false;}
      if(BKeKyeZZKP == true){BKeKyeZZKP = false;}
      if(TFDTtabGYk == true){TFDTtabGYk = false;}
      if(dIDmIfesqq == true){dIDmIfesqq = false;}
      if(YkYgWLsBLW == true){YkYgWLsBLW = false;}
      if(epbOBsrgMt == true){epbOBsrgMt = false;}
      if(pWOGOrGqCR == true){pWOGOrGqCR = false;}
      if(AfhTphgWwh == true){AfhTphgWwh = false;}
      if(gZtBGngokO == true){gZtBGngokO = false;}
      if(nygxACVRRd == true){nygxACVRRd = false;}
      if(FBztWzHHYT == true){FBztWzHHYT = false;}
      if(MUjdMPbMAa == true){MUjdMPbMAa = false;}
      if(LRGmcBzkTn == true){LRGmcBzkTn = false;}
      if(LOFRcfZAeG == true){LOFRcfZAeG = false;}
      if(fZPRCTNCjk == true){fZPRCTNCjk = false;}
      if(aJRpSmuMRU == true){aJRpSmuMRU = false;}
      if(zVnkHxPSBg == true){zVnkHxPSBg = false;}
      if(obhstlBnjJ == true){obhstlBnjJ = false;}
      if(nxBhMCxOyo == true){nxBhMCxOyo = false;}
      if(jNiKHJkeJF == true){jNiKHJkeJF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FQCBZOJFHS
{ 
  void FnHTQCUMVm()
  { 
      bool JiKswVdIGa = false;
      bool EnBVlgIuxi = false;
      bool yGpbaNYiBi = false;
      bool HRPwmUbmol = false;
      bool iLQqdhhNjh = false;
      bool bZKBaCshSi = false;
      bool wuHWTmXEhQ = false;
      bool EUGKzmpyys = false;
      bool fLzSGgGOUj = false;
      bool bsUFonEsXq = false;
      bool JceScHTABn = false;
      bool MuiZDkunQl = false;
      bool fIjxoLzAVL = false;
      bool hwZHiDffpz = false;
      bool NGNfXfJuCD = false;
      bool rPclKArgcR = false;
      bool HSdoFPUbpz = false;
      bool FPxQXZuDZI = false;
      bool BEyRTSTmwh = false;
      bool KzDYqubXZH = false;
      string SQVnrnbVoH;
      string yKStJauKSf;
      string QrWklEsKEi;
      string YDTOcJHumq;
      string GScDeHYBDF;
      string aknPpatkBn;
      string tRQGhupEQz;
      string SAWbZyPSGd;
      string eqGzInPDXC;
      string OWszwnBWUj;
      string RUkDlZNMpr;
      string KbeXIDKRyt;
      string fmfNjwHXek;
      string wrxVMKGCMh;
      string ZCNfrmrUqs;
      string diYaDdnWSp;
      string SogEuRdIKx;
      string wIFPTcZAVx;
      string ElgkHMTWSh;
      string ViiVOkVIjZ;
      if(SQVnrnbVoH == RUkDlZNMpr){JiKswVdIGa = true;}
      else if(RUkDlZNMpr == SQVnrnbVoH){JceScHTABn = true;}
      if(yKStJauKSf == KbeXIDKRyt){EnBVlgIuxi = true;}
      else if(KbeXIDKRyt == yKStJauKSf){MuiZDkunQl = true;}
      if(QrWklEsKEi == fmfNjwHXek){yGpbaNYiBi = true;}
      else if(fmfNjwHXek == QrWklEsKEi){fIjxoLzAVL = true;}
      if(YDTOcJHumq == wrxVMKGCMh){HRPwmUbmol = true;}
      else if(wrxVMKGCMh == YDTOcJHumq){hwZHiDffpz = true;}
      if(GScDeHYBDF == ZCNfrmrUqs){iLQqdhhNjh = true;}
      else if(ZCNfrmrUqs == GScDeHYBDF){NGNfXfJuCD = true;}
      if(aknPpatkBn == diYaDdnWSp){bZKBaCshSi = true;}
      else if(diYaDdnWSp == aknPpatkBn){rPclKArgcR = true;}
      if(tRQGhupEQz == SogEuRdIKx){wuHWTmXEhQ = true;}
      else if(SogEuRdIKx == tRQGhupEQz){HSdoFPUbpz = true;}
      if(SAWbZyPSGd == wIFPTcZAVx){EUGKzmpyys = true;}
      if(eqGzInPDXC == ElgkHMTWSh){fLzSGgGOUj = true;}
      if(OWszwnBWUj == ViiVOkVIjZ){bsUFonEsXq = true;}
      while(wIFPTcZAVx == SAWbZyPSGd){FPxQXZuDZI = true;}
      while(ElgkHMTWSh == ElgkHMTWSh){BEyRTSTmwh = true;}
      while(ViiVOkVIjZ == ViiVOkVIjZ){KzDYqubXZH = true;}
      if(JiKswVdIGa == true){JiKswVdIGa = false;}
      if(EnBVlgIuxi == true){EnBVlgIuxi = false;}
      if(yGpbaNYiBi == true){yGpbaNYiBi = false;}
      if(HRPwmUbmol == true){HRPwmUbmol = false;}
      if(iLQqdhhNjh == true){iLQqdhhNjh = false;}
      if(bZKBaCshSi == true){bZKBaCshSi = false;}
      if(wuHWTmXEhQ == true){wuHWTmXEhQ = false;}
      if(EUGKzmpyys == true){EUGKzmpyys = false;}
      if(fLzSGgGOUj == true){fLzSGgGOUj = false;}
      if(bsUFonEsXq == true){bsUFonEsXq = false;}
      if(JceScHTABn == true){JceScHTABn = false;}
      if(MuiZDkunQl == true){MuiZDkunQl = false;}
      if(fIjxoLzAVL == true){fIjxoLzAVL = false;}
      if(hwZHiDffpz == true){hwZHiDffpz = false;}
      if(NGNfXfJuCD == true){NGNfXfJuCD = false;}
      if(rPclKArgcR == true){rPclKArgcR = false;}
      if(HSdoFPUbpz == true){HSdoFPUbpz = false;}
      if(FPxQXZuDZI == true){FPxQXZuDZI = false;}
      if(BEyRTSTmwh == true){BEyRTSTmwh = false;}
      if(KzDYqubXZH == true){KzDYqubXZH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUMCLFKJSE
{ 
  void sMgoldnpDC()
  { 
      bool MtDOaawRMz = false;
      bool WtSqIZPOAm = false;
      bool peDtJwPKXz = false;
      bool ZXEGqafBcW = false;
      bool LBpfYHWpBq = false;
      bool lIdiHgqJFd = false;
      bool KksMZzoMzg = false;
      bool sOlcannWUC = false;
      bool ZZIgMRsVyK = false;
      bool jWuyLZIdGZ = false;
      bool RJpTxXVAHS = false;
      bool rTnDEkbLzI = false;
      bool FTOnxWSnRA = false;
      bool fKPtjPiojo = false;
      bool usNfSPhrsZ = false;
      bool xwdyUyuCWa = false;
      bool EhhGlgDsSo = false;
      bool CmbKMLFhUg = false;
      bool natrDigRZk = false;
      bool UgSIjMKGsl = false;
      string YZnZmcINQP;
      string ExgVKIUVmI;
      string BtHNsWgMll;
      string ZobETPRkXI;
      string rBzozXnkpT;
      string XUOhTdSafP;
      string uuadpOVbCu;
      string piydQzuRNV;
      string hwWROFaskp;
      string wqEHMwaVzk;
      string BLitdnWjRT;
      string iBMKgzYJPk;
      string mcqLzzdpRU;
      string YYRcTVMbnZ;
      string hpaQHudtZN;
      string WQGOxXUWud;
      string JfSxuJijpK;
      string lwUoCxBaED;
      string VjPDxHSDfw;
      string BpgKQCWdVy;
      if(YZnZmcINQP == BLitdnWjRT){MtDOaawRMz = true;}
      else if(BLitdnWjRT == YZnZmcINQP){RJpTxXVAHS = true;}
      if(ExgVKIUVmI == iBMKgzYJPk){WtSqIZPOAm = true;}
      else if(iBMKgzYJPk == ExgVKIUVmI){rTnDEkbLzI = true;}
      if(BtHNsWgMll == mcqLzzdpRU){peDtJwPKXz = true;}
      else if(mcqLzzdpRU == BtHNsWgMll){FTOnxWSnRA = true;}
      if(ZobETPRkXI == YYRcTVMbnZ){ZXEGqafBcW = true;}
      else if(YYRcTVMbnZ == ZobETPRkXI){fKPtjPiojo = true;}
      if(rBzozXnkpT == hpaQHudtZN){LBpfYHWpBq = true;}
      else if(hpaQHudtZN == rBzozXnkpT){usNfSPhrsZ = true;}
      if(XUOhTdSafP == WQGOxXUWud){lIdiHgqJFd = true;}
      else if(WQGOxXUWud == XUOhTdSafP){xwdyUyuCWa = true;}
      if(uuadpOVbCu == JfSxuJijpK){KksMZzoMzg = true;}
      else if(JfSxuJijpK == uuadpOVbCu){EhhGlgDsSo = true;}
      if(piydQzuRNV == lwUoCxBaED){sOlcannWUC = true;}
      if(hwWROFaskp == VjPDxHSDfw){ZZIgMRsVyK = true;}
      if(wqEHMwaVzk == BpgKQCWdVy){jWuyLZIdGZ = true;}
      while(lwUoCxBaED == piydQzuRNV){CmbKMLFhUg = true;}
      while(VjPDxHSDfw == VjPDxHSDfw){natrDigRZk = true;}
      while(BpgKQCWdVy == BpgKQCWdVy){UgSIjMKGsl = true;}
      if(MtDOaawRMz == true){MtDOaawRMz = false;}
      if(WtSqIZPOAm == true){WtSqIZPOAm = false;}
      if(peDtJwPKXz == true){peDtJwPKXz = false;}
      if(ZXEGqafBcW == true){ZXEGqafBcW = false;}
      if(LBpfYHWpBq == true){LBpfYHWpBq = false;}
      if(lIdiHgqJFd == true){lIdiHgqJFd = false;}
      if(KksMZzoMzg == true){KksMZzoMzg = false;}
      if(sOlcannWUC == true){sOlcannWUC = false;}
      if(ZZIgMRsVyK == true){ZZIgMRsVyK = false;}
      if(jWuyLZIdGZ == true){jWuyLZIdGZ = false;}
      if(RJpTxXVAHS == true){RJpTxXVAHS = false;}
      if(rTnDEkbLzI == true){rTnDEkbLzI = false;}
      if(FTOnxWSnRA == true){FTOnxWSnRA = false;}
      if(fKPtjPiojo == true){fKPtjPiojo = false;}
      if(usNfSPhrsZ == true){usNfSPhrsZ = false;}
      if(xwdyUyuCWa == true){xwdyUyuCWa = false;}
      if(EhhGlgDsSo == true){EhhGlgDsSo = false;}
      if(CmbKMLFhUg == true){CmbKMLFhUg = false;}
      if(natrDigRZk == true){natrDigRZk = false;}
      if(UgSIjMKGsl == true){UgSIjMKGsl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VMXXKWXNAJ
{ 
  void FhYuhVykdr()
  { 
      bool EpBkeCVzLJ = false;
      bool ORlIYDjAYB = false;
      bool qJiaWSiRGj = false;
      bool gFreykJWWj = false;
      bool HIKAMtOryZ = false;
      bool RKfiIuHZNL = false;
      bool SDrbcJZHKm = false;
      bool tMdnsiyhOb = false;
      bool EqTgRVZIVC = false;
      bool diIKQDPhXD = false;
      bool UGhKfFfroY = false;
      bool wYKkGbiLKG = false;
      bool iQkHJKDSXp = false;
      bool SQKLHxJIBM = false;
      bool ohTwGEXXEn = false;
      bool UEXQTDVZBU = false;
      bool BNTzGfOzcI = false;
      bool SaJxQBxnAF = false;
      bool mfOiUNrsrE = false;
      bool biHfLbNTpa = false;
      string FQZmeNjwSO;
      string XWfyDQmgLz;
      string gMTzfxTdyU;
      string VBuJggPPsc;
      string pVJVecGKTN;
      string AIktcrxZHh;
      string tGxxsWbVQW;
      string BWnhJLCxUC;
      string qJJjUNPAfn;
      string joILhiXLcI;
      string BjsxMcTCkR;
      string ozFEpjwMbe;
      string GapclLOczZ;
      string mqTLBGQLXr;
      string sNPNyjjDUy;
      string mKixCZtPKA;
      string OqCKdyfsCj;
      string TjojlrKbdC;
      string bKHBlcHWJb;
      string MAAWdBLEjz;
      if(FQZmeNjwSO == BjsxMcTCkR){EpBkeCVzLJ = true;}
      else if(BjsxMcTCkR == FQZmeNjwSO){UGhKfFfroY = true;}
      if(XWfyDQmgLz == ozFEpjwMbe){ORlIYDjAYB = true;}
      else if(ozFEpjwMbe == XWfyDQmgLz){wYKkGbiLKG = true;}
      if(gMTzfxTdyU == GapclLOczZ){qJiaWSiRGj = true;}
      else if(GapclLOczZ == gMTzfxTdyU){iQkHJKDSXp = true;}
      if(VBuJggPPsc == mqTLBGQLXr){gFreykJWWj = true;}
      else if(mqTLBGQLXr == VBuJggPPsc){SQKLHxJIBM = true;}
      if(pVJVecGKTN == sNPNyjjDUy){HIKAMtOryZ = true;}
      else if(sNPNyjjDUy == pVJVecGKTN){ohTwGEXXEn = true;}
      if(AIktcrxZHh == mKixCZtPKA){RKfiIuHZNL = true;}
      else if(mKixCZtPKA == AIktcrxZHh){UEXQTDVZBU = true;}
      if(tGxxsWbVQW == OqCKdyfsCj){SDrbcJZHKm = true;}
      else if(OqCKdyfsCj == tGxxsWbVQW){BNTzGfOzcI = true;}
      if(BWnhJLCxUC == TjojlrKbdC){tMdnsiyhOb = true;}
      if(qJJjUNPAfn == bKHBlcHWJb){EqTgRVZIVC = true;}
      if(joILhiXLcI == MAAWdBLEjz){diIKQDPhXD = true;}
      while(TjojlrKbdC == BWnhJLCxUC){SaJxQBxnAF = true;}
      while(bKHBlcHWJb == bKHBlcHWJb){mfOiUNrsrE = true;}
      while(MAAWdBLEjz == MAAWdBLEjz){biHfLbNTpa = true;}
      if(EpBkeCVzLJ == true){EpBkeCVzLJ = false;}
      if(ORlIYDjAYB == true){ORlIYDjAYB = false;}
      if(qJiaWSiRGj == true){qJiaWSiRGj = false;}
      if(gFreykJWWj == true){gFreykJWWj = false;}
      if(HIKAMtOryZ == true){HIKAMtOryZ = false;}
      if(RKfiIuHZNL == true){RKfiIuHZNL = false;}
      if(SDrbcJZHKm == true){SDrbcJZHKm = false;}
      if(tMdnsiyhOb == true){tMdnsiyhOb = false;}
      if(EqTgRVZIVC == true){EqTgRVZIVC = false;}
      if(diIKQDPhXD == true){diIKQDPhXD = false;}
      if(UGhKfFfroY == true){UGhKfFfroY = false;}
      if(wYKkGbiLKG == true){wYKkGbiLKG = false;}
      if(iQkHJKDSXp == true){iQkHJKDSXp = false;}
      if(SQKLHxJIBM == true){SQKLHxJIBM = false;}
      if(ohTwGEXXEn == true){ohTwGEXXEn = false;}
      if(UEXQTDVZBU == true){UEXQTDVZBU = false;}
      if(BNTzGfOzcI == true){BNTzGfOzcI = false;}
      if(SaJxQBxnAF == true){SaJxQBxnAF = false;}
      if(mfOiUNrsrE == true){mfOiUNrsrE = false;}
      if(biHfLbNTpa == true){biHfLbNTpa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HRNSALXEOW
{ 
  void nuuJckLQLn()
  { 
      bool OppDJPeOMM = false;
      bool ndWQbFYBqV = false;
      bool IMDakDUbip = false;
      bool aUPjmpQIWK = false;
      bool AnKCwMQcxX = false;
      bool HTWzuCmOSG = false;
      bool uCfVkTNmdl = false;
      bool nPdgUUBAeX = false;
      bool mreLiHxQoj = false;
      bool DCpQOyHoQc = false;
      bool ycyKiqopea = false;
      bool BljtTDXUlc = false;
      bool VxysilZNRW = false;
      bool MMjBZJsUbr = false;
      bool RHkOiQRuwL = false;
      bool ZmCmHAeFax = false;
      bool QbXHNoCiUK = false;
      bool KDrtLOLjKR = false;
      bool TeQGwYJwtY = false;
      bool dmsebpidAt = false;
      string zKaYBAzlgO;
      string cIVOyMWWba;
      string IBoEGrrpVQ;
      string cLmbDIVpTA;
      string PfsKYJQbJo;
      string EgqipyUVSI;
      string IIPPkRUsKo;
      string pgDaLbHeex;
      string bQggMwTEkF;
      string nAXLrGPdYH;
      string nWQTyWdQWO;
      string poqUfqbiCo;
      string yQHEApJqhF;
      string MdGXIFAMhp;
      string SCgWPyJCeB;
      string efaiIXOLTI;
      string MlhRBLiSMa;
      string qOBMWuiknC;
      string fHMgafCWPk;
      string pnsYcfUOUE;
      if(zKaYBAzlgO == nWQTyWdQWO){OppDJPeOMM = true;}
      else if(nWQTyWdQWO == zKaYBAzlgO){ycyKiqopea = true;}
      if(cIVOyMWWba == poqUfqbiCo){ndWQbFYBqV = true;}
      else if(poqUfqbiCo == cIVOyMWWba){BljtTDXUlc = true;}
      if(IBoEGrrpVQ == yQHEApJqhF){IMDakDUbip = true;}
      else if(yQHEApJqhF == IBoEGrrpVQ){VxysilZNRW = true;}
      if(cLmbDIVpTA == MdGXIFAMhp){aUPjmpQIWK = true;}
      else if(MdGXIFAMhp == cLmbDIVpTA){MMjBZJsUbr = true;}
      if(PfsKYJQbJo == SCgWPyJCeB){AnKCwMQcxX = true;}
      else if(SCgWPyJCeB == PfsKYJQbJo){RHkOiQRuwL = true;}
      if(EgqipyUVSI == efaiIXOLTI){HTWzuCmOSG = true;}
      else if(efaiIXOLTI == EgqipyUVSI){ZmCmHAeFax = true;}
      if(IIPPkRUsKo == MlhRBLiSMa){uCfVkTNmdl = true;}
      else if(MlhRBLiSMa == IIPPkRUsKo){QbXHNoCiUK = true;}
      if(pgDaLbHeex == qOBMWuiknC){nPdgUUBAeX = true;}
      if(bQggMwTEkF == fHMgafCWPk){mreLiHxQoj = true;}
      if(nAXLrGPdYH == pnsYcfUOUE){DCpQOyHoQc = true;}
      while(qOBMWuiknC == pgDaLbHeex){KDrtLOLjKR = true;}
      while(fHMgafCWPk == fHMgafCWPk){TeQGwYJwtY = true;}
      while(pnsYcfUOUE == pnsYcfUOUE){dmsebpidAt = true;}
      if(OppDJPeOMM == true){OppDJPeOMM = false;}
      if(ndWQbFYBqV == true){ndWQbFYBqV = false;}
      if(IMDakDUbip == true){IMDakDUbip = false;}
      if(aUPjmpQIWK == true){aUPjmpQIWK = false;}
      if(AnKCwMQcxX == true){AnKCwMQcxX = false;}
      if(HTWzuCmOSG == true){HTWzuCmOSG = false;}
      if(uCfVkTNmdl == true){uCfVkTNmdl = false;}
      if(nPdgUUBAeX == true){nPdgUUBAeX = false;}
      if(mreLiHxQoj == true){mreLiHxQoj = false;}
      if(DCpQOyHoQc == true){DCpQOyHoQc = false;}
      if(ycyKiqopea == true){ycyKiqopea = false;}
      if(BljtTDXUlc == true){BljtTDXUlc = false;}
      if(VxysilZNRW == true){VxysilZNRW = false;}
      if(MMjBZJsUbr == true){MMjBZJsUbr = false;}
      if(RHkOiQRuwL == true){RHkOiQRuwL = false;}
      if(ZmCmHAeFax == true){ZmCmHAeFax = false;}
      if(QbXHNoCiUK == true){QbXHNoCiUK = false;}
      if(KDrtLOLjKR == true){KDrtLOLjKR = false;}
      if(TeQGwYJwtY == true){TeQGwYJwtY = false;}
      if(dmsebpidAt == true){dmsebpidAt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PSOUMUZLOK
{ 
  void YLkJSaTZxk()
  { 
      bool wtZEnwkoYE = false;
      bool tDrOswkAwt = false;
      bool NuGASZAWNA = false;
      bool XUNCZpJjuQ = false;
      bool kcmltlGXft = false;
      bool ljXkrAmYkO = false;
      bool wOaYfZponD = false;
      bool mBEeJjHUGg = false;
      bool SbqTOnxcKY = false;
      bool CjzfUVBOFT = false;
      bool uQibHjfraH = false;
      bool sSSDwTXHKr = false;
      bool bMdOBCCXJn = false;
      bool hsOlkBrOLd = false;
      bool HECDfiQujA = false;
      bool xtEMrilTaE = false;
      bool hHimYAEgRt = false;
      bool bIufjWKaiR = false;
      bool lGmIpnnBtC = false;
      bool OXmHuAVOef = false;
      string EoYLropChF;
      string GcchSWqrsg;
      string ZdrXYVStrG;
      string LXdVGTxPgI;
      string ppwNaztWJh;
      string GlTwEaxAlW;
      string VwJbthzHay;
      string ZbLkqjgdxY;
      string awjKAYDhQf;
      string WwcJmtfUSr;
      string AmwLHdaiFU;
      string sSDNwYLyaV;
      string dQpuadyByw;
      string DMKFXmAXDV;
      string xUcwlEsPNN;
      string igtxNixBkd;
      string fZjIQgIyoI;
      string YmuEXInsIV;
      string kinjMWSMqo;
      string ozmYpXjTeF;
      if(EoYLropChF == AmwLHdaiFU){wtZEnwkoYE = true;}
      else if(AmwLHdaiFU == EoYLropChF){uQibHjfraH = true;}
      if(GcchSWqrsg == sSDNwYLyaV){tDrOswkAwt = true;}
      else if(sSDNwYLyaV == GcchSWqrsg){sSSDwTXHKr = true;}
      if(ZdrXYVStrG == dQpuadyByw){NuGASZAWNA = true;}
      else if(dQpuadyByw == ZdrXYVStrG){bMdOBCCXJn = true;}
      if(LXdVGTxPgI == DMKFXmAXDV){XUNCZpJjuQ = true;}
      else if(DMKFXmAXDV == LXdVGTxPgI){hsOlkBrOLd = true;}
      if(ppwNaztWJh == xUcwlEsPNN){kcmltlGXft = true;}
      else if(xUcwlEsPNN == ppwNaztWJh){HECDfiQujA = true;}
      if(GlTwEaxAlW == igtxNixBkd){ljXkrAmYkO = true;}
      else if(igtxNixBkd == GlTwEaxAlW){xtEMrilTaE = true;}
      if(VwJbthzHay == fZjIQgIyoI){wOaYfZponD = true;}
      else if(fZjIQgIyoI == VwJbthzHay){hHimYAEgRt = true;}
      if(ZbLkqjgdxY == YmuEXInsIV){mBEeJjHUGg = true;}
      if(awjKAYDhQf == kinjMWSMqo){SbqTOnxcKY = true;}
      if(WwcJmtfUSr == ozmYpXjTeF){CjzfUVBOFT = true;}
      while(YmuEXInsIV == ZbLkqjgdxY){bIufjWKaiR = true;}
      while(kinjMWSMqo == kinjMWSMqo){lGmIpnnBtC = true;}
      while(ozmYpXjTeF == ozmYpXjTeF){OXmHuAVOef = true;}
      if(wtZEnwkoYE == true){wtZEnwkoYE = false;}
      if(tDrOswkAwt == true){tDrOswkAwt = false;}
      if(NuGASZAWNA == true){NuGASZAWNA = false;}
      if(XUNCZpJjuQ == true){XUNCZpJjuQ = false;}
      if(kcmltlGXft == true){kcmltlGXft = false;}
      if(ljXkrAmYkO == true){ljXkrAmYkO = false;}
      if(wOaYfZponD == true){wOaYfZponD = false;}
      if(mBEeJjHUGg == true){mBEeJjHUGg = false;}
      if(SbqTOnxcKY == true){SbqTOnxcKY = false;}
      if(CjzfUVBOFT == true){CjzfUVBOFT = false;}
      if(uQibHjfraH == true){uQibHjfraH = false;}
      if(sSSDwTXHKr == true){sSSDwTXHKr = false;}
      if(bMdOBCCXJn == true){bMdOBCCXJn = false;}
      if(hsOlkBrOLd == true){hsOlkBrOLd = false;}
      if(HECDfiQujA == true){HECDfiQujA = false;}
      if(xtEMrilTaE == true){xtEMrilTaE = false;}
      if(hHimYAEgRt == true){hHimYAEgRt = false;}
      if(bIufjWKaiR == true){bIufjWKaiR = false;}
      if(lGmIpnnBtC == true){lGmIpnnBtC = false;}
      if(OXmHuAVOef == true){OXmHuAVOef = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KFWEUYJSZU
{ 
  void scJjHSghLt()
  { 
      bool ISMWqGcyBa = false;
      bool fPZwBjcbuA = false;
      bool ZutwuHEqAZ = false;
      bool YxUHLHpjPG = false;
      bool KzPaCXXCSh = false;
      bool eZlXxNYPbi = false;
      bool BkxbChuRjs = false;
      bool ssMnpaeTtW = false;
      bool iBXRuyLwJy = false;
      bool iZHfEYBnXT = false;
      bool cFRZokNxhW = false;
      bool iEUEzzNffE = false;
      bool VyHlKTkfjQ = false;
      bool YpwZtciycJ = false;
      bool kNOmPdFDfE = false;
      bool LVHSxdyfPV = false;
      bool AgNQxrItKV = false;
      bool POCWTHjUWf = false;
      bool NhzeFDicbQ = false;
      bool eDiHJDAxoW = false;
      string wIdjOFwGmG;
      string uiQdikVkxT;
      string AFjMnSRFic;
      string pNxcXIfLiq;
      string TWAZuQEkhV;
      string qzqdwqYRuu;
      string nqXKQhlmGa;
      string EJBFzdEKRX;
      string OgXNlpVSfg;
      string jOPnDczpJN;
      string dQdHQgykdS;
      string lNAXgHTJXZ;
      string LTGZpotNCW;
      string dOBDsxCPwF;
      string rknNtVOqGw;
      string JpRiBKJEQb;
      string ljiHnWMwei;
      string EDMShaeseU;
      string ZCHGMnxRBh;
      string nxyUSHCgYX;
      if(wIdjOFwGmG == dQdHQgykdS){ISMWqGcyBa = true;}
      else if(dQdHQgykdS == wIdjOFwGmG){cFRZokNxhW = true;}
      if(uiQdikVkxT == lNAXgHTJXZ){fPZwBjcbuA = true;}
      else if(lNAXgHTJXZ == uiQdikVkxT){iEUEzzNffE = true;}
      if(AFjMnSRFic == LTGZpotNCW){ZutwuHEqAZ = true;}
      else if(LTGZpotNCW == AFjMnSRFic){VyHlKTkfjQ = true;}
      if(pNxcXIfLiq == dOBDsxCPwF){YxUHLHpjPG = true;}
      else if(dOBDsxCPwF == pNxcXIfLiq){YpwZtciycJ = true;}
      if(TWAZuQEkhV == rknNtVOqGw){KzPaCXXCSh = true;}
      else if(rknNtVOqGw == TWAZuQEkhV){kNOmPdFDfE = true;}
      if(qzqdwqYRuu == JpRiBKJEQb){eZlXxNYPbi = true;}
      else if(JpRiBKJEQb == qzqdwqYRuu){LVHSxdyfPV = true;}
      if(nqXKQhlmGa == ljiHnWMwei){BkxbChuRjs = true;}
      else if(ljiHnWMwei == nqXKQhlmGa){AgNQxrItKV = true;}
      if(EJBFzdEKRX == EDMShaeseU){ssMnpaeTtW = true;}
      if(OgXNlpVSfg == ZCHGMnxRBh){iBXRuyLwJy = true;}
      if(jOPnDczpJN == nxyUSHCgYX){iZHfEYBnXT = true;}
      while(EDMShaeseU == EJBFzdEKRX){POCWTHjUWf = true;}
      while(ZCHGMnxRBh == ZCHGMnxRBh){NhzeFDicbQ = true;}
      while(nxyUSHCgYX == nxyUSHCgYX){eDiHJDAxoW = true;}
      if(ISMWqGcyBa == true){ISMWqGcyBa = false;}
      if(fPZwBjcbuA == true){fPZwBjcbuA = false;}
      if(ZutwuHEqAZ == true){ZutwuHEqAZ = false;}
      if(YxUHLHpjPG == true){YxUHLHpjPG = false;}
      if(KzPaCXXCSh == true){KzPaCXXCSh = false;}
      if(eZlXxNYPbi == true){eZlXxNYPbi = false;}
      if(BkxbChuRjs == true){BkxbChuRjs = false;}
      if(ssMnpaeTtW == true){ssMnpaeTtW = false;}
      if(iBXRuyLwJy == true){iBXRuyLwJy = false;}
      if(iZHfEYBnXT == true){iZHfEYBnXT = false;}
      if(cFRZokNxhW == true){cFRZokNxhW = false;}
      if(iEUEzzNffE == true){iEUEzzNffE = false;}
      if(VyHlKTkfjQ == true){VyHlKTkfjQ = false;}
      if(YpwZtciycJ == true){YpwZtciycJ = false;}
      if(kNOmPdFDfE == true){kNOmPdFDfE = false;}
      if(LVHSxdyfPV == true){LVHSxdyfPV = false;}
      if(AgNQxrItKV == true){AgNQxrItKV = false;}
      if(POCWTHjUWf == true){POCWTHjUWf = false;}
      if(NhzeFDicbQ == true){NhzeFDicbQ = false;}
      if(eDiHJDAxoW == true){eDiHJDAxoW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OIODGOPREF
{ 
  void MfUjRIndYc()
  { 
      bool lVMfHsdheR = false;
      bool MRKqbJlKQg = false;
      bool KPsXukYpdm = false;
      bool ftzMIDPEMp = false;
      bool KjrCRgmGQG = false;
      bool UfpisVbojV = false;
      bool UmDqlSSyhY = false;
      bool thxZVaXpGO = false;
      bool ySZXSzEQTl = false;
      bool aaTqVWfAQz = false;
      bool OnXrMlhQMR = false;
      bool ylhVWCNfYl = false;
      bool NCeuyTNGDy = false;
      bool tXZHAJtgKf = false;
      bool RnDBnnryTT = false;
      bool JAadkLJbts = false;
      bool XaMOWZLaVN = false;
      bool HfUrUZycHJ = false;
      bool aPmiotwwWn = false;
      bool zSmRHpaodO = false;
      string YKmRBjgLxw;
      string MwnDUmcJRs;
      string PdeYFKbgeQ;
      string KKecAoVYuH;
      string WWHjintcna;
      string ixzWRteNMq;
      string HzffkCQLDe;
      string QEOKWsWupQ;
      string PysDhMKHKF;
      string JHLDzWpayf;
      string XiZIJehoAY;
      string XjXwbIGcyY;
      string rIBxVJrLKz;
      string CuwJsgYjsD;
      string dUHlgZjPap;
      string PNcZnOgbmA;
      string lWdAVcmOCu;
      string iViutWBOQu;
      string YcjTjoRWUe;
      string zxxrQHpGPE;
      if(YKmRBjgLxw == XiZIJehoAY){lVMfHsdheR = true;}
      else if(XiZIJehoAY == YKmRBjgLxw){OnXrMlhQMR = true;}
      if(MwnDUmcJRs == XjXwbIGcyY){MRKqbJlKQg = true;}
      else if(XjXwbIGcyY == MwnDUmcJRs){ylhVWCNfYl = true;}
      if(PdeYFKbgeQ == rIBxVJrLKz){KPsXukYpdm = true;}
      else if(rIBxVJrLKz == PdeYFKbgeQ){NCeuyTNGDy = true;}
      if(KKecAoVYuH == CuwJsgYjsD){ftzMIDPEMp = true;}
      else if(CuwJsgYjsD == KKecAoVYuH){tXZHAJtgKf = true;}
      if(WWHjintcna == dUHlgZjPap){KjrCRgmGQG = true;}
      else if(dUHlgZjPap == WWHjintcna){RnDBnnryTT = true;}
      if(ixzWRteNMq == PNcZnOgbmA){UfpisVbojV = true;}
      else if(PNcZnOgbmA == ixzWRteNMq){JAadkLJbts = true;}
      if(HzffkCQLDe == lWdAVcmOCu){UmDqlSSyhY = true;}
      else if(lWdAVcmOCu == HzffkCQLDe){XaMOWZLaVN = true;}
      if(QEOKWsWupQ == iViutWBOQu){thxZVaXpGO = true;}
      if(PysDhMKHKF == YcjTjoRWUe){ySZXSzEQTl = true;}
      if(JHLDzWpayf == zxxrQHpGPE){aaTqVWfAQz = true;}
      while(iViutWBOQu == QEOKWsWupQ){HfUrUZycHJ = true;}
      while(YcjTjoRWUe == YcjTjoRWUe){aPmiotwwWn = true;}
      while(zxxrQHpGPE == zxxrQHpGPE){zSmRHpaodO = true;}
      if(lVMfHsdheR == true){lVMfHsdheR = false;}
      if(MRKqbJlKQg == true){MRKqbJlKQg = false;}
      if(KPsXukYpdm == true){KPsXukYpdm = false;}
      if(ftzMIDPEMp == true){ftzMIDPEMp = false;}
      if(KjrCRgmGQG == true){KjrCRgmGQG = false;}
      if(UfpisVbojV == true){UfpisVbojV = false;}
      if(UmDqlSSyhY == true){UmDqlSSyhY = false;}
      if(thxZVaXpGO == true){thxZVaXpGO = false;}
      if(ySZXSzEQTl == true){ySZXSzEQTl = false;}
      if(aaTqVWfAQz == true){aaTqVWfAQz = false;}
      if(OnXrMlhQMR == true){OnXrMlhQMR = false;}
      if(ylhVWCNfYl == true){ylhVWCNfYl = false;}
      if(NCeuyTNGDy == true){NCeuyTNGDy = false;}
      if(tXZHAJtgKf == true){tXZHAJtgKf = false;}
      if(RnDBnnryTT == true){RnDBnnryTT = false;}
      if(JAadkLJbts == true){JAadkLJbts = false;}
      if(XaMOWZLaVN == true){XaMOWZLaVN = false;}
      if(HfUrUZycHJ == true){HfUrUZycHJ = false;}
      if(aPmiotwwWn == true){aPmiotwwWn = false;}
      if(zSmRHpaodO == true){zSmRHpaodO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SNVJTZKXJV
{ 
  void CrjKVHxOfN()
  { 
      bool njfNZcizaL = false;
      bool zIIEqgDCgP = false;
      bool RbKisQnPhO = false;
      bool RMuoFJiQEG = false;
      bool IujgObsPue = false;
      bool hwGgILYwTJ = false;
      bool oSRMslNTyg = false;
      bool xlyZGWrdUQ = false;
      bool WXUCfVGNft = false;
      bool klwtRocWnb = false;
      bool OYRNguxfZl = false;
      bool TtbDlRyOgW = false;
      bool fzmEwKpDIR = false;
      bool sUprCxFGVk = false;
      bool YZmtapKsHz = false;
      bool pNpQwOlNQW = false;
      bool EsXIsyEjBn = false;
      bool LqswyFMscG = false;
      bool AxwIbedYwm = false;
      bool LrozfeCeAb = false;
      string GVVyOVuPIx;
      string fKsNldrpuI;
      string LXOAVOXhBM;
      string HzNKVLiOJk;
      string ZYphFDeTtM;
      string QkOUWhHUbz;
      string yNNwogxiqZ;
      string ucfKhmhftS;
      string iEmnuWjrmn;
      string DNlJmMKtsY;
      string FwcURmEEmj;
      string AaZJQtaYBR;
      string wFuDVgqWXV;
      string cmmVNlaSWH;
      string SfEDmbnbrs;
      string kksaczAYyj;
      string wggRGMnEwe;
      string SICszQArPs;
      string sOdejqtLsN;
      string kCUlLkymwa;
      if(GVVyOVuPIx == FwcURmEEmj){njfNZcizaL = true;}
      else if(FwcURmEEmj == GVVyOVuPIx){OYRNguxfZl = true;}
      if(fKsNldrpuI == AaZJQtaYBR){zIIEqgDCgP = true;}
      else if(AaZJQtaYBR == fKsNldrpuI){TtbDlRyOgW = true;}
      if(LXOAVOXhBM == wFuDVgqWXV){RbKisQnPhO = true;}
      else if(wFuDVgqWXV == LXOAVOXhBM){fzmEwKpDIR = true;}
      if(HzNKVLiOJk == cmmVNlaSWH){RMuoFJiQEG = true;}
      else if(cmmVNlaSWH == HzNKVLiOJk){sUprCxFGVk = true;}
      if(ZYphFDeTtM == SfEDmbnbrs){IujgObsPue = true;}
      else if(SfEDmbnbrs == ZYphFDeTtM){YZmtapKsHz = true;}
      if(QkOUWhHUbz == kksaczAYyj){hwGgILYwTJ = true;}
      else if(kksaczAYyj == QkOUWhHUbz){pNpQwOlNQW = true;}
      if(yNNwogxiqZ == wggRGMnEwe){oSRMslNTyg = true;}
      else if(wggRGMnEwe == yNNwogxiqZ){EsXIsyEjBn = true;}
      if(ucfKhmhftS == SICszQArPs){xlyZGWrdUQ = true;}
      if(iEmnuWjrmn == sOdejqtLsN){WXUCfVGNft = true;}
      if(DNlJmMKtsY == kCUlLkymwa){klwtRocWnb = true;}
      while(SICszQArPs == ucfKhmhftS){LqswyFMscG = true;}
      while(sOdejqtLsN == sOdejqtLsN){AxwIbedYwm = true;}
      while(kCUlLkymwa == kCUlLkymwa){LrozfeCeAb = true;}
      if(njfNZcizaL == true){njfNZcizaL = false;}
      if(zIIEqgDCgP == true){zIIEqgDCgP = false;}
      if(RbKisQnPhO == true){RbKisQnPhO = false;}
      if(RMuoFJiQEG == true){RMuoFJiQEG = false;}
      if(IujgObsPue == true){IujgObsPue = false;}
      if(hwGgILYwTJ == true){hwGgILYwTJ = false;}
      if(oSRMslNTyg == true){oSRMslNTyg = false;}
      if(xlyZGWrdUQ == true){xlyZGWrdUQ = false;}
      if(WXUCfVGNft == true){WXUCfVGNft = false;}
      if(klwtRocWnb == true){klwtRocWnb = false;}
      if(OYRNguxfZl == true){OYRNguxfZl = false;}
      if(TtbDlRyOgW == true){TtbDlRyOgW = false;}
      if(fzmEwKpDIR == true){fzmEwKpDIR = false;}
      if(sUprCxFGVk == true){sUprCxFGVk = false;}
      if(YZmtapKsHz == true){YZmtapKsHz = false;}
      if(pNpQwOlNQW == true){pNpQwOlNQW = false;}
      if(EsXIsyEjBn == true){EsXIsyEjBn = false;}
      if(LqswyFMscG == true){LqswyFMscG = false;}
      if(AxwIbedYwm == true){AxwIbedYwm = false;}
      if(LrozfeCeAb == true){LrozfeCeAb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXXSFIHTYN
{ 
  void LExqOGgtfg()
  { 
      bool dqGzQFykDl = false;
      bool ncsuOLSVSM = false;
      bool GPdMdxbuJN = false;
      bool heYIDdlToc = false;
      bool bLymnNTBSd = false;
      bool IDQlGNNtUT = false;
      bool cDboDJEkqj = false;
      bool YyfojtQpYP = false;
      bool dZbeFeNlBo = false;
      bool QrzVAYjJjd = false;
      bool JiJiFJWaCM = false;
      bool xWVEoCawiX = false;
      bool uRiCSgyKoK = false;
      bool JHGtFuQsZw = false;
      bool ImjnrtWtfx = false;
      bool ymZLirzHQY = false;
      bool KLlrDoQayt = false;
      bool lhWmOIgtJY = false;
      bool JEeqLVgtKN = false;
      bool uIbAkxArkC = false;
      string dbhiGktNXW;
      string ktXpumXOan;
      string HdZqfsTTAn;
      string gQxnBKGSte;
      string BiPjWysppg;
      string ztFzMzCpCN;
      string QaNjoTwjnk;
      string gFUumXNoUh;
      string AddSomLxaC;
      string HPQgNaVftC;
      string BJBEAsZJMo;
      string kMVUMlxtuC;
      string IzIlcQomhL;
      string BhtSfqbYRu;
      string MBjkQutuUa;
      string dakrsCAObj;
      string ElbBmDRDoU;
      string KYczoHOWVg;
      string VsSGhaxCYc;
      string qMwgpaYiyM;
      if(dbhiGktNXW == BJBEAsZJMo){dqGzQFykDl = true;}
      else if(BJBEAsZJMo == dbhiGktNXW){JiJiFJWaCM = true;}
      if(ktXpumXOan == kMVUMlxtuC){ncsuOLSVSM = true;}
      else if(kMVUMlxtuC == ktXpumXOan){xWVEoCawiX = true;}
      if(HdZqfsTTAn == IzIlcQomhL){GPdMdxbuJN = true;}
      else if(IzIlcQomhL == HdZqfsTTAn){uRiCSgyKoK = true;}
      if(gQxnBKGSte == BhtSfqbYRu){heYIDdlToc = true;}
      else if(BhtSfqbYRu == gQxnBKGSte){JHGtFuQsZw = true;}
      if(BiPjWysppg == MBjkQutuUa){bLymnNTBSd = true;}
      else if(MBjkQutuUa == BiPjWysppg){ImjnrtWtfx = true;}
      if(ztFzMzCpCN == dakrsCAObj){IDQlGNNtUT = true;}
      else if(dakrsCAObj == ztFzMzCpCN){ymZLirzHQY = true;}
      if(QaNjoTwjnk == ElbBmDRDoU){cDboDJEkqj = true;}
      else if(ElbBmDRDoU == QaNjoTwjnk){KLlrDoQayt = true;}
      if(gFUumXNoUh == KYczoHOWVg){YyfojtQpYP = true;}
      if(AddSomLxaC == VsSGhaxCYc){dZbeFeNlBo = true;}
      if(HPQgNaVftC == qMwgpaYiyM){QrzVAYjJjd = true;}
      while(KYczoHOWVg == gFUumXNoUh){lhWmOIgtJY = true;}
      while(VsSGhaxCYc == VsSGhaxCYc){JEeqLVgtKN = true;}
      while(qMwgpaYiyM == qMwgpaYiyM){uIbAkxArkC = true;}
      if(dqGzQFykDl == true){dqGzQFykDl = false;}
      if(ncsuOLSVSM == true){ncsuOLSVSM = false;}
      if(GPdMdxbuJN == true){GPdMdxbuJN = false;}
      if(heYIDdlToc == true){heYIDdlToc = false;}
      if(bLymnNTBSd == true){bLymnNTBSd = false;}
      if(IDQlGNNtUT == true){IDQlGNNtUT = false;}
      if(cDboDJEkqj == true){cDboDJEkqj = false;}
      if(YyfojtQpYP == true){YyfojtQpYP = false;}
      if(dZbeFeNlBo == true){dZbeFeNlBo = false;}
      if(QrzVAYjJjd == true){QrzVAYjJjd = false;}
      if(JiJiFJWaCM == true){JiJiFJWaCM = false;}
      if(xWVEoCawiX == true){xWVEoCawiX = false;}
      if(uRiCSgyKoK == true){uRiCSgyKoK = false;}
      if(JHGtFuQsZw == true){JHGtFuQsZw = false;}
      if(ImjnrtWtfx == true){ImjnrtWtfx = false;}
      if(ymZLirzHQY == true){ymZLirzHQY = false;}
      if(KLlrDoQayt == true){KLlrDoQayt = false;}
      if(lhWmOIgtJY == true){lhWmOIgtJY = false;}
      if(JEeqLVgtKN == true){JEeqLVgtKN = false;}
      if(uIbAkxArkC == true){uIbAkxArkC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MVMYWDSPSK
{ 
  void MBMegudIMy()
  { 
      bool UYjDHpiPDq = false;
      bool iqBQCHeWbY = false;
      bool IQkwjBzrfI = false;
      bool YfWkKzkBiW = false;
      bool NUZVSLxcdL = false;
      bool cKwEYEnmSF = false;
      bool qpjuSDTPGC = false;
      bool VdnELnpOcX = false;
      bool DWOUeNiRMF = false;
      bool LyhdfXjeDP = false;
      bool rhVaozWrsj = false;
      bool NYJtBUbOPE = false;
      bool TBDAqXwKXn = false;
      bool DLLMfVAmff = false;
      bool pqYbrlnmbL = false;
      bool uVOywpdUjQ = false;
      bool DMUFgBNxNe = false;
      bool ToijOccbIE = false;
      bool jIhLrhxMQp = false;
      bool rfDObdVStp = false;
      string HDNRobiyXC;
      string VVUtYwyVSu;
      string oAjkaOTUmu;
      string WFCqbYNRAm;
      string fynITaXhoG;
      string OAsBQGScqZ;
      string HOLbfPTcRz;
      string hfVePqMaQz;
      string qleffWLAaV;
      string GkaZeRmLcD;
      string HuQoYieOlZ;
      string tqMqiVifwI;
      string ESCusxFuAx;
      string DAxMqwUpHx;
      string rxNAbOYipI;
      string iGPUznrUwa;
      string diOoVsszzm;
      string BsXzQHEBTe;
      string YVEqNwjcNC;
      string DzsfSIhYdh;
      if(HDNRobiyXC == HuQoYieOlZ){UYjDHpiPDq = true;}
      else if(HuQoYieOlZ == HDNRobiyXC){rhVaozWrsj = true;}
      if(VVUtYwyVSu == tqMqiVifwI){iqBQCHeWbY = true;}
      else if(tqMqiVifwI == VVUtYwyVSu){NYJtBUbOPE = true;}
      if(oAjkaOTUmu == ESCusxFuAx){IQkwjBzrfI = true;}
      else if(ESCusxFuAx == oAjkaOTUmu){TBDAqXwKXn = true;}
      if(WFCqbYNRAm == DAxMqwUpHx){YfWkKzkBiW = true;}
      else if(DAxMqwUpHx == WFCqbYNRAm){DLLMfVAmff = true;}
      if(fynITaXhoG == rxNAbOYipI){NUZVSLxcdL = true;}
      else if(rxNAbOYipI == fynITaXhoG){pqYbrlnmbL = true;}
      if(OAsBQGScqZ == iGPUznrUwa){cKwEYEnmSF = true;}
      else if(iGPUznrUwa == OAsBQGScqZ){uVOywpdUjQ = true;}
      if(HOLbfPTcRz == diOoVsszzm){qpjuSDTPGC = true;}
      else if(diOoVsszzm == HOLbfPTcRz){DMUFgBNxNe = true;}
      if(hfVePqMaQz == BsXzQHEBTe){VdnELnpOcX = true;}
      if(qleffWLAaV == YVEqNwjcNC){DWOUeNiRMF = true;}
      if(GkaZeRmLcD == DzsfSIhYdh){LyhdfXjeDP = true;}
      while(BsXzQHEBTe == hfVePqMaQz){ToijOccbIE = true;}
      while(YVEqNwjcNC == YVEqNwjcNC){jIhLrhxMQp = true;}
      while(DzsfSIhYdh == DzsfSIhYdh){rfDObdVStp = true;}
      if(UYjDHpiPDq == true){UYjDHpiPDq = false;}
      if(iqBQCHeWbY == true){iqBQCHeWbY = false;}
      if(IQkwjBzrfI == true){IQkwjBzrfI = false;}
      if(YfWkKzkBiW == true){YfWkKzkBiW = false;}
      if(NUZVSLxcdL == true){NUZVSLxcdL = false;}
      if(cKwEYEnmSF == true){cKwEYEnmSF = false;}
      if(qpjuSDTPGC == true){qpjuSDTPGC = false;}
      if(VdnELnpOcX == true){VdnELnpOcX = false;}
      if(DWOUeNiRMF == true){DWOUeNiRMF = false;}
      if(LyhdfXjeDP == true){LyhdfXjeDP = false;}
      if(rhVaozWrsj == true){rhVaozWrsj = false;}
      if(NYJtBUbOPE == true){NYJtBUbOPE = false;}
      if(TBDAqXwKXn == true){TBDAqXwKXn = false;}
      if(DLLMfVAmff == true){DLLMfVAmff = false;}
      if(pqYbrlnmbL == true){pqYbrlnmbL = false;}
      if(uVOywpdUjQ == true){uVOywpdUjQ = false;}
      if(DMUFgBNxNe == true){DMUFgBNxNe = false;}
      if(ToijOccbIE == true){ToijOccbIE = false;}
      if(jIhLrhxMQp == true){jIhLrhxMQp = false;}
      if(rfDObdVStp == true){rfDObdVStp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class COCBWUSILP
{ 
  void UTAAdXktjY()
  { 
      bool UJHBryRKxG = false;
      bool tXiUqWlipb = false;
      bool dHFfTtUyrD = false;
      bool rjkEmPEKBf = false;
      bool SxbUloezKb = false;
      bool QEXseMDagy = false;
      bool cTRtNJmdga = false;
      bool RagKJgfkse = false;
      bool PVmQlmLrZa = false;
      bool McdDDzehGb = false;
      bool BARjKpXNjy = false;
      bool gShBhHfAHZ = false;
      bool ytEGOnxdHJ = false;
      bool BxdQcPDCGw = false;
      bool PyHbtsubUw = false;
      bool SdafdHwLVV = false;
      bool rtGZwinRXS = false;
      bool DctKKzlbLU = false;
      bool rUILpWWxlV = false;
      bool TqgjDVrgeK = false;
      string FKYKQIVCLs;
      string XBtUslYCXo;
      string rZGbaaWyjs;
      string qhzEVSinyG;
      string xDqPbbLFNj;
      string ywpdEeDwjo;
      string kWSSCoCpzZ;
      string DjDQqniqAy;
      string ORkzutqUzq;
      string OlEIUZkYMl;
      string ZVFngOsZlQ;
      string wMwkZTlSWI;
      string ygpIKQftwR;
      string DJdOYsLxSg;
      string BRiitCpTiB;
      string mRBEmrfxcQ;
      string hydUMlhgMg;
      string IoApGgyHNI;
      string ZLLtdkIZaf;
      string MNTByDnOVI;
      if(FKYKQIVCLs == ZVFngOsZlQ){UJHBryRKxG = true;}
      else if(ZVFngOsZlQ == FKYKQIVCLs){BARjKpXNjy = true;}
      if(XBtUslYCXo == wMwkZTlSWI){tXiUqWlipb = true;}
      else if(wMwkZTlSWI == XBtUslYCXo){gShBhHfAHZ = true;}
      if(rZGbaaWyjs == ygpIKQftwR){dHFfTtUyrD = true;}
      else if(ygpIKQftwR == rZGbaaWyjs){ytEGOnxdHJ = true;}
      if(qhzEVSinyG == DJdOYsLxSg){rjkEmPEKBf = true;}
      else if(DJdOYsLxSg == qhzEVSinyG){BxdQcPDCGw = true;}
      if(xDqPbbLFNj == BRiitCpTiB){SxbUloezKb = true;}
      else if(BRiitCpTiB == xDqPbbLFNj){PyHbtsubUw = true;}
      if(ywpdEeDwjo == mRBEmrfxcQ){QEXseMDagy = true;}
      else if(mRBEmrfxcQ == ywpdEeDwjo){SdafdHwLVV = true;}
      if(kWSSCoCpzZ == hydUMlhgMg){cTRtNJmdga = true;}
      else if(hydUMlhgMg == kWSSCoCpzZ){rtGZwinRXS = true;}
      if(DjDQqniqAy == IoApGgyHNI){RagKJgfkse = true;}
      if(ORkzutqUzq == ZLLtdkIZaf){PVmQlmLrZa = true;}
      if(OlEIUZkYMl == MNTByDnOVI){McdDDzehGb = true;}
      while(IoApGgyHNI == DjDQqniqAy){DctKKzlbLU = true;}
      while(ZLLtdkIZaf == ZLLtdkIZaf){rUILpWWxlV = true;}
      while(MNTByDnOVI == MNTByDnOVI){TqgjDVrgeK = true;}
      if(UJHBryRKxG == true){UJHBryRKxG = false;}
      if(tXiUqWlipb == true){tXiUqWlipb = false;}
      if(dHFfTtUyrD == true){dHFfTtUyrD = false;}
      if(rjkEmPEKBf == true){rjkEmPEKBf = false;}
      if(SxbUloezKb == true){SxbUloezKb = false;}
      if(QEXseMDagy == true){QEXseMDagy = false;}
      if(cTRtNJmdga == true){cTRtNJmdga = false;}
      if(RagKJgfkse == true){RagKJgfkse = false;}
      if(PVmQlmLrZa == true){PVmQlmLrZa = false;}
      if(McdDDzehGb == true){McdDDzehGb = false;}
      if(BARjKpXNjy == true){BARjKpXNjy = false;}
      if(gShBhHfAHZ == true){gShBhHfAHZ = false;}
      if(ytEGOnxdHJ == true){ytEGOnxdHJ = false;}
      if(BxdQcPDCGw == true){BxdQcPDCGw = false;}
      if(PyHbtsubUw == true){PyHbtsubUw = false;}
      if(SdafdHwLVV == true){SdafdHwLVV = false;}
      if(rtGZwinRXS == true){rtGZwinRXS = false;}
      if(DctKKzlbLU == true){DctKKzlbLU = false;}
      if(rUILpWWxlV == true){rUILpWWxlV = false;}
      if(TqgjDVrgeK == true){TqgjDVrgeK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class REIGQQAZXG
{ 
  void EBRximdodU()
  { 
      bool HlUqyclWxV = false;
      bool asxfptWYRK = false;
      bool wjyjopPlWy = false;
      bool rtzDEQYIPo = false;
      bool JslKkZxYpU = false;
      bool zELKsWnkBI = false;
      bool MAAzcfstaZ = false;
      bool VOJcBCxnyP = false;
      bool rqwBynioJg = false;
      bool bnGGbIsmgF = false;
      bool fDxPykuiJq = false;
      bool ZAllQUDyAo = false;
      bool wDjsxhIDAr = false;
      bool IJGsintfDN = false;
      bool rAfRHbBTpH = false;
      bool FumrIcSDSP = false;
      bool bqhQhPsrDb = false;
      bool ZXumwwXRlU = false;
      bool foNsmNWOjG = false;
      bool VpNmkAROjr = false;
      string TGsdSwlTdA;
      string niPhuVMILh;
      string WLxgajytol;
      string WwljxHgbVF;
      string FZoMZfqXSC;
      string iHraCIILCh;
      string yqdqdrwekm;
      string ojlGcwWkGu;
      string sZblCODLhn;
      string zVYnHNwxhh;
      string jLmfNzUlyG;
      string lWEHoXPqoP;
      string okxwnTKyyO;
      string AYCYLgluYD;
      string sRMbCbQRzj;
      string xEISsyOqqs;
      string nWmiGMTewH;
      string kTRkVWXVsL;
      string CszORuQjfM;
      string SuEfOWdcVp;
      if(TGsdSwlTdA == jLmfNzUlyG){HlUqyclWxV = true;}
      else if(jLmfNzUlyG == TGsdSwlTdA){fDxPykuiJq = true;}
      if(niPhuVMILh == lWEHoXPqoP){asxfptWYRK = true;}
      else if(lWEHoXPqoP == niPhuVMILh){ZAllQUDyAo = true;}
      if(WLxgajytol == okxwnTKyyO){wjyjopPlWy = true;}
      else if(okxwnTKyyO == WLxgajytol){wDjsxhIDAr = true;}
      if(WwljxHgbVF == AYCYLgluYD){rtzDEQYIPo = true;}
      else if(AYCYLgluYD == WwljxHgbVF){IJGsintfDN = true;}
      if(FZoMZfqXSC == sRMbCbQRzj){JslKkZxYpU = true;}
      else if(sRMbCbQRzj == FZoMZfqXSC){rAfRHbBTpH = true;}
      if(iHraCIILCh == xEISsyOqqs){zELKsWnkBI = true;}
      else if(xEISsyOqqs == iHraCIILCh){FumrIcSDSP = true;}
      if(yqdqdrwekm == nWmiGMTewH){MAAzcfstaZ = true;}
      else if(nWmiGMTewH == yqdqdrwekm){bqhQhPsrDb = true;}
      if(ojlGcwWkGu == kTRkVWXVsL){VOJcBCxnyP = true;}
      if(sZblCODLhn == CszORuQjfM){rqwBynioJg = true;}
      if(zVYnHNwxhh == SuEfOWdcVp){bnGGbIsmgF = true;}
      while(kTRkVWXVsL == ojlGcwWkGu){ZXumwwXRlU = true;}
      while(CszORuQjfM == CszORuQjfM){foNsmNWOjG = true;}
      while(SuEfOWdcVp == SuEfOWdcVp){VpNmkAROjr = true;}
      if(HlUqyclWxV == true){HlUqyclWxV = false;}
      if(asxfptWYRK == true){asxfptWYRK = false;}
      if(wjyjopPlWy == true){wjyjopPlWy = false;}
      if(rtzDEQYIPo == true){rtzDEQYIPo = false;}
      if(JslKkZxYpU == true){JslKkZxYpU = false;}
      if(zELKsWnkBI == true){zELKsWnkBI = false;}
      if(MAAzcfstaZ == true){MAAzcfstaZ = false;}
      if(VOJcBCxnyP == true){VOJcBCxnyP = false;}
      if(rqwBynioJg == true){rqwBynioJg = false;}
      if(bnGGbIsmgF == true){bnGGbIsmgF = false;}
      if(fDxPykuiJq == true){fDxPykuiJq = false;}
      if(ZAllQUDyAo == true){ZAllQUDyAo = false;}
      if(wDjsxhIDAr == true){wDjsxhIDAr = false;}
      if(IJGsintfDN == true){IJGsintfDN = false;}
      if(rAfRHbBTpH == true){rAfRHbBTpH = false;}
      if(FumrIcSDSP == true){FumrIcSDSP = false;}
      if(bqhQhPsrDb == true){bqhQhPsrDb = false;}
      if(ZXumwwXRlU == true){ZXumwwXRlU = false;}
      if(foNsmNWOjG == true){foNsmNWOjG = false;}
      if(VpNmkAROjr == true){VpNmkAROjr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQUKOUHQKB
{ 
  void LnuJDdLfPu()
  { 
      bool PqLpzWcoxE = false;
      bool fNmPcOwPLo = false;
      bool YLsDGoKKSJ = false;
      bool gIhBcucJat = false;
      bool rJgJbpHMcf = false;
      bool mOyVGEyHjK = false;
      bool MSVmXXelmg = false;
      bool kmoRxOdjbP = false;
      bool gxgmWSJLtX = false;
      bool xUYPhYnskD = false;
      bool KUZutAYgYr = false;
      bool ZNfTcOkhQF = false;
      bool OTqOjPNZjX = false;
      bool akyXELXlsV = false;
      bool sbmCyioElS = false;
      bool nFbfoqdLKd = false;
      bool lyxAQnPHPQ = false;
      bool qzotLlfoPB = false;
      bool aImQjVIRhN = false;
      bool hLaOitemkJ = false;
      string JtgCaJTmTA;
      string OGSoTIeCsE;
      string WOBWUTpGio;
      string yMGHZHqZdB;
      string ufuRxGiVQP;
      string XUqNNtsJhG;
      string TNDeCBzKPL;
      string RFXqJpTjZO;
      string jUoSRcUrte;
      string OgqWhhcQPw;
      string GXFFyRxAEX;
      string aJjTWyXjNY;
      string fHQkxjNAJa;
      string NCTcHLOjUz;
      string fUnVDExXAi;
      string KrDpPzHUHO;
      string EwpcKXoGLK;
      string imPNsLStgr;
      string lozZQUzdNH;
      string EtbFtieKLf;
      if(JtgCaJTmTA == GXFFyRxAEX){PqLpzWcoxE = true;}
      else if(GXFFyRxAEX == JtgCaJTmTA){KUZutAYgYr = true;}
      if(OGSoTIeCsE == aJjTWyXjNY){fNmPcOwPLo = true;}
      else if(aJjTWyXjNY == OGSoTIeCsE){ZNfTcOkhQF = true;}
      if(WOBWUTpGio == fHQkxjNAJa){YLsDGoKKSJ = true;}
      else if(fHQkxjNAJa == WOBWUTpGio){OTqOjPNZjX = true;}
      if(yMGHZHqZdB == NCTcHLOjUz){gIhBcucJat = true;}
      else if(NCTcHLOjUz == yMGHZHqZdB){akyXELXlsV = true;}
      if(ufuRxGiVQP == fUnVDExXAi){rJgJbpHMcf = true;}
      else if(fUnVDExXAi == ufuRxGiVQP){sbmCyioElS = true;}
      if(XUqNNtsJhG == KrDpPzHUHO){mOyVGEyHjK = true;}
      else if(KrDpPzHUHO == XUqNNtsJhG){nFbfoqdLKd = true;}
      if(TNDeCBzKPL == EwpcKXoGLK){MSVmXXelmg = true;}
      else if(EwpcKXoGLK == TNDeCBzKPL){lyxAQnPHPQ = true;}
      if(RFXqJpTjZO == imPNsLStgr){kmoRxOdjbP = true;}
      if(jUoSRcUrte == lozZQUzdNH){gxgmWSJLtX = true;}
      if(OgqWhhcQPw == EtbFtieKLf){xUYPhYnskD = true;}
      while(imPNsLStgr == RFXqJpTjZO){qzotLlfoPB = true;}
      while(lozZQUzdNH == lozZQUzdNH){aImQjVIRhN = true;}
      while(EtbFtieKLf == EtbFtieKLf){hLaOitemkJ = true;}
      if(PqLpzWcoxE == true){PqLpzWcoxE = false;}
      if(fNmPcOwPLo == true){fNmPcOwPLo = false;}
      if(YLsDGoKKSJ == true){YLsDGoKKSJ = false;}
      if(gIhBcucJat == true){gIhBcucJat = false;}
      if(rJgJbpHMcf == true){rJgJbpHMcf = false;}
      if(mOyVGEyHjK == true){mOyVGEyHjK = false;}
      if(MSVmXXelmg == true){MSVmXXelmg = false;}
      if(kmoRxOdjbP == true){kmoRxOdjbP = false;}
      if(gxgmWSJLtX == true){gxgmWSJLtX = false;}
      if(xUYPhYnskD == true){xUYPhYnskD = false;}
      if(KUZutAYgYr == true){KUZutAYgYr = false;}
      if(ZNfTcOkhQF == true){ZNfTcOkhQF = false;}
      if(OTqOjPNZjX == true){OTqOjPNZjX = false;}
      if(akyXELXlsV == true){akyXELXlsV = false;}
      if(sbmCyioElS == true){sbmCyioElS = false;}
      if(nFbfoqdLKd == true){nFbfoqdLKd = false;}
      if(lyxAQnPHPQ == true){lyxAQnPHPQ = false;}
      if(qzotLlfoPB == true){qzotLlfoPB = false;}
      if(aImQjVIRhN == true){aImQjVIRhN = false;}
      if(hLaOitemkJ == true){hLaOitemkJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QXIMRORWMU
{ 
  void khFDAynGmC()
  { 
      bool BfOtOpzBxR = false;
      bool bsXHLuFNjB = false;
      bool qtywPmjIWf = false;
      bool seKzAUDbtg = false;
      bool ZaApJNHKjD = false;
      bool TlThRHgSda = false;
      bool GqdRXwiYGp = false;
      bool rdTCaPsIlC = false;
      bool fYXSLGLbhr = false;
      bool njxSaixiRN = false;
      bool diDsLpSQGB = false;
      bool OYfbugSKFQ = false;
      bool jGpNCHfAbr = false;
      bool SJpXXwVeHV = false;
      bool nuVfdODVWt = false;
      bool QlcBcWroqE = false;
      bool JRnOhEhHEy = false;
      bool LnDjcnkJjm = false;
      bool DKdhaffouA = false;
      bool EfmDMVGGyY = false;
      string IHheNrimea;
      string AgjEjbBPfT;
      string jiyQuFfXNH;
      string CByNVybLra;
      string gpcjYpPBqC;
      string SlSMyZJQiI;
      string LKYXYyiVhk;
      string zpWFmsFNrE;
      string oegLnQilPw;
      string oLbjOVQFLZ;
      string HtSFCbOMZE;
      string TuYeSfcNiH;
      string PwFkwnOmqQ;
      string czCRxuMaJM;
      string BVMLctmwQh;
      string rDWDKLngJN;
      string NbVIbTrGhW;
      string TBDVFsitIC;
      string BRVIXZbyHl;
      string HfRuzZzDjI;
      if(IHheNrimea == HtSFCbOMZE){BfOtOpzBxR = true;}
      else if(HtSFCbOMZE == IHheNrimea){diDsLpSQGB = true;}
      if(AgjEjbBPfT == TuYeSfcNiH){bsXHLuFNjB = true;}
      else if(TuYeSfcNiH == AgjEjbBPfT){OYfbugSKFQ = true;}
      if(jiyQuFfXNH == PwFkwnOmqQ){qtywPmjIWf = true;}
      else if(PwFkwnOmqQ == jiyQuFfXNH){jGpNCHfAbr = true;}
      if(CByNVybLra == czCRxuMaJM){seKzAUDbtg = true;}
      else if(czCRxuMaJM == CByNVybLra){SJpXXwVeHV = true;}
      if(gpcjYpPBqC == BVMLctmwQh){ZaApJNHKjD = true;}
      else if(BVMLctmwQh == gpcjYpPBqC){nuVfdODVWt = true;}
      if(SlSMyZJQiI == rDWDKLngJN){TlThRHgSda = true;}
      else if(rDWDKLngJN == SlSMyZJQiI){QlcBcWroqE = true;}
      if(LKYXYyiVhk == NbVIbTrGhW){GqdRXwiYGp = true;}
      else if(NbVIbTrGhW == LKYXYyiVhk){JRnOhEhHEy = true;}
      if(zpWFmsFNrE == TBDVFsitIC){rdTCaPsIlC = true;}
      if(oegLnQilPw == BRVIXZbyHl){fYXSLGLbhr = true;}
      if(oLbjOVQFLZ == HfRuzZzDjI){njxSaixiRN = true;}
      while(TBDVFsitIC == zpWFmsFNrE){LnDjcnkJjm = true;}
      while(BRVIXZbyHl == BRVIXZbyHl){DKdhaffouA = true;}
      while(HfRuzZzDjI == HfRuzZzDjI){EfmDMVGGyY = true;}
      if(BfOtOpzBxR == true){BfOtOpzBxR = false;}
      if(bsXHLuFNjB == true){bsXHLuFNjB = false;}
      if(qtywPmjIWf == true){qtywPmjIWf = false;}
      if(seKzAUDbtg == true){seKzAUDbtg = false;}
      if(ZaApJNHKjD == true){ZaApJNHKjD = false;}
      if(TlThRHgSda == true){TlThRHgSda = false;}
      if(GqdRXwiYGp == true){GqdRXwiYGp = false;}
      if(rdTCaPsIlC == true){rdTCaPsIlC = false;}
      if(fYXSLGLbhr == true){fYXSLGLbhr = false;}
      if(njxSaixiRN == true){njxSaixiRN = false;}
      if(diDsLpSQGB == true){diDsLpSQGB = false;}
      if(OYfbugSKFQ == true){OYfbugSKFQ = false;}
      if(jGpNCHfAbr == true){jGpNCHfAbr = false;}
      if(SJpXXwVeHV == true){SJpXXwVeHV = false;}
      if(nuVfdODVWt == true){nuVfdODVWt = false;}
      if(QlcBcWroqE == true){QlcBcWroqE = false;}
      if(JRnOhEhHEy == true){JRnOhEhHEy = false;}
      if(LnDjcnkJjm == true){LnDjcnkJjm = false;}
      if(DKdhaffouA == true){DKdhaffouA = false;}
      if(EfmDMVGGyY == true){EfmDMVGGyY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PVUVBEEKZJ
{ 
  void oajBwuTXME()
  { 
      bool mnsmpJoAbV = false;
      bool GiNMLEkSjE = false;
      bool NtepxTYOMO = false;
      bool gpthAXlIYI = false;
      bool AtwYSHBwZf = false;
      bool bzmiAsIDpW = false;
      bool jZnNnPofMm = false;
      bool SctaDTyFWp = false;
      bool RcofmgDKgH = false;
      bool OiRCXZGhjC = false;
      bool RVilNzFMeg = false;
      bool tDfAEHjHaH = false;
      bool MdyFXjKqCd = false;
      bool MPVUXwtDRm = false;
      bool bpfAMLCRyQ = false;
      bool oyHcomXcNd = false;
      bool nNJBTegLbH = false;
      bool NgomeVyxsM = false;
      bool gsslnOHrej = false;
      bool XQonzOgegh = false;
      string BnqHTUtrlN;
      string ldgXrwpwJf;
      string rorVrmOwcZ;
      string tPALiwViCm;
      string jNdronBOpW;
      string fxrLELuUOg;
      string GyOMSVdVnu;
      string ZHsVwdKAgE;
      string lzFFsxWoHW;
      string BATVgkyRYS;
      string JeauxXDWOZ;
      string BtmKtHrJSU;
      string yoORtYnWoL;
      string esbOtGXKIU;
      string sAagVGMIaZ;
      string royDTUQJBX;
      string jghDtHSYPn;
      string ihAxbyNgun;
      string LeuPSptXtZ;
      string pOJkkMRXmN;
      if(BnqHTUtrlN == JeauxXDWOZ){mnsmpJoAbV = true;}
      else if(JeauxXDWOZ == BnqHTUtrlN){RVilNzFMeg = true;}
      if(ldgXrwpwJf == BtmKtHrJSU){GiNMLEkSjE = true;}
      else if(BtmKtHrJSU == ldgXrwpwJf){tDfAEHjHaH = true;}
      if(rorVrmOwcZ == yoORtYnWoL){NtepxTYOMO = true;}
      else if(yoORtYnWoL == rorVrmOwcZ){MdyFXjKqCd = true;}
      if(tPALiwViCm == esbOtGXKIU){gpthAXlIYI = true;}
      else if(esbOtGXKIU == tPALiwViCm){MPVUXwtDRm = true;}
      if(jNdronBOpW == sAagVGMIaZ){AtwYSHBwZf = true;}
      else if(sAagVGMIaZ == jNdronBOpW){bpfAMLCRyQ = true;}
      if(fxrLELuUOg == royDTUQJBX){bzmiAsIDpW = true;}
      else if(royDTUQJBX == fxrLELuUOg){oyHcomXcNd = true;}
      if(GyOMSVdVnu == jghDtHSYPn){jZnNnPofMm = true;}
      else if(jghDtHSYPn == GyOMSVdVnu){nNJBTegLbH = true;}
      if(ZHsVwdKAgE == ihAxbyNgun){SctaDTyFWp = true;}
      if(lzFFsxWoHW == LeuPSptXtZ){RcofmgDKgH = true;}
      if(BATVgkyRYS == pOJkkMRXmN){OiRCXZGhjC = true;}
      while(ihAxbyNgun == ZHsVwdKAgE){NgomeVyxsM = true;}
      while(LeuPSptXtZ == LeuPSptXtZ){gsslnOHrej = true;}
      while(pOJkkMRXmN == pOJkkMRXmN){XQonzOgegh = true;}
      if(mnsmpJoAbV == true){mnsmpJoAbV = false;}
      if(GiNMLEkSjE == true){GiNMLEkSjE = false;}
      if(NtepxTYOMO == true){NtepxTYOMO = false;}
      if(gpthAXlIYI == true){gpthAXlIYI = false;}
      if(AtwYSHBwZf == true){AtwYSHBwZf = false;}
      if(bzmiAsIDpW == true){bzmiAsIDpW = false;}
      if(jZnNnPofMm == true){jZnNnPofMm = false;}
      if(SctaDTyFWp == true){SctaDTyFWp = false;}
      if(RcofmgDKgH == true){RcofmgDKgH = false;}
      if(OiRCXZGhjC == true){OiRCXZGhjC = false;}
      if(RVilNzFMeg == true){RVilNzFMeg = false;}
      if(tDfAEHjHaH == true){tDfAEHjHaH = false;}
      if(MdyFXjKqCd == true){MdyFXjKqCd = false;}
      if(MPVUXwtDRm == true){MPVUXwtDRm = false;}
      if(bpfAMLCRyQ == true){bpfAMLCRyQ = false;}
      if(oyHcomXcNd == true){oyHcomXcNd = false;}
      if(nNJBTegLbH == true){nNJBTegLbH = false;}
      if(NgomeVyxsM == true){NgomeVyxsM = false;}
      if(gsslnOHrej == true){gsslnOHrej = false;}
      if(XQonzOgegh == true){XQonzOgegh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GJRMHNEQPN
{ 
  void DiMrhhReKh()
  { 
      bool yaiVoPNxfz = false;
      bool NgyJxixEDz = false;
      bool wILfOrcNFo = false;
      bool tqDwwANCDI = false;
      bool nBpumfFIZa = false;
      bool AIRoApOCGw = false;
      bool lArpFVdBNw = false;
      bool VtBtLtRPsi = false;
      bool mUneokZNwF = false;
      bool kKwHVnJApQ = false;
      bool BDtcEGHWdF = false;
      bool XyJWIRLNBU = false;
      bool wQFHLLytXW = false;
      bool jRZbhjaKZh = false;
      bool dDjphlAYyE = false;
      bool bwzVUjxlQs = false;
      bool HNyGVFYhoX = false;
      bool pAmSpsgOZY = false;
      bool LZuSumSEHx = false;
      bool lnsfZQEcUb = false;
      string dohdhxWdpz;
      string VEAZIfRDAL;
      string ZnEyNZhDRD;
      string iUkapjckUr;
      string xrGoYDfLCm;
      string WZiaipjiPI;
      string OSMlPBTYjY;
      string DfhHNggPZJ;
      string sWAefJkJrA;
      string zsUMddfTZW;
      string jGbdipqaMC;
      string IUJGOrSgGG;
      string QJgjYKKVdj;
      string AMpCZluWwp;
      string SJxoqdiOxl;
      string LzNSGZYqEY;
      string eUxbBueHfb;
      string wukPmGMqrt;
      string bwXrYBzWuA;
      string NDRWKxMUnw;
      if(dohdhxWdpz == jGbdipqaMC){yaiVoPNxfz = true;}
      else if(jGbdipqaMC == dohdhxWdpz){BDtcEGHWdF = true;}
      if(VEAZIfRDAL == IUJGOrSgGG){NgyJxixEDz = true;}
      else if(IUJGOrSgGG == VEAZIfRDAL){XyJWIRLNBU = true;}
      if(ZnEyNZhDRD == QJgjYKKVdj){wILfOrcNFo = true;}
      else if(QJgjYKKVdj == ZnEyNZhDRD){wQFHLLytXW = true;}
      if(iUkapjckUr == AMpCZluWwp){tqDwwANCDI = true;}
      else if(AMpCZluWwp == iUkapjckUr){jRZbhjaKZh = true;}
      if(xrGoYDfLCm == SJxoqdiOxl){nBpumfFIZa = true;}
      else if(SJxoqdiOxl == xrGoYDfLCm){dDjphlAYyE = true;}
      if(WZiaipjiPI == LzNSGZYqEY){AIRoApOCGw = true;}
      else if(LzNSGZYqEY == WZiaipjiPI){bwzVUjxlQs = true;}
      if(OSMlPBTYjY == eUxbBueHfb){lArpFVdBNw = true;}
      else if(eUxbBueHfb == OSMlPBTYjY){HNyGVFYhoX = true;}
      if(DfhHNggPZJ == wukPmGMqrt){VtBtLtRPsi = true;}
      if(sWAefJkJrA == bwXrYBzWuA){mUneokZNwF = true;}
      if(zsUMddfTZW == NDRWKxMUnw){kKwHVnJApQ = true;}
      while(wukPmGMqrt == DfhHNggPZJ){pAmSpsgOZY = true;}
      while(bwXrYBzWuA == bwXrYBzWuA){LZuSumSEHx = true;}
      while(NDRWKxMUnw == NDRWKxMUnw){lnsfZQEcUb = true;}
      if(yaiVoPNxfz == true){yaiVoPNxfz = false;}
      if(NgyJxixEDz == true){NgyJxixEDz = false;}
      if(wILfOrcNFo == true){wILfOrcNFo = false;}
      if(tqDwwANCDI == true){tqDwwANCDI = false;}
      if(nBpumfFIZa == true){nBpumfFIZa = false;}
      if(AIRoApOCGw == true){AIRoApOCGw = false;}
      if(lArpFVdBNw == true){lArpFVdBNw = false;}
      if(VtBtLtRPsi == true){VtBtLtRPsi = false;}
      if(mUneokZNwF == true){mUneokZNwF = false;}
      if(kKwHVnJApQ == true){kKwHVnJApQ = false;}
      if(BDtcEGHWdF == true){BDtcEGHWdF = false;}
      if(XyJWIRLNBU == true){XyJWIRLNBU = false;}
      if(wQFHLLytXW == true){wQFHLLytXW = false;}
      if(jRZbhjaKZh == true){jRZbhjaKZh = false;}
      if(dDjphlAYyE == true){dDjphlAYyE = false;}
      if(bwzVUjxlQs == true){bwzVUjxlQs = false;}
      if(HNyGVFYhoX == true){HNyGVFYhoX = false;}
      if(pAmSpsgOZY == true){pAmSpsgOZY = false;}
      if(LZuSumSEHx == true){LZuSumSEHx = false;}
      if(lnsfZQEcUb == true){lnsfZQEcUb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHASQDSZWX
{ 
  void HjnAaJGdKe()
  { 
      bool prKNhUOGto = false;
      bool SRaYdDAEor = false;
      bool PjlORCLGIn = false;
      bool SuBVVrQYTe = false;
      bool tlCOHBaafS = false;
      bool gzWYFGFuuf = false;
      bool JHyFVWQEDl = false;
      bool mbjJychXHQ = false;
      bool ajapGTXbQP = false;
      bool lUdnUlnwrj = false;
      bool jVXteFONab = false;
      bool XhndEZfHzC = false;
      bool znmmzSxwoL = false;
      bool okeWfEMgKB = false;
      bool EKAoqEfzju = false;
      bool GgwpjuijuM = false;
      bool HSXPmmDQxz = false;
      bool Nzwyxonywt = false;
      bool lyLtFHnnlj = false;
      bool VbkysllkCE = false;
      string CfFatWWyYf;
      string fksDdVgaml;
      string aMQmAhpWBh;
      string suDDLeJPBp;
      string cRLudQJgSt;
      string XyqexpORZM;
      string gAwqlkgprz;
      string LRZxJIAVJj;
      string XIEGJtEXFU;
      string PqpnJbUUIs;
      string iToThGYtVn;
      string psIooXwohr;
      string gJjWiTbkng;
      string nfMQADTkYC;
      string VJBReWiAzl;
      string felQMZjRkO;
      string emGoAJfqok;
      string DKQfVWHRqL;
      string jalBAIswEZ;
      string SBzJWhDMQV;
      if(CfFatWWyYf == iToThGYtVn){prKNhUOGto = true;}
      else if(iToThGYtVn == CfFatWWyYf){jVXteFONab = true;}
      if(fksDdVgaml == psIooXwohr){SRaYdDAEor = true;}
      else if(psIooXwohr == fksDdVgaml){XhndEZfHzC = true;}
      if(aMQmAhpWBh == gJjWiTbkng){PjlORCLGIn = true;}
      else if(gJjWiTbkng == aMQmAhpWBh){znmmzSxwoL = true;}
      if(suDDLeJPBp == nfMQADTkYC){SuBVVrQYTe = true;}
      else if(nfMQADTkYC == suDDLeJPBp){okeWfEMgKB = true;}
      if(cRLudQJgSt == VJBReWiAzl){tlCOHBaafS = true;}
      else if(VJBReWiAzl == cRLudQJgSt){EKAoqEfzju = true;}
      if(XyqexpORZM == felQMZjRkO){gzWYFGFuuf = true;}
      else if(felQMZjRkO == XyqexpORZM){GgwpjuijuM = true;}
      if(gAwqlkgprz == emGoAJfqok){JHyFVWQEDl = true;}
      else if(emGoAJfqok == gAwqlkgprz){HSXPmmDQxz = true;}
      if(LRZxJIAVJj == DKQfVWHRqL){mbjJychXHQ = true;}
      if(XIEGJtEXFU == jalBAIswEZ){ajapGTXbQP = true;}
      if(PqpnJbUUIs == SBzJWhDMQV){lUdnUlnwrj = true;}
      while(DKQfVWHRqL == LRZxJIAVJj){Nzwyxonywt = true;}
      while(jalBAIswEZ == jalBAIswEZ){lyLtFHnnlj = true;}
      while(SBzJWhDMQV == SBzJWhDMQV){VbkysllkCE = true;}
      if(prKNhUOGto == true){prKNhUOGto = false;}
      if(SRaYdDAEor == true){SRaYdDAEor = false;}
      if(PjlORCLGIn == true){PjlORCLGIn = false;}
      if(SuBVVrQYTe == true){SuBVVrQYTe = false;}
      if(tlCOHBaafS == true){tlCOHBaafS = false;}
      if(gzWYFGFuuf == true){gzWYFGFuuf = false;}
      if(JHyFVWQEDl == true){JHyFVWQEDl = false;}
      if(mbjJychXHQ == true){mbjJychXHQ = false;}
      if(ajapGTXbQP == true){ajapGTXbQP = false;}
      if(lUdnUlnwrj == true){lUdnUlnwrj = false;}
      if(jVXteFONab == true){jVXteFONab = false;}
      if(XhndEZfHzC == true){XhndEZfHzC = false;}
      if(znmmzSxwoL == true){znmmzSxwoL = false;}
      if(okeWfEMgKB == true){okeWfEMgKB = false;}
      if(EKAoqEfzju == true){EKAoqEfzju = false;}
      if(GgwpjuijuM == true){GgwpjuijuM = false;}
      if(HSXPmmDQxz == true){HSXPmmDQxz = false;}
      if(Nzwyxonywt == true){Nzwyxonywt = false;}
      if(lyLtFHnnlj == true){lyLtFHnnlj = false;}
      if(VbkysllkCE == true){VbkysllkCE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGOCKHCMYR
{ 
  void hNRQpGImWB()
  { 
      bool RQwfiVdxtt = false;
      bool zWPRPcRiLn = false;
      bool dLbTeYQPDb = false;
      bool LfrlIRVDGE = false;
      bool qRdFBkfHuk = false;
      bool zRCWAFobAJ = false;
      bool ENtRiTedJy = false;
      bool GObGwMhVSt = false;
      bool rJURcscUkD = false;
      bool ctCwAcWLWh = false;
      bool GByxdjouZm = false;
      bool WSJGQtsboo = false;
      bool pJrFUMMfGT = false;
      bool pWzkmqKXmr = false;
      bool EhuyfJkueF = false;
      bool jtVhqwIrbR = false;
      bool XJoGxASYSZ = false;
      bool jVnxjIOtZL = false;
      bool aRABjuARsq = false;
      bool hSuVUurnAe = false;
      string WMFoMzgmJN;
      string fTibkNFqnb;
      string ecBWnIEjQq;
      string aCDGpJJjuu;
      string SNImWEaHwe;
      string BBKfBsKhBD;
      string txWRldQcla;
      string DUusIQUNAi;
      string gxmkpYqWEw;
      string zaiqAVppBs;
      string nyUUagFRXj;
      string XxhRWxJkaM;
      string lsXobbkEsl;
      string aeMGuibSKJ;
      string SZzUYBsRUD;
      string MFPnGtZfrz;
      string uBYkJsjbVn;
      string UqaRsMtDQZ;
      string iSioZUPXzB;
      string IuZKNRBNLe;
      if(WMFoMzgmJN == nyUUagFRXj){RQwfiVdxtt = true;}
      else if(nyUUagFRXj == WMFoMzgmJN){GByxdjouZm = true;}
      if(fTibkNFqnb == XxhRWxJkaM){zWPRPcRiLn = true;}
      else if(XxhRWxJkaM == fTibkNFqnb){WSJGQtsboo = true;}
      if(ecBWnIEjQq == lsXobbkEsl){dLbTeYQPDb = true;}
      else if(lsXobbkEsl == ecBWnIEjQq){pJrFUMMfGT = true;}
      if(aCDGpJJjuu == aeMGuibSKJ){LfrlIRVDGE = true;}
      else if(aeMGuibSKJ == aCDGpJJjuu){pWzkmqKXmr = true;}
      if(SNImWEaHwe == SZzUYBsRUD){qRdFBkfHuk = true;}
      else if(SZzUYBsRUD == SNImWEaHwe){EhuyfJkueF = true;}
      if(BBKfBsKhBD == MFPnGtZfrz){zRCWAFobAJ = true;}
      else if(MFPnGtZfrz == BBKfBsKhBD){jtVhqwIrbR = true;}
      if(txWRldQcla == uBYkJsjbVn){ENtRiTedJy = true;}
      else if(uBYkJsjbVn == txWRldQcla){XJoGxASYSZ = true;}
      if(DUusIQUNAi == UqaRsMtDQZ){GObGwMhVSt = true;}
      if(gxmkpYqWEw == iSioZUPXzB){rJURcscUkD = true;}
      if(zaiqAVppBs == IuZKNRBNLe){ctCwAcWLWh = true;}
      while(UqaRsMtDQZ == DUusIQUNAi){jVnxjIOtZL = true;}
      while(iSioZUPXzB == iSioZUPXzB){aRABjuARsq = true;}
      while(IuZKNRBNLe == IuZKNRBNLe){hSuVUurnAe = true;}
      if(RQwfiVdxtt == true){RQwfiVdxtt = false;}
      if(zWPRPcRiLn == true){zWPRPcRiLn = false;}
      if(dLbTeYQPDb == true){dLbTeYQPDb = false;}
      if(LfrlIRVDGE == true){LfrlIRVDGE = false;}
      if(qRdFBkfHuk == true){qRdFBkfHuk = false;}
      if(zRCWAFobAJ == true){zRCWAFobAJ = false;}
      if(ENtRiTedJy == true){ENtRiTedJy = false;}
      if(GObGwMhVSt == true){GObGwMhVSt = false;}
      if(rJURcscUkD == true){rJURcscUkD = false;}
      if(ctCwAcWLWh == true){ctCwAcWLWh = false;}
      if(GByxdjouZm == true){GByxdjouZm = false;}
      if(WSJGQtsboo == true){WSJGQtsboo = false;}
      if(pJrFUMMfGT == true){pJrFUMMfGT = false;}
      if(pWzkmqKXmr == true){pWzkmqKXmr = false;}
      if(EhuyfJkueF == true){EhuyfJkueF = false;}
      if(jtVhqwIrbR == true){jtVhqwIrbR = false;}
      if(XJoGxASYSZ == true){XJoGxASYSZ = false;}
      if(jVnxjIOtZL == true){jVnxjIOtZL = false;}
      if(aRABjuARsq == true){aRABjuARsq = false;}
      if(hSuVUurnAe == true){hSuVUurnAe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSDZJWZPIV
{ 
  void hnTaQOFPnE()
  { 
      bool QGcLeiWaXb = false;
      bool JdnHUhAmuM = false;
      bool JfyrAwBmEC = false;
      bool BXTTWyxzVF = false;
      bool fJybQFgTEy = false;
      bool PNUuLjIkKi = false;
      bool hjWVakJTkV = false;
      bool kARofAhVat = false;
      bool OghGlmDXIl = false;
      bool pLnlWwlcBf = false;
      bool uNhiNPweOK = false;
      bool ClKQTBBPjm = false;
      bool gkLzfYMeSj = false;
      bool NFTtzByzsW = false;
      bool pYJxjEBXSV = false;
      bool tWsNzJCiCn = false;
      bool DRMdwxRPRS = false;
      bool CBWMxHbNOb = false;
      bool WnMwpqMFuo = false;
      bool zOwETYMeAm = false;
      string CmgSnbruNZ;
      string oHsxrqtLUx;
      string rZXrTWdTpN;
      string lWiSjAhkkK;
      string kEnYnJdwty;
      string psuyqcPnzQ;
      string xYFzmSYZMr;
      string IIaJMmkyDJ;
      string rhYqXsakaH;
      string jtlTMLznkV;
      string kEiCpgRkkD;
      string qQjpXPzObt;
      string qnzFHOWGxB;
      string nwNhXnyWAp;
      string aozXPTJuuw;
      string LkMqdxEcua;
      string JKnjPtDCRj;
      string RcNkSCnaom;
      string FaKAoDjWEZ;
      string iUbZgPBPHV;
      if(CmgSnbruNZ == kEiCpgRkkD){QGcLeiWaXb = true;}
      else if(kEiCpgRkkD == CmgSnbruNZ){uNhiNPweOK = true;}
      if(oHsxrqtLUx == qQjpXPzObt){JdnHUhAmuM = true;}
      else if(qQjpXPzObt == oHsxrqtLUx){ClKQTBBPjm = true;}
      if(rZXrTWdTpN == qnzFHOWGxB){JfyrAwBmEC = true;}
      else if(qnzFHOWGxB == rZXrTWdTpN){gkLzfYMeSj = true;}
      if(lWiSjAhkkK == nwNhXnyWAp){BXTTWyxzVF = true;}
      else if(nwNhXnyWAp == lWiSjAhkkK){NFTtzByzsW = true;}
      if(kEnYnJdwty == aozXPTJuuw){fJybQFgTEy = true;}
      else if(aozXPTJuuw == kEnYnJdwty){pYJxjEBXSV = true;}
      if(psuyqcPnzQ == LkMqdxEcua){PNUuLjIkKi = true;}
      else if(LkMqdxEcua == psuyqcPnzQ){tWsNzJCiCn = true;}
      if(xYFzmSYZMr == JKnjPtDCRj){hjWVakJTkV = true;}
      else if(JKnjPtDCRj == xYFzmSYZMr){DRMdwxRPRS = true;}
      if(IIaJMmkyDJ == RcNkSCnaom){kARofAhVat = true;}
      if(rhYqXsakaH == FaKAoDjWEZ){OghGlmDXIl = true;}
      if(jtlTMLznkV == iUbZgPBPHV){pLnlWwlcBf = true;}
      while(RcNkSCnaom == IIaJMmkyDJ){CBWMxHbNOb = true;}
      while(FaKAoDjWEZ == FaKAoDjWEZ){WnMwpqMFuo = true;}
      while(iUbZgPBPHV == iUbZgPBPHV){zOwETYMeAm = true;}
      if(QGcLeiWaXb == true){QGcLeiWaXb = false;}
      if(JdnHUhAmuM == true){JdnHUhAmuM = false;}
      if(JfyrAwBmEC == true){JfyrAwBmEC = false;}
      if(BXTTWyxzVF == true){BXTTWyxzVF = false;}
      if(fJybQFgTEy == true){fJybQFgTEy = false;}
      if(PNUuLjIkKi == true){PNUuLjIkKi = false;}
      if(hjWVakJTkV == true){hjWVakJTkV = false;}
      if(kARofAhVat == true){kARofAhVat = false;}
      if(OghGlmDXIl == true){OghGlmDXIl = false;}
      if(pLnlWwlcBf == true){pLnlWwlcBf = false;}
      if(uNhiNPweOK == true){uNhiNPweOK = false;}
      if(ClKQTBBPjm == true){ClKQTBBPjm = false;}
      if(gkLzfYMeSj == true){gkLzfYMeSj = false;}
      if(NFTtzByzsW == true){NFTtzByzsW = false;}
      if(pYJxjEBXSV == true){pYJxjEBXSV = false;}
      if(tWsNzJCiCn == true){tWsNzJCiCn = false;}
      if(DRMdwxRPRS == true){DRMdwxRPRS = false;}
      if(CBWMxHbNOb == true){CBWMxHbNOb = false;}
      if(WnMwpqMFuo == true){WnMwpqMFuo = false;}
      if(zOwETYMeAm == true){zOwETYMeAm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XBHDNAGWXY
{ 
  void wjqKMbNBMX()
  { 
      bool mBGEjahBij = false;
      bool MuiLfidAsu = false;
      bool HSGzPiiqXp = false;
      bool BpKziufbYN = false;
      bool zgoRGTnWVP = false;
      bool KYMyGTuHnA = false;
      bool rqcriVkjbk = false;
      bool DBafwZcnrw = false;
      bool uLVIebdLsO = false;
      bool AYmYVIDxhj = false;
      bool iEukLJyfCf = false;
      bool qGOrEfUTMH = false;
      bool rYpNjeNCKn = false;
      bool VfGHMqQjwV = false;
      bool cxJMXtJuTp = false;
      bool mjjarKNgAg = false;
      bool uwVNJKzGfN = false;
      bool OkWpetOdop = false;
      bool UShTBlwfPB = false;
      bool djjOafbwDM = false;
      string ryPbqWUWDP;
      string hbwdbTPQyT;
      string EblLJELnhL;
      string FbjKOTikSd;
      string IqGEbmNcpT;
      string LbfcAQLERl;
      string KfnqJGrlOI;
      string jeyUKMUhiW;
      string qixOAduGKy;
      string IeTfSbCOtV;
      string taNgigcLRm;
      string udUtubhZqf;
      string KkbQAFKRBi;
      string KFmMbPUPfT;
      string AjoWDdJYkq;
      string scXOLIzxgc;
      string VLJicoqHSf;
      string GRtWfawENV;
      string wlgJoghXBS;
      string PWiCyoZFtN;
      if(ryPbqWUWDP == taNgigcLRm){mBGEjahBij = true;}
      else if(taNgigcLRm == ryPbqWUWDP){iEukLJyfCf = true;}
      if(hbwdbTPQyT == udUtubhZqf){MuiLfidAsu = true;}
      else if(udUtubhZqf == hbwdbTPQyT){qGOrEfUTMH = true;}
      if(EblLJELnhL == KkbQAFKRBi){HSGzPiiqXp = true;}
      else if(KkbQAFKRBi == EblLJELnhL){rYpNjeNCKn = true;}
      if(FbjKOTikSd == KFmMbPUPfT){BpKziufbYN = true;}
      else if(KFmMbPUPfT == FbjKOTikSd){VfGHMqQjwV = true;}
      if(IqGEbmNcpT == AjoWDdJYkq){zgoRGTnWVP = true;}
      else if(AjoWDdJYkq == IqGEbmNcpT){cxJMXtJuTp = true;}
      if(LbfcAQLERl == scXOLIzxgc){KYMyGTuHnA = true;}
      else if(scXOLIzxgc == LbfcAQLERl){mjjarKNgAg = true;}
      if(KfnqJGrlOI == VLJicoqHSf){rqcriVkjbk = true;}
      else if(VLJicoqHSf == KfnqJGrlOI){uwVNJKzGfN = true;}
      if(jeyUKMUhiW == GRtWfawENV){DBafwZcnrw = true;}
      if(qixOAduGKy == wlgJoghXBS){uLVIebdLsO = true;}
      if(IeTfSbCOtV == PWiCyoZFtN){AYmYVIDxhj = true;}
      while(GRtWfawENV == jeyUKMUhiW){OkWpetOdop = true;}
      while(wlgJoghXBS == wlgJoghXBS){UShTBlwfPB = true;}
      while(PWiCyoZFtN == PWiCyoZFtN){djjOafbwDM = true;}
      if(mBGEjahBij == true){mBGEjahBij = false;}
      if(MuiLfidAsu == true){MuiLfidAsu = false;}
      if(HSGzPiiqXp == true){HSGzPiiqXp = false;}
      if(BpKziufbYN == true){BpKziufbYN = false;}
      if(zgoRGTnWVP == true){zgoRGTnWVP = false;}
      if(KYMyGTuHnA == true){KYMyGTuHnA = false;}
      if(rqcriVkjbk == true){rqcriVkjbk = false;}
      if(DBafwZcnrw == true){DBafwZcnrw = false;}
      if(uLVIebdLsO == true){uLVIebdLsO = false;}
      if(AYmYVIDxhj == true){AYmYVIDxhj = false;}
      if(iEukLJyfCf == true){iEukLJyfCf = false;}
      if(qGOrEfUTMH == true){qGOrEfUTMH = false;}
      if(rYpNjeNCKn == true){rYpNjeNCKn = false;}
      if(VfGHMqQjwV == true){VfGHMqQjwV = false;}
      if(cxJMXtJuTp == true){cxJMXtJuTp = false;}
      if(mjjarKNgAg == true){mjjarKNgAg = false;}
      if(uwVNJKzGfN == true){uwVNJKzGfN = false;}
      if(OkWpetOdop == true){OkWpetOdop = false;}
      if(UShTBlwfPB == true){UShTBlwfPB = false;}
      if(djjOafbwDM == true){djjOafbwDM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDLNOCQEKM
{ 
  void TIONbCxsjG()
  { 
      bool TexPdjArzD = false;
      bool VyFXejFeVj = false;
      bool WZhQDATMzz = false;
      bool KDITXwlqUh = false;
      bool kXTTMJMQwn = false;
      bool SpVKAsxgLc = false;
      bool PnsArRplAh = false;
      bool yNKnyyGNDt = false;
      bool nCQKfUgxTd = false;
      bool zEfrRxdTat = false;
      bool TaQNoEfgMB = false;
      bool midRoMWiTX = false;
      bool jrSVhthSWB = false;
      bool UlmJZMlCUa = false;
      bool ozkRpQaNDE = false;
      bool ZuADJaIteu = false;
      bool WMKLfBwTqb = false;
      bool aUNrikHAfR = false;
      bool STPRaZkizz = false;
      bool DrWZEboZlo = false;
      string lNRkwdpwhF;
      string byjmRePkBL;
      string VFBlsqjBYW;
      string MYrzKLZmDZ;
      string tiqaQzIYaX;
      string cdAOjgLerF;
      string snWKsCFjcF;
      string FbgbQmNZUs;
      string iKaAthXdOc;
      string AtuyfGLghO;
      string sXwVRBwYyx;
      string TlKyWiNWQK;
      string ebVzFLgiuK;
      string agqGzKOEhs;
      string lyfRJNiwbx;
      string roQXiRCwPG;
      string UNcnVmtEyL;
      string TInXXfuDpq;
      string bjHyRlQTWh;
      string ISoaYYUruW;
      if(lNRkwdpwhF == sXwVRBwYyx){TexPdjArzD = true;}
      else if(sXwVRBwYyx == lNRkwdpwhF){TaQNoEfgMB = true;}
      if(byjmRePkBL == TlKyWiNWQK){VyFXejFeVj = true;}
      else if(TlKyWiNWQK == byjmRePkBL){midRoMWiTX = true;}
      if(VFBlsqjBYW == ebVzFLgiuK){WZhQDATMzz = true;}
      else if(ebVzFLgiuK == VFBlsqjBYW){jrSVhthSWB = true;}
      if(MYrzKLZmDZ == agqGzKOEhs){KDITXwlqUh = true;}
      else if(agqGzKOEhs == MYrzKLZmDZ){UlmJZMlCUa = true;}
      if(tiqaQzIYaX == lyfRJNiwbx){kXTTMJMQwn = true;}
      else if(lyfRJNiwbx == tiqaQzIYaX){ozkRpQaNDE = true;}
      if(cdAOjgLerF == roQXiRCwPG){SpVKAsxgLc = true;}
      else if(roQXiRCwPG == cdAOjgLerF){ZuADJaIteu = true;}
      if(snWKsCFjcF == UNcnVmtEyL){PnsArRplAh = true;}
      else if(UNcnVmtEyL == snWKsCFjcF){WMKLfBwTqb = true;}
      if(FbgbQmNZUs == TInXXfuDpq){yNKnyyGNDt = true;}
      if(iKaAthXdOc == bjHyRlQTWh){nCQKfUgxTd = true;}
      if(AtuyfGLghO == ISoaYYUruW){zEfrRxdTat = true;}
      while(TInXXfuDpq == FbgbQmNZUs){aUNrikHAfR = true;}
      while(bjHyRlQTWh == bjHyRlQTWh){STPRaZkizz = true;}
      while(ISoaYYUruW == ISoaYYUruW){DrWZEboZlo = true;}
      if(TexPdjArzD == true){TexPdjArzD = false;}
      if(VyFXejFeVj == true){VyFXejFeVj = false;}
      if(WZhQDATMzz == true){WZhQDATMzz = false;}
      if(KDITXwlqUh == true){KDITXwlqUh = false;}
      if(kXTTMJMQwn == true){kXTTMJMQwn = false;}
      if(SpVKAsxgLc == true){SpVKAsxgLc = false;}
      if(PnsArRplAh == true){PnsArRplAh = false;}
      if(yNKnyyGNDt == true){yNKnyyGNDt = false;}
      if(nCQKfUgxTd == true){nCQKfUgxTd = false;}
      if(zEfrRxdTat == true){zEfrRxdTat = false;}
      if(TaQNoEfgMB == true){TaQNoEfgMB = false;}
      if(midRoMWiTX == true){midRoMWiTX = false;}
      if(jrSVhthSWB == true){jrSVhthSWB = false;}
      if(UlmJZMlCUa == true){UlmJZMlCUa = false;}
      if(ozkRpQaNDE == true){ozkRpQaNDE = false;}
      if(ZuADJaIteu == true){ZuADJaIteu = false;}
      if(WMKLfBwTqb == true){WMKLfBwTqb = false;}
      if(aUNrikHAfR == true){aUNrikHAfR = false;}
      if(STPRaZkizz == true){STPRaZkizz = false;}
      if(DrWZEboZlo == true){DrWZEboZlo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBUKJBWXNE
{ 
  void OTrpNXSLdl()
  { 
      bool jwdDHfElMW = false;
      bool ShMENbIUik = false;
      bool pjuGQYoeAE = false;
      bool jwnJPqSlle = false;
      bool CPtFItyYwf = false;
      bool COhmszBXlh = false;
      bool pZkIlVsCoW = false;
      bool IViDiapoxW = false;
      bool aPiUCVOBPP = false;
      bool ptADncdkTl = false;
      bool BuiZWffdES = false;
      bool ILaPGaqQGQ = false;
      bool HqlYgOVePF = false;
      bool xEVKUfgIxV = false;
      bool okxxHdTjwN = false;
      bool lNeCeJJKsI = false;
      bool JANyVDoQta = false;
      bool thTjaVtoRC = false;
      bool tlhCTiZTeL = false;
      bool VVPnMnWzbD = false;
      string PHXHVLjfcA;
      string rHxokDXcRU;
      string XlzCCJQVFR;
      string hbWHxIhIan;
      string MXzRZoOVHg;
      string zmdJucHUEM;
      string uOaKSQkpqb;
      string VOBdHAlhcN;
      string uuNXStyMMT;
      string BMEOryxnzJ;
      string EXdeKjkzCu;
      string qZrqQAACrX;
      string SXdWaIKmkI;
      string CyhTIWQhMh;
      string IyKQcaUMxq;
      string ytwbqgtGEC;
      string ZyOssrqXht;
      string jSpJOTNMtz;
      string nxosKHCGcb;
      string cKdKIKiQXj;
      if(PHXHVLjfcA == EXdeKjkzCu){jwdDHfElMW = true;}
      else if(EXdeKjkzCu == PHXHVLjfcA){BuiZWffdES = true;}
      if(rHxokDXcRU == qZrqQAACrX){ShMENbIUik = true;}
      else if(qZrqQAACrX == rHxokDXcRU){ILaPGaqQGQ = true;}
      if(XlzCCJQVFR == SXdWaIKmkI){pjuGQYoeAE = true;}
      else if(SXdWaIKmkI == XlzCCJQVFR){HqlYgOVePF = true;}
      if(hbWHxIhIan == CyhTIWQhMh){jwnJPqSlle = true;}
      else if(CyhTIWQhMh == hbWHxIhIan){xEVKUfgIxV = true;}
      if(MXzRZoOVHg == IyKQcaUMxq){CPtFItyYwf = true;}
      else if(IyKQcaUMxq == MXzRZoOVHg){okxxHdTjwN = true;}
      if(zmdJucHUEM == ytwbqgtGEC){COhmszBXlh = true;}
      else if(ytwbqgtGEC == zmdJucHUEM){lNeCeJJKsI = true;}
      if(uOaKSQkpqb == ZyOssrqXht){pZkIlVsCoW = true;}
      else if(ZyOssrqXht == uOaKSQkpqb){JANyVDoQta = true;}
      if(VOBdHAlhcN == jSpJOTNMtz){IViDiapoxW = true;}
      if(uuNXStyMMT == nxosKHCGcb){aPiUCVOBPP = true;}
      if(BMEOryxnzJ == cKdKIKiQXj){ptADncdkTl = true;}
      while(jSpJOTNMtz == VOBdHAlhcN){thTjaVtoRC = true;}
      while(nxosKHCGcb == nxosKHCGcb){tlhCTiZTeL = true;}
      while(cKdKIKiQXj == cKdKIKiQXj){VVPnMnWzbD = true;}
      if(jwdDHfElMW == true){jwdDHfElMW = false;}
      if(ShMENbIUik == true){ShMENbIUik = false;}
      if(pjuGQYoeAE == true){pjuGQYoeAE = false;}
      if(jwnJPqSlle == true){jwnJPqSlle = false;}
      if(CPtFItyYwf == true){CPtFItyYwf = false;}
      if(COhmszBXlh == true){COhmszBXlh = false;}
      if(pZkIlVsCoW == true){pZkIlVsCoW = false;}
      if(IViDiapoxW == true){IViDiapoxW = false;}
      if(aPiUCVOBPP == true){aPiUCVOBPP = false;}
      if(ptADncdkTl == true){ptADncdkTl = false;}
      if(BuiZWffdES == true){BuiZWffdES = false;}
      if(ILaPGaqQGQ == true){ILaPGaqQGQ = false;}
      if(HqlYgOVePF == true){HqlYgOVePF = false;}
      if(xEVKUfgIxV == true){xEVKUfgIxV = false;}
      if(okxxHdTjwN == true){okxxHdTjwN = false;}
      if(lNeCeJJKsI == true){lNeCeJJKsI = false;}
      if(JANyVDoQta == true){JANyVDoQta = false;}
      if(thTjaVtoRC == true){thTjaVtoRC = false;}
      if(tlhCTiZTeL == true){tlhCTiZTeL = false;}
      if(VVPnMnWzbD == true){VVPnMnWzbD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LDOFQHKWCS
{ 
  void rcMNXYunye()
  { 
      bool aiaPTGbnMO = false;
      bool GufFQiynRS = false;
      bool dCbatWbjSs = false;
      bool QlcpunjOEK = false;
      bool ramGTtphhL = false;
      bool NkyPqXGAUw = false;
      bool drVTxTRoJb = false;
      bool ziiGZDOVHA = false;
      bool gsBGefnNyW = false;
      bool hitIgAETJz = false;
      bool bAYGLdBqon = false;
      bool JkrUOjpPnQ = false;
      bool fEqmtPoZZZ = false;
      bool yuLHXgUutA = false;
      bool dwXKNwqYsw = false;
      bool JoerTXJkLw = false;
      bool obROoNYjwh = false;
      bool OuUmmiffYx = false;
      bool YQfcQJPTnA = false;
      bool WiiyLCeJVz = false;
      string dqlFyuobaL;
      string BJfJzxmDQS;
      string nxoEckERdC;
      string RnkNHBmnsK;
      string bdbHuiDWZA;
      string fSDObfChcN;
      string pXyYsMXRCy;
      string JyKFqKUgIs;
      string ghqcWyjVla;
      string yFLfUDfDNh;
      string KlTaqgIyWR;
      string LVYifHgUCu;
      string cBfbzDmekn;
      string eRSahuOPlo;
      string plzUPcgbzM;
      string WKBSFIGrbm;
      string tcMilsCyAj;
      string sQiMFpCKLV;
      string WKeYQTPAVZ;
      string oVnytMYPhV;
      if(dqlFyuobaL == KlTaqgIyWR){aiaPTGbnMO = true;}
      else if(KlTaqgIyWR == dqlFyuobaL){bAYGLdBqon = true;}
      if(BJfJzxmDQS == LVYifHgUCu){GufFQiynRS = true;}
      else if(LVYifHgUCu == BJfJzxmDQS){JkrUOjpPnQ = true;}
      if(nxoEckERdC == cBfbzDmekn){dCbatWbjSs = true;}
      else if(cBfbzDmekn == nxoEckERdC){fEqmtPoZZZ = true;}
      if(RnkNHBmnsK == eRSahuOPlo){QlcpunjOEK = true;}
      else if(eRSahuOPlo == RnkNHBmnsK){yuLHXgUutA = true;}
      if(bdbHuiDWZA == plzUPcgbzM){ramGTtphhL = true;}
      else if(plzUPcgbzM == bdbHuiDWZA){dwXKNwqYsw = true;}
      if(fSDObfChcN == WKBSFIGrbm){NkyPqXGAUw = true;}
      else if(WKBSFIGrbm == fSDObfChcN){JoerTXJkLw = true;}
      if(pXyYsMXRCy == tcMilsCyAj){drVTxTRoJb = true;}
      else if(tcMilsCyAj == pXyYsMXRCy){obROoNYjwh = true;}
      if(JyKFqKUgIs == sQiMFpCKLV){ziiGZDOVHA = true;}
      if(ghqcWyjVla == WKeYQTPAVZ){gsBGefnNyW = true;}
      if(yFLfUDfDNh == oVnytMYPhV){hitIgAETJz = true;}
      while(sQiMFpCKLV == JyKFqKUgIs){OuUmmiffYx = true;}
      while(WKeYQTPAVZ == WKeYQTPAVZ){YQfcQJPTnA = true;}
      while(oVnytMYPhV == oVnytMYPhV){WiiyLCeJVz = true;}
      if(aiaPTGbnMO == true){aiaPTGbnMO = false;}
      if(GufFQiynRS == true){GufFQiynRS = false;}
      if(dCbatWbjSs == true){dCbatWbjSs = false;}
      if(QlcpunjOEK == true){QlcpunjOEK = false;}
      if(ramGTtphhL == true){ramGTtphhL = false;}
      if(NkyPqXGAUw == true){NkyPqXGAUw = false;}
      if(drVTxTRoJb == true){drVTxTRoJb = false;}
      if(ziiGZDOVHA == true){ziiGZDOVHA = false;}
      if(gsBGefnNyW == true){gsBGefnNyW = false;}
      if(hitIgAETJz == true){hitIgAETJz = false;}
      if(bAYGLdBqon == true){bAYGLdBqon = false;}
      if(JkrUOjpPnQ == true){JkrUOjpPnQ = false;}
      if(fEqmtPoZZZ == true){fEqmtPoZZZ = false;}
      if(yuLHXgUutA == true){yuLHXgUutA = false;}
      if(dwXKNwqYsw == true){dwXKNwqYsw = false;}
      if(JoerTXJkLw == true){JoerTXJkLw = false;}
      if(obROoNYjwh == true){obROoNYjwh = false;}
      if(OuUmmiffYx == true){OuUmmiffYx = false;}
      if(YQfcQJPTnA == true){YQfcQJPTnA = false;}
      if(WiiyLCeJVz == true){WiiyLCeJVz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XKRXYDYHBN
{ 
  void rPckaudewM()
  { 
      bool jPhzDajXMr = false;
      bool jfoHdnVkeD = false;
      bool FIttTGWgqM = false;
      bool zYOaWkjkzi = false;
      bool MSpaXhzGXP = false;
      bool lTUePaVnfw = false;
      bool ECfAsLROkr = false;
      bool DklupmSSVk = false;
      bool HPJbZeDiLu = false;
      bool PwECdKmohM = false;
      bool QkVeLAhYob = false;
      bool ICRuonrDZN = false;
      bool HiCocHgiRf = false;
      bool zcjJUWteQZ = false;
      bool wdsimMdJNo = false;
      bool SiPTEhhfBE = false;
      bool TzHIceRIaS = false;
      bool sMmAQcoSCP = false;
      bool cXUbMPNQEm = false;
      bool nOcMGxWjGH = false;
      string gwkgTVXAYI;
      string tXrJtmbGzi;
      string ontuXrUNru;
      string jHJMTwzQhX;
      string kqDpijprQz;
      string XwTJNsBpJa;
      string AKIdXmNfpy;
      string nLXaxykDLn;
      string CcwrWnmAza;
      string tIGGXaiZSu;
      string VKBSLLYsLP;
      string HxdUYXOPGj;
      string zMgPDfERDW;
      string PKkPRqacgK;
      string OtniSwdlgA;
      string MSThwIclOe;
      string HGooAxMNDg;
      string wkiuUEXxwH;
      string BSjDKwqDTI;
      string NoOBDIFziU;
      if(gwkgTVXAYI == VKBSLLYsLP){jPhzDajXMr = true;}
      else if(VKBSLLYsLP == gwkgTVXAYI){QkVeLAhYob = true;}
      if(tXrJtmbGzi == HxdUYXOPGj){jfoHdnVkeD = true;}
      else if(HxdUYXOPGj == tXrJtmbGzi){ICRuonrDZN = true;}
      if(ontuXrUNru == zMgPDfERDW){FIttTGWgqM = true;}
      else if(zMgPDfERDW == ontuXrUNru){HiCocHgiRf = true;}
      if(jHJMTwzQhX == PKkPRqacgK){zYOaWkjkzi = true;}
      else if(PKkPRqacgK == jHJMTwzQhX){zcjJUWteQZ = true;}
      if(kqDpijprQz == OtniSwdlgA){MSpaXhzGXP = true;}
      else if(OtniSwdlgA == kqDpijprQz){wdsimMdJNo = true;}
      if(XwTJNsBpJa == MSThwIclOe){lTUePaVnfw = true;}
      else if(MSThwIclOe == XwTJNsBpJa){SiPTEhhfBE = true;}
      if(AKIdXmNfpy == HGooAxMNDg){ECfAsLROkr = true;}
      else if(HGooAxMNDg == AKIdXmNfpy){TzHIceRIaS = true;}
      if(nLXaxykDLn == wkiuUEXxwH){DklupmSSVk = true;}
      if(CcwrWnmAza == BSjDKwqDTI){HPJbZeDiLu = true;}
      if(tIGGXaiZSu == NoOBDIFziU){PwECdKmohM = true;}
      while(wkiuUEXxwH == nLXaxykDLn){sMmAQcoSCP = true;}
      while(BSjDKwqDTI == BSjDKwqDTI){cXUbMPNQEm = true;}
      while(NoOBDIFziU == NoOBDIFziU){nOcMGxWjGH = true;}
      if(jPhzDajXMr == true){jPhzDajXMr = false;}
      if(jfoHdnVkeD == true){jfoHdnVkeD = false;}
      if(FIttTGWgqM == true){FIttTGWgqM = false;}
      if(zYOaWkjkzi == true){zYOaWkjkzi = false;}
      if(MSpaXhzGXP == true){MSpaXhzGXP = false;}
      if(lTUePaVnfw == true){lTUePaVnfw = false;}
      if(ECfAsLROkr == true){ECfAsLROkr = false;}
      if(DklupmSSVk == true){DklupmSSVk = false;}
      if(HPJbZeDiLu == true){HPJbZeDiLu = false;}
      if(PwECdKmohM == true){PwECdKmohM = false;}
      if(QkVeLAhYob == true){QkVeLAhYob = false;}
      if(ICRuonrDZN == true){ICRuonrDZN = false;}
      if(HiCocHgiRf == true){HiCocHgiRf = false;}
      if(zcjJUWteQZ == true){zcjJUWteQZ = false;}
      if(wdsimMdJNo == true){wdsimMdJNo = false;}
      if(SiPTEhhfBE == true){SiPTEhhfBE = false;}
      if(TzHIceRIaS == true){TzHIceRIaS = false;}
      if(sMmAQcoSCP == true){sMmAQcoSCP = false;}
      if(cXUbMPNQEm == true){cXUbMPNQEm = false;}
      if(nOcMGxWjGH == true){nOcMGxWjGH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SQBNPPZMKW
{ 
  void gcLqzIESbe()
  { 
      bool kcKnjAyDCf = false;
      bool WFBWEehnpb = false;
      bool qgXszVnIFT = false;
      bool geAJfMHixf = false;
      bool YTPgmrWsJE = false;
      bool ynDYdDFQnN = false;
      bool MpxiyqFqqr = false;
      bool XypJCXRpGH = false;
      bool ztyBUsaaeb = false;
      bool HquiTiWfiu = false;
      bool meBRgzxtWG = false;
      bool lOKfORrwNF = false;
      bool QeMPjfCGoS = false;
      bool AkHLUUsfTV = false;
      bool wfDXosfOUC = false;
      bool qZRddIRlhA = false;
      bool xpFDFAGzLs = false;
      bool XMbrIjaoZq = false;
      bool AnllbaTdgM = false;
      bool DHxTYFazRn = false;
      string EFcehllPYt;
      string uxfXjzMDQP;
      string xldokRkkVo;
      string KFiklfqNFb;
      string PzCVnxDirJ;
      string cLXJqRbntQ;
      string ABtjipOukE;
      string HzxnAyjHAm;
      string NCrLLyhZsT;
      string DCTnbNERmy;
      string iIynBdNiIs;
      string hTnGCxIhXj;
      string InBRAFfIMl;
      string sRUCDEEEKh;
      string kyQAljOMld;
      string FVtCotGfnu;
      string yEWWzPzkCx;
      string sEXpzJXBeQ;
      string pSWhgXXSMJ;
      string yXQOjfbsAV;
      if(EFcehllPYt == iIynBdNiIs){kcKnjAyDCf = true;}
      else if(iIynBdNiIs == EFcehllPYt){meBRgzxtWG = true;}
      if(uxfXjzMDQP == hTnGCxIhXj){WFBWEehnpb = true;}
      else if(hTnGCxIhXj == uxfXjzMDQP){lOKfORrwNF = true;}
      if(xldokRkkVo == InBRAFfIMl){qgXszVnIFT = true;}
      else if(InBRAFfIMl == xldokRkkVo){QeMPjfCGoS = true;}
      if(KFiklfqNFb == sRUCDEEEKh){geAJfMHixf = true;}
      else if(sRUCDEEEKh == KFiklfqNFb){AkHLUUsfTV = true;}
      if(PzCVnxDirJ == kyQAljOMld){YTPgmrWsJE = true;}
      else if(kyQAljOMld == PzCVnxDirJ){wfDXosfOUC = true;}
      if(cLXJqRbntQ == FVtCotGfnu){ynDYdDFQnN = true;}
      else if(FVtCotGfnu == cLXJqRbntQ){qZRddIRlhA = true;}
      if(ABtjipOukE == yEWWzPzkCx){MpxiyqFqqr = true;}
      else if(yEWWzPzkCx == ABtjipOukE){xpFDFAGzLs = true;}
      if(HzxnAyjHAm == sEXpzJXBeQ){XypJCXRpGH = true;}
      if(NCrLLyhZsT == pSWhgXXSMJ){ztyBUsaaeb = true;}
      if(DCTnbNERmy == yXQOjfbsAV){HquiTiWfiu = true;}
      while(sEXpzJXBeQ == HzxnAyjHAm){XMbrIjaoZq = true;}
      while(pSWhgXXSMJ == pSWhgXXSMJ){AnllbaTdgM = true;}
      while(yXQOjfbsAV == yXQOjfbsAV){DHxTYFazRn = true;}
      if(kcKnjAyDCf == true){kcKnjAyDCf = false;}
      if(WFBWEehnpb == true){WFBWEehnpb = false;}
      if(qgXszVnIFT == true){qgXszVnIFT = false;}
      if(geAJfMHixf == true){geAJfMHixf = false;}
      if(YTPgmrWsJE == true){YTPgmrWsJE = false;}
      if(ynDYdDFQnN == true){ynDYdDFQnN = false;}
      if(MpxiyqFqqr == true){MpxiyqFqqr = false;}
      if(XypJCXRpGH == true){XypJCXRpGH = false;}
      if(ztyBUsaaeb == true){ztyBUsaaeb = false;}
      if(HquiTiWfiu == true){HquiTiWfiu = false;}
      if(meBRgzxtWG == true){meBRgzxtWG = false;}
      if(lOKfORrwNF == true){lOKfORrwNF = false;}
      if(QeMPjfCGoS == true){QeMPjfCGoS = false;}
      if(AkHLUUsfTV == true){AkHLUUsfTV = false;}
      if(wfDXosfOUC == true){wfDXosfOUC = false;}
      if(qZRddIRlhA == true){qZRddIRlhA = false;}
      if(xpFDFAGzLs == true){xpFDFAGzLs = false;}
      if(XMbrIjaoZq == true){XMbrIjaoZq = false;}
      if(AnllbaTdgM == true){AnllbaTdgM = false;}
      if(DHxTYFazRn == true){DHxTYFazRn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CSATGTSLXD
{ 
  void iJrKLlLymy()
  { 
      bool DEyLZyQdic = false;
      bool fysinsmnNI = false;
      bool sEopuCQJNa = false;
      bool rIKrFBNnrJ = false;
      bool hSRCNDmTkP = false;
      bool ltQQhyOHQW = false;
      bool hGPHjXmAcl = false;
      bool eywEZalmcq = false;
      bool PxYynyqtKG = false;
      bool mFXVbbDJSo = false;
      bool PlpyjnyMpG = false;
      bool LadYGkhQSl = false;
      bool frpVzZZacy = false;
      bool XcTnbdGZOA = false;
      bool zdEDtLayOp = false;
      bool tlpgIXwTyK = false;
      bool NXjqiiGpxc = false;
      bool dHBSlBnlan = false;
      bool ybLlDklmeD = false;
      bool glaEmbtMTL = false;
      string lTLjIHsOob;
      string skwVesdEOE;
      string pPzEPqlaXq;
      string EJzqbQkBGE;
      string yqhTCtFsWg;
      string ctoCDVTGTR;
      string URqxWikFsN;
      string IcyJGyhfCV;
      string ksDpNJTxmG;
      string wdgojfAjwS;
      string IAAJXAwfwF;
      string nnEygbNBjN;
      string PnRmQeuIZZ;
      string yxiiNjstRN;
      string MnAgSHYiII;
      string RzAiDTiMrs;
      string FmFVHpEUjw;
      string hSiWAamjTI;
      string FLARIywAes;
      string BfCYIYheZb;
      if(lTLjIHsOob == IAAJXAwfwF){DEyLZyQdic = true;}
      else if(IAAJXAwfwF == lTLjIHsOob){PlpyjnyMpG = true;}
      if(skwVesdEOE == nnEygbNBjN){fysinsmnNI = true;}
      else if(nnEygbNBjN == skwVesdEOE){LadYGkhQSl = true;}
      if(pPzEPqlaXq == PnRmQeuIZZ){sEopuCQJNa = true;}
      else if(PnRmQeuIZZ == pPzEPqlaXq){frpVzZZacy = true;}
      if(EJzqbQkBGE == yxiiNjstRN){rIKrFBNnrJ = true;}
      else if(yxiiNjstRN == EJzqbQkBGE){XcTnbdGZOA = true;}
      if(yqhTCtFsWg == MnAgSHYiII){hSRCNDmTkP = true;}
      else if(MnAgSHYiII == yqhTCtFsWg){zdEDtLayOp = true;}
      if(ctoCDVTGTR == RzAiDTiMrs){ltQQhyOHQW = true;}
      else if(RzAiDTiMrs == ctoCDVTGTR){tlpgIXwTyK = true;}
      if(URqxWikFsN == FmFVHpEUjw){hGPHjXmAcl = true;}
      else if(FmFVHpEUjw == URqxWikFsN){NXjqiiGpxc = true;}
      if(IcyJGyhfCV == hSiWAamjTI){eywEZalmcq = true;}
      if(ksDpNJTxmG == FLARIywAes){PxYynyqtKG = true;}
      if(wdgojfAjwS == BfCYIYheZb){mFXVbbDJSo = true;}
      while(hSiWAamjTI == IcyJGyhfCV){dHBSlBnlan = true;}
      while(FLARIywAes == FLARIywAes){ybLlDklmeD = true;}
      while(BfCYIYheZb == BfCYIYheZb){glaEmbtMTL = true;}
      if(DEyLZyQdic == true){DEyLZyQdic = false;}
      if(fysinsmnNI == true){fysinsmnNI = false;}
      if(sEopuCQJNa == true){sEopuCQJNa = false;}
      if(rIKrFBNnrJ == true){rIKrFBNnrJ = false;}
      if(hSRCNDmTkP == true){hSRCNDmTkP = false;}
      if(ltQQhyOHQW == true){ltQQhyOHQW = false;}
      if(hGPHjXmAcl == true){hGPHjXmAcl = false;}
      if(eywEZalmcq == true){eywEZalmcq = false;}
      if(PxYynyqtKG == true){PxYynyqtKG = false;}
      if(mFXVbbDJSo == true){mFXVbbDJSo = false;}
      if(PlpyjnyMpG == true){PlpyjnyMpG = false;}
      if(LadYGkhQSl == true){LadYGkhQSl = false;}
      if(frpVzZZacy == true){frpVzZZacy = false;}
      if(XcTnbdGZOA == true){XcTnbdGZOA = false;}
      if(zdEDtLayOp == true){zdEDtLayOp = false;}
      if(tlpgIXwTyK == true){tlpgIXwTyK = false;}
      if(NXjqiiGpxc == true){NXjqiiGpxc = false;}
      if(dHBSlBnlan == true){dHBSlBnlan = false;}
      if(ybLlDklmeD == true){ybLlDklmeD = false;}
      if(glaEmbtMTL == true){glaEmbtMTL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HWTWSVINVT
{ 
  void HxBKgATBlN()
  { 
      bool yoIoewblNj = false;
      bool OAiozrXGoJ = false;
      bool uiisAdYuLZ = false;
      bool IpnkLnDsrs = false;
      bool dJEifZVkxj = false;
      bool qZKUROFOoA = false;
      bool WfZnbYLydK = false;
      bool oeNufkdzNZ = false;
      bool InxahhfTSw = false;
      bool hnErVxjQHG = false;
      bool NWGmuMMOng = false;
      bool kGAOrihzFs = false;
      bool rrfhbAaVZh = false;
      bool BMrGMkgKfV = false;
      bool VQelKbmozl = false;
      bool OjLNOUqYKt = false;
      bool lpoFeXNtCH = false;
      bool BXSiWbNsWz = false;
      bool MkVmSQBdrq = false;
      bool sIzkjfbYHm = false;
      string UzCdqodZXB;
      string xfkcQWxILi;
      string qkofOAnWiF;
      string ORRmDiLBZm;
      string bdQCIncMoK;
      string JmoXDiKVPq;
      string AGqSmeOxYg;
      string LuhYHMUlXZ;
      string XbgYuactjT;
      string XolimVmxPc;
      string ZemHyNFQPp;
      string OXxoSXYSWL;
      string CTMEJVIyll;
      string ZWWtArnYZh;
      string VLdtFzrxPO;
      string wTaDaFSiyc;
      string EGddPqBCna;
      string jzrooppSzJ;
      string dLhXoFwSTu;
      string ZFaxcPgzdN;
      if(UzCdqodZXB == ZemHyNFQPp){yoIoewblNj = true;}
      else if(ZemHyNFQPp == UzCdqodZXB){NWGmuMMOng = true;}
      if(xfkcQWxILi == OXxoSXYSWL){OAiozrXGoJ = true;}
      else if(OXxoSXYSWL == xfkcQWxILi){kGAOrihzFs = true;}
      if(qkofOAnWiF == CTMEJVIyll){uiisAdYuLZ = true;}
      else if(CTMEJVIyll == qkofOAnWiF){rrfhbAaVZh = true;}
      if(ORRmDiLBZm == ZWWtArnYZh){IpnkLnDsrs = true;}
      else if(ZWWtArnYZh == ORRmDiLBZm){BMrGMkgKfV = true;}
      if(bdQCIncMoK == VLdtFzrxPO){dJEifZVkxj = true;}
      else if(VLdtFzrxPO == bdQCIncMoK){VQelKbmozl = true;}
      if(JmoXDiKVPq == wTaDaFSiyc){qZKUROFOoA = true;}
      else if(wTaDaFSiyc == JmoXDiKVPq){OjLNOUqYKt = true;}
      if(AGqSmeOxYg == EGddPqBCna){WfZnbYLydK = true;}
      else if(EGddPqBCna == AGqSmeOxYg){lpoFeXNtCH = true;}
      if(LuhYHMUlXZ == jzrooppSzJ){oeNufkdzNZ = true;}
      if(XbgYuactjT == dLhXoFwSTu){InxahhfTSw = true;}
      if(XolimVmxPc == ZFaxcPgzdN){hnErVxjQHG = true;}
      while(jzrooppSzJ == LuhYHMUlXZ){BXSiWbNsWz = true;}
      while(dLhXoFwSTu == dLhXoFwSTu){MkVmSQBdrq = true;}
      while(ZFaxcPgzdN == ZFaxcPgzdN){sIzkjfbYHm = true;}
      if(yoIoewblNj == true){yoIoewblNj = false;}
      if(OAiozrXGoJ == true){OAiozrXGoJ = false;}
      if(uiisAdYuLZ == true){uiisAdYuLZ = false;}
      if(IpnkLnDsrs == true){IpnkLnDsrs = false;}
      if(dJEifZVkxj == true){dJEifZVkxj = false;}
      if(qZKUROFOoA == true){qZKUROFOoA = false;}
      if(WfZnbYLydK == true){WfZnbYLydK = false;}
      if(oeNufkdzNZ == true){oeNufkdzNZ = false;}
      if(InxahhfTSw == true){InxahhfTSw = false;}
      if(hnErVxjQHG == true){hnErVxjQHG = false;}
      if(NWGmuMMOng == true){NWGmuMMOng = false;}
      if(kGAOrihzFs == true){kGAOrihzFs = false;}
      if(rrfhbAaVZh == true){rrfhbAaVZh = false;}
      if(BMrGMkgKfV == true){BMrGMkgKfV = false;}
      if(VQelKbmozl == true){VQelKbmozl = false;}
      if(OjLNOUqYKt == true){OjLNOUqYKt = false;}
      if(lpoFeXNtCH == true){lpoFeXNtCH = false;}
      if(BXSiWbNsWz == true){BXSiWbNsWz = false;}
      if(MkVmSQBdrq == true){MkVmSQBdrq = false;}
      if(sIzkjfbYHm == true){sIzkjfbYHm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PXYZRVSNAX
{ 
  void TTNBMBhoaj()
  { 
      bool zJJDWnRpFB = false;
      bool RQpeIhWOPX = false;
      bool nsDoSInlAl = false;
      bool xRVcBzXOLK = false;
      bool cnndwPcGdL = false;
      bool TdoqnFGUjN = false;
      bool zeoTDAuNcI = false;
      bool KHCFuzFZsC = false;
      bool fhInSTcdow = false;
      bool sCdyLxyUaw = false;
      bool UPcUBLaiwn = false;
      bool zfbhhQWAAi = false;
      bool XQXfPHcEtx = false;
      bool AkzwhPEnmH = false;
      bool ssgAwMawPt = false;
      bool ZxTqYDqwEs = false;
      bool hVoymOgezR = false;
      bool LiNsodjWiC = false;
      bool ggnzXCQHXd = false;
      bool YHisZWDiNh = false;
      string CGZlUccnPR;
      string fVwlmAUhNB;
      string QQSYxgdzpq;
      string NbkpMszHZp;
      string iPNwcPbUNT;
      string WUErEknBnm;
      string zcyXDDjFZs;
      string ANIXRBDVuh;
      string FIkWTsWsla;
      string FySlpFQorY;
      string eVtTSJMfZD;
      string gRFGhqqaEJ;
      string gpTznBtVhL;
      string jOcWCiORDJ;
      string gpSitmrMDz;
      string NojiqoCufR;
      string PpyNSRniDz;
      string bZXtcpWkEA;
      string IgSiytdteN;
      string gSkltprFPb;
      if(CGZlUccnPR == eVtTSJMfZD){zJJDWnRpFB = true;}
      else if(eVtTSJMfZD == CGZlUccnPR){UPcUBLaiwn = true;}
      if(fVwlmAUhNB == gRFGhqqaEJ){RQpeIhWOPX = true;}
      else if(gRFGhqqaEJ == fVwlmAUhNB){zfbhhQWAAi = true;}
      if(QQSYxgdzpq == gpTznBtVhL){nsDoSInlAl = true;}
      else if(gpTznBtVhL == QQSYxgdzpq){XQXfPHcEtx = true;}
      if(NbkpMszHZp == jOcWCiORDJ){xRVcBzXOLK = true;}
      else if(jOcWCiORDJ == NbkpMszHZp){AkzwhPEnmH = true;}
      if(iPNwcPbUNT == gpSitmrMDz){cnndwPcGdL = true;}
      else if(gpSitmrMDz == iPNwcPbUNT){ssgAwMawPt = true;}
      if(WUErEknBnm == NojiqoCufR){TdoqnFGUjN = true;}
      else if(NojiqoCufR == WUErEknBnm){ZxTqYDqwEs = true;}
      if(zcyXDDjFZs == PpyNSRniDz){zeoTDAuNcI = true;}
      else if(PpyNSRniDz == zcyXDDjFZs){hVoymOgezR = true;}
      if(ANIXRBDVuh == bZXtcpWkEA){KHCFuzFZsC = true;}
      if(FIkWTsWsla == IgSiytdteN){fhInSTcdow = true;}
      if(FySlpFQorY == gSkltprFPb){sCdyLxyUaw = true;}
      while(bZXtcpWkEA == ANIXRBDVuh){LiNsodjWiC = true;}
      while(IgSiytdteN == IgSiytdteN){ggnzXCQHXd = true;}
      while(gSkltprFPb == gSkltprFPb){YHisZWDiNh = true;}
      if(zJJDWnRpFB == true){zJJDWnRpFB = false;}
      if(RQpeIhWOPX == true){RQpeIhWOPX = false;}
      if(nsDoSInlAl == true){nsDoSInlAl = false;}
      if(xRVcBzXOLK == true){xRVcBzXOLK = false;}
      if(cnndwPcGdL == true){cnndwPcGdL = false;}
      if(TdoqnFGUjN == true){TdoqnFGUjN = false;}
      if(zeoTDAuNcI == true){zeoTDAuNcI = false;}
      if(KHCFuzFZsC == true){KHCFuzFZsC = false;}
      if(fhInSTcdow == true){fhInSTcdow = false;}
      if(sCdyLxyUaw == true){sCdyLxyUaw = false;}
      if(UPcUBLaiwn == true){UPcUBLaiwn = false;}
      if(zfbhhQWAAi == true){zfbhhQWAAi = false;}
      if(XQXfPHcEtx == true){XQXfPHcEtx = false;}
      if(AkzwhPEnmH == true){AkzwhPEnmH = false;}
      if(ssgAwMawPt == true){ssgAwMawPt = false;}
      if(ZxTqYDqwEs == true){ZxTqYDqwEs = false;}
      if(hVoymOgezR == true){hVoymOgezR = false;}
      if(LiNsodjWiC == true){LiNsodjWiC = false;}
      if(ggnzXCQHXd == true){ggnzXCQHXd = false;}
      if(YHisZWDiNh == true){YHisZWDiNh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBMUROWHCI
{ 
  void cJuKHDgCdY()
  { 
      bool ViGRGOzScZ = false;
      bool pcoQuUymqg = false;
      bool oyEAxmwjdu = false;
      bool cyGoxkDury = false;
      bool pcegSTPeir = false;
      bool bqqjwWeGTS = false;
      bool SOngwqVASK = false;
      bool RDtrpMTWgd = false;
      bool XQBkSlHWrZ = false;
      bool FwaYfanxja = false;
      bool xPLXaYwysj = false;
      bool DHYpuBNCOK = false;
      bool jzHsFUbVMO = false;
      bool XWmFfHFcKt = false;
      bool oJdIWxWjcd = false;
      bool NkiYqyHRSF = false;
      bool wZkdLgUTKm = false;
      bool wjrTUaVyWH = false;
      bool xrsiAmnNNg = false;
      bool zmKEyPXzwp = false;
      string dKIqiQGzSD;
      string MEjYsurZWI;
      string iinQilQYPi;
      string cqdNKJlMzM;
      string KHfdYPfeOo;
      string kJsUBuVqIx;
      string AgjjZUaVOi;
      string JeZJxaCJrT;
      string GlKZyTyJMP;
      string ntECMcXwED;
      string nJPeeFiiXZ;
      string rLznpNWJkG;
      string WRJzuPZXxT;
      string DGFnewVets;
      string kPklXbuPLy;
      string GNKygVAQjP;
      string eKkDVkGLJt;
      string rqOrUHfWbS;
      string UJMyMouHGI;
      string wEueNZdhQl;
      if(dKIqiQGzSD == nJPeeFiiXZ){ViGRGOzScZ = true;}
      else if(nJPeeFiiXZ == dKIqiQGzSD){xPLXaYwysj = true;}
      if(MEjYsurZWI == rLznpNWJkG){pcoQuUymqg = true;}
      else if(rLznpNWJkG == MEjYsurZWI){DHYpuBNCOK = true;}
      if(iinQilQYPi == WRJzuPZXxT){oyEAxmwjdu = true;}
      else if(WRJzuPZXxT == iinQilQYPi){jzHsFUbVMO = true;}
      if(cqdNKJlMzM == DGFnewVets){cyGoxkDury = true;}
      else if(DGFnewVets == cqdNKJlMzM){XWmFfHFcKt = true;}
      if(KHfdYPfeOo == kPklXbuPLy){pcegSTPeir = true;}
      else if(kPklXbuPLy == KHfdYPfeOo){oJdIWxWjcd = true;}
      if(kJsUBuVqIx == GNKygVAQjP){bqqjwWeGTS = true;}
      else if(GNKygVAQjP == kJsUBuVqIx){NkiYqyHRSF = true;}
      if(AgjjZUaVOi == eKkDVkGLJt){SOngwqVASK = true;}
      else if(eKkDVkGLJt == AgjjZUaVOi){wZkdLgUTKm = true;}
      if(JeZJxaCJrT == rqOrUHfWbS){RDtrpMTWgd = true;}
      if(GlKZyTyJMP == UJMyMouHGI){XQBkSlHWrZ = true;}
      if(ntECMcXwED == wEueNZdhQl){FwaYfanxja = true;}
      while(rqOrUHfWbS == JeZJxaCJrT){wjrTUaVyWH = true;}
      while(UJMyMouHGI == UJMyMouHGI){xrsiAmnNNg = true;}
      while(wEueNZdhQl == wEueNZdhQl){zmKEyPXzwp = true;}
      if(ViGRGOzScZ == true){ViGRGOzScZ = false;}
      if(pcoQuUymqg == true){pcoQuUymqg = false;}
      if(oyEAxmwjdu == true){oyEAxmwjdu = false;}
      if(cyGoxkDury == true){cyGoxkDury = false;}
      if(pcegSTPeir == true){pcegSTPeir = false;}
      if(bqqjwWeGTS == true){bqqjwWeGTS = false;}
      if(SOngwqVASK == true){SOngwqVASK = false;}
      if(RDtrpMTWgd == true){RDtrpMTWgd = false;}
      if(XQBkSlHWrZ == true){XQBkSlHWrZ = false;}
      if(FwaYfanxja == true){FwaYfanxja = false;}
      if(xPLXaYwysj == true){xPLXaYwysj = false;}
      if(DHYpuBNCOK == true){DHYpuBNCOK = false;}
      if(jzHsFUbVMO == true){jzHsFUbVMO = false;}
      if(XWmFfHFcKt == true){XWmFfHFcKt = false;}
      if(oJdIWxWjcd == true){oJdIWxWjcd = false;}
      if(NkiYqyHRSF == true){NkiYqyHRSF = false;}
      if(wZkdLgUTKm == true){wZkdLgUTKm = false;}
      if(wjrTUaVyWH == true){wjrTUaVyWH = false;}
      if(xrsiAmnNNg == true){xrsiAmnNNg = false;}
      if(zmKEyPXzwp == true){zmKEyPXzwp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XFZBSZTZGI
{ 
  void mMjNKhfSXc()
  { 
      bool SntbdyDHCH = false;
      bool XupNEkduoR = false;
      bool uswrhHAfiV = false;
      bool PfuEVIxMUa = false;
      bool cWyeMUPxZN = false;
      bool JqTnIYqCsV = false;
      bool xXYfqrAkqu = false;
      bool nQaNnYuQeM = false;
      bool qDGVMYMGww = false;
      bool RtSydFxRnU = false;
      bool TeGdZrQFAi = false;
      bool dZWgdtQDTR = false;
      bool esotdsybjh = false;
      bool accKrMwbwT = false;
      bool IHGMSqXlTi = false;
      bool ntyVoaoLAf = false;
      bool tnURIBxLnR = false;
      bool xnGzJXmcbl = false;
      bool VMHBsfeGVR = false;
      bool XkbPZTlnDR = false;
      string yWpkuwgczU;
      string pYtsrnOKSq;
      string nnWXjUmroY;
      string RunphUSALT;
      string YpXflKFwap;
      string GehRqKzRAZ;
      string JonaCujDKX;
      string UOzzSxQqlY;
      string OpQzSlNWyX;
      string VBzkKiCxcp;
      string aCkDUqfhyt;
      string sIebLSYnHQ;
      string gMFmBTONoj;
      string uTNuyMEMea;
      string GeXEdMWXZq;
      string KNoMJNwyBA;
      string bRsOyZticy;
      string NLJgJCoAIn;
      string wqnyZgdBlk;
      string QGKdynlIFD;
      if(yWpkuwgczU == aCkDUqfhyt){SntbdyDHCH = true;}
      else if(aCkDUqfhyt == yWpkuwgczU){TeGdZrQFAi = true;}
      if(pYtsrnOKSq == sIebLSYnHQ){XupNEkduoR = true;}
      else if(sIebLSYnHQ == pYtsrnOKSq){dZWgdtQDTR = true;}
      if(nnWXjUmroY == gMFmBTONoj){uswrhHAfiV = true;}
      else if(gMFmBTONoj == nnWXjUmroY){esotdsybjh = true;}
      if(RunphUSALT == uTNuyMEMea){PfuEVIxMUa = true;}
      else if(uTNuyMEMea == RunphUSALT){accKrMwbwT = true;}
      if(YpXflKFwap == GeXEdMWXZq){cWyeMUPxZN = true;}
      else if(GeXEdMWXZq == YpXflKFwap){IHGMSqXlTi = true;}
      if(GehRqKzRAZ == KNoMJNwyBA){JqTnIYqCsV = true;}
      else if(KNoMJNwyBA == GehRqKzRAZ){ntyVoaoLAf = true;}
      if(JonaCujDKX == bRsOyZticy){xXYfqrAkqu = true;}
      else if(bRsOyZticy == JonaCujDKX){tnURIBxLnR = true;}
      if(UOzzSxQqlY == NLJgJCoAIn){nQaNnYuQeM = true;}
      if(OpQzSlNWyX == wqnyZgdBlk){qDGVMYMGww = true;}
      if(VBzkKiCxcp == QGKdynlIFD){RtSydFxRnU = true;}
      while(NLJgJCoAIn == UOzzSxQqlY){xnGzJXmcbl = true;}
      while(wqnyZgdBlk == wqnyZgdBlk){VMHBsfeGVR = true;}
      while(QGKdynlIFD == QGKdynlIFD){XkbPZTlnDR = true;}
      if(SntbdyDHCH == true){SntbdyDHCH = false;}
      if(XupNEkduoR == true){XupNEkduoR = false;}
      if(uswrhHAfiV == true){uswrhHAfiV = false;}
      if(PfuEVIxMUa == true){PfuEVIxMUa = false;}
      if(cWyeMUPxZN == true){cWyeMUPxZN = false;}
      if(JqTnIYqCsV == true){JqTnIYqCsV = false;}
      if(xXYfqrAkqu == true){xXYfqrAkqu = false;}
      if(nQaNnYuQeM == true){nQaNnYuQeM = false;}
      if(qDGVMYMGww == true){qDGVMYMGww = false;}
      if(RtSydFxRnU == true){RtSydFxRnU = false;}
      if(TeGdZrQFAi == true){TeGdZrQFAi = false;}
      if(dZWgdtQDTR == true){dZWgdtQDTR = false;}
      if(esotdsybjh == true){esotdsybjh = false;}
      if(accKrMwbwT == true){accKrMwbwT = false;}
      if(IHGMSqXlTi == true){IHGMSqXlTi = false;}
      if(ntyVoaoLAf == true){ntyVoaoLAf = false;}
      if(tnURIBxLnR == true){tnURIBxLnR = false;}
      if(xnGzJXmcbl == true){xnGzJXmcbl = false;}
      if(VMHBsfeGVR == true){VMHBsfeGVR = false;}
      if(XkbPZTlnDR == true){XkbPZTlnDR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZOPMWDYREW
{ 
  void jJcmUPEYMn()
  { 
      bool QVNWnVkUXw = false;
      bool RlsgQmxMkF = false;
      bool EzdgBMgOHS = false;
      bool atyxoCTSXA = false;
      bool pUTupqATGG = false;
      bool ayYNgQqgUa = false;
      bool oVNFVXmwqO = false;
      bool TeokOiehpJ = false;
      bool LNHAqcUkPX = false;
      bool KlxwLTHOZS = false;
      bool DEbrluJnyx = false;
      bool lJpLPaOMNr = false;
      bool DCfSDghrZu = false;
      bool bQHXFHkONu = false;
      bool SflSlBwkfj = false;
      bool FuAhOAXJoF = false;
      bool NQOCUUBSGI = false;
      bool pzyRYWQNfC = false;
      bool kxLoogPZIE = false;
      bool ibZIhCRixR = false;
      string PIzgZoOyUK;
      string KDggAfbWud;
      string KPiTnPzHgk;
      string SafjifWRVO;
      string enTJnPQmUO;
      string QdLfDzYesJ;
      string oHQjqjWxxU;
      string IKBfyWuZfX;
      string zLmRUnOAgj;
      string GqYLYXWjSE;
      string sSoAFFcehg;
      string EzyUKcTzOC;
      string UWQNNQkpHZ;
      string zKHbefVmMO;
      string LiRzeHsDBu;
      string DXUPiVCbln;
      string UmXHgsqWpd;
      string HglAqlEQhF;
      string XgoLWborrI;
      string ctAXsYKKSk;
      if(PIzgZoOyUK == sSoAFFcehg){QVNWnVkUXw = true;}
      else if(sSoAFFcehg == PIzgZoOyUK){DEbrluJnyx = true;}
      if(KDggAfbWud == EzyUKcTzOC){RlsgQmxMkF = true;}
      else if(EzyUKcTzOC == KDggAfbWud){lJpLPaOMNr = true;}
      if(KPiTnPzHgk == UWQNNQkpHZ){EzdgBMgOHS = true;}
      else if(UWQNNQkpHZ == KPiTnPzHgk){DCfSDghrZu = true;}
      if(SafjifWRVO == zKHbefVmMO){atyxoCTSXA = true;}
      else if(zKHbefVmMO == SafjifWRVO){bQHXFHkONu = true;}
      if(enTJnPQmUO == LiRzeHsDBu){pUTupqATGG = true;}
      else if(LiRzeHsDBu == enTJnPQmUO){SflSlBwkfj = true;}
      if(QdLfDzYesJ == DXUPiVCbln){ayYNgQqgUa = true;}
      else if(DXUPiVCbln == QdLfDzYesJ){FuAhOAXJoF = true;}
      if(oHQjqjWxxU == UmXHgsqWpd){oVNFVXmwqO = true;}
      else if(UmXHgsqWpd == oHQjqjWxxU){NQOCUUBSGI = true;}
      if(IKBfyWuZfX == HglAqlEQhF){TeokOiehpJ = true;}
      if(zLmRUnOAgj == XgoLWborrI){LNHAqcUkPX = true;}
      if(GqYLYXWjSE == ctAXsYKKSk){KlxwLTHOZS = true;}
      while(HglAqlEQhF == IKBfyWuZfX){pzyRYWQNfC = true;}
      while(XgoLWborrI == XgoLWborrI){kxLoogPZIE = true;}
      while(ctAXsYKKSk == ctAXsYKKSk){ibZIhCRixR = true;}
      if(QVNWnVkUXw == true){QVNWnVkUXw = false;}
      if(RlsgQmxMkF == true){RlsgQmxMkF = false;}
      if(EzdgBMgOHS == true){EzdgBMgOHS = false;}
      if(atyxoCTSXA == true){atyxoCTSXA = false;}
      if(pUTupqATGG == true){pUTupqATGG = false;}
      if(ayYNgQqgUa == true){ayYNgQqgUa = false;}
      if(oVNFVXmwqO == true){oVNFVXmwqO = false;}
      if(TeokOiehpJ == true){TeokOiehpJ = false;}
      if(LNHAqcUkPX == true){LNHAqcUkPX = false;}
      if(KlxwLTHOZS == true){KlxwLTHOZS = false;}
      if(DEbrluJnyx == true){DEbrluJnyx = false;}
      if(lJpLPaOMNr == true){lJpLPaOMNr = false;}
      if(DCfSDghrZu == true){DCfSDghrZu = false;}
      if(bQHXFHkONu == true){bQHXFHkONu = false;}
      if(SflSlBwkfj == true){SflSlBwkfj = false;}
      if(FuAhOAXJoF == true){FuAhOAXJoF = false;}
      if(NQOCUUBSGI == true){NQOCUUBSGI = false;}
      if(pzyRYWQNfC == true){pzyRYWQNfC = false;}
      if(kxLoogPZIE == true){kxLoogPZIE = false;}
      if(ibZIhCRixR == true){ibZIhCRixR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KLBGNKUQHD
{ 
  void iNzxdFYTeb()
  { 
      bool AmTOqlqwXN = false;
      bool ZJIaZtJGwS = false;
      bool fncQcuZnat = false;
      bool IyAqJhfTCm = false;
      bool fauTFMaeCd = false;
      bool AqfXyMJDlw = false;
      bool LDVdFaIQRq = false;
      bool NpDIlErJKP = false;
      bool TtlwtQScsw = false;
      bool YcgGbcFROd = false;
      bool EJNKPKnWks = false;
      bool UArVbQRYjn = false;
      bool IfXUSkIwgJ = false;
      bool zaufLJgafi = false;
      bool cuqzbYjLeK = false;
      bool LghZVXlrqe = false;
      bool CqpbttEMJR = false;
      bool jprAKNoXst = false;
      bool AwRWxRrUKn = false;
      bool XnjBglFOFh = false;
      string lFJYXMMNxK;
      string bFiHjcEiZG;
      string DkRUfEcmiC;
      string LHQECCypDx;
      string TaGjsSGjnt;
      string ZUsBzAmnsT;
      string jZdtzToeEh;
      string eOfcmcehaM;
      string yrzocqOOEC;
      string OKxiMtxMkZ;
      string dafFPKnPOW;
      string VFMfVqaoQH;
      string FaZBTTQwPs;
      string fSxBiWMsYR;
      string CyzhgIyQNV;
      string SHucTCBdlw;
      string trAVqDHKxy;
      string dgQyEGbrUK;
      string VzhtZXWTgf;
      string ViGbXKycqd;
      if(lFJYXMMNxK == dafFPKnPOW){AmTOqlqwXN = true;}
      else if(dafFPKnPOW == lFJYXMMNxK){EJNKPKnWks = true;}
      if(bFiHjcEiZG == VFMfVqaoQH){ZJIaZtJGwS = true;}
      else if(VFMfVqaoQH == bFiHjcEiZG){UArVbQRYjn = true;}
      if(DkRUfEcmiC == FaZBTTQwPs){fncQcuZnat = true;}
      else if(FaZBTTQwPs == DkRUfEcmiC){IfXUSkIwgJ = true;}
      if(LHQECCypDx == fSxBiWMsYR){IyAqJhfTCm = true;}
      else if(fSxBiWMsYR == LHQECCypDx){zaufLJgafi = true;}
      if(TaGjsSGjnt == CyzhgIyQNV){fauTFMaeCd = true;}
      else if(CyzhgIyQNV == TaGjsSGjnt){cuqzbYjLeK = true;}
      if(ZUsBzAmnsT == SHucTCBdlw){AqfXyMJDlw = true;}
      else if(SHucTCBdlw == ZUsBzAmnsT){LghZVXlrqe = true;}
      if(jZdtzToeEh == trAVqDHKxy){LDVdFaIQRq = true;}
      else if(trAVqDHKxy == jZdtzToeEh){CqpbttEMJR = true;}
      if(eOfcmcehaM == dgQyEGbrUK){NpDIlErJKP = true;}
      if(yrzocqOOEC == VzhtZXWTgf){TtlwtQScsw = true;}
      if(OKxiMtxMkZ == ViGbXKycqd){YcgGbcFROd = true;}
      while(dgQyEGbrUK == eOfcmcehaM){jprAKNoXst = true;}
      while(VzhtZXWTgf == VzhtZXWTgf){AwRWxRrUKn = true;}
      while(ViGbXKycqd == ViGbXKycqd){XnjBglFOFh = true;}
      if(AmTOqlqwXN == true){AmTOqlqwXN = false;}
      if(ZJIaZtJGwS == true){ZJIaZtJGwS = false;}
      if(fncQcuZnat == true){fncQcuZnat = false;}
      if(IyAqJhfTCm == true){IyAqJhfTCm = false;}
      if(fauTFMaeCd == true){fauTFMaeCd = false;}
      if(AqfXyMJDlw == true){AqfXyMJDlw = false;}
      if(LDVdFaIQRq == true){LDVdFaIQRq = false;}
      if(NpDIlErJKP == true){NpDIlErJKP = false;}
      if(TtlwtQScsw == true){TtlwtQScsw = false;}
      if(YcgGbcFROd == true){YcgGbcFROd = false;}
      if(EJNKPKnWks == true){EJNKPKnWks = false;}
      if(UArVbQRYjn == true){UArVbQRYjn = false;}
      if(IfXUSkIwgJ == true){IfXUSkIwgJ = false;}
      if(zaufLJgafi == true){zaufLJgafi = false;}
      if(cuqzbYjLeK == true){cuqzbYjLeK = false;}
      if(LghZVXlrqe == true){LghZVXlrqe = false;}
      if(CqpbttEMJR == true){CqpbttEMJR = false;}
      if(jprAKNoXst == true){jprAKNoXst = false;}
      if(AwRWxRrUKn == true){AwRWxRrUKn = false;}
      if(XnjBglFOFh == true){XnjBglFOFh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GQIGARLJRS
{ 
  void dJWVoVjdwa()
  { 
      bool gsEymabeml = false;
      bool bmRIeJjJSe = false;
      bool eyIIpmFqbl = false;
      bool yuGCReGSgk = false;
      bool pxQGYtYuTZ = false;
      bool GIoHohkuIz = false;
      bool UjDAmgfOqz = false;
      bool CRcgnggCju = false;
      bool NKXCfpFyMi = false;
      bool tLKgPFtPSq = false;
      bool OJDTWnfITI = false;
      bool BhLMlKMBUx = false;
      bool bgCHFqHuRh = false;
      bool mRjrgDGDer = false;
      bool KwdEhLzxuF = false;
      bool sruVPgHwOf = false;
      bool fjqlVjySfh = false;
      bool DJVbleDyYs = false;
      bool qKAMotVNcA = false;
      bool wKnyLZFriy = false;
      string jeAYohCjeS;
      string yFzAdNaKLj;
      string gmyrefGfOT;
      string PezBznAyQB;
      string ehPphbHnel;
      string WhWihxgHsJ;
      string bWVLDSGxAo;
      string NctJFyWIKC;
      string XSBbxgHPTC;
      string HrEGZHMEmO;
      string VKmoYsnMci;
      string ZXxpkJVsNV;
      string LpdyhUYmjy;
      string lSVwgNeLDD;
      string rtmjbiuNVQ;
      string kSpQDffnHE;
      string UBcexHCBJX;
      string dKpKcQDsWy;
      string YKQTMScErB;
      string gqEyiqRHmT;
      if(jeAYohCjeS == VKmoYsnMci){gsEymabeml = true;}
      else if(VKmoYsnMci == jeAYohCjeS){OJDTWnfITI = true;}
      if(yFzAdNaKLj == ZXxpkJVsNV){bmRIeJjJSe = true;}
      else if(ZXxpkJVsNV == yFzAdNaKLj){BhLMlKMBUx = true;}
      if(gmyrefGfOT == LpdyhUYmjy){eyIIpmFqbl = true;}
      else if(LpdyhUYmjy == gmyrefGfOT){bgCHFqHuRh = true;}
      if(PezBznAyQB == lSVwgNeLDD){yuGCReGSgk = true;}
      else if(lSVwgNeLDD == PezBznAyQB){mRjrgDGDer = true;}
      if(ehPphbHnel == rtmjbiuNVQ){pxQGYtYuTZ = true;}
      else if(rtmjbiuNVQ == ehPphbHnel){KwdEhLzxuF = true;}
      if(WhWihxgHsJ == kSpQDffnHE){GIoHohkuIz = true;}
      else if(kSpQDffnHE == WhWihxgHsJ){sruVPgHwOf = true;}
      if(bWVLDSGxAo == UBcexHCBJX){UjDAmgfOqz = true;}
      else if(UBcexHCBJX == bWVLDSGxAo){fjqlVjySfh = true;}
      if(NctJFyWIKC == dKpKcQDsWy){CRcgnggCju = true;}
      if(XSBbxgHPTC == YKQTMScErB){NKXCfpFyMi = true;}
      if(HrEGZHMEmO == gqEyiqRHmT){tLKgPFtPSq = true;}
      while(dKpKcQDsWy == NctJFyWIKC){DJVbleDyYs = true;}
      while(YKQTMScErB == YKQTMScErB){qKAMotVNcA = true;}
      while(gqEyiqRHmT == gqEyiqRHmT){wKnyLZFriy = true;}
      if(gsEymabeml == true){gsEymabeml = false;}
      if(bmRIeJjJSe == true){bmRIeJjJSe = false;}
      if(eyIIpmFqbl == true){eyIIpmFqbl = false;}
      if(yuGCReGSgk == true){yuGCReGSgk = false;}
      if(pxQGYtYuTZ == true){pxQGYtYuTZ = false;}
      if(GIoHohkuIz == true){GIoHohkuIz = false;}
      if(UjDAmgfOqz == true){UjDAmgfOqz = false;}
      if(CRcgnggCju == true){CRcgnggCju = false;}
      if(NKXCfpFyMi == true){NKXCfpFyMi = false;}
      if(tLKgPFtPSq == true){tLKgPFtPSq = false;}
      if(OJDTWnfITI == true){OJDTWnfITI = false;}
      if(BhLMlKMBUx == true){BhLMlKMBUx = false;}
      if(bgCHFqHuRh == true){bgCHFqHuRh = false;}
      if(mRjrgDGDer == true){mRjrgDGDer = false;}
      if(KwdEhLzxuF == true){KwdEhLzxuF = false;}
      if(sruVPgHwOf == true){sruVPgHwOf = false;}
      if(fjqlVjySfh == true){fjqlVjySfh = false;}
      if(DJVbleDyYs == true){DJVbleDyYs = false;}
      if(qKAMotVNcA == true){qKAMotVNcA = false;}
      if(wKnyLZFriy == true){wKnyLZFriy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RWLXXHPBHD
{ 
  void ADyDhByBCt()
  { 
      bool hlslMQcRdO = false;
      bool HjimTfEAHX = false;
      bool RRcUXjpEac = false;
      bool UXAMAOiMef = false;
      bool rnXhdaheSb = false;
      bool yddafQJXOc = false;
      bool aYqAtjjWmF = false;
      bool xqVbfcttqx = false;
      bool CLkyeqtZfi = false;
      bool FKyCFTwWnt = false;
      bool pKqNdGICuD = false;
      bool VOgQZOmrVD = false;
      bool oJqDAmsSVL = false;
      bool fXGwGrTWTX = false;
      bool hrdbNpcgbp = false;
      bool fDBkEfSnMq = false;
      bool NofiWyHkKh = false;
      bool uPYxUxfOoJ = false;
      bool JLqefbVVqZ = false;
      bool YeKcKrLuFO = false;
      string EESpLqCfZo;
      string DIfaezcSIz;
      string UNTgJMsOoX;
      string XHmPsPlpyZ;
      string ILDNhmpIUx;
      string WriSqpjkfz;
      string ynqBRuUPhP;
      string NlTiqJKGyV;
      string VksqBeXTYC;
      string eAKzbTTBwl;
      string SaZFijYAbh;
      string fdmKdMuAAl;
      string XBqfjNbUHW;
      string oIKMDuKmIQ;
      string GXqqVBMAUO;
      string YTBJORjsVU;
      string IDsFrXSaGi;
      string BHqifzJzKh;
      string AbzrxUGBxl;
      string KQRmICelyx;
      if(EESpLqCfZo == SaZFijYAbh){hlslMQcRdO = true;}
      else if(SaZFijYAbh == EESpLqCfZo){pKqNdGICuD = true;}
      if(DIfaezcSIz == fdmKdMuAAl){HjimTfEAHX = true;}
      else if(fdmKdMuAAl == DIfaezcSIz){VOgQZOmrVD = true;}
      if(UNTgJMsOoX == XBqfjNbUHW){RRcUXjpEac = true;}
      else if(XBqfjNbUHW == UNTgJMsOoX){oJqDAmsSVL = true;}
      if(XHmPsPlpyZ == oIKMDuKmIQ){UXAMAOiMef = true;}
      else if(oIKMDuKmIQ == XHmPsPlpyZ){fXGwGrTWTX = true;}
      if(ILDNhmpIUx == GXqqVBMAUO){rnXhdaheSb = true;}
      else if(GXqqVBMAUO == ILDNhmpIUx){hrdbNpcgbp = true;}
      if(WriSqpjkfz == YTBJORjsVU){yddafQJXOc = true;}
      else if(YTBJORjsVU == WriSqpjkfz){fDBkEfSnMq = true;}
      if(ynqBRuUPhP == IDsFrXSaGi){aYqAtjjWmF = true;}
      else if(IDsFrXSaGi == ynqBRuUPhP){NofiWyHkKh = true;}
      if(NlTiqJKGyV == BHqifzJzKh){xqVbfcttqx = true;}
      if(VksqBeXTYC == AbzrxUGBxl){CLkyeqtZfi = true;}
      if(eAKzbTTBwl == KQRmICelyx){FKyCFTwWnt = true;}
      while(BHqifzJzKh == NlTiqJKGyV){uPYxUxfOoJ = true;}
      while(AbzrxUGBxl == AbzrxUGBxl){JLqefbVVqZ = true;}
      while(KQRmICelyx == KQRmICelyx){YeKcKrLuFO = true;}
      if(hlslMQcRdO == true){hlslMQcRdO = false;}
      if(HjimTfEAHX == true){HjimTfEAHX = false;}
      if(RRcUXjpEac == true){RRcUXjpEac = false;}
      if(UXAMAOiMef == true){UXAMAOiMef = false;}
      if(rnXhdaheSb == true){rnXhdaheSb = false;}
      if(yddafQJXOc == true){yddafQJXOc = false;}
      if(aYqAtjjWmF == true){aYqAtjjWmF = false;}
      if(xqVbfcttqx == true){xqVbfcttqx = false;}
      if(CLkyeqtZfi == true){CLkyeqtZfi = false;}
      if(FKyCFTwWnt == true){FKyCFTwWnt = false;}
      if(pKqNdGICuD == true){pKqNdGICuD = false;}
      if(VOgQZOmrVD == true){VOgQZOmrVD = false;}
      if(oJqDAmsSVL == true){oJqDAmsSVL = false;}
      if(fXGwGrTWTX == true){fXGwGrTWTX = false;}
      if(hrdbNpcgbp == true){hrdbNpcgbp = false;}
      if(fDBkEfSnMq == true){fDBkEfSnMq = false;}
      if(NofiWyHkKh == true){NofiWyHkKh = false;}
      if(uPYxUxfOoJ == true){uPYxUxfOoJ = false;}
      if(JLqefbVVqZ == true){JLqefbVVqZ = false;}
      if(YeKcKrLuFO == true){YeKcKrLuFO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YOPJLNDBDJ
{ 
  void sAYHNlDlAf()
  { 
      bool cQMssYWUkS = false;
      bool tZgMrBmHcf = false;
      bool ZSWZVllXoF = false;
      bool TgtPoAoqnf = false;
      bool YSJxWjTHda = false;
      bool HEBxFKslWG = false;
      bool lyeezMfRWq = false;
      bool LwTwHHIZDl = false;
      bool RdtOyOewKd = false;
      bool HCTgtamdxJ = false;
      bool ECjlOKjFpy = false;
      bool CSiknIDQgj = false;
      bool hiHsiJcmCf = false;
      bool TdbsgPsHAn = false;
      bool dYGManShrl = false;
      bool WWwMaUuqCE = false;
      bool gxCJdXqpDY = false;
      bool OuPsGIbtRu = false;
      bool qttQIxgORL = false;
      bool TCFuGfWxhC = false;
      string SmZEJkNxxb;
      string LcFrIpCNXz;
      string VXJVnjaUQP;
      string HWWhZOMfoK;
      string dUPYWlzghH;
      string cHQonudDPZ;
      string KrghTnGXSs;
      string dVYNVAHjzC;
      string jsmIlAFgse;
      string jIQOzknhEh;
      string ebOndHhDTn;
      string msENoRFXuS;
      string iZdmJUEJOk;
      string LZfQWIdzdd;
      string SCNFrqEDZg;
      string eQlkzFybeI;
      string CXohbNNnpf;
      string nGtQAfLXtS;
      string QBjgFumtQQ;
      string KBTVbuMede;
      if(SmZEJkNxxb == ebOndHhDTn){cQMssYWUkS = true;}
      else if(ebOndHhDTn == SmZEJkNxxb){ECjlOKjFpy = true;}
      if(LcFrIpCNXz == msENoRFXuS){tZgMrBmHcf = true;}
      else if(msENoRFXuS == LcFrIpCNXz){CSiknIDQgj = true;}
      if(VXJVnjaUQP == iZdmJUEJOk){ZSWZVllXoF = true;}
      else if(iZdmJUEJOk == VXJVnjaUQP){hiHsiJcmCf = true;}
      if(HWWhZOMfoK == LZfQWIdzdd){TgtPoAoqnf = true;}
      else if(LZfQWIdzdd == HWWhZOMfoK){TdbsgPsHAn = true;}
      if(dUPYWlzghH == SCNFrqEDZg){YSJxWjTHda = true;}
      else if(SCNFrqEDZg == dUPYWlzghH){dYGManShrl = true;}
      if(cHQonudDPZ == eQlkzFybeI){HEBxFKslWG = true;}
      else if(eQlkzFybeI == cHQonudDPZ){WWwMaUuqCE = true;}
      if(KrghTnGXSs == CXohbNNnpf){lyeezMfRWq = true;}
      else if(CXohbNNnpf == KrghTnGXSs){gxCJdXqpDY = true;}
      if(dVYNVAHjzC == nGtQAfLXtS){LwTwHHIZDl = true;}
      if(jsmIlAFgse == QBjgFumtQQ){RdtOyOewKd = true;}
      if(jIQOzknhEh == KBTVbuMede){HCTgtamdxJ = true;}
      while(nGtQAfLXtS == dVYNVAHjzC){OuPsGIbtRu = true;}
      while(QBjgFumtQQ == QBjgFumtQQ){qttQIxgORL = true;}
      while(KBTVbuMede == KBTVbuMede){TCFuGfWxhC = true;}
      if(cQMssYWUkS == true){cQMssYWUkS = false;}
      if(tZgMrBmHcf == true){tZgMrBmHcf = false;}
      if(ZSWZVllXoF == true){ZSWZVllXoF = false;}
      if(TgtPoAoqnf == true){TgtPoAoqnf = false;}
      if(YSJxWjTHda == true){YSJxWjTHda = false;}
      if(HEBxFKslWG == true){HEBxFKslWG = false;}
      if(lyeezMfRWq == true){lyeezMfRWq = false;}
      if(LwTwHHIZDl == true){LwTwHHIZDl = false;}
      if(RdtOyOewKd == true){RdtOyOewKd = false;}
      if(HCTgtamdxJ == true){HCTgtamdxJ = false;}
      if(ECjlOKjFpy == true){ECjlOKjFpy = false;}
      if(CSiknIDQgj == true){CSiknIDQgj = false;}
      if(hiHsiJcmCf == true){hiHsiJcmCf = false;}
      if(TdbsgPsHAn == true){TdbsgPsHAn = false;}
      if(dYGManShrl == true){dYGManShrl = false;}
      if(WWwMaUuqCE == true){WWwMaUuqCE = false;}
      if(gxCJdXqpDY == true){gxCJdXqpDY = false;}
      if(OuPsGIbtRu == true){OuPsGIbtRu = false;}
      if(qttQIxgORL == true){qttQIxgORL = false;}
      if(TCFuGfWxhC == true){TCFuGfWxhC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JPVXBKNLCC
{ 
  void LSDcLmiwRe()
  { 
      bool ANtqJjLCAf = false;
      bool DzMGUEXKWi = false;
      bool lzkAGLVrDV = false;
      bool TZfLQsElFw = false;
      bool paWbSTABep = false;
      bool pNTjSActky = false;
      bool NSydLdSBoa = false;
      bool zkEasLbIgl = false;
      bool KTMMfGGwrP = false;
      bool PKBHhWbsQn = false;
      bool AyMDpEIsqH = false;
      bool YUMymsFlyE = false;
      bool XWIZLojxrV = false;
      bool iirslMHJVa = false;
      bool yNFkquyCUn = false;
      bool RpuLQdplrB = false;
      bool ULAVXobTMZ = false;
      bool lwPWGKRWiP = false;
      bool pgbDDsngbH = false;
      bool WVQUGmMjNB = false;
      string TPpVrdypGi;
      string wDSgSpGiFs;
      string qwrWqbMwCm;
      string UjGRjaxKbM;
      string aMSzbYFJEi;
      string RFOQVWXTeP;
      string RBnTOLxBwr;
      string rwHrSddruR;
      string WDrSUOUowM;
      string CdeLuYYzjP;
      string aEMMpVyWxq;
      string seXNsOJUyA;
      string qHEjoNQwwt;
      string FdHfpSpecz;
      string PyrFTXGRRg;
      string ODBjXTzcWc;
      string ECZCkOWrWZ;
      string XdryjrPzPQ;
      string HzdOfBcXHW;
      string TMIzuNXpTE;
      if(TPpVrdypGi == aEMMpVyWxq){ANtqJjLCAf = true;}
      else if(aEMMpVyWxq == TPpVrdypGi){AyMDpEIsqH = true;}
      if(wDSgSpGiFs == seXNsOJUyA){DzMGUEXKWi = true;}
      else if(seXNsOJUyA == wDSgSpGiFs){YUMymsFlyE = true;}
      if(qwrWqbMwCm == qHEjoNQwwt){lzkAGLVrDV = true;}
      else if(qHEjoNQwwt == qwrWqbMwCm){XWIZLojxrV = true;}
      if(UjGRjaxKbM == FdHfpSpecz){TZfLQsElFw = true;}
      else if(FdHfpSpecz == UjGRjaxKbM){iirslMHJVa = true;}
      if(aMSzbYFJEi == PyrFTXGRRg){paWbSTABep = true;}
      else if(PyrFTXGRRg == aMSzbYFJEi){yNFkquyCUn = true;}
      if(RFOQVWXTeP == ODBjXTzcWc){pNTjSActky = true;}
      else if(ODBjXTzcWc == RFOQVWXTeP){RpuLQdplrB = true;}
      if(RBnTOLxBwr == ECZCkOWrWZ){NSydLdSBoa = true;}
      else if(ECZCkOWrWZ == RBnTOLxBwr){ULAVXobTMZ = true;}
      if(rwHrSddruR == XdryjrPzPQ){zkEasLbIgl = true;}
      if(WDrSUOUowM == HzdOfBcXHW){KTMMfGGwrP = true;}
      if(CdeLuYYzjP == TMIzuNXpTE){PKBHhWbsQn = true;}
      while(XdryjrPzPQ == rwHrSddruR){lwPWGKRWiP = true;}
      while(HzdOfBcXHW == HzdOfBcXHW){pgbDDsngbH = true;}
      while(TMIzuNXpTE == TMIzuNXpTE){WVQUGmMjNB = true;}
      if(ANtqJjLCAf == true){ANtqJjLCAf = false;}
      if(DzMGUEXKWi == true){DzMGUEXKWi = false;}
      if(lzkAGLVrDV == true){lzkAGLVrDV = false;}
      if(TZfLQsElFw == true){TZfLQsElFw = false;}
      if(paWbSTABep == true){paWbSTABep = false;}
      if(pNTjSActky == true){pNTjSActky = false;}
      if(NSydLdSBoa == true){NSydLdSBoa = false;}
      if(zkEasLbIgl == true){zkEasLbIgl = false;}
      if(KTMMfGGwrP == true){KTMMfGGwrP = false;}
      if(PKBHhWbsQn == true){PKBHhWbsQn = false;}
      if(AyMDpEIsqH == true){AyMDpEIsqH = false;}
      if(YUMymsFlyE == true){YUMymsFlyE = false;}
      if(XWIZLojxrV == true){XWIZLojxrV = false;}
      if(iirslMHJVa == true){iirslMHJVa = false;}
      if(yNFkquyCUn == true){yNFkquyCUn = false;}
      if(RpuLQdplrB == true){RpuLQdplrB = false;}
      if(ULAVXobTMZ == true){ULAVXobTMZ = false;}
      if(lwPWGKRWiP == true){lwPWGKRWiP = false;}
      if(pgbDDsngbH == true){pgbDDsngbH = false;}
      if(WVQUGmMjNB == true){WVQUGmMjNB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BMKJAXIRVA
{ 
  void MgAZLeHueM()
  { 
      bool aYAOwiNMiw = false;
      bool ibJflreKaU = false;
      bool siQaGCIfdg = false;
      bool fqzTnaWMUV = false;
      bool tZhpXQQcnE = false;
      bool oISLxrIZIt = false;
      bool ZhhBQrcoqL = false;
      bool USoFaSAaCp = false;
      bool kfqZrWXmVw = false;
      bool RwDauMrgYe = false;
      bool nakcjWSNkd = false;
      bool qhXSItpIJs = false;
      bool ToStsXOOJN = false;
      bool aTBWBJtOpU = false;
      bool EKCrFjYkRA = false;
      bool VjXfKzHpiL = false;
      bool IEDWDXfAQz = false;
      bool AbRnoJlaoJ = false;
      bool zcwIqquVLC = false;
      bool BDeeMAGeoh = false;
      string HuoMKYAXXa;
      string cflyLRDXuA;
      string pydczIHreC;
      string ZSOfmsaFSK;
      string cdwOCtGMDE;
      string TCDGQIQMNC;
      string QIrVAKQFLS;
      string qyFjXMBPZE;
      string BtnZhXOHOd;
      string bOqPtTkaNq;
      string cABkNVwSiE;
      string GBlIBVTRmc;
      string uJqgpbGppD;
      string aaBiaBsDLM;
      string awYKWabiOY;
      string zSmjwTITul;
      string PGcecfzDhz;
      string bQFaBzjgKO;
      string zXbREHmQlH;
      string rZIZwUTsgp;
      if(HuoMKYAXXa == cABkNVwSiE){aYAOwiNMiw = true;}
      else if(cABkNVwSiE == HuoMKYAXXa){nakcjWSNkd = true;}
      if(cflyLRDXuA == GBlIBVTRmc){ibJflreKaU = true;}
      else if(GBlIBVTRmc == cflyLRDXuA){qhXSItpIJs = true;}
      if(pydczIHreC == uJqgpbGppD){siQaGCIfdg = true;}
      else if(uJqgpbGppD == pydczIHreC){ToStsXOOJN = true;}
      if(ZSOfmsaFSK == aaBiaBsDLM){fqzTnaWMUV = true;}
      else if(aaBiaBsDLM == ZSOfmsaFSK){aTBWBJtOpU = true;}
      if(cdwOCtGMDE == awYKWabiOY){tZhpXQQcnE = true;}
      else if(awYKWabiOY == cdwOCtGMDE){EKCrFjYkRA = true;}
      if(TCDGQIQMNC == zSmjwTITul){oISLxrIZIt = true;}
      else if(zSmjwTITul == TCDGQIQMNC){VjXfKzHpiL = true;}
      if(QIrVAKQFLS == PGcecfzDhz){ZhhBQrcoqL = true;}
      else if(PGcecfzDhz == QIrVAKQFLS){IEDWDXfAQz = true;}
      if(qyFjXMBPZE == bQFaBzjgKO){USoFaSAaCp = true;}
      if(BtnZhXOHOd == zXbREHmQlH){kfqZrWXmVw = true;}
      if(bOqPtTkaNq == rZIZwUTsgp){RwDauMrgYe = true;}
      while(bQFaBzjgKO == qyFjXMBPZE){AbRnoJlaoJ = true;}
      while(zXbREHmQlH == zXbREHmQlH){zcwIqquVLC = true;}
      while(rZIZwUTsgp == rZIZwUTsgp){BDeeMAGeoh = true;}
      if(aYAOwiNMiw == true){aYAOwiNMiw = false;}
      if(ibJflreKaU == true){ibJflreKaU = false;}
      if(siQaGCIfdg == true){siQaGCIfdg = false;}
      if(fqzTnaWMUV == true){fqzTnaWMUV = false;}
      if(tZhpXQQcnE == true){tZhpXQQcnE = false;}
      if(oISLxrIZIt == true){oISLxrIZIt = false;}
      if(ZhhBQrcoqL == true){ZhhBQrcoqL = false;}
      if(USoFaSAaCp == true){USoFaSAaCp = false;}
      if(kfqZrWXmVw == true){kfqZrWXmVw = false;}
      if(RwDauMrgYe == true){RwDauMrgYe = false;}
      if(nakcjWSNkd == true){nakcjWSNkd = false;}
      if(qhXSItpIJs == true){qhXSItpIJs = false;}
      if(ToStsXOOJN == true){ToStsXOOJN = false;}
      if(aTBWBJtOpU == true){aTBWBJtOpU = false;}
      if(EKCrFjYkRA == true){EKCrFjYkRA = false;}
      if(VjXfKzHpiL == true){VjXfKzHpiL = false;}
      if(IEDWDXfAQz == true){IEDWDXfAQz = false;}
      if(AbRnoJlaoJ == true){AbRnoJlaoJ = false;}
      if(zcwIqquVLC == true){zcwIqquVLC = false;}
      if(BDeeMAGeoh == true){BDeeMAGeoh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GICDKFDPOX
{ 
  void kmVfyrXrBc()
  { 
      bool nTPVnhjYCu = false;
      bool xKrTqLWeMf = false;
      bool aiwCEYaXkl = false;
      bool sJplTQwVgO = false;
      bool sjxtWzCzyV = false;
      bool uJwDmEXMRP = false;
      bool HLmPCnUFAa = false;
      bool OByxmqkCfF = false;
      bool WaZOpiMmzO = false;
      bool sjERHgwhqi = false;
      bool dwzWGtLzQu = false;
      bool TUgMsglXZS = false;
      bool agGlgewfpF = false;
      bool uDKwaZaCIw = false;
      bool XNVDtXCqYZ = false;
      bool uXIXHwpNpa = false;
      bool xeILAQKklS = false;
      bool FiPcuNLDqJ = false;
      bool cFGPJWulnd = false;
      bool jNMgysFKCd = false;
      string hEqYJArWwF;
      string fPHTzrkdtC;
      string thLPczLAGt;
      string qnbNjGnqFD;
      string KrRIspycyV;
      string RQUalAsbuK;
      string orPBNqmtir;
      string DtXqrCPCVm;
      string AhBjcaTBbi;
      string NMuuOSbPtB;
      string CEtFSWrdii;
      string jpGIKHpeYm;
      string XlSAdqzccY;
      string ZAHTkunuRF;
      string hpSryWGmkH;
      string cxqHdQksbb;
      string XPBJIjilWO;
      string StNSEhSZBH;
      string jMrVwcIApU;
      string KtTohSoJiO;
      if(hEqYJArWwF == CEtFSWrdii){nTPVnhjYCu = true;}
      else if(CEtFSWrdii == hEqYJArWwF){dwzWGtLzQu = true;}
      if(fPHTzrkdtC == jpGIKHpeYm){xKrTqLWeMf = true;}
      else if(jpGIKHpeYm == fPHTzrkdtC){TUgMsglXZS = true;}
      if(thLPczLAGt == XlSAdqzccY){aiwCEYaXkl = true;}
      else if(XlSAdqzccY == thLPczLAGt){agGlgewfpF = true;}
      if(qnbNjGnqFD == ZAHTkunuRF){sJplTQwVgO = true;}
      else if(ZAHTkunuRF == qnbNjGnqFD){uDKwaZaCIw = true;}
      if(KrRIspycyV == hpSryWGmkH){sjxtWzCzyV = true;}
      else if(hpSryWGmkH == KrRIspycyV){XNVDtXCqYZ = true;}
      if(RQUalAsbuK == cxqHdQksbb){uJwDmEXMRP = true;}
      else if(cxqHdQksbb == RQUalAsbuK){uXIXHwpNpa = true;}
      if(orPBNqmtir == XPBJIjilWO){HLmPCnUFAa = true;}
      else if(XPBJIjilWO == orPBNqmtir){xeILAQKklS = true;}
      if(DtXqrCPCVm == StNSEhSZBH){OByxmqkCfF = true;}
      if(AhBjcaTBbi == jMrVwcIApU){WaZOpiMmzO = true;}
      if(NMuuOSbPtB == KtTohSoJiO){sjERHgwhqi = true;}
      while(StNSEhSZBH == DtXqrCPCVm){FiPcuNLDqJ = true;}
      while(jMrVwcIApU == jMrVwcIApU){cFGPJWulnd = true;}
      while(KtTohSoJiO == KtTohSoJiO){jNMgysFKCd = true;}
      if(nTPVnhjYCu == true){nTPVnhjYCu = false;}
      if(xKrTqLWeMf == true){xKrTqLWeMf = false;}
      if(aiwCEYaXkl == true){aiwCEYaXkl = false;}
      if(sJplTQwVgO == true){sJplTQwVgO = false;}
      if(sjxtWzCzyV == true){sjxtWzCzyV = false;}
      if(uJwDmEXMRP == true){uJwDmEXMRP = false;}
      if(HLmPCnUFAa == true){HLmPCnUFAa = false;}
      if(OByxmqkCfF == true){OByxmqkCfF = false;}
      if(WaZOpiMmzO == true){WaZOpiMmzO = false;}
      if(sjERHgwhqi == true){sjERHgwhqi = false;}
      if(dwzWGtLzQu == true){dwzWGtLzQu = false;}
      if(TUgMsglXZS == true){TUgMsglXZS = false;}
      if(agGlgewfpF == true){agGlgewfpF = false;}
      if(uDKwaZaCIw == true){uDKwaZaCIw = false;}
      if(XNVDtXCqYZ == true){XNVDtXCqYZ = false;}
      if(uXIXHwpNpa == true){uXIXHwpNpa = false;}
      if(xeILAQKklS == true){xeILAQKklS = false;}
      if(FiPcuNLDqJ == true){FiPcuNLDqJ = false;}
      if(cFGPJWulnd == true){cFGPJWulnd = false;}
      if(jNMgysFKCd == true){jNMgysFKCd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ILPUTFVHTS
{ 
  void eiCzZxgncy()
  { 
      bool mVTltyPZYp = false;
      bool eVMjJVyyBA = false;
      bool tknPRBhlun = false;
      bool jjdCzalwSn = false;
      bool gpQwxAcxGU = false;
      bool cTkZfBgETr = false;
      bool PdekGuqKkh = false;
      bool jCfMTDUqRR = false;
      bool XkeZKQyEVx = false;
      bool sgbZYCLepC = false;
      bool ISMXkZmXGb = false;
      bool golCUezEZp = false;
      bool wmnmnCaGnQ = false;
      bool roBPIEXGoj = false;
      bool caxsQEtYFs = false;
      bool DGFAFUdYih = false;
      bool zgiojqnWtP = false;
      bool GrPoMVpuWj = false;
      bool HBAuMljAJn = false;
      bool ZzXGkuqHIY = false;
      string LVQiMlKRTe;
      string YtVzeWeVVJ;
      string scaBjXePWD;
      string HEjGIMWfBP;
      string blhjtIUtoA;
      string rJQVThtPyo;
      string GtuQWTKPpS;
      string AzTGhGtpGb;
      string DjaWLynNla;
      string RGhLIgqRMZ;
      string xFEWAroJnN;
      string nEIVlWTYFY;
      string fwdPAtQIyA;
      string PccgdyeDVS;
      string IdZXlNxLZk;
      string NSMnsBaoWF;
      string bgLmxLabrn;
      string qPClPCVFcl;
      string wFhMlxQomc;
      string WpgPqbSlaa;
      if(LVQiMlKRTe == xFEWAroJnN){mVTltyPZYp = true;}
      else if(xFEWAroJnN == LVQiMlKRTe){ISMXkZmXGb = true;}
      if(YtVzeWeVVJ == nEIVlWTYFY){eVMjJVyyBA = true;}
      else if(nEIVlWTYFY == YtVzeWeVVJ){golCUezEZp = true;}
      if(scaBjXePWD == fwdPAtQIyA){tknPRBhlun = true;}
      else if(fwdPAtQIyA == scaBjXePWD){wmnmnCaGnQ = true;}
      if(HEjGIMWfBP == PccgdyeDVS){jjdCzalwSn = true;}
      else if(PccgdyeDVS == HEjGIMWfBP){roBPIEXGoj = true;}
      if(blhjtIUtoA == IdZXlNxLZk){gpQwxAcxGU = true;}
      else if(IdZXlNxLZk == blhjtIUtoA){caxsQEtYFs = true;}
      if(rJQVThtPyo == NSMnsBaoWF){cTkZfBgETr = true;}
      else if(NSMnsBaoWF == rJQVThtPyo){DGFAFUdYih = true;}
      if(GtuQWTKPpS == bgLmxLabrn){PdekGuqKkh = true;}
      else if(bgLmxLabrn == GtuQWTKPpS){zgiojqnWtP = true;}
      if(AzTGhGtpGb == qPClPCVFcl){jCfMTDUqRR = true;}
      if(DjaWLynNla == wFhMlxQomc){XkeZKQyEVx = true;}
      if(RGhLIgqRMZ == WpgPqbSlaa){sgbZYCLepC = true;}
      while(qPClPCVFcl == AzTGhGtpGb){GrPoMVpuWj = true;}
      while(wFhMlxQomc == wFhMlxQomc){HBAuMljAJn = true;}
      while(WpgPqbSlaa == WpgPqbSlaa){ZzXGkuqHIY = true;}
      if(mVTltyPZYp == true){mVTltyPZYp = false;}
      if(eVMjJVyyBA == true){eVMjJVyyBA = false;}
      if(tknPRBhlun == true){tknPRBhlun = false;}
      if(jjdCzalwSn == true){jjdCzalwSn = false;}
      if(gpQwxAcxGU == true){gpQwxAcxGU = false;}
      if(cTkZfBgETr == true){cTkZfBgETr = false;}
      if(PdekGuqKkh == true){PdekGuqKkh = false;}
      if(jCfMTDUqRR == true){jCfMTDUqRR = false;}
      if(XkeZKQyEVx == true){XkeZKQyEVx = false;}
      if(sgbZYCLepC == true){sgbZYCLepC = false;}
      if(ISMXkZmXGb == true){ISMXkZmXGb = false;}
      if(golCUezEZp == true){golCUezEZp = false;}
      if(wmnmnCaGnQ == true){wmnmnCaGnQ = false;}
      if(roBPIEXGoj == true){roBPIEXGoj = false;}
      if(caxsQEtYFs == true){caxsQEtYFs = false;}
      if(DGFAFUdYih == true){DGFAFUdYih = false;}
      if(zgiojqnWtP == true){zgiojqnWtP = false;}
      if(GrPoMVpuWj == true){GrPoMVpuWj = false;}
      if(HBAuMljAJn == true){HBAuMljAJn = false;}
      if(ZzXGkuqHIY == true){ZzXGkuqHIY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MKZYXTNBZY
{ 
  void PiEXblDgya()
  { 
      bool aJsNmVLaCU = false;
      bool mhjcPkWhDY = false;
      bool SecnSRZYSM = false;
      bool cuVknVseTR = false;
      bool LpNUEPnYHJ = false;
      bool FxakKugEuV = false;
      bool ulIorrLzos = false;
      bool rrOlNbRIjD = false;
      bool cARJHeUkZr = false;
      bool onixVYgYcM = false;
      bool DojNQMinXi = false;
      bool dXUrsuUzhM = false;
      bool XaYxDEIRQo = false;
      bool tsfWzmPDrt = false;
      bool wfNqORSqDZ = false;
      bool EhpPncQmJM = false;
      bool DQXinkrxsF = false;
      bool eQGmPqMgil = false;
      bool kRNpjMCPiV = false;
      bool VcsepeHeDc = false;
      string hRazZeOqgQ;
      string YSgzfFZdqY;
      string RUbKFiMRCD;
      string BzcNRRfEyM;
      string SNwqhuUKrd;
      string DTEhfNoPtp;
      string RxndPYoTgN;
      string YUfeGEXjcJ;
      string NCZYzguugD;
      string bPJHtVYSbI;
      string FBcdFhnZab;
      string pEmjcPXPdi;
      string dslclILXkk;
      string eFITEMYuTR;
      string sUTFNWcYed;
      string yInrdMOzrw;
      string WPopwjwSfQ;
      string pbwMpJYfOO;
      string flsGmWRQpr;
      string xYCWtcfdJd;
      if(hRazZeOqgQ == FBcdFhnZab){aJsNmVLaCU = true;}
      else if(FBcdFhnZab == hRazZeOqgQ){DojNQMinXi = true;}
      if(YSgzfFZdqY == pEmjcPXPdi){mhjcPkWhDY = true;}
      else if(pEmjcPXPdi == YSgzfFZdqY){dXUrsuUzhM = true;}
      if(RUbKFiMRCD == dslclILXkk){SecnSRZYSM = true;}
      else if(dslclILXkk == RUbKFiMRCD){XaYxDEIRQo = true;}
      if(BzcNRRfEyM == eFITEMYuTR){cuVknVseTR = true;}
      else if(eFITEMYuTR == BzcNRRfEyM){tsfWzmPDrt = true;}
      if(SNwqhuUKrd == sUTFNWcYed){LpNUEPnYHJ = true;}
      else if(sUTFNWcYed == SNwqhuUKrd){wfNqORSqDZ = true;}
      if(DTEhfNoPtp == yInrdMOzrw){FxakKugEuV = true;}
      else if(yInrdMOzrw == DTEhfNoPtp){EhpPncQmJM = true;}
      if(RxndPYoTgN == WPopwjwSfQ){ulIorrLzos = true;}
      else if(WPopwjwSfQ == RxndPYoTgN){DQXinkrxsF = true;}
      if(YUfeGEXjcJ == pbwMpJYfOO){rrOlNbRIjD = true;}
      if(NCZYzguugD == flsGmWRQpr){cARJHeUkZr = true;}
      if(bPJHtVYSbI == xYCWtcfdJd){onixVYgYcM = true;}
      while(pbwMpJYfOO == YUfeGEXjcJ){eQGmPqMgil = true;}
      while(flsGmWRQpr == flsGmWRQpr){kRNpjMCPiV = true;}
      while(xYCWtcfdJd == xYCWtcfdJd){VcsepeHeDc = true;}
      if(aJsNmVLaCU == true){aJsNmVLaCU = false;}
      if(mhjcPkWhDY == true){mhjcPkWhDY = false;}
      if(SecnSRZYSM == true){SecnSRZYSM = false;}
      if(cuVknVseTR == true){cuVknVseTR = false;}
      if(LpNUEPnYHJ == true){LpNUEPnYHJ = false;}
      if(FxakKugEuV == true){FxakKugEuV = false;}
      if(ulIorrLzos == true){ulIorrLzos = false;}
      if(rrOlNbRIjD == true){rrOlNbRIjD = false;}
      if(cARJHeUkZr == true){cARJHeUkZr = false;}
      if(onixVYgYcM == true){onixVYgYcM = false;}
      if(DojNQMinXi == true){DojNQMinXi = false;}
      if(dXUrsuUzhM == true){dXUrsuUzhM = false;}
      if(XaYxDEIRQo == true){XaYxDEIRQo = false;}
      if(tsfWzmPDrt == true){tsfWzmPDrt = false;}
      if(wfNqORSqDZ == true){wfNqORSqDZ = false;}
      if(EhpPncQmJM == true){EhpPncQmJM = false;}
      if(DQXinkrxsF == true){DQXinkrxsF = false;}
      if(eQGmPqMgil == true){eQGmPqMgil = false;}
      if(kRNpjMCPiV == true){kRNpjMCPiV = false;}
      if(VcsepeHeDc == true){VcsepeHeDc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LWUPLXICRJ
{ 
  void KzEoeytOuV()
  { 
      bool yYqUJHDdCF = false;
      bool pABTSgSEAP = false;
      bool MxmqYnDjYf = false;
      bool tnkisTawuX = false;
      bool LczPPOjFDs = false;
      bool yKwRdBlzwU = false;
      bool ETEVKBPSZz = false;
      bool GVIbEjxWbK = false;
      bool ExgegirSEr = false;
      bool haAZTrYcEN = false;
      bool yQeEmbBTNs = false;
      bool DOXkQHmZoa = false;
      bool JwNhRfVhIL = false;
      bool LUSNLmRbrF = false;
      bool hXFKnTDOJM = false;
      bool FyncEBCxmH = false;
      bool GSKChiuJZd = false;
      bool oKhjskqDsx = false;
      bool bHYwGMfoJJ = false;
      bool jTojzOMCcF = false;
      string jwuPpAbMRa;
      string geDFgqAlxM;
      string iszaKklaDM;
      string UemBFssYik;
      string yIHCwjCMnj;
      string gLJLgpwUFE;
      string NAIEGCrBAm;
      string yaDLNalxdZ;
      string iZmTfIVbUO;
      string xXTdXxzCwt;
      string rAMBkFIxxG;
      string DzqeVnNoYx;
      string gQgkoZGYnP;
      string ajAighNkhZ;
      string AXdNKxgoIj;
      string jKczNbTbLL;
      string ziIgfTyIxm;
      string ZbGzwIlSZr;
      string rRQEfPGBUF;
      string OlYWaQOxhq;
      if(jwuPpAbMRa == rAMBkFIxxG){yYqUJHDdCF = true;}
      else if(rAMBkFIxxG == jwuPpAbMRa){yQeEmbBTNs = true;}
      if(geDFgqAlxM == DzqeVnNoYx){pABTSgSEAP = true;}
      else if(DzqeVnNoYx == geDFgqAlxM){DOXkQHmZoa = true;}
      if(iszaKklaDM == gQgkoZGYnP){MxmqYnDjYf = true;}
      else if(gQgkoZGYnP == iszaKklaDM){JwNhRfVhIL = true;}
      if(UemBFssYik == ajAighNkhZ){tnkisTawuX = true;}
      else if(ajAighNkhZ == UemBFssYik){LUSNLmRbrF = true;}
      if(yIHCwjCMnj == AXdNKxgoIj){LczPPOjFDs = true;}
      else if(AXdNKxgoIj == yIHCwjCMnj){hXFKnTDOJM = true;}
      if(gLJLgpwUFE == jKczNbTbLL){yKwRdBlzwU = true;}
      else if(jKczNbTbLL == gLJLgpwUFE){FyncEBCxmH = true;}
      if(NAIEGCrBAm == ziIgfTyIxm){ETEVKBPSZz = true;}
      else if(ziIgfTyIxm == NAIEGCrBAm){GSKChiuJZd = true;}
      if(yaDLNalxdZ == ZbGzwIlSZr){GVIbEjxWbK = true;}
      if(iZmTfIVbUO == rRQEfPGBUF){ExgegirSEr = true;}
      if(xXTdXxzCwt == OlYWaQOxhq){haAZTrYcEN = true;}
      while(ZbGzwIlSZr == yaDLNalxdZ){oKhjskqDsx = true;}
      while(rRQEfPGBUF == rRQEfPGBUF){bHYwGMfoJJ = true;}
      while(OlYWaQOxhq == OlYWaQOxhq){jTojzOMCcF = true;}
      if(yYqUJHDdCF == true){yYqUJHDdCF = false;}
      if(pABTSgSEAP == true){pABTSgSEAP = false;}
      if(MxmqYnDjYf == true){MxmqYnDjYf = false;}
      if(tnkisTawuX == true){tnkisTawuX = false;}
      if(LczPPOjFDs == true){LczPPOjFDs = false;}
      if(yKwRdBlzwU == true){yKwRdBlzwU = false;}
      if(ETEVKBPSZz == true){ETEVKBPSZz = false;}
      if(GVIbEjxWbK == true){GVIbEjxWbK = false;}
      if(ExgegirSEr == true){ExgegirSEr = false;}
      if(haAZTrYcEN == true){haAZTrYcEN = false;}
      if(yQeEmbBTNs == true){yQeEmbBTNs = false;}
      if(DOXkQHmZoa == true){DOXkQHmZoa = false;}
      if(JwNhRfVhIL == true){JwNhRfVhIL = false;}
      if(LUSNLmRbrF == true){LUSNLmRbrF = false;}
      if(hXFKnTDOJM == true){hXFKnTDOJM = false;}
      if(FyncEBCxmH == true){FyncEBCxmH = false;}
      if(GSKChiuJZd == true){GSKChiuJZd = false;}
      if(oKhjskqDsx == true){oKhjskqDsx = false;}
      if(bHYwGMfoJJ == true){bHYwGMfoJJ = false;}
      if(jTojzOMCcF == true){jTojzOMCcF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JTQIYSBIXI
{ 
  void odcLgGSafw()
  { 
      bool FwCwWNZBLz = false;
      bool JMpnAyAysg = false;
      bool kVunzfuqKt = false;
      bool FBdVqqjAoP = false;
      bool AtKMVcCZlD = false;
      bool TPPCsjBNwq = false;
      bool RipRsIhTxJ = false;
      bool NzJcfqLiSW = false;
      bool dVEGaokbcG = false;
      bool oVExxRErSM = false;
      bool uibcoTGlVB = false;
      bool YStZNwdiqD = false;
      bool WFpqTruLfO = false;
      bool mSPFausaQH = false;
      bool izFbhWaejA = false;
      bool mUBPporkJx = false;
      bool XtGHOGDnyS = false;
      bool DCRjUXzOIx = false;
      bool QQbeaRQAPl = false;
      bool CHRTinryMb = false;
      string cccyNyunDg;
      string HRpfTKRTGO;
      string OOjuTLEBZY;
      string DUSGQhZTsu;
      string cYrhAJPSTQ;
      string rGcLbNrhdC;
      string ssOeclyiPk;
      string jyZKloWCtK;
      string wlhIfxrGdC;
      string oroqCiKMFO;
      string LfDhgsfSZm;
      string qpmSFGKFze;
      string tqFMwrIiHC;
      string eJxfzPiAbl;
      string RYgqLzEWlu;
      string YENZTTapkn;
      string jxKXHgsHTo;
      string XKdMNUKNAw;
      string nlwLdauWLe;
      string orOmBTOJid;
      if(cccyNyunDg == LfDhgsfSZm){FwCwWNZBLz = true;}
      else if(LfDhgsfSZm == cccyNyunDg){uibcoTGlVB = true;}
      if(HRpfTKRTGO == qpmSFGKFze){JMpnAyAysg = true;}
      else if(qpmSFGKFze == HRpfTKRTGO){YStZNwdiqD = true;}
      if(OOjuTLEBZY == tqFMwrIiHC){kVunzfuqKt = true;}
      else if(tqFMwrIiHC == OOjuTLEBZY){WFpqTruLfO = true;}
      if(DUSGQhZTsu == eJxfzPiAbl){FBdVqqjAoP = true;}
      else if(eJxfzPiAbl == DUSGQhZTsu){mSPFausaQH = true;}
      if(cYrhAJPSTQ == RYgqLzEWlu){AtKMVcCZlD = true;}
      else if(RYgqLzEWlu == cYrhAJPSTQ){izFbhWaejA = true;}
      if(rGcLbNrhdC == YENZTTapkn){TPPCsjBNwq = true;}
      else if(YENZTTapkn == rGcLbNrhdC){mUBPporkJx = true;}
      if(ssOeclyiPk == jxKXHgsHTo){RipRsIhTxJ = true;}
      else if(jxKXHgsHTo == ssOeclyiPk){XtGHOGDnyS = true;}
      if(jyZKloWCtK == XKdMNUKNAw){NzJcfqLiSW = true;}
      if(wlhIfxrGdC == nlwLdauWLe){dVEGaokbcG = true;}
      if(oroqCiKMFO == orOmBTOJid){oVExxRErSM = true;}
      while(XKdMNUKNAw == jyZKloWCtK){DCRjUXzOIx = true;}
      while(nlwLdauWLe == nlwLdauWLe){QQbeaRQAPl = true;}
      while(orOmBTOJid == orOmBTOJid){CHRTinryMb = true;}
      if(FwCwWNZBLz == true){FwCwWNZBLz = false;}
      if(JMpnAyAysg == true){JMpnAyAysg = false;}
      if(kVunzfuqKt == true){kVunzfuqKt = false;}
      if(FBdVqqjAoP == true){FBdVqqjAoP = false;}
      if(AtKMVcCZlD == true){AtKMVcCZlD = false;}
      if(TPPCsjBNwq == true){TPPCsjBNwq = false;}
      if(RipRsIhTxJ == true){RipRsIhTxJ = false;}
      if(NzJcfqLiSW == true){NzJcfqLiSW = false;}
      if(dVEGaokbcG == true){dVEGaokbcG = false;}
      if(oVExxRErSM == true){oVExxRErSM = false;}
      if(uibcoTGlVB == true){uibcoTGlVB = false;}
      if(YStZNwdiqD == true){YStZNwdiqD = false;}
      if(WFpqTruLfO == true){WFpqTruLfO = false;}
      if(mSPFausaQH == true){mSPFausaQH = false;}
      if(izFbhWaejA == true){izFbhWaejA = false;}
      if(mUBPporkJx == true){mUBPporkJx = false;}
      if(XtGHOGDnyS == true){XtGHOGDnyS = false;}
      if(DCRjUXzOIx == true){DCRjUXzOIx = false;}
      if(QQbeaRQAPl == true){QQbeaRQAPl = false;}
      if(CHRTinryMb == true){CHRTinryMb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HDTUJBCORF
{ 
  void eqTVylztkf()
  { 
      bool SuCDDQgxUV = false;
      bool IkNLKmbCJZ = false;
      bool lazaPoLcmz = false;
      bool MIEZsUeqNq = false;
      bool axBtFPKoIV = false;
      bool YCVBerubnN = false;
      bool FEJUIAfmSp = false;
      bool IkoRzoYFUz = false;
      bool eVTQZJlDuA = false;
      bool ZDCzlWmgkF = false;
      bool jWVSMnNECp = false;
      bool SpGoiijrtz = false;
      bool OcrRQFhofb = false;
      bool CrUPOHzBEk = false;
      bool uhAEhjwNQC = false;
      bool mtllqHeDCH = false;
      bool GYXZnaUpZa = false;
      bool iinJDgbmjf = false;
      bool ITYdoHGiYH = false;
      bool cuyweWJaQG = false;
      string FCaxQlNymH;
      string ghkzRfChKX;
      string ccXbFGXEFm;
      string TQzOsjbjNU;
      string XQUitOeAfG;
      string NHpBhbdzqK;
      string NJrAmQhWGg;
      string DSTozLHogq;
      string aWXyZMZyfQ;
      string FcrDHOYUwd;
      string fItzCumBBV;
      string ToRAipksaZ;
      string pjpoaaZPhk;
      string mmrCKScYwd;
      string YYwJxPKrUQ;
      string cesVmwRFXb;
      string UXSQhfxOoQ;
      string NMxwBRmfqL;
      string QguQHItWPO;
      string BXBTJBFebR;
      if(FCaxQlNymH == fItzCumBBV){SuCDDQgxUV = true;}
      else if(fItzCumBBV == FCaxQlNymH){jWVSMnNECp = true;}
      if(ghkzRfChKX == ToRAipksaZ){IkNLKmbCJZ = true;}
      else if(ToRAipksaZ == ghkzRfChKX){SpGoiijrtz = true;}
      if(ccXbFGXEFm == pjpoaaZPhk){lazaPoLcmz = true;}
      else if(pjpoaaZPhk == ccXbFGXEFm){OcrRQFhofb = true;}
      if(TQzOsjbjNU == mmrCKScYwd){MIEZsUeqNq = true;}
      else if(mmrCKScYwd == TQzOsjbjNU){CrUPOHzBEk = true;}
      if(XQUitOeAfG == YYwJxPKrUQ){axBtFPKoIV = true;}
      else if(YYwJxPKrUQ == XQUitOeAfG){uhAEhjwNQC = true;}
      if(NHpBhbdzqK == cesVmwRFXb){YCVBerubnN = true;}
      else if(cesVmwRFXb == NHpBhbdzqK){mtllqHeDCH = true;}
      if(NJrAmQhWGg == UXSQhfxOoQ){FEJUIAfmSp = true;}
      else if(UXSQhfxOoQ == NJrAmQhWGg){GYXZnaUpZa = true;}
      if(DSTozLHogq == NMxwBRmfqL){IkoRzoYFUz = true;}
      if(aWXyZMZyfQ == QguQHItWPO){eVTQZJlDuA = true;}
      if(FcrDHOYUwd == BXBTJBFebR){ZDCzlWmgkF = true;}
      while(NMxwBRmfqL == DSTozLHogq){iinJDgbmjf = true;}
      while(QguQHItWPO == QguQHItWPO){ITYdoHGiYH = true;}
      while(BXBTJBFebR == BXBTJBFebR){cuyweWJaQG = true;}
      if(SuCDDQgxUV == true){SuCDDQgxUV = false;}
      if(IkNLKmbCJZ == true){IkNLKmbCJZ = false;}
      if(lazaPoLcmz == true){lazaPoLcmz = false;}
      if(MIEZsUeqNq == true){MIEZsUeqNq = false;}
      if(axBtFPKoIV == true){axBtFPKoIV = false;}
      if(YCVBerubnN == true){YCVBerubnN = false;}
      if(FEJUIAfmSp == true){FEJUIAfmSp = false;}
      if(IkoRzoYFUz == true){IkoRzoYFUz = false;}
      if(eVTQZJlDuA == true){eVTQZJlDuA = false;}
      if(ZDCzlWmgkF == true){ZDCzlWmgkF = false;}
      if(jWVSMnNECp == true){jWVSMnNECp = false;}
      if(SpGoiijrtz == true){SpGoiijrtz = false;}
      if(OcrRQFhofb == true){OcrRQFhofb = false;}
      if(CrUPOHzBEk == true){CrUPOHzBEk = false;}
      if(uhAEhjwNQC == true){uhAEhjwNQC = false;}
      if(mtllqHeDCH == true){mtllqHeDCH = false;}
      if(GYXZnaUpZa == true){GYXZnaUpZa = false;}
      if(iinJDgbmjf == true){iinJDgbmjf = false;}
      if(ITYdoHGiYH == true){ITYdoHGiYH = false;}
      if(cuyweWJaQG == true){cuyweWJaQG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FWCEMEJZNY
{ 
  void fjjJqOPSlc()
  { 
      bool zCgJKHBtVx = false;
      bool rNLZZfrOPr = false;
      bool RSslbDuXqd = false;
      bool pQyrVnTmUW = false;
      bool wNwjUtGmbf = false;
      bool PNVCygIthG = false;
      bool McCrHbPTDk = false;
      bool MFtswDVIRg = false;
      bool xHwKNbtuso = false;
      bool eZFOKSKDcr = false;
      bool eljpTKTcGt = false;
      bool KAbAIEgqde = false;
      bool gTaOGmAehc = false;
      bool rReYBKXFqD = false;
      bool IRoydexEGF = false;
      bool lTZyLKLUjg = false;
      bool KotcBrUDyx = false;
      bool gbAaWPebja = false;
      bool ouYbqYrgNq = false;
      bool zCUJsSWLwl = false;
      string nJRXlHpNBN;
      string NzHYhIHoIn;
      string TFckbfrOOt;
      string ypqVEejkCF;
      string KVDHemamEJ;
      string kTKTPhgfwG;
      string ObzHOWHlUD;
      string YVmDdxCUGn;
      string FFJEIefXFV;
      string xDnuphWwsH;
      string fnSBkOgHpS;
      string fMZHBJRtyj;
      string qjgyFUhqMu;
      string aGayIQmISt;
      string xXgmpjdgtg;
      string QcyIQuHTuQ;
      string gotuqZkazk;
      string WIaDlSCtIU;
      string qBwfeyHShM;
      string ISNCMIcluP;
      if(nJRXlHpNBN == fnSBkOgHpS){zCgJKHBtVx = true;}
      else if(fnSBkOgHpS == nJRXlHpNBN){eljpTKTcGt = true;}
      if(NzHYhIHoIn == fMZHBJRtyj){rNLZZfrOPr = true;}
      else if(fMZHBJRtyj == NzHYhIHoIn){KAbAIEgqde = true;}
      if(TFckbfrOOt == qjgyFUhqMu){RSslbDuXqd = true;}
      else if(qjgyFUhqMu == TFckbfrOOt){gTaOGmAehc = true;}
      if(ypqVEejkCF == aGayIQmISt){pQyrVnTmUW = true;}
      else if(aGayIQmISt == ypqVEejkCF){rReYBKXFqD = true;}
      if(KVDHemamEJ == xXgmpjdgtg){wNwjUtGmbf = true;}
      else if(xXgmpjdgtg == KVDHemamEJ){IRoydexEGF = true;}
      if(kTKTPhgfwG == QcyIQuHTuQ){PNVCygIthG = true;}
      else if(QcyIQuHTuQ == kTKTPhgfwG){lTZyLKLUjg = true;}
      if(ObzHOWHlUD == gotuqZkazk){McCrHbPTDk = true;}
      else if(gotuqZkazk == ObzHOWHlUD){KotcBrUDyx = true;}
      if(YVmDdxCUGn == WIaDlSCtIU){MFtswDVIRg = true;}
      if(FFJEIefXFV == qBwfeyHShM){xHwKNbtuso = true;}
      if(xDnuphWwsH == ISNCMIcluP){eZFOKSKDcr = true;}
      while(WIaDlSCtIU == YVmDdxCUGn){gbAaWPebja = true;}
      while(qBwfeyHShM == qBwfeyHShM){ouYbqYrgNq = true;}
      while(ISNCMIcluP == ISNCMIcluP){zCUJsSWLwl = true;}
      if(zCgJKHBtVx == true){zCgJKHBtVx = false;}
      if(rNLZZfrOPr == true){rNLZZfrOPr = false;}
      if(RSslbDuXqd == true){RSslbDuXqd = false;}
      if(pQyrVnTmUW == true){pQyrVnTmUW = false;}
      if(wNwjUtGmbf == true){wNwjUtGmbf = false;}
      if(PNVCygIthG == true){PNVCygIthG = false;}
      if(McCrHbPTDk == true){McCrHbPTDk = false;}
      if(MFtswDVIRg == true){MFtswDVIRg = false;}
      if(xHwKNbtuso == true){xHwKNbtuso = false;}
      if(eZFOKSKDcr == true){eZFOKSKDcr = false;}
      if(eljpTKTcGt == true){eljpTKTcGt = false;}
      if(KAbAIEgqde == true){KAbAIEgqde = false;}
      if(gTaOGmAehc == true){gTaOGmAehc = false;}
      if(rReYBKXFqD == true){rReYBKXFqD = false;}
      if(IRoydexEGF == true){IRoydexEGF = false;}
      if(lTZyLKLUjg == true){lTZyLKLUjg = false;}
      if(KotcBrUDyx == true){KotcBrUDyx = false;}
      if(gbAaWPebja == true){gbAaWPebja = false;}
      if(ouYbqYrgNq == true){ouYbqYrgNq = false;}
      if(zCUJsSWLwl == true){zCUJsSWLwl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GLTMPAYXEZ
{ 
  void AnsWHeXBlU()
  { 
      bool PiFxTqRweF = false;
      bool ERWBlwERMR = false;
      bool CzfLOygWLy = false;
      bool VpSuazhPfO = false;
      bool jnBbGSEFmV = false;
      bool mcWawPCthV = false;
      bool KujfjOzbal = false;
      bool NnlyhOyEEw = false;
      bool saioLrTqyL = false;
      bool xngKDoDUqr = false;
      bool TceBHyqXsh = false;
      bool QyolbjLtTr = false;
      bool tIcPnZHatr = false;
      bool KcMMcQwhhN = false;
      bool BuxQtzzuiS = false;
      bool dIAzyLAOMh = false;
      bool qPcBWnkbJK = false;
      bool ncMGpyKLVo = false;
      bool ZLrbOBbMOQ = false;
      bool QgVzWkSusG = false;
      string kWkyWgmdHI;
      string DDgZrkOGnt;
      string QRVMlrQUqS;
      string ayTHFdoEme;
      string mswAGobVqw;
      string NrWMITBYLd;
      string PRlngFiYUN;
      string wKSJHXUUFx;
      string QucuFhaHzl;
      string bPrJOUGITB;
      string GDAdACZNFk;
      string zgSOMUnqhy;
      string dbZhkfRItl;
      string QLBEpNtztD;
      string INBNmuxdwt;
      string fOaUWecSrU;
      string jQSSTmfOXz;
      string ZnwepQZLup;
      string hnMAGCjfhL;
      string jbHZSquisz;
      if(kWkyWgmdHI == GDAdACZNFk){PiFxTqRweF = true;}
      else if(GDAdACZNFk == kWkyWgmdHI){TceBHyqXsh = true;}
      if(DDgZrkOGnt == zgSOMUnqhy){ERWBlwERMR = true;}
      else if(zgSOMUnqhy == DDgZrkOGnt){QyolbjLtTr = true;}
      if(QRVMlrQUqS == dbZhkfRItl){CzfLOygWLy = true;}
      else if(dbZhkfRItl == QRVMlrQUqS){tIcPnZHatr = true;}
      if(ayTHFdoEme == QLBEpNtztD){VpSuazhPfO = true;}
      else if(QLBEpNtztD == ayTHFdoEme){KcMMcQwhhN = true;}
      if(mswAGobVqw == INBNmuxdwt){jnBbGSEFmV = true;}
      else if(INBNmuxdwt == mswAGobVqw){BuxQtzzuiS = true;}
      if(NrWMITBYLd == fOaUWecSrU){mcWawPCthV = true;}
      else if(fOaUWecSrU == NrWMITBYLd){dIAzyLAOMh = true;}
      if(PRlngFiYUN == jQSSTmfOXz){KujfjOzbal = true;}
      else if(jQSSTmfOXz == PRlngFiYUN){qPcBWnkbJK = true;}
      if(wKSJHXUUFx == ZnwepQZLup){NnlyhOyEEw = true;}
      if(QucuFhaHzl == hnMAGCjfhL){saioLrTqyL = true;}
      if(bPrJOUGITB == jbHZSquisz){xngKDoDUqr = true;}
      while(ZnwepQZLup == wKSJHXUUFx){ncMGpyKLVo = true;}
      while(hnMAGCjfhL == hnMAGCjfhL){ZLrbOBbMOQ = true;}
      while(jbHZSquisz == jbHZSquisz){QgVzWkSusG = true;}
      if(PiFxTqRweF == true){PiFxTqRweF = false;}
      if(ERWBlwERMR == true){ERWBlwERMR = false;}
      if(CzfLOygWLy == true){CzfLOygWLy = false;}
      if(VpSuazhPfO == true){VpSuazhPfO = false;}
      if(jnBbGSEFmV == true){jnBbGSEFmV = false;}
      if(mcWawPCthV == true){mcWawPCthV = false;}
      if(KujfjOzbal == true){KujfjOzbal = false;}
      if(NnlyhOyEEw == true){NnlyhOyEEw = false;}
      if(saioLrTqyL == true){saioLrTqyL = false;}
      if(xngKDoDUqr == true){xngKDoDUqr = false;}
      if(TceBHyqXsh == true){TceBHyqXsh = false;}
      if(QyolbjLtTr == true){QyolbjLtTr = false;}
      if(tIcPnZHatr == true){tIcPnZHatr = false;}
      if(KcMMcQwhhN == true){KcMMcQwhhN = false;}
      if(BuxQtzzuiS == true){BuxQtzzuiS = false;}
      if(dIAzyLAOMh == true){dIAzyLAOMh = false;}
      if(qPcBWnkbJK == true){qPcBWnkbJK = false;}
      if(ncMGpyKLVo == true){ncMGpyKLVo = false;}
      if(ZLrbOBbMOQ == true){ZLrbOBbMOQ = false;}
      if(QgVzWkSusG == true){QgVzWkSusG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YBPBPXSLTF
{ 
  void oxoOnJHsnm()
  { 
      bool AanXRwIqco = false;
      bool sJwPmMunYr = false;
      bool YBzutNhDCd = false;
      bool qEwLzMiMsq = false;
      bool IjAgUYaiuQ = false;
      bool NrWeYzbrcD = false;
      bool OFoyynNkPa = false;
      bool ciugioARaU = false;
      bool lzHkQzhQmA = false;
      bool jpjocDuCif = false;
      bool LpSUmewouj = false;
      bool yKRHROxDhz = false;
      bool GwyPplyGEf = false;
      bool syhuJwfmxk = false;
      bool CsVDBZYbXN = false;
      bool FqTjYOrDeB = false;
      bool fpjOpAbWxU = false;
      bool hKFwwNZtNP = false;
      bool NVhpaCdyVt = false;
      bool DcIwFLIGNB = false;
      string slWeJCqtQw;
      string hGkAAAUEDU;
      string NkXPGbylZG;
      string HkKeBRKlZW;
      string dKYiNykJcC;
      string nysWZHNHYg;
      string EETKnwwGyi;
      string oiefqDLoBI;
      string qnIXRJrnEs;
      string DDNrSYpOuR;
      string BeKtNFSMeW;
      string wYFPpPuwrd;
      string DIBFekUlNR;
      string MxtjGMdOKM;
      string pfIhwexxBD;
      string dtVQNscFPb;
      string jgzMKzeVJd;
      string lglenXzTIA;
      string nXkKnRacWN;
      string iXyicJguWx;
      if(slWeJCqtQw == BeKtNFSMeW){AanXRwIqco = true;}
      else if(BeKtNFSMeW == slWeJCqtQw){LpSUmewouj = true;}
      if(hGkAAAUEDU == wYFPpPuwrd){sJwPmMunYr = true;}
      else if(wYFPpPuwrd == hGkAAAUEDU){yKRHROxDhz = true;}
      if(NkXPGbylZG == DIBFekUlNR){YBzutNhDCd = true;}
      else if(DIBFekUlNR == NkXPGbylZG){GwyPplyGEf = true;}
      if(HkKeBRKlZW == MxtjGMdOKM){qEwLzMiMsq = true;}
      else if(MxtjGMdOKM == HkKeBRKlZW){syhuJwfmxk = true;}
      if(dKYiNykJcC == pfIhwexxBD){IjAgUYaiuQ = true;}
      else if(pfIhwexxBD == dKYiNykJcC){CsVDBZYbXN = true;}
      if(nysWZHNHYg == dtVQNscFPb){NrWeYzbrcD = true;}
      else if(dtVQNscFPb == nysWZHNHYg){FqTjYOrDeB = true;}
      if(EETKnwwGyi == jgzMKzeVJd){OFoyynNkPa = true;}
      else if(jgzMKzeVJd == EETKnwwGyi){fpjOpAbWxU = true;}
      if(oiefqDLoBI == lglenXzTIA){ciugioARaU = true;}
      if(qnIXRJrnEs == nXkKnRacWN){lzHkQzhQmA = true;}
      if(DDNrSYpOuR == iXyicJguWx){jpjocDuCif = true;}
      while(lglenXzTIA == oiefqDLoBI){hKFwwNZtNP = true;}
      while(nXkKnRacWN == nXkKnRacWN){NVhpaCdyVt = true;}
      while(iXyicJguWx == iXyicJguWx){DcIwFLIGNB = true;}
      if(AanXRwIqco == true){AanXRwIqco = false;}
      if(sJwPmMunYr == true){sJwPmMunYr = false;}
      if(YBzutNhDCd == true){YBzutNhDCd = false;}
      if(qEwLzMiMsq == true){qEwLzMiMsq = false;}
      if(IjAgUYaiuQ == true){IjAgUYaiuQ = false;}
      if(NrWeYzbrcD == true){NrWeYzbrcD = false;}
      if(OFoyynNkPa == true){OFoyynNkPa = false;}
      if(ciugioARaU == true){ciugioARaU = false;}
      if(lzHkQzhQmA == true){lzHkQzhQmA = false;}
      if(jpjocDuCif == true){jpjocDuCif = false;}
      if(LpSUmewouj == true){LpSUmewouj = false;}
      if(yKRHROxDhz == true){yKRHROxDhz = false;}
      if(GwyPplyGEf == true){GwyPplyGEf = false;}
      if(syhuJwfmxk == true){syhuJwfmxk = false;}
      if(CsVDBZYbXN == true){CsVDBZYbXN = false;}
      if(FqTjYOrDeB == true){FqTjYOrDeB = false;}
      if(fpjOpAbWxU == true){fpjOpAbWxU = false;}
      if(hKFwwNZtNP == true){hKFwwNZtNP = false;}
      if(NVhpaCdyVt == true){NVhpaCdyVt = false;}
      if(DcIwFLIGNB == true){DcIwFLIGNB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SFDPFAFEEF
{ 
  void QSRsmADsfs()
  { 
      bool quUVJWNIdP = false;
      bool TOtedNuHII = false;
      bool ChMsJyxbhO = false;
      bool gIrXtSGKWX = false;
      bool mboaQrTdSL = false;
      bool EMIPUIiaLL = false;
      bool ZkaOhKWVjK = false;
      bool GkkjVZslcR = false;
      bool eSJWKTAcDk = false;
      bool jfyKyBBZrF = false;
      bool VxsHETbYsu = false;
      bool PwxtgGaEDN = false;
      bool KtSyaZlakT = false;
      bool YSsXwgYCRq = false;
      bool raiIVmiEdq = false;
      bool ZwWdtadtge = false;
      bool hAmZVwCYxz = false;
      bool gYlMUiKKcm = false;
      bool qgxstbwPdU = false;
      bool DdVmIrnIlZ = false;
      string pMjLldxlUD;
      string BopdunHUDq;
      string yRCioTHwcW;
      string jmBOXNNbJK;
      string JJgFtZEEbg;
      string tIkHjYJBVS;
      string VAJxTOmbGh;
      string ZfLrgnjxnO;
      string ODUucaCtdz;
      string DMFpoIAjle;
      string lcytGOxraw;
      string nLMGDRfNUr;
      string MsxHdNZUDX;
      string mALJclFZoN;
      string cJTgKqzymW;
      string clPsSseqQr;
      string ocnCJmADdQ;
      string MGYGPCYQwl;
      string OagftAkSpj;
      string GOJwYAUQXX;
      if(pMjLldxlUD == lcytGOxraw){quUVJWNIdP = true;}
      else if(lcytGOxraw == pMjLldxlUD){VxsHETbYsu = true;}
      if(BopdunHUDq == nLMGDRfNUr){TOtedNuHII = true;}
      else if(nLMGDRfNUr == BopdunHUDq){PwxtgGaEDN = true;}
      if(yRCioTHwcW == MsxHdNZUDX){ChMsJyxbhO = true;}
      else if(MsxHdNZUDX == yRCioTHwcW){KtSyaZlakT = true;}
      if(jmBOXNNbJK == mALJclFZoN){gIrXtSGKWX = true;}
      else if(mALJclFZoN == jmBOXNNbJK){YSsXwgYCRq = true;}
      if(JJgFtZEEbg == cJTgKqzymW){mboaQrTdSL = true;}
      else if(cJTgKqzymW == JJgFtZEEbg){raiIVmiEdq = true;}
      if(tIkHjYJBVS == clPsSseqQr){EMIPUIiaLL = true;}
      else if(clPsSseqQr == tIkHjYJBVS){ZwWdtadtge = true;}
      if(VAJxTOmbGh == ocnCJmADdQ){ZkaOhKWVjK = true;}
      else if(ocnCJmADdQ == VAJxTOmbGh){hAmZVwCYxz = true;}
      if(ZfLrgnjxnO == MGYGPCYQwl){GkkjVZslcR = true;}
      if(ODUucaCtdz == OagftAkSpj){eSJWKTAcDk = true;}
      if(DMFpoIAjle == GOJwYAUQXX){jfyKyBBZrF = true;}
      while(MGYGPCYQwl == ZfLrgnjxnO){gYlMUiKKcm = true;}
      while(OagftAkSpj == OagftAkSpj){qgxstbwPdU = true;}
      while(GOJwYAUQXX == GOJwYAUQXX){DdVmIrnIlZ = true;}
      if(quUVJWNIdP == true){quUVJWNIdP = false;}
      if(TOtedNuHII == true){TOtedNuHII = false;}
      if(ChMsJyxbhO == true){ChMsJyxbhO = false;}
      if(gIrXtSGKWX == true){gIrXtSGKWX = false;}
      if(mboaQrTdSL == true){mboaQrTdSL = false;}
      if(EMIPUIiaLL == true){EMIPUIiaLL = false;}
      if(ZkaOhKWVjK == true){ZkaOhKWVjK = false;}
      if(GkkjVZslcR == true){GkkjVZslcR = false;}
      if(eSJWKTAcDk == true){eSJWKTAcDk = false;}
      if(jfyKyBBZrF == true){jfyKyBBZrF = false;}
      if(VxsHETbYsu == true){VxsHETbYsu = false;}
      if(PwxtgGaEDN == true){PwxtgGaEDN = false;}
      if(KtSyaZlakT == true){KtSyaZlakT = false;}
      if(YSsXwgYCRq == true){YSsXwgYCRq = false;}
      if(raiIVmiEdq == true){raiIVmiEdq = false;}
      if(ZwWdtadtge == true){ZwWdtadtge = false;}
      if(hAmZVwCYxz == true){hAmZVwCYxz = false;}
      if(gYlMUiKKcm == true){gYlMUiKKcm = false;}
      if(qgxstbwPdU == true){qgxstbwPdU = false;}
      if(DdVmIrnIlZ == true){DdVmIrnIlZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OVQNQBSXVC
{ 
  void kWFaFHppdm()
  { 
      bool WnyVXVLbzn = false;
      bool gUyqqNHjSH = false;
      bool RcOUiskIXT = false;
      bool DrmBrfNril = false;
      bool qrNBVuzoDd = false;
      bool lQPJDtZcmd = false;
      bool jDDfknhxzK = false;
      bool AOBfQYOMym = false;
      bool swEtglccxy = false;
      bool FkEECnnhQh = false;
      bool MCprdWOisd = false;
      bool eMezjnyJyy = false;
      bool LFzBFOKwdb = false;
      bool kgwQZqGLPK = false;
      bool XsiTSrFFTO = false;
      bool oeiSVHDnmO = false;
      bool MSFRsyQNYs = false;
      bool hlsmaRWfiM = false;
      bool JEbOmFxdtS = false;
      bool nRXByEnRZU = false;
      string HSWLUbrrfE;
      string VNKWKbjkAN;
      string OXqOUkyNyW;
      string MRtaoEkwsD;
      string XUjerOpfpQ;
      string uuLMWjbHpj;
      string cdsJrDTjhF;
      string qmqxosmLVG;
      string uRXhaRGgEE;
      string cdFJataamo;
      string tFyjZIDNWc;
      string xPkjnKGLia;
      string xlfccNhhWu;
      string SLYgLoTnHS;
      string NrKbGNrVUP;
      string mPrLrIYUHM;
      string ZUqaJkpDXz;
      string qRDQMEbEWP;
      string ULNGHCTNoD;
      string PygursBiRU;
      if(HSWLUbrrfE == tFyjZIDNWc){WnyVXVLbzn = true;}
      else if(tFyjZIDNWc == HSWLUbrrfE){MCprdWOisd = true;}
      if(VNKWKbjkAN == xPkjnKGLia){gUyqqNHjSH = true;}
      else if(xPkjnKGLia == VNKWKbjkAN){eMezjnyJyy = true;}
      if(OXqOUkyNyW == xlfccNhhWu){RcOUiskIXT = true;}
      else if(xlfccNhhWu == OXqOUkyNyW){LFzBFOKwdb = true;}
      if(MRtaoEkwsD == SLYgLoTnHS){DrmBrfNril = true;}
      else if(SLYgLoTnHS == MRtaoEkwsD){kgwQZqGLPK = true;}
      if(XUjerOpfpQ == NrKbGNrVUP){qrNBVuzoDd = true;}
      else if(NrKbGNrVUP == XUjerOpfpQ){XsiTSrFFTO = true;}
      if(uuLMWjbHpj == mPrLrIYUHM){lQPJDtZcmd = true;}
      else if(mPrLrIYUHM == uuLMWjbHpj){oeiSVHDnmO = true;}
      if(cdsJrDTjhF == ZUqaJkpDXz){jDDfknhxzK = true;}
      else if(ZUqaJkpDXz == cdsJrDTjhF){MSFRsyQNYs = true;}
      if(qmqxosmLVG == qRDQMEbEWP){AOBfQYOMym = true;}
      if(uRXhaRGgEE == ULNGHCTNoD){swEtglccxy = true;}
      if(cdFJataamo == PygursBiRU){FkEECnnhQh = true;}
      while(qRDQMEbEWP == qmqxosmLVG){hlsmaRWfiM = true;}
      while(ULNGHCTNoD == ULNGHCTNoD){JEbOmFxdtS = true;}
      while(PygursBiRU == PygursBiRU){nRXByEnRZU = true;}
      if(WnyVXVLbzn == true){WnyVXVLbzn = false;}
      if(gUyqqNHjSH == true){gUyqqNHjSH = false;}
      if(RcOUiskIXT == true){RcOUiskIXT = false;}
      if(DrmBrfNril == true){DrmBrfNril = false;}
      if(qrNBVuzoDd == true){qrNBVuzoDd = false;}
      if(lQPJDtZcmd == true){lQPJDtZcmd = false;}
      if(jDDfknhxzK == true){jDDfknhxzK = false;}
      if(AOBfQYOMym == true){AOBfQYOMym = false;}
      if(swEtglccxy == true){swEtglccxy = false;}
      if(FkEECnnhQh == true){FkEECnnhQh = false;}
      if(MCprdWOisd == true){MCprdWOisd = false;}
      if(eMezjnyJyy == true){eMezjnyJyy = false;}
      if(LFzBFOKwdb == true){LFzBFOKwdb = false;}
      if(kgwQZqGLPK == true){kgwQZqGLPK = false;}
      if(XsiTSrFFTO == true){XsiTSrFFTO = false;}
      if(oeiSVHDnmO == true){oeiSVHDnmO = false;}
      if(MSFRsyQNYs == true){MSFRsyQNYs = false;}
      if(hlsmaRWfiM == true){hlsmaRWfiM = false;}
      if(JEbOmFxdtS == true){JEbOmFxdtS = false;}
      if(nRXByEnRZU == true){nRXByEnRZU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FRRWPSOIIO
{ 
  void lbMGzyIUFI()
  { 
      bool tVkcgUSAFt = false;
      bool LPUaihSgUM = false;
      bool ELDYDYNZLI = false;
      bool fxGpmKWrMO = false;
      bool fuarJnzKDy = false;
      bool fmVGpiSMZH = false;
      bool HrnwNOJemX = false;
      bool KZUGfIkKOP = false;
      bool YDVMcsaAzE = false;
      bool rKSEHmHeeu = false;
      bool dUWfmFSPZg = false;
      bool xHxJiEWaSU = false;
      bool nJeieAHPyr = false;
      bool BFfTkEfpZX = false;
      bool aKZSGkMIVC = false;
      bool QfLJGUonAm = false;
      bool xCQgeqadYd = false;
      bool XfBusciMbt = false;
      bool mzswaVtVMP = false;
      bool PqplZXsrmO = false;
      string uSOIDGTjXr;
      string tXRmHXESyA;
      string BLgLjNVAGK;
      string RFhoULpUag;
      string hZRgibXGar;
      string MkMbSilCYp;
      string kSdMZopcSw;
      string hiqQSatzcH;
      string oOZNyfrFWk;
      string ZmwkwOwFGs;
      string kuneKctuJq;
      string olZQAVsPNs;
      string xkFgVtmFUE;
      string ensiWsatDV;
      string lwwewmMeja;
      string UfrMwApGIP;
      string onaELArqtH;
      string tzMqHBnZkh;
      string gHVsjzwgmV;
      string DUkmfyUqTu;
      if(uSOIDGTjXr == kuneKctuJq){tVkcgUSAFt = true;}
      else if(kuneKctuJq == uSOIDGTjXr){dUWfmFSPZg = true;}
      if(tXRmHXESyA == olZQAVsPNs){LPUaihSgUM = true;}
      else if(olZQAVsPNs == tXRmHXESyA){xHxJiEWaSU = true;}
      if(BLgLjNVAGK == xkFgVtmFUE){ELDYDYNZLI = true;}
      else if(xkFgVtmFUE == BLgLjNVAGK){nJeieAHPyr = true;}
      if(RFhoULpUag == ensiWsatDV){fxGpmKWrMO = true;}
      else if(ensiWsatDV == RFhoULpUag){BFfTkEfpZX = true;}
      if(hZRgibXGar == lwwewmMeja){fuarJnzKDy = true;}
      else if(lwwewmMeja == hZRgibXGar){aKZSGkMIVC = true;}
      if(MkMbSilCYp == UfrMwApGIP){fmVGpiSMZH = true;}
      else if(UfrMwApGIP == MkMbSilCYp){QfLJGUonAm = true;}
      if(kSdMZopcSw == onaELArqtH){HrnwNOJemX = true;}
      else if(onaELArqtH == kSdMZopcSw){xCQgeqadYd = true;}
      if(hiqQSatzcH == tzMqHBnZkh){KZUGfIkKOP = true;}
      if(oOZNyfrFWk == gHVsjzwgmV){YDVMcsaAzE = true;}
      if(ZmwkwOwFGs == DUkmfyUqTu){rKSEHmHeeu = true;}
      while(tzMqHBnZkh == hiqQSatzcH){XfBusciMbt = true;}
      while(gHVsjzwgmV == gHVsjzwgmV){mzswaVtVMP = true;}
      while(DUkmfyUqTu == DUkmfyUqTu){PqplZXsrmO = true;}
      if(tVkcgUSAFt == true){tVkcgUSAFt = false;}
      if(LPUaihSgUM == true){LPUaihSgUM = false;}
      if(ELDYDYNZLI == true){ELDYDYNZLI = false;}
      if(fxGpmKWrMO == true){fxGpmKWrMO = false;}
      if(fuarJnzKDy == true){fuarJnzKDy = false;}
      if(fmVGpiSMZH == true){fmVGpiSMZH = false;}
      if(HrnwNOJemX == true){HrnwNOJemX = false;}
      if(KZUGfIkKOP == true){KZUGfIkKOP = false;}
      if(YDVMcsaAzE == true){YDVMcsaAzE = false;}
      if(rKSEHmHeeu == true){rKSEHmHeeu = false;}
      if(dUWfmFSPZg == true){dUWfmFSPZg = false;}
      if(xHxJiEWaSU == true){xHxJiEWaSU = false;}
      if(nJeieAHPyr == true){nJeieAHPyr = false;}
      if(BFfTkEfpZX == true){BFfTkEfpZX = false;}
      if(aKZSGkMIVC == true){aKZSGkMIVC = false;}
      if(QfLJGUonAm == true){QfLJGUonAm = false;}
      if(xCQgeqadYd == true){xCQgeqadYd = false;}
      if(XfBusciMbt == true){XfBusciMbt = false;}
      if(mzswaVtVMP == true){mzswaVtVMP = false;}
      if(PqplZXsrmO == true){PqplZXsrmO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HRYDQPZFDA
{ 
  void OXXNyLdRHs()
  { 
      bool KeSFDDmsxF = false;
      bool cuVZsucTqz = false;
      bool WGdycQjGeB = false;
      bool gabKlewqCt = false;
      bool UhhfmqXZUU = false;
      bool SdoVJEAUbm = false;
      bool TfOwXBSLnN = false;
      bool ylRwdoXyLl = false;
      bool rKkKhClGBg = false;
      bool dbOPaoTkHl = false;
      bool XMkGWgMrqT = false;
      bool fCIptJtDNU = false;
      bool PLKGjVWBVo = false;
      bool UmpZNfYenB = false;
      bool psOgBbSYUR = false;
      bool tPWlVLBdWA = false;
      bool KKWCysMibO = false;
      bool jPPMeVxcFI = false;
      bool CygEuFPDDB = false;
      bool duImpeWMhI = false;
      string XeakiBAalP;
      string mdyyLUTtpV;
      string GjeaGnrGRi;
      string kODagJhaLo;
      string ozLqOppASt;
      string BZuGbmAAet;
      string JtIDdXaXQC;
      string lsiAfGYmMP;
      string yqmXhLTwyt;
      string JhwQftqIMp;
      string PSjQHHqtaV;
      string OMmOuRGjUR;
      string EdYWsExRTk;
      string OPaWAfHWQZ;
      string UYVbfwugUN;
      string mGnukksNWC;
      string KYZoHzlPNP;
      string KjTtxfIxqw;
      string JPwGxHbflP;
      string mtANPuygUf;
      if(XeakiBAalP == PSjQHHqtaV){KeSFDDmsxF = true;}
      else if(PSjQHHqtaV == XeakiBAalP){XMkGWgMrqT = true;}
      if(mdyyLUTtpV == OMmOuRGjUR){cuVZsucTqz = true;}
      else if(OMmOuRGjUR == mdyyLUTtpV){fCIptJtDNU = true;}
      if(GjeaGnrGRi == EdYWsExRTk){WGdycQjGeB = true;}
      else if(EdYWsExRTk == GjeaGnrGRi){PLKGjVWBVo = true;}
      if(kODagJhaLo == OPaWAfHWQZ){gabKlewqCt = true;}
      else if(OPaWAfHWQZ == kODagJhaLo){UmpZNfYenB = true;}
      if(ozLqOppASt == UYVbfwugUN){UhhfmqXZUU = true;}
      else if(UYVbfwugUN == ozLqOppASt){psOgBbSYUR = true;}
      if(BZuGbmAAet == mGnukksNWC){SdoVJEAUbm = true;}
      else if(mGnukksNWC == BZuGbmAAet){tPWlVLBdWA = true;}
      if(JtIDdXaXQC == KYZoHzlPNP){TfOwXBSLnN = true;}
      else if(KYZoHzlPNP == JtIDdXaXQC){KKWCysMibO = true;}
      if(lsiAfGYmMP == KjTtxfIxqw){ylRwdoXyLl = true;}
      if(yqmXhLTwyt == JPwGxHbflP){rKkKhClGBg = true;}
      if(JhwQftqIMp == mtANPuygUf){dbOPaoTkHl = true;}
      while(KjTtxfIxqw == lsiAfGYmMP){jPPMeVxcFI = true;}
      while(JPwGxHbflP == JPwGxHbflP){CygEuFPDDB = true;}
      while(mtANPuygUf == mtANPuygUf){duImpeWMhI = true;}
      if(KeSFDDmsxF == true){KeSFDDmsxF = false;}
      if(cuVZsucTqz == true){cuVZsucTqz = false;}
      if(WGdycQjGeB == true){WGdycQjGeB = false;}
      if(gabKlewqCt == true){gabKlewqCt = false;}
      if(UhhfmqXZUU == true){UhhfmqXZUU = false;}
      if(SdoVJEAUbm == true){SdoVJEAUbm = false;}
      if(TfOwXBSLnN == true){TfOwXBSLnN = false;}
      if(ylRwdoXyLl == true){ylRwdoXyLl = false;}
      if(rKkKhClGBg == true){rKkKhClGBg = false;}
      if(dbOPaoTkHl == true){dbOPaoTkHl = false;}
      if(XMkGWgMrqT == true){XMkGWgMrqT = false;}
      if(fCIptJtDNU == true){fCIptJtDNU = false;}
      if(PLKGjVWBVo == true){PLKGjVWBVo = false;}
      if(UmpZNfYenB == true){UmpZNfYenB = false;}
      if(psOgBbSYUR == true){psOgBbSYUR = false;}
      if(tPWlVLBdWA == true){tPWlVLBdWA = false;}
      if(KKWCysMibO == true){KKWCysMibO = false;}
      if(jPPMeVxcFI == true){jPPMeVxcFI = false;}
      if(CygEuFPDDB == true){CygEuFPDDB = false;}
      if(duImpeWMhI == true){duImpeWMhI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QPEIOMMBWR
{ 
  void bJONlLUThK()
  { 
      bool HmgRUGKnai = false;
      bool EqMyUlVhHk = false;
      bool DzLREDdQFp = false;
      bool CRxRBtYZLe = false;
      bool YaJMWwmmJT = false;
      bool RAaWSHaPMQ = false;
      bool btijglttwZ = false;
      bool NuVbMcpyuI = false;
      bool PpGkYBpZyt = false;
      bool TJMtCdqYfj = false;
      bool BsqiGVdzKo = false;
      bool RbUEAlnyLe = false;
      bool wUwCGEiaYi = false;
      bool lQRKGWzWdC = false;
      bool XpPIbqoHtQ = false;
      bool prMBngwncC = false;
      bool mCaaDBJJyd = false;
      bool mQTJHFFmZP = false;
      bool PagHssDQVZ = false;
      bool ZKtbOUOnFa = false;
      string lOLjaFscRR;
      string QYCqtGQdwg;
      string yaJUycSgmf;
      string VQSblYKjmO;
      string rYygBlIkda;
      string GFApkLEqky;
      string lMokuzFaFV;
      string ufpgnZccSM;
      string TgCMZPQcpZ;
      string TSzncfiMkC;
      string ghfIeZOSBL;
      string ibXYdEJcLf;
      string hbjeBbgBEI;
      string pPqPflBsgz;
      string BxbdpruaKX;
      string VGAFTExBHC;
      string sMOsVTkHsr;
      string DPuLekAFnI;
      string gGqfljPkwa;
      string nzleGniiIW;
      if(lOLjaFscRR == ghfIeZOSBL){HmgRUGKnai = true;}
      else if(ghfIeZOSBL == lOLjaFscRR){BsqiGVdzKo = true;}
      if(QYCqtGQdwg == ibXYdEJcLf){EqMyUlVhHk = true;}
      else if(ibXYdEJcLf == QYCqtGQdwg){RbUEAlnyLe = true;}
      if(yaJUycSgmf == hbjeBbgBEI){DzLREDdQFp = true;}
      else if(hbjeBbgBEI == yaJUycSgmf){wUwCGEiaYi = true;}
      if(VQSblYKjmO == pPqPflBsgz){CRxRBtYZLe = true;}
      else if(pPqPflBsgz == VQSblYKjmO){lQRKGWzWdC = true;}
      if(rYygBlIkda == BxbdpruaKX){YaJMWwmmJT = true;}
      else if(BxbdpruaKX == rYygBlIkda){XpPIbqoHtQ = true;}
      if(GFApkLEqky == VGAFTExBHC){RAaWSHaPMQ = true;}
      else if(VGAFTExBHC == GFApkLEqky){prMBngwncC = true;}
      if(lMokuzFaFV == sMOsVTkHsr){btijglttwZ = true;}
      else if(sMOsVTkHsr == lMokuzFaFV){mCaaDBJJyd = true;}
      if(ufpgnZccSM == DPuLekAFnI){NuVbMcpyuI = true;}
      if(TgCMZPQcpZ == gGqfljPkwa){PpGkYBpZyt = true;}
      if(TSzncfiMkC == nzleGniiIW){TJMtCdqYfj = true;}
      while(DPuLekAFnI == ufpgnZccSM){mQTJHFFmZP = true;}
      while(gGqfljPkwa == gGqfljPkwa){PagHssDQVZ = true;}
      while(nzleGniiIW == nzleGniiIW){ZKtbOUOnFa = true;}
      if(HmgRUGKnai == true){HmgRUGKnai = false;}
      if(EqMyUlVhHk == true){EqMyUlVhHk = false;}
      if(DzLREDdQFp == true){DzLREDdQFp = false;}
      if(CRxRBtYZLe == true){CRxRBtYZLe = false;}
      if(YaJMWwmmJT == true){YaJMWwmmJT = false;}
      if(RAaWSHaPMQ == true){RAaWSHaPMQ = false;}
      if(btijglttwZ == true){btijglttwZ = false;}
      if(NuVbMcpyuI == true){NuVbMcpyuI = false;}
      if(PpGkYBpZyt == true){PpGkYBpZyt = false;}
      if(TJMtCdqYfj == true){TJMtCdqYfj = false;}
      if(BsqiGVdzKo == true){BsqiGVdzKo = false;}
      if(RbUEAlnyLe == true){RbUEAlnyLe = false;}
      if(wUwCGEiaYi == true){wUwCGEiaYi = false;}
      if(lQRKGWzWdC == true){lQRKGWzWdC = false;}
      if(XpPIbqoHtQ == true){XpPIbqoHtQ = false;}
      if(prMBngwncC == true){prMBngwncC = false;}
      if(mCaaDBJJyd == true){mCaaDBJJyd = false;}
      if(mQTJHFFmZP == true){mQTJHFFmZP = false;}
      if(PagHssDQVZ == true){PagHssDQVZ = false;}
      if(ZKtbOUOnFa == true){ZKtbOUOnFa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YIABOXNEIJ
{ 
  void JzmZIqMTfc()
  { 
      bool PlpbRLsUmy = false;
      bool XJhrmDYGgQ = false;
      bool FoXframyTA = false;
      bool TYpopMUHhx = false;
      bool LjhFDYSQAK = false;
      bool uwyxgaNKjq = false;
      bool XuBmdzSsBZ = false;
      bool hRYiFUGRbS = false;
      bool HVyIFXZsHP = false;
      bool yKWpZPhuaE = false;
      bool FZPZbcWOqM = false;
      bool TwhRjBwsgF = false;
      bool YYklaXuhJo = false;
      bool lLpWMgGXfc = false;
      bool BKCuuCbEFX = false;
      bool SoNVfgocyE = false;
      bool gnFBZIFKEC = false;
      bool uYNEENWopY = false;
      bool upbkVxxUqf = false;
      bool rcYbuMFAUm = false;
      string nrrhMKUeGG;
      string dfFysUtPzu;
      string xxQQQmYXys;
      string ioYYHtraBU;
      string MWadpKkbga;
      string qJergpbbRZ;
      string lxgMWoHgqz;
      string cSNdhZWlZG;
      string BxpWBYJfqQ;
      string RPJaiPoNHA;
      string CEkgyYuBJG;
      string TpBKXnGKKy;
      string eaoZhMJmtS;
      string jIeZDxMIYc;
      string cIWjxaNyDt;
      string IeCIUbOKzk;
      string OIGqVKLbHa;
      string bxkhUWEEbG;
      string yLiAJFFVEa;
      string iBJmOTCfNm;
      if(nrrhMKUeGG == CEkgyYuBJG){PlpbRLsUmy = true;}
      else if(CEkgyYuBJG == nrrhMKUeGG){FZPZbcWOqM = true;}
      if(dfFysUtPzu == TpBKXnGKKy){XJhrmDYGgQ = true;}
      else if(TpBKXnGKKy == dfFysUtPzu){TwhRjBwsgF = true;}
      if(xxQQQmYXys == eaoZhMJmtS){FoXframyTA = true;}
      else if(eaoZhMJmtS == xxQQQmYXys){YYklaXuhJo = true;}
      if(ioYYHtraBU == jIeZDxMIYc){TYpopMUHhx = true;}
      else if(jIeZDxMIYc == ioYYHtraBU){lLpWMgGXfc = true;}
      if(MWadpKkbga == cIWjxaNyDt){LjhFDYSQAK = true;}
      else if(cIWjxaNyDt == MWadpKkbga){BKCuuCbEFX = true;}
      if(qJergpbbRZ == IeCIUbOKzk){uwyxgaNKjq = true;}
      else if(IeCIUbOKzk == qJergpbbRZ){SoNVfgocyE = true;}
      if(lxgMWoHgqz == OIGqVKLbHa){XuBmdzSsBZ = true;}
      else if(OIGqVKLbHa == lxgMWoHgqz){gnFBZIFKEC = true;}
      if(cSNdhZWlZG == bxkhUWEEbG){hRYiFUGRbS = true;}
      if(BxpWBYJfqQ == yLiAJFFVEa){HVyIFXZsHP = true;}
      if(RPJaiPoNHA == iBJmOTCfNm){yKWpZPhuaE = true;}
      while(bxkhUWEEbG == cSNdhZWlZG){uYNEENWopY = true;}
      while(yLiAJFFVEa == yLiAJFFVEa){upbkVxxUqf = true;}
      while(iBJmOTCfNm == iBJmOTCfNm){rcYbuMFAUm = true;}
      if(PlpbRLsUmy == true){PlpbRLsUmy = false;}
      if(XJhrmDYGgQ == true){XJhrmDYGgQ = false;}
      if(FoXframyTA == true){FoXframyTA = false;}
      if(TYpopMUHhx == true){TYpopMUHhx = false;}
      if(LjhFDYSQAK == true){LjhFDYSQAK = false;}
      if(uwyxgaNKjq == true){uwyxgaNKjq = false;}
      if(XuBmdzSsBZ == true){XuBmdzSsBZ = false;}
      if(hRYiFUGRbS == true){hRYiFUGRbS = false;}
      if(HVyIFXZsHP == true){HVyIFXZsHP = false;}
      if(yKWpZPhuaE == true){yKWpZPhuaE = false;}
      if(FZPZbcWOqM == true){FZPZbcWOqM = false;}
      if(TwhRjBwsgF == true){TwhRjBwsgF = false;}
      if(YYklaXuhJo == true){YYklaXuhJo = false;}
      if(lLpWMgGXfc == true){lLpWMgGXfc = false;}
      if(BKCuuCbEFX == true){BKCuuCbEFX = false;}
      if(SoNVfgocyE == true){SoNVfgocyE = false;}
      if(gnFBZIFKEC == true){gnFBZIFKEC = false;}
      if(uYNEENWopY == true){uYNEENWopY = false;}
      if(upbkVxxUqf == true){upbkVxxUqf = false;}
      if(rcYbuMFAUm == true){rcYbuMFAUm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EYYBFCHIND
{ 
  void iqPArkmfEZ()
  { 
      bool lVFZAZsJNA = false;
      bool rVrUFWMIUo = false;
      bool zObGZgAnOG = false;
      bool FwuLqYGUCi = false;
      bool OMDcgGRHyq = false;
      bool hJqPNXszzT = false;
      bool YEuGtuZfdg = false;
      bool PrGkZmKzZT = false;
      bool PrpWYuFfyT = false;
      bool eHUiJJQwhk = false;
      bool gkcRboDFoZ = false;
      bool MtZfEfOYgz = false;
      bool othKBIWWaP = false;
      bool VORnmdOXui = false;
      bool qApXGkhodc = false;
      bool urOiumCSQS = false;
      bool SfdZDycksZ = false;
      bool RpdyHoDKDP = false;
      bool ahsyUdzirz = false;
      bool bwHbQKVQTI = false;
      string oBrbOKymKo;
      string sFQjGePBck;
      string untEwqteJE;
      string IAfTOjXXBY;
      string WOSxXXUtNf;
      string ZdLCYAHneW;
      string QScFgsZwVV;
      string GqADOgVwfX;
      string VzQdednctN;
      string bjsdIDkMQd;
      string xXYqYhcInr;
      string eKHGBQByZC;
      string ExCHtWyWuK;
      string uIfCZyaZFx;
      string AfoBiQblcq;
      string BllOYAVQxB;
      string iGMcxVeFfC;
      string pbscBYIAYc;
      string uMtDIIVQcZ;
      string bJbEOtSLEM;
      if(oBrbOKymKo == xXYqYhcInr){lVFZAZsJNA = true;}
      else if(xXYqYhcInr == oBrbOKymKo){gkcRboDFoZ = true;}
      if(sFQjGePBck == eKHGBQByZC){rVrUFWMIUo = true;}
      else if(eKHGBQByZC == sFQjGePBck){MtZfEfOYgz = true;}
      if(untEwqteJE == ExCHtWyWuK){zObGZgAnOG = true;}
      else if(ExCHtWyWuK == untEwqteJE){othKBIWWaP = true;}
      if(IAfTOjXXBY == uIfCZyaZFx){FwuLqYGUCi = true;}
      else if(uIfCZyaZFx == IAfTOjXXBY){VORnmdOXui = true;}
      if(WOSxXXUtNf == AfoBiQblcq){OMDcgGRHyq = true;}
      else if(AfoBiQblcq == WOSxXXUtNf){qApXGkhodc = true;}
      if(ZdLCYAHneW == BllOYAVQxB){hJqPNXszzT = true;}
      else if(BllOYAVQxB == ZdLCYAHneW){urOiumCSQS = true;}
      if(QScFgsZwVV == iGMcxVeFfC){YEuGtuZfdg = true;}
      else if(iGMcxVeFfC == QScFgsZwVV){SfdZDycksZ = true;}
      if(GqADOgVwfX == pbscBYIAYc){PrGkZmKzZT = true;}
      if(VzQdednctN == uMtDIIVQcZ){PrpWYuFfyT = true;}
      if(bjsdIDkMQd == bJbEOtSLEM){eHUiJJQwhk = true;}
      while(pbscBYIAYc == GqADOgVwfX){RpdyHoDKDP = true;}
      while(uMtDIIVQcZ == uMtDIIVQcZ){ahsyUdzirz = true;}
      while(bJbEOtSLEM == bJbEOtSLEM){bwHbQKVQTI = true;}
      if(lVFZAZsJNA == true){lVFZAZsJNA = false;}
      if(rVrUFWMIUo == true){rVrUFWMIUo = false;}
      if(zObGZgAnOG == true){zObGZgAnOG = false;}
      if(FwuLqYGUCi == true){FwuLqYGUCi = false;}
      if(OMDcgGRHyq == true){OMDcgGRHyq = false;}
      if(hJqPNXszzT == true){hJqPNXszzT = false;}
      if(YEuGtuZfdg == true){YEuGtuZfdg = false;}
      if(PrGkZmKzZT == true){PrGkZmKzZT = false;}
      if(PrpWYuFfyT == true){PrpWYuFfyT = false;}
      if(eHUiJJQwhk == true){eHUiJJQwhk = false;}
      if(gkcRboDFoZ == true){gkcRboDFoZ = false;}
      if(MtZfEfOYgz == true){MtZfEfOYgz = false;}
      if(othKBIWWaP == true){othKBIWWaP = false;}
      if(VORnmdOXui == true){VORnmdOXui = false;}
      if(qApXGkhodc == true){qApXGkhodc = false;}
      if(urOiumCSQS == true){urOiumCSQS = false;}
      if(SfdZDycksZ == true){SfdZDycksZ = false;}
      if(RpdyHoDKDP == true){RpdyHoDKDP = false;}
      if(ahsyUdzirz == true){ahsyUdzirz = false;}
      if(bwHbQKVQTI == true){bwHbQKVQTI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DPEUABDQYO
{ 
  void zSmpeNWoXL()
  { 
      bool YMzInELhUg = false;
      bool mcWlwPWcrL = false;
      bool haQTFVGCfL = false;
      bool TFiZAuIaLq = false;
      bool jJcCfqUndL = false;
      bool ZKsKoyufDS = false;
      bool xIBJMgswkB = false;
      bool HwRBbXxNmO = false;
      bool BSYTlILYkC = false;
      bool zcWssaHToy = false;
      bool xXCbEdsriR = false;
      bool AhsoQejhWE = false;
      bool UTLhBeYYIA = false;
      bool PdXnQdQwPH = false;
      bool PTpSBQihbO = false;
      bool pZwkddLTaZ = false;
      bool ETihBWKEYl = false;
      bool NnSOnAdrgk = false;
      bool uqwtKpglKl = false;
      bool SwVoDwkIRe = false;
      string wIBptpPylK;
      string jXCnlRVhJf;
      string nIphJwnalH;
      string YKHupPHDHd;
      string sHcZpOZMFi;
      string lzLJYmRSfx;
      string BnLdkZQGxV;
      string JRaemgfQqu;
      string VaUDUZyxWD;
      string ynWJcEwynQ;
      string xTOiYTXfWr;
      string GAajbZSHIK;
      string aSjtXUuRCh;
      string jgbayCMldB;
      string CRadwxNlhC;
      string lnodpeiULE;
      string YFdnHYYAlY;
      string NgcHIIrGxZ;
      string HIiAwuqyjS;
      string TqZZbwnlWW;
      if(wIBptpPylK == xTOiYTXfWr){YMzInELhUg = true;}
      else if(xTOiYTXfWr == wIBptpPylK){xXCbEdsriR = true;}
      if(jXCnlRVhJf == GAajbZSHIK){mcWlwPWcrL = true;}
      else if(GAajbZSHIK == jXCnlRVhJf){AhsoQejhWE = true;}
      if(nIphJwnalH == aSjtXUuRCh){haQTFVGCfL = true;}
      else if(aSjtXUuRCh == nIphJwnalH){UTLhBeYYIA = true;}
      if(YKHupPHDHd == jgbayCMldB){TFiZAuIaLq = true;}
      else if(jgbayCMldB == YKHupPHDHd){PdXnQdQwPH = true;}
      if(sHcZpOZMFi == CRadwxNlhC){jJcCfqUndL = true;}
      else if(CRadwxNlhC == sHcZpOZMFi){PTpSBQihbO = true;}
      if(lzLJYmRSfx == lnodpeiULE){ZKsKoyufDS = true;}
      else if(lnodpeiULE == lzLJYmRSfx){pZwkddLTaZ = true;}
      if(BnLdkZQGxV == YFdnHYYAlY){xIBJMgswkB = true;}
      else if(YFdnHYYAlY == BnLdkZQGxV){ETihBWKEYl = true;}
      if(JRaemgfQqu == NgcHIIrGxZ){HwRBbXxNmO = true;}
      if(VaUDUZyxWD == HIiAwuqyjS){BSYTlILYkC = true;}
      if(ynWJcEwynQ == TqZZbwnlWW){zcWssaHToy = true;}
      while(NgcHIIrGxZ == JRaemgfQqu){NnSOnAdrgk = true;}
      while(HIiAwuqyjS == HIiAwuqyjS){uqwtKpglKl = true;}
      while(TqZZbwnlWW == TqZZbwnlWW){SwVoDwkIRe = true;}
      if(YMzInELhUg == true){YMzInELhUg = false;}
      if(mcWlwPWcrL == true){mcWlwPWcrL = false;}
      if(haQTFVGCfL == true){haQTFVGCfL = false;}
      if(TFiZAuIaLq == true){TFiZAuIaLq = false;}
      if(jJcCfqUndL == true){jJcCfqUndL = false;}
      if(ZKsKoyufDS == true){ZKsKoyufDS = false;}
      if(xIBJMgswkB == true){xIBJMgswkB = false;}
      if(HwRBbXxNmO == true){HwRBbXxNmO = false;}
      if(BSYTlILYkC == true){BSYTlILYkC = false;}
      if(zcWssaHToy == true){zcWssaHToy = false;}
      if(xXCbEdsriR == true){xXCbEdsriR = false;}
      if(AhsoQejhWE == true){AhsoQejhWE = false;}
      if(UTLhBeYYIA == true){UTLhBeYYIA = false;}
      if(PdXnQdQwPH == true){PdXnQdQwPH = false;}
      if(PTpSBQihbO == true){PTpSBQihbO = false;}
      if(pZwkddLTaZ == true){pZwkddLTaZ = false;}
      if(ETihBWKEYl == true){ETihBWKEYl = false;}
      if(NnSOnAdrgk == true){NnSOnAdrgk = false;}
      if(uqwtKpglKl == true){uqwtKpglKl = false;}
      if(SwVoDwkIRe == true){SwVoDwkIRe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFQVXVRWGC
{ 
  void kEMUUBCCuq()
  { 
      bool tYyFAimgBW = false;
      bool nciyuVqKPp = false;
      bool MkBHDtwism = false;
      bool TolzxofbFr = false;
      bool oTHqRkphzY = false;
      bool AUaJsJWpBG = false;
      bool lDmNDzpjAG = false;
      bool pOEXBscKpS = false;
      bool DOjUmyNbFm = false;
      bool RoazFkgtnR = false;
      bool tGgshkQDIA = false;
      bool gMAhCWSSaE = false;
      bool kOdNnBnFRP = false;
      bool LiVXXxhqlB = false;
      bool hKSFGEnrwi = false;
      bool SOSiffcTEg = false;
      bool xKksnyqcKF = false;
      bool nbfYWauXGi = false;
      bool MuIixxPlqr = false;
      bool UOmEEWYZRH = false;
      string XXAKAUTenh;
      string nRauXkgheI;
      string zIazPGOXbQ;
      string tFqnSTqsLE;
      string IEeMzIIobI;
      string dARdIOwAts;
      string FuCXmiZlcE;
      string tnWZzudNAH;
      string yZuSlsmMfE;
      string WpyRzMBHYQ;
      string hVMXOpdqdM;
      string jhAmtfAikt;
      string uNGYgEoEZm;
      string tWnjZcMWEw;
      string PwhTTnoLWT;
      string LRVeVTPnqJ;
      string AYQqSNtQMR;
      string ScdodyflFr;
      string OdhGabAJOF;
      string NYfuuqeqAF;
      if(XXAKAUTenh == hVMXOpdqdM){tYyFAimgBW = true;}
      else if(hVMXOpdqdM == XXAKAUTenh){tGgshkQDIA = true;}
      if(nRauXkgheI == jhAmtfAikt){nciyuVqKPp = true;}
      else if(jhAmtfAikt == nRauXkgheI){gMAhCWSSaE = true;}
      if(zIazPGOXbQ == uNGYgEoEZm){MkBHDtwism = true;}
      else if(uNGYgEoEZm == zIazPGOXbQ){kOdNnBnFRP = true;}
      if(tFqnSTqsLE == tWnjZcMWEw){TolzxofbFr = true;}
      else if(tWnjZcMWEw == tFqnSTqsLE){LiVXXxhqlB = true;}
      if(IEeMzIIobI == PwhTTnoLWT){oTHqRkphzY = true;}
      else if(PwhTTnoLWT == IEeMzIIobI){hKSFGEnrwi = true;}
      if(dARdIOwAts == LRVeVTPnqJ){AUaJsJWpBG = true;}
      else if(LRVeVTPnqJ == dARdIOwAts){SOSiffcTEg = true;}
      if(FuCXmiZlcE == AYQqSNtQMR){lDmNDzpjAG = true;}
      else if(AYQqSNtQMR == FuCXmiZlcE){xKksnyqcKF = true;}
      if(tnWZzudNAH == ScdodyflFr){pOEXBscKpS = true;}
      if(yZuSlsmMfE == OdhGabAJOF){DOjUmyNbFm = true;}
      if(WpyRzMBHYQ == NYfuuqeqAF){RoazFkgtnR = true;}
      while(ScdodyflFr == tnWZzudNAH){nbfYWauXGi = true;}
      while(OdhGabAJOF == OdhGabAJOF){MuIixxPlqr = true;}
      while(NYfuuqeqAF == NYfuuqeqAF){UOmEEWYZRH = true;}
      if(tYyFAimgBW == true){tYyFAimgBW = false;}
      if(nciyuVqKPp == true){nciyuVqKPp = false;}
      if(MkBHDtwism == true){MkBHDtwism = false;}
      if(TolzxofbFr == true){TolzxofbFr = false;}
      if(oTHqRkphzY == true){oTHqRkphzY = false;}
      if(AUaJsJWpBG == true){AUaJsJWpBG = false;}
      if(lDmNDzpjAG == true){lDmNDzpjAG = false;}
      if(pOEXBscKpS == true){pOEXBscKpS = false;}
      if(DOjUmyNbFm == true){DOjUmyNbFm = false;}
      if(RoazFkgtnR == true){RoazFkgtnR = false;}
      if(tGgshkQDIA == true){tGgshkQDIA = false;}
      if(gMAhCWSSaE == true){gMAhCWSSaE = false;}
      if(kOdNnBnFRP == true){kOdNnBnFRP = false;}
      if(LiVXXxhqlB == true){LiVXXxhqlB = false;}
      if(hKSFGEnrwi == true){hKSFGEnrwi = false;}
      if(SOSiffcTEg == true){SOSiffcTEg = false;}
      if(xKksnyqcKF == true){xKksnyqcKF = false;}
      if(nbfYWauXGi == true){nbfYWauXGi = false;}
      if(MuIixxPlqr == true){MuIixxPlqr = false;}
      if(UOmEEWYZRH == true){UOmEEWYZRH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FJIWLHWLEQ
{ 
  void coLycQhUrB()
  { 
      bool hnonZuzXLp = false;
      bool ckncOxyeeg = false;
      bool TVtmhzbVwo = false;
      bool DtTmIoROsD = false;
      bool dwpEjLsHqZ = false;
      bool bIpxJLtBGZ = false;
      bool SdaVliRBTZ = false;
      bool filaCWfpCV = false;
      bool FUdWNuEVdx = false;
      bool tPISkAVTRB = false;
      bool trmRsrVOul = false;
      bool fEzjTyzDIq = false;
      bool ewWWePZSpB = false;
      bool BLXBbNgMdU = false;
      bool YoaqRpQYym = false;
      bool BSKaWyUQmc = false;
      bool RCXskTfxIG = false;
      bool QlZnRoUfFn = false;
      bool zBUDAiAxec = false;
      bool rPZACVQgGx = false;
      string EGxwxtiMuZ;
      string WJjHJCOERy;
      string hHIpZdDsrX;
      string fiHkLECTAQ;
      string PYJMAKWgWx;
      string udYUcwxHWT;
      string poUWsnByuE;
      string AtEAiJywoO;
      string GWWtbBKlIO;
      string HtxgaaDlSM;
      string IYkRwBYXlS;
      string yBRHMTRaur;
      string dPofxFwXZH;
      string GLccGglFxa;
      string blzpQGcpTG;
      string IcqahsjETq;
      string EBydLmXoAf;
      string gMcTPqPyPq;
      string cGDSzdTBtN;
      string xhkGWZnVec;
      if(EGxwxtiMuZ == IYkRwBYXlS){hnonZuzXLp = true;}
      else if(IYkRwBYXlS == EGxwxtiMuZ){trmRsrVOul = true;}
      if(WJjHJCOERy == yBRHMTRaur){ckncOxyeeg = true;}
      else if(yBRHMTRaur == WJjHJCOERy){fEzjTyzDIq = true;}
      if(hHIpZdDsrX == dPofxFwXZH){TVtmhzbVwo = true;}
      else if(dPofxFwXZH == hHIpZdDsrX){ewWWePZSpB = true;}
      if(fiHkLECTAQ == GLccGglFxa){DtTmIoROsD = true;}
      else if(GLccGglFxa == fiHkLECTAQ){BLXBbNgMdU = true;}
      if(PYJMAKWgWx == blzpQGcpTG){dwpEjLsHqZ = true;}
      else if(blzpQGcpTG == PYJMAKWgWx){YoaqRpQYym = true;}
      if(udYUcwxHWT == IcqahsjETq){bIpxJLtBGZ = true;}
      else if(IcqahsjETq == udYUcwxHWT){BSKaWyUQmc = true;}
      if(poUWsnByuE == EBydLmXoAf){SdaVliRBTZ = true;}
      else if(EBydLmXoAf == poUWsnByuE){RCXskTfxIG = true;}
      if(AtEAiJywoO == gMcTPqPyPq){filaCWfpCV = true;}
      if(GWWtbBKlIO == cGDSzdTBtN){FUdWNuEVdx = true;}
      if(HtxgaaDlSM == xhkGWZnVec){tPISkAVTRB = true;}
      while(gMcTPqPyPq == AtEAiJywoO){QlZnRoUfFn = true;}
      while(cGDSzdTBtN == cGDSzdTBtN){zBUDAiAxec = true;}
      while(xhkGWZnVec == xhkGWZnVec){rPZACVQgGx = true;}
      if(hnonZuzXLp == true){hnonZuzXLp = false;}
      if(ckncOxyeeg == true){ckncOxyeeg = false;}
      if(TVtmhzbVwo == true){TVtmhzbVwo = false;}
      if(DtTmIoROsD == true){DtTmIoROsD = false;}
      if(dwpEjLsHqZ == true){dwpEjLsHqZ = false;}
      if(bIpxJLtBGZ == true){bIpxJLtBGZ = false;}
      if(SdaVliRBTZ == true){SdaVliRBTZ = false;}
      if(filaCWfpCV == true){filaCWfpCV = false;}
      if(FUdWNuEVdx == true){FUdWNuEVdx = false;}
      if(tPISkAVTRB == true){tPISkAVTRB = false;}
      if(trmRsrVOul == true){trmRsrVOul = false;}
      if(fEzjTyzDIq == true){fEzjTyzDIq = false;}
      if(ewWWePZSpB == true){ewWWePZSpB = false;}
      if(BLXBbNgMdU == true){BLXBbNgMdU = false;}
      if(YoaqRpQYym == true){YoaqRpQYym = false;}
      if(BSKaWyUQmc == true){BSKaWyUQmc = false;}
      if(RCXskTfxIG == true){RCXskTfxIG = false;}
      if(QlZnRoUfFn == true){QlZnRoUfFn = false;}
      if(zBUDAiAxec == true){zBUDAiAxec = false;}
      if(rPZACVQgGx == true){rPZACVQgGx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GMAWXBOXCT
{ 
  void UkDowFaNZF()
  { 
      bool LjdggELWWQ = false;
      bool TNSTBVwMOw = false;
      bool asUreoLBzB = false;
      bool jbYhtbZDwL = false;
      bool nMIQcfuYip = false;
      bool mJYFqROlCr = false;
      bool rKWUgrokYY = false;
      bool wsQDHOkEOz = false;
      bool tmSJOZCSqc = false;
      bool MnAESdomjj = false;
      bool qKzJtsrVxb = false;
      bool fKWDxFrNGG = false;
      bool oVswLHrMkd = false;
      bool YxUeHjnIPU = false;
      bool hgUOwCRxGN = false;
      bool kbgcuUQDyl = false;
      bool AfkSDhoruN = false;
      bool RiykYIAezI = false;
      bool puFXsxQqil = false;
      bool TjJcTBuCLN = false;
      string oXdxUTrPZL;
      string CqjMEnUNWo;
      string MOHbbVFnSr;
      string RNiTfOuJKj;
      string jePGfbccFG;
      string IasKaaPCVy;
      string NEwhsoIQgo;
      string sKClFgyBuA;
      string schMjpUYrE;
      string zsnLWehgMq;
      string TLuPNxXGFt;
      string bNGVFkVjyD;
      string TiXbpzWqPZ;
      string yRnEfggRyl;
      string RNTybkmSGk;
      string JyhIWjmSZN;
      string ZgqewKYCoY;
      string DElLlGPZAF;
      string MEjdQAifgw;
      string sOrjMjWnBR;
      if(oXdxUTrPZL == TLuPNxXGFt){LjdggELWWQ = true;}
      else if(TLuPNxXGFt == oXdxUTrPZL){qKzJtsrVxb = true;}
      if(CqjMEnUNWo == bNGVFkVjyD){TNSTBVwMOw = true;}
      else if(bNGVFkVjyD == CqjMEnUNWo){fKWDxFrNGG = true;}
      if(MOHbbVFnSr == TiXbpzWqPZ){asUreoLBzB = true;}
      else if(TiXbpzWqPZ == MOHbbVFnSr){oVswLHrMkd = true;}
      if(RNiTfOuJKj == yRnEfggRyl){jbYhtbZDwL = true;}
      else if(yRnEfggRyl == RNiTfOuJKj){YxUeHjnIPU = true;}
      if(jePGfbccFG == RNTybkmSGk){nMIQcfuYip = true;}
      else if(RNTybkmSGk == jePGfbccFG){hgUOwCRxGN = true;}
      if(IasKaaPCVy == JyhIWjmSZN){mJYFqROlCr = true;}
      else if(JyhIWjmSZN == IasKaaPCVy){kbgcuUQDyl = true;}
      if(NEwhsoIQgo == ZgqewKYCoY){rKWUgrokYY = true;}
      else if(ZgqewKYCoY == NEwhsoIQgo){AfkSDhoruN = true;}
      if(sKClFgyBuA == DElLlGPZAF){wsQDHOkEOz = true;}
      if(schMjpUYrE == MEjdQAifgw){tmSJOZCSqc = true;}
      if(zsnLWehgMq == sOrjMjWnBR){MnAESdomjj = true;}
      while(DElLlGPZAF == sKClFgyBuA){RiykYIAezI = true;}
      while(MEjdQAifgw == MEjdQAifgw){puFXsxQqil = true;}
      while(sOrjMjWnBR == sOrjMjWnBR){TjJcTBuCLN = true;}
      if(LjdggELWWQ == true){LjdggELWWQ = false;}
      if(TNSTBVwMOw == true){TNSTBVwMOw = false;}
      if(asUreoLBzB == true){asUreoLBzB = false;}
      if(jbYhtbZDwL == true){jbYhtbZDwL = false;}
      if(nMIQcfuYip == true){nMIQcfuYip = false;}
      if(mJYFqROlCr == true){mJYFqROlCr = false;}
      if(rKWUgrokYY == true){rKWUgrokYY = false;}
      if(wsQDHOkEOz == true){wsQDHOkEOz = false;}
      if(tmSJOZCSqc == true){tmSJOZCSqc = false;}
      if(MnAESdomjj == true){MnAESdomjj = false;}
      if(qKzJtsrVxb == true){qKzJtsrVxb = false;}
      if(fKWDxFrNGG == true){fKWDxFrNGG = false;}
      if(oVswLHrMkd == true){oVswLHrMkd = false;}
      if(YxUeHjnIPU == true){YxUeHjnIPU = false;}
      if(hgUOwCRxGN == true){hgUOwCRxGN = false;}
      if(kbgcuUQDyl == true){kbgcuUQDyl = false;}
      if(AfkSDhoruN == true){AfkSDhoruN = false;}
      if(RiykYIAezI == true){RiykYIAezI = false;}
      if(puFXsxQqil == true){puFXsxQqil = false;}
      if(TjJcTBuCLN == true){TjJcTBuCLN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWKQACNVTA
{ 
  void gUdBpaqquX()
  { 
      bool iZEbRVLdHf = false;
      bool wtktIMBMYg = false;
      bool SOpYNqxDVW = false;
      bool ajFbHxAabP = false;
      bool IJYlZkaGau = false;
      bool EzZsfTjfOZ = false;
      bool XIIkELoImL = false;
      bool LZjJXJpEzc = false;
      bool QqcZSbJMwm = false;
      bool NULBqAAngN = false;
      bool wSTOidOQUV = false;
      bool dfglJgehSc = false;
      bool CcLzxqOhRX = false;
      bool ICWkfxWNpn = false;
      bool MrqZJhnZrJ = false;
      bool VSUDKSGTQr = false;
      bool PgyxNaIuFL = false;
      bool JQqdQJllpP = false;
      bool CnoHCogTZN = false;
      bool qDwxYessMi = false;
      string UhWiOtibVl;
      string NJqAzJSFEm;
      string cOiVMZzHWV;
      string LVsnMnbRKq;
      string eHJwOnlgQU;
      string YYhVqFyAVn;
      string taFzZqPDnK;
      string hBuMHVEmHY;
      string nRqCwmmWwG;
      string pawVxDCKWW;
      string XhsFlWcVNU;
      string ALswAbjCCl;
      string ErHgUGFYPE;
      string TtQjBGXkPZ;
      string JRIaFdhzVU;
      string TzHjSeaMkf;
      string REGJBGuIts;
      string Dymcblifbp;
      string XFDtkUmfRV;
      string fLAiHFLzZz;
      if(UhWiOtibVl == XhsFlWcVNU){iZEbRVLdHf = true;}
      else if(XhsFlWcVNU == UhWiOtibVl){wSTOidOQUV = true;}
      if(NJqAzJSFEm == ALswAbjCCl){wtktIMBMYg = true;}
      else if(ALswAbjCCl == NJqAzJSFEm){dfglJgehSc = true;}
      if(cOiVMZzHWV == ErHgUGFYPE){SOpYNqxDVW = true;}
      else if(ErHgUGFYPE == cOiVMZzHWV){CcLzxqOhRX = true;}
      if(LVsnMnbRKq == TtQjBGXkPZ){ajFbHxAabP = true;}
      else if(TtQjBGXkPZ == LVsnMnbRKq){ICWkfxWNpn = true;}
      if(eHJwOnlgQU == JRIaFdhzVU){IJYlZkaGau = true;}
      else if(JRIaFdhzVU == eHJwOnlgQU){MrqZJhnZrJ = true;}
      if(YYhVqFyAVn == TzHjSeaMkf){EzZsfTjfOZ = true;}
      else if(TzHjSeaMkf == YYhVqFyAVn){VSUDKSGTQr = true;}
      if(taFzZqPDnK == REGJBGuIts){XIIkELoImL = true;}
      else if(REGJBGuIts == taFzZqPDnK){PgyxNaIuFL = true;}
      if(hBuMHVEmHY == Dymcblifbp){LZjJXJpEzc = true;}
      if(nRqCwmmWwG == XFDtkUmfRV){QqcZSbJMwm = true;}
      if(pawVxDCKWW == fLAiHFLzZz){NULBqAAngN = true;}
      while(Dymcblifbp == hBuMHVEmHY){JQqdQJllpP = true;}
      while(XFDtkUmfRV == XFDtkUmfRV){CnoHCogTZN = true;}
      while(fLAiHFLzZz == fLAiHFLzZz){qDwxYessMi = true;}
      if(iZEbRVLdHf == true){iZEbRVLdHf = false;}
      if(wtktIMBMYg == true){wtktIMBMYg = false;}
      if(SOpYNqxDVW == true){SOpYNqxDVW = false;}
      if(ajFbHxAabP == true){ajFbHxAabP = false;}
      if(IJYlZkaGau == true){IJYlZkaGau = false;}
      if(EzZsfTjfOZ == true){EzZsfTjfOZ = false;}
      if(XIIkELoImL == true){XIIkELoImL = false;}
      if(LZjJXJpEzc == true){LZjJXJpEzc = false;}
      if(QqcZSbJMwm == true){QqcZSbJMwm = false;}
      if(NULBqAAngN == true){NULBqAAngN = false;}
      if(wSTOidOQUV == true){wSTOidOQUV = false;}
      if(dfglJgehSc == true){dfglJgehSc = false;}
      if(CcLzxqOhRX == true){CcLzxqOhRX = false;}
      if(ICWkfxWNpn == true){ICWkfxWNpn = false;}
      if(MrqZJhnZrJ == true){MrqZJhnZrJ = false;}
      if(VSUDKSGTQr == true){VSUDKSGTQr = false;}
      if(PgyxNaIuFL == true){PgyxNaIuFL = false;}
      if(JQqdQJllpP == true){JQqdQJllpP = false;}
      if(CnoHCogTZN == true){CnoHCogTZN = false;}
      if(qDwxYessMi == true){qDwxYessMi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XDBNANSDHG
{ 
  void VJIuTCeuUl()
  { 
      bool qKyHcSjUzF = false;
      bool ooccfFqYfw = false;
      bool VUCQaYVoxL = false;
      bool PQkRTyYFPR = false;
      bool esQUjXoLqq = false;
      bool QxQQSWHhfE = false;
      bool xuWmpYDLIg = false;
      bool glJNRbDhfD = false;
      bool iJxFtSAUyw = false;
      bool qpYKTjWceL = false;
      bool TdCKKemCzq = false;
      bool SZBcUmxQsX = false;
      bool XiNLppMysh = false;
      bool FZDUjFHmuP = false;
      bool exUHdRowpg = false;
      bool lFjGmjPpTU = false;
      bool SnIQkrVgsP = false;
      bool fKVcraNGhY = false;
      bool BPIMwzpwgz = false;
      bool oQSZxqoEVl = false;
      string OBkZKSIoRs;
      string fSegrzEnNh;
      string bltCADCSRd;
      string kiAGOFShrh;
      string EsXJQumiOS;
      string NJNIHbGhYG;
      string PpXmIxSYSm;
      string gWufchOklF;
      string QTDyQaVrzl;
      string yjJlROVkAT;
      string cOQblpNgeY;
      string NVwTpwlYVg;
      string aZZfnxNJON;
      string McjScBDbMa;
      string NoMZYcnouV;
      string cxPTrCojmo;
      string cERQMjkcqn;
      string rJMuTlMzGK;
      string JXNrkPNQaZ;
      string MSnWxIWwNo;
      if(OBkZKSIoRs == cOQblpNgeY){qKyHcSjUzF = true;}
      else if(cOQblpNgeY == OBkZKSIoRs){TdCKKemCzq = true;}
      if(fSegrzEnNh == NVwTpwlYVg){ooccfFqYfw = true;}
      else if(NVwTpwlYVg == fSegrzEnNh){SZBcUmxQsX = true;}
      if(bltCADCSRd == aZZfnxNJON){VUCQaYVoxL = true;}
      else if(aZZfnxNJON == bltCADCSRd){XiNLppMysh = true;}
      if(kiAGOFShrh == McjScBDbMa){PQkRTyYFPR = true;}
      else if(McjScBDbMa == kiAGOFShrh){FZDUjFHmuP = true;}
      if(EsXJQumiOS == NoMZYcnouV){esQUjXoLqq = true;}
      else if(NoMZYcnouV == EsXJQumiOS){exUHdRowpg = true;}
      if(NJNIHbGhYG == cxPTrCojmo){QxQQSWHhfE = true;}
      else if(cxPTrCojmo == NJNIHbGhYG){lFjGmjPpTU = true;}
      if(PpXmIxSYSm == cERQMjkcqn){xuWmpYDLIg = true;}
      else if(cERQMjkcqn == PpXmIxSYSm){SnIQkrVgsP = true;}
      if(gWufchOklF == rJMuTlMzGK){glJNRbDhfD = true;}
      if(QTDyQaVrzl == JXNrkPNQaZ){iJxFtSAUyw = true;}
      if(yjJlROVkAT == MSnWxIWwNo){qpYKTjWceL = true;}
      while(rJMuTlMzGK == gWufchOklF){fKVcraNGhY = true;}
      while(JXNrkPNQaZ == JXNrkPNQaZ){BPIMwzpwgz = true;}
      while(MSnWxIWwNo == MSnWxIWwNo){oQSZxqoEVl = true;}
      if(qKyHcSjUzF == true){qKyHcSjUzF = false;}
      if(ooccfFqYfw == true){ooccfFqYfw = false;}
      if(VUCQaYVoxL == true){VUCQaYVoxL = false;}
      if(PQkRTyYFPR == true){PQkRTyYFPR = false;}
      if(esQUjXoLqq == true){esQUjXoLqq = false;}
      if(QxQQSWHhfE == true){QxQQSWHhfE = false;}
      if(xuWmpYDLIg == true){xuWmpYDLIg = false;}
      if(glJNRbDhfD == true){glJNRbDhfD = false;}
      if(iJxFtSAUyw == true){iJxFtSAUyw = false;}
      if(qpYKTjWceL == true){qpYKTjWceL = false;}
      if(TdCKKemCzq == true){TdCKKemCzq = false;}
      if(SZBcUmxQsX == true){SZBcUmxQsX = false;}
      if(XiNLppMysh == true){XiNLppMysh = false;}
      if(FZDUjFHmuP == true){FZDUjFHmuP = false;}
      if(exUHdRowpg == true){exUHdRowpg = false;}
      if(lFjGmjPpTU == true){lFjGmjPpTU = false;}
      if(SnIQkrVgsP == true){SnIQkrVgsP = false;}
      if(fKVcraNGhY == true){fKVcraNGhY = false;}
      if(BPIMwzpwgz == true){BPIMwzpwgz = false;}
      if(oQSZxqoEVl == true){oQSZxqoEVl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZHSWGGUQEB
{ 
  void BWbFhtIxgf()
  { 
      bool QusEkAjftO = false;
      bool MgyEsnhoFc = false;
      bool wXkqXZLOtE = false;
      bool mNIwymRVAW = false;
      bool JMyLShNuVf = false;
      bool FGXBbrJBgK = false;
      bool oUkpbyXCFF = false;
      bool WMoiTjZZYo = false;
      bool LQsOzgoHTF = false;
      bool dPnohnaIjT = false;
      bool JLoQIsQohr = false;
      bool SjcqyYbWpu = false;
      bool IQhAbGXzAf = false;
      bool IRoEeAacFG = false;
      bool PAZblsmwpJ = false;
      bool LERoKsconB = false;
      bool URnBjBuXMy = false;
      bool xzQjeIqGNh = false;
      bool TaIqTDzAsl = false;
      bool WlnEkyMXrk = false;
      string aKHHETwotC;
      string LifVTnLXxe;
      string GbCtOhQgLQ;
      string mwLGrnFPmu;
      string ENIrSakgwB;
      string WNmoXzHMsV;
      string DOdcPOWYce;
      string iwjCZrTJbm;
      string xjjJtZIWhs;
      string grVQrpiecD;
      string DLDRSZckOf;
      string eykFYTdUio;
      string GApiypaTJj;
      string IogXikfSpT;
      string xWICOhHPrX;
      string LOumxDVTTb;
      string zJadWpRMWm;
      string mKdPriqnUP;
      string iKalXtssae;
      string PMzOUnudeY;
      if(aKHHETwotC == DLDRSZckOf){QusEkAjftO = true;}
      else if(DLDRSZckOf == aKHHETwotC){JLoQIsQohr = true;}
      if(LifVTnLXxe == eykFYTdUio){MgyEsnhoFc = true;}
      else if(eykFYTdUio == LifVTnLXxe){SjcqyYbWpu = true;}
      if(GbCtOhQgLQ == GApiypaTJj){wXkqXZLOtE = true;}
      else if(GApiypaTJj == GbCtOhQgLQ){IQhAbGXzAf = true;}
      if(mwLGrnFPmu == IogXikfSpT){mNIwymRVAW = true;}
      else if(IogXikfSpT == mwLGrnFPmu){IRoEeAacFG = true;}
      if(ENIrSakgwB == xWICOhHPrX){JMyLShNuVf = true;}
      else if(xWICOhHPrX == ENIrSakgwB){PAZblsmwpJ = true;}
      if(WNmoXzHMsV == LOumxDVTTb){FGXBbrJBgK = true;}
      else if(LOumxDVTTb == WNmoXzHMsV){LERoKsconB = true;}
      if(DOdcPOWYce == zJadWpRMWm){oUkpbyXCFF = true;}
      else if(zJadWpRMWm == DOdcPOWYce){URnBjBuXMy = true;}
      if(iwjCZrTJbm == mKdPriqnUP){WMoiTjZZYo = true;}
      if(xjjJtZIWhs == iKalXtssae){LQsOzgoHTF = true;}
      if(grVQrpiecD == PMzOUnudeY){dPnohnaIjT = true;}
      while(mKdPriqnUP == iwjCZrTJbm){xzQjeIqGNh = true;}
      while(iKalXtssae == iKalXtssae){TaIqTDzAsl = true;}
      while(PMzOUnudeY == PMzOUnudeY){WlnEkyMXrk = true;}
      if(QusEkAjftO == true){QusEkAjftO = false;}
      if(MgyEsnhoFc == true){MgyEsnhoFc = false;}
      if(wXkqXZLOtE == true){wXkqXZLOtE = false;}
      if(mNIwymRVAW == true){mNIwymRVAW = false;}
      if(JMyLShNuVf == true){JMyLShNuVf = false;}
      if(FGXBbrJBgK == true){FGXBbrJBgK = false;}
      if(oUkpbyXCFF == true){oUkpbyXCFF = false;}
      if(WMoiTjZZYo == true){WMoiTjZZYo = false;}
      if(LQsOzgoHTF == true){LQsOzgoHTF = false;}
      if(dPnohnaIjT == true){dPnohnaIjT = false;}
      if(JLoQIsQohr == true){JLoQIsQohr = false;}
      if(SjcqyYbWpu == true){SjcqyYbWpu = false;}
      if(IQhAbGXzAf == true){IQhAbGXzAf = false;}
      if(IRoEeAacFG == true){IRoEeAacFG = false;}
      if(PAZblsmwpJ == true){PAZblsmwpJ = false;}
      if(LERoKsconB == true){LERoKsconB = false;}
      if(URnBjBuXMy == true){URnBjBuXMy = false;}
      if(xzQjeIqGNh == true){xzQjeIqGNh = false;}
      if(TaIqTDzAsl == true){TaIqTDzAsl = false;}
      if(WlnEkyMXrk == true){WlnEkyMXrk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DCEBCOVBVI
{ 
  void CyJEqYLVXI()
  { 
      bool RsHtqGymZM = false;
      bool ErUlmGbLPX = false;
      bool WmBgEbOcQg = false;
      bool EPEKoStryk = false;
      bool gCZYZQWkyo = false;
      bool SJqBXdrZoP = false;
      bool rUWrIomKwT = false;
      bool MiMdpUMbHn = false;
      bool EcdbOuYDlK = false;
      bool aTChsMegQk = false;
      bool dMnebjwMKC = false;
      bool RPSBLOqtdM = false;
      bool PjYlrsfdjd = false;
      bool ofLVKrnzze = false;
      bool zLrisKBBWd = false;
      bool VkCDUsmCli = false;
      bool DSbgMkEwqT = false;
      bool ZqtzNEqorh = false;
      bool qeHFIEcHBQ = false;
      bool ElMQafiLWH = false;
      string ZOgMSNGqTm;
      string FWJleAkEyA;
      string zSiNYQRgLV;
      string fiecPYNaEu;
      string UrNtFEJKKg;
      string mLHXDGeTmB;
      string uYeyGWrfWF;
      string mJzCfGEoHT;
      string HHVehUaGZJ;
      string tsmCzuNPmi;
      string McnFsdLErx;
      string BoMTsnCAPk;
      string wkGMLsVwCj;
      string soCYGeTQkD;
      string JWOcHEgTJL;
      string rMzClbVasz;
      string IOBHDMmmMO;
      string TlOMbYWdFG;
      string MBmprfoAle;
      string JrXlutUGYu;
      if(ZOgMSNGqTm == McnFsdLErx){RsHtqGymZM = true;}
      else if(McnFsdLErx == ZOgMSNGqTm){dMnebjwMKC = true;}
      if(FWJleAkEyA == BoMTsnCAPk){ErUlmGbLPX = true;}
      else if(BoMTsnCAPk == FWJleAkEyA){RPSBLOqtdM = true;}
      if(zSiNYQRgLV == wkGMLsVwCj){WmBgEbOcQg = true;}
      else if(wkGMLsVwCj == zSiNYQRgLV){PjYlrsfdjd = true;}
      if(fiecPYNaEu == soCYGeTQkD){EPEKoStryk = true;}
      else if(soCYGeTQkD == fiecPYNaEu){ofLVKrnzze = true;}
      if(UrNtFEJKKg == JWOcHEgTJL){gCZYZQWkyo = true;}
      else if(JWOcHEgTJL == UrNtFEJKKg){zLrisKBBWd = true;}
      if(mLHXDGeTmB == rMzClbVasz){SJqBXdrZoP = true;}
      else if(rMzClbVasz == mLHXDGeTmB){VkCDUsmCli = true;}
      if(uYeyGWrfWF == IOBHDMmmMO){rUWrIomKwT = true;}
      else if(IOBHDMmmMO == uYeyGWrfWF){DSbgMkEwqT = true;}
      if(mJzCfGEoHT == TlOMbYWdFG){MiMdpUMbHn = true;}
      if(HHVehUaGZJ == MBmprfoAle){EcdbOuYDlK = true;}
      if(tsmCzuNPmi == JrXlutUGYu){aTChsMegQk = true;}
      while(TlOMbYWdFG == mJzCfGEoHT){ZqtzNEqorh = true;}
      while(MBmprfoAle == MBmprfoAle){qeHFIEcHBQ = true;}
      while(JrXlutUGYu == JrXlutUGYu){ElMQafiLWH = true;}
      if(RsHtqGymZM == true){RsHtqGymZM = false;}
      if(ErUlmGbLPX == true){ErUlmGbLPX = false;}
      if(WmBgEbOcQg == true){WmBgEbOcQg = false;}
      if(EPEKoStryk == true){EPEKoStryk = false;}
      if(gCZYZQWkyo == true){gCZYZQWkyo = false;}
      if(SJqBXdrZoP == true){SJqBXdrZoP = false;}
      if(rUWrIomKwT == true){rUWrIomKwT = false;}
      if(MiMdpUMbHn == true){MiMdpUMbHn = false;}
      if(EcdbOuYDlK == true){EcdbOuYDlK = false;}
      if(aTChsMegQk == true){aTChsMegQk = false;}
      if(dMnebjwMKC == true){dMnebjwMKC = false;}
      if(RPSBLOqtdM == true){RPSBLOqtdM = false;}
      if(PjYlrsfdjd == true){PjYlrsfdjd = false;}
      if(ofLVKrnzze == true){ofLVKrnzze = false;}
      if(zLrisKBBWd == true){zLrisKBBWd = false;}
      if(VkCDUsmCli == true){VkCDUsmCli = false;}
      if(DSbgMkEwqT == true){DSbgMkEwqT = false;}
      if(ZqtzNEqorh == true){ZqtzNEqorh = false;}
      if(qeHFIEcHBQ == true){qeHFIEcHBQ = false;}
      if(ElMQafiLWH == true){ElMQafiLWH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIRGCDGVGA
{ 
  void znkCzynIIV()
  { 
      bool NHUMVEwhig = false;
      bool eunmfyPQti = false;
      bool sqAatuCaYN = false;
      bool BofhNZllKm = false;
      bool dSObnAdczP = false;
      bool tHznXVGtRZ = false;
      bool BUJUfoOGZG = false;
      bool McFHEacYlt = false;
      bool RZbITsprJq = false;
      bool SrUjkJIsuz = false;
      bool kWCrDRCqix = false;
      bool rhHWIbrABm = false;
      bool yWxhmTIUVu = false;
      bool RjcmItWiFC = false;
      bool pzILzkkxaJ = false;
      bool QIqIBNZTFi = false;
      bool JhUmeIEUOO = false;
      bool EItzwzOkiC = false;
      bool iKsMeJrUkt = false;
      bool TCdVsIdUgq = false;
      string qSscbbLIqm;
      string AOnenWrrEW;
      string mdJAoNyrEm;
      string xUQkpJheBi;
      string mHfwhbkpVA;
      string pGjjSNJrnN;
      string dSEEofxCod;
      string nNpVifxNSM;
      string cIVExpjgSc;
      string zpqnFTCbGC;
      string ehBrLcQOAl;
      string PwZbkUxzHy;
      string uQjMdyWBQO;
      string cVGPgtHdsT;
      string ZVffMDQOCj;
      string WCUIGOynNN;
      string FOxlJtpJtp;
      string NSGmYZjDAa;
      string gHzgqZAyIS;
      string uSPeNKYtWR;
      if(qSscbbLIqm == ehBrLcQOAl){NHUMVEwhig = true;}
      else if(ehBrLcQOAl == qSscbbLIqm){kWCrDRCqix = true;}
      if(AOnenWrrEW == PwZbkUxzHy){eunmfyPQti = true;}
      else if(PwZbkUxzHy == AOnenWrrEW){rhHWIbrABm = true;}
      if(mdJAoNyrEm == uQjMdyWBQO){sqAatuCaYN = true;}
      else if(uQjMdyWBQO == mdJAoNyrEm){yWxhmTIUVu = true;}
      if(xUQkpJheBi == cVGPgtHdsT){BofhNZllKm = true;}
      else if(cVGPgtHdsT == xUQkpJheBi){RjcmItWiFC = true;}
      if(mHfwhbkpVA == ZVffMDQOCj){dSObnAdczP = true;}
      else if(ZVffMDQOCj == mHfwhbkpVA){pzILzkkxaJ = true;}
      if(pGjjSNJrnN == WCUIGOynNN){tHznXVGtRZ = true;}
      else if(WCUIGOynNN == pGjjSNJrnN){QIqIBNZTFi = true;}
      if(dSEEofxCod == FOxlJtpJtp){BUJUfoOGZG = true;}
      else if(FOxlJtpJtp == dSEEofxCod){JhUmeIEUOO = true;}
      if(nNpVifxNSM == NSGmYZjDAa){McFHEacYlt = true;}
      if(cIVExpjgSc == gHzgqZAyIS){RZbITsprJq = true;}
      if(zpqnFTCbGC == uSPeNKYtWR){SrUjkJIsuz = true;}
      while(NSGmYZjDAa == nNpVifxNSM){EItzwzOkiC = true;}
      while(gHzgqZAyIS == gHzgqZAyIS){iKsMeJrUkt = true;}
      while(uSPeNKYtWR == uSPeNKYtWR){TCdVsIdUgq = true;}
      if(NHUMVEwhig == true){NHUMVEwhig = false;}
      if(eunmfyPQti == true){eunmfyPQti = false;}
      if(sqAatuCaYN == true){sqAatuCaYN = false;}
      if(BofhNZllKm == true){BofhNZllKm = false;}
      if(dSObnAdczP == true){dSObnAdczP = false;}
      if(tHznXVGtRZ == true){tHznXVGtRZ = false;}
      if(BUJUfoOGZG == true){BUJUfoOGZG = false;}
      if(McFHEacYlt == true){McFHEacYlt = false;}
      if(RZbITsprJq == true){RZbITsprJq = false;}
      if(SrUjkJIsuz == true){SrUjkJIsuz = false;}
      if(kWCrDRCqix == true){kWCrDRCqix = false;}
      if(rhHWIbrABm == true){rhHWIbrABm = false;}
      if(yWxhmTIUVu == true){yWxhmTIUVu = false;}
      if(RjcmItWiFC == true){RjcmItWiFC = false;}
      if(pzILzkkxaJ == true){pzILzkkxaJ = false;}
      if(QIqIBNZTFi == true){QIqIBNZTFi = false;}
      if(JhUmeIEUOO == true){JhUmeIEUOO = false;}
      if(EItzwzOkiC == true){EItzwzOkiC = false;}
      if(iKsMeJrUkt == true){iKsMeJrUkt = false;}
      if(TCdVsIdUgq == true){TCdVsIdUgq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SDMTTNEGZE
{ 
  void sJFzTXLQGN()
  { 
      bool oNHttwsurz = false;
      bool HJskUjneRN = false;
      bool NmAgtkiVjT = false;
      bool LMPweBlmKq = false;
      bool VNqFyLNsBS = false;
      bool dydsABMazI = false;
      bool MXLYnusxGS = false;
      bool xBTarAwuhi = false;
      bool WoTQoMiWuc = false;
      bool oLmCdxCSRC = false;
      bool RQmiVbdCBA = false;
      bool ERrPkWEtia = false;
      bool MWBcdkNRwt = false;
      bool xddeRGCkuM = false;
      bool ifUuXXTWQH = false;
      bool sIiqptPKFk = false;
      bool OLFGDamMye = false;
      bool USyWqfBGEF = false;
      bool QpAoAoumoW = false;
      bool prfKyWZNrx = false;
      string iuGtJoCYhB;
      string waFTWEHxwi;
      string zVtVlCUhyN;
      string bCMhQwCNgM;
      string cMYcknMFMW;
      string MbLIRNAjIG;
      string UTaUZsNXCa;
      string CtQiGmwQkx;
      string pPVbAzpDPD;
      string uSFZqIkDDq;
      string anDkTSLbCe;
      string QizKQEyzUZ;
      string DJHyfiopqx;
      string BrMsWBMjHg;
      string nNBkmLTtJm;
      string KlidnQfEFk;
      string dUjFcXWFmP;
      string rOrmloIWLT;
      string PtgEmPJiEG;
      string UHeWDSdwHO;
      if(iuGtJoCYhB == anDkTSLbCe){oNHttwsurz = true;}
      else if(anDkTSLbCe == iuGtJoCYhB){RQmiVbdCBA = true;}
      if(waFTWEHxwi == QizKQEyzUZ){HJskUjneRN = true;}
      else if(QizKQEyzUZ == waFTWEHxwi){ERrPkWEtia = true;}
      if(zVtVlCUhyN == DJHyfiopqx){NmAgtkiVjT = true;}
      else if(DJHyfiopqx == zVtVlCUhyN){MWBcdkNRwt = true;}
      if(bCMhQwCNgM == BrMsWBMjHg){LMPweBlmKq = true;}
      else if(BrMsWBMjHg == bCMhQwCNgM){xddeRGCkuM = true;}
      if(cMYcknMFMW == nNBkmLTtJm){VNqFyLNsBS = true;}
      else if(nNBkmLTtJm == cMYcknMFMW){ifUuXXTWQH = true;}
      if(MbLIRNAjIG == KlidnQfEFk){dydsABMazI = true;}
      else if(KlidnQfEFk == MbLIRNAjIG){sIiqptPKFk = true;}
      if(UTaUZsNXCa == dUjFcXWFmP){MXLYnusxGS = true;}
      else if(dUjFcXWFmP == UTaUZsNXCa){OLFGDamMye = true;}
      if(CtQiGmwQkx == rOrmloIWLT){xBTarAwuhi = true;}
      if(pPVbAzpDPD == PtgEmPJiEG){WoTQoMiWuc = true;}
      if(uSFZqIkDDq == UHeWDSdwHO){oLmCdxCSRC = true;}
      while(rOrmloIWLT == CtQiGmwQkx){USyWqfBGEF = true;}
      while(PtgEmPJiEG == PtgEmPJiEG){QpAoAoumoW = true;}
      while(UHeWDSdwHO == UHeWDSdwHO){prfKyWZNrx = true;}
      if(oNHttwsurz == true){oNHttwsurz = false;}
      if(HJskUjneRN == true){HJskUjneRN = false;}
      if(NmAgtkiVjT == true){NmAgtkiVjT = false;}
      if(LMPweBlmKq == true){LMPweBlmKq = false;}
      if(VNqFyLNsBS == true){VNqFyLNsBS = false;}
      if(dydsABMazI == true){dydsABMazI = false;}
      if(MXLYnusxGS == true){MXLYnusxGS = false;}
      if(xBTarAwuhi == true){xBTarAwuhi = false;}
      if(WoTQoMiWuc == true){WoTQoMiWuc = false;}
      if(oLmCdxCSRC == true){oLmCdxCSRC = false;}
      if(RQmiVbdCBA == true){RQmiVbdCBA = false;}
      if(ERrPkWEtia == true){ERrPkWEtia = false;}
      if(MWBcdkNRwt == true){MWBcdkNRwt = false;}
      if(xddeRGCkuM == true){xddeRGCkuM = false;}
      if(ifUuXXTWQH == true){ifUuXXTWQH = false;}
      if(sIiqptPKFk == true){sIiqptPKFk = false;}
      if(OLFGDamMye == true){OLFGDamMye = false;}
      if(USyWqfBGEF == true){USyWqfBGEF = false;}
      if(QpAoAoumoW == true){QpAoAoumoW = false;}
      if(prfKyWZNrx == true){prfKyWZNrx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HDPPBBEDLK
{ 
  void TWmrFKySWS()
  { 
      bool herqrOyMDd = false;
      bool JUJZdnDHRK = false;
      bool GZPFiIfKVG = false;
      bool FcKrJztXNu = false;
      bool XszoFUeMQE = false;
      bool zCMXZIPmIj = false;
      bool hmqxXfJQPd = false;
      bool sesWlNZZzO = false;
      bool cSsQGDQmSB = false;
      bool jHPcMjCCRY = false;
      bool KNxlKUIokM = false;
      bool homtGPtZqU = false;
      bool PWyOtlPQJC = false;
      bool KXIZDPVGGl = false;
      bool uaBFStTUWx = false;
      bool pbLwJnPhrX = false;
      bool ErfiBKgNqq = false;
      bool smSEZoUsuz = false;
      bool StsMLhMLQO = false;
      bool zmOhgDuSDH = false;
      string XDZmQpChbq;
      string JVnoQDxNMz;
      string PjAlYSrEQt;
      string qrkMdIyepH;
      string DcrruOwPdJ;
      string wWNNrmCmNy;
      string xyQgzQjbKI;
      string FSXFwlrIqK;
      string WcZHyUeWUp;
      string FKQqJFMKre;
      string dUEUDdzIRF;
      string utwCaUXJie;
      string lMHUDtBfup;
      string YhQMgCXEDU;
      string VWFOtLOOQo;
      string gDaMrQMjRJ;
      string bSNafNciVY;
      string wSFOJOHrZr;
      string emPFJVGDTP;
      string onmtrCJdhg;
      if(XDZmQpChbq == dUEUDdzIRF){herqrOyMDd = true;}
      else if(dUEUDdzIRF == XDZmQpChbq){KNxlKUIokM = true;}
      if(JVnoQDxNMz == utwCaUXJie){JUJZdnDHRK = true;}
      else if(utwCaUXJie == JVnoQDxNMz){homtGPtZqU = true;}
      if(PjAlYSrEQt == lMHUDtBfup){GZPFiIfKVG = true;}
      else if(lMHUDtBfup == PjAlYSrEQt){PWyOtlPQJC = true;}
      if(qrkMdIyepH == YhQMgCXEDU){FcKrJztXNu = true;}
      else if(YhQMgCXEDU == qrkMdIyepH){KXIZDPVGGl = true;}
      if(DcrruOwPdJ == VWFOtLOOQo){XszoFUeMQE = true;}
      else if(VWFOtLOOQo == DcrruOwPdJ){uaBFStTUWx = true;}
      if(wWNNrmCmNy == gDaMrQMjRJ){zCMXZIPmIj = true;}
      else if(gDaMrQMjRJ == wWNNrmCmNy){pbLwJnPhrX = true;}
      if(xyQgzQjbKI == bSNafNciVY){hmqxXfJQPd = true;}
      else if(bSNafNciVY == xyQgzQjbKI){ErfiBKgNqq = true;}
      if(FSXFwlrIqK == wSFOJOHrZr){sesWlNZZzO = true;}
      if(WcZHyUeWUp == emPFJVGDTP){cSsQGDQmSB = true;}
      if(FKQqJFMKre == onmtrCJdhg){jHPcMjCCRY = true;}
      while(wSFOJOHrZr == FSXFwlrIqK){smSEZoUsuz = true;}
      while(emPFJVGDTP == emPFJVGDTP){StsMLhMLQO = true;}
      while(onmtrCJdhg == onmtrCJdhg){zmOhgDuSDH = true;}
      if(herqrOyMDd == true){herqrOyMDd = false;}
      if(JUJZdnDHRK == true){JUJZdnDHRK = false;}
      if(GZPFiIfKVG == true){GZPFiIfKVG = false;}
      if(FcKrJztXNu == true){FcKrJztXNu = false;}
      if(XszoFUeMQE == true){XszoFUeMQE = false;}
      if(zCMXZIPmIj == true){zCMXZIPmIj = false;}
      if(hmqxXfJQPd == true){hmqxXfJQPd = false;}
      if(sesWlNZZzO == true){sesWlNZZzO = false;}
      if(cSsQGDQmSB == true){cSsQGDQmSB = false;}
      if(jHPcMjCCRY == true){jHPcMjCCRY = false;}
      if(KNxlKUIokM == true){KNxlKUIokM = false;}
      if(homtGPtZqU == true){homtGPtZqU = false;}
      if(PWyOtlPQJC == true){PWyOtlPQJC = false;}
      if(KXIZDPVGGl == true){KXIZDPVGGl = false;}
      if(uaBFStTUWx == true){uaBFStTUWx = false;}
      if(pbLwJnPhrX == true){pbLwJnPhrX = false;}
      if(ErfiBKgNqq == true){ErfiBKgNqq = false;}
      if(smSEZoUsuz == true){smSEZoUsuz = false;}
      if(StsMLhMLQO == true){StsMLhMLQO = false;}
      if(zmOhgDuSDH == true){zmOhgDuSDH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXLCITZTDB
{ 
  void tJKUwLSclY()
  { 
      bool ACBjkFhyCN = false;
      bool BxZuylMKcj = false;
      bool eqpHbiDpdp = false;
      bool obsRtzAmrj = false;
      bool BLSOqsWtoT = false;
      bool XswzOJLtIC = false;
      bool BqTLYZEIBz = false;
      bool lZSrhTXaPh = false;
      bool LJAJSwesCj = false;
      bool mFdoiJqGpR = false;
      bool nNsphyaDQu = false;
      bool kkdZqqpJsb = false;
      bool tLFQLfucJY = false;
      bool bRjytxQKbT = false;
      bool VbcHzCaDyq = false;
      bool ShNNWcHbdB = false;
      bool DxtrSTAffs = false;
      bool afhZGShyRJ = false;
      bool EqeRFtDWaQ = false;
      bool onfZQXgkne = false;
      string ePTSVxMEwc;
      string CJAbsDkBrl;
      string gmckeRPJbe;
      string BnRFLLHjoO;
      string ZGfCHnyyfR;
      string rVMRoqlhmD;
      string hDbRaNrtPg;
      string uBMcLZHadq;
      string TRdJlebzQT;
      string YYxlgWeOas;
      string uDhyVqJiGO;
      string iLDuiPYRew;
      string lsdwHWDZun;
      string uszkuQifmt;
      string UrrBjMUBCR;
      string yMidHCZlpz;
      string njnSSpMSAS;
      string fsdjbsBbLu;
      string BBWcoiKUcs;
      string qxonGkDYit;
      if(ePTSVxMEwc == uDhyVqJiGO){ACBjkFhyCN = true;}
      else if(uDhyVqJiGO == ePTSVxMEwc){nNsphyaDQu = true;}
      if(CJAbsDkBrl == iLDuiPYRew){BxZuylMKcj = true;}
      else if(iLDuiPYRew == CJAbsDkBrl){kkdZqqpJsb = true;}
      if(gmckeRPJbe == lsdwHWDZun){eqpHbiDpdp = true;}
      else if(lsdwHWDZun == gmckeRPJbe){tLFQLfucJY = true;}
      if(BnRFLLHjoO == uszkuQifmt){obsRtzAmrj = true;}
      else if(uszkuQifmt == BnRFLLHjoO){bRjytxQKbT = true;}
      if(ZGfCHnyyfR == UrrBjMUBCR){BLSOqsWtoT = true;}
      else if(UrrBjMUBCR == ZGfCHnyyfR){VbcHzCaDyq = true;}
      if(rVMRoqlhmD == yMidHCZlpz){XswzOJLtIC = true;}
      else if(yMidHCZlpz == rVMRoqlhmD){ShNNWcHbdB = true;}
      if(hDbRaNrtPg == njnSSpMSAS){BqTLYZEIBz = true;}
      else if(njnSSpMSAS == hDbRaNrtPg){DxtrSTAffs = true;}
      if(uBMcLZHadq == fsdjbsBbLu){lZSrhTXaPh = true;}
      if(TRdJlebzQT == BBWcoiKUcs){LJAJSwesCj = true;}
      if(YYxlgWeOas == qxonGkDYit){mFdoiJqGpR = true;}
      while(fsdjbsBbLu == uBMcLZHadq){afhZGShyRJ = true;}
      while(BBWcoiKUcs == BBWcoiKUcs){EqeRFtDWaQ = true;}
      while(qxonGkDYit == qxonGkDYit){onfZQXgkne = true;}
      if(ACBjkFhyCN == true){ACBjkFhyCN = false;}
      if(BxZuylMKcj == true){BxZuylMKcj = false;}
      if(eqpHbiDpdp == true){eqpHbiDpdp = false;}
      if(obsRtzAmrj == true){obsRtzAmrj = false;}
      if(BLSOqsWtoT == true){BLSOqsWtoT = false;}
      if(XswzOJLtIC == true){XswzOJLtIC = false;}
      if(BqTLYZEIBz == true){BqTLYZEIBz = false;}
      if(lZSrhTXaPh == true){lZSrhTXaPh = false;}
      if(LJAJSwesCj == true){LJAJSwesCj = false;}
      if(mFdoiJqGpR == true){mFdoiJqGpR = false;}
      if(nNsphyaDQu == true){nNsphyaDQu = false;}
      if(kkdZqqpJsb == true){kkdZqqpJsb = false;}
      if(tLFQLfucJY == true){tLFQLfucJY = false;}
      if(bRjytxQKbT == true){bRjytxQKbT = false;}
      if(VbcHzCaDyq == true){VbcHzCaDyq = false;}
      if(ShNNWcHbdB == true){ShNNWcHbdB = false;}
      if(DxtrSTAffs == true){DxtrSTAffs = false;}
      if(afhZGShyRJ == true){afhZGShyRJ = false;}
      if(EqeRFtDWaQ == true){EqeRFtDWaQ = false;}
      if(onfZQXgkne == true){onfZQXgkne = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CZCYBTUUFO
{ 
  void gSDyIZqlrh()
  { 
      bool AdIKwWDpxP = false;
      bool upjzCUCTQg = false;
      bool OeKtEDZFdx = false;
      bool fUIupeXprm = false;
      bool oITIjQDgzd = false;
      bool VQGobUTOFs = false;
      bool wxMAiZgoJW = false;
      bool xMadrGKBJn = false;
      bool zrGzbPOTSU = false;
      bool LIkzpquTYK = false;
      bool jNWbfJobwV = false;
      bool KRERsEqMYT = false;
      bool KMWoLnabnB = false;
      bool KqczDkUdTR = false;
      bool amWxKtESFl = false;
      bool zhuEzWqhPr = false;
      bool hMntKTnFOH = false;
      bool iMsGsXoYeR = false;
      bool jIVBCcuXzf = false;
      bool tmNajNycmp = false;
      string yNQQlYXCUW;
      string aPZyiEGLab;
      string PFbfaWDurY;
      string RiPaaQjQbJ;
      string ilqXidwiuA;
      string HMDFErljoP;
      string VcKuEqAyXR;
      string UpjQrcNExw;
      string ZUAqRFfKWh;
      string ezaLnGbwSr;
      string dxKcfQblMa;
      string ehmroAcScz;
      string KpbomUOXcl;
      string BRkEScJWLA;
      string ctxwDwLhWm;
      string cJSTgmVVpK;
      string BEJZYMwhZL;
      string qGGbVQrfkp;
      string IgBoJryRXe;
      string HngByYjWWp;
      if(yNQQlYXCUW == dxKcfQblMa){AdIKwWDpxP = true;}
      else if(dxKcfQblMa == yNQQlYXCUW){jNWbfJobwV = true;}
      if(aPZyiEGLab == ehmroAcScz){upjzCUCTQg = true;}
      else if(ehmroAcScz == aPZyiEGLab){KRERsEqMYT = true;}
      if(PFbfaWDurY == KpbomUOXcl){OeKtEDZFdx = true;}
      else if(KpbomUOXcl == PFbfaWDurY){KMWoLnabnB = true;}
      if(RiPaaQjQbJ == BRkEScJWLA){fUIupeXprm = true;}
      else if(BRkEScJWLA == RiPaaQjQbJ){KqczDkUdTR = true;}
      if(ilqXidwiuA == ctxwDwLhWm){oITIjQDgzd = true;}
      else if(ctxwDwLhWm == ilqXidwiuA){amWxKtESFl = true;}
      if(HMDFErljoP == cJSTgmVVpK){VQGobUTOFs = true;}
      else if(cJSTgmVVpK == HMDFErljoP){zhuEzWqhPr = true;}
      if(VcKuEqAyXR == BEJZYMwhZL){wxMAiZgoJW = true;}
      else if(BEJZYMwhZL == VcKuEqAyXR){hMntKTnFOH = true;}
      if(UpjQrcNExw == qGGbVQrfkp){xMadrGKBJn = true;}
      if(ZUAqRFfKWh == IgBoJryRXe){zrGzbPOTSU = true;}
      if(ezaLnGbwSr == HngByYjWWp){LIkzpquTYK = true;}
      while(qGGbVQrfkp == UpjQrcNExw){iMsGsXoYeR = true;}
      while(IgBoJryRXe == IgBoJryRXe){jIVBCcuXzf = true;}
      while(HngByYjWWp == HngByYjWWp){tmNajNycmp = true;}
      if(AdIKwWDpxP == true){AdIKwWDpxP = false;}
      if(upjzCUCTQg == true){upjzCUCTQg = false;}
      if(OeKtEDZFdx == true){OeKtEDZFdx = false;}
      if(fUIupeXprm == true){fUIupeXprm = false;}
      if(oITIjQDgzd == true){oITIjQDgzd = false;}
      if(VQGobUTOFs == true){VQGobUTOFs = false;}
      if(wxMAiZgoJW == true){wxMAiZgoJW = false;}
      if(xMadrGKBJn == true){xMadrGKBJn = false;}
      if(zrGzbPOTSU == true){zrGzbPOTSU = false;}
      if(LIkzpquTYK == true){LIkzpquTYK = false;}
      if(jNWbfJobwV == true){jNWbfJobwV = false;}
      if(KRERsEqMYT == true){KRERsEqMYT = false;}
      if(KMWoLnabnB == true){KMWoLnabnB = false;}
      if(KqczDkUdTR == true){KqczDkUdTR = false;}
      if(amWxKtESFl == true){amWxKtESFl = false;}
      if(zhuEzWqhPr == true){zhuEzWqhPr = false;}
      if(hMntKTnFOH == true){hMntKTnFOH = false;}
      if(iMsGsXoYeR == true){iMsGsXoYeR = false;}
      if(jIVBCcuXzf == true){jIVBCcuXzf = false;}
      if(tmNajNycmp == true){tmNajNycmp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGAIOWDSKQ
{ 
  void ffaOGWCnGO()
  { 
      bool BinsJpKxBF = false;
      bool PMUhUSymZo = false;
      bool uejSWZtjHw = false;
      bool eONPcXFInk = false;
      bool qyCyWbZPsN = false;
      bool IXFjfVzUVj = false;
      bool uZpFZAzEEw = false;
      bool Mpzoxxckwt = false;
      bool AeqsnGJdjG = false;
      bool YjlEoQHxYV = false;
      bool cUKwARYPli = false;
      bool sNYaiQiwQS = false;
      bool qUUyWcDuAf = false;
      bool ofMaRfTtsW = false;
      bool hsrBNLLLUY = false;
      bool hKfFdIzMZX = false;
      bool OcPFsNAyJD = false;
      bool woDtjxbTkL = false;
      bool RrZbydzGwI = false;
      bool fHTVHEdlHz = false;
      string CtrTFnkkpW;
      string xOkHsdIUeM;
      string jhXSkLpBzU;
      string szuTJAlbDA;
      string TflwhETQSA;
      string eapDEUVZht;
      string yjkVdxSRxs;
      string rfRdsEwbkg;
      string qYiypRJqPo;
      string dMsICjtPRj;
      string kCTZIyJMKA;
      string XsnBCYBmeL;
      string naCIOflIaJ;
      string JgKAwoFIpr;
      string IxgPRjXrGc;
      string hHkFwJzKLb;
      string LBkBpqinEM;
      string TrxmDqtmpd;
      string HsCxaBuEDl;
      string otxNfHLfYa;
      if(CtrTFnkkpW == kCTZIyJMKA){BinsJpKxBF = true;}
      else if(kCTZIyJMKA == CtrTFnkkpW){cUKwARYPli = true;}
      if(xOkHsdIUeM == XsnBCYBmeL){PMUhUSymZo = true;}
      else if(XsnBCYBmeL == xOkHsdIUeM){sNYaiQiwQS = true;}
      if(jhXSkLpBzU == naCIOflIaJ){uejSWZtjHw = true;}
      else if(naCIOflIaJ == jhXSkLpBzU){qUUyWcDuAf = true;}
      if(szuTJAlbDA == JgKAwoFIpr){eONPcXFInk = true;}
      else if(JgKAwoFIpr == szuTJAlbDA){ofMaRfTtsW = true;}
      if(TflwhETQSA == IxgPRjXrGc){qyCyWbZPsN = true;}
      else if(IxgPRjXrGc == TflwhETQSA){hsrBNLLLUY = true;}
      if(eapDEUVZht == hHkFwJzKLb){IXFjfVzUVj = true;}
      else if(hHkFwJzKLb == eapDEUVZht){hKfFdIzMZX = true;}
      if(yjkVdxSRxs == LBkBpqinEM){uZpFZAzEEw = true;}
      else if(LBkBpqinEM == yjkVdxSRxs){OcPFsNAyJD = true;}
      if(rfRdsEwbkg == TrxmDqtmpd){Mpzoxxckwt = true;}
      if(qYiypRJqPo == HsCxaBuEDl){AeqsnGJdjG = true;}
      if(dMsICjtPRj == otxNfHLfYa){YjlEoQHxYV = true;}
      while(TrxmDqtmpd == rfRdsEwbkg){woDtjxbTkL = true;}
      while(HsCxaBuEDl == HsCxaBuEDl){RrZbydzGwI = true;}
      while(otxNfHLfYa == otxNfHLfYa){fHTVHEdlHz = true;}
      if(BinsJpKxBF == true){BinsJpKxBF = false;}
      if(PMUhUSymZo == true){PMUhUSymZo = false;}
      if(uejSWZtjHw == true){uejSWZtjHw = false;}
      if(eONPcXFInk == true){eONPcXFInk = false;}
      if(qyCyWbZPsN == true){qyCyWbZPsN = false;}
      if(IXFjfVzUVj == true){IXFjfVzUVj = false;}
      if(uZpFZAzEEw == true){uZpFZAzEEw = false;}
      if(Mpzoxxckwt == true){Mpzoxxckwt = false;}
      if(AeqsnGJdjG == true){AeqsnGJdjG = false;}
      if(YjlEoQHxYV == true){YjlEoQHxYV = false;}
      if(cUKwARYPli == true){cUKwARYPli = false;}
      if(sNYaiQiwQS == true){sNYaiQiwQS = false;}
      if(qUUyWcDuAf == true){qUUyWcDuAf = false;}
      if(ofMaRfTtsW == true){ofMaRfTtsW = false;}
      if(hsrBNLLLUY == true){hsrBNLLLUY = false;}
      if(hKfFdIzMZX == true){hKfFdIzMZX = false;}
      if(OcPFsNAyJD == true){OcPFsNAyJD = false;}
      if(woDtjxbTkL == true){woDtjxbTkL = false;}
      if(RrZbydzGwI == true){RrZbydzGwI = false;}
      if(fHTVHEdlHz == true){fHTVHEdlHz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PHTZAGWBFA
{ 
  void LVbDbbbKnK()
  { 
      bool XpdwfXkjIx = false;
      bool yEkbSbDASS = false;
      bool ZiJEZNcUZK = false;
      bool eTTUDOQwtM = false;
      bool raAufmlImj = false;
      bool JHBOhngYWS = false;
      bool uPKyRdjPXE = false;
      bool LGGGZziNYl = false;
      bool bThpAWSFmO = false;
      bool gqYbRcPBdB = false;
      bool DVjiYCBunh = false;
      bool FTAjqagUxt = false;
      bool LecIWTgenx = false;
      bool igjXiFizQx = false;
      bool VWRFJNqnjq = false;
      bool uuEioYsbLE = false;
      bool UVHpyXibBk = false;
      bool qhDAXoMWzI = false;
      bool crtwCncBhK = false;
      bool LHmMbAPaGl = false;
      string uowMGrKwEp;
      string mAAqUONHXm;
      string gCHbnJuWqT;
      string xJlIGesoYn;
      string bYbFmRcWlq;
      string FkElsshUXw;
      string xnFjsdOrjo;
      string VYijKIZBnV;
      string gYkzOLFAON;
      string xYQbqnSrMJ;
      string DjlwUfCUak;
      string TgfCOYCGUg;
      string YOdWrxIGsW;
      string ohndSxlodi;
      string JjYcsQrNNR;
      string kMWfknFODX;
      string WwbEukrCiR;
      string lNblXnoBcb;
      string EurakcLIre;
      string qXkGLNIUgH;
      if(uowMGrKwEp == DjlwUfCUak){XpdwfXkjIx = true;}
      else if(DjlwUfCUak == uowMGrKwEp){DVjiYCBunh = true;}
      if(mAAqUONHXm == TgfCOYCGUg){yEkbSbDASS = true;}
      else if(TgfCOYCGUg == mAAqUONHXm){FTAjqagUxt = true;}
      if(gCHbnJuWqT == YOdWrxIGsW){ZiJEZNcUZK = true;}
      else if(YOdWrxIGsW == gCHbnJuWqT){LecIWTgenx = true;}
      if(xJlIGesoYn == ohndSxlodi){eTTUDOQwtM = true;}
      else if(ohndSxlodi == xJlIGesoYn){igjXiFizQx = true;}
      if(bYbFmRcWlq == JjYcsQrNNR){raAufmlImj = true;}
      else if(JjYcsQrNNR == bYbFmRcWlq){VWRFJNqnjq = true;}
      if(FkElsshUXw == kMWfknFODX){JHBOhngYWS = true;}
      else if(kMWfknFODX == FkElsshUXw){uuEioYsbLE = true;}
      if(xnFjsdOrjo == WwbEukrCiR){uPKyRdjPXE = true;}
      else if(WwbEukrCiR == xnFjsdOrjo){UVHpyXibBk = true;}
      if(VYijKIZBnV == lNblXnoBcb){LGGGZziNYl = true;}
      if(gYkzOLFAON == EurakcLIre){bThpAWSFmO = true;}
      if(xYQbqnSrMJ == qXkGLNIUgH){gqYbRcPBdB = true;}
      while(lNblXnoBcb == VYijKIZBnV){qhDAXoMWzI = true;}
      while(EurakcLIre == EurakcLIre){crtwCncBhK = true;}
      while(qXkGLNIUgH == qXkGLNIUgH){LHmMbAPaGl = true;}
      if(XpdwfXkjIx == true){XpdwfXkjIx = false;}
      if(yEkbSbDASS == true){yEkbSbDASS = false;}
      if(ZiJEZNcUZK == true){ZiJEZNcUZK = false;}
      if(eTTUDOQwtM == true){eTTUDOQwtM = false;}
      if(raAufmlImj == true){raAufmlImj = false;}
      if(JHBOhngYWS == true){JHBOhngYWS = false;}
      if(uPKyRdjPXE == true){uPKyRdjPXE = false;}
      if(LGGGZziNYl == true){LGGGZziNYl = false;}
      if(bThpAWSFmO == true){bThpAWSFmO = false;}
      if(gqYbRcPBdB == true){gqYbRcPBdB = false;}
      if(DVjiYCBunh == true){DVjiYCBunh = false;}
      if(FTAjqagUxt == true){FTAjqagUxt = false;}
      if(LecIWTgenx == true){LecIWTgenx = false;}
      if(igjXiFizQx == true){igjXiFizQx = false;}
      if(VWRFJNqnjq == true){VWRFJNqnjq = false;}
      if(uuEioYsbLE == true){uuEioYsbLE = false;}
      if(UVHpyXibBk == true){UVHpyXibBk = false;}
      if(qhDAXoMWzI == true){qhDAXoMWzI = false;}
      if(crtwCncBhK == true){crtwCncBhK = false;}
      if(LHmMbAPaGl == true){LHmMbAPaGl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TDYPDHRYYD
{ 
  void AEtbcRFrnz()
  { 
      bool dIGSYaBBFX = false;
      bool FuIzsPjagl = false;
      bool nRuaVtXjCY = false;
      bool MfGlCmLmrF = false;
      bool RiVoEAhbcE = false;
      bool MgXFHLNexd = false;
      bool CQyfLZoWwG = false;
      bool EwhbTEwGWU = false;
      bool MwGyMeIBeq = false;
      bool ZfpNCAkodd = false;
      bool LKeWAPzukC = false;
      bool OGIbRGKATf = false;
      bool RmqFgXGUZT = false;
      bool TGbrJBQixw = false;
      bool fMQcbSXOuu = false;
      bool pkVxMXTYpb = false;
      bool JdVQhIeQRQ = false;
      bool oaCXAFWOdN = false;
      bool zqYdcikeel = false;
      bool hrsUlBpztS = false;
      string XpHLhWtlza;
      string edfCdIGWaN;
      string CeFXcsbyHd;
      string sppHwFPPjX;
      string bDURDgNAIt;
      string iWWEerkiio;
      string twdVgonXGY;
      string sqmDkzJnUu;
      string fbpMuWSkcD;
      string UfftcfYzkO;
      string sosiBriSSf;
      string ixOnISFRaJ;
      string VCuCDMKraF;
      string ZJCGBphGLC;
      string nARwUXQrkJ;
      string ZHYasptqeo;
      string hqrNFYtIlS;
      string kzGXVUjyhf;
      string uRGQfSkbMK;
      string wpaWUwIEqu;
      if(XpHLhWtlza == sosiBriSSf){dIGSYaBBFX = true;}
      else if(sosiBriSSf == XpHLhWtlza){LKeWAPzukC = true;}
      if(edfCdIGWaN == ixOnISFRaJ){FuIzsPjagl = true;}
      else if(ixOnISFRaJ == edfCdIGWaN){OGIbRGKATf = true;}
      if(CeFXcsbyHd == VCuCDMKraF){nRuaVtXjCY = true;}
      else if(VCuCDMKraF == CeFXcsbyHd){RmqFgXGUZT = true;}
      if(sppHwFPPjX == ZJCGBphGLC){MfGlCmLmrF = true;}
      else if(ZJCGBphGLC == sppHwFPPjX){TGbrJBQixw = true;}
      if(bDURDgNAIt == nARwUXQrkJ){RiVoEAhbcE = true;}
      else if(nARwUXQrkJ == bDURDgNAIt){fMQcbSXOuu = true;}
      if(iWWEerkiio == ZHYasptqeo){MgXFHLNexd = true;}
      else if(ZHYasptqeo == iWWEerkiio){pkVxMXTYpb = true;}
      if(twdVgonXGY == hqrNFYtIlS){CQyfLZoWwG = true;}
      else if(hqrNFYtIlS == twdVgonXGY){JdVQhIeQRQ = true;}
      if(sqmDkzJnUu == kzGXVUjyhf){EwhbTEwGWU = true;}
      if(fbpMuWSkcD == uRGQfSkbMK){MwGyMeIBeq = true;}
      if(UfftcfYzkO == wpaWUwIEqu){ZfpNCAkodd = true;}
      while(kzGXVUjyhf == sqmDkzJnUu){oaCXAFWOdN = true;}
      while(uRGQfSkbMK == uRGQfSkbMK){zqYdcikeel = true;}
      while(wpaWUwIEqu == wpaWUwIEqu){hrsUlBpztS = true;}
      if(dIGSYaBBFX == true){dIGSYaBBFX = false;}
      if(FuIzsPjagl == true){FuIzsPjagl = false;}
      if(nRuaVtXjCY == true){nRuaVtXjCY = false;}
      if(MfGlCmLmrF == true){MfGlCmLmrF = false;}
      if(RiVoEAhbcE == true){RiVoEAhbcE = false;}
      if(MgXFHLNexd == true){MgXFHLNexd = false;}
      if(CQyfLZoWwG == true){CQyfLZoWwG = false;}
      if(EwhbTEwGWU == true){EwhbTEwGWU = false;}
      if(MwGyMeIBeq == true){MwGyMeIBeq = false;}
      if(ZfpNCAkodd == true){ZfpNCAkodd = false;}
      if(LKeWAPzukC == true){LKeWAPzukC = false;}
      if(OGIbRGKATf == true){OGIbRGKATf = false;}
      if(RmqFgXGUZT == true){RmqFgXGUZT = false;}
      if(TGbrJBQixw == true){TGbrJBQixw = false;}
      if(fMQcbSXOuu == true){fMQcbSXOuu = false;}
      if(pkVxMXTYpb == true){pkVxMXTYpb = false;}
      if(JdVQhIeQRQ == true){JdVQhIeQRQ = false;}
      if(oaCXAFWOdN == true){oaCXAFWOdN = false;}
      if(zqYdcikeel == true){zqYdcikeel = false;}
      if(hrsUlBpztS == true){hrsUlBpztS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GCGYJEKWVW
{ 
  void GgGEZcdSQH()
  { 
      bool bqPOftdkSI = false;
      bool FWeJOTSILp = false;
      bool XDJtEZUlwB = false;
      bool EBLybhAVyE = false;
      bool WBzOGajOgS = false;
      bool PuPXsYgUJG = false;
      bool ZrnQEEKggf = false;
      bool SwJGTVDund = false;
      bool oGFdlIknED = false;
      bool BfLredMhKB = false;
      bool PDgAASlIDW = false;
      bool UlgfQSmKeu = false;
      bool SWbdemjRao = false;
      bool IVjlNkZFcT = false;
      bool WbjghOzfaM = false;
      bool qCDOisaCUN = false;
      bool hTgONzBtRe = false;
      bool shgKYpltwQ = false;
      bool mEpOyGRUCU = false;
      bool KWjPkCtVTi = false;
      string yIlmLFmERc;
      string SzBVHcTBjJ;
      string PCbFuqMFMT;
      string PnuKnTeNjO;
      string BWWjxCTRDm;
      string bXIIywggrU;
      string sgrxMeDqhn;
      string yGRVIsfqIr;
      string WtBZqqemLq;
      string lyUOUTeYWR;
      string ybjPoVGmAF;
      string QoYzxzfSFU;
      string AQfpBzlCAn;
      string NGTpstJlkV;
      string kqmFaxZURV;
      string nMTCRhwtNo;
      string jDmLrJUhFC;
      string oshiiIcZOE;
      string ZQkezBlRXL;
      string xPXulhEbNQ;
      if(yIlmLFmERc == ybjPoVGmAF){bqPOftdkSI = true;}
      else if(ybjPoVGmAF == yIlmLFmERc){PDgAASlIDW = true;}
      if(SzBVHcTBjJ == QoYzxzfSFU){FWeJOTSILp = true;}
      else if(QoYzxzfSFU == SzBVHcTBjJ){UlgfQSmKeu = true;}
      if(PCbFuqMFMT == AQfpBzlCAn){XDJtEZUlwB = true;}
      else if(AQfpBzlCAn == PCbFuqMFMT){SWbdemjRao = true;}
      if(PnuKnTeNjO == NGTpstJlkV){EBLybhAVyE = true;}
      else if(NGTpstJlkV == PnuKnTeNjO){IVjlNkZFcT = true;}
      if(BWWjxCTRDm == kqmFaxZURV){WBzOGajOgS = true;}
      else if(kqmFaxZURV == BWWjxCTRDm){WbjghOzfaM = true;}
      if(bXIIywggrU == nMTCRhwtNo){PuPXsYgUJG = true;}
      else if(nMTCRhwtNo == bXIIywggrU){qCDOisaCUN = true;}
      if(sgrxMeDqhn == jDmLrJUhFC){ZrnQEEKggf = true;}
      else if(jDmLrJUhFC == sgrxMeDqhn){hTgONzBtRe = true;}
      if(yGRVIsfqIr == oshiiIcZOE){SwJGTVDund = true;}
      if(WtBZqqemLq == ZQkezBlRXL){oGFdlIknED = true;}
      if(lyUOUTeYWR == xPXulhEbNQ){BfLredMhKB = true;}
      while(oshiiIcZOE == yGRVIsfqIr){shgKYpltwQ = true;}
      while(ZQkezBlRXL == ZQkezBlRXL){mEpOyGRUCU = true;}
      while(xPXulhEbNQ == xPXulhEbNQ){KWjPkCtVTi = true;}
      if(bqPOftdkSI == true){bqPOftdkSI = false;}
      if(FWeJOTSILp == true){FWeJOTSILp = false;}
      if(XDJtEZUlwB == true){XDJtEZUlwB = false;}
      if(EBLybhAVyE == true){EBLybhAVyE = false;}
      if(WBzOGajOgS == true){WBzOGajOgS = false;}
      if(PuPXsYgUJG == true){PuPXsYgUJG = false;}
      if(ZrnQEEKggf == true){ZrnQEEKggf = false;}
      if(SwJGTVDund == true){SwJGTVDund = false;}
      if(oGFdlIknED == true){oGFdlIknED = false;}
      if(BfLredMhKB == true){BfLredMhKB = false;}
      if(PDgAASlIDW == true){PDgAASlIDW = false;}
      if(UlgfQSmKeu == true){UlgfQSmKeu = false;}
      if(SWbdemjRao == true){SWbdemjRao = false;}
      if(IVjlNkZFcT == true){IVjlNkZFcT = false;}
      if(WbjghOzfaM == true){WbjghOzfaM = false;}
      if(qCDOisaCUN == true){qCDOisaCUN = false;}
      if(hTgONzBtRe == true){hTgONzBtRe = false;}
      if(shgKYpltwQ == true){shgKYpltwQ = false;}
      if(mEpOyGRUCU == true){mEpOyGRUCU = false;}
      if(KWjPkCtVTi == true){KWjPkCtVTi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HTRMIFMREB
{ 
  void TZCHQmGPIz()
  { 
      bool XqVnqxbAqk = false;
      bool VOjwLaTgdl = false;
      bool PGZyhJOQdZ = false;
      bool tGglngakKa = false;
      bool OtjiIddBZj = false;
      bool DoWhXQRWFg = false;
      bool iKWQpOhxHe = false;
      bool ziVDWVVqoD = false;
      bool fMpsWFjzOX = false;
      bool PEecqDWTrs = false;
      bool wftujTSSKC = false;
      bool uZgCBWUdtk = false;
      bool dhijOuEsLS = false;
      bool yBzwHzSuIC = false;
      bool mRnMboWcaU = false;
      bool isZGPNxJfo = false;
      bool PYGrDsaktB = false;
      bool EYUqyMtWHY = false;
      bool XbRqiEbrft = false;
      bool CIOSmNKwIi = false;
      string hDpQpGgRfe;
      string FeGCtTCynp;
      string QnkkgfFfaE;
      string SghNlWHUKM;
      string espQtkHzxI;
      string BUbuTsSFiJ;
      string BBqbMYwrQW;
      string MgnbLWyTpw;
      string YFhSDxEltr;
      string EBkAKdCODU;
      string nOhauTgAjx;
      string tyPlkuTYYO;
      string UJyXRKunQh;
      string UjQUIJXGWi;
      string QECwyFlzOP;
      string JdooAdQJIk;
      string XsiBcKhtda;
      string XMCoyPHBZM;
      string YwYBXptbTe;
      string sNykLXVATm;
      if(hDpQpGgRfe == nOhauTgAjx){XqVnqxbAqk = true;}
      else if(nOhauTgAjx == hDpQpGgRfe){wftujTSSKC = true;}
      if(FeGCtTCynp == tyPlkuTYYO){VOjwLaTgdl = true;}
      else if(tyPlkuTYYO == FeGCtTCynp){uZgCBWUdtk = true;}
      if(QnkkgfFfaE == UJyXRKunQh){PGZyhJOQdZ = true;}
      else if(UJyXRKunQh == QnkkgfFfaE){dhijOuEsLS = true;}
      if(SghNlWHUKM == UjQUIJXGWi){tGglngakKa = true;}
      else if(UjQUIJXGWi == SghNlWHUKM){yBzwHzSuIC = true;}
      if(espQtkHzxI == QECwyFlzOP){OtjiIddBZj = true;}
      else if(QECwyFlzOP == espQtkHzxI){mRnMboWcaU = true;}
      if(BUbuTsSFiJ == JdooAdQJIk){DoWhXQRWFg = true;}
      else if(JdooAdQJIk == BUbuTsSFiJ){isZGPNxJfo = true;}
      if(BBqbMYwrQW == XsiBcKhtda){iKWQpOhxHe = true;}
      else if(XsiBcKhtda == BBqbMYwrQW){PYGrDsaktB = true;}
      if(MgnbLWyTpw == XMCoyPHBZM){ziVDWVVqoD = true;}
      if(YFhSDxEltr == YwYBXptbTe){fMpsWFjzOX = true;}
      if(EBkAKdCODU == sNykLXVATm){PEecqDWTrs = true;}
      while(XMCoyPHBZM == MgnbLWyTpw){EYUqyMtWHY = true;}
      while(YwYBXptbTe == YwYBXptbTe){XbRqiEbrft = true;}
      while(sNykLXVATm == sNykLXVATm){CIOSmNKwIi = true;}
      if(XqVnqxbAqk == true){XqVnqxbAqk = false;}
      if(VOjwLaTgdl == true){VOjwLaTgdl = false;}
      if(PGZyhJOQdZ == true){PGZyhJOQdZ = false;}
      if(tGglngakKa == true){tGglngakKa = false;}
      if(OtjiIddBZj == true){OtjiIddBZj = false;}
      if(DoWhXQRWFg == true){DoWhXQRWFg = false;}
      if(iKWQpOhxHe == true){iKWQpOhxHe = false;}
      if(ziVDWVVqoD == true){ziVDWVVqoD = false;}
      if(fMpsWFjzOX == true){fMpsWFjzOX = false;}
      if(PEecqDWTrs == true){PEecqDWTrs = false;}
      if(wftujTSSKC == true){wftujTSSKC = false;}
      if(uZgCBWUdtk == true){uZgCBWUdtk = false;}
      if(dhijOuEsLS == true){dhijOuEsLS = false;}
      if(yBzwHzSuIC == true){yBzwHzSuIC = false;}
      if(mRnMboWcaU == true){mRnMboWcaU = false;}
      if(isZGPNxJfo == true){isZGPNxJfo = false;}
      if(PYGrDsaktB == true){PYGrDsaktB = false;}
      if(EYUqyMtWHY == true){EYUqyMtWHY = false;}
      if(XbRqiEbrft == true){XbRqiEbrft = false;}
      if(CIOSmNKwIi == true){CIOSmNKwIi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFWSCHQHET
{ 
  void duCzafyKhD()
  { 
      bool otDjzBOWTA = false;
      bool dQIRryqqtK = false;
      bool LlWsmlQEWD = false;
      bool ValTognfAU = false;
      bool zdLSVjfwUG = false;
      bool ETtXBCWJwN = false;
      bool kJzQeDdobL = false;
      bool KKqYLhaEWC = false;
      bool FUjQyCgORm = false;
      bool JdiljodtmS = false;
      bool GqTJuscULS = false;
      bool aRlsHPZiRb = false;
      bool VPWoBfaEoV = false;
      bool EfQEwOBZUF = false;
      bool ZMCzMqrpeT = false;
      bool PtcLxqTeIP = false;
      bool RXfoNtBgxs = false;
      bool OzNMCJMXcJ = false;
      bool nkYUGKDFHF = false;
      bool uWRFmBfMkR = false;
      string QVpNDGUuVd;
      string sOgNTWITbe;
      string YikhQYUlga;
      string frUaSJiieS;
      string EuORQIVrsT;
      string DiZuygjHxe;
      string khNtyAtGtK;
      string mZnIZcUSQI;
      string CcsNXxSZcl;
      string YblAhVhUTP;
      string NPxhfdtQUU;
      string MRqnbHoAVB;
      string hTcHlLnnZD;
      string uzyAtmfKht;
      string CBEHZHjxXa;
      string ggyShtlpwT;
      string oGpQYMSptn;
      string beSbygPVgd;
      string aqPzWNAfSA;
      string BoNNEuKniN;
      if(QVpNDGUuVd == NPxhfdtQUU){otDjzBOWTA = true;}
      else if(NPxhfdtQUU == QVpNDGUuVd){GqTJuscULS = true;}
      if(sOgNTWITbe == MRqnbHoAVB){dQIRryqqtK = true;}
      else if(MRqnbHoAVB == sOgNTWITbe){aRlsHPZiRb = true;}
      if(YikhQYUlga == hTcHlLnnZD){LlWsmlQEWD = true;}
      else if(hTcHlLnnZD == YikhQYUlga){VPWoBfaEoV = true;}
      if(frUaSJiieS == uzyAtmfKht){ValTognfAU = true;}
      else if(uzyAtmfKht == frUaSJiieS){EfQEwOBZUF = true;}
      if(EuORQIVrsT == CBEHZHjxXa){zdLSVjfwUG = true;}
      else if(CBEHZHjxXa == EuORQIVrsT){ZMCzMqrpeT = true;}
      if(DiZuygjHxe == ggyShtlpwT){ETtXBCWJwN = true;}
      else if(ggyShtlpwT == DiZuygjHxe){PtcLxqTeIP = true;}
      if(khNtyAtGtK == oGpQYMSptn){kJzQeDdobL = true;}
      else if(oGpQYMSptn == khNtyAtGtK){RXfoNtBgxs = true;}
      if(mZnIZcUSQI == beSbygPVgd){KKqYLhaEWC = true;}
      if(CcsNXxSZcl == aqPzWNAfSA){FUjQyCgORm = true;}
      if(YblAhVhUTP == BoNNEuKniN){JdiljodtmS = true;}
      while(beSbygPVgd == mZnIZcUSQI){OzNMCJMXcJ = true;}
      while(aqPzWNAfSA == aqPzWNAfSA){nkYUGKDFHF = true;}
      while(BoNNEuKniN == BoNNEuKniN){uWRFmBfMkR = true;}
      if(otDjzBOWTA == true){otDjzBOWTA = false;}
      if(dQIRryqqtK == true){dQIRryqqtK = false;}
      if(LlWsmlQEWD == true){LlWsmlQEWD = false;}
      if(ValTognfAU == true){ValTognfAU = false;}
      if(zdLSVjfwUG == true){zdLSVjfwUG = false;}
      if(ETtXBCWJwN == true){ETtXBCWJwN = false;}
      if(kJzQeDdobL == true){kJzQeDdobL = false;}
      if(KKqYLhaEWC == true){KKqYLhaEWC = false;}
      if(FUjQyCgORm == true){FUjQyCgORm = false;}
      if(JdiljodtmS == true){JdiljodtmS = false;}
      if(GqTJuscULS == true){GqTJuscULS = false;}
      if(aRlsHPZiRb == true){aRlsHPZiRb = false;}
      if(VPWoBfaEoV == true){VPWoBfaEoV = false;}
      if(EfQEwOBZUF == true){EfQEwOBZUF = false;}
      if(ZMCzMqrpeT == true){ZMCzMqrpeT = false;}
      if(PtcLxqTeIP == true){PtcLxqTeIP = false;}
      if(RXfoNtBgxs == true){RXfoNtBgxs = false;}
      if(OzNMCJMXcJ == true){OzNMCJMXcJ = false;}
      if(nkYUGKDFHF == true){nkYUGKDFHF = false;}
      if(uWRFmBfMkR == true){uWRFmBfMkR = false;}
    } 
}; 
