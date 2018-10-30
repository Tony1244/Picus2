#include "CSX_Memory.h"
#include <vector>

#include <Psapi.h>
#pragma comment(lib,"psapi")

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

//[junk_enable /]
MODULEINFO GetModuleInfo(PCHAR szModule)
{
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = GetModuleHandleA(szModule);

	if (hModule == 0)
		return modinfo;

	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	return modinfo;
}

namespace CSX
{
	namespace Memory
	{
		/* Find Push String ( 0x68, dword ptr [str] ) */
		DWORD FindPatternV2(std::string moduleName, std::string Mask)
		{
			const char* pat = Mask.c_str();
			DWORD firstMatch = 0;
			DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
			MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
			DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
			for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
			{
				if (!*pat)
				{
					return firstMatch;
				}
				if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
				{
					if (!firstMatch)
					{
						firstMatch = pCur;
					}

					if (!pat[2])
					{
						return firstMatch;
					}


					if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					{
						pat += 3;
					}
					else
					{
						pat += 2; //one ?
					}

				}
				else
				{
					pat = Mask.c_str();
					firstMatch = 0;
				}
			}
			return NULL;
		}
#define IsInRange(x, a, b) (x >= a && x <= b)
#define GetBits(x) (IsInRange(x, '0', '9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xA))
#define GetByte(x) (GetBits(x[0]) << 4 | GetBits(x[1]))
		DWORD FindSig(DWORD dwAddress, DWORD dwLength, const char* szPattern)
		{
			if (!dwAddress || !dwLength || !szPattern)
				return 0;

			const char* pat = szPattern;
			DWORD firstMatch = NULL;

			for (DWORD pCur = dwAddress; pCur < dwLength; pCur++)
			{
				if (!*pat)
					return firstMatch;

				if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == GetByte(pat))
				{
					if (!firstMatch)
						firstMatch = pCur;

					if (!pat[2])
						return firstMatch;

					if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
						pat += 3;

					else pat += 2;
				}
				else
				{
					pat = szPattern;
					firstMatch = 0;
				}
			}

			return 0;
		}
		DWORD FindSignature(const char* szModuleName, const char* PatternName, char* szPattern)
		{
			HMODULE hModule = GetModuleHandleA(szModuleName);
			PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hModule;
			PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hModule) + pDOSHeader->e_lfanew);

			DWORD ret = FindSig(((DWORD)hModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DWORD)hModule) + pNTHeaders->OptionalHeader.SizeOfCode, szPattern);;

			return ret;
		}

		/* Find Push String ( 0x68, dword ptr [str] ) */

		DWORD FindPushString(DWORD dwStart, DWORD dwEnd, DWORD dwAddress)
		{
			char szPattern[5] = { 0x68 , 0x00 , 0x00 , 0x00 , 0x00 };
			*(PDWORD)&szPattern[1] = dwAddress;
			return FindPattern(szPattern, sizeof(szPattern), dwStart, dwEnd, 0);
		}

		DWORD FindPushString(PCHAR szModule, DWORD dwAddress)
		{
			MODULEINFO mInfo = GetModuleInfo(szModule);

			DWORD dwStart = (DWORD)mInfo.lpBaseOfDll;
			DWORD dwSize = (DWORD)mInfo.SizeOfImage;

			return FindPushString(dwStart, dwStart + dwSize, dwAddress);
		}

		/* Code Style Use Mask \x8B\xFF\xFF\xFF\xFF x???? */

		DWORD FindPattern(PCHAR pPattern, PCHAR pszMask, DWORD dwStart, DWORD dwEnd, DWORD dwOffset)
		{
			bool bFound = false;
			DWORD dwPtLen = lstrlenA(pszMask);

#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::FindPattern(%s) Init", pszMask);
#endif

			for (DWORD dwPtr = dwStart; dwPtr < dwEnd - dwPtLen; dwPtr++) {
				bFound = true;

				for (DWORD idx = 0; idx < dwPtLen; idx++) {
					if (pszMask[idx] == 'x' && pPattern[idx] != *(PCHAR)(dwPtr + idx))
					{
						bFound = false;
						break;
					}
				}

				if (bFound)
				{
#if ENABLE_DEBUG_FILE == 1
					string pPattern_str = pPattern;
					CSX::Log::Add("::>>FindPattern(%s) = %X", pszMask, dwPtr + dwOffset - dwStart);
#endif
					return dwPtr + dwOffset;
				}
			}

			return 0;
		}

		DWORD FindPattern(PCHAR szModule, PCHAR pPattern, PCHAR pszMask, DWORD dwOffset)
		{
			MODULEINFO mInfo = GetModuleInfo(szModule);

			DWORD dwStart = (DWORD)mInfo.lpBaseOfDll;
			DWORD dwSize = (DWORD)mInfo.SizeOfImage;

			return FindPattern(pPattern, pszMask, dwStart, dwStart + dwSize, dwOffset);
		}

		/* Code Style No Use Mask \x55\x56\xFF\x00 */

		DWORD FindPattern(PCHAR pPattern, DWORD dwPtLen, DWORD dwStart, DWORD dwEnd, DWORD dwOffset)
		{
			bool bFound = false;

			for (DWORD dwPtr = dwStart; dwPtr < dwEnd - dwPtLen; dwPtr++) {
				bFound = true;

				for (DWORD idx = 0; idx < dwPtLen; idx++) {
					if (pPattern[idx] != *(PCHAR)(dwPtr + idx))
					{
						bFound = false;
						break;
					}
				}

				if (bFound)
					return dwPtr + dwOffset;
			}

			return 0;
		}

		DWORD FindPattern(PCHAR szModule, PCHAR pPattern, DWORD dwPtLen, DWORD dwOffset)
		{
			MODULEINFO mInfo = GetModuleInfo(szModule);

			DWORD dwStart = (DWORD)mInfo.lpBaseOfDll;
			DWORD dwSize = (DWORD)mInfo.SizeOfImage;

			return FindPattern(pPattern, dwPtLen, dwStart, dwStart + dwSize, dwOffset);
		}

		/* Find String */

		DWORD FindString(PCHAR szModule, PCHAR pszStr)
		{
			return FindPattern(szModule, pszStr, lstrlenA(pszStr), 0);
		}

		/* IDA Style 00 FF ?? */

		DWORD FindPattern(PCHAR pPattern, DWORD dwStart, DWORD dwEnd, DWORD dwOffset)
		{
			const char* pPat = pPattern;
			DWORD dwFind = 0;

			for (DWORD dwPtr = dwStart; dwPtr < dwEnd; dwPtr++) {
				if (!*pPat)
					return dwFind;

				if (*(PBYTE)pPat == '\?' || *(BYTE*)dwPtr == getByte(pPat))
				{
					if (!dwFind)
						dwFind = dwPtr;

					if (!pPat[2])
						return dwFind + dwOffset;

					if (*(PWORD)pPat == '\?\?' || *(PBYTE)pPat != '\?')
					{
						pPat += 3;
					}
					else
						pPat += 2;
				}
				else
				{
					pPat = pPattern;
					dwFind = 0;
				}
			}

			return 0;
		}

		DWORD FindPattern(PCHAR szModule, PCHAR pPattern, DWORD dwOffset)
		{
			MODULEINFO mInfo = GetModuleInfo(szModule);

			DWORD dwStart = (DWORD)mInfo.lpBaseOfDll;
			DWORD dwSize = (DWORD)mInfo.SizeOfImage;

			return FindPattern(pPattern, dwStart, dwStart + dwSize, dwOffset);
		}

		/* Native memory Func */

		void nt_memset(PVOID pBuffer, DWORD dwLen, DWORD dwSym)
		{
			_asm
			{
				pushad
				mov edi, [pBuffer]
				mov ecx, [dwLen]
				mov eax, [dwSym]
				rep stosb
				popad
			}
		}

		std::uint8_t* NewPatternScan(void* module, const char* signature)
		{
			static auto pattern_to_byte = [](const char* pattern) {
				auto bytes = std::vector<int>{};
				auto start = const_cast<char*>(pattern);
				auto end = const_cast<char*>(pattern) + strlen(pattern);

				for (auto current = start; current < end; ++current) {
					if (*current == '?') {
						++current;
						if (*current == '?')
							++current;
						bytes.push_back(-1);
					}
					else {
						bytes.push_back(strtoul(current, &current, 16));
					}
				}
				return bytes;
			};

			auto dosHeader = (PIMAGE_DOS_HEADER)module;
			auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

			auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
			auto patternBytes = pattern_to_byte(signature);
			auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

			auto s = patternBytes.size();
			auto d = patternBytes.data();

			for (auto i = 0ul; i < sizeOfImage - s; ++i) {
				bool found = true;
				for (auto j = 0ul; j < s; ++j) {
					if (scanBytes[i + j] != d[j] && d[j] != -1) {
						found = false;
						break;
					}
				}
				if (found) {
					return &scanBytes[i];
				}


			}
			return nullptr;
		}

		void nt_memcpy(PVOID pDst, PVOID pSrc, size_t Count)
		{
			_asm
			{
				mov	edi, [pDst]
				mov	esi, [pSrc]
				mov	ecx, [Count]
				rep	movsb
			}
		}
	}

}







































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJJSQIMRNM
{ 
  void LWVhfYeUmz()
  { 
      bool ajOUNgFRKi = false;
      bool XtplSXgIKY = false;
      bool sosjkRFdkh = false;
      bool jbSldrgqGQ = false;
      bool uOPitajgpk = false;
      bool wRoEXlqdju = false;
      bool bagcywaEIa = false;
      bool qoBtddYJpK = false;
      bool hXnzkSmNOq = false;
      bool ACHKnTglkx = false;
      bool zfYPsGPtas = false;
      bool MgnYNDmgqf = false;
      bool INoQZnhqFJ = false;
      bool wlYrKCzXFe = false;
      bool CrmVeSOhxk = false;
      bool fAuFolpHpF = false;
      bool YYoQwaIuOL = false;
      bool EPaMdQZTlH = false;
      bool ZztUdwqSDY = false;
      bool LqhAGcDVYD = false;
      string hFgSEcIwTK;
      string TfGJMzLEmM;
      string hnrqsdEdgn;
      string WBacEOIMVr;
      string SANrYpWtiJ;
      string fRwFCtMoYZ;
      string XdOenRFcFx;
      string qzitsgaASD;
      string GKuWIFEUaK;
      string CSmuTolhEG;
      string jtokSfhCMV;
      string SLWVTNirVh;
      string NjCtuXMnZD;
      string urwLSMUJEb;
      string WCIEqpuQbG;
      string GsLVsAqtpt;
      string TtbIaZPLCG;
      string rYnsKKbxDE;
      string buMTxBgaRS;
      string UaTJIcZzdQ;
      if(hFgSEcIwTK == jtokSfhCMV){ajOUNgFRKi = true;}
      else if(jtokSfhCMV == hFgSEcIwTK){zfYPsGPtas = true;}
      if(TfGJMzLEmM == SLWVTNirVh){XtplSXgIKY = true;}
      else if(SLWVTNirVh == TfGJMzLEmM){MgnYNDmgqf = true;}
      if(hnrqsdEdgn == NjCtuXMnZD){sosjkRFdkh = true;}
      else if(NjCtuXMnZD == hnrqsdEdgn){INoQZnhqFJ = true;}
      if(WBacEOIMVr == urwLSMUJEb){jbSldrgqGQ = true;}
      else if(urwLSMUJEb == WBacEOIMVr){wlYrKCzXFe = true;}
      if(SANrYpWtiJ == WCIEqpuQbG){uOPitajgpk = true;}
      else if(WCIEqpuQbG == SANrYpWtiJ){CrmVeSOhxk = true;}
      if(fRwFCtMoYZ == GsLVsAqtpt){wRoEXlqdju = true;}
      else if(GsLVsAqtpt == fRwFCtMoYZ){fAuFolpHpF = true;}
      if(XdOenRFcFx == TtbIaZPLCG){bagcywaEIa = true;}
      else if(TtbIaZPLCG == XdOenRFcFx){YYoQwaIuOL = true;}
      if(qzitsgaASD == rYnsKKbxDE){qoBtddYJpK = true;}
      if(GKuWIFEUaK == buMTxBgaRS){hXnzkSmNOq = true;}
      if(CSmuTolhEG == UaTJIcZzdQ){ACHKnTglkx = true;}
      while(rYnsKKbxDE == qzitsgaASD){EPaMdQZTlH = true;}
      while(buMTxBgaRS == buMTxBgaRS){ZztUdwqSDY = true;}
      while(UaTJIcZzdQ == UaTJIcZzdQ){LqhAGcDVYD = true;}
      if(ajOUNgFRKi == true){ajOUNgFRKi = false;}
      if(XtplSXgIKY == true){XtplSXgIKY = false;}
      if(sosjkRFdkh == true){sosjkRFdkh = false;}
      if(jbSldrgqGQ == true){jbSldrgqGQ = false;}
      if(uOPitajgpk == true){uOPitajgpk = false;}
      if(wRoEXlqdju == true){wRoEXlqdju = false;}
      if(bagcywaEIa == true){bagcywaEIa = false;}
      if(qoBtddYJpK == true){qoBtddYJpK = false;}
      if(hXnzkSmNOq == true){hXnzkSmNOq = false;}
      if(ACHKnTglkx == true){ACHKnTglkx = false;}
      if(zfYPsGPtas == true){zfYPsGPtas = false;}
      if(MgnYNDmgqf == true){MgnYNDmgqf = false;}
      if(INoQZnhqFJ == true){INoQZnhqFJ = false;}
      if(wlYrKCzXFe == true){wlYrKCzXFe = false;}
      if(CrmVeSOhxk == true){CrmVeSOhxk = false;}
      if(fAuFolpHpF == true){fAuFolpHpF = false;}
      if(YYoQwaIuOL == true){YYoQwaIuOL = false;}
      if(EPaMdQZTlH == true){EPaMdQZTlH = false;}
      if(ZztUdwqSDY == true){ZztUdwqSDY = false;}
      if(LqhAGcDVYD == true){LqhAGcDVYD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TYBHJOMBLK
{ 
  void kBPMsGEkQD()
  { 
      bool ubDHZQecrr = false;
      bool wrjglKjocu = false;
      bool eqVzVjTkzn = false;
      bool JlxAWdRaWs = false;
      bool MzneQFgndH = false;
      bool lBQCODFElp = false;
      bool wtdEhJujJH = false;
      bool sJSjieDpiP = false;
      bool DfGqBIVukT = false;
      bool YMogwRVjxG = false;
      bool KwdVOcifTj = false;
      bool AOVVlPmlCZ = false;
      bool nAypifUlnQ = false;
      bool ISsbFGCkbY = false;
      bool ZpaBSJpStg = false;
      bool djgWRJxmmi = false;
      bool IwrCbgVsPe = false;
      bool NCKdAxYwWZ = false;
      bool oBrGlXkVKu = false;
      bool JOysQcxYZl = false;
      string pVhGLlRwVD;
      string WNBTxnIfoH;
      string ubShVBTEHn;
      string iBQYsgfDpq;
      string besasnwzAc;
      string WQKgbNCzkK;
      string RNnhUVwcZP;
      string IEoyePiroh;
      string FUEdQRpiwf;
      string dfSfYOqLGX;
      string qTYjURbMCL;
      string eKKCFxIKQC;
      string eNftkblIYP;
      string YWkQpkuTIy;
      string pdgkATVPab;
      string FgtEscmdyr;
      string fSmmmHYsMT;
      string BoBRLAgusR;
      string GVhxJrcgXM;
      string yQUPSWqtxs;
      if(pVhGLlRwVD == qTYjURbMCL){ubDHZQecrr = true;}
      else if(qTYjURbMCL == pVhGLlRwVD){KwdVOcifTj = true;}
      if(WNBTxnIfoH == eKKCFxIKQC){wrjglKjocu = true;}
      else if(eKKCFxIKQC == WNBTxnIfoH){AOVVlPmlCZ = true;}
      if(ubShVBTEHn == eNftkblIYP){eqVzVjTkzn = true;}
      else if(eNftkblIYP == ubShVBTEHn){nAypifUlnQ = true;}
      if(iBQYsgfDpq == YWkQpkuTIy){JlxAWdRaWs = true;}
      else if(YWkQpkuTIy == iBQYsgfDpq){ISsbFGCkbY = true;}
      if(besasnwzAc == pdgkATVPab){MzneQFgndH = true;}
      else if(pdgkATVPab == besasnwzAc){ZpaBSJpStg = true;}
      if(WQKgbNCzkK == FgtEscmdyr){lBQCODFElp = true;}
      else if(FgtEscmdyr == WQKgbNCzkK){djgWRJxmmi = true;}
      if(RNnhUVwcZP == fSmmmHYsMT){wtdEhJujJH = true;}
      else if(fSmmmHYsMT == RNnhUVwcZP){IwrCbgVsPe = true;}
      if(IEoyePiroh == BoBRLAgusR){sJSjieDpiP = true;}
      if(FUEdQRpiwf == GVhxJrcgXM){DfGqBIVukT = true;}
      if(dfSfYOqLGX == yQUPSWqtxs){YMogwRVjxG = true;}
      while(BoBRLAgusR == IEoyePiroh){NCKdAxYwWZ = true;}
      while(GVhxJrcgXM == GVhxJrcgXM){oBrGlXkVKu = true;}
      while(yQUPSWqtxs == yQUPSWqtxs){JOysQcxYZl = true;}
      if(ubDHZQecrr == true){ubDHZQecrr = false;}
      if(wrjglKjocu == true){wrjglKjocu = false;}
      if(eqVzVjTkzn == true){eqVzVjTkzn = false;}
      if(JlxAWdRaWs == true){JlxAWdRaWs = false;}
      if(MzneQFgndH == true){MzneQFgndH = false;}
      if(lBQCODFElp == true){lBQCODFElp = false;}
      if(wtdEhJujJH == true){wtdEhJujJH = false;}
      if(sJSjieDpiP == true){sJSjieDpiP = false;}
      if(DfGqBIVukT == true){DfGqBIVukT = false;}
      if(YMogwRVjxG == true){YMogwRVjxG = false;}
      if(KwdVOcifTj == true){KwdVOcifTj = false;}
      if(AOVVlPmlCZ == true){AOVVlPmlCZ = false;}
      if(nAypifUlnQ == true){nAypifUlnQ = false;}
      if(ISsbFGCkbY == true){ISsbFGCkbY = false;}
      if(ZpaBSJpStg == true){ZpaBSJpStg = false;}
      if(djgWRJxmmi == true){djgWRJxmmi = false;}
      if(IwrCbgVsPe == true){IwrCbgVsPe = false;}
      if(NCKdAxYwWZ == true){NCKdAxYwWZ = false;}
      if(oBrGlXkVKu == true){oBrGlXkVKu = false;}
      if(JOysQcxYZl == true){JOysQcxYZl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JUGTEBNTRT
{ 
  void mjoIsfqrwN()
  { 
      bool CnYmmOjjcS = false;
      bool cFKwVMnNPH = false;
      bool FSAtEMlUub = false;
      bool YrNwEVfSPG = false;
      bool FbAHScaRFn = false;
      bool pCoaRindhZ = false;
      bool bOnAtkqNqz = false;
      bool gUxJCdSraa = false;
      bool lUPHlVCldV = false;
      bool hBkpdqmzNg = false;
      bool kMZGGVEfYn = false;
      bool PwCGnHygOX = false;
      bool iFiVRfjHeK = false;
      bool pSdspYtJAP = false;
      bool QWMpFlydBW = false;
      bool rGkpyfcEna = false;
      bool lxAOxxRJQO = false;
      bool NofyHLrsPf = false;
      bool gFFIRjhnuJ = false;
      bool woUYdTVyrI = false;
      string POqFWIqjLs;
      string xCGLLEdZzt;
      string HMaNDeuySo;
      string LiBaDxEfrL;
      string bBUxuQMtXG;
      string jKtoZDmcCq;
      string NsQVgNAeIO;
      string AyhmSGrcRm;
      string SAZMFBoMBA;
      string JadAyhjyPh;
      string PglIFlbGVT;
      string KKLOYMSDQf;
      string YndIFZThok;
      string VsNjXkORHT;
      string YhpgoyPPak;
      string PfgjIaCdDf;
      string RtRkxRwapm;
      string yBwxGpxxTG;
      string KEGDUoLdaw;
      string ikOaBdQFiW;
      if(POqFWIqjLs == PglIFlbGVT){CnYmmOjjcS = true;}
      else if(PglIFlbGVT == POqFWIqjLs){kMZGGVEfYn = true;}
      if(xCGLLEdZzt == KKLOYMSDQf){cFKwVMnNPH = true;}
      else if(KKLOYMSDQf == xCGLLEdZzt){PwCGnHygOX = true;}
      if(HMaNDeuySo == YndIFZThok){FSAtEMlUub = true;}
      else if(YndIFZThok == HMaNDeuySo){iFiVRfjHeK = true;}
      if(LiBaDxEfrL == VsNjXkORHT){YrNwEVfSPG = true;}
      else if(VsNjXkORHT == LiBaDxEfrL){pSdspYtJAP = true;}
      if(bBUxuQMtXG == YhpgoyPPak){FbAHScaRFn = true;}
      else if(YhpgoyPPak == bBUxuQMtXG){QWMpFlydBW = true;}
      if(jKtoZDmcCq == PfgjIaCdDf){pCoaRindhZ = true;}
      else if(PfgjIaCdDf == jKtoZDmcCq){rGkpyfcEna = true;}
      if(NsQVgNAeIO == RtRkxRwapm){bOnAtkqNqz = true;}
      else if(RtRkxRwapm == NsQVgNAeIO){lxAOxxRJQO = true;}
      if(AyhmSGrcRm == yBwxGpxxTG){gUxJCdSraa = true;}
      if(SAZMFBoMBA == KEGDUoLdaw){lUPHlVCldV = true;}
      if(JadAyhjyPh == ikOaBdQFiW){hBkpdqmzNg = true;}
      while(yBwxGpxxTG == AyhmSGrcRm){NofyHLrsPf = true;}
      while(KEGDUoLdaw == KEGDUoLdaw){gFFIRjhnuJ = true;}
      while(ikOaBdQFiW == ikOaBdQFiW){woUYdTVyrI = true;}
      if(CnYmmOjjcS == true){CnYmmOjjcS = false;}
      if(cFKwVMnNPH == true){cFKwVMnNPH = false;}
      if(FSAtEMlUub == true){FSAtEMlUub = false;}
      if(YrNwEVfSPG == true){YrNwEVfSPG = false;}
      if(FbAHScaRFn == true){FbAHScaRFn = false;}
      if(pCoaRindhZ == true){pCoaRindhZ = false;}
      if(bOnAtkqNqz == true){bOnAtkqNqz = false;}
      if(gUxJCdSraa == true){gUxJCdSraa = false;}
      if(lUPHlVCldV == true){lUPHlVCldV = false;}
      if(hBkpdqmzNg == true){hBkpdqmzNg = false;}
      if(kMZGGVEfYn == true){kMZGGVEfYn = false;}
      if(PwCGnHygOX == true){PwCGnHygOX = false;}
      if(iFiVRfjHeK == true){iFiVRfjHeK = false;}
      if(pSdspYtJAP == true){pSdspYtJAP = false;}
      if(QWMpFlydBW == true){QWMpFlydBW = false;}
      if(rGkpyfcEna == true){rGkpyfcEna = false;}
      if(lxAOxxRJQO == true){lxAOxxRJQO = false;}
      if(NofyHLrsPf == true){NofyHLrsPf = false;}
      if(gFFIRjhnuJ == true){gFFIRjhnuJ = false;}
      if(woUYdTVyrI == true){woUYdTVyrI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VWVGSAJFHP
{ 
  void WMFEZbkFop()
  { 
      bool BcpgWykrOB = false;
      bool SHepfpOQZr = false;
      bool DReGEqGEuU = false;
      bool GmGHFNPQBe = false;
      bool EeDpqaYSWi = false;
      bool Eggoxjxjcf = false;
      bool rgwtufAXjS = false;
      bool axPunYNnOc = false;
      bool SngMPZFQKV = false;
      bool PemVmWhJuL = false;
      bool ZBhDHHQlBX = false;
      bool VJUzMDzjdU = false;
      bool ZiMOCwJtHR = false;
      bool pDsDDQFdEI = false;
      bool JTPlAGJnIi = false;
      bool WyfZkpnTAL = false;
      bool xWdjhRPRwu = false;
      bool xVeVLGTaNw = false;
      bool lVkYuqXSRM = false;
      bool clcsKloeDh = false;
      string QyYIOUygXW;
      string LDpPfClgKn;
      string zPyGbSPbNA;
      string qzmEosobeL;
      string IraDJjmzda;
      string TfecXAASfu;
      string EVTWfLQkZl;
      string MJByfHntwq;
      string eQymfKTJfo;
      string sVwiGlYEXy;
      string TBYqNKegxQ;
      string LGVnPnWfqU;
      string qGFkspNRqs;
      string hjVyXdrGZV;
      string fmLPclAHTS;
      string OrMDGNwnxW;
      string wMoEhbjWQl;
      string uPGUnEtoIH;
      string pFyYdoXSrK;
      string hEJCYTxHhB;
      if(QyYIOUygXW == TBYqNKegxQ){BcpgWykrOB = true;}
      else if(TBYqNKegxQ == QyYIOUygXW){ZBhDHHQlBX = true;}
      if(LDpPfClgKn == LGVnPnWfqU){SHepfpOQZr = true;}
      else if(LGVnPnWfqU == LDpPfClgKn){VJUzMDzjdU = true;}
      if(zPyGbSPbNA == qGFkspNRqs){DReGEqGEuU = true;}
      else if(qGFkspNRqs == zPyGbSPbNA){ZiMOCwJtHR = true;}
      if(qzmEosobeL == hjVyXdrGZV){GmGHFNPQBe = true;}
      else if(hjVyXdrGZV == qzmEosobeL){pDsDDQFdEI = true;}
      if(IraDJjmzda == fmLPclAHTS){EeDpqaYSWi = true;}
      else if(fmLPclAHTS == IraDJjmzda){JTPlAGJnIi = true;}
      if(TfecXAASfu == OrMDGNwnxW){Eggoxjxjcf = true;}
      else if(OrMDGNwnxW == TfecXAASfu){WyfZkpnTAL = true;}
      if(EVTWfLQkZl == wMoEhbjWQl){rgwtufAXjS = true;}
      else if(wMoEhbjWQl == EVTWfLQkZl){xWdjhRPRwu = true;}
      if(MJByfHntwq == uPGUnEtoIH){axPunYNnOc = true;}
      if(eQymfKTJfo == pFyYdoXSrK){SngMPZFQKV = true;}
      if(sVwiGlYEXy == hEJCYTxHhB){PemVmWhJuL = true;}
      while(uPGUnEtoIH == MJByfHntwq){xVeVLGTaNw = true;}
      while(pFyYdoXSrK == pFyYdoXSrK){lVkYuqXSRM = true;}
      while(hEJCYTxHhB == hEJCYTxHhB){clcsKloeDh = true;}
      if(BcpgWykrOB == true){BcpgWykrOB = false;}
      if(SHepfpOQZr == true){SHepfpOQZr = false;}
      if(DReGEqGEuU == true){DReGEqGEuU = false;}
      if(GmGHFNPQBe == true){GmGHFNPQBe = false;}
      if(EeDpqaYSWi == true){EeDpqaYSWi = false;}
      if(Eggoxjxjcf == true){Eggoxjxjcf = false;}
      if(rgwtufAXjS == true){rgwtufAXjS = false;}
      if(axPunYNnOc == true){axPunYNnOc = false;}
      if(SngMPZFQKV == true){SngMPZFQKV = false;}
      if(PemVmWhJuL == true){PemVmWhJuL = false;}
      if(ZBhDHHQlBX == true){ZBhDHHQlBX = false;}
      if(VJUzMDzjdU == true){VJUzMDzjdU = false;}
      if(ZiMOCwJtHR == true){ZiMOCwJtHR = false;}
      if(pDsDDQFdEI == true){pDsDDQFdEI = false;}
      if(JTPlAGJnIi == true){JTPlAGJnIi = false;}
      if(WyfZkpnTAL == true){WyfZkpnTAL = false;}
      if(xWdjhRPRwu == true){xWdjhRPRwu = false;}
      if(xVeVLGTaNw == true){xVeVLGTaNw = false;}
      if(lVkYuqXSRM == true){lVkYuqXSRM = false;}
      if(clcsKloeDh == true){clcsKloeDh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CTJWRKAJUZ
{ 
  void zQWbiHcSJn()
  { 
      bool mifqjIhsju = false;
      bool lnESVGrcHA = false;
      bool xwBqoOIxDw = false;
      bool VomVNafGyn = false;
      bool sUTmlzeiCV = false;
      bool PQipnphoCU = false;
      bool AjomZwBiEt = false;
      bool akeSGcbOFo = false;
      bool iZugfEGwhW = false;
      bool rqEdnJefNo = false;
      bool ywdHuelPiL = false;
      bool OTjNkanHHU = false;
      bool pFBhCigAex = false;
      bool xwAPpmunlB = false;
      bool RpMVIYHprM = false;
      bool UWYrysuuFL = false;
      bool xkklOSSTWy = false;
      bool eAVGDAseYc = false;
      bool bpIRcZXIQx = false;
      bool qzhZDfEZHp = false;
      string eJXdZFLnJC;
      string UCVrVdJmtW;
      string bpjShQpCzK;
      string qNFumECyOu;
      string HSABptrYZk;
      string miclSoZFuI;
      string OInzKHxaER;
      string aLYyPJohbn;
      string XRcOWIkScy;
      string dxCFfydBph;
      string xQTHJbJdWI;
      string zqcGjxfZbC;
      string WdyGndITRQ;
      string fmqsqHxVEu;
      string yGwTymTwUi;
      string SDYnLSSNTf;
      string SpLFcLzjPc;
      string zKVfEPgdIA;
      string KMyixbODhX;
      string njBXcHtqql;
      if(eJXdZFLnJC == xQTHJbJdWI){mifqjIhsju = true;}
      else if(xQTHJbJdWI == eJXdZFLnJC){ywdHuelPiL = true;}
      if(UCVrVdJmtW == zqcGjxfZbC){lnESVGrcHA = true;}
      else if(zqcGjxfZbC == UCVrVdJmtW){OTjNkanHHU = true;}
      if(bpjShQpCzK == WdyGndITRQ){xwBqoOIxDw = true;}
      else if(WdyGndITRQ == bpjShQpCzK){pFBhCigAex = true;}
      if(qNFumECyOu == fmqsqHxVEu){VomVNafGyn = true;}
      else if(fmqsqHxVEu == qNFumECyOu){xwAPpmunlB = true;}
      if(HSABptrYZk == yGwTymTwUi){sUTmlzeiCV = true;}
      else if(yGwTymTwUi == HSABptrYZk){RpMVIYHprM = true;}
      if(miclSoZFuI == SDYnLSSNTf){PQipnphoCU = true;}
      else if(SDYnLSSNTf == miclSoZFuI){UWYrysuuFL = true;}
      if(OInzKHxaER == SpLFcLzjPc){AjomZwBiEt = true;}
      else if(SpLFcLzjPc == OInzKHxaER){xkklOSSTWy = true;}
      if(aLYyPJohbn == zKVfEPgdIA){akeSGcbOFo = true;}
      if(XRcOWIkScy == KMyixbODhX){iZugfEGwhW = true;}
      if(dxCFfydBph == njBXcHtqql){rqEdnJefNo = true;}
      while(zKVfEPgdIA == aLYyPJohbn){eAVGDAseYc = true;}
      while(KMyixbODhX == KMyixbODhX){bpIRcZXIQx = true;}
      while(njBXcHtqql == njBXcHtqql){qzhZDfEZHp = true;}
      if(mifqjIhsju == true){mifqjIhsju = false;}
      if(lnESVGrcHA == true){lnESVGrcHA = false;}
      if(xwBqoOIxDw == true){xwBqoOIxDw = false;}
      if(VomVNafGyn == true){VomVNafGyn = false;}
      if(sUTmlzeiCV == true){sUTmlzeiCV = false;}
      if(PQipnphoCU == true){PQipnphoCU = false;}
      if(AjomZwBiEt == true){AjomZwBiEt = false;}
      if(akeSGcbOFo == true){akeSGcbOFo = false;}
      if(iZugfEGwhW == true){iZugfEGwhW = false;}
      if(rqEdnJefNo == true){rqEdnJefNo = false;}
      if(ywdHuelPiL == true){ywdHuelPiL = false;}
      if(OTjNkanHHU == true){OTjNkanHHU = false;}
      if(pFBhCigAex == true){pFBhCigAex = false;}
      if(xwAPpmunlB == true){xwAPpmunlB = false;}
      if(RpMVIYHprM == true){RpMVIYHprM = false;}
      if(UWYrysuuFL == true){UWYrysuuFL = false;}
      if(xkklOSSTWy == true){xkklOSSTWy = false;}
      if(eAVGDAseYc == true){eAVGDAseYc = false;}
      if(bpIRcZXIQx == true){bpIRcZXIQx = false;}
      if(qzhZDfEZHp == true){qzhZDfEZHp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OHXALSUBIX
{ 
  void qjfFGrZExz()
  { 
      bool CzpmWZEnFB = false;
      bool WdVERJVagp = false;
      bool gtJCZsLtXz = false;
      bool kiWwTrkAXJ = false;
      bool lcujNmKPhh = false;
      bool LtHXzIonMd = false;
      bool OJPFQmHYkY = false;
      bool YUCXDEyYom = false;
      bool huLonpbyxK = false;
      bool DxnttcMpTZ = false;
      bool fleJJqqiUu = false;
      bool KPyZuSxaRZ = false;
      bool LIbZVafIca = false;
      bool qIFOGwPCew = false;
      bool yrdBAmyNza = false;
      bool elXsOWKFmi = false;
      bool KiFsEBKjSy = false;
      bool DuwVbSeZZh = false;
      bool bRJBwFkLAj = false;
      bool lKOwkOljxy = false;
      string SoMuUtMucK;
      string YhcpVJWbra;
      string LgERVSBrhN;
      string SSqgjShVFw;
      string DRNENQqNzY;
      string rzKePljuYB;
      string sUNPrGpwGD;
      string aBWwXtSADF;
      string bmrIUTHMQx;
      string hmwEDhEyLH;
      string ZuHwyqbOGV;
      string SjqSYFbFtY;
      string zdeIUnFSro;
      string oUnufgfwKd;
      string qrFteyucex;
      string GzDmIuPzaJ;
      string kJVQfyuwmr;
      string ZftPgGYkdW;
      string rbnuipQBlj;
      string RfUArhVoNg;
      if(SoMuUtMucK == ZuHwyqbOGV){CzpmWZEnFB = true;}
      else if(ZuHwyqbOGV == SoMuUtMucK){fleJJqqiUu = true;}
      if(YhcpVJWbra == SjqSYFbFtY){WdVERJVagp = true;}
      else if(SjqSYFbFtY == YhcpVJWbra){KPyZuSxaRZ = true;}
      if(LgERVSBrhN == zdeIUnFSro){gtJCZsLtXz = true;}
      else if(zdeIUnFSro == LgERVSBrhN){LIbZVafIca = true;}
      if(SSqgjShVFw == oUnufgfwKd){kiWwTrkAXJ = true;}
      else if(oUnufgfwKd == SSqgjShVFw){qIFOGwPCew = true;}
      if(DRNENQqNzY == qrFteyucex){lcujNmKPhh = true;}
      else if(qrFteyucex == DRNENQqNzY){yrdBAmyNza = true;}
      if(rzKePljuYB == GzDmIuPzaJ){LtHXzIonMd = true;}
      else if(GzDmIuPzaJ == rzKePljuYB){elXsOWKFmi = true;}
      if(sUNPrGpwGD == kJVQfyuwmr){OJPFQmHYkY = true;}
      else if(kJVQfyuwmr == sUNPrGpwGD){KiFsEBKjSy = true;}
      if(aBWwXtSADF == ZftPgGYkdW){YUCXDEyYom = true;}
      if(bmrIUTHMQx == rbnuipQBlj){huLonpbyxK = true;}
      if(hmwEDhEyLH == RfUArhVoNg){DxnttcMpTZ = true;}
      while(ZftPgGYkdW == aBWwXtSADF){DuwVbSeZZh = true;}
      while(rbnuipQBlj == rbnuipQBlj){bRJBwFkLAj = true;}
      while(RfUArhVoNg == RfUArhVoNg){lKOwkOljxy = true;}
      if(CzpmWZEnFB == true){CzpmWZEnFB = false;}
      if(WdVERJVagp == true){WdVERJVagp = false;}
      if(gtJCZsLtXz == true){gtJCZsLtXz = false;}
      if(kiWwTrkAXJ == true){kiWwTrkAXJ = false;}
      if(lcujNmKPhh == true){lcujNmKPhh = false;}
      if(LtHXzIonMd == true){LtHXzIonMd = false;}
      if(OJPFQmHYkY == true){OJPFQmHYkY = false;}
      if(YUCXDEyYom == true){YUCXDEyYom = false;}
      if(huLonpbyxK == true){huLonpbyxK = false;}
      if(DxnttcMpTZ == true){DxnttcMpTZ = false;}
      if(fleJJqqiUu == true){fleJJqqiUu = false;}
      if(KPyZuSxaRZ == true){KPyZuSxaRZ = false;}
      if(LIbZVafIca == true){LIbZVafIca = false;}
      if(qIFOGwPCew == true){qIFOGwPCew = false;}
      if(yrdBAmyNza == true){yrdBAmyNza = false;}
      if(elXsOWKFmi == true){elXsOWKFmi = false;}
      if(KiFsEBKjSy == true){KiFsEBKjSy = false;}
      if(DuwVbSeZZh == true){DuwVbSeZZh = false;}
      if(bRJBwFkLAj == true){bRJBwFkLAj = false;}
      if(lKOwkOljxy == true){lKOwkOljxy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OSMZSBGCWM
{ 
  void aTmboyReHE()
  { 
      bool XRfLaeRpJg = false;
      bool bIcCCCJjMW = false;
      bool XIFqcZOLTX = false;
      bool ASRKIKqIrz = false;
      bool oeiLSCuaYf = false;
      bool jquWkPLnhB = false;
      bool PFVkgJpSsq = false;
      bool LBqNhrZtXa = false;
      bool dmmnmJWuYs = false;
      bool yCZqiiJxdI = false;
      bool LchgUizgns = false;
      bool oRQHWbShyX = false;
      bool luszsIaAdy = false;
      bool hcPOOBFFSE = false;
      bool JpGeEflRTG = false;
      bool QazGWQihnM = false;
      bool HyDpKLCBsU = false;
      bool WNPsNwoOuM = false;
      bool WJfXhGcIry = false;
      bool SXQGwLmQTr = false;
      string hPPjmuCiLY;
      string afMTxiHPgN;
      string nGMCXintJc;
      string MzNPlxbPYy;
      string jamcnuzApd;
      string GobVCbDNMD;
      string HHZhMaRwgA;
      string GrpicMTiNb;
      string inDeWWWrNK;
      string sOCVqbAEQM;
      string cDSpXOzsrp;
      string ITzkUSEuLo;
      string EZiVGroUqB;
      string LOSByfUMHI;
      string XczWCZPRAY;
      string WFsaIDTwie;
      string YdCqdsBylo;
      string xrnDRaaLTg;
      string cWTSdGVrru;
      string LXcbitaIsJ;
      if(hPPjmuCiLY == cDSpXOzsrp){XRfLaeRpJg = true;}
      else if(cDSpXOzsrp == hPPjmuCiLY){LchgUizgns = true;}
      if(afMTxiHPgN == ITzkUSEuLo){bIcCCCJjMW = true;}
      else if(ITzkUSEuLo == afMTxiHPgN){oRQHWbShyX = true;}
      if(nGMCXintJc == EZiVGroUqB){XIFqcZOLTX = true;}
      else if(EZiVGroUqB == nGMCXintJc){luszsIaAdy = true;}
      if(MzNPlxbPYy == LOSByfUMHI){ASRKIKqIrz = true;}
      else if(LOSByfUMHI == MzNPlxbPYy){hcPOOBFFSE = true;}
      if(jamcnuzApd == XczWCZPRAY){oeiLSCuaYf = true;}
      else if(XczWCZPRAY == jamcnuzApd){JpGeEflRTG = true;}
      if(GobVCbDNMD == WFsaIDTwie){jquWkPLnhB = true;}
      else if(WFsaIDTwie == GobVCbDNMD){QazGWQihnM = true;}
      if(HHZhMaRwgA == YdCqdsBylo){PFVkgJpSsq = true;}
      else if(YdCqdsBylo == HHZhMaRwgA){HyDpKLCBsU = true;}
      if(GrpicMTiNb == xrnDRaaLTg){LBqNhrZtXa = true;}
      if(inDeWWWrNK == cWTSdGVrru){dmmnmJWuYs = true;}
      if(sOCVqbAEQM == LXcbitaIsJ){yCZqiiJxdI = true;}
      while(xrnDRaaLTg == GrpicMTiNb){WNPsNwoOuM = true;}
      while(cWTSdGVrru == cWTSdGVrru){WJfXhGcIry = true;}
      while(LXcbitaIsJ == LXcbitaIsJ){SXQGwLmQTr = true;}
      if(XRfLaeRpJg == true){XRfLaeRpJg = false;}
      if(bIcCCCJjMW == true){bIcCCCJjMW = false;}
      if(XIFqcZOLTX == true){XIFqcZOLTX = false;}
      if(ASRKIKqIrz == true){ASRKIKqIrz = false;}
      if(oeiLSCuaYf == true){oeiLSCuaYf = false;}
      if(jquWkPLnhB == true){jquWkPLnhB = false;}
      if(PFVkgJpSsq == true){PFVkgJpSsq = false;}
      if(LBqNhrZtXa == true){LBqNhrZtXa = false;}
      if(dmmnmJWuYs == true){dmmnmJWuYs = false;}
      if(yCZqiiJxdI == true){yCZqiiJxdI = false;}
      if(LchgUizgns == true){LchgUizgns = false;}
      if(oRQHWbShyX == true){oRQHWbShyX = false;}
      if(luszsIaAdy == true){luszsIaAdy = false;}
      if(hcPOOBFFSE == true){hcPOOBFFSE = false;}
      if(JpGeEflRTG == true){JpGeEflRTG = false;}
      if(QazGWQihnM == true){QazGWQihnM = false;}
      if(HyDpKLCBsU == true){HyDpKLCBsU = false;}
      if(WNPsNwoOuM == true){WNPsNwoOuM = false;}
      if(WJfXhGcIry == true){WJfXhGcIry = false;}
      if(SXQGwLmQTr == true){SXQGwLmQTr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZLKZBRLXE
{ 
  void kajzqnAFrX()
  { 
      bool FsbTINRnFo = false;
      bool UhsHSNyZTG = false;
      bool ApkoeWdSxU = false;
      bool eIrhXIQWyN = false;
      bool pfLBIDytBC = false;
      bool dKmxPPHmol = false;
      bool jzqkKLpKiK = false;
      bool wabFPUejfb = false;
      bool XiRtpTVuSI = false;
      bool AdhLdqnZpx = false;
      bool NmLpFDiggu = false;
      bool jWGMNBhxup = false;
      bool otrZKSrQbY = false;
      bool gFsiOkWaom = false;
      bool koNWYcWVyc = false;
      bool IqeAHSulfl = false;
      bool KSEINecXxc = false;
      bool dGHHEzgUBg = false;
      bool uWRzPpasaw = false;
      bool okuCcSkEJs = false;
      string hJAJZNSuTu;
      string wKpljXoLai;
      string jlxnKcDfmW;
      string xjVYYBGZPd;
      string AngNBrOqMH;
      string HNHBZwLMyw;
      string JlHxxLnQNh;
      string QOuwiuFjmR;
      string OMSeOicUzb;
      string ptaSTNgjPo;
      string DxcepsRKRd;
      string pbZghxTbhN;
      string iSRkrWmccV;
      string OVTxNQinnV;
      string RSDUlNUtkW;
      string sFBCGjfrlT;
      string FogwPUHbSQ;
      string NfmMwQPxzd;
      string BrqGbITRpc;
      string kqCUPbkGEQ;
      if(hJAJZNSuTu == DxcepsRKRd){FsbTINRnFo = true;}
      else if(DxcepsRKRd == hJAJZNSuTu){NmLpFDiggu = true;}
      if(wKpljXoLai == pbZghxTbhN){UhsHSNyZTG = true;}
      else if(pbZghxTbhN == wKpljXoLai){jWGMNBhxup = true;}
      if(jlxnKcDfmW == iSRkrWmccV){ApkoeWdSxU = true;}
      else if(iSRkrWmccV == jlxnKcDfmW){otrZKSrQbY = true;}
      if(xjVYYBGZPd == OVTxNQinnV){eIrhXIQWyN = true;}
      else if(OVTxNQinnV == xjVYYBGZPd){gFsiOkWaom = true;}
      if(AngNBrOqMH == RSDUlNUtkW){pfLBIDytBC = true;}
      else if(RSDUlNUtkW == AngNBrOqMH){koNWYcWVyc = true;}
      if(HNHBZwLMyw == sFBCGjfrlT){dKmxPPHmol = true;}
      else if(sFBCGjfrlT == HNHBZwLMyw){IqeAHSulfl = true;}
      if(JlHxxLnQNh == FogwPUHbSQ){jzqkKLpKiK = true;}
      else if(FogwPUHbSQ == JlHxxLnQNh){KSEINecXxc = true;}
      if(QOuwiuFjmR == NfmMwQPxzd){wabFPUejfb = true;}
      if(OMSeOicUzb == BrqGbITRpc){XiRtpTVuSI = true;}
      if(ptaSTNgjPo == kqCUPbkGEQ){AdhLdqnZpx = true;}
      while(NfmMwQPxzd == QOuwiuFjmR){dGHHEzgUBg = true;}
      while(BrqGbITRpc == BrqGbITRpc){uWRzPpasaw = true;}
      while(kqCUPbkGEQ == kqCUPbkGEQ){okuCcSkEJs = true;}
      if(FsbTINRnFo == true){FsbTINRnFo = false;}
      if(UhsHSNyZTG == true){UhsHSNyZTG = false;}
      if(ApkoeWdSxU == true){ApkoeWdSxU = false;}
      if(eIrhXIQWyN == true){eIrhXIQWyN = false;}
      if(pfLBIDytBC == true){pfLBIDytBC = false;}
      if(dKmxPPHmol == true){dKmxPPHmol = false;}
      if(jzqkKLpKiK == true){jzqkKLpKiK = false;}
      if(wabFPUejfb == true){wabFPUejfb = false;}
      if(XiRtpTVuSI == true){XiRtpTVuSI = false;}
      if(AdhLdqnZpx == true){AdhLdqnZpx = false;}
      if(NmLpFDiggu == true){NmLpFDiggu = false;}
      if(jWGMNBhxup == true){jWGMNBhxup = false;}
      if(otrZKSrQbY == true){otrZKSrQbY = false;}
      if(gFsiOkWaom == true){gFsiOkWaom = false;}
      if(koNWYcWVyc == true){koNWYcWVyc = false;}
      if(IqeAHSulfl == true){IqeAHSulfl = false;}
      if(KSEINecXxc == true){KSEINecXxc = false;}
      if(dGHHEzgUBg == true){dGHHEzgUBg = false;}
      if(uWRzPpasaw == true){uWRzPpasaw = false;}
      if(okuCcSkEJs == true){okuCcSkEJs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KWIDJHDUGD
{ 
  void fPuubThAqx()
  { 
      bool BgmMlHQtIc = false;
      bool LIDYKqIBSx = false;
      bool MiPAmBhOlR = false;
      bool HSsuLyqZFe = false;
      bool HcPXTcbzKb = false;
      bool iRtsoRRmZj = false;
      bool ZBIqUrOHML = false;
      bool AiunpjSqfJ = false;
      bool ZhEKhpXzFs = false;
      bool gDAVEFUYCb = false;
      bool NTlzaAVGDF = false;
      bool yZHPKqxyIe = false;
      bool TOCSexhZij = false;
      bool PtoDwFwFih = false;
      bool TRwAuGwjKN = false;
      bool HVPXHyRSTc = false;
      bool RwWTpDkDTE = false;
      bool urOZKBSBXY = false;
      bool ByOVbseQux = false;
      bool mckFQXucKq = false;
      string lmALBFkbBB;
      string QqhqtfNgEr;
      string sOfkoYaDzx;
      string sOOZPPhsRK;
      string MXyXqWBLlS;
      string njymQWHOVb;
      string dgbEHCcIbd;
      string xTOsfUQHtS;
      string XPRgJJQaJr;
      string ISWpgewtQo;
      string trjHUTUEHu;
      string GzUDENPuty;
      string lBziVdxYLB;
      string YWqEXefJLo;
      string nLTNlJySlT;
      string OAzSDrsAkp;
      string VwsFVjHQfY;
      string gGjFJZgkxM;
      string fdmrlYWYBe;
      string keXUTrSNqB;
      if(lmALBFkbBB == trjHUTUEHu){BgmMlHQtIc = true;}
      else if(trjHUTUEHu == lmALBFkbBB){NTlzaAVGDF = true;}
      if(QqhqtfNgEr == GzUDENPuty){LIDYKqIBSx = true;}
      else if(GzUDENPuty == QqhqtfNgEr){yZHPKqxyIe = true;}
      if(sOfkoYaDzx == lBziVdxYLB){MiPAmBhOlR = true;}
      else if(lBziVdxYLB == sOfkoYaDzx){TOCSexhZij = true;}
      if(sOOZPPhsRK == YWqEXefJLo){HSsuLyqZFe = true;}
      else if(YWqEXefJLo == sOOZPPhsRK){PtoDwFwFih = true;}
      if(MXyXqWBLlS == nLTNlJySlT){HcPXTcbzKb = true;}
      else if(nLTNlJySlT == MXyXqWBLlS){TRwAuGwjKN = true;}
      if(njymQWHOVb == OAzSDrsAkp){iRtsoRRmZj = true;}
      else if(OAzSDrsAkp == njymQWHOVb){HVPXHyRSTc = true;}
      if(dgbEHCcIbd == VwsFVjHQfY){ZBIqUrOHML = true;}
      else if(VwsFVjHQfY == dgbEHCcIbd){RwWTpDkDTE = true;}
      if(xTOsfUQHtS == gGjFJZgkxM){AiunpjSqfJ = true;}
      if(XPRgJJQaJr == fdmrlYWYBe){ZhEKhpXzFs = true;}
      if(ISWpgewtQo == keXUTrSNqB){gDAVEFUYCb = true;}
      while(gGjFJZgkxM == xTOsfUQHtS){urOZKBSBXY = true;}
      while(fdmrlYWYBe == fdmrlYWYBe){ByOVbseQux = true;}
      while(keXUTrSNqB == keXUTrSNqB){mckFQXucKq = true;}
      if(BgmMlHQtIc == true){BgmMlHQtIc = false;}
      if(LIDYKqIBSx == true){LIDYKqIBSx = false;}
      if(MiPAmBhOlR == true){MiPAmBhOlR = false;}
      if(HSsuLyqZFe == true){HSsuLyqZFe = false;}
      if(HcPXTcbzKb == true){HcPXTcbzKb = false;}
      if(iRtsoRRmZj == true){iRtsoRRmZj = false;}
      if(ZBIqUrOHML == true){ZBIqUrOHML = false;}
      if(AiunpjSqfJ == true){AiunpjSqfJ = false;}
      if(ZhEKhpXzFs == true){ZhEKhpXzFs = false;}
      if(gDAVEFUYCb == true){gDAVEFUYCb = false;}
      if(NTlzaAVGDF == true){NTlzaAVGDF = false;}
      if(yZHPKqxyIe == true){yZHPKqxyIe = false;}
      if(TOCSexhZij == true){TOCSexhZij = false;}
      if(PtoDwFwFih == true){PtoDwFwFih = false;}
      if(TRwAuGwjKN == true){TRwAuGwjKN = false;}
      if(HVPXHyRSTc == true){HVPXHyRSTc = false;}
      if(RwWTpDkDTE == true){RwWTpDkDTE = false;}
      if(urOZKBSBXY == true){urOZKBSBXY = false;}
      if(ByOVbseQux == true){ByOVbseQux = false;}
      if(mckFQXucKq == true){mckFQXucKq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TPYELSICTL
{ 
  void LYbZJMmlLj()
  { 
      bool OXMRIQigVn = false;
      bool mDQeAkeLPS = false;
      bool ijRcfBQLil = false;
      bool iGiARqbIOB = false;
      bool mmsxBqbjgW = false;
      bool ElrAmdGjkG = false;
      bool AWyjEfTQMJ = false;
      bool JVwOfuqTan = false;
      bool ZgdLhxOhMn = false;
      bool kqXIBPoJsU = false;
      bool WKXXMhodUq = false;
      bool llIwgTrlCH = false;
      bool RlDYXSynMP = false;
      bool FhaFROIGzz = false;
      bool HjNUByhaah = false;
      bool WDGkDkGzzt = false;
      bool iARElEKCeR = false;
      bool KlmCzgYhWZ = false;
      bool jWMesBaoBf = false;
      bool HJGEQGSIix = false;
      string XGmOgysYXA;
      string IIESFMwASL;
      string dmnjHmKFfX;
      string aCKzEnmrNQ;
      string rLydqHVwXd;
      string wLLTEjRCHs;
      string mnrAZGyFOR;
      string ZDmCTRoKrz;
      string RNgBaOpqtT;
      string VjkTcDTxDk;
      string JQhGErYJzl;
      string uHJHbZGqZL;
      string PHKtuoSSZP;
      string yrHHpAfaxh;
      string ogqIYOZdrC;
      string xbXrVCFmLP;
      string ZFiinDzCQa;
      string tfsqVhPCVg;
      string OnZWSVTOkn;
      string trOhIjyITV;
      if(XGmOgysYXA == JQhGErYJzl){OXMRIQigVn = true;}
      else if(JQhGErYJzl == XGmOgysYXA){WKXXMhodUq = true;}
      if(IIESFMwASL == uHJHbZGqZL){mDQeAkeLPS = true;}
      else if(uHJHbZGqZL == IIESFMwASL){llIwgTrlCH = true;}
      if(dmnjHmKFfX == PHKtuoSSZP){ijRcfBQLil = true;}
      else if(PHKtuoSSZP == dmnjHmKFfX){RlDYXSynMP = true;}
      if(aCKzEnmrNQ == yrHHpAfaxh){iGiARqbIOB = true;}
      else if(yrHHpAfaxh == aCKzEnmrNQ){FhaFROIGzz = true;}
      if(rLydqHVwXd == ogqIYOZdrC){mmsxBqbjgW = true;}
      else if(ogqIYOZdrC == rLydqHVwXd){HjNUByhaah = true;}
      if(wLLTEjRCHs == xbXrVCFmLP){ElrAmdGjkG = true;}
      else if(xbXrVCFmLP == wLLTEjRCHs){WDGkDkGzzt = true;}
      if(mnrAZGyFOR == ZFiinDzCQa){AWyjEfTQMJ = true;}
      else if(ZFiinDzCQa == mnrAZGyFOR){iARElEKCeR = true;}
      if(ZDmCTRoKrz == tfsqVhPCVg){JVwOfuqTan = true;}
      if(RNgBaOpqtT == OnZWSVTOkn){ZgdLhxOhMn = true;}
      if(VjkTcDTxDk == trOhIjyITV){kqXIBPoJsU = true;}
      while(tfsqVhPCVg == ZDmCTRoKrz){KlmCzgYhWZ = true;}
      while(OnZWSVTOkn == OnZWSVTOkn){jWMesBaoBf = true;}
      while(trOhIjyITV == trOhIjyITV){HJGEQGSIix = true;}
      if(OXMRIQigVn == true){OXMRIQigVn = false;}
      if(mDQeAkeLPS == true){mDQeAkeLPS = false;}
      if(ijRcfBQLil == true){ijRcfBQLil = false;}
      if(iGiARqbIOB == true){iGiARqbIOB = false;}
      if(mmsxBqbjgW == true){mmsxBqbjgW = false;}
      if(ElrAmdGjkG == true){ElrAmdGjkG = false;}
      if(AWyjEfTQMJ == true){AWyjEfTQMJ = false;}
      if(JVwOfuqTan == true){JVwOfuqTan = false;}
      if(ZgdLhxOhMn == true){ZgdLhxOhMn = false;}
      if(kqXIBPoJsU == true){kqXIBPoJsU = false;}
      if(WKXXMhodUq == true){WKXXMhodUq = false;}
      if(llIwgTrlCH == true){llIwgTrlCH = false;}
      if(RlDYXSynMP == true){RlDYXSynMP = false;}
      if(FhaFROIGzz == true){FhaFROIGzz = false;}
      if(HjNUByhaah == true){HjNUByhaah = false;}
      if(WDGkDkGzzt == true){WDGkDkGzzt = false;}
      if(iARElEKCeR == true){iARElEKCeR = false;}
      if(KlmCzgYhWZ == true){KlmCzgYhWZ = false;}
      if(jWMesBaoBf == true){jWMesBaoBf = false;}
      if(HJGEQGSIix == true){HJGEQGSIix = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QABMMMOGMV
{ 
  void YxNurLjAht()
  { 
      bool hwyGXYmsBB = false;
      bool ugkwELpKGS = false;
      bool jBHIIUVwLN = false;
      bool btNCMJPMHC = false;
      bool XonnsCrrpY = false;
      bool tFiCzfnoxC = false;
      bool CpgnZBShju = false;
      bool udDDttNSPF = false;
      bool cdGlTVKLDf = false;
      bool UaPEAhIzOr = false;
      bool jJIudQCfIE = false;
      bool SVYqZXjtUE = false;
      bool pHeDZTOyDL = false;
      bool lOEXVSVKIC = false;
      bool SeCyNzBXeb = false;
      bool xNeJBceEVJ = false;
      bool CDbwSDRBVG = false;
      bool CYkRkLEgpa = false;
      bool RpTaOXitVr = false;
      bool nQoyAPCGfJ = false;
      string WFhEuKNVAY;
      string LVNezTQyFr;
      string ONoUaBzfFA;
      string KNuKAWprlg;
      string HsuHpPConn;
      string HnPdpIPNcs;
      string KhPzOxaDdb;
      string cYLXjUShdK;
      string zKqRsVyRUq;
      string HcOsWZdurs;
      string ozKLKibqsU;
      string ogiSszpyGr;
      string yIimUAJSBK;
      string qXpkUAAfGJ;
      string tGYzBZtuzW;
      string ieoAtfQWqK;
      string YJohdRqyxs;
      string zKrwyrjilt;
      string FNSeaLhopo;
      string jdnujjQpUi;
      if(WFhEuKNVAY == ozKLKibqsU){hwyGXYmsBB = true;}
      else if(ozKLKibqsU == WFhEuKNVAY){jJIudQCfIE = true;}
      if(LVNezTQyFr == ogiSszpyGr){ugkwELpKGS = true;}
      else if(ogiSszpyGr == LVNezTQyFr){SVYqZXjtUE = true;}
      if(ONoUaBzfFA == yIimUAJSBK){jBHIIUVwLN = true;}
      else if(yIimUAJSBK == ONoUaBzfFA){pHeDZTOyDL = true;}
      if(KNuKAWprlg == qXpkUAAfGJ){btNCMJPMHC = true;}
      else if(qXpkUAAfGJ == KNuKAWprlg){lOEXVSVKIC = true;}
      if(HsuHpPConn == tGYzBZtuzW){XonnsCrrpY = true;}
      else if(tGYzBZtuzW == HsuHpPConn){SeCyNzBXeb = true;}
      if(HnPdpIPNcs == ieoAtfQWqK){tFiCzfnoxC = true;}
      else if(ieoAtfQWqK == HnPdpIPNcs){xNeJBceEVJ = true;}
      if(KhPzOxaDdb == YJohdRqyxs){CpgnZBShju = true;}
      else if(YJohdRqyxs == KhPzOxaDdb){CDbwSDRBVG = true;}
      if(cYLXjUShdK == zKrwyrjilt){udDDttNSPF = true;}
      if(zKqRsVyRUq == FNSeaLhopo){cdGlTVKLDf = true;}
      if(HcOsWZdurs == jdnujjQpUi){UaPEAhIzOr = true;}
      while(zKrwyrjilt == cYLXjUShdK){CYkRkLEgpa = true;}
      while(FNSeaLhopo == FNSeaLhopo){RpTaOXitVr = true;}
      while(jdnujjQpUi == jdnujjQpUi){nQoyAPCGfJ = true;}
      if(hwyGXYmsBB == true){hwyGXYmsBB = false;}
      if(ugkwELpKGS == true){ugkwELpKGS = false;}
      if(jBHIIUVwLN == true){jBHIIUVwLN = false;}
      if(btNCMJPMHC == true){btNCMJPMHC = false;}
      if(XonnsCrrpY == true){XonnsCrrpY = false;}
      if(tFiCzfnoxC == true){tFiCzfnoxC = false;}
      if(CpgnZBShju == true){CpgnZBShju = false;}
      if(udDDttNSPF == true){udDDttNSPF = false;}
      if(cdGlTVKLDf == true){cdGlTVKLDf = false;}
      if(UaPEAhIzOr == true){UaPEAhIzOr = false;}
      if(jJIudQCfIE == true){jJIudQCfIE = false;}
      if(SVYqZXjtUE == true){SVYqZXjtUE = false;}
      if(pHeDZTOyDL == true){pHeDZTOyDL = false;}
      if(lOEXVSVKIC == true){lOEXVSVKIC = false;}
      if(SeCyNzBXeb == true){SeCyNzBXeb = false;}
      if(xNeJBceEVJ == true){xNeJBceEVJ = false;}
      if(CDbwSDRBVG == true){CDbwSDRBVG = false;}
      if(CYkRkLEgpa == true){CYkRkLEgpa = false;}
      if(RpTaOXitVr == true){RpTaOXitVr = false;}
      if(nQoyAPCGfJ == true){nQoyAPCGfJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONAKFVHEDA
{ 
  void mRwJBXoTFQ()
  { 
      bool YWfrozhAMD = false;
      bool XVswECSIjR = false;
      bool GCIhhdiPSq = false;
      bool fxZulArofW = false;
      bool jiFtYMCGKi = false;
      bool JxaLaWOxKL = false;
      bool QRgUWZuxKD = false;
      bool JcbMgWxOIU = false;
      bool acFigiWOUP = false;
      bool lteUGRBjWy = false;
      bool QFwHZgUNdD = false;
      bool ZAopknMxnn = false;
      bool DgctROyHGO = false;
      bool UMqJDVgyJA = false;
      bool NIjRokFniS = false;
      bool FDwhujcBoK = false;
      bool hNHPhMIemO = false;
      bool HOnnatxKEf = false;
      bool JKXmJQQJOT = false;
      bool seIyRABUib = false;
      string ClcKDieTXS;
      string UAGljrZfXw;
      string wPkgKgGIZk;
      string tBoMmOSUFh;
      string FdHFfViTiD;
      string OUDGhlAuzW;
      string cWslXTLtzU;
      string YEaoqRIfAo;
      string xlZVVYxidA;
      string OXViFhkUgM;
      string JoUOdJtNPQ;
      string dTtKYpxWPz;
      string VbPzFBirjI;
      string fnzneIQLrL;
      string ejSMWtcKJO;
      string kNEgphYVIc;
      string aBdHjpUGeQ;
      string YleEUlJDbL;
      string XXhUWSiRxx;
      string iuCOkcFLcg;
      if(ClcKDieTXS == JoUOdJtNPQ){YWfrozhAMD = true;}
      else if(JoUOdJtNPQ == ClcKDieTXS){QFwHZgUNdD = true;}
      if(UAGljrZfXw == dTtKYpxWPz){XVswECSIjR = true;}
      else if(dTtKYpxWPz == UAGljrZfXw){ZAopknMxnn = true;}
      if(wPkgKgGIZk == VbPzFBirjI){GCIhhdiPSq = true;}
      else if(VbPzFBirjI == wPkgKgGIZk){DgctROyHGO = true;}
      if(tBoMmOSUFh == fnzneIQLrL){fxZulArofW = true;}
      else if(fnzneIQLrL == tBoMmOSUFh){UMqJDVgyJA = true;}
      if(FdHFfViTiD == ejSMWtcKJO){jiFtYMCGKi = true;}
      else if(ejSMWtcKJO == FdHFfViTiD){NIjRokFniS = true;}
      if(OUDGhlAuzW == kNEgphYVIc){JxaLaWOxKL = true;}
      else if(kNEgphYVIc == OUDGhlAuzW){FDwhujcBoK = true;}
      if(cWslXTLtzU == aBdHjpUGeQ){QRgUWZuxKD = true;}
      else if(aBdHjpUGeQ == cWslXTLtzU){hNHPhMIemO = true;}
      if(YEaoqRIfAo == YleEUlJDbL){JcbMgWxOIU = true;}
      if(xlZVVYxidA == XXhUWSiRxx){acFigiWOUP = true;}
      if(OXViFhkUgM == iuCOkcFLcg){lteUGRBjWy = true;}
      while(YleEUlJDbL == YEaoqRIfAo){HOnnatxKEf = true;}
      while(XXhUWSiRxx == XXhUWSiRxx){JKXmJQQJOT = true;}
      while(iuCOkcFLcg == iuCOkcFLcg){seIyRABUib = true;}
      if(YWfrozhAMD == true){YWfrozhAMD = false;}
      if(XVswECSIjR == true){XVswECSIjR = false;}
      if(GCIhhdiPSq == true){GCIhhdiPSq = false;}
      if(fxZulArofW == true){fxZulArofW = false;}
      if(jiFtYMCGKi == true){jiFtYMCGKi = false;}
      if(JxaLaWOxKL == true){JxaLaWOxKL = false;}
      if(QRgUWZuxKD == true){QRgUWZuxKD = false;}
      if(JcbMgWxOIU == true){JcbMgWxOIU = false;}
      if(acFigiWOUP == true){acFigiWOUP = false;}
      if(lteUGRBjWy == true){lteUGRBjWy = false;}
      if(QFwHZgUNdD == true){QFwHZgUNdD = false;}
      if(ZAopknMxnn == true){ZAopknMxnn = false;}
      if(DgctROyHGO == true){DgctROyHGO = false;}
      if(UMqJDVgyJA == true){UMqJDVgyJA = false;}
      if(NIjRokFniS == true){NIjRokFniS = false;}
      if(FDwhujcBoK == true){FDwhujcBoK = false;}
      if(hNHPhMIemO == true){hNHPhMIemO = false;}
      if(HOnnatxKEf == true){HOnnatxKEf = false;}
      if(JKXmJQQJOT == true){JKXmJQQJOT = false;}
      if(seIyRABUib == true){seIyRABUib = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TFXEOGQERR
{ 
  void PcxDZTsVIF()
  { 
      bool TjrYtaDcMj = false;
      bool xROOmERWJP = false;
      bool TYRhynZMJy = false;
      bool GictLRchfn = false;
      bool JDgbMMXJuq = false;
      bool peCqxuSKZF = false;
      bool ApTNcNoTCV = false;
      bool bjpUFPqpVl = false;
      bool QQQRHbgkxQ = false;
      bool zRHanTjSyy = false;
      bool WEGZPGnglh = false;
      bool DbonojYCGB = false;
      bool gDVkWJcPgl = false;
      bool eYrWOLJqBB = false;
      bool mzzPNWcTkD = false;
      bool thMxQTiUDF = false;
      bool cXzACdjRYc = false;
      bool ZhAEOhEGXz = false;
      bool fIedqxLtFu = false;
      bool comwXOzzMi = false;
      string KgncXdboCQ;
      string iikjCqCmLW;
      string tRfDxNbcrW;
      string NkxsZRfNUJ;
      string oOpKzOMNxP;
      string UztwTrAkfJ;
      string ByweCykrKj;
      string KnSCgebUEh;
      string AOfcCOpBYh;
      string RuhKHqSLHA;
      string dUCMEfgqOo;
      string QegxImRTbn;
      string HiScRPGIto;
      string MPMDEfLSXW;
      string gzmiQlNkBU;
      string ZziTrtBZto;
      string ZYxZcAScrc;
      string ayuFHIwiLf;
      string BUGZPNgsLK;
      string dlXiwICMGQ;
      if(KgncXdboCQ == dUCMEfgqOo){TjrYtaDcMj = true;}
      else if(dUCMEfgqOo == KgncXdboCQ){WEGZPGnglh = true;}
      if(iikjCqCmLW == QegxImRTbn){xROOmERWJP = true;}
      else if(QegxImRTbn == iikjCqCmLW){DbonojYCGB = true;}
      if(tRfDxNbcrW == HiScRPGIto){TYRhynZMJy = true;}
      else if(HiScRPGIto == tRfDxNbcrW){gDVkWJcPgl = true;}
      if(NkxsZRfNUJ == MPMDEfLSXW){GictLRchfn = true;}
      else if(MPMDEfLSXW == NkxsZRfNUJ){eYrWOLJqBB = true;}
      if(oOpKzOMNxP == gzmiQlNkBU){JDgbMMXJuq = true;}
      else if(gzmiQlNkBU == oOpKzOMNxP){mzzPNWcTkD = true;}
      if(UztwTrAkfJ == ZziTrtBZto){peCqxuSKZF = true;}
      else if(ZziTrtBZto == UztwTrAkfJ){thMxQTiUDF = true;}
      if(ByweCykrKj == ZYxZcAScrc){ApTNcNoTCV = true;}
      else if(ZYxZcAScrc == ByweCykrKj){cXzACdjRYc = true;}
      if(KnSCgebUEh == ayuFHIwiLf){bjpUFPqpVl = true;}
      if(AOfcCOpBYh == BUGZPNgsLK){QQQRHbgkxQ = true;}
      if(RuhKHqSLHA == dlXiwICMGQ){zRHanTjSyy = true;}
      while(ayuFHIwiLf == KnSCgebUEh){ZhAEOhEGXz = true;}
      while(BUGZPNgsLK == BUGZPNgsLK){fIedqxLtFu = true;}
      while(dlXiwICMGQ == dlXiwICMGQ){comwXOzzMi = true;}
      if(TjrYtaDcMj == true){TjrYtaDcMj = false;}
      if(xROOmERWJP == true){xROOmERWJP = false;}
      if(TYRhynZMJy == true){TYRhynZMJy = false;}
      if(GictLRchfn == true){GictLRchfn = false;}
      if(JDgbMMXJuq == true){JDgbMMXJuq = false;}
      if(peCqxuSKZF == true){peCqxuSKZF = false;}
      if(ApTNcNoTCV == true){ApTNcNoTCV = false;}
      if(bjpUFPqpVl == true){bjpUFPqpVl = false;}
      if(QQQRHbgkxQ == true){QQQRHbgkxQ = false;}
      if(zRHanTjSyy == true){zRHanTjSyy = false;}
      if(WEGZPGnglh == true){WEGZPGnglh = false;}
      if(DbonojYCGB == true){DbonojYCGB = false;}
      if(gDVkWJcPgl == true){gDVkWJcPgl = false;}
      if(eYrWOLJqBB == true){eYrWOLJqBB = false;}
      if(mzzPNWcTkD == true){mzzPNWcTkD = false;}
      if(thMxQTiUDF == true){thMxQTiUDF = false;}
      if(cXzACdjRYc == true){cXzACdjRYc = false;}
      if(ZhAEOhEGXz == true){ZhAEOhEGXz = false;}
      if(fIedqxLtFu == true){fIedqxLtFu = false;}
      if(comwXOzzMi == true){comwXOzzMi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JEJCNXTFFI
{ 
  void IylsOBHtsa()
  { 
      bool czpnjQZFae = false;
      bool BCNrCGCBex = false;
      bool FNtlRgQgRh = false;
      bool KzJGOJMWKg = false;
      bool kIrUAuMUmn = false;
      bool trsyPPEEWD = false;
      bool ArmsUBsGdr = false;
      bool sfpxMxUYkW = false;
      bool UutdmSGKqy = false;
      bool EIzHgrVyAy = false;
      bool BFqttOBwlS = false;
      bool teSAhEyIFC = false;
      bool uiPemkfiPT = false;
      bool bWYmUODziX = false;
      bool QJXYEZpyYb = false;
      bool tMrxDSpMGJ = false;
      bool hRgSpXFffT = false;
      bool ByZhklKqZN = false;
      bool ugKmYPdbiB = false;
      bool YqsZoybEhg = false;
      string mixVVouktm;
      string bDlQRqbMRs;
      string ZUCGZYqlCb;
      string HKGHIyPtWO;
      string eBDdtwyRDo;
      string bSljmRgquw;
      string yIiSfRweIS;
      string ahoDOYRYMc;
      string aZhNznXWTp;
      string RYyZQVRkyb;
      string ATIkNtciVO;
      string AHeRVYaVSq;
      string sZKRBCjPmr;
      string GfajcGQxzF;
      string LoBEoJtfDr;
      string tuSGiZIpiK;
      string KNwcITguoP;
      string HdVMfDYFcq;
      string IDLtyKNTAC;
      string xZNouxsYwV;
      if(mixVVouktm == ATIkNtciVO){czpnjQZFae = true;}
      else if(ATIkNtciVO == mixVVouktm){BFqttOBwlS = true;}
      if(bDlQRqbMRs == AHeRVYaVSq){BCNrCGCBex = true;}
      else if(AHeRVYaVSq == bDlQRqbMRs){teSAhEyIFC = true;}
      if(ZUCGZYqlCb == sZKRBCjPmr){FNtlRgQgRh = true;}
      else if(sZKRBCjPmr == ZUCGZYqlCb){uiPemkfiPT = true;}
      if(HKGHIyPtWO == GfajcGQxzF){KzJGOJMWKg = true;}
      else if(GfajcGQxzF == HKGHIyPtWO){bWYmUODziX = true;}
      if(eBDdtwyRDo == LoBEoJtfDr){kIrUAuMUmn = true;}
      else if(LoBEoJtfDr == eBDdtwyRDo){QJXYEZpyYb = true;}
      if(bSljmRgquw == tuSGiZIpiK){trsyPPEEWD = true;}
      else if(tuSGiZIpiK == bSljmRgquw){tMrxDSpMGJ = true;}
      if(yIiSfRweIS == KNwcITguoP){ArmsUBsGdr = true;}
      else if(KNwcITguoP == yIiSfRweIS){hRgSpXFffT = true;}
      if(ahoDOYRYMc == HdVMfDYFcq){sfpxMxUYkW = true;}
      if(aZhNznXWTp == IDLtyKNTAC){UutdmSGKqy = true;}
      if(RYyZQVRkyb == xZNouxsYwV){EIzHgrVyAy = true;}
      while(HdVMfDYFcq == ahoDOYRYMc){ByZhklKqZN = true;}
      while(IDLtyKNTAC == IDLtyKNTAC){ugKmYPdbiB = true;}
      while(xZNouxsYwV == xZNouxsYwV){YqsZoybEhg = true;}
      if(czpnjQZFae == true){czpnjQZFae = false;}
      if(BCNrCGCBex == true){BCNrCGCBex = false;}
      if(FNtlRgQgRh == true){FNtlRgQgRh = false;}
      if(KzJGOJMWKg == true){KzJGOJMWKg = false;}
      if(kIrUAuMUmn == true){kIrUAuMUmn = false;}
      if(trsyPPEEWD == true){trsyPPEEWD = false;}
      if(ArmsUBsGdr == true){ArmsUBsGdr = false;}
      if(sfpxMxUYkW == true){sfpxMxUYkW = false;}
      if(UutdmSGKqy == true){UutdmSGKqy = false;}
      if(EIzHgrVyAy == true){EIzHgrVyAy = false;}
      if(BFqttOBwlS == true){BFqttOBwlS = false;}
      if(teSAhEyIFC == true){teSAhEyIFC = false;}
      if(uiPemkfiPT == true){uiPemkfiPT = false;}
      if(bWYmUODziX == true){bWYmUODziX = false;}
      if(QJXYEZpyYb == true){QJXYEZpyYb = false;}
      if(tMrxDSpMGJ == true){tMrxDSpMGJ = false;}
      if(hRgSpXFffT == true){hRgSpXFffT = false;}
      if(ByZhklKqZN == true){ByZhklKqZN = false;}
      if(ugKmYPdbiB == true){ugKmYPdbiB = false;}
      if(YqsZoybEhg == true){YqsZoybEhg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCVGCPBDYA
{ 
  void MSXQizmfzy()
  { 
      bool RImSerxelf = false;
      bool wokUklGZIs = false;
      bool DDbEomjdrY = false;
      bool DTPVBsYdQE = false;
      bool qxXJPXnzVr = false;
      bool tmXwZNfidr = false;
      bool ISmMbbYOTr = false;
      bool McJDBGfSoQ = false;
      bool zjHzdQuTwm = false;
      bool MpzYwXKKgm = false;
      bool yZfdfRcUtT = false;
      bool gNtNrXLmhL = false;
      bool fFRgfWckGd = false;
      bool uUkBRZEdTM = false;
      bool mZYcFywlfX = false;
      bool MWbVGsHzyJ = false;
      bool orOQXMcruS = false;
      bool ThTVYFgoag = false;
      bool ZpEhQYsPtY = false;
      bool RFeKWtLIFs = false;
      string PRTasDERly;
      string yZSsgboOld;
      string kXPdGFeudw;
      string rDyONRUwSl;
      string VBqzsMaZAV;
      string GRJJnrBoTn;
      string YJnoGtbDfO;
      string GrwzIjgQkt;
      string dEuIpasnaV;
      string QecdMMNBsy;
      string kWtlONVJBD;
      string LkEYJUOezf;
      string BmbJxbPRmu;
      string WeWmJHJItc;
      string EjlWJeZDUq;
      string yhCNxxtjnl;
      string yDWFgfNRPB;
      string LFkWaQAFzS;
      string BLxwxncJoL;
      string MYUHdBNgoc;
      if(PRTasDERly == kWtlONVJBD){RImSerxelf = true;}
      else if(kWtlONVJBD == PRTasDERly){yZfdfRcUtT = true;}
      if(yZSsgboOld == LkEYJUOezf){wokUklGZIs = true;}
      else if(LkEYJUOezf == yZSsgboOld){gNtNrXLmhL = true;}
      if(kXPdGFeudw == BmbJxbPRmu){DDbEomjdrY = true;}
      else if(BmbJxbPRmu == kXPdGFeudw){fFRgfWckGd = true;}
      if(rDyONRUwSl == WeWmJHJItc){DTPVBsYdQE = true;}
      else if(WeWmJHJItc == rDyONRUwSl){uUkBRZEdTM = true;}
      if(VBqzsMaZAV == EjlWJeZDUq){qxXJPXnzVr = true;}
      else if(EjlWJeZDUq == VBqzsMaZAV){mZYcFywlfX = true;}
      if(GRJJnrBoTn == yhCNxxtjnl){tmXwZNfidr = true;}
      else if(yhCNxxtjnl == GRJJnrBoTn){MWbVGsHzyJ = true;}
      if(YJnoGtbDfO == yDWFgfNRPB){ISmMbbYOTr = true;}
      else if(yDWFgfNRPB == YJnoGtbDfO){orOQXMcruS = true;}
      if(GrwzIjgQkt == LFkWaQAFzS){McJDBGfSoQ = true;}
      if(dEuIpasnaV == BLxwxncJoL){zjHzdQuTwm = true;}
      if(QecdMMNBsy == MYUHdBNgoc){MpzYwXKKgm = true;}
      while(LFkWaQAFzS == GrwzIjgQkt){ThTVYFgoag = true;}
      while(BLxwxncJoL == BLxwxncJoL){ZpEhQYsPtY = true;}
      while(MYUHdBNgoc == MYUHdBNgoc){RFeKWtLIFs = true;}
      if(RImSerxelf == true){RImSerxelf = false;}
      if(wokUklGZIs == true){wokUklGZIs = false;}
      if(DDbEomjdrY == true){DDbEomjdrY = false;}
      if(DTPVBsYdQE == true){DTPVBsYdQE = false;}
      if(qxXJPXnzVr == true){qxXJPXnzVr = false;}
      if(tmXwZNfidr == true){tmXwZNfidr = false;}
      if(ISmMbbYOTr == true){ISmMbbYOTr = false;}
      if(McJDBGfSoQ == true){McJDBGfSoQ = false;}
      if(zjHzdQuTwm == true){zjHzdQuTwm = false;}
      if(MpzYwXKKgm == true){MpzYwXKKgm = false;}
      if(yZfdfRcUtT == true){yZfdfRcUtT = false;}
      if(gNtNrXLmhL == true){gNtNrXLmhL = false;}
      if(fFRgfWckGd == true){fFRgfWckGd = false;}
      if(uUkBRZEdTM == true){uUkBRZEdTM = false;}
      if(mZYcFywlfX == true){mZYcFywlfX = false;}
      if(MWbVGsHzyJ == true){MWbVGsHzyJ = false;}
      if(orOQXMcruS == true){orOQXMcruS = false;}
      if(ThTVYFgoag == true){ThTVYFgoag = false;}
      if(ZpEhQYsPtY == true){ZpEhQYsPtY = false;}
      if(RFeKWtLIFs == true){RFeKWtLIFs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KIFYCZZYEB
{ 
  void nsEYQcALHX()
  { 
      bool mmntABpqVn = false;
      bool aHCCLfxqlV = false;
      bool ThyAYMJmBQ = false;
      bool EwhHDdbJxG = false;
      bool qpwssIqZgt = false;
      bool fWTfpFnnUm = false;
      bool rDoEjdZuyh = false;
      bool DnseeckFGP = false;
      bool UiFGkhcBQy = false;
      bool pmnJOmArJO = false;
      bool iwazprcnAM = false;
      bool ThgESIxiTC = false;
      bool BXdAqPzjQq = false;
      bool cswqgYIFPs = false;
      bool EoBEdHGjqF = false;
      bool pQXGNLSaIZ = false;
      bool rsWJialpXt = false;
      bool ArSaxLWZVi = false;
      bool JPrLBLUodV = false;
      bool GhxpALRqUD = false;
      string dToBPHMRzi;
      string dOIFbAXwbh;
      string zQLEEahNbL;
      string lPVEVcZXXy;
      string rSCmoZkcUo;
      string UPVeoMHkwn;
      string YypnwNsEiy;
      string azYcogNYPd;
      string oFrlpWtpOI;
      string UoaiZsbOpa;
      string fgsWOUqrpI;
      string zhVRySGExZ;
      string TCoZckYoDu;
      string EyhnxIMVWV;
      string eBAFJmTIkG;
      string mXRPGcqSsd;
      string uBntDAzgUp;
      string GkgatRCjQp;
      string RPExIggRhT;
      string QsbsZdNFCJ;
      if(dToBPHMRzi == fgsWOUqrpI){mmntABpqVn = true;}
      else if(fgsWOUqrpI == dToBPHMRzi){iwazprcnAM = true;}
      if(dOIFbAXwbh == zhVRySGExZ){aHCCLfxqlV = true;}
      else if(zhVRySGExZ == dOIFbAXwbh){ThgESIxiTC = true;}
      if(zQLEEahNbL == TCoZckYoDu){ThyAYMJmBQ = true;}
      else if(TCoZckYoDu == zQLEEahNbL){BXdAqPzjQq = true;}
      if(lPVEVcZXXy == EyhnxIMVWV){EwhHDdbJxG = true;}
      else if(EyhnxIMVWV == lPVEVcZXXy){cswqgYIFPs = true;}
      if(rSCmoZkcUo == eBAFJmTIkG){qpwssIqZgt = true;}
      else if(eBAFJmTIkG == rSCmoZkcUo){EoBEdHGjqF = true;}
      if(UPVeoMHkwn == mXRPGcqSsd){fWTfpFnnUm = true;}
      else if(mXRPGcqSsd == UPVeoMHkwn){pQXGNLSaIZ = true;}
      if(YypnwNsEiy == uBntDAzgUp){rDoEjdZuyh = true;}
      else if(uBntDAzgUp == YypnwNsEiy){rsWJialpXt = true;}
      if(azYcogNYPd == GkgatRCjQp){DnseeckFGP = true;}
      if(oFrlpWtpOI == RPExIggRhT){UiFGkhcBQy = true;}
      if(UoaiZsbOpa == QsbsZdNFCJ){pmnJOmArJO = true;}
      while(GkgatRCjQp == azYcogNYPd){ArSaxLWZVi = true;}
      while(RPExIggRhT == RPExIggRhT){JPrLBLUodV = true;}
      while(QsbsZdNFCJ == QsbsZdNFCJ){GhxpALRqUD = true;}
      if(mmntABpqVn == true){mmntABpqVn = false;}
      if(aHCCLfxqlV == true){aHCCLfxqlV = false;}
      if(ThyAYMJmBQ == true){ThyAYMJmBQ = false;}
      if(EwhHDdbJxG == true){EwhHDdbJxG = false;}
      if(qpwssIqZgt == true){qpwssIqZgt = false;}
      if(fWTfpFnnUm == true){fWTfpFnnUm = false;}
      if(rDoEjdZuyh == true){rDoEjdZuyh = false;}
      if(DnseeckFGP == true){DnseeckFGP = false;}
      if(UiFGkhcBQy == true){UiFGkhcBQy = false;}
      if(pmnJOmArJO == true){pmnJOmArJO = false;}
      if(iwazprcnAM == true){iwazprcnAM = false;}
      if(ThgESIxiTC == true){ThgESIxiTC = false;}
      if(BXdAqPzjQq == true){BXdAqPzjQq = false;}
      if(cswqgYIFPs == true){cswqgYIFPs = false;}
      if(EoBEdHGjqF == true){EoBEdHGjqF = false;}
      if(pQXGNLSaIZ == true){pQXGNLSaIZ = false;}
      if(rsWJialpXt == true){rsWJialpXt = false;}
      if(ArSaxLWZVi == true){ArSaxLWZVi = false;}
      if(JPrLBLUodV == true){JPrLBLUodV = false;}
      if(GhxpALRqUD == true){GhxpALRqUD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MUBNHWPBZB
{ 
  void EwRxwECdgQ()
  { 
      bool fAlRKuLANn = false;
      bool rwYMmRBMgi = false;
      bool hOerWUPRJr = false;
      bool NkIGUjhTjY = false;
      bool PaDCLiQnKu = false;
      bool mlaPLQVstp = false;
      bool ftpVZGmRrD = false;
      bool jhbHTGLbfm = false;
      bool DaGNFbJsuE = false;
      bool NnYtsVjhcF = false;
      bool wywHLEJSuE = false;
      bool EsNGlEncQy = false;
      bool wtWnouIgOy = false;
      bool WdzaqEeyBB = false;
      bool SqxqzTaSIn = false;
      bool gGRdIBbHSQ = false;
      bool ubExgatlOh = false;
      bool ZoaPfFwfoU = false;
      bool UpYZQPMURo = false;
      bool bXfkFplzJX = false;
      string DBSqCoIFPs;
      string RLmTkKNFVx;
      string LCrmXMZkVC;
      string TQKzJQRouJ;
      string SwIbXqIjtV;
      string NBjPbBJeTo;
      string OXjMZBAnJT;
      string rXKLdOtPPg;
      string DopzoRfuWI;
      string GlUFuuMuCW;
      string pUZadoqYkM;
      string GtPmlZgkXH;
      string UEQBMGCEQi;
      string CyMspiOPVA;
      string aHKJBMWhTU;
      string NaXuBlDYNW;
      string llICKIgVwC;
      string KRPXgNtHzA;
      string jTkuUaaRqE;
      string epByNnzIys;
      if(DBSqCoIFPs == pUZadoqYkM){fAlRKuLANn = true;}
      else if(pUZadoqYkM == DBSqCoIFPs){wywHLEJSuE = true;}
      if(RLmTkKNFVx == GtPmlZgkXH){rwYMmRBMgi = true;}
      else if(GtPmlZgkXH == RLmTkKNFVx){EsNGlEncQy = true;}
      if(LCrmXMZkVC == UEQBMGCEQi){hOerWUPRJr = true;}
      else if(UEQBMGCEQi == LCrmXMZkVC){wtWnouIgOy = true;}
      if(TQKzJQRouJ == CyMspiOPVA){NkIGUjhTjY = true;}
      else if(CyMspiOPVA == TQKzJQRouJ){WdzaqEeyBB = true;}
      if(SwIbXqIjtV == aHKJBMWhTU){PaDCLiQnKu = true;}
      else if(aHKJBMWhTU == SwIbXqIjtV){SqxqzTaSIn = true;}
      if(NBjPbBJeTo == NaXuBlDYNW){mlaPLQVstp = true;}
      else if(NaXuBlDYNW == NBjPbBJeTo){gGRdIBbHSQ = true;}
      if(OXjMZBAnJT == llICKIgVwC){ftpVZGmRrD = true;}
      else if(llICKIgVwC == OXjMZBAnJT){ubExgatlOh = true;}
      if(rXKLdOtPPg == KRPXgNtHzA){jhbHTGLbfm = true;}
      if(DopzoRfuWI == jTkuUaaRqE){DaGNFbJsuE = true;}
      if(GlUFuuMuCW == epByNnzIys){NnYtsVjhcF = true;}
      while(KRPXgNtHzA == rXKLdOtPPg){ZoaPfFwfoU = true;}
      while(jTkuUaaRqE == jTkuUaaRqE){UpYZQPMURo = true;}
      while(epByNnzIys == epByNnzIys){bXfkFplzJX = true;}
      if(fAlRKuLANn == true){fAlRKuLANn = false;}
      if(rwYMmRBMgi == true){rwYMmRBMgi = false;}
      if(hOerWUPRJr == true){hOerWUPRJr = false;}
      if(NkIGUjhTjY == true){NkIGUjhTjY = false;}
      if(PaDCLiQnKu == true){PaDCLiQnKu = false;}
      if(mlaPLQVstp == true){mlaPLQVstp = false;}
      if(ftpVZGmRrD == true){ftpVZGmRrD = false;}
      if(jhbHTGLbfm == true){jhbHTGLbfm = false;}
      if(DaGNFbJsuE == true){DaGNFbJsuE = false;}
      if(NnYtsVjhcF == true){NnYtsVjhcF = false;}
      if(wywHLEJSuE == true){wywHLEJSuE = false;}
      if(EsNGlEncQy == true){EsNGlEncQy = false;}
      if(wtWnouIgOy == true){wtWnouIgOy = false;}
      if(WdzaqEeyBB == true){WdzaqEeyBB = false;}
      if(SqxqzTaSIn == true){SqxqzTaSIn = false;}
      if(gGRdIBbHSQ == true){gGRdIBbHSQ = false;}
      if(ubExgatlOh == true){ubExgatlOh = false;}
      if(ZoaPfFwfoU == true){ZoaPfFwfoU = false;}
      if(UpYZQPMURo == true){UpYZQPMURo = false;}
      if(bXfkFplzJX == true){bXfkFplzJX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UXHGEXYNTQ
{ 
  void YWVfRgSCcU()
  { 
      bool UToacrVRXc = false;
      bool jJXPORHUFo = false;
      bool efPNAIXbZE = false;
      bool MzsKSkdEXB = false;
      bool DqSlHIiywu = false;
      bool nwRaynDbZU = false;
      bool UtqSQkQNwd = false;
      bool mDwDlnMdGr = false;
      bool YYfdQQgSMd = false;
      bool gCdCfJAAVV = false;
      bool rVCRIjzOnJ = false;
      bool bZVhwwOMCz = false;
      bool EyARwkZsXc = false;
      bool nMIjACVNVf = false;
      bool QSdCCGfwGi = false;
      bool umxVRsUkUW = false;
      bool KGpLVORlht = false;
      bool ZApVikUyOo = false;
      bool EcmnhAOlRG = false;
      bool gkrzVKbSgm = false;
      string kSdqUGuCwT;
      string MNszqzQecu;
      string CeKjmSgpgM;
      string msZdZjtDDD;
      string muanpnXspc;
      string NppfCGHtDB;
      string YEUjgTnPZH;
      string ENbYHGEVsz;
      string unADyxDtaT;
      string bAzBdiZpHW;
      string AIShXzNQXu;
      string BkBEGkERlj;
      string PsnGeEOZtY;
      string gNOVylURey;
      string ilWeRqzuus;
      string eIEXGGTMDT;
      string kmVzOnWeFT;
      string PllmAdWJnn;
      string FTeBtYIpOq;
      string SHOKMwQXQd;
      if(kSdqUGuCwT == AIShXzNQXu){UToacrVRXc = true;}
      else if(AIShXzNQXu == kSdqUGuCwT){rVCRIjzOnJ = true;}
      if(MNszqzQecu == BkBEGkERlj){jJXPORHUFo = true;}
      else if(BkBEGkERlj == MNszqzQecu){bZVhwwOMCz = true;}
      if(CeKjmSgpgM == PsnGeEOZtY){efPNAIXbZE = true;}
      else if(PsnGeEOZtY == CeKjmSgpgM){EyARwkZsXc = true;}
      if(msZdZjtDDD == gNOVylURey){MzsKSkdEXB = true;}
      else if(gNOVylURey == msZdZjtDDD){nMIjACVNVf = true;}
      if(muanpnXspc == ilWeRqzuus){DqSlHIiywu = true;}
      else if(ilWeRqzuus == muanpnXspc){QSdCCGfwGi = true;}
      if(NppfCGHtDB == eIEXGGTMDT){nwRaynDbZU = true;}
      else if(eIEXGGTMDT == NppfCGHtDB){umxVRsUkUW = true;}
      if(YEUjgTnPZH == kmVzOnWeFT){UtqSQkQNwd = true;}
      else if(kmVzOnWeFT == YEUjgTnPZH){KGpLVORlht = true;}
      if(ENbYHGEVsz == PllmAdWJnn){mDwDlnMdGr = true;}
      if(unADyxDtaT == FTeBtYIpOq){YYfdQQgSMd = true;}
      if(bAzBdiZpHW == SHOKMwQXQd){gCdCfJAAVV = true;}
      while(PllmAdWJnn == ENbYHGEVsz){ZApVikUyOo = true;}
      while(FTeBtYIpOq == FTeBtYIpOq){EcmnhAOlRG = true;}
      while(SHOKMwQXQd == SHOKMwQXQd){gkrzVKbSgm = true;}
      if(UToacrVRXc == true){UToacrVRXc = false;}
      if(jJXPORHUFo == true){jJXPORHUFo = false;}
      if(efPNAIXbZE == true){efPNAIXbZE = false;}
      if(MzsKSkdEXB == true){MzsKSkdEXB = false;}
      if(DqSlHIiywu == true){DqSlHIiywu = false;}
      if(nwRaynDbZU == true){nwRaynDbZU = false;}
      if(UtqSQkQNwd == true){UtqSQkQNwd = false;}
      if(mDwDlnMdGr == true){mDwDlnMdGr = false;}
      if(YYfdQQgSMd == true){YYfdQQgSMd = false;}
      if(gCdCfJAAVV == true){gCdCfJAAVV = false;}
      if(rVCRIjzOnJ == true){rVCRIjzOnJ = false;}
      if(bZVhwwOMCz == true){bZVhwwOMCz = false;}
      if(EyARwkZsXc == true){EyARwkZsXc = false;}
      if(nMIjACVNVf == true){nMIjACVNVf = false;}
      if(QSdCCGfwGi == true){QSdCCGfwGi = false;}
      if(umxVRsUkUW == true){umxVRsUkUW = false;}
      if(KGpLVORlht == true){KGpLVORlht = false;}
      if(ZApVikUyOo == true){ZApVikUyOo = false;}
      if(EcmnhAOlRG == true){EcmnhAOlRG = false;}
      if(gkrzVKbSgm == true){gkrzVKbSgm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XAOAUXQISY
{ 
  void WkNjVWWKjJ()
  { 
      bool JAXWslkTnD = false;
      bool qXsqDwSezl = false;
      bool FkLcVrsDkX = false;
      bool HsfxrFbzjG = false;
      bool DjfErtoQRu = false;
      bool AAURHXotAA = false;
      bool shiQuxruyx = false;
      bool UStshUFGjb = false;
      bool DblpWHYNpU = false;
      bool PgzjNVBPJt = false;
      bool BsRTahFajm = false;
      bool RiKXwQwrtn = false;
      bool XdFchmSKfM = false;
      bool SpwoZKJSPn = false;
      bool CydDCgVamw = false;
      bool YJVVWWnokm = false;
      bool OttWTblUyl = false;
      bool GdcFkZACaB = false;
      bool RrXjmJUaSC = false;
      bool WUgcZIDGiZ = false;
      string behiFPYYxu;
      string zkIXygcBzU;
      string iDrAMqcLJR;
      string OeZnGJUIqU;
      string BZqLkqrDzw;
      string zhkpiXmhWO;
      string mNOffTKUQn;
      string MUKeSJMfPU;
      string yYLNRgsjFi;
      string WlkbhnKLfQ;
      string fXlKieXGWZ;
      string LGRBPNBBOz;
      string aaPhRZihxe;
      string yBAyoalAdl;
      string ImMeWPTjLT;
      string lJwfpFIEsJ;
      string uoIraJGTMo;
      string aAXbqmNjKB;
      string FzWcroEUIi;
      string ShHUqTeUDM;
      if(behiFPYYxu == fXlKieXGWZ){JAXWslkTnD = true;}
      else if(fXlKieXGWZ == behiFPYYxu){BsRTahFajm = true;}
      if(zkIXygcBzU == LGRBPNBBOz){qXsqDwSezl = true;}
      else if(LGRBPNBBOz == zkIXygcBzU){RiKXwQwrtn = true;}
      if(iDrAMqcLJR == aaPhRZihxe){FkLcVrsDkX = true;}
      else if(aaPhRZihxe == iDrAMqcLJR){XdFchmSKfM = true;}
      if(OeZnGJUIqU == yBAyoalAdl){HsfxrFbzjG = true;}
      else if(yBAyoalAdl == OeZnGJUIqU){SpwoZKJSPn = true;}
      if(BZqLkqrDzw == ImMeWPTjLT){DjfErtoQRu = true;}
      else if(ImMeWPTjLT == BZqLkqrDzw){CydDCgVamw = true;}
      if(zhkpiXmhWO == lJwfpFIEsJ){AAURHXotAA = true;}
      else if(lJwfpFIEsJ == zhkpiXmhWO){YJVVWWnokm = true;}
      if(mNOffTKUQn == uoIraJGTMo){shiQuxruyx = true;}
      else if(uoIraJGTMo == mNOffTKUQn){OttWTblUyl = true;}
      if(MUKeSJMfPU == aAXbqmNjKB){UStshUFGjb = true;}
      if(yYLNRgsjFi == FzWcroEUIi){DblpWHYNpU = true;}
      if(WlkbhnKLfQ == ShHUqTeUDM){PgzjNVBPJt = true;}
      while(aAXbqmNjKB == MUKeSJMfPU){GdcFkZACaB = true;}
      while(FzWcroEUIi == FzWcroEUIi){RrXjmJUaSC = true;}
      while(ShHUqTeUDM == ShHUqTeUDM){WUgcZIDGiZ = true;}
      if(JAXWslkTnD == true){JAXWslkTnD = false;}
      if(qXsqDwSezl == true){qXsqDwSezl = false;}
      if(FkLcVrsDkX == true){FkLcVrsDkX = false;}
      if(HsfxrFbzjG == true){HsfxrFbzjG = false;}
      if(DjfErtoQRu == true){DjfErtoQRu = false;}
      if(AAURHXotAA == true){AAURHXotAA = false;}
      if(shiQuxruyx == true){shiQuxruyx = false;}
      if(UStshUFGjb == true){UStshUFGjb = false;}
      if(DblpWHYNpU == true){DblpWHYNpU = false;}
      if(PgzjNVBPJt == true){PgzjNVBPJt = false;}
      if(BsRTahFajm == true){BsRTahFajm = false;}
      if(RiKXwQwrtn == true){RiKXwQwrtn = false;}
      if(XdFchmSKfM == true){XdFchmSKfM = false;}
      if(SpwoZKJSPn == true){SpwoZKJSPn = false;}
      if(CydDCgVamw == true){CydDCgVamw = false;}
      if(YJVVWWnokm == true){YJVVWWnokm = false;}
      if(OttWTblUyl == true){OttWTblUyl = false;}
      if(GdcFkZACaB == true){GdcFkZACaB = false;}
      if(RrXjmJUaSC == true){RrXjmJUaSC = false;}
      if(WUgcZIDGiZ == true){WUgcZIDGiZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MCMOVFCJZA
{ 
  void sUEDPaVrID()
  { 
      bool XGlyoNlmzA = false;
      bool TUgQWlfyoc = false;
      bool qsFHzAIWqW = false;
      bool YtKHENuNCT = false;
      bool NcyhzAVzUN = false;
      bool heHTPdAeyn = false;
      bool FPucbYJZMJ = false;
      bool qRwUONtXHz = false;
      bool eIBdnslqqZ = false;
      bool MQPNOygVFZ = false;
      bool qwmLWPimEB = false;
      bool icWzJwORnh = false;
      bool lRhlwZChGP = false;
      bool gYRhHiVoHY = false;
      bool KzloqjtPER = false;
      bool jOhWnYNAPw = false;
      bool NAfoUKKoqZ = false;
      bool aYKPXmesuL = false;
      bool fldnfRptsi = false;
      bool UUZKKJSxTf = false;
      string BsaJXQmTCw;
      string KSSuDlqfCn;
      string nPJsAypKfK;
      string YxsiBXCcMV;
      string ymgAjxrSPp;
      string crFgekihJZ;
      string acnrXMYjse;
      string jNTfoAiJID;
      string GXtohfrMDQ;
      string nUTmuUznbX;
      string XIYjGOYYqd;
      string BYZGSCiyKr;
      string UMfcqOtfjU;
      string BthkexyJiT;
      string GSUYOOuNTs;
      string lBdjCLbusq;
      string TroWcHqnaV;
      string DYOqkCrHOb;
      string TgMqhAPxhT;
      string VDQrzOcxwG;
      if(BsaJXQmTCw == XIYjGOYYqd){XGlyoNlmzA = true;}
      else if(XIYjGOYYqd == BsaJXQmTCw){qwmLWPimEB = true;}
      if(KSSuDlqfCn == BYZGSCiyKr){TUgQWlfyoc = true;}
      else if(BYZGSCiyKr == KSSuDlqfCn){icWzJwORnh = true;}
      if(nPJsAypKfK == UMfcqOtfjU){qsFHzAIWqW = true;}
      else if(UMfcqOtfjU == nPJsAypKfK){lRhlwZChGP = true;}
      if(YxsiBXCcMV == BthkexyJiT){YtKHENuNCT = true;}
      else if(BthkexyJiT == YxsiBXCcMV){gYRhHiVoHY = true;}
      if(ymgAjxrSPp == GSUYOOuNTs){NcyhzAVzUN = true;}
      else if(GSUYOOuNTs == ymgAjxrSPp){KzloqjtPER = true;}
      if(crFgekihJZ == lBdjCLbusq){heHTPdAeyn = true;}
      else if(lBdjCLbusq == crFgekihJZ){jOhWnYNAPw = true;}
      if(acnrXMYjse == TroWcHqnaV){FPucbYJZMJ = true;}
      else if(TroWcHqnaV == acnrXMYjse){NAfoUKKoqZ = true;}
      if(jNTfoAiJID == DYOqkCrHOb){qRwUONtXHz = true;}
      if(GXtohfrMDQ == TgMqhAPxhT){eIBdnslqqZ = true;}
      if(nUTmuUznbX == VDQrzOcxwG){MQPNOygVFZ = true;}
      while(DYOqkCrHOb == jNTfoAiJID){aYKPXmesuL = true;}
      while(TgMqhAPxhT == TgMqhAPxhT){fldnfRptsi = true;}
      while(VDQrzOcxwG == VDQrzOcxwG){UUZKKJSxTf = true;}
      if(XGlyoNlmzA == true){XGlyoNlmzA = false;}
      if(TUgQWlfyoc == true){TUgQWlfyoc = false;}
      if(qsFHzAIWqW == true){qsFHzAIWqW = false;}
      if(YtKHENuNCT == true){YtKHENuNCT = false;}
      if(NcyhzAVzUN == true){NcyhzAVzUN = false;}
      if(heHTPdAeyn == true){heHTPdAeyn = false;}
      if(FPucbYJZMJ == true){FPucbYJZMJ = false;}
      if(qRwUONtXHz == true){qRwUONtXHz = false;}
      if(eIBdnslqqZ == true){eIBdnslqqZ = false;}
      if(MQPNOygVFZ == true){MQPNOygVFZ = false;}
      if(qwmLWPimEB == true){qwmLWPimEB = false;}
      if(icWzJwORnh == true){icWzJwORnh = false;}
      if(lRhlwZChGP == true){lRhlwZChGP = false;}
      if(gYRhHiVoHY == true){gYRhHiVoHY = false;}
      if(KzloqjtPER == true){KzloqjtPER = false;}
      if(jOhWnYNAPw == true){jOhWnYNAPw = false;}
      if(NAfoUKKoqZ == true){NAfoUKKoqZ = false;}
      if(aYKPXmesuL == true){aYKPXmesuL = false;}
      if(fldnfRptsi == true){fldnfRptsi = false;}
      if(UUZKKJSxTf == true){UUZKKJSxTf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZVBWVBRNAR
{ 
  void cAgmynCgal()
  { 
      bool SDQmtxPnLg = false;
      bool QYYUuYyfyr = false;
      bool QWGrPUzbCh = false;
      bool ZBPVBZxTAO = false;
      bool wbCDUnzzHE = false;
      bool eVhGXuwXWZ = false;
      bool xmlcHOJCTU = false;
      bool bdfjwoUDXb = false;
      bool VATyDDSJxF = false;
      bool cZxaQJoYuG = false;
      bool ewemcApyKi = false;
      bool aszuDxTnZD = false;
      bool uAFOrBgFSl = false;
      bool zwHRwZUgUC = false;
      bool NUzOejZBWT = false;
      bool oByqKdqQta = false;
      bool TkfXiekhyd = false;
      bool blSWpaBpiH = false;
      bool bfhzxxxQGR = false;
      bool hElticnaeA = false;
      string AyLKklfJhL;
      string IuQhxkxzgT;
      string leZPmyMfeY;
      string GQphLzdfgL;
      string ueaWGdpnJF;
      string MtdLSVYuXm;
      string YAeJFrEiWx;
      string HQRUXGDCIJ;
      string IYVYLLlePo;
      string ZhItmuARQO;
      string YHQMyucImL;
      string SWlNdAdFxt;
      string FZSgWYIWhc;
      string GkktjBHJaQ;
      string hcqEWDutPm;
      string QtUWJznjoY;
      string mFaKFgkrdc;
      string rTefLbiOKT;
      string dNHtLMQNkk;
      string NXUCdcCgzo;
      if(AyLKklfJhL == YHQMyucImL){SDQmtxPnLg = true;}
      else if(YHQMyucImL == AyLKklfJhL){ewemcApyKi = true;}
      if(IuQhxkxzgT == SWlNdAdFxt){QYYUuYyfyr = true;}
      else if(SWlNdAdFxt == IuQhxkxzgT){aszuDxTnZD = true;}
      if(leZPmyMfeY == FZSgWYIWhc){QWGrPUzbCh = true;}
      else if(FZSgWYIWhc == leZPmyMfeY){uAFOrBgFSl = true;}
      if(GQphLzdfgL == GkktjBHJaQ){ZBPVBZxTAO = true;}
      else if(GkktjBHJaQ == GQphLzdfgL){zwHRwZUgUC = true;}
      if(ueaWGdpnJF == hcqEWDutPm){wbCDUnzzHE = true;}
      else if(hcqEWDutPm == ueaWGdpnJF){NUzOejZBWT = true;}
      if(MtdLSVYuXm == QtUWJznjoY){eVhGXuwXWZ = true;}
      else if(QtUWJznjoY == MtdLSVYuXm){oByqKdqQta = true;}
      if(YAeJFrEiWx == mFaKFgkrdc){xmlcHOJCTU = true;}
      else if(mFaKFgkrdc == YAeJFrEiWx){TkfXiekhyd = true;}
      if(HQRUXGDCIJ == rTefLbiOKT){bdfjwoUDXb = true;}
      if(IYVYLLlePo == dNHtLMQNkk){VATyDDSJxF = true;}
      if(ZhItmuARQO == NXUCdcCgzo){cZxaQJoYuG = true;}
      while(rTefLbiOKT == HQRUXGDCIJ){blSWpaBpiH = true;}
      while(dNHtLMQNkk == dNHtLMQNkk){bfhzxxxQGR = true;}
      while(NXUCdcCgzo == NXUCdcCgzo){hElticnaeA = true;}
      if(SDQmtxPnLg == true){SDQmtxPnLg = false;}
      if(QYYUuYyfyr == true){QYYUuYyfyr = false;}
      if(QWGrPUzbCh == true){QWGrPUzbCh = false;}
      if(ZBPVBZxTAO == true){ZBPVBZxTAO = false;}
      if(wbCDUnzzHE == true){wbCDUnzzHE = false;}
      if(eVhGXuwXWZ == true){eVhGXuwXWZ = false;}
      if(xmlcHOJCTU == true){xmlcHOJCTU = false;}
      if(bdfjwoUDXb == true){bdfjwoUDXb = false;}
      if(VATyDDSJxF == true){VATyDDSJxF = false;}
      if(cZxaQJoYuG == true){cZxaQJoYuG = false;}
      if(ewemcApyKi == true){ewemcApyKi = false;}
      if(aszuDxTnZD == true){aszuDxTnZD = false;}
      if(uAFOrBgFSl == true){uAFOrBgFSl = false;}
      if(zwHRwZUgUC == true){zwHRwZUgUC = false;}
      if(NUzOejZBWT == true){NUzOejZBWT = false;}
      if(oByqKdqQta == true){oByqKdqQta = false;}
      if(TkfXiekhyd == true){TkfXiekhyd = false;}
      if(blSWpaBpiH == true){blSWpaBpiH = false;}
      if(bfhzxxxQGR == true){bfhzxxxQGR = false;}
      if(hElticnaeA == true){hElticnaeA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGEGAMPKMF
{ 
  void cqdabFsnQL()
  { 
      bool wkTUPwdIaE = false;
      bool MPBqKSxCmY = false;
      bool lspoObhbcW = false;
      bool coxQpBHgLD = false;
      bool jkaAmQMDlC = false;
      bool gSCqDDudGn = false;
      bool NBfDaXSjAI = false;
      bool LPpinARoCx = false;
      bool OepaoKlGMm = false;
      bool GcaXpiFXZP = false;
      bool ycCcpRcTCD = false;
      bool kFaIYiKFNQ = false;
      bool kMXNBhoRsE = false;
      bool utPmzlbMjX = false;
      bool gRDJCABRzG = false;
      bool XzKIdlFobI = false;
      bool bLZyHppnIm = false;
      bool GyVoiSINKA = false;
      bool fWRlgwjGJN = false;
      bool glkbwVrFBL = false;
      string hzdFamdDxo;
      string ozSaiuhTpP;
      string glhSjSTrbs;
      string IdCuxjsJem;
      string NuUrLuPNIS;
      string CJQNowQKUI;
      string TlbDgKwWcy;
      string BYoCBkQpHo;
      string CGiJqzNoGA;
      string SinVTbTRKA;
      string ysjJQcTNLD;
      string eaCfFMCRLh;
      string xHPbfSjTiZ;
      string QzeHpJVYsN;
      string ezcCVrfIQG;
      string ZCFcCqcHdx;
      string sAdlmfuuou;
      string pcXxCyeMGm;
      string maCbzOsBFz;
      string gOtwUeUpPp;
      if(hzdFamdDxo == ysjJQcTNLD){wkTUPwdIaE = true;}
      else if(ysjJQcTNLD == hzdFamdDxo){ycCcpRcTCD = true;}
      if(ozSaiuhTpP == eaCfFMCRLh){MPBqKSxCmY = true;}
      else if(eaCfFMCRLh == ozSaiuhTpP){kFaIYiKFNQ = true;}
      if(glhSjSTrbs == xHPbfSjTiZ){lspoObhbcW = true;}
      else if(xHPbfSjTiZ == glhSjSTrbs){kMXNBhoRsE = true;}
      if(IdCuxjsJem == QzeHpJVYsN){coxQpBHgLD = true;}
      else if(QzeHpJVYsN == IdCuxjsJem){utPmzlbMjX = true;}
      if(NuUrLuPNIS == ezcCVrfIQG){jkaAmQMDlC = true;}
      else if(ezcCVrfIQG == NuUrLuPNIS){gRDJCABRzG = true;}
      if(CJQNowQKUI == ZCFcCqcHdx){gSCqDDudGn = true;}
      else if(ZCFcCqcHdx == CJQNowQKUI){XzKIdlFobI = true;}
      if(TlbDgKwWcy == sAdlmfuuou){NBfDaXSjAI = true;}
      else if(sAdlmfuuou == TlbDgKwWcy){bLZyHppnIm = true;}
      if(BYoCBkQpHo == pcXxCyeMGm){LPpinARoCx = true;}
      if(CGiJqzNoGA == maCbzOsBFz){OepaoKlGMm = true;}
      if(SinVTbTRKA == gOtwUeUpPp){GcaXpiFXZP = true;}
      while(pcXxCyeMGm == BYoCBkQpHo){GyVoiSINKA = true;}
      while(maCbzOsBFz == maCbzOsBFz){fWRlgwjGJN = true;}
      while(gOtwUeUpPp == gOtwUeUpPp){glkbwVrFBL = true;}
      if(wkTUPwdIaE == true){wkTUPwdIaE = false;}
      if(MPBqKSxCmY == true){MPBqKSxCmY = false;}
      if(lspoObhbcW == true){lspoObhbcW = false;}
      if(coxQpBHgLD == true){coxQpBHgLD = false;}
      if(jkaAmQMDlC == true){jkaAmQMDlC = false;}
      if(gSCqDDudGn == true){gSCqDDudGn = false;}
      if(NBfDaXSjAI == true){NBfDaXSjAI = false;}
      if(LPpinARoCx == true){LPpinARoCx = false;}
      if(OepaoKlGMm == true){OepaoKlGMm = false;}
      if(GcaXpiFXZP == true){GcaXpiFXZP = false;}
      if(ycCcpRcTCD == true){ycCcpRcTCD = false;}
      if(kFaIYiKFNQ == true){kFaIYiKFNQ = false;}
      if(kMXNBhoRsE == true){kMXNBhoRsE = false;}
      if(utPmzlbMjX == true){utPmzlbMjX = false;}
      if(gRDJCABRzG == true){gRDJCABRzG = false;}
      if(XzKIdlFobI == true){XzKIdlFobI = false;}
      if(bLZyHppnIm == true){bLZyHppnIm = false;}
      if(GyVoiSINKA == true){GyVoiSINKA = false;}
      if(fWRlgwjGJN == true){fWRlgwjGJN = false;}
      if(glkbwVrFBL == true){glkbwVrFBL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XCDEBCVQQW
{ 
  void JIrlOkjUzj()
  { 
      bool tlnzQPJLlI = false;
      bool lOlKaOmKor = false;
      bool tJVoMRHjIb = false;
      bool znKyenPtSP = false;
      bool qhbRVeMymo = false;
      bool wASjLjPylz = false;
      bool HZCKIyEnel = false;
      bool ysrYBLgDTh = false;
      bool EJwTezUZlu = false;
      bool YRHSHQfRIX = false;
      bool ZYSApDIshz = false;
      bool CLeEtydifJ = false;
      bool cdBjNgkYQk = false;
      bool fPtwHepucb = false;
      bool pbrlrMmDYJ = false;
      bool lwkztwWimJ = false;
      bool SjbxTlQhxO = false;
      bool HhGESBlOqA = false;
      bool tgzHyiduBL = false;
      bool IGITJGztSF = false;
      string dWKGBEXHSR;
      string OKkchZPZiM;
      string qytqasRuSC;
      string oigFeirCQb;
      string PLYEOgnmar;
      string VpSahecSeH;
      string mboQbfcexy;
      string hMJGxfZpcs;
      string EeUafyQFXz;
      string FYWIomWIbi;
      string EJocKIgLdC;
      string FmplCHHNjc;
      string PWHyrIoARK;
      string JRNsouprPW;
      string REbUtShkGh;
      string eIXySgBpjB;
      string SgtTsnYwxG;
      string QPyMLKulEZ;
      string ZEsieAsOaH;
      string tzIOEjKHbF;
      if(dWKGBEXHSR == EJocKIgLdC){tlnzQPJLlI = true;}
      else if(EJocKIgLdC == dWKGBEXHSR){ZYSApDIshz = true;}
      if(OKkchZPZiM == FmplCHHNjc){lOlKaOmKor = true;}
      else if(FmplCHHNjc == OKkchZPZiM){CLeEtydifJ = true;}
      if(qytqasRuSC == PWHyrIoARK){tJVoMRHjIb = true;}
      else if(PWHyrIoARK == qytqasRuSC){cdBjNgkYQk = true;}
      if(oigFeirCQb == JRNsouprPW){znKyenPtSP = true;}
      else if(JRNsouprPW == oigFeirCQb){fPtwHepucb = true;}
      if(PLYEOgnmar == REbUtShkGh){qhbRVeMymo = true;}
      else if(REbUtShkGh == PLYEOgnmar){pbrlrMmDYJ = true;}
      if(VpSahecSeH == eIXySgBpjB){wASjLjPylz = true;}
      else if(eIXySgBpjB == VpSahecSeH){lwkztwWimJ = true;}
      if(mboQbfcexy == SgtTsnYwxG){HZCKIyEnel = true;}
      else if(SgtTsnYwxG == mboQbfcexy){SjbxTlQhxO = true;}
      if(hMJGxfZpcs == QPyMLKulEZ){ysrYBLgDTh = true;}
      if(EeUafyQFXz == ZEsieAsOaH){EJwTezUZlu = true;}
      if(FYWIomWIbi == tzIOEjKHbF){YRHSHQfRIX = true;}
      while(QPyMLKulEZ == hMJGxfZpcs){HhGESBlOqA = true;}
      while(ZEsieAsOaH == ZEsieAsOaH){tgzHyiduBL = true;}
      while(tzIOEjKHbF == tzIOEjKHbF){IGITJGztSF = true;}
      if(tlnzQPJLlI == true){tlnzQPJLlI = false;}
      if(lOlKaOmKor == true){lOlKaOmKor = false;}
      if(tJVoMRHjIb == true){tJVoMRHjIb = false;}
      if(znKyenPtSP == true){znKyenPtSP = false;}
      if(qhbRVeMymo == true){qhbRVeMymo = false;}
      if(wASjLjPylz == true){wASjLjPylz = false;}
      if(HZCKIyEnel == true){HZCKIyEnel = false;}
      if(ysrYBLgDTh == true){ysrYBLgDTh = false;}
      if(EJwTezUZlu == true){EJwTezUZlu = false;}
      if(YRHSHQfRIX == true){YRHSHQfRIX = false;}
      if(ZYSApDIshz == true){ZYSApDIshz = false;}
      if(CLeEtydifJ == true){CLeEtydifJ = false;}
      if(cdBjNgkYQk == true){cdBjNgkYQk = false;}
      if(fPtwHepucb == true){fPtwHepucb = false;}
      if(pbrlrMmDYJ == true){pbrlrMmDYJ = false;}
      if(lwkztwWimJ == true){lwkztwWimJ = false;}
      if(SjbxTlQhxO == true){SjbxTlQhxO = false;}
      if(HhGESBlOqA == true){HhGESBlOqA = false;}
      if(tgzHyiduBL == true){tgzHyiduBL = false;}
      if(IGITJGztSF == true){IGITJGztSF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NWPHTSVIGM
{ 
  void WiEaCuYUdM()
  { 
      bool BYbCzPcnip = false;
      bool qDVBsBnAAw = false;
      bool XrckRNyhai = false;
      bool tBiVcjebSr = false;
      bool fZIZpDusey = false;
      bool axbKGJwpjl = false;
      bool QtNzupTzYI = false;
      bool WLhIQxjDuO = false;
      bool REDbHwZXPT = false;
      bool mnqfakMIdz = false;
      bool juUWaOPTtI = false;
      bool ZsuVTLqkqy = false;
      bool QujFUiUBge = false;
      bool kaYudVjgAs = false;
      bool gGdHstsVMO = false;
      bool taQeinLPBr = false;
      bool tNlOWyTzqy = false;
      bool bJkyRKQcLZ = false;
      bool pyoRkKKtLp = false;
      bool KTeHySTPju = false;
      string hTYCbCUGET;
      string tzbZngwdmS;
      string MldlsFJaTz;
      string jycPcgwbWq;
      string XDGuqGIjDP;
      string edNTGwolJW;
      string rslFjwWLxH;
      string kUGwuJeitm;
      string xZXETFjIJg;
      string qJRAydQBLu;
      string iwlwdKXRYx;
      string QGqWYSVgke;
      string LNCQPbCFyQ;
      string rdXzDAmbaJ;
      string gSjLQkRuae;
      string IiPfiVsVfC;
      string IRTHElirTY;
      string esGbxsdpAe;
      string JGdSHIOqPh;
      string GRuXAOybHd;
      if(hTYCbCUGET == iwlwdKXRYx){BYbCzPcnip = true;}
      else if(iwlwdKXRYx == hTYCbCUGET){juUWaOPTtI = true;}
      if(tzbZngwdmS == QGqWYSVgke){qDVBsBnAAw = true;}
      else if(QGqWYSVgke == tzbZngwdmS){ZsuVTLqkqy = true;}
      if(MldlsFJaTz == LNCQPbCFyQ){XrckRNyhai = true;}
      else if(LNCQPbCFyQ == MldlsFJaTz){QujFUiUBge = true;}
      if(jycPcgwbWq == rdXzDAmbaJ){tBiVcjebSr = true;}
      else if(rdXzDAmbaJ == jycPcgwbWq){kaYudVjgAs = true;}
      if(XDGuqGIjDP == gSjLQkRuae){fZIZpDusey = true;}
      else if(gSjLQkRuae == XDGuqGIjDP){gGdHstsVMO = true;}
      if(edNTGwolJW == IiPfiVsVfC){axbKGJwpjl = true;}
      else if(IiPfiVsVfC == edNTGwolJW){taQeinLPBr = true;}
      if(rslFjwWLxH == IRTHElirTY){QtNzupTzYI = true;}
      else if(IRTHElirTY == rslFjwWLxH){tNlOWyTzqy = true;}
      if(kUGwuJeitm == esGbxsdpAe){WLhIQxjDuO = true;}
      if(xZXETFjIJg == JGdSHIOqPh){REDbHwZXPT = true;}
      if(qJRAydQBLu == GRuXAOybHd){mnqfakMIdz = true;}
      while(esGbxsdpAe == kUGwuJeitm){bJkyRKQcLZ = true;}
      while(JGdSHIOqPh == JGdSHIOqPh){pyoRkKKtLp = true;}
      while(GRuXAOybHd == GRuXAOybHd){KTeHySTPju = true;}
      if(BYbCzPcnip == true){BYbCzPcnip = false;}
      if(qDVBsBnAAw == true){qDVBsBnAAw = false;}
      if(XrckRNyhai == true){XrckRNyhai = false;}
      if(tBiVcjebSr == true){tBiVcjebSr = false;}
      if(fZIZpDusey == true){fZIZpDusey = false;}
      if(axbKGJwpjl == true){axbKGJwpjl = false;}
      if(QtNzupTzYI == true){QtNzupTzYI = false;}
      if(WLhIQxjDuO == true){WLhIQxjDuO = false;}
      if(REDbHwZXPT == true){REDbHwZXPT = false;}
      if(mnqfakMIdz == true){mnqfakMIdz = false;}
      if(juUWaOPTtI == true){juUWaOPTtI = false;}
      if(ZsuVTLqkqy == true){ZsuVTLqkqy = false;}
      if(QujFUiUBge == true){QujFUiUBge = false;}
      if(kaYudVjgAs == true){kaYudVjgAs = false;}
      if(gGdHstsVMO == true){gGdHstsVMO = false;}
      if(taQeinLPBr == true){taQeinLPBr = false;}
      if(tNlOWyTzqy == true){tNlOWyTzqy = false;}
      if(bJkyRKQcLZ == true){bJkyRKQcLZ = false;}
      if(pyoRkKKtLp == true){pyoRkKKtLp = false;}
      if(KTeHySTPju == true){KTeHySTPju = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TNDVCMCWLY
{ 
  void fEEJRYKqki()
  { 
      bool HNgMTUUahq = false;
      bool FIDSLbAXrY = false;
      bool VkquXlrqfo = false;
      bool bOzEIcUxdi = false;
      bool FODdpmAIBS = false;
      bool MxrzeVVlng = false;
      bool bcusOpJzJi = false;
      bool HDtJTGgMEj = false;
      bool lipMbeVAZm = false;
      bool GiIwGbTKOz = false;
      bool dBzRLJDifY = false;
      bool nJgDusmhRj = false;
      bool UIYWcXtxCq = false;
      bool mWyFGjjXBR = false;
      bool amUByxCEBN = false;
      bool nkreeUbcom = false;
      bool OGfnkQLaxK = false;
      bool IPfzIgnXXe = false;
      bool VpuoCBeSak = false;
      bool HHhOCUGfPg = false;
      string bNpwAwHLwr;
      string kWZBUPYFiy;
      string nbmfWwBnJS;
      string uYVKRAFmiK;
      string lufGqlqLzb;
      string oXCApAaKZD;
      string uTBdxLBOjU;
      string KlWXLrufoj;
      string FpogcXVUUR;
      string YtMfPSsCJe;
      string jbbdRDAdnx;
      string EtVpyFdUAY;
      string pftRuPYqIr;
      string zrWJzdNKPZ;
      string WqgWMeYWgK;
      string nYCjoEgJiC;
      string dJVwyLXLpU;
      string qTEaCyzXFQ;
      string pCJxDZplUu;
      string wEbNuMVkXA;
      if(bNpwAwHLwr == jbbdRDAdnx){HNgMTUUahq = true;}
      else if(jbbdRDAdnx == bNpwAwHLwr){dBzRLJDifY = true;}
      if(kWZBUPYFiy == EtVpyFdUAY){FIDSLbAXrY = true;}
      else if(EtVpyFdUAY == kWZBUPYFiy){nJgDusmhRj = true;}
      if(nbmfWwBnJS == pftRuPYqIr){VkquXlrqfo = true;}
      else if(pftRuPYqIr == nbmfWwBnJS){UIYWcXtxCq = true;}
      if(uYVKRAFmiK == zrWJzdNKPZ){bOzEIcUxdi = true;}
      else if(zrWJzdNKPZ == uYVKRAFmiK){mWyFGjjXBR = true;}
      if(lufGqlqLzb == WqgWMeYWgK){FODdpmAIBS = true;}
      else if(WqgWMeYWgK == lufGqlqLzb){amUByxCEBN = true;}
      if(oXCApAaKZD == nYCjoEgJiC){MxrzeVVlng = true;}
      else if(nYCjoEgJiC == oXCApAaKZD){nkreeUbcom = true;}
      if(uTBdxLBOjU == dJVwyLXLpU){bcusOpJzJi = true;}
      else if(dJVwyLXLpU == uTBdxLBOjU){OGfnkQLaxK = true;}
      if(KlWXLrufoj == qTEaCyzXFQ){HDtJTGgMEj = true;}
      if(FpogcXVUUR == pCJxDZplUu){lipMbeVAZm = true;}
      if(YtMfPSsCJe == wEbNuMVkXA){GiIwGbTKOz = true;}
      while(qTEaCyzXFQ == KlWXLrufoj){IPfzIgnXXe = true;}
      while(pCJxDZplUu == pCJxDZplUu){VpuoCBeSak = true;}
      while(wEbNuMVkXA == wEbNuMVkXA){HHhOCUGfPg = true;}
      if(HNgMTUUahq == true){HNgMTUUahq = false;}
      if(FIDSLbAXrY == true){FIDSLbAXrY = false;}
      if(VkquXlrqfo == true){VkquXlrqfo = false;}
      if(bOzEIcUxdi == true){bOzEIcUxdi = false;}
      if(FODdpmAIBS == true){FODdpmAIBS = false;}
      if(MxrzeVVlng == true){MxrzeVVlng = false;}
      if(bcusOpJzJi == true){bcusOpJzJi = false;}
      if(HDtJTGgMEj == true){HDtJTGgMEj = false;}
      if(lipMbeVAZm == true){lipMbeVAZm = false;}
      if(GiIwGbTKOz == true){GiIwGbTKOz = false;}
      if(dBzRLJDifY == true){dBzRLJDifY = false;}
      if(nJgDusmhRj == true){nJgDusmhRj = false;}
      if(UIYWcXtxCq == true){UIYWcXtxCq = false;}
      if(mWyFGjjXBR == true){mWyFGjjXBR = false;}
      if(amUByxCEBN == true){amUByxCEBN = false;}
      if(nkreeUbcom == true){nkreeUbcom = false;}
      if(OGfnkQLaxK == true){OGfnkQLaxK = false;}
      if(IPfzIgnXXe == true){IPfzIgnXXe = false;}
      if(VpuoCBeSak == true){VpuoCBeSak = false;}
      if(HHhOCUGfPg == true){HHhOCUGfPg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YOAFDVTXFX
{ 
  void kZlGulZNQP()
  { 
      bool JxmHSpShYW = false;
      bool pGhAFdJSQx = false;
      bool lTydgbQqfX = false;
      bool ZBRxbgDEfy = false;
      bool JXQhtCpiKL = false;
      bool KXmWepyIaq = false;
      bool ZaCBwoojXX = false;
      bool aElRmOCQjd = false;
      bool lggTMBNuSl = false;
      bool htdoYiVPkE = false;
      bool NFLlkGkUiP = false;
      bool nhYwFsshnt = false;
      bool atRlofaxsE = false;
      bool sleeQfUuhG = false;
      bool QsLDyAVgje = false;
      bool ombpdTnZwF = false;
      bool enbeVBDseY = false;
      bool YyzgdhiNmo = false;
      bool KsNOOGJoBx = false;
      bool ruycabQfgw = false;
      string ZpgAjBgcTH;
      string zpqpIUTUzo;
      string qdNhOLsyFS;
      string DgclGPtgRt;
      string wFkEdXgEjp;
      string xiofOucykY;
      string IiXBDRMFir;
      string alDEsksJDq;
      string eoNPUUrxXL;
      string muurlMhjAL;
      string KaUqPKfjmc;
      string BSuttTVHfh;
      string YPgXFeqKRf;
      string CJIqfDTVAJ;
      string oIKtJTAByS;
      string pZDRmuswlj;
      string TURGZrKDOp;
      string zAHVrQFlOl;
      string epLzocFpEj;
      string JXjPpUpDUQ;
      if(ZpgAjBgcTH == KaUqPKfjmc){JxmHSpShYW = true;}
      else if(KaUqPKfjmc == ZpgAjBgcTH){NFLlkGkUiP = true;}
      if(zpqpIUTUzo == BSuttTVHfh){pGhAFdJSQx = true;}
      else if(BSuttTVHfh == zpqpIUTUzo){nhYwFsshnt = true;}
      if(qdNhOLsyFS == YPgXFeqKRf){lTydgbQqfX = true;}
      else if(YPgXFeqKRf == qdNhOLsyFS){atRlofaxsE = true;}
      if(DgclGPtgRt == CJIqfDTVAJ){ZBRxbgDEfy = true;}
      else if(CJIqfDTVAJ == DgclGPtgRt){sleeQfUuhG = true;}
      if(wFkEdXgEjp == oIKtJTAByS){JXQhtCpiKL = true;}
      else if(oIKtJTAByS == wFkEdXgEjp){QsLDyAVgje = true;}
      if(xiofOucykY == pZDRmuswlj){KXmWepyIaq = true;}
      else if(pZDRmuswlj == xiofOucykY){ombpdTnZwF = true;}
      if(IiXBDRMFir == TURGZrKDOp){ZaCBwoojXX = true;}
      else if(TURGZrKDOp == IiXBDRMFir){enbeVBDseY = true;}
      if(alDEsksJDq == zAHVrQFlOl){aElRmOCQjd = true;}
      if(eoNPUUrxXL == epLzocFpEj){lggTMBNuSl = true;}
      if(muurlMhjAL == JXjPpUpDUQ){htdoYiVPkE = true;}
      while(zAHVrQFlOl == alDEsksJDq){YyzgdhiNmo = true;}
      while(epLzocFpEj == epLzocFpEj){KsNOOGJoBx = true;}
      while(JXjPpUpDUQ == JXjPpUpDUQ){ruycabQfgw = true;}
      if(JxmHSpShYW == true){JxmHSpShYW = false;}
      if(pGhAFdJSQx == true){pGhAFdJSQx = false;}
      if(lTydgbQqfX == true){lTydgbQqfX = false;}
      if(ZBRxbgDEfy == true){ZBRxbgDEfy = false;}
      if(JXQhtCpiKL == true){JXQhtCpiKL = false;}
      if(KXmWepyIaq == true){KXmWepyIaq = false;}
      if(ZaCBwoojXX == true){ZaCBwoojXX = false;}
      if(aElRmOCQjd == true){aElRmOCQjd = false;}
      if(lggTMBNuSl == true){lggTMBNuSl = false;}
      if(htdoYiVPkE == true){htdoYiVPkE = false;}
      if(NFLlkGkUiP == true){NFLlkGkUiP = false;}
      if(nhYwFsshnt == true){nhYwFsshnt = false;}
      if(atRlofaxsE == true){atRlofaxsE = false;}
      if(sleeQfUuhG == true){sleeQfUuhG = false;}
      if(QsLDyAVgje == true){QsLDyAVgje = false;}
      if(ombpdTnZwF == true){ombpdTnZwF = false;}
      if(enbeVBDseY == true){enbeVBDseY = false;}
      if(YyzgdhiNmo == true){YyzgdhiNmo = false;}
      if(KsNOOGJoBx == true){KsNOOGJoBx = false;}
      if(ruycabQfgw == true){ruycabQfgw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OVBIDNBDRM
{ 
  void QWtAxBtzQi()
  { 
      bool mWgYeULVLV = false;
      bool uujYaTLmLO = false;
      bool qwJwOFWMma = false;
      bool uVWIMhfVRg = false;
      bool HMmFYnsCco = false;
      bool YnRfZpMkKY = false;
      bool yzikZYYaMs = false;
      bool npVeHeJEWZ = false;
      bool MUixCHDpiV = false;
      bool UuLsiHcCez = false;
      bool PRojBiSmYt = false;
      bool gINjLdPkhS = false;
      bool VhrqXrdcwz = false;
      bool BGYXKufzwT = false;
      bool nQRnnMgagF = false;
      bool rrTMdgZxLI = false;
      bool EppYrZjoYQ = false;
      bool yQoNdEQDDL = false;
      bool LDuqHJlLtd = false;
      bool UhmmPyZsuN = false;
      string OyLzVaLNig;
      string iXLoEmCCZO;
      string VfiKOTjEoO;
      string SuBHCRNNTc;
      string ZzZmOKNRuP;
      string fFpYAhOBjB;
      string qHYUOmVDml;
      string YniwnWGwuE;
      string GSIZhMEcHT;
      string CMcRlRaFYa;
      string nJdIqrWtjd;
      string bSFfuXyzlB;
      string hswSiLKQKV;
      string uBWTPxnAip;
      string pKrdrjHxWN;
      string TbSXsuNKYe;
      string gFiOhawkPx;
      string iyPwLWARaz;
      string ENtwCSizaT;
      string icaDIjbduR;
      if(OyLzVaLNig == nJdIqrWtjd){mWgYeULVLV = true;}
      else if(nJdIqrWtjd == OyLzVaLNig){PRojBiSmYt = true;}
      if(iXLoEmCCZO == bSFfuXyzlB){uujYaTLmLO = true;}
      else if(bSFfuXyzlB == iXLoEmCCZO){gINjLdPkhS = true;}
      if(VfiKOTjEoO == hswSiLKQKV){qwJwOFWMma = true;}
      else if(hswSiLKQKV == VfiKOTjEoO){VhrqXrdcwz = true;}
      if(SuBHCRNNTc == uBWTPxnAip){uVWIMhfVRg = true;}
      else if(uBWTPxnAip == SuBHCRNNTc){BGYXKufzwT = true;}
      if(ZzZmOKNRuP == pKrdrjHxWN){HMmFYnsCco = true;}
      else if(pKrdrjHxWN == ZzZmOKNRuP){nQRnnMgagF = true;}
      if(fFpYAhOBjB == TbSXsuNKYe){YnRfZpMkKY = true;}
      else if(TbSXsuNKYe == fFpYAhOBjB){rrTMdgZxLI = true;}
      if(qHYUOmVDml == gFiOhawkPx){yzikZYYaMs = true;}
      else if(gFiOhawkPx == qHYUOmVDml){EppYrZjoYQ = true;}
      if(YniwnWGwuE == iyPwLWARaz){npVeHeJEWZ = true;}
      if(GSIZhMEcHT == ENtwCSizaT){MUixCHDpiV = true;}
      if(CMcRlRaFYa == icaDIjbduR){UuLsiHcCez = true;}
      while(iyPwLWARaz == YniwnWGwuE){yQoNdEQDDL = true;}
      while(ENtwCSizaT == ENtwCSizaT){LDuqHJlLtd = true;}
      while(icaDIjbduR == icaDIjbduR){UhmmPyZsuN = true;}
      if(mWgYeULVLV == true){mWgYeULVLV = false;}
      if(uujYaTLmLO == true){uujYaTLmLO = false;}
      if(qwJwOFWMma == true){qwJwOFWMma = false;}
      if(uVWIMhfVRg == true){uVWIMhfVRg = false;}
      if(HMmFYnsCco == true){HMmFYnsCco = false;}
      if(YnRfZpMkKY == true){YnRfZpMkKY = false;}
      if(yzikZYYaMs == true){yzikZYYaMs = false;}
      if(npVeHeJEWZ == true){npVeHeJEWZ = false;}
      if(MUixCHDpiV == true){MUixCHDpiV = false;}
      if(UuLsiHcCez == true){UuLsiHcCez = false;}
      if(PRojBiSmYt == true){PRojBiSmYt = false;}
      if(gINjLdPkhS == true){gINjLdPkhS = false;}
      if(VhrqXrdcwz == true){VhrqXrdcwz = false;}
      if(BGYXKufzwT == true){BGYXKufzwT = false;}
      if(nQRnnMgagF == true){nQRnnMgagF = false;}
      if(rrTMdgZxLI == true){rrTMdgZxLI = false;}
      if(EppYrZjoYQ == true){EppYrZjoYQ = false;}
      if(yQoNdEQDDL == true){yQoNdEQDDL = false;}
      if(LDuqHJlLtd == true){LDuqHJlLtd = false;}
      if(UhmmPyZsuN == true){UhmmPyZsuN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LUWPRTJKLI
{ 
  void AMaMbUmNsL()
  { 
      bool aCbpxShZkz = false;
      bool geGPBMZomV = false;
      bool LZoipMpioW = false;
      bool sZqlcBcnwX = false;
      bool TXzDqBDdVa = false;
      bool WKkciAMszk = false;
      bool czkOFHnTlz = false;
      bool ikrOCmZkqo = false;
      bool IMMOzinNDc = false;
      bool njnLuTmkyj = false;
      bool NjqVqlRVau = false;
      bool abBKcQlVOV = false;
      bool SZPJKzxgTh = false;
      bool AomHaXUqWN = false;
      bool RSmIBMicie = false;
      bool hQVbQmThKr = false;
      bool nkCstkotjE = false;
      bool wuyBEAlHHy = false;
      bool PTxoziSKpm = false;
      bool ElfeYfPtNQ = false;
      string SYCBQoXlBg;
      string zXNReSkMlH;
      string GSHyAMxFTG;
      string PmsPPDlxmg;
      string PpfqhNeajl;
      string tTEQdzREAE;
      string qRRtQMeyCb;
      string gmZErPmQQm;
      string gWVhMuickQ;
      string lhxioyYkZV;
      string hgYIEHtzYO;
      string LAmMWUujhU;
      string cCMkoyopPs;
      string qBpuEAxMcF;
      string BjDWEktjMU;
      string CnDFrfUmTF;
      string RDjeXKKrHV;
      string WiGcTsyogD;
      string EFdtqCykCY;
      string fKsWmxzYyt;
      if(SYCBQoXlBg == hgYIEHtzYO){aCbpxShZkz = true;}
      else if(hgYIEHtzYO == SYCBQoXlBg){NjqVqlRVau = true;}
      if(zXNReSkMlH == LAmMWUujhU){geGPBMZomV = true;}
      else if(LAmMWUujhU == zXNReSkMlH){abBKcQlVOV = true;}
      if(GSHyAMxFTG == cCMkoyopPs){LZoipMpioW = true;}
      else if(cCMkoyopPs == GSHyAMxFTG){SZPJKzxgTh = true;}
      if(PmsPPDlxmg == qBpuEAxMcF){sZqlcBcnwX = true;}
      else if(qBpuEAxMcF == PmsPPDlxmg){AomHaXUqWN = true;}
      if(PpfqhNeajl == BjDWEktjMU){TXzDqBDdVa = true;}
      else if(BjDWEktjMU == PpfqhNeajl){RSmIBMicie = true;}
      if(tTEQdzREAE == CnDFrfUmTF){WKkciAMszk = true;}
      else if(CnDFrfUmTF == tTEQdzREAE){hQVbQmThKr = true;}
      if(qRRtQMeyCb == RDjeXKKrHV){czkOFHnTlz = true;}
      else if(RDjeXKKrHV == qRRtQMeyCb){nkCstkotjE = true;}
      if(gmZErPmQQm == WiGcTsyogD){ikrOCmZkqo = true;}
      if(gWVhMuickQ == EFdtqCykCY){IMMOzinNDc = true;}
      if(lhxioyYkZV == fKsWmxzYyt){njnLuTmkyj = true;}
      while(WiGcTsyogD == gmZErPmQQm){wuyBEAlHHy = true;}
      while(EFdtqCykCY == EFdtqCykCY){PTxoziSKpm = true;}
      while(fKsWmxzYyt == fKsWmxzYyt){ElfeYfPtNQ = true;}
      if(aCbpxShZkz == true){aCbpxShZkz = false;}
      if(geGPBMZomV == true){geGPBMZomV = false;}
      if(LZoipMpioW == true){LZoipMpioW = false;}
      if(sZqlcBcnwX == true){sZqlcBcnwX = false;}
      if(TXzDqBDdVa == true){TXzDqBDdVa = false;}
      if(WKkciAMszk == true){WKkciAMszk = false;}
      if(czkOFHnTlz == true){czkOFHnTlz = false;}
      if(ikrOCmZkqo == true){ikrOCmZkqo = false;}
      if(IMMOzinNDc == true){IMMOzinNDc = false;}
      if(njnLuTmkyj == true){njnLuTmkyj = false;}
      if(NjqVqlRVau == true){NjqVqlRVau = false;}
      if(abBKcQlVOV == true){abBKcQlVOV = false;}
      if(SZPJKzxgTh == true){SZPJKzxgTh = false;}
      if(AomHaXUqWN == true){AomHaXUqWN = false;}
      if(RSmIBMicie == true){RSmIBMicie = false;}
      if(hQVbQmThKr == true){hQVbQmThKr = false;}
      if(nkCstkotjE == true){nkCstkotjE = false;}
      if(wuyBEAlHHy == true){wuyBEAlHHy = false;}
      if(PTxoziSKpm == true){PTxoziSKpm = false;}
      if(ElfeYfPtNQ == true){ElfeYfPtNQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LMCIKUQBIV
{ 
  void HRfJqCCIUW()
  { 
      bool lOsfriKTDT = false;
      bool oTVgIstmKW = false;
      bool yPDRfzpSWE = false;
      bool HePQJTKEeJ = false;
      bool ByQxFzjNGF = false;
      bool drflzWKazr = false;
      bool srxzMKDFXo = false;
      bool ipHBUzyGMg = false;
      bool ObLQZOydQl = false;
      bool IiElQIBQjt = false;
      bool uepRWnjdQz = false;
      bool XEOScQggZy = false;
      bool LZolfAkVkM = false;
      bool ygWRkjlssk = false;
      bool dUMQNEUkJz = false;
      bool bTqkhUpEkW = false;
      bool COsEBpgwgs = false;
      bool dmmnTqNXXb = false;
      bool fAMkjepkjQ = false;
      bool thHWhPaHPW = false;
      string tLpXPsYjIX;
      string RwTEkawVUF;
      string kzJocjnsam;
      string sTWRkJeRTC;
      string LtfsgyNhXH;
      string juyLhtBBuf;
      string EfJVexZCTa;
      string weCSsqTPHd;
      string VGUSCxULjp;
      string IcVnxfjJOi;
      string YKOwKFsfRp;
      string aksQJyKpSg;
      string bOScSSIOVN;
      string GJBXEKqYHw;
      string DossOWjFdy;
      string UspgGKrkcr;
      string xeJDjRjUMy;
      string GlhVcmUYOw;
      string iDjWrMSUQt;
      string SGuPzYepJx;
      if(tLpXPsYjIX == YKOwKFsfRp){lOsfriKTDT = true;}
      else if(YKOwKFsfRp == tLpXPsYjIX){uepRWnjdQz = true;}
      if(RwTEkawVUF == aksQJyKpSg){oTVgIstmKW = true;}
      else if(aksQJyKpSg == RwTEkawVUF){XEOScQggZy = true;}
      if(kzJocjnsam == bOScSSIOVN){yPDRfzpSWE = true;}
      else if(bOScSSIOVN == kzJocjnsam){LZolfAkVkM = true;}
      if(sTWRkJeRTC == GJBXEKqYHw){HePQJTKEeJ = true;}
      else if(GJBXEKqYHw == sTWRkJeRTC){ygWRkjlssk = true;}
      if(LtfsgyNhXH == DossOWjFdy){ByQxFzjNGF = true;}
      else if(DossOWjFdy == LtfsgyNhXH){dUMQNEUkJz = true;}
      if(juyLhtBBuf == UspgGKrkcr){drflzWKazr = true;}
      else if(UspgGKrkcr == juyLhtBBuf){bTqkhUpEkW = true;}
      if(EfJVexZCTa == xeJDjRjUMy){srxzMKDFXo = true;}
      else if(xeJDjRjUMy == EfJVexZCTa){COsEBpgwgs = true;}
      if(weCSsqTPHd == GlhVcmUYOw){ipHBUzyGMg = true;}
      if(VGUSCxULjp == iDjWrMSUQt){ObLQZOydQl = true;}
      if(IcVnxfjJOi == SGuPzYepJx){IiElQIBQjt = true;}
      while(GlhVcmUYOw == weCSsqTPHd){dmmnTqNXXb = true;}
      while(iDjWrMSUQt == iDjWrMSUQt){fAMkjepkjQ = true;}
      while(SGuPzYepJx == SGuPzYepJx){thHWhPaHPW = true;}
      if(lOsfriKTDT == true){lOsfriKTDT = false;}
      if(oTVgIstmKW == true){oTVgIstmKW = false;}
      if(yPDRfzpSWE == true){yPDRfzpSWE = false;}
      if(HePQJTKEeJ == true){HePQJTKEeJ = false;}
      if(ByQxFzjNGF == true){ByQxFzjNGF = false;}
      if(drflzWKazr == true){drflzWKazr = false;}
      if(srxzMKDFXo == true){srxzMKDFXo = false;}
      if(ipHBUzyGMg == true){ipHBUzyGMg = false;}
      if(ObLQZOydQl == true){ObLQZOydQl = false;}
      if(IiElQIBQjt == true){IiElQIBQjt = false;}
      if(uepRWnjdQz == true){uepRWnjdQz = false;}
      if(XEOScQggZy == true){XEOScQggZy = false;}
      if(LZolfAkVkM == true){LZolfAkVkM = false;}
      if(ygWRkjlssk == true){ygWRkjlssk = false;}
      if(dUMQNEUkJz == true){dUMQNEUkJz = false;}
      if(bTqkhUpEkW == true){bTqkhUpEkW = false;}
      if(COsEBpgwgs == true){COsEBpgwgs = false;}
      if(dmmnTqNXXb == true){dmmnTqNXXb = false;}
      if(fAMkjepkjQ == true){fAMkjepkjQ = false;}
      if(thHWhPaHPW == true){thHWhPaHPW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFSEVPADZJ
{ 
  void QJhhBKlkeM()
  { 
      bool OPCgxOyhQf = false;
      bool OStJMJzFDI = false;
      bool nhZIWgrIfR = false;
      bool puygqtxtWO = false;
      bool SxwDmdszqy = false;
      bool mwKjUfosJQ = false;
      bool WoCypSTNRS = false;
      bool LFiooplWVs = false;
      bool nrRgesjNLK = false;
      bool EDjFqdtxMT = false;
      bool JfhXlhNVud = false;
      bool tSWQbeWUTx = false;
      bool hGBHNIUcyL = false;
      bool unJBiIKtuw = false;
      bool eOShPlfTcL = false;
      bool HZdPlDdZJd = false;
      bool MkXihGIVhT = false;
      bool UbZWRTmTqb = false;
      bool bBzlEVJtPe = false;
      bool djjRjtqizJ = false;
      string bAQFiIVeBE;
      string OOgxydukjH;
      string wkwAPenpJN;
      string VEjAlrFmgi;
      string WTLXBJBNkc;
      string cGPMeqDQpE;
      string UfUmiJdgLF;
      string XIEBkbYYzF;
      string cZFfjPoXVt;
      string oowbNqzYor;
      string eUBfFTCNaC;
      string SeQjbtZnDS;
      string TGKQQhLbnt;
      string cAiHZHYYaP;
      string NbwSaKYMAT;
      string QLUVXYKjPW;
      string IZZgZSuJKT;
      string VBMmFrKqoF;
      string JzaUdQeMiB;
      string xnJDHmBOsI;
      if(bAQFiIVeBE == eUBfFTCNaC){OPCgxOyhQf = true;}
      else if(eUBfFTCNaC == bAQFiIVeBE){JfhXlhNVud = true;}
      if(OOgxydukjH == SeQjbtZnDS){OStJMJzFDI = true;}
      else if(SeQjbtZnDS == OOgxydukjH){tSWQbeWUTx = true;}
      if(wkwAPenpJN == TGKQQhLbnt){nhZIWgrIfR = true;}
      else if(TGKQQhLbnt == wkwAPenpJN){hGBHNIUcyL = true;}
      if(VEjAlrFmgi == cAiHZHYYaP){puygqtxtWO = true;}
      else if(cAiHZHYYaP == VEjAlrFmgi){unJBiIKtuw = true;}
      if(WTLXBJBNkc == NbwSaKYMAT){SxwDmdszqy = true;}
      else if(NbwSaKYMAT == WTLXBJBNkc){eOShPlfTcL = true;}
      if(cGPMeqDQpE == QLUVXYKjPW){mwKjUfosJQ = true;}
      else if(QLUVXYKjPW == cGPMeqDQpE){HZdPlDdZJd = true;}
      if(UfUmiJdgLF == IZZgZSuJKT){WoCypSTNRS = true;}
      else if(IZZgZSuJKT == UfUmiJdgLF){MkXihGIVhT = true;}
      if(XIEBkbYYzF == VBMmFrKqoF){LFiooplWVs = true;}
      if(cZFfjPoXVt == JzaUdQeMiB){nrRgesjNLK = true;}
      if(oowbNqzYor == xnJDHmBOsI){EDjFqdtxMT = true;}
      while(VBMmFrKqoF == XIEBkbYYzF){UbZWRTmTqb = true;}
      while(JzaUdQeMiB == JzaUdQeMiB){bBzlEVJtPe = true;}
      while(xnJDHmBOsI == xnJDHmBOsI){djjRjtqizJ = true;}
      if(OPCgxOyhQf == true){OPCgxOyhQf = false;}
      if(OStJMJzFDI == true){OStJMJzFDI = false;}
      if(nhZIWgrIfR == true){nhZIWgrIfR = false;}
      if(puygqtxtWO == true){puygqtxtWO = false;}
      if(SxwDmdszqy == true){SxwDmdszqy = false;}
      if(mwKjUfosJQ == true){mwKjUfosJQ = false;}
      if(WoCypSTNRS == true){WoCypSTNRS = false;}
      if(LFiooplWVs == true){LFiooplWVs = false;}
      if(nrRgesjNLK == true){nrRgesjNLK = false;}
      if(EDjFqdtxMT == true){EDjFqdtxMT = false;}
      if(JfhXlhNVud == true){JfhXlhNVud = false;}
      if(tSWQbeWUTx == true){tSWQbeWUTx = false;}
      if(hGBHNIUcyL == true){hGBHNIUcyL = false;}
      if(unJBiIKtuw == true){unJBiIKtuw = false;}
      if(eOShPlfTcL == true){eOShPlfTcL = false;}
      if(HZdPlDdZJd == true){HZdPlDdZJd = false;}
      if(MkXihGIVhT == true){MkXihGIVhT = false;}
      if(UbZWRTmTqb == true){UbZWRTmTqb = false;}
      if(bBzlEVJtPe == true){bBzlEVJtPe = false;}
      if(djjRjtqizJ == true){djjRjtqizJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GHSTYOMTOM
{ 
  void KkWZszWBwg()
  { 
      bool VtAFxTJPpX = false;
      bool oIpSrxACxf = false;
      bool rnLEGeSwmu = false;
      bool UGtdmXOkYI = false;
      bool LqGZoIJyNT = false;
      bool jfgpGgiwzR = false;
      bool BMctDhOLfU = false;
      bool hPcoUBglPx = false;
      bool VUhSLnZEWF = false;
      bool oSlHHyNLVG = false;
      bool txSslTDqVF = false;
      bool AwfBwfeKhP = false;
      bool HJoZfPcVhV = false;
      bool mUPICYCofr = false;
      bool jiiRFrlkKa = false;
      bool TCcGzkIrNW = false;
      bool qgJzRefXyW = false;
      bool dodpeYaWUm = false;
      bool crKHCkqJJR = false;
      bool QJaJADYjAZ = false;
      string MkgxaVWGzK;
      string TZifDoBaLz;
      string EHcnnGKKoZ;
      string NcYseWffNl;
      string ptcccRCwZq;
      string iZwOpFHsIT;
      string LLQZxqApBg;
      string JVNYJJeAKV;
      string ENkyqnfJCY;
      string OlWsZddDfl;
      string RMusgMLXFf;
      string aGhmPxaSiI;
      string KpmbRWzTye;
      string faUYEqSrQd;
      string bHEVyIEicb;
      string CLTWaaZTaK;
      string MqYZAzlJhX;
      string eiCEfDlQcI;
      string SPpWbUGxxd;
      string RzQFRjieVz;
      if(MkgxaVWGzK == RMusgMLXFf){VtAFxTJPpX = true;}
      else if(RMusgMLXFf == MkgxaVWGzK){txSslTDqVF = true;}
      if(TZifDoBaLz == aGhmPxaSiI){oIpSrxACxf = true;}
      else if(aGhmPxaSiI == TZifDoBaLz){AwfBwfeKhP = true;}
      if(EHcnnGKKoZ == KpmbRWzTye){rnLEGeSwmu = true;}
      else if(KpmbRWzTye == EHcnnGKKoZ){HJoZfPcVhV = true;}
      if(NcYseWffNl == faUYEqSrQd){UGtdmXOkYI = true;}
      else if(faUYEqSrQd == NcYseWffNl){mUPICYCofr = true;}
      if(ptcccRCwZq == bHEVyIEicb){LqGZoIJyNT = true;}
      else if(bHEVyIEicb == ptcccRCwZq){jiiRFrlkKa = true;}
      if(iZwOpFHsIT == CLTWaaZTaK){jfgpGgiwzR = true;}
      else if(CLTWaaZTaK == iZwOpFHsIT){TCcGzkIrNW = true;}
      if(LLQZxqApBg == MqYZAzlJhX){BMctDhOLfU = true;}
      else if(MqYZAzlJhX == LLQZxqApBg){qgJzRefXyW = true;}
      if(JVNYJJeAKV == eiCEfDlQcI){hPcoUBglPx = true;}
      if(ENkyqnfJCY == SPpWbUGxxd){VUhSLnZEWF = true;}
      if(OlWsZddDfl == RzQFRjieVz){oSlHHyNLVG = true;}
      while(eiCEfDlQcI == JVNYJJeAKV){dodpeYaWUm = true;}
      while(SPpWbUGxxd == SPpWbUGxxd){crKHCkqJJR = true;}
      while(RzQFRjieVz == RzQFRjieVz){QJaJADYjAZ = true;}
      if(VtAFxTJPpX == true){VtAFxTJPpX = false;}
      if(oIpSrxACxf == true){oIpSrxACxf = false;}
      if(rnLEGeSwmu == true){rnLEGeSwmu = false;}
      if(UGtdmXOkYI == true){UGtdmXOkYI = false;}
      if(LqGZoIJyNT == true){LqGZoIJyNT = false;}
      if(jfgpGgiwzR == true){jfgpGgiwzR = false;}
      if(BMctDhOLfU == true){BMctDhOLfU = false;}
      if(hPcoUBglPx == true){hPcoUBglPx = false;}
      if(VUhSLnZEWF == true){VUhSLnZEWF = false;}
      if(oSlHHyNLVG == true){oSlHHyNLVG = false;}
      if(txSslTDqVF == true){txSslTDqVF = false;}
      if(AwfBwfeKhP == true){AwfBwfeKhP = false;}
      if(HJoZfPcVhV == true){HJoZfPcVhV = false;}
      if(mUPICYCofr == true){mUPICYCofr = false;}
      if(jiiRFrlkKa == true){jiiRFrlkKa = false;}
      if(TCcGzkIrNW == true){TCcGzkIrNW = false;}
      if(qgJzRefXyW == true){qgJzRefXyW = false;}
      if(dodpeYaWUm == true){dodpeYaWUm = false;}
      if(crKHCkqJJR == true){crKHCkqJJR = false;}
      if(QJaJADYjAZ == true){QJaJADYjAZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TEIXEQWMOQ
{ 
  void nGLpRQuyKE()
  { 
      bool xVcZbJHLni = false;
      bool hJdgVTqZsg = false;
      bool dffOPJspmD = false;
      bool LREiQTsSri = false;
      bool FAxfMGeszS = false;
      bool NAlxRQpOJR = false;
      bool PQYjXPFuQB = false;
      bool ZYgJbdhzBI = false;
      bool ezpToLfGRz = false;
      bool ddIaSnaMIx = false;
      bool BjcxroSbVm = false;
      bool hpMAmQZEuL = false;
      bool izdQXuPGpm = false;
      bool CUpEHtWsbA = false;
      bool rDkdQmRInC = false;
      bool OWRxNCGLZw = false;
      bool YMlikNAIrr = false;
      bool sgctTfNAAj = false;
      bool dHRmXfCspF = false;
      bool nLSebeRCsD = false;
      string IlhKOiySXV;
      string eJYczEEmNm;
      string zpCiFPDOYz;
      string zqURoCyatN;
      string AGJUSjGLUY;
      string aaKuSSjyFy;
      string eisYWnoGmw;
      string GdszmsggQV;
      string JrtAYXfZzW;
      string SzVuiRMkxd;
      string uAYYSxhKHZ;
      string lChiomnsAz;
      string HPHPdGHyQV;
      string fwjlZISUga;
      string oVRYkPRlFu;
      string cSjyVfrIuL;
      string ojtltoSuJf;
      string TTLYJlxieN;
      string oVrUsMLlPt;
      string QJZVlFaeeu;
      if(IlhKOiySXV == uAYYSxhKHZ){xVcZbJHLni = true;}
      else if(uAYYSxhKHZ == IlhKOiySXV){BjcxroSbVm = true;}
      if(eJYczEEmNm == lChiomnsAz){hJdgVTqZsg = true;}
      else if(lChiomnsAz == eJYczEEmNm){hpMAmQZEuL = true;}
      if(zpCiFPDOYz == HPHPdGHyQV){dffOPJspmD = true;}
      else if(HPHPdGHyQV == zpCiFPDOYz){izdQXuPGpm = true;}
      if(zqURoCyatN == fwjlZISUga){LREiQTsSri = true;}
      else if(fwjlZISUga == zqURoCyatN){CUpEHtWsbA = true;}
      if(AGJUSjGLUY == oVRYkPRlFu){FAxfMGeszS = true;}
      else if(oVRYkPRlFu == AGJUSjGLUY){rDkdQmRInC = true;}
      if(aaKuSSjyFy == cSjyVfrIuL){NAlxRQpOJR = true;}
      else if(cSjyVfrIuL == aaKuSSjyFy){OWRxNCGLZw = true;}
      if(eisYWnoGmw == ojtltoSuJf){PQYjXPFuQB = true;}
      else if(ojtltoSuJf == eisYWnoGmw){YMlikNAIrr = true;}
      if(GdszmsggQV == TTLYJlxieN){ZYgJbdhzBI = true;}
      if(JrtAYXfZzW == oVrUsMLlPt){ezpToLfGRz = true;}
      if(SzVuiRMkxd == QJZVlFaeeu){ddIaSnaMIx = true;}
      while(TTLYJlxieN == GdszmsggQV){sgctTfNAAj = true;}
      while(oVrUsMLlPt == oVrUsMLlPt){dHRmXfCspF = true;}
      while(QJZVlFaeeu == QJZVlFaeeu){nLSebeRCsD = true;}
      if(xVcZbJHLni == true){xVcZbJHLni = false;}
      if(hJdgVTqZsg == true){hJdgVTqZsg = false;}
      if(dffOPJspmD == true){dffOPJspmD = false;}
      if(LREiQTsSri == true){LREiQTsSri = false;}
      if(FAxfMGeszS == true){FAxfMGeszS = false;}
      if(NAlxRQpOJR == true){NAlxRQpOJR = false;}
      if(PQYjXPFuQB == true){PQYjXPFuQB = false;}
      if(ZYgJbdhzBI == true){ZYgJbdhzBI = false;}
      if(ezpToLfGRz == true){ezpToLfGRz = false;}
      if(ddIaSnaMIx == true){ddIaSnaMIx = false;}
      if(BjcxroSbVm == true){BjcxroSbVm = false;}
      if(hpMAmQZEuL == true){hpMAmQZEuL = false;}
      if(izdQXuPGpm == true){izdQXuPGpm = false;}
      if(CUpEHtWsbA == true){CUpEHtWsbA = false;}
      if(rDkdQmRInC == true){rDkdQmRInC = false;}
      if(OWRxNCGLZw == true){OWRxNCGLZw = false;}
      if(YMlikNAIrr == true){YMlikNAIrr = false;}
      if(sgctTfNAAj == true){sgctTfNAAj = false;}
      if(dHRmXfCspF == true){dHRmXfCspF = false;}
      if(nLSebeRCsD == true){nLSebeRCsD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DJYFIQNMXO
{ 
  void zTHmkjzHlO()
  { 
      bool hyswfYKaZU = false;
      bool BBctrpRTWg = false;
      bool fAEqhczeKQ = false;
      bool bFfdeADrcR = false;
      bool sSFRNflxBQ = false;
      bool gEQNRhsBOC = false;
      bool YePIrwUzOq = false;
      bool mYpFnNtmdB = false;
      bool qBdtjXnSLw = false;
      bool GBdarNCwYQ = false;
      bool LmhJdHNLZE = false;
      bool mGXMKWAVYT = false;
      bool ICmRkktPMZ = false;
      bool KyNMpESUQb = false;
      bool KcrHJAdRQV = false;
      bool MgWEIIzPXr = false;
      bool NyyzsosKVF = false;
      bool DeFxJfJfIj = false;
      bool HczqMdaIEg = false;
      bool FCwXOMdsNU = false;
      string AwzZxxeSaq;
      string CSRbdGDniu;
      string KtURGgNFlg;
      string InCJqoYmBS;
      string gbAqlFppWQ;
      string BubhGGbgTP;
      string iZgshNPIkn;
      string hQlQNiscfB;
      string qXhUfNMUCk;
      string MqSkiHuGJX;
      string phEiikIKTX;
      string MzASYLqLNU;
      string BtFAapxBgG;
      string mlTIKJSzlu;
      string FBBeXNpAMX;
      string PjsnVubEHr;
      string mGcNjZerHP;
      string rqYSOAsabN;
      string zwoJpDsemP;
      string gOrsHyXnty;
      if(AwzZxxeSaq == phEiikIKTX){hyswfYKaZU = true;}
      else if(phEiikIKTX == AwzZxxeSaq){LmhJdHNLZE = true;}
      if(CSRbdGDniu == MzASYLqLNU){BBctrpRTWg = true;}
      else if(MzASYLqLNU == CSRbdGDniu){mGXMKWAVYT = true;}
      if(KtURGgNFlg == BtFAapxBgG){fAEqhczeKQ = true;}
      else if(BtFAapxBgG == KtURGgNFlg){ICmRkktPMZ = true;}
      if(InCJqoYmBS == mlTIKJSzlu){bFfdeADrcR = true;}
      else if(mlTIKJSzlu == InCJqoYmBS){KyNMpESUQb = true;}
      if(gbAqlFppWQ == FBBeXNpAMX){sSFRNflxBQ = true;}
      else if(FBBeXNpAMX == gbAqlFppWQ){KcrHJAdRQV = true;}
      if(BubhGGbgTP == PjsnVubEHr){gEQNRhsBOC = true;}
      else if(PjsnVubEHr == BubhGGbgTP){MgWEIIzPXr = true;}
      if(iZgshNPIkn == mGcNjZerHP){YePIrwUzOq = true;}
      else if(mGcNjZerHP == iZgshNPIkn){NyyzsosKVF = true;}
      if(hQlQNiscfB == rqYSOAsabN){mYpFnNtmdB = true;}
      if(qXhUfNMUCk == zwoJpDsemP){qBdtjXnSLw = true;}
      if(MqSkiHuGJX == gOrsHyXnty){GBdarNCwYQ = true;}
      while(rqYSOAsabN == hQlQNiscfB){DeFxJfJfIj = true;}
      while(zwoJpDsemP == zwoJpDsemP){HczqMdaIEg = true;}
      while(gOrsHyXnty == gOrsHyXnty){FCwXOMdsNU = true;}
      if(hyswfYKaZU == true){hyswfYKaZU = false;}
      if(BBctrpRTWg == true){BBctrpRTWg = false;}
      if(fAEqhczeKQ == true){fAEqhczeKQ = false;}
      if(bFfdeADrcR == true){bFfdeADrcR = false;}
      if(sSFRNflxBQ == true){sSFRNflxBQ = false;}
      if(gEQNRhsBOC == true){gEQNRhsBOC = false;}
      if(YePIrwUzOq == true){YePIrwUzOq = false;}
      if(mYpFnNtmdB == true){mYpFnNtmdB = false;}
      if(qBdtjXnSLw == true){qBdtjXnSLw = false;}
      if(GBdarNCwYQ == true){GBdarNCwYQ = false;}
      if(LmhJdHNLZE == true){LmhJdHNLZE = false;}
      if(mGXMKWAVYT == true){mGXMKWAVYT = false;}
      if(ICmRkktPMZ == true){ICmRkktPMZ = false;}
      if(KyNMpESUQb == true){KyNMpESUQb = false;}
      if(KcrHJAdRQV == true){KcrHJAdRQV = false;}
      if(MgWEIIzPXr == true){MgWEIIzPXr = false;}
      if(NyyzsosKVF == true){NyyzsosKVF = false;}
      if(DeFxJfJfIj == true){DeFxJfJfIj = false;}
      if(HczqMdaIEg == true){HczqMdaIEg = false;}
      if(FCwXOMdsNU == true){FCwXOMdsNU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZRBOHFZJJO
{ 
  void tLugQFoJEd()
  { 
      bool aAwiRmEjMh = false;
      bool eCNBOZcALq = false;
      bool zrXYGKdYJm = false;
      bool bONzoXPMRd = false;
      bool CRgQmJPjqH = false;
      bool dYKFYhcXbH = false;
      bool IeaZFPoNMq = false;
      bool KQihogLGlx = false;
      bool tthBIDEHaG = false;
      bool urjKUWqHKX = false;
      bool TBXzwNocQq = false;
      bool WVleMOxYQC = false;
      bool KhmFwSfYMS = false;
      bool pDwNcrWhFt = false;
      bool NaqiiYFExG = false;
      bool YRpIMlORDd = false;
      bool gQPxBSZXCT = false;
      bool qPTWnjqDVW = false;
      bool MbaGsXNnBq = false;
      bool dEdbMxLshQ = false;
      string RQydrhhrdt;
      string tUPFuhmYAf;
      string PVuQTFiRmK;
      string QBlYBTJXgF;
      string mOFMniLlUI;
      string CNSoouUhKm;
      string yQETdshqDa;
      string XOqtrAPicj;
      string txweIChwjF;
      string ybNtGWJlht;
      string BTisjmVXxn;
      string flEZrBTZLa;
      string KkGxbwAxnU;
      string pdAhiZNDtU;
      string fJzuZMWnBE;
      string DjaHiQNkRn;
      string mYjcyBlWqS;
      string mQeptBlKXP;
      string YMuiQGCsyR;
      string LclGgHZWxX;
      if(RQydrhhrdt == BTisjmVXxn){aAwiRmEjMh = true;}
      else if(BTisjmVXxn == RQydrhhrdt){TBXzwNocQq = true;}
      if(tUPFuhmYAf == flEZrBTZLa){eCNBOZcALq = true;}
      else if(flEZrBTZLa == tUPFuhmYAf){WVleMOxYQC = true;}
      if(PVuQTFiRmK == KkGxbwAxnU){zrXYGKdYJm = true;}
      else if(KkGxbwAxnU == PVuQTFiRmK){KhmFwSfYMS = true;}
      if(QBlYBTJXgF == pdAhiZNDtU){bONzoXPMRd = true;}
      else if(pdAhiZNDtU == QBlYBTJXgF){pDwNcrWhFt = true;}
      if(mOFMniLlUI == fJzuZMWnBE){CRgQmJPjqH = true;}
      else if(fJzuZMWnBE == mOFMniLlUI){NaqiiYFExG = true;}
      if(CNSoouUhKm == DjaHiQNkRn){dYKFYhcXbH = true;}
      else if(DjaHiQNkRn == CNSoouUhKm){YRpIMlORDd = true;}
      if(yQETdshqDa == mYjcyBlWqS){IeaZFPoNMq = true;}
      else if(mYjcyBlWqS == yQETdshqDa){gQPxBSZXCT = true;}
      if(XOqtrAPicj == mQeptBlKXP){KQihogLGlx = true;}
      if(txweIChwjF == YMuiQGCsyR){tthBIDEHaG = true;}
      if(ybNtGWJlht == LclGgHZWxX){urjKUWqHKX = true;}
      while(mQeptBlKXP == XOqtrAPicj){qPTWnjqDVW = true;}
      while(YMuiQGCsyR == YMuiQGCsyR){MbaGsXNnBq = true;}
      while(LclGgHZWxX == LclGgHZWxX){dEdbMxLshQ = true;}
      if(aAwiRmEjMh == true){aAwiRmEjMh = false;}
      if(eCNBOZcALq == true){eCNBOZcALq = false;}
      if(zrXYGKdYJm == true){zrXYGKdYJm = false;}
      if(bONzoXPMRd == true){bONzoXPMRd = false;}
      if(CRgQmJPjqH == true){CRgQmJPjqH = false;}
      if(dYKFYhcXbH == true){dYKFYhcXbH = false;}
      if(IeaZFPoNMq == true){IeaZFPoNMq = false;}
      if(KQihogLGlx == true){KQihogLGlx = false;}
      if(tthBIDEHaG == true){tthBIDEHaG = false;}
      if(urjKUWqHKX == true){urjKUWqHKX = false;}
      if(TBXzwNocQq == true){TBXzwNocQq = false;}
      if(WVleMOxYQC == true){WVleMOxYQC = false;}
      if(KhmFwSfYMS == true){KhmFwSfYMS = false;}
      if(pDwNcrWhFt == true){pDwNcrWhFt = false;}
      if(NaqiiYFExG == true){NaqiiYFExG = false;}
      if(YRpIMlORDd == true){YRpIMlORDd = false;}
      if(gQPxBSZXCT == true){gQPxBSZXCT = false;}
      if(qPTWnjqDVW == true){qPTWnjqDVW = false;}
      if(MbaGsXNnBq == true){MbaGsXNnBq = false;}
      if(dEdbMxLshQ == true){dEdbMxLshQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZNWWVOMNB
{ 
  void JyihPZAkfs()
  { 
      bool dQJjKmypKb = false;
      bool thVxQSazLR = false;
      bool IrsVMCKZBf = false;
      bool LAxeVkKYIi = false;
      bool JhxpOBKDAA = false;
      bool glbxalWmWH = false;
      bool cYnePtjqae = false;
      bool HBqcIatDHL = false;
      bool qHZByZXAEi = false;
      bool OXCAFjsSaT = false;
      bool QTbUrfuyoA = false;
      bool qTfKPVymfo = false;
      bool VilrQjypXX = false;
      bool gbbmtXeEJS = false;
      bool eZLDquqqki = false;
      bool kGlkyghjDI = false;
      bool gFZRTPqsPr = false;
      bool ptcMKwXiAV = false;
      bool rHEolZpqnM = false;
      bool ouBBkZzsjb = false;
      string RNCWePKHqi;
      string PrNpyRpyCa;
      string weReNgYWuQ;
      string kdIAXgEUEo;
      string weKdMcHltL;
      string QTshomuWIy;
      string pmMZxkjMRQ;
      string MUtMdQUnSk;
      string YmcjAQjZLj;
      string lgMFyISjfa;
      string suTcyuYfDX;
      string RHEXZDKcYg;
      string BKAheeIoNU;
      string yjHrrcSzkE;
      string rDVnRdcofu;
      string ypKzYhtlyT;
      string ljShYhzMew;
      string jKqUnxnMPA;
      string CTISVHYHSJ;
      string igARSIknOj;
      if(RNCWePKHqi == suTcyuYfDX){dQJjKmypKb = true;}
      else if(suTcyuYfDX == RNCWePKHqi){QTbUrfuyoA = true;}
      if(PrNpyRpyCa == RHEXZDKcYg){thVxQSazLR = true;}
      else if(RHEXZDKcYg == PrNpyRpyCa){qTfKPVymfo = true;}
      if(weReNgYWuQ == BKAheeIoNU){IrsVMCKZBf = true;}
      else if(BKAheeIoNU == weReNgYWuQ){VilrQjypXX = true;}
      if(kdIAXgEUEo == yjHrrcSzkE){LAxeVkKYIi = true;}
      else if(yjHrrcSzkE == kdIAXgEUEo){gbbmtXeEJS = true;}
      if(weKdMcHltL == rDVnRdcofu){JhxpOBKDAA = true;}
      else if(rDVnRdcofu == weKdMcHltL){eZLDquqqki = true;}
      if(QTshomuWIy == ypKzYhtlyT){glbxalWmWH = true;}
      else if(ypKzYhtlyT == QTshomuWIy){kGlkyghjDI = true;}
      if(pmMZxkjMRQ == ljShYhzMew){cYnePtjqae = true;}
      else if(ljShYhzMew == pmMZxkjMRQ){gFZRTPqsPr = true;}
      if(MUtMdQUnSk == jKqUnxnMPA){HBqcIatDHL = true;}
      if(YmcjAQjZLj == CTISVHYHSJ){qHZByZXAEi = true;}
      if(lgMFyISjfa == igARSIknOj){OXCAFjsSaT = true;}
      while(jKqUnxnMPA == MUtMdQUnSk){ptcMKwXiAV = true;}
      while(CTISVHYHSJ == CTISVHYHSJ){rHEolZpqnM = true;}
      while(igARSIknOj == igARSIknOj){ouBBkZzsjb = true;}
      if(dQJjKmypKb == true){dQJjKmypKb = false;}
      if(thVxQSazLR == true){thVxQSazLR = false;}
      if(IrsVMCKZBf == true){IrsVMCKZBf = false;}
      if(LAxeVkKYIi == true){LAxeVkKYIi = false;}
      if(JhxpOBKDAA == true){JhxpOBKDAA = false;}
      if(glbxalWmWH == true){glbxalWmWH = false;}
      if(cYnePtjqae == true){cYnePtjqae = false;}
      if(HBqcIatDHL == true){HBqcIatDHL = false;}
      if(qHZByZXAEi == true){qHZByZXAEi = false;}
      if(OXCAFjsSaT == true){OXCAFjsSaT = false;}
      if(QTbUrfuyoA == true){QTbUrfuyoA = false;}
      if(qTfKPVymfo == true){qTfKPVymfo = false;}
      if(VilrQjypXX == true){VilrQjypXX = false;}
      if(gbbmtXeEJS == true){gbbmtXeEJS = false;}
      if(eZLDquqqki == true){eZLDquqqki = false;}
      if(kGlkyghjDI == true){kGlkyghjDI = false;}
      if(gFZRTPqsPr == true){gFZRTPqsPr = false;}
      if(ptcMKwXiAV == true){ptcMKwXiAV = false;}
      if(rHEolZpqnM == true){rHEolZpqnM = false;}
      if(ouBBkZzsjb == true){ouBBkZzsjb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JXGMUYQQEY
{ 
  void suniCQaDcU()
  { 
      bool WJzRELozzl = false;
      bool oDfoLPunwh = false;
      bool krQzjmFLjW = false;
      bool PWrdHNILfH = false;
      bool InojTqfYcT = false;
      bool SQsFpdrAgQ = false;
      bool GcPcWSKCgy = false;
      bool GiIoZxCger = false;
      bool HfiQDydmmd = false;
      bool UIdOBfYMMB = false;
      bool gdrdMjIDer = false;
      bool aLUnJZtyYX = false;
      bool oXODcyEsnt = false;
      bool YpTdLdnEES = false;
      bool pZHuCJmpFa = false;
      bool lZmoLIOnBN = false;
      bool eOPkTkqqcf = false;
      bool lotGgOPTAS = false;
      bool LOnMIyCdRC = false;
      bool OzCpmbJWaQ = false;
      string EmprOERIEk;
      string kuBDnBZRWu;
      string NVAlooTfKf;
      string YsJLPuSfhi;
      string RLTTAHZeuk;
      string ikApWhlECZ;
      string jlxYMrlonr;
      string htjmcBCflh;
      string OnjZxnrSog;
      string JOcIzfNuHH;
      string VjqCCoANNU;
      string fFRUKuBXbX;
      string ASAGiTQbnx;
      string nGYdMewhWH;
      string meFUBDwIxD;
      string epTjHCikTi;
      string XYYPgYgmIf;
      string ySATkUMfFe;
      string WIdjSymnWJ;
      string uLNniNFpnb;
      if(EmprOERIEk == VjqCCoANNU){WJzRELozzl = true;}
      else if(VjqCCoANNU == EmprOERIEk){gdrdMjIDer = true;}
      if(kuBDnBZRWu == fFRUKuBXbX){oDfoLPunwh = true;}
      else if(fFRUKuBXbX == kuBDnBZRWu){aLUnJZtyYX = true;}
      if(NVAlooTfKf == ASAGiTQbnx){krQzjmFLjW = true;}
      else if(ASAGiTQbnx == NVAlooTfKf){oXODcyEsnt = true;}
      if(YsJLPuSfhi == nGYdMewhWH){PWrdHNILfH = true;}
      else if(nGYdMewhWH == YsJLPuSfhi){YpTdLdnEES = true;}
      if(RLTTAHZeuk == meFUBDwIxD){InojTqfYcT = true;}
      else if(meFUBDwIxD == RLTTAHZeuk){pZHuCJmpFa = true;}
      if(ikApWhlECZ == epTjHCikTi){SQsFpdrAgQ = true;}
      else if(epTjHCikTi == ikApWhlECZ){lZmoLIOnBN = true;}
      if(jlxYMrlonr == XYYPgYgmIf){GcPcWSKCgy = true;}
      else if(XYYPgYgmIf == jlxYMrlonr){eOPkTkqqcf = true;}
      if(htjmcBCflh == ySATkUMfFe){GiIoZxCger = true;}
      if(OnjZxnrSog == WIdjSymnWJ){HfiQDydmmd = true;}
      if(JOcIzfNuHH == uLNniNFpnb){UIdOBfYMMB = true;}
      while(ySATkUMfFe == htjmcBCflh){lotGgOPTAS = true;}
      while(WIdjSymnWJ == WIdjSymnWJ){LOnMIyCdRC = true;}
      while(uLNniNFpnb == uLNniNFpnb){OzCpmbJWaQ = true;}
      if(WJzRELozzl == true){WJzRELozzl = false;}
      if(oDfoLPunwh == true){oDfoLPunwh = false;}
      if(krQzjmFLjW == true){krQzjmFLjW = false;}
      if(PWrdHNILfH == true){PWrdHNILfH = false;}
      if(InojTqfYcT == true){InojTqfYcT = false;}
      if(SQsFpdrAgQ == true){SQsFpdrAgQ = false;}
      if(GcPcWSKCgy == true){GcPcWSKCgy = false;}
      if(GiIoZxCger == true){GiIoZxCger = false;}
      if(HfiQDydmmd == true){HfiQDydmmd = false;}
      if(UIdOBfYMMB == true){UIdOBfYMMB = false;}
      if(gdrdMjIDer == true){gdrdMjIDer = false;}
      if(aLUnJZtyYX == true){aLUnJZtyYX = false;}
      if(oXODcyEsnt == true){oXODcyEsnt = false;}
      if(YpTdLdnEES == true){YpTdLdnEES = false;}
      if(pZHuCJmpFa == true){pZHuCJmpFa = false;}
      if(lZmoLIOnBN == true){lZmoLIOnBN = false;}
      if(eOPkTkqqcf == true){eOPkTkqqcf = false;}
      if(lotGgOPTAS == true){lotGgOPTAS = false;}
      if(LOnMIyCdRC == true){LOnMIyCdRC = false;}
      if(OzCpmbJWaQ == true){OzCpmbJWaQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXVIHGJUIM
{ 
  void fudGOnQdGH()
  { 
      bool phYKiVCFPH = false;
      bool izqYIPJRKs = false;
      bool nnyXBZbCIZ = false;
      bool NhZXwZIDij = false;
      bool PKQZucuMyh = false;
      bool IYJtXCjAJJ = false;
      bool sAxptBYSci = false;
      bool GFiZdcWXbX = false;
      bool dPEZQnXezs = false;
      bool pItYpPNaft = false;
      bool DciObCpjQu = false;
      bool fLXkeduWZG = false;
      bool dsSisyLJiO = false;
      bool PwrhTBfoyN = false;
      bool ymOENdjItM = false;
      bool TqAZPKJzVc = false;
      bool qfABfiToRd = false;
      bool xGYLHqeOVO = false;
      bool NDPWuXuSSJ = false;
      bool qfTUVRlNYe = false;
      string jPuKiDDCXG;
      string MNDegNSEft;
      string GKYixxflKS;
      string EHgAaMCKst;
      string LjSrwFekez;
      string PlioLZpMMk;
      string WRrFBEfDEU;
      string LHLkiVqflq;
      string RuHLDRYroA;
      string VoxHXsrNqr;
      string ZbfKmHaxGo;
      string hJaUTbKgCi;
      string fnODyWJDNo;
      string ccotRpOxXu;
      string qakzSLObnu;
      string iLLIMlNbLQ;
      string xXjQLFUfDd;
      string MNIGrECOkm;
      string HhORGRQghe;
      string blkGySqUnM;
      if(jPuKiDDCXG == ZbfKmHaxGo){phYKiVCFPH = true;}
      else if(ZbfKmHaxGo == jPuKiDDCXG){DciObCpjQu = true;}
      if(MNDegNSEft == hJaUTbKgCi){izqYIPJRKs = true;}
      else if(hJaUTbKgCi == MNDegNSEft){fLXkeduWZG = true;}
      if(GKYixxflKS == fnODyWJDNo){nnyXBZbCIZ = true;}
      else if(fnODyWJDNo == GKYixxflKS){dsSisyLJiO = true;}
      if(EHgAaMCKst == ccotRpOxXu){NhZXwZIDij = true;}
      else if(ccotRpOxXu == EHgAaMCKst){PwrhTBfoyN = true;}
      if(LjSrwFekez == qakzSLObnu){PKQZucuMyh = true;}
      else if(qakzSLObnu == LjSrwFekez){ymOENdjItM = true;}
      if(PlioLZpMMk == iLLIMlNbLQ){IYJtXCjAJJ = true;}
      else if(iLLIMlNbLQ == PlioLZpMMk){TqAZPKJzVc = true;}
      if(WRrFBEfDEU == xXjQLFUfDd){sAxptBYSci = true;}
      else if(xXjQLFUfDd == WRrFBEfDEU){qfABfiToRd = true;}
      if(LHLkiVqflq == MNIGrECOkm){GFiZdcWXbX = true;}
      if(RuHLDRYroA == HhORGRQghe){dPEZQnXezs = true;}
      if(VoxHXsrNqr == blkGySqUnM){pItYpPNaft = true;}
      while(MNIGrECOkm == LHLkiVqflq){xGYLHqeOVO = true;}
      while(HhORGRQghe == HhORGRQghe){NDPWuXuSSJ = true;}
      while(blkGySqUnM == blkGySqUnM){qfTUVRlNYe = true;}
      if(phYKiVCFPH == true){phYKiVCFPH = false;}
      if(izqYIPJRKs == true){izqYIPJRKs = false;}
      if(nnyXBZbCIZ == true){nnyXBZbCIZ = false;}
      if(NhZXwZIDij == true){NhZXwZIDij = false;}
      if(PKQZucuMyh == true){PKQZucuMyh = false;}
      if(IYJtXCjAJJ == true){IYJtXCjAJJ = false;}
      if(sAxptBYSci == true){sAxptBYSci = false;}
      if(GFiZdcWXbX == true){GFiZdcWXbX = false;}
      if(dPEZQnXezs == true){dPEZQnXezs = false;}
      if(pItYpPNaft == true){pItYpPNaft = false;}
      if(DciObCpjQu == true){DciObCpjQu = false;}
      if(fLXkeduWZG == true){fLXkeduWZG = false;}
      if(dsSisyLJiO == true){dsSisyLJiO = false;}
      if(PwrhTBfoyN == true){PwrhTBfoyN = false;}
      if(ymOENdjItM == true){ymOENdjItM = false;}
      if(TqAZPKJzVc == true){TqAZPKJzVc = false;}
      if(qfABfiToRd == true){qfABfiToRd = false;}
      if(xGYLHqeOVO == true){xGYLHqeOVO = false;}
      if(NDPWuXuSSJ == true){NDPWuXuSSJ = false;}
      if(qfTUVRlNYe == true){qfTUVRlNYe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OUMIQIVLMW
{ 
  void ylXEInECPz()
  { 
      bool BlYbwqEWrW = false;
      bool RsIhFZgCsd = false;
      bool wnDbPPDJTG = false;
      bool HkuMYLgDse = false;
      bool cHIOdWTBza = false;
      bool TgDERNiwLg = false;
      bool muDlPgxwIt = false;
      bool rdJOAnenxs = false;
      bool wCJrmahqtK = false;
      bool ckqMrhDWzx = false;
      bool YWrFioWoDc = false;
      bool itySjkkKyo = false;
      bool zGByRGmxWS = false;
      bool kHoATYJEJx = false;
      bool DrmRbhmXbH = false;
      bool xrXKySVtmb = false;
      bool CZSkraFyyL = false;
      bool afBBkGTiVi = false;
      bool TOUPUridBB = false;
      bool DPQgtcZBZA = false;
      string phKlATlYpy;
      string WfpBshKefP;
      string BbVlTDGpLX;
      string SAFNAtplVG;
      string FGLAEYWyYW;
      string HHyaGNMXRx;
      string MwNRfVacAz;
      string rXJZJtQVhu;
      string fIQnQKCdGl;
      string hRTXsJssUh;
      string xtxZejxYQM;
      string xppWQDeYBU;
      string TwWORZDkfA;
      string BWBAxlLqJg;
      string McNsnqbxGo;
      string dTrzNBWiIE;
      string fLsPLaooYe;
      string rmOUHqidZZ;
      string yGepVgeBlw;
      string PciFAAjxhN;
      if(phKlATlYpy == xtxZejxYQM){BlYbwqEWrW = true;}
      else if(xtxZejxYQM == phKlATlYpy){YWrFioWoDc = true;}
      if(WfpBshKefP == xppWQDeYBU){RsIhFZgCsd = true;}
      else if(xppWQDeYBU == WfpBshKefP){itySjkkKyo = true;}
      if(BbVlTDGpLX == TwWORZDkfA){wnDbPPDJTG = true;}
      else if(TwWORZDkfA == BbVlTDGpLX){zGByRGmxWS = true;}
      if(SAFNAtplVG == BWBAxlLqJg){HkuMYLgDse = true;}
      else if(BWBAxlLqJg == SAFNAtplVG){kHoATYJEJx = true;}
      if(FGLAEYWyYW == McNsnqbxGo){cHIOdWTBza = true;}
      else if(McNsnqbxGo == FGLAEYWyYW){DrmRbhmXbH = true;}
      if(HHyaGNMXRx == dTrzNBWiIE){TgDERNiwLg = true;}
      else if(dTrzNBWiIE == HHyaGNMXRx){xrXKySVtmb = true;}
      if(MwNRfVacAz == fLsPLaooYe){muDlPgxwIt = true;}
      else if(fLsPLaooYe == MwNRfVacAz){CZSkraFyyL = true;}
      if(rXJZJtQVhu == rmOUHqidZZ){rdJOAnenxs = true;}
      if(fIQnQKCdGl == yGepVgeBlw){wCJrmahqtK = true;}
      if(hRTXsJssUh == PciFAAjxhN){ckqMrhDWzx = true;}
      while(rmOUHqidZZ == rXJZJtQVhu){afBBkGTiVi = true;}
      while(yGepVgeBlw == yGepVgeBlw){TOUPUridBB = true;}
      while(PciFAAjxhN == PciFAAjxhN){DPQgtcZBZA = true;}
      if(BlYbwqEWrW == true){BlYbwqEWrW = false;}
      if(RsIhFZgCsd == true){RsIhFZgCsd = false;}
      if(wnDbPPDJTG == true){wnDbPPDJTG = false;}
      if(HkuMYLgDse == true){HkuMYLgDse = false;}
      if(cHIOdWTBza == true){cHIOdWTBza = false;}
      if(TgDERNiwLg == true){TgDERNiwLg = false;}
      if(muDlPgxwIt == true){muDlPgxwIt = false;}
      if(rdJOAnenxs == true){rdJOAnenxs = false;}
      if(wCJrmahqtK == true){wCJrmahqtK = false;}
      if(ckqMrhDWzx == true){ckqMrhDWzx = false;}
      if(YWrFioWoDc == true){YWrFioWoDc = false;}
      if(itySjkkKyo == true){itySjkkKyo = false;}
      if(zGByRGmxWS == true){zGByRGmxWS = false;}
      if(kHoATYJEJx == true){kHoATYJEJx = false;}
      if(DrmRbhmXbH == true){DrmRbhmXbH = false;}
      if(xrXKySVtmb == true){xrXKySVtmb = false;}
      if(CZSkraFyyL == true){CZSkraFyyL = false;}
      if(afBBkGTiVi == true){afBBkGTiVi = false;}
      if(TOUPUridBB == true){TOUPUridBB = false;}
      if(DPQgtcZBZA == true){DPQgtcZBZA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DQYOIDBQNY
{ 
  void BdmJTncTLL()
  { 
      bool oxPCquWlus = false;
      bool TKkIMyVfja = false;
      bool qBOYHoPlpT = false;
      bool fMRoUEIbVL = false;
      bool sfaOHPNVAN = false;
      bool eZldGnhqtB = false;
      bool fjuaMHswnH = false;
      bool otKYgLZAQq = false;
      bool aslcoFZmhg = false;
      bool VRgTeIjABA = false;
      bool VRhrXjPNwu = false;
      bool NgZCamySlH = false;
      bool gFNGkXNpsX = false;
      bool aZzQVJLtEE = false;
      bool oLpmSoqdsr = false;
      bool KRNsSQEaGA = false;
      bool WZUYUnhJgQ = false;
      bool aEOgRUOZnw = false;
      bool fiwAMJLFxF = false;
      bool EjmEhPqRRd = false;
      string nfItusOeVE;
      string hYgtFrmNny;
      string Sousiyketo;
      string TJXoXIrEXB;
      string RhHWoDqqni;
      string tDXUOyjOKx;
      string HikgkXBrVw;
      string zholfjhYEf;
      string HtpKuPkDZY;
      string YdtasixalR;
      string BzUqjLOlnd;
      string QLJdpNsZlV;
      string lyRwXVnOrx;
      string mHmmeHYyai;
      string AzOuINTPjf;
      string pWnPeDgYTN;
      string WAsqqJXWzh;
      string otzCUliVmK;
      string BYdMHQSWHa;
      string azeMLAGWEy;
      if(nfItusOeVE == BzUqjLOlnd){oxPCquWlus = true;}
      else if(BzUqjLOlnd == nfItusOeVE){VRhrXjPNwu = true;}
      if(hYgtFrmNny == QLJdpNsZlV){TKkIMyVfja = true;}
      else if(QLJdpNsZlV == hYgtFrmNny){NgZCamySlH = true;}
      if(Sousiyketo == lyRwXVnOrx){qBOYHoPlpT = true;}
      else if(lyRwXVnOrx == Sousiyketo){gFNGkXNpsX = true;}
      if(TJXoXIrEXB == mHmmeHYyai){fMRoUEIbVL = true;}
      else if(mHmmeHYyai == TJXoXIrEXB){aZzQVJLtEE = true;}
      if(RhHWoDqqni == AzOuINTPjf){sfaOHPNVAN = true;}
      else if(AzOuINTPjf == RhHWoDqqni){oLpmSoqdsr = true;}
      if(tDXUOyjOKx == pWnPeDgYTN){eZldGnhqtB = true;}
      else if(pWnPeDgYTN == tDXUOyjOKx){KRNsSQEaGA = true;}
      if(HikgkXBrVw == WAsqqJXWzh){fjuaMHswnH = true;}
      else if(WAsqqJXWzh == HikgkXBrVw){WZUYUnhJgQ = true;}
      if(zholfjhYEf == otzCUliVmK){otKYgLZAQq = true;}
      if(HtpKuPkDZY == BYdMHQSWHa){aslcoFZmhg = true;}
      if(YdtasixalR == azeMLAGWEy){VRgTeIjABA = true;}
      while(otzCUliVmK == zholfjhYEf){aEOgRUOZnw = true;}
      while(BYdMHQSWHa == BYdMHQSWHa){fiwAMJLFxF = true;}
      while(azeMLAGWEy == azeMLAGWEy){EjmEhPqRRd = true;}
      if(oxPCquWlus == true){oxPCquWlus = false;}
      if(TKkIMyVfja == true){TKkIMyVfja = false;}
      if(qBOYHoPlpT == true){qBOYHoPlpT = false;}
      if(fMRoUEIbVL == true){fMRoUEIbVL = false;}
      if(sfaOHPNVAN == true){sfaOHPNVAN = false;}
      if(eZldGnhqtB == true){eZldGnhqtB = false;}
      if(fjuaMHswnH == true){fjuaMHswnH = false;}
      if(otKYgLZAQq == true){otKYgLZAQq = false;}
      if(aslcoFZmhg == true){aslcoFZmhg = false;}
      if(VRgTeIjABA == true){VRgTeIjABA = false;}
      if(VRhrXjPNwu == true){VRhrXjPNwu = false;}
      if(NgZCamySlH == true){NgZCamySlH = false;}
      if(gFNGkXNpsX == true){gFNGkXNpsX = false;}
      if(aZzQVJLtEE == true){aZzQVJLtEE = false;}
      if(oLpmSoqdsr == true){oLpmSoqdsr = false;}
      if(KRNsSQEaGA == true){KRNsSQEaGA = false;}
      if(WZUYUnhJgQ == true){WZUYUnhJgQ = false;}
      if(aEOgRUOZnw == true){aEOgRUOZnw = false;}
      if(fiwAMJLFxF == true){fiwAMJLFxF = false;}
      if(EjmEhPqRRd == true){EjmEhPqRRd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class STQLJZTWMF
{ 
  void QyCnVIoPWX()
  { 
      bool OwHAcOaAiT = false;
      bool CuuCfqaqWG = false;
      bool BFiXqNuSHj = false;
      bool pXsdoksVmS = false;
      bool sewkaXHySV = false;
      bool cnAKeIMiIO = false;
      bool SHrzcdCQMu = false;
      bool yFEENVJyxT = false;
      bool GwAlGCWhzf = false;
      bool XKMYzkmwHx = false;
      bool UqkXXXiwxJ = false;
      bool zOloHVHGsa = false;
      bool GTRgWmseEb = false;
      bool iMpzyOLcNi = false;
      bool SajofJYWQc = false;
      bool dfDgpAZDAj = false;
      bool eDqUamXlqs = false;
      bool KesKHfjbBM = false;
      bool OVObyCIJJx = false;
      bool oHbcEOiOOr = false;
      string bDpgBxptsu;
      string NLCGqqFiGj;
      string qnwJIilVSG;
      string cyTNkwBJLd;
      string gClfOMyzEW;
      string yAtyemGfXS;
      string LTblSOrnVt;
      string ouXcDnCQuu;
      string jlQuIcEVix;
      string pVlrSMZzMz;
      string UKdKhCbRtp;
      string jojciYCfco;
      string JWEXESJeJq;
      string OCDuaYIGNG;
      string BmasNAkIJs;
      string KtWXpxGFGO;
      string rwHDagkoBJ;
      string QuSVnVuKKD;
      string hAVPgUffFc;
      string SCAzNEeXRf;
      if(bDpgBxptsu == UKdKhCbRtp){OwHAcOaAiT = true;}
      else if(UKdKhCbRtp == bDpgBxptsu){UqkXXXiwxJ = true;}
      if(NLCGqqFiGj == jojciYCfco){CuuCfqaqWG = true;}
      else if(jojciYCfco == NLCGqqFiGj){zOloHVHGsa = true;}
      if(qnwJIilVSG == JWEXESJeJq){BFiXqNuSHj = true;}
      else if(JWEXESJeJq == qnwJIilVSG){GTRgWmseEb = true;}
      if(cyTNkwBJLd == OCDuaYIGNG){pXsdoksVmS = true;}
      else if(OCDuaYIGNG == cyTNkwBJLd){iMpzyOLcNi = true;}
      if(gClfOMyzEW == BmasNAkIJs){sewkaXHySV = true;}
      else if(BmasNAkIJs == gClfOMyzEW){SajofJYWQc = true;}
      if(yAtyemGfXS == KtWXpxGFGO){cnAKeIMiIO = true;}
      else if(KtWXpxGFGO == yAtyemGfXS){dfDgpAZDAj = true;}
      if(LTblSOrnVt == rwHDagkoBJ){SHrzcdCQMu = true;}
      else if(rwHDagkoBJ == LTblSOrnVt){eDqUamXlqs = true;}
      if(ouXcDnCQuu == QuSVnVuKKD){yFEENVJyxT = true;}
      if(jlQuIcEVix == hAVPgUffFc){GwAlGCWhzf = true;}
      if(pVlrSMZzMz == SCAzNEeXRf){XKMYzkmwHx = true;}
      while(QuSVnVuKKD == ouXcDnCQuu){KesKHfjbBM = true;}
      while(hAVPgUffFc == hAVPgUffFc){OVObyCIJJx = true;}
      while(SCAzNEeXRf == SCAzNEeXRf){oHbcEOiOOr = true;}
      if(OwHAcOaAiT == true){OwHAcOaAiT = false;}
      if(CuuCfqaqWG == true){CuuCfqaqWG = false;}
      if(BFiXqNuSHj == true){BFiXqNuSHj = false;}
      if(pXsdoksVmS == true){pXsdoksVmS = false;}
      if(sewkaXHySV == true){sewkaXHySV = false;}
      if(cnAKeIMiIO == true){cnAKeIMiIO = false;}
      if(SHrzcdCQMu == true){SHrzcdCQMu = false;}
      if(yFEENVJyxT == true){yFEENVJyxT = false;}
      if(GwAlGCWhzf == true){GwAlGCWhzf = false;}
      if(XKMYzkmwHx == true){XKMYzkmwHx = false;}
      if(UqkXXXiwxJ == true){UqkXXXiwxJ = false;}
      if(zOloHVHGsa == true){zOloHVHGsa = false;}
      if(GTRgWmseEb == true){GTRgWmseEb = false;}
      if(iMpzyOLcNi == true){iMpzyOLcNi = false;}
      if(SajofJYWQc == true){SajofJYWQc = false;}
      if(dfDgpAZDAj == true){dfDgpAZDAj = false;}
      if(eDqUamXlqs == true){eDqUamXlqs = false;}
      if(KesKHfjbBM == true){KesKHfjbBM = false;}
      if(OVObyCIJJx == true){OVObyCIJJx = false;}
      if(oHbcEOiOOr == true){oHbcEOiOOr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ALXTLHWAIR
{ 
  void XmRfLrrbgx()
  { 
      bool GwkZWUstfr = false;
      bool LaVtZkRiwN = false;
      bool jOJxyhSslI = false;
      bool DcDWwaYNIZ = false;
      bool ignUpBMMLW = false;
      bool YeQmZqlnbo = false;
      bool BAIXohWyxz = false;
      bool LDZVdCaoHw = false;
      bool UFgPiXMQxE = false;
      bool nklTXiYPfH = false;
      bool dOOMKUFuIW = false;
      bool QxgeTwTrnQ = false;
      bool VGArLaRGxu = false;
      bool cKIzSGpUFO = false;
      bool SRHZnpEHzb = false;
      bool OgaOlXNVAi = false;
      bool CyxNtFngMM = false;
      bool FzmZyEzZEU = false;
      bool WKGVfwitNt = false;
      bool sUTWLTTsfh = false;
      string LqXZWiXMMp;
      string HyJcDCYciA;
      string VfhuWBsCWU;
      string GAWYcitpEc;
      string pddIOXOEJx;
      string ZRnnleIcCV;
      string oUoqiHbkAT;
      string IiXGJqCYfz;
      string losYtoLhmy;
      string ZQnimVolYH;
      string udEpoqshet;
      string cjwCiAbPxt;
      string wsxCsqunSn;
      string CQzYDIjDjD;
      string udDrVpTkAm;
      string sYneKBfCwx;
      string uFOpqLjXza;
      string PYetyRpFgC;
      string WKmftcbUNB;
      string bhGlHpOMBJ;
      if(LqXZWiXMMp == udEpoqshet){GwkZWUstfr = true;}
      else if(udEpoqshet == LqXZWiXMMp){dOOMKUFuIW = true;}
      if(HyJcDCYciA == cjwCiAbPxt){LaVtZkRiwN = true;}
      else if(cjwCiAbPxt == HyJcDCYciA){QxgeTwTrnQ = true;}
      if(VfhuWBsCWU == wsxCsqunSn){jOJxyhSslI = true;}
      else if(wsxCsqunSn == VfhuWBsCWU){VGArLaRGxu = true;}
      if(GAWYcitpEc == CQzYDIjDjD){DcDWwaYNIZ = true;}
      else if(CQzYDIjDjD == GAWYcitpEc){cKIzSGpUFO = true;}
      if(pddIOXOEJx == udDrVpTkAm){ignUpBMMLW = true;}
      else if(udDrVpTkAm == pddIOXOEJx){SRHZnpEHzb = true;}
      if(ZRnnleIcCV == sYneKBfCwx){YeQmZqlnbo = true;}
      else if(sYneKBfCwx == ZRnnleIcCV){OgaOlXNVAi = true;}
      if(oUoqiHbkAT == uFOpqLjXza){BAIXohWyxz = true;}
      else if(uFOpqLjXza == oUoqiHbkAT){CyxNtFngMM = true;}
      if(IiXGJqCYfz == PYetyRpFgC){LDZVdCaoHw = true;}
      if(losYtoLhmy == WKmftcbUNB){UFgPiXMQxE = true;}
      if(ZQnimVolYH == bhGlHpOMBJ){nklTXiYPfH = true;}
      while(PYetyRpFgC == IiXGJqCYfz){FzmZyEzZEU = true;}
      while(WKmftcbUNB == WKmftcbUNB){WKGVfwitNt = true;}
      while(bhGlHpOMBJ == bhGlHpOMBJ){sUTWLTTsfh = true;}
      if(GwkZWUstfr == true){GwkZWUstfr = false;}
      if(LaVtZkRiwN == true){LaVtZkRiwN = false;}
      if(jOJxyhSslI == true){jOJxyhSslI = false;}
      if(DcDWwaYNIZ == true){DcDWwaYNIZ = false;}
      if(ignUpBMMLW == true){ignUpBMMLW = false;}
      if(YeQmZqlnbo == true){YeQmZqlnbo = false;}
      if(BAIXohWyxz == true){BAIXohWyxz = false;}
      if(LDZVdCaoHw == true){LDZVdCaoHw = false;}
      if(UFgPiXMQxE == true){UFgPiXMQxE = false;}
      if(nklTXiYPfH == true){nklTXiYPfH = false;}
      if(dOOMKUFuIW == true){dOOMKUFuIW = false;}
      if(QxgeTwTrnQ == true){QxgeTwTrnQ = false;}
      if(VGArLaRGxu == true){VGArLaRGxu = false;}
      if(cKIzSGpUFO == true){cKIzSGpUFO = false;}
      if(SRHZnpEHzb == true){SRHZnpEHzb = false;}
      if(OgaOlXNVAi == true){OgaOlXNVAi = false;}
      if(CyxNtFngMM == true){CyxNtFngMM = false;}
      if(FzmZyEzZEU == true){FzmZyEzZEU = false;}
      if(WKGVfwitNt == true){WKGVfwitNt = false;}
      if(sUTWLTTsfh == true){sUTWLTTsfh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YPHNOXFXHA
{ 
  void CUXcBkAacZ()
  { 
      bool sKxcRnqQCg = false;
      bool FzEfSwATTQ = false;
      bool tkxOAUrQZO = false;
      bool ucZCidLXsQ = false;
      bool nGUGlmJfOh = false;
      bool tYKptIMicx = false;
      bool wZqnkbZCwn = false;
      bool kbZDbnPqbM = false;
      bool KLCqTVRiHZ = false;
      bool RbuwUOPgUK = false;
      bool NHiaxRyHNG = false;
      bool sUHPljXzTO = false;
      bool JptWWIfdhN = false;
      bool XiVRyCcbtB = false;
      bool XJVBgwUeKk = false;
      bool qPMFAWNMDn = false;
      bool lUYAhJyoQi = false;
      bool GwFRqAUsoZ = false;
      bool mATxWIWQQb = false;
      bool oPXFPDkVSX = false;
      string aiejAiEPzw;
      string suzFOtmDML;
      string zKoxrJcWuE;
      string aRIqjoVIND;
      string yzFmIMYSOP;
      string zJBiTQsgrq;
      string GhUtVblIUZ;
      string XeoJNAEBnf;
      string jKIfFQPZWT;
      string unQWxQdLRg;
      string ZQxnqTTqVS;
      string LrrLGwYnoF;
      string LMkAejNRMw;
      string VsjHFSMUok;
      string wXEEICuEQB;
      string rpVLUNfxIH;
      string FBeYxSIkGm;
      string iDzEInIgrc;
      string nJBLEfXXmr;
      string mOLhetseHo;
      if(aiejAiEPzw == ZQxnqTTqVS){sKxcRnqQCg = true;}
      else if(ZQxnqTTqVS == aiejAiEPzw){NHiaxRyHNG = true;}
      if(suzFOtmDML == LrrLGwYnoF){FzEfSwATTQ = true;}
      else if(LrrLGwYnoF == suzFOtmDML){sUHPljXzTO = true;}
      if(zKoxrJcWuE == LMkAejNRMw){tkxOAUrQZO = true;}
      else if(LMkAejNRMw == zKoxrJcWuE){JptWWIfdhN = true;}
      if(aRIqjoVIND == VsjHFSMUok){ucZCidLXsQ = true;}
      else if(VsjHFSMUok == aRIqjoVIND){XiVRyCcbtB = true;}
      if(yzFmIMYSOP == wXEEICuEQB){nGUGlmJfOh = true;}
      else if(wXEEICuEQB == yzFmIMYSOP){XJVBgwUeKk = true;}
      if(zJBiTQsgrq == rpVLUNfxIH){tYKptIMicx = true;}
      else if(rpVLUNfxIH == zJBiTQsgrq){qPMFAWNMDn = true;}
      if(GhUtVblIUZ == FBeYxSIkGm){wZqnkbZCwn = true;}
      else if(FBeYxSIkGm == GhUtVblIUZ){lUYAhJyoQi = true;}
      if(XeoJNAEBnf == iDzEInIgrc){kbZDbnPqbM = true;}
      if(jKIfFQPZWT == nJBLEfXXmr){KLCqTVRiHZ = true;}
      if(unQWxQdLRg == mOLhetseHo){RbuwUOPgUK = true;}
      while(iDzEInIgrc == XeoJNAEBnf){GwFRqAUsoZ = true;}
      while(nJBLEfXXmr == nJBLEfXXmr){mATxWIWQQb = true;}
      while(mOLhetseHo == mOLhetseHo){oPXFPDkVSX = true;}
      if(sKxcRnqQCg == true){sKxcRnqQCg = false;}
      if(FzEfSwATTQ == true){FzEfSwATTQ = false;}
      if(tkxOAUrQZO == true){tkxOAUrQZO = false;}
      if(ucZCidLXsQ == true){ucZCidLXsQ = false;}
      if(nGUGlmJfOh == true){nGUGlmJfOh = false;}
      if(tYKptIMicx == true){tYKptIMicx = false;}
      if(wZqnkbZCwn == true){wZqnkbZCwn = false;}
      if(kbZDbnPqbM == true){kbZDbnPqbM = false;}
      if(KLCqTVRiHZ == true){KLCqTVRiHZ = false;}
      if(RbuwUOPgUK == true){RbuwUOPgUK = false;}
      if(NHiaxRyHNG == true){NHiaxRyHNG = false;}
      if(sUHPljXzTO == true){sUHPljXzTO = false;}
      if(JptWWIfdhN == true){JptWWIfdhN = false;}
      if(XiVRyCcbtB == true){XiVRyCcbtB = false;}
      if(XJVBgwUeKk == true){XJVBgwUeKk = false;}
      if(qPMFAWNMDn == true){qPMFAWNMDn = false;}
      if(lUYAhJyoQi == true){lUYAhJyoQi = false;}
      if(GwFRqAUsoZ == true){GwFRqAUsoZ = false;}
      if(mATxWIWQQb == true){mATxWIWQQb = false;}
      if(oPXFPDkVSX == true){oPXFPDkVSX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CARYHMCJZD
{ 
  void xAuAINgzHw()
  { 
      bool mukLMoNzmd = false;
      bool bnFfnORQYY = false;
      bool ZFFAPrfBCx = false;
      bool JTunWZcBUF = false;
      bool znCJhRcdbJ = false;
      bool sSUAhgojuT = false;
      bool JLxoUHrQJN = false;
      bool lQuSYkDuSy = false;
      bool PCYrEpztGp = false;
      bool krFBwnqMoZ = false;
      bool YLUOXcXCbx = false;
      bool csRxEHlEkd = false;
      bool IxKSctKtVk = false;
      bool spGsYDhKUb = false;
      bool SxSJMqZHxo = false;
      bool BmbKRbBBkc = false;
      bool RdfqDlmYYB = false;
      bool ZbiILKeAGk = false;
      bool TDxgiGNuax = false;
      bool BfYrKoQbGZ = false;
      string qqJrxFwLQE;
      string VhIMhUDKno;
      string hsfpQLnYVx;
      string trymwZOjBR;
      string sOYCdzJjpa;
      string GgppxxKSbk;
      string QXoTJdiUPH;
      string GSJVwSUdMQ;
      string CEhupMCHoy;
      string PuHPAUZErA;
      string QnThUnXTte;
      string cgGLiMpsdx;
      string bafRrKKsVa;
      string sPkMANkAaB;
      string ohNKUhowgn;
      string efauXpICpJ;
      string cdyTkNutLU;
      string bpSbIsNUwJ;
      string VNMguMnonK;
      string FiJQYKjsYH;
      if(qqJrxFwLQE == QnThUnXTte){mukLMoNzmd = true;}
      else if(QnThUnXTte == qqJrxFwLQE){YLUOXcXCbx = true;}
      if(VhIMhUDKno == cgGLiMpsdx){bnFfnORQYY = true;}
      else if(cgGLiMpsdx == VhIMhUDKno){csRxEHlEkd = true;}
      if(hsfpQLnYVx == bafRrKKsVa){ZFFAPrfBCx = true;}
      else if(bafRrKKsVa == hsfpQLnYVx){IxKSctKtVk = true;}
      if(trymwZOjBR == sPkMANkAaB){JTunWZcBUF = true;}
      else if(sPkMANkAaB == trymwZOjBR){spGsYDhKUb = true;}
      if(sOYCdzJjpa == ohNKUhowgn){znCJhRcdbJ = true;}
      else if(ohNKUhowgn == sOYCdzJjpa){SxSJMqZHxo = true;}
      if(GgppxxKSbk == efauXpICpJ){sSUAhgojuT = true;}
      else if(efauXpICpJ == GgppxxKSbk){BmbKRbBBkc = true;}
      if(QXoTJdiUPH == cdyTkNutLU){JLxoUHrQJN = true;}
      else if(cdyTkNutLU == QXoTJdiUPH){RdfqDlmYYB = true;}
      if(GSJVwSUdMQ == bpSbIsNUwJ){lQuSYkDuSy = true;}
      if(CEhupMCHoy == VNMguMnonK){PCYrEpztGp = true;}
      if(PuHPAUZErA == FiJQYKjsYH){krFBwnqMoZ = true;}
      while(bpSbIsNUwJ == GSJVwSUdMQ){ZbiILKeAGk = true;}
      while(VNMguMnonK == VNMguMnonK){TDxgiGNuax = true;}
      while(FiJQYKjsYH == FiJQYKjsYH){BfYrKoQbGZ = true;}
      if(mukLMoNzmd == true){mukLMoNzmd = false;}
      if(bnFfnORQYY == true){bnFfnORQYY = false;}
      if(ZFFAPrfBCx == true){ZFFAPrfBCx = false;}
      if(JTunWZcBUF == true){JTunWZcBUF = false;}
      if(znCJhRcdbJ == true){znCJhRcdbJ = false;}
      if(sSUAhgojuT == true){sSUAhgojuT = false;}
      if(JLxoUHrQJN == true){JLxoUHrQJN = false;}
      if(lQuSYkDuSy == true){lQuSYkDuSy = false;}
      if(PCYrEpztGp == true){PCYrEpztGp = false;}
      if(krFBwnqMoZ == true){krFBwnqMoZ = false;}
      if(YLUOXcXCbx == true){YLUOXcXCbx = false;}
      if(csRxEHlEkd == true){csRxEHlEkd = false;}
      if(IxKSctKtVk == true){IxKSctKtVk = false;}
      if(spGsYDhKUb == true){spGsYDhKUb = false;}
      if(SxSJMqZHxo == true){SxSJMqZHxo = false;}
      if(BmbKRbBBkc == true){BmbKRbBBkc = false;}
      if(RdfqDlmYYB == true){RdfqDlmYYB = false;}
      if(ZbiILKeAGk == true){ZbiILKeAGk = false;}
      if(TDxgiGNuax == true){TDxgiGNuax = false;}
      if(BfYrKoQbGZ == true){BfYrKoQbGZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VWQHRNHGVH
{ 
  void BlhBjwSezg()
  { 
      bool BdsZGRmBWs = false;
      bool FMTPyreaEE = false;
      bool XHkAcYBrTN = false;
      bool xUJzdKwlZj = false;
      bool hhJKPNamjT = false;
      bool nfenetsswh = false;
      bool PugIwkCTln = false;
      bool usBUVoyZjP = false;
      bool yOIAZQoVTi = false;
      bool RDoqUmBAOe = false;
      bool KGAwXueKRo = false;
      bool uSIgjAlgie = false;
      bool wgzCVrDJAi = false;
      bool nxLFEqOMbd = false;
      bool ldDdmyuIHT = false;
      bool ATQjhdHxZf = false;
      bool qUKhByHCbr = false;
      bool lZEErScUOX = false;
      bool wuCfiTfaXZ = false;
      bool jQmwmQSVco = false;
      string MUlAWVoJWS;
      string zLhrLsoBJq;
      string eHMaIFkVoG;
      string jFukqYWMot;
      string sgbeJVfkFU;
      string SsdaIFHKqR;
      string jTTQisPxAm;
      string VbMPxxegRm;
      string YAQUmqbUbl;
      string QMUWJZNLwP;
      string GijRypfNdK;
      string aZrEsiDycr;
      string RuUNVJHoGX;
      string jSkCgoQyWw;
      string KNpRLqTQdZ;
      string VOiExKOVun;
      string iqHGZHooWD;
      string SEaggEECCe;
      string opLfBVjgEV;
      string ZtCiMTGjrD;
      if(MUlAWVoJWS == GijRypfNdK){BdsZGRmBWs = true;}
      else if(GijRypfNdK == MUlAWVoJWS){KGAwXueKRo = true;}
      if(zLhrLsoBJq == aZrEsiDycr){FMTPyreaEE = true;}
      else if(aZrEsiDycr == zLhrLsoBJq){uSIgjAlgie = true;}
      if(eHMaIFkVoG == RuUNVJHoGX){XHkAcYBrTN = true;}
      else if(RuUNVJHoGX == eHMaIFkVoG){wgzCVrDJAi = true;}
      if(jFukqYWMot == jSkCgoQyWw){xUJzdKwlZj = true;}
      else if(jSkCgoQyWw == jFukqYWMot){nxLFEqOMbd = true;}
      if(sgbeJVfkFU == KNpRLqTQdZ){hhJKPNamjT = true;}
      else if(KNpRLqTQdZ == sgbeJVfkFU){ldDdmyuIHT = true;}
      if(SsdaIFHKqR == VOiExKOVun){nfenetsswh = true;}
      else if(VOiExKOVun == SsdaIFHKqR){ATQjhdHxZf = true;}
      if(jTTQisPxAm == iqHGZHooWD){PugIwkCTln = true;}
      else if(iqHGZHooWD == jTTQisPxAm){qUKhByHCbr = true;}
      if(VbMPxxegRm == SEaggEECCe){usBUVoyZjP = true;}
      if(YAQUmqbUbl == opLfBVjgEV){yOIAZQoVTi = true;}
      if(QMUWJZNLwP == ZtCiMTGjrD){RDoqUmBAOe = true;}
      while(SEaggEECCe == VbMPxxegRm){lZEErScUOX = true;}
      while(opLfBVjgEV == opLfBVjgEV){wuCfiTfaXZ = true;}
      while(ZtCiMTGjrD == ZtCiMTGjrD){jQmwmQSVco = true;}
      if(BdsZGRmBWs == true){BdsZGRmBWs = false;}
      if(FMTPyreaEE == true){FMTPyreaEE = false;}
      if(XHkAcYBrTN == true){XHkAcYBrTN = false;}
      if(xUJzdKwlZj == true){xUJzdKwlZj = false;}
      if(hhJKPNamjT == true){hhJKPNamjT = false;}
      if(nfenetsswh == true){nfenetsswh = false;}
      if(PugIwkCTln == true){PugIwkCTln = false;}
      if(usBUVoyZjP == true){usBUVoyZjP = false;}
      if(yOIAZQoVTi == true){yOIAZQoVTi = false;}
      if(RDoqUmBAOe == true){RDoqUmBAOe = false;}
      if(KGAwXueKRo == true){KGAwXueKRo = false;}
      if(uSIgjAlgie == true){uSIgjAlgie = false;}
      if(wgzCVrDJAi == true){wgzCVrDJAi = false;}
      if(nxLFEqOMbd == true){nxLFEqOMbd = false;}
      if(ldDdmyuIHT == true){ldDdmyuIHT = false;}
      if(ATQjhdHxZf == true){ATQjhdHxZf = false;}
      if(qUKhByHCbr == true){qUKhByHCbr = false;}
      if(lZEErScUOX == true){lZEErScUOX = false;}
      if(wuCfiTfaXZ == true){wuCfiTfaXZ = false;}
      if(jQmwmQSVco == true){jQmwmQSVco = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESNAWMHBRR
{ 
  void lWyNURYHyd()
  { 
      bool okwmoMRwGd = false;
      bool TsKfbgPKcg = false;
      bool iJVGbSfdlV = false;
      bool wDjunkVAes = false;
      bool HpLUZwJkkR = false;
      bool UCJPFfOoKV = false;
      bool gnJjhQJPrq = false;
      bool KPfiZsxBgf = false;
      bool JurTAtsToH = false;
      bool VfoIMSfamJ = false;
      bool ltrtGFVZoM = false;
      bool hNIdLkuoin = false;
      bool WoZjUeZWWH = false;
      bool MWNWtPCxNu = false;
      bool XTecZIXLxa = false;
      bool WprzlwTIZb = false;
      bool fyDhALzljw = false;
      bool ixbnPDKxKL = false;
      bool HOZujVeOkx = false;
      bool utXkOYQwcO = false;
      string iQNUkkyDEm;
      string iIQVgnKiEi;
      string HGWfkXhwJD;
      string KQXjbQwnCe;
      string jJTjGHtgTU;
      string lbyAobshjN;
      string CBtBcSjgsQ;
      string rVgYzymmZc;
      string dBcoQhRXuz;
      string WOEnchOSHm;
      string XMmCbQuZAp;
      string oGHGiAXEkt;
      string AMlsscQruQ;
      string iTelFQNaMz;
      string mqWEJQGyFb;
      string KJhNmKatJz;
      string ACdjGVaVBR;
      string mxrkGIpgic;
      string WSmTGYlRzt;
      string pTQNzjMmxn;
      if(iQNUkkyDEm == XMmCbQuZAp){okwmoMRwGd = true;}
      else if(XMmCbQuZAp == iQNUkkyDEm){ltrtGFVZoM = true;}
      if(iIQVgnKiEi == oGHGiAXEkt){TsKfbgPKcg = true;}
      else if(oGHGiAXEkt == iIQVgnKiEi){hNIdLkuoin = true;}
      if(HGWfkXhwJD == AMlsscQruQ){iJVGbSfdlV = true;}
      else if(AMlsscQruQ == HGWfkXhwJD){WoZjUeZWWH = true;}
      if(KQXjbQwnCe == iTelFQNaMz){wDjunkVAes = true;}
      else if(iTelFQNaMz == KQXjbQwnCe){MWNWtPCxNu = true;}
      if(jJTjGHtgTU == mqWEJQGyFb){HpLUZwJkkR = true;}
      else if(mqWEJQGyFb == jJTjGHtgTU){XTecZIXLxa = true;}
      if(lbyAobshjN == KJhNmKatJz){UCJPFfOoKV = true;}
      else if(KJhNmKatJz == lbyAobshjN){WprzlwTIZb = true;}
      if(CBtBcSjgsQ == ACdjGVaVBR){gnJjhQJPrq = true;}
      else if(ACdjGVaVBR == CBtBcSjgsQ){fyDhALzljw = true;}
      if(rVgYzymmZc == mxrkGIpgic){KPfiZsxBgf = true;}
      if(dBcoQhRXuz == WSmTGYlRzt){JurTAtsToH = true;}
      if(WOEnchOSHm == pTQNzjMmxn){VfoIMSfamJ = true;}
      while(mxrkGIpgic == rVgYzymmZc){ixbnPDKxKL = true;}
      while(WSmTGYlRzt == WSmTGYlRzt){HOZujVeOkx = true;}
      while(pTQNzjMmxn == pTQNzjMmxn){utXkOYQwcO = true;}
      if(okwmoMRwGd == true){okwmoMRwGd = false;}
      if(TsKfbgPKcg == true){TsKfbgPKcg = false;}
      if(iJVGbSfdlV == true){iJVGbSfdlV = false;}
      if(wDjunkVAes == true){wDjunkVAes = false;}
      if(HpLUZwJkkR == true){HpLUZwJkkR = false;}
      if(UCJPFfOoKV == true){UCJPFfOoKV = false;}
      if(gnJjhQJPrq == true){gnJjhQJPrq = false;}
      if(KPfiZsxBgf == true){KPfiZsxBgf = false;}
      if(JurTAtsToH == true){JurTAtsToH = false;}
      if(VfoIMSfamJ == true){VfoIMSfamJ = false;}
      if(ltrtGFVZoM == true){ltrtGFVZoM = false;}
      if(hNIdLkuoin == true){hNIdLkuoin = false;}
      if(WoZjUeZWWH == true){WoZjUeZWWH = false;}
      if(MWNWtPCxNu == true){MWNWtPCxNu = false;}
      if(XTecZIXLxa == true){XTecZIXLxa = false;}
      if(WprzlwTIZb == true){WprzlwTIZb = false;}
      if(fyDhALzljw == true){fyDhALzljw = false;}
      if(ixbnPDKxKL == true){ixbnPDKxKL = false;}
      if(HOZujVeOkx == true){HOZujVeOkx = false;}
      if(utXkOYQwcO == true){utXkOYQwcO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LQYVLFQLVN
{ 
  void wtTOCnyxcO()
  { 
      bool NTAfffLiin = false;
      bool mOGHEAUTXn = false;
      bool fjFHAhDHIT = false;
      bool nXWSuhYOxg = false;
      bool gPOiAEZLNc = false;
      bool oIxbhdOrfy = false;
      bool cDZPzOqnLV = false;
      bool bGWqHPUVHu = false;
      bool IqsfdfZujR = false;
      bool TfiyDcpzik = false;
      bool MkArAikGTS = false;
      bool IrkjolJtkT = false;
      bool owEtCwWXme = false;
      bool ZVmWhWqBet = false;
      bool tTbRIatzJR = false;
      bool TuNPwQgFpE = false;
      bool MNSnsmFOBS = false;
      bool tHPqYUTmla = false;
      bool BXOVKdIXaR = false;
      bool okLahgAmYV = false;
      string CHhJhbaICX;
      string OkVmzVFVCm;
      string bYmHrkLQeR;
      string gZceUHYblw;
      string QNtJjocdMB;
      string WtcVXcUZRx;
      string QJcjqnHqRq;
      string wdjFWOdcWC;
      string HgEdulxGGr;
      string myJofHkJSu;
      string hlMUEsKWzJ;
      string zrDOojFzoF;
      string qAjYExTtZO;
      string cTKaUVTiYC;
      string aZGwsuuuzw;
      string CkUMEgCmQG;
      string YQxkfegbtT;
      string PVZldQtmfJ;
      string CYudMrzxWm;
      string TgSScKcVPN;
      if(CHhJhbaICX == hlMUEsKWzJ){NTAfffLiin = true;}
      else if(hlMUEsKWzJ == CHhJhbaICX){MkArAikGTS = true;}
      if(OkVmzVFVCm == zrDOojFzoF){mOGHEAUTXn = true;}
      else if(zrDOojFzoF == OkVmzVFVCm){IrkjolJtkT = true;}
      if(bYmHrkLQeR == qAjYExTtZO){fjFHAhDHIT = true;}
      else if(qAjYExTtZO == bYmHrkLQeR){owEtCwWXme = true;}
      if(gZceUHYblw == cTKaUVTiYC){nXWSuhYOxg = true;}
      else if(cTKaUVTiYC == gZceUHYblw){ZVmWhWqBet = true;}
      if(QNtJjocdMB == aZGwsuuuzw){gPOiAEZLNc = true;}
      else if(aZGwsuuuzw == QNtJjocdMB){tTbRIatzJR = true;}
      if(WtcVXcUZRx == CkUMEgCmQG){oIxbhdOrfy = true;}
      else if(CkUMEgCmQG == WtcVXcUZRx){TuNPwQgFpE = true;}
      if(QJcjqnHqRq == YQxkfegbtT){cDZPzOqnLV = true;}
      else if(YQxkfegbtT == QJcjqnHqRq){MNSnsmFOBS = true;}
      if(wdjFWOdcWC == PVZldQtmfJ){bGWqHPUVHu = true;}
      if(HgEdulxGGr == CYudMrzxWm){IqsfdfZujR = true;}
      if(myJofHkJSu == TgSScKcVPN){TfiyDcpzik = true;}
      while(PVZldQtmfJ == wdjFWOdcWC){tHPqYUTmla = true;}
      while(CYudMrzxWm == CYudMrzxWm){BXOVKdIXaR = true;}
      while(TgSScKcVPN == TgSScKcVPN){okLahgAmYV = true;}
      if(NTAfffLiin == true){NTAfffLiin = false;}
      if(mOGHEAUTXn == true){mOGHEAUTXn = false;}
      if(fjFHAhDHIT == true){fjFHAhDHIT = false;}
      if(nXWSuhYOxg == true){nXWSuhYOxg = false;}
      if(gPOiAEZLNc == true){gPOiAEZLNc = false;}
      if(oIxbhdOrfy == true){oIxbhdOrfy = false;}
      if(cDZPzOqnLV == true){cDZPzOqnLV = false;}
      if(bGWqHPUVHu == true){bGWqHPUVHu = false;}
      if(IqsfdfZujR == true){IqsfdfZujR = false;}
      if(TfiyDcpzik == true){TfiyDcpzik = false;}
      if(MkArAikGTS == true){MkArAikGTS = false;}
      if(IrkjolJtkT == true){IrkjolJtkT = false;}
      if(owEtCwWXme == true){owEtCwWXme = false;}
      if(ZVmWhWqBet == true){ZVmWhWqBet = false;}
      if(tTbRIatzJR == true){tTbRIatzJR = false;}
      if(TuNPwQgFpE == true){TuNPwQgFpE = false;}
      if(MNSnsmFOBS == true){MNSnsmFOBS = false;}
      if(tHPqYUTmla == true){tHPqYUTmla = false;}
      if(BXOVKdIXaR == true){BXOVKdIXaR = false;}
      if(okLahgAmYV == true){okLahgAmYV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SKMOBRYSSJ
{ 
  void qIMmXJPNWx()
  { 
      bool npDTGfQttS = false;
      bool pbBFCSOwXo = false;
      bool CKYsJdpOAk = false;
      bool YdXfCbpjtf = false;
      bool tHuOVpxIsC = false;
      bool RSYMpcQJKc = false;
      bool oBsJtLEVCa = false;
      bool ceCruuPJXS = false;
      bool fhVyTGFKoZ = false;
      bool KfZRprNlUJ = false;
      bool lbGRYlPgRu = false;
      bool NHlqwHfupm = false;
      bool GsgcQxFjBD = false;
      bool hcoNgEaDZg = false;
      bool pXrtLDshUh = false;
      bool LSugCrucBb = false;
      bool gffOMjRXJr = false;
      bool fcVJxiAlQN = false;
      bool DWPSqPhHKn = false;
      bool JyCxAKrdgb = false;
      string UQswgxnPLu;
      string IRgZCnfTwr;
      string TKiCGpSnnJ;
      string RKrQgbhifU;
      string xdWFGBsrCo;
      string MDMbbKhqoq;
      string ezaBdyYQsZ;
      string FwmbuomcwF;
      string wZlzxOxPnV;
      string tqsooyDUaH;
      string bczbiPPjgl;
      string WEtjtENaDP;
      string BJbXfODxlw;
      string lSCndSaJQh;
      string yMhCypwJtk;
      string jbQLGRBauU;
      string MRykAEBGFa;
      string dEKVQnbZZp;
      string RsDBMKBpgL;
      string RzNwUfOxCs;
      if(UQswgxnPLu == bczbiPPjgl){npDTGfQttS = true;}
      else if(bczbiPPjgl == UQswgxnPLu){lbGRYlPgRu = true;}
      if(IRgZCnfTwr == WEtjtENaDP){pbBFCSOwXo = true;}
      else if(WEtjtENaDP == IRgZCnfTwr){NHlqwHfupm = true;}
      if(TKiCGpSnnJ == BJbXfODxlw){CKYsJdpOAk = true;}
      else if(BJbXfODxlw == TKiCGpSnnJ){GsgcQxFjBD = true;}
      if(RKrQgbhifU == lSCndSaJQh){YdXfCbpjtf = true;}
      else if(lSCndSaJQh == RKrQgbhifU){hcoNgEaDZg = true;}
      if(xdWFGBsrCo == yMhCypwJtk){tHuOVpxIsC = true;}
      else if(yMhCypwJtk == xdWFGBsrCo){pXrtLDshUh = true;}
      if(MDMbbKhqoq == jbQLGRBauU){RSYMpcQJKc = true;}
      else if(jbQLGRBauU == MDMbbKhqoq){LSugCrucBb = true;}
      if(ezaBdyYQsZ == MRykAEBGFa){oBsJtLEVCa = true;}
      else if(MRykAEBGFa == ezaBdyYQsZ){gffOMjRXJr = true;}
      if(FwmbuomcwF == dEKVQnbZZp){ceCruuPJXS = true;}
      if(wZlzxOxPnV == RsDBMKBpgL){fhVyTGFKoZ = true;}
      if(tqsooyDUaH == RzNwUfOxCs){KfZRprNlUJ = true;}
      while(dEKVQnbZZp == FwmbuomcwF){fcVJxiAlQN = true;}
      while(RsDBMKBpgL == RsDBMKBpgL){DWPSqPhHKn = true;}
      while(RzNwUfOxCs == RzNwUfOxCs){JyCxAKrdgb = true;}
      if(npDTGfQttS == true){npDTGfQttS = false;}
      if(pbBFCSOwXo == true){pbBFCSOwXo = false;}
      if(CKYsJdpOAk == true){CKYsJdpOAk = false;}
      if(YdXfCbpjtf == true){YdXfCbpjtf = false;}
      if(tHuOVpxIsC == true){tHuOVpxIsC = false;}
      if(RSYMpcQJKc == true){RSYMpcQJKc = false;}
      if(oBsJtLEVCa == true){oBsJtLEVCa = false;}
      if(ceCruuPJXS == true){ceCruuPJXS = false;}
      if(fhVyTGFKoZ == true){fhVyTGFKoZ = false;}
      if(KfZRprNlUJ == true){KfZRprNlUJ = false;}
      if(lbGRYlPgRu == true){lbGRYlPgRu = false;}
      if(NHlqwHfupm == true){NHlqwHfupm = false;}
      if(GsgcQxFjBD == true){GsgcQxFjBD = false;}
      if(hcoNgEaDZg == true){hcoNgEaDZg = false;}
      if(pXrtLDshUh == true){pXrtLDshUh = false;}
      if(LSugCrucBb == true){LSugCrucBb = false;}
      if(gffOMjRXJr == true){gffOMjRXJr = false;}
      if(fcVJxiAlQN == true){fcVJxiAlQN = false;}
      if(DWPSqPhHKn == true){DWPSqPhHKn = false;}
      if(JyCxAKrdgb == true){JyCxAKrdgb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GCBZMLOFEB
{ 
  void EWLtBwPzPu()
  { 
      bool rwkStZoGjg = false;
      bool XVVcVWsYjs = false;
      bool EpZOfKDAHF = false;
      bool HaTTKksWlc = false;
      bool awQOpnESTS = false;
      bool AyhNjBWWlj = false;
      bool VnzeYwCCSj = false;
      bool cVlGRHZKXr = false;
      bool FkgnEJsGiI = false;
      bool OWjCHlxkps = false;
      bool kBziodLbub = false;
      bool aLytdjGKaO = false;
      bool DuSKVGljzf = false;
      bool JnUeGDlyzZ = false;
      bool xRKGgDXpXW = false;
      bool fmKaooinMi = false;
      bool rbbPRlpTmZ = false;
      bool xIKARlkLcS = false;
      bool huLbAVdtoQ = false;
      bool UxlPgVount = false;
      string DIHkfZhXfX;
      string ygnGgytyiB;
      string zflAfptLtB;
      string puOeliDcuA;
      string WqarXiwFRy;
      string MiAsLWWGFp;
      string eVdehDSJUy;
      string uQChdHFtcw;
      string sotunHuUSO;
      string MwXFVBNwJU;
      string PmjSCufRPD;
      string RbdJwpbhqa;
      string HypFlzsxMc;
      string tIjIfGEbrr;
      string bcEPxjROIf;
      string ZeFiMRwdfD;
      string ChFmIIqVcp;
      string kzpyyesaIC;
      string geogDPDAwO;
      string JZuopsWRGo;
      if(DIHkfZhXfX == PmjSCufRPD){rwkStZoGjg = true;}
      else if(PmjSCufRPD == DIHkfZhXfX){kBziodLbub = true;}
      if(ygnGgytyiB == RbdJwpbhqa){XVVcVWsYjs = true;}
      else if(RbdJwpbhqa == ygnGgytyiB){aLytdjGKaO = true;}
      if(zflAfptLtB == HypFlzsxMc){EpZOfKDAHF = true;}
      else if(HypFlzsxMc == zflAfptLtB){DuSKVGljzf = true;}
      if(puOeliDcuA == tIjIfGEbrr){HaTTKksWlc = true;}
      else if(tIjIfGEbrr == puOeliDcuA){JnUeGDlyzZ = true;}
      if(WqarXiwFRy == bcEPxjROIf){awQOpnESTS = true;}
      else if(bcEPxjROIf == WqarXiwFRy){xRKGgDXpXW = true;}
      if(MiAsLWWGFp == ZeFiMRwdfD){AyhNjBWWlj = true;}
      else if(ZeFiMRwdfD == MiAsLWWGFp){fmKaooinMi = true;}
      if(eVdehDSJUy == ChFmIIqVcp){VnzeYwCCSj = true;}
      else if(ChFmIIqVcp == eVdehDSJUy){rbbPRlpTmZ = true;}
      if(uQChdHFtcw == kzpyyesaIC){cVlGRHZKXr = true;}
      if(sotunHuUSO == geogDPDAwO){FkgnEJsGiI = true;}
      if(MwXFVBNwJU == JZuopsWRGo){OWjCHlxkps = true;}
      while(kzpyyesaIC == uQChdHFtcw){xIKARlkLcS = true;}
      while(geogDPDAwO == geogDPDAwO){huLbAVdtoQ = true;}
      while(JZuopsWRGo == JZuopsWRGo){UxlPgVount = true;}
      if(rwkStZoGjg == true){rwkStZoGjg = false;}
      if(XVVcVWsYjs == true){XVVcVWsYjs = false;}
      if(EpZOfKDAHF == true){EpZOfKDAHF = false;}
      if(HaTTKksWlc == true){HaTTKksWlc = false;}
      if(awQOpnESTS == true){awQOpnESTS = false;}
      if(AyhNjBWWlj == true){AyhNjBWWlj = false;}
      if(VnzeYwCCSj == true){VnzeYwCCSj = false;}
      if(cVlGRHZKXr == true){cVlGRHZKXr = false;}
      if(FkgnEJsGiI == true){FkgnEJsGiI = false;}
      if(OWjCHlxkps == true){OWjCHlxkps = false;}
      if(kBziodLbub == true){kBziodLbub = false;}
      if(aLytdjGKaO == true){aLytdjGKaO = false;}
      if(DuSKVGljzf == true){DuSKVGljzf = false;}
      if(JnUeGDlyzZ == true){JnUeGDlyzZ = false;}
      if(xRKGgDXpXW == true){xRKGgDXpXW = false;}
      if(fmKaooinMi == true){fmKaooinMi = false;}
      if(rbbPRlpTmZ == true){rbbPRlpTmZ = false;}
      if(xIKARlkLcS == true){xIKARlkLcS = false;}
      if(huLbAVdtoQ == true){huLbAVdtoQ = false;}
      if(UxlPgVount == true){UxlPgVount = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QDDVKYMDFO
{ 
  void lwepbjNICL()
  { 
      bool xulRSWnybQ = false;
      bool ZEqKEPNeYA = false;
      bool yRaPXmUCNP = false;
      bool ngPIiFxGGV = false;
      bool bPKQPGETtX = false;
      bool rDOfQeUWsf = false;
      bool ClkLcrnhaz = false;
      bool RGXDYhGJzQ = false;
      bool hAIpXkRjqE = false;
      bool jaNaSoeynX = false;
      bool RVstGkeLHh = false;
      bool XLXcxCcunq = false;
      bool ZEqWOqsxji = false;
      bool DHUayLHNil = false;
      bool FGcIfYCkcQ = false;
      bool MjKwxNeVfP = false;
      bool rhbYePqwdk = false;
      bool uPLCkTbhpo = false;
      bool nITSWSxXdk = false;
      bool gkhTsXdEdP = false;
      string aBlITTLmDE;
      string CFFtsRxboW;
      string VtTpFOzrQA;
      string nYkrmVdlDQ;
      string LTpaYtHXwz;
      string ljFtYfguCE;
      string USWCQcUMHW;
      string nKYXKCDsRL;
      string HawQODTqTG;
      string ohiywswnJw;
      string ZtQZLaLgiW;
      string cndqxsWGnM;
      string IdsBhFbZbQ;
      string GOiUlMKWEm;
      string qmHwcBEqBC;
      string WpAxmuBOqG;
      string zlESQNEIFj;
      string izBBUVVwXf;
      string BjYZsPOlhp;
      string LueymFhnfP;
      if(aBlITTLmDE == ZtQZLaLgiW){xulRSWnybQ = true;}
      else if(ZtQZLaLgiW == aBlITTLmDE){RVstGkeLHh = true;}
      if(CFFtsRxboW == cndqxsWGnM){ZEqKEPNeYA = true;}
      else if(cndqxsWGnM == CFFtsRxboW){XLXcxCcunq = true;}
      if(VtTpFOzrQA == IdsBhFbZbQ){yRaPXmUCNP = true;}
      else if(IdsBhFbZbQ == VtTpFOzrQA){ZEqWOqsxji = true;}
      if(nYkrmVdlDQ == GOiUlMKWEm){ngPIiFxGGV = true;}
      else if(GOiUlMKWEm == nYkrmVdlDQ){DHUayLHNil = true;}
      if(LTpaYtHXwz == qmHwcBEqBC){bPKQPGETtX = true;}
      else if(qmHwcBEqBC == LTpaYtHXwz){FGcIfYCkcQ = true;}
      if(ljFtYfguCE == WpAxmuBOqG){rDOfQeUWsf = true;}
      else if(WpAxmuBOqG == ljFtYfguCE){MjKwxNeVfP = true;}
      if(USWCQcUMHW == zlESQNEIFj){ClkLcrnhaz = true;}
      else if(zlESQNEIFj == USWCQcUMHW){rhbYePqwdk = true;}
      if(nKYXKCDsRL == izBBUVVwXf){RGXDYhGJzQ = true;}
      if(HawQODTqTG == BjYZsPOlhp){hAIpXkRjqE = true;}
      if(ohiywswnJw == LueymFhnfP){jaNaSoeynX = true;}
      while(izBBUVVwXf == nKYXKCDsRL){uPLCkTbhpo = true;}
      while(BjYZsPOlhp == BjYZsPOlhp){nITSWSxXdk = true;}
      while(LueymFhnfP == LueymFhnfP){gkhTsXdEdP = true;}
      if(xulRSWnybQ == true){xulRSWnybQ = false;}
      if(ZEqKEPNeYA == true){ZEqKEPNeYA = false;}
      if(yRaPXmUCNP == true){yRaPXmUCNP = false;}
      if(ngPIiFxGGV == true){ngPIiFxGGV = false;}
      if(bPKQPGETtX == true){bPKQPGETtX = false;}
      if(rDOfQeUWsf == true){rDOfQeUWsf = false;}
      if(ClkLcrnhaz == true){ClkLcrnhaz = false;}
      if(RGXDYhGJzQ == true){RGXDYhGJzQ = false;}
      if(hAIpXkRjqE == true){hAIpXkRjqE = false;}
      if(jaNaSoeynX == true){jaNaSoeynX = false;}
      if(RVstGkeLHh == true){RVstGkeLHh = false;}
      if(XLXcxCcunq == true){XLXcxCcunq = false;}
      if(ZEqWOqsxji == true){ZEqWOqsxji = false;}
      if(DHUayLHNil == true){DHUayLHNil = false;}
      if(FGcIfYCkcQ == true){FGcIfYCkcQ = false;}
      if(MjKwxNeVfP == true){MjKwxNeVfP = false;}
      if(rhbYePqwdk == true){rhbYePqwdk = false;}
      if(uPLCkTbhpo == true){uPLCkTbhpo = false;}
      if(nITSWSxXdk == true){nITSWSxXdk = false;}
      if(gkhTsXdEdP == true){gkhTsXdEdP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZKVMQNEZJV
{ 
  void qUBgydjzjT()
  { 
      bool kBFAHCPzck = false;
      bool zoIeVyLEso = false;
      bool zJPVIypxFu = false;
      bool poamxRGDVg = false;
      bool hPqzCSJrZU = false;
      bool XNoGTblirI = false;
      bool LStgtKNUgE = false;
      bool qIhMGjRPTo = false;
      bool oxXjXczUTV = false;
      bool eXLNUPVKFq = false;
      bool FnLUdPfbzj = false;
      bool JVPCTNuJJR = false;
      bool LrBLYTxUrq = false;
      bool OHKbjAlCGH = false;
      bool xWViMJIIsH = false;
      bool TLAmfNmAwJ = false;
      bool SLjHVBLmST = false;
      bool asCBUnVRyO = false;
      bool LnajXCGWuV = false;
      bool MlFwoklNNK = false;
      string wumxCLmfbL;
      string nGskQsZqll;
      string AaXbPhWjHu;
      string tuhMHtqIUL;
      string TIJGugxijM;
      string RIKsjUXKgT;
      string nCXgRsYgcV;
      string BQWZRqQQfi;
      string jnAudljnbm;
      string WfbBXRkbnC;
      string IQFNKAkjbs;
      string DGdyjzBcDf;
      string IjFpzUoVCz;
      string GocdZThmjd;
      string AALhiPBcQY;
      string QHYIsXLPOo;
      string KPhcmOdAXQ;
      string QOrYfIXWHi;
      string TLEdiyPTjB;
      string HSXuTjRiuT;
      if(wumxCLmfbL == IQFNKAkjbs){kBFAHCPzck = true;}
      else if(IQFNKAkjbs == wumxCLmfbL){FnLUdPfbzj = true;}
      if(nGskQsZqll == DGdyjzBcDf){zoIeVyLEso = true;}
      else if(DGdyjzBcDf == nGskQsZqll){JVPCTNuJJR = true;}
      if(AaXbPhWjHu == IjFpzUoVCz){zJPVIypxFu = true;}
      else if(IjFpzUoVCz == AaXbPhWjHu){LrBLYTxUrq = true;}
      if(tuhMHtqIUL == GocdZThmjd){poamxRGDVg = true;}
      else if(GocdZThmjd == tuhMHtqIUL){OHKbjAlCGH = true;}
      if(TIJGugxijM == AALhiPBcQY){hPqzCSJrZU = true;}
      else if(AALhiPBcQY == TIJGugxijM){xWViMJIIsH = true;}
      if(RIKsjUXKgT == QHYIsXLPOo){XNoGTblirI = true;}
      else if(QHYIsXLPOo == RIKsjUXKgT){TLAmfNmAwJ = true;}
      if(nCXgRsYgcV == KPhcmOdAXQ){LStgtKNUgE = true;}
      else if(KPhcmOdAXQ == nCXgRsYgcV){SLjHVBLmST = true;}
      if(BQWZRqQQfi == QOrYfIXWHi){qIhMGjRPTo = true;}
      if(jnAudljnbm == TLEdiyPTjB){oxXjXczUTV = true;}
      if(WfbBXRkbnC == HSXuTjRiuT){eXLNUPVKFq = true;}
      while(QOrYfIXWHi == BQWZRqQQfi){asCBUnVRyO = true;}
      while(TLEdiyPTjB == TLEdiyPTjB){LnajXCGWuV = true;}
      while(HSXuTjRiuT == HSXuTjRiuT){MlFwoklNNK = true;}
      if(kBFAHCPzck == true){kBFAHCPzck = false;}
      if(zoIeVyLEso == true){zoIeVyLEso = false;}
      if(zJPVIypxFu == true){zJPVIypxFu = false;}
      if(poamxRGDVg == true){poamxRGDVg = false;}
      if(hPqzCSJrZU == true){hPqzCSJrZU = false;}
      if(XNoGTblirI == true){XNoGTblirI = false;}
      if(LStgtKNUgE == true){LStgtKNUgE = false;}
      if(qIhMGjRPTo == true){qIhMGjRPTo = false;}
      if(oxXjXczUTV == true){oxXjXczUTV = false;}
      if(eXLNUPVKFq == true){eXLNUPVKFq = false;}
      if(FnLUdPfbzj == true){FnLUdPfbzj = false;}
      if(JVPCTNuJJR == true){JVPCTNuJJR = false;}
      if(LrBLYTxUrq == true){LrBLYTxUrq = false;}
      if(OHKbjAlCGH == true){OHKbjAlCGH = false;}
      if(xWViMJIIsH == true){xWViMJIIsH = false;}
      if(TLAmfNmAwJ == true){TLAmfNmAwJ = false;}
      if(SLjHVBLmST == true){SLjHVBLmST = false;}
      if(asCBUnVRyO == true){asCBUnVRyO = false;}
      if(LnajXCGWuV == true){LnajXCGWuV = false;}
      if(MlFwoklNNK == true){MlFwoklNNK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WFSEDITXRG
{ 
  void nexfoNWCij()
  { 
      bool wJoASsoJEm = false;
      bool QgKNbWAFDZ = false;
      bool WRPNrmJlgr = false;
      bool VeiltSxAXn = false;
      bool jiWZIRbttV = false;
      bool RJxTtdtbHf = false;
      bool iDcMQkxXTJ = false;
      bool YzgOomuoFa = false;
      bool KPrLaLgPrP = false;
      bool XVrrFgGKJW = false;
      bool TEZjwRcieG = false;
      bool iFWgUTLRkE = false;
      bool EheEkDHoJI = false;
      bool fkfhGGoHOI = false;
      bool iyjkfSzKWk = false;
      bool VoYESlYVys = false;
      bool KnZVayYnaO = false;
      bool dDCcUFxtXS = false;
      bool EwRXmqMaPU = false;
      bool gTIVyuXNKh = false;
      string ssjfAdTJIp;
      string LNaSDleYxE;
      string OJXOkIEpeC;
      string xYdoJwVeks;
      string TKSlHzRGrj;
      string ZhhNZjVUtq;
      string ZcdFsmikIH;
      string PAmDjDpkGl;
      string pyyucOpQOZ;
      string aAksTpgMsU;
      string PgxkTZuedV;
      string skNIBaeicd;
      string wSVifPPsis;
      string WcqkVJBMaD;
      string TKlrfplbrr;
      string LxjPYxKNEE;
      string KBukzPsclq;
      string ZRIZKkfcCp;
      string cmBphZsbMY;
      string zmIVrRPBsQ;
      if(ssjfAdTJIp == PgxkTZuedV){wJoASsoJEm = true;}
      else if(PgxkTZuedV == ssjfAdTJIp){TEZjwRcieG = true;}
      if(LNaSDleYxE == skNIBaeicd){QgKNbWAFDZ = true;}
      else if(skNIBaeicd == LNaSDleYxE){iFWgUTLRkE = true;}
      if(OJXOkIEpeC == wSVifPPsis){WRPNrmJlgr = true;}
      else if(wSVifPPsis == OJXOkIEpeC){EheEkDHoJI = true;}
      if(xYdoJwVeks == WcqkVJBMaD){VeiltSxAXn = true;}
      else if(WcqkVJBMaD == xYdoJwVeks){fkfhGGoHOI = true;}
      if(TKSlHzRGrj == TKlrfplbrr){jiWZIRbttV = true;}
      else if(TKlrfplbrr == TKSlHzRGrj){iyjkfSzKWk = true;}
      if(ZhhNZjVUtq == LxjPYxKNEE){RJxTtdtbHf = true;}
      else if(LxjPYxKNEE == ZhhNZjVUtq){VoYESlYVys = true;}
      if(ZcdFsmikIH == KBukzPsclq){iDcMQkxXTJ = true;}
      else if(KBukzPsclq == ZcdFsmikIH){KnZVayYnaO = true;}
      if(PAmDjDpkGl == ZRIZKkfcCp){YzgOomuoFa = true;}
      if(pyyucOpQOZ == cmBphZsbMY){KPrLaLgPrP = true;}
      if(aAksTpgMsU == zmIVrRPBsQ){XVrrFgGKJW = true;}
      while(ZRIZKkfcCp == PAmDjDpkGl){dDCcUFxtXS = true;}
      while(cmBphZsbMY == cmBphZsbMY){EwRXmqMaPU = true;}
      while(zmIVrRPBsQ == zmIVrRPBsQ){gTIVyuXNKh = true;}
      if(wJoASsoJEm == true){wJoASsoJEm = false;}
      if(QgKNbWAFDZ == true){QgKNbWAFDZ = false;}
      if(WRPNrmJlgr == true){WRPNrmJlgr = false;}
      if(VeiltSxAXn == true){VeiltSxAXn = false;}
      if(jiWZIRbttV == true){jiWZIRbttV = false;}
      if(RJxTtdtbHf == true){RJxTtdtbHf = false;}
      if(iDcMQkxXTJ == true){iDcMQkxXTJ = false;}
      if(YzgOomuoFa == true){YzgOomuoFa = false;}
      if(KPrLaLgPrP == true){KPrLaLgPrP = false;}
      if(XVrrFgGKJW == true){XVrrFgGKJW = false;}
      if(TEZjwRcieG == true){TEZjwRcieG = false;}
      if(iFWgUTLRkE == true){iFWgUTLRkE = false;}
      if(EheEkDHoJI == true){EheEkDHoJI = false;}
      if(fkfhGGoHOI == true){fkfhGGoHOI = false;}
      if(iyjkfSzKWk == true){iyjkfSzKWk = false;}
      if(VoYESlYVys == true){VoYESlYVys = false;}
      if(KnZVayYnaO == true){KnZVayYnaO = false;}
      if(dDCcUFxtXS == true){dDCcUFxtXS = false;}
      if(EwRXmqMaPU == true){EwRXmqMaPU = false;}
      if(gTIVyuXNKh == true){gTIVyuXNKh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WFPRXOZFMU
{ 
  void xhwtgDfbUu()
  { 
      bool WSpiNDoFwU = false;
      bool raBpKemXIT = false;
      bool DLDwXrzHbF = false;
      bool nfmjJSUOVi = false;
      bool mlyRgpfntK = false;
      bool oqGReLPtKU = false;
      bool DgdpgMnQfr = false;
      bool JYBZgQNkOh = false;
      bool MKNQQxZUFy = false;
      bool CaEAeFIHkU = false;
      bool BOICBQofkO = false;
      bool xeecHsTMYj = false;
      bool lTLgohTBua = false;
      bool HFztfxCKPA = false;
      bool HsipBXwasl = false;
      bool kwiBhhDbMS = false;
      bool wnkJGqekwJ = false;
      bool qIwXbsjUeR = false;
      bool lrHIoLWyLy = false;
      bool taywETHYiK = false;
      string salKYWBCSG;
      string hwwYEfARxM;
      string XxwaXsaksa;
      string lMTgklXhML;
      string eaMwSTUGAA;
      string gNOwXudLmf;
      string wQIqUVbOmR;
      string HSEkhxjAIE;
      string XUjstXyXIo;
      string HMtgONRUbw;
      string qFShrNJcOa;
      string LdCiHbfOxx;
      string XEGxKuXXVT;
      string ePXLMRBCBf;
      string OUJhdcJLYm;
      string gCWdXmzUXw;
      string plGtwuFpVp;
      string ZdNRhCtXTg;
      string lLyilbrtmZ;
      string RgeFocOOki;
      if(salKYWBCSG == qFShrNJcOa){WSpiNDoFwU = true;}
      else if(qFShrNJcOa == salKYWBCSG){BOICBQofkO = true;}
      if(hwwYEfARxM == LdCiHbfOxx){raBpKemXIT = true;}
      else if(LdCiHbfOxx == hwwYEfARxM){xeecHsTMYj = true;}
      if(XxwaXsaksa == XEGxKuXXVT){DLDwXrzHbF = true;}
      else if(XEGxKuXXVT == XxwaXsaksa){lTLgohTBua = true;}
      if(lMTgklXhML == ePXLMRBCBf){nfmjJSUOVi = true;}
      else if(ePXLMRBCBf == lMTgklXhML){HFztfxCKPA = true;}
      if(eaMwSTUGAA == OUJhdcJLYm){mlyRgpfntK = true;}
      else if(OUJhdcJLYm == eaMwSTUGAA){HsipBXwasl = true;}
      if(gNOwXudLmf == gCWdXmzUXw){oqGReLPtKU = true;}
      else if(gCWdXmzUXw == gNOwXudLmf){kwiBhhDbMS = true;}
      if(wQIqUVbOmR == plGtwuFpVp){DgdpgMnQfr = true;}
      else if(plGtwuFpVp == wQIqUVbOmR){wnkJGqekwJ = true;}
      if(HSEkhxjAIE == ZdNRhCtXTg){JYBZgQNkOh = true;}
      if(XUjstXyXIo == lLyilbrtmZ){MKNQQxZUFy = true;}
      if(HMtgONRUbw == RgeFocOOki){CaEAeFIHkU = true;}
      while(ZdNRhCtXTg == HSEkhxjAIE){qIwXbsjUeR = true;}
      while(lLyilbrtmZ == lLyilbrtmZ){lrHIoLWyLy = true;}
      while(RgeFocOOki == RgeFocOOki){taywETHYiK = true;}
      if(WSpiNDoFwU == true){WSpiNDoFwU = false;}
      if(raBpKemXIT == true){raBpKemXIT = false;}
      if(DLDwXrzHbF == true){DLDwXrzHbF = false;}
      if(nfmjJSUOVi == true){nfmjJSUOVi = false;}
      if(mlyRgpfntK == true){mlyRgpfntK = false;}
      if(oqGReLPtKU == true){oqGReLPtKU = false;}
      if(DgdpgMnQfr == true){DgdpgMnQfr = false;}
      if(JYBZgQNkOh == true){JYBZgQNkOh = false;}
      if(MKNQQxZUFy == true){MKNQQxZUFy = false;}
      if(CaEAeFIHkU == true){CaEAeFIHkU = false;}
      if(BOICBQofkO == true){BOICBQofkO = false;}
      if(xeecHsTMYj == true){xeecHsTMYj = false;}
      if(lTLgohTBua == true){lTLgohTBua = false;}
      if(HFztfxCKPA == true){HFztfxCKPA = false;}
      if(HsipBXwasl == true){HsipBXwasl = false;}
      if(kwiBhhDbMS == true){kwiBhhDbMS = false;}
      if(wnkJGqekwJ == true){wnkJGqekwJ = false;}
      if(qIwXbsjUeR == true){qIwXbsjUeR = false;}
      if(lrHIoLWyLy == true){lrHIoLWyLy = false;}
      if(taywETHYiK == true){taywETHYiK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WTVYPJHEJY
{ 
  void ApkdioDZco()
  { 
      bool bLEjXRWrLK = false;
      bool JsHFwlBQLF = false;
      bool gNfudRSotr = false;
      bool ZmAThzydGu = false;
      bool aMbykmiZHg = false;
      bool DDminOeJFF = false;
      bool ygxSjWsnXw = false;
      bool nXKQeTkhJq = false;
      bool ishNnWzQeT = false;
      bool ToXAwtPION = false;
      bool suBKrfrWET = false;
      bool cxzOVEzjdM = false;
      bool WcIDbzzJTk = false;
      bool EcTwxnrWUI = false;
      bool dcMLqWoIdq = false;
      bool uedBqQmxis = false;
      bool fiCSOzcDRh = false;
      bool MbPVitPwME = false;
      bool JqecpZyRFf = false;
      bool BtmacuZswq = false;
      string ffGWxdECYV;
      string xBAJDEfSHt;
      string poMYqnsLRF;
      string HRQJArlHhQ;
      string EGxourHGNl;
      string KLwqAqThfJ;
      string kskSOejqIK;
      string RXjpoiqWdy;
      string gmyfuwUZJJ;
      string YEaYeLVeaP;
      string HQxCTlaFCQ;
      string zwDgbytFXS;
      string JKgzlMwKKc;
      string NMuOqQouLI;
      string UPXrJbBtwg;
      string QPGIFwiyPH;
      string oPuYDmAooL;
      string JzsOxtlopJ;
      string LCOdMxFmIt;
      string gqfETETzoV;
      if(ffGWxdECYV == HQxCTlaFCQ){bLEjXRWrLK = true;}
      else if(HQxCTlaFCQ == ffGWxdECYV){suBKrfrWET = true;}
      if(xBAJDEfSHt == zwDgbytFXS){JsHFwlBQLF = true;}
      else if(zwDgbytFXS == xBAJDEfSHt){cxzOVEzjdM = true;}
      if(poMYqnsLRF == JKgzlMwKKc){gNfudRSotr = true;}
      else if(JKgzlMwKKc == poMYqnsLRF){WcIDbzzJTk = true;}
      if(HRQJArlHhQ == NMuOqQouLI){ZmAThzydGu = true;}
      else if(NMuOqQouLI == HRQJArlHhQ){EcTwxnrWUI = true;}
      if(EGxourHGNl == UPXrJbBtwg){aMbykmiZHg = true;}
      else if(UPXrJbBtwg == EGxourHGNl){dcMLqWoIdq = true;}
      if(KLwqAqThfJ == QPGIFwiyPH){DDminOeJFF = true;}
      else if(QPGIFwiyPH == KLwqAqThfJ){uedBqQmxis = true;}
      if(kskSOejqIK == oPuYDmAooL){ygxSjWsnXw = true;}
      else if(oPuYDmAooL == kskSOejqIK){fiCSOzcDRh = true;}
      if(RXjpoiqWdy == JzsOxtlopJ){nXKQeTkhJq = true;}
      if(gmyfuwUZJJ == LCOdMxFmIt){ishNnWzQeT = true;}
      if(YEaYeLVeaP == gqfETETzoV){ToXAwtPION = true;}
      while(JzsOxtlopJ == RXjpoiqWdy){MbPVitPwME = true;}
      while(LCOdMxFmIt == LCOdMxFmIt){JqecpZyRFf = true;}
      while(gqfETETzoV == gqfETETzoV){BtmacuZswq = true;}
      if(bLEjXRWrLK == true){bLEjXRWrLK = false;}
      if(JsHFwlBQLF == true){JsHFwlBQLF = false;}
      if(gNfudRSotr == true){gNfudRSotr = false;}
      if(ZmAThzydGu == true){ZmAThzydGu = false;}
      if(aMbykmiZHg == true){aMbykmiZHg = false;}
      if(DDminOeJFF == true){DDminOeJFF = false;}
      if(ygxSjWsnXw == true){ygxSjWsnXw = false;}
      if(nXKQeTkhJq == true){nXKQeTkhJq = false;}
      if(ishNnWzQeT == true){ishNnWzQeT = false;}
      if(ToXAwtPION == true){ToXAwtPION = false;}
      if(suBKrfrWET == true){suBKrfrWET = false;}
      if(cxzOVEzjdM == true){cxzOVEzjdM = false;}
      if(WcIDbzzJTk == true){WcIDbzzJTk = false;}
      if(EcTwxnrWUI == true){EcTwxnrWUI = false;}
      if(dcMLqWoIdq == true){dcMLqWoIdq = false;}
      if(uedBqQmxis == true){uedBqQmxis = false;}
      if(fiCSOzcDRh == true){fiCSOzcDRh = false;}
      if(MbPVitPwME == true){MbPVitPwME = false;}
      if(JqecpZyRFf == true){JqecpZyRFf = false;}
      if(BtmacuZswq == true){BtmacuZswq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BAJCPPIVUM
{ 
  void lCEapCxaBq()
  { 
      bool bKeruPKejg = false;
      bool wSgeRGTrBy = false;
      bool ZpImBDQwmq = false;
      bool uTOzLywAyn = false;
      bool EVTZOdotJZ = false;
      bool xnTrxkBrqr = false;
      bool yOrrkbDhSS = false;
      bool JStMtEWhXW = false;
      bool NVlMsGzWBa = false;
      bool wEJGpodanl = false;
      bool ZGbqQetHxs = false;
      bool OTTTdcbeye = false;
      bool cggqWFImWE = false;
      bool ZuskwGtuwN = false;
      bool LqYILcjocM = false;
      bool MzbJJsZjTL = false;
      bool VHksSTZiWX = false;
      bool hghjTkHXfs = false;
      bool UTKJqaSjaD = false;
      bool fKakrDGfpr = false;
      string DjwAncOruf;
      string gELetsrdPg;
      string BuTuGPYOHN;
      string RMyjhaFQjb;
      string ltOrZHKWuw;
      string NqpJTHPBsY;
      string EAkhNTFawT;
      string matmuHgaVy;
      string ECSKAaWoQZ;
      string KEWKXlIgeF;
      string CiZbIlwCOL;
      string aoetTCgZhm;
      string wQKVIhEjPI;
      string yAuPwVbqCN;
      string dTaEzUZcpV;
      string EiyrIkYESZ;
      string hMmFNasPxy;
      string ZoXTIboFWn;
      string IastEOBDGK;
      string xWYbfRgVpX;
      if(DjwAncOruf == CiZbIlwCOL){bKeruPKejg = true;}
      else if(CiZbIlwCOL == DjwAncOruf){ZGbqQetHxs = true;}
      if(gELetsrdPg == aoetTCgZhm){wSgeRGTrBy = true;}
      else if(aoetTCgZhm == gELetsrdPg){OTTTdcbeye = true;}
      if(BuTuGPYOHN == wQKVIhEjPI){ZpImBDQwmq = true;}
      else if(wQKVIhEjPI == BuTuGPYOHN){cggqWFImWE = true;}
      if(RMyjhaFQjb == yAuPwVbqCN){uTOzLywAyn = true;}
      else if(yAuPwVbqCN == RMyjhaFQjb){ZuskwGtuwN = true;}
      if(ltOrZHKWuw == dTaEzUZcpV){EVTZOdotJZ = true;}
      else if(dTaEzUZcpV == ltOrZHKWuw){LqYILcjocM = true;}
      if(NqpJTHPBsY == EiyrIkYESZ){xnTrxkBrqr = true;}
      else if(EiyrIkYESZ == NqpJTHPBsY){MzbJJsZjTL = true;}
      if(EAkhNTFawT == hMmFNasPxy){yOrrkbDhSS = true;}
      else if(hMmFNasPxy == EAkhNTFawT){VHksSTZiWX = true;}
      if(matmuHgaVy == ZoXTIboFWn){JStMtEWhXW = true;}
      if(ECSKAaWoQZ == IastEOBDGK){NVlMsGzWBa = true;}
      if(KEWKXlIgeF == xWYbfRgVpX){wEJGpodanl = true;}
      while(ZoXTIboFWn == matmuHgaVy){hghjTkHXfs = true;}
      while(IastEOBDGK == IastEOBDGK){UTKJqaSjaD = true;}
      while(xWYbfRgVpX == xWYbfRgVpX){fKakrDGfpr = true;}
      if(bKeruPKejg == true){bKeruPKejg = false;}
      if(wSgeRGTrBy == true){wSgeRGTrBy = false;}
      if(ZpImBDQwmq == true){ZpImBDQwmq = false;}
      if(uTOzLywAyn == true){uTOzLywAyn = false;}
      if(EVTZOdotJZ == true){EVTZOdotJZ = false;}
      if(xnTrxkBrqr == true){xnTrxkBrqr = false;}
      if(yOrrkbDhSS == true){yOrrkbDhSS = false;}
      if(JStMtEWhXW == true){JStMtEWhXW = false;}
      if(NVlMsGzWBa == true){NVlMsGzWBa = false;}
      if(wEJGpodanl == true){wEJGpodanl = false;}
      if(ZGbqQetHxs == true){ZGbqQetHxs = false;}
      if(OTTTdcbeye == true){OTTTdcbeye = false;}
      if(cggqWFImWE == true){cggqWFImWE = false;}
      if(ZuskwGtuwN == true){ZuskwGtuwN = false;}
      if(LqYILcjocM == true){LqYILcjocM = false;}
      if(MzbJJsZjTL == true){MzbJJsZjTL = false;}
      if(VHksSTZiWX == true){VHksSTZiWX = false;}
      if(hghjTkHXfs == true){hghjTkHXfs = false;}
      if(UTKJqaSjaD == true){UTKJqaSjaD = false;}
      if(fKakrDGfpr == true){fKakrDGfpr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SKYLIOJKLS
{ 
  void MXMDdLHLFY()
  { 
      bool jfxDdhroen = false;
      bool WSMnhjSqGa = false;
      bool miKQIThAgN = false;
      bool oRlZKcYRkf = false;
      bool rlwPcXhjYY = false;
      bool ESBPsBUgtJ = false;
      bool AqIQyEflcF = false;
      bool KAFahBlumj = false;
      bool lxaHJWQWgJ = false;
      bool HrXaeAcfRX = false;
      bool ruGTODNZhr = false;
      bool OZsJXCQBHa = false;
      bool nJFTyRcdug = false;
      bool XGdPrqqHrF = false;
      bool JpnntgzNDc = false;
      bool jbXpihomUw = false;
      bool aidBUIwcQg = false;
      bool LIICRyVRZQ = false;
      bool SOaSwuinfK = false;
      bool BEmwdZLmTl = false;
      string ytqDchytQQ;
      string QmdpyDlGMM;
      string ImkqxZUzrE;
      string xWiwZHzdri;
      string DLwfxCJkQy;
      string yZrhuKIzFC;
      string MyCLTtEhPp;
      string DINdIwqEtt;
      string PjitGWdBBO;
      string zAYoVEJkMD;
      string ybUatpLOYy;
      string TDFLmcPIFw;
      string PCfBqDjXHD;
      string mGrqumOIzP;
      string LPcCtutMCr;
      string oBePmwwTiq;
      string GnGULNKOPz;
      string OGIpkzZcGu;
      string IWUPNkabDz;
      string qtYHJWJHpf;
      if(ytqDchytQQ == ybUatpLOYy){jfxDdhroen = true;}
      else if(ybUatpLOYy == ytqDchytQQ){ruGTODNZhr = true;}
      if(QmdpyDlGMM == TDFLmcPIFw){WSMnhjSqGa = true;}
      else if(TDFLmcPIFw == QmdpyDlGMM){OZsJXCQBHa = true;}
      if(ImkqxZUzrE == PCfBqDjXHD){miKQIThAgN = true;}
      else if(PCfBqDjXHD == ImkqxZUzrE){nJFTyRcdug = true;}
      if(xWiwZHzdri == mGrqumOIzP){oRlZKcYRkf = true;}
      else if(mGrqumOIzP == xWiwZHzdri){XGdPrqqHrF = true;}
      if(DLwfxCJkQy == LPcCtutMCr){rlwPcXhjYY = true;}
      else if(LPcCtutMCr == DLwfxCJkQy){JpnntgzNDc = true;}
      if(yZrhuKIzFC == oBePmwwTiq){ESBPsBUgtJ = true;}
      else if(oBePmwwTiq == yZrhuKIzFC){jbXpihomUw = true;}
      if(MyCLTtEhPp == GnGULNKOPz){AqIQyEflcF = true;}
      else if(GnGULNKOPz == MyCLTtEhPp){aidBUIwcQg = true;}
      if(DINdIwqEtt == OGIpkzZcGu){KAFahBlumj = true;}
      if(PjitGWdBBO == IWUPNkabDz){lxaHJWQWgJ = true;}
      if(zAYoVEJkMD == qtYHJWJHpf){HrXaeAcfRX = true;}
      while(OGIpkzZcGu == DINdIwqEtt){LIICRyVRZQ = true;}
      while(IWUPNkabDz == IWUPNkabDz){SOaSwuinfK = true;}
      while(qtYHJWJHpf == qtYHJWJHpf){BEmwdZLmTl = true;}
      if(jfxDdhroen == true){jfxDdhroen = false;}
      if(WSMnhjSqGa == true){WSMnhjSqGa = false;}
      if(miKQIThAgN == true){miKQIThAgN = false;}
      if(oRlZKcYRkf == true){oRlZKcYRkf = false;}
      if(rlwPcXhjYY == true){rlwPcXhjYY = false;}
      if(ESBPsBUgtJ == true){ESBPsBUgtJ = false;}
      if(AqIQyEflcF == true){AqIQyEflcF = false;}
      if(KAFahBlumj == true){KAFahBlumj = false;}
      if(lxaHJWQWgJ == true){lxaHJWQWgJ = false;}
      if(HrXaeAcfRX == true){HrXaeAcfRX = false;}
      if(ruGTODNZhr == true){ruGTODNZhr = false;}
      if(OZsJXCQBHa == true){OZsJXCQBHa = false;}
      if(nJFTyRcdug == true){nJFTyRcdug = false;}
      if(XGdPrqqHrF == true){XGdPrqqHrF = false;}
      if(JpnntgzNDc == true){JpnntgzNDc = false;}
      if(jbXpihomUw == true){jbXpihomUw = false;}
      if(aidBUIwcQg == true){aidBUIwcQg = false;}
      if(LIICRyVRZQ == true){LIICRyVRZQ = false;}
      if(SOaSwuinfK == true){SOaSwuinfK = false;}
      if(BEmwdZLmTl == true){BEmwdZLmTl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SEEIHHXWQY
{ 
  void alhkTnGMGR()
  { 
      bool rkIJWrAQkq = false;
      bool aLdpYHKrZo = false;
      bool pOQAUYVyWN = false;
      bool qiLUghICNU = false;
      bool eJHIFKhQlY = false;
      bool yHwsOcUHny = false;
      bool VCtWzrAJIq = false;
      bool yHdFKgHHuK = false;
      bool pFMyPilRFE = false;
      bool MBOPycPjIN = false;
      bool JXIuZpdqih = false;
      bool VNMcIQowHQ = false;
      bool FiEEdxsOGh = false;
      bool RWygARwRXY = false;
      bool FuhWhznkGh = false;
      bool mTbrHaTDQb = false;
      bool wOjBQyOecp = false;
      bool TXXiKKAgVe = false;
      bool IIHXuyuGZZ = false;
      bool ysAubqKfGi = false;
      string YMOCsUoewz;
      string NAqqLNYAqg;
      string KqqYAtyfBD;
      string fkEgNdpjSj;
      string dzUeiqNeVj;
      string TQgYTgVoBz;
      string WJcrSbuKch;
      string WngHDKWMpI;
      string fSKQjPEfMg;
      string IBhTMUVbLG;
      string wDBnNejYVJ;
      string KIzsSDzMID;
      string XPxwYVGMth;
      string otBiMbRVDF;
      string feJDVzBoAJ;
      string VJTIifFEOr;
      string YWdmUQHPgq;
      string lcIDWrFtZY;
      string TQLkMeZrzf;
      string VMGKfJAWiF;
      if(YMOCsUoewz == wDBnNejYVJ){rkIJWrAQkq = true;}
      else if(wDBnNejYVJ == YMOCsUoewz){JXIuZpdqih = true;}
      if(NAqqLNYAqg == KIzsSDzMID){aLdpYHKrZo = true;}
      else if(KIzsSDzMID == NAqqLNYAqg){VNMcIQowHQ = true;}
      if(KqqYAtyfBD == XPxwYVGMth){pOQAUYVyWN = true;}
      else if(XPxwYVGMth == KqqYAtyfBD){FiEEdxsOGh = true;}
      if(fkEgNdpjSj == otBiMbRVDF){qiLUghICNU = true;}
      else if(otBiMbRVDF == fkEgNdpjSj){RWygARwRXY = true;}
      if(dzUeiqNeVj == feJDVzBoAJ){eJHIFKhQlY = true;}
      else if(feJDVzBoAJ == dzUeiqNeVj){FuhWhznkGh = true;}
      if(TQgYTgVoBz == VJTIifFEOr){yHwsOcUHny = true;}
      else if(VJTIifFEOr == TQgYTgVoBz){mTbrHaTDQb = true;}
      if(WJcrSbuKch == YWdmUQHPgq){VCtWzrAJIq = true;}
      else if(YWdmUQHPgq == WJcrSbuKch){wOjBQyOecp = true;}
      if(WngHDKWMpI == lcIDWrFtZY){yHdFKgHHuK = true;}
      if(fSKQjPEfMg == TQLkMeZrzf){pFMyPilRFE = true;}
      if(IBhTMUVbLG == VMGKfJAWiF){MBOPycPjIN = true;}
      while(lcIDWrFtZY == WngHDKWMpI){TXXiKKAgVe = true;}
      while(TQLkMeZrzf == TQLkMeZrzf){IIHXuyuGZZ = true;}
      while(VMGKfJAWiF == VMGKfJAWiF){ysAubqKfGi = true;}
      if(rkIJWrAQkq == true){rkIJWrAQkq = false;}
      if(aLdpYHKrZo == true){aLdpYHKrZo = false;}
      if(pOQAUYVyWN == true){pOQAUYVyWN = false;}
      if(qiLUghICNU == true){qiLUghICNU = false;}
      if(eJHIFKhQlY == true){eJHIFKhQlY = false;}
      if(yHwsOcUHny == true){yHwsOcUHny = false;}
      if(VCtWzrAJIq == true){VCtWzrAJIq = false;}
      if(yHdFKgHHuK == true){yHdFKgHHuK = false;}
      if(pFMyPilRFE == true){pFMyPilRFE = false;}
      if(MBOPycPjIN == true){MBOPycPjIN = false;}
      if(JXIuZpdqih == true){JXIuZpdqih = false;}
      if(VNMcIQowHQ == true){VNMcIQowHQ = false;}
      if(FiEEdxsOGh == true){FiEEdxsOGh = false;}
      if(RWygARwRXY == true){RWygARwRXY = false;}
      if(FuhWhznkGh == true){FuhWhznkGh = false;}
      if(mTbrHaTDQb == true){mTbrHaTDQb = false;}
      if(wOjBQyOecp == true){wOjBQyOecp = false;}
      if(TXXiKKAgVe == true){TXXiKKAgVe = false;}
      if(IIHXuyuGZZ == true){IIHXuyuGZZ = false;}
      if(ysAubqKfGi == true){ysAubqKfGi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XMAHAPUZYQ
{ 
  void HuJsKpPBIi()
  { 
      bool qyijqrVrAn = false;
      bool qVgtfdhSqy = false;
      bool gLLKGyyqop = false;
      bool KJZKGPSruT = false;
      bool tzlewerERU = false;
      bool RNqdYfmYcr = false;
      bool teDKchuVnQ = false;
      bool KoXWDgZfNa = false;
      bool GsZTXxSwla = false;
      bool btPCZPwaBN = false;
      bool jVQAJcpTZq = false;
      bool GGKClAFilf = false;
      bool PzjNnQZUwn = false;
      bool kyezpkbYKu = false;
      bool HyVtTViMQZ = false;
      bool KNoVykkDLr = false;
      bool DUXlGIbKLA = false;
      bool XfYpXRdpsS = false;
      bool hMEWcXIIBF = false;
      bool zYMRrmZimL = false;
      string rhKQebSUFx;
      string UriIGfwwUW;
      string abqdLBWFJu;
      string KDZAoEkIDM;
      string qEHaYcEKhf;
      string CWMjOPpgEd;
      string FMLKmRRiSC;
      string umsHfVUQEi;
      string wMXdsnpolY;
      string OEDYHdsxnG;
      string LVqfkOdFEr;
      string uZbVhsohRy;
      string bbwtmpiTAB;
      string cWbxWZVrrd;
      string JkksdochqO;
      string oLfoeiYxrt;
      string eKEDPXxdyH;
      string WxomoqqDPy;
      string NBclLQqlSn;
      string BYzyyzfhcF;
      if(rhKQebSUFx == LVqfkOdFEr){qyijqrVrAn = true;}
      else if(LVqfkOdFEr == rhKQebSUFx){jVQAJcpTZq = true;}
      if(UriIGfwwUW == uZbVhsohRy){qVgtfdhSqy = true;}
      else if(uZbVhsohRy == UriIGfwwUW){GGKClAFilf = true;}
      if(abqdLBWFJu == bbwtmpiTAB){gLLKGyyqop = true;}
      else if(bbwtmpiTAB == abqdLBWFJu){PzjNnQZUwn = true;}
      if(KDZAoEkIDM == cWbxWZVrrd){KJZKGPSruT = true;}
      else if(cWbxWZVrrd == KDZAoEkIDM){kyezpkbYKu = true;}
      if(qEHaYcEKhf == JkksdochqO){tzlewerERU = true;}
      else if(JkksdochqO == qEHaYcEKhf){HyVtTViMQZ = true;}
      if(CWMjOPpgEd == oLfoeiYxrt){RNqdYfmYcr = true;}
      else if(oLfoeiYxrt == CWMjOPpgEd){KNoVykkDLr = true;}
      if(FMLKmRRiSC == eKEDPXxdyH){teDKchuVnQ = true;}
      else if(eKEDPXxdyH == FMLKmRRiSC){DUXlGIbKLA = true;}
      if(umsHfVUQEi == WxomoqqDPy){KoXWDgZfNa = true;}
      if(wMXdsnpolY == NBclLQqlSn){GsZTXxSwla = true;}
      if(OEDYHdsxnG == BYzyyzfhcF){btPCZPwaBN = true;}
      while(WxomoqqDPy == umsHfVUQEi){XfYpXRdpsS = true;}
      while(NBclLQqlSn == NBclLQqlSn){hMEWcXIIBF = true;}
      while(BYzyyzfhcF == BYzyyzfhcF){zYMRrmZimL = true;}
      if(qyijqrVrAn == true){qyijqrVrAn = false;}
      if(qVgtfdhSqy == true){qVgtfdhSqy = false;}
      if(gLLKGyyqop == true){gLLKGyyqop = false;}
      if(KJZKGPSruT == true){KJZKGPSruT = false;}
      if(tzlewerERU == true){tzlewerERU = false;}
      if(RNqdYfmYcr == true){RNqdYfmYcr = false;}
      if(teDKchuVnQ == true){teDKchuVnQ = false;}
      if(KoXWDgZfNa == true){KoXWDgZfNa = false;}
      if(GsZTXxSwla == true){GsZTXxSwla = false;}
      if(btPCZPwaBN == true){btPCZPwaBN = false;}
      if(jVQAJcpTZq == true){jVQAJcpTZq = false;}
      if(GGKClAFilf == true){GGKClAFilf = false;}
      if(PzjNnQZUwn == true){PzjNnQZUwn = false;}
      if(kyezpkbYKu == true){kyezpkbYKu = false;}
      if(HyVtTViMQZ == true){HyVtTViMQZ = false;}
      if(KNoVykkDLr == true){KNoVykkDLr = false;}
      if(DUXlGIbKLA == true){DUXlGIbKLA = false;}
      if(XfYpXRdpsS == true){XfYpXRdpsS = false;}
      if(hMEWcXIIBF == true){hMEWcXIIBF = false;}
      if(zYMRrmZimL == true){zYMRrmZimL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KSSPGMBSDX
{ 
  void gEziPaCwwd()
  { 
      bool ClHoAlouYh = false;
      bool sWoOfsjMkC = false;
      bool omzspoINNH = false;
      bool wKemHKYmks = false;
      bool OKZQCryseR = false;
      bool CdupTPlOyL = false;
      bool dbhRlhqCGU = false;
      bool UxbrmdMipx = false;
      bool qOiuFRPoSr = false;
      bool XKnYOmcIeU = false;
      bool BumJxECCDp = false;
      bool CDXAUOslLT = false;
      bool SCiOxJICcA = false;
      bool BEEVwubYyA = false;
      bool PMkcoTmnEA = false;
      bool spwKByLXMm = false;
      bool wzZCoyzBDY = false;
      bool mTmLEGQGYc = false;
      bool WUxcGKHsTy = false;
      bool iDMLEPmhmq = false;
      string MFfOnpetDd;
      string tUiZaVKttm;
      string UmUwdrZanA;
      string COfmzflHJx;
      string EehndROMUr;
      string ITLhPZkjkw;
      string QEGCbfouZu;
      string iCjxhpEfRL;
      string dMGurhDyXY;
      string tCWNgAXeMy;
      string cSmZIGiNzY;
      string UFRYRDxKKs;
      string cqWAAgeWPh;
      string RZSTiLZgll;
      string yoyzEojyud;
      string CNTTUlulYb;
      string aLyQGulypG;
      string cQXYtmrXwK;
      string wgbleEGzyw;
      string PnHKLmqgrJ;
      if(MFfOnpetDd == cSmZIGiNzY){ClHoAlouYh = true;}
      else if(cSmZIGiNzY == MFfOnpetDd){BumJxECCDp = true;}
      if(tUiZaVKttm == UFRYRDxKKs){sWoOfsjMkC = true;}
      else if(UFRYRDxKKs == tUiZaVKttm){CDXAUOslLT = true;}
      if(UmUwdrZanA == cqWAAgeWPh){omzspoINNH = true;}
      else if(cqWAAgeWPh == UmUwdrZanA){SCiOxJICcA = true;}
      if(COfmzflHJx == RZSTiLZgll){wKemHKYmks = true;}
      else if(RZSTiLZgll == COfmzflHJx){BEEVwubYyA = true;}
      if(EehndROMUr == yoyzEojyud){OKZQCryseR = true;}
      else if(yoyzEojyud == EehndROMUr){PMkcoTmnEA = true;}
      if(ITLhPZkjkw == CNTTUlulYb){CdupTPlOyL = true;}
      else if(CNTTUlulYb == ITLhPZkjkw){spwKByLXMm = true;}
      if(QEGCbfouZu == aLyQGulypG){dbhRlhqCGU = true;}
      else if(aLyQGulypG == QEGCbfouZu){wzZCoyzBDY = true;}
      if(iCjxhpEfRL == cQXYtmrXwK){UxbrmdMipx = true;}
      if(dMGurhDyXY == wgbleEGzyw){qOiuFRPoSr = true;}
      if(tCWNgAXeMy == PnHKLmqgrJ){XKnYOmcIeU = true;}
      while(cQXYtmrXwK == iCjxhpEfRL){mTmLEGQGYc = true;}
      while(wgbleEGzyw == wgbleEGzyw){WUxcGKHsTy = true;}
      while(PnHKLmqgrJ == PnHKLmqgrJ){iDMLEPmhmq = true;}
      if(ClHoAlouYh == true){ClHoAlouYh = false;}
      if(sWoOfsjMkC == true){sWoOfsjMkC = false;}
      if(omzspoINNH == true){omzspoINNH = false;}
      if(wKemHKYmks == true){wKemHKYmks = false;}
      if(OKZQCryseR == true){OKZQCryseR = false;}
      if(CdupTPlOyL == true){CdupTPlOyL = false;}
      if(dbhRlhqCGU == true){dbhRlhqCGU = false;}
      if(UxbrmdMipx == true){UxbrmdMipx = false;}
      if(qOiuFRPoSr == true){qOiuFRPoSr = false;}
      if(XKnYOmcIeU == true){XKnYOmcIeU = false;}
      if(BumJxECCDp == true){BumJxECCDp = false;}
      if(CDXAUOslLT == true){CDXAUOslLT = false;}
      if(SCiOxJICcA == true){SCiOxJICcA = false;}
      if(BEEVwubYyA == true){BEEVwubYyA = false;}
      if(PMkcoTmnEA == true){PMkcoTmnEA = false;}
      if(spwKByLXMm == true){spwKByLXMm = false;}
      if(wzZCoyzBDY == true){wzZCoyzBDY = false;}
      if(mTmLEGQGYc == true){mTmLEGQGYc = false;}
      if(WUxcGKHsTy == true){WUxcGKHsTy = false;}
      if(iDMLEPmhmq == true){iDMLEPmhmq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ITYDPKXVAV
{ 
  void JsDDTddpqC()
  { 
      bool wPpAEDBRyB = false;
      bool itpVLCKnCr = false;
      bool CqwxJnjRPT = false;
      bool rDacMATOJE = false;
      bool cyZHTKIuRH = false;
      bool mXLiQESspQ = false;
      bool TiBdIfTNJL = false;
      bool iueyODRodz = false;
      bool eoAIgUqqMH = false;
      bool haXsjtwuzn = false;
      bool pukGXqrMUM = false;
      bool lcOqkdisxm = false;
      bool nbBBdHWkOT = false;
      bool GWpoIjDsjo = false;
      bool beWzVELgHG = false;
      bool LDxLzOtjcP = false;
      bool THyAFPmZiB = false;
      bool aoIHKJFBfY = false;
      bool wpcHIDYdos = false;
      bool oTPTVUfVsF = false;
      string qMEcpoZSiD;
      string tXLZxQspQK;
      string oUPzchNfBy;
      string lEiRhMrwjr;
      string uPYVNfnKkj;
      string LKglWVwEAI;
      string asRjRonsrk;
      string XxGXOYwslw;
      string tCuQlbWwuL;
      string PmubQCxnEX;
      string rtRzLOEJXx;
      string ZDSENYxAxo;
      string RqygUjBdGM;
      string aHnNDAkwFX;
      string XNYxkLUqOr;
      string EwqPFAukea;
      string NZCKVSPFAN;
      string nBuZRERBuI;
      string PKPOHdPXIC;
      string EzQdJxLOaS;
      if(qMEcpoZSiD == rtRzLOEJXx){wPpAEDBRyB = true;}
      else if(rtRzLOEJXx == qMEcpoZSiD){pukGXqrMUM = true;}
      if(tXLZxQspQK == ZDSENYxAxo){itpVLCKnCr = true;}
      else if(ZDSENYxAxo == tXLZxQspQK){lcOqkdisxm = true;}
      if(oUPzchNfBy == RqygUjBdGM){CqwxJnjRPT = true;}
      else if(RqygUjBdGM == oUPzchNfBy){nbBBdHWkOT = true;}
      if(lEiRhMrwjr == aHnNDAkwFX){rDacMATOJE = true;}
      else if(aHnNDAkwFX == lEiRhMrwjr){GWpoIjDsjo = true;}
      if(uPYVNfnKkj == XNYxkLUqOr){cyZHTKIuRH = true;}
      else if(XNYxkLUqOr == uPYVNfnKkj){beWzVELgHG = true;}
      if(LKglWVwEAI == EwqPFAukea){mXLiQESspQ = true;}
      else if(EwqPFAukea == LKglWVwEAI){LDxLzOtjcP = true;}
      if(asRjRonsrk == NZCKVSPFAN){TiBdIfTNJL = true;}
      else if(NZCKVSPFAN == asRjRonsrk){THyAFPmZiB = true;}
      if(XxGXOYwslw == nBuZRERBuI){iueyODRodz = true;}
      if(tCuQlbWwuL == PKPOHdPXIC){eoAIgUqqMH = true;}
      if(PmubQCxnEX == EzQdJxLOaS){haXsjtwuzn = true;}
      while(nBuZRERBuI == XxGXOYwslw){aoIHKJFBfY = true;}
      while(PKPOHdPXIC == PKPOHdPXIC){wpcHIDYdos = true;}
      while(EzQdJxLOaS == EzQdJxLOaS){oTPTVUfVsF = true;}
      if(wPpAEDBRyB == true){wPpAEDBRyB = false;}
      if(itpVLCKnCr == true){itpVLCKnCr = false;}
      if(CqwxJnjRPT == true){CqwxJnjRPT = false;}
      if(rDacMATOJE == true){rDacMATOJE = false;}
      if(cyZHTKIuRH == true){cyZHTKIuRH = false;}
      if(mXLiQESspQ == true){mXLiQESspQ = false;}
      if(TiBdIfTNJL == true){TiBdIfTNJL = false;}
      if(iueyODRodz == true){iueyODRodz = false;}
      if(eoAIgUqqMH == true){eoAIgUqqMH = false;}
      if(haXsjtwuzn == true){haXsjtwuzn = false;}
      if(pukGXqrMUM == true){pukGXqrMUM = false;}
      if(lcOqkdisxm == true){lcOqkdisxm = false;}
      if(nbBBdHWkOT == true){nbBBdHWkOT = false;}
      if(GWpoIjDsjo == true){GWpoIjDsjo = false;}
      if(beWzVELgHG == true){beWzVELgHG = false;}
      if(LDxLzOtjcP == true){LDxLzOtjcP = false;}
      if(THyAFPmZiB == true){THyAFPmZiB = false;}
      if(aoIHKJFBfY == true){aoIHKJFBfY = false;}
      if(wpcHIDYdos == true){wpcHIDYdos = false;}
      if(oTPTVUfVsF == true){oTPTVUfVsF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YASPFQSWNR
{ 
  void LIgLdOxYLz()
  { 
      bool hCOLkXrqfT = false;
      bool fNKAZkYNMJ = false;
      bool rpKQTecUFW = false;
      bool GhEszYwgBm = false;
      bool CQRWlwPgdT = false;
      bool nkVTqrrxqF = false;
      bool uWlIMyJQAB = false;
      bool nqLZGbXmdW = false;
      bool PwqkhVMjCH = false;
      bool fypurfeIKn = false;
      bool mzfbexYuMP = false;
      bool TFTUpyfAap = false;
      bool kYOsUpBQha = false;
      bool xPbpjQQOGk = false;
      bool xQXlnaeUFs = false;
      bool zdhTCNklGn = false;
      bool uINlSDcdjZ = false;
      bool hRsosUBbFt = false;
      bool KfKnaShImV = false;
      bool edHSooDkTj = false;
      string dNWlkNpnsg;
      string glgfrjuhjl;
      string UASJAkcOVZ;
      string mxqUXRhkZu;
      string jNfZOPVLMi;
      string QHSSWdtMkz;
      string kbRTtjuLIa;
      string BJInBHUsuk;
      string PQBmIedXxs;
      string WVzZKIuLfe;
      string UJClgGzeRP;
      string IBRAjTZeKP;
      string FWOODeKhds;
      string LINQQFOPFB;
      string ezGgjVEzop;
      string hQAPYxunhB;
      string wRAXEAmBjd;
      string FKYJjFQgdh;
      string aLrmKtHxqS;
      string KZgEENyhcj;
      if(dNWlkNpnsg == UJClgGzeRP){hCOLkXrqfT = true;}
      else if(UJClgGzeRP == dNWlkNpnsg){mzfbexYuMP = true;}
      if(glgfrjuhjl == IBRAjTZeKP){fNKAZkYNMJ = true;}
      else if(IBRAjTZeKP == glgfrjuhjl){TFTUpyfAap = true;}
      if(UASJAkcOVZ == FWOODeKhds){rpKQTecUFW = true;}
      else if(FWOODeKhds == UASJAkcOVZ){kYOsUpBQha = true;}
      if(mxqUXRhkZu == LINQQFOPFB){GhEszYwgBm = true;}
      else if(LINQQFOPFB == mxqUXRhkZu){xPbpjQQOGk = true;}
      if(jNfZOPVLMi == ezGgjVEzop){CQRWlwPgdT = true;}
      else if(ezGgjVEzop == jNfZOPVLMi){xQXlnaeUFs = true;}
      if(QHSSWdtMkz == hQAPYxunhB){nkVTqrrxqF = true;}
      else if(hQAPYxunhB == QHSSWdtMkz){zdhTCNklGn = true;}
      if(kbRTtjuLIa == wRAXEAmBjd){uWlIMyJQAB = true;}
      else if(wRAXEAmBjd == kbRTtjuLIa){uINlSDcdjZ = true;}
      if(BJInBHUsuk == FKYJjFQgdh){nqLZGbXmdW = true;}
      if(PQBmIedXxs == aLrmKtHxqS){PwqkhVMjCH = true;}
      if(WVzZKIuLfe == KZgEENyhcj){fypurfeIKn = true;}
      while(FKYJjFQgdh == BJInBHUsuk){hRsosUBbFt = true;}
      while(aLrmKtHxqS == aLrmKtHxqS){KfKnaShImV = true;}
      while(KZgEENyhcj == KZgEENyhcj){edHSooDkTj = true;}
      if(hCOLkXrqfT == true){hCOLkXrqfT = false;}
      if(fNKAZkYNMJ == true){fNKAZkYNMJ = false;}
      if(rpKQTecUFW == true){rpKQTecUFW = false;}
      if(GhEszYwgBm == true){GhEszYwgBm = false;}
      if(CQRWlwPgdT == true){CQRWlwPgdT = false;}
      if(nkVTqrrxqF == true){nkVTqrrxqF = false;}
      if(uWlIMyJQAB == true){uWlIMyJQAB = false;}
      if(nqLZGbXmdW == true){nqLZGbXmdW = false;}
      if(PwqkhVMjCH == true){PwqkhVMjCH = false;}
      if(fypurfeIKn == true){fypurfeIKn = false;}
      if(mzfbexYuMP == true){mzfbexYuMP = false;}
      if(TFTUpyfAap == true){TFTUpyfAap = false;}
      if(kYOsUpBQha == true){kYOsUpBQha = false;}
      if(xPbpjQQOGk == true){xPbpjQQOGk = false;}
      if(xQXlnaeUFs == true){xQXlnaeUFs = false;}
      if(zdhTCNklGn == true){zdhTCNklGn = false;}
      if(uINlSDcdjZ == true){uINlSDcdjZ = false;}
      if(hRsosUBbFt == true){hRsosUBbFt = false;}
      if(KfKnaShImV == true){KfKnaShImV = false;}
      if(edHSooDkTj == true){edHSooDkTj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BSZBMEKUAB
{ 
  void pMhbkATcHL()
  { 
      bool KYSJNiwlsO = false;
      bool qDCylFmjHG = false;
      bool cYVIQpZMPa = false;
      bool LMgRQiOhOz = false;
      bool GDZXAfYbwB = false;
      bool ERnFulCKsX = false;
      bool IiWRDdVjgC = false;
      bool qEVHzYzyHk = false;
      bool QyQNWtYbVe = false;
      bool fDoppXgHTV = false;
      bool JntsJzwfFV = false;
      bool lECIHKSIuI = false;
      bool FtNCWmPeRb = false;
      bool rrdlabDWEX = false;
      bool yrVAsbBghf = false;
      bool EYMLPParWW = false;
      bool jQOddtZPgf = false;
      bool HuEXKMYNJt = false;
      bool liwkWSeSVL = false;
      bool BLAgmgdqVy = false;
      string fTLmPEWhZa;
      string iuerZoqJcA;
      string KrUYOrUNwc;
      string haIoyWrhOC;
      string uAVrIeAWHh;
      string wctNOnymYX;
      string jIlxsHmosC;
      string wItZFJWcPi;
      string qxGOgEgtaK;
      string XFIqRlOXzB;
      string rKcEkmhTIE;
      string RVWpflCXPn;
      string ZsOidqzDHS;
      string tydNpfUBct;
      string VMkVrChSKe;
      string jqIKbzwsZt;
      string meLpJTqIzA;
      string RBuVRMHsqb;
      string IgrbhDpSlq;
      string ibahGqBuLY;
      if(fTLmPEWhZa == rKcEkmhTIE){KYSJNiwlsO = true;}
      else if(rKcEkmhTIE == fTLmPEWhZa){JntsJzwfFV = true;}
      if(iuerZoqJcA == RVWpflCXPn){qDCylFmjHG = true;}
      else if(RVWpflCXPn == iuerZoqJcA){lECIHKSIuI = true;}
      if(KrUYOrUNwc == ZsOidqzDHS){cYVIQpZMPa = true;}
      else if(ZsOidqzDHS == KrUYOrUNwc){FtNCWmPeRb = true;}
      if(haIoyWrhOC == tydNpfUBct){LMgRQiOhOz = true;}
      else if(tydNpfUBct == haIoyWrhOC){rrdlabDWEX = true;}
      if(uAVrIeAWHh == VMkVrChSKe){GDZXAfYbwB = true;}
      else if(VMkVrChSKe == uAVrIeAWHh){yrVAsbBghf = true;}
      if(wctNOnymYX == jqIKbzwsZt){ERnFulCKsX = true;}
      else if(jqIKbzwsZt == wctNOnymYX){EYMLPParWW = true;}
      if(jIlxsHmosC == meLpJTqIzA){IiWRDdVjgC = true;}
      else if(meLpJTqIzA == jIlxsHmosC){jQOddtZPgf = true;}
      if(wItZFJWcPi == RBuVRMHsqb){qEVHzYzyHk = true;}
      if(qxGOgEgtaK == IgrbhDpSlq){QyQNWtYbVe = true;}
      if(XFIqRlOXzB == ibahGqBuLY){fDoppXgHTV = true;}
      while(RBuVRMHsqb == wItZFJWcPi){HuEXKMYNJt = true;}
      while(IgrbhDpSlq == IgrbhDpSlq){liwkWSeSVL = true;}
      while(ibahGqBuLY == ibahGqBuLY){BLAgmgdqVy = true;}
      if(KYSJNiwlsO == true){KYSJNiwlsO = false;}
      if(qDCylFmjHG == true){qDCylFmjHG = false;}
      if(cYVIQpZMPa == true){cYVIQpZMPa = false;}
      if(LMgRQiOhOz == true){LMgRQiOhOz = false;}
      if(GDZXAfYbwB == true){GDZXAfYbwB = false;}
      if(ERnFulCKsX == true){ERnFulCKsX = false;}
      if(IiWRDdVjgC == true){IiWRDdVjgC = false;}
      if(qEVHzYzyHk == true){qEVHzYzyHk = false;}
      if(QyQNWtYbVe == true){QyQNWtYbVe = false;}
      if(fDoppXgHTV == true){fDoppXgHTV = false;}
      if(JntsJzwfFV == true){JntsJzwfFV = false;}
      if(lECIHKSIuI == true){lECIHKSIuI = false;}
      if(FtNCWmPeRb == true){FtNCWmPeRb = false;}
      if(rrdlabDWEX == true){rrdlabDWEX = false;}
      if(yrVAsbBghf == true){yrVAsbBghf = false;}
      if(EYMLPParWW == true){EYMLPParWW = false;}
      if(jQOddtZPgf == true){jQOddtZPgf = false;}
      if(HuEXKMYNJt == true){HuEXKMYNJt = false;}
      if(liwkWSeSVL == true){liwkWSeSVL = false;}
      if(BLAgmgdqVy == true){BLAgmgdqVy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LGLBDRRBKS
{ 
  void tDEhtnHieA()
  { 
      bool IXPZMAoRxf = false;
      bool gECUVCzHHH = false;
      bool qKtDdDgTdO = false;
      bool mrzZMsLhzK = false;
      bool pckCRDnNIn = false;
      bool yFwbWydLwJ = false;
      bool SUnhsoFcIb = false;
      bool pQHwRNZqla = false;
      bool OSLoPguXCN = false;
      bool OAlprVoDJb = false;
      bool xKEfyhxzKI = false;
      bool YmYVuzJyRL = false;
      bool shatMoeREu = false;
      bool YVhJcDNeqh = false;
      bool iwMsobbPtr = false;
      bool MpkxiPjKSI = false;
      bool CeuOiCFOrr = false;
      bool kdHicxUgFk = false;
      bool NOXLiikjaM = false;
      bool SDMhfDByJm = false;
      string MyWEqzrbqP;
      string aegQCalehT;
      string GdsADSGNoG;
      string STtzErOwRc;
      string kmPYWfbrYR;
      string MmucXiEVBY;
      string relkxHjhLK;
      string LoMFhSNTdW;
      string pOnXseXRbV;
      string mruskGBebO;
      string wtfOGXZotE;
      string UkqdhcpOqR;
      string iSGoXSsSUb;
      string RirOawhZQV;
      string EhWWABBRLH;
      string QlmJfcnqqm;
      string dGUSmlscCk;
      string tPxVMAwinV;
      string RbHMKeuhiy;
      string HqidqxNDjO;
      if(MyWEqzrbqP == wtfOGXZotE){IXPZMAoRxf = true;}
      else if(wtfOGXZotE == MyWEqzrbqP){xKEfyhxzKI = true;}
      if(aegQCalehT == UkqdhcpOqR){gECUVCzHHH = true;}
      else if(UkqdhcpOqR == aegQCalehT){YmYVuzJyRL = true;}
      if(GdsADSGNoG == iSGoXSsSUb){qKtDdDgTdO = true;}
      else if(iSGoXSsSUb == GdsADSGNoG){shatMoeREu = true;}
      if(STtzErOwRc == RirOawhZQV){mrzZMsLhzK = true;}
      else if(RirOawhZQV == STtzErOwRc){YVhJcDNeqh = true;}
      if(kmPYWfbrYR == EhWWABBRLH){pckCRDnNIn = true;}
      else if(EhWWABBRLH == kmPYWfbrYR){iwMsobbPtr = true;}
      if(MmucXiEVBY == QlmJfcnqqm){yFwbWydLwJ = true;}
      else if(QlmJfcnqqm == MmucXiEVBY){MpkxiPjKSI = true;}
      if(relkxHjhLK == dGUSmlscCk){SUnhsoFcIb = true;}
      else if(dGUSmlscCk == relkxHjhLK){CeuOiCFOrr = true;}
      if(LoMFhSNTdW == tPxVMAwinV){pQHwRNZqla = true;}
      if(pOnXseXRbV == RbHMKeuhiy){OSLoPguXCN = true;}
      if(mruskGBebO == HqidqxNDjO){OAlprVoDJb = true;}
      while(tPxVMAwinV == LoMFhSNTdW){kdHicxUgFk = true;}
      while(RbHMKeuhiy == RbHMKeuhiy){NOXLiikjaM = true;}
      while(HqidqxNDjO == HqidqxNDjO){SDMhfDByJm = true;}
      if(IXPZMAoRxf == true){IXPZMAoRxf = false;}
      if(gECUVCzHHH == true){gECUVCzHHH = false;}
      if(qKtDdDgTdO == true){qKtDdDgTdO = false;}
      if(mrzZMsLhzK == true){mrzZMsLhzK = false;}
      if(pckCRDnNIn == true){pckCRDnNIn = false;}
      if(yFwbWydLwJ == true){yFwbWydLwJ = false;}
      if(SUnhsoFcIb == true){SUnhsoFcIb = false;}
      if(pQHwRNZqla == true){pQHwRNZqla = false;}
      if(OSLoPguXCN == true){OSLoPguXCN = false;}
      if(OAlprVoDJb == true){OAlprVoDJb = false;}
      if(xKEfyhxzKI == true){xKEfyhxzKI = false;}
      if(YmYVuzJyRL == true){YmYVuzJyRL = false;}
      if(shatMoeREu == true){shatMoeREu = false;}
      if(YVhJcDNeqh == true){YVhJcDNeqh = false;}
      if(iwMsobbPtr == true){iwMsobbPtr = false;}
      if(MpkxiPjKSI == true){MpkxiPjKSI = false;}
      if(CeuOiCFOrr == true){CeuOiCFOrr = false;}
      if(kdHicxUgFk == true){kdHicxUgFk = false;}
      if(NOXLiikjaM == true){NOXLiikjaM = false;}
      if(SDMhfDByJm == true){SDMhfDByJm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GPREIKEBVY
{ 
  void TiKkpMVLfY()
  { 
      bool TsjErHRyMO = false;
      bool rkDhCMDGFd = false;
      bool SLzIhuJWWA = false;
      bool icBglOaOhz = false;
      bool BISYOMYcNf = false;
      bool FEoeuHtaWw = false;
      bool ytbLePjVwn = false;
      bool koXFcKsZsV = false;
      bool WfJquemVld = false;
      bool TAqlBGgGsz = false;
      bool bCfYtQfjCk = false;
      bool OTgBYRkjQA = false;
      bool bNjSTkxlDV = false;
      bool dmgtsUAjxe = false;
      bool yCSBPASpMi = false;
      bool VwosWORNEI = false;
      bool StfgGammHD = false;
      bool RAmkBZtiCT = false;
      bool SGYUAgxnWe = false;
      bool ClenLDVltn = false;
      string MfSAxotSVz;
      string AKcacsrLns;
      string AxYquNaYcl;
      string AxclCJpsuf;
      string PIeKzcFLWC;
      string jrfZLOGaFi;
      string OUoiyDhqYS;
      string DzQHdqRNrR;
      string IOCaCIQCZm;
      string DOmLQtTuMu;
      string tNlDzjbYuT;
      string xrimaASOgp;
      string leQlPnLEqi;
      string XVBwWtbyaR;
      string frHFpKfAkQ;
      string bEOWIPwAmK;
      string YWgMwaqlPf;
      string XTmPJtXKwF;
      string ILTaHSHemH;
      string ybKQrIKtJO;
      if(MfSAxotSVz == tNlDzjbYuT){TsjErHRyMO = true;}
      else if(tNlDzjbYuT == MfSAxotSVz){bCfYtQfjCk = true;}
      if(AKcacsrLns == xrimaASOgp){rkDhCMDGFd = true;}
      else if(xrimaASOgp == AKcacsrLns){OTgBYRkjQA = true;}
      if(AxYquNaYcl == leQlPnLEqi){SLzIhuJWWA = true;}
      else if(leQlPnLEqi == AxYquNaYcl){bNjSTkxlDV = true;}
      if(AxclCJpsuf == XVBwWtbyaR){icBglOaOhz = true;}
      else if(XVBwWtbyaR == AxclCJpsuf){dmgtsUAjxe = true;}
      if(PIeKzcFLWC == frHFpKfAkQ){BISYOMYcNf = true;}
      else if(frHFpKfAkQ == PIeKzcFLWC){yCSBPASpMi = true;}
      if(jrfZLOGaFi == bEOWIPwAmK){FEoeuHtaWw = true;}
      else if(bEOWIPwAmK == jrfZLOGaFi){VwosWORNEI = true;}
      if(OUoiyDhqYS == YWgMwaqlPf){ytbLePjVwn = true;}
      else if(YWgMwaqlPf == OUoiyDhqYS){StfgGammHD = true;}
      if(DzQHdqRNrR == XTmPJtXKwF){koXFcKsZsV = true;}
      if(IOCaCIQCZm == ILTaHSHemH){WfJquemVld = true;}
      if(DOmLQtTuMu == ybKQrIKtJO){TAqlBGgGsz = true;}
      while(XTmPJtXKwF == DzQHdqRNrR){RAmkBZtiCT = true;}
      while(ILTaHSHemH == ILTaHSHemH){SGYUAgxnWe = true;}
      while(ybKQrIKtJO == ybKQrIKtJO){ClenLDVltn = true;}
      if(TsjErHRyMO == true){TsjErHRyMO = false;}
      if(rkDhCMDGFd == true){rkDhCMDGFd = false;}
      if(SLzIhuJWWA == true){SLzIhuJWWA = false;}
      if(icBglOaOhz == true){icBglOaOhz = false;}
      if(BISYOMYcNf == true){BISYOMYcNf = false;}
      if(FEoeuHtaWw == true){FEoeuHtaWw = false;}
      if(ytbLePjVwn == true){ytbLePjVwn = false;}
      if(koXFcKsZsV == true){koXFcKsZsV = false;}
      if(WfJquemVld == true){WfJquemVld = false;}
      if(TAqlBGgGsz == true){TAqlBGgGsz = false;}
      if(bCfYtQfjCk == true){bCfYtQfjCk = false;}
      if(OTgBYRkjQA == true){OTgBYRkjQA = false;}
      if(bNjSTkxlDV == true){bNjSTkxlDV = false;}
      if(dmgtsUAjxe == true){dmgtsUAjxe = false;}
      if(yCSBPASpMi == true){yCSBPASpMi = false;}
      if(VwosWORNEI == true){VwosWORNEI = false;}
      if(StfgGammHD == true){StfgGammHD = false;}
      if(RAmkBZtiCT == true){RAmkBZtiCT = false;}
      if(SGYUAgxnWe == true){SGYUAgxnWe = false;}
      if(ClenLDVltn == true){ClenLDVltn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BRKXDXLQMD
{ 
  void OPDuZshxto()
  { 
      bool JymszWpjqm = false;
      bool FsDSagPQXH = false;
      bool dDkVDapUts = false;
      bool RVNOyfdfOD = false;
      bool lBxQyTpkUl = false;
      bool jISgUGNQpY = false;
      bool fVoxVienTt = false;
      bool CjCUUcFTXi = false;
      bool jEzIJIDgtq = false;
      bool SNooWPLAuO = false;
      bool oBRajAGxLr = false;
      bool BssHnbWgnM = false;
      bool fxtbbotMxF = false;
      bool QFYItimXXI = false;
      bool CFVBpYThBu = false;
      bool seMhhqHozu = false;
      bool FsAGauUjNF = false;
      bool oyIeJabrlD = false;
      bool UMLCLlspZC = false;
      bool axYcCJFOat = false;
      string eTfLcSSdqB;
      string cbsLFbbHQN;
      string eTJyeXjciO;
      string EOzYXcunoh;
      string fUGQosqgNG;
      string RqwVeLKhfF;
      string iotbwOcUnb;
      string gnShgKMsJk;
      string fDPbwNScsL;
      string SMIizpZdTZ;
      string QWrkZdXNoU;
      string yQYtZeYSfi;
      string uzabJTeiiq;
      string jiYiUIKeCR;
      string oEnYNBnNJT;
      string QHykeQuQaF;
      string yoexjOqoZQ;
      string UtQNtqLCNI;
      string eRYOZcknED;
      string NsDwSAYpny;
      if(eTfLcSSdqB == QWrkZdXNoU){JymszWpjqm = true;}
      else if(QWrkZdXNoU == eTfLcSSdqB){oBRajAGxLr = true;}
      if(cbsLFbbHQN == yQYtZeYSfi){FsDSagPQXH = true;}
      else if(yQYtZeYSfi == cbsLFbbHQN){BssHnbWgnM = true;}
      if(eTJyeXjciO == uzabJTeiiq){dDkVDapUts = true;}
      else if(uzabJTeiiq == eTJyeXjciO){fxtbbotMxF = true;}
      if(EOzYXcunoh == jiYiUIKeCR){RVNOyfdfOD = true;}
      else if(jiYiUIKeCR == EOzYXcunoh){QFYItimXXI = true;}
      if(fUGQosqgNG == oEnYNBnNJT){lBxQyTpkUl = true;}
      else if(oEnYNBnNJT == fUGQosqgNG){CFVBpYThBu = true;}
      if(RqwVeLKhfF == QHykeQuQaF){jISgUGNQpY = true;}
      else if(QHykeQuQaF == RqwVeLKhfF){seMhhqHozu = true;}
      if(iotbwOcUnb == yoexjOqoZQ){fVoxVienTt = true;}
      else if(yoexjOqoZQ == iotbwOcUnb){FsAGauUjNF = true;}
      if(gnShgKMsJk == UtQNtqLCNI){CjCUUcFTXi = true;}
      if(fDPbwNScsL == eRYOZcknED){jEzIJIDgtq = true;}
      if(SMIizpZdTZ == NsDwSAYpny){SNooWPLAuO = true;}
      while(UtQNtqLCNI == gnShgKMsJk){oyIeJabrlD = true;}
      while(eRYOZcknED == eRYOZcknED){UMLCLlspZC = true;}
      while(NsDwSAYpny == NsDwSAYpny){axYcCJFOat = true;}
      if(JymszWpjqm == true){JymszWpjqm = false;}
      if(FsDSagPQXH == true){FsDSagPQXH = false;}
      if(dDkVDapUts == true){dDkVDapUts = false;}
      if(RVNOyfdfOD == true){RVNOyfdfOD = false;}
      if(lBxQyTpkUl == true){lBxQyTpkUl = false;}
      if(jISgUGNQpY == true){jISgUGNQpY = false;}
      if(fVoxVienTt == true){fVoxVienTt = false;}
      if(CjCUUcFTXi == true){CjCUUcFTXi = false;}
      if(jEzIJIDgtq == true){jEzIJIDgtq = false;}
      if(SNooWPLAuO == true){SNooWPLAuO = false;}
      if(oBRajAGxLr == true){oBRajAGxLr = false;}
      if(BssHnbWgnM == true){BssHnbWgnM = false;}
      if(fxtbbotMxF == true){fxtbbotMxF = false;}
      if(QFYItimXXI == true){QFYItimXXI = false;}
      if(CFVBpYThBu == true){CFVBpYThBu = false;}
      if(seMhhqHozu == true){seMhhqHozu = false;}
      if(FsAGauUjNF == true){FsAGauUjNF = false;}
      if(oyIeJabrlD == true){oyIeJabrlD = false;}
      if(UMLCLlspZC == true){UMLCLlspZC = false;}
      if(axYcCJFOat == true){axYcCJFOat = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IZANUJSRRE
{ 
  void nuiiEyfrVy()
  { 
      bool wLLyIcsUet = false;
      bool mLUUKxClqS = false;
      bool VHgsNSRdpt = false;
      bool xHXEEwWTZj = false;
      bool YjAJtJYUcn = false;
      bool hJGqUoeSkp = false;
      bool KPejwfnPQN = false;
      bool ZiLHtkGXyD = false;
      bool sxBBMmBfiP = false;
      bool RDhiYIFPMO = false;
      bool VIEONyxywj = false;
      bool hGUhwNNcWJ = false;
      bool dIfBuVAbik = false;
      bool fqLihkrlmN = false;
      bool oCizgLiAmK = false;
      bool ubrDkNbDSq = false;
      bool yUPLDqukzL = false;
      bool VapJTbYfTj = false;
      bool mzoXpEyIyU = false;
      bool IoSuPTlXwp = false;
      string RBEFiwConm;
      string KXUbTYUAFy;
      string uuolgxgQkb;
      string cKNhRYrMSI;
      string rkCEwIKozF;
      string JCVJYVMRYl;
      string OlDLJzKmJu;
      string fIhxGKrjoX;
      string mqQfSZoEJu;
      string LZmgsGhptx;
      string yWfEYBUYDN;
      string cccAzXUWsj;
      string JFdOiGUADz;
      string cCpqZPLLGR;
      string EQBuRixlhU;
      string lKxKmrsRVS;
      string fUUDkamkai;
      string MIQbesEhwA;
      string IiShMRFfDh;
      string VtpmkjwxKq;
      if(RBEFiwConm == yWfEYBUYDN){wLLyIcsUet = true;}
      else if(yWfEYBUYDN == RBEFiwConm){VIEONyxywj = true;}
      if(KXUbTYUAFy == cccAzXUWsj){mLUUKxClqS = true;}
      else if(cccAzXUWsj == KXUbTYUAFy){hGUhwNNcWJ = true;}
      if(uuolgxgQkb == JFdOiGUADz){VHgsNSRdpt = true;}
      else if(JFdOiGUADz == uuolgxgQkb){dIfBuVAbik = true;}
      if(cKNhRYrMSI == cCpqZPLLGR){xHXEEwWTZj = true;}
      else if(cCpqZPLLGR == cKNhRYrMSI){fqLihkrlmN = true;}
      if(rkCEwIKozF == EQBuRixlhU){YjAJtJYUcn = true;}
      else if(EQBuRixlhU == rkCEwIKozF){oCizgLiAmK = true;}
      if(JCVJYVMRYl == lKxKmrsRVS){hJGqUoeSkp = true;}
      else if(lKxKmrsRVS == JCVJYVMRYl){ubrDkNbDSq = true;}
      if(OlDLJzKmJu == fUUDkamkai){KPejwfnPQN = true;}
      else if(fUUDkamkai == OlDLJzKmJu){yUPLDqukzL = true;}
      if(fIhxGKrjoX == MIQbesEhwA){ZiLHtkGXyD = true;}
      if(mqQfSZoEJu == IiShMRFfDh){sxBBMmBfiP = true;}
      if(LZmgsGhptx == VtpmkjwxKq){RDhiYIFPMO = true;}
      while(MIQbesEhwA == fIhxGKrjoX){VapJTbYfTj = true;}
      while(IiShMRFfDh == IiShMRFfDh){mzoXpEyIyU = true;}
      while(VtpmkjwxKq == VtpmkjwxKq){IoSuPTlXwp = true;}
      if(wLLyIcsUet == true){wLLyIcsUet = false;}
      if(mLUUKxClqS == true){mLUUKxClqS = false;}
      if(VHgsNSRdpt == true){VHgsNSRdpt = false;}
      if(xHXEEwWTZj == true){xHXEEwWTZj = false;}
      if(YjAJtJYUcn == true){YjAJtJYUcn = false;}
      if(hJGqUoeSkp == true){hJGqUoeSkp = false;}
      if(KPejwfnPQN == true){KPejwfnPQN = false;}
      if(ZiLHtkGXyD == true){ZiLHtkGXyD = false;}
      if(sxBBMmBfiP == true){sxBBMmBfiP = false;}
      if(RDhiYIFPMO == true){RDhiYIFPMO = false;}
      if(VIEONyxywj == true){VIEONyxywj = false;}
      if(hGUhwNNcWJ == true){hGUhwNNcWJ = false;}
      if(dIfBuVAbik == true){dIfBuVAbik = false;}
      if(fqLihkrlmN == true){fqLihkrlmN = false;}
      if(oCizgLiAmK == true){oCizgLiAmK = false;}
      if(ubrDkNbDSq == true){ubrDkNbDSq = false;}
      if(yUPLDqukzL == true){yUPLDqukzL = false;}
      if(VapJTbYfTj == true){VapJTbYfTj = false;}
      if(mzoXpEyIyU == true){mzoXpEyIyU = false;}
      if(IoSuPTlXwp == true){IoSuPTlXwp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YVWARRUIGH
{ 
  void WfaeekkDkl()
  { 
      bool rjKPtpJrQI = false;
      bool WwsEJAzjMO = false;
      bool qWBlbnbHgJ = false;
      bool WgkytcQNcy = false;
      bool BELROleppC = false;
      bool WrWNyUiXnG = false;
      bool OCLHkpKuJf = false;
      bool ilHONlKiXp = false;
      bool JkQdldJWzY = false;
      bool ssYVjzsEgY = false;
      bool aigJTjjHAL = false;
      bool KzAyxckgUG = false;
      bool fmujmpMleO = false;
      bool sGCyOZEGKC = false;
      bool tCWmOtraYG = false;
      bool NLiZrmnwWc = false;
      bool WyblSDxBiW = false;
      bool XeWSMcQHUr = false;
      bool ykMYAgXcGa = false;
      bool lHigewZkUL = false;
      string WLCFaczJVC;
      string RztgqBhZuJ;
      string PokUsIIfLq;
      string rLKaYrErtr;
      string nrWkwdqFWs;
      string aLoXXgZhMS;
      string TSxeKFoSIy;
      string woeDVWRAXO;
      string QCJSPfWmDq;
      string SWfbYUurap;
      string oYxXwkglBB;
      string OZJxBRIdOd;
      string iBPQfZJDdA;
      string bZYhYqElWe;
      string zjkBcsMhZH;
      string MQcwHmJgqW;
      string bcHBYnAbXJ;
      string MWHjezQNmm;
      string NacWnKxcal;
      string hXtADVbjbo;
      if(WLCFaczJVC == oYxXwkglBB){rjKPtpJrQI = true;}
      else if(oYxXwkglBB == WLCFaczJVC){aigJTjjHAL = true;}
      if(RztgqBhZuJ == OZJxBRIdOd){WwsEJAzjMO = true;}
      else if(OZJxBRIdOd == RztgqBhZuJ){KzAyxckgUG = true;}
      if(PokUsIIfLq == iBPQfZJDdA){qWBlbnbHgJ = true;}
      else if(iBPQfZJDdA == PokUsIIfLq){fmujmpMleO = true;}
      if(rLKaYrErtr == bZYhYqElWe){WgkytcQNcy = true;}
      else if(bZYhYqElWe == rLKaYrErtr){sGCyOZEGKC = true;}
      if(nrWkwdqFWs == zjkBcsMhZH){BELROleppC = true;}
      else if(zjkBcsMhZH == nrWkwdqFWs){tCWmOtraYG = true;}
      if(aLoXXgZhMS == MQcwHmJgqW){WrWNyUiXnG = true;}
      else if(MQcwHmJgqW == aLoXXgZhMS){NLiZrmnwWc = true;}
      if(TSxeKFoSIy == bcHBYnAbXJ){OCLHkpKuJf = true;}
      else if(bcHBYnAbXJ == TSxeKFoSIy){WyblSDxBiW = true;}
      if(woeDVWRAXO == MWHjezQNmm){ilHONlKiXp = true;}
      if(QCJSPfWmDq == NacWnKxcal){JkQdldJWzY = true;}
      if(SWfbYUurap == hXtADVbjbo){ssYVjzsEgY = true;}
      while(MWHjezQNmm == woeDVWRAXO){XeWSMcQHUr = true;}
      while(NacWnKxcal == NacWnKxcal){ykMYAgXcGa = true;}
      while(hXtADVbjbo == hXtADVbjbo){lHigewZkUL = true;}
      if(rjKPtpJrQI == true){rjKPtpJrQI = false;}
      if(WwsEJAzjMO == true){WwsEJAzjMO = false;}
      if(qWBlbnbHgJ == true){qWBlbnbHgJ = false;}
      if(WgkytcQNcy == true){WgkytcQNcy = false;}
      if(BELROleppC == true){BELROleppC = false;}
      if(WrWNyUiXnG == true){WrWNyUiXnG = false;}
      if(OCLHkpKuJf == true){OCLHkpKuJf = false;}
      if(ilHONlKiXp == true){ilHONlKiXp = false;}
      if(JkQdldJWzY == true){JkQdldJWzY = false;}
      if(ssYVjzsEgY == true){ssYVjzsEgY = false;}
      if(aigJTjjHAL == true){aigJTjjHAL = false;}
      if(KzAyxckgUG == true){KzAyxckgUG = false;}
      if(fmujmpMleO == true){fmujmpMleO = false;}
      if(sGCyOZEGKC == true){sGCyOZEGKC = false;}
      if(tCWmOtraYG == true){tCWmOtraYG = false;}
      if(NLiZrmnwWc == true){NLiZrmnwWc = false;}
      if(WyblSDxBiW == true){WyblSDxBiW = false;}
      if(XeWSMcQHUr == true){XeWSMcQHUr = false;}
      if(ykMYAgXcGa == true){ykMYAgXcGa = false;}
      if(lHigewZkUL == true){lHigewZkUL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPKVHCJRRK
{ 
  void WFXHoRJgly()
  { 
      bool amognbqlEu = false;
      bool VeosbVrLrd = false;
      bool VpVSVTwfVa = false;
      bool blTeJWHnAf = false;
      bool loxMzbdALZ = false;
      bool QdAeqkRWLT = false;
      bool eLQcSiLKjE = false;
      bool NELMrgrJSs = false;
      bool owTuKylnnX = false;
      bool FkbfAZYTsQ = false;
      bool PTQHMLRnmK = false;
      bool rIDReiqURU = false;
      bool xWVLybbeLR = false;
      bool HYPBdUfMiy = false;
      bool fyBdexgJBR = false;
      bool iDCYTryEIj = false;
      bool jmbUCTrBnJ = false;
      bool DdkSoyVrfB = false;
      bool tRdtiDWqhk = false;
      bool WaDzOsVgaL = false;
      string NSJcXhBeyL;
      string NCIJStKkUC;
      string ibBWUSIkwM;
      string oAFDVQCwFo;
      string unRQhXEWhG;
      string GYtiqkQmIE;
      string ZPikVMwEmC;
      string rNfeGtKjox;
      string NkDoGPFWMk;
      string zPnAPeFgtU;
      string azjfOrsPbw;
      string agyKqnMsdG;
      string HZrCCbZePa;
      string odoUWOBWZN;
      string WptPJSRcJa;
      string SLCnMBHgcl;
      string SNABHxqdnb;
      string mpTQjRebrj;
      string KxVnIdaBHV;
      string GTsmuIosIM;
      if(NSJcXhBeyL == azjfOrsPbw){amognbqlEu = true;}
      else if(azjfOrsPbw == NSJcXhBeyL){PTQHMLRnmK = true;}
      if(NCIJStKkUC == agyKqnMsdG){VeosbVrLrd = true;}
      else if(agyKqnMsdG == NCIJStKkUC){rIDReiqURU = true;}
      if(ibBWUSIkwM == HZrCCbZePa){VpVSVTwfVa = true;}
      else if(HZrCCbZePa == ibBWUSIkwM){xWVLybbeLR = true;}
      if(oAFDVQCwFo == odoUWOBWZN){blTeJWHnAf = true;}
      else if(odoUWOBWZN == oAFDVQCwFo){HYPBdUfMiy = true;}
      if(unRQhXEWhG == WptPJSRcJa){loxMzbdALZ = true;}
      else if(WptPJSRcJa == unRQhXEWhG){fyBdexgJBR = true;}
      if(GYtiqkQmIE == SLCnMBHgcl){QdAeqkRWLT = true;}
      else if(SLCnMBHgcl == GYtiqkQmIE){iDCYTryEIj = true;}
      if(ZPikVMwEmC == SNABHxqdnb){eLQcSiLKjE = true;}
      else if(SNABHxqdnb == ZPikVMwEmC){jmbUCTrBnJ = true;}
      if(rNfeGtKjox == mpTQjRebrj){NELMrgrJSs = true;}
      if(NkDoGPFWMk == KxVnIdaBHV){owTuKylnnX = true;}
      if(zPnAPeFgtU == GTsmuIosIM){FkbfAZYTsQ = true;}
      while(mpTQjRebrj == rNfeGtKjox){DdkSoyVrfB = true;}
      while(KxVnIdaBHV == KxVnIdaBHV){tRdtiDWqhk = true;}
      while(GTsmuIosIM == GTsmuIosIM){WaDzOsVgaL = true;}
      if(amognbqlEu == true){amognbqlEu = false;}
      if(VeosbVrLrd == true){VeosbVrLrd = false;}
      if(VpVSVTwfVa == true){VpVSVTwfVa = false;}
      if(blTeJWHnAf == true){blTeJWHnAf = false;}
      if(loxMzbdALZ == true){loxMzbdALZ = false;}
      if(QdAeqkRWLT == true){QdAeqkRWLT = false;}
      if(eLQcSiLKjE == true){eLQcSiLKjE = false;}
      if(NELMrgrJSs == true){NELMrgrJSs = false;}
      if(owTuKylnnX == true){owTuKylnnX = false;}
      if(FkbfAZYTsQ == true){FkbfAZYTsQ = false;}
      if(PTQHMLRnmK == true){PTQHMLRnmK = false;}
      if(rIDReiqURU == true){rIDReiqURU = false;}
      if(xWVLybbeLR == true){xWVLybbeLR = false;}
      if(HYPBdUfMiy == true){HYPBdUfMiy = false;}
      if(fyBdexgJBR == true){fyBdexgJBR = false;}
      if(iDCYTryEIj == true){iDCYTryEIj = false;}
      if(jmbUCTrBnJ == true){jmbUCTrBnJ = false;}
      if(DdkSoyVrfB == true){DdkSoyVrfB = false;}
      if(tRdtiDWqhk == true){tRdtiDWqhk = false;}
      if(WaDzOsVgaL == true){WaDzOsVgaL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RPWMOWJYED
{ 
  void yosZVFSnLO()
  { 
      bool ThZYQXNEeN = false;
      bool nGAtMlMYfx = false;
      bool zTpmLTHTVW = false;
      bool suQguOQASp = false;
      bool lIjLUyHWQR = false;
      bool YHPJzzqmMx = false;
      bool QtiHUroSzy = false;
      bool VLFpLqidSN = false;
      bool MkCDyleGgu = false;
      bool WdnVZrYcqb = false;
      bool InWSwMBZyH = false;
      bool QNUzjfqfIi = false;
      bool MilEarXjPT = false;
      bool SGmpEYNjGl = false;
      bool jFHYeJJnkt = false;
      bool ArTIOZCSqE = false;
      bool oRJdoJZdtL = false;
      bool RGYWyHaMYQ = false;
      bool hiyVSZmebe = false;
      bool WtrBxSwcjU = false;
      string brAhlefpNg;
      string toUIrmPlbG;
      string asnIttzdPi;
      string dCKbyoRtho;
      string yUQUsrBjcY;
      string LFZNNhDqmr;
      string fBaeDqerJC;
      string UUEmIFcTOC;
      string rOBpXXcwNQ;
      string laHoJxtkRC;
      string NIZZDpBmFI;
      string EjckAQAjGe;
      string OhdsQtNOcL;
      string KqBMnioamg;
      string WopFMBxWos;
      string xKelmeegJJ;
      string clJtxMhPwQ;
      string bYxZHYqYgO;
      string wqZjOzMOZI;
      string EHRcEkfwHz;
      if(brAhlefpNg == NIZZDpBmFI){ThZYQXNEeN = true;}
      else if(NIZZDpBmFI == brAhlefpNg){InWSwMBZyH = true;}
      if(toUIrmPlbG == EjckAQAjGe){nGAtMlMYfx = true;}
      else if(EjckAQAjGe == toUIrmPlbG){QNUzjfqfIi = true;}
      if(asnIttzdPi == OhdsQtNOcL){zTpmLTHTVW = true;}
      else if(OhdsQtNOcL == asnIttzdPi){MilEarXjPT = true;}
      if(dCKbyoRtho == KqBMnioamg){suQguOQASp = true;}
      else if(KqBMnioamg == dCKbyoRtho){SGmpEYNjGl = true;}
      if(yUQUsrBjcY == WopFMBxWos){lIjLUyHWQR = true;}
      else if(WopFMBxWos == yUQUsrBjcY){jFHYeJJnkt = true;}
      if(LFZNNhDqmr == xKelmeegJJ){YHPJzzqmMx = true;}
      else if(xKelmeegJJ == LFZNNhDqmr){ArTIOZCSqE = true;}
      if(fBaeDqerJC == clJtxMhPwQ){QtiHUroSzy = true;}
      else if(clJtxMhPwQ == fBaeDqerJC){oRJdoJZdtL = true;}
      if(UUEmIFcTOC == bYxZHYqYgO){VLFpLqidSN = true;}
      if(rOBpXXcwNQ == wqZjOzMOZI){MkCDyleGgu = true;}
      if(laHoJxtkRC == EHRcEkfwHz){WdnVZrYcqb = true;}
      while(bYxZHYqYgO == UUEmIFcTOC){RGYWyHaMYQ = true;}
      while(wqZjOzMOZI == wqZjOzMOZI){hiyVSZmebe = true;}
      while(EHRcEkfwHz == EHRcEkfwHz){WtrBxSwcjU = true;}
      if(ThZYQXNEeN == true){ThZYQXNEeN = false;}
      if(nGAtMlMYfx == true){nGAtMlMYfx = false;}
      if(zTpmLTHTVW == true){zTpmLTHTVW = false;}
      if(suQguOQASp == true){suQguOQASp = false;}
      if(lIjLUyHWQR == true){lIjLUyHWQR = false;}
      if(YHPJzzqmMx == true){YHPJzzqmMx = false;}
      if(QtiHUroSzy == true){QtiHUroSzy = false;}
      if(VLFpLqidSN == true){VLFpLqidSN = false;}
      if(MkCDyleGgu == true){MkCDyleGgu = false;}
      if(WdnVZrYcqb == true){WdnVZrYcqb = false;}
      if(InWSwMBZyH == true){InWSwMBZyH = false;}
      if(QNUzjfqfIi == true){QNUzjfqfIi = false;}
      if(MilEarXjPT == true){MilEarXjPT = false;}
      if(SGmpEYNjGl == true){SGmpEYNjGl = false;}
      if(jFHYeJJnkt == true){jFHYeJJnkt = false;}
      if(ArTIOZCSqE == true){ArTIOZCSqE = false;}
      if(oRJdoJZdtL == true){oRJdoJZdtL = false;}
      if(RGYWyHaMYQ == true){RGYWyHaMYQ = false;}
      if(hiyVSZmebe == true){hiyVSZmebe = false;}
      if(WtrBxSwcjU == true){WtrBxSwcjU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GMNSQVUZGP
{ 
  void trgTVhOTNJ()
  { 
      bool szuKnMZGYN = false;
      bool erQMNAkphx = false;
      bool nUsKTqbegW = false;
      bool zYZfamEIjk = false;
      bool uypBChreHg = false;
      bool UMspgXFjqw = false;
      bool juZBOFSjlZ = false;
      bool wbFwBodrHk = false;
      bool zxWzBmfjzC = false;
      bool hTQnAAYolw = false;
      bool PHrhjrGxnq = false;
      bool tMcFxmYZzb = false;
      bool ZhkjqcKRuB = false;
      bool QoGLUqFnPI = false;
      bool fhwHIUpLpN = false;
      bool bzoJVgWIqH = false;
      bool goBmaFGRjG = false;
      bool gjKqwrldaW = false;
      bool lzahYQAwon = false;
      bool UxxHapgIgD = false;
      string fbCVudDxEo;
      string GNJoQqfSha;
      string aWSCPOqIIn;
      string RxlXqnxzNE;
      string UjfMpOJgGp;
      string SgFSEJIAGg;
      string munPXJalyb;
      string sfFdGqpGLA;
      string EKCSUkqTSh;
      string exsgQZuQng;
      string mXidwmbaMN;
      string SCnFbbrVul;
      string RHSQxwmXMf;
      string uZReNgbYVg;
      string JQHFOcImFn;
      string gZUCPeFSgA;
      string ADNfSsjJrt;
      string ATzNcBAMBT;
      string mzSXyUFPPh;
      string aJqUgFCamU;
      if(fbCVudDxEo == mXidwmbaMN){szuKnMZGYN = true;}
      else if(mXidwmbaMN == fbCVudDxEo){PHrhjrGxnq = true;}
      if(GNJoQqfSha == SCnFbbrVul){erQMNAkphx = true;}
      else if(SCnFbbrVul == GNJoQqfSha){tMcFxmYZzb = true;}
      if(aWSCPOqIIn == RHSQxwmXMf){nUsKTqbegW = true;}
      else if(RHSQxwmXMf == aWSCPOqIIn){ZhkjqcKRuB = true;}
      if(RxlXqnxzNE == uZReNgbYVg){zYZfamEIjk = true;}
      else if(uZReNgbYVg == RxlXqnxzNE){QoGLUqFnPI = true;}
      if(UjfMpOJgGp == JQHFOcImFn){uypBChreHg = true;}
      else if(JQHFOcImFn == UjfMpOJgGp){fhwHIUpLpN = true;}
      if(SgFSEJIAGg == gZUCPeFSgA){UMspgXFjqw = true;}
      else if(gZUCPeFSgA == SgFSEJIAGg){bzoJVgWIqH = true;}
      if(munPXJalyb == ADNfSsjJrt){juZBOFSjlZ = true;}
      else if(ADNfSsjJrt == munPXJalyb){goBmaFGRjG = true;}
      if(sfFdGqpGLA == ATzNcBAMBT){wbFwBodrHk = true;}
      if(EKCSUkqTSh == mzSXyUFPPh){zxWzBmfjzC = true;}
      if(exsgQZuQng == aJqUgFCamU){hTQnAAYolw = true;}
      while(ATzNcBAMBT == sfFdGqpGLA){gjKqwrldaW = true;}
      while(mzSXyUFPPh == mzSXyUFPPh){lzahYQAwon = true;}
      while(aJqUgFCamU == aJqUgFCamU){UxxHapgIgD = true;}
      if(szuKnMZGYN == true){szuKnMZGYN = false;}
      if(erQMNAkphx == true){erQMNAkphx = false;}
      if(nUsKTqbegW == true){nUsKTqbegW = false;}
      if(zYZfamEIjk == true){zYZfamEIjk = false;}
      if(uypBChreHg == true){uypBChreHg = false;}
      if(UMspgXFjqw == true){UMspgXFjqw = false;}
      if(juZBOFSjlZ == true){juZBOFSjlZ = false;}
      if(wbFwBodrHk == true){wbFwBodrHk = false;}
      if(zxWzBmfjzC == true){zxWzBmfjzC = false;}
      if(hTQnAAYolw == true){hTQnAAYolw = false;}
      if(PHrhjrGxnq == true){PHrhjrGxnq = false;}
      if(tMcFxmYZzb == true){tMcFxmYZzb = false;}
      if(ZhkjqcKRuB == true){ZhkjqcKRuB = false;}
      if(QoGLUqFnPI == true){QoGLUqFnPI = false;}
      if(fhwHIUpLpN == true){fhwHIUpLpN = false;}
      if(bzoJVgWIqH == true){bzoJVgWIqH = false;}
      if(goBmaFGRjG == true){goBmaFGRjG = false;}
      if(gjKqwrldaW == true){gjKqwrldaW = false;}
      if(lzahYQAwon == true){lzahYQAwon = false;}
      if(UxxHapgIgD == true){UxxHapgIgD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BVAJBNFIBS
{ 
  void HhkJZdIFiC()
  { 
      bool OwPFfLZPyg = false;
      bool dooHCpDlBx = false;
      bool VaUYVdrhuk = false;
      bool AiSpdiDyjr = false;
      bool YIYKptKjKC = false;
      bool IETZEmbpjC = false;
      bool TqUMguWzcS = false;
      bool mECIXNBJia = false;
      bool SIXrcwOslp = false;
      bool HNOgYhmMdt = false;
      bool XLGqPDCKBq = false;
      bool kRGIjLTcjj = false;
      bool gcMmLYpUip = false;
      bool ZoeoDGBgbY = false;
      bool tDquFoHGwN = false;
      bool NKbtMtzSfq = false;
      bool NgaKQwmQEc = false;
      bool JmALpclQgV = false;
      bool QiYVbOMkbJ = false;
      bool HiAkKNbfdJ = false;
      string GXxFFLJqta;
      string fSXYZaCzGK;
      string IGRqqhYmcL;
      string MYGfsmtTDh;
      string pafeQaeYqG;
      string VTBZxzGFNX;
      string lVOhNHMqfl;
      string fiuXTgalaQ;
      string CAwWpsWgis;
      string goGfwUMxRJ;
      string NmsFZlXdFP;
      string YTewUkZqrT;
      string jeIlFqcPaz;
      string TdURDOHpwD;
      string VsaSUMKJKK;
      string tUExYheGzi;
      string JICFwtyNsF;
      string diunyqEoQr;
      string fSEQEyYXrU;
      string jAqMsMpUWZ;
      if(GXxFFLJqta == NmsFZlXdFP){OwPFfLZPyg = true;}
      else if(NmsFZlXdFP == GXxFFLJqta){XLGqPDCKBq = true;}
      if(fSXYZaCzGK == YTewUkZqrT){dooHCpDlBx = true;}
      else if(YTewUkZqrT == fSXYZaCzGK){kRGIjLTcjj = true;}
      if(IGRqqhYmcL == jeIlFqcPaz){VaUYVdrhuk = true;}
      else if(jeIlFqcPaz == IGRqqhYmcL){gcMmLYpUip = true;}
      if(MYGfsmtTDh == TdURDOHpwD){AiSpdiDyjr = true;}
      else if(TdURDOHpwD == MYGfsmtTDh){ZoeoDGBgbY = true;}
      if(pafeQaeYqG == VsaSUMKJKK){YIYKptKjKC = true;}
      else if(VsaSUMKJKK == pafeQaeYqG){tDquFoHGwN = true;}
      if(VTBZxzGFNX == tUExYheGzi){IETZEmbpjC = true;}
      else if(tUExYheGzi == VTBZxzGFNX){NKbtMtzSfq = true;}
      if(lVOhNHMqfl == JICFwtyNsF){TqUMguWzcS = true;}
      else if(JICFwtyNsF == lVOhNHMqfl){NgaKQwmQEc = true;}
      if(fiuXTgalaQ == diunyqEoQr){mECIXNBJia = true;}
      if(CAwWpsWgis == fSEQEyYXrU){SIXrcwOslp = true;}
      if(goGfwUMxRJ == jAqMsMpUWZ){HNOgYhmMdt = true;}
      while(diunyqEoQr == fiuXTgalaQ){JmALpclQgV = true;}
      while(fSEQEyYXrU == fSEQEyYXrU){QiYVbOMkbJ = true;}
      while(jAqMsMpUWZ == jAqMsMpUWZ){HiAkKNbfdJ = true;}
      if(OwPFfLZPyg == true){OwPFfLZPyg = false;}
      if(dooHCpDlBx == true){dooHCpDlBx = false;}
      if(VaUYVdrhuk == true){VaUYVdrhuk = false;}
      if(AiSpdiDyjr == true){AiSpdiDyjr = false;}
      if(YIYKptKjKC == true){YIYKptKjKC = false;}
      if(IETZEmbpjC == true){IETZEmbpjC = false;}
      if(TqUMguWzcS == true){TqUMguWzcS = false;}
      if(mECIXNBJia == true){mECIXNBJia = false;}
      if(SIXrcwOslp == true){SIXrcwOslp = false;}
      if(HNOgYhmMdt == true){HNOgYhmMdt = false;}
      if(XLGqPDCKBq == true){XLGqPDCKBq = false;}
      if(kRGIjLTcjj == true){kRGIjLTcjj = false;}
      if(gcMmLYpUip == true){gcMmLYpUip = false;}
      if(ZoeoDGBgbY == true){ZoeoDGBgbY = false;}
      if(tDquFoHGwN == true){tDquFoHGwN = false;}
      if(NKbtMtzSfq == true){NKbtMtzSfq = false;}
      if(NgaKQwmQEc == true){NgaKQwmQEc = false;}
      if(JmALpclQgV == true){JmALpclQgV = false;}
      if(QiYVbOMkbJ == true){QiYVbOMkbJ = false;}
      if(HiAkKNbfdJ == true){HiAkKNbfdJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CSALOIEISF
{ 
  void OHwIDakRNH()
  { 
      bool KJIaEugoJh = false;
      bool JWuHKcogBb = false;
      bool gYQFKYCnJK = false;
      bool eDgjbmSqjQ = false;
      bool KyPAYEnyaJ = false;
      bool tKxwilsDPe = false;
      bool ssfzDFoLfX = false;
      bool JxxkRhIPgG = false;
      bool kDNAPTFkAo = false;
      bool sPbEWQSQxS = false;
      bool ObSCzxNMdA = false;
      bool ccWItpeeii = false;
      bool AEKqetUsNB = false;
      bool PrSNqIkLBS = false;
      bool GsHALPsSJg = false;
      bool lmhNSKRbXE = false;
      bool cUycjkKIRl = false;
      bool FTdQcGwKeO = false;
      bool BBigPcKEuf = false;
      bool qInwoltePZ = false;
      string hSzTrCOFWT;
      string ZONlPSsTAq;
      string dnXiMRDPbJ;
      string EHDEXgNmgy;
      string MDnEHnksYT;
      string laXJstuQHZ;
      string yzcMOSKJNh;
      string EGmBdZASbX;
      string gKqIXditLd;
      string lxfGAMaaon;
      string caepOemVfS;
      string sbnismITok;
      string iQyjwGZfBQ;
      string zYdntFeAsr;
      string pMNrjJJxNM;
      string EHlEEMcutH;
      string FGUOTTyznm;
      string IIZwtWCFzl;
      string wbRnMqmZih;
      string biGlliqzXP;
      if(hSzTrCOFWT == caepOemVfS){KJIaEugoJh = true;}
      else if(caepOemVfS == hSzTrCOFWT){ObSCzxNMdA = true;}
      if(ZONlPSsTAq == sbnismITok){JWuHKcogBb = true;}
      else if(sbnismITok == ZONlPSsTAq){ccWItpeeii = true;}
      if(dnXiMRDPbJ == iQyjwGZfBQ){gYQFKYCnJK = true;}
      else if(iQyjwGZfBQ == dnXiMRDPbJ){AEKqetUsNB = true;}
      if(EHDEXgNmgy == zYdntFeAsr){eDgjbmSqjQ = true;}
      else if(zYdntFeAsr == EHDEXgNmgy){PrSNqIkLBS = true;}
      if(MDnEHnksYT == pMNrjJJxNM){KyPAYEnyaJ = true;}
      else if(pMNrjJJxNM == MDnEHnksYT){GsHALPsSJg = true;}
      if(laXJstuQHZ == EHlEEMcutH){tKxwilsDPe = true;}
      else if(EHlEEMcutH == laXJstuQHZ){lmhNSKRbXE = true;}
      if(yzcMOSKJNh == FGUOTTyznm){ssfzDFoLfX = true;}
      else if(FGUOTTyznm == yzcMOSKJNh){cUycjkKIRl = true;}
      if(EGmBdZASbX == IIZwtWCFzl){JxxkRhIPgG = true;}
      if(gKqIXditLd == wbRnMqmZih){kDNAPTFkAo = true;}
      if(lxfGAMaaon == biGlliqzXP){sPbEWQSQxS = true;}
      while(IIZwtWCFzl == EGmBdZASbX){FTdQcGwKeO = true;}
      while(wbRnMqmZih == wbRnMqmZih){BBigPcKEuf = true;}
      while(biGlliqzXP == biGlliqzXP){qInwoltePZ = true;}
      if(KJIaEugoJh == true){KJIaEugoJh = false;}
      if(JWuHKcogBb == true){JWuHKcogBb = false;}
      if(gYQFKYCnJK == true){gYQFKYCnJK = false;}
      if(eDgjbmSqjQ == true){eDgjbmSqjQ = false;}
      if(KyPAYEnyaJ == true){KyPAYEnyaJ = false;}
      if(tKxwilsDPe == true){tKxwilsDPe = false;}
      if(ssfzDFoLfX == true){ssfzDFoLfX = false;}
      if(JxxkRhIPgG == true){JxxkRhIPgG = false;}
      if(kDNAPTFkAo == true){kDNAPTFkAo = false;}
      if(sPbEWQSQxS == true){sPbEWQSQxS = false;}
      if(ObSCzxNMdA == true){ObSCzxNMdA = false;}
      if(ccWItpeeii == true){ccWItpeeii = false;}
      if(AEKqetUsNB == true){AEKqetUsNB = false;}
      if(PrSNqIkLBS == true){PrSNqIkLBS = false;}
      if(GsHALPsSJg == true){GsHALPsSJg = false;}
      if(lmhNSKRbXE == true){lmhNSKRbXE = false;}
      if(cUycjkKIRl == true){cUycjkKIRl = false;}
      if(FTdQcGwKeO == true){FTdQcGwKeO = false;}
      if(BBigPcKEuf == true){BBigPcKEuf = false;}
      if(qInwoltePZ == true){qInwoltePZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LYHEDPCCUS
{ 
  void IjZwUorktM()
  { 
      bool dXkKwLLlXp = false;
      bool YuhYUckFdt = false;
      bool aTaFZUWeZp = false;
      bool YbEjigxwWE = false;
      bool TFJPrykVse = false;
      bool etGCIJxfjb = false;
      bool ofMgRwpxom = false;
      bool fohZaUKKNa = false;
      bool jAltKdVCbY = false;
      bool jQMuOnsbyu = false;
      bool ImfFzpMfam = false;
      bool zlSIqntRWm = false;
      bool ZmVPDOblKm = false;
      bool aiMRSxUfuU = false;
      bool RpanZxyDEa = false;
      bool saFKUUQPCk = false;
      bool NZUnMQZAot = false;
      bool TOWBVjLgpF = false;
      bool PXhjszcBwx = false;
      bool fEdJGqUlbJ = false;
      string fSahKVsgOq;
      string nnRpxDLkBI;
      string OVAtZmRgZs;
      string olbLoKmoLz;
      string nspuNqaYSB;
      string YDgIeJRgHW;
      string DMGVBCMFBl;
      string QWZBUVfEfh;
      string MsNYUlETgf;
      string rFgnwblUsL;
      string eVXfkBcenJ;
      string dMBYKKygAP;
      string xsYVsKpkFs;
      string iLLTDpVgnS;
      string IYeWBfEHdk;
      string cETdOlwCmZ;
      string LrZtZSBgVT;
      string nQsgGXNBTN;
      string FhGTPergFQ;
      string sTtNHQzkxi;
      if(fSahKVsgOq == eVXfkBcenJ){dXkKwLLlXp = true;}
      else if(eVXfkBcenJ == fSahKVsgOq){ImfFzpMfam = true;}
      if(nnRpxDLkBI == dMBYKKygAP){YuhYUckFdt = true;}
      else if(dMBYKKygAP == nnRpxDLkBI){zlSIqntRWm = true;}
      if(OVAtZmRgZs == xsYVsKpkFs){aTaFZUWeZp = true;}
      else if(xsYVsKpkFs == OVAtZmRgZs){ZmVPDOblKm = true;}
      if(olbLoKmoLz == iLLTDpVgnS){YbEjigxwWE = true;}
      else if(iLLTDpVgnS == olbLoKmoLz){aiMRSxUfuU = true;}
      if(nspuNqaYSB == IYeWBfEHdk){TFJPrykVse = true;}
      else if(IYeWBfEHdk == nspuNqaYSB){RpanZxyDEa = true;}
      if(YDgIeJRgHW == cETdOlwCmZ){etGCIJxfjb = true;}
      else if(cETdOlwCmZ == YDgIeJRgHW){saFKUUQPCk = true;}
      if(DMGVBCMFBl == LrZtZSBgVT){ofMgRwpxom = true;}
      else if(LrZtZSBgVT == DMGVBCMFBl){NZUnMQZAot = true;}
      if(QWZBUVfEfh == nQsgGXNBTN){fohZaUKKNa = true;}
      if(MsNYUlETgf == FhGTPergFQ){jAltKdVCbY = true;}
      if(rFgnwblUsL == sTtNHQzkxi){jQMuOnsbyu = true;}
      while(nQsgGXNBTN == QWZBUVfEfh){TOWBVjLgpF = true;}
      while(FhGTPergFQ == FhGTPergFQ){PXhjszcBwx = true;}
      while(sTtNHQzkxi == sTtNHQzkxi){fEdJGqUlbJ = true;}
      if(dXkKwLLlXp == true){dXkKwLLlXp = false;}
      if(YuhYUckFdt == true){YuhYUckFdt = false;}
      if(aTaFZUWeZp == true){aTaFZUWeZp = false;}
      if(YbEjigxwWE == true){YbEjigxwWE = false;}
      if(TFJPrykVse == true){TFJPrykVse = false;}
      if(etGCIJxfjb == true){etGCIJxfjb = false;}
      if(ofMgRwpxom == true){ofMgRwpxom = false;}
      if(fohZaUKKNa == true){fohZaUKKNa = false;}
      if(jAltKdVCbY == true){jAltKdVCbY = false;}
      if(jQMuOnsbyu == true){jQMuOnsbyu = false;}
      if(ImfFzpMfam == true){ImfFzpMfam = false;}
      if(zlSIqntRWm == true){zlSIqntRWm = false;}
      if(ZmVPDOblKm == true){ZmVPDOblKm = false;}
      if(aiMRSxUfuU == true){aiMRSxUfuU = false;}
      if(RpanZxyDEa == true){RpanZxyDEa = false;}
      if(saFKUUQPCk == true){saFKUUQPCk = false;}
      if(NZUnMQZAot == true){NZUnMQZAot = false;}
      if(TOWBVjLgpF == true){TOWBVjLgpF = false;}
      if(PXhjszcBwx == true){PXhjszcBwx = false;}
      if(fEdJGqUlbJ == true){fEdJGqUlbJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FPCNYKWWQO
{ 
  void RqrRNtuITL()
  { 
      bool kePYSCyMCa = false;
      bool BKWGWfzDlQ = false;
      bool qEUsQzAyOc = false;
      bool nboQtbsNeC = false;
      bool aOLJBaBcyn = false;
      bool DBpNRgJVIS = false;
      bool CzyZlZVFLu = false;
      bool mkXipbrLrp = false;
      bool yXzZZlkazN = false;
      bool RWFLzaQlWa = false;
      bool EuQDBScGXo = false;
      bool oxdSUeAXAz = false;
      bool nuGycPeMiO = false;
      bool KFoQkDGuXH = false;
      bool JeDJYTrmqU = false;
      bool ZslWlJnRak = false;
      bool mQWIdiIMgQ = false;
      bool XEzspJrwZI = false;
      bool XrUOnRTRda = false;
      bool OnUmTrHtfo = false;
      string FjVdElcJcT;
      string FBHhtMyOMk;
      string AGRnmyeZXS;
      string HJaOPnbJCo;
      string xWxQPCNOdE;
      string zPNXKyShqF;
      string HCkKMwZsRG;
      string knMWmcIBXk;
      string kPuSTqwDDQ;
      string VtSwhtklDT;
      string bTwXTKCpjh;
      string oQJFTqHSqU;
      string zWoAkpVPor;
      string qWxEIQTWyI;
      string oGSVbEjMbq;
      string mSuiTFeumc;
      string nlBqpSSFxD;
      string XjThfsDTYf;
      string GImyFYbOjD;
      string lXjVTCEbeI;
      if(FjVdElcJcT == bTwXTKCpjh){kePYSCyMCa = true;}
      else if(bTwXTKCpjh == FjVdElcJcT){EuQDBScGXo = true;}
      if(FBHhtMyOMk == oQJFTqHSqU){BKWGWfzDlQ = true;}
      else if(oQJFTqHSqU == FBHhtMyOMk){oxdSUeAXAz = true;}
      if(AGRnmyeZXS == zWoAkpVPor){qEUsQzAyOc = true;}
      else if(zWoAkpVPor == AGRnmyeZXS){nuGycPeMiO = true;}
      if(HJaOPnbJCo == qWxEIQTWyI){nboQtbsNeC = true;}
      else if(qWxEIQTWyI == HJaOPnbJCo){KFoQkDGuXH = true;}
      if(xWxQPCNOdE == oGSVbEjMbq){aOLJBaBcyn = true;}
      else if(oGSVbEjMbq == xWxQPCNOdE){JeDJYTrmqU = true;}
      if(zPNXKyShqF == mSuiTFeumc){DBpNRgJVIS = true;}
      else if(mSuiTFeumc == zPNXKyShqF){ZslWlJnRak = true;}
      if(HCkKMwZsRG == nlBqpSSFxD){CzyZlZVFLu = true;}
      else if(nlBqpSSFxD == HCkKMwZsRG){mQWIdiIMgQ = true;}
      if(knMWmcIBXk == XjThfsDTYf){mkXipbrLrp = true;}
      if(kPuSTqwDDQ == GImyFYbOjD){yXzZZlkazN = true;}
      if(VtSwhtklDT == lXjVTCEbeI){RWFLzaQlWa = true;}
      while(XjThfsDTYf == knMWmcIBXk){XEzspJrwZI = true;}
      while(GImyFYbOjD == GImyFYbOjD){XrUOnRTRda = true;}
      while(lXjVTCEbeI == lXjVTCEbeI){OnUmTrHtfo = true;}
      if(kePYSCyMCa == true){kePYSCyMCa = false;}
      if(BKWGWfzDlQ == true){BKWGWfzDlQ = false;}
      if(qEUsQzAyOc == true){qEUsQzAyOc = false;}
      if(nboQtbsNeC == true){nboQtbsNeC = false;}
      if(aOLJBaBcyn == true){aOLJBaBcyn = false;}
      if(DBpNRgJVIS == true){DBpNRgJVIS = false;}
      if(CzyZlZVFLu == true){CzyZlZVFLu = false;}
      if(mkXipbrLrp == true){mkXipbrLrp = false;}
      if(yXzZZlkazN == true){yXzZZlkazN = false;}
      if(RWFLzaQlWa == true){RWFLzaQlWa = false;}
      if(EuQDBScGXo == true){EuQDBScGXo = false;}
      if(oxdSUeAXAz == true){oxdSUeAXAz = false;}
      if(nuGycPeMiO == true){nuGycPeMiO = false;}
      if(KFoQkDGuXH == true){KFoQkDGuXH = false;}
      if(JeDJYTrmqU == true){JeDJYTrmqU = false;}
      if(ZslWlJnRak == true){ZslWlJnRak = false;}
      if(mQWIdiIMgQ == true){mQWIdiIMgQ = false;}
      if(XEzspJrwZI == true){XEzspJrwZI = false;}
      if(XrUOnRTRda == true){XrUOnRTRda = false;}
      if(OnUmTrHtfo == true){OnUmTrHtfo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KYJCOCQLAK
{ 
  void MyIErALDEl()
  { 
      bool NUJBIMkFMV = false;
      bool ZDSNEDfriB = false;
      bool EBheBjMKYy = false;
      bool LHzOAUsMyX = false;
      bool XbZLEZUKci = false;
      bool scQhULmdzY = false;
      bool AZfOJSDDMj = false;
      bool KTsKcbbWZa = false;
      bool PBhpEiqRso = false;
      bool gOMYXyuKCl = false;
      bool WQyrXZjFEs = false;
      bool iQDYJyqpJZ = false;
      bool bkJXCuGTmd = false;
      bool fRUnEyDoRe = false;
      bool zkMAFQLnPY = false;
      bool HFBbKkHapc = false;
      bool SPRaMRuOUK = false;
      bool uBYeapYJRl = false;
      bool jSEOWaPrdS = false;
      bool qbznLiTlmm = false;
      string LZmInLxofQ;
      string krqnwcmatm;
      string xJSAUMwQYH;
      string TcwXuTUcDK;
      string RNrWMChyVc;
      string mMVYgBGlma;
      string OgPXxIwSsc;
      string IKXiVjRwnR;
      string eytwUHGWpt;
      string MhocwkxTZE;
      string GOFsUbnlDx;
      string iKyVuPlTDp;
      string BZbyQZVtmj;
      string lxViLPsBbr;
      string STSsKCjTgf;
      string ycQjCglGbt;
      string GszTKknOJe;
      string WkrKWgGinO;
      string pCNHkJglge;
      string dmYglYUziY;
      if(LZmInLxofQ == GOFsUbnlDx){NUJBIMkFMV = true;}
      else if(GOFsUbnlDx == LZmInLxofQ){WQyrXZjFEs = true;}
      if(krqnwcmatm == iKyVuPlTDp){ZDSNEDfriB = true;}
      else if(iKyVuPlTDp == krqnwcmatm){iQDYJyqpJZ = true;}
      if(xJSAUMwQYH == BZbyQZVtmj){EBheBjMKYy = true;}
      else if(BZbyQZVtmj == xJSAUMwQYH){bkJXCuGTmd = true;}
      if(TcwXuTUcDK == lxViLPsBbr){LHzOAUsMyX = true;}
      else if(lxViLPsBbr == TcwXuTUcDK){fRUnEyDoRe = true;}
      if(RNrWMChyVc == STSsKCjTgf){XbZLEZUKci = true;}
      else if(STSsKCjTgf == RNrWMChyVc){zkMAFQLnPY = true;}
      if(mMVYgBGlma == ycQjCglGbt){scQhULmdzY = true;}
      else if(ycQjCglGbt == mMVYgBGlma){HFBbKkHapc = true;}
      if(OgPXxIwSsc == GszTKknOJe){AZfOJSDDMj = true;}
      else if(GszTKknOJe == OgPXxIwSsc){SPRaMRuOUK = true;}
      if(IKXiVjRwnR == WkrKWgGinO){KTsKcbbWZa = true;}
      if(eytwUHGWpt == pCNHkJglge){PBhpEiqRso = true;}
      if(MhocwkxTZE == dmYglYUziY){gOMYXyuKCl = true;}
      while(WkrKWgGinO == IKXiVjRwnR){uBYeapYJRl = true;}
      while(pCNHkJglge == pCNHkJglge){jSEOWaPrdS = true;}
      while(dmYglYUziY == dmYglYUziY){qbznLiTlmm = true;}
      if(NUJBIMkFMV == true){NUJBIMkFMV = false;}
      if(ZDSNEDfriB == true){ZDSNEDfriB = false;}
      if(EBheBjMKYy == true){EBheBjMKYy = false;}
      if(LHzOAUsMyX == true){LHzOAUsMyX = false;}
      if(XbZLEZUKci == true){XbZLEZUKci = false;}
      if(scQhULmdzY == true){scQhULmdzY = false;}
      if(AZfOJSDDMj == true){AZfOJSDDMj = false;}
      if(KTsKcbbWZa == true){KTsKcbbWZa = false;}
      if(PBhpEiqRso == true){PBhpEiqRso = false;}
      if(gOMYXyuKCl == true){gOMYXyuKCl = false;}
      if(WQyrXZjFEs == true){WQyrXZjFEs = false;}
      if(iQDYJyqpJZ == true){iQDYJyqpJZ = false;}
      if(bkJXCuGTmd == true){bkJXCuGTmd = false;}
      if(fRUnEyDoRe == true){fRUnEyDoRe = false;}
      if(zkMAFQLnPY == true){zkMAFQLnPY = false;}
      if(HFBbKkHapc == true){HFBbKkHapc = false;}
      if(SPRaMRuOUK == true){SPRaMRuOUK = false;}
      if(uBYeapYJRl == true){uBYeapYJRl = false;}
      if(jSEOWaPrdS == true){jSEOWaPrdS = false;}
      if(qbznLiTlmm == true){qbznLiTlmm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YFJIARLZOX
{ 
  void Jgfqtniihu()
  { 
      bool DspgjlTxOf = false;
      bool szScRqjlNL = false;
      bool xGRpyJKxEa = false;
      bool kAufVotNJu = false;
      bool JdRcmLHnUw = false;
      bool NliTgwazia = false;
      bool bWsnurElHc = false;
      bool wWbSBTnnDm = false;
      bool BWcHNyRazY = false;
      bool NteiTmkdht = false;
      bool HVfrzpKPRN = false;
      bool HlwwYEtkaw = false;
      bool ZcmhOBrryO = false;
      bool hKGIefpjHW = false;
      bool nBIlQbyiJP = false;
      bool szDkTdhxcy = false;
      bool yRRDexemQs = false;
      bool OJcDHYUBRl = false;
      bool DJiiUiHUoB = false;
      bool xrHJYWjFHT = false;
      string XKtRgYFDOb;
      string ZLVLkaLPJw;
      string wOrPQaqXrR;
      string hOicDSaHrn;
      string pmwiNLQykD;
      string cnPxhIRdAF;
      string ghLxtLcrHR;
      string AEXVFJRICF;
      string Jslonsykut;
      string BxGlGIaznC;
      string hXpSCYQtrY;
      string qIbtumuWIB;
      string MqxNQDxkOw;
      string hSUzXlDSlP;
      string cDsVDrUMqT;
      string NEpmoqacCz;
      string befwpYnbWJ;
      string jbjsXIxaKY;
      string hjtthdbgJf;
      string KZQlnxXxfd;
      if(XKtRgYFDOb == hXpSCYQtrY){DspgjlTxOf = true;}
      else if(hXpSCYQtrY == XKtRgYFDOb){HVfrzpKPRN = true;}
      if(ZLVLkaLPJw == qIbtumuWIB){szScRqjlNL = true;}
      else if(qIbtumuWIB == ZLVLkaLPJw){HlwwYEtkaw = true;}
      if(wOrPQaqXrR == MqxNQDxkOw){xGRpyJKxEa = true;}
      else if(MqxNQDxkOw == wOrPQaqXrR){ZcmhOBrryO = true;}
      if(hOicDSaHrn == hSUzXlDSlP){kAufVotNJu = true;}
      else if(hSUzXlDSlP == hOicDSaHrn){hKGIefpjHW = true;}
      if(pmwiNLQykD == cDsVDrUMqT){JdRcmLHnUw = true;}
      else if(cDsVDrUMqT == pmwiNLQykD){nBIlQbyiJP = true;}
      if(cnPxhIRdAF == NEpmoqacCz){NliTgwazia = true;}
      else if(NEpmoqacCz == cnPxhIRdAF){szDkTdhxcy = true;}
      if(ghLxtLcrHR == befwpYnbWJ){bWsnurElHc = true;}
      else if(befwpYnbWJ == ghLxtLcrHR){yRRDexemQs = true;}
      if(AEXVFJRICF == jbjsXIxaKY){wWbSBTnnDm = true;}
      if(Jslonsykut == hjtthdbgJf){BWcHNyRazY = true;}
      if(BxGlGIaznC == KZQlnxXxfd){NteiTmkdht = true;}
      while(jbjsXIxaKY == AEXVFJRICF){OJcDHYUBRl = true;}
      while(hjtthdbgJf == hjtthdbgJf){DJiiUiHUoB = true;}
      while(KZQlnxXxfd == KZQlnxXxfd){xrHJYWjFHT = true;}
      if(DspgjlTxOf == true){DspgjlTxOf = false;}
      if(szScRqjlNL == true){szScRqjlNL = false;}
      if(xGRpyJKxEa == true){xGRpyJKxEa = false;}
      if(kAufVotNJu == true){kAufVotNJu = false;}
      if(JdRcmLHnUw == true){JdRcmLHnUw = false;}
      if(NliTgwazia == true){NliTgwazia = false;}
      if(bWsnurElHc == true){bWsnurElHc = false;}
      if(wWbSBTnnDm == true){wWbSBTnnDm = false;}
      if(BWcHNyRazY == true){BWcHNyRazY = false;}
      if(NteiTmkdht == true){NteiTmkdht = false;}
      if(HVfrzpKPRN == true){HVfrzpKPRN = false;}
      if(HlwwYEtkaw == true){HlwwYEtkaw = false;}
      if(ZcmhOBrryO == true){ZcmhOBrryO = false;}
      if(hKGIefpjHW == true){hKGIefpjHW = false;}
      if(nBIlQbyiJP == true){nBIlQbyiJP = false;}
      if(szDkTdhxcy == true){szDkTdhxcy = false;}
      if(yRRDexemQs == true){yRRDexemQs = false;}
      if(OJcDHYUBRl == true){OJcDHYUBRl = false;}
      if(DJiiUiHUoB == true){DJiiUiHUoB = false;}
      if(xrHJYWjFHT == true){xrHJYWjFHT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CXESCNDCTQ
{ 
  void MNRJOzGVAw()
  { 
      bool haetLsoJxl = false;
      bool fSOXzoPhDC = false;
      bool tSTrUyXXfG = false;
      bool AKulPcflzW = false;
      bool YinzFjMUxK = false;
      bool oVgFWOHmYN = false;
      bool VQdqlUWbHV = false;
      bool JdhgcKeUmk = false;
      bool kDaUQdcpOB = false;
      bool VsMlAHExMk = false;
      bool MjMaBKnAbM = false;
      bool jlAnbSpIZI = false;
      bool qgMGAPRwfV = false;
      bool FgHBXBpzTG = false;
      bool pcOCRisYKh = false;
      bool QuXEtfXGZk = false;
      bool sqTFGCdyPZ = false;
      bool cpoSSNSJoQ = false;
      bool WskyEJJDHr = false;
      bool diYiNyIIwO = false;
      string OICLHRlkTI;
      string TMdqSLDjqt;
      string mjtCbteqbO;
      string AdIuGyNiZp;
      string gmcdhicKYm;
      string pEpHleOAiM;
      string luJFIoEhjT;
      string yUKAMAHPTr;
      string RTRoXumBIb;
      string jMzMDlcXVr;
      string etZEoVtotl;
      string WyfquScTgM;
      string CCYIikUxwZ;
      string WitaNWsMAB;
      string BxGWElgIRk;
      string JIpIpbURUD;
      string BwsUPmEFcX;
      string ZPTfLEwCDx;
      string ELfLQNskkk;
      string CarwAFEkHQ;
      if(OICLHRlkTI == etZEoVtotl){haetLsoJxl = true;}
      else if(etZEoVtotl == OICLHRlkTI){MjMaBKnAbM = true;}
      if(TMdqSLDjqt == WyfquScTgM){fSOXzoPhDC = true;}
      else if(WyfquScTgM == TMdqSLDjqt){jlAnbSpIZI = true;}
      if(mjtCbteqbO == CCYIikUxwZ){tSTrUyXXfG = true;}
      else if(CCYIikUxwZ == mjtCbteqbO){qgMGAPRwfV = true;}
      if(AdIuGyNiZp == WitaNWsMAB){AKulPcflzW = true;}
      else if(WitaNWsMAB == AdIuGyNiZp){FgHBXBpzTG = true;}
      if(gmcdhicKYm == BxGWElgIRk){YinzFjMUxK = true;}
      else if(BxGWElgIRk == gmcdhicKYm){pcOCRisYKh = true;}
      if(pEpHleOAiM == JIpIpbURUD){oVgFWOHmYN = true;}
      else if(JIpIpbURUD == pEpHleOAiM){QuXEtfXGZk = true;}
      if(luJFIoEhjT == BwsUPmEFcX){VQdqlUWbHV = true;}
      else if(BwsUPmEFcX == luJFIoEhjT){sqTFGCdyPZ = true;}
      if(yUKAMAHPTr == ZPTfLEwCDx){JdhgcKeUmk = true;}
      if(RTRoXumBIb == ELfLQNskkk){kDaUQdcpOB = true;}
      if(jMzMDlcXVr == CarwAFEkHQ){VsMlAHExMk = true;}
      while(ZPTfLEwCDx == yUKAMAHPTr){cpoSSNSJoQ = true;}
      while(ELfLQNskkk == ELfLQNskkk){WskyEJJDHr = true;}
      while(CarwAFEkHQ == CarwAFEkHQ){diYiNyIIwO = true;}
      if(haetLsoJxl == true){haetLsoJxl = false;}
      if(fSOXzoPhDC == true){fSOXzoPhDC = false;}
      if(tSTrUyXXfG == true){tSTrUyXXfG = false;}
      if(AKulPcflzW == true){AKulPcflzW = false;}
      if(YinzFjMUxK == true){YinzFjMUxK = false;}
      if(oVgFWOHmYN == true){oVgFWOHmYN = false;}
      if(VQdqlUWbHV == true){VQdqlUWbHV = false;}
      if(JdhgcKeUmk == true){JdhgcKeUmk = false;}
      if(kDaUQdcpOB == true){kDaUQdcpOB = false;}
      if(VsMlAHExMk == true){VsMlAHExMk = false;}
      if(MjMaBKnAbM == true){MjMaBKnAbM = false;}
      if(jlAnbSpIZI == true){jlAnbSpIZI = false;}
      if(qgMGAPRwfV == true){qgMGAPRwfV = false;}
      if(FgHBXBpzTG == true){FgHBXBpzTG = false;}
      if(pcOCRisYKh == true){pcOCRisYKh = false;}
      if(QuXEtfXGZk == true){QuXEtfXGZk = false;}
      if(sqTFGCdyPZ == true){sqTFGCdyPZ = false;}
      if(cpoSSNSJoQ == true){cpoSSNSJoQ = false;}
      if(WskyEJJDHr == true){WskyEJJDHr = false;}
      if(diYiNyIIwO == true){diYiNyIIwO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YHODONKJHC
{ 
  void qPfZqlLFYm()
  { 
      bool xVgPSLJVfY = false;
      bool yJwnQCttRY = false;
      bool bQjOVZtGgk = false;
      bool aEJoVasLmX = false;
      bool SnJRpQilyn = false;
      bool ZxboBflStr = false;
      bool RCotytAGRp = false;
      bool JhHsGnHRYF = false;
      bool qIIrLcbUno = false;
      bool nZRuGPzOSu = false;
      bool PbTIeqphiN = false;
      bool YUtnBJtwhV = false;
      bool SeSbBiQMmp = false;
      bool nrydoOnANU = false;
      bool ltlZQTfctx = false;
      bool VCgxcjIqHu = false;
      bool ZdurYgVQzl = false;
      bool UthMiXsrLg = false;
      bool DnSoTlLAAE = false;
      bool GwrStIysBj = false;
      string GVgzAaJggJ;
      string ohjfdOgGRm;
      string AZhffQhxxh;
      string OEZVnWKtBP;
      string rNjapAkokL;
      string ZOfLugmBTj;
      string rMjztkIOqG;
      string DlFBuloGoe;
      string erLkHzXNZH;
      string jJaQXfdkfF;
      string rWydHnJeQJ;
      string qfLoEzAyqu;
      string MuniWtLndO;
      string HEZjlItgcT;
      string oswQQDxkMX;
      string eeskrxhOHN;
      string cVACBmFaDw;
      string FTVXFSyXST;
      string wZbFjbKoqn;
      string ZeZOpTrtOd;
      if(GVgzAaJggJ == rWydHnJeQJ){xVgPSLJVfY = true;}
      else if(rWydHnJeQJ == GVgzAaJggJ){PbTIeqphiN = true;}
      if(ohjfdOgGRm == qfLoEzAyqu){yJwnQCttRY = true;}
      else if(qfLoEzAyqu == ohjfdOgGRm){YUtnBJtwhV = true;}
      if(AZhffQhxxh == MuniWtLndO){bQjOVZtGgk = true;}
      else if(MuniWtLndO == AZhffQhxxh){SeSbBiQMmp = true;}
      if(OEZVnWKtBP == HEZjlItgcT){aEJoVasLmX = true;}
      else if(HEZjlItgcT == OEZVnWKtBP){nrydoOnANU = true;}
      if(rNjapAkokL == oswQQDxkMX){SnJRpQilyn = true;}
      else if(oswQQDxkMX == rNjapAkokL){ltlZQTfctx = true;}
      if(ZOfLugmBTj == eeskrxhOHN){ZxboBflStr = true;}
      else if(eeskrxhOHN == ZOfLugmBTj){VCgxcjIqHu = true;}
      if(rMjztkIOqG == cVACBmFaDw){RCotytAGRp = true;}
      else if(cVACBmFaDw == rMjztkIOqG){ZdurYgVQzl = true;}
      if(DlFBuloGoe == FTVXFSyXST){JhHsGnHRYF = true;}
      if(erLkHzXNZH == wZbFjbKoqn){qIIrLcbUno = true;}
      if(jJaQXfdkfF == ZeZOpTrtOd){nZRuGPzOSu = true;}
      while(FTVXFSyXST == DlFBuloGoe){UthMiXsrLg = true;}
      while(wZbFjbKoqn == wZbFjbKoqn){DnSoTlLAAE = true;}
      while(ZeZOpTrtOd == ZeZOpTrtOd){GwrStIysBj = true;}
      if(xVgPSLJVfY == true){xVgPSLJVfY = false;}
      if(yJwnQCttRY == true){yJwnQCttRY = false;}
      if(bQjOVZtGgk == true){bQjOVZtGgk = false;}
      if(aEJoVasLmX == true){aEJoVasLmX = false;}
      if(SnJRpQilyn == true){SnJRpQilyn = false;}
      if(ZxboBflStr == true){ZxboBflStr = false;}
      if(RCotytAGRp == true){RCotytAGRp = false;}
      if(JhHsGnHRYF == true){JhHsGnHRYF = false;}
      if(qIIrLcbUno == true){qIIrLcbUno = false;}
      if(nZRuGPzOSu == true){nZRuGPzOSu = false;}
      if(PbTIeqphiN == true){PbTIeqphiN = false;}
      if(YUtnBJtwhV == true){YUtnBJtwhV = false;}
      if(SeSbBiQMmp == true){SeSbBiQMmp = false;}
      if(nrydoOnANU == true){nrydoOnANU = false;}
      if(ltlZQTfctx == true){ltlZQTfctx = false;}
      if(VCgxcjIqHu == true){VCgxcjIqHu = false;}
      if(ZdurYgVQzl == true){ZdurYgVQzl = false;}
      if(UthMiXsrLg == true){UthMiXsrLg = false;}
      if(DnSoTlLAAE == true){DnSoTlLAAE = false;}
      if(GwrStIysBj == true){GwrStIysBj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PHCVDSXZBJ
{ 
  void XOkKzXJljk()
  { 
      bool asixYbgjHQ = false;
      bool uOAUWBinxD = false;
      bool AesQACWzUz = false;
      bool oIkBWEYBlj = false;
      bool MpEulJKUzx = false;
      bool PukAdwzRwV = false;
      bool EhOIbmcyxR = false;
      bool bhBMqKZxeq = false;
      bool rCAXitWkXa = false;
      bool FHEQeeawSz = false;
      bool fLWgUgsXJT = false;
      bool VClFcBgqYh = false;
      bool PraVMUdkhL = false;
      bool iddfKgfTCB = false;
      bool AzbEFCUymc = false;
      bool yjWkjnkBUA = false;
      bool DHpxjqXGtw = false;
      bool VNnWgPQVPJ = false;
      bool AeyENzHswW = false;
      bool uezCysIdTO = false;
      string oVzEneYAdC;
      string GJAQZWxupg;
      string zZIowMSMet;
      string jRXJXlRHAC;
      string VkPEmGmKWV;
      string nykVKOMKHb;
      string MLUiRokqsn;
      string EoumLNKEBo;
      string YHpIGkfCzI;
      string YHzYpKPfly;
      string VwQhRyDxKw;
      string EIISCEUMbf;
      string IirjOwoVxB;
      string ydRCTcqIqI;
      string hiqCEQygWl;
      string oDDGplEfSU;
      string JhzJyZpFyY;
      string NMVTyYqofy;
      string xHyLLtZLMg;
      string YKoVyzjhEd;
      if(oVzEneYAdC == VwQhRyDxKw){asixYbgjHQ = true;}
      else if(VwQhRyDxKw == oVzEneYAdC){fLWgUgsXJT = true;}
      if(GJAQZWxupg == EIISCEUMbf){uOAUWBinxD = true;}
      else if(EIISCEUMbf == GJAQZWxupg){VClFcBgqYh = true;}
      if(zZIowMSMet == IirjOwoVxB){AesQACWzUz = true;}
      else if(IirjOwoVxB == zZIowMSMet){PraVMUdkhL = true;}
      if(jRXJXlRHAC == ydRCTcqIqI){oIkBWEYBlj = true;}
      else if(ydRCTcqIqI == jRXJXlRHAC){iddfKgfTCB = true;}
      if(VkPEmGmKWV == hiqCEQygWl){MpEulJKUzx = true;}
      else if(hiqCEQygWl == VkPEmGmKWV){AzbEFCUymc = true;}
      if(nykVKOMKHb == oDDGplEfSU){PukAdwzRwV = true;}
      else if(oDDGplEfSU == nykVKOMKHb){yjWkjnkBUA = true;}
      if(MLUiRokqsn == JhzJyZpFyY){EhOIbmcyxR = true;}
      else if(JhzJyZpFyY == MLUiRokqsn){DHpxjqXGtw = true;}
      if(EoumLNKEBo == NMVTyYqofy){bhBMqKZxeq = true;}
      if(YHpIGkfCzI == xHyLLtZLMg){rCAXitWkXa = true;}
      if(YHzYpKPfly == YKoVyzjhEd){FHEQeeawSz = true;}
      while(NMVTyYqofy == EoumLNKEBo){VNnWgPQVPJ = true;}
      while(xHyLLtZLMg == xHyLLtZLMg){AeyENzHswW = true;}
      while(YKoVyzjhEd == YKoVyzjhEd){uezCysIdTO = true;}
      if(asixYbgjHQ == true){asixYbgjHQ = false;}
      if(uOAUWBinxD == true){uOAUWBinxD = false;}
      if(AesQACWzUz == true){AesQACWzUz = false;}
      if(oIkBWEYBlj == true){oIkBWEYBlj = false;}
      if(MpEulJKUzx == true){MpEulJKUzx = false;}
      if(PukAdwzRwV == true){PukAdwzRwV = false;}
      if(EhOIbmcyxR == true){EhOIbmcyxR = false;}
      if(bhBMqKZxeq == true){bhBMqKZxeq = false;}
      if(rCAXitWkXa == true){rCAXitWkXa = false;}
      if(FHEQeeawSz == true){FHEQeeawSz = false;}
      if(fLWgUgsXJT == true){fLWgUgsXJT = false;}
      if(VClFcBgqYh == true){VClFcBgqYh = false;}
      if(PraVMUdkhL == true){PraVMUdkhL = false;}
      if(iddfKgfTCB == true){iddfKgfTCB = false;}
      if(AzbEFCUymc == true){AzbEFCUymc = false;}
      if(yjWkjnkBUA == true){yjWkjnkBUA = false;}
      if(DHpxjqXGtw == true){DHpxjqXGtw = false;}
      if(VNnWgPQVPJ == true){VNnWgPQVPJ = false;}
      if(AeyENzHswW == true){AeyENzHswW = false;}
      if(uezCysIdTO == true){uezCysIdTO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZMYQYMXMLB
{ 
  void XdKDuqqrtS()
  { 
      bool ZiNCNhMlcZ = false;
      bool ajDQRygRHd = false;
      bool IKiUdOdWSd = false;
      bool sZoVUUeKzz = false;
      bool pohnIgySob = false;
      bool ReVUnPAsXy = false;
      bool EpTzgBugux = false;
      bool TVSHnSbuLx = false;
      bool PKhpLNEThF = false;
      bool UkmAuzViHG = false;
      bool lQXrIwLNgV = false;
      bool mEhaisIdmT = false;
      bool xazpbhhSLn = false;
      bool xsmELymphP = false;
      bool BpmLRPDMQC = false;
      bool qqunJKRhPZ = false;
      bool NsBrXsQcOj = false;
      bool GSuWRGmmXL = false;
      bool eVBJxFyztA = false;
      bool gEZHBInunY = false;
      string HSPIBafoBO;
      string DEwnhGRhTA;
      string jSnUZppXuV;
      string tjtXOKHTqG;
      string OrUuDKNuZI;
      string AwkGSoduhL;
      string kHteTSKXYW;
      string zxqNkrxrQO;
      string ctymUyznFY;
      string gMlfUGyobj;
      string AoVCJDFWUa;
      string rldShpJHKV;
      string TVRzplLKre;
      string sHQfOmYudR;
      string scSeguhSxe;
      string wpeFQdWVLW;
      string qtepgjUyEu;
      string RNdrcpCmSu;
      string EsNMhDbKOj;
      string QCjGZyxcyw;
      if(HSPIBafoBO == AoVCJDFWUa){ZiNCNhMlcZ = true;}
      else if(AoVCJDFWUa == HSPIBafoBO){lQXrIwLNgV = true;}
      if(DEwnhGRhTA == rldShpJHKV){ajDQRygRHd = true;}
      else if(rldShpJHKV == DEwnhGRhTA){mEhaisIdmT = true;}
      if(jSnUZppXuV == TVRzplLKre){IKiUdOdWSd = true;}
      else if(TVRzplLKre == jSnUZppXuV){xazpbhhSLn = true;}
      if(tjtXOKHTqG == sHQfOmYudR){sZoVUUeKzz = true;}
      else if(sHQfOmYudR == tjtXOKHTqG){xsmELymphP = true;}
      if(OrUuDKNuZI == scSeguhSxe){pohnIgySob = true;}
      else if(scSeguhSxe == OrUuDKNuZI){BpmLRPDMQC = true;}
      if(AwkGSoduhL == wpeFQdWVLW){ReVUnPAsXy = true;}
      else if(wpeFQdWVLW == AwkGSoduhL){qqunJKRhPZ = true;}
      if(kHteTSKXYW == qtepgjUyEu){EpTzgBugux = true;}
      else if(qtepgjUyEu == kHteTSKXYW){NsBrXsQcOj = true;}
      if(zxqNkrxrQO == RNdrcpCmSu){TVSHnSbuLx = true;}
      if(ctymUyznFY == EsNMhDbKOj){PKhpLNEThF = true;}
      if(gMlfUGyobj == QCjGZyxcyw){UkmAuzViHG = true;}
      while(RNdrcpCmSu == zxqNkrxrQO){GSuWRGmmXL = true;}
      while(EsNMhDbKOj == EsNMhDbKOj){eVBJxFyztA = true;}
      while(QCjGZyxcyw == QCjGZyxcyw){gEZHBInunY = true;}
      if(ZiNCNhMlcZ == true){ZiNCNhMlcZ = false;}
      if(ajDQRygRHd == true){ajDQRygRHd = false;}
      if(IKiUdOdWSd == true){IKiUdOdWSd = false;}
      if(sZoVUUeKzz == true){sZoVUUeKzz = false;}
      if(pohnIgySob == true){pohnIgySob = false;}
      if(ReVUnPAsXy == true){ReVUnPAsXy = false;}
      if(EpTzgBugux == true){EpTzgBugux = false;}
      if(TVSHnSbuLx == true){TVSHnSbuLx = false;}
      if(PKhpLNEThF == true){PKhpLNEThF = false;}
      if(UkmAuzViHG == true){UkmAuzViHG = false;}
      if(lQXrIwLNgV == true){lQXrIwLNgV = false;}
      if(mEhaisIdmT == true){mEhaisIdmT = false;}
      if(xazpbhhSLn == true){xazpbhhSLn = false;}
      if(xsmELymphP == true){xsmELymphP = false;}
      if(BpmLRPDMQC == true){BpmLRPDMQC = false;}
      if(qqunJKRhPZ == true){qqunJKRhPZ = false;}
      if(NsBrXsQcOj == true){NsBrXsQcOj = false;}
      if(GSuWRGmmXL == true){GSuWRGmmXL = false;}
      if(eVBJxFyztA == true){eVBJxFyztA = false;}
      if(gEZHBInunY == true){gEZHBInunY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWJVXAFTZB
{ 
  void mxzJMfknho()
  { 
      bool emgTViFcus = false;
      bool LyolzRLVgk = false;
      bool KJmWCDRyco = false;
      bool weYXguWtEg = false;
      bool fRJiMPjycI = false;
      bool XanHzUzKQS = false;
      bool QGAGwgYREE = false;
      bool tRRzEszEKm = false;
      bool TTVURVqQXM = false;
      bool uMdlPZRDle = false;
      bool pRsYOGInCG = false;
      bool VuzdyxkfnZ = false;
      bool oIsrIgmfie = false;
      bool awRewBZwFL = false;
      bool MCNRqAMAmS = false;
      bool okPMohYAQg = false;
      bool ScFXeYcUgw = false;
      bool WnZcMmtaBH = false;
      bool TmrQopfFoO = false;
      bool cYfYrjxpmR = false;
      string dTmdefNjmD;
      string rgTlsPrdRc;
      string ZmzUhJlkQo;
      string lmugoDyDAR;
      string BmeVeRiSuk;
      string pDVbbqTSwU;
      string sbSyREllxp;
      string QndzbmIdoP;
      string aSofyiQSEy;
      string ifHeYYTfDZ;
      string exVFTCYWAo;
      string hodftZmmzi;
      string mSgyGkfyZC;
      string SbZOkdxjLw;
      string JtSPQtCbjz;
      string lggUlMPXyi;
      string VZxxWFOOuQ;
      string cCbDYsARhM;
      string iENaQkuFbX;
      string NYkcZiwUsK;
      if(dTmdefNjmD == exVFTCYWAo){emgTViFcus = true;}
      else if(exVFTCYWAo == dTmdefNjmD){pRsYOGInCG = true;}
      if(rgTlsPrdRc == hodftZmmzi){LyolzRLVgk = true;}
      else if(hodftZmmzi == rgTlsPrdRc){VuzdyxkfnZ = true;}
      if(ZmzUhJlkQo == mSgyGkfyZC){KJmWCDRyco = true;}
      else if(mSgyGkfyZC == ZmzUhJlkQo){oIsrIgmfie = true;}
      if(lmugoDyDAR == SbZOkdxjLw){weYXguWtEg = true;}
      else if(SbZOkdxjLw == lmugoDyDAR){awRewBZwFL = true;}
      if(BmeVeRiSuk == JtSPQtCbjz){fRJiMPjycI = true;}
      else if(JtSPQtCbjz == BmeVeRiSuk){MCNRqAMAmS = true;}
      if(pDVbbqTSwU == lggUlMPXyi){XanHzUzKQS = true;}
      else if(lggUlMPXyi == pDVbbqTSwU){okPMohYAQg = true;}
      if(sbSyREllxp == VZxxWFOOuQ){QGAGwgYREE = true;}
      else if(VZxxWFOOuQ == sbSyREllxp){ScFXeYcUgw = true;}
      if(QndzbmIdoP == cCbDYsARhM){tRRzEszEKm = true;}
      if(aSofyiQSEy == iENaQkuFbX){TTVURVqQXM = true;}
      if(ifHeYYTfDZ == NYkcZiwUsK){uMdlPZRDle = true;}
      while(cCbDYsARhM == QndzbmIdoP){WnZcMmtaBH = true;}
      while(iENaQkuFbX == iENaQkuFbX){TmrQopfFoO = true;}
      while(NYkcZiwUsK == NYkcZiwUsK){cYfYrjxpmR = true;}
      if(emgTViFcus == true){emgTViFcus = false;}
      if(LyolzRLVgk == true){LyolzRLVgk = false;}
      if(KJmWCDRyco == true){KJmWCDRyco = false;}
      if(weYXguWtEg == true){weYXguWtEg = false;}
      if(fRJiMPjycI == true){fRJiMPjycI = false;}
      if(XanHzUzKQS == true){XanHzUzKQS = false;}
      if(QGAGwgYREE == true){QGAGwgYREE = false;}
      if(tRRzEszEKm == true){tRRzEszEKm = false;}
      if(TTVURVqQXM == true){TTVURVqQXM = false;}
      if(uMdlPZRDle == true){uMdlPZRDle = false;}
      if(pRsYOGInCG == true){pRsYOGInCG = false;}
      if(VuzdyxkfnZ == true){VuzdyxkfnZ = false;}
      if(oIsrIgmfie == true){oIsrIgmfie = false;}
      if(awRewBZwFL == true){awRewBZwFL = false;}
      if(MCNRqAMAmS == true){MCNRqAMAmS = false;}
      if(okPMohYAQg == true){okPMohYAQg = false;}
      if(ScFXeYcUgw == true){ScFXeYcUgw = false;}
      if(WnZcMmtaBH == true){WnZcMmtaBH = false;}
      if(TmrQopfFoO == true){TmrQopfFoO = false;}
      if(cYfYrjxpmR == true){cYfYrjxpmR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RTUVBEMPHY
{ 
  void DTnJqYLESN()
  { 
      bool brhJRkeHQn = false;
      bool jrVSJpOCVJ = false;
      bool XGBsmFldcC = false;
      bool XcWgjDFYOA = false;
      bool CCDqxByMUo = false;
      bool UVhctUqnVL = false;
      bool yBeOQHVohF = false;
      bool jpmVGUCKwl = false;
      bool GZImhBttmO = false;
      bool MQDCCBXoao = false;
      bool fJdOFdiMVZ = false;
      bool RfrjEXsqfO = false;
      bool MaBSsTljTF = false;
      bool wNjGFxwshD = false;
      bool SgYNwfYTxd = false;
      bool HgILbFHKVl = false;
      bool qysPcEwldH = false;
      bool bzIcwfCnWM = false;
      bool tSloxOEXdA = false;
      bool okWwLUmIjr = false;
      string VQQAQetnom;
      string VTiuDQrfXa;
      string sycNSByOgm;
      string SDTGimYOkp;
      string JolmHJQjKT;
      string DQoMQWmCgO;
      string feHCTSzbMP;
      string qdthRDLpFI;
      string kOEMiCOGpL;
      string AVgVJdhjTo;
      string KnWtbZVGuM;
      string KxxYdRatSR;
      string EslAPVwYXn;
      string VbVQywqJkJ;
      string fHLcBDYIqr;
      string CnQBkQBVeG;
      string dwiHqiagZh;
      string ZRIJkwgJzM;
      string wmhfkhKTeg;
      string tUeefiYElR;
      if(VQQAQetnom == KnWtbZVGuM){brhJRkeHQn = true;}
      else if(KnWtbZVGuM == VQQAQetnom){fJdOFdiMVZ = true;}
      if(VTiuDQrfXa == KxxYdRatSR){jrVSJpOCVJ = true;}
      else if(KxxYdRatSR == VTiuDQrfXa){RfrjEXsqfO = true;}
      if(sycNSByOgm == EslAPVwYXn){XGBsmFldcC = true;}
      else if(EslAPVwYXn == sycNSByOgm){MaBSsTljTF = true;}
      if(SDTGimYOkp == VbVQywqJkJ){XcWgjDFYOA = true;}
      else if(VbVQywqJkJ == SDTGimYOkp){wNjGFxwshD = true;}
      if(JolmHJQjKT == fHLcBDYIqr){CCDqxByMUo = true;}
      else if(fHLcBDYIqr == JolmHJQjKT){SgYNwfYTxd = true;}
      if(DQoMQWmCgO == CnQBkQBVeG){UVhctUqnVL = true;}
      else if(CnQBkQBVeG == DQoMQWmCgO){HgILbFHKVl = true;}
      if(feHCTSzbMP == dwiHqiagZh){yBeOQHVohF = true;}
      else if(dwiHqiagZh == feHCTSzbMP){qysPcEwldH = true;}
      if(qdthRDLpFI == ZRIJkwgJzM){jpmVGUCKwl = true;}
      if(kOEMiCOGpL == wmhfkhKTeg){GZImhBttmO = true;}
      if(AVgVJdhjTo == tUeefiYElR){MQDCCBXoao = true;}
      while(ZRIJkwgJzM == qdthRDLpFI){bzIcwfCnWM = true;}
      while(wmhfkhKTeg == wmhfkhKTeg){tSloxOEXdA = true;}
      while(tUeefiYElR == tUeefiYElR){okWwLUmIjr = true;}
      if(brhJRkeHQn == true){brhJRkeHQn = false;}
      if(jrVSJpOCVJ == true){jrVSJpOCVJ = false;}
      if(XGBsmFldcC == true){XGBsmFldcC = false;}
      if(XcWgjDFYOA == true){XcWgjDFYOA = false;}
      if(CCDqxByMUo == true){CCDqxByMUo = false;}
      if(UVhctUqnVL == true){UVhctUqnVL = false;}
      if(yBeOQHVohF == true){yBeOQHVohF = false;}
      if(jpmVGUCKwl == true){jpmVGUCKwl = false;}
      if(GZImhBttmO == true){GZImhBttmO = false;}
      if(MQDCCBXoao == true){MQDCCBXoao = false;}
      if(fJdOFdiMVZ == true){fJdOFdiMVZ = false;}
      if(RfrjEXsqfO == true){RfrjEXsqfO = false;}
      if(MaBSsTljTF == true){MaBSsTljTF = false;}
      if(wNjGFxwshD == true){wNjGFxwshD = false;}
      if(SgYNwfYTxd == true){SgYNwfYTxd = false;}
      if(HgILbFHKVl == true){HgILbFHKVl = false;}
      if(qysPcEwldH == true){qysPcEwldH = false;}
      if(bzIcwfCnWM == true){bzIcwfCnWM = false;}
      if(tSloxOEXdA == true){tSloxOEXdA = false;}
      if(okWwLUmIjr == true){okWwLUmIjr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CJRCJBDLMZ
{ 
  void eUVEbgmoTI()
  { 
      bool EtehHlUmen = false;
      bool VptnhWLzxQ = false;
      bool wNZrWCZWNS = false;
      bool eHHyzIRadd = false;
      bool NDETUCpxaR = false;
      bool iUfleqUlKF = false;
      bool MyZMINiuoY = false;
      bool FkUTDrIFXT = false;
      bool McuwiKbUSI = false;
      bool mePYRPdrKG = false;
      bool TtICLyzLhl = false;
      bool hOOpsiCccy = false;
      bool lNcfkZUwCn = false;
      bool OQuQARUrjk = false;
      bool KPlgZYQYfh = false;
      bool MAOMUFRbQl = false;
      bool cDJtWRTypa = false;
      bool NJsrmVawGM = false;
      bool JwPTaOBhut = false;
      bool AsbyHHGrJH = false;
      string lRbkSwkyaz;
      string eCRLlIacEQ;
      string UhqJSHsOMb;
      string dDEYmCXQQm;
      string LLzqUiDgjB;
      string omhipDZSSK;
      string CVkyUaysYi;
      string kJLQEJizoi;
      string DMeKmqVUhj;
      string cFyFjoaBWs;
      string jKIAQeaQdg;
      string UZciHpqZKd;
      string EcKnGeLGfP;
      string hgcwyrDetI;
      string PFqBOCbOxt;
      string yApsnHzTsk;
      string TUkOymxgjP;
      string lLfCNzkJZE;
      string DwIlQhqjHq;
      string rjkJouTcCb;
      if(lRbkSwkyaz == jKIAQeaQdg){EtehHlUmen = true;}
      else if(jKIAQeaQdg == lRbkSwkyaz){TtICLyzLhl = true;}
      if(eCRLlIacEQ == UZciHpqZKd){VptnhWLzxQ = true;}
      else if(UZciHpqZKd == eCRLlIacEQ){hOOpsiCccy = true;}
      if(UhqJSHsOMb == EcKnGeLGfP){wNZrWCZWNS = true;}
      else if(EcKnGeLGfP == UhqJSHsOMb){lNcfkZUwCn = true;}
      if(dDEYmCXQQm == hgcwyrDetI){eHHyzIRadd = true;}
      else if(hgcwyrDetI == dDEYmCXQQm){OQuQARUrjk = true;}
      if(LLzqUiDgjB == PFqBOCbOxt){NDETUCpxaR = true;}
      else if(PFqBOCbOxt == LLzqUiDgjB){KPlgZYQYfh = true;}
      if(omhipDZSSK == yApsnHzTsk){iUfleqUlKF = true;}
      else if(yApsnHzTsk == omhipDZSSK){MAOMUFRbQl = true;}
      if(CVkyUaysYi == TUkOymxgjP){MyZMINiuoY = true;}
      else if(TUkOymxgjP == CVkyUaysYi){cDJtWRTypa = true;}
      if(kJLQEJizoi == lLfCNzkJZE){FkUTDrIFXT = true;}
      if(DMeKmqVUhj == DwIlQhqjHq){McuwiKbUSI = true;}
      if(cFyFjoaBWs == rjkJouTcCb){mePYRPdrKG = true;}
      while(lLfCNzkJZE == kJLQEJizoi){NJsrmVawGM = true;}
      while(DwIlQhqjHq == DwIlQhqjHq){JwPTaOBhut = true;}
      while(rjkJouTcCb == rjkJouTcCb){AsbyHHGrJH = true;}
      if(EtehHlUmen == true){EtehHlUmen = false;}
      if(VptnhWLzxQ == true){VptnhWLzxQ = false;}
      if(wNZrWCZWNS == true){wNZrWCZWNS = false;}
      if(eHHyzIRadd == true){eHHyzIRadd = false;}
      if(NDETUCpxaR == true){NDETUCpxaR = false;}
      if(iUfleqUlKF == true){iUfleqUlKF = false;}
      if(MyZMINiuoY == true){MyZMINiuoY = false;}
      if(FkUTDrIFXT == true){FkUTDrIFXT = false;}
      if(McuwiKbUSI == true){McuwiKbUSI = false;}
      if(mePYRPdrKG == true){mePYRPdrKG = false;}
      if(TtICLyzLhl == true){TtICLyzLhl = false;}
      if(hOOpsiCccy == true){hOOpsiCccy = false;}
      if(lNcfkZUwCn == true){lNcfkZUwCn = false;}
      if(OQuQARUrjk == true){OQuQARUrjk = false;}
      if(KPlgZYQYfh == true){KPlgZYQYfh = false;}
      if(MAOMUFRbQl == true){MAOMUFRbQl = false;}
      if(cDJtWRTypa == true){cDJtWRTypa = false;}
      if(NJsrmVawGM == true){NJsrmVawGM = false;}
      if(JwPTaOBhut == true){JwPTaOBhut = false;}
      if(AsbyHHGrJH == true){AsbyHHGrJH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJAMXHUJTK
{ 
  void YLPjoeSUJu()
  { 
      bool GtANjSVGCR = false;
      bool jSQDdDcYxs = false;
      bool tnoSCUSzyJ = false;
      bool UYOmiYjJwF = false;
      bool owqwVWEwDY = false;
      bool XAIuESFgKO = false;
      bool zWHrxKEdTF = false;
      bool TTbqExwswf = false;
      bool PWwYkTPThQ = false;
      bool TCyhFRnyyK = false;
      bool SabxFDYRpH = false;
      bool VLkeycaiGd = false;
      bool tkuDkQVtll = false;
      bool IytkMnuySg = false;
      bool tycauHRSic = false;
      bool qFqUQgfXMo = false;
      bool heeEyWRzRK = false;
      bool hcQYiuITIc = false;
      bool zDLJuDGYUf = false;
      bool IWkdzPTXbX = false;
      string YYBNnrQMjw;
      string WJNfAIclXh;
      string BiDMcENpEg;
      string BFuGSwPDwW;
      string YXaVBkZAaI;
      string VUNnuoUnkj;
      string eaICtQOGME;
      string sZpAIcIgKq;
      string eNOuLgrHKd;
      string aaRLryPXak;
      string WSmVPueNfR;
      string gmdsFRLMqN;
      string YGwicRIdHK;
      string NjGZUMZsfP;
      string CeaswmxXGa;
      string lCgNLPVDsy;
      string mAFUExgDXs;
      string qSgaLteDmo;
      string TjWgXKCsNF;
      string pVzhcBYGnz;
      if(YYBNnrQMjw == WSmVPueNfR){GtANjSVGCR = true;}
      else if(WSmVPueNfR == YYBNnrQMjw){SabxFDYRpH = true;}
      if(WJNfAIclXh == gmdsFRLMqN){jSQDdDcYxs = true;}
      else if(gmdsFRLMqN == WJNfAIclXh){VLkeycaiGd = true;}
      if(BiDMcENpEg == YGwicRIdHK){tnoSCUSzyJ = true;}
      else if(YGwicRIdHK == BiDMcENpEg){tkuDkQVtll = true;}
      if(BFuGSwPDwW == NjGZUMZsfP){UYOmiYjJwF = true;}
      else if(NjGZUMZsfP == BFuGSwPDwW){IytkMnuySg = true;}
      if(YXaVBkZAaI == CeaswmxXGa){owqwVWEwDY = true;}
      else if(CeaswmxXGa == YXaVBkZAaI){tycauHRSic = true;}
      if(VUNnuoUnkj == lCgNLPVDsy){XAIuESFgKO = true;}
      else if(lCgNLPVDsy == VUNnuoUnkj){qFqUQgfXMo = true;}
      if(eaICtQOGME == mAFUExgDXs){zWHrxKEdTF = true;}
      else if(mAFUExgDXs == eaICtQOGME){heeEyWRzRK = true;}
      if(sZpAIcIgKq == qSgaLteDmo){TTbqExwswf = true;}
      if(eNOuLgrHKd == TjWgXKCsNF){PWwYkTPThQ = true;}
      if(aaRLryPXak == pVzhcBYGnz){TCyhFRnyyK = true;}
      while(qSgaLteDmo == sZpAIcIgKq){hcQYiuITIc = true;}
      while(TjWgXKCsNF == TjWgXKCsNF){zDLJuDGYUf = true;}
      while(pVzhcBYGnz == pVzhcBYGnz){IWkdzPTXbX = true;}
      if(GtANjSVGCR == true){GtANjSVGCR = false;}
      if(jSQDdDcYxs == true){jSQDdDcYxs = false;}
      if(tnoSCUSzyJ == true){tnoSCUSzyJ = false;}
      if(UYOmiYjJwF == true){UYOmiYjJwF = false;}
      if(owqwVWEwDY == true){owqwVWEwDY = false;}
      if(XAIuESFgKO == true){XAIuESFgKO = false;}
      if(zWHrxKEdTF == true){zWHrxKEdTF = false;}
      if(TTbqExwswf == true){TTbqExwswf = false;}
      if(PWwYkTPThQ == true){PWwYkTPThQ = false;}
      if(TCyhFRnyyK == true){TCyhFRnyyK = false;}
      if(SabxFDYRpH == true){SabxFDYRpH = false;}
      if(VLkeycaiGd == true){VLkeycaiGd = false;}
      if(tkuDkQVtll == true){tkuDkQVtll = false;}
      if(IytkMnuySg == true){IytkMnuySg = false;}
      if(tycauHRSic == true){tycauHRSic = false;}
      if(qFqUQgfXMo == true){qFqUQgfXMo = false;}
      if(heeEyWRzRK == true){heeEyWRzRK = false;}
      if(hcQYiuITIc == true){hcQYiuITIc = false;}
      if(zDLJuDGYUf == true){zDLJuDGYUf = false;}
      if(IWkdzPTXbX == true){IWkdzPTXbX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XHUCALGMVJ
{ 
  void UhroyfVElJ()
  { 
      bool qOXlUkqhQX = false;
      bool MjHIyziETA = false;
      bool VDBgMsDARF = false;
      bool esrVBuEcDC = false;
      bool sxiPuXVrZu = false;
      bool ZuSQemMpZb = false;
      bool hqQKsSqkHD = false;
      bool tGAQGYTllo = false;
      bool WKZVfiabqN = false;
      bool hODbTCgXWb = false;
      bool gjkWBTuBJF = false;
      bool TaEjEWQteJ = false;
      bool qOtsUfCXwE = false;
      bool qwOJHmZDUL = false;
      bool nZRktHJSXx = false;
      bool kmsMjRpqCU = false;
      bool QWEFOWLtcR = false;
      bool xNYSVRwIyM = false;
      bool VjAzSECCYp = false;
      bool whBzuQUMWW = false;
      string kdXxxDgycf;
      string frOLxUHArL;
      string RGTpoUQmhD;
      string mBnJIjSMEH;
      string noCqoVMFzZ;
      string NOdIReJhIc;
      string msPYrdEFCM;
      string BuwkXbDcBS;
      string HKnHoYWerd;
      string akEaUtYdyK;
      string RGDlYSSsko;
      string agfpUcFHiT;
      string HZNYlPpUPc;
      string CZdpABGBhW;
      string FcsDCsENGq;
      string oQtdCrsdAJ;
      string bxcHlBCpoT;
      string VDYMNefJWr;
      string KcOYnkeznH;
      string HcAYtIzlQA;
      if(kdXxxDgycf == RGDlYSSsko){qOXlUkqhQX = true;}
      else if(RGDlYSSsko == kdXxxDgycf){gjkWBTuBJF = true;}
      if(frOLxUHArL == agfpUcFHiT){MjHIyziETA = true;}
      else if(agfpUcFHiT == frOLxUHArL){TaEjEWQteJ = true;}
      if(RGTpoUQmhD == HZNYlPpUPc){VDBgMsDARF = true;}
      else if(HZNYlPpUPc == RGTpoUQmhD){qOtsUfCXwE = true;}
      if(mBnJIjSMEH == CZdpABGBhW){esrVBuEcDC = true;}
      else if(CZdpABGBhW == mBnJIjSMEH){qwOJHmZDUL = true;}
      if(noCqoVMFzZ == FcsDCsENGq){sxiPuXVrZu = true;}
      else if(FcsDCsENGq == noCqoVMFzZ){nZRktHJSXx = true;}
      if(NOdIReJhIc == oQtdCrsdAJ){ZuSQemMpZb = true;}
      else if(oQtdCrsdAJ == NOdIReJhIc){kmsMjRpqCU = true;}
      if(msPYrdEFCM == bxcHlBCpoT){hqQKsSqkHD = true;}
      else if(bxcHlBCpoT == msPYrdEFCM){QWEFOWLtcR = true;}
      if(BuwkXbDcBS == VDYMNefJWr){tGAQGYTllo = true;}
      if(HKnHoYWerd == KcOYnkeznH){WKZVfiabqN = true;}
      if(akEaUtYdyK == HcAYtIzlQA){hODbTCgXWb = true;}
      while(VDYMNefJWr == BuwkXbDcBS){xNYSVRwIyM = true;}
      while(KcOYnkeznH == KcOYnkeznH){VjAzSECCYp = true;}
      while(HcAYtIzlQA == HcAYtIzlQA){whBzuQUMWW = true;}
      if(qOXlUkqhQX == true){qOXlUkqhQX = false;}
      if(MjHIyziETA == true){MjHIyziETA = false;}
      if(VDBgMsDARF == true){VDBgMsDARF = false;}
      if(esrVBuEcDC == true){esrVBuEcDC = false;}
      if(sxiPuXVrZu == true){sxiPuXVrZu = false;}
      if(ZuSQemMpZb == true){ZuSQemMpZb = false;}
      if(hqQKsSqkHD == true){hqQKsSqkHD = false;}
      if(tGAQGYTllo == true){tGAQGYTllo = false;}
      if(WKZVfiabqN == true){WKZVfiabqN = false;}
      if(hODbTCgXWb == true){hODbTCgXWb = false;}
      if(gjkWBTuBJF == true){gjkWBTuBJF = false;}
      if(TaEjEWQteJ == true){TaEjEWQteJ = false;}
      if(qOtsUfCXwE == true){qOtsUfCXwE = false;}
      if(qwOJHmZDUL == true){qwOJHmZDUL = false;}
      if(nZRktHJSXx == true){nZRktHJSXx = false;}
      if(kmsMjRpqCU == true){kmsMjRpqCU = false;}
      if(QWEFOWLtcR == true){QWEFOWLtcR = false;}
      if(xNYSVRwIyM == true){xNYSVRwIyM = false;}
      if(VjAzSECCYp == true){VjAzSECCYp = false;}
      if(whBzuQUMWW == true){whBzuQUMWW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VRLHUCADRF
{ 
  void iiaCphAzIK()
  { 
      bool dkBzXCXNoQ = false;
      bool JeKDDBXiuX = false;
      bool SauAutDeRj = false;
      bool QMQeXZGzCy = false;
      bool qsIZFDFnGM = false;
      bool dFWckDoADc = false;
      bool yrwEzwNfed = false;
      bool tXfwgZSVuq = false;
      bool oPXEGKpnsU = false;
      bool jGuZzyxDZI = false;
      bool pYIbRFZawL = false;
      bool jTFMmiUqyn = false;
      bool GZlJtncGwh = false;
      bool cPulBPGulA = false;
      bool kOrhkPAilQ = false;
      bool dFFlCQmzgd = false;
      bool cTdNhTXSLW = false;
      bool bYExCqgDXe = false;
      bool mtTeEWKJjj = false;
      bool cHNIXRjezQ = false;
      string fgcbdwhCPP;
      string bEWyLKBrQo;
      string OHapWmCdSD;
      string iDARdFIpcA;
      string wLJRAlGfSx;
      string uMjoQXGmEp;
      string tEiMfYEFUF;
      string BLOPrDxJok;
      string gWKUIVSKAF;
      string zUkmGrbxkb;
      string gBKMujyTwN;
      string ZwyTJWsODK;
      string FsEPGgZbJA;
      string aAXMDeLyYX;
      string XzOmeDWRci;
      string yMsaWnwuGO;
      string JVJwlZYkPd;
      string LuoflGeRjC;
      string KIyaBOGxpO;
      string iQqKOBoRAE;
      if(fgcbdwhCPP == gBKMujyTwN){dkBzXCXNoQ = true;}
      else if(gBKMujyTwN == fgcbdwhCPP){pYIbRFZawL = true;}
      if(bEWyLKBrQo == ZwyTJWsODK){JeKDDBXiuX = true;}
      else if(ZwyTJWsODK == bEWyLKBrQo){jTFMmiUqyn = true;}
      if(OHapWmCdSD == FsEPGgZbJA){SauAutDeRj = true;}
      else if(FsEPGgZbJA == OHapWmCdSD){GZlJtncGwh = true;}
      if(iDARdFIpcA == aAXMDeLyYX){QMQeXZGzCy = true;}
      else if(aAXMDeLyYX == iDARdFIpcA){cPulBPGulA = true;}
      if(wLJRAlGfSx == XzOmeDWRci){qsIZFDFnGM = true;}
      else if(XzOmeDWRci == wLJRAlGfSx){kOrhkPAilQ = true;}
      if(uMjoQXGmEp == yMsaWnwuGO){dFWckDoADc = true;}
      else if(yMsaWnwuGO == uMjoQXGmEp){dFFlCQmzgd = true;}
      if(tEiMfYEFUF == JVJwlZYkPd){yrwEzwNfed = true;}
      else if(JVJwlZYkPd == tEiMfYEFUF){cTdNhTXSLW = true;}
      if(BLOPrDxJok == LuoflGeRjC){tXfwgZSVuq = true;}
      if(gWKUIVSKAF == KIyaBOGxpO){oPXEGKpnsU = true;}
      if(zUkmGrbxkb == iQqKOBoRAE){jGuZzyxDZI = true;}
      while(LuoflGeRjC == BLOPrDxJok){bYExCqgDXe = true;}
      while(KIyaBOGxpO == KIyaBOGxpO){mtTeEWKJjj = true;}
      while(iQqKOBoRAE == iQqKOBoRAE){cHNIXRjezQ = true;}
      if(dkBzXCXNoQ == true){dkBzXCXNoQ = false;}
      if(JeKDDBXiuX == true){JeKDDBXiuX = false;}
      if(SauAutDeRj == true){SauAutDeRj = false;}
      if(QMQeXZGzCy == true){QMQeXZGzCy = false;}
      if(qsIZFDFnGM == true){qsIZFDFnGM = false;}
      if(dFWckDoADc == true){dFWckDoADc = false;}
      if(yrwEzwNfed == true){yrwEzwNfed = false;}
      if(tXfwgZSVuq == true){tXfwgZSVuq = false;}
      if(oPXEGKpnsU == true){oPXEGKpnsU = false;}
      if(jGuZzyxDZI == true){jGuZzyxDZI = false;}
      if(pYIbRFZawL == true){pYIbRFZawL = false;}
      if(jTFMmiUqyn == true){jTFMmiUqyn = false;}
      if(GZlJtncGwh == true){GZlJtncGwh = false;}
      if(cPulBPGulA == true){cPulBPGulA = false;}
      if(kOrhkPAilQ == true){kOrhkPAilQ = false;}
      if(dFFlCQmzgd == true){dFFlCQmzgd = false;}
      if(cTdNhTXSLW == true){cTdNhTXSLW = false;}
      if(bYExCqgDXe == true){bYExCqgDXe = false;}
      if(mtTeEWKJjj == true){mtTeEWKJjj = false;}
      if(cHNIXRjezQ == true){cHNIXRjezQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AGHZOLOOWK
{ 
  void KxXgJNUokm()
  { 
      bool PFHIJyDelD = false;
      bool VEYQpFafXN = false;
      bool GSTXXgXkcC = false;
      bool KHwikOrAca = false;
      bool XgcAQbVFty = false;
      bool gpfSuxlikb = false;
      bool ZSCjrNHoea = false;
      bool NZCwpZoSHw = false;
      bool LRpdUUbcnn = false;
      bool cIPBBFerHC = false;
      bool TgaTkGmjcV = false;
      bool HTanQHbXPX = false;
      bool ldBqxEKBtj = false;
      bool twKFbdqVsO = false;
      bool gqzSfJhbjt = false;
      bool cGciPofiVf = false;
      bool wloraLIVMl = false;
      bool PFeAqtehLn = false;
      bool VhQAHmSbom = false;
      bool yIAMRtBGqU = false;
      string QUJjsVsXlD;
      string VEwEqiHkXF;
      string AxMDoiOICQ;
      string BSamhAurmc;
      string LKWAIYooGx;
      string kDlJcSHGuK;
      string HjVUBCdIWq;
      string nOxtsoaMtP;
      string sYCEeygQJO;
      string soxcUaoBzF;
      string ufSOJVFrPn;
      string ruLeQihQpC;
      string VMyHyyRUYS;
      string zYMnUNFmuI;
      string roBVVxcRLl;
      string sYLwjhgKQK;
      string EjSxnThXKD;
      string ctUgJgLclA;
      string UzJmZaMPDl;
      string fuWjEHVDgC;
      if(QUJjsVsXlD == ufSOJVFrPn){PFHIJyDelD = true;}
      else if(ufSOJVFrPn == QUJjsVsXlD){TgaTkGmjcV = true;}
      if(VEwEqiHkXF == ruLeQihQpC){VEYQpFafXN = true;}
      else if(ruLeQihQpC == VEwEqiHkXF){HTanQHbXPX = true;}
      if(AxMDoiOICQ == VMyHyyRUYS){GSTXXgXkcC = true;}
      else if(VMyHyyRUYS == AxMDoiOICQ){ldBqxEKBtj = true;}
      if(BSamhAurmc == zYMnUNFmuI){KHwikOrAca = true;}
      else if(zYMnUNFmuI == BSamhAurmc){twKFbdqVsO = true;}
      if(LKWAIYooGx == roBVVxcRLl){XgcAQbVFty = true;}
      else if(roBVVxcRLl == LKWAIYooGx){gqzSfJhbjt = true;}
      if(kDlJcSHGuK == sYLwjhgKQK){gpfSuxlikb = true;}
      else if(sYLwjhgKQK == kDlJcSHGuK){cGciPofiVf = true;}
      if(HjVUBCdIWq == EjSxnThXKD){ZSCjrNHoea = true;}
      else if(EjSxnThXKD == HjVUBCdIWq){wloraLIVMl = true;}
      if(nOxtsoaMtP == ctUgJgLclA){NZCwpZoSHw = true;}
      if(sYCEeygQJO == UzJmZaMPDl){LRpdUUbcnn = true;}
      if(soxcUaoBzF == fuWjEHVDgC){cIPBBFerHC = true;}
      while(ctUgJgLclA == nOxtsoaMtP){PFeAqtehLn = true;}
      while(UzJmZaMPDl == UzJmZaMPDl){VhQAHmSbom = true;}
      while(fuWjEHVDgC == fuWjEHVDgC){yIAMRtBGqU = true;}
      if(PFHIJyDelD == true){PFHIJyDelD = false;}
      if(VEYQpFafXN == true){VEYQpFafXN = false;}
      if(GSTXXgXkcC == true){GSTXXgXkcC = false;}
      if(KHwikOrAca == true){KHwikOrAca = false;}
      if(XgcAQbVFty == true){XgcAQbVFty = false;}
      if(gpfSuxlikb == true){gpfSuxlikb = false;}
      if(ZSCjrNHoea == true){ZSCjrNHoea = false;}
      if(NZCwpZoSHw == true){NZCwpZoSHw = false;}
      if(LRpdUUbcnn == true){LRpdUUbcnn = false;}
      if(cIPBBFerHC == true){cIPBBFerHC = false;}
      if(TgaTkGmjcV == true){TgaTkGmjcV = false;}
      if(HTanQHbXPX == true){HTanQHbXPX = false;}
      if(ldBqxEKBtj == true){ldBqxEKBtj = false;}
      if(twKFbdqVsO == true){twKFbdqVsO = false;}
      if(gqzSfJhbjt == true){gqzSfJhbjt = false;}
      if(cGciPofiVf == true){cGciPofiVf = false;}
      if(wloraLIVMl == true){wloraLIVMl = false;}
      if(PFeAqtehLn == true){PFeAqtehLn = false;}
      if(VhQAHmSbom == true){VhQAHmSbom = false;}
      if(yIAMRtBGqU == true){yIAMRtBGqU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJOAODHVXA
{ 
  void TYMfdoxZPA()
  { 
      bool cRSiAfRAXN = false;
      bool mrKtSsaSLO = false;
      bool DsJNjgCXMF = false;
      bool VlasqElzqS = false;
      bool oOzBKjmqiH = false;
      bool YeCEUjIEzS = false;
      bool csmSqAQRDN = false;
      bool HbbsYnsHCz = false;
      bool tKoEfpiVXG = false;
      bool wgzYoubfJJ = false;
      bool TUnUAwDJef = false;
      bool pBCAXREhlB = false;
      bool RuswRZcDDc = false;
      bool MNxreYWTEj = false;
      bool mZpqQudyAX = false;
      bool qstIrYarCZ = false;
      bool TAFBTcDKUz = false;
      bool ujdCNrEBeW = false;
      bool wdCflSTnzG = false;
      bool xeRdPmTnXn = false;
      string ZLXnIEyjNE;
      string GlaeuUikNJ;
      string aYAqpxmeYU;
      string pkKjlVtYiD;
      string eTTGgpMcBd;
      string oqsHaAKfxL;
      string QTLrNVbqsY;
      string aJCKdHEsJA;
      string jKdteyrCIl;
      string KNaWlKIbrL;
      string NUjcDfoicT;
      string uRWxaGpQNO;
      string dZiHNNheXS;
      string ycAxlOaBqz;
      string JJYnpsqdwf;
      string UqOchnlbOo;
      string xJKJVRQYLM;
      string foZOFTBtQT;
      string WEiqyGOWPy;
      string cylBBzyOSX;
      if(ZLXnIEyjNE == NUjcDfoicT){cRSiAfRAXN = true;}
      else if(NUjcDfoicT == ZLXnIEyjNE){TUnUAwDJef = true;}
      if(GlaeuUikNJ == uRWxaGpQNO){mrKtSsaSLO = true;}
      else if(uRWxaGpQNO == GlaeuUikNJ){pBCAXREhlB = true;}
      if(aYAqpxmeYU == dZiHNNheXS){DsJNjgCXMF = true;}
      else if(dZiHNNheXS == aYAqpxmeYU){RuswRZcDDc = true;}
      if(pkKjlVtYiD == ycAxlOaBqz){VlasqElzqS = true;}
      else if(ycAxlOaBqz == pkKjlVtYiD){MNxreYWTEj = true;}
      if(eTTGgpMcBd == JJYnpsqdwf){oOzBKjmqiH = true;}
      else if(JJYnpsqdwf == eTTGgpMcBd){mZpqQudyAX = true;}
      if(oqsHaAKfxL == UqOchnlbOo){YeCEUjIEzS = true;}
      else if(UqOchnlbOo == oqsHaAKfxL){qstIrYarCZ = true;}
      if(QTLrNVbqsY == xJKJVRQYLM){csmSqAQRDN = true;}
      else if(xJKJVRQYLM == QTLrNVbqsY){TAFBTcDKUz = true;}
      if(aJCKdHEsJA == foZOFTBtQT){HbbsYnsHCz = true;}
      if(jKdteyrCIl == WEiqyGOWPy){tKoEfpiVXG = true;}
      if(KNaWlKIbrL == cylBBzyOSX){wgzYoubfJJ = true;}
      while(foZOFTBtQT == aJCKdHEsJA){ujdCNrEBeW = true;}
      while(WEiqyGOWPy == WEiqyGOWPy){wdCflSTnzG = true;}
      while(cylBBzyOSX == cylBBzyOSX){xeRdPmTnXn = true;}
      if(cRSiAfRAXN == true){cRSiAfRAXN = false;}
      if(mrKtSsaSLO == true){mrKtSsaSLO = false;}
      if(DsJNjgCXMF == true){DsJNjgCXMF = false;}
      if(VlasqElzqS == true){VlasqElzqS = false;}
      if(oOzBKjmqiH == true){oOzBKjmqiH = false;}
      if(YeCEUjIEzS == true){YeCEUjIEzS = false;}
      if(csmSqAQRDN == true){csmSqAQRDN = false;}
      if(HbbsYnsHCz == true){HbbsYnsHCz = false;}
      if(tKoEfpiVXG == true){tKoEfpiVXG = false;}
      if(wgzYoubfJJ == true){wgzYoubfJJ = false;}
      if(TUnUAwDJef == true){TUnUAwDJef = false;}
      if(pBCAXREhlB == true){pBCAXREhlB = false;}
      if(RuswRZcDDc == true){RuswRZcDDc = false;}
      if(MNxreYWTEj == true){MNxreYWTEj = false;}
      if(mZpqQudyAX == true){mZpqQudyAX = false;}
      if(qstIrYarCZ == true){qstIrYarCZ = false;}
      if(TAFBTcDKUz == true){TAFBTcDKUz = false;}
      if(ujdCNrEBeW == true){ujdCNrEBeW = false;}
      if(wdCflSTnzG == true){wdCflSTnzG = false;}
      if(xeRdPmTnXn == true){xeRdPmTnXn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XKHRSSGKLT
{ 
  void cKokxbqtlk()
  { 
      bool BYSDzefKzr = false;
      bool hbyjWdOKcY = false;
      bool PcQOrGFrnH = false;
      bool SfCSQFDKcC = false;
      bool xETcqDPgKE = false;
      bool NqquHXHDLs = false;
      bool ZnWqZCZeSQ = false;
      bool ZEhabKJnWn = false;
      bool pXgitanGKr = false;
      bool xAzibJhbDo = false;
      bool cjNsdJJQTw = false;
      bool OTgWDBGmwy = false;
      bool NTTaTZEyyR = false;
      bool cgjhKFKmEk = false;
      bool RXmNcdTbfa = false;
      bool CtfEaJQmZE = false;
      bool EKRBThiyLx = false;
      bool qShKgogFxo = false;
      bool GcSXOhBfGB = false;
      bool oXNAgGGktu = false;
      string IqjPEEbJpb;
      string ezuXdXGekm;
      string jsQKsZwGfW;
      string NwspwUEZJy;
      string MoHnGUAKYJ;
      string KnWTfPZYVd;
      string IVdSOiFFaI;
      string TgUmZtlbEY;
      string ZkgWMYYYJg;
      string teDeppLnZW;
      string PtiPocSjtl;
      string cyTxDWnGGp;
      string JfutNocpwi;
      string ixChIeCRgi;
      string FoeXDwKGbT;
      string BFhjMizoBA;
      string AcmKDfulnX;
      string TWYWjUAWpR;
      string dVOcgdPSUZ;
      string fNQgibCUUX;
      if(IqjPEEbJpb == PtiPocSjtl){BYSDzefKzr = true;}
      else if(PtiPocSjtl == IqjPEEbJpb){cjNsdJJQTw = true;}
      if(ezuXdXGekm == cyTxDWnGGp){hbyjWdOKcY = true;}
      else if(cyTxDWnGGp == ezuXdXGekm){OTgWDBGmwy = true;}
      if(jsQKsZwGfW == JfutNocpwi){PcQOrGFrnH = true;}
      else if(JfutNocpwi == jsQKsZwGfW){NTTaTZEyyR = true;}
      if(NwspwUEZJy == ixChIeCRgi){SfCSQFDKcC = true;}
      else if(ixChIeCRgi == NwspwUEZJy){cgjhKFKmEk = true;}
      if(MoHnGUAKYJ == FoeXDwKGbT){xETcqDPgKE = true;}
      else if(FoeXDwKGbT == MoHnGUAKYJ){RXmNcdTbfa = true;}
      if(KnWTfPZYVd == BFhjMizoBA){NqquHXHDLs = true;}
      else if(BFhjMizoBA == KnWTfPZYVd){CtfEaJQmZE = true;}
      if(IVdSOiFFaI == AcmKDfulnX){ZnWqZCZeSQ = true;}
      else if(AcmKDfulnX == IVdSOiFFaI){EKRBThiyLx = true;}
      if(TgUmZtlbEY == TWYWjUAWpR){ZEhabKJnWn = true;}
      if(ZkgWMYYYJg == dVOcgdPSUZ){pXgitanGKr = true;}
      if(teDeppLnZW == fNQgibCUUX){xAzibJhbDo = true;}
      while(TWYWjUAWpR == TgUmZtlbEY){qShKgogFxo = true;}
      while(dVOcgdPSUZ == dVOcgdPSUZ){GcSXOhBfGB = true;}
      while(fNQgibCUUX == fNQgibCUUX){oXNAgGGktu = true;}
      if(BYSDzefKzr == true){BYSDzefKzr = false;}
      if(hbyjWdOKcY == true){hbyjWdOKcY = false;}
      if(PcQOrGFrnH == true){PcQOrGFrnH = false;}
      if(SfCSQFDKcC == true){SfCSQFDKcC = false;}
      if(xETcqDPgKE == true){xETcqDPgKE = false;}
      if(NqquHXHDLs == true){NqquHXHDLs = false;}
      if(ZnWqZCZeSQ == true){ZnWqZCZeSQ = false;}
      if(ZEhabKJnWn == true){ZEhabKJnWn = false;}
      if(pXgitanGKr == true){pXgitanGKr = false;}
      if(xAzibJhbDo == true){xAzibJhbDo = false;}
      if(cjNsdJJQTw == true){cjNsdJJQTw = false;}
      if(OTgWDBGmwy == true){OTgWDBGmwy = false;}
      if(NTTaTZEyyR == true){NTTaTZEyyR = false;}
      if(cgjhKFKmEk == true){cgjhKFKmEk = false;}
      if(RXmNcdTbfa == true){RXmNcdTbfa = false;}
      if(CtfEaJQmZE == true){CtfEaJQmZE = false;}
      if(EKRBThiyLx == true){EKRBThiyLx = false;}
      if(qShKgogFxo == true){qShKgogFxo = false;}
      if(GcSXOhBfGB == true){GcSXOhBfGB = false;}
      if(oXNAgGGktu == true){oXNAgGGktu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TOMKZBDPRF
{ 
  void QuKjyyOmCu()
  { 
      bool HykQAQFdJz = false;
      bool ZmeBVgwBQZ = false;
      bool aDCJzemNJc = false;
      bool FfIYHLnChF = false;
      bool cgTWmnzHlw = false;
      bool gWmBAEwbQU = false;
      bool drTftseFtK = false;
      bool stSLwtifVK = false;
      bool ffaMwhsHXC = false;
      bool OMkNbkMmbt = false;
      bool JsMbDlDbEG = false;
      bool UQFGoyQHjL = false;
      bool zXhrufJFiK = false;
      bool huDbBlSzJK = false;
      bool eQCRgyGeXd = false;
      bool TFDPtlLUfW = false;
      bool cxrsXZMdED = false;
      bool eRxZfiUPKw = false;
      bool YehFpcqmgP = false;
      bool aySlghXIsH = false;
      string fnxEYyyIro;
      string MxAsaOwLQO;
      string DBzHwIfitw;
      string UlDaFGkLiu;
      string yCjlqiQeoq;
      string YBznVeooIQ;
      string SPOuTZsZmU;
      string cjbVQAQMQN;
      string qAtCXSmPFa;
      string QwCRchnoRQ;
      string oqqTNnZdWU;
      string NbYuZSVLXA;
      string mdTMDggJsi;
      string LbuzXzIZoj;
      string sJrjMnWHqJ;
      string McRQdKWeQf;
      string GPknJkgYWa;
      string JuWmHdkjzO;
      string JYSiWiKdVM;
      string bdIIddYEaa;
      if(fnxEYyyIro == oqqTNnZdWU){HykQAQFdJz = true;}
      else if(oqqTNnZdWU == fnxEYyyIro){JsMbDlDbEG = true;}
      if(MxAsaOwLQO == NbYuZSVLXA){ZmeBVgwBQZ = true;}
      else if(NbYuZSVLXA == MxAsaOwLQO){UQFGoyQHjL = true;}
      if(DBzHwIfitw == mdTMDggJsi){aDCJzemNJc = true;}
      else if(mdTMDggJsi == DBzHwIfitw){zXhrufJFiK = true;}
      if(UlDaFGkLiu == LbuzXzIZoj){FfIYHLnChF = true;}
      else if(LbuzXzIZoj == UlDaFGkLiu){huDbBlSzJK = true;}
      if(yCjlqiQeoq == sJrjMnWHqJ){cgTWmnzHlw = true;}
      else if(sJrjMnWHqJ == yCjlqiQeoq){eQCRgyGeXd = true;}
      if(YBznVeooIQ == McRQdKWeQf){gWmBAEwbQU = true;}
      else if(McRQdKWeQf == YBznVeooIQ){TFDPtlLUfW = true;}
      if(SPOuTZsZmU == GPknJkgYWa){drTftseFtK = true;}
      else if(GPknJkgYWa == SPOuTZsZmU){cxrsXZMdED = true;}
      if(cjbVQAQMQN == JuWmHdkjzO){stSLwtifVK = true;}
      if(qAtCXSmPFa == JYSiWiKdVM){ffaMwhsHXC = true;}
      if(QwCRchnoRQ == bdIIddYEaa){OMkNbkMmbt = true;}
      while(JuWmHdkjzO == cjbVQAQMQN){eRxZfiUPKw = true;}
      while(JYSiWiKdVM == JYSiWiKdVM){YehFpcqmgP = true;}
      while(bdIIddYEaa == bdIIddYEaa){aySlghXIsH = true;}
      if(HykQAQFdJz == true){HykQAQFdJz = false;}
      if(ZmeBVgwBQZ == true){ZmeBVgwBQZ = false;}
      if(aDCJzemNJc == true){aDCJzemNJc = false;}
      if(FfIYHLnChF == true){FfIYHLnChF = false;}
      if(cgTWmnzHlw == true){cgTWmnzHlw = false;}
      if(gWmBAEwbQU == true){gWmBAEwbQU = false;}
      if(drTftseFtK == true){drTftseFtK = false;}
      if(stSLwtifVK == true){stSLwtifVK = false;}
      if(ffaMwhsHXC == true){ffaMwhsHXC = false;}
      if(OMkNbkMmbt == true){OMkNbkMmbt = false;}
      if(JsMbDlDbEG == true){JsMbDlDbEG = false;}
      if(UQFGoyQHjL == true){UQFGoyQHjL = false;}
      if(zXhrufJFiK == true){zXhrufJFiK = false;}
      if(huDbBlSzJK == true){huDbBlSzJK = false;}
      if(eQCRgyGeXd == true){eQCRgyGeXd = false;}
      if(TFDPtlLUfW == true){TFDPtlLUfW = false;}
      if(cxrsXZMdED == true){cxrsXZMdED = false;}
      if(eRxZfiUPKw == true){eRxZfiUPKw = false;}
      if(YehFpcqmgP == true){YehFpcqmgP = false;}
      if(aySlghXIsH == true){aySlghXIsH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AQYLZLZPQK
{ 
  void cVmwktjrMU()
  { 
      bool UZwyaYjxDi = false;
      bool rUaKpbUxls = false;
      bool YHogdJVYrr = false;
      bool rKVcslbtCQ = false;
      bool KCpKtGoxId = false;
      bool wHtIgNjPUQ = false;
      bool CKFKqhyyRD = false;
      bool AatViVQemX = false;
      bool UYQNwkQNue = false;
      bool BMZlNzxfTM = false;
      bool HpeEcUMXYK = false;
      bool wFcwwdtqNF = false;
      bool RjCmCnBIHi = false;
      bool XkKZPdsLkb = false;
      bool Yrnkhwicoi = false;
      bool FGROuXnrCo = false;
      bool SDQplLuCfR = false;
      bool jhGlgZuREG = false;
      bool EYSYcRSwer = false;
      bool pBJuIUayyV = false;
      string LRCMaZbmoJ;
      string ipubVKCCZh;
      string HwwGQadVpm;
      string bVLBPDRDbu;
      string WbBkWMAicQ;
      string okjgVPVuuz;
      string uFwBgNdsMS;
      string ryZeKfuLjE;
      string aurYxqkeez;
      string gVIcAQezDI;
      string hGVKYqLFVo;
      string UJLqYzMXEp;
      string czNMkWpxdt;
      string BuHaVTYhAG;
      string ffIpeWKREA;
      string EGuNfirJYB;
      string AOabnYBjUF;
      string ZeWxJxpXhN;
      string LYsdptAttm;
      string aPIyFREfBF;
      if(LRCMaZbmoJ == hGVKYqLFVo){UZwyaYjxDi = true;}
      else if(hGVKYqLFVo == LRCMaZbmoJ){HpeEcUMXYK = true;}
      if(ipubVKCCZh == UJLqYzMXEp){rUaKpbUxls = true;}
      else if(UJLqYzMXEp == ipubVKCCZh){wFcwwdtqNF = true;}
      if(HwwGQadVpm == czNMkWpxdt){YHogdJVYrr = true;}
      else if(czNMkWpxdt == HwwGQadVpm){RjCmCnBIHi = true;}
      if(bVLBPDRDbu == BuHaVTYhAG){rKVcslbtCQ = true;}
      else if(BuHaVTYhAG == bVLBPDRDbu){XkKZPdsLkb = true;}
      if(WbBkWMAicQ == ffIpeWKREA){KCpKtGoxId = true;}
      else if(ffIpeWKREA == WbBkWMAicQ){Yrnkhwicoi = true;}
      if(okjgVPVuuz == EGuNfirJYB){wHtIgNjPUQ = true;}
      else if(EGuNfirJYB == okjgVPVuuz){FGROuXnrCo = true;}
      if(uFwBgNdsMS == AOabnYBjUF){CKFKqhyyRD = true;}
      else if(AOabnYBjUF == uFwBgNdsMS){SDQplLuCfR = true;}
      if(ryZeKfuLjE == ZeWxJxpXhN){AatViVQemX = true;}
      if(aurYxqkeez == LYsdptAttm){UYQNwkQNue = true;}
      if(gVIcAQezDI == aPIyFREfBF){BMZlNzxfTM = true;}
      while(ZeWxJxpXhN == ryZeKfuLjE){jhGlgZuREG = true;}
      while(LYsdptAttm == LYsdptAttm){EYSYcRSwer = true;}
      while(aPIyFREfBF == aPIyFREfBF){pBJuIUayyV = true;}
      if(UZwyaYjxDi == true){UZwyaYjxDi = false;}
      if(rUaKpbUxls == true){rUaKpbUxls = false;}
      if(YHogdJVYrr == true){YHogdJVYrr = false;}
      if(rKVcslbtCQ == true){rKVcslbtCQ = false;}
      if(KCpKtGoxId == true){KCpKtGoxId = false;}
      if(wHtIgNjPUQ == true){wHtIgNjPUQ = false;}
      if(CKFKqhyyRD == true){CKFKqhyyRD = false;}
      if(AatViVQemX == true){AatViVQemX = false;}
      if(UYQNwkQNue == true){UYQNwkQNue = false;}
      if(BMZlNzxfTM == true){BMZlNzxfTM = false;}
      if(HpeEcUMXYK == true){HpeEcUMXYK = false;}
      if(wFcwwdtqNF == true){wFcwwdtqNF = false;}
      if(RjCmCnBIHi == true){RjCmCnBIHi = false;}
      if(XkKZPdsLkb == true){XkKZPdsLkb = false;}
      if(Yrnkhwicoi == true){Yrnkhwicoi = false;}
      if(FGROuXnrCo == true){FGROuXnrCo = false;}
      if(SDQplLuCfR == true){SDQplLuCfR = false;}
      if(jhGlgZuREG == true){jhGlgZuREG = false;}
      if(EYSYcRSwer == true){EYSYcRSwer = false;}
      if(pBJuIUayyV == true){pBJuIUayyV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEGTRUAWGK
{ 
  void dXSwtxGJDo()
  { 
      bool sygLoRQeeI = false;
      bool DKKQLcqqAX = false;
      bool uslddltZjb = false;
      bool sNjjERgwjH = false;
      bool UOskXlsmTt = false;
      bool dqDKgzLDgD = false;
      bool XpuDOpZaMs = false;
      bool wtHsDfAAGq = false;
      bool sHGpxBJZCF = false;
      bool GdOgidTpVh = false;
      bool MSaayijKGA = false;
      bool zLwpJPjFFN = false;
      bool fAXGmSeZJY = false;
      bool MJdXeagfrO = false;
      bool RzSBGugYWS = false;
      bool tOjIBLtTne = false;
      bool DJAhmogXLi = false;
      bool iEMquggVAq = false;
      bool kGDpeyYVWS = false;
      bool gMqMKHykNQ = false;
      string xjPgewDoTO;
      string zVfVmqocAE;
      string OiTITSzAwo;
      string kzeMDxAByu;
      string iZpXNGGUMP;
      string gXbkEOQHNM;
      string wDredzpSSp;
      string pneEVnrutM;
      string MdnfHMWtIn;
      string gsmkyfgKsN;
      string QmCWYrrWPQ;
      string WUNBzSPLXQ;
      string cwKdIxAsFp;
      string GgBfuYbQHP;
      string TAdrRLfllf;
      string QUmbkUcXNb;
      string qzQZJoSgFZ;
      string pyEHxcRSMx;
      string QOHZYktYta;
      string wEDeXUiEhc;
      if(xjPgewDoTO == QmCWYrrWPQ){sygLoRQeeI = true;}
      else if(QmCWYrrWPQ == xjPgewDoTO){MSaayijKGA = true;}
      if(zVfVmqocAE == WUNBzSPLXQ){DKKQLcqqAX = true;}
      else if(WUNBzSPLXQ == zVfVmqocAE){zLwpJPjFFN = true;}
      if(OiTITSzAwo == cwKdIxAsFp){uslddltZjb = true;}
      else if(cwKdIxAsFp == OiTITSzAwo){fAXGmSeZJY = true;}
      if(kzeMDxAByu == GgBfuYbQHP){sNjjERgwjH = true;}
      else if(GgBfuYbQHP == kzeMDxAByu){MJdXeagfrO = true;}
      if(iZpXNGGUMP == TAdrRLfllf){UOskXlsmTt = true;}
      else if(TAdrRLfllf == iZpXNGGUMP){RzSBGugYWS = true;}
      if(gXbkEOQHNM == QUmbkUcXNb){dqDKgzLDgD = true;}
      else if(QUmbkUcXNb == gXbkEOQHNM){tOjIBLtTne = true;}
      if(wDredzpSSp == qzQZJoSgFZ){XpuDOpZaMs = true;}
      else if(qzQZJoSgFZ == wDredzpSSp){DJAhmogXLi = true;}
      if(pneEVnrutM == pyEHxcRSMx){wtHsDfAAGq = true;}
      if(MdnfHMWtIn == QOHZYktYta){sHGpxBJZCF = true;}
      if(gsmkyfgKsN == wEDeXUiEhc){GdOgidTpVh = true;}
      while(pyEHxcRSMx == pneEVnrutM){iEMquggVAq = true;}
      while(QOHZYktYta == QOHZYktYta){kGDpeyYVWS = true;}
      while(wEDeXUiEhc == wEDeXUiEhc){gMqMKHykNQ = true;}
      if(sygLoRQeeI == true){sygLoRQeeI = false;}
      if(DKKQLcqqAX == true){DKKQLcqqAX = false;}
      if(uslddltZjb == true){uslddltZjb = false;}
      if(sNjjERgwjH == true){sNjjERgwjH = false;}
      if(UOskXlsmTt == true){UOskXlsmTt = false;}
      if(dqDKgzLDgD == true){dqDKgzLDgD = false;}
      if(XpuDOpZaMs == true){XpuDOpZaMs = false;}
      if(wtHsDfAAGq == true){wtHsDfAAGq = false;}
      if(sHGpxBJZCF == true){sHGpxBJZCF = false;}
      if(GdOgidTpVh == true){GdOgidTpVh = false;}
      if(MSaayijKGA == true){MSaayijKGA = false;}
      if(zLwpJPjFFN == true){zLwpJPjFFN = false;}
      if(fAXGmSeZJY == true){fAXGmSeZJY = false;}
      if(MJdXeagfrO == true){MJdXeagfrO = false;}
      if(RzSBGugYWS == true){RzSBGugYWS = false;}
      if(tOjIBLtTne == true){tOjIBLtTne = false;}
      if(DJAhmogXLi == true){DJAhmogXLi = false;}
      if(iEMquggVAq == true){iEMquggVAq = false;}
      if(kGDpeyYVWS == true){kGDpeyYVWS = false;}
      if(gMqMKHykNQ == true){gMqMKHykNQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWUUMPEZLX
{ 
  void eHaUGzJjMP()
  { 
      bool cTJoULABOw = false;
      bool fwpepHzOxw = false;
      bool XeygrBZflu = false;
      bool oWSzpjMgTA = false;
      bool WPbcWbrIuE = false;
      bool gzDKRxVcxS = false;
      bool lTOSHJcpnG = false;
      bool tStxYHCUJQ = false;
      bool JRjhNoTHhr = false;
      bool OjiBODAJVN = false;
      bool yBToKOEGkJ = false;
      bool tATgJTjgER = false;
      bool pUIuqKishV = false;
      bool HszwRHyuWz = false;
      bool kMVXxOPCqt = false;
      bool TTEDWcsYxA = false;
      bool fKXOCBAXOC = false;
      bool VnJFfcykxc = false;
      bool tfBmCmnuYn = false;
      bool NZxWTZoHVw = false;
      string krnPLmlaLM;
      string BGqEVRdlYi;
      string xWqxagWlCk;
      string lQOCyCfZtX;
      string YpQrEeNGjc;
      string ynAGQNBpnd;
      string QAYaZkqnFT;
      string lDqBKHGysu;
      string TPBYlxPHkk;
      string BolPGXRoST;
      string nYAQquwywJ;
      string GCxrKAyzoc;
      string UiCUSwQaul;
      string oRfYHtPkgp;
      string BRLbeyrtFG;
      string YRAozEWfyu;
      string dUDKToVXjP;
      string kNRyaCXaoT;
      string EWVoMWQpZD;
      string XimlLfNBHp;
      if(krnPLmlaLM == nYAQquwywJ){cTJoULABOw = true;}
      else if(nYAQquwywJ == krnPLmlaLM){yBToKOEGkJ = true;}
      if(BGqEVRdlYi == GCxrKAyzoc){fwpepHzOxw = true;}
      else if(GCxrKAyzoc == BGqEVRdlYi){tATgJTjgER = true;}
      if(xWqxagWlCk == UiCUSwQaul){XeygrBZflu = true;}
      else if(UiCUSwQaul == xWqxagWlCk){pUIuqKishV = true;}
      if(lQOCyCfZtX == oRfYHtPkgp){oWSzpjMgTA = true;}
      else if(oRfYHtPkgp == lQOCyCfZtX){HszwRHyuWz = true;}
      if(YpQrEeNGjc == BRLbeyrtFG){WPbcWbrIuE = true;}
      else if(BRLbeyrtFG == YpQrEeNGjc){kMVXxOPCqt = true;}
      if(ynAGQNBpnd == YRAozEWfyu){gzDKRxVcxS = true;}
      else if(YRAozEWfyu == ynAGQNBpnd){TTEDWcsYxA = true;}
      if(QAYaZkqnFT == dUDKToVXjP){lTOSHJcpnG = true;}
      else if(dUDKToVXjP == QAYaZkqnFT){fKXOCBAXOC = true;}
      if(lDqBKHGysu == kNRyaCXaoT){tStxYHCUJQ = true;}
      if(TPBYlxPHkk == EWVoMWQpZD){JRjhNoTHhr = true;}
      if(BolPGXRoST == XimlLfNBHp){OjiBODAJVN = true;}
      while(kNRyaCXaoT == lDqBKHGysu){VnJFfcykxc = true;}
      while(EWVoMWQpZD == EWVoMWQpZD){tfBmCmnuYn = true;}
      while(XimlLfNBHp == XimlLfNBHp){NZxWTZoHVw = true;}
      if(cTJoULABOw == true){cTJoULABOw = false;}
      if(fwpepHzOxw == true){fwpepHzOxw = false;}
      if(XeygrBZflu == true){XeygrBZflu = false;}
      if(oWSzpjMgTA == true){oWSzpjMgTA = false;}
      if(WPbcWbrIuE == true){WPbcWbrIuE = false;}
      if(gzDKRxVcxS == true){gzDKRxVcxS = false;}
      if(lTOSHJcpnG == true){lTOSHJcpnG = false;}
      if(tStxYHCUJQ == true){tStxYHCUJQ = false;}
      if(JRjhNoTHhr == true){JRjhNoTHhr = false;}
      if(OjiBODAJVN == true){OjiBODAJVN = false;}
      if(yBToKOEGkJ == true){yBToKOEGkJ = false;}
      if(tATgJTjgER == true){tATgJTjgER = false;}
      if(pUIuqKishV == true){pUIuqKishV = false;}
      if(HszwRHyuWz == true){HszwRHyuWz = false;}
      if(kMVXxOPCqt == true){kMVXxOPCqt = false;}
      if(TTEDWcsYxA == true){TTEDWcsYxA = false;}
      if(fKXOCBAXOC == true){fKXOCBAXOC = false;}
      if(VnJFfcykxc == true){VnJFfcykxc = false;}
      if(tfBmCmnuYn == true){tfBmCmnuYn = false;}
      if(NZxWTZoHVw == true){NZxWTZoHVw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NYEZRXYTIW
{ 
  void RMdEwHAEKT()
  { 
      bool epwdfssKwr = false;
      bool ZtTkFNgeUD = false;
      bool gKPILhdqYk = false;
      bool UHMqZrdLPL = false;
      bool TmfCQezhAW = false;
      bool WKMVeUZmRy = false;
      bool PCkLXShcKM = false;
      bool jUPJisdNrg = false;
      bool iwpBOJtpLF = false;
      bool RpsRwRBUdx = false;
      bool wVXnmBuCmk = false;
      bool pMtjPSLixN = false;
      bool XqREtsbyNQ = false;
      bool qIitjNXBOM = false;
      bool OqDaPFwJBc = false;
      bool FRXQZFDSss = false;
      bool ZxoVsgdzzC = false;
      bool tKUjzfnqoo = false;
      bool xSwjLYkSUe = false;
      bool JFIVlQCggh = false;
      string PFFaCKUpgE;
      string iYEumrsLdc;
      string dtkPECKmgO;
      string lgxSLqzWCZ;
      string gqWTimrCMP;
      string fjJSHVToWz;
      string AhISRBaljw;
      string sVIDulWQfR;
      string KIZQiCXeKo;
      string WJADZzhEBg;
      string LGRQWJbFWU;
      string yDJEnrHqiP;
      string dwatZiVEdw;
      string ESOyFDpJtY;
      string aSHoqTAuOh;
      string qpUlDOeWqn;
      string nWbZQenKzk;
      string BxxKoLokCF;
      string hZpwFNyctp;
      string YSSGkDpgYL;
      if(PFFaCKUpgE == LGRQWJbFWU){epwdfssKwr = true;}
      else if(LGRQWJbFWU == PFFaCKUpgE){wVXnmBuCmk = true;}
      if(iYEumrsLdc == yDJEnrHqiP){ZtTkFNgeUD = true;}
      else if(yDJEnrHqiP == iYEumrsLdc){pMtjPSLixN = true;}
      if(dtkPECKmgO == dwatZiVEdw){gKPILhdqYk = true;}
      else if(dwatZiVEdw == dtkPECKmgO){XqREtsbyNQ = true;}
      if(lgxSLqzWCZ == ESOyFDpJtY){UHMqZrdLPL = true;}
      else if(ESOyFDpJtY == lgxSLqzWCZ){qIitjNXBOM = true;}
      if(gqWTimrCMP == aSHoqTAuOh){TmfCQezhAW = true;}
      else if(aSHoqTAuOh == gqWTimrCMP){OqDaPFwJBc = true;}
      if(fjJSHVToWz == qpUlDOeWqn){WKMVeUZmRy = true;}
      else if(qpUlDOeWqn == fjJSHVToWz){FRXQZFDSss = true;}
      if(AhISRBaljw == nWbZQenKzk){PCkLXShcKM = true;}
      else if(nWbZQenKzk == AhISRBaljw){ZxoVsgdzzC = true;}
      if(sVIDulWQfR == BxxKoLokCF){jUPJisdNrg = true;}
      if(KIZQiCXeKo == hZpwFNyctp){iwpBOJtpLF = true;}
      if(WJADZzhEBg == YSSGkDpgYL){RpsRwRBUdx = true;}
      while(BxxKoLokCF == sVIDulWQfR){tKUjzfnqoo = true;}
      while(hZpwFNyctp == hZpwFNyctp){xSwjLYkSUe = true;}
      while(YSSGkDpgYL == YSSGkDpgYL){JFIVlQCggh = true;}
      if(epwdfssKwr == true){epwdfssKwr = false;}
      if(ZtTkFNgeUD == true){ZtTkFNgeUD = false;}
      if(gKPILhdqYk == true){gKPILhdqYk = false;}
      if(UHMqZrdLPL == true){UHMqZrdLPL = false;}
      if(TmfCQezhAW == true){TmfCQezhAW = false;}
      if(WKMVeUZmRy == true){WKMVeUZmRy = false;}
      if(PCkLXShcKM == true){PCkLXShcKM = false;}
      if(jUPJisdNrg == true){jUPJisdNrg = false;}
      if(iwpBOJtpLF == true){iwpBOJtpLF = false;}
      if(RpsRwRBUdx == true){RpsRwRBUdx = false;}
      if(wVXnmBuCmk == true){wVXnmBuCmk = false;}
      if(pMtjPSLixN == true){pMtjPSLixN = false;}
      if(XqREtsbyNQ == true){XqREtsbyNQ = false;}
      if(qIitjNXBOM == true){qIitjNXBOM = false;}
      if(OqDaPFwJBc == true){OqDaPFwJBc = false;}
      if(FRXQZFDSss == true){FRXQZFDSss = false;}
      if(ZxoVsgdzzC == true){ZxoVsgdzzC = false;}
      if(tKUjzfnqoo == true){tKUjzfnqoo = false;}
      if(xSwjLYkSUe == true){xSwjLYkSUe = false;}
      if(JFIVlQCggh == true){JFIVlQCggh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KZTKOZQOUF
{ 
  void RelXWyrfNT()
  { 
      bool EDbmQYNIqR = false;
      bool cGYflFmYys = false;
      bool UUYOeMfCBh = false;
      bool CFeZHkjStP = false;
      bool bzYqQezeAe = false;
      bool iyKWrjdMIE = false;
      bool sLHIOWayYA = false;
      bool VTdiQVwhyz = false;
      bool MABVyDuHhW = false;
      bool HWKpVQrPbt = false;
      bool DBGzJPTbGV = false;
      bool nwOJqsJkKK = false;
      bool aTQBsyJmMz = false;
      bool dgGEuLsCLh = false;
      bool jTBLiLIBzc = false;
      bool HGFQSjjEFL = false;
      bool GgOGqGoKNe = false;
      bool zHZbaHRFRh = false;
      bool oHnirXbokK = false;
      bool aowzbDEtTb = false;
      string kEjhEMZiBd;
      string iKljxMkVLa;
      string iVfhyLPfLz;
      string puGLkKUMCW;
      string HfkDLIXogt;
      string kWnOhPYCir;
      string xtWCmnEZzm;
      string rYTnTDjbVp;
      string mayROSHrdU;
      string lRcJZMJhQW;
      string EyptCMDztd;
      string ewfsFWwFnT;
      string gMudBZuKOG;
      string tCLyknjEOB;
      string PHxzpokjDD;
      string QEtwprCLrb;
      string QsjnicjgIQ;
      string lqplEYOumL;
      string oLGLopHPIs;
      string lYLmkWWJQN;
      if(kEjhEMZiBd == EyptCMDztd){EDbmQYNIqR = true;}
      else if(EyptCMDztd == kEjhEMZiBd){DBGzJPTbGV = true;}
      if(iKljxMkVLa == ewfsFWwFnT){cGYflFmYys = true;}
      else if(ewfsFWwFnT == iKljxMkVLa){nwOJqsJkKK = true;}
      if(iVfhyLPfLz == gMudBZuKOG){UUYOeMfCBh = true;}
      else if(gMudBZuKOG == iVfhyLPfLz){aTQBsyJmMz = true;}
      if(puGLkKUMCW == tCLyknjEOB){CFeZHkjStP = true;}
      else if(tCLyknjEOB == puGLkKUMCW){dgGEuLsCLh = true;}
      if(HfkDLIXogt == PHxzpokjDD){bzYqQezeAe = true;}
      else if(PHxzpokjDD == HfkDLIXogt){jTBLiLIBzc = true;}
      if(kWnOhPYCir == QEtwprCLrb){iyKWrjdMIE = true;}
      else if(QEtwprCLrb == kWnOhPYCir){HGFQSjjEFL = true;}
      if(xtWCmnEZzm == QsjnicjgIQ){sLHIOWayYA = true;}
      else if(QsjnicjgIQ == xtWCmnEZzm){GgOGqGoKNe = true;}
      if(rYTnTDjbVp == lqplEYOumL){VTdiQVwhyz = true;}
      if(mayROSHrdU == oLGLopHPIs){MABVyDuHhW = true;}
      if(lRcJZMJhQW == lYLmkWWJQN){HWKpVQrPbt = true;}
      while(lqplEYOumL == rYTnTDjbVp){zHZbaHRFRh = true;}
      while(oLGLopHPIs == oLGLopHPIs){oHnirXbokK = true;}
      while(lYLmkWWJQN == lYLmkWWJQN){aowzbDEtTb = true;}
      if(EDbmQYNIqR == true){EDbmQYNIqR = false;}
      if(cGYflFmYys == true){cGYflFmYys = false;}
      if(UUYOeMfCBh == true){UUYOeMfCBh = false;}
      if(CFeZHkjStP == true){CFeZHkjStP = false;}
      if(bzYqQezeAe == true){bzYqQezeAe = false;}
      if(iyKWrjdMIE == true){iyKWrjdMIE = false;}
      if(sLHIOWayYA == true){sLHIOWayYA = false;}
      if(VTdiQVwhyz == true){VTdiQVwhyz = false;}
      if(MABVyDuHhW == true){MABVyDuHhW = false;}
      if(HWKpVQrPbt == true){HWKpVQrPbt = false;}
      if(DBGzJPTbGV == true){DBGzJPTbGV = false;}
      if(nwOJqsJkKK == true){nwOJqsJkKK = false;}
      if(aTQBsyJmMz == true){aTQBsyJmMz = false;}
      if(dgGEuLsCLh == true){dgGEuLsCLh = false;}
      if(jTBLiLIBzc == true){jTBLiLIBzc = false;}
      if(HGFQSjjEFL == true){HGFQSjjEFL = false;}
      if(GgOGqGoKNe == true){GgOGqGoKNe = false;}
      if(zHZbaHRFRh == true){zHZbaHRFRh = false;}
      if(oHnirXbokK == true){oHnirXbokK = false;}
      if(aowzbDEtTb == true){aowzbDEtTb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OEPINLFDAR
{ 
  void DTGuDCFjDk()
  { 
      bool qaOOHUCcuB = false;
      bool ifxEyIrHFZ = false;
      bool SQGBtSMAVt = false;
      bool KDdogVoCgP = false;
      bool zLeXHAptNp = false;
      bool yNVATaUMTn = false;
      bool HCHBpfCHWc = false;
      bool SoaoZGlhtt = false;
      bool cSmfwwhcVG = false;
      bool AcirHxEdgb = false;
      bool yhWjXImfZM = false;
      bool olSZKoOaEt = false;
      bool xYlQboGhgc = false;
      bool CHBRwuwCIn = false;
      bool IBDJROKIgS = false;
      bool hcYldYwFIh = false;
      bool BFzxKgkAdP = false;
      bool rMSQlwVbzN = false;
      bool eyAOtYhOmW = false;
      bool yptZlCCFzj = false;
      string VOFZzAmcpX;
      string VnBQqLxMDB;
      string NIshFCUmBb;
      string UFQuDCPcaP;
      string SLrVukwJZt;
      string rCmqxMVXUw;
      string fzaODPXFMo;
      string uTkmiCQXlT;
      string GKMGiRRZyp;
      string grIejSjcRf;
      string NqwkzXQzHu;
      string uxlApUlUel;
      string yxHWHDLGDQ;
      string RmGGGPNbHK;
      string BRRDtiGHoO;
      string fPyfgPjZcu;
      string MKwpcIqesZ;
      string HKMUkffDbY;
      string xERnkCoZYq;
      string fnyLypVbZl;
      if(VOFZzAmcpX == NqwkzXQzHu){qaOOHUCcuB = true;}
      else if(NqwkzXQzHu == VOFZzAmcpX){yhWjXImfZM = true;}
      if(VnBQqLxMDB == uxlApUlUel){ifxEyIrHFZ = true;}
      else if(uxlApUlUel == VnBQqLxMDB){olSZKoOaEt = true;}
      if(NIshFCUmBb == yxHWHDLGDQ){SQGBtSMAVt = true;}
      else if(yxHWHDLGDQ == NIshFCUmBb){xYlQboGhgc = true;}
      if(UFQuDCPcaP == RmGGGPNbHK){KDdogVoCgP = true;}
      else if(RmGGGPNbHK == UFQuDCPcaP){CHBRwuwCIn = true;}
      if(SLrVukwJZt == BRRDtiGHoO){zLeXHAptNp = true;}
      else if(BRRDtiGHoO == SLrVukwJZt){IBDJROKIgS = true;}
      if(rCmqxMVXUw == fPyfgPjZcu){yNVATaUMTn = true;}
      else if(fPyfgPjZcu == rCmqxMVXUw){hcYldYwFIh = true;}
      if(fzaODPXFMo == MKwpcIqesZ){HCHBpfCHWc = true;}
      else if(MKwpcIqesZ == fzaODPXFMo){BFzxKgkAdP = true;}
      if(uTkmiCQXlT == HKMUkffDbY){SoaoZGlhtt = true;}
      if(GKMGiRRZyp == xERnkCoZYq){cSmfwwhcVG = true;}
      if(grIejSjcRf == fnyLypVbZl){AcirHxEdgb = true;}
      while(HKMUkffDbY == uTkmiCQXlT){rMSQlwVbzN = true;}
      while(xERnkCoZYq == xERnkCoZYq){eyAOtYhOmW = true;}
      while(fnyLypVbZl == fnyLypVbZl){yptZlCCFzj = true;}
      if(qaOOHUCcuB == true){qaOOHUCcuB = false;}
      if(ifxEyIrHFZ == true){ifxEyIrHFZ = false;}
      if(SQGBtSMAVt == true){SQGBtSMAVt = false;}
      if(KDdogVoCgP == true){KDdogVoCgP = false;}
      if(zLeXHAptNp == true){zLeXHAptNp = false;}
      if(yNVATaUMTn == true){yNVATaUMTn = false;}
      if(HCHBpfCHWc == true){HCHBpfCHWc = false;}
      if(SoaoZGlhtt == true){SoaoZGlhtt = false;}
      if(cSmfwwhcVG == true){cSmfwwhcVG = false;}
      if(AcirHxEdgb == true){AcirHxEdgb = false;}
      if(yhWjXImfZM == true){yhWjXImfZM = false;}
      if(olSZKoOaEt == true){olSZKoOaEt = false;}
      if(xYlQboGhgc == true){xYlQboGhgc = false;}
      if(CHBRwuwCIn == true){CHBRwuwCIn = false;}
      if(IBDJROKIgS == true){IBDJROKIgS = false;}
      if(hcYldYwFIh == true){hcYldYwFIh = false;}
      if(BFzxKgkAdP == true){BFzxKgkAdP = false;}
      if(rMSQlwVbzN == true){rMSQlwVbzN = false;}
      if(eyAOtYhOmW == true){eyAOtYhOmW = false;}
      if(yptZlCCFzj == true){yptZlCCFzj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUMUUEBYXO
{ 
  void WVOxXoMlHr()
  { 
      bool QmEWTRiLLE = false;
      bool neLEqakbHl = false;
      bool XTWUkzbhyR = false;
      bool xpUAXllacy = false;
      bool HrbcnbwmZi = false;
      bool bAlRsxQikU = false;
      bool oAMtHxJLgF = false;
      bool nJyIdfqsgI = false;
      bool CoHOpwEDGZ = false;
      bool UCoIJGehVp = false;
      bool SkGTtRBcmN = false;
      bool FWCcSAryDK = false;
      bool sGEGjkUozW = false;
      bool BJXqpQhnTX = false;
      bool uaQsUyAMpI = false;
      bool NgdKwMgAiI = false;
      bool xLdPMuyKmB = false;
      bool SEdfPSpLkl = false;
      bool kIzqIUfMtc = false;
      bool jhEKaixAfZ = false;
      string iRlcgmIiWm;
      string RDKSRbZSlW;
      string FIhAAMRQhw;
      string TqIXRtxdmq;
      string fQfkgWtpbO;
      string HbrQpailbU;
      string VrAZSaumBW;
      string euetpncxSc;
      string RanSorzrhp;
      string KLBRVnPFRF;
      string bHnEjMwxZB;
      string ylSzCtDhka;
      string aCEKMStNYB;
      string YWeMBJljic;
      string uBRfrXsCPa;
      string khTqeYCdrR;
      string SiYXcaHFxr;
      string HTzIeZjXRn;
      string ZqxxQpDnhb;
      string GIqRKMbtDR;
      if(iRlcgmIiWm == bHnEjMwxZB){QmEWTRiLLE = true;}
      else if(bHnEjMwxZB == iRlcgmIiWm){SkGTtRBcmN = true;}
      if(RDKSRbZSlW == ylSzCtDhka){neLEqakbHl = true;}
      else if(ylSzCtDhka == RDKSRbZSlW){FWCcSAryDK = true;}
      if(FIhAAMRQhw == aCEKMStNYB){XTWUkzbhyR = true;}
      else if(aCEKMStNYB == FIhAAMRQhw){sGEGjkUozW = true;}
      if(TqIXRtxdmq == YWeMBJljic){xpUAXllacy = true;}
      else if(YWeMBJljic == TqIXRtxdmq){BJXqpQhnTX = true;}
      if(fQfkgWtpbO == uBRfrXsCPa){HrbcnbwmZi = true;}
      else if(uBRfrXsCPa == fQfkgWtpbO){uaQsUyAMpI = true;}
      if(HbrQpailbU == khTqeYCdrR){bAlRsxQikU = true;}
      else if(khTqeYCdrR == HbrQpailbU){NgdKwMgAiI = true;}
      if(VrAZSaumBW == SiYXcaHFxr){oAMtHxJLgF = true;}
      else if(SiYXcaHFxr == VrAZSaumBW){xLdPMuyKmB = true;}
      if(euetpncxSc == HTzIeZjXRn){nJyIdfqsgI = true;}
      if(RanSorzrhp == ZqxxQpDnhb){CoHOpwEDGZ = true;}
      if(KLBRVnPFRF == GIqRKMbtDR){UCoIJGehVp = true;}
      while(HTzIeZjXRn == euetpncxSc){SEdfPSpLkl = true;}
      while(ZqxxQpDnhb == ZqxxQpDnhb){kIzqIUfMtc = true;}
      while(GIqRKMbtDR == GIqRKMbtDR){jhEKaixAfZ = true;}
      if(QmEWTRiLLE == true){QmEWTRiLLE = false;}
      if(neLEqakbHl == true){neLEqakbHl = false;}
      if(XTWUkzbhyR == true){XTWUkzbhyR = false;}
      if(xpUAXllacy == true){xpUAXllacy = false;}
      if(HrbcnbwmZi == true){HrbcnbwmZi = false;}
      if(bAlRsxQikU == true){bAlRsxQikU = false;}
      if(oAMtHxJLgF == true){oAMtHxJLgF = false;}
      if(nJyIdfqsgI == true){nJyIdfqsgI = false;}
      if(CoHOpwEDGZ == true){CoHOpwEDGZ = false;}
      if(UCoIJGehVp == true){UCoIJGehVp = false;}
      if(SkGTtRBcmN == true){SkGTtRBcmN = false;}
      if(FWCcSAryDK == true){FWCcSAryDK = false;}
      if(sGEGjkUozW == true){sGEGjkUozW = false;}
      if(BJXqpQhnTX == true){BJXqpQhnTX = false;}
      if(uaQsUyAMpI == true){uaQsUyAMpI = false;}
      if(NgdKwMgAiI == true){NgdKwMgAiI = false;}
      if(xLdPMuyKmB == true){xLdPMuyKmB = false;}
      if(SEdfPSpLkl == true){SEdfPSpLkl = false;}
      if(kIzqIUfMtc == true){kIzqIUfMtc = false;}
      if(jhEKaixAfZ == true){jhEKaixAfZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WMKNSFHJYI
{ 
  void tdcWLpchdy()
  { 
      bool ynzOmQNnLg = false;
      bool atpAeluRJs = false;
      bool oTIqaQLZNz = false;
      bool GNWfZVxjZb = false;
      bool UrjIjNjJHI = false;
      bool KmNWFdfHmW = false;
      bool EmZMZMXJZI = false;
      bool oLrgXwjzGN = false;
      bool fCSFoTzzaw = false;
      bool powCXhSWiX = false;
      bool oaizTytfyI = false;
      bool tgAZpCUUWF = false;
      bool MXhdSzPoJp = false;
      bool dMQiXESSkp = false;
      bool YSBSCIoVMU = false;
      bool MyzcKRsFfU = false;
      bool iFWIdgPQCl = false;
      bool jCigfsWObJ = false;
      bool JscodfMmXG = false;
      bool LNlPGTwrnU = false;
      string GKDXzqmUQz;
      string auxfageUwW;
      string otAEyXKjRT;
      string DcVmazRDzr;
      string wRgRjzVMnC;
      string ILYKJMJzZb;
      string fCDxwyYJFb;
      string PbUDaXNhTy;
      string CywOKqELdO;
      string oRcXLtOjVl;
      string aMHLmgqVjk;
      string ybeaZhGnmF;
      string tNeplxyxqg;
      string JcLhXpqjbc;
      string AiarPNlCyd;
      string mZxQrMgQYo;
      string htdDbUPxCj;
      string qWMJFLllaY;
      string KwyMsifuoL;
      string IZKluFEXPt;
      if(GKDXzqmUQz == aMHLmgqVjk){ynzOmQNnLg = true;}
      else if(aMHLmgqVjk == GKDXzqmUQz){oaizTytfyI = true;}
      if(auxfageUwW == ybeaZhGnmF){atpAeluRJs = true;}
      else if(ybeaZhGnmF == auxfageUwW){tgAZpCUUWF = true;}
      if(otAEyXKjRT == tNeplxyxqg){oTIqaQLZNz = true;}
      else if(tNeplxyxqg == otAEyXKjRT){MXhdSzPoJp = true;}
      if(DcVmazRDzr == JcLhXpqjbc){GNWfZVxjZb = true;}
      else if(JcLhXpqjbc == DcVmazRDzr){dMQiXESSkp = true;}
      if(wRgRjzVMnC == AiarPNlCyd){UrjIjNjJHI = true;}
      else if(AiarPNlCyd == wRgRjzVMnC){YSBSCIoVMU = true;}
      if(ILYKJMJzZb == mZxQrMgQYo){KmNWFdfHmW = true;}
      else if(mZxQrMgQYo == ILYKJMJzZb){MyzcKRsFfU = true;}
      if(fCDxwyYJFb == htdDbUPxCj){EmZMZMXJZI = true;}
      else if(htdDbUPxCj == fCDxwyYJFb){iFWIdgPQCl = true;}
      if(PbUDaXNhTy == qWMJFLllaY){oLrgXwjzGN = true;}
      if(CywOKqELdO == KwyMsifuoL){fCSFoTzzaw = true;}
      if(oRcXLtOjVl == IZKluFEXPt){powCXhSWiX = true;}
      while(qWMJFLllaY == PbUDaXNhTy){jCigfsWObJ = true;}
      while(KwyMsifuoL == KwyMsifuoL){JscodfMmXG = true;}
      while(IZKluFEXPt == IZKluFEXPt){LNlPGTwrnU = true;}
      if(ynzOmQNnLg == true){ynzOmQNnLg = false;}
      if(atpAeluRJs == true){atpAeluRJs = false;}
      if(oTIqaQLZNz == true){oTIqaQLZNz = false;}
      if(GNWfZVxjZb == true){GNWfZVxjZb = false;}
      if(UrjIjNjJHI == true){UrjIjNjJHI = false;}
      if(KmNWFdfHmW == true){KmNWFdfHmW = false;}
      if(EmZMZMXJZI == true){EmZMZMXJZI = false;}
      if(oLrgXwjzGN == true){oLrgXwjzGN = false;}
      if(fCSFoTzzaw == true){fCSFoTzzaw = false;}
      if(powCXhSWiX == true){powCXhSWiX = false;}
      if(oaizTytfyI == true){oaizTytfyI = false;}
      if(tgAZpCUUWF == true){tgAZpCUUWF = false;}
      if(MXhdSzPoJp == true){MXhdSzPoJp = false;}
      if(dMQiXESSkp == true){dMQiXESSkp = false;}
      if(YSBSCIoVMU == true){YSBSCIoVMU = false;}
      if(MyzcKRsFfU == true){MyzcKRsFfU = false;}
      if(iFWIdgPQCl == true){iFWIdgPQCl = false;}
      if(jCigfsWObJ == true){jCigfsWObJ = false;}
      if(JscodfMmXG == true){JscodfMmXG = false;}
      if(LNlPGTwrnU == true){LNlPGTwrnU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ICYIANTYFZ
{ 
  void BkFyyenLWs()
  { 
      bool JbLPpnMwmz = false;
      bool EchOOTnzBP = false;
      bool HkICYpQXXG = false;
      bool LXIbKchlnk = false;
      bool HMjdKPAeSB = false;
      bool dMAWSYSIpA = false;
      bool WnYfmfTGDk = false;
      bool lBKPHtAdrJ = false;
      bool pkFVbyXlIl = false;
      bool JYwnOSmDqd = false;
      bool utagPbCkOX = false;
      bool XoQgJkiDDn = false;
      bool IhxRaMFVBn = false;
      bool GwlNNwJYGA = false;
      bool wlWkNTIOdc = false;
      bool jjzDUMxJFC = false;
      bool VfjaQaDCSN = false;
      bool bJxDqWLLDG = false;
      bool EpqXDWxisB = false;
      bool yASDdQCuTl = false;
      string IIVdoCChLb;
      string OLnlZpuxnf;
      string ZboynDTQpR;
      string JlhbmcXgzn;
      string WPLMMLzZRE;
      string yYXHhfTXpk;
      string ikrtSbcLzw;
      string RNyzIKQckc;
      string EsylSjOatG;
      string JzqOFkXQsk;
      string hnaVljaXyX;
      string PqlMgpmFah;
      string NCQrmSWjtX;
      string mziAtPRcAh;
      string JpbWpRNdgP;
      string yRoLWeWiiT;
      string MqdajQIlRR;
      string YKFsYXZtBU;
      string EsCeYUJWcP;
      string rhsgUSLBlZ;
      if(IIVdoCChLb == hnaVljaXyX){JbLPpnMwmz = true;}
      else if(hnaVljaXyX == IIVdoCChLb){utagPbCkOX = true;}
      if(OLnlZpuxnf == PqlMgpmFah){EchOOTnzBP = true;}
      else if(PqlMgpmFah == OLnlZpuxnf){XoQgJkiDDn = true;}
      if(ZboynDTQpR == NCQrmSWjtX){HkICYpQXXG = true;}
      else if(NCQrmSWjtX == ZboynDTQpR){IhxRaMFVBn = true;}
      if(JlhbmcXgzn == mziAtPRcAh){LXIbKchlnk = true;}
      else if(mziAtPRcAh == JlhbmcXgzn){GwlNNwJYGA = true;}
      if(WPLMMLzZRE == JpbWpRNdgP){HMjdKPAeSB = true;}
      else if(JpbWpRNdgP == WPLMMLzZRE){wlWkNTIOdc = true;}
      if(yYXHhfTXpk == yRoLWeWiiT){dMAWSYSIpA = true;}
      else if(yRoLWeWiiT == yYXHhfTXpk){jjzDUMxJFC = true;}
      if(ikrtSbcLzw == MqdajQIlRR){WnYfmfTGDk = true;}
      else if(MqdajQIlRR == ikrtSbcLzw){VfjaQaDCSN = true;}
      if(RNyzIKQckc == YKFsYXZtBU){lBKPHtAdrJ = true;}
      if(EsylSjOatG == EsCeYUJWcP){pkFVbyXlIl = true;}
      if(JzqOFkXQsk == rhsgUSLBlZ){JYwnOSmDqd = true;}
      while(YKFsYXZtBU == RNyzIKQckc){bJxDqWLLDG = true;}
      while(EsCeYUJWcP == EsCeYUJWcP){EpqXDWxisB = true;}
      while(rhsgUSLBlZ == rhsgUSLBlZ){yASDdQCuTl = true;}
      if(JbLPpnMwmz == true){JbLPpnMwmz = false;}
      if(EchOOTnzBP == true){EchOOTnzBP = false;}
      if(HkICYpQXXG == true){HkICYpQXXG = false;}
      if(LXIbKchlnk == true){LXIbKchlnk = false;}
      if(HMjdKPAeSB == true){HMjdKPAeSB = false;}
      if(dMAWSYSIpA == true){dMAWSYSIpA = false;}
      if(WnYfmfTGDk == true){WnYfmfTGDk = false;}
      if(lBKPHtAdrJ == true){lBKPHtAdrJ = false;}
      if(pkFVbyXlIl == true){pkFVbyXlIl = false;}
      if(JYwnOSmDqd == true){JYwnOSmDqd = false;}
      if(utagPbCkOX == true){utagPbCkOX = false;}
      if(XoQgJkiDDn == true){XoQgJkiDDn = false;}
      if(IhxRaMFVBn == true){IhxRaMFVBn = false;}
      if(GwlNNwJYGA == true){GwlNNwJYGA = false;}
      if(wlWkNTIOdc == true){wlWkNTIOdc = false;}
      if(jjzDUMxJFC == true){jjzDUMxJFC = false;}
      if(VfjaQaDCSN == true){VfjaQaDCSN = false;}
      if(bJxDqWLLDG == true){bJxDqWLLDG = false;}
      if(EpqXDWxisB == true){EpqXDWxisB = false;}
      if(yASDdQCuTl == true){yASDdQCuTl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MRHWGDEUKZ
{ 
  void cytphtdXUL()
  { 
      bool TxNBlPbhoK = false;
      bool SoHoDSnSmt = false;
      bool nmShIhrixb = false;
      bool KJZhqcemel = false;
      bool HTSrqIMVYj = false;
      bool GylZnfderD = false;
      bool XsjMzIOZyZ = false;
      bool mAmBmUTaqz = false;
      bool VWJNVMXAsK = false;
      bool yAtaNOiGsh = false;
      bool slWywFKkmT = false;
      bool LDmshBiVqm = false;
      bool kOgnbmGMmY = false;
      bool kNhJGizKRP = false;
      bool CmNYzuMBrM = false;
      bool eNPFxdFiWI = false;
      bool zyyOixVdlz = false;
      bool BYEajxBHnf = false;
      bool aFTZsWybMb = false;
      bool cQmIQEozpB = false;
      string QKBuoPOWdz;
      string jJQKaSisil;
      string YMTlflsPbr;
      string LQnXsVtZAz;
      string hzhthUXMdx;
      string TQZOYDpOPD;
      string VzulnTVrRE;
      string YJriDZeZDK;
      string NgkdXtqYyp;
      string eeKwdhDuFO;
      string yetZXKXpKz;
      string XQKEooOQNs;
      string cxtbZtzuFV;
      string ViUoLilLGN;
      string WBNyROTGHn;
      string TlhLlBkRzd;
      string LbjodouVrG;
      string CDKAWbiuKK;
      string arnQCiBICJ;
      string yULbCtQYUb;
      if(QKBuoPOWdz == yetZXKXpKz){TxNBlPbhoK = true;}
      else if(yetZXKXpKz == QKBuoPOWdz){slWywFKkmT = true;}
      if(jJQKaSisil == XQKEooOQNs){SoHoDSnSmt = true;}
      else if(XQKEooOQNs == jJQKaSisil){LDmshBiVqm = true;}
      if(YMTlflsPbr == cxtbZtzuFV){nmShIhrixb = true;}
      else if(cxtbZtzuFV == YMTlflsPbr){kOgnbmGMmY = true;}
      if(LQnXsVtZAz == ViUoLilLGN){KJZhqcemel = true;}
      else if(ViUoLilLGN == LQnXsVtZAz){kNhJGizKRP = true;}
      if(hzhthUXMdx == WBNyROTGHn){HTSrqIMVYj = true;}
      else if(WBNyROTGHn == hzhthUXMdx){CmNYzuMBrM = true;}
      if(TQZOYDpOPD == TlhLlBkRzd){GylZnfderD = true;}
      else if(TlhLlBkRzd == TQZOYDpOPD){eNPFxdFiWI = true;}
      if(VzulnTVrRE == LbjodouVrG){XsjMzIOZyZ = true;}
      else if(LbjodouVrG == VzulnTVrRE){zyyOixVdlz = true;}
      if(YJriDZeZDK == CDKAWbiuKK){mAmBmUTaqz = true;}
      if(NgkdXtqYyp == arnQCiBICJ){VWJNVMXAsK = true;}
      if(eeKwdhDuFO == yULbCtQYUb){yAtaNOiGsh = true;}
      while(CDKAWbiuKK == YJriDZeZDK){BYEajxBHnf = true;}
      while(arnQCiBICJ == arnQCiBICJ){aFTZsWybMb = true;}
      while(yULbCtQYUb == yULbCtQYUb){cQmIQEozpB = true;}
      if(TxNBlPbhoK == true){TxNBlPbhoK = false;}
      if(SoHoDSnSmt == true){SoHoDSnSmt = false;}
      if(nmShIhrixb == true){nmShIhrixb = false;}
      if(KJZhqcemel == true){KJZhqcemel = false;}
      if(HTSrqIMVYj == true){HTSrqIMVYj = false;}
      if(GylZnfderD == true){GylZnfderD = false;}
      if(XsjMzIOZyZ == true){XsjMzIOZyZ = false;}
      if(mAmBmUTaqz == true){mAmBmUTaqz = false;}
      if(VWJNVMXAsK == true){VWJNVMXAsK = false;}
      if(yAtaNOiGsh == true){yAtaNOiGsh = false;}
      if(slWywFKkmT == true){slWywFKkmT = false;}
      if(LDmshBiVqm == true){LDmshBiVqm = false;}
      if(kOgnbmGMmY == true){kOgnbmGMmY = false;}
      if(kNhJGizKRP == true){kNhJGizKRP = false;}
      if(CmNYzuMBrM == true){CmNYzuMBrM = false;}
      if(eNPFxdFiWI == true){eNPFxdFiWI = false;}
      if(zyyOixVdlz == true){zyyOixVdlz = false;}
      if(BYEajxBHnf == true){BYEajxBHnf = false;}
      if(aFTZsWybMb == true){aFTZsWybMb = false;}
      if(cQmIQEozpB == true){cQmIQEozpB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZJNGACVUZD
{ 
  void WbIKwLZXzT()
  { 
      bool KhnKyUbVtu = false;
      bool RaOwbrNPSe = false;
      bool kjwkEnGjaP = false;
      bool ViSLZBWcQL = false;
      bool qklnjZlCWB = false;
      bool jHIsValCGJ = false;
      bool NrueYiHDVa = false;
      bool UkyGmAxHBd = false;
      bool CDMYeNZZpz = false;
      bool PTVHxzoHPA = false;
      bool RifwfyJCGU = false;
      bool ceBcHKeVzK = false;
      bool IhNWKBPqIm = false;
      bool KprALTXPsg = false;
      bool EXTUWkSrzm = false;
      bool TTHErjUJke = false;
      bool iRsSKllAQn = false;
      bool mPcSFkNsAZ = false;
      bool hWqVSpimIa = false;
      bool yNdOymdBJj = false;
      string NPslPrjMTY;
      string OTcryynHgr;
      string JRydZqmVuN;
      string GhCPkAhGNR;
      string ZXNnSfrGsZ;
      string YAxWPuQPMX;
      string FOQFSgQNHx;
      string PhtPRlEKKs;
      string ygcVnFjfzo;
      string iStoMLGHUl;
      string OeyuJqGhEd;
      string pGESYXluRM;
      string wkNRNxmEDF;
      string exoYeThgLx;
      string zCaVzcNbQn;
      string ZLpHocRghL;
      string DBeyyrRfmF;
      string pFiTNtKqRk;
      string jLmOfTHgjB;
      string BBzzsyXbXG;
      if(NPslPrjMTY == OeyuJqGhEd){KhnKyUbVtu = true;}
      else if(OeyuJqGhEd == NPslPrjMTY){RifwfyJCGU = true;}
      if(OTcryynHgr == pGESYXluRM){RaOwbrNPSe = true;}
      else if(pGESYXluRM == OTcryynHgr){ceBcHKeVzK = true;}
      if(JRydZqmVuN == wkNRNxmEDF){kjwkEnGjaP = true;}
      else if(wkNRNxmEDF == JRydZqmVuN){IhNWKBPqIm = true;}
      if(GhCPkAhGNR == exoYeThgLx){ViSLZBWcQL = true;}
      else if(exoYeThgLx == GhCPkAhGNR){KprALTXPsg = true;}
      if(ZXNnSfrGsZ == zCaVzcNbQn){qklnjZlCWB = true;}
      else if(zCaVzcNbQn == ZXNnSfrGsZ){EXTUWkSrzm = true;}
      if(YAxWPuQPMX == ZLpHocRghL){jHIsValCGJ = true;}
      else if(ZLpHocRghL == YAxWPuQPMX){TTHErjUJke = true;}
      if(FOQFSgQNHx == DBeyyrRfmF){NrueYiHDVa = true;}
      else if(DBeyyrRfmF == FOQFSgQNHx){iRsSKllAQn = true;}
      if(PhtPRlEKKs == pFiTNtKqRk){UkyGmAxHBd = true;}
      if(ygcVnFjfzo == jLmOfTHgjB){CDMYeNZZpz = true;}
      if(iStoMLGHUl == BBzzsyXbXG){PTVHxzoHPA = true;}
      while(pFiTNtKqRk == PhtPRlEKKs){mPcSFkNsAZ = true;}
      while(jLmOfTHgjB == jLmOfTHgjB){hWqVSpimIa = true;}
      while(BBzzsyXbXG == BBzzsyXbXG){yNdOymdBJj = true;}
      if(KhnKyUbVtu == true){KhnKyUbVtu = false;}
      if(RaOwbrNPSe == true){RaOwbrNPSe = false;}
      if(kjwkEnGjaP == true){kjwkEnGjaP = false;}
      if(ViSLZBWcQL == true){ViSLZBWcQL = false;}
      if(qklnjZlCWB == true){qklnjZlCWB = false;}
      if(jHIsValCGJ == true){jHIsValCGJ = false;}
      if(NrueYiHDVa == true){NrueYiHDVa = false;}
      if(UkyGmAxHBd == true){UkyGmAxHBd = false;}
      if(CDMYeNZZpz == true){CDMYeNZZpz = false;}
      if(PTVHxzoHPA == true){PTVHxzoHPA = false;}
      if(RifwfyJCGU == true){RifwfyJCGU = false;}
      if(ceBcHKeVzK == true){ceBcHKeVzK = false;}
      if(IhNWKBPqIm == true){IhNWKBPqIm = false;}
      if(KprALTXPsg == true){KprALTXPsg = false;}
      if(EXTUWkSrzm == true){EXTUWkSrzm = false;}
      if(TTHErjUJke == true){TTHErjUJke = false;}
      if(iRsSKllAQn == true){iRsSKllAQn = false;}
      if(mPcSFkNsAZ == true){mPcSFkNsAZ = false;}
      if(hWqVSpimIa == true){hWqVSpimIa = false;}
      if(yNdOymdBJj == true){yNdOymdBJj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YXCRFSGJLI
{ 
  void mBElAGeDhw()
  { 
      bool eMLmwLmZUP = false;
      bool OrEiWOkHMF = false;
      bool KjsRHUaNZE = false;
      bool GMSgWmWIjN = false;
      bool pWqfZPBJns = false;
      bool qfifRuTseb = false;
      bool jZAPJCYWLi = false;
      bool qcXyOnrMqr = false;
      bool TQZfMacmPb = false;
      bool TccIcPVaWX = false;
      bool pdyEBOIjQd = false;
      bool CGBmHSATDi = false;
      bool ZlHiPNzOVz = false;
      bool RQpTBpSUex = false;
      bool RrVkYNbpAJ = false;
      bool PBXnyDWOnm = false;
      bool PsORLlQgkR = false;
      bool AeoFQgPVKC = false;
      bool lIOLiPsBVx = false;
      bool SEgqhYdEZm = false;
      string rLLgRjVFcd;
      string eywsbxQsCB;
      string ohoVpTRcpn;
      string tjobFJqcVh;
      string UhiedTqshf;
      string kDNUgKVppx;
      string RrPoitIUmR;
      string FmXUfHyKqW;
      string bYtJCpWUtu;
      string mBlYPcRtui;
      string KWFQaxfsnY;
      string LLyTVsxGlr;
      string XnZreDByED;
      string pEOHLFSdhE;
      string KcfUibDSDW;
      string eLHCLWxNkW;
      string wgokiGwpHP;
      string ZTXghuHEJC;
      string AhugYdwMwo;
      string IFrKHcnukb;
      if(rLLgRjVFcd == KWFQaxfsnY){eMLmwLmZUP = true;}
      else if(KWFQaxfsnY == rLLgRjVFcd){pdyEBOIjQd = true;}
      if(eywsbxQsCB == LLyTVsxGlr){OrEiWOkHMF = true;}
      else if(LLyTVsxGlr == eywsbxQsCB){CGBmHSATDi = true;}
      if(ohoVpTRcpn == XnZreDByED){KjsRHUaNZE = true;}
      else if(XnZreDByED == ohoVpTRcpn){ZlHiPNzOVz = true;}
      if(tjobFJqcVh == pEOHLFSdhE){GMSgWmWIjN = true;}
      else if(pEOHLFSdhE == tjobFJqcVh){RQpTBpSUex = true;}
      if(UhiedTqshf == KcfUibDSDW){pWqfZPBJns = true;}
      else if(KcfUibDSDW == UhiedTqshf){RrVkYNbpAJ = true;}
      if(kDNUgKVppx == eLHCLWxNkW){qfifRuTseb = true;}
      else if(eLHCLWxNkW == kDNUgKVppx){PBXnyDWOnm = true;}
      if(RrPoitIUmR == wgokiGwpHP){jZAPJCYWLi = true;}
      else if(wgokiGwpHP == RrPoitIUmR){PsORLlQgkR = true;}
      if(FmXUfHyKqW == ZTXghuHEJC){qcXyOnrMqr = true;}
      if(bYtJCpWUtu == AhugYdwMwo){TQZfMacmPb = true;}
      if(mBlYPcRtui == IFrKHcnukb){TccIcPVaWX = true;}
      while(ZTXghuHEJC == FmXUfHyKqW){AeoFQgPVKC = true;}
      while(AhugYdwMwo == AhugYdwMwo){lIOLiPsBVx = true;}
      while(IFrKHcnukb == IFrKHcnukb){SEgqhYdEZm = true;}
      if(eMLmwLmZUP == true){eMLmwLmZUP = false;}
      if(OrEiWOkHMF == true){OrEiWOkHMF = false;}
      if(KjsRHUaNZE == true){KjsRHUaNZE = false;}
      if(GMSgWmWIjN == true){GMSgWmWIjN = false;}
      if(pWqfZPBJns == true){pWqfZPBJns = false;}
      if(qfifRuTseb == true){qfifRuTseb = false;}
      if(jZAPJCYWLi == true){jZAPJCYWLi = false;}
      if(qcXyOnrMqr == true){qcXyOnrMqr = false;}
      if(TQZfMacmPb == true){TQZfMacmPb = false;}
      if(TccIcPVaWX == true){TccIcPVaWX = false;}
      if(pdyEBOIjQd == true){pdyEBOIjQd = false;}
      if(CGBmHSATDi == true){CGBmHSATDi = false;}
      if(ZlHiPNzOVz == true){ZlHiPNzOVz = false;}
      if(RQpTBpSUex == true){RQpTBpSUex = false;}
      if(RrVkYNbpAJ == true){RrVkYNbpAJ = false;}
      if(PBXnyDWOnm == true){PBXnyDWOnm = false;}
      if(PsORLlQgkR == true){PsORLlQgkR = false;}
      if(AeoFQgPVKC == true){AeoFQgPVKC = false;}
      if(lIOLiPsBVx == true){lIOLiPsBVx = false;}
      if(SEgqhYdEZm == true){SEgqhYdEZm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NQUJMIFTYD
{ 
  void qmMtiKQxtw()
  { 
      bool iniXGNlDGJ = false;
      bool ZxqipEVuDZ = false;
      bool DtDeAwxGut = false;
      bool fVhfqhEUwA = false;
      bool sbCxAGMdDH = false;
      bool DaAZpojEXJ = false;
      bool PeIMdDOKrH = false;
      bool zByDgbrGds = false;
      bool iTDnqEVHpC = false;
      bool xAwljNToTw = false;
      bool qBluHBcwsO = false;
      bool wdZdawbUVY = false;
      bool hHUoKzELSS = false;
      bool IClgBghHfo = false;
      bool bYNaFSZRLm = false;
      bool lzTtOjgwkI = false;
      bool xQcaFtrscs = false;
      bool OUngxIssiq = false;
      bool YlAffJiqRR = false;
      bool AkVXqKumVL = false;
      string wrXdhkbYSe;
      string PjXwTULzYW;
      string uMkmeoXBck;
      string xRRGngQRLo;
      string fmBQhLkeIm;
      string OYptejHjys;
      string NZuggyRQIl;
      string DtnjqIKTET;
      string ErspWYaXbD;
      string ZfSRaFqUij;
      string sTWViTjGCV;
      string ZmfeoUgFKI;
      string WtnEMWbVIk;
      string QpjUZjVWGD;
      string nUUFdlAncF;
      string XkKaMzfRJM;
      string rOxQFiDLFE;
      string zKzGTCZhaZ;
      string WmrCNefJHZ;
      string EDMsLZWDAt;
      if(wrXdhkbYSe == sTWViTjGCV){iniXGNlDGJ = true;}
      else if(sTWViTjGCV == wrXdhkbYSe){qBluHBcwsO = true;}
      if(PjXwTULzYW == ZmfeoUgFKI){ZxqipEVuDZ = true;}
      else if(ZmfeoUgFKI == PjXwTULzYW){wdZdawbUVY = true;}
      if(uMkmeoXBck == WtnEMWbVIk){DtDeAwxGut = true;}
      else if(WtnEMWbVIk == uMkmeoXBck){hHUoKzELSS = true;}
      if(xRRGngQRLo == QpjUZjVWGD){fVhfqhEUwA = true;}
      else if(QpjUZjVWGD == xRRGngQRLo){IClgBghHfo = true;}
      if(fmBQhLkeIm == nUUFdlAncF){sbCxAGMdDH = true;}
      else if(nUUFdlAncF == fmBQhLkeIm){bYNaFSZRLm = true;}
      if(OYptejHjys == XkKaMzfRJM){DaAZpojEXJ = true;}
      else if(XkKaMzfRJM == OYptejHjys){lzTtOjgwkI = true;}
      if(NZuggyRQIl == rOxQFiDLFE){PeIMdDOKrH = true;}
      else if(rOxQFiDLFE == NZuggyRQIl){xQcaFtrscs = true;}
      if(DtnjqIKTET == zKzGTCZhaZ){zByDgbrGds = true;}
      if(ErspWYaXbD == WmrCNefJHZ){iTDnqEVHpC = true;}
      if(ZfSRaFqUij == EDMsLZWDAt){xAwljNToTw = true;}
      while(zKzGTCZhaZ == DtnjqIKTET){OUngxIssiq = true;}
      while(WmrCNefJHZ == WmrCNefJHZ){YlAffJiqRR = true;}
      while(EDMsLZWDAt == EDMsLZWDAt){AkVXqKumVL = true;}
      if(iniXGNlDGJ == true){iniXGNlDGJ = false;}
      if(ZxqipEVuDZ == true){ZxqipEVuDZ = false;}
      if(DtDeAwxGut == true){DtDeAwxGut = false;}
      if(fVhfqhEUwA == true){fVhfqhEUwA = false;}
      if(sbCxAGMdDH == true){sbCxAGMdDH = false;}
      if(DaAZpojEXJ == true){DaAZpojEXJ = false;}
      if(PeIMdDOKrH == true){PeIMdDOKrH = false;}
      if(zByDgbrGds == true){zByDgbrGds = false;}
      if(iTDnqEVHpC == true){iTDnqEVHpC = false;}
      if(xAwljNToTw == true){xAwljNToTw = false;}
      if(qBluHBcwsO == true){qBluHBcwsO = false;}
      if(wdZdawbUVY == true){wdZdawbUVY = false;}
      if(hHUoKzELSS == true){hHUoKzELSS = false;}
      if(IClgBghHfo == true){IClgBghHfo = false;}
      if(bYNaFSZRLm == true){bYNaFSZRLm = false;}
      if(lzTtOjgwkI == true){lzTtOjgwkI = false;}
      if(xQcaFtrscs == true){xQcaFtrscs = false;}
      if(OUngxIssiq == true){OUngxIssiq = false;}
      if(YlAffJiqRR == true){YlAffJiqRR = false;}
      if(AkVXqKumVL == true){AkVXqKumVL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VNFWMSHWTT
{ 
  void cozueXUtiD()
  { 
      bool eDldsuNfhB = false;
      bool aEhPwTLxfS = false;
      bool aLHWGILIIk = false;
      bool BwBWNGKhws = false;
      bool rewLVhVZoi = false;
      bool YhgfPTwOWj = false;
      bool jEWxzdDLBp = false;
      bool IcAmZwPuAY = false;
      bool mkTZLTPUGt = false;
      bool JuKMInIzMr = false;
      bool dKXzZwhsFT = false;
      bool EBOxxykwkf = false;
      bool NhEHfNSnel = false;
      bool nQiIubMTAP = false;
      bool kWPmpIgMOK = false;
      bool CLNfduGQSL = false;
      bool ctOSfmSGCU = false;
      bool kQwVtqSQQX = false;
      bool gFYUibCCdz = false;
      bool VwAnlqHwGC = false;
      string bfLlgqZFaH;
      string HHlsnIbDqA;
      string PMqPXdnCoK;
      string OFaDhgkTLY;
      string TImbkLKyeK;
      string ZzClsPnuND;
      string DWPPsCghKH;
      string WHqSgGZPeM;
      string SoWekPCnKS;
      string roGHUwsWhh;
      string dbnXmRHjFl;
      string oXQBjOAked;
      string zsXqOhBjxj;
      string NChwhqAzqS;
      string IShXdUXEXG;
      string wHrDikEwJF;
      string QXmUYloUSs;
      string NBtLVgKzNs;
      string JwLpnFKdNw;
      string lEokCkeNyq;
      if(bfLlgqZFaH == dbnXmRHjFl){eDldsuNfhB = true;}
      else if(dbnXmRHjFl == bfLlgqZFaH){dKXzZwhsFT = true;}
      if(HHlsnIbDqA == oXQBjOAked){aEhPwTLxfS = true;}
      else if(oXQBjOAked == HHlsnIbDqA){EBOxxykwkf = true;}
      if(PMqPXdnCoK == zsXqOhBjxj){aLHWGILIIk = true;}
      else if(zsXqOhBjxj == PMqPXdnCoK){NhEHfNSnel = true;}
      if(OFaDhgkTLY == NChwhqAzqS){BwBWNGKhws = true;}
      else if(NChwhqAzqS == OFaDhgkTLY){nQiIubMTAP = true;}
      if(TImbkLKyeK == IShXdUXEXG){rewLVhVZoi = true;}
      else if(IShXdUXEXG == TImbkLKyeK){kWPmpIgMOK = true;}
      if(ZzClsPnuND == wHrDikEwJF){YhgfPTwOWj = true;}
      else if(wHrDikEwJF == ZzClsPnuND){CLNfduGQSL = true;}
      if(DWPPsCghKH == QXmUYloUSs){jEWxzdDLBp = true;}
      else if(QXmUYloUSs == DWPPsCghKH){ctOSfmSGCU = true;}
      if(WHqSgGZPeM == NBtLVgKzNs){IcAmZwPuAY = true;}
      if(SoWekPCnKS == JwLpnFKdNw){mkTZLTPUGt = true;}
      if(roGHUwsWhh == lEokCkeNyq){JuKMInIzMr = true;}
      while(NBtLVgKzNs == WHqSgGZPeM){kQwVtqSQQX = true;}
      while(JwLpnFKdNw == JwLpnFKdNw){gFYUibCCdz = true;}
      while(lEokCkeNyq == lEokCkeNyq){VwAnlqHwGC = true;}
      if(eDldsuNfhB == true){eDldsuNfhB = false;}
      if(aEhPwTLxfS == true){aEhPwTLxfS = false;}
      if(aLHWGILIIk == true){aLHWGILIIk = false;}
      if(BwBWNGKhws == true){BwBWNGKhws = false;}
      if(rewLVhVZoi == true){rewLVhVZoi = false;}
      if(YhgfPTwOWj == true){YhgfPTwOWj = false;}
      if(jEWxzdDLBp == true){jEWxzdDLBp = false;}
      if(IcAmZwPuAY == true){IcAmZwPuAY = false;}
      if(mkTZLTPUGt == true){mkTZLTPUGt = false;}
      if(JuKMInIzMr == true){JuKMInIzMr = false;}
      if(dKXzZwhsFT == true){dKXzZwhsFT = false;}
      if(EBOxxykwkf == true){EBOxxykwkf = false;}
      if(NhEHfNSnel == true){NhEHfNSnel = false;}
      if(nQiIubMTAP == true){nQiIubMTAP = false;}
      if(kWPmpIgMOK == true){kWPmpIgMOK = false;}
      if(CLNfduGQSL == true){CLNfduGQSL = false;}
      if(ctOSfmSGCU == true){ctOSfmSGCU = false;}
      if(kQwVtqSQQX == true){kQwVtqSQQX = false;}
      if(gFYUibCCdz == true){gFYUibCCdz = false;}
      if(VwAnlqHwGC == true){VwAnlqHwGC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MJGKVTDQZF
{ 
  void qTGrmrHbkh()
  { 
      bool riycotpcVW = false;
      bool ZZJsdHuQOK = false;
      bool upFuIXLyOn = false;
      bool GWjWYikSCj = false;
      bool PZEblcXLLx = false;
      bool RDpEHBcDTQ = false;
      bool iqNhPColTu = false;
      bool VcNduUldIe = false;
      bool AzmQWDffOX = false;
      bool FhylBYLWLi = false;
      bool mkrQbopMIl = false;
      bool PztnQiExLM = false;
      bool VJWwondbbV = false;
      bool JORZqPHVog = false;
      bool NTWcHGmKUS = false;
      bool UOKzMdNwan = false;
      bool LOkmcAhUwA = false;
      bool bhHdzCltoi = false;
      bool ATGJBtERNN = false;
      bool CLtBVzijAG = false;
      string coOngtUqaO;
      string yMmcTaEYIL;
      string DUuTbFCmfe;
      string aWDXFThmHG;
      string aOIRZkUelt;
      string ztyUpIttLa;
      string qhLwmaJOWA;
      string sQRBjnLctp;
      string jWBlegYihx;
      string ZnafOsDMdy;
      string bGIkAhcwjB;
      string wQAUpTgYQG;
      string CZfZaFpkmq;
      string jyzuNdOPkx;
      string EcyfAJnFot;
      string LdwXwCZhKu;
      string rqIsQxQEGM;
      string EQnTBZbzYQ;
      string RjureFCayL;
      string DgFoFNTEPC;
      if(coOngtUqaO == bGIkAhcwjB){riycotpcVW = true;}
      else if(bGIkAhcwjB == coOngtUqaO){mkrQbopMIl = true;}
      if(yMmcTaEYIL == wQAUpTgYQG){ZZJsdHuQOK = true;}
      else if(wQAUpTgYQG == yMmcTaEYIL){PztnQiExLM = true;}
      if(DUuTbFCmfe == CZfZaFpkmq){upFuIXLyOn = true;}
      else if(CZfZaFpkmq == DUuTbFCmfe){VJWwondbbV = true;}
      if(aWDXFThmHG == jyzuNdOPkx){GWjWYikSCj = true;}
      else if(jyzuNdOPkx == aWDXFThmHG){JORZqPHVog = true;}
      if(aOIRZkUelt == EcyfAJnFot){PZEblcXLLx = true;}
      else if(EcyfAJnFot == aOIRZkUelt){NTWcHGmKUS = true;}
      if(ztyUpIttLa == LdwXwCZhKu){RDpEHBcDTQ = true;}
      else if(LdwXwCZhKu == ztyUpIttLa){UOKzMdNwan = true;}
      if(qhLwmaJOWA == rqIsQxQEGM){iqNhPColTu = true;}
      else if(rqIsQxQEGM == qhLwmaJOWA){LOkmcAhUwA = true;}
      if(sQRBjnLctp == EQnTBZbzYQ){VcNduUldIe = true;}
      if(jWBlegYihx == RjureFCayL){AzmQWDffOX = true;}
      if(ZnafOsDMdy == DgFoFNTEPC){FhylBYLWLi = true;}
      while(EQnTBZbzYQ == sQRBjnLctp){bhHdzCltoi = true;}
      while(RjureFCayL == RjureFCayL){ATGJBtERNN = true;}
      while(DgFoFNTEPC == DgFoFNTEPC){CLtBVzijAG = true;}
      if(riycotpcVW == true){riycotpcVW = false;}
      if(ZZJsdHuQOK == true){ZZJsdHuQOK = false;}
      if(upFuIXLyOn == true){upFuIXLyOn = false;}
      if(GWjWYikSCj == true){GWjWYikSCj = false;}
      if(PZEblcXLLx == true){PZEblcXLLx = false;}
      if(RDpEHBcDTQ == true){RDpEHBcDTQ = false;}
      if(iqNhPColTu == true){iqNhPColTu = false;}
      if(VcNduUldIe == true){VcNduUldIe = false;}
      if(AzmQWDffOX == true){AzmQWDffOX = false;}
      if(FhylBYLWLi == true){FhylBYLWLi = false;}
      if(mkrQbopMIl == true){mkrQbopMIl = false;}
      if(PztnQiExLM == true){PztnQiExLM = false;}
      if(VJWwondbbV == true){VJWwondbbV = false;}
      if(JORZqPHVog == true){JORZqPHVog = false;}
      if(NTWcHGmKUS == true){NTWcHGmKUS = false;}
      if(UOKzMdNwan == true){UOKzMdNwan = false;}
      if(LOkmcAhUwA == true){LOkmcAhUwA = false;}
      if(bhHdzCltoi == true){bhHdzCltoi = false;}
      if(ATGJBtERNN == true){ATGJBtERNN = false;}
      if(CLtBVzijAG == true){CLtBVzijAG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GECAFOCTFT
{ 
  void ampeUJaZiF()
  { 
      bool GZnhyZnQqx = false;
      bool wfbyMXdUnL = false;
      bool ukaTxTFOlu = false;
      bool fhnFZBgHVF = false;
      bool ICaJJIDGoO = false;
      bool CJptbUzTjd = false;
      bool TZewROqWXL = false;
      bool qWyiCsJRKo = false;
      bool QzYWsVrtcF = false;
      bool BNXqkhWeqt = false;
      bool QghdXfKGqi = false;
      bool KgJuNUAIDu = false;
      bool WwsSJczGyU = false;
      bool VeZPXjQuzM = false;
      bool KkDttTDbdP = false;
      bool gObuXTmOTt = false;
      bool gDIVMfHtWc = false;
      bool EEJpkkszYo = false;
      bool ZWchmHCdqD = false;
      bool xBbEfGbggN = false;
      string wZoJJrarkH;
      string rDcSbmGDad;
      string wRwroKCYXV;
      string ulMxqgAVVY;
      string hgLKrINwRJ;
      string MNJfZedwUy;
      string pCUOLFpfbu;
      string ljhBwOFkAf;
      string xFHNJhbgXL;
      string DDBWifMwyl;
      string RhUWWbfHiK;
      string YrwnBjuGFd;
      string dJHPriiKSP;
      string CJmOOOkjpg;
      string BTxNmKHNUy;
      string kFpTHIZFen;
      string sUoTIOEgZl;
      string zKQYbKLtcg;
      string aUpUexTSGF;
      string oeECmgddFX;
      if(wZoJJrarkH == RhUWWbfHiK){GZnhyZnQqx = true;}
      else if(RhUWWbfHiK == wZoJJrarkH){QghdXfKGqi = true;}
      if(rDcSbmGDad == YrwnBjuGFd){wfbyMXdUnL = true;}
      else if(YrwnBjuGFd == rDcSbmGDad){KgJuNUAIDu = true;}
      if(wRwroKCYXV == dJHPriiKSP){ukaTxTFOlu = true;}
      else if(dJHPriiKSP == wRwroKCYXV){WwsSJczGyU = true;}
      if(ulMxqgAVVY == CJmOOOkjpg){fhnFZBgHVF = true;}
      else if(CJmOOOkjpg == ulMxqgAVVY){VeZPXjQuzM = true;}
      if(hgLKrINwRJ == BTxNmKHNUy){ICaJJIDGoO = true;}
      else if(BTxNmKHNUy == hgLKrINwRJ){KkDttTDbdP = true;}
      if(MNJfZedwUy == kFpTHIZFen){CJptbUzTjd = true;}
      else if(kFpTHIZFen == MNJfZedwUy){gObuXTmOTt = true;}
      if(pCUOLFpfbu == sUoTIOEgZl){TZewROqWXL = true;}
      else if(sUoTIOEgZl == pCUOLFpfbu){gDIVMfHtWc = true;}
      if(ljhBwOFkAf == zKQYbKLtcg){qWyiCsJRKo = true;}
      if(xFHNJhbgXL == aUpUexTSGF){QzYWsVrtcF = true;}
      if(DDBWifMwyl == oeECmgddFX){BNXqkhWeqt = true;}
      while(zKQYbKLtcg == ljhBwOFkAf){EEJpkkszYo = true;}
      while(aUpUexTSGF == aUpUexTSGF){ZWchmHCdqD = true;}
      while(oeECmgddFX == oeECmgddFX){xBbEfGbggN = true;}
      if(GZnhyZnQqx == true){GZnhyZnQqx = false;}
      if(wfbyMXdUnL == true){wfbyMXdUnL = false;}
      if(ukaTxTFOlu == true){ukaTxTFOlu = false;}
      if(fhnFZBgHVF == true){fhnFZBgHVF = false;}
      if(ICaJJIDGoO == true){ICaJJIDGoO = false;}
      if(CJptbUzTjd == true){CJptbUzTjd = false;}
      if(TZewROqWXL == true){TZewROqWXL = false;}
      if(qWyiCsJRKo == true){qWyiCsJRKo = false;}
      if(QzYWsVrtcF == true){QzYWsVrtcF = false;}
      if(BNXqkhWeqt == true){BNXqkhWeqt = false;}
      if(QghdXfKGqi == true){QghdXfKGqi = false;}
      if(KgJuNUAIDu == true){KgJuNUAIDu = false;}
      if(WwsSJczGyU == true){WwsSJczGyU = false;}
      if(VeZPXjQuzM == true){VeZPXjQuzM = false;}
      if(KkDttTDbdP == true){KkDttTDbdP = false;}
      if(gObuXTmOTt == true){gObuXTmOTt = false;}
      if(gDIVMfHtWc == true){gDIVMfHtWc = false;}
      if(EEJpkkszYo == true){EEJpkkszYo = false;}
      if(ZWchmHCdqD == true){ZWchmHCdqD = false;}
      if(xBbEfGbggN == true){xBbEfGbggN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SUETLGBVJR
{ 
  void GleCaNCzGO()
  { 
      bool GDSMVnVVof = false;
      bool LUKFoPMxKi = false;
      bool hXjRcqMxZe = false;
      bool yVZeybjNee = false;
      bool LWbeITPsiJ = false;
      bool yHlTxhTAjd = false;
      bool bXuKgpteHN = false;
      bool fySfWKwEJI = false;
      bool bTOQfqiFhP = false;
      bool IidADmaQxS = false;
      bool ZjkUdznGwl = false;
      bool lOqaCHJedp = false;
      bool GnxrFwURbj = false;
      bool jeGphqhslg = false;
      bool CcJudsqCyw = false;
      bool dwmGMkmsOg = false;
      bool eVeMCGHBsL = false;
      bool YPrxnceBNM = false;
      bool FRTfFnqzdw = false;
      bool DodFBfxwsX = false;
      string ODCCOYzLEx;
      string TxpXIeOFmE;
      string yxGaiedJEt;
      string UVVjLcOMRw;
      string MPVsoEzxpN;
      string bedrZQxaSi;
      string toGJbyaFLf;
      string QBmpriaMke;
      string fgTpRoqdJu;
      string fmshBWIMQq;
      string dskKxZrmAp;
      string ojonDNVPql;
      string HxwQzcIEoU;
      string ZOutBluJsq;
      string xDcSFuyFdn;
      string ArVdifxUKU;
      string RmyeQaotmR;
      string RMWzoDTcKE;
      string eCaAThsQKU;
      string oazYYKFxCe;
      if(ODCCOYzLEx == dskKxZrmAp){GDSMVnVVof = true;}
      else if(dskKxZrmAp == ODCCOYzLEx){ZjkUdznGwl = true;}
      if(TxpXIeOFmE == ojonDNVPql){LUKFoPMxKi = true;}
      else if(ojonDNVPql == TxpXIeOFmE){lOqaCHJedp = true;}
      if(yxGaiedJEt == HxwQzcIEoU){hXjRcqMxZe = true;}
      else if(HxwQzcIEoU == yxGaiedJEt){GnxrFwURbj = true;}
      if(UVVjLcOMRw == ZOutBluJsq){yVZeybjNee = true;}
      else if(ZOutBluJsq == UVVjLcOMRw){jeGphqhslg = true;}
      if(MPVsoEzxpN == xDcSFuyFdn){LWbeITPsiJ = true;}
      else if(xDcSFuyFdn == MPVsoEzxpN){CcJudsqCyw = true;}
      if(bedrZQxaSi == ArVdifxUKU){yHlTxhTAjd = true;}
      else if(ArVdifxUKU == bedrZQxaSi){dwmGMkmsOg = true;}
      if(toGJbyaFLf == RmyeQaotmR){bXuKgpteHN = true;}
      else if(RmyeQaotmR == toGJbyaFLf){eVeMCGHBsL = true;}
      if(QBmpriaMke == RMWzoDTcKE){fySfWKwEJI = true;}
      if(fgTpRoqdJu == eCaAThsQKU){bTOQfqiFhP = true;}
      if(fmshBWIMQq == oazYYKFxCe){IidADmaQxS = true;}
      while(RMWzoDTcKE == QBmpriaMke){YPrxnceBNM = true;}
      while(eCaAThsQKU == eCaAThsQKU){FRTfFnqzdw = true;}
      while(oazYYKFxCe == oazYYKFxCe){DodFBfxwsX = true;}
      if(GDSMVnVVof == true){GDSMVnVVof = false;}
      if(LUKFoPMxKi == true){LUKFoPMxKi = false;}
      if(hXjRcqMxZe == true){hXjRcqMxZe = false;}
      if(yVZeybjNee == true){yVZeybjNee = false;}
      if(LWbeITPsiJ == true){LWbeITPsiJ = false;}
      if(yHlTxhTAjd == true){yHlTxhTAjd = false;}
      if(bXuKgpteHN == true){bXuKgpteHN = false;}
      if(fySfWKwEJI == true){fySfWKwEJI = false;}
      if(bTOQfqiFhP == true){bTOQfqiFhP = false;}
      if(IidADmaQxS == true){IidADmaQxS = false;}
      if(ZjkUdznGwl == true){ZjkUdznGwl = false;}
      if(lOqaCHJedp == true){lOqaCHJedp = false;}
      if(GnxrFwURbj == true){GnxrFwURbj = false;}
      if(jeGphqhslg == true){jeGphqhslg = false;}
      if(CcJudsqCyw == true){CcJudsqCyw = false;}
      if(dwmGMkmsOg == true){dwmGMkmsOg = false;}
      if(eVeMCGHBsL == true){eVeMCGHBsL = false;}
      if(YPrxnceBNM == true){YPrxnceBNM = false;}
      if(FRTfFnqzdw == true){FRTfFnqzdw = false;}
      if(DodFBfxwsX == true){DodFBfxwsX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KHCHCIGGUR
{ 
  void ruyffHFUWg()
  { 
      bool cOpbUJXZGd = false;
      bool nGfImCKHNl = false;
      bool MjZxOWxYDs = false;
      bool RMBWKVsjQE = false;
      bool upDRqxuBSu = false;
      bool OwfuDsnrNx = false;
      bool LyVMMbFIxR = false;
      bool JZqIpWgHFR = false;
      bool awGHdVfFTR = false;
      bool gAVSswTpFP = false;
      bool qmDBloEWFg = false;
      bool LgmuVPrNip = false;
      bool uzoejJDXPs = false;
      bool CpBoZnrFVo = false;
      bool QIAlFAMawc = false;
      bool EFHOUqxXQc = false;
      bool kgHLdUexVh = false;
      bool XmrtZlzCYj = false;
      bool wcaloxilUh = false;
      bool pTnsEjBnIk = false;
      string FyffXqNPsJ;
      string bwPqJKAoWQ;
      string YczxbEzjlj;
      string TMqcrylaZE;
      string HpWchczBUQ;
      string MsQOMbyhDS;
      string rddJoOEmyL;
      string YYORIiGVPz;
      string FxPUXZwbQP;
      string zDWHMdLNnS;
      string XLCIrmdyGc;
      string VbSEMtNIlO;
      string ScVhLUCHEd;
      string WrhwatuGcj;
      string wxVmtXkSuS;
      string QDbYzupTxW;
      string kWsbFctWcS;
      string yHeBSVGinn;
      string jiMlNTQJwf;
      string DaJFyZDtgQ;
      if(FyffXqNPsJ == XLCIrmdyGc){cOpbUJXZGd = true;}
      else if(XLCIrmdyGc == FyffXqNPsJ){qmDBloEWFg = true;}
      if(bwPqJKAoWQ == VbSEMtNIlO){nGfImCKHNl = true;}
      else if(VbSEMtNIlO == bwPqJKAoWQ){LgmuVPrNip = true;}
      if(YczxbEzjlj == ScVhLUCHEd){MjZxOWxYDs = true;}
      else if(ScVhLUCHEd == YczxbEzjlj){uzoejJDXPs = true;}
      if(TMqcrylaZE == WrhwatuGcj){RMBWKVsjQE = true;}
      else if(WrhwatuGcj == TMqcrylaZE){CpBoZnrFVo = true;}
      if(HpWchczBUQ == wxVmtXkSuS){upDRqxuBSu = true;}
      else if(wxVmtXkSuS == HpWchczBUQ){QIAlFAMawc = true;}
      if(MsQOMbyhDS == QDbYzupTxW){OwfuDsnrNx = true;}
      else if(QDbYzupTxW == MsQOMbyhDS){EFHOUqxXQc = true;}
      if(rddJoOEmyL == kWsbFctWcS){LyVMMbFIxR = true;}
      else if(kWsbFctWcS == rddJoOEmyL){kgHLdUexVh = true;}
      if(YYORIiGVPz == yHeBSVGinn){JZqIpWgHFR = true;}
      if(FxPUXZwbQP == jiMlNTQJwf){awGHdVfFTR = true;}
      if(zDWHMdLNnS == DaJFyZDtgQ){gAVSswTpFP = true;}
      while(yHeBSVGinn == YYORIiGVPz){XmrtZlzCYj = true;}
      while(jiMlNTQJwf == jiMlNTQJwf){wcaloxilUh = true;}
      while(DaJFyZDtgQ == DaJFyZDtgQ){pTnsEjBnIk = true;}
      if(cOpbUJXZGd == true){cOpbUJXZGd = false;}
      if(nGfImCKHNl == true){nGfImCKHNl = false;}
      if(MjZxOWxYDs == true){MjZxOWxYDs = false;}
      if(RMBWKVsjQE == true){RMBWKVsjQE = false;}
      if(upDRqxuBSu == true){upDRqxuBSu = false;}
      if(OwfuDsnrNx == true){OwfuDsnrNx = false;}
      if(LyVMMbFIxR == true){LyVMMbFIxR = false;}
      if(JZqIpWgHFR == true){JZqIpWgHFR = false;}
      if(awGHdVfFTR == true){awGHdVfFTR = false;}
      if(gAVSswTpFP == true){gAVSswTpFP = false;}
      if(qmDBloEWFg == true){qmDBloEWFg = false;}
      if(LgmuVPrNip == true){LgmuVPrNip = false;}
      if(uzoejJDXPs == true){uzoejJDXPs = false;}
      if(CpBoZnrFVo == true){CpBoZnrFVo = false;}
      if(QIAlFAMawc == true){QIAlFAMawc = false;}
      if(EFHOUqxXQc == true){EFHOUqxXQc = false;}
      if(kgHLdUexVh == true){kgHLdUexVh = false;}
      if(XmrtZlzCYj == true){XmrtZlzCYj = false;}
      if(wcaloxilUh == true){wcaloxilUh = false;}
      if(pTnsEjBnIk == true){pTnsEjBnIk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MEGCIWAUSC
{ 
  void FmyDmjoRew()
  { 
      bool EEODPWPzXX = false;
      bool ZRWxxJXjtW = false;
      bool CFQmEMHODk = false;
      bool cypxtTZkbc = false;
      bool UAyfHQsKyn = false;
      bool yauOTynazC = false;
      bool PBultbaZDc = false;
      bool ilHQBBHkfm = false;
      bool TwQOmCCbdw = false;
      bool fykYNTELke = false;
      bool oTHUELSdMR = false;
      bool pCuLiSkgzr = false;
      bool ZzwGxjAiDh = false;
      bool wuzByzouJa = false;
      bool jYOLFcDZot = false;
      bool iXMrFpWAXU = false;
      bool KiaeUuDtNi = false;
      bool coWXHAkjBT = false;
      bool gatIzYiGuH = false;
      bool boWoPAxjqK = false;
      string LIIEhcFUmN;
      string JdIwyJbofF;
      string RLISGexBKU;
      string yhpgaIBzGM;
      string LJOkOYoERb;
      string AYhZYzzpyD;
      string eEJRPambUo;
      string IbhTsIxWEg;
      string oriiUYAPHb;
      string IKBDgHzxVm;
      string kNjcSYpNfP;
      string CclQNlUZxp;
      string aXTsfxZdll;
      string JzBQubIFQw;
      string hljrYfYjpt;
      string lYzeMNsqxU;
      string yLbtGCbUVl;
      string dPJAHnmbTz;
      string XonrzjzVEh;
      string hQIuxVKokV;
      if(LIIEhcFUmN == kNjcSYpNfP){EEODPWPzXX = true;}
      else if(kNjcSYpNfP == LIIEhcFUmN){oTHUELSdMR = true;}
      if(JdIwyJbofF == CclQNlUZxp){ZRWxxJXjtW = true;}
      else if(CclQNlUZxp == JdIwyJbofF){pCuLiSkgzr = true;}
      if(RLISGexBKU == aXTsfxZdll){CFQmEMHODk = true;}
      else if(aXTsfxZdll == RLISGexBKU){ZzwGxjAiDh = true;}
      if(yhpgaIBzGM == JzBQubIFQw){cypxtTZkbc = true;}
      else if(JzBQubIFQw == yhpgaIBzGM){wuzByzouJa = true;}
      if(LJOkOYoERb == hljrYfYjpt){UAyfHQsKyn = true;}
      else if(hljrYfYjpt == LJOkOYoERb){jYOLFcDZot = true;}
      if(AYhZYzzpyD == lYzeMNsqxU){yauOTynazC = true;}
      else if(lYzeMNsqxU == AYhZYzzpyD){iXMrFpWAXU = true;}
      if(eEJRPambUo == yLbtGCbUVl){PBultbaZDc = true;}
      else if(yLbtGCbUVl == eEJRPambUo){KiaeUuDtNi = true;}
      if(IbhTsIxWEg == dPJAHnmbTz){ilHQBBHkfm = true;}
      if(oriiUYAPHb == XonrzjzVEh){TwQOmCCbdw = true;}
      if(IKBDgHzxVm == hQIuxVKokV){fykYNTELke = true;}
      while(dPJAHnmbTz == IbhTsIxWEg){coWXHAkjBT = true;}
      while(XonrzjzVEh == XonrzjzVEh){gatIzYiGuH = true;}
      while(hQIuxVKokV == hQIuxVKokV){boWoPAxjqK = true;}
      if(EEODPWPzXX == true){EEODPWPzXX = false;}
      if(ZRWxxJXjtW == true){ZRWxxJXjtW = false;}
      if(CFQmEMHODk == true){CFQmEMHODk = false;}
      if(cypxtTZkbc == true){cypxtTZkbc = false;}
      if(UAyfHQsKyn == true){UAyfHQsKyn = false;}
      if(yauOTynazC == true){yauOTynazC = false;}
      if(PBultbaZDc == true){PBultbaZDc = false;}
      if(ilHQBBHkfm == true){ilHQBBHkfm = false;}
      if(TwQOmCCbdw == true){TwQOmCCbdw = false;}
      if(fykYNTELke == true){fykYNTELke = false;}
      if(oTHUELSdMR == true){oTHUELSdMR = false;}
      if(pCuLiSkgzr == true){pCuLiSkgzr = false;}
      if(ZzwGxjAiDh == true){ZzwGxjAiDh = false;}
      if(wuzByzouJa == true){wuzByzouJa = false;}
      if(jYOLFcDZot == true){jYOLFcDZot = false;}
      if(iXMrFpWAXU == true){iXMrFpWAXU = false;}
      if(KiaeUuDtNi == true){KiaeUuDtNi = false;}
      if(coWXHAkjBT == true){coWXHAkjBT = false;}
      if(gatIzYiGuH == true){gatIzYiGuH = false;}
      if(boWoPAxjqK == true){boWoPAxjqK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VQEXAKTEXE
{ 
  void serrbUIOEx()
  { 
      bool PqBWroyrzJ = false;
      bool JltdKLurPS = false;
      bool lWiSCoqHsk = false;
      bool ssBDkQJWFt = false;
      bool opVeMkDqDj = false;
      bool naoeBsHiUC = false;
      bool ypyNPQkqst = false;
      bool CYlVdwAEGQ = false;
      bool lAEJxREWBq = false;
      bool IaCDuzqIOw = false;
      bool AMxJhPnSBF = false;
      bool rDbDQyloQy = false;
      bool LNoCkbViae = false;
      bool ErpKPYCtah = false;
      bool ckUwyFyylw = false;
      bool MBqQjlWuXF = false;
      bool sFrVAANRnq = false;
      bool wqNhUasrDf = false;
      bool dXwdRDAYZc = false;
      bool BHVVoXszuy = false;
      string hHZSIkjNgG;
      string bcqTfCrreW;
      string itSpDUsfjg;
      string HdgQefgbUw;
      string UBoNoJRYpL;
      string oCBownniOm;
      string rEcAyxwZoA;
      string UPXhCgEFBs;
      string CTpYrEbrUp;
      string qxMgEQYoOq;
      string NrjopYeTlO;
      string iihVkXNEHt;
      string VEFyJXCpdl;
      string IPpKfKjBhS;
      string YIFFHIPqwf;
      string CUgUVIlkeS;
      string WooAGTrXoZ;
      string nMWoUMzAqA;
      string IKsxjmhVnW;
      string XyVOujSFym;
      if(hHZSIkjNgG == NrjopYeTlO){PqBWroyrzJ = true;}
      else if(NrjopYeTlO == hHZSIkjNgG){AMxJhPnSBF = true;}
      if(bcqTfCrreW == iihVkXNEHt){JltdKLurPS = true;}
      else if(iihVkXNEHt == bcqTfCrreW){rDbDQyloQy = true;}
      if(itSpDUsfjg == VEFyJXCpdl){lWiSCoqHsk = true;}
      else if(VEFyJXCpdl == itSpDUsfjg){LNoCkbViae = true;}
      if(HdgQefgbUw == IPpKfKjBhS){ssBDkQJWFt = true;}
      else if(IPpKfKjBhS == HdgQefgbUw){ErpKPYCtah = true;}
      if(UBoNoJRYpL == YIFFHIPqwf){opVeMkDqDj = true;}
      else if(YIFFHIPqwf == UBoNoJRYpL){ckUwyFyylw = true;}
      if(oCBownniOm == CUgUVIlkeS){naoeBsHiUC = true;}
      else if(CUgUVIlkeS == oCBownniOm){MBqQjlWuXF = true;}
      if(rEcAyxwZoA == WooAGTrXoZ){ypyNPQkqst = true;}
      else if(WooAGTrXoZ == rEcAyxwZoA){sFrVAANRnq = true;}
      if(UPXhCgEFBs == nMWoUMzAqA){CYlVdwAEGQ = true;}
      if(CTpYrEbrUp == IKsxjmhVnW){lAEJxREWBq = true;}
      if(qxMgEQYoOq == XyVOujSFym){IaCDuzqIOw = true;}
      while(nMWoUMzAqA == UPXhCgEFBs){wqNhUasrDf = true;}
      while(IKsxjmhVnW == IKsxjmhVnW){dXwdRDAYZc = true;}
      while(XyVOujSFym == XyVOujSFym){BHVVoXszuy = true;}
      if(PqBWroyrzJ == true){PqBWroyrzJ = false;}
      if(JltdKLurPS == true){JltdKLurPS = false;}
      if(lWiSCoqHsk == true){lWiSCoqHsk = false;}
      if(ssBDkQJWFt == true){ssBDkQJWFt = false;}
      if(opVeMkDqDj == true){opVeMkDqDj = false;}
      if(naoeBsHiUC == true){naoeBsHiUC = false;}
      if(ypyNPQkqst == true){ypyNPQkqst = false;}
      if(CYlVdwAEGQ == true){CYlVdwAEGQ = false;}
      if(lAEJxREWBq == true){lAEJxREWBq = false;}
      if(IaCDuzqIOw == true){IaCDuzqIOw = false;}
      if(AMxJhPnSBF == true){AMxJhPnSBF = false;}
      if(rDbDQyloQy == true){rDbDQyloQy = false;}
      if(LNoCkbViae == true){LNoCkbViae = false;}
      if(ErpKPYCtah == true){ErpKPYCtah = false;}
      if(ckUwyFyylw == true){ckUwyFyylw = false;}
      if(MBqQjlWuXF == true){MBqQjlWuXF = false;}
      if(sFrVAANRnq == true){sFrVAANRnq = false;}
      if(wqNhUasrDf == true){wqNhUasrDf = false;}
      if(dXwdRDAYZc == true){dXwdRDAYZc = false;}
      if(BHVVoXszuy == true){BHVVoXszuy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESXDYNOSWX
{ 
  void blLhQAleli()
  { 
      bool BbHgtljicA = false;
      bool qcNTVoLibH = false;
      bool gMgRRmgCeA = false;
      bool NUGfHzlicF = false;
      bool gtBwnDyaxz = false;
      bool dJpoyouoPH = false;
      bool EgDblVVhMW = false;
      bool DcFWamKjdN = false;
      bool nGFfWDeRgR = false;
      bool DwTVAApZJR = false;
      bool hQNauBETOL = false;
      bool eKLBSybXEh = false;
      bool qEAtSHIjVa = false;
      bool xjZLfWrejV = false;
      bool zKCVmsjRCC = false;
      bool YRUbadQSHn = false;
      bool rTynOtkAVw = false;
      bool GxnihfBeHZ = false;
      bool WqgSBePyjB = false;
      bool GYWwcfMOGs = false;
      string zNOjIiTpqH;
      string ZudqaOqSmn;
      string CaBLLYePCs;
      string HwHiGsqibl;
      string SiubruCNMD;
      string nPXtPXMCXi;
      string EEmxAdntkg;
      string XIpAUSeYSQ;
      string WQDyEqXMSi;
      string foKshOuxbO;
      string GIceffZXZw;
      string rniGMnAosI;
      string GaaCBhxxRF;
      string XhxEKNmYRX;
      string RzmWprGEft;
      string NGESHegZcy;
      string ibGTYKpdwy;
      string AbWUpHnELI;
      string bsQWqQcdxe;
      string gMuToosSxf;
      if(zNOjIiTpqH == GIceffZXZw){BbHgtljicA = true;}
      else if(GIceffZXZw == zNOjIiTpqH){hQNauBETOL = true;}
      if(ZudqaOqSmn == rniGMnAosI){qcNTVoLibH = true;}
      else if(rniGMnAosI == ZudqaOqSmn){eKLBSybXEh = true;}
      if(CaBLLYePCs == GaaCBhxxRF){gMgRRmgCeA = true;}
      else if(GaaCBhxxRF == CaBLLYePCs){qEAtSHIjVa = true;}
      if(HwHiGsqibl == XhxEKNmYRX){NUGfHzlicF = true;}
      else if(XhxEKNmYRX == HwHiGsqibl){xjZLfWrejV = true;}
      if(SiubruCNMD == RzmWprGEft){gtBwnDyaxz = true;}
      else if(RzmWprGEft == SiubruCNMD){zKCVmsjRCC = true;}
      if(nPXtPXMCXi == NGESHegZcy){dJpoyouoPH = true;}
      else if(NGESHegZcy == nPXtPXMCXi){YRUbadQSHn = true;}
      if(EEmxAdntkg == ibGTYKpdwy){EgDblVVhMW = true;}
      else if(ibGTYKpdwy == EEmxAdntkg){rTynOtkAVw = true;}
      if(XIpAUSeYSQ == AbWUpHnELI){DcFWamKjdN = true;}
      if(WQDyEqXMSi == bsQWqQcdxe){nGFfWDeRgR = true;}
      if(foKshOuxbO == gMuToosSxf){DwTVAApZJR = true;}
      while(AbWUpHnELI == XIpAUSeYSQ){GxnihfBeHZ = true;}
      while(bsQWqQcdxe == bsQWqQcdxe){WqgSBePyjB = true;}
      while(gMuToosSxf == gMuToosSxf){GYWwcfMOGs = true;}
      if(BbHgtljicA == true){BbHgtljicA = false;}
      if(qcNTVoLibH == true){qcNTVoLibH = false;}
      if(gMgRRmgCeA == true){gMgRRmgCeA = false;}
      if(NUGfHzlicF == true){NUGfHzlicF = false;}
      if(gtBwnDyaxz == true){gtBwnDyaxz = false;}
      if(dJpoyouoPH == true){dJpoyouoPH = false;}
      if(EgDblVVhMW == true){EgDblVVhMW = false;}
      if(DcFWamKjdN == true){DcFWamKjdN = false;}
      if(nGFfWDeRgR == true){nGFfWDeRgR = false;}
      if(DwTVAApZJR == true){DwTVAApZJR = false;}
      if(hQNauBETOL == true){hQNauBETOL = false;}
      if(eKLBSybXEh == true){eKLBSybXEh = false;}
      if(qEAtSHIjVa == true){qEAtSHIjVa = false;}
      if(xjZLfWrejV == true){xjZLfWrejV = false;}
      if(zKCVmsjRCC == true){zKCVmsjRCC = false;}
      if(YRUbadQSHn == true){YRUbadQSHn = false;}
      if(rTynOtkAVw == true){rTynOtkAVw = false;}
      if(GxnihfBeHZ == true){GxnihfBeHZ = false;}
      if(WqgSBePyjB == true){WqgSBePyjB = false;}
      if(GYWwcfMOGs == true){GYWwcfMOGs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OPWHZHAAOL
{ 
  void FWwNSkydFM()
  { 
      bool xoZMibsuIP = false;
      bool cnOsAABWTc = false;
      bool qIyIfGWidj = false;
      bool wEeffSaKyx = false;
      bool kWtgLsNpGi = false;
      bool RqnkboqRfc = false;
      bool FKQXSXJhNh = false;
      bool ZqYWqUNQxm = false;
      bool rgbuRFQtEp = false;
      bool aJdVraFVOm = false;
      bool jebYJaRRsG = false;
      bool aZUsjYhVFM = false;
      bool HPdWGPMCdQ = false;
      bool OqCJDMEDlq = false;
      bool myAyOBojkT = false;
      bool sjPBfUBERs = false;
      bool NPncqjXKpX = false;
      bool TeiOYIOeHE = false;
      bool acQJXeaAdh = false;
      bool KzkrcXKXGe = false;
      string gncUEaYiYC;
      string RmYbDwbwtf;
      string LKpgLPQuNK;
      string qRQQkgzGsC;
      string ZJYTEbEhex;
      string xauJYWxuJn;
      string JdUOLAWHpV;
      string wVDqFClWbi;
      string LiPPNPVGrN;
      string jExErwnJHE;
      string FwqJAaXDDV;
      string kaSZcaNFAu;
      string dPPclrYyzJ;
      string NbOXdOqGOl;
      string rSCVcIkWaR;
      string iiJLaogOWI;
      string CYEtHJLuwN;
      string iGpNDKMszc;
      string HBXgZeRDxn;
      string hcjGjTNINS;
      if(gncUEaYiYC == FwqJAaXDDV){xoZMibsuIP = true;}
      else if(FwqJAaXDDV == gncUEaYiYC){jebYJaRRsG = true;}
      if(RmYbDwbwtf == kaSZcaNFAu){cnOsAABWTc = true;}
      else if(kaSZcaNFAu == RmYbDwbwtf){aZUsjYhVFM = true;}
      if(LKpgLPQuNK == dPPclrYyzJ){qIyIfGWidj = true;}
      else if(dPPclrYyzJ == LKpgLPQuNK){HPdWGPMCdQ = true;}
      if(qRQQkgzGsC == NbOXdOqGOl){wEeffSaKyx = true;}
      else if(NbOXdOqGOl == qRQQkgzGsC){OqCJDMEDlq = true;}
      if(ZJYTEbEhex == rSCVcIkWaR){kWtgLsNpGi = true;}
      else if(rSCVcIkWaR == ZJYTEbEhex){myAyOBojkT = true;}
      if(xauJYWxuJn == iiJLaogOWI){RqnkboqRfc = true;}
      else if(iiJLaogOWI == xauJYWxuJn){sjPBfUBERs = true;}
      if(JdUOLAWHpV == CYEtHJLuwN){FKQXSXJhNh = true;}
      else if(CYEtHJLuwN == JdUOLAWHpV){NPncqjXKpX = true;}
      if(wVDqFClWbi == iGpNDKMszc){ZqYWqUNQxm = true;}
      if(LiPPNPVGrN == HBXgZeRDxn){rgbuRFQtEp = true;}
      if(jExErwnJHE == hcjGjTNINS){aJdVraFVOm = true;}
      while(iGpNDKMszc == wVDqFClWbi){TeiOYIOeHE = true;}
      while(HBXgZeRDxn == HBXgZeRDxn){acQJXeaAdh = true;}
      while(hcjGjTNINS == hcjGjTNINS){KzkrcXKXGe = true;}
      if(xoZMibsuIP == true){xoZMibsuIP = false;}
      if(cnOsAABWTc == true){cnOsAABWTc = false;}
      if(qIyIfGWidj == true){qIyIfGWidj = false;}
      if(wEeffSaKyx == true){wEeffSaKyx = false;}
      if(kWtgLsNpGi == true){kWtgLsNpGi = false;}
      if(RqnkboqRfc == true){RqnkboqRfc = false;}
      if(FKQXSXJhNh == true){FKQXSXJhNh = false;}
      if(ZqYWqUNQxm == true){ZqYWqUNQxm = false;}
      if(rgbuRFQtEp == true){rgbuRFQtEp = false;}
      if(aJdVraFVOm == true){aJdVraFVOm = false;}
      if(jebYJaRRsG == true){jebYJaRRsG = false;}
      if(aZUsjYhVFM == true){aZUsjYhVFM = false;}
      if(HPdWGPMCdQ == true){HPdWGPMCdQ = false;}
      if(OqCJDMEDlq == true){OqCJDMEDlq = false;}
      if(myAyOBojkT == true){myAyOBojkT = false;}
      if(sjPBfUBERs == true){sjPBfUBERs = false;}
      if(NPncqjXKpX == true){NPncqjXKpX = false;}
      if(TeiOYIOeHE == true){TeiOYIOeHE = false;}
      if(acQJXeaAdh == true){acQJXeaAdh = false;}
      if(KzkrcXKXGe == true){KzkrcXKXGe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ACVBEHTCUS
{ 
  void DbQuaWQeiK()
  { 
      bool IYQeYRtAjH = false;
      bool EYgzampdXu = false;
      bool ZSWXcWksfT = false;
      bool ZEQiWLPXHE = false;
      bool uViAZebKsX = false;
      bool NcRAboCsBC = false;
      bool fATQgAIycP = false;
      bool XRWSzDiWyy = false;
      bool tazIFxlQGg = false;
      bool JWVEYtCRSZ = false;
      bool VdgdAuGzAX = false;
      bool FeuDIFBLLj = false;
      bool NqqwGAwStF = false;
      bool BRDXbPsVHJ = false;
      bool qlQhadbSwT = false;
      bool spGiLelkXz = false;
      bool zmFtWnbWar = false;
      bool LeDBsaaJUb = false;
      bool YcWaLLKUMx = false;
      bool dIyIJDgVLl = false;
      string IaONwKKatc;
      string XQJsOTlTuH;
      string dSGwaGZgAU;
      string FHYAzezlXx;
      string ZcnAGUmwnU;
      string UCsLkoURlo;
      string kcZYXPqItj;
      string UzwxgBeFoG;
      string TdsfACONPJ;
      string JgzhMxCPcq;
      string cdCEzUGudi;
      string KOcfVHjtXU;
      string BdrjZnANkj;
      string yObydobnff;
      string wSjfyuDSLE;
      string NIrIpzkRdL;
      string UrKtkwleCg;
      string fuNqXhtLke;
      string jgCfWpWTHe;
      string DJJULEHouC;
      if(IaONwKKatc == cdCEzUGudi){IYQeYRtAjH = true;}
      else if(cdCEzUGudi == IaONwKKatc){VdgdAuGzAX = true;}
      if(XQJsOTlTuH == KOcfVHjtXU){EYgzampdXu = true;}
      else if(KOcfVHjtXU == XQJsOTlTuH){FeuDIFBLLj = true;}
      if(dSGwaGZgAU == BdrjZnANkj){ZSWXcWksfT = true;}
      else if(BdrjZnANkj == dSGwaGZgAU){NqqwGAwStF = true;}
      if(FHYAzezlXx == yObydobnff){ZEQiWLPXHE = true;}
      else if(yObydobnff == FHYAzezlXx){BRDXbPsVHJ = true;}
      if(ZcnAGUmwnU == wSjfyuDSLE){uViAZebKsX = true;}
      else if(wSjfyuDSLE == ZcnAGUmwnU){qlQhadbSwT = true;}
      if(UCsLkoURlo == NIrIpzkRdL){NcRAboCsBC = true;}
      else if(NIrIpzkRdL == UCsLkoURlo){spGiLelkXz = true;}
      if(kcZYXPqItj == UrKtkwleCg){fATQgAIycP = true;}
      else if(UrKtkwleCg == kcZYXPqItj){zmFtWnbWar = true;}
      if(UzwxgBeFoG == fuNqXhtLke){XRWSzDiWyy = true;}
      if(TdsfACONPJ == jgCfWpWTHe){tazIFxlQGg = true;}
      if(JgzhMxCPcq == DJJULEHouC){JWVEYtCRSZ = true;}
      while(fuNqXhtLke == UzwxgBeFoG){LeDBsaaJUb = true;}
      while(jgCfWpWTHe == jgCfWpWTHe){YcWaLLKUMx = true;}
      while(DJJULEHouC == DJJULEHouC){dIyIJDgVLl = true;}
      if(IYQeYRtAjH == true){IYQeYRtAjH = false;}
      if(EYgzampdXu == true){EYgzampdXu = false;}
      if(ZSWXcWksfT == true){ZSWXcWksfT = false;}
      if(ZEQiWLPXHE == true){ZEQiWLPXHE = false;}
      if(uViAZebKsX == true){uViAZebKsX = false;}
      if(NcRAboCsBC == true){NcRAboCsBC = false;}
      if(fATQgAIycP == true){fATQgAIycP = false;}
      if(XRWSzDiWyy == true){XRWSzDiWyy = false;}
      if(tazIFxlQGg == true){tazIFxlQGg = false;}
      if(JWVEYtCRSZ == true){JWVEYtCRSZ = false;}
      if(VdgdAuGzAX == true){VdgdAuGzAX = false;}
      if(FeuDIFBLLj == true){FeuDIFBLLj = false;}
      if(NqqwGAwStF == true){NqqwGAwStF = false;}
      if(BRDXbPsVHJ == true){BRDXbPsVHJ = false;}
      if(qlQhadbSwT == true){qlQhadbSwT = false;}
      if(spGiLelkXz == true){spGiLelkXz = false;}
      if(zmFtWnbWar == true){zmFtWnbWar = false;}
      if(LeDBsaaJUb == true){LeDBsaaJUb = false;}
      if(YcWaLLKUMx == true){YcWaLLKUMx = false;}
      if(dIyIJDgVLl == true){dIyIJDgVLl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWZWDISVPD
{ 
  void iDlPQPgkKW()
  { 
      bool pcWkCjwSqL = false;
      bool kYIHKEClOL = false;
      bool jaToOtSMVr = false;
      bool yiGRJfdUUl = false;
      bool NVtLBpUinu = false;
      bool QaqfPOJhWI = false;
      bool QjxzNCRpye = false;
      bool ZhQcxOgHmX = false;
      bool ZjXaaXqaCt = false;
      bool WwyMUcXuxz = false;
      bool YejJViJOiB = false;
      bool hBuyhgMWXp = false;
      bool KqnEHciDHU = false;
      bool pkJmyuzNEq = false;
      bool NcrALUBzem = false;
      bool QBWHnhpfCr = false;
      bool AGGOKwqHzl = false;
      bool gzRfcgzmsl = false;
      bool bjYUDnOCyQ = false;
      bool ETLMqHWcoO = false;
      string huJsIGzCwY;
      string DjPizgiVAr;
      string yqMVnUHfCJ;
      string goOAQousUA;
      string WoAgUYykVj;
      string xdJWyqhnEn;
      string yTzmqOVORK;
      string kpBAUIpfBP;
      string WWKSMDfqCZ;
      string GHnfBDoNpF;
      string DiSLyHcIBo;
      string ACloQbIfZm;
      string hdLrDdBUyQ;
      string TbouMmDyTF;
      string aWpNYDUzOZ;
      string tImDWYXaHU;
      string FHKjVYNqbd;
      string XKLULLnySz;
      string JBFXVKnlXm;
      string PcqzzTMFqA;
      if(huJsIGzCwY == DiSLyHcIBo){pcWkCjwSqL = true;}
      else if(DiSLyHcIBo == huJsIGzCwY){YejJViJOiB = true;}
      if(DjPizgiVAr == ACloQbIfZm){kYIHKEClOL = true;}
      else if(ACloQbIfZm == DjPizgiVAr){hBuyhgMWXp = true;}
      if(yqMVnUHfCJ == hdLrDdBUyQ){jaToOtSMVr = true;}
      else if(hdLrDdBUyQ == yqMVnUHfCJ){KqnEHciDHU = true;}
      if(goOAQousUA == TbouMmDyTF){yiGRJfdUUl = true;}
      else if(TbouMmDyTF == goOAQousUA){pkJmyuzNEq = true;}
      if(WoAgUYykVj == aWpNYDUzOZ){NVtLBpUinu = true;}
      else if(aWpNYDUzOZ == WoAgUYykVj){NcrALUBzem = true;}
      if(xdJWyqhnEn == tImDWYXaHU){QaqfPOJhWI = true;}
      else if(tImDWYXaHU == xdJWyqhnEn){QBWHnhpfCr = true;}
      if(yTzmqOVORK == FHKjVYNqbd){QjxzNCRpye = true;}
      else if(FHKjVYNqbd == yTzmqOVORK){AGGOKwqHzl = true;}
      if(kpBAUIpfBP == XKLULLnySz){ZhQcxOgHmX = true;}
      if(WWKSMDfqCZ == JBFXVKnlXm){ZjXaaXqaCt = true;}
      if(GHnfBDoNpF == PcqzzTMFqA){WwyMUcXuxz = true;}
      while(XKLULLnySz == kpBAUIpfBP){gzRfcgzmsl = true;}
      while(JBFXVKnlXm == JBFXVKnlXm){bjYUDnOCyQ = true;}
      while(PcqzzTMFqA == PcqzzTMFqA){ETLMqHWcoO = true;}
      if(pcWkCjwSqL == true){pcWkCjwSqL = false;}
      if(kYIHKEClOL == true){kYIHKEClOL = false;}
      if(jaToOtSMVr == true){jaToOtSMVr = false;}
      if(yiGRJfdUUl == true){yiGRJfdUUl = false;}
      if(NVtLBpUinu == true){NVtLBpUinu = false;}
      if(QaqfPOJhWI == true){QaqfPOJhWI = false;}
      if(QjxzNCRpye == true){QjxzNCRpye = false;}
      if(ZhQcxOgHmX == true){ZhQcxOgHmX = false;}
      if(ZjXaaXqaCt == true){ZjXaaXqaCt = false;}
      if(WwyMUcXuxz == true){WwyMUcXuxz = false;}
      if(YejJViJOiB == true){YejJViJOiB = false;}
      if(hBuyhgMWXp == true){hBuyhgMWXp = false;}
      if(KqnEHciDHU == true){KqnEHciDHU = false;}
      if(pkJmyuzNEq == true){pkJmyuzNEq = false;}
      if(NcrALUBzem == true){NcrALUBzem = false;}
      if(QBWHnhpfCr == true){QBWHnhpfCr = false;}
      if(AGGOKwqHzl == true){AGGOKwqHzl = false;}
      if(gzRfcgzmsl == true){gzRfcgzmsl = false;}
      if(bjYUDnOCyQ == true){bjYUDnOCyQ = false;}
      if(ETLMqHWcoO == true){ETLMqHWcoO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUFQPRJRWP
{ 
  void BBdSWKqVGa()
  { 
      bool pZLaNHaRXY = false;
      bool duofoiEJZj = false;
      bool kOJXlrRkBI = false;
      bool oVOTVJkZNS = false;
      bool ogiWbJeUFS = false;
      bool CJyATaPmnV = false;
      bool opPOjHfVKe = false;
      bool yeuHtDfmub = false;
      bool NweiFeXOzt = false;
      bool sxkrdzQTlT = false;
      bool dJKZTXOqGP = false;
      bool ucrMHrKgJF = false;
      bool jRVPlBsDct = false;
      bool lLBayElFOh = false;
      bool QfHjzQFYjk = false;
      bool ojKgjLmtnS = false;
      bool dKNLcjbQND = false;
      bool FFRanEKkQU = false;
      bool wTSrFCATql = false;
      bool QqQwEFRuGP = false;
      string oSeAgkAopA;
      string DIJVHEbKpy;
      string yNpWOIjceG;
      string lzOOSFXmhU;
      string KRoeynacSV;
      string GAIoEabHlY;
      string AWJjODttDC;
      string fnbVnfYLXa;
      string gGKJzkqZJq;
      string cPBJTmHFQt;
      string tfZQoRXmAY;
      string CQjLrsMAjc;
      string MTkMYPlSBA;
      string XStdfAgsTg;
      string NEYknMfpRZ;
      string aHUmhZuNrY;
      string fFkAAiVFeq;
      string MSfDPIuzXL;
      string jwAbZQyGwG;
      string FTBuBHTYkE;
      if(oSeAgkAopA == tfZQoRXmAY){pZLaNHaRXY = true;}
      else if(tfZQoRXmAY == oSeAgkAopA){dJKZTXOqGP = true;}
      if(DIJVHEbKpy == CQjLrsMAjc){duofoiEJZj = true;}
      else if(CQjLrsMAjc == DIJVHEbKpy){ucrMHrKgJF = true;}
      if(yNpWOIjceG == MTkMYPlSBA){kOJXlrRkBI = true;}
      else if(MTkMYPlSBA == yNpWOIjceG){jRVPlBsDct = true;}
      if(lzOOSFXmhU == XStdfAgsTg){oVOTVJkZNS = true;}
      else if(XStdfAgsTg == lzOOSFXmhU){lLBayElFOh = true;}
      if(KRoeynacSV == NEYknMfpRZ){ogiWbJeUFS = true;}
      else if(NEYknMfpRZ == KRoeynacSV){QfHjzQFYjk = true;}
      if(GAIoEabHlY == aHUmhZuNrY){CJyATaPmnV = true;}
      else if(aHUmhZuNrY == GAIoEabHlY){ojKgjLmtnS = true;}
      if(AWJjODttDC == fFkAAiVFeq){opPOjHfVKe = true;}
      else if(fFkAAiVFeq == AWJjODttDC){dKNLcjbQND = true;}
      if(fnbVnfYLXa == MSfDPIuzXL){yeuHtDfmub = true;}
      if(gGKJzkqZJq == jwAbZQyGwG){NweiFeXOzt = true;}
      if(cPBJTmHFQt == FTBuBHTYkE){sxkrdzQTlT = true;}
      while(MSfDPIuzXL == fnbVnfYLXa){FFRanEKkQU = true;}
      while(jwAbZQyGwG == jwAbZQyGwG){wTSrFCATql = true;}
      while(FTBuBHTYkE == FTBuBHTYkE){QqQwEFRuGP = true;}
      if(pZLaNHaRXY == true){pZLaNHaRXY = false;}
      if(duofoiEJZj == true){duofoiEJZj = false;}
      if(kOJXlrRkBI == true){kOJXlrRkBI = false;}
      if(oVOTVJkZNS == true){oVOTVJkZNS = false;}
      if(ogiWbJeUFS == true){ogiWbJeUFS = false;}
      if(CJyATaPmnV == true){CJyATaPmnV = false;}
      if(opPOjHfVKe == true){opPOjHfVKe = false;}
      if(yeuHtDfmub == true){yeuHtDfmub = false;}
      if(NweiFeXOzt == true){NweiFeXOzt = false;}
      if(sxkrdzQTlT == true){sxkrdzQTlT = false;}
      if(dJKZTXOqGP == true){dJKZTXOqGP = false;}
      if(ucrMHrKgJF == true){ucrMHrKgJF = false;}
      if(jRVPlBsDct == true){jRVPlBsDct = false;}
      if(lLBayElFOh == true){lLBayElFOh = false;}
      if(QfHjzQFYjk == true){QfHjzQFYjk = false;}
      if(ojKgjLmtnS == true){ojKgjLmtnS = false;}
      if(dKNLcjbQND == true){dKNLcjbQND = false;}
      if(FFRanEKkQU == true){FFRanEKkQU = false;}
      if(wTSrFCATql == true){wTSrFCATql = false;}
      if(QqQwEFRuGP == true){QqQwEFRuGP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HALTRKVLDP
{ 
  void aCtrTVSlGq()
  { 
      bool BXGwrgqLsB = false;
      bool rBYGPlXOqu = false;
      bool VWLdkLgCZb = false;
      bool JVcJgSrIWW = false;
      bool uMCkFixOCH = false;
      bool grLfJdMbKf = false;
      bool zolQrVXOYw = false;
      bool tPrTAIUZYC = false;
      bool ORzRuQJxzD = false;
      bool GQxpWFaksj = false;
      bool KhpFNQArfA = false;
      bool IlCIRhpTVb = false;
      bool LaOUpdRCxt = false;
      bool hjgoqgatDd = false;
      bool QRRztTNoXo = false;
      bool PGORXjSUOj = false;
      bool zxtkSYFNRk = false;
      bool GuQrKsJPaV = false;
      bool PcdIdaUOQG = false;
      bool NGeTdSXfgU = false;
      string xYrpTSLBSe;
      string JynDBGcPGt;
      string DMhHtqlyKV;
      string lCwgLuOVJZ;
      string KxbddpdVxO;
      string YFyQnkpjub;
      string gNpwrHCHqG;
      string rHFfiFjEdD;
      string NPAwxfDera;
      string EdZhrwGekW;
      string nVepVRARgh;
      string AlGqORMtzL;
      string DWPQBOgXnm;
      string zETGPqjKZe;
      string flxKaSXhSZ;
      string iMfYTRGOoH;
      string kbdtiuRzbW;
      string hCUTfRYEoh;
      string qyEODmYumx;
      string kVVStEHDbf;
      if(xYrpTSLBSe == nVepVRARgh){BXGwrgqLsB = true;}
      else if(nVepVRARgh == xYrpTSLBSe){KhpFNQArfA = true;}
      if(JynDBGcPGt == AlGqORMtzL){rBYGPlXOqu = true;}
      else if(AlGqORMtzL == JynDBGcPGt){IlCIRhpTVb = true;}
      if(DMhHtqlyKV == DWPQBOgXnm){VWLdkLgCZb = true;}
      else if(DWPQBOgXnm == DMhHtqlyKV){LaOUpdRCxt = true;}
      if(lCwgLuOVJZ == zETGPqjKZe){JVcJgSrIWW = true;}
      else if(zETGPqjKZe == lCwgLuOVJZ){hjgoqgatDd = true;}
      if(KxbddpdVxO == flxKaSXhSZ){uMCkFixOCH = true;}
      else if(flxKaSXhSZ == KxbddpdVxO){QRRztTNoXo = true;}
      if(YFyQnkpjub == iMfYTRGOoH){grLfJdMbKf = true;}
      else if(iMfYTRGOoH == YFyQnkpjub){PGORXjSUOj = true;}
      if(gNpwrHCHqG == kbdtiuRzbW){zolQrVXOYw = true;}
      else if(kbdtiuRzbW == gNpwrHCHqG){zxtkSYFNRk = true;}
      if(rHFfiFjEdD == hCUTfRYEoh){tPrTAIUZYC = true;}
      if(NPAwxfDera == qyEODmYumx){ORzRuQJxzD = true;}
      if(EdZhrwGekW == kVVStEHDbf){GQxpWFaksj = true;}
      while(hCUTfRYEoh == rHFfiFjEdD){GuQrKsJPaV = true;}
      while(qyEODmYumx == qyEODmYumx){PcdIdaUOQG = true;}
      while(kVVStEHDbf == kVVStEHDbf){NGeTdSXfgU = true;}
      if(BXGwrgqLsB == true){BXGwrgqLsB = false;}
      if(rBYGPlXOqu == true){rBYGPlXOqu = false;}
      if(VWLdkLgCZb == true){VWLdkLgCZb = false;}
      if(JVcJgSrIWW == true){JVcJgSrIWW = false;}
      if(uMCkFixOCH == true){uMCkFixOCH = false;}
      if(grLfJdMbKf == true){grLfJdMbKf = false;}
      if(zolQrVXOYw == true){zolQrVXOYw = false;}
      if(tPrTAIUZYC == true){tPrTAIUZYC = false;}
      if(ORzRuQJxzD == true){ORzRuQJxzD = false;}
      if(GQxpWFaksj == true){GQxpWFaksj = false;}
      if(KhpFNQArfA == true){KhpFNQArfA = false;}
      if(IlCIRhpTVb == true){IlCIRhpTVb = false;}
      if(LaOUpdRCxt == true){LaOUpdRCxt = false;}
      if(hjgoqgatDd == true){hjgoqgatDd = false;}
      if(QRRztTNoXo == true){QRRztTNoXo = false;}
      if(PGORXjSUOj == true){PGORXjSUOj = false;}
      if(zxtkSYFNRk == true){zxtkSYFNRk = false;}
      if(GuQrKsJPaV == true){GuQrKsJPaV = false;}
      if(PcdIdaUOQG == true){PcdIdaUOQG = false;}
      if(NGeTdSXfgU == true){NGeTdSXfgU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCPNJRLNJR
{ 
  void IZFbJBqdBP()
  { 
      bool QYduSgKIQk = false;
      bool GglVBDHBUS = false;
      bool hXgIhdoKBR = false;
      bool LTNEtxiMqE = false;
      bool uYLMtodNyn = false;
      bool JDFWfrrVNo = false;
      bool rAGyYmShbE = false;
      bool UtKPXILTNr = false;
      bool zaLMIHNpXB = false;
      bool FMyCMuRMmH = false;
      bool WultTOsozX = false;
      bool fYHUoRntpR = false;
      bool YcKazHuHDb = false;
      bool pzfGVDnQst = false;
      bool OYpzUfFdMu = false;
      bool GXWVitkLuL = false;
      bool SklWhgsAyk = false;
      bool cWBwDAlLFS = false;
      bool CRtHVRbJXb = false;
      bool ScVgaclTQm = false;
      string GDUCOfczST;
      string OedmxMlCMB;
      string BTeEOsuLmp;
      string ygVxOWAlhN;
      string MSfkSkjYkM;
      string QtgnhlYQnU;
      string kQLbUhJgXa;
      string LzUznhmtkc;
      string JVaaZEzgOb;
      string xjyMbwGEPk;
      string bCAJAQYhzA;
      string yeeKLPpkCP;
      string hbSucbAIWr;
      string bidABGUQZI;
      string fQhOdREnAM;
      string GVBACAjEgY;
      string QPLHYPBeJE;
      string tYKsiQtDRK;
      string WMIJlFhcyA;
      string VQjArQFZpN;
      if(GDUCOfczST == bCAJAQYhzA){QYduSgKIQk = true;}
      else if(bCAJAQYhzA == GDUCOfczST){WultTOsozX = true;}
      if(OedmxMlCMB == yeeKLPpkCP){GglVBDHBUS = true;}
      else if(yeeKLPpkCP == OedmxMlCMB){fYHUoRntpR = true;}
      if(BTeEOsuLmp == hbSucbAIWr){hXgIhdoKBR = true;}
      else if(hbSucbAIWr == BTeEOsuLmp){YcKazHuHDb = true;}
      if(ygVxOWAlhN == bidABGUQZI){LTNEtxiMqE = true;}
      else if(bidABGUQZI == ygVxOWAlhN){pzfGVDnQst = true;}
      if(MSfkSkjYkM == fQhOdREnAM){uYLMtodNyn = true;}
      else if(fQhOdREnAM == MSfkSkjYkM){OYpzUfFdMu = true;}
      if(QtgnhlYQnU == GVBACAjEgY){JDFWfrrVNo = true;}
      else if(GVBACAjEgY == QtgnhlYQnU){GXWVitkLuL = true;}
      if(kQLbUhJgXa == QPLHYPBeJE){rAGyYmShbE = true;}
      else if(QPLHYPBeJE == kQLbUhJgXa){SklWhgsAyk = true;}
      if(LzUznhmtkc == tYKsiQtDRK){UtKPXILTNr = true;}
      if(JVaaZEzgOb == WMIJlFhcyA){zaLMIHNpXB = true;}
      if(xjyMbwGEPk == VQjArQFZpN){FMyCMuRMmH = true;}
      while(tYKsiQtDRK == LzUznhmtkc){cWBwDAlLFS = true;}
      while(WMIJlFhcyA == WMIJlFhcyA){CRtHVRbJXb = true;}
      while(VQjArQFZpN == VQjArQFZpN){ScVgaclTQm = true;}
      if(QYduSgKIQk == true){QYduSgKIQk = false;}
      if(GglVBDHBUS == true){GglVBDHBUS = false;}
      if(hXgIhdoKBR == true){hXgIhdoKBR = false;}
      if(LTNEtxiMqE == true){LTNEtxiMqE = false;}
      if(uYLMtodNyn == true){uYLMtodNyn = false;}
      if(JDFWfrrVNo == true){JDFWfrrVNo = false;}
      if(rAGyYmShbE == true){rAGyYmShbE = false;}
      if(UtKPXILTNr == true){UtKPXILTNr = false;}
      if(zaLMIHNpXB == true){zaLMIHNpXB = false;}
      if(FMyCMuRMmH == true){FMyCMuRMmH = false;}
      if(WultTOsozX == true){WultTOsozX = false;}
      if(fYHUoRntpR == true){fYHUoRntpR = false;}
      if(YcKazHuHDb == true){YcKazHuHDb = false;}
      if(pzfGVDnQst == true){pzfGVDnQst = false;}
      if(OYpzUfFdMu == true){OYpzUfFdMu = false;}
      if(GXWVitkLuL == true){GXWVitkLuL = false;}
      if(SklWhgsAyk == true){SklWhgsAyk = false;}
      if(cWBwDAlLFS == true){cWBwDAlLFS = false;}
      if(CRtHVRbJXb == true){CRtHVRbJXb = false;}
      if(ScVgaclTQm == true){ScVgaclTQm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NECOXZGDYS
{ 
  void dtsbFsOBto()
  { 
      bool EpUQDiRGUK = false;
      bool SBuUhmNelA = false;
      bool OkDBhoINik = false;
      bool UflpFoLlum = false;
      bool wmRBVylbew = false;
      bool LgExHSlTiO = false;
      bool ZDXiplPEPr = false;
      bool aaizEaTCej = false;
      bool CfimZnaoil = false;
      bool DrDgMsPhLj = false;
      bool ihMlUjyFsf = false;
      bool ziozLsUjIB = false;
      bool KZUcoiXClL = false;
      bool KkqtAUTwSp = false;
      bool pVwCmTCEUT = false;
      bool XfYJZIMixk = false;
      bool MuTgUNrtyq = false;
      bool ZYRSLodRpU = false;
      bool fTgSmeMhUr = false;
      bool HjygctBOhZ = false;
      string XWlISAlMZz;
      string SMjwIbNTCf;
      string UjjxuhuLks;
      string rEVEuEPrBq;
      string xUYmcDOCTL;
      string fjNCVmloMk;
      string EZafHNpfBD;
      string MVRLiALxTr;
      string TrrZMHqTiH;
      string RaeQlXsreO;
      string MhBQzKRBTV;
      string boUURMhBTz;
      string WWxslkqBYL;
      string GSREekpbaC;
      string oozMfbFKyZ;
      string orYerpkIdN;
      string SQcIOJXPpg;
      string WGaRKgXjNJ;
      string efDyVNtlMo;
      string zgxMiYLqxW;
      if(XWlISAlMZz == MhBQzKRBTV){EpUQDiRGUK = true;}
      else if(MhBQzKRBTV == XWlISAlMZz){ihMlUjyFsf = true;}
      if(SMjwIbNTCf == boUURMhBTz){SBuUhmNelA = true;}
      else if(boUURMhBTz == SMjwIbNTCf){ziozLsUjIB = true;}
      if(UjjxuhuLks == WWxslkqBYL){OkDBhoINik = true;}
      else if(WWxslkqBYL == UjjxuhuLks){KZUcoiXClL = true;}
      if(rEVEuEPrBq == GSREekpbaC){UflpFoLlum = true;}
      else if(GSREekpbaC == rEVEuEPrBq){KkqtAUTwSp = true;}
      if(xUYmcDOCTL == oozMfbFKyZ){wmRBVylbew = true;}
      else if(oozMfbFKyZ == xUYmcDOCTL){pVwCmTCEUT = true;}
      if(fjNCVmloMk == orYerpkIdN){LgExHSlTiO = true;}
      else if(orYerpkIdN == fjNCVmloMk){XfYJZIMixk = true;}
      if(EZafHNpfBD == SQcIOJXPpg){ZDXiplPEPr = true;}
      else if(SQcIOJXPpg == EZafHNpfBD){MuTgUNrtyq = true;}
      if(MVRLiALxTr == WGaRKgXjNJ){aaizEaTCej = true;}
      if(TrrZMHqTiH == efDyVNtlMo){CfimZnaoil = true;}
      if(RaeQlXsreO == zgxMiYLqxW){DrDgMsPhLj = true;}
      while(WGaRKgXjNJ == MVRLiALxTr){ZYRSLodRpU = true;}
      while(efDyVNtlMo == efDyVNtlMo){fTgSmeMhUr = true;}
      while(zgxMiYLqxW == zgxMiYLqxW){HjygctBOhZ = true;}
      if(EpUQDiRGUK == true){EpUQDiRGUK = false;}
      if(SBuUhmNelA == true){SBuUhmNelA = false;}
      if(OkDBhoINik == true){OkDBhoINik = false;}
      if(UflpFoLlum == true){UflpFoLlum = false;}
      if(wmRBVylbew == true){wmRBVylbew = false;}
      if(LgExHSlTiO == true){LgExHSlTiO = false;}
      if(ZDXiplPEPr == true){ZDXiplPEPr = false;}
      if(aaizEaTCej == true){aaizEaTCej = false;}
      if(CfimZnaoil == true){CfimZnaoil = false;}
      if(DrDgMsPhLj == true){DrDgMsPhLj = false;}
      if(ihMlUjyFsf == true){ihMlUjyFsf = false;}
      if(ziozLsUjIB == true){ziozLsUjIB = false;}
      if(KZUcoiXClL == true){KZUcoiXClL = false;}
      if(KkqtAUTwSp == true){KkqtAUTwSp = false;}
      if(pVwCmTCEUT == true){pVwCmTCEUT = false;}
      if(XfYJZIMixk == true){XfYJZIMixk = false;}
      if(MuTgUNrtyq == true){MuTgUNrtyq = false;}
      if(ZYRSLodRpU == true){ZYRSLodRpU = false;}
      if(fTgSmeMhUr == true){fTgSmeMhUr = false;}
      if(HjygctBOhZ == true){HjygctBOhZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NUPYZVYBGC
{ 
  void eSSAIqMbHQ()
  { 
      bool neDKzDCQoV = false;
      bool tPhUPXIJqd = false;
      bool swQbXjBSPO = false;
      bool ETsSBzUVDe = false;
      bool brfzPeHZlx = false;
      bool uAArYrNamP = false;
      bool BjBZRaVPSP = false;
      bool ClFLBAPQMr = false;
      bool bbfRTDTBsI = false;
      bool ktindqqFgo = false;
      bool IrGWtIunpY = false;
      bool bxOtmZEiGO = false;
      bool HUWKeIDRhK = false;
      bool IKiWiiVJXK = false;
      bool IeLTgnfoAD = false;
      bool mIyShnVwqk = false;
      bool FcGeQRNqKD = false;
      bool EuKuGbJCcq = false;
      bool cNQdXzLQou = false;
      bool NYRlFeXfCP = false;
      string oDUxmPcgmU;
      string mVUEipNiPy;
      string cIOxpAxOfD;
      string SnRnPmiCGc;
      string OnpUUnENCw;
      string XabqzgnWGm;
      string SNAjCyDgou;
      string HKcmioRtcC;
      string wiMjfqMZni;
      string zLuTJBmGRV;
      string kWYGoMyoIK;
      string OstEqjBPEK;
      string kdsFwuPIch;
      string BLbGRYJFuS;
      string sWRdUGRpcZ;
      string zWCGkGdSKs;
      string xoMZICRmmR;
      string ZwUkROLOkp;
      string dYfCieJUVK;
      string tptCVDKrVR;
      if(oDUxmPcgmU == kWYGoMyoIK){neDKzDCQoV = true;}
      else if(kWYGoMyoIK == oDUxmPcgmU){IrGWtIunpY = true;}
      if(mVUEipNiPy == OstEqjBPEK){tPhUPXIJqd = true;}
      else if(OstEqjBPEK == mVUEipNiPy){bxOtmZEiGO = true;}
      if(cIOxpAxOfD == kdsFwuPIch){swQbXjBSPO = true;}
      else if(kdsFwuPIch == cIOxpAxOfD){HUWKeIDRhK = true;}
      if(SnRnPmiCGc == BLbGRYJFuS){ETsSBzUVDe = true;}
      else if(BLbGRYJFuS == SnRnPmiCGc){IKiWiiVJXK = true;}
      if(OnpUUnENCw == sWRdUGRpcZ){brfzPeHZlx = true;}
      else if(sWRdUGRpcZ == OnpUUnENCw){IeLTgnfoAD = true;}
      if(XabqzgnWGm == zWCGkGdSKs){uAArYrNamP = true;}
      else if(zWCGkGdSKs == XabqzgnWGm){mIyShnVwqk = true;}
      if(SNAjCyDgou == xoMZICRmmR){BjBZRaVPSP = true;}
      else if(xoMZICRmmR == SNAjCyDgou){FcGeQRNqKD = true;}
      if(HKcmioRtcC == ZwUkROLOkp){ClFLBAPQMr = true;}
      if(wiMjfqMZni == dYfCieJUVK){bbfRTDTBsI = true;}
      if(zLuTJBmGRV == tptCVDKrVR){ktindqqFgo = true;}
      while(ZwUkROLOkp == HKcmioRtcC){EuKuGbJCcq = true;}
      while(dYfCieJUVK == dYfCieJUVK){cNQdXzLQou = true;}
      while(tptCVDKrVR == tptCVDKrVR){NYRlFeXfCP = true;}
      if(neDKzDCQoV == true){neDKzDCQoV = false;}
      if(tPhUPXIJqd == true){tPhUPXIJqd = false;}
      if(swQbXjBSPO == true){swQbXjBSPO = false;}
      if(ETsSBzUVDe == true){ETsSBzUVDe = false;}
      if(brfzPeHZlx == true){brfzPeHZlx = false;}
      if(uAArYrNamP == true){uAArYrNamP = false;}
      if(BjBZRaVPSP == true){BjBZRaVPSP = false;}
      if(ClFLBAPQMr == true){ClFLBAPQMr = false;}
      if(bbfRTDTBsI == true){bbfRTDTBsI = false;}
      if(ktindqqFgo == true){ktindqqFgo = false;}
      if(IrGWtIunpY == true){IrGWtIunpY = false;}
      if(bxOtmZEiGO == true){bxOtmZEiGO = false;}
      if(HUWKeIDRhK == true){HUWKeIDRhK = false;}
      if(IKiWiiVJXK == true){IKiWiiVJXK = false;}
      if(IeLTgnfoAD == true){IeLTgnfoAD = false;}
      if(mIyShnVwqk == true){mIyShnVwqk = false;}
      if(FcGeQRNqKD == true){FcGeQRNqKD = false;}
      if(EuKuGbJCcq == true){EuKuGbJCcq = false;}
      if(cNQdXzLQou == true){cNQdXzLQou = false;}
      if(NYRlFeXfCP == true){NYRlFeXfCP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GMDSWLFYDL
{ 
  void zfkwZLqrQV()
  { 
      bool pWpfIlWQjJ = false;
      bool JiDCxUNJhi = false;
      bool sIkbyKRReF = false;
      bool Nczrzyfzad = false;
      bool ndZhTTWumx = false;
      bool EPYcmhkNgx = false;
      bool UFkewfiLDy = false;
      bool nOhDuOhCHe = false;
      bool nWdhAyEWEQ = false;
      bool MRRcJirtln = false;
      bool kLqnIogUhX = false;
      bool ziGCJxaDdy = false;
      bool aMGlkWwEtM = false;
      bool VmQTtbepYK = false;
      bool QjnfRdLPTL = false;
      bool HoQmMXFFCk = false;
      bool rbaVCLRmIh = false;
      bool SkdShqXZUG = false;
      bool LgkhEgWcGV = false;
      bool VZmnRnISdF = false;
      string jEAqsKrQee;
      string SfaxdWstCM;
      string hNIoIeAJVK;
      string ZXPXmmfFxq;
      string nWmyxARdfe;
      string tEhqnWuLiN;
      string JhuUFtPCJp;
      string pmxKYKZKrH;
      string NWdqPUoYjQ;
      string rUWigFbRsC;
      string kOUonHHWSc;
      string wjTbAmDDFk;
      string FqSsxVQNdS;
      string iHRoWyBoCI;
      string MSGGUIAtht;
      string BXMIxsubqS;
      string pssztnRdEC;
      string kOBwXmjMXo;
      string UVfjQKuJrc;
      string DZxjRSYGMf;
      if(jEAqsKrQee == kOUonHHWSc){pWpfIlWQjJ = true;}
      else if(kOUonHHWSc == jEAqsKrQee){kLqnIogUhX = true;}
      if(SfaxdWstCM == wjTbAmDDFk){JiDCxUNJhi = true;}
      else if(wjTbAmDDFk == SfaxdWstCM){ziGCJxaDdy = true;}
      if(hNIoIeAJVK == FqSsxVQNdS){sIkbyKRReF = true;}
      else if(FqSsxVQNdS == hNIoIeAJVK){aMGlkWwEtM = true;}
      if(ZXPXmmfFxq == iHRoWyBoCI){Nczrzyfzad = true;}
      else if(iHRoWyBoCI == ZXPXmmfFxq){VmQTtbepYK = true;}
      if(nWmyxARdfe == MSGGUIAtht){ndZhTTWumx = true;}
      else if(MSGGUIAtht == nWmyxARdfe){QjnfRdLPTL = true;}
      if(tEhqnWuLiN == BXMIxsubqS){EPYcmhkNgx = true;}
      else if(BXMIxsubqS == tEhqnWuLiN){HoQmMXFFCk = true;}
      if(JhuUFtPCJp == pssztnRdEC){UFkewfiLDy = true;}
      else if(pssztnRdEC == JhuUFtPCJp){rbaVCLRmIh = true;}
      if(pmxKYKZKrH == kOBwXmjMXo){nOhDuOhCHe = true;}
      if(NWdqPUoYjQ == UVfjQKuJrc){nWdhAyEWEQ = true;}
      if(rUWigFbRsC == DZxjRSYGMf){MRRcJirtln = true;}
      while(kOBwXmjMXo == pmxKYKZKrH){SkdShqXZUG = true;}
      while(UVfjQKuJrc == UVfjQKuJrc){LgkhEgWcGV = true;}
      while(DZxjRSYGMf == DZxjRSYGMf){VZmnRnISdF = true;}
      if(pWpfIlWQjJ == true){pWpfIlWQjJ = false;}
      if(JiDCxUNJhi == true){JiDCxUNJhi = false;}
      if(sIkbyKRReF == true){sIkbyKRReF = false;}
      if(Nczrzyfzad == true){Nczrzyfzad = false;}
      if(ndZhTTWumx == true){ndZhTTWumx = false;}
      if(EPYcmhkNgx == true){EPYcmhkNgx = false;}
      if(UFkewfiLDy == true){UFkewfiLDy = false;}
      if(nOhDuOhCHe == true){nOhDuOhCHe = false;}
      if(nWdhAyEWEQ == true){nWdhAyEWEQ = false;}
      if(MRRcJirtln == true){MRRcJirtln = false;}
      if(kLqnIogUhX == true){kLqnIogUhX = false;}
      if(ziGCJxaDdy == true){ziGCJxaDdy = false;}
      if(aMGlkWwEtM == true){aMGlkWwEtM = false;}
      if(VmQTtbepYK == true){VmQTtbepYK = false;}
      if(QjnfRdLPTL == true){QjnfRdLPTL = false;}
      if(HoQmMXFFCk == true){HoQmMXFFCk = false;}
      if(rbaVCLRmIh == true){rbaVCLRmIh = false;}
      if(SkdShqXZUG == true){SkdShqXZUG = false;}
      if(LgkhEgWcGV == true){LgkhEgWcGV = false;}
      if(VZmnRnISdF == true){VZmnRnISdF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PIXENJPMXY
{ 
  void iJpxPZrhKb()
  { 
      bool SFTfailwWp = false;
      bool UpfFVQUcpb = false;
      bool pCsSzcLApO = false;
      bool yBeMIXaGdc = false;
      bool RmxUHtuRxA = false;
      bool NLegEQLBfx = false;
      bool WlFIqTKTxy = false;
      bool oNzMKCEYKF = false;
      bool htDoAmVxHr = false;
      bool LZafFfgodn = false;
      bool ibTyLAMRWB = false;
      bool LmpaPbhPHE = false;
      bool xNLFlPmSGe = false;
      bool VOtWVGaEdA = false;
      bool ZEaFfXizQd = false;
      bool xRhYqVPOMu = false;
      bool NsKqfxrSEI = false;
      bool BdkHdslFYO = false;
      bool fmBcgDgVfA = false;
      bool pLrhlgsiZi = false;
      string wAZBVsIjzQ;
      string jSpebPlFdg;
      string rFrHixxSoN;
      string cnVcXJWwmt;
      string wnbwhgXUQh;
      string NbARuqISRY;
      string upulnwwMHS;
      string spRikEdwYC;
      string ZbCHAAmDhg;
      string BDeOzGspHk;
      string jKNynWKRgq;
      string MLsOzTmmkm;
      string IseaQoLCje;
      string KnonSOOESc;
      string pVWpToKPPf;
      string SGETcpemgz;
      string LHgCgYWEuj;
      string EiTHxmVoGa;
      string dumEMEiUKc;
      string jbWSRinUJt;
      if(wAZBVsIjzQ == jKNynWKRgq){SFTfailwWp = true;}
      else if(jKNynWKRgq == wAZBVsIjzQ){ibTyLAMRWB = true;}
      if(jSpebPlFdg == MLsOzTmmkm){UpfFVQUcpb = true;}
      else if(MLsOzTmmkm == jSpebPlFdg){LmpaPbhPHE = true;}
      if(rFrHixxSoN == IseaQoLCje){pCsSzcLApO = true;}
      else if(IseaQoLCje == rFrHixxSoN){xNLFlPmSGe = true;}
      if(cnVcXJWwmt == KnonSOOESc){yBeMIXaGdc = true;}
      else if(KnonSOOESc == cnVcXJWwmt){VOtWVGaEdA = true;}
      if(wnbwhgXUQh == pVWpToKPPf){RmxUHtuRxA = true;}
      else if(pVWpToKPPf == wnbwhgXUQh){ZEaFfXizQd = true;}
      if(NbARuqISRY == SGETcpemgz){NLegEQLBfx = true;}
      else if(SGETcpemgz == NbARuqISRY){xRhYqVPOMu = true;}
      if(upulnwwMHS == LHgCgYWEuj){WlFIqTKTxy = true;}
      else if(LHgCgYWEuj == upulnwwMHS){NsKqfxrSEI = true;}
      if(spRikEdwYC == EiTHxmVoGa){oNzMKCEYKF = true;}
      if(ZbCHAAmDhg == dumEMEiUKc){htDoAmVxHr = true;}
      if(BDeOzGspHk == jbWSRinUJt){LZafFfgodn = true;}
      while(EiTHxmVoGa == spRikEdwYC){BdkHdslFYO = true;}
      while(dumEMEiUKc == dumEMEiUKc){fmBcgDgVfA = true;}
      while(jbWSRinUJt == jbWSRinUJt){pLrhlgsiZi = true;}
      if(SFTfailwWp == true){SFTfailwWp = false;}
      if(UpfFVQUcpb == true){UpfFVQUcpb = false;}
      if(pCsSzcLApO == true){pCsSzcLApO = false;}
      if(yBeMIXaGdc == true){yBeMIXaGdc = false;}
      if(RmxUHtuRxA == true){RmxUHtuRxA = false;}
      if(NLegEQLBfx == true){NLegEQLBfx = false;}
      if(WlFIqTKTxy == true){WlFIqTKTxy = false;}
      if(oNzMKCEYKF == true){oNzMKCEYKF = false;}
      if(htDoAmVxHr == true){htDoAmVxHr = false;}
      if(LZafFfgodn == true){LZafFfgodn = false;}
      if(ibTyLAMRWB == true){ibTyLAMRWB = false;}
      if(LmpaPbhPHE == true){LmpaPbhPHE = false;}
      if(xNLFlPmSGe == true){xNLFlPmSGe = false;}
      if(VOtWVGaEdA == true){VOtWVGaEdA = false;}
      if(ZEaFfXizQd == true){ZEaFfXizQd = false;}
      if(xRhYqVPOMu == true){xRhYqVPOMu = false;}
      if(NsKqfxrSEI == true){NsKqfxrSEI = false;}
      if(BdkHdslFYO == true){BdkHdslFYO = false;}
      if(fmBcgDgVfA == true){fmBcgDgVfA = false;}
      if(pLrhlgsiZi == true){pLrhlgsiZi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TMNETJKIHW
{ 
  void dRFnLbIKSN()
  { 
      bool FUjCtQymVB = false;
      bool nVjCpVZrIE = false;
      bool uyaZBNHVzr = false;
      bool ONGuSlkiPp = false;
      bool ULKIVGLwwo = false;
      bool INPwYHsJAf = false;
      bool IcmcmZPojD = false;
      bool jqbSijmSEu = false;
      bool CLYJjByKVK = false;
      bool sbhjgrXhVu = false;
      bool pWLrFQkxMo = false;
      bool TaFFcxDdrk = false;
      bool bFSYKIIqkq = false;
      bool LFwIEfAgDS = false;
      bool PAxgqRVcGj = false;
      bool otpjTkEmgx = false;
      bool IsMUdOdwAx = false;
      bool xVZYUaHlgs = false;
      bool lfkBCQPLnT = false;
      bool aMzGKWncCc = false;
      string PIWLVqndtj;
      string RYttAJbEca;
      string JPFaDWCyrw;
      string pRMsGxVwRB;
      string sjIKxPIWny;
      string MRscWzDwIz;
      string nplxsAMAnD;
      string melbhYHtcn;
      string NfJtjYYjVH;
      string tZnSMDyKQx;
      string DHhjKheQuy;
      string qISUkIfqNU;
      string abegJNpTOe;
      string ZwcfjGxYiC;
      string sHoXPkGThE;
      string WGxwVacBaw;
      string qLCPXtelje;
      string KGIKaTmGQX;
      string GVlKHTygKJ;
      string cwylKhFYAU;
      if(PIWLVqndtj == DHhjKheQuy){FUjCtQymVB = true;}
      else if(DHhjKheQuy == PIWLVqndtj){pWLrFQkxMo = true;}
      if(RYttAJbEca == qISUkIfqNU){nVjCpVZrIE = true;}
      else if(qISUkIfqNU == RYttAJbEca){TaFFcxDdrk = true;}
      if(JPFaDWCyrw == abegJNpTOe){uyaZBNHVzr = true;}
      else if(abegJNpTOe == JPFaDWCyrw){bFSYKIIqkq = true;}
      if(pRMsGxVwRB == ZwcfjGxYiC){ONGuSlkiPp = true;}
      else if(ZwcfjGxYiC == pRMsGxVwRB){LFwIEfAgDS = true;}
      if(sjIKxPIWny == sHoXPkGThE){ULKIVGLwwo = true;}
      else if(sHoXPkGThE == sjIKxPIWny){PAxgqRVcGj = true;}
      if(MRscWzDwIz == WGxwVacBaw){INPwYHsJAf = true;}
      else if(WGxwVacBaw == MRscWzDwIz){otpjTkEmgx = true;}
      if(nplxsAMAnD == qLCPXtelje){IcmcmZPojD = true;}
      else if(qLCPXtelje == nplxsAMAnD){IsMUdOdwAx = true;}
      if(melbhYHtcn == KGIKaTmGQX){jqbSijmSEu = true;}
      if(NfJtjYYjVH == GVlKHTygKJ){CLYJjByKVK = true;}
      if(tZnSMDyKQx == cwylKhFYAU){sbhjgrXhVu = true;}
      while(KGIKaTmGQX == melbhYHtcn){xVZYUaHlgs = true;}
      while(GVlKHTygKJ == GVlKHTygKJ){lfkBCQPLnT = true;}
      while(cwylKhFYAU == cwylKhFYAU){aMzGKWncCc = true;}
      if(FUjCtQymVB == true){FUjCtQymVB = false;}
      if(nVjCpVZrIE == true){nVjCpVZrIE = false;}
      if(uyaZBNHVzr == true){uyaZBNHVzr = false;}
      if(ONGuSlkiPp == true){ONGuSlkiPp = false;}
      if(ULKIVGLwwo == true){ULKIVGLwwo = false;}
      if(INPwYHsJAf == true){INPwYHsJAf = false;}
      if(IcmcmZPojD == true){IcmcmZPojD = false;}
      if(jqbSijmSEu == true){jqbSijmSEu = false;}
      if(CLYJjByKVK == true){CLYJjByKVK = false;}
      if(sbhjgrXhVu == true){sbhjgrXhVu = false;}
      if(pWLrFQkxMo == true){pWLrFQkxMo = false;}
      if(TaFFcxDdrk == true){TaFFcxDdrk = false;}
      if(bFSYKIIqkq == true){bFSYKIIqkq = false;}
      if(LFwIEfAgDS == true){LFwIEfAgDS = false;}
      if(PAxgqRVcGj == true){PAxgqRVcGj = false;}
      if(otpjTkEmgx == true){otpjTkEmgx = false;}
      if(IsMUdOdwAx == true){IsMUdOdwAx = false;}
      if(xVZYUaHlgs == true){xVZYUaHlgs = false;}
      if(lfkBCQPLnT == true){lfkBCQPLnT = false;}
      if(aMzGKWncCc == true){aMzGKWncCc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FQIPFNRHAT
{ 
  void PNJgiNGkoC()
  { 
      bool rwXOkfhYZm = false;
      bool GBrPouYnDh = false;
      bool poATHyOhVe = false;
      bool VoCDGFKXuc = false;
      bool JDmhknjeeo = false;
      bool GiKcmDuDHl = false;
      bool QzDuRRyoJi = false;
      bool kBsaYmCSiS = false;
      bool NjDgXldZQC = false;
      bool KHQILJzrPT = false;
      bool ptVuDFpjDz = false;
      bool BbUnXguWXe = false;
      bool mXYGXdjjOO = false;
      bool mKDOcTOIcR = false;
      bool utVQBilbjd = false;
      bool OcTjgRVOWZ = false;
      bool VGVoMpYFLE = false;
      bool SmtFjsBHEo = false;
      bool qHAjAJpShK = false;
      bool xzlCuoYgEL = false;
      string kXUGjfIgKl;
      string iWzJWsdutN;
      string MxkbxQCStb;
      string csHOKhiKhP;
      string ClkyHEyAyW;
      string QYoWcmmrJT;
      string cplhIoOjzo;
      string KTMdLaLmUr;
      string SBTXLEDklW;
      string tpBNlMzCoS;
      string oNAJLwLLKB;
      string azXQBaVOWE;
      string kdybtTSzqz;
      string bIxCDEAKLO;
      string srZjutRjLL;
      string pjfkgKOYPq;
      string dMTLZSCVMx;
      string ZKCHKsDNfz;
      string ChmfIqbMUr;
      string obuTkfXOKc;
      if(kXUGjfIgKl == oNAJLwLLKB){rwXOkfhYZm = true;}
      else if(oNAJLwLLKB == kXUGjfIgKl){ptVuDFpjDz = true;}
      if(iWzJWsdutN == azXQBaVOWE){GBrPouYnDh = true;}
      else if(azXQBaVOWE == iWzJWsdutN){BbUnXguWXe = true;}
      if(MxkbxQCStb == kdybtTSzqz){poATHyOhVe = true;}
      else if(kdybtTSzqz == MxkbxQCStb){mXYGXdjjOO = true;}
      if(csHOKhiKhP == bIxCDEAKLO){VoCDGFKXuc = true;}
      else if(bIxCDEAKLO == csHOKhiKhP){mKDOcTOIcR = true;}
      if(ClkyHEyAyW == srZjutRjLL){JDmhknjeeo = true;}
      else if(srZjutRjLL == ClkyHEyAyW){utVQBilbjd = true;}
      if(QYoWcmmrJT == pjfkgKOYPq){GiKcmDuDHl = true;}
      else if(pjfkgKOYPq == QYoWcmmrJT){OcTjgRVOWZ = true;}
      if(cplhIoOjzo == dMTLZSCVMx){QzDuRRyoJi = true;}
      else if(dMTLZSCVMx == cplhIoOjzo){VGVoMpYFLE = true;}
      if(KTMdLaLmUr == ZKCHKsDNfz){kBsaYmCSiS = true;}
      if(SBTXLEDklW == ChmfIqbMUr){NjDgXldZQC = true;}
      if(tpBNlMzCoS == obuTkfXOKc){KHQILJzrPT = true;}
      while(ZKCHKsDNfz == KTMdLaLmUr){SmtFjsBHEo = true;}
      while(ChmfIqbMUr == ChmfIqbMUr){qHAjAJpShK = true;}
      while(obuTkfXOKc == obuTkfXOKc){xzlCuoYgEL = true;}
      if(rwXOkfhYZm == true){rwXOkfhYZm = false;}
      if(GBrPouYnDh == true){GBrPouYnDh = false;}
      if(poATHyOhVe == true){poATHyOhVe = false;}
      if(VoCDGFKXuc == true){VoCDGFKXuc = false;}
      if(JDmhknjeeo == true){JDmhknjeeo = false;}
      if(GiKcmDuDHl == true){GiKcmDuDHl = false;}
      if(QzDuRRyoJi == true){QzDuRRyoJi = false;}
      if(kBsaYmCSiS == true){kBsaYmCSiS = false;}
      if(NjDgXldZQC == true){NjDgXldZQC = false;}
      if(KHQILJzrPT == true){KHQILJzrPT = false;}
      if(ptVuDFpjDz == true){ptVuDFpjDz = false;}
      if(BbUnXguWXe == true){BbUnXguWXe = false;}
      if(mXYGXdjjOO == true){mXYGXdjjOO = false;}
      if(mKDOcTOIcR == true){mKDOcTOIcR = false;}
      if(utVQBilbjd == true){utVQBilbjd = false;}
      if(OcTjgRVOWZ == true){OcTjgRVOWZ = false;}
      if(VGVoMpYFLE == true){VGVoMpYFLE = false;}
      if(SmtFjsBHEo == true){SmtFjsBHEo = false;}
      if(qHAjAJpShK == true){qHAjAJpShK = false;}
      if(xzlCuoYgEL == true){xzlCuoYgEL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GRDQIGEKQV
{ 
  void jYRnQmSCnN()
  { 
      bool pOTGqlAJwM = false;
      bool NHqTeoQIlt = false;
      bool IijBwEEAaq = false;
      bool LZsKiDtWSr = false;
      bool KtznzjqTfo = false;
      bool hSDsSHeSJm = false;
      bool gAiFBmOfka = false;
      bool utotiNiuBL = false;
      bool MjTkIrWAra = false;
      bool YaMfKJLtlM = false;
      bool VLiEtndJJE = false;
      bool YjQyZxfxwJ = false;
      bool QNmJCThIjZ = false;
      bool CoIopBBOqU = false;
      bool NMqnCoKOGM = false;
      bool dOxcuHXYCZ = false;
      bool GUZjBiabIY = false;
      bool wQFbuDWzHN = false;
      bool JTCWunrfsh = false;
      bool cbMRNsmHlT = false;
      string lhZhOZpAnN;
      string RKEIdSVTOP;
      string onRClBKrBT;
      string TgMIQzLjdt;
      string DgUOSwIuTZ;
      string lIcjlyPWuN;
      string OyyTtkxure;
      string HloUMHSCip;
      string rOXbhLDcWS;
      string innQeEiAUh;
      string yMCoRASIXd;
      string eNmFUzaVlh;
      string gUYZuTxYoH;
      string YShBqfMhJg;
      string rtFrmVAiue;
      string dMOlAdmcty;
      string DsSPFMekOo;
      string mrMEomPflZ;
      string SNcKdLDwBN;
      string rinLdyboma;
      if(lhZhOZpAnN == yMCoRASIXd){pOTGqlAJwM = true;}
      else if(yMCoRASIXd == lhZhOZpAnN){VLiEtndJJE = true;}
      if(RKEIdSVTOP == eNmFUzaVlh){NHqTeoQIlt = true;}
      else if(eNmFUzaVlh == RKEIdSVTOP){YjQyZxfxwJ = true;}
      if(onRClBKrBT == gUYZuTxYoH){IijBwEEAaq = true;}
      else if(gUYZuTxYoH == onRClBKrBT){QNmJCThIjZ = true;}
      if(TgMIQzLjdt == YShBqfMhJg){LZsKiDtWSr = true;}
      else if(YShBqfMhJg == TgMIQzLjdt){CoIopBBOqU = true;}
      if(DgUOSwIuTZ == rtFrmVAiue){KtznzjqTfo = true;}
      else if(rtFrmVAiue == DgUOSwIuTZ){NMqnCoKOGM = true;}
      if(lIcjlyPWuN == dMOlAdmcty){hSDsSHeSJm = true;}
      else if(dMOlAdmcty == lIcjlyPWuN){dOxcuHXYCZ = true;}
      if(OyyTtkxure == DsSPFMekOo){gAiFBmOfka = true;}
      else if(DsSPFMekOo == OyyTtkxure){GUZjBiabIY = true;}
      if(HloUMHSCip == mrMEomPflZ){utotiNiuBL = true;}
      if(rOXbhLDcWS == SNcKdLDwBN){MjTkIrWAra = true;}
      if(innQeEiAUh == rinLdyboma){YaMfKJLtlM = true;}
      while(mrMEomPflZ == HloUMHSCip){wQFbuDWzHN = true;}
      while(SNcKdLDwBN == SNcKdLDwBN){JTCWunrfsh = true;}
      while(rinLdyboma == rinLdyboma){cbMRNsmHlT = true;}
      if(pOTGqlAJwM == true){pOTGqlAJwM = false;}
      if(NHqTeoQIlt == true){NHqTeoQIlt = false;}
      if(IijBwEEAaq == true){IijBwEEAaq = false;}
      if(LZsKiDtWSr == true){LZsKiDtWSr = false;}
      if(KtznzjqTfo == true){KtznzjqTfo = false;}
      if(hSDsSHeSJm == true){hSDsSHeSJm = false;}
      if(gAiFBmOfka == true){gAiFBmOfka = false;}
      if(utotiNiuBL == true){utotiNiuBL = false;}
      if(MjTkIrWAra == true){MjTkIrWAra = false;}
      if(YaMfKJLtlM == true){YaMfKJLtlM = false;}
      if(VLiEtndJJE == true){VLiEtndJJE = false;}
      if(YjQyZxfxwJ == true){YjQyZxfxwJ = false;}
      if(QNmJCThIjZ == true){QNmJCThIjZ = false;}
      if(CoIopBBOqU == true){CoIopBBOqU = false;}
      if(NMqnCoKOGM == true){NMqnCoKOGM = false;}
      if(dOxcuHXYCZ == true){dOxcuHXYCZ = false;}
      if(GUZjBiabIY == true){GUZjBiabIY = false;}
      if(wQFbuDWzHN == true){wQFbuDWzHN = false;}
      if(JTCWunrfsh == true){JTCWunrfsh = false;}
      if(cbMRNsmHlT == true){cbMRNsmHlT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BHNIEWURRP
{ 
  void GKfkSMCCjI()
  { 
      bool iSgdxJWsKV = false;
      bool bsiDzOTScP = false;
      bool zLjPiQwVRC = false;
      bool tdXUYInGum = false;
      bool ZUOieEzoVG = false;
      bool ftJkjXiQug = false;
      bool NAbIaxVOeq = false;
      bool ZMXppexAkd = false;
      bool RGAKVAUlkB = false;
      bool YXLNYYrFHh = false;
      bool ikKegSWSuE = false;
      bool ZhfQOGAQma = false;
      bool ciccRCAJRR = false;
      bool lrsCugwUdC = false;
      bool dCqfaqruyS = false;
      bool XbSfEzHhMd = false;
      bool SMAcShncUh = false;
      bool KemjxZrxBa = false;
      bool KFKysKYMyw = false;
      bool YNIzjQBNNs = false;
      string WKLyRoBcWQ;
      string mPCmqFRZJh;
      string SuhzGAHIfS;
      string GiBcfUqSXA;
      string nCbcKkewMY;
      string GCKQpacLrQ;
      string grxDKDOZGV;
      string OzBJsQSEoV;
      string ULwHMEYjmF;
      string reaGSwFXSH;
      string VFopKHABWY;
      string IXWWwVwoqF;
      string ddmBdiYupx;
      string LtlhzPVFxE;
      string EXMNxUIDKx;
      string APgMcrRnMa;
      string iEKZMNkoWf;
      string zprmBGQYEI;
      string aUkrwwNYEG;
      string xhsVVzMmBi;
      if(WKLyRoBcWQ == VFopKHABWY){iSgdxJWsKV = true;}
      else if(VFopKHABWY == WKLyRoBcWQ){ikKegSWSuE = true;}
      if(mPCmqFRZJh == IXWWwVwoqF){bsiDzOTScP = true;}
      else if(IXWWwVwoqF == mPCmqFRZJh){ZhfQOGAQma = true;}
      if(SuhzGAHIfS == ddmBdiYupx){zLjPiQwVRC = true;}
      else if(ddmBdiYupx == SuhzGAHIfS){ciccRCAJRR = true;}
      if(GiBcfUqSXA == LtlhzPVFxE){tdXUYInGum = true;}
      else if(LtlhzPVFxE == GiBcfUqSXA){lrsCugwUdC = true;}
      if(nCbcKkewMY == EXMNxUIDKx){ZUOieEzoVG = true;}
      else if(EXMNxUIDKx == nCbcKkewMY){dCqfaqruyS = true;}
      if(GCKQpacLrQ == APgMcrRnMa){ftJkjXiQug = true;}
      else if(APgMcrRnMa == GCKQpacLrQ){XbSfEzHhMd = true;}
      if(grxDKDOZGV == iEKZMNkoWf){NAbIaxVOeq = true;}
      else if(iEKZMNkoWf == grxDKDOZGV){SMAcShncUh = true;}
      if(OzBJsQSEoV == zprmBGQYEI){ZMXppexAkd = true;}
      if(ULwHMEYjmF == aUkrwwNYEG){RGAKVAUlkB = true;}
      if(reaGSwFXSH == xhsVVzMmBi){YXLNYYrFHh = true;}
      while(zprmBGQYEI == OzBJsQSEoV){KemjxZrxBa = true;}
      while(aUkrwwNYEG == aUkrwwNYEG){KFKysKYMyw = true;}
      while(xhsVVzMmBi == xhsVVzMmBi){YNIzjQBNNs = true;}
      if(iSgdxJWsKV == true){iSgdxJWsKV = false;}
      if(bsiDzOTScP == true){bsiDzOTScP = false;}
      if(zLjPiQwVRC == true){zLjPiQwVRC = false;}
      if(tdXUYInGum == true){tdXUYInGum = false;}
      if(ZUOieEzoVG == true){ZUOieEzoVG = false;}
      if(ftJkjXiQug == true){ftJkjXiQug = false;}
      if(NAbIaxVOeq == true){NAbIaxVOeq = false;}
      if(ZMXppexAkd == true){ZMXppexAkd = false;}
      if(RGAKVAUlkB == true){RGAKVAUlkB = false;}
      if(YXLNYYrFHh == true){YXLNYYrFHh = false;}
      if(ikKegSWSuE == true){ikKegSWSuE = false;}
      if(ZhfQOGAQma == true){ZhfQOGAQma = false;}
      if(ciccRCAJRR == true){ciccRCAJRR = false;}
      if(lrsCugwUdC == true){lrsCugwUdC = false;}
      if(dCqfaqruyS == true){dCqfaqruyS = false;}
      if(XbSfEzHhMd == true){XbSfEzHhMd = false;}
      if(SMAcShncUh == true){SMAcShncUh = false;}
      if(KemjxZrxBa == true){KemjxZrxBa = false;}
      if(KFKysKYMyw == true){KFKysKYMyw = false;}
      if(YNIzjQBNNs == true){YNIzjQBNNs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XQAUAECCAC
{ 
  void qpLoaUnVIU()
  { 
      bool rAURTHoATr = false;
      bool FEwZTIPdKK = false;
      bool flbFlDGdyu = false;
      bool wlZzhItynJ = false;
      bool OLlemmpRsc = false;
      bool prJHgGXPeP = false;
      bool AKBYuTdwqL = false;
      bool NQpAuUzwRz = false;
      bool NokVEDbSSa = false;
      bool jdTXIEJNiT = false;
      bool IsZgOZCJMM = false;
      bool HaxeCLYfTr = false;
      bool qLdQajxRrq = false;
      bool KlMyqUODGe = false;
      bool BSFGTJfoVw = false;
      bool edsqbxOIGe = false;
      bool cjQUBVOznh = false;
      bool wVYopXFXxR = false;
      bool DHwuMfrVVs = false;
      bool FFxaCRBkEx = false;
      string hPoRCabPrI;
      string UObYdULIZH;
      string ZRJpodOhEg;
      string rhOZLLeCkJ;
      string oZpYXRVpda;
      string QOURwQFycY;
      string LsLKQmABNR;
      string oIXPSzbkRX;
      string HYDcQcMwct;
      string FgYMxuOeIj;
      string QTbMlHqEzx;
      string oUgFQmohtm;
      string aDXSLIjLSW;
      string jwbgGmwqpJ;
      string lIwfFkzTuK;
      string FfkVJMwJAc;
      string XflbNrrzyd;
      string pyqjBRGrMa;
      string IPPHRDLGWs;
      string qlqNkFVURN;
      if(hPoRCabPrI == QTbMlHqEzx){rAURTHoATr = true;}
      else if(QTbMlHqEzx == hPoRCabPrI){IsZgOZCJMM = true;}
      if(UObYdULIZH == oUgFQmohtm){FEwZTIPdKK = true;}
      else if(oUgFQmohtm == UObYdULIZH){HaxeCLYfTr = true;}
      if(ZRJpodOhEg == aDXSLIjLSW){flbFlDGdyu = true;}
      else if(aDXSLIjLSW == ZRJpodOhEg){qLdQajxRrq = true;}
      if(rhOZLLeCkJ == jwbgGmwqpJ){wlZzhItynJ = true;}
      else if(jwbgGmwqpJ == rhOZLLeCkJ){KlMyqUODGe = true;}
      if(oZpYXRVpda == lIwfFkzTuK){OLlemmpRsc = true;}
      else if(lIwfFkzTuK == oZpYXRVpda){BSFGTJfoVw = true;}
      if(QOURwQFycY == FfkVJMwJAc){prJHgGXPeP = true;}
      else if(FfkVJMwJAc == QOURwQFycY){edsqbxOIGe = true;}
      if(LsLKQmABNR == XflbNrrzyd){AKBYuTdwqL = true;}
      else if(XflbNrrzyd == LsLKQmABNR){cjQUBVOznh = true;}
      if(oIXPSzbkRX == pyqjBRGrMa){NQpAuUzwRz = true;}
      if(HYDcQcMwct == IPPHRDLGWs){NokVEDbSSa = true;}
      if(FgYMxuOeIj == qlqNkFVURN){jdTXIEJNiT = true;}
      while(pyqjBRGrMa == oIXPSzbkRX){wVYopXFXxR = true;}
      while(IPPHRDLGWs == IPPHRDLGWs){DHwuMfrVVs = true;}
      while(qlqNkFVURN == qlqNkFVURN){FFxaCRBkEx = true;}
      if(rAURTHoATr == true){rAURTHoATr = false;}
      if(FEwZTIPdKK == true){FEwZTIPdKK = false;}
      if(flbFlDGdyu == true){flbFlDGdyu = false;}
      if(wlZzhItynJ == true){wlZzhItynJ = false;}
      if(OLlemmpRsc == true){OLlemmpRsc = false;}
      if(prJHgGXPeP == true){prJHgGXPeP = false;}
      if(AKBYuTdwqL == true){AKBYuTdwqL = false;}
      if(NQpAuUzwRz == true){NQpAuUzwRz = false;}
      if(NokVEDbSSa == true){NokVEDbSSa = false;}
      if(jdTXIEJNiT == true){jdTXIEJNiT = false;}
      if(IsZgOZCJMM == true){IsZgOZCJMM = false;}
      if(HaxeCLYfTr == true){HaxeCLYfTr = false;}
      if(qLdQajxRrq == true){qLdQajxRrq = false;}
      if(KlMyqUODGe == true){KlMyqUODGe = false;}
      if(BSFGTJfoVw == true){BSFGTJfoVw = false;}
      if(edsqbxOIGe == true){edsqbxOIGe = false;}
      if(cjQUBVOznh == true){cjQUBVOznh = false;}
      if(wVYopXFXxR == true){wVYopXFXxR = false;}
      if(DHwuMfrVVs == true){DHwuMfrVVs = false;}
      if(FFxaCRBkEx == true){FFxaCRBkEx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CJQAMSRKSX
{ 
  void QMqsebWSwE()
  { 
      bool zNAgaZOtCT = false;
      bool lBbymhdLEG = false;
      bool PxuXgCiNIZ = false;
      bool GauMnwdXDt = false;
      bool BmmKbYNBLS = false;
      bool QpwHeCRczY = false;
      bool qAlcNKGPJq = false;
      bool DGHJEbJkuI = false;
      bool ngBoIQdmgl = false;
      bool dBXeDABJxQ = false;
      bool RyrUOKhlCC = false;
      bool rggpjJywTw = false;
      bool gShWMChcGE = false;
      bool aAneppogay = false;
      bool hrkesxUgts = false;
      bool CEpAjzPUIM = false;
      bool cFfybrsBAs = false;
      bool URVUOnhDdO = false;
      bool gAiMCWJmtq = false;
      bool aTXNVcLmCB = false;
      string CtOwZFBLNJ;
      string pUlFoKhuCL;
      string SFIunobdIw;
      string HIpraYpLTQ;
      string CnrYKuyPcQ;
      string CCaMsxkSIk;
      string dWCQCheseP;
      string UVblJdMjks;
      string qLArtEgczd;
      string nWDimelaVc;
      string PEkNufaoDO;
      string jBhPtSVJWy;
      string ABsBaySszd;
      string rlNHclZmwN;
      string crZjsmnmnT;
      string JbDXcNKjlx;
      string MhpYWymamH;
      string riNIUIbJHn;
      string JeEeUPhpeO;
      string apAzAuBANu;
      if(CtOwZFBLNJ == PEkNufaoDO){zNAgaZOtCT = true;}
      else if(PEkNufaoDO == CtOwZFBLNJ){RyrUOKhlCC = true;}
      if(pUlFoKhuCL == jBhPtSVJWy){lBbymhdLEG = true;}
      else if(jBhPtSVJWy == pUlFoKhuCL){rggpjJywTw = true;}
      if(SFIunobdIw == ABsBaySszd){PxuXgCiNIZ = true;}
      else if(ABsBaySszd == SFIunobdIw){gShWMChcGE = true;}
      if(HIpraYpLTQ == rlNHclZmwN){GauMnwdXDt = true;}
      else if(rlNHclZmwN == HIpraYpLTQ){aAneppogay = true;}
      if(CnrYKuyPcQ == crZjsmnmnT){BmmKbYNBLS = true;}
      else if(crZjsmnmnT == CnrYKuyPcQ){hrkesxUgts = true;}
      if(CCaMsxkSIk == JbDXcNKjlx){QpwHeCRczY = true;}
      else if(JbDXcNKjlx == CCaMsxkSIk){CEpAjzPUIM = true;}
      if(dWCQCheseP == MhpYWymamH){qAlcNKGPJq = true;}
      else if(MhpYWymamH == dWCQCheseP){cFfybrsBAs = true;}
      if(UVblJdMjks == riNIUIbJHn){DGHJEbJkuI = true;}
      if(qLArtEgczd == JeEeUPhpeO){ngBoIQdmgl = true;}
      if(nWDimelaVc == apAzAuBANu){dBXeDABJxQ = true;}
      while(riNIUIbJHn == UVblJdMjks){URVUOnhDdO = true;}
      while(JeEeUPhpeO == JeEeUPhpeO){gAiMCWJmtq = true;}
      while(apAzAuBANu == apAzAuBANu){aTXNVcLmCB = true;}
      if(zNAgaZOtCT == true){zNAgaZOtCT = false;}
      if(lBbymhdLEG == true){lBbymhdLEG = false;}
      if(PxuXgCiNIZ == true){PxuXgCiNIZ = false;}
      if(GauMnwdXDt == true){GauMnwdXDt = false;}
      if(BmmKbYNBLS == true){BmmKbYNBLS = false;}
      if(QpwHeCRczY == true){QpwHeCRczY = false;}
      if(qAlcNKGPJq == true){qAlcNKGPJq = false;}
      if(DGHJEbJkuI == true){DGHJEbJkuI = false;}
      if(ngBoIQdmgl == true){ngBoIQdmgl = false;}
      if(dBXeDABJxQ == true){dBXeDABJxQ = false;}
      if(RyrUOKhlCC == true){RyrUOKhlCC = false;}
      if(rggpjJywTw == true){rggpjJywTw = false;}
      if(gShWMChcGE == true){gShWMChcGE = false;}
      if(aAneppogay == true){aAneppogay = false;}
      if(hrkesxUgts == true){hrkesxUgts = false;}
      if(CEpAjzPUIM == true){CEpAjzPUIM = false;}
      if(cFfybrsBAs == true){cFfybrsBAs = false;}
      if(URVUOnhDdO == true){URVUOnhDdO = false;}
      if(gAiMCWJmtq == true){gAiMCWJmtq = false;}
      if(aTXNVcLmCB == true){aTXNVcLmCB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PMIJFKPXHA
{ 
  void qTEAiUdzYh()
  { 
      bool wTyeJMkmLA = false;
      bool JuOQjHMpzQ = false;
      bool CTLLZsulAW = false;
      bool xZBWFJumos = false;
      bool FlZKHUlifb = false;
      bool nUidsbIlEQ = false;
      bool QzmnCisqKZ = false;
      bool MYAFKPsBEF = false;
      bool HMGXhbpXdd = false;
      bool AIiXcGzlHY = false;
      bool atXFPPTdSc = false;
      bool hHhyJDrOFZ = false;
      bool rUNgYDpbbD = false;
      bool PHsedMnAIS = false;
      bool HMFAusakOZ = false;
      bool OkggfGgqgL = false;
      bool ZqBOMaNCTw = false;
      bool OrGlSePMlf = false;
      bool cENCoeZMyX = false;
      bool fxTwsPKqmT = false;
      string eujgiNEjQb;
      string WOVICIMVBK;
      string JNHHTkbzsn;
      string WUKdQSICQR;
      string aKVuUTkSHh;
      string gXbClRncMy;
      string lFqcFCErrj;
      string AKFiiyqLlz;
      string AJqLHzrHqz;
      string dfoRfVTspS;
      string PraXhVRrSm;
      string ZbpNxcNfVF;
      string JxArFTUmCN;
      string exVTjHiSdk;
      string gAnDYCpbUD;
      string HmXjJSrhSN;
      string AeoFIcFVdp;
      string tuCjYIIxTC;
      string dsRzFqZkKR;
      string PAzPjBLiuw;
      if(eujgiNEjQb == PraXhVRrSm){wTyeJMkmLA = true;}
      else if(PraXhVRrSm == eujgiNEjQb){atXFPPTdSc = true;}
      if(WOVICIMVBK == ZbpNxcNfVF){JuOQjHMpzQ = true;}
      else if(ZbpNxcNfVF == WOVICIMVBK){hHhyJDrOFZ = true;}
      if(JNHHTkbzsn == JxArFTUmCN){CTLLZsulAW = true;}
      else if(JxArFTUmCN == JNHHTkbzsn){rUNgYDpbbD = true;}
      if(WUKdQSICQR == exVTjHiSdk){xZBWFJumos = true;}
      else if(exVTjHiSdk == WUKdQSICQR){PHsedMnAIS = true;}
      if(aKVuUTkSHh == gAnDYCpbUD){FlZKHUlifb = true;}
      else if(gAnDYCpbUD == aKVuUTkSHh){HMFAusakOZ = true;}
      if(gXbClRncMy == HmXjJSrhSN){nUidsbIlEQ = true;}
      else if(HmXjJSrhSN == gXbClRncMy){OkggfGgqgL = true;}
      if(lFqcFCErrj == AeoFIcFVdp){QzmnCisqKZ = true;}
      else if(AeoFIcFVdp == lFqcFCErrj){ZqBOMaNCTw = true;}
      if(AKFiiyqLlz == tuCjYIIxTC){MYAFKPsBEF = true;}
      if(AJqLHzrHqz == dsRzFqZkKR){HMGXhbpXdd = true;}
      if(dfoRfVTspS == PAzPjBLiuw){AIiXcGzlHY = true;}
      while(tuCjYIIxTC == AKFiiyqLlz){OrGlSePMlf = true;}
      while(dsRzFqZkKR == dsRzFqZkKR){cENCoeZMyX = true;}
      while(PAzPjBLiuw == PAzPjBLiuw){fxTwsPKqmT = true;}
      if(wTyeJMkmLA == true){wTyeJMkmLA = false;}
      if(JuOQjHMpzQ == true){JuOQjHMpzQ = false;}
      if(CTLLZsulAW == true){CTLLZsulAW = false;}
      if(xZBWFJumos == true){xZBWFJumos = false;}
      if(FlZKHUlifb == true){FlZKHUlifb = false;}
      if(nUidsbIlEQ == true){nUidsbIlEQ = false;}
      if(QzmnCisqKZ == true){QzmnCisqKZ = false;}
      if(MYAFKPsBEF == true){MYAFKPsBEF = false;}
      if(HMGXhbpXdd == true){HMGXhbpXdd = false;}
      if(AIiXcGzlHY == true){AIiXcGzlHY = false;}
      if(atXFPPTdSc == true){atXFPPTdSc = false;}
      if(hHhyJDrOFZ == true){hHhyJDrOFZ = false;}
      if(rUNgYDpbbD == true){rUNgYDpbbD = false;}
      if(PHsedMnAIS == true){PHsedMnAIS = false;}
      if(HMFAusakOZ == true){HMFAusakOZ = false;}
      if(OkggfGgqgL == true){OkggfGgqgL = false;}
      if(ZqBOMaNCTw == true){ZqBOMaNCTw = false;}
      if(OrGlSePMlf == true){OrGlSePMlf = false;}
      if(cENCoeZMyX == true){cENCoeZMyX = false;}
      if(fxTwsPKqmT == true){fxTwsPKqmT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WGNVOKAZQF
{ 
  void NqSZddUwDJ()
  { 
      bool NanDCzBezE = false;
      bool EZgGnyyjxa = false;
      bool TAuXYGarsR = false;
      bool OcjFdzKIAg = false;
      bool PwbjkbExIn = false;
      bool rCMoeNfQeu = false;
      bool XJkhoaobco = false;
      bool moiPKXXKlx = false;
      bool CdiEYLQuZP = false;
      bool StdEIGKttK = false;
      bool lcUTBDSwdH = false;
      bool pUegstZgIc = false;
      bool JtBNVsKeGD = false;
      bool NcQbLYIODV = false;
      bool sUQRYxPwLN = false;
      bool fckQAqaHyH = false;
      bool rnoatMECVT = false;
      bool lLcmjodinX = false;
      bool dOSrWjrzbT = false;
      bool xBPudEepXL = false;
      string zklQakPunk;
      string fybCwKmPkz;
      string EAakXNPzhj;
      string ZyrJbMmose;
      string bEiaMYCJQW;
      string xXpNAzKAsM;
      string UPMELhFSZj;
      string WxWGXzRzXz;
      string LFiLlCHdJb;
      string BlufJLqdPe;
      string SiifzABipA;
      string hLbtBOgBSI;
      string ZaJyhkBpxL;
      string HmisgbWCLk;
      string BYnItpKBdt;
      string epLHFqZkyO;
      string yKldrubiMZ;
      string reogHBmAEq;
      string azMCgRabno;
      string BkDxmplJPz;
      if(zklQakPunk == SiifzABipA){NanDCzBezE = true;}
      else if(SiifzABipA == zklQakPunk){lcUTBDSwdH = true;}
      if(fybCwKmPkz == hLbtBOgBSI){EZgGnyyjxa = true;}
      else if(hLbtBOgBSI == fybCwKmPkz){pUegstZgIc = true;}
      if(EAakXNPzhj == ZaJyhkBpxL){TAuXYGarsR = true;}
      else if(ZaJyhkBpxL == EAakXNPzhj){JtBNVsKeGD = true;}
      if(ZyrJbMmose == HmisgbWCLk){OcjFdzKIAg = true;}
      else if(HmisgbWCLk == ZyrJbMmose){NcQbLYIODV = true;}
      if(bEiaMYCJQW == BYnItpKBdt){PwbjkbExIn = true;}
      else if(BYnItpKBdt == bEiaMYCJQW){sUQRYxPwLN = true;}
      if(xXpNAzKAsM == epLHFqZkyO){rCMoeNfQeu = true;}
      else if(epLHFqZkyO == xXpNAzKAsM){fckQAqaHyH = true;}
      if(UPMELhFSZj == yKldrubiMZ){XJkhoaobco = true;}
      else if(yKldrubiMZ == UPMELhFSZj){rnoatMECVT = true;}
      if(WxWGXzRzXz == reogHBmAEq){moiPKXXKlx = true;}
      if(LFiLlCHdJb == azMCgRabno){CdiEYLQuZP = true;}
      if(BlufJLqdPe == BkDxmplJPz){StdEIGKttK = true;}
      while(reogHBmAEq == WxWGXzRzXz){lLcmjodinX = true;}
      while(azMCgRabno == azMCgRabno){dOSrWjrzbT = true;}
      while(BkDxmplJPz == BkDxmplJPz){xBPudEepXL = true;}
      if(NanDCzBezE == true){NanDCzBezE = false;}
      if(EZgGnyyjxa == true){EZgGnyyjxa = false;}
      if(TAuXYGarsR == true){TAuXYGarsR = false;}
      if(OcjFdzKIAg == true){OcjFdzKIAg = false;}
      if(PwbjkbExIn == true){PwbjkbExIn = false;}
      if(rCMoeNfQeu == true){rCMoeNfQeu = false;}
      if(XJkhoaobco == true){XJkhoaobco = false;}
      if(moiPKXXKlx == true){moiPKXXKlx = false;}
      if(CdiEYLQuZP == true){CdiEYLQuZP = false;}
      if(StdEIGKttK == true){StdEIGKttK = false;}
      if(lcUTBDSwdH == true){lcUTBDSwdH = false;}
      if(pUegstZgIc == true){pUegstZgIc = false;}
      if(JtBNVsKeGD == true){JtBNVsKeGD = false;}
      if(NcQbLYIODV == true){NcQbLYIODV = false;}
      if(sUQRYxPwLN == true){sUQRYxPwLN = false;}
      if(fckQAqaHyH == true){fckQAqaHyH = false;}
      if(rnoatMECVT == true){rnoatMECVT = false;}
      if(lLcmjodinX == true){lLcmjodinX = false;}
      if(dOSrWjrzbT == true){dOSrWjrzbT = false;}
      if(xBPudEepXL == true){xBPudEepXL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DDTEBNVPPG
{ 
  void qpurryFtBy()
  { 
      bool PwAJIVaDUP = false;
      bool tasjQTZNbk = false;
      bool ZqFRKETeJN = false;
      bool UNKPFcoZXL = false;
      bool gEdbQkyxLx = false;
      bool rPqhJXqiyE = false;
      bool BwsGufQddn = false;
      bool eAoPDUNcBZ = false;
      bool GWTMVFWcFg = false;
      bool lGbTJkKWgk = false;
      bool TUSXRrZbdo = false;
      bool JNhXyecgkp = false;
      bool JnXxBYYVGS = false;
      bool JqwPGkDutc = false;
      bool etyQWXYDVd = false;
      bool IclpafwVVs = false;
      bool TEVLeSRRRM = false;
      bool bgmHKOoGZd = false;
      bool AUzbKfFFoZ = false;
      bool nhYBJZYmlE = false;
      string pnnExkiFIY;
      string tbWVZCBIym;
      string PFkxNuGZBA;
      string MSYjUAmlXU;
      string VNnXJnhKFY;
      string tKMgmjDppC;
      string eIDHLaCmBY;
      string PPkdRBRMnY;
      string MuTcFCFrxj;
      string xwuVpMKfLh;
      string luJgJeYhOk;
      string SqCQoinaBJ;
      string UKpQbSUPnF;
      string qkAFmRkmSa;
      string cXcLQGsdfG;
      string XidCNbFsFp;
      string JJtJsgpxdW;
      string xBHagxgdzU;
      string YpighIHyrL;
      string MrgcQScSSi;
      if(pnnExkiFIY == luJgJeYhOk){PwAJIVaDUP = true;}
      else if(luJgJeYhOk == pnnExkiFIY){TUSXRrZbdo = true;}
      if(tbWVZCBIym == SqCQoinaBJ){tasjQTZNbk = true;}
      else if(SqCQoinaBJ == tbWVZCBIym){JNhXyecgkp = true;}
      if(PFkxNuGZBA == UKpQbSUPnF){ZqFRKETeJN = true;}
      else if(UKpQbSUPnF == PFkxNuGZBA){JnXxBYYVGS = true;}
      if(MSYjUAmlXU == qkAFmRkmSa){UNKPFcoZXL = true;}
      else if(qkAFmRkmSa == MSYjUAmlXU){JqwPGkDutc = true;}
      if(VNnXJnhKFY == cXcLQGsdfG){gEdbQkyxLx = true;}
      else if(cXcLQGsdfG == VNnXJnhKFY){etyQWXYDVd = true;}
      if(tKMgmjDppC == XidCNbFsFp){rPqhJXqiyE = true;}
      else if(XidCNbFsFp == tKMgmjDppC){IclpafwVVs = true;}
      if(eIDHLaCmBY == JJtJsgpxdW){BwsGufQddn = true;}
      else if(JJtJsgpxdW == eIDHLaCmBY){TEVLeSRRRM = true;}
      if(PPkdRBRMnY == xBHagxgdzU){eAoPDUNcBZ = true;}
      if(MuTcFCFrxj == YpighIHyrL){GWTMVFWcFg = true;}
      if(xwuVpMKfLh == MrgcQScSSi){lGbTJkKWgk = true;}
      while(xBHagxgdzU == PPkdRBRMnY){bgmHKOoGZd = true;}
      while(YpighIHyrL == YpighIHyrL){AUzbKfFFoZ = true;}
      while(MrgcQScSSi == MrgcQScSSi){nhYBJZYmlE = true;}
      if(PwAJIVaDUP == true){PwAJIVaDUP = false;}
      if(tasjQTZNbk == true){tasjQTZNbk = false;}
      if(ZqFRKETeJN == true){ZqFRKETeJN = false;}
      if(UNKPFcoZXL == true){UNKPFcoZXL = false;}
      if(gEdbQkyxLx == true){gEdbQkyxLx = false;}
      if(rPqhJXqiyE == true){rPqhJXqiyE = false;}
      if(BwsGufQddn == true){BwsGufQddn = false;}
      if(eAoPDUNcBZ == true){eAoPDUNcBZ = false;}
      if(GWTMVFWcFg == true){GWTMVFWcFg = false;}
      if(lGbTJkKWgk == true){lGbTJkKWgk = false;}
      if(TUSXRrZbdo == true){TUSXRrZbdo = false;}
      if(JNhXyecgkp == true){JNhXyecgkp = false;}
      if(JnXxBYYVGS == true){JnXxBYYVGS = false;}
      if(JqwPGkDutc == true){JqwPGkDutc = false;}
      if(etyQWXYDVd == true){etyQWXYDVd = false;}
      if(IclpafwVVs == true){IclpafwVVs = false;}
      if(TEVLeSRRRM == true){TEVLeSRRRM = false;}
      if(bgmHKOoGZd == true){bgmHKOoGZd = false;}
      if(AUzbKfFFoZ == true){AUzbKfFFoZ = false;}
      if(nhYBJZYmlE == true){nhYBJZYmlE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MAVISAJKYD
{ 
  void XSoJBuustB()
  { 
      bool MHUiNodXNs = false;
      bool elcqdBeYiD = false;
      bool hdTxIXCWlf = false;
      bool LMxSSVtIVL = false;
      bool cUNfuPpXhc = false;
      bool oTzWOimXZp = false;
      bool mGkhgRoKXI = false;
      bool GVCWZNQnBs = false;
      bool gdnJprNZDj = false;
      bool hVifXWifzd = false;
      bool ZfzZVTQbwB = false;
      bool SzVfIIRbqn = false;
      bool DPGnZjmWzD = false;
      bool djoXTBeNmW = false;
      bool alcBRiACXP = false;
      bool EHoKZKYLAk = false;
      bool ftcsXhJyMG = false;
      bool dEnTMRlFWp = false;
      bool jkyiyWueyJ = false;
      bool bSNBqgJidi = false;
      string FxSSfxBoAF;
      string AtJxauGXDj;
      string JNBfEbzqhU;
      string LuUiZMCfUF;
      string SXfBHOuFjc;
      string ALuJQqwmOD;
      string xJHfsEZaXO;
      string saDxQkhzXo;
      string ftHEUAzLRh;
      string PPRRIIQAIC;
      string oThVjZIyrf;
      string JxOYWDCDLs;
      string FOJoydIloH;
      string UhqVAMLkTu;
      string qBSlYSAstF;
      string GNnPxZKrWG;
      string QWIjKbFsXK;
      string qQiQBEuXPf;
      string cPqjBHsbYZ;
      string BSOMdUrhax;
      if(FxSSfxBoAF == oThVjZIyrf){MHUiNodXNs = true;}
      else if(oThVjZIyrf == FxSSfxBoAF){ZfzZVTQbwB = true;}
      if(AtJxauGXDj == JxOYWDCDLs){elcqdBeYiD = true;}
      else if(JxOYWDCDLs == AtJxauGXDj){SzVfIIRbqn = true;}
      if(JNBfEbzqhU == FOJoydIloH){hdTxIXCWlf = true;}
      else if(FOJoydIloH == JNBfEbzqhU){DPGnZjmWzD = true;}
      if(LuUiZMCfUF == UhqVAMLkTu){LMxSSVtIVL = true;}
      else if(UhqVAMLkTu == LuUiZMCfUF){djoXTBeNmW = true;}
      if(SXfBHOuFjc == qBSlYSAstF){cUNfuPpXhc = true;}
      else if(qBSlYSAstF == SXfBHOuFjc){alcBRiACXP = true;}
      if(ALuJQqwmOD == GNnPxZKrWG){oTzWOimXZp = true;}
      else if(GNnPxZKrWG == ALuJQqwmOD){EHoKZKYLAk = true;}
      if(xJHfsEZaXO == QWIjKbFsXK){mGkhgRoKXI = true;}
      else if(QWIjKbFsXK == xJHfsEZaXO){ftcsXhJyMG = true;}
      if(saDxQkhzXo == qQiQBEuXPf){GVCWZNQnBs = true;}
      if(ftHEUAzLRh == cPqjBHsbYZ){gdnJprNZDj = true;}
      if(PPRRIIQAIC == BSOMdUrhax){hVifXWifzd = true;}
      while(qQiQBEuXPf == saDxQkhzXo){dEnTMRlFWp = true;}
      while(cPqjBHsbYZ == cPqjBHsbYZ){jkyiyWueyJ = true;}
      while(BSOMdUrhax == BSOMdUrhax){bSNBqgJidi = true;}
      if(MHUiNodXNs == true){MHUiNodXNs = false;}
      if(elcqdBeYiD == true){elcqdBeYiD = false;}
      if(hdTxIXCWlf == true){hdTxIXCWlf = false;}
      if(LMxSSVtIVL == true){LMxSSVtIVL = false;}
      if(cUNfuPpXhc == true){cUNfuPpXhc = false;}
      if(oTzWOimXZp == true){oTzWOimXZp = false;}
      if(mGkhgRoKXI == true){mGkhgRoKXI = false;}
      if(GVCWZNQnBs == true){GVCWZNQnBs = false;}
      if(gdnJprNZDj == true){gdnJprNZDj = false;}
      if(hVifXWifzd == true){hVifXWifzd = false;}
      if(ZfzZVTQbwB == true){ZfzZVTQbwB = false;}
      if(SzVfIIRbqn == true){SzVfIIRbqn = false;}
      if(DPGnZjmWzD == true){DPGnZjmWzD = false;}
      if(djoXTBeNmW == true){djoXTBeNmW = false;}
      if(alcBRiACXP == true){alcBRiACXP = false;}
      if(EHoKZKYLAk == true){EHoKZKYLAk = false;}
      if(ftcsXhJyMG == true){ftcsXhJyMG = false;}
      if(dEnTMRlFWp == true){dEnTMRlFWp = false;}
      if(jkyiyWueyJ == true){jkyiyWueyJ = false;}
      if(bSNBqgJidi == true){bSNBqgJidi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJXBJHUJEB
{ 
  void lroXxbcZkB()
  { 
      bool aNAGFdOnng = false;
      bool TOVaysTWdf = false;
      bool EOJdVatKCx = false;
      bool QuMUUbYdeU = false;
      bool ZTQINxEuZz = false;
      bool bKiLnMEVke = false;
      bool jEkpQYCAFW = false;
      bool ToqJFjxAQX = false;
      bool WyjCUFMAgI = false;
      bool XDsAjUiZqo = false;
      bool uDpDfmSZFE = false;
      bool OEFMHlThUK = false;
      bool MBTxzPuqYk = false;
      bool BXIabSIgWh = false;
      bool mltbsSyfry = false;
      bool BAEfbtjrEP = false;
      bool qbAUCqudjo = false;
      bool dlLlXZHqDf = false;
      bool RPyaiBSbzh = false;
      bool iPcHqLlYZC = false;
      string ZnfpNUZnNX;
      string RDtYEbTLzZ;
      string bpUZekwHlr;
      string ttnItQowfp;
      string YuJGnqVhAf;
      string bLHYnjSGLc;
      string YRCVdXOldm;
      string mWeJAffOkm;
      string ONHGPhlOUK;
      string xikDRGsncP;
      string bjDMsEgyXH;
      string EEUXNKKwFu;
      string kzQToDlaqt;
      string mqlULeJtNK;
      string BnpMFsNMoG;
      string uxigecSjWo;
      string SFGdUMSzMh;
      string BQhtsxIENw;
      string pZkjzoIEph;
      string MZWXrwgMrs;
      if(ZnfpNUZnNX == bjDMsEgyXH){aNAGFdOnng = true;}
      else if(bjDMsEgyXH == ZnfpNUZnNX){uDpDfmSZFE = true;}
      if(RDtYEbTLzZ == EEUXNKKwFu){TOVaysTWdf = true;}
      else if(EEUXNKKwFu == RDtYEbTLzZ){OEFMHlThUK = true;}
      if(bpUZekwHlr == kzQToDlaqt){EOJdVatKCx = true;}
      else if(kzQToDlaqt == bpUZekwHlr){MBTxzPuqYk = true;}
      if(ttnItQowfp == mqlULeJtNK){QuMUUbYdeU = true;}
      else if(mqlULeJtNK == ttnItQowfp){BXIabSIgWh = true;}
      if(YuJGnqVhAf == BnpMFsNMoG){ZTQINxEuZz = true;}
      else if(BnpMFsNMoG == YuJGnqVhAf){mltbsSyfry = true;}
      if(bLHYnjSGLc == uxigecSjWo){bKiLnMEVke = true;}
      else if(uxigecSjWo == bLHYnjSGLc){BAEfbtjrEP = true;}
      if(YRCVdXOldm == SFGdUMSzMh){jEkpQYCAFW = true;}
      else if(SFGdUMSzMh == YRCVdXOldm){qbAUCqudjo = true;}
      if(mWeJAffOkm == BQhtsxIENw){ToqJFjxAQX = true;}
      if(ONHGPhlOUK == pZkjzoIEph){WyjCUFMAgI = true;}
      if(xikDRGsncP == MZWXrwgMrs){XDsAjUiZqo = true;}
      while(BQhtsxIENw == mWeJAffOkm){dlLlXZHqDf = true;}
      while(pZkjzoIEph == pZkjzoIEph){RPyaiBSbzh = true;}
      while(MZWXrwgMrs == MZWXrwgMrs){iPcHqLlYZC = true;}
      if(aNAGFdOnng == true){aNAGFdOnng = false;}
      if(TOVaysTWdf == true){TOVaysTWdf = false;}
      if(EOJdVatKCx == true){EOJdVatKCx = false;}
      if(QuMUUbYdeU == true){QuMUUbYdeU = false;}
      if(ZTQINxEuZz == true){ZTQINxEuZz = false;}
      if(bKiLnMEVke == true){bKiLnMEVke = false;}
      if(jEkpQYCAFW == true){jEkpQYCAFW = false;}
      if(ToqJFjxAQX == true){ToqJFjxAQX = false;}
      if(WyjCUFMAgI == true){WyjCUFMAgI = false;}
      if(XDsAjUiZqo == true){XDsAjUiZqo = false;}
      if(uDpDfmSZFE == true){uDpDfmSZFE = false;}
      if(OEFMHlThUK == true){OEFMHlThUK = false;}
      if(MBTxzPuqYk == true){MBTxzPuqYk = false;}
      if(BXIabSIgWh == true){BXIabSIgWh = false;}
      if(mltbsSyfry == true){mltbsSyfry = false;}
      if(BAEfbtjrEP == true){BAEfbtjrEP = false;}
      if(qbAUCqudjo == true){qbAUCqudjo = false;}
      if(dlLlXZHqDf == true){dlLlXZHqDf = false;}
      if(RPyaiBSbzh == true){RPyaiBSbzh = false;}
      if(iPcHqLlYZC == true){iPcHqLlYZC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IUERONERUI
{ 
  void gPdwVedOlB()
  { 
      bool gLJdeuESZz = false;
      bool bdeNoOVDtG = false;
      bool RZoflkBDaS = false;
      bool HGsrnXdxGs = false;
      bool qyxADOiqXg = false;
      bool EayfmHVdqt = false;
      bool sArHrVkmZQ = false;
      bool kXwAPTbnbW = false;
      bool CKftNgINEf = false;
      bool CzFMApGoIh = false;
      bool duQGufdxPT = false;
      bool ehCUrhUytK = false;
      bool NXhsOkSjAZ = false;
      bool NmetrGsZyg = false;
      bool CKxkATxjTR = false;
      bool VIuxTGNXqJ = false;
      bool MtxpGrCHbk = false;
      bool ouzMICZxsu = false;
      bool nhPhDEqgZl = false;
      bool rVhnTINHdH = false;
      string RnFSDAmRIe;
      string DmsIysViPw;
      string OJaAnmxWRa;
      string LWLRnfgUHa;
      string KYrBXdGlBV;
      string OIwKJHMEdP;
      string DPzhSfbbTS;
      string MAbokpRYcK;
      string gKVwMDaAHf;
      string SbpqXuYKhq;
      string CdRiJNfGYS;
      string pnaThrsDUP;
      string FaTnzjKjRp;
      string QGplHDrmly;
      string WTbnoeAVIe;
      string BVoSkbJdiY;
      string DwoiCjxoLe;
      string zGQWrlzeyU;
      string inalnuRXAf;
      string sOENuZdrlF;
      if(RnFSDAmRIe == CdRiJNfGYS){gLJdeuESZz = true;}
      else if(CdRiJNfGYS == RnFSDAmRIe){duQGufdxPT = true;}
      if(DmsIysViPw == pnaThrsDUP){bdeNoOVDtG = true;}
      else if(pnaThrsDUP == DmsIysViPw){ehCUrhUytK = true;}
      if(OJaAnmxWRa == FaTnzjKjRp){RZoflkBDaS = true;}
      else if(FaTnzjKjRp == OJaAnmxWRa){NXhsOkSjAZ = true;}
      if(LWLRnfgUHa == QGplHDrmly){HGsrnXdxGs = true;}
      else if(QGplHDrmly == LWLRnfgUHa){NmetrGsZyg = true;}
      if(KYrBXdGlBV == WTbnoeAVIe){qyxADOiqXg = true;}
      else if(WTbnoeAVIe == KYrBXdGlBV){CKxkATxjTR = true;}
      if(OIwKJHMEdP == BVoSkbJdiY){EayfmHVdqt = true;}
      else if(BVoSkbJdiY == OIwKJHMEdP){VIuxTGNXqJ = true;}
      if(DPzhSfbbTS == DwoiCjxoLe){sArHrVkmZQ = true;}
      else if(DwoiCjxoLe == DPzhSfbbTS){MtxpGrCHbk = true;}
      if(MAbokpRYcK == zGQWrlzeyU){kXwAPTbnbW = true;}
      if(gKVwMDaAHf == inalnuRXAf){CKftNgINEf = true;}
      if(SbpqXuYKhq == sOENuZdrlF){CzFMApGoIh = true;}
      while(zGQWrlzeyU == MAbokpRYcK){ouzMICZxsu = true;}
      while(inalnuRXAf == inalnuRXAf){nhPhDEqgZl = true;}
      while(sOENuZdrlF == sOENuZdrlF){rVhnTINHdH = true;}
      if(gLJdeuESZz == true){gLJdeuESZz = false;}
      if(bdeNoOVDtG == true){bdeNoOVDtG = false;}
      if(RZoflkBDaS == true){RZoflkBDaS = false;}
      if(HGsrnXdxGs == true){HGsrnXdxGs = false;}
      if(qyxADOiqXg == true){qyxADOiqXg = false;}
      if(EayfmHVdqt == true){EayfmHVdqt = false;}
      if(sArHrVkmZQ == true){sArHrVkmZQ = false;}
      if(kXwAPTbnbW == true){kXwAPTbnbW = false;}
      if(CKftNgINEf == true){CKftNgINEf = false;}
      if(CzFMApGoIh == true){CzFMApGoIh = false;}
      if(duQGufdxPT == true){duQGufdxPT = false;}
      if(ehCUrhUytK == true){ehCUrhUytK = false;}
      if(NXhsOkSjAZ == true){NXhsOkSjAZ = false;}
      if(NmetrGsZyg == true){NmetrGsZyg = false;}
      if(CKxkATxjTR == true){CKxkATxjTR = false;}
      if(VIuxTGNXqJ == true){VIuxTGNXqJ = false;}
      if(MtxpGrCHbk == true){MtxpGrCHbk = false;}
      if(ouzMICZxsu == true){ouzMICZxsu = false;}
      if(nhPhDEqgZl == true){nhPhDEqgZl = false;}
      if(rVhnTINHdH == true){rVhnTINHdH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZPAGGQRMEZ
{ 
  void MkcSjNFsJE()
  { 
      bool umfpODEipH = false;
      bool bBGViltGlo = false;
      bool JbzNtiQTtS = false;
      bool AKCYtXwgWx = false;
      bool XAPQeszlzF = false;
      bool jgmPzTnSuf = false;
      bool lkoWGQygaK = false;
      bool pMinQJMihA = false;
      bool idTnhTWmYa = false;
      bool jdlpKlKrJN = false;
      bool tSKoPXxyyp = false;
      bool GFjuxIRAnl = false;
      bool sLHAaMardd = false;
      bool yTYUFQTdYK = false;
      bool WYohTesqsC = false;
      bool TJDXTiKJOC = false;
      bool xEUTrmfPog = false;
      bool nnbdOUWYgu = false;
      bool SizbKnQBAV = false;
      bool FJPVNSDUpg = false;
      string sTIiRplIzZ;
      string NSBJYyYnXI;
      string jZSiPfjwiH;
      string OdqzUDaHLs;
      string KMGrzkoOzn;
      string JxNOZSAZSk;
      string FoZqKjaCnU;
      string XRceyWTZid;
      string qVxtyQPcYC;
      string CBnZnUmOgP;
      string KladQqUiQC;
      string zZpntjrfst;
      string TxdlSVcCpc;
      string jFsSTEuTcG;
      string wfMWDcKAfE;
      string bHVmuMIoLt;
      string ORsmRsgWTo;
      string oYClxnkHho;
      string LbWlAcjFXG;
      string uFHiremZEJ;
      if(sTIiRplIzZ == KladQqUiQC){umfpODEipH = true;}
      else if(KladQqUiQC == sTIiRplIzZ){tSKoPXxyyp = true;}
      if(NSBJYyYnXI == zZpntjrfst){bBGViltGlo = true;}
      else if(zZpntjrfst == NSBJYyYnXI){GFjuxIRAnl = true;}
      if(jZSiPfjwiH == TxdlSVcCpc){JbzNtiQTtS = true;}
      else if(TxdlSVcCpc == jZSiPfjwiH){sLHAaMardd = true;}
      if(OdqzUDaHLs == jFsSTEuTcG){AKCYtXwgWx = true;}
      else if(jFsSTEuTcG == OdqzUDaHLs){yTYUFQTdYK = true;}
      if(KMGrzkoOzn == wfMWDcKAfE){XAPQeszlzF = true;}
      else if(wfMWDcKAfE == KMGrzkoOzn){WYohTesqsC = true;}
      if(JxNOZSAZSk == bHVmuMIoLt){jgmPzTnSuf = true;}
      else if(bHVmuMIoLt == JxNOZSAZSk){TJDXTiKJOC = true;}
      if(FoZqKjaCnU == ORsmRsgWTo){lkoWGQygaK = true;}
      else if(ORsmRsgWTo == FoZqKjaCnU){xEUTrmfPog = true;}
      if(XRceyWTZid == oYClxnkHho){pMinQJMihA = true;}
      if(qVxtyQPcYC == LbWlAcjFXG){idTnhTWmYa = true;}
      if(CBnZnUmOgP == uFHiremZEJ){jdlpKlKrJN = true;}
      while(oYClxnkHho == XRceyWTZid){nnbdOUWYgu = true;}
      while(LbWlAcjFXG == LbWlAcjFXG){SizbKnQBAV = true;}
      while(uFHiremZEJ == uFHiremZEJ){FJPVNSDUpg = true;}
      if(umfpODEipH == true){umfpODEipH = false;}
      if(bBGViltGlo == true){bBGViltGlo = false;}
      if(JbzNtiQTtS == true){JbzNtiQTtS = false;}
      if(AKCYtXwgWx == true){AKCYtXwgWx = false;}
      if(XAPQeszlzF == true){XAPQeszlzF = false;}
      if(jgmPzTnSuf == true){jgmPzTnSuf = false;}
      if(lkoWGQygaK == true){lkoWGQygaK = false;}
      if(pMinQJMihA == true){pMinQJMihA = false;}
      if(idTnhTWmYa == true){idTnhTWmYa = false;}
      if(jdlpKlKrJN == true){jdlpKlKrJN = false;}
      if(tSKoPXxyyp == true){tSKoPXxyyp = false;}
      if(GFjuxIRAnl == true){GFjuxIRAnl = false;}
      if(sLHAaMardd == true){sLHAaMardd = false;}
      if(yTYUFQTdYK == true){yTYUFQTdYK = false;}
      if(WYohTesqsC == true){WYohTesqsC = false;}
      if(TJDXTiKJOC == true){TJDXTiKJOC = false;}
      if(xEUTrmfPog == true){xEUTrmfPog = false;}
      if(nnbdOUWYgu == true){nnbdOUWYgu = false;}
      if(SizbKnQBAV == true){SizbKnQBAV = false;}
      if(FJPVNSDUpg == true){FJPVNSDUpg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VOTDSGALQT
{ 
  void pifWtyXnBN()
  { 
      bool rUTHzRVifS = false;
      bool IUheufeYtJ = false;
      bool leycoIyeXd = false;
      bool MsRYLYQGbq = false;
      bool NogFPVUDKw = false;
      bool EJFqHNVqSp = false;
      bool TpLBGODISW = false;
      bool PXwDuxxsMS = false;
      bool ntUaZCnZQy = false;
      bool CYmkXXcfzB = false;
      bool SLkmffNBuK = false;
      bool PcdACYVkaD = false;
      bool acqTUpjLfX = false;
      bool TRtLAbJgts = false;
      bool oleGiYumhy = false;
      bool CqEuZoTQSp = false;
      bool uBVWpyiSAa = false;
      bool OnqhOnykku = false;
      bool uxdgVbMykL = false;
      bool HsNExmQHPk = false;
      string nsCiTAdhCu;
      string KlrfCXAsgq;
      string WfAQhbEofp;
      string bObyhclxqV;
      string mpqGmIuYyK;
      string YAwORIslAq;
      string uoCLTuKtyY;
      string kCCLEfntcY;
      string ffqUQaSNfY;
      string jAwzZxnelq;
      string yBaYZWxjKk;
      string TzIbKPygur;
      string cwNYokFDkG;
      string qIHlZeERut;
      string dhDuFjqUnK;
      string yHjtNCmBio;
      string QtzDtKrWBf;
      string KglAOusSTE;
      string sjOaIjYMXX;
      string qChGcjhzBt;
      if(nsCiTAdhCu == yBaYZWxjKk){rUTHzRVifS = true;}
      else if(yBaYZWxjKk == nsCiTAdhCu){SLkmffNBuK = true;}
      if(KlrfCXAsgq == TzIbKPygur){IUheufeYtJ = true;}
      else if(TzIbKPygur == KlrfCXAsgq){PcdACYVkaD = true;}
      if(WfAQhbEofp == cwNYokFDkG){leycoIyeXd = true;}
      else if(cwNYokFDkG == WfAQhbEofp){acqTUpjLfX = true;}
      if(bObyhclxqV == qIHlZeERut){MsRYLYQGbq = true;}
      else if(qIHlZeERut == bObyhclxqV){TRtLAbJgts = true;}
      if(mpqGmIuYyK == dhDuFjqUnK){NogFPVUDKw = true;}
      else if(dhDuFjqUnK == mpqGmIuYyK){oleGiYumhy = true;}
      if(YAwORIslAq == yHjtNCmBio){EJFqHNVqSp = true;}
      else if(yHjtNCmBio == YAwORIslAq){CqEuZoTQSp = true;}
      if(uoCLTuKtyY == QtzDtKrWBf){TpLBGODISW = true;}
      else if(QtzDtKrWBf == uoCLTuKtyY){uBVWpyiSAa = true;}
      if(kCCLEfntcY == KglAOusSTE){PXwDuxxsMS = true;}
      if(ffqUQaSNfY == sjOaIjYMXX){ntUaZCnZQy = true;}
      if(jAwzZxnelq == qChGcjhzBt){CYmkXXcfzB = true;}
      while(KglAOusSTE == kCCLEfntcY){OnqhOnykku = true;}
      while(sjOaIjYMXX == sjOaIjYMXX){uxdgVbMykL = true;}
      while(qChGcjhzBt == qChGcjhzBt){HsNExmQHPk = true;}
      if(rUTHzRVifS == true){rUTHzRVifS = false;}
      if(IUheufeYtJ == true){IUheufeYtJ = false;}
      if(leycoIyeXd == true){leycoIyeXd = false;}
      if(MsRYLYQGbq == true){MsRYLYQGbq = false;}
      if(NogFPVUDKw == true){NogFPVUDKw = false;}
      if(EJFqHNVqSp == true){EJFqHNVqSp = false;}
      if(TpLBGODISW == true){TpLBGODISW = false;}
      if(PXwDuxxsMS == true){PXwDuxxsMS = false;}
      if(ntUaZCnZQy == true){ntUaZCnZQy = false;}
      if(CYmkXXcfzB == true){CYmkXXcfzB = false;}
      if(SLkmffNBuK == true){SLkmffNBuK = false;}
      if(PcdACYVkaD == true){PcdACYVkaD = false;}
      if(acqTUpjLfX == true){acqTUpjLfX = false;}
      if(TRtLAbJgts == true){TRtLAbJgts = false;}
      if(oleGiYumhy == true){oleGiYumhy = false;}
      if(CqEuZoTQSp == true){CqEuZoTQSp = false;}
      if(uBVWpyiSAa == true){uBVWpyiSAa = false;}
      if(OnqhOnykku == true){OnqhOnykku = false;}
      if(uxdgVbMykL == true){uxdgVbMykL = false;}
      if(HsNExmQHPk == true){HsNExmQHPk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FURVUFKWGD
{ 
  void QoYTrkiscn()
  { 
      bool HwdTsaRWnY = false;
      bool JTwDEoXCoG = false;
      bool JdDuCCmGyC = false;
      bool HVUDsIAryK = false;
      bool dVdXWDVhZR = false;
      bool QjygzcshQq = false;
      bool mKXkQmysKu = false;
      bool ofEebnAeYy = false;
      bool gFfgkXXmDQ = false;
      bool PRaHXSyrHi = false;
      bool EbXdckfSFL = false;
      bool bNJSJhepzs = false;
      bool PKosfWExHI = false;
      bool oHXosEgBDz = false;
      bool qEhrnBIIxo = false;
      bool nHsNStmdyG = false;
      bool giLxVUpTYF = false;
      bool AcmABLcxFd = false;
      bool NuzRThOJVz = false;
      bool RDDxSIsjVT = false;
      string CRyqkLRNFH;
      string OhHwoNIjpX;
      string iybTbnCGju;
      string ZEjSmntsOV;
      string YGTfGnOrJg;
      string RKVKcDpeOx;
      string ILcKgKxnJB;
      string SOVTybewMn;
      string YKxCdOhZpj;
      string xPeQNNcJyw;
      string pZhHNCoBLA;
      string XtRZXyOZgR;
      string bXyYDDiEGk;
      string yVxQyzbooa;
      string ZgOoLDxFrO;
      string zCcfTSbJDK;
      string TjtaBCwAaY;
      string VYkFruJIMA;
      string FdLqkurRxf;
      string WSkeHommmJ;
      if(CRyqkLRNFH == pZhHNCoBLA){HwdTsaRWnY = true;}
      else if(pZhHNCoBLA == CRyqkLRNFH){EbXdckfSFL = true;}
      if(OhHwoNIjpX == XtRZXyOZgR){JTwDEoXCoG = true;}
      else if(XtRZXyOZgR == OhHwoNIjpX){bNJSJhepzs = true;}
      if(iybTbnCGju == bXyYDDiEGk){JdDuCCmGyC = true;}
      else if(bXyYDDiEGk == iybTbnCGju){PKosfWExHI = true;}
      if(ZEjSmntsOV == yVxQyzbooa){HVUDsIAryK = true;}
      else if(yVxQyzbooa == ZEjSmntsOV){oHXosEgBDz = true;}
      if(YGTfGnOrJg == ZgOoLDxFrO){dVdXWDVhZR = true;}
      else if(ZgOoLDxFrO == YGTfGnOrJg){qEhrnBIIxo = true;}
      if(RKVKcDpeOx == zCcfTSbJDK){QjygzcshQq = true;}
      else if(zCcfTSbJDK == RKVKcDpeOx){nHsNStmdyG = true;}
      if(ILcKgKxnJB == TjtaBCwAaY){mKXkQmysKu = true;}
      else if(TjtaBCwAaY == ILcKgKxnJB){giLxVUpTYF = true;}
      if(SOVTybewMn == VYkFruJIMA){ofEebnAeYy = true;}
      if(YKxCdOhZpj == FdLqkurRxf){gFfgkXXmDQ = true;}
      if(xPeQNNcJyw == WSkeHommmJ){PRaHXSyrHi = true;}
      while(VYkFruJIMA == SOVTybewMn){AcmABLcxFd = true;}
      while(FdLqkurRxf == FdLqkurRxf){NuzRThOJVz = true;}
      while(WSkeHommmJ == WSkeHommmJ){RDDxSIsjVT = true;}
      if(HwdTsaRWnY == true){HwdTsaRWnY = false;}
      if(JTwDEoXCoG == true){JTwDEoXCoG = false;}
      if(JdDuCCmGyC == true){JdDuCCmGyC = false;}
      if(HVUDsIAryK == true){HVUDsIAryK = false;}
      if(dVdXWDVhZR == true){dVdXWDVhZR = false;}
      if(QjygzcshQq == true){QjygzcshQq = false;}
      if(mKXkQmysKu == true){mKXkQmysKu = false;}
      if(ofEebnAeYy == true){ofEebnAeYy = false;}
      if(gFfgkXXmDQ == true){gFfgkXXmDQ = false;}
      if(PRaHXSyrHi == true){PRaHXSyrHi = false;}
      if(EbXdckfSFL == true){EbXdckfSFL = false;}
      if(bNJSJhepzs == true){bNJSJhepzs = false;}
      if(PKosfWExHI == true){PKosfWExHI = false;}
      if(oHXosEgBDz == true){oHXosEgBDz = false;}
      if(qEhrnBIIxo == true){qEhrnBIIxo = false;}
      if(nHsNStmdyG == true){nHsNStmdyG = false;}
      if(giLxVUpTYF == true){giLxVUpTYF = false;}
      if(AcmABLcxFd == true){AcmABLcxFd = false;}
      if(NuzRThOJVz == true){NuzRThOJVz = false;}
      if(RDDxSIsjVT == true){RDDxSIsjVT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CQOLBCRLUM
{ 
  void yIURJFHTJU()
  { 
      bool YzcBJEGRuh = false;
      bool nTMaMXWksj = false;
      bool mIgPYIMozf = false;
      bool tZCyhzdRsQ = false;
      bool ZxwfckoEaa = false;
      bool snROsQSNcA = false;
      bool rQSPmNQOsM = false;
      bool tFrcJoMAlm = false;
      bool TIOYlGInER = false;
      bool gPnrYIefrO = false;
      bool TaKNfnunEE = false;
      bool DRbogjBtcg = false;
      bool FbJbfeQzEA = false;
      bool KgHWSsxArx = false;
      bool KTiAOPmyLn = false;
      bool GkDLJqQihB = false;
      bool XwjDtWJFVn = false;
      bool lBBfVksINQ = false;
      bool qRnPtYcwMa = false;
      bool bOSpZOjfGq = false;
      string QqwtTkVBaR;
      string ddPtSYrcXH;
      string YOajoGglRY;
      string SaJERaUpwc;
      string lwrukIugHL;
      string yVEBJCPLFN;
      string DjiBzCUKbr;
      string DBguUcVfzf;
      string KzdGZwVHuO;
      string KIjhYCMquh;
      string mkFPHwoJgg;
      string gjMZDEFcbD;
      string fMPNguRyVR;
      string QejQrZtNzd;
      string GMaOhZuKeT;
      string wjPrCaUrhL;
      string epmOPBAwgc;
      string KrcxwTlBeH;
      string zGTCUfOqOR;
      string ECemyQYLyf;
      if(QqwtTkVBaR == mkFPHwoJgg){YzcBJEGRuh = true;}
      else if(mkFPHwoJgg == QqwtTkVBaR){TaKNfnunEE = true;}
      if(ddPtSYrcXH == gjMZDEFcbD){nTMaMXWksj = true;}
      else if(gjMZDEFcbD == ddPtSYrcXH){DRbogjBtcg = true;}
      if(YOajoGglRY == fMPNguRyVR){mIgPYIMozf = true;}
      else if(fMPNguRyVR == YOajoGglRY){FbJbfeQzEA = true;}
      if(SaJERaUpwc == QejQrZtNzd){tZCyhzdRsQ = true;}
      else if(QejQrZtNzd == SaJERaUpwc){KgHWSsxArx = true;}
      if(lwrukIugHL == GMaOhZuKeT){ZxwfckoEaa = true;}
      else if(GMaOhZuKeT == lwrukIugHL){KTiAOPmyLn = true;}
      if(yVEBJCPLFN == wjPrCaUrhL){snROsQSNcA = true;}
      else if(wjPrCaUrhL == yVEBJCPLFN){GkDLJqQihB = true;}
      if(DjiBzCUKbr == epmOPBAwgc){rQSPmNQOsM = true;}
      else if(epmOPBAwgc == DjiBzCUKbr){XwjDtWJFVn = true;}
      if(DBguUcVfzf == KrcxwTlBeH){tFrcJoMAlm = true;}
      if(KzdGZwVHuO == zGTCUfOqOR){TIOYlGInER = true;}
      if(KIjhYCMquh == ECemyQYLyf){gPnrYIefrO = true;}
      while(KrcxwTlBeH == DBguUcVfzf){lBBfVksINQ = true;}
      while(zGTCUfOqOR == zGTCUfOqOR){qRnPtYcwMa = true;}
      while(ECemyQYLyf == ECemyQYLyf){bOSpZOjfGq = true;}
      if(YzcBJEGRuh == true){YzcBJEGRuh = false;}
      if(nTMaMXWksj == true){nTMaMXWksj = false;}
      if(mIgPYIMozf == true){mIgPYIMozf = false;}
      if(tZCyhzdRsQ == true){tZCyhzdRsQ = false;}
      if(ZxwfckoEaa == true){ZxwfckoEaa = false;}
      if(snROsQSNcA == true){snROsQSNcA = false;}
      if(rQSPmNQOsM == true){rQSPmNQOsM = false;}
      if(tFrcJoMAlm == true){tFrcJoMAlm = false;}
      if(TIOYlGInER == true){TIOYlGInER = false;}
      if(gPnrYIefrO == true){gPnrYIefrO = false;}
      if(TaKNfnunEE == true){TaKNfnunEE = false;}
      if(DRbogjBtcg == true){DRbogjBtcg = false;}
      if(FbJbfeQzEA == true){FbJbfeQzEA = false;}
      if(KgHWSsxArx == true){KgHWSsxArx = false;}
      if(KTiAOPmyLn == true){KTiAOPmyLn = false;}
      if(GkDLJqQihB == true){GkDLJqQihB = false;}
      if(XwjDtWJFVn == true){XwjDtWJFVn = false;}
      if(lBBfVksINQ == true){lBBfVksINQ = false;}
      if(qRnPtYcwMa == true){qRnPtYcwMa = false;}
      if(bOSpZOjfGq == true){bOSpZOjfGq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ACSUQHFAYF
{ 
  void nydTQJoTqs()
  { 
      bool tPjBwpkgxZ = false;
      bool abQSqAmWSe = false;
      bool DZIwlRqBmA = false;
      bool EWDPlbSeEz = false;
      bool DzeNXuutOm = false;
      bool LWWGkUGmPd = false;
      bool yisxUDXBfP = false;
      bool gIRSaEuuXp = false;
      bool WxlznhAxeR = false;
      bool UePaBUFhrU = false;
      bool XsNzFDEDff = false;
      bool YKPYHBwsIm = false;
      bool DaWOtCrqRF = false;
      bool zNCDScimtj = false;
      bool cwRyrJPpTz = false;
      bool XLYFRxWzED = false;
      bool LMlZgLILGd = false;
      bool RJzYJGIXVk = false;
      bool lBXRhmnxlV = false;
      bool GihpYPKrRg = false;
      string UZiuIpmEIB;
      string LihHqybMlb;
      string miIZeKAagM;
      string zcighobeIZ;
      string bNUSYwKWgG;
      string jRKsalQJQy;
      string oMXuCizAYC;
      string VxDLAYNoBh;
      string zdsZchRpGw;
      string XSNKkOpZQp;
      string wKxeklNzsB;
      string XaHhyKTxRT;
      string QJsbdCisak;
      string hnYLlngOoq;
      string TRxEXxLfLZ;
      string usHwYmQUAh;
      string DUXHTjCwuJ;
      string dFIazyLoDg;
      string qDgBoofbmz;
      string XLNGmztokn;
      if(UZiuIpmEIB == wKxeklNzsB){tPjBwpkgxZ = true;}
      else if(wKxeklNzsB == UZiuIpmEIB){XsNzFDEDff = true;}
      if(LihHqybMlb == XaHhyKTxRT){abQSqAmWSe = true;}
      else if(XaHhyKTxRT == LihHqybMlb){YKPYHBwsIm = true;}
      if(miIZeKAagM == QJsbdCisak){DZIwlRqBmA = true;}
      else if(QJsbdCisak == miIZeKAagM){DaWOtCrqRF = true;}
      if(zcighobeIZ == hnYLlngOoq){EWDPlbSeEz = true;}
      else if(hnYLlngOoq == zcighobeIZ){zNCDScimtj = true;}
      if(bNUSYwKWgG == TRxEXxLfLZ){DzeNXuutOm = true;}
      else if(TRxEXxLfLZ == bNUSYwKWgG){cwRyrJPpTz = true;}
      if(jRKsalQJQy == usHwYmQUAh){LWWGkUGmPd = true;}
      else if(usHwYmQUAh == jRKsalQJQy){XLYFRxWzED = true;}
      if(oMXuCizAYC == DUXHTjCwuJ){yisxUDXBfP = true;}
      else if(DUXHTjCwuJ == oMXuCizAYC){LMlZgLILGd = true;}
      if(VxDLAYNoBh == dFIazyLoDg){gIRSaEuuXp = true;}
      if(zdsZchRpGw == qDgBoofbmz){WxlznhAxeR = true;}
      if(XSNKkOpZQp == XLNGmztokn){UePaBUFhrU = true;}
      while(dFIazyLoDg == VxDLAYNoBh){RJzYJGIXVk = true;}
      while(qDgBoofbmz == qDgBoofbmz){lBXRhmnxlV = true;}
      while(XLNGmztokn == XLNGmztokn){GihpYPKrRg = true;}
      if(tPjBwpkgxZ == true){tPjBwpkgxZ = false;}
      if(abQSqAmWSe == true){abQSqAmWSe = false;}
      if(DZIwlRqBmA == true){DZIwlRqBmA = false;}
      if(EWDPlbSeEz == true){EWDPlbSeEz = false;}
      if(DzeNXuutOm == true){DzeNXuutOm = false;}
      if(LWWGkUGmPd == true){LWWGkUGmPd = false;}
      if(yisxUDXBfP == true){yisxUDXBfP = false;}
      if(gIRSaEuuXp == true){gIRSaEuuXp = false;}
      if(WxlznhAxeR == true){WxlznhAxeR = false;}
      if(UePaBUFhrU == true){UePaBUFhrU = false;}
      if(XsNzFDEDff == true){XsNzFDEDff = false;}
      if(YKPYHBwsIm == true){YKPYHBwsIm = false;}
      if(DaWOtCrqRF == true){DaWOtCrqRF = false;}
      if(zNCDScimtj == true){zNCDScimtj = false;}
      if(cwRyrJPpTz == true){cwRyrJPpTz = false;}
      if(XLYFRxWzED == true){XLYFRxWzED = false;}
      if(LMlZgLILGd == true){LMlZgLILGd = false;}
      if(RJzYJGIXVk == true){RJzYJGIXVk = false;}
      if(lBXRhmnxlV == true){lBXRhmnxlV = false;}
      if(GihpYPKrRg == true){GihpYPKrRg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TWRCEOCYZH
{ 
  void TrQNHThpuT()
  { 
      bool GchhIahxaE = false;
      bool EVezmXOeqs = false;
      bool wOXoWHCShC = false;
      bool RWsYXoBYkg = false;
      bool SIMxGaaulH = false;
      bool LhSusqFsKB = false;
      bool YPOXlhcGby = false;
      bool VotKZnCZhw = false;
      bool fGfaqiEyef = false;
      bool iIOjHDsnKY = false;
      bool yUTnlVnHUF = false;
      bool ofLOUSingD = false;
      bool cdawONaKCW = false;
      bool uNOIxKlrnV = false;
      bool uwdZpDwAOn = false;
      bool TEHHuUsWYY = false;
      bool tdEyKaQCQJ = false;
      bool fqzLHfABFL = false;
      bool QauOCpGHMc = false;
      bool RPSPaRqePO = false;
      string yyjILkFoFj;
      string GgcXtyJBAo;
      string yDpiiRUrNp;
      string lNAEFIOHSA;
      string KYaYtItSBJ;
      string cMmKxuIAZt;
      string PNaOxrfYRk;
      string iBhzdZbQna;
      string XBpENZZpGK;
      string zOhYjxxLaC;
      string bVBPZadngX;
      string SqLyWOXWAX;
      string RpRHlUSIPg;
      string bQplyBAZem;
      string ulJirHCiCV;
      string YaKDjlEtdF;
      string HUYzuCBZAU;
      string NxrNcfghOd;
      string RjGsHBFmCL;
      string xGuZeZNJnp;
      if(yyjILkFoFj == bVBPZadngX){GchhIahxaE = true;}
      else if(bVBPZadngX == yyjILkFoFj){yUTnlVnHUF = true;}
      if(GgcXtyJBAo == SqLyWOXWAX){EVezmXOeqs = true;}
      else if(SqLyWOXWAX == GgcXtyJBAo){ofLOUSingD = true;}
      if(yDpiiRUrNp == RpRHlUSIPg){wOXoWHCShC = true;}
      else if(RpRHlUSIPg == yDpiiRUrNp){cdawONaKCW = true;}
      if(lNAEFIOHSA == bQplyBAZem){RWsYXoBYkg = true;}
      else if(bQplyBAZem == lNAEFIOHSA){uNOIxKlrnV = true;}
      if(KYaYtItSBJ == ulJirHCiCV){SIMxGaaulH = true;}
      else if(ulJirHCiCV == KYaYtItSBJ){uwdZpDwAOn = true;}
      if(cMmKxuIAZt == YaKDjlEtdF){LhSusqFsKB = true;}
      else if(YaKDjlEtdF == cMmKxuIAZt){TEHHuUsWYY = true;}
      if(PNaOxrfYRk == HUYzuCBZAU){YPOXlhcGby = true;}
      else if(HUYzuCBZAU == PNaOxrfYRk){tdEyKaQCQJ = true;}
      if(iBhzdZbQna == NxrNcfghOd){VotKZnCZhw = true;}
      if(XBpENZZpGK == RjGsHBFmCL){fGfaqiEyef = true;}
      if(zOhYjxxLaC == xGuZeZNJnp){iIOjHDsnKY = true;}
      while(NxrNcfghOd == iBhzdZbQna){fqzLHfABFL = true;}
      while(RjGsHBFmCL == RjGsHBFmCL){QauOCpGHMc = true;}
      while(xGuZeZNJnp == xGuZeZNJnp){RPSPaRqePO = true;}
      if(GchhIahxaE == true){GchhIahxaE = false;}
      if(EVezmXOeqs == true){EVezmXOeqs = false;}
      if(wOXoWHCShC == true){wOXoWHCShC = false;}
      if(RWsYXoBYkg == true){RWsYXoBYkg = false;}
      if(SIMxGaaulH == true){SIMxGaaulH = false;}
      if(LhSusqFsKB == true){LhSusqFsKB = false;}
      if(YPOXlhcGby == true){YPOXlhcGby = false;}
      if(VotKZnCZhw == true){VotKZnCZhw = false;}
      if(fGfaqiEyef == true){fGfaqiEyef = false;}
      if(iIOjHDsnKY == true){iIOjHDsnKY = false;}
      if(yUTnlVnHUF == true){yUTnlVnHUF = false;}
      if(ofLOUSingD == true){ofLOUSingD = false;}
      if(cdawONaKCW == true){cdawONaKCW = false;}
      if(uNOIxKlrnV == true){uNOIxKlrnV = false;}
      if(uwdZpDwAOn == true){uwdZpDwAOn = false;}
      if(TEHHuUsWYY == true){TEHHuUsWYY = false;}
      if(tdEyKaQCQJ == true){tdEyKaQCQJ = false;}
      if(fqzLHfABFL == true){fqzLHfABFL = false;}
      if(QauOCpGHMc == true){QauOCpGHMc = false;}
      if(RPSPaRqePO == true){RPSPaRqePO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSMYDVASEP
{ 
  void zRtQCilAZa()
  { 
      bool GTRUoDIebG = false;
      bool xdaCkCGlqJ = false;
      bool VOLfmrlRIF = false;
      bool HMuSGhxrWi = false;
      bool pMyiiReUgT = false;
      bool GpXrOrIkgw = false;
      bool RqVWzkiHuD = false;
      bool EOPHTJPcxV = false;
      bool NQjoyQoCEN = false;
      bool YMKZRypbix = false;
      bool iWYdOraPYE = false;
      bool cfnLiAHgXh = false;
      bool wfChdrDopU = false;
      bool SmszlprGZG = false;
      bool oYcAksYypQ = false;
      bool qIDBBCTqAV = false;
      bool nkZDkolnYs = false;
      bool IBHRrWDCwj = false;
      bool TFzZdKjqxj = false;
      bool VBFEREzZOw = false;
      string JuoEYLKHXl;
      string ZFHOyyKwqZ;
      string NUVVlMLCBF;
      string XpMmBgWRWV;
      string QmsHllFtpl;
      string FISnaoZSSM;
      string zHFSNisUNQ;
      string asZVIZaOjz;
      string GQLPAPXYLL;
      string HEyJVIhasC;
      string sjfYKMixeA;
      string NKiSFiuoRy;
      string LUIBJWtPzA;
      string rAVgFWjlFn;
      string fasLywUeDm;
      string MrItqYadPm;
      string RSxeINoBNi;
      string yIjdSjaxDN;
      string BPMLmzqaog;
      string uFWSVMcOCj;
      if(JuoEYLKHXl == sjfYKMixeA){GTRUoDIebG = true;}
      else if(sjfYKMixeA == JuoEYLKHXl){iWYdOraPYE = true;}
      if(ZFHOyyKwqZ == NKiSFiuoRy){xdaCkCGlqJ = true;}
      else if(NKiSFiuoRy == ZFHOyyKwqZ){cfnLiAHgXh = true;}
      if(NUVVlMLCBF == LUIBJWtPzA){VOLfmrlRIF = true;}
      else if(LUIBJWtPzA == NUVVlMLCBF){wfChdrDopU = true;}
      if(XpMmBgWRWV == rAVgFWjlFn){HMuSGhxrWi = true;}
      else if(rAVgFWjlFn == XpMmBgWRWV){SmszlprGZG = true;}
      if(QmsHllFtpl == fasLywUeDm){pMyiiReUgT = true;}
      else if(fasLywUeDm == QmsHllFtpl){oYcAksYypQ = true;}
      if(FISnaoZSSM == MrItqYadPm){GpXrOrIkgw = true;}
      else if(MrItqYadPm == FISnaoZSSM){qIDBBCTqAV = true;}
      if(zHFSNisUNQ == RSxeINoBNi){RqVWzkiHuD = true;}
      else if(RSxeINoBNi == zHFSNisUNQ){nkZDkolnYs = true;}
      if(asZVIZaOjz == yIjdSjaxDN){EOPHTJPcxV = true;}
      if(GQLPAPXYLL == BPMLmzqaog){NQjoyQoCEN = true;}
      if(HEyJVIhasC == uFWSVMcOCj){YMKZRypbix = true;}
      while(yIjdSjaxDN == asZVIZaOjz){IBHRrWDCwj = true;}
      while(BPMLmzqaog == BPMLmzqaog){TFzZdKjqxj = true;}
      while(uFWSVMcOCj == uFWSVMcOCj){VBFEREzZOw = true;}
      if(GTRUoDIebG == true){GTRUoDIebG = false;}
      if(xdaCkCGlqJ == true){xdaCkCGlqJ = false;}
      if(VOLfmrlRIF == true){VOLfmrlRIF = false;}
      if(HMuSGhxrWi == true){HMuSGhxrWi = false;}
      if(pMyiiReUgT == true){pMyiiReUgT = false;}
      if(GpXrOrIkgw == true){GpXrOrIkgw = false;}
      if(RqVWzkiHuD == true){RqVWzkiHuD = false;}
      if(EOPHTJPcxV == true){EOPHTJPcxV = false;}
      if(NQjoyQoCEN == true){NQjoyQoCEN = false;}
      if(YMKZRypbix == true){YMKZRypbix = false;}
      if(iWYdOraPYE == true){iWYdOraPYE = false;}
      if(cfnLiAHgXh == true){cfnLiAHgXh = false;}
      if(wfChdrDopU == true){wfChdrDopU = false;}
      if(SmszlprGZG == true){SmszlprGZG = false;}
      if(oYcAksYypQ == true){oYcAksYypQ = false;}
      if(qIDBBCTqAV == true){qIDBBCTqAV = false;}
      if(nkZDkolnYs == true){nkZDkolnYs = false;}
      if(IBHRrWDCwj == true){IBHRrWDCwj = false;}
      if(TFzZdKjqxj == true){TFzZdKjqxj = false;}
      if(VBFEREzZOw == true){VBFEREzZOw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZLTEFYGTMM
{ 
  void GVVGoLhVbx()
  { 
      bool KGVkmtMGRN = false;
      bool RVABOdkqYF = false;
      bool WUpYaRJKWo = false;
      bool QFILNYoLYM = false;
      bool izLZBIxDAK = false;
      bool WgEpppPxJV = false;
      bool jCibwMMonp = false;
      bool oZSMWWIQWR = false;
      bool TGKMSjASUW = false;
      bool IqBCbgPjco = false;
      bool uIPKUwNrSS = false;
      bool hyarCdqWJM = false;
      bool MtTQgyXPjp = false;
      bool HYngVKqAqV = false;
      bool VHzBnJQJAy = false;
      bool osZPcBnycW = false;
      bool YyIcLIKsVq = false;
      bool mqenqEtSbW = false;
      bool hNPlAOyXEU = false;
      bool WrWUwXyWoe = false;
      string yfdVcqEFoR;
      string fHLTPMxWow;
      string iTuuyowZBH;
      string RSMbRioxkj;
      string fboBhlKmnh;
      string OGXKsdjiXm;
      string udDhzMtjBg;
      string WzkEQHetML;
      string dIkTrLuCin;
      string zGZyoBXHCV;
      string ralHKOUStk;
      string zpVLIlrjom;
      string RqBMhQYlPO;
      string jWrqTDWdJd;
      string pbIxoJkOoD;
      string ImRODAYYZt;
      string ohDeBbydrE;
      string POZLxoiDXX;
      string eKwLGwFcnS;
      string dyEPnHYduM;
      if(yfdVcqEFoR == ralHKOUStk){KGVkmtMGRN = true;}
      else if(ralHKOUStk == yfdVcqEFoR){uIPKUwNrSS = true;}
      if(fHLTPMxWow == zpVLIlrjom){RVABOdkqYF = true;}
      else if(zpVLIlrjom == fHLTPMxWow){hyarCdqWJM = true;}
      if(iTuuyowZBH == RqBMhQYlPO){WUpYaRJKWo = true;}
      else if(RqBMhQYlPO == iTuuyowZBH){MtTQgyXPjp = true;}
      if(RSMbRioxkj == jWrqTDWdJd){QFILNYoLYM = true;}
      else if(jWrqTDWdJd == RSMbRioxkj){HYngVKqAqV = true;}
      if(fboBhlKmnh == pbIxoJkOoD){izLZBIxDAK = true;}
      else if(pbIxoJkOoD == fboBhlKmnh){VHzBnJQJAy = true;}
      if(OGXKsdjiXm == ImRODAYYZt){WgEpppPxJV = true;}
      else if(ImRODAYYZt == OGXKsdjiXm){osZPcBnycW = true;}
      if(udDhzMtjBg == ohDeBbydrE){jCibwMMonp = true;}
      else if(ohDeBbydrE == udDhzMtjBg){YyIcLIKsVq = true;}
      if(WzkEQHetML == POZLxoiDXX){oZSMWWIQWR = true;}
      if(dIkTrLuCin == eKwLGwFcnS){TGKMSjASUW = true;}
      if(zGZyoBXHCV == dyEPnHYduM){IqBCbgPjco = true;}
      while(POZLxoiDXX == WzkEQHetML){mqenqEtSbW = true;}
      while(eKwLGwFcnS == eKwLGwFcnS){hNPlAOyXEU = true;}
      while(dyEPnHYduM == dyEPnHYduM){WrWUwXyWoe = true;}
      if(KGVkmtMGRN == true){KGVkmtMGRN = false;}
      if(RVABOdkqYF == true){RVABOdkqYF = false;}
      if(WUpYaRJKWo == true){WUpYaRJKWo = false;}
      if(QFILNYoLYM == true){QFILNYoLYM = false;}
      if(izLZBIxDAK == true){izLZBIxDAK = false;}
      if(WgEpppPxJV == true){WgEpppPxJV = false;}
      if(jCibwMMonp == true){jCibwMMonp = false;}
      if(oZSMWWIQWR == true){oZSMWWIQWR = false;}
      if(TGKMSjASUW == true){TGKMSjASUW = false;}
      if(IqBCbgPjco == true){IqBCbgPjco = false;}
      if(uIPKUwNrSS == true){uIPKUwNrSS = false;}
      if(hyarCdqWJM == true){hyarCdqWJM = false;}
      if(MtTQgyXPjp == true){MtTQgyXPjp = false;}
      if(HYngVKqAqV == true){HYngVKqAqV = false;}
      if(VHzBnJQJAy == true){VHzBnJQJAy = false;}
      if(osZPcBnycW == true){osZPcBnycW = false;}
      if(YyIcLIKsVq == true){YyIcLIKsVq = false;}
      if(mqenqEtSbW == true){mqenqEtSbW = false;}
      if(hNPlAOyXEU == true){hNPlAOyXEU = false;}
      if(WrWUwXyWoe == true){WrWUwXyWoe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PXVIQLDCBV
{ 
  void xZwAXZjBMQ()
  { 
      bool hkxDRWKAjo = false;
      bool LmmpAfAuUr = false;
      bool rWaIkuPPxS = false;
      bool DWUPWkzkWL = false;
      bool kOxxnqlFwF = false;
      bool pROoeKJnSW = false;
      bool HuDQknRWTO = false;
      bool fPXJHdYcUt = false;
      bool IJSrckIfkL = false;
      bool aKSAEpLfLz = false;
      bool YPlhYZtEhB = false;
      bool kgSYOxbLnA = false;
      bool fllHmVxXER = false;
      bool RrQVUsWkSC = false;
      bool qDyiZtqtkG = false;
      bool NArLSlcdtC = false;
      bool cVzPisPxDU = false;
      bool ZqrlIcnDhs = false;
      bool dDlyDRAFCi = false;
      bool PsqPZUDhzg = false;
      string XFnhVJIdlA;
      string ohSSUEGaKY;
      string bqNQjDrahz;
      string gMhNQKcaTY;
      string UCPCAKTxwT;
      string IEzZhfqXyR;
      string QgwlScAECK;
      string aeHkEZaKQZ;
      string iudNqcMHej;
      string SFcBImGdjW;
      string JPtlrdwNUI;
      string EfGXiVDhup;
      string QrZSqVBGcR;
      string TxasPTAqUM;
      string fzlWemyFRm;
      string iXhsGQpauW;
      string bokDnHENHO;
      string ULMhJRFCnE;
      string WwnohwOhmz;
      string dZwxkqNihX;
      if(XFnhVJIdlA == JPtlrdwNUI){hkxDRWKAjo = true;}
      else if(JPtlrdwNUI == XFnhVJIdlA){YPlhYZtEhB = true;}
      if(ohSSUEGaKY == EfGXiVDhup){LmmpAfAuUr = true;}
      else if(EfGXiVDhup == ohSSUEGaKY){kgSYOxbLnA = true;}
      if(bqNQjDrahz == QrZSqVBGcR){rWaIkuPPxS = true;}
      else if(QrZSqVBGcR == bqNQjDrahz){fllHmVxXER = true;}
      if(gMhNQKcaTY == TxasPTAqUM){DWUPWkzkWL = true;}
      else if(TxasPTAqUM == gMhNQKcaTY){RrQVUsWkSC = true;}
      if(UCPCAKTxwT == fzlWemyFRm){kOxxnqlFwF = true;}
      else if(fzlWemyFRm == UCPCAKTxwT){qDyiZtqtkG = true;}
      if(IEzZhfqXyR == iXhsGQpauW){pROoeKJnSW = true;}
      else if(iXhsGQpauW == IEzZhfqXyR){NArLSlcdtC = true;}
      if(QgwlScAECK == bokDnHENHO){HuDQknRWTO = true;}
      else if(bokDnHENHO == QgwlScAECK){cVzPisPxDU = true;}
      if(aeHkEZaKQZ == ULMhJRFCnE){fPXJHdYcUt = true;}
      if(iudNqcMHej == WwnohwOhmz){IJSrckIfkL = true;}
      if(SFcBImGdjW == dZwxkqNihX){aKSAEpLfLz = true;}
      while(ULMhJRFCnE == aeHkEZaKQZ){ZqrlIcnDhs = true;}
      while(WwnohwOhmz == WwnohwOhmz){dDlyDRAFCi = true;}
      while(dZwxkqNihX == dZwxkqNihX){PsqPZUDhzg = true;}
      if(hkxDRWKAjo == true){hkxDRWKAjo = false;}
      if(LmmpAfAuUr == true){LmmpAfAuUr = false;}
      if(rWaIkuPPxS == true){rWaIkuPPxS = false;}
      if(DWUPWkzkWL == true){DWUPWkzkWL = false;}
      if(kOxxnqlFwF == true){kOxxnqlFwF = false;}
      if(pROoeKJnSW == true){pROoeKJnSW = false;}
      if(HuDQknRWTO == true){HuDQknRWTO = false;}
      if(fPXJHdYcUt == true){fPXJHdYcUt = false;}
      if(IJSrckIfkL == true){IJSrckIfkL = false;}
      if(aKSAEpLfLz == true){aKSAEpLfLz = false;}
      if(YPlhYZtEhB == true){YPlhYZtEhB = false;}
      if(kgSYOxbLnA == true){kgSYOxbLnA = false;}
      if(fllHmVxXER == true){fllHmVxXER = false;}
      if(RrQVUsWkSC == true){RrQVUsWkSC = false;}
      if(qDyiZtqtkG == true){qDyiZtqtkG = false;}
      if(NArLSlcdtC == true){NArLSlcdtC = false;}
      if(cVzPisPxDU == true){cVzPisPxDU = false;}
      if(ZqrlIcnDhs == true){ZqrlIcnDhs = false;}
      if(dDlyDRAFCi == true){dDlyDRAFCi = false;}
      if(PsqPZUDhzg == true){PsqPZUDhzg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NEDNXTLJJH
{ 
  void HGAxyhoTSq()
  { 
      bool jwyaYMNVdA = false;
      bool BzXOIpioGc = false;
      bool UAaqjjXilz = false;
      bool AIhPXEicIX = false;
      bool YdOkfeUFne = false;
      bool dAkfHjUGqn = false;
      bool ndidArQHpE = false;
      bool GGghEploKF = false;
      bool PSuGVAWBIn = false;
      bool iclTittkkm = false;
      bool NMOjYWSDbQ = false;
      bool xfulYVicIA = false;
      bool VPzCUdUMyJ = false;
      bool uBDXqDDLhy = false;
      bool gTZrpDgAuN = false;
      bool KRckRyNMOu = false;
      bool CGERUwbXtV = false;
      bool RXuJSCpGLR = false;
      bool wTQkydXRGs = false;
      bool oqwlwaOHXt = false;
      string NExnjHtIEW;
      string UbLkURtAPD;
      string zHmlJWFIyh;
      string byaZAZJKjq;
      string ZoAyPmspFZ;
      string MueJFFRLeM;
      string ClJWtWAkju;
      string HjPXcKHnVV;
      string dPCXVfTQTu;
      string HyfXonedEs;
      string lIFKSbfGgu;
      string ycoIilikAN;
      string CjQomJErio;
      string fcjcjUJqFs;
      string AMjYxdIWnC;
      string EscqpCqQXI;
      string XmWqPUsMYN;
      string crfHMpArrI;
      string AgDgklzslg;
      string dsTwVNprJb;
      if(NExnjHtIEW == lIFKSbfGgu){jwyaYMNVdA = true;}
      else if(lIFKSbfGgu == NExnjHtIEW){NMOjYWSDbQ = true;}
      if(UbLkURtAPD == ycoIilikAN){BzXOIpioGc = true;}
      else if(ycoIilikAN == UbLkURtAPD){xfulYVicIA = true;}
      if(zHmlJWFIyh == CjQomJErio){UAaqjjXilz = true;}
      else if(CjQomJErio == zHmlJWFIyh){VPzCUdUMyJ = true;}
      if(byaZAZJKjq == fcjcjUJqFs){AIhPXEicIX = true;}
      else if(fcjcjUJqFs == byaZAZJKjq){uBDXqDDLhy = true;}
      if(ZoAyPmspFZ == AMjYxdIWnC){YdOkfeUFne = true;}
      else if(AMjYxdIWnC == ZoAyPmspFZ){gTZrpDgAuN = true;}
      if(MueJFFRLeM == EscqpCqQXI){dAkfHjUGqn = true;}
      else if(EscqpCqQXI == MueJFFRLeM){KRckRyNMOu = true;}
      if(ClJWtWAkju == XmWqPUsMYN){ndidArQHpE = true;}
      else if(XmWqPUsMYN == ClJWtWAkju){CGERUwbXtV = true;}
      if(HjPXcKHnVV == crfHMpArrI){GGghEploKF = true;}
      if(dPCXVfTQTu == AgDgklzslg){PSuGVAWBIn = true;}
      if(HyfXonedEs == dsTwVNprJb){iclTittkkm = true;}
      while(crfHMpArrI == HjPXcKHnVV){RXuJSCpGLR = true;}
      while(AgDgklzslg == AgDgklzslg){wTQkydXRGs = true;}
      while(dsTwVNprJb == dsTwVNprJb){oqwlwaOHXt = true;}
      if(jwyaYMNVdA == true){jwyaYMNVdA = false;}
      if(BzXOIpioGc == true){BzXOIpioGc = false;}
      if(UAaqjjXilz == true){UAaqjjXilz = false;}
      if(AIhPXEicIX == true){AIhPXEicIX = false;}
      if(YdOkfeUFne == true){YdOkfeUFne = false;}
      if(dAkfHjUGqn == true){dAkfHjUGqn = false;}
      if(ndidArQHpE == true){ndidArQHpE = false;}
      if(GGghEploKF == true){GGghEploKF = false;}
      if(PSuGVAWBIn == true){PSuGVAWBIn = false;}
      if(iclTittkkm == true){iclTittkkm = false;}
      if(NMOjYWSDbQ == true){NMOjYWSDbQ = false;}
      if(xfulYVicIA == true){xfulYVicIA = false;}
      if(VPzCUdUMyJ == true){VPzCUdUMyJ = false;}
      if(uBDXqDDLhy == true){uBDXqDDLhy = false;}
      if(gTZrpDgAuN == true){gTZrpDgAuN = false;}
      if(KRckRyNMOu == true){KRckRyNMOu = false;}
      if(CGERUwbXtV == true){CGERUwbXtV = false;}
      if(RXuJSCpGLR == true){RXuJSCpGLR = false;}
      if(wTQkydXRGs == true){wTQkydXRGs = false;}
      if(oqwlwaOHXt == true){oqwlwaOHXt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KUKKXIUWZG
{ 
  void wtJatUTBaT()
  { 
      bool dVpEihwiAz = false;
      bool LsuJoTccnp = false;
      bool ObPSPfysJH = false;
      bool JcKnfoNSof = false;
      bool qtuJKbOaYE = false;
      bool NOwpiBFXoD = false;
      bool jDYsohhGcz = false;
      bool FJnHyTfGHn = false;
      bool QWTFstfUFe = false;
      bool ipdkwnVCUb = false;
      bool tHxYzDanqO = false;
      bool VzPAmMiTzt = false;
      bool CNByQPfCLK = false;
      bool ydkesIYuFo = false;
      bool TqcpIiZcyj = false;
      bool ECCZYgFzHj = false;
      bool XXcgQqNkHd = false;
      bool nmNKZLjLog = false;
      bool oCDbFwbLFM = false;
      bool CZmVRuNwZR = false;
      string uejZpslQwQ;
      string iIBDRLWLsS;
      string lUXrTIKJVM;
      string SulTBeXWOo;
      string hUelkxSKUx;
      string ILCRmaGrGg;
      string hcuixnWgBl;
      string nzwEjRokHV;
      string pAnXEHrUfa;
      string YfPhGFZuox;
      string akIiIIPygV;
      string kUjjqhnWep;
      string uBBaNHjOxe;
      string qtwKuFqFPw;
      string qsmKoDwepY;
      string QDQzBYjgUB;
      string XABCdqYZok;
      string piGhyCNqlK;
      string LEXXNncwJV;
      string UKkNXqrkfx;
      if(uejZpslQwQ == akIiIIPygV){dVpEihwiAz = true;}
      else if(akIiIIPygV == uejZpslQwQ){tHxYzDanqO = true;}
      if(iIBDRLWLsS == kUjjqhnWep){LsuJoTccnp = true;}
      else if(kUjjqhnWep == iIBDRLWLsS){VzPAmMiTzt = true;}
      if(lUXrTIKJVM == uBBaNHjOxe){ObPSPfysJH = true;}
      else if(uBBaNHjOxe == lUXrTIKJVM){CNByQPfCLK = true;}
      if(SulTBeXWOo == qtwKuFqFPw){JcKnfoNSof = true;}
      else if(qtwKuFqFPw == SulTBeXWOo){ydkesIYuFo = true;}
      if(hUelkxSKUx == qsmKoDwepY){qtuJKbOaYE = true;}
      else if(qsmKoDwepY == hUelkxSKUx){TqcpIiZcyj = true;}
      if(ILCRmaGrGg == QDQzBYjgUB){NOwpiBFXoD = true;}
      else if(QDQzBYjgUB == ILCRmaGrGg){ECCZYgFzHj = true;}
      if(hcuixnWgBl == XABCdqYZok){jDYsohhGcz = true;}
      else if(XABCdqYZok == hcuixnWgBl){XXcgQqNkHd = true;}
      if(nzwEjRokHV == piGhyCNqlK){FJnHyTfGHn = true;}
      if(pAnXEHrUfa == LEXXNncwJV){QWTFstfUFe = true;}
      if(YfPhGFZuox == UKkNXqrkfx){ipdkwnVCUb = true;}
      while(piGhyCNqlK == nzwEjRokHV){nmNKZLjLog = true;}
      while(LEXXNncwJV == LEXXNncwJV){oCDbFwbLFM = true;}
      while(UKkNXqrkfx == UKkNXqrkfx){CZmVRuNwZR = true;}
      if(dVpEihwiAz == true){dVpEihwiAz = false;}
      if(LsuJoTccnp == true){LsuJoTccnp = false;}
      if(ObPSPfysJH == true){ObPSPfysJH = false;}
      if(JcKnfoNSof == true){JcKnfoNSof = false;}
      if(qtuJKbOaYE == true){qtuJKbOaYE = false;}
      if(NOwpiBFXoD == true){NOwpiBFXoD = false;}
      if(jDYsohhGcz == true){jDYsohhGcz = false;}
      if(FJnHyTfGHn == true){FJnHyTfGHn = false;}
      if(QWTFstfUFe == true){QWTFstfUFe = false;}
      if(ipdkwnVCUb == true){ipdkwnVCUb = false;}
      if(tHxYzDanqO == true){tHxYzDanqO = false;}
      if(VzPAmMiTzt == true){VzPAmMiTzt = false;}
      if(CNByQPfCLK == true){CNByQPfCLK = false;}
      if(ydkesIYuFo == true){ydkesIYuFo = false;}
      if(TqcpIiZcyj == true){TqcpIiZcyj = false;}
      if(ECCZYgFzHj == true){ECCZYgFzHj = false;}
      if(XXcgQqNkHd == true){XXcgQqNkHd = false;}
      if(nmNKZLjLog == true){nmNKZLjLog = false;}
      if(oCDbFwbLFM == true){oCDbFwbLFM = false;}
      if(CZmVRuNwZR == true){CZmVRuNwZR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGUVRAIFRZ
{ 
  void uJOLXpwzlI()
  { 
      bool lAjVqYQPrm = false;
      bool QCZnqfsqMi = false;
      bool gjUUXTzolB = false;
      bool WKpspYqAGW = false;
      bool LIkoALiqdC = false;
      bool zonThBeOyX = false;
      bool YbcqQGLgxR = false;
      bool nrkoXYzfTL = false;
      bool kILjCgVWKo = false;
      bool tcCiyiesYt = false;
      bool zBsLNGEywJ = false;
      bool CytlmPQroi = false;
      bool joWIXLpBqn = false;
      bool sFHZLiPzWu = false;
      bool cXZAluhPui = false;
      bool RlEpKKejnB = false;
      bool PCHHPwqUaD = false;
      bool zRVsGLOVVb = false;
      bool dZGIVHBRPB = false;
      bool DeLUeZQSkp = false;
      string WVxsSsJPLc;
      string poIHRxYyPa;
      string OGoyXHWqwD;
      string bnDUyKMXPK;
      string woCmQhrUBX;
      string HbMloQfyVL;
      string VRSHABkmJH;
      string kAhFdZDCho;
      string OCpXwAbQeg;
      string dNCEneVulP;
      string wEKtmGsGHP;
      string MdPfwTatKA;
      string YUIbcWydRz;
      string DIPSsKqwkp;
      string GVJOTAxWHT;
      string DajlpbwhQP;
      string HOoILENxll;
      string ceJUsDKsIc;
      string YbVxucXdbR;
      string OIeUhrgACO;
      if(WVxsSsJPLc == wEKtmGsGHP){lAjVqYQPrm = true;}
      else if(wEKtmGsGHP == WVxsSsJPLc){zBsLNGEywJ = true;}
      if(poIHRxYyPa == MdPfwTatKA){QCZnqfsqMi = true;}
      else if(MdPfwTatKA == poIHRxYyPa){CytlmPQroi = true;}
      if(OGoyXHWqwD == YUIbcWydRz){gjUUXTzolB = true;}
      else if(YUIbcWydRz == OGoyXHWqwD){joWIXLpBqn = true;}
      if(bnDUyKMXPK == DIPSsKqwkp){WKpspYqAGW = true;}
      else if(DIPSsKqwkp == bnDUyKMXPK){sFHZLiPzWu = true;}
      if(woCmQhrUBX == GVJOTAxWHT){LIkoALiqdC = true;}
      else if(GVJOTAxWHT == woCmQhrUBX){cXZAluhPui = true;}
      if(HbMloQfyVL == DajlpbwhQP){zonThBeOyX = true;}
      else if(DajlpbwhQP == HbMloQfyVL){RlEpKKejnB = true;}
      if(VRSHABkmJH == HOoILENxll){YbcqQGLgxR = true;}
      else if(HOoILENxll == VRSHABkmJH){PCHHPwqUaD = true;}
      if(kAhFdZDCho == ceJUsDKsIc){nrkoXYzfTL = true;}
      if(OCpXwAbQeg == YbVxucXdbR){kILjCgVWKo = true;}
      if(dNCEneVulP == OIeUhrgACO){tcCiyiesYt = true;}
      while(ceJUsDKsIc == kAhFdZDCho){zRVsGLOVVb = true;}
      while(YbVxucXdbR == YbVxucXdbR){dZGIVHBRPB = true;}
      while(OIeUhrgACO == OIeUhrgACO){DeLUeZQSkp = true;}
      if(lAjVqYQPrm == true){lAjVqYQPrm = false;}
      if(QCZnqfsqMi == true){QCZnqfsqMi = false;}
      if(gjUUXTzolB == true){gjUUXTzolB = false;}
      if(WKpspYqAGW == true){WKpspYqAGW = false;}
      if(LIkoALiqdC == true){LIkoALiqdC = false;}
      if(zonThBeOyX == true){zonThBeOyX = false;}
      if(YbcqQGLgxR == true){YbcqQGLgxR = false;}
      if(nrkoXYzfTL == true){nrkoXYzfTL = false;}
      if(kILjCgVWKo == true){kILjCgVWKo = false;}
      if(tcCiyiesYt == true){tcCiyiesYt = false;}
      if(zBsLNGEywJ == true){zBsLNGEywJ = false;}
      if(CytlmPQroi == true){CytlmPQroi = false;}
      if(joWIXLpBqn == true){joWIXLpBqn = false;}
      if(sFHZLiPzWu == true){sFHZLiPzWu = false;}
      if(cXZAluhPui == true){cXZAluhPui = false;}
      if(RlEpKKejnB == true){RlEpKKejnB = false;}
      if(PCHHPwqUaD == true){PCHHPwqUaD = false;}
      if(zRVsGLOVVb == true){zRVsGLOVVb = false;}
      if(dZGIVHBRPB == true){dZGIVHBRPB = false;}
      if(DeLUeZQSkp == true){DeLUeZQSkp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TUMVTCERJL
{ 
  void DCTQdLJzzM()
  { 
      bool JEgMoKPcXE = false;
      bool PfBWsfiEmf = false;
      bool alUxtsUEzS = false;
      bool ooRzJdXrlU = false;
      bool ieCEZpwiry = false;
      bool ZsPYVWiiSw = false;
      bool oLcEPaNBNP = false;
      bool IqSSxujQXE = false;
      bool wkLBsuYsdl = false;
      bool tnZoeWBxnz = false;
      bool cuVcpiaxba = false;
      bool lRLNzDAbLU = false;
      bool BUXaUTQcmZ = false;
      bool smbXaBPiKK = false;
      bool UbQDAcbLpb = false;
      bool WZkTxHWuIV = false;
      bool RxJCgzpmly = false;
      bool nRQBAZDUar = false;
      bool qFmKCTBIaT = false;
      bool dTZorXROVA = false;
      string ClxQHLJlpi;
      string RjEzilwAHq;
      string hmGFJeBGcU;
      string shQXslGOxe;
      string OSVLsorfcX;
      string sZPLBPfrGc;
      string JCIUpiSfFw;
      string fhDbcPQtLU;
      string lVcFaSREWd;
      string GOHUULJBVJ;
      string VMZfrLWmik;
      string ykflpnZDsW;
      string RNIboQZiHQ;
      string FPYByZwxNP;
      string wdVkeVhUdg;
      string lGHyrIDypa;
      string kmfRfiMdnQ;
      string qbpdamrXwS;
      string hFEaezIZJp;
      string VyGldIyDFw;
      if(ClxQHLJlpi == VMZfrLWmik){JEgMoKPcXE = true;}
      else if(VMZfrLWmik == ClxQHLJlpi){cuVcpiaxba = true;}
      if(RjEzilwAHq == ykflpnZDsW){PfBWsfiEmf = true;}
      else if(ykflpnZDsW == RjEzilwAHq){lRLNzDAbLU = true;}
      if(hmGFJeBGcU == RNIboQZiHQ){alUxtsUEzS = true;}
      else if(RNIboQZiHQ == hmGFJeBGcU){BUXaUTQcmZ = true;}
      if(shQXslGOxe == FPYByZwxNP){ooRzJdXrlU = true;}
      else if(FPYByZwxNP == shQXslGOxe){smbXaBPiKK = true;}
      if(OSVLsorfcX == wdVkeVhUdg){ieCEZpwiry = true;}
      else if(wdVkeVhUdg == OSVLsorfcX){UbQDAcbLpb = true;}
      if(sZPLBPfrGc == lGHyrIDypa){ZsPYVWiiSw = true;}
      else if(lGHyrIDypa == sZPLBPfrGc){WZkTxHWuIV = true;}
      if(JCIUpiSfFw == kmfRfiMdnQ){oLcEPaNBNP = true;}
      else if(kmfRfiMdnQ == JCIUpiSfFw){RxJCgzpmly = true;}
      if(fhDbcPQtLU == qbpdamrXwS){IqSSxujQXE = true;}
      if(lVcFaSREWd == hFEaezIZJp){wkLBsuYsdl = true;}
      if(GOHUULJBVJ == VyGldIyDFw){tnZoeWBxnz = true;}
      while(qbpdamrXwS == fhDbcPQtLU){nRQBAZDUar = true;}
      while(hFEaezIZJp == hFEaezIZJp){qFmKCTBIaT = true;}
      while(VyGldIyDFw == VyGldIyDFw){dTZorXROVA = true;}
      if(JEgMoKPcXE == true){JEgMoKPcXE = false;}
      if(PfBWsfiEmf == true){PfBWsfiEmf = false;}
      if(alUxtsUEzS == true){alUxtsUEzS = false;}
      if(ooRzJdXrlU == true){ooRzJdXrlU = false;}
      if(ieCEZpwiry == true){ieCEZpwiry = false;}
      if(ZsPYVWiiSw == true){ZsPYVWiiSw = false;}
      if(oLcEPaNBNP == true){oLcEPaNBNP = false;}
      if(IqSSxujQXE == true){IqSSxujQXE = false;}
      if(wkLBsuYsdl == true){wkLBsuYsdl = false;}
      if(tnZoeWBxnz == true){tnZoeWBxnz = false;}
      if(cuVcpiaxba == true){cuVcpiaxba = false;}
      if(lRLNzDAbLU == true){lRLNzDAbLU = false;}
      if(BUXaUTQcmZ == true){BUXaUTQcmZ = false;}
      if(smbXaBPiKK == true){smbXaBPiKK = false;}
      if(UbQDAcbLpb == true){UbQDAcbLpb = false;}
      if(WZkTxHWuIV == true){WZkTxHWuIV = false;}
      if(RxJCgzpmly == true){RxJCgzpmly = false;}
      if(nRQBAZDUar == true){nRQBAZDUar = false;}
      if(qFmKCTBIaT == true){qFmKCTBIaT = false;}
      if(dTZorXROVA == true){dTZorXROVA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YILZHCQPMG
{ 
  void mbOjeVGYnU()
  { 
      bool EtCnKGlZQf = false;
      bool KohLIJpCcw = false;
      bool KbyzEWlbGx = false;
      bool gDKclOgOwo = false;
      bool zSBgcVnMkH = false;
      bool IDXfSbuDim = false;
      bool UJSTyGeEYs = false;
      bool baFmxrZRWi = false;
      bool iYqzodeeJJ = false;
      bool TdfIUozhiV = false;
      bool qimqegxkha = false;
      bool CcgAEuRTeU = false;
      bool bAuPYyuxSI = false;
      bool sqiAqzkAUH = false;
      bool ftwhGpxeDY = false;
      bool WeCNtqnXSf = false;
      bool lASZhKtfIE = false;
      bool JRzWogDMIh = false;
      bool BPsskNoUGz = false;
      bool LNhnVebVAu = false;
      string zOPezbYLUo;
      string SNhPtKWAZU;
      string ycIRpbhWmE;
      string KcSxzewSgD;
      string EOBcMqLsFt;
      string XTqDKWFynW;
      string sBYQdoujPO;
      string NDSVQibeEz;
      string QnQrfqkOlb;
      string ZydKJCojzX;
      string wacqgTAVmb;
      string uasoFEkgkl;
      string DfynoOZHLN;
      string srfgCoLZLL;
      string qPaKgzFoEE;
      string RIzMTPcoBR;
      string trJZhDtLlQ;
      string sKVYunFmGp;
      string JjCHwkrSMm;
      string LVYsRyGBcd;
      if(zOPezbYLUo == wacqgTAVmb){EtCnKGlZQf = true;}
      else if(wacqgTAVmb == zOPezbYLUo){qimqegxkha = true;}
      if(SNhPtKWAZU == uasoFEkgkl){KohLIJpCcw = true;}
      else if(uasoFEkgkl == SNhPtKWAZU){CcgAEuRTeU = true;}
      if(ycIRpbhWmE == DfynoOZHLN){KbyzEWlbGx = true;}
      else if(DfynoOZHLN == ycIRpbhWmE){bAuPYyuxSI = true;}
      if(KcSxzewSgD == srfgCoLZLL){gDKclOgOwo = true;}
      else if(srfgCoLZLL == KcSxzewSgD){sqiAqzkAUH = true;}
      if(EOBcMqLsFt == qPaKgzFoEE){zSBgcVnMkH = true;}
      else if(qPaKgzFoEE == EOBcMqLsFt){ftwhGpxeDY = true;}
      if(XTqDKWFynW == RIzMTPcoBR){IDXfSbuDim = true;}
      else if(RIzMTPcoBR == XTqDKWFynW){WeCNtqnXSf = true;}
      if(sBYQdoujPO == trJZhDtLlQ){UJSTyGeEYs = true;}
      else if(trJZhDtLlQ == sBYQdoujPO){lASZhKtfIE = true;}
      if(NDSVQibeEz == sKVYunFmGp){baFmxrZRWi = true;}
      if(QnQrfqkOlb == JjCHwkrSMm){iYqzodeeJJ = true;}
      if(ZydKJCojzX == LVYsRyGBcd){TdfIUozhiV = true;}
      while(sKVYunFmGp == NDSVQibeEz){JRzWogDMIh = true;}
      while(JjCHwkrSMm == JjCHwkrSMm){BPsskNoUGz = true;}
      while(LVYsRyGBcd == LVYsRyGBcd){LNhnVebVAu = true;}
      if(EtCnKGlZQf == true){EtCnKGlZQf = false;}
      if(KohLIJpCcw == true){KohLIJpCcw = false;}
      if(KbyzEWlbGx == true){KbyzEWlbGx = false;}
      if(gDKclOgOwo == true){gDKclOgOwo = false;}
      if(zSBgcVnMkH == true){zSBgcVnMkH = false;}
      if(IDXfSbuDim == true){IDXfSbuDim = false;}
      if(UJSTyGeEYs == true){UJSTyGeEYs = false;}
      if(baFmxrZRWi == true){baFmxrZRWi = false;}
      if(iYqzodeeJJ == true){iYqzodeeJJ = false;}
      if(TdfIUozhiV == true){TdfIUozhiV = false;}
      if(qimqegxkha == true){qimqegxkha = false;}
      if(CcgAEuRTeU == true){CcgAEuRTeU = false;}
      if(bAuPYyuxSI == true){bAuPYyuxSI = false;}
      if(sqiAqzkAUH == true){sqiAqzkAUH = false;}
      if(ftwhGpxeDY == true){ftwhGpxeDY = false;}
      if(WeCNtqnXSf == true){WeCNtqnXSf = false;}
      if(lASZhKtfIE == true){lASZhKtfIE = false;}
      if(JRzWogDMIh == true){JRzWogDMIh = false;}
      if(BPsskNoUGz == true){BPsskNoUGz = false;}
      if(LNhnVebVAu == true){LNhnVebVAu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HTHEGPUALG
{ 
  void btgSdKBHse()
  { 
      bool CczYhINmtm = false;
      bool poUyQaxUMR = false;
      bool jYpspBlzuE = false;
      bool DLfCmRsjWN = false;
      bool DuyYmAXouM = false;
      bool nbEZrcmFif = false;
      bool VNqoieJSLy = false;
      bool hNyzOnaQGp = false;
      bool cxEhQaGFJJ = false;
      bool emBpqoEIoI = false;
      bool pFdweadFLD = false;
      bool CVzsCYJIYI = false;
      bool XEIBTtMHHY = false;
      bool jRbxzXTHDp = false;
      bool xBsGHJnImS = false;
      bool eujgjlwbcj = false;
      bool OVxmTktBse = false;
      bool FBFiKWKCtK = false;
      bool GEUosogtNM = false;
      bool areSaaEGlW = false;
      string EUqOaFYEKl;
      string riYHrHHqfF;
      string GNWbCatxIc;
      string moSZLQxCnd;
      string NFtUPKKXXx;
      string mYJfZqyOLz;
      string LbwgzDPyua;
      string JFDBqASBMr;
      string PVYLpOemAU;
      string RhpoSlJNVM;
      string uMbxmhVInY;
      string XxCTioCjqj;
      string XbyaJaOOhF;
      string qFeAwDtbXH;
      string sWzawUfVFc;
      string iZVlnSNAmM;
      string TGZhhSSCWf;
      string uaLiqAbXeo;
      string urJEVQisLd;
      string psnLnlxQrc;
      if(EUqOaFYEKl == uMbxmhVInY){CczYhINmtm = true;}
      else if(uMbxmhVInY == EUqOaFYEKl){pFdweadFLD = true;}
      if(riYHrHHqfF == XxCTioCjqj){poUyQaxUMR = true;}
      else if(XxCTioCjqj == riYHrHHqfF){CVzsCYJIYI = true;}
      if(GNWbCatxIc == XbyaJaOOhF){jYpspBlzuE = true;}
      else if(XbyaJaOOhF == GNWbCatxIc){XEIBTtMHHY = true;}
      if(moSZLQxCnd == qFeAwDtbXH){DLfCmRsjWN = true;}
      else if(qFeAwDtbXH == moSZLQxCnd){jRbxzXTHDp = true;}
      if(NFtUPKKXXx == sWzawUfVFc){DuyYmAXouM = true;}
      else if(sWzawUfVFc == NFtUPKKXXx){xBsGHJnImS = true;}
      if(mYJfZqyOLz == iZVlnSNAmM){nbEZrcmFif = true;}
      else if(iZVlnSNAmM == mYJfZqyOLz){eujgjlwbcj = true;}
      if(LbwgzDPyua == TGZhhSSCWf){VNqoieJSLy = true;}
      else if(TGZhhSSCWf == LbwgzDPyua){OVxmTktBse = true;}
      if(JFDBqASBMr == uaLiqAbXeo){hNyzOnaQGp = true;}
      if(PVYLpOemAU == urJEVQisLd){cxEhQaGFJJ = true;}
      if(RhpoSlJNVM == psnLnlxQrc){emBpqoEIoI = true;}
      while(uaLiqAbXeo == JFDBqASBMr){FBFiKWKCtK = true;}
      while(urJEVQisLd == urJEVQisLd){GEUosogtNM = true;}
      while(psnLnlxQrc == psnLnlxQrc){areSaaEGlW = true;}
      if(CczYhINmtm == true){CczYhINmtm = false;}
      if(poUyQaxUMR == true){poUyQaxUMR = false;}
      if(jYpspBlzuE == true){jYpspBlzuE = false;}
      if(DLfCmRsjWN == true){DLfCmRsjWN = false;}
      if(DuyYmAXouM == true){DuyYmAXouM = false;}
      if(nbEZrcmFif == true){nbEZrcmFif = false;}
      if(VNqoieJSLy == true){VNqoieJSLy = false;}
      if(hNyzOnaQGp == true){hNyzOnaQGp = false;}
      if(cxEhQaGFJJ == true){cxEhQaGFJJ = false;}
      if(emBpqoEIoI == true){emBpqoEIoI = false;}
      if(pFdweadFLD == true){pFdweadFLD = false;}
      if(CVzsCYJIYI == true){CVzsCYJIYI = false;}
      if(XEIBTtMHHY == true){XEIBTtMHHY = false;}
      if(jRbxzXTHDp == true){jRbxzXTHDp = false;}
      if(xBsGHJnImS == true){xBsGHJnImS = false;}
      if(eujgjlwbcj == true){eujgjlwbcj = false;}
      if(OVxmTktBse == true){OVxmTktBse = false;}
      if(FBFiKWKCtK == true){FBFiKWKCtK = false;}
      if(GEUosogtNM == true){GEUosogtNM = false;}
      if(areSaaEGlW == true){areSaaEGlW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PAYDSFNWVD
{ 
  void sWZSaqtrbC()
  { 
      bool ZKlZwlqoIG = false;
      bool XGCHyDyTNG = false;
      bool EkKDfiTrbK = false;
      bool abURJLeFBt = false;
      bool ihaYWmypKG = false;
      bool pIGExozhtN = false;
      bool SzNxfukkym = false;
      bool YrRTWVKlgr = false;
      bool kdgVTRUPTU = false;
      bool LxKnbjUcra = false;
      bool CMqWgyqmha = false;
      bool eMBCcnRqcO = false;
      bool aUQdbahdql = false;
      bool BgsFpXlKnV = false;
      bool aghrpywILm = false;
      bool ScAdAguNuF = false;
      bool QMwuZxTuLE = false;
      bool BGCGnsmYnc = false;
      bool eYRDSXgOFJ = false;
      bool bYOhFNklRr = false;
      string dRnxYYnXpN;
      string xnCqVbHpBh;
      string QGmDmYYSVW;
      string TFdjgkTHFk;
      string hZMUCqefHz;
      string VsMgqXdjJA;
      string zUBSsqJRJk;
      string HzjPzqtSBw;
      string ssLVBarxsJ;
      string GjyFlNXsaK;
      string gMWVrVIwgA;
      string dLhNGFIeRS;
      string zMYAdXBedl;
      string SAqqOgWpde;
      string SuPrftBjzf;
      string FrbIKUmVqU;
      string UdSugcTqyY;
      string iSBlADwgTj;
      string VQeygaXift;
      string sAyJJocULC;
      if(dRnxYYnXpN == gMWVrVIwgA){ZKlZwlqoIG = true;}
      else if(gMWVrVIwgA == dRnxYYnXpN){CMqWgyqmha = true;}
      if(xnCqVbHpBh == dLhNGFIeRS){XGCHyDyTNG = true;}
      else if(dLhNGFIeRS == xnCqVbHpBh){eMBCcnRqcO = true;}
      if(QGmDmYYSVW == zMYAdXBedl){EkKDfiTrbK = true;}
      else if(zMYAdXBedl == QGmDmYYSVW){aUQdbahdql = true;}
      if(TFdjgkTHFk == SAqqOgWpde){abURJLeFBt = true;}
      else if(SAqqOgWpde == TFdjgkTHFk){BgsFpXlKnV = true;}
      if(hZMUCqefHz == SuPrftBjzf){ihaYWmypKG = true;}
      else if(SuPrftBjzf == hZMUCqefHz){aghrpywILm = true;}
      if(VsMgqXdjJA == FrbIKUmVqU){pIGExozhtN = true;}
      else if(FrbIKUmVqU == VsMgqXdjJA){ScAdAguNuF = true;}
      if(zUBSsqJRJk == UdSugcTqyY){SzNxfukkym = true;}
      else if(UdSugcTqyY == zUBSsqJRJk){QMwuZxTuLE = true;}
      if(HzjPzqtSBw == iSBlADwgTj){YrRTWVKlgr = true;}
      if(ssLVBarxsJ == VQeygaXift){kdgVTRUPTU = true;}
      if(GjyFlNXsaK == sAyJJocULC){LxKnbjUcra = true;}
      while(iSBlADwgTj == HzjPzqtSBw){BGCGnsmYnc = true;}
      while(VQeygaXift == VQeygaXift){eYRDSXgOFJ = true;}
      while(sAyJJocULC == sAyJJocULC){bYOhFNklRr = true;}
      if(ZKlZwlqoIG == true){ZKlZwlqoIG = false;}
      if(XGCHyDyTNG == true){XGCHyDyTNG = false;}
      if(EkKDfiTrbK == true){EkKDfiTrbK = false;}
      if(abURJLeFBt == true){abURJLeFBt = false;}
      if(ihaYWmypKG == true){ihaYWmypKG = false;}
      if(pIGExozhtN == true){pIGExozhtN = false;}
      if(SzNxfukkym == true){SzNxfukkym = false;}
      if(YrRTWVKlgr == true){YrRTWVKlgr = false;}
      if(kdgVTRUPTU == true){kdgVTRUPTU = false;}
      if(LxKnbjUcra == true){LxKnbjUcra = false;}
      if(CMqWgyqmha == true){CMqWgyqmha = false;}
      if(eMBCcnRqcO == true){eMBCcnRqcO = false;}
      if(aUQdbahdql == true){aUQdbahdql = false;}
      if(BgsFpXlKnV == true){BgsFpXlKnV = false;}
      if(aghrpywILm == true){aghrpywILm = false;}
      if(ScAdAguNuF == true){ScAdAguNuF = false;}
      if(QMwuZxTuLE == true){QMwuZxTuLE = false;}
      if(BGCGnsmYnc == true){BGCGnsmYnc = false;}
      if(eYRDSXgOFJ == true){eYRDSXgOFJ = false;}
      if(bYOhFNklRr == true){bYOhFNklRr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NPRPPQUJFO
{ 
  void SruMgWuGwH()
  { 
      bool IJIBgJhRNb = false;
      bool AOgJLOZoQr = false;
      bool WTxOTaamGw = false;
      bool rDhCQGtAsw = false;
      bool wofFFamuLa = false;
      bool gqdBzoMthG = false;
      bool iuLQiwgdrE = false;
      bool UYwTwgmrJr = false;
      bool mebeOAYfDb = false;
      bool tARmNAdOVI = false;
      bool tIDGGHuKFR = false;
      bool BUkpSETfCh = false;
      bool WBaQJUGJGu = false;
      bool DXVAxdbUXG = false;
      bool FOakZZObTI = false;
      bool gxMnlshlxl = false;
      bool BkEKOdykrn = false;
      bool czIubIappj = false;
      bool FeoxNGKhOE = false;
      bool woWlFUJPWw = false;
      string PLolHpiPDq;
      string eVZNWffalM;
      string MZZTqAKrYo;
      string fpQYofXxKg;
      string DpiNMVjDWq;
      string gHYdOpkUuH;
      string eqpNKnEBXq;
      string IhQFJVpMHV;
      string PHUhHYQmJz;
      string tCCCBLAUCX;
      string QiffiypTUs;
      string zXNYqXVIGl;
      string WRrYwGfNDx;
      string VVKiFgbozI;
      string ixSQzWocLc;
      string pqOQBzpGib;
      string SbPWWcNeTJ;
      string wfJxCZzbYZ;
      string QDCZGdGtgF;
      string pUFWpGgusV;
      if(PLolHpiPDq == QiffiypTUs){IJIBgJhRNb = true;}
      else if(QiffiypTUs == PLolHpiPDq){tIDGGHuKFR = true;}
      if(eVZNWffalM == zXNYqXVIGl){AOgJLOZoQr = true;}
      else if(zXNYqXVIGl == eVZNWffalM){BUkpSETfCh = true;}
      if(MZZTqAKrYo == WRrYwGfNDx){WTxOTaamGw = true;}
      else if(WRrYwGfNDx == MZZTqAKrYo){WBaQJUGJGu = true;}
      if(fpQYofXxKg == VVKiFgbozI){rDhCQGtAsw = true;}
      else if(VVKiFgbozI == fpQYofXxKg){DXVAxdbUXG = true;}
      if(DpiNMVjDWq == ixSQzWocLc){wofFFamuLa = true;}
      else if(ixSQzWocLc == DpiNMVjDWq){FOakZZObTI = true;}
      if(gHYdOpkUuH == pqOQBzpGib){gqdBzoMthG = true;}
      else if(pqOQBzpGib == gHYdOpkUuH){gxMnlshlxl = true;}
      if(eqpNKnEBXq == SbPWWcNeTJ){iuLQiwgdrE = true;}
      else if(SbPWWcNeTJ == eqpNKnEBXq){BkEKOdykrn = true;}
      if(IhQFJVpMHV == wfJxCZzbYZ){UYwTwgmrJr = true;}
      if(PHUhHYQmJz == QDCZGdGtgF){mebeOAYfDb = true;}
      if(tCCCBLAUCX == pUFWpGgusV){tARmNAdOVI = true;}
      while(wfJxCZzbYZ == IhQFJVpMHV){czIubIappj = true;}
      while(QDCZGdGtgF == QDCZGdGtgF){FeoxNGKhOE = true;}
      while(pUFWpGgusV == pUFWpGgusV){woWlFUJPWw = true;}
      if(IJIBgJhRNb == true){IJIBgJhRNb = false;}
      if(AOgJLOZoQr == true){AOgJLOZoQr = false;}
      if(WTxOTaamGw == true){WTxOTaamGw = false;}
      if(rDhCQGtAsw == true){rDhCQGtAsw = false;}
      if(wofFFamuLa == true){wofFFamuLa = false;}
      if(gqdBzoMthG == true){gqdBzoMthG = false;}
      if(iuLQiwgdrE == true){iuLQiwgdrE = false;}
      if(UYwTwgmrJr == true){UYwTwgmrJr = false;}
      if(mebeOAYfDb == true){mebeOAYfDb = false;}
      if(tARmNAdOVI == true){tARmNAdOVI = false;}
      if(tIDGGHuKFR == true){tIDGGHuKFR = false;}
      if(BUkpSETfCh == true){BUkpSETfCh = false;}
      if(WBaQJUGJGu == true){WBaQJUGJGu = false;}
      if(DXVAxdbUXG == true){DXVAxdbUXG = false;}
      if(FOakZZObTI == true){FOakZZObTI = false;}
      if(gxMnlshlxl == true){gxMnlshlxl = false;}
      if(BkEKOdykrn == true){BkEKOdykrn = false;}
      if(czIubIappj == true){czIubIappj = false;}
      if(FeoxNGKhOE == true){FeoxNGKhOE = false;}
      if(woWlFUJPWw == true){woWlFUJPWw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UDFFSAHICB
{ 
  void UVHBbrpBqV()
  { 
      bool cfgnfWDDbZ = false;
      bool QKbynsRbso = false;
      bool PquebHSTxZ = false;
      bool fgasVxkzPj = false;
      bool wfLwyFjqWZ = false;
      bool UDLZgljCLY = false;
      bool DjFCtjjibq = false;
      bool ISMIsjfzfW = false;
      bool WawWEcVALj = false;
      bool NhnqfLZIBO = false;
      bool VBPfRCqCgx = false;
      bool GjWoBcnhxQ = false;
      bool OjWrcZdUbg = false;
      bool JWxQAVLQFC = false;
      bool kSSOccLzoD = false;
      bool XrLkzldWCq = false;
      bool XVaAmjmFne = false;
      bool RWbuewQIPA = false;
      bool OefYIRLMQO = false;
      bool rnOOePqSas = false;
      string GykONEHmOT;
      string dcFNCEBdZi;
      string qdbBnnXQKc;
      string AotdbiGQRe;
      string TSEJqbYoXo;
      string qkPCybWjZZ;
      string fpbkSohbkS;
      string xjLtPYYRKM;
      string OhsUlPYqez;
      string MWprycpTqC;
      string sxDErGYUmY;
      string DEZNKyxHyC;
      string PpwlGZtTwm;
      string iEaHSRdncf;
      string qEEFuHxbgA;
      string fhVnlCARyR;
      string LEYApzdRus;
      string TIeRLLkppz;
      string cRmwGAimVP;
      string QMpKTlfEPw;
      if(GykONEHmOT == sxDErGYUmY){cfgnfWDDbZ = true;}
      else if(sxDErGYUmY == GykONEHmOT){VBPfRCqCgx = true;}
      if(dcFNCEBdZi == DEZNKyxHyC){QKbynsRbso = true;}
      else if(DEZNKyxHyC == dcFNCEBdZi){GjWoBcnhxQ = true;}
      if(qdbBnnXQKc == PpwlGZtTwm){PquebHSTxZ = true;}
      else if(PpwlGZtTwm == qdbBnnXQKc){OjWrcZdUbg = true;}
      if(AotdbiGQRe == iEaHSRdncf){fgasVxkzPj = true;}
      else if(iEaHSRdncf == AotdbiGQRe){JWxQAVLQFC = true;}
      if(TSEJqbYoXo == qEEFuHxbgA){wfLwyFjqWZ = true;}
      else if(qEEFuHxbgA == TSEJqbYoXo){kSSOccLzoD = true;}
      if(qkPCybWjZZ == fhVnlCARyR){UDLZgljCLY = true;}
      else if(fhVnlCARyR == qkPCybWjZZ){XrLkzldWCq = true;}
      if(fpbkSohbkS == LEYApzdRus){DjFCtjjibq = true;}
      else if(LEYApzdRus == fpbkSohbkS){XVaAmjmFne = true;}
      if(xjLtPYYRKM == TIeRLLkppz){ISMIsjfzfW = true;}
      if(OhsUlPYqez == cRmwGAimVP){WawWEcVALj = true;}
      if(MWprycpTqC == QMpKTlfEPw){NhnqfLZIBO = true;}
      while(TIeRLLkppz == xjLtPYYRKM){RWbuewQIPA = true;}
      while(cRmwGAimVP == cRmwGAimVP){OefYIRLMQO = true;}
      while(QMpKTlfEPw == QMpKTlfEPw){rnOOePqSas = true;}
      if(cfgnfWDDbZ == true){cfgnfWDDbZ = false;}
      if(QKbynsRbso == true){QKbynsRbso = false;}
      if(PquebHSTxZ == true){PquebHSTxZ = false;}
      if(fgasVxkzPj == true){fgasVxkzPj = false;}
      if(wfLwyFjqWZ == true){wfLwyFjqWZ = false;}
      if(UDLZgljCLY == true){UDLZgljCLY = false;}
      if(DjFCtjjibq == true){DjFCtjjibq = false;}
      if(ISMIsjfzfW == true){ISMIsjfzfW = false;}
      if(WawWEcVALj == true){WawWEcVALj = false;}
      if(NhnqfLZIBO == true){NhnqfLZIBO = false;}
      if(VBPfRCqCgx == true){VBPfRCqCgx = false;}
      if(GjWoBcnhxQ == true){GjWoBcnhxQ = false;}
      if(OjWrcZdUbg == true){OjWrcZdUbg = false;}
      if(JWxQAVLQFC == true){JWxQAVLQFC = false;}
      if(kSSOccLzoD == true){kSSOccLzoD = false;}
      if(XrLkzldWCq == true){XrLkzldWCq = false;}
      if(XVaAmjmFne == true){XVaAmjmFne = false;}
      if(RWbuewQIPA == true){RWbuewQIPA = false;}
      if(OefYIRLMQO == true){OefYIRLMQO = false;}
      if(rnOOePqSas == true){rnOOePqSas = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUBMVNJOSB
{ 
  void AlIXemowsK()
  { 
      bool DYVVuQmxum = false;
      bool iOesYmKTRe = false;
      bool aKfAlVXygI = false;
      bool IogPKxrRzm = false;
      bool QzCXjNgrYG = false;
      bool hKLTfsrUjZ = false;
      bool snQmetgOhb = false;
      bool usTdNbHHQX = false;
      bool nfZZZxcNiR = false;
      bool EWgZtbiPro = false;
      bool fRJxKopgFD = false;
      bool kkELkMOpMh = false;
      bool QTfQWYLtil = false;
      bool srParVVcPk = false;
      bool HuHefTSVng = false;
      bool MrDKYLlsal = false;
      bool cwySKsVcSP = false;
      bool qlZaZVLAjC = false;
      bool GpGBZAnECf = false;
      bool jcBdILxoUl = false;
      string oXYCTsdMQp;
      string WbEyrtolZP;
      string JiiEZCkzrq;
      string hMJobDNGoe;
      string HtTyOlWWXP;
      string oTgIkGnTbR;
      string HeTYHJSPVo;
      string giwuHOOkpn;
      string eNbcCOeADV;
      string OsdXWcatpE;
      string THBhiGWlAW;
      string qDcnltCqWs;
      string eRMAZmEYXe;
      string nTukUXMstw;
      string qrzgdLQpkc;
      string ZjXxZBtAHu;
      string ByOVhWHqTO;
      string gJwaBlSfVO;
      string WNmuEDwxLS;
      string cLkytsdcyG;
      if(oXYCTsdMQp == THBhiGWlAW){DYVVuQmxum = true;}
      else if(THBhiGWlAW == oXYCTsdMQp){fRJxKopgFD = true;}
      if(WbEyrtolZP == qDcnltCqWs){iOesYmKTRe = true;}
      else if(qDcnltCqWs == WbEyrtolZP){kkELkMOpMh = true;}
      if(JiiEZCkzrq == eRMAZmEYXe){aKfAlVXygI = true;}
      else if(eRMAZmEYXe == JiiEZCkzrq){QTfQWYLtil = true;}
      if(hMJobDNGoe == nTukUXMstw){IogPKxrRzm = true;}
      else if(nTukUXMstw == hMJobDNGoe){srParVVcPk = true;}
      if(HtTyOlWWXP == qrzgdLQpkc){QzCXjNgrYG = true;}
      else if(qrzgdLQpkc == HtTyOlWWXP){HuHefTSVng = true;}
      if(oTgIkGnTbR == ZjXxZBtAHu){hKLTfsrUjZ = true;}
      else if(ZjXxZBtAHu == oTgIkGnTbR){MrDKYLlsal = true;}
      if(HeTYHJSPVo == ByOVhWHqTO){snQmetgOhb = true;}
      else if(ByOVhWHqTO == HeTYHJSPVo){cwySKsVcSP = true;}
      if(giwuHOOkpn == gJwaBlSfVO){usTdNbHHQX = true;}
      if(eNbcCOeADV == WNmuEDwxLS){nfZZZxcNiR = true;}
      if(OsdXWcatpE == cLkytsdcyG){EWgZtbiPro = true;}
      while(gJwaBlSfVO == giwuHOOkpn){qlZaZVLAjC = true;}
      while(WNmuEDwxLS == WNmuEDwxLS){GpGBZAnECf = true;}
      while(cLkytsdcyG == cLkytsdcyG){jcBdILxoUl = true;}
      if(DYVVuQmxum == true){DYVVuQmxum = false;}
      if(iOesYmKTRe == true){iOesYmKTRe = false;}
      if(aKfAlVXygI == true){aKfAlVXygI = false;}
      if(IogPKxrRzm == true){IogPKxrRzm = false;}
      if(QzCXjNgrYG == true){QzCXjNgrYG = false;}
      if(hKLTfsrUjZ == true){hKLTfsrUjZ = false;}
      if(snQmetgOhb == true){snQmetgOhb = false;}
      if(usTdNbHHQX == true){usTdNbHHQX = false;}
      if(nfZZZxcNiR == true){nfZZZxcNiR = false;}
      if(EWgZtbiPro == true){EWgZtbiPro = false;}
      if(fRJxKopgFD == true){fRJxKopgFD = false;}
      if(kkELkMOpMh == true){kkELkMOpMh = false;}
      if(QTfQWYLtil == true){QTfQWYLtil = false;}
      if(srParVVcPk == true){srParVVcPk = false;}
      if(HuHefTSVng == true){HuHefTSVng = false;}
      if(MrDKYLlsal == true){MrDKYLlsal = false;}
      if(cwySKsVcSP == true){cwySKsVcSP = false;}
      if(qlZaZVLAjC == true){qlZaZVLAjC = false;}
      if(GpGBZAnECf == true){GpGBZAnECf = false;}
      if(jcBdILxoUl == true){jcBdILxoUl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JYHKAHJNMB
{ 
  void RlpHBbDTJz()
  { 
      bool KuxKsacahs = false;
      bool CqCqqKTXTw = false;
      bool OsMixExAAh = false;
      bool zdnZEhrRiq = false;
      bool KsglUbJusR = false;
      bool OeonxRhNMn = false;
      bool dbZzsYCbmJ = false;
      bool SCnckULaNU = false;
      bool uBGhSUnAcm = false;
      bool zdEtNhShru = false;
      bool ZhIizMpMDb = false;
      bool GGzrsbUrgY = false;
      bool kCyzKnytOD = false;
      bool BdhRuNrWhG = false;
      bool dbxBgreLBk = false;
      bool MaATKWiJYL = false;
      bool NwxzZcYhxf = false;
      bool jxJZuIFxSR = false;
      bool JlrcpacOGX = false;
      bool diyWsgexbD = false;
      string WSRRALTbRk;
      string jDuZAVzGdh;
      string sdiWKDXCuk;
      string JoFxsaAgZP;
      string KlsXuWICQF;
      string MeAprritHw;
      string mRgfatyygZ;
      string USfOXHkLbm;
      string uVkoXdoOFA;
      string qFYcbrFMwB;
      string YKUpjtzlSk;
      string GXSUBRfqIw;
      string FisfiPsCle;
      string BYOaNkAuFd;
      string eCwTtSmEaK;
      string MOEzupQnHU;
      string AwzmihIrHQ;
      string QkkdRCmYlP;
      string cobbSmTPeX;
      string TLmkciCJjL;
      if(WSRRALTbRk == YKUpjtzlSk){KuxKsacahs = true;}
      else if(YKUpjtzlSk == WSRRALTbRk){ZhIizMpMDb = true;}
      if(jDuZAVzGdh == GXSUBRfqIw){CqCqqKTXTw = true;}
      else if(GXSUBRfqIw == jDuZAVzGdh){GGzrsbUrgY = true;}
      if(sdiWKDXCuk == FisfiPsCle){OsMixExAAh = true;}
      else if(FisfiPsCle == sdiWKDXCuk){kCyzKnytOD = true;}
      if(JoFxsaAgZP == BYOaNkAuFd){zdnZEhrRiq = true;}
      else if(BYOaNkAuFd == JoFxsaAgZP){BdhRuNrWhG = true;}
      if(KlsXuWICQF == eCwTtSmEaK){KsglUbJusR = true;}
      else if(eCwTtSmEaK == KlsXuWICQF){dbxBgreLBk = true;}
      if(MeAprritHw == MOEzupQnHU){OeonxRhNMn = true;}
      else if(MOEzupQnHU == MeAprritHw){MaATKWiJYL = true;}
      if(mRgfatyygZ == AwzmihIrHQ){dbZzsYCbmJ = true;}
      else if(AwzmihIrHQ == mRgfatyygZ){NwxzZcYhxf = true;}
      if(USfOXHkLbm == QkkdRCmYlP){SCnckULaNU = true;}
      if(uVkoXdoOFA == cobbSmTPeX){uBGhSUnAcm = true;}
      if(qFYcbrFMwB == TLmkciCJjL){zdEtNhShru = true;}
      while(QkkdRCmYlP == USfOXHkLbm){jxJZuIFxSR = true;}
      while(cobbSmTPeX == cobbSmTPeX){JlrcpacOGX = true;}
      while(TLmkciCJjL == TLmkciCJjL){diyWsgexbD = true;}
      if(KuxKsacahs == true){KuxKsacahs = false;}
      if(CqCqqKTXTw == true){CqCqqKTXTw = false;}
      if(OsMixExAAh == true){OsMixExAAh = false;}
      if(zdnZEhrRiq == true){zdnZEhrRiq = false;}
      if(KsglUbJusR == true){KsglUbJusR = false;}
      if(OeonxRhNMn == true){OeonxRhNMn = false;}
      if(dbZzsYCbmJ == true){dbZzsYCbmJ = false;}
      if(SCnckULaNU == true){SCnckULaNU = false;}
      if(uBGhSUnAcm == true){uBGhSUnAcm = false;}
      if(zdEtNhShru == true){zdEtNhShru = false;}
      if(ZhIizMpMDb == true){ZhIizMpMDb = false;}
      if(GGzrsbUrgY == true){GGzrsbUrgY = false;}
      if(kCyzKnytOD == true){kCyzKnytOD = false;}
      if(BdhRuNrWhG == true){BdhRuNrWhG = false;}
      if(dbxBgreLBk == true){dbxBgreLBk = false;}
      if(MaATKWiJYL == true){MaATKWiJYL = false;}
      if(NwxzZcYhxf == true){NwxzZcYhxf = false;}
      if(jxJZuIFxSR == true){jxJZuIFxSR = false;}
      if(JlrcpacOGX == true){JlrcpacOGX = false;}
      if(diyWsgexbD == true){diyWsgexbD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELNMYQWPJQ
{ 
  void cXEcExeMde()
  { 
      bool UVkrLSiXmG = false;
      bool IqHoKwegPm = false;
      bool ecTzByrckm = false;
      bool LnCUFmsHIU = false;
      bool qcbsVmTCMu = false;
      bool tyyyLqBkpN = false;
      bool aGlAuTnmiW = false;
      bool CWYtuCBZdN = false;
      bool dpQorMpDIO = false;
      bool lIQutkpayB = false;
      bool ygSosWZDDJ = false;
      bool obHbijoxIh = false;
      bool dkdTktGdAK = false;
      bool LaacPwWawU = false;
      bool lmAzZJAnLJ = false;
      bool usRPWNDzEy = false;
      bool QwCrxNAeMl = false;
      bool MNAmwpketb = false;
      bool sSRpOSILFB = false;
      bool sXWxEpjHBL = false;
      string LxnZeyXiQK;
      string OeAWOzATej;
      string QeLBjLiVhh;
      string qDwlkGsXhU;
      string xcfhhNhmLX;
      string umPiMfklpT;
      string PBBiSLhNlI;
      string FbkJmmzdTV;
      string duKJlEmNZE;
      string UHhNFubxOV;
      string fTADSTBFwY;
      string gHRTpTqqwO;
      string XTnhmysXEr;
      string LBOypJtHqS;
      string CgRAWMoOXk;
      string DjBzxLeSPT;
      string adBDNfrTdf;
      string ZjAcLqCnLZ;
      string JdzTnaAOAd;
      string dbqWrYfNlq;
      if(LxnZeyXiQK == fTADSTBFwY){UVkrLSiXmG = true;}
      else if(fTADSTBFwY == LxnZeyXiQK){ygSosWZDDJ = true;}
      if(OeAWOzATej == gHRTpTqqwO){IqHoKwegPm = true;}
      else if(gHRTpTqqwO == OeAWOzATej){obHbijoxIh = true;}
      if(QeLBjLiVhh == XTnhmysXEr){ecTzByrckm = true;}
      else if(XTnhmysXEr == QeLBjLiVhh){dkdTktGdAK = true;}
      if(qDwlkGsXhU == LBOypJtHqS){LnCUFmsHIU = true;}
      else if(LBOypJtHqS == qDwlkGsXhU){LaacPwWawU = true;}
      if(xcfhhNhmLX == CgRAWMoOXk){qcbsVmTCMu = true;}
      else if(CgRAWMoOXk == xcfhhNhmLX){lmAzZJAnLJ = true;}
      if(umPiMfklpT == DjBzxLeSPT){tyyyLqBkpN = true;}
      else if(DjBzxLeSPT == umPiMfklpT){usRPWNDzEy = true;}
      if(PBBiSLhNlI == adBDNfrTdf){aGlAuTnmiW = true;}
      else if(adBDNfrTdf == PBBiSLhNlI){QwCrxNAeMl = true;}
      if(FbkJmmzdTV == ZjAcLqCnLZ){CWYtuCBZdN = true;}
      if(duKJlEmNZE == JdzTnaAOAd){dpQorMpDIO = true;}
      if(UHhNFubxOV == dbqWrYfNlq){lIQutkpayB = true;}
      while(ZjAcLqCnLZ == FbkJmmzdTV){MNAmwpketb = true;}
      while(JdzTnaAOAd == JdzTnaAOAd){sSRpOSILFB = true;}
      while(dbqWrYfNlq == dbqWrYfNlq){sXWxEpjHBL = true;}
      if(UVkrLSiXmG == true){UVkrLSiXmG = false;}
      if(IqHoKwegPm == true){IqHoKwegPm = false;}
      if(ecTzByrckm == true){ecTzByrckm = false;}
      if(LnCUFmsHIU == true){LnCUFmsHIU = false;}
      if(qcbsVmTCMu == true){qcbsVmTCMu = false;}
      if(tyyyLqBkpN == true){tyyyLqBkpN = false;}
      if(aGlAuTnmiW == true){aGlAuTnmiW = false;}
      if(CWYtuCBZdN == true){CWYtuCBZdN = false;}
      if(dpQorMpDIO == true){dpQorMpDIO = false;}
      if(lIQutkpayB == true){lIQutkpayB = false;}
      if(ygSosWZDDJ == true){ygSosWZDDJ = false;}
      if(obHbijoxIh == true){obHbijoxIh = false;}
      if(dkdTktGdAK == true){dkdTktGdAK = false;}
      if(LaacPwWawU == true){LaacPwWawU = false;}
      if(lmAzZJAnLJ == true){lmAzZJAnLJ = false;}
      if(usRPWNDzEy == true){usRPWNDzEy = false;}
      if(QwCrxNAeMl == true){QwCrxNAeMl = false;}
      if(MNAmwpketb == true){MNAmwpketb = false;}
      if(sSRpOSILFB == true){sSRpOSILFB = false;}
      if(sXWxEpjHBL == true){sXWxEpjHBL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IFXZYIOTQV
{ 
  void AUPRGMknyx()
  { 
      bool hODruyOxdV = false;
      bool syLnIHQzQZ = false;
      bool ENoRomzBbz = false;
      bool rLFjaUCQLS = false;
      bool IjrTEggizt = false;
      bool PrMWBTYlCI = false;
      bool zMVechrbNn = false;
      bool EAmyRTVUNI = false;
      bool FPBgiAziiG = false;
      bool uQODSuOMqV = false;
      bool nFULpPENEg = false;
      bool yDYsCiKnwc = false;
      bool hIsGrnljeV = false;
      bool FJdqUAupqS = false;
      bool ukdBIqrUAj = false;
      bool kaQNneLNSB = false;
      bool dTiiboZgYC = false;
      bool mTwcgxeqyB = false;
      bool uQitkdrQDo = false;
      bool ngXooaCuZT = false;
      string lPDfmqGaeU;
      string lRpqqcJZwn;
      string uGRsXJkYre;
      string fPpHUgdWqJ;
      string rRXmKJfGhU;
      string ZdbNVexJId;
      string GhhAoWbhWK;
      string ymiludheiN;
      string ceqWEBnbko;
      string jUNNDKiXxn;
      string hxiWVmuoRr;
      string xRZuAbpKum;
      string hzwhZdYVik;
      string uKguffuTAQ;
      string GyKsrRtSMb;
      string TXbKFhABwr;
      string OZGgwljeOU;
      string fVJefjoCoI;
      string jGIGQWhWox;
      string esWICgqcwF;
      if(lPDfmqGaeU == hxiWVmuoRr){hODruyOxdV = true;}
      else if(hxiWVmuoRr == lPDfmqGaeU){nFULpPENEg = true;}
      if(lRpqqcJZwn == xRZuAbpKum){syLnIHQzQZ = true;}
      else if(xRZuAbpKum == lRpqqcJZwn){yDYsCiKnwc = true;}
      if(uGRsXJkYre == hzwhZdYVik){ENoRomzBbz = true;}
      else if(hzwhZdYVik == uGRsXJkYre){hIsGrnljeV = true;}
      if(fPpHUgdWqJ == uKguffuTAQ){rLFjaUCQLS = true;}
      else if(uKguffuTAQ == fPpHUgdWqJ){FJdqUAupqS = true;}
      if(rRXmKJfGhU == GyKsrRtSMb){IjrTEggizt = true;}
      else if(GyKsrRtSMb == rRXmKJfGhU){ukdBIqrUAj = true;}
      if(ZdbNVexJId == TXbKFhABwr){PrMWBTYlCI = true;}
      else if(TXbKFhABwr == ZdbNVexJId){kaQNneLNSB = true;}
      if(GhhAoWbhWK == OZGgwljeOU){zMVechrbNn = true;}
      else if(OZGgwljeOU == GhhAoWbhWK){dTiiboZgYC = true;}
      if(ymiludheiN == fVJefjoCoI){EAmyRTVUNI = true;}
      if(ceqWEBnbko == jGIGQWhWox){FPBgiAziiG = true;}
      if(jUNNDKiXxn == esWICgqcwF){uQODSuOMqV = true;}
      while(fVJefjoCoI == ymiludheiN){mTwcgxeqyB = true;}
      while(jGIGQWhWox == jGIGQWhWox){uQitkdrQDo = true;}
      while(esWICgqcwF == esWICgqcwF){ngXooaCuZT = true;}
      if(hODruyOxdV == true){hODruyOxdV = false;}
      if(syLnIHQzQZ == true){syLnIHQzQZ = false;}
      if(ENoRomzBbz == true){ENoRomzBbz = false;}
      if(rLFjaUCQLS == true){rLFjaUCQLS = false;}
      if(IjrTEggizt == true){IjrTEggizt = false;}
      if(PrMWBTYlCI == true){PrMWBTYlCI = false;}
      if(zMVechrbNn == true){zMVechrbNn = false;}
      if(EAmyRTVUNI == true){EAmyRTVUNI = false;}
      if(FPBgiAziiG == true){FPBgiAziiG = false;}
      if(uQODSuOMqV == true){uQODSuOMqV = false;}
      if(nFULpPENEg == true){nFULpPENEg = false;}
      if(yDYsCiKnwc == true){yDYsCiKnwc = false;}
      if(hIsGrnljeV == true){hIsGrnljeV = false;}
      if(FJdqUAupqS == true){FJdqUAupqS = false;}
      if(ukdBIqrUAj == true){ukdBIqrUAj = false;}
      if(kaQNneLNSB == true){kaQNneLNSB = false;}
      if(dTiiboZgYC == true){dTiiboZgYC = false;}
      if(mTwcgxeqyB == true){mTwcgxeqyB = false;}
      if(uQitkdrQDo == true){uQitkdrQDo = false;}
      if(ngXooaCuZT == true){ngXooaCuZT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZEVYVBRCQX
{ 
  void kifIOLHRPg()
  { 
      bool UqXYqBLegP = false;
      bool rquFCSiJUS = false;
      bool MZWbFRJnss = false;
      bool acEBuQaqqj = false;
      bool jgAcsNRaDQ = false;
      bool nfEPutUwSY = false;
      bool qXkmnPmtJk = false;
      bool rqRkhfZsir = false;
      bool AijcFtXoFA = false;
      bool wdYRrMuMnc = false;
      bool ZXRRXxNTgP = false;
      bool UaNZYImIht = false;
      bool rynIoNRzrU = false;
      bool jNFFRcQREH = false;
      bool fDHofUQysi = false;
      bool YletjbiIcK = false;
      bool eOaMeHVHIw = false;
      bool rVEZNoqzbT = false;
      bool wSGJwxhLUp = false;
      bool tIoscRbuKY = false;
      string MNsAtnHLEE;
      string gTxgbjIuKS;
      string fSJGrFZsOX;
      string wESzRSepRi;
      string BMPsFeKKZb;
      string UbYBktDmIo;
      string NOwfHcAxOI;
      string FScaQSCQAM;
      string uOTlCUeQOX;
      string PrhcVmQjkc;
      string eMwQWCyxkR;
      string qllusytJcm;
      string xiipsMkzFd;
      string CSeXhhSDPA;
      string VgfxgcFliW;
      string rGGyeucFWJ;
      string RyrGOXHONK;
      string fqtbQPClJQ;
      string HyPikwLgrl;
      string ENgGiWoZhI;
      if(MNsAtnHLEE == eMwQWCyxkR){UqXYqBLegP = true;}
      else if(eMwQWCyxkR == MNsAtnHLEE){ZXRRXxNTgP = true;}
      if(gTxgbjIuKS == qllusytJcm){rquFCSiJUS = true;}
      else if(qllusytJcm == gTxgbjIuKS){UaNZYImIht = true;}
      if(fSJGrFZsOX == xiipsMkzFd){MZWbFRJnss = true;}
      else if(xiipsMkzFd == fSJGrFZsOX){rynIoNRzrU = true;}
      if(wESzRSepRi == CSeXhhSDPA){acEBuQaqqj = true;}
      else if(CSeXhhSDPA == wESzRSepRi){jNFFRcQREH = true;}
      if(BMPsFeKKZb == VgfxgcFliW){jgAcsNRaDQ = true;}
      else if(VgfxgcFliW == BMPsFeKKZb){fDHofUQysi = true;}
      if(UbYBktDmIo == rGGyeucFWJ){nfEPutUwSY = true;}
      else if(rGGyeucFWJ == UbYBktDmIo){YletjbiIcK = true;}
      if(NOwfHcAxOI == RyrGOXHONK){qXkmnPmtJk = true;}
      else if(RyrGOXHONK == NOwfHcAxOI){eOaMeHVHIw = true;}
      if(FScaQSCQAM == fqtbQPClJQ){rqRkhfZsir = true;}
      if(uOTlCUeQOX == HyPikwLgrl){AijcFtXoFA = true;}
      if(PrhcVmQjkc == ENgGiWoZhI){wdYRrMuMnc = true;}
      while(fqtbQPClJQ == FScaQSCQAM){rVEZNoqzbT = true;}
      while(HyPikwLgrl == HyPikwLgrl){wSGJwxhLUp = true;}
      while(ENgGiWoZhI == ENgGiWoZhI){tIoscRbuKY = true;}
      if(UqXYqBLegP == true){UqXYqBLegP = false;}
      if(rquFCSiJUS == true){rquFCSiJUS = false;}
      if(MZWbFRJnss == true){MZWbFRJnss = false;}
      if(acEBuQaqqj == true){acEBuQaqqj = false;}
      if(jgAcsNRaDQ == true){jgAcsNRaDQ = false;}
      if(nfEPutUwSY == true){nfEPutUwSY = false;}
      if(qXkmnPmtJk == true){qXkmnPmtJk = false;}
      if(rqRkhfZsir == true){rqRkhfZsir = false;}
      if(AijcFtXoFA == true){AijcFtXoFA = false;}
      if(wdYRrMuMnc == true){wdYRrMuMnc = false;}
      if(ZXRRXxNTgP == true){ZXRRXxNTgP = false;}
      if(UaNZYImIht == true){UaNZYImIht = false;}
      if(rynIoNRzrU == true){rynIoNRzrU = false;}
      if(jNFFRcQREH == true){jNFFRcQREH = false;}
      if(fDHofUQysi == true){fDHofUQysi = false;}
      if(YletjbiIcK == true){YletjbiIcK = false;}
      if(eOaMeHVHIw == true){eOaMeHVHIw = false;}
      if(rVEZNoqzbT == true){rVEZNoqzbT = false;}
      if(wSGJwxhLUp == true){wSGJwxhLUp = false;}
      if(tIoscRbuKY == true){tIoscRbuKY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QCGLDLTZPT
{ 
  void OYggqIaKdi()
  { 
      bool daEPRysBHs = false;
      bool balwutSWPe = false;
      bool DCkaKkxlnt = false;
      bool ptEJOJNkHo = false;
      bool NjGRWpGBEB = false;
      bool uqYkzbocFf = false;
      bool AHNNChWbhl = false;
      bool ggOZRSuTEU = false;
      bool eugmyzUTKl = false;
      bool TkfanFWsOo = false;
      bool TeSSUObyTf = false;
      bool fVXjBFZZOD = false;
      bool MCRuRuAmlL = false;
      bool wCFPBAcORj = false;
      bool WWzdGyMuZi = false;
      bool fwdLbQMWAY = false;
      bool NnMIjdQIiB = false;
      bool bKIefpCnoT = false;
      bool hENCeAXtmj = false;
      bool mFOrViJqtb = false;
      string PUybLQXfEc;
      string eaSgGkOiRi;
      string QxjZrpDYsq;
      string okVaXaBAEd;
      string aiswFsKLHY;
      string XrHrDRjYjV;
      string MzlMnsFrJe;
      string jNdnIhEnUy;
      string frQUTwdcWF;
      string qbQiQbwfIM;
      string nRBcnKOTjV;
      string NwEkpUhRsq;
      string ObVDmIxtWg;
      string kXeIKNpmfI;
      string hKrAqtWerw;
      string selQxLwxof;
      string MTxDkoQwab;
      string dukjIEiULr;
      string kRBZmGlOKz;
      string RryzwONoPC;
      if(PUybLQXfEc == nRBcnKOTjV){daEPRysBHs = true;}
      else if(nRBcnKOTjV == PUybLQXfEc){TeSSUObyTf = true;}
      if(eaSgGkOiRi == NwEkpUhRsq){balwutSWPe = true;}
      else if(NwEkpUhRsq == eaSgGkOiRi){fVXjBFZZOD = true;}
      if(QxjZrpDYsq == ObVDmIxtWg){DCkaKkxlnt = true;}
      else if(ObVDmIxtWg == QxjZrpDYsq){MCRuRuAmlL = true;}
      if(okVaXaBAEd == kXeIKNpmfI){ptEJOJNkHo = true;}
      else if(kXeIKNpmfI == okVaXaBAEd){wCFPBAcORj = true;}
      if(aiswFsKLHY == hKrAqtWerw){NjGRWpGBEB = true;}
      else if(hKrAqtWerw == aiswFsKLHY){WWzdGyMuZi = true;}
      if(XrHrDRjYjV == selQxLwxof){uqYkzbocFf = true;}
      else if(selQxLwxof == XrHrDRjYjV){fwdLbQMWAY = true;}
      if(MzlMnsFrJe == MTxDkoQwab){AHNNChWbhl = true;}
      else if(MTxDkoQwab == MzlMnsFrJe){NnMIjdQIiB = true;}
      if(jNdnIhEnUy == dukjIEiULr){ggOZRSuTEU = true;}
      if(frQUTwdcWF == kRBZmGlOKz){eugmyzUTKl = true;}
      if(qbQiQbwfIM == RryzwONoPC){TkfanFWsOo = true;}
      while(dukjIEiULr == jNdnIhEnUy){bKIefpCnoT = true;}
      while(kRBZmGlOKz == kRBZmGlOKz){hENCeAXtmj = true;}
      while(RryzwONoPC == RryzwONoPC){mFOrViJqtb = true;}
      if(daEPRysBHs == true){daEPRysBHs = false;}
      if(balwutSWPe == true){balwutSWPe = false;}
      if(DCkaKkxlnt == true){DCkaKkxlnt = false;}
      if(ptEJOJNkHo == true){ptEJOJNkHo = false;}
      if(NjGRWpGBEB == true){NjGRWpGBEB = false;}
      if(uqYkzbocFf == true){uqYkzbocFf = false;}
      if(AHNNChWbhl == true){AHNNChWbhl = false;}
      if(ggOZRSuTEU == true){ggOZRSuTEU = false;}
      if(eugmyzUTKl == true){eugmyzUTKl = false;}
      if(TkfanFWsOo == true){TkfanFWsOo = false;}
      if(TeSSUObyTf == true){TeSSUObyTf = false;}
      if(fVXjBFZZOD == true){fVXjBFZZOD = false;}
      if(MCRuRuAmlL == true){MCRuRuAmlL = false;}
      if(wCFPBAcORj == true){wCFPBAcORj = false;}
      if(WWzdGyMuZi == true){WWzdGyMuZi = false;}
      if(fwdLbQMWAY == true){fwdLbQMWAY = false;}
      if(NnMIjdQIiB == true){NnMIjdQIiB = false;}
      if(bKIefpCnoT == true){bKIefpCnoT = false;}
      if(hENCeAXtmj == true){hENCeAXtmj = false;}
      if(mFOrViJqtb == true){mFOrViJqtb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TUAAHYYUDD
{ 
  void sQfkUXJfnT()
  { 
      bool EWJISygbHV = false;
      bool JgdUrmkFJK = false;
      bool cJLGmdKqGX = false;
      bool MaXYJNuked = false;
      bool JGBJZYNJYo = false;
      bool gjsGguKCUn = false;
      bool npUiIiIEKe = false;
      bool rAZfAWIBfO = false;
      bool PARRpbgQqN = false;
      bool CrPqoTkRBq = false;
      bool QJytxgJNGK = false;
      bool mIVGXnXDsf = false;
      bool BqMwbzjiqg = false;
      bool lqAoyGCXTI = false;
      bool RTKgatWJSB = false;
      bool wgXUpYwBSy = false;
      bool xaVYYwHgHR = false;
      bool kzjjNhffUg = false;
      bool cZQpkESfzY = false;
      bool KAFVLqxlHe = false;
      string fNDrmdKeRm;
      string GHbjrrdbQW;
      string rJweyFddGp;
      string XYwNzMiIGP;
      string TRuCDSuEyj;
      string UxpEKVRXsg;
      string AfYbPgLNje;
      string JUVADaOsbe;
      string KYfVVZiqDd;
      string tKOYOmsSmW;
      string HgTSazboBi;
      string HXwOWaACGo;
      string xTKGjyGwlP;
      string guGEXcFMtV;
      string ytoTWVNACn;
      string mpMyYmWNhc;
      string seDlCLRqqs;
      string VnIjpDdpjN;
      string jFtxbqiIfj;
      string FqdRcSpDRK;
      if(fNDrmdKeRm == HgTSazboBi){EWJISygbHV = true;}
      else if(HgTSazboBi == fNDrmdKeRm){QJytxgJNGK = true;}
      if(GHbjrrdbQW == HXwOWaACGo){JgdUrmkFJK = true;}
      else if(HXwOWaACGo == GHbjrrdbQW){mIVGXnXDsf = true;}
      if(rJweyFddGp == xTKGjyGwlP){cJLGmdKqGX = true;}
      else if(xTKGjyGwlP == rJweyFddGp){BqMwbzjiqg = true;}
      if(XYwNzMiIGP == guGEXcFMtV){MaXYJNuked = true;}
      else if(guGEXcFMtV == XYwNzMiIGP){lqAoyGCXTI = true;}
      if(TRuCDSuEyj == ytoTWVNACn){JGBJZYNJYo = true;}
      else if(ytoTWVNACn == TRuCDSuEyj){RTKgatWJSB = true;}
      if(UxpEKVRXsg == mpMyYmWNhc){gjsGguKCUn = true;}
      else if(mpMyYmWNhc == UxpEKVRXsg){wgXUpYwBSy = true;}
      if(AfYbPgLNje == seDlCLRqqs){npUiIiIEKe = true;}
      else if(seDlCLRqqs == AfYbPgLNje){xaVYYwHgHR = true;}
      if(JUVADaOsbe == VnIjpDdpjN){rAZfAWIBfO = true;}
      if(KYfVVZiqDd == jFtxbqiIfj){PARRpbgQqN = true;}
      if(tKOYOmsSmW == FqdRcSpDRK){CrPqoTkRBq = true;}
      while(VnIjpDdpjN == JUVADaOsbe){kzjjNhffUg = true;}
      while(jFtxbqiIfj == jFtxbqiIfj){cZQpkESfzY = true;}
      while(FqdRcSpDRK == FqdRcSpDRK){KAFVLqxlHe = true;}
      if(EWJISygbHV == true){EWJISygbHV = false;}
      if(JgdUrmkFJK == true){JgdUrmkFJK = false;}
      if(cJLGmdKqGX == true){cJLGmdKqGX = false;}
      if(MaXYJNuked == true){MaXYJNuked = false;}
      if(JGBJZYNJYo == true){JGBJZYNJYo = false;}
      if(gjsGguKCUn == true){gjsGguKCUn = false;}
      if(npUiIiIEKe == true){npUiIiIEKe = false;}
      if(rAZfAWIBfO == true){rAZfAWIBfO = false;}
      if(PARRpbgQqN == true){PARRpbgQqN = false;}
      if(CrPqoTkRBq == true){CrPqoTkRBq = false;}
      if(QJytxgJNGK == true){QJytxgJNGK = false;}
      if(mIVGXnXDsf == true){mIVGXnXDsf = false;}
      if(BqMwbzjiqg == true){BqMwbzjiqg = false;}
      if(lqAoyGCXTI == true){lqAoyGCXTI = false;}
      if(RTKgatWJSB == true){RTKgatWJSB = false;}
      if(wgXUpYwBSy == true){wgXUpYwBSy = false;}
      if(xaVYYwHgHR == true){xaVYYwHgHR = false;}
      if(kzjjNhffUg == true){kzjjNhffUg = false;}
      if(cZQpkESfzY == true){cZQpkESfzY = false;}
      if(KAFVLqxlHe == true){KAFVLqxlHe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OORVHHYFFU
{ 
  void xrbOCNVMxG()
  { 
      bool BcKItDxhNe = false;
      bool IEUpTetPTC = false;
      bool uxskjmlouX = false;
      bool xfLxgNgfLg = false;
      bool HdQLFruwyN = false;
      bool QmDykEiYYH = false;
      bool RHlphbsXJG = false;
      bool xOEltQfgfq = false;
      bool qopgGKcNMb = false;
      bool dIHEPAqadc = false;
      bool zXmrPChQDT = false;
      bool YCrhQbRFiW = false;
      bool zfLgcoHzWt = false;
      bool ZECDqTCyQD = false;
      bool bLJrDaQZmn = false;
      bool hlqGcTLFPa = false;
      bool uitJtTznpx = false;
      bool YSnfumVScB = false;
      bool XhMhLmMwZX = false;
      bool HwioIsRAyi = false;
      string PbtcSrJJkd;
      string hXfSfeJrtb;
      string MUVKlaqahu;
      string nFtmXmEZcU;
      string yPORiUcKdp;
      string HdCyNuGipr;
      string Bibpoccrtr;
      string ZjPYdxFDbR;
      string xfxrmKCwYc;
      string fVijTOnYbF;
      string rjQkPXOcTQ;
      string oDHYtUliDe;
      string ZfTRLEBeFO;
      string JgaWZNPLcP;
      string uZcHncNJpz;
      string cEVweLQyYK;
      string WjWFHHbkzg;
      string EZGmiADLch;
      string pqoGkFLdqN;
      string xQmRrLCWAf;
      if(PbtcSrJJkd == rjQkPXOcTQ){BcKItDxhNe = true;}
      else if(rjQkPXOcTQ == PbtcSrJJkd){zXmrPChQDT = true;}
      if(hXfSfeJrtb == oDHYtUliDe){IEUpTetPTC = true;}
      else if(oDHYtUliDe == hXfSfeJrtb){YCrhQbRFiW = true;}
      if(MUVKlaqahu == ZfTRLEBeFO){uxskjmlouX = true;}
      else if(ZfTRLEBeFO == MUVKlaqahu){zfLgcoHzWt = true;}
      if(nFtmXmEZcU == JgaWZNPLcP){xfLxgNgfLg = true;}
      else if(JgaWZNPLcP == nFtmXmEZcU){ZECDqTCyQD = true;}
      if(yPORiUcKdp == uZcHncNJpz){HdQLFruwyN = true;}
      else if(uZcHncNJpz == yPORiUcKdp){bLJrDaQZmn = true;}
      if(HdCyNuGipr == cEVweLQyYK){QmDykEiYYH = true;}
      else if(cEVweLQyYK == HdCyNuGipr){hlqGcTLFPa = true;}
      if(Bibpoccrtr == WjWFHHbkzg){RHlphbsXJG = true;}
      else if(WjWFHHbkzg == Bibpoccrtr){uitJtTznpx = true;}
      if(ZjPYdxFDbR == EZGmiADLch){xOEltQfgfq = true;}
      if(xfxrmKCwYc == pqoGkFLdqN){qopgGKcNMb = true;}
      if(fVijTOnYbF == xQmRrLCWAf){dIHEPAqadc = true;}
      while(EZGmiADLch == ZjPYdxFDbR){YSnfumVScB = true;}
      while(pqoGkFLdqN == pqoGkFLdqN){XhMhLmMwZX = true;}
      while(xQmRrLCWAf == xQmRrLCWAf){HwioIsRAyi = true;}
      if(BcKItDxhNe == true){BcKItDxhNe = false;}
      if(IEUpTetPTC == true){IEUpTetPTC = false;}
      if(uxskjmlouX == true){uxskjmlouX = false;}
      if(xfLxgNgfLg == true){xfLxgNgfLg = false;}
      if(HdQLFruwyN == true){HdQLFruwyN = false;}
      if(QmDykEiYYH == true){QmDykEiYYH = false;}
      if(RHlphbsXJG == true){RHlphbsXJG = false;}
      if(xOEltQfgfq == true){xOEltQfgfq = false;}
      if(qopgGKcNMb == true){qopgGKcNMb = false;}
      if(dIHEPAqadc == true){dIHEPAqadc = false;}
      if(zXmrPChQDT == true){zXmrPChQDT = false;}
      if(YCrhQbRFiW == true){YCrhQbRFiW = false;}
      if(zfLgcoHzWt == true){zfLgcoHzWt = false;}
      if(ZECDqTCyQD == true){ZECDqTCyQD = false;}
      if(bLJrDaQZmn == true){bLJrDaQZmn = false;}
      if(hlqGcTLFPa == true){hlqGcTLFPa = false;}
      if(uitJtTznpx == true){uitJtTznpx = false;}
      if(YSnfumVScB == true){YSnfumVScB = false;}
      if(XhMhLmMwZX == true){XhMhLmMwZX = false;}
      if(HwioIsRAyi == true){HwioIsRAyi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OEZIHJDBEZ
{ 
  void dGaGWWzOSx()
  { 
      bool FcYjpEJOTx = false;
      bool wzfkpwZtUT = false;
      bool rfruGbhJhn = false;
      bool rUOebYkINR = false;
      bool HeAsNtwkUj = false;
      bool whMqXYjddO = false;
      bool WAffFajAIQ = false;
      bool LQgDLMeyhM = false;
      bool ewnxqKIXHD = false;
      bool oGeyuHyUnl = false;
      bool JubEXfAJeK = false;
      bool skwRiZLint = false;
      bool SMsFaFkhHE = false;
      bool OKKuCjTiYL = false;
      bool JyrxJEJNOU = false;
      bool uPftTxCWdS = false;
      bool tSBauiaBOz = false;
      bool FbJckTTuuW = false;
      bool uWSmIydPbE = false;
      bool hxFGQqwRBa = false;
      string nPXazwmTxI;
      string uRPhawScuX;
      string jZoFdOKxlK;
      string WawNZgZmqq;
      string qjUOhuygBc;
      string aiCChOZSwk;
      string logmlTVCIt;
      string VfkEgzFaXi;
      string PcwJimYteL;
      string GHqGEBCgbN;
      string ZwYGGuyyVi;
      string JztNUJsXDy;
      string uaWxnOneze;
      string xXyJITEoCn;
      string oaYwBGMdku;
      string IeddSyZbSq;
      string GSyqllBjEA;
      string EEUPJUCZug;
      string BJsEVRsUqJ;
      string tcVKgVbgKP;
      if(nPXazwmTxI == ZwYGGuyyVi){FcYjpEJOTx = true;}
      else if(ZwYGGuyyVi == nPXazwmTxI){JubEXfAJeK = true;}
      if(uRPhawScuX == JztNUJsXDy){wzfkpwZtUT = true;}
      else if(JztNUJsXDy == uRPhawScuX){skwRiZLint = true;}
      if(jZoFdOKxlK == uaWxnOneze){rfruGbhJhn = true;}
      else if(uaWxnOneze == jZoFdOKxlK){SMsFaFkhHE = true;}
      if(WawNZgZmqq == xXyJITEoCn){rUOebYkINR = true;}
      else if(xXyJITEoCn == WawNZgZmqq){OKKuCjTiYL = true;}
      if(qjUOhuygBc == oaYwBGMdku){HeAsNtwkUj = true;}
      else if(oaYwBGMdku == qjUOhuygBc){JyrxJEJNOU = true;}
      if(aiCChOZSwk == IeddSyZbSq){whMqXYjddO = true;}
      else if(IeddSyZbSq == aiCChOZSwk){uPftTxCWdS = true;}
      if(logmlTVCIt == GSyqllBjEA){WAffFajAIQ = true;}
      else if(GSyqllBjEA == logmlTVCIt){tSBauiaBOz = true;}
      if(VfkEgzFaXi == EEUPJUCZug){LQgDLMeyhM = true;}
      if(PcwJimYteL == BJsEVRsUqJ){ewnxqKIXHD = true;}
      if(GHqGEBCgbN == tcVKgVbgKP){oGeyuHyUnl = true;}
      while(EEUPJUCZug == VfkEgzFaXi){FbJckTTuuW = true;}
      while(BJsEVRsUqJ == BJsEVRsUqJ){uWSmIydPbE = true;}
      while(tcVKgVbgKP == tcVKgVbgKP){hxFGQqwRBa = true;}
      if(FcYjpEJOTx == true){FcYjpEJOTx = false;}
      if(wzfkpwZtUT == true){wzfkpwZtUT = false;}
      if(rfruGbhJhn == true){rfruGbhJhn = false;}
      if(rUOebYkINR == true){rUOebYkINR = false;}
      if(HeAsNtwkUj == true){HeAsNtwkUj = false;}
      if(whMqXYjddO == true){whMqXYjddO = false;}
      if(WAffFajAIQ == true){WAffFajAIQ = false;}
      if(LQgDLMeyhM == true){LQgDLMeyhM = false;}
      if(ewnxqKIXHD == true){ewnxqKIXHD = false;}
      if(oGeyuHyUnl == true){oGeyuHyUnl = false;}
      if(JubEXfAJeK == true){JubEXfAJeK = false;}
      if(skwRiZLint == true){skwRiZLint = false;}
      if(SMsFaFkhHE == true){SMsFaFkhHE = false;}
      if(OKKuCjTiYL == true){OKKuCjTiYL = false;}
      if(JyrxJEJNOU == true){JyrxJEJNOU = false;}
      if(uPftTxCWdS == true){uPftTxCWdS = false;}
      if(tSBauiaBOz == true){tSBauiaBOz = false;}
      if(FbJckTTuuW == true){FbJckTTuuW = false;}
      if(uWSmIydPbE == true){uWSmIydPbE = false;}
      if(hxFGQqwRBa == true){hxFGQqwRBa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMCUBVXJGH
{ 
  void OHFOYuPEJY()
  { 
      bool zLsUCaqyow = false;
      bool dsQUldqadc = false;
      bool WsindpnNOe = false;
      bool zRGJflLVuA = false;
      bool ufxjZpMKPy = false;
      bool coNdaFbFqM = false;
      bool mcjKwMlHoA = false;
      bool RVedgpwzOm = false;
      bool cdyQCJDbiZ = false;
      bool JGdhMSwlmM = false;
      bool DEUPfGJjxj = false;
      bool JcqDiJeSHm = false;
      bool IJXPpLrwQN = false;
      bool tJLBjYIhjw = false;
      bool zTezQfPZzC = false;
      bool nceAEsfEYU = false;
      bool NNSiozRoTK = false;
      bool AwiLmoeYzK = false;
      bool uRxOZQeKwp = false;
      bool rEJOhlAuJQ = false;
      string hyWnSDtRQn;
      string XzHqQIGbIB;
      string QwWHQkyDQa;
      string alSsJQysSx;
      string kLhDAcENMT;
      string nQErNkbOXh;
      string FpAoMkgOgA;
      string JMJLQENSHm;
      string fjqxmKgZeX;
      string ojVjqtKrqP;
      string upgLJaHrbI;
      string XIHjCVzDCC;
      string DHiILZqYTW;
      string tUbqroCfmL;
      string CoxVAfbkhV;
      string uHpoLnGYAj;
      string ihYFOCgPrM;
      string STQqzOJNHe;
      string xFqyblemfD;
      string iceCbTPrGy;
      if(hyWnSDtRQn == upgLJaHrbI){zLsUCaqyow = true;}
      else if(upgLJaHrbI == hyWnSDtRQn){DEUPfGJjxj = true;}
      if(XzHqQIGbIB == XIHjCVzDCC){dsQUldqadc = true;}
      else if(XIHjCVzDCC == XzHqQIGbIB){JcqDiJeSHm = true;}
      if(QwWHQkyDQa == DHiILZqYTW){WsindpnNOe = true;}
      else if(DHiILZqYTW == QwWHQkyDQa){IJXPpLrwQN = true;}
      if(alSsJQysSx == tUbqroCfmL){zRGJflLVuA = true;}
      else if(tUbqroCfmL == alSsJQysSx){tJLBjYIhjw = true;}
      if(kLhDAcENMT == CoxVAfbkhV){ufxjZpMKPy = true;}
      else if(CoxVAfbkhV == kLhDAcENMT){zTezQfPZzC = true;}
      if(nQErNkbOXh == uHpoLnGYAj){coNdaFbFqM = true;}
      else if(uHpoLnGYAj == nQErNkbOXh){nceAEsfEYU = true;}
      if(FpAoMkgOgA == ihYFOCgPrM){mcjKwMlHoA = true;}
      else if(ihYFOCgPrM == FpAoMkgOgA){NNSiozRoTK = true;}
      if(JMJLQENSHm == STQqzOJNHe){RVedgpwzOm = true;}
      if(fjqxmKgZeX == xFqyblemfD){cdyQCJDbiZ = true;}
      if(ojVjqtKrqP == iceCbTPrGy){JGdhMSwlmM = true;}
      while(STQqzOJNHe == JMJLQENSHm){AwiLmoeYzK = true;}
      while(xFqyblemfD == xFqyblemfD){uRxOZQeKwp = true;}
      while(iceCbTPrGy == iceCbTPrGy){rEJOhlAuJQ = true;}
      if(zLsUCaqyow == true){zLsUCaqyow = false;}
      if(dsQUldqadc == true){dsQUldqadc = false;}
      if(WsindpnNOe == true){WsindpnNOe = false;}
      if(zRGJflLVuA == true){zRGJflLVuA = false;}
      if(ufxjZpMKPy == true){ufxjZpMKPy = false;}
      if(coNdaFbFqM == true){coNdaFbFqM = false;}
      if(mcjKwMlHoA == true){mcjKwMlHoA = false;}
      if(RVedgpwzOm == true){RVedgpwzOm = false;}
      if(cdyQCJDbiZ == true){cdyQCJDbiZ = false;}
      if(JGdhMSwlmM == true){JGdhMSwlmM = false;}
      if(DEUPfGJjxj == true){DEUPfGJjxj = false;}
      if(JcqDiJeSHm == true){JcqDiJeSHm = false;}
      if(IJXPpLrwQN == true){IJXPpLrwQN = false;}
      if(tJLBjYIhjw == true){tJLBjYIhjw = false;}
      if(zTezQfPZzC == true){zTezQfPZzC = false;}
      if(nceAEsfEYU == true){nceAEsfEYU = false;}
      if(NNSiozRoTK == true){NNSiozRoTK = false;}
      if(AwiLmoeYzK == true){AwiLmoeYzK = false;}
      if(uRxOZQeKwp == true){uRxOZQeKwp = false;}
      if(rEJOhlAuJQ == true){rEJOhlAuJQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BLOCFHJHJG
{ 
  void NBLkYCWkRj()
  { 
      bool dWRAohSiMK = false;
      bool UleZGzuLdU = false;
      bool olgLboQPpN = false;
      bool EPEDKdSybj = false;
      bool nOoPdRRxWF = false;
      bool dULMFqoFXz = false;
      bool QCrzFEhbPb = false;
      bool fwitfZwRgK = false;
      bool WTrkjjEqyS = false;
      bool oMabTkVpJY = false;
      bool iphtYgkQge = false;
      bool tWYMbxKHOU = false;
      bool ApdxmTVGat = false;
      bool EGIIaglyMD = false;
      bool zmKSXRnNAW = false;
      bool aOanYsMjGE = false;
      bool KdolanOPku = false;
      bool KLuLVMfKYV = false;
      bool fHGETpeTih = false;
      bool UBqHrUyYri = false;
      string RLQDULjERh;
      string NJFVejLPXW;
      string DPLaaPOzAA;
      string kmtGwLwnum;
      string jtcDPhSgpa;
      string RsHXDBAocF;
      string wkEQxZOyZT;
      string mWUkmImILr;
      string whJYhqfWDu;
      string LHLopypLFo;
      string STHWmuYWjt;
      string NrcjINbehF;
      string trudHeLetn;
      string SaCVZcallm;
      string SIlJgTdbfc;
      string WLdzuaYcOH;
      string iscwbloHKf;
      string mostmkFlxn;
      string BjyRRGxCZy;
      string DxXdEYfpgt;
      if(RLQDULjERh == STHWmuYWjt){dWRAohSiMK = true;}
      else if(STHWmuYWjt == RLQDULjERh){iphtYgkQge = true;}
      if(NJFVejLPXW == NrcjINbehF){UleZGzuLdU = true;}
      else if(NrcjINbehF == NJFVejLPXW){tWYMbxKHOU = true;}
      if(DPLaaPOzAA == trudHeLetn){olgLboQPpN = true;}
      else if(trudHeLetn == DPLaaPOzAA){ApdxmTVGat = true;}
      if(kmtGwLwnum == SaCVZcallm){EPEDKdSybj = true;}
      else if(SaCVZcallm == kmtGwLwnum){EGIIaglyMD = true;}
      if(jtcDPhSgpa == SIlJgTdbfc){nOoPdRRxWF = true;}
      else if(SIlJgTdbfc == jtcDPhSgpa){zmKSXRnNAW = true;}
      if(RsHXDBAocF == WLdzuaYcOH){dULMFqoFXz = true;}
      else if(WLdzuaYcOH == RsHXDBAocF){aOanYsMjGE = true;}
      if(wkEQxZOyZT == iscwbloHKf){QCrzFEhbPb = true;}
      else if(iscwbloHKf == wkEQxZOyZT){KdolanOPku = true;}
      if(mWUkmImILr == mostmkFlxn){fwitfZwRgK = true;}
      if(whJYhqfWDu == BjyRRGxCZy){WTrkjjEqyS = true;}
      if(LHLopypLFo == DxXdEYfpgt){oMabTkVpJY = true;}
      while(mostmkFlxn == mWUkmImILr){KLuLVMfKYV = true;}
      while(BjyRRGxCZy == BjyRRGxCZy){fHGETpeTih = true;}
      while(DxXdEYfpgt == DxXdEYfpgt){UBqHrUyYri = true;}
      if(dWRAohSiMK == true){dWRAohSiMK = false;}
      if(UleZGzuLdU == true){UleZGzuLdU = false;}
      if(olgLboQPpN == true){olgLboQPpN = false;}
      if(EPEDKdSybj == true){EPEDKdSybj = false;}
      if(nOoPdRRxWF == true){nOoPdRRxWF = false;}
      if(dULMFqoFXz == true){dULMFqoFXz = false;}
      if(QCrzFEhbPb == true){QCrzFEhbPb = false;}
      if(fwitfZwRgK == true){fwitfZwRgK = false;}
      if(WTrkjjEqyS == true){WTrkjjEqyS = false;}
      if(oMabTkVpJY == true){oMabTkVpJY = false;}
      if(iphtYgkQge == true){iphtYgkQge = false;}
      if(tWYMbxKHOU == true){tWYMbxKHOU = false;}
      if(ApdxmTVGat == true){ApdxmTVGat = false;}
      if(EGIIaglyMD == true){EGIIaglyMD = false;}
      if(zmKSXRnNAW == true){zmKSXRnNAW = false;}
      if(aOanYsMjGE == true){aOanYsMjGE = false;}
      if(KdolanOPku == true){KdolanOPku = false;}
      if(KLuLVMfKYV == true){KLuLVMfKYV = false;}
      if(fHGETpeTih == true){fHGETpeTih = false;}
      if(UBqHrUyYri == true){UBqHrUyYri = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CFVDJHOEFM
{ 
  void XzFadTByfh()
  { 
      bool SWZaWbWyQp = false;
      bool hNbKMhFuuW = false;
      bool wwDAfcncRr = false;
      bool lqRtIIsjWs = false;
      bool rdgDOllHgY = false;
      bool MqxajVSYut = false;
      bool ntgYDqwhCD = false;
      bool nUXCeSOAls = false;
      bool pguseuspJl = false;
      bool pUocExwIzW = false;
      bool pEFdjqSuwR = false;
      bool GSlBEGznsI = false;
      bool yFXPNTfuxg = false;
      bool VGBODkbQIm = false;
      bool bysrfWhnYy = false;
      bool yIOqYjfoQQ = false;
      bool LXxOuARXxS = false;
      bool eheGfAMfjp = false;
      bool lqVziNqJpS = false;
      bool ElzraEAewe = false;
      string DeDJnIQmsu;
      string kdQLMhFXPk;
      string BeTWRTxazQ;
      string kHCkBqHcmi;
      string kpebuoKtuT;
      string STfVFXKgqU;
      string LpncJdbfKU;
      string abkgzKAqac;
      string JCeexRbgec;
      string gZlSXtCBSR;
      string NejasqiyVt;
      string XTFNKJLIer;
      string CtAgnApSIE;
      string IyYIPdRElG;
      string hcKjFMTXHO;
      string isWaPSdDlr;
      string AQpQlYtxyf;
      string qGWXJYjPaa;
      string fSKtVObysx;
      string AORsGRmsyg;
      if(DeDJnIQmsu == NejasqiyVt){SWZaWbWyQp = true;}
      else if(NejasqiyVt == DeDJnIQmsu){pEFdjqSuwR = true;}
      if(kdQLMhFXPk == XTFNKJLIer){hNbKMhFuuW = true;}
      else if(XTFNKJLIer == kdQLMhFXPk){GSlBEGznsI = true;}
      if(BeTWRTxazQ == CtAgnApSIE){wwDAfcncRr = true;}
      else if(CtAgnApSIE == BeTWRTxazQ){yFXPNTfuxg = true;}
      if(kHCkBqHcmi == IyYIPdRElG){lqRtIIsjWs = true;}
      else if(IyYIPdRElG == kHCkBqHcmi){VGBODkbQIm = true;}
      if(kpebuoKtuT == hcKjFMTXHO){rdgDOllHgY = true;}
      else if(hcKjFMTXHO == kpebuoKtuT){bysrfWhnYy = true;}
      if(STfVFXKgqU == isWaPSdDlr){MqxajVSYut = true;}
      else if(isWaPSdDlr == STfVFXKgqU){yIOqYjfoQQ = true;}
      if(LpncJdbfKU == AQpQlYtxyf){ntgYDqwhCD = true;}
      else if(AQpQlYtxyf == LpncJdbfKU){LXxOuARXxS = true;}
      if(abkgzKAqac == qGWXJYjPaa){nUXCeSOAls = true;}
      if(JCeexRbgec == fSKtVObysx){pguseuspJl = true;}
      if(gZlSXtCBSR == AORsGRmsyg){pUocExwIzW = true;}
      while(qGWXJYjPaa == abkgzKAqac){eheGfAMfjp = true;}
      while(fSKtVObysx == fSKtVObysx){lqVziNqJpS = true;}
      while(AORsGRmsyg == AORsGRmsyg){ElzraEAewe = true;}
      if(SWZaWbWyQp == true){SWZaWbWyQp = false;}
      if(hNbKMhFuuW == true){hNbKMhFuuW = false;}
      if(wwDAfcncRr == true){wwDAfcncRr = false;}
      if(lqRtIIsjWs == true){lqRtIIsjWs = false;}
      if(rdgDOllHgY == true){rdgDOllHgY = false;}
      if(MqxajVSYut == true){MqxajVSYut = false;}
      if(ntgYDqwhCD == true){ntgYDqwhCD = false;}
      if(nUXCeSOAls == true){nUXCeSOAls = false;}
      if(pguseuspJl == true){pguseuspJl = false;}
      if(pUocExwIzW == true){pUocExwIzW = false;}
      if(pEFdjqSuwR == true){pEFdjqSuwR = false;}
      if(GSlBEGznsI == true){GSlBEGznsI = false;}
      if(yFXPNTfuxg == true){yFXPNTfuxg = false;}
      if(VGBODkbQIm == true){VGBODkbQIm = false;}
      if(bysrfWhnYy == true){bysrfWhnYy = false;}
      if(yIOqYjfoQQ == true){yIOqYjfoQQ = false;}
      if(LXxOuARXxS == true){LXxOuARXxS = false;}
      if(eheGfAMfjp == true){eheGfAMfjp = false;}
      if(lqVziNqJpS == true){lqVziNqJpS = false;}
      if(ElzraEAewe == true){ElzraEAewe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SGVLEPDICN
{ 
  void SimhSWsCqw()
  { 
      bool AcTOTuuwrK = false;
      bool zhbEqDWaxN = false;
      bool jBTHnUmeXM = false;
      bool PIFmCZcCwE = false;
      bool hgOELhHwdM = false;
      bool PWHuszILZy = false;
      bool IQXfuqbnCR = false;
      bool aTdreDmPwG = false;
      bool NpBKwsBKtD = false;
      bool QQcxwRIhJU = false;
      bool GStLlurPPp = false;
      bool LsPSkRONiB = false;
      bool oQtzAJqfuN = false;
      bool tEGbAtwoYA = false;
      bool AktEqXAJMd = false;
      bool DuzHeoYtLb = false;
      bool EMTCuGmnSp = false;
      bool VYohBDWpHc = false;
      bool IgSRKzFywK = false;
      bool VBdwwnRrIj = false;
      string ZarbPSFRxP;
      string PqFVORizNh;
      string iwEIiXGbes;
      string qtoVulTWdS;
      string NysoufwbxG;
      string tsaDDdVjsr;
      string MdmEXUCiZc;
      string yLUuUkCPNC;
      string adeXzyTlSR;
      string PickGiLoQZ;
      string dNBUIhXeiR;
      string aGWqRhyOEZ;
      string BQQIMOhjnk;
      string ZNymYMcJOQ;
      string ZnCAqJMlSY;
      string jwjqXNxsIt;
      string AnpxqNIiSE;
      string EoAnzNNPQD;
      string CwQPAdcGOK;
      string PjBUQlxEJc;
      if(ZarbPSFRxP == dNBUIhXeiR){AcTOTuuwrK = true;}
      else if(dNBUIhXeiR == ZarbPSFRxP){GStLlurPPp = true;}
      if(PqFVORizNh == aGWqRhyOEZ){zhbEqDWaxN = true;}
      else if(aGWqRhyOEZ == PqFVORizNh){LsPSkRONiB = true;}
      if(iwEIiXGbes == BQQIMOhjnk){jBTHnUmeXM = true;}
      else if(BQQIMOhjnk == iwEIiXGbes){oQtzAJqfuN = true;}
      if(qtoVulTWdS == ZNymYMcJOQ){PIFmCZcCwE = true;}
      else if(ZNymYMcJOQ == qtoVulTWdS){tEGbAtwoYA = true;}
      if(NysoufwbxG == ZnCAqJMlSY){hgOELhHwdM = true;}
      else if(ZnCAqJMlSY == NysoufwbxG){AktEqXAJMd = true;}
      if(tsaDDdVjsr == jwjqXNxsIt){PWHuszILZy = true;}
      else if(jwjqXNxsIt == tsaDDdVjsr){DuzHeoYtLb = true;}
      if(MdmEXUCiZc == AnpxqNIiSE){IQXfuqbnCR = true;}
      else if(AnpxqNIiSE == MdmEXUCiZc){EMTCuGmnSp = true;}
      if(yLUuUkCPNC == EoAnzNNPQD){aTdreDmPwG = true;}
      if(adeXzyTlSR == CwQPAdcGOK){NpBKwsBKtD = true;}
      if(PickGiLoQZ == PjBUQlxEJc){QQcxwRIhJU = true;}
      while(EoAnzNNPQD == yLUuUkCPNC){VYohBDWpHc = true;}
      while(CwQPAdcGOK == CwQPAdcGOK){IgSRKzFywK = true;}
      while(PjBUQlxEJc == PjBUQlxEJc){VBdwwnRrIj = true;}
      if(AcTOTuuwrK == true){AcTOTuuwrK = false;}
      if(zhbEqDWaxN == true){zhbEqDWaxN = false;}
      if(jBTHnUmeXM == true){jBTHnUmeXM = false;}
      if(PIFmCZcCwE == true){PIFmCZcCwE = false;}
      if(hgOELhHwdM == true){hgOELhHwdM = false;}
      if(PWHuszILZy == true){PWHuszILZy = false;}
      if(IQXfuqbnCR == true){IQXfuqbnCR = false;}
      if(aTdreDmPwG == true){aTdreDmPwG = false;}
      if(NpBKwsBKtD == true){NpBKwsBKtD = false;}
      if(QQcxwRIhJU == true){QQcxwRIhJU = false;}
      if(GStLlurPPp == true){GStLlurPPp = false;}
      if(LsPSkRONiB == true){LsPSkRONiB = false;}
      if(oQtzAJqfuN == true){oQtzAJqfuN = false;}
      if(tEGbAtwoYA == true){tEGbAtwoYA = false;}
      if(AktEqXAJMd == true){AktEqXAJMd = false;}
      if(DuzHeoYtLb == true){DuzHeoYtLb = false;}
      if(EMTCuGmnSp == true){EMTCuGmnSp = false;}
      if(VYohBDWpHc == true){VYohBDWpHc = false;}
      if(IgSRKzFywK == true){IgSRKzFywK = false;}
      if(VBdwwnRrIj == true){VBdwwnRrIj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFHBVKLYUX
{ 
  void IglLSncjlI()
  { 
      bool FZRXleKXgm = false;
      bool RtCPDXrfdm = false;
      bool XmrgNKDQeI = false;
      bool GFlycWPdfD = false;
      bool xqyonIttTw = false;
      bool efAtURhkKb = false;
      bool btsYgLIDmg = false;
      bool IOAapfoDrF = false;
      bool PIxhcZFrdK = false;
      bool neSDaDxZHc = false;
      bool zqHmmQeZDn = false;
      bool cerEMSwKuG = false;
      bool GPZbrduwzl = false;
      bool iOuPFXAKuM = false;
      bool tenohJlOqI = false;
      bool GleBVjRftJ = false;
      bool UhaRFNjbzn = false;
      bool RlPhLabjti = false;
      bool qgFpewjttV = false;
      bool GUPkrMEWjT = false;
      string hIZFeBygws;
      string lWinaNWtAA;
      string IZBDXTxJCC;
      string xlOEMmVihw;
      string GppDjkpqsk;
      string hwPiWIGWhK;
      string EndtwAHeam;
      string qnMEtSiySl;
      string cGPRTAVfgE;
      string gzAWrRLwHj;
      string dLPFssjKoD;
      string YIDuhxXMZu;
      string dbxWGrmpMb;
      string HlpiIRpJXa;
      string QKqdeXuFnt;
      string szWLGCOszA;
      string GsyMwmRUmQ;
      string HOnzeSjTqi;
      string xhBShIOecG;
      string CxKWTWMdgr;
      if(hIZFeBygws == dLPFssjKoD){FZRXleKXgm = true;}
      else if(dLPFssjKoD == hIZFeBygws){zqHmmQeZDn = true;}
      if(lWinaNWtAA == YIDuhxXMZu){RtCPDXrfdm = true;}
      else if(YIDuhxXMZu == lWinaNWtAA){cerEMSwKuG = true;}
      if(IZBDXTxJCC == dbxWGrmpMb){XmrgNKDQeI = true;}
      else if(dbxWGrmpMb == IZBDXTxJCC){GPZbrduwzl = true;}
      if(xlOEMmVihw == HlpiIRpJXa){GFlycWPdfD = true;}
      else if(HlpiIRpJXa == xlOEMmVihw){iOuPFXAKuM = true;}
      if(GppDjkpqsk == QKqdeXuFnt){xqyonIttTw = true;}
      else if(QKqdeXuFnt == GppDjkpqsk){tenohJlOqI = true;}
      if(hwPiWIGWhK == szWLGCOszA){efAtURhkKb = true;}
      else if(szWLGCOszA == hwPiWIGWhK){GleBVjRftJ = true;}
      if(EndtwAHeam == GsyMwmRUmQ){btsYgLIDmg = true;}
      else if(GsyMwmRUmQ == EndtwAHeam){UhaRFNjbzn = true;}
      if(qnMEtSiySl == HOnzeSjTqi){IOAapfoDrF = true;}
      if(cGPRTAVfgE == xhBShIOecG){PIxhcZFrdK = true;}
      if(gzAWrRLwHj == CxKWTWMdgr){neSDaDxZHc = true;}
      while(HOnzeSjTqi == qnMEtSiySl){RlPhLabjti = true;}
      while(xhBShIOecG == xhBShIOecG){qgFpewjttV = true;}
      while(CxKWTWMdgr == CxKWTWMdgr){GUPkrMEWjT = true;}
      if(FZRXleKXgm == true){FZRXleKXgm = false;}
      if(RtCPDXrfdm == true){RtCPDXrfdm = false;}
      if(XmrgNKDQeI == true){XmrgNKDQeI = false;}
      if(GFlycWPdfD == true){GFlycWPdfD = false;}
      if(xqyonIttTw == true){xqyonIttTw = false;}
      if(efAtURhkKb == true){efAtURhkKb = false;}
      if(btsYgLIDmg == true){btsYgLIDmg = false;}
      if(IOAapfoDrF == true){IOAapfoDrF = false;}
      if(PIxhcZFrdK == true){PIxhcZFrdK = false;}
      if(neSDaDxZHc == true){neSDaDxZHc = false;}
      if(zqHmmQeZDn == true){zqHmmQeZDn = false;}
      if(cerEMSwKuG == true){cerEMSwKuG = false;}
      if(GPZbrduwzl == true){GPZbrduwzl = false;}
      if(iOuPFXAKuM == true){iOuPFXAKuM = false;}
      if(tenohJlOqI == true){tenohJlOqI = false;}
      if(GleBVjRftJ == true){GleBVjRftJ = false;}
      if(UhaRFNjbzn == true){UhaRFNjbzn = false;}
      if(RlPhLabjti == true){RlPhLabjti = false;}
      if(qgFpewjttV == true){qgFpewjttV = false;}
      if(GUPkrMEWjT == true){GUPkrMEWjT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GHVYGAHSNF
{ 
  void CDkxPFYeRX()
  { 
      bool PCBPnnJfRo = false;
      bool NseHVpyJre = false;
      bool FDJnZJqmXF = false;
      bool TyGtSSzytn = false;
      bool LVkHtZSZQy = false;
      bool UJyATLrMod = false;
      bool wVIMVOlkoC = false;
      bool qAOESiSCtz = false;
      bool pRWZjJAGaH = false;
      bool alJPqpNYke = false;
      bool nhkOGTusgj = false;
      bool spSoneyhbM = false;
      bool NfKgaEqyNc = false;
      bool VsQOLIfHSP = false;
      bool OGYpOkTTbM = false;
      bool qewYQIXEmB = false;
      bool cwfDOzYDdf = false;
      bool yqPLxGGUSp = false;
      bool kWWBlpwrxC = false;
      bool kbTRmRaUaO = false;
      string KwyXZuNyRp;
      string SPbLsxdLlj;
      string jZFOznptsH;
      string VkncWOacmG;
      string frtPLgtpZr;
      string oGCPujqjYl;
      string ESEJThayod;
      string VBXeDrfoDR;
      string tzUASOiYhl;
      string XpDBBMnjuc;
      string GuBwWniWLD;
      string EBgGrFyEqE;
      string zCQCFexWdq;
      string EutZLyxYde;
      string fLMdhWJxIu;
      string OispcDezpq;
      string pMrUzIHGus;
      string HZZMYmplTh;
      string VANhbUCDxH;
      string TyhlnTTqeZ;
      if(KwyXZuNyRp == GuBwWniWLD){PCBPnnJfRo = true;}
      else if(GuBwWniWLD == KwyXZuNyRp){nhkOGTusgj = true;}
      if(SPbLsxdLlj == EBgGrFyEqE){NseHVpyJre = true;}
      else if(EBgGrFyEqE == SPbLsxdLlj){spSoneyhbM = true;}
      if(jZFOznptsH == zCQCFexWdq){FDJnZJqmXF = true;}
      else if(zCQCFexWdq == jZFOznptsH){NfKgaEqyNc = true;}
      if(VkncWOacmG == EutZLyxYde){TyGtSSzytn = true;}
      else if(EutZLyxYde == VkncWOacmG){VsQOLIfHSP = true;}
      if(frtPLgtpZr == fLMdhWJxIu){LVkHtZSZQy = true;}
      else if(fLMdhWJxIu == frtPLgtpZr){OGYpOkTTbM = true;}
      if(oGCPujqjYl == OispcDezpq){UJyATLrMod = true;}
      else if(OispcDezpq == oGCPujqjYl){qewYQIXEmB = true;}
      if(ESEJThayod == pMrUzIHGus){wVIMVOlkoC = true;}
      else if(pMrUzIHGus == ESEJThayod){cwfDOzYDdf = true;}
      if(VBXeDrfoDR == HZZMYmplTh){qAOESiSCtz = true;}
      if(tzUASOiYhl == VANhbUCDxH){pRWZjJAGaH = true;}
      if(XpDBBMnjuc == TyhlnTTqeZ){alJPqpNYke = true;}
      while(HZZMYmplTh == VBXeDrfoDR){yqPLxGGUSp = true;}
      while(VANhbUCDxH == VANhbUCDxH){kWWBlpwrxC = true;}
      while(TyhlnTTqeZ == TyhlnTTqeZ){kbTRmRaUaO = true;}
      if(PCBPnnJfRo == true){PCBPnnJfRo = false;}
      if(NseHVpyJre == true){NseHVpyJre = false;}
      if(FDJnZJqmXF == true){FDJnZJqmXF = false;}
      if(TyGtSSzytn == true){TyGtSSzytn = false;}
      if(LVkHtZSZQy == true){LVkHtZSZQy = false;}
      if(UJyATLrMod == true){UJyATLrMod = false;}
      if(wVIMVOlkoC == true){wVIMVOlkoC = false;}
      if(qAOESiSCtz == true){qAOESiSCtz = false;}
      if(pRWZjJAGaH == true){pRWZjJAGaH = false;}
      if(alJPqpNYke == true){alJPqpNYke = false;}
      if(nhkOGTusgj == true){nhkOGTusgj = false;}
      if(spSoneyhbM == true){spSoneyhbM = false;}
      if(NfKgaEqyNc == true){NfKgaEqyNc = false;}
      if(VsQOLIfHSP == true){VsQOLIfHSP = false;}
      if(OGYpOkTTbM == true){OGYpOkTTbM = false;}
      if(qewYQIXEmB == true){qewYQIXEmB = false;}
      if(cwfDOzYDdf == true){cwfDOzYDdf = false;}
      if(yqPLxGGUSp == true){yqPLxGGUSp = false;}
      if(kWWBlpwrxC == true){kWWBlpwrxC = false;}
      if(kbTRmRaUaO == true){kbTRmRaUaO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LHNDXAAIAB
{ 
  void YKihrGszHg()
  { 
      bool tlXgHxFjCI = false;
      bool mlCbeGaJsp = false;
      bool cWXSMXoGig = false;
      bool ZlDmozsSDr = false;
      bool GZlKEOSgOI = false;
      bool CiBuuWNFTj = false;
      bool IyAViBhOmf = false;
      bool NHFBiDkMNy = false;
      bool EHqZdpjHrR = false;
      bool lnzSiHYQbC = false;
      bool fDtiutdAMr = false;
      bool lAqVfBHaqs = false;
      bool RaWUsZIlRb = false;
      bool dTkLSANHdj = false;
      bool LjuAekwcmh = false;
      bool zxYhkEgYpV = false;
      bool lqhjNROfDe = false;
      bool nzwHghfWoH = false;
      bool ceyibguCZN = false;
      bool SnRIyTBLmN = false;
      string ZbfGqKTQlI;
      string BktsRpejTD;
      string KgmonUNfKn;
      string WXXJhHIYGb;
      string CZSLltntKP;
      string dyaWDsnpRW;
      string wnGxldNjKJ;
      string hGdrAjNaDt;
      string gSVtKYxBGo;
      string TRGjeOSUZH;
      string gEiAhWUiVS;
      string eNmXocSMlN;
      string gLcVoQztNl;
      string RrBuMbjULm;
      string DNemKGdhtB;
      string wFiMaUbNLR;
      string XaUjBlLrKN;
      string syAyJSgoLi;
      string lQzLpLJoTr;
      string AVJtPcsulX;
      if(ZbfGqKTQlI == gEiAhWUiVS){tlXgHxFjCI = true;}
      else if(gEiAhWUiVS == ZbfGqKTQlI){fDtiutdAMr = true;}
      if(BktsRpejTD == eNmXocSMlN){mlCbeGaJsp = true;}
      else if(eNmXocSMlN == BktsRpejTD){lAqVfBHaqs = true;}
      if(KgmonUNfKn == gLcVoQztNl){cWXSMXoGig = true;}
      else if(gLcVoQztNl == KgmonUNfKn){RaWUsZIlRb = true;}
      if(WXXJhHIYGb == RrBuMbjULm){ZlDmozsSDr = true;}
      else if(RrBuMbjULm == WXXJhHIYGb){dTkLSANHdj = true;}
      if(CZSLltntKP == DNemKGdhtB){GZlKEOSgOI = true;}
      else if(DNemKGdhtB == CZSLltntKP){LjuAekwcmh = true;}
      if(dyaWDsnpRW == wFiMaUbNLR){CiBuuWNFTj = true;}
      else if(wFiMaUbNLR == dyaWDsnpRW){zxYhkEgYpV = true;}
      if(wnGxldNjKJ == XaUjBlLrKN){IyAViBhOmf = true;}
      else if(XaUjBlLrKN == wnGxldNjKJ){lqhjNROfDe = true;}
      if(hGdrAjNaDt == syAyJSgoLi){NHFBiDkMNy = true;}
      if(gSVtKYxBGo == lQzLpLJoTr){EHqZdpjHrR = true;}
      if(TRGjeOSUZH == AVJtPcsulX){lnzSiHYQbC = true;}
      while(syAyJSgoLi == hGdrAjNaDt){nzwHghfWoH = true;}
      while(lQzLpLJoTr == lQzLpLJoTr){ceyibguCZN = true;}
      while(AVJtPcsulX == AVJtPcsulX){SnRIyTBLmN = true;}
      if(tlXgHxFjCI == true){tlXgHxFjCI = false;}
      if(mlCbeGaJsp == true){mlCbeGaJsp = false;}
      if(cWXSMXoGig == true){cWXSMXoGig = false;}
      if(ZlDmozsSDr == true){ZlDmozsSDr = false;}
      if(GZlKEOSgOI == true){GZlKEOSgOI = false;}
      if(CiBuuWNFTj == true){CiBuuWNFTj = false;}
      if(IyAViBhOmf == true){IyAViBhOmf = false;}
      if(NHFBiDkMNy == true){NHFBiDkMNy = false;}
      if(EHqZdpjHrR == true){EHqZdpjHrR = false;}
      if(lnzSiHYQbC == true){lnzSiHYQbC = false;}
      if(fDtiutdAMr == true){fDtiutdAMr = false;}
      if(lAqVfBHaqs == true){lAqVfBHaqs = false;}
      if(RaWUsZIlRb == true){RaWUsZIlRb = false;}
      if(dTkLSANHdj == true){dTkLSANHdj = false;}
      if(LjuAekwcmh == true){LjuAekwcmh = false;}
      if(zxYhkEgYpV == true){zxYhkEgYpV = false;}
      if(lqhjNROfDe == true){lqhjNROfDe = false;}
      if(nzwHghfWoH == true){nzwHghfWoH = false;}
      if(ceyibguCZN == true){ceyibguCZN = false;}
      if(SnRIyTBLmN == true){SnRIyTBLmN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class THCMTOAAZO
{ 
  void RXslpkEPwj()
  { 
      bool pnVePbOCtX = false;
      bool hTdpPPtPxf = false;
      bool rYmXyHwdta = false;
      bool EVBaDttjOR = false;
      bool goaiEMxQNs = false;
      bool BluYzRAxfH = false;
      bool ekHSSMRClU = false;
      bool VKBeyCxDTk = false;
      bool JePBYSZcbk = false;
      bool swDGlwhHQr = false;
      bool tudsWqkPZw = false;
      bool TwdtyAUGtz = false;
      bool loaBbYHtsC = false;
      bool UombpOAWdh = false;
      bool hJCeQwRIIl = false;
      bool abNQFFTcQx = false;
      bool ipWWbdJCEi = false;
      bool zybLRbmwje = false;
      bool HykGarbWVk = false;
      bool uXFfyqmeCm = false;
      string nMXoAjUFZI;
      string EGGxjqSXPW;
      string zHuYRtMUhP;
      string qfLrqkMxCd;
      string YcJMGoaxOr;
      string yDJMRfRyWF;
      string XAXKRYuNFz;
      string eVUkxWxiSc;
      string TPGoRnVyaK;
      string TNZwGYEzug;
      string sMqPNbhYPt;
      string ihftlHthsc;
      string DxmteQwYdY;
      string RymkiGXpao;
      string FwigbkhfKz;
      string eWGRdwZwjx;
      string fJupbjttKe;
      string iDHDXGNGSt;
      string hPOesurVGm;
      string gbGcJwBrEq;
      if(nMXoAjUFZI == sMqPNbhYPt){pnVePbOCtX = true;}
      else if(sMqPNbhYPt == nMXoAjUFZI){tudsWqkPZw = true;}
      if(EGGxjqSXPW == ihftlHthsc){hTdpPPtPxf = true;}
      else if(ihftlHthsc == EGGxjqSXPW){TwdtyAUGtz = true;}
      if(zHuYRtMUhP == DxmteQwYdY){rYmXyHwdta = true;}
      else if(DxmteQwYdY == zHuYRtMUhP){loaBbYHtsC = true;}
      if(qfLrqkMxCd == RymkiGXpao){EVBaDttjOR = true;}
      else if(RymkiGXpao == qfLrqkMxCd){UombpOAWdh = true;}
      if(YcJMGoaxOr == FwigbkhfKz){goaiEMxQNs = true;}
      else if(FwigbkhfKz == YcJMGoaxOr){hJCeQwRIIl = true;}
      if(yDJMRfRyWF == eWGRdwZwjx){BluYzRAxfH = true;}
      else if(eWGRdwZwjx == yDJMRfRyWF){abNQFFTcQx = true;}
      if(XAXKRYuNFz == fJupbjttKe){ekHSSMRClU = true;}
      else if(fJupbjttKe == XAXKRYuNFz){ipWWbdJCEi = true;}
      if(eVUkxWxiSc == iDHDXGNGSt){VKBeyCxDTk = true;}
      if(TPGoRnVyaK == hPOesurVGm){JePBYSZcbk = true;}
      if(TNZwGYEzug == gbGcJwBrEq){swDGlwhHQr = true;}
      while(iDHDXGNGSt == eVUkxWxiSc){zybLRbmwje = true;}
      while(hPOesurVGm == hPOesurVGm){HykGarbWVk = true;}
      while(gbGcJwBrEq == gbGcJwBrEq){uXFfyqmeCm = true;}
      if(pnVePbOCtX == true){pnVePbOCtX = false;}
      if(hTdpPPtPxf == true){hTdpPPtPxf = false;}
      if(rYmXyHwdta == true){rYmXyHwdta = false;}
      if(EVBaDttjOR == true){EVBaDttjOR = false;}
      if(goaiEMxQNs == true){goaiEMxQNs = false;}
      if(BluYzRAxfH == true){BluYzRAxfH = false;}
      if(ekHSSMRClU == true){ekHSSMRClU = false;}
      if(VKBeyCxDTk == true){VKBeyCxDTk = false;}
      if(JePBYSZcbk == true){JePBYSZcbk = false;}
      if(swDGlwhHQr == true){swDGlwhHQr = false;}
      if(tudsWqkPZw == true){tudsWqkPZw = false;}
      if(TwdtyAUGtz == true){TwdtyAUGtz = false;}
      if(loaBbYHtsC == true){loaBbYHtsC = false;}
      if(UombpOAWdh == true){UombpOAWdh = false;}
      if(hJCeQwRIIl == true){hJCeQwRIIl = false;}
      if(abNQFFTcQx == true){abNQFFTcQx = false;}
      if(ipWWbdJCEi == true){ipWWbdJCEi = false;}
      if(zybLRbmwje == true){zybLRbmwje = false;}
      if(HykGarbWVk == true){HykGarbWVk = false;}
      if(uXFfyqmeCm == true){uXFfyqmeCm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JZGFAOHFJE
{ 
  void PKHSmasewE()
  { 
      bool oYmbBHBzVD = false;
      bool lYQoqebEIq = false;
      bool opcqVFbJqt = false;
      bool qIRjHKkUEY = false;
      bool qlNaAOAyLE = false;
      bool EMDuAyuuGw = false;
      bool frIaLdGfgg = false;
      bool sGAiADcCpG = false;
      bool EcympeEWiI = false;
      bool OpOHsycmOW = false;
      bool ITQdKxMUux = false;
      bool VrFzqCtVjg = false;
      bool YjxYRDrrpB = false;
      bool ZpnTykLTbr = false;
      bool SjalmWkOQq = false;
      bool EHChyYVrMG = false;
      bool EUdtWfEkBG = false;
      bool pasqNnILkt = false;
      bool ScazxSmGVZ = false;
      bool OTGVmyGgOH = false;
      string WxaXRjGQBN;
      string geEmMPVIur;
      string WjimYSSuGG;
      string SgKOqiTpLR;
      string YMiYxyucZl;
      string ZEROAmOnzy;
      string RKJtuATpud;
      string ufwdTJAJoZ;
      string WoUTgNPwNE;
      string TfpNANDndx;
      string eFhuqsIntq;
      string mFzYacooNg;
      string kWbqKPoicF;
      string GLfquRHYcm;
      string FbBWQOgQlW;
      string XNZwMHdpka;
      string DYKojaYHdJ;
      string VQLaaIUEZw;
      string iXxFgskidm;
      string nQnCifQMmp;
      if(WxaXRjGQBN == eFhuqsIntq){oYmbBHBzVD = true;}
      else if(eFhuqsIntq == WxaXRjGQBN){ITQdKxMUux = true;}
      if(geEmMPVIur == mFzYacooNg){lYQoqebEIq = true;}
      else if(mFzYacooNg == geEmMPVIur){VrFzqCtVjg = true;}
      if(WjimYSSuGG == kWbqKPoicF){opcqVFbJqt = true;}
      else if(kWbqKPoicF == WjimYSSuGG){YjxYRDrrpB = true;}
      if(SgKOqiTpLR == GLfquRHYcm){qIRjHKkUEY = true;}
      else if(GLfquRHYcm == SgKOqiTpLR){ZpnTykLTbr = true;}
      if(YMiYxyucZl == FbBWQOgQlW){qlNaAOAyLE = true;}
      else if(FbBWQOgQlW == YMiYxyucZl){SjalmWkOQq = true;}
      if(ZEROAmOnzy == XNZwMHdpka){EMDuAyuuGw = true;}
      else if(XNZwMHdpka == ZEROAmOnzy){EHChyYVrMG = true;}
      if(RKJtuATpud == DYKojaYHdJ){frIaLdGfgg = true;}
      else if(DYKojaYHdJ == RKJtuATpud){EUdtWfEkBG = true;}
      if(ufwdTJAJoZ == VQLaaIUEZw){sGAiADcCpG = true;}
      if(WoUTgNPwNE == iXxFgskidm){EcympeEWiI = true;}
      if(TfpNANDndx == nQnCifQMmp){OpOHsycmOW = true;}
      while(VQLaaIUEZw == ufwdTJAJoZ){pasqNnILkt = true;}
      while(iXxFgskidm == iXxFgskidm){ScazxSmGVZ = true;}
      while(nQnCifQMmp == nQnCifQMmp){OTGVmyGgOH = true;}
      if(oYmbBHBzVD == true){oYmbBHBzVD = false;}
      if(lYQoqebEIq == true){lYQoqebEIq = false;}
      if(opcqVFbJqt == true){opcqVFbJqt = false;}
      if(qIRjHKkUEY == true){qIRjHKkUEY = false;}
      if(qlNaAOAyLE == true){qlNaAOAyLE = false;}
      if(EMDuAyuuGw == true){EMDuAyuuGw = false;}
      if(frIaLdGfgg == true){frIaLdGfgg = false;}
      if(sGAiADcCpG == true){sGAiADcCpG = false;}
      if(EcympeEWiI == true){EcympeEWiI = false;}
      if(OpOHsycmOW == true){OpOHsycmOW = false;}
      if(ITQdKxMUux == true){ITQdKxMUux = false;}
      if(VrFzqCtVjg == true){VrFzqCtVjg = false;}
      if(YjxYRDrrpB == true){YjxYRDrrpB = false;}
      if(ZpnTykLTbr == true){ZpnTykLTbr = false;}
      if(SjalmWkOQq == true){SjalmWkOQq = false;}
      if(EHChyYVrMG == true){EHChyYVrMG = false;}
      if(EUdtWfEkBG == true){EUdtWfEkBG = false;}
      if(pasqNnILkt == true){pasqNnILkt = false;}
      if(ScazxSmGVZ == true){ScazxSmGVZ = false;}
      if(OTGVmyGgOH == true){OTGVmyGgOH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MVMABSPMQW
{ 
  void yrLsDrOCZG()
  { 
      bool qyhCUKnFoL = false;
      bool BOwwpMfdao = false;
      bool XEpBmSHtrX = false;
      bool IqcTSSqCgy = false;
      bool hpjYrIOVSF = false;
      bool COSxsmHgOC = false;
      bool DsMRCKlccW = false;
      bool UdwcHhURJd = false;
      bool DkbmVtXeZf = false;
      bool KKmeuncSVh = false;
      bool WlswjXRopL = false;
      bool SpWkyRRZuI = false;
      bool lGDxLKqRhS = false;
      bool EBuaHRrfCx = false;
      bool bioNNUmCfc = false;
      bool WDWNwPhwjZ = false;
      bool gAHWHQuwcf = false;
      bool ZkXxgDRpjq = false;
      bool WnkEwBdheq = false;
      bool iwubPaaSFw = false;
      string UyALzRIWHX;
      string ogTmLfUpTT;
      string SqIxDktzqt;
      string ZKKcwKxMrt;
      string rquRPWlume;
      string yCGECcpDHN;
      string WJfNxdVqpA;
      string iHxYaauphg;
      string yyLLwXEGaT;
      string UsEdXhLhUk;
      string BuFlwpEgca;
      string gzVaOXyTQY;
      string YOPWfoDTBr;
      string OMUwfDsYPF;
      string SXdzlVXcOz;
      string jrQuMlehGH;
      string mkejMTdZuL;
      string dZDLGBkPkK;
      string QZEBIWwZjs;
      string XLRIShrtmR;
      if(UyALzRIWHX == BuFlwpEgca){qyhCUKnFoL = true;}
      else if(BuFlwpEgca == UyALzRIWHX){WlswjXRopL = true;}
      if(ogTmLfUpTT == gzVaOXyTQY){BOwwpMfdao = true;}
      else if(gzVaOXyTQY == ogTmLfUpTT){SpWkyRRZuI = true;}
      if(SqIxDktzqt == YOPWfoDTBr){XEpBmSHtrX = true;}
      else if(YOPWfoDTBr == SqIxDktzqt){lGDxLKqRhS = true;}
      if(ZKKcwKxMrt == OMUwfDsYPF){IqcTSSqCgy = true;}
      else if(OMUwfDsYPF == ZKKcwKxMrt){EBuaHRrfCx = true;}
      if(rquRPWlume == SXdzlVXcOz){hpjYrIOVSF = true;}
      else if(SXdzlVXcOz == rquRPWlume){bioNNUmCfc = true;}
      if(yCGECcpDHN == jrQuMlehGH){COSxsmHgOC = true;}
      else if(jrQuMlehGH == yCGECcpDHN){WDWNwPhwjZ = true;}
      if(WJfNxdVqpA == mkejMTdZuL){DsMRCKlccW = true;}
      else if(mkejMTdZuL == WJfNxdVqpA){gAHWHQuwcf = true;}
      if(iHxYaauphg == dZDLGBkPkK){UdwcHhURJd = true;}
      if(yyLLwXEGaT == QZEBIWwZjs){DkbmVtXeZf = true;}
      if(UsEdXhLhUk == XLRIShrtmR){KKmeuncSVh = true;}
      while(dZDLGBkPkK == iHxYaauphg){ZkXxgDRpjq = true;}
      while(QZEBIWwZjs == QZEBIWwZjs){WnkEwBdheq = true;}
      while(XLRIShrtmR == XLRIShrtmR){iwubPaaSFw = true;}
      if(qyhCUKnFoL == true){qyhCUKnFoL = false;}
      if(BOwwpMfdao == true){BOwwpMfdao = false;}
      if(XEpBmSHtrX == true){XEpBmSHtrX = false;}
      if(IqcTSSqCgy == true){IqcTSSqCgy = false;}
      if(hpjYrIOVSF == true){hpjYrIOVSF = false;}
      if(COSxsmHgOC == true){COSxsmHgOC = false;}
      if(DsMRCKlccW == true){DsMRCKlccW = false;}
      if(UdwcHhURJd == true){UdwcHhURJd = false;}
      if(DkbmVtXeZf == true){DkbmVtXeZf = false;}
      if(KKmeuncSVh == true){KKmeuncSVh = false;}
      if(WlswjXRopL == true){WlswjXRopL = false;}
      if(SpWkyRRZuI == true){SpWkyRRZuI = false;}
      if(lGDxLKqRhS == true){lGDxLKqRhS = false;}
      if(EBuaHRrfCx == true){EBuaHRrfCx = false;}
      if(bioNNUmCfc == true){bioNNUmCfc = false;}
      if(WDWNwPhwjZ == true){WDWNwPhwjZ = false;}
      if(gAHWHQuwcf == true){gAHWHQuwcf = false;}
      if(ZkXxgDRpjq == true){ZkXxgDRpjq = false;}
      if(WnkEwBdheq == true){WnkEwBdheq = false;}
      if(iwubPaaSFw == true){iwubPaaSFw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HCIYAYCOJJ
{ 
  void xLKrkWPueT()
  { 
      bool mOOikjGwgp = false;
      bool yBeNXmQlwN = false;
      bool PaWdBuSJzq = false;
      bool HqiJpmgTfd = false;
      bool yeDkpfEbTK = false;
      bool TMlZkLrjhp = false;
      bool QwwohGRVWk = false;
      bool FxFSPkXkmU = false;
      bool pqpoWuFJXe = false;
      bool uwkoMBhNDj = false;
      bool OiEiEWGTKA = false;
      bool nGxNzZFHSm = false;
      bool BIxroJLPFN = false;
      bool DJhDGHlHkA = false;
      bool nkyXqnzXom = false;
      bool uauQhGkLsu = false;
      bool KpNxwdYsHr = false;
      bool myVSyPJYBA = false;
      bool JnZSRcORUz = false;
      bool VaNpoyXBaM = false;
      string pmaVYBtgRo;
      string XEUUUjrkzW;
      string wkzbhZaACu;
      string ObXGKpiBHw;
      string dGsQzaQFyr;
      string CToLUEmyny;
      string asdVaugOKe;
      string BpdDroribH;
      string IVBJrtmMkF;
      string CjNIVkcWoE;
      string sCuTqLokSe;
      string MEWfpEqUdg;
      string HUcEbQcVhH;
      string MUsXNGZhSf;
      string EBsFsyNgSQ;
      string sIsIwYYpqa;
      string iTDKRqLySi;
      string eJBxbGaWLd;
      string CuDRNEajbn;
      string hjpqxkyimB;
      if(pmaVYBtgRo == sCuTqLokSe){mOOikjGwgp = true;}
      else if(sCuTqLokSe == pmaVYBtgRo){OiEiEWGTKA = true;}
      if(XEUUUjrkzW == MEWfpEqUdg){yBeNXmQlwN = true;}
      else if(MEWfpEqUdg == XEUUUjrkzW){nGxNzZFHSm = true;}
      if(wkzbhZaACu == HUcEbQcVhH){PaWdBuSJzq = true;}
      else if(HUcEbQcVhH == wkzbhZaACu){BIxroJLPFN = true;}
      if(ObXGKpiBHw == MUsXNGZhSf){HqiJpmgTfd = true;}
      else if(MUsXNGZhSf == ObXGKpiBHw){DJhDGHlHkA = true;}
      if(dGsQzaQFyr == EBsFsyNgSQ){yeDkpfEbTK = true;}
      else if(EBsFsyNgSQ == dGsQzaQFyr){nkyXqnzXom = true;}
      if(CToLUEmyny == sIsIwYYpqa){TMlZkLrjhp = true;}
      else if(sIsIwYYpqa == CToLUEmyny){uauQhGkLsu = true;}
      if(asdVaugOKe == iTDKRqLySi){QwwohGRVWk = true;}
      else if(iTDKRqLySi == asdVaugOKe){KpNxwdYsHr = true;}
      if(BpdDroribH == eJBxbGaWLd){FxFSPkXkmU = true;}
      if(IVBJrtmMkF == CuDRNEajbn){pqpoWuFJXe = true;}
      if(CjNIVkcWoE == hjpqxkyimB){uwkoMBhNDj = true;}
      while(eJBxbGaWLd == BpdDroribH){myVSyPJYBA = true;}
      while(CuDRNEajbn == CuDRNEajbn){JnZSRcORUz = true;}
      while(hjpqxkyimB == hjpqxkyimB){VaNpoyXBaM = true;}
      if(mOOikjGwgp == true){mOOikjGwgp = false;}
      if(yBeNXmQlwN == true){yBeNXmQlwN = false;}
      if(PaWdBuSJzq == true){PaWdBuSJzq = false;}
      if(HqiJpmgTfd == true){HqiJpmgTfd = false;}
      if(yeDkpfEbTK == true){yeDkpfEbTK = false;}
      if(TMlZkLrjhp == true){TMlZkLrjhp = false;}
      if(QwwohGRVWk == true){QwwohGRVWk = false;}
      if(FxFSPkXkmU == true){FxFSPkXkmU = false;}
      if(pqpoWuFJXe == true){pqpoWuFJXe = false;}
      if(uwkoMBhNDj == true){uwkoMBhNDj = false;}
      if(OiEiEWGTKA == true){OiEiEWGTKA = false;}
      if(nGxNzZFHSm == true){nGxNzZFHSm = false;}
      if(BIxroJLPFN == true){BIxroJLPFN = false;}
      if(DJhDGHlHkA == true){DJhDGHlHkA = false;}
      if(nkyXqnzXom == true){nkyXqnzXom = false;}
      if(uauQhGkLsu == true){uauQhGkLsu = false;}
      if(KpNxwdYsHr == true){KpNxwdYsHr = false;}
      if(myVSyPJYBA == true){myVSyPJYBA = false;}
      if(JnZSRcORUz == true){JnZSRcORUz = false;}
      if(VaNpoyXBaM == true){VaNpoyXBaM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WMWVCIDBJY
{ 
  void rigZySWTgQ()
  { 
      bool WtCgrDVwwk = false;
      bool qAtHEHHYXJ = false;
      bool gXPowFEUsJ = false;
      bool zlEnxySVcg = false;
      bool nPFMTayAIr = false;
      bool mToUhzdNkm = false;
      bool zBCmlFuFKF = false;
      bool nlwpURSCUU = false;
      bool GELBVexjFx = false;
      bool TFkphmMRaO = false;
      bool esoDDBXyzQ = false;
      bool fbsPfuoBRH = false;
      bool ILzMkiBFIh = false;
      bool FBbGoNOIxU = false;
      bool HyjoQrLUJl = false;
      bool xKzTFTscRU = false;
      bool zSpRKezlaS = false;
      bool gfEwAJaJur = false;
      bool WguVjtBIAU = false;
      bool TlqbVnIRdk = false;
      string VxJkddpLLS;
      string gHsSLiwBbA;
      string ITFdXOgQKL;
      string lCGbDSgSEf;
      string lxJqoLiblB;
      string fOFZtCqfNP;
      string wZBAgdBQOs;
      string CdwwOKJNnL;
      string eFdJeWxghB;
      string aAEoiMwJKL;
      string KSMsyCRIKi;
      string rcqBjqwrUJ;
      string gThNRBYHNB;
      string OzDcBMrjKc;
      string FnVyIxIDEq;
      string QEnBdpjzbx;
      string cKuJTrZOAX;
      string zMhrEryjET;
      string sVCVkKLCyL;
      string bsHMzusMeP;
      if(VxJkddpLLS == KSMsyCRIKi){WtCgrDVwwk = true;}
      else if(KSMsyCRIKi == VxJkddpLLS){esoDDBXyzQ = true;}
      if(gHsSLiwBbA == rcqBjqwrUJ){qAtHEHHYXJ = true;}
      else if(rcqBjqwrUJ == gHsSLiwBbA){fbsPfuoBRH = true;}
      if(ITFdXOgQKL == gThNRBYHNB){gXPowFEUsJ = true;}
      else if(gThNRBYHNB == ITFdXOgQKL){ILzMkiBFIh = true;}
      if(lCGbDSgSEf == OzDcBMrjKc){zlEnxySVcg = true;}
      else if(OzDcBMrjKc == lCGbDSgSEf){FBbGoNOIxU = true;}
      if(lxJqoLiblB == FnVyIxIDEq){nPFMTayAIr = true;}
      else if(FnVyIxIDEq == lxJqoLiblB){HyjoQrLUJl = true;}
      if(fOFZtCqfNP == QEnBdpjzbx){mToUhzdNkm = true;}
      else if(QEnBdpjzbx == fOFZtCqfNP){xKzTFTscRU = true;}
      if(wZBAgdBQOs == cKuJTrZOAX){zBCmlFuFKF = true;}
      else if(cKuJTrZOAX == wZBAgdBQOs){zSpRKezlaS = true;}
      if(CdwwOKJNnL == zMhrEryjET){nlwpURSCUU = true;}
      if(eFdJeWxghB == sVCVkKLCyL){GELBVexjFx = true;}
      if(aAEoiMwJKL == bsHMzusMeP){TFkphmMRaO = true;}
      while(zMhrEryjET == CdwwOKJNnL){gfEwAJaJur = true;}
      while(sVCVkKLCyL == sVCVkKLCyL){WguVjtBIAU = true;}
      while(bsHMzusMeP == bsHMzusMeP){TlqbVnIRdk = true;}
      if(WtCgrDVwwk == true){WtCgrDVwwk = false;}
      if(qAtHEHHYXJ == true){qAtHEHHYXJ = false;}
      if(gXPowFEUsJ == true){gXPowFEUsJ = false;}
      if(zlEnxySVcg == true){zlEnxySVcg = false;}
      if(nPFMTayAIr == true){nPFMTayAIr = false;}
      if(mToUhzdNkm == true){mToUhzdNkm = false;}
      if(zBCmlFuFKF == true){zBCmlFuFKF = false;}
      if(nlwpURSCUU == true){nlwpURSCUU = false;}
      if(GELBVexjFx == true){GELBVexjFx = false;}
      if(TFkphmMRaO == true){TFkphmMRaO = false;}
      if(esoDDBXyzQ == true){esoDDBXyzQ = false;}
      if(fbsPfuoBRH == true){fbsPfuoBRH = false;}
      if(ILzMkiBFIh == true){ILzMkiBFIh = false;}
      if(FBbGoNOIxU == true){FBbGoNOIxU = false;}
      if(HyjoQrLUJl == true){HyjoQrLUJl = false;}
      if(xKzTFTscRU == true){xKzTFTscRU = false;}
      if(zSpRKezlaS == true){zSpRKezlaS = false;}
      if(gfEwAJaJur == true){gfEwAJaJur = false;}
      if(WguVjtBIAU == true){WguVjtBIAU = false;}
      if(TlqbVnIRdk == true){TlqbVnIRdk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WSYAWEVOZO
{ 
  void HiBLmzDTrC()
  { 
      bool FyFWumBoYI = false;
      bool NVYmIqjItN = false;
      bool oykmoOCquG = false;
      bool xUjbRauQrz = false;
      bool moBDDgusAZ = false;
      bool cgmLnHMRgg = false;
      bool kKsRLrlwUh = false;
      bool uSQtaAwgjH = false;
      bool SIpVdPgXnK = false;
      bool NciKObujqK = false;
      bool uzXSdJQrjn = false;
      bool KfhYNcUXnu = false;
      bool KNHKUSjFez = false;
      bool EMoYMSjXqU = false;
      bool znmzzhtJxl = false;
      bool GXuwAgqNyL = false;
      bool ZLMkjypJMu = false;
      bool rxfTwVZILl = false;
      bool XZIsrgQsYe = false;
      bool aWYfunbCPB = false;
      string MirMIjEIJy;
      string JTPBtBDOGX;
      string WJcNOeTeUa;
      string gnyFAZfuUc;
      string UiGNmBckdY;
      string MUpthCFeyd;
      string QZniQUVKBU;
      string VIscDmDPZM;
      string CiAuNLyEXx;
      string TAwqLuuWxR;
      string fSiJDEaMpt;
      string zpEkbhYrVE;
      string WQmEAULCQI;
      string qfSHgizprI;
      string kkOcxcuKOd;
      string VCBruPfeJh;
      string rXugCTXxEr;
      string iiAMTlCJGW;
      string YBmmmodZMQ;
      string DTfJQMogZd;
      if(MirMIjEIJy == fSiJDEaMpt){FyFWumBoYI = true;}
      else if(fSiJDEaMpt == MirMIjEIJy){uzXSdJQrjn = true;}
      if(JTPBtBDOGX == zpEkbhYrVE){NVYmIqjItN = true;}
      else if(zpEkbhYrVE == JTPBtBDOGX){KfhYNcUXnu = true;}
      if(WJcNOeTeUa == WQmEAULCQI){oykmoOCquG = true;}
      else if(WQmEAULCQI == WJcNOeTeUa){KNHKUSjFez = true;}
      if(gnyFAZfuUc == qfSHgizprI){xUjbRauQrz = true;}
      else if(qfSHgizprI == gnyFAZfuUc){EMoYMSjXqU = true;}
      if(UiGNmBckdY == kkOcxcuKOd){moBDDgusAZ = true;}
      else if(kkOcxcuKOd == UiGNmBckdY){znmzzhtJxl = true;}
      if(MUpthCFeyd == VCBruPfeJh){cgmLnHMRgg = true;}
      else if(VCBruPfeJh == MUpthCFeyd){GXuwAgqNyL = true;}
      if(QZniQUVKBU == rXugCTXxEr){kKsRLrlwUh = true;}
      else if(rXugCTXxEr == QZniQUVKBU){ZLMkjypJMu = true;}
      if(VIscDmDPZM == iiAMTlCJGW){uSQtaAwgjH = true;}
      if(CiAuNLyEXx == YBmmmodZMQ){SIpVdPgXnK = true;}
      if(TAwqLuuWxR == DTfJQMogZd){NciKObujqK = true;}
      while(iiAMTlCJGW == VIscDmDPZM){rxfTwVZILl = true;}
      while(YBmmmodZMQ == YBmmmodZMQ){XZIsrgQsYe = true;}
      while(DTfJQMogZd == DTfJQMogZd){aWYfunbCPB = true;}
      if(FyFWumBoYI == true){FyFWumBoYI = false;}
      if(NVYmIqjItN == true){NVYmIqjItN = false;}
      if(oykmoOCquG == true){oykmoOCquG = false;}
      if(xUjbRauQrz == true){xUjbRauQrz = false;}
      if(moBDDgusAZ == true){moBDDgusAZ = false;}
      if(cgmLnHMRgg == true){cgmLnHMRgg = false;}
      if(kKsRLrlwUh == true){kKsRLrlwUh = false;}
      if(uSQtaAwgjH == true){uSQtaAwgjH = false;}
      if(SIpVdPgXnK == true){SIpVdPgXnK = false;}
      if(NciKObujqK == true){NciKObujqK = false;}
      if(uzXSdJQrjn == true){uzXSdJQrjn = false;}
      if(KfhYNcUXnu == true){KfhYNcUXnu = false;}
      if(KNHKUSjFez == true){KNHKUSjFez = false;}
      if(EMoYMSjXqU == true){EMoYMSjXqU = false;}
      if(znmzzhtJxl == true){znmzzhtJxl = false;}
      if(GXuwAgqNyL == true){GXuwAgqNyL = false;}
      if(ZLMkjypJMu == true){ZLMkjypJMu = false;}
      if(rxfTwVZILl == true){rxfTwVZILl = false;}
      if(XZIsrgQsYe == true){XZIsrgQsYe = false;}
      if(aWYfunbCPB == true){aWYfunbCPB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SKWTGBHNIR
{ 
  void ujHcIpOnYn()
  { 
      bool lgdrIFcYxb = false;
      bool IaZicJeFAh = false;
      bool IWqEMPBwCn = false;
      bool eDJwmFwarp = false;
      bool weSefYAqce = false;
      bool IgAxzPpYfr = false;
      bool DfWJwERcuW = false;
      bool MENJkcDLYn = false;
      bool PKSWeyCLwW = false;
      bool PWuzlQIJha = false;
      bool GWuGRESpLV = false;
      bool MdArbsNzdy = false;
      bool BFgYHpINWU = false;
      bool UsdygrOMFZ = false;
      bool eMzZJkWDWr = false;
      bool CIejYApVyb = false;
      bool uFSqASzCKj = false;
      bool eAsDToFGOV = false;
      bool TFpeRMNtYf = false;
      bool BsNdeZsIZq = false;
      string cGeIFhDMIG;
      string FkqIPkhOkK;
      string jwwXAXhCkq;
      string guNQiNmWMs;
      string rdwPPlRbKg;
      string oXxqRgJHHg;
      string ABbQYJXZZC;
      string yKBrSGzgHO;
      string GFqECJyVyB;
      string DeOespCepF;
      string OqCIheVFYL;
      string gczsatJXOP;
      string LBbYzSuWzb;
      string EUpBAODiVX;
      string msxmTZfVDy;
      string feQZtMPdIP;
      string iyGwHMmyrL;
      string paBqcSEnEZ;
      string mZSAuZEQGn;
      string zZZFnnmAeH;
      if(cGeIFhDMIG == OqCIheVFYL){lgdrIFcYxb = true;}
      else if(OqCIheVFYL == cGeIFhDMIG){GWuGRESpLV = true;}
      if(FkqIPkhOkK == gczsatJXOP){IaZicJeFAh = true;}
      else if(gczsatJXOP == FkqIPkhOkK){MdArbsNzdy = true;}
      if(jwwXAXhCkq == LBbYzSuWzb){IWqEMPBwCn = true;}
      else if(LBbYzSuWzb == jwwXAXhCkq){BFgYHpINWU = true;}
      if(guNQiNmWMs == EUpBAODiVX){eDJwmFwarp = true;}
      else if(EUpBAODiVX == guNQiNmWMs){UsdygrOMFZ = true;}
      if(rdwPPlRbKg == msxmTZfVDy){weSefYAqce = true;}
      else if(msxmTZfVDy == rdwPPlRbKg){eMzZJkWDWr = true;}
      if(oXxqRgJHHg == feQZtMPdIP){IgAxzPpYfr = true;}
      else if(feQZtMPdIP == oXxqRgJHHg){CIejYApVyb = true;}
      if(ABbQYJXZZC == iyGwHMmyrL){DfWJwERcuW = true;}
      else if(iyGwHMmyrL == ABbQYJXZZC){uFSqASzCKj = true;}
      if(yKBrSGzgHO == paBqcSEnEZ){MENJkcDLYn = true;}
      if(GFqECJyVyB == mZSAuZEQGn){PKSWeyCLwW = true;}
      if(DeOespCepF == zZZFnnmAeH){PWuzlQIJha = true;}
      while(paBqcSEnEZ == yKBrSGzgHO){eAsDToFGOV = true;}
      while(mZSAuZEQGn == mZSAuZEQGn){TFpeRMNtYf = true;}
      while(zZZFnnmAeH == zZZFnnmAeH){BsNdeZsIZq = true;}
      if(lgdrIFcYxb == true){lgdrIFcYxb = false;}
      if(IaZicJeFAh == true){IaZicJeFAh = false;}
      if(IWqEMPBwCn == true){IWqEMPBwCn = false;}
      if(eDJwmFwarp == true){eDJwmFwarp = false;}
      if(weSefYAqce == true){weSefYAqce = false;}
      if(IgAxzPpYfr == true){IgAxzPpYfr = false;}
      if(DfWJwERcuW == true){DfWJwERcuW = false;}
      if(MENJkcDLYn == true){MENJkcDLYn = false;}
      if(PKSWeyCLwW == true){PKSWeyCLwW = false;}
      if(PWuzlQIJha == true){PWuzlQIJha = false;}
      if(GWuGRESpLV == true){GWuGRESpLV = false;}
      if(MdArbsNzdy == true){MdArbsNzdy = false;}
      if(BFgYHpINWU == true){BFgYHpINWU = false;}
      if(UsdygrOMFZ == true){UsdygrOMFZ = false;}
      if(eMzZJkWDWr == true){eMzZJkWDWr = false;}
      if(CIejYApVyb == true){CIejYApVyb = false;}
      if(uFSqASzCKj == true){uFSqASzCKj = false;}
      if(eAsDToFGOV == true){eAsDToFGOV = false;}
      if(TFpeRMNtYf == true){TFpeRMNtYf = false;}
      if(BsNdeZsIZq == true){BsNdeZsIZq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SYTHFVDLXY
{ 
  void eCOBaHzEGs()
  { 
      bool SLJDICrkSF = false;
      bool gZBiXfsffB = false;
      bool YbVgUHXDZf = false;
      bool UOKIBYEwxH = false;
      bool QJIRWjlCds = false;
      bool CoxsXqobhA = false;
      bool eoKmkSPsgy = false;
      bool bwiXjPTDJk = false;
      bool VVYgceRQjK = false;
      bool jbOwcbyUgE = false;
      bool UrUfQGGYJI = false;
      bool XkSweIPdKF = false;
      bool AyIWOzhltH = false;
      bool RyWFQcAsPW = false;
      bool YrHbmzJRRU = false;
      bool MUKbEViyQQ = false;
      bool XTdBpYOMeC = false;
      bool IVNmfHqgiP = false;
      bool pQUZuwmtBu = false;
      bool sBcyyEOFkN = false;
      string OaaiQDApsM;
      string ugJijxOsFg;
      string RgWDBNoQOz;
      string fwjVwypsGF;
      string wryqqjfQfF;
      string ZOuzugEXhC;
      string Njasgyxmlk;
      string HVlAjZifLR;
      string hYjJYQBjaO;
      string tRLDrMQEKr;
      string mrdtyEbtOU;
      string yXMPUozRTP;
      string xMMWqoJiIX;
      string JdUSdotoLU;
      string oHUGQVEuiC;
      string MzjtuZfHDI;
      string tslqLTDsle;
      string tJGzaprFFU;
      string jOAFKJtaXE;
      string JmlCZuUcux;
      if(OaaiQDApsM == mrdtyEbtOU){SLJDICrkSF = true;}
      else if(mrdtyEbtOU == OaaiQDApsM){UrUfQGGYJI = true;}
      if(ugJijxOsFg == yXMPUozRTP){gZBiXfsffB = true;}
      else if(yXMPUozRTP == ugJijxOsFg){XkSweIPdKF = true;}
      if(RgWDBNoQOz == xMMWqoJiIX){YbVgUHXDZf = true;}
      else if(xMMWqoJiIX == RgWDBNoQOz){AyIWOzhltH = true;}
      if(fwjVwypsGF == JdUSdotoLU){UOKIBYEwxH = true;}
      else if(JdUSdotoLU == fwjVwypsGF){RyWFQcAsPW = true;}
      if(wryqqjfQfF == oHUGQVEuiC){QJIRWjlCds = true;}
      else if(oHUGQVEuiC == wryqqjfQfF){YrHbmzJRRU = true;}
      if(ZOuzugEXhC == MzjtuZfHDI){CoxsXqobhA = true;}
      else if(MzjtuZfHDI == ZOuzugEXhC){MUKbEViyQQ = true;}
      if(Njasgyxmlk == tslqLTDsle){eoKmkSPsgy = true;}
      else if(tslqLTDsle == Njasgyxmlk){XTdBpYOMeC = true;}
      if(HVlAjZifLR == tJGzaprFFU){bwiXjPTDJk = true;}
      if(hYjJYQBjaO == jOAFKJtaXE){VVYgceRQjK = true;}
      if(tRLDrMQEKr == JmlCZuUcux){jbOwcbyUgE = true;}
      while(tJGzaprFFU == HVlAjZifLR){IVNmfHqgiP = true;}
      while(jOAFKJtaXE == jOAFKJtaXE){pQUZuwmtBu = true;}
      while(JmlCZuUcux == JmlCZuUcux){sBcyyEOFkN = true;}
      if(SLJDICrkSF == true){SLJDICrkSF = false;}
      if(gZBiXfsffB == true){gZBiXfsffB = false;}
      if(YbVgUHXDZf == true){YbVgUHXDZf = false;}
      if(UOKIBYEwxH == true){UOKIBYEwxH = false;}
      if(QJIRWjlCds == true){QJIRWjlCds = false;}
      if(CoxsXqobhA == true){CoxsXqobhA = false;}
      if(eoKmkSPsgy == true){eoKmkSPsgy = false;}
      if(bwiXjPTDJk == true){bwiXjPTDJk = false;}
      if(VVYgceRQjK == true){VVYgceRQjK = false;}
      if(jbOwcbyUgE == true){jbOwcbyUgE = false;}
      if(UrUfQGGYJI == true){UrUfQGGYJI = false;}
      if(XkSweIPdKF == true){XkSweIPdKF = false;}
      if(AyIWOzhltH == true){AyIWOzhltH = false;}
      if(RyWFQcAsPW == true){RyWFQcAsPW = false;}
      if(YrHbmzJRRU == true){YrHbmzJRRU = false;}
      if(MUKbEViyQQ == true){MUKbEViyQQ = false;}
      if(XTdBpYOMeC == true){XTdBpYOMeC = false;}
      if(IVNmfHqgiP == true){IVNmfHqgiP = false;}
      if(pQUZuwmtBu == true){pQUZuwmtBu = false;}
      if(sBcyyEOFkN == true){sBcyyEOFkN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGQJOCCUCC
{ 
  void UNoFgGuBHt()
  { 
      bool ypCzFtFdni = false;
      bool gTmxLdtQXH = false;
      bool hxSEMlZCVC = false;
      bool rZWrODuErE = false;
      bool EZrzBzSsnl = false;
      bool yrrCnAWylT = false;
      bool UCHkqGxuhH = false;
      bool ipXSDIFSCN = false;
      bool SfNjEzhUDN = false;
      bool gxSYjBRGIu = false;
      bool CXKfCHTYyf = false;
      bool tEuXAnnXgq = false;
      bool YbqUalXyiC = false;
      bool pzKHKuUhgw = false;
      bool fIVXTbBtXu = false;
      bool MtYQVagpEQ = false;
      bool jVowpusnNF = false;
      bool SGpjLQFSBz = false;
      bool jdZnouZtli = false;
      bool NdcPLJTYhX = false;
      string Euhqudinae;
      string CftQRBAmik;
      string AmOnuKsOjq;
      string WtlaeEFdTk;
      string xTbcOqdKNm;
      string kAKTPRfswj;
      string jTEiHHsTkN;
      string wVSyngLkZD;
      string fiBwGWjRKN;
      string XLhiAdPrUH;
      string yKZAqOgMfi;
      string FuTrDBSHck;
      string XbIWokmixJ;
      string RTQSFVIBFq;
      string pWlbIcqpfy;
      string LHPjiWBCKF;
      string bxOVRldBmg;
      string sQCkuAogOM;
      string sxDyyJDfii;
      string TGqzPrIPJW;
      if(Euhqudinae == yKZAqOgMfi){ypCzFtFdni = true;}
      else if(yKZAqOgMfi == Euhqudinae){CXKfCHTYyf = true;}
      if(CftQRBAmik == FuTrDBSHck){gTmxLdtQXH = true;}
      else if(FuTrDBSHck == CftQRBAmik){tEuXAnnXgq = true;}
      if(AmOnuKsOjq == XbIWokmixJ){hxSEMlZCVC = true;}
      else if(XbIWokmixJ == AmOnuKsOjq){YbqUalXyiC = true;}
      if(WtlaeEFdTk == RTQSFVIBFq){rZWrODuErE = true;}
      else if(RTQSFVIBFq == WtlaeEFdTk){pzKHKuUhgw = true;}
      if(xTbcOqdKNm == pWlbIcqpfy){EZrzBzSsnl = true;}
      else if(pWlbIcqpfy == xTbcOqdKNm){fIVXTbBtXu = true;}
      if(kAKTPRfswj == LHPjiWBCKF){yrrCnAWylT = true;}
      else if(LHPjiWBCKF == kAKTPRfswj){MtYQVagpEQ = true;}
      if(jTEiHHsTkN == bxOVRldBmg){UCHkqGxuhH = true;}
      else if(bxOVRldBmg == jTEiHHsTkN){jVowpusnNF = true;}
      if(wVSyngLkZD == sQCkuAogOM){ipXSDIFSCN = true;}
      if(fiBwGWjRKN == sxDyyJDfii){SfNjEzhUDN = true;}
      if(XLhiAdPrUH == TGqzPrIPJW){gxSYjBRGIu = true;}
      while(sQCkuAogOM == wVSyngLkZD){SGpjLQFSBz = true;}
      while(sxDyyJDfii == sxDyyJDfii){jdZnouZtli = true;}
      while(TGqzPrIPJW == TGqzPrIPJW){NdcPLJTYhX = true;}
      if(ypCzFtFdni == true){ypCzFtFdni = false;}
      if(gTmxLdtQXH == true){gTmxLdtQXH = false;}
      if(hxSEMlZCVC == true){hxSEMlZCVC = false;}
      if(rZWrODuErE == true){rZWrODuErE = false;}
      if(EZrzBzSsnl == true){EZrzBzSsnl = false;}
      if(yrrCnAWylT == true){yrrCnAWylT = false;}
      if(UCHkqGxuhH == true){UCHkqGxuhH = false;}
      if(ipXSDIFSCN == true){ipXSDIFSCN = false;}
      if(SfNjEzhUDN == true){SfNjEzhUDN = false;}
      if(gxSYjBRGIu == true){gxSYjBRGIu = false;}
      if(CXKfCHTYyf == true){CXKfCHTYyf = false;}
      if(tEuXAnnXgq == true){tEuXAnnXgq = false;}
      if(YbqUalXyiC == true){YbqUalXyiC = false;}
      if(pzKHKuUhgw == true){pzKHKuUhgw = false;}
      if(fIVXTbBtXu == true){fIVXTbBtXu = false;}
      if(MtYQVagpEQ == true){MtYQVagpEQ = false;}
      if(jVowpusnNF == true){jVowpusnNF = false;}
      if(SGpjLQFSBz == true){SGpjLQFSBz = false;}
      if(jdZnouZtli == true){jdZnouZtli = false;}
      if(NdcPLJTYhX == true){NdcPLJTYhX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AMXXJGCOGE
{ 
  void kYHATrCSsV()
  { 
      bool eFrfKtOYUD = false;
      bool JwqWxDVcQl = false;
      bool sZmCyJXtQA = false;
      bool weOMhUsmoM = false;
      bool bOliiFZJqL = false;
      bool VTUTsFSphA = false;
      bool VUITHehenb = false;
      bool KinEJemDTr = false;
      bool jNDFdbKuSc = false;
      bool BDEnpHGRbD = false;
      bool XuUOAlfPJO = false;
      bool ROWoQHRDpe = false;
      bool UlMLZGezOC = false;
      bool XVbPTosnEq = false;
      bool wtlDKmgPWh = false;
      bool oCbwikhInt = false;
      bool HfAGqwmGUb = false;
      bool OcyyhZAJBm = false;
      bool ZPcgNUtfgi = false;
      bool GkAKiQteMO = false;
      string uyUPaJNGTM;
      string UtCcDxNNri;
      string FirNgPCTVM;
      string OPixKSylMf;
      string MaxkRMafse;
      string qqaywMGGiK;
      string HtjGxFLFSj;
      string zbBLWekGwU;
      string oVZqUWnkAx;
      string LqCBYRpqmM;
      string AVMJePoPbR;
      string bAKOUkUskZ;
      string QZEVYHZAmE;
      string nsTiTTJQLF;
      string hYJiVLgmgm;
      string xxFMwaRqjX;
      string pocXchfauA;
      string bDhfrrQUzN;
      string alSzGqnGms;
      string CRfnPrwlFm;
      if(uyUPaJNGTM == AVMJePoPbR){eFrfKtOYUD = true;}
      else if(AVMJePoPbR == uyUPaJNGTM){XuUOAlfPJO = true;}
      if(UtCcDxNNri == bAKOUkUskZ){JwqWxDVcQl = true;}
      else if(bAKOUkUskZ == UtCcDxNNri){ROWoQHRDpe = true;}
      if(FirNgPCTVM == QZEVYHZAmE){sZmCyJXtQA = true;}
      else if(QZEVYHZAmE == FirNgPCTVM){UlMLZGezOC = true;}
      if(OPixKSylMf == nsTiTTJQLF){weOMhUsmoM = true;}
      else if(nsTiTTJQLF == OPixKSylMf){XVbPTosnEq = true;}
      if(MaxkRMafse == hYJiVLgmgm){bOliiFZJqL = true;}
      else if(hYJiVLgmgm == MaxkRMafse){wtlDKmgPWh = true;}
      if(qqaywMGGiK == xxFMwaRqjX){VTUTsFSphA = true;}
      else if(xxFMwaRqjX == qqaywMGGiK){oCbwikhInt = true;}
      if(HtjGxFLFSj == pocXchfauA){VUITHehenb = true;}
      else if(pocXchfauA == HtjGxFLFSj){HfAGqwmGUb = true;}
      if(zbBLWekGwU == bDhfrrQUzN){KinEJemDTr = true;}
      if(oVZqUWnkAx == alSzGqnGms){jNDFdbKuSc = true;}
      if(LqCBYRpqmM == CRfnPrwlFm){BDEnpHGRbD = true;}
      while(bDhfrrQUzN == zbBLWekGwU){OcyyhZAJBm = true;}
      while(alSzGqnGms == alSzGqnGms){ZPcgNUtfgi = true;}
      while(CRfnPrwlFm == CRfnPrwlFm){GkAKiQteMO = true;}
      if(eFrfKtOYUD == true){eFrfKtOYUD = false;}
      if(JwqWxDVcQl == true){JwqWxDVcQl = false;}
      if(sZmCyJXtQA == true){sZmCyJXtQA = false;}
      if(weOMhUsmoM == true){weOMhUsmoM = false;}
      if(bOliiFZJqL == true){bOliiFZJqL = false;}
      if(VTUTsFSphA == true){VTUTsFSphA = false;}
      if(VUITHehenb == true){VUITHehenb = false;}
      if(KinEJemDTr == true){KinEJemDTr = false;}
      if(jNDFdbKuSc == true){jNDFdbKuSc = false;}
      if(BDEnpHGRbD == true){BDEnpHGRbD = false;}
      if(XuUOAlfPJO == true){XuUOAlfPJO = false;}
      if(ROWoQHRDpe == true){ROWoQHRDpe = false;}
      if(UlMLZGezOC == true){UlMLZGezOC = false;}
      if(XVbPTosnEq == true){XVbPTosnEq = false;}
      if(wtlDKmgPWh == true){wtlDKmgPWh = false;}
      if(oCbwikhInt == true){oCbwikhInt = false;}
      if(HfAGqwmGUb == true){HfAGqwmGUb = false;}
      if(OcyyhZAJBm == true){OcyyhZAJBm = false;}
      if(ZPcgNUtfgi == true){ZPcgNUtfgi = false;}
      if(GkAKiQteMO == true){GkAKiQteMO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KXCRPIDZQS
{ 
  void TPDHkciPcj()
  { 
      bool OQfPMULcZS = false;
      bool uRGwtWQnaA = false;
      bool tejGARhiyB = false;
      bool csDBIfzrCX = false;
      bool YNVDzPKSxw = false;
      bool sGkKEifZOt = false;
      bool lbdYoBNEmN = false;
      bool WXlCbfJgGk = false;
      bool GPlBHWIrxZ = false;
      bool zZcIlwiwOy = false;
      bool BFeiYUUiiX = false;
      bool YzTdmWpbRR = false;
      bool sVHNNxucQf = false;
      bool xMSHiBkCcl = false;
      bool CYJYAAGyUP = false;
      bool FGewFfyQUb = false;
      bool ZqRCaLfLtl = false;
      bool knzeOTLhNN = false;
      bool qwIBZphVCD = false;
      bool CTgAMLHGyn = false;
      string mWRNnlzTdC;
      string hzNDjoMJAw;
      string bozZcdIGNz;
      string uwzqHWgRGi;
      string oEPlzoSosT;
      string LhgmhyWrkJ;
      string crFdGlAWuM;
      string ItDRHXYNZm;
      string LTNtnMOMIJ;
      string zogwFwyleN;
      string owsfKQePeK;
      string YJRyyJeKps;
      string WmNlMTNGLK;
      string YmhMxPZhiW;
      string hygykpWhyw;
      string RnwlpBhHSq;
      string DXDTlkbFBh;
      string jxbSLXGPBW;
      string xfHPskqwVu;
      string hROrTJtMLz;
      if(mWRNnlzTdC == owsfKQePeK){OQfPMULcZS = true;}
      else if(owsfKQePeK == mWRNnlzTdC){BFeiYUUiiX = true;}
      if(hzNDjoMJAw == YJRyyJeKps){uRGwtWQnaA = true;}
      else if(YJRyyJeKps == hzNDjoMJAw){YzTdmWpbRR = true;}
      if(bozZcdIGNz == WmNlMTNGLK){tejGARhiyB = true;}
      else if(WmNlMTNGLK == bozZcdIGNz){sVHNNxucQf = true;}
      if(uwzqHWgRGi == YmhMxPZhiW){csDBIfzrCX = true;}
      else if(YmhMxPZhiW == uwzqHWgRGi){xMSHiBkCcl = true;}
      if(oEPlzoSosT == hygykpWhyw){YNVDzPKSxw = true;}
      else if(hygykpWhyw == oEPlzoSosT){CYJYAAGyUP = true;}
      if(LhgmhyWrkJ == RnwlpBhHSq){sGkKEifZOt = true;}
      else if(RnwlpBhHSq == LhgmhyWrkJ){FGewFfyQUb = true;}
      if(crFdGlAWuM == DXDTlkbFBh){lbdYoBNEmN = true;}
      else if(DXDTlkbFBh == crFdGlAWuM){ZqRCaLfLtl = true;}
      if(ItDRHXYNZm == jxbSLXGPBW){WXlCbfJgGk = true;}
      if(LTNtnMOMIJ == xfHPskqwVu){GPlBHWIrxZ = true;}
      if(zogwFwyleN == hROrTJtMLz){zZcIlwiwOy = true;}
      while(jxbSLXGPBW == ItDRHXYNZm){knzeOTLhNN = true;}
      while(xfHPskqwVu == xfHPskqwVu){qwIBZphVCD = true;}
      while(hROrTJtMLz == hROrTJtMLz){CTgAMLHGyn = true;}
      if(OQfPMULcZS == true){OQfPMULcZS = false;}
      if(uRGwtWQnaA == true){uRGwtWQnaA = false;}
      if(tejGARhiyB == true){tejGARhiyB = false;}
      if(csDBIfzrCX == true){csDBIfzrCX = false;}
      if(YNVDzPKSxw == true){YNVDzPKSxw = false;}
      if(sGkKEifZOt == true){sGkKEifZOt = false;}
      if(lbdYoBNEmN == true){lbdYoBNEmN = false;}
      if(WXlCbfJgGk == true){WXlCbfJgGk = false;}
      if(GPlBHWIrxZ == true){GPlBHWIrxZ = false;}
      if(zZcIlwiwOy == true){zZcIlwiwOy = false;}
      if(BFeiYUUiiX == true){BFeiYUUiiX = false;}
      if(YzTdmWpbRR == true){YzTdmWpbRR = false;}
      if(sVHNNxucQf == true){sVHNNxucQf = false;}
      if(xMSHiBkCcl == true){xMSHiBkCcl = false;}
      if(CYJYAAGyUP == true){CYJYAAGyUP = false;}
      if(FGewFfyQUb == true){FGewFfyQUb = false;}
      if(ZqRCaLfLtl == true){ZqRCaLfLtl = false;}
      if(knzeOTLhNN == true){knzeOTLhNN = false;}
      if(qwIBZphVCD == true){qwIBZphVCD = false;}
      if(CTgAMLHGyn == true){CTgAMLHGyn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VESDICJLAO
{ 
  void iAoTdUpBJf()
  { 
      bool aZOCFfbMLh = false;
      bool rzVxNaEXYP = false;
      bool CtDCUYraAi = false;
      bool afQUGGUzHt = false;
      bool KUydzOtUhf = false;
      bool NNnIugWMhg = false;
      bool nBMbGMiBpG = false;
      bool GFPeFgwZDF = false;
      bool dWrUVNqHYZ = false;
      bool jIRZGIIVWl = false;
      bool frebYIxJDN = false;
      bool jxIcCQJqGs = false;
      bool VabPWxnoYw = false;
      bool YaCRYlqQuN = false;
      bool PhELplAnXo = false;
      bool zQPdQFQOEb = false;
      bool THkGoJtqDQ = false;
      bool YswrcnVQZj = false;
      bool xzRixIKXBS = false;
      bool UcLTsHxxWg = false;
      string angrtjFcHS;
      string MykSTKEfaR;
      string dryUyxxGIH;
      string XKNCAyZbUb;
      string zfujgcnFOB;
      string iFsilhpLtw;
      string lzTztBkhRV;
      string kcLyRxxNmV;
      string JrqGYSRdQS;
      string HNhXoALuof;
      string rGmsQGstRn;
      string kbXXltIMab;
      string jGQzNWtmIR;
      string lBXHdDExpS;
      string YWMbgfpJku;
      string qzUNulonet;
      string LGkzCiEPti;
      string oKWHCMsoRh;
      string gjBNamgJMq;
      string OQSwHSkNYx;
      if(angrtjFcHS == rGmsQGstRn){aZOCFfbMLh = true;}
      else if(rGmsQGstRn == angrtjFcHS){frebYIxJDN = true;}
      if(MykSTKEfaR == kbXXltIMab){rzVxNaEXYP = true;}
      else if(kbXXltIMab == MykSTKEfaR){jxIcCQJqGs = true;}
      if(dryUyxxGIH == jGQzNWtmIR){CtDCUYraAi = true;}
      else if(jGQzNWtmIR == dryUyxxGIH){VabPWxnoYw = true;}
      if(XKNCAyZbUb == lBXHdDExpS){afQUGGUzHt = true;}
      else if(lBXHdDExpS == XKNCAyZbUb){YaCRYlqQuN = true;}
      if(zfujgcnFOB == YWMbgfpJku){KUydzOtUhf = true;}
      else if(YWMbgfpJku == zfujgcnFOB){PhELplAnXo = true;}
      if(iFsilhpLtw == qzUNulonet){NNnIugWMhg = true;}
      else if(qzUNulonet == iFsilhpLtw){zQPdQFQOEb = true;}
      if(lzTztBkhRV == LGkzCiEPti){nBMbGMiBpG = true;}
      else if(LGkzCiEPti == lzTztBkhRV){THkGoJtqDQ = true;}
      if(kcLyRxxNmV == oKWHCMsoRh){GFPeFgwZDF = true;}
      if(JrqGYSRdQS == gjBNamgJMq){dWrUVNqHYZ = true;}
      if(HNhXoALuof == OQSwHSkNYx){jIRZGIIVWl = true;}
      while(oKWHCMsoRh == kcLyRxxNmV){YswrcnVQZj = true;}
      while(gjBNamgJMq == gjBNamgJMq){xzRixIKXBS = true;}
      while(OQSwHSkNYx == OQSwHSkNYx){UcLTsHxxWg = true;}
      if(aZOCFfbMLh == true){aZOCFfbMLh = false;}
      if(rzVxNaEXYP == true){rzVxNaEXYP = false;}
      if(CtDCUYraAi == true){CtDCUYraAi = false;}
      if(afQUGGUzHt == true){afQUGGUzHt = false;}
      if(KUydzOtUhf == true){KUydzOtUhf = false;}
      if(NNnIugWMhg == true){NNnIugWMhg = false;}
      if(nBMbGMiBpG == true){nBMbGMiBpG = false;}
      if(GFPeFgwZDF == true){GFPeFgwZDF = false;}
      if(dWrUVNqHYZ == true){dWrUVNqHYZ = false;}
      if(jIRZGIIVWl == true){jIRZGIIVWl = false;}
      if(frebYIxJDN == true){frebYIxJDN = false;}
      if(jxIcCQJqGs == true){jxIcCQJqGs = false;}
      if(VabPWxnoYw == true){VabPWxnoYw = false;}
      if(YaCRYlqQuN == true){YaCRYlqQuN = false;}
      if(PhELplAnXo == true){PhELplAnXo = false;}
      if(zQPdQFQOEb == true){zQPdQFQOEb = false;}
      if(THkGoJtqDQ == true){THkGoJtqDQ = false;}
      if(YswrcnVQZj == true){YswrcnVQZj = false;}
      if(xzRixIKXBS == true){xzRixIKXBS = false;}
      if(UcLTsHxxWg == true){UcLTsHxxWg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ULZXBWTUJZ
{ 
  void SyUUtrBGJN()
  { 
      bool fGlIlxrFGl = false;
      bool FAiyBTGcon = false;
      bool jrVhEtziya = false;
      bool FVVRTyRxIn = false;
      bool UQPAEIjeAo = false;
      bool srRInnjDDq = false;
      bool yJHegieReD = false;
      bool CIUATTbVdw = false;
      bool KUhJhMEMce = false;
      bool ONsQpLJjSU = false;
      bool dRAxljXQoU = false;
      bool LOZGgcaxwT = false;
      bool eRnznoODKH = false;
      bool JrCISrUkXy = false;
      bool omXISAmmjM = false;
      bool jMmypMdAIw = false;
      bool UUFgKTLRnn = false;
      bool IpZyersefn = false;
      bool BbSyXxEDRG = false;
      bool OTbadUgpxz = false;
      string yOiZZautXJ;
      string GgZzKMgJAw;
      string bSYrGSfVLt;
      string ZbBKDCQhTA;
      string EIfCKWCqBX;
      string FbRfOeoqSG;
      string uYicidfPuH;
      string uyozrSmWgi;
      string PnUmnyKVwY;
      string MZOMFeZCSg;
      string qmuscHmRnu;
      string rSJjqGEuok;
      string TJTWtVibtM;
      string rjDAqcrbJg;
      string KshAftPeVz;
      string adNgMgTYyH;
      string XLXaCHOJrN;
      string NckHaabSpA;
      string FDFtlNWWmJ;
      string IScCIzUGxY;
      if(yOiZZautXJ == qmuscHmRnu){fGlIlxrFGl = true;}
      else if(qmuscHmRnu == yOiZZautXJ){dRAxljXQoU = true;}
      if(GgZzKMgJAw == rSJjqGEuok){FAiyBTGcon = true;}
      else if(rSJjqGEuok == GgZzKMgJAw){LOZGgcaxwT = true;}
      if(bSYrGSfVLt == TJTWtVibtM){jrVhEtziya = true;}
      else if(TJTWtVibtM == bSYrGSfVLt){eRnznoODKH = true;}
      if(ZbBKDCQhTA == rjDAqcrbJg){FVVRTyRxIn = true;}
      else if(rjDAqcrbJg == ZbBKDCQhTA){JrCISrUkXy = true;}
      if(EIfCKWCqBX == KshAftPeVz){UQPAEIjeAo = true;}
      else if(KshAftPeVz == EIfCKWCqBX){omXISAmmjM = true;}
      if(FbRfOeoqSG == adNgMgTYyH){srRInnjDDq = true;}
      else if(adNgMgTYyH == FbRfOeoqSG){jMmypMdAIw = true;}
      if(uYicidfPuH == XLXaCHOJrN){yJHegieReD = true;}
      else if(XLXaCHOJrN == uYicidfPuH){UUFgKTLRnn = true;}
      if(uyozrSmWgi == NckHaabSpA){CIUATTbVdw = true;}
      if(PnUmnyKVwY == FDFtlNWWmJ){KUhJhMEMce = true;}
      if(MZOMFeZCSg == IScCIzUGxY){ONsQpLJjSU = true;}
      while(NckHaabSpA == uyozrSmWgi){IpZyersefn = true;}
      while(FDFtlNWWmJ == FDFtlNWWmJ){BbSyXxEDRG = true;}
      while(IScCIzUGxY == IScCIzUGxY){OTbadUgpxz = true;}
      if(fGlIlxrFGl == true){fGlIlxrFGl = false;}
      if(FAiyBTGcon == true){FAiyBTGcon = false;}
      if(jrVhEtziya == true){jrVhEtziya = false;}
      if(FVVRTyRxIn == true){FVVRTyRxIn = false;}
      if(UQPAEIjeAo == true){UQPAEIjeAo = false;}
      if(srRInnjDDq == true){srRInnjDDq = false;}
      if(yJHegieReD == true){yJHegieReD = false;}
      if(CIUATTbVdw == true){CIUATTbVdw = false;}
      if(KUhJhMEMce == true){KUhJhMEMce = false;}
      if(ONsQpLJjSU == true){ONsQpLJjSU = false;}
      if(dRAxljXQoU == true){dRAxljXQoU = false;}
      if(LOZGgcaxwT == true){LOZGgcaxwT = false;}
      if(eRnznoODKH == true){eRnznoODKH = false;}
      if(JrCISrUkXy == true){JrCISrUkXy = false;}
      if(omXISAmmjM == true){omXISAmmjM = false;}
      if(jMmypMdAIw == true){jMmypMdAIw = false;}
      if(UUFgKTLRnn == true){UUFgKTLRnn = false;}
      if(IpZyersefn == true){IpZyersefn = false;}
      if(BbSyXxEDRG == true){BbSyXxEDRG = false;}
      if(OTbadUgpxz == true){OTbadUgpxz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EEHNFQUBXK
{ 
  void YoqYXdDSID()
  { 
      bool ZEGYVfPzOO = false;
      bool xGBwmciYud = false;
      bool GNqTXagxqI = false;
      bool JFzDYpKjgi = false;
      bool aFyfyKYXhV = false;
      bool NLspALMlBt = false;
      bool zRHGErHyXw = false;
      bool SyqMCAOKVM = false;
      bool BIOUuyLIDM = false;
      bool cYiliIxrbF = false;
      bool DazkDOTgnz = false;
      bool xCPnrpDmKF = false;
      bool gytLTtPEcs = false;
      bool DWiPJZIdRf = false;
      bool edTDPaIttr = false;
      bool FKhVYEfnRJ = false;
      bool zODuwaSAeR = false;
      bool hYVdaCeqwr = false;
      bool kUKjmroMqF = false;
      bool tUMHgPaYHn = false;
      string iOXtTeoClk;
      string kIFubLXcVT;
      string dIILNINOIY;
      string nLHKwRsIIf;
      string YymLpmelEl;
      string xjtBZZGLfL;
      string QasMxYAtyK;
      string SPTpteUwVa;
      string caJWbDQGjW;
      string KgbwOyFaNQ;
      string ljntThPEGu;
      string FJpFhpQWks;
      string HtJbzkmXbw;
      string ZthEnsmPDt;
      string nMzoRBpWOY;
      string gipUJraLth;
      string trbKUKblQo;
      string CBSqFttTKy;
      string tQIDOqENtw;
      string RaUVzwjoUG;
      if(iOXtTeoClk == ljntThPEGu){ZEGYVfPzOO = true;}
      else if(ljntThPEGu == iOXtTeoClk){DazkDOTgnz = true;}
      if(kIFubLXcVT == FJpFhpQWks){xGBwmciYud = true;}
      else if(FJpFhpQWks == kIFubLXcVT){xCPnrpDmKF = true;}
      if(dIILNINOIY == HtJbzkmXbw){GNqTXagxqI = true;}
      else if(HtJbzkmXbw == dIILNINOIY){gytLTtPEcs = true;}
      if(nLHKwRsIIf == ZthEnsmPDt){JFzDYpKjgi = true;}
      else if(ZthEnsmPDt == nLHKwRsIIf){DWiPJZIdRf = true;}
      if(YymLpmelEl == nMzoRBpWOY){aFyfyKYXhV = true;}
      else if(nMzoRBpWOY == YymLpmelEl){edTDPaIttr = true;}
      if(xjtBZZGLfL == gipUJraLth){NLspALMlBt = true;}
      else if(gipUJraLth == xjtBZZGLfL){FKhVYEfnRJ = true;}
      if(QasMxYAtyK == trbKUKblQo){zRHGErHyXw = true;}
      else if(trbKUKblQo == QasMxYAtyK){zODuwaSAeR = true;}
      if(SPTpteUwVa == CBSqFttTKy){SyqMCAOKVM = true;}
      if(caJWbDQGjW == tQIDOqENtw){BIOUuyLIDM = true;}
      if(KgbwOyFaNQ == RaUVzwjoUG){cYiliIxrbF = true;}
      while(CBSqFttTKy == SPTpteUwVa){hYVdaCeqwr = true;}
      while(tQIDOqENtw == tQIDOqENtw){kUKjmroMqF = true;}
      while(RaUVzwjoUG == RaUVzwjoUG){tUMHgPaYHn = true;}
      if(ZEGYVfPzOO == true){ZEGYVfPzOO = false;}
      if(xGBwmciYud == true){xGBwmciYud = false;}
      if(GNqTXagxqI == true){GNqTXagxqI = false;}
      if(JFzDYpKjgi == true){JFzDYpKjgi = false;}
      if(aFyfyKYXhV == true){aFyfyKYXhV = false;}
      if(NLspALMlBt == true){NLspALMlBt = false;}
      if(zRHGErHyXw == true){zRHGErHyXw = false;}
      if(SyqMCAOKVM == true){SyqMCAOKVM = false;}
      if(BIOUuyLIDM == true){BIOUuyLIDM = false;}
      if(cYiliIxrbF == true){cYiliIxrbF = false;}
      if(DazkDOTgnz == true){DazkDOTgnz = false;}
      if(xCPnrpDmKF == true){xCPnrpDmKF = false;}
      if(gytLTtPEcs == true){gytLTtPEcs = false;}
      if(DWiPJZIdRf == true){DWiPJZIdRf = false;}
      if(edTDPaIttr == true){edTDPaIttr = false;}
      if(FKhVYEfnRJ == true){FKhVYEfnRJ = false;}
      if(zODuwaSAeR == true){zODuwaSAeR = false;}
      if(hYVdaCeqwr == true){hYVdaCeqwr = false;}
      if(kUKjmroMqF == true){kUKjmroMqF = false;}
      if(tUMHgPaYHn == true){tUMHgPaYHn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KALCSQJXEQ
{ 
  void hHnIAysiSO()
  { 
      bool yZMswNLDgQ = false;
      bool jWuHlbqxQP = false;
      bool QWUFnlfOry = false;
      bool ytOwXrWTet = false;
      bool KFoxnnNxGJ = false;
      bool cZLhoaEGEK = false;
      bool gwLhSoHzjs = false;
      bool EXSWFKhXQz = false;
      bool XhIiUYigHw = false;
      bool nPOUMNtGez = false;
      bool gONMEFGocd = false;
      bool sfpFlyncNs = false;
      bool GarmFoIyJq = false;
      bool QasRSJUwdP = false;
      bool RsDcCHZJhN = false;
      bool ZQsksFVZGP = false;
      bool xIekNSmYlc = false;
      bool dryxbMXOky = false;
      bool OyPwRzhHYN = false;
      bool muoOSIORPj = false;
      string rwGaythNIK;
      string GBBCtIANIw;
      string OWXPDVBkfw;
      string lAstUckYRp;
      string SDUNKopNJD;
      string NELKjUXpXb;
      string rxgLXGIHhR;
      string WauRcKCKFN;
      string fnacigoiJz;
      string EtBoxVVJoE;
      string gifqflJsgZ;
      string SNkKwEVDbp;
      string QZxhNbZFUH;
      string nrUBfwHjwx;
      string XuBjfqJpss;
      string zShzmHkxdE;
      string LDYYkarjdA;
      string wlGdSVXNBV;
      string RiMaHVJVOY;
      string LJFrlTWcyF;
      if(rwGaythNIK == gifqflJsgZ){yZMswNLDgQ = true;}
      else if(gifqflJsgZ == rwGaythNIK){gONMEFGocd = true;}
      if(GBBCtIANIw == SNkKwEVDbp){jWuHlbqxQP = true;}
      else if(SNkKwEVDbp == GBBCtIANIw){sfpFlyncNs = true;}
      if(OWXPDVBkfw == QZxhNbZFUH){QWUFnlfOry = true;}
      else if(QZxhNbZFUH == OWXPDVBkfw){GarmFoIyJq = true;}
      if(lAstUckYRp == nrUBfwHjwx){ytOwXrWTet = true;}
      else if(nrUBfwHjwx == lAstUckYRp){QasRSJUwdP = true;}
      if(SDUNKopNJD == XuBjfqJpss){KFoxnnNxGJ = true;}
      else if(XuBjfqJpss == SDUNKopNJD){RsDcCHZJhN = true;}
      if(NELKjUXpXb == zShzmHkxdE){cZLhoaEGEK = true;}
      else if(zShzmHkxdE == NELKjUXpXb){ZQsksFVZGP = true;}
      if(rxgLXGIHhR == LDYYkarjdA){gwLhSoHzjs = true;}
      else if(LDYYkarjdA == rxgLXGIHhR){xIekNSmYlc = true;}
      if(WauRcKCKFN == wlGdSVXNBV){EXSWFKhXQz = true;}
      if(fnacigoiJz == RiMaHVJVOY){XhIiUYigHw = true;}
      if(EtBoxVVJoE == LJFrlTWcyF){nPOUMNtGez = true;}
      while(wlGdSVXNBV == WauRcKCKFN){dryxbMXOky = true;}
      while(RiMaHVJVOY == RiMaHVJVOY){OyPwRzhHYN = true;}
      while(LJFrlTWcyF == LJFrlTWcyF){muoOSIORPj = true;}
      if(yZMswNLDgQ == true){yZMswNLDgQ = false;}
      if(jWuHlbqxQP == true){jWuHlbqxQP = false;}
      if(QWUFnlfOry == true){QWUFnlfOry = false;}
      if(ytOwXrWTet == true){ytOwXrWTet = false;}
      if(KFoxnnNxGJ == true){KFoxnnNxGJ = false;}
      if(cZLhoaEGEK == true){cZLhoaEGEK = false;}
      if(gwLhSoHzjs == true){gwLhSoHzjs = false;}
      if(EXSWFKhXQz == true){EXSWFKhXQz = false;}
      if(XhIiUYigHw == true){XhIiUYigHw = false;}
      if(nPOUMNtGez == true){nPOUMNtGez = false;}
      if(gONMEFGocd == true){gONMEFGocd = false;}
      if(sfpFlyncNs == true){sfpFlyncNs = false;}
      if(GarmFoIyJq == true){GarmFoIyJq = false;}
      if(QasRSJUwdP == true){QasRSJUwdP = false;}
      if(RsDcCHZJhN == true){RsDcCHZJhN = false;}
      if(ZQsksFVZGP == true){ZQsksFVZGP = false;}
      if(xIekNSmYlc == true){xIekNSmYlc = false;}
      if(dryxbMXOky == true){dryxbMXOky = false;}
      if(OyPwRzhHYN == true){OyPwRzhHYN = false;}
      if(muoOSIORPj == true){muoOSIORPj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCQFIFWOBS
{ 
  void uWjAxALqSM()
  { 
      bool EbpJfrSDSQ = false;
      bool sPFkfVtmaA = false;
      bool zHiicNUZMD = false;
      bool XfQqHOqUkS = false;
      bool CIaOUFFFNb = false;
      bool ValPowsHgS = false;
      bool XrqPrMyNdR = false;
      bool eYCHypfTOW = false;
      bool HOLkgwtBBK = false;
      bool VjmRuJRLVH = false;
      bool HrbwwxYdRz = false;
      bool QYsKLIgGiu = false;
      bool SxLSwuljMn = false;
      bool YUxHPPmPnj = false;
      bool XQiCtwpbGm = false;
      bool cKcanJfIAB = false;
      bool KoQdZwbluu = false;
      bool VRSzXCNIYz = false;
      bool EJdZKNqWSF = false;
      bool idOlYizFcx = false;
      string IrzxqDjNAi;
      string ZfTDHEaoRl;
      string VSgGPoNcBK;
      string ZWggeAgTbS;
      string NlQEMgEsXc;
      string hYabPoKrgB;
      string pGLoJCzlXH;
      string WHMzXjCbti;
      string jTFXcAuERo;
      string oolZbGaauK;
      string hRVPFZLbEe;
      string miyyQWBmMI;
      string GtUiShVmWQ;
      string IagiBSyoSC;
      string oTAmBGqmIF;
      string FmNlDmxlxX;
      string EYEmVMBOxy;
      string YMUKTmsggL;
      string qheRLVMtfN;
      string VLqtyQONQo;
      if(IrzxqDjNAi == hRVPFZLbEe){EbpJfrSDSQ = true;}
      else if(hRVPFZLbEe == IrzxqDjNAi){HrbwwxYdRz = true;}
      if(ZfTDHEaoRl == miyyQWBmMI){sPFkfVtmaA = true;}
      else if(miyyQWBmMI == ZfTDHEaoRl){QYsKLIgGiu = true;}
      if(VSgGPoNcBK == GtUiShVmWQ){zHiicNUZMD = true;}
      else if(GtUiShVmWQ == VSgGPoNcBK){SxLSwuljMn = true;}
      if(ZWggeAgTbS == IagiBSyoSC){XfQqHOqUkS = true;}
      else if(IagiBSyoSC == ZWggeAgTbS){YUxHPPmPnj = true;}
      if(NlQEMgEsXc == oTAmBGqmIF){CIaOUFFFNb = true;}
      else if(oTAmBGqmIF == NlQEMgEsXc){XQiCtwpbGm = true;}
      if(hYabPoKrgB == FmNlDmxlxX){ValPowsHgS = true;}
      else if(FmNlDmxlxX == hYabPoKrgB){cKcanJfIAB = true;}
      if(pGLoJCzlXH == EYEmVMBOxy){XrqPrMyNdR = true;}
      else if(EYEmVMBOxy == pGLoJCzlXH){KoQdZwbluu = true;}
      if(WHMzXjCbti == YMUKTmsggL){eYCHypfTOW = true;}
      if(jTFXcAuERo == qheRLVMtfN){HOLkgwtBBK = true;}
      if(oolZbGaauK == VLqtyQONQo){VjmRuJRLVH = true;}
      while(YMUKTmsggL == WHMzXjCbti){VRSzXCNIYz = true;}
      while(qheRLVMtfN == qheRLVMtfN){EJdZKNqWSF = true;}
      while(VLqtyQONQo == VLqtyQONQo){idOlYizFcx = true;}
      if(EbpJfrSDSQ == true){EbpJfrSDSQ = false;}
      if(sPFkfVtmaA == true){sPFkfVtmaA = false;}
      if(zHiicNUZMD == true){zHiicNUZMD = false;}
      if(XfQqHOqUkS == true){XfQqHOqUkS = false;}
      if(CIaOUFFFNb == true){CIaOUFFFNb = false;}
      if(ValPowsHgS == true){ValPowsHgS = false;}
      if(XrqPrMyNdR == true){XrqPrMyNdR = false;}
      if(eYCHypfTOW == true){eYCHypfTOW = false;}
      if(HOLkgwtBBK == true){HOLkgwtBBK = false;}
      if(VjmRuJRLVH == true){VjmRuJRLVH = false;}
      if(HrbwwxYdRz == true){HrbwwxYdRz = false;}
      if(QYsKLIgGiu == true){QYsKLIgGiu = false;}
      if(SxLSwuljMn == true){SxLSwuljMn = false;}
      if(YUxHPPmPnj == true){YUxHPPmPnj = false;}
      if(XQiCtwpbGm == true){XQiCtwpbGm = false;}
      if(cKcanJfIAB == true){cKcanJfIAB = false;}
      if(KoQdZwbluu == true){KoQdZwbluu = false;}
      if(VRSzXCNIYz == true){VRSzXCNIYz = false;}
      if(EJdZKNqWSF == true){EJdZKNqWSF = false;}
      if(idOlYizFcx == true){idOlYizFcx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BTSZXVJGAR
{ 
  void PFZpyeUooK()
  { 
      bool hgaMYpJsRa = false;
      bool ztkTgyPccR = false;
      bool AigdzofCdz = false;
      bool DbehrLAYZr = false;
      bool IxdtVCzWfS = false;
      bool nxuxVzzwNi = false;
      bool JHORWXPDbV = false;
      bool xpDkICEmHw = false;
      bool pIVLLFfgLr = false;
      bool LEKqiBhMWy = false;
      bool mwuKUxtKnS = false;
      bool uMnRsAkDGQ = false;
      bool rhqiJsfLCH = false;
      bool TqPJJsNLqN = false;
      bool LUrrxzQsyh = false;
      bool QeGFFEEMAb = false;
      bool RhIgzDxdIz = false;
      bool lYMsFWozlK = false;
      bool clMTqnkJEE = false;
      bool oBLOucLLss = false;
      string VWtDZRgLFw;
      string LwgRtiglbY;
      string cpgHWUlAXy;
      string mBTOQyxexd;
      string EMhmwOAGel;
      string dkWbpfomfE;
      string efmGJKcRBw;
      string lBnxUQHtKI;
      string UeVlTBdqYk;
      string IKyszXZbck;
      string lhFiAcwZHZ;
      string XubXiAKBlI;
      string gksQnaCuxw;
      string pfQYWmZllq;
      string EDjyMMiaJy;
      string NYoUEAonuY;
      string ZBbLiqeCAw;
      string ZXOuDdAtDa;
      string ralyhRqwUV;
      string xkqMQDaYOV;
      if(VWtDZRgLFw == lhFiAcwZHZ){hgaMYpJsRa = true;}
      else if(lhFiAcwZHZ == VWtDZRgLFw){mwuKUxtKnS = true;}
      if(LwgRtiglbY == XubXiAKBlI){ztkTgyPccR = true;}
      else if(XubXiAKBlI == LwgRtiglbY){uMnRsAkDGQ = true;}
      if(cpgHWUlAXy == gksQnaCuxw){AigdzofCdz = true;}
      else if(gksQnaCuxw == cpgHWUlAXy){rhqiJsfLCH = true;}
      if(mBTOQyxexd == pfQYWmZllq){DbehrLAYZr = true;}
      else if(pfQYWmZllq == mBTOQyxexd){TqPJJsNLqN = true;}
      if(EMhmwOAGel == EDjyMMiaJy){IxdtVCzWfS = true;}
      else if(EDjyMMiaJy == EMhmwOAGel){LUrrxzQsyh = true;}
      if(dkWbpfomfE == NYoUEAonuY){nxuxVzzwNi = true;}
      else if(NYoUEAonuY == dkWbpfomfE){QeGFFEEMAb = true;}
      if(efmGJKcRBw == ZBbLiqeCAw){JHORWXPDbV = true;}
      else if(ZBbLiqeCAw == efmGJKcRBw){RhIgzDxdIz = true;}
      if(lBnxUQHtKI == ZXOuDdAtDa){xpDkICEmHw = true;}
      if(UeVlTBdqYk == ralyhRqwUV){pIVLLFfgLr = true;}
      if(IKyszXZbck == xkqMQDaYOV){LEKqiBhMWy = true;}
      while(ZXOuDdAtDa == lBnxUQHtKI){lYMsFWozlK = true;}
      while(ralyhRqwUV == ralyhRqwUV){clMTqnkJEE = true;}
      while(xkqMQDaYOV == xkqMQDaYOV){oBLOucLLss = true;}
      if(hgaMYpJsRa == true){hgaMYpJsRa = false;}
      if(ztkTgyPccR == true){ztkTgyPccR = false;}
      if(AigdzofCdz == true){AigdzofCdz = false;}
      if(DbehrLAYZr == true){DbehrLAYZr = false;}
      if(IxdtVCzWfS == true){IxdtVCzWfS = false;}
      if(nxuxVzzwNi == true){nxuxVzzwNi = false;}
      if(JHORWXPDbV == true){JHORWXPDbV = false;}
      if(xpDkICEmHw == true){xpDkICEmHw = false;}
      if(pIVLLFfgLr == true){pIVLLFfgLr = false;}
      if(LEKqiBhMWy == true){LEKqiBhMWy = false;}
      if(mwuKUxtKnS == true){mwuKUxtKnS = false;}
      if(uMnRsAkDGQ == true){uMnRsAkDGQ = false;}
      if(rhqiJsfLCH == true){rhqiJsfLCH = false;}
      if(TqPJJsNLqN == true){TqPJJsNLqN = false;}
      if(LUrrxzQsyh == true){LUrrxzQsyh = false;}
      if(QeGFFEEMAb == true){QeGFFEEMAb = false;}
      if(RhIgzDxdIz == true){RhIgzDxdIz = false;}
      if(lYMsFWozlK == true){lYMsFWozlK = false;}
      if(clMTqnkJEE == true){clMTqnkJEE = false;}
      if(oBLOucLLss == true){oBLOucLLss = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VUQKVMBMRL
{ 
  void cYqWYXoTKM()
  { 
      bool meANWOtMYb = false;
      bool rSEKTYxaAB = false;
      bool nwHkeaOKbu = false;
      bool ULbNlArLcn = false;
      bool oEGeZCwdon = false;
      bool FIBxFqXOiw = false;
      bool zjkcHfqqYT = false;
      bool glyLMiobLb = false;
      bool dkUmpLKdHt = false;
      bool cccfnETdXs = false;
      bool KFFVHTJojW = false;
      bool BuDGRNPxmu = false;
      bool VNidpDIRXH = false;
      bool PLERQXfyeV = false;
      bool BVsksgYVOZ = false;
      bool oVpcXxWbfD = false;
      bool KrRcGoqkot = false;
      bool hQRQsATxjI = false;
      bool dmDxStVbtT = false;
      bool BDSbKJEQdD = false;
      string iqzexJkjuc;
      string qGbURqeoBj;
      string uUJTJJjKXi;
      string RuNumeYCTN;
      string UEgInOmBMp;
      string qfMmaNheVn;
      string YaLLLwrggm;
      string RcUmPqnBet;
      string WhyhrlhaUY;
      string wsffotrUxr;
      string WGUZXNLYWj;
      string YfAbRpbdSY;
      string NQLHpYwnyU;
      string yTDlXQNYJd;
      string ZJDkAPsEOz;
      string ROBXeFtMjz;
      string QWZCkFcNDB;
      string bDToyDMaHZ;
      string erZzCiRfGR;
      string VBnJMDiBzt;
      if(iqzexJkjuc == WGUZXNLYWj){meANWOtMYb = true;}
      else if(WGUZXNLYWj == iqzexJkjuc){KFFVHTJojW = true;}
      if(qGbURqeoBj == YfAbRpbdSY){rSEKTYxaAB = true;}
      else if(YfAbRpbdSY == qGbURqeoBj){BuDGRNPxmu = true;}
      if(uUJTJJjKXi == NQLHpYwnyU){nwHkeaOKbu = true;}
      else if(NQLHpYwnyU == uUJTJJjKXi){VNidpDIRXH = true;}
      if(RuNumeYCTN == yTDlXQNYJd){ULbNlArLcn = true;}
      else if(yTDlXQNYJd == RuNumeYCTN){PLERQXfyeV = true;}
      if(UEgInOmBMp == ZJDkAPsEOz){oEGeZCwdon = true;}
      else if(ZJDkAPsEOz == UEgInOmBMp){BVsksgYVOZ = true;}
      if(qfMmaNheVn == ROBXeFtMjz){FIBxFqXOiw = true;}
      else if(ROBXeFtMjz == qfMmaNheVn){oVpcXxWbfD = true;}
      if(YaLLLwrggm == QWZCkFcNDB){zjkcHfqqYT = true;}
      else if(QWZCkFcNDB == YaLLLwrggm){KrRcGoqkot = true;}
      if(RcUmPqnBet == bDToyDMaHZ){glyLMiobLb = true;}
      if(WhyhrlhaUY == erZzCiRfGR){dkUmpLKdHt = true;}
      if(wsffotrUxr == VBnJMDiBzt){cccfnETdXs = true;}
      while(bDToyDMaHZ == RcUmPqnBet){hQRQsATxjI = true;}
      while(erZzCiRfGR == erZzCiRfGR){dmDxStVbtT = true;}
      while(VBnJMDiBzt == VBnJMDiBzt){BDSbKJEQdD = true;}
      if(meANWOtMYb == true){meANWOtMYb = false;}
      if(rSEKTYxaAB == true){rSEKTYxaAB = false;}
      if(nwHkeaOKbu == true){nwHkeaOKbu = false;}
      if(ULbNlArLcn == true){ULbNlArLcn = false;}
      if(oEGeZCwdon == true){oEGeZCwdon = false;}
      if(FIBxFqXOiw == true){FIBxFqXOiw = false;}
      if(zjkcHfqqYT == true){zjkcHfqqYT = false;}
      if(glyLMiobLb == true){glyLMiobLb = false;}
      if(dkUmpLKdHt == true){dkUmpLKdHt = false;}
      if(cccfnETdXs == true){cccfnETdXs = false;}
      if(KFFVHTJojW == true){KFFVHTJojW = false;}
      if(BuDGRNPxmu == true){BuDGRNPxmu = false;}
      if(VNidpDIRXH == true){VNidpDIRXH = false;}
      if(PLERQXfyeV == true){PLERQXfyeV = false;}
      if(BVsksgYVOZ == true){BVsksgYVOZ = false;}
      if(oVpcXxWbfD == true){oVpcXxWbfD = false;}
      if(KrRcGoqkot == true){KrRcGoqkot = false;}
      if(hQRQsATxjI == true){hQRQsATxjI = false;}
      if(dmDxStVbtT == true){dmDxStVbtT = false;}
      if(BDSbKJEQdD == true){BDSbKJEQdD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UHJOROAKUP
{ 
  void arLPWXZyHH()
  { 
      bool IkIaXfzcrW = false;
      bool mKVaWIBFKd = false;
      bool UTcftwRXqj = false;
      bool XSsBZNUcuI = false;
      bool tstUiEyWel = false;
      bool tcmkuoIbfb = false;
      bool NakIzURTBJ = false;
      bool mYKBibZHwp = false;
      bool xusFoufIGk = false;
      bool ErwTtTHlVO = false;
      bool leVUzVSkBT = false;
      bool OBepdSgfSE = false;
      bool oJMPEtbpHP = false;
      bool TmlhDSZYGT = false;
      bool btHmVDNFob = false;
      bool lbTRZcRFQE = false;
      bool sbdkzaOxmL = false;
      bool rIZybtCZsA = false;
      bool gVBedrTTIZ = false;
      bool ATHCZAQVmt = false;
      string amOSXqzcif;
      string pNnzCGlbZO;
      string MbCIzkxJeK;
      string CnUNlTDING;
      string JVHjtInbqe;
      string DHAnhzkFTm;
      string tpyYcCsZNh;
      string DdOTEqUROp;
      string wVRzGunfem;
      string ixoaMTXhGr;
      string PONJbZsfjq;
      string dSqcqXXySh;
      string NMuazFomHj;
      string SlLVZhHHXf;
      string BHwmIPGLjn;
      string wYPYdDSmKV;
      string kFYzXrHUDI;
      string QPZlfGPHRi;
      string zcDSntWmrW;
      string OTxBtwhxOQ;
      if(amOSXqzcif == PONJbZsfjq){IkIaXfzcrW = true;}
      else if(PONJbZsfjq == amOSXqzcif){leVUzVSkBT = true;}
      if(pNnzCGlbZO == dSqcqXXySh){mKVaWIBFKd = true;}
      else if(dSqcqXXySh == pNnzCGlbZO){OBepdSgfSE = true;}
      if(MbCIzkxJeK == NMuazFomHj){UTcftwRXqj = true;}
      else if(NMuazFomHj == MbCIzkxJeK){oJMPEtbpHP = true;}
      if(CnUNlTDING == SlLVZhHHXf){XSsBZNUcuI = true;}
      else if(SlLVZhHHXf == CnUNlTDING){TmlhDSZYGT = true;}
      if(JVHjtInbqe == BHwmIPGLjn){tstUiEyWel = true;}
      else if(BHwmIPGLjn == JVHjtInbqe){btHmVDNFob = true;}
      if(DHAnhzkFTm == wYPYdDSmKV){tcmkuoIbfb = true;}
      else if(wYPYdDSmKV == DHAnhzkFTm){lbTRZcRFQE = true;}
      if(tpyYcCsZNh == kFYzXrHUDI){NakIzURTBJ = true;}
      else if(kFYzXrHUDI == tpyYcCsZNh){sbdkzaOxmL = true;}
      if(DdOTEqUROp == QPZlfGPHRi){mYKBibZHwp = true;}
      if(wVRzGunfem == zcDSntWmrW){xusFoufIGk = true;}
      if(ixoaMTXhGr == OTxBtwhxOQ){ErwTtTHlVO = true;}
      while(QPZlfGPHRi == DdOTEqUROp){rIZybtCZsA = true;}
      while(zcDSntWmrW == zcDSntWmrW){gVBedrTTIZ = true;}
      while(OTxBtwhxOQ == OTxBtwhxOQ){ATHCZAQVmt = true;}
      if(IkIaXfzcrW == true){IkIaXfzcrW = false;}
      if(mKVaWIBFKd == true){mKVaWIBFKd = false;}
      if(UTcftwRXqj == true){UTcftwRXqj = false;}
      if(XSsBZNUcuI == true){XSsBZNUcuI = false;}
      if(tstUiEyWel == true){tstUiEyWel = false;}
      if(tcmkuoIbfb == true){tcmkuoIbfb = false;}
      if(NakIzURTBJ == true){NakIzURTBJ = false;}
      if(mYKBibZHwp == true){mYKBibZHwp = false;}
      if(xusFoufIGk == true){xusFoufIGk = false;}
      if(ErwTtTHlVO == true){ErwTtTHlVO = false;}
      if(leVUzVSkBT == true){leVUzVSkBT = false;}
      if(OBepdSgfSE == true){OBepdSgfSE = false;}
      if(oJMPEtbpHP == true){oJMPEtbpHP = false;}
      if(TmlhDSZYGT == true){TmlhDSZYGT = false;}
      if(btHmVDNFob == true){btHmVDNFob = false;}
      if(lbTRZcRFQE == true){lbTRZcRFQE = false;}
      if(sbdkzaOxmL == true){sbdkzaOxmL = false;}
      if(rIZybtCZsA == true){rIZybtCZsA = false;}
      if(gVBedrTTIZ == true){gVBedrTTIZ = false;}
      if(ATHCZAQVmt == true){ATHCZAQVmt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FQHHCBHGHN
{ 
  void FGxxOCtPdg()
  { 
      bool RkjoaAaTxi = false;
      bool FXweMaakDd = false;
      bool MeYjVjpUlX = false;
      bool gDoTRMtKBZ = false;
      bool soZXSWYfHE = false;
      bool tuGRclLzSq = false;
      bool KGhYBCicNA = false;
      bool fQicjWEBRz = false;
      bool LJMgdkxWpe = false;
      bool AuqKPlHBVQ = false;
      bool nuRHYcLcgG = false;
      bool hKhTeBtAtP = false;
      bool FLliAkYYNx = false;
      bool PDfBLPqEIA = false;
      bool YTojxpMXeN = false;
      bool rGHFLbJiHm = false;
      bool DmPipddgIP = false;
      bool JorsqkVClK = false;
      bool XBszFJwZoi = false;
      bool GIxVxkEGtS = false;
      string GMsutJQQoN;
      string yMoakJfSXJ;
      string cCzyfjYwrR;
      string rSOgextKkz;
      string zHPDmStWEn;
      string zOxRDDNtOK;
      string jUXXUfxHum;
      string OUgYJUmwLM;
      string pCrERdUwca;
      string jAuaOejrhH;
      string UlaRYegYIi;
      string QQiBUhbTFq;
      string KBdUCOYGKd;
      string kuODrDbaem;
      string wwntKTQsGg;
      string CPlqxTIGOK;
      string GaOdyUCeJR;
      string FBoStONjJi;
      string xezcaUIWGY;
      string uVLUfVgJuo;
      if(GMsutJQQoN == UlaRYegYIi){RkjoaAaTxi = true;}
      else if(UlaRYegYIi == GMsutJQQoN){nuRHYcLcgG = true;}
      if(yMoakJfSXJ == QQiBUhbTFq){FXweMaakDd = true;}
      else if(QQiBUhbTFq == yMoakJfSXJ){hKhTeBtAtP = true;}
      if(cCzyfjYwrR == KBdUCOYGKd){MeYjVjpUlX = true;}
      else if(KBdUCOYGKd == cCzyfjYwrR){FLliAkYYNx = true;}
      if(rSOgextKkz == kuODrDbaem){gDoTRMtKBZ = true;}
      else if(kuODrDbaem == rSOgextKkz){PDfBLPqEIA = true;}
      if(zHPDmStWEn == wwntKTQsGg){soZXSWYfHE = true;}
      else if(wwntKTQsGg == zHPDmStWEn){YTojxpMXeN = true;}
      if(zOxRDDNtOK == CPlqxTIGOK){tuGRclLzSq = true;}
      else if(CPlqxTIGOK == zOxRDDNtOK){rGHFLbJiHm = true;}
      if(jUXXUfxHum == GaOdyUCeJR){KGhYBCicNA = true;}
      else if(GaOdyUCeJR == jUXXUfxHum){DmPipddgIP = true;}
      if(OUgYJUmwLM == FBoStONjJi){fQicjWEBRz = true;}
      if(pCrERdUwca == xezcaUIWGY){LJMgdkxWpe = true;}
      if(jAuaOejrhH == uVLUfVgJuo){AuqKPlHBVQ = true;}
      while(FBoStONjJi == OUgYJUmwLM){JorsqkVClK = true;}
      while(xezcaUIWGY == xezcaUIWGY){XBszFJwZoi = true;}
      while(uVLUfVgJuo == uVLUfVgJuo){GIxVxkEGtS = true;}
      if(RkjoaAaTxi == true){RkjoaAaTxi = false;}
      if(FXweMaakDd == true){FXweMaakDd = false;}
      if(MeYjVjpUlX == true){MeYjVjpUlX = false;}
      if(gDoTRMtKBZ == true){gDoTRMtKBZ = false;}
      if(soZXSWYfHE == true){soZXSWYfHE = false;}
      if(tuGRclLzSq == true){tuGRclLzSq = false;}
      if(KGhYBCicNA == true){KGhYBCicNA = false;}
      if(fQicjWEBRz == true){fQicjWEBRz = false;}
      if(LJMgdkxWpe == true){LJMgdkxWpe = false;}
      if(AuqKPlHBVQ == true){AuqKPlHBVQ = false;}
      if(nuRHYcLcgG == true){nuRHYcLcgG = false;}
      if(hKhTeBtAtP == true){hKhTeBtAtP = false;}
      if(FLliAkYYNx == true){FLliAkYYNx = false;}
      if(PDfBLPqEIA == true){PDfBLPqEIA = false;}
      if(YTojxpMXeN == true){YTojxpMXeN = false;}
      if(rGHFLbJiHm == true){rGHFLbJiHm = false;}
      if(DmPipddgIP == true){DmPipddgIP = false;}
      if(JorsqkVClK == true){JorsqkVClK = false;}
      if(XBszFJwZoi == true){XBszFJwZoi = false;}
      if(GIxVxkEGtS == true){GIxVxkEGtS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RTHHATCBHJ
{ 
  void CptUXWemfN()
  { 
      bool EmPSiJPAua = false;
      bool CibUTIgNiB = false;
      bool RXhVfSfnNV = false;
      bool QmhCLhJtbm = false;
      bool YtKKQPYBcR = false;
      bool hZpixgFtmP = false;
      bool calZJOAYJk = false;
      bool zlkubWNWFP = false;
      bool teLwmpxyEe = false;
      bool cOHLKxIjAB = false;
      bool OzrqSunuGZ = false;
      bool ThoWVxPplT = false;
      bool RBTeIjeZje = false;
      bool OcWDAtlTcq = false;
      bool BBreKtYkpM = false;
      bool hRxgiMfNih = false;
      bool QOKbKpLkVa = false;
      bool LuMuRPJoTN = false;
      bool KsjXwxepUm = false;
      bool OYktamqPTU = false;
      string noQmVziSCU;
      string eayQiFOtxK;
      string NWGVDrzdpl;
      string JQQysilJGR;
      string cABoJpuNkl;
      string RsSWrRhuic;
      string AEbQLOKzWz;
      string TFnfgNUQLM;
      string xksEUPysFa;
      string ApacRXXkcu;
      string ewpkSMFloe;
      string xRjVfOLXww;
      string PQswzcdKNJ;
      string ojmQgBuIlI;
      string KLEaciGExC;
      string MAngeOCtko;
      string htXfpNdSne;
      string TDknkEMSSQ;
      string VZNKwnuGkS;
      string zAWwZPmYkP;
      if(noQmVziSCU == ewpkSMFloe){EmPSiJPAua = true;}
      else if(ewpkSMFloe == noQmVziSCU){OzrqSunuGZ = true;}
      if(eayQiFOtxK == xRjVfOLXww){CibUTIgNiB = true;}
      else if(xRjVfOLXww == eayQiFOtxK){ThoWVxPplT = true;}
      if(NWGVDrzdpl == PQswzcdKNJ){RXhVfSfnNV = true;}
      else if(PQswzcdKNJ == NWGVDrzdpl){RBTeIjeZje = true;}
      if(JQQysilJGR == ojmQgBuIlI){QmhCLhJtbm = true;}
      else if(ojmQgBuIlI == JQQysilJGR){OcWDAtlTcq = true;}
      if(cABoJpuNkl == KLEaciGExC){YtKKQPYBcR = true;}
      else if(KLEaciGExC == cABoJpuNkl){BBreKtYkpM = true;}
      if(RsSWrRhuic == MAngeOCtko){hZpixgFtmP = true;}
      else if(MAngeOCtko == RsSWrRhuic){hRxgiMfNih = true;}
      if(AEbQLOKzWz == htXfpNdSne){calZJOAYJk = true;}
      else if(htXfpNdSne == AEbQLOKzWz){QOKbKpLkVa = true;}
      if(TFnfgNUQLM == TDknkEMSSQ){zlkubWNWFP = true;}
      if(xksEUPysFa == VZNKwnuGkS){teLwmpxyEe = true;}
      if(ApacRXXkcu == zAWwZPmYkP){cOHLKxIjAB = true;}
      while(TDknkEMSSQ == TFnfgNUQLM){LuMuRPJoTN = true;}
      while(VZNKwnuGkS == VZNKwnuGkS){KsjXwxepUm = true;}
      while(zAWwZPmYkP == zAWwZPmYkP){OYktamqPTU = true;}
      if(EmPSiJPAua == true){EmPSiJPAua = false;}
      if(CibUTIgNiB == true){CibUTIgNiB = false;}
      if(RXhVfSfnNV == true){RXhVfSfnNV = false;}
      if(QmhCLhJtbm == true){QmhCLhJtbm = false;}
      if(YtKKQPYBcR == true){YtKKQPYBcR = false;}
      if(hZpixgFtmP == true){hZpixgFtmP = false;}
      if(calZJOAYJk == true){calZJOAYJk = false;}
      if(zlkubWNWFP == true){zlkubWNWFP = false;}
      if(teLwmpxyEe == true){teLwmpxyEe = false;}
      if(cOHLKxIjAB == true){cOHLKxIjAB = false;}
      if(OzrqSunuGZ == true){OzrqSunuGZ = false;}
      if(ThoWVxPplT == true){ThoWVxPplT = false;}
      if(RBTeIjeZje == true){RBTeIjeZje = false;}
      if(OcWDAtlTcq == true){OcWDAtlTcq = false;}
      if(BBreKtYkpM == true){BBreKtYkpM = false;}
      if(hRxgiMfNih == true){hRxgiMfNih = false;}
      if(QOKbKpLkVa == true){QOKbKpLkVa = false;}
      if(LuMuRPJoTN == true){LuMuRPJoTN = false;}
      if(KsjXwxepUm == true){KsjXwxepUm = false;}
      if(OYktamqPTU == true){OYktamqPTU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RDCMVQCOED
{ 
  void NCJYjcywGx()
  { 
      bool ZQbbbEYKWz = false;
      bool SmJtWyzdhw = false;
      bool IVATZnAREa = false;
      bool rpfiIRwaPe = false;
      bool dEnyBYqcwL = false;
      bool fCIZeEQHCn = false;
      bool EGGuHcHalE = false;
      bool BYOCREhCSA = false;
      bool wWVrtogGEE = false;
      bool BoXaaXxrqX = false;
      bool RQqqJHnGHZ = false;
      bool WOnBqgjNAR = false;
      bool uBVgDMAmbt = false;
      bool GoKuiffeim = false;
      bool BaydhmAWjs = false;
      bool mjqZcQtJnw = false;
      bool GBeNTgDsSL = false;
      bool BFeNQUCqzP = false;
      bool MdDiGWykRS = false;
      bool kWpmfzujKA = false;
      string ZKZnLexDtl;
      string XOlqbOtkHL;
      string hIcgZzMERK;
      string rNjamKdjPH;
      string uDCQKScQjo;
      string TneuqRhrNL;
      string SskjtKdKDR;
      string jKUzPeFLWH;
      string VuTcpDhojV;
      string ckWDoCRSVA;
      string nSNSEJTffM;
      string LVVGpWYIsq;
      string boagoynQJN;
      string MmoWSDhBXf;
      string iCIWKGPPNR;
      string cJYeYzqfcF;
      string VCVRAXfynl;
      string oXjNHYfDVi;
      string iXCrjDOKyT;
      string MBXSJfgpWm;
      if(ZKZnLexDtl == nSNSEJTffM){ZQbbbEYKWz = true;}
      else if(nSNSEJTffM == ZKZnLexDtl){RQqqJHnGHZ = true;}
      if(XOlqbOtkHL == LVVGpWYIsq){SmJtWyzdhw = true;}
      else if(LVVGpWYIsq == XOlqbOtkHL){WOnBqgjNAR = true;}
      if(hIcgZzMERK == boagoynQJN){IVATZnAREa = true;}
      else if(boagoynQJN == hIcgZzMERK){uBVgDMAmbt = true;}
      if(rNjamKdjPH == MmoWSDhBXf){rpfiIRwaPe = true;}
      else if(MmoWSDhBXf == rNjamKdjPH){GoKuiffeim = true;}
      if(uDCQKScQjo == iCIWKGPPNR){dEnyBYqcwL = true;}
      else if(iCIWKGPPNR == uDCQKScQjo){BaydhmAWjs = true;}
      if(TneuqRhrNL == cJYeYzqfcF){fCIZeEQHCn = true;}
      else if(cJYeYzqfcF == TneuqRhrNL){mjqZcQtJnw = true;}
      if(SskjtKdKDR == VCVRAXfynl){EGGuHcHalE = true;}
      else if(VCVRAXfynl == SskjtKdKDR){GBeNTgDsSL = true;}
      if(jKUzPeFLWH == oXjNHYfDVi){BYOCREhCSA = true;}
      if(VuTcpDhojV == iXCrjDOKyT){wWVrtogGEE = true;}
      if(ckWDoCRSVA == MBXSJfgpWm){BoXaaXxrqX = true;}
      while(oXjNHYfDVi == jKUzPeFLWH){BFeNQUCqzP = true;}
      while(iXCrjDOKyT == iXCrjDOKyT){MdDiGWykRS = true;}
      while(MBXSJfgpWm == MBXSJfgpWm){kWpmfzujKA = true;}
      if(ZQbbbEYKWz == true){ZQbbbEYKWz = false;}
      if(SmJtWyzdhw == true){SmJtWyzdhw = false;}
      if(IVATZnAREa == true){IVATZnAREa = false;}
      if(rpfiIRwaPe == true){rpfiIRwaPe = false;}
      if(dEnyBYqcwL == true){dEnyBYqcwL = false;}
      if(fCIZeEQHCn == true){fCIZeEQHCn = false;}
      if(EGGuHcHalE == true){EGGuHcHalE = false;}
      if(BYOCREhCSA == true){BYOCREhCSA = false;}
      if(wWVrtogGEE == true){wWVrtogGEE = false;}
      if(BoXaaXxrqX == true){BoXaaXxrqX = false;}
      if(RQqqJHnGHZ == true){RQqqJHnGHZ = false;}
      if(WOnBqgjNAR == true){WOnBqgjNAR = false;}
      if(uBVgDMAmbt == true){uBVgDMAmbt = false;}
      if(GoKuiffeim == true){GoKuiffeim = false;}
      if(BaydhmAWjs == true){BaydhmAWjs = false;}
      if(mjqZcQtJnw == true){mjqZcQtJnw = false;}
      if(GBeNTgDsSL == true){GBeNTgDsSL = false;}
      if(BFeNQUCqzP == true){BFeNQUCqzP = false;}
      if(MdDiGWykRS == true){MdDiGWykRS = false;}
      if(kWpmfzujKA == true){kWpmfzujKA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUUMTNKMOP
{ 
  void PFSUbgyHXQ()
  { 
      bool QhlNrrCPwb = false;
      bool BuVrhJplAs = false;
      bool HBNksjBWPP = false;
      bool CHQfKIsUOH = false;
      bool stoTnwchDu = false;
      bool KyLxCOTATH = false;
      bool qfAfZseohZ = false;
      bool PUXrzNLtxx = false;
      bool HSSTFDwSdu = false;
      bool nsBGQNtJst = false;
      bool RnAdfpaSxo = false;
      bool DZDVAXNfZW = false;
      bool xLLlkWTQbl = false;
      bool SBACfTSonP = false;
      bool ccVnqOpeFr = false;
      bool zNiWxFbNrI = false;
      bool VJqKVBYApg = false;
      bool FYrKtTpWuW = false;
      bool goLjmFRcEZ = false;
      bool qEwesSlKSo = false;
      string gMHeLGUHuN;
      string EXmtwWzFGI;
      string IeYtcuXIUF;
      string siKTocaDtD;
      string ASmWCPKiRC;
      string dPdcnCmNBQ;
      string hLloTVNTET;
      string uuKCIoqCrN;
      string koqRbdEgfl;
      string oNBdUngxDf;
      string BpdxGhEaUy;
      string KkVnesUUNp;
      string QfnRdhsghT;
      string IsyLLtKsLs;
      string YdMgbDrNya;
      string TLjMPVCLSY;
      string nXsApRmJbk;
      string iaJTQmTHpa;
      string pehGAwJkwp;
      string qyZlEAkLpJ;
      if(gMHeLGUHuN == BpdxGhEaUy){QhlNrrCPwb = true;}
      else if(BpdxGhEaUy == gMHeLGUHuN){RnAdfpaSxo = true;}
      if(EXmtwWzFGI == KkVnesUUNp){BuVrhJplAs = true;}
      else if(KkVnesUUNp == EXmtwWzFGI){DZDVAXNfZW = true;}
      if(IeYtcuXIUF == QfnRdhsghT){HBNksjBWPP = true;}
      else if(QfnRdhsghT == IeYtcuXIUF){xLLlkWTQbl = true;}
      if(siKTocaDtD == IsyLLtKsLs){CHQfKIsUOH = true;}
      else if(IsyLLtKsLs == siKTocaDtD){SBACfTSonP = true;}
      if(ASmWCPKiRC == YdMgbDrNya){stoTnwchDu = true;}
      else if(YdMgbDrNya == ASmWCPKiRC){ccVnqOpeFr = true;}
      if(dPdcnCmNBQ == TLjMPVCLSY){KyLxCOTATH = true;}
      else if(TLjMPVCLSY == dPdcnCmNBQ){zNiWxFbNrI = true;}
      if(hLloTVNTET == nXsApRmJbk){qfAfZseohZ = true;}
      else if(nXsApRmJbk == hLloTVNTET){VJqKVBYApg = true;}
      if(uuKCIoqCrN == iaJTQmTHpa){PUXrzNLtxx = true;}
      if(koqRbdEgfl == pehGAwJkwp){HSSTFDwSdu = true;}
      if(oNBdUngxDf == qyZlEAkLpJ){nsBGQNtJst = true;}
      while(iaJTQmTHpa == uuKCIoqCrN){FYrKtTpWuW = true;}
      while(pehGAwJkwp == pehGAwJkwp){goLjmFRcEZ = true;}
      while(qyZlEAkLpJ == qyZlEAkLpJ){qEwesSlKSo = true;}
      if(QhlNrrCPwb == true){QhlNrrCPwb = false;}
      if(BuVrhJplAs == true){BuVrhJplAs = false;}
      if(HBNksjBWPP == true){HBNksjBWPP = false;}
      if(CHQfKIsUOH == true){CHQfKIsUOH = false;}
      if(stoTnwchDu == true){stoTnwchDu = false;}
      if(KyLxCOTATH == true){KyLxCOTATH = false;}
      if(qfAfZseohZ == true){qfAfZseohZ = false;}
      if(PUXrzNLtxx == true){PUXrzNLtxx = false;}
      if(HSSTFDwSdu == true){HSSTFDwSdu = false;}
      if(nsBGQNtJst == true){nsBGQNtJst = false;}
      if(RnAdfpaSxo == true){RnAdfpaSxo = false;}
      if(DZDVAXNfZW == true){DZDVAXNfZW = false;}
      if(xLLlkWTQbl == true){xLLlkWTQbl = false;}
      if(SBACfTSonP == true){SBACfTSonP = false;}
      if(ccVnqOpeFr == true){ccVnqOpeFr = false;}
      if(zNiWxFbNrI == true){zNiWxFbNrI = false;}
      if(VJqKVBYApg == true){VJqKVBYApg = false;}
      if(FYrKtTpWuW == true){FYrKtTpWuW = false;}
      if(goLjmFRcEZ == true){goLjmFRcEZ = false;}
      if(qEwesSlKSo == true){qEwesSlKSo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FBIDWMHYHD
{ 
  void aFzmbKaiaq()
  { 
      bool CyWHmIUUWG = false;
      bool sQPRsOndpe = false;
      bool WZDeokRkFo = false;
      bool NYapsjdFhS = false;
      bool iCgKnyYGsY = false;
      bool WODGWbtrSC = false;
      bool qiOhrUoZYI = false;
      bool jhuXwUsrpp = false;
      bool LKrfRzUTTQ = false;
      bool plmebzmyST = false;
      bool IzgknoSfKB = false;
      bool iCCbqfqhPr = false;
      bool AUFHSytPww = false;
      bool gtZVhLdGrc = false;
      bool gnJRhmjKnw = false;
      bool IEiZTmsYRp = false;
      bool tCjOTncfsf = false;
      bool CjpmLLLnZe = false;
      bool OjbAmcLzCu = false;
      bool REoBidEtxs = false;
      string aIWNyNnSeo;
      string GjqjUaQlZg;
      string lBrgRyginf;
      string qdyIrEHnGK;
      string fKHgpdtQGw;
      string cFAsHYQpwz;
      string fEeyyckhrQ;
      string SceOBbsKqn;
      string DPbqDldEAS;
      string mRrGeafJiM;
      string rLYpcAZkrf;
      string eGzIuQbmuL;
      string zfhYcBkYjZ;
      string wjadurplOC;
      string LsMUngSjKN;
      string yrNWMMdANb;
      string PBARiteUMD;
      string ZpXrzGSMju;
      string hANVaDWERh;
      string OoYmmKrtlt;
      if(aIWNyNnSeo == rLYpcAZkrf){CyWHmIUUWG = true;}
      else if(rLYpcAZkrf == aIWNyNnSeo){IzgknoSfKB = true;}
      if(GjqjUaQlZg == eGzIuQbmuL){sQPRsOndpe = true;}
      else if(eGzIuQbmuL == GjqjUaQlZg){iCCbqfqhPr = true;}
      if(lBrgRyginf == zfhYcBkYjZ){WZDeokRkFo = true;}
      else if(zfhYcBkYjZ == lBrgRyginf){AUFHSytPww = true;}
      if(qdyIrEHnGK == wjadurplOC){NYapsjdFhS = true;}
      else if(wjadurplOC == qdyIrEHnGK){gtZVhLdGrc = true;}
      if(fKHgpdtQGw == LsMUngSjKN){iCgKnyYGsY = true;}
      else if(LsMUngSjKN == fKHgpdtQGw){gnJRhmjKnw = true;}
      if(cFAsHYQpwz == yrNWMMdANb){WODGWbtrSC = true;}
      else if(yrNWMMdANb == cFAsHYQpwz){IEiZTmsYRp = true;}
      if(fEeyyckhrQ == PBARiteUMD){qiOhrUoZYI = true;}
      else if(PBARiteUMD == fEeyyckhrQ){tCjOTncfsf = true;}
      if(SceOBbsKqn == ZpXrzGSMju){jhuXwUsrpp = true;}
      if(DPbqDldEAS == hANVaDWERh){LKrfRzUTTQ = true;}
      if(mRrGeafJiM == OoYmmKrtlt){plmebzmyST = true;}
      while(ZpXrzGSMju == SceOBbsKqn){CjpmLLLnZe = true;}
      while(hANVaDWERh == hANVaDWERh){OjbAmcLzCu = true;}
      while(OoYmmKrtlt == OoYmmKrtlt){REoBidEtxs = true;}
      if(CyWHmIUUWG == true){CyWHmIUUWG = false;}
      if(sQPRsOndpe == true){sQPRsOndpe = false;}
      if(WZDeokRkFo == true){WZDeokRkFo = false;}
      if(NYapsjdFhS == true){NYapsjdFhS = false;}
      if(iCgKnyYGsY == true){iCgKnyYGsY = false;}
      if(WODGWbtrSC == true){WODGWbtrSC = false;}
      if(qiOhrUoZYI == true){qiOhrUoZYI = false;}
      if(jhuXwUsrpp == true){jhuXwUsrpp = false;}
      if(LKrfRzUTTQ == true){LKrfRzUTTQ = false;}
      if(plmebzmyST == true){plmebzmyST = false;}
      if(IzgknoSfKB == true){IzgknoSfKB = false;}
      if(iCCbqfqhPr == true){iCCbqfqhPr = false;}
      if(AUFHSytPww == true){AUFHSytPww = false;}
      if(gtZVhLdGrc == true){gtZVhLdGrc = false;}
      if(gnJRhmjKnw == true){gnJRhmjKnw = false;}
      if(IEiZTmsYRp == true){IEiZTmsYRp = false;}
      if(tCjOTncfsf == true){tCjOTncfsf = false;}
      if(CjpmLLLnZe == true){CjpmLLLnZe = false;}
      if(OjbAmcLzCu == true){OjbAmcLzCu = false;}
      if(REoBidEtxs == true){REoBidEtxs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TBQPDTHEVN
{ 
  void wQAxlPoBYL()
  { 
      bool oIXoJrRiFo = false;
      bool GFMctmYCer = false;
      bool TiNaJEAfhq = false;
      bool RflqXpkSNs = false;
      bool IKFGllmqPl = false;
      bool XXpgLFuweF = false;
      bool rkANWaTVEE = false;
      bool CFnljIdGoX = false;
      bool RJQwTtpEfR = false;
      bool tnnHBWKrjL = false;
      bool RRlLiRiEwC = false;
      bool boHGnhUEsb = false;
      bool jOomJORgkM = false;
      bool ykWdGzXENC = false;
      bool LkIdoFfhTS = false;
      bool CGzHaDbyCU = false;
      bool zCTiDqRdAn = false;
      bool KPppQzGLyE = false;
      bool hjMRKrlODC = false;
      bool XYCrCJRYZy = false;
      string WPWLoVkEYN;
      string TygDbNwoSC;
      string ATBhpzuMtc;
      string mNGhuxripd;
      string NNPkepUJRf;
      string KdBDnDOnVo;
      string aXJuZFqyIe;
      string UNzonlEPCA;
      string ekuOSIMCtr;
      string hDMADpDTKZ;
      string yVAlKweMPB;
      string yylVKocucR;
      string roEQwQAyly;
      string ijEcBIjIDV;
      string cAmrsjRqpO;
      string MIpsgIRjos;
      string wgZQSNtITB;
      string ETqHnrCLWM;
      string zIHXlZtKur;
      string qATKYwZVZe;
      if(WPWLoVkEYN == yVAlKweMPB){oIXoJrRiFo = true;}
      else if(yVAlKweMPB == WPWLoVkEYN){RRlLiRiEwC = true;}
      if(TygDbNwoSC == yylVKocucR){GFMctmYCer = true;}
      else if(yylVKocucR == TygDbNwoSC){boHGnhUEsb = true;}
      if(ATBhpzuMtc == roEQwQAyly){TiNaJEAfhq = true;}
      else if(roEQwQAyly == ATBhpzuMtc){jOomJORgkM = true;}
      if(mNGhuxripd == ijEcBIjIDV){RflqXpkSNs = true;}
      else if(ijEcBIjIDV == mNGhuxripd){ykWdGzXENC = true;}
      if(NNPkepUJRf == cAmrsjRqpO){IKFGllmqPl = true;}
      else if(cAmrsjRqpO == NNPkepUJRf){LkIdoFfhTS = true;}
      if(KdBDnDOnVo == MIpsgIRjos){XXpgLFuweF = true;}
      else if(MIpsgIRjos == KdBDnDOnVo){CGzHaDbyCU = true;}
      if(aXJuZFqyIe == wgZQSNtITB){rkANWaTVEE = true;}
      else if(wgZQSNtITB == aXJuZFqyIe){zCTiDqRdAn = true;}
      if(UNzonlEPCA == ETqHnrCLWM){CFnljIdGoX = true;}
      if(ekuOSIMCtr == zIHXlZtKur){RJQwTtpEfR = true;}
      if(hDMADpDTKZ == qATKYwZVZe){tnnHBWKrjL = true;}
      while(ETqHnrCLWM == UNzonlEPCA){KPppQzGLyE = true;}
      while(zIHXlZtKur == zIHXlZtKur){hjMRKrlODC = true;}
      while(qATKYwZVZe == qATKYwZVZe){XYCrCJRYZy = true;}
      if(oIXoJrRiFo == true){oIXoJrRiFo = false;}
      if(GFMctmYCer == true){GFMctmYCer = false;}
      if(TiNaJEAfhq == true){TiNaJEAfhq = false;}
      if(RflqXpkSNs == true){RflqXpkSNs = false;}
      if(IKFGllmqPl == true){IKFGllmqPl = false;}
      if(XXpgLFuweF == true){XXpgLFuweF = false;}
      if(rkANWaTVEE == true){rkANWaTVEE = false;}
      if(CFnljIdGoX == true){CFnljIdGoX = false;}
      if(RJQwTtpEfR == true){RJQwTtpEfR = false;}
      if(tnnHBWKrjL == true){tnnHBWKrjL = false;}
      if(RRlLiRiEwC == true){RRlLiRiEwC = false;}
      if(boHGnhUEsb == true){boHGnhUEsb = false;}
      if(jOomJORgkM == true){jOomJORgkM = false;}
      if(ykWdGzXENC == true){ykWdGzXENC = false;}
      if(LkIdoFfhTS == true){LkIdoFfhTS = false;}
      if(CGzHaDbyCU == true){CGzHaDbyCU = false;}
      if(zCTiDqRdAn == true){zCTiDqRdAn = false;}
      if(KPppQzGLyE == true){KPppQzGLyE = false;}
      if(hjMRKrlODC == true){hjMRKrlODC = false;}
      if(XYCrCJRYZy == true){XYCrCJRYZy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBEUGARCKW
{ 
  void mhMlSsJSHj()
  { 
      bool RdkQFnTDAB = false;
      bool gzitGHOnCJ = false;
      bool ZagQpjTeqs = false;
      bool eecMmrINUn = false;
      bool iBngmEYwqo = false;
      bool XaxDwqxTaV = false;
      bool ToLHWCVWHO = false;
      bool zASOZYlzdk = false;
      bool LXmCUEgZQw = false;
      bool tnmzTsogJj = false;
      bool iBocoXHicW = false;
      bool ExopJuBJlS = false;
      bool UwGKTKNTtf = false;
      bool iFosCJiKMx = false;
      bool wywsrwzxoY = false;
      bool rftqPmudJe = false;
      bool JnnwmzHwmA = false;
      bool LqwoVWzMRW = false;
      bool LQdUnDKydP = false;
      bool NEBhmIJzFs = false;
      string RutxqmtxuZ;
      string lPDtWgWYEH;
      string hMsEYEqQUp;
      string rwTChTcPjN;
      string eejbHTGOny;
      string YZehPECpYl;
      string udbEgouBMD;
      string DGoqbCcQwF;
      string ycbWQSRklc;
      string RmpyRBCfuS;
      string XECktRknFM;
      string bksTmSBFmO;
      string WKPjkQQpYa;
      string AxVdhsapby;
      string hdeYBfsWKy;
      string zxrguMoRzd;
      string BtOeMeOOlt;
      string rLcnfsepiE;
      string WseabDEnhU;
      string DIqyxmOAMV;
      if(RutxqmtxuZ == XECktRknFM){RdkQFnTDAB = true;}
      else if(XECktRknFM == RutxqmtxuZ){iBocoXHicW = true;}
      if(lPDtWgWYEH == bksTmSBFmO){gzitGHOnCJ = true;}
      else if(bksTmSBFmO == lPDtWgWYEH){ExopJuBJlS = true;}
      if(hMsEYEqQUp == WKPjkQQpYa){ZagQpjTeqs = true;}
      else if(WKPjkQQpYa == hMsEYEqQUp){UwGKTKNTtf = true;}
      if(rwTChTcPjN == AxVdhsapby){eecMmrINUn = true;}
      else if(AxVdhsapby == rwTChTcPjN){iFosCJiKMx = true;}
      if(eejbHTGOny == hdeYBfsWKy){iBngmEYwqo = true;}
      else if(hdeYBfsWKy == eejbHTGOny){wywsrwzxoY = true;}
      if(YZehPECpYl == zxrguMoRzd){XaxDwqxTaV = true;}
      else if(zxrguMoRzd == YZehPECpYl){rftqPmudJe = true;}
      if(udbEgouBMD == BtOeMeOOlt){ToLHWCVWHO = true;}
      else if(BtOeMeOOlt == udbEgouBMD){JnnwmzHwmA = true;}
      if(DGoqbCcQwF == rLcnfsepiE){zASOZYlzdk = true;}
      if(ycbWQSRklc == WseabDEnhU){LXmCUEgZQw = true;}
      if(RmpyRBCfuS == DIqyxmOAMV){tnmzTsogJj = true;}
      while(rLcnfsepiE == DGoqbCcQwF){LqwoVWzMRW = true;}
      while(WseabDEnhU == WseabDEnhU){LQdUnDKydP = true;}
      while(DIqyxmOAMV == DIqyxmOAMV){NEBhmIJzFs = true;}
      if(RdkQFnTDAB == true){RdkQFnTDAB = false;}
      if(gzitGHOnCJ == true){gzitGHOnCJ = false;}
      if(ZagQpjTeqs == true){ZagQpjTeqs = false;}
      if(eecMmrINUn == true){eecMmrINUn = false;}
      if(iBngmEYwqo == true){iBngmEYwqo = false;}
      if(XaxDwqxTaV == true){XaxDwqxTaV = false;}
      if(ToLHWCVWHO == true){ToLHWCVWHO = false;}
      if(zASOZYlzdk == true){zASOZYlzdk = false;}
      if(LXmCUEgZQw == true){LXmCUEgZQw = false;}
      if(tnmzTsogJj == true){tnmzTsogJj = false;}
      if(iBocoXHicW == true){iBocoXHicW = false;}
      if(ExopJuBJlS == true){ExopJuBJlS = false;}
      if(UwGKTKNTtf == true){UwGKTKNTtf = false;}
      if(iFosCJiKMx == true){iFosCJiKMx = false;}
      if(wywsrwzxoY == true){wywsrwzxoY = false;}
      if(rftqPmudJe == true){rftqPmudJe = false;}
      if(JnnwmzHwmA == true){JnnwmzHwmA = false;}
      if(LqwoVWzMRW == true){LqwoVWzMRW = false;}
      if(LQdUnDKydP == true){LQdUnDKydP = false;}
      if(NEBhmIJzFs == true){NEBhmIJzFs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ANBFFMLCEF
{ 
  void sIwigbyLHZ()
  { 
      bool PllEerktOc = false;
      bool GBzmGbQPaw = false;
      bool eDdeNaWEWn = false;
      bool AkDOritEju = false;
      bool VTarbDSVxS = false;
      bool FuymnLIHpE = false;
      bool UfXacUxktX = false;
      bool gMffaKckCJ = false;
      bool HBHDhFmPZf = false;
      bool amNfZouzPG = false;
      bool FhaZlrPRMd = false;
      bool iWEgxTYUrX = false;
      bool hhKNwsyzGk = false;
      bool PcVuDYZgQp = false;
      bool pUDwxDigiF = false;
      bool QaHqXXWMcr = false;
      bool tPLaOGBIdX = false;
      bool tqDChNeOQs = false;
      bool KRQATnVdXe = false;
      bool BMEYuZJbhp = false;
      string ksSbUzbzoj;
      string uYAjONkZrl;
      string RHlFwwdWyZ;
      string ZiLfJaJrJl;
      string PixpDekCCk;
      string hWYwmdGMeY;
      string UFAOJMNTZm;
      string DsQFViJwCQ;
      string LbTMrDJOrf;
      string UxMjRKhifq;
      string QQbOhnGSZE;
      string TJKNNsknVG;
      string CzbtSGffmL;
      string AaPKAtAFeD;
      string wpnnMKlzWX;
      string YtMYoRogwa;
      string IZfODstzNS;
      string sfIRKLKmhI;
      string UgIPmGOpVi;
      string FSJDuWKZjS;
      if(ksSbUzbzoj == QQbOhnGSZE){PllEerktOc = true;}
      else if(QQbOhnGSZE == ksSbUzbzoj){FhaZlrPRMd = true;}
      if(uYAjONkZrl == TJKNNsknVG){GBzmGbQPaw = true;}
      else if(TJKNNsknVG == uYAjONkZrl){iWEgxTYUrX = true;}
      if(RHlFwwdWyZ == CzbtSGffmL){eDdeNaWEWn = true;}
      else if(CzbtSGffmL == RHlFwwdWyZ){hhKNwsyzGk = true;}
      if(ZiLfJaJrJl == AaPKAtAFeD){AkDOritEju = true;}
      else if(AaPKAtAFeD == ZiLfJaJrJl){PcVuDYZgQp = true;}
      if(PixpDekCCk == wpnnMKlzWX){VTarbDSVxS = true;}
      else if(wpnnMKlzWX == PixpDekCCk){pUDwxDigiF = true;}
      if(hWYwmdGMeY == YtMYoRogwa){FuymnLIHpE = true;}
      else if(YtMYoRogwa == hWYwmdGMeY){QaHqXXWMcr = true;}
      if(UFAOJMNTZm == IZfODstzNS){UfXacUxktX = true;}
      else if(IZfODstzNS == UFAOJMNTZm){tPLaOGBIdX = true;}
      if(DsQFViJwCQ == sfIRKLKmhI){gMffaKckCJ = true;}
      if(LbTMrDJOrf == UgIPmGOpVi){HBHDhFmPZf = true;}
      if(UxMjRKhifq == FSJDuWKZjS){amNfZouzPG = true;}
      while(sfIRKLKmhI == DsQFViJwCQ){tqDChNeOQs = true;}
      while(UgIPmGOpVi == UgIPmGOpVi){KRQATnVdXe = true;}
      while(FSJDuWKZjS == FSJDuWKZjS){BMEYuZJbhp = true;}
      if(PllEerktOc == true){PllEerktOc = false;}
      if(GBzmGbQPaw == true){GBzmGbQPaw = false;}
      if(eDdeNaWEWn == true){eDdeNaWEWn = false;}
      if(AkDOritEju == true){AkDOritEju = false;}
      if(VTarbDSVxS == true){VTarbDSVxS = false;}
      if(FuymnLIHpE == true){FuymnLIHpE = false;}
      if(UfXacUxktX == true){UfXacUxktX = false;}
      if(gMffaKckCJ == true){gMffaKckCJ = false;}
      if(HBHDhFmPZf == true){HBHDhFmPZf = false;}
      if(amNfZouzPG == true){amNfZouzPG = false;}
      if(FhaZlrPRMd == true){FhaZlrPRMd = false;}
      if(iWEgxTYUrX == true){iWEgxTYUrX = false;}
      if(hhKNwsyzGk == true){hhKNwsyzGk = false;}
      if(PcVuDYZgQp == true){PcVuDYZgQp = false;}
      if(pUDwxDigiF == true){pUDwxDigiF = false;}
      if(QaHqXXWMcr == true){QaHqXXWMcr = false;}
      if(tPLaOGBIdX == true){tPLaOGBIdX = false;}
      if(tqDChNeOQs == true){tqDChNeOQs = false;}
      if(KRQATnVdXe == true){KRQATnVdXe = false;}
      if(BMEYuZJbhp == true){BMEYuZJbhp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BRIRMKCVPY
{ 
  void EVJdCICwqm()
  { 
      bool eZdNlSQxob = false;
      bool ZKeoKNjiZQ = false;
      bool FGKNQdWgLC = false;
      bool wFhdCnoTfD = false;
      bool RyyaEjDyCK = false;
      bool EYJyGXOPwH = false;
      bool ujkmfTbAlW = false;
      bool YQCVzGHjIg = false;
      bool aYdAxXuiXd = false;
      bool YYWXIgMLtk = false;
      bool HCLflnVnzz = false;
      bool QeHPfWFkoI = false;
      bool XsbIxAseNR = false;
      bool swoXZYMyOJ = false;
      bool BHjYNsRHqk = false;
      bool bbVlMNZDhk = false;
      bool tpZgFToipH = false;
      bool KHWfGQJDtE = false;
      bool ilncpRaDLL = false;
      bool yIPcOKhCSt = false;
      string VNittdlLGR;
      string KoFPCwVNhU;
      string RpAJZKoWUp;
      string rXjlWDKaVC;
      string QgnCfrnPeK;
      string POxCdfNZTj;
      string nOpQZmETsy;
      string luqeDkBxch;
      string WZrKZcagHq;
      string pkHlNBqXcs;
      string mTWfYUWRzs;
      string dPxlNOWfpw;
      string MXLCIAnFQB;
      string tcUitCCLkF;
      string FIhOMZmVYy;
      string dLhffPHUXX;
      string fRAxzAuNqK;
      string MLtjpDpxph;
      string NSgRWhunDd;
      string thnMYnHjPL;
      if(VNittdlLGR == mTWfYUWRzs){eZdNlSQxob = true;}
      else if(mTWfYUWRzs == VNittdlLGR){HCLflnVnzz = true;}
      if(KoFPCwVNhU == dPxlNOWfpw){ZKeoKNjiZQ = true;}
      else if(dPxlNOWfpw == KoFPCwVNhU){QeHPfWFkoI = true;}
      if(RpAJZKoWUp == MXLCIAnFQB){FGKNQdWgLC = true;}
      else if(MXLCIAnFQB == RpAJZKoWUp){XsbIxAseNR = true;}
      if(rXjlWDKaVC == tcUitCCLkF){wFhdCnoTfD = true;}
      else if(tcUitCCLkF == rXjlWDKaVC){swoXZYMyOJ = true;}
      if(QgnCfrnPeK == FIhOMZmVYy){RyyaEjDyCK = true;}
      else if(FIhOMZmVYy == QgnCfrnPeK){BHjYNsRHqk = true;}
      if(POxCdfNZTj == dLhffPHUXX){EYJyGXOPwH = true;}
      else if(dLhffPHUXX == POxCdfNZTj){bbVlMNZDhk = true;}
      if(nOpQZmETsy == fRAxzAuNqK){ujkmfTbAlW = true;}
      else if(fRAxzAuNqK == nOpQZmETsy){tpZgFToipH = true;}
      if(luqeDkBxch == MLtjpDpxph){YQCVzGHjIg = true;}
      if(WZrKZcagHq == NSgRWhunDd){aYdAxXuiXd = true;}
      if(pkHlNBqXcs == thnMYnHjPL){YYWXIgMLtk = true;}
      while(MLtjpDpxph == luqeDkBxch){KHWfGQJDtE = true;}
      while(NSgRWhunDd == NSgRWhunDd){ilncpRaDLL = true;}
      while(thnMYnHjPL == thnMYnHjPL){yIPcOKhCSt = true;}
      if(eZdNlSQxob == true){eZdNlSQxob = false;}
      if(ZKeoKNjiZQ == true){ZKeoKNjiZQ = false;}
      if(FGKNQdWgLC == true){FGKNQdWgLC = false;}
      if(wFhdCnoTfD == true){wFhdCnoTfD = false;}
      if(RyyaEjDyCK == true){RyyaEjDyCK = false;}
      if(EYJyGXOPwH == true){EYJyGXOPwH = false;}
      if(ujkmfTbAlW == true){ujkmfTbAlW = false;}
      if(YQCVzGHjIg == true){YQCVzGHjIg = false;}
      if(aYdAxXuiXd == true){aYdAxXuiXd = false;}
      if(YYWXIgMLtk == true){YYWXIgMLtk = false;}
      if(HCLflnVnzz == true){HCLflnVnzz = false;}
      if(QeHPfWFkoI == true){QeHPfWFkoI = false;}
      if(XsbIxAseNR == true){XsbIxAseNR = false;}
      if(swoXZYMyOJ == true){swoXZYMyOJ = false;}
      if(BHjYNsRHqk == true){BHjYNsRHqk = false;}
      if(bbVlMNZDhk == true){bbVlMNZDhk = false;}
      if(tpZgFToipH == true){tpZgFToipH = false;}
      if(KHWfGQJDtE == true){KHWfGQJDtE = false;}
      if(ilncpRaDLL == true){ilncpRaDLL = false;}
      if(yIPcOKhCSt == true){yIPcOKhCSt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NZTXUDYBEY
{ 
  void PtiXUCdnyh()
  { 
      bool acZbPVVNPQ = false;
      bool jXdWlBbkpn = false;
      bool fWdrAcWQHi = false;
      bool bNRlEIRCft = false;
      bool KdspeylLps = false;
      bool SMbyGEzham = false;
      bool yFFgoVFrRd = false;
      bool jYFucBcnNC = false;
      bool pLZOQOlSeA = false;
      bool JibsuEYMAI = false;
      bool rtsMItGfUF = false;
      bool aLUYwmeqQZ = false;
      bool imMRTAxMAX = false;
      bool bQmEJwSNGV = false;
      bool IGxZYyOCwI = false;
      bool ZhwaYFgasH = false;
      bool wtexcKXPPA = false;
      bool URktRcpmrV = false;
      bool ltQqytTLeE = false;
      bool OqTyZNaAwO = false;
      string MciPQiGYJe;
      string zxdKiVkYRm;
      string qQPHjJPrBN;
      string QdZtlEXubp;
      string ejCmPoWKSY;
      string HgNFWuMaeH;
      string SOXwOUWiYd;
      string yoxbHHOcru;
      string lFYbFjQUWp;
      string qxQTWQLGYt;
      string RnknZRilxP;
      string fjhjVNoupd;
      string ECLhlBYcEq;
      string uIDxcyTjCn;
      string AeWHKHOgyJ;
      string aPPtpObCBY;
      string sFgFTXfkGW;
      string sFsCdZeEXe;
      string lrduPfrJGO;
      string VQhcttxRml;
      if(MciPQiGYJe == RnknZRilxP){acZbPVVNPQ = true;}
      else if(RnknZRilxP == MciPQiGYJe){rtsMItGfUF = true;}
      if(zxdKiVkYRm == fjhjVNoupd){jXdWlBbkpn = true;}
      else if(fjhjVNoupd == zxdKiVkYRm){aLUYwmeqQZ = true;}
      if(qQPHjJPrBN == ECLhlBYcEq){fWdrAcWQHi = true;}
      else if(ECLhlBYcEq == qQPHjJPrBN){imMRTAxMAX = true;}
      if(QdZtlEXubp == uIDxcyTjCn){bNRlEIRCft = true;}
      else if(uIDxcyTjCn == QdZtlEXubp){bQmEJwSNGV = true;}
      if(ejCmPoWKSY == AeWHKHOgyJ){KdspeylLps = true;}
      else if(AeWHKHOgyJ == ejCmPoWKSY){IGxZYyOCwI = true;}
      if(HgNFWuMaeH == aPPtpObCBY){SMbyGEzham = true;}
      else if(aPPtpObCBY == HgNFWuMaeH){ZhwaYFgasH = true;}
      if(SOXwOUWiYd == sFgFTXfkGW){yFFgoVFrRd = true;}
      else if(sFgFTXfkGW == SOXwOUWiYd){wtexcKXPPA = true;}
      if(yoxbHHOcru == sFsCdZeEXe){jYFucBcnNC = true;}
      if(lFYbFjQUWp == lrduPfrJGO){pLZOQOlSeA = true;}
      if(qxQTWQLGYt == VQhcttxRml){JibsuEYMAI = true;}
      while(sFsCdZeEXe == yoxbHHOcru){URktRcpmrV = true;}
      while(lrduPfrJGO == lrduPfrJGO){ltQqytTLeE = true;}
      while(VQhcttxRml == VQhcttxRml){OqTyZNaAwO = true;}
      if(acZbPVVNPQ == true){acZbPVVNPQ = false;}
      if(jXdWlBbkpn == true){jXdWlBbkpn = false;}
      if(fWdrAcWQHi == true){fWdrAcWQHi = false;}
      if(bNRlEIRCft == true){bNRlEIRCft = false;}
      if(KdspeylLps == true){KdspeylLps = false;}
      if(SMbyGEzham == true){SMbyGEzham = false;}
      if(yFFgoVFrRd == true){yFFgoVFrRd = false;}
      if(jYFucBcnNC == true){jYFucBcnNC = false;}
      if(pLZOQOlSeA == true){pLZOQOlSeA = false;}
      if(JibsuEYMAI == true){JibsuEYMAI = false;}
      if(rtsMItGfUF == true){rtsMItGfUF = false;}
      if(aLUYwmeqQZ == true){aLUYwmeqQZ = false;}
      if(imMRTAxMAX == true){imMRTAxMAX = false;}
      if(bQmEJwSNGV == true){bQmEJwSNGV = false;}
      if(IGxZYyOCwI == true){IGxZYyOCwI = false;}
      if(ZhwaYFgasH == true){ZhwaYFgasH = false;}
      if(wtexcKXPPA == true){wtexcKXPPA = false;}
      if(URktRcpmrV == true){URktRcpmrV = false;}
      if(ltQqytTLeE == true){ltQqytTLeE = false;}
      if(OqTyZNaAwO == true){OqTyZNaAwO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LDEHQIGIRH
{ 
  void bBDAsffMak()
  { 
      bool ATXcwsDAxj = false;
      bool cEUywURucb = false;
      bool VUIykAgZFf = false;
      bool nxORIdaZjY = false;
      bool CwYySJWYyO = false;
      bool YNogJeLYru = false;
      bool LduQwfpDoR = false;
      bool tqKEZYuJfa = false;
      bool dIbpHaHgIc = false;
      bool SBhnNYBICm = false;
      bool TSifUgCjGj = false;
      bool jBsQRDBEIV = false;
      bool XIuMyrJVqB = false;
      bool XmHsHKYuUZ = false;
      bool XXZXsQIQWK = false;
      bool WwzgOKXWgc = false;
      bool XfsFMwtAIH = false;
      bool dGjhxAhWTg = false;
      bool jrzgeanadx = false;
      bool lCNrCrdULw = false;
      string WCAeTJYYnw;
      string JgrbLeSmcq;
      string rugNjtiIWB;
      string FrdYdqExpQ;
      string whXqgYLLZd;
      string IwJFVbVmuY;
      string ZQBmqRCSxU;
      string aUwLtJWpfL;
      string iXhrrJiYDC;
      string VRCRpefjAP;
      string WrNFDmzxKL;
      string EeGjpChItg;
      string hdPuyJSeUP;
      string cloPopKcoF;
      string KkNrxpKSbn;
      string xXpTgrbSGt;
      string UTbuhSpqtz;
      string rEToWxPXxI;
      string yzCgRFwVhw;
      string NqWtjpISJe;
      if(WCAeTJYYnw == WrNFDmzxKL){ATXcwsDAxj = true;}
      else if(WrNFDmzxKL == WCAeTJYYnw){TSifUgCjGj = true;}
      if(JgrbLeSmcq == EeGjpChItg){cEUywURucb = true;}
      else if(EeGjpChItg == JgrbLeSmcq){jBsQRDBEIV = true;}
      if(rugNjtiIWB == hdPuyJSeUP){VUIykAgZFf = true;}
      else if(hdPuyJSeUP == rugNjtiIWB){XIuMyrJVqB = true;}
      if(FrdYdqExpQ == cloPopKcoF){nxORIdaZjY = true;}
      else if(cloPopKcoF == FrdYdqExpQ){XmHsHKYuUZ = true;}
      if(whXqgYLLZd == KkNrxpKSbn){CwYySJWYyO = true;}
      else if(KkNrxpKSbn == whXqgYLLZd){XXZXsQIQWK = true;}
      if(IwJFVbVmuY == xXpTgrbSGt){YNogJeLYru = true;}
      else if(xXpTgrbSGt == IwJFVbVmuY){WwzgOKXWgc = true;}
      if(ZQBmqRCSxU == UTbuhSpqtz){LduQwfpDoR = true;}
      else if(UTbuhSpqtz == ZQBmqRCSxU){XfsFMwtAIH = true;}
      if(aUwLtJWpfL == rEToWxPXxI){tqKEZYuJfa = true;}
      if(iXhrrJiYDC == yzCgRFwVhw){dIbpHaHgIc = true;}
      if(VRCRpefjAP == NqWtjpISJe){SBhnNYBICm = true;}
      while(rEToWxPXxI == aUwLtJWpfL){dGjhxAhWTg = true;}
      while(yzCgRFwVhw == yzCgRFwVhw){jrzgeanadx = true;}
      while(NqWtjpISJe == NqWtjpISJe){lCNrCrdULw = true;}
      if(ATXcwsDAxj == true){ATXcwsDAxj = false;}
      if(cEUywURucb == true){cEUywURucb = false;}
      if(VUIykAgZFf == true){VUIykAgZFf = false;}
      if(nxORIdaZjY == true){nxORIdaZjY = false;}
      if(CwYySJWYyO == true){CwYySJWYyO = false;}
      if(YNogJeLYru == true){YNogJeLYru = false;}
      if(LduQwfpDoR == true){LduQwfpDoR = false;}
      if(tqKEZYuJfa == true){tqKEZYuJfa = false;}
      if(dIbpHaHgIc == true){dIbpHaHgIc = false;}
      if(SBhnNYBICm == true){SBhnNYBICm = false;}
      if(TSifUgCjGj == true){TSifUgCjGj = false;}
      if(jBsQRDBEIV == true){jBsQRDBEIV = false;}
      if(XIuMyrJVqB == true){XIuMyrJVqB = false;}
      if(XmHsHKYuUZ == true){XmHsHKYuUZ = false;}
      if(XXZXsQIQWK == true){XXZXsQIQWK = false;}
      if(WwzgOKXWgc == true){WwzgOKXWgc = false;}
      if(XfsFMwtAIH == true){XfsFMwtAIH = false;}
      if(dGjhxAhWTg == true){dGjhxAhWTg = false;}
      if(jrzgeanadx == true){jrzgeanadx = false;}
      if(lCNrCrdULw == true){lCNrCrdULw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PCOPUAFUMO
{ 
  void AptiQQDLcT()
  { 
      bool UCeVcGTqYZ = false;
      bool lgzHIEImrK = false;
      bool uaXzizzqPT = false;
      bool kygjsxYVqB = false;
      bool pVUKDHxZXO = false;
      bool pemGjsdemd = false;
      bool HbbEomzPOK = false;
      bool fluqUZGNwa = false;
      bool CYSAdFLazz = false;
      bool TshMsNtPVQ = false;
      bool HgLNhDiwkK = false;
      bool mPiLbiIaai = false;
      bool aYPOqmEhxG = false;
      bool epqeTUMFSa = false;
      bool VPooLDJVkK = false;
      bool ESoloiRwVt = false;
      bool yAyefwYErG = false;
      bool WDIzNLiaCm = false;
      bool dhxmBLBFoj = false;
      bool DPiXbUQKJP = false;
      string DKSaUnVsFx;
      string OgiBBQmiFH;
      string lgHcwswGVi;
      string tJsoIzXwMb;
      string mdHMKOJNbM;
      string YIgQfWCoda;
      string rOWVCEmsrB;
      string sqWdTIYuSh;
      string jhdJKkbcJl;
      string xhRkiYGkJF;
      string aPVZThlCwW;
      string xGWwqJkNLR;
      string cKjFEKYltu;
      string CmlNGTMDob;
      string zZflopLUsZ;
      string mrZqcQePVI;
      string IAHAUJUIpW;
      string wgYiSCdyPN;
      string zDrUHJNtkp;
      string nxhgTyRfQf;
      if(DKSaUnVsFx == aPVZThlCwW){UCeVcGTqYZ = true;}
      else if(aPVZThlCwW == DKSaUnVsFx){HgLNhDiwkK = true;}
      if(OgiBBQmiFH == xGWwqJkNLR){lgzHIEImrK = true;}
      else if(xGWwqJkNLR == OgiBBQmiFH){mPiLbiIaai = true;}
      if(lgHcwswGVi == cKjFEKYltu){uaXzizzqPT = true;}
      else if(cKjFEKYltu == lgHcwswGVi){aYPOqmEhxG = true;}
      if(tJsoIzXwMb == CmlNGTMDob){kygjsxYVqB = true;}
      else if(CmlNGTMDob == tJsoIzXwMb){epqeTUMFSa = true;}
      if(mdHMKOJNbM == zZflopLUsZ){pVUKDHxZXO = true;}
      else if(zZflopLUsZ == mdHMKOJNbM){VPooLDJVkK = true;}
      if(YIgQfWCoda == mrZqcQePVI){pemGjsdemd = true;}
      else if(mrZqcQePVI == YIgQfWCoda){ESoloiRwVt = true;}
      if(rOWVCEmsrB == IAHAUJUIpW){HbbEomzPOK = true;}
      else if(IAHAUJUIpW == rOWVCEmsrB){yAyefwYErG = true;}
      if(sqWdTIYuSh == wgYiSCdyPN){fluqUZGNwa = true;}
      if(jhdJKkbcJl == zDrUHJNtkp){CYSAdFLazz = true;}
      if(xhRkiYGkJF == nxhgTyRfQf){TshMsNtPVQ = true;}
      while(wgYiSCdyPN == sqWdTIYuSh){WDIzNLiaCm = true;}
      while(zDrUHJNtkp == zDrUHJNtkp){dhxmBLBFoj = true;}
      while(nxhgTyRfQf == nxhgTyRfQf){DPiXbUQKJP = true;}
      if(UCeVcGTqYZ == true){UCeVcGTqYZ = false;}
      if(lgzHIEImrK == true){lgzHIEImrK = false;}
      if(uaXzizzqPT == true){uaXzizzqPT = false;}
      if(kygjsxYVqB == true){kygjsxYVqB = false;}
      if(pVUKDHxZXO == true){pVUKDHxZXO = false;}
      if(pemGjsdemd == true){pemGjsdemd = false;}
      if(HbbEomzPOK == true){HbbEomzPOK = false;}
      if(fluqUZGNwa == true){fluqUZGNwa = false;}
      if(CYSAdFLazz == true){CYSAdFLazz = false;}
      if(TshMsNtPVQ == true){TshMsNtPVQ = false;}
      if(HgLNhDiwkK == true){HgLNhDiwkK = false;}
      if(mPiLbiIaai == true){mPiLbiIaai = false;}
      if(aYPOqmEhxG == true){aYPOqmEhxG = false;}
      if(epqeTUMFSa == true){epqeTUMFSa = false;}
      if(VPooLDJVkK == true){VPooLDJVkK = false;}
      if(ESoloiRwVt == true){ESoloiRwVt = false;}
      if(yAyefwYErG == true){yAyefwYErG = false;}
      if(WDIzNLiaCm == true){WDIzNLiaCm = false;}
      if(dhxmBLBFoj == true){dhxmBLBFoj = false;}
      if(DPiXbUQKJP == true){DPiXbUQKJP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UEGXVVNZDA
{ 
  void UozeOVTkbi()
  { 
      bool RugkQmjNoU = false;
      bool jRFxegceQD = false;
      bool rUqFBWmeTY = false;
      bool QdqSonIcnZ = false;
      bool jKFQxjRZbJ = false;
      bool IwbuNwEbjs = false;
      bool AFsPEFalIp = false;
      bool YzqqSgPZHQ = false;
      bool FMCKQTCwFs = false;
      bool jgstYeRoMq = false;
      bool JeRljIFjbf = false;
      bool gdTTmnChzj = false;
      bool DdgPGqGwRn = false;
      bool PZNPGatQZH = false;
      bool ORTYLFNZHk = false;
      bool bipbmexCfs = false;
      bool CIRnPGQDMM = false;
      bool slIqUlKIDA = false;
      bool dgogLgikba = false;
      bool dqkgEFzfJE = false;
      string cmsLLKzcAA;
      string qDlmUFPPto;
      string HPqyuMnraf;
      string icygBnwLEa;
      string rhSGfGcMXg;
      string kHRlpMutPz;
      string VGCUQOFEkf;
      string JEKTwYxkRo;
      string ibTsubKLpn;
      string rBuFEkfyoR;
      string AXarWgxyoR;
      string PKcaPtmIYo;
      string EsOxnIJEOL;
      string ryuznLAbVN;
      string dLWXXgXTpK;
      string yWYANGIdEO;
      string WrjdYRPcmE;
      string sKlLKrWpYG;
      string joOEMUYtlg;
      string CWXHqlbszG;
      if(cmsLLKzcAA == AXarWgxyoR){RugkQmjNoU = true;}
      else if(AXarWgxyoR == cmsLLKzcAA){JeRljIFjbf = true;}
      if(qDlmUFPPto == PKcaPtmIYo){jRFxegceQD = true;}
      else if(PKcaPtmIYo == qDlmUFPPto){gdTTmnChzj = true;}
      if(HPqyuMnraf == EsOxnIJEOL){rUqFBWmeTY = true;}
      else if(EsOxnIJEOL == HPqyuMnraf){DdgPGqGwRn = true;}
      if(icygBnwLEa == ryuznLAbVN){QdqSonIcnZ = true;}
      else if(ryuznLAbVN == icygBnwLEa){PZNPGatQZH = true;}
      if(rhSGfGcMXg == dLWXXgXTpK){jKFQxjRZbJ = true;}
      else if(dLWXXgXTpK == rhSGfGcMXg){ORTYLFNZHk = true;}
      if(kHRlpMutPz == yWYANGIdEO){IwbuNwEbjs = true;}
      else if(yWYANGIdEO == kHRlpMutPz){bipbmexCfs = true;}
      if(VGCUQOFEkf == WrjdYRPcmE){AFsPEFalIp = true;}
      else if(WrjdYRPcmE == VGCUQOFEkf){CIRnPGQDMM = true;}
      if(JEKTwYxkRo == sKlLKrWpYG){YzqqSgPZHQ = true;}
      if(ibTsubKLpn == joOEMUYtlg){FMCKQTCwFs = true;}
      if(rBuFEkfyoR == CWXHqlbszG){jgstYeRoMq = true;}
      while(sKlLKrWpYG == JEKTwYxkRo){slIqUlKIDA = true;}
      while(joOEMUYtlg == joOEMUYtlg){dgogLgikba = true;}
      while(CWXHqlbszG == CWXHqlbszG){dqkgEFzfJE = true;}
      if(RugkQmjNoU == true){RugkQmjNoU = false;}
      if(jRFxegceQD == true){jRFxegceQD = false;}
      if(rUqFBWmeTY == true){rUqFBWmeTY = false;}
      if(QdqSonIcnZ == true){QdqSonIcnZ = false;}
      if(jKFQxjRZbJ == true){jKFQxjRZbJ = false;}
      if(IwbuNwEbjs == true){IwbuNwEbjs = false;}
      if(AFsPEFalIp == true){AFsPEFalIp = false;}
      if(YzqqSgPZHQ == true){YzqqSgPZHQ = false;}
      if(FMCKQTCwFs == true){FMCKQTCwFs = false;}
      if(jgstYeRoMq == true){jgstYeRoMq = false;}
      if(JeRljIFjbf == true){JeRljIFjbf = false;}
      if(gdTTmnChzj == true){gdTTmnChzj = false;}
      if(DdgPGqGwRn == true){DdgPGqGwRn = false;}
      if(PZNPGatQZH == true){PZNPGatQZH = false;}
      if(ORTYLFNZHk == true){ORTYLFNZHk = false;}
      if(bipbmexCfs == true){bipbmexCfs = false;}
      if(CIRnPGQDMM == true){CIRnPGQDMM = false;}
      if(slIqUlKIDA == true){slIqUlKIDA = false;}
      if(dgogLgikba == true){dgogLgikba = false;}
      if(dqkgEFzfJE == true){dqkgEFzfJE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TLKHJTAIZJ
{ 
  void LKcYgXiwWj()
  { 
      bool wHdwCZaMoc = false;
      bool qEfxRZdIrS = false;
      bool OkELHalHye = false;
      bool yPdoUOWhgx = false;
      bool PoiCbybmzL = false;
      bool FWrzIKDSna = false;
      bool nSOKdbaqcC = false;
      bool CuatCZCCjI = false;
      bool yyHmYbXdfK = false;
      bool LEtFJxZXXA = false;
      bool XkKwIKuxwi = false;
      bool HBhecoKbkC = false;
      bool EwKRqyAUkF = false;
      bool zddikNnLdO = false;
      bool fZgwCJVOcU = false;
      bool lymUwaZrFJ = false;
      bool JaMqjdWztO = false;
      bool AzxWWdPOPg = false;
      bool clqPTAqImK = false;
      bool nuFUEENpLY = false;
      string iUGdCYyhhl;
      string WItOhOzerZ;
      string kbtnkFsnto;
      string rmTtKSipUB;
      string gRkFrhZyBj;
      string sEDeSGaSrw;
      string fKnrtjoAEO;
      string fIKprSqnuD;
      string eulJwminbD;
      string rPyXVVcrLI;
      string rZslEjtMmz;
      string PlXoQjXduH;
      string ABYAWPJlUV;
      string oycmKFBAFL;
      string rWBbnFrIHk;
      string yzwEHqBsOn;
      string aIqQJQJjeL;
      string iXYjOdAwMQ;
      string WAeiXpBXfS;
      string DIkQkjejSX;
      if(iUGdCYyhhl == rZslEjtMmz){wHdwCZaMoc = true;}
      else if(rZslEjtMmz == iUGdCYyhhl){XkKwIKuxwi = true;}
      if(WItOhOzerZ == PlXoQjXduH){qEfxRZdIrS = true;}
      else if(PlXoQjXduH == WItOhOzerZ){HBhecoKbkC = true;}
      if(kbtnkFsnto == ABYAWPJlUV){OkELHalHye = true;}
      else if(ABYAWPJlUV == kbtnkFsnto){EwKRqyAUkF = true;}
      if(rmTtKSipUB == oycmKFBAFL){yPdoUOWhgx = true;}
      else if(oycmKFBAFL == rmTtKSipUB){zddikNnLdO = true;}
      if(gRkFrhZyBj == rWBbnFrIHk){PoiCbybmzL = true;}
      else if(rWBbnFrIHk == gRkFrhZyBj){fZgwCJVOcU = true;}
      if(sEDeSGaSrw == yzwEHqBsOn){FWrzIKDSna = true;}
      else if(yzwEHqBsOn == sEDeSGaSrw){lymUwaZrFJ = true;}
      if(fKnrtjoAEO == aIqQJQJjeL){nSOKdbaqcC = true;}
      else if(aIqQJQJjeL == fKnrtjoAEO){JaMqjdWztO = true;}
      if(fIKprSqnuD == iXYjOdAwMQ){CuatCZCCjI = true;}
      if(eulJwminbD == WAeiXpBXfS){yyHmYbXdfK = true;}
      if(rPyXVVcrLI == DIkQkjejSX){LEtFJxZXXA = true;}
      while(iXYjOdAwMQ == fIKprSqnuD){AzxWWdPOPg = true;}
      while(WAeiXpBXfS == WAeiXpBXfS){clqPTAqImK = true;}
      while(DIkQkjejSX == DIkQkjejSX){nuFUEENpLY = true;}
      if(wHdwCZaMoc == true){wHdwCZaMoc = false;}
      if(qEfxRZdIrS == true){qEfxRZdIrS = false;}
      if(OkELHalHye == true){OkELHalHye = false;}
      if(yPdoUOWhgx == true){yPdoUOWhgx = false;}
      if(PoiCbybmzL == true){PoiCbybmzL = false;}
      if(FWrzIKDSna == true){FWrzIKDSna = false;}
      if(nSOKdbaqcC == true){nSOKdbaqcC = false;}
      if(CuatCZCCjI == true){CuatCZCCjI = false;}
      if(yyHmYbXdfK == true){yyHmYbXdfK = false;}
      if(LEtFJxZXXA == true){LEtFJxZXXA = false;}
      if(XkKwIKuxwi == true){XkKwIKuxwi = false;}
      if(HBhecoKbkC == true){HBhecoKbkC = false;}
      if(EwKRqyAUkF == true){EwKRqyAUkF = false;}
      if(zddikNnLdO == true){zddikNnLdO = false;}
      if(fZgwCJVOcU == true){fZgwCJVOcU = false;}
      if(lymUwaZrFJ == true){lymUwaZrFJ = false;}
      if(JaMqjdWztO == true){JaMqjdWztO = false;}
      if(AzxWWdPOPg == true){AzxWWdPOPg = false;}
      if(clqPTAqImK == true){clqPTAqImK = false;}
      if(nuFUEENpLY == true){nuFUEENpLY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TSEGQRBQSK
{ 
  void pqZawlYene()
  { 
      bool KkEdrdorBK = false;
      bool NrCKiigcZt = false;
      bool NTScDyIlCh = false;
      bool obpVWtVCUm = false;
      bool hntsfIZOJj = false;
      bool VsRLgqSbZs = false;
      bool VDoTUlCgmn = false;
      bool NeIlLZYYwu = false;
      bool XsbSMuJeof = false;
      bool ascaReyaYt = false;
      bool GsaUVqkezG = false;
      bool RtedVbbVGY = false;
      bool bXrHNTBhUg = false;
      bool byACoeSGwU = false;
      bool KdehNgNyEo = false;
      bool DbTzRhATHC = false;
      bool oCKSeStcoq = false;
      bool JUZlOyrJsf = false;
      bool FDcedzeBjG = false;
      bool dyzteITMDu = false;
      string KmqIOYSBOP;
      string YUyQgSGXzW;
      string ALNWAQgzFa;
      string STOsdzYfcf;
      string fBCmApPLgw;
      string lXmLJzZTHx;
      string qSunwFGElg;
      string sZuSqyJZVK;
      string BUSJotfDje;
      string ZFXenMFNpu;
      string jKZACLcTUK;
      string ozxxwVAlzC;
      string YCUGHnBPed;
      string rujaapuRHc;
      string QMiYoZHaiS;
      string MTOmWgoSrO;
      string JNoqStPWVF;
      string ahdVkMTwQg;
      string fafMQXfwEs;
      string BbZrSDWrGu;
      if(KmqIOYSBOP == jKZACLcTUK){KkEdrdorBK = true;}
      else if(jKZACLcTUK == KmqIOYSBOP){GsaUVqkezG = true;}
      if(YUyQgSGXzW == ozxxwVAlzC){NrCKiigcZt = true;}
      else if(ozxxwVAlzC == YUyQgSGXzW){RtedVbbVGY = true;}
      if(ALNWAQgzFa == YCUGHnBPed){NTScDyIlCh = true;}
      else if(YCUGHnBPed == ALNWAQgzFa){bXrHNTBhUg = true;}
      if(STOsdzYfcf == rujaapuRHc){obpVWtVCUm = true;}
      else if(rujaapuRHc == STOsdzYfcf){byACoeSGwU = true;}
      if(fBCmApPLgw == QMiYoZHaiS){hntsfIZOJj = true;}
      else if(QMiYoZHaiS == fBCmApPLgw){KdehNgNyEo = true;}
      if(lXmLJzZTHx == MTOmWgoSrO){VsRLgqSbZs = true;}
      else if(MTOmWgoSrO == lXmLJzZTHx){DbTzRhATHC = true;}
      if(qSunwFGElg == JNoqStPWVF){VDoTUlCgmn = true;}
      else if(JNoqStPWVF == qSunwFGElg){oCKSeStcoq = true;}
      if(sZuSqyJZVK == ahdVkMTwQg){NeIlLZYYwu = true;}
      if(BUSJotfDje == fafMQXfwEs){XsbSMuJeof = true;}
      if(ZFXenMFNpu == BbZrSDWrGu){ascaReyaYt = true;}
      while(ahdVkMTwQg == sZuSqyJZVK){JUZlOyrJsf = true;}
      while(fafMQXfwEs == fafMQXfwEs){FDcedzeBjG = true;}
      while(BbZrSDWrGu == BbZrSDWrGu){dyzteITMDu = true;}
      if(KkEdrdorBK == true){KkEdrdorBK = false;}
      if(NrCKiigcZt == true){NrCKiigcZt = false;}
      if(NTScDyIlCh == true){NTScDyIlCh = false;}
      if(obpVWtVCUm == true){obpVWtVCUm = false;}
      if(hntsfIZOJj == true){hntsfIZOJj = false;}
      if(VsRLgqSbZs == true){VsRLgqSbZs = false;}
      if(VDoTUlCgmn == true){VDoTUlCgmn = false;}
      if(NeIlLZYYwu == true){NeIlLZYYwu = false;}
      if(XsbSMuJeof == true){XsbSMuJeof = false;}
      if(ascaReyaYt == true){ascaReyaYt = false;}
      if(GsaUVqkezG == true){GsaUVqkezG = false;}
      if(RtedVbbVGY == true){RtedVbbVGY = false;}
      if(bXrHNTBhUg == true){bXrHNTBhUg = false;}
      if(byACoeSGwU == true){byACoeSGwU = false;}
      if(KdehNgNyEo == true){KdehNgNyEo = false;}
      if(DbTzRhATHC == true){DbTzRhATHC = false;}
      if(oCKSeStcoq == true){oCKSeStcoq = false;}
      if(JUZlOyrJsf == true){JUZlOyrJsf = false;}
      if(FDcedzeBjG == true){FDcedzeBjG = false;}
      if(dyzteITMDu == true){dyzteITMDu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SIZHSKBOTI
{ 
  void dkeTKofnnU()
  { 
      bool qgErqYUaLa = false;
      bool ufGZWljYQZ = false;
      bool qxYXnPmYhn = false;
      bool HsHMKIwknj = false;
      bool XnKxbRwenX = false;
      bool TDRWdsHfDa = false;
      bool kusXSBYtON = false;
      bool pyjgCDmbwW = false;
      bool TIkJTEbjhQ = false;
      bool BPhMybtleZ = false;
      bool rCQZhUTjUa = false;
      bool GfjfHcJjDO = false;
      bool ZoLxMaQWhZ = false;
      bool IAxVdRrLby = false;
      bool kqOHJUeBFU = false;
      bool SKhPADpSMG = false;
      bool EwCuSGiOBp = false;
      bool kxIFciZEmr = false;
      bool uOQNGxRgVZ = false;
      bool bZzUtnoTnD = false;
      string PVMhsSTmmC;
      string cPBeEbNLiy;
      string qfoZumRbVL;
      string KkXECkxZFV;
      string hflDRwAbHN;
      string ZZIQajfmmG;
      string ArQbrrqxcS;
      string emFMPLslHy;
      string lpUHkjbHdS;
      string FJmyVoOKLZ;
      string FDynimTwAO;
      string ptenUKXJpH;
      string PiSKMUzHqa;
      string xiZhshqfYy;
      string QfHObKezdK;
      string RFTDJVjnaN;
      string mMEZRGTxul;
      string SrjrqiaEhB;
      string pAcfIrPWXW;
      string xCEKKDbhxV;
      if(PVMhsSTmmC == FDynimTwAO){qgErqYUaLa = true;}
      else if(FDynimTwAO == PVMhsSTmmC){rCQZhUTjUa = true;}
      if(cPBeEbNLiy == ptenUKXJpH){ufGZWljYQZ = true;}
      else if(ptenUKXJpH == cPBeEbNLiy){GfjfHcJjDO = true;}
      if(qfoZumRbVL == PiSKMUzHqa){qxYXnPmYhn = true;}
      else if(PiSKMUzHqa == qfoZumRbVL){ZoLxMaQWhZ = true;}
      if(KkXECkxZFV == xiZhshqfYy){HsHMKIwknj = true;}
      else if(xiZhshqfYy == KkXECkxZFV){IAxVdRrLby = true;}
      if(hflDRwAbHN == QfHObKezdK){XnKxbRwenX = true;}
      else if(QfHObKezdK == hflDRwAbHN){kqOHJUeBFU = true;}
      if(ZZIQajfmmG == RFTDJVjnaN){TDRWdsHfDa = true;}
      else if(RFTDJVjnaN == ZZIQajfmmG){SKhPADpSMG = true;}
      if(ArQbrrqxcS == mMEZRGTxul){kusXSBYtON = true;}
      else if(mMEZRGTxul == ArQbrrqxcS){EwCuSGiOBp = true;}
      if(emFMPLslHy == SrjrqiaEhB){pyjgCDmbwW = true;}
      if(lpUHkjbHdS == pAcfIrPWXW){TIkJTEbjhQ = true;}
      if(FJmyVoOKLZ == xCEKKDbhxV){BPhMybtleZ = true;}
      while(SrjrqiaEhB == emFMPLslHy){kxIFciZEmr = true;}
      while(pAcfIrPWXW == pAcfIrPWXW){uOQNGxRgVZ = true;}
      while(xCEKKDbhxV == xCEKKDbhxV){bZzUtnoTnD = true;}
      if(qgErqYUaLa == true){qgErqYUaLa = false;}
      if(ufGZWljYQZ == true){ufGZWljYQZ = false;}
      if(qxYXnPmYhn == true){qxYXnPmYhn = false;}
      if(HsHMKIwknj == true){HsHMKIwknj = false;}
      if(XnKxbRwenX == true){XnKxbRwenX = false;}
      if(TDRWdsHfDa == true){TDRWdsHfDa = false;}
      if(kusXSBYtON == true){kusXSBYtON = false;}
      if(pyjgCDmbwW == true){pyjgCDmbwW = false;}
      if(TIkJTEbjhQ == true){TIkJTEbjhQ = false;}
      if(BPhMybtleZ == true){BPhMybtleZ = false;}
      if(rCQZhUTjUa == true){rCQZhUTjUa = false;}
      if(GfjfHcJjDO == true){GfjfHcJjDO = false;}
      if(ZoLxMaQWhZ == true){ZoLxMaQWhZ = false;}
      if(IAxVdRrLby == true){IAxVdRrLby = false;}
      if(kqOHJUeBFU == true){kqOHJUeBFU = false;}
      if(SKhPADpSMG == true){SKhPADpSMG = false;}
      if(EwCuSGiOBp == true){EwCuSGiOBp = false;}
      if(kxIFciZEmr == true){kxIFciZEmr = false;}
      if(uOQNGxRgVZ == true){uOQNGxRgVZ = false;}
      if(bZzUtnoTnD == true){bZzUtnoTnD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MEXAKECHSN
{ 
  void lcBrAIhVpN()
  { 
      bool IonHwPIKDN = false;
      bool bTOSwByYEf = false;
      bool ADDnEhmHbC = false;
      bool aSgcUHdbQb = false;
      bool AYHfysCJMr = false;
      bool reHrTEkACN = false;
      bool cBiAmImlyo = false;
      bool XWIcfawXoK = false;
      bool edtiKuLoJP = false;
      bool VdYDyypHso = false;
      bool GQLWUVWeLr = false;
      bool INKqhyGzpq = false;
      bool xybhTsxFdg = false;
      bool kodAEOSXOn = false;
      bool YgcQGISgUA = false;
      bool rpQCqHncDa = false;
      bool XRAeHTiJmT = false;
      bool fikBRQVLaL = false;
      bool aPjdotXaIw = false;
      bool ZpTmPHfxIm = false;
      string XLKXLufWxZ;
      string ZKtCkXyFod;
      string YmRWuaUSUL;
      string tSrornNcQC;
      string iuEtUPwZtn;
      string IfgOCksncj;
      string ZNBlfGSEKw;
      string KUoltciWBf;
      string dtXgCOkdlH;
      string tZAfcVtROO;
      string wqPydnpuUY;
      string CWlxFfoTjR;
      string UnSCBjUJJX;
      string iRImimeZDN;
      string XpINFXnCZw;
      string fZgxsIYMws;
      string TglwokOyOS;
      string APQVsefExd;
      string wRiMqJjKta;
      string NRcJtpEMXU;
      if(XLKXLufWxZ == wqPydnpuUY){IonHwPIKDN = true;}
      else if(wqPydnpuUY == XLKXLufWxZ){GQLWUVWeLr = true;}
      if(ZKtCkXyFod == CWlxFfoTjR){bTOSwByYEf = true;}
      else if(CWlxFfoTjR == ZKtCkXyFod){INKqhyGzpq = true;}
      if(YmRWuaUSUL == UnSCBjUJJX){ADDnEhmHbC = true;}
      else if(UnSCBjUJJX == YmRWuaUSUL){xybhTsxFdg = true;}
      if(tSrornNcQC == iRImimeZDN){aSgcUHdbQb = true;}
      else if(iRImimeZDN == tSrornNcQC){kodAEOSXOn = true;}
      if(iuEtUPwZtn == XpINFXnCZw){AYHfysCJMr = true;}
      else if(XpINFXnCZw == iuEtUPwZtn){YgcQGISgUA = true;}
      if(IfgOCksncj == fZgxsIYMws){reHrTEkACN = true;}
      else if(fZgxsIYMws == IfgOCksncj){rpQCqHncDa = true;}
      if(ZNBlfGSEKw == TglwokOyOS){cBiAmImlyo = true;}
      else if(TglwokOyOS == ZNBlfGSEKw){XRAeHTiJmT = true;}
      if(KUoltciWBf == APQVsefExd){XWIcfawXoK = true;}
      if(dtXgCOkdlH == wRiMqJjKta){edtiKuLoJP = true;}
      if(tZAfcVtROO == NRcJtpEMXU){VdYDyypHso = true;}
      while(APQVsefExd == KUoltciWBf){fikBRQVLaL = true;}
      while(wRiMqJjKta == wRiMqJjKta){aPjdotXaIw = true;}
      while(NRcJtpEMXU == NRcJtpEMXU){ZpTmPHfxIm = true;}
      if(IonHwPIKDN == true){IonHwPIKDN = false;}
      if(bTOSwByYEf == true){bTOSwByYEf = false;}
      if(ADDnEhmHbC == true){ADDnEhmHbC = false;}
      if(aSgcUHdbQb == true){aSgcUHdbQb = false;}
      if(AYHfysCJMr == true){AYHfysCJMr = false;}
      if(reHrTEkACN == true){reHrTEkACN = false;}
      if(cBiAmImlyo == true){cBiAmImlyo = false;}
      if(XWIcfawXoK == true){XWIcfawXoK = false;}
      if(edtiKuLoJP == true){edtiKuLoJP = false;}
      if(VdYDyypHso == true){VdYDyypHso = false;}
      if(GQLWUVWeLr == true){GQLWUVWeLr = false;}
      if(INKqhyGzpq == true){INKqhyGzpq = false;}
      if(xybhTsxFdg == true){xybhTsxFdg = false;}
      if(kodAEOSXOn == true){kodAEOSXOn = false;}
      if(YgcQGISgUA == true){YgcQGISgUA = false;}
      if(rpQCqHncDa == true){rpQCqHncDa = false;}
      if(XRAeHTiJmT == true){XRAeHTiJmT = false;}
      if(fikBRQVLaL == true){fikBRQVLaL = false;}
      if(aPjdotXaIw == true){aPjdotXaIw = false;}
      if(ZpTmPHfxIm == true){ZpTmPHfxIm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VVBGMNRJXT
{ 
  void ZikAsKiwlH()
  { 
      bool HzywyPFEuB = false;
      bool mZMjjQGlnk = false;
      bool mHbGKrAWoy = false;
      bool zpEDDdZBxB = false;
      bool gqVaTkbeUT = false;
      bool oQldFzWqkF = false;
      bool OhOwBxVIfF = false;
      bool pEolDulBmZ = false;
      bool QVCVIiDaxD = false;
      bool GiPqmzcYYW = false;
      bool PSyOdkaAaJ = false;
      bool NVDLorernS = false;
      bool stLbzHoxzD = false;
      bool SNbQKxWmrX = false;
      bool HDAmpjeECt = false;
      bool TjjGcUHWPV = false;
      bool udBWqAsmAq = false;
      bool UrAQLptXkO = false;
      bool bjtEjicVmp = false;
      bool pAXVbcBcwp = false;
      string yJIZVbMfAL;
      string YJHIiPweBd;
      string ckoAnqUoaz;
      string xngUyfuXWQ;
      string cgfybblpqO;
      string ycsBoNUHkd;
      string HXFBOjblJD;
      string UXIjAwEpXL;
      string EdyLAUuffk;
      string LmlrIEaejr;
      string AzgmtaTJAs;
      string IejZZdZsAt;
      string nwGXrgkPaw;
      string UZGfLExKRZ;
      string AkembfDMRe;
      string egdoDEsIuM;
      string oEhEXiYDNV;
      string gPbZtCQTwL;
      string cYxuQmuQbH;
      string KnOEjwDZOs;
      if(yJIZVbMfAL == AzgmtaTJAs){HzywyPFEuB = true;}
      else if(AzgmtaTJAs == yJIZVbMfAL){PSyOdkaAaJ = true;}
      if(YJHIiPweBd == IejZZdZsAt){mZMjjQGlnk = true;}
      else if(IejZZdZsAt == YJHIiPweBd){NVDLorernS = true;}
      if(ckoAnqUoaz == nwGXrgkPaw){mHbGKrAWoy = true;}
      else if(nwGXrgkPaw == ckoAnqUoaz){stLbzHoxzD = true;}
      if(xngUyfuXWQ == UZGfLExKRZ){zpEDDdZBxB = true;}
      else if(UZGfLExKRZ == xngUyfuXWQ){SNbQKxWmrX = true;}
      if(cgfybblpqO == AkembfDMRe){gqVaTkbeUT = true;}
      else if(AkembfDMRe == cgfybblpqO){HDAmpjeECt = true;}
      if(ycsBoNUHkd == egdoDEsIuM){oQldFzWqkF = true;}
      else if(egdoDEsIuM == ycsBoNUHkd){TjjGcUHWPV = true;}
      if(HXFBOjblJD == oEhEXiYDNV){OhOwBxVIfF = true;}
      else if(oEhEXiYDNV == HXFBOjblJD){udBWqAsmAq = true;}
      if(UXIjAwEpXL == gPbZtCQTwL){pEolDulBmZ = true;}
      if(EdyLAUuffk == cYxuQmuQbH){QVCVIiDaxD = true;}
      if(LmlrIEaejr == KnOEjwDZOs){GiPqmzcYYW = true;}
      while(gPbZtCQTwL == UXIjAwEpXL){UrAQLptXkO = true;}
      while(cYxuQmuQbH == cYxuQmuQbH){bjtEjicVmp = true;}
      while(KnOEjwDZOs == KnOEjwDZOs){pAXVbcBcwp = true;}
      if(HzywyPFEuB == true){HzywyPFEuB = false;}
      if(mZMjjQGlnk == true){mZMjjQGlnk = false;}
      if(mHbGKrAWoy == true){mHbGKrAWoy = false;}
      if(zpEDDdZBxB == true){zpEDDdZBxB = false;}
      if(gqVaTkbeUT == true){gqVaTkbeUT = false;}
      if(oQldFzWqkF == true){oQldFzWqkF = false;}
      if(OhOwBxVIfF == true){OhOwBxVIfF = false;}
      if(pEolDulBmZ == true){pEolDulBmZ = false;}
      if(QVCVIiDaxD == true){QVCVIiDaxD = false;}
      if(GiPqmzcYYW == true){GiPqmzcYYW = false;}
      if(PSyOdkaAaJ == true){PSyOdkaAaJ = false;}
      if(NVDLorernS == true){NVDLorernS = false;}
      if(stLbzHoxzD == true){stLbzHoxzD = false;}
      if(SNbQKxWmrX == true){SNbQKxWmrX = false;}
      if(HDAmpjeECt == true){HDAmpjeECt = false;}
      if(TjjGcUHWPV == true){TjjGcUHWPV = false;}
      if(udBWqAsmAq == true){udBWqAsmAq = false;}
      if(UrAQLptXkO == true){UrAQLptXkO = false;}
      if(bjtEjicVmp == true){bjtEjicVmp = false;}
      if(pAXVbcBcwp == true){pAXVbcBcwp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FZIZFZSCTL
{ 
  void THngzKipTL()
  { 
      bool JXKhaSNrJd = false;
      bool fplpOywset = false;
      bool wQNcMwyPlI = false;
      bool RCsJnujPTL = false;
      bool swkbmeYXDc = false;
      bool IuOaprJhUe = false;
      bool TyGBLdwbCT = false;
      bool OgYSBAelpg = false;
      bool WaLIzWnSSu = false;
      bool kBtoqtojPJ = false;
      bool ixUjObVuYp = false;
      bool MXqnIslyBo = false;
      bool odJHhMljbG = false;
      bool KuVgyYGbsX = false;
      bool AssbhMKGgy = false;
      bool IphaTEnNBC = false;
      bool plTReRBKpi = false;
      bool mJEcnwjgYU = false;
      bool CeDcyTMuMs = false;
      bool krZqhOYawQ = false;
      string uxoxxRMeRZ;
      string FeUtGrVkqe;
      string kcNPeWVlCQ;
      string DZEIWlcSze;
      string WFqICEDZbI;
      string ytddiSjYSa;
      string wZbBWfaMXU;
      string OClLHelENZ;
      string SuKtRIuZZE;
      string BDAXiwcplV;
      string dqBHswIRVD;
      string feLrIAPhiN;
      string jAlTSLCNcL;
      string BuSqwasCAV;
      string AcEWXVrHPh;
      string fuGXkcFhnh;
      string stnKBkMTwh;
      string HNhNNHwOwx;
      string TuxueGouFS;
      string VLORbFosVl;
      if(uxoxxRMeRZ == dqBHswIRVD){JXKhaSNrJd = true;}
      else if(dqBHswIRVD == uxoxxRMeRZ){ixUjObVuYp = true;}
      if(FeUtGrVkqe == feLrIAPhiN){fplpOywset = true;}
      else if(feLrIAPhiN == FeUtGrVkqe){MXqnIslyBo = true;}
      if(kcNPeWVlCQ == jAlTSLCNcL){wQNcMwyPlI = true;}
      else if(jAlTSLCNcL == kcNPeWVlCQ){odJHhMljbG = true;}
      if(DZEIWlcSze == BuSqwasCAV){RCsJnujPTL = true;}
      else if(BuSqwasCAV == DZEIWlcSze){KuVgyYGbsX = true;}
      if(WFqICEDZbI == AcEWXVrHPh){swkbmeYXDc = true;}
      else if(AcEWXVrHPh == WFqICEDZbI){AssbhMKGgy = true;}
      if(ytddiSjYSa == fuGXkcFhnh){IuOaprJhUe = true;}
      else if(fuGXkcFhnh == ytddiSjYSa){IphaTEnNBC = true;}
      if(wZbBWfaMXU == stnKBkMTwh){TyGBLdwbCT = true;}
      else if(stnKBkMTwh == wZbBWfaMXU){plTReRBKpi = true;}
      if(OClLHelENZ == HNhNNHwOwx){OgYSBAelpg = true;}
      if(SuKtRIuZZE == TuxueGouFS){WaLIzWnSSu = true;}
      if(BDAXiwcplV == VLORbFosVl){kBtoqtojPJ = true;}
      while(HNhNNHwOwx == OClLHelENZ){mJEcnwjgYU = true;}
      while(TuxueGouFS == TuxueGouFS){CeDcyTMuMs = true;}
      while(VLORbFosVl == VLORbFosVl){krZqhOYawQ = true;}
      if(JXKhaSNrJd == true){JXKhaSNrJd = false;}
      if(fplpOywset == true){fplpOywset = false;}
      if(wQNcMwyPlI == true){wQNcMwyPlI = false;}
      if(RCsJnujPTL == true){RCsJnujPTL = false;}
      if(swkbmeYXDc == true){swkbmeYXDc = false;}
      if(IuOaprJhUe == true){IuOaprJhUe = false;}
      if(TyGBLdwbCT == true){TyGBLdwbCT = false;}
      if(OgYSBAelpg == true){OgYSBAelpg = false;}
      if(WaLIzWnSSu == true){WaLIzWnSSu = false;}
      if(kBtoqtojPJ == true){kBtoqtojPJ = false;}
      if(ixUjObVuYp == true){ixUjObVuYp = false;}
      if(MXqnIslyBo == true){MXqnIslyBo = false;}
      if(odJHhMljbG == true){odJHhMljbG = false;}
      if(KuVgyYGbsX == true){KuVgyYGbsX = false;}
      if(AssbhMKGgy == true){AssbhMKGgy = false;}
      if(IphaTEnNBC == true){IphaTEnNBC = false;}
      if(plTReRBKpi == true){plTReRBKpi = false;}
      if(mJEcnwjgYU == true){mJEcnwjgYU = false;}
      if(CeDcyTMuMs == true){CeDcyTMuMs = false;}
      if(krZqhOYawQ == true){krZqhOYawQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TMDPCOXUIR
{ 
  void TMpKtcoPzm()
  { 
      bool NQVHoozNba = false;
      bool AjieXyoIgg = false;
      bool mfFNMKNcFz = false;
      bool QsEKfDndFg = false;
      bool ihiCWBXVyw = false;
      bool rOmAggKHte = false;
      bool bWIcJGeXyU = false;
      bool JLDAxFwCqL = false;
      bool mreIGBGDdz = false;
      bool rfiaELYGrP = false;
      bool VzWdlgLlDb = false;
      bool jHQiqjrAVI = false;
      bool Aatybcbcuk = false;
      bool fpKapnUAWZ = false;
      bool pTACPjPAiT = false;
      bool TYkjPtEYBI = false;
      bool EiqRutxpsD = false;
      bool PqcuSfaqiq = false;
      bool NbsaRHEZLu = false;
      bool iuyNUGciHV = false;
      string hPlULDUfSF;
      string gcTuRSZYBn;
      string DPhqQuwlnq;
      string plsoPzVgZD;
      string YGqNWhicoK;
      string QQFstRguEP;
      string GirbOtjdfR;
      string wrzyPwYTTh;
      string LSwcZYgAux;
      string SabJwpNOzb;
      string xFxXNXQGcx;
      string sMaVEnlOBo;
      string NjiizUQpCZ;
      string hJUqkGVYPC;
      string IZWxDFAGEH;
      string DzNJNNVOXs;
      string HaDDPirikx;
      string RNzzgmMles;
      string UJkuViwLcW;
      string kHAWthWTgT;
      if(hPlULDUfSF == xFxXNXQGcx){NQVHoozNba = true;}
      else if(xFxXNXQGcx == hPlULDUfSF){VzWdlgLlDb = true;}
      if(gcTuRSZYBn == sMaVEnlOBo){AjieXyoIgg = true;}
      else if(sMaVEnlOBo == gcTuRSZYBn){jHQiqjrAVI = true;}
      if(DPhqQuwlnq == NjiizUQpCZ){mfFNMKNcFz = true;}
      else if(NjiizUQpCZ == DPhqQuwlnq){Aatybcbcuk = true;}
      if(plsoPzVgZD == hJUqkGVYPC){QsEKfDndFg = true;}
      else if(hJUqkGVYPC == plsoPzVgZD){fpKapnUAWZ = true;}
      if(YGqNWhicoK == IZWxDFAGEH){ihiCWBXVyw = true;}
      else if(IZWxDFAGEH == YGqNWhicoK){pTACPjPAiT = true;}
      if(QQFstRguEP == DzNJNNVOXs){rOmAggKHte = true;}
      else if(DzNJNNVOXs == QQFstRguEP){TYkjPtEYBI = true;}
      if(GirbOtjdfR == HaDDPirikx){bWIcJGeXyU = true;}
      else if(HaDDPirikx == GirbOtjdfR){EiqRutxpsD = true;}
      if(wrzyPwYTTh == RNzzgmMles){JLDAxFwCqL = true;}
      if(LSwcZYgAux == UJkuViwLcW){mreIGBGDdz = true;}
      if(SabJwpNOzb == kHAWthWTgT){rfiaELYGrP = true;}
      while(RNzzgmMles == wrzyPwYTTh){PqcuSfaqiq = true;}
      while(UJkuViwLcW == UJkuViwLcW){NbsaRHEZLu = true;}
      while(kHAWthWTgT == kHAWthWTgT){iuyNUGciHV = true;}
      if(NQVHoozNba == true){NQVHoozNba = false;}
      if(AjieXyoIgg == true){AjieXyoIgg = false;}
      if(mfFNMKNcFz == true){mfFNMKNcFz = false;}
      if(QsEKfDndFg == true){QsEKfDndFg = false;}
      if(ihiCWBXVyw == true){ihiCWBXVyw = false;}
      if(rOmAggKHte == true){rOmAggKHte = false;}
      if(bWIcJGeXyU == true){bWIcJGeXyU = false;}
      if(JLDAxFwCqL == true){JLDAxFwCqL = false;}
      if(mreIGBGDdz == true){mreIGBGDdz = false;}
      if(rfiaELYGrP == true){rfiaELYGrP = false;}
      if(VzWdlgLlDb == true){VzWdlgLlDb = false;}
      if(jHQiqjrAVI == true){jHQiqjrAVI = false;}
      if(Aatybcbcuk == true){Aatybcbcuk = false;}
      if(fpKapnUAWZ == true){fpKapnUAWZ = false;}
      if(pTACPjPAiT == true){pTACPjPAiT = false;}
      if(TYkjPtEYBI == true){TYkjPtEYBI = false;}
      if(EiqRutxpsD == true){EiqRutxpsD = false;}
      if(PqcuSfaqiq == true){PqcuSfaqiq = false;}
      if(NbsaRHEZLu == true){NbsaRHEZLu = false;}
      if(iuyNUGciHV == true){iuyNUGciHV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LZAMSHRPRO
{ 
  void xdhPdrdlIU()
  { 
      bool TdBPItMEHJ = false;
      bool KByZcWrznz = false;
      bool EOqfBIgIix = false;
      bool LliKakHVoz = false;
      bool pzggdzHqUe = false;
      bool xlUoMFlUOA = false;
      bool NEUJyXRnyq = false;
      bool PVJnIEgKCB = false;
      bool AomDAYQsxU = false;
      bool ylHokldXiF = false;
      bool hTrdPabfgH = false;
      bool YbSMzXQQIY = false;
      bool HYpdrcOTDW = false;
      bool ZJbwTgwJnZ = false;
      bool xkMpwWTtpM = false;
      bool VMOJyIdOkm = false;
      bool LHcJhPAVsR = false;
      bool bHciaVLAgV = false;
      bool ITdpBMtRyK = false;
      bool DgXBNoICIg = false;
      string eFQOdGwJfh;
      string toNCFXsjHA;
      string PakDSlFnAS;
      string dLtfddEelT;
      string kaXDUjWzOn;
      string YeIjOETMur;
      string AIJNEiugYb;
      string TNxnPnDhhh;
      string PFYLszDKRY;
      string JqitScRJzl;
      string ooZmUKgTUZ;
      string AleNcujxTE;
      string fjPzSbeDVl;
      string WsiwsZfkph;
      string SipqYXMVRX;
      string sTotFEYZUr;
      string fcxhCHDhUC;
      string OyGklwtXau;
      string PIkysDDopn;
      string BGQyCokIoQ;
      if(eFQOdGwJfh == ooZmUKgTUZ){TdBPItMEHJ = true;}
      else if(ooZmUKgTUZ == eFQOdGwJfh){hTrdPabfgH = true;}
      if(toNCFXsjHA == AleNcujxTE){KByZcWrznz = true;}
      else if(AleNcujxTE == toNCFXsjHA){YbSMzXQQIY = true;}
      if(PakDSlFnAS == fjPzSbeDVl){EOqfBIgIix = true;}
      else if(fjPzSbeDVl == PakDSlFnAS){HYpdrcOTDW = true;}
      if(dLtfddEelT == WsiwsZfkph){LliKakHVoz = true;}
      else if(WsiwsZfkph == dLtfddEelT){ZJbwTgwJnZ = true;}
      if(kaXDUjWzOn == SipqYXMVRX){pzggdzHqUe = true;}
      else if(SipqYXMVRX == kaXDUjWzOn){xkMpwWTtpM = true;}
      if(YeIjOETMur == sTotFEYZUr){xlUoMFlUOA = true;}
      else if(sTotFEYZUr == YeIjOETMur){VMOJyIdOkm = true;}
      if(AIJNEiugYb == fcxhCHDhUC){NEUJyXRnyq = true;}
      else if(fcxhCHDhUC == AIJNEiugYb){LHcJhPAVsR = true;}
      if(TNxnPnDhhh == OyGklwtXau){PVJnIEgKCB = true;}
      if(PFYLszDKRY == PIkysDDopn){AomDAYQsxU = true;}
      if(JqitScRJzl == BGQyCokIoQ){ylHokldXiF = true;}
      while(OyGklwtXau == TNxnPnDhhh){bHciaVLAgV = true;}
      while(PIkysDDopn == PIkysDDopn){ITdpBMtRyK = true;}
      while(BGQyCokIoQ == BGQyCokIoQ){DgXBNoICIg = true;}
      if(TdBPItMEHJ == true){TdBPItMEHJ = false;}
      if(KByZcWrznz == true){KByZcWrznz = false;}
      if(EOqfBIgIix == true){EOqfBIgIix = false;}
      if(LliKakHVoz == true){LliKakHVoz = false;}
      if(pzggdzHqUe == true){pzggdzHqUe = false;}
      if(xlUoMFlUOA == true){xlUoMFlUOA = false;}
      if(NEUJyXRnyq == true){NEUJyXRnyq = false;}
      if(PVJnIEgKCB == true){PVJnIEgKCB = false;}
      if(AomDAYQsxU == true){AomDAYQsxU = false;}
      if(ylHokldXiF == true){ylHokldXiF = false;}
      if(hTrdPabfgH == true){hTrdPabfgH = false;}
      if(YbSMzXQQIY == true){YbSMzXQQIY = false;}
      if(HYpdrcOTDW == true){HYpdrcOTDW = false;}
      if(ZJbwTgwJnZ == true){ZJbwTgwJnZ = false;}
      if(xkMpwWTtpM == true){xkMpwWTtpM = false;}
      if(VMOJyIdOkm == true){VMOJyIdOkm = false;}
      if(LHcJhPAVsR == true){LHcJhPAVsR = false;}
      if(bHciaVLAgV == true){bHciaVLAgV = false;}
      if(ITdpBMtRyK == true){ITdpBMtRyK = false;}
      if(DgXBNoICIg == true){DgXBNoICIg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DBDBAGRUBY
{ 
  void NSPHSRxapi()
  { 
      bool QKQgwgRgku = false;
      bool ZsVBNCbewi = false;
      bool wVYcHzLDhg = false;
      bool IsuSjVzwZi = false;
      bool bnxQLJuSGO = false;
      bool SUDlVtknZw = false;
      bool UOzDlgxCQq = false;
      bool CfENGIYHQy = false;
      bool ErxSOmpJxo = false;
      bool jLWcNNosdd = false;
      bool LsBOMmQoeN = false;
      bool VcWarbQfoz = false;
      bool qnEbHqIbzr = false;
      bool TfdmmKqhGa = false;
      bool WAdjSGnwjk = false;
      bool wIDemXnYHV = false;
      bool enpmtpzjng = false;
      bool kiZNbpJUJA = false;
      bool CMqOwKbyzO = false;
      bool WSZjwhKqoc = false;
      string JlPHEgBwyD;
      string ymXLFuqIVu;
      string LWtlKtuHaM;
      string sDeroNYwXl;
      string GxDEIfGxOq;
      string LNSdclqdxJ;
      string lsUlKuHfWr;
      string WujioNTpcd;
      string myriBekBOC;
      string VuyNAMcRsN;
      string YaaWUPcjoP;
      string SBASWnAlke;
      string JFQTVawVib;
      string kBwPEMWUNk;
      string CBMziUueqM;
      string LpgODSKGBs;
      string TGAMdQEjOJ;
      string QeXzcIsQkA;
      string fQdVPtUhLk;
      string CQTTRuAzVR;
      if(JlPHEgBwyD == YaaWUPcjoP){QKQgwgRgku = true;}
      else if(YaaWUPcjoP == JlPHEgBwyD){LsBOMmQoeN = true;}
      if(ymXLFuqIVu == SBASWnAlke){ZsVBNCbewi = true;}
      else if(SBASWnAlke == ymXLFuqIVu){VcWarbQfoz = true;}
      if(LWtlKtuHaM == JFQTVawVib){wVYcHzLDhg = true;}
      else if(JFQTVawVib == LWtlKtuHaM){qnEbHqIbzr = true;}
      if(sDeroNYwXl == kBwPEMWUNk){IsuSjVzwZi = true;}
      else if(kBwPEMWUNk == sDeroNYwXl){TfdmmKqhGa = true;}
      if(GxDEIfGxOq == CBMziUueqM){bnxQLJuSGO = true;}
      else if(CBMziUueqM == GxDEIfGxOq){WAdjSGnwjk = true;}
      if(LNSdclqdxJ == LpgODSKGBs){SUDlVtknZw = true;}
      else if(LpgODSKGBs == LNSdclqdxJ){wIDemXnYHV = true;}
      if(lsUlKuHfWr == TGAMdQEjOJ){UOzDlgxCQq = true;}
      else if(TGAMdQEjOJ == lsUlKuHfWr){enpmtpzjng = true;}
      if(WujioNTpcd == QeXzcIsQkA){CfENGIYHQy = true;}
      if(myriBekBOC == fQdVPtUhLk){ErxSOmpJxo = true;}
      if(VuyNAMcRsN == CQTTRuAzVR){jLWcNNosdd = true;}
      while(QeXzcIsQkA == WujioNTpcd){kiZNbpJUJA = true;}
      while(fQdVPtUhLk == fQdVPtUhLk){CMqOwKbyzO = true;}
      while(CQTTRuAzVR == CQTTRuAzVR){WSZjwhKqoc = true;}
      if(QKQgwgRgku == true){QKQgwgRgku = false;}
      if(ZsVBNCbewi == true){ZsVBNCbewi = false;}
      if(wVYcHzLDhg == true){wVYcHzLDhg = false;}
      if(IsuSjVzwZi == true){IsuSjVzwZi = false;}
      if(bnxQLJuSGO == true){bnxQLJuSGO = false;}
      if(SUDlVtknZw == true){SUDlVtknZw = false;}
      if(UOzDlgxCQq == true){UOzDlgxCQq = false;}
      if(CfENGIYHQy == true){CfENGIYHQy = false;}
      if(ErxSOmpJxo == true){ErxSOmpJxo = false;}
      if(jLWcNNosdd == true){jLWcNNosdd = false;}
      if(LsBOMmQoeN == true){LsBOMmQoeN = false;}
      if(VcWarbQfoz == true){VcWarbQfoz = false;}
      if(qnEbHqIbzr == true){qnEbHqIbzr = false;}
      if(TfdmmKqhGa == true){TfdmmKqhGa = false;}
      if(WAdjSGnwjk == true){WAdjSGnwjk = false;}
      if(wIDemXnYHV == true){wIDemXnYHV = false;}
      if(enpmtpzjng == true){enpmtpzjng = false;}
      if(kiZNbpJUJA == true){kiZNbpJUJA = false;}
      if(CMqOwKbyzO == true){CMqOwKbyzO = false;}
      if(WSZjwhKqoc == true){WSZjwhKqoc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZGLVHABBXP
{ 
  void JQCQpikkTe()
  { 
      bool iDoUeeSDaL = false;
      bool JUIsCMpHAe = false;
      bool iVoRcoGDks = false;
      bool ekXyUutXTd = false;
      bool jynBWOihOE = false;
      bool WxmTeNOXqo = false;
      bool YPRggXxKXG = false;
      bool RSmVukgnuO = false;
      bool FXogVhxDTG = false;
      bool gWfdEUfGUy = false;
      bool RYKImEJQYs = false;
      bool gaccjBakKz = false;
      bool asqQYulJRZ = false;
      bool EaSwwgMgsR = false;
      bool XgeZZGsDtD = false;
      bool tuuVXXhsir = false;
      bool RAzznFHffD = false;
      bool nsqsasOQpS = false;
      bool BiONeJexYX = false;
      bool yTxBzXhekT = false;
      string frQmGhxYYN;
      string jrQduCtiWM;
      string HEbHNpntKY;
      string GNwBVTbXmC;
      string WoXrKyOqyi;
      string pDlUraQJZQ;
      string sDOAGVwPHb;
      string ZVwUpRgixO;
      string axwaiDbbIt;
      string CSyWITaXkn;
      string BziWIUHReZ;
      string thLKowGmQD;
      string sUGMYGXYLV;
      string qIxINbOYSN;
      string wKwiATHmgM;
      string MmGhugrVxB;
      string whGJikkDxM;
      string hhUCHiXXME;
      string zjryIDCONf;
      string jraQQNEmzO;
      if(frQmGhxYYN == BziWIUHReZ){iDoUeeSDaL = true;}
      else if(BziWIUHReZ == frQmGhxYYN){RYKImEJQYs = true;}
      if(jrQduCtiWM == thLKowGmQD){JUIsCMpHAe = true;}
      else if(thLKowGmQD == jrQduCtiWM){gaccjBakKz = true;}
      if(HEbHNpntKY == sUGMYGXYLV){iVoRcoGDks = true;}
      else if(sUGMYGXYLV == HEbHNpntKY){asqQYulJRZ = true;}
      if(GNwBVTbXmC == qIxINbOYSN){ekXyUutXTd = true;}
      else if(qIxINbOYSN == GNwBVTbXmC){EaSwwgMgsR = true;}
      if(WoXrKyOqyi == wKwiATHmgM){jynBWOihOE = true;}
      else if(wKwiATHmgM == WoXrKyOqyi){XgeZZGsDtD = true;}
      if(pDlUraQJZQ == MmGhugrVxB){WxmTeNOXqo = true;}
      else if(MmGhugrVxB == pDlUraQJZQ){tuuVXXhsir = true;}
      if(sDOAGVwPHb == whGJikkDxM){YPRggXxKXG = true;}
      else if(whGJikkDxM == sDOAGVwPHb){RAzznFHffD = true;}
      if(ZVwUpRgixO == hhUCHiXXME){RSmVukgnuO = true;}
      if(axwaiDbbIt == zjryIDCONf){FXogVhxDTG = true;}
      if(CSyWITaXkn == jraQQNEmzO){gWfdEUfGUy = true;}
      while(hhUCHiXXME == ZVwUpRgixO){nsqsasOQpS = true;}
      while(zjryIDCONf == zjryIDCONf){BiONeJexYX = true;}
      while(jraQQNEmzO == jraQQNEmzO){yTxBzXhekT = true;}
      if(iDoUeeSDaL == true){iDoUeeSDaL = false;}
      if(JUIsCMpHAe == true){JUIsCMpHAe = false;}
      if(iVoRcoGDks == true){iVoRcoGDks = false;}
      if(ekXyUutXTd == true){ekXyUutXTd = false;}
      if(jynBWOihOE == true){jynBWOihOE = false;}
      if(WxmTeNOXqo == true){WxmTeNOXqo = false;}
      if(YPRggXxKXG == true){YPRggXxKXG = false;}
      if(RSmVukgnuO == true){RSmVukgnuO = false;}
      if(FXogVhxDTG == true){FXogVhxDTG = false;}
      if(gWfdEUfGUy == true){gWfdEUfGUy = false;}
      if(RYKImEJQYs == true){RYKImEJQYs = false;}
      if(gaccjBakKz == true){gaccjBakKz = false;}
      if(asqQYulJRZ == true){asqQYulJRZ = false;}
      if(EaSwwgMgsR == true){EaSwwgMgsR = false;}
      if(XgeZZGsDtD == true){XgeZZGsDtD = false;}
      if(tuuVXXhsir == true){tuuVXXhsir = false;}
      if(RAzznFHffD == true){RAzznFHffD = false;}
      if(nsqsasOQpS == true){nsqsasOQpS = false;}
      if(BiONeJexYX == true){BiONeJexYX = false;}
      if(yTxBzXhekT == true){yTxBzXhekT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UXTLENSQQF
{ 
  void bSxpgXPFYC()
  { 
      bool aswTHSlLkH = false;
      bool BYyefqyHQE = false;
      bool LKMdXxxuIU = false;
      bool CCLfCMFKgW = false;
      bool HfPryqksQL = false;
      bool JUycWQgRuJ = false;
      bool UqDPFyMScS = false;
      bool knZtwfuTeg = false;
      bool MEewLhEiJk = false;
      bool fnOXBQbzmA = false;
      bool eSQxZVtEfp = false;
      bool VMlOxQLGEW = false;
      bool tcIqmxYCrf = false;
      bool EugeCtnhWp = false;
      bool nADSPTBAak = false;
      bool EUuPFBJYJc = false;
      bool wqLzlZeGMD = false;
      bool cdjNitZpbT = false;
      bool uXbGaiAQYA = false;
      bool jOXsswnDfo = false;
      string wMwNnIcSKF;
      string UbkNNICrzl;
      string yoqSlsWOHn;
      string mTaHKilAZD;
      string JRyxpJTOFX;
      string WjVPDHUcau;
      string kOLVSAAcCe;
      string WBSubfptbc;
      string YHIjQDyLDD;
      string NIYeRuGbdo;
      string IqLZAVRZnX;
      string RaAyVcFbFP;
      string CoYzQNcmdf;
      string YNPmThwhiu;
      string lXWfkmHaIo;
      string peWOlTRMJl;
      string rdwHyDLNen;
      string gWrKcdRsNd;
      string GBenptqAAA;
      string PiYwCHbPgh;
      if(wMwNnIcSKF == IqLZAVRZnX){aswTHSlLkH = true;}
      else if(IqLZAVRZnX == wMwNnIcSKF){eSQxZVtEfp = true;}
      if(UbkNNICrzl == RaAyVcFbFP){BYyefqyHQE = true;}
      else if(RaAyVcFbFP == UbkNNICrzl){VMlOxQLGEW = true;}
      if(yoqSlsWOHn == CoYzQNcmdf){LKMdXxxuIU = true;}
      else if(CoYzQNcmdf == yoqSlsWOHn){tcIqmxYCrf = true;}
      if(mTaHKilAZD == YNPmThwhiu){CCLfCMFKgW = true;}
      else if(YNPmThwhiu == mTaHKilAZD){EugeCtnhWp = true;}
      if(JRyxpJTOFX == lXWfkmHaIo){HfPryqksQL = true;}
      else if(lXWfkmHaIo == JRyxpJTOFX){nADSPTBAak = true;}
      if(WjVPDHUcau == peWOlTRMJl){JUycWQgRuJ = true;}
      else if(peWOlTRMJl == WjVPDHUcau){EUuPFBJYJc = true;}
      if(kOLVSAAcCe == rdwHyDLNen){UqDPFyMScS = true;}
      else if(rdwHyDLNen == kOLVSAAcCe){wqLzlZeGMD = true;}
      if(WBSubfptbc == gWrKcdRsNd){knZtwfuTeg = true;}
      if(YHIjQDyLDD == GBenptqAAA){MEewLhEiJk = true;}
      if(NIYeRuGbdo == PiYwCHbPgh){fnOXBQbzmA = true;}
      while(gWrKcdRsNd == WBSubfptbc){cdjNitZpbT = true;}
      while(GBenptqAAA == GBenptqAAA){uXbGaiAQYA = true;}
      while(PiYwCHbPgh == PiYwCHbPgh){jOXsswnDfo = true;}
      if(aswTHSlLkH == true){aswTHSlLkH = false;}
      if(BYyefqyHQE == true){BYyefqyHQE = false;}
      if(LKMdXxxuIU == true){LKMdXxxuIU = false;}
      if(CCLfCMFKgW == true){CCLfCMFKgW = false;}
      if(HfPryqksQL == true){HfPryqksQL = false;}
      if(JUycWQgRuJ == true){JUycWQgRuJ = false;}
      if(UqDPFyMScS == true){UqDPFyMScS = false;}
      if(knZtwfuTeg == true){knZtwfuTeg = false;}
      if(MEewLhEiJk == true){MEewLhEiJk = false;}
      if(fnOXBQbzmA == true){fnOXBQbzmA = false;}
      if(eSQxZVtEfp == true){eSQxZVtEfp = false;}
      if(VMlOxQLGEW == true){VMlOxQLGEW = false;}
      if(tcIqmxYCrf == true){tcIqmxYCrf = false;}
      if(EugeCtnhWp == true){EugeCtnhWp = false;}
      if(nADSPTBAak == true){nADSPTBAak = false;}
      if(EUuPFBJYJc == true){EUuPFBJYJc = false;}
      if(wqLzlZeGMD == true){wqLzlZeGMD = false;}
      if(cdjNitZpbT == true){cdjNitZpbT = false;}
      if(uXbGaiAQYA == true){uXbGaiAQYA = false;}
      if(jOXsswnDfo == true){jOXsswnDfo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONEOFZILRR
{ 
  void qYVJWizoGF()
  { 
      bool wyillYGRps = false;
      bool XCPdcZnoTm = false;
      bool gWygpFwHLP = false;
      bool sFFUgLLhdl = false;
      bool BqfTkOeUxm = false;
      bool HsLuEYABwf = false;
      bool czGaASxuxQ = false;
      bool NFLhkoqdub = false;
      bool abJXHzsKPI = false;
      bool LKlxJCjETS = false;
      bool QjXgZChdKO = false;
      bool gVFUFBpiSA = false;
      bool ZmfnFDSNYh = false;
      bool FmKcKqDcyF = false;
      bool QPAAaoERrI = false;
      bool MBkSsdDiaV = false;
      bool iUFbJsLcJO = false;
      bool xNkNiKmeNQ = false;
      bool yAVPVDBrjf = false;
      bool mUBbVwJXqh = false;
      string JEnwqKQYuP;
      string gNkBpqfNCI;
      string nXxYILWhER;
      string XQpxDOSZos;
      string FFaHCfuBBg;
      string uwSQalHPnf;
      string mhTcqPXmya;
      string YGYIDixoVc;
      string PUfWWbyYVQ;
      string HDkJFWkxQm;
      string IHDZIoXJMr;
      string oRsLPSBwGO;
      string RyQgSUUODg;
      string xzXhTIRGOh;
      string EoMcapJZtm;
      string UnpBVJqVHn;
      string TIFfuosKqH;
      string BuhYKblnGc;
      string KtUPLIIWMJ;
      string RuzaNuifhk;
      if(JEnwqKQYuP == IHDZIoXJMr){wyillYGRps = true;}
      else if(IHDZIoXJMr == JEnwqKQYuP){QjXgZChdKO = true;}
      if(gNkBpqfNCI == oRsLPSBwGO){XCPdcZnoTm = true;}
      else if(oRsLPSBwGO == gNkBpqfNCI){gVFUFBpiSA = true;}
      if(nXxYILWhER == RyQgSUUODg){gWygpFwHLP = true;}
      else if(RyQgSUUODg == nXxYILWhER){ZmfnFDSNYh = true;}
      if(XQpxDOSZos == xzXhTIRGOh){sFFUgLLhdl = true;}
      else if(xzXhTIRGOh == XQpxDOSZos){FmKcKqDcyF = true;}
      if(FFaHCfuBBg == EoMcapJZtm){BqfTkOeUxm = true;}
      else if(EoMcapJZtm == FFaHCfuBBg){QPAAaoERrI = true;}
      if(uwSQalHPnf == UnpBVJqVHn){HsLuEYABwf = true;}
      else if(UnpBVJqVHn == uwSQalHPnf){MBkSsdDiaV = true;}
      if(mhTcqPXmya == TIFfuosKqH){czGaASxuxQ = true;}
      else if(TIFfuosKqH == mhTcqPXmya){iUFbJsLcJO = true;}
      if(YGYIDixoVc == BuhYKblnGc){NFLhkoqdub = true;}
      if(PUfWWbyYVQ == KtUPLIIWMJ){abJXHzsKPI = true;}
      if(HDkJFWkxQm == RuzaNuifhk){LKlxJCjETS = true;}
      while(BuhYKblnGc == YGYIDixoVc){xNkNiKmeNQ = true;}
      while(KtUPLIIWMJ == KtUPLIIWMJ){yAVPVDBrjf = true;}
      while(RuzaNuifhk == RuzaNuifhk){mUBbVwJXqh = true;}
      if(wyillYGRps == true){wyillYGRps = false;}
      if(XCPdcZnoTm == true){XCPdcZnoTm = false;}
      if(gWygpFwHLP == true){gWygpFwHLP = false;}
      if(sFFUgLLhdl == true){sFFUgLLhdl = false;}
      if(BqfTkOeUxm == true){BqfTkOeUxm = false;}
      if(HsLuEYABwf == true){HsLuEYABwf = false;}
      if(czGaASxuxQ == true){czGaASxuxQ = false;}
      if(NFLhkoqdub == true){NFLhkoqdub = false;}
      if(abJXHzsKPI == true){abJXHzsKPI = false;}
      if(LKlxJCjETS == true){LKlxJCjETS = false;}
      if(QjXgZChdKO == true){QjXgZChdKO = false;}
      if(gVFUFBpiSA == true){gVFUFBpiSA = false;}
      if(ZmfnFDSNYh == true){ZmfnFDSNYh = false;}
      if(FmKcKqDcyF == true){FmKcKqDcyF = false;}
      if(QPAAaoERrI == true){QPAAaoERrI = false;}
      if(MBkSsdDiaV == true){MBkSsdDiaV = false;}
      if(iUFbJsLcJO == true){iUFbJsLcJO = false;}
      if(xNkNiKmeNQ == true){xNkNiKmeNQ = false;}
      if(yAVPVDBrjf == true){yAVPVDBrjf = false;}
      if(mUBbVwJXqh == true){mUBbVwJXqh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VEEVAPTDPQ
{ 
  void OSYibUZHrR()
  { 
      bool plpTIfoGwS = false;
      bool NUVFcUlFhx = false;
      bool VUGnsEwUHp = false;
      bool OlwewQUWzq = false;
      bool BzMBlKaiiV = false;
      bool TcfPzVeBaE = false;
      bool iUzFDbYqIL = false;
      bool zPFpuWHEBh = false;
      bool dNlkWlFgfa = false;
      bool lSwuHgzGyK = false;
      bool liZWVEWoUb = false;
      bool NaArZVhNiQ = false;
      bool WqKgZfTJiN = false;
      bool XBGqwtmOOS = false;
      bool OQLEMLSDVk = false;
      bool ykXgmtYsxo = false;
      bool jNFGEMTJwe = false;
      bool iTzQCGfGTN = false;
      bool NPnyOlcYDB = false;
      bool VsRZhBKEAA = false;
      string srlAmHlqxJ;
      string ltgqRYCcsu;
      string TVidCEwock;
      string cNSRHJheNs;
      string cJlGiHEFIn;
      string rdiJMWIHxi;
      string LwNMfYbPiI;
      string qWPASJjcut;
      string zpforzeJEk;
      string AZhdgfuYZK;
      string foVAxVOhqD;
      string mfMDjVQYUg;
      string tRKyHQokTl;
      string OKCkOKTfrW;
      string jwSBxTNdtK;
      string PWEsPNdWrf;
      string fdOEobdanZ;
      string BjgyxxzJAm;
      string DKqIWqFIUA;
      string fwnLpGhNMV;
      if(srlAmHlqxJ == foVAxVOhqD){plpTIfoGwS = true;}
      else if(foVAxVOhqD == srlAmHlqxJ){liZWVEWoUb = true;}
      if(ltgqRYCcsu == mfMDjVQYUg){NUVFcUlFhx = true;}
      else if(mfMDjVQYUg == ltgqRYCcsu){NaArZVhNiQ = true;}
      if(TVidCEwock == tRKyHQokTl){VUGnsEwUHp = true;}
      else if(tRKyHQokTl == TVidCEwock){WqKgZfTJiN = true;}
      if(cNSRHJheNs == OKCkOKTfrW){OlwewQUWzq = true;}
      else if(OKCkOKTfrW == cNSRHJheNs){XBGqwtmOOS = true;}
      if(cJlGiHEFIn == jwSBxTNdtK){BzMBlKaiiV = true;}
      else if(jwSBxTNdtK == cJlGiHEFIn){OQLEMLSDVk = true;}
      if(rdiJMWIHxi == PWEsPNdWrf){TcfPzVeBaE = true;}
      else if(PWEsPNdWrf == rdiJMWIHxi){ykXgmtYsxo = true;}
      if(LwNMfYbPiI == fdOEobdanZ){iUzFDbYqIL = true;}
      else if(fdOEobdanZ == LwNMfYbPiI){jNFGEMTJwe = true;}
      if(qWPASJjcut == BjgyxxzJAm){zPFpuWHEBh = true;}
      if(zpforzeJEk == DKqIWqFIUA){dNlkWlFgfa = true;}
      if(AZhdgfuYZK == fwnLpGhNMV){lSwuHgzGyK = true;}
      while(BjgyxxzJAm == qWPASJjcut){iTzQCGfGTN = true;}
      while(DKqIWqFIUA == DKqIWqFIUA){NPnyOlcYDB = true;}
      while(fwnLpGhNMV == fwnLpGhNMV){VsRZhBKEAA = true;}
      if(plpTIfoGwS == true){plpTIfoGwS = false;}
      if(NUVFcUlFhx == true){NUVFcUlFhx = false;}
      if(VUGnsEwUHp == true){VUGnsEwUHp = false;}
      if(OlwewQUWzq == true){OlwewQUWzq = false;}
      if(BzMBlKaiiV == true){BzMBlKaiiV = false;}
      if(TcfPzVeBaE == true){TcfPzVeBaE = false;}
      if(iUzFDbYqIL == true){iUzFDbYqIL = false;}
      if(zPFpuWHEBh == true){zPFpuWHEBh = false;}
      if(dNlkWlFgfa == true){dNlkWlFgfa = false;}
      if(lSwuHgzGyK == true){lSwuHgzGyK = false;}
      if(liZWVEWoUb == true){liZWVEWoUb = false;}
      if(NaArZVhNiQ == true){NaArZVhNiQ = false;}
      if(WqKgZfTJiN == true){WqKgZfTJiN = false;}
      if(XBGqwtmOOS == true){XBGqwtmOOS = false;}
      if(OQLEMLSDVk == true){OQLEMLSDVk = false;}
      if(ykXgmtYsxo == true){ykXgmtYsxo = false;}
      if(jNFGEMTJwe == true){jNFGEMTJwe = false;}
      if(iTzQCGfGTN == true){iTzQCGfGTN = false;}
      if(NPnyOlcYDB == true){NPnyOlcYDB = false;}
      if(VsRZhBKEAA == true){VsRZhBKEAA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GLIDZCFKRC
{ 
  void jjEuMtkaNH()
  { 
      bool xLMIDnfbbO = false;
      bool NNGYIKxscW = false;
      bool EondopwhZb = false;
      bool bpZOFBNsEL = false;
      bool dEzsngskJB = false;
      bool qqBZfHXhTM = false;
      bool rxCzmXnrSH = false;
      bool wDnRszotpH = false;
      bool xKYXkkozhx = false;
      bool dfZqTfBzGQ = false;
      bool sBRBFmCjgf = false;
      bool ScqLPgYeOC = false;
      bool hnJVdQdwxM = false;
      bool yonZOusWSx = false;
      bool hFSBeAoObl = false;
      bool HWkDhFruXn = false;
      bool JFlThcnQwU = false;
      bool nBLQTcUHqc = false;
      bool bPULFaEjqJ = false;
      bool DxzdnbSzTB = false;
      string yrMaeGAySS;
      string bmhxElDqKl;
      string yZuXNzdffi;
      string gmgharcYmR;
      string GmggOQjxCA;
      string hywCgYwoNe;
      string bUSjloGAWL;
      string JdDrfKrNIw;
      string OfceAhpdAB;
      string unKIpkUxuZ;
      string KjaqqDtEWW;
      string fifRPwqniD;
      string ybAUPUSuCt;
      string puSikeFknx;
      string mlHcVMIsst;
      string tfOqaijFbV;
      string jzBcgkPwgj;
      string pFAlPLUWzC;
      string MZCIzJgaIC;
      string uzJRMnjdwj;
      if(yrMaeGAySS == KjaqqDtEWW){xLMIDnfbbO = true;}
      else if(KjaqqDtEWW == yrMaeGAySS){sBRBFmCjgf = true;}
      if(bmhxElDqKl == fifRPwqniD){NNGYIKxscW = true;}
      else if(fifRPwqniD == bmhxElDqKl){ScqLPgYeOC = true;}
      if(yZuXNzdffi == ybAUPUSuCt){EondopwhZb = true;}
      else if(ybAUPUSuCt == yZuXNzdffi){hnJVdQdwxM = true;}
      if(gmgharcYmR == puSikeFknx){bpZOFBNsEL = true;}
      else if(puSikeFknx == gmgharcYmR){yonZOusWSx = true;}
      if(GmggOQjxCA == mlHcVMIsst){dEzsngskJB = true;}
      else if(mlHcVMIsst == GmggOQjxCA){hFSBeAoObl = true;}
      if(hywCgYwoNe == tfOqaijFbV){qqBZfHXhTM = true;}
      else if(tfOqaijFbV == hywCgYwoNe){HWkDhFruXn = true;}
      if(bUSjloGAWL == jzBcgkPwgj){rxCzmXnrSH = true;}
      else if(jzBcgkPwgj == bUSjloGAWL){JFlThcnQwU = true;}
      if(JdDrfKrNIw == pFAlPLUWzC){wDnRszotpH = true;}
      if(OfceAhpdAB == MZCIzJgaIC){xKYXkkozhx = true;}
      if(unKIpkUxuZ == uzJRMnjdwj){dfZqTfBzGQ = true;}
      while(pFAlPLUWzC == JdDrfKrNIw){nBLQTcUHqc = true;}
      while(MZCIzJgaIC == MZCIzJgaIC){bPULFaEjqJ = true;}
      while(uzJRMnjdwj == uzJRMnjdwj){DxzdnbSzTB = true;}
      if(xLMIDnfbbO == true){xLMIDnfbbO = false;}
      if(NNGYIKxscW == true){NNGYIKxscW = false;}
      if(EondopwhZb == true){EondopwhZb = false;}
      if(bpZOFBNsEL == true){bpZOFBNsEL = false;}
      if(dEzsngskJB == true){dEzsngskJB = false;}
      if(qqBZfHXhTM == true){qqBZfHXhTM = false;}
      if(rxCzmXnrSH == true){rxCzmXnrSH = false;}
      if(wDnRszotpH == true){wDnRszotpH = false;}
      if(xKYXkkozhx == true){xKYXkkozhx = false;}
      if(dfZqTfBzGQ == true){dfZqTfBzGQ = false;}
      if(sBRBFmCjgf == true){sBRBFmCjgf = false;}
      if(ScqLPgYeOC == true){ScqLPgYeOC = false;}
      if(hnJVdQdwxM == true){hnJVdQdwxM = false;}
      if(yonZOusWSx == true){yonZOusWSx = false;}
      if(hFSBeAoObl == true){hFSBeAoObl = false;}
      if(HWkDhFruXn == true){HWkDhFruXn = false;}
      if(JFlThcnQwU == true){JFlThcnQwU = false;}
      if(nBLQTcUHqc == true){nBLQTcUHqc = false;}
      if(bPULFaEjqJ == true){bPULFaEjqJ = false;}
      if(DxzdnbSzTB == true){DxzdnbSzTB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NNBFGTFOPE
{ 
  void xyZYUdXEEV()
  { 
      bool tAjEKRLZiK = false;
      bool aNRWtrDVDA = false;
      bool rnBTnzOqJV = false;
      bool oKwrlMTQkZ = false;
      bool ebaQRZRiyr = false;
      bool qhrIiGyPQK = false;
      bool CTQMVPRZkh = false;
      bool XmkcUQMkBO = false;
      bool hfsQeHRmIf = false;
      bool NDAZWKLOuC = false;
      bool HqxPTEwPnS = false;
      bool sNNCcWazgN = false;
      bool xeRFUTlKFJ = false;
      bool EyozGphdxa = false;
      bool LCzolzoyxA = false;
      bool jMhgEcZrtz = false;
      bool RkJdNuXOul = false;
      bool nwBFCuebSU = false;
      bool dnNFZrPIuc = false;
      bool QpixJZsVbq = false;
      string gaPzEFQHGi;
      string PFNnlYMAth;
      string hEVHFoBwYF;
      string xZocMIudfE;
      string kOrYIxIDHa;
      string eyxWybFItP;
      string EThAlpQjac;
      string diUpwTMxyH;
      string fyoxazbRek;
      string CmiQARfrlS;
      string gYbexudHZd;
      string OIJmiFejYl;
      string NyFpapzDpe;
      string mUKfaHVJAf;
      string UUqAVsdwgt;
      string mwSAEhSlEH;
      string uZRuqtycMb;
      string jUjsQsHFTg;
      string MDVurqBKbr;
      string njFrjuDwIb;
      if(gaPzEFQHGi == gYbexudHZd){tAjEKRLZiK = true;}
      else if(gYbexudHZd == gaPzEFQHGi){HqxPTEwPnS = true;}
      if(PFNnlYMAth == OIJmiFejYl){aNRWtrDVDA = true;}
      else if(OIJmiFejYl == PFNnlYMAth){sNNCcWazgN = true;}
      if(hEVHFoBwYF == NyFpapzDpe){rnBTnzOqJV = true;}
      else if(NyFpapzDpe == hEVHFoBwYF){xeRFUTlKFJ = true;}
      if(xZocMIudfE == mUKfaHVJAf){oKwrlMTQkZ = true;}
      else if(mUKfaHVJAf == xZocMIudfE){EyozGphdxa = true;}
      if(kOrYIxIDHa == UUqAVsdwgt){ebaQRZRiyr = true;}
      else if(UUqAVsdwgt == kOrYIxIDHa){LCzolzoyxA = true;}
      if(eyxWybFItP == mwSAEhSlEH){qhrIiGyPQK = true;}
      else if(mwSAEhSlEH == eyxWybFItP){jMhgEcZrtz = true;}
      if(EThAlpQjac == uZRuqtycMb){CTQMVPRZkh = true;}
      else if(uZRuqtycMb == EThAlpQjac){RkJdNuXOul = true;}
      if(diUpwTMxyH == jUjsQsHFTg){XmkcUQMkBO = true;}
      if(fyoxazbRek == MDVurqBKbr){hfsQeHRmIf = true;}
      if(CmiQARfrlS == njFrjuDwIb){NDAZWKLOuC = true;}
      while(jUjsQsHFTg == diUpwTMxyH){nwBFCuebSU = true;}
      while(MDVurqBKbr == MDVurqBKbr){dnNFZrPIuc = true;}
      while(njFrjuDwIb == njFrjuDwIb){QpixJZsVbq = true;}
      if(tAjEKRLZiK == true){tAjEKRLZiK = false;}
      if(aNRWtrDVDA == true){aNRWtrDVDA = false;}
      if(rnBTnzOqJV == true){rnBTnzOqJV = false;}
      if(oKwrlMTQkZ == true){oKwrlMTQkZ = false;}
      if(ebaQRZRiyr == true){ebaQRZRiyr = false;}
      if(qhrIiGyPQK == true){qhrIiGyPQK = false;}
      if(CTQMVPRZkh == true){CTQMVPRZkh = false;}
      if(XmkcUQMkBO == true){XmkcUQMkBO = false;}
      if(hfsQeHRmIf == true){hfsQeHRmIf = false;}
      if(NDAZWKLOuC == true){NDAZWKLOuC = false;}
      if(HqxPTEwPnS == true){HqxPTEwPnS = false;}
      if(sNNCcWazgN == true){sNNCcWazgN = false;}
      if(xeRFUTlKFJ == true){xeRFUTlKFJ = false;}
      if(EyozGphdxa == true){EyozGphdxa = false;}
      if(LCzolzoyxA == true){LCzolzoyxA = false;}
      if(jMhgEcZrtz == true){jMhgEcZrtz = false;}
      if(RkJdNuXOul == true){RkJdNuXOul = false;}
      if(nwBFCuebSU == true){nwBFCuebSU = false;}
      if(dnNFZrPIuc == true){dnNFZrPIuc = false;}
      if(QpixJZsVbq == true){QpixJZsVbq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PAQGRDUGXF
{ 
  void tVhdEOXdgT()
  { 
      bool gCjDryTCuu = false;
      bool XeJEmElBLf = false;
      bool KYBGiRjRUw = false;
      bool omkkzejAeK = false;
      bool WaSOZaDYdq = false;
      bool ulsQAIBdUa = false;
      bool NChzFjtYEI = false;
      bool TlVAJjFlfH = false;
      bool NLmcADtTjq = false;
      bool dGeEwTrTIo = false;
      bool feTVWJPrGQ = false;
      bool COxMMCOEzB = false;
      bool pZnNdNGREo = false;
      bool qldpahqQGp = false;
      bool nBNToPISrt = false;
      bool FmUHzGpGrJ = false;
      bool CynQYPjHkd = false;
      bool KxyIMnMUXN = false;
      bool EnZJjERVqU = false;
      bool rkYwnpNwuY = false;
      string SDaOZXGqeR;
      string AqPzfscqLX;
      string ZjLlEjDeRt;
      string AZMbSltPrq;
      string PCltoKChfO;
      string tmpyohqoKp;
      string UbZjQaenft;
      string zNzTIWyQws;
      string hVzCANjOlj;
      string tEFBWnbCdO;
      string fOBkPgnVoS;
      string jZrQIzbXjD;
      string pQBwAtIxwU;
      string uwmhMSTOmT;
      string YNYTzTMnsX;
      string LESZXPMFkU;
      string XpZUWnmKDo;
      string eNjPdcqgwf;
      string gTEXIpcNJx;
      string GNcRuhmEwL;
      if(SDaOZXGqeR == fOBkPgnVoS){gCjDryTCuu = true;}
      else if(fOBkPgnVoS == SDaOZXGqeR){feTVWJPrGQ = true;}
      if(AqPzfscqLX == jZrQIzbXjD){XeJEmElBLf = true;}
      else if(jZrQIzbXjD == AqPzfscqLX){COxMMCOEzB = true;}
      if(ZjLlEjDeRt == pQBwAtIxwU){KYBGiRjRUw = true;}
      else if(pQBwAtIxwU == ZjLlEjDeRt){pZnNdNGREo = true;}
      if(AZMbSltPrq == uwmhMSTOmT){omkkzejAeK = true;}
      else if(uwmhMSTOmT == AZMbSltPrq){qldpahqQGp = true;}
      if(PCltoKChfO == YNYTzTMnsX){WaSOZaDYdq = true;}
      else if(YNYTzTMnsX == PCltoKChfO){nBNToPISrt = true;}
      if(tmpyohqoKp == LESZXPMFkU){ulsQAIBdUa = true;}
      else if(LESZXPMFkU == tmpyohqoKp){FmUHzGpGrJ = true;}
      if(UbZjQaenft == XpZUWnmKDo){NChzFjtYEI = true;}
      else if(XpZUWnmKDo == UbZjQaenft){CynQYPjHkd = true;}
      if(zNzTIWyQws == eNjPdcqgwf){TlVAJjFlfH = true;}
      if(hVzCANjOlj == gTEXIpcNJx){NLmcADtTjq = true;}
      if(tEFBWnbCdO == GNcRuhmEwL){dGeEwTrTIo = true;}
      while(eNjPdcqgwf == zNzTIWyQws){KxyIMnMUXN = true;}
      while(gTEXIpcNJx == gTEXIpcNJx){EnZJjERVqU = true;}
      while(GNcRuhmEwL == GNcRuhmEwL){rkYwnpNwuY = true;}
      if(gCjDryTCuu == true){gCjDryTCuu = false;}
      if(XeJEmElBLf == true){XeJEmElBLf = false;}
      if(KYBGiRjRUw == true){KYBGiRjRUw = false;}
      if(omkkzejAeK == true){omkkzejAeK = false;}
      if(WaSOZaDYdq == true){WaSOZaDYdq = false;}
      if(ulsQAIBdUa == true){ulsQAIBdUa = false;}
      if(NChzFjtYEI == true){NChzFjtYEI = false;}
      if(TlVAJjFlfH == true){TlVAJjFlfH = false;}
      if(NLmcADtTjq == true){NLmcADtTjq = false;}
      if(dGeEwTrTIo == true){dGeEwTrTIo = false;}
      if(feTVWJPrGQ == true){feTVWJPrGQ = false;}
      if(COxMMCOEzB == true){COxMMCOEzB = false;}
      if(pZnNdNGREo == true){pZnNdNGREo = false;}
      if(qldpahqQGp == true){qldpahqQGp = false;}
      if(nBNToPISrt == true){nBNToPISrt = false;}
      if(FmUHzGpGrJ == true){FmUHzGpGrJ = false;}
      if(CynQYPjHkd == true){CynQYPjHkd = false;}
      if(KxyIMnMUXN == true){KxyIMnMUXN = false;}
      if(EnZJjERVqU == true){EnZJjERVqU = false;}
      if(rkYwnpNwuY == true){rkYwnpNwuY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XPYEUCIOJP
{ 
  void SFYLemwUQo()
  { 
      bool VzgyXRQXWp = false;
      bool JVPOpFCAcF = false;
      bool nHLZIXJSzE = false;
      bool OZwxqdQiUM = false;
      bool PoshGqMMhK = false;
      bool lPQuYOnGoA = false;
      bool IyXRaiYSXL = false;
      bool oTfPozNdSR = false;
      bool LxjnSzJBYb = false;
      bool pJsUDRQaGX = false;
      bool RtnVUSjAFY = false;
      bool BJmXnLNiza = false;
      bool ZWsuVfZKLW = false;
      bool imWuzRIOTA = false;
      bool OIwzagVUfr = false;
      bool EgbfxtAsAo = false;
      bool rZnipNlqYW = false;
      bool DzPzMRatUn = false;
      bool JEdTRBKqyE = false;
      bool RONeIoTMIM = false;
      string sHPSRqEtWF;
      string jMPaeWIiUn;
      string iVjftfndit;
      string YXCTmXwfId;
      string QCzQZFxmqI;
      string BMBMHXXjXk;
      string DaKbfMJunH;
      string ZcZqXfWSGn;
      string hBmarMVpMP;
      string zMHXZpqWkM;
      string wByjhYmKoa;
      string BFciCCmjiT;
      string qTiYHNVCQg;
      string nzhsrfCDsT;
      string ZKAlNtiXUX;
      string CHmQVbSZbU;
      string DjtHlBXjqV;
      string zjqPtfSwKN;
      string dxgsegMQXQ;
      string NbaYQoQsAM;
      if(sHPSRqEtWF == wByjhYmKoa){VzgyXRQXWp = true;}
      else if(wByjhYmKoa == sHPSRqEtWF){RtnVUSjAFY = true;}
      if(jMPaeWIiUn == BFciCCmjiT){JVPOpFCAcF = true;}
      else if(BFciCCmjiT == jMPaeWIiUn){BJmXnLNiza = true;}
      if(iVjftfndit == qTiYHNVCQg){nHLZIXJSzE = true;}
      else if(qTiYHNVCQg == iVjftfndit){ZWsuVfZKLW = true;}
      if(YXCTmXwfId == nzhsrfCDsT){OZwxqdQiUM = true;}
      else if(nzhsrfCDsT == YXCTmXwfId){imWuzRIOTA = true;}
      if(QCzQZFxmqI == ZKAlNtiXUX){PoshGqMMhK = true;}
      else if(ZKAlNtiXUX == QCzQZFxmqI){OIwzagVUfr = true;}
      if(BMBMHXXjXk == CHmQVbSZbU){lPQuYOnGoA = true;}
      else if(CHmQVbSZbU == BMBMHXXjXk){EgbfxtAsAo = true;}
      if(DaKbfMJunH == DjtHlBXjqV){IyXRaiYSXL = true;}
      else if(DjtHlBXjqV == DaKbfMJunH){rZnipNlqYW = true;}
      if(ZcZqXfWSGn == zjqPtfSwKN){oTfPozNdSR = true;}
      if(hBmarMVpMP == dxgsegMQXQ){LxjnSzJBYb = true;}
      if(zMHXZpqWkM == NbaYQoQsAM){pJsUDRQaGX = true;}
      while(zjqPtfSwKN == ZcZqXfWSGn){DzPzMRatUn = true;}
      while(dxgsegMQXQ == dxgsegMQXQ){JEdTRBKqyE = true;}
      while(NbaYQoQsAM == NbaYQoQsAM){RONeIoTMIM = true;}
      if(VzgyXRQXWp == true){VzgyXRQXWp = false;}
      if(JVPOpFCAcF == true){JVPOpFCAcF = false;}
      if(nHLZIXJSzE == true){nHLZIXJSzE = false;}
      if(OZwxqdQiUM == true){OZwxqdQiUM = false;}
      if(PoshGqMMhK == true){PoshGqMMhK = false;}
      if(lPQuYOnGoA == true){lPQuYOnGoA = false;}
      if(IyXRaiYSXL == true){IyXRaiYSXL = false;}
      if(oTfPozNdSR == true){oTfPozNdSR = false;}
      if(LxjnSzJBYb == true){LxjnSzJBYb = false;}
      if(pJsUDRQaGX == true){pJsUDRQaGX = false;}
      if(RtnVUSjAFY == true){RtnVUSjAFY = false;}
      if(BJmXnLNiza == true){BJmXnLNiza = false;}
      if(ZWsuVfZKLW == true){ZWsuVfZKLW = false;}
      if(imWuzRIOTA == true){imWuzRIOTA = false;}
      if(OIwzagVUfr == true){OIwzagVUfr = false;}
      if(EgbfxtAsAo == true){EgbfxtAsAo = false;}
      if(rZnipNlqYW == true){rZnipNlqYW = false;}
      if(DzPzMRatUn == true){DzPzMRatUn = false;}
      if(JEdTRBKqyE == true){JEdTRBKqyE = false;}
      if(RONeIoTMIM == true){RONeIoTMIM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KUAPQTKQYN
{ 
  void SdOGFTscYa()
  { 
      bool YUnJfJTGZJ = false;
      bool wfnylecJYY = false;
      bool IpXjRYkbwT = false;
      bool oJBjCnuRbd = false;
      bool gasFifNgzl = false;
      bool dYRqchwDrH = false;
      bool YqKFUmeDwx = false;
      bool jKgtqhwSAl = false;
      bool LDcJpPrJHT = false;
      bool rqZUFpPnjw = false;
      bool AJkCCSrWAu = false;
      bool lcDFuVOAOF = false;
      bool uVwbFrjLoB = false;
      bool RHiElBSZGW = false;
      bool WUJMgOnUYj = false;
      bool aPYeBeNIwJ = false;
      bool ifhycetzTt = false;
      bool CnsrhZLjtp = false;
      bool EPlFZCiECG = false;
      bool nJdwnqlKiC = false;
      string WCEdmGGyAQ;
      string nCeuTmAbRT;
      string aMPRJgxtLV;
      string weTVdydQhF;
      string IOtHPhQaFT;
      string lOunUKllTF;
      string JLldTIiJRV;
      string IjsLLLRHCb;
      string QVorigjfAT;
      string MqwcuwbPmG;
      string zGIiLCVibJ;
      string rdjrnnVtum;
      string YCIyJQmQQO;
      string iCTwbKMFfg;
      string LBDqbhHDnH;
      string ahUAgwyKZt;
      string OESMZpJmPd;
      string aQNNaXzRWa;
      string IibInBgTOf;
      string LBfkRGipQl;
      if(WCEdmGGyAQ == zGIiLCVibJ){YUnJfJTGZJ = true;}
      else if(zGIiLCVibJ == WCEdmGGyAQ){AJkCCSrWAu = true;}
      if(nCeuTmAbRT == rdjrnnVtum){wfnylecJYY = true;}
      else if(rdjrnnVtum == nCeuTmAbRT){lcDFuVOAOF = true;}
      if(aMPRJgxtLV == YCIyJQmQQO){IpXjRYkbwT = true;}
      else if(YCIyJQmQQO == aMPRJgxtLV){uVwbFrjLoB = true;}
      if(weTVdydQhF == iCTwbKMFfg){oJBjCnuRbd = true;}
      else if(iCTwbKMFfg == weTVdydQhF){RHiElBSZGW = true;}
      if(IOtHPhQaFT == LBDqbhHDnH){gasFifNgzl = true;}
      else if(LBDqbhHDnH == IOtHPhQaFT){WUJMgOnUYj = true;}
      if(lOunUKllTF == ahUAgwyKZt){dYRqchwDrH = true;}
      else if(ahUAgwyKZt == lOunUKllTF){aPYeBeNIwJ = true;}
      if(JLldTIiJRV == OESMZpJmPd){YqKFUmeDwx = true;}
      else if(OESMZpJmPd == JLldTIiJRV){ifhycetzTt = true;}
      if(IjsLLLRHCb == aQNNaXzRWa){jKgtqhwSAl = true;}
      if(QVorigjfAT == IibInBgTOf){LDcJpPrJHT = true;}
      if(MqwcuwbPmG == LBfkRGipQl){rqZUFpPnjw = true;}
      while(aQNNaXzRWa == IjsLLLRHCb){CnsrhZLjtp = true;}
      while(IibInBgTOf == IibInBgTOf){EPlFZCiECG = true;}
      while(LBfkRGipQl == LBfkRGipQl){nJdwnqlKiC = true;}
      if(YUnJfJTGZJ == true){YUnJfJTGZJ = false;}
      if(wfnylecJYY == true){wfnylecJYY = false;}
      if(IpXjRYkbwT == true){IpXjRYkbwT = false;}
      if(oJBjCnuRbd == true){oJBjCnuRbd = false;}
      if(gasFifNgzl == true){gasFifNgzl = false;}
      if(dYRqchwDrH == true){dYRqchwDrH = false;}
      if(YqKFUmeDwx == true){YqKFUmeDwx = false;}
      if(jKgtqhwSAl == true){jKgtqhwSAl = false;}
      if(LDcJpPrJHT == true){LDcJpPrJHT = false;}
      if(rqZUFpPnjw == true){rqZUFpPnjw = false;}
      if(AJkCCSrWAu == true){AJkCCSrWAu = false;}
      if(lcDFuVOAOF == true){lcDFuVOAOF = false;}
      if(uVwbFrjLoB == true){uVwbFrjLoB = false;}
      if(RHiElBSZGW == true){RHiElBSZGW = false;}
      if(WUJMgOnUYj == true){WUJMgOnUYj = false;}
      if(aPYeBeNIwJ == true){aPYeBeNIwJ = false;}
      if(ifhycetzTt == true){ifhycetzTt = false;}
      if(CnsrhZLjtp == true){CnsrhZLjtp = false;}
      if(EPlFZCiECG == true){EPlFZCiECG = false;}
      if(nJdwnqlKiC == true){nJdwnqlKiC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLNJXLUKWR
{ 
  void LsClCpsxRh()
  { 
      bool kDTilymAUE = false;
      bool IyoaNcBVRA = false;
      bool RgLTRMzlQg = false;
      bool irEgIWFdiA = false;
      bool hLpNnmJGPW = false;
      bool FzCGLDrzQY = false;
      bool yBinVPsISp = false;
      bool WWmRSGqxee = false;
      bool DrWsajpxVE = false;
      bool eFNJBgbBrY = false;
      bool sBnYAhMjnE = false;
      bool MtUlVFdpMk = false;
      bool YulOLQJcQl = false;
      bool doFGlBEysr = false;
      bool WGJQqkkbmu = false;
      bool CloGAxOZMi = false;
      bool XiSBaXoNAU = false;
      bool BfwTORlVWZ = false;
      bool fhoUjrAyGn = false;
      bool lekKTmmHpT = false;
      string CrjHRebNqj;
      string FAuMsAVbIq;
      string thxXkRHwOH;
      string oNVehiBpnf;
      string wjTMTyStBx;
      string rDnpFUuLVA;
      string XeyitqdQdK;
      string zenbuKNjEm;
      string zNtQPkYfYN;
      string noUnIQkjRb;
      string TCPqyMPLtu;
      string GKHiAJkhTJ;
      string SyqQWJKATd;
      string YcSbSwyDRC;
      string VNkdGchkmy;
      string fDQIJVLzUo;
      string COqQVdreQD;
      string LhPQmENMJs;
      string aZNVyVLKSw;
      string kyhcAGVUHc;
      if(CrjHRebNqj == TCPqyMPLtu){kDTilymAUE = true;}
      else if(TCPqyMPLtu == CrjHRebNqj){sBnYAhMjnE = true;}
      if(FAuMsAVbIq == GKHiAJkhTJ){IyoaNcBVRA = true;}
      else if(GKHiAJkhTJ == FAuMsAVbIq){MtUlVFdpMk = true;}
      if(thxXkRHwOH == SyqQWJKATd){RgLTRMzlQg = true;}
      else if(SyqQWJKATd == thxXkRHwOH){YulOLQJcQl = true;}
      if(oNVehiBpnf == YcSbSwyDRC){irEgIWFdiA = true;}
      else if(YcSbSwyDRC == oNVehiBpnf){doFGlBEysr = true;}
      if(wjTMTyStBx == VNkdGchkmy){hLpNnmJGPW = true;}
      else if(VNkdGchkmy == wjTMTyStBx){WGJQqkkbmu = true;}
      if(rDnpFUuLVA == fDQIJVLzUo){FzCGLDrzQY = true;}
      else if(fDQIJVLzUo == rDnpFUuLVA){CloGAxOZMi = true;}
      if(XeyitqdQdK == COqQVdreQD){yBinVPsISp = true;}
      else if(COqQVdreQD == XeyitqdQdK){XiSBaXoNAU = true;}
      if(zenbuKNjEm == LhPQmENMJs){WWmRSGqxee = true;}
      if(zNtQPkYfYN == aZNVyVLKSw){DrWsajpxVE = true;}
      if(noUnIQkjRb == kyhcAGVUHc){eFNJBgbBrY = true;}
      while(LhPQmENMJs == zenbuKNjEm){BfwTORlVWZ = true;}
      while(aZNVyVLKSw == aZNVyVLKSw){fhoUjrAyGn = true;}
      while(kyhcAGVUHc == kyhcAGVUHc){lekKTmmHpT = true;}
      if(kDTilymAUE == true){kDTilymAUE = false;}
      if(IyoaNcBVRA == true){IyoaNcBVRA = false;}
      if(RgLTRMzlQg == true){RgLTRMzlQg = false;}
      if(irEgIWFdiA == true){irEgIWFdiA = false;}
      if(hLpNnmJGPW == true){hLpNnmJGPW = false;}
      if(FzCGLDrzQY == true){FzCGLDrzQY = false;}
      if(yBinVPsISp == true){yBinVPsISp = false;}
      if(WWmRSGqxee == true){WWmRSGqxee = false;}
      if(DrWsajpxVE == true){DrWsajpxVE = false;}
      if(eFNJBgbBrY == true){eFNJBgbBrY = false;}
      if(sBnYAhMjnE == true){sBnYAhMjnE = false;}
      if(MtUlVFdpMk == true){MtUlVFdpMk = false;}
      if(YulOLQJcQl == true){YulOLQJcQl = false;}
      if(doFGlBEysr == true){doFGlBEysr = false;}
      if(WGJQqkkbmu == true){WGJQqkkbmu = false;}
      if(CloGAxOZMi == true){CloGAxOZMi = false;}
      if(XiSBaXoNAU == true){XiSBaXoNAU = false;}
      if(BfwTORlVWZ == true){BfwTORlVWZ = false;}
      if(fhoUjrAyGn == true){fhoUjrAyGn = false;}
      if(lekKTmmHpT == true){lekKTmmHpT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NIAXKUOTGH
{ 
  void CVnLPwZsRO()
  { 
      bool FVoUKxwcjD = false;
      bool jdZnfelYQu = false;
      bool CFaPENSOmP = false;
      bool SuzebiryBH = false;
      bool rUGwikzqzS = false;
      bool KNlMpzuYQx = false;
      bool dgoUknduLw = false;
      bool mnWIDgyefT = false;
      bool NbPTEEImnb = false;
      bool nShEcKelLu = false;
      bool GDeCfWpdII = false;
      bool BPsxiCRVPf = false;
      bool eqGiHUFSer = false;
      bool BMTkMKwMnh = false;
      bool NedfaYZkUa = false;
      bool sJVePPxwuL = false;
      bool QXyQGowHjY = false;
      bool GEghSzMaHi = false;
      bool uUxEyrpnUx = false;
      bool NARcQpgNYl = false;
      string tlQflLrBik;
      string qkILzuUmXA;
      string HIykkdRkfJ;
      string BoQDqbLFSD;
      string DYjwoaqhdY;
      string giRTxkmeuI;
      string tHUYiBUFUX;
      string iPTTxiXCwJ;
      string mjHHcSWwFF;
      string nfJKIwELNm;
      string GkMFoRPxWO;
      string MkikVKzMwP;
      string eXzPjDFILB;
      string eMnICBWBRK;
      string DYYqrCxXoy;
      string wqOxIilxVl;
      string MGlViAxaiT;
      string myulMFyHWh;
      string FgTMFnyqzT;
      string PZefyxmDHr;
      if(tlQflLrBik == GkMFoRPxWO){FVoUKxwcjD = true;}
      else if(GkMFoRPxWO == tlQflLrBik){GDeCfWpdII = true;}
      if(qkILzuUmXA == MkikVKzMwP){jdZnfelYQu = true;}
      else if(MkikVKzMwP == qkILzuUmXA){BPsxiCRVPf = true;}
      if(HIykkdRkfJ == eXzPjDFILB){CFaPENSOmP = true;}
      else if(eXzPjDFILB == HIykkdRkfJ){eqGiHUFSer = true;}
      if(BoQDqbLFSD == eMnICBWBRK){SuzebiryBH = true;}
      else if(eMnICBWBRK == BoQDqbLFSD){BMTkMKwMnh = true;}
      if(DYjwoaqhdY == DYYqrCxXoy){rUGwikzqzS = true;}
      else if(DYYqrCxXoy == DYjwoaqhdY){NedfaYZkUa = true;}
      if(giRTxkmeuI == wqOxIilxVl){KNlMpzuYQx = true;}
      else if(wqOxIilxVl == giRTxkmeuI){sJVePPxwuL = true;}
      if(tHUYiBUFUX == MGlViAxaiT){dgoUknduLw = true;}
      else if(MGlViAxaiT == tHUYiBUFUX){QXyQGowHjY = true;}
      if(iPTTxiXCwJ == myulMFyHWh){mnWIDgyefT = true;}
      if(mjHHcSWwFF == FgTMFnyqzT){NbPTEEImnb = true;}
      if(nfJKIwELNm == PZefyxmDHr){nShEcKelLu = true;}
      while(myulMFyHWh == iPTTxiXCwJ){GEghSzMaHi = true;}
      while(FgTMFnyqzT == FgTMFnyqzT){uUxEyrpnUx = true;}
      while(PZefyxmDHr == PZefyxmDHr){NARcQpgNYl = true;}
      if(FVoUKxwcjD == true){FVoUKxwcjD = false;}
      if(jdZnfelYQu == true){jdZnfelYQu = false;}
      if(CFaPENSOmP == true){CFaPENSOmP = false;}
      if(SuzebiryBH == true){SuzebiryBH = false;}
      if(rUGwikzqzS == true){rUGwikzqzS = false;}
      if(KNlMpzuYQx == true){KNlMpzuYQx = false;}
      if(dgoUknduLw == true){dgoUknduLw = false;}
      if(mnWIDgyefT == true){mnWIDgyefT = false;}
      if(NbPTEEImnb == true){NbPTEEImnb = false;}
      if(nShEcKelLu == true){nShEcKelLu = false;}
      if(GDeCfWpdII == true){GDeCfWpdII = false;}
      if(BPsxiCRVPf == true){BPsxiCRVPf = false;}
      if(eqGiHUFSer == true){eqGiHUFSer = false;}
      if(BMTkMKwMnh == true){BMTkMKwMnh = false;}
      if(NedfaYZkUa == true){NedfaYZkUa = false;}
      if(sJVePPxwuL == true){sJVePPxwuL = false;}
      if(QXyQGowHjY == true){QXyQGowHjY = false;}
      if(GEghSzMaHi == true){GEghSzMaHi = false;}
      if(uUxEyrpnUx == true){uUxEyrpnUx = false;}
      if(NARcQpgNYl == true){NARcQpgNYl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NYSAJGFKYZ
{ 
  void PNCrbDSQlj()
  { 
      bool wxaJXkWseC = false;
      bool WsBEYuBweL = false;
      bool zVnxucBzuR = false;
      bool aPMFyARncM = false;
      bool gtHKhHfNSO = false;
      bool pUfpYZJcOt = false;
      bool iXxMaHgwGX = false;
      bool dMSSeEOdOm = false;
      bool xnffbFiVfX = false;
      bool qnZicJxtia = false;
      bool ajHtjcCNLT = false;
      bool LeOaxuqQkV = false;
      bool XKQhgpljoV = false;
      bool HTtmMMgkwy = false;
      bool DVKLLLYzkh = false;
      bool RfJNCPSYNs = false;
      bool pRXpMrkaNj = false;
      bool OFUmRCzFWU = false;
      bool RmyHDbKgkx = false;
      bool tHXCHlxUyT = false;
      string QCiUgwwzhO;
      string iUGdYfFiOg;
      string xCDQCalxJV;
      string RcoXAlZAST;
      string nKNmHoZAiZ;
      string OUdWVNzRRG;
      string KyoLxGeicl;
      string FEQtrmnPIM;
      string AkNiHwyRBl;
      string mHiLJoUCoB;
      string KpWxUJEiei;
      string ZiIFFZjGDB;
      string HNhqyxVEkC;
      string SlaHCJNQOy;
      string qOmSMEzdFj;
      string FOyntxIfyW;
      string nAybPmIBCw;
      string LTqFJrZOdt;
      string yryBxEmlMF;
      string BhRrKqQKCY;
      if(QCiUgwwzhO == KpWxUJEiei){wxaJXkWseC = true;}
      else if(KpWxUJEiei == QCiUgwwzhO){ajHtjcCNLT = true;}
      if(iUGdYfFiOg == ZiIFFZjGDB){WsBEYuBweL = true;}
      else if(ZiIFFZjGDB == iUGdYfFiOg){LeOaxuqQkV = true;}
      if(xCDQCalxJV == HNhqyxVEkC){zVnxucBzuR = true;}
      else if(HNhqyxVEkC == xCDQCalxJV){XKQhgpljoV = true;}
      if(RcoXAlZAST == SlaHCJNQOy){aPMFyARncM = true;}
      else if(SlaHCJNQOy == RcoXAlZAST){HTtmMMgkwy = true;}
      if(nKNmHoZAiZ == qOmSMEzdFj){gtHKhHfNSO = true;}
      else if(qOmSMEzdFj == nKNmHoZAiZ){DVKLLLYzkh = true;}
      if(OUdWVNzRRG == FOyntxIfyW){pUfpYZJcOt = true;}
      else if(FOyntxIfyW == OUdWVNzRRG){RfJNCPSYNs = true;}
      if(KyoLxGeicl == nAybPmIBCw){iXxMaHgwGX = true;}
      else if(nAybPmIBCw == KyoLxGeicl){pRXpMrkaNj = true;}
      if(FEQtrmnPIM == LTqFJrZOdt){dMSSeEOdOm = true;}
      if(AkNiHwyRBl == yryBxEmlMF){xnffbFiVfX = true;}
      if(mHiLJoUCoB == BhRrKqQKCY){qnZicJxtia = true;}
      while(LTqFJrZOdt == FEQtrmnPIM){OFUmRCzFWU = true;}
      while(yryBxEmlMF == yryBxEmlMF){RmyHDbKgkx = true;}
      while(BhRrKqQKCY == BhRrKqQKCY){tHXCHlxUyT = true;}
      if(wxaJXkWseC == true){wxaJXkWseC = false;}
      if(WsBEYuBweL == true){WsBEYuBweL = false;}
      if(zVnxucBzuR == true){zVnxucBzuR = false;}
      if(aPMFyARncM == true){aPMFyARncM = false;}
      if(gtHKhHfNSO == true){gtHKhHfNSO = false;}
      if(pUfpYZJcOt == true){pUfpYZJcOt = false;}
      if(iXxMaHgwGX == true){iXxMaHgwGX = false;}
      if(dMSSeEOdOm == true){dMSSeEOdOm = false;}
      if(xnffbFiVfX == true){xnffbFiVfX = false;}
      if(qnZicJxtia == true){qnZicJxtia = false;}
      if(ajHtjcCNLT == true){ajHtjcCNLT = false;}
      if(LeOaxuqQkV == true){LeOaxuqQkV = false;}
      if(XKQhgpljoV == true){XKQhgpljoV = false;}
      if(HTtmMMgkwy == true){HTtmMMgkwy = false;}
      if(DVKLLLYzkh == true){DVKLLLYzkh = false;}
      if(RfJNCPSYNs == true){RfJNCPSYNs = false;}
      if(pRXpMrkaNj == true){pRXpMrkaNj = false;}
      if(OFUmRCzFWU == true){OFUmRCzFWU = false;}
      if(RmyHDbKgkx == true){RmyHDbKgkx = false;}
      if(tHXCHlxUyT == true){tHXCHlxUyT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PMYRMMVSYF
{ 
  void XDFNpMCBZW()
  { 
      bool DisPgHKLga = false;
      bool kwxZrHThws = false;
      bool lfhyzdASdj = false;
      bool KrGepeYoJX = false;
      bool SWHdaJSDJa = false;
      bool ExiDdWAtPC = false;
      bool HqhwQsoRjM = false;
      bool ieYYZPYEWp = false;
      bool LxJDfNIDAS = false;
      bool ddYGQboKMh = false;
      bool TATwqYXKcO = false;
      bool yuWYqKheQC = false;
      bool jkRQiEGRHy = false;
      bool aNroWKcNLG = false;
      bool oxalTiHzPG = false;
      bool sKtJxhiCNm = false;
      bool SFDenjDhCf = false;
      bool gUSJNmKexz = false;
      bool wGCBEQThrn = false;
      bool bazXnituyj = false;
      string mAUWxoHedF;
      string RKHdgneWNz;
      string uOadgMCBFF;
      string CebojuXYQR;
      string TfQAwWmTUH;
      string BFlZsYYqoj;
      string mGZYDlhRsl;
      string QFFweOxagJ;
      string ZifyExsCwL;
      string VfifeNGrwK;
      string oUZipuzotd;
      string ayJfKDabUG;
      string sfVgQjVZRR;
      string HFdVUEIwHI;
      string xDHSkWWDUa;
      string leXpRIzsSF;
      string ZYXbVUTmKF;
      string tdTLIpXDus;
      string NREpfchnEL;
      string FPdBhYefwQ;
      if(mAUWxoHedF == oUZipuzotd){DisPgHKLga = true;}
      else if(oUZipuzotd == mAUWxoHedF){TATwqYXKcO = true;}
      if(RKHdgneWNz == ayJfKDabUG){kwxZrHThws = true;}
      else if(ayJfKDabUG == RKHdgneWNz){yuWYqKheQC = true;}
      if(uOadgMCBFF == sfVgQjVZRR){lfhyzdASdj = true;}
      else if(sfVgQjVZRR == uOadgMCBFF){jkRQiEGRHy = true;}
      if(CebojuXYQR == HFdVUEIwHI){KrGepeYoJX = true;}
      else if(HFdVUEIwHI == CebojuXYQR){aNroWKcNLG = true;}
      if(TfQAwWmTUH == xDHSkWWDUa){SWHdaJSDJa = true;}
      else if(xDHSkWWDUa == TfQAwWmTUH){oxalTiHzPG = true;}
      if(BFlZsYYqoj == leXpRIzsSF){ExiDdWAtPC = true;}
      else if(leXpRIzsSF == BFlZsYYqoj){sKtJxhiCNm = true;}
      if(mGZYDlhRsl == ZYXbVUTmKF){HqhwQsoRjM = true;}
      else if(ZYXbVUTmKF == mGZYDlhRsl){SFDenjDhCf = true;}
      if(QFFweOxagJ == tdTLIpXDus){ieYYZPYEWp = true;}
      if(ZifyExsCwL == NREpfchnEL){LxJDfNIDAS = true;}
      if(VfifeNGrwK == FPdBhYefwQ){ddYGQboKMh = true;}
      while(tdTLIpXDus == QFFweOxagJ){gUSJNmKexz = true;}
      while(NREpfchnEL == NREpfchnEL){wGCBEQThrn = true;}
      while(FPdBhYefwQ == FPdBhYefwQ){bazXnituyj = true;}
      if(DisPgHKLga == true){DisPgHKLga = false;}
      if(kwxZrHThws == true){kwxZrHThws = false;}
      if(lfhyzdASdj == true){lfhyzdASdj = false;}
      if(KrGepeYoJX == true){KrGepeYoJX = false;}
      if(SWHdaJSDJa == true){SWHdaJSDJa = false;}
      if(ExiDdWAtPC == true){ExiDdWAtPC = false;}
      if(HqhwQsoRjM == true){HqhwQsoRjM = false;}
      if(ieYYZPYEWp == true){ieYYZPYEWp = false;}
      if(LxJDfNIDAS == true){LxJDfNIDAS = false;}
      if(ddYGQboKMh == true){ddYGQboKMh = false;}
      if(TATwqYXKcO == true){TATwqYXKcO = false;}
      if(yuWYqKheQC == true){yuWYqKheQC = false;}
      if(jkRQiEGRHy == true){jkRQiEGRHy = false;}
      if(aNroWKcNLG == true){aNroWKcNLG = false;}
      if(oxalTiHzPG == true){oxalTiHzPG = false;}
      if(sKtJxhiCNm == true){sKtJxhiCNm = false;}
      if(SFDenjDhCf == true){SFDenjDhCf = false;}
      if(gUSJNmKexz == true){gUSJNmKexz = false;}
      if(wGCBEQThrn == true){wGCBEQThrn = false;}
      if(bazXnituyj == true){bazXnituyj = false;}
    } 
}; 
